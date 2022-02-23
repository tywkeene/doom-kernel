#!/bin/bash
qemu-system-arm -m 1024 -smp 4 --machine raspi2b -cpu cortex-a7 -serial stdio -kernel doomos.elf
