# CoreMarkForRISCV_RV64_onQemu
***
###Пререквизиты:
1. Собрать riscv-gcc для архитектуры RV64G:
Установить необходимые для сборки пакеты
$ sudo apt-get install autoconf automake autotools-dev curl python3 libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev libexpat-dev>
Склонировать git-репозиторий riscv-gnu-toolchain
<git clone https://github.com/riscv-collab/riscv-gnu-toolchain.git>
Задать конфигурацию для сборки 
<./configure --prefix=/opt/riscv --with-arch=rv64G --with-abi=lp64d -mcmodel=medany >
Выполнить сборку
<make>
2. Для сборки бенчмарка Coremark:
Склонировать git-репозиторий Coremark
<git clone https://github.com/eembc/coremark.git>
3. Для сборки qemu
Установить необходимые для сборки пакеты
<sudo apt install autoconf automake autotools-dev curl libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev libexpat-dev git >
Склонировать git-репозиторий qemu
<git clone https://github.com/qemu/qemu>
Задать конфигурацию для сборки
<git checkout v5.0.0
./configure --target-list=riscv64-softmmu --prefix=$INSTALL_DIR>
Выполнить сборку
<make -j $(nproc)
sudo make install>
4. Для сборки FreeRTOS:
Скачать архив FreeRTOS 202112.00 (https://www.freertos.org/a00104.html)
