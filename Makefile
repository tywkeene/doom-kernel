CC	      = arm-none-eabi-gcc
AS 	 	  = arm-none-eabi-as
LD	      = arm-none-eabi-ld

CFLAGS    = -mcpu=cortex-a7 -std=gnu99 -Wall -Wextra -ffreestanding -shared -fpic -I./../include
AS_FLAGS  = -ffreestanding -mcpu=cortex-a7 -fpic

ASM  = $(patsubst %.s,%.o,$(wildcard asm/*.s))
KERNEL = $(patsubst %.c,%.o,$(wildcard kernel/*.c))
KERNEL_OUT = doomos.elf

all: doom-kernel

doom-kernel: asm/boot.o kernel/kernel.o $(ASM) $(KERNEL)
	$(LD) -T linker.ld $(LDFLAGS) -o $(KERNEL_OUT) $^

clean:
	$(RM) doom-kernel.elf asm/*.o kernel/*.o *.o
