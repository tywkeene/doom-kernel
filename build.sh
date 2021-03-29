#!/bin/bash

arm-none-eabi-gcc -mcpu=cortex-a7 -fpic -ffreestanding -I./include/ -std=gnu99 -c kernel/kernel.c -o kernel.o -O2 -Wall -Wextra
arm-none-eabi-gcc -mcpu=cortex-a7 -fpic -ffreestanding -I./include/ -std=gnu99 -c kernel/mmio.c -o mmio.o -O2 -Wall -Wextra
arm-none-eabi-gcc -mcpu=cortex-a7 -fpic -ffreestanding -I./include/ -std=gnu99 -c kernel/uart.c -o uart.o -O2 -Wall -Wextra
arm-none-eabi-gcc -mcpu=cortex-a7 -fpic -ffreestanding -I./include/ -std=gnu99 -c kernel/printk.c -o printk.o -O2 -Wall -Wextra

arm-none-eabi-gcc -mcpu=cortex-a7 -fpic -ffreestanding -c asm/boot.s -o boot.o
arm-none-eabi-gcc -mcpu=cortex-a7 -fpic -ffreestanding -c asm/utils.s -o utils.o

arm-none-eabi-gcc -T linker.ld -ffreestanding -O2 -nostdlib -o doomos.elf *.o -lgcc
