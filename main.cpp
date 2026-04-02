#include <thread>
#include <vector>
#include <iostream>
#include "queue.hpp"

BoundedQueue<std::vector<uint8_t>> packet_queue(1000);

void start_capture(const char* dev);
void parse_packet(const uint8_t* packet, size_t len);

void consumer() {
    while (true) {
        auto pkt = packet_queue.pop();
        parse_packet(pkt.data(), pkt.size());
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: ./analyzer <interface>\n";
        return 1;
    }

    std::thread producer(start_capture, argv[1]);
    std::thread consumer_thread(consumer);

    producer.join();
    consumer_thread.join();

    return 0;
}
