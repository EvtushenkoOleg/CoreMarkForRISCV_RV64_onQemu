PATHMAKE = FreeRTOS_RISCV_RV64G/Demo/RISC-V-Qemu-virt_GCC/

all:
	$(MAKE) -C $(PATHMAKE)
	
qemu:
	$(MAKE) -C $(PATHMAKE) $@

clean:
	$(MAKE) -C $(PATHMAKE) $@
