#include "types.hpp"
#include <iostream>
#include <arpa/inet.h>

void parse_packet(const uint8_t* packet, size_t len) {
    // Minimum Ethernet size check
    if (len < sizeof(EthernetHeader)) return;

    auto eth = reinterpret_cast<const EthernetHeader*>(packet);
    uint16_t eth_type = ntohs(eth->type);

    // IPv4
    if (eth_type == 0x0800) {
        auto ip = reinterpret_cast<const IPv4Header*>(packet + sizeof(EthernetHeader));

        uint8_t ihl = ip->version_ihl & 0x0F;
        size_t ip_len = ihl * 4;

        if (len < sizeof(EthernetHeader) + ip_len) return;

        const uint8_t* transport = packet + sizeof(EthernetHeader) + ip_len;

        if (ip->protocol == 6) {
            auto tcp = reinterpret_cast<const TCPHeader*>(transport);
            std::cout << "[IPv4][TCP] "
                      << ntohs(tcp->src_port) << " -> "
                      << ntohs(tcp->dst_port) << "\n";
        }
        else if (ip->protocol == 17) {
            auto udp = reinterpret_cast<const UDPHeader*>(transport);
            std::cout << "[IPv4][UDP] "
                      << ntohs(udp->src_port) << " -> "
                      << ntohs(udp->dst_port) << "\n";
        }
    }

    // IPv6
    else if (eth_type == 0x86DD) {
        auto ip6 = reinterpret_cast<const IPv6Header*>(packet + sizeof(EthernetHeader));

        const uint8_t* transport = packet + sizeof(EthernetHeader) + sizeof(IPv6Header);

        if (ip6->next_header == 6) {
            auto tcp = reinterpret_cast<const TCPHeader*>(transport);
            std::cout << "[IPv6][TCP] "
                      << ntohs(tcp->src_port) << " -> "
                      << ntohs(tcp->dst_port) << "\n";
        }
        else if (ip6->next_header == 17) {
            auto udp = reinterpret_cast<const UDPHeader*>(transport);
            std::cout << "[IPv6][UDP] "
                      << ntohs(udp->src_port) << " -> "
                      << ntohs(udp->dst_port) << "\n";
        }
    }
}
