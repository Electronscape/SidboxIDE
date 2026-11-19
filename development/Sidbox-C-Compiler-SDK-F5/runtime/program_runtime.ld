ENTRY(sidc_vectors)
SECTIONS {
    . = 0;
    .text : {
        KEEP(*(.text.sidc_vectors))
        *(.text*)
        *(.rodata*)
        . = ALIGN(4);
    }
    .unexpected : { *(.data*) *(.bss*) *(COMMON) *(.got*) }
    /DISCARD/ : { *(.ARM.exidx*) *(.ARM.extab*) *(.note*) *(.comment) }
}
ASSERT(SIZEOF(.unexpected) == 0, "Generated programs need a position-independent runtime")
