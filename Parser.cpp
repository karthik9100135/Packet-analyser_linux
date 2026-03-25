#include "types.hpp"
#include <iostream>
#include <arpa/inet.h>

void parse_packet(const uint8_t* packet, size_t len) {
    if (len < sizeof(EthernetHeader)) return;

    auto eth = reinterpret_cast<const EthernetHeader*>(packet);
    if (ntohs(eth->type) != 0x0800) return;

    auto ip = reinterpret_cast<const IPv4Header*>(packet + sizeof(EthernetHeader));

    uint8_t ihl = ip->version_ihl & 0x0F;
    size_t ip_len = ihl * 4;

    if (len < sizeof(EthernetHeader) + ip_len) return;

    const uint8_t* transport = packet + sizeof(EthernetHeader) + ip_len;

    if (ip->protocol == 6) {
        auto tcp = reinterpret_cast<const TCPHeader*>(transport);
        std::cout << "TCP Packet: "
                  << ntohs(tcp->src_port) << " -> "
                  << ntohs(tcp->dst_port) << "\n";
    }
    else if (ip->protocol == 17) {
        auto udp = reinterpret_cast<const UDPHeader*>(transport);
        std::cout << "UDP Packet: "
                  << ntohs(udp->src_port) << " -> "
                  << ntohs(udp->dst_port) << "\n";
    }
}
