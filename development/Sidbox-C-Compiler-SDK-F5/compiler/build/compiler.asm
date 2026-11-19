
/mnt/LinuxDatas/work/SidboxIDE/SidboxIDE/development/Sidbox-C-Compiler-SDK-F5/compiler/build/cgarm/compiler-cgarm/compiler.elf:     file format elf32-littlearm


Disassembly of section .text.initMalloc:

d00155f8 <.text.initMalloc>:
d00155f8:	f44f4b06 			; <UNDEFINED> instruction: 0xf44f4b06
d00155fc:	4a064180 	bmi	0xd01a5c04
d0015600:	589a447b 	ldmpl	sl, {r0, r1, r3, r4, r5, r6, sl, lr}
d0015604:	4a056011 	bmi	0xd016d650
d0015608:	4b05589a 	blmi	0xd016b878
d001560c:	601a447b 	andsvs	r4, sl, fp, ror r4
d0015610:	bf004770 	svclt	0x00004770
d0015614:	000018e0 	andeq	r1, r0, r0, ror #17
d0015618:	00000004 	andeq	r0, r0, r4
d001561c:	00000000 	andeq	r0, r0, r0
d0015620:	000476a0 	andeq	r7, r4, r0, lsr #13

Disassembly of section .text.applet_entry:

d0015624 <.text.applet_entry>:
d0015624:	9101b507 	tstls	r1, r7, lsl #10
d0015628:	ffe6f7ff 			; <UNDEFINED> instruction: 0xffe6f7ff
d001562c:	b0039901 	andlt	r9, r3, r1, lsl #18
d0015630:	eb04f85d 	bl	0xd01537ac
d0015634:	be78f7ff 	mrclt	7, 3, APSR_nzcv, cr8, cr15, {7}

Disassembly of section .text.read_file:

d0014950 <.text.read_file>:
d0014950:	41ffe92d 	mvnsmi	lr, sp, lsr #18
d0014954:	4b1a461e 	blmi	0xd06a61d4
d0014958:	4690460f 	ldrmi	r4, [r0], pc, lsl #12
d001495c:	aa01685b 	bge	0xd006ead0
d0014960:	681d2101 	ldmdavs	sp, {r0, r8, sp}
d0014964:	47986bab 	ldrmi	r6, [r8, fp, lsr #23]
d0014968:	4604b120 	strmi	fp, [r4], -r0, lsr #2
d001496c:	b0044620 	andlt	r4, r4, r0, lsr #12
d0014970:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d0014974:	0002e9cd 	andeq	lr, r2, sp, asr #19
d0014978:	a9026ceb 	stmdbge	r2, {r0, r1, r3, r5, r6, r7, sl, fp, sp, lr}
d001497c:	47989801 	ldrmi	r9, [r8, r1, lsl #16]
d0014980:	b9784604 	ldmdblt	r8!, {r2, r9, sl, lr}^
d0014984:	45429a02 	strbmi	r9, [r2, #-2562]	; 0xfffff5fe
d0014988:	b15ad817 	cmplt	sl, r7, lsl r8
d001498c:	ab036bec 	blge	0xd00ef944
d0014990:	98014639 	stmdals	r1, {r0, r3, r4, r5, r9, sl, lr}
d0014994:	460447a0 	strmi	r4, [r4], -r0, lsr #15
d0014998:	e9ddb920 	ldmib	sp, {r5, r8, fp, ip, sp, pc}^
d001499c:	1a240402 	bne	0xd09159ac
d00149a0:	2401bf18 	strcs	fp, [r1], #-3864	; 0xfffff0e8
d00149a4:	98016d6b 	stmdals	r1, {r0, r1, r3, r5, r6, r8, sl, fp, sp, lr}
d00149a8:	2c004798 	stccs	7, cr4, [r0], {152}	; 0x98
d00149ac:	4604d1de 			; <UNDEFINED> instruction: 0x4604d1de
d00149b0:	d1db2800 	bicsle	r2, fp, r0, lsl #16
d00149b4:	60339b02 	eorsvs	r9, r3, r2, lsl #22
d00149b8:	f06fe7d8 			; <UNDEFINED> instruction: 0xf06fe7d8
d00149bc:	e7f10402 	ldrb	r0, [r1, r2, lsl #8]!
d00149c0:	2001f000 	andcs	pc, r1, r0

Disassembly of section .text.read_apicore:

d00149e4 <.text.read_apicore>:
d00149e4:	460ab507 	strmi	fp, [sl], -r7, lsl #10
d00149e8:	48064601 	stmdami	r6, {r0, r9, sl, lr}
d00149ec:	4478ab01 	ldrbtmi	sl, [r8], #-2817	; 0xfffff4ff
d00149f0:	ffaef7ff 			; <UNDEFINED> instruction: 0xffaef7ff
d00149f4:	9801b918 	stmdals	r1, {r3, r4, r8, fp, ip, sp, pc}
d00149f8:	f85db003 			; <UNDEFINED> instruction: 0xf85db003
d00149fc:	2000fb04 	andcs	pc, r0, r4, lsl #22
d0014a00:	bf00e7fa 	svclt	0x0000e7fa
d0014a04:	ffffffd2 			; <UNDEFINED> instruction: 0xffffffd2

Disassembly of section .text.write_file:

d0014a20 <.text.write_file>:
d0014a20:	41ffe92d 	mvnsmi	lr, sp, lsr #18
d0014a24:	46154b3e 			; <UNDEFINED> instruction: 0x46154b3e
d0014a28:	46074c3e 			; <UNDEFINED> instruction: 0x46074c3e
d0014a2c:	4688685b 	pkhtbmi	r6, r8, fp, asr #16
d0014a30:	4a3d447c 	bmi	0xd0f65c28
d0014a34:	f44f681e 	vst2.8	{d22-d23}, [pc :64], lr
d0014a38:	46037180 	strmi	r7, [r3], -r0, lsl #3
d0014a3c:	4620447a 			; <UNDEFINED> instruction: 0x4620447a
d0014a40:	f9d8f002 			; <UNDEFINED> instruction: 0xf9d8f002
d0014a44:	483a4a39 	ldmdami	sl!, {r0, r3, r4, r5, r9, fp, lr}
d0014a48:	447a463b 	ldrbtmi	r4, [sl], #-1595	; 0xfffff9c5
d0014a4c:	7180f44f 	orrvc	pc, r0, pc, asr #8
d0014a50:	f0024478 			; <UNDEFINED> instruction: 0xf0024478
d0014a54:	4620f9cf 	strtmi	pc, [r0], -pc, asr #19
d0014a58:	aa016bb3 	bge	0xd006f92c
d0014a5c:	47982106 	ldrmi	r2, [r8, r6, lsl #2]
d0014a60:	b9784604 	ldmdblt	r8!, {r2, r9, sl, lr}^
d0014a64:	b98d9002 	stmiblt	sp, {r1, ip, pc}
d0014a68:	98016d33 	stmdals	r1, {r0, r1, r4, r5, r8, sl, fp, sp, lr}
d0014a6c:	46044798 			; <UNDEFINED> instruction: 0x46044798
d0014a70:	98016d73 	stmdals	r1, {r0, r1, r4, r5, r6, r8, sl, fp, sp, lr}
d0014a74:	b90c4798 	stmdblt	ip, {r3, r4, r7, r8, r9, sl, lr}
d0014a78:	4604b1b0 			; <UNDEFINED> instruction: 0x4604b1b0
d0014a7c:	6db3482d 	ldcvs	8, cr4, [r3, #180]!	; 0xb4
d0014a80:	47984478 			; <UNDEFINED> instruction: 0x47984478
d0014a84:	b0044620 	andlt	r4, r4, r0, lsr #12
d0014a88:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d0014a8c:	ab026c34 	blge	0xd00afb64
d0014a90:	4641462a 	strbmi	r4, [r1], -sl, lsr #12
d0014a94:	47a09801 	strmi	r9, [r0, r1, lsl #16]!
d0014a98:	28004604 	stmdacs	r0, {r2, r9, sl, lr}
d0014a9c:	9b02d1e8 	blls	0xd00c9244
d0014aa0:	d0e142ab 	rscle	r4, r1, fp, lsr #5
d0014aa4:	e7e32401 	strb	r2, [r3, r1, lsl #8]!
d0014aa8:	46226ab3 			; <UNDEFINED> instruction: 0x46226ab3
d0014aac:	4638a903 	ldrtmi	sl, [r8], -r3, lsl #18
d0014ab0:	47989403 	ldrmi	r9, [r8, r3, lsl #8]
d0014ab4:	b9804605 	stmiblt	r0, {r0, r2, r9, sl, lr}
d0014ab8:	07db9b03 	ldrbeq	r9, [fp, r3, lsl #22]
d0014abc:	491ed424 	ldmdbmi	lr, {r2, r5, sl, ip, lr, pc}
d0014ac0:	6df34638 	ldclvs	6, cr4, [r3, #224]!	; 0xe0
d0014ac4:	47984479 			; <UNDEFINED> instruction: 0x47984479
d0014ac8:	b1d84605 	bicslt	r4, r8, r5, lsl #12
d0014acc:	6db3481b 	ldcvs	8, cr4, [r3, #108]!	; 0x6c
d0014ad0:	47984478 			; <UNDEFINED> instruction: 0x47984478
d0014ad4:	462cb9d4 			; <UNDEFINED> instruction: 0x462cb9d4
d0014ad8:	2804e7d4 	stmdacs	r4, {r2, r4, r6, r7, r8, r9, sl, sp, lr, pc}
d0014adc:	4818d1f6 	ldmdami	r8, {r1, r2, r4, r5, r6, r7, r8, ip, lr, pc}
d0014ae0:	6df34639 	ldclvs	6, cr4, [r3, #228]!	; 0xe4
d0014ae4:	47984478 			; <UNDEFINED> instruction: 0x47984478
d0014ae8:	28004605 	stmdacs	r0, {r0, r2, r9, sl, lr}
d0014aec:	2c00d1ee 	stfcsd	f5, [r0], {238}	; 0xee
d0014af0:	4814d0c8 	ldmdami	r4, {r3, r6, r7, ip, lr, pc}
d0014af4:	44786db3 	ldrbtmi	r6, [r8], #-3507	; 0xfffff24d
d0014af8:	1e044798 	mcrne	7, 0, r4, cr4, cr8, {4}
d0014afc:	2401bf18 	strcs	fp, [r1], #-3864	; 0xfffff0e8
d0014b00:	e7bf4264 	ldr	r4, [pc, r4, ror #4]!
d0014b04:	e7ea2401 	strb	r2, [sl, r1, lsl #8]!
d0014b08:	e7df2507 	ldrb	r2, [pc, r7, lsl #10]
d0014b0c:	4639480e 	ldrtmi	r4, [r9], -lr, lsl #16
d0014b10:	44786df3 	ldrbtmi	r6, [r8], #-3571	; 0xfffff20d
d0014b14:	28004798 	stmdacs	r0, {r3, r4, r7, r8, r9, sl, lr}
d0014b18:	f06fd0dd 			; <UNDEFINED> instruction: 0xf06fd0dd
d0014b1c:	e7b10401 	ldr	r0, [r1, r1, lsl #8]!
d0014b20:	2001f000 	andcs	pc, r1, r0
d0014b24:	00047ff8 	strdeq	r7, [r4], -r8
d0014b28:	ffffffc8 			; <UNDEFINED> instruction: 0xffffffc8
d0014b2c:	ffffffc6 			; <UNDEFINED> instruction: 0xffffffc6
d0014b30:	00026d38 	andeq	r6, r2, r8, lsr sp
d0014b34:	00047fa8 	andeq	r7, r4, r8, lsr #31
d0014b38:	00026cc4 	andeq	r6, r2, r4, asr #25
d0014b3c:	00047f58 	andeq	r7, r4, r8, asr pc
d0014b40:	00047f44 	andeq	r7, r4, r4, asr #30
d0014b44:	00026c92 	muleq	r2, r2, ip
d0014b48:	00026c76 	andeq	r6, r2, r6, ror ip

Disassembly of section .text.show_status:

d0014b50 <.text.show_status>:
d0014b50:	46024b09 	strmi	r4, [r2], -r9, lsl #22
d0014b54:	6818447b 	ldmdavs	r8, {r0, r1, r3, r4, r5, r6, sl, lr}
d0014b58:	689b4b06 	ldmvs	fp, {r1, r2, r8, r9, fp, lr}
d0014b5c:	68dbb120 	ldmvs	fp, {r5, r8, ip, sp, pc}^
d0014b60:	f8d34611 			; <UNDEFINED> instruction: 0xf8d34611
d0014b64:	471830c4 	ldrmi	r3, [r8, -r4, asr #1]
d0014b68:	4904681b 	stmdbmi	r4, {r0, r1, r3, r4, fp, sp, lr}
d0014b6c:	4479681b 	ldrbtmi	r6, [r9], #-2075	; 0xfffff7e5
d0014b70:	bf004718 	svclt	0x00004718
d0014b74:	2001f000 	andcs	pc, r1, r0
d0014b78:	00048154 	andeq	r8, r4, r4, asr r1
d0014b7c:	ffffffda 			; <UNDEFINED> instruction: 0xffffffda

Disassembly of section .text.open_editor:

d0014bf8 <.text.open_editor>:
d0014bf8:	47ffe92d 	ldrbmi	lr, [pc, sp, lsr #18]!
d0014bfc:	f2404c5d 	vfma.f32	q10, q0, <illegal reg q6.5>
d0014c00:	4607324d 	strmi	r3, [r7], -sp, asr #4
d0014c04:	68a3210c 	stmiavs	r3!, {r2, r3, r8, sp}
d0014c08:	685b2000 	ldmdavs	fp, {sp}^
d0014c0c:	4a5a9202 	bmi	0xd16b941c
d0014c10:	9201447a 	andls	r4, r1, #2046820352	; 0x7a000000
d0014c14:	728ef44f 	addvc	pc, lr, #1325400064	; 0x4f000000
d0014c18:	22119200 	andscs	r9, r1, #0, 4
d0014c1c:	f44f681d 	vst2.8	{d22-d23}, [pc :64]!
d0014c20:	47a873e4 	strmi	r7, [r8, r4, ror #7]!
d0014c24:	46051e43 	strmi	r1, [r5], -r3, asr #28
d0014c28:	2bfdb2db 	blcs	0xcff8179c
d0014c2c:	4853d907 	ldmdami	r3, {r0, r1, r2, r8, fp, ip, lr, pc}^
d0014c30:	f7ff4478 			; <UNDEFINED> instruction: 0xf7ff4478
d0014c34:	2001ff8d 	andcs	pc, r1, sp, lsl #31
d0014c38:	e8bdb004 	pop	{r2, ip, sp, pc}
d0014c3c:	4e5087f0 	mrcmi	7, 2, r8, cr0, cr0, {7}
d0014c40:	447e212f 	ldrbtmi	r2, [lr], #-303	; 0xfffffed1
d0014c44:	f0024630 			; <UNDEFINED> instruction: 0xf0024630
d0014c48:	68a2f93d 	stmiavs	r2!, {r0, r2, r3, r4, r5, r8, fp, ip, sp, lr, pc}
d0014c4c:	68d24603 	ldmvs	r2, {r0, r1, r9, sl, lr}^
d0014c50:	8018f8d2 			; <UNDEFINED> instruction: 0x8018f8d2
d0014c54:	d07a2800 	rsbsle	r2, sl, r0, lsl #16
d0014c58:	26013301 	strcs	r3, [r1], -r1, lsl #6
d0014c5c:	23109301 	tstcs	r0, #67108864	; 0x4000000
d0014c60:	21082209 	tstcs	r8, r9, lsl #4
d0014c64:	93004628 	movwls	r4, #1576	; 0x628
d0014c68:	7387f44f 	orrvc	pc, r7, #1325400064	; 0x4f000000
d0014c6c:	f04f9602 			; <UNDEFINED> instruction: 0xf04f9602
d0014c70:	47c00918 	bfimi	r0, r8, (invalid: 18:0)
d0014c74:	4a4368a3 	bmi	0xd10eef08
d0014c78:	718ff44f 	orrvc	pc, pc, pc, asr #8
d0014c7c:	468068db 	pkhtbmi	r6, r0, fp, asr #17
d0014c80:	f8cd447a 			; <UNDEFINED> instruction: 0xf8cd447a
d0014c84:	96029000 	strls	r9, [r2], -r0
d0014c88:	92014628 	andls	r4, r1, #40, 12	; 0x2800000
d0014c8c:	f8d32204 			; <UNDEFINED> instruction: 0xf8d32204
d0014c90:	2344a008 	movtcs	sl, #16392	; 0x4008
d0014c94:	4b3c47d0 	blmi	0xd0f26bdc
d0014c98:	f44f4a3c 	vst1.8	{d20-d21}, [pc :256], ip
d0014c9c:	447b71b4 	ldrbtmi	r7, [fp], #-436	; 0xfffffe4c
d0014ca0:	6018447a 	andsvs	r4, r8, sl, ror r4
d0014ca4:	68a34628 	stmiavs	r3!, {r3, r5, r9, sl, lr}
d0014ca8:	920168db 	andls	r6, r1, #14352384	; 0xdb0000
d0014cac:	96022204 	strls	r2, [r2], -r4, lsl #4
d0014cb0:	9000f8cd 	andls	pc, r0, sp, asr #17
d0014cb4:	9008f8d3 	ldrdls	pc, [r8], -r3
d0014cb8:	47c8234e 	strbmi	r2, [r8, lr, asr #6]
d0014cbc:	22004b34 	andcs	r4, r0, #52, 22	; 0xd000
d0014cc0:	447b2108 	ldrbtmi	r2, [fp], #-264	; 0xfffffef8
d0014cc4:	46286018 			; <UNDEFINED> instruction: 0x46286018
d0014cc8:	68db68a3 	ldmvs	fp, {r0, r1, r5, r7, fp, sp, lr}^
d0014ccc:	4a319202 	bmi	0xd0c794dc
d0014cd0:	447a9603 	ldrbtmi	r9, [sl], #-1539	; 0xfffff9fd
d0014cd4:	22c19201 	sbccs	r9, r1, #268435456	; 0x10000000
d0014cd8:	22229200 	eorcs	r9, r2, #0, 4
d0014cdc:	9034f8d3 	ldrsbtls	pc, [r4], -r3	; <UNPREDICTABLE>
d0014ce0:	73d7f44f 	bicsvc	pc, r7, #1325400064	; 0x4f000000
d0014ce4:	4b2c47c8 	blmi	0xd0b26c0c
d0014ce8:	6018447b 	andsvs	r4, r8, fp, ror r4
d0014cec:	68db68a3 	ldmvs	fp, {r0, r1, r5, r7, fp, sp, lr}^
d0014cf0:	9018f8d3 			; <UNDEFINED> instruction: 0x9018f8d3
d0014cf4:	d12c2f00 			; <UNDEFINED> instruction: 0xd12c2f00
d0014cf8:	447b4b28 	ldrbtmi	r4, [fp], #-2856	; 0xfffff4d8
d0014cfc:	23129301 	tstcs	r2, #67108864	; 0x4000000
d0014d00:	210822eb 	smlattcs	r8, fp, r2, r2
d0014d04:	46289300 	strtmi	r9, [r8], -r0, lsl #6
d0014d08:	73d7f44f 	bicsvc	pc, r7, #1325400064	; 0x4f000000
d0014d0c:	47c89602 	strbmi	r9, [r8, r2, lsl #12]
d0014d10:	447b4b23 	ldrbtmi	r4, [fp], #-2851	; 0xfffff4dd
d0014d14:	f1b86018 			; <UNDEFINED> instruction: 0xf1b86018
d0014d18:	d00c0f00 	andle	r0, ip, r0, lsl #30
d0014d1c:	447b4b21 	ldrbtmi	r4, [fp], #-2849	; 0xfffff4df
d0014d20:	b143681b 	cmplt	r3, fp, lsl r8
d0014d24:	447b4b20 	ldrbtmi	r4, [fp], #-2848	; 0xfffff4e0
d0014d28:	b123681b 			; <UNDEFINED> instruction: 0xb123681b
d0014d2c:	447e4e1f 	ldrbtmi	r4, [lr], #-3615	; 0xfffff1e1
d0014d30:	b1036833 	tstlt	r3, r3, lsr r8
d0014d34:	68a3b980 	stmiavs	r3!, {r7, r8, fp, ip, sp, pc}
d0014d38:	685b4628 	ldmdavs	fp, {r3, r5, r9, sl, lr}^
d0014d3c:	4798685b 			; <UNDEFINED> instruction: 0x4798685b
d0014d40:	22004b1b 	andcs	r4, r0, #27648	; 0x6c00
d0014d44:	447b481b 	ldrbtmi	r4, [fp], #-2075	; 0xfffff7e5
d0014d48:	601a4478 	andsvs	r4, sl, r8, ror r4
d0014d4c:	4633e771 			; <UNDEFINED> instruction: 0x4633e771
d0014d50:	4b19e783 	blmi	0xd068eb64
d0014d54:	e7d1447b 			; <UNDEFINED> instruction: 0xe7d1447b
d0014d58:	462868a3 	strtmi	r6, [r8], -r3, lsr #17
d0014d5c:	685b4917 	ldmdavs	fp, {r0, r1, r2, r4, r8, fp, lr}^
d0014d60:	689b4479 	ldmvs	fp, {r0, r3, r4, r5, r6, sl, lr}
d0014d64:	68a34798 	stmiavs	r3!, {r3, r4, r7, r8, r9, sl, lr}
d0014d68:	68db6830 	ldmvs	fp, {r4, r5, fp, sp, lr}^
d0014d6c:	47986ddb 			; <UNDEFINED> instruction: 0x47986ddb
d0014d70:	e7612000 	strb	r2, [r1, -r0]!
d0014d74:	2001f000 	andcs	pc, r1, r0
d0014d78:	ffffff8a 			; <UNDEFINED> instruction: 0xffffff8a
d0014d7c:	ffffff73 			; <UNDEFINED> instruction: 0xffffff73
d0014d80:	00047ce6 	andeq	r7, r4, r6, ror #25
d0014d84:	ffffff3f 			; <UNDEFINED> instruction: 0xffffff3f
d0014d88:	00027c76 	andeq	r7, r2, r6, ror ip
d0014d8c:	ffffff24 			; <UNDEFINED> instruction: 0xffffff24
d0014d90:	00026bc6 	andeq	r6, r2, r6, asr #23
d0014d94:	00027c46 	andeq	r7, r2, r6, asr #24
d0014d98:	00026ba4 	andeq	r6, r2, r4, lsr #23
d0014d9c:	fffffe92 			; <UNDEFINED> instruction: 0xfffffe92
d0014da0:	00047f96 	muleq	r4, r6, pc	; <UNPREDICTABLE>
d0014da4:	00027bf6 	strdeq	r7, [r2], -r6
d0014da8:	00026b62 	andeq	r6, r2, r2, ror #22
d0014dac:	00026b5e 	andeq	r6, r2, lr, asr fp
d0014db0:	00047f62 	andeq	r7, r4, r2, ror #30
d0014db4:	fffffe82 			; <UNDEFINED> instruction: 0xfffffe82
d0014db8:	fffffe28 			; <UNDEFINED> instruction: 0xfffffe28
d0014dbc:	00000441 	andeq	r0, r0, r1, asr #8

Disassembly of section .text.report_file.part.0:

d0014e68 <.text.report_file.part.0>:
d0014e68:	1cc5b537 	cfstr64ne	mvdx11, [r5], {55}	; 0x37
d0014e6c:	460b4604 	strmi	r4, [fp], -r4, lsl #12
d0014e70:	4812d108 	ldmdami	r2, {r3, r8, ip, lr, pc}
d0014e74:	f7ff4478 			; <UNDEFINED> instruction: 0xf7ff4478
d0014e78:	1c63fe6b 	stclne	14, cr15, [r3], #-428	; 0xfffffe54
d0014e7c:	41584258 	cmpmi	r8, r8, asr r2
d0014e80:	bd30b003 	ldclt	0, cr11, [r0, #-12]!
d0014e84:	d1021d20 	tstle	r2, r0, lsr #26
d0014e88:	4478480d 	ldrbtmi	r4, [r8], #-2061	; 0xfffff7f3
d0014e8c:	1ca1e7f3 	stcne	7, cr14, [r1], #972	; 0x3cc
d0014e90:	480cd102 	stmdami	ip, {r1, r8, ip, lr, pc}
d0014e94:	e7ee4478 			; <UNDEFINED> instruction: 0xe7ee4478
d0014e98:	d1021c62 	tstle	r2, r2, ror #24
d0014e9c:	4478480a 	ldrbtmi	r4, [r8], #-2058	; 0xfffff7f6
d0014ea0:	4d0ae7e9 	stcmi	7, cr14, [sl, #-932]	; 0xfffffc5c
d0014ea4:	71c0f44f 	bicvc	pc, r0, pc, asr #8
d0014ea8:	447d4a09 	ldrbtmi	r4, [sp], #-2569	; 0xfffff5f7
d0014eac:	447a9400 	ldrbtmi	r9, [sl], #-1024	; 0xfffffc00
d0014eb0:	f0014628 			; <UNDEFINED> instruction: 0xf0014628
d0014eb4:	4628ff9f 	qadd8mi	pc, r8, pc	; <UNPREDICTABLE>
d0014eb8:	bf00e7dd 	svclt	0x0000e7dd
d0014ebc:	ffffff48 			; <UNDEFINED> instruction: 0xffffff48
d0014ec0:	ffffff49 			; <UNDEFINED> instruction: 0xffffff49
d0014ec4:	ffffff5a 			; <UNDEFINED> instruction: 0xffffff5a
d0014ec8:	ffffff7c 			; <UNDEFINED> instruction: 0xffffff7c
d0014ecc:	00047c7e 	andeq	r7, r4, lr, ror ip
d0014ed0:	ffffff9b 			; <UNDEFINED> instruction: 0xffffff9b

Disassembly of section .text.resolve_source_path.constprop.0:

d0014ee4 <.text.resolve_source_path.constprop.0>:
d0014ee4:	4604b573 			; <UNDEFINED> instruction: 0x4604b573
d0014ee8:	f001460e 			; <UNDEFINED> instruction: 0xf001460e
d0014eec:	2802ffbb 	stmdacs	r2, {r0, r1, r3, r4, r5, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0014ef0:	2000d802 	andcs	sp, r0, r2, lsl #16
d0014ef4:	bd70b002 	ldcllt	0, cr11, [r0, #-8]!
d0014ef8:	f8104420 			; <UNDEFINED> instruction: 0xf8104420
d0014efc:	2b2e3c02 	blcs	0xd0ba3f0c
d0014f00:	f810d1f7 			; <UNDEFINED> instruction: 0xf810d1f7
d0014f04:	f0433c01 			; <UNDEFINED> instruction: 0xf0433c01
d0014f08:	2b630320 	blcs	0xd18d5b90
d0014f0c:	213ad1f1 	teqcs	sl, r1	; <illegal shifter operand>
d0014f10:	f0014620 			; <UNDEFINED> instruction: 0xf0014620
d0014f14:	7823ffcb 	stmdavc	r3!, {r0, r1, r3, r6, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0014f18:	d0032b2f 	andle	r2, r3, pc, lsr #22
d0014f1c:	7843b180 	stmdavc	r3, {r7, r8, ip, sp, pc}^
d0014f20:	d1e62b2f 	mvnle	r2, pc, lsr #22
d0014f24:	46234a1b 			; <UNDEFINED> instruction: 0x46234a1b
d0014f28:	7180f44f 	orrvc	pc, r0, pc, asr #8
d0014f2c:	447a4630 	ldrbtmi	r4, [sl], #-1584	; 0xfffff9d0
d0014f30:	ff60f001 			; <UNDEFINED> instruction: 0xff60f001
d0014f34:	28fc3803 	ldmcs	ip!, {r0, r1, fp, ip, sp}^
d0014f38:	2000bf8c 	andcs	fp, r0, ip, lsl #31
d0014f3c:	e7d92001 	ldrb	r2, [r9, r1]
d0014f40:	f44f4b13 			; <UNDEFINED> instruction: 0xf44f4b13
d0014f44:	4d147180 	ldfmis	f7, [r4, #-512]	; 0xfffffe00
d0014f48:	447d685b 	ldrbtmi	r6, [sp], #-2139	; 0xfffff7a5
d0014f4c:	4628681b 			; <UNDEFINED> instruction: 0x4628681b
d0014f50:	479869db 			; <UNDEFINED> instruction: 0x479869db
d0014f54:	d1cc2800 	bicle	r2, ip, r0, lsl #16
d0014f58:	2b00782b 	blcs	0xd003300c
d0014f5c:	4628d0c9 	strtmi	sp, [r8], -r9, asr #1
d0014f60:	ff80f001 			; <UNDEFINED> instruction: 0xff80f001
d0014f64:	f8104428 			; <UNDEFINED> instruction: 0xf8104428
d0014f68:	2b2f3c01 	blcs	0xd0be3f74
d0014f6c:	4b0bd00d 	blmi	0xd0308fa8
d0014f70:	4a0b447b 	bmi	0xd02e6164
d0014f74:	7180f44f 	orrvc	pc, r0, pc, asr #8
d0014f78:	447a4630 	ldrbtmi	r4, [sl], #-1584	; 0xfffff9d0
d0014f7c:	3400e9cd 	strcc	lr, [r0], #-2509	; 0xfffff633
d0014f80:	447b4b08 	ldrbtmi	r4, [fp], #-2824	; 0xfffff4f8
d0014f84:	ff36f001 			; <UNDEFINED> instruction: 0xff36f001
d0014f88:	4b07e7d4 	blmi	0xd020eee0
d0014f8c:	e7f0447b 			; <UNDEFINED> instruction: 0xe7f0447b
d0014f90:	2001f000 	andcs	pc, r1, r0
d0014f94:	ffffffa5 			; <UNDEFINED> instruction: 0xffffffa5
d0014f98:	00047ade 	ldrdeq	r7, [r4], -lr
d0014f9c:	ffffff61 			; <UNDEFINED> instruction: 0xffffff61
d0014fa0:	ffffff5c 			; <UNDEFINED> instruction: 0xffffff5c
d0014fa4:	00047aa6 	andeq	r7, r4, r6, lsr #21
d0014fa8:	ffffff44 			; <UNDEFINED> instruction: 0xffffff44

Disassembly of section .text.build:

d0015000 <.text.build>:
d0015000:	b5304b4e 	ldrlt	r4, [r0, #-2894]!	; 0xfffff4b2
d0015004:	b08d447b 	addlt	r4, sp, fp, ror r4
d0015008:	3006e9cd 	andcc	lr, r6, sp, asr #19
d001500c:	447b4b4c 	ldrbtmi	r4, [fp], #-2892	; 0xfffff4b4
d0015010:	29006819 	stmdbcs	r0, {r0, r3, r4, fp, sp, lr}
d0015014:	484bd04c 	stmdami	fp, {r2, r3, r6, ip, lr, pc}^
d0015018:	ab084478 	blge	0xd0226200
d001501c:	4a4a2901 	bmi	0xd129f428
d0015020:	bf389300 	svclt	0x00389300
d0015024:	ab052101 	blge	0xd015d430
d0015028:	f7ff447a 			; <UNDEFINED> instruction: 0xf7ff447a
d001502c:	4604fbff 			; <UNDEFINED> instruction: 0x4604fbff
d0015030:	d1422800 	cmple	r2, r0, lsl #16
d0015034:	9b0b4a45 	blls	0xd02e7950
d0015038:	6812447a 	ldmdavs	r2, {r1, r3, r4, r5, r6, sl, lr}
d001503c:	d2394293 	eorsle	r4, r9, #805306377	; 0x30000009
d0015040:	447c4c43 	ldrbtmi	r4, [ip], #-3139	; 0xfffff3bd
d0015044:	2403eb04 	strcs	lr, [r3], #-2820	; 0xfffff4fc
d0015048:	4620212f 	strtmi	r2, [r0], -pc, lsr #2
d001504c:	ff3af001 			; <UNDEFINED> instruction: 0xff3af001
d0015050:	1c44b100 	stfnep	f3, [r4], {-0}
d0015054:	9a099b08 	bls	0xd027bc7c
d0015058:	b90b990a 	stmdblt	fp, {r1, r3, r8, fp, ip, pc}
d001505c:	447b4b3d 	ldrbtmi	r4, [fp], #-2877	; 0xfffff4c3
d0015060:	9200483d 	andls	r4, r0, #3997696	; 0x3d0000
d0015064:	4a3d4478 	bmi	0xd0f6624c
d0015068:	46239302 	strtmi	r9, [r3], -r2, lsl #6
d001506c:	447a4604 	ldrbtmi	r4, [sl], #-1540	; 0xfffff9fc
d0015070:	f44f9101 	vst4.8	{d25,d27,d29,d31}, [pc], r1
d0015074:	f00171c0 			; <UNDEFINED> instruction: 0xf00171c0
d0015078:	4620febd 			; <UNDEFINED> instruction: 0x4620febd
d001507c:	f7ff4c38 			; <UNDEFINED> instruction: 0xf7ff4c38
d0015080:	447cfd67 	ldrbtmi	pc, [ip], #-3431	; 0xfffff299	; <UNPREDICTABLE>
d0015084:	b1886820 	orrlt	r6, r8, r0, lsr #16
d0015088:	b1719909 	cmnlt	r1, r9, lsl #18
d001508c:	b1629a0a 	cmnlt	r2, sl, lsl #20
d0015090:	3a014d29 	bcc	0xd006853c
d0015094:	68ab3901 	stmiavs	fp!, {r0, r8, fp, ip, sp}
d0015098:	f8d368db 			; <UNDEFINED> instruction: 0xf8d368db
d001509c:	479830b8 			; <UNDEFINED> instruction: 0x479830b8
d00150a0:	682068ab 	stmdavs	r0!, {r0, r1, r3, r5, r7, fp, sp, lr}
d00150a4:	6ddb68db 	ldclvs	8, cr6, [fp, #876]	; 0x36c
d00150a8:	20004798 	mulcs	r0, r8, r7
d00150ac:	bd30b00d 	ldclt	0, cr11, [r0, #-52]!	; 0xffffffcc
d00150b0:	e7b2a806 	ldr	sl, [r2, r6, lsl #16]!
d00150b4:	447c4c2b 	ldrbtmi	r4, [ip], #-3115	; 0xfffff3d5
d00150b8:	4d2be7c6 	stcmi	7, cr14, [fp, #-792]!	; 0xfffffce8
d00150bc:	99054602 	stmdbls	r5, {r1, r9, sl, lr}
d00150c0:	4628447d 			; <UNDEFINED> instruction: 0x4628447d
d00150c4:	fcacf7ff 	stc2	7, cr15, [ip], #1020	; 0x3fc
d00150c8:	4b28bb80 	blmi	0xd0a43ed0
d00150cc:	6818447b 	ldmdavs	r8, {r0, r1, r3, r4, r5, r6, sl, lr}
d00150d0:	212fb118 			; <UNDEFINED> instruction: 0x212fb118
d00150d4:	f0014628 			; <UNDEFINED> instruction: 0xf0014628
d00150d8:	4b25fef5 	blmi	0xd0994cb4
d00150dc:	681a447b 	ldmdavs	sl, {r0, r1, r3, r4, r5, r6, sl, lr}
d00150e0:	d9142a01 	ldmdble	r4, {r0, r9, fp, sp}
d00150e4:	1c43b180 	stfnep	f3, [r3], {128}	; 0x80
d00150e8:	f44f4822 	vst2.8	{d20-d21}, [pc :128], r2
d00150ec:	920171c0 	andls	r7, r1, #192, 2	; 0x30
d00150f0:	44784a21 	ldrbtmi	r4, [r8], #-2593	; 0xfffff5df
d00150f4:	447a9400 	ldrbtmi	r9, [sl], #-1024	; 0xfffffc00
d00150f8:	fe7cf001 	cdp2	0, 7, cr15, cr12, cr1, {0}
d00150fc:	4478481f 	ldrbtmi	r4, [r8], #-2079	; 0xfffff7e1
d0015100:	fd26f7ff 	stc2	7, cr15, [r6, #-1020]!	; 0xfffffc04
d0015104:	e7d12001 	ldrb	r2, [r1, r1]
d0015108:	447b4b1d 	ldrbtmi	r4, [fp], #-2845	; 0xfffff4e3
d001510c:	b150e7ec 	cmplt	r0, ip, ror #15
d0015110:	4a1c1c43 	bmi	0xd071c224
d0015114:	71c0f44f 	bicvc	pc, r0, pc, asr #8
d0015118:	447a481b 	ldrbtmi	r4, [sl], #-2075	; 0xfffff7e5
d001511c:	44789400 	ldrbtmi	r9, [r8], #-1024	; 0xfffffc00
d0015120:	fe68f001 	cdp2	0, 6, cr15, cr8, cr1, {0}
d0015124:	4b19e7ea 	blmi	0xd068f0d4
d0015128:	e7f2447b 			; <UNDEFINED> instruction: 0xe7f2447b
d001512c:	44794918 	ldrbtmi	r4, [r9], #-2328	; 0xfffff6e8
d0015130:	fe9af7ff 	mrc2	7, 4, pc, cr10, cr15, {7}
d0015134:	bf00e7ba 	svclt	0x0000e7ba
d0015138:	2001f000 	andcs	pc, r1, r0
d001513c:	00027914 	andeq	r7, r2, r4, lsl r9
d0015140:	00026882 	andeq	r6, r2, r2, lsl #17
d0015144:	0002787c 	andeq	r7, r2, ip, ror r8
d0015148:	fffff9b9 			; <UNDEFINED> instruction: 0xfffff9b9
d001514c:	00026858 	andeq	r6, r2, r8, asr r8
d0015150:	00026852 	andeq	r6, r2, r2, asr r8
d0015154:	ffffff4a 			; <UNDEFINED> instruction: 0xffffff4a
d0015158:	00047ac4 	andeq	r7, r4, r4, asr #21
d001515c:	ffffff4d 			; <UNDEFINED> instruction: 0xffffff4d
d0015160:	0002680a 	andeq	r6, r2, sl, lsl #16
d0015164:	00047872 	andeq	r7, r4, r2, ror r8
d0015168:	000265c8 	andeq	r6, r2, r8, asr #11
d001516c:	00047bdc 	ldrdeq	r7, [r4], -ip
d0015170:	000267b4 			; <UNDEFINED> instruction: 0x000267b4
d0015174:	00047a36 	andeq	r7, r4, r6, lsr sl
d0015178:	fffffed1 			; <UNDEFINED> instruction: 0xfffffed1
d001517c:	00047a2a 	andeq	r7, r4, sl, lsr #20
d0015180:	0002657e 	andeq	r6, r2, lr, ror r5
d0015184:	fffffecd 			; <UNDEFINED> instruction: 0xfffffecd
d0015188:	00047a0a 	andeq	r7, r4, sl, lsl #20
d001518c:	00026560 	andeq	r6, r2, r0, ror #10
d0015190:	fffffa96 			; <UNDEFINED> instruction: 0xfffffa96

Disassembly of section .text.editor_proc:

d00151a4 <.text.editor_proc>:
d00151a4:	460cb513 			; <UNDEFINED> instruction: 0x460cb513
d00151a8:	d0412900 	suble	r2, r1, r0, lsl #18
d00151ac:	2b10680b 	blcs	0xd042f1e0
d00151b0:	68cad13e 	stmiavs	sl, {r1, r2, r3, r4, r5, r8, ip, lr, pc}^
d00151b4:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d00151b8:	d139429a 	teqle	r9, sl	; <illegal shifter operand>
d00151bc:	688b4a1f 	stmvs	fp, {r0, r1, r2, r3, r4, r9, fp, lr}
d00151c0:	6812447a 	ldmdavs	r2, {r1, r3, r4, r5, r6, sl, lr}
d00151c4:	d0044293 	mulle	r4, r3, r2
d00151c8:	447a4a1d 	ldrbtmi	r4, [sl], #-2589	; 0xfffff5e3
d00151cc:	42936812 	addsmi	r6, r3, #1179648	; 0x120000
d00151d0:	4b18d12e 	blmi	0xd0649690
d00151d4:	689b481b 	ldmvs	fp, {r0, r1, r3, r4, fp, lr}
d00151d8:	4478491b 	ldrbtmi	r4, [r8], #-2331	; 0xfffff6e5
d00151dc:	447968db 	ldrbtmi	r6, [r9], #-2267	; 0xfffff725
d00151e0:	6f1b4a15 	svcvs	0x001b4a15
d00151e4:	91016800 	tstls	r1, r0, lsl #16
d00151e8:	38014798 	stmdacc	r1, {r3, r4, r7, r8, r9, sl, lr}
d00151ec:	f5b09901 			; <UNDEFINED> instruction: 0xf5b09901
d00151f0:	d9043f00 	stmdble	r4, {r8, r9, sl, fp, ip, sp}
d00151f4:	44784815 	ldrbtmi	r4, [r8], #-2069	; 0xfffff7eb
d00151f8:	fcaaf7ff 	stc2	7, cr15, [sl], #1020	; 0x3fc
d00151fc:	4b14e007 	blmi	0xd054d220
d0015200:	447b68a2 	ldrbtmi	r6, [fp], #-2210	; 0xfffff75e
d0015204:	429a681b 	addsmi	r6, sl, #1769472	; 0x1b0000
d0015208:	f7ffd104 			; <UNDEFINED> instruction: 0xf7ffd104
d001520c:	20f0fef9 	ldrshtcs	pc, [r0], #233	; 0xe9	; <UNPREDICTABLE>
d0015210:	bd10b002 	ldclt	0, cr11, [r0, #-8]
d0015214:	480f4602 	stmdami	pc, {r1, r9, sl, lr}	; <UNPREDICTABLE>
d0015218:	f7ff4478 			; <UNDEFINED> instruction: 0xf7ff4478
d001521c:	b910fc01 	ldmdblt	r0, {r0, sl, fp, ip, sp, lr, pc}
d0015220:	4478480d 	ldrbtmi	r4, [r8], #-2061	; 0xfffff7f3
d0015224:	490de7e8 	stmdbmi	sp, {r3, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d0015228:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d001522c:	e7eefe1d 			; <UNDEFINED> instruction: 0xe7eefe1d
d0015230:	e7ed2000 	strb	r2, [sp, r0]!
d0015234:	2001f000 	andcs	pc, r1, r0
d0015238:	00020001 	andeq	r0, r2, r1
d001523c:	00027754 	andeq	r7, r2, r4, asr r7
d0015240:	000266be 			; <UNDEFINED> instruction: 0x000266be
d0015244:	000266b2 			; <UNDEFINED> instruction: 0x000266b2
d0015248:	0002773a 	andeq	r7, r2, sl, lsr r7
d001524c:	fffffbc6 			; <UNDEFINED> instruction: 0xfffffbc6
d0015250:	00026686 	andeq	r6, r2, r6, lsl #13
d0015254:	00047710 	andeq	r7, r4, r0, lsl r7
d0015258:	ffffff6e 			; <UNDEFINED> instruction: 0xffffff6e
d001525c:	fffff997 			; <UNDEFINED> instruction: 0xfffff997

Disassembly of section .text.startup.main:

d0015328 <.text.startup.main>:
d0015328:	e92d2801 	push	{r0, fp, sp}
d001532c:	46064ff0 			; <UNDEFINED> instruction: 0x46064ff0
d0015330:	460db087 	strmi	fp, [sp], -r7, lsl #1
d0015334:	2803d015 	stmdacs	r3, {r0, r2, r4, ip, lr, pc}
d0015338:	4978d115 	ldmdbmi	r8!, {r0, r2, r4, r8, ip, lr, pc}^
d001533c:	44796868 	ldrbtmi	r6, [r9], #-2152	; 0xfffff798
d0015340:	fd9cf001 	ldc2	0, cr15, [ip, #4]
d0015344:	f480fab0 	vst3.32			; <UNDEFINED> instruction: 0xf480fab0
d0015348:	1e730964 	vsubne.f16	s1, s6, s9	; <UNPREDICTABLE>
d001534c:	d90c2b10 	stmdble	ip, {r4, r8, r9, fp, sp}
d0015350:	44784873 	ldrbtmi	r4, [r8], #-2163	; 0xfffff78d
d0015354:	f7ff2401 			; <UNDEFINED> instruction: 0xf7ff2401
d0015358:	4620fbfb 			; <UNDEFINED> instruction: 0x4620fbfb
d001535c:	e8bdb007 	pop	{r0, r1, r2, ip, sp, pc}
d0015360:	46048ff0 			; <UNDEFINED> instruction: 0x46048ff0
d0015364:	2400e7f1 	strcs	lr, [r0], #-2033	; 0xfffff80f
d0015368:	2e01e7ef 	cdpcs	7, 0, cr14, cr1, cr15, {7}
d001536c:	496dd046 	stmdbmi	sp!, {r1, r2, r6, ip, lr, pc}^
d0015370:	44796868 	ldrbtmi	r6, [r9], #-2152	; 0xfffff798
d0015374:	fd82f001 	stc2	0, cr15, [r2, #4]
d0015378:	f0402800 			; <UNDEFINED> instruction: 0xf0402800
d001537c:	2c0080ca 	stccs	0, cr8, [r0], {202}	; 0xca
d0015380:	f106d0e6 			; <UNDEFINED> instruction: 0xf106d0e6
d0015384:	3b014380 	blcc	0xd006618c
d0015388:	0023f855 	eoreq	pc, r3, r5, asr r8	; <UNPREDICTABLE>
d001538c:	8198f8df 			; <UNDEFINED> instruction: 0x8198f8df
d0015390:	464144f8 			; <UNDEFINED> instruction: 0x464144f8
d0015394:	fda6f7ff 	stc2	7, cr15, [r6, #1020]!	; 0x3fc
d0015398:	4640b398 			; <UNDEFINED> instruction: 0x4640b398
d001539c:	fd62f001 	stc2l	0, cr15, [r2, #-4]!
d00153a0:	030ef100 	movweq	pc, #57600	; 0xe100	; <UNPREDICTABLE>
d00153a4:	d82c2bff 	stmdale	ip!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, fp, sp}
d00153a8:	9180f8df 	ldrdls	pc, [r0, pc]
d00153ac:	46411e47 	strbmi	r1, [r1], -r7, asr #28
d00153b0:	463a44f9 			; <UNDEFINED> instruction: 0x463a44f9
d00153b4:	f0004648 			; <UNDEFINED> instruction: 0xf0004648
d00153b8:	495df94d 	ldmdbmi	sp, {r0, r2, r3, r6, r8, fp, ip, sp, lr, pc}^
d00153bc:	eb092204 	bl	0xd025dbd4
d00153c0:	44790007 	ldrbtmi	r0, [r9], #-7
d00153c4:	f946f000 			; <UNDEFINED> instruction: 0xf946f000
d00153c8:	4d5ab1f4 	ldfmip	f3, [sl, #-976]	; 0xfffffc30
d00153cc:	f44f2300 	vst2.8	{d18-d21}, [pc], r0
d00153d0:	46403200 	strbmi	r3, [r0], -r0, lsl #4
d00153d4:	9305447d 	movwls	r4, #21629	; 0x547d
d00153d8:	4629ab05 	strtmi	sl, [r9], -r5, lsl #22
d00153dc:	fab8f7ff 	blx	0xcee533e0
d00153e0:	d17f2800 	cmnle	pc, r0, lsl #16
d00153e4:	9a054601 	bls	0xd0166bf0
d00153e8:	f0014628 			; <UNDEFINED> instruction: 0xf0014628
d00153ec:	2800fd25 	stmdacs	r0, {r0, r2, r5, r8, sl, fp, ip, sp, lr, pc}
d00153f0:	8085f040 	addhi	pc, r5, r0, asr #32
d00153f4:	54e89b05 	strbtpl	r9, [r8], #2821	; 0xb05
d00153f8:	e07c2000 	rsbs	r2, ip, r0
d00153fc:	4478484e 	ldrbtmi	r4, [r8], #-2126	; 0xfffff7b2
d0015400:	484ee7c4 	stmdami	lr, {r2, r6, r7, r8, r9, sl, sp, lr, pc}^
d0015404:	e7a54478 			; <UNDEFINED> instruction: 0xe7a54478
d0015408:	35044b4d 	strcc	r4, [r4, #-2893]	; 0xfffff4b3
d001540c:	b134f8df 	teqlt	r4, pc	; <illegal shifter operand>	; <UNPREDICTABLE>
d0015410:	0a01f04f 	beq	0xd0091554
d0015414:	44fb447b 	ldrbtmi	r4, [fp], #1147	; 0x47b
d0015418:	4b4b601c 	blmi	0xd12ed490
d001541c:	9302447b 	movwls	r4, #9339	; 0x247b
d0015420:	447b4b4a 	ldrbtmi	r4, [fp], #-2890	; 0xfffff4b6
d0015424:	45569303 	ldrbmi	r9, [r6, #-771]	; 0xfffffcfd
d0015428:	2000d106 	andcs	sp, r0, r6, lsl #2
d001542c:	fde8f7ff 	stc2l	7, cr15, [r8, #1020]!	; 0x3fc
d0015430:	f480fab0 	vst3.32			; <UNDEFINED> instruction: 0xf480fab0
d0015434:	e7900964 	ldr	r0, [r0, r4, ror #18]
d0015438:	8000f8db 	ldrdhi	pc, [r0], -fp
d001543c:	9b02462f 	blls	0xd00a6d00
d0015440:	68383504 	ldmdavs	r8!, {r2, r8, sl, ip, sp}
d0015444:	2908eb03 	stmdbcs	r8, {r0, r1, r8, r9, fp, sp, lr, pc}
d0015448:	f7ff4649 			; <UNDEFINED> instruction: 0xf7ff4649
d001544c:	b950fd4b 	ldmdblt	r0, {r0, r1, r3, r6, r8, sl, fp, ip, sp, lr, pc}^
d0015450:	4a404c3f 	bmi	0xd1028554
d0015454:	683b447c 	ldmdavs	fp!, {r2, r3, r4, r5, r6, sl, lr}
d0015458:	f44f447a 	vst3.16	{d20-d22}, [pc :256], sl
d001545c:	462071c0 	strtmi	r7, [r0], -r0, asr #3
d0015460:	fcc8f001 	stc2l	0, cr15, [r8], {1}
d0015464:	2300e01e 	movwcs	lr, #30
d0015468:	0704eb08 	streq	lr, [r4, -r8, lsl #22]
d001546c:	3200f5c4 	andcc	pc, r0, #196, 10	; 0x31000000
d0015470:	93054648 	movwls	r4, #22088	; 0x5648
d0015474:	441f9b03 	ldrmi	r9, [pc], #-2819	; 0xd001547c
d0015478:	4639ab05 	ldrtmi	sl, [r9], -r5, lsl #22
d001547c:	fa68f7ff 	blx	0xd1a53480
d0015480:	b1884601 	orrlt	r4, r8, r1, lsl #12
d0015484:	d1021cc3 	smlabtle	r2, r3, ip, r1
d0015488:	44784833 	ldrbtmi	r4, [r8], #-2099	; 0xfffff7cd
d001548c:	4c33e762 	ldcmi	7, cr14, [r3], #-392	; 0xfffffe78
d0015490:	4a33464b 	bmi	0xd0ce6dc4
d0015494:	71c0f44f 	bicvc	pc, r0, pc, asr #8
d0015498:	9000447c 	andls	r4, r0, ip, ror r4
d001549c:	4620447a 			; <UNDEFINED> instruction: 0x4620447a
d00154a0:	fca8f001 	stc2	0, cr15, [r8], #4
d00154a4:	e7554620 	ldrb	r4, [r5, -r0, lsr #12]
d00154a8:	46389a05 	ldrtmi	r9, [r8], -r5, lsl #20
d00154ac:	fcc4f001 	stc2l	0, cr15, [r4], {1}
d00154b0:	4c2cb128 	stfmid	f3, [ip], #-160	; 0xffffff60
d00154b4:	4a2c464b 	bmi	0xd0b26de8
d00154b8:	447a447c 	ldrbtmi	r4, [sl], #-1148	; 0xfffffb84
d00154bc:	4b2be7cd 	blmi	0xd0b0f3f8
d00154c0:	0a01f10a 	beq	0xd00918f0
d00154c4:	447b9a05 	ldrbtmi	r9, [fp], #-2565	; 0xfffff5fb
d00154c8:	54b84414 	ldrtpl	r4, [r8], #1044	; 0x414
d00154cc:	7038f843 	eorsvc	pc, r8, r3, asr #16
d00154d0:	08c8eb03 	stmiaeq	r8, {r0, r1, r8, r9, fp, sp, lr, pc}^
d00154d4:	3000f8db 	ldrdcc	pc, [r0], -fp
d00154d8:	2004f8c8 	andcs	pc, r4, r8, asr #17
d00154dc:	f8cb3301 			; <UNDEFINED> instruction: 0xf8cb3301
d00154e0:	e7a03000 	str	r3, [r0, r0]!
d00154e4:	d10c2804 	tstle	ip, r4, lsl #16
d00154e8:	227d4921 	rsbscs	r4, sp, #540672	; 0x84000
d00154ec:	44794628 	ldrbtmi	r4, [r9], #-1576	; 0xfffff9d8
d00154f0:	f8b0f000 			; <UNDEFINED> instruction: 0xf8b0f000
d00154f4:	f7ff2001 			; <UNDEFINED> instruction: 0xf7ff2001
d00154f8:	4604fb7f 			; <UNDEFINED> instruction: 0x4604fb7f
d00154fc:	f06fe72d 			; <UNDEFINED> instruction: 0xf06fe72d
d0015500:	491c0003 	ldmdbmi	ip, {r0, r1}
d0015504:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d0015508:	2800fcaf 	stmdacs	r0, {r0, r1, r2, r3, r5, r7, sl, fp, ip, sp, lr, pc}
d001550c:	af25f43f 	svcge	0x0025f43f
d0015510:	2c00e772 	stccs	7, cr14, [r0], {114}	; 0x72
d0015514:	af35f47f 	svcge	0x0035f47f
d0015518:	e7376868 	ldr	r6, [r7, -r8, ror #16]!
d001551c:	ffffff26 			; <UNDEFINED> instruction: 0xffffff26
d0015520:	ffffff15 			; <UNDEFINED> instruction: 0xffffff15
d0015524:	fffffef2 			; <UNDEFINED> instruction: 0xfffffef2
d0015528:	00047598 	muleq	r4, r8, r5
d001552c:	000262d8 	ldrdeq	r6, [r2], -r8
d0015530:	fffffed0 			; <UNDEFINED> instruction: 0xfffffed0
d0015534:	00027544 	andeq	r7, r2, r4, asr #10
d0015538:	fffffe5e 			; <UNDEFINED> instruction: 0xfffffe5e
d001553c:	fffffe92 			; <UNDEFINED> instruction: 0xfffffe92
d0015540:	0002647c 	andeq	r6, r2, ip, ror r4
d0015544:	0002647a 	andeq	r6, r2, sl, ror r4
d0015548:	00026478 	andeq	r6, r2, r8, ror r4
d001554c:	000274f6 	strdeq	r7, [r2], -r6
d0015550:	000476d4 	ldrdeq	r7, [r4], -r4
d0015554:	fffffe56 			; <UNDEFINED> instruction: 0xfffffe56
d0015558:	fffffe3f 			; <UNDEFINED> instruction: 0xfffffe3f
d001555c:	00047690 	muleq	r4, r0, r6
d0015560:	fffffe4d 			; <UNDEFINED> instruction: 0xfffffe4d
d0015564:	00047670 	andeq	r7, r4, r0, ror r6
d0015568:	fffffe46 			; <UNDEFINED> instruction: 0xfffffe46
d001556c:	000273ce 	andeq	r7, r2, lr, asr #7
d0015570:	00000086 	andeq	r0, r0, r6, lsl #1
d0015574:	fffffe14 			; <UNDEFINED> instruction: 0xfffffe14

Disassembly of section .text.SBV2_CRC32:

d0010180 <.text.SBV2_CRC32>:
d0010180:	4401b530 	strmi	fp, [r1], #-1328	; 0xfffffad0
d0010184:	33fff04f 	mvnscc	pc, #79	; 0x4f
d0010188:	42884d08 	addmi	r4, r8, #8, 26	; 0x200
d001018c:	43d8d101 	bicsmi	sp, r8, #1073741824	; 0x40000000
d0010190:	f810bd30 			; <UNDEFINED> instruction: 0xf810bd30
d0010194:	40532b01 	subsmi	r2, r3, r1, lsl #22
d0010198:	f0132208 			; <UNDEFINED> instruction: 0xf0132208
d001019c:	bf180401 	svclt	0x00180401
d00101a0:	3a01462c 	bcc	0xd0061a58
d00101a4:	0353ea84 	cmpeq	r3, #132, 20	; 0x84000
d00101a8:	e7eed1f7 			; <UNDEFINED> instruction: 0xe7eed1f7
d00101ac:	edb88320 	ldc	3, cr8, [r8, #128]!	; 0x80

Disassembly of section .text.letter:

d00101b0 <.text.letter>:
d00101b0:	0320f020 	nopeq	{32}
d00101b4:	2b193b41 	blcs	0xd065eec0
d00101b8:	f1a0d904 			; <UNDEFINED> instruction: 0xf1a0d904
d00101bc:	4258035f 	subsmi	r0, r8, #2080374785	; 0x7c000001
d00101c0:	47704158 			; <UNDEFINED> instruction: 0x47704158
d00101c4:	47702001 	ldrbmi	r2, [r0, -r1]!

Disassembly of section .text.hex_digit:

d00101c8 <.text.hex_digit>:
d00101c8:	38304603 	ldmdacc	r0!, {r0, r1, r9, sl, lr}
d00101cc:	d9082809 	stmdble	r8, {r0, r3, fp, sp}
d00101d0:	0020f043 	eoreq	pc, r0, r3, asr #32
d00101d4:	0361f1a0 	msreq	SPSR_c, #160, 2	; 0x28
d00101d8:	d8012b05 	stmdale	r1, {r0, r2, r8, r9, fp, sp}
d00101dc:	47703857 			; <UNDEFINED> instruction: 0x47703857
d00101e0:	47702010 			; <UNDEFINED> instruction: 0x47702010

Disassembly of section .text.valid_api_name:

d00101e4 <.text.valid_api_name>:
d00101e4:	4602b510 			; <UNDEFINED> instruction: 0x4602b510
d00101e8:	f7ff7800 			; <UNDEFINED> instruction: 0xf7ff7800
d00101ec:	b170ffe1 	cmnlt	r0, r1, ror #31	; <UNPREDICTABLE>
d00101f0:	041ff102 	ldreq	pc, [pc], #-258	; 0xd00101f8
d00101f4:	1f01f812 	svcne	0x0001f812
d00101f8:	4608b151 			; <UNDEFINED> instruction: 0x4608b151
d00101fc:	ffd8f7ff 			; <UNDEFINED> instruction: 0xffd8f7ff
d0010200:	3930b910 	ldmdbcc	r0!, {r4, r8, fp, ip, sp, pc}
d0010204:	d8022909 	stmdale	r2, {r0, r3, r8, fp, sp}
d0010208:	d1f342a2 	mvnsle	r4, r2, lsr #5
d001020c:	bd102000 	ldclt	0, cr2, [r0, #-0]
d0010210:	e7fc2001 	ldrb	r2, [ip, r1]!

Disassembly of section .text.name_is.isra.0:

d0010214 <.text.name_is.isra.0>:
d0010214:	460db537 			; <UNDEFINED> instruction: 0x460db537
d0010218:	46104604 	ldrmi	r4, [r0], -r4, lsl #12
d001021c:	f0069201 			; <UNDEFINED> instruction: 0xf0069201
d0010220:	42a8fe21 	adcmi	pc, r8, #528	; 0x210
d0010224:	99014602 	stmdbls	r1, {r1, r9, sl, lr}
d0010228:	4620d107 	strtmi	sp, [r0], -r7, lsl #2
d001022c:	fa22f005 	blx	0xd08cc248
d0010230:	f080fab0 			; <UNDEFINED> instruction: 0xf080fab0
d0010234:	b0030940 	andlt	r0, r3, r0, asr #18
d0010238:	2000bd30 	andcs	fp, r0, r0, lsr sp
d001023c:	Address 0x00000000d001023c is out of bounds.


Disassembly of section .text.find_api_constant.isra.0.constprop.0:

d0010240 <.text.find_api_constant.isra.0.constprop.0>:
d0010240:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d0010244:	46074c0c 	strmi	r4, [r7], -ip, lsl #24
d0010248:	26004689 	strcs	r4, [r0], -r9, lsl #13
d001024c:	46a0447c 	sxtabmi	r4, r0, ip, ror #8
d0010250:	3070f8d8 	ldrsbtcc	pc, [r0], #-136	; 0xffffff78	; <UNPREDICTABLE>
d0010254:	d303429e 	movwle	r4, #12958	; 0x329e
d0010258:	46282500 	strtmi	r2, [r8], -r0, lsl #10
d001025c:	83f8e8bd 	mvnshi	lr, #12386304	; 0xbd0000
d0010260:	0594f604 	ldreq	pc, [r4, #1540]	; 0x604
d0010264:	46384649 	ldrtmi	r4, [r8], -r9, asr #12
d0010268:	462a3424 	strtmi	r3, [sl], -r4, lsr #8
d001026c:	ffd2f7ff 			; <UNDEFINED> instruction: 0xffd2f7ff
d0010270:	d1f22800 	mvnsle	r2, r0, lsl #16
d0010274:	e7eb3601 	strb	r3, [fp, r1, lsl #12]!
d0010278:	00007d74 	andeq	r7, r0, r4, ror sp

Disassembly of section .text.find_global.isra.0.constprop.0:

d001027c <.text.find_global.isra.0.constprop.0>:
d001027c:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d0010280:	46814e12 	pkhbtmi	r4, r1, r2, lsl #28
d0010284:	24004688 	strcs	r4, [r0], #-1672	; 0xfffff978
d0010288:	f506447e 			; <UNDEFINED> instruction: 0xf506447e
d001028c:	f506450e 			; <UNDEFINED> instruction: 0xf506450e
d0010290:	35544722 	ldrbcc	r4, [r4, #-1826]	; 0xfffff8de
d0010294:	683b3754 	ldmdavs	fp!, {r2, r4, r6, r8, r9, sl, ip, sp}
d0010298:	d302429c 	movwle	r4, #8860	; 0x229c
d001029c:	30fff04f 	rscscc	pc, pc, pc, asr #32
d00102a0:	f895e00e 			; <UNDEFINED> instruction: 0xf895e00e
d00102a4:	7a332025 	bvc	0xd0cd8340
d00102a8:	d10b429a 			; <UNDEFINED> instruction: 0xd10b429a
d00102ac:	4543686b 	strbmi	r6, [r3, #-2155]	; 0xfffff795
d00102b0:	4642d108 	strbmi	sp, [r2], -r8, lsl #2
d00102b4:	68284649 	stmdavs	r8!, {r0, r3, r6, r9, sl, lr}
d00102b8:	f9dcf005 			; <UNDEFINED> instruction: 0xf9dcf005
d00102bc:	4620b910 			; <UNDEFINED> instruction: 0x4620b910
d00102c0:	83f8e8bd 	mvnshi	lr, #12386304	; 0xbd0000
d00102c4:	35283401 	strcc	r3, [r8, #-1025]!	; 0xfffffbff
d00102c8:	bf00e7e5 	svclt	0x0000e7e5
d00102cc:	00007d38 	andeq	r7, r0, r8, lsr sp

Disassembly of section .text.escape_byte.isra.0.constprop.0:

d0010308 <.text.escape_byte.isra.0.constprop.0>:
d0010308:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d001030c:	461e681d 			; <UNDEFINED> instruction: 0x461e681d
d0010310:	f8dd4607 			; <UNDEFINED> instruction: 0xf8dd4607
d0010314:	1c6b8018 	stclne	0, cr8, [fp], #-96	; 0xffffffa0
d0010318:	782c6033 	stmdavc	ip!, {r0, r1, r4, r5, sp, lr}
d001031c:	d8112c78 	ldmdale	r1, {r3, r4, r5, r6, sl, fp, sp}
d0010320:	d8252c6d 	stmdale	r5!, {r0, r2, r3, r5, r6, sl, fp, sp}
d0010324:	d8492c3f 	stmdale	r9, {r0, r1, r2, r3, r4, r5, sl, fp, sp}^
d0010328:	d90b2c21 	stmdble	fp, {r0, r5, sl, fp, sp}
d001032c:	0022f1a4 	eoreq	pc, r2, r4, lsr #3
d0010330:	fc80fa5f 	stc2	10, cr15, [r0], {95}	; 0x5f	; <UNPREDICTABLE>
d0010334:	fa002001 	blx	0xd0018340
d0010338:	f8dff00c 			; <UNDEFINED> instruction: 0xf8dff00c
d001033c:	ea10c154 	b	0xd0440894
d0010340:	d1360f0c 	teqle	r6, ip, lsl #30
d0010344:	2c073c30 	stccs	12, cr3, [r7], {48}	; 0x30
d0010348:	4543d866 	strbmi	sp, [r3, #-2150]	; 0xfffff79a
d001034c:	786bd031 	stmdavc	fp!, {r0, r4, r5, ip, lr, pc}^
d0010350:	2b073b30 	blcs	0xd01df018
d0010354:	1ca8d82d 	stcne	8, cr13, [r8], #180	; 0xb4
d0010358:	45806030 	strmi	r6, [r0, #48]	; 0x30
d001035c:	f1a3786b 			; <UNDEFINED> instruction: 0xf1a3786b
d0010360:	eb030330 	bl	0xd00d1028
d0010364:	f04004c4 			; <UNDEFINED> instruction: 0xf04004c4
d0010368:	2cff8082 	ldclcs	0, cr8, [pc], #520	; 0xd0010578
d001036c:	e020d854 	eor	sp, r0, r4, asr r8
d0010370:	006ef1a4 	rsbeq	pc, lr, r4, lsr #3
d0010374:	d8e5280a 	stmiale	r5!, {r1, r3, fp, sp}^
d0010378:	0c08f20f 	sfmeq	f7, 1, [r8], {15}
d001037c:	0020f85c 	eoreq	pc, r0, ip, asr r8	; <UNPREDICTABLE>
d0010380:	47604484 	strbmi	r4, [r0, -r4, lsl #9]!
d0010384:	00000103 	andeq	r0, r0, r3, lsl #2
d0010388:	ffffffc1 			; <UNDEFINED> instruction: 0xffffffc1
d001038c:	ffffffc1 			; <UNDEFINED> instruction: 0xffffffc1
d0010390:	ffffffc1 			; <UNDEFINED> instruction: 0xffffffc1
d0010394:	0000002d 	andeq	r0, r0, sp, lsr #32
d0010398:	ffffffc1 			; <UNDEFINED> instruction: 0xffffffc1
d001039c:	00000089 	andeq	r0, r0, r9, lsl #1
d00103a0:	ffffffc1 			; <UNDEFINED> instruction: 0xffffffc1
d00103a4:	0000008d 	andeq	r0, r0, sp, lsl #1
d00103a8:	ffffffc1 			; <UNDEFINED> instruction: 0xffffffc1
d00103ac:	00000091 	muleq	r0, r1, r0
d00103b0:	4620240d 	strtmi	r2, [r0], -sp, lsl #8
d00103b4:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d00103b8:	e7fa2408 	ldrb	r2, [sl, r8, lsl #8]!
d00103bc:	005cf1a4 	subseq	pc, ip, r4, lsr #3
d00103c0:	fc80fa5f 	stc2	10, cr15, [r0], {95}	; 0x5f	; <UNPREDICTABLE>
d00103c4:	0f0af1bc 	svceq	0x000af1bc
d00103c8:	280ad8bc 	stmdacs	sl, {r2, r3, r4, r5, r7, fp, ip, lr, pc}
d00103cc:	f20fd8ba 	vtst.8	d13, d31, d26
d00103d0:	f85c0c0c 			; <UNDEFINED> instruction: 0xf85c0c0c
d00103d4:	44840020 	strmi	r0, [r4], #32
d00103d8:	bf004760 	svclt	0x00004760
d00103dc:	ffffffd7 			; <UNDEFINED> instruction: 0xffffffd7
d00103e0:	ffffff69 			; <UNDEFINED> instruction: 0xffffff69
d00103e4:	ffffff69 			; <UNDEFINED> instruction: 0xffffff69
d00103e8:	ffffff69 			; <UNDEFINED> instruction: 0xffffff69
d00103ec:	ffffff69 			; <UNDEFINED> instruction: 0xffffff69
d00103f0:	000000af 	andeq	r0, r0, pc, lsr #1
d00103f4:	ffffffdd 			; <UNDEFINED> instruction: 0xffffffdd
d00103f8:	ffffff69 			; <UNDEFINED> instruction: 0xffffff69
d00103fc:	ffffff69 			; <UNDEFINED> instruction: 0xffffff69
d0010400:	ffffff69 			; <UNDEFINED> instruction: 0xffffff69
d0010404:	0000002d 	andeq	r0, r0, sp, lsr #32
d0010408:	e7d2240c 	ldrb	r2, [r2, ip, lsl #8]
d001040c:	e7d02409 	ldrb	r2, [r0, r9, lsl #8]
d0010410:	e7ce240b 	strb	r2, [lr, fp, lsl #8]
d0010414:	d1064543 	tstle	r6, r3, asr #10
d0010418:	447b4b1e 	ldrbtmi	r4, [fp], #-2846	; 0xfffff4e2
d001041c:	b9ec6d1c 	stmiblt	ip!, {r2, r3, r4, r8, sl, fp, sp, lr}^
d0010420:	4478481d 	ldrbtmi	r4, [r8], #-2077	; 0xfffff7e3
d0010424:	7868e01e 	stmdavc	r8!, {r1, r2, r3, r4, sp, lr, pc}^
d0010428:	fecef7ff 	mcr2	7, 6, pc, cr14, cr15, {7}	; <UNPREDICTABLE>
d001042c:	d0f32810 	rscsle	r2, r3, r0, lsl r8
d0010430:	68352400 	ldmdavs	r5!, {sl, sp}
d0010434:	d0bc45a8 	adcsle	r4, ip, r8, lsr #11
d0010438:	f7ff7828 			; <UNDEFINED> instruction: 0xf7ff7828
d001043c:	2810fec5 	ldmdacs	r0, {r0, r2, r6, r7, r9, sl, fp, ip, sp, lr, pc}
d0010440:	1c6bd0b7 	stclne	0, cr13, [fp], #-732	; 0xfffffd24
d0010444:	60330124 	eorsvs	r0, r3, r4, lsr #2
d0010448:	f7ff7828 			; <UNDEFINED> instruction: 0xf7ff7828
d001044c:	4404febd 	strmi	pc, [r4], #-3773	; 0xfffff143
d0010450:	d9ee2cff 	stmible	lr!, {r0, r1, r2, r3, r4, r5, r6, r7, sl, fp, sp}^
d0010454:	447b4b11 	ldrbtmi	r4, [fp], #-2833	; 0xfffff4ef
d0010458:	b10c6d1c 	tstlt	ip, ip, lsl sp
d001045c:	e7a82400 	str	r2, [r8, r0, lsl #8]!
d0010460:	4478480f 	ldrbtmi	r4, [r8], #-2063	; 0xfffff7f1
d0010464:	655f6518 	ldrbvs	r6, [pc, #-1304]	; 0xd000ff54
d0010468:	65da6599 	ldrbvs	r6, [sl, #1433]	; 0x599
d001046c:	78abe7a1 	stmiavc	fp!, {r0, r5, r7, r8, r9, sl, sp, lr, pc}
d0010470:	2b073b30 	blcs	0xd01df138
d0010474:	af79f63f 	svcge	0x0079f63f
d0010478:	60331ceb 	eorsvs	r1, r3, fp, ror #25
d001047c:	3b3078ab 	blcc	0xd0c2e730
d0010480:	04c4eb03 	strbeq	lr, [r4], #2819	; 0xb03
d0010484:	240ae771 	strcs	lr, [sl], #-1905	; 0xfffff88f
d0010488:	2407e793 	strcs	lr, [r7], #-1939	; 0xfffff86d
d001048c:	bf00e791 	svclt	0x0000e791
d0010490:	20000021 	andcs	r0, r0, r1, lsr #32
d0010494:	00007ba6 	andeq	r7, r0, r6, lsr #23
d0010498:	fffffec2 			; <UNDEFINED> instruction: 0xfffffec2
d001049c:	00007b6a 	andeq	r7, r0, sl, ror #22
d00104a0:	fffffe6a 			; <UNDEFINED> instruction: 0xfffffe6a

Disassembly of section .text.here.constprop.0:

d00104a4 <.text.here.constprop.0>:
d00104a4:	21004b0d 	tstcs	r0, sp, lsl #22
d00104a8:	e92d447b 	push	{r0, r1, r3, r4, r5, r6, sl, lr}
d00104ac:	681a41f0 	ldmdavs	sl, {r4, r5, r6, r7, r8, lr}
d00104b0:	68dd4604 	ldmvs	sp, {r2, r9, sl, lr}^
d00104b4:	f8d33004 			; <UNDEFINED> instruction: 0xf8d33004
d00104b8:	44158010 	ldrmi	r8, [r5], #-16
d00104bc:	695f2218 	ldmdbvs	pc, {r3, r4, r9, sp}^	; <UNPREDICTABLE>
d00104c0:	f0057a1e 			; <UNDEFINED> instruction: 0xf0057a1e
d00104c4:	f44ff8b9 	vst2.32	{d31-d32}, [pc :256], r9
d00104c8:	46207380 	strtmi	r7, [r0], -r0, lsl #7
d00104cc:	f8c46025 			; <UNDEFINED> instruction: 0xf8c46025
d00104d0:	6127800c 			; <UNDEFINED> instruction: 0x6127800c
d00104d4:	76266163 	strtvc	r6, [r6], -r3, ror #2
d00104d8:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d00104dc:	00007b18 	andeq	r7, r0, r8, lsl fp

Disassembly of section .text.peek.constprop.0:

d00104e0 <.text.peek.constprop.0>:
d00104e0:	447b4b05 	ldrbtmi	r4, [fp], #-2821	; 0xfffff4fb
d00104e4:	441068da 	ldrmi	r6, [r0], #-2266	; 0xfffff726
d00104e8:	4290685a 	addsmi	r6, r0, #5898240	; 0x5a0000
d00104ec:	681bbf3a 	ldmdavs	fp, {r1, r3, r4, r5, r8, r9, sl, fp, ip, sp, pc}
d00104f0:	20005c18 	andcs	r5, r0, r8, lsl ip
d00104f4:	bf004770 	svclt	0x00004770
d00104f8:	00007ade 	ldrdeq	r7, [r0], -lr

Disassembly of section .text.read_char.constprop.0:

d00104fc <.text.read_char.constprop.0>:
d00104fc:	4b12b508 	blmi	0xd04bd924
d0010500:	68da447b 	ldmvs	sl, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0010504:	428a6859 	addmi	r6, sl, #5832704	; 0x590000
d0010508:	6819d01b 	ldmdavs	r9, {r0, r1, r3, r4, ip, lr, pc}
d001050c:	60d81c50 	sbcsvs	r1, r8, r0, asr ip
d0010510:	290a5c89 	stmdbcs	sl, {r0, r3, r7, sl, fp, ip, lr}
d0010514:	290dd006 	stmdbcs	sp, {r1, r2, ip, lr, pc}
d0010518:	2000d10d 	andcs	sp, r0, sp, lsl #2
d001051c:	ffe0f7ff 			; <UNDEFINED> instruction: 0xffe0f7ff
d0010520:	d008280a 	andle	r2, r8, sl, lsl #16
d0010524:	447b4b09 	ldrbtmi	r4, [fp], #-2825	; 0xfffff4f7
d0010528:	3201691a 	andcc	r6, r1, #425984	; 0x68000
d001052c:	2201611a 	andcs	r6, r1, #-2147483642	; 0x80000006
d0010530:	4608615a 			; <UNDEFINED> instruction: 0x4608615a
d0010534:	4a06bd08 	bmi	0xd01bf95c
d0010538:	6953447a 	ldmdbvs	r3, {r1, r3, r4, r5, r6, sl, lr}^
d001053c:	61533301 	cmpvs	r3, r1, lsl #6
d0010540:	2100e7f7 	strdcs	lr, [r0, -r7]
d0010544:	bf00e7f5 	svclt	0x0000e7f5
d0010548:	00007ac0 	andeq	r7, r0, r0, asr #21
d001054c:	00007a9a 	muleq	r0, sl, sl
d0010550:	00007a88 	andeq	r7, r0, r8, lsl #21

Disassembly of section .text.advance.constprop.0:

d00106d0 <.text.advance.constprop.0>:
d00106d0:	4ff0e92d 	svcmi	0x00f0e92d
d00106d4:	6614f8df 			; <UNDEFINED> instruction: 0x6614f8df
d00106d8:	447eb09d 	ldrbtmi	fp, [lr], #-157	; 0xffffff63
d00106dc:	0534f106 	ldreq	pc, [r4, #-262]!	; 0xfffffefa
d00106e0:	0418f106 	ldreq	pc, [r8], #-262	; 0xfffffefa
d00106e4:	c40fcd0f 	strgt	ip, [pc], #-3343	; 0xd00106ec
d00106e8:	0007e895 	muleq	r7, r5, r8
d00106ec:	e8846d33 	stm	r4, {r0, r1, r4, r5, r8, sl, fp, sp, lr}
d00106f0:	2b000007 	blcs	0xd0010714
d00106f4:	82e5f040 	rschi	pc, r5, #64	; 0x40
d00106f8:	45f4f8df 	ldrbmi	pc, [r4, #2271]!	; 0x8df	; <UNPREDICTABLE>
d00106fc:	55f4f8df 	ldrbpl	pc, [r4, #2271]!	; 0x8df	; <UNPREDICTABLE>
d0010700:	447d447c 	ldrbtmi	r4, [sp], #-1148	; 0xfffffb84
d0010704:	f7ff2000 			; <UNDEFINED> instruction: 0xf7ff2000
d0010708:	2820feeb 	stmdacs	r0!, {r0, r1, r3, r5, r6, r7, r9, sl, fp, ip, sp, lr, pc}
d001070c:	f1a0d003 			; <UNDEFINED> instruction: 0xf1a0d003
d0010710:	2b040309 	blcs	0xd011133c
d0010714:	f7ffd802 			; <UNDEFINED> instruction: 0xf7ffd802
d0010718:	e7f3fef1 	udf	#16353	; 0x3fe1
d001071c:	d12d282f 			; <UNDEFINED> instruction: 0xd12d282f
d0010720:	f7ff2001 			; <UNDEFINED> instruction: 0xf7ff2001
d0010724:	282ffedd 	stmdacs	pc!, {r0, r2, r3, r4, r6, r7, r9, sl, fp, ip, sp, lr, pc}	; <UNPREDICTABLE>
d0010728:	6869d10d 	stmdavs	r9!, {r0, r2, r3, r8, ip, lr, pc}^
d001072c:	68ee2000 	stmiavs	lr!, {sp}^
d0010730:	fed6f7ff 	mrc2	7, 6, pc, cr6, cr15, {7}
d0010734:	d0e5428e 	rscle	r4, r5, lr, lsl #5
d0010738:	d0e3280a 	rscle	r2, r3, sl, lsl #16
d001073c:	d0e1280d 	rscle	r2, r1, sp, lsl #16
d0010740:	fedcf7ff 	mrc2	7, 6, pc, cr12, cr15, {7}
d0010744:	282ae7f1 	stmdacs	sl!, {r0, r4, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d0010748:	a815d118 	ldmdage	r5, {r3, r4, r8, ip, lr, pc}
d001074c:	feaaf7ff 	mcr2	7, 5, pc, cr10, cr15, {7}	; <UNPREDICTABLE>
d0010750:	fed4f7ff 	mrc2	7, 6, pc, cr4, cr15, {7}
d0010754:	fed2f7ff 	mrc2	7, 6, pc, cr2, cr15, {7}
d0010758:	686368e2 	stmdavs	r3!, {r1, r5, r6, r7, fp, sp, lr}^
d001075c:	f000429a 			; <UNDEFINED> instruction: 0xf000429a
d0010760:	200082a4 	andcs	r8, r0, r4, lsr #5
d0010764:	febcf7ff 	mrc2	7, 5, pc, cr12, cr15, {7}
d0010768:	d1f3282a 	mvnsle	r2, sl, lsr #16
d001076c:	f7ff2001 			; <UNDEFINED> instruction: 0xf7ff2001
d0010770:	282ffeb7 	stmdacs	pc!, {r0, r1, r2, r4, r5, r7, r9, sl, fp, ip, sp, lr, pc}	; <UNPREDICTABLE>
d0010774:	f7ffd1ee 			; <UNDEFINED> instruction: 0xf7ffd1ee
d0010778:	e7ccfec1 	strb	pc, [ip, r1, asr #29]	; <UNPREDICTABLE>
d001077c:	ad08ac07 	stcge	12, cr10, [r8, #-28]	; 0xffffffe4
d0010780:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010784:	f8dffe8f 			; <UNDEFINED> instruction: 0xf8dffe8f
d0010788:	f8dd2570 			; <UNDEFINED> instruction: 0xf8dd2570
d001078c:	447aa01c 	ldrbtmi	sl, [sl], #-28	; 0xffffffe4
d0010790:	8034f89d 	mlashi	r4, sp, r8, pc	; <UNPREDICTABLE>
d0010794:	685368d1 	ldmdavs	r3, {r0, r4, r6, r7, fp, sp, lr}^
d0010798:	e8954299 	ldm	r5, {r0, r3, r4, r7, r9, lr}
d001079c:	d10402e0 	smlattle	r4, r0, r2, r0
d00107a0:	b030f8dd 	ldrsbtlt	pc, [r0], -sp	; <UNPREDICTABLE>
d00107a4:	0c38f10d 	ldfeqd	f7, [r8], #-52	; 0xffffffcc
d00107a8:	9203e18c 	andls	lr, r3, #140, 2	; 0x23
d00107ac:	fea6f7ff 	mcr2	7, 5, pc, cr6, cr15, {7}	; <UNPREDICTABLE>
d00107b0:	46832823 	strmi	r2, [r3], r3, lsr #16
d00107b4:	f0409a03 			; <UNDEFINED> instruction: 0xf0409a03
d00107b8:	f10d80b0 			; <UNDEFINED> instruction: 0xf10d80b0
d00107bc:	cc0f0c54 	stcgt	12, cr0, [pc], {84}	; 0x54
d00107c0:	000fe8ac 	andeq	lr, pc, ip, lsr #17
d00107c4:	0007e894 	muleq	r7, r4, r8
d00107c8:	0007e88c 	andeq	lr, r7, ip, lsl #17
d00107cc:	f7ff2000 			; <UNDEFINED> instruction: 0xf7ff2000
d00107d0:	2820fe87 	stmdacs	r0!, {r0, r1, r2, r7, r9, sl, fp, ip, sp, lr, pc}
d00107d4:	2809d01c 	stmdacs	r9, {r2, r3, r4, ip, lr, pc}
d00107d8:	f8dfd01a 			; <UNDEFINED> instruction: 0xf8dfd01a
d00107dc:	2400b520 	strcs	fp, [r0], #-1312	; 0xfffffae0
d00107e0:	f7ff44fb 			; <UNDEFINED> instruction: 0xf7ff44fb
d00107e4:	f81bfe8b 			; <UNDEFINED> instruction: 0xf81bfe8b
d00107e8:	42983b01 	addsmi	r3, r8, #1024	; 0x400
d00107ec:	f8dfd013 			; <UNDEFINED> instruction: 0xf8dfd013
d00107f0:	447b3510 	ldrbtmi	r3, [fp], #-1296	; 0xfffffaf0
d00107f4:	2a006d1a 	bcs	0xd002bc64
d00107f8:	8263f040 	rsbhi	pc, r3, #64	; 0x40
d00107fc:	2504f8df 	strcs	pc, [r4, #-2271]	; 0xfffff721
d0010800:	651a447a 	ldrvs	r4, [sl, #-1146]	; 0xfffffb86
d0010804:	f8c3655f 			; <UNDEFINED> instruction: 0xf8c3655f
d0010808:	f8c39058 			; <UNDEFINED> instruction: 0xf8c39058
d001080c:	e258805c 	subs	r8, r8, #92	; 0x5c
d0010810:	fe74f7ff 	mrc2	7, 3, pc, cr4, cr15, {7}
d0010814:	3401e7da 	strcc	lr, [r1], #-2010	; 0xfffff826
d0010818:	d1e22c07 	mvnle	r2, r7, lsl #24
d001081c:	f7ff2000 			; <UNDEFINED> instruction: 0xf7ff2000
d0010820:	2820fe5f 	stmdacs	r0!, {r0, r1, r2, r3, r4, r6, r9, sl, fp, ip, sp, lr, pc}
d0010824:	2809d022 	stmdacs	r9, {r1, r5, ip, lr, pc}
d0010828:	f7ffd020 			; <UNDEFINED> instruction: 0xf7ffd020
d001082c:	283cfe67 	ldmdacs	ip!, {r0, r1, r2, r5, r6, r9, sl, fp, ip, sp, lr, pc}
d0010830:	f0404604 			; <UNDEFINED> instruction: 0xf0404604
d0010834:	243e8248 	ldrtcs	r8, [lr], #-584	; 0xfffffdb8
d0010838:	34ccf8df 	strbcc	pc, [ip], #2271	; 0x8df	; <UNPREDICTABLE>
d001083c:	0b00f04f 	bleq	0xd004c980
d0010840:	9303447b 	movwls	r4, #13435	; 0x347b
d0010844:	f7ff2000 			; <UNDEFINED> instruction: 0xf7ff2000
d0010848:	9b03fe4b 	blls	0xd011017c
d001084c:	2b01f813 	blcs	0xd008e8a0
d0010850:	93034290 	movwls	r4, #12944	; 0x3290
d0010854:	f8dfd00d 			; <UNDEFINED> instruction: 0xf8dfd00d
d0010858:	447b34b4 	ldrbtmi	r3, [fp], #-1204	; 0xfffffb4c
d001085c:	2a006d1a 	bcs	0xd002bccc
d0010860:	822ff040 	eorhi	pc, pc, #64	; 0x40
d0010864:	24a8f8df 	strtcs	pc, [r8], #2271	; 0x8df
d0010868:	e7ca447a 			; <UNDEFINED> instruction: 0xe7ca447a
d001086c:	fe46f7ff 	mcr2	7, 2, pc, cr6, cr15, {7}	; <UNPREDICTABLE>
d0010870:	f10be7d4 			; <UNDEFINED> instruction: 0xf10be7d4
d0010874:	f7ff0b01 			; <UNDEFINED> instruction: 0xf7ff0b01
d0010878:	f1bbfe41 			; <UNDEFINED> instruction: 0xf1bbfe41
d001087c:	d1e10f06 	mvnle	r0, r6, lsl #30
d0010880:	fe3cf7ff 	mrc2	7, 1, pc, cr12, cr15, {7}
d0010884:	d1e642a0 	mvnle	r4, r0, lsr #5
d0010888:	f7ffe001 			; <UNDEFINED> instruction: 0xf7ffe001
d001088c:	2000fe37 	andcs	pc, r0, r7, lsr lr	; <UNPREDICTABLE>
d0010890:	fe26f7ff 	mcr2	7, 1, pc, cr6, cr15, {7}	; <UNPREDICTABLE>
d0010894:	d0f82820 	rscsle	r2, r8, r0, lsr #16
d0010898:	d0f62809 	rscsle	r2, r6, r9, lsl #16
d001089c:	3474f8df 	ldrbtcc	pc, [r4], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d00108a0:	68da447b 	ldmvs	sl, {r0, r1, r3, r4, r5, r6, sl, lr}^
d00108a4:	429a685b 	addsmi	r6, sl, #5963776	; 0x5b0000
d00108a8:	280dd00a 	stmdacs	sp, {r1, r3, ip, lr, pc}
d00108ac:	280ad008 	stmdacs	sl, {r3, ip, lr, pc}
d00108b0:	282fd006 	stmdacs	pc!, {r1, r2, ip, lr, pc}	; <UNPREDICTABLE>
d00108b4:	2001d1cf 	andcs	sp, r1, pc, asr #3
d00108b8:	fe12f7ff 	mrc2	7, 0, pc, cr2, cr15, {7}
d00108bc:	d1ca282f 	bicle	r2, sl, pc, lsr #16
d00108c0:	7b83f44f 	blvc	0xce10da04
d00108c4:	0c54f10d 	ldfeqp	f7, [r4], {13}
d00108c8:	9064f8cd 	rsbls	pc, r4, sp, asr #17
d00108cc:	f8cdac0e 			; <UNDEFINED> instruction: 0xf8cdac0e
d00108d0:	f88db068 			; <UNDEFINED> instruction: 0xf88db068
d00108d4:	f8cd806c 			; <UNDEFINED> instruction: 0xf8cd806c
d00108d8:	9516a054 	ldrls	sl, [r6, #-84]	; 0xffffffac
d00108dc:	97189617 			; <UNDEFINED> instruction: 0x97189617
d00108e0:	000fe8bc 			; <UNDEFINED> instruction: 0x000fe8bc
d00108e4:	e89cc40f 	ldm	ip, {r0, r1, r2, r3, sl, lr, pc}
d00108e8:	e8840007 	stm	r4, {r0, r1, r2}
d00108ec:	f8df0007 			; <UNDEFINED> instruction: 0xf8df0007
d00108f0:	f88d4428 			; <UNDEFINED> instruction: 0xf88d4428
d00108f4:	447c8050 	ldrbtmi	r8, [ip], #-80	; 0xffffffb0
d00108f8:	a50ee9cd 	strge	lr, [lr, #-2509]	; 0xfffff633
d00108fc:	3434ad0e 	ldrtcc	sl, [r4], #-3342	; 0xfffff2f2
d0010900:	9b12e9cd 	blls	0xd04cb03c
d0010904:	6710e9cd 	ldrvs	lr, [r0, -sp, asr #19]
d0010908:	c40fcd0f 	strgt	ip, [pc], #-3343	; 0xd0010910
d001090c:	0007e895 	muleq	r7, r5, r8
d0010910:	0007e884 	andeq	lr, r7, r4, lsl #17
d0010914:	e8bdb01d 	pop	{r0, r2, r3, r4, ip, sp, pc}
d0010918:	92048ff0 	andls	r8, r4, #240, 30	; 0x3c0
d001091c:	fc48f7ff 	mcrr2	7, 15, pc, r8, cr15	; <UNPREDICTABLE>
d0010920:	b9809003 	stmiblt	r0, {r0, r1, ip, pc}
d0010924:	0330f1ab 	teqeq	r0, #-1073741782	; 0xc000002a	; <UNPREDICTABLE>
d0010928:	2b099a04 	blcs	0xd0277140
d001092c:	f2009304 	vcgt.s8	d9, d0, d4
d0010930:	f1bb80d7 			; <UNDEFINED> instruction: 0xf1bb80d7
d0010934:	f0000f30 			; <UNDEFINED> instruction: 0xf0000f30
d0010938:	f04f81ca 			; <UNDEFINED> instruction: 0xf04f81ca
d001093c:	9e040b0a 	vmlals.f64	d0, d4, d10
d0010940:	f7ffe076 			; <UNDEFINED> instruction: 0xf7ffe076
d0010944:	2000fddb 	ldrdcs	pc, [r0], -fp
d0010948:	fdcaf7ff 	stc2l	7, cr15, [sl, #1020]	; 0x3fc
d001094c:	f7ff4602 			; <UNDEFINED> instruction: 0xf7ff4602
d0010950:	2800fc2f 	stmdacs	r0, {r0, r1, r2, r3, r5, sl, fp, ip, sp, lr, pc}
d0010954:	3a30d1f5 	bcc	0xd0c45130
d0010958:	d9f22a09 	ldmible	r2!, {r0, r3, r9, fp, sp}^
d001095c:	46834bef 	strmi	r4, [r3], pc, ror #23
d0010960:	681d447b 	ldmdavs	sp, {r0, r1, r3, r4, r5, r6, sl, lr}
d0010964:	441d68db 	ldrmi	r6, [sp], #-2267	; 0xfffff725
d0010968:	eba54bed 	bl	0xce963924
d001096c:	447b050a 	ldrbtmi	r0, [fp], #-1290	; 0xfffffaf6
d0010970:	2b04f853 	blcs	0xd014eac4
d0010974:	46504629 	ldrbmi	r4, [r0], -r9, lsr #12
d0010978:	93049303 	movwls	r9, #17155	; 0x4303
d001097c:	fc4af7ff 	mcrr2	7, 15, pc, sl, cr15	; <UNPREDICTABLE>
d0010980:	b1289b03 			; <UNDEFINED> instruction: 0xb1289b03
d0010984:	1b07f20b 	blne	0xd020d1b8
d0010988:	f8cd9508 			; <UNDEFINED> instruction: 0xf8cd9508
d001098c:	e709b030 	smladx	r9, r0, r0, fp
d0010990:	0b01f10b 	bleq	0xd008cdc4
d0010994:	0f0cf1bb 	svceq	0x000cf1bb
d0010998:	4be2d1ea 	blmi	0xcf8c5148
d001099c:	447b4683 	ldrbtmi	r4, [fp], #-1667	; 0xfffff97d
d00109a0:	2b04f853 	blcs	0xd014eaf4
d00109a4:	46504629 	ldrbmi	r4, [r0], -r9, lsr #12
d00109a8:	93049303 	movwls	r9, #17155	; 0x4303
d00109ac:	fc32f7ff 	ldc2	7, cr15, [r2], #-1020	; 0xfffffc04
d00109b0:	b1409b03 	cmplt	r0, r3, lsl #22
d00109b4:	447b4bdc 	ldrbtmi	r4, [fp], #-3036	; 0xfffff424
d00109b8:	2a006d1a 	bcs	0xd002be28
d00109bc:	8181f040 	orrhi	pc, r1, r0, asr #32
d00109c0:	447a4ada 	ldrbtmi	r4, [sl], #-2778	; 0xfffff526
d00109c4:	f10be71d 			; <UNDEFINED> instruction: 0xf10be71d
d00109c8:	f1bb0b01 			; <UNDEFINED> instruction: 0xf1bb0b01
d00109cc:	d1e70f20 	mvnle	r0, r0, lsr #30
d00109d0:	1b01f240 	blne	0xd008d2d8
d00109d4:	e7d89508 	ldrb	r9, [r8, r8, lsl #10]
d00109d8:	f7ff9205 			; <UNDEFINED> instruction: 0xf7ff9205
d00109dc:	9803fd8f 	stmdals	r3, {r0, r1, r2, r3, r7, r8, sl, fp, ip, sp, lr, pc}
d00109e0:	fd7ef7ff 	ldc2l	7, cr15, [lr, #-1020]!	; 0xfffffc04
d00109e4:	fbf0f7ff 	blx	0xcfc4e9ea
d00109e8:	46832810 	pkhbtmi	r2, r3, r0, lsl #16
d00109ec:	d15c9a05 	cmple	ip, r5, lsl #20
d00109f0:	2b006d13 	blcs	0xd002be44
d00109f4:	4bced1a3 	blmi	0xcf3c5088
d00109f8:	447b6557 	ldrbtmi	r6, [fp], #-1367	; 0xfffffaa9
d00109fc:	9058f8c2 	subsls	pc, r8, r2, asr #17
d0010a00:	805cf8c2 	subshi	pc, ip, r2, asr #17
d0010a04:	e79a6513 			; <UNDEFINED> instruction: 0xe79a6513
d0010a08:	fd78f7ff 	ldc2l	7, cr15, [r8, #-1020]!	; 0xfffffc04
d0010a0c:	fbdcf7ff 	blx	0xcf74ea12
d0010a10:	fbb343c3 	blx	0xcece1926
d0010a14:	42b3f3fb 	adcsmi	pc, r3, #-335544317	; 0xec000003
d0010a18:	4bc6d208 	blmi	0xcf1c5240
d0010a1c:	6d1a447b 	cfldrsvs	mvf4, [sl, #-492]	; 0xfffffe14
d0010a20:	f0402a00 			; <UNDEFINED> instruction: 0xf0402a00
d0010a24:	4ac4814e 	bmi	0xcf130f64
d0010a28:	e6ea447a 	uxtab	r4, sl, sl, ror #8
d0010a2c:	060bfb06 	streq	pc, [fp], -r6, lsl #22
d0010a30:	f7ff2000 			; <UNDEFINED> instruction: 0xf7ff2000
d0010a34:	4602fd55 			; <UNDEFINED> instruction: 0x4602fd55
d0010a38:	fbc6f7ff 	blx	0xcf1cea3e
d0010a3c:	d8e34583 	stmiale	r3!, {r0, r1, r7, r8, sl, lr}^
d0010a40:	0320f042 	nopeq	{66}	; 0x42
d0010a44:	93032b75 	movwls	r2, #15221	; 0x3b75
d0010a48:	f7ffd101 			; <UNDEFINED> instruction: 0xf7ffd101
d0010a4c:	2000fd57 	andcs	pc, r0, r7, asr sp	; <UNPREDICTABLE>
d0010a50:	fd46f7ff 	stc2l	7, cr15, [r6, #-1020]	; 0xfffffc04
d0010a54:	0330f1a0 	teqeq	r0, #160, 2	; 0x28	; <UNPREDICTABLE>
d0010a58:	aa0e4601 	bge	0xd03a2264
d0010a5c:	d90c2b09 	stmdble	ip, {r0, r3, r8, r9, fp, sp}
d0010a60:	fba6f7ff 	blx	0xce9cea66
d0010a64:	292eb948 	stmdbcs	lr!, {r3, r6, r8, fp, ip, sp, pc}
d0010a68:	9b03d007 	blls	0xd0104a8c
d0010a6c:	d0312b75 	eorsle	r2, r1, r5, ror fp
d0010a70:	0f0af1bb 	svceq	0x000af1bb
d0010a74:	2e00d11c 	mcrcs	1, 0, sp, cr0, cr12, {0}
d0010a78:	4bb0da2f 	blmi	0xcec4733c
d0010a7c:	6d19447b 	cfldrsvs	mvf4, [r9, #-492]	; 0xfffffe14
d0010a80:	49afb939 	stmibmi	pc!, {r0, r3, r4, r5, r8, fp, ip, sp, pc}	; <UNPREDICTABLE>
d0010a84:	4479655f 	ldrbtmi	r6, [r9], #-1375	; 0xfffffaa1
d0010a88:	9058f8c3 	subsls	pc, r8, r3, asr #17
d0010a8c:	805cf8c3 	subshi	pc, ip, r3, asr #17
d0010a90:	46106519 			; <UNDEFINED> instruction: 0x46106519
d0010a94:	fd06f7ff 	stc2	7, cr15, [r6, #-1020]	; 0xfffffc04
d0010a98:	8050f89d 			; <UNDEFINED> instruction: 0x8050f89d
d0010a9c:	a50ee9dd 	strge	lr, [lr, #-2525]	; 0xfffff623
d0010aa0:	6710e9dd 			; <UNDEFINED> instruction: 0x6710e9dd
d0010aa4:	9b12e9dd 	blls	0xd04cb220
d0010aa8:	f04fe721 			; <UNDEFINED> instruction: 0xf04fe721
d0010aac:	e7460b10 	smlald	r0, r6, r0, fp
d0010ab0:	f2402e00 	vceq.f32	d18, d0, d0
d0010ab4:	bfa81b03 	svclt	0x00a81b03
d0010ab8:	7b81f44f 	blvc	0xce08dbfc
d0010abc:	96094694 			; <UNDEFINED> instruction: 0x96094694
d0010ac0:	b030f8cd 	eorslt	pc, r0, sp, asr #17
d0010ac4:	e8accc0f 	stmia	ip!, {r0, r1, r2, r3, sl, fp, lr, pc}
d0010ac8:	e894000f 	ldm	r4, {r0, r1, r2, r3}
d0010acc:	e88c0007 	stm	ip, {r0, r1, r2}
d0010ad0:	e70c0007 	str	r0, [ip, -r7]
d0010ad4:	1b03f240 	blne	0xd010d3dc
d0010ad8:	f44fe7f0 	vst1.64	{d30}, [pc :256], r0
d0010adc:	e7ed7b81 	strb	r7, [sp, r1, lsl #23]!
d0010ae0:	0f22f1bb 	svceq	0x0022f1bb
d0010ae4:	f1bbd002 			; <UNDEFINED> instruction: 0xf1bbd002
d0010ae8:	d1780f27 	cmnle	r8, r7, lsr #30
d0010aec:	f2424a95 	vpmin.s8	d20, d18, d5
d0010af0:	447a4501 	ldrbtmi	r4, [sl], #-1281	; 0xfffffaff
d0010af4:	93036813 	movwls	r6, #14355	; 0x3813
d0010af8:	930468d3 	movwls	r6, #18643	; 0x48d3
d0010afc:	685168d0 	ldmdavs	r1, {r4, r6, r7, fp, sp, lr}^
d0010b00:	d05e4288 	subsle	r4, lr, r8, lsl #5
d0010b04:	f7ff9205 			; <UNDEFINED> instruction: 0xf7ff9205
d0010b08:	4583fcf9 	strmi	pc, [r3, #3321]	; 0xcf9
d0010b0c:	d14c9a05 	cmple	ip, r5, lsl #20
d0010b10:	f1bb9904 			; <UNDEFINED> instruction: 0xf1bb9904
d0010b14:	68d50f22 	ldmvs	r5, {r1, r5, r8, r9, sl, fp}^
d0010b18:	eb039b03 	bl	0xd00f772c
d0010b1c:	f1050a01 			; <UNDEFINED> instruction: 0xf1050a01
d0010b20:	681531ff 	ldmdavs	r5, {r0, r1, r2, r3, r4, r5, r6, r7, r8, ip, sp}
d0010b24:	eba5440d 	bl	0xce961b60
d0010b28:	d03b050a 	eorsle	r0, fp, sl, lsl #10
d0010b2c:	0b05eb0a 	bleq	0xd018b75c
d0010b30:	a054f8cd 	subsge	pc, r4, sp, asr #17
d0010b34:	d10c45da 	ldrdle	r4, [ip, -sl]
d0010b38:	2b006d13 	blcs	0xd002bf8c
d0010b3c:	80c1f040 	sbchi	pc, r1, r0, asr #32
d0010b40:	65574b81 	ldrbvs	r4, [r7, #-2945]	; 0xfffff47f
d0010b44:	f8c2447b 			; <UNDEFINED> instruction: 0xf8c2447b
d0010b48:	f8c29058 			; <UNDEFINED> instruction: 0xf8c29058
d0010b4c:	6513805c 	ldrvs	r8, [r3, #-92]	; 0xffffffa4
d0010b50:	f10ae0b7 			; <UNDEFINED> instruction: 0xf10ae0b7
d0010b54:	9a030301 	bls	0xd00d1760
d0010b58:	93159904 	tstls	r5, #4, 18	; 0x10000
d0010b5c:	2e5c5c56 	mrccs	12, 2, r5, cr12, cr6, {2}
d0010b60:	459bd10a 	ldrmi	sp, [fp, #266]	; 0x10a
d0010b64:	ab15d008 	blge	0xd0584b8c
d0010b68:	46494642 	strbmi	r4, [r9], -r2, asr #12
d0010b6c:	f8cd4638 			; <UNDEFINED> instruction: 0xf8cd4638
d0010b70:	f7ffb000 			; <UNDEFINED> instruction: 0xf7ffb000
d0010b74:	4606fbc9 	strmi	pc, [r6], -r9, asr #23
d0010b78:	459b9b15 	ldrmi	r9, [fp, #2837]	; 0xb15
d0010b7c:	4b73d00b 	blmi	0xd1d04bb0
d0010b80:	6d1a447b 	cfldrsvs	mvf4, [sl, #-492]	; 0xfffffe14
d0010b84:	4a72b93a 	bmi	0xd1cbf074
d0010b88:	447a655f 	ldrbtmi	r6, [sl], #-1375	; 0xfffffaa1
d0010b8c:	9058f8c3 	subsls	pc, r8, r3, asr #17
d0010b90:	805cf8c3 	subshi	pc, ip, r3, asr #17
d0010b94:	f44f651a 	vst3.8	{d22,d24,d26}, [pc :64], sl
d0010b98:	f8cd7b81 			; <UNDEFINED> instruction: 0xf8cd7b81
d0010b9c:	9508a01c 	strls	sl, [r8, #-28]	; 0xffffffe4
d0010ba0:	e6f29609 	ldrbt	r9, [r2], r9, lsl #12
d0010ba4:	7b82f44f 	blvc	0xce0cdce8
d0010ba8:	285ce7f7 	ldmdacs	ip, {r0, r1, r2, r4, r5, r6, r7, r8, r9, sl, sp, lr, pc}^
d0010bac:	9205d103 	andls	sp, r5, #-1073741824	; 0xc0000000
d0010bb0:	fca4f7ff 	stc2	7, cr15, [r4], #1020	; 0x3fc
d0010bb4:	280d9a05 	stmdacs	sp, {r0, r2, r9, fp, ip, pc}
d0010bb8:	fa25d8a0 	blx	0xd0986e40
d0010bbc:	07c1f000 	strbeq	pc, [r1, r0]	; <UNPREDICTABLE>
d0010bc0:	f1bbd59c 			; <UNDEFINED> instruction: 0xf1bbd59c
d0010bc4:	d1020f22 	tstle	r2, r2, lsr #30
d0010bc8:	447a4a62 	ldrbtmi	r4, [sl], #-2658	; 0xfffff59e
d0010bcc:	4a62e001 	bmi	0xd18c8bd8
d0010bd0:	4b62447a 	blmi	0xd18a1dc0
d0010bd4:	6d19447b 	cfldrsvs	mvf4, [r9, #-492]	; 0xfffffe14
d0010bd8:	d1722900 	cmnle	r2, r0, lsl #18
d0010bdc:	f7ffe611 			; <UNDEFINED> instruction: 0xf7ffe611
d0010be0:	283dfc7f 	ldmdacs	sp!, {r0, r1, r2, r3, r4, r5, r6, sl, fp, ip, sp, lr, pc}
d0010be4:	d1164602 	tstle	r6, r2, lsl #12
d0010be8:	0f21f1bb 	svceq	0x0021f1bb
d0010bec:	f1abd003 			; <UNDEFINED> instruction: 0xf1abd003
d0010bf0:	2902013c 	stmdbcs	r2, {r2, r3, r4, r5, r8}
d0010bf4:	f7ffd822 			; <UNDEFINED> instruction: 0xf7ffd822
d0010bf8:	f1bbfc81 			; <UNDEFINED> instruction: 0xf1bbfc81
d0010bfc:	d04e0f3d 	suble	r0, lr, sp, lsr pc
d0010c00:	0f21f1bb 	svceq	0x0021f1bb
d0010c04:	f1bbd04e 			; <UNDEFINED> instruction: 0xf1bbd04e
d0010c08:	f2400f3c 	vrecps.f32	d16, d0, d28
d0010c0c:	bf181b15 	svclt	0x00181b15
d0010c10:	7b8bf44f 	blvc	0xce30dd54
d0010c14:	4583e6b9 	strmi	lr, [r3, #1721]	; 0x6b9
d0010c18:	f1bbd110 			; <UNDEFINED> instruction: 0xf1bbd110
d0010c1c:	d0020f26 	andle	r0, r2, r6, lsr #30
d0010c20:	0f7cf1bb 	svceq	0x007cf1bb
d0010c24:	9203d10a 	andls	sp, r3, #-2147483646	; 0x80000002
d0010c28:	fc68f7ff 	stc2l	7, cr15, [r8], #-1020	; 0xfffffc04
d0010c2c:	f2409a03 	vpmax.s8	d25, d0, d3
d0010c30:	2a261b17 	bcs	0xd0997894
d0010c34:	f44fbf18 			; <UNDEFINED> instruction: 0xf44fbf18
d0010c38:	e6a67b8c 	strt	r7, [r6], ip, lsl #23
d0010c3c:	0f2df1bb 	svceq	0x002df1bb
d0010c40:	2a3ed106 	bcs	0xd0fc5060
d0010c44:	f240d116 	vand	d29, d0, d6
d0010c48:	f7ff1b19 			; <UNDEFINED> instruction: 0xf7ff1b19
d0010c4c:	e69cfc57 			; <UNDEFINED> instruction: 0xe69cfc57
d0010c50:	0f00f1bb 	svceq	0x0000f1bb
d0010c54:	4b42d10e 	blmi	0xd10c5094
d0010c58:	6d1a447b 	cfldrsvs	mvf4, [sl, #-492]	; 0xfffffe14
d0010c5c:	4a41b93a 	bmi	0xd107f14c
d0010c60:	447a655f 	ldrbtmi	r6, [sl], #-1375	; 0xfffffaa1
d0010c64:	9058f8c3 	subsls	pc, r8, r3, asr #17
d0010c68:	805cf8c3 	subshi	pc, ip, r3, asr #17
d0010c6c:	f240651a 	vqrshl.s8	d22, d10, d0
d0010c70:	e68a1b05 	str	r1, [sl], r5, lsl #22
d0010c74:	d1074593 			; <UNDEFINED> instruction: 0xd1074593
d0010c78:	002bf1ab 	eoreq	pc, fp, fp, lsr #3
d0010c7c:	d8032813 	stmdale	r3, {r0, r1, r4, fp, sp}
d0010c80:	40c14919 	sbcmi	r4, r1, r9, lsl r9
d0010c84:	d4e607cb 	strbtle	r0, [r6], #1995	; 0x7cb
d0010c88:	f47f2a3d 			; <UNDEFINED> instruction: 0xf47f2a3d
d0010c8c:	4836ae7e 	ldmdami	r6!, {r1, r2, r3, r4, r5, r6, r9, sl, fp, sp, pc}
d0010c90:	44784659 	ldrbtmi	r4, [r8], #-1625	; 0xfffff9a7
d0010c94:	f90af006 			; <UNDEFINED> instruction: 0xf90af006
d0010c98:	d1dc2800 	bicsle	r2, ip, r0, lsl #16
d0010c9c:	f240e675 	vmin.s8	q15, q0, <illegal reg q10.5>
d0010ca0:	e6721b13 			; <UNDEFINED> instruction: 0xe6721b13
d0010ca4:	7b8af44f 	blvc	0xce2cdde8
d0010ca8:	6d23e66f 	stcvs	6, cr14, [r3, #-444]!	; 0xfffffe44
d0010cac:	4a2fb94b 	bmi	0xd0bff1e0
d0010cb0:	306cf89d 	mlscc	ip, sp, r8, pc	; <UNPREDICTABLE>
d0010cb4:	65e3447a 	strbvs	r4, [r3, #1146]!	; 0x47a
d0010cb8:	9a186522 	bls	0xd062a148
d0010cbc:	9a196562 	bls	0xd066a24c
d0010cc0:	a80e65a2 	stmdage	lr, {r1, r5, r7, r8, sl, sp, lr}
d0010cc4:	2822e6e6 	stmdacs	r2!, {r1, r2, r5, r6, r7, r9, sl, sp, lr, pc}
d0010cc8:	adb6f43f 	cfldrsge	mvf15, [r6, #252]!	; 0xfc
d0010ccc:	9205e5c3 	andls	lr, r5, #817889280	; 0x30c00000
d0010cd0:	fc06f7ff 	stc2	7, cr15, [r6], {255}	; 0xff
d0010cd4:	0020f040 	eoreq	pc, r0, r0, asr #32
d0010cd8:	28789a05 	ldmdacs	r8!, {r0, r2, r9, fp, ip, pc}^
d0010cdc:	ae7cf43f 	mrcge	4, 3, APSR_nzcv, cr12, cr15, {1}
d0010ce0:	0b08f04f 	bleq	0xd024ce24
d0010ce4:	bf00e62b 	svclt	0x0000e62b
d0010ce8:	000a0005 	andeq	r0, sl, r5
d0010cec:	000078e6 	andeq	r7, r0, r6, ror #17
d0010cf0:	000078c0 	andeq	r7, r0, r0, asr #17
d0010cf4:	000078be 			; <UNDEFINED> instruction: 0x000078be
d0010cf8:	00007832 	andeq	r7, r0, r2, lsr r8
d0010cfc:	00004099 	muleq	r0, r9, r0
d0010d00:	000077ce 	andeq	r7, r0, lr, asr #15
d0010d04:	fffffd9b 			; <UNDEFINED> instruction: 0xfffffd9b
d0010d08:	00004046 	andeq	r4, r0, r6, asr #32
d0010d0c:	00007766 	andeq	r7, r0, r6, ror #14
d0010d10:	fffffd4e 			; <UNDEFINED> instruction: 0xfffffd4e
d0010d14:	00007720 	andeq	r7, r0, r0, lsr #14
d0010d18:	000076ca 	andeq	r7, r0, sl, asr #13
d0010d1c:	00007660 	andeq	r7, r0, r0, ror #12
d0010d20:	000065aa 	andeq	r6, r0, sl, lsr #11
d0010d24:	000065aa 	andeq	r6, r0, sl, lsr #11
d0010d28:	0000760a 	andeq	r7, r0, sl, lsl #12
d0010d2c:	fffffc1f 			; <UNDEFINED> instruction: 0xfffffc1f
d0010d30:	fffffc0e 			; <UNDEFINED> instruction: 0xfffffc0e
d0010d34:	000075a4 	andeq	r7, r0, r4, lsr #11
d0010d38:	fffffbf9 			; <UNDEFINED> instruction: 0xfffffbf9
d0010d3c:	00007544 	andeq	r7, r0, r4, asr #10
d0010d40:	fffffbc0 			; <UNDEFINED> instruction: 0xfffffbc0
d0010d44:	000074ce 	andeq	r7, r0, lr, asr #9
d0010d48:	fffffb30 			; <UNDEFINED> instruction: 0xfffffb30
d0010d4c:	00007440 	andeq	r7, r0, r0, asr #8
d0010d50:	fffffaea 			; <UNDEFINED> instruction: 0xfffffaea
d0010d54:	fffff986 			; <UNDEFINED> instruction: 0xfffff986
d0010d58:	fffff998 			; <UNDEFINED> instruction: 0xfffff998
d0010d5c:	000073ec 	andeq	r7, r0, ip, ror #7
d0010d60:	00007368 	andeq	r7, r0, r8, ror #6
d0010d64:	fffffa43 			; <UNDEFINED> instruction: 0xfffffa43
d0010d68:	fffffa0a 			; <UNDEFINED> instruction: 0xfffffa0a
d0010d6c:	fffff8d0 			; <UNDEFINED> instruction: 0xfffff8d0

Disassembly of section .text.accept.constprop.0:

d0010d70 <.text.accept.constprop.0>:
d0010d70:	447a4a07 	ldrbtmi	r4, [sl], #-2567	; 0xfffff5f9
d0010d74:	6d13b508 	cfldr32vs	mvfx11, [r3, #-32]	; 0xffffffe0
d0010d78:	6ad2b933 	bvs	0xcf4bf24c
d0010d7c:	d1054282 	smlabble	r5, r2, r2, r4
d0010d80:	fca6f7ff 	stc2	7, cr15, [r6], #1020	; 0x3fc
d0010d84:	bd082001 	stclt	0, cr2, [r8, #-4]
d0010d88:	e7fc2000 	ldrb	r2, [ip, r0]!
d0010d8c:	e7fa4618 			; <UNDEFINED> instruction: 0xe7fa4618
d0010d90:	0000724e 	andeq	r7, r0, lr, asr #4

Disassembly of section .text.accept_sdk_type.constprop.0:

d0010d94 <.text.accept_sdk_type.constprop.0>:
d0010d94:	46024b0b 	strmi	r4, [r2], -fp, lsl #22
d0010d98:	6ed9447b 	mrcvs	4, 6, r4, cr9, cr11, {3}
d0010d9c:	b171b510 	cmnlt	r1, r0, lsl r5
d0010da0:	f2406adc 	vpmin.s8	q11, q8, q6
d0010da4:	428c1101 	addmi	r1, ip, #1073741824	; 0x40000000
d0010da8:	69d9d109 	ldmibvs	r9, {r0, r3, r8, ip, lr, pc}^
d0010dac:	f7ff6998 			; <UNDEFINED> instruction: 0xf7ff6998
d0010db0:	b120fa31 	msrlt	R8_usr, r1
d0010db4:	e8bd4620 	pop	{r5, r9, sl, lr}
d0010db8:	f7ff4010 			; <UNDEFINED> instruction: 0xf7ff4010
d0010dbc:	2000bfd9 	ldrdcs	fp, [r0], -r9
d0010dc0:	bf00bd10 	svclt	0x0000bd10
d0010dc4:	00007228 	andeq	r7, r0, r8, lsr #4

Disassembly of section .text.error.constprop.0:

d0010dc8 <.text.error.constprop.0>:
d0010dc8:	447b4b06 	ldrbtmi	r4, [fp], #-2822	; 0xfffff4fa
d0010dcc:	b5106d1a 	ldrlt	r6, [r0, #-3354]	; 0xfffff2e6
d0010dd0:	6a5cb93a 	bvs	0xd173f2c0
d0010dd4:	f8936a99 			; <UNDEFINED> instruction: 0xf8936a99
d0010dd8:	65182030 	ldrvs	r2, [r8, #-48]	; 0xffffffd0
d0010ddc:	6599655c 	ldrvs	r6, [r9, #1372]	; 0x55c
d0010de0:	bd1065da 	cfldr32lt	mvfx6, [r0, #-872]	; 0xfffffc98
d0010de4:	000071f6 	strdeq	r7, [r0], -r6

Disassembly of section .text.expect.constprop.0:

d0010de8 <.text.expect.constprop.0>:
d0010de8:	460db538 			; <UNDEFINED> instruction: 0x460db538
d0010dec:	ffc0f7ff 			; <UNDEFINED> instruction: 0xffc0f7ff
d0010df0:	b9204604 	stmdblt	r0!, {r2, r9, sl, lr}
d0010df4:	f7ff4628 			; <UNDEFINED> instruction: 0xf7ff4628
d0010df8:	4620ffe7 	strtmi	pc, [r0], -r7, ror #31
d0010dfc:	2401bd38 	strcs	fp, [r1], #-3384	; 0xfffff2c8
d0010e00:	Address 0x00000000d0010e00 is out of bounds.


Disassembly of section .text.find_function.isra.0.constprop.0:

d0010e04 <.text.find_function.isra.0.constprop.0>:
d0010e04:	47f0e92d 	ldrbmi	lr, [r0, sp, lsr #18]!
d0010e08:	46824e14 	pkhbtmi	r4, r2, r4, lsl #28
d0010e0c:	25004688 	strcs	r4, [r0, #-1672]	; 0xfffff978
d0010e10:	f04f447e 			; <UNDEFINED> instruction: 0xf04f447e
d0010e14:	f50639ff 			; <UNDEFINED> instruction: 0xf50639ff
d0010e18:	f5064422 			; <UNDEFINED> instruction: 0xf5064422
d0010e1c:	3460474e 	strbtcc	r4, [r0], #-1870	; 0xfffff8b2
d0010e20:	683b3760 	ldmdavs	fp!, {r5, r6, r8, r9, sl, ip, sp}
d0010e24:	d211429d 	andsle	r4, r1, #-805306359	; 0xd0000009
d0010e28:	45436863 	strbmi	r6, [r3, #-2147]	; 0xfffff79d
d0010e2c:	4642d112 			; <UNDEFINED> instruction: 0x4642d112
d0010e30:	68204651 	stmdavs	r0!, {r0, r4, r6, r9, sl, lr}
d0010e34:	fc1ef004 	ldc2	0, cr15, [lr], {4}
d0010e38:	f894b960 			; <UNDEFINED> instruction: 0xf894b960
d0010e3c:	b1433024 	cmplt	r3, r4, lsr #32
d0010e40:	2025f894 	mlacs	r5, r4, r8, pc	; <UNPREDICTABLE>
d0010e44:	429a7a33 	addsmi	r7, sl, #208896	; 0x33000
d0010e48:	46a9d104 	strtmi	sp, [r9], r4, lsl #2
d0010e4c:	e8bd4648 	pop	{r3, r6, r9, sl, lr}
d0010e50:	46a987f0 			; <UNDEFINED> instruction: 0x46a987f0
d0010e54:	342c3501 	strtcc	r3, [ip], #-1281	; 0xfffffaff
d0010e58:	bf00e7e3 	svclt	0x0000e7e3
d0010e5c:	000071b0 			; <UNDEFINED> instruction: 0x000071b0

Disassembly of section .text.find_local.isra.0.constprop.0:

d0010e60 <.text.find_local.isra.0.constprop.0>:
d0010e60:	4c0fb5f8 	cfstr32mi	mvfx11, [pc], {248}	; 0xf8
d0010e64:	460e4607 	strmi	r4, [lr], -r7, lsl #12
d0010e68:	f504447c 			; <UNDEFINED> instruction: 0xf504447c
d0010e6c:	6f1d3393 	svcvs	0x001d3393
d0010e70:	1445eb04 	strbne	lr, [r5], #-2820	; 0xfffff4fc
d0010e74:	348ff504 	strcc	pc, [pc], #1284	; 0xd0010e7c
d0010e78:	b9153454 	ldmdblt	r5, {r2, r4, r6, sl, ip, sp}
d0010e7c:	30fff04f 	rscscc	pc, pc, pc, asr #32
d0010e80:	6823e00b 	stmdavs	r3!, {r0, r1, r3, sp, lr, pc}
d0010e84:	42b33d01 	adcsmi	r3, r3, #1, 26	; 0x40
d0010e88:	4632d108 	ldrtmi	sp, [r2], -r8, lsl #2
d0010e8c:	f8544639 			; <UNDEFINED> instruction: 0xf8544639
d0010e90:	f0040c04 			; <UNDEFINED> instruction: 0xf0040c04
d0010e94:	b908fbef 	stmdblt	r8, {r0, r1, r2, r3, r5, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d0010e98:	bdf84628 	ldcllt	6, cr4, [r8, #160]!	; 0xa0
d0010e9c:	e7ec3c20 	strb	r3, [ip, r0, lsr #24]!
d0010ea0:	00007158 	andeq	r7, r0, r8, asr r1

Disassembly of section .text.wide_immediate:

d0010ea4 <.text.wide_immediate>:
d0010ea4:	085db530 	ldmdaeq	sp, {r4, r5, r8, sl, ip, sp, pc}^
d0010ea8:	3413ea41 	ldrcc	lr, [r3], #-2625	; 0xfffff5bf
d0010eac:	6580f405 	strvs	pc, [r0, #1029]	; 0x405
d0010eb0:	011bb2d9 			; <UNDEFINED> instruction: 0x011bb2d9
d0010eb4:	ea41432c 	b	0xd1061b6c
d0010eb8:	4d0a2202 	sfmmi	f2, 4, [sl, #-8]
d0010ebc:	41e0f403 	mvnmi	pc, r3, lsl #8
d0010ec0:	447db224 	ldrbtmi	fp, [sp], #-548	; 0xfffffddc
d0010ec4:	4428430a 	strtmi	r4, [r8], #-778	; 0xfffffcf6
d0010ec8:	f880b292 			; <UNDEFINED> instruction: 0xf880b292
d0010ecc:	f3c44040 	vmla.i<illegal width 8>	q10, q2, d0[0]
d0010ed0:	f8802407 			; <UNDEFINED> instruction: 0xf8802407
d0010ed4:	0a122042 	beq	0xd0498fe4
d0010ed8:	4041f880 	submi	pc, r1, r0, lsl #17
d0010edc:	2043f880 	subcs	pc, r3, r0, lsl #17
d0010ee0:	bf00bd30 	svclt	0x0000bd30
d0010ee4:	0001a786 	andeq	sl, r1, r6, lsl #15

Disassembly of section .text.emit.constprop.0:

d0010f04 <.text.emit.constprop.0>:
d0010f04:	447a4a0e 	ldrbtmi	r4, [sl], #-2574	; 0xfffff5f2
d0010f08:	b4106d13 	ldrlt	r6, [r0], #-3347	; 0xfffff2ed
d0010f0c:	f8d2b9ab 			; <UNDEFINED> instruction: 0xf8d2b9ab
d0010f10:	1ca14e48 	stcne	14, cr4, [r1], #288	; 0x120
d0010f14:	3f80f5b1 	svccc	0x0080f5b1
d0010f18:	480ad905 	stmdami	sl, {r0, r2, r8, fp, ip, lr, pc}
d0010f1c:	4b04f85d 	blmi	0xd014f098
d0010f20:	f7ff4478 			; <UNDEFINED> instruction: 0xf7ff4478
d0010f24:	4b08bf51 	blmi	0xd0240c70
d0010f28:	1e48f8c2 	cdpne	8, 4, cr15, cr8, cr2, {6}
d0010f2c:	4423447b 	strtmi	r4, [r3], #-1147	; 0xfffffb85
d0010f30:	0040f883 	subeq	pc, r0, r3, lsl #17
d0010f34:	f8830a00 			; <UNDEFINED> instruction: 0xf8830a00
d0010f38:	f85d0041 			; <UNDEFINED> instruction: 0xf85d0041
d0010f3c:	47704b04 	ldrbmi	r4, [r0, -r4, lsl #22]!
d0010f40:	000070ba 	strheq	r7, [r0], -sl
d0010f44:	ffffffc4 			; <UNDEFINED> instruction: 0xffffffc4
d0010f48:	0001a71c 	andeq	sl, r1, ip, lsl r7

Disassembly of section .text.load_constant.constprop.0:

d0010f4c <.text.load_constant.constprop.0>:
d0010f4c:	e92d29ff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, fp, sp}
d0010f50:	460541f0 			; <UNDEFINED> instruction: 0x460541f0
d0010f54:	d80a460c 	stmdale	sl, {r2, r3, r9, sl, lr}
d0010f58:	d8082807 	stmdale	r8, {r0, r1, r2, fp, sp}
d0010f5c:	2000ea41 	andcs	lr, r0, r1, asr #20
d0010f60:	5000f440 	andpl	pc, r0, r0, asr #8
d0010f64:	41f0e8bd 	ldrhmi	lr, [r0, #141]!	; 0x8d
d0010f68:	f7ffb280 			; <UNDEFINED> instruction: 0xf7ffb280
d0010f6c:	4b17bfcb 	blmi	0xd0600ea0
d0010f70:	447b2000 	ldrbtmi	r2, [fp], #-0
d0010f74:	6e48f8d3 	mcrvs	8, 2, pc, cr8, cr3, {6}	; <UNPREDICTABLE>
d0010f78:	ffc4f7ff 			; <UNDEFINED> instruction: 0xffc4f7ff
d0010f7c:	f7ff2000 			; <UNDEFINED> instruction: 0xf7ff2000
d0010f80:	f5b4ffc1 			; <UNDEFINED> instruction: 0xf5b4ffc1
d0010f84:	d3053f80 	movwle	r3, #24448	; 0x5f80
d0010f88:	f7ff2000 			; <UNDEFINED> instruction: 0xf7ff2000
d0010f8c:	2000ffbb 			; <UNDEFINED> instruction: 0x2000ffbb
d0010f90:	ffb8f7ff 			; <UNDEFINED> instruction: 0xffb8f7ff
d0010f94:	447f4f0e 	ldrbtmi	r4, [pc], #-3854	; 0xd0010f9c
d0010f98:	b9a36d3b 	stmiblt	r3!, {r0, r1, r3, r4, r5, r8, sl, fp, sp, lr}
d0010f9c:	462ab2a3 	strtmi	fp, [sl], -r3, lsr #5
d0010fa0:	2140f24f 	cmpcs	r0, pc, asr #4	; <UNPREDICTABLE>
d0010fa4:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0010fa8:	f5b4ff7d 			; <UNDEFINED> instruction: 0xf5b4ff7d
d0010fac:	d30a3f80 	movwle	r3, #44928	; 0xaf80
d0010fb0:	b9436d3b 	stmdblt	r3, {r0, r1, r3, r4, r5, r8, sl, fp, sp, lr}^
d0010fb4:	462a0c23 	strtmi	r0, [sl], -r3, lsr #24
d0010fb8:	f24f1d30 	vmla.f32	d17, d15, d16
d0010fbc:	e8bd21c0 	pop	{r6, r7, r8, sp}
d0010fc0:	f7ff41f0 			; <UNDEFINED> instruction: 0xf7ff41f0
d0010fc4:	e8bdbf6f 	pop	{r0, r1, r2, r3, r5, r6, r8, r9, sl, fp, ip, sp, pc}
d0010fc8:	bf0081f0 	svclt	0x000081f0
d0010fcc:	0000704e 	andeq	r7, r0, lr, asr #32
d0010fd0:	0000702a 	andeq	r7, r0, sl, lsr #32

Disassembly of section .text.load_local.constprop.0:

d0010fd4 <.text.load_local.constprop.0>:
d0010fd4:	b510281f 	ldrlt	r2, [r0, #-2079]	; 0xfffff7e1
d0010fd8:	d808b284 	stmdale	r8, {r2, r7, r9, ip, sp, pc}
d0010fdc:	0038f646 	eorseq	pc, r8, r6, asr #12
d0010fe0:	1084ea40 	addne	lr, r4, r0, asr #20
d0010fe4:	e8bdb280 	pop	{r7, r9, ip, sp, pc}
d0010fe8:	f7ff4010 			; <UNDEFINED> instruction: 0xf7ff4010
d0010fec:	f64fbf8b 			; <UNDEFINED> instruction: 0xf64fbf8b
d0010ff0:	f7ff00d7 			; <UNDEFINED> instruction: 0xf7ff00d7
d0010ff4:	00a0ff87 	adceq	pc, r0, r7, lsl #31
d0010ff8:	Address 0x00000000d0010ff8 is out of bounds.


Disassembly of section .text.store_local.constprop.0:

d0010ffa <.text.store_local.constprop.0>:
d0010ffa:	b538281f 	ldrlt	r2, [r8, #-2079]!	; 0xfffff7e1
d0010ffe:	b285b28c 	addlt	fp, r5, #140, 4	; 0xc0000008
d0011002:	ea44d80a 	b	0xd1147032
d0011006:	f4401085 	vst4.32	{d17-d20}, [r0], r5
d001100a:	f04040c0 			; <UNDEFINED> instruction: 0xf04040c0
d001100e:	b2800038 	addlt	r0, r0, #56	; 0x38
d0011012:	4038e8bd 	ldrhtmi	lr, [r8], -sp
d0011016:	bf75f7ff 	svclt	0x0075f7ff
d001101a:	00c7f64f 	sbceq	pc, r7, pc, asr #12
d001101e:	ff71f7ff 			; <UNDEFINED> instruction: 0xff71f7ff
d0011022:	ea4000a8 	b	0xd10112ca
d0011026:	e7f23004 	ldrb	r3, [r2, r4]!

Disassembly of section .text.emit_address.constprop.0:

d0011050 <.text.emit_address.constprop.0>:
d0011050:	4b1bb538 	blmi	0xd06fe538
d0011054:	f6484604 			; <UNDEFINED> instruction: 0xf6484604
d0011058:	447b6050 	ldrbtmi	r6, [fp], #-80	; 0xffffffb0
d001105c:	f5b2581a 			; <UNDEFINED> instruction: 0xf5b2581a
d0011060:	d1056f00 	tstle	r5, r0, lsl #30
d0011064:	e8bd4817 	pop	{r0, r1, r2, r4, fp, lr}
d0011068:	44784038 	ldrbtmi	r4, [r8], #-56	; 0xffffffc8
d001106c:	beacf7ff 	mcrlt	7, 5, pc, cr12, cr15, {7}	; <UNPREDICTABLE>
d0011070:	f6021c55 			; <UNDEFINED> instruction: 0xf6021c55
d0011074:	501d12ca 	andspl	r1, sp, sl, asr #5
d0011078:	0e48f8d3 	mcreq	8, 2, pc, cr8, cr3, {6}	; <UNPREDICTABLE>
d001107c:	0032f843 	eorseq	pc, r2, r3, asr #16
d0011080:	03c2eb03 	biceq	lr, r2, #3072	; 0xc00
d0011084:	80992000 	addshi	r2, r9, r0
d0011088:	f7ff719c 			; <UNDEFINED> instruction: 0xf7ff719c
d001108c:	2000ff3b 	andcs	pc, r0, fp, lsr pc	; <UNPREDICTABLE>
d0011090:	ff38f7ff 			; <UNDEFINED> instruction: 0xff38f7ff
d0011094:	f7ff2000 			; <UNDEFINED> instruction: 0xf7ff2000
d0011098:	2000ff35 	andcs	pc, r0, r5, lsr pc	; <UNPREDICTABLE>
d001109c:	ff32f7ff 			; <UNDEFINED> instruction: 0xff32f7ff
d00110a0:	4022f44f 	eormi	pc, r2, pc, asr #8
d00110a4:	ff2ef7ff 			; <UNDEFINED> instruction: 0xff2ef7ff
d00110a8:	bf0c2c01 	svclt	0x000c2c01
d00110ac:	20002041 	andcs	r2, r0, r1, asr #32
d00110b0:	50c0f440 	sbcpl	pc, r0, r0, asr #8
d00110b4:	4038e8bd 	ldrhtmi	lr, [r8], -sp
d00110b8:	0010f040 	andseq	pc, r0, r0, asr #32
d00110bc:	bf22f7ff 	svclt	0x0022f7ff
d00110c0:	00006f66 	andeq	r6, r0, r6, ror #30
d00110c4:	ffffffbc 			; <UNDEFINED> instruction: 0xffffffbc

Disassembly of section .text.string_argument.constprop.0:

d0011108 <.text.string_argument.constprop.0>:
d0011108:	47ffe92d 	ldrbmi	lr, [pc, sp, lsr #18]!
d001110c:	447c4c34 	ldrbtmi	r4, [ip], #-3124	; 0xfffff3cc
d0011110:	f5b36ae3 			; <UNDEFINED> instruction: 0xf5b36ae3
d0011114:	d0067f82 	andle	r7, r6, r2, lsl #31
d0011118:	44784832 	ldrbtmi	r4, [r8], #-2098	; 0xfffff7ce
d001111c:	fe54f7ff 	mrc2	7, 2, pc, cr4, cr15, {7}
d0011120:	e8bdb004 	pop	{r2, ip, sp, pc}
d0011124:	f8d487f0 			; <UNDEFINED> instruction: 0xf8d487f0
d0011128:	f5b88e4c 			; <UNDEFINED> instruction: 0xf5b88e4c
d001112c:	d02b4f80 	eorle	r4, fp, r0, lsl #31
d0011130:	447d4d2d 	ldrbtmi	r4, [sp], #-3373	; 0xfffff2d3
d0011134:	f10d69a6 			; <UNDEFINED> instruction: 0xf10d69a6
d0011138:	69e30a0c 	stmibvs	r3!, {r2, r3, r9, fp}^
d001113c:	96034f2b 	strls	r4, [r3], -fp, lsr #30
d0011140:	f8d4441e 			; <UNDEFINED> instruction: 0xf8d4441e
d0011144:	447f9024 	ldrbtmi	r9, [pc], #-36	; 0xd001114c
d0011148:	f8946aa1 			; <UNDEFINED> instruction: 0xf8946aa1
d001114c:	98032030 	stmdals	r3, {r4, r5, sp}
d0011150:	d11c4286 	tstle	ip, r6, lsl #5
d0011154:	fabcf7ff 	blx	0xcef4f158
d0011158:	447b4b25 	ldrbtmi	r4, [fp], #-2853	; 0xfffff4db
d001115c:	f5b26ada 			; <UNDEFINED> instruction: 0xf5b26ada
d0011160:	d1027f82 	smlabble	r2, r2, pc, r7	; <UNPREDICTABLE>
d0011164:	2b006d1b 	blcs	0xd002c5d8
d0011168:	4b22d0e4 	blmi	0xd08c5500
d001116c:	447b2000 	ldrbtmi	r2, [fp], #-0
d0011170:	2e4cf8d3 	mcrcs	8, 2, pc, cr12, cr3, {6}	; <UNPREDICTABLE>
d0011174:	f8c31c51 			; <UNDEFINED> instruction: 0xf8c31c51
d0011178:	44131e4c 	ldrmi	r1, [r3], #-3660	; 0xfffff1b4
d001117c:	f8834641 			; <UNDEFINED> instruction: 0xf8834641
d0011180:	f7ff0e50 			; <UNDEFINED> instruction: 0xf7ff0e50
d0011184:	e7cbff65 	strb	pc, [fp, r5, ror #30]	; <UNPREDICTABLE>
d0011188:	4478481b 	ldrbtmi	r4, [r8], #-2075	; 0xfffff7e5
d001118c:	f8d5e7c6 			; <UNDEFINED> instruction: 0xf8d5e7c6
d0011190:	33013e4c 	movwcc	r3, #7756	; 0x1e4c
d0011194:	4f80f5b3 	svcmi	0x0080f5b3
d0011198:	6d2bd30a 	stcvs	3, cr13, [fp, #-40]!	; 0xffffffd8
d001119c:	d1bf2b00 			; <UNDEFINED> instruction: 0xd1bf2b00
d00111a0:	f8c54b16 			; <UNDEFINED> instruction: 0xf8c54b16
d00111a4:	447b9054 	ldrbtmi	r9, [fp], #-84	; 0xffffffac
d00111a8:	65ea65a9 	strbvs	r6, [sl, #1449]!	; 0x5a9
d00111ac:	e7b7652b 	ldr	r6, [r7, fp, lsr #10]!
d00111b0:	93031c43 	movwls	r1, #15427	; 0x3c43
d00111b4:	285c7800 	ldmdacs	ip, {fp, ip, sp, lr}^
d00111b8:	4653d104 	ldrbmi	sp, [r3], -r4, lsl #2
d00111bc:	96004648 	strls	r4, [r0], -r8, asr #12
d00111c0:	f8a2f7ff 			; <UNDEFINED> instruction: 0xf8a2f7ff
d00111c4:	2b006d3b 	blcs	0xd002c6b8
d00111c8:	f8d7d1aa 			; <UNDEFINED> instruction: 0xf8d7d1aa
d00111cc:	f1033e4c 			; <UNDEFINED> instruction: 0xf1033e4c
d00111d0:	443b0c01 	ldrtmi	r0, [fp], #-3073	; 0xfffff3ff
d00111d4:	ce4cf8c7 	cdpgt	8, 4, cr15, cr12, cr7, {6}
d00111d8:	0e50f883 	cdpeq	8, 5, cr15, cr0, cr3, {4}
d00111dc:	bf00e7b7 	svclt	0x0000e7b7
d00111e0:	00006eb2 			; <UNDEFINED> instruction: 0x00006eb2
d00111e4:	ffffffaa 			; <UNDEFINED> instruction: 0xffffffaa
d00111e8:	00006e8e 	andeq	r6, r0, lr, lsl #29
d00111ec:	00006e7a 	andeq	r6, r0, sl, ror lr
d00111f0:	00006e66 	andeq	r6, r0, r6, ror #28
d00111f4:	00006e52 	andeq	r6, r0, r2, asr lr
d00111f8:	ffffff5d 			; <UNDEFINED> instruction: 0xffffff5d
d00111fc:	ffffff41 			; <UNDEFINED> instruction: 0xffffff41

Disassembly of section .text.branch.constprop.0:

d0011200 <.text.branch.constprop.0>:
d0011200:	20004b06 	andcs	r4, r0, r6, lsl #22
d0011204:	b510447b 	ldrlt	r4, [r0, #-1147]	; 0xfffffb85
d0011208:	4e48f8d3 	mcrmi	8, 2, pc, cr8, cr3, {6}	; <UNPREDICTABLE>
d001120c:	fe7af7ff 	mrc2	7, 3, pc, cr10, cr15, {7}
d0011210:	f7ff2000 			; <UNDEFINED> instruction: 0xf7ff2000
d0011214:	4620fe77 			; <UNDEFINED> instruction: 0x4620fe77
d0011218:	bf00bd10 	svclt	0x0000bd10
d001121c:	00006dbc 			; <UNDEFINED> instruction: 0x00006dbc

Disassembly of section .text.branch_on_value.constprop.0:

d0011220 <.text.branch_on_value.constprop.0>:
d0011220:	4604b510 			; <UNDEFINED> instruction: 0x4604b510
d0011224:	5020f44f 	eorpl	pc, r0, pc, asr #8
d0011228:	fe6cf7ff 	mcr2	7, 3, pc, cr12, cr15, {7}	; <UNPREDICTABLE>
d001122c:	1301f24d 	movwne	pc, #4685	; 0x124d	; <UNPREDICTABLE>
d0011230:	0001f24d 	andeq	pc, r1, sp, asr #4
d0011234:	bf082c00 	svclt	0x00082c00
d0011238:	f7ff4618 			; <UNDEFINED> instruction: 0xf7ff4618
d001123c:	e8bdfe63 	pop	{r0, r1, r5, r6, r9, sl, fp, ip, sp, lr, pc}
d0011240:	f7ff4010 			; <UNDEFINED> instruction: 0xf7ff4010
d0011244:	Address 0x00000000d0011244 is out of bounds.


Disassembly of section .text.boolean.constprop.0:

d0011246 <.text.boolean.constprop.0>:
d0011246:	f24db508 	vrshl.s8	d27, d8, d13
d001124a:	ea430301 	b	0xd10d1e56
d001124e:	b2802000 	addlt	r2, r0, #0
d0011252:	fe57f7ff 	mrc2	7, 2, pc, cr7, cr15, {7}
d0011256:	5000f44f 	andpl	pc, r0, pc, asr #8
d001125a:	fe53f7ff 	mrc2	7, 2, pc, cr3, cr15, {7}
d001125e:	4060f44f 	rsbmi	pc, r0, pc, asr #8
d0011262:	fe4ff7ff 	mcr2	7, 2, pc, cr15, cr15, {7}	; <UNPREDICTABLE>
d0011266:	0001f242 	andeq	pc, r1, r2, asr #4
d001126a:	4008e8bd 			; <UNDEFINED> instruction: 0x4008e8bd
d001126e:	be49f7ff 	mcrlt	7, 2, pc, cr9, cr15, {7}	; <UNPREDICTABLE>

Disassembly of section .text.prepare_call.constprop.0:

d0011272 <.text.prepare_call.constprop.0>:
d0011272:	e92d2804 	push	{r2, fp, sp}
d0011276:	460541f0 			; <UNDEFINED> instruction: 0x460541f0
d001127a:	2504bf38 	strcs	fp, [r4, #-3896]	; 0xfffff0c8
d001127e:	3d034604 	stccc	6, cr4, [r3, #-16]
d0011282:	0501f035 	streq	pc, [r1, #-53]	; 0xffffffcb
d0011286:	f445d006 	vst4.8	{d29-d32}, [r5], r6
d001128a:	f0404030 			; <UNDEFINED> instruction: 0xf0404030
d001128e:	b2800080 	addlt	r0, r0, #128	; 0x80
d0011292:	fe37f7ff 	mrc2	7, 1, pc, cr7, cr15, {7}
d0011296:	f04f1f66 			; <UNDEFINED> instruction: 0xf04f1f66
d001129a:	00770804 	rsbseq	r0, r7, r4, lsl #16
d001129e:	0646eb05 	strbeq	lr, [r6], -r5, lsl #22
d00112a2:	4544b2b6 	strbmi	fp, [r4, #-694]	; 0xfffffd4a
d00112a6:	f107d80a 			; <UNDEFINED> instruction: 0xf107d80a
d00112aa:	27000608 	strcs	r0, [r0, -r8, lsl #12]
d00112ae:	b2b6442e 	adcslt	r4, r6, #771751936	; 0x2e000000
d00112b2:	d02142bc 	strhtle	r4, [r1], -ip
d00112b6:	d1112f04 	tstle	r1, r4, lsl #30
d00112ba:	e025b9fd 	strd	fp, [r5], -sp	; <UNPREDICTABLE>
d00112be:	4018f446 	andsmi	pc, r8, r6, asr #8
d00112c2:	f7ff3e02 			; <UNDEFINED> instruction: 0xf7ff3e02
d00112c6:	f1a8fe1e 			; <UNDEFINED> instruction: 0xf1a8fe1e
d00112ca:	b2b60004 	adcslt	r0, r6, #4
d00112ce:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d00112d2:	4010f440 	andsmi	pc, r0, r0, asr #8
d00112d6:	f7ffb280 			; <UNDEFINED> instruction: 0xf7ffb280
d00112da:	e7e2fe14 			; <UNDEFINED> instruction: 0xe7e2fe14
d00112de:	3701b2bb 			; <UNDEFINED> instruction: 0x3701b2bb
d00112e2:	30c3ebc3 	sbccc	lr, r3, r3, asr #23
d00112e6:	0040eb06 	subeq	lr, r0, r6, lsl #22
d00112ea:	2003ea40 	andcs	lr, r3, r0, asr #20
d00112ee:	4018f440 	andsmi	pc, r8, r0, asr #8
d00112f2:	f7ffb280 			; <UNDEFINED> instruction: 0xf7ffb280
d00112f6:	e7dbfe06 	ldrb	pc, [fp, r6, lsl #28]	; <UNPREDICTABLE>
d00112fa:	eb05b125 	bl	0xd017d796
d00112fe:	46200444 	strtmi	r0, [r0], -r4, asr #8
d0011302:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d0011306:	d0fa2c00 	rscsle	r2, sl, r0, lsl #24
d001130a:	24000060 	strcs	r0, [r0], #-96	; 0xffffffa0
d001130e:	4030f440 	eorsmi	pc, r0, r0, asr #8
d0011312:	f7ffb280 			; <UNDEFINED> instruction: 0xf7ffb280
d0011316:	e7f2fdf6 	udf	#12246	; 0x2fd6

Disassembly of section .text.null_argument.constprop.0:

d0011320 <.text.null_argument.constprop.0>:
d0011320:	447b4b17 	ldrbtmi	r4, [fp], #-2839	; 0xfffff4e9
d0011324:	b5136ada 	ldrlt	r6, [r3, #-2778]	; 0xfffff526
d0011328:	7181f5a2 	orrvc	pc, r1, r2, lsr #11
d001132c:	d8042901 	stmdale	r4, {r0, r8, fp, sp}
d0011330:	b1e36a1b 	mvnlt	r6, fp, lsl sl
d0011334:	b0022000 	andlt	r2, r2, r0
d0011338:	f240bd10 	vmla.f32	d27, d0, d0
d001133c:	428a1101 	addmi	r1, sl, #1073741824	; 0x40000000
d0011340:	699cd1f8 	ldmibvs	ip, {r3, r4, r5, r6, r7, r8, ip, lr, pc}
d0011344:	69d94a0f 	ldmibvs	r9, {r0, r1, r2, r3, r9, fp, lr}^
d0011348:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d001134c:	f7fe9101 			; <UNDEFINED> instruction: 0xf7fe9101
d0011350:	9901ff61 	stmdbls	r1, {r0, r5, r6, r8, r9, sl, fp, ip, sp, lr, pc}
d0011354:	d0ed2800 	rscle	r2, sp, r0, lsl #16
d0011358:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d001135c:	2800fd81 	stmdacs	r0, {r0, r7, r8, sl, fp, ip, sp, lr, pc}
d0011360:	dae79901 	ble	0xcf9f776c
d0011364:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011368:	2800ff89 	stmdacs	r0, {r0, r3, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d001136c:	f7ffdae2 			; <UNDEFINED> instruction: 0xf7ffdae2
d0011370:	f44ff9af 	vst2.32	{d31,d33}, [pc :128]
d0011374:	f7ff5000 			; <UNDEFINED> instruction: 0xf7ff5000
d0011378:	2001fdc5 	andcs	pc, r1, r5, asr #27
d001137c:	bf00e7db 	svclt	0x0000e7db
d0011380:	00006c9e 	muleq	r0, lr, ip
d0011384:	ffffffcc 			; <UNDEFINED> instruction: 0xffffffcc

Disassembly of section .text.patch_branch.isra.0.part.0:

d0011388 <.text.patch_branch.isra.0.part.0>:
d0011388:	2a001a09 	bcs	0xd0017bb4
d001138c:	0104f1a1 	smlatbeq	r4, r1, r1, pc	; <UNPREDICTABLE>
d0011390:	f44fbf14 			; <UNDEFINED> instruction: 0xf44fbf14
d0011394:	f44f4250 	vst1.16	{d20-d23}, [pc :64], r0
d0011398:	b5f04210 	ldrblt	r4, [r0, #528]!	; 0x210
d001139c:	6600f3c1 	strvs	pc, [r0], -r1, asr #7
d00113a0:	3409f3c1 	strcc	pc, [r9], #-961	; 0xfffffc3f
d00113a4:	ea864f11 	b	0xce1a4ff0
d00113a8:	ea4453d1 	b	0xd11262f4
d00113ac:	447f2486 	ldrbtmi	r2, [pc], #-1158	; 0xd00113b4
d00113b0:	f44443db 	vst2.<illegal width 64>	{d20-d23}, [r4 :64], fp
d00113b4:	f0034470 			; <UNDEFINED> instruction: 0xf0034470
d00113b8:	ea860501 	b	0xce1927c4
d00113bc:	f3c15391 	vrsra.u64	d21, d1, #63
d00113c0:	183e014a 	ldmdane	lr!, {r1, r3, r6, r8}
d00113c4:	f88643db 			; <UNDEFINED> instruction: 0xf88643db
d00113c8:	0a244040 	beq	0xd09214d0
d00113cc:	0301f003 	movweq	pc, #4099	; 0x1003	; <UNPREDICTABLE>
d00113d0:	4041f886 	submi	pc, r1, r6, lsl #17
d00113d4:	ea4302db 	b	0xd10d1f48
d00113d8:	430b3345 	movwmi	r3, #45893	; 0xb345
d00113dc:	f8864313 			; <UNDEFINED> instruction: 0xf8864313
d00113e0:	0a1b3042 	beq	0xd06dd4f0
d00113e4:	3043f886 	subcc	pc, r3, r6, lsl #17
d00113e8:	bf00bdf0 	svclt	0x0000bdf0
d00113ec:	0001a29a 	muleq	r1, sl, r2

Disassembly of section .text.patch_branch.isra.0:

d00113f0 <.text.patch_branch.isra.0>:
d00113f0:	4604b410 			; <UNDEFINED> instruction: 0x4604b410
d00113f4:	46114608 	ldrmi	r4, [r1], -r8, lsl #12
d00113f8:	b91c461a 	ldmdblt	ip, {r1, r3, r4, r9, sl, lr}
d00113fc:	4b04f85d 	blmi	0xd014f578
d0011400:	bfc2f7ff 	svclt	0x00c2f7ff
d0011404:	4b04f85d 	blmi	0xd014f580
d0011408:	Address 0x00000000d0011408 is out of bounds.


Disassembly of section .text.unary.constprop.0:

d0011824 <.text.unary.constprop.0>:
d0011824:	4ff0e92d 	svcmi	0x00f0e92d
d0011828:	88bcf8df 	ldmhi	ip!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d001182c:	ed2d44f8 	cfstrs	mvf4, [sp, #-992]!	; 0xfffffc20
d0011830:	f8d88b02 			; <UNDEFINED> instruction: 0xf8d88b02
d0011834:	b087a050 	addlt	sl, r7, r0, asr r0
d0011838:	f1ba9000 			; <UNDEFINED> instruction: 0xf1ba9000
d001183c:	f0400f00 			; <UNDEFINED> instruction: 0xf0400f00
d0011840:	f5088440 			; <UNDEFINED> instruction: 0xf5088440
d0011844:	f1083293 			; <UNDEFINED> instruction: 0xf1083293
d0011848:	f8d8011c 			; <UNDEFINED> instruction: 0xf8d8011c
d001184c:	6fd39018 	svcvs	0x00d39018
d0011850:	b02cf8d8 	ldrdlt	pc, [ip], -r8	; <UNPREDICTABLE>
d0011854:	f8983301 			; <UNDEFINED> instruction: 0xf8983301
d0011858:	2b207030 	blcs	0xd082d920
d001185c:	c97267d3 	ldmdbgt	r2!, {r0, r1, r4, r6, r7, r8, r9, sl, sp, lr}^
d0011860:	f8dfd906 			; <UNDEFINED> instruction: 0xf8dfd906
d0011864:	44780888 	ldrbtmi	r0, [r8], #-2184	; 0xfffff778
d0011868:	faaef7ff 	blx	0xcebcf86c
d001186c:	e2292400 	eor	r2, r9, #0, 8
d0011870:	7081f44f 	addvc	pc, r1, pc, asr #8
d0011874:	f7ff9101 			; <UNDEFINED> instruction: 0xf7ff9101
d0011878:	9901fa7b 	stmdbls	r1, {r0, r1, r3, r4, r5, r6, r9, fp, ip, sp, lr, pc}
d001187c:	2000b150 	andcs	fp, r0, r0, asr r1
d0011880:	f7ff4621 			; <UNDEFINED> instruction: 0xf7ff4621
d0011884:	f240fb63 	vqdmulh.s<illegal width 8>	<illegal reg q15.5>, q0, <illegal reg q9.5>
d0011888:	45831003 	strmi	r1, [r3, #3]
d001188c:	2400bf14 	strcs	fp, [r0], #-3860	; 0xfffff0ec
d0011890:	e2172401 	ands	r2, r7, #16777216	; 0x1000000
d0011894:	1003f240 	andne	pc, r3, r0, asr #4
d0011898:	f7ff9101 			; <UNDEFINED> instruction: 0xf7ff9101
d001189c:	4682fa69 	strmi	pc, [r2], r9, ror #20
d00118a0:	d1ec2800 	mvnle	r2, r0, lsl #16
d00118a4:	1001f240 	andne	pc, r1, r0, asr #4
d00118a8:	fa62f7ff 	blx	0xd18cf8ac
d00118ac:	20284604 	eorcs	r4, r8, r4, lsl #12
d00118b0:	f0002c00 			; <UNDEFINED> instruction: 0xf0002c00
d00118b4:	f7ff83a9 			; <UNDEFINED> instruction: 0xf7ff83a9
d00118b8:	9901fa5b 	stmdbls	r1, {r0, r1, r3, r4, r6, r9, fp, ip, sp, lr, pc}
d00118bc:	28004604 	stmdacs	r0, {r2, r9, sl, lr}
d00118c0:	82b6f000 	adcshi	pc, r6, #0
d00118c4:	46c24654 			; <UNDEFINED> instruction: 0x46c24654
d00118c8:	306cf8da 	ldrdcc	pc, [ip], #-138	; 0xffffff76	; <UNPREDICTABLE>
d00118cc:	d31d429c 	tstle	sp, #156, 4	; 0xc0000009
d00118d0:	91004648 	tstls	r0, r8, asr #12
d00118d4:	fa96f7ff 	blx	0xce5cf8d8
d00118d8:	0800f1b0 	stmdaeq	r0, {r4, r5, r7, r8, ip, sp, lr, pc}
d00118dc:	db079900 	blle	0xd01f7ce4
d00118e0:	91004648 	tstls	r0, r8, asr #12
d00118e4:	fabcf7ff 	blx	0xcef4f8e8
d00118e8:	99002800 	stmdbls	r0, {fp, sp}
d00118ec:	81caf2c0 	bichi	pc, sl, r0, asr #5
d00118f0:	37fcf8df 	ubfxcc	pc, pc, #17, #29
d00118f4:	6d1c447b 	cfldrsvs	mvf4, [ip, #-492]	; 0xfffffe14
d00118f8:	d1b72c00 			; <UNDEFINED> instruction: 0xd1b72c00
d00118fc:	27f4f8df 	ubfxcs	pc, pc, #17, #21
d0011900:	651a447a 	ldrvs	r4, [sl, #-1146]	; 0xfffffb86
d0011904:	659e655d 	ldrvs	r6, [lr, #1373]	; 0x55d
d0011908:	e1db65df 	ldrsb	r6, [fp, #95]	; 0x5f
d001190c:	0b74f108 	bleq	0xd1d4dd34
d0011910:	91004648 	tstls	r0, r8, asr #12
d0011914:	f7fe465a 			; <UNDEFINED> instruction: 0xf7fe465a
d0011918:	f108fc7d 			; <UNDEFINED> instruction: 0xf108fc7d
d001191c:	28000334 	stmdacs	r0, {r2, r4, r5, r8, r9}
d0011920:	83d1f040 	bicshi	pc, r1, #64	; 0x40
d0011924:	46983401 	ldrmi	r3, [r8], r1, lsl #8
d0011928:	e7cd9900 	strb	r9, [sp, r0, lsl #18]
d001192c:	b1239b00 			; <UNDEFINED> instruction: 0xb1239b00
d0011930:	1a10ee18 	bne	0xd044d198
d0011934:	f7ff202c 			; <UNDEFINED> instruction: 0xf7ff202c
d0011938:	7837fa57 	ldmdavc	r7!, {r0, r1, r2, r4, r6, r9, fp, ip, sp, lr, pc}
d001193c:	2b0d1e7b 	blcs	0xd0359330
d0011940:	8173f200 	cmnhi	r3, r0, lsl #4	; <UNPREDICTABLE>
d0011944:	f013e8df 			; <UNDEFINED> instruction: 0xf013e8df
d0011948:	000e005c 	andeq	r0, lr, ip, asr r0
d001194c:	01710171 	cmneq	r1, r1, ror r1
d0011950:	01710171 	cmneq	r1, r1, ror r1
d0011954:	01710171 	cmneq	r1, r1, ror r1
d0011958:	00660066 	rsbeq	r0, r6, r6, rrx
d001195c:	00660171 	rsbeq	r0, r6, r1, ror r1
d0011960:	013800e4 	teqeq	r8, r4, ror #1
d0011964:	fbd0f7ff 	blx	0xcf44f96a
d0011968:	4003f24b 	andmi	pc, r3, fp, asr #4
d001196c:	f7ff3601 			; <UNDEFINED> instruction: 0xf7ff3601
d0011970:	9b00fac9 	blls	0xd005049c
d0011974:	93003301 	movwls	r3, #769	; 0x301
d0011978:	2300e9dd 	movwcs	lr, #2525	; 0x9dd
d001197c:	d9034293 	stmdble	r3, {r0, r1, r4, r7, r9, lr}
d0011980:	6d1b9b04 	vldrvs	d9, [fp, #-16]
d0011984:	d0d12b00 	sbcsle	r2, r1, r0, lsl #22
d0011988:	176cf8df 			; <UNDEFINED> instruction: 0x176cf8df
d001198c:	44792029 	ldrbtmi	r2, [r9], #-41	; 0xffffffd7
d0011990:	fa2af7ff 	blx	0xd0acf994
d0011994:	9801b368 	stmdals	r1, {r3, r5, r6, r8, r9, ip, sp, pc}
d0011998:	0520f10b 	streq	pc, [r0, #-267]!	; 0xfffffef5
d001199c:	fc69f7ff 	stc2l	7, cr15, [r9], #-1020	; 0xfffffc04
d00119a0:	3758f8df 	smmlscc	r8, pc, r8, pc	; <UNPREDICTABLE>
d00119a4:	089af108 	ldmeq	sl, {r3, r8, ip, sp, lr, pc}
d00119a8:	447b4604 	ldrbtmi	r4, [fp], #-1540	; 0xfffff9fc
d00119ac:	6e99200c 	cdpvs	0, 9, cr2, cr9, cr12, {0}
d00119b0:	faccf7ff 	blx	0xcf34f9b4
d00119b4:	00dcf64f 	sbcseq	pc, ip, pc, asr #12
d00119b8:	faa4f7ff 	blx	0xce94f9bc
d00119bc:	0b02f835 	bleq	0xd00cfa98
d00119c0:	4040f440 	submi	pc, r0, r0, asr #8
d00119c4:	fa9ef7ff 	blx	0xce7cf9c8
d00119c8:	d1f345a8 	mvnsle	r4, r8, lsr #11
d00119cc:	70e0f244 	rscvc	pc, r0, r4, asr #4
d00119d0:	fa98f7ff 	blx	0xce64f9d4
d00119d4:	f444b124 	vst4.8	{d27,d29,d31,d33}, [r4 :128], r4
d00119d8:	b2804030 	addlt	r4, r0, #48	; 0x30
d00119dc:	fa92f7ff 	blx	0xce4cf9e0
d00119e0:	3027f89b 	mlacc	r7, fp, r8, pc	; <UNPREDICTABLE>
d00119e4:	f0402b06 			; <UNDEFINED> instruction: 0xf0402b06
d00119e8:	f24b8147 	vrhadd.s8	q12, <illegal reg q5.5>, <illegal reg q3.5>
d00119ec:	f7ff20c0 			; <UNDEFINED> instruction: 0xf7ff20c0
d00119f0:	f89bfa89 			; <UNDEFINED> instruction: 0xf89bfa89
d00119f4:	28070027 	stmdacs	r7, {r0, r1, r2, r5}
d00119f8:	81d4f000 	bicshi	pc, r4, r0
d00119fc:	e7452805 	strb	r2, [r5, -r5, lsl #16]
d0011a00:	fc8ef7ff 	stc2	7, cr15, [lr], {255}	; 0xff
d0011a04:	d1af2800 			; <UNDEFINED> instruction: 0xd1af2800
d0011a08:	06f4f8df 	usateq	pc, #20, pc, asr #17	; <UNPREDICTABLE>
d0011a0c:	f7ff4478 			; <UNDEFINED> instruction: 0xf7ff4478
d0011a10:	e7a9f9db 	sbfx	pc, fp, #19, #10
d0011a14:	fc84f7ff 	stc2	7, cr15, [r4], {255}	; 0xff
d0011a18:	d1a52800 			; <UNDEFINED> instruction: 0xd1a52800
d0011a1c:	f7ff2026 			; <UNDEFINED> instruction: 0xf7ff2026
d0011a20:	f8dff9a7 			; <UNDEFINED> instruction: 0xf8dff9a7
d0011a24:	447b36e0 	ldrbtmi	r3, [fp], #-1760	; 0xfffff920
d0011a28:	6ad96a5a 	bvs	0xcf66c398
d0011a2c:	6a9a9202 	bvs	0xce6b623c
d0011a30:	a030f893 	mlasge	r0, r3, r8, pc	; <UNPREDICTABLE>
d0011a34:	f2409203 	vhsub.s8	d25, d0, d3
d0011a38:	42911201 	addsmi	r1, r1, #268435456	; 0x10000000
d0011a3c:	f8dfd010 			; <UNDEFINED> instruction: 0xf8dfd010
d0011a40:	447b36c8 	ldrbtmi	r3, [fp], #-1736	; 0xfffff938
d0011a44:	2a006d1a 	bcs	0xd002ceb4
d0011a48:	f8dfd18e 			; <UNDEFINED> instruction: 0xf8dfd18e
d0011a4c:	447a26c0 	ldrbtmi	r2, [sl], #-1728	; 0xfffff940
d0011a50:	9a02651a 	bls	0xd00aaec0
d0011a54:	a05cf8c3 	subsge	pc, ip, r3, asr #17
d0011a58:	9a03655a 	bls	0xd00eafc8
d0011a5c:	e783659a 			; <UNDEFINED> instruction: 0xe783659a
d0011a60:	9018f8d3 			; <UNDEFINED> instruction: 0x9018f8d3
d0011a64:	464869d9 			; <UNDEFINED> instruction: 0x464869d9
d0011a68:	f7ff9105 			; <UNDEFINED> instruction: 0xf7ff9105
d0011a6c:	1e05f9cb 	vmlsne.f16	s30, s11, s22	; <UNPREDICTABLE>
d0011a70:	9905dbe5 	stmdbls	r5, {r0, r2, r5, r6, r7, r8, r9, fp, ip, lr, pc}
d0011a74:	f7ff4648 			; <UNDEFINED> instruction: 0xf7ff4648
d0011a78:	2800f9f3 	stmdacs	r0, {r0, r1, r4, r5, r6, r7, r8, fp, ip, sp, lr, pc}
d0011a7c:	2f09dadf 	svccs	0x0009dadf
d0011a80:	2f0cd020 	svccs	0x000cd020
d0011a84:	f8dfd127 			; <UNDEFINED> instruction: 0xf8dfd127
d0011a88:	27029688 	strcs	r9, [r2, -r8, lsl #13]
d0011a8c:	1684f8df 	pkhtbne	pc, r4, pc, asr #17	; <UNPREDICTABLE>
d0011a90:	463a44f9 			; <UNDEFINED> instruction: 0x463a44f9
d0011a94:	f8df4479 			; <UNDEFINED> instruction: 0xf8df4479
d0011a98:	232cc680 			; <UNDEFINED> instruction: 0x232cc680
d0011a9c:	2e83f24a 	cdpcs	2, 8, cr15, cr3, cr10, {2}
d0011aa0:	436b44fc 	cmnmi	fp, #252, 8	; 0xfc000000
d0011aa4:	0003eb0c 	andeq	lr, r3, ip, lsl #22
d0011aa8:	e00ef810 	and	pc, lr, r0, lsl r8	; <UNPREDICTABLE>
d0011aac:	d01b45be 			; <UNDEFINED> instruction: 0xd01b45be
d0011ab0:	3668f8df 			; <UNDEFINED> instruction: 0x3668f8df
d0011ab4:	6d1a447b 	cfldrsvs	mvf4, [sl, #-492]	; 0xfffffe14
d0011ab8:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0011abc:	f8c3af55 			; <UNDEFINED> instruction: 0xf8c3af55
d0011ac0:	e7c69050 			; <UNDEFINED> instruction: 0xe7c69050
d0011ac4:	9658f8df 			; <UNDEFINED> instruction: 0x9658f8df
d0011ac8:	f8df2701 			; <UNDEFINED> instruction: 0xf8df2701
d0011acc:	22051658 	andcs	r1, r5, #88, 12	; 0x5800000
d0011ad0:	447944f9 	ldrbtmi	r4, [r9], #-1273	; 0xfffffb07
d0011ad4:	f8dfe7df 			; <UNDEFINED> instruction: 0xf8dfe7df
d0011ad8:	27019650 	smlsdcs	r1, r0, r6, r9
d0011adc:	164cf8df 			; <UNDEFINED> instruction: 0x164cf8df
d0011ae0:	463a44f9 			; <UNDEFINED> instruction: 0x463a44f9
d0011ae4:	e7d64479 			; <UNDEFINED> instruction: 0xe7d64479
d0011ae8:	2780f24a 	strcs	pc, [r0, sl, asr #4]
d0011aec:	42905dc0 	addsmi	r5, r0, #192, 26	; 0x3000
d0011af0:	f503d1de 			; <UNDEFINED> instruction: 0xf503d1de
d0011af4:	30864022 	addcc	r4, r6, r2, lsr #32
d0011af8:	f0034460 			; <UNDEFINED> instruction: 0xf0034460
d0011afc:	2800fdbb 	stmdacs	r0, {r0, r1, r3, r4, r5, r7, r8, sl, fp, ip, sp, lr, pc}
d0011b00:	f7fed1d6 			; <UNDEFINED> instruction: 0xf7fed1d6
d0011b04:	4629fde5 	strtmi	pc, [r9], -r5, ror #27
d0011b08:	f7ff2002 			; <UNDEFINED> instruction: 0xf7ff2002
d0011b0c:	e72bfaa1 	str	pc, [fp, -r1, lsr #21]!
d0011b10:	fc06f7ff 	stc2	7, cr15, [r6], {255}	; 0xff
d0011b14:	f47f2800 			; <UNDEFINED> instruction: 0xf47f2800
d0011b18:	f8dfaf27 			; <UNDEFINED> instruction: 0xf8dfaf27
d0011b1c:	20261614 	eorcs	r1, r6, r4, lsl r6
d0011b20:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d0011b24:	2800f961 	stmdacs	r0, {r0, r5, r6, r8, fp, ip, sp, lr, pc}
d0011b28:	af1ef43f 	svcge	0x001ef43f
d0011b2c:	9604f8df 			; <UNDEFINED> instruction: 0x9604f8df
d0011b30:	1201f240 	andne	pc, r1, #64, 4
d0011b34:	f8d944f9 			; <UNDEFINED> instruction: 0xf8d944f9
d0011b38:	f8d9102c 			; <UNDEFINED> instruction: 0xf8d9102c
d0011b3c:	42913028 	addsmi	r3, r1, #40	; 0x28
d0011b40:	a024f8d9 	ldrdge	pc, [r4], -r9	; <UNPREDICTABLE>
d0011b44:	7030f899 	mlasvc	r0, r9, r8, pc	; <UNPREDICTABLE>
d0011b48:	d0109302 	andsle	r9, r0, r2, lsl #6
d0011b4c:	35e8f8df 	strbcc	pc, [r8, #2271]!	; 0x8df	; <UNPREDICTABLE>
d0011b50:	6d1a447b 	cfldrsvs	mvf4, [sl, #-492]	; 0xfffffe14
d0011b54:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0011b58:	f8dfaf07 			; <UNDEFINED> instruction: 0xf8dfaf07
d0011b5c:	f8c325e0 			; <UNDEFINED> instruction: 0xf8c325e0
d0011b60:	447aa054 	ldrbtmi	sl, [sl], #-84	; 0xffffffac
d0011b64:	9a02651a 	bls	0xd00aafd4
d0011b68:	65df659a 	ldrbvs	r6, [pc, #1434]	; 0xd001210a
d0011b6c:	f8d9e6fc 			; <UNDEFINED> instruction: 0xf8d9e6fc
d0011b70:	f8d92018 			; <UNDEFINED> instruction: 0xf8d92018
d0011b74:	4610101c 			; <UNDEFINED> instruction: 0x4610101c
d0011b78:	91059203 	tstls	r5, r3, lsl #4
d0011b7c:	fb7ef7fe 	blx	0xd1fcfb7e
d0011b80:	dbe31e05 	blle	0xcf8d939c
d0011b84:	99059a03 	stmdbls	r5, {r0, r1, r9, fp, ip, pc}
d0011b88:	f7ff4610 			; <UNDEFINED> instruction: 0xf7ff4610
d0011b8c:	2800f969 	stmdacs	r0, {r0, r3, r5, r6, r8, fp, ip, sp, lr, pc}
d0011b90:	2228dadc 	eorcs	sp, r8, #220, 20	; 0xdc000
d0011b94:	9305fb02 	movwls	pc, #23298	; 0x5b02	; <UNPREDICTABLE>
d0011b98:	6278f648 	rsbsvs	pc, r8, #72, 12	; 0x4800000
d0011b9c:	2b055c9b 	blcs	0xd0168e10
d0011ba0:	f7fed1d4 			; <UNDEFINED> instruction: 0xf7fed1d4
d0011ba4:	2001fd95 	mulcs	r1, r5, sp
d0011ba8:	f7ff4629 			; <UNDEFINED> instruction: 0xf7ff4629
d0011bac:	f244fa51 	vpmin.s8	<illegal reg q15.5>, q2, <illegal reg q0.5>
d0011bb0:	f7ff6008 			; <UNDEFINED> instruction: 0xf7ff6008
d0011bb4:	e6d7f9a7 	ldrb	pc, [r7], r7, lsr #19	; <UNPREDICTABLE>
d0011bb8:	fbb2f7ff 	blx	0xceccfbbe
d0011bbc:	f47f2800 			; <UNDEFINED> instruction: 0xf47f2800
d0011bc0:	6ae2aed3 	bvs	0xcf8bd714
d0011bc4:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d0011bc8:	a024f8d4 	ldrdge	pc, [r4], -r4	; <UNPREDICTABLE>
d0011bcc:	f8d4429a 			; <UNDEFINED> instruction: 0xf8d4429a
d0011bd0:	f8949028 			; <UNDEFINED> instruction: 0xf8949028
d0011bd4:	d00f7030 	andle	r7, pc, r0, lsr r0	; <UNPREDICTABLE>
d0011bd8:	3564f8df 	strbcc	pc, [r4, #-2271]!	; 0xfffff721	; <UNPREDICTABLE>
d0011bdc:	6d1a447b 	cfldrsvs	mvf4, [sl, #-492]	; 0xfffffe14
d0011be0:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0011be4:	f8dfaec1 			; <UNDEFINED> instruction: 0xf8dfaec1
d0011be8:	f8c3255c 			; <UNDEFINED> instruction: 0xf8c3255c
d0011bec:	447aa054 	ldrbtmi	sl, [sl], #-84	; 0xffffffac
d0011bf0:	9058f8c3 	subsls	pc, r8, r3, asr #17
d0011bf4:	e7b8651a 			; <UNDEFINED> instruction: 0xe7b8651a
d0011bf8:	69e169a3 	stmibvs	r1!, {r0, r1, r5, r7, r8, fp, sp, lr}^
d0011bfc:	93024618 	movwls	r4, #9752	; 0x2618
d0011c00:	f7fe9103 			; <UNDEFINED> instruction: 0xf7fe9103
d0011c04:	1e05fb3b 	vmovne.16	d5[0], pc
d0011c08:	9b02dbe6 	blls	0xd00c8ba8
d0011c0c:	46189903 	ldrmi	r9, [r8], -r3, lsl #18
d0011c10:	f926f7ff 			; <UNDEFINED> instruction: 0xf926f7ff
d0011c14:	dadf2800 	ble	0xcf7dbc1c
d0011c18:	f6482328 			; <UNDEFINED> instruction: 0xf6482328
d0011c1c:	fb036278 	blx	0xd00ea606
d0011c20:	5c9b4305 	ldcpl	3, cr4, [fp], {5}
d0011c24:	d1d72b07 	bicsle	r2, r7, r7, lsl #22
d0011c28:	2101e7bb 			; <UNDEFINED> instruction: 0x2101e7bb
d0011c2c:	f0004608 			; <UNDEFINED> instruction: 0xf0004608
d0011c30:	7833fb11 	ldmdavc	r3!, {r0, r4, r8, r9, fp, ip, sp, lr, pc}
d0011c34:	2b053b03 	blcs	0xd0160848
d0011c38:	ae96f63f 	mrcge	6, 4, APSR_nzcv, cr6, cr15, {1}
d0011c3c:	f852a202 			; <UNDEFINED> instruction: 0xf852a202
d0011c40:	441a3023 	ldrmi	r3, [sl], #-35	; 0xffffffdd
d0011c44:	bf004710 	svclt	0x00004710
d0011c48:	00000019 	andeq	r0, r0, r9, lsl r0
d0011c4c:	0000001f 	andeq	r0, r0, pc, lsl r0
d0011c50:	fffffd21 			; <UNDEFINED> instruction: 0xfffffd21
d0011c54:	0000002b 	andeq	r0, r0, fp, lsr #32
d0011c58:	fffffd21 			; <UNDEFINED> instruction: 0xfffffd21
d0011c5c:	00000025 	andeq	r0, r0, r5, lsr #32
d0011c60:	4032f44f 	eorsmi	pc, r2, pc, asr #8
d0011c64:	f24be7a5 	vabd.s8	d30, d27, d21
d0011c68:	e7a22080 	str	r2, [r2, r0, lsl #1]!
d0011c6c:	2040f24b 	subcs	pc, r0, fp, asr #4
d0011c70:	f24be79f 	vaba.s8	d30, d27, d15
d0011c74:	e79c20c0 	ldr	r2, [ip, r0, asr #1]
d0011c78:	f47f2b08 			; <UNDEFINED> instruction: 0xf47f2b08
d0011c7c:	f24baeba 			; <UNDEFINED> instruction: 0xf24baeba
d0011c80:	e6b42040 	ldrt	r2, [r4], r0, asr #32
d0011c84:	f7fe4648 			; <UNDEFINED> instruction: 0xf7fe4648
d0011c88:	2800faf9 	stmdacs	r0, {r0, r3, r4, r5, r6, r7, r9, fp, ip, sp, lr, pc}
d0011c8c:	ae30f6bf 	mrcge	6, 1, APSR_nzcv, cr0, cr15, {5}
d0011c90:	f24a242c 	vshl.s8	d18, d28, d10
d0011c94:	fb042287 	blx	0xd011a6ba
d0011c98:	eb0af408 	bl	0xd02cecc0
d0011c9c:	5c9a0304 	ldcpl	3, cr0, [sl], {4}
d0011ca0:	d11d2a04 	tstle	sp, r4, lsl #20
d0011ca4:	4050f8da 	ldrsbmi	pc, [r0], #-138	; 0xffffff76	; <UNPREDICTABLE>
d0011ca8:	f47f2c00 			; <UNDEFINED> instruction: 0xf47f2c00
d0011cac:	f8dfaddf 			; <UNDEFINED> instruction: 0xf8dfaddf
d0011cb0:	f8ca3498 			; <UNDEFINED> instruction: 0xf8ca3498
d0011cb4:	447b5054 	ldrbtmi	r5, [fp], #-84	; 0xffffffac
d0011cb8:	6058f8ca 	subsvs	pc, r8, sl, asr #17
d0011cbc:	705cf8ca 	subsvc	pc, ip, sl, asr #17
d0011cc0:	3050f8ca 	subscc	pc, r0, sl, asr #17
d0011cc4:	3484f8df 	strcc	pc, [r4], #2271	; 0x8df
d0011cc8:	f503447b 			; <UNDEFINED> instruction: 0xf503447b
d0011ccc:	6fda3393 	svcvs	0x00da3393
d0011cd0:	67da3a01 	ldrbvs	r3, [sl, r1, lsl #20]
d0011cd4:	b0074620 	andlt	r4, r7, r0, lsr #12
d0011cd8:	8b02ecbd 	blhi	0xd00ccfd4
d0011cdc:	8ff0e8bd 	svchi	0x00f0e8bd
d0011ce0:	2281f24a 	addcs	pc, r1, #-1610612732	; 0xa0000004
d0011ce4:	2b045c9b 	blcs	0xd0128f58
d0011ce8:	f504d017 			; <UNDEFINED> instruction: 0xf504d017
d0011cec:	f04f4322 			; <UNDEFINED> instruction: 0xf04f4322
d0011cf0:	33860900 	orrcc	r0, r6, #0, 18
d0011cf4:	f8df4453 			; <UNDEFINED> instruction: 0xf8df4453
d0011cf8:	44faa458 	ldrbtmi	sl, [sl], #1112	; 0x458
d0011cfc:	44549300 	ldrbmi	r9, [r4], #-768	; 0xfffffd00
d0011d00:	4422f504 	strtmi	pc, [r2], #-1284	; 0xfffffafc
d0011d04:	78203480 	stmdavc	r0!, {r7, sl, ip, sp}
d0011d08:	d2024581 	andle	r4, r2, #541065216	; 0x20400000
d0011d0c:	3050f8da 	ldrsbcc	pc, [r0], #-138	; 0xffffff76	; <UNPREDICTABLE>
d0011d10:	f7ffb353 			; <UNDEFINED> instruction: 0xf7ffb353
d0011d14:	4604faae 	strmi	pc, [r4], -lr, lsr #21
d0011d18:	2400e002 	strcs	lr, [r0], #-2
d0011d1c:	f9f4f7ff 			; <UNDEFINED> instruction: 0xf9f4f7ff
d0011d20:	1430f8df 	ldrtne	pc, [r0], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d0011d24:	44792029 	ldrbtmi	r2, [r9], #-41	; 0xffffffd7
d0011d28:	f85ef7ff 			; <UNDEFINED> instruction: 0xf85ef7ff
d0011d2c:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0011d30:	f8dfad9d 			; <UNDEFINED> instruction: 0xf8dfad9d
d0011d34:	44f99424 	ldrbtmi	r9, [r9], #1060	; 0x424
d0011d38:	3387f509 	orrcc	pc, r7, #37748736	; 0x2400000
d0011d3c:	a064f8d3 	ldrdge	pc, [r4], #-131	; 0xffffff7d	; <UNPREDICTABLE>
d0011d40:	6f00f5ba 	svcvs	0x0000f5ba
d0011d44:	f8d9d152 			; <UNDEFINED> instruction: 0xf8d9d152
d0011d48:	2c004050 	stccs	0, cr4, [r0], {80}	; 0x50
d0011d4c:	ad8ef47f 	cfstrsge	mvf15, [lr, #508]	; 0x1fc
d0011d50:	3408f8df 	strcc	pc, [r8], #-2271	; 0xfffff721
d0011d54:	5054f8c9 	subspl	pc, r4, r9, asr #17
d0011d58:	f8c9447b 			; <UNDEFINED> instruction: 0xf8c9447b
d0011d5c:	f8c96058 			; <UNDEFINED> instruction: 0xf8c96058
d0011d60:	f8c9705c 			; <UNDEFINED> instruction: 0xf8c9705c
d0011d64:	e7ad3050 	sbfx	r3, r0, #0, #14
d0011d68:	0f00f1b9 	svceq	0x0000f1b9
d0011d6c:	49fcd004 	ldmibmi	ip!, {r2, ip, lr, pc}^
d0011d70:	4479202c 	ldrbtmi	r2, [r9], #-44	; 0xffffffd4
d0011d74:	f838f7ff 			; <UNDEFINED> instruction: 0xf838f7ff
d0011d78:	f8139b00 			; <UNDEFINED> instruction: 0xf8139b00
d0011d7c:	9300bb01 	movwls	fp, #2817	; 0xb01
d0011d80:	03fbf00b 	mvnseq	pc, #11
d0011d84:	d12c2b02 			; <UNDEFINED> instruction: 0xd12c2b02
d0011d88:	facaf7ff 	blx	0xcf2cfd8c
d0011d8c:	4bf5bb10 	blmi	0xcfd809d4
d0011d90:	1201f240 	andne	pc, r1, #64, 4
d0011d94:	6ad9447b 	bvs	0xcf662f88
d0011d98:	d0054291 	mulle	r5, r1, r2
d0011d9c:	447848f2 	ldrbtmi	r4, [r8], #-2290	; 0xfffff70e
d0011da0:	f812f7ff 			; <UNDEFINED> instruction: 0xf812f7ff
d0011da4:	e78d2402 	str	r2, [sp, r2, lsl #8]
d0011da8:	699869d9 	ldmibvs	r8, {r0, r3, r4, r6, r7, r8, fp, sp, lr}
d0011dac:	f7ff9301 			; <UNDEFINED> instruction: 0xf7ff9301
d0011db0:	2800f857 	stmdacs	r0, {r0, r1, r2, r4, r6, fp, ip, sp, lr, pc}
d0011db4:	9b01dbf2 	blls	0xd0088d84
d0011db8:	eb039001 	bl	0xd00f5dc4
d0011dbc:	f5031340 			; <UNDEFINED> instruction: 0xf5031340
d0011dc0:	f893338f 			; <UNDEFINED> instruction: 0xf893338f
d0011dc4:	455b308d 	ldrbmi	r3, [fp, #-141]	; 0xffffff73
d0011dc8:	f7fed1e8 			; <UNDEFINED> instruction: 0xf7fed1e8
d0011dcc:	9801fc81 	stmdals	r1, {r0, r7, sl, fp, ip, sp, lr, pc}
d0011dd0:	f900f7ff 			; <UNDEFINED> instruction: 0xf900f7ff
d0011dd4:	4003f24b 	andmi	pc, r3, fp, asr #4
d0011dd8:	0901f109 	stmdbeq	r1, {r0, r3, r8, ip, sp, lr, pc}
d0011ddc:	f892f7ff 			; <UNDEFINED> instruction: 0xf892f7ff
d0011de0:	2101e791 			; <UNDEFINED> instruction: 0x2101e791
d0011de4:	f0004608 			; <UNDEFINED> instruction: 0xf0004608
d0011de8:	e7f3fa35 			; <UNDEFINED> instruction: 0xe7f3fa35
d0011dec:	0201f10a 	andeq	pc, r1, #-2147483646	; 0x80000002
d0011df0:	5acef50a 	bpl	0xcf3cf220
d0011df4:	0a0cf10a 	beq	0xd034e224
d0011df8:	f7ff665a 			; <UNDEFINED> instruction: 0xf7ff665a
d0011dfc:	eb09fa01 	bl	0xd0290608
d0011e00:	f8c909ca 			; <UNDEFINED> instruction: 0xf8c909ca
d0011e04:	f8a90004 			; <UNDEFINED> instruction: 0xf8a90004
d0011e08:	b1248008 			; <UNDEFINED> instruction: 0xb1248008
d0011e0c:	4030f444 	eorsmi	pc, r0, r4, asr #8
d0011e10:	f7ffb280 			; <UNDEFINED> instruction: 0xf7ffb280
d0011e14:	48d5f877 	ldmmi	r5, {r0, r1, r2, r4, r5, r6, fp, ip, sp, lr, pc}^
d0011e18:	4478232c 	ldrbtmi	r2, [r8], #-812	; 0xfffffcd4
d0011e1c:	0808fb03 	stmdaeq	r8, {r0, r1, r8, r9, fp, ip, sp, lr, pc}
d0011e20:	2383f24a 	orrcs	pc, r3, #-1610612732	; 0xa0000004
d0011e24:	3003f818 	andcc	pc, r3, r8, lsl r8	; <UNPREDICTABLE>
d0011e28:	f47f2b01 			; <UNDEFINED> instruction: 0xf47f2b01
d0011e2c:	e7b9ad1f 			; <UNDEFINED> instruction: 0xe7b9ad1f
d0011e30:	91014648 	tstls	r1, r8, asr #12
d0011e34:	f814f7ff 			; <UNDEFINED> instruction: 0xf814f7ff
d0011e38:	46829901 	strmi	r9, [r2], r1, lsl #18
d0011e3c:	f7fe4648 			; <UNDEFINED> instruction: 0xf7fe4648
d0011e40:	9901f9ff 	stmdbls	r1, {r0, r1, r2, r3, r4, r5, r6, r7, r8, fp, ip, sp, lr, pc}
d0011e44:	6a01b120 	bvs	0xd007e2cc
d0011e48:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0011e4c:	e739f87f 			; <UNDEFINED> instruction: 0xe739f87f
d0011e50:	0f00f1ba 	svceq	0x0000f1ba
d0011e54:	eb08db6d 	bl	0xd0248c10
d0011e58:	f508184a 			; <UNDEFINED> instruction: 0xf508184a
d0011e5c:	f898388f 			; <UNDEFINED> instruction: 0xf898388f
d0011e60:	f1b8808d 			; <UNDEFINED> instruction: 0xf1b8808d
d0011e64:	d0020f02 	andle	r0, r2, r2, lsl #30
d0011e68:	0f04f1b8 	svceq	0x0004f1b8
d0011e6c:	4bc0d108 	blmi	0xcf046294
d0011e70:	6d1a447b 	cfldrsvs	mvf4, [sl, #-492]	; 0xfffffe14
d0011e74:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0011e78:	4abeacf9 	bmi	0xcefbd264
d0011e7c:	e540447a 	strb	r4, [r0, #-1146]	; 0xfffffb86
d0011e80:	f7ff4650 			; <UNDEFINED> instruction: 0xf7ff4650
d0011e84:	f1b8f8a7 			; <UNDEFINED> instruction: 0xf1b8f8a7
d0011e88:	d14f0f06 	cmple	pc, r6, lsl #30
d0011e8c:	1019f240 	andsne	pc, r9, r0, asr #4
d0011e90:	ff6ef7fe 			; <UNDEFINED> instruction: 0xff6ef7fe
d0011e94:	2403b908 	strcs	fp, [r3], #-2312	; 0xfffff6f8
d0011e98:	4bb7e714 	blmi	0xcee0baf0
d0011e9c:	1001f240 	andne	pc, r1, r0, asr #4
d0011ea0:	447b49b6 	ldrbtmi	r4, [fp], #-2486	; 0xfffff64a
d0011ea4:	f8d34479 			; <UNDEFINED> instruction: 0xf8d34479
d0011ea8:	f8d39018 			; <UNDEFINED> instruction: 0xf8d39018
d0011eac:	f8d3a01c 			; <UNDEFINED> instruction: 0xf8d3a01c
d0011eb0:	6a9f8024 	bvs	0xce7f1f48
d0011eb4:	6030f893 	mlasvs	r0, r3, r8, pc	; <UNPREDICTABLE>
d0011eb8:	ff96f7fe 			; <UNDEFINED> instruction: 0xff96f7fe
d0011ebc:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0011ec0:	f8dfacd5 			; <UNDEFINED> instruction: 0xf8dfacd5
d0011ec4:	2500b2bc 	strcs	fp, [r0, #-700]	; 0xfffffd44
d0011ec8:	f85b44fb 			; <UNDEFINED> instruction: 0xf85b44fb
d0011ecc:	46512b04 	ldrbmi	r2, [r1], -r4, lsl #22
d0011ed0:	f7fe4648 			; <UNDEFINED> instruction: 0xf7fe4648
d0011ed4:	4604f99f 			; <UNDEFINED> instruction: 0x4604f99f
d0011ed8:	f64fb1b8 			; <UNDEFINED> instruction: 0xf64fb1b8
d0011edc:	f64f03d0 			; <UNDEFINED> instruction: 0xf64f03d0
d0011ee0:	2d010090 	stccs	0, cr0, [r1, #-576]	; 0xfffffdc0
d0011ee4:	4618bf18 	sadd16mi	fp, r8, r8
d0011ee8:	f80cf7ff 			; <UNDEFINED> instruction: 0xf80cf7ff
d0011eec:	447b4ba5 	ldrbtmi	r4, [fp], #-2981	; 0xfffff45b
d0011ef0:	0345eb03 	movteq	lr, #23299	; 0x5b03
d0011ef4:	0e34f8b3 	mrceq	8, 1, APSR_nzcv, cr4, cr3, {5}
d0011ef8:	f804f7ff 			; <UNDEFINED> instruction: 0xf804f7ff
d0011efc:	3d02b11d 	stfccd	f3, [r2, #-116]	; 0xffffff8c
d0011f00:	f63f2d01 			; <UNDEFINED> instruction: 0xf63f2d01
d0011f04:	2401acb3 	strcs	sl, [r1], #-3251	; 0xfffff34d
d0011f08:	3501e6dc 	strcc	lr, [r1, #-1756]	; 0xfffff924
d0011f0c:	d1dc2d08 	bicsle	r2, ip, r8, lsl #26
d0011f10:	447b4b9d 	ldrbtmi	r4, [fp], #-2973	; 0xfffff463
d0011f14:	2a006d1a 	bcs	0xd002d384
d0011f18:	aca8f47f 	cfstrsge	mvf15, [r8], #508	; 0x1fc
d0011f1c:	f8c34a9b 			; <UNDEFINED> instruction: 0xf8c34a9b
d0011f20:	447a8054 	ldrbtmi	r8, [sl], #-84	; 0xffffffac
d0011f24:	65de659f 	ldrbvs	r6, [lr, #1439]	; 0x59f
d0011f28:	e6cb651a 			; <UNDEFINED> instruction: 0xe6cb651a
d0011f2c:	0f01f1b8 	svceq	0x0001f1b8
d0011f30:	4648e4ac 	strbmi	lr, [r8], -ip, lsr #9
d0011f34:	f7fe9101 			; <UNDEFINED> instruction: 0xf7fe9101
d0011f38:	f1b0f9a1 			; <UNDEFINED> instruction: 0xf1b0f9a1
d0011f3c:	99010a00 	stmdbls	r1, {r9, fp}
d0011f40:	2328db4b 			; <UNDEFINED> instruction: 0x2328db4b
d0011f44:	880afb03 	stmdahi	sl, {r0, r1, r8, r9, fp, ip, sp, lr, pc}
d0011f48:	6378f648 	cmnvs	r8, #72, 12	; 0x4800000	; <UNPREDICTABLE>
d0011f4c:	5003f818 	andpl	pc, r3, r8, lsl r8	; <UNPREDICTABLE>
d0011f50:	d1382d07 	teqle	r8, r7, lsl #26
d0011f54:	205b498e 	subscs	r4, fp, lr, lsl #19
d0011f58:	f7fe4479 			; <UNDEFINED> instruction: 0xf7fe4479
d0011f5c:	2800ff45 	stmdacs	r0, {r0, r2, r6, r8, r9, sl, fp, ip, sp, lr, pc}
d0011f60:	ac84f43f 	cfstrsge	mvf15, [r4], {63}	; 0x3f
d0011f64:	46082101 	strmi	r2, [r8], -r1, lsl #2
d0011f68:	f974f000 			; <UNDEFINED> instruction: 0xf974f000
d0011f6c:	205d4989 	subscs	r4, sp, r9, lsl #19
d0011f70:	f7fe4479 			; <UNDEFINED> instruction: 0xf7fe4479
d0011f74:	2800ff39 	stmdacs	r0, {r0, r3, r4, r5, r8, r9, sl, fp, ip, sp, lr, pc}
d0011f78:	ac78f43f 	cfldrdge	mvd15, [r8], #-252	; 0xffffff04
d0011f7c:	20014651 	andcs	r4, r1, r1, asr r6
d0011f80:	f866f7ff 			; <UNDEFINED> instruction: 0xf866f7ff
d0011f84:	b9239b00 	stmdblt	r3!, {r8, r9, fp, ip, pc}
d0011f88:	4008f645 	andmi	pc, r8, r5, asr #12
d0011f8c:	ffbaf7fe 			; <UNDEFINED> instruction: 0xffbaf7fe
d0011f90:	203de698 	mlascs	sp, r8, r6, lr
d0011f94:	feecf7fe 	mcr2	7, 7, pc, cr12, cr14, {7}	; <UNPREDICTABLE>
d0011f98:	d0f52800 	rscsle	r2, r5, r0, lsl #16
d0011f9c:	0008f641 	andeq	pc, r8, r1, asr #12
d0011fa0:	ffb0f7fe 			; <UNDEFINED> instruction: 0xffb0f7fe
d0011fa4:	4003f24b 	andmi	pc, r3, fp, asr #4
d0011fa8:	ffacf7fe 			; <UNDEFINED> instruction: 0xffacf7fe
d0011fac:	46082101 	strmi	r2, [r8], -r1, lsl #2
d0011fb0:	f950f000 			; <UNDEFINED> instruction: 0xf950f000
d0011fb4:	4006f64b 	andmi	pc, r6, fp, asr #12
d0011fb8:	ffa4f7fe 			; <UNDEFINED> instruction: 0xffa4f7fe
d0011fbc:	0008f247 	andeq	pc, r8, r7, asr #4
d0011fc0:	ffa0f7fe 			; <UNDEFINED> instruction: 0xffa0f7fe
d0011fc4:	4651e6ee 	ldrbmi	lr, [r1], -lr, ror #13
d0011fc8:	f7ff2001 			; <UNDEFINED> instruction: 0xf7ff2001
d0011fcc:	f646f841 			; <UNDEFINED> instruction: 0xf646f841
d0011fd0:	f7fe0008 			; <UNDEFINED> instruction: 0xf7fe0008
d0011fd4:	2d01ff97 	stccs	15, cr15, [r1, #-604]	; 0xfffffda4
d0011fd8:	f8d8e458 			; <UNDEFINED> instruction: 0xf8d8e458
d0011fdc:	b153306c 	cmplt	r3, ip, rrx
d0011fe0:	46484a6d 	strbmi	r4, [r8], -sp, ror #20
d0011fe4:	f7fe447a 			; <UNDEFINED> instruction: 0xf7fe447a
d0011fe8:	b120f915 	msrlt	CPSR_, r5, lsl r9
d0011fec:	5000f44f 	andpl	pc, r0, pc, asr #8
d0011ff0:	ff88f7fe 			; <UNDEFINED> instruction: 0xff88f7fe
d0011ff4:	4b69e74f 	blmi	0xd1a8bd38
d0011ff8:	6d1a447b 	cfldrsvs	mvf4, [sl, #-492]	; 0xfffffe14
d0011ffc:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0012000:	4a67ac35 	bmi	0xd19fd0dc
d0012004:	e47c447a 	ldrbt	r4, [ip], #-1146	; 0xfffffb86
d0012008:	feb2f7fe 	mrc2	7, 5, pc, cr2, cr14, {7}
d001200c:	4621b150 			; <UNDEFINED> instruction: 0x4621b150
d0012010:	f0002001 			; <UNDEFINED> instruction: 0xf0002001
d0012014:	4963f91f 	stmdbmi	r3!, {r0, r1, r2, r3, r4, r8, fp, ip, sp, lr, pc}^
d0012018:	20294604 	eorcs	r4, r9, r4, lsl #12
d001201c:	f7fe4479 			; <UNDEFINED> instruction: 0xf7fe4479
d0012020:	e64ffee3 	strb	pc, [pc], -r3, ror #29	; <UNPREDICTABLE>
d0012024:	f7fe202b 			; <UNDEFINED> instruction: 0xf7fe202b
d0012028:	b170fea3 	cmnlt	r0, r3, lsr #29	; <UNPREDICTABLE>
d001202c:	f7ff2000 			; <UNDEFINED> instruction: 0xf7ff2000
d0012030:	2802fbf9 	stmdacs	r2, {r0, r3, r4, r5, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d0012034:	d11d4604 	tstle	sp, r4, lsl #12
d0012038:	447b4b5b 	ldrbtmi	r4, [fp], #-2907	; 0xfffff4a5
d001203c:	2a006d1a 	bcs	0xd002d4ac
d0012040:	ae40f47f 	mcrge	4, 2, pc, cr0, cr15, {3}	; <UNPREDICTABLE>
d0012044:	447a4a59 	ldrbtmi	r4, [sl], #-2649	; 0xfffff5a7
d0012048:	202de45b 	eorcs	lr, sp, fp, asr r4
d001204c:	fe90f7fe 	mrc2	7, 4, pc, cr0, cr14, {7}
d0012050:	d1eb2800 	mvnle	r2, r0, lsl #16
d0012054:	f7fe2021 			; <UNDEFINED> instruction: 0xf7fe2021
d0012058:	2800fe8b 	stmdacs	r0, {r0, r1, r3, r7, r9, sl, fp, ip, sp, lr, pc}
d001205c:	207ed1e6 	rsbscs	sp, lr, r6, ror #3
d0012060:	fe86f7fe 	mcr2	7, 4, pc, cr6, cr14, {7}	; <UNPREDICTABLE>
d0012064:	28004604 	stmdacs	r0, {r2, r9, sl, lr}
d0012068:	4851d1e0 	ldmdami	r1, {r5, r6, r7, r8, ip, lr, pc}^
d001206c:	f7fe4478 			; <UNDEFINED> instruction: 0xf7fe4478
d0012070:	e627feab 	strt	pc, [r7], -fp, lsr #29
d0012074:	d10b2803 	tstle	fp, r3, lsl #16
d0012078:	0f21f1bb 	svceq	0x0021f1bb
d001207c:	4b4dd018 	blmi	0xd13860e4
d0012080:	6d1a447b 	cfldrsvs	mvf4, [sl, #-492]	; 0xfffffe14
d0012084:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0012088:	4a4baf06 	bmi	0xd12fdca8
d001208c:	e438447a 	ldrt	r4, [r8], #-1146	; 0xfffffb86
d0012090:	0f2df1bb 	svceq	0x002df1bb
d0012094:	f244d102 	vrhadd.s8	d29, d4, d2
d0012098:	e7772040 	ldrb	r2, [r7, -r0, asr #32]!
d001209c:	0f7ef1bb 	svceq	0x007ef1bb
d00120a0:	f244d102 	vrhadd.s8	d29, d4, d2
d00120a4:	e77130c0 	ldrb	r3, [r1, -r0, asr #1]!
d00120a8:	0f21f1bb 	svceq	0x0021f1bb
d00120ac:	ae0af47f 	mcrge	4, 0, pc, cr10, cr15, {3}	; <UNPREDICTABLE>
d00120b0:	5020f44f 	eorpl	pc, r0, pc, asr #8
d00120b4:	ff26f7fe 			; <UNDEFINED> instruction: 0xff26f7fe
d00120b8:	f7ff2000 			; <UNDEFINED> instruction: 0xf7ff2000
d00120bc:	f7fff8c4 			; <UNDEFINED> instruction: 0xf7fff8c4
d00120c0:	2400bbd5 	strcs	fp, [r0], #-3029	; 0xfffff42b
d00120c4:	f89be606 			; <UNDEFINED> instruction: 0xf89be606
d00120c8:	f1083026 			; <UNDEFINED> instruction: 0xf1083026
d00120cc:	4c3b069c 	ldcmi	6, cr0, [fp], #-624	; 0xfffffd90
d00120d0:	23009301 	movwcs	r9, #769	; 0x301
d00120d4:	9300447c 	movwls	r4, #1148	; 0x47c
d00120d8:	447b4b39 	ldrbtmi	r4, [fp], #-2873	; 0xfffff4c7
d00120dc:	4b399304 	blmi	0xd0e76cf4
d00120e0:	ee08447b 	mcr	4, 0, r4, cr8, cr11, {3}
d00120e4:	e4473a10 	strb	r3, [r7], #-2576	; 0xfffff5f0
d00120e8:	00006794 	muleq	r0, r4, r7
d00120ec:	fffffc51 			; <UNDEFINED> instruction: 0xfffffc51
d00120f0:	000066cc 	andeq	r6, r0, ip, asr #13
d00120f4:	fffffce4 			; <UNDEFINED> instruction: 0xfffffce4
d00120f8:	fffffc2e 			; <UNDEFINED> instruction: 0xfffffc2e
d00120fc:	00006616 	andeq	r6, r0, r6, lsl r6
d0012100:	fffffaf6 			; <UNDEFINED> instruction: 0xfffffaf6
d0012104:	0000659a 	muleq	r0, sl, r5
d0012108:	0000657e 	andeq	r6, r0, lr, ror r5
d001210c:	fffffad8 			; <UNDEFINED> instruction: 0xfffffad8
d0012110:	fffff9e1 			; <UNDEFINED> instruction: 0xfffff9e1
d0012114:	00002eb6 			; <UNDEFINED> instruction: 0x00002eb6
d0012118:	00006520 	andeq	r6, r0, r0, lsr #10
d001211c:	0000650c 	andeq	r6, r0, ip, lsl #10
d0012120:	fffff959 			; <UNDEFINED> instruction: 0xfffff959
d0012124:	00002daf 	andeq	r2, r0, pc, lsr #27
d0012128:	fffff926 			; <UNDEFINED> instruction: 0xfffff926
d001212c:	00002e65 	andeq	r2, r0, r5, ror #28
d0012130:	fffffa34 			; <UNDEFINED> instruction: 0xfffffa34
d0012134:	0000648c 	andeq	r6, r0, ip, lsl #9
d0012138:	00006470 	andeq	r6, r0, r0, ror r4
d001213c:	fffff9f2 			; <UNDEFINED> instruction: 0xfffff9f2
d0012140:	000063e4 	andeq	r6, r0, r4, ror #7
d0012144:	fffff99f 			; <UNDEFINED> instruction: 0xfffff99f
d0012148:	fffff958 			; <UNDEFINED> instruction: 0xfffff958
d001214c:	000062f8 	strdeq	r6, [r0], -r8
d0012150:	000062c6 	andeq	r6, r0, r6, asr #5
d0012154:	fffff961 			; <UNDEFINED> instruction: 0xfffff961
d0012158:	0000628a 	andeq	r6, r0, sl, lsl #5
d001215c:	fffff953 			; <UNDEFINED> instruction: 0xfffff953
d0012160:	fffff8c8 			; <UNDEFINED> instruction: 0xfffff8c8
d0012164:	0000622c 	andeq	r6, r0, ip, lsr #4
d0012168:	fffff8bb 			; <UNDEFINED> instruction: 0xfffff8bb
d001216c:	000061a6 	andeq	r6, r0, r6, lsr #3
d0012170:	00006150 	andeq	r6, r0, r0, asr r1
d0012174:	fffff847 			; <UNDEFINED> instruction: 0xfffff847
d0012178:	0000611e 	andeq	r6, r0, lr, lsl r1
d001217c:	fffff84d 			; <UNDEFINED> instruction: 0xfffff84d
d0012180:	00005030 	andeq	r5, r0, r0, lsr r0
d0012184:	000060d2 	ldrdeq	r6, [r0], -r2
d0012188:	000060ae 	andeq	r6, r0, lr, lsr #1
d001218c:	fffff7f2 			; <UNDEFINED> instruction: 0xfffff7f2
d0012190:	fffff7d7 			; <UNDEFINED> instruction: 0xfffff7d7
d0012194:	fffff7eb 			; <UNDEFINED> instruction: 0xfffff7eb
d0012198:	fffff332 			; <UNDEFINED> instruction: 0xfffff332
d001219c:	00005fc8 	andeq	r5, r0, r8, asr #31
d00121a0:	fffff77b 			; <UNDEFINED> instruction: 0xfffff77b
d00121a4:	fffff784 			; <UNDEFINED> instruction: 0xfffff784
d00121a8:	00005f86 	andeq	r5, r0, r6, lsl #31
d00121ac:	fffff767 			; <UNDEFINED> instruction: 0xfffff767
d00121b0:	fffff792 			; <UNDEFINED> instruction: 0xfffff792
d00121b4:	00005f40 	andeq	r5, r0, r0, asr #30
d00121b8:	fffff747 			; <UNDEFINED> instruction: 0xfffff747
d00121bc:	00005eec 	andeq	r5, r0, ip, ror #29
d00121c0:	00005ee6 	andeq	r5, r0, r6, ror #29
d00121c4:	fffff3ff 			; <UNDEFINED> instruction: 0xfffff3ff

Disassembly of section .text.expression.constprop.0:

d0012254 <.text.expression.constprop.0>:
d0012254:	345cf8df 	ldrbcc	pc, [ip], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d0012258:	e92d447b 	push	{r0, r1, r3, r4, r5, r6, sl, lr}
d001225c:	6a5f4ff0 	bvs	0xd17e6224
d0012260:	f8d3b085 			; <UNDEFINED> instruction: 0xf8d3b085
d0012264:	f8938028 			; <UNDEFINED> instruction: 0xf8938028
d0012268:	f5039030 			; <UNDEFINED> instruction: 0xf5039030
d001226c:	90023393 	mulls	r2, r3, r3
d0012270:	91006fda 	ldrdls	r6, [r0, -sl]
d0012274:	2a203201 	bcs	0xd081ea80
d0012278:	d90467da 	stmdble	r4, {r1, r3, r4, r6, r7, r8, r9, sl, sp, lr}
d001227c:	0438f8df 	ldrteq	pc, [r8], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d0012280:	f7fe4478 			; <UNDEFINED> instruction: 0xf7fe4478
d0012284:	9b00fda1 	blls	0xd0051910
d0012288:	6430f8df 	ldrtvs	pc, [r0], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d001228c:	447e3b03 	ldrbtmi	r3, [lr], #-2819	; 0xfffff4fd
d0012290:	41584258 	cmpmi	r8, r8, asr r2
d0012294:	fac6f7ff 	blx	0xcf1d0298
d0012298:	3424f8df 	strtcc	pc, [r4], #-2271	; 0xfffff721
d001229c:	447b4682 	ldrbtmi	r4, [fp], #-1666	; 0xfffff97e
d00122a0:	f8df9301 			; <UNDEFINED> instruction: 0xf8df9301
d00122a4:	447b3420 	ldrbtmi	r3, [fp], #-1056	; 0xfffffbe0
d00122a8:	9b019303 	blls	0xd0076ebc
d00122ac:	b9ad6d1d 	stmiblt	sp!, {r0, r2, r3, r4, r8, sl, fp, sp, lr}
d00122b0:	2c5e6adc 	mrrccs	10, 13, r6, lr, cr12
d00122b4:	8172f000 	cmnhi	r2, r0	; <UNPREDICTABLE>
d00122b8:	814ef300 	mrshi	pc, SPSR_hyp	; <UNPREDICTABLE>
d00122bc:	f3002c2f 			; <UNDEFINED> instruction: 0xf3002c2f
d00122c0:	2c248144 	stfcsd	f0, [r4], #-272	; 0xfffffef0
d00122c4:	8131f300 	teqhi	r1, r0, lsl #6	; <UNPREDICTABLE>
d00122c8:	42ab9b02 	adcmi	r9, fp, #2048	; 0x800
d00122cc:	f1badc06 			; <UNDEFINED> instruction: 0xf1badc06
d00122d0:	d1230f02 			; <UNDEFINED> instruction: 0xd1230f02
d00122d4:	447848fc 	ldrbtmi	r4, [r8], #-2300	; 0xfffff704
d00122d8:	fd76f7fe 	ldc2l	7, cr15, [r6, #-1016]!	; 0xfffffc08
d00122dc:	3b019b00 	blcc	0xd0078ee4
d00122e0:	f2002b01 	vqdmulh.s<illegal width 8>	d2, d0, d1
d00122e4:	f1ba8163 			; <UNDEFINED> instruction: 0xf1ba8163
d00122e8:	f0400f02 			; <UNDEFINED> instruction: 0xf0400f02
d00122ec:	4bf7815f 	blmi	0xcfdf2870
d00122f0:	6d1a447b 	cfldrsvs	mvf4, [sl, #-492]	; 0xfffffe14
d00122f4:	4af6b93a 	bmi	0xcfdc07e4
d00122f8:	651a447a 	ldrvs	r4, [sl, #-1146]	; 0xfffffb86
d00122fc:	f8c3655f 			; <UNDEFINED> instruction: 0xf8c3655f
d0012300:	f8c38058 			; <UNDEFINED> instruction: 0xf8c38058
d0012304:	4bf3905c 	blmi	0xcfcf647c
d0012308:	447b4650 	ldrbtmi	r4, [fp], #-1616	; 0xfffff9b0
d001230c:	3393f503 	orrscc	pc, r3, #12582912	; 0xc00000
d0012310:	3a016fda 	bcc	0xd006e280
d0012314:	b00567da 	ldrdlt	r6, [r5], -sl
d0012318:	8ff0e8bd 	svchi	0x00f0e8bd
d001231c:	7b8bf46f 	blvc	0xce30f4e0
d0012320:	f9d6f7fe 			; <UNDEFINED> instruction: 0xf9d6f7fe
d0012324:	eb043501 	bl	0xd011f730
d0012328:	2b01030b 	blcs	0xd0052f5c
d001232c:	f5a4d82e 			; <UNDEFINED> instruction: 0xf5a4d82e
d0012330:	f1de7e8c 			; <UNDEFINED> instruction: 0xf1de7e8c
d0012334:	eb440400 	bl	0xd111333c
d0012338:	4620040e 	strtmi	r0, [r0], -lr, lsl #8
d001233c:	ff70f7fe 			; <UNDEFINED> instruction: 0xff70f7fe
d0012340:	46284683 	strtmi	r4, [r8], -r3, lsl #13
d0012344:	21024de4 	smlattcs	r2, r4, sp, r4
d0012348:	ff84f7ff 			; <UNDEFINED> instruction: 0xff84f7ff
d001234c:	f44f447d 	vst3.16	{d20-d22}, [pc :256]!
d0012350:	f7fe5020 			; <UNDEFINED> instruction: 0xf7fe5020
d0012354:	2001fdd7 	ldrdcs	pc, [r1], -r7
d0012358:	ff75f7fe 			; <UNDEFINED> instruction: 0xff75f7fe
d001235c:	ff50f7fe 			; <UNDEFINED> instruction: 0xff50f7fe
d0012360:	f8d52300 			; <UNDEFINED> instruction: 0xf8d52300
d0012364:	46822e48 	strmi	r2, [r2], r8, asr #28
d0012368:	6d284659 	stcvs	6, cr4, [r8, #-356]!	; 0xfffffe9c
d001236c:	f840f7ff 			; <UNDEFINED> instruction: 0xf840f7ff
d0012370:	20004621 	andcs	r4, r0, r1, lsr #12
d0012374:	fdeaf7fe 	stc2l	7, cr15, [sl, #1016]!	; 0x3f8
d0012378:	f8d52300 			; <UNDEFINED> instruction: 0xf8d52300
d001237c:	46512e48 	ldrbmi	r2, [r1], -r8, asr #28
d0012380:	f7ff6d28 			; <UNDEFINED> instruction: 0xf7ff6d28
d0012384:	f04ff835 			; <UNDEFINED> instruction: 0xf04ff835
d0012388:	e78e0a00 	str	r0, [lr, r0, lsl #20]
d001238c:	7c89f46f 	cfstrsvc	mvf15, [r9], {111}	; 0x6f
d0012390:	0f03f1ba 	svceq	0x0003f1ba
d0012394:	0b0ceb04 	bleq	0xd034cfac
d0012398:	f1bbd110 			; <UNDEFINED> instruction: 0xf1bbd110
d001239c:	d90d0f01 	stmdble	sp, {r0, r8, r9, sl, fp}
d00123a0:	447b4bce 	ldrbtmi	r4, [fp], #-3022	; 0xfffff432
d00123a4:	2a006d1a 	bcs	0xd002d814
d00123a8:	4acdd198 	bmi	0xcf386a10
d00123ac:	447a655f 	ldrbtmi	r6, [sl], #-1375	; 0xfffffaa1
d00123b0:	8058f8c3 	subshi	pc, r8, r3, asr #17
d00123b4:	905cf8c3 	subsls	pc, ip, r3, asr #17
d00123b8:	e78f651a 	usada8	pc, sl, r5, r6	; <UNPREDICTABLE>
d00123bc:	4003f24b 	andmi	pc, r3, fp, asr #4
d00123c0:	fda0f7fe 	stc2	7, cr15, [r0, #1016]!	; 0x3f8
d00123c4:	0f02f1bb 	svceq	0x0002f1bb
d00123c8:	bf344628 	svclt	0x00344628
d00123cc:	21012102 	tstcs	r1, r2, lsl #2
d00123d0:	ff40f7ff 			; <UNDEFINED> instruction: 0xff40f7ff
d00123d4:	0f01f1bb 	svceq	0x0001f1bb
d00123d8:	d8114605 	ldmdale	r1, {r0, r2, r9, sl, lr}
d00123dc:	0103f1aa 	smlatbeq	r3, sl, r1, pc	; <UNPREDICTABLE>
d00123e0:	424a3803 	submi	r3, sl, #196608	; 0x30000
d00123e4:	4243414a 	submi	r4, r3, #-2147483630	; 0x80000012
d00123e8:	429a4143 	addsmi	r4, sl, #-1073741808	; 0xc0000010
d00123ec:	6d33d008 	ldcvs	0, cr13, [r3, #-32]!	; 0xffffffe0
d00123f0:	9b03b933 	blls	0xd01008c4
d00123f4:	65336577 	ldrvs	r6, [r3, #-1399]!	; 0xfffffa89
d00123f8:	8058f8c6 	subshi	pc, r8, r6, asr #17
d00123fc:	905cf8c6 	subsls	pc, ip, r6, asr #17
d0012400:	4006f64b 	andmi	pc, r6, fp, asr #12
d0012404:	fd7ef7fe 	ldc2l	7, cr15, [lr, #-1016]!	; 0xfffffc08
d0012408:	0f01f1ba 	svceq	0x0001f1ba
d001240c:	80dff000 	sbcshi	pc, pc, r0
d0012410:	f0402d01 			; <UNDEFINED> instruction: 0xf0402d01
d0012414:	2c2f8124 	stfcsd	f0, [pc], #-144	; 0xd001238c
d0012418:	811af300 	tsthi	sl, r0, lsl #6	; <UNPREDICTABLE>
d001241c:	f3402c24 			; <UNDEFINED> instruction: 0xf3402c24
d0012420:	f1a48100 			; <UNDEFINED> instruction: 0xf1a48100
d0012424:	2b0a0325 	blcs	0xd02930c0
d0012428:	80fbf200 	rscshi	pc, fp, r0, lsl #4
d001242c:	f013e8df 			; <UNDEFINED> instruction: 0xf013e8df
d0012430:	0025004a 	eoreq	r0, r5, sl, asr #32
d0012434:	00f900f9 	ldrshteq	r0, [r9], #9
d0012438:	001d00f9 	ldrsheq	r0, [sp], -r9
d001243c:	00f9000b 	rscseq	r0, r9, fp
d0012440:	00f90015 	rscseq	r0, r9, r5, lsl r0
d0012444:	f04f003c 			; <UNDEFINED> instruction: 0xf04f003c
d0012448:	f6410a01 			; <UNDEFINED> instruction: 0xf6410a01
d001244c:	f7fe0008 			; <UNDEFINED> instruction: 0xf7fe0008
d0012450:	e72afd59 			; <UNDEFINED> instruction: 0xe72afd59
d0012454:	0a00f04f 	beq	0xd004e598
d0012458:	f04fe7f7 			; <UNDEFINED> instruction: 0xf04fe7f7
d001245c:	f6410a01 			; <UNDEFINED> instruction: 0xf6410a01
d0012460:	e7f42008 	ldrb	r2, [r4, r8]!
d0012464:	0a00f04f 	beq	0xd004e5a8
d0012468:	f04fe7f9 			; <UNDEFINED> instruction: 0xf04fe7f9
d001246c:	f2440a01 	vpmax.s8	d16, d4, d1
d0012470:	e7ec3048 	strb	r3, [ip, r8, asr #32]!
d0012474:	0a00f04f 	beq	0xd004e5b8
d0012478:	f04fe7f9 			; <UNDEFINED> instruction: 0xf04fe7f9
d001247c:	f2440a01 	vpmax.s8	d16, d4, d1
d0012480:	e7e40008 	strb	r0, [r4, r8]!
d0012484:	0a00f04f 	beq	0xd004e5c8
d0012488:	4655e7f9 			; <UNDEFINED> instruction: 0x4655e7f9
d001248c:	3008f244 	andcc	pc, r8, r4, asr #4
d0012490:	f7fe46aa 			; <UNDEFINED> instruction: 0xf7fe46aa
d0012494:	e708fd37 	smuadx	r8, r7, sp
d0012498:	e7f72500 	ldrb	r2, [r7, r0, lsl #10]!
d001249c:	f2444655 	vmin.s8	q10, q2, <illegal reg q2.5>
d00124a0:	e7f50048 	ldrb	r0, [r5, r8, asr #32]!
d00124a4:	e7fa2500 	ldrb	r2, [sl, r0, lsl #10]!
d00124a8:	0a01f04f 	beq	0xd008e5ec
d00124ac:	30b1f64f 	adcscc	pc, r1, pc, asr #12
d00124b0:	fd28f7fe 	stc2	7, cr15, [r8, #-1016]!	; 0xfffffc08
d00124b4:	00f0f24f 	rscseq	pc, r0, pc, asr #4
d00124b8:	f04fe7c9 			; <UNDEFINED> instruction: 0xf04fe7c9
d00124bc:	f64f0a00 			; <UNDEFINED> instruction: 0xf64f0a00
d00124c0:	e7f53091 			; <UNDEFINED> instruction: 0xe7f53091
d00124c4:	0a01f04f 	beq	0xd008e608
d00124c8:	30b1f64f 	adcscc	pc, r1, pc, asr #12
d00124cc:	fd1af7fe 	ldc2	7, cr15, [sl, #-1016]	; 0xfffffc08
d00124d0:	20f0f24f 	rscscs	pc, r0, pc, asr #4
d00124d4:	fd16f7fe 	ldc2	7, cr15, [r6, #-1016]	; 0xfffffc08
d00124d8:	3050f244 	subscc	pc, r0, r4, asr #4
d00124dc:	fd12f7fe 	ldc2	7, cr15, [r2, #-1016]	; 0xfffffc08
d00124e0:	f04fe7bd 			; <UNDEFINED> instruction: 0xf04fe7bd
d00124e4:	f64f0a00 			; <UNDEFINED> instruction: 0xf64f0a00
d00124e8:	e7ef3091 			; <UNDEFINED> instruction: 0xe7ef3091
d00124ec:	748af5a4 	strvc	pc, [sl], #1444	; 0x5a4
d00124f0:	d8032c02 	stmdale	r3, {r1, sl, fp, sp}
d00124f4:	f004e8df 			; <UNDEFINED> instruction: 0xf004e8df
d00124f8:	00081206 	andeq	r1, r8, r6, lsl #4
d00124fc:	f7fe2000 			; <UNDEFINED> instruction: 0xf7fe2000
d0012500:	e740fea2 	strb	pc, [r0, -r2, lsr #29]	; <UNPREDICTABLE>
d0012504:	e7fa2001 	ldrb	r2, [sl, r1]!
d0012508:	bf0c2d00 	svclt	0x000c2d00
d001250c:	2002200a 	andcs	r2, r2, sl
d0012510:	2d00e7f5 	stccs	7, cr14, [r0, #-980]	; 0xfffffc2c
d0012514:	200bbf0c 	andcs	fp, fp, ip, lsl #30
d0012518:	e7f02003 	ldrb	r2, [r0, r3]!
d001251c:	bf0c2d00 	svclt	0x000c2d00
d0012520:	2009200d 	andcs	r2, r9, sp
d0012524:	2502e7eb 	strcs	lr, [r2, #-2027]	; 0xfffff815
d0012528:	f1a4e6ce 			; <UNDEFINED> instruction: 0xf1a4e6ce
d001252c:	2b0a0325 	blcs	0xd02931c8
d0012530:	e8dfd809 	ldm	pc, {r0, r3, fp, ip, lr, pc}^	; <UNPREDICTABLE>
d0012534:	3731f003 	ldrcc	pc, [r1, -r3]!
d0012538:	31080808 	tstcc	r8, r8, lsl #16
d001253c:	08060806 	stmdaeq	r6, {r1, r2, fp}
d0012540:	25080031 	strcs	r0, [r8, #-49]	; 0xffffffcf
d0012544:	2500e6c0 	strcs	lr, [r0, #-1728]	; 0xfffff940
d0012548:	f024e6be 			; <UNDEFINED> instruction: 0xf024e6be
d001254c:	2b3c0302 	blcs	0xd0f1315c
d0012550:	2500bf14 	strcs	fp, [r0, #-3860]	; 0xfffff0ec
d0012554:	e6b72507 	ldrt	r2, [r7], r7, lsl #10
d0012558:	d0252c7c 	eorle	r2, r5, ip, ror ip
d001255c:	7389f46f 	orrvc	pc, r9, #1862270976	; 0x6f000000
d0012560:	2b0518e3 	blcs	0xd01588f4
d0012564:	aeb0f63f 	mrcge	6, 5, APSR_nzcv, cr0, cr15, {1}
d0012568:	d8ec2b05 	stmiale	ip!, {r0, r2, r8, r9, fp, sp}^
d001256c:	f852a202 			; <UNDEFINED> instruction: 0xf852a202
d0012570:	441a3023 	ldrmi	r3, [sl], #-35	; 0xffffffdd
d0012574:	bf004710 	svclt	0x00004710
d0012578:	00000019 	andeq	r0, r0, r9, lsl r0
d001257c:	00000019 	andeq	r0, r0, r9, lsl r0
d0012580:	0000001d 	andeq	r0, r0, sp, lsl r0
d0012584:	0000001d 	andeq	r0, r0, sp, lsl r0
d0012588:	ffffffaf 			; <UNDEFINED> instruction: 0xffffffaf
d001258c:	00000029 	andeq	r0, r0, r9, lsr #32
d0012590:	e6992506 	ldr	r2, [r9], r6, lsl #10
d0012594:	e6972507 	ldr	r2, [r7], r7, lsl #10
d0012598:	e6952509 	ldr	r2, [r5], r9, lsl #10
d001259c:	e6932504 	ldr	r2, [r3], r4, lsl #10
d00125a0:	e6912501 	ldr	r2, [r1], r1, lsl #10
d00125a4:	e68f2505 	str	r2, [pc], r5, lsl #10
d00125a8:	e68d2503 	str	r2, [sp], r3, lsl #10
d00125ac:	2b019b00 	blcs	0xd00791b4
d00125b0:	aea9f47f 	mcrge	4, 5, pc, cr9, cr15, {3}	; <UNPREDICTABLE>
d00125b4:	0f03f1ba 	svceq	0x0003f1ba
d00125b8:	aea5f47f 	mcrge	4, 5, pc, cr5, cr15, {3}	; <UNPREDICTABLE>
d00125bc:	447b4b49 	ldrbtmi	r4, [fp], #-2889	; 0xfffff4b7
d00125c0:	2a006d1a 	bcs	0xd002da30
d00125c4:	ae9ff47f 	mrcge	4, 4, APSR_nzcv, cr15, cr15, {3}
d00125c8:	447a4a47 	ldrbtmi	r4, [sl], #-2631	; 0xfffff5b9
d00125cc:	2c2fe695 	stccs	6, cr14, [pc], #-596	; 0xd0012380
d00125d0:	2c24dc20 	stccs	12, cr13, [r4], #-128	; 0xffffff80
d00125d4:	f1a4dd24 			; <UNDEFINED> instruction: 0xf1a4dd24
d00125d8:	2b0a0325 	blcs	0xd0293274
d00125dc:	a202d820 	andge	sp, r2, #32, 16	; 0x200000
d00125e0:	3023f852 	eorcc	pc, r3, r2, asr r8	; <UNPREDICTABLE>
d00125e4:	4710441a 			; <UNDEFINED> instruction: 0x4710441a
d00125e8:	fffffee1 			; <UNDEFINED> instruction: 0xfffffee1
d00125ec:	fffffe97 			; <UNDEFINED> instruction: 0xfffffe97
d00125f0:	00000039 	andeq	r0, r0, r9, lsr r0
d00125f4:	00000039 	andeq	r0, r0, r9, lsr r0
d00125f8:	00000039 	andeq	r0, r0, r9, lsr r0
d00125fc:	fffffe87 			; <UNDEFINED> instruction: 0xfffffe87
d0012600:	fffffe63 			; <UNDEFINED> instruction: 0xfffffe63
d0012604:	00000039 	andeq	r0, r0, r9, lsr r0
d0012608:	fffffe77 			; <UNDEFINED> instruction: 0xfffffe77
d001260c:	00000039 	andeq	r0, r0, r9, lsr r0
d0012610:	fffffec5 			; <UNDEFINED> instruction: 0xfffffec5
d0012614:	f43f2c5e 			; <UNDEFINED> instruction: 0xf43f2c5e
d0012618:	2c7caf41 	ldclcs	15, cr10, [ip], #-260	; 0xfffffefc
d001261c:	af35f43f 	svcge	0x0035f43f
d0012620:	f2442501 	vrshl.s8	d18, d1, d4
d0012624:	f7fe2081 			; <UNDEFINED> instruction: 0xf7fe2081
d0012628:	f5b4fc6d 			; <UNDEFINED> instruction: 0xf5b4fc6d
d001262c:	f73f7f8b 			; <UNDEFINED> instruction: 0xf73f7f8b
d0012630:	f5b4aeaa 			; <UNDEFINED> instruction: 0xf5b4aeaa
d0012634:	f73f7f89 			; <UNDEFINED> instruction: 0xf73f7f89
d0012638:	2c3caf59 	ldccs	15, cr10, [ip], #-356	; 0xfffffe9c
d001263c:	af69f43f 	svcge	0x0069f43f
d0012640:	f47f2c3e 			; <UNDEFINED> instruction: 0xf47f2c3e
d0012644:	2d00aea0 	stccs	14, cr10, [r0, #-640]	; 0xfffffd80
d0012648:	200cbf0c 	andcs	fp, ip, ip, lsl #30
d001264c:	e7562008 	ldrb	r2, [r6, -r8]
d0012650:	f43f2c5e 			; <UNDEFINED> instruction: 0xf43f2c5e
d0012654:	2c7caf24 	ldclcs	15, cr10, [ip], #-144	; 0xffffff70
d0012658:	af18f43f 	svcge	0x0018f43f
d001265c:	2c2fe7e1 	stccs	7, cr14, [pc], #-900	; 0xd00122e0
d0012660:	2c24dc20 	stccs	12, cr13, [r4], #-128	; 0xffffff80
d0012664:	f1a4dd24 			; <UNDEFINED> instruction: 0xf1a4dd24
d0012668:	2b0a0325 	blcs	0xd0293304
d001266c:	a202d820 	andge	sp, r2, #32, 16	; 0x200000
d0012670:	3023f852 	eorcc	pc, r3, r2, asr r8	; <UNPREDICTABLE>
d0012674:	4710441a 			; <UNDEFINED> instruction: 0x4710441a
d0012678:	fffffe6b 			; <UNDEFINED> instruction: 0xfffffe6b
d001267c:	fffffe0d 			; <UNDEFINED> instruction: 0xfffffe0d
d0012680:	00000039 	andeq	r0, r0, r9, lsr r0
d0012684:	00000039 	andeq	r0, r0, r9, lsr r0
d0012688:	00000039 	andeq	r0, r0, r9, lsr r0
d001268c:	fffffdfd 			; <UNDEFINED> instruction: 0xfffffdfd
d0012690:	fffffddd 			; <UNDEFINED> instruction: 0xfffffddd
d0012694:	00000039 	andeq	r0, r0, r9, lsr r0
d0012698:	fffffded 			; <UNDEFINED> instruction: 0xfffffded
d001269c:	00000039 	andeq	r0, r0, r9, lsr r0
d00126a0:	fffffe43 			; <UNDEFINED> instruction: 0xfffffe43
d00126a4:	f43f2c5e 			; <UNDEFINED> instruction: 0xf43f2c5e
d00126a8:	2c7caefd 	ldclcs	14, cr10, [ip], #-1012	; 0xfffffc0c
d00126ac:	aef4f43f 	mrcge	4, 7, APSR_nzcv, cr4, cr15, {1}
d00126b0:	e7b62500 	ldr	r2, [r6, r0, lsl #10]!
d00126b4:	00005d68 	andeq	r5, r0, r8, ror #26
d00126b8:	fffff237 			; <UNDEFINED> instruction: 0xfffff237
d00126bc:	00005d32 	andeq	r5, r0, r2, lsr sp
d00126c0:	00005d22 	andeq	r5, r0, r2, lsr #26
d00126c4:	ffffff1e 			; <UNDEFINED> instruction: 0xffffff1e
d00126c8:	fffff4d7 			; <UNDEFINED> instruction: 0xfffff4d7
d00126cc:	00005cd0 	ldrdeq	r5, [r0], -r0
d00126d0:	ffffff0b 			; <UNDEFINED> instruction: 0xffffff0b
d00126d4:	00005cb6 			; <UNDEFINED> instruction: 0x00005cb6
d00126d8:	00005c74 	andeq	r5, r0, r4, ror ip
d00126dc:	00005c1e 	andeq	r5, r0, lr, lsl ip
d00126e0:	fffff425 			; <UNDEFINED> instruction: 0xfffff425
d00126e4:	00005a02 	andeq	r5, r0, r2, lsl #20
d00126e8:	fffffc5d 			; <UNDEFINED> instruction: 0xfffffc5d

Disassembly of section .text.condition.constprop.0:

d0012728 <.text.condition.constprop.0>:
d0012728:	20284908 	eorcs	r4, r8, r8, lsl #18
d001272c:	4479b508 	ldrbtmi	fp, [r9], #-1288	; 0xfffffaf8
d0012730:	fb5af7fe 	blx	0xd16d0732
d0012734:	20012102 	andcs	r2, r1, r2, lsl #2
d0012738:	fd8cf7ff 	stc2	7, cr15, [ip, #1020]	; 0x3fc
d001273c:	20294904 	eorcs	r4, r9, r4, lsl #18
d0012740:	e8bd4479 	pop	{r0, r3, r4, r5, r6, sl, lr}
d0012744:	f7fe4008 			; <UNDEFINED> instruction: 0xf7fe4008
d0012748:	bf00bb4f 	svclt	0x0000bb4f
d001274c:	ffffffba 			; <UNDEFINED> instruction: 0xffffffba
d0012750:	ffffffc6 			; <UNDEFINED> instruction: 0xffffffc6

Disassembly of section .text.block.constprop.0:

d001283c <.text.block.constprop.0>:
d001283c:	4ff0e92d 	svcmi	0x00f0e92d
d0012840:	b0934f73 	addslt	r4, r3, r3, ror pc
d0012844:	81ccf8df 	ldrdhi	pc, [ip, #143]	; 0x8f
d0012848:	44f8447f 	ldrbtmi	r4, [r8], #1151	; 0x47f
d001284c:	3993f507 	ldmibcc	r3, {r0, r1, r2, r8, sl, ip, sp, lr, pc}
d0012850:	6050f8d8 	ldrsbvs	pc, [r0], #-136	; 0xffffff78	; <UNPREDICTABLE>
d0012854:	f8d8b936 			; <UNDEFINED> instruction: 0xf8d8b936
d0012858:	2b7d302c 	blcs	0xd1f5e910
d001285c:	f5b3d002 			; <UNDEFINED> instruction: 0xf5b3d002
d0012860:	d1077f80 	smlabble	r7, r0, pc, r7	; <UNPREDICTABLE>
d0012864:	207d496c 	rsbscs	r4, sp, ip, ror #18
d0012868:	b0134479 	andslt	r4, r3, r9, ror r4
d001286c:	4ff0e8bd 	svcmi	0x00f0e8bd
d0012870:	babaf7fe 	blt	0xceed0870
d0012874:	1007f240 	andne	pc, r7, r0, asr #4
d0012878:	fa7af7fe 	blx	0xd1ed0878
d001287c:	f8d8b9c0 			; <UNDEFINED> instruction: 0xf8d8b9c0
d0012880:	f240202c 	vhadd.s8	d18, d0, d28
d0012884:	429a1301 	addsmi	r1, sl, #67108864	; 0x4000000
d0012888:	f8d8d137 			; <UNDEFINED> instruction: 0xf8d8d137
d001288c:	f8d8101c 			; <UNDEFINED> instruction: 0xf8d8101c
d0012890:	f7fe0018 			; <UNDEFINED> instruction: 0xf7fe0018
d0012894:	2800fae5 	stmdacs	r0, {r0, r2, r5, r6, r7, r9, fp, ip, sp, lr, pc}
d0012898:	4860da2f 	stmdami	r0!, {r0, r1, r2, r3, r5, r9, fp, ip, lr, pc}^
d001289c:	f7fe4478 			; <UNDEFINED> instruction: 0xf7fe4478
d00128a0:	bb68fa79 	bllt	0xd1a5128c
d00128a4:	4478485e 	ldrbtmi	r4, [r8], #-2142	; 0xfffff7a2
d00128a8:	fa74f7fe 	blx	0xd1d508a8
d00128ac:	2605b1f8 			; <UNDEFINED> instruction: 0x2605b1f8
d00128b0:	ac044d5c 	stcge	13, cr4, [r4], {92}	; 0x5c
d00128b4:	f105447d 			; <UNDEFINED> instruction: 0xf105447d
d00128b8:	e8bc0c18 	ldm	ip!, {r3, r4, sl, fp}
d00128bc:	c40f000f 	strgt	r0, [pc], #-15	; 0xd00128c4
d00128c0:	0007e89c 	muleq	r7, ip, r8
d00128c4:	0007e884 	andeq	lr, r7, r4, lsl #17
d00128c8:	f2404957 	vmul.i8	q10, q0, <illegal reg q3.5>
d00128cc:	44791001 	ldrbtmi	r1, [r9], #-1
d00128d0:	fa8af7fe 	blx	0xce2d08d0
d00128d4:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d00128d8:	6aeb8097 	bvs	0xcfaf2b3c
d00128dc:	d1112b5b 	tstle	r1, fp, asr fp
d00128e0:	44784852 	ldrbtmi	r4, [r8], #-2130	; 0xfffff7ae
d00128e4:	e8bdb013 	pop	{r0, r1, r4, ip, sp, pc}
d00128e8:	f7fe4ff0 			; <UNDEFINED> instruction: 0xf7fe4ff0
d00128ec:	4850ba6d 	ldmdami	r0, {r0, r2, r3, r5, r6, r9, fp, ip, sp, pc}^
d00128f0:	f7fe4478 			; <UNDEFINED> instruction: 0xf7fe4478
d00128f4:	2800fa4f 	stmdacs	r0, {r0, r1, r2, r3, r6, r9, fp, ip, sp, lr, pc}
d00128f8:	f000d1d9 			; <UNDEFINED> instruction: 0xf000d1d9
d00128fc:	e7a7f965 	str	pc, [r7, r5, ror #18]!
d0012900:	e7d52601 	ldrb	r2, [r5, r1, lsl #12]
d0012904:	0c10f10d 	ldfeqd	f7, [r0], {13}
d0012908:	f8ddac0b 			; <UNDEFINED> instruction: 0xf8ddac0b
d001290c:	f89db020 			; <UNDEFINED> instruction: 0xf89db020
d0012910:	e8bca028 	ldm	ip!, {r3, r5, sp, pc}
d0012914:	c40f000f 	strgt	r0, [pc], #-15	; 0xd001291c
d0012918:	0007e89c 	muleq	r7, ip, r8
d001291c:	0007e884 	andeq	lr, r7, r4, lsl #17
d0012920:	2104e9dd 	ldrdcs	lr, [r4, -sp]
d0012924:	46109b07 	ldrmi	r9, [r0], -r7, lsl #22
d0012928:	93039102 	movwls	r9, #12546	; 0x3102
d001292c:	f7fe9201 			; <UNDEFINED> instruction: 0xf7fe9201
d0012930:	2800fa97 	stmdacs	r0, {r0, r1, r2, r4, r7, r9, fp, ip, sp, lr, pc}
d0012934:	99029a01 	stmdbls	r2, {r0, r9, fp, ip, pc}
d0012938:	db2d9b03 	blle	0xd0b7954c
d001293c:	1040eb05 	subne	lr, r0, r5, lsl #22
d0012940:	308ff500 	addcc	pc, pc, r0, lsl #10
d0012944:	408cf890 	umullmi	pc, ip, r0, r8	; <UNPREDICTABLE>
d0012948:	3093f505 	addscc	pc, r3, r5, lsl #10
d001294c:	42846f80 	addmi	r6, r4, #128, 30	; 0x200
d0012950:	6d2cd122 	stfvsd	f5, [ip, #-136]!	; 0xffffff78
d0012954:	d1552c00 	cmple	r5, r0, lsl #24
d0012958:	656b4a36 	strbvs	r4, [fp, #-2614]!	; 0xfffff5ca
d001295c:	f8c5447a 			; <UNDEFINED> instruction: 0xf8c5447a
d0012960:	f8c5b058 			; <UNDEFINED> instruction: 0xf8c5b058
d0012964:	652aa05c 	strvs	sl, [sl, #-92]!	; 0xffffffa4
d0012968:	f7fe203d 			; <UNDEFINED> instruction: 0xf7fe203d
d001296c:	b168fa01 	msrlt	(UNDEF: 104), r1
d0012970:	46082101 	strmi	r2, [r8], -r1, lsl #2
d0012974:	fc6ef7ff 	stc2l	7, cr15, [lr], #-1020	; 0xfffffc04
d0012978:	d1032e05 	tstle	r3, r5, lsl #28
d001297c:	20c0f24b 	sbccs	pc, r0, fp, asr #4
d0012980:	fac0f7fe 	blx	0xcf050980
d0012984:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d0012988:	fb37f7fe 	blx	0xd0e1098a
d001298c:	203b492a 	eorscs	r4, fp, sl, lsr #18
d0012990:	f7fe4479 			; <UNDEFINED> instruction: 0xf7fe4479
d0012994:	e75bfa29 	ldrb	pc, [fp, -r9, lsr #20]	; <UNPREDICTABLE>
d0012998:	4070f8d9 	ldrsbtmi	pc, [r0], #-137	; 0xffffff77	; <UNPREDICTABLE>
d001299c:	d10a2c40 	tstle	sl, r0, asr #24
d00129a0:	bb7c6d3c 	bllt	0xd1f2de98
d00129a4:	657b4a25 	ldrbvs	r4, [fp, #-2597]!	; 0xfffff5db
d00129a8:	f8c7447a 			; <UNDEFINED> instruction: 0xf8c7447a
d00129ac:	f8c7b058 			; <UNDEFINED> instruction: 0xf8c7b058
d00129b0:	653aa05c 	ldrvs	sl, [sl, #-92]!	; 0xffffffa4
d00129b4:	f8cde7d8 			; <UNDEFINED> instruction: 0xf8cde7d8
d00129b8:	eb07b03c 	bl	0xd01feab0
d00129bc:	f88d1b44 			; <UNDEFINED> instruction: 0xf88d1b44
d00129c0:	f10da044 			; <UNDEFINED> instruction: 0xf10da044
d00129c4:	f50b0a2c 			; <UNDEFINED> instruction: 0xf50b0a2c
d00129c8:	920b3b8f 	andls	r3, fp, #146432	; 0x23c00
d00129cc:	1c65910c 	stfnep	f1, [r5], #-48	; 0xffffffd0
d00129d0:	0e70f10b 	expeqs	f7, #3.0
d00129d4:	f899930e 			; <UNDEFINED> instruction: 0xf899930e
d00129d8:	f8c9c078 			; <UNDEFINED> instruction: 0xf8c9c078
d00129dc:	f88b5070 			; <UNDEFINED> instruction: 0xf88b5070
d00129e0:	f88bc08c 			; <UNDEFINED> instruction: 0xf88bc08c
d00129e4:	e8ba608d 	ldm	sl!, {r0, r2, r3, r7, sp, lr}
d00129e8:	e8ae000f 	stmia	lr!, {r0, r1, r2, r3}
d00129ec:	f8d9000f 			; <UNDEFINED> instruction: 0xf8d9000f
d00129f0:	e89a3074 	ldm	sl, {r2, r4, r5, r6, ip, sp}
d00129f4:	429d0007 	addsmi	r0, sp, #7
d00129f8:	0007e88e 	andeq	lr, r7, lr, lsl #17
d00129fc:	f8c9d9b4 			; <UNDEFINED> instruction: 0xf8c9d9b4
d0012a00:	e7b15074 			; <UNDEFINED> instruction: 0xe7b15074
d0012a04:	e7af2400 	str	r2, [pc, r0, lsl #8]!
d0012a08:	e8bdb013 	pop	{r0, r1, r4, ip, sp, pc}
d0012a0c:	bf008ff0 	svclt	0x00008ff0
d0012a10:	00005778 	andeq	r5, r0, r8, ror r7
d0012a14:	00005776 	andeq	r5, r0, r6, ror r7
d0012a18:	ffffffb0 			; <UNDEFINED> instruction: 0xffffffb0
d0012a1c:	fffffeb4 			; <UNDEFINED> instruction: 0xfffffeb4
d0012a20:	fffffeb3 			; <UNDEFINED> instruction: 0xfffffeb3
d0012a24:	0000570c 	andeq	r5, r0, ip, lsl #14
d0012a28:	fffffe9c 			; <UNDEFINED> instruction: 0xfffffe9c
d0012a2c:	fffffea7 			; <UNDEFINED> instruction: 0xfffffea7
d0012a30:	fffffe72 			; <UNDEFINED> instruction: 0xfffffe72
d0012a34:	fffffe61 			; <UNDEFINED> instruction: 0xfffffe61
d0012a38:	fffffe69 			; <UNDEFINED> instruction: 0xfffffe69
d0012a3c:	fffffe31 			; <UNDEFINED> instruction: 0xfffffe31

Disassembly of section .text.statement.constprop.0:

d0012bc8 <.text.statement.constprop.0>:
d0012bc8:	47f3e92d 	ldrbmi	lr, [r3, sp, lsr #18]!
d0012bcc:	447c4ccb 	ldrbtmi	r4, [ip], #-3275	; 0xfffff335
d0012bd0:	bb0b6d23 	bllt	0xd02ee064
d0012bd4:	3593f504 	ldrcc	pc, [r3, #1284]	; 0x504
d0012bd8:	33016feb 	movwcc	r6, #8171	; 0x1feb
d0012bdc:	67eb2b20 	strbvs	r2, [fp, r0, lsr #22]!
d0012be0:	48c7d904 	stmiami	r7, {r2, r8, fp, ip, lr, pc}^
d0012be4:	f7fe4478 			; <UNDEFINED> instruction: 0xf7fe4478
d0012be8:	e00ef8ef 	and	pc, lr, pc, ror #17
d0012bec:	f7fe207b 			; <UNDEFINED> instruction: 0xf7fe207b
d0012bf0:	4607f8bf 			; <UNDEFINED> instruction: 0x4607f8bf
d0012bf4:	6fabb198 	svcvs	0x00abb198
d0012bf8:	33016f2c 	movwcc	r6, #7980	; 0x1f2c
d0012bfc:	f7ff67ab 			; <UNDEFINED> instruction: 0xf7ff67ab
d0012c00:	6fabfe1d 	svcvs	0x00abfe1d
d0012c04:	3b01672c 	blcc	0xd006c8bc
d0012c08:	4bbe67ab 	blmi	0xcefacabc
d0012c0c:	f503447b 			; <UNDEFINED> instruction: 0xf503447b
d0012c10:	6fda3393 	svcvs	0x00da3393
d0012c14:	67da3a01 	ldrbvs	r3, [sl, r1, lsl #20]
d0012c18:	e8bdb002 	pop	{r1, ip, sp, pc}
d0012c1c:	f44f87f0 	vst1.64	{d24}, [pc :256], r0
d0012c20:	f7fe7086 			; <UNDEFINED> instruction: 0xf7fe7086
d0012c24:	4606f8a5 	strmi	pc, [r6], -r5, lsr #17
d0012c28:	f7ffb328 			; <UNDEFINED> instruction: 0xf7ffb328
d0012c2c:	4638fd7d 			; <UNDEFINED> instruction: 0x4638fd7d
d0012c30:	faf6f7fe 	blx	0xcfdd0c30
d0012c34:	f7ff9001 			; <UNDEFINED> instruction: 0xf7ff9001
d0012c38:	f240ffc7 	vmax.f32	<illegal reg q15.5>, q8, <illegal reg q3.5>
d0012c3c:	f7fe100d 			; <UNDEFINED> instruction: 0xf7fe100d
d0012c40:	9901f897 	stmdbls	r1, {r0, r1, r2, r4, r7, fp, ip, sp, lr, pc}
d0012c44:	b1984603 	orrslt	r4, r8, r3, lsl #12
d0012c48:	fadaf7fe 	blx	0xcf6d0c48
d0012c4c:	463b4605 	ldrtmi	r4, [fp], -r5, lsl #12
d0012c50:	2e48f8d4 	mcrcs	8, 2, pc, cr8, cr4, {6}	; <UNPREDICTABLE>
d0012c54:	6d209901 			; <UNDEFINED> instruction: 0x6d209901
d0012c58:	fbcaf7fe 	blx	0xcf2d0c5a
d0012c5c:	ffb4f7ff 			; <UNDEFINED> instruction: 0xffb4f7ff
d0012c60:	f8d4463b 			; <UNDEFINED> instruction: 0xf8d4463b
d0012c64:	46292e48 	strtmi	r2, [r9], -r8, asr #28
d0012c68:	f7fe6d20 			; <UNDEFINED> instruction: 0xf7fe6d20
d0012c6c:	e7ccfbc1 	strb	pc, [ip, r1, asr #23]	; <UNPREDICTABLE>
d0012c70:	2e48f8d4 	mcrcs	8, 2, pc, cr8, cr4, {6}	; <UNPREDICTABLE>
d0012c74:	f44fe7f8 	vst1.64	{d30}, [pc :256], r8
d0012c78:	f7fe7087 			; <UNDEFINED> instruction: 0xf7fe7087
d0012c7c:	2800f879 	stmdacs	r0, {r0, r3, r4, r5, r6, fp, ip, sp, lr, pc}
d0012c80:	f8d5d04a 			; <UNDEFINED> instruction: 0xf8d5d04a
d0012c84:	2b203080 	blcs	0xd081ee8c
d0012c88:	489fd102 	ldmmi	pc, {r1, r8, ip, lr, pc}	; <UNPREDICTABLE>
d0012c8c:	e7aa4478 			; <UNDEFINED> instruction: 0xe7aa4478
d0012c90:	8084f8d5 	ldrdhi	pc, [r4], r5
d0012c94:	9e48f8d4 	mcrls	8, 2, pc, cr8, cr4, {6}	; <UNPREDICTABLE>
d0012c98:	fd46f7ff 	stc2l	7, cr15, [r6, #-1020]	; 0xfffffc04
d0012c9c:	f8df4630 			; <UNDEFINED> instruction: 0xf8df4630
d0012ca0:	f7fea26c 			; <UNDEFINED> instruction: 0xf7fea26c
d0012ca4:	f8d5fabd 			; <UNDEFINED> instruction: 0xf8d5fabd
d0012ca8:	46073080 	strmi	r3, [r7], -r0, lsl #1
d0012cac:	330144fa 	movwcc	r4, #5370	; 0x14fa
d0012cb0:	3080f8c5 	addcc	pc, r0, r5, asr #17
d0012cb4:	ff88f7ff 			; <UNDEFINED> instruction: 0xff88f7ff
d0012cb8:	3080f8d5 	ldrdcc	pc, [r0], r5
d0012cbc:	f8c53b01 			; <UNDEFINED> instruction: 0xf8c53b01
d0012cc0:	f7fe3080 			; <UNDEFINED> instruction: 0xf7fe3080
d0012cc4:	4633fa9d 			; <UNDEFINED> instruction: 0x4633fa9d
d0012cc8:	464a4601 	strbmi	r4, [sl], -r1, lsl #12
d0012ccc:	f7fe6d20 			; <UNDEFINED> instruction: 0xf7fe6d20
d0012cd0:	4633fb8f 	ldrtmi	pc, [r3], -pc, lsl #23	; <UNPREDICTABLE>
d0012cd4:	5613f508 	ldrpl	pc, [r3], -r8, lsl #10
d0012cd8:	46474639 			; <UNDEFINED> instruction: 0x46474639
d0012cdc:	2e48f8d4 	mcrcs	8, 2, pc, cr8, cr4, {6}	; <UNPREDICTABLE>
d0012ce0:	6d203611 	stcvs	6, cr3, [r0, #-68]!	; 0xffffffbc
d0012ce4:	fb84f7fe 	blx	0xce150ce6
d0012ce8:	06c6eb04 	strbeq	lr, [r6], r4, lsl #22
d0012cec:	2084f8d5 	ldrdcs	pc, [r4], r5
d0012cf0:	d3024297 	movwle	r4, #8855	; 0x2297
d0012cf4:	8084f8c5 	addhi	pc, r4, r5, asr #17
d0012cf8:	7933e787 	ldmdbvc	r3!, {r0, r1, r2, r7, r8, r9, sl, sp, lr, pc}
d0012cfc:	b14b6831 	cmplt	fp, r1, lsr r8
d0012d00:	2e48f8d4 	mcrcs	8, 2, pc, cr8, cr4, {6}	; <UNPREDICTABLE>
d0012d04:	f8da2300 			; <UNDEFINED> instruction: 0xf8da2300
d0012d08:	37010050 	smlsdcc	r1, r0, r0, r0
d0012d0c:	f7fe3608 			; <UNDEFINED> instruction: 0xf7fe3608
d0012d10:	e7ebfb6f 	strb	pc, [fp, pc, ror #22]!	; <UNPREDICTABLE>
d0012d14:	e7f5464a 	ldrb	r4, [r5, sl, asr #12]!
d0012d18:	f46f6ae7 	vld1.64	{d22-d23}, [pc :128], r7
d0012d1c:	187b7188 	ldmdane	fp!, {r3, r7, r8, ip, sp, lr}^
d0012d20:	d8302b01 	ldmdale	r0!, {r0, r8, r9, fp, sp}
d0012d24:	3080f8d5 	ldrdcc	pc, [r0], r5
d0012d28:	f240b94b 	vmla.i8	<illegal reg q13.5>, q0, <illegal reg q5.5>
d0012d2c:	429f1311 	addsmi	r1, pc, #1140850688	; 0x44000000
d0012d30:	4877d002 	ldmdami	r7!, {r1, ip, lr, pc}^
d0012d34:	e7564478 			; <UNDEFINED> instruction: 0xe7564478
d0012d38:	44784876 	ldrbtmi	r4, [r8], #-2166	; 0xfffff78a
d0012d3c:	f8d5e753 			; <UNDEFINED> instruction: 0xf8d5e753
d0012d40:	f5b33084 			; <UNDEFINED> instruction: 0xf5b33084
d0012d44:	d1027f00 	tstle	r2, r0, lsl #30
d0012d48:	44784873 	ldrbtmi	r4, [r8], #-2163	; 0xfffff78d
d0012d4c:	f7fde74b 			; <UNDEFINED> instruction: 0xf7fde74b
d0012d50:	4972fcbf 	ldmdbmi	r2!, {r0, r1, r2, r3, r4, r5, r7, sl, fp, ip, sp, lr, pc}^
d0012d54:	4479203b 	ldrbtmi	r2, [r9], #-59	; 0xffffffc5
d0012d58:	f846f7fe 			; <UNDEFINED> instruction: 0xf846f7fe
d0012d5c:	6084f8d5 	ldrdvs	pc, [r4], r5
d0012d60:	f8c51c73 			; <UNDEFINED> instruction: 0xf8c51c73
d0012d64:	f7fe3084 			; <UNDEFINED> instruction: 0xf7fe3084
d0012d68:	f506fa4b 			; <UNDEFINED> instruction: 0xf506fa4b
d0012d6c:	33115313 	tstcc	r1, #1275068416	; 0x4c000000
d0012d70:	0033f844 	eorseq	pc, r3, r4, asr #16
d0012d74:	04c3eb04 	strbeq	lr, [r3], #2820	; 0xb04
d0012d78:	1311f240 	tstne	r1, #64, 4	; <UNPREDICTABLE>
d0012d7c:	42531afa 	subsmi	r1, r3, #1024000	; 0xfa000
d0012d80:	71234153 			; <UNDEFINED> instruction: 0x71234153
d0012d84:	f240e741 	vabd.s8	q15, q0, <illegal reg q0.5>
d0012d88:	f7fd100f 			; <UNDEFINED> instruction: 0xf7fd100f
d0012d8c:	b398fff1 	orrslt	pc, r8, #964	; 0x3c4
d0012d90:	358ff504 	strcc	pc, [pc, #1284]	; 0xd001329c
d0012d94:	306cf895 	mlscc	ip, r5, r8, pc	; <UNPREDICTABLE>
d0012d98:	d01b2b01 	andsle	r2, fp, r1, lsl #22
d0012d9c:	46082101 	strmi	r2, [r8], -r1, lsl #2
d0012da0:	fa58f7ff 	blx	0xd1650da4
d0012da4:	306cf895 	mlscc	ip, r5, r8, pc	; <UNPREDICTABLE>
d0012da8:	d1032b02 	tstle	r3, r2, lsl #22
d0012dac:	20c0f24b 	sbccs	pc, r0, fp, asr #4
d0012db0:	f8a8f7fe 			; <UNDEFINED> instruction: 0xf8a8f7fe
d0012db4:	203b4d5a 	eorscs	r4, fp, sl, asr sp
d0012db8:	447d495a 	ldrbtmi	r4, [sp], #-2394	; 0xfffff6a6
d0012dbc:	f7fe4479 			; <UNDEFINED> instruction: 0xf7fe4479
d0012dc0:	f505f813 			; <UNDEFINED> instruction: 0xf505f813
d0012dc4:	6e9c338f 	cdpvs	3, 9, cr3, cr12, cr15, {4}
d0012dc8:	6f80f5b4 	svcvs	0x0080f5b4
d0012dcc:	4856d10a 	ldmdami	r6, {r1, r3, r8, ip, lr, pc}^
d0012dd0:	e7084478 	smlsdx	r8, r8, r4, r4
d0012dd4:	2b3b6ae3 	blcs	0xd0eed968
d0012dd8:	4854d0ec 	ldmdami	r4, {r2, r3, r5, r6, r7, ip, lr, pc}^
d0012ddc:	f7fd4478 			; <UNDEFINED> instruction: 0xf7fd4478
d0012de0:	e7e7fff3 			; <UNDEFINED> instruction: 0xe7e7fff3
d0012de4:	f5041c62 			; <UNDEFINED> instruction: 0xf5041c62
d0012de8:	341a4487 	ldrcc	r4, [sl], #-1159	; 0xfffffb79
d0012dec:	f7fe669a 			; <UNDEFINED> instruction: 0xf7fe669a
d0012df0:	f845fa07 			; <UNDEFINED> instruction: 0xf845fa07
d0012df4:	e7080024 	str	r0, [r8, -r4, lsr #32]
d0012df8:	f7fd203b 			; <UNDEFINED> instruction: 0xf7fd203b
d0012dfc:	2800ffb9 	stmdacs	r0, {r0, r3, r4, r5, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0012e00:	af03f47f 	svcge	0x0003f47f
d0012e04:	f2406ae2 	vpmax.s8	q11, q8, q9
d0012e08:	429a1301 	addsmi	r1, sl, #67108864	; 0x4000000
d0012e0c:	6ca3d167 	stfvsd	f5, [r3], #412	; 0x19c
d0012e10:	d1642b3d 	cmnle	r4, sp, lsr fp
d0012e14:	447c4c46 	ldrbtmi	r4, [ip], #-3142	; 0xfffff3ba
d0012e18:	9018f8d4 			; <UNDEFINED> instruction: 0x9018f8d4
d0012e1c:	464869e1 	strbmi	r6, [r8], -r1, ror #19
d0012e20:	91016a66 	tstls	r1, r6, ror #20
d0012e24:	f8946aa7 			; <UNDEFINED> instruction: 0xf8946aa7
d0012e28:	f7fe8030 			; <UNDEFINED> instruction: 0xf7fe8030
d0012e2c:	1e05f819 	mcrne	8, 0, pc, cr5, cr9, {0}	; <UNPREDICTABLE>
d0012e30:	da599901 	ble	0xd167923c
d0012e34:	f7fd4648 			; <UNDEFINED> instruction: 0xf7fd4648
d0012e38:	f1b0fa21 			; <UNDEFINED> instruction: 0xf1b0fa21
d0012e3c:	db130900 	blle	0xd04d5244
d0012e40:	fb032328 	blx	0xd00dbaea
d0012e44:	f6484409 			; <UNDEFINED> instruction: 0xf6484409
d0012e48:	5ce46378 	stclpl	3, cr6, [r4], #480	; 0x1e0
d0012e4c:	d11a2c07 	tstle	sl, r7, lsl #24
d0012e50:	447b4b38 	ldrbtmi	r4, [fp], #-2872	; 0xfffff4c8
d0012e54:	b9826d1a 	stmiblt	r2, {r1, r3, r4, r8, sl, fp, sp, lr}
d0012e58:	447a4a37 	ldrbtmi	r4, [sl], #-2615	; 0xfffff5c9
d0012e5c:	655e651a 	ldrbvs	r6, [lr, #-1306]	; 0xfffffae6
d0012e60:	f8c3659f 			; <UNDEFINED> instruction: 0xf8c3659f
d0012e64:	e008805c 	and	r8, r8, ip, asr r0
d0012e68:	b9336d23 	ldmdblt	r3!, {r0, r1, r5, r8, sl, fp, sp, lr}
d0012e6c:	65664b33 	strbvs	r4, [r6, #-2867]!	; 0xfffff4cd
d0012e70:	65a7447b 	strvs	r4, [r7, #1147]!	; 0x47b
d0012e74:	805cf8c4 	subshi	pc, ip, r4, asr #17
d0012e78:	49316523 	ldmdbmi	r1!, {r0, r1, r5, r8, sl, sp, lr}
d0012e7c:	4479203b 	ldrbtmi	r2, [r9], #-59	; 0xffffffc5
d0012e80:	ffb2f7fd 			; <UNDEFINED> instruction: 0xffb2f7fd
d0012e84:	f024e6c1 			; <UNDEFINED> instruction: 0xf024e6c1
d0012e88:	2b020304 	blcs	0xd0093aa0
d0012e8c:	2c04d001 	stccs	0, cr13, [r4], {1}
d0012e90:	4b2cd107 	blmi	0xd0b472b4
d0012e94:	6d1a447b 	cfldrsvs	mvf4, [sl, #-492]	; 0xfffffe14
d0012e98:	d1ee2a00 	mvnle	r2, r0, lsl #20
d0012e9c:	447a4a2a 	ldrbtmi	r4, [sl], #-2602	; 0xfffff5d6
d0012ea0:	f7fde7dc 			; <UNDEFINED> instruction: 0xf7fde7dc
d0012ea4:	f7fdfc15 			; <UNDEFINED> instruction: 0xf7fdfc15
d0012ea8:	2101fc13 	tstcs	r1, r3, lsl ip	; <UNPREDICTABLE>
d0012eac:	f7ff4608 			; <UNDEFINED> instruction: 0xf7ff4608
d0012eb0:	2c05f9d1 			; <UNDEFINED> instruction: 0x2c05f9d1
d0012eb4:	f24bd103 	vrhadd.s8	d29, d11, d3
d0012eb8:	f7fe20c0 			; <UNDEFINED> instruction: 0xf7fe20c0
d0012ebc:	2d00f823 	stccs	8, cr15, [r0, #-140]	; 0xffffff74
d0012ec0:	2100db04 	tstcs	r0, r4, lsl #22
d0012ec4:	f7fe4628 			; <UNDEFINED> instruction: 0xf7fe4628
d0012ec8:	e7d6f898 	bfi	pc, r8, #17, #6	; <UNPREDICTABLE>
d0012ecc:	20014649 	andcs	r4, r1, r9, asr #12
d0012ed0:	f8bef7fe 			; <UNDEFINED> instruction: 0xf8bef7fe
d0012ed4:	0008f246 	andeq	pc, r8, r6, asr #4
d0012ed8:	f814f7fe 			; <UNDEFINED> instruction: 0xf814f7fe
d0012edc:	2103e7cd 	smlabtcs	r3, sp, r7, lr
d0012ee0:	f7ff2001 			; <UNDEFINED> instruction: 0xf7ff2001
d0012ee4:	e7c8f9b7 			; <UNDEFINED> instruction: 0xe7c8f9b7
d0012ee8:	1445eb04 	strbne	lr, [r5], #-2820	; 0xfffff4fc
d0012eec:	39fff04f 	ldmibcc	pc!, {r0, r1, r2, r3, r6, ip, sp, lr, pc}^	; <UNPREDICTABLE>
d0012ef0:	348ff504 	strcc	pc, [pc], #1284	; 0xd0012ef8
d0012ef4:	408df894 	umullmi	pc, sp, r4, r8	; <UNPREDICTABLE>
d0012ef8:	bf00e7a8 	svclt	0x0000e7a8
d0012efc:	000053f2 	strdeq	r5, [r0], -r2
d0012f00:	ffffe8d3 			; <UNDEFINED> instruction: 0xffffe8d3
d0012f04:	000053b4 			; <UNDEFINED> instruction: 0x000053b4
d0012f08:	fffffddd 			; <UNDEFINED> instruction: 0xfffffddd
d0012f0c:	00005314 	andeq	r5, r0, r4, lsl r3
d0012f10:	fffffd1d 			; <UNDEFINED> instruction: 0xfffffd1d
d0012f14:	fffffd02 			; <UNDEFINED> instruction: 0xfffffd02
d0012f18:	fffffd35 			; <UNDEFINED> instruction: 0xfffffd35
d0012f1c:	fffffd4b 			; <UNDEFINED> instruction: 0xfffffd4b
d0012f20:	00005206 	andeq	r5, r0, r6, lsl #4
d0012f24:	fffffd36 			; <UNDEFINED> instruction: 0xfffffd36
d0012f28:	fffffd3c 			; <UNDEFINED> instruction: 0xfffffd3c
d0012f2c:	fffffcea 			; <UNDEFINED> instruction: 0xfffffcea
d0012f30:	000051aa 	andeq	r5, r0, sl, lsr #3
d0012f34:	0000516e 	andeq	r5, r0, lr, ror #2
d0012f38:	fffffcf8 			; <UNDEFINED> instruction: 0xfffffcf8
d0012f3c:	fffffcbd 			; <UNDEFINED> instruction: 0xfffffcbd
d0012f40:	fffffd26 			; <UNDEFINED> instruction: 0xfffffd26
d0012f44:	0000512c 	andeq	r5, r0, ip, lsr #2
d0012f48:	fffffcda 			; <UNDEFINED> instruction: 0xfffffcda

Disassembly of section .text.sidc_compile_sources.part.0:

d0013520 <.text.sidc_compile_sources.part.0>:
d0013520:	4ff0e92d 	svcmi	0x00f0e92d
d0013524:	46052400 	strmi	r2, [r5], -r0, lsl #8
d0013528:	ed2d3004 	stc	0, cr3, [sp, #-16]!
d001352c:	b0c58b02 	sbclt	r8, r5, r2, lsl #22
d0013530:	4623930e 	strtmi	r9, [r3], -lr, lsl #6
d0013534:	428c9209 	addmi	r9, ip, #-1879048192	; 0x90000000
d0013538:	4ea9d134 	mcrmi	1, 5, sp, cr9, cr4, {1}
d001353c:	4aa62100 	bmi	0xce99b944
d0013540:	4630447e 			; <UNDEFINED> instruction: 0x4630447e
d0013544:	f878f002 			; <UNDEFINED> instruction: 0xf878f002
d0013548:	49a748a6 	stmibmi	r7!, {r1, r2, r5, r7, fp, lr}
d001354c:	447822bc 	ldrbtmi	r2, [r8], #-700	; 0xfffffd44
d0013550:	30404479 	subcc	r4, r0, r9, ror r4
d0013554:	f87ef002 			; <UNDEFINED> instruction: 0xf87ef002
d0013558:	f8c623bc 			; <UNDEFINED> instruction: 0xf8c623bc
d001355c:	1d2b3e48 	stcne	14, cr3, [fp, #-288]!	; 0xfffffee0
d0013560:	b2e39306 	rsclt	r9, r3, #402653184	; 0x18000000
d0013564:	2300930d 	movwcs	r9, #781	; 0x30d
d0013568:	4ba09305 	blmi	0xce838184
d001356c:	930b447b 	movwls	r4, #46203	; 0xb47b
d0013570:	434ef503 	movtmi	pc, #58627	; 0xe503	; <UNPREDICTABLE>
d0013574:	93073360 	movwls	r3, #29536	; 0x7360
d0013578:	9a054c9d 	bls	0xd01667f4
d001357c:	447c990d 	ldrbtmi	r9, [ip], #-2317	; 0xfffff6f3
d0013580:	6d23428a 	sfmvs	f4, 4, [r3, #-552]!	; 0xfffffdd8
d0013584:	86fbf000 	ldrbthi	pc, [fp], r0	; <UNPREDICTABLE>
d0013588:	4c9ab343 	ldcmi	3, cr11, [sl], {67}	; 0x43
d001358c:	f8df2600 			; <UNDEFINED> instruction: 0xf8df2600
d0013590:	447c8268 	ldrbtmi	r8, [ip], #-616	; 0xfffffd98
d0013594:	f50444f8 			; <UNDEFINED> instruction: 0xf50444f8
d0013598:	f504454e 			; <UNDEFINED> instruction: 0xf504454e
d001359c:	35643787 	strbcc	r3, [r4, #-1927]!	; 0xfffff879
d00135a0:	bf33f000 	svclt	0x0033f000
d00135a4:	2034f855 	eorscs	pc, r4, r5, asr r8	; <UNPREDICTABLE>
d00135a8:	f850b12a 			; <UNDEFINED> instruction: 0xf850b12a
d00135ac:	f5c32034 			; <UNDEFINED> instruction: 0xf5c32034
d00135b0:	42b23600 	adcsmi	r3, r2, #0, 12
d00135b4:	2901d90f 	stmdbcs	r1, {r0, r1, r2, r3, r8, fp, ip, lr, pc}
d00135b8:	4b90d00a 	blmi	0xce4475e8
d00135bc:	9a50447b 	bls	0xd14247b0
d00135c0:	23016013 	movwcs	r6, #4115	; 0x1013
d00135c4:	605360d4 	ldrsbvs	r6, [r3], #-4
d00135c8:	25006093 	strcs	r6, [r0, #-147]	; 0xffffff6d
d00135cc:	b8cdf001 	stmialt	sp, {r0, ip, sp, lr, pc}^
d00135d0:	447b4b8b 	ldrbtmi	r4, [fp], #-2955	; 0xfffff475
d00135d4:	4413e7f3 	ldrmi	lr, [r3], #-2035	; 0xfffff80d
d00135d8:	e7ac3401 	str	r3, [ip, r1, lsl #8]!
d00135dc:	46a19a05 	strtmi	r9, [r1], r5, lsl #20
d00135e0:	72224d88 	eorvc	r4, r2, #136, 26	; 0x2200
d00135e4:	447d9a06 	ldrbtmi	r9, [sp], #-2566	; 0xfffff5fa
d00135e8:	2c04f852 	stccs	8, cr15, [r4], {82}	; 0x52
d00135ec:	9a066022 	bls	0xd01ab67c
d00135f0:	60e36812 	rscvs	r6, r3, r2, lsl r8
d00135f4:	60622301 	rsbvs	r2, r2, r1, lsl #6
d00135f8:	61236163 			; <UNDEFINED> instruction: 0x61236163
d00135fc:	f868f7fd 			; <UNDEFINED> instruction: 0xf868f7fd
d0013600:	f866f7fd 			; <UNDEFINED> instruction: 0xf866f7fd
d0013604:	0394f605 	orrseq	pc, r4, #5242880	; 0x500000
d0013608:	3a10ee08 	bcc	0xd044ee30
d001360c:	202cf8d9 	ldrdcs	pc, [ip], -r9	; <UNPREDICTABLE>
d0013610:	3050f8d9 	ldrsbcc	pc, [r0], #-137	; 0xffffff77	; <UNPREDICTABLE>
d0013614:	7f83f5b2 	svcvc	0x0083f5b2
d0013618:	b13bd113 	teqlt	fp, r3, lsl r1
d001361c:	33019b05 	movwcc	r9, #6917	; 0x1b05
d0013620:	9305b2db 	movwls	fp, #21211	; 0x52db
d0013624:	33089b06 	movwcc	r9, #35590	; 0x8b06
d0013628:	e7a59306 	str	r9, [r5, r6, lsl #6]!
d001362c:	606cf8d9 	ldrdvs	pc, [ip], #-137	; 0xffffff77	; <UNPREDICTABLE>
d0013630:	f0402e00 			; <UNDEFINED> instruction: 0xf0402e00
d0013634:	9b09808b 	blls	0xd0273868
d0013638:	4873b93b 	ldmdami	r3!, {r0, r1, r3, r4, r5, r8, fp, ip, sp, pc}^
d001363c:	f7fd4478 			; <UNDEFINED> instruction: 0xf7fd4478
d0013640:	4b72fbc3 	blmi	0xd1cd2554
d0013644:	930a447b 	movwls	r4, #42107	; 0xa47b
d0013648:	f8dfe18f 			; <UNDEFINED> instruction: 0xf8dfe18f
d001364c:	f64081c4 			; <UNDEFINED> instruction: 0xf64081c4
d0013650:	9b0951ec 	blls	0xd0267e08
d0013654:	464044f8 			; <UNDEFINED> instruction: 0x464044f8
d0013658:	28004798 	stmdacs	r0, {r3, r4, r7, r8, r9, sl, lr}
d001365c:	f1a0d0ed 			; <UNDEFINED> instruction: 0xf1a0d0ed
d0013660:	f6400218 			; <UNDEFINED> instruction: 0xf6400218
d0013664:	429a53d4 	addsmi	r5, sl, #212, 6	; 0x50000003
d0013668:	8084f200 	addhi	pc, r4, r0, lsl #4
d001366c:	22041f04 	andcs	r1, r4, #4, 30
d0013670:	eb08a81a 	bl	0xd023d6e0
d0013674:	f0010104 			; <UNDEFINED> instruction: 0xf0010104
d0013678:	4621ffed 	strtmi	pc, [r1], -sp, ror #31
d001367c:	f7fc4640 			; <UNDEFINED> instruction: 0xf7fc4640
d0013680:	9b1afd7f 	blls	0xd06d2c84
d0013684:	d1754298 			; <UNDEFINED> instruction: 0xd1754298
d0013688:	4641af21 	strbmi	sl, [r1], -r1, lsr #30
d001368c:	46382214 			; <UNDEFINED> instruction: 0x46382214
d0013690:	ffe0f001 			; <UNDEFINED> instruction: 0xffe0f001
d0013694:	2208495f 	andcs	r4, r8, #1556480	; 0x17c000
d0013698:	44794638 	ldrbtmi	r4, [r9], #-1592	; 0xfffff9c8
d001369c:	ffeaf001 			; <UNDEFINED> instruction: 0xffeaf001
d00136a0:	28004680 	stmdacs	r0, {r7, r9, sl, lr}
d00136a4:	2701d155 	smlsdcs	r1, r5, r1, sp
d00136a8:	9a234b4c 	bls	0xd08e63e0
d00136ac:	d161429a 			; <UNDEFINED> instruction: 0xd161429a
d00136b0:	1e4b9924 	vmlane.f16	s19, s22, s9	; <UNPREDICTABLE>
d00136b4:	d85d2b27 	ldmdale	sp, {r0, r1, r2, r5, r8, r9, fp, sp}^
d00136b8:	2a289a25 	bcs	0xd0a39f54
d00136bc:	f1b8d85a 			; <UNDEFINED> instruction: 0xf1b8d85a
d00136c0:	bf0c0f00 	svclt	0x000c0f00
d00136c4:	2308230c 	movwcs	r2, #33548	; 0x830c
d00136c8:	93022f00 	movwls	r2, #12032	; 0x2f00
d00136cc:	0328f103 	msreq	CPSR_f, #-1073741824	; 0xc0000000
d00136d0:	f101fb03 			; <UNDEFINED> instruction: 0xf101fb03
d00136d4:	f04f9301 			; <UNDEFINED> instruction: 0xf04f9301
d00136d8:	fb030324 	blx	0xd00d4372
d00136dc:	bf14f202 	svclt	0x0014f202
d00136e0:	23002314 	movwcs	r2, #788	; 0x314
d00136e4:	0a14f102 	beq	0xd054faf4
d00136e8:	4453448a 	ldrbmi	r4, [r3], #-1162	; 0xfffffb76
d00136ec:	d141429c 			; <UNDEFINED> instruction: 0xd141429c
d00136f0:	b124f8df 	ldrdlt	pc, [r4, -pc]!	; <UNPREDICTABLE>
d00136f4:	ee183114 	mrc	1, 0, r3, cr8, cr4, {0}
d00136f8:	44fb0a10 	ldrbtmi	r0, [fp], #2576	; 0xa10
d00136fc:	f0014459 			; <UNDEFINED> instruction: 0xf0014459
d0013700:	2f00ffa9 	svccs	0x0000ffa9
d0013704:	f1b8d139 			; <UNDEFINED> instruction: 0xf1b8d139
d0013708:	d15e0f00 	cmple	lr, r0, lsl #30
d001370c:	0a0ef04f 	beq	0xd03cf850
d0013710:	f04f4c42 			; <UNDEFINED> instruction: 0xf04f4c42
d0013714:	49420800 	stmdbmi	r2, {fp}^
d0013718:	7bfcf640 	blvc	0xcff51020
d001371c:	4479447c 	ldrbtmi	r4, [r9], #-1148	; 0xfffffb84
d0013720:	3114349c 			; <UNDEFINED> instruction: 0x3114349c
d0013724:	45909a24 	ldrmi	r9, [r0, #2596]	; 0xa24
d0013728:	8086f0c0 	addhi	pc, r6, r0, asr #1
d001372c:	9f254c3d 	svcls	0x00254c3d
d0013730:	f604447c 			; <UNDEFINED> instruction: 0xf604447c
d0013734:	42be0494 	adcsmi	r0, lr, #148, 8	; 0x94000000
d0013738:	80c8f040 	sbchi	pc, r8, r0, asr #32
d001373c:	ae214c3a 	mcrge	12, 1, r4, cr1, cr10, {1}
d0013740:	ce0f447c 	mcrgt	4, 0, r4, cr15, cr12, {3}
d0013744:	c40f3460 	strgt	r3, [pc], #-1120	; 0xd001374c
d0013748:	60236833 	eorvs	r6, r3, r3, lsr r8
d001374c:	ffc0f7fc 			; <UNDEFINED> instruction: 0xffc0f7fc
d0013750:	4936e75c 	ldmdbmi	r6!, {r2, r3, r4, r6, r8, r9, sl, sp, lr, pc}
d0013754:	46382208 	ldrtmi	r2, [r8], -r8, lsl #4
d0013758:	f0014479 			; <UNDEFINED> instruction: 0xf0014479
d001375c:	2800ff8b 	stmdacs	r0, {r0, r1, r3, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0013760:	4933d0a1 	ldmdbmi	r3!, {r0, r5, r7, ip, lr, pc}
d0013764:	22084638 	andcs	r4, r8, #56, 12	; 0x3800000
d0013768:	f0014479 			; <UNDEFINED> instruction: 0xf0014479
d001376c:	4607ff83 	strmi	pc, [r7], -r3, lsl #31
d0013770:	d0992800 	addsle	r2, r9, r0, lsl #16
d0013774:	4478482f 	ldrbtmi	r4, [r8], #-2095	; 0xfffff7d1
d0013778:	f605e761 			; <UNDEFINED> instruction: 0xf605e761
d001377c:	22146434 	andscs	r6, r4, #52, 8	; 0x34000000
d0013780:	010aeb0b 	tsteq	sl, fp, lsl #22
d0013784:	f0014620 			; <UNDEFINED> instruction: 0xf0014620
d0013788:	f8b5ff65 			; <UNDEFINED> instruction: 0xf8b5ff65
d001378c:	f6401e44 			; <UNDEFINED> instruction: 0xf6401e44
d0013790:	1f0a73fc 	svcne	0x000a73fc
d0013794:	d8ed429a 	stmiale	sp!, {r1, r3, r4, r7, r9, lr}^
d0013798:	0303f001 	movweq	pc, #12289	; 0x3001	; <UNPREDICTABLE>
d001379c:	2e46f8b5 	mcrcs	8, 2, pc, cr6, cr5, {5}	; <UNPREDICTABLE>
d00137a0:	d1e74313 	mvnle	r4, r3, lsl r3
d00137a4:	f8342204 			; <UNDEFINED> instruction: 0xf8342204
d00137a8:	f1020b02 			; <UNDEFINED> instruction: 0xf1020b02
d00137ac:	ea1c3cff 	b	0xd0722bb0
d00137b0:	d1df0f00 	bicsle	r0, pc, r0, lsl #30
d00137b4:	42901a8a 	addsmi	r1, r0, #565248	; 0x8a000
d00137b8:	3301d8dc 	movwcc	sp, #6364	; 0x18dc
d00137bc:	d0a22b08 	adcle	r2, r2, r8, lsl #22
d00137c0:	bf0c2b01 	svclt	0x000c2b01
d00137c4:	22042201 	andcs	r2, r4, #268435456	; 0x10000000
d00137c8:	2f00e7ed 	svccs	0x0000e7ed
d00137cc:	f04fbf14 			; <UNDEFINED> instruction: 0xf04fbf14
d00137d0:	f04f0a0d 			; <UNDEFINED> instruction: 0xf04f0a0d
d00137d4:	e79b0a0a 	ldr	r0, [fp, sl, lsl #20]
d00137d8:	00013688 	andeq	r3, r1, r8, lsl #13
d00137dc:	2001f000 	andcs	pc, r1, r0
d00137e0:	00004a80 	andeq	r4, r0, r0, lsl #21
d00137e4:	000180fa 	strdeq	r8, [r1], -sl
d00137e8:	0000133d 	andeq	r1, r0, sp, lsr r3
d00137ec:	00004a54 	andeq	r4, r0, r4, asr sl
d00137f0:	00004a42 	andeq	r4, r0, r2, asr #20
d00137f4:	00004a2e 	andeq	r4, r0, lr, lsr #20
d00137f8:	ffffff1b 			; <UNDEFINED> instruction: 0xffffff1b
d00137fc:	fffff9a3 			; <UNDEFINED> instruction: 0xfffff9a3
d0013800:	fffff976 			; <UNDEFINED> instruction: 0xfffff976
d0013804:	000049da 	ldrdeq	r4, [r0], -sl
d0013808:	fffff943 			; <UNDEFINED> instruction: 0xfffff943
d001380c:	0000497c 	andeq	r4, r0, ip, ror r9
d0013810:	00003b80 	andeq	r3, r0, r0, lsl #23
d0013814:	fffff90e 			; <UNDEFINED> instruction: 0xfffff90e
d0013818:	00003ada 	ldrdeq	r3, [r0], -sl
d001381c:	000048a4 	andeq	r4, r0, r4, lsr #17
d0013820:	00003ab6 			; <UNDEFINED> instruction: 0x00003ab6
d0013824:	00004890 	muleq	r0, r0, r8
d0013828:	00004880 	andeq	r4, r0, r0, lsl #17
d001382c:	fffff858 			; <UNDEFINED> instruction: 0xfffff858
d0013830:	fffff850 			; <UNDEFINED> instruction: 0xfffff850
d0013834:	fffff84a 			; <UNDEFINED> instruction: 0xfffff84a
d0013838:	0728f1a4 	streq	pc, [r8, -r4, lsr #3]!
d001383c:	91039a01 	tstls	r3, r1, lsl #20
d0013840:	f0014638 			; <UNDEFINED> instruction: 0xf0014638
d0013844:	4638ff07 	ldrtmi	pc, [r8], -r7, lsl #30	; <UNPREDICTABLE>
d0013848:	fcccf7fc 	stc2l	7, cr15, [ip], {252}	; 0xfc
d001384c:	d0912800 	addsle	r2, r1, r0, lsl #16
d0013850:	0c02f814 	stceq	8, cr15, [r2], {20}
d0013854:	42839b02 	addmi	r9, r3, #2048	; 0x800
d0013858:	f814d38c 			; <UNDEFINED> instruction: 0xf814d38c
d001385c:	f6402c01 			; <UNDEFINED> instruction: 0xf6402c01
d0013860:	99030381 	stmdbls	r3, {r0, r7, r8, r9}
d0013864:	2f031f57 	svccs	0x00031f57
d0013868:	2a0bd901 	bcs	0xd0309c74
d001386c:	f1a4d182 			; <UNDEFINED> instruction: 0xf1a4d182
d0013870:	27000c08 	strcs	r0, [r0, -r8, lsl #24]
d0013874:	2b02f83c 	blcs	0xd00d196c
d0013878:	f63f455a 			; <UNDEFINED> instruction: 0xf63f455a
d001387c:	f012af7b 			; <UNDEFINED> instruction: 0xf012af7b
d0013880:	f47f0203 			; <UNDEFINED> instruction: 0xf47f0203
d0013884:	3701af77 	smlsdxcc	r1, r7, pc, sl	; <UNPREDICTABLE>
d0013888:	d1f32f03 	mvnsle	r2, r3, lsl #30
d001388c:	429046a4 	addsmi	r4, r0, #164, 12	; 0xa400000
d0013890:	280bd807 	stmdacs	fp, {r0, r1, r2, fp, ip, lr, pc}
d0013894:	9a01d914 	bls	0xd0089cec
d0013898:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d001389c:	44113434 	ldrmi	r3, [r1], #-1076	; 0xfffffbcc
d00138a0:	f81ce740 			; <UNDEFINED> instruction: 0xf81ce740
d00138a4:	2f0b7b01 	svccs	0x000b7b01
d00138a8:	fa23d805 	blx	0xd09098c4
d00138ac:	f01efe07 			; <UNDEFINED> instruction: 0xf01efe07
d00138b0:	f47f0f01 			; <UNDEFINED> instruction: 0xf47f0f01
d00138b4:	4557af5f 	ldrbmi	sl, [r7, #-3935]	; 0xfffff0a1
d00138b8:	af5cf63f 	svcge	0x005cf63f
d00138bc:	e7e63201 	strb	r3, [r6, r1, lsl #4]!
d00138c0:	2a005c22 	bcs	0xd002a950
d00138c4:	af56f47f 	svcge	0x0056f47f
d00138c8:	e7e23001 	strb	r3, [r2, r1]!
d00138cc:	34244620 	strtcc	r4, [r4], #-1568	; 0xfffff9e0
d00138d0:	fc88f7fc 	stc2	7, cr15, [r8], {252}	; 0xfc
d00138d4:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d00138d8:	3601af4d 	strcc	sl, [r1], -sp, asr #30
d00138dc:	f8dfe72b 			; <UNDEFINED> instruction: 0xf8dfe72b
d00138e0:	44780c2c 	ldrbtmi	r0, [r8], #-3116	; 0xfffff3d4
d00138e4:	fa56f7fd 	blx	0xd15d18e0
d00138e8:	f8dfb9a8 			; <UNDEFINED> instruction: 0xf8dfb9a8
d00138ec:	44780c24 	ldrbtmi	r0, [r8], #-3108	; 0xfffff3dc
d00138f0:	fa50f7fd 	blx	0xd14518ec
d00138f4:	f8dfb930 			; <UNDEFINED> instruction: 0xf8dfb930
d00138f8:	44780c1c 	ldrbtmi	r0, [r8], #-3100	; 0xfffff3e4
d00138fc:	fa4af7fd 	blx	0xd12d18f8
d0013900:	d0592800 	subsle	r2, r9, r0, lsl #16
d0013904:	e0612705 	rsb	r2, r1, r5, lsl #14
d0013908:	f04f2700 			; <UNDEFINED> instruction: 0xf04f2700
d001390c:	e05f0b01 	subs	r0, pc, r1, lsl #22
d0013910:	0b02f04f 	bleq	0xd00cfa54
d0013914:	2701e05c 	smlsdcs	r1, ip, r0, lr
d0013918:	f109e05a 			; <UNDEFINED> instruction: 0xf109e05a
d001391c:	46210274 			; <UNDEFINED> instruction: 0x46210274
d0013920:	f1094630 			; <UNDEFINED> instruction: 0xf1094630
d0013924:	f7fc0934 			; <UNDEFINED> instruction: 0xf7fc0934
d0013928:	b910fc75 	ldmdblt	r0, {r0, r2, r4, r5, r6, sl, fp, ip, sp, lr, pc}
d001392c:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d0013930:	f8dfe0b1 			; <UNDEFINED> instruction: 0xf8dfe0b1
d0013934:	447b3be4 	ldrbtmi	r3, [fp], #-3044	; 0xfffff41c
d0013938:	b9b26d1a 	ldmiblt	r2!, {r1, r3, r4, r8, sl, fp, sp, lr}
d001393c:	2bdcf8df 	blcs	0xcf751cc0
d0013940:	651a447a 	ldrvs	r4, [sl, #-1146]	; 0xfffffb86
d0013944:	f8c39a02 			; <UNDEFINED> instruction: 0xf8c39a02
d0013948:	655aa05c 	ldrbvs	sl, [sl, #-92]	; 0xffffffa4
d001394c:	659a9a03 	ldrvs	r9, [sl, #2563]	; 0xa03
d0013950:	6d2be00b 	stcvs	0, cr14, [fp, #-44]!	; 0xffffffd4
d0013954:	f8dfb94b 			; <UNDEFINED> instruction: 0xf8dfb94b
d0013958:	447b3bc8 	ldrbtmi	r3, [fp], #-3016	; 0xfffff438
d001395c:	9b02652b 	blls	0xd00ace10
d0013960:	a05cf8c5 	subsge	pc, ip, r5, asr #17
d0013964:	9b03656b 	blls	0xd00ecf18
d0013968:	9b0a65ab 	blls	0xd02ad01c
d001396c:	2b006d1b 	blcs	0xd002ede0
d0013970:	ae54f47f 	mrcge	4, 2, APSR_nzcv, cr4, cr15, {3}
d0013974:	6adb9b0a 	bvs	0xcf6fa5a4
d0013978:	7f80f5b3 	svcvc	0x0080f5b3
d001397c:	ae4ef43f 	mcrge	4, 2, pc, cr14, cr15, {1}	; <UNPREDICTABLE>
d0013980:	7088f44f 	addvc	pc, r8, pc, asr #8
d0013984:	f9f4f7fd 			; <UNDEFINED> instruction: 0xf9f4f7fd
d0013988:	b9189004 	ldmdblt	r8, {r2, ip, pc}
d001398c:	1009f240 	andne	pc, r9, r0, asr #4
d0013990:	f9eef7fd 			; <UNDEFINED> instruction: 0xf9eef7fd
d0013994:	7084f44f 	addvc	pc, r4, pc, asr #8
d0013998:	f9eaf7fd 			; <UNDEFINED> instruction: 0xf9eaf7fd
d001399c:	28004607 	stmdacs	r0, {r0, r1, r2, r9, sl, lr}
d00139a0:	f8dfd1b2 			; <UNDEFINED> instruction: 0xf8dfd1b2
d00139a4:	44780b80 	ldrbtmi	r0, [r8], #-2944	; 0xfffff480
d00139a8:	f9f4f7fd 			; <UNDEFINED> instruction: 0xf9f4f7fd
d00139ac:	28004683 	stmdacs	r0, {r0, r1, r7, r9, sl, lr}
d00139b0:	9b04d1ae 	blls	0xd0148070
d00139b4:	d1922b00 	orrsle	r2, r2, r0, lsl #22
d00139b8:	1b6cf8df 	blne	0xd1b51d3c
d00139bc:	1007f240 	andne	pc, r7, r0, asr #4
d00139c0:	f7fd4479 			; <UNDEFINED> instruction: 0xf7fd4479
d00139c4:	2800fa11 	stmdacs	r0, {r0, r4, r9, fp, ip, sp, lr, pc}
d00139c8:	2700d0cf 	strcs	sp, [r0, -pc, asr #1]
d00139cc:	0b00f04f 	bleq	0xd004fb10
d00139d0:	5b58f8df 	blpl	0xd1651d54
d00139d4:	447dac13 	ldrbtmi	sl, [sp], #-3091	; 0xfffff3ed
d00139d8:	0618f105 	ldreq	pc, [r8], -r5, lsl #2
d00139dc:	a030f895 	mlasge	r0, r5, r8, pc	; <UNPREDICTABLE>
d00139e0:	c40fce0f 	strgt	ip, [pc], #-3599	; 0xd00139e8
d00139e4:	0007e896 	muleq	r7, r6, r8
d00139e8:	69ae6a6b 	stmibvs	lr!, {r0, r1, r3, r5, r6, r9, fp, sp, lr}
d00139ec:	6aab9302 	bvs	0xceaf85fc
d00139f0:	0007e884 	andeq	lr, r7, r4, lsl #17
d00139f4:	1b38f8df 	blne	0xd0e51d78
d00139f8:	1001f240 	andne	pc, r1, r0, asr #4
d00139fc:	447969ec 	ldrbtmi	r6, [r9], #-2540	; 0xfffff614
d0013a00:	f7fd9303 			; <UNDEFINED> instruction: 0xf7fd9303
d0013a04:	2800f9f1 	stmdacs	r0, {r0, r4, r5, r6, r7, r8, fp, ip, sp, lr, pc}
d0013a08:	9b04d0af 	blls	0xd0147ccc
d0013a0c:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d0013a10:	f1bb8145 			; <UNDEFINED> instruction: 0xf1bb8145
d0013a14:	f0400f00 			; <UNDEFINED> instruction: 0xf0400f00
d0013a18:	b91f8141 	ldmdblt	pc, {r0, r6, r8, pc}	; <UNPREDICTABLE>
d0013a1c:	2b286aeb 	blcs	0xd0a2e5d0
d0013a20:	813cf000 	teqhi	ip, r0	; <UNPREDICTABLE>
d0013a24:	f10d9b02 			; <UNDEFINED> instruction: 0xf10d9b02
d0013a28:	f88d0c4c 			; <UNDEFINED> instruction: 0xf88d0c4c
d0013a2c:	ad21a064 	stcge	0, cr10, [r1, #-400]!	; 0xfffffe70
d0013a30:	9b039316 	blls	0xd00f8690
d0013a34:	93179613 	tstls	r7, #19922944	; 0x1300000
d0013a38:	e8bc9414 	ldm	ip!, {r2, r4, sl, ip, pc}
d0013a3c:	c50f000f 	strgt	r0, [pc, #-15]	; 0xd0013a35
d0013a40:	0007e89c 	muleq	r7, ip, r8
d0013a44:	0007e885 	andeq	lr, r7, r5, lsl #17
d0013a48:	46304621 	ldrtmi	r4, [r0], -r1, lsr #12
d0013a4c:	f9daf7fd 			; <UNDEFINED> instruction: 0xf9daf7fd
d0013a50:	46054621 	strmi	r4, [r5], -r1, lsr #12
d0013a54:	f7fc4630 			; <UNDEFINED> instruction: 0xf7fc4630
d0013a58:	2800fc11 	stmdacs	r0, {r0, r4, sl, fp, ip, sp, lr, pc}
d0013a5c:	af69f6bf 	svcge	0x0069f6bf
d0013a60:	db0c2d00 	blle	0xd031ee68
d0013a64:	3accf8df 	bcc	0xcf351de8
d0013a68:	f24a202c 	vhadd.s8	d18, d10, d28
d0013a6c:	447b2285 	ldrbtmi	r2, [fp], #-645	; 0xfffffd7b
d0013a70:	3505fb00 	strcc	pc, [r5, #-2816]	; 0xfffff500
d0013a74:	5caa7a1b 	vstmiapl	sl!, {s14-s40}
d0013a78:	f43f429a 			; <UNDEFINED> instruction: 0xf43f429a
d0013a7c:	4621af5a 	qsaxmi	sl, r1, sl
d0013a80:	f7fc4630 			; <UNDEFINED> instruction: 0xf7fc4630
d0013a84:	2800fbdd 	stmdacs	r0, {r0, r2, r3, r4, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d0013a88:	af53f47f 	svcge	0x0053f47f
d0013a8c:	9aa8f8df 	bls	0xcea51e10
d0013a90:	44f94680 	ldrbtmi	r4, [r9], #1664	; 0x680
d0013a94:	6eeb464d 	cdpvs	6, 14, cr4, cr11, cr13, {2}
d0013a98:	f4ff4598 			; <UNDEFINED> instruction: 0xf4ff4598
d0013a9c:	f505af3e 			; <UNDEFINED> instruction: 0xf505af3e
d0013aa0:	f8d84822 			; <UNDEFINED> instruction: 0xf8d84822
d0013aa4:	f1083054 			; <UNDEFINED> instruction: 0xf1083054
d0013aa8:	2b800854 	blcs	0xce015c00
d0013aac:	af51f43f 	svcge	0x0051f43f
d0013ab0:	f7fd205b 			; <UNDEFINED> instruction: 0xf7fd205b
d0013ab4:	bb40f95d 	bllt	0xd1052030
d0013ab8:	4607b2fd 			; <UNDEFINED> instruction: 0x4607b2fd
d0013abc:	f7fd203d 			; <UNDEFINED> instruction: 0xf7fd203d
d0013ac0:	2800f957 	stmdacs	r0, {r0, r1, r2, r4, r6, r8, fp, ip, sp, lr, pc}
d0013ac4:	80def000 	sbcshi	pc, lr, r0
d0013ac8:	f0402d07 			; <UNDEFINED> instruction: 0xf0402d07
d0013acc:	f8df80bd 			; <UNDEFINED> instruction: 0xf8df80bd
d0013ad0:	207b1a6c 	rsbscs	r1, fp, ip, ror #20
d0013ad4:	91014479 	tstls	r1, r9, ror r4
d0013ad8:	f986f7fd 			; <UNDEFINED> instruction: 0xf986f7fd
d0013adc:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0013ae0:	f8dfaf44 			; <UNDEFINED> instruction: 0xf8dfaf44
d0013ae4:	447a2a5c 	ldrbtmi	r2, [sl], #-2652	; 0xfffff5a4
d0013ae8:	f5a36ad3 			; <UNDEFINED> instruction: 0xf5a36ad3
d0013aec:	2b017381 	blcs	0xd00708f8
d0013af0:	f8d2d805 			; <UNDEFINED> instruction: 0xf8d2d805
d0013af4:	9901b020 	stmdbls	r1, {r5, ip, sp, pc}
d0013af8:	0f00f1bb 	svceq	0x0000f1bb
d0013afc:	f8dfd048 			; <UNDEFINED> instruction: 0xf8dfd048
d0013b00:	44780a44 	ldrbtmi	r0, [r8], #-2628	; 0xfffff5bc
d0013b04:	f960f7fd 			; <UNDEFINED> instruction: 0xf960f7fd
d0013b08:	2f05e72f 	svccs	0x0005e72f
d0013b0c:	6d2bd007 	stcvs	0, cr13, [fp, #-28]!	; 0xffffffe4
d0013b10:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0013b14:	f8dfaf2a 			; <UNDEFINED> instruction: 0xf8dfaf2a
d0013b18:	447b3a30 	ldrbtmi	r3, [fp], #-2608	; 0xfffff5d0
d0013b1c:	6aebe71e 	bvs	0xcfb0d79c
d0013b20:	f5a36a68 			; <UNDEFINED> instruction: 0xf5a36a68
d0013b24:	6aa97381 	bvs	0xcea70930
d0013b28:	2030f895 	mlascs	r0, r5, r8, pc	; <UNPREDICTABLE>
d0013b2c:	d8012b01 	stmdale	r1, {r0, r8, r9, fp, sp}
d0013b30:	b9776a2f 	ldmdblt	r7!, {r0, r1, r2, r3, r5, r9, fp, sp, lr}^
d0013b34:	4a14f8df 	bmi	0xd0551eb8
d0013b38:	6d23447c 	cfstrsvs	mvf4, [r3, #-496]!	; 0xfffffe10
d0013b3c:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0013b40:	f8dfaf14 			; <UNDEFINED> instruction: 0xf8dfaf14
d0013b44:	65603a0c 	strbvs	r3, [r0, #-2572]!	; 0xfffff5f4
d0013b48:	65a1447b 	strvs	r4, [r1, #1147]!	; 0x47b
d0013b4c:	652365e2 	strvs	r6, [r3, #-1506]!	; 0xfffffa1e
d0013b50:	f8d8e70b 			; <UNDEFINED> instruction: 0xf8d8e70b
d0013b54:	f5c33008 			; <UNDEFINED> instruction: 0xf5c33008
d0013b58:	429f2380 	addsmi	r2, pc, #128, 6
d0013b5c:	6d2bd90b 			; <UNDEFINED> instruction: 0x6d2bd90b
d0013b60:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0013b64:	f8dfaf02 			; <UNDEFINED> instruction: 0xf8dfaf02
d0013b68:	656839ec 	strbvs	r3, [r8, #-2540]!	; 0xfffff614
d0013b6c:	65a9447b 	strvs	r4, [r9, #1147]!	; 0x47b
d0013b70:	652b65ea 	strvs	r6, [fp, #-1514]!	; 0xfffffa16
d0013b74:	f7fce6f9 			; <UNDEFINED> instruction: 0xf7fce6f9
d0013b78:	f8dffdab 			; <UNDEFINED> instruction: 0xf8dffdab
d0013b7c:	205d19dc 	ldrsbcs	r1, [sp], #-156	; 0xffffff64
d0013b80:	f7fd4479 			; <UNDEFINED> instruction: 0xf7fd4479
d0013b84:	2800f931 	stmdacs	r0, {r0, r4, r5, r8, fp, ip, sp, lr, pc}
d0013b88:	aeeff43f 	mcrge	4, 7, pc, cr15, cr15, {1}	; <UNPREDICTABLE>
d0013b8c:	e7952507 	ldr	r2, [r5, r7, lsl #10]
d0013b90:	f7fc9101 			; <UNDEFINED> instruction: 0xf7fc9101
d0013b94:	202cfd9d 	mlacs	ip, sp, sp, pc	; <UNPREDICTABLE>
d0013b98:	f8eaf7fd 			; <UNDEFINED> instruction: 0xf8eaf7fd
d0013b9c:	207d9901 	rsbscs	r9, sp, r1, lsl #18
d0013ba0:	f922f7fd 			; <UNDEFINED> instruction: 0xf922f7fd
d0013ba4:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0013ba8:	f8dfaee0 			; <UNDEFINED> instruction: 0xf8dfaee0
d0013bac:	203b19b0 	ldrhtcs	r1, [fp], -r0
d0013bb0:	f7fd4479 			; <UNDEFINED> instruction: 0xf7fd4479
d0013bb4:	2800f919 	stmdacs	r0, {r0, r3, r4, r8, fp, ip, sp, lr, pc}
d0013bb8:	aed7f43f 	mrcge	4, 6, APSR_nzcv, cr7, cr15, {1}
d0013bbc:	39a0f8df 	stmibcc	r0!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d0013bc0:	f04f2d07 			; <UNDEFINED> instruction: 0xf04f2d07
d0013bc4:	96210e28 	strtls	r0, [r1], -r8, lsr #28
d0013bc8:	9422447b 	strtls	r4, [r2], #-1147	; 0xfffffb85
d0013bcc:	f88dae21 			; <UNDEFINED> instruction: 0xf88dae21
d0013bd0:	f503a09c 			; <UNDEFINED> instruction: 0xf503a09c
d0013bd4:	f5034222 			; <UNDEFINED> instruction: 0xf5034222
d0013bd8:	6d914322 	ldcvs	3, cr4, [r1, #136]	; 0x88
d0013bdc:	035cf103 	cmpeq	ip, #-1073741824	; 0xc0000000	; <UNPREDICTABLE>
d0013be0:	c000f8d3 	ldrdgt	pc, [r0], -r3
d0013be4:	0258f102 	subseq	pc, r8, #-2147483648	; 0x80000000
d0013be8:	1d0bbf1b 	stcne	15, cr11, [fp, #-108]	; 0xffffff94
d0013bec:	4467468c 	strbtmi	r4, [r7], #-1676	; 0xfffff974
d0013bf0:	f8df6013 			; <UNDEFINED> instruction: 0xf8df6013
d0013bf4:	bf082970 	svclt	0x00082970
d0013bf8:	447a601f 	ldrbtmi	r6, [sl], #-31	; 0xffffffe1
d0013bfc:	4322f502 	msrmi	CPSR_x, #8388608	; 0x800000
d0013c00:	6d597a17 	vldrvs	s15, [r9, #-92]	; 0xffffffa4
d0013c04:	fb0e1c48 	blx	0xd039ad2e
d0013c08:	65582e01 	ldrbvs	r2, [r8, #-3585]	; 0xfffff1ff
d0013c0c:	440ef50e 	strmi	pc, [lr], #-1294	; 0xfffffaf2
d0013c10:	34549b02 	ldrbcc	r9, [r4], #-2818	; 0xfffff4fe
d0013c14:	9b039324 	blls	0xd00f88ac
d0013c18:	ce0f9325 	cdpgt	3, 0, cr9, cr15, cr5, {1}
d0013c1c:	f648c40f 			; <UNDEFINED> instruction: 0xf648c40f
d0013c20:	f84e6370 			; <UNDEFINED> instruction: 0xf84e6370
d0013c24:	f648b003 			; <UNDEFINED> instruction: 0xf648b003
d0013c28:	f84e6374 			; <UNDEFINED> instruction: 0xf84e6374
d0013c2c:	f648c003 			; <UNDEFINED> instruction: 0xf648c003
d0013c30:	e8966378 	ldm	r6, {r3, r4, r5, r6, r8, r9, sp, lr}
d0013c34:	f80e0007 			; <UNDEFINED> instruction: 0xf80e0007
d0013c38:	f6485003 			; <UNDEFINED> instruction: 0xf6485003
d0013c3c:	e8846379 	stm	r4, {r0, r3, r4, r5, r6, r8, r9, sp, lr}
d0013c40:	f80e0007 			; <UNDEFINED> instruction: 0xf80e0007
d0013c44:	e6907003 	ldr	r7, [r0], r3
d0013c48:	f7fd202d 			; <UNDEFINED> instruction: 0xf7fd202d
d0013c4c:	f8dff891 			; <UNDEFINED> instruction: 0xf8dff891
d0013c50:	f2403918 	vmul.i8	d19, d0, d8
d0013c54:	46801101 	strmi	r1, [r0], r1, lsl #2
d0013c58:	6ada447b 	bvs	0xcf6a4e4c
d0013c5c:	d116428a 	tstle	r6, sl, lsl #5
d0013c60:	699869d9 	ldmibvs	r8, {r0, r3, r4, r6, r7, r8, fp, sp, lr}
d0013c64:	faecf7fc 	blx	0xcfb51c5c
d0013c68:	f8dfb918 			; <UNDEFINED> instruction: 0xf8dfb918
d0013c6c:	44780900 	ldrbtmi	r0, [r8], #-2304	; 0xfffff700
d0013c70:	f8d0e748 			; <UNDEFINED> instruction: 0xf8d0e748
d0013c74:	f7fcb020 			; <UNDEFINED> instruction: 0xf7fcb020
d0013c78:	f1b8fd2b 			; <UNDEFINED> instruction: 0xf1b8fd2b
d0013c7c:	d0010f00 	andle	r0, r1, r0, lsl #30
d0013c80:	0b00f1cb 	bleq	0xd00503b4
d0013c84:	bf082d05 	svclt	0x00082d05
d0013c88:	fb8bfa5f 	blx	0xce31260e
d0013c8c:	f5a2e78d 			; <UNDEFINED> instruction: 0xf5a2e78d
d0013c90:	2a017281 	bcs	0xd007069c
d0013c94:	f8d3d8e9 			; <UNDEFINED> instruction: 0xf8d3d8e9
d0013c98:	e7ecb020 	strb	fp, [ip, r0, lsr #32]!
d0013c9c:	18d0f8df 	ldmne	r0, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d0013ca0:	44792028 	ldrbtmi	r2, [r9], #-40	; 0xffffffd8
d0013ca4:	f8a0f7fd 			; <UNDEFINED> instruction: 0xf8a0f7fd
d0013ca8:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0013cac:	4621ae5e 			; <UNDEFINED> instruction: 0x4621ae5e
d0013cb0:	f7fc4630 			; <UNDEFINED> instruction: 0xf7fc4630
d0013cb4:	2800fae3 	stmdacs	r0, {r0, r1, r5, r6, r7, r9, fp, ip, sp, lr, pc}
d0013cb8:	f8dfdb0a 			; <UNDEFINED> instruction: 0xf8dfdb0a
d0013cbc:	447b38b8 	ldrbtmi	r3, [fp], #-2232	; 0xfffff748
d0013cc0:	2a006d1a 	bcs	0xd002f130
d0013cc4:	ae51f47f 	mrcge	4, 2, APSR_nzcv, cr1, cr15, {3}
d0013cc8:	28acf8df 	stmiacs	ip!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d0013ccc:	e638447a 			; <UNDEFINED> instruction: 0xe638447a
d0013cd0:	28a8f8df 	stmiacs	r8!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d0013cd4:	46304621 	ldrtmi	r4, [r0], -r1, lsr #12
d0013cd8:	f7fc447a 			; <UNDEFINED> instruction: 0xf7fc447a
d0013cdc:	bb78fa9b 	bllt	0xd1e52750
d0013ce0:	289cf8df 	ldmcs	ip, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d0013ce4:	46304621 	ldrtmi	r4, [r0], -r1, lsr #12
d0013ce8:	f7fc447a 			; <UNDEFINED> instruction: 0xf7fc447a
d0013cec:	bb50fa93 	bllt	0xd1452740
d0013cf0:	2890f8df 	ldmcs	r0, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d0013cf4:	46304621 	ldrtmi	r4, [r0], -r1, lsr #12
d0013cf8:	f7fc447a 			; <UNDEFINED> instruction: 0xf7fc447a
d0013cfc:	2800fa8b 	stmdacs	r0, {r0, r1, r3, r7, r9, fp, ip, sp, lr, pc}
d0013d00:	f04fbf0c 			; <UNDEFINED> instruction: 0xf04fbf0c
d0013d04:	f04f0900 			; <UNDEFINED> instruction: 0xf04f0900
d0013d08:	f8df090c 			; <UNDEFINED> instruction: 0xf8df090c
d0013d0c:	4621287c 			; <UNDEFINED> instruction: 0x4621287c
d0013d10:	447a4630 	ldrbtmi	r4, [sl], #-1584	; 0xfffff9d0
d0013d14:	fa7ef7fc 	blx	0xd1fd1d0c
d0013d18:	90084603 	andls	r4, r8, r3, lsl #12
d0013d1c:	0303ea59 	movweq	lr, #14937	; 0x3a59
d0013d20:	9b04d014 	blls	0xd0147d78
d0013d24:	030bea53 	movweq	lr, #47699	; 0xba53
d0013d28:	f8dfd010 			; <UNDEFINED> instruction: 0xf8dfd010
d0013d2c:	447b3860 	ldrbtmi	r3, [fp], #-2144	; 0xfffff7a0
d0013d30:	2a006d1a 	bcs	0xd002f1a0
d0013d34:	ae19f47f 	mrcge	4, 0, APSR_nzcv, cr9, cr15, {3}
d0013d38:	2854f8df 	ldmdacs	r4, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d0013d3c:	e600447a 			; <UNDEFINED> instruction: 0xe600447a
d0013d40:	0904f04f 	stmdbeq	r4, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d0013d44:	f04fe7e1 			; <UNDEFINED> instruction: 0xf04fe7e1
d0013d48:	e7de0908 	ldrb	r0, [lr, r8, lsl #18]
d0013d4c:	f1b92500 			; <UNDEFINED> instruction: 0xf1b92500
d0013d50:	95110f04 	ldrls	r0, [r1, #-3844]	; 0xfffff0fc
d0013d54:	5048f88d 	subpl	pc, r8, sp, lsl #17
d0013d58:	f8dfd17f 			; <UNDEFINED> instruction: 0xf8dfd17f
d0013d5c:	f44f1838 	vst2.8	{d17-d18}, [pc :256], r8
d0013d60:	44797085 	ldrbtmi	r7, [r9], #-133	; 0xffffff7b
d0013d64:	f7fd9101 			; <UNDEFINED> instruction: 0xf7fd9101
d0013d68:	2800f83f 	stmdacs	r0, {r0, r1, r2, r3, r4, r5, fp, ip, sp, lr, pc}
d0013d6c:	adfdf43f 	cfldrdge	mvd15, [sp, #252]!	; 0xfc
d0013d70:	f2409901 	vmla.i8	d25, d0, d1
d0013d74:	f7fd100b 			; <UNDEFINED> instruction: 0xf7fd100b
d0013d78:	2800f837 	stmdacs	r0, {r0, r1, r2, r4, r5, fp, ip, sp, lr, pc}
d0013d7c:	adf5f43f 	cfldrdge	mvd15, [r5, #252]!	; 0xfc
d0013d80:	202a9901 	eorcs	r9, sl, r1, lsl #18
d0013d84:	f830f7fd 			; <UNDEFINED> instruction: 0xf830f7fd
d0013d88:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0013d8c:	f240adee 	vadd.f32	q13, q8, q15
d0013d90:	f7fc1001 			; <UNDEFINED> instruction: 0xf7fc1001
d0013d94:	2302ffed 	movwcs	pc, #12269	; 0x2fed	; <UNPREDICTABLE>
d0013d98:	3044f88d 	subcc	pc, r4, sp, lsl #17
d0013d9c:	93012301 	movwls	r2, #4865	; 0x1301
d0013da0:	17f4f8df 	ubfxne	pc, pc, #17, #21
d0013da4:	44792029 	ldrbtmi	r2, [r9], #-41	; 0xffffffd7
d0013da8:	f81ef7fd 			; <UNDEFINED> instruction: 0xf81ef7fd
d0013dac:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0013db0:	f019addc 			; <UNDEFINED> instruction: 0xf019addc
d0013db4:	d0030f08 	andle	r0, r3, r8, lsl #30
d0013db8:	2b009b01 	blcs	0xd003a9c4
d0013dbc:	8117f040 	tsthi	r7, r0, asr #32	; <UNPREDICTABLE>
d0013dc0:	77d8f8df 			; <UNDEFINED> instruction: 0x77d8f8df
d0013dc4:	447f2500 	ldrbtmi	r2, [pc], #-1280	; 0xd0013dcc
d0013dc8:	4722f507 	strmi	pc, [r2, -r7, lsl #10]!
d0013dcc:	9b073760 	blls	0xd01e1b54
d0013dd0:	429d681b 	addsmi	r6, sp, #1769472	; 0x1b0000
d0013dd4:	232cd221 			; <UNDEFINED> instruction: 0x232cd221
d0013dd8:	f805fb03 			; <UNDEFINED> instruction: 0xf805fb03
d0013ddc:	42a3687b 	adcmi	r6, r3, #8060928	; 0x7b0000
d0013de0:	8110f040 	tsthi	r0, r0, asr #32	; <UNPREDICTABLE>
d0013de4:	46314622 	ldrtmi	r4, [r1], -r2, lsr #12
d0013de8:	f0016838 			; <UNDEFINED> instruction: 0xf0016838
d0013dec:	2800fc43 	stmdacs	r0, {r0, r1, r6, sl, fp, ip, sp, lr, pc}
d0013df0:	8108f040 	tsthi	r8, r0, asr #32	; <UNPREDICTABLE>
d0013df4:	2024f897 	mlacs	r4, r7, r8, pc	; <UNPREDICTABLE>
d0013df8:	3010f89d 	mulscc	r0, sp, r8
d0013dfc:	f040429a 			; <UNDEFINED> instruction: 0xf040429a
d0013e00:	9b048101 	blls	0xd013420c
d0013e04:	9b0bb133 	blls	0xd03002d8
d0013e08:	2025f897 	mlacs	r5, r7, r8, pc	; <UNPREDICTABLE>
d0013e0c:	429a7a1b 	addsmi	r7, sl, #110592	; 0x1b000
d0013e10:	80f8f040 	rscshi	pc, r8, r0, asr #32
d0013e14:	f2802d00 	vqdmull.s<illegal width 8>	q1, d0, d0
d0013e18:	462184bd 			; <UNDEFINED> instruction: 0x462184bd
d0013e1c:	f7fc4630 			; <UNDEFINED> instruction: 0xf7fc4630
d0013e20:	2800fff1 	stmdacs	r0, {r0, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0013e24:	84d1f2c0 	ldrbhi	pc, [r1], #704	; 0x2c0	; <UNPREDICTABLE>
d0013e28:	46304621 	ldrtmi	r4, [r0], -r1, lsr #12
d0013e2c:	ffeaf7fc 			; <UNDEFINED> instruction: 0xffeaf7fc
d0013e30:	376cf8df 			; <UNDEFINED> instruction: 0x376cf8df
d0013e34:	447b222c 	ldrbtmi	r2, [fp], #-556	; 0xfffffdd4
d0013e38:	3000fb02 	andcc	pc, r0, r2, lsl #22
d0013e3c:	2285f24a 	addcs	pc, r5, #-1610612732	; 0xa0000004
d0013e40:	7a1a5c81 	bvc	0xd06ab04c
d0013e44:	f0404291 			; <UNDEFINED> instruction: 0xf0404291
d0013e48:	6d1a84c0 	cfldrsvs	mvf8, [sl, #-768]	; 0xfffffd00
d0013e4c:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0013e50:	f8dfad8c 			; <UNDEFINED> instruction: 0xf8dfad8c
d0013e54:	447a2750 	ldrbtmi	r2, [sl], #-1872	; 0xfffff8b0
d0013e58:	f8dfe573 			; <UNDEFINED> instruction: 0xf8dfe573
d0013e5c:	447b374c 	ldrbtmi	r3, [fp], #-1868	; 0xfffff8b4
d0013e60:	f5b26ada 			; <UNDEFINED> instruction: 0xf5b26ada
d0013e64:	d1067f84 	smlabble	r6, r4, pc, r7	; <UNPREDICTABLE>
d0013e68:	2b296c9b 	blcs	0xd0a6f0dc
d0013e6c:	f7fcd103 			; <UNDEFINED> instruction: 0xf7fcd103
d0013e70:	9501fc2f 	strls	pc, [r1, #-3119]	; 0xfffff3d1
d0013e74:	2300e794 	movwcs	lr, #1940	; 0x794
d0013e78:	8730f8df 			; <UNDEFINED> instruction: 0x8730f8df
d0013e7c:	9301ad11 	movwls	sl, #7441	; 0x1d11
d0013e80:	f8df44f8 			; <UNDEFINED> instruction: 0xf8df44f8
d0013e84:	447b372c 	ldrbtmi	r3, [fp], #-1836	; 0xfffff8d4
d0013e88:	3a10ee08 	bcc	0xd044f6b0
d0013e8c:	3724f8df 			; <UNDEFINED> instruction: 0x3724f8df
d0013e90:	ee08447b 	mcr	4, 0, r4, cr8, cr11, {3}
d0013e94:	9b013a90 	blls	0xd00628dc
d0013e98:	d14a2b01 	cmple	sl, r1, lsl #22
d0013e9c:	2b009b08 	blcs	0xd003aac4
d0013ea0:	f89dd047 			; <UNDEFINED> instruction: 0xf89dd047
d0013ea4:	2b003044 	blcs	0xd001ffbc
d0013ea8:	f240d143 	vrhadd.s8	<illegal reg q14.5>, q0, <illegal reg q1.5>
d0013eac:	f7fc100b 			; <UNDEFINED> instruction: 0xf7fc100b
d0013eb0:	2800ff5f 	stmdacs	r0, {r0, r1, r2, r3, r4, r6, r8, r9, sl, fp, ip, sp, lr, pc}
d0013eb4:	f8dfd03d 			; <UNDEFINED> instruction: 0xf8dfd03d
d0013eb8:	202a1700 	eorcs	r1, sl, r0, lsl #14
d0013ebc:	910c4479 	tstls	ip, r9, ror r4
d0013ec0:	ff92f7fc 			; <UNDEFINED> instruction: 0xff92f7fc
d0013ec4:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0013ec8:	990cad50 	stmdbls	ip, {r4, r6, r8, sl, fp, sp, pc}
d0013ecc:	f7fc202a 			; <UNDEFINED> instruction: 0xf7fc202a
d0013ed0:	2800ff8b 	stmdacs	r0, {r0, r1, r3, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0013ed4:	ad49f43f 	cfstrdge	mvd15, [r9, #-252]	; 0xffffff04
d0013ed8:	f88d2304 			; <UNDEFINED> instruction: 0xf88d2304
d0013edc:	f8df3045 			; <UNDEFINED> instruction: 0xf8df3045
d0013ee0:	ab21c6dc 	blge	0xd0885a58
d0013ee4:	271c9a01 	ldrcs	r9, [ip, -r1, lsl #20]
d0013ee8:	fb0744fc 	blx	0xd01e52e2
d0013eec:	f10c3702 			; <UNDEFINED> instruction: 0xf10c3702
d0013ef0:	e8bc0c18 	ldm	ip!, {r3, r4, sl, fp}
d0013ef4:	c70f000f 	strgt	r0, [pc, -pc]
d0013ef8:	0007e89c 	muleq	r7, ip, r8
d0013efc:	0007e887 	andeq	lr, r7, r7, lsl #17
d0013f00:	1001f240 	andne	pc, r1, r0, asr #4
d0013f04:	ff34f7fc 			; <UNDEFINED> instruction: 0xff34f7fc
d0013f08:	33019b01 	movwcc	r9, #6913	; 0x1b01
d0013f0c:	f8159301 			; <UNDEFINED> instruction: 0xf8159301
d0013f10:	2b043b01 	blcs	0xd0122b1c
d0013f14:	af44f43f 	svcge	0x0044f43f
d0013f18:	f7fc202c 			; <UNDEFINED> instruction: 0xf7fc202c
d0013f1c:	2800ff29 	stmdacs	r0, {r0, r3, r5, r8, r9, sl, fp, ip, sp, lr, pc}
d0013f20:	af3ef43f 	svcge	0x003ef43f
d0013f24:	2b059b01 	blcs	0xd017ab30
d0013f28:	f8dfd1b5 			; <UNDEFINED> instruction: 0xf8dfd1b5
d0013f2c:	44780694 	ldrbtmi	r0, [r8], #-1684	; 0xfffff96c
d0013f30:	f240e5e8 	vrshl.s8	q15, q12, q8
d0013f34:	f7fc1007 			; <UNDEFINED> instruction: 0xf7fc1007
d0013f38:	b110ff1b 	tstlt	r0, fp, lsl pc	; <UNPREDICTABLE>
d0013f3c:	702b2300 	eorvc	r2, fp, r0, lsl #6
d0013f40:	ee18e7cd 	cdp	7, 1, cr14, cr8, cr13, {6}
d0013f44:	f7fc0a10 			; <UNDEFINED> instruction: 0xf7fc0a10
d0013f48:	b108ff25 	tstlt	r8, r5, lsr #30	; <UNPREDICTABLE>
d0013f4c:	e7f62303 	ldrb	r2, [r6, r3, lsl #6]!
d0013f50:	0a90ee18 	beq	0xce44f7b8
d0013f54:	ff1ef7fc 			; <UNDEFINED> instruction: 0xff1ef7fc
d0013f58:	2301b108 	movwcs	fp, #4360	; 0x1108
d0013f5c:	4640e7ef 	strbmi	lr, [r0], -pc, ror #15
d0013f60:	ff18f7fc 			; <UNDEFINED> instruction: 0xff18f7fc
d0013f64:	2305b108 	movwcs	fp, #20744	; 0x5108
d0013f68:	f8dfe7e9 			; <UNDEFINED> instruction: 0xf8dfe7e9
d0013f6c:	44780658 	ldrbtmi	r0, [r8], #-1624	; 0xfffff9a8
d0013f70:	ff10f7fc 			; <UNDEFINED> instruction: 0xff10f7fc
d0013f74:	d1f62800 	mvnsle	r2, r0, lsl #16
d0013f78:	764cf8df 			; <UNDEFINED> instruction: 0x764cf8df
d0013f7c:	6efb447f 	mrcvs	4, 7, r4, cr11, cr15, {3}
d0013f80:	f44fb38b 	vst2.32	{d27-d30}, [pc], fp
d0013f84:	f7fc7085 			; <UNDEFINED> instruction: 0xf7fc7085
d0013f88:	b1d0fef3 	ldrshlt	pc, [r0, #227]	; 0xe3	; <UNPREDICTABLE>
d0013f8c:	063cf8df 			; <UNDEFINED> instruction: 0x063cf8df
d0013f90:	f7fc4478 			; <UNDEFINED> instruction: 0xf7fc4478
d0013f94:	b918feff 	ldmdblt	r8, {r0, r1, r2, r3, r4, r5, r6, r7, r9, sl, fp, ip, sp, lr, pc}
d0013f98:	0634f8df 			; <UNDEFINED> instruction: 0x0634f8df
d0013f9c:	e5b14478 	ldr	r4, [r1, #1144]!	; 0x478
d0013fa0:	1630f8df 			; <UNDEFINED> instruction: 0x1630f8df
d0013fa4:	4479202a 	ldrbtmi	r2, [r9], #-42	; 0xffffffd6
d0013fa8:	ff1ef7fc 			; <UNDEFINED> instruction: 0xff1ef7fc
d0013fac:	d0f32800 	rscsle	r2, r3, r0, lsl #16
d0013fb0:	3e44f8b7 	mcrcc	8, 2, pc, cr4, cr7, {5}	; <UNPREDICTABLE>
d0013fb4:	f8dfb91b 			; <UNDEFINED> instruction: 0xf8dfb91b
d0013fb8:	44780620 	ldrbtmi	r0, [r8], #-1568	; 0xfffff9e0
d0013fbc:	2306e5a2 	movwcs	lr, #26018	; 0x65a2
d0013fc0:	6efbe7bd 	mrcvs	7, 7, lr, cr11, cr13, {5}
d0013fc4:	f44fb17b 	vst4.16	{d27,d29,d31,d33}, [pc :256], fp
d0013fc8:	f7fc7084 			; <UNDEFINED> instruction: 0xf7fc7084
d0013fcc:	b150fed1 	ldrsblt	pc, [r0, #-225]	; 0xffffff1f	; <UNPREDICTABLE>
d0013fd0:	1608f8df 			; <UNDEFINED> instruction: 0x1608f8df
d0013fd4:	4479202a 	ldrbtmi	r2, [r9], #-42	; 0xffffffd6
d0013fd8:	ff06f7fc 			; <UNDEFINED> instruction: 0xff06f7fc
d0013fdc:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0013fe0:	2302acc4 	movwcs	sl, #11460	; 0x2cc4
d0013fe4:	f8dfe7ab 			; <UNDEFINED> instruction: 0xf8dfe7ab
d0013fe8:	447805f8 	ldrbtmi	r0, [r8], #-1528	; 0xfffffa08
d0013fec:	f8dfe58a 			; <UNDEFINED> instruction: 0xf8dfe58a
d0013ff0:	447b35f4 	ldrbtmi	r3, [fp], #-1524	; 0xfffffa0c
d0013ff4:	2a006d1a 	bcs	0xd002f464
d0013ff8:	acb7f47f 	cfldrsge	mvf15, [r7], #508	; 0x1fc
d0013ffc:	25e8f8df 	strbcs	pc, [r8, #2271]!	; 0x8df	; <UNPREDICTABLE>
d0014000:	e49e447a 	ldr	r4, [lr], #1146	; 0x47a
d0014004:	372c3501 	strcc	r3, [ip, -r1, lsl #10]!
d0014008:	1c6ae6e1 	stclne	6, cr14, [sl], #-900	; 0xfffffc7c
d001400c:	601a2100 	andsvs	r2, sl, r0, lsl #2
d0014010:	7a3b222c 	bvc	0xd0edc8c8
d0014014:	fb02930c 	blx	0xd00b8c4e
d0014018:	eb07f305 	bl	0xd0210c34
d001401c:	93080803 	movwls	r0, #34819	; 0x8803
d0014020:	4322f508 	msrmi	CPSR_x, #8, 10	; 0x2000000
d0014024:	46183360 	ldrmi	r3, [r8], -r0, ror #6
d0014028:	fb06f001 	blx	0xd01d0036
d001402c:	96139a02 	ldrls	r9, [r3], -r2, lsl #20
d0014030:	9216ae13 	andsls	sl, r6, #304	; 0x130
d0014034:	94149a03 	ldrls	r9, [r4], #-2563	; 0xfffff5fd
d0014038:	92174604 	andsls	r4, r7, #4, 12	; 0x400000
d001403c:	a064f88d 	rsbge	pc, r4, sp, lsl #17
d0014040:	c40fce0f 	strgt	ip, [pc], #-3599	; 0xd0014048
d0014044:	0007e896 	muleq	r7, r6, r8
d0014048:	237cf24a 	cmncs	ip, #-1610612732	; 0xa0000004	; <UNPREDICTABLE>
d001404c:	0007e884 	andeq	lr, r7, r4, lsl #17
d0014050:	9003f848 	andls	pc, r3, r8, asr #16
d0014054:	2380f24a 	orrcs	pc, r0, #-1610612732	; 0xa0000004
d0014058:	a9119a01 	ldmdbge	r1, {r0, r9, fp, ip, pc}
d001405c:	2003f808 	andcs	pc, r3, r8, lsl #16
d0014060:	0200f1b9 	andeq	pc, r0, #1073741870	; 0x4000002e
d0014064:	2381f24a 	orrcs	pc, r1, #-1610612732	; 0xa0000004
d0014068:	2201bf18 	andcs	fp, r1, #24, 30	; 0x60
d001406c:	9003f808 	andls	pc, r3, r8, lsl #16
d0014070:	2382f24a 	orrcs	pc, r2, #-1610612732	; 0xa0000004
d0014074:	2003f808 	andcs	pc, r3, r8, lsl #16
d0014078:	2383f24a 	orrcs	pc, r3, #-1610612732	; 0xa0000004
d001407c:	f8089a04 			; <UNDEFINED> instruction: 0xf8089a04
d0014080:	f24ab003 	vhadd.s8	d27, d10, d3
d0014084:	f8082384 			; <UNDEFINED> instruction: 0xf8082384
d0014088:	f24a2003 	vhadd.s8	d18, d10, d3
d001408c:	9a0c2385 	bls	0xd031cea8
d0014090:	2003f808 	andcs	pc, r3, r8, lsl #16
d0014094:	9a019b08 	bls	0xd007acbc
d0014098:	4022f503 	eormi	pc, r2, r3, lsl #10
d001409c:	44383086 	ldrtmi	r3, [r8], #-134	; 0xffffff7a
d00140a0:	fad8f001 	blx	0xcf6500ac
d00140a4:	f7fc203b 			; <UNDEFINED> instruction: 0xf7fc203b
d00140a8:	2800fe63 	stmdacs	r0, {r0, r1, r5, r6, r9, sl, fp, ip, sp, lr, pc}
d00140ac:	ac5df47f 	cfldrdge	mvd15, [sp], {127}	; 0x7f
d00140b0:	6538f8df 	ldrvs	pc, [r8, #-2271]!	; 0xfffff721
d00140b4:	f24a232c 	vcgt.s8	d18, d10, d28
d00140b8:	447e2782 	ldrbtmi	r2, [lr], #-1922	; 0xfffff87e
d00140bc:	6505fb03 	strvs	pc, [r5, #-2819]	; 0xfffff4fd
d00140c0:	b1cc5dec 	biclt	r5, ip, ip, ror #27
d00140c4:	2b006d33 	blcs	0xd002f598
d00140c8:	ac4ff47f 	cfstrdge	mvd15, [pc], {127}	; 0x7f
d00140cc:	3520f8df 	strcc	pc, [r0, #-2271]!	; 0xfffff721
d00140d0:	a05cf8c6 	subsge	pc, ip, r6, asr #17
d00140d4:	6533447b 	ldrvs	r4, [r3, #-1147]!	; 0xfffffb85
d00140d8:	65739b02 	ldrbvs	r9, [r3, #-2818]!	; 0xfffff4fe
d00140dc:	65b39b03 	ldrvs	r9, [r3, #2819]!	; 0xb03
d00140e0:	f508e443 			; <UNDEFINED> instruction: 0xf508e443
d00140e4:	9a014022 	bls	0xd0064174
d00140e8:	3086a911 	addcc	sl, r6, r1, lsl r9
d00140ec:	f0014420 			; <UNDEFINED> instruction: 0xf0014420
d00140f0:	2800fac1 	stmdacs	r0, {r0, r6, r7, r9, fp, ip, sp, lr, pc}
d00140f4:	e35ed0d6 	cmp	lr, #214	; 0xd6
d00140f8:	14f8f8df 	ldrbtne	pc, [r8], #2271	; 0x8df	; <UNPREDICTABLE>
d00140fc:	4479207b 	ldrbtmi	r2, [r9], #-123	; 0xffffff85
d0014100:	fe72f7fc 	mrc2	7, 3, pc, cr2, cr12, {7}
d0014104:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0014108:	f8d6ac30 			; <UNDEFINED> instruction: 0xf8d6ac30
d001410c:	f24a2e48 	vceq.f32	q9, q5, q4
d0014110:	f24b237c 	vcge.s8	q9, <illegal reg q5.5>, q14
d0014114:	50ea5080 	rscpl	r5, sl, r0, lsl #1
d0014118:	f5062301 			; <UNDEFINED> instruction: 0xf5062301
d001411c:	55eb328f 	strbpl	r3, [fp, #655]!	; 0x28f
d0014120:	3393f506 	orrscc	pc, r3, #25165824	; 0x1800000
d0014124:	679c6694 			; <UNDEFINED> instruction: 0x679c6694
d0014128:	671c675c 			; <UNDEFINED> instruction: 0x671c675c
d001412c:	4084f8c3 	addmi	pc, r4, r3, asr #17
d0014130:	4080f8c3 	addmi	pc, r0, r3, asr #17
d0014134:	2383f24a 	orrcs	pc, r3, #-1610612732	; 0xa0000004
d0014138:	74bcf8df 	ldrtvc	pc, [ip], #2271	; 0x8df	; <UNPREDICTABLE>
d001413c:	447f5ceb 	ldrbtmi	r5, [pc], #-3307	; 0xd0014144
d0014140:	306cf882 	rsbcc	pc, ip, r2, lsl #17
d0014144:	fedef7fc 	mrc2	7, 6, pc, cr14, cr12, {7}
d0014148:	3e48f8d6 	mcrcc	8, 2, pc, cr8, cr6, {6}	; <UNPREDICTABLE>
d001414c:	ae214620 	cfmadda32ge	mvax1, mvax4, mvfx1, mvfx0
d0014150:	3893f507 	ldmcc	r3, {r0, r1, r2, r8, sl, ip, sp, lr, pc}
d0014154:	f7fc9303 			; <UNDEFINED> instruction: 0xf7fc9303
d0014158:	f44ffed5 			; <UNDEFINED> instruction: 0xf44ffed5
d001415c:	f7fc402f 			; <UNDEFINED> instruction: 0xf7fc402f
d0014160:	f8dffed1 			; <UNDEFINED> instruction: 0xf8dffed1
d0014164:	94023498 	strls	r3, [r2], #-1176	; 0xfffffb68
d0014168:	9308447b 	movwls	r4, #33915	; 0x847b
d001416c:	42a39b01 	adcmi	r9, r3, #1024	; 0x400
d0014170:	f7fed149 			; <UNDEFINED> instruction: 0xf7fed149
d0014174:	f8dffb63 			; <UNDEFINED> instruction: 0xf8dffb63
d0014178:	447b3488 	ldrbtmi	r3, [fp], #-1160	; 0xfffffb78
d001417c:	338ff503 	orrcc	pc, pc, #12582912	; 0xc00000
d0014180:	306cf893 	mlscc	ip, r3, r8, pc	; <UNPREDICTABLE>
d0014184:	d0032b01 	andle	r2, r3, r1, lsl #22
d0014188:	5000f44f 	andpl	pc, r0, pc, asr #8
d001418c:	febaf7fc 	mrc2	7, 5, pc, cr10, cr12, {7}
d0014190:	6470f8df 	ldrbtvs	pc, [r0], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d0014194:	f506447e 			; <UNDEFINED> instruction: 0xf506447e
d0014198:	f8d63393 			; <UNDEFINED> instruction: 0xf8d63393
d001419c:	6f5c8e48 	svcvs	0x005c8e48
d00141a0:	f0243401 			; <UNDEFINED> instruction: 0xf0243401
d00141a4:	b2a50401 	adclt	r0, r5, #16777216	; 0x1000000
d00141a8:	4030f445 	eorsmi	pc, r0, r5, asr #8
d00141ac:	feaaf7fc 	mcr2	7, 5, pc, cr10, cr12, {7}	; <UNPREDICTABLE>
d00141b0:	5080f64b 	addpl	pc, r0, fp, asr #12
d00141b4:	fea6f7fc 	mcr2	7, 5, pc, cr6, cr12, {7}	; <UNPREDICTABLE>
d00141b8:	2b006d33 	blcs	0xd002f68c
d00141bc:	abd5f47f 	blge	0xcf5913c0
d00141c0:	3444f8df 	strbcc	pc, [r4], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d00141c4:	4530f445 	ldrmi	pc, [r0, #-1093]!	; 0xfffffbbb
d00141c8:	447b9a03 	ldrbtmi	r9, [fp], #-2563	; 0xfffff5fd
d00141cc:	0580f045 	streq	pc, [r0, #69]	; 0x45
d00141d0:	f882441a 			; <UNDEFINED> instruction: 0xf882441a
d00141d4:	0a2d5040 	beq	0xd0b682dc
d00141d8:	5041f882 	subpl	pc, r1, r2, lsl #17
d00141dc:	b1429a02 	cmplt	r2, r2, lsl #20
d00141e0:	44133402 	ldrmi	r3, [r3], #-1026	; 0xfffffbfe
d00141e4:	b2a400a4 	adclt	r0, r4, #164	; 0xa4
d00141e8:	4040f883 	submi	pc, r0, r3, lsl #17
d00141ec:	f8830a24 			; <UNDEFINED> instruction: 0xf8830a24
d00141f0:	f8df4041 			; <UNDEFINED> instruction: 0xf8df4041
d00141f4:	26004418 			; <UNDEFINED> instruction: 0x26004418
d00141f8:	f504447c 			; <UNDEFINED> instruction: 0xf504447c
d00141fc:	f5043587 			; <UNDEFINED> instruction: 0xf5043587
d0014200:	3568378f 	strbcc	r3, [r8, #-1935]!	; 0xfffff871
d0014204:	6972e0b5 	ldmdbvs	r2!, {r0, r2, r4, r5, r7, sp, lr, pc}^
d0014208:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d001420c:	9018f896 	mulsls	r8, r6, r8
d0014210:	f8d6429a 			; <UNDEFINED> instruction: 0xf8d6429a
d0014214:	f8d6a010 			; <UNDEFINED> instruction: 0xf8d6a010
d0014218:	d010b00c 	andsle	fp, r0, ip
d001421c:	447b4bfc 	ldrbtmi	r4, [fp], #-3068	; 0xfffff404
d0014220:	2a006d1a 	bcs	0xd002f690
d0014224:	aba1f47f 	blge	0xce891428
d0014228:	f8c34afa 			; <UNDEFINED> instruction: 0xf8c34afa
d001422c:	447ab054 	ldrbtmi	fp, [sl], #-84	; 0xffffffac
d0014230:	a058f8c3 	subsge	pc, r8, r3, asr #17
d0014234:	905cf8c3 	subsls	pc, ip, r3, asr #17
d0014238:	f7ff651a 			; <UNDEFINED> instruction: 0xf7ff651a
d001423c:	ab11bb96 	blge	0xd048309c
d0014240:	ad1a46b4 	ldcge	6, cr4, [sl, #-720]	; 0xfffffd30
d0014244:	93045ce3 	movwls	r5, #19683	; 0x4ce3
d0014248:	000fe8bc 			; <UNDEFINED> instruction: 0x000fe8bc
d001424c:	e89cc50f 	ldm	ip, {r0, r1, r2, r3, r8, sl, lr, pc}
d0014250:	68330007 	ldmdavs	r3!, {r0, r1, r2}
d0014254:	0007e885 	andeq	lr, r7, r5, lsl #17
d0014258:	46186871 			; <UNDEFINED> instruction: 0x46186871
d001425c:	910f930c 	tstls	pc, ip, lsl #6
d0014260:	fdfef7fc 	ldc2l	7, cr15, [lr, #1008]!	; 0x3f0
d0014264:	9b0c2800 	blls	0xd031e26c
d0014268:	db3e990f 	blle	0xd0fba6ac
d001426c:	447a4aea 	ldrbtmi	r4, [sl], #-2794	; 0xfffff516
d0014270:	1040eb02 	subne	lr, r0, r2, lsl #22
d0014274:	308ff500 	addcc	pc, pc, r0, lsl #10
d0014278:	508cf890 	umullpl	pc, ip, r0, r8	; <UNPREDICTABLE>
d001427c:	3093f502 	addscc	pc, r3, r2, lsl #10
d0014280:	42856f80 	addmi	r6, r5, #128, 30	; 0x200
d0014284:	6d15d131 	ldfvsd	f5, [r5, #-196]	; 0xffffff3c
d0014288:	d1672d00 	cmnle	r7, r0, lsl #26
d001428c:	f8c24be3 			; <UNDEFINED> instruction: 0xf8c24be3
d0014290:	447bb054 	ldrbtmi	fp, [fp], #-84	; 0xffffffac
d0014294:	a058f8c2 	subsge	pc, r8, r2, asr #17
d0014298:	905cf8c2 	subsls	pc, ip, r2, asr #17
d001429c:	2c046513 	cfstr32cs	mvfx6, [r4], {19}
d00142a0:	f64fd15e 			; <UNDEFINED> instruction: 0xf64fd15e
d00142a4:	f04f00d7 			; <UNDEFINED> instruction: 0xf04f00d7
d00142a8:	f7fc0900 			; <UNDEFINED> instruction: 0xf7fc0900
d00142ac:	4bdcfe2b 	blmi	0xcf753b60
d00142b0:	447b2000 	ldrbtmi	r2, [fp], #-0
d00142b4:	3e48f8d3 	mcrcc	8, 2, pc, cr8, cr3, {6}	; <UNPREDICTABLE>
d00142b8:	f7fc9302 			; <UNDEFINED> instruction: 0xf7fc9302
d00142bc:	ab11fe23 	blge	0xd0493b50
d00142c0:	2b055ce3 	blcs	0xd016b654
d00142c4:	fa1fd10a 	blx	0xd08086f4
d00142c8:	ea40f089 	b	0xd10504f4
d00142cc:	f44000c0 	vst4.<illegal width 64>	{d16-d19}, [r0], r0
d00142d0:	f0404032 			; <UNDEFINED> instruction: 0xf0404032
d00142d4:	b28000c0 	addlt	r0, r0, #192	; 0xc0
d00142d8:	fe14f7fc 	mrc2	7, 0, pc, cr4, cr12, {7}
d00142dc:	46284649 	strtmi	r4, [r8], -r9, asr #12
d00142e0:	361c3401 	ldrcc	r3, [ip], -r1, lsl #8
d00142e4:	fe89f7fc 	mcr2	7, 4, pc, cr9, cr12, {7}	; <UNPREDICTABLE>
d00142e8:	f8d8e740 			; <UNDEFINED> instruction: 0xf8d8e740
d00142ec:	2d405070 	stclcs	0, cr5, [r0, #-448]	; 0xfffffe40
d00142f0:	6d3dd10a 	ldfvsd	f5, [sp, #-40]!	; 0xffffffd8
d00142f4:	9b08bb95 	blls	0xd0243150
d00142f8:	b054f8c7 	subslt	pc, r4, r7, asr #17
d00142fc:	f8c7653b 			; <UNDEFINED> instruction: 0xf8c7653b
d0014300:	f8c7a058 			; <UNDEFINED> instruction: 0xf8c7a058
d0014304:	e7ca905c 			; <UNDEFINED> instruction: 0xe7ca905c
d0014308:	b074f8cd 	rsbslt	pc, r4, sp, asr #17
d001430c:	1b45eb07 	blne	0xd118ef30
d0014310:	a078f8cd 	rsbsge	pc, r8, sp, asr #17
d0014314:	0a68f10d 	beq	0xd1a50750
d0014318:	3b8ff50b 	blcc	0xce41174c
d001431c:	9080f88d 	addls	pc, r0, sp, lsl #17
d0014320:	0c01f105 	stfeqd	f7, [r1], {5}
d0014324:	e078f898 			; <UNDEFINED> instruction: 0xe078f898
d0014328:	0970f10b 	ldmdbeq	r0!, {r0, r1, r3, r8, ip, sp, lr, pc}^
d001432c:	c070f8c8 	rsbsgt	pc, r0, r8, asr #17
d0014330:	e08cf88b 	add	pc, ip, fp, lsl #17
d0014334:	311ae9cd 	tstcc	sl, sp, asr #19
d0014338:	000fe8ba 			; <UNDEFINED> instruction: 0x000fe8ba
d001433c:	000fe8a9 	andeq	lr, pc, r9, lsr #17
d0014340:	f88b9b04 			; <UNDEFINED> instruction: 0xf88b9b04
d0014344:	f8d8308d 			; <UNDEFINED> instruction: 0xf8d8308d
d0014348:	e89a3074 	ldm	sl, {r2, r4, r5, r6, ip, sp}
d001434c:	459c0007 	ldrmi	r0, [ip, #7]
d0014350:	0007e889 	andeq	lr, r7, r9, lsl #17
d0014354:	f8c8d9a3 			; <UNDEFINED> instruction: 0xf8c8d9a3
d0014358:	e7a0c074 			; <UNDEFINED> instruction: 0xe7a0c074
d001435c:	e79e2500 	ldr	r2, [lr, r0, lsl #10]
d0014360:	e7ac46a1 	str	r4, [ip, r1, lsr #13]!
d0014364:	23003601 	movwcs	r3, #1537	; 0x601
d0014368:	f8554642 			; <UNDEFINED> instruction: 0xf8554642
d001436c:	f7fd1b04 			; <UNDEFINED> instruction: 0xf7fd1b04
d0014370:	6ebbf83f 	mrcvs	8, 5, APSR_nzcv, cr11, cr15, {1}
d0014374:	429e6d20 	addsmi	r6, lr, #32, 26	; 0x800
d0014378:	f7ffd3f4 			; <UNDEFINED> instruction: 0xf7ffd3f4
d001437c:	2b00baf6 	blcs	0xd0042f5c
d0014380:	a903f47f 	stmdbge	r3, {r0, r1, r2, r3, r4, r5, r6, sl, ip, sp, lr, pc}
d0014384:	210448a7 	smlatbcs	r4, r7, r8, r4
d0014388:	f7fc4478 			; <UNDEFINED> instruction: 0xf7fc4478
d001438c:	2800fd3b 	stmdacs	r0, {r0, r1, r3, r4, r5, r8, sl, fp, ip, sp, lr, pc}
d0014390:	232cdb0f 			; <UNDEFINED> instruction: 0x232cdb0f
d0014394:	4400fb03 	strmi	pc, [r0], #-2819	; 0xfffff4fd
d0014398:	2382f24a 	orrcs	pc, r2, #-1610612732	; 0xa0000004
d001439c:	b1435ce3 	smlalttlt	r5, r3, r3, ip
d00143a0:	2380f24a 	orrcs	pc, r0, #-1610612732	; 0xa0000004
d00143a4:	b1535ce3 	cmplt	r3, r3, ror #25
d00143a8:	2387f24a 	orrcs	pc, r7, #-1610612732	; 0xa0000004
d00143ac:	2b045ce3 	blcs	0xd012b740
d00143b0:	489dd005 	ldmmi	sp, {r0, r2, ip, lr, pc}
d00143b4:	f7fc4478 			; <UNDEFINED> instruction: 0xf7fc4478
d00143b8:	f7fffd07 			; <UNDEFINED> instruction: 0xf7fffd07
d00143bc:	4c9bb8e6 	ldcmi	8, cr11, [fp], {230}	; 0xe6
d00143c0:	f24a232c 	vcgt.s8	d18, d10, d28
d00143c4:	447c227c 	ldrbtmi	r2, [ip], #-636	; 0xfffffd84
d00143c8:	4000fb03 	andmi	pc, r0, r3, lsl #22
d00143cc:	58822300 	stmpl	r2, {r8, r9, sp}
d00143d0:	6d204619 	stcvs	6, cr4, [r0, #-100]!	; 0xffffff9c
d00143d4:	f80cf7fd 			; <UNDEFINED> instruction: 0xf80cf7fd
d00143d8:	b8d7f7ff 	ldmlt	r7, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}^
d00143dc:	232c88aa 			; <UNDEFINED> instruction: 0x232c88aa
d00143e0:	f24a4353 	vcge.s8	q10, q5, <illegal reg q1.5>
d00143e4:	18e12282 	stmiane	r1!, {r1, r7, r9, sp}^
d00143e8:	2a005c8a 	bcs	0xd002b618
d00143ec:	f503d142 			; <UNDEFINED> instruction: 0xf503d142
d00143f0:	33604322 	cmncc	r0, #-2013265920	; 0x88000000
d00143f4:	68d94423 	ldmvs	r9, {r0, r1, r5, sl, lr}^
d00143f8:	7e1b691a 			; <UNDEFINED> instruction: 0x7e1b691a
d00143fc:	8050f8c4 	subshi	pc, r0, r4, asr #17
d0014400:	65a26561 	strvs	r6, [r2, #1377]!	; 0x561
d0014404:	360165e3 	strcc	r6, [r1], -r3, ror #11
d0014408:	6e7b3508 	cdpvs	5, 7, cr3, cr11, cr8, {0}
d001440c:	d202429e 	andle	r4, r2, #-536870903	; 0xe0000009
d0014410:	2b006d23 	blcs	0xd002f8a4
d0014414:	4b86d0e2 	blmi	0xce1c87a4
d0014418:	f8d3447b 			; <UNDEFINED> instruction: 0xf8d3447b
d001441c:	f8d32e4c 			; <UNDEFINED> instruction: 0xf8d32e4c
d0014420:	eb011e48 	bl	0xd005bd48
d0014424:	f1090902 			; <UNDEFINED> instruction: 0xf1090902
d0014428:	f0220203 			; <UNDEFINED> instruction: 0xf0220203
d001442c:	92010203 	andls	r0, r1, #805306368	; 0x30000000
d0014430:	2258f24a 	subscs	pc, r8, #-1610612732	; 0xa0000004
d0014434:	b32e589e 			; <UNDEFINED> instruction: 0xb32e589e
d0014438:	441e9b01 	ldrmi	r9, [lr], #-2817	; 0xfffff4ff
d001443c:	031ff106 	tsteq	pc, #-2147483647	; 0x80000001	; <UNPREDICTABLE>
d0014440:	3f80f5b6 	svccc	0x0080f5b6
d0014444:	031ff023 	tsteq	pc, #35	; 0x23	; <UNPREDICTABLE>
d0014448:	d9039302 	stmdble	r3, {r1, r8, r9, ip, pc}
d001444c:	44784879 	ldrbtmi	r4, [r8], #-2169	; 0xfffff787
d0014450:	fcbaf7fc 	ldc2	7, cr15, [sl], #1008	; 0x3f0
d0014454:	f04f4c78 			; <UNDEFINED> instruction: 0xf04f4c78
d0014458:	4b780a00 	blmi	0xd1e16c60
d001445c:	46d0447c 			; <UNDEFINED> instruction: 0x46d0447c
d0014460:	f504447b 			; <UNDEFINED> instruction: 0xf504447b
d0014464:	f504479c 			; <UNDEFINED> instruction: 0xf504479c
d0014468:	93034b0e 	movwls	r4, #15118	; 0x3b0e
d001446c:	f10b3750 			; <UNDEFINED> instruction: 0xf10b3750
d0014470:	e02c0b50 	eor	r0, ip, r0, asr fp
d0014474:	237cf24a 	cmncs	ip, #-1610612732	; 0xa0000004	; <UNPREDICTABLE>
d0014478:	68282201 	stmdavs	r8!, {r0, r9, sp}
d001447c:	f7fc58c9 			; <UNDEFINED> instruction: 0xf7fc58c9
d0014480:	e7c0ff83 	strb	pc, [r0, r3, lsl #31]	; <UNPREDICTABLE>
d0014484:	e7d9464e 	ldrb	r4, [r9, lr, asr #12]
d0014488:	683879ba 	ldmdavs	r8!, {r1, r3, r4, r5, r7, r8, fp, ip, sp, lr}
d001448c:	bb3a88b9 	bllt	0xd0eb6778
d0014490:	5e48f8d4 	mcrpl	8, 2, pc, cr8, cr4, {6}	; <UNPREDICTABLE>
d0014494:	f100194b 			; <UNDEFINED> instruction: 0xf100194b
d0014498:	1e51050c 	cdpne	5, 5, cr0, cr1, cr12, {0}
d001449c:	f10a9004 			; <UNDEFINED> instruction: 0xf10a9004
d00144a0:	f0250a01 			; <UNDEFINED> instruction: 0xf0250a01
d00144a4:	424a0503 	submi	r0, sl, #12582912	; 0xc00000
d00144a8:	0708f107 	streq	pc, [r8, -r7, lsl #2]
d00144ac:	0505eba3 	streq	lr, [r5, #-2979]	; 0xfffff45d
d00144b0:	f24f414a 	vrhadd.s8	q10, <illegal reg q7.5>, q5
d00144b4:	b2ab2140 	adclt	r2, fp, #64, 2
d00144b8:	f7fc9205 			; <UNDEFINED> instruction: 0xf7fc9205
d00144bc:	9804fcf3 	stmdals	r4, {r0, r1, r4, r5, r6, r7, sl, fp, ip, sp, lr, pc}
d00144c0:	9a050c2b 	bls	0xd0157574
d00144c4:	21c0f24f 	biccs	pc, r0, pc, asr #4
d00144c8:	f7fc3004 			; <UNDEFINED> instruction: 0xf7fc3004
d00144cc:	f8dbfceb 			; <UNDEFINED> instruction: 0xf8dbfceb
d00144d0:	6d232000 	stcvs	0, cr2, [r3, #-0]
d00144d4:	f0804592 			; <UNDEFINED> instruction: 0xf0804592
d00144d8:	2b0080d8 	blcs	0xd0034840
d00144dc:	e0c3d0d4 	ldrd	sp, [r3], #4
d00144e0:	f0402a01 			; <UNDEFINED> instruction: 0xf0402a01
d00144e4:	232880ad 			; <UNDEFINED> instruction: 0x232880ad
d00144e8:	f648434b 			; <UNDEFINED> instruction: 0xf648434b
d00144ec:	18e56178 	stmiane	r5!, {r3, r4, r5, r6, r8, sp, lr}^
d00144f0:	99025c6d 	stmdbls	r2, {r0, r2, r3, r5, r6, sl, fp, ip, lr}
d00144f4:	9901468c 	stmdbls	r1, {r2, r3, r7, r9, sl, lr}
d00144f8:	bf182d07 	svclt	0x00182d07
d00144fc:	9903468c 	stmdbls	r3, {r2, r3, r7, r9, sl, lr}
d0014500:	f648440b 			; <UNDEFINED> instruction: 0xf648440b
d0014504:	585b6174 	ldmdapl	fp, {r2, r4, r5, r6, r8, sp, lr}^
d0014508:	e7c44463 	strb	r4, [r4, r3, ror #8]
d001450c:	ffffee6e 			; <UNDEFINED> instruction: 0xffffee6e
d0014510:	ffffee6b 			; <UNDEFINED> instruction: 0xffffee6b
d0014514:	ffffee68 			; <UNDEFINED> instruction: 0xffffee68
d0014518:	0000468a 	andeq	r4, r0, sl, lsl #13
d001451c:	fffff6fc 			; <UNDEFINED> instruction: 0xfffff6fc
d0014520:	fffff6fc 			; <UNDEFINED> instruction: 0xfffff6fc
d0014524:	fffff634 			; <UNDEFINED> instruction: 0xfffff634
d0014528:	fffff62a 			; <UNDEFINED> instruction: 0xfffff62a
d001452c:	000045ea 	andeq	r4, r0, sl, ror #11
d0014530:	fffff622 			; <UNDEFINED> instruction: 0xfffff622
d0014534:	00004552 	andeq	r4, r0, r2, asr r5
d0014538:	0000452e 	andeq	r4, r0, lr, lsr #10
d001453c:	fffff621 			; <UNDEFINED> instruction: 0xfffff621
d0014540:	000044da 	ldrdeq	r4, [r0], -sl
d0014544:	fffff5f3 			; <UNDEFINED> instruction: 0xfffff5f3
d0014548:	ffffec6f 			; <UNDEFINED> instruction: 0xffffec6f
d001454c:	00004488 	andeq	r4, r0, r8, lsl #9
d0014550:	fffff533 			; <UNDEFINED> instruction: 0xfffff533
d0014554:	fffff540 			; <UNDEFINED> instruction: 0xfffff540
d0014558:	fffff54e 			; <UNDEFINED> instruction: 0xfffff54e
d001455c:	fffff5a4 			; <UNDEFINED> instruction: 0xfffff5a4
d0014560:	000043f8 	strdeq	r4, [r0], -r8
d0014564:	000043c6 	andeq	r4, r0, r6, asr #7
d0014568:	00004368 	andeq	r4, r0, r8, ror #6
d001456c:	fffff4aa 			; <UNDEFINED> instruction: 0xfffff4aa
d0014570:	fffff4d8 			; <UNDEFINED> instruction: 0xfffff4d8
d0014574:	00004302 	andeq	r4, r0, r2, lsl #6
d0014578:	fffff370 			; <UNDEFINED> instruction: 0xfffff370
d001457c:	fffff4c3 			; <UNDEFINED> instruction: 0xfffff4c3
d0014580:	fffff4c2 			; <UNDEFINED> instruction: 0xfffff4c2
d0014584:	fffff4bf 			; <UNDEFINED> instruction: 0xfffff4bf
d0014588:	fffff4b4 			; <UNDEFINED> instruction: 0xfffff4b4
d001458c:	00004292 	muleq	r0, r2, r2
d0014590:	fffff48f 			; <UNDEFINED> instruction: 0xfffff48f
d0014594:	fffff4a9 			; <UNDEFINED> instruction: 0xfffff4a9
d0014598:	fffff5b1 			; <UNDEFINED> instruction: 0xfffff5b1
d001459c:	000041fa 	strdeq	r4, [r0], -sl
d00145a0:	0000418a 	andeq	r4, r0, sl, lsl #3
d00145a4:	fffff546 			; <UNDEFINED> instruction: 0xfffff546
d00145a8:	00004162 	andeq	r4, r0, r2, ror #2
d00145ac:	ffffe8d9 			; <UNDEFINED> instruction: 0xffffe8d9
d00145b0:	fffff407 			; <UNDEFINED> instruction: 0xfffff407
d00145b4:	ffffe8c0 			; <UNDEFINED> instruction: 0xffffe8c0
d00145b8:	fffff3a4 			; <UNDEFINED> instruction: 0xfffff3a4
d00145bc:	000040d8 	ldrdeq	r4, [r0], -r8
d00145c0:	fffff308 			; <UNDEFINED> instruction: 0xfffff308
d00145c4:	ffffe7f4 			; <UNDEFINED> instruction: 0xffffe7f4
d00145c8:	00004044 	andeq	r4, r0, r4, asr #32
d00145cc:	fffff305 			; <UNDEFINED> instruction: 0xfffff305
d00145d0:	fffff305 			; <UNDEFINED> instruction: 0xfffff305
d00145d4:	fffff322 			; <UNDEFINED> instruction: 0xfffff322
d00145d8:	fffff333 			; <UNDEFINED> instruction: 0xfffff333
d00145dc:	fffff33b 			; <UNDEFINED> instruction: 0xfffff33b
d00145e0:	fffff349 			; <UNDEFINED> instruction: 0xfffff349
d00145e4:	00003fce 	andeq	r3, r0, lr, asr #31
d00145e8:	fffff379 			; <UNDEFINED> instruction: 0xfffff379
d00145ec:	00003f06 	andeq	r3, r0, r6, lsl #30
d00145f0:	fffff33d 			; <UNDEFINED> instruction: 0xfffff33d
d00145f4:	fffff32c 			; <UNDEFINED> instruction: 0xfffff32c
d00145f8:	00003e82 	andeq	r3, r0, r2, lsl #29
d00145fc:	ffffe671 			; <UNDEFINED> instruction: 0xffffe671
d0014600:	00003e46 	andeq	r3, r0, r6, asr #28
d0014604:	00003e2c 	andeq	r3, r0, ip, lsr #28
d0014608:	0001747e 	andeq	r7, r1, lr, ror r4
d001460c:	00003dc8 	andeq	r3, r0, r8, asr #27
d0014610:	00003da2 	andeq	r3, r0, r2, lsr #27
d0014614:	fffff21c 			; <UNDEFINED> instruction: 0xfffff21c
d0014618:	00003d52 	andeq	r3, r0, r2, asr sp
d001461c:	ffffe52b 			; <UNDEFINED> instruction: 0xffffe52b
d0014620:	00003d0e 	andeq	r3, r0, lr, lsl #26
d0014624:	ffffee3e 			; <UNDEFINED> instruction: 0xffffee3e
d0014628:	fffff0c2 			; <UNDEFINED> instruction: 0xfffff0c2
d001462c:	00003bfa 	strdeq	r3, [r0], -sl
d0014630:	00003ba8 	andeq	r3, r0, r8, lsr #23
d0014634:	fffff083 			; <UNDEFINED> instruction: 0xfffff083
d0014638:	00003b64 	andeq	r3, r0, r4, ror #22
d001463c:	00003b60 	andeq	r3, r0, r0, ror #22
d0014640:	f24a232c 	vcgt.s8	d18, d10, d28
d0014644:	434b2582 	movtmi	r2, #46466	; 0xb582
d0014648:	5d4d18e1 	stclpl	8, cr1, [sp, #-900]	; 0xfffffc7c
d001464c:	f503b9ad 			; <UNDEFINED> instruction: 0xf503b9ad
d0014650:	486b4322 	stmdami	fp!, {r1, r5, r8, r9, lr}^
d0014654:	44783360 	ldrbtmi	r3, [r8], #-864	; 0xfffffca0
d0014658:	68d94423 	ldmvs	r9, {r0, r1, r5, sl, lr}^
d001465c:	7e1b691a 			; <UNDEFINED> instruction: 0x7e1b691a
d0014660:	65616520 	strbvs	r6, [r1, #-1312]!	; 0xfffffae0
d0014664:	65e365a2 	strbvs	r6, [r3, #1442]!	; 0x5a2
d0014668:	9c504b66 	mrrcls	11, 6, r4, r0, cr6
d001466c:	3350447b 	cmpcc	r0, #2063597568	; 0x7b000000
d0014670:	e884cb0f 	stm	r4, {r0, r1, r2, r3, r8, r9, fp, lr, pc}
d0014674:	f7fe000f 			; <UNDEFINED> instruction: 0xf7fe000f
d0014678:	f24abfa8 	vmax.f32	d27, d26, d24
d001467c:	f44f237c 	vst2.16	{d18-d21}, [pc :256], ip
d0014680:	58cb5800 	stmiapl	fp, {fp, ip, lr}^
d0014684:	0301f043 	movweq	pc, #4163	; 0x1043	; <UNPREDICTABLE>
d0014688:	9303e705 	movwls	lr, #14085	; 0x3705
d001468c:	d1eb2b00 	mvnle	r2, r0, lsl #22
d0014690:	a174f8df 	ldrsbge	pc, [r4, #-143]!	; 0xffffff71	; <UNPREDICTABLE>
d0014694:	6765f504 	strbvs	pc, [r5, -r4, lsl #10]!	; <UNPREDICTABLE>
d0014698:	0e48f8d4 	mcreq	8, 2, pc, cr8, cr4, {6}	; <UNPREDICTABLE>
d001469c:	44fa1cf5 	ldrbtmi	r1, [sl], #3317	; 0xcf5
d00146a0:	2e4cf8d4 	mcrcs	8, 2, pc, cr12, cr4, {6}	; <UNPREDICTABLE>
d00146a4:	f0254639 			; <UNDEFINED> instruction: 0xf0254639
d00146a8:	f10a0503 			; <UNDEFINED> instruction: 0xf10a0503
d00146ac:	f8df0a40 			; <UNDEFINED> instruction: 0xf8df0a40
d00146b0:	f504b15c 			; <UNDEFINED> instruction: 0xf504b15c
d00146b4:	4450440e 	ldrbmi	r4, [r0], #-1038	; 0xfffffbf2
d00146b8:	f00044fb 			; <UNDEFINED> instruction: 0xf00044fb
d00146bc:	9b03ffcb 	blls	0xd01145f0
d00146c0:	0009eb0a 	andeq	lr, r9, sl, lsl #22
d00146c4:	0209eba5 	andeq	lr, r9, #168960	; 0x29400
d00146c8:	f5a74619 			; <UNDEFINED> instruction: 0xf5a74619
d00146cc:	f0006965 			; <UNDEFINED> instruction: 0xf0006965
d00146d0:	f507ffb3 			; <UNDEFINED> instruction: 0xf507ffb3
d00146d4:	9b034714 	blls	0xd00e632c
d00146d8:	37043470 	smlsdxcc	r4, r0, r4, r3
d00146dc:	0b40f10b 	bleq	0xd1050b10
d00146e0:	683b469a 	ldmdavs	fp!, {r1, r3, r4, r7, r9, sl, lr}
d00146e4:	d346459a 	movtle	r4, #26010	; 0x659a
d00146e8:	ac212740 	stcge	7, cr2, [r1], #-256	; 0xffffff00
d00146ec:	463a2100 	ldrtmi	r2, [sl], -r0, lsl #2
d00146f0:	f0004620 			; <UNDEFINED> instruction: 0xf0004620
d00146f4:	4946ffa1 	stmdbmi	r6, {r0, r5, r7, r8, r9, sl, fp, ip, sp, lr, pc}^
d00146f8:	46202208 	strtmi	r2, [r0], -r8, lsl #4
d00146fc:	443d4479 	ldrtmi	r4, [sp], #-1145	; 0xfffffb87
d0014700:	ffa8f000 			; <UNDEFINED> instruction: 0xffa8f000
d0014704:	9a022302 	bls	0xd009d314
d0014708:	93234631 			; <UNDEFINED> instruction: 0x93234631
d001470c:	235cf24a 	cmpcs	ip, #-1610612732	; 0xa0000004	; <UNPREDICTABLE>
d0014710:	f8599724 			; <UNDEFINED> instruction: 0xf8599724
d0014714:	4f3f3003 	svcmi	0x003f3003
d0014718:	9626331f 			; <UNDEFINED> instruction: 0x9626331f
d001471c:	9525447f 	strls	r4, [r5, #-1151]!	; 0xfffffb81
d0014720:	952a4413 	strls	r4, [sl, #-1043]!	; 0xfffffbed
d0014724:	0040f107 	subeq	pc, r0, r7, lsl #2
d0014728:	f023463e 			; <UNDEFINED> instruction: 0xf023463e
d001472c:	f8cd031f 			; <UNDEFINED> instruction: 0xf8cd031f
d0014730:	444380b8 	strbmi	r8, [r3], #-184	; 0xffffff48
d0014734:	23019327 	movwcs	r9, #4903	; 0x1327
d0014738:	4b309328 	blmi	0xd0c393e0
d001473c:	23209329 			; <UNDEFINED> instruction: 0x23209329
d0014740:	f1b8932c 			; <UNDEFINED> instruction: 0xf1b8932c
d0014744:	bf180300 	svclt	0x00180300
d0014748:	932f2301 			; <UNDEFINED> instruction: 0x932f2301
d001474c:	fd18f7fb 	ldc2	7, cr15, [r8, #-1004]	; 0xfffffc14
d0014750:	cc0f9030 	stcgt	0, cr9, [pc], {48}	; 0x30
d0014754:	cc0fc60f 	stcgt	6, cr12, [pc], {15}
d0014758:	cc0fc60f 	stcgt	6, cr12, [pc], {15}
d001475c:	e894c60f 	ldm	r4, {r0, r1, r2, r3, r9, sl, lr, pc}
d0014760:	e886000f 	stm	r6, {r0, r1, r2, r3}
d0014764:	9b0e000f 	blls	0xd03947a8
d0014768:	4628601f 			; <UNDEFINED> instruction: 0x4628601f
d001476c:	ecbdb045 	ldc	0, cr11, [sp], #276	; 0x114
d0014770:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d0014774:	7a238ff0 	bvc	0xd08f873c
d0014778:	d0072b07 	andle	r2, r7, r7, lsl #22
d001477c:	22046860 	andcs	r6, r4, #96, 16	; 0x600000
d0014780:	46219b01 	strtmi	r9, [r1], -r1, lsl #22
d0014784:	44584418 	ldrbmi	r4, [r8], #-1048	; 0xfffffbe8
d0014788:	ff64f000 			; <UNDEFINED> instruction: 0xff64f000
d001478c:	0a01f10a 	beq	0xd0090bbc
d0014790:	e7a63428 	str	r3, [r6, r8, lsr #8]!
d0014794:	232c4c20 			; <UNDEFINED> instruction: 0x232c4c20
d0014798:	2280f24a 	addcs	pc, r0, #-1610612732	; 0xa0000004
d001479c:	447c9901 	ldrbtmi	r9, [ip], #-2305	; 0xfffff6ff
d00147a0:	4305fb03 	movwmi	pc, #23299	; 0x5b03	; <UNPREDICTABLE>
d00147a4:	42915c9a 	addsmi	r5, r1, #39424	; 0x9a00
d00147a8:	f24ad105 	vrhadd.s8	d29, d10, d5
d00147ac:	5c9b2283 	lfmpl	f2, 4, [fp], {131}	; 0x83
d00147b0:	f43f459b 			; <UNDEFINED> instruction: 0xf43f459b
d00147b4:	4b19ac96 	blmi	0xd067fa14
d00147b8:	6d1a447b 	cfldrsvs	mvf4, [sl, #-492]	; 0xfffffe14
d00147bc:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d00147c0:	4a17a8d4 	bmi	0xd05feb18
d00147c4:	f7ff447a 			; <UNDEFINED> instruction: 0xf7ff447a
d00147c8:	4f16b8bc 	svcmi	0x0016b8bc
d00147cc:	f507447f 			; <UNDEFINED> instruction: 0xf507447f
d00147d0:	6e1d434e 	cdpvs	3, 1, cr4, cr13, cr14, {2}
d00147d4:	f5b53360 			; <UNDEFINED> instruction: 0xf5b53360
d00147d8:	f47f7f80 			; <UNDEFINED> instruction: 0xf47f7f80
d00147dc:	6d3bac16 	ldcvs	12, cr10, [fp, #-88]!	; 0xffffffa8
d00147e0:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d00147e4:	4b10a8c2 	blmi	0xd043eaf4
d00147e8:	a05cf8c7 	subsge	pc, ip, r7, asr #17
d00147ec:	653b447b 	ldrvs	r4, [fp, #-1147]!	; 0xfffffb85
d00147f0:	657b9b02 	ldrbvs	r9, [fp, #-2818]!	; 0xfffff4fe
d00147f4:	65bb9b03 	ldrvs	r9, [fp, #2819]!	; 0xb03
d00147f8:	b8b7f7ff 	ldmlt	r7!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}
d00147fc:	d0010000 	andle	r0, r1, r0
d0014800:	ffffee9f 			; <UNDEFINED> instruction: 0xffffee9f
d0014804:	00003954 	andeq	r3, r0, r4, asr r9
d0014808:	00016faa 	andeq	r6, r1, sl, lsr #31
d001480c:	00016f90 	muleq	r1, r0, pc	; <UNPREDICTABLE>
d0014810:	00000174 	andeq	r0, r0, r4, ror r1
d0014814:	00016f2c 	andeq	r6, r1, ip, lsr #30
d0014818:	00003822 	andeq	r3, r0, r2, lsr #16
d001481c:	00003808 	andeq	r3, r0, r8, lsl #16
d0014820:	ffffec1d 			; <UNDEFINED> instruction: 0xffffec1d
d0014824:	000037f4 	strdeq	r3, [r0], -r4
d0014828:	ffffebe2 			; <UNDEFINED> instruction: 0xffffebe2

Disassembly of section .text.sidc_compile_sources:

d001482c <.text.sidc_compile_sources>:
d001482c:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d0014830:	460e9c06 	strmi	r9, [lr], -r6, lsl #24
d0014834:	46052100 	strmi	r2, [r5], -r0, lsl #2
d0014838:	46204690 			; <UNDEFINED> instruction: 0x46204690
d001483c:	60192210 	andsvs	r2, r9, r0, lsl r2
d0014840:	f000461f 			; <UNDEFINED> instruction: 0xf000461f
d0014844:	b15dfef9 	ldrshlt	pc, [sp, #-233]	; 0xffffff17	; <UNPREDICTABLE>
d0014848:	2b0f1e73 	blcs	0xd03dc21c
d001484c:	463bd808 	ldrtmi	sp, [fp], -r8, lsl #16
d0014850:	46314642 	ldrtmi	r4, [r1], -r2, asr #12
d0014854:	94064628 	strls	r4, [r6], #-1576	; 0xfffff9d8
d0014858:	41f0e8bd 	ldrhmi	lr, [r0, #141]!	; 0x8d
d001485c:	be60f7fe 	mcrlt	7, 3, pc, cr0, cr14, {7}	; <UNPREDICTABLE>
d0014860:	447b4b03 	ldrbtmi	r4, [fp], #-2819	; 0xfffff4fd
d0014864:	e884cb0f 	stm	r4, {r0, r1, r2, r3, r8, r9, fp, lr, pc}
d0014868:	2000000f 	andcs	r0, r0, pc
d001486c:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d0014870:	00002686 	andeq	r2, r0, r6, lsl #13

Disassembly of section .text.memset:

d0015638 <.text.memset>:
d0015638:	b2c9b15a 	sbclt	fp, r9, #-2147483626	; 0x80000016
d001563c:	b4104603 	ldrlt	r4, [r0], #-1539	; 0xfffff9fd
d0015640:	461a1884 	ldrmi	r1, [sl], -r4, lsl #17
d0015644:	42a33301 	adcmi	r3, r3, #67108864	; 0x4000000
d0015648:	d1fa7011 	mvnsle	r7, r1, lsl r0
d001564c:	4b04f85d 	blmi	0xd01537c8
d0015650:	47704770 			; <UNDEFINED> instruction: 0x47704770

Disassembly of section .text.memcpy:

d0015654 <.text.memcpy>:
d0015654:	4603b162 	strmi	fp, [r3], -r2, ror #2
d0015658:	1885b430 	stmne	r5, {r4, r5, sl, ip, sp, pc}
d001565c:	461c780a 	ldrmi	r7, [ip], -sl, lsl #16
d0015660:	31013301 	tstcc	r1, r1, lsl #6
d0015664:	42abb2d2 	adcmi	fp, fp, #536870925	; 0x2000000d
d0015668:	d1f77022 	mvnsle	r7, r2, lsr #32
d001566c:	4770bc30 			; <UNDEFINED> instruction: 0x4770bc30
d0015670:	bf004770 	svclt	0x00004770

Disassembly of section .text.memcmp:

d0015674 <.text.memcmp>:
d0015674:	46034402 	strmi	r4, [r3], -r2, lsl #8
d0015678:	d0134290 	mulsle	r3, r0, r2
d001567c:	e002b470 	and	fp, r2, r0, ror r4
d0015680:	46034290 			; <UNDEFINED> instruction: 0x46034290
d0015684:	f813d00b 			; <UNDEFINED> instruction: 0xf813d00b
d0015688:	f8115b01 			; <UNDEFINED> instruction: 0xf8115b01
d001568c:	46184b01 	ldrmi	r4, [r8], -r1, lsl #22
d0015690:	42a5b2ee 	adcmi	fp, r5, #-536870898	; 0xe000000e
d0015694:	d0f3b2e3 	rscsle	fp, r3, r3, ror #5
d0015698:	bc701af0 			; <UNDEFINED> instruction: 0xbc701af0
d001569c:	20004770 	andcs	r4, r0, r0, ror r7
d00156a0:	4770bc70 			; <UNDEFINED> instruction: 0x4770bc70
d00156a4:	47702000 	ldrbmi	r2, [r0, -r0]!

Disassembly of section .text.sb_f_fixed:

d00156a8 <.text.sb_f_fixed>:
d00156a8:	0b40eeb5 	bleq	0xd1051184
d00156ac:	4ff0e92d 	svcmi	0x00f0e92d
d00156b0:	fa10eef1 	blx	0xd045127c
d00156b4:	d0354606 	eorsle	r4, r5, r6, lsl #12
d00156b8:	6b04eeb2 	blvs	0xd0151188
d00156bc:	eeb02400 	cdp	4, 11, cr2, cr0, cr0, {0}
d00156c0:	eeb47b40 	vcmp.f64	d7, d0
d00156c4:	eef10bc6 	vsqrt.f64	d16, d6
d00156c8:	da22fa10 	ble	0xd08d3f10
d00156cc:	6b00eeb7 	blvs	0xd00511b0
d00156d0:	7bc6eeb4 	blvc	0xcf1d11a8
d00156d4:	fa10eef1 	blx	0xd04512a0
d00156d8:	80a6f140 	adchi	pc, r6, r0, asr #2
d00156dc:	5b04eeb2 	blpl	0xd01511ac
d00156e0:	73a1f46f 			; <UNDEFINED> instruction: 0x73a1f46f
d00156e4:	eeb4e004 	cdp	0, 11, cr14, cr4, cr4, {0}
d00156e8:	eef17bc6 	vsqrt.f64	d23, d6
d00156ec:	d504fa10 	strle	pc, [r4, #-2576]	; 0xfffff5f0
d00156f0:	ee273c01 	cdp	12, 2, cr3, cr7, cr1, {0}
d00156f4:	429c7b05 	addsmi	r7, ip, #5120	; 0x1400
d00156f8:	ea24daf5 	b	0xd094c2d4
d00156fc:	ea6f73e4 	b	0xd1bf2694
d0015700:	459c0c01 	ldrmi	r0, [ip, #3073]	; 0xc01
d0015704:	2000dd16 	andcs	sp, r0, r6, lsl sp
d0015708:	8ff0e8bd 	svchi	0x00f0e8bd
d001570c:	7f9af5b4 	svcvc	0x009af5b4
d0015710:	ee87d0dc 	mcr	0, 4, sp, cr7, cr12, {6}
d0015714:	34017b06 	strcc	r7, [r1], #-2822	; 0xfffff4fa
d0015718:	7bc6eeb4 	blvc	0xcf1d11f0
d001571c:	fa10eef1 	blx	0xd04512e8
d0015720:	e7d3daf4 			; <UNDEFINED> instruction: 0xe7d3daf4
d0015724:	eeb02300 	cdp	3, 11, cr2, cr0, cr0, {0}
d0015728:	461c7b40 	ldrmi	r7, [ip], -r0, asr #22
d001572c:	0c01ea6f 			; <UNDEFINED> instruction: 0x0c01ea6f
d0015730:	dce8459c 	cfstr64le	mvdx4, [r8], #624	; 0x270
d0015734:	0b00f04f 	bleq	0xd0051878
d0015738:	5b04eeb2 	blpl	0xd0151208
d001573c:	0902ea41 	stmdbeq	r2, {r0, r6, r9, fp, sp, lr, pc}
d0015740:	38fff10c 	ldmcc	pc!, {r2, r3, r8, ip, sp, lr, pc}^	; <UNPREDICTABLE>
d0015744:	43f74658 	mvnsmi	r4, #88, 12	; 0x5800000
d0015748:	0a30f04f 	beq	0xd0c5188c
d001574c:	4b38ed9f 	blmi	0xd0e50dd0
d0015750:	0b40eeb5 	bleq	0xd105122c
d0015754:	fa10eef1 	blx	0xd0451320
d0015758:	42a3d030 	adcmi	sp, r3, #48	; 0x30
d001575c:	eefddc2e 	cdp	12, 15, cr13, cr13, cr14, {1}
d0015760:	f10b6bc7 			; <UNDEFINED> instruction: 0xf10b6bc7
d0015764:	ee160b01 	vnmls.f64	d0, d6, d1
d0015768:	ee161a90 	vmov	r1, s13
d001576c:	29092a90 	stmdbcs	r9, {r4, r7, r9, fp, sp}
d0015770:	2209bfa8 	andcs	fp, r9, #168, 30	; 0x2a0
d0015774:	0f11f1bb 	svceq	0x0011f1bb
d0015778:	72e2ea22 	rscvc	lr, r2, #139264	; 0x22000
d001577c:	2a90ee06 	bcs	0xce450f9c
d0015780:	6be6eeb8 	blvs	0xcf9d1268
d0015784:	7b46ee37 	blvc	0xd11d1068
d0015788:	7b05ee27 	blvc	0xd019102c
d001578c:	459cdc16 	ldrmi	sp, [ip, #3094]	; 0xc16
d0015790:	3230d018 	eorscc	sp, r0, #24
d0015794:	5432b2d2 	ldrtpl	fp, [r2], #-722	; 0xfffffd2e
d0015798:	3b013001 	blcc	0xd00617a4
d001579c:	d0b34543 	adcsle	r4, r3, r3, asr #10
d00157a0:	d1d51c59 	bicsle	r1, r5, r9, asr ip
d00157a4:	0f00f1b9 	svceq	0x0000f1b9
d00157a8:	eeb5d0d2 	mrc	0, 5, sp, cr5, cr2, {6}
d00157ac:	f04f0b40 			; <UNDEFINED> instruction: 0xf04f0b40
d00157b0:	5432022e 	ldrtpl	r0, [r2], #-558	; 0xfffffdd2
d00157b4:	eef13001 	cdp	0, 15, cr3, cr1, cr1, {0}
d00157b8:	d1cefa10 	bicle	pc, lr, r0, lsl sl	; <UNPREDICTABLE>
d00157bc:	d0ec459c 	smlalle	r4, ip, ip, r5
d00157c0:	e7e82230 			; <UNDEFINED> instruction: 0xe7e82230
d00157c4:	dd1e2905 	vldrle.16	s4, [lr, #-10]	; <UNPREDICTABLE>
d00157c8:	dd172800 	ldcle	8, cr2, [r7, #-0]
d00157cc:	0e00eb06 	vmlaeq.f64	d14, d0, d6
d00157d0:	f8124672 			; <UNDEFINED> instruction: 0xf8124672
d00157d4:	292e1d01 	stmdbcs	lr!, {r0, r8, sl, fp, ip}
d00157d8:	0502eb07 	streq	lr, [r2, #-2823]	; 0xfffff4f9
d00157dc:	2938d003 	ldmdbcs	r8!, {r0, r1, ip, lr, pc}
d00157e0:	f882d91f 			; <UNDEFINED> instruction: 0xf882d91f
d00157e4:	3501a000 	strcc	sl, [r1, #-0]
d00157e8:	2800d1f3 	stmdacs	r0, {r0, r1, r4, r5, r6, r7, r8, ip, lr, pc}
d00157ec:	4672dd06 	ldrbtmi	sp, [r2], -r6, lsl #26
d00157f0:	1c01f812 	stcne	8, cr15, [r1], {18}
d00157f4:	1901f802 	stmdbne	r1, {r1, fp, ip, sp, lr, pc}
d00157f8:	d1f94296 			; <UNDEFINED> instruction: 0xd1f94296
d00157fc:	0231f04f 	eorseq	pc, r1, #79	; 0x4f
d0015800:	70323001 	eorsvc	r3, r2, r1
d0015804:	d1c8e7c9 	bicle	lr, r8, r9, asr #15
d0015808:	7bc4eeb4 	blvc	0xcf1512e0
d001580c:	fa10eef1 	blx	0xd04513d8
d0015810:	2800dcda 	stmdacs	r0, {r1, r3, r4, r6, r7, sl, fp, ip, lr, pc}
d0015814:	1832d0c1 	ldmdane	r2!, {r0, r6, r7, ip, lr, pc}
d0015818:	2c01f812 	stccs	8, cr15, [r1], {18}
d001581c:	d5bc07d2 	ldrle	r0, [ip, #2002]!	; 0x7d2
d0015820:	3101e7d2 	ldrdcc	lr, [r1, -r2]
d0015824:	e7b87011 			; <UNDEFINED> instruction: 0xe7b87011
d0015828:	e77f4623 	ldrb	r4, [pc, -r3, lsr #12]!
d001582c:	8000f3af 	andhi	pc, r0, pc, lsr #7
d0015830:	812dea11 			; <UNDEFINED> instruction: 0x812dea11
d0015834:	3d719799 	ldclcc	7, cr9, [r1, #-612]!	; 0xfffffd9c

Disassembly of section .text.sb_f_exponent:

d0015838 <.text.sb_f_exponent>:
d0015838:	0b40eeb5 	bleq	0xd1051314
d001583c:	4ff0e92d 	svcmi	0x00f0e92d
d0015840:	fa10eef1 	blx	0xd045140c
d0015844:	d0344607 	eorsle	r4, r4, r7, lsl #12
d0015848:	6b04eeb2 	blvs	0xd0151318
d001584c:	0bc6eeb4 	bleq	0xcf1d1324
d0015850:	fa10eef1 	blx	0xd045141c
d0015854:	80cef2c0 	sbchi	pc, lr, r0, asr #5
d0015858:	7b40eeb0 	blvc	0xd1051320
d001585c:	e0022400 	and	r2, r2, r0, lsl #8
d0015860:	7f9af5b4 	svcvc	0x009af5b4
d0015864:	ee87d007 	cdp	0, 8, cr13, cr7, cr7, {0}
d0015868:	34017b06 	strcc	r7, [r1], #-2822	; 0xfffff4fa
d001586c:	7bc6eeb4 	blvc	0xcf1d1344
d0015870:	fa10eef1 	blx	0xd045143c
d0015874:	eeb7daf4 			; <UNDEFINED> instruction: 0xeeb7daf4
d0015878:	eeb46b00 	vmov.f64	d6, #64	; 0x3e000000  0.125
d001587c:	eef17bc6 	vsqrt.f64	d23, d6
d0015880:	d519fa10 	ldrle	pc, [r9, #-2576]	; 0xfffff5f0
d0015884:	5b04eeb2 	blpl	0xd0151354
d0015888:	70a1f46f 	adcvc	pc, r1, pc, ror #8
d001588c:	eeb4e004 	cdp	0, 11, cr14, cr4, cr4, {0}
d0015890:	eef17bc6 	vsqrt.f64	d23, d6
d0015894:	d50ffa10 	strle	pc, [pc, #-2576]	; 0xd0014e8c
d0015898:	ee273c01 	cdp	12, 2, cr3, cr7, cr1, {0}
d001589c:	42847b05 	addmi	r7, r4, #5120	; 0x1400
d00158a0:	f111daf5 			; <UNDEFINED> instruction: 0xf111daf5
d00158a4:	d50a0e01 	strle	r0, [sl, #-3585]	; 0xfffff1ff
d00158a8:	2102463e 	tstcs	r2, lr, lsr r6
d00158ac:	22002501 	andcs	r2, r0, #4194304	; 0x400000
d00158b0:	eeb0e062 	cdp	0, 11, cr14, cr0, cr2, {3}
d00158b4:	24007b40 	strcs	r7, [r0], #-2880	; 0xfffff4c0
d00158b8:	0e01f111 	mcreq	1, 0, pc, cr1, cr1, {0}	; <UNPREDICTABLE>
d00158bc:	2500d4f4 	strcs	sp, [r0, #-1268]	; 0xfffffb0c
d00158c0:	5b04eeb2 	blpl	0xd0151390
d00158c4:	0902ea41 	stmdbeq	r2, {r0, r6, r9, fp, sp, lr, pc}
d00158c8:	462a1c88 	strtmi	r1, [sl], -r8, lsl #25
d00158cc:	0807ea6f 	stmdaeq	r7, {r0, r1, r2, r3, r5, r6, r9, fp, sp, lr, pc}
d00158d0:	0a30f04f 	beq	0xd0c51a14
d00158d4:	0b2ef04f 	bleq	0xd0bd1a18
d00158d8:	4b49ed9f 	blmi	0xd1290f5c
d00158dc:	0b40eeb5 	bleq	0xd10513b8
d00158e0:	fa10eef1 	blx	0xd04514ac
d00158e4:	4575d114 	ldrbmi	sp, [r5, #-276]!	; 0xfffffeec
d00158e8:	2130d002 	teqcs	r0, r2
d00158ec:	320154b9 	andcc	r5, r1, #-1191182336	; 0xb9000000
d00158f0:	42853501 	addmi	r3, r5, #4194304	; 0x400000
d00158f4:	2d01d03d 	stccs	0, cr13, [r1, #-244]	; 0xffffff0c
d00158f8:	f1b9d1f0 			; <UNDEFINED> instruction: 0xf1b9d1f0
d00158fc:	d0ed0f00 	rscle	r0, sp, r0, lsl #30
d0015900:	0b40eeb5 	bleq	0xd10513dc
d0015904:	b002f807 	andlt	pc, r2, r7, lsl #16
d0015908:	eef13201 	cdp	2, 15, cr3, cr1, cr1, {0}
d001590c:	d0eafa10 	rscle	pc, sl, r0, lsl sl	; <UNPREDICTABLE>
d0015910:	6bc7eefd 	blvs	0xcf21150c
d0015914:	6a90ee16 	bvs	0xce451174
d0015918:	1a90ee16 	bne	0xce451178
d001591c:	bfa82e09 	svclt	0x00a82e09
d0015920:	45752109 	ldrbmi	r2, [r5, #-265]!	; 0xfffffef7
d0015924:	71e1ea21 	mvnvc	lr, r1, lsr #20
d0015928:	1a90ee06 	bne	0xce451148
d001592c:	6be6eeb8 	blvs	0xcf9d1414
d0015930:	7b46ee37 	blvc	0xd11d1214
d0015934:	7b05ee27 	blvc	0xd01911d8
d0015938:	3130d002 	teqcc	r0, r2
d001593c:	e7d5b2c9 	ldrb	fp, [r5, r9, asr #5]
d0015940:	dd462e05 	stclle	14, cr2, [r6, #-20]	; 0xffffffec
d0015944:	dd0d2a00 	vstrle	s4, [sp, #-0]
d0015948:	f81118b9 			; <UNDEFINED> instruction: 0xf81118b9
d001594c:	2e2e6d01 	cdpcs	13, 2, cr6, cr14, cr1, {0}
d0015950:	0c01eb08 			; <UNDEFINED> instruction: 0x0c01eb08
d0015954:	2e38d003 	cdpcs	0, 3, cr13, cr8, cr3, {0}
d0015958:	f881d949 			; <UNDEFINED> instruction: 0xf881d949
d001595c:	f1bca000 			; <UNDEFINED> instruction: 0xf1bca000
d0015960:	d1f23fff 	ldrshle	r3, [r2, #255]!	; 0xff
d0015964:	f04f3501 			; <UNDEFINED> instruction: 0xf04f3501
d0015968:	34010131 	strcc	r0, [r1], #-305	; 0xfffffecf
d001596c:	70394285 	eorsvc	r4, r9, r5, lsl #5
d0015970:	18bed1c1 	ldmne	lr!, {r0, r6, r7, r8, ip, lr, pc}
d0015974:	1c911c55 	ldcne	12, cr1, [r1], {85}	; 0x55
d0015978:	bf142b00 	svclt	0x00142b00
d001597c:	20652045 	rsbcs	r2, r5, r5, asr #32
d0015980:	70302c00 	eorsvc	r2, r0, r0, lsl #24
d0015984:	232dbfb4 			; <UNDEFINED> instruction: 0x232dbfb4
d0015988:	2c00232b 	stccs	3, cr2, [r0], {43}	; 0x2b
d001598c:	bfb8557b 	svclt	0x00b8557b
d0015990:	2c634264 	sfmcs	f4, 2, [r3], #-400	; 0xfffffe70
d0015994:	4b1cdd06 	blmi	0xd074cdb4
d0015998:	0304fba3 	movweq	pc, #19363	; 0x4ba3	; <UNPREDICTABLE>
d001599c:	3330095b 	teqcc	r0, #1490944	; 0x16c000
d00159a0:	1cd1547b 	cfldrdne	mvd5, [r1], {123}	; 0x7b
d00159a4:	187d4a19 	ldmdane	sp!, {r0, r3, r4, r9, fp, lr}^
d00159a8:	0304fba2 	movweq	pc, #19362	; 0x4ba2	; <UNPREDICTABLE>
d00159ac:	08db1c88 	ldmeq	fp, {r3, r7, sl, fp, ip}^
d00159b0:	6203fba2 	andvs	pc, r3, #165888	; 0x28800
d00159b4:	0683eb03 	streq	lr, [r3], r3, lsl #22
d00159b8:	eba408d2 	bl	0xce917d08
d00159bc:	eb020446 	bl	0xd0096adc
d00159c0:	34300282 	ldrtcc	r0, [r0], #-642	; 0xfffffd7e
d00159c4:	0342eba3 	movteq	lr, #11171	; 0x2ba3
d00159c8:	547b3330 	ldrbtpl	r3, [fp], #-816	; 0xfffffcd0
d00159cc:	e8bd706c 	pop	{r2, r3, r5, r6, ip, sp, lr}
d00159d0:	d18d8ff0 	strdle	r8, [sp, r0]
d00159d4:	7bc4eeb4 	blvc	0xcf1514ac
d00159d8:	fa10eef1 	blx	0xd04515a4
d00159dc:	2a00dcb2 	bcs	0xd004ccac
d00159e0:	18b9d086 	ldmne	r9!, {r1, r2, r7, ip, lr, pc}
d00159e4:	1c01f811 	stcne	8, cr15, [r1], {17}
d00159e8:	d58107c9 	strle	r0, [r1, #1993]	; 0x7c9
d00159ec:	3601e7aa 	strcc	lr, [r1], -sl, lsr #15
d00159f0:	e77d700e 	ldrb	r7, [sp, -lr]!
d00159f4:	7b40eeb0 	blvc	0xd10514bc
d00159f8:	e73c2400 	ldr	r2, [ip, -r0, lsl #8]!
d00159fc:	8000f3af 	andhi	pc, r0, pc, lsr #7
d0015a00:	812dea11 			; <UNDEFINED> instruction: 0x812dea11
d0015a04:	3d719799 	ldclcc	7, cr9, [r1, #-612]!	; 0xfffffd9c
d0015a08:	51eb851f 	mvnpl	r8, pc, lsl r5
d0015a0c:	cccccccd 	stclgt	12, cr12, [ip], {205}	; 0xcd

Disassembly of section .text.sb_flush.part.0:

d0015a10 <.text.sb_flush.part.0>:
d0015a10:	2090f8d0 			; <UNDEFINED> instruction: 0x2090f8d0
d0015a14:	4b07b16a 	blmi	0xd0201fc4
d0015a18:	0110f100 	tsteq	r0, r0, lsl #2	; <UNPREDICTABLE>
d0015a1c:	681b689b 	ldmdavs	fp, {r0, r1, r3, r4, r7, fp, sp, lr}
d0015a20:	685bb510 	ldmdavs	fp, {r4, r8, sl, ip, sp, pc}^
d0015a24:	20004604 	andcs	r4, r0, r4, lsl #12
d0015a28:	23004798 	movwcs	r4, #1944	; 0x798
d0015a2c:	3090f8c4 	addscc	pc, r0, r4, asr #17
d0015a30:	4770bd10 			; <UNDEFINED> instruction: 0x4770bd10
d0015a34:	2001f000 	andcs	pc, r1, r0

Disassembly of section .text.sb_char:

d0015a38 <.text.sb_char>:
d0015a38:	b51068c3 	ldrlt	r6, [r0, #-2243]	; 0xfffff73d
d0015a3c:	b1834604 	orrlt	r4, r3, r4, lsl #12
d0015a40:	3090f8d0 			; <UNDEFINED> instruction: 0x3090f8d0
d0015a44:	44031c5a 	strmi	r1, [r3], #-3162	; 0xfffff3a6
d0015a48:	f8c02a80 			; <UNDEFINED> instruction: 0xf8c02a80
d0015a4c:	74192090 	ldrvc	r2, [r9], #-144	; 0xffffff70
d0015a50:	68a3d013 	stmiavs	r3!, {r0, r1, r4, ip, lr, pc}
d0015a54:	4200f06f 	andmi	pc, r0, #111	; 0x6f
d0015a58:	d2014293 	andle	r4, r1, #805306377	; 0x30000009
d0015a5c:	60a33301 	adcvs	r3, r3, r1, lsl #6
d0015a60:	6800bd10 	stmdavs	r0, {r4, r8, sl, fp, ip, sp, pc}
d0015a64:	d0f42800 	rscsle	r2, r4, r0, lsl #16
d0015a68:	68a36862 	stmiavs	r3!, {r1, r5, r6, fp, sp, lr}
d0015a6c:	bf182a00 	svclt	0x00182a00
d0015a70:	42933a01 	addsmi	r3, r3, #4096	; 0x1000
d0015a74:	54c1d2ee 	strbpl	sp, [r1], #750	; 0x2ee
d0015a78:	f7ffe7eb 			; <UNDEFINED> instruction: 0xf7ffe7eb
d0015a7c:	68a3ffc9 	stmiavs	r3!, {r0, r3, r6, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0015a80:	bf00e7e8 	svclt	0x0000e7e8

Disassembly of section .text.sb_number:

d0015a98 <.text.sb_number>:
d0015a98:	4ff0e92d 	svcmi	0x00f0e92d
d0015a9c:	8b02ed2d 	blhi	0xd00d0f58
d0015aa0:	ee08b09b 	mcr	0, 0, fp, cr8, cr11, {4}
d0015aa4:	93070a10 	movwls	r0, #31248	; 0x7a10
d0015aa8:	92069b2b 	andls	r9, r6, #44032	; 0xac00
d0015aac:	d13e2b00 	teqle	lr, r0, lsl #22
d0015ab0:	e9dd4bbf 	ldmib	sp, {r0, r1, r2, r3, r4, r5, r7, r8, r9, fp, lr}^
d0015ab4:	447b1206 	ldrbtmi	r1, [fp], #-518	; 0xfffffdfa
d0015ab8:	460b9305 	strmi	r9, [fp], -r5, lsl #6
d0015abc:	d13e4313 	teqle	lr, r3, lsl r3
d0015ac0:	9a2a9b2a 	bls	0xd0abc770
d0015ac4:	bf183b00 	svclt	0x00183b00
d0015ac8:	2a002301 	bcs	0xd001e6d4
d0015acc:	9303d137 	movwls	sp, #12599	; 0x3137
d0015ad0:	2b009b27 	blcs	0xd003c774
d0015ad4:	9b28d179 	blls	0xd0a4a0c0
d0015ad8:	f1000759 			; <UNDEFINED> instruction: 0xf1000759
d0015adc:	ea4f8101 	b	0xd13f5ee8
d0015ae0:	9a2c0983 	bls	0xd0b180f4
d0015ae4:	1a40f3c9 	bne	0xd1052a10
d0015ae8:	0920f009 	stmdbeq	r0!, {r0, r3, ip, sp, lr, pc}
d0015aec:	2a004653 	bcs	0xd0027440
d0015af0:	9a26d072 	bls	0xd09c9cc0
d0015af4:	f0002a10 			; <UNDEFINED> instruction: 0xf0002a10
d0015af8:	9a2680f8 	bls	0xd09b5ee0
d0015afc:	f0002a02 			; <UNDEFINED> instruction: 0xf0002a02
d0015b00:	9a268144 	bls	0xd09b6018
d0015b04:	9a032a08 	bls	0xd00e032c
d0015b08:	8122f000 	msrhi	CPSR_x, r0
d0015b0c:	2600992a 	strcs	r9, [r0], -sl, lsr #18
d0015b10:	82a0f8df 	adchi	pc, r0, #14614528	; 0xdf0000
d0015b14:	44f84291 	ldrbtmi	r4, [r8], #657	; 0x291
d0015b18:	9a03dc69 	bls	0xd010ccc4
d0015b1c:	19942700 	ldmibne	r4, {r8, r9, sl, sp}
d0015b20:	44239a29 	strtmi	r9, [r3], #-2601	; 0xfffff5d7
d0015b24:	f0c04293 			; <UNDEFINED> instruction: 0xf0c04293
d0015b28:	463c80e8 	ldrtmi	r8, [ip], -r8, ror #1
d0015b2c:	4ba2e0e7 	blmi	0xce8cded0
d0015b30:	1206e9dd 	andne	lr, r6, #3620864	; 0x374000
d0015b34:	9305447b 	movwls	r4, #21627	; 0x547b
d0015b38:	4313460b 	tstmi	r3, #11534336	; 0xb00000
d0015b3c:	ab09d0c0 	blge	0xd0289e44
d0015b40:	26012200 	strcs	r2, [r1], -r0, lsl #4
d0015b44:	e9dd9304 	ldmib	sp, {r2, r8, r9, ip, pc}^
d0015b48:	469b3406 	ldrmi	r3, [fp], r6, lsl #8
d0015b4c:	46272300 	strtmi	r2, [r7], -r0, lsl #6
d0015b50:	9b269303 	blls	0xd09ba764
d0015b54:	e9cd4619 	stmib	sp, {r0, r3, r4, r9, sl, lr}^
d0015b58:	23001200 	movwcs	r1, #512	; 0x200
d0015b5c:	0ffa203f 	svceq	0x00fa203f
d0015b60:	b008f8cd 	andlt	pc, r8, sp, asr #17
d0015b64:	469a4699 			; <UNDEFINED> instruction: 0x469a4699
d0015b68:	99023801 	stmdbls	r2, {r0, fp, ip, sp}
d0015b6c:	0420f1c0 	strteq	pc, [r0], #-448	; 0xfffffe40
d0015b70:	0520f1a0 	streq	pc, [r0, #-416]!	; 0xfffffe60
d0015b74:	f1b040c1 			; <UNDEFINED> instruction: 0xf1b040c1
d0015b78:	fa073fff 	blx	0xd01e5b7c
d0015b7c:	fa27fe04 	blx	0xd0a15394
d0015b80:	fa26fc05 	blx	0xd09d4b9c
d0015b84:	fa06f404 	blx	0xd01d2b9c
d0015b88:	ea41f505 	b	0xd1092fa4
d0015b8c:	fa06010e 	blx	0xd0195fcc
d0015b90:	ea44f800 	b	0xd1153b98
d0015b94:	ea410405 	b	0xd1056bb0
d0015b98:	d072010c 	rsbsle	r0, r2, ip, lsl #2
d0015b9c:	f0011895 			; <UNDEFINED> instruction: 0xf0011895
d0015ba0:	eb430101 	bl	0xd10d5fac
d0015ba4:	ea410c03 	b	0xd1058bb8
d0015ba8:	46630205 	strbtmi	r0, [r3], -r5, lsl #4
d0015bac:	bc00e9dd 			; <UNDEFINED> instruction: 0xbc00e9dd
d0015bb0:	bf084563 	svclt	0x00084563
d0015bb4:	d3d7455a 	bicsle	r4, r7, #377487360	; 0x16800000
d0015bb8:	020bebb2 	andeq	lr, fp, #182272	; 0x2c800
d0015bbc:	0909ea48 	stmdbeq	r9, {r3, r6, r9, fp, sp, lr, pc}
d0015bc0:	0a0aea44 	beq	0xd02d04d8
d0015bc4:	030ceb63 	movweq	lr, #52067	; 0xcb63
d0015bc8:	2301e7ce 	movwcs	lr, #6094	; 0x17ce
d0015bcc:	092df04f 	pusheq	{r0, r1, r2, r3, r6, ip, sp, lr, pc}
d0015bd0:	9a2c469a 	bls	0xd0b27640
d0015bd4:	d18c2a00 	orrle	r2, ip, r0, lsl #20
d0015bd8:	f0129a28 			; <UNDEFINED> instruction: 0xf0129a28
d0015bdc:	d16a0610 	cmnle	sl, r0, lsl r6
d0015be0:	81d8f8df 	ldrsbhi	pc, [r8, #143]	; 0x8f	; <UNPREDICTABLE>
d0015be4:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d0015be8:	4291992a 	addsmi	r9, r1, #688128	; 0xa8000
d0015bec:	9903dd95 	stmdbls	r3, {r0, r2, r4, r7, r8, sl, fp, ip, lr, pc}
d0015bf0:	198a982a 	stmibne	sl, {r1, r3, r5, fp, ip, pc}
d0015bf4:	44131a47 	ldrmi	r1, [r3], #-2631	; 0xfffff5b9
d0015bf8:	443b9a29 	ldrtmi	r9, [fp], #-2601	; 0xfffff5d7
d0015bfc:	d87c429a 	ldmdale	ip!, {r1, r3, r4, r7, r9, lr}^
d0015c00:	24009b28 	strcs	r9, [r0], #-2856	; 0xfffff4d8
d0015c04:	0501f003 	streq	pc, [r1, #-3]
d0015c08:	0f00f1ba 	svceq	0x0000f1ba
d0015c0c:	b16ed14d 	cmnlt	lr, sp, asr #2
d0015c10:	1000f898 	mulne	r0, r8, r8
d0015c14:	0a10ee18 	beq	0xd045147c
d0015c18:	ff0ef7ff 			; <UNDEFINED> instruction: 0xff0ef7ff
d0015c1c:	d1052e02 	tstle	r5, r2, lsl #28
d0015c20:	1001f898 	mulne	r1, r8, r8
d0015c24:	0a10ee18 	beq	0xd045148c
d0015c28:	ff06f7ff 			; <UNDEFINED> instruction: 0xff06f7ff
d0015c2c:	b1471e7e 	hvclt	29166	; 0x71ee
d0015c30:	7a10ee18 	bvc	0xd0451498
d0015c34:	21303e01 	teqcs	r0, r1, lsl #28
d0015c38:	f7ff4638 			; <UNDEFINED> instruction: 0xf7ff4638
d0015c3c:	1c72fefd 	ldclne	14, cr15, [r2], #-1012	; 0xfffffc0c
d0015c40:	9b03d1f8 	blls	0xd010a428
d0015c44:	af09b163 	svcge	0x0009b163
d0015c48:	ee189b03 	vnmls.f64	d9, d8, d3
d0015c4c:	443b8a10 	ldrtmi	r8, [fp], #-2576	; 0xfffff5f0
d0015c50:	f816461e 			; <UNDEFINED> instruction: 0xf816461e
d0015c54:	46401d01 	strbmi	r1, [r0], -r1, lsl #26
d0015c58:	feeef7ff 	mcr2	7, 7, pc, cr14, cr15, {7}	; <UNPREDICTABLE>
d0015c5c:	d1f842b7 	ldrhle	r4, [r8, #39]!	; 0x27
d0015c60:	1e65b155 	mcrne	1, 3, fp, cr5, cr5, {2}
d0015c64:	ee18b144 	mnfem	f3, f4
d0015c68:	3d014a10 	vstrcc	s8, [r1, #-64]	; 0xffffffc0
d0015c6c:	46202120 	strtmi	r2, [r0], -r0, lsr #2
d0015c70:	fee2f7ff 	mcr2	7, 7, pc, cr2, cr15, {7}	; <UNPREDICTABLE>
d0015c74:	d1f81c6b 	mvnsle	r1, fp, ror #24
d0015c78:	ecbdb01b 	ldc	0, cr11, [sp], #108	; 0x6c
d0015c7c:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d0015c80:	99058ff0 	stmdbls	r5, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
d0015c84:	9903440a 	stmdbls	r3, {r1, r3, sl, lr}
d0015c88:	31017813 	tstcc	r1, r3, lsl r8
d0015c8c:	91039a04 	tstls	r3, r4, lsl #20
d0015c90:	3b01f802 	blcc	0xd0093ca0
d0015c94:	030aea59 	movweq	lr, #43609	; 0xaa59
d0015c98:	f43f9204 			; <UNDEFINED> instruction: 0xf43f9204
d0015c9c:	2940af19 	stmdbcs	r0, {r0, r3, r4, r8, r9, sl, fp, sp, pc}^
d0015ca0:	af16f63f 	svcge	0x0016f63f
d0015ca4:	465746cb 	ldrbmi	r4, [r7], -fp, asr #13
d0015ca8:	4649e757 			; <UNDEFINED> instruction: 0x4649e757
d0015cac:	0a10ee18 	beq	0xd0451514
d0015cb0:	fec2f7ff 	mcr2	7, 6, pc, cr2, cr15, {7}	; <UNPREDICTABLE>
d0015cb4:	e9dde7ab 	ldmib	sp, {r0, r1, r3, r5, r7, r8, r9, sl, sp, lr, pc}^
d0015cb8:	430a1206 	movwmi	r1, #41478	; 0xa206
d0015cbc:	af19f47f 	svcge	0x0019f47f
d0015cc0:	2a089a26 	bcs	0xd023c560
d0015cc4:	9a03d167 	bls	0xd010a268
d0015cc8:	d1642a00 	cmnle	r4, r0, lsl #20
d0015ccc:	21302201 	teqcs	r0, r1, lsl #4
d0015cd0:	80ecf8df 	ldrdhi	pc, [ip], #143	; 0x8f	; <UNPREDICTABLE>
d0015cd4:	44f89e2c 	ldrbtmi	r9, [r8], #3628	; 0xe2c
d0015cd8:	f88d9203 			; <UNDEFINED> instruction: 0xf88d9203
d0015cdc:	e7831024 	str	r1, [r3, r4, lsr #32]
d0015ce0:	f04f2301 			; <UNDEFINED> instruction: 0xf04f2301
d0015ce4:	469a092b 	ldrmi	r0, [sl], fp, lsr #18
d0015ce8:	9a2be773 	bls	0xd0b0fabc
d0015cec:	f8dfb352 			; <UNDEFINED> instruction: 0xf8dfb352
d0015cf0:	260280d4 			; <UNDEFINED> instruction: 0x260280d4
d0015cf4:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d0015cf8:	9a29e776 	bls	0xd0a8fad8
d0015cfc:	9b281ad4 	blls	0xd0a1c854
d0015d00:	0303f003 	movweq	pc, #12291	; 0x3003	; <UNPREDICTABLE>
d0015d04:	d1022b02 	tstle	r2, r2, lsl #22
d0015d08:	2b009b2a 	blcs	0xd003c9b8
d0015d0c:	9b28db33 	blls	0xd0a4c9e0
d0015d10:	0501f013 	streq	pc, [r1, #-19]	; 0xffffffed
d0015d14:	af78f47f 	svcge	0x0078f47f
d0015d18:	3bfff104 	blcc	0xd0012130
d0015d1c:	d0402c00 	suble	r2, r0, r0, lsl #24
d0015d20:	ee189402 	cfmuls	mvf9, mvf8, mvf2
d0015d24:	f10b4a10 			; <UNDEFINED> instruction: 0xf10b4a10
d0015d28:	21203bff 	strdcs	r3, [r0, -pc]!
d0015d2c:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0015d30:	f1bbfe83 			; <UNDEFINED> instruction: 0xf1bbfe83
d0015d34:	d1f63fff 	ldrshle	r3, [r6, #255]!	; 0xff
d0015d38:	f1ba9c02 			; <UNDEFINED> instruction: 0xf1ba9c02
d0015d3c:	f43f0f00 			; <UNDEFINED> instruction: 0xf43f0f00
d0015d40:	e7b2af66 	ldr	sl, [r2, r6, ror #30]!
d0015d44:	8080f8df 	ldrdhi	pc, [r0], pc	; <UNPREDICTABLE>
d0015d48:	9a032602 	bls	0xd00df558
d0015d4c:	e74b44f8 			; <UNDEFINED> instruction: 0xe74b44f8
d0015d50:	a91ab15a 	ldmdbge	sl, {r1, r3, r4, r6, r8, ip, sp, pc}
d0015d54:	f812188a 			; <UNDEFINED> instruction: 0xf812188a
d0015d58:	2a302c45 	bcs	0xd0c20e74
d0015d5c:	f8dfd105 			; <UNDEFINED> instruction: 0xf8dfd105
d0015d60:	2600806c 	strcs	r8, [r0], -ip, rrx
d0015d64:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d0015d68:	f8dfe73e 			; <UNDEFINED> instruction: 0xf8dfe73e
d0015d6c:	26018064 	strcs	r8, [r1], -r4, rrx
d0015d70:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d0015d74:	9b28e738 	blls	0xd0a4fa5c
d0015d78:	24004427 	strcs	r4, [r0], #-1063	; 0xfffffbd9
d0015d7c:	0501f003 	streq	pc, [r1, #-3]
d0015d80:	0f00f1ba 	svceq	0x0000f1ba
d0015d84:	af43f43f 	svcge	0x0043f43f
d0015d88:	f8dfe78f 			; <UNDEFINED> instruction: 0xf8dfe78f
d0015d8c:	46168048 	ldrmi	r8, [r6], -r8, asr #32
d0015d90:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d0015d94:	f8dfe728 			; <UNDEFINED> instruction: 0xf8dfe728
d0015d98:	26008040 	strcs	r8, [r0], -r0, asr #32
d0015d9c:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d0015da0:	4625e722 	strtmi	lr, [r5], -r2, lsr #14
d0015da4:	0f00f1ba 	svceq	0x0000f1ba
d0015da8:	af31f43f 	svcge	0x0031f43f
d0015dac:	bf00e77d 	svclt	0x0000e77d
d0015db0:	0000136a 	andeq	r1, r0, sl, ror #6
d0015db4:	ffffff6e 			; <UNDEFINED> instruction: 0xffffff6e
d0015db8:	000012d8 	ldrdeq	r1, [r0], -r8
d0015dbc:	fffffe9e 			; <UNDEFINED> instruction: 0xfffffe9e
d0015dc0:	fffffdae 			; <UNDEFINED> instruction: 0xfffffdae
d0015dc4:	fffffd8a 			; <UNDEFINED> instruction: 0xfffffd8a
d0015dc8:	fffffd3c 			; <UNDEFINED> instruction: 0xfffffd3c
d0015dcc:	fffffd1e 			; <UNDEFINED> instruction: 0xfffffd1e
d0015dd0:	fffffd1a 			; <UNDEFINED> instruction: 0xfffffd1a
d0015dd4:	fffffcfe 			; <UNDEFINED> instruction: 0xfffffcfe
d0015dd8:	fffffce6 			; <UNDEFINED> instruction: 0xfffffce6

Disassembly of section .text.sb_float:

d0015df4 <.text.sb_float>:
d0015df4:	4ff0e92d 	svcmi	0x00f0e92d
d0015df8:	bb10ec5c 	bllt	0xd0450f70
d0015dfc:	461eb0df 			; <UNDEFINED> instruction: 0x461eb0df
d0015e00:	73dcea5f 	bicsvc	lr, ip, #389120	; 0x5f000
d0015e04:	460446e0 	strmi	r4, [r4], -r0, ror #13
d0015e08:	4615468a 	ldrmi	r4, [r5], -sl, lsl #13
d0015e0c:	9a10ee10 	bls	0xd0451654
d0015e10:	ed8d9304 	stc	3, cr9, [sp, #16]
d0015e14:	d10a0b00 	tstle	sl, r0, lsl #22
d0015e18:	f1000750 			; <UNDEFINED> instruction: 0xf1000750
d0015e1c:	009380cb 	addseq	r8, r3, fp, asr #1
d0015e20:	1740f3c3 	strbne	pc, [r0, -r3, asr #7]	; <UNPREDICTABLE>
d0015e24:	0320f003 	wfieq
d0015e28:	930346bb 	movwls	r4, #14011	; 0x36bb
d0015e2c:	2701e003 	strcs	lr, [r1, -r3]
d0015e30:	46bb232d 	ldrtmi	r2, [fp], sp, lsr #6
d0015e34:	f04f9303 			; <UNDEFINED> instruction: 0xf04f9303
d0015e38:	21000c00 	tstcs	r0, r0, lsl #24
d0015e3c:	70fff240 	rscsvc	pc, pc, r0, asr #4
d0015e40:	520af3c8 	andpl	pc, sl, #200, 6	; 0x20000003
d0015e44:	f1aa458c 			; <UNDEFINED> instruction: 0xf1aa458c
d0015e48:	bf080e41 	svclt	0x00080e41
d0015e4c:	fa5f4282 	blx	0xd17e685c
d0015e50:	d03efe8e 	eorsle	pc, lr, lr, lsl #29
d0015e54:	2b099b68 	blcs	0xd027cbfc
d0015e58:	4afcdd4b 	bmi	0xcff4d38c
d0015e5c:	0918f10d 	ldmdbeq	r8, {r0, r2, r3, r8, ip, sp, lr, pc}
d0015e60:	237046e0 	cmncs	r0, #224, 12	; 0xe000000
d0015e64:	4649447a 			; <UNDEFINED> instruction: 0x4649447a
d0015e68:	3201203c 	andcc	r2, r1, #60	; 0x3c
d0015e6c:	4618e002 	ldrmi	lr, [r8], -r2
d0015e70:	3f01f812 	svccc	0x0001f812
d0015e74:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d0015e78:	0b01f801 	bleq	0xd0093e84
d0015e7c:	d1f62b00 	mvnsle	r2, r0, lsl #22
d0015e80:	020beb08 	andeq	lr, fp, #8, 22	; 0x2000
d0015e84:	42b22301 	adcsmi	r2, r2, #67108864	; 0x4000000
d0015e88:	8099f0c0 	addshi	pc, r9, r0, asr #1
d0015e8c:	f0052600 			; <UNDEFINED> instruction: 0xf0052600
d0015e90:	2a020203 	bcs	0xd00966a4
d0015e94:	2b00d102 	blcs	0xd004a2a4
d0015e98:	8093f040 	addshi	pc, r3, r0, asr #32
d0015e9c:	0501f015 	streq	pc, [r1, #-21]	; 0xffffffeb
d0015ea0:	80bcf040 	adcshi	pc, ip, r0, asr #32
d0015ea4:	b1361e75 	teqlt	r6, r5, ror lr
d0015ea8:	21203d01 			; <UNDEFINED> instruction: 0x21203d01
d0015eac:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0015eb0:	1c69fdc3 	stclne	13, cr15, [r9], #-780	; 0xfffffcf4
d0015eb4:	2f00d1f8 	svccs	0x0000d1f8
d0015eb8:	8091f000 	addshi	pc, r1, r0
d0015ebc:	46209903 	strtmi	r9, [r0], -r3, lsl #18
d0015ec0:	fdbaf7ff 	ldc2	7, cr15, [sl, #1020]!	; 0x3fc
d0015ec4:	0f00f1b8 	svceq	0x0000f1b8
d0015ec8:	808df040 	addhi	pc, sp, r0, asr #32
d0015ecc:	e8bdb05f 	pop	{r0, r1, r2, r3, r4, r6, ip, sp, pc}
d0015ed0:	464a8ff0 			; <UNDEFINED> instruction: 0x464a8ff0
d0015ed4:	0313f3c8 	tsteq	r3, #200, 6	; 0x20000003	; <UNPREDICTABLE>
d0015ed8:	f0404313 			; <UNDEFINED> instruction: 0xf0404313
d0015edc:	f1be80ae 			; <UNDEFINED> instruction: 0xf1be80ae
d0015ee0:	f2000f19 	vrecps.f32	d0, d0, d9
d0015ee4:	f8df80d4 			; <UNDEFINED> instruction: 0xf8df80d4
d0015ee8:	234ec368 	movtcs	ip, #58216	; 0xe368
d0015eec:	44fc2149 	ldrbtmi	r2, [ip], #329	; 0x149
d0015ef0:	9b04e0ab 	blls	0xd014e1a4
d0015ef4:	ed9db12b 	ldfd	f3, [sp, #172]	; 0xac
d0015ef8:	eeb17b00 	vmov.f64	d7, #16	; 0x40800000  4.0
d0015efc:	ed8d7b47 	vstr	d7, [sp, #284]	; 0x11c
d0015f00:	f1be7b00 			; <UNDEFINED> instruction: 0xf1be7b00
d0015f04:	f00a0f19 			; <UNDEFINED> instruction: 0xf00a0f19
d0015f08:	bf8c0adf 	svclt	0x008c0adf
d0015f0c:	23012300 	movwcs	r2, #4864	; 0x1300
d0015f10:	9b689304 	blls	0xd1a3ab28
d0015f14:	f2c02b00 	vqdmlsl.s<illegal width 8>	q9, d0, d0
d0015f18:	f1ba80c5 			; <UNDEFINED> instruction: 0xf1ba80c5
d0015f1c:	f0400f47 			; <UNDEFINED> instruction: 0xf0400f47
d0015f20:	9b6880c7 	blls	0xd1a36244
d0015f24:	bf082b00 	svclt	0x00082b00
d0015f28:	93682301 	cmnls	r8, #67108864	; 0x4000000
d0015f2c:	7b00ed9d 	blvc	0xd00515a8
d0015f30:	7b40eeb5 	blvc	0xd1051a0c
d0015f34:	fa10eef1 	blx	0xd0451b00
d0015f38:	80d0f000 	sbcshi	pc, r0, r0
d0015f3c:	6b04eeb2 	blvs	0xd0151a0c
d0015f40:	7bc6eeb4 	blvc	0xcf1d1a18
d0015f44:	fa10eef1 	blx	0xd0451b10
d0015f48:	8170f2c0 	cmnhi	r0, r0, asr #5	; <UNPREDICTABLE>
d0015f4c:	0a00f04f 	beq	0xd0052090
d0015f50:	f5bae003 			; <UNDEFINED> instruction: 0xf5bae003
d0015f54:	f0007f9a 			; <UNDEFINED> instruction: 0xf0007f9a
d0015f58:	ee87810f 	sins	f0, #10.0
d0015f5c:	f10a7b06 			; <UNDEFINED> instruction: 0xf10a7b06
d0015f60:	eeb40a01 	vmov.f32	s0, #65	; 0x3e080000  0.1328125
d0015f64:	eef17bc6 	vsqrt.f64	d23, d6
d0015f68:	daf2fa10 	ble	0xcfcd47b0
d0015f6c:	6b00eeb7 	blvs	0xd0051a50
d0015f70:	7bc6eeb4 	blvc	0xcf1d1a48
d0015f74:	fa10eef1 	blx	0xd0451b40
d0015f78:	eeb2d511 	mrc	5, 5, sp, cr2, cr1, {0}
d0015f7c:	eeb75b04 	vmov.f64	d5, #116	; 0x3fa00000  1.250
d0015f80:	e0036b00 	and	r6, r3, r0, lsl #22
d0015f84:	7fa2f51a 	svcvc	0x00a2f51a
d0015f88:	80fef000 	rscshi	pc, lr, r0
d0015f8c:	7b05ee27 	blvc	0xd0191830
d0015f90:	3afff10a 	bcc	0xd00123c0
d0015f94:	7bc6eeb4 	blvc	0xcf1d1a6c
d0015f98:	fa10eef1 	blx	0xd0451b64
d0015f9c:	9b68d4f2 	blls	0xd1a4b36c
d0015fa0:	f3404553 	vqrshl.u8	q10, <illegal reg q1.5>, q0
d0015fa4:	f11a80f1 			; <UNDEFINED> instruction: 0xf11a80f1
d0015fa8:	f2c00f04 			; <UNDEFINED> instruction: 0xf2c00f04
d0015fac:	f10a80ed 			; <UNDEFINED> instruction: 0xf10a80ed
d0015fb0:	e0960101 	adds	r0, r6, r1, lsl #2
d0015fb4:	232b2701 			; <UNDEFINED> instruction: 0x232b2701
d0015fb8:	930346bb 	movwls	r4, #14011	; 0x36bb
d0015fbc:	1ab6e73b 	bne	0xcedcfcb0
d0015fc0:	f005e765 			; <UNDEFINED> instruction: 0xf005e765
d0015fc4:	2f000501 	svccs	0x00000501
d0015fc8:	bb8dd167 	bllt	0xce38a56c
d0015fcc:	b1361e75 	teqlt	r6, r5, ror lr
d0015fd0:	21303d01 	teqcs	r0, r1, lsl #26
d0015fd4:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0015fd8:	1c6afd2f 	stclne	13, cr15, [sl], #-188	; 0xffffff44
d0015fdc:	f1b8d1f8 			; <UNDEFINED> instruction: 0xf1b8d1f8
d0015fe0:	f43f0f00 			; <UNDEFINED> instruction: 0xf43f0f00
d0015fe4:	2500af73 	strcs	sl, [r0, #-3955]	; 0xfffff08d
d0015fe8:	37012700 	strcc	r2, [r1, -r0, lsl #14]
d0015fec:	1b01f819 	blne	0xd0094058
d0015ff0:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0015ff4:	4547fd21 	strbmi	pc, [r7, #-3361]	; 0xfffff2df	; <UNPREDICTABLE>
d0015ff8:	2d00d3f7 	stccs	3, cr13, [r0, #-988]	; 0xfffffc24
d0015ffc:	af66f43f 	svcge	0x0066f43f
d0016000:	2e001e75 	mcrcs	14, 0, r1, cr0, cr5, {3}
d0016004:	af62f43f 	svcge	0x0062f43f
d0016008:	21203d01 			; <UNDEFINED> instruction: 0x21203d01
d001600c:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0016010:	1c6bfd13 	stclne	13, cr15, [fp], #-76	; 0xffffffb4
d0016014:	b05fd1f8 	ldrshlt	sp, [pc], #-24	; <UNPREDICTABLE>
d0016018:	8ff0e8bd 	svchi	0x00f0e8bd
d001601c:	f1b8b927 			; <UNDEFINED> instruction: 0xf1b8b927
d0016020:	d1e10f00 	mvnle	r0, r0, lsl #30
d0016024:	461ee7ec 	ldrmi	lr, [lr], -ip, ror #15
d0016028:	46209903 	strtmi	r9, [r0], -r3, lsl #18
d001602c:	fd04f7ff 	stc2	7, cr15, [r4, #-1020]	; 0xfffffc04
d0016030:	0f00f1b8 	svceq	0x0000f1b8
d0016034:	2501d0e4 	strcs	sp, [r1, #-228]	; 0xffffff1c
d0016038:	f1bee7d6 			; <UNDEFINED> instruction: 0xf1bee7d6
d001603c:	d9470f19 	stmdble	r7, {r0, r3, r4, r8, r9, sl, fp}^
d0016040:	c210f8df 	andsgt	pc, r0, #14614528	; 0xdf0000
d0016044:	216e2361 	cmncs	lr, r1, ror #6
d0016048:	f10d44fc 			; <UNDEFINED> instruction: 0xf10d44fc
d001604c:	f10c0918 			; <UNDEFINED> instruction: 0xf10c0918
d0016050:	ea6f0202 	b	0xd1bd6860
d0016054:	46480c0c 	strbmi	r0, [r8], -ip, lsl #24
d0016058:	f812e001 			; <UNDEFINED> instruction: 0xf812e001
d001605c:	f8003b01 			; <UNDEFINED> instruction: 0xf8003b01
d0016060:	eb0c1b01 	bl	0xd031cc6c
d0016064:	46190802 	ldrmi	r0, [r9], -r2, lsl #16
d0016068:	d1f62b00 	mvnsle	r2, r0, lsl #22
d001606c:	020beb08 	andeq	lr, fp, #8, 22	; 0x2000
d0016070:	d8a44296 	stmiale	r4!, {r1, r2, r4, r7, r9, lr}
d0016074:	0601f015 			; <UNDEFINED> instruction: 0x0601f015
d0016078:	af1df43f 	svcge	0x001df43f
d001607c:	d1d22f00 	bicsle	r2, r2, r0, lsl #30
d0016080:	0f00f1b8 	svceq	0x0000f1b8
d0016084:	af22f43f 	svcge	0x0022f43f
d0016088:	463e4635 			; <UNDEFINED> instruction: 0x463e4635
d001608c:	f8dfe7ac 			; <UNDEFINED> instruction: 0xf8dfe7ac
d0016090:	236ec1c8 	cmncs	lr, #200, 2	; 0x32
d0016094:	44fc2169 	ldrbtmi	r2, [ip], #361	; 0x169
d0016098:	9903e7d7 	stmdbls	r3, {r0, r1, r2, r4, r6, r7, r8, r9, sl, sp, lr, pc}
d001609c:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d00160a0:	e792fccb 	ldr	pc, [r2, fp, asr #25]
d00160a4:	f1ba2306 			; <UNDEFINED> instruction: 0xf1ba2306
d00160a8:	93680f47 	cmnls	r8, #284	; 0x11c
d00160ac:	af3ef43f 	svcge	0x003ef43f
d00160b0:	0f45f1ba 	svceq	0x0045f1ba
d00160b4:	0918f10d 	ldmdbeq	r8, {r0, r2, r3, r8, ip, sp, lr, pc}
d00160b8:	9b04d154 	blls	0xd014a610
d00160bc:	0210f005 	andseq	pc, r0, #5
d00160c0:	46489968 	strbmi	r9, [r8], -r8, ror #18
d00160c4:	0b00ed9d 	bleq	0xd0051740
d00160c8:	fbb6f7ff 	blx	0xcedd40ce
d00160cc:	e6d74680 	ldrb	r4, [r7], r0, lsl #13
d00160d0:	c188f8df 	ldrdgt	pc, [r8, pc]
d00160d4:	214e2341 	cmpcs	lr, r1, asr #6
d00160d8:	e7b644fc 			; <UNDEFINED> instruction: 0xe7b644fc
d00160dc:	f04f2101 			; <UNDEFINED> instruction: 0xf04f2101
d00160e0:	9b680a00 	blls	0xd1a188e8
d00160e4:	0918f10d 	ldmdbeq	r8, {r0, r2, r3, r8, ip, sp, lr, pc}
d00160e8:	0210f005 	andseq	pc, r0, #5
d00160ec:	46481a59 			; <UNDEFINED> instruction: 0x46481a59
d00160f0:	ed9d9205 	lfm	f1, 1, [sp, #20]
d00160f4:	f7ff0b00 			; <UNDEFINED> instruction: 0xf7ff0b00
d00160f8:	4680fad7 	pkhtbmi	pc, r0, r7, asr #21	; <UNPREDICTABLE>
d00160fc:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0016100:	4649aebf 			; <UNDEFINED> instruction: 0x4649aebf
d0016104:	9a052300 	bls	0xd015ed0c
d0016108:	3301e003 	movwcc	lr, #4099	; 0x1003
d001610c:	f0004598 			; <UNDEFINED> instruction: 0xf0004598
d0016110:	f8118086 			; <UNDEFINED> instruction: 0xf8118086
d0016114:	282e0b01 	stmdacs	lr!, {r0, r8, r9, fp}
d0016118:	f1bad1f7 			; <UNDEFINED> instruction: 0xf1bad1f7
d001611c:	db020f00 	blle	0xd0099d24
d0016120:	42999968 	addsmi	r9, r9, #104, 18	; 0x1a0000
d0016124:	2a00d334 	bcs	0xd004adfc
d0016128:	aeaaf47f 	mcrge	4, 5, pc, cr10, cr15, {3}	; <UNPREDICTABLE>
d001612c:	e002464b 	and	r4, r2, fp, asr #12
d0016130:	f43f4590 			; <UNDEFINED> instruction: 0xf43f4590
d0016134:	f813aea5 			; <UNDEFINED> instruction: 0xf813aea5
d0016138:	32011b01 	andcc	r1, r1, #1024	; 0x400
d001613c:	d1f7292e 	mvnsle	r2, lr, lsr #18
d0016140:	0308eb09 	movweq	lr, #35593	; 0x8b09
d0016144:	f813e005 			; <UNDEFINED> instruction: 0xf813e005
d0016148:	29301d01 	ldmdbcs	r0!, {r0, r8, sl, fp, ip}
d001614c:	ae98f47f 	mrcge	4, 4, APSR_nzcv, cr8, cr15, {3}
d0016150:	45904680 	ldrmi	r4, [r0, #1664]	; 0x680
d0016154:	30fff108 	rscscc	pc, pc, r8, lsl #2
d0016158:	f47fd8f5 			; <UNDEFINED> instruction: 0xf47fd8f5
d001615c:	f108ae91 			; <UNDEFINED> instruction: 0xf108ae91
d0016160:	e68d38ff 			; <UNDEFINED> instruction: 0xe68d38ff
d0016164:	0b00ed9d 	bleq	0xd00517e0
d0016168:	f0059968 			; <UNDEFINED> instruction: 0xf0059968
d001616c:	46480210 			; <UNDEFINED> instruction: 0x46480210
d0016170:	fa9af7ff 	blx	0xce6d4174
d0016174:	e6834680 	str	r4, [r3], r0, lsl #13
d0016178:	6b00eeb7 	blvs	0xd0051c5c
d001617c:	7bc6eeb4 	blvc	0xcf1d1c54
d0016180:	fa10eef1 	blx	0xd0451d4c
d0016184:	aef9f53f 	mrcge	5, 7, APSR_nzcv, cr9, cr15, {1}
d0016188:	0210f005 	andseq	pc, r0, #5
d001618c:	0918f10d 	ldmdbeq	r8, {r0, r2, r3, r8, ip, sp, lr, pc}
d0016190:	46489968 	strbmi	r9, [r8], -r8, ror #18
d0016194:	39019b04 	stmdbcc	r1, {r2, r8, r9, fp, ip, pc}
d0016198:	ed9d9204 	lfm	f1, 1, [sp, #16]
d001619c:	f7ff0b00 			; <UNDEFINED> instruction: 0xf7ff0b00
d00161a0:	9a04fb4b 	bls	0xd0154ed4
d00161a4:	2a004680 	bcs	0xd0027bac
d00161a8:	ae6af47f 	mcrge	4, 3, pc, cr10, cr15, {3}	; <UNPREDICTABLE>
d00161ac:	46424448 	strbmi	r4, [r2], -r8, asr #8
d00161b0:	461ae000 	ldrmi	lr, [sl], -r0
d00161b4:	2a001e53 	bcs	0xd001db08
d00161b8:	ae62f43f 	mcrge	4, 3, pc, cr2, cr15, {1}	; <UNPREDICTABLE>
d00161bc:	1d01f810 	stcne	8, cr15, [r1, #-64]	; 0xffffffc0
d00161c0:	0cdff001 	ldcleq	0, cr15, [pc], {1}
d00161c4:	0f45f1bc 	svceq	0x0045f1bc
d00161c8:	eb09d1f3 	bl	0xd028a99c
d00161cc:	46180c03 	ldrmi	r0, [r8], -r3, lsl #24
d00161d0:	f81ce005 			; <UNDEFINED> instruction: 0xf81ce005
d00161d4:	f1baad01 			; <UNDEFINED> instruction: 0xf1baad01
d00161d8:	d1220f30 			; <UNDEFINED> instruction: 0xd1220f30
d00161dc:	f1004670 			; <UNDEFINED> instruction: 0xf1004670
d00161e0:	28003eff 	stmdacs	r0, {r0, r1, r2, r3, r4, r5, r6, r7, r9, sl, fp, ip, sp}
d00161e4:	4543d1f5 	strbmi	sp, [r3, #-501]	; 0xfffffe0b
d00161e8:	f1c2d212 			; <UNDEFINED> instruction: 0xf1c2d212
d00161ec:	eb090a01 	bl	0xd02589f8
d00161f0:	f10d0c03 			; <UNDEFINED> instruction: 0xf10d0c03
d00161f4:	44820e17 	strmi	r0, [r2], #3607	; 0xe17
d00161f8:	445344c6 	ldrbmi	r4, [r3], #-1222	; 0xfffffb3a
d00161fc:	3b0144d6 	blcc	0xd006755c
d0016200:	e001444b 	and	r4, r1, fp, asr #8
d0016204:	1f01f81c 	svcne	0x0001f81c
d0016208:	1f01f803 	svcne	0x0001f803
d001620c:	d1f94573 	mvnsle	r4, r3, ror r5
d0016210:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d0016214:	0202eba8 	andeq	lr, r2, #168, 22	; 0x2a000
d0016218:	0802eb00 	stmdaeq	r2, {r8, r9, fp, sp, lr, pc}
d001621c:	4643e630 			; <UNDEFINED> instruction: 0x4643e630
d0016220:	f1bae77b 			; <UNDEFINED> instruction: 0xf1bae77b
d0016224:	bf080f2e 	svclt	0x00080f2e
d0016228:	e7dc4670 			; <UNDEFINED> instruction: 0xe7dc4670
d001622c:	7b00eeb7 	blvc	0xd0051d10
d0016230:	6b00ed9d 	blvs	0xd00518ac
d0016234:	6bc7eeb4 	blvs	0xcf211d0c
d0016238:	fa10eef1 	blx	0xd0451e04
d001623c:	af4ef57f 	svcge	0x004ef57f
d0016240:	0a00f04f 	beq	0xd0052384
d0016244:	7b00ed9d 	blvc	0xd00518c0
d0016248:	bf00e697 	svclt	0x0000e697
d001624c:	ffffff84 			; <UNDEFINED> instruction: 0xffffff84
d0016250:	fffffeee 			; <UNDEFINED> instruction: 0xfffffeee
d0016254:	fffffd90 			; <UNDEFINED> instruction: 0xfffffd90
d0016258:	fffffd4e 			; <UNDEFINED> instruction: 0xfffffd4e
d001625c:	fffffd08 			; <UNDEFINED> instruction: 0xfffffd08

Disassembly of section .text.sb_format.part.0:

d0016290 <.text.sb_format.part.0>:
d0016290:	4ff0e92d 	svcmi	0x00f0e92d
d0016294:	78094688 	stmdavc	r9, {r3, r7, r9, sl, lr}
d0016298:	4683b0a7 	strmi	fp, [r3], r7, lsr #1
d001629c:	f0002900 			; <UNDEFINED> instruction: 0xf0002900
d00162a0:	4bfa80b3 	blmi	0xcfeb6574
d00162a4:	f8df4691 			; <UNDEFINED> instruction: 0xf8df4691
d00162a8:	447ba3e8 	ldrbtmi	sl, [fp], #-1000	; 0xfffffc18
d00162ac:	4bf99308 	blmi	0xcfe7aed4
d00162b0:	9309447b 	movwls	r4, #38011	; 0x947b
d00162b4:	f0402925 			; <UNDEFINED> instruction: 0xf0402925
d00162b8:	f89880fd 			; <UNDEFINED> instruction: 0xf89880fd
d00162bc:	2c254001 	stccs	0, cr4, [r5], #-4
d00162c0:	80fef000 	rscshi	pc, lr, r0
d00162c4:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d00162c8:	f1a42600 			; <UNDEFINED> instruction: 0xf1a42600
d00162cc:	2b100320 	blcs	0xd0416f54
d00162d0:	e8dfd80a 	ldm	pc, {r1, r3, fp, ip, lr, pc}^	; <UNPREDICTABLE>
d00162d4:	0978f003 	ldmdbeq	r8!, {r0, r1, ip, sp, lr, pc}^
d00162d8:	09097509 	stmdbeq	r9, {r0, r3, r8, sl, ip, sp, lr}
d00162dc:	09090909 	stmdbeq	r9, {r0, r3, r8, fp}
d00162e0:	6f097209 	svcvs	0x00097209
d00162e4:	006a0909 	rsbeq	r0, sl, r9, lsl #18
d00162e8:	f0402c2a 			; <UNDEFINED> instruction: 0xf0402c2a
d00162ec:	f8d980ef 			; <UNDEFINED> instruction: 0xf8d980ef
d00162f0:	f1083000 			; <UNDEFINED> instruction: 0xf1083000
d00162f4:	681d0101 	ldmdavs	sp, {r0, r8}
d00162f8:	2d001d1a 	stccs	13, cr1, [r0, #-104]	; 0xffffff98
d00162fc:	2000f8c9 	andcs	pc, r0, r9, asr #17
d0016300:	8122f2c0 	smlawthi	r2, r0, r2, pc	; <UNPREDICTABLE>
d0016304:	5f00f5b5 	svcpl	0x0000f5b5
d0016308:	4001f898 	mulmi	r1, r8, r8
d001630c:	f44fbf28 			; <UNDEFINED> instruction: 0xf44fbf28
d0016310:	2c2e5500 	cfstr32cs	mvfx5, [lr], #-0
d0016314:	80fbf000 	rscshi	pc, fp, r0
d0016318:	37fff04f 	ldrbcc	pc, [pc, pc, asr #32]!	; <UNPREDICTABLE>
d001631c:	f0002c68 			; <UNDEFINED> instruction: 0xf0002c68
d0016320:	2c6c810d 	stfcsp	f0, [ip], #-52	; 0xffffffcc
d0016324:	811ef000 	tsthi	lr, r0	; <UNPREDICTABLE>
d0016328:	f0002c7a 			; <UNDEFINED> instruction: 0xf0002c7a
d001632c:	2c748122 	ldfcsp	f0, [r4], #-136	; 0xffffff78
d0016330:	8161f000 	msrhi	SPSR_c, r0
d0016334:	f0002c6a 			; <UNDEFINED> instruction: 0xf0002c6a
d0016338:	230081b3 	movwcs	r8, #435	; 0x1b3
d001633c:	d0632c00 	rsble	r2, r3, r0, lsl #24
d0016340:	f1012c64 			; <UNDEFINED> instruction: 0xf1012c64
d0016344:	d07d0801 	rsbsle	r0, sp, r1, lsl #16
d0016348:	d07b2c69 	rsbsle	r2, fp, r9, ror #24
d001634c:	0262f1a4 	rsbeq	pc, r2, #164, 2	; 0x29
d0016350:	01dff004 	bicseq	pc, pc, r4
d0016354:	f1a1b2d2 			; <UNDEFINED> instruction: 0xf1a1b2d2
d0016358:	2a130c58 	bcs	0xd04d94c0
d001635c:	fc8cfabc 	stc2	10, cr15, [ip], {188}	; 0xbc	; <UNPREDICTABLE>
d0016360:	1c5cea4f 	mrrcne	10, 4, lr, ip, cr15
d0016364:	48c8d806 	stmiami	r8, {r1, r2, fp, ip, lr, pc}^
d0016368:	f202fa20 	vpmax.s8	d15, d2, d16
d001636c:	0201f002 	andeq	pc, r1, #2
d0016370:	0c02ea4c 			; <UNDEFINED> instruction: 0x0c02ea4c
d0016374:	0f00f1bc 	svceq	0x0000f1bc
d0016378:	816cf000 	msrhi	SPSR_fs, r0
d001637c:	f0002c6f 			; <UNDEFINED> instruction: 0xf0002c6f
d0016380:	2958811b 	ldmdbcs	r8, {r0, r1, r3, r4, r8, pc}^
d0016384:	811af000 	tsthi	sl, r0	; <UNPREDICTABLE>
d0016388:	bf0c2c62 	svclt	0x000c2c62
d001638c:	210a2102 	tstcs	sl, r2, lsl #2
d0016390:	2b063b01 	blcs	0xd01a4f9c
d0016394:	84fdf200 	ldrbthi	pc, [sp], #512	; 0x200	; <UNPREDICTABLE>
d0016398:	f013e8df 			; <UNDEFINED> instruction: 0xf013e8df
d001639c:	0143014b 	cmpeq	r3, fp, asr #2
d00163a0:	00480018 	subeq	r0, r8, r8, lsl r0
d00163a4:	00180018 	andseq	r0, r8, r8, lsl r0
d00163a8:	f0460048 			; <UNDEFINED> instruction: 0xf0460048
d00163ac:	f8180602 			; <UNDEFINED> instruction: 0xf8180602
d00163b0:	e78a4f01 	str	r4, [sl, r1, lsl #30]
d00163b4:	0601f046 	streq	pc, [r1], -r6, asr #32
d00163b8:	f046e7f9 			; <UNDEFINED> instruction: 0xf046e7f9
d00163bc:	e7f60604 	ldrb	r0, [r6, r4, lsl #12]!
d00163c0:	0610f046 	ldreq	pc, [r0], -r6, asr #32
d00163c4:	f046e7f3 			; <UNDEFINED> instruction: 0xf046e7f3
d00163c8:	e7f00608 	ldrb	r0, [r0, r8, lsl #12]!
d00163cc:	3000f8d9 	ldrdcc	pc, [r0], -r9
d00163d0:	681a1d18 	ldmdavs	sl, {r3, r4, r8, sl, fp, ip}
d00163d4:	f8c92300 			; <UNDEFINED> instruction: 0xf8c92300
d00163d8:	f1a40000 			; <UNDEFINED> instruction: 0xf1a40000
d00163dc:	f0260058 			; <UNDEFINED> instruction: 0xf0260058
d00163e0:	2400060c 	strcs	r0, [r0], #-1548	; 0xfffff9f4
d00163e4:	fab09704 	blx	0xcec3bffc
d00163e8:	9602f080 	strls	pc, [r2], -r0, lsl #1
d00163ec:	09409503 	stmdbeq	r0, {r0, r1, r8, sl, ip, pc}^
d00163f0:	94069100 	strls	r9, [r6], #-256	; 0xffffff00
d00163f4:	46589005 	ldrbmi	r9, [r8], -r5
d00163f8:	f7ff9401 			; <UNDEFINED> instruction: 0xf7ff9401
d00163fc:	f898fb4d 			; <UNDEFINED> instruction: 0xf898fb4d
d0016400:	29001000 	stmdbcs	r0, {ip}
d0016404:	af56f47f 	svcge	0x0056f47f
d0016408:	300cf8db 	ldrdcc	pc, [ip], -fp
d001640c:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d0016410:	465880db 			; <UNDEFINED> instruction: 0x465880db
d0016414:	fafcf7ff 	blx	0xcff54418
d0016418:	300cf8db 	ldrdcc	pc, [ip], -fp
d001641c:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d0016420:	f8db80d3 			; <UNDEFINED> instruction: 0xf8db80d3
d0016424:	b0270008 	eorlt	r0, r7, r8
d0016428:	8ff0e8bd 	svchi	0x00f0e8bd
d001642c:	3000f8d9 	ldrdcc	pc, [r0], -r9
d0016430:	f0233307 			; <UNDEFINED> instruction: 0xf0233307
d0016434:	f1030307 			; <UNDEFINED> instruction: 0xf1030307
d0016438:	f8c90208 			; <UNDEFINED> instruction: 0xf8c90208
d001643c:	e9d32000 	ldmib	r3, {sp}^
d0016440:	e7ca2300 	strb	r2, [sl, r0, lsl #6]
d0016444:	2b063b01 	blcs	0xd01a5050
d0016448:	84acf200 	strthi	pc, [ip], #512	; 0x200
d001644c:	f003e8df 			; <UNDEFINED> instruction: 0xf003e8df
d0016450:	1f04d7e0 	svcne	0x0004d7e0
d0016454:	001f0404 	andseq	r0, pc, r4, lsl #8
d0016458:	3000f8d9 	ldrdcc	pc, [r0], -r9
d001645c:	1d1a6818 	ldcne	8, cr6, [sl, #-96]	; 0xffffffa0
d0016460:	f8c917c1 			; <UNDEFINED> instruction: 0xf8c917c1
d0016464:	28002000 	stmdacs	r0, {sp}
d0016468:	0300f171 	movweq	pc, #369	; 0x171	; <UNPREDICTABLE>
d001646c:	4602db1e 			; <UNDEFINED> instruction: 0x4602db1e
d0016470:	0fc8460b 	svceq	0x00c8460b
d0016474:	2100240a 	tstcs	r0, sl, lsl #8
d0016478:	90019704 	andls	r9, r1, r4, lsl #14
d001647c:	95034658 	strls	r4, [r3, #-1624]	; 0xfffff9a8
d0016480:	91069602 	tstls	r6, r2, lsl #12
d0016484:	94009105 	strls	r9, [r0], #-261	; 0xfffffefb
d0016488:	fb06f7ff 	blx	0xd01d448e
d001648c:	f8d9e7b7 			; <UNDEFINED> instruction: 0xf8d9e7b7
d0016490:	33073000 	movwcc	r3, #28672	; 0x7000
d0016494:	0307f023 	movweq	pc, #28707	; 0x7023	; <UNPREDICTABLE>
d0016498:	0100e9d3 	ldrdeq	lr, [r0, -r3]
d001649c:	0208f103 	andeq	pc, r8, #-1073741824	; 0xc0000000
d00164a0:	f8c92800 			; <UNDEFINED> instruction: 0xf8c92800
d00164a4:	f1712000 			; <UNDEFINED> instruction: 0xf1712000
d00164a8:	dae00300 	ble	0xcf8170b0
d00164ac:	eb614242 	bl	0xd1866dbc
d00164b0:	e7de0341 	ldrb	r0, [lr, r1, asr #6]
d00164b4:	f1084658 			; <UNDEFINED> instruction: 0xf1084658
d00164b8:	f7ff0801 			; <UNDEFINED> instruction: 0xf7ff0801
d00164bc:	e79efabd 			; <UNDEFINED> instruction: 0xe79efabd
d00164c0:	f1084658 			; <UNDEFINED> instruction: 0xf1084658
d00164c4:	f7ff0802 			; <UNDEFINED> instruction: 0xf7ff0802
d00164c8:	e798fab7 			; <UNDEFINED> instruction: 0xe798fab7
d00164cc:	0230f1a4 	eorseq	pc, r0, #164, 2	; 0x29
d00164d0:	2b09b2d3 	blcs	0xd0283024
d00164d4:	80e8f200 	rschi	pc, r8, r0, lsl #4
d00164d8:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d00164dc:	f5c22500 			; <UNDEFINED> instruction: 0xf5c22500
d00164e0:	46415300 	strbmi	r5, [r1], -r0, lsl #6
d00164e4:	0085eb05 	addeq	lr, r5, r5, lsl #22
d00164e8:	4303fbaa 	movwmi	pc, #15274	; 0x3baa	; <UNPREDICTABLE>
d00164ec:	4b01f818 	blmi	0xd0094554
d00164f0:	0fd3ebb5 	svceq	0x00d3ebb5
d00164f4:	0540eb02 	strbeq	lr, [r0, #-2818]	; 0xfffff4fe
d00164f8:	0230f1a4 	eorseq	pc, r0, #164, 2	; 0x29
d00164fc:	f44fbf88 			; <UNDEFINED> instruction: 0xf44fbf88
d0016500:	b2d35500 	sbcslt	r5, r3, #0, 10
d0016504:	d9ea2b09 	stmible	sl!, {r0, r3, r8, r9, fp, sp}^
d0016508:	f47f2c2e 			; <UNDEFINED> instruction: 0xf47f2c2e
d001650c:	784caf05 	stmdavc	ip, {r0, r2, r8, r9, sl, fp, sp, pc}^
d0016510:	d1322c2a 	teqle	r2, sl, lsr #24
d0016514:	3000f8d9 	ldrdcc	pc, [r0], -r9
d0016518:	681f1c88 	ldmdavs	pc, {r3, r7, sl, fp, ip}	; <UNPREDICTABLE>
d001651c:	2f001d1a 	svccs	0x00001d1a
d0016520:	2000f8c9 	andcs	pc, r0, r9, asr #17
d0016524:	f2c0788c 	vmlal.s8	<illegal reg q11.5>, d16, d12
d0016528:	f5b78091 			; <UNDEFINED> instruction: 0xf5b78091
d001652c:	46015f00 	strmi	r5, [r1], -r0, lsl #30
d0016530:	f44fbf28 			; <UNDEFINED> instruction: 0xf44fbf28
d0016534:	2c685700 	stclcs	7, cr5, [r8], #-0
d0016538:	aef3f47f 	mrcge	4, 7, APSR_nzcv, cr3, cr15, {3}
d001653c:	2c68784c 	stclcs	8, cr7, [r8], #-304	; 0xfffffed0
d0016540:	3101d03e 	tstcc	r1, lr, lsr r0
d0016544:	e6f92302 	ldrbt	r2, [r9], r2, lsl #6
d0016548:	4f00f1b5 	svcmi	0x0000f1b5
d001654c:	0601f046 	streq	pc, [r1], -r6, asr #32
d0016550:	426dd077 	rsbmi	sp, sp, #119	; 0x77
d0016554:	4001f898 	mulmi	r1, r8, r8
d0016558:	5f00f5b5 	svcpl	0x0000f5b5
d001655c:	f44fbf28 			; <UNDEFINED> instruction: 0xf44fbf28
d0016560:	e6d65500 	ldrb	r5, [r6], r0, lsl #10
d0016564:	2c6c784c 	stclcs	8, cr7, [ip], #-304	; 0xfffffed0
d0016568:	8096f000 	addshi	pc, r6, r0
d001656c:	23033101 	movwcs	r3, #12545	; 0x3101
d0016570:	784ce6e4 	stmdavc	ip, {r2, r5, r6, r7, r9, sl, sp, lr, pc}^
d0016574:	31012305 	tstcc	r1, r5, lsl #6
d0016578:	f1a4e6e0 			; <UNDEFINED> instruction: 0xf1a4e6e0
d001657c:	1c480230 	sfmne	f0, 2, [r8], {48}	; 0x30
d0016580:	2b09b2d3 	blcs	0xd02830d4
d0016584:	80daf200 	sbcshi	pc, sl, r0, lsl #4
d0016588:	27001c88 	strcs	r1, [r0, -r8, lsl #25]
d001658c:	5300f5c2 	movwpl	pc, #1474	; 0x5c2	; <UNPREDICTABLE>
d0016590:	0487eb07 	streq	lr, [r7], #2823	; 0xb07
d0016594:	fbaa4601 	blx	0xceaa7da2
d0016598:	ebb7c303 	bl	0xcee071ac
d001659c:	eb020fd3 	bl	0xd009a4f0
d00165a0:	f8100744 			; <UNDEFINED> instruction: 0xf8100744
d00165a4:	bf884b01 	svclt	0x00884b01
d00165a8:	5700f44f 	strpl	pc, [r0, -pc, asr #8]
d00165ac:	0230f1a4 	eorseq	pc, r0, #164, 2	; 0x29
d00165b0:	2b09b2d3 	blcs	0xd0283104
d00165b4:	e6b1d9ea 	ldrt	sp, [r1], sl, ror #19
d00165b8:	e6e92108 	strbt	r2, [r9], r8, lsl #2
d00165bc:	e6e72110 	usat	r2, #7, r0, lsl #2
d00165c0:	2301788c 	movwcs	r7, #6284	; 0x188c
d00165c4:	e6b93102 	ldrt	r3, [r9], r2, lsl #2
d00165c8:	3000f8db 	ldrdcc	pc, [r0], -fp
d00165cc:	f43f2b00 			; <UNDEFINED> instruction: 0xf43f2b00
d00165d0:	f8dbaf28 			; <UNDEFINED> instruction: 0xf8dbaf28
d00165d4:	2a002004 	bcs	0xd001e5ec
d00165d8:	af23f43f 	svcge	0x0023f43f
d00165dc:	1008f8db 	ldrdne	pc, [r8], -fp
d00165e0:	bf98428a 	svclt	0x0098428a
d00165e4:	31fff102 	mvnscc	pc, r2, lsl #2
d00165e8:	545a2200 	ldrbpl	r2, [sl], #-512	; 0xfffffe00
d00165ec:	0008f8db 	ldrdeq	pc, [r8], -fp
d00165f0:	e8bdb027 	pop	{r0, r1, r2, r5, ip, sp, pc}
d00165f4:	784c8ff0 	stmdavc	ip, {r4, r5, r6, r7, r8, r9, sl, fp, pc}^
d00165f8:	31012306 	tstcc	r1, r6, lsl #6
d00165fc:	f8d9e69e 			; <UNDEFINED> instruction: 0xf8d9e69e
d0016600:	f9b33000 			; <UNDEFINED> instruction: 0xf9b33000
d0016604:	1d1a0000 	ldcne	0, cr0, [sl, #-0]
d0016608:	f8c917c1 			; <UNDEFINED> instruction: 0xf8c917c1
d001660c:	e72a2000 	str	r2, [sl, -r0]!
d0016610:	3000f8d9 	ldrdcc	pc, [r0], -r9
d0016614:	0000f993 	muleq	r0, r3, r9
d0016618:	17c11d1a 	bfine	r1, sl, (invalid: 26:1)
d001661c:	2000f8c9 	andcs	pc, r0, r9, asr #17
d0016620:	f8d9e721 			; <UNDEFINED> instruction: 0xf8d9e721
d0016624:	1d183000 	ldcne	0, cr3, [r8, #-0]
d0016628:	2300881a 	movwcs	r8, #2074	; 0x81a
d001662c:	0000f8c9 	andeq	pc, r0, r9, asr #17
d0016630:	f8d9e6d3 			; <UNDEFINED> instruction: 0xf8d9e6d3
d0016634:	1d183000 	ldcne	0, cr3, [r8, #-0]
d0016638:	2300781a 	movwcs	r7, #2074	; 0x81a
d001663c:	0000f8c9 	andeq	pc, r0, r9, asr #17
d0016640:	f898e6cb 			; <UNDEFINED> instruction: 0xf898e6cb
d0016644:	f44f4001 	vst4.8	{d20-d23}, [pc], r1
d0016648:	e6625500 	strbt	r5, [r2], -r0, lsl #10
d001664c:	37fff04f 	ldrbcc	pc, [pc, pc, asr #32]!	; <UNPREDICTABLE>
d0016650:	e6634601 	strbt	r4, [r3], -r1, lsl #12
d0016654:	d0592c70 	subsle	r2, r9, r0, ror ip
d0016658:	d0722c73 	rsbsle	r2, r2, r3, ror ip
d001665c:	d0262c63 	eorle	r2, r6, r3, ror #24
d0016660:	0245f1a1 	subeq	pc, r5, #1073741864	; 0x40000028
d0016664:	d93f2a02 	ldmdble	pc!, {r1, r9, fp, sp}	; <UNPREDICTABLE>
d0016668:	f0002941 			; <UNDEFINED> instruction: 0xf0002941
d001666c:	2c6e80af 	stclcs	0, cr8, [lr], #-700	; 0xfffffd44
d0016670:	8216f000 	andshi	pc, r6, #0
d0016674:	21254658 			; <UNDEFINED> instruction: 0x21254658
d0016678:	f9def7ff 			; <UNDEFINED> instruction: 0xf9def7ff
d001667c:	46584621 	ldrbmi	r4, [r8], -r1, lsr #12
d0016680:	f9daf7ff 			; <UNDEFINED> instruction: 0xf9daf7ff
d0016684:	bf00e6bb 	svclt	0x0000e6bb
d0016688:	00082001 	andeq	r2, r8, r1
d001668c:	ffffffce 			; <UNDEFINED> instruction: 0xffffffce
d0016690:	cccccccd 	stclgt	12, cr12, [ip], {205}	; 0xcd
d0016694:	ffffffb4 			; <UNDEFINED> instruction: 0xffffffb4
d0016698:	2304788c 	movwcs	r7, #18572	; 0x488c
d001669c:	e64d3102 	strb	r3, [sp], -r2, lsl #2
d00166a0:	2307784c 	movwcs	r7, #30796	; 0x784c
d00166a4:	e6493101 	strb	r3, [r9], -r1, lsl #2
d00166a8:	25004641 	strcs	r4, [r0, #-1601]	; 0xfffff9bf
d00166ac:	2d01e631 	stccs	6, cr14, [r1, #-196]	; 0xffffff3c
d00166b0:	2501bf38 	strcs	fp, [r1, #-3896]	; 0xfffff0c8
d00166b4:	f10507f6 			; <UNDEFINED> instruction: 0xf10507f6
d00166b8:	f14037ff 			; <UNDEFINED> instruction: 0xf14037ff
d00166bc:	f8d9818b 			; <UNDEFINED> instruction: 0xf8d9818b
d00166c0:	46583000 	ldrbmi	r3, [r8], -r0
d00166c4:	1d1a3d02 	ldcne	13, cr3, [sl, #-8]
d00166c8:	f8c97819 			; <UNDEFINED> instruction: 0xf8c97819
d00166cc:	f7ff2000 			; <UNDEFINED> instruction: 0xf7ff2000
d00166d0:	2f00f9b3 	svccs	0x0000f9b3
d00166d4:	ae93f43f 	mrcge	4, 4, APSR_nzcv, cr3, cr15, {1}
d00166d8:	46583d01 	ldrbmi	r3, [r8], -r1, lsl #26
d00166dc:	f7ff2120 			; <UNDEFINED> instruction: 0xf7ff2120
d00166e0:	1c68f9ab 			; <UNDEFINED> instruction: 0x1c68f9ab
d00166e4:	e68ad1f8 			; <UNDEFINED> instruction: 0xe68ad1f8
d00166e8:	0000f8d9 	ldrdeq	pc, [r0], -r9
d00166ec:	462b4621 	strtmi	r4, [fp], -r1, lsr #12
d00166f0:	1dc44632 	stclne	6, cr4, [r4, #200]	; 0xc8
d00166f4:	f0244658 			; <UNDEFINED> instruction: 0xf0244658
d00166f8:	ed940407 	cfldrs	mvf0, [r4, #28]
d00166fc:	34080b00 	strcc	r0, [r8], #-2816	; 0xfffff500
d0016700:	f8c99700 			; <UNDEFINED> instruction: 0xf8c99700
d0016704:	f7ff4000 			; <UNDEFINED> instruction: 0xf7ff4000
d0016708:	e678fb75 			; <UNDEFINED> instruction: 0xe678fb75
d001670c:	3000f8d9 	ldrdcc	pc, [r0], -r9
d0016710:	060cf026 	streq	pc, [ip], -r6, lsr #32
d0016714:	21102401 	tstcs	r0, r1, lsl #8
d0016718:	46581d1a 			; <UNDEFINED> instruction: 0x46581d1a
d001671c:	2000f8c9 	andcs	pc, r0, r9, asr #17
d0016720:	4663681a 			; <UNDEFINED> instruction: 0x4663681a
d0016724:	f8cd9602 			; <UNDEFINED> instruction: 0xf8cd9602
d0016728:	9704c014 	smladls	r4, r4, r0, ip
d001672c:	f8cd9503 			; <UNDEFINED> instruction: 0xf8cd9503
d0016730:	9406c004 	strls	ip, [r6], #-4
d0016734:	f7ff9100 			; <UNDEFINED> instruction: 0xf7ff9100
d0016738:	e660f9af 	strbt	pc, [r0], -pc, lsr #19	; <UNPREDICTABLE>
d001673c:	27004601 	strcs	r4, [r0, -r1, lsl #12]
d0016740:	f8d9e5ec 			; <UNDEFINED> instruction: 0xf8d9e5ec
d0016744:	1d1a3000 	ldcne	0, cr3, [sl, #-0]
d0016748:	2000f8c9 	andcs	pc, r0, r9, asr #17
d001674c:	9314681b 	tstls	r4, #1769472	; 0x1b0000
d0016750:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d0016754:	781b813b 	ldmdavc	fp, {r0, r1, r3, r4, r5, r8, pc}
d0016758:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d001675c:	0ff88197 	svceq	0x00f88197
d0016760:	f0002f00 			; <UNDEFINED> instruction: 0xf0002f00
d0016764:	9a148193 	bls	0xd0536db8
d0016768:	f8122400 			; <UNDEFINED> instruction: 0xf8122400
d001676c:	34013f01 	strcc	r3, [r1], #-3841	; 0xfffff0ff
d0016770:	42bcb11b 	adcsmi	fp, ip, #-1073741818	; 0xc0000006
d0016774:	2800d3f9 	stmdacs	r0, {r0, r3, r4, r5, r6, r7, r8, r9, ip, lr, pc}
d0016778:	42a5d1f7 	adcmi	sp, r5, #-1073741763	; 0xc000003d
d001677c:	813df200 	teqhi	sp, r0, lsl #4	; <UNPREDICTABLE>
d0016780:	0301f016 	movweq	pc, #4118	; 0x1016	; <UNPREDICTABLE>
d0016784:	f0009312 			; <UNDEFINED> instruction: 0xf0009312
d0016788:	25008189 	strcs	r8, [r0, #-393]	; 0xfffffe77
d001678c:	95149b14 	ldrls	r9, [r4, #-2836]	; 0xfffff4ec
d0016790:	1e5e4625 	cdpne	6, 5, cr4, cr14, cr5, {1}
d0016794:	4637461c 			; <UNDEFINED> instruction: 0x4637461c
d0016798:	f8164658 			; <UNDEFINED> instruction: 0xf8164658
d001679c:	f7ff1f01 			; <UNDEFINED> instruction: 0xf7ff1f01
d00167a0:	1cbbf94b 			; <UNDEFINED> instruction: 0x1cbbf94b
d00167a4:	429d1b1b 	addsmi	r1, sp, #27648	; 0x6c00
d00167a8:	9b12d8f5 	blls	0xd04ccb84
d00167ac:	2b009d14 	blcs	0xd003dc04
d00167b0:	ae25f43f 	mcrge	4, 1, pc, cr5, cr15, {1}	; <UNPREDICTABLE>
d00167b4:	2d001e6c 	stccs	14, cr1, [r0, #-432]	; 0xfffffe50
d00167b8:	ae21f43f 	mcrge	4, 1, pc, cr1, cr15, {1}	; <UNPREDICTABLE>
d00167bc:	21203c01 			; <UNDEFINED> instruction: 0x21203c01
d00167c0:	f7ff4658 			; <UNDEFINED> instruction: 0xf7ff4658
d00167c4:	1c67f939 			; <UNDEFINED> instruction: 0x1c67f939
d00167c8:	e618d1f8 			; <UNDEFINED> instruction: 0xe618d1f8
d00167cc:	3000f8d9 	ldrdcc	pc, [r0], -r9
d00167d0:	f0233307 			; <UNDEFINED> instruction: 0xf0233307
d00167d4:	ed930307 	ldc	3, cr0, [r3, #28]
d00167d8:	33087b00 	movwcc	r7, #35584	; 0x8b00
d00167dc:	0b17ec51 	bleq	0xd0611928
d00167e0:	3000f8c9 	andcc	pc, r0, r9, asr #17
d00167e4:	ee17460b 	cfmsub32	mvax0, mvfx4, mvfx7, mvfx11
d00167e8:	2b002a10 	blcs	0xd0021030
d00167ec:	7b12ed8d 	blvc	0xd04d1e28
d00167f0:	8176f2c0 	cmnhi	r6, r0, asr #5	; <UNPREDICTABLE>
d00167f4:	f1000771 			; <UNDEFINED> instruction: 0xf1000771
d00167f8:	00b18176 	adcseq	r8, r1, r6, ror r1
d00167fc:	0120f001 	msreq	CPSR_, r1
d0016800:	f3c39114 	vorr.i32	d25, #180	; 0x000000b4
d0016804:	920c510a 	andls	r5, ip, #-2147483646	; 0x80000002
d0016808:	72fff240 	rscsvc	pc, pc, #64, 4
d001680c:	0313f3c3 	tsteq	r3, #201326595	; 0xc000003	; <UNPREDICTABLE>
d0016810:	42919116 	addsmi	r9, r1, #-2147483643	; 0x80000005
d0016814:	f000930d 			; <UNDEFINED> instruction: 0xf000930d
d0016818:	9b16817c 	blls	0xd05b6e10
d001681c:	bf142b00 	svclt	0x00142b00
d0016820:	22002201 	andcs	r2, r0, #268435456	; 0x10000000
d0016824:	f0009217 			; <UNDEFINED> instruction: 0xf0009217
d0016828:	f2a38161 	vmla.f32	d8, d3, d1[1]
d001682c:	2b0033ff 	blcs	0xd0023830
d0016830:	bfb8931a 	svclt	0x00b8931a
d0016834:	9312425b 	tstls	r2, #-1342177275	; 0xb0000005
d0016838:	f0001c78 			; <UNDEFINED> instruction: 0xf0001c78
d001683c:	f5b7818a 			; <UNDEFINED> instruction: 0xf5b7818a
d0016840:	f3405f00 	vpmax.f32	d21, d0, d0
d0016844:	f44f817d 	vst4.16	{d24,d26,d28,d30}, [pc :256]!
d0016848:	e9dd5700 	ldmib	sp, {r8, r9, sl, ip, lr}^
d001684c:	9715230c 	ldrls	r2, [r5, -ip, lsl #6]
d0016850:	230ae9cd 	movwcs	lr, #43469	; 0xa9cd
d0016854:	2100ab22 	tstcs	r0, r2, lsr #22
d0016858:	ee079a12 			; <UNDEFINED> instruction: 0xee079a12
d001685c:	4618ba90 			; <UNDEFINED> instruction: 0x4618ba90
d0016860:	fbaa9321 	blx	0xceabb4ee
d0016864:	4694c302 	ldrmi	ip, [r4], r2, lsl #6
d0016868:	3101468e 	smlabbcc	r1, lr, r6, r4
d001686c:	0bd3ea4f 	bleq	0xcf5111b0
d0016870:	0f09f1bc 	svceq	0x0009f1bc
d0016874:	038beb0b 	orreq	lr, fp, #11264	; 0x2c00
d0016878:	0343eba2 	movteq	lr, #15266	; 0x3ba2
d001687c:	f103465a 			; <UNDEFINED> instruction: 0xf103465a
d0016880:	b2db0330 	sbcslt	r0, fp, #48, 6	; 0xc0000000
d0016884:	3b01f800 	blcc	0xd009488c
d0016888:	ee17d8eb 	cdp	8, 1, cr13, cr7, cr11, {7}
d001688c:	931fba90 	tstls	pc, #144, 20	; 0x90000
d0016890:	e080f8cd 	add	pc, r0, sp, asr #17
d0016894:	f0002f00 			; <UNDEFINED> instruction: 0xf0002f00
d0016898:	f00681bd 			; <UNDEFINED> instruction: 0xf00681bd
d001689c:	22040310 	andcs	r0, r4, #16, 6	; 0x40000000
d00168a0:	9b14931b 	blls	0xd053b514
d00168a4:	3b009815 	blcc	0xd003c900
d00168a8:	2301bf18 	movwcs	fp, #7960	; 0x1f18
d00168ac:	44033302 	strmi	r3, [r3], #-770	; 0xfffffcfe
d00168b0:	4413440b 	ldrmi	r4, [r3], #-1035	; 0xfffffbf5
d00168b4:	f240429d 	vqsub.s8	d20, d16, d13
d00168b8:	f00681b9 			; <UNDEFINED> instruction: 0xf00681b9
d00168bc:	f0060101 			; <UNDEFINED> instruction: 0xf0060101
d00168c0:	1aea0003 	bne	0xcfa968d4
d00168c4:	0301f081 	movweq	pc, #4225	; 0x1081	; <UNPREDICTABLE>
d00168c8:	901e9116 	andsls	r9, lr, r6, lsl r1
d00168cc:	bf0c2802 	svclt	0x000c2802
d00168d0:	f0032600 			; <UNDEFINED> instruction: 0xf0032600
d00168d4:	92120601 	andsls	r0, r2, #1048576	; 0x100000
d00168d8:	f0002e00 			; <UNDEFINED> instruction: 0xf0002e00
d00168dc:	1e5581a5 	lognedp	f0, f5
d00168e0:	f0002a00 			; <UNDEFINED> instruction: 0xf0002a00
d00168e4:	3d0181b0 	stfccd	f0, [r1, #-704]	; 0xfffffd40
d00168e8:	46582120 	ldrbmi	r2, [r8], -r0, lsr #2
d00168ec:	f8a4f7ff 			; <UNDEFINED> instruction: 0xf8a4f7ff
d00168f0:	d1f81c69 	mvnsle	r1, r9, ror #24
d00168f4:	93162300 	tstls	r6, #0, 6
d00168f8:	2b009b14 	blcs	0xd003d550
d00168fc:	8185f040 	orrhi	pc, r5, r0, asr #32
d0016900:	46582130 			; <UNDEFINED> instruction: 0x46582130
d0016904:	f898f7ff 			; <UNDEFINED> instruction: 0xf898f7ff
d0016908:	46582c41 	ldrbmi	r2, [r8], -r1, asr #24
d001690c:	2158bf0c 	cmpcs	r8, ip, lsl #30
d0016910:	f7ff2178 			; <UNDEFINED> instruction: 0xf7ff2178
d0016914:	9b1ef891 	blls	0xd07d4b60
d0016918:	d1022b02 	tstle	r2, r2, lsl #22
d001691c:	f0402e00 			; <UNDEFINED> instruction: 0xf0402e00
d0016920:	99178195 	ldmdbls	r7, {r0, r2, r4, r7, r8, pc}
d0016924:	31304658 	teqcc	r0, r8, asr r6
d0016928:	f7ffb2c9 			; <UNDEFINED> instruction: 0xf7ffb2c9
d001692c:	9b15f885 	blls	0xd0594b48
d0016930:	43139a1b 	tstmi	r3, #110592	; 0x1b000
d0016934:	212ed003 			; <UNDEFINED> instruction: 0x212ed003
d0016938:	f7ff4658 			; <UNDEFINED> instruction: 0xf7ff4658
d001693c:	2c41f87d 	mcrrcs	8, 7, pc, r1, cr13	; <UNPREDICTABLE>
d0016940:	816ff000 	msrhi	SPSR_fsxc, r0
d0016944:	f0002f00 			; <UNDEFINED> instruction: 0xf0002f00
d0016948:	9e08821f 	mcrls	2, 0, r8, cr8, cr15, {0}
d001694c:	250000bb 	strcs	r0, [r0, #-187]	; 0xffffff45
d0016950:	3b049415 	blcc	0xd013b9ac
d0016954:	e0069314 	and	r9, r6, r4, lsl r3
d0016958:	78193501 	ldmdavc	r9, {r0, r8, sl, ip, sp}
d001695c:	f7ff4658 			; <UNDEFINED> instruction: 0xf7ff4658
d0016960:	42aff86b 	adcmi	pc, pc, #7012352	; 0x6b0000
d0016964:	2d0cd064 	stccs	0, cr13, [ip, #-400]	; 0xfffffe70
d0016968:	dcf54633 	ldclle	6, cr4, [r5], #204	; 0xcc
d001696c:	7185ebc5 	orrvc	lr, r5, r5, asr #23
d0016970:	9c0a9b14 			; <UNDEFINED> instruction: 0x9c0a9b14
d0016974:	460a2f0c 	strmi	r2, [sl], -ip, lsl #30
d0016978:	0181ea4f 	orreq	lr, r1, pc, asr #20
d001697c:	0282eb03 	addeq	lr, r2, #3072	; 0xc00
d0016980:	0330f101 	teqeq	r0, #1073741824	; 0x40000000	; <UNPREDICTABLE>
d0016984:	0110f101 	tsteq	r0, r1, lsl #2	; <UNPREDICTABLE>
d0016988:	0020f1c2 	eoreq	pc, r0, r2, asr #3
d001698c:	0c20f1a2 	stfeqd	f7, [r0], #-648	; 0xfffffd78
d0016990:	f202fa24 	vpmax.s8	d15, d2, d20
d0016994:	f1c39c0b 			; <UNDEFINED> instruction: 0xf1c39c0b
d0016998:	fa040e20 	blx	0xd011a220
d001699c:	9c0cf000 	stcls	0, cr15, [ip], {-0}
d00169a0:	f303fa24 	vpmax.u8	d15, d3, d20
d00169a4:	ea429c0d 	b	0xd10bd9e0
d00169a8:	980d0200 	stmdals	sp, {r9}
d00169ac:	fe0efa04 	vseleq.f32	s30, s28, s8
d00169b0:	fa209c0b 	blx	0xd083d9e4
d00169b4:	fa24f101 	blx	0xd0952dc0
d00169b8:	ea43fc0c 	b	0xd11159f0
d00169bc:	dc32030e 	ldcle	3, cr0, [r2], #-56	; 0xffffffc8
d00169c0:	020cea42 	andeq	lr, ip, #270336	; 0x42000
d00169c4:	030ff002 	movweq	pc, #61442	; 0xf002	; <UNPREDICTABLE>
d00169c8:	e7c54433 			; <UNDEFINED> instruction: 0xe7c54433
d00169cc:	447b4bfb 	ldrbtmi	r4, [fp], #-3067	; 0xfffff405
d00169d0:	e6c49314 			; <UNDEFINED> instruction: 0xe6c49314
d00169d4:	b1373d02 	teqlt	r7, r2, lsl #26
d00169d8:	21203d01 			; <UNDEFINED> instruction: 0x21203d01
d00169dc:	f7ff4658 			; <UNDEFINED> instruction: 0xf7ff4658
d00169e0:	1c6cf82b 	stclne	8, cr15, [ip], #-172	; 0xffffff54
d00169e4:	f8d9d1f8 			; <UNDEFINED> instruction: 0xf8d9d1f8
d00169e8:	46583000 	ldrbmi	r3, [r8], -r0
d00169ec:	78191d1a 	ldmdavc	r9, {r1, r3, r4, r8, sl, fp, ip}
d00169f0:	2000f8c9 	andcs	pc, r0, r9, asr #17
d00169f4:	f820f7ff 			; <UNDEFINED> instruction: 0xf820f7ff
d00169f8:	f016e501 			; <UNDEFINED> instruction: 0xf016e501
d00169fc:	eba50301 	bl	0xce957608
d0016a00:	93120504 	tstls	r2, #4, 10	; 0x1000000
d0016a04:	aec2f47f 	mcrge	4, 6, pc, cr2, cr15, {3}	; <UNPREDICTABLE>
d0016a08:	b1351e6e 	teqlt	r5, lr, ror #28
d0016a0c:	21203e01 			; <UNDEFINED> instruction: 0x21203e01
d0016a10:	f7ff4658 			; <UNDEFINED> instruction: 0xf7ff4658
d0016a14:	1c73f811 	ldclne	8, cr15, [r3], #-68	; 0xffffffbc
d0016a18:	2c00d1f8 	stfcsd	f5, [r0], {248}	; 0xf8
d0016a1c:	aceff43f 	cfstrdge	mvd15, [pc], #252	; 0xd0016b20
d0016a20:	93122300 	tstls	r2, #0, 6
d0016a24:	430be6b2 	movwmi	lr, #46770	; 0xb6b2
d0016a28:	030ff003 	movweq	pc, #61443	; 0xf003	; <UNPREDICTABLE>
d0016a2c:	e7934433 			; <UNDEFINED> instruction: 0xe7934433
d0016a30:	2c419c15 	mcrrcs	12, 1, r9, r1, cr5
d0016a34:	2150bf0c 	cmpcs	r0, ip, lsl #30
d0016a38:	46582170 			; <UNDEFINED> instruction: 0x46582170
d0016a3c:	fffcf7fe 			; <UNDEFINED> instruction: 0xfffcf7fe
d0016a40:	9d219b1a 	vstmdbls	r1!, {d9-d21}
d0016a44:	2b004658 	blcs	0xd00283ac
d0016a48:	461c9b20 	ldrmi	r9, [ip], -r0, lsr #22
d0016a4c:	212dbfb4 			; <UNDEFINED> instruction: 0x212dbfb4
d0016a50:	f7fe212b 			; <UNDEFINED> instruction: 0xf7fe212b
d0016a54:	442cfff1 	strtmi	pc, [ip], #-4081	; 0xfffff00f
d0016a58:	e001991f 	and	r9, r1, pc, lsl r9
d0016a5c:	1d01f814 	stcne	8, cr15, [r1, #-80]	; 0xffffffb0
d0016a60:	f7fe4658 			; <UNDEFINED> instruction: 0xf7fe4658
d0016a64:	42a5ffe9 	adcmi	pc, r5, #932	; 0x3a4
d0016a68:	9b16d1f8 	blls	0xd05cb250
d0016a6c:	f43f2b00 			; <UNDEFINED> instruction: 0xf43f2b00
d0016a70:	9b12acc6 	blls	0xd04c1d90
d0016a74:	2b001e5c 	blcs	0xd001e3ec
d0016a78:	acc1f43f 	cfstrdge	mvd15, [r1], {63}	; 0x3f
d0016a7c:	21203c01 			; <UNDEFINED> instruction: 0x21203c01
d0016a80:	f7fe4658 			; <UNDEFINED> instruction: 0xf7fe4658
d0016a84:	1c63ffd9 	stclne	15, cr15, [r3], #-868	; 0xfffffc9c
d0016a88:	e4b8d1f8 	ldrt	sp, [r8], #504	; 0x1f8
d0016a8c:	f43f2d00 			; <UNDEFINED> instruction: 0xf43f2d00
d0016a90:	07f2acb6 			; <UNDEFINED> instruction: 0x07f2acb6
d0016a94:	817af140 	cmnhi	sl, r0, asr #2	; <UNPREDICTABLE>
d0016a98:	e68f1e6c 	str	r1, [pc], ip, ror #28
d0016a9c:	e7bc9d12 			; <UNDEFINED> instruction: 0xe7bc9d12
d0016aa0:	f8db3b01 			; <UNDEFINED> instruction: 0xf8db3b01
d0016aa4:	2b062008 	blcs	0xd019eacc
d0016aa8:	e8dfd812 	ldm	pc, {r1, r4, fp, ip, lr, pc}^	; <UNPREDICTABLE>
d0016aac:	014bf013 	cmpeq	fp, r3, lsl r0	; <UNPREDICTABLE>
d0016ab0:	00110142 	andseq	r0, r1, r2, asr #2
d0016ab4:	00110007 	andseq	r0, r1, r7
d0016ab8:	00070011 	andeq	r0, r7, r1, lsl r0
d0016abc:	3000f8d9 	ldrdcc	pc, [r0], -r9
d0016ac0:	1d182100 	ldfnes	f2, [r8, #-0]
d0016ac4:	0000f8c9 	andeq	pc, r0, r9, asr #17
d0016ac8:	e9c3681b 	stmib	r3, {r0, r1, r3, r4, fp, sp, lr}^
d0016acc:	e4962100 	ldr	r2, [r6], #256	; 0x100
d0016ad0:	3000f8d9 	ldrdcc	pc, [r0], -r9
d0016ad4:	f8c91d19 			; <UNDEFINED> instruction: 0xf8c91d19
d0016ad8:	681b1000 	ldmdavs	fp, {ip}
d0016adc:	e48e601a 	str	r6, [lr], #26
d0016ae0:	9114212d 	tstls	r4, sp, lsr #2
d0016ae4:	212be68d 	smlawbcs	fp, sp, r6, lr
d0016ae8:	e68a9114 	pkhbt	r9, sl, r4, lsl #2
d0016aec:	010ce9dd 	ldrdeq	lr, [ip, -sp]
d0016af0:	32fef240 	rscscc	pc, lr, #64, 4
d0016af4:	0301ea50 	movweq	lr, #6736	; 0x1a50
d0016af8:	48af9916 	stmiami	pc!, {r1, r2, r4, r8, fp, ip, pc}	; <UNPREDICTABLE>
d0016afc:	460bbf0c 	strmi	fp, [fp], -ip, lsl #30
d0016b00:	93124613 	tstls	r2, #19922944	; 0x1300000
d0016b04:	230ce9dd 	movwcs	lr, #51677	; 0xc9dd
d0016b08:	460bbf0c 	strmi	fp, [fp], -ip, lsl #30
d0016b0c:	931a4603 	tstls	sl, #3145728	; 0x300000
d0016b10:	2c41e692 	mcrrcs	6, 9, lr, r1, cr2
d0016b14:	4632462b 	ldrtmi	r4, [r2], -fp, lsr #12
d0016b18:	bf0c4658 	svclt	0x000c4658
d0016b1c:	21662146 	cmncs	r6, r6, asr #2
d0016b20:	ed9d9700 	ldc	7, cr9, [sp]
d0016b24:	f7ff0b12 			; <UNDEFINED> instruction: 0xf7ff0b12
d0016b28:	e468f965 	strbt	pc, [r8], #-2405	; 0xfffff69b	; <UNPREDICTABLE>
d0016b2c:	463b4631 			; <UNDEFINED> instruction: 0x463b4631
d0016b30:	f8cd462c 			; <UNDEFINED> instruction: 0xf8cd462c
d0016b34:	9e158048 	cdpls	0, 1, cr8, cr5, cr8, {2}
d0016b38:	461746c8 	ldrmi	r4, [r7], -r8, asr #13
d0016b3c:	460d4699 			; <UNDEFINED> instruction: 0x460d4699
d0016b40:	f3402f0c 	vpmax.f32	d18, d0, d12
d0016b44:	97158090 			; <UNDEFINED> instruction: 0x97158090
d0016b48:	230ce9dd 	movwcs	lr, #51677	; 0xc9dd
d0016b4c:	230ae9cd 	movwcs	lr, #43469	; 0xa9cd
d0016b50:	270de680 	strcs	lr, [sp, -r0, lsl #13]
d0016b54:	46494628 	strbmi	r4, [r9], -r8, lsr #12
d0016b58:	46c12300 	strbmi	r2, [r1], r0, lsl #6
d0016b5c:	9615463a 			; <UNDEFINED> instruction: 0x9615463a
d0016b60:	4625469e 			; <UNDEFINED> instruction: 0x4625469e
d0016b64:	8048f8dd 	ldrdhi	pc, [r8], #-141	; 0xffffff73
d0016b68:	4606460f 	strmi	r4, [r6], -pc, lsl #12
d0016b6c:	0c20f1c3 	stfeqd	f7, [r0], #-780	; 0xfffffcf4
d0016b70:	990c980d 	stmdbls	ip, {r0, r2, r3, fp, ip, pc}
d0016b74:	0420f1a3 	strteq	pc, [r0], #-419	; 0xfffffe5d
d0016b78:	fc0cfa00 	stc2	10, cr15, [ip], {-0}	; <UNPREDICTABLE>
d0016b7c:	40e040d9 	ldrdmi	r4, [r0], #9	; <UNPREDICTABLE>
d0016b80:	ea413304 	b	0xd1063798
d0016b84:	4301010c 	movwmi	r0, #4364	; 0x110c
d0016b88:	010ff001 	tsteq	pc, r1	; <UNPREDICTABLE>
d0016b8c:	1e0ae9cd 	vmlsne.f16	s28, s21, s26	; <UNPREDICTABLE>
d0016b90:	010ae9dd 	ldrdeq	lr, [sl, -sp]
d0016b94:	d1c94301 	bicle	r4, r9, r1, lsl #6
d0016b98:	d1e73a01 	mvnle	r3, r1, lsl #20
d0016b9c:	f8cd463b 			; <UNDEFINED> instruction: 0xf8cd463b
d0016ba0:	46178048 	ldrmi	r8, [r7], -r8, asr #32
d0016ba4:	469946c8 	ldrmi	r4, [r9], r8, asr #13
d0016ba8:	462c4631 			; <UNDEFINED> instruction: 0x462c4631
d0016bac:	460d9e15 			; <UNDEFINED> instruction: 0x460d9e15
d0016bb0:	e9dd9715 	ldmib	sp, {r0, r2, r4, r8, r9, sl, ip, pc}^
d0016bb4:	e9cd230c 	stmib	sp, {r2, r3, r8, r9, sp}^
d0016bb8:	22012318 	andcs	r2, r1, #24, 6	; 0x60000000
d0016bbc:	e9cd2300 	stmib	sp, {r8, r9, sp}^
d0016bc0:	22002310 	andcs	r2, r0, #16, 6	; 0x40000000
d0016bc4:	2300f44f 	movwcs	pc, #1103	; 0x44f	; <UNPREDICTABLE>
d0016bc8:	230ee9cd 	movwcs	lr, #59853	; 0xe9cd
d0016bcc:	230ee9dd 	movwcs	lr, #59869	; 0xe9dd
d0016bd0:	0118e9dd 			; <UNDEFINED> instruction: 0x0118e9dd
d0016bd4:	bf08428b 	svclt	0x0008428b
d0016bd8:	f0c04282 			; <UNDEFINED> instruction: 0xf0c04282
d0016bdc:	429980c1 	addsmi	r8, r9, #193	; 0xc1
d0016be0:	4290bf08 	addsmi	fp, r0, #8, 30
d0016be4:	80b7f000 	adcshi	pc, r7, r0
d0016be8:	230ae9dd 	movwcs	lr, #43485	; 0xa9dd
d0016bec:	0110e9dd 			; <UNDEFINED> instruction: 0x0110e9dd
d0016bf0:	bf08428b 	svclt	0x0008428b
d0016bf4:	f47f4282 			; <UNDEFINED> instruction: 0xf47f4282
d0016bf8:	9b17ae2d 	blls	0xd06024b4
d0016bfc:	33012200 	movwcc	r2, #4608	; 0x1200
d0016c00:	23009317 	movwcs	r9, #791	; 0x317
d0016c04:	230ae9cd 	movwcs	lr, #43469	; 0xa9cd
d0016c08:	4619e624 	ldrmi	lr, [r9], -r4, lsr #12
d0016c0c:	f7fe4658 			; <UNDEFINED> instruction: 0xf7fe4658
d0016c10:	e675ff13 	uhadd16	pc, r5, r3	; <UNPREDICTABLE>
d0016c14:	0310f016 	tsteq	r0, #22	; <UNPREDICTABLE>
d0016c18:	2204bf14 	andcs	fp, r4, #20, 30	; 0x50
d0016c1c:	931b2203 	tstls	fp, #805306368	; 0x30000000
d0016c20:	b177e63f 	cmnlt	r7, pc, lsr r6
d0016c24:	e6919e09 	ldr	r9, [r1], r9, lsl #28
d0016c28:	e665461e 			; <UNDEFINED> instruction: 0xe665461e
d0016c2c:	0203f006 	andeq	pc, r3, #6
d0016c30:	0301f006 	movweq	pc, #4102	; 0x1006	; <UNPREDICTABLE>
d0016c34:	2200921e 	andcs	r9, r0, #-536870911	; 0xe0000001
d0016c38:	0601f083 	streq	pc, [r1], -r3, lsl #1
d0016c3c:	92129316 	andsls	r9, r2, #1476395008	; 0x58000000
d0016c40:	2150e65a 	cmpcs	r0, sl, asr r6
d0016c44:	9b12e6f9 	blls	0xd04d0830
d0016c48:	e6559316 			; <UNDEFINED> instruction: 0xe6559316
d0016c4c:	1e5d9b12 	vmovne.s8	r9, d13[0]
d0016c50:	f43f2b00 			; <UNDEFINED> instruction: 0xf43f2b00
d0016c54:	3d01ae66 	stccc	14, cr10, [r1, #-408]	; 0xfffffe68
d0016c58:	46582130 			; <UNDEFINED> instruction: 0x46582130
d0016c5c:	feecf7fe 	mcr2	7, 7, pc, cr12, cr14, {7}	; <UNPREDICTABLE>
d0016c60:	d1f81c6a 	mvnsle	r1, sl, ror #24
d0016c64:	f1c7e65d 			; <UNDEFINED> instruction: 0xf1c7e65d
d0016c68:	e9dd030d 	ldmib	sp, {r0, r2, r3, r8, r9}^
d0016c6c:	009b120c 	addseq	r1, fp, ip, lsl #4
d0016c70:	f1c34618 			; <UNDEFINED> instruction: 0xf1c34618
d0016c74:	f1a30c20 			; <UNDEFINED> instruction: 0xf1a30c20
d0016c78:	460b0e20 	strmi	r0, [fp], -r0, lsr #28
d0016c7c:	fc0cfa02 	stc2	10, cr15, [ip], {2}	; <UNPREDICTABLE>
d0016c80:	32fff04f 	rscscc	pc, pc, #79	; 0x4f
d0016c84:	f1a040c3 			; <UNDEFINED> instruction: 0xf1a040c3
d0016c88:	930a0120 	movwls	r0, #41248	; 0xa120
d0016c8c:	33fff04f 	mvnscc	pc, #79	; 0x4f
d0016c90:	fe0efa03 	vseleq.f32	s30, s28, s6
d0016c94:	f300fa02 	vpmax.u8	d15, d0, d2
d0016c98:	ea429a0a 	b	0xd10bd4c8
d0016c9c:	f1c0020c 			; <UNDEFINED> instruction: 0xf1c0020c
d0016ca0:	920a0c20 	andls	r0, sl, #32, 24	; 0x2000
d0016ca4:	fa229a0d 	blx	0xd08bd4e0
d0016ca8:	ea43f101 	b	0xd11130b4
d0016cac:	f04f020e 			; <UNDEFINED> instruction: 0xf04f020e
d0016cb0:	fa2333ff 	blx	0xd08e3cb4
d0016cb4:	4603fc0c 	strmi	pc, [r3], -ip, lsl #24
d0016cb8:	30fff04f 	rscscc	pc, pc, pc, asr #32
d0016cbc:	0e21f1a3 	abseqdp	f7, f3
d0016cc0:	40989315 	addsmi	r9, r8, r5, lsl r3
d0016cc4:	ea429b0a 	b	0xd10bd8f4
d0016cc8:	430b020c 	movwmi	r0, #45580	; 0xb20c
d0016ccc:	921b2101 	andsls	r2, fp, #1073741824	; 0x40000000
d0016cd0:	9b0c930a 	blls	0xd033b900
d0016cd4:	ea239a15 	b	0xd08fd530
d0016cd8:	00b80300 	adcseq	r0, r8, r0, lsl #6
d0016cdc:	0c21f1c2 	stfeqd	f7, [r1], #-776	; 0xfffffcf8
d0016ce0:	93189715 	tstls	r8, #5505024	; 0x540000
d0016ce4:	f30efa01 	vpmax.u8	d15, d14, d1
d0016ce8:	0e20f1a0 	abseqdp	f7, f0
d0016cec:	fc0cfa21 	stc2	10, cr15, [ip], {33}	; 0x21	; <UNPREDICTABLE>
d0016cf0:	9b0d930f 	blls	0xd037b934
d0016cf4:	930b40d3 	movwls	r4, #45267	; 0xb0d3
d0016cf8:	f30efa01 	vpmax.u8	d15, d14, d1
d0016cfc:	0e20f1c0 	abseqdm	f7, f0
d0016d00:	9b0f9311 	blls	0xd03fb94c
d0016d04:	fe0efa21 	vseleq.f32	s30, s28, s3
d0016d08:	030cea43 	movweq	lr, #51779	; 0xca43
d0016d0c:	3cfff102 	ldfccp	f7, [pc], #8	; 0xd0016d1c
d0016d10:	930f9a1b 	movwls	r9, #64027	; 0xfa1b
d0016d14:	ea239b0d 	b	0xd08fd950
d0016d18:	fa010202 	blx	0xd0057528
d0016d1c:	930ef30c 	movwls	pc, #58124	; 0xe30c	; <UNPREDICTABLE>
d0016d20:	92199b11 	andsls	r9, r9, #17408	; 0x4400
d0016d24:	030eea43 	movweq	lr, #59971	; 0xea43
d0016d28:	fa019311 	blx	0xd007b974
d0016d2c:	9310f300 	tstls	r0, #0, 6	; <UNPREDICTABLE>
d0016d30:	f8d9e74c 			; <UNDEFINED> instruction: 0xf8d9e74c
d0016d34:	1d193000 	ldcne	0, cr3, [r9, #-0]
d0016d38:	1000f8c9 	andne	pc, r0, r9, asr #17
d0016d3c:	801a681b 	andshi	r6, sl, fp, lsl r8
d0016d40:	bb5df7ff 	bllt	0xd1794d44
d0016d44:	3000f8d9 	ldrdcc	pc, [r0], -r9
d0016d48:	f8c91d19 			; <UNDEFINED> instruction: 0xf8c91d19
d0016d4c:	681b1000 	ldmdavs	fp, {ip}
d0016d50:	f7ff701a 			; <UNDEFINED> instruction: 0xf7ff701a
d0016d54:	b95fbb54 	ldmdblt	pc, {r2, r4, r6, r8, r9, fp, ip, sp, pc}^	; <UNPREDICTABLE>
d0016d58:	2b009b16 	blcs	0xd003d9b8
d0016d5c:	af44f43f 	svcge	0x0044f43f
d0016d60:	33019b0a 	movwcc	r9, #6922	; 0x1b0a
d0016d64:	9b0b930a 	blls	0xd02fb994
d0016d68:	0300f143 	movweq	pc, #323	; 0x143	; <UNPREDICTABLE>
d0016d6c:	e73b930b 	ldr	r9, [fp, -fp, lsl #6]!
d0016d70:	f0039b0a 			; <UNDEFINED> instruction: 0xf0039b0a
d0016d74:	931c0301 	tstls	ip, #67108864	; 0x4000000
d0016d78:	931d2300 	tstls	sp, #0, 6
d0016d7c:	231ce9dd 	tstcs	ip, #3620864	; 0x374000
d0016d80:	f43f4313 			; <UNDEFINED> instruction: 0xf43f4313
d0016d84:	e7ebaf31 			; <UNDEFINED> instruction: 0xe7ebaf31
d0016d88:	e6562170 			; <UNDEFINED> instruction: 0xe6562170
d0016d8c:	24001e6e 	strcs	r1, [r0], #-3694	; 0xfffff192
d0016d90:	f8d9e63c 			; <UNDEFINED> instruction: 0xf8d9e63c
d0016d94:	23000000 	movwcs	r0, #0
d0016d98:	30046802 	andcc	r6, r4, r2, lsl #16
d0016d9c:	0000f8c9 	andeq	pc, r0, r9, asr #17
d0016da0:	bb1bf7ff 	bllt	0xd0714da4
d0016da4:	3000f8d9 	ldrdcc	pc, [r0], -r9
d0016da8:	33046818 	movwcc	r6, #18456	; 0x4818
d0016dac:	f8c917c1 			; <UNDEFINED> instruction: 0xf8c917c1
d0016db0:	f7ff3000 			; <UNDEFINED> instruction: 0xf7ff3000
d0016db4:	bf00bb58 	svclt	0x0000bb58
d0016db8:	fffffc02 			; <UNDEFINED> instruction: 0xfffffc02
d0016dbc:	fffff88e 			; <UNDEFINED> instruction: 0xfffff88e

Disassembly of section .text.vsnprintf:

d0016dc0 <.text.vsnprintf>:
d0016dc0:	b0a7b5f0 	strdlt	fp, [r7], r0	; <UNPREDICTABLE>
d0016dc4:	460e4607 	strmi	r4, [lr], -r7, lsl #12
d0016dc8:	4614461d 			; <UNDEFINED> instruction: 0x4614461d
d0016dcc:	228c2100 	addcs	r2, ip, #0, 2
d0016dd0:	f7fea803 			; <UNDEFINED> instruction: 0xf7fea803
d0016dd4:	9701fc31 	smuadxls	r1, r1, ip
d0016dd8:	95009602 	strls	r9, [r0, #-1538]	; 0xfffff9fe
d0016ddc:	4621b134 			; <UNDEFINED> instruction: 0x4621b134
d0016de0:	a801466a 	stmdage	r1, {r1, r3, r5, r6, r9, sl, lr}
d0016de4:	fa54f7ff 	blx	0xd1554de8
d0016de8:	bdf0b027 	ldcllt	0, cr11, [r0, #156]!	; 0x9c
d0016dec:	30fff04f 	rscscc	pc, pc, pc, asr #32
d0016df0:	bf00e7fa 	svclt	0x0000e7fa

Disassembly of section .text.snprintf:

d0016df4 <.text.snprintf>:
d0016df4:	b500b40c 	strlt	fp, [r0, #-1036]	; 0xfffffbf4
d0016df8:	ab04b083 	blge	0xd014300c
d0016dfc:	2b04f853 	blcs	0xd0154f50
d0016e00:	f7ff9301 			; <UNDEFINED> instruction: 0xf7ff9301
d0016e04:	b003ffdd 	ldrdlt	pc, [r3], -sp
d0016e08:	eb04f85d 	bl	0xd0154f84
d0016e0c:	4770b002 	ldrbmi	fp, [r0, -r2]!

Disassembly of section .text.memchr:

d0016e38 <.text.memchr>:
d0016e38:	4603b192 			; <UNDEFINED> instruction: 0x4603b192
d0016e3c:	b410b2c9 	ldrlt	fp, [r0], #-713	; 0xfffffd37
d0016e40:	e0011884 	and	r1, r1, r4, lsl #17
d0016e44:	d00742a3 	andle	r4, r7, r3, lsr #5
d0016e48:	f8134618 			; <UNDEFINED> instruction: 0xf8134618
d0016e4c:	428a2b01 	addmi	r2, sl, #1024	; 0x400
d0016e50:	f85dd1f8 			; <UNDEFINED> instruction: 0xf85dd1f8
d0016e54:	47704b04 	ldrbmi	r4, [r0, -r4, lsl #22]!
d0016e58:	f85d2000 			; <UNDEFINED> instruction: 0xf85d2000
d0016e5c:	47704b04 	ldrbmi	r4, [r0, -r4, lsl #22]!
d0016e60:	47704610 			; <UNDEFINED> instruction: 0x47704610

Disassembly of section .text.strlen:

d0016e64 <.text.strlen>:
d0016e64:	b1327802 	teqlt	r2, r2, lsl #16
d0016e68:	f8134603 			; <UNDEFINED> instruction: 0xf8134603
d0016e6c:	29001f01 	stmdbcs	r0, {r0, r8, r9, sl, fp, ip}
d0016e70:	1a18d1fb 	bne	0xd064b664
d0016e74:	46104770 			; <UNDEFINED> instruction: 0x46104770
d0016e78:	bf004770 	svclt	0x00004770

Disassembly of section .text.strcmp:

d0016e7c <.text.strcmp>:
d0016e7c:	b1937803 	orrslt	r7, r3, r3, lsl #16
d0016e80:	e002b410 	and	fp, r2, r0, lsl r4
d0016e84:	3f01f810 	svccc	0x0001f810
d0016e88:	460cb143 	strmi	fp, [ip], -r3, asr #2
d0016e8c:	2b01f811 	blcs	0xd0094ed8
d0016e90:	d0f7429a 	smlalsle	r4, r7, sl, r2
d0016e94:	f85d1a98 			; <UNDEFINED> instruction: 0xf85d1a98
d0016e98:	47704b04 	ldrbmi	r4, [r0, -r4, lsl #22]!
d0016e9c:	f85d7862 			; <UNDEFINED> instruction: 0xf85d7862
d0016ea0:	1a984b04 	bne	0xce629ab8
d0016ea4:	780a4770 	stmdavc	sl, {r4, r5, r6, r8, r9, sl, lr}
d0016ea8:	47701a98 			; <UNDEFINED> instruction: 0x47701a98

Disassembly of section .text.strchr:

d0016eac <.text.strchr>:
d0016eac:	7803b2c9 	stmdavc	r3, {r0, r3, r6, r7, r9, ip, sp, pc}
d0016eb0:	d0064299 	mulle	r6, r9, r2
d0016eb4:	f810b123 			; <UNDEFINED> instruction: 0xf810b123
d0016eb8:	428b3f01 	addmi	r3, fp, #1, 30
d0016ebc:	4770d1fa 			; <UNDEFINED> instruction: 0x4770d1fa
d0016ec0:	47704618 			; <UNDEFINED> instruction: 0x47704618

Disassembly of section .text.strrchr:

d0016ec4 <.text.strrchr>:
d0016ec4:	b2c92200 	sbclt	r2, r9, #0, 4
d0016ec8:	4604b410 			; <UNDEFINED> instruction: 0x4604b410
d0016ecc:	3b01f810 	blcc	0xd0094f14
d0016ed0:	bf08428b 	svclt	0x0008428b
d0016ed4:	2b004622 	blcs	0xd0028764
d0016ed8:	4610d1f7 			; <UNDEFINED> instruction: 0x4610d1f7
d0016edc:	4b04f85d 	blmi	0xd0155058
d0016ee0:	bf004770 	svclt	0x00004770
