SECTIONS
{
  . = 0x80f5c400;
  .text : { *(.text) }
  .data : { *(.data) }
  .bss : { *(.bss) }
  /DISCARD/ : { *(.comment) *(.gnu*) }
}
