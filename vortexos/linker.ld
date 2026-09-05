ENTRY(_start)

SECTIONS
{
    . = 1M; /* GRUB prefiere cargar el sistema en el primer Megabyte */

    .text : { *(.multiboot) *(.text) }
    .rodata : { *(.rodata) }
    .data : { *(.data) }
    .bss  : { *(.bss) }
}
