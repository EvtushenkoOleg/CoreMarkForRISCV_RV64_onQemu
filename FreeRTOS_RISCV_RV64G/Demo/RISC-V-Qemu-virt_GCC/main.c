
#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>

#include "riscv-virt.h"
#include "ns16550.h"
void vApplicationMallocFailedHook( void );
void vApplicationIdleHook( void );
void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName );
void vApplicationTickHook( void );
#define MYRAMADDR	0x0000000080155610UL

void startCoreMark(){
	int retCoreMark = 0;
	int (*coremark)() = MYRAMADDR;
	retCoreMark = coremark();
	if(retCoreMark)
		vSendString( "CoreMark is done! :D" );
	else
		vSendString( "Error: CoreMark is not done! :(" );
}

int main( void )
{
	vSendString( "Hello FreeRTOS!" );
	
	/*unsigned long long * ptrRamAddr = MYRAMADDR;
	unsigned long long buf =0;
	FILE * file;
	vSendString( "Open coreMark.out!" );
	if((file = fopen("coremark.out", "r"))!=NULL) {
		vSendString( "CoreMark.out is open!" );
		while(fscanf(file, "%llu", &buf) != EOF){

		vSendString( "1");

		*ptrRamAddr++ = buf;
		}
	fclose(file);
	vSendString( "2");
	const TickType_t xDelay = 1000/portTICK_PERIOD_MS; //delay 5 second
	BaseType_t xReturned; 
	xTaskHandle xHandle = NULL;
	
	xReturned = xTaskCreate( startCoreMark, "CoreMark", configMINIMAL_STACK_SIZE * 2U, NULL, NULL, xHandle);
	if(xReturned == pdPASS ){
		vSendString( "Start CoreMark!" );
		vTaskDelay(xDelay); //start task Delay with 5 second
	}
	else
		vSendString( "Error: CoreMark not start" );
	
	vTaskStartScheduler();
	}
	vSendString( "ERROR: CoreMark.out is not open!" );*/
	return 0;
}

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