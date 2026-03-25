#include <pcap.h>
#include <cstring>
#include "queue.hpp"

extern BoundedQueue<std::vector<uint8_t>> packet_queue;

void packet_handler(u_char*, const struct pcap_pkthdr* header, const u_char* packet) {
    std::vector<uint8_t> data(packet, packet + header->len);
    packet_queue.push(data);
}

void start_capture(const char* dev) {
    char errbuf[PCAP_ERRBUF_SIZE];

    pcap_t* handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
    if (!handle) {
        perror("pcap_open_live failed");
        return;
    }

    pcap_loop(handle, 0, packet_handler, nullptr);
}
