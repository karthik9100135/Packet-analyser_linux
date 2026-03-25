# Architecture Overview

This project uses a producer-consumer model:

- Producer: Captures packets from kernel
- Queue: Buffers packets (bounded)
- Consumer: Parses packets

Key design goal:
Move bottleneck from kernel → user space
