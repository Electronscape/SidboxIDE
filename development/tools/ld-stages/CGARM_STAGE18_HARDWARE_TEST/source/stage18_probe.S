	.text
	.syntax unified
	.eabi_attribute	67, "2.09"	@ Tag_conformance
	.cpu	cortex-m7
	.eabi_attribute	6, 13	@ Tag_CPU_arch
	.eabi_attribute	7, 77	@ Tag_CPU_arch_profile
	.eabi_attribute	8, 0	@ Tag_ARM_ISA_use
	.eabi_attribute	9, 2	@ Tag_THUMB_ISA_use
	.fpu	fpv5-d16
	.eabi_attribute	36, 1	@ Tag_FP_HP_extension
	.eabi_attribute	34, 1	@ Tag_CPU_unaligned_access
	.eabi_attribute	15, 1	@ Tag_ABI_PCS_RW_data
	.eabi_attribute	16, 1	@ Tag_ABI_PCS_RO_data
	.eabi_attribute	17, 2	@ Tag_ABI_PCS_GOT_use
	.eabi_attribute	20, 1	@ Tag_ABI_FP_denormal
	.eabi_attribute	21, 0	@ Tag_ABI_FP_exceptions
	.eabi_attribute	23, 3	@ Tag_ABI_FP_number_model
	.eabi_attribute	24, 1	@ Tag_ABI_align_needed
	.eabi_attribute	25, 1	@ Tag_ABI_align_preserved
	.eabi_attribute	38, 1	@ Tag_ABI_FP_16bit_format
	.eabi_attribute	18, 4	@ Tag_ABI_PCS_wchar_t
	.eabi_attribute	26, 2	@ Tag_ABI_enum_size
	.eabi_attribute	14, 0	@ Tag_ABI_PCS_R9_use
	.file	"stage18_probe.c"
	.section	.text.applet_entry,"ax",%progbits
	.globl	applet_entry                    @ -- Begin function applet_entry
	.p2align	2
	.type	applet_entry,%function
	.code	16                              @ @applet_entry
	.thumb_func
applet_entry:
@ %bb.0:
	ldr	r0, .LCPI0_0
.LPC0_0:
	add	r0, pc
	ldr	r1, [r0]
	ldr	r2, .LCPI0_1
.LPC0_1:
	add	r2, pc
	cmp	r1, r2
	itt	ne
	mvnne	r0, #1800
	bxne	lr
.LBB0_1:
	push	{r4, r6, r7, lr}
	add	r7, sp, #8
	ldr	r0, [r0]
	movw	r1, #65518
	movt	r1, #6336
	ldr	r0, [r0]
	cmp	r0, r1
	movw	r0, #63731
	movt	r0, #65535
	bne	.LBB0_5
@ %bb.2:
	ldr	r4, .LCPI0_2
.LPC0_2:
	add	r4, pc
	ldr	r1, [r4]
	cmp	r1, #0
	itt	ne
	addne	r0, #2
	popne	{r4, r6, r7, pc}
.LBB0_3:
	ldr	r1, .LCPI0_3
	add.w	r12, r0, #1
.LPC0_3:
	add	r1, pc
	ldr	r3, [r1]
	cbz	r3, .LBB0_6
.LBB0_4:
	mov	r0, r12
	pop	{r4, r6, r7, pc}
.LBB0_5:
	adds	r0, #3
	pop	{r4, r6, r7, pc}
.LBB0_6:
	movs	r3, #1
.LBB0_7:                                @ =>This Inner Loop Header: Depth=1
	cmp	r3, #8
	beq	.LBB0_10
@ %bb.8:                                @   in Loop: Header=BB0_7 Depth=1
	ldr.w	r2, [r1, r3, lsl #2]
	adds	r3, #1
	cmp	r2, #0
	beq	.LBB0_7
@ %bb.9:
	subs	r2, r3, #2
                                        @ implicit-def: $lr
	cmp	r2, #7
	blo	.LBB0_4
.LBB0_10:
	movs	r2, #24
	movw	r3, #9320
	movt	r2, #47710
	movt	r3, #4951
	str	r2, [r4]
	str	r3, [r1, #28]
	ldr	r4, [r4]
	cmp	r4, r2
	it	ne
	popne	{r4, r6, r7, pc}
.LBB0_11:
	ldr	r1, [r1, #28]
	cmp	r1, r3
	it	eq
	movweq	r0, #1818
	pop	{r4, r6, r7, pc}
	.p2align	2
@ %bb.12:
.LCPI0_0:
	.long	stage18_rebased_pointer-(.LPC0_0+4)
.LCPI0_1:
	.long	stage18_init_word-(.LPC0_1+4)
.LCPI0_2:
	.long	stage18_zero_word-(.LPC0_2+4)
.LCPI0_3:
	.long	stage18_zero_array-(.LPC0_3+4)
.Lfunc_end0:
	.size	applet_entry, .Lfunc_end0-applet_entry
                                        @ -- End function
	.type	stage18_rebased_pointer,%object @ @stage18_rebased_pointer
	.section	.data.stage18_rebased_pointer,"aw",%progbits
	.p2align	2, 0x0
stage18_rebased_pointer:
	.long	stage18_init_word
	.size	stage18_rebased_pointer, 4

	.type	stage18_init_word,%object       @ @stage18_init_word
	.section	.data.stage18_init_word,"aw",%progbits
	.p2align	2, 0x0
stage18_init_word:
	.long	415301614                       @ 0x18c0ffee
	.size	stage18_init_word, 4

	.type	stage18_zero_word,%object       @ @stage18_zero_word
	.section	.bss.stage18_zero_word,"aw",%nobits
	.p2align	2, 0x0
stage18_zero_word:
	.long	0                               @ 0x0
	.size	stage18_zero_word, 4

	.type	stage18_zero_array,%object      @ @stage18_zero_array
	.section	.bss.stage18_zero_array,"aw",%nobits
	.p2align	2, 0x0
stage18_zero_array:
	.zero	32
	.size	stage18_zero_array, 32

	.ident	"clang version 17.0.0 (https://github.com/swiftlang/llvm-project.git 10999b6d034fe318f3d56c83bddb6572593a8bb0)"
	.section	".note.GNU-stack","",%progbits
	.addrsig
	.addrsig_sym applet_entry
	.addrsig_sym stage18_rebased_pointer
	.addrsig_sym stage18_init_word
	.addrsig_sym stage18_zero_word
	.addrsig_sym stage18_zero_array
	.eabi_attribute	30, 1	@ Tag_ABI_optimization_goals
