#!/bin/bash
qemu-system-arm -m 1024 -smp 4 -M raspi2 -serial stdio -kernel doomos.elf
