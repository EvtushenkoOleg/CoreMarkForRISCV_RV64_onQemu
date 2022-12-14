export PATH := /opt/riscv/bin:$(PATH)

CROSS   = riscv64-unknown-elf-
CC      = $(CROSS)gcc
OBJCOPY = $(CROSS)objcopy
ARCH    = $(CROSS)ar

BUILD_DIR       = build
RTOS_SOURCE_DIR = $(abspath ../../Source)
DEMO_SOURCE_DIR = $(abspath ../Common/Minimal)
#FOR COREMARK	
FLAGSCM = -DPERFORMANCE_RUN=1 -DITERATIONS=10000
SRCS_COREMARK = core_main.c core_list_join.c core_matrix.c core_state.c core_util.c core_portme.c 

CPPFLAGS = \
	-D__riscv_float_abi_soft \
	-DportasmHANDLE_INTERRUPT=handle_trap \
	-I . -I ../Common/include \
	-I $(RTOS_SOURCE_DIR)/include \
	-I $(RTOS_SOURCE_DIR)/portable/GCC/RISC-V \
	-I $(RTOS_SOURCE_DIR)/portable/GCC/RISC-V/chip_specific_extensions/RV32I_CLINT_no_extensions
CFLAGS  = -march=rv64g -mabi=lp64d -mcmodel=medany \
	-Wall \
	-fmessage-length=0 \
	-ffunction-sections \
	-fdata-sections \
	-fno-builtin-printf\
	$(FLAGSCM)
LDFLAGS = -nostartfiles -Tfake_rom.lds \
	-march=rv64g -mabi=lp64d -mcmodel=medany \
	-Xlinker --gc-sections \
	-Xlinker --defsym=__stack_size=500 \
	-Xlinker -Map=RTOSDemo.map\
	


ifeq ($(DEBUG), 1)
    CFLAGS += -O3 -ggdb3
else
    CFLAGS += -O2
endif

SRCS =  main.c riscv-virt.c ns16550.c printf-stdarg.c $(SRCS_COREMARK)\
	$(DEMO_SOURCE_DIR)/EventGroupsDemo.c \
	$(DEMO_SOURCE_DIR)/TaskNotify.c \
	$(DEMO_SOURCE_DIR)/TimerDemo.c \
	$(DEMO_SOURCE_DIR)/blocktim.c \
	$(DEMO_SOURCE_DIR)/dynamic.c \
	$(DEMO_SOURCE_DIR)/recmutex.c \
	$(RTOS_SOURCE_DIR)/event_groups.c \
	$(RTOS_SOURCE_DIR)/list.c \
	$(RTOS_SOURCE_DIR)/queue.c \
	$(RTOS_SOURCE_DIR)/stream_buffer.c \
	$(RTOS_SOURCE_DIR)/tasks.c \
	$(RTOS_SOURCE_DIR)/timers.c \
	$(RTOS_SOURCE_DIR)/portable/MemMang/heap_4.c \
	$(RTOS_SOURCE_DIR)/portable/GCC/RISC-V/port.c

ASMS = start.S vector.S\
	$(RTOS_SOURCE_DIR)/portable/GCC/RISC-V/portASM.S

OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o) $(ASMS:%.S=$(BUILD_DIR)/%.o)
DEPS = $(SRCS:%.c=$(BUILD_DIR)/%.d) $(ASMS:%.S=$(BUILD_DIR)/%.d)


$(BUILD_DIR)/RTOSDemo.elf: $(OBJS) fake_rom.lds Makefile
	$(CC) $(LDFLAGS) $(OBJS) -o $@
	

$(BUILD_DIR)/%.o: %.c Makefile
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

$(BUILD_DIR)/%.o: %.S Makefile
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

qemu: $(BUILD_DIR)/RTOSDemo.elf
	qemu-system-riscv64 -nographic -machine virt -bios none -smp 2 -kernel ./build/RTOSDemo.elf

clean:
	rm -rf $(BUILD_DIR)

-include $(DEPS)
