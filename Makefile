CC	      = arm-none-eabi-gcc
AS 	 	  = arm-none-eabi-gcc
LD	      = arm-none-eabi-gcc

CFLAGS    = -mcpu=cortex-a7 -std=gnu99 -Wall -Wextra -ffreestanding -shared -fpic -I./../include
LDFLAGS   = -shared -nostdlib
AS_FLAGS  = -ffreestanding -mcpu=cortex-a7 -fpic

EMU 	  = qemu-system-arm 
EMU_FLAGS = -m 1024 -M raspi2 -serial stdio

BOOT = $(patsubst %.s,%.o,$(wildcard boot/*.s))
KERNEL = $(patsubst %.c,%.o,$(wildcard kernel/*.c))

KERNEL_OUT = doom-kernel.elf

all: boot kernel doom-kernel

boot: $(BOOT)
	$(AS) -c -o $@ $< $(AS_FLAGS)
kernel: $(KERNEL)
	$(CC) -c -o $@ $< $(CFLAGS)

doom-kernel: boot kernel
	$(LD) -T ./boot/linker.ld $(LDFLAGS) -o $(KERNEL_OUT) $^

run: doom-kernel
	@qemu-system-arm $(EMU_FLAGS) -kernel $(KERNEL_OUT)
	printf "\n"

clean:
	$(RM) $(OBJFILES) $(KERNEL_OUT) *.o kernel/*.o boot/*.o
