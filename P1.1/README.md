# P1.1 Raw Socket Example

For the very first part of this project we create a raw socket example program. It consists of two programs. First a "poor mans" wireshark where dump all traffic on a specified interface. We use raw sockets so that we can observe the full ethernet frame that each packet consits of. This program is contained in the C file [sniff.c](./sniff.c).  