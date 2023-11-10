# P2.1 Userspace and Command Line tool Exploration

# Sysfs

* used `/sys/class/net` 

## Sysfs Appendix

The past few MEME projects made heavy use of the sysfs interface. The goal here is to use the above playing around with sysfs to generate target questions that show how sysfs works and how to use it. The first thing we notice when we `cd /sys` is we the top dir layout of the interface.

```bash
dr-xr-xr-x   12 root     root             0 Jan  1 00:00 .
drwxr-xr-x   18 root     root          1024 Nov 10  2023 ..
drwxr-xr-x    2 root     root             0 Jan  1 00:00 block
drwxr-xr-x   27 root     root             0 Jan  1 00:00 bus
drwxr-xr-x   54 root     root             0 Jan  1 00:00 class
drwxr-xr-x    4 root     root             0 Jan  1 00:00 dev
drwxr-xr-x   10 root     root             0 Jan  1 00:00 devices
drwxr-xr-x    3 root     root             0 Jan  1 00:00 firmware
drwxr-xr-x    7 root     root             0 Jan  1 00:00 fs
drwxr-xr-x   12 root     root             0 Jan  1 00:00 kernel
drwxr-xr-x   70 root     root             0 Jan  1 00:00 module
drwxr-xr-x    2 root     root             0 Jan  1 00:00 power
```

## Resources