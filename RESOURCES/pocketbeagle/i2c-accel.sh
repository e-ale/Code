#!/bin/bash
if [ "$EUID" != "0" ];
  then echo "Please run as root"
  exit
fi
[ -e /sys/kernel/config/device-tree/overlays/accel ] && rmdir /sys/kernel/config/device-tree/overlays/accel
mkdir -p /sys/kernel/config/device-tree/overlays/accel
dtc -W no-unit_address_vs_reg -@ -o /sys/kernel/config/device-tree/overlays/accel/dtbo i2c-accel.dts
sleep 2
cd "/sys/bus/iio/devices/iio:device1"
watch -n0 cat in_accel_x_raw in_accel_y_raw in_accel_z_raw 
