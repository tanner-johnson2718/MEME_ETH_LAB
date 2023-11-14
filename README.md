# MEME Layer 1 and 2 Ethernet Lab

In this installment of the MEME series we take more of a lab homework assignment approach. The aim is to dig deeply into Layer 1 and 2 (in the OSI model) of the Ethernet standard. The approach is from a low-level / embedded / firmware software perspective. The idea is to take your everyday linux laptop, an RPI and look into the specifics of link set up, ethernet frame layout, how drivers set up the network hardware, low level networking protocols (L1 and L2), etc. Since this is such a vast topic we will narrow the scope with the following constraints:

* The main interface will be a linux system on both the laptop and RPI side.
* Will build a minimal rpi image to flash using buildroot
* Laptop will be our everyday laptop running ubuntu
* Kernel hacking will happen on RPI only
* Will simply connect an etherner cord from RPI to build PC.
* Will use UART GPIO pins on PI for interface
* Will restrict to Layer 1 and 2 i.e. no IP, TCP, etc.

Some defining goals to get the project going and figure out a starting point are the following:

<table>
 <tr>
    <td>
    <li>Understand MAC and PHY Hardware</li>
    <li>Understand Speed Negotiation</li>
    <li>Layer 1 and 2 Protocols</li>
    <li>MDIO and MII</li>
    <li>Device Trees</li>
    <li>Initial handshake and negotiation</li>
    </td>
    <td>
    <li>Neighbor Discovery (0xFF)</li>
    <li>Ring Buffer on NIC</li>
    <li>How do frames make their way to user-space</li>
    <li>Catalog important Linux commands</li>
    <li>Use and read Official IEEE standards</li>
    </td>
 </tr>
</table>




# Part 1 Hardware and Init Software set up

* [X] [P1.1](./P1.1/) - Create a Raw Socket Example Program
* [X] [P1.2](./P1.2/) - Use BuildRoot to build and make loadable image for the RPI
    * [X] Connect to RPI via UART terminal
    * [X] Develop means of pushing code to RPI
        * [X] Develop a means of cross compiling
    * [X] Connect GDB debugger to rpi over UART.
    * [X] Send and Recv a Raw Eth Frame from RPI to Laptop
    * [X] [SW Flow and How to use scripts](./P1.2/README.md#sw-flow)

# Part 2 Linux Software Stack Exploration on RPI

* [ ] [P2.1](./P2.1/) - Use sysfs kernel interface to engage with NIC driver
* []
* [ ] [P2.3](./P2.3/) - Use GDB to reverse Engineer a net sys calls.
    * [ ] Find Def of relavent data structures
    * [ ] Create a call graph
    * [ ] Annotate importat Files
* [ ] Reverse Engineer the BCM 2711 genet driver
* [ ] Track a Packet from Send to Recv in Userspaces
* [ ] Random Clean Up
    * [ ] Address Families?
    * [ ] NIC Ring Buffer

# Part 3 RPI Network Hardware Exploration

* [ ] How are Inturrupts generated
* [ ] MII and MDIO
* [ ] Device Tree
* [ ] NIC on RPI
* [ ] What is each wire on a Cat 5e cable doing
* [ ] What happens when I first plug in a cord
* [ ] Trace the physcial connections from