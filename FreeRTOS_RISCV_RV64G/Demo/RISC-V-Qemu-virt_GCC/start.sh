#!/bin/bash

export PATH=/opt/riscv/bin:$PATH
make clean
make DEBUG=1

qemu-system-riscv64 -nographic -machine virt -bios none -kernel ./build/RTOSDemo.elf
