#include "Fsr.h"
#include "inet/common/ModuleAccess.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/linklayer/common/InterfaceTag_m.h"

namespace inet::fsr {

Define_Module(Fsr);

Fsr::Fsr() {}

Fsr::~Fsr() {
    cancelAndDelete(helloTimer);
    cancelAndDelete(lspTimer);
    cancelAndDelete(lifetimeTimer);
}

void Fsr::initialize(int stage) {
    RoutingProtocolBase::initialize(stage);
    if (stage != INITSTAGE_LOCAL)
        return;

    // load parameters
    helloInterval     = par("helloBroadcastInterval").doubleValue();
    lspInterval       = par("lspUpdateInterval").doubleValue();
    lifetimeInterval  = par("entryLifetimeInterval").doubleValue();
    jitter            = par("maxJitter").doubleValue();
    maxLifetime       = par("maxEntryLifetime").intValue();

    // get modules
    routingTable      = getModuleFromPar<IRoutingTable>(par("routingTableModule"), this);
    interfaceTable    = getModuleFromPar<IInterfaceTable>(par("interfaceTableModule"), this);

    // configure socket
    socket.setOutputGate(gate("socketOut"));
    socket.bind(Ipv4Address(), 3131);
    socket.setBroadcast(true);
    socket.setCallback(this);

    selfAddress = routingTable->getRouterIdAsGeneric().toIpv4();
    topology[selfAddress] = {{}, 0, maxLifetime};
    distance[selfAddress] = 0;

    // schedule timers
    helloTimer    = new cMessage("HelloTimer");
    lspTimer      = new cMessage("LspTimer");
    lifetimeTimer = new cMessage("LifetimeTimer");

    scheduleAt(simTime() + uniform(0, jitter), helloTimer);
    scheduleAt(simTime() + uniform(0, jitter), lspTimer);
    scheduleAt(simTime() + uniform(0, jitter), lifetimeTimer);
}

void Fsr::handleMessageWhenUp(cMessage* msg) {
    if (msg->isSelfMessage()) {
        if (msg == helloTimer)
            handleHelloTimeout();
        else if (msg == lspTimer)
            handleLspTimeout();
        else if (msg == lifetimeTimer)
            handleLifetimeTimeout();
    }
    else
        socket.processMessage(msg);
}

void Fsr::handleHelloTimeout() {
    broadcastHello();
    scheduleAt(simTime() + helloInterval + uniform(0, jitter), helloTimer);
}

void Fsr::handleLspTimeout() {
    broadcastLspUpdate();
    scheduleAt(simTime() + lspInterval + uniform(0, jitter), lspTimer);
}

void Fsr::handleLifetimeTimeout() {
    ageEntries();
    scheduleAt(simTime() + lifetimeInterval + uniform(0, jitter), lifetimeTimer);
}

void Fsr::handleSocketData(UdpSocket*, Packet* pkt) {
    auto src  = pkt->getTag<L3AddressInd>()->getSrcAddress().toIpv4();
    auto fsrPkt = pkt->popAtFront<FsrPacket>();
    processLsp(fsrPkt, src);
    delete pkt;
}

void Fsr::handleSocketError(UdpSocket*, Indication*) {}
void Fsr::handleSocketClose(UdpSocket*) {}

void Fsr::broadcastHello() {
    auto pkt = makeShared<FsrPacket>();
    Packet out("Hello", pkt);
    out.addTag<InterfaceReq>()->setInterfaceId(interfaceTable->getInterfaceByName(par("interface"))->getInterfaceId());
    out.addTag<L3AddressReq>()->setDestAddress(Ipv4Address::ALLONES_ADDRESS);
    out.addTag<L4PortReq>()->setDestPort(3131);
    socket.send(&out);
}

void Fsr::broadcastLspUpdate() {
    topology[selfAddress].seqNum++;
    std::vector<LinkStateEntry> entries;
    std::vector<Ipv4Address>    neighbors;
    for (auto& [addr, te] : topology) {
        if (--te.life > 0) {
            entries.push_back({addr, te.seqNum, (uint8_t)neighbors.size(), (uint8_t)te.neighbors.size()});
            neighbors.insert(neighbors.end(), te.neighbors.begin(), te.neighbors.end());
        }
    }
    auto pkt = createLspPacket(entries, neighbors);

    for (auto nbr : topology[selfAddress].neighbors) {
        Packet out("LSPUpdate", pkt);
        out.clearTags();
        out.addTag<InterfaceReq>()->setInterfaceId(interfaceTable->getInterfaceByName(par("interface"))->getInterfaceId());
        out.addTag<L3AddressReq>()->setDestAddress(nbr);
        out.addTag<L4PortReq>()->setDestPort(3131);
        socket.send(&out);
    }
}

Ptr<FsrPacket> Fsr::createLspPacket(const std::vector<LinkStateEntry>& entries,
                                     const std::vector<Ipv4Address>& neighbors) const {
    auto pkt = makeShared<FsrPacket>();
    pkt->setLinksArraySize(entries.size());
    for (size_t i = 0; i < entries.size(); ++i)
        pkt->setLinks(i, entries[i]);
    pkt->setNeighborsListArraySize(neighbors.size());
    for (size_t i = 0; i < neighbors.size(); ++i)
        pkt->setNeighborsList(i, neighbors[i]);
    return pkt;
}

void Fsr::processLsp(const Ptr<const FsrPacket>& pkt, const Ipv4Address&) {
    for (auto& entry : pkt->getLinksArray()) {
        auto addr = entry.destAddress;
        auto& te = topology[addr];
        if (entry.sequenceNumber > te.seqNum) {
            te.seqNum    = entry.sequenceNumber;
            te.life      = maxLifetime;
            te.neighbors.clear();
            for (int i = entry.neighborsStartIndex; i < entry.neighborsStartIndex + entry.neighborsSize; ++i)
                te.neighbors.insert(pkt->getNeighborsList(i));
        }
    }
    recalculateRoutes();
}

void Fsr::ageEntries() {
    for (auto it = topology.begin(); it != topology.end();) {
        if (it->first != selfAddress && --it->second.life <= 0)
            it = topology.erase(it);
        else
            ++it;
    }
    recalculateRoutes();
}

void Fsr::recalculateRoutes() {
    std::queue<Ipv4Address> q;
    std::map<Ipv4Address, Ipv4Address> pred;
    distance.clear();
    for (auto& [addr, _] : topology)
        distance[addr] = UINT_MAX;
    distance[selfAddress] = 0;
    q.push(selfAddress);

    while (!q.empty()) {
        auto u = q.front(); q.pop();
        for (auto nbr : topology[u].neighbors) {
            if (distance[nbr] == UINT_MAX) {
                distance[nbr] = distance[u] + 1;
                pred[nbr]     = u;
                q.push(nbr);
            }
        }
    }

    removeOldRoutes();
    addNewRoutes(pred);
}

void Fsr::removeOldRoutes() {
    for (int i = routingTable->getNumRoutes() - 1; i >= 0; --i) {
        auto route = routingTable->getRoute(i);
        if (route->getSource() == this)
            routingTable->deleteRoute(route);
    }
}

void Fsr::addNewRoutes(const std::map<Ipv4Address, Ipv4Address>& pred) {
    for (auto& [dst, _] : pred) {
        if (dst == selfAddress || distance[dst] == UINT_MAX) continue;
        Ipv4Address nextHop = dst;
        while (pred.at(nextHop) != selfAddress)
            nextHop = pred.at(nextHop);

        auto route = routingTable->createRoute();
        route->setDestination(dst);
        route->setNextHop(nextHop);
        route->setSourceType(IRoute::MANUAL);
        route->setPrefixLength(32);
        route->setInterface(interfaceTable->getInterfaceByName(par("interface")));
        route->setMetric(distance[dst]);
        routingTable->addRoute(route);
    }
}

void Fsr::finish() {
    recordScalar("BytesSent", socket.getControlInfoBytes());
}

} // namespace inet::fsr