# doom-kernel
A kernel targeting the ARM Cortex-A7 CPU used by the Raspberry Pi 2 B with the end goal of hosting Doom and only Doom.

## Building

Makefile is broken, use build.sh and run.sh. Requires the ARM GCC cross compiler and qemu to run.
Qemu supports outputting serial output to stdout, so we use UART for `printk()` and get output in the terminal.

this is a pain in the ass to get building right so good luck lol

## Current Goals

I know this probably isn't realistic in any kind of reasonable timeframe but w/e, it's the journey not the desination

- [X] Boot something
- [X] Enable UART
- [X] Hello world
- [ ] Bring up all 4 processors
- [ ] Get all 4 processors to print their own CPUID
- [ ] Enable the FPU and MMU

...

- [ ] Keyboard/gamepad support
- [ ] Audio output
- [ ] Video output

...

- [ ] Run Doom

...infinity

- [ ] Multiplayer/online Doom
