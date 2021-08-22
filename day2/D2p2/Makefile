obj-m:=D2p2.o
CROSS_COMPILE_KDIR=/lib/modules/5.10.52-v7l+/build/
all:
	make -C $(CROSS_COMPILE_KDIR) M=$(PWD) modules
clean:
	make -C $(CROSS_COMPILE_KDIR) M=$(PWD) clean
