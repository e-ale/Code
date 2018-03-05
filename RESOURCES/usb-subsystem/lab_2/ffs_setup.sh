#!/bin/sh -ex

modprobe libcomposite

# Mount configfs locally
mkdir -p config
mount none config -t configfs

# Create the USB gadget configuration
mkdir -p config/usb_gadget/
cd config/usb_gadget/

# Remove the existing (distro-created) gadget from the hardware
if [ -d g_multi ]; then
	echo "" >g_multi/UDC
fi

# Create a gadget called g1
mkdir g1
cd g1

# Set the VID/PID/Strings
echo 0x1a0a >idVendor
echo 0xbadd >idProduct
mkdir strings/0x409

# Set the VID/PID/Strings (cont'd)
echo 12345 >strings/0x409/serialnumber
echo "Signal 11" >strings/0x409/manufacturer
echo "Test" >strings/0x409/product

# Create a configuration called c.1
mkdir configs/c.1
mkdir configs/c.1/strings/0x409
echo "Config1" >configs/c.1/strings/0x409/configuration

# Setup the function, FunctionFS (named usb0)
mkdir functions/ffs.usb0
ln -s functions/ffs.usb0 configs/c.1

# Mount the function filesystem for usb0
cd ../../../
mkdir -p ffs
mount usb0 ffs -t functionfs

# From inside the mounted ffs directory, run your
# user space program and wait until it's started.
cd ffs
../ffs-test/ffs-test & # from the Linux kernel
sleep 3
cd ..

# Enable the USB device
echo musb-hdrc.0 >config/usb_gadget/g1/UDC
