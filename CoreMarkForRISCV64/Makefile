export PATH := /opt/riscv/bin:$(PATH)
CROSS   = riscv64-unknown-elf-
CC      = $(CROSS)gcc

CFLAGS  = -O2\
	-march=rv64g -mabi=lp64d -mcmodel=medany 


SRCS = core_list_join.c core_main.c core_matrix.c core_state.c core_util.c core_portme.c
#SRCSO = $(SRCS:%.c=%.o)
#LIB = coremarkshared.so
OUT = coremark.out
FLAGSCM = -DPERFORMANCE_RUN=1 -DITERATIONS=10
FLAGMAP = -Xlinker -r 
all:
	$(CC) $(CFLAGS) $(FLAGMAP) -o $(OUT) $(SRCS) $(FLAGSCM)

clean:
	rm -rf $(OUT)

 #riscv64-unknown-elf-gcc -Os -pie -nostdlib -mcmodel=medany -fPIC test.c -o test.so > a.txt
 #$(CC) $(CFLAGS) -Xlinker -r -Xlinker -Map=coremark.map  -o $(OUT) $(SRCS) $(FLAGSCM)
 #cc -Kpic -G -M mapfile -h libidx5.so.1 idx5.c -o stublib/libidx5.so.1
# cc main.c -L stublib -R '$ORIGIN/lib' -lidx5 -lc
#$ LD_PRELOAD=stublib/libidx5.so.1 ./a.out
#$ cc -Kpic -G -M mapfile -h libidx5.so.1 idx5.c -o stublib/libidx5.so.1 -zstub

#$(CC) -mcmodel=medany -fPIC $(FLAGMAP) $(SRCS) $(FLAGSCM) -o coremark.so -zstub
#LD_PRELOAD=coremark.so ./coremark.out
#$(CC) -M coremark.map -h coremark.so $(SRCS) -o coremark.so

#orginal

