# Packet-analyser_linux
# Real-Time Multi-Threaded Packet Analyzer

## 📌 Overview
This project is a real-time packet analyzer built in C++ on Linux using libpcap. It captures live network traffic, parses protocol headers, and processes packets using a multithreaded architecture.

The system is designed to demonstrate core networking and systems concepts such as packet capture, protocol parsing, and concurrent processing.

---

## 🚀 Features
- Real-time packet capture using libpcap
- Parsing of Ethernet, IPv4, TCP, and UDP headers
- Multithreaded producer-consumer model
- Bounded queue for backpressure control
- Safe packet parsing with bounds checking
- Modular and extensible design

---

## 🏗️ Architecture

NIC → Kernel Buffer → Producer Thread → Bounded Queue → Consumer Thread → Parser

- Producer thread captures packets
- Consumer thread processes packets
- Queue decouples capture from processing

---

## ⚙️ Technologies Used
- C++
- Linux
- libpcap
- Multithreading (std::thread, mutex, condition_variable)

---

##  Key Concepts Demonstrated
- TCP/IP protocol stack
- Packet structure and parsing
- Kernel vs user space networking
- Multithreading and synchronization
- Backpressure and queue management
- Endianness handling

---

## 🛠️ Build Instructions

### Install dependencies
```bash
sudo apt-get install libpcap-dev

-----------------------

##🤝 Contributing

Contributions are welcome!

- Fork the repository
- Create a new branch (`feature/your-feature`)
- Commit your changes
- Open a pull request

Please ensure your code:
- Follows clean C++ practices
- Includes basic validation
- Does not break existing functionality
