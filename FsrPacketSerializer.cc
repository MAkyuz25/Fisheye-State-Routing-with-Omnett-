// FsrPacketSerializer.cc
#include "FsrPacketSerializer.h"
#include "inet/common/packet/serializer/ChunkSerializerRegistry.h"
#include "inet/routing/fsr/FsrPacket_m.h"

namespace inet::fsr {
Register_Serializer(FsrPacket, FsrPacketSerializer);

void FsrPacketSerializer::serializeChunk(MemoryOutputStream& stream, const Ptr<const Chunk>& chunk) const {
    auto pkt = staticPtrCast<const FsrPacket>(chunk);
    writeLinkEntries(stream, *pkt);
    writeNeighborEntries(stream, *pkt);
}

Ptr<Chunk> FsrPacketSerializer::deserializeChunk(MemoryInputStream& stream) const {
    auto pkt = makeShared<FsrPacket>();
    readLinkEntries(stream, *pkt);
    readNeighborEntries(stream, *pkt);
    pkt->setChunkLength(
        B(4 + pkt->getLinksArraySize()*sizeof(LinkStateEntry) +
          4 + pkt->getNeighborsListArraySize()*sizeof(Ipv4Address)));
    return pkt;
}

void FsrPacketSerializer::writeLinkEntries(MemoryOutputStream& stream, const FsrPacket& pkt) const {
    stream.writeUint32Be(pkt.getLinksArraySize());
    for (auto& e : pkt.getLinksArray()) {
        stream.writeIpv4Address(e.destAddress);
        stream.writeUint32Be(e.sequenceNumber);
        stream.writeUint8(e.neighborsStartIndex);
        stream.writeUint8(e.neighborsSize);
    }
}

void FsrPacketSerializer::writeNeighborEntries(MemoryOutputStream& stream, const FsrPacket& pkt) const {
    stream.writeUint32Be(pkt.getNeighborsListArraySize());
    for (auto& addr : pkt.getNeighborsListArray())
        stream.writeIpv4Address(addr);
}

void FsrPacketSerializer::readLinkEntries(MemoryInputStream& stream, FsrPacket& pkt) const {
    auto count = stream.readUint32Be();
    pkt.setLinksArraySize(count);
    for (size_t i = 0; i < count; ++i) {
        LinkStateEntry e;
        e.destAddress         = stream.readIpv4Address();
        e.sequenceNumber      = stream.readUint32Be();
        e.neighborsStartIndex = stream.readUint8();
        e.neighborsSize       = stream.readUint8();
        pkt.setLinks(i, e);
    }
}

void FsrPacketSerializer::readNeighborEntries(MemoryInputStream& stream, FsrPacket& pkt) const {
    auto count = stream.readUint32Be();
    pkt.setNeighborsListArraySize(count);
    for (size_t i = 0; i < count; ++i)
        pkt.setNeighborsList(i, stream.readIpv4Address());
}

} // namespace inet::fsr
