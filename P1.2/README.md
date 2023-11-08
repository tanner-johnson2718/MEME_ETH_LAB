# P1.2 RPI Image

The goal of this step is to use BuildRoot to compile and flash a micro SD with a kernel we built. This will allow us to change kernel source and to compile kernel modules. We will use our [MEME OS 1](https://github.com/tanner-johnson2718/MEME_OS) as a starting point as we have some useful scripts to facilitate the dev process.

# Kernel Build ENV set up

The following was executed at the root dir and will create dir called 'buildroot' that contains the ENV for building our RPI root image.

```bash
# Download and set up repo for build root
touch .gitignore
echo 'buildroot' > .gitignore
wget https://buildroot.org/downloads/buildroot-2023.02.6.tar.xz
tar xf buildroot-2023.02.6.tar.xz
mv buildroot-2023.02.6 buildroot

# Move to buildroot and build the basic buildroot config
cd buildroot
make list-defconfigs   # verify that 1 it works and 2 you see raspberrypi4_64_defconfig
make raspberrypi4_64_defconfig

# There is now a .config file containing the build params for buildroot targeting
# a 64bit RPI 4. This can be saved off and modified later. Now build the image
make
```

# RPI Init Set UP

```bash
# Move to Directory where the output image, sdcard.img resides
cd output/images

# Plug the micro sd into the build PC. Use one of the following to get the device name
lsblk
dmesg

# This will give you the device name, partition name, and the mound location. Umount the partition and the mount location
sudo umount /media/user/3158-99
sudo umount /dev/mmcblk0p0

# Flash the image to the SD card
sudo dd if=sdcard.img of=/dev/mmcblk0

# Put the micro sd into the PI and connct the GND (6), UART TX (8), and UART RX (10) pins on the rpi to the UART to USB adapter. Plug USB adapter into build PC. Run the following to see the dev name
dmesg

# Plug in RPI power supply and then connect to rpi
minicom -D /dev/ttyUSB0 -b 115200

# Once in mini com CTL A is the escape key. Shift X to exit. SHift O to access options. In options->Serial Port you may have to turn off hardware flow control.
```

# Set up GDB and Attach Over UART


# Resources

* https://medium.com/@hungryspider/building-custom-linux-for-raspberry-pi-using-buildroot-f81efc7aa817