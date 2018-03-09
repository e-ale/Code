obj-m += lab1.o lab2_1.o lab2_2.o

export KROOT=/lib/modules/$(shell uname -r)/build

all:  modules

modules modules_install clean::
	@$(MAKE) -C $(KROOT) M=$(shell pwd) $@

clean::
	rm -rf   Module.symvers modules.order
