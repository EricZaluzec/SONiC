
ifneq ($(KERNELRELEASE),)
obj-m:=accton_as7712_32x_fan.o accton_as7712_32x_sfp.o leds-accton_as7712_32x.o \
       accton_as7712_32x_psu.o accton_i2c_cpld.o ym2651y.o 

else
ifeq (,$(KERNEL_SRC))
$(error KERNEL_SRC is not defined)
else
KERNELDIR:=$(KERNEL_SRC)
endif
PWD:=$(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR)  M=$(PWD) modules
clean:
	rm -rf *.o *.mod.c *.mod.o *.ko .*cmd .tmp_versions Module.markers Module.symvers modules.order
endif
