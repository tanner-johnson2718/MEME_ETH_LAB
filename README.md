# MEME Layer 1 and 2 Ethernet Lab

In this installment of the MEME series we take more of a lab homework assignment approach. The aim is to dig deeply into Layer 1 and 2 (in the OSI model) of the Ethernet standard. The approach is from a low-level / embedded / firmware software perspective. The idea is to take your everyday linux laptop, an RPI and look into the specifics of link set up, ethernet frame layout, how drivers set up the network hardware, low level networking protocols (L1 and L2), etc. Since this is such a vast topic we will narrow the scope with the following constraints:

* The main interface will be a linux system on both the laptop and RPI side (no bare metal and we will have an OS underneath us).
* Will build a minimal rpi image to flash
* We will use our everyday linux laptop as our build PC and as the main target host that controls and interfaces with the RPI.
* Will simply connect an etherner cord from RPI to build PC.
* Will use UART GPIO pins on PI for interface
* Will restrict to Layer 1 and 2 i.e. no IP, TCP, etc.

Some defining goals to get the project going and figure out a starting point are the following:

<table border="0">
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

## SW Flow

The SW flow and capabilities derived in Part 1 are encapsulated by the set of scripts: 

| script | desc | comments|
| --- | --- | --- |
| `env_init.sh` | Must be sourced before using any of the scripts | - |
| `build.sh` | The proper way to call 'make all'. Copies saved configs and external packages and issues a make call | Used when new packages are added or for initial build. Will rebuild SD image based on contents on images dir. Note does issue a recompile of any package. |
| `rebuild_external_package.sh` | A light rebuild script that rebuilds just a specific external package and rebuilds the rootfs | - |
| `create_empty_*.sh` | Creates boiler plate for user apps | the .mk file contains the instructions for building, installing, etc. |
| `flash_sd.sh` | Give it the name of the block device, will unmount any partitions and reflash with current sd image | - |
| `serial_term.sh` | Connect to terminal over uart using minicom | After running once, can just use `minicom` | 
| `serial_push.sh` | Copy a file over serial to device | - |
| `serial_gdb.sh`  | Connect arch specific gdb to device over serial | Besure the device is on, logged into, in a terminal and not already in kdb |
| `serial_force_reboot.sh` | Will reboot device if it is in a terminal or in kdb | Will not work if waiting for log in |  

**Note:** to rebuild a specific package delete its build dir in output/build.  Completely remove the output dir to "nuke" the buildroot system. This will keep the package source downloaded but will force a rebuilt of everything including host tools.  

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