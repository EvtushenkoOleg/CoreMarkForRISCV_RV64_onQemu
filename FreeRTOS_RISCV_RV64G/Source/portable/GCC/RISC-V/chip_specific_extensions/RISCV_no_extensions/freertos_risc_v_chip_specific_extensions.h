/*
 * FreeRTOS Kernel V10.5.1
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

/*
 * The FreeRTOS kernel's RISC-V port is split between the the code that is
 * common across all currently supported RISC-V chips (implementations of the
 * RISC-V ISA), and code that tailors the port to a specific RISC-V chip:
 *
 * + FreeRTOS\Source\portable\GCC\RISC-V\portASM.S contains the code that
 *   is common to all currently supported RISC-V chips.  There is only one
 *   portASM.S file because the same file is built for all RISC-V target chips.
 *
 * + Header files called freertos_risc_v_chip_specific_extensions.h contain the
 *   code that tailors the FreeRTOS kernel's RISC-V port to a specific RISC-V
 *   chip.  There are multiple freertos_risc_v_chip_specific_extensions.h files
 *   as there are multiple RISC-V chip implementations.
 *
 * !!!NOTE!!!
 * TAKE CARE TO INCLUDE THE CORRECT freertos_risc_v_chip_specific_extensions.h
 * HEADER FILE FOR THE CHIP IN USE.  This is done using the assembler's (not the
 * compiler's!) include path.  For example, if the chip in use includes a core
 * local interrupter (CLINT) and does not include any chip specific register
 * extensions then add the path below to the assembler's include path:
 * FreeRTOS\Source\portable\GCC\RISC-V\chip_specific_extensions\RISCV_MTIME_CLINT_no_extensions
 *
 */


#ifndef __FREERTOS_RISC_V_EXTENSIONS_H__
#define __FREERTOS_RISC_V_EXTENSIONS_H__

#define portasmHAS_SIFIVE_CLINT         1
#define portasmHAS_MTIME                1
#define portasmADDITIONAL_CONTEXT_SIZE  32

.macro portasmSAVE_ADDITIONAL_REGISTERS
    /* No additional registers to save, so this macro does nothing. */
    addi sp, sp, -(portasmADDITIONAL_CONTEXT_SIZE * portWORD_SIZE)
    sw f0, 1 * portWORD_SIZE( sp )
    sw f1, 2 * portWORD_SIZE( sp )
    sw f2, 3 * portWORD_SIZE( sp )
    sw f3, 4 * portWORD_SIZE( sp )
    sw f4, 5 * portWORD_SIZE( sp )
    sw f5, 6 * portWORD_SIZE( sp )
    sw f6, 7 * portWORD_SIZE( sp )
    sw f7, 8 * portWORD_SIZE( sp )
    sw f8, 9 * portWORD_SIZE( sp )
    sw f9, 10 * portWORD_SIZE( sp )
    sw f10, 11 * portWORD_SIZE( sp )
    sw f11, 12 * portWORD_SIZE( sp )
    sw f12, 13 * portWORD_SIZE( sp )
    sw f13, 14 * portWORD_SIZE( sp )
    sw f14, 15 * portWORD_SIZE( sp )
    sw f15, 16 * portWORD_SIZE( sp )
    sw f16, 17 * portWORD_SIZE( sp )
    sw f17, 18 * portWORD_SIZE( sp )
    sw f18, 19 * portWORD_SIZE( sp )
    sw f19, 20 * portWORD_SIZE( sp )
    sw f20, 21 * portWORD_SIZE( sp )
    sw f21, 22 * portWORD_SIZE( sp )
    sw f22, 23 * portWORD_SIZE( sp )
    sw f23, 24 * portWORD_SIZE( sp )
    sw f24, 25 * portWORD_SIZE( sp )
    sw f25, 26 * portWORD_SIZE( sp )
    sw f26, 27 * portWORD_SIZE( sp )
    sw f27, 28 * portWORD_SIZE( sp )
    sw f28, 29 * portWORD_SIZE( sp )
    sw f29, 30 * portWORD_SIZE( sp )
    sw f30, 31 * portWORD_SIZE( sp )
    sw f31, 32 * portWORD_SIZE( sp )   
    
    .endm

.macro portasmRESTORE_ADDITIONAL_REGISTERS
    /* No additional registers to restore, so this macro does nothing. */
    lw f0, 1 * portWORD_SIZE( sp )
    lw f1, 2 * portWORD_SIZE( sp )
    lw f2, 3 * portWORD_SIZE( sp )
    lw f3, 4 * portWORD_SIZE( sp )
    lw f4, 5 * portWORD_SIZE( sp )
    lw f5, 6 * portWORD_SIZE( sp )
    lw f6, 7 * portWORD_SIZE( sp )
    lw f7, 8 * portWORD_SIZE( sp )
    lw f8, 9 * portWORD_SIZE( sp )
    lw f9, 10 * portWORD_SIZE( sp )
    lw f10, 11 * portWORD_SIZE( sp )
    lw f11, 12 * portWORD_SIZE( sp )
    lw f12, 13 * portWORD_SIZE( sp )
    lw f13, 14 * portWORD_SIZE( sp )
    lw f14, 15 * portWORD_SIZE( sp )
    lw f15, 16 * portWORD_SIZE( sp )
    lw f16, 17 * portWORD_SIZE( sp )
    lw f17, 18 * portWORD_SIZE( sp )
    lw f18, 19 * portWORD_SIZE( sp )
    lw f19, 20 * portWORD_SIZE( sp )
    lw f20, 21 * portWORD_SIZE( sp )
    lw f21, 22 * portWORD_SIZE( sp )
    lw f22, 23 * portWORD_SIZE( sp )
    lw f23, 24 * portWORD_SIZE( sp )
    lw f24, 25 * portWORD_SIZE( sp )
    lw f25, 26 * portWORD_SIZE( sp )
    lw f26, 27 * portWORD_SIZE( sp )
    lw f27, 28 * portWORD_SIZE( sp )
    lw f28, 29 * portWORD_SIZE( sp )
    lw f29, 30 * portWORD_SIZE( sp )
    lw f30, 31 * portWORD_SIZE( sp )
    lw f31, 32 * portWORD_SIZE( sp )
    
    addi sp, sp, (portasmADDITIONAL_CONTEXT_SIZE * portWORD_SIZE)
    .endm

#endif /* __FREERTOS_RISC_V_EXTENSIONS_H__ */
