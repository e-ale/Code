#!/bin/bash
if [ "$EUID" != "0" ];
  then echo "Please run as root"
  exit
fi
[ -e /sys/kernel/config/device-tree/overlays/foo ] && rmdir /sys/kernel/config/device-tree/overlays/foo
mkdir -p /sys/kernel/config/device-tree/overlays/foo
dtc -W no-unit_address_vs_reg -@ -o /sys/kernel/config/device-tree/overlays/foo/dtbo i2c-foo.dts
