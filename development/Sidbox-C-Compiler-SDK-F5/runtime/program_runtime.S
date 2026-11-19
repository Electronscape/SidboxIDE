    .syntax unified
    .thumb
    .section .text.sidc_vectors,"ax",%progbits
    .p2align 2
    .global sidc_vectors
    .type sidc_vectors,%function
    .thumb_func
sidc_vectors:
    nop.w                       /* Patched to B.W main by the compiler */
    b.w sidbox_message
    b.w sidbox_ticks
    b.w sidbox_buttons
    .size sidc_vectors, .-sidc_vectors
