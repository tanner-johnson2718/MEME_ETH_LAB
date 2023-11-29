# BCM Genet Driver Reverse Engineer

The goal of this installation is to figure out how this driver works. From our [first go around](./init_notes.md) we could see the probe and remove driver functions as well as netdev_ops functions that are actually called to use this device to process packets. The `skb_buff`, `net_dev`, and `bcmgenet_priv` are the data structures of primary interest. Some pointed questions to guide this are:

* Memory locations. fd580000? base pointer in private bcm struct?
    * Registers?

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