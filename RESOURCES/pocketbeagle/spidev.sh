#!/bin/bash
if [ "$EUID" != "0" ];
  then echo "Please run as root"
  exit
fi
echo spi > "/sys/devices/platform/ocp/ocp:P2_25_pinmux/state"
echo spi_sclk > "/sys/devices/platform/ocp/ocp:P2_29_pinmux/state"
echo spi_cs > "/sys/devices/platform/ocp/ocp:P2_31_pinmux/state"
echo -ne "\x40\x00\x00" > /dev/spidev2.1
echo -ne "\x40\x01\x00" > /dev/spidev2.1
echo -ne "\x40\x12\xc0" > /dev/spidev2.1
echo -ne "\x40\x13\xc0" > /dev/spidev2.1
