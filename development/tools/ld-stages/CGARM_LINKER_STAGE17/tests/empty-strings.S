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
 .reloc ., R_ARM_REL32, .LC0
 .word -4
 .reloc ., R_ARM_REL32, .LC1
 .word -4
 .reloc ., R_ARM_REL32, .rodata.str1.1
 .word 0
 .reloc ., R_ARM_REL32, .data.ptr
 .word 0
.size applet_entry, .-applet_entry
.section .rodata.str1.1,"aMS",%progbits,1
.LC0: .asciz ""
.LC1: .asciz ""
.section .data.ptr,"aw",%progbits
.reloc ., R_ARM_ABS32, applet_entry
.word 0
