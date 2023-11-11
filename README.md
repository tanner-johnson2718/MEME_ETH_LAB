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

# Part 1 Hardware and Init Software set up

* [X] [P1.1](./P1.1/) - Create a Raw Socket Example Program
* [ ] [P1.2](./P1.2/) - Use BuildRoot to build and make loadable image for the RPI
    * [X] Connect to RPI via UART terminal
    * [X] Develop means of pushing code to RPI
        * [X] Develop a means of cross compiling
    * [X] Connect GDB debugger to rpi over UART.
    * [ ] Send and Recv a Raw Eth Frame from RPI to Laptop

## Finalized HW Set Up

TODO

## SW Flow

The SW flow and capabilities are encapsulated by the set of scripts: 

| script | desc | comments|
| --- | --- | --- |
| `env_init.sh` | Must be sourced before using any of the scripts | - |
| `build.sh` | The proper way to call 'make all'. Copies saved configs and external packages and issues a make call | Used when new packages are added or for initial build. Will rebuild SD image based on contents on images dir. Note does issue a recompile of any package. |
| `rebuild_external_package.sh` | A light rebuild script that rebuilds just a specific external package and rebuilds the rootfs | - |
| `create_empty_*.sh` | Creates boiler plate for user apps | the .mk file contains the instructions for building, installing, etc. |
| `flash_sd.sh` | Give it the name of the block device, will unmount any partitions and reflash with current sd image | - |
| `serial_term.sh` | Connect to terminal over uart using minicom | - | 
| `serial_copy.sh` | Copy a file over serial to device | TODO |
| `serial_gdb.sh`  | Connect arch specific gdb to device over serial | TODO | 

**Note:** to rebuild a specific package delete its build dir in output/build.  Completely remove the output dir to "nuke" the buildroot system. This will keep the package source downloaded but will force a rebuilt of everything including host tools.  

# Part 2 Linux Software Stack Exploration on RPI

* [ ] [P2.1](./P2.1/) - Use sysfs kernel interface to engage with NIC driver
* [ ] [P2.2](./P2.2/) - Use GDB to reverse Engineer a socket() call.
    * [ ] Find Def of relavent data structures
    * [ ] Create a call graph
    * [ ] Annotate importat Files
* [ ] Reverse Engineer the BCM 2711 genet driver
* [ ] Use GDB to reverse Engineer a bind() call.
    * [ ] Find Def of relavent data structures
    * [ ] Create a call graph
    * [ ] Annotate importat Files
* [ ] Set of Useful Command line args:
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