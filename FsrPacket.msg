cplusplus {{
    struct LinkStateEntry {
        inet::Ipv4Address destAddress;
        unsigned int     sequenceNumber;
        uint8_t          neighborsStartIndex;
        uint8_t          neighborsSize;
    };
}}

message FsrPacket {
    fields:
        LinkStateEntry links[];
        inet::Ipv4Address neighborsList[];
}