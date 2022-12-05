# FreeRTOS internal cmake file. Do not use it in user top-level project

add_library(freertos_kernel_port STATIC
    # RISC-V architecture ports for GCC
    $<$<STREQUAL:${FREERTOS_PORT},GCC_RISC_V>:
        GCC/RISC-V/port.c
        GCC/RISC-V/portASM.S>

    $<$<STREQUAL:${FREERTOS_PORT},GCC_RISC_V_PULPINO_VEGA_RV32M1RM>:
        GCC/RISC-V/port.c
        GCC/RISC-V/portASM.S>

    # RISC-V architecture ports for GCC
    $<$<STREQUAL:${FREERTOS_PORT},GCC_RISC_V>:
        ${CMAKE_CURRENT_LIST_DIR}/GCC/RISC-V
        ${CMAKE_CURRENT_LIST_DIR}/GCC/RISC-V/chip_specific_extensions/RISCV_MTIME_CLINT_no_extensions>

    $<$<STREQUAL:${FREERTOS_PORT},GCC_RISC_V_PULPINO_VEGA_RV32M1RM>:
        ${CMAKE_CURRENT_LIST_DIR}/GCC/RISC-V
        ${CMAKE_CURRENT_LIST_DIR}/GCC/RISC-V/chip_specific_extensions/Pulpino_Vega_RV32M1RM>


target_link_libraries(freertos_kernel_port
    PUBLIC
        $<$<STREQUAL:${FREERTOS_PORT},GCC_RP2040>:pico_base_headers>
        $<$<STREQUAL:${FREERTOS_PORT},GCC_XTENSA_ESP32>:idf::esp32>
    PRIVATE
        freertos_kernel
        "$<$<STREQUAL:${FREERTOS_PORT},GCC_RP2040>:hardware_clocks;hardware_exception>"
        $<$<STREQUAL:${FREERTOS_PORT},MSVC_MINGW>:winmm> # Windows library which implements timers
)
