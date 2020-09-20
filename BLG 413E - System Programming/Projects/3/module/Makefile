obj-m := scull.o
all: 
	make -k -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
