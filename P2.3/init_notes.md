# BCM Genet MAC Driver (INIT NOTES)

First Look Notes:
* driver is bcmgenet at 'drivers/net/ethernet/broadcom/genet/*'
* First Look over, possible vectors of approaching this:
    * TX / RX Queues and ring buffers
    * DMA
    * Stat vectors / registers / etc
    * ACPI?
    * Kernel memory allocation
    * IRQs
    * PHY Interface
* Some possible "hacks"/deliverables
    * unload then load tainted genet driver
    * tainted driver allows for reception of packets not destined for it (all MACs)
    * Does wire shark read all packets regardless of MAC
    * Can I change the MAC?
* Acronyms
    * HFB - Hardware Filter Block
    * CB - control block
    * BD - buffer descriptor
    * SKB - socket buffer

# Lab 2.3.1 - Dumb Dumb Lab

Goal of the lab is to figure out how the PI responds to packets whose MAC addr is not that of the PIs. 

## Q1 

If I send a packet with a mac addr not the same as that of the PI, but switch the PHY to blink on activity, will it blink?

```bash
# On PI Change Phy to blink on activity
phytool write eth0/1/23 0x0f04
phytool write eth0/1/21 0x0199

# On PC send 10 packets at 1 sec interval with wrong mac addr
sudo ./gen enp2s0 00:00:00:00:00:00 00:00:00:00:00:00 0x6969 1514

# Observe LEDs on PI
```

**PHY Blinks w/ packets of wrong MAC ADDR**


## Q2 

Is there activity from the PHY to the phy via the rgmii bus? So we need to figure out how to determine whether or nor this bus is active. The first point of attack is determinc if the activity LED lights blink if and only if there is activity on link AND the RGMII bus.

* Does it blink in loopback mode? **NO**, in loopback mode we see no LED activity. But we know there is ARP traffic both inbound and outbound. We can see the arp packet generated by the PI MAC by using the ETH sniff program, which shows it getting send and looped back by the phy as an inbound packet. Since there is no LED activity light but there is RGMII and Link activity, we can conclude if this light is blinking then there must be activity on the link that is sent up to the MAC via the RGMII bus. Which implies the MAC is getting our packets of wrong MAC addr and filtering them somehow.

## Q3

**JUST NEED PROMISCIOUS MODE TO READ ALL PACKETS HITTING A NIC**

```bash
ifconfig eth0 promisc
```

# Lab 2.3.2 Still Trivial Lab

How can we change the MAC on PI? [See](../Docs/Changing-MAC-addresses.pdf). 

```bash
ip link set eth0 down
ip link set eth0 address 11:22:33:44:55:66
ip link set eth0 up
```

# Lab 2.3.3 Reading Registers on the MAC

* register read and writes are just mem reads at memory mapped IO
* `void __iomem base;`?
* `include/linux/netdevice.h` -> net device struct definition

# Resources
* [Old SKB Doc](http://vger.kernel.org/~davem/skb.html)
* [Change MAC on a PI](../Docs/Changing-MAC-addresses.pdf)
* [Good resource on nics?](https://www.oreilly.com/library/view/linux-device-drivers/0596005903/ch17.html)