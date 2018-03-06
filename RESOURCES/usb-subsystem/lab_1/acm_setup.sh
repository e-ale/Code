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

# Create a function (tty CDC/ACM) named usb0
mkdir functions/acm.usb0

# Link that function to configuration c.1
ln -s functions/acm.usb0 configs/c.1

# Enable the USB device. Find the device
# name in /sys/class/udc/ .
echo musb-hdrc.0 >UDC
