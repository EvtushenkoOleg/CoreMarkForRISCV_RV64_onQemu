# CoreMarkForRISCV_RV64_onQemu
***
### Пререквизиты:
1. Собран riscv-gcc для архитектуры RV64G:
- Установка необходимых для сборки пакетов
```$ sudo apt-get install autoconf automake autotools-dev curl python3 libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev libexpat-dev```
- Клонирование git-репозитория riscv-gnu-toolchain
```git clone https://github.com/riscv-collab/riscv-gnu-toolchain.git```
- Задание конфигурации для сборки 
```./configure --prefix=/opt/riscv --with-arch=rv64G --with-abi=lp64d -mcmodel=medany```
- Выполнение сборки
```make```
2. Для сборки бенчмарка Coremark:
 - Клонировние git-репозитория Coremark
```git clone https://github.com/eembc/coremark.git```
- Копирование из исходного репозитория в директорию CoreMarkForRISCV64 следующих файлов: 
+ core_list_join.c 
+ core_main.c 
+ core_matrix.c 
+ core_state.c 
+ core_util.c 
+ core_portme.c 
+ coremark.h
+ core_portme.h
3. Для сборки qemu
- Установка необходимых для сборки пакетов
```sudo apt install autoconf automake autotools-dev curl libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev libexpat-dev git```
- Клонирование git-репозитория Qemu
```git clone https://github.com/qemu/qemu```
- Задание конфигурации для сборки
```git checkout v5.0.0```
```./configure --target-list=riscv64-softmmu --prefix=$INSTALL_DIR```
- Выполнение сборки
```make -j $(nproc)```
```sudo make install```
4. Для сборки FreeRTOS:
- Скачивание и разарихивирование архива [FreeRTOS 202112.00](https://www.freertos.org/a00104.html)
- Копирование следующих директорий в директорию FreeRTOS_RISCV_RV64G:
+ Source/GCC/RISC-V
+ License
+ Demo/Common и Demo/RISC-V-Qemu-virt_GCC


***
### Сборка Coremark:
1. Создан Makefile, в котором для сборки используется riscv64-unknown-elf-gcc с флагами для архитектуры RV64G (-march=rv64g -mabi=lp64d -mcmodel=medany). Так запускается на виртуальной машине Qemu, то количество итераций выбрано 10 (-DITERATIONS=10)
2. Из директории CoreMarkForRISCV64 запускаем сборку бенчмарка для RV64G
```make```

### Сборка FreeRTOS:
1. Удален main_blinky.c
2. Добавлен printf-stdarg.c для печати в консоль через UART
3. Изменены:
+ main.c (Создан vTaskCoreMark)
+ ~~fake_rom.lds (Добавлена загрузка coremark.out в память)~~
+ Makefile (Изменена архитектура -march=rv64g -mabi=lp64d -mcmodel=medany)
4. Из директории FreeRTOS_RISCV_RV64G запускаем сборку FreeRTOS для RV64G
```make```

### Запуск Coremark под FreeRTOS для RISC-V (RV64G) на Qemu
Вызываем qemu-system-riscv64, передевая в парамметры файл собранной FreeRTOS:
```qemu-system-riscv64 -nographic -machine virt -bios none -kernel ./build/RTOSDemo.elf```