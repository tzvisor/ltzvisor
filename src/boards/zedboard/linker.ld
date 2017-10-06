OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH("arm")

ENTRY(_reset_handler)


MEMORY
{
	OCM (rwx): ORIGIN = 0x00000000, LENGTH = 0x00030000 				
	DDR_NS  (rwx)  : ORIGIN = 0x00100000, LENGTH = 0x1BEFFFFF
	DDR_S  (rwx)  : ORIGIN = 0x1C000000, LENGTH = 0x03F00000  	
}


SECTIONS
{
	_code_begin = .;
	
	.startup :{
		__startup_start = .;
			*(.startup)
		__startup_end = .;
	} > DDR_S
	. = ALIGN(0x1000);

	.text : {
		*(.text)
	} > DDR_S
	. = ALIGN(0x1000);

	.data : {
		*(.data)
	} > DDR_S
	. = ALIGN(0x1000);

	.rodata : {
		*(.rodata)
	} > DDR_S
	. = ALIGN(0x1000);

	_SW_BSS_START = .;
	.bss : {
		*(.bss) 
		*(COMMON)
	} > DDR_S
	. = ALIGN(0x1000);
	_bss_size = _SW_BSS_END - _SW_BSS_START;
	_SW_BSS_END = .; 
	
	.heap (NOLOAD) : {
		. = ALIGN(16);
		_heap = .;
		HeapBase = .;
		PROVIDE(_heap_start = .);
		. += 0x2000;
		PROVIDE(_heap_end = .);
		HeapLimit = .;
	}  > DDR_S 
	_SW_CODE_END = .;
 }

