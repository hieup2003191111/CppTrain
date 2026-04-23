obj-m += led.o

KDIR = /home/hieu/beagleboneblack/kernelbuildscripts/KERNEL

CROSS_COMPILE = /home/hieu/beagleboneblack/gcc-linaro-6.5.0-2018.12-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-

all:
	make ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) -C $(KDIR) M=$(PWD) modules
clean:
	make ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) -C $(KDIR) M=$(PWD) clean