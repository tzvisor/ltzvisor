OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH("arm")

ENTRY(_reset_handler)

phy_offset  = 0x3C000000;


SECTIONS
{
	. = phy_offset;
	_code_begin = .;

	.text : {
		*(.text)
	}
	. = ALIGN(0x1000);

	.data : {
		*(.data)
	}
	. = ALIGN(0x1000);

	.rodata : {
		*(.rodata)
	}
	. = ALIGN(0x1000);

	_SW_BSS_START = .;
	.bss : {
		*(.bss) 
		*(COMMON)
	}
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
	}  
	_SW_CODE_END = .;
 }
