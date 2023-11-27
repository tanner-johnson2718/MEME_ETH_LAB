# BCM Genet MAC Driver

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

# Lab 2.3.1 - Wireshark, PHY, and wrong MAC addrs

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

# Resources
* [Old SKB Doc](http://vger.kernel.org/~davem/skb.html)