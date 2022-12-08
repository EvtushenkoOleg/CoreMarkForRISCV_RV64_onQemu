/*
 * FreeRTOS V202211.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
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

/* FreeRTOS kernel includes. */
#include <FreeRTOS.h>
#include <task.h>

#include <stdio.h>

#include "riscv-virt.h"
#include "ns16550.h"
/* Run a simple demo just prints 'Blink' */
#define mainVECTOR_MODE_DIRECT	1
/* Delay.  The 5s value is converted
to ticks using the pdMS_TO_TICKS() macro. */
#define main_FREQUENCY_MS			pdMS_TO_TICKS( 25000 )
//Address coremark.out(main)
#define MYRAMADDR	0x800a0b54UL

extern void freertos_risc_v_trap_handler( void );
extern void freertos_vector_table( void );

void vApplicationMallocFailedHook( void );
void vApplicationIdleHook( void );
void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName );
void vApplicationTickHook( void );

void vTaskTest( void *pvParameters )
{
	/* Remove compiler warning about unused parameter. */
	( void ) pvParameters;
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount ();
	for(;;){
		vSendString( "In TaskTest" );
		vTaskDelayUntil( &xLastWakeTime, main_FREQUENCY_MS );
	
	}
}

void vTaskCoreMark(void *pvParameters){
	( void ) pvParameters;
	vSendString( "in Funct startCoremark" );
	int retCoreMark = 1;
	int (*coremark)(void) = MYRAMADDR;
	for(;;){
		retCoreMark = coremark();
		if(!retCoreMark)
			vSendString( "CoreMark is done! :D" );
		else
			vSendString( "Error: CoreMark is not done! :(" );
	}
}

/*-----------------------------------------------------------*/

int main( void )
{
	int ret;
	printf("PRINTF WORK? ooh yee \n");
	// trap handler initialization
		#if( mainVECTOR_MODE_DIRECT == 1 )
	{
		__asm__ volatile( "csrw mtvec, %0" :: "r"( freertos_risc_v_trap_handler ) );
	}
	#else
	{
		__asm__ volatile( "csrw mtvec, %0" :: "r"( ( uintptr_t )freertos_vector_table | 0x1 ) );
	}
	#endif

	vSendString( "Hello FreeRTOS!" );
	xTaskHandle xHandle = NULL;
	BaseType_t xReturned; 
	//xTaskCreate( vTaskTest, "TaskTest", configMINIMAL_STACK_SIZE * 2U, NULL,
	//				1, &xHandle);
					
	xReturned = xTaskCreate( vTaskCoreMark, "Coremark", configMINIMAL_STACK_SIZE * 2U, NULL,
					1, &xHandle);
					
	if(xReturned == pdPASS ){
		vSendString( "Task Coremark Created" );
		vSendString( "vTaskStartScheduler start" );
		vTaskStartScheduler();
		vSendString( "back to main" );
		vTaskStartScheduler();
	}
	else
		vSendString( "Error: Task Coremark not Created" );
	
	
	return 0;
}

/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook( void )
{
	/* vApplicationMallocFailedHook() will only be called if
	configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
	function that will get called if a call to pvPortMalloc() fails.
	pvPortMalloc() is called internally by the kernel whenever a task, queue,
	timer or semaphore is created.  It is also called by various parts of the
	demo application.  If heap_1.c or heap_2.c are used, then the size of the
	heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
	FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
	to query the size of free heap space that remains (although it does not
	provide information on how the remaining heap might be fragmented). */
	taskDISABLE_INTERRUPTS();
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
	/* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
	to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
	task.  It is essential that code added to this hook function never attempts
	to block in any way (for example, call xQueueReceive() with a block time
	specified, or call vTaskDelay()).  If the application makes use of the
	vTaskDelete() API function (as this demo application does) then it is also
	important that vApplicationIdleHook() is permitted to return to its calling
	function, because it is the responsibility of the idle task to clean up
	memory allocated by the kernel to any task that has since been deleted. */
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
	( void ) pcTaskName;
	( void ) pxTask;

	/* Run time stack overflow checking is performed if
	configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	function is called if a stack overflow is detected. */
	taskDISABLE_INTERRUPTS();
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
}
/*-----------------------------------------------------------*/

void vAssertCalled( void )
{
volatile uint32_t ulSetTo1ToExitFunction = 0;

	taskDISABLE_INTERRUPTS();
	while( ulSetTo1ToExitFunction != 1 )
	{
		__asm volatile( "NOP" );
	}
}
