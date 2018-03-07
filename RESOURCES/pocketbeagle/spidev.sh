#!/bin/sh
if [ "$EUID" -ne 0 ]
  then echo "Please run as root"
  exit
fi
echo -ne "\x40\x00\x00" > /dev/spidev2.1
echo -ne "\x40\x01\x00" > /dev/spidev2.1
echo -ne "\x40\x12\xc0" > /dev/spidev2.1
echo -ne "\x40\x13\xc0" > /dev/spidev2.1
