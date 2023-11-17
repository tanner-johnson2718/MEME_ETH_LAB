# Playing with out Raw Socks

Goal in this part is to actually use our raw socket generator and sniffer to send packets back and forth and see if we can learn anything from there. This is less of a super specific goal oriented lesson and more of a just play around and annotate anything youve learned. 

# Refactor Code

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
cd external_packages/ethram/src
make
```

# CRC, Packet Len, and MAC addr Lessons

We set up the laptop to send and the pi to recv and noticed the following:

* 

# Interface stats




# Wireshark vs Our Sniffer

# Resources
