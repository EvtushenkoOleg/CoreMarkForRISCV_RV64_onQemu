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
2. Для сборки FreeRTOS:  
- Скачивание и разарихивирование архива [FreeRTOS 202112.00](https://www.freertos.org/a00104.html)  
- Копирование следующих директорий в директорию FreeRTOS_RISCV_RV64G:  
+ Source/GCC/RISC-V  
+ License  
+ Demo/Common и Demo/RISC-V-Qemu-virt_GCC  
3. Для сборки бенчмарка Coremark:  
 - Клонировние git-репозитория Coremark  
  ```git clone https://github.com/eembc/coremark.git```  
- Копирование из исходного репозитория в директорию FreeRTOS_RISCV_RV64G/Demo/RISC-V-Qemu-virt_GCC следующих файлов:  
+ core_list_join.c 
+ core_main.c 
+ core_matrix.c 
+ core_state.c 
+ core_util.c 
+ core_portme.c 
+ coremark.h
+ core_portme.h
4. Для сборки qemu
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


***
### Сборка Coremark:
Примечание:
Планировалось оздать Makefile, в котором для сборки используется riscv64-unknown-elf-gcc с флагами для архитектуры RV64G (-march=rv64g -mabi=lp64d -mcmodel=medany) и затем загружать в память вирутальной машины под FreeRTOS на Qemu. Но возникли следующие трудности: т.к. бенчмарк долежн запускать как задача (Task), то не обходима main программа, которая будет создавать задачу. Соответственно, при сборке FreeRTOS линкер по понятным причинам не дает загрузить в память исполняемый файл, т.к. существует основная в которой есть функция main и метка _start. Поэтому было принято решение собирать бенчмарк вместе со сборкой FreeRTOS.
1. Изменение имени главной программы в файле core_main.c с `void main()` на `void coremark_main()` 
2. Измение файла core_portme.c - добавлено считывание значения со счетчика циклов процессора (mcycle) для вычисления в дальнейшем времени работы бенчмарка  
3. Измение файла core_portme.h - т.к. платформа не использует time.h, то #define HAS_TIME_H установлен в 0; т.к. реализация печати во FreeRTOS с помощью printf-stdarg.c не поддерживает вывод вещественных значений, то #define HAS_FLOAT установлен в 0; т.к. используется 64 разрядная система, то ee_ptr_int установлен тип unsigned long long.
4. Исправлен вывод некоторых значений с помощью printf

### Сборка FreeRTOS:
1. Удалён main_blinky.c
2. Добавлен printf-stdarg.c для печати в консоль через UART
3. Изменены:
+ main.c - создана функция vTaskCoreMark, в которой производися вызов бенчмарка (coremark_main() ) и установка задержки в 5 секунд с помощью vTaskDelayUntil
+ Makefile добавлен к переменной PATH путь к `riscv64-unknown-elf-gcc`; изменена архитектура `-march=rv64g -mabi=lp64d -mcmodel=medany`; добавлены в сборку файлы(*.c) бенчмарка с флагами (`-DPERFORMANCE_RUN=1 -DITERATIONS=10000`)
4. Из директории FreeRTOS_RISCV_RV64G, либо из корневой директории запускаем сборку FreeRTOS для RV64G
  ```make```  

### Запуск Coremark под FreeRTOS для RISC-V (RV64G) на Qemu
Вызов Qemu с созданной FreeRTOS может осуществляться, либо из директории FreeRTOS_RISCV_RV64G, либо из корневой директории:
  ```make qemu```  
Данный вызов выполняет следующее:
  ```qemu-system-riscv64 -nographic -machine virt -bios none -smp 2 -kernel ./build/RTOSDemo.elf```  
Задаються параметры 
* -nographic - вызов вывода графического вывода и использование для вывода в консоль I/O портов
* -machine virt - выбор виртуальной машины
* -bios none - вызов без загрузки биоса
* -smp 2 - количество процессоров (2)
* -kernel ./build/RTOSDemo.elf - ууказание собранного FreeRTOS

### Вывод в консоль
![1](https://raw.githubusercontent.com/EvtushenkoOleg/pict/main/logStart1.png)
![2](https://raw.githubusercontent.com/EvtushenkoOleg/pict/main/logStart2.png)
