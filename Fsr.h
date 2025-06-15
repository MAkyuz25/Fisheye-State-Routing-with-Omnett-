#ifndef INET_ROUTING_FSR_FSRROUTING_H_
#define INET_ROUTING_FSR_FSRROUTING_H_

#include "inet/common/packet/Packet.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
#include "inet/networklayer/contract/IRoutingTable.h"
#include "inet/networklayer/contract/ipv4/Ipv4Address.h"
#include "inet/routing/base/RoutingProtocolBase.h"
#include "inet/routing/fsr/FsrPacket_m.h"
#include "inet/transportlayer/contract/udp/UdpSocket.h"

namespace inet::fsr {

class INET_API Fsr : public RoutingProtocolBase, public UdpSocket::ICallback {
  public:
    Fsr();
    ~Fsr() override;

    // Lifecycle
    int numInitStages() const override { return NUM_INIT_STAGES; }
    void initialize(int stage) override;
    void handleMessageWhenUp(cMessage* msg) override;
    void finish() override;

  protected:
    // Lifecycle hooks
    void handleStartOperation(LifecycleOperation* op) override;
    void handleCrashOperation(LifecycleOperation* op) override;

    // UDP callbacks
    void handleSocketData(UdpSocket* sock, Packet* pkt) override;
    void handleSocketError(UdpSocket* sock, Indication* ind) override;
    void handleSocketClose(UdpSocket* sock) override;

    // Timer handlers
    void handleHelloTimeout();
    void handleLspTimeout();
    void handleLifetimeTimeout();

    // Protocol actions
    void broadcastHello();
    void broadcastLspUpdate();
    void processLsp(const Ptr<const FsrPacket>& pkt, const Ipv4Address& sender);
    void ageEntries();
    void recalculateRoutes();

    // Helpers
    Ptr<FsrPacket> createLspPacket(const std::vector<LinkStateEntry>& entries,
                                   const std::vector<Ipv4Address>& neighbors) const;
    void removeOldRoutes();
    void addNewRoutes(const std::map<Ipv4Address, Ipv4Address>& predecessor);

  private:
    // Configuration parameters
    double helloInterval     = 0;
    double lspInterval       = 0;
    double lifetimeInterval  = 0;
    double jitter            = 0;
    int    maxLifetime       = 0;

    // Socket and address
    UdpSocket      socket;
    Ipv4Address    selfAddress;

    // Topology tables
    struct TopoEntry {
        std::set<Ipv4Address> neighbors;
        uint32_t seqNum = 0;
        int      life   = 0;
    };
    std::map<Ipv4Address, TopoEntry> topology;

    // Distance table
    std::map<Ipv4Address, uint32_t> distance;

    // Timers
    cMessage* helloTimer    = nullptr;
    cMessage* lspTimer      = nullptr;
    cMessage* lifetimeTimer = nullptr;

    // Modules
    IRoutingTable*   routingTable   = nullptr;
    IInterfaceTable* interfaceTable = nullptr;
};

} // namespace inet::fsr

#endif // INET_ROUTING_FSR_FSRROUTING_H_