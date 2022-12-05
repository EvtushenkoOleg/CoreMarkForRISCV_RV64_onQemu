CROSS   = riscv64-unknown-elf-
CC      = $(CROSS)gcc

CFLAGS  = -O2\
	-march=rv64g -mabi=lp64d -mcmodel=medany 


SRCS = core_list_join.c core_main.c core_matrix.c core_state.c core_util.c core_portme.c
OUT = coremark.out
FLAGSCM = -DPERFORMANCE_RUN=1 -DITERATIONS=1000

all:
	$(CC) $(CFLAGS) -o $(OUT) $(SRCS) $(FLAGSCM)

clean:
	rm -rf $(OUT)

