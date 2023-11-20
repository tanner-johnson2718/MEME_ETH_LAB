# Reverse Engineer the PHY on the RPI

* BCM54213PE driver loc -> linux-*/drivers/net/phy/broadcom.c
* installed phytool from buildroot packages menu
* `include/linux/brcmphy.h` contains the register definitions for the PHY
* `include/linux/phy.c` contains includes for phy_read, phy state mahcine, etc.

# Code Set Up

## Refactor Code

The first thing we want todo is refacor the code. Also we need a dedicated place for this code to reside. So we moved the official files into the `external_packages/ethraw` directory and depricated the first version contained in `P1.1`. Next we did the following:

* Created library `libEth` with common code
* Removed as much global state as possible
* Turned consts into #define's
* Added the packet generation params as input args
* Removed CRC display code and any mention of CRC
* Removed options to dump whole packet as this isn't required.

Finally, with the scripts developed in part 1, we can cross compile and send the newly factored code to the PI with the following (making sure it is powered on and logged into):

```bash
source ./scripts/env_init.sh
./scripts/rebuild_external_package.sh ethraw
./scripts/serial_push ./buildroot/output/build/ethraw*/gen
./scripts/serial_push ./buildroot/output/build/ethraw*/sniff
```

And on the host side we can build x86 versions of the code:

```bash
cd external_packages/ethraw/src
make
```

## CRC, Packet Len, and MAC addr Lessons

We set up the laptop to send and the pi to recv and noticed the following:

* Packets inbound to pi must have MAC dest match or have a broadcast MAC to register
* In C code, raw sockets do not have any transparency into CRC, it is purely hardware.
    * Although 802.3 states this can be done by the MAC or PHY
* Stats on interface can be dumped via the [script](../scripts/sysfs_net_stat_dump.sh)
* If not listening for raw socket packets they get dropped
* Max Packet len is 1518 including CRC and 1514 in userspace raw socket

# MDIO Bus Hacking

MDIO Registers (Clause 22)
:------------:|
![](../Docs/mdio_c22_reg_table.png)

Pull PHYID from MDIO Bus:

```bash
# phytool <read/write> <if/phy num/reg> where phy num can be pulled from the sysfs interface
~ phytool read eth0/1/2
0x600d
~ phytool read eth0/1/3
0x84a2
```