# MEME Layer 1 and 2 Ethernet Lab

In this installment of the MEME series we take more of a lab homework assignment approach. The aim is to dig deeply into Layer 1 and 2 (in the OSI model) of the Ethernet standard. The approach is from a low-level / embedded / firmware software perspective. The idea is to take your everyday linux laptop, an ethernet switch and an RPI and look into the specifics of link set up, ethernet frame layout, how drivers set up the network hardware, low level networking protocols (L1 and L2), etc. Since this is such a vast topic we will narrow the scope with the following constraints:

* The main interface will be a linux system on both the laptop and RPI side (no bare metal and we will have an OS underneath us).
* We will use our everyday linux laptop with out modification and the RPI will use an off the shelf build and flash tools.
* Ideally we will make no changes to the kernel on the RPI but we make some for expolration purposes (at the end of the day we will need to dig into kernel code to fully understand this topic).
    * Kernel modules (on the RPI) are the preferred method of running kernel level code and are encourage.
* Will restrict to Layer 1 and 2 i.e. no IP, TCP, etc.
* Will focus on 10/100 mbps Ethernet, no gig ethernet.

Some defining goals to get the project going and figure out a starting point are the following:

* Understand MAC and PHY Hardware
* Understand Speed Negotiation
* Layer 1 and 2 Protocols
* MDIO and MII
* Device Trees
* Initial handshake and negotiation
* Neighbor Discovery (0xFF)
* Ring Buffer on NIC
* How do frames make their way to user-space
* Catalog important Linux commands
* Use and read Official IEEE standards

# Hardware Requirements

| Hardware | Specific Model We Use | Comments |
| --- | --- | --- |
| Linux Laptop | - | - |
| RPI | - | - |
| Uart to USB cable | - | - 
| Ethernet Switch | - | - |
| Ethernet Cords x2 | - | - |


# Part 1 Hardware set up

* [ ] Create a Raw Socket Library
* [ ] Get source and tools to build and flash a minimal RPI image
* [ ] Get RPI up and running with UART shell attached
* [ ] Develop means of pushing code to RPI
* [ ] Send and Recv a Raw Eth Frame from RPI to Laptop

# Part 2 