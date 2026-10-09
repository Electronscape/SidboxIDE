/* Only for the host proof test; NOT a replacement for gui.ld. */
ENTRY(applet_entry)
MEMORY {
    APPLET (rwx) : ORIGIN = 0xD0010000, LENGTH = 0x20000
}
SECTIONS {
    . = ORIGIN(APPLET);
    .text : { *(.text*) *(.rodata*) } > APPLET
    .data : { *(.data*) } > APPLET
    .bss (NOLOAD) : { *(.bss*) *(COMMON) } > APPLET
}
