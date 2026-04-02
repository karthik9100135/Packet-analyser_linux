#include <pcap.h>
#include <vector>
#include <iostream>
#include "queue.hpp"

extern BoundedQueue<std::vector<uint8_t>> packet_queue;

void packet_handler(u_char*, const struct pcap_pkthdr* header, const u_char* packet) {
    // Copy packet safely
    std::vector<uint8_t> data(packet, packet + header->len);

    // Push to shared queue (mutex handled inside)
    packet_queue.push(data);
}

void start_capture(const char* dev) {
    char errbuf[PCAP_ERRBUF_SIZE];

    pcap_t* handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
    if (!handle) {
        std::cerr << "Error opening device: " << errbuf << "\n";
        return;
    }

    std::cout << "Capturing on interface: " << dev << "\n";

    // Infinite capture loop
    pcap_loop(handle, 0, packet_handler, nullptr);

    pcap_close(handle);
}
