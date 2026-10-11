.syntax unified
.cpu cortex-m7
.thumb
.section .text.applet_entry,"ax",%progbits
.global applet_entry
.type applet_entry,%function
.thumb_func
applet_entry:
 bx lr
 .balign 4
 .reloc ., R_ARM_GOT_BREL, heap_size
 .word 0
 .reloc ., R_ARM_GOT_BREL, aaa
 .word 0
 .reloc ., R_ARM_BASE_PREL, _GLOBAL_OFFSET_TABLE_
 .word 0
.size applet_entry, .-applet_entry
.section .bss.spare,"aw",%nobits
.space 7
.comm heap_size,4,4
.comm aaa,8,8
