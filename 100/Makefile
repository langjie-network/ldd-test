
KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD       := $(shell pwd)

obj-m	:=mychardev.o

all:
	make -C $(KERNELDIR) M=$(PWD) modules

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions *.mod *.order *.symvers

