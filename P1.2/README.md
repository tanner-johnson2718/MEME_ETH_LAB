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
# Resources

* https://medium.com/@hungryspider/building-custom-linux-for-raspberry-pi-using-buildroot-f81efc7aa817