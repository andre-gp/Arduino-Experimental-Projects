#include "Arduino.h"

struct DNSHeader
{
    uint16_t id;  
    uint16_t flags;
    uint16_t qdcount;
    uint16_t ancount;
    uint16_t nscount;
    uint16_t arcount;
};

// struct to keep track of client's ip and port
struct ClientInfo {
    IPAddress addr;
    uint16_t port;
};