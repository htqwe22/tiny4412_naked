OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
/*ENTRY(main) */
SECTIONS
{
/*. = 0x02023400;*/
. = 0x02030000;
.text : { *(.text) }
.data : { *(.data) }
bss_start = .;
.bss  : { *(.bss) }
bss_end = .;
}
