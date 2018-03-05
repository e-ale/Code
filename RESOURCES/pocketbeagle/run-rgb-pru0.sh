#!/bin/bash
if [ "$EUID" != "0" ];
  then echo "Please run as root"
  exit
fi
# red
echo pruout > /sys/devices/platform/ocp/ocp\:P1_33_pinmux/state
# green
echo gpio > /sys/devices/platform/ocp/ocp\:P2_01_pinmux/state
echo out > /sys/class/gpio/gpio50/direction
echo 0 > /sys/class/gpio/gpio50/value
# blue
echo pruout > /sys/devices/platform/ocp/ocp\:P1_36_pinmux/state
make -f /var/lib/cloud9/examples/extras/pru/Makefile TARGET=rgb PRUN=pru0
