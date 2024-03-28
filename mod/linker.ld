SECTIONS
{
  . = 0x801c6254;
  .text : { *(.text) }
  .data : { *(.data) }
  .bss : { *(.bss) }
  /DISCARD/ : { *(.comment) *(.gnu*) }
}
