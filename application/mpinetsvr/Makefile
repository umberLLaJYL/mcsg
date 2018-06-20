obj := $(patsubst %.c,%.o,$(wildcard *.c))

mpinetsvr : $(obj)
	arm-none-linux-gnueabi-gcc -o mpinetsvr $(obj)