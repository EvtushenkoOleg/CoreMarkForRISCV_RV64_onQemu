OUTPUT_ARCH( "riscv" )
ENTRY( _start )

MEMORY
{
	/* Fake ROM area */
	rom (rxa) : ORIGIN = 0x80000000, LENGTH = 512K
	ram (wxa) : ORIGIN = 0x80080000, LENGTH = 1024K
	myram (wxa) : ORIGIN = 0x800a0000, LENGTH = 150K
}

SECTIONS
{
	.init :
	{
		_text = .;
		KEEP (*(SORT_NONE(.init)))
	} >rom AT>rom
	
	.text :
	{
		*(.text.unlikely .text.unlikely.*)
		*(.text.startup .text.startup.*)
		*(.text .text.*)
		*(.gnu.linkonce.t.*)
		
	} >rom AT>rom
	
	.fini :
	{
		KEEP (*(SORT_NONE(.fini)))
		_etext = .;
	} >rom AT>rom

	.rodata.align :
	{
		. = ALIGN(8);
		_rodata = .;
	} >rom AT>rom

	.rodata.start :
	{
		_rodata_lma = LOADADDR(.rodata.start);
	} >rom AT>rom

	.rodata :
	{
		*(.rdata)
		*(.rodata .rodata.*)
		*(.gnu.linkonce.r.*)

		. = ALIGN(8);
		_erodata = .;
	} >rom AT>rom

	.data.align :
	{
		. = ALIGN(8);
		_data = .;
	} >ram AT>rom

	.data.start :
	{
		_data_lma = LOADADDR(.data.start);
	} >ram AT>rom

	.data :
	{
		
		*(.data .data.*)
		*(.gnu.linkonce.d.*)
		. = ALIGN(8);
		PROVIDE( __global_pointer$ = . + 0x80000 );
		*(.sdata .sdata.*)
		*(.sdata2 .sdata2.*)
		*(.gnu.linkonce.s.*)
		. = ALIGN(8);
		*(.srodata.cst16)
		*(.srodata.cst8)
		*(.srodata.cst4)
		*(.srodata.cst2)
		*(.srodata .srodata.*)
		
		. = ALIGN(8);
		_edata = .;
	} >ram AT>rom
	

	.bss.align :
	{
		. = ALIGN(8);
		_bss = .;
	} >ram AT>rom

	.bss.start :
	{
		_bss_lma = LOADADDR(.bss.start);
	} >ram AT>rom

	.bss :
	{
		*(.sbss*)
		*(.gnu.linkonce.sb.*)
		*(.bss .bss.*)
		*(.gnu.linkonce.b.*)
		*(COMMON)

		. = ALIGN(8);
		_ebss = .;
	} >ram AT>rom

	. = ALIGN(16);
	
	. = 0x800a0000 ;

	/*-----------------------NOT WORK----------------------------*/
	/*.coremark :
	{
		coremark.out(.*)
	} >myram AT>rom
	
	coremark.data : {coremark.out(.data)} >myram AT>rom
	coremark.bss : {coremark.out(.bss)} >myram AT>rom
	coremark.text : {coremark.out(.text)} >myram AT>rom
	
	.coremark :
	{
		KEEP(*coremark.out(.*))
	}
	*/
	/*----------------------------------------------------------*/
	. = ALIGN(8);
	
	_end = .;
	
	.stack :
	{
		. = ALIGN(16);
		. += __stack_size;
		_stack_top = .;
	} >ram AT>ram
}
