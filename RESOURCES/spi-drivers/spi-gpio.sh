#!/bin/bash
if [ "$EUID" != "0" ];
  then echo "Please run as root"
  exit
fi
#[ -e /sys/kernel/config/device-tree/overlays/spi-gpio ] && rmdir /sys/kernel/config/device-tree/overlays/spi-gpio
#mkdir -p /sys/kernel/config/device-tree/overlays/spi-gpio
#dtc -W no-unit_address_vs_reg -@ -o /sys/kernel/config/device-tree/overlays/spi-gpio/dtbo spi-gpio.dts
dtc -W no-unit_address_vs_reg -@ -o /lib/firmware/spi-gpio.dtbo spi-gpio.dts
