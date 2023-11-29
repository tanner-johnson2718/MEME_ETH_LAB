# BCM Genet Driver Reverse Engineer

The goal of this installation is to figure out how this driver works. From our [first go around](./init_notes.md) we could see the probe and remove driver functions as well as netdev_ops functions that are actually called to use this device to process packets. The `skb_buff`, `net_dev`, and `bcmgenet_priv` are the data structures of primary interest. Some pointed questions to guide this are:

* Memory locations. fd580000? base pointer in private bcm struct?
    * Stat Registers?
* Tx/Rx queues?
* Where does the packet actually reside in the socket buffer
* DMA?
* IRQs
* Need to get into the probe function

# Reading stat registers (MIB - Management Information base)

```
base = 0xffffffc011d70000     (will change)
umac_off = 0x800
mib_stat_start = 0x400
```

* Got base addr:
    * add a bp at `bcmgenet_xmit`.
    * Set another bp a few instructions down st the priv var was in scope
    * Then `print priv->base`
* `bcmgenet_update_mib_counters` reads and updates thes counters
* In GDB `x/100xb $base+0x800+0x400` where we set base via `set $base = 0xffffffc011d70000`
* `struct bcmgenet_stats bcmgenet_gstrings_stats` defines which variables are MIB
* The other stat variables appear to be updated in software `bcmgenet_get_stats`
    * These appear to be aggregate stats calculated from the sum of each tx/rx queue counts
* `ethtool --statistics eth0` causes both `bcmgenet_update_mib_counters` and `bcmgenet_get_stats` to trigger

# Kmod to Convert to physical addrs

```C
#include <asm/memory.h>

phys_addr_t virt_to_phys(const volatile void *x);
```

# TX / RX queues

We start this where we left off in the first section. The question where are looking to answer is why are the q's labeled from 0-16 but only 0,1,2,3,and 16 are used?