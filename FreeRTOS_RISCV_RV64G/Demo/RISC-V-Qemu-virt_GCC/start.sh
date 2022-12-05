#!/bin/bash

export PATH=/opt/riscv/bin:$PATH
make clean
make DEBUG=1

qemu-system-riscv64 -machine virt -nographic -bios none -chardev stdio,id=con,mux=on -serial chardev:con -mon chardev=con,mode=readline -kernel ./build/RTOSDemo.axf
