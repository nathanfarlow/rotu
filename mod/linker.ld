SECTIONS
{
  . = 0x801cbcbc;
  .text : { *(.text) }
  .data : { *(.data) }
  .bss : { *(.bss) }
  /DISCARD/ : { *(.comment) *(.gnu*) }
}
