// FsrPacketSerializer.h
#ifndef INET_ROUTING_FSR_FSRPACKETSERIALIZER_H_
#define INET_ROUTING_FSR_FSRPACKETSERIALIZER_H_

#include "inet/common/packet/serializer/FieldsChunkSerializer.h"

namespace inet::fsr {

class INET_API FsrPacketSerializer : public FieldsChunkSerializer {
  public:
    FsrPacketSerializer() {}

  protected:
    void serializeChunk(MemoryOutputStream& stream, const Ptr<const Chunk>& chunk) const override;
    Ptr<Chunk> deserializeChunk(MemoryInputStream& stream) const override;

  private:
    void writeLinkEntries(MemoryOutputStream& stream, const FsrPacket& pkt) const;
    void writeNeighborEntries(MemoryOutputStream& stream, const FsrPacket& pkt) const;
    void readLinkEntries(MemoryInputStream& stream, FsrPacket& pkt) const;
    void readNeighborEntries(MemoryInputStream& stream, FsrPacket& pkt) const;
};

} // namespace inet::fsr

#endif // INET_ROUTING_FSR_FSRPACKETSERIALIZER_H_
