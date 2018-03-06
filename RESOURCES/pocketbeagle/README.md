These are some [PocketBeagle](https://beagleboard.org/pocket) + [BaconBits](https://github.com/e-ale/BaconBitsCapeHW) command-line examples

The below examples were tested on the [BeagleBoard.org 2018-03-05 Debian Stretch IoT image](http://debian.beagleboard.org/images/bone-debian-9.3-iot-armhf-2018-03-05-4gb.img.xz). Find the latest images at https://beagleboard.org/latest-images.

```
debian@beaglebone:~$ sudo /opt/scripts/tools/version.sh
git:/opt/scripts/:[e307a944e0be0610ff5296e0abe4ad31a6e70daa]
eeprom:[A335PBGL00A21741GPB30158]
model:[TI_AM335x_PocketBeagle]
dogtag:[BeagleBoard.org Debian Image 2018-03-05]
bootloader:[microSD]:[/dev/mmcblk0]:[U-Boot 2018.01-00002-ge9ff418fb8]:[location: dd MBR]
kernel:[4.9.82-ti-r102]
nodejs:[v6.13.0]
uboot_overlay_options:[enable_uboot_overlays=1]
uboot_overlay_options:[enable_uboot_cape_universal=1]
pkg:[bb-cape-overlays]:[4.4.20180305.0-0rcnee0~stretch+20180305]
pkg:[bb-wl18xx-firmware]:[1.20170829-0rcnee2~stretch+20180104]
pkg:[firmware-ti-connectivity]:[20170823-1rcnee0~stretch+20170830]
groups:[debian : debian adm kmem dialout cdrom floppy audio dip video plugdev users systemd-journal i2c bluetooth netdev cloud9ide gpio pwm eqep admin spi tisdk weston-launch xenomai]
cmdline:[console=ttyO0,115200n8 root=/dev/mmcblk0p1 ro rootfstype=ext4 rootwait coherent_pool=1M net.ifnames=0 quiet]
dmesg | grep pinctrl-single
[    1.424571] pinctrl-single 44e10800.pinmux: 142 pins at pa f9e10800 size 568
dmesg | grep gpio-of-helper
[    1.433009] gpio-of-helper ocp:cape-universal: ready
END
```

# User button
```sh
watch -n0 cat /sys/class/gpio/gpio45/value
```

# Potentiometer
```sh
watch -n0 cat /sys/bus/iio/devices/iio\:device0/in_voltage0_raw
```

# SPI 7-segment LEDs
```sh
echo -ne "\x40\x00\x00" | sudo tee /dev/spidev2.1 | xxd
echo -ne "\x40\x01\x00" | sudo tee /dev/spidev2.1 | xxd
echo -ne "\x40\x12\xc0" | sudo tee /dev/spidev2.1 | xxd
echo -ne "\x40\x13\xc0" | sudo tee /dev/spidev2.1 | xxd
```

# I2C accelerometer (mma8452)
```sh
sudo mkdir -p /sys/kernel/config/device-tree/overlays/accel
sudo dtc -W no-unit_address_vs_reg -@ -o /sys/kernel/config/device-tree/overlays/accel/dtbo <<EOF
/dts-v1/;
/plugin/;
/ {
  fragment@0 {
    target = <&i2c2>;
    __overlay__ {
      #address-cells = <1>;
      #size-cells = <0>;
      accel@1c {
	compatible = "fsl,mma8452";
        reg = <0x1c>;
      };
    };
  };
};
EOF
sleep 2
cd /sys/bus/iio/devices/iio\:device1
watch -n0 sudo cat in_accel_x_raw in_accel_y_raw in_accel_z_raw 
```

# PRU examples
You'll need to start by enabling the PRU RPROC overlay. In future images, this should not be required and should actually just be part of the default device tree.

```sh
sudo sed -i -e "s/#?uboot_overlay_pru=.*RPROC.*$/uboot_overlay_pru=\/lib\/firmware\/AM335X-PRU-RPROC-4-9-TI-00A0.dtbo/;" /boot/uEnv.txt
sudo shutdown -r now
```

After rebooting, the version will look like the below.

```
debian@beaglebone:/var/lib/cloud9$ sudo /opt/scripts/tools/version.sh
[sudo] password for debian:
git:/opt/scripts/:[e307a944e0be0610ff5296e0abe4ad31a6e70daa]
eeprom:[A335PBGL00A21741GPB30158]
model:[TI_AM335x_PocketBeagle]
dogtag:[BeagleBoard.org Debian Image 2018-03-05]
bootloader:[microSD]:[/dev/mmcblk0]:[U-Boot 2018.01-00002-ge9ff418fb8]:[location: dd MBR]
kernel:[4.9.82-ti-r102]
nodejs:[v6.13.0]
uboot_overlay_options:[enable_uboot_overlays=1]
uboot_overlay_options:[uboot_overlay_pru=/lib/firmware/AM335X-PRU-RPROC-4-9-TI-00A0.dtbo]
uboot_overlay_options:[enable_uboot_cape_universal=1]
pkg:[bb-cape-overlays]:[4.4.20180305.0-0rcnee0~stretch+20180305]
pkg:[bb-wl18xx-firmware]:[1.20170829-0rcnee2~stretch+20180104]
pkg:[firmware-ti-connectivity]:[20170823-1rcnee0~stretch+20170830]
groups:[debian : debian adm kmem dialout cdrom floppy audio dip video plugdev users systemd-journal i2c bluetooth netdev cloud9ide gpio pwm eqep admin spi tisdk weston-launch xenomai]
cmdline:[console=ttyO0,115200n8 root=/dev/mmcblk0p1 ro rootfstype=ext4 rootwait coherent_pool=1M net.ifnames=0 quiet]
dmesg | grep pinctrl-single
[    1.425322] pinctrl-single 44e10800.pinmux: 142 pins at pa f9e10800 size 568
dmesg | grep gpio-of-helper
[    1.434029] gpio-of-helper ocp:cape-universal: ready
```

Then you can try to run the PRU examples.

```sh
cd /var/lib/cloud9/examples/extras/pru
make TARGET=hello-pru PRUN=pru0
make TARGET=hello-pru PRUN=pru1
```