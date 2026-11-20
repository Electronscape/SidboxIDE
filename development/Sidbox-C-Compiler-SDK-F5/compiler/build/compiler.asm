
/mnt/LinuxDatas/work/SidboxIDE/SidboxIDE/development/Sidbox-C-Compiler-SDK-F5/compiler/build/cgarm/compiler-cgarm/compiler.elf:     file format elf32-littlearm


Disassembly of section .text.initMalloc:

d00215d0 <.text.initMalloc>:
d00215d0:	f44f4b06 			; <UNDEFINED> instruction: 0xf44f4b06
d00215d4:	4a064180 	bmi	0xd01b1bdc
d00215d8:	589a447b 	ldmpl	sl, {r0, r1, r3, r4, r5, r6, sl, lr}
d00215dc:	4a056011 	bmi	0xd0179628
d00215e0:	4b05589a 	blmi	0xd0177850
d00215e4:	601a447b 	andsvs	r4, sl, fp, ror r4
d00215e8:	bf004770 	svclt	0x00004770
d00215ec:	000018e0 	andeq	r1, r0, r0, ror #17
d00215f0:	00000004 	andeq	r0, r0, r4
d00215f4:	00000000 	andeq	r0, r0, r0
d00215f8:	00155790 	mulseq	r5, r0, r7

Disassembly of section .text.applet_entry:

d00215fc <.text.applet_entry>:
d00215fc:	9101b507 	tstls	r1, r7, lsl #10
d0021600:	ffe6f7ff 			; <UNDEFINED> instruction: 0xffe6f7ff
d0021604:	b0039901 	andlt	r9, r3, r1, lsl #18
d0021608:	eb04f85d 	bl	0xd015f784
d002160c:	bd94f7ff 	ldclt	7, cr15, [r4, #1020]	; 0x3fc

Disassembly of section .text.show_status:

d001fad0 <.text.show_status>:
d001fad0:	46024b0d 	strmi	r4, [r2], -sp, lsl #22
d001fad4:	b513447b 	ldrlt	r4, [r3, #-1147]	; 0xfffffb85
d001fad8:	4c0a6818 	stcmi	8, cr6, [sl], {24}
d001fadc:	68a3b138 	stmiavs	r3!, {r3, r4, r5, r8, ip, sp, pc}
d001fae0:	92014611 	andls	r4, r1, #17825792	; 0x1100000
d001fae4:	f8d368db 			; <UNDEFINED> instruction: 0xf8d368db
d001fae8:	479830c4 	ldrmi	r3, [r8, r4, asr #1]
d001faec:	68a39a01 	stmiavs	r3!, {r0, r9, fp, ip, pc}
d001faf0:	49062000 	stmdbmi	r6, {sp}
d001faf4:	4479681b 	ldrbtmi	r6, [r9], #-2075	; 0xfffff7e5
d001faf8:	b002681b 	andlt	r6, r2, fp, lsl r8
d001fafc:	4010e8bd 			; <UNDEFINED> instruction: 0x4010e8bd
d001fb00:	bf004718 	svclt	0x00004718
d001fb04:	2001f000 	andcs	pc, r1, r0
d001fb08:	00155168 	andseq	r5, r5, r8, ror #2
d001fb0c:	ffffffd2 			; <UNDEFINED> instruction: 0xffffffd2

Disassembly of section .text.read_file:

d001fb10 <.text.read_file>:
d001fb10:	41ffe92d 	mvnsmi	lr, sp, lsr #18
d001fb14:	4b1a461e 	blmi	0xd06b1394
d001fb18:	4690460f 	ldrmi	r4, [r0], pc, lsl #12
d001fb1c:	aa01685b 	bge	0xd0079c90
d001fb20:	681d2101 	ldmdavs	sp, {r0, r8, sp}
d001fb24:	47986bab 	ldrmi	r6, [r8, fp, lsr #23]
d001fb28:	4604b120 	strmi	fp, [r4], -r0, lsr #2
d001fb2c:	b0044620 	andlt	r4, r4, r0, lsr #12
d001fb30:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d001fb34:	0002e9cd 	andeq	lr, r2, sp, asr #19
d001fb38:	a9026ceb 	stmdbge	r2, {r0, r1, r3, r5, r6, r7, sl, fp, sp, lr}
d001fb3c:	47989801 	ldrmi	r9, [r8, r1, lsl #16]
d001fb40:	b9784604 	ldmdblt	r8!, {r2, r9, sl, lr}^
d001fb44:	45429a02 	strbmi	r9, [r2, #-2562]	; 0xfffff5fe
d001fb48:	b15ad817 	cmplt	sl, r7, lsl r8
d001fb4c:	ab036bec 	blge	0xd00fab04
d001fb50:	98014639 	stmdals	r1, {r0, r3, r4, r5, r9, sl, lr}
d001fb54:	460447a0 	strmi	r4, [r4], -r0, lsr #15
d001fb58:	e9ddb920 	ldmib	sp, {r5, r8, fp, ip, sp, pc}^
d001fb5c:	1a240402 	bne	0xd0920b6c
d001fb60:	2401bf18 	strcs	fp, [r1], #-3864	; 0xfffff0e8
d001fb64:	98016d6b 	stmdals	r1, {r0, r1, r3, r5, r6, r8, sl, fp, sp, lr}
d001fb68:	2c004798 	stccs	7, cr4, [r0], {152}	; 0x98
d001fb6c:	4604d1de 			; <UNDEFINED> instruction: 0x4604d1de
d001fb70:	d1db2800 	bicsle	r2, fp, r0, lsl #16
d001fb74:	60339b02 	eorsvs	r9, r3, r2, lsl #22
d001fb78:	f06fe7d8 			; <UNDEFINED> instruction: 0xf06fe7d8
d001fb7c:	e7f10402 	ldrb	r0, [r1, r2, lsl #8]!
d001fb80:	2001f000 	andcs	pc, r1, r0

Disassembly of section .text.read_apicore:

d001fba4 <.text.read_apicore>:
d001fba4:	460ab507 	strmi	fp, [sl], -r7, lsl #10
d001fba8:	48064601 	stmdami	r6, {r0, r9, sl, lr}
d001fbac:	4478ab01 	ldrbtmi	sl, [r8], #-2817	; 0xfffff4ff
d001fbb0:	ffaef7ff 			; <UNDEFINED> instruction: 0xffaef7ff
d001fbb4:	9801b918 	stmdals	r1, {r3, r4, r8, fp, ip, sp, pc}
d001fbb8:	f85db003 			; <UNDEFINED> instruction: 0xf85db003
d001fbbc:	2000fb04 	andcs	pc, r0, r4, lsl #22
d001fbc0:	bf00e7fa 	svclt	0x0000e7fa
d001fbc4:	ffffffd2 			; <UNDEFINED> instruction: 0xffffffd2

Disassembly of section .text.open_editor:

d001fc40 <.text.open_editor>:
d001fc40:	47ffe92d 	ldrbmi	lr, [pc, sp, lsr #18]!
d001fc44:	f2404c5d 	vfma.f32	q10, q0, <illegal reg q6.5>
d001fc48:	4607324d 	strmi	r3, [r7], -sp, asr #4
d001fc4c:	68a3210c 	stmiavs	r3!, {r2, r3, r8, sp}
d001fc50:	685b2000 	ldmdavs	fp, {sp}^
d001fc54:	4a5a9202 	bmi	0xd16c4464
d001fc58:	9201447a 	andls	r4, r1, #2046820352	; 0x7a000000
d001fc5c:	728ef44f 	addvc	pc, lr, #1325400064	; 0x4f000000
d001fc60:	22119200 	andscs	r9, r1, #0, 4
d001fc64:	f44f681d 	vst2.8	{d22-d23}, [pc :64]!
d001fc68:	47a873e4 	strmi	r7, [r8, r4, ror #7]!
d001fc6c:	46051e43 	strmi	r1, [r5], -r3, asr #28
d001fc70:	2bfdb2db 	blcs	0xcff8c7e4
d001fc74:	4853d907 	ldmdami	r3, {r0, r1, r2, r8, fp, ip, lr, pc}^
d001fc78:	f7ff4478 			; <UNDEFINED> instruction: 0xf7ff4478
d001fc7c:	2001ff29 	andcs	pc, r1, r9, lsr #30
d001fc80:	e8bdb004 	pop	{r2, ip, sp, pc}
d001fc84:	4e5087f0 	mrcmi	7, 2, r8, cr0, cr0, {7}
d001fc88:	447e212f 	ldrbtmi	r2, [lr], #-303	; 0xfffffed1
d001fc8c:	f0034630 			; <UNDEFINED> instruction: 0xf0034630
d001fc90:	68a2f905 	stmiavs	r2!, {r0, r2, r8, fp, ip, sp, lr, pc}
d001fc94:	68d24603 	ldmvs	r2, {r0, r1, r9, sl, lr}^
d001fc98:	8018f8d2 			; <UNDEFINED> instruction: 0x8018f8d2
d001fc9c:	d07a2800 	rsbsle	r2, sl, r0, lsl #16
d001fca0:	26013301 	strcs	r3, [r1], -r1, lsl #6
d001fca4:	23109301 	tstcs	r0, #67108864	; 0x4000000
d001fca8:	21082209 	tstcs	r8, r9, lsl #4
d001fcac:	93004628 	movwls	r4, #1576	; 0x628
d001fcb0:	7387f44f 	orrvc	pc, r7, #1325400064	; 0x4f000000
d001fcb4:	f04f9602 			; <UNDEFINED> instruction: 0xf04f9602
d001fcb8:	47c00918 	bfimi	r0, r8, (invalid: 18:0)
d001fcbc:	4a4368a3 	bmi	0xd10f9f50
d001fcc0:	718ff44f 	orrvc	pc, pc, pc, asr #8
d001fcc4:	468068db 	pkhtbmi	r6, r0, fp, asr #17
d001fcc8:	f8cd447a 			; <UNDEFINED> instruction: 0xf8cd447a
d001fccc:	96029000 	strls	r9, [r2], -r0
d001fcd0:	92014628 	andls	r4, r1, #40, 12	; 0x2800000
d001fcd4:	f8d32204 			; <UNDEFINED> instruction: 0xf8d32204
d001fcd8:	2344a008 	movtcs	sl, #16392	; 0x4008
d001fcdc:	4b3c47d0 	blmi	0xd0f31c24
d001fce0:	f44f4a3c 	vst1.8	{d20-d21}, [pc :256], ip
d001fce4:	447b71b4 	ldrbtmi	r7, [fp], #-436	; 0xfffffe4c
d001fce8:	6018447a 	andsvs	r4, r8, sl, ror r4
d001fcec:	68a34628 	stmiavs	r3!, {r3, r5, r9, sl, lr}
d001fcf0:	920168db 	andls	r6, r1, #14352384	; 0xdb0000
d001fcf4:	96022204 	strls	r2, [r2], -r4, lsl #4
d001fcf8:	9000f8cd 	andls	pc, r0, sp, asr #17
d001fcfc:	9008f8d3 	ldrdls	pc, [r8], -r3
d001fd00:	47c8234e 	strbmi	r2, [r8, lr, asr #6]
d001fd04:	22004b34 	andcs	r4, r0, #52, 22	; 0xd000
d001fd08:	447b2108 	ldrbtmi	r2, [fp], #-264	; 0xfffffef8
d001fd0c:	46286018 			; <UNDEFINED> instruction: 0x46286018
d001fd10:	68db68a3 	ldmvs	fp, {r0, r1, r5, r7, fp, sp, lr}^
d001fd14:	4a319202 	bmi	0xd0c84524
d001fd18:	447a9603 	ldrbtmi	r9, [sl], #-1539	; 0xfffff9fd
d001fd1c:	22c19201 	sbccs	r9, r1, #268435456	; 0x10000000
d001fd20:	22229200 	eorcs	r9, r2, #0, 4
d001fd24:	9034f8d3 	ldrsbtls	pc, [r4], -r3	; <UNPREDICTABLE>
d001fd28:	73d7f44f 	bicsvc	pc, r7, #1325400064	; 0x4f000000
d001fd2c:	4b2c47c8 	blmi	0xd0b31c54
d001fd30:	6018447b 	andsvs	r4, r8, fp, ror r4
d001fd34:	68db68a3 	ldmvs	fp, {r0, r1, r5, r7, fp, sp, lr}^
d001fd38:	9018f8d3 			; <UNDEFINED> instruction: 0x9018f8d3
d001fd3c:	d12c2f00 			; <UNDEFINED> instruction: 0xd12c2f00
d001fd40:	447b4b28 	ldrbtmi	r4, [fp], #-2856	; 0xfffff4d8
d001fd44:	23129301 	tstcs	r2, #67108864	; 0x4000000
d001fd48:	210822eb 	smlattcs	r8, fp, r2, r2
d001fd4c:	46289300 	strtmi	r9, [r8], -r0, lsl #6
d001fd50:	73d7f44f 	bicsvc	pc, r7, #1325400064	; 0x4f000000
d001fd54:	47c89602 	strbmi	r9, [r8, r2, lsl #12]
d001fd58:	447b4b23 	ldrbtmi	r4, [fp], #-2851	; 0xfffff4dd
d001fd5c:	f1b86018 			; <UNDEFINED> instruction: 0xf1b86018
d001fd60:	d00c0f00 	andle	r0, ip, r0, lsl #30
d001fd64:	447b4b21 	ldrbtmi	r4, [fp], #-2849	; 0xfffff4df
d001fd68:	b143681b 	cmplt	r3, fp, lsl r8
d001fd6c:	447b4b20 	ldrbtmi	r4, [fp], #-2848	; 0xfffff4e0
d001fd70:	b123681b 			; <UNDEFINED> instruction: 0xb123681b
d001fd74:	447e4e1f 	ldrbtmi	r4, [lr], #-3615	; 0xfffff1e1
d001fd78:	b1036833 	tstlt	r3, r3, lsr r8
d001fd7c:	68a3b980 	stmiavs	r3!, {r7, r8, fp, ip, sp, pc}
d001fd80:	685b4628 	ldmdavs	fp, {r3, r5, r9, sl, lr}^
d001fd84:	4798685b 			; <UNDEFINED> instruction: 0x4798685b
d001fd88:	22004b1b 	andcs	r4, r0, #27648	; 0x6c00
d001fd8c:	447b481b 	ldrbtmi	r4, [fp], #-2075	; 0xfffff7e5
d001fd90:	601a4478 	andsvs	r4, sl, r8, ror r4
d001fd94:	4633e771 			; <UNDEFINED> instruction: 0x4633e771
d001fd98:	4b19e783 	blmi	0xd0699bac
d001fd9c:	e7d1447b 			; <UNDEFINED> instruction: 0xe7d1447b
d001fda0:	462868a3 	strtmi	r6, [r8], -r3, lsr #17
d001fda4:	685b4917 	ldmdavs	fp, {r0, r1, r2, r4, r8, fp, lr}^
d001fda8:	689b4479 	ldmvs	fp, {r0, r3, r4, r5, r6, sl, lr}
d001fdac:	68a34798 	stmiavs	r3!, {r3, r4, r7, r8, r9, sl, lr}
d001fdb0:	68db6830 	ldmvs	fp, {r4, r5, fp, sp, lr}^
d001fdb4:	47986ddb 			; <UNDEFINED> instruction: 0x47986ddb
d001fdb8:	e7612000 	strb	r2, [r1, -r0]!
d001fdbc:	2001f000 	andcs	pc, r1, r0
d001fdc0:	ffffff8a 			; <UNDEFINED> instruction: 0xffffff8a
d001fdc4:	ffffff73 			; <UNDEFINED> instruction: 0xffffff73
d001fdc8:	00154c32 	andseq	r4, r5, r2, lsr ip
d001fdcc:	ffffff3f 			; <UNDEFINED> instruction: 0xffffff3f
d001fdd0:	00054bc2 	andeq	r4, r5, r2, asr #23
d001fdd4:	ffffff24 			; <UNDEFINED> instruction: 0xffffff24
d001fdd8:	00053aaa 	andeq	r3, r5, sl, lsr #21
d001fddc:	00054b92 	muleq	r5, r2, fp
d001fde0:	00053ae4 	andeq	r3, r5, r4, ror #21
d001fde4:	fffffe92 			; <UNDEFINED> instruction: 0xfffffe92
d001fde8:	00154ee2 	andseq	r4, r5, r2, ror #29
d001fdec:	00054b42 	andeq	r4, r5, r2, asr #22
d001fdf0:	00053a46 	andeq	r3, r5, r6, asr #20
d001fdf4:	00053a9e 	muleq	r5, lr, sl
d001fdf8:	00154eae 	andseq	r4, r5, lr, lsr #29
d001fdfc:	fffffe82 			; <UNDEFINED> instruction: 0xfffffe82
d001fe00:	fffffe28 			; <UNDEFINED> instruction: 0xfffffe28
d001fe04:	00000dbd 			; <UNDEFINED> instruction: 0x00000dbd

Disassembly of section .text.stream_open_file:

d001fe08 <.text.stream_open_file>:
d001fe08:	4e0cb570 	cfrshl64mi	mvdx12, mvdx0, fp
d001fe0c:	f241460c 	vmax.s8	d20, d1, d12
d001fe10:	21000218 	tstcs	r0, r8, lsl r2
d001fe14:	f0014605 			; <UNDEFINED> instruction: 0xf0014605
d001fe18:	6873fbfb 	ldmdavs	r3!, {r0, r1, r3, r4, r5, r6, r7, r8, r9, fp, ip, sp, lr, pc}^
d001fe1c:	681b4620 	ldmdavs	fp, {r5, r9, sl, lr}
d001fe20:	47986d9b 			; <UNDEFINED> instruction: 0x47986d9b
d001fe24:	462a6873 			; <UNDEFINED> instruction: 0x462a6873
d001fe28:	681b2107 	ldmdavs	fp, {r0, r1, r2, r8, sp}
d001fe2c:	6b9b4620 	blvs	0xce6f16b4
d001fe30:	fab04798 	blx	0xcec31c98
d001fe34:	0940f080 	stmdbeq	r0, {r7, ip, sp, lr, pc}^
d001fe38:	bf00bd70 	svclt	0x0000bd70
d001fe3c:	2001f000 	andcs	pc, r1, r0

Disassembly of section .text.stream_flush_page.part.0:

d001fe40 <.text.stream_flush_page.part.0>:
d001fe40:	685b4b16 	ldmdavs	fp, {r1, r2, r4, r8, r9, fp, lr}^
d001fe44:	681fb5f7 	ldmdavs	pc, {r0, r1, r2, r4, r5, r6, r7, r8, sl, ip, sp, pc}	; <UNPREDICTABLE>
d001fe48:	0504f241 	streq	pc, [r4, #-577]	; 0xfffffdbf
d001fe4c:	46042300 	strmi	r2, [r4], -r0, lsl #6
d001fe50:	93015941 	movwls	r5, #6465	; 0x1941
d001fe54:	6c7b6800 	ldclvs	8, cr6, [fp], #-0
d001fe58:	b1104798 			; <UNDEFINED> instruction: 0xb1104798
d001fe5c:	b0032000 	andlt	r2, r3, r0
d001fe60:	f241bdf0 	vmla.f32	<illegal reg q13.5>, <illegal reg q8.5>, q8
d001fe64:	6c3f0608 	ldcvs	6, cr0, [pc], #-32	; 0xd001fe4c
d001fe68:	1d21ab01 	fstmdbxne	r1!, {d10-d9}	;@ Deprecated
d001fe6c:	682059a2 	stmdavs	r0!, {r1, r5, r7, r8, fp, ip, lr}
d001fe70:	280047b8 	stmdacs	r0, {r3, r4, r5, r7, r8, r9, sl, lr}
d001fe74:	59a3d1f2 	stmibpl	r3!, {r1, r4, r5, r6, r7, r8, ip, lr, pc}
d001fe78:	42939a01 	addsmi	r9, r3, #4096	; 0x1000
d001fe7c:	5962d1ee 	stmdbpl	r2!, {r1, r2, r3, r5, r6, r7, r8, ip, lr, pc}^
d001fe80:	44132001 	ldrmi	r2, [r3], #-1
d001fe84:	020cf241 	andeq	pc, ip, #268435460	; 0x10000004
d001fe88:	428b58a1 	addmi	r5, fp, #10551296	; 0xa10000
d001fe8c:	50a3bf88 	adcpl	fp, r3, r8, lsl #31
d001fe90:	0314f241 	tsteq	r4, #268435460	; 0x10000004	; <UNPREDICTABLE>
d001fe94:	50e22200 	rscpl	r2, r2, r0, lsl #4
d001fe98:	bf00e7e1 	svclt	0x0000e7e1
d001fe9c:	2001f000 	andcs	pc, r1, r0

Disassembly of section .text.stream_io_read:

d001fea0 <.text.stream_io_read>:
d001fea0:	43f7e92d 	mvnsmi	lr, #737280	; 0xb4000
d001fea4:	46059f0a 	strmi	r9, [r5], -sl, lsl #30
d001fea8:	46984616 			; <UNDEFINED> instruction: 0x46984616
d001feac:	f500b161 			; <UNDEFINED> instruction: 0xf500b161
d001feb0:	34185480 	ldrcc	r5, [r8], #-1152	; 0xfffffb80
d001feb4:	b94b6823 	stmdblt	fp, {r0, r1, r5, fp, sp, lr}^
d001feb8:	1330f242 	teqne	r0, #536870916	; 0x20000004	; <UNPREDICTABLE>
d001febc:	20002201 	andcs	r2, r0, r1, lsl #4
d001fec0:	b00350ea 	andlt	r5, r3, sl, ror #1
d001fec4:	83f0e8bd 	mvnshi	lr, #12386304	; 0xbd0000
d001fec8:	e7f34604 	ldrb	r4, [r3, r4, lsl #12]!
d001fecc:	0314f241 	tsteq	r4, #268435460	; 0x10000004	; <UNPREDICTABLE>
d001fed0:	bb1b58e3 	bllt	0xd06f6264
d001fed4:	030cf241 	movweq	pc, #49729	; 0xc241	; <UNPREDICTABLE>
d001fed8:	429658e2 	addsmi	r5, r6, #14811136	; 0xe20000
d001fedc:	1b92d8ec 	blne	0xce4d6294
d001fee0:	d8e94297 	stmiale	r9!, {r0, r1, r2, r4, r7, r9, lr}^
d001fee4:	4b10b1c7 	blmi	0xd044c608
d001fee8:	68204631 	stmdavs	r0!, {r0, r4, r5, r9, sl, lr}
d001feec:	f8d3685b 			; <UNDEFINED> instruction: 0xf8d3685b
d001fef0:	23009000 	movwcs	r9, #0
d001fef4:	f8d99301 			; <UNDEFINED> instruction: 0xf8d99301
d001fef8:	47983044 	ldrmi	r3, [r8, r4, asr #32]
d001fefc:	d1db2800 	bicsle	r2, fp, r0, lsl #16
d001ff00:	603cf8d9 	ldrsbtvs	pc, [ip], -r9	; <UNPREDICTABLE>
d001ff04:	463aab01 	ldrtmi	sl, [sl], -r1, lsl #22
d001ff08:	68204641 	stmdavs	r0!, {r0, r6, r9, sl, lr}
d001ff0c:	280047b0 	stmdacs	r0, {r4, r5, r7, r8, r9, sl, lr}
d001ff10:	9b01d1d2 	blls	0xd0094660
d001ff14:	d1cf429f 			; <UNDEFINED> instruction: 0xd1cf429f
d001ff18:	e7d22001 	ldrb	r2, [r2, r1]
d001ff1c:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d001ff20:	2800ff8f 	stmdacs	r0, {r0, r1, r2, r3, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d001ff24:	e7d5d0c8 	ldrb	sp, [r5, r8, asr #1]
d001ff28:	2001f000 	andcs	pc, r1, r0

Disassembly of section .text.progress_proc:

d001ff2c <.text.progress_proc>:
d001ff2c:	680bb171 	stmdavs	fp, {r0, r4, r5, r6, r8, ip, sp, pc}
d001ff30:	d10b2b20 	tstle	fp, r0, lsr #22
d001ff34:	f5b368cb 			; <UNDEFINED> instruction: 0xf5b368cb
d001ff38:	d1075f80 	smlabble	r7, r0, pc, r5	; <UNPREDICTABLE>
d001ff3c:	447b4b04 	ldrbtmi	r4, [fp], #-2820	; 0xfffff4fc
d001ff40:	2b00681b 	blcs	0xd0039fb4
d001ff44:	2000bf0c 	andcs	fp, r0, ip, lsl #30
d001ff48:	477020f0 			; <UNDEFINED> instruction: 0x477020f0
d001ff4c:	47702000 	ldrbmi	r2, [r0, -r0]!
d001ff50:	000538d2 	ldrdeq	r3, [r5], -r2

Disassembly of section .text.console_compile_progress:

d001ff90 <.text.console_compile_progress>:
d001ff90:	43f7e92d 	mvnsmi	lr, #737280	; 0xb4000
d001ff94:	461c4d3f 			; <UNDEFINED> instruction: 0x461c4d3f
d001ff98:	4690460f 	ldrmi	r4, [r0], pc, lsl #12
d001ff9c:	2b0068ab 	blcs	0xd003a250
d001ffa0:	68abd074 	stmiavs	fp!, {r2, r4, r5, r6, ip, lr, pc}
d001ffa4:	2b00681b 	blcs	0xd003a018
d001ffa8:	bb24d070 	bllt	0xd0954170
d001ffac:	460a68ab 	strmi	r6, [sl], -fp, lsr #17
d001ffb0:	46204939 			; <UNDEFINED> instruction: 0x46204939
d001ffb4:	4479681b 	ldrbtmi	r6, [r9], #-2075	; 0xfffff7e5
d001ffb8:	4798681b 			; <UNDEFINED> instruction: 0x4798681b
d001ffbc:	447b4b37 	ldrbtmi	r4, [fp], #-2871	; 0xfffff4c9
d001ffc0:	2b00681b 	blcs	0xd003a034
d001ffc4:	2c00d062 	stccs	0, cr13, [r0], {98}	; 0x62
d001ffc8:	4a35d13c 	bmi	0xd0d944c0
d001ffcc:	4835463b 	ldmdami	r5!, {r0, r1, r3, r4, r5, r9, sl, lr}
d001ffd0:	71c0f44f 	bicvc	pc, r0, pc, asr #8
d001ffd4:	4478447a 	ldrbtmi	r4, [r8], #-1146	; 0xfffffb86
d001ffd8:	fef8f002 	cdp2	0, 15, cr15, cr8, cr2, {0}
d001ffdc:	4a3268ab 	bmi	0xd0cba290
d001ffe0:	447a68db 	ldrbtmi	r6, [sl], #-2267	; 0xfffff725
d001ffe4:	f8d34931 			; <UNDEFINED> instruction: 0xf8d34931
d001ffe8:	447930c4 	ldrbtmi	r3, [r9], #-196	; 0xffffff3c
d001ffec:	b0036810 	andlt	r6, r3, r0, lsl r8
d001fff0:	43f0e8bd 	mvnsmi	lr, #12386304	; 0xbd0000
d001fff4:	20644718 	rsbcs	r4, r4, r8, lsl r7
d001fff8:	fbb42300 	blx	0xced28c02
d001fffc:	4681f6f0 			; <UNDEFINED> instruction: 0x4681f6f0
d0020000:	4c16fb00 			; <UNDEFINED> instruction: 0x4c16fb00
d0020004:	0e01f100 	mvfeqs	f7, f0
d0020008:	d30b4283 	movwle	r4, #45699	; 0xb283
d002000c:	200068aa 	andcs	r6, r0, sl, lsr #17
d0020010:	68124927 	ldmdavs	r2, {r0, r1, r2, r5, r8, fp, lr}
d0020014:	94014479 	strls	r4, [r1], #-1145	; 0xfffffb87
d0020018:	8000f8cd 	andhi	pc, r0, sp, asr #17
d002001c:	463a6816 			; <UNDEFINED> instruction: 0x463a6816
d0020020:	e7cb47b0 			; <UNDEFINED> instruction: 0xe7cb47b0
d0020024:	0103eb0e 	tsteq	r3, lr, lsl #22
d0020028:	fb010849 	blx	0xd0062156
d002002c:	3263f20c 	rsbcc	pc, r3, #12, 4	; 0xc0000000
d0020030:	f2f9fbb2 			; <UNDEFINED> instruction: 0xf2f9fbb2
d0020034:	2206fb01 	andcs	pc, r6, #1024	; 0x400
d0020038:	d2014590 	andle	r4, r1, #144, 10	; 0x24000000
d002003c:	e7e11e48 	strb	r1, [r1, r8, asr #28]!
d0020040:	e7e1460b 	strb	r4, [r1, fp, lsl #12]!
d0020044:	21002064 	tstcs	r0, r4, rrx
d0020048:	fcf0fbb4 	ldc2l	11, cr15, [r0], #720	; 0x2d0	; <UNPREDICTABLE>
d002004c:	fb004686 	blx	0xd0031a6e
d0020050:	1c43441c 	cfstrdne	mvd4, [r3], {28}
d0020054:	d30a4281 	movwle	r4, #41601	; 0xa281
d0020058:	463b4a16 			; <UNDEFINED> instruction: 0x463b4a16
d002005c:	91004816 	tstls	r0, r6, lsl r8
d0020060:	f44f447a 	vst3.16	{d20-d22}, [pc :256], sl
d0020064:	447871c0 	ldrbtmi	r7, [r8], #-448	; 0xfffffe40
d0020068:	feb0f002 	cdp2	0, 11, cr15, cr0, cr2, {0}
d002006c:	185ae7b6 	ldmdane	sl, {r1, r2, r4, r5, r7, r8, r9, sl, sp, lr, pc}^
d0020070:	fb020852 	blx	0xd00a21c2
d0020074:	3663f604 	strbtcc	pc, [r3], -r4, lsl #12	; <UNPREDICTABLE>
d0020078:	f6fefbb6 			; <UNDEFINED> instruction: 0xf6fefbb6
d002007c:	660cfb02 	strvs	pc, [ip], -r2, lsl #22
d0020080:	d20145b0 	andle	r4, r1, #176, 10	; 0x2c000000
d0020084:	e7e41e50 	ubfx	r1, r0, #28, #5
d0020088:	e7e34611 			; <UNDEFINED> instruction: 0xe7e34611
d002008c:	e8bdb003 	pop	{r0, r1, ip, sp, pc}
d0020090:	bf0083f0 	svclt	0x000083f0
d0020094:	2001f000 	andcs	pc, r1, r0
d0020098:	ffffff9a 			; <UNDEFINED> instruction: 0xffffff9a
d002009c:	00154c7e 	andseq	r4, r5, lr, ror ip
d00200a0:	ffffffa8 			; <UNDEFINED> instruction: 0xffffffa8
d00200a4:	00154ae6 	andseq	r4, r5, r6, ror #21
d00200a8:	00154c5a 	andseq	r4, r5, sl, asr ip
d00200ac:	00154ad2 			; <UNDEFINED> instruction: 0x00154ad2
d00200b0:	ffffff4a 			; <UNDEFINED> instruction: 0xffffff4a
d00200b4:	ffffff22 			; <UNDEFINED> instruction: 0xffffff22
d00200b8:	00154a56 	andseq	r4, r5, r6, asr sl

Disassembly of section .text.report_file:

d0020164 <.text.report_file>:
d0020164:	460bb537 			; <UNDEFINED> instruction: 0x460bb537
d0020168:	b3284604 			; <UNDEFINED> instruction: 0xb3284604
d002016c:	d1081cc5 	smlabtle	r8, r5, ip, r1
d0020170:	44784812 	ldrbtmi	r4, [r8], #-2066	; 0xfffff7ee
d0020174:	fcacf7ff 	stc2	7, cr15, [ip], #1020	; 0x3fc
d0020178:	42581c63 	subsmi	r1, r8, #25344	; 0x6300
d002017c:	b0034158 	andlt	r4, r3, r8, asr r1
d0020180:	1d20bd30 	stcne	13, cr11, [r0, #-192]!	; 0xffffff40
d0020184:	480ed102 	stmdami	lr, {r1, r8, ip, lr, pc}
d0020188:	e7f34478 			; <UNDEFINED> instruction: 0xe7f34478
d002018c:	d1021ca1 	smlatble	r2, r1, ip, r1
d0020190:	4478480c 	ldrbtmi	r4, [r8], #-2060	; 0xfffff7f4
d0020194:	1c62e7ee 	stclne	7, cr14, [r2], #-952	; 0xfffffc48
d0020198:	480bd102 	stmdami	fp, {r1, r8, ip, lr, pc}
d002019c:	e7e94478 			; <UNDEFINED> instruction: 0xe7e94478
d00201a0:	f44f4d0a 			; <UNDEFINED> instruction: 0xf44f4d0a
d00201a4:	4a0a71c0 	bmi	0xd02bc8ac
d00201a8:	9400447d 	strls	r4, [r0], #-1149	; 0xfffffb83
d00201ac:	4628447a 			; <UNDEFINED> instruction: 0x4628447a
d00201b0:	fe0cf002 	cdp2	0, 0, cr15, cr12, cr2, {0}
d00201b4:	e7dd4628 	ldrb	r4, [sp, r8, lsr #12]
d00201b8:	e7e02001 	strb	r2, [r0, r1]!
d00201bc:	ffffff46 			; <UNDEFINED> instruction: 0xffffff46
d00201c0:	ffffff45 			; <UNDEFINED> instruction: 0xffffff45
d00201c4:	ffffff56 			; <UNDEFINED> instruction: 0xffffff56
d00201c8:	ffffff78 			; <UNDEFINED> instruction: 0xffffff78
d00201cc:	00154914 	andseq	r4, r5, r4, lsl r9
d00201d0:	ffffff97 			; <UNDEFINED> instruction: 0xffffff97

Disassembly of section .text.read_header:

d00201d4 <.text.read_header>:
d00201d4:	47f0e92d 	ldrbmi	lr, [r0, sp, lsr #18]!
d00201d8:	460d9f09 	strmi	r9, [sp], -r9, lsl #30
d00201dc:	46984616 			; <UNDEFINED> instruction: 0x46984616
d00201e0:	b9104681 	ldmdblt	r0, {r0, r7, r9, sl, lr}
d00201e4:	e8bd2000 	ldmfd	sp!, {sp}
d00201e8:	290087f0 	stmdbcs	r0, {r4, r5, r6, r7, r8, r9, sl, pc}
d00201ec:	780bd0fa 	stmdavc	fp, {r1, r3, r4, r5, r6, r7, ip, lr, pc}
d00201f0:	d0f72b00 	rscsle	r2, r7, r0, lsl #22
d00201f4:	d0f52b2f 	rscsle	r2, r5, pc, lsr #22
d00201f8:	4628213a 			; <UNDEFINED> instruction: 0x4628213a
d00201fc:	fe42f002 	cdp2	0, 4, cr15, cr2, cr2, {0}
d0020200:	d1ef2800 	mvnle	r2, r0, lsl #16
d0020204:	4648212f 	strbmi	r2, [r8], -pc, lsr #2
d0020208:	fe48f002 	cdp2	0, 4, cr15, cr8, cr2, {0}
d002020c:	d0e92800 	rscle	r2, r9, r0, lsl #16
d0020210:	0409eba0 	streq	lr, [r9], #-2976	; 0xfffff460
d0020214:	f0024628 			; <UNDEFINED> instruction: 0xf0024628
d0020218:	9a0afe11 	bls	0xd02dfa64
d002021c:	46823401 	strmi	r3, [r2], r1, lsl #8
d0020220:	429a1823 	addsmi	r1, sl, #2293760	; 0x230000
d0020224:	4622d9de 			; <UNDEFINED> instruction: 0x4622d9de
d0020228:	46384649 	ldrtmi	r4, [r8], -r9, asr #12
d002022c:	f9fef001 			; <UNDEFINED> instruction: 0xf9fef001
d0020230:	0201f10a 	andeq	pc, r1, #-2147483646	; 0x80000002
d0020234:	19384629 	ldmdbne	r8!, {r0, r3, r5, r9, sl, lr}
d0020238:	f9f8f001 			; <UNDEFINED> instruction: 0xf9f8f001
d002023c:	9b08b14e 	blls	0xd024c77c
d0020240:	46314642 	ldrtmi	r4, [r1], -r2, asr #12
d0020244:	f7ff4638 			; <UNDEFINED> instruction: 0xf7ff4638
d0020248:	fab0fc63 	blx	0xcec5f3dc
d002024c:	0940f080 	stmdbeq	r0, {r7, ip, sp, lr, pc}^
d0020250:	2001e7c9 	andcs	lr, r1, r9, asr #15
d0020254:	Address 0x00000000d0020254 is out of bounds.


Disassembly of section .text.resolve_path.constprop.0:

d0020264 <.text.resolve_path.constprop.0>:
d0020264:	460fb5f7 			; <UNDEFINED> instruction: 0x460fb5f7
d0020268:	46044616 			; <UNDEFINED> instruction: 0x46044616
d002026c:	2000b910 	andcs	fp, r0, r0, lsl r9
d0020270:	bdf0b003 	ldcllt	0, cr11, [r0, #12]!
d0020274:	2b007803 	blcs	0xd003e288
d0020278:	f002d0f9 			; <UNDEFINED> instruction: 0xf002d0f9
d002027c:	4605fddf 			; <UNDEFINED> instruction: 0x4605fddf
d0020280:	f0024638 			; <UNDEFINED> instruction: 0xf0024638
d0020284:	4285fddb 	addmi	pc, r5, #14016	; 0x36c0
d0020288:	1a2bd9f1 	bne	0xd0b16a54
d002028c:	44253f01 	strtmi	r3, [r5], #-3841	; 0xfffff0ff
d0020290:	42ab4423 	adcmi	r4, fp, #587202560	; 0x23000000
d0020294:	213ad118 	teqcs	sl, r8, lsl r1
d0020298:	f0024620 			; <UNDEFINED> instruction: 0xf0024620
d002029c:	7823fdf3 	stmdavc	r3!, {r0, r1, r4, r5, r6, r7, r8, sl, fp, ip, sp, lr, pc}
d00202a0:	d0032b2f 	andle	r2, r3, pc, lsr #22
d00202a4:	7843b1d8 	stmdavc	r3, {r3, r4, r6, r7, r8, ip, sp, pc}^
d00202a8:	d1e02b2f 	mvnle	r2, pc, lsr #22
d00202ac:	46234a21 	strtmi	r4, [r3], -r1, lsr #20
d00202b0:	7180f44f 	orrvc	pc, r0, pc, asr #8
d00202b4:	447a4630 	ldrbtmi	r4, [sl], #-1584	; 0xfffff9d0
d00202b8:	fd88f002 	stc2	0, cr15, [r8, #8]
d00202bc:	28fe3801 	ldmcs	lr!, {r0, fp, ip, sp}^
d00202c0:	2000bf8c 	andcs	fp, r0, ip, lsl #31
d00202c4:	e7d32001 	ldrb	r2, [r3, r1]
d00202c8:	1b01f813 	blne	0xd009e31c
d00202cc:	2f01f817 	svccs	0x0001f817
d00202d0:	0120f041 	msreq	CPSR_, r1, asr #32
d00202d4:	0220f042 	eoreq	pc, r0, #66	; 0x42
d00202d8:	d0da4291 	smullsle	r4, sl, r1, r2
d00202dc:	4b14e7c7 	blmi	0xd055a200
d00202e0:	7180f44f 	orrvc	pc, r0, pc, asr #8
d00202e4:	685b4d14 	ldmdavs	fp, {r2, r4, r8, sl, fp, lr}^
d00202e8:	681b447d 	ldmdavs	fp, {r0, r2, r3, r4, r5, r6, sl, lr}
d00202ec:	69db4628 	ldmibvs	fp, {r3, r5, r9, sl, lr}^
d00202f0:	28004798 	stmdacs	r0, {r3, r4, r7, r8, r9, sl, lr}
d00202f4:	782bd1bb 	stmdavc	fp!, {r0, r1, r3, r4, r5, r7, r8, ip, lr, pc}
d00202f8:	d0b82b00 	adcsle	r2, r8, r0, lsl #22
d00202fc:	f0024628 			; <UNDEFINED> instruction: 0xf0024628
d0020300:	4428fd9d 	strtmi	pc, [r8], #-3485	; 0xfffff263
d0020304:	3c01f810 	stccc	8, cr15, [r1], {16}
d0020308:	d00d2b2f 	andle	r2, sp, pc, lsr #22
d002030c:	447b4b0b 	ldrbtmi	r4, [fp], #-2827	; 0xfffff4f5
d0020310:	f44f4a0b 	vst1.8	{d20-d21}, [pc], fp
d0020314:	46307180 	ldrtmi	r7, [r0], -r0, lsl #3
d0020318:	e9cd447a 	stmib	sp, {r1, r3, r4, r5, r6, sl, lr}^
d002031c:	4b093400 	blmi	0xd026d324
d0020320:	f002447b 			; <UNDEFINED> instruction: 0xf002447b
d0020324:	e7c9fd53 			; <UNDEFINED> instruction: 0xe7c9fd53
d0020328:	447b4b07 	ldrbtmi	r4, [fp], #-2823	; 0xfffff4f9
d002032c:	bf00e7f0 	svclt	0x0000e7f0
d0020330:	2001f000 	andcs	pc, r1, r0
d0020334:	ffffff9f 			; <UNDEFINED> instruction: 0xffffff9f
d0020338:	001546d4 			; <UNDEFINED> instruction: 0x001546d4
d002033c:	ffffff45 			; <UNDEFINED> instruction: 0xffffff45
d0020340:	ffffff40 			; <UNDEFINED> instruction: 0xffffff40
d0020344:	0015469c 	mulseq	r5, ip, r6
d0020348:	ffffff28 			; <UNDEFINED> instruction: 0xffffff28

Disassembly of section .text.stream_close_file:

d002034c <.text.stream_close_file>:
d002034c:	b5706803 	ldrblt	r6, [r0, #-2051]!	; 0xfffff7fd
d0020350:	b9134605 	ldmdblt	r3, {r0, r2, r9, sl, lr}
d0020354:	46202401 	strtmi	r2, [r0], -r1, lsl #8
d0020358:	f241bd70 	vmla.f32	<illegal reg q13.5>, <illegal reg q0.5>, q8
d002035c:	4e0f0314 	mcrmi	3, 0, r0, cr15, cr4, {0}
d0020360:	b9a358c3 	stmiblt	r3!, {r0, r1, r6, r7, fp, ip, lr}
d0020364:	68286873 	stmdavs	r8!, {r0, r1, r4, r5, r6, fp, sp, lr}
d0020368:	6d1b681b 	ldcvs	8, cr6, [fp, #-108]	; 0xffffff94
d002036c:	fab04798 	blx	0xcec321d4
d0020370:	0964f480 	stmdbeq	r4!, {r7, sl, ip, sp, lr, pc}^
d0020374:	68286873 	stmdavs	r8!, {r0, r1, r4, r5, r6, fp, sp, lr}
d0020378:	6d5b681b 	ldclvs	8, cr6, [fp, #-108]	; 0xffffff94
d002037c:	23004798 	movwcs	r4, #1944	; 0x798
d0020380:	2c00602b 	stccs	0, cr6, [r0], {43}	; 0x2b
d0020384:	2800d0e7 	stmdacs	r0, {r0, r1, r2, r5, r6, r7, ip, lr, pc}
d0020388:	461cd0e4 	ldrmi	sp, [ip], -r4, ror #1
d002038c:	f7ffe7e3 			; <UNDEFINED> instruction: 0xf7ffe7e3
d0020390:	4604fd57 			; <UNDEFINED> instruction: 0x4604fd57
d0020394:	d0ed2800 	rscle	r2, sp, r0, lsl #16
d0020398:	bf00e7e4 	svclt	0x0000e7e4
d002039c:	2001f000 	andcs	pc, r1, r0

Disassembly of section .text.stream_finish_app:

d00203c8 <.text.stream_finish_app>:
d00203c8:	43f0e92d 	mvnsmi	lr, #737280	; 0xb4000
d00203cc:	b0874c53 	addlt	r4, r7, r3, asr ip
d00203d0:	460f4680 	strmi	r4, [pc], -r0, lsl #13
d00203d4:	f944f7fe 			; <UNDEFINED> instruction: 0xf944f7fe
d00203d8:	447c2100 	ldrbtmi	r2, [ip], #-256	; 0xffffff00
d00203dc:	9140f8df 	ldrdls	pc, [r0, #-143]	; 0xffffff71
d00203e0:	f7fe4608 			; <UNDEFINED> instruction: 0xf7fe4608
d00203e4:	f504f855 			; <UNDEFINED> instruction: 0xf504f855
d00203e8:	464e5080 	strbmi	r5, [lr], -r0, lsl #1
d00203ec:	f7ff3018 			; <UNDEFINED> instruction: 0xf7ff3018
d00203f0:	4605ffad 	strmi	pc, [r5], -sp, lsr #31
d00203f4:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d00203f8:	f8d9ffa9 			; <UNDEFINED> instruction: 0xf8d9ffa9
d00203fc:	28003004 	stmdacs	r0, {r2, ip, sp}
d0020400:	5000f504 	andpl	pc, r0, r4, lsl #10
d0020404:	bf08681b 	svclt	0x0008681b
d0020408:	30302500 	eorscc	r2, r0, r0, lsl #10
d002040c:	47986d9b 			; <UNDEFINED> instruction: 0x47986d9b
d0020410:	f242b13d 	vand	d27, d2, d29
d0020414:	58e41330 	stmiapl	r4!, {r4, r5, r8, r9, ip}^
d0020418:	b117b91c 	tstlt	r7, ip, lsl r9
d002041c:	0f00f1b8 	svceq	0x0000f1b8
d0020420:	6873d113 	ldmdavs	r3!, {r0, r1, r4, r8, ip, lr, pc}^
d0020424:	681b483f 	ldmdavs	fp, {r0, r1, r2, r3, r4, r5, fp, lr}
d0020428:	6d9b4478 	cfldrsvs	mvf4, [fp, #480]	; 0x1e0
d002042c:	2d004798 	stccs	7, cr4, [r0, #-608]	; 0xfffffda0
d0020430:	4a3dd071 	bmi	0xd0f945fc
d0020434:	1330f242 	teqne	r0, #536870916	; 0x20000004	; <UNPREDICTABLE>
d0020438:	58d4447a 	ldmpl	r4, {r1, r3, r4, r5, r6, sl, lr}^
d002043c:	bf183c00 	svclt	0x00183c00
d0020440:	46202401 	strtmi	r2, [r0], -r1, lsl #8
d0020444:	e8bdb007 	pop	{r0, r1, r2, ip, sp, pc}
d0020448:	f8d983f0 			; <UNDEFINED> instruction: 0xf8d983f0
d002044c:	aa033004 	bge	0xd00ec464
d0020450:	a9044836 	stmdbge	r4, {r1, r2, r4, r5, fp, lr}
d0020454:	4478681b 	ldrbtmi	r6, [r8], #-2075	; 0xfffff7e5
d0020458:	6a9b9403 	bvs	0xce70546c
d002045c:	47989404 	ldrmi	r9, [r8, r4, lsl #8]
d0020460:	9a04b930 	bls	0xd014e928
d0020464:	0501f012 	streq	pc, [r1, #-18]	; 0xffffffee
d0020468:	9b03d102 	blls	0xd0114878
d002046c:	d0074543 	andle	r4, r7, r3, asr #10
d0020470:	463c6873 			; <UNDEFINED> instruction: 0x463c6873
d0020474:	681b482e 	ldmdavs	fp, {r1, r2, r3, r5, fp, lr}
d0020478:	6d9b4478 	cfldrsvs	mvf4, [fp, #480]	; 0x1e0
d002047c:	e7e04798 			; <UNDEFINED> instruction: 0xe7e04798
d0020480:	3008f8d9 	ldrdcc	pc, [r8], -r9
d0020484:	681b492b 	ldmdavs	fp, {r0, r1, r3, r5, r8, fp, lr}
d0020488:	f8df4479 			; <UNDEFINED> instruction: 0xf8df4479
d002048c:	681b80ac 	ldmdavs	fp, {r2, r3, r5, r7, pc}
d0020490:	f8d94798 			; <UNDEFINED> instruction: 0xf8d94798
d0020494:	44f83004 	ldrbtmi	r3, [r8], #4
d0020498:	681e462a 	ldmdavs	lr, {r1, r3, r5, r9, sl, lr}
d002049c:	9505a905 	strls	sl, [r5, #-2309]	; 0xfffff6fb
d00204a0:	6ab34640 	bvs	0xcecf1da8
d00204a4:	46054798 			; <UNDEFINED> instruction: 0x46054798
d00204a8:	9b05b978 	blls	0xd018ea90
d00204ac:	d42507db 	strtle	r0, [r5], #-2011	; 0xfffff825
d00204b0:	46404922 	strbmi	r4, [r0], -r2, lsr #18
d00204b4:	44796df3 	ldrbtmi	r6, [r9], #-3571	; 0xfffff20d
d00204b8:	46054798 			; <UNDEFINED> instruction: 0x46054798
d00204bc:	4820b1e0 	stmdami	r0!, {r5, r6, r7, r8, ip, sp, pc}
d00204c0:	6db3462c 	ldcvs	6, cr4, [r3, #176]!	; 0xb0
d00204c4:	47984478 			; <UNDEFINED> instruction: 0x47984478
d00204c8:	2804e7bb 	stmdacs	r4, {r0, r1, r3, r4, r5, r7, r8, r9, sl, sp, lr, pc}
d00204cc:	491dd1f7 	ldmdbmi	sp, {r0, r1, r2, r4, r5, r6, r7, r8, ip, lr, pc}
d00204d0:	4479481d 	ldrbtmi	r4, [r9], #-2077	; 0xfffff7e3
d00204d4:	44786df3 	ldrbtmi	r6, [r8], #-3571	; 0xfffff20d
d00204d8:	47989101 	ldrmi	r9, [r8, r1, lsl #2]
d00204dc:	46059901 	strmi	r9, [r5], -r1, lsl #18
d00204e0:	2c00b170 	stfcsd	f3, [r0], {112}	; 0x70
d00204e4:	4819d0eb 	ldmdami	r9, {r0, r1, r3, r5, r6, r7, ip, lr, pc}
d00204e8:	44786df3 	ldrbtmi	r6, [r8], #-3571	; 0xfffff20d
d00204ec:	28004798 	stmdacs	r0, {r3, r4, r7, r8, r9, sl, lr}
d00204f0:	f06fd0e5 			; <UNDEFINED> instruction: 0xf06fd0e5
d00204f4:	e7a40401 	str	r0, [r4, r1, lsl #8]!
d00204f8:	e7e8463c 			; <UNDEFINED> instruction: 0xe7e8463c
d00204fc:	e7de2507 	ldrb	r2, [lr, r7, lsl #10]
d0020500:	d09e2c00 	addsle	r2, lr, r0, lsl #24
d0020504:	6db34812 	ldcvs	8, cr4, [r3, #72]!	; 0x48
d0020508:	47984478 			; <UNDEFINED> instruction: 0x47984478
d002050c:	bf183800 	svclt	0x00183800
d0020510:	42442001 	submi	r2, r4, #1
d0020514:	2401e795 	strcs	lr, [r1], #-1941	; 0xfffff86b
d0020518:	bf00e793 	svclt	0x0000e793
d002051c:	00154866 	andseq	r4, r5, r6, ror #16
d0020520:	2001f000 	andcs	pc, r1, r0
d0020524:	00154594 	mulseq	r5, r4, r5
d0020528:	00154808 	andseq	r4, r5, r8, lsl #16
d002052c:	00154566 	andseq	r4, r5, r6, ror #10
d0020530:	00154544 	andseq	r4, r5, r4, asr #10
d0020534:	ffffff14 			; <UNDEFINED> instruction: 0xffffff14
d0020538:	0005311e 	andeq	r3, r5, lr, lsl r1
d002053c:	000531fe 	strdeq	r3, [r5], -lr
d0020540:	001544f8 			; <UNDEFINED> instruction: 0x001544f8
d0020544:	000530e2 	andeq	r3, r5, r2, ror #1
d0020548:	001544e6 	andseq	r4, r5, r6, ror #9
d002054c:	000531ca 	andeq	r3, r5, sl, asr #3
d0020550:	000531ac 	andeq	r3, r5, ip, lsr #3

Disassembly of section .text.compile_tick:

d00205b4 <.text.compile_tick>:
d00205b4:	4f5eb5f0 	svcmi	0x005eb5f0
d00205b8:	447fb087 	ldrbtmi	fp, [pc], #-135	; 0xd00205c0
d00205bc:	b16b683b 	cmnlt	fp, fp, lsr r8
d00205c0:	447e4e5c 	ldrbtmi	r4, [lr], #-3676	; 0xfffff1a4
d00205c4:	b94d6835 	stmdblt	sp, {r0, r2, r4, r5, fp, sp, lr}^
d00205c8:	a9052301 	stmdbge	r5, {r0, r8, r9, sp}
d00205cc:	95052080 	strls	r2, [r5, #-128]	; 0xffffff80
d00205d0:	f7fe6033 			; <UNDEFINED> instruction: 0xf7fe6033
d00205d4:	4604f857 			; <UNDEFINED> instruction: 0x4604f857
d00205d8:	6030b910 	eorsvs	fp, r0, r0, lsl r9
d00205dc:	bdf0b007 	ldcllt	0, cr11, [r0, #28]!
d00205e0:	4d55603d 	ldclmi	0, cr6, [r5, #-244]	; 0xffffff0c
d00205e4:	7828447d 	stmdavc	r8!, {r0, r2, r3, r4, r5, r6, sl, lr}
d00205e8:	d00b28ff 	strdle	r2, [fp], -pc	; <UNPREDICTABLE>
d00205ec:	68b34e4f 	ldmvs	r3!, {r0, r1, r2, r3, r6, r9, sl, fp, lr}
d00205f0:	68db695b 	ldmvs	fp, {r0, r1, r3, r4, r6, r8, fp, sp, lr}^
d00205f4:	68b34798 	ldmvs	r3!, {r3, r4, r7, r8, r9, sl, lr}
d00205f8:	695b7828 	ldmdbvs	fp, {r3, r5, fp, ip, sp, lr}^
d00205fc:	4798685b 			; <UNDEFINED> instruction: 0x4798685b
d0020600:	702b23ff 	strdvc	r2, [fp], -pc	; <UNPREDICTABLE>
d0020604:	98052c00 	stmdals	r5, {sl, fp, sp}
d0020608:	2100bfd4 	ldrdcs	fp, [r0, -r4]
d002060c:	f7ff2101 			; <UNDEFINED> instruction: 0xf7ff2101
d0020610:	494afedb 	stmdbmi	sl, {r0, r1, r3, r4, r6, r7, r9, sl, fp, ip, sp, lr, pc}^
d0020614:	680b4479 	stmdavs	fp, {r0, r3, r4, r5, r6, sl, lr}
d0020618:	d0452b00 	suble	r2, r5, r0, lsl #22
d002061c:	b94c690c 	stmdblt	ip, {r2, r3, r8, fp, sp, lr}^
d0020620:	68cb4a47 	stmiavs	fp, {r0, r1, r2, r6, r9, fp, lr}^
d0020624:	6812447a 	ldmdavs	r2, {r1, r3, r4, r5, r6, sl, lr}
d0020628:	d23a4293 	eorsle	r4, sl, #805306377	; 0x30000009
d002062c:	447c4c45 	ldrbtmi	r4, [ip], #-3141	; 0xfffff3bb
d0020630:	2403eb04 	strcs	lr, [r3], #-2820	; 0xfffff4fc
d0020634:	4620212f 	strtmi	r2, [r0], -pc, lsr #2
d0020638:	fc30f002 	ldc2	0, cr15, [r0], #-8
d002063c:	1c44b100 	stfnep	f3, [r4], {-0}
d0020640:	f44f4d41 			; <UNDEFINED> instruction: 0xf44f4d41
d0020644:	484171c0 	stmdami	r1, {r6, r7, r8, ip, sp, lr}^
d0020648:	4a41447d 	bmi	0xd1071844
d002064c:	682b4478 	stmdavs	fp!, {r3, r4, r5, r6, sl, lr}
d0020650:	9302447a 	movwls	r4, #9338	; 0x247a
d0020654:	930168ab 	movwls	r6, #6315	; 0x18ab
d0020658:	9300686b 	movwls	r6, #2155	; 0x86b
d002065c:	46044623 	strmi	r4, [r4], -r3, lsr #12
d0020660:	fbb4f002 	blx	0xced5c672
d0020664:	4c3b4620 	ldcmi	6, cr4, [fp], #-128	; 0xffffff80
d0020668:	fa32f7ff 	blx	0xd0cde66c
d002066c:	6820447c 	stmdavs	r0!, {r2, r3, r4, r5, r6, sl, lr}
d0020670:	692bb190 	stmdbvs	fp!, {r4, r7, r8, ip, sp, pc}
d0020674:	6869b983 	stmdavs	r9!, {r0, r1, r7, r8, fp, ip, sp, pc}^
d0020678:	68aab171 	stmiavs	sl!, {r0, r4, r5, r6, r8, ip, sp, pc}
d002067c:	4d2bb162 	stfmid	f3, [fp, #-392]!	; 0xfffffe78
d0020680:	39013a01 	stmdbcc	r1, {r0, r9, fp, ip, sp}
d0020684:	68db68ab 	ldmvs	fp, {r0, r1, r3, r5, r7, fp, sp, lr}^
d0020688:	30b8f8d3 	ldrsbtcc	pc, [r8], r3	; <UNPREDICTABLE>
d002068c:	68ab4798 	stmiavs	fp!, {r3, r4, r7, r8, r9, sl, lr}
d0020690:	68db6820 	ldmvs	fp, {r5, fp, sp, lr}^
d0020694:	47986ddb 			; <UNDEFINED> instruction: 0x47986ddb
d0020698:	22004b2f 	andcs	r4, r0, #48128	; 0xbc00
d002069c:	601a447b 	andsvs	r4, sl, fp, ror r4
d00206a0:	4c2ee79c 	stcmi	7, cr14, [lr], #-624	; 0xfffffd90
d00206a4:	e7c5447c 			; <UNDEFINED> instruction: 0xe7c5447c
d00206a8:	d1372800 	teqle	r7, r0, lsl #16
d00206ac:	dd3a2c00 	ldcle	12, cr2, [sl, #-0]
d00206b0:	2a009a05 	bcs	0xd0046ecc
d00206b4:	4a2ad037 	bmi	0xd0ad4798
d00206b8:	6812447a 	ldmdavs	r2, {r1, r3, r4, r5, r6, sl, lr}
d00206bc:	4829b12a 	stmdami	r9!, {r1, r3, r5, r8, ip, sp, pc}
d00206c0:	4478212f 	ldrbtmi	r2, [r8], #-303	; 0xfffffed1
d00206c4:	fbeaf002 	blx	0xcfadc6d6
d00206c8:	4a274603 	bmi	0xd09f1edc
d00206cc:	6811447a 	ldmdavs	r1, {r1, r3, r4, r5, r6, sl, lr}
d00206d0:	29019a05 	stmdbcs	r1, {r0, r2, r9, fp, ip, pc}
d00206d4:	b17bd913 	cmnlt	fp, r3, lsl r9
d00206d8:	48243301 	stmdami	r4!, {r0, r8, r9, ip, sp}
d00206dc:	4a249200 	bmi	0xd0944ee4
d00206e0:	91014478 	tstls	r1, r8, ror r4
d00206e4:	71c0f44f 	bicvc	pc, r0, pc, asr #8
d00206e8:	f002447a 			; <UNDEFINED> instruction: 0xf002447a
d00206ec:	4821fb6f 	stmdami	r1!, {r0, r1, r2, r3, r5, r6, r8, r9, fp, ip, sp, lr, pc}
d00206f0:	f7ff4478 			; <UNDEFINED> instruction: 0xf7ff4478
d00206f4:	e7cff9ed 	strb	pc, [pc, sp, ror #19]	; <UNPREDICTABLE>
d00206f8:	447b4b1f 	ldrbtmi	r4, [fp], #-2847	; 0xfffff4e1
d00206fc:	b153e7ed 	cmplt	r3, sp, ror #15
d0020700:	92003301 	andls	r3, r0, #67108864	; 0x4000000
d0020704:	71c0f44f 	bicvc	pc, r0, pc, asr #8
d0020708:	481d4a1c 	ldmdami	sp, {r2, r3, r4, r9, fp, lr}
d002070c:	4478447a 	ldrbtmi	r4, [r8], #-1146	; 0xfffffb86
d0020710:	fb5cf002 	blx	0xd175c722
d0020714:	4b1be7eb 	blmi	0xd071a6c8
d0020718:	e7f2447b 			; <UNDEFINED> instruction: 0xe7f2447b
d002071c:	4479491a 	ldrbtmi	r4, [r9], #-2330	; 0xfffff6e6
d0020720:	fd20f7ff 	stc2	7, cr15, [r0, #-1020]!	; 0xfffffc04
d0020724:	4819e7b8 	ldmdami	r9, {r3, r4, r5, r7, r8, r9, sl, sp, lr, pc}
d0020728:	e7e24478 			; <UNDEFINED> instruction: 0xe7e24478
d002072c:	2001f000 	andcs	pc, r1, r0
d0020730:	00053256 	andeq	r3, r5, r6, asr r2
d0020734:	0005320a 	andeq	r3, r5, sl, lsl #4
d0020738:	000029f4 	strdeq	r2, [r0], -r4
d002073c:	000531a4 	andeq	r3, r5, r4, lsr #3
d0020740:	000531fc 	strdeq	r3, [r5], -ip
d0020744:	000531f6 	strdeq	r3, [r5], -r6
d0020748:	00053170 	andeq	r3, r5, r0, ror r1
d002074c:	00154470 	andseq	r4, r5, r0, ror r4
d0020750:	ffffff00 			; <UNDEFINED> instruction: 0xffffff00
d0020754:	000531a8 	andeq	r3, r5, r8, lsr #3
d0020758:	00053130 	andeq	r3, r5, r0, lsr r1
d002075c:	00154218 	andseq	r4, r5, r8, lsl r2
d0020760:	00154584 	andseq	r4, r5, r4, lsl #11
d0020764:	00052ef2 	strdeq	r2, [r5], -r2	; <UNPREDICTABLE>
d0020768:	00053154 	andeq	r3, r5, r4, asr r1
d002076c:	001543dc 			; <UNDEFINED> instruction: 0x001543dc
d0020770:	fffffe74 			; <UNDEFINED> instruction: 0xfffffe74
d0020774:	001543cc 	andseq	r4, r5, ip, asr #7
d0020778:	00052eba 			; <UNDEFINED> instruction: 0x00052eba
d002077c:	fffffe70 			; <UNDEFINED> instruction: 0xfffffe70
d0020780:	001543ae 	andseq	r4, r5, lr, lsr #7
d0020784:	00052e9c 	muleq	r5, ip, lr
d0020788:	fffff4ee 			; <UNDEFINED> instruction: 0xfffff4ee
d002078c:	fffffe68 			; <UNDEFINED> instruction: 0xfffffe68

Disassembly of section .text.build:

d0020858 <.text.build>:
d0020858:	447b4b87 	ldrbtmi	r4, [fp], #-2951	; 0xfffff479
d002085c:	e92d681b 	push	{r0, r1, r3, r4, fp, sp, lr}
d0020860:	b08b4ff0 	strdlt	r4, [fp], r0
d0020864:	4885b143 	stmmi	r5, {r0, r1, r6, r8, ip, sp, pc}
d0020868:	f7ff4478 			; <UNDEFINED> instruction: 0xf7ff4478
d002086c:	2500f931 	strcs	pc, [r0, #-2353]	; 0xfffff6cf
d0020870:	b00b4628 	andlt	r4, fp, r8, lsr #12
d0020874:	8ff0e8bd 	svchi	0x00f0e8bd
d0020878:	447a4a81 	ldrbtmi	r4, [sl], #-2689	; 0xfffff57f
d002087c:	2f006817 	svccs	0x00006817
d0020880:	4a80d06d 	bmi	0xce054a3c
d0020884:	447a4880 	ldrbtmi	r4, [sl], #-2176	; 0xfffff780
d0020888:	eb004478 	bl	0xd0031a70
d002088c:	33012103 	movwcc	r2, #4355	; 0x1103
d0020890:	f842429f 			; <UNDEFINED> instruction: 0xf842429f
d0020894:	d1f81b04 	mvnsle	r1, r4, lsl #22
d0020898:	447d4d7c 	ldrbtmi	r4, [sp], #-3452	; 0xfffff284
d002089c:	2f014b7c 	svccs	0x00014b7c
d00208a0:	f04f4c74 			; <UNDEFINED> instruction: 0xf04f4c74
d00208a4:	447b0214 	ldrbtmi	r0, [fp], #-532	; 0xfffffdec
d00208a8:	0100f04f 	tsteq	r0, pc, asr #32	; <UNPREDICTABLE>
d00208ac:	2701bf38 	smladxcs	r1, r8, pc, fp	; <UNPREDICTABLE>
d00208b0:	93044618 	movwls	r4, #17944	; 0x4618
d00208b4:	feacf000 	cdp2	0, 10, cr15, cr12, cr0, {0}
d00208b8:	497668a3 	ldmdbmi	r6!, {r0, r1, r5, r7, fp, sp, lr}^
d00208bc:	681b463a 	ldmdavs	fp, {r1, r3, r4, r5, r9, sl, lr}
d00208c0:	44792000 	ldrbtmi	r2, [r9], #-0
d00208c4:	4798681b 			; <UNDEFINED> instruction: 0x4798681b
d00208c8:	447b4b73 	ldrbtmi	r4, [fp], #-2931	; 0xfffff48d
d00208cc:	93054618 	movwls	r4, #22040	; 0x5618
d00208d0:	fab4f002 	blx	0xced5c8e0
d00208d4:	f51038f7 			; <UNDEFINED> instruction: 0xf51038f7
d00208d8:	f2407f81 	vmax.f32	d23, d16, d1
d00208dc:	f8df8086 			; <UNDEFINED> instruction: 0xf8df8086
d00208e0:	f44f91bc 	vst4.32	{d25,d27,d29,d31}, [pc :256], ip
d00208e4:	4a6e7180 	bmi	0xd1bbceec
d00208e8:	0b00f04f 	bleq	0xd005ca2c
d00208ec:	4e6d44f9 	mcrmi	4, 3, r4, cr13, cr9, {7}
d00208f0:	447a9b05 	ldrbtmi	r9, [sl], #-2821	; 0xfffff4fb
d00208f4:	4648447e 			; <UNDEFINED> instruction: 0x4648447e
d00208f8:	fa68f002 	blx	0xd1a5c908
d00208fc:	486b4a6a 	stmdami	fp!, {r1, r3, r5, r6, r9, fp, lr}^
d0020900:	5800f506 	stmdapl	r0, {r1, r2, r8, sl, ip, sp, lr, pc}
d0020904:	447a9b05 	ldrbtmi	r9, [sl], #-2821	; 0xfffff4fb
d0020908:	7180f44f 	orrvc	pc, r0, pc, asr #8
d002090c:	f0024478 			; <UNDEFINED> instruction: 0xf0024478
d0020910:	f108fa5d 			; <UNDEFINED> instruction: 0xf108fa5d
d0020914:	4a660830 	bmi	0xd19a29dc
d0020918:	7180f44f 	orrvc	pc, r0, pc, asr #8
d002091c:	46409b05 	strbmi	r9, [r0], -r5, lsl #22
d0020920:	f002447a 			; <UNDEFINED> instruction: 0xf002447a
d0020924:	f242fa53 	vpmin.s8	<illegal reg q15.5>, q1, <illegal reg q1.5>
d0020928:	46491330 			; <UNDEFINED> instruction: 0x46491330
d002092c:	f8464630 			; <UNDEFINED> instruction: 0xf8464630
d0020930:	f7ffb003 			; <UNDEFINED> instruction: 0xf7ffb003
d0020934:	b180fa69 	orrlt	pc, r0, r9, ror #20
d0020938:	5a80f506 	bpl	0xce05dd58
d002093c:	f10a4641 			; <UNDEFINED> instruction: 0xf10a4641
d0020940:	46500a18 			; <UNDEFINED> instruction: 0x46500a18
d0020944:	fa60f7ff 	blx	0xd185e948
d0020948:	4630b9a8 	ldrtmi	fp, [r0], -r8, lsr #19
d002094c:	fcfef7ff 	ldc2l	7, cr15, [lr], #1020	; 0x3fc
d0020950:	46486863 	strbmi	r6, [r8], -r3, ror #16
d0020954:	6d9b681b 	ldcvs	8, cr6, [fp, #108]	; 0x6c
d0020958:	25014798 	strcs	r4, [r1, #-1944]	; 0xfffff868
d002095c:	4d55e03f 	ldclmi	0, cr14, [r5, #-252]	; 0xffffff04
d0020960:	447d4b55 	ldrbtmi	r4, [sp], #-2901	; 0xfffff4ab
d0020964:	447b4a55 	ldrbtmi	r4, [fp], #-2645	; 0xfffff5ab
d0020968:	6068447a 	rsbvs	r4, r8, sl, ror r4
d002096c:	4b54602b 	blmi	0xd1538a20
d0020970:	601a447b 	andsvs	r4, sl, fp, ror r4
d0020974:	4b53e792 	blmi	0xd151a7c4
d0020978:	e893447b 	ldm	r3, {r0, r1, r3, r4, r5, r6, sl, lr}
d002097c:	ab070007 	blge	0xd01e09a0
d0020980:	0007e883 	andeq	lr, r7, r3, lsl #17
d0020984:	46594850 			; <UNDEFINED> instruction: 0x46594850
d0020988:	44789305 	ldrbtmi	r9, [r8], #-773	; 0xfffffcfb
d002098c:	fd80f7fd 	stc2	7, cr15, [r0, #1012]	; 0x3f4
d0020990:	494e9b04 	stmdbmi	lr, {r2, r8, r9, fp, ip, pc}^
d0020994:	93024628 	movwls	r4, #9768	; 0x2628
d0020998:	9b05463a 	blls	0xd0172288
d002099c:	93014479 	movwls	r4, #5241	; 0x1479
d00209a0:	447b4b4b 	ldrbtmi	r4, [fp], #-2891	; 0xfffff4b5
d00209a4:	4b4b9300 	blmi	0xd13055ac
d00209a8:	f7fd447b 			; <UNDEFINED> instruction: 0xf7fd447b
d00209ac:	4605fd7d 			; <UNDEFINED> instruction: 0x4605fd7d
d00209b0:	f7fdb9e8 			; <UNDEFINED> instruction: 0xf7fdb9e8
d00209b4:	4629fe55 			; <UNDEFINED> instruction: 0x4629fe55
d00209b8:	f7fd4628 			; <UNDEFINED> instruction: 0xf7fd4628
d00209bc:	4650fd69 	ldrbmi	pc, [r0], -r9, ror #26	; <UNPREDICTABLE>
d00209c0:	fcc4f7ff 	stc2l	7, cr15, [r4], {255}	; 0xff
d00209c4:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d00209c8:	6863fcc1 	stmdavs	r3!, {r0, r6, r7, sl, fp, ip, sp, lr, pc}^
d00209cc:	681b4640 	ldmdavs	fp, {r6, r9, sl, lr}
d00209d0:	47986d9b 			; <UNDEFINED> instruction: 0x47986d9b
d00209d4:	46486863 	strbmi	r6, [r8], -r3, ror #16
d00209d8:	6d9b681b 	ldcvs	8, cr6, [fp, #108]	; 0x6c
d00209dc:	4b3e4798 	blmi	0xd0fb2844
d00209e0:	681e447b 	ldmdavs	lr, {r0, r1, r3, r4, r5, r6, sl, lr}
d00209e4:	4630b12e 	ldrtmi	fp, [r0], -lr, lsr #2
d00209e8:	2506e73f 	strcs	lr, [r6, #-1855]	; 0xfffff8c1
d00209ec:	465de7f7 			; <UNDEFINED> instruction: 0x465de7f7
d00209f0:	b12de7f5 	strdlt	lr, [sp, -r5]!
d00209f4:	46284939 			; <UNDEFINED> instruction: 0x46284939
d00209f8:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d00209fc:	e736fbb3 			; <UNDEFINED> instruction: 0xe736fbb3
d0020a00:	4e3768a3 	cdpmi	8, 3, cr6, cr7, cr3, {5}
d0020a04:	447e695b 	ldrbtmi	r6, [lr], #-2395	; 0xfffff6a5
d0020a08:	4798681b 			; <UNDEFINED> instruction: 0x4798681b
d0020a0c:	703028ff 	ldrshtvc	r2, [r0], -pc
d0020a10:	4629d108 	strtmi	sp, [r9], -r8, lsl #2
d0020a14:	f7ff4628 			; <UNDEFINED> instruction: 0xf7ff4628
d0020a18:	4832fcd7 	ldmdami	r2!, {r0, r1, r2, r4, r6, r7, sl, fp, ip, sp, lr, pc}
d0020a1c:	f7ff4478 			; <UNDEFINED> instruction: 0xf7ff4478
d0020a20:	e725f857 			; <UNDEFINED> instruction: 0xe725f857
d0020a24:	27014b30 	smladxcs	r1, r0, fp, r4
d0020a28:	80c0f8df 	ldrdhi	pc, [r0], #143	; 0x8f
d0020a2c:	447b220a 	ldrbtmi	r2, [fp], #-522	; 0xfffffdf6
d0020a30:	461144f8 			; <UNDEFINED> instruction: 0x461144f8
d0020a34:	68a3601d 	stmiavs	r3!, {r0, r2, r3, r4, sp, lr}
d0020a38:	7000f8c8 	andvc	pc, r0, r8, asr #17
d0020a3c:	9500695b 	strls	r6, [r0, #-2395]	; 0xfffff6a5
d0020a40:	9008f8d3 	ldrdls	pc, [r8], -r3
d0020a44:	447b4b2a 	ldrbtmi	r4, [fp], #-2858	; 0xfffff4d6
d0020a48:	280047c8 	stmdacs	r0, {r3, r6, r7, r8, r9, sl, lr}
d0020a4c:	68a3da0f 	stmiavs	r3!, {r0, r1, r2, r3, r9, fp, ip, lr, pc}
d0020a50:	695b7830 	ldmdbvs	fp, {r4, r5, fp, ip, sp, lr}^
d0020a54:	5000f8c8 	andpl	pc, r0, r8, asr #17
d0020a58:	4798685b 			; <UNDEFINED> instruction: 0x4798685b
d0020a5c:	462923ff 			; <UNDEFINED> instruction: 0x462923ff
d0020a60:	70334628 	eorsvc	r4, r3, r8, lsr #12
d0020a64:	fcb0f7ff 	ldc2	7, cr15, [r0], #1020	; 0x3fc
d0020a68:	44784822 	ldrbtmi	r4, [r8], #-2082	; 0xfffff7de
d0020a6c:	463de7d7 			; <UNDEFINED> instruction: 0x463de7d7
d0020a70:	bf00e6fe 	svclt	0x0000e6fe
d0020a74:	2001f000 	andcs	pc, r1, r0
d0020a78:	00052fb6 			; <UNDEFINED> instruction: 0x00052fb6
d0020a7c:	ffffff24 			; <UNDEFINED> instruction: 0xffffff24
d0020a80:	00052fa6 	andeq	r2, r5, r6, lsr #31
d0020a84:	00052f4a 	andeq	r2, r5, sl, asr #30
d0020a88:	00052f9c 	muleq	r5, ip, pc	; <UNPREDICTABLE>
d0020a8c:	00053f8a 	andeq	r3, r5, sl, lsl #31
d0020a90:	00052f12 	andeq	r2, r5, r2, lsl pc
d0020a94:	fffffee4 			; <UNDEFINED> instruction: 0xfffffee4
d0020a98:	00052cea 	andeq	r2, r5, sl, ror #25
d0020a9c:	001540d0 	ldrsbeq	r4, [r5], -r0
d0020aa0:	fffffee5 			; <UNDEFINED> instruction: 0xfffffee5
d0020aa4:	0015434c 	andseq	r4, r5, ip, asr #6
d0020aa8:	fffffedd 			; <UNDEFINED> instruction: 0xfffffedd
d0020aac:	00052da8 	andeq	r2, r5, r8, lsr #27
d0020ab0:	fffffecf 			; <UNDEFINED> instruction: 0xfffffecf
d0020ab4:	00052eb6 			; <UNDEFINED> instruction: 0x00052eb6
d0020ab8:	00053f46 	andeq	r3, r5, r6, asr #30
d0020abc:	00153f54 	andseq	r3, r5, r4, asr pc
d0020ac0:	00052e60 	andeq	r2, r5, r0, ror #28
d0020ac4:	00002654 	andeq	r2, r0, r4, asr r6
d0020ac8:	fffff603 			; <UNDEFINED> instruction: 0xfffff603
d0020acc:	00052e34 	andeq	r2, r5, r4, lsr lr
d0020ad0:	fffff82f 			; <UNDEFINED> instruction: 0xfffff82f
d0020ad4:	fffff1f9 			; <UNDEFINED> instruction: 0xfffff1f9
d0020ad8:	00052dd8 	ldrdeq	r2, [r5], -r8
d0020adc:	fffffe03 			; <UNDEFINED> instruction: 0xfffffe03
d0020ae0:	000025d2 	ldrdeq	r2, [r0], -r2	; <UNPREDICTABLE>
d0020ae4:	fffffdf2 			; <UNDEFINED> instruction: 0xfffffdf2
d0020ae8:	00052d9e 	muleq	r5, lr, sp
d0020aec:	00052de0 	andeq	r2, r5, r0, ror #27
d0020af0:	fffffb6b 			; <UNDEFINED> instruction: 0xfffffb6b
d0020af4:	fffffdc5 			; <UNDEFINED> instruction: 0xfffffdc5

Disassembly of section .text.editor_proc:

d0020b68 <.text.editor_proc>:
d0020b68:	447b4b7a 	ldrbtmi	r4, [fp], #-2938	; 0xfffff486
d0020b6c:	4ff0e92d 	svcmi	0x00f0e92d
d0020b70:	b085681e 	addlt	r6, r5, lr, lsl r8
d0020b74:	b17e460c 	cmnlt	lr, ip, lsl #12
d0020b78:	f0002900 			; <UNDEFINED> instruction: 0xf0002900
d0020b7c:	680b80e4 	stmdavs	fp, {r2, r5, r6, r7, pc}
d0020b80:	d10c2b20 	tstle	ip, r0, lsr #22
d0020b84:	f5b368cb 			; <UNDEFINED> instruction: 0xf5b368cb
d0020b88:	f0405f80 			; <UNDEFINED> instruction: 0xf0405f80
d0020b8c:	487280dc 	ldmdami	r2!, {r2, r3, r4, r6, r7, pc}^
d0020b90:	f7fe4478 			; <UNDEFINED> instruction: 0xf7fe4478
d0020b94:	e039ff9d 	mlas	r9, sp, pc, pc	; <UNPREDICTABLE>
d0020b98:	f0002900 			; <UNDEFINED> instruction: 0xf0002900
d0020b9c:	682380d4 	stmdavs	r3!, {r2, r4, r6, r7, pc}
d0020ba0:	f0402b10 			; <UNDEFINED> instruction: 0xf0402b10
d0020ba4:	68e280d0 	stmiavs	r2!, {r4, r6, r7, pc}^
d0020ba8:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d0020bac:	f040429a 			; <UNDEFINED> instruction: 0xf040429a
d0020bb0:	4a6a80ca 	bmi	0xd1ac0ee0
d0020bb4:	447a68a3 	ldrbtmi	r6, [sl], #-2211	; 0xfffff75d
d0020bb8:	42936812 	addsmi	r6, r3, #1179648	; 0x120000
d0020bbc:	4a68d005 	bmi	0xd1a54bd8
d0020bc0:	6812447a 	ldmdavs	r2, {r1, r3, r4, r5, r6, sl, lr}
d0020bc4:	f0404293 			; <UNDEFINED> instruction: 0xf0404293
d0020bc8:	b11680be 	ldrhlt	r8, [r6, -lr]
d0020bcc:	44784865 	ldrbtmi	r4, [r8], #-2149	; 0xfffff79b
d0020bd0:	4d5ee7df 	ldclmi	7, cr14, [lr, #-892]	; 0xfffffc84
d0020bd4:	8190f8df 			; <UNDEFINED> instruction: 0x8190f8df
d0020bd8:	486468ab 	stmdami	r4!, {r0, r1, r3, r5, r7, fp, sp, lr}^
d0020bdc:	68db44f8 	ldmvs	fp, {r3, r4, r5, r6, r7, sl, lr}^
d0020be0:	4a5b4478 	bmi	0xd16f1dc8
d0020be4:	46416f1b 			; <UNDEFINED> instruction: 0x46416f1b
d0020be8:	47986800 	ldrmi	r6, [r8, r0, lsl #16]
d0020bec:	f5b71e47 			; <UNDEFINED> instruction: 0xf5b71e47
d0020bf0:	d9021f80 	stmdble	r2, {r7, r8, r9, sl, fp, ip}
d0020bf4:	4478485e 	ldrbtmi	r4, [r8], #-2142	; 0xfffff7a2
d0020bf8:	4b5ee7cb 	blmi	0xd17dab2c
d0020bfc:	447b68a2 	ldrbtmi	r6, [fp], #-2210	; 0xfffff75e
d0020c00:	429a681b 	addsmi	r6, sl, #1769472	; 0x1b0000
d0020c04:	4638d106 	ldrtmi	sp, [r8], -r6, lsl #2
d0020c08:	fe26f7ff 	mcr2	7, 1, pc, cr6, cr15, {7}	; <UNPREDICTABLE>
d0020c0c:	b00520f0 	strdlt	r2, [r5], -r0
d0020c10:	8ff0e8bd 	svchi	0x00f0e8bd
d0020c14:	b160f8df 	ldrdlt	pc, [r0, #-143]!	; 0xffffff71
d0020c18:	44fb686b 	ldrbtmi	r6, [fp], #2155	; 0x86b
d0020c1c:	4658681d 			; <UNDEFINED> instruction: 0x4658681d
d0020c20:	f90cf002 			; <UNDEFINED> instruction: 0xf90cf002
d0020c24:	03f7f1a0 	mvnseq	pc, #160, 2	; 0x28
d0020c28:	f5134604 			; <UNDEFINED> instruction: 0xf5134604
d0020c2c:	f2407f81 	vmax.f32	d23, d16, d1
d0020c30:	f8df8088 			; <UNDEFINED> instruction: 0xf8df8088
d0020c34:	46029148 	strmi	r9, [r2], -r8, asr #2
d0020c38:	f8df4659 			; <UNDEFINED> instruction: 0xf8df4659
d0020c3c:	44f9a144 	ldrbtmi	sl, [r9], #324	; 0x144
d0020c40:	464844fa 			; <UNDEFINED> instruction: 0x464844fa
d0020c44:	fcf2f000 	ldc2l	0, cr15, [r2]
d0020c48:	220a494e 	andcs	r4, sl, #1277952	; 0x138000
d0020c4c:	0004eb09 	andeq	lr, r4, r9, lsl #22
d0020c50:	f0004479 			; <UNDEFINED> instruction: 0xf0004479
d0020c54:	4622fceb 	strtmi	pc, [r2], -fp, ror #25
d0020c58:	46504659 			; <UNDEFINED> instruction: 0x46504659
d0020c5c:	fce6f000 	stc2l	0, cr15, [r6]
d0020c60:	220a4949 	andcs	r4, sl, #1196032	; 0x124000
d0020c64:	0004eb0a 	andeq	lr, r4, sl, lsl #22
d0020c68:	f0004479 			; <UNDEFINED> instruction: 0xf0004479
d0020c6c:	6babfcdf 	blvs	0xceb1fff0
d0020c70:	2106aa01 	tstcs	r6, r1, lsl #20
d0020c74:	47984648 	ldrmi	r4, [r8, r8, asr #12]
d0020c78:	9602b980 	strls	fp, [r2], -r0, lsl #19
d0020c7c:	6d2bb99f 			; <UNDEFINED> instruction: 0x6d2bb99f
d0020c80:	47989801 	ldrmi	r9, [r8, r1, lsl #16]
d0020c84:	6d6b4604 	stclvs	6, cr4, [fp, #-16]!
d0020c88:	47989801 	ldrmi	r9, [r8, r1, lsl #16]
d0020c8c:	b1c0b90c 	biclt	fp, r0, ip, lsl #18
d0020c90:	483e4604 	ldmdami	lr!, {r2, r9, sl, lr}
d0020c94:	44786dab 	ldrbtmi	r6, [r8], #-3499	; 0xfffff255
d0020c98:	46204798 			; <UNDEFINED> instruction: 0x46204798
d0020c9c:	4479493c 	ldrbtmi	r4, [r9], #-2364	; 0xfffff6c4
d0020ca0:	fa60f7ff 	blx	0xd185eca4
d0020ca4:	6c2ce7b2 	stcvs	7, cr14, [ip], #-712	; 0xfffffd38
d0020ca8:	463aab02 	ldrtmi	sl, [sl], -r2, lsl #22
d0020cac:	98014641 	stmdals	r1, {r0, r6, r9, sl, lr}
d0020cb0:	460447a0 	strmi	r4, [r4], -r0, lsr #15
d0020cb4:	d1e62800 	mvnle	r2, r0, lsl #16
d0020cb8:	429f9b02 	addsmi	r9, pc, #2048	; 0x800
d0020cbc:	2401d0df 	strcs	sp, [r1], #-223	; 0xffffff21
d0020cc0:	4f34e7e1 	svcmi	0x0034e7e1
d0020cc4:	94034622 	strls	r4, [r3], #-1570	; 0xfffff9de
d0020cc8:	447fa903 	ldrbtmi	sl, [pc], #-2307	; 0xd0020cd0
d0020ccc:	46386aab 	ldrtmi	r6, [r8], -fp, lsr #21
d0020cd0:	46044798 			; <UNDEFINED> instruction: 0x46044798
d0020cd4:	9b03b9d0 	blls	0xd010f41c
d0020cd8:	d42d07db 	strtle	r0, [sp], #-2011	; 0xfffff825
d0020cdc:	4638492e 	ldrtmi	r4, [r8], -lr, lsr #18
d0020ce0:	44796deb 	ldrbtmi	r6, [r9], #-3563	; 0xfffff215
d0020ce4:	46044798 			; <UNDEFINED> instruction: 0x46044798
d0020ce8:	482cb320 	stmdami	ip!, {r5, r8, r9, ip, sp, pc}
d0020cec:	44786dab 	ldrbtmi	r6, [r8], #-3499	; 0xfffff255
d0020cf0:	2e004798 	mcrcs	7, 0, r4, cr0, cr8, {4}
d0020cf4:	492ad0d1 	stmdbmi	sl!, {r0, r4, r6, r7, ip, lr, pc}
d0020cf8:	6deb482a 	stclvs	8, cr4, [fp, #168]!	; 0xa8
d0020cfc:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d0020d00:	28004798 	stmdacs	r0, {r3, r4, r7, r8, r9, sl, lr}
d0020d04:	f06fd0c9 			; <UNDEFINED> instruction: 0xf06fd0c9
d0020d08:	e7c70001 	strb	r0, [r7, r1]
d0020d0c:	d1ec2804 	mvnle	r2, r4, lsl #16
d0020d10:	48264925 	stmdami	r6!, {r0, r2, r5, r8, fp, lr}
d0020d14:	44796deb 	ldrbtmi	r6, [r9], #-3563	; 0xfffff215
d0020d18:	47984478 			; <UNDEFINED> instruction: 0x47984478
d0020d1c:	28004604 	stmdacs	r0, {r2, r9, sl, lr}
d0020d20:	b15ed1e3 	cmplt	lr, r3, ror #3
d0020d24:	6dab4822 	stcvs	8, cr4, [fp, #136]!	; 0x88
d0020d28:	47984478 			; <UNDEFINED> instruction: 0x47984478
d0020d2c:	f04fb130 			; <UNDEFINED> instruction: 0xf04fb130
d0020d30:	e7b330ff 			; <UNDEFINED> instruction: 0xe7b330ff
d0020d34:	e7eb2601 	strb	r2, [fp, r1, lsl #12]!
d0020d38:	e7d62407 	ldrb	r2, [r6, r7, lsl #8]
d0020d3c:	4478481d 	ldrbtmi	r4, [r8], #-2077	; 0xfffff7e3
d0020d40:	2007e727 	andcs	lr, r7, r7, lsr #14
d0020d44:	2000e7aa 	andcs	lr, r0, sl, lsr #15
d0020d48:	bf00e761 	svclt	0x0000e761
d0020d4c:	2001f000 	andcs	pc, r1, r0
d0020d50:	00100001 	andseq	r0, r0, r1
d0020d54:	00052ca6 	andeq	r2, r5, r6, lsr #25
d0020d58:	ffffff64 			; <UNDEFINED> instruction: 0xffffff64
d0020d5c:	00053cf2 	strdeq	r3, [r5], -r2
d0020d60:	00052bf4 	strdeq	r2, [r5], -r4
d0020d64:	ffffff4e 			; <UNDEFINED> instruction: 0xffffff4e
d0020d68:	00053cd0 	ldrdeq	r3, [r5], -r0
d0020d6c:	00052c34 	andeq	r2, r5, r4, lsr ip
d0020d70:	fffff4c2 			; <UNDEFINED> instruction: 0xfffff4c2
d0020d74:	00052bb6 			; <UNDEFINED> instruction: 0x00052bb6
d0020d78:	00153ca2 	andseq	r3, r5, r2, lsr #25
d0020d7c:	00153d7e 	andseq	r3, r5, lr, ror sp
d0020d80:	00052a74 	andeq	r2, r5, r4, ror sl
d0020d84:	fffffef3 			; <UNDEFINED> instruction: 0xfffffef3
d0020d88:	fffffee5 			; <UNDEFINED> instruction: 0xfffffee5
d0020d8c:	00153d26 	andseq	r3, r5, r6, lsr #26
d0020d90:	ffffef69 			; <UNDEFINED> instruction: 0xffffef69
d0020d94:	00153bf2 			; <UNDEFINED> instruction: 0x00153bf2
d0020d98:	000529d2 	ldrdeq	r2, [r5], -r2	; <UNPREDICTABLE>
d0020d9c:	00153cce 	andseq	r3, r5, lr, asr #25
d0020da0:	00153bc0 	andseq	r3, r5, r0, asr #23
d0020da4:	000529b6 			; <UNDEFINED> instruction: 0x000529b6
d0020da8:	00153ba6 	andseq	r3, r5, r6, lsr #23
d0020dac:	00153ca4 	andseq	r3, r5, r4, lsr #25
d0020db0:	0005298c 	andeq	r2, r5, ip, lsl #19
d0020db4:	fffffe19 			; <UNDEFINED> instruction: 0xfffffe19

Disassembly of section .text.stream_io_write:

d0020db8 <.text.stream_io_write>:
d0020db8:	4ff0e92d 	svcmi	0x00f0e92d
d0020dbc:	4616b087 	ldrmi	fp, [r6], -r7, lsl #1
d0020dc0:	9001461f 	andls	r4, r1, pc, lsl r6
d0020dc4:	f500b141 			; <UNDEFINED> instruction: 0xf500b141
d0020dc8:	35185580 	ldrcc	r5, [r8, #-1408]	; 0xfffffa80
d0020dcc:	b92b9b10 	stmdblt	fp!, {r4, r8, r9, fp, ip, pc}
d0020dd0:	b0072001 	andlt	r2, r7, r1
d0020dd4:	8ff0e8bd 	svchi	0x00f0e8bd
d0020dd8:	e7f79d01 	ldrb	r9, [r7, r1, lsl #26]!
d0020ddc:	2b00682b 	blcs	0xd003ae90
d0020de0:	9b10d05a 	blls	0xd0454f50
d0020de4:	429e43db 	addsmi	r4, lr, #1811939331	; 0x6c000003
d0020de8:	f505d856 			; <UNDEFINED> instruction: 0xf505d856
d0020dec:	f1095980 			; <UNDEFINED> instruction: 0xf1095980
d0020df0:	f4260910 	vld2.8	{d0,d2}, [r6 :64], r0
d0020df4:	f505647f 			; <UNDEFINED> instruction: 0xf505647f
d0020df8:	f8d95880 			; <UNDEFINED> instruction: 0xf8d95880
d0020dfc:	f0243000 			; <UNDEFINED> instruction: 0xf0243000
d0020e00:	f108040f 			; <UNDEFINED> instruction: 0xf108040f
d0020e04:	b1230814 			; <UNDEFINED> instruction: 0xb1230814
d0020e08:	0304f241 	movweq	pc, #16961	; 0x4241	; <UNPREDICTABLE>
d0020e0c:	429c58eb 	addsmi	r5, ip, #15400960	; 0xeb0000
d0020e10:	f8d8d01c 			; <UNDEFINED> instruction: 0xf8d8d01c
d0020e14:	2b003000 	blcs	0xd002ce1c
d0020e18:	f105d139 			; <UNDEFINED> instruction: 0xf105d139
d0020e1c:	f44f0a04 	vst1.8	{d16-d17}, [pc], r4
d0020e20:	21005280 	smlabbcs	r0, r0, r2, r5
d0020e24:	f0004650 			; <UNDEFINED> instruction: 0xf0004650
d0020e28:	f241fbf3 	vpadd.i8	<illegal reg q15.5>, <illegal reg q8.5>, <illegal reg q9.5>
d0020e2c:	f2410304 	vcgt.s8	d16, d1, d4
d0020e30:	50ec0208 	rscpl	r0, ip, r8, lsl #4
d0020e34:	f8c92301 			; <UNDEFINED> instruction: 0xf8c92301
d0020e38:	18ab3000 	stmiane	fp!, {ip, sp}
d0020e3c:	23009302 	movwcs	r9, #770	; 0x302
d0020e40:	f24150ab 	vhadd.s8	d21, d17, d27
d0020e44:	58aa020c 	stmiapl	sl!, {r2, r3, r9}
d0020e48:	d32c4294 			; <UNDEFINED> instruction: 0xd32c4294
d0020e4c:	0a04eba6 	beq	0xd015bcec
d0020e50:	9b101ba4 	blls	0xd0427ce8
d0020e54:	f5041d28 			; <UNDEFINED> instruction: 0xf5041d28
d0020e58:	46395480 	ldrtmi	r5, [r9], -r0, lsl #9
d0020e5c:	429c4450 	addsmi	r4, ip, #80, 8	; 0x50000000
d0020e60:	461cbf28 	ldrmi	fp, [ip], -r8, lsr #30
d0020e64:	44264622 	strtmi	r4, [r6], #-1570	; 0xfffff9de
d0020e68:	fbe0f000 	blx	0xcf85ce72
d0020e6c:	0208f241 	andeq	pc, r8, #268435460	; 0x10000004
d0020e70:	0304eb0a 	movweq	lr, #19210	; 0x4b0a
d0020e74:	58a94427 	stmiapl	r9!, {r0, r1, r2, r5, sl, lr}
d0020e78:	bf88428b 	svclt	0x0088428b
d0020e7c:	230150ab 	movwcs	r5, #4267	; 0x10ab
d0020e80:	3000f8c8 	andcc	pc, r0, r8, asr #17
d0020e84:	1b1b9b10 	blne	0xd0707acc
d0020e88:	d1b29310 			; <UNDEFINED> instruction: 0xd1b29310
d0020e8c:	4628e7a0 	strtmi	lr, [r8], -r0, lsr #15
d0020e90:	ffd6f7fe 			; <UNDEFINED> instruction: 0xffd6f7fe
d0020e94:	d1c02800 	bicle	r2, r0, r0, lsl #16
d0020e98:	1330f242 	teqne	r0, #536870916	; 0x20000004	; <UNPREDICTABLE>
d0020e9c:	99012201 	stmdbls	r1, {r0, r9, sp}
d0020ea0:	50ca2000 	sbcpl	r2, sl, r0
d0020ea4:	9305e795 	movwls	lr, #22421	; 0x5795
d0020ea8:	4b114621 	blmi	0xd0472734
d0020eac:	685b6828 	ldmdavs	fp, {r3, r5, fp, sp, lr}^
d0020eb0:	f8d39203 			; <UNDEFINED> instruction: 0xf8d39203
d0020eb4:	f8dbb000 			; <UNDEFINED> instruction: 0xf8dbb000
d0020eb8:	47983044 	ldrmi	r3, [r8, r4, asr #32]
d0020ebc:	d1eb2800 	mvnle	r2, r0, lsl #16
d0020ec0:	ab059a03 	blge	0xd01876d4
d0020ec4:	b03cf8db 	ldrsbtlt	pc, [ip], -fp	; <UNPREDICTABLE>
d0020ec8:	1b124651 	blne	0xd04b2814
d0020ecc:	f5b26828 			; <UNDEFINED> instruction: 0xf5b26828
d0020ed0:	bf285f80 	svclt	0x00285f80
d0020ed4:	5280f44f 	addpl	pc, r0, #1325400064	; 0x4f000000
d0020ed8:	47d89203 	ldrbmi	r9, [r8, r3, lsl #4]
d0020edc:	d1db2800 	bicsle	r2, fp, r0, lsl #16
d0020ee0:	9a039b05 	bls	0xd0107afc
d0020ee4:	d1d7429a 			; <UNDEFINED> instruction: 0xd1d7429a
d0020ee8:	601a9b02 	andsvs	r9, sl, r2, lsl #22
d0020eec:	bf00e7ae 	svclt	0x0000e7ae
d0020ef0:	2001f000 	andcs	pc, r1, r0

Disassembly of section .text.startup.main:

d0021138 <.text.startup.main>:
d0021138:	e92d2801 	push	{r0, fp, sp}
d002113c:	46044ff0 			; <UNDEFINED> instruction: 0x46044ff0
d0021140:	ed2d460f 	stc	6, cr4, [sp, #-60]!	; 0xffffffc4
d0021144:	b0998b02 	addslt	r8, r9, r2, lsl #22
d0021148:	808cf000 	addhi	pc, ip, r0
d002114c:	f0402803 			; <UNDEFINED> instruction: 0xf0402803
d0021150:	49d681a6 	ldmibmi	r6, {r1, r2, r5, r7, r8, pc}^
d0021154:	44796878 	ldrbtmi	r6, [r9], #-2168	; 0xfffff788
d0021158:	fe7cf001 	cdp2	0, 7, cr15, cr12, cr1, {0}
d002115c:	f680fab0 			; <UNDEFINED> instruction: 0xf680fab0
d0021160:	49d30976 	ldmibmi	r3, {r1, r2, r4, r5, r6, r8, fp}^
d0021164:	44796878 	ldrbtmi	r6, [r9], #-2168	; 0xfffff788
d0021168:	fe74f001 	cdp2	0, 7, cr15, cr4, cr1, {0}
d002116c:	b966b958 	stmdblt	r6!, {r3, r4, r6, r8, fp, ip, sp, pc}^
d0021170:	447848d0 	ldrbtmi	r4, [r8], #-2256	; 0xfffff730
d0021174:	fcacf7fe 	stc2	7, cr15, [ip], #1016	; 0x3f8
d0021178:	46202401 	strtmi	r2, [r0], -r1, lsl #8
d002117c:	ecbdb019 	ldc	0, cr11, [sp], #100	; 0x64
d0021180:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d0021184:	2e008ff0 	mcrcs	15, 0, r8, cr0, cr0, {7}
d0021188:	f104d05d 			; <UNDEFINED> instruction: 0xf104d05d
d002118c:	25004480 	strcs	r4, [r0, #-1152]	; 0xfffffb80
d0021190:	46ab3c01 	strtmi	r3, [fp], r1, lsl #24
d0021194:	0024f857 	eoreq	pc, r4, r7, asr r8	; <UNPREDICTABLE>
d0021198:	f8df2401 			; <UNDEFINED> instruction: 0xf8df2401
d002119c:	49c7831c 	stmibmi	r7, {r2, r3, r4, r8, r9, pc}^
d00211a0:	447944f8 	ldrbtmi	r4, [r9], #-1272	; 0xfffffb08
d00211a4:	f7ff4642 			; <UNDEFINED> instruction: 0xf7ff4642
d00211a8:	2800f85d 	stmdacs	r0, {r0, r2, r3, r4, r6, fp, ip, sp, lr, pc}
d00211ac:	48c4d15f 	stmiami	r4, {r0, r1, r2, r3, r4, r6, r8, ip, lr, pc}^
d00211b0:	e7df4478 			; <UNDEFINED> instruction: 0xe7df4478
d00211b4:	0389ea4f 	orreq	lr, r9, #323584	; 0x4f000
d00211b8:	1a10ee18 	bne	0xd045ca20
d00211bc:	0029f857 	eoreq	pc, r9, r7, asr r8	; <UNPREDICTABLE>
d00211c0:	0889eb07 	stmeq	r9, {r0, r1, r2, r8, r9, fp, sp, lr, pc}
d00211c4:	f0019304 			; <UNDEFINED> instruction: 0xf0019304
d00211c8:	b960fe45 	stmdblt	r0!, {r0, r2, r6, r9, sl, fp, ip, sp, lr, pc}^
d00211cc:	f109b946 			; <UNDEFINED> instruction: 0xf109b946
d00211d0:	42a10101 	adcmi	r0, r1, #1073741824	; 0x40000000
d00211d4:	f8d8da04 			; <UNDEFINED> instruction: 0xf8d8da04
d00211d8:	78091004 	stmdavc	r9, {r2, ip}
d00211dc:	d130292d 	teqle	r0, sp, lsr #18
d00211e0:	447848b8 	ldrbtmi	r4, [r8], #-2232	; 0xfffff748
d00211e4:	4651e7c6 	ldrbmi	lr, [r1], -r6, asr #15
d00211e8:	0029f857 	eoreq	pc, r9, r7, asr r8	; <UNPREDICTABLE>
d00211ec:	fe32f001 	cdp2	0, 3, cr15, cr2, cr1, {0}
d00211f0:	f1bbb978 			; <UNDEFINED> instruction: 0xf1bbb978
d00211f4:	d1090f00 	tstle	r9, r0, lsl #30
d00211f8:	0901f109 	stmdbeq	r1, {r0, r3, r8, ip, sp, lr, pc}
d00211fc:	da0545a1 	ble	0xd0172888
d0021200:	b004f8d8 	ldrdlt	pc, [r4], -r8
d0021204:	1000f89b 	mulne	r0, fp, r8
d0021208:	d112292d 	tstle	r2, sp, lsr #18
d002120c:	447848ae 	ldrbtmi	r4, [r8], #-2222	; 0xfffff752
d0021210:	9b04e7b0 	blls	0xd015b0d8
d0021214:	780858f9 	stmdavc	r8, {r0, r3, r4, r5, r6, r7, fp, ip, lr}
d0021218:	d001282d 	andle	r2, r1, sp, lsr #16
d002121c:	d9022d0f 	stmdble	r2, {r0, r1, r2, r3, r8, sl, fp, sp}
d0021220:	447848aa 	ldrbtmi	r4, [r8], #-2218	; 0xfffff756
d0021224:	ab18e7a6 	blge	0xd065b0c4
d0021228:	0085eb03 	addeq	lr, r5, r3, lsl #22
d002122c:	f8403501 			; <UNDEFINED> instruction: 0xf8403501
d0021230:	f1091c40 			; <UNDEFINED> instruction: 0xf1091c40
d0021234:	45a10901 	strmi	r0, [r1, #2305]!	; 0x901
d0021238:	b985dbbc 	stmiblt	r5, {r2, r3, r4, r5, r7, r8, r9, fp, ip, lr, pc}
d002123c:	447848a4 	ldrbtmi	r4, [r8], #-2212	; 0xfffff75c
d0021240:	2601e798 			; <UNDEFINED> instruction: 0x2601e798
d0021244:	4ba3e7f5 	blmi	0xce91b220
d0021248:	0901f04f 	stmdbeq	r1, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d002124c:	a288f8df 	addge	pc, r8, #14614528	; 0xdf0000
d0021250:	447b4635 	ldrbtmi	r4, [fp], #-1589	; 0xfffff9cb
d0021254:	44fa46b3 	ldrbtmi	r4, [sl], #1715	; 0x6b3
d0021258:	3a10ee08 	bcc	0xd045ca80
d002125c:	9808e7eb 	stmdals	r8, {r0, r1, r3, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d0021260:	e79a2400 	ldr	r2, [sl, r0, lsl #8]
d0021264:	489d2500 	ldmmi	sp, {r8, sl, sp}
d0021268:	447846ab 	ldrbtmi	r4, [r8], #-1707	; 0xfffff955
d002126c:	f1bbe795 			; <UNDEFINED> instruction: 0xf1bbe795
d0021270:	d05f0f00 	subsle	r0, pc, r0, lsl #30
d0021274:	46584a9a 			; <UNDEFINED> instruction: 0x46584a9a
d0021278:	447a499a 	ldrbtmi	r4, [sl], #-2458	; 0xfffff666
d002127c:	f7fe4479 			; <UNDEFINED> instruction: 0xf7fe4479
d0021280:	2800fff1 	stmdacs	r0, {r0, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0021284:	4898d093 	ldmmi	r8, {r0, r1, r4, r7, ip, lr, pc}
d0021288:	f0014478 			; <UNDEFINED> instruction: 0xf0014478
d002128c:	38f7fdd7 	ldmcc	r7!, {r0, r1, r2, r4, r6, r7, r8, sl, fp, ip, sp, lr, pc}^
d0021290:	7f81f510 	svcvc	0x0081f510
d0021294:	2c00d98b 			; <UNDEFINED> instruction: 0x2c00d98b
d0021298:	80d1f040 	sbcshi	pc, r1, r0, asr #32
d002129c:	46274b93 			; <UNDEFINED> instruction: 0x46274b93
d00212a0:	b24cf8df 	sublt	pc, ip, #14614528	; 0xdf0000
d00212a4:	447b46a0 	ldrbtmi	r4, [fp], #-1696	; 0xfffff960
d00212a8:	601c44fb 			; <UNDEFINED> instruction: 0x601c44fb
d00212ac:	447b4b91 	ldrbtmi	r4, [fp], #-2961	; 0xfffff46f
d00212b0:	4b919304 	blmi	0xce485ec8
d00212b4:	ee08447b 	mcr	4, 0, r4, cr8, cr11, {3}
d00212b8:	42af3a10 	adcmi	r3, pc, #16, 20	; 0x10000
d00212bc:	4e7ad151 	mrcmi	1, 3, sp, cr10, cr1, {2}
d00212c0:	320df240 	andcc	pc, sp, #64, 4
d00212c4:	20002137 	andcs	r2, r0, r7, lsr r1
d00212c8:	4f8c68b3 	svcmi	0x008c68b3
d00212cc:	9202685b 	andls	r6, r2, #5963776	; 0x5b0000
d00212d0:	4a8b447f 	bmi	0xce2f24d4
d00212d4:	9201447a 	andls	r4, r1, #2046820352	; 0x7a000000
d00212d8:	9200225c 	andls	r2, r0, #92, 4	; 0xc0000005
d00212dc:	681d224b 	ldmdavs	sp, {r0, r1, r3, r6, r9, sp}
d00212e0:	73b9f44f 			; <UNDEFINED> instruction: 0x73b9f44f
d00212e4:	1e4347a8 	cdpne	7, 4, cr4, cr3, cr8, {5}
d00212e8:	b2db7038 	sbcslt	r7, fp, #56	; 0x38
d00212ec:	d81e2bfd 	ldmdale	lr, {r0, r2, r3, r4, r5, r6, r7, r8, r9, fp, sp}
d00212f0:	f04f4a84 			; <UNDEFINED> instruction: 0xf04f4a84
d00212f4:	68b30801 	ldmvs	r3!, {r0, fp}
d00212f8:	447a210a 	ldrbtmi	r2, [sl], #-266	; 0xfffffef6
d00212fc:	9208f8df 	andls	pc, r8, #14614528	; 0xdf0000
d0021300:	920168db 	andls	r6, r1, #14352384	; 0xdb0000
d0021304:	f8cd2214 			; <UNDEFINED> instruction: 0xf8cd2214
d0021308:	44f98008 	ldrbtmi	r8, [r9], #8
d002130c:	22179200 	andscs	r9, r7, #0, 4
d0021310:	f240699d 	vmul.i8	d22, d16, d13
d0021314:	47a81359 	sbfxmi	r1, r9, #6, #9
d0021318:	460568b3 			; <UNDEFINED> instruction: 0x460568b3
d002131c:	0000f8c9 	andeq	pc, r0, r9, asr #17
d0021320:	7838685b 	ldmdavc	r8!, {r0, r1, r3, r4, r6, fp, sp, lr}
d0021324:	d1762d00 	cmnle	r6, r0, lsl #26
d0021328:	4798685b 			; <UNDEFINED> instruction: 0x4798685b
d002132c:	4877703d 	ldmdami	r7!, {r0, r2, r3, r4, r5, ip, sp, lr}^
d0021330:	e71f4478 			; <UNDEFINED> instruction: 0xe71f4478
d0021334:	f0014640 			; <UNDEFINED> instruction: 0xf0014640
d0021338:	1cc3fd81 	stclne	13, cr15, [r3], {129}	; 0x81
d002133c:	7f80f5b3 	svcvc	0x0080f5b3
d0021340:	af35f63f 	svcge	0x0035f63f
d0021344:	1e464f72 	mcrne	15, 2, r4, cr6, cr2, {3}
d0021348:	447f4641 	ldrbtmi	r4, [pc], #-1601	; 0xd0021350
d002134c:	46384632 			; <UNDEFINED> instruction: 0x46384632
d0021350:	f96cf000 			; <UNDEFINED> instruction: 0xf96cf000
d0021354:	2204496f 	andcs	r4, r4, #1818624	; 0x1bc000
d0021358:	447919b8 	ldrbtmi	r1, [r9], #-2488	; 0xfffff648
d002135c:	f966f000 			; <UNDEFINED> instruction: 0xf966f000
d0021360:	9a04e791 	bls	0xd015b1ac
d0021364:	f8dbab08 			; <UNDEFINED> instruction: 0xf8dbab08
d0021368:	ee189000 	cdp	0, 1, cr9, cr8, cr0, {0}
d002136c:	f8531a10 			; <UNDEFINED> instruction: 0xf8531a10
d0021370:	eb023027 	bl	0xd00ad414
d0021374:	46182a09 	ldrmi	r2, [r8], -r9, lsl #20
d0021378:	46529305 	ldrbmi	r9, [r2], -r5, lsl #6
d002137c:	ff72f7fe 			; <UNDEFINED> instruction: 0xff72f7fe
d0021380:	b9489b05 	stmdblt	r8, {r0, r2, r8, r9, fp, ip, pc}^
d0021384:	4a654c64 	bmi	0xd197451c
d0021388:	447a447c 	ldrbtmi	r4, [sl], #-1148	; 0xfffffb84
d002138c:	71c0f44f 	bicvc	pc, r0, pc, asr #8
d0021390:	f0014620 			; <UNDEFINED> instruction: 0xf0014620
d0021394:	e01ffd1b 	ands	pc, pc, fp, lsl sp	; <UNPREDICTABLE>
d0021398:	eb092300 	bl	0xd0269fa0
d002139c:	f5c80608 			; <UNDEFINED> instruction: 0xf5c80608
d00213a0:	46501280 	ldrbmi	r1, [r0], -r0, lsl #5
d00213a4:	4b5e9307 	blmi	0xd17c5fc8
d00213a8:	441e447b 	ldrmi	r4, [lr], #-1147	; 0xfffffb85
d00213ac:	4631ab07 	ldrtmi	sl, [r1], -r7, lsl #22
d00213b0:	fbaef7fe 	blx	0xcebdf3b2
d00213b4:	b1884601 	orrlt	r4, r8, r1, lsl #12
d00213b8:	d1021cc3 	smlabtle	r2, r3, ip, r1
d00213bc:	44784859 	ldrbtmi	r4, [r8], #-2137	; 0xfffff7a7
d00213c0:	4c59e6d8 	mrrcmi	6, 13, lr, r9, cr8
d00213c4:	4a594653 	bmi	0xd1672d18
d00213c8:	71c0f44f 	bicvc	pc, r0, pc, asr #8
d00213cc:	9000447c 	andls	r4, r0, ip, ror r4
d00213d0:	4620447a 			; <UNDEFINED> instruction: 0x4620447a
d00213d4:	fcfaf001 	ldc2l	0, cr15, [sl], #4
d00213d8:	e6cb4620 	strb	r4, [fp], r0, lsr #12
d00213dc:	46309a07 	ldrtmi	r9, [r0], -r7, lsl #20
d00213e0:	fd16f001 	ldc2	0, cr15, [r6, #-4]
d00213e4:	4c52b128 	ldfmip	f3, [r2], {40}	; 0x28
d00213e8:	4a524653 	bmi	0xd14b2d3c
d00213ec:	447a447c 	ldrbtmi	r4, [sl], #-1148	; 0xfffffb84
d00213f0:	4b51e7cc 	blmi	0xd149b328
d00213f4:	9a073701 	bls	0xd01ef000
d00213f8:	4490447b 	ldrmi	r4, [r0], #1147	; 0x47b
d00213fc:	f84354b0 			; <UNDEFINED> instruction: 0xf84354b0
d0021400:	eb036039 	bl	0xd00f94ec
d0021404:	f8db09c9 			; <UNDEFINED> instruction: 0xf8db09c9
d0021408:	f8c93000 			; <UNDEFINED> instruction: 0xf8c93000
d002140c:	33012004 	movwcc	r2, #4100	; 0x1004
d0021410:	3000f8cb 	andcc	pc, r0, fp, asr #17
d0021414:	4949e751 	stmdbmi	r9, {r0, r4, r6, r8, r9, sl, sp, lr, pc}^
d0021418:	4479689b 	ldrbtmi	r6, [r9], #-2203	; 0xfffff765
d002141c:	20004798 	mulcs	r0, r8, r7
d0021420:	fa1af7ff 	blx	0xd06df424
d0021424:	28004605 	stmdacs	r0, {r0, r2, r9, sl, lr}
d0021428:	aea7f47f 	mcrge	4, 5, pc, cr7, cr15, {3}	; <UNPREDICTABLE>
d002142c:	783868b3 	ldmdavc	r8!, {r0, r1, r4, r5, r7, fp, sp, lr}
d0021430:	685b685b 	ldmdavs	fp, {r0, r1, r3, r4, r6, fp, sp, lr}^
d0021434:	703d4798 	mlasvc	sp, r8, r7, r4
d0021438:	5000f8c9 	andpl	pc, r0, r9, asr #17
d002143c:	4e40e69c 	mcrmi	6, 2, lr, cr0, cr12, {4}
d0021440:	48402300 	stmdami	r0, {r8, r9, sp}^
d0021444:	1280f44f 	addne	pc, r0, #1325400064	; 0x4f000000
d0021448:	9307447e 	movwls	r4, #29822	; 0x747e
d002144c:	ab074478 	blge	0xd01f2634
d0021450:	f7fe4631 			; <UNDEFINED> instruction: 0xf7fe4631
d0021454:	4605fb5d 			; <UNDEFINED> instruction: 0x4605fb5d
d0021458:	4601b988 	strmi	fp, [r1], -r8, lsl #19
d002145c:	46309a07 	ldrtmi	r9, [r0], -r7, lsl #20
d0021460:	fcd6f001 	ldc2l	0, cr15, [r6], {1}
d0021464:	9b07b9c0 	blls	0xd020fb6c
d0021468:	493754f5 	ldmdbmi	r7!, {r0, r2, r4, r5, r6, r7, sl, ip, lr}
d002146c:	44794628 	ldrbtmi	r4, [r9], #-1576	; 0xfffff9d8
d0021470:	fe78f7fe 	mrc2	7, 3, pc, cr8, cr14, {7}
d0021474:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0021478:	2000ae80 	andcs	sl, r0, r0, lsl #29
d002147c:	2804e008 	stmdacs	r4, {r3, sp, lr, pc}
d0021480:	4932d1f3 	ldmdbmi	r2!, {r0, r1, r4, r5, r6, r7, r8, ip, lr, pc}
d0021484:	4630227d 			; <UNDEFINED> instruction: 0x4630227d
d0021488:	f0004479 			; <UNDEFINED> instruction: 0xf0004479
d002148c:	2001f8cf 	andcs	pc, r1, pc, asr #17
d0021490:	fbd6f7fe 	blx	0xcf5df492
d0021494:	e6704604 	ldrbt	r4, [r0], -r4, lsl #12
d0021498:	0503f06f 	streq	pc, [r3, #-111]	; 0xffffff91
d002149c:	2800e7e5 	stmdacs	r0, {r0, r2, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d00214a0:	ae66f77f 	mcrge	7, 3, pc, cr6, cr15, {3}	; <UNPREDICTABLE>
d00214a4:	e65c2600 	ldrb	r2, [ip], -r0, lsl #12
d00214a8:	2001f000 	andcs	pc, r1, r0
d00214ac:	fffffda2 			; <UNDEFINED> instruction: 0xfffffda2
d00214b0:	fffffd92 			; <UNDEFINED> instruction: 0xfffffd92
d00214b4:	fffffd89 			; <UNDEFINED> instruction: 0xfffffd89
d00214b8:	0015371c 	andseq	r3, r5, ip, lsl r7
d00214bc:	fffffe75 			; <UNDEFINED> instruction: 0xfffffe75
d00214c0:	fffffe6a 			; <UNDEFINED> instruction: 0xfffffe6a
d00214c4:	fffffd61 			; <UNDEFINED> instruction: 0xfffffd61
d00214c8:	fffffd6d 			; <UNDEFINED> instruction: 0xfffffd6d
d00214cc:	fffffd8e 			; <UNDEFINED> instruction: 0xfffffd8e
d00214d0:	fffffda2 			; <UNDEFINED> instruction: 0xfffffda2
d00214d4:	fffffcee 			; <UNDEFINED> instruction: 0xfffffcee
d00214d8:	fffffd22 			; <UNDEFINED> instruction: 0xfffffd22
d00214dc:	fffffc86 			; <UNDEFINED> instruction: 0xfffffc86
d00214e0:	0005233a 	andeq	r2, r5, sl, lsr r3
d00214e4:	fffffdd2 			; <UNDEFINED> instruction: 0xfffffdd2
d00214e8:	0005232c 	andeq	r2, r5, ip, lsr #6
d00214ec:	0005257a 	andeq	r2, r5, sl, ror r5
d00214f0:	00052578 	andeq	r2, r5, r8, ror r5
d00214f4:	00052576 	andeq	r2, r5, r6, ror r5
d00214f8:	fffffd63 			; <UNDEFINED> instruction: 0xfffffd63
d00214fc:	000535d4 	ldrdeq	r3, [r5], -r4
d0021500:	fffffdeb 			; <UNDEFINED> instruction: 0xfffffdeb
d0021504:	fffffdd7 			; <UNDEFINED> instruction: 0xfffffdd7
d0021508:	00153932 	andseq	r3, r5, r2, lsr r9
d002150c:	fffffdb6 			; <UNDEFINED> instruction: 0xfffffdb6
d0021510:	0005226a 	andeq	r2, r5, sl, ror #4
d0021514:	fffffcf9 			; <UNDEFINED> instruction: 0xfffffcf9
d0021518:	00153734 	andseq	r3, r5, r4, lsr r7
d002151c:	fffffccd 			; <UNDEFINED> instruction: 0xfffffccd
d0021520:	00053504 	andeq	r3, r5, r4, lsl #10
d0021524:	fffffcb4 			; <UNDEFINED> instruction: 0xfffffcb4
d0021528:	001536f0 			; <UNDEFINED> instruction: 0x001536f0
d002152c:	fffffcc0 			; <UNDEFINED> instruction: 0xfffffcc0
d0021530:	001536d0 			; <UNDEFINED> instruction: 0x001536d0
d0021534:	fffffcb9 			; <UNDEFINED> instruction: 0xfffffcb9
d0021538:	0005342c 	andeq	r3, r5, ip, lsr #8
d002153c:	ffffeb0f 			; <UNDEFINED> instruction: 0xffffeb0f
d0021540:	00053464 	andeq	r3, r5, r4, ror #8
d0021544:	00153470 	andseq	r3, r5, r0, ror r4
d0021548:	fffffcb8 			; <UNDEFINED> instruction: 0xfffffcb8
d002154c:	000000c4 	andeq	r0, r0, r4, asr #1

Disassembly of section .text.progress_report:

d00101bc <.text.progress_report>:
d00101bc:	4a084613 	bmi	0xd0221a10
d00101c0:	b410447a 	ldrlt	r4, [r0], #-1146	; 0xfffffb86
d00101c4:	b1446814 	cmplt	r4, r4, lsl r8
d00101c8:	4601460a 	strmi	r4, [r1], -sl, lsl #12
d00101cc:	46a44805 	strtmi	r4, [r4], r5, lsl #16
d00101d0:	4b04f85d 	blmi	0xd014e34c
d00101d4:	68004478 	stmdavs	r0, {r3, r4, r5, r6, sl, lr}
d00101d8:	f85d4760 			; <UNDEFINED> instruction: 0xf85d4760
d00101dc:	47704b04 	ldrbmi	r4, [r0, -r4, lsl #22]!
d00101e0:	000633dc 	ldrdeq	r3, [r6], -ip
d00101e4:	000633cc 	andeq	r3, r6, ip, asr #7

Disassembly of section .text.progress_parse:

d00101f8 <.text.progress_parse>:
d00101f8:	4b18b538 	blmi	0xd063d6e0
d00101fc:	681b447b 	ldmdavs	fp, {r0, r1, r3, r4, r5, r6, sl, lr}
d0010200:	6f83b35b 	svcvs	0x0083b35b
d0010204:	da282b00 	ble	0xd0a1ae0c
d0010208:	447b4b15 	ldrbtmi	r4, [fp], #-2837	; 0xfffff4eb
d001020c:	f5b2681a 			; <UNDEFINED> instruction: 0xf5b2681a
d0010210:	d3224f00 			; <UNDEFINED> instruction: 0xd3224f00
d0010214:	447d4d13 	ldrbtmi	r4, [sp], #-3347	; 0xfffff2ed
d0010218:	2b64682b 	blcs	0xd192a2cc
d001021c:	68c1d81d 	stmiavs	r1, {r0, r2, r3, r4, fp, ip, lr, pc}^
d0010220:	44784811 	ldrbtmi	r4, [r8], #-2065	; 0xfffff7ef
d0010224:	44016800 	strmi	r6, [r1], #-2048	; 0xfffff800
d0010228:	f002fb03 			; <UNDEFINED> instruction: 0xf002fb03
d001022c:	30632364 	rsbcc	r2, r3, r4, ror #6
d0010230:	fbb04291 	blx	0xcec20c7e
d0010234:	bf28f0f3 	svclt	0x0028f0f3
d0010238:	42814611 	addmi	r4, r1, #17825792	; 0x1100000
d001023c:	434bd30d 	movtmi	sp, #45837	; 0xb30d
d0010240:	fbb3480a 	blx	0xcece2272
d0010244:	4478f4f2 	ldrbtmi	pc, [r8], #-1266	; 0xfffffb0e	; <UNPREDICTABLE>
d0010248:	ffb8f7ff 			; <UNDEFINED> instruction: 0xffb8f7ff
d001024c:	fbb42305 	blx	0xced18e6a
d0010250:	3301f3f3 	movwcc	pc, #5107	; 0x13f3	; <UNPREDICTABLE>
d0010254:	0383eb03 	orreq	lr, r3, #3072	; 0xc00
d0010258:	bd38602b 	ldclt	0, cr6, [r8, #-172]!	; 0xffffff54
d001025c:	000633a0 	andeq	r3, r6, r0, lsr #7
d0010260:	000633a2 	andeq	r3, r6, r2, lsr #7
d0010264:	0006338e 	andeq	r3, r6, lr, lsl #7
d0010268:	00063386 	andeq	r3, r6, r6, lsl #7
d001026c:	ffffff9e 			; <UNDEFINED> instruction: 0xffffff9e

Disassembly of section .text.error:

d0010270 <.text.error>:
d0010270:	b5306d83 	ldrlt	r6, [r0, #-3459]!	; 0xfffff27d
d0010274:	6a45b94b 	bvs	0xd117e7a8
d0010278:	6b436a84 	blvs	0xd10eac90
d001027c:	2030f890 	mlascs	r0, r0, r8, pc	; <UNPREDICTABLE>
d0010280:	e9c06683 	stmib	r0, {r0, r1, r7, r9, sl, sp, lr}^
d0010284:	e9c01516 	stmib	r0, {r1, r2, r4, r8, sl, ip}^
d0010288:	bd304218 	lfmlt	f4, 4, [r0, #-96]!	; 0xffffffa0

Disassembly of section .text.peek:

d001028c <.text.peek>:
d001028c:	441968c3 	ldrmi	r6, [r9], #-2243	; 0xfffff73d
d0010290:	428b6843 	addmi	r6, fp, #4390912	; 0x430000
d0010294:	6803bf86 	stmdavs	r3, {r1, r2, r7, r8, r9, sl, fp, ip, sp, pc}
d0010298:	20005c58 	andcs	r5, r0, r8, asr ip
d001029c:	Address 0x00000000d001029c is out of bounds.


Disassembly of section .text.read_char:

d001029e <.text.read_char>:
d001029e:	460268c3 	strmi	r6, [r2], -r3, asr #17
d00102a2:	428b6841 	addmi	r6, fp, #4259840	; 0x410000
d00102a6:	d016b510 	andsle	fp, r6, r0, lsl r5
d00102aa:	68011c5c 	stmdavs	r1, {r2, r3, r4, r6, sl, fp, ip}
d00102ae:	5ccc60c4 	stclpl	0, cr6, [ip], {196}	; 0xc4
d00102b2:	d0062c0a 	andle	r2, r6, sl, lsl #24
d00102b6:	d10b2c0d 	tstle	fp, sp, lsl #24
d00102ba:	f7ff2100 			; <UNDEFINED> instruction: 0xf7ff2100
d00102be:	280affe6 	stmdacs	sl, {r1, r2, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d00102c2:	6913d006 	ldmdbvs	r3, {r1, r2, ip, lr, pc}
d00102c6:	61133301 	tstvs	r3, r1, lsl #6
d00102ca:	61532301 	cmpvs	r3, r1, lsl #6
d00102ce:	bd104620 	ldclt	6, cr4, [r0, #-128]	; 0xffffff80
d00102d2:	33016953 	movwcc	r6, #6483	; 0x1953
d00102d6:	2400e7f9 	strcs	lr, [r0], #-2041	; 0xfffff807
d00102da:	Address 0x00000000d00102da is out of bounds.


Disassembly of section .text.here:

d00102dc <.text.here>:
d00102dc:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d00102e0:	4604680b 	strmi	r6, [r4], -fp, lsl #16
d00102e4:	221868cd 	andscs	r6, r8, #13434880	; 0xcd0000
d00102e8:	30047a0f 	andcc	r7, r4, pc, lsl #20
d00102ec:	6f8b441d 	svcvs	0x008b441d
d00102f0:	e9d12b00 	ldmib	r1, {r8, r9, fp, sp}^
d00102f4:	bfa89804 	svclt	0x00a89804
d00102f8:	f04f6f4e 			; <UNDEFINED> instruction: 0xf04f6f4e
d00102fc:	bfb80100 	svclt	0x00b80100
d0010300:	f0112600 			; <UNDEFINED> instruction: 0xf0112600
d0010304:	f44ff985 	vst2.32	{d31,d33}, [pc], r5
d0010308:	46207380 	strtmi	r7, [r0], -r0, lsl #7
d001030c:	f8c46025 			; <UNDEFINED> instruction: 0xf8c46025
d0010310:	f8c4900c 			; <UNDEFINED> instruction: 0xf8c4900c
d0010314:	61638010 	cmnvs	r3, r0, lsl r0
d0010318:	61e67627 	mvnvs	r7, r7, lsr #12
d001031c:	83f8e8bd 	mvnshi	lr, #12386304	; 0xbd0000

Disassembly of section .text.preproc_active:

d0010320 <.text.preproc_active>:
d0010320:	030cf24d 	movweq	pc, #49741	; 0xc24d	; <UNPREDICTABLE>
d0010324:	b14b58c3 	smlalbtlt	r5, fp, r3, r8
d0010328:	534ff503 	movtpl	pc, #62723	; 0xf503	; <UNPREDICTABLE>
d001032c:	eb003321 	bl	0xd001cfb8
d0010330:	79400083 	stmdbvc	r0, {r0, r1, r7}^
d0010334:	bf183800 	svclt	0x00183800
d0010338:	47702001 	ldrbmi	r2, [r0, -r1]!
d001033c:	47702001 	ldrbmi	r2, [r0, -r1]!

Disassembly of section .text.pp_space:

d0010340 <.text.pp_space>:
d0010340:	6a436a81 	bvs	0xd10ead4c
d0010344:	d204428b 	andle	r4, r4, #-1342177272	; 0xb0000008
d0010348:	2a20781a 	bcs	0xd082e3b8
d001034c:	2a09d002 	bcs	0xd028435c
d0010350:	4770d000 	ldrbmi	sp, [r0, -r0]!
d0010354:	62433301 	subvs	r3, r3, #67108864	; 0x4000000
d0010358:	Address 0x00000000d0010358 is out of bounds.


Disassembly of section .text.pp_line_end:

d001035a <.text.pp_line_end>:
d001035a:	4604b510 			; <UNDEFINED> instruction: 0x4604b510
d001035e:	686368e2 	stmdavs	r3!, {r1, r5, r6, r7, fp, sp, lr}^
d0010362:	d207429a 	andle	r4, r7, #-1610612727	; 0xa0000009
d0010366:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d001036a:	ff8ff7ff 			; <UNDEFINED> instruction: 0xff8ff7ff
d001036e:	d001280d 	andle	r2, r1, sp, lsl #16
d0010372:	d100280a 	tstle	r0, sl, lsl #16
d0010376:	4620bd10 			; <UNDEFINED> instruction: 0x4620bd10
d001037a:	ff90f7ff 			; <UNDEFINED> instruction: 0xff90f7ff
d001037e:	Address 0x00000000d001037e is out of bounds.


Disassembly of section .text.enum_constant_lookup:

d0010380 <.text.enum_constant_lookup>:
d0010380:	337ef500 	cmncc	lr, #0, 10	; <UNPREDICTABLE>
d0010384:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d0010388:	4190f8d3 			; <UNDEFINED> instruction: 0x4190f8d3
d001038c:	46062328 	strmi	r2, [r6], -r8, lsr #6
d0010390:	1e654688 	cdpne	6, 6, cr4, cr5, cr8, {4}
d0010394:	0404fb03 	streq	pc, [r4], #-2819	; 0xfffff4fd
d0010398:	f5044617 			; <UNDEFINED> instruction: 0xf5044617
d001039c:	34683478 	strbtcc	r3, [r8], #-1144	; 0xfffffb88
d00103a0:	da022d00 	ble	0xd009b7a8
d00103a4:	35fff04f 	ldrbcc	pc, [pc, #79]!	; 0xd00103fb	; <UNPREDICTABLE>
d00103a8:	f894e011 			; <UNDEFINED> instruction: 0xf894e011
d00103ac:	7a332024 	bvc	0xd0cd8444
d00103b0:	d002429a 	mulle	r2, sl, r2
d00103b4:	3c283d01 	stccc	13, cr3, [r8], #-4
d00103b8:	6863e7f2 	stmdavs	r3!, {r1, r4, r5, r6, r7, r8, r9, sl, sp, lr, pc}^
d00103bc:	d1f942bb 	ldrhle	r4, [r9, #43]!	; 0x2b
d00103c0:	4641463a 			; <UNDEFINED> instruction: 0x4641463a
d00103c4:	f0116820 			; <UNDEFINED> instruction: 0xf0116820
d00103c8:	2800f941 	stmdacs	r0, {r0, r6, r8, fp, ip, sp, lr, pc}
d00103cc:	4628d1f2 			; <UNDEFINED> instruction: 0x4628d1f2
d00103d0:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d

Disassembly of section .text.pp_take:

d00103d4 <.text.pp_take>:
d00103d4:	460eb570 			; <UNDEFINED> instruction: 0x460eb570
d00103d8:	f7ff4604 			; <UNDEFINED> instruction: 0xf7ff4604
d00103dc:	4630ffb1 			; <UNDEFINED> instruction: 0x4630ffb1
d00103e0:	fd2cf012 	stc2	0, cr15, [ip, #-72]!	; 0xffffffb8
d00103e4:	46056aa3 	strmi	r6, [r5], -r3, lsr #21
d00103e8:	1a1b6a60 	bne	0xd06ead70
d00103ec:	d20142ab 	andle	r4, r1, #-1342177270	; 0xb000000a
d00103f0:	bd702000 	ldcllt	0, cr2, [r0, #-0]
d00103f4:	4631462a 	ldrtmi	r4, [r1], -sl, lsr #12
d00103f8:	f928f011 			; <UNDEFINED> instruction: 0xf928f011
d00103fc:	d1f72800 	mvnsle	r2, r0, lsl #16
d0010400:	44286a60 	strtmi	r6, [r8], #-2656	; 0xfffff5a0
d0010404:	20016260 	andcs	r6, r1, r0, ror #4
d0010408:	Address 0x00000000d0010408 is out of bounds.


Disassembly of section .text.macro_index:

d001040a <.text.macro_index>:
d001040a:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d001040e:	462bf500 	strtmi	pc, [fp], -r0, lsl #10
d0010412:	444ff500 	strbmi	pc, [pc], #-1280	; 0xd001041a	; <UNPREDICTABLE>
d0010416:	46174688 	ldrmi	r4, [r7], -r8, lsl #13
d001041a:	25003688 	strcs	r3, [r0, #-1672]	; 0xfffff978
d001041e:	68233488 	stmdavs	r3!, {r3, r7, sl, ip, sp}
d0010422:	d80242ab 	stmdale	r2, {r0, r1, r3, r5, r7, r9, lr}
d0010426:	30fff04f 	rscscc	pc, pc, pc, asr #32
d001042a:	4630e00b 	ldrtmi	lr, [r0], -fp
d001042e:	fd05f012 	stc2	0, cr15, [r5, #-72]	; 0xffffffb8
d0010432:	d10842b8 			; <UNDEFINED> instruction: 0xd10842b8
d0010436:	4641463a 			; <UNDEFINED> instruction: 0x4641463a
d001043a:	f0114630 			; <UNDEFINED> instruction: 0xf0114630
d001043e:	b910f906 	ldmdblt	r0, {r1, r2, r8, fp, ip, sp, lr, pc}
d0010442:	e8bd4628 	pop	{r3, r5, r9, sl, lr}
d0010446:	350181f0 	strcc	r8, [r1, #-496]	; 0xfffffe10
d001044a:	e7e83648 	strb	r3, [r8, r8, asr #12]!

Disassembly of section .text.letter:

d001044e <.text.letter>:
d001044e:	0320f020 	nopeq	{32}
d0010452:	2b193b41 	blcs	0xd065f15e
d0010456:	f1a0d904 			; <UNDEFINED> instruction: 0xf1a0d904
d001045a:	4258035f 	subsmi	r0, r8, #2080374785	; 0x7c000001
d001045e:	47704158 			; <UNDEFINED> instruction: 0x47704158
d0010462:	47702001 	ldrbmi	r2, [r0, -r1]!

Disassembly of section .text.valid_api_name:

d001046c <.text.valid_api_name>:
d001046c:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d0010470:	46884606 	strmi	r4, [r8], r6, lsl #12
d0010474:	b19a4617 	orrslt	r4, sl, r7, lsl r6
d0010478:	2204491a 	andcs	r4, r4, #425984	; 0x68000
d001047c:	f0114479 			; <UNDEFINED> instruction: 0xf0114479
d0010480:	bb58f8e5 	bllt	0xd164e81c
d0010484:	5d302404 	cfldrspl	mvf2, [r0, #-16]!
d0010488:	ffe1f7ff 			; <UNDEFINED> instruction: 0xffe1f7ff
d001048c:	2500b330 	strcs	fp, [r0, #-816]	; 0xfffffcd0
d0010490:	b93a5d32 	ldmdblt	sl!, {r1, r4, r5, r8, sl, fp, ip, lr}
d0010494:	1e28b327 	cdpne	3, 2, cr11, cr8, cr7, {1}
d0010498:	2001bf18 	andcs	fp, r1, r8, lsl pc
d001049c:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d00104a0:	e7f04614 			; <UNDEFINED> instruction: 0xe7f04614
d00104a4:	2a2db197 	bcs	0xd0b7cb08
d00104a8:	1ca3d110 	stfned	f5, [r3], #64	; 0x40
d00104ac:	d20d4543 	andle	r4, sp, #281018368	; 0x10c00000
d00104b0:	5c701c61 	ldclpl	12, cr1, [r0], #-388	; 0xfffffe7c
d00104b4:	d109283e 	tstle	r9, lr, lsr r8
d00104b8:	f7ff5cf0 			; <UNDEFINED> instruction: 0xf7ff5cf0
d00104bc:	b128ffc8 	smlawtlt	r8, r8, pc, pc	; <UNPREDICTABLE>
d00104c0:	460c3501 	strmi	r3, [ip], -r1, lsl #10
d00104c4:	45a03401 	strmi	r3, [r0, #1025]!	; 0x401
d00104c8:	e007d8e2 	and	sp, r7, r2, ror #17
d00104cc:	f7ff4610 			; <UNDEFINED> instruction: 0xf7ff4610
d00104d0:	2800ffbe 	stmdacs	r0, {r1, r2, r3, r4, r5, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d00104d4:	3a30d1f6 	bcc	0xd0c44cb4
d00104d8:	d9f32a09 	ldmible	r3!, {r0, r3, r9, fp, sp}^
d00104dc:	e7dd2000 	ldrb	r2, [sp, r0]
d00104e0:	e7db2001 	ldrb	r2, [fp, r1]
d00104e4:	ffffffe6 			; <UNDEFINED> instruction: 0xffffffe6

Disassembly of section .text.hex_digit:

d00104e8 <.text.hex_digit>:
d00104e8:	38304603 	ldmdacc	r0!, {r0, r1, r9, sl, lr}
d00104ec:	d9082809 	stmdble	r8, {r0, r3, fp, sp}
d00104f0:	0020f043 	eoreq	pc, r0, r3, asr #32
d00104f4:	0361f1a0 	msreq	SPSR_c, #160, 2	; 0x28
d00104f8:	d8012b05 	stmdale	r1, {r0, r2, r8, r9, fp, sp}
d00104fc:	47703857 			; <UNDEFINED> instruction: 0x47703857
d0010500:	47702010 			; <UNDEFINED> instruction: 0x47702010

Disassembly of section .text.escape_byte.isra.0:

d001053c <.text.escape_byte.isra.0>:
d001053c:	47f0e92d 	ldrbmi	lr, [r0, sp, lsr #18]!
d0010540:	46059e09 	strmi	r9, [r5], -r9, lsl #28
d0010544:	f8dd461f 			; <UNDEFINED> instruction: 0xf8dd461f
d0010548:	6830a020 	ldmdavs	r0!, {r5, sp, pc}
d001054c:	8028f8dd 	ldrdhi	pc, [r8], -sp	; <UNPREDICTABLE>
d0010550:	60331c43 	eorsvs	r1, r3, r3, asr #24
d0010554:	2c787804 	ldclcs	8, cr7, [r8], #-16
d0010558:	2c6dd812 	stclcs	8, cr13, [sp], #-72	; 0xffffffb8
d001055c:	2c3fd828 	ldccs	8, cr13, [pc], #-160	; 0xd00104c4
d0010560:	2c21d84e 	stccs	8, cr13, [r1], #-312	; 0xfffffec8
d0010564:	f1a4d90c 			; <UNDEFINED> instruction: 0xf1a4d90c
d0010568:	fa5f0c22 	blx	0xd17d35f8
d001056c:	f04ffe8c 			; <UNDEFINED> instruction: 0xf04ffe8c
d0010570:	fa0c0c01 	blx	0xd031357c
d0010574:	f8dffc0e 			; <UNDEFINED> instruction: 0xf8dffc0e
d0010578:	ea1ce160 	b	0xd0748b00
d001057c:	d13a0f0e 	teqle	sl, lr, lsl #30
d0010580:	2c073c30 	stccs	12, cr3, [r7], {48}	; 0x30
d0010584:	4543d86a 	strbmi	sp, [r3, #-2154]	; 0xfffff796
d0010588:	7843d035 	stmdavc	r3, {r0, r2, r4, r5, ip, lr, pc}^
d001058c:	2b073b30 	blcs	0xd01df254
d0010590:	f100d831 			; <UNDEFINED> instruction: 0xf100d831
d0010594:	f8c60c02 			; <UNDEFINED> instruction: 0xf8c60c02
d0010598:	45e0c000 	strbmi	ip, [r0, #0]!
d001059c:	f1a37843 			; <UNDEFINED> instruction: 0xf1a37843
d00105a0:	eb030330 	bl	0xd00d1268
d00105a4:	f04004c4 			; <UNDEFINED> instruction: 0xf04004c4
d00105a8:	2cff8086 	ldclcs	0, cr8, [pc], #536	; 0xd00107c8
d00105ac:	e022d856 	eor	sp, r2, r6, asr r8
d00105b0:	0c6ef1a4 	stfeqp	f7, [lr], #-656	; 0xfffffd70
d00105b4:	0f0af1bc 	svceq	0x000af1bc
d00105b8:	f20fd8e2 	vadd.i8	<illegal reg q6.5>, <illegal reg q15.5>, q9
d00105bc:	f85e0e0c 			; <UNDEFINED> instruction: 0xf85e0e0c
d00105c0:	44e6c02c 	strbtmi	ip, [r6], #44	; 0x2c
d00105c4:	bf004770 	svclt	0x00004770
d00105c8:	00000107 	andeq	r0, r0, r7, lsl #2
d00105cc:	ffffffb9 			; <UNDEFINED> instruction: 0xffffffb9
d00105d0:	ffffffb9 			; <UNDEFINED> instruction: 0xffffffb9
d00105d4:	ffffffb9 			; <UNDEFINED> instruction: 0xffffffb9
d00105d8:	0000002d 	andeq	r0, r0, sp, lsr #32
d00105dc:	ffffffb9 			; <UNDEFINED> instruction: 0xffffffb9
d00105e0:	00000089 	andeq	r0, r0, r9, lsl #1
d00105e4:	ffffffb9 			; <UNDEFINED> instruction: 0xffffffb9
d00105e8:	0000008d 	andeq	r0, r0, sp, lsl #1
d00105ec:	ffffffb9 			; <UNDEFINED> instruction: 0xffffffb9
d00105f0:	00000091 	muleq	r0, r1, r0
d00105f4:	4620240d 	strtmi	r2, [r0], -sp, lsl #8
d00105f8:	87f0e8bd 			; <UNDEFINED> instruction: 0x87f0e8bd
d00105fc:	e7fa2408 	ldrb	r2, [sl, r8, lsl #8]!
d0010600:	0c5cf1a4 	ldfeqp	f7, [ip], {164}	; 0xa4
d0010604:	fe8cfa5f 	mcr2	10, 4, pc, cr12, cr15, {2}	; <UNPREDICTABLE>
d0010608:	0f0af1be 	svceq	0x000af1be
d001060c:	f1bcd8b8 			; <UNDEFINED> instruction: 0xf1bcd8b8
d0010610:	d8b50f0a 	ldmle	r5!, {r1, r3, r8, r9, sl, fp}
d0010614:	0e08f20f 	cdpeq	2, 0, cr15, cr8, cr15, {0}
d0010618:	c02cf85e 	eorgt	pc, ip, lr, asr r8	; <UNPREDICTABLE>
d001061c:	477044e6 	ldrbmi	r4, [r0, -r6, ror #9]!
d0010620:	ffffffd7 			; <UNDEFINED> instruction: 0xffffffd7
d0010624:	ffffff61 			; <UNDEFINED> instruction: 0xffffff61
d0010628:	ffffff61 			; <UNDEFINED> instruction: 0xffffff61
d001062c:	ffffff61 			; <UNDEFINED> instruction: 0xffffff61
d0010630:	ffffff61 			; <UNDEFINED> instruction: 0xffffff61
d0010634:	000000b3 	strheq	r0, [r0], -r3
d0010638:	ffffffdd 			; <UNDEFINED> instruction: 0xffffffdd
d001063c:	ffffff61 			; <UNDEFINED> instruction: 0xffffff61
d0010640:	ffffff61 			; <UNDEFINED> instruction: 0xffffff61
d0010644:	ffffff61 			; <UNDEFINED> instruction: 0xffffff61
d0010648:	0000002d 	andeq	r0, r0, sp, lsr #32
d001064c:	e7d2240c 	ldrb	r2, [r2, ip, lsl #8]
d0010650:	e7d02409 	ldrb	r2, [r0, r9, lsl #8]
d0010654:	e7ce240b 	strb	r2, [lr, fp, lsl #8]
d0010658:	d1044543 	tstle	r4, r3, asr #10
d001065c:	b9fc6dac 	ldmiblt	ip!, {r2, r3, r5, r7, r8, sl, fp, sp, lr}^
d0010660:	447b4b1e 	ldrbtmi	r4, [fp], #-2846	; 0xfffff4e2
d0010664:	7840e020 	stmdavc	r0, {r5, sp, lr, pc}^
d0010668:	ff3ef7ff 			; <UNDEFINED> instruction: 0xff3ef7ff
d001066c:	d0f52810 	rscsle	r2, r5, r0, lsl r8
d0010670:	f8d62400 			; <UNDEFINED> instruction: 0xf8d62400
d0010674:	45c89000 	strbmi	r9, [r8]
d0010678:	f899d0bd 			; <UNDEFINED> instruction: 0xf899d0bd
d001067c:	f7ff0000 			; <UNDEFINED> instruction: 0xf7ff0000
d0010680:	2810ff33 	ldmdacs	r0, {r0, r1, r4, r5, r8, r9, sl, fp, ip, sp, lr, pc}
d0010684:	f109d0b7 			; <UNDEFINED> instruction: 0xf109d0b7
d0010688:	01240301 			; <UNDEFINED> instruction: 0x01240301
d001068c:	f8996033 			; <UNDEFINED> instruction: 0xf8996033
d0010690:	f7ff0000 			; <UNDEFINED> instruction: 0xf7ff0000
d0010694:	4404ff29 	strmi	pc, [r4], #-3881	; 0xfffff0d7
d0010698:	d9ea2cff 	stmible	sl!, {r0, r1, r2, r3, r4, r5, r6, r7, sl, fp, sp}^
d001069c:	b10c6dac 	smlatblt	ip, ip, sp, r6
d00106a0:	e7a82400 	str	r2, [r8, r0, lsl #8]!
d00106a4:	447b4b0e 	ldrbtmi	r4, [fp], #-2830	; 0xfffff4f2
d00106a8:	a068f8c5 	rsbge	pc, r8, r5, asr #17
d00106ac:	3116e9c5 	tstcc	r6, r5, asr #19
d00106b0:	2718e9c5 	ldrcs	lr, [r8, -r5, asr #19]
d00106b4:	7883e79f 	stmvc	r3, {r0, r1, r2, r3, r4, r7, r8, r9, sl, sp, lr, pc}
d00106b8:	2b073b30 	blcs	0xd01df380
d00106bc:	af75f63f 	svcge	0x0075f63f
d00106c0:	60331cc3 	eorsvs	r1, r3, r3, asr #25
d00106c4:	3b307883 	blcc	0xd0c2e8d8
d00106c8:	04c4eb03 	strbeq	lr, [r4], #2819	; 0xb03
d00106cc:	240ae76d 	strcs	lr, [sl], #-1901	; 0xfffff893
d00106d0:	2407e791 	strcs	lr, [r7], #-1937	; 0xfffff86f
d00106d4:	bf00e78f 	svclt	0x0000e78f
d00106d8:	20000021 	andcs	r0, r0, r1, lsr #32
d00106dc:	fffffeb6 			; <UNDEFINED> instruction: 0xfffffeb6
d00106e0:	fffffe5a 			; <UNDEFINED> instruction: 0xfffffe5a

Disassembly of section .text.same_name.isra.0:

d00106e4 <.text.same_name.isra.0>:
d00106e4:	460cb510 			; <UNDEFINED> instruction: 0x460cb510
d00106e8:	429c4611 	addsmi	r4, ip, #17825792	; 0x1100000
d00106ec:	4622d106 	strtmi	sp, [r2], -r6, lsl #2
d00106f0:	ffacf010 			; <UNDEFINED> instruction: 0xffacf010
d00106f4:	f080fab0 			; <UNDEFINED> instruction: 0xf080fab0
d00106f8:	bd100940 	vldrlt.16	s0, [r0, #-128]	; 0xffffff80	; <UNPREDICTABLE>
d00106fc:	e7fc2000 	ldrb	r2, [ip, r0]!

Disassembly of section .text.find_record.isra.0:

d0010700 <.text.find_record.isra.0>:
d0010700:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d0010704:	3467f500 	strbtcc	pc, [r7], #-1280	; 0xfffffb00	; <UNPREDICTABLE>
d0010708:	4690460f 	ldrmi	r4, [r0], pc, lsl #12
d001070c:	f5042500 			; <UNDEFINED> instruction: 0xf5042500
d0010710:	f50074e4 			; <UNDEFINED> instruction: 0xf50074e4
d0010714:	fa5f3675 	blx	0xd17de0f0
d0010718:	f8d6f983 			; <UNDEFINED> instruction: 0xf8d6f983
d001071c:	429d3388 	addsmi	r3, sp, #136, 6	; 0x20000002
d0010720:	f04fd302 			; <UNDEFINED> instruction: 0xf04fd302
d0010724:	e00e30ff 	strd	r3, [lr], -pc	; <UNPREDICTABLE>
d0010728:	3264f894 	rsbcc	pc, r4, #148, 16	; 0x940000
d001072c:	4643b96b 	strbmi	fp, [r3], -fp, ror #18
d0010730:	e9d4463a 	ldmib	r4, {r1, r3, r4, r5, r9, sl, lr}^
d0010734:	f7ff0100 			; <UNDEFINED> instruction: 0xf7ff0100
d0010738:	b130ffd5 	teqlt	r0, r5	; <illegal shifter operand>	; <UNPREDICTABLE>
d001073c:	3263f894 	rsbcc	pc, r3, #148, 16	; 0x940000
d0010740:	d102454b 	tstle	r2, fp, asr #10
d0010744:	e8bd4628 	pop	{r3, r5, r9, sl, lr}
d0010748:	350183f8 	strcc	r8, [r1, #-1016]	; 0xfffffc08
d001074c:	741af504 	ldrvc	pc, [sl], #-1284	; 0xfffffafc
d0010750:	Address 0x00000000d0010750 is out of bounds.


Disassembly of section .text.records_equal:

d0010752 <.text.records_equal>:
d0010752:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d0010756:	3260f8d0 	rsbcc	pc, r0, #208, 16	; 0xd00000
d001075a:	f0234606 			; <UNDEFINED> instruction: 0xf0234606
d001075e:	f8d1427f 			; <UNDEFINED> instruction: 0xf8d1427f
d0010762:	f0233260 			; <UNDEFINED> instruction: 0xf0233260
d0010766:	429a437f 	addsmi	r4, sl, #-67108863	; 0xfc000001
d001076a:	2000d002 	andcs	sp, r0, r2
d001076e:	83f8e8bd 	mvnshi	lr, #12386304	; 0xbd0000
d0010772:	2263f890 	rsbcs	pc, r3, #144, 16	; 0x900000
d0010776:	3263f891 	rsbcc	pc, r3, #9502720	; 0x910000
d001077a:	d1f6429a 			; <UNDEFINED> instruction: 0xd1f6429a
d001077e:	460c4605 	strmi	r4, [ip], -r5, lsl #12
d0010782:	f8962700 			; <UNDEFINED> instruction: 0xf8962700
d0010786:	429f3262 	addsmi	r3, pc, #536870918	; 0x20000006
d001078a:	2001d301 	andcs	sp, r1, r1, lsl #6
d001078e:	6a63e7ee 	bvs	0xd190a74e
d0010792:	6a2246a9 	bvs	0xd08a223e
d0010796:	6a6946a0 	bvs	0xd1a6221e
d001079a:	f7ff6a28 			; <UNDEFINED> instruction: 0xf7ff6a28
d001079e:	2800ffa2 	stmdacs	r0, {r1, r5, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d00107a2:	f895d0e3 			; <UNDEFINED> instruction: 0xf895d0e3
d00107a6:	f8942040 			; <UNDEFINED> instruction: 0xf8942040
d00107aa:	429a3040 	addsmi	r3, sl, #64	; 0x40
d00107ae:	f895d1dd 			; <UNDEFINED> instruction: 0xf895d1dd
d00107b2:	f8942041 			; <UNDEFINED> instruction: 0xf8942041
d00107b6:	429a3041 	addsmi	r3, sl, #65	; 0x41
d00107ba:	f8b9d1d7 			; <UNDEFINED> instruction: 0xf8b9d1d7
d00107be:	35242042 	strcc	r2, [r4, #-66]!	; 0xffffffbe
d00107c2:	3042f8b8 	strhcc	pc, [r2], #-136	; 0xffffff78	; <UNPREDICTABLE>
d00107c6:	429a3424 	addsmi	r3, sl, #36, 8	; 0x24000000
d00107ca:	3701d1cf 	strcc	sp, [r1, -pc, asr #3]
d00107ce:	Address 0x00000000d00107ce is out of bounds.


Disassembly of section .text.find_local.isra.0:

d00107d0 <.text.find_local.isra.0>:
d00107d0:	2392f500 	orrscs	pc, r2, #0, 10
d00107d4:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d00107d8:	6238f8d3 	eorsvs	pc, r8, #13828096	; 0xd30000
d00107dc:	460f2530 			; <UNDEFINED> instruction: 0x460f2530
d00107e0:	fb054690 	blx	0xd016222a
d00107e4:	f5000006 			; <UNDEFINED> instruction: 0xf5000006
d00107e8:	f5042490 			; <UNDEFINED> instruction: 0xf5042490
d00107ec:	b91664c1 	ldmdblt	r6, {r0, r6, r7, sl, sp, lr}
d00107f0:	30fff04f 	rscscc	pc, pc, pc, asr #32
d00107f4:	6861e00a 	stmdavs	r1!, {r1, r3, sp, lr, pc}^
d00107f8:	463a4643 	ldrtmi	r4, [sl], -r3, asr #12
d00107fc:	0930f854 	ldmdbeq	r0!, {r2, r4, r6, fp, ip, sp, lr, pc}
d0010800:	f7ff3e01 			; <UNDEFINED> instruction: 0xf7ff3e01
d0010804:	2800ff6f 	stmdacs	r0, {r0, r1, r2, r3, r5, r6, r8, r9, sl, fp, ip, sp, lr, pc}
d0010808:	4630d0f1 			; <UNDEFINED> instruction: 0x4630d0f1
d001080c:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d

Disassembly of section .text.find_global.isra.0:

d0010810 <.text.find_global.isra.0>:
d0010810:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d0010814:	355ff500 	ldrbcc	pc, [pc, #-1280]	; 0xd001031c	; <UNPREDICTABLE>
d0010818:	460f4606 	strmi	r4, [pc], -r6, lsl #12
d001081c:	f5054690 			; <UNDEFINED> instruction: 0xf5054690
d0010820:	24007571 	strcs	r7, [r0], #-1393	; 0xfffffa8f
d0010824:	3967f500 	stmdbcc	r7!, {r8, sl, ip, sp, lr, pc}^
d0010828:	31c4f8d9 	ldrdcc	pc, [r4, #137]	; 0x89
d001082c:	d302429c 	movwle	r4, #8860	; 0x229c
d0010830:	30fff04f 	rscscc	pc, pc, pc, asr #32
d0010834:	f895e00c 			; <UNDEFINED> instruction: 0xf895e00c
d0010838:	7a332029 	bvc	0xd0cd88e4
d001083c:	d109429a 			; <UNDEFINED> instruction: 0xd109429a
d0010840:	463a4643 	ldrtmi	r4, [sl], -r3, asr #12
d0010844:	0100e9d5 	ldrdeq	lr, [r0, -r5]
d0010848:	ff4cf7ff 			; <UNDEFINED> instruction: 0xff4cf7ff
d001084c:	4620b110 			; <UNDEFINED> instruction: 0x4620b110
d0010850:	83f8e8bd 	mvnshi	lr, #12386304	; 0xbd0000
d0010854:	353c3401 	ldrcc	r3, [ip, #-1025]!	; 0xfffffbff
d0010858:	Address 0x00000000d0010858 is out of bounds.


Disassembly of section .text.find_alias.isra.0:

d001085a <.text.find_alias.isra.0>:
d001085a:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d001085e:	3575f500 	ldrbcc	pc, [r5, #-1280]!	; 0xfffffb00	; <UNPREDICTABLE>
d0010862:	460f4606 	strmi	r4, [pc], -r6, lsl #12
d0010866:	f5054690 			; <UNDEFINED> instruction: 0xf5054690
d001086a:	24007563 	strcs	r7, [r0], #-1379	; 0xfffffa9d
d001086e:	3978f500 	ldmdbcc	r8!, {r8, sl, ip, sp, lr, pc}^
d0010872:	308cf8d9 	ldrdcc	pc, [ip], r9
d0010876:	d302429c 	movwle	r4, #8860	; 0x229c
d001087a:	30fff04f 	rscscc	pc, pc, pc, asr #32
d001087e:	f895e00c 			; <UNDEFINED> instruction: 0xf895e00c
d0010882:	7a332021 	bvc	0xd0cd890e
d0010886:	d109429a 			; <UNDEFINED> instruction: 0xd109429a
d001088a:	463a4643 	ldrtmi	r4, [sl], -r3, asr #12
d001088e:	0100e9d5 	ldrdeq	lr, [r0, -r5]
d0010892:	ff27f7ff 			; <UNDEFINED> instruction: 0xff27f7ff
d0010896:	4620b110 			; <UNDEFINED> instruction: 0x4620b110
d001089a:	83f8e8bd 	mvnshi	lr, #12386304	; 0xbd0000
d001089e:	35243401 	strcc	r3, [r4, #-1025]!	; 0xfffffbff
d00108a2:	Address 0x00000000d00108a2 is out of bounds.


Disassembly of section .text.is_record_type:

d00108a4 <.text.is_record_type>:
d00108a4:	f46f6ac3 	vld1.64	{d22-d23}, [pc], r3
d00108a8:	189a728b 	ldmne	sl, {r0, r1, r3, r7, r9, ip, sp, lr}
d00108ac:	b5102a01 	ldrlt	r2, [r0, #-2561]	; 0xfffff5ff
d00108b0:	d8014604 	stmdale	r1, {r2, r9, sl, lr}
d00108b4:	bd102001 	ldclt	0, cr2, [r0, #-4]
d00108b8:	1201f240 	andne	pc, r1, #64, 4
d00108bc:	d10e4293 			; <UNDEFINED> instruction: 0xd10e4293
d00108c0:	698169c2 	stmibvs	r1, {r1, r6, r7, r8, fp, sp, lr}
d00108c4:	ffc9f7ff 			; <UNDEFINED> instruction: 0xffc9f7ff
d00108c8:	db081e03 	blle	0xd02180dc
d00108cc:	fb002024 	blx	0xd0018966
d00108d0:	f5004003 			; <UNDEFINED> instruction: 0xf5004003
d00108d4:	f8903075 			; <UNDEFINED> instruction: 0xf8903075
d00108d8:	2bff33ac 	blcs	0xcffdd790
d00108dc:	2000d1ea 	andcs	sp, r0, sl, ror #3
d00108e0:	Address 0x00000000d00108e0 is out of bounds.


Disassembly of section .text.find_function.isra.0:

d00108e2 <.text.find_function.isra.0>:
d00108e2:	47f0e92d 	ldrbmi	lr, [r0, sp, lsr #18]!
d00108e6:	347ff500 	ldrbtcc	pc, [pc], #-1280	; 0xd00108ee	; <UNPREDICTABLE>
d00108ea:	46884606 	strmi	r4, [r8], r6, lsl #12
d00108ee:	f5044691 			; <UNDEFINED> instruction: 0xf5044691
d00108f2:	2500740a 	strcs	r7, [r0, #-1034]	; 0xfffffbf6
d00108f6:	37fff04f 	ldrbcc	pc, [pc, pc, asr #32]!	; <UNPREDICTABLE>
d00108fa:	2a86f500 	bcs	0xce1cdd02
d00108fe:	3628f8da 			; <UNDEFINED> instruction: 0x3628f8da
d0010902:	d20f429d 	andle	r4, pc, #-805306359	; 0xd0000009
d0010906:	4642464b 	strbmi	r4, [r2], -fp, asr #12
d001090a:	0100e9d4 	ldrdeq	lr, [r0, -r4]
d001090e:	fee9f7ff 	mcr2	7, 7, pc, cr9, cr15, {7}	; <UNPREDICTABLE>
d0010912:	f894b160 			; <UNDEFINED> instruction: 0xf894b160
d0010916:	b1433028 	cmplt	r3, r8, lsr #32
d001091a:	2029f894 	mlacs	r9, r4, r8, pc	; <UNPREDICTABLE>
d001091e:	429a7a33 	addsmi	r7, sl, #208896	; 0x33000
d0010922:	462fd104 	strtmi	sp, [pc], -r4, lsl #2
d0010926:	e8bd4638 	pop	{r3, r4, r5, r9, sl, lr}
d001092a:	462f87f0 			; <UNDEFINED> instruction: 0x462f87f0
d001092e:	34383501 	ldrtcc	r3, [r8], #-1281	; 0xfffffaff
d0010932:	Address 0x00000000d0010932 is out of bounds.


Disassembly of section .text.name_is.isra.0:

d0010934 <.text.name_is.isra.0>:
d0010934:	460db537 			; <UNDEFINED> instruction: 0x460db537
d0010938:	46104604 	ldrmi	r4, [r0], -r4, lsl #12
d001093c:	f0129201 			; <UNDEFINED> instruction: 0xf0129201
d0010940:	42a8fa7d 	adcmi	pc, r8, #512000	; 0x7d000
d0010944:	99014602 	stmdbls	r1, {r1, r9, sl, lr}
d0010948:	4620d107 	strtmi	sp, [r0], -r7, lsl #2
d001094c:	fe7ef010 	mrc2	0, 3, pc, cr14, cr0, {0}
d0010950:	f080fab0 			; <UNDEFINED> instruction: 0xf080fab0
d0010954:	b0030940 	andlt	r0, r3, r0, asr #18
d0010958:	2000bd30 	andcs	fp, r0, r0, lsr sp
d001095c:	Address 0x00000000d001095c is out of bounds.


Disassembly of section .text.find_api_call.isra.0:

d001095e <.text.find_api_call.isra.0>:
d001095e:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d0010962:	4550f500 	ldrbmi	pc, [r0, #-1280]	; 0xfffffb00	; <UNPREDICTABLE>
d0010966:	4450f500 	ldrbmi	pc, [r0], #-1280	; 0xfffffb00	; <UNPREDICTABLE>
d001096a:	4690460f 	ldrmi	r4, [r0], pc, lsl #12
d001096e:	26003524 	strcs	r3, [r0], -r4, lsr #10
d0010972:	6823341c 	stmdavs	r3!, {r2, r3, r4, sl, ip, sp}
d0010976:	d304429e 	movwle	r4, #17054	; 0x429e
d001097a:	0900f04f 	stmdbeq	r0, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d001097e:	e8bd4648 	pop	{r3, r6, r9, sl, lr}
d0010982:	462a83f8 			; <UNDEFINED> instruction: 0x462a83f8
d0010986:	46384641 	ldrtmi	r4, [r8], -r1, asr #12
d001098a:	f7ff46a9 			; <UNDEFINED> instruction: 0xf7ff46a9
d001098e:	3554ffd2 	ldrbcc	pc, [r4, #-4050]	; 0xfffff02e	; <UNPREDICTABLE>
d0010992:	d1f32800 	mvnsle	r2, r0, lsl #16
d0010996:	e7ec3601 	strb	r3, [ip, r1, lsl #12]!

Disassembly of section .text.find_api_constant.isra.0:

d001099a <.text.find_api_constant.isra.0>:
d001099a:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d001099e:	3582f500 	strcc	pc, [r2, #1280]	; 0x500
d00109a2:	4450f500 	ldrbmi	pc, [r0], #-1280	; 0xfffffb00	; <UNPREDICTABLE>
d00109a6:	4690460f 	ldrmi	r4, [r0], pc, lsl #12
d00109aa:	260035a4 	strcs	r3, [r0], -r4, lsr #11
d00109ae:	68233420 	stmdavs	r3!, {r5, sl, ip, sp}
d00109b2:	d304429e 	movwle	r4, #17054	; 0x429e
d00109b6:	0900f04f 	stmdbeq	r0, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d00109ba:	e8bd4648 	pop	{r3, r6, r9, sl, lr}
d00109be:	462a83f8 			; <UNDEFINED> instruction: 0x462a83f8
d00109c2:	46384641 	ldrtmi	r4, [r8], -r1, asr #12
d00109c6:	f7ff46a9 			; <UNDEFINED> instruction: 0xf7ff46a9
d00109ca:	3524ffb4 	strcc	pc, [r4, #-4020]!	; 0xfffff04c
d00109ce:	d1f32800 	mvnsle	r2, r0, lsl #16
d00109d2:	e7ec3601 	strb	r3, [ip, r1, lsl #12]!

Disassembly of section .text.pp_unary:

d00109ec <.text.pp_unary>:
d00109ec:	e92d6ac3 	push	{r0, r1, r6, r7, r9, fp, sp, lr}
d00109f0:	1c5a43f7 	mrrcne	3, 15, r4, sl, cr7
d00109f4:	2a204604 	bcs	0xd082220c
d00109f8:	d90962c2 	stmdble	r9, {r1, r6, r7, r9, sp, lr}
d00109fc:	26002201 	strcs	r2, [r0], -r1, lsl #4
d0010a00:	62c32700 	sbcvs	r2, r3, #0, 14
d0010a04:	46306302 	ldrtmi	r6, [r0], -r2, lsl #6
d0010a08:	b0034639 	andlt	r4, r3, r9, lsr r6
d0010a0c:	83f0e8bd 	mvnshi	lr, #12386304	; 0xbd0000
d0010a10:	44794986 	ldrbtmi	r4, [r9], #-2438	; 0xfffff67a
d0010a14:	fcdef7ff 	ldc2l	7, cr15, [lr], {255}	; 0xff
d0010a18:	4620b148 	strtmi	fp, [r0], -r8, asr #2
d0010a1c:	ffe6f7ff 			; <UNDEFINED> instruction: 0xffe6f7ff
d0010a20:	0301ea50 	movweq	lr, #6736	; 0x1a50
d0010a24:	2601bf0c 	strcs	fp, [r1], -ip, lsl #30
d0010a28:	27002600 	strcs	r2, [r0, -r0, lsl #12]
d0010a2c:	4980e00a 	stmibmi	r0, {r1, r3, sp, lr, pc}
d0010a30:	44794620 	ldrbtmi	r4, [r9], #-1568	; 0xfffff9e0
d0010a34:	fccef7ff 	stc2l	7, cr15, [lr], {255}	; 0xff
d0010a38:	4620b140 	strtmi	fp, [r0], -r0, asr #2
d0010a3c:	ffd6f7ff 			; <UNDEFINED> instruction: 0xffd6f7ff
d0010a40:	43cf43c6 	bicmi	r4, pc, #402653187	; 0x18000003
d0010a44:	3b016ae3 	blcc	0xd006b5d8
d0010a48:	e7dc62e3 	ldrb	r6, [ip, r3, ror #5]
d0010a4c:	46204979 			; <UNDEFINED> instruction: 0x46204979
d0010a50:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d0010a54:	b128fcbf 	msrlt	CPSR_f, pc	; <illegal shifter operand>
d0010a58:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010a5c:	4606ffc7 	strmi	pc, [r6], -r7, asr #31
d0010a60:	e7ef460f 	strb	r4, [pc, pc, lsl #12]!
d0010a64:	46204974 			; <UNDEFINED> instruction: 0x46204974
d0010a68:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d0010a6c:	b130fcb3 	teqlt	r0, r3	; <illegal shifter operand>	; <UNPREDICTABLE>
d0010a70:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010a74:	4246ffbb 	submi	pc, r6, #748	; 0x2ec
d0010a78:	0741eb61 	strbeq	lr, [r1, -r1, ror #22]
d0010a7c:	4620e7e2 	strtmi	lr, [r0], -r2, ror #15
d0010a80:	fc5ef7ff 	mrrc2	7, 15, pc, lr, cr15	; <UNPREDICTABLE>
d0010a84:	1c5a6ae3 	mrrcne	10, 14, r6, sl, cr3
d0010a88:	62e22a20 	rscvs	r2, r2, #32, 20	; 0x20000
d0010a8c:	2201d904 	andcs	sp, r1, #4, 18	; 0x10000
d0010a90:	62e32600 	rscvs	r2, r3, #0, 12
d0010a94:	e7c86322 	strb	r6, [r8, r2, lsr #6]
d0010a98:	44794968 	ldrbtmi	r4, [r9], #-2408	; 0xfffff698
d0010a9c:	fc9af7ff 	ldc2	7, cr15, [sl], {255}	; 0xff
d0010aa0:	4620b168 	strtmi	fp, [r0], -r8, ror #2
d0010aa4:	fb3cf000 	blx	0xd0f4caae
d0010aa8:	4965460f 	stmdbmi	r5!, {r0, r1, r2, r3, r9, sl, lr}^
d0010aac:	44794606 	ldrbtmi	r4, [r9], #-1542	; 0xfffff9fa
d0010ab0:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010ab4:	bba0fc8f 	bllt	0xce84fcf8
d0010ab8:	63232301 			; <UNDEFINED> instruction: 0x63232301
d0010abc:	6a65e031 	bvs	0xd1988b88
d0010ac0:	8028f8d4 	ldrdhi	pc, [r8], -r4	; <UNPREDICTABLE>
d0010ac4:	d2514545 	subsle	r4, r1, #289406976	; 0x11400000
d0010ac8:	f1a07828 			; <UNDEFINED> instruction: 0xf1a07828
d0010acc:	2b090330 	blcs	0xd0251794
d0010ad0:	eba8d849 	bl	0xcea46bfc
d0010ad4:	2b020305 	blcs	0xd00916f0
d0010ad8:	2830dd27 	ldmdacs	r0!, {r0, r1, r2, r5, r8, sl, fp, ip, lr, pc}
d0010adc:	786bd12a 	stmdavc	fp!, {r1, r3, r5, r8, ip, lr, pc}^
d0010ae0:	03dff003 	bicseq	pc, pc, #3
d0010ae4:	d1272b58 			; <UNDEFINED> instruction: 0xd1272b58
d0010ae8:	21103502 	tstcs	r0, r2, lsl #10
d0010aec:	25006265 	strcs	r6, [r0, #-613]	; 0xfffffd9b
d0010af0:	27002600 	strcs	r2, [r0, -r0, lsl #12]
d0010af4:	0901f04f 	stmdbeq	r1, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d0010af8:	45906a62 	ldrmi	r6, [r0, #2658]	; 0xa62
d0010afc:	8092f240 	addshi	pc, r2, r0, asr #4
d0010b00:	f7ff7810 			; <UNDEFINED> instruction: 0xf7ff7810
d0010b04:	4281fcf1 	addmi	pc, r1, #61696	; 0xf100
d0010b08:	b91dd818 	ldmdblt	sp, {r3, r4, fp, ip, lr, pc}
d0010b0c:	45902301 	ldrmi	r2, [r0, #769]	; 0x301
d0010b10:	d9066323 	stmdble	r6, {r0, r1, r5, r8, r9, sp, lr}
d0010b14:	f0037813 			; <UNDEFINED> instruction: 0xf0037813
d0010b18:	2b5503df 	blcs	0xd1551a9c
d0010b1c:	3201d101 	andcc	sp, r1, #1073741824	; 0x40000000
d0010b20:	6ae36262 	bvs	0xcf8e94b0
d0010b24:	62e33b01 	rscvs	r3, r3, #1024	; 0x400
d0010b28:	2830e78c 	ldmdacs	r0!, {r2, r3, r7, r8, r9, sl, sp, lr, pc}
d0010b2c:	210abf14 	tstcs	sl, r4, lsl pc
d0010b30:	e7dc2108 	ldrb	r2, [ip, r8, lsl #2]
d0010b34:	e7da210a 	ldrb	r2, [sl, sl, lsl #2]
d0010b38:	e7d82108 	ldrb	r2, [r8, r8, lsl #2]
d0010b3c:	35011c53 	strcc	r1, [r1, #-3155]	; 0xfffff3ad
d0010b40:	78106263 	ldmdavc	r0, {r0, r1, r5, r6, r9, sp, lr}
d0010b44:	fcd0f7ff 	ldc2l	7, cr15, [r0], {255}	; 0xff
d0010b48:	fbb343c3 	blx	0xcece1a5e
d0010b4c:	42b3f3f1 	adcsmi	pc, r3, #-1006632957	; 0xc4000003
d0010b50:	2306fba1 	movwcs	pc, #27553	; 0x6ba1	; <UNPREDICTABLE>
d0010b54:	f8c4bf38 			; <UNDEFINED> instruction: 0xf8c4bf38
d0010b58:	18169030 	ldmdane	r6, {r4, r5, ip, pc}
d0010b5c:	3307fb01 	movwcc	pc, #31489	; 0x7b01	; <UNPREDICTABLE>
d0010b60:	0700f143 	streq	pc, [r0, -r3, asr #2]
d0010b64:	f7ffe7c8 			; <UNDEFINED> instruction: 0xf7ffe7c8
d0010b68:	b930fc72 	ldmdblt	r0!, {r1, r4, r5, r6, sl, fp, ip, sp, lr, pc}
d0010b6c:	63232301 			; <UNDEFINED> instruction: 0x63232301
d0010b70:	27002600 	strcs	r2, [r0, -r0, lsl #12]
d0010b74:	3201e7d5 	andcc	lr, r1, #55836672	; 0x3540000
d0010b78:	6a626262 	bvs	0xd18a9508
d0010b7c:	d9084590 	stmdble	r8, {r4, r7, r8, sl, lr}
d0010b80:	46087811 			; <UNDEFINED> instruction: 0x46087811
d0010b84:	fc63f7ff 	stc2l	7, cr15, [r3], #-1020	; 0xfffffc04
d0010b88:	d1f42800 	mvnsle	r2, r0, lsl #16
d0010b8c:	29093930 	stmdbcs	r9, {r4, r5, r8, fp, ip, sp}
d0010b90:	1b52d9f1 	blne	0xd14c735c
d0010b94:	d1362a07 	teqle	r6, r7, lsl #20
d0010b98:	4628492a 	strtmi	r4, [r8], -sl, lsr #18
d0010b9c:	44799201 	ldrbtmi	r9, [r9], #-513	; 0xfffffdff
d0010ba0:	fd54f010 	ldc2l	0, cr15, [r4, #-64]	; 0xffffffc0
d0010ba4:	bb709a01 	bllt	0xd1c373b0
d0010ba8:	46204927 	strtmi	r4, [r0], -r7, lsr #18
d0010bac:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d0010bb0:	4680fc11 	pkhbtmi	pc, r0, r1, lsl #24	; <UNPREDICTABLE>
d0010bb4:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010bb8:	6a61fbc3 	bvs	0xd188facc
d0010bbc:	42b16aa6 	adcsmi	r6, r1, #679936	; 0xa6000
d0010bc0:	7808d003 	stmdavc	r8, {r0, r1, ip, lr, pc}
d0010bc4:	fc43f7ff 	mcrr2	7, 15, pc, r3, cr15	; <UNPREDICTABLE>
d0010bc8:	2301b908 	movwcs	fp, #6408	; 0x1908
d0010bcc:	6a626323 	bvs	0xd18a9860
d0010bd0:	d9074296 	stmdble	r7, {r1, r2, r4, r7, r9, lr}
d0010bd4:	46287815 			; <UNDEFINED> instruction: 0x46287815
d0010bd8:	fc39f7ff 	ldc2	7, cr15, [r9], #-1020	; 0xfffffc04
d0010bdc:	3d30b980 			; <UNDEFINED> instruction: 0x3d30b980
d0010be0:	d90d2d09 	stmdble	sp, {r0, r3, r8, sl, fp, sp}
d0010be4:	68201a52 	stmdavs	r0!, {r1, r4, r6, r9, fp, ip}
d0010be8:	fc0ff7ff 	stc2	7, cr15, [pc], {255}	; 0xff
d0010bec:	17c12700 	strbne	r2, [r1, r0, lsl #14]
d0010bf0:	0ff643ce 	svceq	0x00f643ce
d0010bf4:	0f00f1b8 	svceq	0x0000f1b8
d0010bf8:	4914d093 	ldmdbmi	r4, {r0, r1, r4, r7, ip, lr, pc}
d0010bfc:	e7574479 			; <UNDEFINED> instruction: 0xe7574479
d0010c00:	62623201 	rsbvs	r3, r2, #268435456	; 0x10000000
d0010c04:	4629e7e3 	strtmi	lr, [r9], -r3, ror #15
d0010c08:	f7ff6820 			; <UNDEFINED> instruction: 0xf7ff6820
d0010c0c:	2800fbfe 	stmdacs	r0, {r1, r2, r3, r4, r5, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d0010c10:	6823dbae 	stmdavs	r3!, {r1, r2, r3, r5, r7, r8, r9, fp, ip, lr, pc}
d0010c14:	fb022248 	blx	0xd009953e
d0010c18:	f5003000 			; <UNDEFINED> instruction: 0xf5003000
d0010c1c:	e9d0402b 	ldmib	r0, {r0, r1, r3, r5, lr}^
d0010c20:	e77e6732 			; <UNDEFINED> instruction: 0xe77e6732
d0010c24:	f47f2d00 			; <UNDEFINED> instruction: 0xf47f2d00
d0010c28:	e76faf7c 			; <UNDEFINED> instruction: 0xe76faf7c
d0010c2c:	ffffffc0 			; <UNDEFINED> instruction: 0xffffffc0
d0010c30:	ffffffa2 			; <UNDEFINED> instruction: 0xffffffa2
d0010c34:	ffffff86 			; <UNDEFINED> instruction: 0xffffff86
d0010c38:	ffffff70 			; <UNDEFINED> instruction: 0xffffff70
d0010c3c:	ffffff40 			; <UNDEFINED> instruction: 0xffffff40
d0010c40:	ffffff2e 			; <UNDEFINED> instruction: 0xffffff2e
d0010c44:	fffffe40 			; <UNDEFINED> instruction: 0xfffffe40
d0010c48:	fffffe2e 			; <UNDEFINED> instruction: 0xfffffe2e
d0010c4c:	fffffde0 			; <UNDEFINED> instruction: 0xfffffde0

Disassembly of section .text.pp_mul:

d0010c58 <.text.pp_mul>:
d0010c58:	4ff0e92d 	svcmi	0x00f0e92d
d0010c5c:	8b02ed2d 	blhi	0xd00cc118
d0010c60:	4606b089 	strmi	fp, [r6], -r9, lsl #1
d0010c64:	fec2f7ff 	mcr2	7, 6, pc, cr2, cr15, {7}	; <UNPREDICTABLE>
d0010c68:	46044b67 	strmi	r4, [r4], -r7, ror #22
d0010c6c:	447b460d 	ldrbtmi	r4, [fp], #-1549	; 0xfffff9f3
d0010c70:	3a10ee08 	bcc	0xd044c498
d0010c74:	447b4b65 	ldrbtmi	r4, [fp], #-2917	; 0xfffff49b
d0010c78:	3a90ee08 	bcc	0xce44c4a0
d0010c7c:	1a10ee18 	bne	0xd044c4e4
d0010c80:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0010c84:	b178fba7 	cmnlt	r8, r7, lsr #23	; <UNPREDICTABLE>
d0010c88:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0010c8c:	4361feaf 	msrmi	SPSR_c, #2800	; 0xaf0
d0010c90:	3400fba4 	strcc	pc, [r0], #-2980	; 0xfffff45c
d0010c94:	1105fb00 	tstne	r5, r0, lsl #22	; <UNPREDICTABLE>
d0010c98:	3400e9cd 	strcc	lr, [r0], #-2509	; 0xfffff633
d0010c9c:	440b9b01 	strmi	r9, [fp], #-2817	; 0xfffff4ff
d0010ca0:	e9dd9301 	ldmib	sp, {r0, r8, r9, ip, pc}^
d0010ca4:	e7e94500 	strb	r4, [r9, r0, lsl #10]!
d0010ca8:	1a90ee18 	bne	0xce44c510
d0010cac:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0010cb0:	9006fb91 	mulls	r6, r1, fp
d0010cb4:	4956b938 	ldmdbmi	r6, {r3, r4, r5, r8, fp, ip, sp, pc}^
d0010cb8:	44794630 	ldrbtmi	r4, [r9], #-1584	; 0xfffff9d0
d0010cbc:	fb8af7ff 	blx	0xce2cecc2
d0010cc0:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d0010cc4:	46308099 			; <UNDEFINED> instruction: 0x46308099
d0010cc8:	fe90f7ff 	mrc2	7, 4, pc, cr0, cr15, {7}
d0010ccc:	0100e9cd 	smlabteq	r0, sp, r9, lr
d0010cd0:	2300e9dd 	movwcs	lr, #2525	; 0x9dd
d0010cd4:	d1094313 	tstle	r9, r3, lsl r3
d0010cd8:	29006b71 	stmdbcs	r0, {r0, r4, r5, r6, r8, r9, fp, sp, lr}
d0010cdc:	2301d0e1 	movwcs	sp, #4321	; 0x10e1
d0010ce0:	63332400 	teqvs	r3, #0, 8
d0010ce4:	e9cd2300 	stmib	sp, {r8, r9, sp}^
d0010ce8:	e7da3400 	ldrb	r3, [sl, r0, lsl #8]
d0010cec:	f1752c00 			; <UNDEFINED> instruction: 0xf1752c00
d0010cf0:	e9cd0300 	stmib	sp, {r8, r9}^
d0010cf4:	da044502 	ble	0xd0122104
d0010cf8:	eb654262 	bl	0xd1961688
d0010cfc:	e9cd0345 	stmib	sp, {r0, r2, r6, r8, r9}^
d0010d00:	e9dd2302 	ldmib	sp, {r1, r8, r9, sp}^
d0010d04:	2a002300 	bcs	0xd001990c
d0010d08:	2304e9cd 	movwcs	lr, #18893	; 0x49cd
d0010d0c:	0300f173 	movweq	pc, #371	; 0x173	; <UNPREDICTABLE>
d0010d10:	e9ddda06 	ldmib	sp, {r1, r2, r9, fp, ip, lr, pc}^
d0010d14:	42522300 	subsmi	r2, r2, #0, 6
d0010d18:	0343eb63 	movteq	lr, #15203	; 0x3b63
d0010d1c:	2304e9cd 	movwcs	lr, #18893	; 0x49cd
d0010d20:	0a00f04f 	beq	0xd004ce64
d0010d24:	0b00f04f 	bleq	0xd004ce68
d0010d28:	f04f213f 			; <UNDEFINED> instruction: 0xf04f213f
d0010d2c:	46570c01 	ldrbmi	r0, [r7], -r1, lsl #24
d0010d30:	eb1a46d8 	bl	0xd06a2898
d0010d34:	f1c1030a 			; <UNDEFINED> instruction: 0xf1c1030a
d0010d38:	f1a10920 			; <UNDEFINED> instruction: 0xf1a10920
d0010d3c:	461a0e20 	ldrmi	r0, [sl], -r0, lsr #28
d0010d40:	030beb4b 	movweq	lr, #47947	; 0xbb4b
d0010d44:	9b029307 	blls	0xd00b5968
d0010d48:	b01cf8dd 			; <UNDEFINED> instruction: 0xb01cf8dd
d0010d4c:	f001fa23 			; <UNDEFINED> instruction: 0xf001fa23
d0010d50:	fa039b03 	blx	0xd00f7964
d0010d54:	fa23f909 	blx	0xd090f180
d0010d58:	ea40fe0e 	b	0xd1050598
d0010d5c:	ea400009 	b	0xd1010d88
d0010d60:	f1a1000e 			; <UNDEFINED> instruction: 0xf1a1000e
d0010d64:	f0000e20 			; <UNDEFINED> instruction: 0xf0000e20
d0010d68:	ea400001 	b	0xd1010d74
d0010d6c:	f1c10a02 			; <UNDEFINED> instruction: 0xf1c10a02
d0010d70:	e9dd0020 	ldmib	sp, {r5}^
d0010d74:	459b2304 	ldrmi	r2, [fp, #772]	; 0x304
d0010d78:	4592bf08 	ldrmi	fp, [r2, #3848]	; 0xf08
d0010d7c:	fa0cd313 	blx	0xd03459d0
d0010d80:	fa2cfe0e 	blx	0xd0b505c0
d0010d84:	9b04f000 	blls	0xd014cd8c
d0010d88:	0000ea4e 	andeq	lr, r0, lr, asr #20
d0010d8c:	fe01fa0c 	vseleq.f32	s30, s2, s24
d0010d90:	0a03ebba 	beq	0xd010bc80
d0010d94:	ea4e9b05 	b	0xd13b79b0
d0010d98:	ea400e07 	b	0xd10145bc
d0010d9c:	eb6b0008 	bl	0xd1ad0dc4
d0010da0:	46770b03 	ldrbtmi	r0, [r7], -r3, lsl #22
d0010da4:	39014680 	stmdbcc	r1, {r7, r9, sl, lr}
d0010da8:	9b06d2c3 	blls	0xd01c58bc
d0010dac:	9b01b1c3 	blls	0xd007d4c0
d0010db0:	0fdb0fea 	svceq	0x00db0fea
d0010db4:	7fd5ebb3 	svcvc	0x00d5ebb3
d0010db8:	f04fbf15 			; <UNDEFINED> instruction: 0xf04fbf15
d0010dbc:	f06f4100 			; <UNDEFINED> instruction: 0xf06f4100
d0010dc0:	20004100 	andcs	r4, r0, r0, lsl #2
d0010dc4:	30fff04f 	rscscc	pc, pc, pc, asr #32
d0010dc8:	bf084541 	svclt	0x00084541
d0010dcc:	d38642b8 	orrle	r4, r6, #184, 4	; 0x8000000b
d0010dd0:	d002429a 	mulle	r2, sl, r2
d0010dd4:	eb68427f 	bl	0xd1a217d8
d0010dd8:	e9cd0848 	stmib	sp, {r3, r6, fp}^
d0010ddc:	e7607800 	strb	r7, [r0, -r0, lsl #16]!
d0010de0:	f1752c00 			; <UNDEFINED> instruction: 0xf1752c00
d0010de4:	e9cd0300 	stmib	sp, {r8, r9}^
d0010de8:	f6bfab00 			; <UNDEFINED> instruction: 0xf6bfab00
d0010dec:	f1daaf5a 			; <UNDEFINED> instruction: 0xf1daaf5a
d0010df0:	eb6b0300 	bl	0xd1ad19f8
d0010df4:	e776044b 	ldrb	r0, [r6, -fp, asr #8]!
d0010df8:	46294620 	strtmi	r4, [r9], -r0, lsr #12
d0010dfc:	ecbdb009 	ldc	0, cr11, [sp], #36	; 0x24
d0010e00:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d0010e04:	bf008ff0 	svclt	0x00008ff0
d0010e08:	ffffffde 			; <UNDEFINED> instruction: 0xffffffde
d0010e0c:	ffffffd8 			; <UNDEFINED> instruction: 0xffffffd8
d0010e10:	ffffff96 			; <UNDEFINED> instruction: 0xffffff96

Disassembly of section .text.pp_add:

d0010e14 <.text.pp_add>:
d0010e14:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d0010e18:	46064f12 			; <UNDEFINED> instruction: 0x46064f12
d0010e1c:	8048f8df 	ldrdhi	pc, [r8], #-143	; 0xffffff71
d0010e20:	ff1af7ff 			; <UNDEFINED> instruction: 0xff1af7ff
d0010e24:	4604447f 			; <UNDEFINED> instruction: 0x4604447f
d0010e28:	44f8460d 	ldrbtmi	r4, [r8], #1549	; 0x60d
d0010e2c:	46304639 			; <UNDEFINED> instruction: 0x46304639
d0010e30:	fad0f7ff 	blx	0xcf44ee34
d0010e34:	4630b130 			; <UNDEFINED> instruction: 0x4630b130
d0010e38:	ff0ef7ff 			; <UNDEFINED> instruction: 0xff0ef7ff
d0010e3c:	eb411824 	bl	0xd1056ed4
d0010e40:	e7f30505 	ldrb	r0, [r3, r5, lsl #10]!
d0010e44:	46304641 	ldrtmi	r4, [r0], -r1, asr #12
d0010e48:	fac4f7ff 	blx	0xcf14ee4c
d0010e4c:	4630b130 			; <UNDEFINED> instruction: 0x4630b130
d0010e50:	ff02f7ff 			; <UNDEFINED> instruction: 0xff02f7ff
d0010e54:	eb651a24 	bl	0xd19576ec
d0010e58:	e7e70501 	strb	r0, [r7, r1, lsl #10]!
d0010e5c:	46294620 	strtmi	r4, [r9], -r0, lsr #12
d0010e60:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d0010e64:	fffffbb2 			; <UNDEFINED> instruction: 0xfffffbb2
d0010e68:	fffffbae 			; <UNDEFINED> instruction: 0xfffffbae

Disassembly of section .text.pp_shift:

d0010e74 <.text.pp_shift>:
d0010e74:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d0010e78:	805cf8df 	ldrsbhi	pc, [ip], #-143	; 0xffffff71	; <UNPREDICTABLE>
d0010e7c:	f8df4604 			; <UNDEFINED> instruction: 0xf8df4604
d0010e80:	f7ff905c 			; <UNDEFINED> instruction: 0xf7ff905c
d0010e84:	44f8ffc7 	ldrbtmi	pc, [r8], #4039	; 0xfc7	; <UNPREDICTABLE>
d0010e88:	460e4605 	strmi	r4, [lr], -r5, lsl #12
d0010e8c:	464144f9 			; <UNDEFINED> instruction: 0x464144f9
d0010e90:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010e94:	b160fa9f 	msrlt	(UNDEF: 96), pc
d0010e98:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010e9c:	2900ffbb 	stmdbcs	r0, {r0, r1, r3, r4, r5, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0010ea0:	2820bf08 	stmdacs	r0!, {r3, r8, r9, sl, fp, ip, sp, pc}
d0010ea4:	2301d302 	movwcs	sp, #4866	; 0x1302
d0010ea8:	e7f06323 	ldrb	r6, [r0, r3, lsr #6]!
d0010eac:	26004085 	strcs	r4, [r0], -r5, lsl #1
d0010eb0:	4649e7ed 	strbmi	lr, [r9], -sp, ror #15
d0010eb4:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010eb8:	b140fa8d 	smlalbblt	pc, r0, sp, sl	; <UNPREDICTABLE>
d0010ebc:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010ec0:	2900ffa9 	stmdbcs	r0, {r0, r3, r5, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0010ec4:	2820bf08 	stmdacs	r0!, {r3, r8, r9, sl, fp, ip, sp, pc}
d0010ec8:	40c5d2ed 	sbcmi	sp, r5, sp, ror #5
d0010ecc:	4628e7ef 	strtmi	lr, [r8], -pc, ror #15
d0010ed0:	e8bd4631 	pop	{r0, r4, r5, r9, sl, lr}
d0010ed4:	bf0083f8 	svclt	0x000083f8
d0010ed8:	ffffffe2 			; <UNDEFINED> instruction: 0xffffffe2
d0010edc:	ffffffdf 			; <UNDEFINED> instruction: 0xffffffdf

Disassembly of section .text.pp_rel:

d0010eec <.text.pp_rel>:
d0010eec:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d0010ef0:	46064f24 	strmi	r4, [r6], -r4, lsr #30
d0010ef4:	8090f8df 			; <UNDEFINED> instruction: 0x8090f8df
d0010ef8:	ffbcf7ff 			; <UNDEFINED> instruction: 0xffbcf7ff
d0010efc:	908cf8df 	ldrdls	pc, [ip], pc	; <UNPREDICTABLE>
d0010f00:	460d4604 	strmi	r4, [sp], -r4, lsl #12
d0010f04:	44f8447f 	ldrbtmi	r4, [r8], #1151	; 0x47f
d0010f08:	463944f9 			; <UNDEFINED> instruction: 0x463944f9
d0010f0c:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0010f10:	b158fa61 	cmplt	r8, r1, ror #20	; <UNPREDICTABLE>
d0010f14:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0010f18:	42a0ffad 	adcmi	pc, r0, #692	; 0x2b4
d0010f1c:	0305eb71 	movweq	lr, #23409	; 0x5b71
d0010f20:	2401bfac 	strcs	fp, [r1], #-4012	; 0xfffff054
d0010f24:	b2e42400 	rsclt	r2, r4, #0, 8
d0010f28:	e7ee2500 	strb	r2, [lr, r0, lsl #10]!
d0010f2c:	46304641 	ldrtmi	r4, [r0], -r1, asr #12
d0010f30:	fa50f7ff 	blx	0xd144ef34
d0010f34:	4630b130 			; <UNDEFINED> instruction: 0x4630b130
d0010f38:	ff9cf7ff 			; <UNDEFINED> instruction: 0xff9cf7ff
d0010f3c:	eb754284 	bl	0xd1d61954
d0010f40:	e7ed0301 	strb	r0, [sp, r1, lsl #6]!
d0010f44:	46304649 	ldrtmi	r4, [r0], -r9, asr #12
d0010f48:	fa44f7ff 	blx	0xd114ef4c
d0010f4c:	4630b148 	ldrtmi	fp, [r0], -r8, asr #2
d0010f50:	ff90f7ff 			; <UNDEFINED> instruction: 0xff90f7ff
d0010f54:	eb754284 	bl	0xd1d6196c
d0010f58:	bfb40301 	svclt	0x00b40301
d0010f5c:	24002401 	strcs	r2, [r0], #-1025	; 0xfffffbff
d0010f60:	490be7e1 	stmdbmi	fp, {r0, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d0010f64:	44794630 	ldrbtmi	r4, [r9], #-1584	; 0xfffff9d0
d0010f68:	fa34f7ff 	blx	0xd0d4ef6c
d0010f6c:	4630b130 			; <UNDEFINED> instruction: 0x4630b130
d0010f70:	ff80f7ff 			; <UNDEFINED> instruction: 0xff80f7ff
d0010f74:	eb7142a0 	bl	0xd1c619fc
d0010f78:	e7ee0305 	strb	r0, [lr, r5, lsl #6]!
d0010f7c:	46294620 	strtmi	r4, [r9], -r0, lsr #12
d0010f80:	83f8e8bd 	mvnshi	lr, #12386304	; 0xbd0000
d0010f84:	ffffffd8 			; <UNDEFINED> instruction: 0xffffffd8
d0010f88:	ffffffd9 			; <UNDEFINED> instruction: 0xffffffd9
d0010f8c:	ffffffda 			; <UNDEFINED> instruction: 0xffffffda
d0010f90:	ffffff7e 			; <UNDEFINED> instruction: 0xffffff7e

Disassembly of section .text.pp_eq:

d0010f9c <.text.pp_eq>:
d0010f9c:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d0010fa0:	46064f15 			; <UNDEFINED> instruction: 0x46064f15
d0010fa4:	8054f8df 	ldrsbhi	pc, [r4], #-143	; 0xffffff71	; <UNPREDICTABLE>
d0010fa8:	ffa0f7ff 			; <UNDEFINED> instruction: 0xffa0f7ff
d0010fac:	4604447f 			; <UNDEFINED> instruction: 0x4604447f
d0010fb0:	44f8460d 	ldrbtmi	r4, [r8], #1549	; 0x60d
d0010fb4:	46304639 			; <UNDEFINED> instruction: 0x46304639
d0010fb8:	fa0cf7ff 	blx	0xd034efbc
d0010fbc:	4630b150 			; <UNDEFINED> instruction: 0x4630b150
d0010fc0:	ff94f7ff 			; <UNDEFINED> instruction: 0xff94f7ff
d0010fc4:	bf0642a9 	svclt	0x000642a9
d0010fc8:	240142a0 	strcs	r4, [r1], #-672	; 0xfffffd60
d0010fcc:	b2e42400 	rsclt	r2, r4, #0, 8
d0010fd0:	e7ef2500 	strb	r2, [pc, r0, lsl #10]!
d0010fd4:	46304641 	ldrtmi	r4, [r0], -r1, asr #12
d0010fd8:	f9fcf7ff 			; <UNDEFINED> instruction: 0xf9fcf7ff
d0010fdc:	4630b140 	ldrtmi	fp, [r0], -r0, asr #2
d0010fe0:	ff84f7ff 			; <UNDEFINED> instruction: 0xff84f7ff
d0010fe4:	bf0a42a9 	svclt	0x000a42a9
d0010fe8:	240142a0 	strcs	r4, [r1], #-672	; 0xfffffd60
d0010fec:	e7ee2400 	strb	r2, [lr, r0, lsl #8]!
d0010ff0:	46294620 	strtmi	r4, [r9], -r0, lsr #12
d0010ff4:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d0010ff8:	ffffffe4 			; <UNDEFINED> instruction: 0xffffffe4
d0010ffc:	ffffffe1 			; <UNDEFINED> instruction: 0xffffffe1

Disassembly of section .text.pp_band:

d0011000 <.text.pp_band>:
d0011000:	4604b570 			; <UNDEFINED> instruction: 0x4604b570
d0011004:	ffcaf7ff 			; <UNDEFINED> instruction: 0xffcaf7ff
d0011008:	460d4606 	strmi	r4, [sp], -r6, lsl #12
d001100c:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0011010:	6a63f997 	bvs	0xd190f674
d0011014:	428b6aa1 	addmi	r6, fp, #659456	; 0xa1000
d0011018:	781ad20f 	ldmdavc	sl, {r0, r1, r2, r3, r9, ip, lr, pc}
d001101c:	d10c2a26 	tstle	ip, r6, lsr #20
d0011020:	42911c5a 	addsmi	r1, r1, #23040	; 0x5a00
d0011024:	785bd902 	ldmdavc	fp, {r1, r8, fp, ip, lr, pc}^
d0011028:	d0062b26 	andle	r2, r6, r6, lsr #22
d001102c:	62624620 	rsbvs	r4, r2, #32, 12	; 0x2000000
d0011030:	ffb4f7ff 			; <UNDEFINED> instruction: 0xffb4f7ff
d0011034:	400d4006 	andmi	r4, sp, r6
d0011038:	4630e7e8 	ldrtmi	lr, [r0], -r8, ror #15
d001103c:	bd704629 	ldcllt	6, cr4, [r0, #-164]!	; 0xffffff5c

Disassembly of section .text.pp_xor:

d0011044 <.text.pp_xor>:
d0011044:	4f0ab5f8 	svcmi	0x000ab5f8
d0011048:	f7ff4606 			; <UNDEFINED> instruction: 0xf7ff4606
d001104c:	4605ffd9 			; <UNDEFINED> instruction: 0x4605ffd9
d0011050:	447f460c 	ldrbtmi	r4, [pc], #-1548	; 0xd0011058
d0011054:	46304639 			; <UNDEFINED> instruction: 0x46304639
d0011058:	f9bcf7ff 			; <UNDEFINED> instruction: 0xf9bcf7ff
d001105c:	4628b910 			; <UNDEFINED> instruction: 0x4628b910
d0011060:	bdf84621 	ldcllt	6, cr4, [r8, #132]!	; 0x84
d0011064:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0011068:	4045ffcb 	submi	pc, r5, fp, asr #31
d001106c:	e7f1404c 	ldrb	r4, [r1, ip, asr #32]!
d0011070:	ffffffea 			; <UNDEFINED> instruction: 0xffffffea

Disassembly of section .text.pp_bor:

d0011074 <.text.pp_bor>:
d0011074:	4604b570 			; <UNDEFINED> instruction: 0x4604b570
d0011078:	ffe4f7ff 			; <UNDEFINED> instruction: 0xffe4f7ff
d001107c:	460d4606 	strmi	r4, [sp], -r6, lsl #12
d0011080:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0011084:	6a63f95d 	bvs	0xd190f600
d0011088:	428b6aa1 	addmi	r6, fp, #659456	; 0xa1000
d001108c:	781ad20f 	ldmdavc	sl, {r0, r1, r2, r3, r9, ip, lr, pc}
d0011090:	d10c2a7c 	tstle	ip, ip, ror sl
d0011094:	42911c5a 	addsmi	r1, r1, #23040	; 0x5a00
d0011098:	785bd902 	ldmdavc	fp, {r1, r8, fp, ip, lr, pc}^
d001109c:	d0062b7c 	andle	r2, r6, ip, ror fp
d00110a0:	62624620 	rsbvs	r4, r2, #32, 12	; 0x2000000
d00110a4:	ffcef7ff 			; <UNDEFINED> instruction: 0xffcef7ff
d00110a8:	430d4306 	movwmi	r4, #54022	; 0xd306
d00110ac:	4630e7e8 	ldrtmi	lr, [r0], -r8, ror #15
d00110b0:	bd704629 	ldcllt	6, cr4, [r0, #-164]!	; 0xffffff5c

Disassembly of section .text.pp_and:

d00110b8 <.text.pp_and>:
d00110b8:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d00110bc:	46064f16 			; <UNDEFINED> instruction: 0x46064f16
d00110c0:	ffd8f7ff 			; <UNDEFINED> instruction: 0xffd8f7ff
d00110c4:	460d4604 	strmi	r4, [sp], -r4, lsl #12
d00110c8:	4639447f 			; <UNDEFINED> instruction: 0x4639447f
d00110cc:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d00110d0:	b918f981 	ldmdblt	r8, {r0, r7, r8, fp, ip, sp, lr, pc}
d00110d4:	46294620 	strtmi	r4, [r9], -r0, lsr #12
d00110d8:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d00110dc:	8034f8d6 	ldrsbthi	pc, [r4], -r6	; <UNPREDICTABLE>
d00110e0:	0f00f1b8 	svceq	0x0000f1b8
d00110e4:	ea54d014 	b	0xd154513c
d00110e8:	bf140305 	svclt	0x00140305
d00110ec:	23002301 	movwcs	r2, #769	; 0x301
d00110f0:	46306373 			; <UNDEFINED> instruction: 0x46306373
d00110f4:	ffbef7ff 			; <UNDEFINED> instruction: 0xffbef7ff
d00110f8:	0305ea54 	movweq	lr, #23124	; 0x5a54
d00110fc:	8034f8c6 	eorshi	pc, r4, r6, asr #17
d0011100:	ea50d008 	b	0xd1445128
d0011104:	bf140301 	svclt	0x00140301
d0011108:	24002401 	strcs	r2, [r0], #-1025	; 0xfffffbff
d001110c:	e7dc17e5 	ldrb	r1, [ip, r5, ror #15]
d0011110:	e7ed4643 	strb	r4, [sp, r3, asr #12]!
d0011114:	e7f92400 	ldrb	r2, [r9, r0, lsl #8]!
d0011118:	ffffffe8 			; <UNDEFINED> instruction: 0xffffffe8

Disassembly of section .text.pp_or:

d0011120 <.text.pp_or>:
d0011120:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d0011124:	46064f15 			; <UNDEFINED> instruction: 0x46064f15
d0011128:	ffc6f7ff 			; <UNDEFINED> instruction: 0xffc6f7ff
d001112c:	460d4604 	strmi	r4, [sp], -r4, lsl #12
d0011130:	4639447f 			; <UNDEFINED> instruction: 0x4639447f
d0011134:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0011138:	b918f94d 	ldmdblt	r8, {r0, r2, r3, r6, r8, fp, ip, sp, lr, pc}
d001113c:	46294620 	strtmi	r4, [r9], -r0, lsr #12
d0011140:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d0011144:	8034f8d6 	ldrsbthi	pc, [r4], -r6	; <UNPREDICTABLE>
d0011148:	0f00f1b8 	svceq	0x0000f1b8
d001114c:	ea54d014 	b	0xd15451a4
d0011150:	bf0c0305 	svclt	0x000c0305
d0011154:	23002301 	movwcs	r2, #769	; 0x301
d0011158:	46306373 			; <UNDEFINED> instruction: 0x46306373
d001115c:	ffacf7ff 			; <UNDEFINED> instruction: 0xffacf7ff
d0011160:	43294320 			; <UNDEFINED> instruction: 0x43294320
d0011164:	8034f8c6 	eorshi	pc, r4, r6, asr #17
d0011168:	ea502500 	b	0xd141a570
d001116c:	bf140301 	svclt	0x00140301
d0011170:	24002401 	strcs	r2, [r0], #-1025	; 0xfffffbff
d0011174:	e7dcb2e4 	ldrb	fp, [ip, r4, ror #5]
d0011178:	e7ed4643 	strb	r4, [sp, r3, asr #12]!
d001117c:	ffffffe8 			; <UNDEFINED> instruction: 0xffffffe8

Disassembly of section .text.pp_value:

d00111b0 <.text.pp_value>:
d00111b0:	b5f0b084 	ldrblt	fp, [r0, #132]!	; 0x84
d00111b4:	4606b08f 	strmi	fp, [r6], -pc, lsl #1
d00111b8:	9000ac15 	andls	sl, r0, r5, lsl ip
d00111bc:	9f1ead01 	svcls	0x001ead01
d00111c0:	000ee884 	andeq	lr, lr, r4, lsl #17
d00111c4:	c50fcc0f 	strgt	ip, [pc, #-3087]	; 0xd00105bd
d00111c8:	000fe894 	muleq	pc, r4, r8	; <UNPREDICTABLE>
d00111cc:	000fe885 	andeq	lr, pc, r5, lsl #17
d00111d0:	466d9b1d 			; <UNDEFINED> instruction: 0x466d9b1d
d00111d4:	970a2401 	strls	r2, [sl, -r1, lsl #8]
d00111d8:	23009309 	movwcs	r9, #777	; 0x309
d00111dc:	940d4628 	strls	r4, [sp], #-1576	; 0xfffff9d8
d00111e0:	930c930b 	movwls	r9, #49931	; 0xc30b
d00111e4:	ff9cf7ff 			; <UNDEFINED> instruction: 0xff9cf7ff
d00111e8:	e9c39b1f 	stmib	r3, {r0, r1, r2, r3, r4, r8, r9, fp, ip, pc}^
d00111ec:	46280100 	strtmi	r0, [r8], -r0, lsl #2
d00111f0:	f8a6f7ff 			; <UNDEFINED> instruction: 0xf8a6f7ff
d00111f4:	b9139b0c 	ldmdblt	r3, {r2, r3, r8, r9, fp, ip, pc}
d00111f8:	42bb9b09 	adcsmi	r9, fp, #9216	; 0x2400
d00111fc:	6db0d012 	ldcvs	0, cr13, [r0, #72]!	; 0x48
d0011200:	490ab990 	stmdbmi	sl, {r4, r7, r8, fp, ip, sp, pc}
d0011204:	206cf89d 	mlscs	ip, sp, r8, pc	; <UNPREDICTABLE>
d0011208:	65b14479 	ldrvs	r4, [r1, #1145]!	; 0x479
d001120c:	65f19918 	ldrbvs	r9, [r1, #2328]!	; 0x918
d0011210:	e9c69919 	stmib	r6, {r0, r3, r4, r8, fp, ip, pc}^
d0011214:	9a1c1218 	bls	0xd0715a7c
d0011218:	b00f66b2 			; <UNDEFINED> instruction: 0xb00f66b2
d001121c:	40f0e8bd 	ldrhtmi	lr, [r0], #141	; 0x8d
d0011220:	4770b004 	ldrbmi	fp, [r0, -r4]!
d0011224:	e7f84620 	ldrb	r4, [r8, r0, lsr #12]!
d0011228:	e7f62000 	ldrb	r2, [r6, r0]!
d001122c:	ffffff74 			; <UNDEFINED> instruction: 0xffffff74

Disassembly of section .text.enter_header.isra.0:

d00113d0 <.text.enter_header.isra.0>:
d00113d0:	4ff0e92d 	svcmi	0x00f0e92d
d00113d4:	f5ad461e 			; <UNDEFINED> instruction: 0xf5ad461e
d00113d8:	6ec37d0d 	cdpvs	13, 12, cr7, cr3, cr13, {0}
d00113dc:	9d984604 	ldcls	6, cr4, [r8, #16]
d00113e0:	92059104 	andls	r9, r5, #4, 2
d00113e4:	6d85b993 	vstrvs.16	s22, [r5, #294]	; 0x126	; <UNPREDICTABLE>
d00113e8:	2500b12d 	strcs	fp, [r0, #-301]	; 0xfffffed3
d00113ec:	f50d4628 			; <UNDEFINED> instruction: 0xf50d4628
d00113f0:	e8bd7d0d 	pop	{r0, r2, r3, r8, sl, fp, ip, sp, lr}
d00113f4:	4bfa8ff0 	blmi	0xcfeb53bc
d00113f8:	65a3447b 	strvs	r4, [r3, #1147]!	; 0x47b
d00113fc:	65e39b04 	strbvs	r9, [r3, #2820]!	; 0xb04
d0011400:	e9c49b05 	stmib	r4, {r0, r2, r8, r9, fp, ip, pc}^
d0011404:	9b963618 	blls	0xce59ec6c
d0011408:	e7ef66a3 	strb	r6, [pc, r3, lsr #13]!
d001140c:	2bfe1e6b 	blcs	0xcff98dc0
d0011410:	6d85d905 	vstrvs.16	s26, [r5, #10]	; <UNPREDICTABLE>
d0011414:	d1e82d00 	mvnle	r2, r0, lsl #26
d0011418:	447b4bf2 	ldrbtmi	r4, [fp], #-3058	; 0xfffff40e
d001141c:	f10de7ed 			; <UNDEFINED> instruction: 0xf10de7ed
d0011420:	462a0930 			; <UNDEFINED> instruction: 0x462a0930
d0011424:	46489997 			; <UNDEFINED> instruction: 0x46489997
d0011428:	f900f010 			; <UNDEFINED> instruction: 0xf900f010
d001142c:	46482300 	strbmi	r2, [r8], -r0, lsl #6
d0011430:	3005f809 	andcc	pc, r5, r9, lsl #16
d0011434:	fd02f011 	stc2	0, cr15, [r2, #-68]	; 0xffffffbc
d0011438:	d8052802 	stmdale	r5, {r1, fp, sp}
d001143c:	2d006da5 	stccs	13, cr6, [r0, #-660]	; 0xfffffd6c
d0011440:	4be9d1d3 	blmi	0xcfa85b94
d0011444:	e7d8447b 			; <UNDEFINED> instruction: 0xe7d8447b
d0011448:	49e83802 	stmibmi	r8!, {r1, fp, ip, sp}^
d001144c:	44794448 	ldrbtmi	r4, [r9], #-1096	; 0xfffffbb8
d0011450:	fd00f011 	stc2	0, cr15, [r0, #-68]	; 0xffffffbc
d0011454:	28004605 	stmdacs	r0, {r0, r2, r9, sl, lr}
d0011458:	ab0bd1f0 	blge	0xd0305c20
d001145c:	7280f44f 	addvc	pc, r0, #1325400064	; 0x4f000000
d0011460:	7b98f50d 	blvc	0xce64e89c
d0011464:	9202900b 	andls	r9, r2, #11
d0011468:	46024649 	strmi	r4, [r2], -r9, asr #12
d001146c:	e9cd6ee7 	stmib	sp, {r0, r1, r2, r5, r6, r7, r9, sl, fp, sp, lr}^
d0011470:	46033b00 	strmi	r3, [r3], -r0, lsl #22
d0011474:	47b86f60 	ldrmi	r6, [r8, r0, ror #30]!
d0011478:	f504b1e8 			; <UNDEFINED> instruction: 0xf504b1e8
d001147c:	46a87700 	strtmi	r7, [r8], r0, lsl #14
d0011480:	5a2ef504 	bpl	0xd0bce898
d0011484:	3000f8da 	ldrdcc	pc, [r0], -sl
d0011488:	d2064598 	andle	r4, r6, #152, 10	; 0x26000000
d001148c:	46594638 			; <UNDEFINED> instruction: 0x46594638
d0011490:	77a6f507 	strvc	pc, [r6, r7, lsl #10]!
d0011494:	fcdef011 	ldc2l	0, cr15, [lr], {17}
d0011498:	f8dab998 			; <UNDEFINED> instruction: 0xf8dab998
d001149c:	45983000 	ldrmi	r3, [r8]
d00114a0:	8103f040 	tsthi	r3, r0, asr #32	; <UNPREDICTABLE>
d00114a4:	0f20f1b8 	svceq	0x0020f1b8
d00114a8:	6da3d10e 	stfvsd	f5, [r3, #56]!	; 0x38
d00114ac:	d19c2b00 	orrsle	r2, ip, r0, lsl #22
d00114b0:	447b4bcf 	ldrbtmi	r4, [fp], #-3023	; 0xfffff431
d00114b4:	6da3e7a1 	stcvs	7, cr14, [r3, #644]!	; 0x284
d00114b8:	d1962b00 	orrsle	r2, r6, r0, lsl #22
d00114bc:	447b4bcd 	ldrbtmi	r4, [fp], #-3021	; 0xfffff433
d00114c0:	f108e79b 			; <UNDEFINED> instruction: 0xf108e79b
d00114c4:	e7dd0801 	ldrb	r0, [sp, r1, lsl #16]
d00114c8:	3384f642 	orrcc	pc, r4, #69206016	; 0x4200000
d00114cc:	f5d258e2 			; <UNDEFINED> instruction: 0xf5d258e2
d00114d0:	d1054300 	mrsle	r4, SP_abt
d00114d4:	2b006da3 	blcs	0xd002cb68
d00114d8:	4bc7d187 	blmi	0xcf205afc
d00114dc:	e78c447b 			; <UNDEFINED> instruction: 0xe78c447b
d00114e0:	512ef504 	msrpl	CPSR_fsx, r4, lsl #10
d00114e4:	7b98f50d 	blvc	0xce64e920
d00114e8:	31086f60 	tstcc	r8, r0, ror #30
d00114ec:	f8cd6ee7 			; <UNDEFINED> instruction: 0xf8cd6ee7
d00114f0:	9106b004 	tstls	r6, r4
d00114f4:	7180f44f 	orrvc	pc, r0, pc, asr #8
d00114f8:	91029307 	tstls	r2, r7, lsl #6
d00114fc:	9109a90b 	tstls	r9, fp, lsl #18
d0011500:	99069100 	stmdbls	r6, {r8, ip, pc}
d0011504:	4649440a 	strbmi	r4, [r9], -sl, lsl #8
d0011508:	9b0747b8 	blls	0xd01e33f0
d001150c:	6da5b930 			; <UNDEFINED> instruction: 0x6da5b930
d0011510:	f47f2d00 			; <UNDEFINED> instruction: 0xf47f2d00
d0011514:	4bb9af6a 	blmi	0xcee7d2c4
d0011518:	e76e447b 			; <UNDEFINED> instruction: 0xe76e447b
d001151c:	68129a09 	ldmdavs	r2, {r0, r3, r9, fp, ip, pc}
d0011520:	d2064293 	andle	r4, r6, #805306377	; 0x30000009
d0011524:	2b006da3 	blcs	0xd002cbb8
d0011528:	af5ff47f 	svcge	0x005ff47f
d001152c:	447b4bb4 	ldrbtmi	r4, [fp], #-2996	; 0xfffff44c
d0011530:	f642e763 			; <UNDEFINED> instruction: 0xf642e763
d0011534:	21003384 	smlabbcs	r0, r4, r3, r3
d0011538:	9b0658e0 	blls	0xd01a78c0
d001153c:	f0114418 			; <UNDEFINED> instruction: 0xf0114418
d0011540:	4681fc67 	strmi	pc, [r1], r7, ror #24
d0011544:	d1ed2800 	mvnle	r2, r0, lsl #16
d0011548:	3000f8da 	ldrdcc	pc, [r0], -sl
d001154c:	70a6f44f 	adcvc	pc, r6, pc, asr #8
d0011550:	33019307 	movwcc	r9, #4871	; 0x1307
d0011554:	3000f8ca 	andcc	pc, r0, sl, asr #17
d0011558:	43439b07 	movtmi	r9, #15111	; 0x3b07
d001155c:	93084658 	movwls	r4, #34392	; 0x8658
d0011560:	7300f503 	movwvc	pc, #1283	; 0x503	; <UNPREDICTABLE>
d0011564:	0a03eb04 	beq	0xd010c17c
d0011568:	fc68f011 	stc2l	0, cr15, [r8], #-68	; 0xffffffbc
d001156c:	1c424659 	mcrrne	6, 5, r4, r2, cr9
d0011570:	f0104650 			; <UNDEFINED> instruction: 0xf0104650
d0011574:	f642f85b 			; <UNDEFINED> instruction: 0xf642f85b
d0011578:	9b083284 	blls	0xd021df90
d001157c:	9a0958a1 	bls	0xd0267808
d0011580:	681218e3 	ldmdavs	r2, {r0, r1, r5, r6, r7, fp, ip}
d0011584:	1300f8c3 	movwne	pc, #2243	; 0x8c3	; <UNPREDICTABLE>
d0011588:	2304f8c3 	movwcs	pc, #18627	; 0x48c3	; <UNPREDICTABLE>
d001158c:	9308f8c3 	movwls	pc, #35011	; 0x88c3	; <UNPREDICTABLE>
d0011590:	440b9b06 	strmi	r9, [fp], #-2822	; 0xfffff4fa
d0011594:	0902eb03 	stmdbeq	r2, {r0, r1, r8, r9, fp, sp, lr, pc}
d0011598:	4a90469a 	bmi	0xce423008
d001159c:	d90945d1 	stmdble	r9, {r0, r4, r6, r7, r8, sl, lr}
d00115a0:	3000f89a 	mulcc	r0, sl, r8
d00115a4:	b2db3b09 	sbcslt	r3, fp, #9216	; 0x2400
d00115a8:	d8032b17 	stmdale	r3, {r0, r1, r2, r4, r8, r9, fp, sp}
d00115ac:	f303fa22 	vpmax.u8	d15, d3, d18
d00115b0:	d41607db 	ldrle	r0, [r6], #-2011	; 0xfffff825
d00115b4:	030aeba9 	movweq	lr, #43945	; 0xaba9
d00115b8:	dd292b01 	fstmdbxle	r9!, {d2-d1}	;@ Deprecated
d00115bc:	3000f89a 	mulcc	r0, sl, r8
d00115c0:	d1252b2f 			; <UNDEFINED> instruction: 0xd1252b2f
d00115c4:	3001f89a 	mulcc	r1, sl, r8
d00115c8:	d10d2b2f 	tstle	sp, pc, lsr #22
d00115cc:	0302f10a 	movweq	pc, #8458	; 0x210a	; <UNPREDICTABLE>
d00115d0:	469a4599 			; <UNDEFINED> instruction: 0x469a4599
d00115d4:	f89ad9ee 			; <UNDEFINED> instruction: 0xf89ad9ee
d00115d8:	33011000 	movwcc	r1, #4096	; 0x1000
d00115dc:	d1f7290a 	mvnsle	r2, sl, lsl #18
d00115e0:	f10ae7dc 			; <UNDEFINED> instruction: 0xf10ae7dc
d00115e4:	e7d90a01 	ldrb	r0, [r9, r1, lsl #20]
d00115e8:	d1112b2a 	tstle	r1, sl, lsr #22
d00115ec:	0a02f10a 	beq	0xd00cda1c
d00115f0:	0301f10a 	movweq	pc, #4362	; 0x110a	; <UNPREDICTABLE>
d00115f4:	d90b4599 	stmdble	fp, {r0, r3, r4, r7, r8, sl, lr}
d00115f8:	1c01f813 	stcne	8, cr15, [r1], {19}
d00115fc:	d105292a 	tstle	r5, sl, lsr #18
d0011600:	292f7819 	stmdbcs	pc!, {r0, r3, r4, fp, ip, sp, lr}	; <UNPREDICTABLE>
d0011604:	f10ad102 			; <UNDEFINED> instruction: 0xf10ad102
d0011608:	e7c70a02 	strb	r0, [r7, r2, lsl #20]
d001160c:	e7ef469a 			; <UNDEFINED> instruction: 0xe7ef469a
d0011610:	030aeba9 	movweq	lr, #43945	; 0xaba9
d0011614:	dd422b06 	vstrle	d18, [r2, #-24]	; 0xffffffe8
d0011618:	2207497a 	andcs	r4, r7, #1998848	; 0x1e8000
d001161c:	44794650 	ldrbtmi	r4, [r9], #-1616	; 0xfffff9b0
d0011620:	f814f010 			; <UNDEFINED> instruction: 0xf814f010
d0011624:	f10abbd8 			; <UNDEFINED> instruction: 0xf10abbd8
d0011628:	45b90707 	ldrmi	r0, [r9, #1799]!	; 0x707
d001162c:	f89ad005 			; <UNDEFINED> instruction: 0xf89ad005
d0011630:	2b203007 	blcs	0xd081d654
d0011634:	2b09d001 	blcs	0xd0285640
d0011638:	45b9d131 	ldrmi	sp, [r9, #305]!	; 0x131
d001163c:	d9474639 	stmdble	r7, {r0, r3, r4, r5, r9, sl, lr}^
d0011640:	f813463b 			; <UNDEFINED> instruction: 0xf813463b
d0011644:	2a202b01 	bcs	0xd081c250
d0011648:	2a09d040 	bcs	0xd0285750
d001164c:	463ad03e 			; <UNDEFINED> instruction: 0x463ad03e
d0011650:	f8923701 			; <UNDEFINED> instruction: 0xf8923701
d0011654:	4650a000 	ldrbmi	sl, [r0], -r0
d0011658:	fef9f7fe 	mrc2	7, 7, pc, cr9, cr14, {7}
d001165c:	f1aab920 			; <UNDEFINED> instruction: 0xf1aab920
d0011660:	f1ba0a30 			; <UNDEFINED> instruction: 0xf1ba0a30
d0011664:	d8020f09 	stmdale	r2, {r0, r3, r8, r9, sl, fp}
d0011668:	463a45b9 			; <UNDEFINED> instruction: 0x463a45b9
d001166c:	1a57d8ef 	bne	0xd1607a30
d0011670:	7808d015 	stmdavc	r8, {r0, r2, r4, ip, lr, pc}
d0011674:	feebf7fe 	mcr2	7, 7, pc, cr11, cr14, {7}	; <UNPREDICTABLE>
d0011678:	2f3fb188 	svccs	0x003fb188
d001167c:	9b08d80f 	blls	0xd02476c0
d0011680:	f203463a 	vmin.s8	d4, d3, d26
d0011684:	4420300b 	strtmi	r3, [r0], #-11
d0011688:	ffd0f00f 			; <UNDEFINED> instruction: 0xffd0f00f
d001168c:	f44f9b07 			; <UNDEFINED> instruction: 0xf44f9b07
d0011690:	fb0272a6 	blx	0xd00ae132
d0011694:	23004203 	movwcs	r4, #515	; 0x203
d0011698:	f882443a 			; <UNDEFINED> instruction: 0xf882443a
d001169c:	f642330b 			; <UNDEFINED> instruction: 0xf642330b
d00116a0:	990b3284 	stmdbls	fp, {r2, r7, r9, ip, sp}
d00116a4:	440b58a3 	strmi	r5, [fp], #-2211	; 0xfffff75d
d00116a8:	7a2350a3 	bvc	0xd08e593c
d00116ac:	409f2701 	addsmi	r2, pc, r1, lsl #14
d00116b0:	73a6f44f 			; <UNDEFINED> instruction: 0x73a6f44f
d00116b4:	4308fb03 	movwmi	pc, #35587	; 0x8b03	; <UNPREDICTABLE>
d00116b8:	f893b2bf 			; <UNDEFINED> instruction: 0xf893b2bf
d00116bc:	b14a230a 	cmplt	sl, sl, lsl #6
d00116c0:	3308f8b3 	movwcc	pc, #34995	; 0x88b3	; <UNPREDICTABLE>
d00116c4:	d005421f 	andle	r4, r5, pc, lsl r2
d00116c8:	e68f2501 	str	r2, [pc], r1, lsl #10
d00116cc:	e7b4461f 			; <UNDEFINED> instruction: 0xe7b4461f
d00116d0:	e7cc463a 			; <UNDEFINED> instruction: 0xe7cc463a
d00116d4:	31fcf8d4 	ldrsbcc	pc, [ip, #132]!	; 0x84	; <UNPREDICTABLE>
d00116d8:	d1062b0c 	tstle	r6, ip, lsl #22
d00116dc:	2b006da3 	blcs	0xd002cd70
d00116e0:	ae83f47f 	mcrge	4, 4, pc, cr3, cr15, {3}	; <UNPREDICTABLE>
d00116e4:	447b4b48 	ldrbtmi	r4, [fp], #-2888	; 0xfffff4b8
d00116e8:	f44fe687 	vst1.32	{d30-d32}, [pc], r7
d00116ec:	fb0171a6 	blx	0xd006dd8e
d00116f0:	1863f108 	stmdane	r3!, {r3, r8, ip, sp, lr, pc}^
d00116f4:	330bf893 	movwcc	pc, #47251	; 0xb893	; <UNPREDICTABLE>
d00116f8:	6fa1b94b 	svcvs	0x00a1b94b
d00116fc:	d1234541 			; <UNDEFINED> instruction: 0xd1234541
d0011700:	2b006da3 	blcs	0xd002cd94
d0011704:	ae71f47f 	mrcge	4, 3, APSR_nzcv, cr1, cr15, {3}
d0011708:	447b4b40 	ldrbtmi	r4, [fp], #-2880	; 0xfffff4c0
d001170c:	f201e675 	vmin.s8	q7, <illegal reg q0.5>, <illegal reg q10.5>
d0011710:	f504310b 			; <UNDEFINED> instruction: 0xf504310b
d0011714:	f504492b 			; <UNDEFINED> instruction: 0xf504492b
d0011718:	f04f4b4f 			; <UNDEFINED> instruction: 0xf04f4b4f
d001171c:	44210a00 	strtmi	r0, [r1], #-2560	; 0xfffff600
d0011720:	0988f109 	stmibeq	r8, {r0, r3, r8, ip, sp, lr, pc}
d0011724:	0b88f10b 	bleq	0xce24db58
d0011728:	3000f8db 	ldrdcc	pc, [r0], -fp
d001172c:	d2e4459a 	rscle	r4, r4, #645922816	; 0x26800000
d0011730:	91064648 	tstls	r6, r8, asr #12
d0011734:	0948f109 	stmdbeq	r8, {r0, r3, r8, ip, sp, lr, pc}^
d0011738:	fb8cf011 	blx	0xce34d786
d001173c:	d0c32800 	sbcle	r2, r3, r0, lsl #16
d0011740:	0a01f10a 	beq	0xd008db70
d0011744:	e7ef9906 	strb	r9, [pc, r6, lsl #18]!
d0011748:	01fcf8d4 	ldrsbeq	pc, [ip, #132]!	; 0x84	; <UNPREDICTABLE>
d001174c:	f1042200 			; <UNDEFINED> instruction: 0xf1042200
d0011750:	42820c94 	addmi	r0, r2, #148, 24	; 0x9400
d0011754:	1342ea4f 	movtne	lr, #10831	; 0x2a4f
d0011758:	3201d13a 	andcc	sp, r1, #-2147483634	; 0x8000000e
d001175c:	f8d468e5 			; <UNDEFINED> instruction: 0xf8d468e5
d0011760:	44239074 	strtmi	r9, [r3], #-116	; 0xffffff8c
d0011764:	21fcf8c4 	mvnscs	pc, r4, asr #17
d0011768:	020cf24d 	andeq	pc, ip, #-805306364	; 0xd0000004
d001176c:	e004f8d4 	ldrd	pc, [r4], -r4
d0011770:	c002f854 	andgt	pc, r2, r4, asr r8	; <UNPREDICTABLE>
d0011774:	e9d46822 	ldmib	r4, {r1, r5, fp, sp, lr}^
d0011778:	f8c36004 			; <UNDEFINED> instruction: 0xf8c36004
d001177c:	25015088 	strcs	r5, [r1, #-136]	; 0xffffff78
d0011780:	608cf8c3 	addvs	pc, ip, r3, asr #17
d0011784:	f8c367da 			; <UNDEFINED> instruction: 0xf8c367da
d0011788:	e9c3c098 	stmib	r3, {r3, r4, r7, lr, pc}^
d001178c:	e9c30124 	stmib	r3, {r2, r5, r8}^
d0011790:	f44f9e20 			; <UNDEFINED> instruction: 0xf44f9e20
d0011794:	fb0373a6 	blx	0xd00ee636
d0011798:	18e1f308 	stmiane	r1!, {r3, r8, r9, ip, sp, lr, pc}^
d001179c:	7300f503 	movwvc	pc, #1283	; 0x503	; <UNPREDICTABLE>
d00117a0:	2308f8b1 	movwcs	pc, #34993	; 0x88b1	; <UNPREDICTABLE>
d00117a4:	f8d14423 			; <UNDEFINED> instruction: 0xf8d14423
d00117a8:	43170300 	tstmi	r7, #0, 6
d00117ac:	522ef504 	eorpl	pc, lr, #4, 10	; 0x1000000
d00117b0:	f8a13208 			; <UNDEFINED> instruction: 0xf8a13208
d00117b4:	44027308 	strmi	r7, [r2], #-776	; 0xfffffcf8
d00117b8:	f8d16022 			; <UNDEFINED> instruction: 0xf8d16022
d00117bc:	67632304 	strbvs	r2, [r3, -r4, lsl #6]!
d00117c0:	22006062 	andcs	r6, r0, #98	; 0x62
d00117c4:	8078f8c4 	rsbshi	pc, r8, r4, asr #17
d00117c8:	e9c460e2 	stmib	r4, {r1, r5, r6, r7, sp, lr}^
d00117cc:	e60d5504 	str	r5, [sp], -r4, lsl #10
d00117d0:	3003f85c 	andcc	pc, r3, ip, asr r8	; <UNPREDICTABLE>
d00117d4:	d0934598 	umullsle	r4, r3, r8, r5
d00117d8:	e7ba3201 	ldr	r3, [sl, r1, lsl #4]!
d00117dc:	00800013 	addeq	r0, r0, r3, lsl r0
d00117e0:	fffffe34 			; <UNDEFINED> instruction: 0xfffffe34
d00117e4:	fffffe3f 			; <UNDEFINED> instruction: 0xfffffe3f
d00117e8:	fffffe35 			; <UNDEFINED> instruction: 0xfffffe35
d00117ec:	fffffe28 			; <UNDEFINED> instruction: 0xfffffe28
d00117f0:	fffffe1b 			; <UNDEFINED> instruction: 0xfffffe1b
d00117f4:	fffffde8 			; <UNDEFINED> instruction: 0xfffffde8
d00117f8:	fffffe11 			; <UNDEFINED> instruction: 0xfffffe11
d00117fc:	fffffdf9 			; <UNDEFINED> instruction: 0xfffffdf9
d0011800:	fffffe12 			; <UNDEFINED> instruction: 0xfffffe12
d0011804:	fffffd4f 			; <UNDEFINED> instruction: 0xfffffd4f
d0011808:	fffffc8f 			; <UNDEFINED> instruction: 0xfffffc8f
d001180c:	fffffc8b 			; <UNDEFINED> instruction: 0xfffffc8b

Disassembly of section .text.scan:

d00119ac <.text.scan>:
d00119ac:	e92d6d8b 	push	{r0, r1, r3, r7, r8, sl, fp, sp, lr}
d00119b0:	46064ff0 			; <UNDEFINED> instruction: 0x46064ff0
d00119b4:	460cb09d 			; <UNDEFINED> instruction: 0x460cb09d
d00119b8:	f501bba3 			; <UNDEFINED> instruction: 0xf501bba3
d00119bc:	f1084850 			; <UNDEFINED> instruction: 0xf1084850
d00119c0:	4620080c 	strtmi	r0, [r0], -ip, lsl #16
d00119c4:	fcacf7fe 	stc2	7, cr15, [ip], #1016	; 0x3f8
d00119c8:	d14f2800 	cmple	pc, r0, lsl #16
d00119cc:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d00119d0:	fc5cf7fe 	mrrc2	7, 15, pc, ip, cr14	; <UNPREDICTABLE>
d00119d4:	d0282820 	eorle	r2, r8, r0, lsr #16
d00119d8:	d0262809 	eorle	r2, r6, r9, lsl #16
d00119dc:	68e22823 	stmiavs	r2!, {r0, r1, r5, fp, sp}^
d00119e0:	d1366863 	teqle	r6, r3, ror #16
d00119e4:	d241429a 	suble	r4, r1, #-1610612727	; 0xa0000009
d00119e8:	0930f10d 	ldmdbeq	r0!, {r0, r2, r3, r8, ip, sp, lr, pc}
d00119ec:	466f4621 	strbtmi	r4, [pc], -r1, lsr #12
d00119f0:	4648ad14 			; <UNDEFINED> instruction: 0x4648ad14
d00119f4:	fc72f7fe 	ldc2l	7, cr15, [r2], #-1016	; 0xfffffc08
d00119f8:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d00119fc:	f10dfc50 			; <UNDEFINED> instruction: 0xf10dfc50
d0011a00:	e8bc0c38 	ldm	ip!, {r3, r4, r5, sl, fp}
d0011a04:	c70f000f 	strgt	r0, [pc, -pc]
d0011a08:	0003e89c 	muleq	r3, ip, r8
d0011a0c:	0003e887 	andeq	lr, r3, r7, lsl #17
d0011a10:	46284621 	strtmi	r4, [r8], -r1, lsr #12
d0011a14:	000ce899 	muleq	ip, r9, r8
d0011a18:	fd2af000 	stc2	0, cr15, [sl, #-0]
d0011a1c:	b1436da3 	smlaltblt	r6, r3, r3, sp
d0011a20:	46304621 	ldrtmi	r4, [r0], -r1, lsr #12
d0011a24:	fc5af7fe 	mrrc2	7, 15, pc, sl, cr14	; <UNPREDICTABLE>
d0011a28:	4620e00f 	strtmi	lr, [r0], -pc
d0011a2c:	fc37f7fe 	ldc2	7, cr15, [r7], #-1016	; 0xfffffc08
d0011a30:	9b19e7cc 	blls	0xd068b968
d0011a34:	7f97f5b3 	svcvc	0x0097f5b3
d0011a38:	462cd0c3 	strtmi	sp, [ip], -r3, asr #1
d0011a3c:	cc0f4637 	stcgt	6, cr4, [pc], {55}	; 0x37
d0011a40:	e894c70f 	ldm	r4, {r0, r1, r2, r3, r8, r9, sl, lr, pc}
d0011a44:	e887000f 	stm	r7, {r0, r1, r2, r3}
d0011a48:	4630000f 	ldrtmi	r0, [r0], -pc
d0011a4c:	e8bdb01d 	pop	{r0, r2, r3, r4, ip, sp, pc}
d0011a50:	429a8ff0 	addsmi	r8, sl, #240, 30	; 0x3c0
d0011a54:	4620d20a 	strtmi	sp, [r0], -sl, lsl #4
d0011a58:	fc7ff7fe 	ldc2l	7, cr15, [pc], #-1016	; 0xd0011668
d0011a5c:	686368e2 	stmdavs	r3!, {r1, r5, r6, r7, fp, sp, lr}^
d0011a60:	d2ae429a 	adcle	r4, lr, #-1610612727	; 0xa0000009
d0011a64:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011a68:	e7aafc1a 			; <UNDEFINED> instruction: 0xe7aafc1a
d0011a6c:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d0011a70:	fc0cf7fe 	stc2	7, cr15, [ip], {254}	; 0xfe
d0011a74:	d0f52820 	rscsle	r2, r5, r0, lsr #16
d0011a78:	0309f1a0 	movweq	pc, #37280	; 0x91a0	; <UNPREDICTABLE>
d0011a7c:	d9f12b04 	ldmible	r1!, {r2, r8, r9, fp, sp}^
d0011a80:	d170282f 	cmnle	r0, pc, lsr #16
d0011a84:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d0011a88:	fc00f7fe 	stc2	7, cr15, [r0], {254}	; 0xfe
d0011a8c:	d10f282f 	tstle	pc, pc, lsr #16
d0011a90:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d0011a94:	fbfaf7fe 	blx	0xcfecfa96
d0011a98:	686368e2 	stmdavs	r3!, {r1, r5, r6, r7, fp, sp, lr}^
d0011a9c:	d090429a 	umullsle	r4, r0, sl, r2
d0011aa0:	d08e280a 	addle	r2, lr, sl, lsl #16
d0011aa4:	d08c280d 	addle	r2, ip, sp, lsl #16
d0011aa8:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011aac:	e7effbf8 			; <UNDEFINED> instruction: 0xe7effbf8
d0011ab0:	d158282a 	cmple	r8, sl, lsr #16
d0011ab4:	4621a814 			; <UNDEFINED> instruction: 0x4621a814
d0011ab8:	fc10f7fe 	ldc2	7, cr15, [r0], {254}	; 0xfe
d0011abc:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011ac0:	4620fbee 	strtmi	pc, [r0], -lr, ror #23
d0011ac4:	fbebf7fe 	blx	0xcfb0fac6
d0011ac8:	686368e2 	stmdavs	r3!, {r1, r5, r6, r7, fp, sp, lr}^
d0011acc:	f000429a 			; <UNDEFINED> instruction: 0xf000429a
d0011ad0:	210082c0 	smlabtcs	r0, r0, r2, r8
d0011ad4:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011ad8:	282afbd9 	stmdacs	sl!, {r0, r3, r4, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d0011adc:	2101d1f1 	strdcs	sp, [r1, -r1]
d0011ae0:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011ae4:	282ffbd3 	stmdacs	pc!, {r0, r1, r4, r6, r7, r8, r9, fp, ip, sp, lr, pc}	; <UNPREDICTABLE>
d0011ae8:	4620d1eb 	strtmi	sp, [r0], -fp, ror #3
d0011aec:	fbd7f7fe 	blx	0xcf60faee
d0011af0:	3b01e7b8 	blcc	0xd008b9d8
d0011af4:	0000f8d8 	ldrdeq	pc, [r0], -r8
d0011af8:	1143eb04 	cmpne	r3, r4, lsl #22
d0011afc:	f8d1015a 			; <UNDEFINED> instruction: 0xf8d1015a
d0011b00:	42881098 	addmi	r1, r8, #152	; 0x98
d0011b04:	f8dfd006 			; <UNDEFINED> instruction: 0xf8dfd006
d0011b08:	447915e4 	ldrbtmi	r1, [r9], #-1508	; 0xfffffa1c
d0011b0c:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011b10:	e785fbaf 	str	pc, [r5, pc, lsr #23]
d0011b14:	f8c4327c 			; <UNDEFINED> instruction: 0xf8c4327c
d0011b18:	18a331fc 	stmiane	r3!, {r2, r3, r4, r5, r6, r7, r8, ip, sp}
d0011b1c:	c002f854 	andgt	pc, r2, r4, asr r8	; <UNPREDICTABLE>
d0011b20:	000cf103 	andeq	pc, ip, r3, lsl #2
d0011b24:	689d685f 	ldmvs	sp, {r0, r1, r2, r3, r4, r6, fp, sp, lr}
d0011b28:	e9c4c80f 	stmib	r4, {r0, r1, r2, r3, fp, lr, pc}^
d0011b2c:	22011204 	andcs	r1, r1, #4, 4	; 0x40000000
d0011b30:	c000f8c4 	andgt	pc, r0, r4, asr #17
d0011b34:	60656767 	rsbvs	r6, r5, r7, ror #14
d0011b38:	67a360e0 	strvs	r6, [r3, r0, ror #1]!
d0011b3c:	686368e1 	stmdavs	r3!, {r0, r5, r6, r7, fp, sp, lr}^
d0011b40:	f0404299 			; <UNDEFINED> instruction: 0xf0404299
d0011b44:	f8d48297 			; <UNDEFINED> instruction: 0xf8d48297
d0011b48:	2b0031fc 	blcs	0xd001e340
d0011b4c:	2a00d1d1 	bcs	0xd0046298
d0011b50:	af37f47f 	svcge	0x0037f47f
d0011b54:	3000f8d8 	ldrdcc	pc, [r0], -r8
d0011b58:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d0011b5c:	f8df828e 			; <UNDEFINED> instruction: 0xf8df828e
d0011b60:	44791590 	ldrbtmi	r1, [r9], #-1424	; 0xfffffa70
d0011b64:	2200e7d2 	andcs	lr, r0, #55050240	; 0x3480000
d0011b68:	4620e7e8 	strtmi	lr, [r0], -r8, ror #15
d0011b6c:	fb97f7fe 	blx	0xce60fb6e
d0011b70:	46812823 	strmi	r2, [r1], r3, lsr #16
d0011b74:	f10dd123 			; <UNDEFINED> instruction: 0xf10dd123
d0011b78:	46ec0e38 			; <UNDEFINED> instruction: 0x46ec0e38
d0011b7c:	e8beaf14 	ldm	lr!, {r2, r4, r8, r9, sl, fp, sp, pc}
d0011b80:	e8ac000f 	stmia	ip!, {r0, r1, r2, r3}
d0011b84:	e89e000f 	ldm	lr, {r0, r1, r2, r3}
d0011b88:	e88c0003 	stm	ip, {r0, r1}
d0011b8c:	46210003 	strtmi	r0, [r1], -r3
d0011b90:	e8954638 	ldm	r5, {r3, r4, r5, r9, sl, lr}
d0011b94:	f000000c 			; <UNDEFINED> instruction: 0xf000000c
d0011b98:	6da3fc6b 	stcvs	12, cr15, [r3, #428]!	; 0x1ac
d0011b9c:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0011ba0:	9b19af3f 	blls	0xd067d8a4
d0011ba4:	7f97f5b3 	svcvc	0x0097f5b3
d0011ba8:	af0bf43f 	svcge	0x000bf43f
d0011bac:	4635463c 			; <UNDEFINED> instruction: 0x4635463c
d0011bb0:	c50fcc0f 	strgt	ip, [pc, #-3087]	; 0xd0010fa9
d0011bb4:	000fe894 	muleq	pc, r4, r8	; <UNPREDICTABLE>
d0011bb8:	000fe885 	andeq	lr, pc, r5, lsl #17
d0011bbc:	f7fee745 			; <UNDEFINED> instruction: 0xf7fee745
d0011bc0:	4601fc46 	strmi	pc, [r1], -r6, asr #24
d0011bc4:	d1402800 	cmple	r0, r0, lsl #16
d0011bc8:	0830f1a9 	ldmdaeq	r0!, {r0, r3, r5, r7, r8, ip, sp, lr, pc}
d0011bcc:	0f09f1b8 	svceq	0x0009f1b8
d0011bd0:	8111f200 	tsthi	r1, r0, lsl #4	; <UNPREDICTABLE>
d0011bd4:	0f30f1b9 	svceq	0x0030f1b9
d0011bd8:	8266f000 	rsbhi	pc, r6, #0
d0011bdc:	2100270a 	tstcs	r0, sl, lsl #14
d0011be0:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011be4:	4681fb53 	pkhtbmi	pc, r1, r3, asr #22	; <UNPREDICTABLE>
d0011be8:	fc7ef7fe 	ldc2l	7, cr15, [lr], #-1016	; 0xfffffc08
d0011bec:	f2004287 	vhsub.s8	d4, d16, d7
d0011bf0:	f04980db 			; <UNDEFINED> instruction: 0xf04980db
d0011bf4:	f1b90920 			; <UNDEFINED> instruction: 0xf1b90920
d0011bf8:	d1020f75 	tstle	r2, r5, ror pc
d0011bfc:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011c00:	2100fb4e 	tstcs	r0, lr, asr #22	; <UNPREDICTABLE>
d0011c04:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011c08:	f1a0fb41 			; <UNDEFINED> instruction: 0xf1a0fb41
d0011c0c:	46020330 			; <UNDEFINED> instruction: 0x46020330
d0011c10:	d90f2b09 	stmdble	pc, {r0, r3, r8, r9, fp, sp}	; <UNPREDICTABLE>
d0011c14:	fc1bf7fe 	ldc2	7, cr15, [fp], {254}	; 0xfe
d0011c18:	2a2eb960 	bcs	0xd0bc01a0
d0011c1c:	f1b9d00a 			; <UNDEFINED> instruction: 0xf1b9d00a
d0011c20:	f0000f75 			; <UNDEFINED> instruction: 0xf0000f75
d0011c24:	2f0a80e2 	svccs	0x000a80e2
d0011c28:	80d4f040 	sbcshi	pc, r4, r0, asr #32
d0011c2c:	0f00f1b8 	svceq	0x0000f1b8
d0011c30:	80def280 	sbcshi	pc, lr, r0, lsl #5
d0011c34:	2b006da3 	blcs	0xd002d2c8
d0011c38:	aef2f47f 	mrcge	4, 7, APSR_nzcv, cr2, cr15, {3}
d0011c3c:	34b4f8df 	ldrtcc	pc, [r4], #2271	; 0x8df	; <UNPREDICTABLE>
d0011c40:	e041447b 	sub	r4, r1, fp, ror r4
d0011c44:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011c48:	2100fb2a 	tstcs	r0, sl, lsr #22	; <UNPREDICTABLE>
d0011c4c:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011c50:	4602fb1d 			; <UNDEFINED> instruction: 0x4602fb1d
d0011c54:	fbfbf7fe 	blx	0xcff0fc56
d0011c58:	d1f32800 	mvnsle	r2, r0, lsl #16
d0011c5c:	2a093a30 	bcs	0xd0260524
d0011c60:	6825d9f0 	stmdavs	r5!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
d0011c64:	68e34680 	stmiavs	r3!, {r7, r9, sl, lr}^
d0011c68:	948cf8df 	strls	pc, [ip], #2271	; 0x8df
d0011c6c:	44f9441d 	ldrbtmi	r4, [r9], #1053	; 0x41d
d0011c70:	f8591bed 			; <UNDEFINED> instruction: 0xf8591bed
d0011c74:	46292b04 	strtmi	r2, [r9], -r4, lsl #22
d0011c78:	f7fe4638 			; <UNDEFINED> instruction: 0xf7fe4638
d0011c7c:	b160fe5b 	msrlt	(UNDEF: 96), fp
d0011c80:	1007f208 	andne	pc, r7, r8, lsl #4
d0011c84:	9011950d 	andsls	r9, r1, sp, lsl #10
d0011c88:	ad0c4634 	stcge	6, cr4, [ip, #-208]	; 0xffffff30
d0011c8c:	c40fcd0f 	strgt	ip, [pc], #-3343	; 0xd0011c94
d0011c90:	000fe895 	muleq	pc, r5, r8	; <UNPREDICTABLE>
d0011c94:	000fe884 	andeq	lr, pc, r4, lsl #17
d0011c98:	f108e6d7 			; <UNDEFINED> instruction: 0xf108e6d7
d0011c9c:	f1b80801 			; <UNDEFINED> instruction: 0xf1b80801
d0011ca0:	d1e60f15 	mvnle	r0, r5, lsl pc
d0011ca4:	9454f8df 	ldrbls	pc, [r4], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d0011ca8:	44f94680 	ldrbtmi	r4, [r9], #1664	; 0x680
d0011cac:	2b04f859 	blcs	0xd014fe18
d0011cb0:	46384629 	ldrtmi	r4, [r8], -r9, lsr #12
d0011cb4:	fe3ef7fe 	mrc2	7, 1, pc, cr14, cr14, {7}
d0011cb8:	6da3b168 	stfvsd	f3, [r3, #416]!	; 0x1a0
d0011cbc:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0011cc0:	f8dfaeaf 			; <UNDEFINED> instruction: 0xf8dfaeaf
d0011cc4:	447b343c 	ldrbtmi	r3, [fp], #-1084	; 0xfffffbc4
d0011cc8:	9b0665a3 	blls	0xd01ab35c
d0011ccc:	ba18e9c4 	blt	0xd064c3e4
d0011cd0:	9b0765e3 	blls	0xd01eb464
d0011cd4:	f108e1cc 			; <UNDEFINED> instruction: 0xf108e1cc
d0011cd8:	f1b80801 			; <UNDEFINED> instruction: 0xf1b80801
d0011cdc:	d1e50f17 	mvnle	r0, r7, lsl pc
d0011ce0:	4639462a 	ldrtmi	r4, [r9], -sl, lsr #12
d0011ce4:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011ce8:	2800fb4b 	stmdacs	r0, {r0, r1, r3, r6, r8, r9, fp, ip, sp, lr, pc}
d0011cec:	2128db0c 			; <UNDEFINED> instruction: 0x2128db0c
d0011cf0:	fb01950d 	blx	0xd007712e
d0011cf4:	f5044400 			; <UNDEFINED> instruction: 0xf5044400
d0011cf8:	f8d43478 			; <UNDEFINED> instruction: 0xf8d43478
d0011cfc:	930e30b0 	movwls	r3, #57520	; 0xe0b0
d0011d00:	7381f44f 	orrvc	pc, r1, #1325400064	; 0x4f000000
d0011d04:	e7bf9311 			; <UNDEFINED> instruction: 0xe7bf9311
d0011d08:	4639462a 	ldrtmi	r4, [r9], -sl, lsr #12
d0011d0c:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011d10:	2800fb7c 	stmdacs	r0, {r2, r3, r4, r5, r6, r8, r9, fp, ip, sp, lr, pc}
d0011d14:	2348db2a 	movtcs	sp, #35626	; 0x8b2a
d0011d18:	4000fb03 	andmi	pc, r0, r3, lsl #22
d0011d1c:	402bf500 	eormi	pc, fp, r0, lsl #10
d0011d20:	e9d030c8 	ldmib	r0, {r3, r6, r7, ip, sp}^
d0011d24:	f1100100 			; <UNDEFINED> instruction: 0xf1100100
d0011d28:	93084300 	movwls	r4, #33536	; 0x8300
d0011d2c:	0300f141 	movweq	pc, #321	; 0x141	; <UNPREDICTABLE>
d0011d30:	e9dd9309 	ldmib	sp, {r0, r3, r8, r9, ip, pc}^
d0011d34:	2b012308 	blcs	0xd005a95c
d0011d38:	f1b2bf08 			; <UNDEFINED> instruction: 0xf1b2bf08
d0011d3c:	d3064f00 	movwle	r4, #28416	; 0x6f00
d0011d40:	2b006da3 	blcs	0xd002d3d4
d0011d44:	ae6cf47f 	mcrge	4, 3, pc, cr12, cr15, {3}	; <UNPREDICTABLE>
d0011d48:	447b4bee 	ldrbtmi	r4, [fp], #-3054	; 0xfffff412
d0011d4c:	f06fe7bc 			; <UNDEFINED> instruction: 0xf06fe7bc
d0011d50:	23004200 	movwcs	r4, #512	; 0x200
d0011d54:	4282900a 	addmi	r9, r2, #10
d0011d58:	f240418b 	vrhadd.s8	d20, d16, d11
d0011d5c:	bfa81303 	svclt	0x00a81303
d0011d60:	7381f44f 	orrvc	pc, r1, #1325400064	; 0x4f000000
d0011d64:	950d9a0a 	strls	r9, [sp, #-2570]	; 0xfffff5f6
d0011d68:	e7cb920e 	strb	r9, [fp, lr, lsl #4]
d0011d6c:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d0011d70:	4620e7f8 			; <UNDEFINED> instruction: 0x4620e7f8
d0011d74:	f7fe910a 			; <UNDEFINED> instruction: 0xf7fe910a
d0011d78:	990afa92 	stmdbls	sl, {r1, r4, r7, r9, fp, ip, sp, lr, pc}
d0011d7c:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011d80:	f7fefa85 			; <UNDEFINED> instruction: 0xf7fefa85
d0011d84:	2810fbb1 	ldmdacs	r0, {r0, r4, r5, r7, r8, r9, fp, ip, sp, lr, pc}
d0011d88:	d1214607 			; <UNDEFINED> instruction: 0xd1214607
d0011d8c:	2b006da3 	blcs	0xd002d420
d0011d90:	af25f47f 	svcge	0x0025f47f
d0011d94:	447b4bdc 	ldrbtmi	r4, [fp], #-3036	; 0xfffff424
d0011d98:	9b0665a3 	blls	0xd01ab42c
d0011d9c:	9b0765e3 	blls	0xd01eb530
d0011da0:	ba18e9c4 	blt	0xd064c4b8
d0011da4:	e71a66a3 	ldr	r6, [sl, -r3, lsr #13]
d0011da8:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011dac:	f7fefa78 			; <UNDEFINED> instruction: 0xf7fefa78
d0011db0:	43c3fb9b 	bicmi	pc, r3, #158720	; 0x26c00
d0011db4:	f3f7fbb3 			; <UNDEFINED> instruction: 0xf3f7fbb3
d0011db8:	d2064543 	andle	r4, r6, #281018368	; 0x10c00000
d0011dbc:	2b006da3 	blcs	0xd002d450
d0011dc0:	ae2ef47f 	mcrge	4, 1, pc, cr14, cr15, {3}	; <UNPREDICTABLE>
d0011dc4:	447b4bd1 	ldrbtmi	r4, [fp], #-3025	; 0xfffff42f
d0011dc8:	fb08e77e 	blx	0xd024bbca
d0011dcc:	e7060807 	str	r0, [r6, -r7, lsl #16]
d0011dd0:	e7042710 	smlad	r4, r0, r7, r2
d0011dd4:	0f00f1b8 	svceq	0x0000f1b8
d0011dd8:	1303f240 	movwne	pc, #12864	; 0x3240	; <UNPREDICTABLE>
d0011ddc:	f44fbfa8 			; <UNDEFINED> instruction: 0xf44fbfa8
d0011de0:	f8cd7381 			; <UNDEFINED> instruction: 0xf8cd7381
d0011de4:	93118038 	tstls	r1, #56	; 0x38
d0011de8:	f240e15c 	vand	q15, q0, q6
d0011dec:	e7f81303 	ldrb	r1, [r8, r3, lsl #6]!
d0011df0:	7381f44f 	orrvc	pc, r1, #1325400064	; 0x4f000000
d0011df4:	f1b9e7f5 			; <UNDEFINED> instruction: 0xf1b9e7f5
d0011df8:	d0020f22 	andle	r0, r2, r2, lsr #30
d0011dfc:	0f27f1b9 	svceq	0x0027f1b9
d0011e00:	6823d171 	stmdavs	r3!, {r0, r4, r5, r6, r8, ip, lr, pc}
d0011e04:	4701f242 	strmi	pc, [r1, -r2, asr #4]
d0011e08:	68e39308 	stmiavs	r3!, {r3, r8, r9, ip, pc}^
d0011e0c:	68e2930b 	stmiavs	r2!, {r0, r1, r3, r8, r9, ip, pc}^
d0011e10:	429a6863 	addsmi	r6, sl, #6488064	; 0x630000
d0011e14:	4620d05a 			; <UNDEFINED> instruction: 0x4620d05a
d0011e18:	fa41f7fe 	blx	0xd108fe18
d0011e1c:	d14a4581 	smlalbble	r4, sl, r1, r5
d0011e20:	f1b99b08 			; <UNDEFINED> instruction: 0xf1b99b08
d0011e24:	68e70f22 	stmiavs	r7!, {r1, r5, r8, r9, sl, fp}^
d0011e28:	eb039a0b 	bl	0xd00f865c
d0011e2c:	f1070802 			; <UNDEFINED> instruction: 0xf1070802
d0011e30:	682733ff 	stmdavs	r7!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, ip, sp}
d0011e34:	eba7441f 	bl	0xce9e2eb8
d0011e38:	d0390708 	eorsle	r0, r9, r8, lsl #14
d0011e3c:	0907eb08 	stmdbeq	r7, {r3, r8, r9, fp, sp, lr, pc}
d0011e40:	8050f8cd 	subshi	pc, r0, sp, asr #17
d0011e44:	d10645c8 	smlabtle	r6, r8, r5, r4
d0011e48:	2b006da3 	blcs	0xd002d4dc
d0011e4c:	ade8f47f 	cfstrdge	mvd15, [r8, #508]!	; 0x1fc
d0011e50:	447b4baf 	ldrbtmi	r4, [fp], #-2991	; 0xfffff451
d0011e54:	f108e738 			; <UNDEFINED> instruction: 0xf108e738
d0011e58:	9a080301 	bls	0xd0212a64
d0011e5c:	9314990b 	tstls	r4, #180224	; 0x2c000
d0011e60:	2a5c5c52 	bcs	0xd1728fb0
d0011e64:	d10e920a 	tstle	lr, sl, lsl #4
d0011e68:	d00c4599 	mulle	ip, r9, r5
d0011e6c:	465aab14 			; <UNDEFINED> instruction: 0x465aab14
d0011e70:	46209906 	strtmi	r9, [r0], -r6, lsl #18
d0011e74:	9b079301 	blls	0xd01f6a80
d0011e78:	9008f8cd 	andls	pc, r8, sp, asr #17
d0011e7c:	46539300 	ldrbmi	r9, [r3], -r0, lsl #6
d0011e80:	fb5cf7fe 	blx	0xd174fe82
d0011e84:	9b14900a 	blls	0xd0535eb4
d0011e88:	d00a4599 	mulle	sl, r9, r5
d0011e8c:	b9436da3 	stmdblt	r3, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0011e90:	447b4ba0 	ldrbtmi	r4, [fp], #-2976	; 0xfffff460
d0011e94:	9b0665a3 	blls	0xd01ab528
d0011e98:	9b0765e3 	blls	0xd01eb62c
d0011e9c:	ba18e9c4 	blt	0xd064c5b4
d0011ea0:	f44f66a3 	vst1.32	{d22-d24}, [pc :128], r3
d0011ea4:	9a0a7381 	bls	0xd02aecb0
d0011ea8:	870ce9cd 	strhi	lr, [ip, -sp, asr #19]
d0011eac:	e79a920e 	ldr	r9, [sl, lr, lsl #4]
d0011eb0:	7382f44f 	orrvc	pc, r2, #1325400064	; 0x4f000000
d0011eb4:	285ce7f7 	ldmdacs	ip, {r0, r1, r2, r4, r5, r6, r7, r8, r9, sl, sp, lr, pc}^
d0011eb8:	4620d102 	strtmi	sp, [r0], -r2, lsl #2
d0011ebc:	f9eff7fe 			; <UNDEFINED> instruction: 0xf9eff7fe
d0011ec0:	d8a4280d 	stmiale	r4!, {r0, r2, r3, fp, sp}
d0011ec4:	f000fa27 			; <UNDEFINED> instruction: 0xf000fa27
d0011ec8:	d5a007c3 	strle	r0, [r0, #1987]!	; 0x7c3
d0011ecc:	0f22f1b9 	svceq	0x0022f1b9
d0011ed0:	4b91d102 	blmi	0xce4862e0
d0011ed4:	e001447b 	and	r4, r1, fp, ror r4
d0011ed8:	447b4b90 	ldrbtmi	r4, [fp], #-2960	; 0xfffff470
d0011edc:	2a006da2 	bcs	0xd002d56c
d0011ee0:	ad9ef47f 	cfldrsge	mvf15, [lr, #508]	; 0x1fc
d0011ee4:	900ae6f0 	strdls	lr, [sl], -r0
d0011ee8:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011eec:	f029f9cf 			; <UNDEFINED> instruction: 0xf029f9cf
d0011ef0:	46800302 	strmi	r0, [r0], r2, lsl #6
d0011ef4:	2b3c990a 	blcs	0xd0f38324
d0011ef8:	4581d11e 	strmi	sp, [r1, #286]	; 0x11e
d0011efc:	4620d11c 			; <UNDEFINED> instruction: 0x4620d11c
d0011f00:	f7fe9106 			; <UNDEFINED> instruction: 0xf7fe9106
d0011f04:	f1b9f9cc 			; <UNDEFINED> instruction: 0xf1b9f9cc
d0011f08:	99060f3c 	stmdbls	r6, {r2, r3, r4, r5, r8, r9, sl, fp}
d0011f0c:	f2404620 	vmax.s8	d20, d0, d16
d0011f10:	bf181727 	svclt	0x00181727
d0011f14:	7794f44f 	ldrvc	pc, [r4, pc, asr #8]
d0011f18:	f9b8f7fe 			; <UNDEFINED> instruction: 0xf9b8f7fe
d0011f1c:	d109283d 	tstle	r9, sp, lsr r8
d0011f20:	f2404620 	vmax.s8	d20, d0, d16
d0011f24:	f7fe172d 			; <UNDEFINED> instruction: 0xf7fe172d
d0011f28:	f1b9f9ba 			; <UNDEFINED> instruction: 0xf1b9f9ba
d0011f2c:	bf080f3c 	svclt	0x00080f3c
d0011f30:	7796f44f 	ldrvc	pc, [r6, pc, asr #8]
d0011f34:	e0b59711 	adcs	r9, r5, r1, lsl r7
d0011f38:	0f3df1b8 	svceq	0x003df1b8
d0011f3c:	80c0f040 	sbchi	pc, r0, r0, asr #32
d0011f40:	0f2bf1b9 	svceq	0x002bf1b9
d0011f44:	f1b9d002 			; <UNDEFINED> instruction: 0xf1b9d002
d0011f48:	d10a0f2d 	tstle	sl, sp, lsr #30
d0011f4c:	f2404620 	vmax.s8	d20, d0, d16
d0011f50:	f7fe1725 			; <UNDEFINED> instruction: 0xf7fe1725
d0011f54:	f1b9f9a4 			; <UNDEFINED> instruction: 0xf1b9f9a4
d0011f58:	bf180f2b 	svclt	0x00180f2b
d0011f5c:	7793f44f 	ldrvc	pc, [r3, pc, asr #8]
d0011f60:	f1b9e7e8 			; <UNDEFINED> instruction: 0xf1b9e7e8
d0011f64:	d0050f26 	andle	r0, r5, r6, lsr #30
d0011f68:	0f7cf1b9 	svceq	0x007cf1b9
d0011f6c:	f1b9d002 			; <UNDEFINED> instruction: 0xf1b9d002
d0011f70:	d10d0f5e 	tstle	sp, lr, asr pc
d0011f74:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011f78:	f1b9f992 			; <UNDEFINED> instruction: 0xf1b9f992
d0011f7c:	d05f0f26 	subsle	r0, pc, r6, lsr #30
d0011f80:	0f7cf1b9 	svceq	0x007cf1b9
d0011f84:	172bf240 	strne	pc, [fp, -r0, asr #4]!
d0011f88:	f44fbf08 			; <UNDEFINED> instruction: 0xf44fbf08
d0011f8c:	e7d17795 	bfi	r7, r5, #15, #3
d0011f90:	0f3df1b9 	svceq	0x003df1b9
d0011f94:	f1a9d112 			; <UNDEFINED> instruction: 0xf1a9d112
d0011f98:	2b02033c 	blcs	0xd0092c90
d0011f9c:	f1b9d911 			; <UNDEFINED> instruction: 0xf1b9d911
d0011fa0:	d1300f2d 	teqle	r0, sp, lsr #30
d0011fa4:	0f3ef1b8 	svceq	0x003ef1b8
d0011fa8:	4620d13e 			; <UNDEFINED> instruction: 0x4620d13e
d0011fac:	7791f44f 	ldrvc	pc, [r1, pc, asr #8]
d0011fb0:	f975f7fe 			; <UNDEFINED> instruction: 0xf975f7fe
d0011fb4:	f1b9e7be 			; <UNDEFINED> instruction: 0xf1b9e7be
d0011fb8:	d1130f3d 	tstle	r3, sp, lsr pc
d0011fbc:	0f21f1b9 	svceq	0x0021f1b9
d0011fc0:	4620d1e9 	strtmi	sp, [r0], -r9, ror #3
d0011fc4:	f96bf7fe 			; <UNDEFINED> instruction: 0xf96bf7fe
d0011fc8:	0f3df1b9 	svceq	0x003df1b9
d0011fcc:	f1b9d03b 			; <UNDEFINED> instruction: 0xf1b9d03b
d0011fd0:	d03b0f21 	eorsle	r0, fp, r1, lsr #30
d0011fd4:	0f3cf1b9 	svceq	0x003cf1b9
d0011fd8:	171ff240 	ldrne	pc, [pc, -r0, asr #4]
d0011fdc:	f44fbf08 			; <UNDEFINED> instruction: 0xf44fbf08
d0011fe0:	e7a7778f 	str	r7, [r7, pc, lsl #15]!
d0011fe4:	0f26f1b9 	svceq	0x0026f1b9
d0011fe8:	f1b9d002 			; <UNDEFINED> instruction: 0xf1b9d002
d0011fec:	d10a0f7c 	tstle	sl, ip, ror pc
d0011ff0:	f2404620 	vmax.s8	d20, d0, d16
d0011ff4:	f7fe1721 			; <UNDEFINED> instruction: 0xf7fe1721
d0011ff8:	f1b8f952 			; <UNDEFINED> instruction: 0xf1b8f952
d0011ffc:	bf080f26 	svclt	0x00080f26
d0012000:	7790f44f 	ldrvc	pc, [r0, pc, asr #8]
d0012004:	f1b9e796 			; <UNDEFINED> instruction: 0xf1b9e796
d0012008:	d10d0f00 	tstle	sp, r0, lsl #30
d001200c:	b9436da3 	stmdblt	r3, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0012010:	447b4b43 	ldrbtmi	r4, [fp], #-2883	; 0xfffff4bd
d0012014:	9b0665a3 	blls	0xd01ab6a8
d0012018:	9b0765e3 	blls	0xd01eb7ac
d001201c:	ba18e9c4 	blt	0xd064c734
d0012020:	f24066a3 	vmax.s8	d22, d16, d19
d0012024:	e7851705 	str	r1, [r5, r5, lsl #14]
d0012028:	0f3df1b8 	svceq	0x003df1b8
d001202c:	d181464f 	orrle	r4, r1, pc, asr #12
d0012030:	4649483c 			; <UNDEFINED> instruction: 0x4649483c
d0012034:	f0104478 			; <UNDEFINED> instruction: 0xf0104478
d0012038:	2800ff25 	stmdacs	r0, {r0, r2, r5, r8, r9, sl, fp, ip, sp, lr, pc}
d001203c:	e779d1e6 	ldrb	sp, [r9, -r6, ror #3]!
d0012040:	1729f240 	strne	pc, [r9, -r0, asr #4]!
d0012044:	f44fe776 	vst1.16	{d30}, [pc :256], r6
d0012048:	e773778e 	ldrb	r7, [r3, -lr, lsl #15]!
d001204c:	171df240 	ldrne	pc, [sp, -r0, asr #4]
d0012050:	6da3e770 	stcvs	7, cr14, [r3, #448]!	; 0x1c0
d0012054:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0012058:	4a33ace3 	bmi	0xd0cfd3ec
d001205c:	3068f89d 	mlscc	r8, sp, r8, pc	; <UNPREDICTABLE>
d0012060:	65a2447a 	strvs	r4, [r2, #1146]!	; 0x47a
d0012064:	65e29a17 	strbvs	r9, [r2, #2583]!	; 0xa17
d0012068:	e9c49a18 	stmib	r4, {r3, r4, r9, fp, ip, pc}^
d001206c:	9b1b2318 	blls	0xd06dacd4
d0012070:	e4d566a3 	ldrb	r6, [r5], #1699	; 0x6a3
d0012074:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0012078:	ad0caca4 	stcge	12, cr10, [ip, #-656]	; 0xfffffd70
d001207c:	46284621 	strtmi	r4, [r8], -r1, lsr #12
d0012080:	f92cf7fe 			; <UNDEFINED> instruction: 0xf92cf7fe
d0012084:	68e29b0e 	stmiavs	r2!, {r1, r2, r3, r8, r9, fp, ip, pc}^
d0012088:	9b0f930a 	blls	0xd03f6cb8
d001208c:	93069f0c 	movwls	r9, #28428	; 0x6f0c
d0012090:	f8dd9b13 			; <UNDEFINED> instruction: 0xf8dd9b13
d0012094:	9307b040 	movwls	fp, #28736	; 0x7040
d0012098:	f89d6863 			; <UNDEFINED> instruction: 0xf89d6863
d001209c:	429aa048 	addsmi	sl, sl, #72	; 0x48
d00120a0:	ad63f47f 	cfstrdge	mvd15, [r3, #-508]!	; 0xfffffe04
d00120a4:	e5f14634 	ldrb	r4, [r1, #1588]!	; 0x634
d00120a8:	4620900a 	strtmi	r9, [r0], -sl
d00120ac:	f8eef7fe 			; <UNDEFINED> instruction: 0xf8eef7fe
d00120b0:	0020f040 	eoreq	pc, r0, r0, asr #32
d00120b4:	2878990a 	ldmdacs	r8!, {r1, r3, r8, fp, ip, pc}^
d00120b8:	ae5bf43f 	mrcge	4, 2, APSR_nzcv, cr11, cr15, {1}
d00120bc:	e58e2708 	str	r2, [lr, #1800]	; 0x708
d00120c0:	f47f45c1 			; <UNDEFINED> instruction: 0xf47f45c1
d00120c4:	f1b9af6c 			; <UNDEFINED> instruction: 0xf1b9af6c
d00120c8:	d0030f2b 	andle	r0, r3, fp, lsr #30
d00120cc:	0f2df1b9 	svceq	0x002df1b9
d00120d0:	af71f47f 	svcge	0x0071f47f
d00120d4:	f2404620 	vmax.s8	d20, d0, d16
d00120d8:	f7fe1723 			; <UNDEFINED> instruction: 0xf7fe1723
d00120dc:	f1b8f8e0 			; <UNDEFINED> instruction: 0xf1b8f8e0
d00120e0:	bf180f2b 	svclt	0x00180f2b
d00120e4:	7792f44f 	ldrvc	pc, [r2, pc, asr #8]
d00120e8:	bf00e724 	svclt	0x0000e724
d00120ec:	fffffd4d 			; <UNDEFINED> instruction: 0xfffffd4d
d00120f0:	fffffd19 			; <UNDEFINED> instruction: 0xfffffd19
d00120f4:	fffffce9 			; <UNDEFINED> instruction: 0xfffffce9
d00120f8:	000112ae 	andeq	r1, r1, lr, lsr #5
d00120fc:	000112c6 	andeq	r1, r1, r6, asr #5
d0012100:	fffffbd5 			; <UNDEFINED> instruction: 0xfffffbd5
d0012104:	fffffb78 			; <UNDEFINED> instruction: 0xfffffb78
d0012108:	fffffb55 			; <UNDEFINED> instruction: 0xfffffb55
d001210c:	fffffb3e 			; <UNDEFINED> instruction: 0xfffffb3e
d0012110:	fffffb05 			; <UNDEFINED> instruction: 0xfffffb05
d0012114:	fffffac5 			; <UNDEFINED> instruction: 0xfffffac5
d0012118:	fffff938 			; <UNDEFINED> instruction: 0xfffff938
d001211c:	fffff94a 			; <UNDEFINED> instruction: 0xfffff94a
d0012120:	fffff971 			; <UNDEFINED> instruction: 0xfffff971
d0012124:	fffff94b 			; <UNDEFINED> instruction: 0xfffff94b
d0012128:	fffff7e0 			; <UNDEFINED> instruction: 0xfffff7e0

Disassembly of section .text.scan_directive:

d0012470 <.text.scan_directive>:
d0012470:	e92db082 	push	{r1, r7, ip, sp, pc}
d0012474:	ed2d4ff0 	vstr	FPSCR_nzcvqc, [sp, #-448]!	; 0xfffffe40
d0012478:	b09b8b02 	addslt	r8, fp, r2, lsl #22
d001247c:	ee08460c 	cfmadd32	mvax0, mvfx4, mvfx8, mvfx12
d0012480:	a9260a10 	stmdbge	r6!, {r4, r9, fp}
d0012484:	000ce881 	andeq	lr, ip, r1, lsl #17
d0012488:	9d299b2a 	vstmdbls	r9!, {d9-d29}
d001248c:	9b2d9308 	blls	0xd0b770b4
d0012490:	a0b0f89d 	umlalsge	pc, r0, sp, r8	; <UNPREDICTABLE>
d0012494:	68e39309 	stmiavs	r3!, {r0, r3, r8, r9, ip, pc}^
d0012498:	6963930f 	stmdbvs	r3!, {r0, r1, r2, r3, r8, r9, ip, pc}^
d001249c:	21009310 	tstcs	r0, r0, lsl r3
d00124a0:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d00124a4:	2820fef3 	stmdacs	r0!, {r0, r1, r4, r5, r6, r7, r9, sl, fp, ip, sp, lr, pc}
d00124a8:	2809d02a 	stmdacs	r9, {r1, r3, r5, ip, lr, pc}
d00124ac:	6827d028 	stmdavs	r7!, {r3, r5, ip, lr, pc}
d00124b0:	441f68e3 	ldrmi	r6, [pc], #-2275	; 0xd00124b8
d00124b4:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d00124b8:	fee8f7fd 	mcr2	7, 7, pc, cr8, cr13, {7}	; <UNPREDICTABLE>
d00124bc:	ffc7f7fd 			; <UNDEFINED> instruction: 0xffc7f7fd
d00124c0:	bb084681 	bllt	0xd0223ecc
d00124c4:	68e36822 	stmiavs	r3!, {r1, r5, fp, sp, lr}^
d00124c8:	1bd2441a 	blne	0xcf4a3538
d00124cc:	d11f2a07 	tstle	pc, r7, lsl #20
d00124d0:	1964f8df 	stmdbne	r4!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d00124d4:	920a4638 	andls	r4, sl, #56, 12	; 0x3800000
d00124d8:	f00f4479 			; <UNDEFINED> instruction: 0xf00f4479
d00124dc:	fab0f8b7 	blx	0xcec507c0
d00124e0:	9a0af680 	bls	0xd02cfee8
d00124e4:	f04f0976 			; <UNDEFINED> instruction: 0xf04f0976
d00124e8:	2a050b00 	bcs	0xd01550f0
d00124ec:	f8cd46d8 			; <UNDEFINED> instruction: 0xf8cd46d8
d00124f0:	f8cdb030 			; <UNDEFINED> instruction: 0xf8cdb030
d00124f4:	f8cdb028 			; <UNDEFINED> instruction: 0xf8cdb028
d00124f8:	d132b02c 	teqle	r2, ip, lsr #32
d00124fc:	bc8cf000 	stclt	0, cr15, [ip], {0}
d0012500:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0012504:	e7cafecc 	strb	pc, [sl, ip, asr #29]	; <UNPREDICTABLE>
d0012508:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d001250c:	e7d1fec8 	ldrb	pc, [r1, r8, asr #29]	; <UNPREDICTABLE>
d0012510:	f0402a06 			; <UNDEFINED> instruction: 0xf0402a06
d0012514:	f8df8465 			; <UNDEFINED> instruction: 0xf8df8465
d0012518:	46381924 	ldrtmi	r1, [r8], -r4, lsr #18
d001251c:	464e920a 	strbmi	r9, [lr], -sl, lsl #4
d0012520:	f00f4479 			; <UNDEFINED> instruction: 0xf00f4479
d0012524:	f8dff893 			; <UNDEFINED> instruction: 0xf8dff893
d0012528:	fab01918 	blx	0xcec18990
d001252c:	9a0af880 	bls	0xd02d0734
d0012530:	46384479 			; <UNDEFINED> instruction: 0x46384479
d0012534:	f88af00f 			; <UNDEFINED> instruction: 0xf88af00f
d0012538:	f380fab0 			; <UNDEFINED> instruction: 0xf380fab0
d001253c:	1904f8df 	stmdbne	r4, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d0012540:	095b4638 	ldmdbeq	fp, {r3, r4, r5, r9, sl, lr}^
d0012544:	44799a0a 	ldrbtmi	r9, [r9], #-2570	; 0xfffff5f6
d0012548:	1858ea4f 	ldmdane	r8, {r0, r1, r2, r3, r6, r9, fp, sp, lr, pc}^
d001254c:	f00f930b 			; <UNDEFINED> instruction: 0xf00f930b
d0012550:	fab0f87d 	blx	0xcec5074c
d0012554:	f8cdfb80 			; <UNDEFINED> instruction: 0xf8cdfb80
d0012558:	f8cd9030 			; <UNDEFINED> instruction: 0xf8cd9030
d001255c:	ea4f9028 	b	0xd13f6604
d0012560:	23001b5b 	movwcs	r1, #2907	; 0xb5b
d0012564:	930d930e 	movwls	r9, #54030	; 0xd30e
d0012568:	2a02e03a 	bcs	0xd00ca658
d001256c:	2a04d022 	bcs	0xd01465fc
d0012570:	d1b8464e 			; <UNDEFINED> instruction: 0xd1b8464e
d0012574:	18d0f8df 	ldmne	r0, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d0012578:	920a4638 	andls	r4, sl, #56, 12	; 0x3800000
d001257c:	447946cb 	ldrbtmi	r4, [r9], #-1739	; 0xfffff935
d0012580:	f00f46c8 			; <UNDEFINED> instruction: 0xf00f46c8
d0012584:	fab0f863 	blx	0xcec50718
d0012588:	f8dff380 			; <UNDEFINED> instruction: 0xf8dff380
d001258c:	463818c0 	ldrtmi	r1, [r8], -r0, asr #17
d0012590:	9a0a095b 	bls	0xd0294b04
d0012594:	930e4479 	movwls	r4, #58489	; 0xe479
d0012598:	f858f00f 			; <UNDEFINED> instruction: 0xf858f00f
d001259c:	f380fab0 			; <UNDEFINED> instruction: 0xf380fab0
d00125a0:	9034f8cd 	eorsls	pc, r4, sp, asr #17
d00125a4:	9030f8cd 	eorsls	pc, r0, sp, asr #17
d00125a8:	f8cd095b 			; <UNDEFINED> instruction: 0xf8cd095b
d00125ac:	f8cd9028 			; <UNDEFINED> instruction: 0xf8cd9028
d00125b0:	e015902c 	ands	r9, r5, ip, lsr #32
d00125b4:	1898f8df 	ldmne	r8, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d00125b8:	46cb4638 			; <UNDEFINED> instruction: 0x46cb4638
d00125bc:	447946c8 	ldrbtmi	r4, [r9], #-1736	; 0xfffff938
d00125c0:	f00f464e 			; <UNDEFINED> instruction: 0xf00f464e
d00125c4:	fab0f843 	blx	0xcec506d8
d00125c8:	f8cdf380 			; <UNDEFINED> instruction: 0xf8cdf380
d00125cc:	095b9038 	ldmdbeq	fp, {r3, r4, r5, ip, pc}^
d00125d0:	9030f8cd 	eorsls	pc, r0, sp, asr #17
d00125d4:	9028f8cd 	eorls	pc, r8, sp, asr #17
d00125d8:	464b930d 	strbmi	r9, [fp], -sp, lsl #6
d00125dc:	902cf8cd 	eorls	pc, ip, sp, asr #17
d00125e0:	0708ea56 	smlsdeq	r8, r6, sl, lr
d00125e4:	815cf000 	cmphi	ip, r0	; <UNPREDICTABLE>
d00125e8:	93114620 	tstls	r1, #32, 12	; 0x2000000
d00125ec:	fe98f7fd 	mrc2	7, 4, pc, cr8, cr13, {7}
d00125f0:	28009b11 	stmdacs	r0, {r0, r4, r8, r9, fp, ip, pc}
d00125f4:	8154f000 	cmphi	r4, r0	; <UNPREDICTABLE>
d00125f8:	f10d9b0f 			; <UNDEFINED> instruction: 0xf10d9b0f
d00125fc:	ae120c98 	mrcge	12, 0, r0, cr2, cr8, {4}
d0012600:	9b1060e3 	blls	0xd042a994
d0012604:	e8bc6163 	ldm	ip!, {r0, r1, r5, r6, r8, sp, lr}
d0012608:	c60f000f 	strgt	r0, [pc], -pc
d001260c:	000fe89c 	muleq	pc, ip, r8	; <UNPREDICTABLE>
d0012610:	000fe886 	andeq	lr, pc, r6, lsl #17
d0012614:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d0012618:	fe38f7fd 	mrc2	7, 1, pc, cr8, cr13, {7}
d001261c:	d0332820 	eorsle	r2, r3, r0, lsr #16
d0012620:	d0312809 	eorsle	r2, r1, r9, lsl #16
d0012624:	68e36826 	stmiavs	r3!, {r1, r2, r5, fp, sp, lr}^
d0012628:	2100441e 	tstcs	r0, lr, lsl r4
d001262c:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0012630:	f7fdfe2d 			; <UNDEFINED> instruction: 0xf7fdfe2d
d0012634:	bb58ff0c 	bllt	0xd165226c
d0012638:	68e36822 	stmiavs	r3!, {r1, r5, fp, sp, lr}^
d001263c:	1b92441a 	blne	0xce4a36ac
d0012640:	d1292a07 			; <UNDEFINED> instruction: 0xd1292a07
d0012644:	180cf8df 	stmdane	ip, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d0012648:	44794630 	ldrbtmi	r4, [r9], #-1584	; 0xfffff9d0
d001264c:	fffef00e 			; <UNDEFINED> instruction: 0xfffef00e
d0012650:	b3584607 	cmplt	r8, #7340032	; 0x700000
d0012654:	b94b6da3 	stmdblt	fp, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0012658:	37fcf8df 	ubfxcc	pc, pc, #17, #29
d001265c:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0012660:	9b083516 	blls	0xd021fac0
d0012664:	3a18e9c4 	bcc	0xd064cd7c
d0012668:	66a39b09 	strtvs	r9, [r3], r9, lsl #22
d001266c:	ee184621 	cfmsub32	mvax1, mvfx4, mvfx8, mvfx1
d0012670:	f7fd0a10 			; <UNDEFINED> instruction: 0xf7fd0a10
d0012674:	ee18fe33 	mrc	14, 0, APSR_nzcv, cr8, cr3, {1}
d0012678:	b01b0a10 	andslt	r0, fp, r0, lsl sl
d001267c:	8b02ecbd 	blhi	0xd00cd978
d0012680:	4ff0e8bd 	svcmi	0x00f0e8bd
d0012684:	4770b002 	ldrbmi	fp, [r0, -r2]!
d0012688:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d001268c:	e7c1fe08 	strb	pc, [r1, r8, lsl #28]	; <UNPREDICTABLE>
d0012690:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0012694:	e7c8fe04 	strb	pc, [r8, r4, lsl #28]	; <UNPREDICTABLE>
d0012698:	d1db2a06 	bicsle	r2, fp, r6, lsl #20
d001269c:	17bcf8df 	sbfxne	pc, pc, #17, #29
d00126a0:	44794630 	ldrbtmi	r4, [r9], #-1584	; 0xfffff9d0
d00126a4:	ffd2f00e 			; <UNDEFINED> instruction: 0xffd2f00e
d00126a8:	d1d32800 	bicsle	r2, r3, r0, lsl #16
d00126ac:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d00126b0:	fdecf7fd 	stc2l	7, cr15, [ip, #1012]!	; 0x3f4
d00126b4:	d0162820 	andsle	r2, r6, r0, lsr #16
d00126b8:	d0142809 	andsle	r2, r4, r9, lsl #16
d00126bc:	d0552f00 	subsle	r2, r5, r0, lsl #30
d00126c0:	68e76826 	stmiavs	r7!, {r1, r2, r5, fp, sp, lr}^
d00126c4:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d00126c8:	fde0f7fd 	stc2l	7, cr15, [r0, #1012]!	; 0x3f4
d00126cc:	febff7fd 	mrc2	7, 5, pc, cr15, cr13, {7}
d00126d0:	6fa3b968 	svcvs	0x00a3b968
d00126d4:	da0e2b00 	ble	0xd039d2dc
d00126d8:	2b006da3 	blcs	0xd002dd6c
d00126dc:	f8dfd1c6 			; <UNDEFINED> instruction: 0xf8dfd1c6
d00126e0:	447b3780 	ldrbtmi	r3, [fp], #-1920	; 0xfffff880
d00126e4:	4620e7bb 			; <UNDEFINED> instruction: 0x4620e7bb
d00126e8:	fdd9f7fd 	ldc2l	7, cr15, [r9, #1012]	; 0x3f4
d00126ec:	4620e7de 			; <UNDEFINED> instruction: 0x4620e7de
d00126f0:	fdd5f7fd 	ldc2l	7, cr15, [r5, #1012]	; 0x3f4
d00126f4:	6822e7e6 	stmdavs	r2!, {r1, r2, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d00126f8:	68e319f0 	stmiavs	r3!, {r4, r5, r6, r7, r8, fp, ip}^
d00126fc:	1a12441a 	bne	0xd04a376c
d0012700:	d1e92a04 	mvnle	r2, r4, lsl #20
d0012704:	175cf8df 	smmlsne	ip, pc, r8, pc	; <UNPREDICTABLE>
d0012708:	f00e4479 			; <UNDEFINED> instruction: 0xf00e4479
d001270c:	2800ff9f 	stmdacs	r0, {r0, r1, r2, r3, r4, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0012710:	6fa3d1e2 	svcvs	0x00a3d1e2
d0012714:	72a6f44f 	adcvc	pc, r6, #1325400064	; 0x4f000000
d0012718:	4303fb02 	movwmi	pc, #15106	; 0x3b02	; <UNPREDICTABLE>
d001271c:	f8832201 			; <UNDEFINED> instruction: 0xf8832201
d0012720:	2100230a 	tstcs	r0, sl, lsl #6
d0012724:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0012728:	2820fdb1 	stmdacs	r0!, {r0, r4, r5, r7, r8, sl, fp, ip, sp, lr, pc}
d001272c:	80b4f000 	adcshi	pc, r4, r0
d0012730:	f0002809 			; <UNDEFINED> instruction: 0xf0002809
d0012734:	68e280b1 	stmiavs	r2!, {r0, r4, r5, r7, pc}^
d0012738:	429a6863 	addsmi	r6, sl, #6488064	; 0x630000
d001273c:	80a6f000 	adchi	pc, r6, r0
d0012740:	f000280d 			; <UNDEFINED> instruction: 0xf000280d
d0012744:	280a80a3 	stmdacs	sl, {r0, r1, r5, r7, pc}
d0012748:	80a0f000 	adchi	pc, r0, r0
d001274c:	d106282f 	tstle	r6, pc, lsr #16
d0012750:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d0012754:	fd9af7fd 	ldc2	7, cr15, [sl, #1012]	; 0x3f4
d0012758:	f000282f 			; <UNDEFINED> instruction: 0xf000282f
d001275c:	6da38097 	stcvs	0, cr8, [r3, #604]!	; 0x25c
d0012760:	d1832b00 	orrle	r2, r3, r0, lsl #22
d0012764:	3700f8df 			; <UNDEFINED> instruction: 0x3700f8df
d0012768:	e778447b 			; <UNDEFINED> instruction: 0xe778447b
d001276c:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0012770:	2822fd96 	stmdacs	r2!, {r1, r2, r4, r7, r8, sl, fp, ip, sp, lr, pc}
d0012774:	d0094680 	andle	r4, r9, r0, lsl #13
d0012778:	d01c283c 	andsle	r2, ip, ip, lsr r8
d001277c:	2b006da3 	blcs	0xd002de10
d0012780:	af74f47f 	svcge	0x0074f47f
d0012784:	36e4f8df 	usatcc	pc, #4, pc, asr #17	; <UNPREDICTABLE>
d0012788:	e768447b 			; <UNDEFINED> instruction: 0xe768447b
d001278c:	68264681 	stmdavs	r6!, {r0, r7, r9, sl, lr}
d0012790:	210068e7 	smlattcs	r0, r7, r8, r6
d0012794:	68e24620 	stmiavs	r2!, {r5, r9, sl, lr}^
d0012798:	fd78f7fd 	ldc2l	7, cr15, [r8, #-1012]!	; 0xfffffc0c
d001279c:	429a6863 	addsmi	r6, sl, #6488064	; 0x630000
d00127a0:	4581d30c 	strmi	sp, [r1, #780]	; 0x30c
d00127a4:	6da3d014 	stcvs	0, cr13, [r3, #80]!	; 0x50
d00127a8:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d00127ac:	f8dfaf5f 			; <UNDEFINED> instruction: 0xf8dfaf5f
d00127b0:	447b36c0 	ldrbtmi	r3, [fp], #-1728	; 0xfffff940
d00127b4:	f04fe753 			; <UNDEFINED> instruction: 0xf04fe753
d00127b8:	e7e8093e 			; <UNDEFINED> instruction: 0xe7e8093e
d00127bc:	d0074581 	andle	r4, r7, r1, lsl #11
d00127c0:	d0f0280d 	rscsle	r2, r0, sp, lsl #16
d00127c4:	d0ee280a 	rscle	r2, lr, sl, lsl #16
d00127c8:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d00127cc:	e7e0fd68 	strb	pc, [r0, r8, ror #26]!	; <UNPREDICTABLE>
d00127d0:	68264437 	stmdavs	r6!, {r0, r1, r2, r4, r5, sl, lr}
d00127d4:	1bf64416 	blne	0xcfda3834
d00127d8:	4620d0e5 	strtmi	sp, [r0], -r5, ror #1
d00127dc:	fd5ff7fd 	ldc2l	7, cr15, [pc, #-1012]	; 0xd00123f0
d00127e0:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d00127e4:	fd52f7fd 	ldc2l	7, cr15, [r2, #-1012]	; 0xfffffc0c
d00127e8:	d0f62820 	rscsle	r2, r6, r0, lsr #16
d00127ec:	d0f42809 	rscsle	r2, r4, r9, lsl #16
d00127f0:	686368e2 	stmdavs	r3!, {r1, r5, r6, r7, fp, sp, lr}^
d00127f4:	d013429a 	mulsle	r3, sl, r2
d00127f8:	d011280d 	andsle	r2, r1, sp, lsl #16
d00127fc:	d00f280a 	andle	r2, pc, sl, lsl #16
d0012800:	d105282f 	tstle	r5, pc, lsr #16
d0012804:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d0012808:	fd40f7fd 	stc2l	7, cr15, [r0, #-1012]	; 0xfffffc0c
d001280c:	d007282f 	andle	r2, r7, pc, lsr #16
d0012810:	2b006da3 	blcs	0xd002dea4
d0012814:	af2af47f 	svcge	0x002af47f
d0012818:	3658f8df 			; <UNDEFINED> instruction: 0x3658f8df
d001281c:	e71e447b 			; <UNDEFINED> instruction: 0xe71e447b
d0012820:	d11b2e06 	tstle	fp, r6, lsl #28
d0012824:	1650f8df 			; <UNDEFINED> instruction: 0x1650f8df
d0012828:	46384632 			; <UNDEFINED> instruction: 0x46384632
d001282c:	f00e4479 			; <UNDEFINED> instruction: 0xf00e4479
d0012830:	b998ff0d 	ldmiblt	r8, {r0, r2, r3, r8, r9, sl, fp, ip, sp, lr, pc}
d0012834:	ee189b08 	vnmls.f64	d9, d8, d8
d0012838:	95154a10 	ldrls	r4, [r5, #-2576]	; 0xfffff5f0
d001283c:	9316ad12 	tstls	r6, #1152	; 0x480
d0012840:	7383f44f 	orrvc	pc, r3, #1325400064	; 0x4f000000
d0012844:	a060f88d 	rsbge	pc, r0, sp, lsl #17
d0012848:	9b099317 	blls	0xd02774ac
d001284c:	cd0f9319 	stcgt	3, cr9, [pc, #-100]	; 0xd00127f0
d0012850:	e895c40f 	ldm	r5, {r0, r1, r2, r3, sl, lr, pc}
d0012854:	e884000f 	stm	r4, {r0, r1, r2, r3}
d0012858:	e70c000f 	str	r0, [ip, -pc]
d001285c:	0f22f1b8 	svceq	0x0022f1b8
d0012860:	6da3d007 	stcvs	0, cr13, [r3, #28]!
d0012864:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0012868:	f8dfaf01 			; <UNDEFINED> instruction: 0xf8dfaf01
d001286c:	447b3610 	ldrbtmi	r3, [fp], #-1552	; 0xfffff9f0
d0012870:	9b09e6f5 	blls	0xd028c44c
d0012874:	9a084629 	bls	0xd0224120
d0012878:	93004620 	movwls	r4, #1568	; 0x620
d001287c:	96024653 			; <UNDEFINED> instruction: 0x96024653
d0012880:	f7fe9701 			; <UNDEFINED> instruction: 0xf7fe9701
d0012884:	2800fda5 	stmdacs	r0, {r0, r2, r5, r7, r8, sl, fp, ip, sp, lr, pc}
d0012888:	aef0f43f 	mrcge	4, 7, APSR_nzcv, cr0, cr15, {1}
d001288c:	ee184621 	cfmsub32	mvax1, mvfx4, mvfx8, mvfx1
d0012890:	f7ff0a10 			; <UNDEFINED> instruction: 0xf7ff0a10
d0012894:	e6eef88b 	strbt	pc, [lr], fp, lsl #17	; <UNPREDICTABLE>
d0012898:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d001289c:	e740fd00 	strb	pc, [r0, -r0, lsl #26]	; <UNPREDICTABLE>
d00128a0:	0206ea49 	andeq	lr, r6, #299008	; 0x49000
d00128a4:	ea42990b 	b	0xd10b8cd8
d00128a8:	430a0208 	movwmi	r0, #41480	; 0xa208
d00128ac:	430a990a 	movwmi	r9, #43274	; 0xa90a
d00128b0:	430a990c 	movwmi	r9, #43276	; 0xa90c
d00128b4:	ea42990d 	b	0xd10b8cf0
d00128b8:	430a020b 	movwmi	r0, #41483	; 0xa20b
d00128bc:	430a990e 	movwmi	r9, #43278	; 0xa90e
d00128c0:	d123431a 			; <UNDEFINED> instruction: 0xd123431a
d00128c4:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d00128c8:	b158fd2b 	cmplt	r8, fp, lsr #26	; <UNPREDICTABLE>
d00128cc:	b94b6da3 	stmdblt	fp, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d00128d0:	35acf8df 	strcc	pc, [ip, #2271]!	; 0x8df
d00128d4:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d00128d8:	9b083516 	blls	0xd021fd38
d00128dc:	3a18e9c4 	bcc	0xd064cff4
d00128e0:	66a39b09 	strtvs	r9, [r3], r9, lsl #22
d00128e4:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d00128e8:	2220fd38 	eorcs	pc, r0, #56, 26	; 0xe00
d00128ec:	ee182100 	mufe	f2, f0, f0
d00128f0:	f00e0a10 			; <UNDEFINED> instruction: 0xf00e0a10
d00128f4:	f44ffe8d 			; <UNDEFINED> instruction: 0xf44ffe8d
d00128f8:	ee187397 	mrc	3, 0, r7, cr8, cr7, {4}
d00128fc:	61532a10 	cmpvs	r3, r0, lsl sl
d0012900:	4620e6b9 			; <UNDEFINED> instruction: 0x4620e6b9
d0012904:	f7fd930f 			; <UNDEFINED> instruction: 0xf7fd930f
d0012908:	9b0ffcca 	blls	0xd0411c38
d001290c:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d0012910:	f7fd930f 			; <UNDEFINED> instruction: 0xf7fd930f
d0012914:	2820fcbb 	stmdacs	r0!, {r0, r1, r3, r4, r5, r7, sl, fp, ip, sp, lr, pc}
d0012918:	d0f29b0f 	rscsle	r9, r2, pc, lsl #22
d001291c:	d0f02809 	rscsle	r2, r0, r9, lsl #16
d0012920:	46209311 			; <UNDEFINED> instruction: 0x46209311
d0012924:	930f6823 	movwls	r6, #63523	; 0xf823
d0012928:	931068e3 	tstls	r0, #14876672	; 0xe30000
d001292c:	9b0f9a10 	blls	0xd03f9174
d0012930:	f7fd189f 			; <UNDEFINED> instruction: 0xf7fd189f
d0012934:	6821fd12 	stmdavs	r1!, {r1, r4, r8, sl, fp, ip, sp, lr, pc}
d0012938:	46bc68e2 	ldrtmi	r6, [ip], r2, ror #17
d001293c:	44119b11 	ldrmi	r9, [r1], #-2833	; 0xfffff4ef
d0012940:	0201f10c 	andeq	pc, r1, #12, 2
d0012944:	d301428a 	movwle	r4, #4746	; 0x128a
d0012948:	e033468c 	eors	r4, r3, ip, lsl #13
d001294c:	0c01f812 	stceq	8, cr15, [r1], {18}
d0012950:	d15a282f 	cmple	sl, pc, lsr #16
d0012954:	282f7810 	stmdacs	pc!, {r4, fp, ip, sp, lr}	; <UNPREDICTABLE>
d0012958:	282ad02c 	stmdacs	sl!, {r2, r3, r5, ip, lr, pc}
d001295c:	f10cd155 			; <UNDEFINED> instruction: 0xf10cd155
d0012960:	1c500202 	lfmne	f0, 2, [r0], {2}
d0012964:	d2174288 	andsle	r4, r7, #136, 4	; 0x80000008
d0012968:	6c01f810 	stcvs	8, cr15, [r1], {16}
d001296c:	d1112e2a 	tstle	r1, sl, lsr #28
d0012970:	2e2f7806 	cdpcs	8, 2, cr7, cr15, cr6, {0}
d0012974:	3202d10e 	andcc	sp, r2, #-2147483645	; 0x80000003
d0012978:	d21a428a 	andsle	r4, sl, #-1610612728	; 0xa0000008
d001297c:	0b01f812 	bleq	0xd00909cc
d0012980:	d0f92820 	rscsle	r2, r9, r0, lsr #16
d0012984:	d0f72809 	rscsle	r2, r7, r9, lsl #16
d0012988:	b99a6da2 	ldmiblt	sl, {r1, r5, r7, r8, sl, fp, sp, lr}
d001298c:	24f4f8df 	ldrbtcs	pc, [r4], #2271	; 0x8df	; <UNPREDICTABLE>
d0012990:	e006447a 	and	r4, r6, sl, ror r4
d0012994:	e7e44602 	strb	r4, [r4, r2, lsl #12]!
d0012998:	b95a6da2 	ldmdblt	sl, {r1, r5, r7, r8, sl, fp, sp, lr}^
d001299c:	24e8f8df 	strbtcs	pc, [r8], #2271	; 0x8df	; <UNPREDICTABLE>
d00129a0:	e9c4447a 	stmib	r4, {r1, r3, r4, r5, r6, sl, lr}^
d00129a4:	9a082516 	bls	0xd021be04
d00129a8:	2a18e9c4 	bcs	0xd064d0c0
d00129ac:	66a29a09 	strtvs	r9, [r2], r9, lsl #20
d00129b0:	d1e9e000 	mvnle	lr, r0
d00129b4:	42be4666 	adcsmi	r4, lr, #106954752	; 0x6600000
d00129b8:	f816d906 			; <UNDEFINED> instruction: 0xf816d906
d00129bc:	1e712c01 	cdpne	12, 7, cr2, cr1, cr1, {0}
d00129c0:	d0242a20 	eorle	r2, r4, r0, lsr #20
d00129c4:	d0222a09 	eorle	r2, r2, r9, lsl #20
d00129c8:	93114620 	tstls	r1, #32, 12	; 0x2000000
d00129cc:	fca8f7fd 	stc2	7, cr15, [r8], #1012	; 0x3f4
d00129d0:	46809b0c 	strmi	r9, [r0], ip, lsl #22
d00129d4:	000bea43 	andeq	lr, fp, r3, asr #20
d00129d8:	43039b0d 	movwmi	r9, #15117	; 0x3b0d
d00129dc:	f0009b11 			; <UNDEFINED> instruction: 0xf0009b11
d00129e0:	f24d8090 	vqadd.s8	d24, d29, d0
d00129e4:	58e3030c 	stmiapl	r3!, {r2, r3, r8, r9}^
d00129e8:	d1122b20 	tstle	r2, r0, lsr #22
d00129ec:	2b006da3 	blcs	0xd002e080
d00129f0:	af7bf47f 	svcge	0x007bf47f
d00129f4:	3494f8df 	ldrcc	pc, [r4], #2271	; 0x8df
d00129f8:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d00129fc:	9b083516 	blls	0xd021fe5c
d0012a00:	3a18e9c4 	bcc	0xd064d118
d0012a04:	66a39b09 	strtvs	r9, [r3], r9, lsl #22
d0012a08:	4694e76f 	ldrmi	lr, [r4], pc, ror #14
d0012a0c:	460ee798 			; <UNDEFINED> instruction: 0x460ee798
d0012a10:	f1b8e7d1 			; <UNDEFINED> instruction: 0xf1b8e7d1
d0012a14:	d0720f00 	rsbsle	r0, r2, r0, lsl #30
d0012a18:	d0542800 	subsle	r2, r4, r0, lsl #16
d0012a1c:	d00542be 			; <UNDEFINED> instruction: 0xd00542be
d0012a20:	9a109b0f 	bls	0xd0439664
d0012a24:	f7fd5c98 			; <UNDEFINED> instruction: 0xf7fd5c98
d0012a28:	b958fd12 	ldmdblt	r8, {r1, r4, r8, sl, fp, ip, sp, lr, pc}^
d0012a2c:	b94b6da3 	stmdblt	fp, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0012a30:	345cf8df 	ldrbcc	pc, [ip], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d0012a34:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0012a38:	9b083516 	blls	0xd021fe98
d0012a3c:	3a18e9c4 	bcc	0xd064d154
d0012a40:	66a39b09 	strtvs	r9, [r3], r9, lsl #22
d0012a44:	454e46b9 	strbmi	r4, [lr, #-1721]	; 0xfffff947
d0012a48:	d917464a 	ldmdble	r7, {r1, r3, r6, r9, sl, lr}
d0012a4c:	f1097811 			; <UNDEFINED> instruction: 0xf1097811
d0012a50:	46080901 	strmi	r0, [r8], -r1, lsl #18
d0012a54:	fcfbf7fd 	ldc2l	7, cr15, [fp], #1012	; 0x3f4
d0012a58:	d1f42800 	mvnsle	r2, r0, lsl #16
d0012a5c:	29093930 	stmdbcs	r9, {r4, r5, r8, fp, ip, sp}
d0012a60:	6da3d9f1 			; <UNDEFINED> instruction: 0x6da3d9f1
d0012a64:	f8dfb95b 			; <UNDEFINED> instruction: 0xf8dfb95b
d0012a68:	447b342c 	ldrbtmi	r3, [fp], #-1068	; 0xfffffbd4
d0012a6c:	3516e9c4 	ldrcc	lr, [r6, #-2500]	; 0xfffff63c
d0012a70:	e9c49b08 	stmib	r4, {r3, r8, r9, fp, ip, pc}^
d0012a74:	9b093a18 	blls	0xd02612dc
d0012a78:	e00066a3 	and	r6, r0, r3, lsr #13
d0012a7c:	1bd2d1f1 	blne	0xcf4c7248
d0012a80:	46204639 			; <UNDEFINED> instruction: 0x46204639
d0012a84:	fcc1f7fd 	stc2l	7, cr15, [r1], {253}	; 0xfd
d0012a88:	0f00f1bb 	svceq	0x0000f1bb
d0012a8c:	43c0d100 	bicmi	sp, r0, #0, 2
d0012a90:	f24d0fc0 	vmax.f32	q8, <illegal reg q14.5>, q0
d0012a94:	f1b8030c 			; <UNDEFINED> instruction: 0xf1b8030c
d0012a98:	58e10f00 	stmiapl	r1!, {r8, r9, sl, fp}^
d0012a9c:	2000bf08 	andcs	fp, r0, r8, lsl #30
d0012aa0:	50e21c4a 	rscpl	r1, r2, sl, asr #24
d0012aa4:	0481eb04 	streq	lr, [r1], #2820	; 0xb04
d0012aa8:	738cf64c 	orrvc	pc, ip, #76, 12	; 0x4c00000
d0012aac:	f8042200 			; <UNDEFINED> instruction: 0xf8042200
d0012ab0:	f64c8003 			; <UNDEFINED> instruction: 0xf64c8003
d0012ab4:	54e0738d 	strbtpl	r7, [r0], #909	; 0x38d
d0012ab8:	738ef64c 	orrvc	pc, lr, #76, 12	; 0x4c00000
d0012abc:	f64c54e0 			; <UNDEFINED> instruction: 0xf64c54e0
d0012ac0:	54e2738f 	strbtpl	r7, [r2], #911	; 0x38f
d0012ac4:	2200e711 	andcs	lr, r0, #4456448	; 0x440000
d0012ac8:	96062300 	strls	r2, [r6], -r0, lsl #6
d0012acc:	9705ae29 	strls	sl, [r5, -r9, lsr #28]
d0012ad0:	e9cd466d 	stmib	sp, {r0, r2, r3, r5, r6, r9, sl, lr}^
d0012ad4:	ab122312 	blge	0xd049b724
d0012ad8:	ce0f9307 	cdpgt	3, 0, cr9, cr15, cr7, {0}
d0012adc:	6833c50f 	ldmdavs	r3!, {r0, r1, r2, r3, r8, sl, lr, pc}
d0012ae0:	602b4620 	eorvs	r4, fp, r0, lsr #12
d0012ae4:	cb0eab26 	blgt	0xd03bd784
d0012ae8:	fb62f7fe 	blx	0xd18d0aea
d0012aec:	d0d02800 	sbcsle	r2, r0, r0, lsl #16
d0012af0:	2312e9dd 	tstcs	r2, #3620864	; 0x374000
d0012af4:	bf144313 	svclt	0x00144313
d0012af8:	20002001 	andcs	r2, r0, r1
d0012afc:	4640e7c9 	strbmi	lr, [r0], -r9, asr #15
d0012b00:	9a0ee7c7 	bls	0xd03cca24
d0012b04:	0002ea49 	andeq	lr, r2, r9, asr #20
d0012b08:	0203ea50 	andeq	lr, r3, #80, 20	; 0x50000
d0012b0c:	80a2f000 	adchi	pc, r2, r0
d0012b10:	21fcf8d4 	ldrsbcs	pc, [ip, #132]!	; 0x84	; <UNPREDICTABLE>
d0012b14:	eb04b112 	bl	0xd013ef64
d0012b18:	6f921242 	svcvs	0x00921242
d0012b1c:	010cf24d 	tsteq	ip, sp, asr #4	; <UNPREDICTABLE>
d0012b20:	42915861 	addsmi	r5, r1, #6356992	; 0x610000
d0012b24:	6da3d806 	stcvs	8, cr13, [r3, #24]!
d0012b28:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0012b2c:	4bdaaede 	blmi	0xcf6be6ac
d0012b30:	e762447b 			; <UNDEFINED> instruction: 0xe762447b
d0012b34:	f1b91e4a 			; <UNDEFINED> instruction: 0xf1b91e4a
d0012b38:	d0100f00 	andsle	r0, r0, r0, lsl #30
d0012b3c:	d00a42be 			; <UNDEFINED> instruction: 0xd00a42be
d0012b40:	b9436da3 	stmdblt	r3, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0012b44:	447b4bd5 	ldrbtmi	r4, [fp], #-3029	; 0xfffff42b
d0012b48:	3516e9c4 	ldrcc	lr, [r6, #-2500]	; 0xfffff63c
d0012b4c:	e9c49b08 	stmib	r4, {r3, r8, r9, fp, ip, pc}^
d0012b50:	9b093a18 	blls	0xd02613b8
d0012b54:	f24d66a3 	vmax.s8	d22, d29, d19
d0012b58:	50e2030c 	rscpl	r0, r2, ip, lsl #6
d0012b5c:	ea4fe6c5 	b	0xd140c678
d0012b60:	b3630881 	cmnlt	r3, #8454144	; 0x810000
d0012b64:	d10642be 			; <UNDEFINED> instruction: 0xd10642be
d0012b68:	534ff502 	movtpl	pc, #62722	; 0xf502	; <UNPREDICTABLE>
d0012b6c:	eb043322 	bl	0xd011f7fc
d0012b70:	79db0383 	ldmibvc	fp, {r0, r1, r7, r8, r9}^
d0012b74:	6da3b153 	stfvsd	f3, [r3, #332]!	; 0x14c
d0012b78:	4bc9b943 	blmi	0xcf28108c
d0012b7c:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0012b80:	9b083516 	blls	0xd021ffe0
d0012b84:	3a18e9c4 	bcc	0xd064d29c
d0012b88:	66a39b09 	strtvs	r9, [r3], r9, lsl #22
d0012b8c:	f64c4444 			; <UNDEFINED> instruction: 0xf64c4444
d0012b90:	5ce37388 	stclpl	3, cr7, [r3], #544	; 0x220
d0012b94:	f64cb13b 			; <UNDEFINED> instruction: 0xf64cb13b
d0012b98:	f814738a 			; <UNDEFINED> instruction: 0xf814738a
d0012b9c:	fab99003 	blx	0xcee76bb0
d0012ba0:	ea4ff989 	b	0xd14111cc
d0012ba4:	f64c1959 			; <UNDEFINED> instruction: 0xf64c1959
d0012ba8:	f64c7389 			; <UNDEFINED> instruction: 0xf64c7389
d0012bac:	f804728a 			; <UNDEFINED> instruction: 0xf804728a
d0012bb0:	23019003 	movwcs	r9, #4099	; 0x1003
d0012bb4:	f64c54a3 			; <UNDEFINED> instruction: 0xf64c54a3
d0012bb8:	54a3728b 	strtpl	r7, [r3], #651	; 0x28b
d0012bbc:	44a0e695 	strtmi	lr, [r0], #1685	; 0x695
d0012bc0:	738bf64c 	orrvc	pc, fp, #76, 12	; 0x4c00000
d0012bc4:	3003f818 	andcc	pc, r3, r8, lsl r8	; <UNPREDICTABLE>
d0012bc8:	6da3b153 	stfvsd	f3, [r3, #332]!	; 0x14c
d0012bcc:	4bb5b943 	blmi	0xced810e0
d0012bd0:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0012bd4:	9b083516 	blls	0xd0220034
d0012bd8:	3a18e9c4 	bcc	0xd064d2f0
d0012bdc:	66a39b09 	strtvs	r9, [r3], r9, lsl #22
d0012be0:	22002300 	andcs	r2, r0, #0, 6
d0012be4:	2312e9cd 	tstcs	r2, #3358720	; 0x334000
d0012be8:	7388f64c 	orrvc	pc, r8, #76, 12	; 0x4c00000
d0012bec:	3003f818 	andcc	pc, r3, r8, lsl r8	; <UNPREDICTABLE>
d0012bf0:	f64cb923 			; <UNDEFINED> instruction: 0xf64cb923
d0012bf4:	f8087289 			; <UNDEFINED> instruction: 0xf8087289
d0012bf8:	e6763002 	ldrbt	r3, [r6], -r2
d0012bfc:	798af64c 	stmibvc	sl, {r2, r3, r6, r9, sl, ip, sp, lr, pc}
d0012c00:	3009f818 	andcc	pc, r9, r8, lsl r8	; <UNPREDICTABLE>
d0012c04:	f64cb12b 			; <UNDEFINED> instruction: 0xf64cb12b
d0012c08:	22007389 	andcs	r7, r0, #603979778	; 0x24000002
d0012c0c:	2003f808 	andcs	pc, r3, r8, lsl #16
d0012c10:	9606e66b 	strls	lr, [r6], -fp, ror #12
d0012c14:	ae29ab12 	vmovge.32	d9[1], sl
d0012c18:	93079705 	movwls	r9, #30469	; 0x7705
d0012c1c:	ce0f466d 	cfmadd32gt	mvax3, mvfx4, mvfx15, mvfx13
d0012c20:	6833c50f 	ldmdavs	r3!, {r0, r1, r2, r3, r8, sl, lr, pc}
d0012c24:	602b4620 	eorvs	r4, fp, r0, lsr #12
d0012c28:	cb0eab26 	blgt	0xd03bd8c8
d0012c2c:	fac0f7fe 	blx	0xcf050c2c
d0012c30:	2312e9dd 	tstcs	r2, #3620864	; 0x374000
d0012c34:	0103ea52 	tsteq	r3, r2, asr sl
d0012c38:	7189f64c 	orrvc	pc, r9, ip, asr #12
d0012c3c:	2001bf14 	andcs	fp, r1, r4, lsl pc
d0012c40:	43132000 	tstmi	r3, #0
d0012c44:	0001f808 	andeq	pc, r1, r8, lsl #16
d0012c48:	ae4ff43f 	mcrge	4, 2, pc, cr15, cr15, {1}	; <UNPREDICTABLE>
d0012c4c:	f8082301 			; <UNDEFINED> instruction: 0xf8082301
d0012c50:	e64a3009 	strb	r3, [sl], -r9
d0012c54:	0f00f1b8 	svceq	0x0000f1b8
d0012c58:	ae47f43f 	mcrge	4, 2, pc, cr7, cr15, {1}	; <UNPREDICTABLE>
d0012c5c:	9a0a9b0b 	bls	0xd02b9890
d0012c60:	f43f4313 			; <UNDEFINED> instruction: 0xf43f4313
d0012c64:	42beae42 	adcsmi	sl, lr, #1056	; 0x420
d0012c68:	9b0fd023 	blls	0xd0406cfc
d0012c6c:	5c989a10 	vldmiapl	r8, {s18-s33}
d0012c70:	fbedf7fd 	blx	0xcfb90c6e
d0012c74:	46b8b1e8 	ldrtmi	fp, [r8], r8, ror #3
d0012c78:	46434546 	strbmi	r4, [r3], -r6, asr #10
d0012c7c:	4642d90d 	strbmi	sp, [r2], -sp, lsl #18
d0012c80:	802cf8cd 	eorhi	pc, ip, sp, asr #17
d0012c84:	1b01f812 	blne	0xd0090cd4
d0012c88:	f7fd4608 			; <UNDEFINED> instruction: 0xf7fd4608
d0012c8c:	b9b8fbe0 	ldmiblt	r8!, {r5, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d0012c90:	0030f1a1 	eorseq	pc, r0, r1, lsr #3
d0012c94:	28099b0b 	stmdacs	r9, {r0, r1, r3, r8, r9, fp, ip, pc}
d0012c98:	eba8d912 	bl	0xcea490e8
d0012c9c:	f1bb0b07 			; <UNDEFINED> instruction: 0xf1bb0b07
d0012ca0:	d90f0f3f 	stmdble	pc, {r0, r1, r2, r3, r4, r5, r8, r9, sl, fp}	; <UNPREDICTABLE>
d0012ca4:	2b006da3 	blcs	0xd002e338
d0012ca8:	ae1ff47f 	mrcge	4, 0, APSR_nzcv, cr15, cr15, {3}
d0012cac:	447b4b7e 	ldrbtmi	r4, [fp], #-2942	; 0xfffff482
d0012cb0:	6da3e6a3 	stcvs	6, cr14, [r3, #652]!	; 0x28c
d0012cb4:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0012cb8:	4b7cae18 	blmi	0xd1f3e520
d0012cbc:	e69c447b 			; <UNDEFINED> instruction: 0xe69c447b
d0012cc0:	e7d94690 	bfi	r4, r0, #13, #13
d0012cc4:	4639465a 			; <UNDEFINED> instruction: 0x4639465a
d0012cc8:	930b4620 	movwls	r4, #46624	; 0xb620
d0012ccc:	fb9df7fd 	blx	0xce790cca
d0012cd0:	46819a0a 	strmi	r9, [r1], sl, lsl #20
d0012cd4:	b34a9b0b 	movtlt	r9, #43787	; 0xab0b
d0012cd8:	d9114546 	ldmdble	r1, {r1, r2, r6, r8, sl, lr}
d0012cdc:	3b01f818 	blcc	0xd0090d44
d0012ce0:	d0f92b20 	rscsle	r2, r9, r0, lsr #22
d0012ce4:	d0f72b09 	rscsle	r2, r7, r9, lsl #22
d0012ce8:	b9536da3 	ldmdblt	r3, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0012cec:	447b4b70 	ldrbtmi	r4, [fp], #-2928	; 0xfffff490
d0012cf0:	3516e9c4 	ldrcc	lr, [r6, #-2500]	; 0xfffff63c
d0012cf4:	e9c49b08 	stmib	r4, {r3, r8, r9, fp, ip, pc}^
d0012cf8:	9b093a18 	blls	0xd0261560
d0012cfc:	e00066a3 	and	r6, r0, r3, lsr #13
d0012d00:	f1b9d1f2 			; <UNDEFINED> instruction: 0xf1b9d1f2
d0012d04:	f6ff0f00 			; <UNDEFINED> instruction: 0xf6ff0f00
d0012d08:	f64cadf0 			; <UNDEFINED> instruction: 0xf64cadf0
d0012d0c:	22487388 	subcs	r7, r8, #136, 6	; 0x20000002
d0012d10:	fb0258e1 	blx	0xd00a909e
d0012d14:	39014009 	stmdbcc	r1, {r0, r3, lr}
d0012d18:	f64a50e1 			; <UNDEFINED> instruction: 0xf64a50e1
d0012d1c:	fb023388 	blx	0xd009fb46
d0012d20:	44184101 	ldrmi	r4, [r8], #-257	; 0xfffffeff
d0012d24:	f00e4419 			; <UNDEFINED> instruction: 0xf00e4419
d0012d28:	e5defc81 	ldrb	pc, [lr, #3201]	; 0xc81	; <UNPREDICTABLE>
d0012d2c:	d9134546 	ldmdble	r3, {r1, r2, r6, r8, sl, lr}
d0012d30:	3000f898 	mulcc	r0, r8, r8
d0012d34:	d1062b28 	tstle	r6, r8, lsr #22
d0012d38:	2b006da3 	blcs	0xd002e3cc
d0012d3c:	add5f47f 	cfldrdge	mvd15, [r5, #508]	; 0x1fc
d0012d40:	447b4b5c 	ldrbtmi	r4, [fp], #-2908	; 0xfffff4a4
d0012d44:	4546e659 	strbmi	lr, [r6, #-1625]	; 0xfffff9a7
d0012d48:	d0054643 	andle	r4, r5, r3, asr #12
d0012d4c:	2b01f818 	blcs	0xd0090db4
d0012d50:	d0f82a20 	rscsle	r2, r8, r0, lsr #20
d0012d54:	d0f62a09 	rscsle	r2, r6, r9, lsl #20
d0012d58:	21002001 	tstcs	r0, r1
d0012d5c:	e9cd429e 	stmib	sp, {r1, r2, r3, r4, r7, r9, lr}^
d0012d60:	d0130112 	andsle	r0, r3, r2, lsl r1
d0012d64:	aa129606 	bge	0xd04b8584
d0012d68:	9305ae29 	movwls	sl, #24105	; 0x5e29
d0012d6c:	46ec9207 	strbtmi	r9, [ip], r7, lsl #4
d0012d70:	e8acce0f 	stmia	ip!, {r0, r1, r2, r3, r9, sl, fp, lr, pc}
d0012d74:	6833000f 	ldmdavs	r3!, {r0, r1, r2, r3}
d0012d78:	f8cc4620 			; <UNDEFINED> instruction: 0xf8cc4620
d0012d7c:	ab263000 	blge	0xd099ed84
d0012d80:	f7fecb0e 			; <UNDEFINED> instruction: 0xf7fecb0e
d0012d84:	2800fa15 	stmdacs	r0, {r0, r2, r4, r9, fp, ip, sp, lr, pc}
d0012d88:	adaff43f 	cfstrsge	mvf15, [pc, #252]!	; 0xd0012e8c
d0012d8c:	0f00f1b9 	svceq	0x0000f1b9
d0012d90:	f64cda0e 			; <UNDEFINED> instruction: 0xf64cda0e
d0012d94:	58e07388 	stmiapl	r0!, {r3, r7, r8, r9, ip, sp, lr}^
d0012d98:	d1062880 	smlabble	r6, r0, r8, r2
d0012d9c:	2b006da3 	blcs	0xd002e430
d0012da0:	ada3f47f 	cfstrsge	mvf15, [r3, #508]!	; 0x1fc
d0012da4:	447b4b44 	ldrbtmi	r4, [fp], #-2884	; 0xfffff4bc
d0012da8:	1c42e627 	mcrrne	6, 2, lr, r2, cr7
d0012dac:	50e24681 	rscpl	r4, r2, r1, lsl #13
d0012db0:	f64a2048 			; <UNDEFINED> instruction: 0xf64a2048
d0012db4:	465a3588 	ldrbmi	r3, [sl], -r8, lsl #11
d0012db8:	fb004639 	blx	0xd00246a6
d0012dbc:	eb09f909 	bl	0xd02911e8
d0012dc0:	44200005 	strtmi	r0, [r0], #-5
d0012dc4:	f00e444c 			; <UNDEFINED> instruction: 0xf00e444c
d0012dc8:	2300fc31 	movwcs	pc, #3121	; 0xc31	; <UNPREDICTABLE>
d0012dcc:	f50444a3 			; <UNDEFINED> instruction: 0xf50444a3
d0012dd0:	f80b442b 			; <UNDEFINED> instruction: 0xf80b442b
d0012dd4:	e9dd3005 	ldmib	sp, {r0, r2, ip, sp}^
d0012dd8:	e9c42312 	stmib	r4, {r1, r4, r8, r9, sp}^
d0012ddc:	e5842332 	str	r2, [r4, #818]	; 0x332
d0012de0:	f47f2a05 			; <UNDEFINED> instruction: 0xf47f2a05
d0012de4:	4935abc2 	ldmdbmi	r5!, {r1, r6, r7, r8, r9, fp, sp, pc}
d0012de8:	920b4638 	andls	r4, fp, #56, 12	; 0x3800000
d0012dec:	447946cb 	ldrbtmi	r4, [r9], #-1739	; 0xfffff935
d0012df0:	f00e46c8 			; <UNDEFINED> instruction: 0xf00e46c8
d0012df4:	fab0fc2b 	blx	0xcec51ea8
d0012df8:	4931f380 	ldmdbmi	r1!, {r7, r8, r9, ip, sp, lr, pc}
d0012dfc:	095b4638 	ldmdbeq	fp, {r3, r4, r5, r9, sl, lr}^
d0012e00:	44799a0b 	ldrbtmi	r9, [r9], #-2571	; 0xfffff5f5
d0012e04:	930a464e 	movwls	r4, #42574	; 0xa64e
d0012e08:	fc20f00e 	stc2	0, cr15, [r0], #-56	; 0xffffffc8
d0012e0c:	f380fab0 			; <UNDEFINED> instruction: 0xf380fab0
d0012e10:	902cf8cd 	eorls	pc, ip, sp, asr #17
d0012e14:	930c095b 	movwls	r0, #51547	; 0xc95b
d0012e18:	2205492a 	andcs	r4, r5, #688128	; 0xa8000
d0012e1c:	44794638 	ldrbtmi	r4, [r9], #-1592	; 0xfffff9c8
d0012e20:	fc14f00e 	ldc2	0, cr15, [r4], {14}
d0012e24:	fab02300 	blx	0xcec1ba2c
d0012e28:	930ef980 	movwls	pc, #59776	; 0xe980	; <UNPREDICTABLE>
d0012e2c:	1959ea4f 	ldmdbne	r9, {r0, r1, r2, r3, r6, r9, fp, sp, lr, pc}^
d0012e30:	f7ff930d 			; <UNDEFINED> instruction: 0xf7ff930d
d0012e34:	bf00bbd5 	svclt	0x0000bbd5
d0012e38:	fffffc50 			; <UNDEFINED> instruction: 0xfffffc50
d0012e3c:	fffffc10 			; <UNDEFINED> instruction: 0xfffffc10
d0012e40:	fffffc07 			; <UNDEFINED> instruction: 0xfffffc07
d0012e44:	fffffbf8 			; <UNDEFINED> instruction: 0xfffffbf8
d0012e48:	fffffbd6 			; <UNDEFINED> instruction: 0xfffffbd6
d0012e4c:	fffffbc5 			; <UNDEFINED> instruction: 0xfffffbc5
d0012e50:	fffffb93 			; <UNDEFINED> instruction: 0xfffffb93
d0012e54:	fffffade 			; <UNDEFINED> instruction: 0xfffffade
d0012e58:	fffffb08 			; <UNDEFINED> instruction: 0xfffffb08
d0012e5c:	fffffa8e 			; <UNDEFINED> instruction: 0xfffffa8e
d0012e60:	fffffaaa 			; <UNDEFINED> instruction: 0xfffffaaa
d0012e64:	fffffa7f 			; <UNDEFINED> instruction: 0xfffffa7f
d0012e68:	fffffafc 			; <UNDEFINED> instruction: 0xfffffafc
d0012e6c:	fffffa36 			; <UNDEFINED> instruction: 0xfffffa36
d0012e70:	fffffa29 			; <UNDEFINED> instruction: 0xfffffa29
d0012e74:	fffff9e6 			; <UNDEFINED> instruction: 0xfffff9e6
d0012e78:	fffffa01 			; <UNDEFINED> instruction: 0xfffffa01
d0012e7c:	fffff9c6 			; <UNDEFINED> instruction: 0xfffff9c6
d0012e80:	fffff890 			; <UNDEFINED> instruction: 0xfffff890
d0012e84:	fffff925 			; <UNDEFINED> instruction: 0xfffff925
d0012e88:	fffff8ea 			; <UNDEFINED> instruction: 0xfffff8ea
d0012e8c:	fffff8e5 			; <UNDEFINED> instruction: 0xfffff8e5
d0012e90:	fffff8c8 			; <UNDEFINED> instruction: 0xfffff8c8
d0012e94:	fffff8bb 			; <UNDEFINED> instruction: 0xfffff8bb
d0012e98:	fffff81d 			; <UNDEFINED> instruction: 0xfffff81d
d0012e9c:	fffff82f 			; <UNDEFINED> instruction: 0xfffff82f
d0012ea0:	fffff816 			; <UNDEFINED> instruction: 0xfffff816
d0012ea4:	fffff7dd 			; <UNDEFINED> instruction: 0xfffff7dd
d0012ea8:	fffff736 			; <UNDEFINED> instruction: 0xfffff736
d0012eac:	fffff703 			; <UNDEFINED> instruction: 0xfffff703
d0012eb0:	fffff717 			; <UNDEFINED> instruction: 0xfffff717
d0012eb4:	fffff6e0 			; <UNDEFINED> instruction: 0xfffff6e0
d0012eb8:	fffff6ab 			; <UNDEFINED> instruction: 0xfffff6ab
d0012ebc:	fffff357 			; <UNDEFINED> instruction: 0xfffff357
d0012ec0:	fffff349 			; <UNDEFINED> instruction: 0xfffff349
d0012ec4:	fffff340 			; <UNDEFINED> instruction: 0xfffff340

Disassembly of section .text.advance:

d0012ec8 <.text.advance>:
d0012ec8:	f100b570 			; <UNDEFINED> instruction: 0xf100b570
d0012ecc:	46060538 			; <UNDEFINED> instruction: 0x46060538
d0012ed0:	0418f100 	ldreq	pc, [r8], #-256	; 0xffffff00
d0012ed4:	cd0fb088 	stcgt	0, cr11, [pc, #-544]	; 0xd0012cbc
d0012ed8:	e895c40f 	ldm	r5, {r0, r1, r2, r3, sl, lr, pc}
d0012edc:	e884000f 	stm	r4, {r0, r1, r2, r3}
d0012ee0:	466c000f 	strbtmi	r0, [ip], -pc
d0012ee4:	f1064631 			; <UNDEFINED> instruction: 0xf1064631
d0012ee8:	46200538 			; <UNDEFINED> instruction: 0x46200538
d0012eec:	fd5ef7fe 	ldc2l	7, cr15, [lr, #-1016]	; 0xfffffc08
d0012ef0:	c50fcc0f 	strgt	ip, [pc, #-3087]	; 0xd00122e9
d0012ef4:	000fe894 	muleq	pc, r4, r8	; <UNPREDICTABLE>
d0012ef8:	000fe885 	andeq	lr, pc, r5, lsl #17
d0012efc:	b0084630 	andlt	r4, r8, r0, lsr r6
d0012f00:	4070e8bd 	ldrhtmi	lr, [r0], #-141	; 0xffffff73
d0012f04:	b978f7fd 	ldmdblt	r8!, {r0, r2, r3, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}^

Disassembly of section .text.accept:

d0012f08 <.text.accept>:
d0012f08:	6d83b508 	cfstr32vs	mvfx11, [r3, #32]
d0012f0c:	6ac2b933 	bvs	0xcf0c13e0
d0012f10:	d105428a 	smlabble	r5, sl, r2, r4
d0012f14:	ffd8f7ff 			; <UNDEFINED> instruction: 0xffd8f7ff
d0012f18:	bd082001 	stclt	0, cr2, [r8, #-4]
d0012f1c:	e7fc2000 	ldrb	r2, [ip, r0]!
d0012f20:	e7fa4618 			; <UNDEFINED> instruction: 0xe7fa4618

Disassembly of section .text.expect:

d0012f24 <.text.expect>:
d0012f24:	4605b570 			; <UNDEFINED> instruction: 0x4605b570
d0012f28:	f7ff4616 			; <UNDEFINED> instruction: 0xf7ff4616
d0012f2c:	4604ffed 	strmi	pc, [r4], -sp, ror #31
d0012f30:	4631b928 	ldrtmi	fp, [r1], -r8, lsr #18
d0012f34:	f7fd4628 			; <UNDEFINED> instruction: 0xf7fd4628
d0012f38:	4620f99b 			; <UNDEFINED> instruction: 0x4620f99b
d0012f3c:	2401bd70 	strcs	fp, [r1], #-3440	; 0xfffff290
d0012f40:	Address 0x00000000d0012f40 is out of bounds.


Disassembly of section .text.enum_expression:

d0013038 <.text.enum_expression>:
d0013038:	e92d2a19 	push	{r0, r3, r4, r9, fp, sp}
d001303c:	46804ff8 			; <UNDEFINED> instruction: 0x46804ff8
d0013040:	4692468b 	ldrmi	r4, [r2], fp, lsl #13
d0013044:	4995d106 	ldmibmi	r5, {r1, r2, r8, ip, lr, pc}
d0013048:	f7fd4479 			; <UNDEFINED> instruction: 0xf7fd4479
d001304c:	2400f911 	strcs	pc, [r0], #-2321	; 0xfffff6ef
d0013050:	e0f82500 	rscs	r2, r8, r0, lsl #10
d0013054:	2e2b6ac6 	vnmulcs.f32	s12, s23, s12
d0013058:	2e2dd003 	cdpcs	0, 2, cr13, cr13, cr3, {0}
d001305c:	2e7ed001 	cdpcs	0, 7, cr13, cr14, cr1, {0}
d0013060:	4640d133 			; <UNDEFINED> instruction: 0x4640d133
d0013064:	ff30f7ff 			; <UNDEFINED> instruction: 0xff30f7ff
d0013068:	0201f10a 	andeq	pc, r1, #-2147483646	; 0x80000002
d001306c:	46402107 	strbmi	r2, [r0], -r7, lsl #2
d0013070:	ffe2f7ff 			; <UNDEFINED> instruction: 0xffe2f7ff
d0013074:	46042e2d 	strmi	r2, [r4], -sp, lsr #28
d0013078:	d11f460d 	tstle	pc, sp, lsl #12
d001307c:	eb614244 	bl	0xd1863994
d0013080:	f8d80541 			; <UNDEFINED> instruction: 0xf8d80541
d0013084:	2e006058 	mcrcs	0, 0, r6, cr0, cr8, {2}
d0013088:	80ddf040 	sbcshi	pc, sp, r0, asr #32
d001308c:	902cf8d8 	ldrdls	pc, [ip], -r8	; <UNPREDICTABLE>
d0013090:	0f5ef1b9 	svceq	0x005ef1b9
d0013094:	80ebf000 	rschi	pc, fp, r0
d0013098:	80d9f300 	sbcshi	pc, r9, r0, lsl #6
d001309c:	0325f1a9 	msreq	CPSR_sc, #1073741866	; 0x4000002a
d00130a0:	f2002b0a 	vqdmulh.s<illegal width 8>	d2, d0, d10
d00130a4:	2b0a80cd 	blcs	0xd02b33e0
d00130a8:	80dff200 	sbcshi	pc, pc, r0, lsl #4
d00130ac:	f003e8df 			; <UNDEFINED> instruction: 0xf003e8df
d00130b0:	dddde1db 	ldflep	f6, [sp, #876]	; 0x36c
d00130b4:	ddc7dbdd 	vstrle	d29, [r7, #884]	; 0x374
d00130b8:	00dbddc7 	sbcseq	sp, fp, r7, asr #27
d00130bc:	d1e02e7e 	mvnle	r2, lr, ror lr
d00130c0:	43cb43c2 	bicmi	r4, fp, #134217731	; 0x8000003
d00130c4:	461d4614 			; <UNDEFINED> instruction: 0x461d4614
d00130c8:	2128e7db 	ldrdcs	lr, [r8, -fp]!
d00130cc:	ff1cf7ff 			; <UNDEFINED> instruction: 0xff1cf7ff
d00130d0:	f10ab170 			; <UNDEFINED> instruction: 0xf10ab170
d00130d4:	46400201 	strbmi	r0, [r0], -r1, lsl #4
d00130d8:	f7ff2101 			; <UNDEFINED> instruction: 0xf7ff2101
d00130dc:	4a70ffad 	bmi	0xd1c52f98
d00130e0:	460d4604 	strmi	r4, [sp], -r4, lsl #12
d00130e4:	2129447a 			; <UNDEFINED> instruction: 0x2129447a
d00130e8:	f7ff4640 			; <UNDEFINED> instruction: 0xf7ff4640
d00130ec:	e7c8ff1b 	bfi	pc, fp, (invalid: 30:8)	; <UNPREDICTABLE>
d00130f0:	302cf8d8 	ldrdcc	pc, [ip], -r8	; <UNPREDICTABLE>
d00130f4:	7281f5a3 	addvc	pc, r1, #683671552	; 0x28c00000
d00130f8:	d80a2a01 	stmdale	sl, {r0, r9, fp, sp}
d00130fc:	7f81f5b3 	svcvc	0x0081f5b3
d0013100:	4020f8d8 	ldrdmi	pc, [r0], -r8	; <UNPREDICTABLE>
d0013104:	bf0c4640 	svclt	0x000c4640
d0013108:	250017e5 	strcs	r1, [r0, #-2021]	; 0xfffff81b
d001310c:	fedcf7ff 	mrc2	7, 6, pc, cr12, cr15, {7}
d0013110:	4964e7b7 	stmdbmi	r4!, {r0, r1, r2, r4, r5, r7, r8, r9, sl, sp, lr, pc}^
d0013114:	46404479 			; <UNDEFINED> instruction: 0x46404479
d0013118:	4640e797 			; <UNDEFINED> instruction: 0x4640e797
d001311c:	fed4f7ff 	mrc2	7, 6, pc, cr4, cr15, {7}
d0013120:	f10a1c71 			; <UNDEFINED> instruction: 0xf10a1c71
d0013124:	46400201 	strbmi	r0, [r0], -r1, lsl #4
d0013128:	ff86f7ff 			; <UNDEFINED> instruction: 0xff86f7ff
d001312c:	3058f8d8 	ldrsbcc	pc, [r8], #-136	; 0xffffff78	; <UNPREDICTABLE>
d0013130:	460f4606 	strmi	r4, [pc], -r6, lsl #12
d0013134:	d18a2b00 	orrle	r2, sl, r0, lsl #22
d0013138:	0f2ff1b9 	svceq	0x002ff1b9
d001313c:	80a7f000 	adchi	pc, r7, r0
d0013140:	0f25f1b9 	svceq	0x0025f1b9
d0013144:	ea56d115 	b	0xd15c75a0
d0013148:	f0000307 			; <UNDEFINED> instruction: 0xf0000307
d001314c:	1c6b80a3 	stclne	0, cr8, [fp], #-652	; 0xfffffd74
d0013150:	f1b4bf08 			; <UNDEFINED> instruction: 0xf1b4bf08
d0013154:	d0044f00 	andle	r4, r4, r0, lsl #30
d0013158:	f3f6fb94 			; <UNDEFINED> instruction: 0xf3f6fb94
d001315c:	4416fb03 	ldrmi	pc, [r6], #-2819	; 0xfffff4fd
d0013160:	1c7be093 	ldclne	0, cr14, [fp], #-588	; 0xfffffdb4
d0013164:	f1b6bf08 			; <UNDEFINED> instruction: 0xf1b6bf08
d0013168:	d1023fff 	strdle	r3, [r2, -pc]
d001316c:	4479494e 	ldrbtmi	r4, [r9], #-2382	; 0xfffff6b2
d0013170:	f46fe7d1 	vld1.64	{d30}, [pc :64], r1
d0013174:	eb097093 	bl	0xd026f3c8
d0013178:	2b010300 	blcs	0xd0053d80
d001317c:	2f00d806 	svccs	0x0000d806
d0013180:	2e20bf08 	cdpcs	15, 2, cr11, cr0, cr8, {0}
d0013184:	4949d32c 	stmdbmi	r9, {r2, r3, r5, r8, r9, ip, lr, pc}^
d0013188:	e7c44479 			; <UNDEFINED> instruction: 0xe7c44479
d001318c:	0f5ef1b9 	svceq	0x005ef1b9
d0013190:	dc29d04b 	stcle	0, cr13, [r9], #-300	; 0xfffffed4
d0013194:	0925f1a9 	stmdbeq	r5!, {r0, r3, r5, r7, r8, ip, sp, lr, pc}
d0013198:	0f0af1b9 	svceq	0x000af1b9
d001319c:	af71f63f 	svcge	0x0071f63f
d00131a0:	0f0af1b9 	svceq	0x000af1b9
d00131a4:	af6df63f 	svcge	0x006df63f
d00131a8:	f853a302 			; <UNDEFINED> instruction: 0xf853a302
d00131ac:	44132029 	ldrmi	r2, [r3], #-41	; 0xffffffd7
d00131b0:	bf004718 	svclt	0x00004718
d00131b4:	ffffffa5 			; <UNDEFINED> instruction: 0xffffffa5
d00131b8:	0000006d 	andeq	r0, r0, sp, rrx
d00131bc:	fffffecf 			; <UNDEFINED> instruction: 0xfffffecf
d00131c0:	fffffecf 			; <UNDEFINED> instruction: 0xfffffecf
d00131c4:	fffffecf 			; <UNDEFINED> instruction: 0xfffffecf
d00131c8:	0000005d 	andeq	r0, r0, sp, asr r0
d00131cc:	0000004d 	andeq	r0, r0, sp, asr #32
d00131d0:	fffffecf 			; <UNDEFINED> instruction: 0xfffffecf
d00131d4:	00000055 	andeq	r0, r0, r5, asr r0
d00131d8:	fffffecf 			; <UNDEFINED> instruction: 0xfffffecf
d00131dc:	000000d3 	ldrdeq	r0, [r0], -r3
d00131e0:	1327f240 	msrne	CPSR_sxc, #64, 4
d00131e4:	d0254599 	mlale	r5, r9, r5, r4
d00131e8:	7f94f5b9 	svcvc	0x0094f5b9
d00131ec:	f1b9d025 			; <UNDEFINED> instruction: 0xf1b9d025
d00131f0:	f47f0f7c 			; <UNDEFINED> instruction: 0xf47f0f7c
d00131f4:	ea44af46 	b	0xd113ef14
d00131f8:	ea450206 	b	0xd1153a18
d00131fc:	e7610307 	strb	r0, [r1, -r7, lsl #6]!
d0013200:	eb4719a4 	bl	0xd11d9898
d0013204:	e73c0505 	ldr	r0, [ip, -r5, lsl #10]!
d0013208:	eb651ba4 	bl	0xd195a0a0
d001320c:	e7380507 	ldr	r0, [r8, -r7, lsl #10]!
d0013210:	f307fb04 	vqrdmulh.s<illegal width 8>	d15, d7, d4
d0013214:	3305fb06 	movwcc	pc, #23302	; 0x5b06	; <UNPREDICTABLE>
d0013218:	4506fba4 	strmi	pc, [r6, #-2980]	; 0xfffff45c
d001321c:	e730441d 			; <UNDEFINED> instruction: 0xe730441d
d0013220:	0206ea04 	andeq	lr, r6, #4, 20	; 0x4000
d0013224:	0307ea05 	movweq	lr, #31237	; 0x7a05
d0013228:	ea84e74c 	b	0xce14cf60
d001322c:	ea850206 	b	0xce153a4c
d0013230:	e7470307 	strb	r0, [r7, -r7, lsl #6]
d0013234:	250040b4 	strcs	r4, [r0, #-180]	; 0xffffff4c
d0013238:	40f4e723 	rscsmi	lr, r4, r3, lsr #14
d001323c:	2605e7fb 			; <UNDEFINED> instruction: 0x2605e7fb
d0013240:	f77f45b3 			; <UNDEFINED> instruction: 0xf77f45b3
d0013244:	4620af6a 	strtmi	sl, [r0], -sl, ror #30
d0013248:	e8bd4629 	pop	{r0, r3, r5, r9, sl, lr}
d001324c:	f1b98ff8 			; <UNDEFINED> instruction: 0xf1b98ff8
d0013250:	d0100f7c 	andsle	r0, r0, ip, ror pc
d0013254:	7193f46f 	orrsvc	pc, r3, pc, ror #8
d0013258:	0301eb09 	movweq	lr, #6921	; 0x1b09
d001325c:	bf342b02 	svclt	0x00342b02
d0013260:	26002604 	strcs	r2, [r0], -r4, lsl #12
d0013264:	2606e7ec 	strcs	lr, [r6], -ip, ror #15
d0013268:	2600e7ea 	strcs	lr, [r0], -sl, ror #15
d001326c:	2602e7e8 	strcs	lr, [r2], -r8, ror #15
d0013270:	2603e7e6 	strcs	lr, [r3], -r6, ror #15
d0013274:	2601e7e4 	strcs	lr, [r1], -r4, ror #15
d0013278:	1c6ae7e2 	stclne	7, cr14, [sl], #-904	; 0xfffffc78
d001327c:	f1b4bf08 			; <UNDEFINED> instruction: 0xf1b4bf08
d0013280:	f43f4f00 			; <UNDEFINED> instruction: 0xf43f4f00
d0013284:	fb94af6e 	blx	0xce53f046
d0013288:	17e5f4f6 			; <UNDEFINED> instruction: 0x17e5f4f6
d001328c:	ea56e6f9 	b	0xd15cce78
d0013290:	d1f20307 	mvnsle	r0, r7, lsl #6
d0013294:	44794906 	ldrbtmi	r4, [r9], #-2310	; 0xfffff6fa
d0013298:	bf00e73d 	svclt	0x0000e73d
d001329c:	fffffef6 			; <UNDEFINED> instruction: 0xfffffef6
d00132a0:	fffffe7b 			; <UNDEFINED> instruction: 0xfffffe7b
d00132a4:	fffffe74 			; <UNDEFINED> instruction: 0xfffffe74
d00132a8:	fffffe78 			; <UNDEFINED> instruction: 0xfffffe78
d00132ac:	fffffe81 			; <UNDEFINED> instruction: 0xfffffe81
d00132b0:	fffffd2b 			; <UNDEFINED> instruction: 0xfffffd2b

Disassembly of section .text.record_type:

d001331c <.text.record_type>:
d001331c:	4ff7e92d 	svcmi	0x00f7e92d
d0013320:	6ac6460d 	bvs	0xcf1a4b5c
d0013324:	718bf46f 	orrvc	pc, fp, pc, ror #8
d0013328:	18734604 	ldmdane	r3!, {r2, r9, sl, lr}^
d001332c:	d8362b01 	ldmdale	r6!, {r0, r8, r9, fp, sp}
d0013330:	fdcaf7ff 	stc2l	7, cr15, [sl, #1020]	; 0x3fc
d0013334:	6b634a26 	blvs	0xd18e5bd4
d0013338:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d001333c:	4620447a 			; <UNDEFINED> instruction: 0x4620447a
d0013340:	9024f8d4 	ldrdls	pc, [r4], -r4	; <UNPREDICTABLE>
d0013344:	8028f8d4 	ldrdhi	pc, [r8], -r4	; <UNPREDICTABLE>
d0013348:	7030f894 	mlasvc	r0, r4, r8, pc	; <UNPREDICTABLE>
d001334c:	e9d49301 	ldmib	r4, {r0, r8, r9, ip, pc}^
d0013350:	f7ffab06 			; <UNDEFINED> instruction: 0xf7ffab06
d0013354:	b918fde7 	ldmdblt	r8, {r0, r1, r2, r5, r6, r7, r8, sl, fp, ip, sp, lr, pc}
d0013358:	b0032000 	andlt	r2, r3, r0
d001335c:	8ff0e8bd 	svchi	0x00f0e8bd
d0013360:	728cf5a6 	addvc	pc, ip, #696254464	; 0x29800000
d0013364:	46204651 			; <UNDEFINED> instruction: 0x46204651
d0013368:	41534253 	cmpmi	r3, r3, asr r2
d001336c:	f7fd465a 			; <UNDEFINED> instruction: 0xf7fd465a
d0013370:	2800f9c7 	stmdacs	r0, {r0, r1, r2, r6, r7, r8, fp, ip, sp, lr, pc}
d0013374:	f5b6da11 			; <UNDEFINED> instruction: 0xf5b6da11
d0013378:	d00b7f8c 	andle	r7, fp, ip, lsl #31
d001337c:	447b4b15 	ldrbtmi	r4, [fp], #-2837	; 0xfffff4eb
d0013380:	b92a6da2 	stmdblt	sl!, {r1, r5, r7, r8, sl, fp, sp, lr}
d0013384:	3916e9c4 	ldmdbcc	r6, {r2, r6, r7, r8, fp, sp, lr, pc}
d0013388:	e9c49b01 	stmib	r4, {r0, r8, r9, fp, ip, pc}^
d001338c:	66a38718 	ssatvs	r8, #4, r8, lsl #14
d0013390:	e7e22001 	strb	r2, [r2, r1]!
d0013394:	447b4b10 	ldrbtmi	r4, [fp], #-2832	; 0xfffff4f0
d0013398:	6028e7f2 	strdvs	lr, [r8], -r2	; <UNPREDICTABLE>
d001339c:	f240e7f8 	vaba.s8	q15, q8, q12
d00133a0:	429e1301 	addsmi	r1, lr, #67108864	; 0x4000000
d00133a4:	69c2d1d8 	stmibvs	r2, {r3, r4, r6, r7, r8, ip, lr, pc}^
d00133a8:	f7fd6981 			; <UNDEFINED> instruction: 0xf7fd6981
d00133ac:	2800fa56 	stmdacs	r0, {r1, r2, r4, r6, r9, fp, ip, sp, lr, pc}
d00133b0:	2324dbd2 			; <UNDEFINED> instruction: 0x2324dbd2
d00133b4:	4000fb03 	andmi	pc, r0, r3, lsl #22
d00133b8:	3075f500 	rsbscc	pc, r5, r0, lsl #10
d00133bc:	33acf890 			; <UNDEFINED> instruction: 0x33acf890
d00133c0:	d0c92bff 	strdle	r2, [r9], #191	; 0xbf
d00133c4:	602b4620 	eorvs	r4, fp, r0, lsr #12
d00133c8:	fd7ef7ff 	ldc2l	7, cr15, [lr, #-1020]!	; 0xfffffc04
d00133cc:	bf00e7e0 	svclt	0x0000e7e0
d00133d0:	ffffffbd 			; <UNDEFINED> instruction: 0xffffffbd
d00133d4:	ffffff56 			; <UNDEFINED> instruction: 0xffffff56
d00133d8:	ffffff1a 			; <UNDEFINED> instruction: 0xffffff1a

Disassembly of section .text.enum_declaration:

d0013508 <.text.enum_declaration>:
d0013508:	f2404ac4 	vpmax.s8	q10, q8, q2
d001350c:	e92d111b 	push	{r0, r1, r3, r4, r8, ip}
d0013510:	447a4ff0 	ldrbtmi	r4, [sl], #-4080	; 0xfffff010
d0013514:	ed2d4604 	stc	6, cr4, [sp, #-16]!
d0013518:	b0978b02 	addslt	r8, r7, r2, lsl #22
d001351c:	fd02f7ff 	stc2	7, cr15, [r2, #-1020]	; 0xfffffc04
d0013520:	28004605 	stmdacs	r0, {r0, r2, r9, sl, lr}
d0013524:	af06d05a 	svcge	0x0006d05a
d0013528:	21002220 	tstcs	r0, r0, lsr #4
d001352c:	f00e4638 			; <UNDEFINED> instruction: 0xf00e4638
d0013530:	f8d4f86f 			; <UNDEFINED> instruction: 0xf8d4f86f
d0013534:	f240a02c 	vhadd.s8	d26, d0, d28
d0013538:	459a1301 	ldrmi	r1, [sl, #769]	; 0x301
d001353c:	f104d137 			; <UNDEFINED> instruction: 0xf104d137
d0013540:	463d0618 			; <UNDEFINED> instruction: 0x463d0618
d0013544:	c50fce0f 	strgt	ip, [pc, #-3599]	; 0xd001273d
d0013548:	000fe896 	muleq	pc, r6, r8	; <UNPREDICTABLE>
d001354c:	000fe885 	andeq	lr, pc, r5, lsl #17
d0013550:	46206a63 	strtmi	r6, [r0], -r3, ror #20
d0013554:	93026b66 	movwls	r6, #11110	; 0x2b66
d0013558:	93036aa3 	movwls	r6, #15011	; 0x3aa3
d001355c:	3030f894 	mlascc	r0, r4, r8, pc	; <UNPREDICTABLE>
d0013560:	8906e9d4 	stmdbhi	r6, {r2, r4, r6, r7, r8, fp, sp, lr, pc}
d0013564:	f7ff9301 			; <UNDEFINED> instruction: 0xf7ff9301
d0013568:	217bfcaf 	cmncs	fp, pc, lsr #25	; <UNPREDICTABLE>
d001356c:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0013570:	f240fccb 	sha1c.32	<illegal reg q15.5>, q8, <illegal reg q5.5>
d0013574:	46051301 	strmi	r1, [r5], -r1, lsl #6
d0013578:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d001357c:	459a8121 	ldrmi	r8, [sl, #289]	; 0x121
d0013580:	f504d161 			; <UNDEFINED> instruction: 0xf504d161
d0013584:	f04f357e 			; <UNDEFINED> instruction: 0xf04f357e
d0013588:	f5040a00 			; <UNDEFINED> instruction: 0xf5040a00
d001358c:	f5053b7f 			; <UNDEFINED> instruction: 0xf5053b7f
d0013590:	f8db75ca 			; <UNDEFINED> instruction: 0xf8db75ca
d0013594:	f50b3214 			; <UNDEFINED> instruction: 0xf50b3214
d0013598:	459a7205 	ldrmi	r7, [sl, #517]	; 0x205
d001359c:	2b20d30f 	blcs	0xd08481e0
d00135a0:	499fd131 	ldmibmi	pc, {r0, r4, r5, r8, ip, lr, pc}	; <UNPREDICTABLE>
d00135a4:	46204479 			; <UNDEFINED> instruction: 0x46204479
d00135a8:	fe62f7fc 	mcr2	7, 3, pc, cr2, cr12, {7}	; <UNPREDICTABLE>
d00135ac:	2600e015 			; <UNDEFINED> instruction: 0x2600e015
d00135b0:	46b146b2 			; <UNDEFINED> instruction: 0x46b146b2
d00135b4:	960146b0 			; <UNDEFINED> instruction: 0x960146b0
d00135b8:	96029603 	strls	r9, [r2], -r3, lsl #12
d00135bc:	f895e7d5 			; <UNDEFINED> instruction: 0xf895e7d5
d00135c0:	7a232020 	bvc	0xd08db648
d00135c4:	d11a429a 			; <UNDEFINED> instruction: 0xd11a429a
d00135c8:	4642464b 	strbmi	r4, [r2], -fp, asr #12
d00135cc:	0100e9d5 	ldrdeq	lr, [r0, -r5]
d00135d0:	f888f7fd 			; <UNDEFINED> instruction: 0xf888f7fd
d00135d4:	6da5b198 	stfvsd	f3, [r5, #608]!	; 0x260
d00135d8:	2500b135 	strcs	fp, [r0, #-309]	; 0xfffffecb
d00135dc:	b0174628 	andslt	r4, r7, r8, lsr #12
d00135e0:	8b02ecbd 	blhi	0xd00ce8dc
d00135e4:	8ff0e8bd 	svchi	0x00f0e8bd
d00135e8:	447b4b8e 	ldrbtmi	r4, [fp], #-2958	; 0xfffff472
d00135ec:	9b0265a3 	blls	0xd00acc80
d00135f0:	65e366a6 	strbvs	r6, [r3, #1702]!	; 0x6a6
d00135f4:	66239b03 	strtvs	r9, [r3], -r3, lsl #22
d00135f8:	66639b01 	strbtvs	r9, [r3], -r1, lsl #22
d00135fc:	f10ae7ee 			; <UNDEFINED> instruction: 0xf10ae7ee
d0013600:	35240a01 	strcc	r0, [r4, #-2561]!	; 0xfffff5ff
d0013604:	1c59e7c5 	mrrcne	7, 12, lr, r9, cr5
d0013608:	0c24f04f 	stceq	0, cr15, [r4], #-316	; 0xfffffec4
d001360c:	6011960d 	andsvs	r9, r1, sp, lsl #12
d0013610:	fb0c9a02 	blx	0xd0339e22
d0013614:	7a254303 	bvc	0xd0964228
d0013618:	f5039209 			; <UNDEFINED> instruction: 0xf5039209
d001361c:	9a033c7e 	bls	0xd00e281c
d0013620:	76caf50c 	strbvc	pc, [sl], ip, lsl #10	; <UNPREDICTABLE>
d0013624:	f240920a 	vhsub.s8	d25, d0, d10
d0013628:	920b1201 	andls	r1, fp, #268435456	; 0x10000000
d001362c:	e9cd9a01 	stmib	sp, {r0, r9, fp, ip, pc}^
d0013630:	f88d8906 			; <UNDEFINED> instruction: 0xf88d8906
d0013634:	cf0f2030 	svcgt	0x000f2030
d0013638:	e897c60f 	ldm	r7, {r0, r1, r2, r3, r9, sl, lr, pc}
d001363c:	e886000f 	stm	r6, {r0, r1, r2, r3}
d0013640:	f88c000f 			; <UNDEFINED> instruction: 0xf88c000f
d0013644:	4b7851b4 	blmi	0xd1e27d1c
d0013648:	35fff04f 	ldrbcc	pc, [pc, #79]!	; 0xd001369f	; <UNPREDICTABLE>
d001364c:	0b00f04f 	bleq	0xd004f790
d0013650:	462e447b 			; <UNDEFINED> instruction: 0x462e447b
d0013654:	3a10ee08 	bcc	0xd044ee7c
d0013658:	93036da3 	movwls	r6, #15779	; 0x3da3
d001365c:	f0402b00 			; <UNDEFINED> instruction: 0xf0402b00
d0013660:	6ae3809e 	bvs	0xcf8f38e0
d0013664:	f0002b7d 			; <UNDEFINED> instruction: 0xf0002b7d
d0013668:	f5b3809a 			; <UNDEFINED> instruction: 0xf5b3809a
d001366c:	f0007f80 			; <UNDEFINED> instruction: 0xf0007f80
d0013670:	f1048096 			; <UNDEFINED> instruction: 0xf1048096
d0013674:	af0e0c18 	svcge	0x000e0c18
d0013678:	8030f894 	mlashi	r0, r4, r8, pc	; <UNPREDICTABLE>
d001367c:	000fe8bc 			; <UNDEFINED> instruction: 0x000fe8bc
d0013680:	e89cc70f 	ldm	ip, {r0, r1, r2, r3, r8, r9, sl, lr, pc}
d0013684:	e887000f 	stm	r7, {r0, r1, r2, r3}
d0013688:	6a63000f 	bvs	0xd18d36cc
d001368c:	2a10ee18 	bcs	0xd044eef4
d0013690:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d0013694:	93014620 	movwls	r4, #5664	; 0x1620
d0013698:	6b676aa3 	blvs	0xd19ee12c
d001369c:	e9d49302 	ldmib	r4, {r1, r8, r9, ip, pc}^
d00136a0:	f7ffa906 			; <UNDEFINED> instruction: 0xf7ffa906
d00136a4:	2800fc3f 	stmdacs	r0, {r0, r1, r2, r3, r4, r5, sl, fp, ip, sp, lr, pc}
d00136a8:	464ad097 			; <UNDEFINED> instruction: 0x464ad097
d00136ac:	46204651 			; <UNDEFINED> instruction: 0x46204651
d00136b0:	fe66f7fc 	mcr2	7, 3, pc, cr6, cr12, {7}	; <UNPREDICTABLE>
d00136b4:	db0c2800 	blle	0xd031d6bc
d00136b8:	2b006da3 	blcs	0xd002ed4c
d00136bc:	4b5bd18d 	blmi	0xd1707cf8
d00136c0:	65a3447b 	strvs	r4, [r3, #1147]!	; 0x47b
d00136c4:	66a79b01 	strtvs	r9, [r7], r1, lsl #22
d00136c8:	9b0265e3 	blls	0xd00ace5c
d00136cc:	3818e9c4 	ldmdacc	r8, {r2, r6, r7, r8, fp, sp, lr, pc}
d00136d0:	464ae783 	strbmi	lr, [sl], -r3, lsl #15
d00136d4:	46204651 			; <UNDEFINED> instruction: 0x46204651
d00136d8:	f8bff7fd 			; <UNDEFINED> instruction: 0xf8bff7fd
d00136dc:	daeb2800 	ble	0xcfadd6e4
d00136e0:	4620213d 			; <UNDEFINED> instruction: 0x4620213d
d00136e4:	fc10f7ff 	ldc2	7, cr15, [r0], {255}	; 0xff
d00136e8:	9a03b1e0 	bls	0xd00ffe70
d00136ec:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d00136f0:	fca2f7ff 	stc2	7, cr15, [r2], #1020	; 0x3fc
d00136f4:	460e4605 	strmi	r4, [lr], -r5, lsl #12
d00136f8:	4300f115 	movwmi	pc, #277	; 0x115	; <UNPREDICTABLE>
d00136fc:	32fff04f 	rscscc	pc, pc, #79	; 0x4f
d0013700:	f1469304 			; <UNDEFINED> instruction: 0xf1469304
d0013704:	93050300 	movwls	r0, #21248	; 0x5300
d0013708:	e9dd2300 	ldmib	sp, {r8, r9, sp}^
d001370c:	428b0104 	addmi	r0, fp, #4, 2
d0013710:	4282bf08 	addmi	fp, r2, #8, 30
d0013714:	6da3d20a 	sfmvs	f5, 1, [r3, #40]!	; 0x28
d0013718:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001371c:	4b44af5e 	blmi	0xd113f49c
d0013720:	e7ce447b 			; <UNDEFINED> instruction: 0xe7ce447b
d0013724:	f1463501 			; <UNDEFINED> instruction: 0xf1463501
d0013728:	e7e50600 	strb	r0, [r5, r0, lsl #12]!
d001372c:	327ef504 	rsbscc	pc, lr, #4, 10	; 0x1000000
d0013730:	3190f8d2 			; <UNDEFINED> instruction: 0x3190f8d2
d0013734:	d1062ba0 	smlatble	r6, r0, fp, r2
d0013738:	2b006da3 	blcs	0xd002edcc
d001373c:	af4df47f 	svcge	0x004df47f
d0013740:	447b4b3c 	ldrbtmi	r4, [fp], #-2876	; 0xfffff4c4
d0013744:	f88de7bd 			; <UNDEFINED> instruction: 0xf88de7bd
d0013748:	1c598050 	mrrcne	0, 5, r8, r9, cr0
d001374c:	0828f04f 	stmdaeq	r8!, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d0013750:	0e38f10d 	rndeqe	f7, #5.0
d0013754:	1190f8c2 	orrsne	pc, r0, r2, asr #17
d0013758:	0b01f10b 	bleq	0xd008fb8c
d001375c:	fb089a01 	blx	0xd0239f6a
d0013760:	97154803 	ldrls	r4, [r5, -r3, lsl #16]
d0013764:	3878f508 	ldmdacc	r8!, {r3, r8, sl, ip, sp, lr, pc}^
d0013768:	9a029211 	bls	0xd00b7fb4
d001376c:	0790f108 	ldreq	pc, [r0, r8, lsl #2]
d0013770:	c008f894 	mulgt	r8, r4, r8
d0013774:	e9cd9212 	stmib	sp, {r1, r4, r9, ip, pc}^
d0013778:	e8bea90e 	ldm	lr!, {r1, r2, r3, r8, fp, sp, pc}
d001377c:	c70f000f 	strgt	r0, [pc, -pc]
d0013780:	000fe89e 	muleq	pc, lr, r8	; <UNPREDICTABLE>
d0013784:	000fe887 	andeq	lr, pc, r7, lsl #17
d0013788:	4620212c 	strtmi	r2, [r0], -ip, lsr #2
d001378c:	50b0f8c8 	adcspl	pc, r0, r8, asr #17
d0013790:	c0b4f888 	adcsgt	pc, r4, r8, lsl #17
d0013794:	fbb8f7ff 	blx	0xcee5179a
d0013798:	f47f2800 			; <UNDEFINED> instruction: 0xf47f2800
d001379c:	f1bbaf5d 			; <UNDEFINED> instruction: 0xf1bbaf5d
d00137a0:	d1020f00 	tstle	r2, r0, lsl #30
d00137a4:	44794924 	ldrbtmi	r4, [r9], #-2340	; 0xfffff6dc
d00137a8:	4a24e6fd 	bmi	0xd094d3a4
d00137ac:	4620217d 			; <UNDEFINED> instruction: 0x4620217d
d00137b0:	b017447a 	andslt	r4, r7, sl, ror r4
d00137b4:	8b02ecbd 	blhi	0xd00ceab0
d00137b8:	4ff0e8bd 	svcmi	0x00f0e8bd
d00137bc:	bbb2f7ff 	bllt	0xcecd17c0
d00137c0:	d111459a 			; <UNDEFINED> instruction: 0xd111459a
d00137c4:	377ef504 	ldrbcc	pc, [lr, -r4, lsl #10]!	; <UNPREDICTABLE>
d00137c8:	f5044682 			; <UNDEFINED> instruction: 0xf5044682
d00137cc:	f5073b7f 			; <UNDEFINED> instruction: 0xf5073b7f
d00137d0:	f8db77ca 			; <UNDEFINED> instruction: 0xf8db77ca
d00137d4:	459a3214 	ldrmi	r3, [sl, #532]	; 0x214
d00137d8:	6da3d30c 	stcvs	3, cr13, [r3, #48]!	; 0x30
d00137dc:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d00137e0:	4b17aefc 	blmi	0xd05ff3d8
d00137e4:	e701447b 	smlsdx	r1, fp, r4, r4
d00137e8:	46204916 			; <UNDEFINED> instruction: 0x46204916
d00137ec:	f7fc4479 			; <UNDEFINED> instruction: 0xf7fc4479
d00137f0:	e6f3fd3f 			; <UNDEFINED> instruction: 0xe6f3fd3f
d00137f4:	2020f897 	mlacs	r0, r7, r8, pc	; <UNPREDICTABLE>
d00137f8:	429a7a23 	addsmi	r7, sl, #143360	; 0x23000
d00137fc:	f10ad003 			; <UNDEFINED> instruction: 0xf10ad003
d0013800:	37240a01 	strcc	r0, [r4, -r1, lsl #20]!
d0013804:	464be7e5 	strbmi	lr, [fp], -r5, ror #15
d0013808:	e9d74642 	ldmib	r7, {r1, r6, r9, sl, lr}^
d001380c:	f7fc0100 			; <UNDEFINED> instruction: 0xf7fc0100
d0013810:	2800ff69 	stmdacs	r0, {r0, r3, r5, r6, r8, r9, sl, fp, ip, sp, lr, pc}
d0013814:	2501d0f3 	strcs	sp, [r1, #-243]	; 0xffffff0d
d0013818:	bf00e6e0 	svclt	0x0000e6e0
d001381c:	fffffec6 			; <UNDEFINED> instruction: 0xfffffec6
d0013820:	fffffe5c 			; <UNDEFINED> instruction: 0xfffffe5c
d0013824:	fffffdfc 			; <UNDEFINED> instruction: 0xfffffdfc
d0013828:	fffffdc3 			; <UNDEFINED> instruction: 0xfffffdc3
d001382c:	fffffd6f 			; <UNDEFINED> instruction: 0xfffffd6f
d0013830:	fffffd27 			; <UNDEFINED> instruction: 0xfffffd27
d0013834:	fffffd2f 			; <UNDEFINED> instruction: 0xfffffd2f
d0013838:	fffffce3 			; <UNDEFINED> instruction: 0xfffffce3
d001383c:	fffffd00 			; <UNDEFINED> instruction: 0xfffffd00
d0013840:	fffffd0e 			; <UNDEFINED> instruction: 0xfffffd0e
d0013844:	fffffce6 			; <UNDEFINED> instruction: 0xfffffce6

Disassembly of section .text.sizeof_operand:

d0013a48 <.text.sizeof_operand>:
d0013a48:	4ff0e92d 	svcmi	0x00f0e92d
d0013a4c:	21284604 			; <UNDEFINED> instruction: 0x21284604
d0013a50:	8b02ed2d 	blhi	0xd00cef0c
d0013a54:	f7ffb08b 			; <UNDEFINED> instruction: 0xf7ffb08b
d0013a58:	f240fa57 	vpmin.s8	<illegal reg q15.5>, q0, <illegal reg q3.5>
d0013a5c:	90021107 	andls	r1, r2, r7, lsl #2
d0013a60:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0013a64:	b128fa51 	msrlt	R8_fiq, r1
d0013a68:	4620212a 	strtmi	r2, [r0], -sl, lsr #2
d0013a6c:	fa4cf7ff 	blx	0xd1351a70
d0013a70:	e0312704 	eors	r2, r1, r4, lsl #14
d0013a74:	7184f44f 	orrvc	pc, r4, pc, asr #8
d0013a78:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0013a7c:	b190fa45 	orrslt	pc, r0, r5, asr #20
d0013a80:	4620212a 	strtmi	r2, [r0], -sl, lsr #2
d0013a84:	fa40f7ff 	blx	0xd1051a88
d0013a88:	28004607 	stmdacs	r0, {r0, r1, r2, r9, sl, lr}
d0013a8c:	f8dfd1f0 			; <UNDEFINED> instruction: 0xf8dfd1f0
d0013a90:	46201484 	strtmi	r1, [r0], -r4, lsl #9
d0013a94:	f7fc4479 			; <UNDEFINED> instruction: 0xf7fc4479
d0013a98:	4638fbeb 	ldrtmi	pc, [r8], -fp, ror #23	; <UNPREDICTABLE>
d0013a9c:	ecbdb00b 	ldc	0, cr11, [sp], #44	; 0x2c
d0013aa0:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d0013aa4:	6ae28ff0 	bvs	0xcf8b7a6c
d0013aa8:	131bf240 	tstne	fp, #64, 4	; <UNPREDICTABLE>
d0013aac:	d106429a 			; <UNDEFINED> instruction: 0xd106429a
d0013ab0:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0013ab4:	2800fd29 	stmdacs	r0, {r0, r3, r5, r8, sl, fp, ip, sp, lr, pc}
d0013ab8:	2700d1da 			; <UNDEFINED> instruction: 0x2700d1da
d0013abc:	f240e7ed 	vabd.s8	q15, q8, <illegal reg q14.5>
d0013ac0:	4620110b 	strtmi	r1, [r0], -fp, lsl #2
d0013ac4:	fa20f7ff 	blx	0xd0851ac8
d0013ac8:	212ab348 			; <UNDEFINED> instruction: 0x212ab348
d0013acc:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0013ad0:	2800fa1b 	stmdacs	r0, {r0, r1, r3, r4, r9, fp, ip, sp, lr, pc}
d0013ad4:	2701d1cc 	strcs	sp, [r1, -ip, asr #3]
d0013ad8:	4620215b 			; <UNDEFINED> instruction: 0x4620215b
d0013adc:	fa14f7ff 	blx	0xd0551ae0
d0013ae0:	d0602800 	rsble	r2, r0, r0, lsl #16
d0013ae4:	f5a36ae3 			; <UNDEFINED> instruction: 0xf5a36ae3
d0013ae8:	2b017381 	blcs	0xd00708f4
d0013aec:	81e3f200 	mvnhi	pc, r0, lsl #4
d0013af0:	2d006a25 	vstrcs	s12, [r0, #-148]	; 0xffffff6c
d0013af4:	81dff000 	bicshi	pc, pc, r0
d0013af8:	2305fba7 	movwcs	pc, #23463	; 0x5ba7	; <UNPREDICTABLE>
d0013afc:	f0402b00 			; <UNDEFINED> instruction: 0xf0402b00
d0013b00:	462081da 			; <UNDEFINED> instruction: 0x462081da
d0013b04:	f9e0f7ff 			; <UNDEFINED> instruction: 0xf9e0f7ff
d0013b08:	240cf8df 	strcs	pc, [ip], #-2271	; 0xfffff721
d0013b0c:	4620215d 			; <UNDEFINED> instruction: 0x4620215d
d0013b10:	f7ff447a 			; <UNDEFINED> instruction: 0xf7ff447a
d0013b14:	2800fa07 	stmdacs	r0, {r0, r1, r2, r9, fp, ip, sp, lr, pc}
d0013b18:	436fd0cf 	cmnmi	pc, #207	; 0xcf
d0013b1c:	6ae5e043 	bvs	0xcf98bc30
d0013b20:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d0013b24:	d118429d 			; <UNDEFINED> instruction: 0xd118429d
d0013b28:	69e14afc 	stmibvs	r1!, {r2, r3, r4, r5, r6, r7, r9, fp, lr}^
d0013b2c:	69a0447a 	stmibvs	r0!, {r1, r3, r4, r5, r6, sl, lr}
d0013b30:	ff00f7fc 			; <UNDEFINED> instruction: 0xff00f7fc
d0013b34:	4620b118 			; <UNDEFINED> instruction: 0x4620b118
d0013b38:	f9c6f7ff 			; <UNDEFINED> instruction: 0xf9c6f7ff
d0013b3c:	6ae3e7c5 	bvs	0xcf90da58
d0013b40:	d10a42ab 	smlatble	sl, fp, r2, r4
d0013b44:	69e14af6 	stmibvs	r1!, {r1, r2, r4, r5, r6, r7, r9, fp, lr}^
d0013b48:	69a0447a 	stmibvs	r0!, {r1, r3, r4, r5, r6, sl, lr}
d0013b4c:	fef2f7fc 	mrc2	7, 7, pc, cr2, cr12, {7}
d0013b50:	4620b118 			; <UNDEFINED> instruction: 0x4620b118
d0013b54:	f9b8f7ff 			; <UNDEFINED> instruction: 0xf9b8f7ff
d0013b58:	4620e786 	strtmi	lr, [r0], -r6, lsl #15
d0013b5c:	fea2f7fc 	mcr2	7, 5, pc, cr2, cr12, {7}	; <UNPREDICTABLE>
d0013b60:	2300b1c0 	movwcs	fp, #448	; 0x1c0
d0013b64:	4620a909 	strtmi	sl, [r0], -r9, lsl #18
d0013b68:	f7ff9309 			; <UNDEFINED> instruction: 0xf7ff9309
d0013b6c:	2800fbd7 	stmdacs	r0, {r0, r1, r2, r4, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d0013b70:	212ad0a3 			; <UNDEFINED> instruction: 0x212ad0a3
d0013b74:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0013b78:	2800f9c7 	stmdacs	r0, {r0, r1, r2, r6, r7, r8, fp, ip, sp, lr, pc}
d0013b7c:	af78f47f 	svcge	0x0078f47f
d0013b80:	f44f9b09 			; <UNDEFINED> instruction: 0xf44f9b09
d0013b84:	fb02721a 	blx	0xd00b03f6
d0013b88:	f5034303 			; <UNDEFINED> instruction: 0xf5034303
d0013b8c:	8d1f3368 	ldchi	3, cr3, [pc, #-416]	; 0xd00139f4
d0013b90:	e7a100bf 			; <UNDEFINED> instruction: 0xe7a100bf
d0013b94:	f5a36ae3 			; <UNDEFINED> instruction: 0xf5a36ae3
d0013b98:	2b017381 	blcs	0xd00709a4
d0013b9c:	2704d811 	smladcs	r4, r1, r8, sp
d0013ba0:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0013ba4:	9b02f991 	blls	0xd00d21f0
d0013ba8:	f43f2b00 			; <UNDEFINED> instruction: 0xf43f2b00
d0013bac:	4addaf76 	bmi	0xcf77f98c
d0013bb0:	46202129 	strtmi	r2, [r0], -r9, lsr #2
d0013bb4:	f7ff447a 			; <UNDEFINED> instruction: 0xf7ff447a
d0013bb8:	2800f9b5 	stmdacs	r0, {r0, r2, r4, r5, r7, r8, fp, ip, sp, lr, pc}
d0013bbc:	af6df47f 	svcge	0x006df47f
d0013bc0:	212ae77b 			; <UNDEFINED> instruction: 0x212ae77b
d0013bc4:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0013bc8:	6a63f99f 	bvs	0xd191224c
d0013bcc:	46804ad6 	pkhtbmi	r4, r0, r6, asr #21
d0013bd0:	f2409300 	vcgt.s8	d25, d0, d0
d0013bd4:	6b631101 	blvs	0xd18d7fe0
d0013bd8:	4620447a 			; <UNDEFINED> instruction: 0x4620447a
d0013bdc:	a028f8d4 	ldrdge	pc, [r8], -r4	; <UNPREDICTABLE>
d0013be0:	9030f894 	mlasls	r0, r4, r8, pc	; <UNPREDICTABLE>
d0013be4:	e9d49301 	ldmib	r4, {r0, r8, r9, ip, pc}^
d0013be8:	f7ff5606 			; <UNDEFINED> instruction: 0xf7ff5606
d0013bec:	2800f99b 	stmdacs	r0, {r0, r1, r3, r4, r7, r8, fp, ip, sp, lr, pc}
d0013bf0:	af63f43f 	svcge	0x0063f43f
d0013bf4:	46294632 			; <UNDEFINED> instruction: 0x46294632
d0013bf8:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0013bfc:	2800fde9 	stmdacs	r0, {r0, r3, r5, r6, r7, r8, sl, fp, ip, sp, lr, pc}
d0013c00:	8172f280 	cmnhi	r2, r0, lsl #5	; <UNPREDICTABLE>
d0013c04:	46294632 			; <UNDEFINED> instruction: 0x46294632
d0013c08:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0013c0c:	2800fe01 	stmdacs	r0, {r0, r9, sl, fp, ip, sp, lr, pc}
d0013c10:	6da7da0d 			; <UNDEFINED> instruction: 0x6da7da0d
d0013c14:	f47f2f00 			; <UNDEFINED> instruction: 0xf47f2f00
d0013c18:	4bc4af50 	blmi	0xcf13f960
d0013c1c:	65a3447b 	strvs	r4, [r3, #1147]!	; 0x47b
d0013c20:	65e39b00 	strbvs	r9, [r3, #2816]!	; 0xb00
d0013c24:	e9c49b01 	stmib	r4, {r0, r8, r9, fp, ip, pc}^
d0013c28:	66a3a918 	ssatvs	sl, #4, r8, lsl #18
d0013c2c:	233ce735 	teqcs	ip, #13893632	; 0xd40000
d0013c30:	4000fb03 	andmi	pc, r0, r3, lsl #22
d0013c34:	305ff500 	subscc	pc, pc, r0, lsl #10
d0013c38:	23ecf890 	mvncs	pc, #144, 16	; 0x900000
d0013c3c:	53eef890 	mvnpl	pc, #144, 16	; 0x900000
d0013c40:	13fcf8d0 	mvnsne	pc, #208, 16	; 0xd00000
d0013c44:	030df1a2 	movweq	pc, #53666	; 0xd1a2	; <UNPREDICTABLE>
d0013c48:	d9302b04 	ldmdble	r0!, {r2, r8, r9, fp, sp}
d0013c4c:	26001fd3 			; <UNDEFINED> instruction: 0x26001fd3
d0013c50:	d92e2b02 	stmdble	lr!, {r1, r8, r9, fp, sp}
d0013c54:	d02e2a10 	eorle	r2, lr, r0, lsl sl
d0013c58:	0c11f1a2 	ldfeqd	f7, [r1], {162}	; 0xa2
d0013c5c:	0300f1dc 	movweq	pc, #476	; 0x1dc	; <UNPREDICTABLE>
d0013c60:	030ceb43 	movweq	lr, #52035	; 0xcb43
d0013c64:	f0002a0a 			; <UNDEFINED> instruction: 0xf0002a0a
d0013c68:	2a13814b 	bcs	0xd04f419c
d0013c6c:	48a8dc03 	stmiami	r8!, {r0, r1, sl, fp, ip, lr, pc}
d0013c70:	07c740d0 			; <UNDEFINED> instruction: 0x07c740d0
d0013c74:	1f90d421 	svcne	0x0090d421
d0013c78:	0b00f1d0 	bleq	0xd00503c0
d0013c7c:	0b00eb4b 	bleq	0xd004e9b0
d0013c80:	d01d2a07 	andsle	r2, sp, r7, lsl #20
d0013c84:	d01b2a05 	andsle	r2, fp, r5, lsl #20
d0013c88:	f1bbb346 			; <UNDEFINED> instruction: 0xf1bbb346
d0013c8c:	f0400f00 			; <UNDEFINED> instruction: 0xf0400f00
d0013c90:	f44f8122 	vst4.8	{d24,d26,d28,d30}, [pc :128], r2
d0013c94:	fb02721a 	blx	0xd00b0506
d0013c98:	f5024205 			; <UNDEFINED> instruction: 0xf5024205
d0013c9c:	8d173268 	lfmhi	f3, 4, [r7, #-416]	; 0xfffffe60
d0013ca0:	0f00f1b8 	svceq	0x0000f1b8
d0013ca4:	00bfd113 	adcseq	sp, pc, r3, lsl r1	; <UNPREDICTABLE>
d0013ca8:	434fb363 	movtmi	fp, #62307	; 0xf363
d0013cac:	2601e02a 	strcs	lr, [r1], -sl, lsr #32
d0013cb0:	2301e7d0 	movwcs	lr, #6096	; 0x17d0
d0013cb4:	2301e7d9 	movwcs	lr, #6105	; 0x17d9
d0013cb8:	f04fe7d9 			; <UNDEFINED> instruction: 0xf04fe7d9
d0013cbc:	e7e10b01 	strb	r0, [r1, r1, lsl #22]!
d0013cc0:	f1b82701 			; <UNDEFINED> instruction: 0xf1b82701
d0013cc4:	d0ef0f00 	rscle	r0, pc, r0, lsl #30
d0013cc8:	0f00f1bb 	svceq	0x0000f1bb
d0013ccc:	6da7d108 	stfvsd	f5, [r7, #32]!
d0013cd0:	f47f2f00 			; <UNDEFINED> instruction: 0xf47f2f00
d0013cd4:	4b96aef2 	blmi	0xce5bf8a4
d0013cd8:	e7a0447b 			; <UNDEFINED> instruction: 0xe7a0447b
d0013cdc:	e7f02704 	ldrb	r2, [r0, r4, lsl #14]!
d0013ce0:	f0402a0e 			; <UNDEFINED> instruction: 0xf0402a0e
d0013ce4:	f44f8112 	vst4.8	{d24,d26,d28,d30}, [pc :64], r2
d0013ce8:	fb03731a 	blx	0xd00f095a
d0013cec:	f5034305 			; <UNDEFINED> instruction: 0xf5034305
d0013cf0:	8d1f3368 	ldchi	3, cr3, [pc, #-416]	; 0xd0013b58
d0013cf4:	f1a200bf 			; <UNDEFINED> instruction: 0xf1a200bf
d0013cf8:	f04f030e 			; <UNDEFINED> instruction: 0xf04f030e
d0013cfc:	425e0b00 	subsmi	r0, lr, #0, 22
d0013d00:	465b415e 			; <UNDEFINED> instruction: 0x465b415e
d0013d04:	4620215b 			; <UNDEFINED> instruction: 0x4620215b
d0013d08:	f7ff9303 			; <UNDEFINED> instruction: 0xf7ff9303
d0013d0c:	b378f8fd 	cmnlt	r8, #16580608	; 0xfd0000	; <UNPREDICTABLE>
d0013d10:	ea539b03 	b	0xd14fa924
d0013d14:	d115030b 	tstle	r5, fp, lsl #6
d0013d18:	2f006da7 	svccs	0x00006da7
d0013d1c:	aecdf47f 	mcrge	4, 6, pc, cr13, cr15, {3}	; <UNPREDICTABLE>
d0013d20:	447b4b84 	ldrbtmi	r4, [fp], #-2948	; 0xfffff47c
d0013d24:	2b5be77b 	blcs	0xd170db18
d0013d28:	3701d107 	strcc	sp, [r1, -r7, lsl #2]
d0013d2c:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0013d30:	b947f8cb 	stmdblt	r7, {r0, r1, r3, r6, r7, fp, ip, sp, lr, pc}^
d0013d34:	2704b9a6 	strcs	fp, [r4, -r6, lsr #19]
d0013d38:	2b5de01a 	blcs	0xd178bda8
d0013d3c:	f107bf08 			; <UNDEFINED> instruction: 0xf107bf08
d0013d40:	e7f337ff 	udf	#13183	; 0x337f
d0013d44:	6ae32701 	bvs	0xcf8dd950
d0013d48:	7f80f5b3 	svcvc	0x0080f5b3
d0013d4c:	6da2d002 	stcvs	0, cr13, [r2, #8]!
d0013d50:	d0e82a00 	rscle	r2, r8, r0, lsl #20
d0013d54:	46204978 			; <UNDEFINED> instruction: 0x46204978
d0013d58:	f7fc4479 			; <UNDEFINED> instruction: 0xf7fc4479
d0013d5c:	e6acfa89 	strt	pc, [ip], r9, lsl #21
d0013d60:	731af44f 	tstvc	sl, #1325400064	; 0x4f000000	; <UNPREDICTABLE>
d0013d64:	4305fb03 	movwmi	pc, #23299	; 0x5b03	; <UNPREDICTABLE>
d0013d68:	3368f503 	msrcc	SPSR_f, #12582912	; 0xc00000
d0013d6c:	00bf8d1f 	adcseq	r8, pc, pc, lsl sp	; <UNPREDICTABLE>
d0013d70:	447b4b72 	ldrbtmi	r4, [fp], #-2930	; 0xfffff48e
d0013d74:	3a90ee08 	bcc	0xce44f59c
d0013d78:	2b2e6ae3 	blcs	0xd0bae90c
d0013d7c:	f5b3d014 			; <UNDEFINED> instruction: 0xf5b3d014
d0013d80:	f47f7f91 			; <UNDEFINED> instruction: 0xf47f7f91
d0013d84:	f1bbaf10 			; <UNDEFINED> instruction: 0xf1bbaf10
d0013d88:	d1170f00 	tstle	r7, r0, lsl #30
d0013d8c:	2b006da3 	blcs	0xd002f420
d0013d90:	ae93f47f 	mrcge	4, 4, APSR_nzcv, cr3, cr15, {3}
d0013d94:	447b4b6a 	ldrbtmi	r4, [fp], #-2922	; 0xfffff496
d0013d98:	9b0065a3 	blls	0xd002d42c
d0013d9c:	9b0165e3 	blls	0xd006d530
d0013da0:	a918e9c4 	ldmdbge	r8, {r2, r6, r7, r8, fp, sp, lr, pc}
d0013da4:	e68866a3 	str	r6, [r8], r3, lsr #13
d0013da8:	0f00f1bb 	svceq	0x0000f1bb
d0013dac:	6da7d006 	stcvs	0, cr13, [r7, #24]!
d0013db0:	f47f2f00 			; <UNDEFINED> instruction: 0xf47f2f00
d0013db4:	4b63ae82 	blmi	0xd18ff7c4
d0013db8:	e730447b 			; <UNDEFINED> instruction: 0xe730447b
d0013dbc:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0013dc0:	b936f883 	ldmdblt	r6!, {r0, r1, r7, fp, ip, sp, lr, pc}
d0013dc4:	2b006da3 	blcs	0xd002f458
d0013dc8:	ae77f47f 	mrcge	4, 3, APSR_nzcv, cr7, cr15, {3}
d0013dcc:	447b4b5e 	ldrbtmi	r4, [fp], #-2910	; 0xfffff4a2
d0013dd0:	69a3e7e2 	stmibvs	r3!, {r1, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d0013dd4:	2a90ee18 	bcs	0xce44f63c
d0013dd8:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d0013ddc:	ee084620 	cfmadd32	mvax1, mvfx4, mvfx8, mvfx0
d0013de0:	69e33a10 	stmibvs	r3!, {r4, r9, fp, ip, sp}^
d0013de4:	6a639307 	bvs	0xd18f8a08
d0013de8:	6aa39303 	bvs	0xce8f89fc
d0013dec:	f8949306 			; <UNDEFINED> instruction: 0xf8949306
d0013df0:	93053030 	movwls	r3, #20528	; 0x5030
d0013df4:	93046b63 	movwls	r6, #19299	; 0x4b63
d0013df8:	f894f7ff 			; <UNDEFINED> instruction: 0xf894f7ff
d0013dfc:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0013e00:	f44fae5c 			; <UNDEFINED> instruction: 0xf44fae5c
d0013e04:	2700731a 	smladcs	r0, sl, r3, r7
d0013e08:	fb05fb03 	blx	0xd0192a1e
d0013e0c:	f50b9b07 			; <UNDEFINED> instruction: 0xf50b9b07
d0013e10:	44a33867 	strtmi	r3, [r3], #2151	; 0x867
d0013e14:	78f4f508 	ldmvc	r4!, {r3, r8, sl, ip, sp, lr, pc}^
d0013e18:	3b68f50b 	blcc	0xd1a5124c
d0013e1c:	f89b44a0 			; <UNDEFINED> instruction: 0xf89b44a0
d0013e20:	42ba202a 	adcsmi	r2, sl, #42	; 0x2a
d0013e24:	f44fd818 	vst2.8	{d29-d30}, [pc :64], r8
d0013e28:	435d731a 	cmpmi	sp, #1744830464	; 0x68000000
d0013e2c:	f5031963 			; <UNDEFINED> instruction: 0xf5031963
d0013e30:	f8933368 			; <UNDEFINED> instruction: 0xf8933368
d0013e34:	42bb302a 	adcsmi	r3, fp, #42	; 0x2a
d0013e38:	6da7d11c 	stfvsd	f5, [r7, #112]!	; 0x70
d0013e3c:	f47f2f00 			; <UNDEFINED> instruction: 0xf47f2f00
d0013e40:	4b42ae3c 	blmi	0xd10bf738
d0013e44:	65a3447b 	strvs	r4, [r3, #1147]!	; 0x47b
d0013e48:	65e39b03 	strbvs	r9, [r3, #2819]!	; 0xb03
d0013e4c:	66239b06 	strtvs	r9, [r3], -r6, lsl #22
d0013e50:	66639b05 	strbtvs	r9, [r3], -r5, lsl #22
d0013e54:	e6e89b04 	strbt	r9, [r8], r4, lsl #22
d0013e58:	1004f8d8 	ldrdne	pc, [r4], -r8
d0013e5c:	2a10ee18 	bcs	0xd044f6c4
d0013e60:	0b24f858 	bleq	0xd0951fc8
d0013e64:	f7fc9307 			; <UNDEFINED> instruction: 0xf7fc9307
d0013e68:	9b07fc3d 	blls	0xd0212f64
d0013e6c:	d1da2800 	bicsle	r2, sl, r0, lsl #16
d0013e70:	e7d43701 	ldrb	r3, [r4, r1, lsl #14]
d0013e74:	fb032324 	blx	0xd00dcb0e
d0013e78:	44275707 	strtmi	r5, [r7], #-1799	; 0xfffff8f9
d0013e7c:	3767f507 	strbcc	pc, [r7, -r7, lsl #10]!	; <UNPREDICTABLE>
d0013e80:	5208f897 	andpl	pc, r8, #9895936	; 0x970000
d0013e84:	b209f897 	andlt	pc, r9, #9895936	; 0x970000
d0013e88:	03fff1b5 	mvnseq	pc, #1073741869	; 0x4000002d
d0013e8c:	2301bf18 	movwcs	fp, #7960	; 0x1f18
d0013e90:	0f00f1bb 	svceq	0x0000f1bb
d0013e94:	2dffd10d 	ldfcsp	f5, [pc, #52]!	; 0xd0013ed0
d0013e98:	f44fd00a 	vst4.8	{d29-d32}, [pc], sl
d0013e9c:	fb03731a 	blx	0xd00f0b0e
d0013ea0:	f5034305 			; <UNDEFINED> instruction: 0xf5034305
d0013ea4:	8d1f3368 	ldchi	3, cr3, [pc, #-416]	; 0xd0013d0c
d0013ea8:	00bf4633 	adcseq	r4, pc, r3, lsr r6	; <UNPREDICTABLE>
d0013eac:	e763461e 			; <UNDEFINED> instruction: 0xe763461e
d0013eb0:	2704465b 	smlsdcs	r4, fp, r6, r4
d0013eb4:	6da7e7fa 	stcvs	7, cr14, [r7, #1000]!	; 0x3e8
d0013eb8:	f47f2f00 			; <UNDEFINED> instruction: 0xf47f2f00
d0013ebc:	4d24adfe 	stcmi	13, cr10, [r4, #-1016]!	; 0xfffffc08
d0013ec0:	6aa16a60 	bvs	0xce86e848
d0013ec4:	f894447d 			; <UNDEFINED> instruction: 0xf894447d
d0013ec8:	6b632030 	blvs	0xd18dbf90
d0013ecc:	5016e9c4 	andspl	lr, r6, r4, asr #19
d0013ed0:	1218e9c4 	andsne	lr, r8, #196, 18	; 0x310000
d0013ed4:	f1b8e6a9 			; <UNDEFINED> instruction: 0xf1b8e6a9
d0013ed8:	f47f0f00 			; <UNDEFINED> instruction: 0xf47f0f00
d0013edc:	2601af01 	strcs	sl, [r1], -r1, lsl #30
d0013ee0:	f04f2704 			; <UNDEFINED> instruction: 0xf04f2704
d0013ee4:	e6df0b01 	ldrb	r0, [pc], r1, lsl #22
d0013ee8:	fb032330 	blx	0xd00dcbb2
d0013eec:	f5004000 			; <UNDEFINED> instruction: 0xf5004000
d0013ef0:	f8902090 			; <UNDEFINED> instruction: 0xf8902090
d0013ef4:	f8902659 			; <UNDEFINED> instruction: 0xf8902659
d0013ef8:	f8b0565a 			; <UNDEFINED> instruction: 0xf8b0565a
d0013efc:	e6a11662 	strt	r1, [r1], r2, ror #12
d0013f00:	d1e82e00 	mvnle	r2, r0, lsl #28
d0013f04:	0f00f1b8 	svceq	0x0000f1b8
d0013f08:	2704d0ea 	strcs	sp, [r4, -sl, ror #1]
d0013f0c:	bf00e6f3 	svclt	0x0000e6f3
d0013f10:	000c5014 	andeq	r5, ip, r4, lsl r0
d0013f14:	fffffdb0 			; <UNDEFINED> instruction: 0xfffffdb0
d0013f18:	fffffed3 			; <UNDEFINED> instruction: 0xfffffed3
d0013f1c:	fffffd3e 			; <UNDEFINED> instruction: 0xfffffd3e
d0013f20:	fffffd2a 			; <UNDEFINED> instruction: 0xfffffd2a
d0013f24:	fffffe51 			; <UNDEFINED> instruction: 0xfffffe51
d0013f28:	fffffca2 			; <UNDEFINED> instruction: 0xfffffca2
d0013f2c:	fffffc87 			; <UNDEFINED> instruction: 0xfffffc87
d0013f30:	fffffbf8 			; <UNDEFINED> instruction: 0xfffffbf8
d0013f34:	fffffbc7 			; <UNDEFINED> instruction: 0xfffffbc7
d0013f38:	fffffccf 			; <UNDEFINED> instruction: 0xfffffccf
d0013f3c:	fffffc07 			; <UNDEFINED> instruction: 0xfffffc07
d0013f40:	fffffb7d 			; <UNDEFINED> instruction: 0xfffffb7d
d0013f44:	fffffb7c 			; <UNDEFINED> instruction: 0xfffffb7c
d0013f48:	fffffb85 			; <UNDEFINED> instruction: 0xfffffb85
d0013f4c:	fffffb54 			; <UNDEFINED> instruction: 0xfffffb54
d0013f50:	fffffaed 			; <UNDEFINED> instruction: 0xfffffaed

Disassembly of section .text.initialize_large_zero.constprop.0:

d0013f7c <.text.initialize_large_zero.constprop.0>:
d0013f7c:	4c16b513 	cfldr32mi	mvfx11, [r6], {19}
d0013f80:	4a16217b 	bmi	0xd059c574
d0013f84:	447a447c 	ldrbtmi	r4, [sl], #-1148	; 0xfffffb84
d0013f88:	92014620 	andls	r4, r1, #32, 12	; 0x2000000
d0013f8c:	ffcaf7fe 			; <UNDEFINED> instruction: 0xffcaf7fe
d0013f90:	6ae3b300 	bvs	0xcf900b98
d0013f94:	7381f5a3 	orrvc	pc, r1, #683671552	; 0x28c00000
d0013f98:	d8022b01 	stmdale	r2, {r0, r8, r9, fp, sp}
d0013f9c:	9a016a23 	bls	0xd006e830
d0013fa0:	490fb143 	stmdbmi	pc, {r0, r1, r6, r8, ip, sp, pc}	; <UNPREDICTABLE>
d0013fa4:	4479480f 	ldrbtmi	r4, [r9], #-2063	; 0xfffff7f1
d0013fa8:	b0024478 	andlt	r4, r2, r8, ror r4
d0013fac:	4010e8bd 			; <UNDEFINED> instruction: 0x4010e8bd
d0013fb0:	b95ef7fc 	ldmdblt	lr, {r2, r3, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}^
d0013fb4:	92014620 	andls	r4, r1, #32, 12	; 0x2000000
d0013fb8:	ff86f7fe 			; <UNDEFINED> instruction: 0xff86f7fe
d0013fbc:	4620212c 	strtmi	r2, [r0], -ip, lsr #2
d0013fc0:	ffa2f7fe 			; <UNDEFINED> instruction: 0xffa2f7fe
d0013fc4:	217d9a01 	cmncs	sp, r1, lsl #20
d0013fc8:	b0024620 	andlt	r4, r2, r0, lsr #12
d0013fcc:	4010e8bd 			; <UNDEFINED> instruction: 0x4010e8bd
d0013fd0:	bfa8f7fe 	svclt	0x00a8f7fe
d0013fd4:	bd10b002 	ldclt	0, cr11, [r0, #-8]
d0013fd8:	00014240 	andeq	r4, r1, r0, asr #4
d0013fdc:	ffffffca 			; <UNDEFINED> instruction: 0xffffffca
d0013fe0:	ffffffaa 			; <UNDEFINED> instruction: 0xffffffaa
d0013fe4:	0001421c 	andeq	r4, r1, ip, lsl r2

Disassembly of section .text.add_local.constprop.0:

d0014024 <.text.add_local.constprop.0>:
d0014024:	e92db084 	push	{r2, r7, ip, sp, pc}
d0014028:	4d3447f0 	ldcmi	7, cr4, [r4, #-960]!	; 0xfffffc40
d001402c:	447dac08 	ldrbtmi	sl, [sp], #-3080	; 0xfffff3f8
d0014030:	000fe884 	andeq	lr, pc, r4, lsl #17
d0014034:	9a094601 	bls	0xd0265840
d0014038:	f8dd4628 			; <UNDEFINED> instruction: 0xf8dd4628
d001403c:	f8dda02c 			; <UNDEFINED> instruction: 0xf8dda02c
d0014040:	f89d9030 			; <UNDEFINED> instruction: 0xf89d9030
d0014044:	9e0f8038 	mcrls	0, 0, r8, cr15, cr8, {1}
d0014048:	fbc2f7fc 	blx	0xcf0d2042
d001404c:	db1b2800 	blle	0xd06de054
d0014050:	fb032330 	blx	0xd00dcd1a
d0014054:	f5055000 			; <UNDEFINED> instruction: 0xf5055000
d0014058:	f5002392 			; <UNDEFINED> instruction: 0xf5002392
d001405c:	f8d32090 			; <UNDEFINED> instruction: 0xf8d32090
d0014060:	f8903240 			; <UNDEFINED> instruction: 0xf8903240
d0014064:	429a2658 	addsmi	r2, sl, #88, 12	; 0x5800000
d0014068:	6dacd10e 	stfvsd	f5, [ip, #56]!	; 0x38
d001406c:	d1422c00 	cmple	r2, r0, lsl #24
d0014070:	66ae4b23 	strtvs	r4, [lr], r3, lsr #22
d0014074:	e9c5447b 	stmib	r5, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0014078:	e9c59818 	stmib	r5, {r3, r4, fp, ip, pc}^
d001407c:	46203a16 			; <UNDEFINED> instruction: 0x46203a16
d0014080:	47f0e8bd 			; <UNDEFINED> instruction: 0x47f0e8bd
d0014084:	4770b004 	ldrbmi	fp, [r0, -r4]!
d0014088:	447b4b1e 	ldrbtmi	r4, [fp], #-2846	; 0xfffff4e2
d001408c:	2792f503 	ldrcs	pc, [r2, r3, lsl #10]
d0014090:	4238f8d7 	eorsmi	pc, r8, #14090240	; 0xd70000
d0014094:	d1092c40 	tstle	r9, r0, asr #24
d0014098:	bb646d9c 	bllt	0xd192f710
d001409c:	669e4a1a 			; <UNDEFINED> instruction: 0x669e4a1a
d00140a0:	e9c3447a 	stmib	r3, {r1, r3, r4, r5, r6, sl, lr}^
d00140a4:	e9c39818 	stmib	r3, {r3, r4, fp, ip, pc}^
d00140a8:	e7e82a16 			; <UNDEFINED> instruction: 0xe7e82a16
d00140ac:	f1042230 			; <UNDEFINED> instruction: 0xf1042230
d00140b0:	ae080801 	cdpge	8, 0, cr0, cr8, cr1, {0}
d00140b4:	fb022100 	blx	0xd009c4be
d00140b8:	f8973304 			; <UNDEFINED> instruction: 0xf8973304
d00140bc:	f8c79240 			; <UNDEFINED> instruction: 0xf8c79240
d00140c0:	f5038238 			; <UNDEFINED> instruction: 0xf5038238
d00140c4:	f50a2a90 			; <UNDEFINED> instruction: 0xf50a2a90
d00140c8:	462865c7 	strtmi	r6, [r8], -r7, asr #11
d00140cc:	faa0f00d 	blx	0xce850108
d00140d0:	9658f88a 	ldrbls	pc, [r8], -sl, lsl #17	; <UNPREDICTABLE>
d00140d4:	c50fce0f 	strgt	ip, [pc, #-3599]	; 0xd00132cd
d00140d8:	000fe896 	muleq	pc, r6, r8	; <UNPREDICTABLE>
d00140dc:	000fe885 	andeq	lr, pc, r5, lsl #17
d00140e0:	3040f89d 	umaalcc	pc, r0, sp, r8	; <UNPREDICTABLE>
d00140e4:	3659f88a 	ldrbcc	pc, [r9], -sl, lsl #17	; <UNPREDICTABLE>
d00140e8:	323cf8d7 	eorscc	pc, ip, #14090240	; 0xd70000
d00140ec:	d9c64598 	stmible	r6, {r3, r4, r7, r8, sl, lr}^
d00140f0:	823cf8c7 	eorshi	pc, ip, #13041664	; 0xc70000
d00140f4:	2400e7c3 	strcs	lr, [r0], #-1987	; 0xfffff83d
d00140f8:	bf00e7c1 	svclt	0x0000e7c1
d00140fc:	00014196 	muleq	r1, r6, r1
d0014100:	ffffff70 			; <UNDEFINED> instruction: 0xffffff70
d0014104:	0001413a 	andeq	r4, r1, sl, lsr r1
d0014108:	ffffff60 			; <UNDEFINED> instruction: 0xffffff60

Disassembly of section .text.record_definition.constprop.0:

d0014380 <.text.record_definition.constprop.0>:
d0014380:	e92db084 	push	{r2, r7, ip, sp, pc}
d0014384:	f5ad4ff0 			; <UNDEFINED> instruction: 0xf5ad4ff0
d0014388:	f8df7d33 			; <UNDEFINED> instruction: 0xf8df7d33
d001438c:	46065508 	strmi	r5, [r6], -r8, lsl #10
d0014390:	447dacbc 	ldrbtmi	sl, [sp], #-3260	; 0xfffff344
d0014394:	a310f8dd 	tstge	r0, #14483456	; 0xdd0000	; <UNPREDICTABLE>
d0014398:	000fe884 	andeq	lr, pc, r4, lsl #17
d001439c:	217b9bbf 	ldrhcs	r9, [fp, #-191]!	; 0xffffff41
d00143a0:	24f4f8df 	ldrbtcs	pc, [r4], #2271	; 0x8df	; <UNPREDICTABLE>
d00143a4:	93004628 	movwls	r4, #1576	; 0x628
d00143a8:	447a9bc0 	ldrbtmi	r9, [sl], #-3008	; 0xfffff440
d00143ac:	93019fbd 	movwls	r9, #8125	; 0x1fbd
d00143b0:	3308f89d 	movwcc	pc, #34973	; 0x889d	; <UNPREDICTABLE>
d00143b4:	9bc39302 	blls	0xcf0f8fc4
d00143b8:	f7fe9303 			; <UNDEFINED> instruction: 0xf7fe9303
d00143bc:	b910fdb3 	ldmdblt	r0, {r0, r1, r4, r5, r7, r8, sl, fp, ip, sp, lr, pc}
d00143c0:	34fff04f 	ldrbtcc	pc, [pc], #79	; 0xd00143c8	; <UNPREDICTABLE>
d00143c4:	9bc5e232 	blls	0xcf18cc94
d00143c8:	f0402b00 			; <UNDEFINED> instruction: 0xf0402b00
d00143cc:	465380a4 	ldrbmi	r8, [r3], -r4, lsr #1
d00143d0:	4631463a 			; <UNDEFINED> instruction: 0x4631463a
d00143d4:	f7fc4628 			; <UNDEFINED> instruction: 0xf7fc4628
d00143d8:	f08af993 			; <UNDEFINED> instruction: 0xf08af993
d00143dc:	46040301 	strmi	r0, [r4], -r1, lsl #6
d00143e0:	4631463a 			; <UNDEFINED> instruction: 0x4631463a
d00143e4:	f7fc4628 			; <UNDEFINED> instruction: 0xf7fc4628
d00143e8:	2800f98b 	stmdacs	r0, {r0, r1, r3, r7, r8, fp, ip, sp, lr, pc}
d00143ec:	824cf2c0 	subhi	pc, ip, #192, 4
d00143f0:	2b006dab 	blcs	0xd002faa4
d00143f4:	f8dfd1e4 			; <UNDEFINED> instruction: 0xf8dfd1e4
d00143f8:	447b34a4 	ldrbtmi	r3, [fp], #-1188	; 0xfffffb5c
d00143fc:	9b0065ab 	blls	0xd002dab0
d0014400:	9b0165eb 	blls	0xd006dbb4
d0014404:	9b02662b 	blls	0xd00adcb8
d0014408:	9b03666b 	blls	0xd00eddbc
d001440c:	e7d766ab 	ldrb	r6, [r7, fp, lsr #13]
d0014410:	3275f505 	rsbscc	pc, r5, #20971520	; 0x1400000
d0014414:	3388f8d2 	orrcc	pc, r8, #13762560	; 0xd20000
d0014418:	d1062b18 	tstle	r6, r8, lsl fp
d001441c:	2b006dab 	blcs	0xd002fad0
d0014420:	f8dfd1ce 			; <UNDEFINED> instruction: 0xf8dfd1ce
d0014424:	447b347c 	ldrbtmi	r3, [fp], #-1148	; 0xfffffb84
d0014428:	1c59e7e8 	mrrcne	7, 14, lr, r9, cr8
d001442c:	469b7a2e 	ldrmi	r7, [fp], lr, lsr #20
d0014430:	1388f8c2 	orrne	pc, r8, #12713984	; 0xc20000
d0014434:	721af44f 	andsvc	pc, sl, #1325400064	; 0x4f000000
d0014438:	fb0299c5 	blx	0xd00bab56
d001443c:	f5055503 			; <UNDEFINED> instruction: 0xf5055503
d0014440:	f5053767 			; <UNDEFINED> instruction: 0xf5053767
d0014444:	f5073568 			; <UNDEFINED> instruction: 0xf5073568
d0014448:	463877e4 	ldrtmi	r7, [r8], -r4, ror #15
d001444c:	f8e0f00d 			; <UNDEFINED> instruction: 0xf8e0f00d
d0014450:	7c3cf50d 	cfldr32vc	mvfx15, [ip], #-52	; 0xffffffcc
d0014454:	a02bf885 	eorge	pc, fp, r5, lsl #17
d0014458:	602ef885 	eorvs	pc, lr, r5, lsl #17
d001445c:	000fe8bc 			; <UNDEFINED> instruction: 0x000fe8bc
d0014460:	e89cc70f 	ldm	ip, {r0, r1, r2, r3, r8, r9, sl, lr, pc}
d0014464:	e887000f 	stm	r7, {r0, r1, r2, r3}
d0014468:	ad18000f 	ldcge	0, cr0, [r8, #-60]	; 0xffffffc4
d001446c:	721af44f 	andsvc	pc, sl, #1325400064	; 0x4f000000
d0014470:	46282100 	strtmi	r2, [r8], -r0, lsl #2
d0014474:	f00d462e 			; <UNDEFINED> instruction: 0xf00d462e
d0014478:	9bc5f8cb 	blls	0xcf1927ac
d001447c:	d04e2b00 	suble	r2, lr, r0, lsl #22
d0014480:	f10dafc6 			; <UNDEFINED> instruction: 0xf10dafc6
d0014484:	cf0f093c 	svcgt	0x000f093c
d0014488:	e897c60f 	ldm	r7, {r0, r1, r2, r3, r9, sl, lr, pc}
d001448c:	e886000f 	stm	r6, {r0, r1, r2, r3}
d0014490:	9bc5000f 	blls	0xcf1544d4
d0014494:	640cf8df 	strvs	pc, [ip], #-2271	; 0xfffff721
d0014498:	3264f885 	rsbcc	pc, r4, #8716288	; 0x850000
d001449c:	447e2301 	ldrbtmi	r2, [lr], #-769	; 0xfffffcff
d00144a0:	a263f885 	rsbge	pc, r3, #8716288	; 0x850000
d00144a4:	3265f885 	rsbcc	pc, r5, #8716288	; 0x850000
d00144a8:	f8857a33 			; <UNDEFINED> instruction: 0xf8857a33
d00144ac:	6db33266 	lfmvs	f3, 4, [r3, #408]!	; 0x198
d00144b0:	6af3b92b 	bvs	0xcfd02964
d00144b4:	d0022b7d 	andle	r2, r2, sp, ror fp
d00144b8:	7f80f5b3 	svcvc	0x0080f5b3
d00144bc:	4dfad131 	ldfmip	f5, [sl, #196]!	; 0xc4
d00144c0:	4afa217d 	bmi	0xcfe9cabc
d00144c4:	447a447d 	ldrbtmi	r4, [sl], #-1149	; 0xfffffb83
d00144c8:	f7fe4628 			; <UNDEFINED> instruction: 0xf7fe4628
d00144cc:	2800fd2b 	stmdacs	r0, {r0, r1, r3, r5, r8, sl, fp, ip, sp, lr, pc}
d00144d0:	af76f43f 	svcge	0x0076f43f
d00144d4:	af189bc5 	svcge	0x00189bc5
d00144d8:	3518b13b 	ldrcc	fp, [r8, #-315]	; 0xfffffec5
d00144dc:	cd0f463e 	stcgt	6, cr4, [pc, #-248]	; 0xd00143ec
d00144e0:	e895c60f 	ldm	r5, {r0, r1, r2, r3, r9, sl, lr, pc}
d00144e4:	e886000f 	stm	r6, {r0, r1, r2, r3}
d00144e8:	f897000f 			; <UNDEFINED> instruction: 0xf897000f
d00144ec:	2b003262 	blcs	0xd0020e7c
d00144f0:	813cf040 	teqhi	ip, r0, asr #32	; <UNPREDICTABLE>
d00144f4:	447b4bee 	ldrbtmi	r4, [fp], #-3054	; 0xfffff412
d00144f8:	2a006d9a 	bcs	0xd002fb68
d00144fc:	af60f47f 	svcge	0x0060f47f
d0014500:	447a4aec 	ldrbtmi	r4, [sl], #-2796	; 0xfffff514
d0014504:	9a00659a 	bls	0xd002db74
d0014508:	9a0165da 	bls	0xd006dc78
d001450c:	9a02661a 	bls	0xd00add7c
d0014510:	9a03665a 	bls	0xd00ede80
d0014514:	f04fe0dd 			; <UNDEFINED> instruction: 0xf04fe0dd
d0014518:	46a334ff 			; <UNDEFINED> instruction: 0x46a334ff
d001451c:	afbce7a5 	svcge	0x00bce7a5
d0014520:	f89de7af 			; <UNDEFINED> instruction: 0xf89de7af
d0014524:	2b1032c2 	blcs	0xd0421034
d0014528:	49e3d105 	stmibmi	r3!, {r0, r2, r8, ip, lr, pc}^
d001452c:	44794630 	ldrbtmi	r4, [r9], #-1584	; 0xfffff9d0
d0014530:	fe9ef7fb 	mrc2	7, 4, pc, cr14, cr11, {7}
d0014534:	23ffe744 	mvnscs	lr, #68, 14	; 0x1100000
d0014538:	1107f240 	tstne	r7, r0, asr #4	; <UNPREDICTABLE>
d001453c:	f8c94630 			; <UNDEFINED> instruction: 0xf8c94630
d0014540:	f7fe3000 			; <UNDEFINED> instruction: 0xf7fe3000
d0014544:	b1e8fce1 	mvnlt	pc, r1, ror #25
d0014548:	f8c923ff 			; <UNDEFINED> instruction: 0xf8c923ff
d001454c:	4ddb3000 	ldclmi	0, cr3, [fp]
d0014550:	447d212a 	ldrbtmi	r2, [sp], #-298	; 0xfffffed6
d0014554:	f7fe4628 			; <UNDEFINED> instruction: 0xf7fe4628
d0014558:	9006fcd7 	ldrdls	pc, [r6], -r7
d001455c:	d14c2800 	cmple	ip, r0, lsl #16
d0014560:	3000f8d9 	ldrdcc	pc, [r0], -r9
d0014564:	d0482bff 	strdle	r2, [r8], #-191	; 0xffffff41
d0014568:	721af44f 	andsvc	pc, sl, #1325400064	; 0x4f000000
d001456c:	5303fb02 	movwpl	pc, #15106	; 0x3b02	; <UNPREDICTABLE>
d0014570:	3368f503 	msrcc	SPSR_f, #12582912	; 0xc00000
d0014574:	302df893 	mlacc	sp, r3, r8, pc	; <UNPREDICTABLE>
d0014578:	d13e2b00 	teqle	lr, r0, lsl #22
d001457c:	462849d0 			; <UNDEFINED> instruction: 0x462849d0
d0014580:	e7d54479 			; <UNDEFINED> instruction: 0xe7d54479
d0014584:	f2406af2 	vpmin.s8	q11, q8, q9
d0014588:	429a1301 	addsmi	r1, sl, #67108864	; 0x4000000
d001458c:	4630d118 			; <UNDEFINED> instruction: 0x4630d118
d0014590:	1206e9d6 	andne	lr, r6, #3506176	; 0x358000
d0014594:	f961f7fc 			; <UNDEFINED> instruction: 0xf961f7fc
d0014598:	db112800 	blle	0xd045e5a0
d001459c:	e9d64630 	ldmib	r6, {r4, r5, r9, sl, lr}^
d00145a0:	f7fc1206 			; <UNDEFINED> instruction: 0xf7fc1206
d00145a4:	2324f95a 	msrcs	CPSR_s, #1474560	; 0x168000
d00145a8:	6000fb03 	andvs	pc, r0, r3, lsl #22
d00145ac:	3075f500 	rsbscc	pc, r5, r0, lsl #10
d00145b0:	33acf890 			; <UNDEFINED> instruction: 0x33acf890
d00145b4:	d1032bff 	strdle	r2, [r3, -pc]
d00145b8:	f7fe4630 			; <UNDEFINED> instruction: 0xf7fe4630
d00145bc:	e7c6fc85 	strb	pc, [r6, r5, lsl #25]	; <UNPREDICTABLE>
d00145c0:	f24048c0 	vadd.i8	q10, q8, q0
d00145c4:	4478131b 	ldrbtmi	r1, [r8], #-795	; 0xfffffce5
d00145c8:	429a6ac2 	addsmi	r6, sl, #794624	; 0xc2000
d00145cc:	f7fed103 			; <UNDEFINED> instruction: 0xf7fed103
d00145d0:	2800ff9b 	stmdacs	r0, {r0, r1, r3, r4, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d00145d4:	48bcd1b8 	ldmmi	ip!, {r3, r4, r5, r7, r8, ip, lr, pc}
d00145d8:	44784649 	ldrbtmi	r4, [r8], #-1609	; 0xfffff9b7
d00145dc:	fe9ef7fe 	mrc2	7, 4, pc, cr14, cr14, {7}
d00145e0:	d1b42800 			; <UNDEFINED> instruction: 0xd1b42800
d00145e4:	0f00f1ba 	svceq	0x0000f1ba
d00145e8:	49b8d104 	ldmibmi	r8!, {r2, r8, ip, lr, pc}
d00145ec:	48b84479 	ldmmi	r8!, {r0, r3, r4, r5, r6, sl, lr}
d00145f0:	e79d4478 			; <UNDEFINED> instruction: 0xe79d4478
d00145f4:	447949b7 	ldrbtmi	r4, [r9], #-2487	; 0xfffff649
d00145f8:	4db7e7f9 	ldcmi	7, cr14, [r7, #996]!	; 0x3e4
d00145fc:	447daf10 	ldrbtmi	sl, [sp], #-3856	; 0xfffff0f0
d0014600:	0c18f105 	ldfeqd	f7, [r8], {5}
d0014604:	000fe8bc 			; <UNDEFINED> instruction: 0x000fe8bc
d0014608:	e89cc70f 	ldm	ip, {r0, r1, r2, r3, r8, r9, sl, lr, pc}
d001460c:	e887000f 	stm	r7, {r0, r1, r2, r3}
d0014610:	69ab000f 	stmibvs	fp!, {r0, r1, r2, r3}
d0014614:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d0014618:	46284ab0 			; <UNDEFINED> instruction: 0x46284ab0
d001461c:	69eb930b 	stmibvs	fp!, {r0, r1, r3, r8, r9, ip, pc}^
d0014620:	930a447a 	movwls	r4, #42106	; 0xa47a
d0014624:	93056a6b 	movwls	r6, #23147	; 0x5a6b
d0014628:	93096aab 	movwls	r6, #39595	; 0x9aab
d001462c:	3030f895 	mlascc	r0, r5, r8, pc	; <UNPREDICTABLE>
d0014630:	6b6b9308 	blvs	0xd1af9258
d0014634:	f7fe9307 			; <UNDEFINED> instruction: 0xf7fe9307
d0014638:	2800fc75 	stmdacs	r0, {r0, r2, r4, r5, r6, sl, fp, ip, sp, lr, pc}
d001463c:	aec0f43f 	mcrge	4, 6, pc, cr0, cr15, {1}	; <UNPREDICTABLE>
d0014640:	213b4aa7 	teqcs	fp, r7, lsr #21
d0014644:	447a4628 	ldrbtmi	r4, [sl], #-1576	; 0xfffff9d8
d0014648:	fc6cf7fe 	stc2l	7, cr15, [ip], #-1016	; 0xfffffc08
d001464c:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0014650:	ad18aeb7 	ldcge	14, cr10, [r8, #-732]	; 0xfffffd24
d0014654:	46a82700 	strtmi	r2, [r8], r0, lsl #14
d0014658:	c262f898 	rsbgt	pc, r2, #152, 16	; 0x980000
d001465c:	d31c4567 	tstle	ip, #432013312	; 0x19c00000
d0014660:	2b009b06 	blcs	0xd003b280
d0014664:	f8d9d13c 			; <UNDEFINED> instruction: 0xf8d9d13c
d0014668:	2bff3000 	blcs	0xcffe0670
d001466c:	4a9dd038 	bmi	0xce788754
d0014670:	711af44f 	tstvc	sl, pc, asr #8	; <UNPREDICTABLE>
d0014674:	fb01447a 	blx	0xd0065866
d0014678:	f5032303 			; <UNDEFINED> instruction: 0xf5032303
d001467c:	f8b33368 			; <UNDEFINED> instruction: 0xf8b33368
d0014680:	f1bee028 			; <UNDEFINED> instruction: 0xf1bee028
d0014684:	d12d0f00 			; <UNDEFINED> instruction: 0xd12d0f00
d0014688:	447b4b97 	ldrbtmi	r4, [fp], #-2967	; 0xfffff469
d001468c:	2a006d9a 	bcs	0xd002fcfc
d0014690:	ae96f47f 	mrcge	4, 4, APSR_nzcv, cr6, cr15, {3}
d0014694:	447a4a95 	ldrbtmi	r4, [sl], #-2709	; 0xfffff56b
d0014698:	6a69e013 	bvs	0xd1a8c6ec
d001469c:	f8553524 			; <UNDEFINED> instruction: 0xf8553524
d00146a0:	9b0a0c04 	blls	0xd02976b8
d00146a4:	f7fc9a0b 			; <UNDEFINED> instruction: 0xf7fc9a0b
d00146a8:	b1b8f81d 			; <UNDEFINED> instruction: 0xb1b8f81d
d00146ac:	0f00f1ba 	svceq	0x0000f1ba
d00146b0:	4a8fd111 	bmi	0xce408afc
d00146b4:	4b8f447a 	blmi	0xce3e58a4
d00146b8:	6d99447b 	cfldrsvs	mvf4, [r9, #492]	; 0x1ec
d00146bc:	f47f2900 			; <UNDEFINED> instruction: 0xf47f2900
d00146c0:	659aae7f 	ldrvs	sl, [sl, #3711]	; 0xe7f
d00146c4:	65da9a05 	ldrbvs	r9, [sl, #2565]	; 0xa05
d00146c8:	661a9a09 	ldrvs	r9, [sl], -r9, lsl #20
d00146cc:	665a9a08 	ldrbvs	r9, [sl], -r8, lsl #20
d00146d0:	669a9a07 	ldrvs	r9, [sl], r7, lsl #20
d00146d4:	4a88e674 	bmi	0xce24e0ac
d00146d8:	e7ec447a 			; <UNDEFINED> instruction: 0xe7ec447a
d00146dc:	e7bb3701 	ldr	r3, [fp, r1, lsl #14]!
d00146e0:	0e01f04f 	cdpeq	0, 0, cr15, cr1, cr15, {2}
d00146e4:	f8bdab18 			; <UNDEFINED> instruction: 0xf8bdab18
d00146e8:	930482c0 	movwls	r8, #17088	; 0x42c0
d00146ec:	437ff5c8 	cmnmi	pc, #200, 10	; 0x32000000	; <UNPREDICTABLE>
d00146f0:	457333ff 	ldrbmi	r3, [r3, #-1023]!	; 0xfffffc01
d00146f4:	9a04d3c8 	bls	0xd014961c
d00146f8:	0301f10c 	movweq	pc, #4364	; 0x110c	; <UNPREDICTABLE>
d00146fc:	0f00f1ba 	svceq	0x0000f1ba
d0014700:	f882ad10 			; <UNDEFINED> instruction: 0xf882ad10
d0014704:	f8993262 			; <UNDEFINED> instruction: 0xf8993262
d0014708:	930c3000 	movwls	r3, #49152	; 0xc000
d001470c:	4643bf0c 	strbmi	fp, [r3], -ip, lsl #30
d0014710:	930d2300 	movwls	r2, #54016	; 0xd300
d0014714:	93109b0b 	tstls	r0, #11264	; 0x2c00
d0014718:	93119b0a 	tstls	r1, #10240	; 0x2800
d001471c:	93139b05 	tstls	r3, #5120	; 0x1400
d0014720:	93149b09 	tstls	r4, #9216	; 0x2400
d0014724:	f88d9b08 			; <UNDEFINED> instruction: 0xf88d9b08
d0014728:	9b073058 	blls	0xd01e0890
d001472c:	f04f9317 			; <UNDEFINED> instruction: 0xf04f9317
d0014730:	fb030324 	blx	0xd00d53ca
d0014734:	cd0f2c0c 	stcgt	12, cr2, [pc, #-48]	; 0xd001470c
d0014738:	0720f10c 	streq	pc, [r0, -ip, lsl #2]!
d001473c:	e895c70f 	ldm	r5, {r0, r1, r2, r3, r8, r9, sl, lr, pc}
d0014740:	e887000f 	stm	r7, {r0, r1, r2, r3}
d0014744:	9b0c000f 	blls	0xd0314788
d0014748:	3040f88c 	subcc	pc, r0, ip, lsl #17
d001474c:	f88c9b06 			; <UNDEFINED> instruction: 0xf88c9b06
d0014750:	9b0d3041 	blls	0xd036085c
d0014754:	3042f8ac 	subcc	pc, r2, ip, lsr #17
d0014758:	45f0d006 	ldrbmi	sp, [r0, #6]!
d001475c:	aea7f4bf 	mcrge	4, 5, pc, cr7, cr15, {5}	; <UNPREDICTABLE>
d0014760:	f8a39b04 			; <UNDEFINED> instruction: 0xf8a39b04
d0014764:	e6a2e260 	strt	lr, [r2], r0, ror #4
d0014768:	e7f944c6 	ldrb	r4, [r9, r6, asr #9]!
d001476c:	b18b9bc5 	orrlt	r9, fp, r5, asr #23
d0014770:	f04f4e62 			; <UNDEFINED> instruction: 0xf04f4e62
d0014774:	f10d0800 			; <UNDEFINED> instruction: 0xf10d0800
d0014778:	447e0960 	ldrbtmi	r0, [lr], #-2400	; 0xfffff6a0
d001477c:	3567f506 	strbcc	pc, [r7, #-1286]!	; 0xfffffafa	; <UNPREDICTABLE>
d0014780:	3375f506 	cmncc	r5, #25165824	; 0x1800000	; <UNPREDICTABLE>
d0014784:	75e4f505 	strbvc	pc, [r4, #1285]!	; 0x505	; <UNPREDICTABLE>
d0014788:	9b049304 	blls	0xd01393a0
d001478c:	3388f8d3 	orrcc	pc, r8, #13828096	; 0xd30000
d0014790:	d31c4598 	tstle	ip, #152, 10	; 0x26000000
d0014794:	db382c00 	blle	0xd0e1f79c
d0014798:	731af44f 	tstvc	sl, #1325400064	; 0x4f000000	; <UNPREDICTABLE>
d001479c:	a8184958 	ldmdage	r8, {r3, r4, r6, r8, fp, lr}
d00147a0:	44794363 	ldrbtmi	r4, [r9], #-867	; 0xfffffc9d
d00147a4:	3367f503 	msrcc	SPSR_sxc, #12582912	; 0xc00000
d00147a8:	73e4f503 	mvnvc	pc, #12582912	; 0xc00000
d00147ac:	f7fb4419 			; <UNDEFINED> instruction: 0xf7fb4419
d00147b0:	2800ffd0 	stmdacs	r0, {r4, r6, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d00147b4:	f1bad13a 			; <UNDEFINED> instruction: 0xf1bad13a
d00147b8:	d1230f00 			; <UNDEFINED> instruction: 0xd1230f00
d00147bc:	447a4a51 	ldrbtmi	r4, [sl], #-2641	; 0xfffff5af
d00147c0:	447b4b51 	ldrbtmi	r4, [fp], #-2897	; 0xfffff4af
d00147c4:	29006d99 	stmdbcs	r0, {r0, r3, r4, r7, r8, sl, fp, sp, lr}
d00147c8:	adfaf47f 	cfldrdge	mvd15, [sl, #508]!	; 0x1fc
d00147cc:	f895e69a 			; <UNDEFINED> instruction: 0xf895e69a
d00147d0:	b1933264 	orrslt	r3, r3, r4, ror #4
d00147d4:	2266f895 	rsbcs	pc, r6, #9764864	; 0x950000
d00147d8:	429a7a33 	addsmi	r7, sl, #208896	; 0x33000
d00147dc:	e9d9d00d 	ldmib	r9, {r0, r2, r3, ip, lr, pc}^
d00147e0:	e9d52300 	ldmib	r5, {r8, r9, sp}^
d00147e4:	f7fb0100 			; <UNDEFINED> instruction: 0xf7fb0100
d00147e8:	b130ff7d 	teqlt	r0, sp, ror pc	; <UNPREDICTABLE>
d00147ec:	46484629 	strbmi	r4, [r8], -r9, lsr #12
d00147f0:	ffaff7fb 			; <UNDEFINED> instruction: 0xffaff7fb
d00147f4:	4644b108 	strbmi	fp, [r4], -r8, lsl #2
d00147f8:	f108e7ce 			; <UNDEFINED> instruction: 0xf108e7ce
d00147fc:	f5050801 			; <UNDEFINED> instruction: 0xf5050801
d0014800:	e7c2751a 	bfi	r7, sl, (invalid: 10:2)
d0014804:	447a4a41 	ldrbtmi	r4, [sl], #-2625	; 0xfffff5bf
d0014808:	f1bbe7da 			; <UNDEFINED> instruction: 0xf1bbe7da
d001480c:	db140f00 	blle	0xd0518414
d0014810:	f44f483f 	vst2.8	{d20-d21}, [pc :256]
d0014814:	465c721a 			; <UNDEFINED> instruction: 0x465c721a
d0014818:	44784639 	ldrbtmi	r4, [r8], #-1593	; 0xfffff9c7
d001481c:	000bfb02 	andeq	pc, fp, r2, lsl #22
d0014820:	3067f500 	rsbcc	pc, r7, r0, lsl #10
d0014824:	70e4f500 	rscvc	pc, r4, r0, lsl #10
d0014828:	ff00f00c 			; <UNDEFINED> instruction: 0xff00f00c
d001482c:	f50d4620 			; <UNDEFINED> instruction: 0xf50d4620
d0014830:	e8bd7d33 	pop	{r0, r1, r4, r5, r8, sl, fp, ip, sp, lr}
d0014834:	b0044ff0 	strdlt	r4, [r4], -r0
d0014838:	48364770 	ldmdami	r6!, {r4, r5, r6, r8, r9, sl, lr}
d001483c:	f5004478 			; <UNDEFINED> instruction: 0xf5004478
d0014840:	f8d33375 			; <UNDEFINED> instruction: 0xf8d33375
d0014844:	2c184388 	ldccs	3, cr4, [r8], {136}	; 0x88
d0014848:	6d83d10f 	stfvsd	f5, [r3, #60]	; 0x3c
d001484c:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0014850:	4b31adb7 	blmi	0xd0c7ff34
d0014854:	6583447b 	strvs	r4, [r3, #1147]	; 0x47b
d0014858:	65c39b00 	strbvs	r9, [r3, #2816]	; 0xb00
d001485c:	66039b01 	strvs	r9, [r3], -r1, lsl #22
d0014860:	66439b02 	strbvs	r9, [r3], -r2, lsl #22
d0014864:	66839b03 	strvs	r9, [r3], r3, lsl #22
d0014868:	1c62e5aa 	cfstr64ne	mvdx14, [r2], #-680	; 0xfffffd58
d001486c:	f8c34639 			; <UNDEFINED> instruction: 0xf8c34639
d0014870:	f44f2388 	vst2.32	{d18-d21}, [pc], r8
d0014874:	fb02721a 	blx	0xd00b10e6
d0014878:	f5000004 			; <UNDEFINED> instruction: 0xf5000004
d001487c:	f5003067 			; <UNDEFINED> instruction: 0xf5003067
d0014880:	f00c70e4 			; <UNDEFINED> instruction: 0xf00c70e4
d0014884:	e7d1fed3 			; <UNDEFINED> instruction: 0xe7d1fed3
d0014888:	f6ff2c00 			; <UNDEFINED> instruction: 0xf6ff2c00
d001488c:	f04fadc1 			; <UNDEFINED> instruction: 0xf04fadc1
d0014890:	e5ea3bff 	strb	r3, [sl, #3071]!	; 0xbff
d0014894:	00013e32 	andeq	r3, r1, r2, lsr lr
d0014898:	fffffe63 			; <UNDEFINED> instruction: 0xfffffe63
d001489c:	fffffe32 			; <UNDEFINED> instruction: 0xfffffe32
d00148a0:	fffffe33 			; <UNDEFINED> instruction: 0xfffffe33
d00148a4:	00013d26 	andeq	r3, r1, r6, lsr #26
d00148a8:	00013d00 	andeq	r3, r1, r0, lsl #26
d00148ac:	fffffe6d 			; <UNDEFINED> instruction: 0xfffffe6d
d00148b0:	00013cce 	andeq	r3, r1, lr, asr #25
d00148b4:	fffffe52 			; <UNDEFINED> instruction: 0xfffffe52
d00148b8:	fffffd4d 			; <UNDEFINED> instruction: 0xfffffd4d
d00148bc:	00013c72 	andeq	r3, r1, r2, ror ip
d00148c0:	fffffd19 			; <UNDEFINED> instruction: 0xfffffd19
d00148c4:	00013bfe 	strdeq	r3, [r1], -lr
d00148c8:	00013bea 	andeq	r3, r1, sl, ror #23
d00148cc:	fffffb6a 			; <UNDEFINED> instruction: 0xfffffb6a
d00148d0:	00013bd4 	ldrdeq	r3, [r1], -r4
d00148d4:	fffffb12 			; <UNDEFINED> instruction: 0xfffffb12
d00148d8:	00013bc6 	andeq	r3, r1, r6, asr #23
d00148dc:	fffffcad 			; <UNDEFINED> instruction: 0xfffffcad
d00148e0:	fffffca2 			; <UNDEFINED> instruction: 0xfffffca2
d00148e4:	00013b50 	andeq	r3, r1, r0, asr fp
d00148e8:	00013b3a 	andeq	r3, r1, sl, lsr fp
d00148ec:	fffffc72 			; <UNDEFINED> instruction: 0xfffffc72
d00148f0:	fffffb07 			; <UNDEFINED> instruction: 0xfffffb07
d00148f4:	00013b0c 	andeq	r3, r1, ip, lsl #22
d00148f8:	fffffacd 			; <UNDEFINED> instruction: 0xfffffacd
d00148fc:	00013a4a 	andeq	r3, r1, sl, asr #20
d0014900:	00013a22 	andeq	r3, r1, r2, lsr #20
d0014904:	fffffa31 			; <UNDEFINED> instruction: 0xfffffa31
d0014908:	00013a02 	andeq	r3, r1, r2, lsl #20
d001490c:	fffff9cc 			; <UNDEFINED> instruction: 0xfffff9cc
d0014910:	000139aa 	andeq	r3, r1, sl, lsr #19
d0014914:	00013988 	andeq	r3, r1, r8, lsl #19
d0014918:	fffffa05 			; <UNDEFINED> instruction: 0xfffffa05

Disassembly of section .text.accept_sdk_type.constprop.0:

d001491c <.text.accept_sdk_type.constprop.0>:
d001491c:	4c0cb538 	cfstr32mi	mvfx11, [ip], {56}	; 0x38
d0014920:	031cf24d 	tsteq	ip, #-805306364	; 0xd0000004	; <UNPREDICTABLE>
d0014924:	447c4602 	ldrbtmi	r4, [ip], #-1538	; 0xfffff9fe
d0014928:	b17b58e3 	cmnlt	fp, r3, ror #17
d001492c:	f2406ae5 	vpmax.s8	q11, q8, <illegal reg q10.5>
d0014930:	429d1301 	addsmi	r1, sp, #67108864	; 0x4000000
d0014934:	e9d4d10a 	ldmib	r4, {r1, r3, r8, ip, lr, pc}^
d0014938:	f7fb0106 			; <UNDEFINED> instruction: 0xf7fb0106
d001493c:	b128fffb 	strdlt	pc, [r8, -fp]!
d0014940:	46204629 	strtmi	r4, [r0], -r9, lsr #12
d0014944:	4038e8bd 	ldrhtmi	lr, [r8], -sp
d0014948:	badef7fe 	blt	0xcf7d2948
d001494c:	bd382000 	ldclt	0, cr2, [r8, #-0]
d0014950:	0001389e 	muleq	r1, lr, r8

Disassembly of section .text.stream_read.constprop.0:

d0014974 <.text.stream_read.constprop.0>:
d0014974:	4c0fb537 	cfstr32mi	mvfx11, [pc], {55}	; 0x37
d0014978:	6da4447c 	cfstrsvs	mvf4, [r4, #496]!	; 0x1f0
d001497c:	4c0eb94c 			; <UNDEFINED> instruction: 0x4c0eb94c
d0014980:	6824447c 	stmdavs	r4!, {r2, r3, r4, r5, r6, sl, lr}
d0014984:	490db93c 	stmdbmi	sp, {r2, r3, r4, r5, r8, fp, ip, sp, pc}
d0014988:	4479480d 	ldrbtmi	r4, [r9], #-2061	; 0xfffff7f3
d001498c:	f7fb4478 			; <UNDEFINED> instruction: 0xf7fb4478
d0014990:	2000fc6f 	andcs	pc, r0, pc, ror #24
d0014994:	68a5e00b 	stmiavs	r5!, {r0, r1, r3, sp, lr, pc}
d0014998:	d0f42d00 	rscsle	r2, r4, r0, lsl #26
d001499c:	46139300 	ldrmi	r9, [r3], -r0, lsl #6
d00149a0:	4601460a 	strmi	r4, [r1], -sl, lsl #12
d00149a4:	47a86820 	strmi	r6, [r8, r0, lsr #16]!
d00149a8:	d0ec2800 	rscle	r2, ip, r0, lsl #16
d00149ac:	b0032001 	andlt	r2, r3, r1
d00149b0:	bf00bd30 	svclt	0x0000bd30
d00149b4:	0001384c 	andeq	r3, r1, ip, asr #16
d00149b8:	0005ec30 	andeq	lr, r5, r0, lsr ip
d00149bc:	ffffffc6 			; <UNDEFINED> instruction: 0xffffffc6
d00149c0:	00013838 	andeq	r3, r1, r8, lsr r8

Disassembly of section .text.stream_write.constprop.0:

d00149e4 <.text.stream_write.constprop.0>:
d00149e4:	4c0fb537 	cfstr32mi	mvfx11, [pc], {55}	; 0x37
d00149e8:	6da4447c 	cfstrsvs	mvf4, [r4, #496]!	; 0x1f0
d00149ec:	4c0eb94c 			; <UNDEFINED> instruction: 0x4c0eb94c
d00149f0:	6824447c 	stmdavs	r4!, {r2, r3, r4, r5, r6, sl, lr}
d00149f4:	490db93c 	stmdbmi	sp, {r2, r3, r4, r5, r8, fp, ip, sp, pc}
d00149f8:	4479480d 	ldrbtmi	r4, [r9], #-2061	; 0xfffff7f3
d00149fc:	f7fb4478 			; <UNDEFINED> instruction: 0xf7fb4478
d0014a00:	2000fc37 	andcs	pc, r0, r7, lsr ip	; <UNPREDICTABLE>
d0014a04:	6865e00b 	stmdavs	r5!, {r0, r1, r3, sp, lr, pc}^
d0014a08:	d0f42d00 	rscsle	r2, r4, r0, lsl #26
d0014a0c:	46139300 	ldrmi	r9, [r3], -r0, lsl #6
d0014a10:	4601460a 	strmi	r4, [r1], -sl, lsl #12
d0014a14:	47a86820 	strmi	r6, [r8, r0, lsr #16]!
d0014a18:	d0ec2800 	rscle	r2, ip, r0, lsl #16
d0014a1c:	b0032001 	andlt	r2, r3, r1
d0014a20:	bf00bd30 	svclt	0x0000bd30
d0014a24:	000137dc 	ldrdeq	r3, [r1], -ip
d0014a28:	0005ebc0 	andeq	lr, r5, r0, asr #23
d0014a2c:	ffffffc6 			; <UNDEFINED> instruction: 0xffffffc6
d0014a30:	000137c8 	andeq	r3, r1, r8, asr #15

Disassembly of section .text.image_write.constprop.0:

d0014a6c <.text.image_write.constprop.0>:
d0014a6c:	0fbef5b0 	svceq	0x00bef5b0
d0014a70:	f5c0d803 			; <UNDEFINED> instruction: 0xf5c0d803
d0014a74:	429303be 	addsmi	r0, r3, #-134217726	; 0xf8000002
d0014a78:	4906d205 	stmdbmi	r6, {r0, r2, r9, ip, lr, pc}
d0014a7c:	44794806 	ldrbtmi	r4, [r9], #-2054	; 0xfffff7fa
d0014a80:	f7fb4478 			; <UNDEFINED> instruction: 0xf7fb4478
d0014a84:	4613bbf5 			; <UNDEFINED> instruction: 0x4613bbf5
d0014a88:	f100460a 			; <UNDEFINED> instruction: 0xf100460a
d0014a8c:	20000140 	andcs	r0, r0, r0, asr #2
d0014a90:	bfa8f7ff 	svclt	0x00a8f7ff
d0014a94:	ffffffb2 			; <UNDEFINED> instruction: 0xffffffb2
d0014a98:	00013744 	andeq	r3, r1, r4, asr #14

Disassembly of section .text.image_zero.constprop.0:

d0014a9c <.text.image_zero.constprop.0>:
d0014a9c:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d0014aa0:	46054f0c 	strmi	r4, [r5], -ip, lsl #30
d0014aa4:	8030f8df 	ldrsbthi	pc, [r0], -pc	; <UNPREDICTABLE>
d0014aa8:	447f460c 	ldrbtmi	r4, [pc], #-1548	; 0xd0014ab0
d0014aac:	b10c44f8 	strdlt	r4, [ip, -r8]
d0014ab0:	b10b6dbb 			; <UNDEFINED> instruction: 0xb10b6dbb
d0014ab4:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d0014ab8:	6f80f5b4 	svcvs	0x0080f5b4
d0014abc:	46284626 	strtmi	r4, [r8], -r6, lsr #12
d0014ac0:	bf284641 	svclt	0x00284641
d0014ac4:	6680f44f 	strvs	pc, [r0], pc, asr #8
d0014ac8:	44354632 	ldrtmi	r4, [r5], #-1586	; 0xfffff9ce
d0014acc:	f7ff1ba4 			; <UNDEFINED> instruction: 0xf7ff1ba4
d0014ad0:	e7ecffcd 	strb	pc, [ip, sp, asr #31]!	; <UNPREDICTABLE>
d0014ad4:	0001371a 	andeq	r3, r1, sl, lsl r7
d0014ad8:	0000a81c 	andeq	sl, r0, ip, lsl r8

Disassembly of section .text.put16:

d0014adc <.text.put16>:
d0014adc:	2202b507 	andcs	fp, r2, #29360128	; 0x1c00000
d0014ae0:	1004f8ad 	andne	pc, r4, sp, lsr #17
d0014ae4:	f7ffa901 			; <UNDEFINED> instruction: 0xf7ffa901
d0014ae8:	b003ffc1 	andlt	pc, r3, r1, asr #31
d0014aec:	fb04f85d 	blx	0xd0152c6a

Disassembly of section .text.emit:

d0014b14 <.text.emit>:
d0014b14:	b5106d83 	ldrlt	r6, [r0, #-3459]	; 0xfffff27d
d0014b18:	f500b9a3 			; <UNDEFINED> instruction: 0xf500b9a3
d0014b1c:	4a0a348f 	bmi	0xd02a1d60
d0014b20:	31b8f8d4 			; <UNDEFINED> instruction: 0x31b8f8d4
d0014b24:	d9054293 	stmdble	r5, {r0, r1, r4, r7, r9, lr}
d0014b28:	e8bd4908 	pop	{r3, r8, fp, lr}
d0014b2c:	44794010 	ldrbtmi	r4, [r9], #-16
d0014b30:	bb9ef7fb 	bllt	0xce7d2b24
d0014b34:	f7ff4618 			; <UNDEFINED> instruction: 0xf7ff4618
d0014b38:	f8d4ffd1 			; <UNDEFINED> instruction: 0xf8d4ffd1
d0014b3c:	330231b8 	movwcc	r3, #8632	; 0x21b8
d0014b40:	31b8f8c4 			; <UNDEFINED> instruction: 0x31b8f8c4
d0014b44:	bf00bd10 	svclt	0x0000bd10
d0014b48:	005efffe 	ldrsheq	pc, [lr], #-254	; 0xffffff02	; <UNPREDICTABLE>
d0014b4c:	ffffffbe 			; <UNDEFINED> instruction: 0xffffffbe

Disassembly of section .text.load_local:

d0014b50 <.text.load_local>:
d0014b50:	b570291f 	ldrblt	r2, [r0, #-2335]!	; 0xfffff6e1
d0014b54:	b2944606 	addslt	r4, r4, #6291456	; 0x600000
d0014b58:	d80ab28d 	stmdale	sl, {r0, r2, r3, r7, r9, ip, sp, pc}
d0014b5c:	1185ea44 	orrne	lr, r5, r4, asr #20
d0014b60:	41d0f441 	bicsmi	pc, r0, r1, asr #8
d0014b64:	0138f041 	teqeq	r8, r1, asr #32	; <UNPREDICTABLE>
d0014b68:	e8bdb289 	pop	{r0, r3, r7, r9, ip, sp, pc}
d0014b6c:	f7ff4070 			; <UNDEFINED> instruction: 0xf7ff4070
d0014b70:	f64fbfd1 			; <UNDEFINED> instruction: 0xf64fbfd1
d0014b74:	f7ff01d7 			; <UNDEFINED> instruction: 0xf7ff01d7
d0014b78:	4630ffcd 	ldrtmi	pc, [r0], -sp, asr #31	; <UNPREDICTABLE>
d0014b7c:	ea4100a9 	b	0xd1054e28
d0014b80:	b2893104 	addlt	r3, r9, #4, 2
d0014b84:	Address 0x00000000d0014b84 is out of bounds.


Disassembly of section .text.store_local:

d0014b86 <.text.store_local>:
d0014b86:	b570291f 	ldrblt	r2, [r0, #-2335]!	; 0xfffff6e1
d0014b8a:	b2944606 	addslt	r4, r4, #6291456	; 0x600000
d0014b8e:	d80ab28d 	stmdale	sl, {r0, r2, r3, r7, r9, ip, sp, pc}
d0014b92:	1185ea44 	orrne	lr, r5, r4, asr #20
d0014b96:	41c0f441 	bicmi	pc, r0, r1, asr #8
d0014b9a:	0138f041 	teqeq	r8, r1, asr #32	; <UNPREDICTABLE>
d0014b9e:	e8bdb289 	pop	{r0, r3, r7, r9, ip, sp, pc}
d0014ba2:	f7ff4070 			; <UNDEFINED> instruction: 0xf7ff4070
d0014ba6:	f64fbfb6 			; <UNDEFINED> instruction: 0xf64fbfb6
d0014baa:	f7ff01c7 			; <UNDEFINED> instruction: 0xf7ff01c7
d0014bae:	4630ffb2 			; <UNDEFINED> instruction: 0x4630ffb2
d0014bb2:	ea4100a9 	b	0xd1054e5e
d0014bb6:	b2893104 	addlt	r3, r9, #4, 2
d0014bba:	Address 0x00000000d0014bba is out of bounds.


Disassembly of section .text.emit_address:

d0014be4 <.text.emit_address>:
d0014be4:	460db570 			; <UNDEFINED> instruction: 0x460db570
d0014be8:	315ff500 	cmpcc	pc, r0, lsl #10	; <UNPREDICTABLE>
d0014bec:	f8d14604 			; <UNDEFINED> instruction: 0xf8d14604
d0014bf0:	f5b333c0 			; <UNDEFINED> instruction: 0xf5b333c0
d0014bf4:	d1056f00 	tstle	r5, r0, lsl #30
d0014bf8:	e8bd4918 	pop	{r3, r4, r8, fp, lr}
d0014bfc:	44794070 	ldrbtmi	r4, [r9], #-112	; 0xffffff90
d0014c00:	bb36f7fb 	bllt	0xd0dd2bf4
d0014c04:	26041c58 			; <UNDEFINED> instruction: 0x26041c58
d0014c08:	03c0f8c1 	biceq	pc, r0, #12648448	; 0xc10000
d0014c0c:	fb01210c 	blx	0xd005d046
d0014c10:	f5044303 			; <UNDEFINED> instruction: 0xf5044303
d0014c14:	f503318f 			; <UNDEFINED> instruction: 0xf503318f
d0014c18:	f8d13347 			; <UNDEFINED> instruction: 0xf8d13347
d0014c1c:	f8c311b8 			; <UNDEFINED> instruction: 0xf8c311b8
d0014c20:	f8c323c4 			; <UNDEFINED> instruction: 0xf8c323c4
d0014c24:	f88313c0 			; <UNDEFINED> instruction: 0xf88313c0
d0014c28:	210053c8 	smlabtcs	r0, r8, r3, r5
d0014c2c:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0014c30:	3e01ff71 	mcrcc	15, 0, pc, cr1, cr1, {3}	; <UNPREDICTABLE>
d0014c34:	4620d1f9 			; <UNDEFINED> instruction: 0x4620d1f9
d0014c38:	4122f44f 	msrmi	CPSR_x, pc, asr #8
d0014c3c:	ff6af7ff 			; <UNDEFINED> instruction: 0xff6af7ff
d0014c40:	bf0c2d01 	svclt	0x000c2d01
d0014c44:	21002141 	tstcs	r0, r1, asr #2
d0014c48:	f4414620 	vst1.8	{d20-d22}, [r1 :128], r0
d0014c4c:	e8bd51c0 	pop	{r6, r7, r8, ip, lr}
d0014c50:	f0414070 			; <UNDEFINED> instruction: 0xf0414070
d0014c54:	f7ff0110 			; <UNDEFINED> instruction: 0xf7ff0110
d0014c58:	bf00bf5d 	svclt	0x0000bf5d
d0014c5c:	ffffffba 			; <UNDEFINED> instruction: 0xffffffba

Disassembly of section .text.branch:

d0014c60 <.text.branch>:
d0014c60:	f500b538 			; <UNDEFINED> instruction: 0xf500b538
d0014c64:	4604338f 	strmi	r3, [r4], -pc, lsl #7
d0014c68:	f8d32100 			; <UNDEFINED> instruction: 0xf8d32100
d0014c6c:	f7ff51b8 			; <UNDEFINED> instruction: 0xf7ff51b8
d0014c70:	4620ff51 	qsaxmi	pc, r0, r1	; <UNPREDICTABLE>
d0014c74:	f7ff2100 			; <UNDEFINED> instruction: 0xf7ff2100
d0014c78:	4628ff4d 	strtmi	pc, [r8], -sp, asr #30
d0014c7c:	Address 0x00000000d0014c7c is out of bounds.


Disassembly of section .text.branch_on_value:

d0014c7e <.text.branch_on_value>:
d0014c7e:	460db538 			; <UNDEFINED> instruction: 0x460db538
d0014c82:	5120f44f 	msrpl	CPSR_, pc, asr #8
d0014c86:	f7ff4604 			; <UNDEFINED> instruction: 0xf7ff4604
d0014c8a:	f24dff44 	vmax.f32	<illegal reg q15.5>, <illegal reg q6.5>, q2
d0014c8e:	f24d1301 	vcgt.s8	d17, d13, d1
d0014c92:	46200101 	strtmi	r0, [r0], -r1, lsl #2
d0014c96:	bf082d00 	svclt	0x00082d00
d0014c9a:	f7ff4619 			; <UNDEFINED> instruction: 0xf7ff4619
d0014c9e:	4620ff3a 	qasxmi	pc, r0, sl	; <UNPREDICTABLE>
d0014ca2:	4038e8bd 	ldrhtmi	lr, [r8], -sp
d0014ca6:	bfdbf7ff 	svclt	0x00dbf7ff

Disassembly of section .text.boolean:

d0014caa <.text.boolean>:
d0014caa:	0301f24d 	movweq	pc, #4685	; 0x124d	; <UNPREDICTABLE>
d0014cae:	2101ea43 	tstcs	r1, r3, asr #20
d0014cb2:	4604b510 			; <UNDEFINED> instruction: 0x4604b510
d0014cb6:	f7ffb289 			; <UNDEFINED> instruction: 0xf7ffb289
d0014cba:	f44fff2c 			; <UNDEFINED> instruction: 0xf44fff2c
d0014cbe:	46205100 	strtmi	r5, [r0], -r0, lsl #2
d0014cc2:	ff27f7ff 			; <UNDEFINED> instruction: 0xff27f7ff
d0014cc6:	f44f4620 	vst1.8	{d20-d22}, [pc :128], r0
d0014cca:	f7ff4160 			; <UNDEFINED> instruction: 0xf7ff4160
d0014cce:	4620ff22 	strtmi	pc, [r0], -r2, lsr #30
d0014cd2:	0101f242 	tsteq	r1, r2, asr #4	; <UNPREDICTABLE>
d0014cd6:	4010e8bd 			; <UNDEFINED> instruction: 0x4010e8bd
d0014cda:	bf1bf7ff 	svclt	0x001bf7ff

Disassembly of section .text.prepare_call:

d0014cde <.text.prepare_call>:
d0014cde:	e92d2904 	push	{r2, r8, fp, sp}
d0014ce2:	460d43f8 			; <UNDEFINED> instruction: 0x460d43f8
d0014ce6:	2504bf38 	strcs	fp, [r4, #-3896]	; 0xfffff0c8
d0014cea:	460c4607 	strmi	r4, [ip], -r7, lsl #12
d0014cee:	f0353d03 			; <UNDEFINED> instruction: 0xf0353d03
d0014cf2:	d0060501 	andle	r0, r6, r1, lsl #10
d0014cf6:	4130f445 	teqmi	r0, r5, asr #8	; <UNPREDICTABLE>
d0014cfa:	0180f041 	orreq	pc, r0, r1, asr #32
d0014cfe:	f7ffb289 			; <UNDEFINED> instruction: 0xf7ffb289
d0014d02:	1f66ff08 	svcne	0x0066ff08
d0014d06:	0904f04f 	stmdbeq	r4, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d0014d0a:	0846ea4f 	stmdaeq	r6, {r0, r1, r2, r3, r6, r9, fp, sp, lr, pc}^
d0014d0e:	0646eb05 	strbeq	lr, [r6], -r5, lsl #22
d0014d12:	45a1b2b6 	strmi	fp, [r1, #694]!	; 0x2b6
d0014d16:	f108d30c 			; <UNDEFINED> instruction: 0xf108d30c
d0014d1a:	f04f0608 			; <UNDEFINED> instruction: 0xf04f0608
d0014d1e:	442e0800 	strtmi	r0, [lr], #-2048	; 0xfffff800
d0014d22:	45a0b2b6 	strmi	fp, [r0, #694]!	; 0x2b6
d0014d26:	f1b8d027 			; <UNDEFINED> instruction: 0xf1b8d027
d0014d2a:	d1130f04 	tstle	r3, r4, lsl #30
d0014d2e:	e02abb25 	eor	fp, sl, r5, lsr #22
d0014d32:	4118f446 	tstmi	r8, r6, asr #8	; <UNPREDICTABLE>
d0014d36:	f7ff4638 			; <UNDEFINED> instruction: 0xf7ff4638
d0014d3a:	f1a9feec 			; <UNDEFINED> instruction: 0xf1a9feec
d0014d3e:	3e020104 	adfccs	f0, f2, f4
d0014d42:	f4414638 	vst1.8	{d20-d22}, [r1 :256], r8
d0014d46:	f1094110 			; <UNDEFINED> instruction: 0xf1094110
d0014d4a:	b2b60901 	adcslt	r0, r6, #16384	; 0x4000
d0014d4e:	f7ffb289 			; <UNDEFINED> instruction: 0xf7ffb289
d0014d52:	e7defee0 	ldrb	pc, [lr, r0, ror #29]	; <UNPREDICTABLE>
d0014d56:	f388fa1f 	vmovl.u8	<illegal reg q7.5>, d15
d0014d5a:	f1084638 			; <UNDEFINED> instruction: 0xf1084638
d0014d5e:	ebc30801 	bl	0xcf0d6d6a
d0014d62:	eb0631c3 	bl	0xd01a1476
d0014d66:	ea410141 	b	0xd1055272
d0014d6a:	f4412103 	vst4.8	{d18,d20,d22,d24}, [r1], r3
d0014d6e:	b2894118 	addlt	r4, r9, #24, 2
d0014d72:	fecff7ff 	mcr2	7, 6, pc, cr15, cr15, {7}	; <UNPREDICTABLE>
d0014d76:	b125e7d5 	ldrdlt	lr, [r5, -r5]!
d0014d7a:	0444eb05 	strbeq	lr, [r4], #-2821	; 0xfffff4fb
d0014d7e:	e8bd4620 	pop	{r5, r9, sl, lr}
d0014d82:	2c0083f8 	stccs	3, cr8, [r0], {248}	; 0xf8
d0014d86:	0061d0fa 	strdeq	sp, [r1], #-10	; <UNPREDICTABLE>
d0014d8a:	24004638 	strcs	r4, [r0], #-1592	; 0xfffff9c8
d0014d8e:	4130f441 	teqmi	r0, r1, asr #8	; <UNPREDICTABLE>
d0014d92:	f7ffb289 			; <UNDEFINED> instruction: 0xf7ffb289
d0014d96:	e7f1febe 			; <UNDEFINED> instruction: 0xe7f1febe

Disassembly of section .text.binary:

d0014d9a <.text.binary>:
d0014d9a:	b570292f 	ldrblt	r2, [r0, #-2351]!	; 0xfffff6d1
d0014d9e:	460e4604 	strmi	r4, [lr], -r4, lsl #12
d0014da2:	dc0d4615 	stcle	6, cr4, [sp], {21}
d0014da6:	dd102924 	vldrle.16	s4, [r0, #-72]	; 0xffffffb8	; <UNPREDICTABLE>
d0014daa:	0325f1a1 	msreq	CPSR_sc, #1073741864	; 0x40000028
d0014dae:	d80c2b0a 	stmdale	ip, {r1, r3, r8, r9, fp, sp}
d0014db2:	f003e8df 			; <UNDEFINED> instruction: 0xf003e8df
d0014db6:	0b0b4058 	bleq	0xd02e4f1e
d0014dba:	0b363d0b 	bleq	0xd0da41ee
d0014dbe:	004c0b6b 	subeq	r0, ip, fp, ror #22
d0014dc2:	d03a297c 	eorsle	r2, sl, ip, ror r9
d0014dc6:	295edc12 	ldmdbcs	lr, {r1, r4, sl, fp, ip, lr, pc}^
d0014dca:	f244d03a 	vqadd.s8	d29, d4, d26
d0014dce:	46202181 	strtmi	r2, [r0], -r1, lsl #3
d0014dd2:	fe9ff7ff 	mrc2	7, 4, pc, cr15, cr15, {7}
d0014dd6:	7f90f5b6 	svcvc	0x0090f5b6
d0014dda:	f5b6da06 			; <UNDEFINED> instruction: 0xf5b6da06
d0014dde:	da577f8e 	ble	0xd15f4c1e
d0014de2:	d06a2e3c 	rsble	r2, sl, ip, lsr lr
d0014de6:	d06d2e3e 	rsble	r2, sp, lr, lsr lr
d0014dea:	e01e2500 	ands	r2, lr, r0, lsl #10
d0014dee:	7293f46f 	addsvc	pc, r3, #1862270976	; 0x6f000000
d0014df2:	2b01188b 	blcs	0xd005b026
d0014df6:	f244d8e9 	vadd.i8	<illegal reg q14.5>, q10, <illegal reg q12.5>
d0014dfa:	f7ff6102 			; <UNDEFINED> instruction: 0xf7ff6102
d0014dfe:	f244fe8a 	vceq.f32	d31, d20, d10
d0014e02:	46206108 	strtmi	r6, [r0], -r8, lsl #2
d0014e06:	fe85f7ff 	mcr2	7, 4, pc, cr5, cr15, {7}	; <UNPREDICTABLE>
d0014e0a:	1327f240 	msrne	CPSR_sxc, #64, 4
d0014e0e:	d01a429e 	mulsle	sl, lr, r2
d0014e12:	01d0f244 	bicseq	pc, r0, r4, asr #4
d0014e16:	1310f244 	tstne	r0, #68, 4	; 0x40000004	; <UNPREDICTABLE>
d0014e1a:	bf082d00 	svclt	0x00082d00
d0014e1e:	e0014619 	and	r4, r1, r9, lsl r6
d0014e22:	0108f641 	tsteq	r8, r1, asr #12	; <UNPREDICTABLE>
d0014e26:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0014e2a:	4628fe74 			; <UNDEFINED> instruction: 0x4628fe74
d0014e2e:	f244bd70 	vmla.f32	<illegal reg q13.5>, q2, q8
d0014e32:	e7f73148 	ldrb	r3, [r7, r8, asr #2]!
d0014e36:	0108f244 	tsteq	r8, r4, asr #4	; <UNPREDICTABLE>
d0014e3a:	f244e7f4 	vaba.s8	q15, q10, q10
d0014e3e:	e7f23108 	ldrb	r3, [r2, r8, lsl #2]!
d0014e42:	0148f244 	cmpeq	r8, r4, asr #4	; <UNPREDICTABLE>
d0014e46:	f244e7ef 	vabd.s8	q15, q10, <illegal reg q15.5>
d0014e4a:	e7eb0190 			; <UNDEFINED> instruction: 0xe7eb0190
d0014e4e:	3391f64f 	orrscc	pc, r1, #82837504	; 0x4f00000
d0014e52:	31b1f64f 			; <UNDEFINED> instruction: 0x31b1f64f
d0014e56:	bf082d00 	svclt	0x00082d00
d0014e5a:	f7ff4619 			; <UNDEFINED> instruction: 0xf7ff4619
d0014e5e:	f24ffe5a 			; <UNDEFINED> instruction: 0xf24ffe5a
d0014e62:	e7df01f0 			; <UNDEFINED> instruction: 0xe7df01f0
d0014e66:	3391f64f 	orrscc	pc, r1, #82837504	; 0x4f00000
d0014e6a:	31b1f64f 			; <UNDEFINED> instruction: 0x31b1f64f
d0014e6e:	bf082d00 	svclt	0x00082d00
d0014e72:	f7ff4619 			; <UNDEFINED> instruction: 0xf7ff4619
d0014e76:	f24ffe4e 	vceq.f32	<illegal reg q15.5>, <illegal reg q7.5>, q7
d0014e7a:	462021f0 			; <UNDEFINED> instruction: 0x462021f0
d0014e7e:	fe49f7ff 	mcr2	7, 2, pc, cr9, cr15, {7}	; <UNPREDICTABLE>
d0014e82:	3150f244 	cmpcc	r0, r4, asr #4	; <UNPREDICTABLE>
d0014e86:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0014e8a:	f641fe44 			; <UNDEFINED> instruction: 0xf641fe44
d0014e8e:	e7c92108 	strb	r2, [r9, r8, lsl #2]
d0014e92:	738ef46f 	orrvc	pc, lr, #1862270976	; 0x6f000000
d0014e96:	2e02441e 	cfmvdlrcs	mvd2, r4
d0014e9a:	e8dfd803 	ldm	pc, {r0, r1, fp, ip, lr, pc}^	; <UNPREDICTABLE>
d0014e9e:	1807f006 	stmdane	r7, {r1, r2, ip, sp, lr, pc}
d0014ea2:	21000009 	tstcs	r0, r9
d0014ea6:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0014eaa:	e79dfeff 			; <UNDEFINED> instruction: 0xe79dfeff
d0014eae:	e7f92101 	ldrb	r2, [r9, r1, lsl #2]!
d0014eb2:	bf142d00 	svclt	0x00142d00
d0014eb6:	210a2102 	tstcs	sl, r2, lsl #2
d0014eba:	2d00e7f4 	stccs	7, cr14, [r0, #-976]	; 0xfffffc30
d0014ebe:	2103bf14 	tstcs	r3, r4, lsl pc
d0014ec2:	e7ef210b 	strb	r2, [pc, fp, lsl #2]!
d0014ec6:	bf142d00 	svclt	0x00142d00
d0014eca:	210c2108 	tstcs	ip, r8, lsl #2
d0014ece:	2d00e7ea 	stccs	7, cr14, [r0, #-936]	; 0xfffffc58
d0014ed2:	2109bf14 	tstcs	r9, r4, lsl pc
d0014ed6:	e7e5210d 	strb	r2, [r5, sp, lsl #2]!

Disassembly of section .text.increment_scalar.isra.0:

d0014f34 <.text.increment_scalar.isra.0>:
d0014f34:	4ff8e92d 	svcmi	0x00f8e92d
d0014f38:	a030f8dd 	ldrsbtge	pc, [r0], -sp	; <UNPREDICTABLE>
d0014f3c:	460d4604 	strmi	r4, [sp], -r4, lsl #12
d0014f40:	46984617 			; <UNDEFINED> instruction: 0x46984617
d0014f44:	902cf89d 	mlals	ip, sp, r8, pc	; <UNPREDICTABLE>
d0014f48:	b038f8dd 	ldrsbtlt	pc, [r8], -sp	; <UNPREDICTABLE>
d0014f4c:	fc40f7fb 	mcrr2	7, 15, pc, r0, cr11	; <UNPREDICTABLE>
d0014f50:	da6f1e06 	ble	0xd1bdc770
d0014f54:	4629463a 			; <UNDEFINED> instruction: 0x4629463a
d0014f58:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0014f5c:	1e07fc59 	mcrne	12, 0, pc, cr7, cr9, {2}	; <UNPREDICTABLE>
d0014f60:	233cdb19 	teqcs	ip, #25600	; 0x6400
d0014f64:	4307fb03 	movwmi	pc, #31491	; 0x7b03	; <UNPREDICTABLE>
d0014f68:	335ff503 	cmpcc	pc, #12582912	; 0xc00000	; <UNPREDICTABLE>
d0014f6c:	53ecf893 	mvnpl	pc, #9633792	; 0x930000
d0014f70:	33f0f893 	mvnscc	pc, #9633792	; 0x930000
d0014f74:	d06a2b00 	rsble	r2, sl, r0, lsl #22
d0014f78:	b1106da0 	tstlt	r0, r0, lsr #27
d0014f7c:	e8bd2000 	ldmfd	sp!, {sp}
d0014f80:	4b3e8ff8 	blmi	0xd0fb8f68
d0014f84:	f8c4447b 			; <UNDEFINED> instruction: 0xf8c4447b
d0014f88:	e9c4a068 	stmib	r4, {r3, r5, r6, sp, pc}^
d0014f8c:	9b0a3816 	blls	0xd02a2fec
d0014f90:	3918e9c4 	ldmdbcc	r8, {r2, r6, r7, r8, fp, sp, lr, pc}
d0014f94:	6da0e7f3 	stcvs	7, cr14, [r0, #972]!	; 0x3cc
d0014f98:	d1ef2800 	mvnle	r2, r0, lsl #16
d0014f9c:	447b4b38 	ldrbtmi	r4, [fp], #-2872	; 0xfffff4c8
d0014fa0:	2200e7f1 	andcs	lr, r0, #63176704	; 0x3c40000
d0014fa4:	46204631 			; <UNDEFINED> instruction: 0x46204631
d0014fa8:	fdd2f7ff 	ldc2l	7, cr15, [r2, #1020]	; 0x3fc
d0014fac:	0f00f1bb 	svceq	0x0000f1bb
d0014fb0:	f24bd004 	vhadd.s8	d29, d11, d4
d0014fb4:	46204101 	strtmi	r4, [r0], -r1, lsl #2
d0014fb8:	fdacf7ff 	stc2	7, cr15, [ip, #1020]!	; 0x3fc
d0014fbc:	1323f240 	msrne	CPSR_xc, #64, 4
d0014fc0:	46209a0d 	strtmi	r9, [r0], -sp, lsl #20
d0014fc4:	bf07429a 	svclt	0x0007429a
d0014fc8:	0104f243 	tsteq	r4, r3, asr #4	; <UNPREDICTABLE>
d0014fcc:	0301f243 	movweq	pc, #4675	; 0x1243	; <UNPREDICTABLE>
d0014fd0:	0104f643 	tsteq	r4, r3, asr #12	; <UNPREDICTABLE>
d0014fd4:	0301f643 	movweq	pc, #5699	; 0x1643	; <UNPREDICTABLE>
d0014fd8:	bf182d0a 	svclt	0x00182d0a
d0014fdc:	f7ff4619 			; <UNDEFINED> instruction: 0xf7ff4619
d0014fe0:	2d05fd99 	stccs	13, cr15, [r5, #-612]	; 0xfffffd9c
d0014fe4:	f24bd104 	vrhadd.s8	d29, d11, d4
d0014fe8:	462021c0 	strtmi	r2, [r0], -r0, asr #3
d0014fec:	fd92f7ff 	ldc2	7, cr15, [r2, #1020]	; 0x3fc
d0014ff0:	db122e00 	blle	0xd04a07f8
d0014ff4:	46312200 	ldrtmi	r2, [r1], -r0, lsl #4
d0014ff8:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0014ffc:	f1bbfdc4 			; <UNDEFINED> instruction: 0xf1bbfdc4
d0015000:	d0040f00 	andle	r0, r4, r0, lsl #30
d0015004:	4101f64b 	tstmi	r1, fp, asr #12	; <UNPREDICTABLE>
d0015008:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d001500c:	2d0afd83 	stccs	13, cr15, [sl, #-524]	; 0xfffffdf4
d0015010:	1e6bd00e 	cdpne	0, 6, cr13, cr11, cr14, {0}
d0015014:	41584258 	cmpmi	r8, r8, asr r2
d0015018:	4620e7b1 			; <UNDEFINED> instruction: 0x4620e7b1
d001501c:	2101463a 	tstcs	r1, sl, lsr r6
d0015020:	fde0f7ff 	stc2l	7, cr15, [r0, #1020]!	; 0x3fc
d0015024:	0108f246 	tsteq	r8, r6, asr #4	; <UNPREDICTABLE>
d0015028:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d001502c:	e7e6fd73 			; <UNDEFINED> instruction: 0xe7e6fd73
d0015030:	e7a42004 	str	r2, [r4, r4]!
d0015034:	fb032330 	blx	0xd00ddcfe
d0015038:	f5034306 			; <UNDEFINED> instruction: 0xf5034306
d001503c:	f8932390 			; <UNDEFINED> instruction: 0xf8932390
d0015040:	2a002664 	bcs	0xd001e9d8
d0015044:	f893d198 			; <UNDEFINED> instruction: 0xf893d198
d0015048:	f04f5659 			; <UNDEFINED> instruction: 0xf04f5659
d001504c:	1eaa37ff 	mcrne	7, 5, r3, cr10, cr15, {7}
d0015050:	d8032a11 	stmdale	r3, {r0, r4, r9, fp, sp}
d0015054:	40d34b08 	sbcsmi	r4, r3, r8, lsl #22
d0015058:	d49c07da 	ldrle	r0, [ip], #2010	; 0x7da
d001505c:	daa02e00 	ble	0xce820864
d0015060:	463a4620 	ldrtmi	r4, [sl], -r0, lsr #12
d0015064:	f7ff2101 			; <UNDEFINED> instruction: 0xf7ff2101
d0015068:	f646fdbd 			; <UNDEFINED> instruction: 0xf646fdbd
d001506c:	46200108 	strtmi	r0, [r0], -r8, lsl #2
d0015070:	fd50f7ff 	ldc2l	7, cr15, [r0, #-1020]	; 0xfffffc04
d0015074:	bf00e79a 	svclt	0x0000e79a
d0015078:	0003fef5 	strdeq	pc, [r3], -r5
d001507c:	ffffff52 			; <UNDEFINED> instruction: 0xffffff52
d0015080:	ffffff65 			; <UNDEFINED> instruction: 0xffffff65

Disassembly of section .text.string_argument:

d00150d4 <.text.string_argument>:
d00150d4:	f2406ac3 	vpmax.s8	q11, q8, <illegal reg q1.5>
d00150d8:	42931201 	addsmi	r1, r3, #268435456	; 0x10000000
d00150dc:	4ff0e92d 	svcmi	0x00f0e92d
d00150e0:	b0894604 	addlt	r4, r9, r4, lsl #12
d00150e4:	e9d0d12d 	ldmib	r0, {r0, r2, r3, r5, r8, ip, lr, pc}^
d00150e8:	92051206 	andls	r1, r5, #1610612736	; 0x60000000
d00150ec:	f7fb9104 			; <UNDEFINED> instruction: 0xf7fb9104
d00150f0:	1e05fb8f 	vmlane.f64	d15, d21, d15
d00150f4:	9a059904 	bls	0xd017b50c
d00150f8:	4943da05 	stmdbmi	r3, {r0, r2, r9, fp, ip, lr, pc}^
d00150fc:	44794620 	ldrbtmi	r4, [r9], #-1568	; 0xfffff9e0
d0015100:	f8b6f7fb 			; <UNDEFINED> instruction: 0xf8b6f7fb
d0015104:	4620e01a 			; <UNDEFINED> instruction: 0x4620e01a
d0015108:	fb62f7fb 	blx	0xd18d30fe
d001510c:	daf42800 	ble	0xcfd1f114
d0015110:	fb03233c 	blx	0xd00dde0a
d0015114:	f5034305 			; <UNDEFINED> instruction: 0xf5034305
d0015118:	f893335f 			; <UNDEFINED> instruction: 0xf893335f
d001511c:	2b0733ec 	blcs	0xd01e20d4
d0015120:	4620d1eb 	strtmi	sp, [r0], -fp, ror #3
d0015124:	fed0f7fd 	mrc2	7, 6, pc, cr0, cr13, {7}
d0015128:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d001512c:	f7ff462a 			; <UNDEFINED> instruction: 0xf7ff462a
d0015130:	f244fd59 	vmla.f32	<illegal reg q15.5>, q2, <illegal reg q4.5>
d0015134:	46206108 	strtmi	r6, [r0], -r8, lsl #2
d0015138:	fcecf7ff 	stc2l	7, cr15, [ip], #1020	; 0x3fc
d001513c:	e8bdb009 	pop	{r0, r3, ip, sp, pc}
d0015140:	f5b38ff0 			; <UNDEFINED> instruction: 0xf5b38ff0
d0015144:	d1d87f82 	bicsle	r7, r8, r2, lsl #31
d0015148:	368ff500 	strcc	pc, [pc], r0, lsl #10
d001514c:	81bcf8d6 			; <UNDEFINED> instruction: 0x81bcf8d6
d0015150:	3f00f5b8 	svccc	0x0000f5b8
d0015154:	f506d02a 			; <UNDEFINED> instruction: 0xf506d02a
d0015158:	6a6177de 	bvs	0xd18730d8
d001515c:	0b1cf10d 	bleq	0xd0751598
d0015160:	f8946aa2 			; <UNDEFINED> instruction: 0xf8946aa2
d0015164:	f8d49030 			; <UNDEFINED> instruction: 0xf8d49030
d0015168:	e9d4a034 	ldmib	r4, {r2, r4, r5, sp, pc}^
d001516c:	95075306 	strls	r5, [r7, #-774]	; 0xfffffcfa
d0015170:	9807441d 	stmdals	r7, {r0, r2, r3, r4, sl, lr}
d0015174:	d11c42a8 	tstle	ip, r8, lsr #5
d0015178:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d001517c:	6ae3fea5 	bvs	0xcf914c18
d0015180:	7f82f5b3 	svcvc	0x0082f5b3
d0015184:	6da3d102 	stfvsd	f5, [r3, #8]!
d0015188:	d0e62b00 	rscle	r2, r6, r0, lsl #22
d001518c:	31bcf8d6 			; <UNDEFINED> instruction: 0x31bcf8d6
d0015190:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d0015194:	44231c5a 	strtmi	r1, [r3], #-3162	; 0xfffff3a6
d0015198:	338ff503 	orrcc	pc, pc, #12582912	; 0xc00000
d001519c:	21bcf8c6 			; <UNDEFINED> instruction: 0x21bcf8c6
d00151a0:	f8834642 			; <UNDEFINED> instruction: 0xf8834642
d00151a4:	f7ff11c0 			; <UNDEFINED> instruction: 0xf7ff11c0
d00151a8:	e7c7fd1d 	bfi	pc, sp, (invalid: 26:7)	; <UNPREDICTABLE>
d00151ac:	44794917 	ldrbtmi	r4, [r9], #-2327	; 0xfffff6e9
d00151b0:	683be7a6 	ldmdavs	fp!, {r1, r2, r5, r7, r8, r9, sl, sp, lr, pc}
d00151b4:	f5b33301 			; <UNDEFINED> instruction: 0xf5b33301
d00151b8:	d30b3f00 	movwle	r3, #48896	; 0xbf00
d00151bc:	2b006da3 	blcs	0xd0030850
d00151c0:	4b13d1bc 	blmi	0xd05098b8
d00151c4:	a068f8c4 	rsbge	pc, r8, r4, asr #17
d00151c8:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d00151cc:	e9c42918 	stmib	r4, {r3, r4, r8, fp, sp}^
d00151d0:	e7b33116 			; <UNDEFINED> instruction: 0xe7b33116
d00151d4:	93071c43 	movwls	r1, #31811	; 0x7c43
d00151d8:	285c7800 	ldmdacs	ip, {fp, ip, sp, lr}^
d00151dc:	464bd106 	strbmi	sp, [fp], -r6, lsl #2
d00151e0:	95024620 	strls	r4, [r2, #-1568]	; 0xfffff9e0
d00151e4:	ab00e9cd 	blge	0xd004f920
d00151e8:	f9a8f7fb 			; <UNDEFINED> instruction: 0xf9a8f7fb
d00151ec:	2b006da3 	blcs	0xd0030880
d00151f0:	683bd1a4 	ldmdavs	fp!, {r2, r5, r7, r8, ip, lr, pc}
d00151f4:	0c01f103 	stfeqd	f7, [r1], {3}
d00151f8:	f5034423 			; <UNDEFINED> instruction: 0xf5034423
d00151fc:	f8c7338f 			; <UNDEFINED> instruction: 0xf8c7338f
d0015200:	f883c000 			; <UNDEFINED> instruction: 0xf883c000
d0015204:	e7b401c0 	ldr	r0, [r4, r0, asr #3]!
d0015208:	ffffff82 			; <UNDEFINED> instruction: 0xffffff82
d001520c:	ffffff04 			; <UNDEFINED> instruction: 0xffffff04
d0015210:	fffffeea 			; <UNDEFINED> instruction: 0xfffffeea

Disassembly of section .text.copy_record.constprop.0:

d0015214 <.text.copy_record.constprop.0>:
d0015214:	4e0fb5f8 	mcrmi	5, 0, fp, cr15, cr8, {7}
d0015218:	25004607 	strcs	r4, [r0, #-1543]	; 0xfffff9f9
d001521c:	42bd447e 	adcsmi	r4, sp, #2113929216	; 0x7e000000
d0015220:	bdf8d100 	ldfltp	f5, [r8]
d0015224:	f64f00ac 			; <UNDEFINED> instruction: 0xf64f00ac
d0015228:	463001d0 			; <UNDEFINED> instruction: 0x463001d0
d001522c:	f4443501 	vst3.8	{d19,d21,d23}, [r4], r1
d0015230:	f7ff5400 			; <UNDEFINED> instruction: 0xf7ff5400
d0015234:	4630fc6f 	ldrtmi	pc, [r0], -pc, ror #24	; <UNPREDICTABLE>
d0015238:	4621b2a4 	strtmi	fp, [r1], -r4, lsr #5
d001523c:	fc6af7ff 	stc2l	7, cr15, [sl], #-1020	; 0xfffffc04
d0015240:	01c1f64f 	biceq	pc, r1, pc, asr #12
d0015244:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0015248:	4621fc65 	strtmi	pc, [r1], -r5, ror #24
d001524c:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0015250:	e7e4fc61 	strb	pc, [r4, r1, ror #24]!	; <UNPREDICTABLE>
d0015254:	00012fa8 	andeq	r2, r1, r8, lsr #31

Disassembly of section .text.wide_immediate:

d0015258 <.text.wide_immediate>:
d0015258:	461cb570 			; <UNDEFINED> instruction: 0x461cb570
d001525c:	4605085b 			; <UNDEFINED> instruction: 0x4605085b
d0015260:	f4034616 	vst1.8	{d4-d6}, [r3 :64], r6
d0015264:	ea416380 	b	0xd106e06c
d0015268:	43193114 	tstmi	r9, #20, 2
d001526c:	fc36f7ff 	ldc2	7, cr15, [r6], #-1020	; 0xfffffc04
d0015270:	b2e11ca8 	rsclt	r1, r1, #168, 24	; 0xa800
d0015274:	ea410124 	b	0xd105570c
d0015278:	f4042206 	vst1.8	{d2-d5}, [r4], r6
d001527c:	431444e0 	tstmi	r4, #224, 8	; 0xe0000000
d0015280:	e8bdb2a1 	pop	{r0, r5, r7, r9, ip, sp, pc}
d0015284:	f7ff4070 			; <UNDEFINED> instruction: 0xf7ff4070
d0015288:	Address 0x00000000d0015288 is out of bounds.


Disassembly of section .text.load_constant:

d001528a <.text.load_constant>:
d001528a:	e92d2aff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r9, fp, sp}
d001528e:	460541f0 			; <UNDEFINED> instruction: 0x460541f0
d0015292:	4614460e 	ldrmi	r4, [r4], -lr, lsl #12
d0015296:	2907d80a 	stmdbcs	r7, {r1, r3, fp, ip, lr, pc}
d001529a:	ea42d808 	b	0xd10cb2c2
d001529e:	f4412101 	vst4.8	{d18,d20,d22,d24}, [r1], r1
d00152a2:	e8bd5100 	pop	{r8, ip, lr}
d00152a6:	b28941f0 	addlt	r4, r9, #240, 2	; 0x3c
d00152aa:	bc33f7ff 	ldclt	7, cr15, [r3], #-1020	; 0xfffffc04
d00152ae:	338ff505 	orrcc	pc, pc, #20971520	; 0x1400000
d00152b2:	46282100 	strtmi	r2, [r8], -r0, lsl #2
d00152b6:	71b8f8d3 			; <UNDEFINED> instruction: 0x71b8f8d3
d00152ba:	fc2bf7ff 	stc2	7, cr15, [fp], #-1020	; 0xfffffc04
d00152be:	46282100 	strtmi	r2, [r8], -r0, lsl #2
d00152c2:	fc27f7ff 	stc2	7, cr15, [r7], #-1020	; 0xfffffc04
d00152c6:	3f80f5b4 	svccc	0x0080f5b4
d00152ca:	2100d307 	tstcs	r0, r7, lsl #6
d00152ce:	f7ff4628 			; <UNDEFINED> instruction: 0xf7ff4628
d00152d2:	2100fc20 	tstcs	r0, r0, lsr #24	; <UNPREDICTABLE>
d00152d6:	f7ff4628 			; <UNDEFINED> instruction: 0xf7ff4628
d00152da:	6dabfc1c 	stcvs	12, cr15, [fp, #112]!	; 0x70
d00152de:	b2a3b9a3 	adclt	fp, r3, #2670592	; 0x28c000
d00152e2:	f24f4632 	vmin.s8	d20, d15, d18
d00152e6:	46382140 	ldrtmi	r2, [r8], -r0, asr #2
d00152ea:	ffb5f7ff 			; <UNDEFINED> instruction: 0xffb5f7ff
d00152ee:	3f80f5b4 	svccc	0x0080f5b4
d00152f2:	6dabd30a 	stcvs	3, cr13, [fp, #40]!	; 0x28
d00152f6:	0c23b943 			; <UNDEFINED> instruction: 0x0c23b943
d00152fa:	1d384632 	ldcne	6, cr4, [r8, #-200]!	; 0xffffff38
d00152fe:	21c0f24f 	biccs	pc, r0, pc, asr #4
d0015302:	41f0e8bd 	ldrhmi	lr, [r0, #141]!	; 0x8d
d0015306:	bfa7f7ff 	svclt	0x00a7f7ff
d001530a:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d

Disassembly of section .text.constant:

d001530e <.text.constant>:
d001530e:	2100460a 	tstcs	r0, sl, lsl #12
d0015312:	bfbaf7ff 	svclt	0x00baf7ff

Disassembly of section .text.null_argument:

d001531c <.text.null_argument>:
d001531c:	f5a36ac3 			; <UNDEFINED> instruction: 0xf5a36ac3
d0015320:	2a017281 	bcs	0xd0071d2c
d0015324:	4604b570 			; <UNDEFINED> instruction: 0x4604b570
d0015328:	6a03d803 	bvs	0xd010b33c
d001532c:	2000b1eb 	andcs	fp, r0, fp, ror #3
d0015330:	f240bd70 	vmla.f32	<illegal reg q13.5>, q0, q8
d0015334:	42931201 	addsmi	r1, r3, #268435456	; 0x10000000
d0015338:	4a10d1f9 	bmi	0xd0449b24
d001533c:	5606e9d0 			; <UNDEFINED> instruction: 0x5606e9d0
d0015340:	4631447a 			; <UNDEFINED> instruction: 0x4631447a
d0015344:	f7fb4628 			; <UNDEFINED> instruction: 0xf7fb4628
d0015348:	2800faf5 	stmdacs	r0, {r0, r2, r4, r5, r6, r7, r9, fp, ip, sp, lr, pc}
d001534c:	4632d0ef 	ldrtmi	sp, [r2], -pc, ror #1
d0015350:	46204629 	strtmi	r4, [r0], -r9, lsr #12
d0015354:	fa3cf7fb 	blx	0xd0f53348
d0015358:	dae82800 	ble	0xcfa1f360
d001535c:	46294632 			; <UNDEFINED> instruction: 0x46294632
d0015360:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0015364:	2800fa55 	stmdacs	r0, {r0, r2, r4, r6, r9, fp, ip, sp, lr, pc}
d0015368:	4620dae1 	strtmi	sp, [r0], -r1, ror #21
d001536c:	fdacf7fd 	stc2	7, cr15, [ip, #1012]!	; 0x3f4
d0015370:	21004620 	tstcs	r0, r0, lsr #12
d0015374:	ffcbf7ff 			; <UNDEFINED> instruction: 0xffcbf7ff
d0015378:	e7d92001 	ldrb	r2, [r9, r1]
d001537c:	ffffffd2 			; <UNDEFINED> instruction: 0xffffffd2

Disassembly of section .text.function_pointer_value.constprop.0:

d0015414 <.text.function_pointer_value.constprop.0>:
d0015414:	4ff7e92d 	svcmi	0x00f7e92d
d0015418:	46054c4a 	strmi	r4, [r5], -sl, asr #24
d001541c:	4620447c 			; <UNDEFINED> instruction: 0x4620447c
d0015420:	ff7cf7ff 			; <UNDEFINED> instruction: 0xff7cf7ff
d0015424:	2126bb98 			; <UNDEFINED> instruction: 0x2126bb98
d0015428:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d001542c:	4a46fd6d 	bmi	0xd11d49e8
d0015430:	f2406b63 	vqdmulh.s<illegal width 8>	q11, q0, <illegal reg q9.5>
d0015434:	447a1101 	ldrbtmi	r1, [sl], #-257	; 0xfffffeff
d0015438:	f8d44620 			; <UNDEFINED> instruction: 0xf8d44620
d001543c:	f8d49024 			; <UNDEFINED> instruction: 0xf8d49024
d0015440:	f8948028 			; <UNDEFINED> instruction: 0xf8948028
d0015444:	93017030 	movwls	r7, #4144	; 0x1030
d0015448:	b606e9d4 			; <UNDEFINED> instruction: 0xb606e9d4
d001544c:	fd6af7fd 	stc2l	7, cr15, [sl, #-1012]!	; 0xfffffc0c
d0015450:	4632b1e8 	ldrtmi	fp, [r2], -r8, ror #3
d0015454:	46204659 			; <UNDEFINED> instruction: 0x46204659
d0015458:	f9baf7fb 			; <UNDEFINED> instruction: 0xf9baf7fb
d001545c:	0a00f1b0 	beq	0xd0051b24
d0015460:	2030db34 	eorscs	sp, r0, r4, lsr fp
d0015464:	f00afb00 			; <UNDEFINED> instruction: 0xf00afb00
d0015468:	f5031823 			; <UNDEFINED> instruction: 0xf5031823
d001546c:	f8932390 			; <UNDEFINED> instruction: 0xf8932390
d0015470:	2a0c2659 	bcs	0xd031eddc
d0015474:	4b35d00e 	blmi	0xd0d894b4
d0015478:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d001547c:	4a34b93a 	bmi	0xd0d4396c
d0015480:	e9c3447a 	stmib	r3, {r1, r3, r4, r5, r6, sl, lr}^
d0015484:	9a012916 	bls	0xd005f8e4
d0015488:	8718e9c3 	ldrhi	lr, [r8, -r3, asr #19]
d001548c:	b003669a 	mullt	r3, sl, r6
d0015490:	8ff0e8bd 	svchi	0x00f0e8bd
d0015494:	f8937829 			; <UNDEFINED> instruction: 0xf8937829
d0015498:	428a265b 	addmi	r2, sl, #95420416	; 0x5b00000
d001549c:	f893d1eb 			; <UNDEFINED> instruction: 0xf893d1eb
d00154a0:	786b165c 	stmdavc	fp!, {r2, r3, r4, r6, r9, sl, ip}^
d00154a4:	d1e64299 			; <UNDEFINED> instruction: 0xd1e64299
d00154a8:	2090f500 	addscs	pc, r0, r0, lsl #10
d00154ac:	f2001ca9 			; <UNDEFINED> instruction: 0xf2001ca9
d00154b0:	4420605d 	strtmi	r6, [r0], #-93	; 0xffffffa3
d00154b4:	f8caf00c 			; <UNDEFINED> instruction: 0xf8caf00c
d00154b8:	28004602 	stmdacs	r0, {r1, r9, sl, lr}
d00154bc:	4651d1db 			; <UNDEFINED> instruction: 0x4651d1db
d00154c0:	b0034620 	andlt	r4, r3, r0, lsr #12
d00154c4:	4ff0e8bd 	svcmi	0x00f0e8bd
d00154c8:	bb42f7ff 	bllt	0xd10d34cc
d00154cc:	46594632 			; <UNDEFINED> instruction: 0x46594632
d00154d0:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d00154d4:	f1b0fa06 			; <UNDEFINED> instruction: 0xf1b0fa06
d00154d8:	db2a0a00 	blle	0xd0a97ce0
d00154dc:	46594632 			; <UNDEFINED> instruction: 0x46594632
d00154e0:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d00154e4:	2800f995 	stmdacs	r0, {r0, r2, r4, r7, r8, fp, ip, sp, lr, pc}
d00154e8:	2338da23 	teqcs	r8, #143360	; 0x23000
d00154ec:	f30afb03 	vqrdmulh.s<illegal width 8>	d15, d10, d3
d00154f0:	f50118e1 			; <UNDEFINED> instruction: 0xf50118e1
d00154f4:	f891317f 			; <UNDEFINED> instruction: 0xf891317f
d00154f8:	b9d2224d 	ldmiblt	r2, {r0, r2, r3, r6, r9, sp}^
d00154fc:	f8917828 			; <UNDEFINED> instruction: 0xf8917828
d0015500:	4282224c 	addmi	r2, r2, #76, 4	; 0xc0000004
d0015504:	f891d115 			; <UNDEFINED> instruction: 0xf891d115
d0015508:	7869024f 	stmdavc	r9!, {r0, r1, r2, r3, r6, r9}^
d001550c:	d1104288 	tstle	r0, r8, lsl #5
d0015510:	337ff503 	cmncc	pc, #12582912	; 0xc00000	; <UNPREDICTABLE>
d0015514:	f2031ca9 			; <UNDEFINED> instruction: 0xf2031ca9
d0015518:	18e02353 	stmiane	r0!, {r0, r1, r4, r6, r8, r9, sp}^
d001551c:	f896f00c 			; <UNDEFINED> instruction: 0xf896f00c
d0015520:	4652b938 			; <UNDEFINED> instruction: 0x4652b938
d0015524:	46202102 	strtmi	r2, [r0], -r2, lsl #2
d0015528:	e8bdb003 	pop	{r0, r1, ip, sp, pc}
d001552c:	f7ff4ff0 			; <UNDEFINED> instruction: 0xf7ff4ff0
d0015530:	4b08bb59 	blmi	0xd024429c
d0015534:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d0015538:	d1a82a00 			; <UNDEFINED> instruction: 0xd1a82a00
d001553c:	447a4a06 	ldrbtmi	r4, [sl], #-2566	; 0xfffff5fa
d0015540:	bf00e79f 	svclt	0x0000e79f
d0015544:	00012da8 	andeq	r2, r1, r8, lsr #27
d0015548:	ffffff46 			; <UNDEFINED> instruction: 0xffffff46
d001554c:	00012d4c 	andeq	r2, r1, ip, asr #26
d0015550:	ffffff34 			; <UNDEFINED> instruction: 0xffffff34
d0015554:	00012c90 	muleq	r1, r0, ip
d0015558:	fffffe9e 			; <UNDEFINED> instruction: 0xfffffe9e

Disassembly of section .text.local_callback_declaration.constprop.0:

d0015700 <.text.local_callback_declaration.constprop.0>:
d0015700:	47f0e92d 	ldrbmi	lr, [r0, sp, lsr #18]!
d0015704:	b0924e62 	addslt	r4, r2, r2, ror #28
d0015708:	46804a62 	strmi	r4, [r0], r2, ror #20
d001570c:	2128447e 			; <UNDEFINED> instruction: 0x2128447e
d0015710:	4630447a 			; <UNDEFINED> instruction: 0x4630447a
d0015714:	fc06f7fd 	stc2	7, cr15, [r6], {253}	; 0xfd
d0015718:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d001571c:	4a5e80b5 	bmi	0xd17b59f8
d0015720:	4630212a 	ldrtmi	r2, [r0], -sl, lsr #2
d0015724:	f7fd447a 			; <UNDEFINED> instruction: 0xf7fd447a
d0015728:	2800fbfd 	stmdacs	r0, {r0, r2, r3, r4, r5, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d001572c:	80acf000 	adchi	pc, ip, r0
d0015730:	0518f106 	ldreq	pc, [r8, #-262]	; 0xfffffefa
d0015734:	f10dac0a 			; <UNDEFINED> instruction: 0xf10dac0a
d0015738:	cd0f0928 	vstrgt.16	s0, [pc, #-80]	; 0xd00156f0	; <UNPREDICTABLE>
d001573c:	e895c40f 	ldm	r5, {r0, r1, r2, r3, sl, lr, pc}
d0015740:	e884000f 	stm	r4, {r0, r1, r2, r3}
d0015744:	4a55000f 	bmi	0xd1555788
d0015748:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d001574c:	447a4630 	ldrbtmi	r4, [sl], #-1584	; 0xfffff9d0
d0015750:	fbe8f7fd 	blx	0xcfa5374e
d0015754:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d0015758:	4a518097 	bmi	0xd14759bc
d001575c:	46302129 	ldrtmi	r2, [r0], -r9, lsr #2
d0015760:	f7fd447a 			; <UNDEFINED> instruction: 0xf7fd447a
d0015764:	2800fbdf 	stmdacs	r0, {r0, r1, r2, r3, r4, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d0015768:	808ef000 	addhi	pc, lr, r0
d001576c:	21284a4d 			; <UNDEFINED> instruction: 0x21284a4d
d0015770:	447a4630 	ldrbtmi	r4, [sl], #-1584	; 0xfffff9d0
d0015774:	fbd6f7fd 	blx	0xcf5d3772
d0015778:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d001577c:	6af38085 	bvs	0xcfcf5998
d0015780:	af082400 	svcge	0x00082400
d0015784:	7f84f5b3 	svcvc	0x0084f5b3
d0015788:	80bc9408 	adcshi	r9, ip, r8, lsl #8
d001578c:	d14c71bc 	strhle	r7, [ip, #-28]	; 0xffffffe4
d0015790:	2b296cf3 	blcs	0xd0a70b64
d0015794:	4630d14b 	ldrtmi	sp, [r0], -fp, asr #2
d0015798:	fb96f7fd 	blx	0xce5d3796
d001579c:	21294d42 			; <UNDEFINED> instruction: 0x21294d42
d00157a0:	447d4a42 	ldrbtmi	r4, [sp], #-2626	; 0xfffff5be
d00157a4:	4628447a 			; <UNDEFINED> instruction: 0x4628447a
d00157a8:	fbbcf7fd 	blx	0xcef537a6
d00157ac:	d06b2800 	rsble	r2, fp, r0, lsl #16
d00157b0:	9304230c 	movwls	r2, #17164	; 0x430c
d00157b4:	e913ab12 	ldmdb	r3, {r1, r4, r8, r9, fp, sp, pc}
d00157b8:	e88d000f 	stm	sp, {r0, r1, r2, r3}
d00157bc:	e899000f 	ldm	r9, {r0, r1, r2, r3}
d00157c0:	f7fe000f 			; <UNDEFINED> instruction: 0xf7fe000f
d00157c4:	6dabfc2f 	stcvs	12, cr15, [fp, #188]!	; 0xbc
d00157c8:	2b004606 	blcs	0xd0026fe8
d00157cc:	2330d15c 	teqcs	r0, #92, 2
d00157d0:	4020f88d 	eormi	pc, r0, sp, lsl #17
d00157d4:	46392207 	ldrtmi	r2, [r9], -r7, lsl #4
d00157d8:	f400fb03 			; <UNDEFINED> instruction: 0xf400fb03
d00157dc:	8021f88d 	eorhi	pc, r1, sp, lsl #17
d00157e0:	f5001928 			; <UNDEFINED> instruction: 0xf5001928
d00157e4:	f2002090 	vqadd.s8	d2, d16, d0
d00157e8:	f00b605b 			; <UNDEFINED> instruction: 0xf00b605b
d00157ec:	213dff1f 	teqcs	sp, pc, lsl pc	; <UNPREDICTABLE>
d00157f0:	f7fd4628 			; <UNDEFINED> instruction: 0xf7fd4628
d00157f4:	4601fb89 	strmi	pc, [r1], -r9, lsl #23
d00157f8:	d0412800 	suble	r2, r1, r0, lsl #16
d00157fc:	2090f504 	addscs	pc, r0, r4, lsl #10
d0015800:	605bf200 	subsvs	pc, fp, r0, lsl #4
d0015804:	f7ff4428 			; <UNDEFINED> instruction: 0xf7ff4428
d0015808:	4829fe05 	stmdami	r9!, {r0, r2, r9, sl, fp, ip, sp, lr, pc}
d001580c:	22004631 	andcs	r4, r0, #51380224	; 0x3100000
d0015810:	90074478 	andls	r4, r7, r8, ror r4
d0015814:	f9b7f7ff 			; <UNDEFINED> instruction: 0xf9b7f7ff
d0015818:	213b4a26 	teqcs	fp, r6, lsr #20
d001581c:	447a9807 	ldrbtmi	r9, [sl], #-2055	; 0xfffff7f9
d0015820:	e8bdb012 	pop	{r1, r4, ip, sp, pc}
d0015824:	f7fd47f0 			; <UNDEFINED> instruction: 0xf7fd47f0
d0015828:	2b29bb7d 	blcs	0xd0a84624
d001582c:	f8dfd0b6 			; <UNDEFINED> instruction: 0xf8dfd0b6
d0015830:	f10da088 			; <UNDEFINED> instruction: 0xf10da088
d0015834:	4d210622 	stcmi	6, cr0, [r1, #-136]!	; 0xffffff78
d0015838:	44fa2400 	ldrbtmi	r2, [sl], #1024	; 0x400
d001583c:	4652447d 			; <UNDEFINED> instruction: 0x4652447d
d0015840:	1107f240 	tstne	r7, r0, asr #4	; <UNPREDICTABLE>
d0015844:	f7fd4628 			; <UNDEFINED> instruction: 0xf7fd4628
d0015848:	b1e8fb6d 	mvnlt	pc, sp, ror #22
d001584c:	f2402300 	vcgt.s8	d18, d0, d0
d0015850:	34011101 	strcc	r1, [r1], #-257	; 0xfffffeff
d0015854:	f8064628 			; <UNDEFINED> instruction: 0xf8064628
d0015858:	f7fd3b01 			; <UNDEFINED> instruction: 0xf7fd3b01
d001585c:	212cfb55 	msrcs	LR_mon, r5
d0015860:	b2e44628 	rsclt	r4, r4, #40, 12	; 0x2800000
d0015864:	fb50f7fd 	blx	0xd1453862
d0015868:	d0972800 	addsle	r2, r7, r0, lsl #16
d001586c:	d1e62c05 	mvnle	r2, r5, lsl #24
d0015870:	46284913 			; <UNDEFINED> instruction: 0x46284913
d0015874:	b0124479 	andslt	r4, r2, r9, ror r4
d0015878:	47f0e8bd 			; <UNDEFINED> instruction: 0x47f0e8bd
d001587c:	bcf8f7fa 	ldcllt	7, cr15, [r8], #1000	; 0x3e8
d0015880:	f7ff4628 			; <UNDEFINED> instruction: 0xf7ff4628
d0015884:	e7c0fd44 	strb	pc, [r0, r4, asr #26]	; <UNPREDICTABLE>
d0015888:	e8bdb012 	pop	{r1, r4, ip, sp, pc}
d001588c:	bf0087f0 	svclt	0x000087f0
d0015890:	00012ab8 			; <UNDEFINED> instruction: 0x00012ab8
d0015894:	fffffe48 			; <UNDEFINED> instruction: 0xfffffe48
d0015898:	fffffe61 			; <UNDEFINED> instruction: 0xfffffe61
d001589c:	fffffe64 			; <UNDEFINED> instruction: 0xfffffe64
d00158a0:	fffffe7a 			; <UNDEFINED> instruction: 0xfffffe7a
d00158a4:	fffffe95 			; <UNDEFINED> instruction: 0xfffffe95
d00158a8:	00012a22 	andeq	r2, r1, r2, lsr #20
d00158ac:	fffffef6 			; <UNDEFINED> instruction: 0xfffffef6
d00158b0:	000129b4 			; <UNDEFINED> instruction: 0x000129b4
d00158b4:	fffffeab 			; <UNDEFINED> instruction: 0xfffffeab
d00158b8:	fffffe31 			; <UNDEFINED> instruction: 0xfffffe31
d00158bc:	00012988 	andeq	r2, r1, r8, lsl #19
d00158c0:	fffffdc8 			; <UNDEFINED> instruction: 0xfffffdc8

Disassembly of section .text.local_address:

d00158c4 <.text.local_address>:
d00158c4:	4604b510 			; <UNDEFINED> instruction: 0x4604b510
d00158c8:	2100008a 	smlabbcs	r0, sl, r0, r0
d00158cc:	fcddf7ff 	ldc2l	7, cr15, [sp], {255}	; 0xff
d00158d0:	f6414620 			; <UNDEFINED> instruction: 0xf6414620
d00158d4:	e8bd0138 	pop	{r3, r4, r5, r8}
d00158d8:	f7ff4010 			; <UNDEFINED> instruction: 0xf7ff4010
d00158dc:	Address 0x00000000d00158dc is out of bounds.


Disassembly of section .text.int_double_pointer_value:

d0015950 <.text.int_double_pointer_value>:
d0015950:	4ff8e92d 	svcmi	0x00f8e92d
d0015954:	f7ff4604 			; <UNDEFINED> instruction: 0xf7ff4604
d0015958:	bb28fce1 	bllt	0xd0a54ce4
d001595c:	46202126 	strtmi	r2, [r0], -r6, lsr #2
d0015960:	fad2f7fd 	blx	0xcf4d395c
d0015964:	46054a20 	strmi	r4, [r5], -r0, lsr #20
d0015968:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d001596c:	4620447a 			; <UNDEFINED> instruction: 0x4620447a
d0015970:	9024f8d4 	ldrdls	pc, [r4], -r4	; <UNPREDICTABLE>
d0015974:	8028f8d4 	ldrdhi	pc, [r8], -r4	; <UNPREDICTABLE>
d0015978:	7030f894 	mlasvc	r0, r4, r8, pc	; <UNPREDICTABLE>
d001597c:	e9d46b66 	ldmib	r4, {r1, r2, r5, r6, r8, r9, fp, sp, lr}^
d0015980:	f7fdab06 			; <UNDEFINED> instruction: 0xf7fdab06
d0015984:	b178facf 	cmnlt	r8, pc, asr #21	; <UNPREDICTABLE>
d0015988:	465a4651 			; <UNDEFINED> instruction: 0x465a4651
d001598c:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0015990:	1e01ff1f 	mcrne	15, 0, pc, cr1, cr15, {0}	; <UNPREDICTABLE>
d0015994:	6da3da0a 			; <UNDEFINED> instruction: 0x6da3da0a
d0015998:	4b14b933 	blmi	0xd0543e6c
d001599c:	66a6447b 	sxtabvs	r4, r6, fp, ror #8
d00159a0:	3916e9c4 	ldmdbcc	r6, {r2, r6, r7, r8, fp, sp, lr, pc}
d00159a4:	8718e9c4 	ldrhi	lr, [r8, -r4, asr #19]
d00159a8:	8ff8e8bd 	svchi	0x00f8e8bd
d00159ac:	fb032330 	blx	0xd00de676
d00159b0:	f5034301 			; <UNDEFINED> instruction: 0xf5034301
d00159b4:	f8932390 			; <UNDEFINED> instruction: 0xf8932390
d00159b8:	b1353659 	teqlt	r5, r9, asr r6
d00159bc:	d10c2b0a 	tstle	ip, sl, lsl #22
d00159c0:	e8bd4620 	pop	{r5, r9, sl, lr}
d00159c4:	f7ff4ff8 			; <UNDEFINED> instruction: 0xf7ff4ff8
d00159c8:	2b13bf7d 	blcs	0xd05057c4
d00159cc:	462ad105 	strtmi	sp, [sl], -r5, lsl #2
d00159d0:	e8bd4620 	pop	{r5, r9, sl, lr}
d00159d4:	f7ff4ff8 			; <UNDEFINED> instruction: 0xf7ff4ff8
d00159d8:	6da3b8bb 	stcvs	8, cr11, [r3, #748]!	; 0x2ec
d00159dc:	d1e32b00 	mvnle	r2, r0, lsl #22
d00159e0:	447b4b03 	ldrbtmi	r4, [fp], #-2819	; 0xfffff4fd
d00159e4:	bf00e7db 	svclt	0x0000e7db
d00159e8:	ffffff6e 			; <UNDEFINED> instruction: 0xffffff6e
d00159ec:	ffffff5e 			; <UNDEFINED> instruction: 0xffffff5e
d00159f0:	ffffff36 			; <UNDEFINED> instruction: 0xffffff36

Disassembly of section .text.record_member_pointer:

d0015a84 <.text.record_member_pointer>:
d0015a84:	447b4b44 	ldrbtmi	r4, [fp], #-2884	; 0xfffff4bc
d0015a88:	4ff0e92d 	svcmi	0x00f0e92d
d0015a8c:	460e4604 	strmi	r4, [lr], -r4, lsl #12
d0015a90:	8b04ed2d 	blhi	0xd0150f4c
d0015a94:	3a10ee09 	bcc	0xd04512c0
d0015a98:	9203b085 	andls	fp, r3, #133	; 0x85
d0015a9c:	ee1969a3 	vnmls.f16	s12, s19, s7
d0015aa0:	f2402a10 	vpmin.s8	d18, d0, d0
d0015aa4:	46201101 	strtmi	r1, [r0], -r1, lsl #2
d0015aa8:	3a10ee08 	bcc	0xd04512d0
d0015aac:	f8d469e3 			; <UNDEFINED> instruction: 0xf8d469e3
d0015ab0:	ee08b024 	cdp	0, 0, cr11, cr8, cr4, {1}
d0015ab4:	6aa33a90 	bvs	0xce8e44fc
d0015ab8:	9030f894 	mlasls	r0, r4, r8, pc	; <UNPREDICTABLE>
d0015abc:	6b639301 	blvs	0xd18fa6c8
d0015ac0:	f7fd9302 			; <UNDEFINED> instruction: 0xf7fd9302
d0015ac4:	b330fa2f 	teqlt	r0, #192512	; 0x2f000	; <UNPREDICTABLE>
d0015ac8:	731af44f 	tstvc	sl, #1325400064	; 0x4f000000	; <UNPREDICTABLE>
d0015acc:	fb032500 	blx	0xd00deed6
d0015ad0:	f507f706 			; <UNDEFINED> instruction: 0xf507f706
d0015ad4:	44273867 	strtmi	r3, [r7], #-2151	; 0xfffff799
d0015ad8:	78f4f508 	ldmvc	r4!, {r3, r8, sl, ip, sp, lr, pc}^
d0015adc:	3768f507 	strbcc	pc, [r8, -r7, lsl #10]!	; <UNPREDICTABLE>
d0015ae0:	0a08eb04 	beq	0xd02506f8
d0015ae4:	302af897 	mlacc	sl, r7, r8, pc	; <UNPREDICTABLE>
d0015ae8:	d81942ab 	ldmdale	r9, {r0, r1, r3, r5, r7, r9, lr}
d0015aec:	731af44f 	tstvc	sl, #1325400064	; 0x4f000000	; <UNPREDICTABLE>
d0015af0:	4606fb03 	strmi	pc, [r6], -r3, lsl #22
d0015af4:	3668f506 	strbtcc	pc, [r8], -r6, lsl #10	; <UNPREDICTABLE>
d0015af8:	302af896 	mlacc	sl, r6, r8, pc	; <UNPREDICTABLE>
d0015afc:	d11d42ab 	tstle	sp, fp, lsr #5
d0015b00:	b9436da3 	stmdblt	r3, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0015b04:	447b4b25 	ldrbtmi	r4, [fp], #-2853	; 0xfffff4db
d0015b08:	3b16e9c4 	blcc	0xd05d0220
d0015b0c:	e9c49b01 	stmib	r4, {r0, r8, r9, fp, ip, pc}^
d0015b10:	9b023918 	blls	0xd00a3f78
d0015b14:	b00566a3 	andlt	r6, r5, r3, lsr #13
d0015b18:	8b04ecbd 	blhi	0xd0150e14
d0015b1c:	8ff0e8bd 	svchi	0x00f0e8bd
d0015b20:	3004f8da 	ldrdcc	pc, [r4], -sl
d0015b24:	1a90ee18 	bne	0xce45138c
d0015b28:	2b24f85a 	blcs	0xd0953c98
d0015b2c:	0a10ee18 	beq	0xd0451394
d0015b30:	fdd8f7fa 	ldc2l	7, cr15, [r8, #1000]	; 0x3e8
d0015b34:	d1d92800 	bicsle	r2, r9, r0, lsl #16
d0015b38:	e7d33501 	ldrb	r3, [r3, r1, lsl #10]
d0015b3c:	fb032324 	blx	0xd00de7d6
d0015b40:	44258505 	strtmi	r8, [r5], #-1285	; 0xfffffafb
d0015b44:	f8958c6a 			; <UNDEFINED> instruction: 0xf8958c6a
d0015b48:	f8957020 			; <UNDEFINED> instruction: 0xf8957020
d0015b4c:	b14a6021 	cmplt	sl, r1, lsr #32
d0015b50:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d0015b54:	f7ff0092 			; <UNDEFINED> instruction: 0xf7ff0092
d0015b58:	f44ffb98 			; <UNDEFINED> instruction: 0xf44ffb98
d0015b5c:	462051c2 	strtmi	r5, [r0], -r2, asr #3
d0015b60:	ffd8f7fe 			; <UNDEFINED> instruction: 0xffd8f7fe
d0015b64:	d0002fff 	strdle	r2, [r0], -pc	; <UNPREDICTABLE>
d0015b68:	6da3b12e 	stfvsd	f3, [r3, #184]!	; 0xb8
d0015b6c:	d1d22b00 	bicsle	r2, r2, r0, lsl #22
d0015b70:	447b4b0b 	ldrbtmi	r4, [fp], #-2827	; 0xfffff4f5
d0015b74:	212ee7c8 	smlawtcs	lr, r8, r7, lr
d0015b78:	463e4620 	ldrtmi	r4, [lr], -r0, lsr #12
d0015b7c:	f9c4f7fd 			; <UNDEFINED> instruction: 0xf9c4f7fd
d0015b80:	d18b2800 	orrle	r2, fp, r0, lsl #16
d0015b84:	42bb9b03 	adcsmi	r9, fp, #3072	; 0xc00
d0015b88:	6da3d0c5 	stcvs	0, cr13, [r3, #788]!	; 0x314
d0015b8c:	d1c22b00 	bicle	r2, r2, r0, lsl #22
d0015b90:	447b4b04 	ldrbtmi	r4, [fp], #-2820	; 0xfffff4fc
d0015b94:	bf00e7b8 	svclt	0x0000e7b8
d0015b98:	ffffff6a 			; <UNDEFINED> instruction: 0xffffff6a
d0015b9c:	ffffff08 			; <UNDEFINED> instruction: 0xffffff08
d0015ba0:	fffffeb7 			; <UNDEFINED> instruction: 0xfffffeb7
d0015ba4:	fffffebf 			; <UNDEFINED> instruction: 0xfffffebf

Disassembly of section .text.record_pointer_field_address:

d0015c5c <.text.record_pointer_field_address>:
d0015c5c:	447b4b4f 	ldrbtmi	r4, [fp], #-2895	; 0xfffff4b1
d0015c60:	4ff0e92d 	svcmi	0x00f0e92d
d0015c64:	460d4604 	strmi	r4, [sp], -r4, lsl #12
d0015c68:	8b04ed2d 	blhi	0xd0151124
d0015c6c:	3a10ee09 	bcc	0xd0451498
d0015c70:	9203b085 	andls	fp, r3, #133	; 0x85
d0015c74:	ee1969a3 	vnmls.f16	s12, s19, s7
d0015c78:	f2402a10 	vpmin.s8	d18, d0, d0
d0015c7c:	46201101 	strtmi	r1, [r0], -r1, lsl #2
d0015c80:	3a10ee08 	bcc	0xd04514a8
d0015c84:	f8d469e3 			; <UNDEFINED> instruction: 0xf8d469e3
d0015c88:	ee08a024 	cdp	0, 0, cr10, cr8, cr4, {1}
d0015c8c:	6b633a90 	blvs	0xd18e46d4
d0015c90:	9028f8d4 	ldrdls	pc, [r8], -r4	; <UNPREDICTABLE>
d0015c94:	8030f894 	mlashi	r0, r4, r8, pc	; <UNPREDICTABLE>
d0015c98:	f7fd9301 			; <UNDEFINED> instruction: 0xf7fd9301
d0015c9c:	b330f943 	teqlt	r0, #1097728	; 0x10c000	; <UNPREDICTABLE>
d0015ca0:	731af44f 	tstvc	sl, #1325400064	; 0x4f000000	; <UNPREDICTABLE>
d0015ca4:	fb032600 	blx	0xd00df4ae
d0015ca8:	f507f705 			; <UNDEFINED> instruction: 0xf507f705
d0015cac:	44273b67 	strtmi	r3, [r7], #-2919	; 0xfffff499
d0015cb0:	7bf4f50b 	blvc	0xcfd530e4
d0015cb4:	3768f507 	strbcc	pc, [r8, -r7, lsl #10]!	; <UNPREDICTABLE>
d0015cb8:	030beb04 	movweq	lr, #47876	; 0xbb04
d0015cbc:	f8979302 			; <UNDEFINED> instruction: 0xf8979302
d0015cc0:	42b3302a 	adcsmi	r3, r3, #42	; 0x2a
d0015cc4:	f44fd818 	vst2.8	{d29-d30}, [pc :64], r8
d0015cc8:	fb03731a 	blx	0xd00f293a
d0015ccc:	f5054505 			; <UNDEFINED> instruction: 0xf5054505
d0015cd0:	f8953568 			; <UNDEFINED> instruction: 0xf8953568
d0015cd4:	42b3302a 	adcsmi	r3, r3, #42	; 0x2a
d0015cd8:	6da3d11e 	stfvsd	f5, [r3, #120]!	; 0x78
d0015cdc:	4b30b93b 	blmi	0xd0c441d0
d0015ce0:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0015ce4:	9b013a16 	blls	0xd0064544
d0015ce8:	9818e9c4 	ldmdals	r8, {r2, r6, r7, r8, fp, sp, lr, pc}
d0015cec:	b00566a3 	andlt	r6, r5, r3, lsr #13
d0015cf0:	8b04ecbd 	blhi	0xd0150fec
d0015cf4:	8ff0e8bd 	svchi	0x00f0e8bd
d0015cf8:	ee189902 	vnmls.f16	s18, s16, s4
d0015cfc:	9b020a10 	blls	0xd0098544
d0015d00:	2b24f851 	blcs	0xd0953e4c
d0015d04:	9102685b 	tstls	r2, fp, asr r8
d0015d08:	1a90ee18 	bne	0xce451570
d0015d0c:	fceaf7fa 	stc2l	7, cr15, [sl], #1000	; 0x3e8
d0015d10:	d1d82800 	bicsle	r2, r8, r0, lsl #16
d0015d14:	e7d23601 	ldrb	r3, [r2, r1, lsl #12]
d0015d18:	fb032324 	blx	0xd00de9b2
d0015d1c:	4426b606 	strtmi	fp, [r6], #-1542	; 0xfffff9fa
d0015d20:	f8968c72 			; <UNDEFINED> instruction: 0xf8968c72
d0015d24:	f8965020 			; <UNDEFINED> instruction: 0xf8965020
d0015d28:	b14a7021 	cmplt	sl, r1, lsr #32
d0015d2c:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d0015d30:	f7ff0092 			; <UNDEFINED> instruction: 0xf7ff0092
d0015d34:	f44ffaaa 	vst1.32	{d31-d32}, [pc :128], sl
d0015d38:	462051c2 	strtmi	r5, [r0], -r2, asr #3
d0015d3c:	feeaf7fe 	mcr2	7, 7, pc, cr10, cr14, {7}	; <UNPREDICTABLE>
d0015d40:	7191f44f 	orrsvc	pc, r1, pc, asr #8
d0015d44:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0015d48:	b170f8df 	ldrsblt	pc, [r0, #-143]!	; 0xffffff71	; <UNPREDICTABLE>
d0015d4c:	2dffb10f 	ldfcsp	f3, [pc, #60]!	; 0xd0015d90
d0015d50:	6da3d105 	stfvsd	f5, [r3, #20]!
d0015d54:	d1ca2b00 	bicle	r2, sl, r0, lsl #22
d0015d58:	447b4b12 	ldrbtmi	r4, [fp], #-2834	; 0xfffff4ee
d0015d5c:	f44fe7c1 	vst1.64	{d30}, [pc], r1
d0015d60:	462041d0 			; <UNDEFINED> instruction: 0x462041d0
d0015d64:	fed6f7fe 	mrc2	7, 6, pc, cr6, cr14, {7}
d0015d68:	212ee784 	smlawbcs	lr, r4, r7, lr
d0015d6c:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0015d70:	b148f8cb 	smlalbtlt	pc, r8, fp, r8	; <UNPREDICTABLE>
d0015d74:	2dffb917 			; <UNDEFINED> instruction: 0x2dffb917
d0015d78:	af7cf47f 	svcge	0x007cf47f
d0015d7c:	2b006da3 	blcs	0xd0031410
d0015d80:	4b09d1b5 	blmi	0xd028a45c
d0015d84:	e7ac447b 			; <UNDEFINED> instruction: 0xe7ac447b
d0015d88:	9b03b117 	blls	0xd01021ec
d0015d8c:	d0ae429d 	umlalle	r4, lr, sp, r2
d0015d90:	2b006da3 	blcs	0xd0031424
d0015d94:	4b05d1ab 	blmi	0xd018a448
d0015d98:	e7a2447b 			; <UNDEFINED> instruction: 0xe7a2447b
d0015d9c:	ffffff46 			; <UNDEFINED> instruction: 0xffffff46
d0015da0:	fffffee1 			; <UNDEFINED> instruction: 0xfffffee1
d0015da4:	fffffe8f 			; <UNDEFINED> instruction: 0xfffffe8f
d0015da8:	fffffe85 			; <UNDEFINED> instruction: 0xfffffe85
d0015dac:	fffffe92 			; <UNDEFINED> instruction: 0xfffffe92

Disassembly of section .text.struct_double_pointer_value:

d0015e90 <.text.struct_double_pointer_value>:
d0015e90:	4ff7e92d 	svcmi	0x00f7e92d
d0015e94:	460d4604 	strmi	r4, [sp], -r4, lsl #12
d0015e98:	fa40f7ff 	blx	0xd1053e9c
d0015e9c:	bb404680 	bllt	0xd10278a4
d0015ea0:	46202126 	strtmi	r2, [r0], -r6, lsr #2
d0015ea4:	f830f7fd 			; <UNDEFINED> instruction: 0xf830f7fd
d0015ea8:	4a3c6a63 	bmi	0xd0f3083c
d0015eac:	93004683 	movwls	r4, #1667	; 0x683
d0015eb0:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d0015eb4:	447a6aa3 	ldrbtmi	r6, [sl], #-2723	; 0xfffff55d
d0015eb8:	f8944620 			; <UNDEFINED> instruction: 0xf8944620
d0015ebc:	6b669030 	blvs	0xd19b9f84
d0015ec0:	e9d49301 	ldmib	r4, {r0, r8, r9, ip, pc}^
d0015ec4:	f7fd7a06 			; <UNDEFINED> instruction: 0xf7fd7a06
d0015ec8:	b190f82d 	orrslt	pc, r0, sp, lsr #16
d0015ecc:	46394652 			; <UNDEFINED> instruction: 0x46394652
d0015ed0:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0015ed4:	f1b0fc7d 			; <UNDEFINED> instruction: 0xf1b0fc7d
d0015ed8:	da0d0a00 	ble	0xd03586e0
d0015edc:	b9436da3 	stmdblt	r3, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0015ee0:	447b4b2f 	ldrbtmi	r4, [fp], #-2863	; 0xfffff4d1
d0015ee4:	9b0065a3 	blls	0xd002f578
d0015ee8:	65e366a6 	strbvs	r6, [r3, #1702]!	; 0x6a6
d0015eec:	e9c49b01 	stmib	r4, {r0, r8, r9, fp, ip, pc}^
d0015ef0:	b0033918 	andlt	r3, r3, r8, lsl r9
d0015ef4:	8ff0e8bd 	svchi	0x00f0e8bd
d0015ef8:	fb022230 	blx	0xd009e7c2
d0015efc:	f502420a 			; <UNDEFINED> instruction: 0xf502420a
d0015f00:	f8922290 			; <UNDEFINED> instruction: 0xf8922290
d0015f04:	f892765a 			; <UNDEFINED> instruction: 0xf892765a
d0015f08:	f1bb2659 			; <UNDEFINED> instruction: 0xf1bb2659
d0015f0c:	d0320f00 	eorsle	r0, r2, r0, lsl #30
d0015f10:	d1212a0e 			; <UNDEFINED> instruction: 0xd1212a0e
d0015f14:	7191f44f 	orrsvc	pc, r1, pc, asr #8
d0015f18:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0015f1c:	b160fff5 	strdlt	pc, [r0, #-245]!	; 0xffffff0b
d0015f20:	46514642 	ldrbmi	r4, [r1], -r2, asr #12
d0015f24:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0015f28:	462afe13 			; <UNDEFINED> instruction: 0x462afe13
d0015f2c:	46204639 			; <UNDEFINED> instruction: 0x46204639
d0015f30:	e8bdb003 	pop	{r0, r1, ip, sp, pc}
d0015f34:	f7ff4ff0 			; <UNDEFINED> instruction: 0xf7ff4ff0
d0015f38:	42afbe91 	adcmi	fp, pc, #2320	; 0x910
d0015f3c:	4651d106 	ldrbmi	sp, [r1], -r6, lsl #2
d0015f40:	b0034620 	andlt	r4, r3, r0, lsr #12
d0015f44:	4ff0e8bd 	svcmi	0x00f0e8bd
d0015f48:	bcbcf7ff 	ldclt	7, cr15, [ip], #1020	; 0x3fc
d0015f4c:	2b006da3 	blcs	0xd00315e0
d0015f50:	4b14d1cf 	blmi	0xd054a694
d0015f54:	e7c5447b 			; <UNDEFINED> instruction: 0xe7c5447b
d0015f58:	d1182a0d 	tstle	r8, sp, lsl #20
d0015f5c:	212e4a12 			; <UNDEFINED> instruction: 0x212e4a12
d0015f60:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d0015f64:	ffdef7fc 			; <UNDEFINED> instruction: 0xffdef7fc
d0015f68:	d0c22800 	sbcle	r2, r2, r0, lsl #16
d0015f6c:	46204651 			; <UNDEFINED> instruction: 0x46204651
d0015f70:	fca8f7ff 	stc2	7, cr15, [r8], #1020	; 0x3fc
d0015f74:	2a12e7d9 	bcs	0xd04cfee0
d0015f78:	42afd109 	adcmi	sp, pc, #1073741826	; 0x40000002
d0015f7c:	465ad107 	ldrbmi	sp, [sl], -r7, lsl #2
d0015f80:	46204651 			; <UNDEFINED> instruction: 0x46204651
d0015f84:	e8bdb003 	pop	{r0, r1, ip, sp, pc}
d0015f88:	f7fe4ff0 			; <UNDEFINED> instruction: 0xf7fe4ff0
d0015f8c:	6da3bde1 	stcvs	13, cr11, [r3, #900]!	; 0x384
d0015f90:	d1ae2b00 			; <UNDEFINED> instruction: 0xd1ae2b00
d0015f94:	447b4b05 	ldrbtmi	r4, [fp], #-2821	; 0xfffff4fb
d0015f98:	bf00e7a4 	svclt	0x0000e7a4
d0015f9c:	fffffef6 			; <UNDEFINED> instruction: 0xfffffef6
d0015fa0:	fffffef9 			; <UNDEFINED> instruction: 0xfffffef9
d0015fa4:	fffffeb7 			; <UNDEFINED> instruction: 0xfffffeb7
d0015fa8:	fffffed1 			; <UNDEFINED> instruction: 0xfffffed1
d0015fac:	fffffeb8 			; <UNDEFINED> instruction: 0xfffffeb8

Disassembly of section .text.patch_branch.isra.0.part.0:

d0015fb0 <.text.patch_branch.isra.0.part.0>:
d0015fb0:	e92d1a09 	push	{r0, r3, r9, fp, ip}
d0015fb4:	1f0d41f0 	svcne	0x000d41f0
d0015fb8:	46064690 			; <UNDEFINED> instruction: 0x46064690
d0015fbc:	6300f3c5 	movwvs	pc, #965	; 0x3c5	; <UNPREDICTABLE>
d0015fc0:	3109f3c5 	smlabtcc	r9, r5, r3, pc	; <UNPREDICTABLE>
d0015fc4:	54d5ea83 	ldrbpl	lr, [r5], #2691	; 0xa83
d0015fc8:	2183ea41 	orrcs	lr, r3, r1, asr #20
d0015fcc:	f44143e4 	vst2.<illegal width 64>	{d20-d23}, [r1 :128], r4
d0015fd0:	f0044170 			; <UNDEFINED> instruction: 0xf0044170
d0015fd4:	ea830701 	b	0xce0d7be0
d0015fd8:	f7fe5495 			; <UNDEFINED> instruction: 0xf7fe5495
d0015fdc:	f3c5fd7f 	vmvn.i32	<illegal reg q15.5>, #14680063	; 0x00dfffff
d0015fe0:	43e4054a 	mvnmi	r0, #310378496	; 0x12800000
d0015fe4:	0f00f1b8 	svceq	0x0000f1b8
d0015fe8:	0002f106 	andeq	pc, r2, r6, lsl #2
d0015fec:	0401f004 	streq	pc, [r1], #-4
d0015ff0:	f44fbf14 			; <UNDEFINED> instruction: 0xf44fbf14
d0015ff4:	f44f4150 	vst4.16	{d20,d22,d24,d26}, [pc :64], r0
d0015ff8:	02e44110 	rsceq	r4, r4, #16, 2
d0015ffc:	3447ea44 	strbcc	lr, [r7], #-2628	; 0xfffff5bc
d0016000:	4321432c 			; <UNDEFINED> instruction: 0x4321432c
d0016004:	41f0e8bd 	ldrhmi	lr, [r0, #141]!	; 0x8d
d0016008:	bd68f7fe 	stcllt	7, cr15, [r8, #-1016]!	; 0xfffffc08

Disassembly of section .text.patch_branch.isra.0:

d001600c <.text.patch_branch.isra.0>:
d001600c:	4604b410 			; <UNDEFINED> instruction: 0x4604b410
d0016010:	46114608 	ldrmi	r4, [r1], -r8, lsl #12
d0016014:	b91c461a 	ldmdblt	ip, {r1, r3, r4, r9, sl, lr}
d0016018:	4b04f85d 	blmi	0xd0154194
d001601c:	bfc8f7ff 	svclt	0x00c8f7ff
d0016020:	4b04f85d 	blmi	0xd015419c
d0016024:	Address 0x00000000d0016024 is out of bounds.


Disassembly of section .text.expression:

d0016238 <.text.expression>:
d0016238:	4ff0e92d 	svcmi	0x00f0e92d
d001623c:	46046a03 	strmi	r6, [r4], -r3, lsl #20
d0016240:	9024f8d0 	ldrdls	pc, [r4], -r0	; <UNPREDICTABLE>
d0016244:	a030f890 	mlasge	r0, r0, r8, pc	; <UNPREDICTABLE>
d0016248:	8b06ed2d 	blhi	0xd01d1704
d001624c:	9305b08d 	movwls	fp, #20621	; 0x508d
d0016250:	f5009203 			; <UNDEFINED> instruction: 0xf5009203
d0016254:	91042292 			; <UNDEFINED> instruction: 0x91042292
d0016258:	b30ae9d0 	movwlt	lr, #43472	; 0xa9d0
d001625c:	6b439306 	blvs	0xd10fae7c
d0016260:	f8d29301 			; <UNDEFINED> instruction: 0xf8d29301
d0016264:	33013244 	movwcc	r3, #4676	; 0x1244
d0016268:	f8c22b20 			; <UNDEFINED> instruction: 0xf8c22b20
d001626c:	d9043244 	stmdble	r4, {r2, r6, r9, ip, sp}
d0016270:	15e8f8df 	strbne	pc, [r8, #2271]!	; 0x8df	; <UNPREDICTABLE>
d0016274:	f7f94479 			; <UNDEFINED> instruction: 0xf7f94479
d0016278:	9b03fffb 	blls	0xd011626c
d001627c:	42411ed8 	submi	r1, r1, #216, 28	; 0xd80
d0016280:	46204141 	strtmi	r4, [r0], -r1, asr #2
d0016284:	fc08f002 	stc2	0, cr15, [r8], {2}
d0016288:	35d4f8df 	ldrbcc	pc, [r4, #2271]	; 0x8df	; <UNPREDICTABLE>
d001628c:	447b4605 	ldrbtmi	r4, [fp], #-1541	; 0xfffff9fb
d0016290:	f8df9308 			; <UNDEFINED> instruction: 0xf8df9308
d0016294:	447b35d0 	ldrbtmi	r3, [fp], #-1488	; 0xfffffa30
d0016298:	6da69309 	stcvs	3, cr9, [r6, #36]!	; 0x24
d001629c:	6ae7b9b6 	bvs	0xcfa0497c
d00162a0:	f0002f7c 			; <UNDEFINED> instruction: 0xf0002f7c
d00162a4:	f3008167 	vrhadd.u8	q4, q0, <illegal reg q11.5>
d00162a8:	2f2f8136 	svccs	0x002f8136
d00162ac:	8128f300 	msrhi	(UNDEF: 56), r0
d00162b0:	f3002f24 	vpmax.f32	d2, d0, d20
d00162b4:	9b048115 	blls	0xd0136710
d00162b8:	dc0742b3 	sfmle	f4, 4, [r7], {179}	; 0xb3
d00162bc:	d1362d02 	teqle	r6, r2, lsl #26
d00162c0:	15a4f8df 	strne	pc, [r4, #2271]!	; 0x8df
d00162c4:	44794620 	ldrbtmi	r4, [r9], #-1568	; 0xfffff9e0
d00162c8:	ffd2f7f9 			; <UNDEFINED> instruction: 0xffd2f7f9
d00162cc:	b9be6da6 	ldmiblt	lr!, {r1, r2, r5, r7, r8, sl, fp, sp, lr}
d00162d0:	2b019b04 	blcs	0xd007cee8
d00162d4:	213fd114 	teqcs	pc, r4, lsl r1	; <UNPREDICTABLE>
d00162d8:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d00162dc:	b178fe15 	cmnlt	r8, r5, lsl lr	; <UNPREDICTABLE>
d00162e0:	0304f025 	movweq	pc, #16421	; 0x4025	; <UNPREDICTABLE>
d00162e4:	f0402b02 			; <UNDEFINED> instruction: 0xf0402b02
d00162e8:	6da3814d 	stfvsd	f0, [r3, #308]!	; 0x134
d00162ec:	f8dfb943 			; <UNDEFINED> instruction: 0xf8dfb943
d00162f0:	447b357c 	ldrbtmi	r3, [fp], #-1404	; 0xfffffa84
d00162f4:	3916e9c4 	ldmdbcc	r6, {r2, r6, r7, r8, fp, sp, lr, pc}
d00162f8:	e9c49b01 	stmib	r4, {r0, r8, r9, fp, ip, pc}^
d00162fc:	66a3ba18 	ssatvs	fp, #4, r8, lsl #20
d0016300:	3b019b03 	blcc	0xd007cf14
d0016304:	f2002b01 	vqdmulh.s<illegal width 8>	d2, d0, d1
d0016308:	2d028232 	sfmcs	f0, 1, [r2, #-200]	; 0xffffff38
d001630c:	6da3d10a 	stfvsd	f5, [r3, #40]!	; 0x28
d0016310:	f8dfb943 			; <UNDEFINED> instruction: 0xf8dfb943
d0016314:	447b355c 	ldrbtmi	r3, [fp], #-1372	; 0xfffffaa4
d0016318:	3916e9c4 	ldmdbcc	r6, {r2, r6, r7, r8, fp, sp, lr, pc}
d001631c:	e9c49b01 	stmib	r4, {r0, r8, r9, fp, ip, pc}^
d0016320:	66a3ba18 	ssatvs	fp, #4, r8, lsl #20
d0016324:	2b019b03 	blcs	0xd007cf38
d0016328:	8231f040 	eorshi	pc, r1, #64	; 0x40
d001632c:	4620e222 	strtmi	lr, [r0], -r2, lsr #4
d0016330:	f7fc3601 			; <UNDEFINED> instruction: 0xf7fc3601
d0016334:	f5a7fdc9 			; <UNDEFINED> instruction: 0xf5a7fdc9
d0016338:	2b017390 	blcs	0xd0073180
d001633c:	f240d831 	vtst.8	d29, d0, d17
d0016340:	46201521 	strtmi	r1, [r0], -r1, lsr #10
d0016344:	42551b7a 	subsmi	r1, r5, #124928	; 0x1e800
d0016348:	46294155 			; <UNDEFINED> instruction: 0x46294155
d001634c:	fc97f7fe 	ldc2	7, cr15, [r7], {254}	; 0xfe
d0016350:	46312202 	ldrtmi	r2, [r1], -r2, lsl #4
d0016354:	46204607 	strtmi	r4, [r0], -r7, lsl #12
d0016358:	368ff504 	strcc	pc, [pc], r4, lsl #10
d001635c:	ff6cf7ff 			; <UNDEFINED> instruction: 0xff6cf7ff
d0016360:	5120f44f 	msrpl	CPSR_, pc, asr #8
d0016364:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0016368:	2101fbd5 	ldrdcs	pc, [r1, -r5]
d001636c:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0016370:	4620fc9c 			; <UNDEFINED> instruction: 0x4620fc9c
d0016374:	fc74f7fe 	ldc2l	7, cr15, [r4], #-1016	; 0xfffffc08
d0016378:	f8d62300 			; <UNDEFINED> instruction: 0xf8d62300
d001637c:	468021b8 			; <UNDEFINED> instruction: 0x468021b8
d0016380:	6da04639 	stcvs	6, cr4, [r0, #228]!	; 0xe4
d0016384:	fe42f7ff 	mcr2	7, 2, pc, cr2, cr15, {7}	; <UNPREDICTABLE>
d0016388:	46204629 	strtmi	r4, [r0], -r9, lsr #12
d001638c:	ffbff7fe 			; <UNDEFINED> instruction: 0xffbff7fe
d0016390:	f8d62300 			; <UNDEFINED> instruction: 0xf8d62300
d0016394:	464121b8 			; <UNDEFINED> instruction: 0x464121b8
d0016398:	f7ff6da0 			; <UNDEFINED> instruction: 0xf7ff6da0
d001639c:	2500fe37 	strcs	pc, [r0, #-3639]	; 0xfffff1c9
d00163a0:	f5a7e77b 			; <UNDEFINED> instruction: 0xf5a7e77b
d00163a4:	2d03738e 	stccs	3, cr7, [r3, #-568]	; 0xfffffdc8
d00163a8:	d0029302 	andle	r9, r2, r2, lsl #6
d00163ac:	2b021f6b 	blcs	0xd009e160
d00163b0:	9b02d80f 	blls	0xd00cc3f4
d00163b4:	d90c2b01 	stmdble	ip, {r0, r8, r9, fp, sp}
d00163b8:	2b006da3 	blcs	0xd0031a4c
d00163bc:	f8dfd186 			; <UNDEFINED> instruction: 0xf8dfd186
d00163c0:	447b34b4 	ldrbtmi	r3, [fp], #-1204	; 0xfffffb4c
d00163c4:	3916e9c4 	ldmdbcc	r6, {r2, r6, r7, r8, fp, sp, lr, pc}
d00163c8:	e9c49b01 	stmib	r4, {r0, r8, r9, fp, ip, pc}^
d00163cc:	66a3ba18 	ssatvs	fp, #4, r8, lsl #20
d00163d0:	f24be77c 	vaba.s8	q15, <illegal reg q5.5>, q14
d00163d4:	46204103 	strtmi	r4, [r0], -r3, lsl #2
d00163d8:	fb9cf7fe 	blx	0xce7543da
d00163dc:	46316a23 	ldrtmi	r6, [r1], -r3, lsr #20
d00163e0:	46202202 	strtmi	r2, [r0], -r2, lsl #4
d00163e4:	f8d49307 			; <UNDEFINED> instruction: 0xf8d49307
d00163e8:	f7ff802c 			; <UNDEFINED> instruction: 0xf7ff802c
d00163ec:	f64bff25 			; <UNDEFINED> instruction: 0xf64bff25
d00163f0:	46064106 	strmi	r4, [r6], -r6, lsl #2
d00163f4:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d00163f8:	2d04fb8d 	vstrcs	d15, [r4, #-564]	; 0xfffffdcc
d00163fc:	81f8f000 	mvnshi	pc, r0
d0016400:	d1112e04 	tstle	r1, r4, lsl #28
d0016404:	f0402f2b 			; <UNDEFINED> instruction: 0xf0402f2b
d0016408:	1eeb8209 	cdpne	2, 14, cr8, cr11, cr9, {0}
d001640c:	f2402b01 	vqdmulh.s<illegal width 8>	d18, d0, d1
d0016410:	21898208 	orrcs	r8, r9, r8, lsl #4
d0016414:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0016418:	f641fb7d 			; <UNDEFINED> instruction: 0xf641fb7d
d001641c:	46200108 	strtmi	r0, [r0], -r8, lsl #2
d0016420:	f7fe2504 			; <UNDEFINED> instruction: 0xf7fe2504
d0016424:	e738fb77 			; <UNDEFINED> instruction: 0xe738fb77
d0016428:	d0072d03 	andle	r2, r7, r3, lsl #26
d001642c:	d0052e03 	andle	r2, r5, r3, lsl #28
d0016430:	2b021f6b 	blcs	0xd009e1e4
d0016434:	1f73d902 	svcne	0x0073d902
d0016438:	d8392b02 	ldmdale	r9!, {r1, r8, r9, fp, sp}
d001643c:	f5a89b06 			; <UNDEFINED> instruction: 0xf5a89b06
d0016440:	f5a37881 			; <UNDEFINED> instruction: 0xf5a37881
d0016444:	2b017381 	blcs	0xd0073250
d0016448:	9b05bf97 	blls	0xd01862ac
d001644c:	fab32300 	blx	0xcecdf054
d0016450:	095bf383 	ldmdbeq	fp, {r0, r1, r7, r8, r9, ip, sp, lr, pc}^
d0016454:	0f01f1b8 	svceq	0x0001f1b8
d0016458:	9a07bf97 	bls	0xd02062bc
d001645c:	fab22200 	blx	0xcec9ec64
d0016460:	0952f282 	ldmdbeq	r2, {r1, r7, r9, ip, sp, lr, pc}^
d0016464:	d0092d04 	andle	r2, r9, r4, lsl #26
d0016468:	f0402d03 			; <UNDEFINED> instruction: 0xf0402d03
d001646c:	1ef381be 	mrcne	1, 7, r8, cr3, cr14, {5}
d0016470:	d80c2b01 	stmdale	ip, {r0, r8, r9, fp, sp}
d0016474:	2b019b02 	blcs	0xd007d084
d0016478:	e013d80b 	ands	sp, r3, fp, lsl #16
d001647c:	29011ef1 	stmdbcs	r1, {r0, r4, r5, r6, r7, r9, sl, fp, ip}
d0016480:	2e00d9f8 			; <UNDEFINED> instruction: 0x2e00d9f8
d0016484:	81a4f040 			; <UNDEFINED> instruction: 0x81a4f040
d0016488:	d1f32a00 	mvnsle	r2, r0, lsl #20
d001648c:	2e00e001 	cdpcs	0, 0, cr14, cr0, cr1, {0}
d0016490:	6da3d0fa 	stcvs	0, cr13, [r3, #1000]!	; 0x3e8
d0016494:	9b08b933 	blls	0xd0244968
d0016498:	3916e9c4 	ldmdbcc	r6, {r2, r6, r7, r8, fp, sp, lr, pc}
d001649c:	e9c49b01 	stmib	r4, {r0, r8, r9, fp, ip, pc}^
d00164a0:	66a3ba18 	ssatvs	fp, #4, r8, lsl #20
d00164a4:	46392201 	ldrtmi	r2, [r9], -r1, lsl #4
d00164a8:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d00164ac:	e776fc76 			; <UNDEFINED> instruction: 0xe776fc76
d00164b0:	7393f46f 	orrsvc	pc, r3, #1862270976	; 0x6f000000
d00164b4:	2b0118fb 	blcs	0xd005c8a8
d00164b8:	2d01d80c 	stccs	8, cr13, [r1, #-48]	; 0xffffffd0
d00164bc:	2500bf14 	strcs	fp, [r0, #-3860]	; 0xfffff0ec
d00164c0:	462a2501 	strtmi	r2, [sl], -r1, lsl #10
d00164c4:	46204639 			; <UNDEFINED> instruction: 0x46204639
d00164c8:	fc67f7fe 	stc2l	7, cr15, [r7], #-1016	; 0xfffffc08
d00164cc:	bf181e05 	svclt	0x00181e05
d00164d0:	e6e22501 	strbt	r2, [r2], r1, lsl #10
d00164d4:	d0f42d01 	rscsle	r2, r4, r1, lsl #26
d00164d8:	e7ef2e01 	strb	r2, [pc, r1, lsl #28]!
d00164dc:	e6ea2602 	strbt	r2, [sl], r2, lsl #12
d00164e0:	0325f1a7 	msreq	CPSR_sc, #-1073741783	; 0xc0000029
d00164e4:	d8092b0a 	stmdale	r9, {r1, r3, r8, r9, fp, sp}
d00164e8:	f003e8df 			; <UNDEFINED> instruction: 0xf003e8df
d00164ec:	08084842 	stmdaeq	r8, {r1, r6, fp, lr}
d00164f0:	08064208 	stmdaeq	r6, {r3, r9, lr}
d00164f4:	00420806 	subeq	r0, r2, r6, lsl #16
d00164f8:	e6dc2609 	ldrb	r2, [ip], r9, lsl #12
d00164fc:	e6da2600 	ldrb	r2, [sl], r0, lsl #12
d0016500:	d03d2f5e 	eorsle	r2, sp, lr, asr pc
d0016504:	aed7f73f 	mrcge	7, 6, APSR_nzcv, cr7, cr15, {1}
d0016508:	0302f027 	movweq	pc, #8231	; 0x2027	; <UNPREDICTABLE>
d001650c:	bf142b3c 	svclt	0x00142b3c
d0016510:	26072600 	strcs	r2, [r7], -r0, lsl #12
d0016514:	f5a7e6cf 			; <UNDEFINED> instruction: 0xf5a7e6cf
d0016518:	2b0c738e 	blcs	0xd0333358
d001651c:	aecbf63f 	mcrge	6, 6, pc, cr11, cr15, {1}	; <UNPREDICTABLE>
d0016520:	d8eb2b0c 	stmiale	fp!, {r2, r3, r8, r9, fp, sp}^
d0016524:	f852a202 			; <UNDEFINED> instruction: 0xf852a202
d0016528:	441a3023 	ldrmi	r3, [sl], #-35	; 0xffffffdd
d001652c:	bf004710 	svclt	0x00004710
d0016530:	00000035 	andeq	r0, r0, r5, lsr r0
d0016534:	00000035 	andeq	r0, r0, r5, lsr r0
d0016538:	00000039 	andeq	r0, r0, r9, lsr r0
d001653c:	00000039 	andeq	r0, r0, r9, lsr r0
d0016540:	ffffffad 			; <UNDEFINED> instruction: 0xffffffad
d0016544:	00000049 	andeq	r0, r0, r9, asr #32
d0016548:	ffffffcd 			; <UNDEFINED> instruction: 0xffffffcd
d001654c:	ffffffcd 			; <UNDEFINED> instruction: 0xffffffcd
d0016550:	ffffffcd 			; <UNDEFINED> instruction: 0xffffffcd
d0016554:	ffffffcd 			; <UNDEFINED> instruction: 0xffffffcd
d0016558:	ffffffcd 			; <UNDEFINED> instruction: 0xffffffcd
d001655c:	0000003d 	andeq	r0, r0, sp, lsr r0
d0016560:	0000003d 	andeq	r0, r0, sp, lsr r0
d0016564:	e6a62606 	strt	r2, [r6], r6, lsl #12
d0016568:	e6a42607 	strt	r2, [r4], r7, lsl #12
d001656c:	e6a22608 	strt	r2, [r2], r8, lsl #12
d0016570:	e6a0260a 	strt	r2, [r0], sl, lsl #12
d0016574:	e69e2603 	ldr	r2, [lr], r3, lsl #12
d0016578:	e69c2601 	ldr	r2, [ip], r1, lsl #12
d001657c:	e69a2605 	ldr	r2, [sl], r5, lsl #12
d0016580:	e6982604 	ldr	r2, [r8], r4, lsl #12
d0016584:	46204631 			; <UNDEFINED> instruction: 0x46204631
d0016588:	fb79f7fe 	blx	0xd1e9458a
d001658c:	463269a3 	ldrtmi	r6, [r2], -r3, lsr #19
d0016590:	ee089904 	vmla.f16	s18, s16, s8
d0016594:	69e33a10 	stmibvs	r3!, {r4, r9, fp, ip, sp}^
d0016598:	46204680 	strtmi	r4, [r0], -r0, lsl #13
d001659c:	3a90ee08 	bcc	0xce451dc4
d00165a0:	930a6a23 	movwls	r6, #43555	; 0xaa23
d00165a4:	93076ae3 	movwls	r6, #31459	; 0x7ae3
d00165a8:	fe46f7ff 	mcr2	7, 2, pc, cr6, cr15, {7}	; <UNPREDICTABLE>
d00165ac:	2392f504 	orrscs	pc, r2, #4, 10	; 0x1000000
d00165b0:	46074ab1 			; <UNDEFINED> instruction: 0x46074ab1
d00165b4:	9309213a 	movwls	r2, #37178	; 0x913a
d00165b8:	f8d3447a 			; <UNDEFINED> instruction: 0xf8d3447a
d00165bc:	46203248 	strtmi	r3, [r0], -r8, asr #4
d00165c0:	f7fc9302 			; <UNDEFINED> instruction: 0xf7fc9302
d00165c4:	2800fcaf 	stmdacs	r0, {r0, r1, r2, r3, r5, r7, sl, fp, ip, sp, lr, pc}
d00165c8:	ae9af43f 	mrcge	4, 4, APSR_nzcv, cr10, cr15, {1}
d00165cc:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d00165d0:	f504fb47 			; <UNDEFINED> instruction: 0xf504fb47
d00165d4:	4641328f 	strbmi	r3, [r1], -pc, lsl #5
d00165d8:	f8d24633 			; <UNDEFINED> instruction: 0xf8d24633
d00165dc:	ee0a21b8 	mcr	1, 0, r2, cr10, cr8, {5}
d00165e0:	6da00a10 			; <UNDEFINED> instruction: 0x6da00a10
d00165e4:	fd12f7ff 	ldc2	7, cr15, [r2, #-1020]	; 0xfffffc04
d00165e8:	463269a3 	ldrtmi	r6, [r2], -r3, lsr #19
d00165ec:	ee099904 	vmla.f16	s18, s18, s8
d00165f0:	69e33a10 	stmibvs	r3!, {r4, r9, fp, ip, sp}^
d00165f4:	ee094620 	cfmadd32	mvax1, mvfx4, mvfx9, mvfx0
d00165f8:	6a233a90 	bvs	0xd08e5040
d00165fc:	6ae3930b 	bvs	0xcf8fb230
d0016600:	f7ff9308 			; <UNDEFINED> instruction: 0xf7ff9308
d0016604:	9a07fe19 	bls	0xd0215e70
d0016608:	9b094680 	blls	0xd0268010
d001660c:	7281f5a2 	addvc	pc, r1, #679477248	; 0x28800000
d0016610:	3248f8d3 	subcc	pc, r8, #13828096	; 0xd30000
d0016614:	d8202a01 	stmdale	r0!, {r0, r9, fp, sp}
d0016618:	fab29a0a 	blx	0xcecbce48
d001661c:	0976f682 	ldmdbeq	r6!, {r1, r7, r9, sl, ip, sp, lr, pc}^
d0016620:	f5a29a08 			; <UNDEFINED> instruction: 0xf5a29a08
d0016624:	2a017281 	bcs	0xd0073030
d0016628:	9a0bd82a 	bls	0xd030c6d8
d001662c:	f082fab2 			; <UNDEFINED> instruction: 0xf082fab2
d0016630:	f0270940 			; <UNDEFINED> instruction: 0xf0270940
d0016634:	2a020204 	bcs	0xd0096e4c
d0016638:	f028d003 			; <UNDEFINED> instruction: 0xf028d003
d001663c:	2a020204 	bcs	0xd0096e54
d0016640:	6da3d133 	stfvsd	f5, [r3, #204]!	; 0xcc
d0016644:	d1392b00 	teqle	r9, r0, lsl #22
d0016648:	447b4b8c 	ldrbtmi	r4, [fp], #-2956	; 0xfffff474
d001664c:	3916e9c4 	ldmdbcc	r6, {r2, r6, r7, r8, fp, sp, lr, pc}
d0016650:	e9c49b01 	stmib	r4, {r0, r8, r9, fp, ip, pc}^
d0016654:	66a3ba18 	ssatvs	fp, #4, r8, lsl #20
d0016658:	f240e030 	vqadd.s8	d30, d0, d16
d001665c:	99071201 	stmdbls	r7, {r0, r9, ip}
d0016660:	d1dd4291 			; <UNDEFINED> instruction: 0xd1dd4291
d0016664:	ee184a86 	vnmls.f32	s8, s17, s12
d0016668:	ee181a90 	vmov	r1, s17
d001666c:	93040a10 	movwls	r0, #18960	; 0x4a10
d0016670:	f7fa447a 			; <UNDEFINED> instruction: 0xf7fa447a
d0016674:	1e06f95f 			; <UNDEFINED> instruction: 0x1e06f95f
d0016678:	bf189b04 	svclt	0x00189b04
d001667c:	e7cf2601 	strb	r2, [pc, r1, lsl #12]
d0016680:	1201f240 	andne	pc, r1, #64, 4
d0016684:	42919908 	addsmi	r9, r1, #8, 18	; 0x20000
d0016688:	4a7ed10d 	bmi	0xd1fcaac4
d001668c:	1a90ee19 	bne	0xce451ef8
d0016690:	0a10ee19 	beq	0xd0451efc
d0016694:	447a9304 	ldrbtmi	r9, [sl], #-772	; 0xfffffcfc
d0016698:	f94cf7fa 			; <UNDEFINED> instruction: 0xf94cf7fa
d001669c:	9b043800 	blls	0xd01246a4
d00166a0:	2001bf18 	andcs	fp, r1, r8, lsl pc
d00166a4:	2000e7c5 	andcs	lr, r0, r5, asr #15
d00166a8:	2f01e7c3 	svccs	0x0001e7c3
d00166ac:	f1b8d811 			; <UNDEFINED> instruction: 0xf1b8d811
d00166b0:	d83b0f01 	ldmdale	fp!, {r0, r8, r9, sl, fp}
d00166b4:	bf142f01 	svclt	0x00142f01
d00166b8:	25014645 	strcs	r4, [r1, #-1605]	; 0xfffff9bb
d00166bc:	328ff504 	addcc	pc, pc, #4, 10	; 0x1000000
d00166c0:	ee1a2300 	cdp	3, 1, cr2, cr10, cr0, {0}
d00166c4:	6da01a10 			; <UNDEFINED> instruction: 0x6da01a10
d00166c8:	21b8f8d2 			; <UNDEFINED> instruction: 0x21b8f8d2
d00166cc:	fc9ef7ff 	ldc2	7, cr15, [lr], {255}	; 0xff
d00166d0:	4547e616 	strbmi	lr, [r7, #-1558]	; 0xfffff9ea
d00166d4:	2f05d120 	svccs	0x0005d120
d00166d8:	2f03d001 	svccs	0x0003d001
d00166dc:	9a02d115 	bls	0xd00cab38
d00166e0:	d012429a 	mulsle	r2, sl, r2
d00166e4:	b948b9b6 	stmdblt	r8, {r1, r2, r4, r5, r7, r8, fp, ip, sp, pc}^
d00166e8:	b93b6da3 	ldmdblt	fp!, {r0, r1, r5, r7, r8, sl, fp, sp, lr}
d00166ec:	447b4b66 	ldrbtmi	r4, [fp], #-2918	; 0xfffff49a
d00166f0:	3916e9c4 	ldmdbcc	r6, {r2, r6, r7, r8, fp, sp, lr, pc}
d00166f4:	e9c49b01 	stmib	r4, {r0, r8, r9, fp, ip, pc}^
d00166f8:	66a3ba18 	ssatvs	fp, #4, r8, lsl #20
d00166fc:	2392f504 	orrscs	pc, r2, #4, 10	; 0x1000000
d0016700:	f8c39a02 			; <UNDEFINED> instruction: 0xf8c39a02
d0016704:	463d2248 	ldrtmi	r2, [sp], -r8, asr #4
d0016708:	9a02e7d8 	bls	0xd00d0670
d001670c:	bf182e00 	svclt	0x00182e00
d0016710:	4613461a 			; <UNDEFINED> instruction: 0x4613461a
d0016714:	e7f19302 	ldrb	r9, [r1, r2, lsl #6]!
d0016718:	d1072f04 	tstle	r7, r4, lsl #30
d001671c:	d1f22800 	mvnsle	r2, r0, lsl #16
d0016720:	0f04f1b8 	svceq	0x0004f1b8
d0016724:	b146d112 	cmplt	r6, r2, lsl r1
d0016728:	e7c74645 	strb	r4, [r7, r5, asr #12]
d001672c:	0f04f1b8 	svceq	0x0004f1b8
d0016730:	2e00d109 	mvfcss	f5, #1.0
d0016734:	2f03d1f8 	svccs	0x0003d1f8
d0016738:	6da3d007 	stcvs	0, cr13, [r3, #28]!
d001673c:	d1bd2b00 			; <UNDEFINED> instruction: 0xd1bd2b00
d0016740:	447b4b52 	ldrbtmi	r4, [fp], #-2898	; 0xfffff4ae
d0016744:	2f03e782 	svccs	0x0003e782
d0016748:	b948d100 	stmdblt	r8, {r8, ip, lr, pc}^
d001674c:	0f03f1b8 	svceq	0x0003f1b8
d0016750:	2e00d1f3 	mcrcs	1, 0, sp, cr0, cr3, {7}
d0016754:	9a02d0f1 	bls	0xd00cab20
d0016758:	bf182f03 	svclt	0x00182f03
d001675c:	9202461a 	andls	r4, r2, #27262976	; 0x1a00000
d0016760:	2392f504 	orrscs	pc, r2, #4, 10	; 0x1000000
d0016764:	25039a02 	strcs	r9, [r3, #-2562]	; 0xfffff5fe
d0016768:	2248f8c3 	subcs	pc, r8, #12779520	; 0xc30000
d001676c:	9b03e7a6 	blls	0xd011060c
d0016770:	d1192b01 	tstle	r9, r1, lsl #22
d0016774:	2b041eeb 	blcs	0xd011e328
d0016778:	6da3d809 	stcvs	8, cr13, [r3, #36]!	; 0x24
d001677c:	4b44b93b 	blmi	0xd1144c70
d0016780:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0016784:	9b013916 	blls	0xd0064be4
d0016788:	ba18e9c4 	blt	0xd0650ea0
d001678c:	f50466a3 			; <UNDEFINED> instruction: 0xf50466a3
d0016790:	46282492 			; <UNDEFINED> instruction: 0x46282492
d0016794:	3244f8d4 	subcc	pc, r4, #212, 16	; 0xd40000
d0016798:	f8c43b01 			; <UNDEFINED> instruction: 0xf8c43b01
d001679c:	b00d3244 	andlt	r3, sp, r4, asr #4
d00167a0:	8b06ecbd 	blhi	0xd01d1a9c
d00167a4:	8ff0e8bd 	svchi	0x00f0e8bd
d00167a8:	2b049b03 	blcs	0xd013d3bc
d00167ac:	1eebd1ef 	urdne<illegal precision>z	f5, #10.0
d00167b0:	d9ec2b01 	stmible	ip!, {r0, r8, r9, fp, sp}^
d00167b4:	f5a39b06 			; <UNDEFINED> instruction: 0xf5a39b06
d00167b8:	2b017381 	blcs	0xd00735c4
d00167bc:	9b05d802 	blls	0xd018c7cc
d00167c0:	d0e42b00 	rscle	r2, r4, r0, lsl #22
d00167c4:	2b006da3 	blcs	0xd0031e58
d00167c8:	4b32d1e1 	blmi	0xd0ccaf54
d00167cc:	e7d8447b 			; <UNDEFINED> instruction: 0xe7d8447b
d00167d0:	f43f2e04 			; <UNDEFINED> instruction: 0xf43f2e04
d00167d4:	2e03ae5e 	mcrcs	14, 0, sl, cr3, cr14, {2}
d00167d8:	ae5bf47f 	mrcge	4, 2, APSR_nzcv, cr11, cr15, {3}
d00167dc:	f47f2d00 			; <UNDEFINED> instruction: 0xf47f2d00
d00167e0:	2b00ae58 	blcs	0xd0042148
d00167e4:	ae46f47f 	mcrge	4, 2, pc, cr6, cr15, {3}	; <UNPREDICTABLE>
d00167e8:	2e04e653 	mcrcs	6, 0, lr, cr4, cr3, {2}
d00167ec:	e7f5d1f3 	udf	#23827	; 0x5d13
d00167f0:	d1222f2b 			; <UNDEFINED> instruction: 0xd1222f2b
d00167f4:	f43f2e04 			; <UNDEFINED> instruction: 0xf43f2e04
d00167f8:	2e03ae08 	cdpcs	14, 0, cr10, cr3, cr8, {0}
d00167fc:	4620d011 			; <UNDEFINED> instruction: 0x4620d011
d0016800:	f7fe2180 			; <UNDEFINED> instruction: 0xf7fe2180
d0016804:	f641f987 			; <UNDEFINED> instruction: 0xf641f987
d0016808:	f6412308 			; <UNDEFINED> instruction: 0xf6412308
d001680c:	46200108 	strtmi	r0, [r0], -r8, lsl #2
d0016810:	bf182f2b 	svclt	0x00182f2b
d0016814:	f7fe4619 			; <UNDEFINED> instruction: 0xf7fe4619
d0016818:	e53ef97d 	ldr	pc, [lr, #-2429]!	; 0xfffff683
d001681c:	f47f2f2d 			; <UNDEFINED> instruction: 0xf47f2f2d
d0016820:	6da3ae0d 	stcvs	14, cr10, [r3, #52]!	; 0x34
d0016824:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0016828:	9b09ad38 	blls	0xd0281d10
d001682c:	3916e9c4 	ldmdbcc	r6, {r2, r6, r7, r8, fp, sp, lr, pc}
d0016830:	e9c49b01 	stmib	r4, {r0, r8, r9, fp, ip, pc}^
d0016834:	66a3ba18 	ssatvs	fp, #4, r8, lsl #20
d0016838:	2f2de52f 	svccs	0x002de52f
d001683c:	adfef47f 	cfldrdge	mvd15, [lr, #508]!	; 0x1fc
d0016840:	d1da2e04 	bicsle	r2, sl, r4, lsl #28
d0016844:	f6414620 			; <UNDEFINED> instruction: 0xf6414620
d0016848:	f7fe2108 			; <UNDEFINED> instruction: 0xf7fe2108
d001684c:	f44ff963 	vst2.16	{d31,d33}, [pc :128], r3
d0016850:	46205184 	strtmi	r5, [r0], -r4, lsl #3
d0016854:	f95ef7fe 			; <UNDEFINED> instruction: 0xf95ef7fe
d0016858:	bf00e5a1 	svclt	0x0000e5a1
d001685c:	fffffdae 			; <UNDEFINED> instruction: 0xfffffdae
d0016860:	fffffe28 			; <UNDEFINED> instruction: 0xfffffe28
d0016864:	fffffe05 			; <UNDEFINED> instruction: 0xfffffe05
d0016868:	fffffd84 			; <UNDEFINED> instruction: 0xfffffd84
d001686c:	fffffdfa 			; <UNDEFINED> instruction: 0xfffffdfa
d0016870:	fffffeac 			; <UNDEFINED> instruction: 0xfffffeac
d0016874:	fffffcae 			; <UNDEFINED> instruction: 0xfffffcae
d0016878:	fffffb5a 			; <UNDEFINED> instruction: 0xfffffb5a
d001687c:	fffffaef 			; <UNDEFINED> instruction: 0xfffffaef
d0016880:	ffffeca2 			; <UNDEFINED> instruction: 0xffffeca2
d0016884:	ffffec7c 			; <UNDEFINED> instruction: 0xffffec7c
d0016888:	fffffa73 			; <UNDEFINED> instruction: 0xfffffa73
d001688c:	fffffa53 			; <UNDEFINED> instruction: 0xfffffa53
d0016890:	fffffa66 			; <UNDEFINED> instruction: 0xfffffa66
d0016894:	fffffa43 			; <UNDEFINED> instruction: 0xfffffa43

Disassembly of section .text.int_pointer_element:

d00168dc <.text.int_pointer_element>:
d00168dc:	4615b5f8 			; <UNDEFINED> instruction: 0x4615b5f8
d00168e0:	460f4a57 			; <UNDEFINED> instruction: 0x460f4a57
d00168e4:	447a215b 	ldrbtmi	r2, [sl], #-347	; 0xfffffea5
d00168e8:	f7fc4604 			; <UNDEFINED> instruction: 0xf7fc4604
d00168ec:	b910fb1b 	ldmdblt	r0, {r0, r1, r3, r4, r8, r9, fp, ip, sp, lr, pc}
d00168f0:	46282500 	strtmi	r2, [r8], -r0, lsl #10
d00168f4:	f24bbdf8 	vmla.f32	<illegal reg q13.5>, <illegal reg q13.5>, q12
d00168f8:	46204103 	strtmi	r4, [r0], -r3, lsl #2
d00168fc:	f90af7fe 			; <UNDEFINED> instruction: 0xf90af7fe
d0016900:	46202201 	strtmi	r2, [r0], -r1, lsl #4
d0016904:	f7ff4611 			; <UNDEFINED> instruction: 0xf7ff4611
d0016908:	4a4efc97 	bmi	0xd13d5b6c
d001690c:	4620215d 			; <UNDEFINED> instruction: 0x4620215d
d0016910:	f7fc447a 			; <UNDEFINED> instruction: 0xf7fc447a
d0016914:	2800fb07 	stmdacs	r0, {r0, r1, r2, r8, r9, fp, ip, sp, lr, pc}
d0016918:	f64bd0ea 			; <UNDEFINED> instruction: 0xf64bd0ea
d001691c:	46204106 	strtmi	r4, [r0], -r6, lsl #2
d0016920:	f8f8f7fe 			; <UNDEFINED> instruction: 0xf8f8f7fe
d0016924:	46202180 	strtmi	r2, [r0], -r0, lsl #3
d0016928:	f8f4f7fe 			; <UNDEFINED> instruction: 0xf8f4f7fe
d001692c:	0108f641 	tsteq	r8, r1, asr #12	; <UNPREDICTABLE>
d0016930:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0016934:	2d00f8ef 	stccs	8, cr15, [r0, #-956]	; 0xfffffc44
d0016938:	6ae6d142 	bvs	0xcf9cae48
d001693c:	d0412e3d 	suble	r2, r1, sp, lsr lr
d0016940:	7192f46f 	orrsvc	pc, r2, pc, ror #8
d0016944:	2b011873 	blcs	0xd005cb18
d0016948:	f46fd93c 	vld2.8	{d29,d31}, [pc :256], ip
d001694c:	18b37294 	ldmne	r3!, {r2, r4, r7, r9, ip, sp, lr}
d0016950:	d9372b04 	ldmdble	r7!, {r2, r8, r9, fp, sp}
d0016954:	41d0f44f 	bicsmi	pc, r0, pc, asr #8
d0016958:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d001695c:	e7c8f8db 			; <UNDEFINED> instruction: 0xe7c8f8db
d0016960:	0108f641 	tsteq	r8, r1, asr #12	; <UNPREDICTABLE>
d0016964:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0016968:	f64bf8d5 			; <UNDEFINED> instruction: 0xf64bf8d5
d001696c:	46204106 	strtmi	r4, [r0], -r6, lsl #2
d0016970:	f8d0f7fe 			; <UNDEFINED> instruction: 0xf8d0f7fe
d0016974:	0108f246 	tsteq	r8, r6, asr #4	; <UNPREDICTABLE>
d0016978:	25024620 	strcs	r4, [r2, #-1568]	; 0xfffff9e0
d001697c:	f8caf7fe 			; <UNDEFINED> instruction: 0xf8caf7fe
d0016980:	f641e7b7 			; <UNDEFINED> instruction: 0xf641e7b7
d0016984:	e7ed2108 	strb	r2, [sp, r8, lsl #2]!
d0016988:	0108f244 	tsteq	r8, r4, asr #4	; <UNPREDICTABLE>
d001698c:	f244e7ea 	vabd.s8	q15, q10, q13
d0016990:	e7e73108 	strb	r3, [r7, r8, lsl #2]!
d0016994:	0148f244 	cmpeq	r8, r4, asr #4	; <UNPREDICTABLE>
d0016998:	f244e7e4 	vabd.s8	q15, q10, q10
d001699c:	46206102 	strtmi	r6, [r0], -r2, lsl #2
d00169a0:	f8b8f7fe 			; <UNDEFINED> instruction: 0xf8b8f7fe
d00169a4:	6108f244 	tstvs	r8, r4, asr #4	; <UNPREDICTABLE>
d00169a8:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d00169ac:	f244f8b3 	vtst.8	d31, d20, d19
d00169b0:	f2440190 	vand	d16, d20, d0
d00169b4:	f5b61310 			; <UNDEFINED> instruction: 0xf5b61310
d00169b8:	bf187f96 	svclt	0x00187f96
d00169bc:	e7d14619 	bfi	r4, r9, #12, #6
d00169c0:	e7962504 	ldr	r2, [r6, r4, lsl #10]
d00169c4:	d0c52f00 	sbcle	r2, r5, r0, lsl #30
d00169c8:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d00169cc:	f24bfa7d 	vpmin.s8	<illegal reg q15.5>, <illegal reg q5.5>, <illegal reg q14.5>
d00169d0:	46204103 	strtmi	r4, [r0], -r3, lsl #2
d00169d4:	f89ef7fe 			; <UNDEFINED> instruction: 0xf89ef7fe
d00169d8:	d0092e3d 	andle	r2, r9, sp, lsr lr
d00169dc:	41d0f44f 	bicsmi	pc, r0, pc, asr #8
d00169e0:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d00169e4:	f24bf897 	vtst.8	d31, d27, d7
d00169e8:	46204103 	strtmi	r4, [r0], -r3, lsl #2
d00169ec:	f892f7fe 			; <UNDEFINED> instruction: 0xf892f7fe
d00169f0:	46202201 	strtmi	r2, [r0], -r1, lsl #4
d00169f4:	f7ff4611 			; <UNDEFINED> instruction: 0xf7ff4611
d00169f8:	2e3dfc1f 	mrccs	12, 1, APSR_nzcv, cr13, cr15, {0}
d00169fc:	f64bd0b5 			; <UNDEFINED> instruction: 0xf64bd0b5
d0016a00:	46204106 	strtmi	r4, [r0], -r6, lsl #2
d0016a04:	f886f7fe 			; <UNDEFINED> instruction: 0xf886f7fe
d0016a08:	7392f46f 	orrsvc	pc, r2, #1862270976	; 0x6f000000
d0016a0c:	2b0818f3 	blcs	0xd021cde0
d0016a10:	a202d8ab 	andge	sp, r2, #11206656	; 0xab0000
d0016a14:	3023f852 	eorcc	pc, r3, r2, asr r8	; <UNPREDICTABLE>
d0016a18:	4710441a 			; <UNDEFINED> instruction: 0x4710441a
d0016a1c:	ffffff45 			; <UNDEFINED> instruction: 0xffffff45
d0016a20:	ffffff67 			; <UNDEFINED> instruction: 0xffffff67
d0016a24:	ffffff4f 			; <UNDEFINED> instruction: 0xffffff4f
d0016a28:	ffffff4f 			; <UNDEFINED> instruction: 0xffffff4f
d0016a2c:	ffffff6d 			; <UNDEFINED> instruction: 0xffffff6d
d0016a30:	ffffff73 			; <UNDEFINED> instruction: 0xffffff73
d0016a34:	ffffff79 			; <UNDEFINED> instruction: 0xffffff79
d0016a38:	ffffff7f 			; <UNDEFINED> instruction: 0xffffff7f
d0016a3c:	ffffff7f 			; <UNDEFINED> instruction: 0xffffff7f
d0016a40:	ffffffae 			; <UNDEFINED> instruction: 0xffffffae
d0016a44:	ffffffa8 			; <UNDEFINED> instruction: 0xffffffa8

Disassembly of section .text.api_call:

d0016d24 <.text.api_call>:
d0016d24:	4ff0e92d 	svcmi	0x00f0e92d
d0016d28:	8b02ed2d 	blhi	0xd00d21e4
d0016d2c:	f891b089 			; <UNDEFINED> instruction: 0xf891b089
d0016d30:	46043046 	strmi	r3, [r4], -r6, asr #32
d0016d34:	0548f101 	strbeq	pc, [r8, #-257]	; 0xfffffeff	; <UNPREDICTABLE>
d0016d38:	23009303 	movwcs	r9, #771	; 0x303
d0016d3c:	93029101 	movwls	r9, #8449	; 0x2101
d0016d40:	34f0f8df 	ldrbtcc	pc, [r0], #2271	; 0x8df	; <UNPREDICTABLE>
d0016d44:	ee08447b 	mcr	4, 0, r4, cr8, cr11, {3}
d0016d48:	f8df3a10 			; <UNDEFINED> instruction: 0xf8df3a10
d0016d4c:	447b34ec 	ldrbtmi	r3, [fp], #-1260	; 0xfffffb14
d0016d50:	f8df9304 			; <UNDEFINED> instruction: 0xf8df9304
d0016d54:	447b34e8 	ldrbtmi	r3, [fp], #-1256	; 0xfffffb18
d0016d58:	9b029305 	blls	0xd00bb974
d0016d5c:	42939a03 	addsmi	r9, r3, #12288	; 0x3000
d0016d60:	6da3d202 	sfmvs	f5, 1, [r3, #8]!
d0016d64:	d03f2b00 	eorsle	r2, pc, r0, lsl #22
d0016d68:	24d4f8df 	ldrbcs	pc, [r4], #2271	; 0x8df	; <UNPREDICTABLE>
d0016d6c:	46202129 	strtmi	r2, [r0], -r9, lsr #2
d0016d70:	f7fc447a 			; <UNDEFINED> instruction: 0xf7fc447a
d0016d74:	2800f8d7 	stmdacs	r0, {r0, r1, r2, r4, r6, r7, fp, ip, sp, lr, pc}
d0016d78:	8256f000 	subshi	pc, r6, #0
d0016d7c:	46209903 	strtmi	r9, [r0], -r3, lsl #18
d0016d80:	ffadf7fd 			; <UNDEFINED> instruction: 0xffadf7fd
d0016d84:	0318f24d 	tsteq	r8, #-805306364	; 0xd0000004	; <UNPREDICTABLE>
d0016d88:	210c4605 	tstcs	ip, r5, lsl #12
d0016d8c:	462058e2 	strtmi	r5, [r0], -r2, ror #17
d0016d90:	fa7bf7fe 	blx	0xd1f14d90
d0016d94:	f64f9b01 			; <UNDEFINED> instruction: 0xf64f9b01
d0016d98:	f8df79ff 			; <UNDEFINED> instruction: 0xf8df79ff
d0016d9c:	f10384a8 			; <UNDEFINED> instruction: 0xf10384a8
d0016da0:	f1030640 			; <UNDEFINED> instruction: 0xf1030640
d0016da4:	f8360746 			; <UNDEFINED> instruction: 0xf8360746
d0016da8:	454b3b02 	strbmi	r3, [fp, #-2818]	; 0xfffff4fe
d0016dac:	821cf040 	andshi	pc, ip, #64	; 0x40
d0016db0:	71e0f244 	mvnvc	pc, r4, asr #4
d0016db4:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0016db8:	b12dfead 	msrlt	SP_fiq, sp
d0016dbc:	4130f445 	teqmi	r0, r5, asr #8	; <UNPREDICTABLE>
d0016dc0:	b2894620 	addlt	r4, r9, #32, 12	; 0x2000000
d0016dc4:	fea6f7fd 	mcr2	7, 5, pc, cr6, cr13, {7}	; <UNPREDICTABLE>
d0016dc8:	f8939b01 			; <UNDEFINED> instruction: 0xf8939b01
d0016dcc:	2b063047 	blcs	0xd01a2ef0
d0016dd0:	821bf040 	andshi	pc, fp, #64	; 0x40
d0016dd4:	21c0f24b 	biccs	pc, r0, fp, asr #4
d0016dd8:	b0094620 	andlt	r4, r9, r0, lsr #12
d0016ddc:	8b02ecbd 	blhi	0xd00d20d8
d0016de0:	4ff0e8bd 	svcmi	0x00f0e8bd
d0016de4:	be96f7fd 	mrclt	7, 4, APSR_nzcv, cr6, cr13, {7}
d0016de8:	b12b9b02 			; <UNDEFINED> instruction: 0xb12b9b02
d0016dec:	2a10ee18 	bcs	0xd0452654
d0016df0:	4620212c 	strtmi	r2, [r0], -ip, lsr #2
d0016df4:	f896f7fc 			; <UNDEFINED> instruction: 0xf896f7fc
d0016df8:	b000f895 	mullt	r0, r5, r8
d0016dfc:	33fff10b 	mvnscc	pc, #-1073741822	; 0xc0000002
d0016e00:	f2002b15 	vpadd.i8	d2, d0, d5
d0016e04:	e8df81c9 	ldm	pc, {r0, r3, r6, r7, r8, pc}^	; <UNPREDICTABLE>
d0016e08:	0023f013 	eoreq	pc, r3, r3, lsl r0	; <UNPREDICTABLE>
d0016e0c:	01c70016 	biceq	r0, r7, r6, lsl r0
d0016e10:	01c701c7 	biceq	r0, r7, r7, asr #3
d0016e14:	01c701c7 	biceq	r0, r7, r7, asr #3
d0016e18:	002e01c7 	eoreq	r0, lr, r7, asr #3
d0016e1c:	01c7002e 	biceq	r0, r7, lr, lsr #32
d0016e20:	00b0002e 	adcseq	r0, r0, lr, lsr #32
d0016e24:	015e0195 			; <UNDEFINED> instruction: 0x015e0195
d0016e28:	01c701c7 	biceq	r0, r7, r7, asr #3
d0016e2c:	00f000f0 	ldrshteq	r0, [r0], #0
d0016e30:	00f0002e 	rscseq	r0, r0, lr, lsr #32
d0016e34:	46200158 			; <UNDEFINED> instruction: 0x46200158
d0016e38:	f94cf7fe 			; <UNDEFINED> instruction: 0xf94cf7fe
d0016e3c:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d0016e40:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0016e44:	9b02fe67 	blls	0xd00d67e8
d0016e48:	33013501 	movwcc	r3, #5377	; 0x1501
d0016e4c:	e7849302 	str	r9, [r4, r2, lsl #6]
d0016e50:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0016e54:	2800fa63 	stmdacs	r0, {r0, r1, r5, r6, r9, fp, ip, sp, lr, pc}
d0016e58:	49fbd1f0 	ldmibmi	fp!, {r4, r5, r6, r7, r8, ip, lr, pc}^
d0016e5c:	46204479 			; <UNDEFINED> instruction: 0x46204479
d0016e60:	fa06f7f9 	blx	0xd01d4e4c
d0016e64:	4620e7ea 	strtmi	lr, [r0], -sl, ror #15
d0016e68:	fa58f7fe 	blx	0xd1654e68
d0016e6c:	d1e52800 	mvnle	r2, r0, lsl #16
d0016e70:	46202126 	strtmi	r2, [r0], -r6, lsr #2
d0016e74:	f848f7fc 			; <UNDEFINED> instruction: 0xf848f7fc
d0016e78:	f2406ae2 	vpmax.s8	q11, q8, q9
d0016e7c:	f8d41301 			; <UNDEFINED> instruction: 0xf8d41301
d0016e80:	f8d4a024 			; <UNDEFINED> instruction: 0xf8d4a024
d0016e84:	429a9028 	addsmi	r9, sl, #40	; 0x28
d0016e88:	8030f894 	mlashi	r0, r4, r8, pc	; <UNPREDICTABLE>
d0016e8c:	d0066b67 	andle	r6, r6, r7, ror #22
d0016e90:	2b006da3 	blcs	0xd0032524
d0016e94:	4bedd1d2 	blmi	0xcfb8b5e4
d0016e98:	65a3447b 	strvs	r4, [r3, #1147]!	; 0x47b
d0016e9c:	e9d4e02e 	ldmib	r4, {r1, r2, r3, r5, sp, lr, pc}^
d0016ea0:	46201206 	strtmi	r1, [r0], -r6, lsl #4
d0016ea4:	91069207 	tstls	r6, r7, lsl #4
d0016ea8:	fd1bf7f9 	ldc2	7, cr15, [fp, #-996]	; 0xfffffc1c
d0016eac:	dbef1e06 	blle	0xcfbde6cc
d0016eb0:	46209a07 	strtmi	r9, [r0], -r7, lsl #20
d0016eb4:	f7f99906 			; <UNDEFINED> instruction: 0xf7f99906
d0016eb8:	2800fc8b 	stmdacs	r0, {r0, r1, r3, r7, sl, fp, ip, sp, lr, pc}
d0016ebc:	f1bbdae8 			; <UNDEFINED> instruction: 0xf1bbdae8
d0016ec0:	d0210f0c 	eorle	r0, r1, ip, lsl #30
d0016ec4:	0f14f1bb 	svceq	0x0014f1bb
d0016ec8:	f1bbd027 			; <UNDEFINED> instruction: 0xf1bbd027
d0016ecc:	d12d0f09 			; <UNDEFINED> instruction: 0xd12d0f09
d0016ed0:	b37cf8df 	cmnlt	ip, #14614528	; 0xdf0000	; <UNPREDICTABLE>
d0016ed4:	0c01f04f 	stceq	0, cr15, [r1], {79}	; 0x4f
d0016ed8:	220549de 	andcs	r4, r5, #3637248	; 0x378000
d0016edc:	447944fb 	ldrbtmi	r4, [r9], #-1275	; 0xfffffb05
d0016ee0:	43732338 	cmnmi	r3, #56, 6	; 0xe0000000
d0016ee4:	f50018e0 			; <UNDEFINED> instruction: 0xf50018e0
d0016ee8:	f890307f 			; <UNDEFINED> instruction: 0xf890307f
d0016eec:	45e6e24f 	strbmi	lr, [r6, #591]!	; 0x24f
d0016ef0:	6da3d025 	stcvs	0, cr13, [r3, #148]!	; 0x94
d0016ef4:	d1a12b00 			; <UNDEFINED> instruction: 0xd1a12b00
d0016ef8:	b058f8c4 	subslt	pc, r8, r4, asr #17
d0016efc:	a05cf8c4 	subsge	pc, ip, r4, asr #17
d0016f00:	e9c466a7 	stmib	r4, {r0, r1, r2, r5, r7, r9, sl, sp, lr}^
d0016f04:	e7999818 			; <UNDEFINED> instruction: 0xe7999818
d0016f08:	b34cf8df 	movtlt	pc, #51423	; 0xc8df	; <UNPREDICTABLE>
d0016f0c:	0c02f04f 	stceq	0, cr15, [r2], {79}	; 0x4f
d0016f10:	44fb49d2 	ldrbtmi	r4, [fp], #2514	; 0x9d2
d0016f14:	44794662 	ldrbtmi	r4, [r9], #-1634	; 0xfffff99e
d0016f18:	f8dfe7e2 			; <UNDEFINED> instruction: 0xf8dfe7e2
d0016f1c:	f04fb344 			; <UNDEFINED> instruction: 0xf04fb344
d0016f20:	49d00c01 	ldmibmi	r0, {r0, sl, fp}^
d0016f24:	44fb2203 	ldrbtmi	r2, [fp], #515	; 0x203
d0016f28:	e7d94479 			; <UNDEFINED> instruction: 0xe7d94479
d0016f2c:	b338f8df 	teqlt	r8, #14614528	; 0xdf0000	; <UNPREDICTABLE>
d0016f30:	0c01f04f 	stceq	0, cr15, [r1], {79}	; 0x4f
d0016f34:	44fb49cd 	ldrbtmi	r4, [fp], #2509	; 0x9cd
d0016f38:	44794662 	ldrbtmi	r4, [r9], #-1634	; 0xfffff99e
d0016f3c:	f890e7d0 			; <UNDEFINED> instruction: 0xf890e7d0
d0016f40:	4290024c 	addsmi	r0, r0, #76, 4	; 0xc0000004
d0016f44:	f503d1d5 			; <UNDEFINED> instruction: 0xf503d1d5
d0016f48:	f200307f 	vqadd.s8	<illegal reg q1.5>, q0, <illegal reg q15.5>
d0016f4c:	44202053 	strtmi	r2, [r0], #-83	; 0xffffffad
d0016f50:	fb7cf00a 	blx	0xd1f52f82
d0016f54:	d1cc2800 	bicle	r2, ip, r0, lsl #16
d0016f58:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0016f5c:	4632ffb5 			; <UNDEFINED> instruction: 0x4632ffb5
d0016f60:	46202102 	strtmi	r2, [r0], -r2, lsl #2
d0016f64:	fe3ef7fd 	mrc2	7, 1, pc, cr14, cr13, {7}
d0016f68:	4620e768 	strtmi	lr, [r0], -r8, ror #14
d0016f6c:	f9d6f7fe 			; <UNDEFINED> instruction: 0xf9d6f7fe
d0016f70:	f47f2800 			; <UNDEFINED> instruction: 0xf47f2800
d0016f74:	4abeaf63 	bmi	0xcefc2d08
d0016f78:	46202126 	strtmi	r2, [r0], -r6, lsr #2
d0016f7c:	f7fb447a 			; <UNDEFINED> instruction: 0xf7fb447a
d0016f80:	2800ffd1 	stmdacs	r0, {r0, r4, r6, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0016f84:	af5af43f 	svcge	0x005af43f
d0016f88:	f2406ae2 	vpmax.s8	q11, q8, q9
d0016f8c:	f8d41301 			; <UNDEFINED> instruction: 0xf8d41301
d0016f90:	429aa024 	addsmi	sl, sl, #36	; 0x24
d0016f94:	9028f8d4 	ldrdls	pc, [r8], -r4	; <UNPREDICTABLE>
d0016f98:	8030f894 	mlashi	r0, r4, r8, pc	; <UNPREDICTABLE>
d0016f9c:	d0066b67 	andle	r6, r6, r7, ror #22
d0016fa0:	2b006da3 	blcs	0xd0032634
d0016fa4:	af4af47f 	svcge	0x004af47f
d0016fa8:	447b4bb2 	ldrbtmi	r4, [fp], #-2994	; 0xfffff44e
d0016fac:	e9d4e775 	ldmib	r4, {r0, r2, r4, r5, r6, r8, r9, sl, sp, lr, pc}^
d0016fb0:	46201206 	strtmi	r1, [r0], -r6, lsl #4
d0016fb4:	91069207 	tstls	r6, r7, lsl #4
d0016fb8:	fc2af7f9 	stc2	7, cr15, [sl], #-996	; 0xfffffc1c
d0016fbc:	dbef1e06 	blle	0xcfbde7dc
d0016fc0:	46209a07 	strtmi	r9, [r0], -r7, lsl #20
d0016fc4:	f7f99906 			; <UNDEFINED> instruction: 0xf7f99906
d0016fc8:	2800fc03 	stmdacs	r0, {r0, r1, sl, fp, ip, sp, lr, pc}
d0016fcc:	233cdae8 	teqcs	ip, #232, 20	; 0xe8000
d0016fd0:	4306fb03 	movwmi	pc, #27395	; 0x6b03	; <UNPREDICTABLE>
d0016fd4:	335ff503 	cmpcc	pc, #12582912	; 0xc00000	; <UNPREDICTABLE>
d0016fd8:	33ecf893 	mvncc	pc, #9633792	; 0x930000
d0016fdc:	d1df2b05 	bicsle	r2, pc, r5, lsl #22
d0016fe0:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0016fe4:	4632ff71 	shsub16mi	pc, r2, r1	; <UNPREDICTABLE>
d0016fe8:	f1bbe051 			; <UNDEFINED> instruction: 0xf1bbe051
d0016fec:	d01e0f15 	andsle	r0, lr, r5, lsl pc
d0016ff0:	2b13782b 	blcs	0xd04f50a4
d0016ff4:	4ea0d122 	tanmisp	f5, f2
d0016ff8:	4632447e 			; <UNDEFINED> instruction: 0x4632447e
d0016ffc:	46202126 	strtmi	r2, [r0], -r6, lsr #2
d0017000:	ff90f7fb 			; <UNDEFINED> instruction: 0xff90f7fb
d0017004:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0017008:	6ae2af19 	bvs	0xcf8c2c74
d001700c:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d0017010:	a024f8d4 	ldrdge	pc, [r4], -r4	; <UNPREDICTABLE>
d0017014:	f8d4429a 			; <UNDEFINED> instruction: 0xf8d4429a
d0017018:	f8949028 			; <UNDEFINED> instruction: 0xf8949028
d001701c:	6b678030 	blvs	0xd19f70e4
d0017020:	6da3d014 	stcvs	0, cr13, [r3, #80]!	; 0x50
d0017024:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0017028:	65a6af09 	strvs	sl, [r6, #3849]!	; 0xf09
d001702c:	4620e766 	strtmi	lr, [r0], -r6, ror #14
d0017030:	f974f7fe 			; <UNDEFINED> instruction: 0xf974f7fe
d0017034:	f47f2800 			; <UNDEFINED> instruction: 0xf47f2800
d0017038:	e7d9af01 	ldrb	sl, [r9, r1, lsl #30]
d001703c:	d0022b12 	andle	r2, r2, r2, lsl fp
d0017040:	447e4e8e 	ldrbtmi	r4, [lr], #-3726	; 0xfffff172
d0017044:	4e8ee7d9 	mcrmi	7, 4, lr, cr14, cr9, {6}
d0017048:	e7d6447e 			; <UNDEFINED> instruction: 0xe7d6447e
d001704c:	1206e9d4 	andne	lr, r6, #212, 18	; 0x350000
d0017050:	92074620 	andls	r4, r7, #32, 12	; 0x2000000
d0017054:	f7f99106 			; <UNDEFINED> instruction: 0xf7f99106
d0017058:	f1b0fbdb 			; <UNDEFINED> instruction: 0xf1b0fbdb
d001705c:	dbe00b00 	blle	0xcf819c64
d0017060:	46209a07 	strtmi	r9, [r0], -r7, lsl #20
d0017064:	f7f99906 			; <UNDEFINED> instruction: 0xf7f99906
d0017068:	2800fbb3 	stmdacs	r0, {r0, r1, r4, r5, r7, r8, r9, fp, ip, sp, lr, pc}
d001706c:	782bdad9 	stmdavc	fp!, {r0, r3, r4, r6, r7, r9, fp, ip, lr, pc}
d0017070:	d1162b12 	tstle	r6, r2, lsl fp
d0017074:	fb03233c 	blx	0xd00dfd6e
d0017078:	f503430b 			; <UNDEFINED> instruction: 0xf503430b
d001707c:	f893335f 			; <UNDEFINED> instruction: 0xf893335f
d0017080:	2b0133ec 	blcs	0xd0064038
d0017084:	4620d8cd 	strtmi	sp, [r0], -sp, asr #17
d0017088:	ff1ef7fb 			; <UNDEFINED> instruction: 0xff1ef7fb
d001708c:	2101465a 	tstcs	r1, sl, asr r6
d0017090:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0017094:	f244fda7 	vadd.f32	d31, d20, d23
d0017098:	46206108 	strtmi	r6, [r0], -r8, lsl #2
d001709c:	fd3af7fd 	ldc2	7, cr15, [sl, #-1012]!	; 0xfffffc0c
d00170a0:	2b13e6cc 	blcs	0xd0510bd8
d00170a4:	233cd1ef 	teqcs	ip, #-1073741765	; 0xc000003b
d00170a8:	430bfb03 	movwmi	pc, #47875	; 0xbb03	; <UNPREDICTABLE>
d00170ac:	335ff503 	cmpcc	pc, #12582912	; 0xc00000	; <UNPREDICTABLE>
d00170b0:	33ecf893 	mvncc	pc, #9633792	; 0x930000
d00170b4:	d1b42b0f 			; <UNDEFINED> instruction: 0xd1b42b0f
d00170b8:	2202e7e5 	andcs	lr, r2, #60030976	; 0x3940000
d00170bc:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d00170c0:	f8baf7ff 			; <UNDEFINED> instruction: 0xf8baf7ff
d00170c4:	4620e6ba 			; <UNDEFINED> instruction: 0x4620e6ba
d00170c8:	f928f7fe 			; <UNDEFINED> instruction: 0xf928f7fe
d00170cc:	496db110 	stmdbmi	sp!, {r4, r8, ip, sp, pc}^
d00170d0:	e6c44479 	uxtab16	r4, r4, r9, ror #8
d00170d4:	f2406ae2 	vpmax.s8	q11, q8, q9
d00170d8:	f8d41301 			; <UNDEFINED> instruction: 0xf8d41301
d00170dc:	429aa024 	addsmi	sl, sl, #36	; 0x24
d00170e0:	9028f8d4 	ldrdls	pc, [r8], -r4	; <UNPREDICTABLE>
d00170e4:	8030f894 	mlashi	r0, r4, r8, pc	; <UNPREDICTABLE>
d00170e8:	d0056b67 	andle	r6, r5, r7, ror #22
d00170ec:	2b006da3 	blcs	0xd0032780
d00170f0:	aea4f47f 	mcrge	4, 5, pc, cr4, cr15, {3}	; <UNPREDICTABLE>
d00170f4:	e6d09b05 	ldrb	r9, [r0], r5, lsl #22
d00170f8:	1206e9d4 	andne	lr, r6, #212, 18	; 0x350000
d00170fc:	92074620 	andls	r4, r7, #32, 12	; 0x2000000
d0017100:	f7f99106 			; <UNDEFINED> instruction: 0xf7f99106
d0017104:	1e06fb85 	vmlane.f64	d15, d22, d5
d0017108:	9a07dbf0 	bls	0xd020e0d0
d001710c:	99064620 	stmdbls	r6, {r5, r9, sl, lr}
d0017110:	fb5ef7f9 	blx	0xd17d50fe
d0017114:	dae92800 	ble	0xcfa6111c
d0017118:	fb03233c 	blx	0xd00dfe12
d001711c:	f5034306 			; <UNDEFINED> instruction: 0xf5034306
d0017120:	f893335f 			; <UNDEFINED> instruction: 0xf893335f
d0017124:	2a0823ec 	bcs	0xd02200dc
d0017128:	f8d3d1e0 			; <UNDEFINED> instruction: 0xf8d3d1e0
d001712c:	2bff33fc 	blcs	0xcffe4124
d0017130:	e755d9dc 	smmls	r5, ip, r9, sp
d0017134:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0017138:	2800f8f1 	stmdacs	r0, {r0, r4, r5, r6, r7, fp, ip, sp, lr, pc}
d001713c:	ae7ef47f 	mrcge	4, 3, APSR_nzcv, cr14, cr15, {3}
d0017140:	f2406ae2 	vpmax.s8	q11, q8, q9
d0017144:	f8d41301 			; <UNDEFINED> instruction: 0xf8d41301
d0017148:	429aa024 	addsmi	sl, sl, #36	; 0x24
d001714c:	9028f8d4 	ldrdls	pc, [r8], -r4	; <UNPREDICTABLE>
d0017150:	8030f894 	mlashi	r0, r4, r8, pc	; <UNPREDICTABLE>
d0017154:	d0056b67 	andle	r6, r5, r7, ror #22
d0017158:	2b006da3 	blcs	0xd00327ec
d001715c:	ae6ef47f 	mcrge	4, 3, pc, cr14, cr15, {3}	; <UNPREDICTABLE>
d0017160:	e69a9b04 	ldr	r9, [sl], r4, lsl #22
d0017164:	1206e9d4 	andne	lr, r6, #212, 18	; 0x350000
d0017168:	92074620 	andls	r4, r7, #32, 12	; 0x2000000
d001716c:	f7f99106 			; <UNDEFINED> instruction: 0xf7f99106
d0017170:	1e06fb4f 	vmlsne.f64	d15, d6, d15
d0017174:	9a07dbf0 	bls	0xd020e13c
d0017178:	99064620 	stmdbls	r6, {r5, r9, sl, lr}
d001717c:	fb28f7f9 	blx	0xd0a5516a
d0017180:	dae92800 	ble	0xcfa61188
d0017184:	fb03233c 	blx	0xd00dfe7e
d0017188:	f5034306 			; <UNDEFINED> instruction: 0xf5034306
d001718c:	f893335f 			; <UNDEFINED> instruction: 0xf893335f
d0017190:	2b0733ec 	blcs	0xd01e4148
d0017194:	e723d1e0 	str	sp, [r3, -r0, ror #3]!
d0017198:	46202201 	strtmi	r2, [r0], -r1, lsl #4
d001719c:	f7ff4611 			; <UNDEFINED> instruction: 0xf7ff4611
d00171a0:	782bf84b 	stmdavc	fp!, {r0, r1, r3, r6, fp, ip, sp, lr, pc}
d00171a4:	2b053b03 	blcs	0xd0165db8
d00171a8:	ae48f63f 	mcrge	6, 2, pc, cr8, cr15, {1}	; <UNPREDICTABLE>
d00171ac:	f852a202 			; <UNDEFINED> instruction: 0xf852a202
d00171b0:	441a3023 	ldrmi	r3, [sl], #-35	; 0xffffffdd
d00171b4:	bf004710 	svclt	0x00004710
d00171b8:	00000019 	andeq	r0, r0, r9, lsl r0
d00171bc:	0000001f 	andeq	r0, r0, pc, lsl r0
d00171c0:	fffffc85 			; <UNDEFINED> instruction: 0xfffffc85
d00171c4:	0000002b 	andeq	r0, r0, fp, lsr #32
d00171c8:	fffffc85 			; <UNDEFINED> instruction: 0xfffffc85
d00171cc:	00000025 	andeq	r0, r0, r5, lsr #32
d00171d0:	4132f44f 	teqmi	r2, pc, asr #8	; <UNPREDICTABLE>
d00171d4:	f24be761 	vabd.s8	q15, <illegal reg q5.5>, <illegal reg q8.5>
d00171d8:	e75e2180 	ldrb	r2, [lr, -r0, lsl #3]
d00171dc:	2140f24b 	cmpcs	r0, fp, asr #4	; <UNPREDICTABLE>
d00171e0:	f24be75b 	vaba.s8	q15, <illegal reg q5.5>, <illegal reg q5.5>
d00171e4:	e75821c0 	ldrb	r2, [r8, -r0, asr #3]
d00171e8:	01dcf64f 	bicseq	pc, ip, pc, asr #12
d00171ec:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d00171f0:	f836fc91 			; <UNDEFINED> instruction: 0xf836fc91
d00171f4:	46201c02 	strtmi	r1, [r0], -r2, lsl #24
d00171f8:	0108ea41 	tsteq	r8, r1, asr #20
d00171fc:	f7fdb289 			; <UNDEFINED> instruction: 0xf7fdb289
d0017200:	42befc89 	adcsmi	pc, lr, #35072	; 0x8900
d0017204:	adcff47f 	cfstrdge	mvd15, [pc, #508]	; 0xd0017408
d0017208:	2b08e5d2 	blcs	0xd0250958
d001720c:	f24bd102 	vrhadd.s8	d29, d11, d2
d0017210:	e5e12140 	strb	r2, [r1, #320]!	; 0x140
d0017214:	d1022b10 	tstle	r2, r0, lsl fp
d0017218:	2180f24b 	orrcs	pc, r0, fp, asr #4
d001721c:	2b11e5dc 	blcs	0xd0490994
d0017220:	f44fd102 	vst4.8	{d29,d31,d33,d35}, [pc], r2
d0017224:	e5d74132 	ldrb	r4, [r7, #306]	; 0x132
d0017228:	ecbdb009 	ldc	0, cr11, [sp], #36	; 0x24
d001722c:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d0017230:	bf008ff0 	svclt	0x00008ff0
d0017234:	fffffe86 			; <UNDEFINED> instruction: 0xfffffe86
d0017238:	ffffff79 			; <UNDEFINED> instruction: 0xffffff79
d001723c:	ffffff41 			; <UNDEFINED> instruction: 0xffffff41
d0017240:	ffffff86 			; <UNDEFINED> instruction: 0xffffff86
d0017244:	ffffc000 			; <UNDEFINED> instruction: 0xffffc000
d0017248:	fffffd91 			; <UNDEFINED> instruction: 0xfffffd91
d001724c:	fffffd79 			; <UNDEFINED> instruction: 0xfffffd79
d0017250:	fffffc07 			; <UNDEFINED> instruction: 0xfffffc07
d0017254:	00008163 	andeq	r8, r0, r3, ror #2
d0017258:	fffffb55 			; <UNDEFINED> instruction: 0xfffffb55
d001725c:	000083b0 			; <UNDEFINED> instruction: 0x000083b0
d0017260:	fffffb87 			; <UNDEFINED> instruction: 0xfffffb87
d0017264:	0000811e 	andeq	r8, r0, lr, lsl r1
d0017268:	fffffb0e 			; <UNDEFINED> instruction: 0xfffffb0e
d001726c:	0000838b 	andeq	r8, r0, fp, lsl #7
d0017270:	fffffcc3 			; <UNDEFINED> instruction: 0xfffffcc3
d0017274:	fffffc95 			; <UNDEFINED> instruction: 0xfffffc95
d0017278:	fffffb33 			; <UNDEFINED> instruction: 0xfffffb33
d001727c:	fffffb4f 			; <UNDEFINED> instruction: 0xfffffb4f
d0017280:	fffffb12 			; <UNDEFINED> instruction: 0xfffffb12
d0017284:	fffffba8 			; <UNDEFINED> instruction: 0xfffffba8

Disassembly of section .text.indirect_call:

d00172ec <.text.indirect_call>:
d00172ec:	fb032330 	blx	0xd00dffb6
d00172f0:	e92d0301 	push	{r0, r8, r9}
d00172f4:	f50341f0 			; <UNDEFINED> instruction: 0xf50341f0
d00172f8:	f8df2390 			; <UNDEFINED> instruction: 0xf8df2390
d00172fc:	460480a4 	strmi	r8, [r4], -r4, lsr #1
d0017300:	f893460d 			; <UNDEFINED> instruction: 0xf893460d
d0017304:	2600765b 			; <UNDEFINED> instruction: 0x2600765b
d0017308:	42be44f8 	adcsmi	r4, lr, #248, 8	; 0xf8000000
d001730c:	6da3d201 	sfmvs	f5, 1, [r3, #4]!
d0017310:	4639b37b 			; <UNDEFINED> instruction: 0x4639b37b
d0017314:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0017318:	4a22fce2 	bmi	0xd08d66a8
d001731c:	21294606 			; <UNDEFINED> instruction: 0x21294606
d0017320:	4620447a 			; <UNDEFINED> instruction: 0x4620447a
d0017324:	fdfef7fb 	ldc2l	7, cr15, [lr, #1004]!	; 0x3ec
d0017328:	f64fb300 			; <UNDEFINED> instruction: 0xf64fb300
d001732c:	462001d7 			; <UNDEFINED> instruction: 0x462001d7
d0017330:	fbf0f7fd 	blx	0xcfc5532e
d0017334:	46204919 			; <UNDEFINED> instruction: 0x46204919
d0017338:	0185ea41 	orreq	lr, r5, r1, asr #20
d001733c:	f7fdb289 			; <UNDEFINED> instruction: 0xf7fdb289
d0017340:	f244fbe9 	vqdmulh.s<illegal width 8>	<illegal reg q15.5>, q10, <illegal reg q12.5>
d0017344:	462071e0 	strtmi	r7, [r0], -r0, ror #3
d0017348:	fbe4f7fd 	blx	0xcf955346
d001734c:	f446b12e 	vst4.8	{d27,d29,d31,d33}, [r6 :128], lr
d0017350:	46204130 			; <UNDEFINED> instruction: 0x46204130
d0017354:	f7fdb289 			; <UNDEFINED> instruction: 0xf7fdb289
d0017358:	2030fbdd 	ldrsbtcs	pc, [r0], -sp	; <UNPREDICTABLE>
d001735c:	4405fb00 	strmi	pc, [r5], #-2816	; 0xfffff500
d0017360:	2490f504 	ldrcs	pc, [r0], #1284	; 0x504
d0017364:	365cf894 			; <UNDEFINED> instruction: 0x365cf894
d0017368:	d0142b01 	andsle	r2, r4, r1, lsl #22
d001736c:	e8bd2000 	ldmfd	sp!, {sp}
d0017370:	b12681f0 	strdlt	r8, [r6, -r0]!
d0017374:	212c4642 			; <UNDEFINED> instruction: 0x212c4642
d0017378:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d001737c:	2201fdd3 	andcs	pc, r1, #13504	; 0x34c0
d0017380:	36014620 	strcc	r4, [r1], -r0, lsr #12
d0017384:	f7fe4611 			; <UNDEFINED> instruction: 0xf7fe4611
d0017388:	f24bff57 	vrecps.f32	<illegal reg q15.5>, <illegal reg q5.5>, <illegal reg q3.5>
d001738c:	46204103 	strtmi	r4, [r0], -r3, lsl #2
d0017390:	fbc0f7fd 	blx	0xcf05538e
d0017394:	2002e7b9 			; <UNDEFINED> instruction: 0x2002e7b9
d0017398:	bf00e7e9 	svclt	0x0000e7e9
d001739c:	ffffc000 			; <UNDEFINED> instruction: 0xffffc000
d00173a0:	ffffff7c 			; <UNDEFINED> instruction: 0xffffff7c
d00173a4:	ffffff94 			; <UNDEFINED> instruction: 0xffffff94

Disassembly of section .text.struct_array_element:

d0017420 <.text.struct_array_element>:
d0017420:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d0017424:	4a264617 	bmi	0xd09a8c88
d0017428:	215b460d 	cmpcs	fp, sp, lsl #12
d001742c:	4604447a 			; <UNDEFINED> instruction: 0x4604447a
d0017430:	f7fb461e 			; <UNDEFINED> instruction: 0xf7fb461e
d0017434:	2800fd77 	stmdacs	r0, {r0, r1, r2, r4, r5, r6, r8, sl, fp, ip, sp, lr, pc}
d0017438:	f24bd03e 	vqadd.s8	d29, d11, d30
d001743c:	46204103 	strtmi	r4, [r0], -r3, lsl #2
d0017440:	fb68f7fd 	blx	0xd1a5543e
d0017444:	46202201 	strtmi	r2, [r0], -r1, lsl #4
d0017448:	f7fe4611 			; <UNDEFINED> instruction: 0xf7fe4611
d001744c:	4a1dfef5 	bmi	0xd0797028
d0017450:	4620215d 			; <UNDEFINED> instruction: 0x4620215d
d0017454:	f7fb447a 			; <UNDEFINED> instruction: 0xf7fb447a
d0017458:	b368fd65 	msrlt	SPSR_f, #6464	; 0x1940
d001745c:	4106f64b 	tstmi	r6, fp, asr #12	; <UNPREDICTABLE>
d0017460:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0017464:	f44ffb57 			; <UNDEFINED> instruction: 0xf44ffb57
d0017468:	2102701a 	tstcs	r2, sl, lsl r0
d001746c:	4005fb00 	andmi	pc, r5, r0, lsl #22
d0017470:	3068f500 	rsbcc	pc, r8, r0, lsl #10
d0017474:	46208d02 	strtmi	r8, [r0], -r2, lsl #26
d0017478:	f7fd0092 			; <UNDEFINED> instruction: 0xf7fd0092
d001747c:	f244ff06 	vmax.f32	d31, d4, d6
d0017480:	46203150 			; <UNDEFINED> instruction: 0x46203150
d0017484:	fb46f7fd 	blx	0xd11d5482
d0017488:	51c2f44f 	bicpl	pc, r2, pc, asr #8
d001748c:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0017490:	b98efb41 	stmiblt	lr, {r0, r6, r8, r9, fp, ip, sp, lr, pc}
d0017494:	4620212e 	strtmi	r2, [r0], -lr, lsr #2
d0017498:	fd36f7fb 	ldc2	7, cr15, [r6, #-1004]!	; 0xfffffc14
d001749c:	4633b138 			; <UNDEFINED> instruction: 0x4633b138
d00174a0:	4629463a 			; <UNDEFINED> instruction: 0x4629463a
d00174a4:	e8bd4620 	pop	{r5, r9, sl, lr}
d00174a8:	f00041f0 			; <UNDEFINED> instruction: 0xf00041f0
d00174ac:	4906bfa5 	stmdbmi	r6, {r0, r2, r5, r7, r8, r9, sl, fp, ip, sp, pc}
d00174b0:	44794620 	ldrbtmi	r4, [r9], #-1568	; 0xfffff9e0
d00174b4:	fedcf7f8 	mrc2	7, 6, pc, cr12, cr8, {7}
d00174b8:	e8bd2003 	pop	{r0, r1, sp}
d00174bc:	bf0081f0 	svclt	0x000081f0
d00174c0:	ffffff78 			; <UNDEFINED> instruction: 0xffffff78
d00174c4:	ffffff70 			; <UNDEFINED> instruction: 0xffffff70
d00174c8:	ffffff38 			; <UNDEFINED> instruction: 0xffffff38

Disassembly of section .text.record_value_address:

d00175d8 <.text.record_value_address>:
d00175d8:	e92d4a54 	push	{r2, r4, r6, r9, fp, lr}
d00175dc:	447a4ff0 	ldrbtmi	r4, [sl], #-4080	; 0xfffff010
d00175e0:	4689b087 	strmi	fp, [r9], r7, lsl #1
d00175e4:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d00175e8:	6a454604 	bvs	0xd1168e00
d00175ec:	f8906a86 			; <UNDEFINED> instruction: 0xf8906a86
d00175f0:	f8d07030 			; <UNDEFINED> instruction: 0xf8d07030
d00175f4:	e9d08034 	ldmib	r0, {r2, r4, r5, pc}^
d00175f8:	f7fbab06 			; <UNDEFINED> instruction: 0xf7fbab06
d00175fc:	b1f0fc93 			; <UNDEFINED> instruction: 0xb1f0fc93
d0017600:	46202128 	strtmi	r2, [r0], -r8, lsr #2
d0017604:	fc80f7fb 	stc2	7, cr15, [r0], {251}	; 0xfb
d0017608:	462bb1e0 	strtmi	fp, [fp], -r0, ror #3
d001760c:	4651465a 			; <UNDEFINED> instruction: 0x4651465a
d0017610:	e88d4620 	stm	sp, {r5, r9, sl, lr}
d0017614:	f00001c0 			; <UNDEFINED> instruction: 0xf00001c0
d0017618:	2806f959 	stmdacs	r6, {r0, r3, r4, r6, r8, fp, ip, sp, lr, pc}
d001761c:	f504d105 			; <UNDEFINED> instruction: 0xf504d105
d0017620:	f8d32392 			; <UNDEFINED> instruction: 0xf8d32392
d0017624:	454b3248 	strbmi	r3, [fp, #-584]	; 0xfffffdb8
d0017628:	6da3d009 	stcvs	0, cr13, [r3, #36]!	; 0x24
d001762c:	4b40b93b 	blmi	0xd1045b20
d0017630:	f8c4447b 			; <UNDEFINED> instruction: 0xf8c4447b
d0017634:	e9c48068 	stmib	r4, {r3, r5, r6, pc}^
d0017638:	e9c43516 	stmib	r4, {r1, r2, r4, r8, sl, ip, sp}^
d001763c:	b0076718 	andlt	r6, r7, r8, lsl r7
d0017640:	8ff0e8bd 	svchi	0x00f0e8bd
d0017644:	4651465a 			; <UNDEFINED> instruction: 0x4651465a
d0017648:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d001764c:	1e03f8c1 	cdpne	8, 0, cr15, cr3, cr1, {6}
d0017650:	465ada53 			; <UNDEFINED> instruction: 0x465ada53
d0017654:	46204651 			; <UNDEFINED> instruction: 0x46204651
d0017658:	f7f99305 			; <UNDEFINED> instruction: 0xf7f99305
d001765c:	1e02f8d9 	mcrne	8, 0, pc, cr2, cr9, {6}	; <UNPREDICTABLE>
d0017660:	da059b05 	ble	0xd017e27c
d0017664:	2b006da3 	blcs	0xd0032cf8
d0017668:	4b32d1e9 	blmi	0xd0ccbe14
d001766c:	e7e0447b 			; <UNDEFINED> instruction: 0xe7e0447b
d0017670:	fb01213c 	blx	0xd005fb6a
d0017674:	f5014102 			; <UNDEFINED> instruction: 0xf5014102
d0017678:	f891315f 			; <UNDEFINED> instruction: 0xf891315f
d001767c:	f891b3ec 			; <UNDEFINED> instruction: 0xf891b3ec
d0017680:	f1bba3ee 			; <UNDEFINED> instruction: 0xf1bba3ee
d0017684:	d1460f0d 	cmple	r6, sp, lsl #30
d0017688:	21014620 	tstcs	r1, r0, lsr #12
d001768c:	faaaf7fd 	blx	0xcead5688
d0017690:	6108f244 	tstvs	r8, r4, asr #4	; <UNPREDICTABLE>
d0017694:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0017698:	e005fa3d 	and	pc, r5, sp, lsr sl	; <UNPREDICTABLE>
d001769c:	dbf32b00 	blle	0xcfce22a4
d00176a0:	46204619 			; <UNDEFINED> instruction: 0x46204619
d00176a4:	f90ef7fe 			; <UNDEFINED> instruction: 0xf90ef7fe
d00176a8:	0b10f1ab 	bleq	0xd0453d5c
d00176ac:	0f01f1bb 	svceq	0x0001f1bb
d00176b0:	6ae3d80e 	bvs	0xcf90d6f0
d00176b4:	d0052b5b 	andle	r2, r5, fp, asr fp
d00176b8:	2b006da3 	blcs	0xd0032d4c
d00176bc:	4b1ed1bf 	blmi	0xd07cbdc0
d00176c0:	e7b6447b 			; <UNDEFINED> instruction: 0xe7b6447b
d00176c4:	22002301 	andcs	r2, r0, #67108864	; 0x4000000
d00176c8:	46204651 			; <UNDEFINED> instruction: 0x46204651
d00176cc:	fea8f7ff 	mcr2	7, 5, pc, cr8, cr15, {7}	; <UNPREDICTABLE>
d00176d0:	4620212e 	strtmi	r2, [r0], -lr, lsr #2
d00176d4:	fc18f7fb 	ldc2	7, cr15, [r8], {251}	; 0xfb
d00176d8:	464ab138 			; <UNDEFINED> instruction: 0x464ab138
d00176dc:	46204651 			; <UNDEFINED> instruction: 0x46204651
d00176e0:	e8bdb007 	pop	{r0, r1, r2, ip, sp, pc}
d00176e4:	f7fe4ff0 			; <UNDEFINED> instruction: 0xf7fe4ff0
d00176e8:	45d1b9cd 	ldrbmi	fp, [r1, #2509]	; 0x9cd
d00176ec:	6da3d0a7 	stcvs	0, cr13, [r3, #668]!	; 0x29c
d00176f0:	d1a42b00 			; <UNDEFINED> instruction: 0xd1a42b00
d00176f4:	447b4b11 	ldrbtmi	r4, [fp], #-2833	; 0xfffff4ef
d00176f8:	2230e79b 	eorscs	lr, r0, #40632320	; 0x26c0000
d00176fc:	4203fb02 	andmi	pc, r3, #2048	; 0x800
d0017700:	2290f502 	addscs	pc, r0, #8388608	; 0x800000
d0017704:	b659f892 			; <UNDEFINED> instruction: 0xb659f892
d0017708:	a65af892 			; <UNDEFINED> instruction: 0xa65af892
d001770c:	0f0df1bb 	svceq	0x000df1bb
d0017710:	f04fd0c6 			; <UNDEFINED> instruction: 0xf04fd0c6
d0017714:	f1ab32ff 			; <UNDEFINED> instruction: 0xf1ab32ff
d0017718:	2902010f 	stmdbcs	r2, {r0, r1, r2, r3, r8}
d001771c:	6da3d9be 			; <UNDEFINED> instruction: 0x6da3d9be
d0017720:	d18c2b00 	orrle	r2, ip, r0, lsl #22
d0017724:	447b4b06 	ldrbtmi	r4, [fp], #-2822	; 0xfffff4fa
d0017728:	bf00e783 	svclt	0x0000e783
d001772c:	fffffeea 			; <UNDEFINED> instruction: 0xfffffeea
d0017730:	fffffec7 			; <UNDEFINED> instruction: 0xfffffec7
d0017734:	fffffec6 			; <UNDEFINED> instruction: 0xfffffec6
d0017738:	fffffec2 			; <UNDEFINED> instruction: 0xfffffec2
d001773c:	fffffeb7 			; <UNDEFINED> instruction: 0xfffffeb7
d0017740:	fffffe2d 			; <UNDEFINED> instruction: 0xfffffe2d

Disassembly of section .text.call.isra.0:

d00178cc <.text.call.isra.0>:
d00178cc:	4ff0e92d 	svcmi	0x00f0e92d
d00178d0:	460eb087 	strmi	fp, [lr], -r7, lsl #1
d00178d4:	f8df4617 			; <UNDEFINED> instruction: 0xf8df4617
d00178d8:	9302248c 	movwls	r2, #9356	; 0x248c
d00178dc:	f89d4604 			; <UNDEFINED> instruction: 0xf89d4604
d00178e0:	447a3044 	ldrbtmi	r3, [sl], #-68	; 0xffffffbc
d00178e4:	46304639 			; <UNDEFINED> instruction: 0x46304639
d00178e8:	f7f99303 			; <UNDEFINED> instruction: 0xf7f99303
d00178ec:	b1b8f823 			; <UNDEFINED> instruction: 0xb1b8f823
d00178f0:	2474f8df 	ldrbtcs	pc, [r4], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d00178f4:	46304639 			; <UNDEFINED> instruction: 0x46304639
d00178f8:	f7f9447a 			; <UNDEFINED> instruction: 0xf7f9447a
d00178fc:	2800f81b 	stmdacs	r0, {r0, r1, r3, r4, fp, ip, sp, lr, pc}
d0017900:	f8dfd13f 			; <UNDEFINED> instruction: 0xf8dfd13f
d0017904:	46392468 	ldrtmi	r2, [r9], -r8, ror #8
d0017908:	447a4630 	ldrbtmi	r4, [sl], #-1584	; 0xfffff9d0
d001790c:	f812f7f9 			; <UNDEFINED> instruction: 0xf812f7f9
d0017910:	bbb04605 	bllt	0xcec2912c
d0017914:	21012202 	tstcs	r1, r2, lsl #4
d0017918:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d001791c:	e036fc8d 	eors	pc, r6, sp, lsl #25
d0017920:	244cf8df 	strbcs	pc, [ip], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d0017924:	46304639 			; <UNDEFINED> instruction: 0x46304639
d0017928:	f7f9447a 			; <UNDEFINED> instruction: 0xf7f9447a
d001792c:	2800f803 	stmdacs	r0, {r0, r1, fp, ip, sp, lr, pc}
d0017930:	f8dfd1de 			; <UNDEFINED> instruction: 0xf8dfd1de
d0017934:	46392440 	ldrtmi	r2, [r9], -r0, asr #8
d0017938:	447a4630 	ldrbtmi	r4, [sl], #-1584	; 0xfffff9d0
d001793c:	fffaf7f8 			; <UNDEFINED> instruction: 0xfffaf7f8
d0017940:	d1d52800 	bicsle	r2, r5, r0, lsl #16
d0017944:	2430f8df 	ldrtcs	pc, [r0], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d0017948:	46304639 			; <UNDEFINED> instruction: 0x46304639
d001794c:	f7f8447a 			; <UNDEFINED> instruction: 0xf7f8447a
d0017950:	4605fff1 			; <UNDEFINED> instruction: 0x4605fff1
d0017954:	d1cb2800 	bicle	r2, fp, r0, lsl #16
d0017958:	4631463a 			; <UNDEFINED> instruction: 0x4631463a
d001795c:	f7f84620 			; <UNDEFINED> instruction: 0xf7f84620
d0017960:	4680fffe 			; <UNDEFINED> instruction: 0x4680fffe
d0017964:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d0017968:	46018089 	strmi	r8, [r1], -r9, lsl #1
d001796c:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0017970:	f898f9d9 			; <UNDEFINED> instruction: 0xf898f9d9
d0017974:	2d075047 	stccs	0, cr5, [r7, #-284]	; 0xfffffee4
d0017978:	1f6bd010 	svcne	0x006bd010
d001797c:	415d425d 	cmpmi	sp, sp, asr r2
d0017980:	2201e00d 	andcs	lr, r1, #13
d0017984:	46202501 	strtmi	r2, [r0], -r1, lsl #10
d0017988:	f7fe4611 			; <UNDEFINED> instruction: 0xf7fe4611
d001798c:	4afbfc55 	bmi	0xcff16ae8
d0017990:	46202129 	strtmi	r2, [r0], -r9, lsr #2
d0017994:	f7fb447a 			; <UNDEFINED> instruction: 0xf7fb447a
d0017998:	b920fac5 	stmdblt	r0!, {r0, r2, r6, r7, r9, fp, ip, sp, lr, pc}
d001799c:	46282502 	strtmi	r2, [r8], -r2, lsl #10
d00179a0:	e8bdb007 	pop	{r0, r1, r2, ip, sp, pc}
d00179a4:	f5048ff0 			; <UNDEFINED> instruction: 0xf5048ff0
d00179a8:	f8992996 			; <UNDEFINED> instruction: 0xf8992996
d00179ac:	b1b112a2 			; <UNDEFINED> instruction: 0xb1b112a2
d00179b0:	82a0f8b9 	adchi	pc, r0, #12124160	; 0xb90000
d00179b4:	2b006da3 	blcs	0xd0033048
d00179b8:	4642d1f0 			; <UNDEFINED> instruction: 0x4642d1f0
d00179bc:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d00179c0:	f910f7fd 			; <UNDEFINED> instruction: 0xf910f7fd
d00179c4:	238ef504 	orrcs	pc, lr, #4, 10	; 0x1000000
d00179c8:	662cf8d3 			; <UNDEFINED> instruction: 0x662cf8d3
d00179cc:	6f00f5b6 	svcvs	0x0000f5b6
d00179d0:	49ebd141 	stmibmi	fp!, {r0, r6, r8, ip, lr, pc}^
d00179d4:	46204479 			; <UNDEFINED> instruction: 0x46204479
d00179d8:	fc4af7f8 	mcrr2	7, 15, pc, sl, cr8	; <UNPREDICTABLE>
d00179dc:	f504e7de 			; <UNDEFINED> instruction: 0xf504e7de
d00179e0:	f8d33367 			; <UNDEFINED> instruction: 0xf8d33367
d00179e4:	f1b881c4 			; <UNDEFINED> instruction: 0xf1b881c4
d00179e8:	d8060f7f 	stmdale	r6, {r0, r1, r2, r3, r4, r5, r6, r8, r9, sl, fp}
d00179ec:	3a7ff504 	bcc	0xd2014e04
d00179f0:	621cf8da 	andsvs	pc, ip, #14286848	; 0xda0000
d00179f4:	2f78f5b6 	svccs	0x0078f5b6
d00179f8:	49e2d907 	stmibmi	r2!, {r0, r1, r2, r8, fp, ip, lr, pc}^
d00179fc:	f04f4620 			; <UNDEFINED> instruction: 0xf04f4620
d0017a00:	44790800 	ldrbtmi	r0, [r9], #-2048	; 0xfffff800
d0017a04:	fc34f7f8 	ldc2	7, cr15, [r4], #-992	; 0xfffffc20
d0017a08:	f108e7d4 			; <UNDEFINED> instruction: 0xf108e7d4
d0017a0c:	36070201 	strcc	r0, [r7], -r1, lsl #4
d0017a10:	21c4f8c3 	biccs	pc, r4, r3, asr #17
d0017a14:	f894223c 			; <UNDEFINED> instruction: 0xf894223c
d0017a18:	f026b008 			; <UNDEFINED> instruction: 0xf026b008
d0017a1c:	fb020607 	blx	0xd0099242
d0017a20:	f5074708 			; <UNDEFINED> instruction: 0xf5074708
d0017a24:	f507375f 			; <UNDEFINED> instruction: 0xf507375f
d0017a28:	f0097071 			; <UNDEFINED> instruction: 0xf0097071
d0017a2c:	2307fdf1 	movwcs	pc, #32241	; 0x7df1	; <UNPREDICTABLE>
d0017a30:	63e8f8c7 	mvnvs	pc, #13041664	; 0xc70000
d0017a34:	33ecf887 	mvncc	pc, #8847360	; 0x870000
d0017a38:	4300f44f 	movwmi	pc, #1103	; 0x44f	; <UNPREDICTABLE>
d0017a3c:	b3edf887 	mvnlt	pc, #8847360	; 0x870000
d0017a40:	33fcf8c7 	mvnscc	pc, #13041664	; 0xc70000
d0017a44:	2301441e 	movwcs	r4, #5150	; 0x141e
d0017a48:	621cf8ca 	andsvs	pc, ip, #13238272	; 0xca0000
d0017a4c:	82a0f8a9 	adchi	pc, r0, #11075584	; 0xa90000
d0017a50:	32a2f889 	adccc	pc, r2, #8978432	; 0x890000
d0017a54:	1c72e7ae 	ldclne	7, cr14, [r2], #-696	; 0xfffffd48
d0017a58:	eb044620 	bl	0xd01292e0
d0017a5c:	f8c304c6 			; <UNDEFINED> instruction: 0xf8c304c6
d0017a60:	f7fd262c 			; <UNDEFINED> instruction: 0xf7fd262c
d0017a64:	f505f8fd 			; <UNDEFINED> instruction: 0xf505f8fd
d0017a68:	f504437f 			; <UNDEFINED> instruction: 0xf504437f
d0017a6c:	35022486 	strcc	r2, [r2, #-1158]	; 0xfffffb7a
d0017a70:	f8c433fd 			; <UNDEFINED> instruction: 0xf8c433fd
d0017a74:	f8a4062c 			; <UNDEFINED> instruction: 0xf8a4062c
d0017a78:	e7903630 			; <UNDEFINED> instruction: 0xe7903630
d0017a7c:	4631463a 			; <UNDEFINED> instruction: 0x4631463a
d0017a80:	f7f84620 			; <UNDEFINED> instruction: 0xf7f84620
d0017a84:	1e03ff2e 	cdpne	15, 0, cr15, cr3, cr14, {1}
d0017a88:	da0e9301 	ble	0xd03bc694
d0017a8c:	2b006da3 	blcs	0xd0033120
d0017a90:	4bbdd185 	blmi	0xcef8c0ac
d0017a94:	65a3447b 	strvs	r4, [r3, #1147]!	; 0x47b
d0017a98:	65e39b02 	strbvs	r9, [r3, #2818]!	; 0xb02
d0017a9c:	66239b10 			; <UNDEFINED> instruction: 0x66239b10
d0017aa0:	66639b03 	strbtvs	r9, [r3], -r3, lsl #22
d0017aa4:	66a39b12 	ssatvs	r9, #4, r2, lsl #22
d0017aa8:	463ae779 			; <UNDEFINED> instruction: 0x463ae779
d0017aac:	46204631 			; <UNDEFINED> instruction: 0x46204631
d0017ab0:	fe8ef7f8 	mcr2	7, 4, pc, cr14, cr8, {7}	; <UNPREDICTABLE>
d0017ab4:	dae92800 	ble	0xcfa61abc
d0017ab8:	4631463a 			; <UNDEFINED> instruction: 0x4631463a
d0017abc:	f7f84620 			; <UNDEFINED> instruction: 0xf7f84620
d0017ac0:	2800fea7 	stmdacs	r0, {r0, r1, r2, r5, r7, r9, sl, fp, ip, sp, lr, pc}
d0017ac4:	2338dae2 	teqcs	r8, #925696	; 0xe2000
d0017ac8:	fb039a01 	blx	0xd00fe2d6
d0017acc:	f5024202 			; <UNDEFINED> instruction: 0xf5024202
d0017ad0:	f892327f 			; <UNDEFINED> instruction: 0xf892327f
d0017ad4:	29041254 	stmdbcs	r4, {r2, r4, r6, r9, ip}
d0017ad8:	6da3d106 	stfvsd	f5, [r3, #24]!
d0017adc:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0017ae0:	4baaaf5e 	blmi	0xceac3860
d0017ae4:	e7d6447b 			; <UNDEFINED> instruction: 0xe7d6447b
d0017ae8:	224ff892 	subcs	pc, pc, #9568256	; 0x920000
d0017aec:	d1782a04 	cmnle	r8, r4, lsl #20
d0017af0:	fb039a01 	blx	0xd00fe2fe
d0017af4:	f44f4302 	vst2.8	{d20-d23}, [pc], r2
d0017af8:	f503721a 			; <UNDEFINED> instruction: 0xf503721a
d0017afc:	f893337f 			; <UNDEFINED> instruction: 0xf893337f
d0017b00:	fb023252 	blx	0xd00a4452
d0017b04:	f5034303 			; <UNDEFINED> instruction: 0xf5034303
d0017b08:	f8b33368 			; <UNDEFINED> instruction: 0xf8b33368
d0017b0c:	f1baa028 			; <UNDEFINED> instruction: 0xf1baa028
d0017b10:	d0070f00 	andle	r0, r7, r0, lsl #30
d0017b14:	2692f504 	ldrcs	pc, [r2], r4, lsl #10
d0017b18:	9238f8d6 	eorsls	pc, r8, #14024704	; 0xd60000
d0017b1c:	0340f1c9 	movteq	pc, #457	; 0x1c9	; <UNPREDICTABLE>
d0017b20:	d939459a 	ldmdble	r9!, {r1, r3, r4, r7, r8, sl, lr}
d0017b24:	f04f499a 			; <UNDEFINED> instruction: 0xf04f499a
d0017b28:	46200900 	strtmi	r0, [r0], -r0, lsl #18
d0017b2c:	f7f84479 			; <UNDEFINED> instruction: 0xf7f84479
d0017b30:	6da3fb9f 			; <UNDEFINED> instruction: 0x6da3fb9f
d0017b34:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0017b38:	4649af31 			; <UNDEFINED> instruction: 0x4649af31
d0017b3c:	f04f4620 			; <UNDEFINED> instruction: 0xf04f4620
d0017b40:	f7fd0801 			; <UNDEFINED> instruction: 0xf7fd0801
d0017b44:	f24bfebf 			; <UNDEFINED> instruction: 0xf24bfebf
d0017b48:	46204103 	strtmi	r4, [r0], -r3, lsl #2
d0017b4c:	ffe2f7fc 			; <UNDEFINED> instruction: 0xffe2f7fc
d0017b50:	26389b01 	ldrtcs	r9, [r8], -r1, lsl #22
d0017b54:	eb04435e 	bl	0xd01288d4
d0017b58:	f50a0a06 			; <UNDEFINED> instruction: 0xf50a0a06
d0017b5c:	f89a3a7f 			; <UNDEFINED> instruction: 0xf89a3a7f
d0017b60:	2b04324d 	blcs	0xd012449c
d0017b64:	f506d041 			; <UNDEFINED> instruction: 0xf506d041
d0017b68:	f8cd367f 			; <UNDEFINED> instruction: 0xf8cd367f
d0017b6c:	f8dfa010 			; <UNDEFINED> instruction: 0xf8dfa010
d0017b70:	2700a224 	strcs	sl, [r0, -r4, lsr #4]
d0017b74:	2653f206 	ldrbcs	pc, [r3], -r6, lsl #4	; <UNPREDICTABLE>
d0017b78:	442644fa 	strtmi	r4, [r6], #-1274	; 0xfffffb06
d0017b7c:	f8939b04 			; <UNDEFINED> instruction: 0xf8939b04
d0017b80:	428f124c 	addmi	r1, pc, #76, 4	; 0xc0000004
d0017b84:	6da3d202 	sfmvs	f5, 1, [r3, #8]!
d0017b88:	d0492b00 	suble	r2, r9, r0, lsl #22
d0017b8c:	46204441 	strtmi	r4, [r0], -r1, asr #8
d0017b90:	f8a5f7fd 			; <UNDEFINED> instruction: 0xf8a5f7fd
d0017b94:	e02c4606 	eor	r4, ip, r6, lsl #12
d0017b98:	f8d62300 			; <UNDEFINED> instruction: 0xf8d62300
d0017b9c:	21007238 	tstcs	r0, r8, lsr r2
d0017ba0:	23309304 	teqcs	r0, #4, 6	; 0x10000000
d0017ba4:	0801f107 	stmdaeq	r1, {r0, r1, r2, r8, ip, sp, lr, pc}
d0017ba8:	b240f896 	sublt	pc, r0, #9830400	; 0x960000
d0017bac:	4707fb03 	strmi	pc, [r7, -r3, lsl #22]
d0017bb0:	f8c6461a 			; <UNDEFINED> instruction: 0xf8c6461a
d0017bb4:	f5078238 			; <UNDEFINED> instruction: 0xf5078238
d0017bb8:	f5072790 			; <UNDEFINED> instruction: 0xf5072790
d0017bbc:	f00960c7 			; <UNDEFINED> instruction: 0xf00960c7
d0017bc0:	9b04fd27 	blls	0xd0157064
d0017bc4:	f887220b 			; <UNDEFINED> instruction: 0xf887220b
d0017bc8:	3301b658 	movwcc	fp, #5720	; 0x1658
d0017bcc:	2659f887 	ldrbcs	pc, [r9], -r7, lsl #17	; <UNPREDICTABLE>
d0017bd0:	d8e2459a 	stmiale	r2!, {r1, r3, r4, r7, r8, sl, lr}^
d0017bd4:	323cf8d6 	eorscc	pc, ip, #14024704	; 0xd60000
d0017bd8:	bf884598 	svclt	0x00884598
d0017bdc:	823cf8c6 	eorshi	pc, ip, #12976128	; 0xc60000
d0017be0:	f04fe7a7 			; <UNDEFINED> instruction: 0xf04fe7a7
d0017be4:	46c10800 	strbmi	r0, [r1], r0, lsl #16
d0017be8:	2600e7b2 			; <UNDEFINED> instruction: 0x2600e7b2
d0017bec:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0017bf0:	4a69fa71 	bmi	0xd1a965bc
d0017bf4:	46202129 	strtmi	r2, [r0], -r9, lsr #2
d0017bf8:	f7fb447a 			; <UNDEFINED> instruction: 0xf7fb447a
d0017bfc:	2800f993 	stmdacs	r0, {r0, r1, r4, r7, r8, fp, ip, sp, lr, pc}
d0017c00:	aecdf43f 	mcrge	4, 6, pc, cr13, cr15, {1}	; <UNPREDICTABLE>
d0017c04:	238ef504 	orrcs	pc, lr, #4, 10	; 0x1000000
d0017c08:	762cf8d3 			; <UNDEFINED> instruction: 0x762cf8d3
d0017c0c:	6f00f5b7 	svcvs	0x0000f5b7
d0017c10:	6da3d16a 	stfvsd	f5, [r3, #424]!	; 0x1a8
d0017c14:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0017c18:	4b60aec2 	blmi	0xd1843728
d0017c1c:	e73a447b 			; <UNDEFINED> instruction: 0xe73a447b
d0017c20:	4652b127 	ldrbmi	fp, [r2], -r7, lsr #2
d0017c24:	4620212c 	strtmi	r2, [r0], -ip, lsr #2
d0017c28:	f97cf7fb 			; <UNDEFINED> instruction: 0xf97cf7fb
d0017c2c:	bb01f816 	bllt	0xd0095c8c
d0017c30:	0f0df1bb 	svceq	0x000df1bb
d0017c34:	7931d10a 	ldmdbvc	r1!, {r1, r3, r8, ip, lr, pc}
d0017c38:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0017c3c:	f24bfccd 	sha1c.32	<illegal reg q15.5>, <illegal reg q13.5>, <illegal reg q6.5>
d0017c40:	46204103 	strtmi	r4, [r0], -r3, lsl #2
d0017c44:	f7fc3701 			; <UNDEFINED> instruction: 0xf7fc3701
d0017c48:	e797ff65 	ldr	pc, [r7, r5, ror #30]
d0017c4c:	0f0ef1bb 	svceq	0x000ef1bb
d0017c50:	7931d104 	ldmdbvc	r1!, {r2, r8, ip, lr, pc}
d0017c54:	f0004620 			; <UNDEFINED> instruction: 0xf0004620
d0017c58:	e7f0f915 			; <UNDEFINED> instruction: 0xe7f0f915
d0017c5c:	0f12f1bb 	svceq	0x0012f1bb
d0017c60:	7931d104 	ldmdbvc	r1!, {r2, r8, ip, lr, pc}
d0017c64:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0017c68:	e7e8f913 			; <UNDEFINED> instruction: 0xe7e8f913
d0017c6c:	0f13f1bb 	svceq	0x0013f1bb
d0017c70:	4620d103 	strtmi	sp, [r0], -r3, lsl #2
d0017c74:	fe6cf7fd 	mcr2	7, 3, pc, cr12, cr13, {7}	; <UNPREDICTABLE>
d0017c78:	f1bbe7e1 			; <UNDEFINED> instruction: 0xf1bbe7e1
d0017c7c:	d1050f0a 	tstle	r5, sl, lsl #30
d0017c80:	21012204 	tstcs	r1, r4, lsl #4
d0017c84:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0017c88:	e7d8fad7 			; <UNDEFINED> instruction: 0xe7d8fad7
d0017c8c:	03fbf00b 	mvnseq	pc, #11
d0017c90:	d1262b02 			; <UNDEFINED> instruction: 0xd1262b02
d0017c94:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0017c98:	2800fb41 	stmdacs	r0, {r0, r6, r8, r9, fp, ip, sp, lr, pc}
d0017c9c:	6ae2d1cf 	bvs	0xcf8cc3e0
d0017ca0:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d0017ca4:	d002429a 	mulle	r2, sl, r2
d0017ca8:	4479493d 	ldrbtmi	r4, [r9], #-2365	; 0xfffff6c3
d0017cac:	69a1e693 	stmibvs	r1!, {r0, r1, r4, r7, r9, sl, sp, lr, pc}
d0017cb0:	69e24620 	stmibvs	r2!, {r5, r9, sl, lr}^
d0017cb4:	fd8cf7f8 	stc2	7, cr15, [ip, #992]	; 0x3e0
d0017cb8:	dbf51e01 	blle	0xcfd5f4c4
d0017cbc:	91052330 	tstls	r5, r0, lsr r3
d0017cc0:	4301fb03 	movwmi	pc, #6915	; 0x1b03	; <UNPREDICTABLE>
d0017cc4:	2390f503 	orrscs	pc, r0, #12582912	; 0xc00000
d0017cc8:	3659f893 			; <UNDEFINED> instruction: 0x3659f893
d0017ccc:	d1eb455b 	mvnle	r4, fp, asr r5
d0017cd0:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0017cd4:	2200f8f9 	andcs	pc, r0, #16318464	; 0xf90000
d0017cd8:	46209905 	strtmi	r9, [r0], -r5, lsl #18
d0017cdc:	ff38f7fc 			; <UNDEFINED> instruction: 0xff38f7fc
d0017ce0:	2201e7ad 	andcs	lr, r1, #45350912	; 0x2b40000
d0017ce4:	e7cd4611 	bfi	r4, r1, #12, #2
d0017ce8:	eb041c7a 	bl	0xd011eed8
d0017cec:	462007c7 	strtmi	r0, [r0], -r7, asr #15
d0017cf0:	262cf8c3 	strtcs	pc, [ip], -r3, asr #17
d0017cf4:	2786f507 	strcs	pc, [r6, r7, lsl #10]
d0017cf8:	ffb2f7fc 			; <UNDEFINED> instruction: 0xffb2f7fc
d0017cfc:	f8c79b01 			; <UNDEFINED> instruction: 0xf8c79b01
d0017d00:	f8a7062c 			; <UNDEFINED> instruction: 0xf8a7062c
d0017d04:	b12e3630 			; <UNDEFINED> instruction: 0xb12e3630
d0017d08:	4130f446 	teqmi	r0, r6, asr #8	; <UNPREDICTABLE>
d0017d0c:	b2894620 	addlt	r4, r9, #32, 12	; 0x2000000
d0017d10:	ff00f7fc 			; <UNDEFINED> instruction: 0xff00f7fc
d0017d14:	26389b01 	ldrtcs	r9, [r8], -r1, lsl #22
d0017d18:	4603fb06 	strmi	pc, [r3], -r6, lsl #22
d0017d1c:	367ff506 	ldrbtcc	pc, [pc], -r6, lsl #10	; <UNPREDICTABLE>
d0017d20:	324ff896 	subcc	pc, pc, #9830400	; 0x960000
d0017d24:	d10b2b04 	tstle	fp, r4, lsl #22
d0017d28:	46494620 	strbmi	r4, [r9], -r0, lsr #12
d0017d2c:	fdcaf7fd 	stc2l	7, cr15, [sl, #1012]	; 0x3f4
d0017d30:	2492f504 	ldrcs	pc, [r2], #1284	; 0x504
d0017d34:	3252f896 	subscc	pc, r2, #9830400	; 0x960000
d0017d38:	f8c42506 			; <UNDEFINED> instruction: 0xf8c42506
d0017d3c:	e62e3248 	strt	r3, [lr], -r8, asr #4
d0017d40:	d1072b05 	tstle	r7, r5, lsl #22
d0017d44:	2492f504 	ldrcs	pc, [r2], #1284	; 0x504
d0017d48:	3252f896 	subscc	pc, r2, #9830400	; 0x960000
d0017d4c:	f8c42503 			; <UNDEFINED> instruction: 0xf8c42503
d0017d50:	e6243248 	strt	r3, [r4], -r8, asr #4
d0017d54:	f43f2b01 			; <UNDEFINED> instruction: 0xf43f2b01
d0017d58:	2b03ae21 	blcs	0xd01035e4
d0017d5c:	2504bf08 	strcs	fp, [r4, #-3848]	; 0xfffff0f8
d0017d60:	bf00e61d 	svclt	0x0000e61d
d0017d64:	fffffe5e 			; <UNDEFINED> instruction: 0xfffffe5e
d0017d68:	fffffe48 			; <UNDEFINED> instruction: 0xfffffe48
d0017d6c:	fffffe42 			; <UNDEFINED> instruction: 0xfffffe42
d0017d70:	fffffe1f 			; <UNDEFINED> instruction: 0xfffffe1f
d0017d74:	fffffe12 			; <UNDEFINED> instruction: 0xfffffe12
d0017d78:	fffffe0e 			; <UNDEFINED> instruction: 0xfffffe0e
d0017d7c:	fffffdd2 			; <UNDEFINED> instruction: 0xfffffdd2
d0017d80:	fffffde0 			; <UNDEFINED> instruction: 0xfffffde0
d0017d84:	fffffd86 			; <UNDEFINED> instruction: 0xfffffd86
d0017d88:	fffffd38 			; <UNDEFINED> instruction: 0xfffffd38
d0017d8c:	fffffd12 			; <UNDEFINED> instruction: 0xfffffd12
d0017d90:	fffffcf6 			; <UNDEFINED> instruction: 0xfffffcf6
d0017d94:	fffffcdc 			; <UNDEFINED> instruction: 0xfffffcdc
d0017d98:	fffffca9 			; <UNDEFINED> instruction: 0xfffffca9
d0017d9c:	fffffb98 			; <UNDEFINED> instruction: 0xfffffb98
d0017da0:	fffffbc9 			; <UNDEFINED> instruction: 0xfffffbc9

Disassembly of section .text.struct_pointer_value:

d0017e84 <.text.struct_pointer_value>:
d0017e84:	f2406ac2 	vpmax.s8	q11, q8, q1
d0017e88:	429a1301 	addsmi	r1, sl, #67108864	; 0x4000000
d0017e8c:	4ff0e92d 	svcmi	0x00f0e92d
d0017e90:	460f4604 	strmi	r4, [pc], -r4, lsl #12
d0017e94:	8b02ed2d 	blhi	0xd00d3350
d0017e98:	d14cb087 	smlalbble	fp, ip, r7, r0
d0017e9c:	2d286cc5 	stccs	12, cr6, [r8, #-788]!	; 0xfffffcec
d0017ea0:	6b43d149 	blvs	0xd110c3cc
d0017ea4:	b024f8d0 	ldrdlt	pc, [r4], -r0	; <UNPREDICTABLE>
d0017ea8:	a028f8d0 	ldrdge	pc, [r8], -r0	; <UNPREDICTABLE>
d0017eac:	9030f890 	mlasls	r0, r0, r8, pc	; <UNPREDICTABLE>
d0017eb0:	e9d09304 	ldmib	r0, {r2, r8, r9, ip, pc}^
d0017eb4:	f7fb6806 			; <UNDEFINED> instruction: 0xf7fb6806
d0017eb8:	4af1f807 	bmi	0xcfc95edc
d0017ebc:	46204629 	strtmi	r4, [r0], -r9, lsr #12
d0017ec0:	f7fb447a 			; <UNDEFINED> instruction: 0xf7fb447a
d0017ec4:	b1a8f82f 			; <UNDEFINED> instruction: 0xb1a8f82f
d0017ec8:	46429b04 	strbmi	r9, [r2], -r4, lsl #22
d0017ecc:	46204631 			; <UNDEFINED> instruction: 0x46204631
d0017ed0:	465b9302 	ldrbmi	r9, [fp], -r2, lsl #6
d0017ed4:	9004f8cd 	andls	pc, r4, sp, asr #17
d0017ed8:	a000f8cd 	andge	pc, r0, sp, asr #17
d0017edc:	fcf6f7ff 	ldc2l	7, cr15, [r6], #1020	; 0x3fc
d0017ee0:	46054ae8 	strmi	r4, [r5], -r8, ror #21
d0017ee4:	447a4641 	ldrbtmi	r4, [sl], #-1601	; 0xfffff9bf
d0017ee8:	f7f84630 			; <UNDEFINED> instruction: 0xf7f84630
d0017eec:	b130fd23 	teqlt	r0, r3, lsr #26	; <UNPREDICTABLE>
d0017ef0:	d1142d03 	tstle	r4, r3, lsl #26
d0017ef4:	ecbdb007 	ldc	0, cr11, [sp], #28
d0017ef8:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d0017efc:	4ae28ff0 	bmi	0xcf8bbec4
d0017f00:	46304641 	ldrtmi	r4, [r0], -r1, asr #12
d0017f04:	f7f8447a 			; <UNDEFINED> instruction: 0xf7f8447a
d0017f08:	2800fd15 	stmdacs	r0, {r0, r2, r4, r8, sl, fp, ip, sp, lr, pc}
d0017f0c:	2d03d1f0 	stfcsd	f5, [r3, #-960]	; 0xfffffc40
d0017f10:	f504d105 			; <UNDEFINED> instruction: 0xf504d105
d0017f14:	f8d32392 			; <UNDEFINED> instruction: 0xf8d32392
d0017f18:	42bb3248 	adcsmi	r3, fp, #72, 4	; 0x80000004
d0017f1c:	6da3e7e9 	stcvs	7, cr14, [r3, #932]!	; 0x3a4
d0017f20:	d1e72b00 	mvnle	r2, r0, lsl #22
d0017f24:	447b4bd9 	ldrbtmi	r4, [fp], #-3033	; 0xfffff427
d0017f28:	3b16e9c4 	blcc	0xd05d2640
d0017f2c:	e9c49b04 	stmib	r4, {r2, r8, r9, fp, ip, pc}^
d0017f30:	66a3a918 	ssatvs	sl, #4, r8, lsl #18
d0017f34:	212ae7de 	ldrdcs	lr, [sl, -lr]!	; <UNPREDICTABLE>
d0017f38:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0017f3c:	2800ffe5 	stmdacs	r0, {r0, r2, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0017f40:	6ae2d03d 	bvs	0xcf8cc03c
d0017f44:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d0017f48:	9024f8d4 	ldrdls	pc, [r4], -r4	; <UNPREDICTABLE>
d0017f4c:	f8d4429a 			; <UNDEFINED> instruction: 0xf8d4429a
d0017f50:	f8948028 			; <UNDEFINED> instruction: 0xf8948028
d0017f54:	6b656030 	blvs	0xd197001c
d0017f58:	6da3d00a 	stcvs	0, cr13, [r3, #40]!	; 0x28
d0017f5c:	d1c92b00 	bicle	r2, r9, r0, lsl #22
d0017f60:	66a54bcb 	strtvs	r4, [r5], fp, asr #23
d0017f64:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0017f68:	e9c48618 	stmib	r4, {r3, r4, r9, sl, pc}^
d0017f6c:	e7c13916 	bfi	r3, r6, (invalid: 18:1)
d0017f70:	1206e9d4 	andne	lr, r6, #212, 18	; 0x350000
d0017f74:	f7f84620 			; <UNDEFINED> instruction: 0xf7f84620
d0017f78:	f1b0fc2b 			; <UNDEFINED> instruction: 0xf1b0fc2b
d0017f7c:	dbec0a00 	blle	0xcfb1a784
d0017f80:	fb032330 	blx	0xd00e0c4a
d0017f84:	f503430a 			; <UNDEFINED> instruction: 0xf503430a
d0017f88:	f8932390 			; <UNDEFINED> instruction: 0xf8932390
d0017f8c:	2a122659 	bcs	0xd04a18f8
d0017f90:	f893d1e3 			; <UNDEFINED> instruction: 0xf893d1e3
d0017f94:	42bb365a 	adcsmi	r3, fp, #94371840	; 0x5a00000
d0017f98:	4620d1df 			; <UNDEFINED> instruction: 0x4620d1df
d0017f9c:	ff94f7fa 			; <UNDEFINED> instruction: 0xff94f7fa
d0017fa0:	46204651 			; <UNDEFINED> instruction: 0x46204651
d0017fa4:	f7fc2200 			; <UNDEFINED> instruction: 0xf7fc2200
d0017fa8:	f44ffdd3 			; <UNDEFINED> instruction: 0xf44ffdd3
d0017fac:	462041d0 			; <UNDEFINED> instruction: 0x462041d0
d0017fb0:	ecbdb007 	ldc	0, cr11, [sp], #28
d0017fb4:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d0017fb8:	f7fc4ff0 			; <UNDEFINED> instruction: 0xf7fc4ff0
d0017fbc:	2126bdab 			; <UNDEFINED> instruction: 0x2126bdab
d0017fc0:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0017fc4:	6ae3ffa1 	bvs	0xcf917e50
d0017fc8:	1201f240 	andne	pc, r1, #64, 4
d0017fcc:	42934605 	addsmi	r4, r3, #5242880	; 0x500000
d0017fd0:	8143f040 	cmphi	r3, r0, asr #32	; <UNPREDICTABLE>
d0017fd4:	462069a3 	strtmi	r6, [r0], -r3, lsr #19
d0017fd8:	ee0869e6 	vmls.f16	s12, s17, s13
d0017fdc:	6b633a10 	blvs	0xd18e6824
d0017fe0:	f8d44632 			; <UNDEFINED> instruction: 0xf8d44632
d0017fe4:	ee18b024 	cdp	0, 1, cr11, cr8, cr4, {1}
d0017fe8:	f8d41a10 			; <UNDEFINED> instruction: 0xf8d41a10
d0017fec:	f894a028 			; <UNDEFINED> instruction: 0xf894a028
d0017ff0:	93049030 	movwls	r9, #16432	; 0x4030
d0017ff4:	fbecf7f8 	blx	0xcfb55fde
d0017ff8:	0800f1b0 	stmdaeq	r0, {r4, r5, r7, r8, ip, sp, lr, pc}
d0017ffc:	4632da22 	ldrtmi	sp, [r2], -r2, lsr #20
d0018000:	1a10ee18 	bne	0xd0453868
d0018004:	f7f84620 			; <UNDEFINED> instruction: 0xf7f84620
d0018008:	4603fc03 	strmi	pc, [r3], -r3, lsl #24
d001800c:	4aa1b9ed 	bmi	0xce8867c8
d0018010:	ee184631 	mrc	6, 0, r4, cr8, cr1, {1}
d0018014:	93050a10 	movwls	r0, #23056	; 0x5a10
d0018018:	f7f8447a 			; <UNDEFINED> instruction: 0xf7f8447a
d001801c:	9b05fc8b 	blls	0xd0197250
d0018020:	f1b8b198 			; <UNDEFINED> instruction: 0xf1b8b198
d0018024:	da100f00 	ble	0xd041bc2c
d0018028:	da0e2b00 	ble	0xd03a2c30
d001802c:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0018030:	2100ff4b 	tstcs	r0, fp, asr #30	; <UNPREDICTABLE>
d0018034:	b0074620 	andlt	r4, r7, r0, lsr #12
d0018038:	8b02ecbd 	blhi	0xd00d3334
d001803c:	4ff0e8bd 	svcmi	0x00f0e8bd
d0018040:	b965f7fd 	stmdblt	r5!, {r0, r2, r3, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}^
d0018044:	33fff04f 	mvnscc	pc, #79	; 0x4f
d0018048:	4620e7e0 	strtmi	lr, [r0], -r0, ror #15
d001804c:	f7fa9305 			; <UNDEFINED> instruction: 0xf7fa9305
d0018050:	f1b8ff3b 			; <UNDEFINED> instruction: 0xf1b8ff3b
d0018054:	9b050f00 	blls	0xd015bc5c
d0018058:	2130db22 	teqcs	r0, r2, lsr #22
d001805c:	4108fb01 	tstmi	r8, r1, lsl #22	; <UNPREDICTABLE>
d0018060:	2190f501 	orrscs	pc, r0, r1, lsl #10
d0018064:	2659f891 			; <UNDEFINED> instruction: 0x2659f891
d0018068:	665af891 			; <UNDEFINED> instruction: 0x665af891
d001806c:	01fdf002 	mvnseq	pc, r2
d0018070:	d124290d 			; <UNDEFINED> instruction: 0xd124290d
d0018074:	46204641 	strtmi	r4, [r0], -r1, asr #12
d0018078:	fc24f7fd 	stc2	7, cr15, [r4], #-1012	; 0xfffffc0c
d001807c:	4620212e 	strtmi	r2, [r0], -lr, lsr #2
d0018080:	ff42f7fa 			; <UNDEFINED> instruction: 0xff42f7fa
d0018084:	d0622800 	rsble	r2, r2, r0, lsl #16
d0018088:	d04a2d00 	suble	r2, sl, r0, lsl #26
d001808c:	4631463a 			; <UNDEFINED> instruction: 0x4631463a
d0018090:	b0074620 	andlt	r4, r7, r0, lsr #12
d0018094:	8b02ecbd 	blhi	0xd00d3390
d0018098:	4ff0e8bd 	svcmi	0x00f0e8bd
d001809c:	bcf2f7fd 	ldcllt	7, cr15, [r2], #1012	; 0x3f4
d00180a0:	db5f2b00 	blle	0xd17e2ca8
d00180a4:	fb01213c 	blx	0xd006059e
d00180a8:	f5014103 			; <UNDEFINED> instruction: 0xf5014103
d00180ac:	f891315f 			; <UNDEFINED> instruction: 0xf891315f
d00180b0:	f89123ec 			; <UNDEFINED> instruction: 0xf89123ec
d00180b4:	f00263ee 			; <UNDEFINED> instruction: 0xf00263ee
d00180b8:	290d01fd 	stmdbcs	sp, {r0, r2, r3, r4, r5, r6, r7, r8}
d00180bc:	f1a2d026 			; <UNDEFINED> instruction: 0xf1a2d026
d00180c0:	29010110 	stmdbcs	r1, {r4, r8}
d00180c4:	808ef200 	addhi	pc, lr, r0, lsl #4
d00180c8:	0f00f1b8 	svceq	0x0000f1b8
d00180cc:	4641db4d 	strbmi	sp, [r1], -sp, asr #22
d00180d0:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d00180d4:	6ae3fbf7 	bvs	0xcf9170b8
d00180d8:	d1782b5b 	cmnle	r8, fp, asr fp
d00180dc:	2d002301 	stccs	3, cr2, [r0, #-4]
d00180e0:	4631d04e 	ldrtmi	sp, [r1], -lr, asr #32
d00180e4:	46202200 	strtmi	r2, [r0], -r0, lsl #4
d00180e8:	f99af7ff 			; <UNDEFINED> instruction: 0xf99af7ff
d00180ec:	4620212e 	strtmi	r2, [r0], -lr, lsr #2
d00180f0:	ff0af7fa 			; <UNDEFINED> instruction: 0xff0af7fa
d00180f4:	d1c92800 	bicle	r2, r9, r0, lsl #16
d00180f8:	f43f42b7 			; <UNDEFINED> instruction: 0xf43f42b7
d00180fc:	6da3aefb 	stcvs	14, cr10, [r3, #1004]!	; 0x3ec
d0018100:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0018104:	4b64aef7 	blmi	0xd1943ce8
d0018108:	e70d447b 	smlsdx	sp, fp, r4, r4
d001810c:	461a4620 	ldrmi	r4, [sl], -r0, lsr #12
d0018110:	f7fc2101 			; <UNDEFINED> instruction: 0xf7fc2101
d0018114:	f244fd67 	vadd.f32	<illegal reg q15.5>, q2, <illegal reg q11.5>
d0018118:	46206108 	strtmi	r6, [r0], -r8, lsl #2
d001811c:	fcfaf7fc 	ldc2l	7, cr15, [sl], #1008	; 0x3f0
d0018120:	462be7ac 	strtmi	lr, [fp], -ip, lsr #15
d0018124:	4631462a 	ldrtmi	r4, [r1], -sl, lsr #12
d0018128:	f0004620 			; <UNDEFINED> instruction: 0xf0004620
d001812c:	2803f965 	stmdacs	r3, {r0, r2, r5, r6, r8, fp, ip, sp, lr, pc}
d0018130:	f504d106 			; <UNDEFINED> instruction: 0xf504d106
d0018134:	f8d32392 			; <UNDEFINED> instruction: 0xf8d32392
d0018138:	42bb3248 	adcsmi	r3, fp, #72, 4	; 0x80000004
d001813c:	aedaf43f 	mrcge	4, 6, APSR_nzcv, cr10, cr15, {1}
d0018140:	2b006da3 	blcs	0xd00337d4
d0018144:	aed6f47f 	mrcge	4, 6, APSR_nzcv, cr6, cr15, {3}
d0018148:	447b4b54 	ldrbtmi	r4, [fp], #-2900	; 0xfffff4ac
d001814c:	b115e6ec 	tstlt	r5, ip, ror #13
d0018150:	f43f42b7 			; <UNDEFINED> instruction: 0xf43f42b7
d0018154:	6da3aecf 	stcvs	14, cr10, [r3, #828]!	; 0x33c
d0018158:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001815c:	4b50aecb 	blmi	0xd1443c90
d0018160:	e6e1447b 	uxtab	r4, r1, fp, ror #8
d0018164:	220b26ff 	andcs	r2, fp, #267386880	; 0xff00000
d0018168:	4620e7a9 	strtmi	lr, [r0], -r9, lsr #15
d001816c:	2101461a 	tstcs	r1, sl, lsl r6
d0018170:	fd38f7fc 	ldc2	7, cr15, [r8, #-1008]!	; 0xfffffc10
d0018174:	6108f244 	tstvs	r8, r4, asr #4	; <UNPREDICTABLE>
d0018178:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d001817c:	e7aafccb 	str	pc, [sl, fp, asr #25]!
d0018180:	462a4631 			; <UNDEFINED> instruction: 0x462a4631
d0018184:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0018188:	212ef94b 	msrcs	CPSR_fsx, fp, asr #18
d001818c:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0018190:	b1a8febb 			; <UNDEFINED> instruction: 0xb1a8febb
d0018194:	462a462b 	strtmi	r4, [sl], -fp, lsr #12
d0018198:	46204631 			; <UNDEFINED> instruction: 0x46204631
d001819c:	f92cf000 			; <UNDEFINED> instruction: 0xf92cf000
d00181a0:	d1062803 	tstle	r6, r3, lsl #16
d00181a4:	2392f504 	orrscs	pc, r2, #4, 10	; 0x1000000
d00181a8:	3248f8d3 	subcc	pc, r8, #13828096	; 0xd30000
d00181ac:	f43f42bb 			; <UNDEFINED> instruction: 0xf43f42bb
d00181b0:	6da3aea1 	stcvs	14, cr10, [r3, #644]!	; 0x284
d00181b4:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d00181b8:	4b3aae9d 	blmi	0xd0ec3c34
d00181bc:	e6b3447b 	sxtah	r4, r3, fp, ror #8
d00181c0:	2b006da3 	blcs	0xd0033854
d00181c4:	ae96f47f 	mrcge	4, 4, APSR_nzcv, cr6, cr15, {3}
d00181c8:	447b4b37 	ldrbtmi	r4, [fp], #-2871	; 0xfffff4c9
d00181cc:	b915e6ac 	ldmdblt	r5, {r2, r3, r5, r7, r9, sl, sp, lr, pc}
d00181d0:	f43f42b7 			; <UNDEFINED> instruction: 0xf43f42b7
d00181d4:	6da3ae8f 	stcvs	14, cr10, [r3, #572]!	; 0x23c
d00181d8:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d00181dc:	4b33ae8b 	blmi	0xd0d03c10
d00181e0:	e6a1447b 	sxtab	r4, r1, fp, ror #8
d00181e4:	d1312a0e 	teqle	r1, lr, lsl #20
d00181e8:	0f00f1b8 	svceq	0x0000f1b8
d00181ec:	4641db2e 	strbmi	sp, [r1], -lr, lsr #22
d00181f0:	22004620 	andcs	r4, r0, #32, 12	; 0x2000000
d00181f4:	fcacf7fc 	stc2	7, cr15, [ip], #1008	; 0x3f0
d00181f8:	7191f44f 	orrsvc	pc, r1, pc, asr #8
d00181fc:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0018200:	b1c0fe83 	biclt	pc, r0, r3, lsl #29
d0018204:	f47f2d00 			; <UNDEFINED> instruction: 0xf47f2d00
d0018208:	462baf41 	strtmi	sl, [fp], -r1, asr #30
d001820c:	4631462a 	ldrtmi	r4, [r1], -sl, lsr #12
d0018210:	f0004620 			; <UNDEFINED> instruction: 0xf0004620
d0018214:	2803f8f1 	stmdacs	r3, {r0, r4, r5, r6, r7, fp, ip, sp, lr, pc}
d0018218:	f504d106 			; <UNDEFINED> instruction: 0xf504d106
d001821c:	f8d32392 			; <UNDEFINED> instruction: 0xf8d32392
d0018220:	42bb3248 	adcsmi	r3, fp, #72, 4	; 0x80000004
d0018224:	ae66f43f 	mcrge	4, 3, pc, cr6, cr15, {1}	; <UNPREDICTABLE>
d0018228:	2b006da3 	blcs	0xd00338bc
d001822c:	ae62f47f 	mcrge	4, 3, pc, cr2, cr15, {3}	; <UNPREDICTABLE>
d0018230:	447b4b1f 	ldrbtmi	r4, [fp], #-2847	; 0xfffff4e1
d0018234:	b915e678 	ldmdblt	r5, {r3, r4, r5, r6, r9, sl, sp, lr, pc}
d0018238:	f43f42b7 			; <UNDEFINED> instruction: 0xf43f42b7
d001823c:	6da3ae5b 	stcvs	14, cr10, [r3, #364]!	; 0x16c
d0018240:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0018244:	4b1bae57 	blmi	0xd0703ba8
d0018248:	e66d447b 			; <UNDEFINED> instruction: 0xe66d447b
d001824c:	2b006da3 	blcs	0xd00338e0
d0018250:	ae50f47f 	mrcge	4, 2, APSR_nzcv, cr0, cr15, {3}
d0018254:	447b4b18 	ldrbtmi	r4, [fp], #-2840	; 0xfffff4e8
d0018258:	b938e666 	ldmdblt	r8!, {r1, r2, r5, r6, r9, sl, sp, lr, pc}
d001825c:	7381f5a3 	orrvc	pc, r1, #683671552	; 0x28c00000
d0018260:	d8032b01 	stmdale	r3, {r0, r8, r9, fp, sp}
d0018264:	2b006a23 	blcs	0xd0032af8
d0018268:	aee0f43f 	mcrge	4, 7, pc, cr0, cr15, {1}	; <UNPREDICTABLE>
d001826c:	46204913 			; <UNDEFINED> instruction: 0x46204913
d0018270:	b0074479 	andlt	r4, r7, r9, ror r4
d0018274:	8b02ecbd 	blhi	0xd00d3570
d0018278:	4ff0e8bd 	svcmi	0x00f0e8bd
d001827c:	bff8f7f7 	svclt	0x00f8f7f7
d0018280:	fffffee0 			; <UNDEFINED> instruction: 0xfffffee0
d0018284:	fffff85a 			; <UNDEFINED> instruction: 0xfffff85a
d0018288:	fffff848 			; <UNDEFINED> instruction: 0xfffff848
d001828c:	fffffe9b 			; <UNDEFINED> instruction: 0xfffffe9b
d0018290:	fffffe8a 			; <UNDEFINED> instruction: 0xfffffe8a
d0018294:	ffffd2fa 			; <UNDEFINED> instruction: 0xffffd2fa
d0018298:	ffffd949 			; <UNDEFINED> instruction: 0xffffd949
d001829c:	ffffd907 			; <UNDEFINED> instruction: 0xffffd907
d00182a0:	ffffd8f1 			; <UNDEFINED> instruction: 0xffffd8f1
d00182a4:	ffffd895 			; <UNDEFINED> instruction: 0xffffd895
d00182a8:	fffffc52 			; <UNDEFINED> instruction: 0xfffffc52
d00182ac:	ffffd871 			; <UNDEFINED> instruction: 0xffffd871
d00182b0:	ffffd81f 			; <UNDEFINED> instruction: 0xffffd81f
d00182b4:	ffffd809 			; <UNDEFINED> instruction: 0xffffd809
d00182b8:	ffffd7fb 			; <UNDEFINED> instruction: 0xffffd7fb
d00182bc:	fffffbd6 			; <UNDEFINED> instruction: 0xfffffbd6

Disassembly of section .text.struct_member:

d00183f8 <.text.struct_member>:
d00183f8:	4ff0e92d 	svcmi	0x00f0e92d
d00183fc:	4bc3461d 	blmi	0xcf0e9c78
d0018400:	447b4604 	ldrbtmi	r4, [fp], #-1540	; 0xfffff9fc
d0018404:	8b02ed2d 	blhi	0xd00d38c0
d0018408:	3a90ee08 	bcc	0xce453c30
d001840c:	9103b087 	smlabbls	r3, r7, r0, fp
d0018410:	69a39204 	stmibvs	r3!, {r2, r9, ip, pc}
d0018414:	2a90ee18 	bcs	0xce453c7c
d0018418:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d001841c:	ee084620 	cfmadd32	mvax1, mvfx4, mvfx8, mvfx0
d0018420:	69e33a10 	stmibvs	r3!, {r4, r9, fp, ip, sp}^
d0018424:	a024f8d4 	ldrdge	pc, [r4], -r4	; <UNPREDICTABLE>
d0018428:	f8d49301 			; <UNDEFINED> instruction: 0xf8d49301
d001842c:	f8949028 			; <UNDEFINED> instruction: 0xf8949028
d0018430:	6b678030 	blvs	0xd19f84f8
d0018434:	fd76f7fa 	ldc2l	7, cr15, [r6, #-1000]!	; 0xfffffc18
d0018438:	b9089b01 	stmdblt	r8, {r0, r8, r9, fp, ip, pc}
d001843c:	e02e2500 	eor	r2, lr, r0, lsl #10
d0018440:	f44f9a03 	vst1.8	{d25-d26}, [pc], r3
d0018444:	fb01711a 	blx	0xd00748b6
d0018448:	f50bfb02 			; <UNDEFINED> instruction: 0xf50bfb02
d001844c:	44a33267 	strtmi	r3, [r3], #615	; 0x267
d0018450:	72f4f502 	rscsvc	pc, r4, #8388608	; 0x800000
d0018454:	3b68f50b 	blcc	0xd1a55888
d0018458:	18a29202 	stmiane	r2!, {r1, r9, ip, pc}
d001845c:	22004616 	andcs	r4, r0, #23068672	; 0x1600000
d0018460:	f89b9201 			; <UNDEFINED> instruction: 0xf89b9201
d0018464:	9901202a 	stmdbls	r1, {r1, r3, r5, sp}
d0018468:	d81e428a 	ldmdale	lr, {r1, r3, r7, r9, lr}
d001846c:	f44f9b03 			; <UNDEFINED> instruction: 0xf44f9b03
d0018470:	fb02721a 	blx	0xd00b4ce2
d0018474:	9a014103 	bls	0xd0068888
d0018478:	3168f501 	msrcc	SPSR_f, r1, lsl #10
d001847c:	302af891 	mlacc	sl, r1, r8, pc	; <UNPREDICTABLE>
d0018480:	d1244293 			; <UNDEFINED> instruction: 0xd1244293
d0018484:	302bf891 	mlacc	fp, r1, r8, pc	; <UNPREDICTABLE>
d0018488:	4ba1b9f3 	blmi	0xce886c5c
d001848c:	6da5447b 	cfstrsvs	mvf4, [r5, #492]!	; 0x1ec
d0018490:	d1d32d00 	bicsle	r2, r3, r0, lsl #26
d0018494:	e9c466a7 	stmib	r4, {r0, r1, r2, r5, r7, r9, sl, sp, lr}^
d0018498:	e9c43a16 	stmib	r4, {r1, r2, r4, r9, fp, ip, sp}^
d001849c:	46289818 			; <UNDEFINED> instruction: 0x46289818
d00184a0:	ecbdb007 	ldc	0, cr11, [sp], #28
d00184a4:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d00184a8:	68718ff0 	ldmdavs	r1!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}^
d00184ac:	2a10ee18 	bcs	0xd0453d14
d00184b0:	0b24f856 	bleq	0xd0956610
d00184b4:	f7f89305 			; <UNDEFINED> instruction: 0xf7f89305
d00184b8:	9b05f915 	blls	0xd0196914
d00184bc:	d1d52800 	bicsle	r2, r5, r0, lsl #16
d00184c0:	32019a01 	andcc	r9, r1, #4096	; 0x1000
d00184c4:	e7cc9201 	strb	r9, [ip, r1, lsl #4]
d00184c8:	447b4b92 	ldrbtmi	r4, [fp], #-2962	; 0xfffff46e
d00184cc:	2324e7df 			; <UNDEFINED> instruction: 0x2324e7df
d00184d0:	99019a02 	stmdbls	r1, {r1, r9, fp, ip, pc}
d00184d4:	2601fb03 	strcs	pc, [r1], -r3, lsl #22
d00184d8:	8c5a19a3 	mrrchi	9, 10, r1, sl, cr3	; <UNPREDICTABLE>
d00184dc:	6020f893 	mlavs	r0, r3, r8, pc	; <UNPREDICTABLE>
d00184e0:	b021f893 	mlalt	r1, r3, r8, pc	; <UNPREDICTABLE>
d00184e4:	2101b14a 	tstcs	r1, sl, asr #2
d00184e8:	00924620 	addseq	r4, r2, r0, lsr #12
d00184ec:	fecdf7fc 	mcr2	7, 6, pc, cr13, cr12, {7}	; <UNPREDICTABLE>
d00184f0:	51c2f44f 	bicpl	pc, r2, pc, asr #8
d00184f4:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d00184f8:	f1bbfb0d 			; <UNDEFINED> instruction: 0xf1bbfb0d
d00184fc:	d06f0f00 	rsble	r0, pc, r0, lsl #30
d0018500:	7191f44f 	orrsvc	pc, r1, pc, asr #8
d0018504:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0018508:	b170fcff 	ldrshlt	pc, [r0, #-207]!	; 0xffffff31	; <UNPREDICTABLE>
d001850c:	d1052eff 	strdle	r2, [r5, -pc]
d0018510:	2d006da5 	stccs	13, cr6, [r0, #-660]	; 0xfffffd6c
d0018514:	4b80d192 	blmi	0xce04cb64
d0018518:	e7bb447b 			; <UNDEFINED> instruction: 0xe7bb447b
d001851c:	41d0f44f 	bicsmi	pc, r0, pc, asr #8
d0018520:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0018524:	9603faf7 			; <UNDEFINED> instruction: 0x9603faf7
d0018528:	6ae3e773 	bvs	0xcf9122fc
d001852c:	d10b2b2e 	tstle	fp, lr, lsr #22
d0018530:	b10b6da3 	smlatblt	fp, r3, sp, r6
d0018534:	e7b22503 	ldr	r2, [r2, r3, lsl #10]!
d0018538:	447b4b78 	ldrbtmi	r4, [fp], #-2936	; 0xfffff488
d001853c:	e9c466a7 	stmib	r4, {r0, r1, r2, r5, r7, r9, sl, sp, lr}^
d0018540:	e9c43a16 	stmib	r4, {r1, r2, r4, r9, fp, ip, sp}^
d0018544:	e7f59818 			; <UNDEFINED> instruction: 0xe7f59818
d0018548:	6da3b12d 	stfvsd	f3, [r3, #180]!	; 0xb4
d001854c:	d1f12b00 	mvnsle	r2, r0, lsl #22
d0018550:	447b4b73 	ldrbtmi	r4, [fp], #-2931	; 0xfffff48d
d0018554:	9b04e7f2 	blls	0xd0152524
d0018558:	213db30b 	teqcs	sp, fp, lsl #6
d001855c:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0018560:	b1e0fcd3 	ldrdlt	pc, [r0, #195]!	; 0xc3
d0018564:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d0018568:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d001856c:	2efffad3 	mrccs	10, 7, APSR_nzcv, cr15, cr3, {6}
d0018570:	2204d110 	andcs	sp, r4, #16, 2
d0018574:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d0018578:	fe5ef7fd 	mrc2	7, 2, pc, cr14, cr13, {7}
d001857c:	4106f64b 	tstmi	r6, fp, asr #12	; <UNPREDICTABLE>
d0018580:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0018584:	f246fac7 	vpmax.s8	<illegal reg q15.5>, q11, <illegal reg q3.5>
d0018588:	46200108 	strtmi	r0, [r0], -r8, lsl #2
d001858c:	f7fc2502 			; <UNDEFINED> instruction: 0xf7fc2502
d0018590:	e784fac1 	str	pc, [r4, r1, asr #21]
d0018594:	46204631 			; <UNDEFINED> instruction: 0x46204631
d0018598:	fc74f7ff 	ldc2l	7, cr15, [r4], #-1020	; 0xfffffc04
d001859c:	6ae3e7ee 	bvs	0xcf91255c
d00185a0:	7592f46f 	ldrvc	pc, [r2, #1135]	; 0x46f
d00185a4:	2a01195a 	bcs	0xd005eb14
d00185a8:	f46fd904 	vld2.8	{d29,d31}, [pc], r4
d00185ac:	44037094 	strmi	r7, [r3], #-148	; 0xffffff6c
d00185b0:	d8082b04 	stmdale	r8, {r2, r8, r9, fp, sp}
d00185b4:	b9336da3 	ldmdblt	r3!, {r0, r1, r5, r7, r8, sl, fp, sp, lr}
d00185b8:	66a74b5a 	ssatvs	r4, #8, sl, asr #22
d00185bc:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d00185c0:	e9c49818 	stmib	r4, {r3, r4, fp, ip, pc}^
d00185c4:	46203a16 			; <UNDEFINED> instruction: 0x46203a16
d00185c8:	41d0f44f 	bicsmi	pc, r0, pc, asr #8
d00185cc:	faa2f7fc 	blx	0xce8d65c4
d00185d0:	2492f504 	ldrcs	pc, [r2], #1284	; 0x504
d00185d4:	f8c42eff 			; <UNDEFINED> instruction: 0xf8c42eff
d00185d8:	d1ab6248 			; <UNDEFINED> instruction: 0xd1ab6248
d00185dc:	e75e2504 	ldrb	r2, [lr, -r4, lsl #10]
d00185e0:	d00d2eff 	strdle	r2, [sp], -pc	; <UNPREDICTABLE>
d00185e4:	4620212e 	strtmi	r2, [r0], -lr, lsr #2
d00185e8:	fc8ef7fa 	stc2	7, cr15, [lr], {250}	; 0xfa
d00185ec:	d19a2800 	orrsle	r2, sl, r0, lsl #16
d00185f0:	d19f2d00 	orrsle	r2, pc, r0, lsl #26
d00185f4:	2b006da3 	blcs	0xd0033c88
d00185f8:	4b4bd19c 	blmi	0xd130cc70
d00185fc:	e79d447b 			; <UNDEFINED> instruction: 0xe79d447b
d0018600:	2e2e6ae6 	vnmulcs.f32	s12, s29, s13
d0018604:	f5b6d002 			; <UNDEFINED> instruction: 0xf5b6d002
d0018608:	d1057f91 			; <UNDEFINED> instruction: 0xd1057f91
d001860c:	46204947 	strtmi	r4, [r0], -r7, asr #18
d0018610:	f7f74479 			; <UNDEFINED> instruction: 0xf7f74479
d0018614:	e711fe2d 	ldr	pc, [r1, -sp, lsr #28]
d0018618:	d1df2d00 	bicsle	r2, pc, r0, lsl #26
d001861c:	2b009b04 	blcs	0xd003f234
d0018620:	2e3dd06d 	cdpcs	0, 3, cr13, cr13, cr13, {3}
d0018624:	f46fd009 	vld4.8	{d29-d32}, [pc], r9
d0018628:	18737192 	ldmdane	r3!, {r1, r4, r7, r8, ip, sp, lr}^
d001862c:	d9042b01 	stmdble	r4, {r0, r8, r9, fp, sp}
d0018630:	7294f46f 	addsvc	pc, r4, #1862270976	; 0x6f000000
d0018634:	2b0418b3 	blcs	0xd011e908
d0018638:	4620d861 	strtmi	sp, [r0], -r1, ror #16
d001863c:	fc44f7fa 	mcrr2	7, 15, pc, r4, cr10	; <UNPREDICTABLE>
d0018640:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d0018644:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0018648:	2e3dfa65 	vsubcs.f32	s30, s26, s11
d001864c:	f44fd009 	vst4.8	{d29-d32}, [pc], r9
d0018650:	462041d0 			; <UNDEFINED> instruction: 0x462041d0
d0018654:	fa5ef7fc 	blx	0xd17d664c
d0018658:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d001865c:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0018660:	2201fa59 	andcs	pc, r1, #364544	; 0x59000
d0018664:	46114620 	ldrmi	r4, [r1], -r0, lsr #12
d0018668:	fde6f7fd 	stc2l	7, cr15, [r6, #1012]!	; 0x3f4
d001866c:	d0852e3d 	addle	r2, r5, sp, lsr lr
d0018670:	4106f64b 	tstmi	r6, fp, asr #12	; <UNPREDICTABLE>
d0018674:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0018678:	f46ffa4d 	vld1.16	{d31-d32}, [pc]!
d001867c:	18f37392 	ldmne	r3!, {r1, r4, r7, r8, r9, ip, sp, lr}^
d0018680:	f63f2b08 			; <UNDEFINED> instruction: 0xf63f2b08
d0018684:	a202af7b 	andge	sl, r2, #492	; 0x1ec
d0018688:	3023f852 	eorcc	pc, r3, r2, asr r8	; <UNPREDICTABLE>
d001868c:	4710441a 			; <UNDEFINED> instruction: 0x4710441a
d0018690:	00000025 	andeq	r0, r0, r5, lsr #32
d0018694:	00000031 	andeq	r0, r0, r1, lsr r0
d0018698:	fffffeed 			; <UNDEFINED> instruction: 0xfffffeed
d001869c:	fffffeed 			; <UNDEFINED> instruction: 0xfffffeed
d00186a0:	00000037 	andeq	r0, r0, r7, lsr r0
d00186a4:	0000003d 	andeq	r0, r0, sp, lsr r0
d00186a8:	00000043 	andeq	r0, r0, r3, asr #32
d00186ac:	00000049 	andeq	r0, r0, r9, asr #32
d00186b0:	00000049 	andeq	r0, r0, r9, asr #32
d00186b4:	0108f641 	tsteq	r8, r1, asr #12	; <UNPREDICTABLE>
d00186b8:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d00186bc:	e75dfa2b 	ldrb	pc, [sp, -fp, lsr #20]	; <UNPREDICTABLE>
d00186c0:	2108f641 	tstcs	r8, r1, asr #12	; <UNPREDICTABLE>
d00186c4:	f244e7f8 	vaba.s8	q15, q10, q12
d00186c8:	e7f50108 	ldrb	r0, [r5, r8, lsl #2]!
d00186cc:	3108f244 	tstcc	r8, r4, asr #4	; <UNPREDICTABLE>
d00186d0:	f244e7f2 	vaba.s8	q15, q10, q9
d00186d4:	e7ef0148 	strb	r0, [pc, r8, asr #2]!
d00186d8:	6102f244 	tstvs	r2, r4, asr #4	; <UNPREDICTABLE>
d00186dc:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d00186e0:	f244fa19 	vpmin.s8	d31, d4, d9
d00186e4:	46206108 	strtmi	r6, [r0], -r8, lsl #2
d00186e8:	fa14f7fc 	blx	0xd05566e0
d00186ec:	0190f244 	orrseq	pc, r0, r4, asr #4
d00186f0:	1310f244 	tstne	r0, #68, 4	; 0x40000004	; <UNPREDICTABLE>
d00186f4:	7f96f5b6 	svcvc	0x0096f5b6
d00186f8:	4619bf18 	sadd16mi	fp, r9, r8
d00186fc:	f44fe7dc 	vst1.64	{d30}, [pc :64], ip
d0018700:	462041d0 			; <UNDEFINED> instruction: 0x462041d0
d0018704:	fa06f7fc 	blx	0xd01d66fc
d0018708:	bf00e6c9 	svclt	0x0000e6c9
d001870c:	fffffee3 			; <UNDEFINED> instruction: 0xfffffee3
d0018710:	fffffe44 			; <UNDEFINED> instruction: 0xfffffe44
d0018714:	fffffdf2 			; <UNDEFINED> instruction: 0xfffffdf2
d0018718:	fffffde9 			; <UNDEFINED> instruction: 0xfffffde9
d001871c:	fffffde9 			; <UNDEFINED> instruction: 0xfffffde9
d0018720:	fffffdf2 			; <UNDEFINED> instruction: 0xfffffdf2
d0018724:	fffffdbe 			; <UNDEFINED> instruction: 0xfffffdbe
d0018728:	fffffda3 			; <UNDEFINED> instruction: 0xfffffda3
d001872c:	fffffdb7 			; <UNDEFINED> instruction: 0xfffffdb7

Disassembly of section .text.unary:

d0018a98 <.text.unary>:
d0018a98:	4ff0e92d 	svcmi	0x00f0e92d
d0018a9c:	b058f8d0 	ldrsblt	pc, [r8], #-128	; 0xffffff80	; <UNPREDICTABLE>
d0018aa0:	460e4604 	strmi	r4, [lr], -r4, lsl #12
d0018aa4:	8b02ed2d 	blhi	0xd00d3f60
d0018aa8:	f1bbb09d 			; <UNDEFINED> instruction: 0xf1bbb09d
d0018aac:	f0400f00 			; <UNDEFINED> instruction: 0xf0400f00
d0018ab0:	6a838527 	bvs	0xce0f9f54
d0018ab4:	93076ac7 	movwls	r6, #31431	; 0x7ac7
d0018ab8:	3030f890 	mlascc	r0, r0, r8, pc	; <UNPREDICTABLE>
d0018abc:	6b439308 	blvs	0xd10fd6e4
d0018ac0:	f5009306 			; <UNDEFINED> instruction: 0xf5009306
d0018ac4:	f8d32392 			; <UNDEFINED> instruction: 0xf8d32392
d0018ac8:	93092244 	movwls	r2, #37444	; 0x9244
d0018acc:	2a203201 	bcs	0xd08252d8
d0018ad0:	9a06e9d0 	bls	0xd01d3218
d0018ad4:	5808e9d0 	stmdapl	r8, {r4, r6, r7, r8, fp, sp, lr, pc}
d0018ad8:	2244f8c3 	subcs	pc, r4, #12779520	; 0xc30000
d0018adc:	f8dfd906 			; <UNDEFINED> instruction: 0xf8dfd906
d0018ae0:	44791b2c 	ldrbtmi	r1, [r9], #-2860	; 0xfffff4d4
d0018ae4:	fbc4f7f7 	blx	0xcf156aca
d0018ae8:	e0d12500 	sbcs	r2, r1, r0, lsl #10
d0018aec:	718df44f 	orrvc	pc, sp, pc, asr #8
d0018af0:	fa0af7fa 	blx	0xd02d6ae0
d0018af4:	4620b140 	strtmi	fp, [r0], -r0, asr #2
d0018af8:	ffa6f7fa 			; <UNDEFINED> instruction: 0xffa6f7fa
d0018afc:	46204601 	strtmi	r4, [r0], -r1, lsl #12
d0018b00:	fc05f7fc 	stc2	7, cr15, [r5], {252}	; 0xfc
d0018b04:	e0c32501 	sbc	r2, r3, r1, lsl #10
d0018b08:	7181f44f 	orrvc	pc, r1, pc, asr #8
d0018b0c:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0018b10:	b150f9fb 	ldrshlt	pc, [r0, #-155]	; 0xffffff65	; <UNPREDICTABLE>
d0018b14:	46294620 	strtmi	r4, [r9], -r0, lsr #12
d0018b18:	fbf9f7fc 	blx	0xcfe96b12
d0018b1c:	1003f240 	andne	pc, r3, r0, asr #4
d0018b20:	bf144287 	svclt	0x00144287
d0018b24:	25012500 	strcs	r2, [r1, #-1280]	; 0xfffffb00
d0018b28:	f240e0b2 	vqadd.s8	d30, d16, d18
d0018b2c:	46201103 	strtmi	r1, [r0], -r3, lsl #2
d0018b30:	f9eaf7fa 			; <UNDEFINED> instruction: 0xf9eaf7fa
d0018b34:	d1ed2800 	mvnle	r2, r0, lsl #16
d0018b38:	1123f240 	msrne	R11_usr, r0
d0018b3c:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0018b40:	b308f9e3 	movwlt	pc, #35299	; 0x89e3	; <UNPREDICTABLE>
d0018b44:	2ac8f8df 	bcs	0xcf256ec8
d0018b48:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d0018b4c:	46206a63 	strtmi	r6, [r0], -r3, ror #20
d0018b50:	f8d4447a 			; <UNDEFINED> instruction: 0xf8d4447a
d0018b54:	f8948028 			; <UNDEFINED> instruction: 0xf8948028
d0018b58:	f8d49030 			; <UNDEFINED> instruction: 0xf8d49030
d0018b5c:	9306a034 	movwls	sl, #24628	; 0x6034
d0018b60:	5606e9d4 			; <UNDEFINED> instruction: 0x5606e9d4
d0018b64:	f9def7fa 			; <UNDEFINED> instruction: 0xf9def7fa
d0018b68:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d0018b6c:	22008325 	andcs	r8, r0, #-1811939328	; 0x94000000
d0018b70:	46299b06 	strtmi	r9, [r9], -r6, lsl #22
d0018b74:	92049703 	andls	r9, r4, #786432	; 0xc0000
d0018b78:	e88d4632 	stm	sp, {r1, r4, r5, r9, sl, lr}
d0018b7c:	46200700 	strtmi	r0, [r0], -r0, lsl #14
d0018b80:	f9d8f7fc 			; <UNDEFINED> instruction: 0xf9d8f7fc
d0018b84:	e0834605 	add	r4, r3, r5, lsl #12
d0018b88:	7192f44f 	orrsvc	pc, r2, pc, asr #8
d0018b8c:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0018b90:	4683f9bb 			; <UNDEFINED> instruction: 0x4683f9bb
d0018b94:	d1d52800 	bicsle	r2, r5, r0, lsl #16
d0018b98:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d0018b9c:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0018ba0:	4605f9b3 			; <UNDEFINED> instruction: 0x4605f9b3
d0018ba4:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d0018ba8:	f8df82ee 			; <UNDEFINED> instruction: 0xf8df82ee
d0018bac:	46512a68 	ldrbmi	r2, [r1], -r8, ror #20
d0018bb0:	447a4648 	ldrbtmi	r4, [sl], #-1608	; 0xfffff9b8
d0018bb4:	febef7f7 	mrc2	7, 5, pc, cr14, cr7, {7}
d0018bb8:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d0018bbc:	6ae380a5 	bvs	0xcf8f8e58
d0018bc0:	f0402b2e 			; <UNDEFINED> instruction: 0xf0402b2e
d0018bc4:	f8df80a1 			; <UNDEFINED> instruction: 0xf8df80a1
d0018bc8:	25039a50 	strcs	r9, [r3, #-2640]	; 0xfffff5b0
d0018bcc:	1a4cf8df 	bne	0xd1356f50
d0018bd0:	44f92203 	ldrbtmi	r2, [r9], #515	; 0x203
d0018bd4:	4479a80c 	ldrbtmi	sl, [r9], #-2060	; 0xfffff7f4
d0018bd8:	fd28f008 	stc2	0, cr15, [r8, #-32]!	; 0xffffffe0
d0018bdc:	2f2e6ae7 	svccs	0x002e6ae7
d0018be0:	f5b7d002 			; <UNDEFINED> instruction: 0xf5b7d002
d0018be4:	d12c7f91 			; <UNDEFINED> instruction: 0xd12c7f91
d0018be8:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0018bec:	69a3f96d 	stmibvs	r3!, {r0, r2, r3, r5, r6, r8, fp, ip, sp, lr, pc}
d0018bf0:	f240464a 	vmax.s8	q10, q0, q5
d0018bf4:	ee081101 	adfe	f1, f0, f1
d0018bf8:	6a633a10 	bvs	0xd18e7440
d0018bfc:	f8d44620 			; <UNDEFINED> instruction: 0xf8d44620
d0018c00:	930ba01c 	movwls	sl, #45084	; 0xb01c
d0018c04:	6b666aa3 	blvs	0xd19b3698
d0018c08:	f8949309 			; <UNDEFINED> instruction: 0xf8949309
d0018c0c:	930a3030 	movwls	r3, #41008	; 0xa030
d0018c10:	f988f7fa 			; <UNDEFINED> instruction: 0xf988f7fa
d0018c14:	2f2eb1a8 	svccs	0x002eb1a8
d0018c18:	020aeb05 	andeq	lr, sl, #5120	; 0x1400
d0018c1c:	bf0c9b0b 	svclt	0x000c9b0b
d0018c20:	21022101 	tstcs	r2, r1, lsl #2
d0018c24:	2a3f440a 	bcs	0xd0fe9c54
d0018c28:	6da2d93b 			; <UNDEFINED> instruction: 0x6da2d93b
d0018c2c:	f8dfb94a 			; <UNDEFINED> instruction: 0xf8dfb94a
d0018c30:	66a629f0 			; <UNDEFINED> instruction: 0x66a629f0
d0018c34:	e9c4447a 	stmib	r4, {r1, r3, r4, r5, r6, sl, lr}^
d0018c38:	9b092316 	blls	0xd0261898
d0018c3c:	9b0a6623 	blls	0xd02b24d0
d0018c40:	ab1c6663 	blge	0xd07325d4
d0018c44:	442b2200 	strtmi	r2, [fp], #-512	; 0xfffffe00
d0018c48:	2c40f803 	mcrrcs	8, 0, pc, r0, cr3	; <UNPREDICTABLE>
d0018c4c:	b9f36da3 	ldmiblt	r3!, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0018c50:	29d0f8df 	ldmibcs	r0, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d0018c54:	46202128 	strtmi	r2, [r0], -r8, lsr #2
d0018c58:	f7fa447a 			; <UNDEFINED> instruction: 0xf7fa447a
d0018c5c:	b1b0f963 	rorslt	pc, r3, #18	; <UNPREDICTABLE>
d0018c60:	a90c462a 	stmdbge	ip, {r1, r3, r5, r9, sl, lr}
d0018c64:	f7f74620 			; <UNDEFINED> instruction: 0xf7f74620
d0018c68:	4605fe7a 			; <UNDEFINED> instruction: 0x4605fe7a
d0018c6c:	d0362800 	eorsle	r2, r6, r0, lsl #16
d0018c70:	46204601 	strtmi	r4, [r0], -r1, lsl #12
d0018c74:	f856f7fe 			; <UNDEFINED> instruction: 0xf856f7fe
d0018c78:	3047f895 	umaalcc	pc, r7, r5, r8	; <UNPREDICTABLE>
d0018c7c:	d03d2b07 	eorsle	r2, sp, r7, lsl #22
d0018c80:	2a011f5a 	bcs	0xd00609f0
d0018c84:	2b10d93d 	blcs	0xd044f180
d0018c88:	f04fbf08 			; <UNDEFINED> instruction: 0xf04fbf08
d0018c8c:	465d0b01 	ldrbmi	r0, [sp], -r1, lsl #22
d0018c90:	2492f504 	ldrcs	pc, [r2], #1284	; 0x504
d0018c94:	f8d44628 			; <UNDEFINED> instruction: 0xf8d44628
d0018c98:	3b013244 	blcc	0xd00655b0
d0018c9c:	3244f8c4 	subcc	pc, r4, #196, 16	; 0xc40000
d0018ca0:	2f2ee291 	svccs	0x002ee291
d0018ca4:	f105ab1c 			; <UNDEFINED> instruction: 0xf105ab1c
d0018ca8:	a80c0601 	stmdage	ip, {r0, r9, sl}
d0018cac:	bf18442b 	svclt	0x0018442b
d0018cb0:	ee18222d 	cdp	2, 1, cr2, cr8, cr13, {1}
d0018cb4:	bf1c1a10 	svclt	0x001c1a10
d0018cb8:	2c40f803 	mcrrcs	8, 0, pc, r0, cr3	; <UNPREDICTABLE>
d0018cbc:	4652ab1c 			; <UNDEFINED> instruction: 0x4652ab1c
d0018cc0:	f803bf0f 			; <UNDEFINED> instruction: 0xf803bf0f
d0018cc4:	18f67c40 	ldmne	r6!, {r6, sl, fp, ip, sp, lr}^
d0018cc8:	f806233e 			; <UNDEFINED> instruction: 0xf806233e
d0018ccc:	bf183c40 	svclt	0x00183c40
d0018cd0:	44301cae 	ldrtmi	r1, [r0], #-3246	; 0xfffff352
d0018cd4:	050aeb06 	streq	lr, [sl, #-2822]	; 0xfffff4fa
d0018cd8:	fca8f008 	stc2	0, cr15, [r8], #32
d0018cdc:	6da3e77e 	stcvs	7, cr14, [r3, #504]!	; 0x1f8
d0018ce0:	d1d42b00 	bicsle	r2, r4, r0, lsl #22
d0018ce4:	3940f8df 	stmdbcc	r0, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d0018ce8:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0018cec:	9b073816 	blls	0xd01e6d4c
d0018cf0:	9b086623 	blls	0xd0232584
d0018cf4:	9b066663 	blls	0xd01b2688
d0018cf8:	e7c866a3 	strb	r6, [r8, r3, lsr #13]
d0018cfc:	0b02f04f 	bleq	0xd00d4e40
d0018d00:	f04fe7c5 			; <UNDEFINED> instruction: 0xf04fe7c5
d0018d04:	e7c20b01 	strb	r0, [r2, r1, lsl #22]
d0018d08:	46202128 	strtmi	r2, [r0], -r8, lsr #2
d0018d0c:	f8fcf7fa 			; <UNDEFINED> instruction: 0xf8fcf7fa
d0018d10:	b3184605 	tstlt	r8, #5242880	; 0x500000
d0018d14:	46524649 	ldrbmi	r4, [r2], -r9, asr #12
d0018d18:	f7f74620 			; <UNDEFINED> instruction: 0xf7f74620
d0018d1c:	1e01fd59 	mcrne	13, 0, pc, cr1, cr9, {2}	; <UNPREDICTABLE>
d0018d20:	2330db0f 	teqcs	r0, #15360	; 0x3c00
d0018d24:	4301fb03 	movwmi	pc, #6915	; 0x1b03	; <UNPREDICTABLE>
d0018d28:	2390f503 	orrscs	pc, r0, #12582912	; 0xc00000
d0018d2c:	3659f893 			; <UNDEFINED> instruction: 0x3659f893
d0018d30:	d1062b0c 	tstle	r6, ip, lsl #22
d0018d34:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0018d38:	4605fad9 			; <UNDEFINED> instruction: 0x4605fad9
d0018d3c:	d1a72d04 			; <UNDEFINED> instruction: 0xd1a72d04
d0018d40:	9b06e0d9 	blls	0xd01d10ac
d0018d44:	46494652 			; <UNDEFINED> instruction: 0x46494652
d0018d48:	93024620 	movwls	r4, #9760	; 0x2620
d0018d4c:	93019b08 	movwls	r9, #6920	; 0x1b08
d0018d50:	93009b07 	movwls	r9, #2823	; 0xb07
d0018d54:	f7fe4643 			; <UNDEFINED> instruction: 0xf7fe4643
d0018d58:	e7eefdb9 			; <UNDEFINED> instruction: 0xe7eefdb9
d0018d5c:	f46f6ae7 	vld1.64	{d22-d23}, [pc :128], r7
d0018d60:	183b7091 	ldmdane	fp!, {r0, r4, r7, ip, sp, lr}
d0018d64:	d80f2b01 	stmdale	pc, {r0, r8, r9, fp, sp}	; <UNPREDICTABLE>
d0018d68:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0018d6c:	2301f8ad 	movwcs	pc, #6317	; 0x18ad	; <UNPREDICTABLE>
d0018d70:	46494652 			; <UNDEFINED> instruction: 0x46494652
d0018d74:	9b069304 	blls	0xd01bd98c
d0018d78:	93029703 	movwls	r9, #9987	; 0x2703
d0018d7c:	93019b08 	movwls	r9, #6920	; 0x1b08
d0018d80:	93009b07 	movwls	r9, #2823	; 0xb07
d0018d84:	e6fa4643 	ldrbt	r4, [sl], r3, asr #12
d0018d88:	46494652 			; <UNDEFINED> instruction: 0x46494652
d0018d8c:	f7f74620 			; <UNDEFINED> instruction: 0xf7f74620
d0018d90:	4652fd1f 			; <UNDEFINED> instruction: 0x4652fd1f
d0018d94:	46494607 	strbmi	r4, [r9], -r7, lsl #12
d0018d98:	f7f74620 			; <UNDEFINED> instruction: 0xf7f74620
d0018d9c:	4683fdfe 			; <UNDEFINED> instruction: 0x4683fdfe
d0018da0:	6a01b120 	bvs	0xd0085228
d0018da4:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0018da8:	e771fab2 			; <UNDEFINED> instruction: 0xe771fab2
d0018dac:	f2c02f00 			; <UNDEFINED> instruction: 0xf2c02f00
d0018db0:	f04f810d 			; <UNDEFINED> instruction: 0xf04f810d
d0018db4:	fb0a0a30 	blx	0xd029b67e
d0018db8:	f50a4a07 			; <UNDEFINED> instruction: 0xf50a4a07
d0018dbc:	f89a2a90 			; <UNDEFINED> instruction: 0xf89a2a90
d0018dc0:	f1b99659 			; <UNDEFINED> instruction: 0xf1b99659
d0018dc4:	d0020f02 	andle	r0, r2, r2, lsl #30
d0018dc8:	0f04f1b9 	svceq	0x0004f1b9
d0018dcc:	6da3d10e 	stfvsd	f5, [r3, #56]!	; 0x38
d0018dd0:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0018dd4:	f8dfae89 			; <UNDEFINED> instruction: 0xf8dfae89
d0018dd8:	447b3854 	ldrbtmi	r3, [fp], #-2132	; 0xfffff7ac
d0018ddc:	3816e9c4 	ldmdacc	r6, {r2, r6, r7, r8, fp, sp, lr, pc}
d0018de0:	66239b07 	strtvs	r9, [r3], -r7, lsl #22
d0018de4:	66639b08 	strbtvs	r9, [r3], -r8, lsl #22
d0018de8:	e0e79b06 	rsc	r9, r7, r6, lsl #22
d0018dec:	0f0cf1b9 	svceq	0x000cf1b9
d0018df0:	462ad106 	strtmi	sp, [sl], -r6, lsl #2
d0018df4:	46204639 			; <UNDEFINED> instruction: 0x46204639
d0018df8:	feaaf7fb 	mcr2	7, 5, pc, cr10, cr11, {7}	; <UNPREDICTABLE>
d0018dfc:	e7472503 	strb	r2, [r7, -r3, lsl #10]
d0018e00:	0f13f1b9 	svceq	0x0013f1b9
d0018e04:	462ad106 	strtmi	sp, [sl], -r6, lsl #2
d0018e08:	46204639 			; <UNDEFINED> instruction: 0x46204639
d0018e0c:	fea0f7fb 	mcr2	7, 5, pc, cr0, cr11, {7}	; <UNPREDICTABLE>
d0018e10:	e73d2507 	ldr	r2, [sp, -r7, lsl #10]!
d0018e14:	0f12f1b9 	svceq	0x0012f1b9
d0018e18:	462ad10b 	strtmi	sp, [sl], -fp, lsl #2
d0018e1c:	46204639 			; <UNDEFINED> instruction: 0x46204639
d0018e20:	fe96f7fb 	mrc2	7, 4, pc, cr6, cr11, {7}
d0018e24:	365af89a 			; <UNDEFINED> instruction: 0x365af89a
d0018e28:	25059a09 	strcs	r9, [r5, #-2569]	; 0xfffff5f7
d0018e2c:	3248f8c2 	subcc	pc, r8, #12713984	; 0xc20000
d0018e30:	f1a9e72e 			; <UNDEFINED> instruction: 0xf1a9e72e
d0018e34:	2b01030d 	blcs	0xd0059a70
d0018e38:	f1b9d83d 			; <UNDEFINED> instruction: 0xf1b9d83d
d0018e3c:	d11e0f0d 	tstle	lr, sp, lsl #30
d0018e40:	46204639 			; <UNDEFINED> instruction: 0x46204639
d0018e44:	fd3ef7fc 	ldc2	7, cr15, [lr, #-1008]!	; 0xfffffc10
d0018e48:	4620212e 	strtmi	r2, [r0], -lr, lsr #2
d0018e4c:	f85cf7fa 			; <UNDEFINED> instruction: 0xf85cf7fa
d0018e50:	b1604605 	cmnlt	r0, r5, lsl #12
d0018e54:	23002030 	movwcs	r2, #48	; 0x30
d0018e58:	fb004632 	blx	0xd002a72a
d0018e5c:	f5074707 			; <UNDEFINED> instruction: 0xf5074707
d0018e60:	f8972790 			; <UNDEFINED> instruction: 0xf8972790
d0018e64:	4620165a 			; <UNDEFINED> instruction: 0x4620165a
d0018e68:	fac6f7ff 	blx	0xcf1d6e6c
d0018e6c:	6da3e68a 	stcvs	6, cr14, [r3, #552]!	; 0x228
d0018e70:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0018e74:	f8dfae39 			; <UNDEFINED> instruction: 0xf8dfae39
d0018e78:	447b37b8 	ldrbtmi	r3, [fp], #-1976	; 0xfffff848
d0018e7c:	2200e7ae 	andcs	lr, r0, #45613056	; 0x2b80000
d0018e80:	46204639 			; <UNDEFINED> instruction: 0x46204639
d0018e84:	fe64f7fb 	mcr2	7, 3, pc, cr4, cr11, {7}	; <UNPREDICTABLE>
d0018e88:	7191f44f 	orrsvc	pc, r1, pc, asr #8
d0018e8c:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0018e90:	4603f83b 			; <UNDEFINED> instruction: 0x4603f83b
d0018e94:	d1dd2800 	bicsle	r2, sp, r0, lsl #16
d0018e98:	2a5b6ae2 	bcs	0xd16f3a28
d0018e9c:	2230d1ae 	eorscs	sp, r0, #-2147483605	; 0x8000002b
d0018ea0:	4707fb02 	strmi	pc, [r7, -r2, lsl #22]
d0018ea4:	2790f507 	ldrcs	pc, [r0, r7, lsl #10]
d0018ea8:	f8974632 			; <UNDEFINED> instruction: 0xf8974632
d0018eac:	4620165a 			; <UNDEFINED> instruction: 0x4620165a
d0018eb0:	fab6f7fe 	blx	0xcedd6eb0
d0018eb4:	f1b9e666 			; <UNDEFINED> instruction: 0xf1b9e666
d0018eb8:	d1150f10 	tstle	r5, r0, lsl pc
d0018ebc:	46204639 			; <UNDEFINED> instruction: 0x46204639
d0018ec0:	fd00f7fc 	stc2	7, cr15, [r0, #-1008]	; 0xfffffc10
d0018ec4:	2b5b6ae3 	blcs	0xd16f3a58
d0018ec8:	2030d106 	eorscs	sp, r0, r6, lsl #2
d0018ecc:	fb002300 	blx	0xd0021ad6
d0018ed0:	f5074707 			; <UNDEFINED> instruction: 0xf5074707
d0018ed4:	e7e72790 			; <UNDEFINED> instruction: 0xe7e72790
d0018ed8:	2b006da3 	blcs	0xd003456c
d0018edc:	ae04f47f 	mcrge	4, 0, pc, cr4, cr15, {3}	; <UNPREDICTABLE>
d0018ee0:	3750f8df 	smmlscc	r0, pc, r8, pc	; <UNPREDICTABLE>
d0018ee4:	e779447b 			; <UNDEFINED> instruction: 0xe779447b
d0018ee8:	0f09f1b9 	svceq	0x0009f1b9
d0018eec:	4639d10a 	ldrtmi	sp, [r9], -sl, lsl #2
d0018ef0:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0018ef4:	6ae3fce7 	bvs	0xcf918298
d0018ef8:	f0402b5b 			; <UNDEFINED> instruction: 0xf0402b5b
d0018efc:	22008213 	andcs	r8, r0, #805306369	; 0x30000001
d0018f00:	e1b54631 			; <UNDEFINED> instruction: 0xe1b54631
d0018f04:	46392200 	ldrtmi	r2, [r9], -r0, lsl #4
d0018f08:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0018f0c:	f1b9fe21 			; <UNDEFINED> instruction: 0xf1b9fe21
d0018f10:	d1550f06 	cmple	r5, r6, lsl #30
d0018f14:	7191f44f 	orrsvc	pc, r1, pc, asr #8
d0018f18:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d0018f1c:	2800fff5 	stmdacs	r0, {r0, r2, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0018f20:	af6cf43f 	svcge	0x006cf43f
d0018f24:	f2406aa3 	vpmax.s8	d22, d16, d19
d0018f28:	f8df1101 			; <UNDEFINED> instruction: 0xf8df1101
d0018f2c:	4620270c 	strtmi	r2, [r0], -ip, lsl #14
d0018f30:	6b639306 	blvs	0xd18fdb50
d0018f34:	f8d4447a 			; <UNDEFINED> instruction: 0xf8d4447a
d0018f38:	f8949024 			; <UNDEFINED> instruction: 0xf8949024
d0018f3c:	93077030 	movwls	r7, #28720	; 0x7030
d0018f40:	ab06e9d4 	blge	0xd01d3698
d0018f44:	ffeef7f9 			; <UNDEFINED> instruction: 0xffeef7f9
d0018f48:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0018f4c:	f8dfadcd 			; <UNDEFINED> instruction: 0xf8dfadcd
d0018f50:	260086ec 	strcs	r8, [r0], -ip, ror #13
d0018f54:	f85844f8 			; <UNDEFINED> instruction: 0xf85844f8
d0018f58:	46592b04 	ldrbmi	r2, [r9], -r4, lsl #22
d0018f5c:	f7f74650 			; <UNDEFINED> instruction: 0xf7f74650
d0018f60:	4605fce9 	strmi	pc, [r5], -r9, ror #25
d0018f64:	f64fb1d0 			; <UNDEFINED> instruction: 0xf64fb1d0
d0018f68:	f64f03d0 			; <UNDEFINED> instruction: 0xf64f03d0
d0018f6c:	46200190 			; <UNDEFINED> instruction: 0x46200190
d0018f70:	bf182e01 	svclt	0x00182e01
d0018f74:	f7fb4619 			; <UNDEFINED> instruction: 0xf7fb4619
d0018f78:	f506fdcd 			; <UNDEFINED> instruction: 0xf506fdcd
d0018f7c:	4620430f 	strtmi	r4, [r0], -pc, lsl #6
d0018f80:	eb0433d0 	bl	0xd0125ec8
d0018f84:	88990343 	ldmhi	r9, {r0, r1, r6, r8, r9}
d0018f88:	fdc4f7fb 	stc2l	7, cr15, [r4, #1004]	; 0x3ec
d0018f8c:	f43f2e00 			; <UNDEFINED> instruction: 0xf43f2e00
d0018f90:	3e02adb9 	mcrcc	13, 0, sl, cr2, cr9, {5}
d0018f94:	f63f2e01 			; <UNDEFINED> instruction: 0xf63f2e01
d0018f98:	e5b3ada7 	ldr	sl, [r3, #3495]!	; 0xda7
d0018f9c:	2e083601 	cfmadd32cs	mvax0, mvfx3, mvfx8, mvfx1
d0018fa0:	6da3d1d9 	stfvsd	f5, [r3, #868]!	; 0x364
d0018fa4:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0018fa8:	f8dfad9f 			; <UNDEFINED> instruction: 0xf8dfad9f
d0018fac:	447b3694 	ldrbtmi	r3, [fp], #-1684	; 0xfffff96c
d0018fb0:	3916e9c4 	ldmdbcc	r6, {r2, r6, r7, r8, fp, sp, lr, pc}
d0018fb4:	e9c49b06 	stmib	r4, {r1, r2, r8, r9, fp, ip, pc}^
d0018fb8:	9b073718 	blls	0xd01e6c20
d0018fbc:	e66766a3 	strbt	r6, [r7], -r3, lsr #13
d0018fc0:	0f0af1b9 	svceq	0x000af1b9
d0018fc4:	f1b9d097 			; <UNDEFINED> instruction: 0xf1b9d097
d0018fc8:	e5aa0f01 	str	r0, [sl, #3841]!	; 0xf01
d0018fcc:	46494652 			; <UNDEFINED> instruction: 0x46494652
d0018fd0:	f7f74620 			; <UNDEFINED> instruction: 0xf7f74620
d0018fd4:	1e07fc1d 	mcrne	12, 0, pc, cr7, cr13, {0}	; <UNPREDICTABLE>
d0018fd8:	80bff2c0 	adcshi	pc, pc, r0, asr #5
d0018fdc:	093cf04f 	ldmdbeq	ip!, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d0018fe0:	4907fb09 	stmdbmi	r7, {r0, r3, r8, r9, fp, ip, sp, lr, pc}
d0018fe4:	395ff509 	ldmdbcc	pc, {r0, r3, r8, sl, ip, sp, lr, pc}^	; <UNPREDICTABLE>
d0018fe8:	a3ecf899 	mvnge	pc, #10027008	; 0x990000
d0018fec:	0f07f1ba 	svceq	0x0007f1ba
d0018ff0:	f8dfd163 			; <UNDEFINED> instruction: 0xf8dfd163
d0018ff4:	215b2650 	cmpcs	fp, r0, asr r6
d0018ff8:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d0018ffc:	ff92f7f9 			; <UNDEFINED> instruction: 0xff92f7f9
d0019000:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0019004:	2201ad71 	andcs	sl, r1, #7232	; 0x1c40
d0019008:	46114620 	ldrmi	r4, [r1], -r0, lsr #12
d001900c:	f914f7fd 			; <UNDEFINED> instruction: 0xf914f7fd
d0019010:	2634f8df 			; <UNDEFINED> instruction: 0x2634f8df
d0019014:	4620215d 			; <UNDEFINED> instruction: 0x4620215d
d0019018:	f7f9447a 			; <UNDEFINED> instruction: 0xf7f9447a
d001901c:	2800ff83 	stmdacs	r0, {r0, r1, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0019020:	ad62f43f 	cfstrdge	mvd15, [r2, #-252]!	; 0xffffff04
d0019024:	2101463a 	tstcs	r1, sl, lsr r6
d0019028:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d001902c:	6ae7fddb 	bvs	0xcfa187a0
d0019030:	f0002f3d 			; <UNDEFINED> instruction: 0xf0002f3d
d0019034:	f46f8267 	vld1.16	{d24-d27}, [pc :128], r7
d0019038:	187b7192 	ldmdane	fp!, {r1, r4, r7, r8, ip, sp, lr}^
d001903c:	f2402b01 	vqdmulh.s<illegal width 8>	d18, d0, d1
d0019040:	f46f8261 	vld1.16	{d24-d27}, [pc :128], r1
d0019044:	18bb7294 	ldmne	fp!, {r2, r4, r7, r9, ip, sp, lr}
d0019048:	f2402b04 	vqdmulh.s<illegal width 8>	d18, d0, d4
d001904c:	f645825b 			; <UNDEFINED> instruction: 0xf645825b
d0019050:	46204108 	strtmi	r4, [r0], -r8, lsl #2
d0019054:	fd5ef7fb 	ldc2l	7, cr15, [lr, #-1004]	; 0xfffffc14
d0019058:	f641e61a 			; <UNDEFINED> instruction: 0xf641e61a
d001905c:	46200108 	strtmi	r0, [r0], -r8, lsl #2
d0019060:	fd58f7fb 	ldc2l	7, cr15, [r8, #-1004]	; 0xfffffc14
d0019064:	4106f64b 	tstmi	r6, fp, asr #12	; <UNPREDICTABLE>
d0019068:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d001906c:	f247fd53 	vmla.f32	<illegal reg q15.5>, <illegal reg q3.5>, <illegal reg q1.5>
d0019070:	46200108 	strtmi	r0, [r0], -r8, lsl #2
d0019074:	f7fb2502 			; <UNDEFINED> instruction: 0xf7fb2502
d0019078:	e609fd4d 	str	pc, [r9], -sp, asr #26
d001907c:	2108f641 	tstcs	r8, r1, asr #12	; <UNPREDICTABLE>
d0019080:	f244e7ed 	vabd.s8	q15, q10, <illegal reg q14.5>
d0019084:	e7ea0108 	strb	r0, [sl, r8, lsl #2]!
d0019088:	3108f244 	tstcc	r8, r4, asr #4	; <UNPREDICTABLE>
d001908c:	f244e7e7 	vabd.s8	q15, q10, <illegal reg q11.5>
d0019090:	e7e40148 	strb	r0, [r4, r8, asr #2]!
d0019094:	6102f244 	tstvs	r2, r4, asr #4	; <UNPREDICTABLE>
d0019098:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d001909c:	f244fd3b 	vmla.f32	d31, d4, d27
d00190a0:	46206108 	strtmi	r6, [r0], -r8, lsl #2
d00190a4:	fd36f7fb 	ldc2	7, cr15, [r6, #-1004]!	; 0xfffffc14
d00190a8:	0190f244 	orrseq	pc, r0, r4, asr #4
d00190ac:	1310f244 	tstne	r0, #68, 4	; 0x40000004	; <UNPREDICTABLE>
d00190b0:	7f96f5b7 	svcvc	0x0096f5b7
d00190b4:	4619bf18 	sadd16mi	fp, r9, r8
d00190b8:	f1bae7d1 			; <UNDEFINED> instruction: 0xf1bae7d1
d00190bc:	463a0f0f 	ldrtmi	r0, [sl], -pc, lsl #30
d00190c0:	0101f04f 	tsteq	r1, pc, asr #32	; <UNPREDICTABLE>
d00190c4:	d1194620 	tstle	r9, r0, lsr #12
d00190c8:	fd8cf7fb 	stc2	7, cr15, [ip, #1004]	; 0x3ec
d00190cc:	6108f244 	tstvs	r8, r4, asr #4	; <UNPREDICTABLE>
d00190d0:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d00190d4:	212efd1f 	msrcs	CPSR_fsx, pc, lsl sp
d00190d8:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d00190dc:	4605ff15 			; <UNDEFINED> instruction: 0x4605ff15
d00190e0:	465bb120 	ldrbmi	fp, [fp], -r0, lsr #2
d00190e4:	f8994632 			; <UNDEFINED> instruction: 0xf8994632
d00190e8:	e6bc13ee 	ldrt	r1, [ip], lr, ror #7
d00190ec:	2b006da3 	blcs	0xd0034780
d00190f0:	acfaf47f 	cfldrdge	mvd15, [sl], #508	; 0x1fc
d00190f4:	3554f8df 	ldrbcc	pc, [r4, #-2271]	; 0xfffff721	; <UNPREDICTABLE>
d00190f8:	e66f447b 			; <UNDEFINED> instruction: 0xe66f447b
d00190fc:	0f11f1ba 	svceq	0x0011f1ba
d0019100:	f7fbd116 			; <UNDEFINED> instruction: 0xf7fbd116
d0019104:	f244fd6f 	vadd.f32	<illegal reg q15.5>, q2, <illegal reg q15.5>
d0019108:	46206108 	strtmi	r6, [r0], -r8, lsl #2
d001910c:	fd02f7fb 	stc2	7, cr15, [r2, #-1004]	; 0xfffffc14
d0019110:	2b5b6ae3 	blcs	0xd16f3ca4
d0019114:	462bd104 	strtmi	sp, [fp], -r4, lsl #2
d0019118:	f8994632 			; <UNDEFINED> instruction: 0xf8994632
d001911c:	e6c613ee 	strb	r1, [r6], lr, ror #7
d0019120:	2b006da3 	blcs	0xd00347b4
d0019124:	ace0f47f 	cfstrdge	mvd15, [r0], #508	; 0x1fc
d0019128:	3524f8df 	strcc	pc, [r4, #-2271]!	; 0xfffff721
d001912c:	e655447b 			; <UNDEFINED> instruction: 0xe655447b
d0019130:	0f08f1ba 	svceq	0x0008f1ba
d0019134:	f7fbd107 			; <UNDEFINED> instruction: 0xf7fbd107
d0019138:	f244fd55 	vmla.f32	<illegal reg q15.5>, q2, <illegal reg q2.5>
d001913c:	46206108 	strtmi	r6, [r0], -r8, lsl #2
d0019140:	fce8f7fb 	stc2l	7, cr15, [r8], #1004	; 0x3ec
d0019144:	f7fbe6d7 			; <UNDEFINED> instruction: 0xf7fbe6d7
d0019148:	f646fd4d 			; <UNDEFINED> instruction: 0xf646fd4d
d001914c:	46200108 	strtmi	r0, [r0], -r8, lsl #2
d0019150:	fce0f7fb 	stc2l	7, cr15, [r0], #1004	; 0x3ec
d0019154:	0f01f1ba 	svceq	0x0001f1ba
d0019158:	f8dfe4e3 			; <UNDEFINED> instruction: 0xf8dfe4e3
d001915c:	465124f8 			; <UNDEFINED> instruction: 0x465124f8
d0019160:	447a4648 	ldrbtmi	r4, [sl], #-1608	; 0xfffff9b8
d0019164:	fbe6f7f7 	blx	0xcf9d714a
d0019168:	b1204605 			; <UNDEFINED> instruction: 0xb1204605
d001916c:	46204659 			; <UNDEFINED> instruction: 0x46204659
d0019170:	f8cdf7fc 			; <UNDEFINED> instruction: 0xf8cdf7fc
d0019174:	6da3e642 	stcvs	6, cr14, [r3, #264]!	; 0x108
d0019178:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001917c:	f8dfacb5 			; <UNDEFINED> instruction: 0xf8dfacb5
d0019180:	447b34d8 	ldrbtmi	r3, [fp], #-1240	; 0xfffffb28
d0019184:	2126e62a 			; <UNDEFINED> instruction: 0x2126e62a
d0019188:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d001918c:	2800febd 	stmdacs	r0, {r0, r2, r3, r4, r5, r7, r9, sl, fp, ip, sp, lr, pc}
d0019190:	80a5f000 	adchi	pc, r5, r0
d0019194:	24c4f8df 	strbcs	pc, [r4], #2271	; 0x8df	; <UNPREDICTABLE>
d0019198:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d001919c:	6a674620 	bvs	0xd19eaa24
d00191a0:	f8d4447a 			; <UNDEFINED> instruction: 0xf8d4447a
d00191a4:	f8948028 			; <UNDEFINED> instruction: 0xf8948028
d00191a8:	f8d49030 			; <UNDEFINED> instruction: 0xf8d49030
d00191ac:	e9d4a034 	ldmib	r4, {r2, r4, r5, sp, pc}^
d00191b0:	f7f96b06 			; <UNDEFINED> instruction: 0xf7f96b06
d00191b4:	b958feb7 	ldmdblt	r8, {r0, r1, r2, r4, r5, r7, r9, sl, fp, ip, sp, lr, pc}^
d00191b8:	9a099b09 	bls	0xd027fde4
d00191bc:	3244f8d3 	subcc	pc, r4, #13828096	; 0xd30000
d00191c0:	f8c23b01 			; <UNDEFINED> instruction: 0xf8c23b01
d00191c4:	b01d3244 	andslt	r3, sp, r4, asr #4
d00191c8:	8b02ecbd 	blhi	0xd00d44c4
d00191cc:	8ff0e8bd 	svchi	0x00f0e8bd
d00191d0:	465a4631 			; <UNDEFINED> instruction: 0x465a4631
d00191d4:	f7f74620 			; <UNDEFINED> instruction: 0xf7f74620
d00191d8:	1e01fafb 			; <UNDEFINED> instruction: 0x1e01fafb
d00191dc:	81d8f280 	bicshi	pc, r8, r0, lsl #5
d00191e0:	4631465a 			; <UNDEFINED> instruction: 0x4631465a
d00191e4:	f7f74620 			; <UNDEFINED> instruction: 0xf7f74620
d00191e8:	1e02fb13 	vmovne.32	d2[0], pc
d00191ec:	263cdb70 			; <UNDEFINED> instruction: 0x263cdb70
d00191f0:	4602fb06 	strmi	pc, [r2], -r6, lsl #22
d00191f4:	365ff506 	ldrbcc	pc, [pc], -r6, lsl #10	; <UNPREDICTABLE>
d00191f8:	b3f0f896 	mvnslt	pc, #9830400	; 0x960000
d00191fc:	0f00f1bb 	svceq	0x0000f1bb
d0019200:	81e7f000 	mvnhi	pc, r0
d0019204:	2b006da3 	blcs	0xd0034898
d0019208:	ac6ef47f 	cfstrdge	mvd15, [lr], #-508	; 0xfffffe04
d001920c:	3450f8df 	ldrbcc	pc, [r0], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d0019210:	f8c4447b 			; <UNDEFINED> instruction: 0xf8c4447b
d0019214:	e9c4a068 	stmib	r4, {r3, r5, r6, sp, pc}^
d0019218:	e9c43716 	stmib	r4, {r1, r2, r4, r8, r9, sl, ip, sp}^
d001921c:	e5378918 	ldr	r8, [r7, #-2328]!	; 0xfffff6e8
d0019220:	d1052b0e 	tstle	r5, lr, lsl #22
d0019224:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0019228:	f896fb4d 			; <UNDEFINED> instruction: 0xf896fb4d
d001922c:	e5fb365a 	ldrb	r3, [fp, #1626]!	; 0x65a
d0019230:	2b09b15b 	blcs	0xd02857a4
d0019234:	2b0ad009 	blcs	0xd02cd260
d0019238:	6ae3d14a 	bvs	0xcf90d768
d001923c:	d1432b5b 	cmple	r3, fp, asr fp
d0019240:	4620465a 			; <UNDEFINED> instruction: 0x4620465a
d0019244:	fc84f7fb 	stc2	7, cr15, [r4], {251}	; 0xfb
d0019248:	4620e032 			; <UNDEFINED> instruction: 0x4620e032
d001924c:	f7fc9106 			; <UNDEFINED> instruction: 0xf7fc9106
d0019250:	2030fb39 	eorscs	pc, r0, r9, lsr fp	; <UNPREDICTABLE>
d0019254:	6ae39906 	bvs	0xcf8ff674
d0019258:	4101fb00 	tstmi	r1, r0, lsl #22	; <UNPREDICTABLE>
d001925c:	f5012b5b 			; <UNDEFINED> instruction: 0xf5012b5b
d0019260:	f8912190 			; <UNDEFINED> instruction: 0xf8912190
d0019264:	d1073659 	tstle	r7, r9, asr r6
d0019268:	d15b2b09 	cmple	fp, r9, lsl #22
d001926c:	21002201 	tstcs	r0, r1, lsl #4
d0019270:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0019274:	e485fb33 	str	pc, [r5], #2867	; 0xb33
d0019278:	d1532b09 	cmple	r3, r9, lsl #22
d001927c:	2b006da3 	blcs	0xd0034910
d0019280:	ac32f47f 	cfldrsge	mvf15, [r2], #-508	; 0xfffffe04
d0019284:	447b4bf7 	ldrbtmi	r4, [fp], #-3063	; 0xfffff409
d0019288:	f011e7c3 			; <UNDEFINED> instruction: 0xf011e7c3
d001928c:	d11f0bf7 			; <UNDEFINED> instruction: 0xd11f0bf7
d0019290:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d0019294:	fca6f7fb 	stc2	7, cr15, [r6], #1004	; 0x3ec
d0019298:	6108f244 	tstvs	r8, r4, asr #4	; <UNPREDICTABLE>
d001929c:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d00192a0:	6ae3fc39 	bvs	0xcf91838c
d00192a4:	f8962b5b 			; <UNDEFINED> instruction: 0xf8962b5b
d00192a8:	d10433ec 	smlattle	r4, ip, r3, r3
d00192ac:	d1392b08 	teqle	r9, r8, lsl #22
d00192b0:	46592201 	ldrbmi	r2, [r9], -r1, lsl #4
d00192b4:	2b08e7dc 	blcs	0xd025322c
d00192b8:	6da3d134 	stfvsd	f5, [r3, #208]!	; 0xd0
d00192bc:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d00192c0:	4be9ac13 	blmi	0xcfa84314
d00192c4:	e7a4447b 			; <UNDEFINED> instruction: 0xe7a4447b
d00192c8:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d00192cc:	e59ffafb 	ldr	pc, [pc, #2811]	; 0xd0019dcf
d00192d0:	2b006da3 	blcs	0xd0034964
d00192d4:	ac08f47f 	cfstrsge	mvf15, [r8], {127}	; 0x7f
d00192d8:	447b4be4 	ldrbtmi	r4, [fp], #-3044	; 0xfffff41c
d00192dc:	212ae799 			; <UNDEFINED> instruction: 0x212ae799
d00192e0:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d00192e4:	2800fe11 	stmdacs	r0, {r0, r4, r9, sl, fp, ip, sp, lr, pc}
d00192e8:	2100d061 	tstcs	r0, r1, rrx
d00192ec:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d00192f0:	2807fbd3 	stmdacs	r7, {r0, r1, r4, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d00192f4:	d1174605 	tstle	r7, r5, lsl #12
d00192f8:	213db17e 	teqcs	sp, lr, ror r1
d00192fc:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d0019300:	b150fe03 	cmplt	r0, r3, lsl #28	; <UNPREDICTABLE>
d0019304:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d0019308:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d001930c:	2204fc03 	andcs	pc, r4, #768	; 0x300
d0019310:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d0019314:	ff90f7fc 			; <UNDEFINED> instruction: 0xff90f7fc
d0019318:	f44fe01a 	vst4.8	{d30-d33}, [pc :64], sl
d001931c:	462041d0 			; <UNDEFINED> instruction: 0x462041d0
d0019320:	fbf8f7fb 	blx	0xcfe57316
d0019324:	e4b32504 	ldrt	r2, [r3], #1284	; 0x504
d0019328:	d1222805 			; <UNDEFINED> instruction: 0xd1222805
d001932c:	f8d39b09 			; <UNDEFINED> instruction: 0xf8d39b09
d0019330:	b1ae5248 			; <UNDEFINED> instruction: 0xb1ae5248
d0019334:	4620213d 			; <UNDEFINED> instruction: 0x4620213d
d0019338:	fde6f7f9 	stc2l	7, cr15, [r6, #996]!	; 0x3e4
d001933c:	f24bb180 	vrhadd.s8	d27, d27, d0
d0019340:	46204103 	strtmi	r4, [r0], -r3, lsl #2
d0019344:	fbe6f7fb 	blx	0xcf9d733a
d0019348:	46204629 	strtmi	r4, [r0], -r9, lsr #12
d001934c:	fd9af7fe 	ldc2	7, cr15, [sl, #1016]	; 0x3f8
d0019350:	4106f64b 	tstmi	r6, fp, asr #12	; <UNPREDICTABLE>
d0019354:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0019358:	f246fbdd 	vpadd.i8	<illegal reg q15.5>, q11, <illegal reg q6.5>
d001935c:	e6880108 	str	r0, [r8], r8, lsl #2
d0019360:	41d0f44f 	bicsmi	pc, r0, pc, asr #8
d0019364:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0019368:	9b09fbd5 	blls	0xd02982c4
d001936c:	5248f8c3 	subpl	pc, r8, #12779520	; 0xc30000
d0019370:	2804e544 	stmdacs	r4, {r2, r6, r8, sl, sp, lr, pc}
d0019374:	6da3d006 	stcvs	0, cr13, [r3, #24]!
d0019378:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001937c:	4bbcac89 	blmi	0xcef445a8
d0019380:	e52b447b 	str	r4, [fp, #-1147]!	; 0xfffffb85
d0019384:	213db166 	teqcs	sp, r6, ror #2
d0019388:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d001938c:	b138fdbd 	teqlt	r8, sp	; <illegal shifter operand>	; <UNPREDICTABLE>
d0019390:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d0019394:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0019398:	2201fbbd 	andcs	pc, r1, #193536	; 0x2f400
d001939c:	e7b84611 			; <UNDEFINED> instruction: 0xe7b84611
d00193a0:	41d0f44f 	bicsmi	pc, r0, pc, asr #8
d00193a4:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d00193a8:	f7fffbb5 			; <UNDEFINED> instruction: 0xf7fffbb5
d00193ac:	2128bb9d 			; <UNDEFINED> instruction: 0x2128bb9d
d00193b0:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d00193b4:	2800fda9 	stmdacs	r0, {r0, r3, r5, r7, r8, sl, fp, ip, sp, lr, pc}
d00193b8:	6ae3d052 	bvs	0xcf90d508
d00193bc:	d1322b2a 	teqle	r2, sl, lsr #22
d00193c0:	f2406ce2 	sha1c.32	q11, q8, q9
d00193c4:	429a1301 	addsmi	r1, sl, #67108864	; 0x4000000
d00193c8:	6be2d12d 	blvs	0xcf8cd884
d00193cc:	6ba14620 	blvs	0xce86ac54
d00193d0:	f9fef7f7 			; <UNDEFINED> instruction: 0xf9fef7f7
d00193d4:	db261e05 	blle	0xd09a0bf0
d00193d8:	fb032330 	blx	0xd00e20a2
d00193dc:	f5034305 			; <UNDEFINED> instruction: 0xf5034305
d00193e0:	f8932390 			; <UNDEFINED> instruction: 0xf8932390
d00193e4:	2b0c3659 	blcs	0xd0326d50
d00193e8:	4620d11d 			; <UNDEFINED> instruction: 0x4620d11d
d00193ec:	fd6cf7f9 	stc2l	7, cr15, [ip, #-996]!	; 0xfffffc1c
d00193f0:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d00193f4:	4a9ffd69 	bmi	0xce8189a0
d00193f8:	46202129 	strtmi	r2, [r0], -r9, lsr #2
d00193fc:	f7f9447a 			; <UNDEFINED> instruction: 0xf7f9447a
d0019400:	2800fd91 	stmdacs	r0, {r0, r4, r7, r8, sl, fp, ip, sp, lr, pc}
d0019404:	ab70f43f 	blge	0xd1c56508
d0019408:	21284a9b 			; <UNDEFINED> instruction: 0x21284a9b
d001940c:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d0019410:	fd88f7f9 	stc2	7, cr15, [r8, #996]	; 0x3e4
d0019414:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0019418:	4629ab67 	strtmi	sl, [r9], -r7, ror #22
d001941c:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0019420:	f7ffff65 			; <UNDEFINED> instruction: 0xf7ffff65
d0019424:	2200bbaf 	andcs	fp, r0, #179200	; 0x2bc00
d0019428:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d001942c:	ff04f7fc 			; <UNDEFINED> instruction: 0xff04f7fc
d0019430:	46054a92 			; <UNDEFINED> instruction: 0x46054a92
d0019434:	447a2129 	ldrbtmi	r2, [sl], #-297	; 0xfffffed7
d0019438:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d001943c:	2d03fd73 	stccs	13, cr15, [r3, #-460]	; 0xfffffe34
d0019440:	ac7cf47f 	cfldrdge	mvd15, [ip], #-508	; 0xfffffe04
d0019444:	7191f44f 	orrsvc	pc, r1, pc, asr #8
d0019448:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d001944c:	2800fd5d 	stmdacs	r0, {r0, r2, r3, r4, r6, r8, sl, fp, ip, sp, lr, pc}
d0019450:	acd4f43f 	cfldrdge	mvd15, [r4], {63}	; 0x3f
d0019454:	23009909 	movwcs	r9, #2313	; 0x909
d0019458:	f8d14632 			; <UNDEFINED> instruction: 0xf8d14632
d001945c:	e5021248 	str	r1, [r2, #-584]	; 0xfffffdb8
d0019460:	4620212b 	strtmi	r2, [r0], -fp, lsr #2
d0019464:	fd50f7f9 	ldc2l	7, cr15, [r0, #-996]	; 0xfffffc1c
d0019468:	2100b168 	tstcs	r0, r8, ror #2
d001946c:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0019470:	2802fb13 	stmdacs	r2, {r0, r1, r4, r8, r9, fp, ip, sp, lr, pc}
d0019474:	d1204605 			; <UNDEFINED> instruction: 0xd1204605
d0019478:	2b006da3 	blcs	0xd0034b0c
d001947c:	ac08f47f 	cfstrsge	mvf15, [r8], {127}	; 0x7f
d0019480:	447b4b7f 	ldrbtmi	r4, [fp], #-2943	; 0xfffff481
d0019484:	212de4aa 			; <UNDEFINED> instruction: 0x212de4aa
d0019488:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d001948c:	2800fd3d 	stmdacs	r0, {r0, r2, r3, r4, r5, r8, sl, fp, ip, sp, lr, pc}
d0019490:	2121d1eb 			; <UNDEFINED> instruction: 0x2121d1eb
d0019494:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d0019498:	2800fd37 	stmdacs	r0, {r0, r1, r2, r4, r5, r8, sl, fp, ip, sp, lr, pc}
d001949c:	217ed1e5 	cmncs	lr, r5, ror #3
d00194a0:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d00194a4:	4605fd31 			; <UNDEFINED> instruction: 0x4605fd31
d00194a8:	d1de2800 	bicsle	r2, lr, r0, lsl #16
d00194ac:	46204975 			; <UNDEFINED> instruction: 0x46204975
d00194b0:	f7f64479 			; <UNDEFINED> instruction: 0xf7f64479
d00194b4:	f7fffedd 			; <UNDEFINED> instruction: 0xf7fffedd
d00194b8:	2803bbeb 	stmdacs	r3, {r0, r1, r3, r5, r6, r7, r8, r9, fp, ip, sp, pc}
d00194bc:	2f21d108 	svccs	0x0021d108
d00194c0:	6da3d013 	stcvs	0, cr13, [r3, #76]!	; 0x4c
d00194c4:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d00194c8:	4b6fac99 	blmi	0xd1c04734
d00194cc:	e485447b 	str	r4, [r5], #1147	; 0x47b
d00194d0:	d1022f2d 	tstle	r2, sp, lsr #30
d00194d4:	2140f244 	cmpcs	r0, r4, asr #4	; <UNPREDICTABLE>
d00194d8:	2f7ee5bb 	svccs	0x007ee5bb
d00194dc:	f244d102 	vrhadd.s8	d29, d4, d2
d00194e0:	e5b631c0 	ldr	r3, [r6, #448]!	; 0x1c0
d00194e4:	f47f2f21 			; <UNDEFINED> instruction: 0xf47f2f21
d00194e8:	4620abd3 			; <UNDEFINED> instruction: 0x4620abd3
d00194ec:	5120f44f 	msrpl	CPSR_, pc, asr #8
d00194f0:	fb10f7fb 	blx	0xd04574e6
d00194f4:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d00194f8:	fbd7f7fb 	blx	0xcf6174ee
d00194fc:	baf4f7ff 	blt	0xcfd57500
d0019500:	e6602000 	strbt	r2, [r0], -r0
d0019504:	f43f2e00 			; <UNDEFINED> instruction: 0xf43f2e00
d0019508:	4620ada2 	strtmi	sl, [r0], -r2, lsr #27
d001950c:	fcdcf7f9 	ldc2l	7, cr15, [ip], {249}	; 0xf9
d0019510:	0108f641 	tsteq	r8, r1, asr #12	; <UNPREDICTABLE>
d0019514:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0019518:	f24bfafd 	vpmin.s8	<illegal reg q15.5>, <illegal reg q13.5>, <illegal reg q14.5>
d001951c:	46204103 	strtmi	r4, [r0], -r3, lsl #2
d0019520:	faf8f7fb 	blx	0xcfe57514
d0019524:	d0092f3d 	andle	r2, r9, sp, lsr pc
d0019528:	41f0f44f 	mvnsmi	pc, pc, asr #8
d001952c:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0019530:	f24bfaf1 	vpmin.s8	<illegal reg q15.5>, <illegal reg q13.5>, <illegal reg q8.5>
d0019534:	46204103 	strtmi	r4, [r0], -r3, lsl #2
d0019538:	faecf7fb 	blx	0xcfb5752c
d001953c:	46202201 	strtmi	r2, [r0], -r1, lsl #4
d0019540:	f7fc4611 			; <UNDEFINED> instruction: 0xf7fc4611
d0019544:	2f3dfe79 	svccs	0x003dfe79
d0019548:	ad8cf43f 	cfstrsge	mvf15, [ip, #252]	; 0xfc
d001954c:	4106f64b 	tstmi	r6, fp, asr #12	; <UNPREDICTABLE>
d0019550:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0019554:	f46ffadf 	vld1.64	{d31-d32}, [pc :64]
d0019558:	18fb7392 	ldmne	fp!, {r1, r4, r7, r8, r9, ip, sp, lr}^
d001955c:	f63f2b08 			; <UNDEFINED> instruction: 0xf63f2b08
d0019560:	a202ad81 	andge	sl, r2, #8256	; 0x2040
d0019564:	3023f852 	eorcc	pc, r3, r2, asr r8	; <UNPREDICTABLE>
d0019568:	4710441a 			; <UNDEFINED> instruction: 0x4710441a
d001956c:	fffffaef 			; <UNDEFINED> instruction: 0xfffffaef
d0019570:	fffffb11 			; <UNDEFINED> instruction: 0xfffffb11
d0019574:	fffffaf9 			; <UNDEFINED> instruction: 0xfffffaf9
d0019578:	fffffaf9 			; <UNDEFINED> instruction: 0xfffffaf9
d001957c:	fffffb17 			; <UNDEFINED> instruction: 0xfffffb17
d0019580:	fffffb1d 			; <UNDEFINED> instruction: 0xfffffb1d
d0019584:	fffffb23 			; <UNDEFINED> instruction: 0xfffffb23
d0019588:	fffffb29 			; <UNDEFINED> instruction: 0xfffffb29
d001958c:	fffffb29 			; <UNDEFINED> instruction: 0xfffffb29
d0019590:	fb062630 	blx	0xd01a2e5a
d0019594:	f5064601 			; <UNDEFINED> instruction: 0xf5064601
d0019598:	f8962690 			; <UNDEFINED> instruction: 0xf8962690
d001959c:	f1bbb664 			; <UNDEFINED> instruction: 0xf1bbb664
d00195a0:	f47f0f00 			; <UNDEFINED> instruction: 0xf47f0f00
d00195a4:	f896ae2f 			; <UNDEFINED> instruction: 0xf896ae2f
d00195a8:	2b0d3659 	blcs	0xd0366f14
d00195ac:	ae38f47f 	mrcge	4, 1, APSR_nzcv, cr8, cr15, {3}
d00195b0:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d00195b4:	4a35f987 	bmi	0xd0d97bd8
d00195b8:	4620212e 	strtmi	r2, [r0], -lr, lsr #2
d00195bc:	f7f9447a 			; <UNDEFINED> instruction: 0xf7f9447a
d00195c0:	2800fcb1 	stmdacs	r0, {r0, r4, r5, r7, sl, fp, ip, sp, lr, pc}
d00195c4:	aa90f43f 	bge	0xce4566c8
d00195c8:	465a2301 	ldrbmi	r2, [sl], -r1, lsl #6
d00195cc:	165af896 			; <UNDEFINED> instruction: 0x165af896
d00195d0:	f896e449 			; <UNDEFINED> instruction: 0xf896e449
d00195d4:	290f13ec 	stmdbcs	pc, {r2, r3, r5, r6, r7, r8, r9, ip}	; <UNPREDICTABLE>
d00195d8:	ae57f47f 	mrcge	4, 2, APSR_nzcv, cr7, cr15, {3}
d00195dc:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d00195e0:	fb00f7fb 	blx	0xd00575d6
d00195e4:	6108f244 	tstvs	r8, r4, asr #4	; <UNPREDICTABLE>
d00195e8:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d00195ec:	4a28fa93 	bmi	0xd0a58040
d00195f0:	4620212e 	strtmi	r2, [r0], -lr, lsr #2
d00195f4:	f7f9447a 			; <UNDEFINED> instruction: 0xf7f9447a
d00195f8:	2800fc95 	stmdacs	r0, {r0, r2, r4, r7, sl, fp, ip, sp, lr, pc}
d00195fc:	aa74f43f 	bge	0xd1d56700
d0019600:	465a2301 	ldrbmi	r2, [sl], -r1, lsl #6
d0019604:	13eef896 	mvnne	pc, #9830400	; 0x960000
d0019608:	bf00e42d 	svclt	0x0000e42d
d001960c:	ffffd540 			; <UNDEFINED> instruction: 0xffffd540
d0019610:	fffffbdc 			; <UNDEFINED> instruction: 0xfffffbdc
d0019614:	fffffb9b 			; <UNDEFINED> instruction: 0xfffffb9b
d0019618:	fffffb7f 			; <UNDEFINED> instruction: 0xfffffb7f
d001961c:	fffffb77 			; <UNDEFINED> instruction: 0xfffffb77
d0019620:	fffffb39 			; <UNDEFINED> instruction: 0xfffffb39
d0019624:	fffffb44 			; <UNDEFINED> instruction: 0xfffffb44
d0019628:	fffffad3 			; <UNDEFINED> instruction: 0xfffffad3
d001962c:	fffff9fc 			; <UNDEFINED> instruction: 0xfffff9fc
d0019630:	fffff995 			; <UNDEFINED> instruction: 0xfffff995
d0019634:	fffff949 			; <UNDEFINED> instruction: 0xfffff949
d0019638:	fffff922 			; <UNDEFINED> instruction: 0xfffff922
d001963c:	00009fa8 	andeq	r9, r0, r8, lsr #31
d0019640:	fffff8cb 			; <UNDEFINED> instruction: 0xfffff8cb
d0019644:	fffff89a 			; <UNDEFINED> instruction: 0xfffff89a
d0019648:	fffff8a8 			; <UNDEFINED> instruction: 0xfffff8a8
d001964c:	fffff717 			; <UNDEFINED> instruction: 0xfffff717
d0019650:	fffff701 			; <UNDEFINED> instruction: 0xfffff701
d0019654:	ffffc1b0 			; <UNDEFINED> instruction: 0xffffc1b0
d0019658:	fffff762 			; <UNDEFINED> instruction: 0xfffff762
d001965c:	fffff765 			; <UNDEFINED> instruction: 0xfffff765
d0019660:	fffff711 			; <UNDEFINED> instruction: 0xfffff711
d0019664:	fffff6fc 			; <UNDEFINED> instruction: 0xfffff6fc
d0019668:	fffff6be 			; <UNDEFINED> instruction: 0xfffff6be
d001966c:	fffff6d7 			; <UNDEFINED> instruction: 0xfffff6d7
d0019670:	fffff667 			; <UNDEFINED> instruction: 0xfffff667
d0019674:	fffff61e 			; <UNDEFINED> instruction: 0xfffff61e
d0019678:	fffff633 			; <UNDEFINED> instruction: 0xfffff633
d001967c:	fffff632 			; <UNDEFINED> instruction: 0xfffff632
d0019680:	ffffcbc8 			; <UNDEFINED> instruction: 0xffffcbc8
d0019684:	fffff5c5 			; <UNDEFINED> instruction: 0xfffff5c5
d0019688:	ffffcba4 			; <UNDEFINED> instruction: 0xffffcba4
d001968c:	fffff39b 			; <UNDEFINED> instruction: 0xfffff39b
d0019690:	fffff363 			; <UNDEFINED> instruction: 0xfffff363

Disassembly of section .text.condition.constprop.0:

d00196d0 <.text.condition.constprop.0>:
d00196d0:	4c0ab510 	cfstr32mi	mvfx11, [sl], {16}
d00196d4:	4a0a2128 	bmi	0xd02a1b7c
d00196d8:	447a447c 	ldrbtmi	r4, [sl], #-1148	; 0xfffffb84
d00196dc:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d00196e0:	2202fc21 	andcs	pc, r2, #8448	; 0x2100
d00196e4:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d00196e8:	fda6f7fc 	stc2	7, cr15, [r6, #1008]!	; 0x3f0
d00196ec:	46204a05 	strtmi	r4, [r0], -r5, lsl #20
d00196f0:	447a2129 	ldrbtmi	r2, [sl], #-297	; 0xfffffed7
d00196f4:	4010e8bd 			; <UNDEFINED> instruction: 0x4010e8bd
d00196f8:	bc14f7f9 	ldclt	7, cr15, [r4], {249}	; 0xf9
d00196fc:	0000eaec 	andeq	lr, r0, ip, ror #21
d0019700:	ffffffb6 			; <UNDEFINED> instruction: 0xffffffb6
d0019704:	ffffffbc 			; <UNDEFINED> instruction: 0xffffffbc

Disassembly of section .text.simple_expression.constprop.0:

d00198a8 <.text.simple_expression.constprop.0>:
d00198a8:	3434f8df 	ldrtcc	pc, [r4], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d00198ac:	6cdb447b 	cfldrdvs	mvd4, [fp], {123}	; 0x7b
d00198b0:	e92d2b3d 	push	{r0, r2, r3, r4, r5, r8, r9, fp, sp}
d00198b4:	b0854ff0 	strdlt	r4, [r5], r0
d00198b8:	f46fd01f 	vld4.8	{d29-d32}, [pc :64]
d00198bc:	191a7492 	ldmdbne	sl, {r1, r4, r7, sl, ip, sp, lr}
d00198c0:	d91a2a01 	ldmdble	sl, {r0, r9, fp, sp}
d00198c4:	7094f46f 	addsvc	pc, r4, pc, ror #8
d00198c8:	2b044403 	blcs	0xd012a8dc
d00198cc:	2300bf8c 	movwcs	fp, #3980	; 0xf8c
d00198d0:	f8df2301 			; <UNDEFINED> instruction: 0xf8df2301
d00198d4:	93004410 	movwls	r4, #1040	; 0x410
d00198d8:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d00198dc:	6ae2447c 	bvs	0xcf8aaad4
d00198e0:	d101429a 			; <UNDEFINED> instruction: 0xd101429a
d00198e4:	b9539b00 	ldmdblt	r3, {r8, r9, fp, ip, pc}^
d00198e8:	220348ff 	andcs	r4, r3, #16711680	; 0xff0000
d00198ec:	44782101 	ldrbtmi	r2, [r8], #-257	; 0xfffffeff
d00198f0:	e8bdb005 	pop	{r0, r2, ip, sp, pc}
d00198f4:	f7fc4ff0 			; <UNDEFINED> instruction: 0xf7fc4ff0
d00198f8:	2301bc9f 	movwcs	fp, #7327	; 0x1c9f
d00198fc:	e9d4e7e9 	ldmib	r4, {r0, r3, r5, r6, r7, r8, r9, sl, sp, lr, pc}^
d0019900:	6b631206 	blvs	0xd18de120
d0019904:	92024620 	andls	r4, r2, #32, 12	; 0x2000000
d0019908:	91019303 	tstls	r1, r3, lsl #6
d001990c:	f8d46a67 			; <UNDEFINED> instruction: 0xf8d46a67
d0019910:	f8948028 			; <UNDEFINED> instruction: 0xf8948028
d0019914:	f7f69030 			; <UNDEFINED> instruction: 0xf7f69030
d0019918:	a901ff5b 	stmdbge	r1, {r0, r1, r3, r4, r6, r8, r9, sl, fp, ip, sp, lr, pc}
d001991c:	c90e1e05 	stmdbgt	lr, {r0, r2, r9, sl, fp, ip}
d0019920:	81cff280 	bichi	pc, pc, r0, lsl #5
d0019924:	93014620 	movwls	r4, #5664	; 0x1620
d0019928:	ff72f7f6 			; <UNDEFINED> instruction: 0xff72f7f6
d001992c:	0a00f1b0 	beq	0xd0055ff4
d0019930:	db159b01 	blle	0xd058053c
d0019934:	fb02223c 	blx	0xd00a222e
d0019938:	f504440a 			; <UNDEFINED> instruction: 0xf504440a
d001993c:	f894345f 			; <UNDEFINED> instruction: 0xf894345f
d0019940:	b1ba23f0 			; <UNDEFINED> instruction: 0xb1ba23f0
d0019944:	447a4ae9 	ldrbtmi	r4, [sl], #-2793	; 0xfffff517
d0019948:	b9316d91 	ldmdblt	r1!, {r0, r4, r7, r8, sl, fp, sp, lr}
d001994c:	447949e8 	ldrbtmi	r4, [r9], #-2536	; 0xfffff618
d0019950:	e9c26693 	stmib	r2, {r0, r1, r4, r7, r9, sl, sp, lr}^
d0019954:	e9c21716 	stmib	r2, {r1, r2, r4, r8, r9, sl, ip}^
d0019958:	b0058918 	andlt	r8, r5, r8, lsl r9
d001995c:	8ff0e8bd 	svchi	0x00f0e8bd
d0019960:	2a006da2 	bcs	0xd0034ff0
d0019964:	4ae3d1f9 	bmi	0xcf90e150
d0019968:	e9c4447a 	stmib	r4, {r1, r3, r4, r5, r6, sl, lr}^
d001996c:	e9c42716 	stmib	r4, {r1, r2, r4, r8, r9, sl, sp}^
d0019970:	e01a8918 	ands	r8, sl, r8, lsl r9
d0019974:	63ecf894 	mvnvs	pc, #148, 16	; 0x940000
d0019978:	0202f026 	andeq	pc, r2, #38	; 0x26
d001997c:	d15c2a0d 	cmple	ip, sp, lsl #20
d0019980:	93004cdd 	movwls	r4, #3293	; 0xcdd
d0019984:	4620447c 			; <UNDEFINED> instruction: 0x4620447c
d0019988:	fa9ef7f9 	blx	0xce7d7974
d001998c:	4620213d 			; <UNDEFINED> instruction: 0x4620213d
d0019990:	fabaf7f9 	blx	0xceed797c
d0019994:	6da2b958 			; <UNDEFINED> instruction: 0x6da2b958
d0019998:	d1de2a00 	bicsle	r2, lr, r0, lsl #20
d001999c:	9b004ad7 	blls	0xd002c500
d00199a0:	e9c4447a 	stmib	r4, {r1, r3, r4, r5, r6, sl, lr}^
d00199a4:	e9c48918 	stmib	r4, {r3, r4, r8, fp, pc}^
d00199a8:	66a32716 	ssatvs	r2, #4, r6, lsl #14
d00199ac:	2d00e7d5 	stccs	7, cr14, [r0, #-852]	; 0xfffffcac
d00199b0:	bfac48d3 	svclt	0x00ac48d3
d00199b4:	233c2330 	teqcs	ip, #48, 6	; 0xc0000000
d00199b8:	bfaa4478 	svclt	0x00aa4478
d00199bc:	4405fb03 	strmi	pc, [r5], #-2819	; 0xfffff4fd
d00199c0:	440afb03 	strmi	pc, [sl], #-2819	; 0xfffff4fd
d00199c4:	2490f504 	ldrcs	pc, [r0], #1284	; 0x504
d00199c8:	bfb69000 	svclt	0x00b69000
d00199cc:	345ff504 	ldrbcc	pc, [pc], #-1284	; 0xd00199d4	; <UNPREDICTABLE>
d00199d0:	465af894 			; <UNDEFINED> instruction: 0x465af894
d00199d4:	43eef894 	mvnmi	pc, #148, 16	; 0x940000
d00199d8:	f7fd4621 			; <UNDEFINED> instruction: 0xf7fd4621
d00199dc:	9800fdfd 	stmdals	r0, {r0, r2, r3, r4, r5, r6, r7, r8, sl, fp, ip, sp, lr, pc}
d00199e0:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d00199e4:	f896f7fb 			; <UNDEFINED> instruction: 0xf896f7fb
d00199e8:	98002d00 	stmdals	r0, {r8, sl, fp, sp}
d00199ec:	4629db1a 			; <UNDEFINED> instruction: 0x4629db1a
d00199f0:	ff68f7fb 			; <UNDEFINED> instruction: 0xff68f7fb
d00199f4:	f24448c3 	vadd.i8	q10, q10, <illegal reg q1.5>
d00199f8:	44786101 	ldrbtmi	r6, [r8], #-257	; 0xfffffeff
d00199fc:	f7fb4605 			; <UNDEFINED> instruction: 0xf7fb4605
d0019a00:	f64bf889 			; <UNDEFINED> instruction: 0xf64bf889
d0019a04:	46284105 	strtmi	r4, [r8], -r5, lsl #2
d0019a08:	f884f7fb 			; <UNDEFINED> instruction: 0xf884f7fb
d0019a0c:	701af44f 	andsvc	pc, sl, pc, asr #8
d0019a10:	5004fb00 	andpl	pc, r4, r0, lsl #22
d0019a14:	3068f500 	rsbcc	pc, r8, r0, lsl #10
d0019a18:	b0058d00 	andlt	r8, r5, r0, lsl #26
d0019a1c:	4ff0e8bd 	svcmi	0x00f0e8bd
d0019a20:	bbf8f7fb 	bllt	0xcfe57a14
d0019a24:	21014652 	tstcs	r1, r2, asr r6
d0019a28:	f7fb9000 			; <UNDEFINED> instruction: 0xf7fb9000
d0019a2c:	f244f8db 	vtst.8	<illegal reg q15.5>, q10, <illegal reg q5.5>
d0019a30:	98006108 	stmdals	r0, {r3, r8, sp, lr}
d0019a34:	f86ef7fb 			; <UNDEFINED> instruction: 0xf86ef7fb
d0019a38:	1ff2e7dc 	svcne	0x00f2e7dc
d0019a3c:	d9032a02 	stmdble	r3, {r1, r9, fp, sp}
d0019a40:	0210f1a6 	andseq	pc, r0, #-2147483607	; 0x80000029
d0019a44:	d8072a01 	stmdale	r7, {r0, r9, fp, sp}
d0019a48:	447a4aaf 	ldrbtmi	r4, [sl], #-2735	; 0xfffff551
d0019a4c:	29006d91 	stmdbcs	r0, {r0, r4, r7, r8, sl, fp, sp, lr}
d0019a50:	49aed183 	stmibmi	lr!, {r0, r1, r7, r8, ip, lr, pc}
d0019a54:	e77b4479 			; <UNDEFINED> instruction: 0xe77b4479
d0019a58:	29091eb1 	stmdbcs	r9, {r0, r4, r5, r7, r9, sl, fp, ip}
d0019a5c:	f240d80d 	vadd.i8	d29, d0, d13
d0019a60:	40ca2215 	sbcmi	r2, sl, r5, lsl r2
d0019a64:	d50807d1 	strle	r0, [r8, #-2001]	; 0xfffff82f
d0019a68:	447a4aa9 	ldrbtmi	r4, [sl], #-2729	; 0xfffff557
d0019a6c:	29006d91 	stmdbcs	r0, {r0, r4, r7, r8, sl, fp, sp, lr}
d0019a70:	af73f47f 	svcge	0x0073f47f
d0019a74:	447949a7 	ldrbtmi	r4, [r9], #-2471	; 0xfffff659
d0019a78:	4ca7e76a 	stcmi	7, cr14, [r7], #424	; 0x1a8
d0019a7c:	447c9301 	ldrbtmi	r9, [ip], #-769	; 0xfffffcff
d0019a80:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d0019a84:	4620fa21 	strtmi	pc, [r0], -r1, lsr #20
d0019a88:	b02cf8d4 	ldrdlt	pc, [ip], -r4	; <UNPREDICTABLE>
d0019a8c:	fa1cf7f9 	blx	0xd0757a78
d0019a90:	9b012e0c 	blls	0xd00652c8
d0019a94:	f1bbd11a 			; <UNDEFINED> instruction: 0xf1bbd11a
d0019a98:	d0060f3d 	andle	r0, r6, sp, lsr pc
d0019a9c:	2a006da2 	bcs	0xd003512c
d0019aa0:	af5bf47f 	svcge	0x005bf47f
d0019aa4:	447a4a9d 	ldrbtmi	r4, [sl], #-2717	; 0xfffff563
d0019aa8:	2030e75f 	eorscs	lr, r0, pc, asr r7
d0019aac:	4005fb00 	andmi	pc, r5, r0, lsl #22
d0019ab0:	2090f500 	addscs	pc, r0, r0, lsl #10
d0019ab4:	605bf200 	subsvs	pc, fp, r0, lsl #4
d0019ab8:	fcacf7fb 	stc2	7, cr15, [ip], #1004	; 0x3ec
d0019abc:	46292200 	strtmi	r2, [r9], -r0, lsl #4
d0019ac0:	b0054620 	andlt	r4, r5, r0, lsr #12
d0019ac4:	4ff0e8bd 	svcmi	0x00f0e8bd
d0019ac8:	b85df7fb 	ldmdalt	sp, {r0, r1, r3, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}^
d0019acc:	d10d2e13 	tstle	sp, r3, lsl lr
d0019ad0:	0f3df1bb 	svceq	0x003df1bb
d0019ad4:	6da2d006 	stcvs	0, cr13, [r2, #24]!
d0019ad8:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0019adc:	4a90af3e 	bmi	0xce4457dc
d0019ae0:	e742447a 	smlsldx	r4, r2, sl, r4
d0019ae4:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0019ae8:	e7e7ff33 			; <UNDEFINED> instruction: 0xe7e7ff33
d0019aec:	d1142e12 	tstle	r4, r2, lsl lr
d0019af0:	0f3df1bb 	svceq	0x003df1bb
d0019af4:	6da2d006 	stcvs	0, cr13, [r2, #24]!
d0019af8:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0019afc:	4a89af2e 	bmi	0xce2857bc
d0019b00:	e732447a 			; <UNDEFINED> instruction: 0xe732447a
d0019b04:	46202330 			; <UNDEFINED> instruction: 0x46202330
d0019b08:	4305fb03 	movwmi	pc, #23299	; 0x5b03	; <UNPREDICTABLE>
d0019b0c:	2390f503 	orrscs	pc, r0, #12582912	; 0xc00000
d0019b10:	165af893 			; <UNDEFINED> instruction: 0x165af893
d0019b14:	f9bcf7fc 			; <UNDEFINED> instruction: 0xf9bcf7fc
d0019b18:	2e0ee7d0 	mcrcs	7, 0, lr, cr14, cr0, {6}
d0019b1c:	f1bbd114 			; <UNDEFINED> instruction: 0xf1bbd114
d0019b20:	d0060f3d 	andle	r0, r6, sp, lsr pc
d0019b24:	2a006da2 	bcs	0xd00351b4
d0019b28:	af17f47f 	svcge	0x0017f47f
d0019b2c:	447a4a7e 	ldrbtmi	r4, [sl], #-2686	; 0xfffff582
d0019b30:	2330e71b 	teqcs	r0, #7077888	; 0x6c0000
d0019b34:	fb034620 	blx	0xd00eb3be
d0019b38:	f5034305 			; <UNDEFINED> instruction: 0xf5034305
d0019b3c:	f8932390 			; <UNDEFINED> instruction: 0xf8932390
d0019b40:	f7fe165a 			; <UNDEFINED> instruction: 0xf7fe165a
d0019b44:	e7b9f99f 			; <UNDEFINED> instruction: 0xe7b9f99f
d0019b48:	0f3df1bb 	svceq	0x003df1bb
d0019b4c:	80b3f000 	adcshi	pc, r3, r0
d0019b50:	d10b2e0a 	tstle	fp, sl, lsl #28
d0019b54:	7292f46f 	addsvc	pc, r2, #1862270976	; 0x6f000000
d0019b58:	2a01445a 	bcs	0xd006acc8
d0019b5c:	6da2d906 			; <UNDEFINED> instruction: 0x6da2d906
d0019b60:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0019b64:	4a71aefa 	bmi	0xd1c85754
d0019b68:	e6fe447a 	uxtah	r4, lr, sl, ror #8
d0019b6c:	db2d2d00 	blle	0xd0b64f74
d0019b70:	2200486f 	andcs	r4, r0, #7274496	; 0x6f0000
d0019b74:	44784629 	ldrbtmi	r4, [r8], #-1577	; 0xfffff9d7
d0019b78:	ffeaf7fa 			; <UNDEFINED> instruction: 0xffeaf7fa
d0019b7c:	f24b486d 	vadd.i8	q10, <illegal reg q5.5>, <illegal reg q14.5>
d0019b80:	44784103 	ldrbtmi	r4, [r8], #-259	; 0xfffffefd
d0019b84:	ffc6f7fa 			; <UNDEFINED> instruction: 0xffc6f7fa
d0019b88:	21014f6b 	tstcs	r1, fp, ror #30
d0019b8c:	447f9a00 	ldrbtmi	r9, [pc], #-2560	; 0xd0019b94
d0019b90:	f7fc4638 			; <UNDEFINED> instruction: 0xf7fc4638
d0019b94:	f1bbfb51 			; <UNDEFINED> instruction: 0xf1bbfb51
d0019b98:	d02a0f3d 	eorle	r0, sl, sp, lsr pc
d0019b9c:	4106f64b 	tstmi	r6, fp, asr #12	; <UNPREDICTABLE>
d0019ba0:	f7fa4638 			; <UNDEFINED> instruction: 0xf7fa4638
d0019ba4:	f46fffb7 			; <UNDEFINED> instruction: 0xf46fffb7
d0019ba8:	2e0a7392 	mcrcs	3, 0, r7, cr10, cr2, {4}
d0019bac:	0403eb0b 	streq	lr, [r3], #-2827	; 0xfffff4f5
d0019bb0:	2180d12e 	orrcs	sp, r0, lr, lsr #2
d0019bb4:	f7fa4638 			; <UNDEFINED> instruction: 0xf7fa4638
d0019bb8:	2c08ffad 	stccs	15, cr15, [r8], {173}	; 0xad
d0019bbc:	e8dfd821 	ldm	pc, {r0, r5, fp, ip, lr, pc}^	; <UNPREDICTABLE>
d0019bc0:	4112f004 	tstmi	r2, r4	; <UNPREDICTABLE>
d0019bc4:	4b462020 	blmi	0xd11a1c4c
d0019bc8:	00555550 	subseq	r5, r5, r0, asr r5
d0019bcc:	4652485b 			; <UNDEFINED> instruction: 0x4652485b
d0019bd0:	44782101 	ldrbtmi	r2, [r8], #-257	; 0xfffffeff
d0019bd4:	f7fb9001 			; <UNDEFINED> instruction: 0xf7fb9001
d0019bd8:	f646f805 			; <UNDEFINED> instruction: 0xf646f805
d0019bdc:	98010108 	stmdals	r1, {r3, r8}
d0019be0:	ff98f7fa 			; <UNDEFINED> instruction: 0xff98f7fa
d0019be4:	4856e7ca 	ldmdami	r6, {r1, r3, r6, r7, r8, r9, sl, sp, lr, pc}^
d0019be8:	0108f641 	tsteq	r8, r1, asr #12	; <UNPREDICTABLE>
d0019bec:	f7fa4478 			; <UNDEFINED> instruction: 0xf7fa4478
d0019bf0:	2e05ff91 	mcrcs	15, 0, pc, cr5, cr1, {4}	; <UNPREDICTABLE>
d0019bf4:	4853d105 	ldmdami	r3, {r0, r2, r8, ip, lr, pc}^
d0019bf8:	21c0f24b 	biccs	pc, r0, fp, asr #4
d0019bfc:	f7fa4478 			; <UNDEFINED> instruction: 0xf7fa4478
d0019c00:	2d00ff89 	stccs	15, cr15, [r0, #-548]	; 0xfffffddc
d0019c04:	4850db48 	ldmdami	r0, {r3, r6, r8, r9, fp, ip, lr, pc}^
d0019c08:	46292200 	strtmi	r2, [r9], -r0, lsl #4
d0019c0c:	e7584478 			; <UNDEFINED> instruction: 0xe7584478
d0019c10:	d8ee2c08 	stmiale	lr!, {r3, sl, fp, sp}^
d0019c14:	f853a302 			; <UNDEFINED> instruction: 0xf853a302
d0019c18:	44132024 	ldrmi	r2, [r3], #-36	; 0xffffffdc
d0019c1c:	bf004718 	svclt	0x00004718
d0019c20:	ffffffc7 			; <UNDEFINED> instruction: 0xffffffc7
d0019c24:	00000025 	andeq	r0, r0, r5, lsr #32
d0019c28:	ffffffd3 			; <UNDEFINED> instruction: 0xffffffd3
d0019c2c:	ffffffd3 			; <UNDEFINED> instruction: 0xffffffd3
d0019c30:	0000002f 	andeq	r0, r0, pc, lsr #32
d0019c34:	00000039 	andeq	r0, r0, r9, lsr r0
d0019c38:	00000043 	andeq	r0, r0, r3, asr #32
d0019c3c:	0000004d 	andeq	r0, r0, sp, asr #32
d0019c40:	0000004d 	andeq	r0, r0, sp, asr #32
d0019c44:	f6414841 			; <UNDEFINED> instruction: 0xf6414841
d0019c48:	44782108 	ldrbtmi	r2, [r8], #-264	; 0xfffffef8
d0019c4c:	4840e7cf 	stmdami	r0, {r0, r1, r2, r3, r6, r7, r8, r9, sl, sp, lr, pc}^
d0019c50:	0108f244 	tsteq	r8, r4, asr #4	; <UNPREDICTABLE>
d0019c54:	e7ca4478 			; <UNDEFINED> instruction: 0xe7ca4478
d0019c58:	f244483e 	vtst.8	d20, d4, d30
d0019c5c:	44783108 	ldrbtmi	r3, [r8], #-264	; 0xfffffef8
d0019c60:	483de7c5 	ldmdami	sp!, {r0, r2, r6, r7, r8, r9, sl, sp, lr, pc}
d0019c64:	0148f244 	cmpeq	r8, r4, asr #4	; <UNPREDICTABLE>
d0019c68:	e7c04478 			; <UNDEFINED> instruction: 0xe7c04478
d0019c6c:	f244483b 	vtst.8	d20, d4, d27
d0019c70:	44786102 	ldrbtmi	r6, [r8], #-258	; 0xfffffefe
d0019c74:	f7fa9000 			; <UNDEFINED> instruction: 0xf7fa9000
d0019c78:	f244ff4d 	vmax.f32	<illegal reg q15.5>, q2, <illegal reg q6.5>
d0019c7c:	98006108 	stmdals	r0, {r3, r8, sp, lr}
d0019c80:	ff48f7fa 			; <UNDEFINED> instruction: 0xff48f7fa
d0019c84:	0190f244 	orrseq	pc, r0, r4, asr #4
d0019c88:	1310f244 	tstne	r0, #68, 4	; 0x40000004	; <UNPREDICTABLE>
d0019c8c:	f5bb9800 			; <UNDEFINED> instruction: 0xf5bb9800
d0019c90:	bf187f96 	svclt	0x00187f96
d0019c94:	e7aa4619 			; <UNDEFINED> instruction: 0xe7aa4619
d0019c98:	46524831 			; <UNDEFINED> instruction: 0x46524831
d0019c9c:	44782101 	ldrbtmi	r2, [r8], #-257	; 0xfffffeff
d0019ca0:	f7fa9000 			; <UNDEFINED> instruction: 0xf7fa9000
d0019ca4:	f246ff9f 	vrecps.f32	d31, d22, d15
d0019ca8:	98000108 	stmdals	r0, {r3, r8}
d0019cac:	e8bdb005 	pop	{r0, r2, ip, sp, pc}
d0019cb0:	f7fa4ff0 			; <UNDEFINED> instruction: 0xf7fa4ff0
d0019cb4:	2e0abf2f 	cdpcs	15, 0, cr11, cr10, cr15, {1}
d0019cb8:	bf089b00 	svclt	0x00089b00
d0019cbc:	93002304 	movwls	r2, #772	; 0x304
d0019cc0:	2230e762 	eorscs	lr, r0, #25690112	; 0x1880000
d0019cc4:	4405fb02 	strmi	pc, [r5], #-2818	; 0xfffff4fe
d0019cc8:	2490f504 	ldrcs	pc, [r0], #1284	; 0x504
d0019ccc:	2664f894 			; <UNDEFINED> instruction: 0x2664f894
d0019cd0:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0019cd4:	f894ae37 			; <UNDEFINED> instruction: 0xf894ae37
d0019cd8:	f04f6659 			; <UNDEFINED> instruction: 0xf04f6659
d0019cdc:	e64b3aff 			; <UNDEFINED> instruction: 0xe64b3aff
d0019ce0:	0000e918 	andeq	lr, r0, r8, lsl r9
d0019ce4:	0000e8e8 	andeq	lr, r0, r8, ror #17
d0019ce8:	0000e8d6 	ldrdeq	lr, [r0], -r6
d0019cec:	0000e87e 	andeq	lr, r0, lr, ror r8
d0019cf0:	fffffddb 			; <UNDEFINED> instruction: 0xfffffddb
d0019cf4:	fffffd9c 			; <UNDEFINED> instruction: 0xfffffd9c
d0019cf8:	0000e840 	andeq	lr, r0, r0, asr #16
d0019cfc:	fffffda9 			; <UNDEFINED> instruction: 0xfffffda9
d0019d00:	0000e80c 	andeq	lr, r0, ip, lsl #16
d0019d04:	0000e7ca 	andeq	lr, r0, sl, asr #15
d0019d08:	0000e77a 	andeq	lr, r0, sl, ror r7
d0019d0c:	fffffd17 			; <UNDEFINED> instruction: 0xfffffd17
d0019d10:	0000e75a 	andeq	lr, r0, sl, asr r7
d0019d14:	fffffd1b 			; <UNDEFINED> instruction: 0xfffffd1b
d0019d18:	0000e746 	andeq	lr, r0, r6, asr #14
d0019d1c:	fffffd17 			; <UNDEFINED> instruction: 0xfffffd17
d0019d20:	fffffd0e 			; <UNDEFINED> instruction: 0xfffffd0e
d0019d24:	fffffd15 			; <UNDEFINED> instruction: 0xfffffd15
d0019d28:	fffffd11 			; <UNDEFINED> instruction: 0xfffffd11
d0019d2c:	fffffd06 			; <UNDEFINED> instruction: 0xfffffd06
d0019d30:	0000e64e 	andeq	lr, r0, lr, asr #12
d0019d34:	0000e642 	andeq	lr, r0, r2, asr #12
d0019d38:	0000e636 	andeq	lr, r0, r6, lsr r6
d0019d3c:	0000e5f2 	strdeq	lr, [r0], -r2
d0019d40:	0000e5d8 	ldrdeq	lr, [r0], -r8
d0019d44:	0000e5c8 	andeq	lr, r0, r8, asr #11
d0019d48:	0000e5b8 			; <UNDEFINED> instruction: 0x0000e5b8
d0019d4c:	0000e57a 	andeq	lr, r0, sl, ror r5
d0019d50:	0000e570 	andeq	lr, r0, r0, ror r5
d0019d54:	0000e566 	andeq	lr, r0, r6, ror #10
d0019d58:	0000e55c 	andeq	lr, r0, ip, asr r5
d0019d5c:	0000e552 	andeq	lr, r0, r2, asr r5
d0019d60:	0000e526 	andeq	lr, r0, r6, lsr #10

Disassembly of section .text.finish_function_body.constprop.0:

d0019d64 <.text.finish_function_body.constprop.0>:
d0019d64:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d0019d68:	48264680 	stmdami	r6!, {r7, r9, sl, lr}
d0019d6c:	4478460e 	ldrbtmi	r4, [r8], #-1550	; 0xfffff9f2
d0019d70:	2390f500 	orrscs	pc, r0, #0, 10
d0019d74:	3634f893 			; <UNDEFINED> instruction: 0x3634f893
d0019d78:	d0022b01 	andle	r2, r2, r1, lsl #22
d0019d7c:	f7fb2100 			; <UNDEFINED> instruction: 0xf7fb2100
d0019d80:	4f21fac6 	svcmi	0x0021fac6
d0019d84:	f507447f 			; <UNDEFINED> instruction: 0xf507447f
d0019d88:	4638338f 	ldrtmi	r3, [r8], -pc, lsl #7
d0019d8c:	51b8f8d3 			; <UNDEFINED> instruction: 0x51b8f8d3
d0019d90:	2392f507 	orrscs	pc, r2, #29360128	; 0x1c00000
d0019d94:	423cf8d3 	eorsmi	pc, ip, #13828096	; 0xd30000
d0019d98:	f0243401 			; <UNDEFINED> instruction: 0xf0243401
d0019d9c:	fa1f0401 	blx	0xd07dada8
d0019da0:	f449f984 	vst2.32	{d31,d33}, [r9], r4
d0019da4:	f7fa4130 			; <UNDEFINED> instruction: 0xf7fa4130
d0019da8:	f64bfeb5 			; <UNDEFINED> instruction: 0xf64bfeb5
d0019dac:	46385180 	ldrtmi	r5, [r8], -r0, lsl #3
d0019db0:	feb0f7fa 	mrc2	7, 5, pc, cr0, cr10, {7}
d0019db4:	b9d36dbb 	ldmiblt	r3, {r0, r1, r3, r4, r5, r7, r8, sl, fp, sp, lr}^
d0019db8:	4130f449 	teqmi	r0, r9, asr #8	; <UNPREDICTABLE>
d0019dbc:	f0414640 			; <UNDEFINED> instruction: 0xf0414640
d0019dc0:	f7fa0180 			; <UNDEFINED> instruction: 0xf7fa0180
d0019dc4:	b12efe8b 	smlawblt	lr, fp, lr, pc	; <UNPREDICTABLE>
d0019dc8:	46303402 	ldrtmi	r3, [r0], -r2, lsl #8
d0019dcc:	b2a100a4 	adclt	r0, r1, #164	; 0xa4
d0019dd0:	fe84f7fa 	mcr2	7, 4, pc, cr4, cr10, {7}	; <UNPREDICTABLE>
d0019dd4:	27004c0d 	strcs	r4, [r0, -sp, lsl #24]
d0019dd8:	f504447c 			; <UNDEFINED> instruction: 0xf504447c
d0019ddc:	f504268e 			; <UNDEFINED> instruction: 0xf504268e
d0019de0:	f5062890 			; <UNDEFINED> instruction: 0xf5062890
d0019de4:	f8d866c6 			; <UNDEFINED> instruction: 0xf8d866c6
d0019de8:	429f3630 	addsmi	r3, pc, #48, 12	; 0x3000000
d0019dec:	e8bdd301 	pop	{r0, r8, r9, ip, lr, pc}
d0019df0:	230083f8 	movwcs	r8, #1016	; 0x3f8
d0019df4:	f856462a 			; <UNDEFINED> instruction: 0xf856462a
d0019df8:	37011b04 	strcc	r1, [r1, -r4, lsl #22]
d0019dfc:	f7fc6da0 			; <UNDEFINED> instruction: 0xf7fc6da0
d0019e00:	e7f0f905 	ldrb	pc, [r0, r5, lsl #18]!	; <UNPREDICTABLE>
d0019e04:	0000e456 	andeq	lr, r0, r6, asr r4
d0019e08:	0000e440 	andeq	lr, r0, r0, asr #8
d0019e0c:	0000e3ec 	andeq	lr, r0, ip, ror #7

Disassembly of section .text.initialize_scalar.constprop.0:

d0019e70 <.text.initialize_scalar.constprop.0>:
d0019e70:	4ff0e92d 	svcmi	0x00f0e92d
d0019e74:	4606b087 	strmi	fp, [r6], -r7, lsl #1
d0019e78:	9201460d 	andls	r4, r1, #13631488	; 0xd00000
d0019e7c:	4c39b971 			; <UNDEFINED> instruction: 0x4c39b971
d0019e80:	447c2201 	ldrbtmi	r2, [ip], #-513	; 0xfffffdff
d0019e84:	46204611 			; <UNDEFINED> instruction: 0x46204611
d0019e88:	f9d6f7fc 			; <UNDEFINED> instruction: 0xf9d6f7fc
d0019e8c:	4631462a 	ldrtmi	r4, [r1], -sl, lsr #12
d0019e90:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0019e94:	b007fe78 	andlt	pc, r7, r8, ror lr	; <UNPREDICTABLE>
d0019e98:	8ff0e8bd 	svchi	0x00f0e8bd
d0019e9c:	212d4c32 			; <UNDEFINED> instruction: 0x212d4c32
d0019ea0:	4620447c 			; <UNDEFINED> instruction: 0x4620447c
d0019ea4:	f830f7f9 			; <UNDEFINED> instruction: 0xf830f7f9
d0019ea8:	69e269a3 	stmibvs	r2!, {r0, r1, r5, r7, r8, fp, sp, lr}^
d0019eac:	718df44f 	orrvc	pc, sp, pc, asr #8
d0019eb0:	46209000 	strtmi	r9, [r0], -r0
d0019eb4:	92029303 	andls	r9, r2, #201326592	; 0xc000000
d0019eb8:	9030f894 	mlasls	r0, r4, r8, pc	; <UNPREDICTABLE>
d0019ebc:	8034f8d4 	ldrsbthi	pc, [r4], -r4	; <UNPREDICTABLE>
d0019ec0:	5b08e9d4 	blpl	0xd0254618
d0019ec4:	a70ae9d4 			; <UNDEFINED> instruction: 0xa70ae9d4
d0019ec8:	f81ef7f9 			; <UNDEFINED> instruction: 0xf81ef7f9
d0019ecc:	9b039a02 	blls	0xd01006dc
d0019ed0:	4620b190 			; <UNDEFINED> instruction: 0x4620b190
d0019ed4:	fdb8f7f9 	ldc2	7, cr15, [r8, #996]!	; 0x3e4
d0019ed8:	9b004605 	blls	0xd002b6f4
d0019edc:	426db103 	rsbmi	fp, sp, #-1073741824	; 0xc0000000
d0019ee0:	b35b9b01 	cmplt	fp, #1024	; 0x400
d0019ee4:	d9292dff 	stmdble	r9!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, sl, fp, sp}
d0019ee8:	447b4b20 	ldrbtmi	r4, [fp], #-2848	; 0xfffff4e0
d0019eec:	2a006d9a 	bcs	0xd003555c
d0019ef0:	4a1fd1d1 	bmi	0xd080e63c
d0019ef4:	e00f447a 	and	r4, pc, sl, ror r4	; <UNPREDICTABLE>
d0019ef8:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d0019efc:	d112428f 	tstle	r2, pc, lsl #5
d0019f00:	46204619 			; <UNDEFINED> instruction: 0x46204619
d0019f04:	fd49f7f6 	stc2l	7, cr15, [r9, #-984]	; 0xfffffc28
d0019f08:	4b1ab9b0 	blmi	0xd06c85d0
d0019f0c:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d0019f10:	d1c02a00 	bicle	r2, r0, r0, lsl #20
d0019f14:	447a4a18 	ldrbtmi	r4, [sl], #-2584	; 0xfffff5e8
d0019f18:	8068f8c3 	rsbhi	pc, r8, r3, asr #17
d0019f1c:	2b16e9c3 	blcs	0xd05d4630
d0019f20:	a918e9c3 	ldmdbge	r8, {r0, r1, r6, r7, r8, fp, sp, lr, pc}
d0019f24:	f5a7e7b7 			; <UNDEFINED> instruction: 0xf5a7e7b7
d0019f28:	2f017781 	svccs	0x00017781
d0019f2c:	4813d8ed 	ldmdami	r3, {r0, r2, r3, r5, r6, r7, fp, ip, lr, pc}
d0019f30:	f7f84478 			; <UNDEFINED> instruction: 0xf7f84478
d0019f34:	e7d0ffc9 	ldrb	pc, [r0, r9, asr #31]	; <UNPREDICTABLE>
d0019f38:	e7f86a05 	ldrb	r6, [r8, r5, lsl #20]!
d0019f3c:	95054b10 	strls	r4, [r5, #-2832]	; 0xfffff4f0
d0019f40:	f503447b 			; <UNDEFINED> instruction: 0xf503447b
d0019f44:	f8d3337f 			; <UNDEFINED> instruction: 0xf8d3337f
d0019f48:	44311224 	ldrtmi	r1, [r1], #-548	; 0xfffffddc
d0019f4c:	2201b115 	andcs	fp, r1, #1073741829	; 0x40000005
d0019f50:	2220f883 	eorcs	pc, r0, #8585216	; 0x830000
d0019f54:	aa052304 	bge	0xd0162b6c
d0019f58:	20010089 	andcs	r0, r1, r9, lsl #1
d0019f5c:	fd42f7fa 	stc2l	7, cr15, [r2, #-1000]	; 0xfffffc18
d0019f60:	bf00e799 	svclt	0x0000e799
d0019f64:	0000e342 	andeq	lr, r0, r2, asr #6
d0019f68:	0000e324 	andeq	lr, r0, r4, lsr #6
d0019f6c:	0000e2da 	ldrdeq	lr, [r0], -sl
d0019f70:	ffffff4f 			; <UNDEFINED> instruction: 0xffffff4f
d0019f74:	0000e2b8 			; <UNDEFINED> instruction: 0x0000e2b8
d0019f78:	fffffef6 			; <UNDEFINED> instruction: 0xfffffef6
d0019f7c:	0000e294 	muleq	r0, r4, r2
d0019f80:	0000e284 	andeq	lr, r0, r4, lsl #5

Disassembly of section .text.initialize_record.constprop.0:

d001a084 <.text.initialize_record.constprop.0>:
d001a084:	e92d2b21 	push	{r0, r5, r8, r9, fp, sp}
d001a088:	46064ff8 			; <UNDEFINED> instruction: 0x46064ff8
d001a08c:	4617468b 	ldrmi	r4, [r7], -fp, lsl #13
d001a090:	d107469a 			; <UNDEFINED> instruction: 0xd107469a
d001a094:	48554954 	ldmdami	r5, {r2, r4, r6, r8, fp, lr}^
d001a098:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d001a09c:	4ff8e8bd 	svcmi	0x00f8e8bd
d001a0a0:	b8e6f7f6 	stmialt	r6!, {r1, r2, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}^
d001a0a4:	217b4d52 	cmncs	fp, r2, asr sp
d001a0a8:	447d4a52 	ldrbtmi	r4, [sp], #-2642	; 0xfffff5ae
d001a0ac:	4628447a 			; <UNDEFINED> instruction: 0x4628447a
d001a0b0:	ff38f7f8 			; <UNDEFINED> instruction: 0xff38f7f8
d001a0b4:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d001a0b8:	f44f8094 	vst4.32	{d24-d27}, [pc :64], r4
d001a0bc:	f04f731a 			; <UNDEFINED> instruction: 0xf04f731a
d001a0c0:	435e0900 	cmpmi	lr, #0, 18
d001a0c4:	3467f506 	strbtcc	pc, [r7], #-1286	; 0xfffffafa	; <UNPREDICTABLE>
d001a0c8:	74f4f504 	ldrbtvc	pc, [r4], #1284	; 0x504	; <UNPREDICTABLE>
d001a0cc:	6dab442c 	cfstrsvs	mvf4, [fp, #176]!	; 0xb0
d001a0d0:	d1392b00 	teqle	r9, r0, lsl #22
d001a0d4:	2b7d6aeb 	blcs	0xd1f74c88
d001a0d8:	f5b3d036 			; <UNDEFINED> instruction: 0xf5b3d036
d001a0dc:	d0337f80 	eorsle	r7, r3, r0, lsl #31
d001a0e0:	f50219aa 			; <UNDEFINED> instruction: 0xf50219aa
d001a0e4:	f8923268 			; <UNDEFINED> instruction: 0xf8923268
d001a0e8:	4549102a 	strbmi	r1, [r9, #-42]	; 0xffffffd6
d001a0ec:	f892d905 			; <UNDEFINED> instruction: 0xf892d905
d001a0f0:	b13a202b 	teqlt	sl, fp, lsr #32
d001a0f4:	0f00f1b9 	svceq	0x0000f1b9
d001a0f8:	493fd004 	ldmdbmi	pc!, {r2, ip, lr, pc}	; <UNPREDICTABLE>
d001a0fc:	4479483f 	ldrbtmi	r4, [r9], #-2111	; 0xfffff7c1
d001a100:	e7cb4478 			; <UNDEFINED> instruction: 0xe7cb4478
d001a104:	8022f8b4 	strhthi	pc, [r2], -r4	; <UNPREDICTABLE>
d001a108:	2021f894 	mlacs	r1, r4, r8, pc	; <UNPREDICTABLE>
d001a10c:	0020f894 	mlaeq	r0, r4, r8, pc	; <UNPREDICTABLE>
d001a110:	2a0044d8 	bcs	0xd002b478
d001a114:	b38fd047 	orrlt	sp, pc, #71	; 0x47
d001a118:	80e4f8df 	ldrdhi	pc, [r4], #143	; 0x8f	; <UNPREDICTABLE>
d001a11c:	44f84a39 	ldrbtmi	r4, [r8], #2617	; 0xa39
d001a120:	e9d8447a 	ldmib	r8, {r1, r3, r4, r5, r6, sl, lr}^
d001a124:	f7f60106 			; <UNDEFINED> instruction: 0xf7f60106
d001a128:	b1b0fc05 	lslslt	pc, r5, #24	; <UNPREDICTABLE>
d001a12c:	44784836 	ldrbtmi	r4, [r8], #-2102	; 0xfffff7ca
d001a130:	fecaf7f8 	mcr2	7, 6, pc, cr10, cr8, {7}	; <UNPREDICTABLE>
d001a134:	212c4835 			; <UNDEFINED> instruction: 0x212c4835
d001a138:	0901f109 	stmdbeq	r1, {r0, r3, r8, ip, sp, lr, pc}
d001a13c:	44783424 	ldrbtmi	r3, [r8], #-1060	; 0xfffffbdc
d001a140:	fee2f7f8 	mcr2	7, 7, pc, cr2, cr8, {7}	; <UNPREDICTABLE>
d001a144:	d1c22800 	bicle	r2, r2, r0, lsl #16
d001a148:	217d4a31 	cmncs	sp, r1, lsr sl
d001a14c:	447a4831 	ldrbtmi	r4, [sl], #-2097	; 0xfffff7cf
d001a150:	e8bd4478 	pop	{r3, r4, r5, r6, sl, lr}
d001a154:	f7f84ff8 			; <UNDEFINED> instruction: 0xf7f84ff8
d001a158:	f8d8bee5 			; <UNDEFINED> instruction: 0xf8d8bee5
d001a15c:	f5a3302c 			; <UNDEFINED> instruction: 0xf5a3302c
d001a160:	2b017381 	blcs	0xd0076f6c
d001a164:	f8d8d803 			; <UNDEFINED> instruction: 0xf8d8d803
d001a168:	2b003020 	blcs	0xd00261f0
d001a16c:	492ad0de 	stmdbmi	sl!, {r1, r2, r3, r4, r6, r7, ip, lr, pc}
d001a170:	4479482a 	ldrbtmi	r4, [r9], #-2090	; 0xfffff7d6
d001a174:	f7f64478 			; <UNDEFINED> instruction: 0xf7f64478
d001a178:	e7dbf87b 			; <UNDEFINED> instruction: 0xe7dbf87b
d001a17c:	d10c28ff 	strdle	r2, [ip, -pc]
d001a180:	22044827 	andcs	r4, r4, #2555904	; 0x270000
d001a184:	44782101 	ldrbtmi	r2, [r8], #-257	; 0xfffffeff
d001a188:	f856f7fc 			; <UNDEFINED> instruction: 0xf856f7fc
d001a18c:	22004825 	andcs	r4, r0, #2424832	; 0x250000
d001a190:	44784641 	ldrbtmi	r4, [r8], #-1601	; 0xfffff9bf
d001a194:	fcf7f7fa 	ldc2l	7, cr15, [r7], #1000	; 0x3e8
d001a198:	4601e7cc 	strmi	lr, [r1], -ip, asr #15
d001a19c:	44784822 	ldrbtmi	r4, [r8], #-2082	; 0xfffff7de
d001a1a0:	fe70f7fd 	mrc2	7, 3, pc, cr0, cr13, {7}
d001a1a4:	28ffe7f2 	ldmcs	pc!, {r1, r4, r5, r6, r7, r8, r9, sl, sp, lr, pc}^	; <UNPREDICTABLE>
d001a1a8:	4639d104 	ldrtmi	sp, [r9], -r4, lsl #2
d001a1ac:	f7ff4640 			; <UNDEFINED> instruction: 0xf7ff4640
d001a1b0:	e7bffe5f 	sbfx	pc, pc, #28, #32
d001a1b4:	d1062b7b 	tstle	r6, fp, ror fp
d001a1b8:	0301f10a 	movweq	pc, #4362	; 0x110a	; <UNPREDICTABLE>
d001a1bc:	4641463a 			; <UNDEFINED> instruction: 0x4641463a
d001a1c0:	ff60f7ff 			; <UNDEFINED> instruction: 0xff60f7ff
d001a1c4:	f5a3e7b6 			; <UNDEFINED> instruction: 0xf5a3e7b6
d001a1c8:	2b017381 	blcs	0xd0076fd4
d001a1cc:	4b17d804 	blmi	0xd06101e4
d001a1d0:	6a1b447b 	bvs	0xd06eb3c4
d001a1d4:	d0a92b00 	adcle	r2, r9, r0, lsl #22
d001a1d8:	48164915 	ldmdami	r6, {r0, r2, r4, r8, fp, lr}
d001a1dc:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d001a1e0:	e8bde75c 	pop	{r2, r3, r4, r6, r8, r9, sl, sp, lr, pc}
d001a1e4:	bf008ff8 	svclt	0x00008ff8
d001a1e8:	fffffee8 			; <UNDEFINED> instruction: 0xfffffee8
d001a1ec:	0000e12a 	andeq	lr, r0, sl, lsr #2
d001a1f0:	0000e11a 	andeq	lr, r0, sl, lsl r1
d001a1f4:	fffffef4 			; <UNDEFINED> instruction: 0xfffffef4
d001a1f8:	fffffec6 			; <UNDEFINED> instruction: 0xfffffec6
d001a1fc:	0000e0c4 	andeq	lr, r0, r4, asr #1
d001a200:	0000e0a6 	andeq	lr, r0, r6, lsr #1
d001a204:	ffffb1f2 			; <UNDEFINED> instruction: 0xffffb1f2
d001a208:	0000e096 	muleq	r0, r6, r0
d001a20c:	0000e086 	andeq	lr, r0, r6, lsl #1
d001a210:	ffffff0a 			; <UNDEFINED> instruction: 0xffffff0a
d001a214:	0000e074 	andeq	lr, r0, r4, ror r0
d001a218:	fffffe7c 			; <UNDEFINED> instruction: 0xfffffe7c
d001a21c:	0000e050 	andeq	lr, r0, r0, asr r0
d001a220:	0000e03e 	andeq	lr, r0, lr, lsr r0
d001a224:	0000e032 	andeq	lr, r0, r2, lsr r0
d001a228:	0000e026 	andeq	lr, r0, r6, lsr #32
d001a22c:	0000dff4 	strdeq	sp, [r0], -r4
d001a230:	fffffe4b 			; <UNDEFINED> instruction: 0xfffffe4b
d001a234:	0000dfe6 	andeq	sp, r0, r6, ror #31

Disassembly of section .text.initialize_array.constprop.0:

d001a2d0 <.text.initialize_array.constprop.0>:
d001a2d0:	4ff7e92d 	svcmi	0x00f7e92d
d001a2d4:	46154e36 			; <UNDEFINED> instruction: 0x46154e36
d001a2d8:	460c4a36 			; <UNDEFINED> instruction: 0x460c4a36
d001a2dc:	9001447e 	andls	r4, r1, lr, ror r4
d001a2e0:	217b447a 	cmncs	fp, sl, ror r4
d001a2e4:	461f4630 			; <UNDEFINED> instruction: 0x461f4630
d001a2e8:	a030f8dd 	ldrsbtge	pc, [r0], -sp	; <UNPREDICTABLE>
d001a2ec:	fe1af7f8 	mrc2	7, 0, pc, cr10, cr8, {7}
d001a2f0:	d05a2800 	subsle	r2, sl, r0, lsl #16
d001a2f4:	f8df2cff 			; <UNDEFINED> instruction: 0xf8df2cff
d001a2f8:	f04fb0c0 			; <UNDEFINED> instruction: 0xf04fb0c0
d001a2fc:	bf140800 	svclt	0x00140800
d001a300:	701af44f 	andsvc	pc, sl, pc, asr #8
d001a304:	0901f04f 	stmdbeq	r1, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d001a308:	bf1844fb 	svclt	0x001844fb
d001a30c:	6004fb00 	andvs	pc, r4, r0, lsl #22
d001a310:	bf184e2a 	svclt	0x00184e2a
d001a314:	3068f500 	rsbcc	pc, r8, r0, lsl #10
d001a318:	bf18447e 	svclt	0x0018447e
d001a31c:	9028f8b0 	strhtls	pc, [r8], -r0	; <UNPREDICTABLE>
d001a320:	bb036db3 	bllt	0xd00f59f4
d001a324:	2b7d6af3 	blcs	0xd1f74ef8
d001a328:	f5b3d01d 			; <UNDEFINED> instruction: 0xf5b3d01d
d001a32c:	d01a7f80 	andsle	r7, sl, r0, lsl #31
d001a330:	45429a01 	strbmi	r9, [r2, #-2561]	; 0xfffff5ff
d001a334:	4922d107 	stmdbmi	r2!, {r0, r1, r2, r8, ip, lr, pc}
d001a338:	44794630 	ldrbtmi	r4, [r9], #-1584	; 0xfffff9d0
d001a33c:	e8bdb003 	pop	{r0, r1, ip, sp, pc}
d001a340:	f7f54ff0 			; <UNDEFINED> instruction: 0xf7f54ff0
d001a344:	2cffbf95 	ldclcs	15, cr11, [pc], #596	; 0xd001a5a0
d001a348:	4652d117 			; <UNDEFINED> instruction: 0x4652d117
d001a34c:	46284639 			; <UNDEFINED> instruction: 0x46284639
d001a350:	fd8ef7ff 	stc2	7, cr15, [lr, #1020]	; 0x3fc
d001a354:	4658212c 	ldrbmi	r2, [r8], -ip, lsr #2
d001a358:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d001a35c:	f7f8444d 			; <UNDEFINED> instruction: 0xf7f8444d
d001a360:	2800fdd3 	stmdacs	r0, {r0, r1, r4, r6, r7, r8, sl, fp, ip, sp, lr, pc}
d001a364:	4a17d1dc 	bmi	0xd060eadc
d001a368:	4817217d 	ldmdami	r7, {r0, r2, r3, r4, r5, r6, r8, sp}
d001a36c:	4478447a 	ldrbtmi	r4, [r8], #-1146	; 0xfffffb86
d001a370:	e8bdb003 	pop	{r0, r1, ip, sp, pc}
d001a374:	f7f84ff0 			; <UNDEFINED> instruction: 0xf7f84ff0
d001a378:	2b7bbdd5 	blcs	0xd1f09ad4
d001a37c:	2301d106 	movwcs	sp, #4358	; 0x1106
d001a380:	4629463a 			; <UNDEFINED> instruction: 0x4629463a
d001a384:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d001a388:	e7e3fe7d 			; <UNDEFINED> instruction: 0xe7e3fe7d
d001a38c:	7381f5a3 	orrvc	pc, r1, #683671552	; 0x28c00000
d001a390:	d8052b01 	stmdale	r5, {r0, r8, r9, fp, sp}
d001a394:	b91b6a33 	ldmdblt	fp, {r0, r1, r4, r5, r9, fp, sp, lr}
d001a398:	f7f84630 			; <UNDEFINED> instruction: 0xf7f84630
d001a39c:	e7d9fd95 	bfi	pc, r5, (invalid: 27:25)	; <UNPREDICTABLE>
d001a3a0:	480b490a 	stmdami	fp, {r1, r3, r8, fp, lr}
d001a3a4:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d001a3a8:	b003e7c8 	andlt	lr, r3, r8, asr #15
d001a3ac:	8ff0e8bd 	svchi	0x00f0e8bd
d001a3b0:	0000dee8 	andeq	sp, r0, r8, ror #29
d001a3b4:	ffffff54 			; <UNDEFINED> instruction: 0xffffff54
d001a3b8:	0000debc 			; <UNDEFINED> instruction: 0x0000debc
d001a3bc:	0000deac 	andeq	sp, r0, ip, lsr #29
d001a3c0:	ffffff1d 			; <UNDEFINED> instruction: 0xffffff1d
d001a3c4:	ffffff39 			; <UNDEFINED> instruction: 0xffffff39
d001a3c8:	0000de56 	andeq	sp, r0, r6, asr lr
d001a3cc:	fffffed7 			; <UNDEFINED> instruction: 0xfffffed7
d001a3d0:	0000de1e 	andeq	sp, r0, lr, lsl lr

Disassembly of section .text.local_declaration.constprop.0:

d001a63c <.text.local_declaration.constprop.0>:
d001a63c:	4ff0e92d 	svcmi	0x00f0e92d
d001a640:	472cf8df 			; <UNDEFINED> instruction: 0x472cf8df
d001a644:	7185f44f 	orrvc	pc, r5, pc, asr #8
d001a648:	ed2d447c 	cfstrs	mvf4, [sp, #-496]!	; 0xfffffe10
d001a64c:	46208b02 	strtmi	r8, [r0], -r2, lsl #22
d001a650:	f7f8b099 			; <UNDEFINED> instruction: 0xf7f8b099
d001a654:	6ae2fc59 	bvs	0xcf8d97c0
d001a658:	131bf240 	tstne	fp, #64, 4	; <UNPREDICTABLE>
d001a65c:	429a4605 	addsmi	r4, sl, #5242880	; 0x500000
d001a660:	4620d10a 	strtmi	sp, [r0], -sl, lsl #2
d001a664:	ff50f7f8 			; <UNDEFINED> instruction: 0xff50f7f8
d001a668:	2501bb98 	strcs	fp, [r1, #-2968]	; 0xfffff468
d001a66c:	b0194628 	andslt	r4, r9, r8, lsr #12
d001a670:	8b02ecbd 	blhi	0xd00d596c
d001a674:	8ff0e8bd 	svchi	0x00f0e8bd
d001a678:	1107f240 	tstne	r7, r0, asr #4	; <UNPREDICTABLE>
d001a67c:	f7f84620 			; <UNDEFINED> instruction: 0xf7f84620
d001a680:	b148fc43 	cmplt	r8, r3, asr #24	; <UNPREDICTABLE>
d001a684:	2b286ae3 	blcs	0xd0a35218
d001a688:	6ce3d123 	stfvsp	f5, [r3], #140	; 0x8c
d001a68c:	d1202b2a 			; <UNDEFINED> instruction: 0xd1202b2a
d001a690:	f7fb2000 			; <UNDEFINED> instruction: 0xf7fb2000
d001a694:	e7e8f835 			; <UNDEFINED> instruction: 0xe7e8f835
d001a698:	f2406ae2 	vpmax.s8	q11, q8, q9
d001a69c:	429a1301 	addsmi	r1, sl, #67108864	; 0x4000000
d001a6a0:	4620d11c 			; <UNDEFINED> instruction: 0x4620d11c
d001a6a4:	1206e9d4 	andne	lr, r6, #212, 18	; 0x350000
d001a6a8:	f8d7f7f6 			; <UNDEFINED> instruction: 0xf8d7f7f6
d001a6ac:	db152800 	blle	0xd05646b4
d001a6b0:	e9d44620 	ldmib	r4, {r5, r9, sl, lr}^
d001a6b4:	f7f61206 			; <UNDEFINED> instruction: 0xf7f61206
d001a6b8:	2324f8d0 	msrcs	CPSR_s, #208, 16	; 0xd00000
d001a6bc:	4000fb03 	andmi	pc, r0, r3, lsl #22
d001a6c0:	3075f500 	rsbscc	pc, r5, r0, lsl #10
d001a6c4:	33acf890 			; <UNDEFINED> instruction: 0x33acf890
d001a6c8:	d1072bff 	strdle	r2, [r7, -pc]
d001a6cc:	f7f84620 			; <UNDEFINED> instruction: 0xf7f84620
d001a6d0:	2301fbfb 	movwcs	pc, #7163	; 0x1bfb	; <UNPREDICTABLE>
d001a6d4:	23009308 	movwcs	r9, #776	; 0x308
d001a6d8:	e1e19307 	mvn	r9, r7, lsl #6
d001a6dc:	4694f8df 			; <UNDEFINED> instruction: 0x4694f8df
d001a6e0:	7184f44f 	orrvc	pc, r4, pc, asr #8
d001a6e4:	4620447c 			; <UNDEFINED> instruction: 0x4620447c
d001a6e8:	fc0ef7f8 	stc2	7, cr15, [lr], {248}	; 0xf8
d001a6ec:	b1804606 	orrlt	r4, r0, r6, lsl #12
d001a6f0:	2b286ae3 	blcs	0xd0a35284
d001a6f4:	6ce3d104 	stfvsp	f5, [r3], #16
d001a6f8:	d1012b2a 	tstle	r1, sl, lsr #22
d001a6fc:	e7c82001 	strb	r2, [r8, r1]
d001a700:	1674f8df 			; <UNDEFINED> instruction: 0x1674f8df
d001a704:	0674f8df 			; <UNDEFINED> instruction: 0x0674f8df
d001a708:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d001a70c:	fdb0f7f5 	ldc2	7, cr15, [r0, #980]!	; 0x3d4
d001a710:	4620e7ab 	strtmi	lr, [r0], -fp, lsr #15
d001a714:	f8c6f7f6 			; <UNDEFINED> instruction: 0xf8c6f7f6
d001a718:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d001a71c:	a90f819b 	stmdbge	pc, {r0, r1, r3, r4, r7, r8, pc}	; <UNPREDICTABLE>
d001a720:	960f4620 	strls	r4, [pc], -r0, lsr #12
d001a724:	fdfaf7f8 	ldc2l	7, cr15, [sl, #992]!	; 0x3e0
d001a728:	d09e2800 	addsle	r2, lr, r0, lsl #16
d001a72c:	7650f8df 			; <UNDEFINED> instruction: 0x7650f8df
d001a730:	4a10ee08 	bmi	0xd0455f58
d001a734:	f507447f 			; <UNDEFINED> instruction: 0xf507447f
d001a738:	930c2392 	movwls	r2, #50066	; 0xc392
d001a73c:	ee18212a 	mufep	f2, f0, #2.0
d001a740:	f7f80a10 			; <UNDEFINED> instruction: 0xf7f80a10
d001a744:	9007fbe1 	andls	pc, r7, r1, ror #23
d001a748:	d0712800 	rsbsle	r2, r1, r0, lsl #16
d001a74c:	ee18212a 	mufep	f2, f0, #2.0
d001a750:	f7f80a10 			; <UNDEFINED> instruction: 0xf7f80a10
d001a754:	1e03fbd9 			; <UNDEFINED> instruction: 0x1e03fbd9
d001a758:	2301bf18 	movwcs	fp, #7960	; 0x1f18
d001a75c:	6624f8df 			; <UNDEFINED> instruction: 0x6624f8df
d001a760:	9309ac10 	movwls	sl, #39952	; 0x9c10
d001a764:	f106447e 			; <UNDEFINED> instruction: 0xf106447e
d001a768:	f8960518 			; <UNDEFINED> instruction: 0xf8960518
d001a76c:	f8d69030 			; <UNDEFINED> instruction: 0xf8d69030
d001a770:	cd0fb034 	stcgt	0, cr11, [pc, #-208]	; 0xd001a6a8
d001a774:	e895c40f 	ldm	r5, {r0, r1, r2, r3, sl, lr, pc}
d001a778:	e884000f 	stm	r4, {r0, r1, r2, r3}
d001a77c:	f8df000f 			; <UNDEFINED> instruction: 0xf8df000f
d001a780:	f2402608 	vmax.s8	d18, d0, d8
d001a784:	46301101 	ldrtmi	r1, [r0], -r1, lsl #2
d001a788:	447a6a75 	ldrbtmi	r6, [sl], #-2677	; 0xfffff58b
d001a78c:	f7f86ab4 			; <UNDEFINED> instruction: 0xf7f86ab4
d001a790:	ab10fbc9 	blge	0xd04596bc
d001a794:	2800930a 	stmdacs	r0, {r1, r3, r8, r9, ip, pc}
d001a798:	af67f43f 	svcge	0x0067f43f
d001a79c:	2b009b07 	blcs	0xd00413c0
d001a7a0:	4630d148 	ldrtmi	sp, [r0], -r8, asr #2
d001a7a4:	f7f8215b 			; <UNDEFINED> instruction: 0xf7f8215b
d001a7a8:	1e06fbaf 	vmlane.f64	d15, d22, d31
d001a7ac:	2601bf18 			; <UNDEFINED> instruction: 0x2601bf18
d001a7b0:	a5d8f8df 	ldrbge	pc, [r8, #2271]	; 0x8df	; <UNPREDICTABLE>
d001a7b4:	721af44f 	andsvc	pc, sl, #1325400064	; 0x4f000000
d001a7b8:	44fa9b0f 	ldrbtmi	r9, [sl], #2831	; 0xb0f
d001a7bc:	a203fb02 	andge	pc, r3, #2048	; 0x800
d001a7c0:	3268f502 	rsbcc	pc, r8, #8388608	; 0x800000
d001a7c4:	92088d12 	andls	r8, r8, #1152	; 0x480
d001a7c8:	d0602e00 	rsble	r2, r0, r0, lsl #28
d001a7cc:	202cf8da 	ldrdcs	pc, [ip], -sl	; <UNPREDICTABLE>
d001a7d0:	8020f8da 	ldrdhi	pc, [r0], -sl	; <UNPREDICTABLE>
d001a7d4:	7281f5a2 	addvc	pc, r1, #679477248	; 0x28800000
d001a7d8:	d8082a01 	stmdale	r8, {r0, r9, fp, sp}
d001a7dc:	0f00f1b8 	svceq	0x0000f1b8
d001a7e0:	2240d005 	subcs	sp, r0, #5
d001a7e4:	fbb29908 	blx	0xcecc0c0e
d001a7e8:	4590f2f1 	ldrmi	pc, [r0, #753]	; 0x2f1
d001a7ec:	f8dfd928 			; <UNDEFINED> instruction: 0xf8dfd928
d001a7f0:	f44f25a0 	vst3.32	{d18,d20,d22}, [pc :128], r0
d001a7f4:	447a711a 	ldrbtmi	r7, [sl], #-282	; 0xfffffee6
d001a7f8:	2303fb01 	movwcs	pc, #15105	; 0x3b01	; <UNPREDICTABLE>
d001a7fc:	3368f503 	msrcc	SPSR_f, #12582912	; 0xc00000
d001a800:	302bf893 	mlacc	fp, r3, r8, pc	; <UNPREDICTABLE>
d001a804:	f8dfb9c3 			; <UNDEFINED> instruction: 0xf8dfb9c3
d001a808:	447a258c 	ldrbtmi	r2, [sl], #-1420	; 0xfffffa74
d001a80c:	3588f8df 	strcc	pc, [r8, #2271]	; 0x8df
d001a810:	6d99447b 	cfldrsvs	mvf4, [r9, #492]	; 0x1ec
d001a814:	f47f2900 			; <UNDEFINED> instruction: 0xf47f2900
d001a818:	6a5daf28 	bvs	0xd17864c0
d001a81c:	6b596a9c 	blvs	0xd1675294
d001a820:	0030f893 	mlaseq	r0, r3, r8, pc	; <UNPREDICTABLE>
d001a824:	e9c36699 	stmib	r3, {r0, r3, r4, r7, r9, sl, sp, lr}^
d001a828:	e9c32516 	stmib	r3, {r1, r2, r4, r8, sl, sp}^
d001a82c:	e71c4018 			; <UNDEFINED> instruction: 0xe71c4018
d001a830:	e7939b07 	ldr	r9, [r3, r7, lsl #22]
d001a834:	e7bb2600 	ldr	r2, [fp, r0, lsl #12]!
d001a838:	2560f8df 	strbcs	pc, [r0, #-2271]!	; 0xfffff721	; <UNPREDICTABLE>
d001a83c:	e7e5447a 			; <UNDEFINED> instruction: 0xe7e5447a
d001a840:	f7f84650 			; <UNDEFINED> instruction: 0xf7f84650
d001a844:	f8dffb41 			; <UNDEFINED> instruction: 0xf8dffb41
d001a848:	215d2558 	cmpcs	sp, r8, asr r5
d001a84c:	447a4650 	ldrbtmi	r4, [sl], #-1616	; 0xfffff9b0
d001a850:	fb68f7f8 	blx	0xd1a5883a
d001a854:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001a858:	9b07af08 	blls	0xd0206480
d001a85c:	9b08b9d3 	blls	0xd0248fb0
d001a860:	fa03fb08 	blx	0xd0119488
d001a864:	f8d39b0c 			; <UNDEFINED> instruction: 0xf8d39b0c
d001a868:	f1c33238 			; <UNDEFINED> instruction: 0xf1c33238
d001a86c:	45530340 	ldrbmi	r0, [r3, #-832]	; 0xfffffcc0
d001a870:	6dbbd213 	lfmvs	f5, 1, [fp, #76]!	; 0x4c
d001a874:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001a878:	f8dfaef8 			; <UNDEFINED> instruction: 0xf8dfaef8
d001a87c:	f8c73528 			; <UNDEFINED> instruction: 0xf8c73528
d001a880:	447bb068 	ldrbtmi	fp, [fp], #-104	; 0xffffff98
d001a884:	4918e9c7 	ldmdbmi	r8, {r0, r1, r2, r6, r7, r8, fp, sp, lr, pc}
d001a888:	3516e9c7 	ldrcc	lr, [r6, #-2503]	; 0xfffff639
d001a88c:	f04fe6ed 			; <UNDEFINED> instruction: 0xf04fe6ed
d001a890:	e7e20801 	strb	r0, [r2, r1, lsl #16]!
d001a894:	0a01f04f 	beq	0xd00969d8
d001a898:	9b09e7e4 	blls	0xd0294830
d001a89c:	d1622b00 	cmnle	r2, r0, lsl #22
d001a8a0:	2b009b07 	blcs	0xd00414c4
d001a8a4:	2e00d161 	mvfcssz	f5, f1
d001a8a8:	2310bf14 	tstcs	r0, #20, 30	; 0x50
d001a8ac:	9304230d 	movwls	r2, #17165	; 0x430d
d001a8b0:	9414ab18 	ldrls	sl, [r4], #-2840	; 0xfffff4e8
d001a8b4:	9058f88d 	subsls	pc, r8, sp, lsl #17
d001a8b8:	b05cf8cd 	subslt	pc, ip, sp, asr #17
d001a8bc:	e9139513 	ldmdb	r3, {r0, r1, r4, r8, sl, ip, pc}
d001a8c0:	e88d000f 	stm	sp, {r0, r1, r2, r3}
d001a8c4:	9b0a000f 	blls	0xd029a908
d001a8c8:	f7f9cb0f 			; <UNDEFINED> instruction: 0xf7f9cb0f
d001a8cc:	f8dffbab 			; <UNDEFINED> instruction: 0xf8dffbab
d001a8d0:	460524d8 			; <UNDEFINED> instruction: 0x460524d8
d001a8d4:	6d93447a 	cfldrsvs	mvf4, [r3, #488]	; 0x1e8
d001a8d8:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001a8dc:	2130aec6 	teqcs	r0, r6, asr #29
d001a8e0:	0b01f04f 	bleq	0xd0096a24
d001a8e4:	2992f502 	ldmibcs	r2, {r1, r8, sl, ip, sp, lr, pc}
d001a8e8:	fb01920a 	blx	0xd007f11a
d001a8ec:	980f2300 	stmdals	pc, {r8, r9, sp}	; <UNPREDICTABLE>
d001a8f0:	f503910b 			; <UNDEFINED> instruction: 0xf503910b
d001a8f4:	f8832390 			; <UNDEFINED> instruction: 0xf8832390
d001a8f8:	f8a3065a 			; <UNDEFINED> instruction: 0xf8a3065a
d001a8fc:	45da8662 	ldrbmi	r8, [sl, #1634]	; 0x662
d001a900:	4238f8d9 	eorsmi	pc, r8, #14221312	; 0xd90000
d001a904:	f8d9d833 			; <UNDEFINED> instruction: 0xf8d9d833
d001a908:	429c323c 	addsmi	r3, ip, #60, 4	; 0xc0000003
d001a90c:	bf889b07 	svclt	0x00889b07
d001a910:	423cf8c9 	eorsmi	pc, ip, #13172736	; 0xc90000
d001a914:	d04c2b00 	suble	r2, ip, r0, lsl #22
d001a918:	4490f8df 	ldrmi	pc, [r0], #2271	; 0x8df
d001a91c:	447c213d 	ldrbtmi	r2, [ip], #-317	; 0xfffffec3
d001a920:	f7f84620 			; <UNDEFINED> instruction: 0xf7f84620
d001a924:	4601faf1 			; <UNDEFINED> instruction: 0x4601faf1
d001a928:	d03e2800 	eorsle	r2, lr, r0, lsl #16
d001a92c:	46209b09 	strtmi	r9, [r0], -r9, lsl #22
d001a930:	b3bb990f 			; <UNDEFINED> instruction: 0xb3bb990f
d001a934:	faacf7fb 	blx	0xceb58928
d001a938:	0474f8df 	ldrbteq	pc, [r4], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d001a93c:	46292200 	strtmi	r2, [r9], -r0, lsl #4
d001a940:	f7fa4478 			; <UNDEFINED> instruction: 0xf7fa4478
d001a944:	f8dff920 			; <UNDEFINED> instruction: 0xf8dff920
d001a948:	4478046c 	ldrbtmi	r0, [r8], #-1132	; 0xfffffb94
d001a94c:	2b006d83 	blcs	0xd0035f60
d001a950:	f8dfd079 			; <UNDEFINED> instruction: 0xf8dfd079
d001a954:	213b2464 	teqcs	fp, r4, ror #8
d001a958:	0460f8df 	strbteq	pc, [r0], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d001a95c:	4478447a 	ldrbtmi	r4, [r8], #-1146	; 0xfffffb86
d001a960:	fae0f7f8 	blx	0xcf858948
d001a964:	2312e681 	tstcs	r2, #135266304	; 0x8100000
d001a968:	230ee7a1 	movwcs	lr, #59297	; 0xe7a1
d001a96c:	1c63e79f 	stclne	7, cr14, [r3], #-636	; 0xfffffd84
d001a970:	21009a0a 	tstcs	r0, sl, lsl #20
d001a974:	0b01f10b 	bleq	0xd0096da8
d001a978:	3238f8c9 	eorscc	pc, r8, #13172736	; 0xc90000
d001a97c:	3240f899 	subcc	pc, r0, #10027008	; 0x990000
d001a980:	9b0b930d 	blls	0xd02ff5bc
d001a984:	2404fb03 	strcs	pc, [r4], #-2819	; 0xfffff4fd
d001a988:	f5042230 			; <UNDEFINED> instruction: 0xf5042230
d001a98c:	f5042490 			; <UNDEFINED> instruction: 0xf5042490
d001a990:	f00660c7 			; <UNDEFINED> instruction: 0xf00660c7
d001a994:	9b0dfe3d 	blls	0xd039a290
d001a998:	3658f884 	ldrbcc	pc, [r8], -r4, lsl #17	; <UNPREDICTABLE>
d001a99c:	f884230b 			; <UNDEFINED> instruction: 0xf884230b
d001a9a0:	e7ac3659 	sbfx	r3, r9, #12, #13
d001a9a4:	fa6ef7fd 	blx	0xd1bd89a0
d001a9a8:	4620e7c6 	strtmi	lr, [r0], -r6, asr #15
d001a9ac:	fcaff7fa 	stc2	7, cr15, [pc], #1000	; 0xd001ad9c
d001a9b0:	f8dfe7c2 			; <UNDEFINED> instruction: 0xf8dfe7c2
d001a9b4:	213d440c 	teqcs	sp, ip, lsl #8
d001a9b8:	4620447c 			; <UNDEFINED> instruction: 0x4620447c
d001a9bc:	faa4f7f8 	blx	0xce9589a4
d001a9c0:	d0c02800 	sbcle	r2, r0, r0, lsl #16
d001a9c4:	6ae3b9ee 	bvs	0xcf909184
d001a9c8:	d01a2b7b 	andsle	r2, sl, fp, ror fp
d001a9cc:	4620990f 	strtmi	r9, [r0], -pc, lsl #18
d001a9d0:	fe02f7fc 	mcr2	7, 0, pc, cr2, cr12, {7}	; <UNPREDICTABLE>
d001a9d4:	f24b4620 	vmax.s8	d20, d11, d16
d001a9d8:	f7fa4103 			; <UNDEFINED> instruction: 0xf7fa4103
d001a9dc:	4629f89b 			; <UNDEFINED> instruction: 0x4629f89b
d001a9e0:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d001a9e4:	4620ff6f 	strtmi	pc, [r0], -pc, ror #30
d001a9e8:	6101f244 	tstvs	r1, r4, asr #4	; <UNPREDICTABLE>
d001a9ec:	f892f7fa 			; <UNDEFINED> instruction: 0xf892f7fa
d001a9f0:	f64b4620 			; <UNDEFINED> instruction: 0xf64b4620
d001a9f4:	f7fa4105 			; <UNDEFINED> instruction: 0xf7fa4105
d001a9f8:	9808f88d 	stmdals	r8, {r0, r2, r3, r7, fp, ip, sp, lr, pc}
d001a9fc:	fc0af7fa 	stc2	7, cr15, [sl], {250}	; 0xfa
d001aa00:	f8dfe7a1 			; <UNDEFINED> instruction: 0xf8dfe7a1
d001aa04:	240093c0 	strcs	r9, [r0], #-960	; 0xfffffc40
d001aa08:	210048ef 	smlattcs	r0, pc, r8, r4
d001aa0c:	447844f9 	ldrbtmi	r4, [r8], #-1273	; 0xfffffb07
d001aa10:	fc7df7fa 	ldc2l	7, cr15, [sp], #-1000	; 0xfffffc18
d001aa14:	d10945a2 	smlatble	r9, r2, r5, r4
d001aa18:	b176980f 	cmnlt	r6, pc, lsl #16
d001aa1c:	46012300 	strmi	r2, [r1], -r0, lsl #6
d001aa20:	4640462a 	strbmi	r4, [r0], -sl, lsr #12
d001aa24:	f7ff9300 			; <UNDEFINED> instruction: 0xf7ff9300
d001aa28:	e78cfc53 			; <UNDEFINED> instruction: 0xe78cfc53
d001aa2c:	22001929 	andcs	r1, r0, #671744	; 0xa4000
d001aa30:	34014648 	strcc	r4, [r1], #-1608	; 0xfffff9b8
d001aa34:	f8a7f7fa 			; <UNDEFINED> instruction: 0xf8a7f7fa
d001aa38:	2301e7ec 	movwcs	lr, #6124	; 0x17ec
d001aa3c:	46294632 			; <UNDEFINED> instruction: 0x46294632
d001aa40:	fb20f7ff 	blx	0xd0858a46
d001aa44:	212ce77f 			; <UNDEFINED> instruction: 0x212ce77f
d001aa48:	fa5ef7f8 	blx	0xd17d8a30
d001aa4c:	f47f2800 			; <UNDEFINED> instruction: 0xf47f2800
d001aa50:	e77eae75 			; <UNDEFINED> instruction: 0xe77eae75
d001aa54:	f2406ae2 	vpmax.s8	q11, q8, q9
d001aa58:	429a1301 	addsmi	r1, sl, #67108864	; 0x4000000
d001aa5c:	2d00d007 	stccs	0, cr13, [r0, #-28]	; 0xffffffe4
d001aa60:	ae04f43f 	cfmvdhrge	mvd4, pc
d001aa64:	48da49d9 	ldmmi	sl, {r0, r3, r4, r6, r7, r8, fp, lr}^
d001aa68:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d001aa6c:	e9d4e64e 	ldmib	r4, {r1, r2, r3, r6, r9, sl, sp, lr, pc}^
d001aa70:	46201206 	strtmi	r1, [r0], -r6, lsl #4
d001aa74:	feacf7f5 	mcr2	7, 5, pc, cr12, cr5, {7}	; <UNPREDICTABLE>
d001aa78:	daf02800 	ble	0xcfc24a80
d001aa7c:	447848d5 	ldrbtmi	r4, [r8], #-2261	; 0xfffff72b
d001aa80:	ff4cf7f9 			; <UNDEFINED> instruction: 0xff4cf7f9
d001aa84:	f0402800 			; <UNDEFINED> instruction: 0xf0402800
d001aa88:	48d38171 	ldmmi	r3, {r0, r4, r5, r6, r8, pc}^
d001aa8c:	f7f94478 			; <UNDEFINED> instruction: 0xf7f94478
d001aa90:	2800ff45 	stmdacs	r0, {r0, r2, r6, r8, r9, sl, fp, ip, sp, lr, pc}
d001aa94:	2305d051 	movwcs	sp, #20561	; 0x5051
d001aa98:	2d009307 	stccs	3, cr9, [r0, #-28]	; 0xffffffe4
d001aa9c:	9508d1e2 	strls	sp, [r8, #-482]	; 0xfffffe1e
d001aaa0:	4ccf4bce 	vstmiami	pc, {d20-<overflow reg d58>}
d001aaa4:	447c447b 	ldrbtmi	r4, [ip], #-1147	; 0xfffffb85
d001aaa8:	3a10ee08 	bcc	0xd04562d0
d001aaac:	2392f504 	orrscs	pc, r2, #4, 10	; 0x1000000
d001aab0:	9b08930a 	blls	0xd023f6e0
d001aab4:	d0472b00 	suble	r2, r7, r0, lsl #22
d001aab8:	ee18212a 	mufep	f2, f0, #2.0
d001aabc:	f7f80a10 			; <UNDEFINED> instruction: 0xf7f80a10
d001aac0:	2800fa23 	stmdacs	r0, {r0, r1, r5, r9, fp, ip, sp, lr, pc}
d001aac4:	212ad040 			; <UNDEFINED> instruction: 0x212ad040
d001aac8:	0a10ee18 	beq	0xd0456330
d001aacc:	fa1cf7f8 	blx	0xd0758ab4
d001aad0:	bf142800 	svclt	0x00142800
d001aad4:	270a2713 	smladcs	sl, r3, r7, r2
d001aad8:	f10d4ec2 			; <UNDEFINED> instruction: 0xf10d4ec2
d001aadc:	447e0c40 	ldrbtmi	r0, [lr], #-3136	; 0xfffff3c0
d001aae0:	0e18f106 	mnfeqe	f7, f6
d001aae4:	b024f8d6 	ldrdlt	pc, [r4], -r6	; <UNPREDICTABLE>
d001aae8:	a028f8d6 	ldrdge	pc, [r8], -r6	; <UNPREDICTABLE>
d001aaec:	9030f896 	mlasls	r0, r6, r8, pc	; <UNPREDICTABLE>
d001aaf0:	8034f8d6 	ldrsbthi	pc, [r4], -r6	; <UNPREDICTABLE>
d001aaf4:	000fe8be 			; <UNDEFINED> instruction: 0x000fe8be
d001aaf8:	000fe8ac 	andeq	lr, pc, ip, lsr #17
d001aafc:	000fe89e 	muleq	pc, lr, r8	; <UNPREDICTABLE>
d001ab00:	000fe88c 	andeq	lr, pc, ip, lsl #17
d001ab04:	f2404ab8 	vpmin.s8	d20, d16, d24
d001ab08:	46301101 	ldrtmi	r1, [r0], -r1, lsl #2
d001ab0c:	f7f8447a 			; <UNDEFINED> instruction: 0xf7f8447a
d001ab10:	ab10fa09 	blge	0xd045933c
d001ab14:	28009309 	stmdacs	r0, {r0, r3, r8, r9, ip, pc}
d001ab18:	ada7f43f 	cfstrsge	mvf15, [r7, #252]!	; 0xfc
d001ab1c:	b1afb1b5 			; <UNDEFINED> instruction: 0xb1afb1b5
d001ab20:	2b006db3 	blcs	0xd00361f4
d001ab24:	ada1f47f 	cfstrsge	mvf15, [r1, #508]!	; 0x1fc
d001ab28:	f8c64bb0 			; <UNDEFINED> instruction: 0xf8c64bb0
d001ab2c:	447b8068 	ldrbtmi	r8, [fp], #-104	; 0xffffff98
d001ab30:	a918e9c6 	ldmdbge	r8, {r1, r2, r6, r7, r8, fp, sp, lr, pc}
d001ab34:	3b16e9c6 	blcc	0xd05d5254
d001ab38:	48ade597 	stmiami	sp!, {r0, r1, r2, r4, r7, r8, sl, sp, lr, pc}
d001ab3c:	f7f94478 			; <UNDEFINED> instruction: 0xf7f94478
d001ab40:	2800feed 	stmdacs	r0, {r0, r2, r3, r5, r6, r7, r9, sl, fp, ip, sp, lr, pc}
d001ab44:	e78ad1a7 	str	sp, [sl, r7, lsr #3]
d001ab48:	e7c59f07 	strb	r9, [r5, r7, lsl #30]
d001ab4c:	4620215b 			; <UNDEFINED> instruction: 0x4620215b
d001ab50:	f9daf7f8 			; <UNDEFINED> instruction: 0xf9daf7f8
d001ab54:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d001ab58:	b16580b3 	strhlt	r8, [r5, #-3]!
d001ab5c:	2b006da3 	blcs	0xd00361f0
d001ab60:	ad83f47f 	cfstrsge	mvf15, [r3, #508]	; 0x1fc
d001ab64:	447b4ba3 	ldrbtmi	r4, [fp], #-2979	; 0xfffff45d
d001ab68:	8068f8c4 	rsbhi	pc, r8, r4, asr #17
d001ab6c:	3b16e9c4 	blcc	0xd05d5284
d001ab70:	a918e9c4 	ldmdbge	r8, {r2, r6, r7, r8, fp, sp, lr, pc}
d001ab74:	b137e579 	teqlt	r7, r9, ror r5
d001ab78:	2b006da3 	blcs	0xd003620c
d001ab7c:	ad75f47f 	cfldrdge	mvd15, [r5, #-508]!	; 0xfffffe04
d001ab80:	447b4b9d 	ldrbtmi	r4, [fp], #-2973	; 0xfffff463
d001ab84:	6ae3e7f0 	bvs	0xcf914b4c
d001ab88:	f5a36a26 			; <UNDEFINED> instruction: 0xf5a36a26
d001ab8c:	2b017381 	blcs	0xd0077998
d001ab90:	b136d807 	teqlt	r6, r7, lsl #16
d001ab94:	f8d39b0a 			; <UNDEFINED> instruction: 0xf8d39b0a
d001ab98:	f1c33238 			; <UNDEFINED> instruction: 0xf1c33238
d001ab9c:	429e0340 	addsmi	r0, lr, #64, 6
d001aba0:	4b96d912 	blmi	0xce5d0ff0
d001aba4:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d001aba8:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d001abac:	4d94ad5e 	ldcmi	13, cr10, [r4, #376]	; 0x178
d001abb0:	6a986a5c 	bvs	0xce635528
d001abb4:	6b5a447d 	blvs	0xd16abdb0
d001abb8:	1030f893 	mlasne	r0, r3, r8, pc	; <UNPREDICTABLE>
d001abbc:	e9c3669a 	stmib	r3, {r1, r3, r4, r7, r9, sl, sp, lr}^
d001abc0:	e9c35416 	stmib	r3, {r1, r2, r4, sl, ip, lr}^
d001abc4:	e5500118 	ldrb	r0, [r0, #-280]	; 0xfffffee8
d001abc8:	f7f84620 			; <UNDEFINED> instruction: 0xf7f84620
d001abcc:	4a8df97d 	bmi	0xce3991c8
d001abd0:	4620215d 			; <UNDEFINED> instruction: 0x4620215d
d001abd4:	f7f8447a 			; <UNDEFINED> instruction: 0xf7f8447a
d001abd8:	2800f9a5 	stmdacs	r0, {r0, r2, r5, r7, r8, fp, ip, sp, lr, pc}
d001abdc:	ad45f43f 	cfstrdge	mvd15, [r5, #-252]	; 0xffffff04
d001abe0:	f88d2309 			; <UNDEFINED> instruction: 0xf88d2309
d001abe4:	f8cd9058 			; <UNDEFINED> instruction: 0xf8cd9058
d001abe8:	9304a050 	movwls	sl, #16464	; 0x4050
d001abec:	f8cdab18 			; <UNDEFINED> instruction: 0xf8cdab18
d001abf0:	f8cd805c 			; <UNDEFINED> instruction: 0xf8cd805c
d001abf4:	e913b04c 	ldmdb	r3, {r2, r3, r6, ip, sp, pc}
d001abf8:	e88d000f 	stm	sp, {r0, r1, r2, r3}
d001abfc:	9b09000f 	blls	0xd025ac40
d001ac00:	f7f9cb0f 			; <UNDEFINED> instruction: 0xf7f9cb0f
d001ac04:	6da3fa0f 			; <UNDEFINED> instruction: 0x6da3fa0f
d001ac08:	2b004681 	blcs	0xd002c614
d001ac0c:	ad2df47f 	cfstrsge	mvf15, [sp, #-508]!	; 0xfffffe04
d001ac10:	0b30f04f 	bleq	0xd0c56d54
d001ac14:	0801f04f 	stmdaeq	r1, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d001ac18:	2a92f504 	bcs	0xce4d8030
d001ac1c:	fb0b9409 	blx	0xd02ffc4a
d001ac20:	f5034300 			; <UNDEFINED> instruction: 0xf5034300
d001ac24:	f8a32390 			; <UNDEFINED> instruction: 0xf8a32390
d001ac28:	45466662 	strbmi	r6, [r6, #-1634]	; 0xfffff99e
d001ac2c:	7238f8da 	eorsvc	pc, r8, #14286848	; 0xda0000
d001ac30:	f8dad12c 			; <UNDEFINED> instruction: 0xf8dad12c
d001ac34:	213d323c 	teqcs	sp, ip, lsr r2
d001ac38:	bf3842bb 	svclt	0x003842bb
d001ac3c:	723cf8ca 	eorsvc	pc, ip, #13238272	; 0xca0000
d001ac40:	447f4f71 	ldrbtmi	r4, [pc], #-3953	; 0xd001ac48
d001ac44:	f7f84638 			; <UNDEFINED> instruction: 0xf7f84638
d001ac48:	b1a0f95f 	asrlt	pc, pc, r9	; <UNPREDICTABLE>
d001ac4c:	21002600 	tstcs	r0, r0, lsl #12
d001ac50:	f7fa4638 			; <UNDEFINED> instruction: 0xf7fa4638
d001ac54:	eb09fb5c 	bl	0xd02999cc
d001ac58:	36010106 	strcc	r0, [r1], -r6, lsl #2
d001ac5c:	46382200 	ldrtmi	r2, [r8], -r0, lsl #4
d001ac60:	ff91f7f9 			; <UNDEFINED> instruction: 0xff91f7f9
d001ac64:	d1f645b0 	ldrhle	r4, [r6, #80]!	; 0x50
d001ac68:	464a2300 	strbmi	r2, [sl], -r0, lsl #6
d001ac6c:	464021ff 			; <UNDEFINED> instruction: 0x464021ff
d001ac70:	f7ff9300 			; <UNDEFINED> instruction: 0xf7ff9300
d001ac74:	4865fb2d 	stmdami	r5!, {r0, r2, r3, r5, r8, r9, fp, ip, sp, lr, pc}^
d001ac78:	6d834478 	cfstrsvs	mvf4, [r3, #480]	; 0x1e0
d001ac7c:	d06e2b00 	rsble	r2, lr, r0, lsl #22
d001ac80:	213b4a63 	teqcs	fp, r3, ror #20
d001ac84:	447a4863 	ldrbtmi	r4, [sl], #-2147	; 0xfffff79d
d001ac88:	e6694478 			; <UNDEFINED> instruction: 0xe6694478
d001ac8c:	22301c7b 	eorscs	r1, r0, #31488	; 0x7b00
d001ac90:	f1082100 			; <UNDEFINED> instruction: 0xf1082100
d001ac94:	f8ca0801 			; <UNDEFINED> instruction: 0xf8ca0801
d001ac98:	f89a3238 			; <UNDEFINED> instruction: 0xf89a3238
d001ac9c:	930b3240 	movwls	r3, #45632	; 0xb240
d001aca0:	fb0b9b09 	blx	0xd03018ce
d001aca4:	f5073707 			; <UNDEFINED> instruction: 0xf5073707
d001aca8:	f5072790 			; <UNDEFINED> instruction: 0xf5072790
d001acac:	f00660c7 			; <UNDEFINED> instruction: 0xf00660c7
d001acb0:	9b0bfcaf 	blls	0xd0319f74
d001acb4:	3658f887 	ldrbcc	pc, [r8], -r7, lsl #17	; <UNPREDICTABLE>
d001acb8:	f887230b 			; <UNDEFINED> instruction: 0xf887230b
d001acbc:	e7b43659 	sbfx	r3, r9, #12, #21
d001acc0:	f8cdb2fb 			; <UNDEFINED> instruction: 0xf8cdb2fb
d001acc4:	f88da050 			; <UNDEFINED> instruction: 0xf88da050
d001acc8:	93049058 	movwls	r9, #16472	; 0x4058
d001accc:	f8cdab18 			; <UNDEFINED> instruction: 0xf8cdab18
d001acd0:	f8cd805c 			; <UNDEFINED> instruction: 0xf8cd805c
d001acd4:	e913b04c 	ldmdb	r3, {r2, r3, r6, ip, sp, pc}
d001acd8:	e88d000f 	stm	sp, {r0, r1, r2, r3}
d001acdc:	9b09000f 	blls	0xd025ad20
d001ace0:	f7f9cb0f 			; <UNDEFINED> instruction: 0xf7f9cb0f
d001ace4:	6da3f99f 			; <UNDEFINED> instruction: 0x6da3f99f
d001ace8:	2b004606 	blcs	0xd002c508
d001acec:	acbdf47f 	cfldrsge	mvf15, [sp], #508	; 0x1fc
d001acf0:	213d2330 	teqcs	sp, r0, lsr r3
d001acf4:	4300fb03 	movwmi	pc, #2819	; 0xb03	; <UNPREDICTABLE>
d001acf8:	f5034620 			; <UNDEFINED> instruction: 0xf5034620
d001acfc:	f8832390 			; <UNDEFINED> instruction: 0xf8832390
d001ad00:	f7f85664 			; <UNDEFINED> instruction: 0xf7f85664
d001ad04:	b1e0f901 	mvnlt	pc, r1, lsl #18
d001ad08:	d1092f13 	tstle	r9, r3, lsl pc
d001ad0c:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d001ad10:	4841fe1f 	stmdami	r1, {r0, r1, r2, r3, r4, r9, sl, fp, ip, sp, lr, pc}^
d001ad14:	46312200 	ldrtmi	r2, [r1], -r0, lsl #4
d001ad18:	f7f94478 			; <UNDEFINED> instruction: 0xf7f94478
d001ad1c:	e7aaff34 			; <UNDEFINED> instruction: 0xe7aaff34
d001ad20:	f04f2f0a 			; <UNDEFINED> instruction: 0xf04f2f0a
d001ad24:	46200101 	strtmi	r0, [r0], -r1, lsl #2
d001ad28:	2204bf0c 	andcs	fp, r4, #12, 30	; 0x30
d001ad2c:	f7fb2201 			; <UNDEFINED> instruction: 0xf7fb2201
d001ad30:	2f05fa83 	svccs	0x0005fa83
d001ad34:	f24bd1ed 	vrhadd.s8	<illegal reg q14.5>, <illegal reg q13.5>, <illegal reg q14.5>
d001ad38:	462021c0 	strtmi	r2, [r0], -r0, asr #3
d001ad3c:	feeaf7f9 	mcr2	7, 7, pc, cr10, cr9, {7}	; <UNPREDICTABLE>
d001ad40:	2d00e7e7 	stccs	7, cr14, [r0, #-924]	; 0xfffffc64
d001ad44:	6da3d097 	stcvs	0, cr13, [r3, #604]!	; 0x25c
d001ad48:	d1942b00 	orrsle	r2, r4, r0, lsl #22
d001ad4c:	f8c44b33 			; <UNDEFINED> instruction: 0xf8c44b33
d001ad50:	447b8068 	ldrbtmi	r8, [fp], #-104	; 0xffffff98
d001ad54:	a918e9c4 	ldmdbge	r8, {r2, r6, r7, r8, fp, sp, lr, pc}
d001ad58:	3b16e9c4 	blcc	0xd05d5470
d001ad5c:	212ce78b 	smlawbcs	ip, fp, r7, lr
d001ad60:	f8d2f7f8 			; <UNDEFINED> instruction: 0xf8d2f7f8
d001ad64:	f47f2800 			; <UNDEFINED> instruction: 0xf47f2800
d001ad68:	e789aea4 	str	sl, [r9, r4, lsr #29]
d001ad6c:	e6932301 	ldr	r2, [r3], r1, lsl #6
d001ad70:	0000db7c 	andeq	sp, r0, ip, ror fp
d001ad74:	0000dae0 	andeq	sp, r0, r0, ror #21
d001ad78:	fffffd1b 			; <UNDEFINED> instruction: 0xfffffd1b
d001ad7c:	0000daba 			; <UNDEFINED> instruction: 0x0000daba
d001ad80:	0000da90 	muleq	r0, r0, sl
d001ad84:	0000da60 	andeq	sp, r0, r0, ror #20
d001ad88:	fffffcd2 			; <UNDEFINED> instruction: 0xfffffcd2
d001ad8c:	0000da0a 	andeq	sp, r0, sl, lsl #20
d001ad90:	0000d9ce 	andeq	sp, r0, lr, asr #19
d001ad94:	fffffbef 			; <UNDEFINED> instruction: 0xfffffbef
d001ad98:	0000d9b4 			; <UNDEFINED> instruction: 0x0000d9b4
d001ad9c:	fffffb94 			; <UNDEFINED> instruction: 0xfffffb94
d001ada0:	fffffc2c 			; <UNDEFINED> instruction: 0xfffffc2c
d001ada4:	fffffc1d 			; <UNDEFINED> instruction: 0xfffffc1d
d001ada8:	0000d8f0 	strdeq	sp, [r0], -r0
d001adac:	0000d8a6 	andeq	sp, r0, r6, lsr #17
d001adb0:	0000d884 	andeq	sp, r0, r4, lsl #17
d001adb4:	0000d87a 	andeq	sp, r0, sl, ror r8
d001adb8:	fffffb71 			; <UNDEFINED> instruction: 0xfffffb71
d001adbc:	0000d866 	andeq	sp, r0, r6, ror #16
d001adc0:	0000d80c 	andeq	sp, r0, ip, lsl #16
d001adc4:	0000d7b8 			; <UNDEFINED> instruction: 0x0000d7b8
d001adc8:	0000d7b6 			; <UNDEFINED> instruction: 0x0000d7b6
d001adcc:	fffffa9a 			; <UNDEFINED> instruction: 0xfffffa9a
d001add0:	0000d75a 	andeq	sp, r0, sl, asr r7
d001add4:	fffffa72 			; <UNDEFINED> instruction: 0xfffffa72
d001add8:	fffffa6d 			; <UNDEFINED> instruction: 0xfffffa6d
d001addc:	0000d720 	andeq	sp, r0, r0, lsr #14
d001ade0:	0000d71e 	andeq	sp, r0, lr, lsl r7
d001ade4:	0000d6e6 	andeq	sp, r0, r6, ror #13
d001ade8:	fffffa30 			; <UNDEFINED> instruction: 0xfffffa30
d001adec:	fffff9d4 			; <UNDEFINED> instruction: 0xfffff9d4
d001adf0:	ffff8d2e 			; <UNDEFINED> instruction: 0xffff8d2e
d001adf4:	fffff9f5 			; <UNDEFINED> instruction: 0xfffff9f5
d001adf8:	fffff9fc 			; <UNDEFINED> instruction: 0xfffff9fc
d001adfc:	0000d620 	andeq	sp, r0, r0, lsr #12
d001ae00:	fffff9ee 			; <UNDEFINED> instruction: 0xfffff9ee
d001ae04:	fffff9ff 			; <UNDEFINED> instruction: 0xfffff9ff
d001ae08:	0000d582 	andeq	sp, r0, r2, lsl #11
d001ae0c:	0000d54c 	andeq	sp, r0, ip, asr #10
d001ae10:	fffff991 			; <UNDEFINED> instruction: 0xfffff991
d001ae14:	0000d53c 	andeq	sp, r0, ip, lsr r5
d001ae18:	0000d4ac 	andeq	sp, r0, ip, lsr #9
d001ae1c:	fffff8a5 			; <UNDEFINED> instruction: 0xfffff8a5

Disassembly of section .text.block.constprop.0:

d001ae40 <.text.block.constprop.0>:
d001ae40:	4c0db510 	cfstr32mi	mvfx11, [sp], {16}
d001ae44:	6da3447c 	cfstrsvs	mvf4, [r3, #496]!	; 0x1f0
d001ae48:	6ae3b92b 	bvs	0xcf9092fc
d001ae4c:	d0022b7d 	andle	r2, r2, sp, ror fp
d001ae50:	7f80f5b3 	svcvc	0x0080f5b3
d001ae54:	4a09d108 	bmi	0xd028f27c
d001ae58:	4809217d 	stmdami	r9, {r0, r2, r3, r4, r5, r6, r8, sp}
d001ae5c:	4478447a 	ldrbtmi	r4, [r8], #-1146	; 0xfffffb86
d001ae60:	4010e8bd 			; <UNDEFINED> instruction: 0x4010e8bd
d001ae64:	b85ef7f8 	ldmdalt	lr, {r3, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}^
d001ae68:	fbe8f7ff 	blx	0xcfa58e6e
d001ae6c:	d1ea2800 	mvnle	r2, r0, lsl #16
d001ae70:	f9b6f000 			; <UNDEFINED> instruction: 0xf9b6f000
d001ae74:	bf00e7e7 	svclt	0x0000e7e7
d001ae78:	0000d380 	andeq	sp, r0, r0, lsl #7
d001ae7c:	ffffffc0 			; <UNDEFINED> instruction: 0xffffffc0
d001ae80:	0000d366 	andeq	sp, r0, r6, ror #6

Disassembly of section .text.statement.constprop.0:

d001b1e0 <.text.statement.constprop.0>:
d001b1e0:	4ff0e92d 	svcmi	0x00f0e92d
d001b1e4:	49c4f8df 	stmibmi	r4, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d001b1e8:	6da3447c 	cfstrsvs	mvf4, [r3, #496]!	; 0x1f0
d001b1ec:	8b02ed2d 	blhi	0xd00d66a8
d001b1f0:	bb6bb089 	bllt	0xd1b0741c
d001b1f4:	2592f504 	ldrcs	pc, [r2, #1284]	; 0x504
d001b1f8:	3244f8d5 	subcc	pc, r4, #13959168	; 0xd50000
d001b1fc:	2b203301 	blcs	0xd0827e08
d001b200:	3244f8c5 	subcc	pc, r4, #12910592	; 0xc50000
d001b204:	f8dfd904 			; <UNDEFINED> instruction: 0xf8dfd904
d001b208:	447919a8 	ldrbtmi	r1, [r9], #-2472	; 0xfffff658
d001b20c:	e0674620 	rsb	r4, r7, r0, lsr #12
d001b210:	4620217b 			; <UNDEFINED> instruction: 0x4620217b
d001b214:	fe78f7f7 	mrc2	7, 3, pc, cr8, cr7, {7}
d001b218:	b1f04606 	mvnslt	r4, r6, lsl #12
d001b21c:	3240f8d5 	subcc	pc, r0, #13959168	; 0xd50000
d001b220:	4238f8d5 	eorsmi	pc, r8, #13959168	; 0xd50000
d001b224:	f8c53301 			; <UNDEFINED> instruction: 0xf8c53301
d001b228:	f7ff3240 			; <UNDEFINED> instruction: 0xf7ff3240
d001b22c:	f8d5fe09 			; <UNDEFINED> instruction: 0xf8d5fe09
d001b230:	f8c53240 			; <UNDEFINED> instruction: 0xf8c53240
d001b234:	3b014238 	blcc	0xd006bb1c
d001b238:	3240f8c5 	subcc	pc, r0, #12910592	; 0xc50000
d001b23c:	3974f8df 	ldmdbcc	r4!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d001b240:	f503447b 			; <UNDEFINED> instruction: 0xf503447b
d001b244:	f8d32392 			; <UNDEFINED> instruction: 0xf8d32392
d001b248:	3a012244 	bcc	0xd0063b60
d001b24c:	2244f8c3 	subcs	pc, r4, #12779520	; 0xc30000
d001b250:	ecbdb009 	ldc	0, cr11, [sp], #36	; 0x24
d001b254:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d001b258:	f44f8ff0 			; <UNDEFINED> instruction: 0xf44f8ff0
d001b25c:	46207186 	strtmi	r7, [r0], -r6, lsl #3
d001b260:	fe52f7f7 	mrc2	7, 2, pc, cr2, cr7, {7}
d001b264:	b3504680 	cmplt	r0, #128, 12	; 0x8000000
d001b268:	fa32f7fe 	blx	0xd0cd9268
d001b26c:	46204631 			; <UNDEFINED> instruction: 0x46204631
d001b270:	378ff504 	strcc	pc, [pc, r4, lsl #10]
d001b274:	fd03f7f9 	stc2	7, cr15, [r3, #-996]	; 0xfffffc1c
d001b278:	f7ff4605 			; <UNDEFINED> instruction: 0xf7ff4605
d001b27c:	f240ffb1 	vrecps.f32	d31, d16, d17
d001b280:	4620110d 	strtmi	r1, [r0], -sp, lsl #2
d001b284:	fe40f7f7 	mcr2	7, 2, pc, cr0, cr7, {7}	; <UNPREDICTABLE>
d001b288:	b1a04603 	lsllt	r4, r3, #12
d001b28c:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d001b290:	4680fce7 	strmi	pc, [r0], r7, ror #25
d001b294:	f8d74633 			; <UNDEFINED> instruction: 0xf8d74633
d001b298:	462921b8 			; <UNDEFINED> instruction: 0x462921b8
d001b29c:	f7fa6da0 			; <UNDEFINED> instruction: 0xf7fa6da0
d001b2a0:	f7fffeb5 			; <UNDEFINED> instruction: 0xf7fffeb5
d001b2a4:	4633ff9d 	shadd8mi	pc, r3, sp	; <UNPREDICTABLE>
d001b2a8:	21b8f8d7 			; <UNDEFINED> instruction: 0x21b8f8d7
d001b2ac:	6da04641 	stcvs	6, cr4, [r0, #260]!	; 0x104
d001b2b0:	feacf7fa 	mcr2	7, 5, pc, cr12, cr10, {7}	; <UNPREDICTABLE>
d001b2b4:	f8d7e7c2 			; <UNDEFINED> instruction: 0xf8d7e7c2
d001b2b8:	462921b8 			; <UNDEFINED> instruction: 0x462921b8
d001b2bc:	f44fe7f7 	vst1.64	{d30}, [pc :256], r7
d001b2c0:	46207187 	strtmi	r7, [r0], -r7, lsl #3
d001b2c4:	fe20f7f7 	mcr2	7, 1, pc, cr0, cr7, {7}	; <UNPREDICTABLE>
d001b2c8:	d07a2800 	rsbsle	r2, sl, r0, lsl #16
d001b2cc:	324cf8d5 	subcc	pc, ip, #13959168	; 0xd50000
d001b2d0:	d1082b20 	tstle	r8, r0, lsr #22
d001b2d4:	18e0f8df 	stmiane	r0!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d001b2d8:	08e0f8df 	stmiaeq	r0!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d001b2dc:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d001b2e0:	ffc6f7f4 			; <UNDEFINED> instruction: 0xffc6f7f4
d001b2e4:	f504e7aa 			; <UNDEFINED> instruction: 0xf504e7aa
d001b2e8:	f8d5338f 			; <UNDEFINED> instruction: 0xf8d5338f
d001b2ec:	f8d36250 			; <UNDEFINED> instruction: 0xf8d36250
d001b2f0:	f7fe71b8 			; <UNDEFINED> instruction: 0xf7fe71b8
d001b2f4:	4641f9ed 	strbmi	pc, [r1], -sp, ror #19	; <UNPREDICTABLE>
d001b2f8:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d001b2fc:	f8d5fcc0 			; <UNDEFINED> instruction: 0xf8d5fcc0
d001b300:	4680324c 	strmi	r3, [r0], ip, asr #4
d001b304:	f8c53301 			; <UNDEFINED> instruction: 0xf8c53301
d001b308:	f504324c 			; <UNDEFINED> instruction: 0xf504324c
d001b30c:	f8d52594 			; <UNDEFINED> instruction: 0xf8d52594
d001b310:	2b403254 	blcs	0xd1027c68
d001b314:	f8dfd132 			; <UNDEFINED> instruction: 0xf8dfd132
d001b318:	462018a8 	strtmi	r1, [r0], -r8, lsr #17
d001b31c:	f7f44479 			; <UNDEFINED> instruction: 0xf7f44479
d001b320:	f8dfffa7 			; <UNDEFINED> instruction: 0xf8dfffa7
d001b324:	f8df58a0 			; <UNDEFINED> instruction: 0xf8df58a0
d001b328:	447da8a0 	ldrbtmi	sl, [sp], #-2208	; 0xfffff760
d001b32c:	f50544fa 			; <UNDEFINED> instruction: 0xf50544fa
d001b330:	eb052992 	bl	0xd0165980
d001b334:	462804c6 	strtmi	r0, [r8], -r6, asr #9
d001b338:	324cf8d9 	subcc	pc, ip, #14221312	; 0xd90000
d001b33c:	2492f504 	ldrcs	pc, [r2], #1284	; 0x504
d001b340:	f5043b01 			; <UNDEFINED> instruction: 0xf5043b01
d001b344:	f8c97415 			; <UNDEFINED> instruction: 0xf8c97415
d001b348:	f7f9324c 			; <UNDEFINED> instruction: 0xf7f9324c
d001b34c:	2300fc89 	movwcs	pc, #3209	; 0xc89	; <UNPREDICTABLE>
d001b350:	463a4601 	ldrtmi	r4, [sl], -r1, lsl #12
d001b354:	f7fa6da8 			; <UNDEFINED> instruction: 0xf7fa6da8
d001b358:	f505fe59 			; <UNDEFINED> instruction: 0xf505fe59
d001b35c:	4641328f 	strbmi	r3, [r1], -pc, lsl #5
d001b360:	230046b0 	movwcs	r4, #1712	; 0x6b0
d001b364:	21b8f8d2 			; <UNDEFINED> instruction: 0x21b8f8d2
d001b368:	f7fa6da8 			; <UNDEFINED> instruction: 0xf7fa6da8
d001b36c:	f8d9fe4f 			; <UNDEFINED> instruction: 0xf8d9fe4f
d001b370:	45902250 	ldrmi	r2, [r0, #592]	; 0x250
d001b374:	f8c9d313 			; <UNDEFINED> instruction: 0xf8c9d313
d001b378:	e75f6250 			; <UNDEFINED> instruction: 0xe75f6250
d001b37c:	1c5a441c 	cfldrdne	mvd4, [sl], {28}
d001b380:	f5042301 			; <UNDEFINED> instruction: 0xf5042301
d001b384:	f8c52494 			; <UNDEFINED> instruction: 0xf8c52494
d001b388:	f8842254 			; <UNDEFINED> instruction: 0xf8842254
d001b38c:	f7ff3258 			; <UNDEFINED> instruction: 0xf7ff3258
d001b390:	f8d5ff27 			; <UNDEFINED> instruction: 0xf8d5ff27
d001b394:	3b013254 	blcc	0xd0067cec
d001b398:	3254f8c5 	subscc	pc, r4, #12910592	; 0xc50000
d001b39c:	7923e7c1 	stmdbvc	r3!, {r0, r6, r7, r8, r9, sl, sp, lr, pc}
d001b3a0:	b1636821 	cmnlt	r3, r1, lsr #16
d001b3a4:	338ff505 	orrcc	pc, pc, #20971520	; 0x1400000
d001b3a8:	21b8f8d3 			; <UNDEFINED> instruction: 0x21b8f8d3
d001b3ac:	f8da2300 			; <UNDEFINED> instruction: 0xf8da2300
d001b3b0:	f1080058 	cps	#24
d001b3b4:	34080801 	strcc	r0, [r8], #-2049	; 0xfffff7ff
d001b3b8:	fe28f7fa 	mcr2	7, 1, pc, cr8, cr10, {7}	; <UNPREDICTABLE>
d001b3bc:	463ae7d7 			; <UNDEFINED> instruction: 0x463ae7d7
d001b3c0:	f240e7f4 	vaba.s8	q15, q8, q10
d001b3c4:	46201113 			; <UNDEFINED> instruction: 0x46201113
d001b3c8:	fd9ef7f7 	ldc2	7, cr15, [lr, #988]	; 0x3dc
d001b3cc:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d001b3d0:	f8d580e8 			; <UNDEFINED> instruction: 0xf8d580e8
d001b3d4:	2b20324c 	blcs	0xd0827d0c
d001b3d8:	af7cf43f 	svcge	0x007cf43f
d001b3dc:	27ecf8df 	ubfxcs	pc, pc, #17, #13
d001b3e0:	46202128 	strtmi	r2, [r0], -r8, lsr #2
d001b3e4:	f7f7447a 			; <UNDEFINED> instruction: 0xf7f7447a
d001b3e8:	2800fd9d 	stmdacs	r0, {r0, r2, r3, r4, r7, r8, sl, fp, ip, sp, lr, pc}
d001b3ec:	af26f43f 	svcge	0x0026f43f
d001b3f0:	3240f8d5 	subcc	pc, r0, #13959168	; 0xd50000
d001b3f4:	7238f8d5 	eorsvc	pc, r8, #13959168	; 0xd50000
d001b3f8:	f8d53301 			; <UNDEFINED> instruction: 0xf8d53301
d001b3fc:	f8c56250 			; <UNDEFINED> instruction: 0xf8c56250
d001b400:	f7ff3240 			; <UNDEFINED> instruction: 0xf7ff3240
d001b404:	b978f91b 	ldmdblt	r8!, {r0, r1, r3, r4, r8, fp, ip, sp, lr, pc}^
d001b408:	4620213b 			; <UNDEFINED> instruction: 0x4620213b
d001b40c:	fd7cf7f7 	ldc2l	7, cr15, [ip, #-988]!	; 0xfffffc24
d001b410:	f7feb950 			; <UNDEFINED> instruction: 0xf7feb950
d001b414:	f8dffa49 			; <UNDEFINED> instruction: 0xf8dffa49
d001b418:	f8df27b8 			; <UNDEFINED> instruction: 0xf8df27b8
d001b41c:	213b07b8 	teqcs	fp, r8	; <illegal shifter operand>
d001b420:	4478447a 	ldrbtmi	r4, [r8], #-1146	; 0xfffffb86
d001b424:	fd7ef7f7 	ldc2l	7, cr15, [lr, #-988]!	; 0xfffffc24
d001b428:	47acf8df 	sbfxmi	pc, pc, #17, #13
d001b42c:	f504447c 			; <UNDEFINED> instruction: 0xf504447c
d001b430:	f8d3338f 			; <UNDEFINED> instruction: 0xf8d3338f
d001b434:	6ae391b8 	bvs	0xcf8ffb1c
d001b438:	f0002b3b 			; <UNDEFINED> instruction: 0xf0002b3b
d001b43c:	2202808c 	andcs	r8, r2, #140	; 0x8c
d001b440:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d001b444:	fef8f7fa 	mrc2	7, 7, pc, cr8, cr10, {7}
d001b448:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d001b44c:	fc17f7f9 	ldc2	7, cr15, [r7], {249}	; 0xf9
d001b450:	f8df4680 			; <UNDEFINED> instruction: 0xf8df4680
d001b454:	213b4788 	teqcs	fp, r8, lsl #15
d001b458:	2784f8df 			; <UNDEFINED> instruction: 0x2784f8df
d001b45c:	447a447c 	ldrbtmi	r4, [sl], #-1148	; 0xfffffb84
d001b460:	f7f74620 			; <UNDEFINED> instruction: 0xf7f74620
d001b464:	4620fd5f 			; <UNDEFINED> instruction: 0x4620fd5f
d001b468:	fbfaf7f9 	blx	0xcfed9456
d001b46c:	338ff504 	orrcc	pc, pc, #4, 10	; 0x1000000
d001b470:	f8d34682 			; <UNDEFINED> instruction: 0xf8d34682
d001b474:	6ae351b8 	bvs	0xcf8efb5c
d001b478:	d0012b29 	andle	r2, r1, r9, lsr #22
d001b47c:	fa14f7fe 	blx	0xd055947c
d001b480:	4760f8df 			; <UNDEFINED> instruction: 0x4760f8df
d001b484:	f8df2129 			; <UNDEFINED> instruction: 0xf8df2129
d001b488:	447c2760 	ldrbtmi	r2, [ip], #-1888	; 0xfffff8a0
d001b48c:	4620447a 			; <UNDEFINED> instruction: 0x4620447a
d001b490:	fd48f7f7 	stc2l	7, cr15, [r8, #-988]	; 0xfffffc24
d001b494:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d001b498:	464afbe3 	strbmi	pc, [sl], -r3, ror #23	; <UNPREDICTABLE>
d001b49c:	23004601 	movwcs	r4, #1537	; 0x601
d001b4a0:	f5046da0 			; <UNDEFINED> instruction: 0xf5046da0
d001b4a4:	f7fa2994 			; <UNDEFINED> instruction: 0xf7fa2994
d001b4a8:	f504fdb1 			; <UNDEFINED> instruction: 0xf504fdb1
d001b4ac:	2300328f 	movwcs	r3, #655	; 0x28f
d001b4b0:	f8d24651 			; <UNDEFINED> instruction: 0xf8d24651
d001b4b4:	6da021b8 	stfvss	f2, [r0, #736]!	; 0x2e0
d001b4b8:	fda8f7fa 	stc2	7, cr15, [r8, #1000]!	; 0x3e8
d001b4bc:	2292f504 	addscs	pc, r2, #4, 10	; 0x1000000
d001b4c0:	324cf8d2 	subcc	pc, ip, #13762560	; 0xd20000
d001b4c4:	f8c23301 			; <UNDEFINED> instruction: 0xf8c23301
d001b4c8:	f8d9324c 			; <UNDEFINED> instruction: 0xf8d9324c
d001b4cc:	2b403254 	blcs	0xd1027e24
d001b4d0:	f8dfd144 			; <UNDEFINED> instruction: 0xf8dfd144
d001b4d4:	46201718 			; <UNDEFINED> instruction: 0x46201718
d001b4d8:	f7f44479 			; <UNDEFINED> instruction: 0xf7f44479
d001b4dc:	f8dffec9 			; <UNDEFINED> instruction: 0xf8dffec9
d001b4e0:	447c4710 	ldrbtmi	r4, [ip], #-1808	; 0xfffff8f0
d001b4e4:	2292f504 	addscs	pc, r2, #4, 10	; 0x1000000
d001b4e8:	f8d24620 			; <UNDEFINED> instruction: 0xf8d24620
d001b4ec:	3b01324c 	blcc	0xd0067e24
d001b4f0:	324cf8c2 	subcc	pc, ip, #12713984	; 0xc20000
d001b4f4:	fbb4f7f9 	blx	0xced594e2
d001b4f8:	46012300 	strmi	r2, [r1], -r0, lsl #6
d001b4fc:	6da0462a 	stcvs	6, cr4, [r0, #168]!	; 0xa8
d001b500:	fd84f7fa 	stc2	7, cr15, [r4, #1000]	; 0x3e8
d001b504:	0f00f1b8 	svceq	0x0000f1b8
d001b508:	f504d008 			; <UNDEFINED> instruction: 0xf504d008
d001b50c:	2300328f 	movwcs	r3, #655	; 0x28f
d001b510:	6da04641 	stcvs	6, cr4, [r0, #260]!	; 0x104
d001b514:	21b8f8d2 			; <UNDEFINED> instruction: 0x21b8f8d2
d001b518:	fd78f7fa 	ldc2l	7, cr15, [r8, #-1000]!	; 0xfffffc18
d001b51c:	f8df00f4 			; <UNDEFINED> instruction: 0xf8df00f4
d001b520:	f8df86d4 			; <UNDEFINED> instruction: 0xf8df86d4
d001b524:	46b2b6d4 	ssatmi	fp, #19, r4, asr #13
d001b528:	2492f504 	ldrcs	pc, [r2], #1284	; 0x504
d001b52c:	44fb44f8 	ldrbtmi	r4, [fp], #1272	; 0x4f8
d001b530:	7415f504 	ldrvc	pc, [r5], #-1284	; 0xfffffafc
d001b534:	2992f508 	ldmibcs	r2, {r3, r8, sl, ip, sp, lr, pc}
d001b538:	f8d94444 			; <UNDEFINED> instruction: 0xf8d94444
d001b53c:	45922250 	ldrmi	r2, [r2, #592]	; 0x250
d001b540:	f8d9d31d 			; <UNDEFINED> instruction: 0xf8d9d31d
d001b544:	f8c93240 			; <UNDEFINED> instruction: 0xf8c93240
d001b548:	3b016250 	blcc	0xd0073e90
d001b54c:	7238f8c9 	eorsvc	pc, r8, #13172736	; 0xc90000
d001b550:	3240f8c9 	subcc	pc, r0, #13172736	; 0xc90000
d001b554:	f04fe672 			; <UNDEFINED> instruction: 0xf04fe672
d001b558:	e77a0800 	ldrb	r0, [sl, -r0, lsl #16]!
d001b55c:	1c5a441c 	cfldrdne	mvd4, [sl], {28}
d001b560:	f5042301 			; <UNDEFINED> instruction: 0xf5042301
d001b564:	f8c92494 			; <UNDEFINED> instruction: 0xf8c92494
d001b568:	f8842254 			; <UNDEFINED> instruction: 0xf8842254
d001b56c:	f7ff3258 			; <UNDEFINED> instruction: 0xf7ff3258
d001b570:	f8d9fe37 			; <UNDEFINED> instruction: 0xf8d9fe37
d001b574:	3b013254 	blcc	0xd0067ecc
d001b578:	3254f8c9 	subscc	pc, r4, #13172736	; 0xc90000
d001b57c:	7923e7af 	stmdbvc	r3!, {r0, r1, r2, r3, r5, r7, r8, r9, sl, sp, lr, pc}
d001b580:	b1636821 	cmnlt	r3, r1, lsr #16
d001b584:	338ff508 	orrcc	pc, pc, #8, 10	; 0x2000000
d001b588:	21b8f8d3 			; <UNDEFINED> instruction: 0x21b8f8d3
d001b58c:	f8db2300 			; <UNDEFINED> instruction: 0xf8db2300
d001b590:	f10a0058 	cpsie	f,#24
d001b594:	34080a01 	strcc	r0, [r8], #-2561	; 0xfffff5ff
d001b598:	fd38f7fa 	ldc2	7, cr15, [r8, #-1000]!	; 0xfffffc18
d001b59c:	462ae7cd 	strtmi	lr, [sl], -sp, asr #15
d001b5a0:	f44fe7f4 	vst1.64	{d30}, [pc :256], r4
d001b5a4:	4620718a 	strtmi	r7, [r0], -sl, lsl #3
d001b5a8:	fcaef7f7 	stc2	7, cr15, [lr], #988	; 0x3dc
d001b5ac:	28004607 	stmdacs	r0, {r0, r1, r2, r9, sl, lr}
d001b5b0:	8203f000 	andhi	pc, r3, #0
d001b5b4:	2394f504 	orrscs	pc, r4, #4, 10	; 0x1000000
d001b5b8:	3254f8d3 	subscc	pc, r4, #13828096	; 0xd30000
d001b5bc:	d1032b40 	tstle	r3, r0, asr #22
d001b5c0:	1638f8df 			; <UNDEFINED> instruction: 0x1638f8df
d001b5c4:	e6214479 			; <UNDEFINED> instruction: 0xe6214479
d001b5c8:	2396f504 	orrscs	pc, r6, #4, 10	; 0x1000000
d001b5cc:	329cf8d3 	addscc	pc, ip, #13828096	; 0xd30000
d001b5d0:	7f80f5b3 	svcvc	0x0080f5b3
d001b5d4:	d1039300 	mrsle	r9, SP_svc
d001b5d8:	1624f8df 			; <UNDEFINED> instruction: 0x1624f8df
d001b5dc:	e6154479 			; <UNDEFINED> instruction: 0xe6154479
d001b5e0:	3238f8d5 	eorscc	pc, r8, #13959168	; 0xd50000
d001b5e4:	93012b40 	movwls	r2, #6976	; 0x1b40
d001b5e8:	f8dfd110 			; <UNDEFINED> instruction: 0xf8dfd110
d001b5ec:	f8df1618 			; <UNDEFINED> instruction: 0xf8df1618
d001b5f0:	44790618 	ldrbtmi	r0, [r9], #-1560	; 0xfffff9e8
d001b5f4:	f7f44478 			; <UNDEFINED> instruction: 0xf7f44478
d001b5f8:	f8dffe3b 			; <UNDEFINED> instruction: 0xf8dffe3b
d001b5fc:	9a013610 	bls	0xd0068e44
d001b600:	f503447b 			; <UNDEFINED> instruction: 0xf503447b
d001b604:	f8c32392 			; <UNDEFINED> instruction: 0xf8c32392
d001b608:	e6172238 			; <UNDEFINED> instruction: 0xe6172238
d001b60c:	4600f8df 			; <UNDEFINED> instruction: 0x4600f8df
d001b610:	f8df2128 			; <UNDEFINED> instruction: 0xf8df2128
d001b614:	447c2600 	ldrbtmi	r2, [ip], #-1536	; 0xfffffa00
d001b618:	f504447a 			; <UNDEFINED> instruction: 0xf504447a
d001b61c:	46202394 			; <UNDEFINED> instruction: 0x46202394
d001b620:	3298f8d3 	addscc	pc, r8, #13828096	; 0xd30000
d001b624:	f7f79302 			; <UNDEFINED> instruction: 0xf7f79302
d001b628:	2800fc7d 	stmdacs	r0, {r0, r2, r3, r4, r5, r6, sl, fp, ip, sp, lr, pc}
d001b62c:	2201d0e5 	andcs	sp, r1, #229	; 0xe5
d001b630:	46114620 	ldrmi	r4, [r1], -r0, lsr #12
d001b634:	fe00f7fa 	mcr2	7, 0, pc, cr0, cr10, {7}	; <UNPREDICTABLE>
d001b638:	25dcf8df 	ldrbcs	pc, [ip, #2271]	; 0x8df	; <UNPREDICTABLE>
d001b63c:	46202129 	strtmi	r2, [r0], -r9, lsr #2
d001b640:	f7f7447a 			; <UNDEFINED> instruction: 0xf7f7447a
d001b644:	2800fc6f 	stmdacs	r0, {r0, r1, r2, r3, r5, r6, sl, fp, ip, sp, lr, pc}
d001b648:	f8dfd0d7 			; <UNDEFINED> instruction: 0xf8dfd0d7
d001b64c:	217b25d0 	ldrsbcs	r2, [fp, #-80]!	; 0xffffffb0
d001b650:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d001b654:	fc66f7f7 	stc2l	7, cr15, [r6], #-988	; 0xfffffc24
d001b658:	d0ce2800 	sbcle	r2, lr, r0, lsl #16
d001b65c:	2492f504 	ldrcs	pc, [r2], #1284	; 0x504
d001b660:	f8d42100 			; <UNDEFINED> instruction: 0xf8d42100
d001b664:	f8d48238 			; <UNDEFINED> instruction: 0xf8d48238
d001b668:	f108223c 			; <UNDEFINED> instruction: 0xf108223c
d001b66c:	42930301 	addsmi	r0, r3, #67108864	; 0x4000000
d001b670:	3238f8c4 	eorscc	pc, r8, #196, 16	; 0xc40000
d001b674:	0230f04f 	eorseq	pc, r0, #79	; 0x4f
d001b678:	f8c4bf88 			; <UNDEFINED> instruction: 0xf8c4bf88
d001b67c:	f8df323c 			; <UNDEFINED> instruction: 0xf8df323c
d001b680:	447c45a0 	ldrbtmi	r4, [ip], #-1440	; 0xfffffa60
d001b684:	4508fb02 	strmi	pc, [r8, #-2818]	; 0xfffff4fe
d001b688:	2692f504 	ldrcs	pc, [r2], r4, lsl #10
d001b68c:	2590f505 	ldrcs	pc, [r0, #1285]	; 0x505
d001b690:	7240f896 	subvc	pc, r0, #9830400	; 0x960000
d001b694:	60c7f505 	sbcvs	pc, r7, r5, lsl #10
d001b698:	ffbaf005 			; <UNDEFINED> instruction: 0xffbaf005
d001b69c:	2200230b 	andcs	r2, r0, #738197504	; 0x2c000000
d001b6a0:	f8854641 			; <UNDEFINED> instruction: 0xf8854641
d001b6a4:	46203659 			; <UNDEFINED> instruction: 0x46203659
d001b6a8:	7658f885 	ldrbvc	pc, [r8], -r5, lsl #17	; <UNPREDICTABLE>
d001b6ac:	fa6bf7f9 	blx	0xd1b19698
d001b6b0:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d001b6b4:	f8d6fad5 			; <UNDEFINED> instruction: 0xf8d6fad5
d001b6b8:	f5043240 			; <UNDEFINED> instruction: 0xf5043240
d001b6bc:	ee082294 	mcr	2, 0, r2, cr8, cr4, {4}
d001b6c0:	33010a10 	movwcc	r0, #6672	; 0x1a10
d001b6c4:	3240f8c6 	subcc	pc, r0, #12976128	; 0xc60000
d001b6c8:	f8d22600 			; <UNDEFINED> instruction: 0xf8d22600
d001b6cc:	46373254 			; <UNDEFINED> instruction: 0x46373254
d001b6d0:	1c59441c 	cfldrdne	mvd4, [r9], {28}
d001b6d4:	f5042302 			; <UNDEFINED> instruction: 0xf5042302
d001b6d8:	f8c22494 			; <UNDEFINED> instruction: 0xf8c22494
d001b6dc:	f8841254 			; <UNDEFINED> instruction: 0xf8841254
d001b6e0:	f8df3258 			; <UNDEFINED> instruction: 0xf8df3258
d001b6e4:	447b3540 	ldrbtmi	r3, [fp], #-1344	; 0xfffffac0
d001b6e8:	2595f503 	ldrcs	pc, [r5, #1283]	; 0x503
d001b6ec:	7528f505 	strvc	pc, [r8, #-1285]!	; 0xfffffafb
d001b6f0:	4534f8df 	ldrmi	pc, [r4, #-2271]!	; 0xfffff721
d001b6f4:	6da3447c 	cfstrsvs	mvf4, [r3, #496]!	; 0x1f0
d001b6f8:	6ae3bb23 	bvs	0xcf90a38c
d001b6fc:	d0212b7d 	eorle	r2, r1, sp, ror fp
d001b700:	7f80f5b3 	svcvc	0x0080f5b3
d001b704:	f240d01e 	vqadd.s8	d29, d0, d14
d001b708:	42931215 	addsmi	r1, r3, #1342177281	; 0x50000001
d001b70c:	80f4f040 	rscshi	pc, r4, r0, asr #32
d001b710:	f7f74620 			; <UNDEFINED> instruction: 0xf7f74620
d001b714:	6a63fbd9 	bvs	0xd191a680
d001b718:	4620212d 	strtmi	r2, [r0], -sp, lsr #2
d001b71c:	6aa39303 	bvs	0xce900330
d001b720:	a030f894 	mlasge	r0, r4, r8, pc	; <UNPREDICTABLE>
d001b724:	6b639304 	blvs	0xd190033c
d001b728:	f7f79305 			; <UNDEFINED> instruction: 0xf7f79305
d001b72c:	6ae3fbed 	bvs	0xcf91a6e8
d001b730:	7381f5a3 	orrvc	pc, r1, #683671552	; 0x28c00000
d001b734:	d9792b01 	ldmdble	r9!, {r0, r8, r9, fp, sp}^
d001b738:	14f0f8df 	ldrbtne	pc, [r0], #2271	; 0x8df	; <UNPREDICTABLE>
d001b73c:	44794620 	ldrbtmi	r4, [r9], #-1568	; 0xfffff9e0
d001b740:	fd96f7f4 	ldc2	7, cr15, [r6, #976]	; 0x3d0
d001b744:	44e8f8df 	strbtmi	pc, [r8], #2271	; 0x8df	; <UNPREDICTABLE>
d001b748:	f8df217d 			; <UNDEFINED> instruction: 0xf8df217d
d001b74c:	447c24e8 	ldrbtmi	r2, [ip], #-1256	; 0xfffffb18
d001b750:	4620447a 			; <UNDEFINED> instruction: 0x4620447a
d001b754:	2b96f504 	blcs	0xce5d8b6c
d001b758:	fbe4f7f7 	blx	0xcf95973e
d001b75c:	2294f504 	addscs	pc, r4, #4, 10	; 0x1000000
d001b760:	f8d24620 			; <UNDEFINED> instruction: 0xf8d24620
d001b764:	3b013254 	blcc	0xd00680bc
d001b768:	3254f8c2 	subscc	pc, r4, #12713984	; 0xc20000
d001b76c:	2292f504 	addscs	pc, r2, #4, 10	; 0x1000000
d001b770:	3240f8d2 	subcc	pc, r0, #13762560	; 0xd20000
d001b774:	f8c23b01 			; <UNDEFINED> instruction: 0xf8c23b01
d001b778:	f7f93240 			; <UNDEFINED> instruction: 0xf7f93240
d001b77c:	f504fa71 			; <UNDEFINED> instruction: 0xf504fa71
d001b780:	2300328f 	movwcs	r3, #655	; 0x28f
d001b784:	ee184681 	cfmsub32	mvax4, mvfx4, mvfx8, mvfx1
d001b788:	f8d21a10 			; <UNDEFINED> instruction: 0xf8d21a10
d001b78c:	6da021b8 	stfvss	f2, [r0, #736]!	; 0x2e0
d001b790:	fc3cf7fa 	ldc2	7, cr15, [ip], #-1000	; 0xfffffc18
d001b794:	eb049b00 	bl	0xd014239c
d001b798:	469a05c3 	ldrmi	r0, [sl], r3, asr #11
d001b79c:	2595f505 	ldrcs	pc, [r5, #1285]	; 0x505
d001b7a0:	7527f505 	strvc	pc, [r7, #-1285]!	; 0xfffffafb
d001b7a4:	329cf8db 	addscc	pc, ip, #14352384	; 0xdb0000
d001b7a8:	459a3508 	ldrmi	r3, [sl, #1288]	; 0x508
d001b7ac:	80d6f0c0 	sbcshi	pc, r6, r0, asr #1
d001b7b0:	2f004620 	svccs	0x00004620
d001b7b4:	80f4f000 	rscshi	pc, r4, r0
d001b7b8:	fa52f7f9 	blx	0xd14d97a4
d001b7bc:	6da04601 	stcvs	6, cr4, [r0, #4]!
d001b7c0:	23002400 	movwcs	r2, #1024	; 0x400
d001b7c4:	f7fa463a 			; <UNDEFINED> instruction: 0xf7fa463a
d001b7c8:	f8dffc21 			; <UNDEFINED> instruction: 0xf8dffc21
d001b7cc:	4649546c 	strbmi	r5, [r9], -ip, ror #8
d001b7d0:	f505447d 			; <UNDEFINED> instruction: 0xf505447d
d001b7d4:	6da8338f 	stcvs	3, cr3, [r8, #572]!	; 0x23c
d001b7d8:	a1b8f8d3 			; <UNDEFINED> instruction: 0xa1b8f8d3
d001b7dc:	46522300 	ldrbmi	r2, [r2], -r0, lsl #6
d001b7e0:	fc14f7fa 	ldc2	7, cr15, [r4], {250}	; 0xfa
d001b7e4:	2300b12c 	movwcs	fp, #300	; 0x12c
d001b7e8:	46214652 			; <UNDEFINED> instruction: 0x46214652
d001b7ec:	f7fa6da8 			; <UNDEFINED> instruction: 0xf7fa6da8
d001b7f0:	f8dffc0d 			; <UNDEFINED> instruction: 0xf8dffc0d
d001b7f4:	9d024448 	cfstrsls	mvf4, [r2, #-288]	; 0xfffffee0
d001b7f8:	f504447c 			; <UNDEFINED> instruction: 0xf504447c
d001b7fc:	f5082894 			; <UNDEFINED> instruction: 0xf5082894
d001b800:	f8d87727 			; <UNDEFINED> instruction: 0xf8d87727
d001b804:	42952298 	addsmi	r2, r5, #152, 4	; 0x80000009
d001b808:	80cef0c0 	sbchi	pc, lr, r0, asr #1
d001b80c:	f5049a02 			; <UNDEFINED> instruction: 0xf5049a02
d001b810:	f8c82396 			; <UNDEFINED> instruction: 0xf8c82396
d001b814:	9a002298 	bls	0xd002427c
d001b818:	229cf8c3 	addscs	pc, ip, #12779520	; 0xc30000
d001b81c:	f47f2e00 			; <UNDEFINED> instruction: 0xf47f2e00
d001b820:	f8dfaeec 			; <UNDEFINED> instruction: 0xf8dfaeec
d001b824:	4620141c 			; <UNDEFINED> instruction: 0x4620141c
d001b828:	e6e44479 	uxtab	r4, r4, r9, ror #8
d001b82c:	9020f8d4 	ldrdls	pc, [r0], -r4	; <UNPREDICTABLE>
d001b830:	f1c9b108 			; <UNDEFINED> instruction: 0xf1c9b108
d001b834:	f8df0900 			; <UNDEFINED> instruction: 0xf8df0900
d001b838:	447c440c 	ldrbtmi	r4, [ip], #-1036	; 0xfffffbf4
d001b83c:	f7f74620 			; <UNDEFINED> instruction: 0xf7f74620
d001b840:	f8dffb43 			; <UNDEFINED> instruction: 0xf8dffb43
d001b844:	213a2404 	teqcs	sl, r4, lsl #8
d001b848:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d001b84c:	fb6af7f7 	blx	0xd1ad9832
d001b850:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001b854:	6ea2af77 	mcrvs	15, 5, sl, cr2, cr7, {3}
d001b858:	2396f504 	orrscs	pc, r6, #4, 10	; 0x1000000
d001b85c:	920649fb 	andls	r4, r6, #4112384	; 0x3ec000
d001b860:	f8d34479 			; <UNDEFINED> instruction: 0xf8d34479
d001b864:	9a00329c 	bls	0xd00282dc
d001b868:	e9d49107 	ldmib	r4, {r0, r1, r2, r8, ip, pc}^
d001b86c:	e9d40e16 	ldmib	r4, {r1, r2, r4, r9, sl, fp}^
d001b870:	2400cb18 	strcs	ip, [r0], #-2840	; 0xfffff4e8
d001b874:	d31b429a 	tstle	fp, #-1610612727	; 0xa0000009
d001b878:	4af5b13c 	bmi	0xcfd87d70
d001b87c:	447a9906 	ldrbtmi	r9, [sl], #-2310	; 0xfffff6fa
d001b880:	0e16e9c2 	vnmlaeq.f16	s28, s13, s4	; <UNPREDICTABLE>
d001b884:	cb18e9c2 	blgt	0xd0655f94
d001b888:	f5b36691 			; <UNDEFINED> instruction: 0xf5b36691
d001b88c:	d11f7f80 	tstle	pc, r0, lsl #31
d001b890:	447b4bf0 	ldrbtmi	r4, [fp], #-3056	; 0xfffff410
d001b894:	b94a6d9a 	stmdblt	sl, {r1, r3, r4, r7, r8, sl, fp, sp, lr}^
d001b898:	447a4aef 	ldrbtmi	r4, [sl], #-2799	; 0xfffff511
d001b89c:	9a03659a 	bls	0xd00f4f0c
d001b8a0:	9a0465da 	bls	0xd0135010
d001b8a4:	2a18e9c3 	bcs	0xd0655fb8
d001b8a8:	669a9a05 	ldrvs	r9, [sl], r5, lsl #20
d001b8ac:	e71f3601 	ldr	r3, [pc, -r1, lsl #12]
d001b8b0:	1032f855 	eorsne	pc, r2, r5, asr r8	; <UNPREDICTABLE>
d001b8b4:	d1094549 	tstle	r9, r9, asr #10
d001b8b8:	9905b940 	stmdbls	r5, {r6, r8, fp, ip, sp, pc}
d001b8bc:	f8dd46d3 			; <UNDEFINED> instruction: 0xf8dd46d3
d001b8c0:	2401c010 	strcs	ip, [r1], #-16
d001b8c4:	e00cf8dd 	ldrd	pc, [ip], -sp
d001b8c8:	91069807 	tstls	r6, r7, lsl #16
d001b8cc:	e7d13201 	ldrb	r3, [r1, r1, lsl #4]
d001b8d0:	4ae21c58 	bmi	0xcf8a2a38
d001b8d4:	4315f503 	tstmi	r5, #12582912	; 0xc00000	; <UNPREDICTABLE>
d001b8d8:	3353447a 	cmpcc	r3, #2046820352	; 0x7a000000
d001b8dc:	2196f502 	orrscs	pc, r6, r2, lsl #10
d001b8e0:	03c3eb02 	biceq	lr, r3, #2048	; 0x800
d001b8e4:	328ff502 	addcc	pc, pc, #8388608	; 0x800000
d001b8e8:	029cf8c1 	addseq	pc, ip, #12648448	; 0xc10000
d001b8ec:	21b8f8d2 			; <UNDEFINED> instruction: 0x21b8f8d2
d001b8f0:	9008f8c3 	andls	pc, r8, r3, asr #17
d001b8f4:	e7d9605a 			; <UNDEFINED> instruction: 0xe7d9605a
d001b8f8:	718bf44f 	orrvc	pc, fp, pc, asr #8
d001b8fc:	f7f74620 			; <UNDEFINED> instruction: 0xf7f74620
d001b900:	b318fb03 	tstlt	r8, #3072	; 0xc00	; <UNPREDICTABLE>
d001b904:	213a4ad6 	teqcs	sl, r6	; <illegal shifter operand>
d001b908:	46206a63 	strtmi	r6, [r0], -r3, ror #20
d001b90c:	f8d4447a 			; <UNDEFINED> instruction: 0xf8d4447a
d001b910:	f894b028 			; <UNDEFINED> instruction: 0xf894b028
d001b914:	f8d4a030 			; <UNDEFINED> instruction: 0xf8d4a030
d001b918:	93039034 	movwls	r9, #12340	; 0x3034
d001b91c:	fb02f7f7 	blx	0xd00d9902
d001b920:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001b924:	b167af0f 	cmnlt	r7, pc, lsl #30
d001b928:	2a006da2 	bcs	0xd0036fb8
d001b92c:	4acdd1be 	bmi	0xcf39002c
d001b930:	447a9b03 	ldrbtmi	r9, [sl], #-2819	; 0xfffff4fd
d001b934:	9068f8c4 	rsbls	pc, r8, r4, asr #17
d001b938:	65a265e3 	strvs	r6, [r2, #1507]!	; 0x5e3
d001b93c:	ba18e9c4 	blt	0xd0656054
d001b940:	f504e7b4 			; <UNDEFINED> instruction: 0xf504e7b4
d001b944:	f8d4348f 			; <UNDEFINED> instruction: 0xf8d4348f
d001b948:	e7af71b8 			; <UNDEFINED> instruction: 0xe7af71b8
d001b94c:	fe76f7fe 	mrc2	7, 3, pc, cr6, cr14, {7}
d001b950:	f47f2800 			; <UNDEFINED> instruction: 0xf47f2800
d001b954:	f7ffaecd 			; <UNDEFINED> instruction: 0xf7ffaecd
d001b958:	e6c9fc43 	strb	pc, [r9], r3, asr #24	; <UNPREDICTABLE>
d001b95c:	46412200 	strbmi	r2, [r1], -r0, lsl #4
d001b960:	f10a4620 			; <UNDEFINED> instruction: 0xf10a4620
d001b964:	f7f90a01 			; <UNDEFINED> instruction: 0xf7f90a01
d001b968:	f855f8f3 			; <UNDEFINED> instruction: 0xf855f8f3
d001b96c:	21012c04 	tstcs	r1, r4, lsl #24
d001b970:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d001b974:	f244fc8a 			; <UNDEFINED> instruction: 0xf244fc8a
d001b978:	46202188 	strtmi	r2, [r0], -r8, lsl #3
d001b97c:	f8caf7f9 			; <UNDEFINED> instruction: 0xf8caf7f9
d001b980:	1101f24d 	tstne	r1, sp, asr #4	; <UNPREDICTABLE>
d001b984:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d001b988:	4620f8c5 	strtmi	pc, [r0], -r5, asr #17
d001b98c:	f968f7f9 			; <UNDEFINED> instruction: 0xf968f7f9
d001b990:	46012300 	strmi	r2, [r1], -r0, lsl #6
d001b994:	2c08f855 	stccs	8, cr15, [r8], {85}	; 0x55
d001b998:	f7fa6da0 			; <UNDEFINED> instruction: 0xf7fa6da0
d001b99c:	e701fb37 	smuadx	r1, r7, fp
d001b9a0:	f95ef7f9 			; <UNDEFINED> instruction: 0xf95ef7f9
d001b9a4:	e7104604 	ldr	r4, [r0, -r4, lsl #12]
d001b9a8:	1025f857 	eorne	pc, r5, r7, asr r8	; <UNPREDICTABLE>
d001b9ac:	46522300 	ldrbmi	r2, [r2], -r0, lsl #6
d001b9b0:	35016da0 	strcc	r6, [r1, #-3488]	; 0xfffff260
d001b9b4:	fb2af7fa 	blx	0xd0ad99a6
d001b9b8:	6ae6e723 	bvs	0xcf9d564c
d001b9bc:	7288f46f 	addvc	pc, r8, #1862270976	; 0x6f000000
d001b9c0:	2b0118b3 	blcs	0xd0061c94
d001b9c4:	f240d866 	vadd.i8	<illegal reg q14.5>, q0, q11
d001b9c8:	429e1311 	addsmi	r1, lr, #1140850688	; 0x44000000
d001b9cc:	f8d5d00e 			; <UNDEFINED> instruction: 0xf8d5d00e
d001b9d0:	b1ab324c 			; <UNDEFINED> instruction: 0xb1ab324c
d001b9d4:	447848a4 	ldrbtmi	r4, [r8], #-2212	; 0xfffff75c
d001b9d8:	2392f500 	orrscs	pc, r2, #0, 10
d001b9dc:	3250f8d3 	subscc	pc, r0, #13828096	; 0xd30000
d001b9e0:	7f00f5b3 	svcvc	0x0000f5b3
d001b9e4:	49a1d123 	stmibmi	r1!, {r0, r1, r5, r8, ip, lr, pc}
d001b9e8:	e4794479 	ldrbt	r4, [r9], #-1145	; 0xfffffb87
d001b9ec:	2494f504 	ldrcs	pc, [r4], #1284	; 0x504
d001b9f0:	3254f8d4 	subscc	pc, r4, #212, 16	; 0xd40000
d001b9f4:	499eb93b 	ldmibmi	lr, {r0, r1, r3, r4, r5, r8, fp, ip, sp, pc}
d001b9f8:	489e4479 	ldmmi	lr, {r0, r3, r4, r5, r6, sl, lr}
d001b9fc:	e46f4478 	strbt	r4, [pc], #-1144	; 0xd001ba04
d001ba00:	4479499d 	ldrbtmi	r4, [r9], #-2461	; 0xfffff663
d001ba04:	489de7f9 	ldmmi	sp, {r0, r3, r4, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d001ba08:	44034478 	strmi	r4, [r3], #-1144	; 0xfffffb88
d001ba0c:	2394f503 	orrscs	pc, r4, #12582912	; 0xc00000
d001ba10:	3257f893 	subscc	pc, r7, #9633792	; 0x930000
d001ba14:	d1dd2b02 	bicsle	r2, sp, r2, lsl #22
d001ba18:	2394f500 	orrscs	pc, r4, #0, 10
d001ba1c:	3298f8d3 	addscc	pc, r8, #13828096	; 0xd30000
d001ba20:	7f00f5b3 	svcvc	0x0000f5b3
d001ba24:	4996d102 	ldmibmi	r6, {r1, r8, ip, lr, pc}
d001ba28:	e4594479 	ldrb	r4, [r9], #-1145	; 0xfffffb87
d001ba2c:	4c952701 	ldcmi	7, cr2, [r5], {1}
d001ba30:	4620447c 			; <UNDEFINED> instruction: 0x4620447c
d001ba34:	fa48f7f7 	blx	0xd1259a18
d001ba38:	213b4a93 	teqcs	fp, r3	; <illegal shifter operand>
d001ba3c:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d001ba40:	fa70f7f7 	blx	0xd1c59a24
d001ba44:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d001ba48:	b177f90b 	cmnlt	r7, fp, lsl #18	; <UNPREDICTABLE>
d001ba4c:	2294f504 	addscs	pc, r4, #4, 10	; 0x1000000
d001ba50:	3298f8d2 	addscc	pc, r8, #13762560	; 0xd20000
d001ba54:	f5031c59 			; <UNDEFINED> instruction: 0xf5031c59
d001ba58:	33a63394 			; <UNDEFINED> instruction: 0x33a63394
d001ba5c:	1298f8c2 	addsne	pc, r8, #12713984	; 0xc20000
d001ba60:	0483eb04 	streq	lr, [r3], #2820	; 0xb04
d001ba64:	f7ff6060 			; <UNDEFINED> instruction: 0xf7ff6060
d001ba68:	f504bbe9 			; <UNDEFINED> instruction: 0xf504bbe9
d001ba6c:	f8d22292 			; <UNDEFINED> instruction: 0xf8d22292
d001ba70:	1c593250 	lfmne	f3, 2, [r9], {80}	; 0x50
d001ba74:	4312f503 	tstmi	r2, #12582912	; 0xc00000	; <UNPREDICTABLE>
d001ba78:	f8c2334a 			; <UNDEFINED> instruction: 0xf8c2334a
d001ba7c:	eb041250 	bl	0xd01203c4
d001ba80:	f24004c3 	vshl.s8	q8, <illegal reg q1.5>, q8
d001ba84:	1af31311 	bne	0xcfce06d0
d001ba88:	425e6060 	subsmi	r6, lr, #96	; 0x60
d001ba8c:	7226415e 	eorvc	r4, r6, #-2147483625	; 0x80000017
d001ba90:	bbd4f7ff 	bllt	0xcf559a94
d001ba94:	110ff240 	tstne	pc, r0, asr #4	; <UNPREDICTABLE>
d001ba98:	f7f74620 			; <UNDEFINED> instruction: 0xf7f74620
d001ba9c:	2800fa35 	stmdacs	r0, {r0, r2, r4, r5, r9, fp, ip, sp, lr, pc}
d001baa0:	f504d071 			; <UNDEFINED> instruction: 0xf504d071
d001baa4:	f8942490 			; <UNDEFINED> instruction: 0xf8942490
d001baa8:	2b043634 	blcs	0xd0129380
d001baac:	4c77d11f 	ldfmip	f5, [r7], #-124	; 0xffffff84
d001bab0:	f504447c 			; <UNDEFINED> instruction: 0xf504447c
d001bab4:	46202590 			; <UNDEFINED> instruction: 0x46202590
d001bab8:	1635f895 			; <UNDEFINED> instruction: 0x1635f895
d001babc:	fd8cf7fb 	stc2	7, cr15, [ip, #1004]	; 0x3ec
d001bac0:	1636f895 			; <UNDEFINED> instruction: 0x1636f895
d001bac4:	46202201 	strtmi	r2, [r0], -r1, lsl #4
d001bac8:	f842f7f9 			; <UNDEFINED> instruction: 0xf842f7f9
d001bacc:	3635f895 			; <UNDEFINED> instruction: 0x3635f895
d001bad0:	721af44f 	andsvc	pc, sl, #1325400064	; 0x4f000000
d001bad4:	4303fb02 	movwmi	pc, #15106	; 0x3b02	; <UNPREDICTABLE>
d001bad8:	3368f503 	msrcc	SPSR_f, #12582912	; 0xc00000
d001badc:	f7f98d18 			; <UNDEFINED> instruction: 0xf7f98d18
d001bae0:	f244fb99 	vpadd.i8	d31, d20, d9
d001bae4:	46206108 	strtmi	r6, [r0], -r8, lsl #2
d001bae8:	f814f7f9 			; <UNDEFINED> instruction: 0xf814f7f9
d001baec:	2b05e009 	blcs	0xd0193b18
d001baf0:	4867d11b 	stmdami	r7!, {r0, r1, r3, r4, r8, ip, lr, pc}^
d001baf4:	f5004478 			; <UNDEFINED> instruction: 0xf5004478
d001baf8:	f8932390 			; <UNDEFINED> instruction: 0xf8932390
d001bafc:	f7fc1635 			; <UNDEFINED> instruction: 0xf7fc1635
d001bb00:	4d64f9c1 			; <UNDEFINED> instruction: 0x4d64f9c1
d001bb04:	4a64213b 	bmi	0xd1923ff8
d001bb08:	447a447d 	ldrbtmi	r4, [sl], #-1149	; 0xfffffb83
d001bb0c:	f7f74628 			; <UNDEFINED> instruction: 0xf7f74628
d001bb10:	f505fa09 			; <UNDEFINED> instruction: 0xf505fa09
d001bb14:	f8d32390 			; <UNDEFINED> instruction: 0xf8d32390
d001bb18:	f5b44630 			; <UNDEFINED> instruction: 0xf5b44630
d001bb1c:	d1246f80 	smlawble	r4, r0, pc, r6	; <UNPREDICTABLE>
d001bb20:	4628495e 			; <UNDEFINED> instruction: 0x4628495e
d001bb24:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d001bb28:	2b01bbdb 	blcs	0xd008aa9c
d001bb2c:	4c5cd013 	mrrcmi	0, 1, sp, ip, cr3
d001bb30:	f04f2b03 			; <UNDEFINED> instruction: 0xf04f2b03
d001bb34:	447c0101 	ldrbtmi	r0, [ip], #-257	; 0xfffffeff
d001bb38:	2204bf0c 	andcs	fp, r4, #12, 30	; 0x30
d001bb3c:	46202201 	strtmi	r2, [r0], -r1, lsl #4
d001bb40:	fb7af7fa 	blx	0xd1ed9b32
d001bb44:	2390f504 	orrscs	pc, r0, #4, 10	; 0x1000000
d001bb48:	3634f893 			; <UNDEFINED> instruction: 0x3634f893
d001bb4c:	d1d82b02 	bicsle	r2, r8, r2, lsl #22
d001bb50:	21c0f24b 	biccs	pc, r0, fp, asr #4
d001bb54:	4853e7c7 	ldmdami	r3, {r0, r1, r2, r6, r7, r8, r9, sl, sp, lr, pc}^
d001bb58:	6ac34478 	bvs	0xcf0ecd40
d001bb5c:	d0d02b3b 	sbcsle	r2, r0, fp, lsr fp
d001bb60:	44794951 	ldrbtmi	r4, [r9], #-2385	; 0xfffff6af
d001bb64:	fb84f7f4 	blx	0xce159b3e
d001bb68:	1c62e7cb 	stclne	7, cr14, [r2], #-812	; 0xfffffcd4
d001bb6c:	348ef504 	strcc	pc, [lr], #1284	; 0x504
d001bb70:	f5044628 			; <UNDEFINED> instruction: 0xf5044628
d001bb74:	f8c374c6 			; <UNDEFINED> instruction: 0xf8c374c6
d001bb78:	f7f92630 			; <UNDEFINED> instruction: 0xf7f92630
d001bb7c:	f845f871 			; <UNDEFINED> instruction: 0xf845f871
d001bb80:	f7ff0024 			; <UNDEFINED> instruction: 0xf7ff0024
d001bb84:	213bbb5b 	teqcs	fp, fp, asr fp
d001bb88:	f7f74620 			; <UNDEFINED> instruction: 0xf7f74620
d001bb8c:	2800f9bd 	stmdacs	r0, {r0, r2, r3, r4, r5, r7, r8, fp, ip, sp, lr, pc}
d001bb90:	ab54f47f 	blge	0xd1558d94
d001bb94:	fe88f7fd 	mcr2	7, 4, pc, cr8, cr13, {7}	; <UNPREDICTABLE>
d001bb98:	48454a44 	stmdami	r5, {r2, r6, r9, fp, lr}^
d001bb9c:	447a213b 	ldrbtmi	r2, [sl], #-315	; 0xfffffec5
d001bba0:	f7f74478 			; <UNDEFINED> instruction: 0xf7f74478
d001bba4:	f7fff9bf 			; <UNDEFINED> instruction: 0xf7fff9bf
d001bba8:	bf00bb49 	svclt	0x0000bb49
d001bbac:	0000cfdc 	ldrdeq	ip, [r0], -ip	; <UNPREDICTABLE>
d001bbb0:	ffffae18 			; <UNDEFINED> instruction: 0xffffae18
d001bbb4:	0000cf84 	andeq	ip, r0, r4, lsl #31
d001bbb8:	fffffbf7 			; <UNDEFINED> instruction: 0xfffffbf7
d001bbbc:	0000cee6 	andeq	ip, r0, r6, ror #29
d001bbc0:	fffffbcd 			; <UNDEFINED> instruction: 0xfffffbcd
d001bbc4:	0000ce9a 	muleq	r0, sl, lr
d001bbc8:	0000ce98 	muleq	r0, r8, lr
d001bbcc:	fffffb2a 			; <UNDEFINED> instruction: 0xfffffb2a
d001bbd0:	fffffb05 			; <UNDEFINED> instruction: 0xfffffb05
d001bbd4:	0000cda2 	andeq	ip, r0, r2, lsr #27
d001bbd8:	0000cd98 	muleq	r0, r8, sp
d001bbdc:	0000cd68 	andeq	ip, r0, r8, ror #26
d001bbe0:	fffffaea 			; <UNDEFINED> instruction: 0xfffffaea
d001bbe4:	0000cd3a 	andeq	ip, r0, sl, lsr sp
d001bbe8:	fffffadd 			; <UNDEFINED> instruction: 0xfffffadd
d001bbec:	fffffa11 			; <UNDEFINED> instruction: 0xfffffa11
d001bbf0:	0000cce2 	andeq	ip, r0, r2, ror #25
d001bbf4:	0000cc98 	muleq	r0, r8, ip
d001bbf8:	0000cc96 	muleq	r0, r6, ip
d001bbfc:	fffff925 			; <UNDEFINED> instruction: 0xfffff925
d001bc00:	fffff9a9 			; <UNDEFINED> instruction: 0xfffff9a9
d001bc04:	fffff9af 			; <UNDEFINED> instruction: 0xfffff9af
d001bc08:	0000cbd0 	ldrdeq	ip, [r0], -r0
d001bc0c:	0000cbc4 	andeq	ip, r0, r4, asr #23
d001bc10:	0000cbae 	andeq	ip, r0, lr, lsr #23
d001bc14:	fffff9b7 			; <UNDEFINED> instruction: 0xfffff9b7
d001bc18:	fffff9a9 			; <UNDEFINED> instruction: 0xfffff9a9
d001bc1c:	fffff9bc 			; <UNDEFINED> instruction: 0xfffff9bc
d001bc20:	0000cb42 	andeq	ip, r0, r2, asr #22
d001bc24:	0000cade 	ldrdeq	ip, [r0], -lr
d001bc28:	0000cad0 	ldrdeq	ip, [r0], -r0
d001bc2c:	fffff8f4 			; <UNDEFINED> instruction: 0xfffff8f4
d001bc30:	0000ca76 	andeq	ip, r0, r6, ror sl
d001bc34:	fffff95f 			; <UNDEFINED> instruction: 0xfffff95f
d001bc38:	0000c9f4 	strdeq	ip, [r0], -r4
d001bc3c:	0000c9cc 	andeq	ip, r0, ip, asr #19
d001bc40:	fffff8a6 			; <UNDEFINED> instruction: 0xfffff8a6
d001bc44:	0000c98a 	andeq	ip, r0, sl, lsl #19
d001bc48:	fffff80d 			; <UNDEFINED> instruction: 0xfffff80d
d001bc4c:	fffff620 			; <UNDEFINED> instruction: 0xfffff620
d001bc50:	0000c946 	andeq	ip, r0, r6, asr #18
d001bc54:	0000c932 	andeq	ip, r0, r2, lsr r9
d001bc58:	fffff6eb 			; <UNDEFINED> instruction: 0xfffff6eb
d001bc5c:	0000c8ec 	andeq	ip, r0, ip, ror #17
d001bc60:	fffff769 			; <UNDEFINED> instruction: 0xfffff769
d001bc64:	fffff75e 			; <UNDEFINED> instruction: 0xfffff75e
d001bc68:	0000c7ee 	andeq	ip, r0, lr, ror #15
d001bc6c:	fffff727 			; <UNDEFINED> instruction: 0xfffff727
d001bc70:	fffff4bc 			; <UNDEFINED> instruction: 0xfffff4bc
d001bc74:	0000c7c8 	andeq	ip, r0, r8, asr #15
d001bc78:	fffff49a 			; <UNDEFINED> instruction: 0xfffff49a
d001bc7c:	0000c7bc 			; <UNDEFINED> instruction: 0x0000c7bc
d001bc80:	fffff6d0 			; <UNDEFINED> instruction: 0xfffff6d0
d001bc84:	0000c794 	muleq	r0, r4, r7
d001bc88:	fffff6f3 			; <UNDEFINED> instruction: 0xfffff6f3
d001bc8c:	0000c714 	andeq	ip, r0, r4, lsl r7
d001bc90:	0000c6d0 	ldrdeq	ip, [r0], -r0
d001bc94:	0000c6bc 			; <UNDEFINED> instruction: 0x0000c6bc
d001bc98:	fffff678 			; <UNDEFINED> instruction: 0xfffff678
d001bc9c:	fffff678 			; <UNDEFINED> instruction: 0xfffff678
d001bca0:	0000c68e 	andeq	ip, r0, lr, lsl #13
d001bca4:	0000c66c 	andeq	ip, r0, ip, ror #12
d001bca8:	fffff5f4 			; <UNDEFINED> instruction: 0xfffff5f4
d001bcac:	fffff61f 			; <UNDEFINED> instruction: 0xfffff61f
d001bcb0:	0000c624 	andeq	ip, r0, r4, lsr #12

Disassembly of section .text.initialize_static_buffer.constprop.0:

d001bce8 <.text.initialize_static_buffer.constprop.0>:
d001bce8:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d001bcec:	481a4604 	ldmdami	sl, {r2, r9, sl, lr}
d001bcf0:	f5004478 			; <UNDEFINED> instruction: 0xf5004478
d001bcf4:	f8d3337f 			; <UNDEFINED> instruction: 0xf8d3337f
d001bcf8:	f5c55224 			; <UNDEFINED> instruction: 0xf5c55224
d001bcfc:	42a313be 	adcmi	r1, r3, #-134217726	; 0xf8000002
d001bd00:	4916d206 	ldmdbmi	r6, {r1, r2, r9, ip, lr, pc}
d001bd04:	f7f44479 			; <UNDEFINED> instruction: 0xf7f44479
d001bd08:	2000fab3 			; <UNDEFINED> instruction: 0x2000fab3
d001bd0c:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d001bd10:	804cf8df 	ldrdhi	pc, [ip], #-143	; 0xffffff71
d001bd14:	00a400ad 	adceq	r0, r4, sp, lsr #1
d001bd18:	44f84606 	ldrbtmi	r4, [r8], #1542	; 0x606
d001bd1c:	b1046db0 			; <UNDEFINED> instruction: 0xb1046db0
d001bd20:	4b10b150 	blmi	0xd0448268
d001bd24:	fab02200 	blx	0xcec2452c
d001bd28:	447bf080 	ldrbtmi	pc, [fp], #-128	; 0xffffff80	; <UNPREDICTABLE>
d001bd2c:	f5030940 			; <UNDEFINED> instruction: 0xf5030940
d001bd30:	f883337f 			; <UNDEFINED> instruction: 0xf883337f
d001bd34:	e7e92220 	strb	r2, [r9, r0, lsr #4]!
d001bd38:	6f80f5b4 	svcvs	0x0080f5b4
d001bd3c:	46294627 	strtmi	r4, [r9], -r7, lsr #12
d001bd40:	bf284642 	svclt	0x00284642
d001bd44:	6780f44f 	strvs	pc, [r0, pc, asr #8]
d001bd48:	463b2001 	ldrtmi	r2, [fp], -r1
d001bd4c:	1be4443d 	blne	0xcf92ce48
d001bd50:	fe48f7f8 	mcr2	7, 2, pc, cr8, cr8, {7}	; <UNPREDICTABLE>
d001bd54:	bf00e7e2 	svclt	0x0000e7e2
d001bd58:	0000c4d4 	ldrdeq	ip, [r0], -r4
d001bd5c:	ffffffac 			; <UNDEFINED> instruction: 0xffffffac
d001bd60:	000039ae 	andeq	r3, r0, lr, lsr #19
d001bd64:	0000c49a 	muleq	r0, sl, r4

Disassembly of section .text.global_declaration.constprop.0:

d001bee8 <.text.global_declaration.constprop.0>:
d001bee8:	e92db084 	push	{r2, r7, ip, sp, pc}
d001beec:	b08b4ff0 	strdlt	r4, [fp], r0
d001bef0:	b42cf8df 	strtlt	pc, [ip], #-2271	; 0xfffff721
d001bef4:	44fbac14 	ldrbtmi	sl, [fp], #3092	; 0xc14
d001bef8:	f89d9004 			; <UNDEFINED> instruction: 0xf89d9004
d001befc:	9f1d6070 	svcls	0x001d6070
d001bf00:	000fe884 	andeq	lr, pc, r4, lsl #17
d001bf04:	46019a15 			; <UNDEFINED> instruction: 0x46019a15
d001bf08:	f8dd4658 			; <UNDEFINED> instruction: 0xf8dd4658
d001bf0c:	9205a05c 	andls	sl, r5, #92	; 0x5c
d001bf10:	9060f8dd 	ldrdls	pc, [r0], #-141	; 0xffffff73	; <UNPREDICTABLE>
d001bf14:	8068f89d 	mlshi	r8, sp, r8, pc	; <UNPREDICTABLE>
d001bf18:	f7f49d1b 			; <UNDEFINED> instruction: 0xf7f49d1b
d001bf1c:	9a05fce2 	bls	0xd019b2ac
d001bf20:	99044604 	stmdbls	r4, {r2, r9, sl, lr}
d001bf24:	f7f44658 			; <UNDEFINED> instruction: 0xf7f44658
d001bf28:	2800fc98 	stmdacs	r0, {r3, r4, r7, sl, fp, ip, sp, lr, pc}
d001bf2c:	9a059904 	bls	0xd0182344
d001bf30:	4bfcdb0f 	blmi	0xcff52b74
d001bf34:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d001bf38:	4afbb932 	bmi	0xcff0a408
d001bf3c:	447a669d 	ldrbtmi	r6, [sl], #-1693	; 0xfffff963
d001bf40:	9818e9c3 	ldmdals	r8, {r0, r1, r6, r7, r8, fp, sp, lr, pc}
d001bf44:	2a16e9c3 	bcs	0xd05d6658
d001bf48:	e8bdb00b 	pop	{r0, r1, r3, ip, sp, pc}
d001bf4c:	b0044ff0 	strdlt	r4, [r4], -r0
d001bf50:	46584770 			; <UNDEFINED> instruction: 0x46584770
d001bf54:	91049205 	tstls	r4, r5, lsl #4
d001bf58:	fc5af7f4 	mrrc2	7, 15, pc, sl, cr4	; <UNPREDICTABLE>
d001bf5c:	dae82800 	ble	0xcfa25f64
d001bf60:	99042c00 	stmdbls	r4, {sl, fp, sp}
d001bf64:	db0a9a05 	blle	0xd02c2780
d001bf68:	f89b2038 			; <UNDEFINED> instruction: 0xf89b2038
d001bf6c:	fb003008 	blx	0xd0027f96
d001bf70:	f504b404 			; <UNDEFINED> instruction: 0xf504b404
d001bf74:	f894347f 			; <UNDEFINED> instruction: 0xf894347f
d001bf78:	42980251 	addsmi	r0, r8, #268435461	; 0x10000005
d001bf7c:	4cebd0d9 	stclmi	0, cr13, [fp], #868	; 0x364
d001bf80:	447c9205 	ldrbtmi	r9, [ip], #-517	; 0xfffffdfb
d001bf84:	46209104 	strtmi	r9, [r0], -r4, lsl #2
d001bf88:	fd07f7f4 	stc2	7, cr15, [r7, #-976]	; 0xfffffc30
d001bf8c:	9a059904 	bls	0xd01823a4
d001bf90:	d1ce2800 	bicle	r2, lr, r0, lsl #16
d001bf94:	f7f44620 			; <UNDEFINED> instruction: 0xf7f44620
d001bf98:	2800fce2 	stmdacs	r0, {r1, r5, r6, r7, sl, fp, ip, sp, lr, pc}
d001bf9c:	f504d1c9 			; <UNDEFINED> instruction: 0xf504d1c9
d001bfa0:	f8d33367 			; <UNDEFINED> instruction: 0xf8d33367
d001bfa4:	2b8031c4 	blcs	0xce0286bc
d001bfa8:	6da3d10a 	stfvsd	f5, [r3, #40]!	; 0x28
d001bfac:	d1cb2b00 	bicle	r2, fp, r0, lsl #22
d001bfb0:	447b4bdf 	ldrbtmi	r4, [fp], #-3039	; 0xfffff421
d001bfb4:	e9c466a5 	stmib	r4, {r0, r2, r5, r7, r9, sl, sp, lr}^
d001bfb8:	e9c43a16 	stmib	r4, {r1, r2, r4, r9, fp, ip, sp}^
d001bfbc:	e7c39818 	bfi	r9, r8, (invalid: 16:3)
d001bfc0:	4620215b 			; <UNDEFINED> instruction: 0x4620215b
d001bfc4:	ffa0f7f6 			; <UNDEFINED> instruction: 0xffa0f7f6
d001bfc8:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d001bfcc:	b12f80ae 			; <UNDEFINED> instruction: 0xb12f80ae
d001bfd0:	2b006da3 	blcs	0xd0037664
d001bfd4:	4bd7d1b8 	blmi	0xcf6106bc
d001bfd8:	e7eb447b 			; <UNDEFINED> instruction: 0xe7eb447b
d001bfdc:	d0062e05 	andle	r2, r6, r5, lsl #28
d001bfe0:	6da3b12e 	stfvsd	f3, [r3, #184]!	; 0xb8
d001bfe4:	d1af2b00 			; <UNDEFINED> instruction: 0xd1af2b00
d001bfe8:	447b4bd3 	ldrbtmi	r4, [fp], #-3027	; 0xfffff42d
d001bfec:	4bd3e7e2 	blmi	0xcf515f7c
d001bff0:	6ad8447b 	bvs	0xcf62d1e4
d001bff4:	c024f8d3 	ldrdgt	pc, [r4], -r3	; <UNPREDICTABLE>
d001bff8:	7081f5a0 	addvc	pc, r1, r0, lsr #11
d001bffc:	f8936a9c 			; <UNDEFINED> instruction: 0xf8936a9c
d001c000:	28011030 	stmdacs	r1, {r4, r5, ip}
d001c004:	d8016b5a 	stmdale	r1, {r1, r3, r4, r6, r8, r9, fp, sp, lr}
d001c008:	b9606a18 	stmdblt	r0!, {r3, r4, r9, fp, sp, lr}^
d001c00c:	447b4bcc 	ldrbtmi	r4, [fp], #-3020	; 0xfffff434
d001c010:	28006d98 	stmdacs	r0, {r3, r4, r7, r8, sl, fp, sp, lr}
d001c014:	48cbd198 	stmiami	fp, {r3, r4, r7, r8, ip, lr, pc}^
d001c018:	669a4478 			; <UNDEFINED> instruction: 0x669a4478
d001c01c:	0c16e9c3 			; <UNDEFINED> instruction: 0x0c16e9c3
d001c020:	4118e9c3 	tstmi	r8, r3, asr #19
d001c024:	b946e790 	stmdblt	r6, {r4, r7, r8, r9, sl, sp, lr, pc}^
d001c028:	2f80f5b0 	svccs	0x0080f5b0
d001c02c:	6d98d921 	vldrvs.16	s26, [r8, #66]	; 0x42	; <UNPREDICTABLE>
d001c030:	d1892800 	orrle	r2, r9, r0, lsl #16
d001c034:	447848c4 	ldrbtmi	r4, [r8], #-2244	; 0xfffff73c
d001c038:	2501e7ef 	strcs	lr, [r1, #-2031]	; 0xfffff811
d001c03c:	447b4bc3 	ldrbtmi	r4, [fp], #-3011	; 0xfffff43d
d001c040:	337ff503 	cmncc	pc, #12582912	; 0xc00000	; <UNPREDICTABLE>
d001c044:	321cf8d3 	andscc	pc, ip, #13828096	; 0xd30000
d001c048:	3303b916 	movwcc	fp, #14614	; 0x3916
d001c04c:	0303f023 	movweq	pc, #12323	; 0x3023	; <UNPREDICTABLE>
d001c050:	1f80f5b3 	svcne	0x0080f5b3
d001c054:	4345d804 	movtmi	sp, #22532	; 0x5804
d001c058:	1380f5c3 	orrne	pc, r0, #817889280	; 0x30c00000
d001c05c:	d90a429d 	stmdble	sl, {r0, r2, r3, r4, r7, r9, lr}
d001c060:	447b4bbb 	ldrbtmi	r4, [fp], #-3003	; 0xfffff445
d001c064:	28006d98 	stmdacs	r0, {r3, r4, r7, r8, sl, fp, sp, lr}
d001c068:	af6ef47f 	svcge	0x006ef47f
d001c06c:	447848b9 	ldrbtmi	r4, [r8], #-2233	; 0xfffff747
d001c070:	2504e7d3 	strcs	lr, [r4, #-2003]	; 0xfffff82d
d001c074:	48b8e7e2 	ldmmi	r8!, {r1, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d001c078:	90044478 	andls	r4, r4, r8, ror r4
d001c07c:	ff24f7f6 			; <UNDEFINED> instruction: 0xff24f7f6
d001c080:	215d4ab6 	ldrhcs	r4, [sp, #-166]	; 0xffffff5a
d001c084:	447a9804 	ldrbtmi	r9, [sl], #-2052	; 0xfffff7fc
d001c088:	ff4cf7f6 			; <UNDEFINED> instruction: 0xff4cf7f6
d001c08c:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001c090:	2e00af5b 	mcrcs	15, 0, sl, cr0, cr11, {2}
d001c094:	ea4fd14c 	b	0xd14105cc
d001c098:	26080a95 			; <UNDEFINED> instruction: 0x26080a95
d001c09c:	82c0f8df 	sbchi	pc, r0, #14614528	; 0xdf0000
d001c0a0:	44f8213d 	ldrbtmi	r2, [r8], #317	; 0x13d
d001c0a4:	397ff508 	ldmdbcc	pc!, {r3, r8, sl, ip, sp, lr, pc}^	; <UNPREDICTABLE>
d001c0a8:	f8d94640 			; <UNDEFINED> instruction: 0xf8d94640
d001c0ac:	93043224 	movwls	r3, #16932	; 0x4224
d001c0b0:	ff2af7f6 			; <UNDEFINED> instruction: 0xff2af7f6
d001c0b4:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d001c0b8:	1ff380c9 	svcne	0x00f380c9
d001c0bc:	d8552b01 	ldmdale	r5, {r0, r8, r9, fp, sp}^
d001c0c0:	3224f8d9 	eorcc	pc, r4, #14221312	; 0xd90000
d001c0c4:	13bef5c3 			; <UNDEFINED> instruction: 0x13bef5c3
d001c0c8:	d2344553 	eorsle	r4, r4, #348127232	; 0x14c00000
d001c0cc:	ff56f7f7 			; <UNDEFINED> instruction: 0xff56f7f7
d001c0d0:	24002300 	strcs	r2, [r0], #-768	; 0xfffffd00
d001c0d4:	828cf8df 	addhi	pc, ip, #14614528	; 0xdf0000
d001c0d8:	4aa3213b 	bmi	0xce8e45cc
d001c0dc:	930244f8 	movwls	r4, #9464	; 0x24f8
d001c0e0:	4640447a 			; <UNDEFINED> instruction: 0x4640447a
d001c0e4:	ff1ef7f6 			; <UNDEFINED> instruction: 0xff1ef7f6
d001c0e8:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001c0ec:	1ff2af2d 	svcne	0x00f2af2d
d001c0f0:	2a019b02 	bcs	0xd0082d00
d001c0f4:	8105f200 	mrshi	pc, SP_usr	; <UNPREDICTABLE>
d001c0f8:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d001c0fc:	2e0880a9 	cdpcs	0, 0, cr8, cr8, cr9, {5}
d001c100:	f508d108 			; <UNDEFINED> instruction: 0xf508d108
d001c104:	f8d8387f 			; <UNDEFINED> instruction: 0xf8d8387f
d001c108:	32032218 	andcc	r2, r3, #24, 4	; 0x80000001
d001c10c:	0203f022 	andeq	pc, r3, #34	; 0x22
d001c110:	2218f8c8 	andscs	pc, r8, #200, 16	; 0xc80000
d001c114:	447a4a95 	ldrbtmi	r4, [sl], #-2709	; 0xfffff56b
d001c118:	327ff502 	rsbscc	pc, pc, #8388608	; 0x800000
d001c11c:	8218f8d2 	andshi	pc, r8, #13762560	; 0xd20000
d001c120:	0105eb08 	tsteq	r5, r8, lsl #22
d001c124:	1218f8c2 	andsne	pc, r8, #12713984	; 0xc20000
d001c128:	4605e0a7 	strmi	lr, [r5], -r7, lsr #1
d001c12c:	e7b54682 	ldr	r4, [r5, r2, lsl #13]!
d001c130:	260746aa 	strcs	r4, [r7], -sl, lsr #13
d001c134:	4650e7b2 			; <UNDEFINED> instruction: 0x4650e7b2
d001c138:	fdd6f7ff 	ldc2l	7, cr15, [r6, #1020]	; 0x3fc
d001c13c:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001c140:	1ff2af03 	svcne	0x00f2af03
d001c144:	465021ff 			; <UNDEFINED> instruction: 0x465021ff
d001c148:	41534253 	cmpmi	r3, r3, asr r2
d001c14c:	93002200 	movwls	r2, #512	; 0x200
d001c150:	f7fe2301 			; <UNDEFINED> instruction: 0xf7fe2301
d001c154:	f899f8bd 			; <UNDEFINED> instruction: 0xf899f8bd
d001c158:	2b003220 	blcs	0xd00289e0
d001c15c:	f8d9d0b9 			; <UNDEFINED> instruction: 0xf8d9d0b9
d001c160:	44533224 	ldrbmi	r3, [r3], #-548	; 0xfffffddc
d001c164:	3224f8c9 	eorcc	pc, r4, #13172736	; 0xc90000
d001c168:	e7b22301 	ldr	r2, [r2, r1, lsl #6]!
d001c16c:	4640212d 	strbmi	r2, [r0], -sp, lsr #2
d001c170:	fecaf7f6 	mcr2	7, 6, pc, cr10, cr6, {7}	; <UNPREDICTABLE>
d001c174:	3024f8d8 	ldrdcc	pc, [r4], -r8	; <UNPREDICTABLE>
d001c178:	f44f4681 	vst1.32	{d20-d22}, [pc], r1
d001c17c:	9305718d 	movwls	r7, #20877	; 0x518d
d001c180:	f8d84640 			; <UNDEFINED> instruction: 0xf8d84640
d001c184:	f8d83028 			; <UNDEFINED> instruction: 0xf8d83028
d001c188:	9306402c 	movwls	r4, #24620	; 0x602c
d001c18c:	3030f898 	mlascc	r0, r8, r8, pc	; <UNPREDICTABLE>
d001c190:	b206e9d8 	andlt	lr, r6, #216, 18	; 0x360000
d001c194:	f8d89307 			; <UNDEFINED> instruction: 0xf8d89307
d001c198:	92093034 	andls	r3, r9, #52	; 0x34
d001c19c:	f7f69308 			; <UNDEFINED> instruction: 0xf7f69308
d001c1a0:	9a09feb3 	bls	0xd029bc74
d001c1a4:	4640b120 	strbmi	fp, [r0], -r0, lsr #2
d001c1a8:	fc4ef7f7 	mcrr2	7, 15, pc, lr, cr7	; <UNPREDICTABLE>
d001c1ac:	e00d4604 	and	r4, sp, r4, lsl #12
d001c1b0:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d001c1b4:	d113429c 			; <UNDEFINED> instruction: 0xd113429c
d001c1b8:	46404659 			; <UNDEFINED> instruction: 0x46404659
d001c1bc:	fbedf7f4 	blx	0xcfb9a196
d001c1c0:	d0392800 	eorsle	r2, r9, r0, lsl #16
d001c1c4:	46406a04 	strbmi	r6, [r0], -r4, lsl #20
d001c1c8:	fe7ef7f6 	mrc2	7, 3, pc, cr14, cr6, {7}
d001c1cc:	0f00f1b9 	svceq	0x0000f1b9
d001c1d0:	4264d000 	rsbmi	sp, r4, #0
d001c1d4:	f04f2e05 			; <UNDEFINED> instruction: 0xf04f2e05
d001c1d8:	bf080300 	svclt	0x00080300
d001c1dc:	e779b2e4 	ldrb	fp, [r9, -r4, ror #5]!
d001c1e0:	7481f5a4 	strvc	pc, [r1], #1444	; 0x5a4
d001c1e4:	d8272c01 	stmdale	r7!, {r0, sl, fp, sp}
d001c1e8:	21014602 	tstcs	r1, r2, lsl #12
d001c1ec:	f7f64640 			; <UNDEFINED> instruction: 0xf7f64640
d001c1f0:	f8d8ff23 			; <UNDEFINED> instruction: 0xf8d8ff23
d001c1f4:	2b003058 	blcs	0xd002835c
d001c1f8:	aea6f47f 	mcrge	4, 5, pc, cr6, cr15, {3}	; <UNPREDICTABLE>
d001c1fc:	4300f110 	movwmi	pc, #272	; 0x110	; <UNPREDICTABLE>
d001c200:	f1419302 			; <UNDEFINED> instruction: 0xf1419302
d001c204:	93030300 	movwls	r0, #13056	; 0x3300
d001c208:	3402e9dd 	strcc	lr, [r2], #-2525	; 0xfffff623
d001c20c:	bf082c01 	svclt	0x00082c01
d001c210:	4f00f1b3 	svcmi	0x0000f1b3
d001c214:	4b56d3ca 	blmi	0xd15d1144
d001c218:	f8c8447b 			; <UNDEFINED> instruction: 0xf8c8447b
d001c21c:	9b053058 	blls	0xd0168384
d001c220:	305cf8c8 	subscc	pc, ip, r8, asr #17
d001c224:	f8c89b06 			; <UNDEFINED> instruction: 0xf8c89b06
d001c228:	9b073060 	blls	0xd01e83b0
d001c22c:	3064f8c8 	rsbcc	pc, r4, r8, asr #17
d001c230:	f8c89b08 			; <UNDEFINED> instruction: 0xf8c89b08
d001c234:	e6873068 	str	r3, [r7], r8, rrx
d001c238:	484f494e 	stmdami	pc, {r1, r2, r3, r6, r8, fp, lr}^	; <UNPREDICTABLE>
d001c23c:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d001c240:	e8bdb00b 	pop	{r0, r1, r3, ip, sp, pc}
d001c244:	b0044ff0 	strdlt	r4, [r4], -r0
d001c248:	b812f7f4 	ldmdalt	r2, {r2, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}
d001c24c:	e7c14604 	strb	r4, [r1, r4, lsl #12]
d001c250:	d1082e08 	tstle	r8, r8, lsl #28
d001c254:	387ff508 	ldmdacc	pc!, {r3, r8, sl, ip, sp, lr, pc}^	; <UNPREDICTABLE>
d001c258:	221cf8d8 	andscs	pc, ip, #216, 16	; 0xd80000
d001c25c:	f0223203 			; <UNDEFINED> instruction: 0xf0223203
d001c260:	f8c80203 			; <UNDEFINED> instruction: 0xf8c80203
d001c264:	4a45221c 	bmi	0xd1164adc
d001c268:	f502447a 			; <UNDEFINED> instruction: 0xf502447a
d001c26c:	f8d2327f 			; <UNDEFINED> instruction: 0xf8d2327f
d001c270:	eb08821c 	bl	0xd023cae8
d001c274:	f8c20105 			; <UNDEFINED> instruction: 0xf8c20105
d001c278:	4a41121c 	bmi	0xd1060af0
d001c27c:	fa5f2b00 	blx	0xd17e6e84
d001c280:	447af987 	ldrbtmi	pc, [sl], #-2439	; 0xfffff679	; <UNPREDICTABLE>
d001c284:	f04fbf08 			; <UNDEFINED> instruction: 0xf04fbf08
d001c288:	2e080a00 	vmlacs.f32	s0, s16, s0
d001c28c:	3167f502 	msrcc	SPSR_sxc, r2, lsl #10
d001c290:	b008f892 	mullt	r8, r2, r8
d001c294:	f8d1b2da 			; <UNDEFINED> instruction: 0xf8d1b2da
d001c298:	920201c4 	andls	r0, r2, #196, 2	; 0x31
d001c29c:	0c01f100 	stfeqd	f7, [r1], {-0}
d001c2a0:	c1c4f8c1 	bicgt	pc, r4, r1, asr #17
d001c2a4:	08add137 	stmiaeq	sp!, {r0, r1, r2, r4, r5, r8, ip, lr, pc}
d001c2a8:	223c4f36 	eorscs	r4, ip, #54, 30	; 0xd8
d001c2ac:	447f2100 	ldrbtmi	r2, [pc], #-256	; 0xd001c2b4
d001c2b0:	7700fb02 	strvc	pc, [r0, -r2, lsl #22]
d001c2b4:	375ff507 	ldrbcc	pc, [pc, -r7, lsl #10]	; <UNPREDICTABLE>
d001c2b8:	7371f507 	cmnvc	r1, #29360128	; 0x1c00000	; <UNPREDICTABLE>
d001c2bc:	f0054618 			; <UNDEFINED> instruction: 0xf0054618
d001c2c0:	f10df9a7 			; <UNDEFINED> instruction: 0xf10df9a7
d001c2c4:	46840e50 	pkhtbmi	r0, r4, r0, asr #28
d001c2c8:	43e4f8c7 	mvnmi	pc, #13041664	; 0xc70000
d001c2cc:	83e8f8c7 	mvnhi	pc, #13041664	; 0xc70000
d001c2d0:	63ecf887 	mvnvs	pc, #8847360	; 0x870000
d001c2d4:	b3edf887 	mvnlt	pc, #8847360	; 0x870000
d001c2d8:	93f0f887 	mvnsls	pc, #8847360	; 0x870000
d001c2dc:	a3f8f8c7 	mvnsge	pc, #13041664	; 0xc70000
d001c2e0:	53fcf8c7 	mvnspl	pc, #13041664	; 0xc70000
d001c2e4:	000fe8be 			; <UNDEFINED> instruction: 0x000fe8be
d001c2e8:	000fe8ac 	andeq	lr, pc, ip, lsr #17
d001c2ec:	000fe89e 	muleq	pc, lr, r8	; <UNPREDICTABLE>
d001c2f0:	000fe88c 	andeq	lr, pc, ip, lsl #17
d001c2f4:	f8879b02 			; <UNDEFINED> instruction: 0xf8879b02
d001c2f8:	9b0433ef 	blls	0xd01292bc
d001c2fc:	33f4f8c7 	mvnscc	pc, #13041664	; 0xc70000
d001c300:	f508e622 			; <UNDEFINED> instruction: 0xf508e622
d001c304:	f8d2327f 			; <UNDEFINED> instruction: 0xf8d2327f
d001c308:	31031218 	tstcc	r3, r8, lsl r2
d001c30c:	0803f021 	stmdaeq	r3, {r0, r5, ip, sp, lr, pc}
d001c310:	0104f108 	tsteq	r4, r8, lsl #2	; <UNPREDICTABLE>
d001c314:	2e07e706 	cdpcs	7, 0, cr14, cr7, cr6, {0}
d001c318:	2500bf18 	strcs	fp, [r0, #-3864]	; 0xfffff0e8
d001c31c:	bf00e7c4 	svclt	0x0000e7c4
d001c320:	0000c2ce 	andeq	ip, r0, lr, asr #5
d001c324:	0000c290 	muleq	r0, r0, r2
d001c328:	fffffe26 			; <UNDEFINED> instruction: 0xfffffe26
d001c32c:	0000c242 	andeq	ip, r0, r2, asr #4
d001c330:	fffffdcc 			; <UNDEFINED> instruction: 0xfffffdcc
d001c334:	fffffdcb 			; <UNDEFINED> instruction: 0xfffffdcb
d001c338:	fffffde3 			; <UNDEFINED> instruction: 0xfffffde3
d001c33c:	0000c1d4 	ldrdeq	ip, [r0], -r4
d001c340:	0000c1b6 			; <UNDEFINED> instruction: 0x0000c1b6
d001c344:	fffffde6 			; <UNDEFINED> instruction: 0xfffffde6
d001c348:	fffffdf9 			; <UNDEFINED> instruction: 0xfffffdf9
d001c34c:	0000c186 	andeq	ip, r0, r6, lsl #3
d001c350:	0000c162 	andeq	ip, r0, r2, ror #2
d001c354:	fffffde0 			; <UNDEFINED> instruction: 0xfffffde0
d001c358:	0000c14c 	andeq	ip, r0, ip, asr #2
d001c35c:	fffffde8 			; <UNDEFINED> instruction: 0xfffffde8
d001c360:	0000c122 	andeq	ip, r0, r2, lsr #2
d001c364:	0000c0e8 	andeq	ip, r0, r8, ror #1
d001c368:	fffffddd 			; <UNDEFINED> instruction: 0xfffffddd
d001c36c:	0000c0ae 	andeq	ip, r0, lr, lsr #1
d001c370:	fffffc7d 			; <UNDEFINED> instruction: 0xfffffc7d
d001c374:	ffffdbd0 			; <UNDEFINED> instruction: 0xffffdbd0
d001c378:	0000bf86 	andeq	fp, r0, r6, lsl #31
d001c37c:	0000bf5c 	andeq	fp, r0, ip, asr pc
d001c380:	0000bf42 	andeq	fp, r0, r2, asr #30
d001c384:	0000bf16 	andeq	fp, r0, r6, lsl pc

Disassembly of section .text.SBV2_ValidateHeader.constprop.0:

d001c388 <.text.SBV2_ValidateHeader.constprop.0>:
d001c388:	460db5f8 			; <UNDEFINED> instruction: 0x460db5f8
d001c38c:	22084932 	andcs	r4, r8, #819200	; 0xc8000
d001c390:	44794604 	ldrbtmi	r4, [r9], #-1540	; 0xfffff9fc
d001c394:	f95af005 			; <UNDEFINED> instruction: 0xf95af005
d001c398:	d15a2800 	cmple	sl, r0, lsl #16
d001c39c:	2b0268a3 	blcs	0xd00b6630
d001c3a0:	68e3d120 	stmiavs	r3!, {r5, r8, ip, lr, pc}^
d001c3a4:	d11d2b40 	tstle	sp, r0, asr #22
d001c3a8:	42ab6923 	adcmi	r6, fp, #573440	; 0x8c000
d001c3ac:	6ae3d11a 	bvs	0xcf91081c
d001c3b0:	d1172b20 	tstle	r7, r0, lsr #22
d001c3b4:	2f016ba7 	svccs	0x00016ba7
d001c3b8:	6961d814 	stmdbvs	r1!, {r2, r4, fp, ip, lr, pc}^
d001c3bc:	f5b31e4b 			; <UNDEFINED> instruction: 0xf5b31e4b
d001c3c0:	d20f0fbe 	andle	r0, pc, #760	; 0x2f8
d001c3c4:	1e5369a2 	vnmlsne.f16	s13, s7, s5	; <UNPREDICTABLE>
d001c3c8:	0fbef5b3 	svceq	0x00bef5b3
d001c3cc:	06d3d20a 	ldrbeq	sp, [r3], sl, lsl #4
d001c3d0:	4291d108 	addsmi	sp, r1, #8, 2
d001c3d4:	6b23d806 	blvs	0xd09123f4
d001c3d8:	42b31a56 	adcsmi	r1, r3, #352256	; 0x56000
d001c3dc:	6b66d802 	blvs	0xd19d23ec
d001c3e0:	b16eb90f 	cmnlt	lr, pc, lsl #18
d001c3e4:	f5b6bdf8 			; <UNDEFINED> instruction: 0xf5b6bdf8
d001c3e8:	d3fb5f80 	mvnsle	r5, #128, 30	; 0x200
d001c3ec:	0706ea43 	streq	lr, [r6, -r3, asr #20]
d001c3f0:	d1f706ff 	ldrshle	r0, [r7, #111]!	; 0x6f
d001c3f4:	42b31ad3 	adcsmi	r1, r3, #864256	; 0xd3000
d001c3f8:	1a5bd3f4 	bne	0xd17113d0
d001c3fc:	d3f142b3 	mvnsle	r4, #805306379	; 0x3000000b
d001c400:	2b0069e3 	blcs	0xd0036b94
d001c404:	07ded0ee 	ldrbeq	sp, [lr, lr, ror #1]
d001c408:	f023d5ec 			; <UNDEFINED> instruction: 0xf023d5ec
d001c40c:	42990301 	addsmi	r0, r9, #67108864	; 0x4000000
d001c410:	6a63d9e8 	bvs	0xd1912bb8
d001c414:	d9e52b3f 	stmible	r5!, {r0, r1, r2, r3, r4, r5, r8, r9, fp, sp}^
d001c418:	0640f1a3 	strbeq	pc, [r0], -r3, lsr #3	; <UNPREDICTABLE>
d001c41c:	d8e142b1 	stmiale	r1!, {r0, r4, r5, r7, r9, lr}^
d001c420:	d3df429d 	bicsle	r4, pc, #-805306359	; 0xd0000009
d001c424:	432b1aed 			; <UNDEFINED> instruction: 0x432b1aed
d001c428:	d1db079b 			; <UNDEFINED> instruction: 0xd1db079b
d001c42c:	ebb36aa3 	bl	0xcecf6ec0
d001c430:	d1d70f95 			; <UNDEFINED> instruction: 0xd1d70f95
d001c434:	f1036a23 			; <UNDEFINED> instruction: 0xf1036a23
d001c438:	f5b15140 			; <UNDEFINED> instruction: 0xf5b15140
d001c43c:	d2d10fc0 	sbcsle	r0, r1, #192, 30	; 0x300
d001c440:	4050f1c3 	subsmi	pc, r0, r3, asr #3
d001c444:	00c0f500 	sbceq	pc, r0, r0, lsl #10
d001c448:	bf8c4282 	svclt	0x008c4282
d001c44c:	20012000 	andcs	r2, r1, r0
d001c450:	2000e7c8 	andcs	lr, r0, r8, asr #15
d001c454:	bf00e7c6 	svclt	0x0000e7c6
d001c458:	00002ca6 	andeq	r2, r0, r6, lsr #25

Disassembly of section .text.load_apicore.constprop.0:

d001c4e8 <.text.load_apicore.constprop.0>:
d001c4e8:	47f0e92d 	ldrbmi	lr, [r0, sp, lsr #18]!
d001c4ec:	b0864603 	addlt	r4, r6, r3, lsl #12
d001c4f0:	4992b938 	ldmibmi	r2, {r3, r4, r5, r8, fp, ip, sp, pc}
d001c4f4:	44794892 	ldrbtmi	r4, [r9], #-2194	; 0xfffff76e
d001c4f8:	f7f34478 			; <UNDEFINED> instruction: 0xf7f34478
d001c4fc:	2000feb9 			; <UNDEFINED> instruction: 0x2000feb9
d001c500:	4c90e0b2 	ldcmi	0, cr14, [r0], {178}	; 0xb2
d001c504:	71acf644 			; <UNDEFINED> instruction: 0x71acf644
d001c508:	4620447c 			; <UNDEFINED> instruction: 0x4620447c
d001c50c:	28004798 	stmdacs	r0, {r3, r4, r7, r8, r9, sl, lr}
d001c510:	f1a0d0ef 			; <UNDEFINED> instruction: 0xf1a0d0ef
d001c514:	f6440218 			; <UNDEFINED> instruction: 0xf6440218
d001c518:	429a7394 	addsmi	r7, sl, #148, 6	; 0x50000002
d001c51c:	8105f200 	mrshi	pc, SP_usr	; <UNPREDICTABLE>
d001c520:	22041f06 	andcs	r1, r4, #6, 30
d001c524:	4d834668 	stcmi	6, cr4, [r3, #416]	; 0x1a0
d001c528:	f00519a1 			; <UNDEFINED> instruction: 0xf00519a1
d001c52c:	4622f87f 			; <UNDEFINED> instruction: 0x4622f87f
d001c530:	33fff04f 	mvnscc	pc, #79	; 0x4f
d001c534:	f8122100 			; <UNDEFINED> instruction: 0xf8122100
d001c538:	24080b01 	strcs	r0, [r8], #-2817	; 0xfffff4ff
d001c53c:	f0134043 			; <UNDEFINED> instruction: 0xf0134043
d001c540:	bf180001 	svclt	0x00180001
d001c544:	3c014628 	stccc	6, cr4, [r1], {40}	; 0x28
d001c548:	0353ea80 	cmpeq	r3, #128, 20	; 0x80000
d001c54c:	3101d1f7 	strdcc	sp, [r1, -r7]
d001c550:	d8f0428e 	ldmle	r0!, {r1, r2, r3, r7, r9, lr}^
d001c554:	9a0043db 	bls	0xd002d4c8
d001c558:	f040429a 			; <UNDEFINED> instruction: 0xf040429a
d001c55c:	4f7a80e6 	svcmi	0x007a80e6
d001c560:	2214ad01 	andscs	sl, r4, #1, 26	; 0x40
d001c564:	4628447f 			; <UNDEFINED> instruction: 0x4628447f
d001c568:	f0054639 			; <UNDEFINED> instruction: 0xf0054639
d001c56c:	4977f85f 	ldmdbmi	r7!, {r0, r1, r2, r3, r4, r6, fp, ip, sp, lr, pc}^
d001c570:	46282208 	strtmi	r2, [r8], -r8, lsl #4
d001c574:	f0054479 			; <UNDEFINED> instruction: 0xf0054479
d001c578:	b120f869 	msrlt	CPSR_, r9, ror #16
d001c57c:	48754974 	ldmdami	r5!, {r2, r4, r5, r6, r8, fp, lr}^
d001c580:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d001c584:	4b6ce7b9 	blmi	0xd1b56470
d001c588:	429a9a03 	addsmi	r9, sl, #12288	; 0x3000
d001c58c:	80cdf040 	sbchi	pc, sp, r0, asr #32
d001c590:	1e539a04 	vnmlsne.f32	s19, s6, s8
d001c594:	f2002b9f 	vpadd.i8	d2, d16, d15
d001c598:	9b0580c8 	blls	0xd017c8c0
d001c59c:	f2002bc0 	vqdmulh.s<illegal width 8>	q1, q8, q0
d001c5a0:	215480c4 	cmpcs	r4, r4, asr #1
d001c5a4:	22244351 	eorcs	r4, r4, #1140850689	; 0x44000001
d001c5a8:	eb01435a 	bl	0xd006d318
d001c5ac:	f1080802 			; <UNDEFINED> instruction: 0xf1080802
d001c5b0:	429e0328 	addsmi	r0, lr, #40, 6	; 0xa0000000
d001c5b4:	80b9f040 	adcshi	pc, r9, r0, asr #32
d001c5b8:	31144e67 	tstcc	r4, r7, ror #28
d001c5bc:	4439447e 	ldrtmi	r4, [r9], #-1150	; 0xfffffb82
d001c5c0:	3082f506 	addcc	pc, r2, r6, lsl #10
d001c5c4:	f00530a4 			; <UNDEFINED> instruction: 0xf00530a4
d001c5c8:	f506f831 			; <UNDEFINED> instruction: 0xf506f831
d001c5cc:	f108308f 			; <UNDEFINED> instruction: 0xf108308f
d001c5d0:	f5060114 			; <UNDEFINED> instruction: 0xf5060114
d001c5d4:	2214368f 	andscs	r3, r4, #149946368	; 0x8f00000
d001c5d8:	70d2f500 	sbcsvc	pc, r2, r0, lsl #10
d001c5dc:	f0054439 			; <UNDEFINED> instruction: 0xf0054439
d001c5e0:	f8b6f825 			; <UNDEFINED> instruction: 0xf8b6f825
d001c5e4:	f64011b4 			; <UNDEFINED> instruction: 0xf64011b4
d001c5e8:	1f0a73fc 	svcne	0x000a73fc
d001c5ec:	f200429a 	vqsub.s8	d4, d16, d10
d001c5f0:	f001809c 			; <UNDEFINED> instruction: 0xf001809c
d001c5f4:	f8b60303 			; <UNDEFINED> instruction: 0xf8b60303
d001c5f8:	431321b6 	tstmi	r3, #-2147483603	; 0x8000002d
d001c5fc:	8095f040 	addshi	pc, r5, r0, asr #32
d001c600:	22044b56 	andcs	r4, r4, #88064	; 0x15800
d001c604:	f503447b 			; <UNDEFINED> instruction: 0xf503447b
d001c608:	f503338f 			; <UNDEFINED> instruction: 0xf503338f
d001c60c:	f83373d2 			; <UNDEFINED> instruction: 0xf83373d2
d001c610:	1e560b02 	vnmlsne.f64	d16, d6, d2
d001c614:	f0404006 			; <UNDEFINED> instruction: 0xf0404006
d001c618:	1a8a8088 	bne	0xce2bc840
d001c61c:	f2004290 	vqsub.s8	d4, d16, d0
d001c620:	34018084 	strcc	r8, [r1], #-132	; 0xffffff7c
d001c624:	d1222c08 			; <UNDEFINED> instruction: 0xd1222c08
d001c628:	46b04c4d 	ldrtmi	r4, [r0], sp, asr #24
d001c62c:	f6404f4d 			; <UNDEFINED> instruction: 0xf6404f4d
d001c630:	447c79fc 	ldrbtmi	r7, [ip], #-2556	; 0xfffff604
d001c634:	f504447f 			; <UNDEFINED> instruction: 0xf504447f
d001c638:	37144450 			; <UNDEFINED> instruction: 0x37144450
d001c63c:	9b04346c 	blls	0xd01297f4
d001c640:	d3194598 	tstle	r9, #152, 10	; 0x26000000
d001c644:	447c4c48 	ldrbtmi	r4, [ip], #-3144	; 0xfffff3b8
d001c648:	3482f504 	strcc	pc, [r2], #1284	; 0x504
d001c64c:	9b0534a4 	blls	0xd01698e4
d001c650:	d361429e 	cmnle	r1, #-536870903	; 0xe0000009
d001c654:	447c4c45 	ldrbtmi	r4, [ip], #-3141	; 0xfffff3bb
d001c658:	4450f504 	ldrbmi	pc, [r0], #-1284	; 0xfffffafc	; <UNPREDICTABLE>
d001c65c:	3410cd0f 	ldrcc	ip, [r0], #-3343	; 0xfffff2f1
d001c660:	682bc40f 	stmdavs	fp!, {r0, r1, r2, r3, sl, lr, pc}
d001c664:	60232001 	eorvs	r2, r3, r1
d001c668:	e8bdb006 	pop	{r1, r2, ip, sp, pc}
d001c66c:	2c0187f0 	stccs	7, cr8, [r1], {240}	; 0xf0
d001c670:	2201bf0c 	andcs	fp, r1, #12, 30	; 0x30
d001c674:	e7ca2204 	strb	r2, [sl, r4, lsl #4]
d001c678:	0a48f1a4 	beq	0xd1258d10
d001c67c:	46392254 			; <UNDEFINED> instruction: 0x46392254
d001c680:	f0044650 			; <UNDEFINED> instruction: 0xf0044650
d001c684:	2201ffd3 	andcs	pc, r1, #844	; 0x34c
d001c688:	46502140 	ldrbmi	r2, [r0], -r0, asr #2
d001c68c:	feeef7f3 	mcr2	7, 7, pc, cr14, cr3, {7}	; <UNPREDICTABLE>
d001c690:	d04a2800 	suble	r2, sl, r0, lsl #16
d001c694:	2c02f814 	stccs	8, cr15, [r2], {20}
d001c698:	d8462a0c 	stmdale	r6, {r2, r3, r9, fp, sp}^
d001c69c:	3c01f814 	stccc	8, cr15, [r1], {20}
d001c6a0:	b2d93b05 	sbcslt	r3, r9, #5120	; 0x1400
d001c6a4:	d840290c 	stmdale	r0, {r2, r3, r8, fp, sp}^
d001c6a8:	034ff641 	movteq	pc, #63041	; 0xf641	; <UNPREDICTABLE>
d001c6ac:	43db40cb 	bicsmi	r4, fp, #203	; 0xcb
d001c6b0:	0301f013 	movweq	pc, #4115	; 0x1013	; <UNPREDICTABLE>
d001c6b4:	f834d139 			; <UNDEFINED> instruction: 0xf834d139
d001c6b8:	f64f0c08 			; <UNDEFINED> instruction: 0xf64f0c08
d001c6bc:	428871ff 	addmi	r7, r8, #-1073741761	; 0xc000003f
d001c6c0:	f834d033 			; <UNDEFINED> instruction: 0xf834d033
d001c6c4:	42880c06 	addmi	r0, r8, #1536	; 0x600
d001c6c8:	f1a4d02f 			; <UNDEFINED> instruction: 0xf1a4d02f
d001c6cc:	f83c0c08 			; <UNDEFINED> instruction: 0xf83c0c08
d001c6d0:	42880b02 	addmi	r0, r8, #2048	; 0x800
d001c6d4:	4548d003 	strbmi	sp, [r8, #-3]
d001c6d8:	0780d827 	streq	sp, [r0, r7, lsr #16]
d001c6dc:	3301d125 	movwcc	sp, #4389	; 0x1125
d001c6e0:	d1f42b03 	mvnsle	r2, r3, lsl #22
d001c6e4:	23004621 	movwcs	r4, #1569	; 0x621
d001c6e8:	d806429a 	stmdale	r6, {r1, r3, r4, r7, r9, lr}
d001c6ec:	d10f2a0c 	tstle	pc, ip, lsl #20
d001c6f0:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d001c6f4:	37543454 			; <UNDEFINED> instruction: 0x37543454
d001c6f8:	f811e7a1 			; <UNDEFINED> instruction: 0xf811e7a1
d001c6fc:	f1000b01 			; <UNDEFINED> instruction: 0xf1000b01
d001c700:	f1bc3cff 			; <UNDEFINED> instruction: 0xf1bc3cff
d001c704:	d8100f15 	ldmdale	r0, {r0, r2, r4, r8, r9, sl, fp}
d001c708:	d00e2807 	andle	r2, lr, r7, lsl #16
d001c70c:	e7eb3301 	strb	r3, [fp, r1, lsl #6]!
d001c710:	b9535ca3 	ldmdblt	r3, {r0, r1, r5, r7, sl, fp, ip, lr}^
d001c714:	e7e93201 	strb	r3, [r9, r1, lsl #4]!
d001c718:	22004620 	andcs	r4, r0, #32, 12	; 0x2000000
d001c71c:	34242120 	strtcc	r2, [r4], #-288	; 0xfffffee0
d001c720:	fea4f7f3 	mcr2	7, 5, pc, cr4, cr3, {7}	; <UNPREDICTABLE>
d001c724:	3601b108 	strcc	fp, [r1], -r8, lsl #2
d001c728:	4911e791 	ldmdbmi	r1, {r0, r4, r7, r8, r9, sl, sp, lr, pc}
d001c72c:	44794811 	ldrbtmi	r4, [r9], #-2065	; 0xfffff7ef
d001c730:	e6e24478 	uxtab	r4, r2, r8, ror #8
d001c734:	edb88320 	ldc	3, cr8, [r8, #128]!	; 0x80
d001c738:	2001f000 	andcs	pc, r1, r0
d001c73c:	ffffff62 			; <UNDEFINED> instruction: 0xffffff62
d001c740:	0000bccc 	andeq	fp, r0, ip, asr #25
d001c744:	00006d10 	andeq	r6, r0, r0, lsl sp
d001c748:	00006cb4 			; <UNDEFINED> instruction: 0x00006cb4
d001c74c:	ffffff0f 			; <UNDEFINED> instruction: 0xffffff0f
d001c750:	ffffff0b 			; <UNDEFINED> instruction: 0xffffff0b
d001c754:	0000bc42 	andeq	fp, r0, r2, asr #24
d001c758:	0000bc08 	andeq	fp, r0, r8, lsl #24
d001c75c:	0000bbc0 	andeq	fp, r0, r0, asr #23
d001c760:	0000bb92 	muleq	r0, r2, fp
d001c764:	00006be4 	andeq	r6, r0, r4, ror #23
d001c768:	0000bb7e 	andeq	fp, r0, lr, ror fp
d001c76c:	0000bb6e 	andeq	fp, r0, lr, ror #22
d001c770:	fffffd9a 			; <UNDEFINED> instruction: 0xfffffd9a
d001c774:	0000ba94 	muleq	r0, r4, sl

Disassembly of section .text.external_declaration.constprop.0:

d001ce6c <.text.external_declaration.constprop.0>:
d001ce6c:	4ff0e92d 	svcmi	0x00f0e92d
d001ce70:	4be0f8df 	blmi	0xcf85b1f4
d001ce74:	f240b0df 	vqadd.s8	<illegal reg q13.5>, q8, <illegal reg q7.5>
d001ce78:	447c1119 	ldrbtmi	r1, [ip], #-281	; 0xfffffee7
d001ce7c:	f7f64620 			; <UNDEFINED> instruction: 0xf7f64620
d001ce80:	4681f843 	strmi	pc, [r1], r3, asr #16
d001ce84:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d001ce88:	f1048172 			; <UNDEFINED> instruction: 0xf1048172
d001ce8c:	ad260618 	stcge	6, cr0, [r6, #-96]!	; 0xffffffa0
d001ce90:	802cf8d4 	ldrdhi	pc, [ip], -r4	; <UNPREDICTABLE>
d001ce94:	0998f10d 	ldmibeq	r8, {r0, r2, r3, r8, ip, sp, lr, pc}
d001ce98:	c50fce0f 	strgt	ip, [pc, #-3599]	; 0xd001c091
d001ce9c:	000fe896 	muleq	pc, r6, r8	; <UNPREDICTABLE>
d001cea0:	000fe885 	andeq	lr, pc, r5, lsl #17
d001cea4:	f2406a63 	vpmax.s8	q11, q0, <illegal reg q9.5>
d001cea8:	46201107 	strtmi	r1, [r0], -r7, lsl #2
d001ceac:	0518f104 	ldreq	pc, [r8, #-260]	; 0xfffffefc
d001ceb0:	6aa3930f 	bvs	0xce901af4
d001ceb4:	f8949310 			; <UNDEFINED> instruction: 0xf8949310
d001ceb8:	93113030 	tstls	r1, #48	; 0x30
d001cebc:	e9d46b63 	ldmib	r4, {r0, r1, r5, r6, r8, r9, fp, sp, lr}^
d001cec0:	9312ba06 	tstls	r2, #24576	; 0x6000
d001cec4:	f820f7f6 			; <UNDEFINED> instruction: 0xf820f7f6
d001cec8:	28004607 	stmdacs	r0, {r0, r1, r2, r9, sl, lr}
d001cecc:	80f9f040 	rscshi	pc, r9, r0, asr #32
d001ced0:	f2406ae6 	vpmax.s8	q11, q8, q11
d001ced4:	429e131b 	addsmi	r1, lr, #1811939328	; 0x6c000000
d001ced8:	4620d107 	strtmi	sp, [r0], -r7, lsl #2
d001cedc:	fb14f7f6 	blx	0xd055aebe
d001cee0:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d001cee4:	463e80e7 	ldrtmi	r8, [lr], -r7, ror #1
d001cee8:	f46fe04b 	vld4.16	{d30-d33}, [pc], fp
d001ceec:	eb067e8b 	bl	0xd01bc920
d001cef0:	2b01030e 	blcs	0xd005db30
d001cef4:	f5a6d84e 			; <UNDEFINED> instruction: 0xf5a6d84e
d001cef8:	46207c8c 	strtmi	r7, [r0], -ip, lsl #25
d001cefc:	0600f1dc 			; <UNDEFINED> instruction: 0x0600f1dc
d001cf00:	060ceb46 	streq	lr, [ip], -r6, asr #22
d001cf04:	ffe0f7f5 			; <UNDEFINED> instruction: 0xffe0f7f5
d001cf08:	f8d446cc 			; <UNDEFINED> instruction: 0xf8d446cc
d001cf0c:	cd0f802c 	stcgt	0, cr8, [pc, #-176]	; 0xd001ce64
d001cf10:	000fe8ac 	andeq	lr, pc, ip, lsr #17
d001cf14:	000fe895 	muleq	pc, r5, r8	; <UNPREDICTABLE>
d001cf18:	000fe88c 	andeq	lr, pc, ip, lsl #17
d001cf1c:	930f6a63 	movwls	r6, #64099	; 0xfa63
d001cf20:	93106aa3 	tstls	r0, #667648	; 0xa3000
d001cf24:	3030f894 	mlascc	r0, r4, r8, pc	; <UNPREDICTABLE>
d001cf28:	6b639311 	blvs	0xd1901b74
d001cf2c:	f2409312 	vcge.s8	d25, d0, d2
d001cf30:	45981301 	ldrmi	r1, [r8, #769]	; 0x301
d001cf34:	ba06e9d4 	blt	0xd01d768c
d001cf38:	4620d102 	strtmi	sp, [r0], -r2, lsl #2
d001cf3c:	ffc4f7f5 			; <UNDEFINED> instruction: 0xffc4f7f5
d001cf40:	4b14f8df 	blmi	0xd055b2c4
d001cf44:	6ae3447c 	bvs	0xcf8ee13c
d001cf48:	f0002b7b 			; <UNDEFINED> instruction: 0xf0002b7b
d001cf4c:	f24080bd 	vqadd.s8	d24, d16, d29
d001cf50:	45981301 	ldrmi	r1, [r8, #769]	; 0x301
d001cf54:	4633d117 			; <UNDEFINED> instruction: 0x4633d117
d001cf58:	46594652 			; <UNDEFINED> instruction: 0x46594652
d001cf5c:	f7f34620 			; <UNDEFINED> instruction: 0xf7f34620
d001cf60:	1e05fbcf 	vmlsne.f64	d15, d21, d15
d001cf64:	6da3da34 			; <UNDEFINED> instruction: 0x6da3da34
d001cf68:	f8dfb95b 			; <UNDEFINED> instruction: 0xf8dfb95b
d001cf6c:	447b3af0 	ldrbtmi	r3, [fp], #-2800	; 0xfffff510
d001cf70:	9b0f65a3 	blls	0xd03f6604
d001cf74:	9b1065e3 	blls	0xd0436708
d001cf78:	9b116623 	blls	0xd047680c
d001cf7c:	9b126663 	blls	0xd04b6910
d001cf80:	25ff66a3 	ldrbcs	r6, [pc, #1699]!	; 0xd001d62b
d001cf84:	f8dfe024 			; <UNDEFINED> instruction: 0xf8dfe024
d001cf88:	46201ad8 			; <UNDEFINED> instruction: 0x46201ad8
d001cf8c:	f7f34479 			; <UNDEFINED> instruction: 0xf7f34479
d001cf90:	e7f6f96f 	ldrb	pc, [r6, pc, ror #18]!	; <UNPREDICTABLE>
d001cf94:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d001cf98:	f040429e 			; <UNDEFINED> instruction: 0xf040429e
d001cf9c:	4620808e 	strtmi	r8, [r0], -lr, lsl #1
d001cfa0:	1206e9d4 	andne	lr, r6, #212, 18	; 0x350000
d001cfa4:	fc59f7f3 	mrrc2	7, 15, pc, r9, cr3	; <UNPREDICTABLE>
d001cfa8:	da062800 	ble	0xd01a6fb0
d001cfac:	1ab4f8df 	bne	0xced5b330
d001cfb0:	46204479 			; <UNDEFINED> instruction: 0x46204479
d001cfb4:	f95cf7f3 			; <UNDEFINED> instruction: 0xf95cf7f3
d001cfb8:	2324e795 			; <UNDEFINED> instruction: 0x2324e795
d001cfbc:	fb03463e 	blx	0xd00ee8be
d001cfc0:	f5004000 			; <UNDEFINED> instruction: 0xf5004000
d001cfc4:	f8903075 			; <UNDEFINED> instruction: 0xf8903075
d001cfc8:	462053ac 	strtmi	r5, [r0], -ip, lsr #7
d001cfcc:	ff7cf7f5 			; <UNDEFINED> instruction: 0xff7cf7f5
d001cfd0:	4a94f8df 	bmi	0xce55b354
d001cfd4:	6da3447c 	cfstrsvs	mvf4, [r3, #496]!	; 0x1f0
d001cfd8:	d16b2b00 	cmnle	fp, r0, lsl #22
d001cfdc:	9b0fb347 	blls	0xd0409d00
d001cfe0:	ad06464f 	stcge	6, cr4, [r6, #-316]	; 0xfffffec4
d001cfe4:	9b109329 	blls	0xd0441c90
d001cfe8:	382ae9cd 	stmdacc	sl!, {r0, r2, r3, r6, r7, r8, fp, sp, lr, pc}
d001cfec:	f88d9b11 			; <UNDEFINED> instruction: 0xf88d9b11
d001cff0:	9b1230b0 	blls	0xd04a92b8
d001cff4:	ba26e9cd 	blt	0xd09d7730
d001cff8:	cf0f932d 	svcgt	0x000f932d
d001cffc:	e897c50f 	ldm	r7, {r0, r1, r2, r3, r8, sl, lr, pc}
d001d000:	e885000f 	stm	r5, {r0, r1, r2, r3}
d001d004:	f240000f 	vhadd.s8	d16, d0, d15
d001d008:	96041301 	strls	r1, [r4], -r1, lsl #6
d001d00c:	0303ebb8 	movweq	lr, #15288	; 0x3bb8
d001d010:	2301bf18 	movwcs	fp, #7960	; 0x1f18
d001d014:	ab2a9305 	blge	0xd0ac1c30
d001d018:	e88dcb0f 	stm	sp, {r0, r1, r2, r3, r8, r9, fp, lr, pc}
d001d01c:	e899000f 	ldm	r9, {r0, r1, r2, r3}
d001d020:	f7f7000f 			; <UNDEFINED> instruction: 0xf7f7000f
d001d024:	1e05f9ad 	vmlane.f16	s30, s11, s27	; <UNPREDICTABLE>
d001d028:	6da3db44 			; <UNDEFINED> instruction: 0x6da3db44
d001d02c:	d1412b00 	cmple	r1, r0, lsl #22
d001d030:	4a38f8df 	bmi	0xd0e5b3b4
d001d034:	447cae2e 	ldrbtmi	sl, [ip], #-3630	; 0xfffff1d2
d001d038:	0718f104 	ldreq	pc, [r8, -r4, lsl #2]
d001d03c:	c60fcf0f 	strgt	ip, [pc], -pc, lsl #30
d001d040:	000fe897 	muleq	pc, r7, r8	; <UNPREDICTABLE>
d001d044:	000fe886 	andeq	lr, pc, r6, lsl #17
d001d048:	2a24f8df 	bcs	0xd095b3cc
d001d04c:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d001d050:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d001d054:	ff66f7f5 			; <UNDEFINED> instruction: 0xff66f7f5
d001d058:	f8dfb360 			; <UNDEFINED> instruction: 0xf8dfb360
d001d05c:	213b2a18 	teqcs	fp, r8, lsl sl
d001d060:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d001d064:	ff5ef7f5 			; <UNDEFINED> instruction: 0xff5ef7f5
d001d068:	af2eb320 	svcge	0x002eb320
d001d06c:	f8ddae36 			; <UNDEFINED> instruction: 0xf8ddae36
d001d070:	f8dd90c4 			; <UNDEFINED> instruction: 0xf8dd90c4
d001d074:	cf0f80c8 	svcgt	0x000f80c8
d001d078:	ba2ee9dd 	blt	0xd0bd77f4
d001d07c:	e897c60f 	ldm	r7, {r0, r1, r2, r3, r9, sl, lr, pc}
d001d080:	e886000f 	stm	r6, {r0, r1, r2, r3}
d001d084:	4652000f 	ldrbmi	r0, [r2], -pc
d001d088:	46204659 			; <UNDEFINED> instruction: 0x46204659
d001d08c:	70d0f89d 	smullsvc	pc, r0, sp, r8	; <UNPREDICTABLE>
d001d090:	f7f39e35 			; <UNDEFINED> instruction: 0xf7f39e35
d001d094:	2800fbbd 	stmdacs	r0, {r0, r2, r3, r4, r5, r7, r8, r9, fp, ip, sp, lr, pc}
d001d098:	f8dfdb18 			; <UNDEFINED> instruction: 0xf8dfdb18
d001d09c:	447b39dc 	ldrbtmi	r3, [fp], #-2524	; 0xfffff624
d001d0a0:	b93a6d9a 	ldmdblt	sl!, {r1, r3, r4, r7, r8, sl, fp, sp, lr}
d001d0a4:	29d4f8df 	ldmibcs	r4, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d001d0a8:	447a669e 	ldrbtmi	r6, [sl], #-1694	; 0xfffff962
d001d0ac:	8718e9c3 	ldrhi	lr, [r8, -r3, asr #19]
d001d0b0:	2916e9c3 	ldmdbcs	r6, {r0, r1, r6, r7, r8, fp, sp, lr, pc}
d001d0b4:	e8bdb05f 	pop	{r0, r1, r2, r3, r4, r6, ip, sp, pc}
d001d0b8:	f8df8ff0 			; <UNDEFINED> instruction: 0xf8df8ff0
d001d0bc:	447919c4 	ldrbtmi	r1, [r9], #-2500	; 0xfffff63c
d001d0c0:	2600e777 			; <UNDEFINED> instruction: 0x2600e777
d001d0c4:	e75c4637 	smmlar	ip, r7, r6, r4
d001d0c8:	e75a2701 	ldrb	r2, [sl, -r1, lsl #14]
d001d0cc:	46594652 			; <UNDEFINED> instruction: 0x46594652
d001d0d0:	f7f34620 			; <UNDEFINED> instruction: 0xf7f34620
d001d0d4:	2800fc06 	stmdacs	r0, {r1, r2, sl, fp, ip, sp, lr, pc}
d001d0d8:	4652dadf 			; <UNDEFINED> instruction: 0x4652dadf
d001d0dc:	46204659 			; <UNDEFINED> instruction: 0x46204659
d001d0e0:	fbbbf7f3 	blx	0xcef1b0b6
d001d0e4:	db142800 	blle	0xd05270ec
d001d0e8:	fb032324 	blx	0xd00e5d82
d001d0ec:	f5004000 			; <UNDEFINED> instruction: 0xf5004000
d001d0f0:	f8903075 			; <UNDEFINED> instruction: 0xf8903075
d001d0f4:	429d33ac 	addsmi	r3, sp, #172, 6	; 0xb0000002
d001d0f8:	6da3d0dc 	stcvs	0, cr13, [r3, #880]!	; 0x370
d001d0fc:	d1d92b00 	bicsle	r2, r9, r0, lsl #22
d001d100:	3980f8df 	stmibcc	r0, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d001d104:	66a6447b 	sxtabvs	r4, r6, fp, ror #8
d001d108:	3916e9c4 	ldmdbcc	r6, {r2, r6, r7, r8, fp, sp, lr, pc}
d001d10c:	8718e9c4 	ldrhi	lr, [r8, -r4, asr #19]
d001d110:	f504e7d0 			; <UNDEFINED> instruction: 0xf504e7d0
d001d114:	f8d23278 			; <UNDEFINED> instruction: 0xf8d23278
d001d118:	2b40308c 	blcs	0xd1029350
d001d11c:	6da3d106 	stfvsd	f5, [r3, #24]!
d001d120:	d1c72b00 	bicle	r2, r7, r0, lsl #22
d001d124:	3960f8df 	stmdbcc	r0!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d001d128:	e7ec447b 			; <UNDEFINED> instruction: 0xe7ec447b
d001d12c:	f8941c59 			; <UNDEFINED> instruction: 0xf8941c59
d001d130:	f88dc008 			; <UNDEFINED> instruction: 0xf88dc008
d001d134:	af3670f0 	svcge	0x003670f0
d001d138:	108cf8c2 	addne	pc, ip, r2, asr #17
d001d13c:	963d2224 	ldrtls	r2, [sp], -r4, lsr #4
d001d140:	4403fb02 	strmi	pc, [r3], #-2818	; 0xfffff4fe
d001d144:	80e8f8cd 	rschi	pc, r8, sp, asr #17
d001d148:	3475f504 	ldrbtcc	pc, [r5], #-1284	; 0xfffffafc	; <UNPREDICTABLE>
d001d14c:	90e4f8cd 	rscls	pc, r4, sp, asr #17
d001d150:	7663f504 	strbtvc	pc, [r3], -r4, lsl #10	; <UNPREDICTABLE>
d001d154:	53acf884 			; <UNDEFINED> instruction: 0x53acf884
d001d158:	c3adf884 			; <UNDEFINED> instruction: 0xc3adf884
d001d15c:	ba36e9cd 	blt	0xd0dd7898
d001d160:	c60fcf0f 	strgt	ip, [pc], -pc, lsl #30
d001d164:	000fe897 	muleq	pc, r7, r8	; <UNPREDICTABLE>
d001d168:	000fe886 	andeq	lr, pc, r6, lsl #17
d001d16c:	f8d4e7a2 			; <UNDEFINED> instruction: 0xf8d4e7a2
d001d170:	f46f802c 	vld4.8	{d24-d27}, [pc :128], ip
d001d174:	eb08768b 	bl	0xd023aba8
d001d178:	2b010306 	blcs	0xd005dd98
d001d17c:	6ce7d85c 	stclvs	8, cr13, [r7], #368	; 0x170
d001d180:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d001d184:	d157429f 			; <UNDEFINED> instruction: 0xd157429f
d001d188:	0618f104 	ldreq	pc, [r8], -r4, lsl #2
d001d18c:	f7f54620 			; <UNDEFINED> instruction: 0xf7f54620
d001d190:	ad36fe9b 	ldcge	14, cr15, [r6, #-620]!	; 0xfffffd94
d001d194:	b024f8d4 	ldrdlt	pc, [r4], -r4	; <UNPREDICTABLE>
d001d198:	a028f8d4 	ldrdge	pc, [r8], -r4	; <UNPREDICTABLE>
d001d19c:	c50fce0f 	strgt	ip, [pc, #-3599]	; 0xd001c395
d001d1a0:	000fe896 	muleq	pc, r6, r8	; <UNPREDICTABLE>
d001d1a4:	000fe885 	andeq	lr, pc, r5, lsl #17
d001d1a8:	28e0f8df 	stmiacs	r0!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d001d1ac:	46204639 			; <UNDEFINED> instruction: 0x46204639
d001d1b0:	6030f894 	mlasvs	r0, r4, r8, pc	; <UNPREDICTABLE>
d001d1b4:	6b65447a 	blvs	0xd196e3a4
d001d1b8:	f7f5af36 			; <UNDEFINED> instruction: 0xf7f5af36
d001d1bc:	2800feb3 	stmdacs	r0, {r0, r1, r4, r5, r7, r9, sl, fp, ip, sp, lr, pc}
d001d1c0:	af78f43f 	svcge	0x0078f43f
d001d1c4:	2b7b6ae3 	blcs	0xd1ef7d58
d001d1c8:	f88dd129 			; <UNDEFINED> instruction: 0xf88dd129
d001d1cc:	463e60f0 			; <UNDEFINED> instruction: 0x463e60f0
d001d1d0:	ad06953d 	cfstr32ge	mvfx9, [r6, #-244]	; 0xffffff0c
d001d1d4:	a0e8f8cd 	rscge	pc, r8, sp, asr #17
d001d1d8:	b0e4f8cd 	rsclt	pc, r4, sp, asr #17
d001d1dc:	c50fce0f 	strgt	ip, [pc, #-3599]	; 0xd001c3d5
d001d1e0:	000fe896 	muleq	pc, r6, r8	; <UNPREDICTABLE>
d001d1e4:	000fe885 	andeq	lr, pc, r5, lsl #17
d001d1e8:	758cf5a8 	strvc	pc, [ip, #1448]	; 0x5a8
d001d1ec:	9014f8cd 	andsls	pc, r4, sp, asr #17
d001d1f0:	416b426b 	cmnmi	fp, fp, ror #4
d001d1f4:	ab3a9304 	blge	0xd0ec1e0c
d001d1f8:	e88dcb0f 	stm	sp, {r0, r1, r2, r3, r8, r9, fp, lr, pc}
d001d1fc:	e897000f 	ldm	r7, {r0, r1, r2, r3}
d001d200:	f7f7000f 			; <UNDEFINED> instruction: 0xf7f7000f
d001d204:	6da3f8bd 	stcvs	8, cr15, [r3, #756]!	; 0x2f4
d001d208:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001d20c:	f8dfaf53 			; <UNDEFINED> instruction: 0xf8dfaf53
d001d210:	213b2880 	teqcs	fp, r0, lsl #17
d001d214:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d001d218:	fe84f7f5 	mcr2	7, 4, pc, cr4, cr5, {7}	; <UNPREDICTABLE>
d001d21c:	6da3e74a 	stcvs	7, cr14, [r3, #296]!	; 0x128
d001d220:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001d224:	f8dfaf47 			; <UNDEFINED> instruction: 0xf8dfaf47
d001d228:	66a5386c 	strtvs	r3, [r5], ip, ror #16
d001d22c:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d001d230:	e9c4a618 	stmib	r4, {r3, r4, r9, sl, sp, pc}^
d001d234:	e73d3b16 			; <UNDEFINED> instruction: 0xe73d3b16
d001d238:	585cf8df 	ldmdapl	ip, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d001d23c:	7183f44f 	orrvc	pc, r3, pc, asr #8
d001d240:	4628447d 			; <UNDEFINED> instruction: 0x4628447d
d001d244:	fe60f7f5 	mcr2	7, 3, pc, cr0, cr5, {7}	; <UNPREDICTABLE>
d001d248:	f24db148 	vrhadd.s8	<illegal reg q13.5>, <illegal reg q6.5>, q4
d001d24c:	58eb031c 	stmiapl	fp!, {r2, r3, r4, r8, r9}^
d001d250:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001d254:	6f28af2f 	svcvs	0x0028af2f
d001d258:	f946f7ff 			; <UNDEFINED> instruction: 0xf946f7ff
d001d25c:	f44fe72a 	vst1.8	{d30}, [pc :128], sl
d001d260:	46287188 	strtmi	r7, [r8], -r8, lsl #3
d001d264:	fe50f7f5 	mrc2	7, 2, pc, cr0, cr5, {7}
d001d268:	7185f44f 	orrvc	pc, r5, pc, asr #8
d001d26c:	46289014 			; <UNDEFINED> instruction: 0x46289014
d001d270:	fe4af7f5 	mcr2	7, 2, pc, cr10, cr5, {7}	; <UNPREDICTABLE>
d001d274:	f2406aea 	vpmax.s8	q11, q8, q13
d001d278:	4604131b 			; <UNDEFINED> instruction: 0x4604131b
d001d27c:	429a4628 	addsmi	r4, sl, #40, 12	; 0x2800000
d001d280:	f7f6d14b 			; <UNDEFINED> instruction: 0xf7f6d14b
d001d284:	2800f941 	stmdacs	r0, {r0, r6, r8, fp, ip, sp, lr, pc}
d001d288:	af14f43f 	svcge	0x0014f43f
d001d28c:	4628213b 			; <UNDEFINED> instruction: 0x4628213b
d001d290:	fe3af7f5 	mrc2	7, 1, pc, cr10, cr5, {7}
d001d294:	28004680 	stmdacs	r0, {r7, r9, sl, lr}
d001d298:	af0cf47f 	svcge	0x000cf47f
d001d29c:	0718f105 	ldreq	pc, [r8, -r5, lsl #2]
d001d2a0:	f8d5ae36 			; <UNDEFINED> instruction: 0xf8d5ae36
d001d2a4:	f8d5b024 			; <UNDEFINED> instruction: 0xf8d5b024
d001d2a8:	f895a028 			; <UNDEFINED> instruction: 0xf895a028
d001d2ac:	cf0f9030 	svcgt	0x000f9030
d001d2b0:	e897c60f 	ldm	r7, {r0, r1, r2, r3, r9, sl, lr, pc}
d001d2b4:	e886000f 	stm	r6, {r0, r1, r2, r3}
d001d2b8:	f8df000f 			; <UNDEFINED> instruction: 0xf8df000f
d001d2bc:	f24027e0 	vabd.s8	q9, q8, q8
d001d2c0:	46281101 	strtmi	r1, [r8], -r1, lsl #2
d001d2c4:	447a6b6f 	ldrbtmi	r6, [sl], #-2927	; 0xfffff491
d001d2c8:	f7f5ae36 			; <UNDEFINED> instruction: 0xf7f5ae36
d001d2cc:	2800fe2b 	stmdacs	r0, {r0, r1, r3, r5, r9, sl, fp, ip, sp, lr, pc}
d001d2d0:	aef0f43f 	mrcge	4, 7, APSR_nzcv, cr0, cr15, {1}
d001d2d4:	43239b14 			; <UNDEFINED> instruction: 0x43239b14
d001d2d8:	6daad10c 	stfvsd	f5, [sl, #48]!	; 0x30
d001d2dc:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d001d2e0:	f8dfaee9 			; <UNDEFINED> instruction: 0xf8dfaee9
d001d2e4:	66af27bc 			; <UNDEFINED> instruction: 0x66af27bc
d001d2e8:	e9c5447a 	stmib	r5, {r1, r3, r4, r5, r6, sl, lr}^
d001d2ec:	e9c5a918 	stmib	r5, {r3, r4, r8, fp, sp, pc}^
d001d2f0:	e6df2b16 			; <UNDEFINED> instruction: 0xe6df2b16
d001d2f4:	f8cdab3a 			; <UNDEFINED> instruction: 0xf8cdab3a
d001d2f8:	f8cdb0e4 			; <UNDEFINED> instruction: 0xf8cdb0e4
d001d2fc:	f88da0e8 			; <UNDEFINED> instruction: 0xf88da0e8
d001d300:	973d90f0 			; <UNDEFINED> instruction: 0x973d90f0
d001d304:	f8cd9405 			; <UNDEFINED> instruction: 0xf8cd9405
d001d308:	cb0f8010 	blgt	0xd03fd350
d001d30c:	000fe88d 	andeq	lr, pc, sp, lsl #17
d001d310:	000fe896 	muleq	pc, r6, r8	; <UNPREDICTABLE>
d001d314:	fde8f7fe 	stc2l	7, cr15, [r8, #1016]!	; 0x3f8
d001d318:	f7f3e6cc 			; <UNDEFINED> instruction: 0xf7f3e6cc
d001d31c:	2800fac3 	stmdacs	r0, {r0, r1, r6, r7, r9, fp, ip, sp, lr, pc}
d001d320:	81daf000 	bicshi	pc, sl, r0
d001d324:	f8dfb124 			; <UNDEFINED> instruction: 0xf8dfb124
d001d328:	4479177c 	ldrbtmi	r1, [r9], #-1916	; 0xfffff884
d001d32c:	e2604628 	rsb	r4, r0, #40, 12	; 0x2800000
d001d330:	4628a92e 	strtmi	sl, [r8], -lr, lsr #18
d001d334:	f7f5942e 			; <UNDEFINED> instruction: 0xf7f5942e
d001d338:	2800fff1 	stmdacs	r0, {r0, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d001d33c:	aebaf43f 	mrcge	4, 5, APSR_nzcv, cr10, cr15, {1}
d001d340:	0718f105 	ldreq	pc, [r8, -r5, lsl #2]
d001d344:	4628212a 	strtmi	r2, [r8], -sl, lsr #2
d001d348:	f7f5ae36 			; <UNDEFINED> instruction: 0xf7f5ae36
d001d34c:	4604fddd 			; <UNDEFINED> instruction: 0x4604fddd
d001d350:	a030f895 	mlasge	r0, r5, r8, pc	; <UNPREDICTABLE>
d001d354:	c60fcf0f 	strgt	ip, [pc], -pc, lsl #30
d001d358:	000fe897 	muleq	pc, r7, r8	; <UNPREDICTABLE>
d001d35c:	000fe886 	andeq	lr, pc, r6, lsl #17
d001d360:	f2406a6b 	vpmax.s8	q11, q0, <illegal reg q13.5>
d001d364:	f8df1101 			; <UNDEFINED> instruction: 0xf8df1101
d001d368:	46282740 	strtmi	r2, [r8], -r0, asr #14
d001d36c:	6aab9310 	bvs	0xceb01fb4
d001d370:	930f447a 	movwls	r4, #62586	; 0xf47a
d001d374:	e9d56b6b 	ldmib	r5, {r0, r1, r3, r5, r6, r8, r9, fp, sp, lr}^
d001d378:	9311b906 	tstls	r1, #98304	; 0x18000
d001d37c:	fdd2f7f5 	ldc2l	7, cr15, [r2, #980]	; 0x3d4
d001d380:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001d384:	6aebae97 	bvs	0xcfb08de8
d001d388:	d14a2b28 	cmple	sl, r8, lsr #22
d001d38c:	2c009b2e 			; <UNDEFINED> instruction: 0x2c009b2e
d001d390:	ac1eae36 	ldcge	14, cr10, [lr], {54}	; 0x36
d001d394:	bf149316 	svclt	0x00149316
d001d398:	23042305 	movwcs	r2, #17157	; 0x4305
d001d39c:	a0f0f88d 	rscsge	pc, r0, sp, lsl #17
d001d3a0:	93134625 	tstls	r3, #38797312	; 0x2500000
d001d3a4:	93399b10 	teqls	r9, #16, 22	; 0x4000
d001d3a8:	933a9b0f 	teqls	sl, #15360	; 0x3c00
d001d3ac:	e9cd9b11 	stmib	sp, {r0, r4, r8, r9, fp, ip, pc}^
d001d3b0:	933db936 	teqls	sp, #884736	; 0xd8000
d001d3b4:	c50fce0f 	strgt	ip, [pc, #-3599]	; 0xd001c5ad
d001d3b8:	000fe896 	muleq	pc, r6, r8	; <UNPREDICTABLE>
d001d3bc:	000fe885 	andeq	lr, pc, r5, lsl #17
d001d3c0:	ae269b10 	vmovge.32	d6[1], r9
d001d3c4:	907cf8cd 	rsbsls	pc, ip, sp, asr #17
d001d3c8:	9b0f9321 	blls	0xd0402054
d001d3cc:	9b119322 	blls	0xd048205c
d001d3d0:	a090f88d 	addsge	pc, r0, sp, lsl #17
d001d3d4:	cc0f9325 	stcgt	3, cr9, [pc], {37}	; 0x25
d001d3d8:	e895c60f 	ldm	r5, {r0, r1, r2, r3, r9, sl, lr, pc}
d001d3dc:	e886000f 	stm	r6, {r0, r1, r2, r3}
d001d3e0:	f8df000f 			; <UNDEFINED> instruction: 0xf8df000f
d001d3e4:	212846c8 	smlawtcs	r8, r8, r6, r4
d001d3e8:	26c4f8df 			; <UNDEFINED> instruction: 0x26c4f8df
d001d3ec:	447a447c 	ldrbtmi	r4, [sl], #-1148	; 0xfffffb84
d001d3f0:	f7f54620 			; <UNDEFINED> instruction: 0xf7f54620
d001d3f4:	2800fd97 	stmdacs	r0, {r0, r1, r2, r4, r7, r8, sl, fp, ip, sp, lr, pc}
d001d3f8:	ae5cf43f 	mrcge	4, 2, APSR_nzcv, cr12, cr15, {1}
d001d3fc:	4659464a 	ldrbmi	r4, [r9], -sl, asr #12
d001d400:	f7f34620 			; <UNDEFINED> instruction: 0xf7f34620
d001d404:	2800fa2a 	stmdacs	r0, {r1, r3, r5, r9, fp, ip, sp, lr, pc}
d001d408:	8225f2c0 	eorhi	pc, r5, #192, 4
d001d40c:	36a4f8df 	ssatcc	pc, #5, pc, asr #17	; <UNPREDICTABLE>
d001d410:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d001d414:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d001d418:	f8dfae4d 			; <UNDEFINED> instruction: 0xf8dfae4d
d001d41c:	447a269c 	ldrbtmi	r2, [sl], #-1692	; 0xfffff964
d001d420:	b17ce01c 	cmnlt	ip, ip, lsl r0
d001d424:	2b006dab 	blcs	0xd0038ad8
d001d428:	ae44f47f 	mcrge	4, 2, pc, cr4, cr15, {3}	; <UNPREDICTABLE>
d001d42c:	368cf8df 	pkhtbcc	pc, ip, pc, asr #17	; <UNPREDICTABLE>
d001d430:	65ab447b 	strvs	r4, [fp, #1147]!	; 0x47b
d001d434:	65eb9b10 	strbvs	r9, [fp, #2832]!	; 0xb10
d001d438:	e9c59b0f 	stmib	r5, {r0, r1, r2, r3, r8, r9, fp, ip, pc}^
d001d43c:	9b113a18 	blls	0xd046bca4
d001d440:	e63766ab 	ldrt	r6, [r7], -fp, lsr #13
d001d444:	b9939b14 	ldmiblt	r3, {r2, r4, r8, r9, fp, ip, pc}
d001d448:	2b006dab 	blcs	0xd0038afc
d001d44c:	ae32f47f 	mrcge	4, 1, APSR_nzcv, cr2, cr15, {3}
d001d450:	366cf8df 			; <UNDEFINED> instruction: 0x366cf8df
d001d454:	266cf8df 			; <UNDEFINED> instruction: 0x266cf8df
d001d458:	447a447b 	ldrbtmi	r4, [sl], #-1147	; 0xfffffb85
d001d45c:	9a10659a 	bls	0xd0436acc
d001d460:	9a0f65da 	bls	0xd03f6bd0
d001d464:	2a18e9c3 	bcs	0xd0657b78
d001d468:	669a9a11 			; <UNDEFINED> instruction: 0x669a9a11
d001d46c:	4628e622 	strtmi	lr, [r8], -r2, lsr #12
d001d470:	f7f5215b 			; <UNDEFINED> instruction: 0xf7f5215b
d001d474:	9b2efd49 	blls	0xd0bdc9a0
d001d478:	721af44f 	andsvc	pc, sl, #1325400064	; 0x4f000000
d001d47c:	fb024680 	blx	0xd00aee86
d001d480:	f5055503 			; <UNDEFINED> instruction: 0xf5055503
d001d484:	8d2e3568 	cfstr32hi	mvfx3, [lr, #-416]!	; 0xfffffe60
d001d488:	d0762800 	rsbsle	r2, r6, r0, lsl #16
d001d48c:	5638f8df 			; <UNDEFINED> instruction: 0x5638f8df
d001d490:	6aea447d 	bvs	0xcfaae68c
d001d494:	7281f5a2 	addvc	pc, r1, #679477248	; 0x28800000
d001d498:	d8082a01 	stmdale	r8, {r0, r9, fp, sp}
d001d49c:	b1376a2f 	teqlt	r7, pc, lsr #20
d001d4a0:	f44f00b1 	vst4.32	{d16-d19}, [pc :256], r1
d001d4a4:	fbb21280 	blx	0xceca1eae
d001d4a8:	4297f2f1 	addsmi	pc, r7, #268435471	; 0x1000000f
d001d4ac:	f8dfd924 			; <UNDEFINED> instruction: 0xf8dfd924
d001d4b0:	f44f261c 	vst1.8	{d18-d20}, [pc :64], ip
d001d4b4:	447a711a 	ldrbtmi	r7, [sl], #-282	; 0xfffffee6
d001d4b8:	2303fb01 	movwcs	pc, #15105	; 0x3b01	; <UNPREDICTABLE>
d001d4bc:	3368f503 	msrcc	SPSR_f, #12582912	; 0xc00000
d001d4c0:	302bf893 	mlacc	fp, r3, r8, pc	; <UNPREDICTABLE>
d001d4c4:	f8dfb9a3 			; <UNDEFINED> instruction: 0xf8dfb9a3
d001d4c8:	447a2608 	ldrbtmi	r2, [sl], #-1544	; 0xfffff9f8
d001d4cc:	3604f8df 			; <UNDEFINED> instruction: 0x3604f8df
d001d4d0:	6d99447b 	cfldrsvs	mvf4, [r9, #492]	; 0x1ec
d001d4d4:	f47f2900 			; <UNDEFINED> instruction: 0xf47f2900
d001d4d8:	6a5daded 	bvs	0xd1788c94
d001d4dc:	6b596a9c 	blvs	0xd1677f54
d001d4e0:	0030f893 	mlaseq	r0, r3, r8, pc	; <UNPREDICTABLE>
d001d4e4:	e9c36699 	stmib	r3, {r0, r3, r4, r7, r9, sl, sp, lr}^
d001d4e8:	e9c32516 	stmib	r3, {r1, r2, r4, r8, sl, sp}^
d001d4ec:	e5e14018 	strb	r4, [r1, #24]!
d001d4f0:	25e4f8df 	strbcs	pc, [r4, #2271]!	; 0x8df	; <UNPREDICTABLE>
d001d4f4:	e7e9447a 			; <UNDEFINED> instruction: 0xe7e9447a
d001d4f8:	f7f54628 			; <UNDEFINED> instruction: 0xf7f54628
d001d4fc:	f8dffce5 			; <UNDEFINED> instruction: 0xf8dffce5
d001d500:	215d25dc 	ldrsbcs	r2, [sp, #-92]	; 0xffffffa4
d001d504:	447a4628 	ldrbtmi	r4, [sl], #-1576	; 0xfffff9d8
d001d508:	fd0cf7f5 	stc2	7, cr15, [ip, #-980]	; 0xfffffc2c
d001d50c:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001d510:	f8dfadd1 			; <UNDEFINED> instruction: 0xf8dfadd1
d001d514:	213d05cc 	teqcs	sp, ip, asr #11
d001d518:	4478437e 	ldrbtmi	r4, [r8], #-894	; 0xfffffc82
d001d51c:	357ff500 	ldrbcc	pc, [pc, #-1280]!	; 0xd001d024	; <UNPREDICTABLE>
d001d520:	3224f8d5 	eorcc	pc, r4, #13959168	; 0xd50000
d001d524:	f7f59312 			; <UNDEFINED> instruction: 0xf7f59312
d001d528:	b138fcef 	teqlt	r8, pc, ror #25	; <UNPREDICTABLE>
d001d52c:	3224f8d5 	eorcc	pc, r4, #13959168	; 0xd50000
d001d530:	13bef5c3 			; <UNDEFINED> instruction: 0x13bef5c3
d001d534:	d922429e 	stmdble	r2!, {r1, r2, r3, r4, r7, r9, lr}
d001d538:	fd20f7f6 	stc2	7, cr15, [r0, #-984]!	; 0xfffffc28
d001d53c:	55a4f8df 	strpl	pc, [r4, #2271]!	; 0x8df
d001d540:	f8df213b 			; <UNDEFINED> instruction: 0xf8df213b
d001d544:	447d25a4 	ldrbtmi	r2, [sp], #-1444	; 0xfffffa5c
d001d548:	4628447a 			; <UNDEFINED> instruction: 0x4628447a
d001d54c:	fceaf7f5 	stc2l	7, cr15, [sl], #980	; 0x3d4
d001d550:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001d554:	464aadaf 	strbmi	sl, [sl], -pc, lsr #27
d001d558:	46284659 			; <UNDEFINED> instruction: 0x46284659
d001d55c:	f97df7f3 			; <UNDEFINED> instruction: 0xf97df7f3
d001d560:	db332800 	blle	0xd0ce7568
d001d564:	3584f8df 	strcc	pc, [r4, #2271]	; 0x8df
d001d568:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d001d56c:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d001d570:	f8dfada1 			; <UNDEFINED> instruction: 0xf8dfada1
d001d574:	447a257c 	ldrbtmi	r2, [sl], #-1404	; 0xfffffa84
d001d578:	2701e770 	smlsdxcs	r1, r0, r7, lr
d001d57c:	4630e7c9 	ldrtmi	lr, [r0], -r9, asr #15
d001d580:	fbb2f7fe 	blx	0xcecdb582
d001d584:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001d588:	982ead95 	stmdals	lr!, {r0, r2, r4, r7, r8, sl, fp, sp, pc}
d001d58c:	0f00f1b8 	svceq	0x0000f1b8
d001d590:	2200d016 	andcs	sp, r0, #22
d001d594:	23014601 	movwcs	r4, #5633	; 0x1601
d001d598:	92004638 	andls	r4, r0, #56, 12	; 0x3800000
d001d59c:	fe98f7fc 	mrc2	7, 4, pc, cr8, cr12, {7}
d001d5a0:	3550f8df 	ldrbcc	pc, [r0, #-2271]	; 0xfffff721	; <UNPREDICTABLE>
d001d5a4:	f503447b 			; <UNDEFINED> instruction: 0xf503447b
d001d5a8:	f893337f 			; <UNDEFINED> instruction: 0xf893337f
d001d5ac:	2a002220 	bcs	0xd0025e34
d001d5b0:	f8d3d0c4 			; <UNDEFINED> instruction: 0xf8d3d0c4
d001d5b4:	24012224 	strcs	r2, [r1], #-548	; 0xfffffddc
d001d5b8:	f8c34432 			; <UNDEFINED> instruction: 0xf8c34432
d001d5bc:	e7bd2224 	ldr	r2, [sp, r4, lsr #4]!
d001d5c0:	46412301 	strbmi	r2, [r1], -r1, lsl #6
d001d5c4:	f7fc461a 			; <UNDEFINED> instruction: 0xf7fc461a
d001d5c8:	e7e9fd5d 	ubfx	pc, sp, #26, #10
d001d5cc:	4659464a 	ldrbmi	r4, [r9], -sl, asr #12
d001d5d0:	f7f34628 			; <UNDEFINED> instruction: 0xf7f34628
d001d5d4:	2800f91d 	stmdacs	r0, {r0, r2, r3, r4, r8, fp, ip, sp, lr, pc}
d001d5d8:	464adac4 	strbmi	sp, [sl], -r4, asr #21
d001d5dc:	46284659 			; <UNDEFINED> instruction: 0x46284659
d001d5e0:	f97ff7f3 			; <UNDEFINED> instruction: 0xf97ff7f3
d001d5e4:	dabd2800 	ble	0xcef675ec
d001d5e8:	3267f505 	rsbcc	pc, r7, #20971520	; 0x1400000
d001d5ec:	f8d200b3 			; <UNDEFINED> instruction: 0xf8d200b3
d001d5f0:	298011c4 	stmibcs	r0, {r2, r6, r7, r8, ip}
d001d5f4:	f505d008 			; <UNDEFINED> instruction: 0xf505d008
d001d5f8:	b984327f 	stmiblt	r4, {r0, r1, r2, r3, r4, r5, r6, r9, ip, sp}
d001d5fc:	521cf8d2 	andspl	pc, ip, #13762560	; 0xd20000
d001d600:	1080f5c3 	addne	pc, r0, r3, asr #11
d001d604:	d9604285 	stmdble	r0!, {r0, r2, r7, r9, lr}^
d001d608:	34ecf8df 	strbtcc	pc, [ip], #2271	; 0x8df	; <UNPREDICTABLE>
d001d60c:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d001d610:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d001d614:	f8dfad4f 			; <UNDEFINED> instruction: 0xf8dfad4f
d001d618:	447a24e4 	ldrbtmi	r2, [sl], #-1252	; 0xfffffb1c
d001d61c:	f8d2e71e 			; <UNDEFINED> instruction: 0xf8d2e71e
d001d620:	35035218 	strcc	r5, [r3, #-536]	; 0xfffffde8
d001d624:	0503f025 	streq	pc, [r3, #-37]	; 0xffffffdb
d001d628:	f8c2442b 			; <UNDEFINED> instruction: 0xf8c2442b
d001d62c:	f8df3218 			; <UNDEFINED> instruction: 0xf8df3218
d001d630:	f1b834d0 			; <UNDEFINED> instruction: 0xf1b834d0
d001d634:	f1010f00 			; <UNDEFINED> instruction: 0xf1010f00
d001d638:	fa5f0001 	blx	0xd17dd644
d001d63c:	447bf884 	ldrbtmi	pc, [fp], #-2180	; 0xfffff77c	; <UNPREDICTABLE>
d001d640:	3267f503 	rsbcc	pc, r7, #12582912	; 0xc00000
d001d644:	01c4f8c2 	biceq	pc, r4, r2, asr #17
d001d648:	2211bf14 	andscs	fp, r1, #20, 30	; 0x50
d001d64c:	2c00220f 	sfmcs	f2, 4, [r0], {15}
d001d650:	bf089215 	svclt	0x00089215
d001d654:	7a1a2600 	bvc	0xd06a6e5c
d001d658:	f89d9213 			; <UNDEFINED> instruction: 0xf89d9213
d001d65c:	921420b8 	andsls	r2, r4, #184	; 0xb8
d001d660:	fb02223c 	blx	0xd00a5f5a
d001d664:	21003401 	tstcs	r0, r1, lsl #8
d001d668:	345ff504 	ldrbcc	pc, [pc], #-1284	; 0xd001d670	; <UNPREDICTABLE>
d001d66c:	7371f504 	cmnvc	r1, #4, 10	; 0x1000000	; <UNPREDICTABLE>
d001d670:	f0034618 			; <UNDEFINED> instruction: 0xf0034618
d001d674:	9a10ffcd 	bls	0xd045d5b0
d001d678:	0ed8f10d 	atneqe	f7, #5.0
d001d67c:	a0f0f88d 	rscsge	pc, r0, sp, lsl #17
d001d680:	46849239 			; <UNDEFINED> instruction: 0x46849239
d001d684:	f8c49a0f 			; <UNDEFINED> instruction: 0xf8c49a0f
d001d688:	923a53e8 	eorsls	r5, sl, #232, 6	; 0xa0000003
d001d68c:	e9cd9a11 	stmib	sp, {r0, r4, r9, fp, ip, pc}^
d001d690:	923db936 	eorsls	fp, sp, #884736	; 0xd8000
d001d694:	000fe8be 			; <UNDEFINED> instruction: 0x000fe8be
d001d698:	000fe8ac 	andeq	lr, pc, ip, lsr #17
d001d69c:	000fe89e 	muleq	pc, lr, r8	; <UNPREDICTABLE>
d001d6a0:	000fe88c 	andeq	lr, pc, ip, lsl #17
d001d6a4:	f8849b15 			; <UNDEFINED> instruction: 0xf8849b15
d001d6a8:	9b1333ec 	blls	0xd04ea660
d001d6ac:	33edf884 	mvncc	pc, #132, 16	; 0x840000
d001d6b0:	f8849b14 			; <UNDEFINED> instruction: 0xf8849b14
d001d6b4:	f88433ee 			; <UNDEFINED> instruction: 0xf88433ee
d001d6b8:	9b1283ef 	blls	0xd04be67c
d001d6bc:	63f8f8c4 	mvnsvs	pc, #196, 16	; 0xc40000
d001d6c0:	33f4f8c4 	mvnscc	pc, #196, 16	; 0xc40000
d001d6c4:	73fcf8c4 	mvnsvc	pc, #196, 16	; 0xc40000
d001d6c8:	3503e4f4 	strcc	lr, [r3, #-1268]	; 0xfffffb0c
d001d6cc:	0503f025 	streq	pc, [r3, #-37]	; 0xffffffdb
d001d6d0:	f8c2442b 			; <UNDEFINED> instruction: 0xf8c2442b
d001d6d4:	e7aa321c 			; <UNDEFINED> instruction: 0xe7aa321c
d001d6d8:	b9239b14 	stmdblt	r3!, {r2, r4, r8, r9, fp, ip, pc}
d001d6dc:	1109f240 	tstne	r9, r0, asr #4	; <UNPREDICTABLE>
d001d6e0:	f7f54628 			; <UNDEFINED> instruction: 0xf7f54628
d001d6e4:	f8dffc11 			; <UNDEFINED> instruction: 0xf8dffc11
d001d6e8:	f44f041c 	vst3.8	{d16-d18}, [pc :64], ip
d001d6ec:	44787184 	ldrbtmi	r7, [r8], #-388	; 0xfffffe7c
d001d6f0:	fc0af7f5 	stc2	7, cr15, [sl], {245}	; 0xf5
d001d6f4:	28004605 	stmdacs	r0, {r0, r2, r9, sl, lr}
d001d6f8:	f8dfd17e 			; <UNDEFINED> instruction: 0xf8dfd17e
d001d6fc:	4478040c 	ldrbtmi	r0, [r8], #-1036	; 0xfffffbf4
d001d700:	f90cf7f7 			; <UNDEFINED> instruction: 0xf90cf7f7
d001d704:	28004682 	stmdacs	r0, {r1, r7, r9, sl, lr}
d001d708:	9b14d179 	blls	0xd0551cf4
d001d70c:	4dffb993 			; <UNDEFINED> instruction: 0x4dffb993
d001d710:	1107f240 	tstne	r7, r0, asr #4	; <UNPREDICTABLE>
d001d714:	4628447d 			; <UNDEFINED> instruction: 0x4628447d
d001d718:	fbf6f7f5 	blx	0xcfddb6f6
d001d71c:	d0462800 	suble	r2, r6, r0, lsl #16
d001d720:	212a48fb 	strdcs	r4, [sl, -fp]!
d001d724:	f7f54478 			; <UNDEFINED> instruction: 0xf7f54478
d001d728:	2800fbef 	stmdacs	r0, {r0, r1, r2, r3, r5, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d001d72c:	2500d06d 	strcs	sp, [r0, #-109]	; 0xffffff93
d001d730:	e0122303 	ands	r2, r2, r3, lsl #6
d001d734:	447848f7 	ldrbtmi	r4, [r8], #-2295	; 0xfffff709
d001d738:	f8f0f7f7 			; <UNDEFINED> instruction: 0xf8f0f7f7
d001d73c:	d1602800 	cmnle	r0, r0, lsl #16
d001d740:	447848f5 	ldrbtmi	r4, [r8], #-2293	; 0xfffff70b
d001d744:	f8eaf7f7 			; <UNDEFINED> instruction: 0xf8eaf7f7
d001d748:	48f4b928 	ldmmi	r4!, {r3, r5, r8, fp, ip, sp, pc}^
d001d74c:	f7f74478 			; <UNDEFINED> instruction: 0xf7f74478
d001d750:	2800f8e5 	stmdacs	r0, {r0, r2, r5, r6, r7, fp, ip, sp, lr, pc}
d001d754:	2505d0db 	strcs	sp, [r5, #-219]	; 0xffffff25
d001d758:	93132300 	tstls	r3, #0, 6
d001d75c:	af264ef0 	svcge	0x00264ef0
d001d760:	f106447e 			; <UNDEFINED> instruction: 0xf106447e
d001d764:	f8960c18 			; <UNDEFINED> instruction: 0xf8960c18
d001d768:	e8bca030 	ldm	ip!, {r4, r5, sp, pc}
d001d76c:	c70f000f 	strgt	r0, [pc, -pc]
d001d770:	000fe89c 	muleq	pc, ip, r8	; <UNPREDICTABLE>
d001d774:	000fe887 	andeq	lr, pc, r7, lsl #17
d001d778:	46306a73 			; <UNDEFINED> instruction: 0x46306a73
d001d77c:	f2404ae9 	vpmax.s8	q10, q8, <illegal reg q12.5>
d001d780:	93101101 	tstls	r0, #1073741824	; 0x40000000
d001d784:	447a6ab3 	ldrbtmi	r6, [sl], #-2739	; 0xfffff54d
d001d788:	6b73930f 	blvs	0xd1d023cc
d001d78c:	b906e9d6 	stmdblt	r6, {r1, r2, r4, r6, r7, r8, fp, sp, lr, pc}
d001d790:	ae269311 	mcrge	3, 1, r9, cr6, cr1, {0}
d001d794:	fbc6f7f5 	blx	0xcf1db772
d001d798:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001d79c:	9b14ac8b 	blls	0xd05489d0
d001d7a0:	2c00bbb3 			; <UNDEFINED> instruction: 0x2c00bbb3
d001d7a4:	8578f040 	ldrbhi	pc, [r8, #-64]!	; 0xffffffc0	; <UNPREDICTABLE>
d001d7a8:	931623ff 	tstls	r6, #-67108861	; 0xfc000003
d001d7ac:	6aeae619 	bvs	0xcfad7018
d001d7b0:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d001d7b4:	d118429a 			; <UNDEFINED> instruction: 0xd118429a
d001d7b8:	e9d54628 	ldmib	r5, {r3, r5, r9, sl, lr}^
d001d7bc:	f7f31206 			; <UNDEFINED> instruction: 0xf7f31206
d001d7c0:	2800f84c 	stmdacs	r0, {r2, r3, r6, fp, ip, sp, lr, pc}
d001d7c4:	4628db11 			; <UNDEFINED> instruction: 0x4628db11
d001d7c8:	1206e9d5 	andne	lr, r6, #3489792	; 0x354000
d001d7cc:	f845f7f3 			; <UNDEFINED> instruction: 0xf845f7f3
d001d7d0:	fb032324 	blx	0xd00e646a
d001d7d4:	f5005000 			; <UNDEFINED> instruction: 0xf5005000
d001d7d8:	f8903075 			; <UNDEFINED> instruction: 0xf8903075
d001d7dc:	2bff33ac 	blcs	0xcffea694
d001d7e0:	4628d103 	strtmi	sp, [r8], -r3, lsl #2
d001d7e4:	fb70f7f5 	blx	0xd1c5b7c2
d001d7e8:	49cfe79a 	stmibmi	pc, {r1, r3, r4, r7, r8, r9, sl, sp, lr, pc}^	; <UNPREDICTABLE>
d001d7ec:	447948cf 	ldrbtmi	r4, [r9], #-2255	; 0xfffff731
d001d7f0:	f7f24478 			; <UNDEFINED> instruction: 0xf7f24478
d001d7f4:	e45dfd3d 	ldrb	pc, [sp], #-3389	; 0xfffff2c3	; <UNPREDICTABLE>
d001d7f8:	23012500 	movwcs	r2, #5376	; 0x1500
d001d7fc:	2302e7ad 	movwcs	lr, #10157	; 0x27ad
d001d800:	2501e7ab 	strcs	lr, [r1, #-1963]	; 0xfffff855
d001d804:	a04cf8cd 	subge	pc, ip, sp, asr #17
d001d808:	4605e7a8 	strmi	lr, [r5], -r8, lsr #15
d001d80c:	e7a59013 			; <UNDEFINED> instruction: 0xe7a59013
d001d810:	b93b9b13 	ldmdblt	fp!, {r0, r1, r4, r8, r9, fp, ip, pc}
d001d814:	f0402d00 			; <UNDEFINED> instruction: 0xf0402d00
d001d818:	4bc58504 	blmi	0xcf17ec30
d001d81c:	6adb447b 	bvs	0xcf6eea10
d001d820:	d10a2b28 	tstle	sl, r8, lsr #22
d001d824:	d0bf2c00 	adcsle	r2, pc, r0, lsl #24
d001d828:	447b4bc2 	ldrbtmi	r4, [fp], #-3010	; 0xfffff43e
d001d82c:	2a006d9a 	bcs	0xd0038e9c
d001d830:	ac40f47f 	cfstrdge	mvd15, [r0], {127}	; 0x7f
d001d834:	447a4ac0 	ldrbtmi	r4, [sl], #-2752	; 0xfffff540
d001d838:	9b10e610 	blls	0xd0457080
d001d83c:	a0b0f88d 	adcsge	pc, r0, sp, lsl #17
d001d840:	9b0f9329 	blls	0xd04024ec
d001d844:	932a9405 			; <UNDEFINED> instruction: 0x932a9405
d001d848:	95049b11 	strls	r9, [r4, #-2833]	; 0xfffff4ef
d001d84c:	ab2a932d 	blge	0xd0ac2508
d001d850:	b926e9cd 	stmdblt	r6!, {r0, r2, r3, r6, r7, r8, fp, sp, lr, pc}
d001d854:	464ae559 			; <UNDEFINED> instruction: 0x464ae559
d001d858:	46204659 			; <UNDEFINED> instruction: 0x46204659
d001d85c:	ffd8f7f2 			; <UNDEFINED> instruction: 0xffd8f7f2
d001d860:	f6bf2800 			; <UNDEFINED> instruction: 0xf6bf2800
d001d864:	4ab5add3 	bmi	0xced88fb8
d001d868:	46584649 	ldrbmi	r4, [r8], -r9, asr #12
d001d86c:	f7f3447a 			; <UNDEFINED> instruction: 0xf7f3447a
d001d870:	bb40f861 	bllt	0xd105b9fc
d001d874:	46494ab2 			; <UNDEFINED> instruction: 0x46494ab2
d001d878:	447a4658 	ldrbtmi	r4, [sl], #-1624	; 0xfffff9a8
d001d87c:	f85af7f3 			; <UNDEFINED> instruction: 0xf85af7f3
d001d880:	4ab0bb18 	bmi	0xcec4c4e8
d001d884:	46584649 	ldrbmi	r4, [r8], -r9, asr #12
d001d888:	f7f3447a 			; <UNDEFINED> instruction: 0xf7f3447a
d001d88c:	2800f853 	stmdacs	r0, {r0, r1, r4, r6, fp, ip, sp, lr, pc}
d001d890:	2300bf0c 	movwcs	fp, #3852	; 0xf0c
d001d894:	4aac230c 	bmi	0xceb264cc
d001d898:	46584649 	ldrbmi	r4, [r8], -r9, asr #12
d001d89c:	447a9315 	ldrbtmi	r9, [sl], #-789	; 0xfffffceb
d001d8a0:	f848f7f3 			; <UNDEFINED> instruction: 0xf848f7f3
d001d8a4:	90179b15 	andsls	r9, r7, r5, lsl fp
d001d8a8:	d0104303 	andsle	r4, r0, r3, lsl #6
d001d8ac:	9a139b14 	bls	0xd0504504
d001d8b0:	d00c4313 	andle	r4, ip, r3, lsl r3
d001d8b4:	447b4ba5 	ldrbtmi	r4, [fp], #-2981	; 0xfffff45b
d001d8b8:	2a006d9a 	bcs	0xd0038f28
d001d8bc:	abfaf47f 	blge	0xcfedaac0
d001d8c0:	447a4aa3 	ldrbtmi	r4, [sl], #-2723	; 0xfffff55d
d001d8c4:	2304e5ca 	movwcs	lr, #17866	; 0x45ca
d001d8c8:	2308e7e5 	movwcs	lr, #34789	; 0x87e5
d001d8cc:	9b15e7e3 	blls	0xd0597860
d001d8d0:	af1a2400 	svcge	0x001a2400
d001d8d4:	941c2b04 	ldrls	r2, [ip], #-2820	; 0xfffff4fc
d001d8d8:	4074f88d 	rsbsmi	pc, r4, sp, lsl #17
d001d8dc:	713c603c 	teqvc	ip, ip, lsr r0
d001d8e0:	4c9cd149 	ldfmid	f5, [ip], {73}	; 0x49
d001d8e4:	7185f44f 	orrvc	pc, r5, pc, asr #8
d001d8e8:	447c4a9b 	ldrbtmi	r4, [ip], #-2715	; 0xfffff565
d001d8ec:	4620447a 			; <UNDEFINED> instruction: 0x4620447a
d001d8f0:	f7f59212 			; <UNDEFINED> instruction: 0xf7f59212
d001d8f4:	2800fb17 	stmdacs	r0, {r0, r1, r2, r4, r8, r9, fp, ip, sp, lr, pc}
d001d8f8:	abdcf43f 	blge	0xcf75a9fc
d001d8fc:	f2409a12 	vpmin.s8	d25, d0, d2
d001d900:	4620110b 	strtmi	r1, [r0], -fp, lsl #2
d001d904:	fb0ef7f5 	blx	0xd03db8e2
d001d908:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001d90c:	9a12abd3 	bls	0xd04c8860
d001d910:	4620212a 	strtmi	r2, [r0], -sl, lsr #2
d001d914:	fb06f7f5 	blx	0xd01db8f2
d001d918:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001d91c:	f240abcb 	vqdmulh.s<illegal width 8>	q13, q8, <illegal reg q5.5>
d001d920:	46201101 	strtmi	r1, [r0], -r1, lsl #2
d001d924:	faf0f7f5 	blx	0xcfc5b900
d001d928:	703b2302 	eorsvc	r2, fp, r2, lsl #6
d001d92c:	93122301 	tstls	r2, #67108864	; 0x4000000
d001d930:	21294c8a 	smlawbcs	r9, sl, ip, r4
d001d934:	447c4a8a 	ldrbtmi	r4, [ip], #-2698	; 0xfffff576
d001d938:	4620447a 			; <UNDEFINED> instruction: 0x4620447a
d001d93c:	faf2f7f5 	blx	0xcfcdb918
d001d940:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001d944:	9b13abb7 	blls	0xd0508828
d001d948:	f0402b04 			; <UNDEFINED> instruction: 0xf0402b04
d001d94c:	9b1281e7 	blls	0xd04be0f0
d001d950:	f0402b05 			; <UNDEFINED> instruction: 0xf0402b05
d001d954:	6da381e3 	stfvsd	f0, [r3, #908]!	; 0x38c
d001d958:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001d95c:	4b81abab 	blmi	0xce088810
d001d960:	65a3447b 	strvs	r4, [r3, #1147]!	; 0x47b
d001d964:	65e39b10 	strbvs	r9, [r3, #2832]!	; 0xb10
d001d968:	e9c49b0f 	stmib	r4, {r0, r1, r2, r3, r8, r9, fp, ip, pc}^
d001d96c:	9b113a18 	blls	0xd046c1d4
d001d970:	f7ff66a3 			; <UNDEFINED> instruction: 0xf7ff66a3
d001d974:	487cbb9f 	ldmdami	ip!, {r0, r1, r2, r3, r4, r7, r8, r9, fp, ip, sp, pc}^
d001d978:	6ac34478 	bvs	0xcf0eeb60
d001d97c:	7f84f5b3 	svcvc	0x0084f5b3
d001d980:	6cc3d106 	stfvsp	f5, [r3], {6}
d001d984:	d1032b29 	tstle	r3, r9, lsr #22
d001d988:	fa9ef7f5 	blx	0xce7db964
d001d98c:	e7cf9412 	bfi	r9, r2, #8, #8
d001d990:	23004c76 	movwcs	r4, #3190	; 0xc76
d001d994:	447c4e76 	ldrbtmi	r4, [ip], #-3702	; 0xfffff18a
d001d998:	447e9312 	ldrbtmi	r9, [lr], #-786	; 0xfffffcee
d001d99c:	4850f504 	ldmdami	r0, {r2, r8, sl, ip, sp, lr, pc}^
d001d9a0:	081cf108 	ldmdaeq	ip, {r3, r8, ip, sp, lr, pc}
d001d9a4:	2b019b12 	blcs	0xd00845f4
d001d9a8:	80ecf040 	rschi	pc, ip, r0, asr #32
d001d9ac:	2b009b17 	blcs	0xd0044610
d001d9b0:	80e8f000 	rschi	pc, r8, r0
d001d9b4:	9318ab1a 	tstls	r8, #26624	; 0x6800
d001d9b8:	2b00781b 	blcs	0xd003ba2c
d001d9bc:	80e2f040 	rschi	pc, r2, r0, asr #32
d001d9c0:	f2404d6c 	vadd.f32	q10, q0, q14
d001d9c4:	447d110b 	ldrbtmi	r1, [sp], #-267	; 0xfffffef5
d001d9c8:	f7f54628 			; <UNDEFINED> instruction: 0xf7f54628
d001d9cc:	2800fa9d 	stmdacs	r0, {r0, r2, r3, r4, r7, r9, fp, ip, sp, lr, pc}
d001d9d0:	80d8f000 	sbcshi	pc, r8, r0
d001d9d4:	212a4a68 			; <UNDEFINED> instruction: 0x212a4a68
d001d9d8:	447a4628 	ldrbtmi	r4, [sl], #-1576	; 0xfffff9d8
d001d9dc:	f7f59219 			; <UNDEFINED> instruction: 0xf7f59219
d001d9e0:	2800faa1 	stmdacs	r0, {r0, r5, r7, r9, fp, ip, sp, lr, pc}
d001d9e4:	ab66f43f 	blge	0xd19daae8
d001d9e8:	212a9a19 			; <UNDEFINED> instruction: 0x212a9a19
d001d9ec:	f7f54628 			; <UNDEFINED> instruction: 0xf7f54628
d001d9f0:	2800fa99 	stmdacs	r0, {r0, r3, r4, r7, r9, fp, ip, sp, lr, pc}
d001d9f4:	ab5ef43f 	blge	0xd17daaf8
d001d9f8:	9a182304 	bls	0xd0626610
d001d9fc:	4d5f7053 	ldclmi	0, cr7, [pc, #-332]	; 0xd001d8b8
d001da00:	0cd8f10d 	ldfeqp	f7, [r8], {13}
d001da04:	447d9b12 	ldrbtmi	r9, [sp], #-2834	; 0xfffff4ee
d001da08:	1c43eb0c 	mcrrne	11, 0, lr, r3, cr12
d001da0c:	0e18f105 	mnfeqe	f7, f5
d001da10:	000fe8be 			; <UNDEFINED> instruction: 0x000fe8be
d001da14:	000fe8ac 	andeq	lr, pc, ip, lsr #17
d001da18:	000fe89e 	muleq	pc, lr, r8	; <UNPREDICTABLE>
d001da1c:	000fe88c 	andeq	lr, pc, ip, lsl #17
d001da20:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d001da24:	f7f54628 			; <UNDEFINED> instruction: 0xf7f54628
d001da28:	9b12fa6f 	blls	0xd04dc3ec
d001da2c:	93123301 	tstls	r2, #67108864	; 0x4000000
d001da30:	3b01f817 	blcc	0xd009ba94
d001da34:	f43f2b04 			; <UNDEFINED> instruction: 0xf43f2b04
d001da38:	212caf7b 			; <UNDEFINED> instruction: 0x212caf7b
d001da3c:	f7f54628 			; <UNDEFINED> instruction: 0xf7f54628
d001da40:	2800fa63 	stmdacs	r0, {r0, r1, r5, r6, r9, fp, ip, sp, lr, pc}
d001da44:	af74f43f 	svcge	0x0074f43f
d001da48:	2b059b12 	blcs	0xd0184698
d001da4c:	494cd1aa 	stmdbmi	ip, {r1, r3, r5, r7, r8, ip, lr, pc}^
d001da50:	e46b4479 	strbt	r4, [fp], #-1145	; 0xfffffb87
d001da54:	0000b34a 	andeq	fp, r0, sl, asr #6
d001da58:	0000b280 	andeq	fp, r0, r0, lsl #5
d001da5c:	fffff847 			; <UNDEFINED> instruction: 0xfffff847
d001da60:	fffff843 			; <UNDEFINED> instruction: 0xfffff843
d001da64:	fffff847 			; <UNDEFINED> instruction: 0xfffff847
d001da68:	0000b1f0 	strdeq	fp, [r0], -r0
d001da6c:	0000b18e 	andeq	fp, r0, lr, lsl #3
d001da70:	fffff7d9 			; <UNDEFINED> instruction: 0xfffff7d9
d001da74:	fffff7e0 			; <UNDEFINED> instruction: 0xfffff7e0
d001da78:	0000b126 	andeq	fp, r0, r6, lsr #2
d001da7c:	fffff7b3 			; <UNDEFINED> instruction: 0xfffff7b3
d001da80:	fffff751 			; <UNDEFINED> instruction: 0xfffff751
d001da84:	fffff789 			; <UNDEFINED> instruction: 0xfffff789
d001da88:	fffff785 			; <UNDEFINED> instruction: 0xfffff785
d001da8c:	ffff6145 			; <UNDEFINED> instruction: 0xffff6145
d001da90:	fffff6b5 			; <UNDEFINED> instruction: 0xfffff6b5
d001da94:	fffff6c4 			; <UNDEFINED> instruction: 0xfffff6c4
d001da98:	0000af84 	andeq	sl, r0, r4, lsl #31
d001da9c:	fffff64c 			; <UNDEFINED> instruction: 0xfffff64c
d001daa0:	fffff646 			; <UNDEFINED> instruction: 0xfffff646
d001daa4:	fffff62d 			; <UNDEFINED> instruction: 0xfffff62d
d001daa8:	fffff617 			; <UNDEFINED> instruction: 0xfffff617
d001daac:	0000add8 	ldrdeq	sl, [r0], -r8
d001dab0:	ffffa9b2 			; <UNDEFINED> instruction: 0xffffa9b2
d001dab4:	0000adb4 			; <UNDEFINED> instruction: 0x0000adb4
d001dab8:	ffffe946 			; <UNDEFINED> instruction: 0xffffe946
d001dabc:	fffff578 			; <UNDEFINED> instruction: 0xfffff578
d001dac0:	0000ad6c 	andeq	sl, r0, ip, ror #26
d001dac4:	fffff581 			; <UNDEFINED> instruction: 0xfffff581
d001dac8:	0000ad34 	andeq	sl, r0, r4, lsr sp
d001dacc:	0000ad0e 	andeq	sl, r0, lr, lsl #26
d001dad0:	fffff2ca 			; <UNDEFINED> instruction: 0xfffff2ca
d001dad4:	0000acf4 	strdeq	sl, [r0], -r4
d001dad8:	fffff280 			; <UNDEFINED> instruction: 0xfffff280
d001dadc:	ffffcf74 			; <UNDEFINED> instruction: 0xffffcf74
d001dae0:	0000acaa 	andeq	sl, r0, sl, lsr #25
d001dae4:	0000ac7e 	andeq	sl, r0, lr, ror ip
d001dae8:	fffff4be 			; <UNDEFINED> instruction: 0xfffff4be
d001daec:	0000ac5c 	andeq	sl, r0, ip, asr ip
d001daf0:	ffffe7ee 			; <UNDEFINED> instruction: 0xffffe7ee
d001daf4:	0000ac20 	andeq	sl, r0, r0, lsr #24
d001daf8:	0000abb8 			; <UNDEFINED> instruction: 0x0000abb8
d001dafc:	fffff419 			; <UNDEFINED> instruction: 0xfffff419
d001db00:	0000ab86 	andeq	sl, r0, r6, lsl #23
d001db04:	0000aad6 	ldrdeq	sl, [r0], -r6
d001db08:	fffff35e 			; <UNDEFINED> instruction: 0xfffff35e
d001db0c:	0000aab0 			; <UNDEFINED> instruction: 0x0000aab0
d001db10:	0000aaa0 	andeq	sl, r0, r0, lsr #21
d001db14:	ffffcdba 			; <UNDEFINED> instruction: 0xffffcdba
d001db18:	ffffcdb7 			; <UNDEFINED> instruction: 0xffffcdb7
d001db1c:	ffff611e 			; <UNDEFINED> instruction: 0xffff611e
d001db20:	0000aa64 	andeq	sl, r0, r4, ror #20
d001db24:	fffff31c 			; <UNDEFINED> instruction: 0xfffff31c
d001db28:	fffff27e 			; <UNDEFINED> instruction: 0xfffff27e
d001db2c:	0000a9d4 	ldrdeq	sl, [r0], -r4
d001db30:	0000a9a8 	andeq	sl, r0, r8, lsr #19
d001db34:	0000a99a 	muleq	r0, sl, r9
d001db38:	fffff2ac 			; <UNDEFINED> instruction: 0xfffff2ac
d001db3c:	fffff298 			; <UNDEFINED> instruction: 0xfffff298
d001db40:	fffff299 			; <UNDEFINED> instruction: 0xfffff299
d001db44:	fffff298 			; <UNDEFINED> instruction: 0xfffff298
d001db48:	fffff291 			; <UNDEFINED> instruction: 0xfffff291
d001db4c:	0000a90e 	andeq	sl, r0, lr, lsl #18
d001db50:	fffff272 			; <UNDEFINED> instruction: 0xfffff272
d001db54:	0000a8da 	ldrdeq	sl, [r0], -sl	; <UNPREDICTABLE>
d001db58:	fffff288 			; <UNDEFINED> instruction: 0xfffff288
d001db5c:	0000a88e 	andeq	sl, r0, lr, lsl #17
d001db60:	fffff387 			; <UNDEFINED> instruction: 0xfffff387
d001db64:	fffff381 			; <UNDEFINED> instruction: 0xfffff381
d001db68:	0000a84c 	andeq	sl, r0, ip, asr #16
d001db6c:	0000a82e 	andeq	sl, r0, lr, lsr #16
d001db70:	0000a82a 	andeq	sl, r0, sl, lsr #16
d001db74:	0000a7fe 	strdeq	sl, [r0], -lr
d001db78:	fffff1ef 			; <UNDEFINED> instruction: 0xfffff1ef
d001db7c:	0000a7be 			; <UNDEFINED> instruction: 0x0000a7be
d001db80:	fffff14f 			; <UNDEFINED> instruction: 0xfffff14f
d001db84:	f7f24630 			; <UNDEFINED> instruction: 0xf7f24630
d001db88:	b1e8fe8d 	mvnlt	pc, sp, lsl #29
d001db8c:	a92e2300 	stmdbge	lr!, {r8, r9, sp}
d001db90:	932e4630 			; <UNDEFINED> instruction: 0x932e4630
d001db94:	fbc2f7f5 	blx	0xcf0dbb72
d001db98:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001db9c:	212aaa8b 	smlawbcs	sl, fp, sl, sl
d001dba0:	f7f54630 			; <UNDEFINED> instruction: 0xf7f54630
d001dba4:	b168f9b1 	strhlt	pc, [r8, #-145]!	; 0xffffff6f	; <UNPREDICTABLE>
d001dba8:	4630212a 	ldrtmi	r2, [r0], -sl, lsr #2
d001dbac:	f9acf7f5 			; <UNDEFINED> instruction: 0xf9acf7f5
d001dbb0:	bf142800 	svclt	0x00142800
d001dbb4:	230e2312 	movwcs	r2, #58130	; 0xe312
d001dbb8:	ab1c703b 	blge	0xd0739cac
d001dbbc:	99129a2e 	ldmdbls	r2, {r1, r2, r3, r5, r9, fp, ip, pc}
d001dbc0:	e71c54ca 	ldr	r5, [ip, -sl, asr #9]
d001dbc4:	e7f7230d 	ldrb	r2, [r7, sp, lsl #6]!
d001dbc8:	f2406af2 	vpmin.s8	q11, q8, q9
d001dbcc:	429a131b 	addsmi	r1, sl, #1811939328	; 0x6c000000
d001dbd0:	f8dfd026 			; <UNDEFINED> instruction: 0xf8dfd026
d001dbd4:	f24056d4 	vmin.s8	<illegal reg q10.5>, q8, q2
d001dbd8:	447d1107 	ldrbtmi	r1, [sp], #-263	; 0xfffffef9
d001dbdc:	f7f54628 			; <UNDEFINED> instruction: 0xf7f54628
d001dbe0:	bb10f993 	bllt	0xd045c234
d001dbe4:	f2406aea 	vpmax.s8	q11, q8, q13
d001dbe8:	429a1301 	addsmi	r1, sl, #67108864	; 0x4000000
d001dbec:	4628d12f 	strtmi	sp, [r8], -pc, lsr #2
d001dbf0:	1206e9d5 	andne	lr, r6, #3489792	; 0x354000
d001dbf4:	fe31f7f2 	mrc2	7, 1, pc, cr1, cr2, {7}
d001dbf8:	db282800 	blle	0xd0a27c00
d001dbfc:	e9d54628 	ldmib	r5, {r3, r5, r9, sl, lr}^
d001dc00:	f7f21206 			; <UNDEFINED> instruction: 0xf7f21206
d001dc04:	2324fe2a 	msrcs	CPSR_s, #672	; 0x2a0
d001dc08:	5000fb03 	andpl	pc, r0, r3, lsl #22
d001dc0c:	3075f500 	rsbscc	pc, r5, r0, lsl #10
d001dc10:	33acf890 			; <UNDEFINED> instruction: 0x33acf890
d001dc14:	d11a2bff 			; <UNDEFINED> instruction: 0xd11a2bff
d001dc18:	f7f54628 			; <UNDEFINED> instruction: 0xf7f54628
d001dc1c:	e004f955 	and	pc, r4, r5, asr r9	; <UNPREDICTABLE>
d001dc20:	f7f54630 			; <UNDEFINED> instruction: 0xf7f54630
d001dc24:	2800fc71 	stmdacs	r0, {r0, r4, r5, r6, sl, fp, ip, sp, lr, pc}
d001dc28:	f8dfd0d3 			; <UNDEFINED> instruction: 0xf8dfd0d3
d001dc2c:	212a5680 	smlawbcs	sl, r0, r6, r5
d001dc30:	4628447d 			; <UNDEFINED> instruction: 0x4628447d
d001dc34:	f968f7f5 			; <UNDEFINED> instruction: 0xf968f7f5
d001dc38:	212ab138 			; <UNDEFINED> instruction: 0x212ab138
d001dc3c:	f7f54628 			; <UNDEFINED> instruction: 0xf7f54628
d001dc40:	2800f963 	stmdacs	r0, {r0, r1, r5, r6, r8, fp, ip, sp, lr, pc}
d001dc44:	2013bf14 	andscs	fp, r3, r4, lsl pc
d001dc48:	7038200a 	eorsvc	r2, r8, sl
d001dc4c:	f8dfe6d7 			; <UNDEFINED> instruction: 0xf8dfe6d7
d001dc50:	44780660 	ldrbtmi	r0, [r8], #-1632	; 0xfffff9a0
d001dc54:	fe62f7f6 	mcr2	7, 3, pc, cr2, cr6, {7}	; <UNPREDICTABLE>
d001dc58:	2303b110 	movwcs	fp, #12560	; 0x3110
d001dc5c:	e6ce703b 			; <UNDEFINED> instruction: 0xe6ce703b
d001dc60:	0650f8df 			; <UNDEFINED> instruction: 0x0650f8df
d001dc64:	f7f64478 			; <UNDEFINED> instruction: 0xf7f64478
d001dc68:	b108fe59 	tstlt	r8, r9, asr lr	; <UNPREDICTABLE>
d001dc6c:	e7f52301 	ldrb	r2, [r5, r1, lsl #6]!
d001dc70:	0644f8df 			; <UNDEFINED> instruction: 0x0644f8df
d001dc74:	f7f64478 			; <UNDEFINED> instruction: 0xf7f64478
d001dc78:	b108fe51 	tstlt	r8, r1, asr lr	; <UNPREDICTABLE>
d001dc7c:	e7ed2305 	strb	r2, [sp, r5, lsl #6]!
d001dc80:	0638f8df 			; <UNDEFINED> instruction: 0x0638f8df
d001dc84:	f7f64478 			; <UNDEFINED> instruction: 0xf7f64478
d001dc88:	2800fe49 	stmdacs	r0, {r0, r3, r6, r9, sl, fp, ip, sp, lr, pc}
d001dc8c:	f8d8d1f6 			; <UNDEFINED> instruction: 0xf8d8d1f6
d001dc90:	b3e33000 	mvnlt	r3, #0
d001dc94:	7185f44f 	orrvc	pc, r5, pc, asr #8
d001dc98:	f7f54620 			; <UNDEFINED> instruction: 0xf7f54620
d001dc9c:	b308f935 	movwlt	pc, #35125	; 0x8935	; <UNPREDICTABLE>
d001dca0:	061cf8df 			; <UNDEFINED> instruction: 0x061cf8df
d001dca4:	f7f64478 			; <UNDEFINED> instruction: 0xf7f64478
d001dca8:	b930fe39 	ldmdblt	r0!, {r0, r3, r4, r5, r9, sl, fp, ip, sp, lr, pc}
d001dcac:	1614f8df 			; <UNDEFINED> instruction: 0x1614f8df
d001dcb0:	0614f8df 			; <UNDEFINED> instruction: 0x0614f8df
d001dcb4:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d001dcb8:	f8dfe59b 			; <UNDEFINED> instruction: 0xf8dfe59b
d001dcbc:	212a2610 			; <UNDEFINED> instruction: 0x212a2610
d001dcc0:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d001dcc4:	f92ef7f5 			; <UNDEFINED> instruction: 0xf92ef7f5
d001dcc8:	d0ef2800 	rscle	r2, pc, r0, lsl #16
d001dccc:	338ff504 	orrcc	pc, pc, #4, 10	; 0x1000000
d001dcd0:	31b4f8b3 			; <UNDEFINED> instruction: 0x31b4f8b3
d001dcd4:	f8dfb923 			; <UNDEFINED> instruction: 0xf8dfb923
d001dcd8:	462015f8 			; <UNDEFINED> instruction: 0x462015f8
d001dcdc:	e5884479 	str	r4, [r8, #1145]	; 0x479
d001dce0:	e7bb2306 	ldr	r2, [fp, r6, lsl #6]!
d001dce4:	3000f8d8 	ldrdcc	pc, [r0], -r8
d001dce8:	f44fb18b 	vst4.32	{d27,d29,d31,d33}, [pc], fp
d001dcec:	46207184 	strtmi	r7, [r0], -r4, lsl #3
d001dcf0:	f90af7f5 			; <UNDEFINED> instruction: 0xf90af7f5
d001dcf4:	f8dfb158 			; <UNDEFINED> instruction: 0xf8dfb158
d001dcf8:	212a25dc 	ldrdcs	r2, [sl, -ip]!
d001dcfc:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d001dd00:	f910f7f5 			; <UNDEFINED> instruction: 0xf910f7f5
d001dd04:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001dd08:	2302a9d5 	movwcs	sl, #10709	; 0x29d5
d001dd0c:	f8dfe7a6 			; <UNDEFINED> instruction: 0xf8dfe7a6
d001dd10:	f8df15c8 			; <UNDEFINED> instruction: 0xf8df15c8
d001dd14:	447905c8 	ldrbtmi	r0, [r9], #-1480	; 0xfffffa38
d001dd18:	e56a4478 	strb	r4, [sl, #-1144]!	; 0xfffffb88
d001dd1c:	07189b15 			; <UNDEFINED> instruction: 0x07189b15
d001dd20:	9b12d502 	blls	0xd04d3130
d001dd24:	d14b2b00 	cmple	fp, r0, lsl #22
d001dd28:	75b4f8df 	ldrvc	pc, [r4, #2271]!	; 0x8df
d001dd2c:	447f2400 	ldrbtmi	r2, [pc], #-1024	; 0xd001dd34
d001dd30:	357ff507 	ldrbcc	pc, [pc, #-1287]!	; 0xd001d831	; <UNPREDICTABLE>
d001dd34:	2886f507 	stmcs	r6, {r0, r1, r2, r8, sl, ip, sp, lr, pc}
d001dd38:	750af505 	strvc	pc, [sl, #-1285]	; 0xfffffafb
d001dd3c:	3628f8d8 			; <UNDEFINED> instruction: 0x3628f8d8
d001dd40:	d21a429c 	andsle	r4, sl, #156, 4	; 0xc0000009
d001dd44:	465a2338 			; <UNDEFINED> instruction: 0x465a2338
d001dd48:	f604fb03 			; <UNDEFINED> instruction: 0xf604fb03
d001dd4c:	e9d5464b 	ldmib	r5, {r0, r1, r3, r6, r9, sl, lr}^
d001dd50:	f7f20100 			; <UNDEFINED> instruction: 0xf7f20100
d001dd54:	2800fcc7 	stmdacs	r0, {r0, r1, r2, r6, r7, sl, fp, ip, sp, lr, pc}
d001dd58:	f895d03e 			; <UNDEFINED> instruction: 0xf895d03e
d001dd5c:	f89d2028 			; <UNDEFINED> instruction: 0xf89d2028
d001dd60:	429a3050 	addsmi	r3, sl, #80	; 0x50
d001dd64:	9b14d138 	blls	0xd055224c
d001dd68:	f895b123 			; <UNDEFINED> instruction: 0xf895b123
d001dd6c:	7a3b2029 	bvc	0xd0ee5e18
d001dd70:	d131429a 	teqle	r1, sl	; <illegal shifter operand>
d001dd74:	f2802c00 	vmull.s8	q1, d0, d0
d001dd78:	f8df8261 			; <UNDEFINED> instruction: 0xf8df8261
d001dd7c:	464a4568 	strbmi	r4, [sl], -r8, ror #10
d001dd80:	447c4659 	ldrbtmi	r4, [ip], #-1625	; 0xfffff9a7
d001dd84:	f7f24620 			; <UNDEFINED> instruction: 0xf7f24620
d001dd88:	2800fdac 	stmdacs	r0, {r2, r3, r5, r7, r8, sl, fp, ip, sp, lr, pc}
d001dd8c:	8272f2c0 	rsbshi	pc, r2, #192, 4
d001dd90:	4659464a 	ldrbmi	r4, [r9], -sl, asr #12
d001dd94:	f7f24620 			; <UNDEFINED> instruction: 0xf7f24620
d001dd98:	2338fda4 	teqcs	r8, #164, 26	; 0x2900	; <UNPREDICTABLE>
d001dd9c:	4000fb03 	andmi	pc, r0, r3, lsl #22
d001dda0:	f5007a23 			; <UNDEFINED> instruction: 0xf5007a23
d001dda4:	f890307f 			; <UNDEFINED> instruction: 0xf890307f
d001dda8:	429a2251 	addsmi	r2, sl, #268435461	; 0x10000005
d001ddac:	8262f040 	rsbhi	pc, r2, #64	; 0x40
d001ddb0:	2b006da3 	blcs	0xd0039444
d001ddb4:	a97ef47f 	ldmdbge	lr!, {r0, r1, r2, r3, r4, r5, r6, sl, ip, sp, lr, pc}^
d001ddb8:	352cf8df 	strcc	pc, [ip, #-2271]!	; 0xfffff721
d001ddbc:	e5d0447b 	ldrb	r4, [r0, #1147]	; 0x47b
d001ddc0:	3528f8df 	strcc	pc, [r8, #-2271]!	; 0xfffff721
d001ddc4:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d001ddc8:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d001ddcc:	f8dfa973 			; <UNDEFINED> instruction: 0xf8dfa973
d001ddd0:	447a2520 	ldrbtmi	r2, [sl], #-1312	; 0xfffffae0
d001ddd4:	bb42f7ff 	bllt	0xd10dbdd8
d001ddd8:	35383401 	ldrcc	r3, [r8, #-1025]!	; 0xfffffbff
d001dddc:	1c62e7ae 	stclne	7, cr14, [r2], #-696	; 0xfffffd48
d001dde0:	f8952100 			; <UNDEFINED> instruction: 0xf8952100
d001dde4:	f8c38008 			; <UNDEFINED> instruction: 0xf8c38008
d001dde8:	22382628 	eorscs	r2, r8, #40, 12	; 0x2800000
d001ddec:	f704fb02 			; <UNDEFINED> instruction: 0xf704fb02
d001ddf0:	f50719ee 			; <UNDEFINED> instruction: 0xf50719ee
d001ddf4:	f506377f 			; <UNDEFINED> instruction: 0xf506377f
d001ddf8:	f506367f 			; <UNDEFINED> instruction: 0xf506367f
d001ddfc:	4618730a 	ldrmi	r7, [r8], -sl, lsl #6
d001de00:	fc06f003 	stc2	0, cr15, [r6], {3}
d001de04:	f10d9a10 			; <UNDEFINED> instruction: 0xf10d9a10
d001de08:	f88d0e98 			; <UNDEFINED> instruction: 0xf88d0e98
d001de0c:	9229a0b0 	eorls	sl, r9, #176	; 0xb0
d001de10:	9a0f4684 	bls	0xd03ef828
d001de14:	9a11922a 	bls	0xd04826c4
d001de18:	b926e9cd 	stmdblt	r6!, {r0, r2, r3, r6, r7, r8, fp, sp, lr, pc}
d001de1c:	e8be922d 	ldm	lr!, {r0, r2, r3, r5, r9, ip, pc}
d001de20:	e8ac000f 	stmia	ip!, {r0, r1, r2, r3}
d001de24:	e89e000f 	ldm	lr, {r0, r1, r2, r3}
d001de28:	e88c000f 	stm	ip, {r0, r1, r2, r3}
d001de2c:	9b15000f 	blls	0xd055de70
d001de30:	2053f207 	subscs	pc, r3, r7, lsl #4
d001de34:	7716f507 	ldrvc	pc, [r6, -r7, lsl #10]
d001de38:	f8c6a91a 			; <UNDEFINED> instruction: 0xf8c6a91a
d001de3c:	44283248 	strtmi	r3, [r8], #-584	; 0xfffffdb8
d001de40:	f8869b12 			; <UNDEFINED> instruction: 0xf8869b12
d001de44:	9b15324c 	blls	0xd056a77c
d001de48:	324df886 	subcc	pc, sp, #8781824	; 0x860000
d001de4c:	bf183b00 	svclt	0x00183b00
d001de50:	f8862301 			; <UNDEFINED> instruction: 0xf8862301
d001de54:	9b13324e 	blls	0xd04ea794
d001de58:	f8869a12 			; <UNDEFINED> instruction: 0xf8869a12
d001de5c:	9b14324f 	blls	0xd052a7a0
d001de60:	8251f886 	subshi	pc, r1, #8781824	; 0x860000
d001de64:	3250f886 	subscc	pc, r0, #8781824	; 0x860000
d001de68:	f8869b16 			; <UNDEFINED> instruction: 0xf8869b16
d001de6c:	f0033252 			; <UNDEFINED> instruction: 0xf0033252
d001de70:	9a12fbdd 	bls	0xd04dcdec
d001de74:	19e8a91c 	stmibne	r8!, {r2, r3, r4, r8, fp, sp, pc}^
d001de78:	fbd8f003 	blx	0xcf659e8e
d001de7c:	5474f8df 	ldrbtpl	pc, [r4], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d001de80:	447d213b 	ldrbtmi	r2, [sp], #-315	; 0xfffffec5
d001de84:	f7f54628 			; <UNDEFINED> instruction: 0xf7f54628
d001de88:	2800f83f 	stmdacs	r0, {r0, r1, r2, r3, r4, r5, fp, ip, sp, lr, pc}
d001de8c:	a912f47f 	ldmdbge	r2, {r0, r1, r2, r3, r4, r5, r6, sl, ip, sp, lr, pc}
d001de90:	fb032338 	blx	0xd00e6b7a
d001de94:	f5045404 			; <UNDEFINED> instruction: 0xf5045404
d001de98:	f894347f 			; <UNDEFINED> instruction: 0xf894347f
d001de9c:	b326624e 			; <UNDEFINED> instruction: 0xb326624e
d001dea0:	2b006dab 	blcs	0xd0039554
d001dea4:	a906f47f 	stmdbge	r6, {r0, r1, r2, r3, r4, r5, r6, sl, ip, sp, lr, pc}
d001dea8:	344cf8df 	strbcc	pc, [ip], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d001deac:	f7ff447b 			; <UNDEFINED> instruction: 0xf7ff447b
d001deb0:	f893bac0 			; <UNDEFINED> instruction: 0xf893bac0
d001deb4:	9a163252 	bls	0xd05aa804
d001deb8:	f0404293 			; <UNDEFINED> instruction: 0xf0404293
d001debc:	f50681d1 			; <UNDEFINED> instruction: 0xf50681d1
d001dec0:	9a12367f 	bls	0xd04ab8c4
d001dec4:	f206a91a 	vmul.i8	d10, d6, d10
d001dec8:	44282053 	strtmi	r2, [r8], #-83	; 0xffffffad
d001decc:	fbbef003 	blx	0xcefd9ee2
d001ded0:	f0402800 			; <UNDEFINED> instruction: 0xf0402800
d001ded4:	f50681c5 			; <UNDEFINED> instruction: 0xf50681c5
d001ded8:	9a127616 	bls	0xd04bb738
d001dedc:	19a8a91c 	stmibne	r8!, {r2, r3, r4, r8, fp, sp, pc}
d001dee0:	fbb4f003 	blx	0xced59ef6
d001dee4:	d0c92800 	sbcle	r2, r9, r0, lsl #16
d001dee8:	f8dfe1ba 			; <UNDEFINED> instruction: 0xf8dfe1ba
d001deec:	217b2410 	cmncs	fp, r0, lsl r4
d001def0:	447a4628 	ldrbtmi	r4, [sl], #-1576	; 0xfffff9d8
d001def4:	f816f7f5 			; <UNDEFINED> instruction: 0xf816f7f5
d001def8:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001defc:	f505a8db 			; <UNDEFINED> instruction: 0xf505a8db
d001df00:	f505398f 			; <UNDEFINED> instruction: 0xf505398f
d001df04:	f04f2790 			; <UNDEFINED> instruction: 0xf04f2790
d001df08:	f24b0801 	vadd.i8	d16, d11, d1
d001df0c:	f8d95180 			; <UNDEFINED> instruction: 0xf8d95180
d001df10:	462831b8 			; <UNDEFINED> instruction: 0x462831b8
d001df14:	824ef884 	subhi	pc, lr, #132, 16	; 0x840000
d001df18:	3248f8c4 	subcc	pc, r8, #196, 16	; 0xc40000
d001df1c:	2392f505 	orrscs	pc, r2, #20971520	; 0x1400000
d001df20:	6630f8c7 	ldrtvs	pc, [r0], -r7, asr #17	; <UNPREDICTABLE>
d001df24:	6240f8c3 	subvs	pc, r0, #12779520	; 0xc30000
d001df28:	6250f8c3 	subsvs	pc, r0, #12779520	; 0xc30000
d001df2c:	624cf8c3 	subvs	pc, ip, #12779520	; 0xc30000
d001df30:	6636f887 	ldrtvs	pc, [r6], -r7, lsl #17	; <UNPREDICTABLE>
d001df34:	668ee9c3 	strvs	lr, [lr], r3, asr #19
d001df38:	2396f505 	orrscs	pc, r6, #20971520	; 0x1400000
d001df3c:	629cf8c3 	addsvs	pc, ip, #12779520	; 0xc30000
d001df40:	2394f505 	orrscs	pc, r4, #20971520	; 0x1400000
d001df44:	6298f8c3 	addsvs	pc, r8, #12779520	; 0xc30000
d001df48:	6254f8c3 	subsvs	pc, r4, #12779520	; 0xc30000
d001df4c:	324ff894 	subcc	pc, pc, #148, 16	; 0x940000
d001df50:	3634f887 	ldrtcc	pc, [r4], -r7, lsl #17	; <UNPREDICTABLE>
d001df54:	3252f894 	subscc	pc, r2, #148, 16	; 0x940000
d001df58:	f887ac2e 			; <UNDEFINED> instruction: 0xf887ac2e
d001df5c:	f7f63635 			; <UNDEFINED> instruction: 0xf7f63635
d001df60:	f8d9fdd9 			; <UNDEFINED> instruction: 0xf8d9fdd9
d001df64:	463131b8 			; <UNDEFINED> instruction: 0x463131b8
d001df68:	93114628 	tstls	r1, #40, 12	; 0x2800000
d001df6c:	fdd2f7f6 	ldc2l	7, cr15, [r2, #984]	; 0x3d8
d001df70:	412ff44f 	msrmi	CPSR_fsxc, pc, asr #8
d001df74:	f7f64628 			; <UNDEFINED> instruction: 0xf7f64628
d001df78:	9b13fdcd 	blls	0xd051d6b4
d001df7c:	d1522b04 	cmple	r2, r4, lsl #22
d001df80:	46312218 			; <UNDEFINED> instruction: 0x46312218
d001df84:	f003a830 			; <UNDEFINED> instruction: 0xf003a830
d001df88:	4bddfb43 	blmi	0xcf79cc9c
d001df8c:	932e447b 			; <UNDEFINED> instruction: 0x932e447b
d001df90:	932f2314 			; <UNDEFINED> instruction: 0x932f2314
d001df94:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d001df98:	230b9333 	movwcs	r9, #45875	; 0xb333
d001df9c:	ab329304 	blge	0xd0cc2bb4
d001dfa0:	e88dcb0f 	stm	sp, {r0, r1, r2, r3, r8, r9, fp, lr, pc}
d001dfa4:	e894000f 	ldm	r4, {r0, r1, r2, r3}
d001dfa8:	f7f6000f 			; <UNDEFINED> instruction: 0xf7f6000f
d001dfac:	4632f83b 			; <UNDEFINED> instruction: 0x4632f83b
d001dfb0:	f887b2c1 			; <UNDEFINED> instruction: 0xf887b2c1
d001dfb4:	46280636 			; <UNDEFINED> instruction: 0x46280636
d001dfb8:	fde5f7f6 	stc2l	7, cr15, [r5, #984]!	; 0x3d8
d001dfbc:	804cf8cd 	subhi	pc, ip, sp, asr #17
d001dfc0:	22144620 	andscs	r4, r4, #32, 12	; 0x2000000
d001dfc4:	24002100 	strcs	r2, [r0], #-256	; 0xffffff00
d001dfc8:	fb22f003 	blx	0xd08d9fde
d001dfcc:	f10dab1a 			; <UNDEFINED> instruction: 0xf10dab1a
d001dfd0:	f10d0a70 			; <UNDEFINED> instruction: 0xf10d0a70
d001dfd4:	461e0bd8 			; <UNDEFINED> instruction: 0x461e0bd8
d001dfd8:	4bca9310 	blmi	0xcf2c2c20
d001dfdc:	447b940f 	ldrbtmi	r9, [fp], #-1039	; 0xfffffbf1
d001dfe0:	4bc99316 	blmi	0xcf282c40
d001dfe4:	f503447b 			; <UNDEFINED> instruction: 0xf503447b
d001dfe8:	93172392 	tstls	r7, #1207959554	; 0x48000002
d001dfec:	42a39b12 	adcmi	r9, r3, #18432	; 0x4800
d001dff0:	4ec6d11b 	mcrmi	1, 6, sp, cr6, cr11, {0}
d001dff4:	4dc62400 	cfstrdmi	mvd2, [r6]
d001dff8:	447d447e 	ldrbtmi	r4, [sp], #-1150	; 0xfffffb82
d001dffc:	42a39b12 	adcmi	r9, r3, #18432	; 0x4800
d001e000:	80d5f040 	sbcshi	pc, r5, r0, asr #32
d001e004:	447b4bc3 	ldrbtmi	r4, [fp], #-3011	; 0xfffff43d
d001e008:	2b00681b 	blcs	0xd003807c
d001e00c:	8101f000 	mrshi	pc, (UNDEF: 1)	; <UNPREDICTABLE>
d001e010:	f8c39a11 			; <UNDEFINED> instruction: 0xf8c39a11
d001e014:	9a0f210c 	bls	0xd03e644c
d001e018:	2110f8c3 	tstcs	r0, r3, asr #17	; <UNPREDICTABLE>
d001e01c:	f8c32201 			; <UNDEFINED> instruction: 0xf8c32201
d001e020:	f7ff2128 			; <UNDEFINED> instruction: 0xf7ff2128
d001e024:	9613b847 	ldrls	fp, [r3], -r7, asr #16
d001e028:	f8dbe7ca 			; <UNDEFINED> instruction: 0xf8dbe7ca
d001e02c:	f2402014 	vqadd.s8	d18, d0, d4
d001e030:	429a1301 	addsmi	r1, sl, #67108864	; 0x4000000
d001e034:	4bb8d014 	blmi	0xcee5208c
d001e038:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d001e03c:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d001e040:	aa36a839 	bge	0xd0dc812c
d001e044:	1444eb02 	strbne	lr, [r4], #-2818	; 0xfffff4fe
d001e048:	692068e5 	stmdbvs	r0!, {r0, r2, r5, r6, r7, fp, sp, lr}
d001e04c:	7e2169e2 	vnmulvc.f16	s12, s3, s5	; <UNPREDICTABLE>
d001e050:	447c4cb2 	ldrbtmi	r4, [ip], #-3250	; 0xfffff34e
d001e054:	4516e9c3 	ldrmi	lr, [r6, #-2499]	; 0xfffff63d
d001e058:	0118e9c3 	tsteq	r8, r3, asr #19
d001e05c:	ba05f7ff 	blt	0xd019c060
d001e060:	96157832 			; <UNDEFINED> instruction: 0x96157832
d001e064:	d11d2a0d 	tstle	sp, sp, lsl #20
d001e068:	3000f89a 	mulcc	r0, sl, r8
d001e06c:	711af44f 	tstvc	sl, pc, asr #8	; <UNPREDICTABLE>
d001e070:	fb019816 	blx	0xd00840d2
d001e074:	f5030303 			; <UNDEFINED> instruction: 0xf5030303
d001e078:	f8b33368 			; <UNDEFINED> instruction: 0xf8b33368
d001e07c:	f1b99028 			; <UNDEFINED> instruction: 0xf1b99028
d001e080:	d1110f00 	tstle	r1, r0, lsl #30
d001e084:	447b4ba6 	ldrbtmi	r4, [fp], #-2982	; 0xfffff45a
d001e088:	2a006d9a 	bcs	0xd00396f8
d001e08c:	a812f47f 	ldmdage	r2, {r0, r1, r2, r3, r4, r5, r6, sl, ip, sp, lr, pc}
d001e090:	eb02aa36 	bl	0xd00c8970
d001e094:	68e51444 	stmiavs	r5!, {r2, r6, sl, ip}^
d001e098:	69e26920 	stmibvs	r2!, {r5, r8, fp, sp, lr}^
d001e09c:	4ca17e21 	stcmi	14, cr7, [r1], #132	; 0x84
d001e0a0:	e7d7447c 			; <UNDEFINED> instruction: 0xe7d7447c
d001e0a4:	0901f04f 	stmdbeq	r1, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d001e0a8:	f8d39b17 			; <UNDEFINED> instruction: 0xf8d39b17
d001e0ac:	f1c33238 			; <UNDEFINED> instruction: 0xf1c33238
d001e0b0:	454b0340 	strbmi	r0, [fp, #-832]	; 0xfffffcc0
d001e0b4:	ab5ed3e6 	blge	0xd17d3054
d001e0b8:	eb039204 	bl	0xd01028d0
d001e0bc:	f1a31344 			; <UNDEFINED> instruction: 0xf1a31344
d001e0c0:	3b9005a0 	blcc	0xce41f748
d001e0c4:	e88dcb0f 	stm	sp, {r0, r1, r2, r3, r8, r9, fp, lr, pc}
d001e0c8:	e895000f 	ldm	r5, {r0, r1, r2, r3}
d001e0cc:	f7f5000f 			; <UNDEFINED> instruction: 0xf7f5000f
d001e0d0:	ab2effa9 	blge	0xd0bddf7c
d001e0d4:	f8434607 			; <UNDEFINED> instruction: 0xf8434607
d001e0d8:	78330024 	ldmdavc	r3!, {r2, r5}
d001e0dc:	020df1a3 	andeq	pc, sp, #-1073741784	; 0xc0000028
d001e0e0:	d9012a01 	stmdble	r1, {r0, r9, fp, sp}
d001e0e4:	d10a2b12 	tstle	sl, r2, lsl fp
d001e0e8:	22304b8f 	eorscs	r4, r0, #146432	; 0x23c00
d001e0ec:	fb02447b 	blx	0xd00af2e2
d001e0f0:	f89a3307 			; <UNDEFINED> instruction: 0xf89a3307
d001e0f4:	f5032000 			; <UNDEFINED> instruction: 0xf5032000
d001e0f8:	f8832390 			; <UNDEFINED> instruction: 0xf8832390
d001e0fc:	4a8b265a 	bmi	0xce2e7a6c
d001e100:	447a2301 	ldrbtmi	r2, [sl], #-769	; 0xfffffcff
d001e104:	2892f502 	ldmcs	r2, {r1, r8, sl, ip, sp, lr, pc}
d001e108:	45999214 	ldrmi	r9, [r9, #532]	; 0x214
d001e10c:	5238f8d8 	eorspl	pc, r8, #216, 16	; 0xd80000
d001e110:	f8d8d138 			; <UNDEFINED> instruction: 0xf8d8d138
d001e114:	42ab323c 	adcmi	r3, fp, #60, 4	; 0xc0000003
d001e118:	bf389b13 	svclt	0x00389b13
d001e11c:	523cf8c8 	eorspl	pc, ip, #200, 16	; 0xc80000
d001e120:	eb042c04 	bl	0xd0129138
d001e124:	d1100503 	tstle	r0, r3, lsl #10
d001e128:	f64f4881 			; <UNDEFINED> instruction: 0xf64f4881
d001e12c:	250001d7 	strcs	r0, [r0, #-471]	; 0xfffffe29
d001e130:	900f4478 	andls	r4, pc, r8, ror r4	; <UNPREDICTABLE>
d001e134:	fceef7f6 	stc2l	7, cr15, [lr], #984	; 0x3d8
d001e138:	2100980f 	tstcs	r0, pc, lsl #16
d001e13c:	338ff500 	orrcc	pc, pc, #0, 10
d001e140:	31b8f8d3 			; <UNDEFINED> instruction: 0x31b8f8d3
d001e144:	f7f6930f 			; <UNDEFINED> instruction: 0xf7f6930f
d001e148:	9b15fce5 	blls	0xd059d4e4
d001e14c:	781b3601 	ldmdavc	fp, {r0, r9, sl, ip, sp}
d001e150:	d10b2b05 	tstle	fp, r5, lsl #22
d001e154:	4877b2a9 	ldmdami	r7!, {r0, r3, r5, r7, r9, ip, sp, pc}^
d001e158:	01c1ea41 	biceq	lr, r1, r1, asr #20
d001e15c:	f4414478 	vst3.16	{d20-d22}, [r1 :256], r8
d001e160:	f0414132 			; <UNDEFINED> instruction: 0xf0414132
d001e164:	b28901c0 	addlt	r0, r9, #192, 2	; 0x30
d001e168:	fcd4f7f6 	ldc2l	7, cr15, [r4], {246}	; 0xf6
d001e16c:	462a4872 			; <UNDEFINED> instruction: 0x462a4872
d001e170:	34014639 	strcc	r4, [r1], #-1593	; 0xfffff9c7
d001e174:	f10a4478 			; <UNDEFINED> instruction: 0xf10a4478
d001e178:	f10b0a01 			; <UNDEFINED> instruction: 0xf10b0a01
d001e17c:	f7f60b20 			; <UNDEFINED> instruction: 0xf7f60b20
d001e180:	e733fd02 	ldr	pc, [r3, -r2, lsl #26]!
d001e184:	93181c6a 	tstls	r8, #27136	; 0x6a00
d001e188:	21009b14 	tstcs	r0, r4, lsl fp
d001e18c:	2238f8c8 	eorscs	pc, r8, #200, 16	; 0xc80000
d001e190:	fb022230 	blx	0xd00a6a5a
d001e194:	f5053505 			; <UNDEFINED> instruction: 0xf5053505
d001e198:	f5052590 			; <UNDEFINED> instruction: 0xf5052590
d001e19c:	f00360c7 			; <UNDEFINED> instruction: 0xf00360c7
d001e1a0:	220bfa37 	andcs	pc, fp, #225280	; 0x37000
d001e1a4:	f8859b18 			; <UNDEFINED> instruction: 0xf8859b18
d001e1a8:	33012659 	movwcc	r2, #5721	; 0x1659
d001e1ac:	9a10e7ad 	bls	0xd0458068
d001e1b0:	3b01f812 	blcc	0xd009c200
d001e1b4:	92102b0d 	andsls	r2, r0, #13312	; 0x3400
d001e1b8:	3401d001 	strcc	sp, [r1], #-1
d001e1bc:	ab2ee71e 	blge	0xd0bd7e3c
d001e1c0:	721af44f 	andsvc	pc, sl, #1325400064	; 0x4f000000
d001e1c4:	0900f04f 	stmdbeq	r0, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d001e1c8:	f8534630 			; <UNDEFINED> instruction: 0xf8534630
d001e1cc:	ab1c7024 	blge	0xd073a264
d001e1d0:	46395ce3 	ldrtmi	r5, [r9], -r3, ror #25
d001e1d4:	6303fb02 	movwvs	pc, #15106	; 0x3b02	; <UNPREDICTABLE>
d001e1d8:	f5032201 			; <UNDEFINED> instruction: 0xf5032201
d001e1dc:	f8b33368 			; <UNDEFINED> instruction: 0xf8b33368
d001e1e0:	f7f68028 			; <UNDEFINED> instruction: 0xf7f68028
d001e1e4:	45c8fcb5 	strbmi	pc, [r8, #3253]	; 0xcb5	; <UNPREDICTABLE>
d001e1e8:	f64fd9e7 			; <UNDEFINED> instruction: 0xf64fd9e7
d001e1ec:	462801d1 			; <UNDEFINED> instruction: 0x462801d1
d001e1f0:	fc90f7f6 	ldc2	7, cr15, [r0], {246}	; 0xf6
d001e1f4:	ea4f4628 	b	0xd13efa9c
d001e1f8:	b2890189 	addlt	r0, r9, #1073741858	; 0x40000022
d001e1fc:	fc8af7f6 	stc2	7, cr15, [sl], {246}	; 0xf6
d001e200:	0109eb07 	tsteq	r9, r7, lsl #22
d001e204:	46282200 	strtmi	r2, [r8], -r0, lsl #4
d001e208:	0901f109 	stmdbeq	r1, {r0, r3, r8, ip, sp, lr, pc}
d001e20c:	fcbbf7f6 	ldc2	7, cr15, [fp], #984	; 0x3d8
d001e210:	f7fce7e9 			; <UNDEFINED> instruction: 0xf7fce7e9
d001e214:	990ffe15 	stmdbls	pc, {r0, r2, r4, r9, sl, fp, ip, sp, lr, pc}	; <UNPREDICTABLE>
d001e218:	f7fb9811 			; <UNDEFINED> instruction: 0xf7fb9811
d001e21c:	f7fefda3 			; <UNDEFINED> instruction: 0xf7fefda3
d001e220:	2c00bf49 	stccs	15, cr11, [r0], {73}	; 0x49
d001e224:	ab09f43f 	blge	0xd029b328
d001e228:	447b4b44 	ldrbtmi	r4, [fp], #-2884	; 0xfffff4bc
d001e22c:	2a006d9a 	bcs	0xd003989c
d001e230:	af40f47e 	svcge	0x0040f47e
d001e234:	447a4a42 	ldrbtmi	r4, [sl], #-2626	; 0xfffff5be
d001e238:	b910f7ff 	ldmdblt	r0, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}
d001e23c:	23384d41 	teqcs	r8, #4160	; 0x1040
d001e240:	447d9912 	ldrbtmi	r9, [sp], #-2322	; 0xfffff6ee
d001e244:	5304fb03 	movwpl	pc, #19203	; 0x4b03	; <UNPREDICTABLE>
d001e248:	337ff503 	cmncc	pc, #12582912	; 0xc00000	; <UNPREDICTABLE>
d001e24c:	224cf893 	subcs	pc, ip, #9633792	; 0x930000
d001e250:	d1054291 			; <UNDEFINED> instruction: 0xd1054291
d001e254:	224ff893 	subcs	pc, pc, #9633792	; 0x930000
d001e258:	428a9913 	addmi	r9, sl, #311296	; 0x4c000
d001e25c:	ae29f43f 	mcrge	4, 1, pc, cr9, cr15, {1}	; <UNPREDICTABLE>
d001e260:	447b4b39 	ldrbtmi	r4, [fp], #-2873	; 0xfffff4c7
d001e264:	2a006d9a 	bcs	0xd00398d4
d001e268:	af24f47e 	svcge	0x0024f47e
d001e26c:	447a4a37 	ldrbtmi	r4, [sl], #-2615	; 0xfffff5c9
d001e270:	b8f4f7ff 	ldmlt	r4!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}^
d001e274:	447d4d36 	ldrbtmi	r4, [sp], #-3382	; 0xfffff2ca
d001e278:	2386f505 	orrcs	pc, r6, #20971520	; 0x1400000
d001e27c:	4628f8d3 			; <UNDEFINED> instruction: 0x4628f8d3
d001e280:	7f80f5b4 	svcvc	0x0080f5b4
d001e284:	adabf47f 	cfstrsge	mvf15, [fp, #508]!	; 0x1fc
d001e288:	2b006dab 	blcs	0xd003993c
d001e28c:	af12f47e 	svcge	0x0012f47e
d001e290:	447b4b30 	ldrbtmi	r4, [fp], #-2864	; 0xfffff4d0
d001e294:	b8cdf7ff 	stmialt	sp, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}^
d001e298:	2b009b13 	blcs	0xd0044eec
d001e29c:	aac4f47f 	bge	0xcf15b4a0
d001e2a0:	f43f2d00 			; <UNDEFINED> instruction: 0xf43f2d00
d001e2a4:	e7bfaaba 			; <UNDEFINED> instruction: 0xe7bfaaba
d001e2a8:	0000a5ea 	andeq	sl, r0, sl, ror #11
d001e2ac:	0000a594 	muleq	r0, r4, r5
d001e2b0:	ffff5c20 			; <UNDEFINED> instruction: 0xffff5c20
d001e2b4:	ffffc88c 			; <UNDEFINED> instruction: 0xffffc88c
d001e2b8:	ffffc885 			; <UNDEFINED> instruction: 0xffffc885
d001e2bc:	ffff5be6 			; <UNDEFINED> instruction: 0xffff5be6
d001e2c0:	ffffef52 			; <UNDEFINED> instruction: 0xffffef52
d001e2c4:	ffffef4e 			; <UNDEFINED> instruction: 0xffffef4e
d001e2c8:	0000a50e 	andeq	sl, r0, lr, lsl #10
d001e2cc:	ffffef67 			; <UNDEFINED> instruction: 0xffffef67
d001e2d0:	ffffef72 			; <UNDEFINED> instruction: 0xffffef72
d001e2d4:	ffffef7b 			; <UNDEFINED> instruction: 0xffffef7b
d001e2d8:	ffffef85 			; <UNDEFINED> instruction: 0xffffef85
d001e2dc:	0000a4ac 	andeq	sl, r0, ip, lsr #9
d001e2e0:	0000a496 	muleq	r0, r6, r4
d001e2e4:	0000a442 	andeq	sl, r0, r2, asr #8
d001e2e8:	ffffef8a 			; <UNDEFINED> instruction: 0xffffef8a
d001e2ec:	0000a400 	andeq	sl, r0, r0, lsl #8
d001e2f0:	ffffef51 			; <UNDEFINED> instruction: 0xffffef51
d001e2f4:	0000a342 	andeq	sl, r0, r2, asr #6
d001e2f8:	ffffef0f 			; <UNDEFINED> instruction: 0xffffef0f
d001e2fc:	ffffeee2 			; <UNDEFINED> instruction: 0xffffeee2
d001e300:	ffffee68 			; <UNDEFINED> instruction: 0xffffee68
d001e304:	0000a1e6 	andeq	sl, r0, r6, ror #3
d001e308:	0000a1e0 	andeq	sl, r0, r0, ror #3
d001e30c:	0000a1cc 	andeq	sl, r0, ip, asr #3
d001e310:	0000a1ca 	andeq	sl, r0, sl, asr #3
d001e314:	0000520e 	andeq	r5, r0, lr, lsl #4
d001e318:	0000a18c 	andeq	sl, r0, ip, lsl #3
d001e31c:	ffffedb7 			; <UNDEFINED> instruction: 0xffffedb7
d001e320:	0000a13e 	andeq	sl, r0, lr, lsr r1
d001e324:	ffffed95 			; <UNDEFINED> instruction: 0xffffed95
d001e328:	0000a0d8 	ldrdeq	sl, [r0], -r8
d001e32c:	0000a0c2 	andeq	sl, r0, r2, asr #1
d001e330:	0000a094 	muleq	r0, r4, r0
d001e334:	0000a068 	andeq	sl, r0, r8, rrx
d001e338:	0000a050 	andeq	sl, r0, r0, asr r0
d001e33c:	00009f9a 	muleq	r0, sl, pc	; <UNPREDICTABLE>
d001e340:	ffffe888 			; <UNDEFINED> instruction: 0xffffe888
d001e344:	00009f82 	andeq	r9, r0, r2, lsl #31
d001e348:	00009f62 	andeq	r9, r0, r2, ror #30
d001e34c:	ffffeb1d 			; <UNDEFINED> instruction: 0xffffeb1d
d001e350:	00009f4e 	andeq	r9, r0, lr, asr #30
d001e354:	ffffeae6 			; <UNDEFINED> instruction: 0xffffeae6

Disassembly of section .text.sidc_set_progress_callback:

d001e490 <.text.sidc_set_progress_callback>:
d001e490:	447b4b03 	ldrbtmi	r4, [fp], #-2819	; 0xfffff4fd
d001e494:	4b036018 	blmi	0xd00f64fc
d001e498:	6019447b 	andsvs	r4, r9, fp, ror r4
d001e49c:	bf004770 	svclt	0x00004770
d001e4a0:	0005510a 	andeq	r5, r5, sl, lsl #2
d001e4a4:	00055108 	andeq	r5, r5, r8, lsl #2

Disassembly of section .text.sidc_job_begin:

d001e4a8 <.text.sidc_job_begin>:
d001e4a8:	4ff7e92d 	svcmi	0x00f7e92d
d001e4ac:	46809c0e 	strmi	r9, [r0], lr, lsl #24
d001e4b0:	46934689 	ldrmi	r4, [r3], r9, lsl #13
d001e4b4:	9f0d469a 	svcls	0x000d469a
d001e4b8:	2214b1dc 	andscs	fp, r4, #220, 2	; 0x37
d001e4bc:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d001e4c0:	f8a6f003 			; <UNDEFINED> instruction: 0xf8a6f003
d001e4c4:	447b4b59 	ldrbtmi	r4, [fp], #-2905	; 0xfffff4a7
d001e4c8:	b95d681d 	ldmdblt	sp, {r0, r2, r3, r4, fp, sp, lr}^
d001e4cc:	0f00f1b8 	svceq	0x0000f1b8
d001e4d0:	b13fd008 	teqlt	pc, r8
d001e4d4:	b12b687b 			; <UNDEFINED> instruction: 0xb12b687b
d001e4d8:	b11b68bb 			; <UNDEFINED> instruction: 0xb11b68bb
d001e4dc:	33fff10b 	mvnscc	pc, #-1073741822	; 0xc0000002
d001e4e0:	d90a2b0f 	stmdble	sl, {r0, r1, r2, r3, r8, r9, fp, sp}
d001e4e4:	447d4d52 	ldrbtmi	r4, [sp], #-3410	; 0xfffff2ae
d001e4e8:	cd0f3528 	cfstr32gt	mvfx3, [pc, #-160]	; 0xd001e450
d001e4ec:	682bc40f 	stmdavs	fp!, {r0, r1, r2, r3, sl, lr, pc}
d001e4f0:	20006023 	andcs	r6, r0, r3, lsr #32
d001e4f4:	e8bdb003 	pop	{r0, r1, ip, sp, pc}
d001e4f8:	462e8ff0 	qsub8mi	r8, lr, r0
d001e4fc:	0204f108 	andeq	pc, r4, #8, 2
d001e500:	3035f858 	eorscc	pc, r5, r8, asr r8	; <UNPREDICTABLE>
d001e504:	4b4bb95b 	blmi	0xd130ca78
d001e508:	60e52000 	rscvs	r2, r5, r0
d001e50c:	6120447b 			; <UNDEFINED> instruction: 0x6120447b
d001e510:	23016023 	movwcs	r6, #4131	; 0x1023
d001e514:	60a36063 	adcvs	r6, r3, r3, rrx
d001e518:	461de7ec 	ldrmi	lr, [sp], -ip, ror #15
d001e51c:	f852e7f0 			; <UNDEFINED> instruction: 0xf852e7f0
d001e520:	f5c63035 			; <UNDEFINED> instruction: 0xf5c63035
d001e524:	428b1180 	addmi	r1, fp, #128, 2
d001e528:	441ed8ed 	ldrmi	sp, [lr], #-2285	; 0xfffff713
d001e52c:	459b1c6b 	ldrmi	r1, [fp, #3179]	; 0xc6b
d001e530:	f8dfd1f3 			; <UNDEFINED> instruction: 0xf8dfd1f3
d001e534:	f44fb104 	vst4.8	{d27,d29,d31,d33}, [pc], r4
d001e538:	21007298 			; <UNDEFINED> instruction: 0x21007298
d001e53c:	44fb9301 	ldrbtmi	r9, [fp], #769	; 0x301
d001e540:	f0034658 			; <UNDEFINED> instruction: 0xf0034658
d001e544:	f10bf865 			; <UNDEFINED> instruction: 0xf10bf865
d001e548:	22000e80 	andcs	r0, r0, #128, 28	; 0x800
d001e54c:	eb089b01 	bl	0xd0245158
d001e550:	eb0b01c2 	bl	0xd02dec60
d001e554:	c9030cc2 	stmdbgt	r3, {r1, r6, r7, sl, fp}
d001e558:	0003e88c 	andeq	lr, r3, ip, lsl #17
d001e55c:	0f00f1b9 	svceq	0x0000f1b9
d001e560:	f859d05e 			; <UNDEFINED> instruction: 0xf859d05e
d001e564:	42aa1022 	adcmi	r1, sl, #34	; 0x22
d001e568:	1b04f84e 	blne	0xd015c6a8
d001e56c:	0101f102 	tsteq	r1, r2, lsl #2	; <UNPREDICTABLE>
d001e570:	f8dfd154 			; <UNDEFINED> instruction: 0xf8dfd154
d001e574:	f04f80c8 			; <UNDEFINED> instruction: 0xf04f80c8
d001e578:	4d310900 			; <UNDEFINED> instruction: 0x4d310900
d001e57c:	447d44f8 	ldrbtmi	r4, [sp], #-1272	; 0xfffffb08
d001e580:	30d8f8c8 	sbcscc	pc, r8, r8, asr #17
d001e584:	03c8f108 	biceq	pc, r8, #8, 2
d001e588:	60dcf8c8 	sbcsvs	pc, ip, r8, asr #17
d001e58c:	0007e897 	muleq	r7, r7, r8
d001e590:	0007e883 	andeq	lr, r7, r3, lsl #17
d001e594:	27019a0c 	strcs	r9, [r1, -ip, lsl #20]
d001e598:	46282100 	strtmi	r2, [r8], -r0, lsl #2
d001e59c:	20c4f8c8 	sbccs	pc, r4, r8, asr #17
d001e5a0:	f8c84a28 			; <UNDEFINED> instruction: 0xf8c84a28
d001e5a4:	447aa0c0 	ldrbtmi	sl, [sl], #-192	; 0xffffff40
d001e5a8:	40d4f8c8 	sbcsmi	pc, r4, r8, asr #17
d001e5ac:	7124f8c8 	smlawtvc	r4, r8, r8, pc	; <UNPREDICTABLE>
d001e5b0:	8000f8c2 	andhi	pc, r0, r2, asr #17
d001e5b4:	447a4a24 	ldrbtmi	r4, [sl], #-2596	; 0xfffff5dc
d001e5b8:	4a1b6013 	bmi	0xd06f660c
d001e5bc:	f828f003 			; <UNDEFINED> instruction: 0xf828f003
d001e5c0:	22059b0c 	andcs	r9, r5, #12, 22	; 0x3000
d001e5c4:	66eb4821 	strbtvs	r4, [fp], r1, lsr #16
d001e5c8:	33fff04f 	mvnscc	pc, #79	; 0x4f
d001e5cc:	44784649 	ldrbtmi	r4, [r8], #-1609	; 0xfffff9b7
d001e5d0:	4b1f67ab 	blmi	0xd07f8484
d001e5d4:	a070f8c5 	rsbsge	pc, r0, r5, asr #17
d001e5d8:	601e447b 	andsvs	r4, lr, fp, ror r4
d001e5dc:	447b4b1d 	ldrbtmi	r4, [fp], #-2845	; 0xfffff4e3
d001e5e0:	9000f8c3 	andls	pc, r0, r3, asr #17
d001e5e4:	447b4b1c 	ldrbtmi	r4, [fp], #-2844	; 0xfffff4e4
d001e5e8:	4632601a 			; <UNDEFINED> instruction: 0x4632601a
d001e5ec:	fde6f7f1 	stc2l	7, cr15, [r6, #964]!	; 0x3c4
d001e5f0:	22bc491a 	adcscs	r4, ip, #425984	; 0x68000
d001e5f4:	44794648 	ldrbtmi	r4, [r9], #-1608	; 0xfffff9b8
d001e5f8:	fa38f7f6 	blx	0xd0e5c5d8
d001e5fc:	338ff505 	orrcc	pc, pc, #20971520	; 0x1400000
d001e600:	f8c322bc 			; <UNDEFINED> instruction: 0xf8c322bc
d001e604:	6dab21b8 	stfvss	f2, [fp, #736]!	; 0x2e0
d001e608:	3558b163 	ldrbcc	fp, [r8, #-355]	; 0xfffffe9d
d001e60c:	c40fcd0f 	strgt	ip, [pc], #-3343	; 0xd001e614
d001e610:	6023682b 	eorvs	r6, r3, fp, lsr #16
d001e614:	f8c8230a 			; <UNDEFINED> instruction: 0xf8c8230a
d001e618:	e76a3124 	strb	r3, [sl, -r4, lsr #2]!
d001e61c:	e796460a 	ldr	r4, [r6, sl, lsl #12]
d001e620:	e7a04649 	str	r4, [r0, r9, asr #12]!
d001e624:	e7654638 			; <UNDEFINED> instruction: 0xe7654638
d001e628:	0004b2a8 	andeq	fp, r4, r8, lsr #5
d001e62c:	00004d4e 	andeq	r4, r0, lr, asr #26
d001e630:	000049da 	ldrdeq	r4, [r0], -sl
d001e634:	fffffe5d 			; <UNDEFINED> instruction: 0xfffffe5d
d001e638:	00054f2e 	andeq	r4, r5, lr, lsr #30
d001e63c:	00054ef0 	strdeq	r4, [r5], -r0
d001e640:	00009c46 	andeq	r9, r0, r6, asr #24
d001e644:	00004c6e 	andeq	r4, r0, lr, ror #24
d001e648:	00054ffa 	strdeq	r4, [r5], -sl
d001e64c:	ffff1c16 			; <UNDEFINED> instruction: 0xffff1c16
d001e650:	00054fd4 	ldrdeq	r4, [r5], -r4	; <UNPREDICTABLE>
d001e654:	00054fca 	andeq	r4, r5, sl, asr #31
d001e658:	00054fbe 			; <UNDEFINED> instruction: 0x00054fbe
d001e65c:	00000c13 	andeq	r0, r0, r3, lsl ip

Disassembly of section .text.sidc_job_end:

d001e660 <.text.sidc_job_end>:
d001e660:	23004a05 	movwcs	r4, #2565	; 0xa05
d001e664:	6013447a 	andsvs	r4, r3, sl, ror r4
d001e668:	447a4a04 	ldrbtmi	r4, [sl], #-2564	; 0xfffff5fc
d001e66c:	4a046013 	bmi	0xd01366c0
d001e670:	f8c2447a 			; <UNDEFINED> instruction: 0xf8c2447a
d001e674:	47703124 	ldrbmi	r3, [r0, -r4, lsr #2]!
d001e678:	00004bb0 			; <UNDEFINED> instruction: 0x00004bb0
d001e67c:	00054f46 	andeq	r4, r5, r6, asr #30
d001e680:	00054dfc 	strdeq	r4, [r5], -ip

Disassembly of section .text.sidc_job_step:

d001e684 <.text.sidc_job_step>:
d001e684:	38f8f8df 	ldmcc	r8!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d001e688:	e92d447b 	push	{r0, r1, r3, r4, r5, r6, sl, lr}
d001e68c:	681c4ff0 	ldmdavs	ip, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
d001e690:	5d14f2ad 	lfmpl	f7, 1, [r4, #-692]	; 0xfffffd4c
d001e694:	b9144688 	ldmdblt	r4, {r3, r7, r9, sl, lr}
d001e698:	30fff04f 	rscscc	pc, pc, pc, asr #32
d001e69c:	2900e0b9 	stmdbcs	r0, {r0, r3, r4, r5, r7, sp, lr, pc}
d001e6a0:	f8d4d0fa 			; <UNDEFINED> instruction: 0xf8d4d0fa
d001e6a4:	26003124 	strcs	r3, [r0], -r4, lsr #2
d001e6a8:	600e2b0a 	andvs	r2, lr, sl, lsl #22
d001e6ac:	2b09d0f4 	blcs	0xd0292a84
d001e6b0:	f8d4d105 			; <UNDEFINED> instruction: 0xf8d4d105
d001e6b4:	20013120 	andcs	r3, r1, r0, lsr #2
d001e6b8:	3000f8c8 	andcc	pc, r0, r8, asr #17
d001e6bc:	2b01e0a9 	blcs	0xd0096968
d001e6c0:	f8d4d15b 			; <UNDEFINED> instruction: 0xf8d4d15b
d001e6c4:	f8d420e0 			; <UNDEFINED> instruction: 0xf8d420e0
d001e6c8:	428a10d8 	addmi	r1, sl, #216	; 0xd8
d001e6cc:	f8dfd118 			; <UNDEFINED> instruction: 0xf8dfd118
d001e6d0:	447b38b4 	ldrbtmi	r3, [fp], #-2228	; 0xfffff74c
d001e6d4:	2b64681b 	blcs	0xd1938748
d001e6d8:	f8d4d807 			; <UNDEFINED> instruction: 0xf8d4d807
d001e6dc:	f8df20dc 			; <UNDEFINED> instruction: 0xf8df20dc
d001e6e0:	461108a8 	ldrmi	r0, [r1], -r8, lsr #17
d001e6e4:	f7f14478 			; <UNDEFINED> instruction: 0xf7f14478
d001e6e8:	2200fd69 	andcs	pc, r0, #6720	; 0x1a40
d001e6ec:	089cf8df 	ldmeq	ip, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d001e6f0:	44784611 	ldrbtmi	r4, [r8], #-1553	; 0xfffff9ef
d001e6f4:	fd62f7f1 	stc2l	7, cr15, [r2, #-964]!	; 0xfffffc3c
d001e6f8:	f8c42303 			; <UNDEFINED> instruction: 0xf8c42303
d001e6fc:	e07d3124 	rsbs	r3, sp, r4, lsr #2
d001e700:	588cf8df 	stmpl	ip, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d001e704:	01c2eb04 	biceq	lr, r2, r4, lsl #22
d001e708:	7888f8df 	stmvc	r8, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d001e70c:	447f447d 	ldrbtmi	r4, [pc], #-1149	; 0xd001e714
d001e710:	f854722a 			; <UNDEFINED> instruction: 0xf854722a
d001e714:	32200032 	eorcc	r0, r0, #50	; 0x32
d001e718:	2022f854 	eorcs	pc, r2, r4, asr r8	; <UNPREDICTABLE>
d001e71c:	61fcf8c5 	mvnsvs	pc, r5, asr #17
d001e720:	f04f676a 			; <UNDEFINED> instruction: 0xf04f676a
d001e724:	602832ff 	strdvs	r3, [r8], -pc	; <UNPREDICTABLE>
d001e728:	67aa4628 	strvs	r4, [sl, r8, lsr #12]!
d001e72c:	020cf24d 	andeq	pc, ip, #-805306364	; 0xd0000004
d001e730:	f64c50ae 			; <UNDEFINED> instruction: 0xf64c50ae
d001e734:	50ae7288 	adcpl	r7, lr, r8, lsl #5
d001e738:	60ee684a 	rscvs	r6, lr, sl, asr #16
d001e73c:	4650f505 	ldrbmi	pc, [r0], -r5, lsl #10	; <UNPREDICTABLE>
d001e740:	361c606a 	ldrcc	r6, [ip], -sl, rrx
d001e744:	3304e9c5 	movwcc	lr, #18885	; 0x49c5
d001e748:	fbbef7f4 	blx	0xcefdc722
d001e74c:	f7f44628 			; <UNDEFINED> instruction: 0xf7f44628
d001e750:	6aeafbbb 	bvs	0xcfadd644
d001e754:	f5b26dab 			; <UNDEFINED> instruction: 0xf5b26dab
d001e758:	d10c7f83 	smlabble	ip, r3, pc, r7	; <UNPREDICTABLE>
d001e75c:	6833b95b 	ldmdavs	r3!, {r0, r1, r3, r4, r6, r8, fp, ip, sp, pc}
d001e760:	4638b11b 			; <UNDEFINED> instruction: 0x4638b11b
d001e764:	fbb0f7f4 	blx	0xcec5c73e
d001e768:	f8d4e7f3 			; <UNDEFINED> instruction: 0xf8d4e7f3
d001e76c:	f7fd00c0 			; <UNDEFINED> instruction: 0xf7fd00c0
d001e770:	2800febb 	stmdacs	r0, {r0, r1, r3, r4, r5, r7, r9, sl, fp, ip, sp, lr, pc}
d001e774:	2302d1f5 	movwcs	sp, #8693	; 0x21f5
d001e778:	f5b0e7bf 			; <UNDEFINED> instruction: 0xf5b0e7bf
d001e77c:	bf287f00 	svclt	0x00287f00
d001e780:	7000f44f 	andvc	pc, r0, pc, asr #8
d001e784:	bf382801 	svclt	0x00382801
d001e788:	2b022001 	blcs	0xd00a6794
d001e78c:	d1674605 	cmnle	r7, r5, lsl #12
d001e790:	7804f8df 	stmdavc	r4, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d001e794:	a804f8df 	stmdage	r4, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d001e798:	9804f8df 	stmdals	r4, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d001e79c:	44fa447f 	ldrbtmi	r4, [sl], #1151	; 0x47f
d001e7a0:	6dbb44f9 	cfldrsvs	mvf4, [fp, #996]!	; 0x3e4
d001e7a4:	f8dfb16b 			; <UNDEFINED> instruction: 0xf8dfb16b
d001e7a8:	f8d457fc 			; <UNDEFINED> instruction: 0xf8d457fc
d001e7ac:	447d60d4 	ldrbtmi	r6, [sp], #-212	; 0xffffff2c
d001e7b0:	cd0f3558 	cfstr32gt	mvfx3, [pc, #-352]	; 0xd001e658
d001e7b4:	682bc60f 	stmdavs	fp!, {r0, r1, r2, r3, r9, sl, lr, pc}
d001e7b8:	230a6033 	movwcs	r6, #41011	; 0xa033
d001e7bc:	3124f8c4 	smlawtcc	r4, r4, r8, pc	; <UNPREDICTABLE>
d001e7c0:	f8d4e76a 			; <UNDEFINED> instruction: 0xf8d4e76a
d001e7c4:	6afb1128 	bvs	0xcfee2c6c
d001e7c8:	2b7db371 	blcs	0xd1f8b594
d001e7cc:	f5b3d002 			; <UNDEFINED> instruction: 0xf5b3d002
d001e7d0:	d1227f80 	smlawble	r2, r0, pc, r7	; <UNPREDICTABLE>
d001e7d4:	217d4652 	cmncs	sp, r2, asr r6
d001e7d8:	f7f44648 			; <UNDEFINED> instruction: 0xf7f44648
d001e7dc:	f8d9fba3 			; <UNDEFINED> instruction: 0xf8d9fba3
d001e7e0:	b92b3058 	stmdblt	fp!, {r3, r4, r6, ip, sp}
d001e7e4:	1110f8d4 			; <UNDEFINED> instruction: 0x1110f8d4
d001e7e8:	010cf8d4 	ldrdeq	pc, [ip, -r4]
d001e7ec:	fabaf7fb 	blx	0xceedc7e0
d001e7f0:	f8c42300 			; <UNDEFINED> instruction: 0xf8c42300
d001e7f4:	36013128 	strcc	r3, [r1], -r8, lsr #2
d001e7f8:	d1d242b5 	ldrhle	r4, [r2, #37]	; 0x25
d001e7fc:	37a8f8df 	sbfxcc	pc, pc, #17, #9
d001e800:	6d98447b 	cfldrsvs	mvf4, [r8, #492]	; 0x1ec
d001e804:	d1ce2800 	bicle	r2, lr, r0, lsl #16
d001e808:	3124f8d4 	ldrdcc	pc, [r4, -r4]!
d001e80c:	f43f2b09 			; <UNDEFINED> instruction: 0xf43f2b09
d001e810:	f20daf50 	vrecps.f32	q5, <illegal reg q6.5>, q0
d001e814:	e8bd5d14 	pop	{r2, r4, r8, sl, fp, ip, lr}
d001e818:	f7fb8ff0 			; <UNDEFINED> instruction: 0xf7fb8ff0
d001e81c:	2800ff0f 	stmdacs	r0, {r0, r1, r2, r3, r8, r9, sl, fp, ip, sp, lr, pc}
d001e820:	f7fcd1e9 			; <UNDEFINED> instruction: 0xf7fcd1e9
d001e824:	e7e6fcdd 	ubfx	pc, sp, #25, #7
d001e828:	7f80f5b3 	svcvc	0x0080f5b3
d001e82c:	f8d4d115 			; <UNDEFINED> instruction: 0xf8d4d115
d001e830:	f8df30e0 			; <UNDEFINED> instruction: 0xf8df30e0
d001e834:	eb040778 	bl	0xd012061c
d001e838:	330102c3 	movwcc	r0, #4803	; 0x12c3
d001e83c:	68524478 	ldmdavs	r2, {r3, r4, r5, r6, sl, lr}^
d001e840:	f8c46805 			; <UNDEFINED> instruction: 0xf8c46805
d001e844:	442a30e0 	strtmi	r3, [sl], #-224	; 0xffffff20
d001e848:	60f968fd 	ldrshtvs	r6, [r9], #141	; 0x8d
d001e84c:	46386002 	ldrtmi	r6, [r8], -r2
d001e850:	fcd2f7f1 	ldc2l	7, cr15, [r2], {241}	; 0xf1
d001e854:	60fd2301 	rscsvs	r2, sp, r1, lsl #6
d001e858:	f7fee74f 			; <UNDEFINED> instruction: 0xf7fee74f
d001e85c:	e7cafb07 	strb	pc, [sl, r7, lsl #22]	; <UNPREDICTABLE>
d001e860:	d1722b03 	cmnle	r2, r3, lsl #22
d001e864:	5748f8df 			; <UNDEFINED> instruction: 0x5748f8df
d001e868:	f8df2204 			; <UNDEFINED> instruction: 0xf8df2204
d001e86c:	447d1748 	ldrbtmi	r1, [sp], #-1864	; 0xfffff8b8
d001e870:	46284479 			; <UNDEFINED> instruction: 0x46284479
d001e874:	f835f7f2 			; <UNDEFINED> instruction: 0xf835f7f2
d001e878:	db162800 	blle	0xd05a8880
d001e87c:	fb032338 	blx	0xd00e7566
d001e880:	f5035300 			; <UNDEFINED> instruction: 0xf5035300
d001e884:	f893337f 			; <UNDEFINED> instruction: 0xf893337f
d001e888:	b172224e 	cmnlt	r2, lr, asr #4
d001e88c:	324cf893 	subcc	pc, ip, #9633792	; 0x930000
d001e890:	f8dfb1eb 			; <UNDEFINED> instruction: 0xf8dfb1eb
d001e894:	22383724 	eorscs	r3, r8, #36, 14	; 0x900000
d001e898:	fb02447b 	blx	0xd00afa8e
d001e89c:	f5033300 			; <UNDEFINED> instruction: 0xf5033300
d001e8a0:	f893337f 			; <UNDEFINED> instruction: 0xf893337f
d001e8a4:	2b043254 	blcs	0xd012b1fc
d001e8a8:	f8dfd011 			; <UNDEFINED> instruction: 0xf8dfd011
d001e8ac:	f8df1710 			; <UNDEFINED> instruction: 0xf8df1710
d001e8b0:	44790710 	ldrbtmi	r0, [r9], #-1808	; 0xfffff8f0
d001e8b4:	f7f14478 			; <UNDEFINED> instruction: 0xf7f14478
d001e8b8:	f8dffcdb 			; <UNDEFINED> instruction: 0xf8dffcdb
d001e8bc:	44780708 	ldrbtmi	r0, [r8], #-1800	; 0xfffff8f8
d001e8c0:	2396f500 	orrscs	pc, r6, #0, 10
d001e8c4:	32a2f893 	adccc	pc, r2, #9633792	; 0x930000
d001e8c8:	2304b98b 	movwcs	fp, #18827	; 0x498b
d001e8cc:	f8dfe715 			; <UNDEFINED> instruction: 0xf8dfe715
d001e8d0:	233856f8 	teqcs	r8, #248, 12	; 0xf800000
d001e8d4:	fb03447d 	blx	0xd00efad2
d001e8d8:	23005000 	movwcs	r5, #0
d001e8dc:	307ff500 	rsbscc	pc, pc, r0, lsl #10
d001e8e0:	f8d04619 			; <UNDEFINED> instruction: 0xf8d04619
d001e8e4:	6da82248 	sfmvs	f2, 4, [r8, #288]!	; 0x120
d001e8e8:	fb90f7f7 	blx	0xce45c8ce
d001e8ec:	6d86e7e5 	stcvs	7, cr14, [r6, #916]	; 0x394
d001e8f0:	d1ea2e00 	mvnle	r2, r0, lsl #28
d001e8f4:	338ff500 	orrcc	pc, pc, #0, 10
d001e8f8:	76d0f8df 			; <UNDEFINED> instruction: 0x76d0f8df
d001e8fc:	f8d34605 			; <UNDEFINED> instruction: 0xf8d34605
d001e900:	447f31b8 	ldrbtmi	r3, [pc], #-440	; 0xd001e908
d001e904:	310cf8c4 	smlabtcc	ip, r4, r8, pc	; <UNPREDICTABLE>
d001e908:	36027879 			; <UNDEFINED> instruction: 0x36027879
d001e90c:	3b02f817 	blcc	0xd00dc970
d001e910:	ea434628 	b	0xd10f01b8
d001e914:	f7f62101 			; <UNDEFINED> instruction: 0xf7f62101
d001e918:	2ecef8fd 	mcrcs	8, 6, pc, cr14, cr13, {7}	; <UNPREDICTABLE>
d001e91c:	f505d1f4 			; <UNDEFINED> instruction: 0xf505d1f4
d001e920:	f8df338f 			; <UNDEFINED> instruction: 0xf8df338f
d001e924:	260076ac 	strcs	r7, [r0], -ip, lsr #13
d001e928:	31b8f8d3 			; <UNDEFINED> instruction: 0x31b8f8d3
d001e92c:	f8c4447f 			; <UNDEFINED> instruction: 0xf8c4447f
d001e930:	78793110 	ldmdavc	r9!, {r4, r8, ip, sp}^
d001e934:	f8173602 			; <UNDEFINED> instruction: 0xf8173602
d001e938:	46283b02 	strtmi	r3, [r8], -r2, lsl #22
d001e93c:	2101ea43 	tstcs	r1, r3, asr #20
d001e940:	f8e8f7f6 			; <UNDEFINED> instruction: 0xf8e8f7f6
d001e944:	d1f42ef2 	ldrshle	r2, [r4, #226]!	; 0xe2
d001e948:	2b04e7bf 	blcs	0xd015884c
d001e94c:	80a3f040 	adchi	pc, r3, r0, asr #32
d001e950:	a680f8df 	pkhtbge	pc, r0, pc, asr #17	; <UNPREDICTABLE>
d001e954:	9680f8df 	pkhtbls	pc, r0, pc, asr #17	; <UNPREDICTABLE>
d001e958:	44f944fa 	ldrbtmi	r4, [r9], #1274	; 0x4fa
d001e95c:	278ef50a 	strcs	pc, [lr, sl, lsl #10]
d001e960:	30e4f8d4 	ldrdcc	pc, [r4], #132	; 0x84	; <UNPREDICTABLE>
d001e964:	162cf8d7 			; <UNDEFINED> instruction: 0x162cf8d7
d001e968:	2058f8da 	ldrsbcs	pc, [r8], #-138	; 0xffffff76	; <UNPREDICTABLE>
d001e96c:	d244428b 	suble	r4, r4, #-1342177272	; 0xb0000008
d001e970:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d001e974:	00dbaf18 	sbcseq	sl, fp, r8, lsl pc
d001e978:	2386f503 	orrcs	pc, r6, #12582912	; 0xc00000
d001e97c:	632cf203 	msrvs	CPSR_fs, #805306368	; 0x30000000
d001e980:	020aeb03 	andeq	lr, sl, #3072	; 0xc00
d001e984:	000af853 	andeq	pc, sl, r3, asr r8	; <UNPREDICTABLE>
d001e988:	c004f8b2 			; <UNDEFINED> instruction: 0xc004f8b2
d001e98c:	0303f10c 	movweq	pc, #12556	; 0x310c	; <UNPREDICTABLE>
d001e990:	2b01b29b 	blcs	0xd008b404
d001e994:	f8d4d80e 			; <UNDEFINED> instruction: 0xf8d4d80e
d001e998:	f64f3110 			; <UNDEFINED> instruction: 0xf64f3110
d001e99c:	22017efe 	andcs	r7, r1, #4064	; 0xfe0
d001e9a0:	f8d44619 			; <UNDEFINED> instruction: 0xf8d44619
d001e9a4:	45f4310c 	ldrbmi	r3, [r4, #268]!	; 0x10c
d001e9a8:	460bbf18 			; <UNDEFINED> instruction: 0x460bbf18
d001e9ac:	f7f74619 			; <UNDEFINED> instruction: 0xf7f74619
d001e9b0:	e01afaff 			; <UNDEFINED> instruction: 0xe01afaff
d001e9b4:	fb012138 	blx	0xd0066e9e
d001e9b8:	eb0af10c 	bl	0xd02dadf0
d001e9bc:	f5030301 			; <UNDEFINED> instruction: 0xf5030301
d001e9c0:	f893337f 			; <UNDEFINED> instruction: 0xf893337f
d001e9c4:	2a00224e 	bcs	0xd0027304
d001e9c8:	f501d15f 			; <UNDEFINED> instruction: 0xf501d15f
d001e9cc:	f501317f 			; <UNDEFINED> instruction: 0xf501317f
d001e9d0:	4451710a 	ldrbmi	r7, [r1], #-266	; 0xfffffef6
d001e9d4:	c00cf8d1 	ldrdgt	pc, [ip], -r1
d001e9d8:	69cb6908 	stmibvs	fp, {r3, r8, fp, sp, lr}^
d001e9dc:	f8ca7e0a 			; <UNDEFINED> instruction: 0xf8ca7e0a
d001e9e0:	e9ca3068 	stmib	sl, {r3, r5, r6, ip, sp}^
d001e9e4:	e9ca9c16 	stmib	sl, {r1, r2, r4, sl, fp, ip, pc}^
d001e9e8:	f8d40218 			; <UNDEFINED> instruction: 0xf8d40218
d001e9ec:	360130e4 	strcc	r3, [r1], -r4, ror #1
d001e9f0:	42b53301 	adcsmi	r3, r5, #67108864	; 0x4000000
d001e9f4:	30e4f8c4 	rsccc	pc, r4, r4, asr #17
d001e9f8:	f8dfd1b2 			; <UNDEFINED> instruction: 0xf8dfd1b2
d001e9fc:	f8d435e0 			; <UNDEFINED> instruction: 0xf8d435e0
d001ea00:	447b10e4 	ldrbtmi	r1, [fp], #-228	; 0xffffff1c
d001ea04:	228ef503 	addcs	pc, lr, #12582912	; 0xc00000
d001ea08:	262cf8d2 			; <UNDEFINED> instruction: 0x262cf8d2
d001ea0c:	f47f4291 			; <UNDEFINED> instruction: 0xf47f4291
d001ea10:	6d9aaef5 	ldcvs	14, cr10, [sl, #980]	; 0x3d4
d001ea14:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d001ea18:	f503aec6 			; <UNDEFINED> instruction: 0xf503aec6
d001ea1c:	f503328f 			; <UNDEFINED> instruction: 0xf503328f
d001ea20:	e9d2337f 	ldmib	r2, {r0, r1, r2, r3, r4, r5, r6, r8, r9, ip, sp}^
d001ea24:	f8d3126e 			; <UNDEFINED> instruction: 0xf8d3126e
d001ea28:	44113218 	ldrmi	r3, [r1], #-536	; 0xfffffde8
d001ea2c:	f8c41cc8 			; <UNDEFINED> instruction: 0xf8c41cc8
d001ea30:	f02010f4 			; <UNDEFINED> instruction: 0xf02010f4
d001ea34:	f8c40003 			; <UNDEFINED> instruction: 0xf8c40003
d001ea38:	b35300f8 	cmplt	r3, #248	; 0xf8
d001ea3c:	f1034403 			; <UNDEFINED> instruction: 0xf1034403
d001ea40:	4299021f 	addsmi	r0, r9, #-268435455	; 0xf0000001
d001ea44:	30fcf8c4 	rscscc	pc, ip, r4, asr #17
d001ea48:	021ff022 	andseq	pc, pc, #34	; 0x22
d001ea4c:	2100f8c4 	smlabtcs	r0, r4, r8, pc	; <UNPREDICTABLE>
d001ea50:	f5b3d811 			; <UNDEFINED> instruction: 0xf5b3d811
d001ea54:	d80e0fbe 	stmdale	lr, {r1, r2, r3, r4, r5, r7, r8, r9, sl, fp}
d001ea58:	d80c4281 	stmdale	ip, {r0, r7, r9, lr}
d001ea5c:	d30a429a 	movwle	r4, #41626	; 0xa29a
d001ea60:	357cf8df 	ldrbcc	pc, [ip, #-2271]!	; 0xfffff721	; <UNPREDICTABLE>
d001ea64:	02bef5c2 	adcseq	pc, lr, #813694976	; 0x30800000
d001ea68:	f503447b 			; <UNDEFINED> instruction: 0xf503447b
d001ea6c:	f8d3337f 			; <UNDEFINED> instruction: 0xf8d3337f
d001ea70:	4293321c 	addsmi	r3, r3, #28, 4	; 0xc0000001
d001ea74:	f8dfd907 			; <UNDEFINED> instruction: 0xf8dfd907
d001ea78:	f8df156c 			; <UNDEFINED> instruction: 0xf8df156c
d001ea7c:	4479056c 	ldrbtmi	r0, [r9], #-1388	; 0xfffffa94
d001ea80:	f7f14478 			; <UNDEFINED> instruction: 0xf7f14478
d001ea84:	2305fbf5 	movwcs	pc, #23541	; 0x5bf5	; <UNPREDICTABLE>
d001ea88:	2201e637 	andcs	lr, r1, #57671680	; 0x3700000
d001ea8c:	1248f8d3 	subne	pc, r8, #13828096	; 0xd30000
d001ea90:	460be78d 	strmi	lr, [fp], -sp, lsl #15
d001ea94:	2b05e7d3 	blcs	0xd01989e8
d001ea98:	80adf040 	adchi	pc, sp, r0, asr #32
d001ea9c:	754cf8df 	strbvc	pc, [ip, #-2271]	; 0xfffff721	; <UNPREDICTABLE>
d001eaa0:	b54cf8df 	strblt	pc, [ip, #-2271]	; 0xfffff721	; <UNPREDICTABLE>
d001eaa4:	44fb447f 	ldrbtmi	r4, [fp], #1151	; 0x47f
d001eaa8:	3a5ff507 	bcc	0xd181becc
d001eaac:	20e8f8d4 	ldrdcs	pc, [r8], #132	; 0x84	; <UNPREDICTABLE>
d001eab0:	13c0f8da 	bicne	pc, r0, #14286848	; 0xda0000
d001eab4:	428a6dbb 	addmi	r6, sl, #11968	; 0x2ec0
d001eab8:	2b00d23b 	blcs	0xd00533ac
d001eabc:	ae73f47f 	mrcge	4, 3, APSR_nzcv, cr3, cr15, {3}
d001eac0:	4353230c 	cmpmi	r3, #12, 6	; 0x30000000
d001eac4:	3347f503 	movtcc	pc, #29955	; 0x7503	; <UNPREDICTABLE>
d001eac8:	7370f503 	cmnvc	r0, #12582912	; 0xc00000	; <UNPREDICTABLE>
d001eacc:	59d819da 	ldmibpl	r8, {r1, r3, r4, r6, r7, r8, fp, ip}^
d001ead0:	9004f8d2 	ldrdls	pc, [r4], -r2
d001ead4:	2a007a12 	bcs	0xd003d324
d001ead8:	f507d143 			; <UNDEFINED> instruction: 0xf507d143
d001eadc:	f8d3338f 			; <UNDEFINED> instruction: 0xf8d3338f
d001eae0:	444b31b8 	strbmi	r3, [fp], #-440	; 0xfffffe48
d001eae4:	090cf100 	stmdbeq	ip, {r8, ip, sp, lr, pc}
d001eae8:	3cfff102 	ldfccp	f7, [pc], #8	; 0xd001eaf8
d001eaec:	2140f24f 	cmpcs	r0, pc, asr #4	; <UNPREDICTABLE>
d001eaf0:	f0299000 			; <UNDEFINED> instruction: 0xf0299000
d001eaf4:	f1dc0903 			; <UNDEFINED> instruction: 0xf1dc0903
d001eaf8:	f1060200 			; <UNDEFINED> instruction: 0xf1060200
d001eafc:	eba30601 	bl	0xce8e0308
d001eb00:	eb420909 	bl	0xd10a0f2c
d001eb04:	fa1f020c 	blx	0xd07df33c
d001eb08:	9201f389 	andls	pc, r1, #603979778	; 0x24000002
d001eb0c:	fba4f7f6 	blx	0xce95caee
d001eb10:	ea4f9800 	b	0xd1404b18
d001eb14:	9a014319 	bls	0xd006f780
d001eb18:	21c0f24f 	biccs	pc, r0, pc, asr #4
d001eb1c:	f7f63004 			; <UNDEFINED> instruction: 0xf7f63004
d001eb20:	f8d4fb9b 			; <UNDEFINED> instruction: 0xf8d4fb9b
d001eb24:	42b530e8 	adcsmi	r3, r5, #232	; 0xe8
d001eb28:	0301f103 	movweq	pc, #4355	; 0x1103	; <UNPREDICTABLE>
d001eb2c:	30e8f8c4 	rsccc	pc, r8, r4, asr #17
d001eb30:	f8dfd1bc 			; <UNDEFINED> instruction: 0xf8dfd1bc
d001eb34:	f8d434c0 			; <UNDEFINED> instruction: 0xf8d434c0
d001eb38:	447b10e8 	ldrbtmi	r1, [fp], #-232	; 0xffffff18
d001eb3c:	325ff503 	subscc	pc, pc, #12582912	; 0xc00000
d001eb40:	23c0f8d2 	biccs	pc, r0, #13762560	; 0xd20000
d001eb44:	f47f4291 			; <UNDEFINED> instruction: 0xf47f4291
d001eb48:	6d9aae59 	ldcvs	14, cr10, [sl, #356]	; 0x164
d001eb4c:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d001eb50:	f8dfae2a 			; <UNDEFINED> instruction: 0xf8dfae2a
d001eb54:	461104a4 	ldrmi	r0, [r1], -r4, lsr #9
d001eb58:	f7f14478 			; <UNDEFINED> instruction: 0xf7f14478
d001eb5c:	2306fb2f 	movwcs	pc, #27439	; 0x6b2f	; <UNPREDICTABLE>
d001eb60:	2a01e5cb 	bcs	0xd0098294
d001eb64:	233cd121 	teqcs	ip, #1073741832	; 0x40000008
d001eb68:	7309fb03 	movwvc	pc, #39683	; 0x9b03	; <UNPREDICTABLE>
d001eb6c:	335ff503 	cmpcc	pc, #12582912	; 0xc00000	; <UNPREDICTABLE>
d001eb70:	13eff893 	mvnne	pc, #9633792	; 0x930000
d001eb74:	f893b9b1 			; <UNDEFINED> instruction: 0xf893b9b1
d001eb78:	390713ec 	stmdbcc	r7, {r2, r3, r5, r6, r7, r8, r9, ip}
d001eb7c:	290ab2c9 	stmdbcs	sl, {r0, r3, r6, r7, r9, ip, sp, pc}
d001eb80:	f240d810 	vtst.8	d29, d0, d0
d001eb84:	fa235303 	blx	0xd08f3798
d001eb88:	07cbf101 	strbeq	pc, [fp, r1, lsl #2]	; <UNPREDICTABLE>
d001eb8c:	f8d4d50a 			; <UNDEFINED> instruction: 0xf8d4d50a
d001eb90:	233c1100 	teqcs	ip, #0, 2
d001eb94:	b309fb03 	movwlt	pc, #39683	; 0x9b03	; <UNPREDICTABLE>
d001eb98:	335ff503 	cmpcc	pc, #12582912	; 0xc00000	; <UNPREDICTABLE>
d001eb9c:	33e8f8d3 	mvncc	pc, #13828096	; 0xd30000
d001eba0:	e79f440b 	ldr	r4, [pc, fp, lsl #8]
d001eba4:	10f8f8d4 	ldrsbtne	pc, [r8], #132	; 0x84	; <UNPREDICTABLE>
d001eba8:	2338e7f3 	teqcs	r8, #63700992	; 0x3cc0000
d001ebac:	f309fb03 	vqrdmulh.s<illegal width 8>	d15, d9, d3
d001ebb0:	f50118f9 			; <UNDEFINED> instruction: 0xf50118f9
d001ebb4:	f891317f 			; <UNDEFINED> instruction: 0xf891317f
d001ebb8:	f1bcc24e 			; <UNDEFINED> instruction: 0xf1bcc24e
d001ebbc:	d1110f00 	tstle	r1, r0, lsl #30
d001ebc0:	337ff503 	cmncc	pc, #12582912	; 0xc00000	; <UNPREDICTABLE>
d001ebc4:	5434f8df 	ldrtpl	pc, [r4], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d001ebc8:	730af503 	movwvc	pc, #42243	; 0xa503	; <UNPREDICTABLE>
d001ebcc:	443b447d 	ldrtmi	r4, [fp], #-1149	; 0xfffffb83
d001ebd0:	691968d8 	ldmdbvs	r9, {r3, r4, r6, r7, fp, sp, lr}
d001ebd4:	7e1b69da 			; <UNDEFINED> instruction: 0x7e1b69da
d001ebd8:	e9c766ba 	stmib	r7, {r1, r3, r4, r5, r7, r9, sl, sp, lr}^
d001ebdc:	e9c75016 	stmib	r7, {r1, r2, r4, ip, lr}^
d001ebe0:	e5e01318 	strb	r1, [r0, #792]!	; 0x318
d001ebe4:	3248f8d1 	subcc	pc, r8, #13697024	; 0xd10000
d001ebe8:	5100f44f 	tstpl	r0, pc, asr #8	; <UNPREDICTABLE>
d001ebec:	0301f043 	movweq	pc, #4163	; 0x1043	; <UNPREDICTABLE>
d001ebf0:	1108f8c4 	smlabtne	r8, r4, r8, pc	; <UNPREDICTABLE>
d001ebf4:	2b06e776 	blcs	0xd01d89d4
d001ebf8:	f8dfd11a 			; <UNDEFINED> instruction: 0xf8dfd11a
d001ebfc:	44791404 	ldrbtmi	r1, [r9], #-1028	; 0xfffffbfc
d001ec00:	338ff501 	orrcc	pc, pc, #4194304	; 0x400000
d001ec04:	71e0f503 	mvnvc	pc, r3, lsl #10
d001ec08:	01b8f8d3 			; <UNDEFINED> instruction: 0x01b8f8d3
d001ec0c:	21bcf8d3 			; <UNDEFINED> instruction: 0x21bcf8d3
d001ec10:	ff2cf7f5 			; <UNDEFINED> instruction: 0xff2cf7f5
d001ec14:	10fcf8d4 	ldrsbtne	pc, [ip], #132	; 0x84	; <UNPREDICTABLE>
d001ec18:	00f4f8d4 	ldrsbteq	pc, [r4], #132	; 0x84	; <UNPREDICTABLE>
d001ec1c:	f0213103 			; <UNDEFINED> instruction: 0xf0213103
d001ec20:	f8c40103 			; <UNDEFINED> instruction: 0xf8c40103
d001ec24:	1a091104 	bne	0xd026303c
d001ec28:	ff38f7f5 			; <UNDEFINED> instruction: 0xff38f7f5
d001ec2c:	e5642307 	strb	r2, [r4, #-775]!	; 0xfffffcf9
d001ec30:	f0402b07 			; <UNDEFINED> instruction: 0xf0402b07
d001ec34:	4bf380b5 	blmi	0xcfcfef10
d001ec38:	0a00f04f 	beq	0xd005ad7c
d001ec3c:	9300447b 	movwls	r4, #1147	; 0x47b
d001ec40:	3367f503 	msrcc	SPSR_sxc, #12582912	; 0xc00000
d001ec44:	4bf09302 	blmi	0xcfc43854
d001ec48:	9301447b 	movwls	r4, #5243	; 0x147b
d001ec4c:	9b00e049 	blls	0xd0056d78
d001ec50:	fb06263c 	blx	0xd01a854a
d001ec54:	f5063601 			; <UNDEFINED> instruction: 0xf5063601
d001ec58:	f896365f 			; <UNDEFINED> instruction: 0xf896365f
d001ec5c:	2b0033ef 	blcs	0xd002bc20
d001ec60:	f8d4d055 			; <UNDEFINED> instruction: 0xf8d4d055
d001ec64:	f8d610f0 			; <UNDEFINED> instruction: 0xf8d610f0
d001ec68:	42b973f8 	adcsmi	r7, r9, #248, 6	; 0xe0000003
d001ec6c:	1a7fd26f 	bne	0xd2013630
d001ec70:	030aeba5 	movweq	lr, #43941	; 0xaba5
d001ec74:	23f4f8d6 	mvnscs	pc, #14024704	; 0xd60000
d001ec78:	7b88f50d 	blvc	0xce25c0b4
d001ec7c:	7f80f5b7 	svcvc	0x0080f5b7
d001ec80:	0001f04f 	andeq	pc, r1, pc, asr #32
d001ec84:	465a4411 			; <UNDEFINED> instruction: 0x465a4411
d001ec88:	f44fbf28 			; <UNDEFINED> instruction: 0xf44fbf28
d001ec8c:	00897780 	addeq	r7, r9, r0, lsl #15
d001ec90:	bf28429f 	svclt	0x0028429f
d001ec94:	00bb461f 	adcseq	r4, fp, pc, lsl r6
d001ec98:	f7f59303 			; <UNDEFINED> instruction: 0xf7f59303
d001ec9c:	2800fe6b 	stmdacs	r0, {r0, r1, r3, r5, r6, r9, sl, fp, ip, sp, lr, pc}
d001eca0:	f896d060 			; <UNDEFINED> instruction: 0xf896d060
d001eca4:	f8d413ec 			; <UNDEFINED> instruction: 0xf8d413ec
d001eca8:	2907c0f8 	stmdbcs	r7, {r3, r4, r5, r6, r7, lr, pc}
d001ecac:	03e8f8d6 	mvneq	pc, #14024704	; 0xd60000
d001ecb0:	20f0f8d4 	ldrsbtcs	pc, [r0], #132	; 0x84	; <UNPREDICTABLE>
d001ecb4:	d1259b03 			; <UNDEFINED> instruction: 0xd1259b03
d001ecb8:	4619ab04 	ldrmi	sl, [r9], -r4, lsl #22
d001ecbc:	0901f109 	stmdbeq	r1, {r0, r3, r8, ip, sp, lr, pc}
d001ecc0:	6b04f85b 	blvs	0xd015ce34
d001ecc4:	f80345b9 			; <UNDEFINED> instruction: 0xf80345b9
d001ecc8:	d1f76b01 	mvnsle	r6, r1, lsl #22
d001eccc:	463a4494 			; <UNDEFINED> instruction: 0x463a4494
d001ecd0:	44ba4460 	ldrtmi	r4, [sl], #1120	; 0x460
d001ecd4:	fecaf7f5 	mcr2	7, 6, pc, cr10, cr5, {7}	; <UNPREDICTABLE>
d001ecd8:	30f0f8d4 	ldrsbtcc	pc, [r0], #132	; 0x84	; <UNPREDICTABLE>
d001ecdc:	f8c4443b 			; <UNDEFINED> instruction: 0xf8c4443b
d001ece0:	9b0030f0 	blls	0xd002b0a8
d001ece4:	10ecf8d4 	ldrdne	pc, [ip], #132	; 0x84	; <UNPREDICTABLE>
d001ece8:	9058f8d3 	ldrsbls	pc, [r8], #-131	; 0xffffff7d	; <UNPREDICTABLE>
d001ecec:	f8d39b02 			; <UNDEFINED> instruction: 0xf8d39b02
d001ecf0:	429931c4 	addsmi	r3, r9, #196, 2	; 0x31
d001ecf4:	4555d236 	ldrbmi	sp, [r5, #-566]	; 0xfffffdca
d001ecf8:	ad80f67f 	stcge	6, cr15, [r0, #508]	; 0x1fc
d001ecfc:	0f00f1b9 	svceq	0x0000f1b9
d001ed00:	e550d0a5 	ldrb	sp, [r0, #-165]	; 0xffffff5b
d001ed04:	0082eb00 	addeq	lr, r2, r0, lsl #22
d001ed08:	461a4659 			; <UNDEFINED> instruction: 0x461a4659
d001ed0c:	f896e7e0 			; <UNDEFINED> instruction: 0xf896e7e0
d001ed10:	3a0723ec 	bcc	0xd01e7cc8
d001ed14:	2a0ab2d2 	bcs	0xd02cb864
d001ed18:	f240d805 	vadd.i8	d29, d0, d5
d001ed1c:	fa235303 	blx	0xd08f3930
d001ed20:	07d6f202 	ldrbeq	pc, [r6, r2, lsl #4]	; <UNPREDICTABLE>
d001ed24:	233cd413 	teqcs	ip, #318767104	; 0x13000000
d001ed28:	f8d49a01 			; <UNDEFINED> instruction: 0xf8d49a01
d001ed2c:	434b00f8 	movtmi	r0, #45304	; 0xb0f8
d001ed30:	f5039e01 			; <UNDEFINED> instruction: 0xf5039e01
d001ed34:	4413315f 	ldrmi	r3, [r3], #-351	; 0xfffffea1
d001ed38:	f5032204 			; <UNDEFINED> instruction: 0xf5032204
d001ed3c:	f501335f 			; <UNDEFINED> instruction: 0xf501335f
d001ed40:	f8d37179 			; <UNDEFINED> instruction: 0xf8d37179
d001ed44:	443133e8 	ldrtmi	r3, [r1], #-1000	; 0xfffffc18
d001ed48:	f7f54418 			; <UNDEFINED> instruction: 0xf7f54418
d001ed4c:	f8d4fe8f 			; <UNDEFINED> instruction: 0xf8d4fe8f
d001ed50:	f10a30ec 			; <UNDEFINED> instruction: 0xf10a30ec
d001ed54:	33010a01 	movwcc	r0, #6657	; 0x1a01
d001ed58:	30ecf8c4 	rsccc	pc, ip, r4, asr #17
d001ed5c:	f8c42300 			; <UNDEFINED> instruction: 0xf8c42300
d001ed60:	e7be30f0 			; <UNDEFINED> instruction: 0xe7be30f0
d001ed64:	f8d44ba9 			; <UNDEFINED> instruction: 0xf8d44ba9
d001ed68:	447b20ec 	ldrbtmi	r2, [fp], #-236	; 0xffffff14
d001ed6c:	f5036d99 			; <UNDEFINED> instruction: 0xf5036d99
d001ed70:	f8d33367 			; <UNDEFINED> instruction: 0xf8d33367
d001ed74:	429a31c4 	addsmi	r3, sl, #196, 2	; 0x31
d001ed78:	ad40f47f 	cfstrdge	mvd15, [r0, #-508]	; 0xfffffe04
d001ed7c:	f47f2900 			; <UNDEFINED> instruction: 0xf47f2900
d001ed80:	48a3ad12 	stmiami	r3!, {r1, r4, r8, sl, fp, sp, pc}
d001ed84:	20fcf8d4 	ldrsbtcs	pc, [ip], #132	; 0x84	; <UNPREDICTABLE>
d001ed88:	f7f14478 			; <UNDEFINED> instruction: 0xf7f14478
d001ed8c:	f04ffa17 			; <UNDEFINED> instruction: 0xf04ffa17
d001ed90:	f8c433ff 			; <UNDEFINED> instruction: 0xf8c433ff
d001ed94:	230a3118 	movwcs	r3, #41240	; 0xa118
d001ed98:	311cf8c4 	tstcc	ip, r4, asr #17	; <UNPREDICTABLE>
d001ed9c:	e4ac2308 	strt	r2, [ip], #776	; 0x308
d001eda0:	f47f2b08 			; <UNDEFINED> instruction: 0xf47f2b08
d001eda4:	f8dfad2b 			; <UNDEFINED> instruction: 0xf8dfad2b
d001eda8:	0185a26c 	orreq	sl, r5, ip, ror #4
d001edac:	f8df2700 			; <UNDEFINED> instruction: 0xf8df2700
d001edb0:	44fab268 	ldrbtmi	fp, [sl], #616	; 0x268
d001edb4:	1114f8d4 			; <UNDEFINED> instruction: 0x1114f8d4
d001edb8:	30fcf8d4 	ldrsbtcc	pc, [ip], #132	; 0x84	; <UNPREDICTABLE>
d001edbc:	d2184299 	andsle	r4, r8, #-1879048183	; 0x90000009
d001edc0:	6058f8da 	ldrsbvs	pc, [r8], #-138	; 0xffffff76	; <UNPREDICTABLE>
d001edc4:	1a5bb9ae 	bne	0xd170d484
d001edc8:	0907eba5 	stmdbeq	r7, {r0, r2, r5, r7, r8, r9, fp, sp, lr, pc}
d001edcc:	3140aa44 	cmpcc	r0, r4, asr #20
d001edd0:	6f80f5b3 	svcvs	0x0080f5b3
d001edd4:	92004630 	andls	r4, r0, #48, 12	; 0x3000000
d001edd8:	f44fbf28 			; <UNDEFINED> instruction: 0xf44fbf28
d001eddc:	45996380 	ldrmi	r6, [r9, #896]	; 0x380
d001ede0:	4699bf28 	ldrmi	fp, [r9], r8, lsr #30
d001ede4:	f7f5464b 			; <UNDEFINED> instruction: 0xf7f5464b
d001ede8:	9a00fdc5 	bls	0xd005e504
d001edec:	f0402800 			; <UNDEFINED> instruction: 0xf0402800
d001edf0:	4b8a8081 	blmi	0xce2beffc
d001edf4:	681b447b 	ldmdavs	fp, {r0, r1, r3, r4, r5, r6, sl, lr}
d001edf8:	f0402b00 			; <UNDEFINED> instruction: 0xf0402b00
d001edfc:	f8d48087 			; <UNDEFINED> instruction: 0xf8d48087
d001ee00:	f8d430fc 			; <UNDEFINED> instruction: 0xf8d430fc
d001ee04:	429a2114 	addsmi	r2, sl, #20, 2
d001ee08:	acf8f47f 	cfldrdge	mvd15, [r8], #508	; 0x1fc
d001ee0c:	447b4b84 	ldrbtmi	r4, [fp], #-2948	; 0xfffff47c
d001ee10:	2b006d9b 	blcs	0xd003a484
d001ee14:	acf2f47f 	cfldrdge	mvd15, [r2], #508	; 0x1fc
d001ee18:	311cf8d4 			; <UNDEFINED> instruction: 0x311cf8d4
d001ee1c:	d8042b64 	stmdale	r4, {r2, r5, r6, r8, r9, fp, sp}
d001ee20:	46114880 	ldrmi	r4, [r1], -r0, lsl #17
d001ee24:	f7f14478 			; <UNDEFINED> instruction: 0xf7f14478
d001ee28:	ad04f9c9 	vstrge.16	s30, [r4, #-402]	; 0xfffffe6e	; <UNPREDICTABLE>
d001ee2c:	21002640 	tstcs	r0, r0, asr #12
d001ee30:	46284632 			; <UNDEFINED> instruction: 0x46284632
d001ee34:	fbecf002 	blx	0xcfb5ae46
d001ee38:	2208497b 	andcs	r4, r8, #2015232	; 0x1ec000
d001ee3c:	44794628 	ldrbtmi	r4, [r9], #-1576	; 0xfffff9d8
d001ee40:	fbf4f002 	blx	0xcfd5ae52
d001ee44:	1104f8d4 	ldrdne	pc, [r4, -r4]
d001ee48:	f8d42302 			; <UNDEFINED> instruction: 0xf8d42302
d001ee4c:	44310100 	ldrtmi	r0, [r1], #-256	; 0xffffff00
d001ee50:	2108f8d4 	ldrdcs	pc, [r8, -r4]
d001ee54:	3602e9c5 	strcc	lr, [r2], -r5, asr #19
d001ee58:	f8d44e74 			; <UNDEFINED> instruction: 0xf8d44e74
d001ee5c:	447e30fc 	ldrbtmi	r3, [lr], #-252	; 0xffffff04
d001ee60:	616b636a 	cmnvs	fp, sl, ror #6
d001ee64:	337ff506 	cmncc	pc, #25165824	; 0x1800000	; <UNPREDICTABLE>
d001ee68:	f8d36129 			; <UNDEFINED> instruction: 0xf8d36129
d001ee6c:	331f321c 	tstcc	pc, #28, 4	; 0xc0000001
d001ee70:	46284403 	strtmi	r4, [r8], -r3, lsl #8
d001ee74:	031ff023 	tsteq	pc, #35	; 0x23	; <UNPREDICTABLE>
d001ee78:	3a004413 	bcc	0xd002fecc
d001ee7c:	f04f61ab 			; <UNDEFINED> instruction: 0xf04f61ab
d001ee80:	bf180301 	svclt	0x00180301
d001ee84:	61eb2201 	mvnvs	r2, r1, lsl #4
d001ee88:	63aa4b3c 			; <UNDEFINED> instruction: 0x63aa4b3c
d001ee8c:	3108e9c5 	smlabtcc	r8, r5, r9, lr
d001ee90:	62eb2320 	rscvs	r2, fp, #32, 6	; 0x80000000
d001ee94:	3118f8d4 			; <UNDEFINED> instruction: 0x3118f8d4
d001ee98:	63eb43db 	mvnvs	r4, #1811939331	; 0x6c000003
d001ee9c:	fa74f7fd 	blx	0xd1d5ce98
d001eea0:	4963b920 	stmdbmi	r3!, {r5, r8, fp, ip, sp, pc}^
d001eea4:	44794630 	ldrbtmi	r4, [r9], #-1584	; 0xfffff9d0
d001eea8:	f9e2f7f1 			; <UNDEFINED> instruction: 0xf9e2f7f1
d001eeac:	447e4e61 	ldrbtmi	r4, [lr], #-3681	; 0xfffff19f
d001eeb0:	29006db1 	stmdbcs	r0, {r0, r4, r5, r7, r8, sl, fp, sp, lr}
d001eeb4:	aca2f47f 	cfstrsge	mvf15, [r2], #508	; 0x1fc
d001eeb8:	462a2340 	strtmi	r2, [sl], -r0, asr #6
d001eebc:	f7f54608 			; <UNDEFINED> instruction: 0xf7f54608
d001eec0:	6db3fd91 	ldcvs	13, cr15, [r3, #580]!	; 0x244
d001eec4:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001eec8:	692bac99 	stmdbvs	fp!, {r0, r3, r4, r7, sl, fp, sp, pc}
d001eecc:	3120f8c4 	smlawtcc	r0, r4, r8, pc	; <UNPREDICTABLE>
d001eed0:	e4122309 	ldr	r2, [r2], #-777	; 0xfffffcf7
d001eed4:	1118f8d4 			; <UNDEFINED> instruction: 0x1118f8d4
d001eed8:	404b5d93 	umaalmi	r5, fp, r3, sp
d001eedc:	f0132108 			; <UNDEFINED> instruction: 0xf0132108
d001eee0:	bf180001 	svclt	0x00180001
d001eee4:	39014658 	stmdbcc	r1, {r3, r4, r6, r9, sl, lr}
d001eee8:	0353ea80 	cmpeq	r3, #128, 20	; 0x80000
d001eeec:	3601d1f7 			; <UNDEFINED> instruction: 0x3601d1f7
d001eef0:	3118f8c4 	tstcc	r8, r4, asr #17	; <UNPREDICTABLE>
d001eef4:	d1ed454e 	mvnle	r4, lr, asr #10
d001eef8:	3114f8d4 			; <UNDEFINED> instruction: 0x3114f8d4
d001eefc:	44334437 	ldrtmi	r4, [r3], #-1079	; 0xfffffbc9
d001ef00:	f8c442bd 			; <UNDEFINED> instruction: 0xf8c442bd
d001ef04:	f63f3114 			; <UNDEFINED> instruction: 0xf63f3114
d001ef08:	e772af55 			; <UNDEFINED> instruction: 0xe772af55
d001ef0c:	20fcf8d4 	ldrsbtcs	pc, [ip], #132	; 0x84	; <UNPREDICTABLE>
d001ef10:	4f00f5b2 	svcmi	0x0000f5b2
d001ef14:	af73f4ff 	svcge	0x0073f4ff
d001ef18:	711cf8d4 			; <UNDEFINED> instruction: 0x711cf8d4
d001ef1c:	f63f2f64 			; <UNDEFINED> instruction: 0xf63f2f64
d001ef20:	2364af6e 	cmncs	r4, #440	; 0x1b8
d001ef24:	fbb22500 	blx	0xceca832e
d001ef28:	469afcf3 			; <UNDEFINED> instruction: 0x469afcf3
d001ef2c:	2e1cfb03 	vnmlscs.f64	d15, d12, d3
d001ef30:	1114f8d4 			; <UNDEFINED> instruction: 0x1114f8d4
d001ef34:	0901f103 	stmdbeq	r1, {r0, r1, r8, ip, sp, lr, pc}
d001ef38:	d30e429d 	movwle	r4, #58013	; 0xe29d
d001ef3c:	f63f42af 			; <UNDEFINED> instruction: 0xf63f42af
d001ef40:	483daf5e 	ldmdami	sp!, {r1, r2, r3, r4, r6, r8, r9, sl, fp, sp, pc}
d001ef44:	f7f14478 			; <UNDEFINED> instruction: 0xf7f14478
d001ef48:	230af939 	movwcs	pc, #43321	; 0xa939	; <UNPREDICTABLE>
d001ef4c:	f5f3fbb5 			; <UNDEFINED> instruction: 0xf5f3fbb5
d001ef50:	3303fb05 	movwcc	pc, #15109	; 0x3b05	; <UNPREDICTABLE>
d001ef54:	311cf8c4 	tstcc	ip, r4, asr #17	; <UNPREDICTABLE>
d001ef58:	eb09e751 	bl	0xd0298ca4
d001ef5c:	08760605 	ldmdaeq	r6!, {r0, r2, r9, sl}^
d001ef60:	f00efb06 			; <UNDEFINED> instruction: 0xf00efb06
d001ef64:	fbb03063 	blx	0xcec2b0fa
d001ef68:	fb06f0fa 	blx	0xd01db35a
d001ef6c:	4288000c 	addmi	r0, r8, #12
d001ef70:	1e73d901 	vaddne.f16	s27, s6, s2	; <UNPREDICTABLE>
d001ef74:	4635e7dc 			; <UNDEFINED> instruction: 0x4635e7dc
d001ef78:	bf00e7de 	svclt	0x0000e7de
d001ef7c:	d0010000 	andle	r0, r1, r0
d001ef80:	00004b8c 	andeq	r4, r0, ip, lsl #23
d001ef84:	00054ed2 	ldrdeq	r4, [r5], -r2
d001ef88:	ffff1b00 			; <UNDEFINED> instruction: 0xffff1b00
d001ef8c:	fffffc95 			; <UNDEFINED> instruction: 0xfffffc95
d001ef90:	00009ab8 			; <UNDEFINED> instruction: 0x00009ab8
d001ef94:	00009ab6 			; <UNDEFINED> instruction: 0x00009ab6
d001ef98:	00009a28 	andeq	r9, r0, r8, lsr #20
d001ef9c:	ffffc67e 			; <UNDEFINED> instruction: 0xffffc67e
d001efa0:	00009a24 	andeq	r9, r0, r4, lsr #20
d001efa4:	00009a16 	andeq	r9, r0, r6, lsl sl
d001efa8:	000099c4 	andeq	r9, r0, r4, asr #19
d001efac:	00054d6c 	andeq	r4, r5, ip, ror #26
d001efb0:	00009956 	andeq	r9, r0, r6, asr r9
d001efb4:	ffffe2bf 			; <UNDEFINED> instruction: 0xffffe2bf
d001efb8:	0000992c 	andeq	r9, r0, ip, lsr #18
d001efbc:	fffffae0 			; <UNDEFINED> instruction: 0xfffffae0
d001efc0:	00009910 	andeq	r9, r0, r0, lsl r9
d001efc4:	00009906 	andeq	r9, r0, r6, lsl #18
d001efc8:	000098f0 	strdeq	r9, [r0], -r0
d001efcc:	00000747 	andeq	r0, r0, r7, asr #14
d001efd0:	000007eb 	andeq	r0, r0, fp, ror #15
d001efd4:	0000986c 	andeq	r9, r0, ip, ror #16
d001efd8:	fffffa71 			; <UNDEFINED> instruction: 0xfffffa71
d001efdc:	000097c2 	andeq	r9, r0, r2, asr #15
d001efe0:	0000975c 	andeq	r9, r0, ip, asr r7
d001efe4:	fffff96f 			; <UNDEFINED> instruction: 0xfffff96f
d001efe8:	00009744 	andeq	r9, r0, r4, asr #14
d001efec:	00009720 	andeq	r9, r0, r0, lsr #14
d001eff0:	0000971e 	andeq	r9, r0, lr, lsl r7
d001eff4:	0000968a 	andeq	r9, r0, sl, lsl #13
d001eff8:	fffff8ee 			; <UNDEFINED> instruction: 0xfffff8ee
d001effc:	fffff856 			; <UNDEFINED> instruction: 0xfffff856
d001f000:	000095c6 	andeq	r9, r0, r6, asr #11
d001f004:	00009588 	andeq	r9, r0, r8, lsl #11
d001f008:	0000957c 	andeq	r9, r0, ip, ror r5
d001f00c:	0000945a 	andeq	r9, r0, sl, asr r4
d001f010:	fffff6c9 			; <UNDEFINED> instruction: 0xfffff6c9
d001f014:	00009412 	andeq	r9, r0, r2, lsl r4
d001f018:	edb88320 	ldc	3, cr8, [r8, #128]!	; 0x80
d001f01c:	000547a8 	andeq	r4, r5, r8, lsr #15
d001f020:	000093b6 			; <UNDEFINED> instruction: 0x000093b6
d001f024:	fffff62d 			; <UNDEFINED> instruction: 0xfffff62d
d001f028:	000001fa 	strdeq	r0, [r0], -sl
d001f02c:	00009366 	andeq	r9, r0, r6, ror #6
d001f030:	fffff5af 			; <UNDEFINED> instruction: 0xfffff5af
d001f034:	00009316 	andeq	r9, r0, r6, lsl r3
d001f038:	fffff50d 			; <UNDEFINED> instruction: 0xfffff50d

Disassembly of section .text.memset:

d0021610 <.text.memset>:
d0021610:	b2c9b15a 	sbclt	fp, r9, #-2147483626	; 0x80000016
d0021614:	b4104603 	ldrlt	r4, [r0], #-1539	; 0xfffff9fd
d0021618:	461a1884 	ldrmi	r1, [sl], -r4, lsl #17
d002161c:	42a33301 	adcmi	r3, r3, #67108864	; 0x4000000
d0021620:	d1fa7011 	mvnsle	r7, r1, lsl r0
d0021624:	4b04f85d 	blmi	0xd015f7a0
d0021628:	47704770 			; <UNDEFINED> instruction: 0x47704770

Disassembly of section .text.memcpy:

d002162c <.text.memcpy>:
d002162c:	4603b162 	strmi	fp, [r3], -r2, ror #2
d0021630:	1885b430 	stmne	r5, {r4, r5, sl, ip, sp, pc}
d0021634:	461c780a 	ldrmi	r7, [ip], -sl, lsl #16
d0021638:	31013301 	tstcc	r1, r1, lsl #6
d002163c:	42abb2d2 	adcmi	fp, fp, #536870925	; 0x2000000d
d0021640:	d1f77022 	mvnsle	r7, r2, lsr #32
d0021644:	4770bc30 			; <UNDEFINED> instruction: 0x4770bc30
d0021648:	bf004770 	svclt	0x00004770

Disassembly of section .text.memcmp:

d002164c <.text.memcmp>:
d002164c:	46034402 	strmi	r4, [r3], -r2, lsl #8
d0021650:	d0134290 	mulsle	r3, r0, r2
d0021654:	e002b470 	and	fp, r2, r0, ror r4
d0021658:	46034290 			; <UNDEFINED> instruction: 0x46034290
d002165c:	f813d00b 			; <UNDEFINED> instruction: 0xf813d00b
d0021660:	f8115b01 			; <UNDEFINED> instruction: 0xf8115b01
d0021664:	46184b01 	ldrmi	r4, [r8], -r1, lsl #22
d0021668:	42a5b2ee 	adcmi	fp, r5, #-536870898	; 0xe000000e
d002166c:	d0f3b2e3 	rscsle	fp, r3, r3, ror #5
d0021670:	bc701af0 			; <UNDEFINED> instruction: 0xbc701af0
d0021674:	20004770 	andcs	r4, r0, r0, ror r7
d0021678:	4770bc70 			; <UNDEFINED> instruction: 0x4770bc70
d002167c:	47702000 	ldrbmi	r2, [r0, -r0]!

Disassembly of section .text.sb_f_fixed:

d0021680 <.text.sb_f_fixed>:
d0021680:	0b40eeb5 	bleq	0xd105d15c
d0021684:	4ff0e92d 	svcmi	0x00f0e92d
d0021688:	fa10eef1 	blx	0xd045d254
d002168c:	d0354606 	eorsle	r4, r5, r6, lsl #12
d0021690:	6b04eeb2 	blvs	0xd015d160
d0021694:	eeb02400 	cdp	4, 11, cr2, cr0, cr0, {0}
d0021698:	eeb47b40 	vcmp.f64	d7, d0
d002169c:	eef10bc6 	vsqrt.f64	d16, d6
d00216a0:	da22fa10 	ble	0xd08dfee8
d00216a4:	6b00eeb7 	blvs	0xd005d188
d00216a8:	7bc6eeb4 	blvc	0xcf1dd180
d00216ac:	fa10eef1 	blx	0xd045d278
d00216b0:	80a6f140 	adchi	pc, r6, r0, asr #2
d00216b4:	5b04eeb2 	blpl	0xd015d184
d00216b8:	73a1f46f 			; <UNDEFINED> instruction: 0x73a1f46f
d00216bc:	eeb4e004 	cdp	0, 11, cr14, cr4, cr4, {0}
d00216c0:	eef17bc6 	vsqrt.f64	d23, d6
d00216c4:	d504fa10 	strle	pc, [r4, #-2576]	; 0xfffff5f0
d00216c8:	ee273c01 	cdp	12, 2, cr3, cr7, cr1, {0}
d00216cc:	429c7b05 	addsmi	r7, ip, #5120	; 0x1400
d00216d0:	ea24daf5 	b	0xd09582ac
d00216d4:	ea6f73e4 	b	0xd1bfe66c
d00216d8:	459c0c01 	ldrmi	r0, [ip, #3073]	; 0xc01
d00216dc:	2000dd16 	andcs	sp, r0, r6, lsl sp
d00216e0:	8ff0e8bd 	svchi	0x00f0e8bd
d00216e4:	7f9af5b4 	svcvc	0x009af5b4
d00216e8:	ee87d0dc 	mcr	0, 4, sp, cr7, cr12, {6}
d00216ec:	34017b06 	strcc	r7, [r1], #-2822	; 0xfffff4fa
d00216f0:	7bc6eeb4 	blvc	0xcf1dd1c8
d00216f4:	fa10eef1 	blx	0xd045d2c0
d00216f8:	e7d3daf4 			; <UNDEFINED> instruction: 0xe7d3daf4
d00216fc:	eeb02300 	cdp	3, 11, cr2, cr0, cr0, {0}
d0021700:	461c7b40 	ldrmi	r7, [ip], -r0, asr #22
d0021704:	0c01ea6f 			; <UNDEFINED> instruction: 0x0c01ea6f
d0021708:	dce8459c 	cfstr64le	mvdx4, [r8], #624	; 0x270
d002170c:	0b00f04f 	bleq	0xd005d850
d0021710:	5b04eeb2 	blpl	0xd015d1e0
d0021714:	0902ea41 	stmdbeq	r2, {r0, r6, r9, fp, sp, lr, pc}
d0021718:	38fff10c 	ldmcc	pc!, {r2, r3, r8, ip, sp, lr, pc}^	; <UNPREDICTABLE>
d002171c:	43f74658 	mvnsmi	r4, #88, 12	; 0x5800000
d0021720:	0a30f04f 	beq	0xd0c5d864
d0021724:	4b38ed9f 	blmi	0xd0e5cda8
d0021728:	0b40eeb5 	bleq	0xd105d204
d002172c:	fa10eef1 	blx	0xd045d2f8
d0021730:	42a3d030 	adcmi	sp, r3, #48	; 0x30
d0021734:	eefddc2e 	cdp	12, 15, cr13, cr13, cr14, {1}
d0021738:	f10b6bc7 			; <UNDEFINED> instruction: 0xf10b6bc7
d002173c:	ee160b01 	vnmls.f64	d0, d6, d1
d0021740:	ee161a90 	vmov	r1, s13
d0021744:	29092a90 	stmdbcs	r9, {r4, r7, r9, fp, sp}
d0021748:	2209bfa8 	andcs	fp, r9, #168, 30	; 0x2a0
d002174c:	0f11f1bb 	svceq	0x0011f1bb
d0021750:	72e2ea22 	rscvc	lr, r2, #139264	; 0x22000
d0021754:	2a90ee06 	bcs	0xce45cf74
d0021758:	6be6eeb8 	blvs	0xcf9dd240
d002175c:	7b46ee37 	blvc	0xd11dd040
d0021760:	7b05ee27 	blvc	0xd019d004
d0021764:	459cdc16 	ldrmi	sp, [ip, #3094]	; 0xc16
d0021768:	3230d018 	eorscc	sp, r0, #24
d002176c:	5432b2d2 	ldrtpl	fp, [r2], #-722	; 0xfffffd2e
d0021770:	3b013001 	blcc	0xd006d77c
d0021774:	d0b34543 	adcsle	r4, r3, r3, asr #10
d0021778:	d1d51c59 	bicsle	r1, r5, r9, asr ip
d002177c:	0f00f1b9 	svceq	0x0000f1b9
d0021780:	eeb5d0d2 	mrc	0, 5, sp, cr5, cr2, {6}
d0021784:	f04f0b40 			; <UNDEFINED> instruction: 0xf04f0b40
d0021788:	5432022e 	ldrtpl	r0, [r2], #-558	; 0xfffffdd2
d002178c:	eef13001 	cdp	0, 15, cr3, cr1, cr1, {0}
d0021790:	d1cefa10 	bicle	pc, lr, r0, lsl sl	; <UNPREDICTABLE>
d0021794:	d0ec459c 	smlalle	r4, ip, ip, r5
d0021798:	e7e82230 			; <UNDEFINED> instruction: 0xe7e82230
d002179c:	dd1e2905 	vldrle.16	s4, [lr, #-10]	; <UNPREDICTABLE>
d00217a0:	dd172800 	ldcle	8, cr2, [r7, #-0]
d00217a4:	0e00eb06 	vmlaeq.f64	d14, d0, d6
d00217a8:	f8124672 			; <UNDEFINED> instruction: 0xf8124672
d00217ac:	292e1d01 	stmdbcs	lr!, {r0, r8, sl, fp, ip}
d00217b0:	0502eb07 	streq	lr, [r2, #-2823]	; 0xfffff4f9
d00217b4:	2938d003 	ldmdbcs	r8!, {r0, r1, ip, lr, pc}
d00217b8:	f882d91f 			; <UNDEFINED> instruction: 0xf882d91f
d00217bc:	3501a000 	strcc	sl, [r1, #-0]
d00217c0:	2800d1f3 	stmdacs	r0, {r0, r1, r4, r5, r6, r7, r8, ip, lr, pc}
d00217c4:	4672dd06 	ldrbtmi	sp, [r2], -r6, lsl #26
d00217c8:	1c01f812 	stcne	8, cr15, [r1], {18}
d00217cc:	1901f802 	stmdbne	r1, {r1, fp, ip, sp, lr, pc}
d00217d0:	d1f94296 			; <UNDEFINED> instruction: 0xd1f94296
d00217d4:	0231f04f 	eorseq	pc, r1, #79	; 0x4f
d00217d8:	70323001 	eorsvc	r3, r2, r1
d00217dc:	d1c8e7c9 	bicle	lr, r8, r9, asr #15
d00217e0:	7bc4eeb4 	blvc	0xcf15d2b8
d00217e4:	fa10eef1 	blx	0xd045d3b0
d00217e8:	2800dcda 	stmdacs	r0, {r1, r3, r4, r6, r7, sl, fp, ip, lr, pc}
d00217ec:	1832d0c1 	ldmdane	r2!, {r0, r6, r7, ip, lr, pc}
d00217f0:	2c01f812 	stccs	8, cr15, [r1], {18}
d00217f4:	d5bc07d2 	ldrle	r0, [ip, #2002]!	; 0x7d2
d00217f8:	3101e7d2 	ldrdcc	lr, [r1, -r2]
d00217fc:	e7b87011 			; <UNDEFINED> instruction: 0xe7b87011
d0021800:	e77f4623 	ldrb	r4, [pc, -r3, lsr #12]!
d0021804:	8000f3af 	andhi	pc, r0, pc, lsr #7
d0021808:	812dea11 			; <UNDEFINED> instruction: 0x812dea11
d002180c:	3d719799 	ldclcc	7, cr9, [r1, #-612]!	; 0xfffffd9c

Disassembly of section .text.sb_f_exponent:

d0021810 <.text.sb_f_exponent>:
d0021810:	0b40eeb5 	bleq	0xd105d2ec
d0021814:	4ff0e92d 	svcmi	0x00f0e92d
d0021818:	fa10eef1 	blx	0xd045d3e4
d002181c:	d0344607 	eorsle	r4, r4, r7, lsl #12
d0021820:	6b04eeb2 	blvs	0xd015d2f0
d0021824:	0bc6eeb4 	bleq	0xcf1dd2fc
d0021828:	fa10eef1 	blx	0xd045d3f4
d002182c:	80cef2c0 	sbchi	pc, lr, r0, asr #5
d0021830:	7b40eeb0 	blvc	0xd105d2f8
d0021834:	e0022400 	and	r2, r2, r0, lsl #8
d0021838:	7f9af5b4 	svcvc	0x009af5b4
d002183c:	ee87d007 	cdp	0, 8, cr13, cr7, cr7, {0}
d0021840:	34017b06 	strcc	r7, [r1], #-2822	; 0xfffff4fa
d0021844:	7bc6eeb4 	blvc	0xcf1dd31c
d0021848:	fa10eef1 	blx	0xd045d414
d002184c:	eeb7daf4 			; <UNDEFINED> instruction: 0xeeb7daf4
d0021850:	eeb46b00 	vmov.f64	d6, #64	; 0x3e000000  0.125
d0021854:	eef17bc6 	vsqrt.f64	d23, d6
d0021858:	d519fa10 	ldrle	pc, [r9, #-2576]	; 0xfffff5f0
d002185c:	5b04eeb2 	blpl	0xd015d32c
d0021860:	70a1f46f 	adcvc	pc, r1, pc, ror #8
d0021864:	eeb4e004 	cdp	0, 11, cr14, cr4, cr4, {0}
d0021868:	eef17bc6 	vsqrt.f64	d23, d6
d002186c:	d50ffa10 	strle	pc, [pc, #-2576]	; 0xd0020e64
d0021870:	ee273c01 	cdp	12, 2, cr3, cr7, cr1, {0}
d0021874:	42847b05 	addmi	r7, r4, #5120	; 0x1400
d0021878:	f111daf5 			; <UNDEFINED> instruction: 0xf111daf5
d002187c:	d50a0e01 	strle	r0, [sl, #-3585]	; 0xfffff1ff
d0021880:	2102463e 	tstcs	r2, lr, lsr r6
d0021884:	22002501 	andcs	r2, r0, #4194304	; 0x400000
d0021888:	eeb0e062 	cdp	0, 11, cr14, cr0, cr2, {3}
d002188c:	24007b40 	strcs	r7, [r0], #-2880	; 0xfffff4c0
d0021890:	0e01f111 	mcreq	1, 0, pc, cr1, cr1, {0}	; <UNPREDICTABLE>
d0021894:	2500d4f4 	strcs	sp, [r0, #-1268]	; 0xfffffb0c
d0021898:	5b04eeb2 	blpl	0xd015d368
d002189c:	0902ea41 	stmdbeq	r2, {r0, r6, r9, fp, sp, lr, pc}
d00218a0:	462a1c88 	strtmi	r1, [sl], -r8, lsl #25
d00218a4:	0807ea6f 	stmdaeq	r7, {r0, r1, r2, r3, r5, r6, r9, fp, sp, lr, pc}
d00218a8:	0a30f04f 	beq	0xd0c5d9ec
d00218ac:	0b2ef04f 	bleq	0xd0bdd9f0
d00218b0:	4b49ed9f 	blmi	0xd129cf34
d00218b4:	0b40eeb5 	bleq	0xd105d390
d00218b8:	fa10eef1 	blx	0xd045d484
d00218bc:	4575d114 	ldrbmi	sp, [r5, #-276]!	; 0xfffffeec
d00218c0:	2130d002 	teqcs	r0, r2
d00218c4:	320154b9 	andcc	r5, r1, #-1191182336	; 0xb9000000
d00218c8:	42853501 	addmi	r3, r5, #4194304	; 0x400000
d00218cc:	2d01d03d 	stccs	0, cr13, [r1, #-244]	; 0xffffff0c
d00218d0:	f1b9d1f0 			; <UNDEFINED> instruction: 0xf1b9d1f0
d00218d4:	d0ed0f00 	rscle	r0, sp, r0, lsl #30
d00218d8:	0b40eeb5 	bleq	0xd105d3b4
d00218dc:	b002f807 	andlt	pc, r2, r7, lsl #16
d00218e0:	eef13201 	cdp	2, 15, cr3, cr1, cr1, {0}
d00218e4:	d0eafa10 	rscle	pc, sl, r0, lsl sl	; <UNPREDICTABLE>
d00218e8:	6bc7eefd 	blvs	0xcf21d4e4
d00218ec:	6a90ee16 	bvs	0xce45d14c
d00218f0:	1a90ee16 	bne	0xce45d150
d00218f4:	bfa82e09 	svclt	0x00a82e09
d00218f8:	45752109 	ldrbmi	r2, [r5, #-265]!	; 0xfffffef7
d00218fc:	71e1ea21 	mvnvc	lr, r1, lsr #20
d0021900:	1a90ee06 	bne	0xce45d120
d0021904:	6be6eeb8 	blvs	0xcf9dd3ec
d0021908:	7b46ee37 	blvc	0xd11dd1ec
d002190c:	7b05ee27 	blvc	0xd019d1b0
d0021910:	3130d002 	teqcc	r0, r2
d0021914:	e7d5b2c9 	ldrb	fp, [r5, r9, asr #5]
d0021918:	dd462e05 	stclle	14, cr2, [r6, #-20]	; 0xffffffec
d002191c:	dd0d2a00 	vstrle	s4, [sp, #-0]
d0021920:	f81118b9 			; <UNDEFINED> instruction: 0xf81118b9
d0021924:	2e2e6d01 	cdpcs	13, 2, cr6, cr14, cr1, {0}
d0021928:	0c01eb08 			; <UNDEFINED> instruction: 0x0c01eb08
d002192c:	2e38d003 	cdpcs	0, 3, cr13, cr8, cr3, {0}
d0021930:	f881d949 			; <UNDEFINED> instruction: 0xf881d949
d0021934:	f1bca000 			; <UNDEFINED> instruction: 0xf1bca000
d0021938:	d1f23fff 	ldrshle	r3, [r2, #255]!	; 0xff
d002193c:	f04f3501 			; <UNDEFINED> instruction: 0xf04f3501
d0021940:	34010131 	strcc	r0, [r1], #-305	; 0xfffffecf
d0021944:	70394285 	eorsvc	r4, r9, r5, lsl #5
d0021948:	18bed1c1 	ldmne	lr!, {r0, r6, r7, r8, ip, lr, pc}
d002194c:	1c911c55 	ldcne	12, cr1, [r1], {85}	; 0x55
d0021950:	bf142b00 	svclt	0x00142b00
d0021954:	20652045 	rsbcs	r2, r5, r5, asr #32
d0021958:	70302c00 	eorsvc	r2, r0, r0, lsl #24
d002195c:	232dbfb4 			; <UNDEFINED> instruction: 0x232dbfb4
d0021960:	2c00232b 	stccs	3, cr2, [r0], {43}	; 0x2b
d0021964:	bfb8557b 	svclt	0x00b8557b
d0021968:	2c634264 	sfmcs	f4, 2, [r3], #-400	; 0xfffffe70
d002196c:	4b1cdd06 	blmi	0xd0758d8c
d0021970:	0304fba3 	movweq	pc, #19363	; 0x4ba3	; <UNPREDICTABLE>
d0021974:	3330095b 	teqcc	r0, #1490944	; 0x16c000
d0021978:	1cd1547b 	cfldrdne	mvd5, [r1], {123}	; 0x7b
d002197c:	187d4a19 	ldmdane	sp!, {r0, r3, r4, r9, fp, lr}^
d0021980:	0304fba2 	movweq	pc, #19362	; 0x4ba2	; <UNPREDICTABLE>
d0021984:	08db1c88 	ldmeq	fp, {r3, r7, sl, fp, ip}^
d0021988:	6203fba2 	andvs	pc, r3, #165888	; 0x28800
d002198c:	0683eb03 	streq	lr, [r3], r3, lsl #22
d0021990:	eba408d2 	bl	0xce923ce0
d0021994:	eb020446 	bl	0xd00a2ab4
d0021998:	34300282 	ldrtcc	r0, [r0], #-642	; 0xfffffd7e
d002199c:	0342eba3 	movteq	lr, #11171	; 0x2ba3
d00219a0:	547b3330 	ldrbtpl	r3, [fp], #-816	; 0xfffffcd0
d00219a4:	e8bd706c 	pop	{r2, r3, r5, r6, ip, sp, lr}
d00219a8:	d18d8ff0 	strdle	r8, [sp, r0]
d00219ac:	7bc4eeb4 	blvc	0xcf15d484
d00219b0:	fa10eef1 	blx	0xd045d57c
d00219b4:	2a00dcb2 	bcs	0xd0058c84
d00219b8:	18b9d086 	ldmne	r9!, {r1, r2, r7, ip, lr, pc}
d00219bc:	1c01f811 	stcne	8, cr15, [r1], {17}
d00219c0:	d58107c9 	strle	r0, [r1, #1993]	; 0x7c9
d00219c4:	3601e7aa 	strcc	lr, [r1], -sl, lsr #15
d00219c8:	e77d700e 	ldrb	r7, [sp, -lr]!
d00219cc:	7b40eeb0 	blvc	0xd105d494
d00219d0:	e73c2400 	ldr	r2, [ip, -r0, lsl #8]!
d00219d4:	8000f3af 	andhi	pc, r0, pc, lsr #7
d00219d8:	812dea11 			; <UNDEFINED> instruction: 0x812dea11
d00219dc:	3d719799 	ldclcc	7, cr9, [r1, #-612]!	; 0xfffffd9c
d00219e0:	51eb851f 	mvnpl	r8, pc, lsl r5
d00219e4:	cccccccd 	stclgt	12, cr12, [ip], {205}	; 0xcd

Disassembly of section .text.sb_flush.part.0:

d00219e8 <.text.sb_flush.part.0>:
d00219e8:	2090f8d0 			; <UNDEFINED> instruction: 0x2090f8d0
d00219ec:	4b07b16a 	blmi	0xd020df9c
d00219f0:	0110f100 	tsteq	r0, r0, lsl #2	; <UNPREDICTABLE>
d00219f4:	681b689b 	ldmdavs	fp, {r0, r1, r3, r4, r7, fp, sp, lr}
d00219f8:	685bb510 	ldmdavs	fp, {r4, r8, sl, ip, sp, pc}^
d00219fc:	20004604 	andcs	r4, r0, r4, lsl #12
d0021a00:	23004798 	movwcs	r4, #1944	; 0x798
d0021a04:	3090f8c4 	addscc	pc, r0, r4, asr #17
d0021a08:	4770bd10 			; <UNDEFINED> instruction: 0x4770bd10
d0021a0c:	2001f000 	andcs	pc, r1, r0

Disassembly of section .text.sb_char:

d0021a10 <.text.sb_char>:
d0021a10:	b51068c3 	ldrlt	r6, [r0, #-2243]	; 0xfffff73d
d0021a14:	b1834604 	orrlt	r4, r3, r4, lsl #12
d0021a18:	3090f8d0 			; <UNDEFINED> instruction: 0x3090f8d0
d0021a1c:	44031c5a 	strmi	r1, [r3], #-3162	; 0xfffff3a6
d0021a20:	f8c02a80 			; <UNDEFINED> instruction: 0xf8c02a80
d0021a24:	74192090 	ldrvc	r2, [r9], #-144	; 0xffffff70
d0021a28:	68a3d013 	stmiavs	r3!, {r0, r1, r4, ip, lr, pc}
d0021a2c:	4200f06f 	andmi	pc, r0, #111	; 0x6f
d0021a30:	d2014293 	andle	r4, r1, #805306377	; 0x30000009
d0021a34:	60a33301 	adcvs	r3, r3, r1, lsl #6
d0021a38:	6800bd10 	stmdavs	r0, {r4, r8, sl, fp, ip, sp, pc}
d0021a3c:	d0f42800 	rscsle	r2, r4, r0, lsl #16
d0021a40:	68a36862 	stmiavs	r3!, {r1, r5, r6, fp, sp, lr}
d0021a44:	bf182a00 	svclt	0x00182a00
d0021a48:	42933a01 	addsmi	r3, r3, #4096	; 0x1000
d0021a4c:	54c1d2ee 	strbpl	sp, [r1], #750	; 0x2ee
d0021a50:	f7ffe7eb 			; <UNDEFINED> instruction: 0xf7ffe7eb
d0021a54:	68a3ffc9 	stmiavs	r3!, {r0, r3, r6, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0021a58:	bf00e7e8 	svclt	0x0000e7e8

Disassembly of section .text.sb_number:

d0021a70 <.text.sb_number>:
d0021a70:	4ff0e92d 	svcmi	0x00f0e92d
d0021a74:	8b02ed2d 	blhi	0xd00dcf30
d0021a78:	ee08b09b 	mcr	0, 0, fp, cr8, cr11, {4}
d0021a7c:	93070a10 	movwls	r0, #31248	; 0x7a10
d0021a80:	92069b2b 	andls	r9, r6, #44032	; 0xac00
d0021a84:	d13e2b00 	teqle	lr, r0, lsl #22
d0021a88:	e9dd4bbf 	ldmib	sp, {r0, r1, r2, r3, r4, r5, r7, r8, r9, fp, lr}^
d0021a8c:	447b1206 	ldrbtmi	r1, [fp], #-518	; 0xfffffdfa
d0021a90:	460b9305 	strmi	r9, [fp], -r5, lsl #6
d0021a94:	d13e4313 	teqle	lr, r3, lsl r3
d0021a98:	9a2a9b2a 	bls	0xd0ac8748
d0021a9c:	bf183b00 	svclt	0x00183b00
d0021aa0:	2a002301 	bcs	0xd002a6ac
d0021aa4:	9303d137 	movwls	sp, #12599	; 0x3137
d0021aa8:	2b009b27 	blcs	0xd004874c
d0021aac:	9b28d179 	blls	0xd0a56098
d0021ab0:	f1000759 			; <UNDEFINED> instruction: 0xf1000759
d0021ab4:	ea4f8101 	b	0xd1401ec0
d0021ab8:	9a2c0983 	bls	0xd0b240cc
d0021abc:	1a40f3c9 	bne	0xd105e9e8
d0021ac0:	0920f009 	stmdbeq	r0!, {r0, r3, ip, sp, lr, pc}
d0021ac4:	2a004653 	bcs	0xd0033418
d0021ac8:	9a26d072 	bls	0xd09d5c98
d0021acc:	f0002a10 			; <UNDEFINED> instruction: 0xf0002a10
d0021ad0:	9a2680f8 	bls	0xd09c1eb8
d0021ad4:	f0002a02 			; <UNDEFINED> instruction: 0xf0002a02
d0021ad8:	9a268144 	bls	0xd09c1ff0
d0021adc:	9a032a08 	bls	0xd00ec304
d0021ae0:	8122f000 	msrhi	CPSR_x, r0
d0021ae4:	2600992a 	strcs	r9, [r0], -sl, lsr #18
d0021ae8:	82a0f8df 	adchi	pc, r0, #14614528	; 0xdf0000
d0021aec:	44f84291 	ldrbtmi	r4, [r8], #657	; 0x291
d0021af0:	9a03dc69 	bls	0xd0118c9c
d0021af4:	19942700 	ldmibne	r4, {r8, r9, sl, sp}
d0021af8:	44239a29 	strtmi	r9, [r3], #-2601	; 0xfffff5d7
d0021afc:	f0c04293 			; <UNDEFINED> instruction: 0xf0c04293
d0021b00:	463c80e8 	ldrtmi	r8, [ip], -r8, ror #1
d0021b04:	4ba2e0e7 	blmi	0xce8d9ea8
d0021b08:	1206e9dd 	andne	lr, r6, #3620864	; 0x374000
d0021b0c:	9305447b 	movwls	r4, #21627	; 0x547b
d0021b10:	4313460b 	tstmi	r3, #11534336	; 0xb00000
d0021b14:	ab09d0c0 	blge	0xd0295e1c
d0021b18:	26012200 	strcs	r2, [r1], -r0, lsl #4
d0021b1c:	e9dd9304 	ldmib	sp, {r2, r8, r9, ip, pc}^
d0021b20:	469b3406 	ldrmi	r3, [fp], r6, lsl #8
d0021b24:	46272300 	strtmi	r2, [r7], -r0, lsl #6
d0021b28:	9b269303 	blls	0xd09c673c
d0021b2c:	e9cd4619 	stmib	sp, {r0, r3, r4, r9, sl, lr}^
d0021b30:	23001200 	movwcs	r1, #512	; 0x200
d0021b34:	0ffa203f 	svceq	0x00fa203f
d0021b38:	b008f8cd 	andlt	pc, r8, sp, asr #17
d0021b3c:	469a4699 			; <UNDEFINED> instruction: 0x469a4699
d0021b40:	99023801 	stmdbls	r2, {r0, fp, ip, sp}
d0021b44:	0420f1c0 	strteq	pc, [r0], #-448	; 0xfffffe40
d0021b48:	0520f1a0 	streq	pc, [r0, #-416]!	; 0xfffffe60
d0021b4c:	f1b040c1 			; <UNDEFINED> instruction: 0xf1b040c1
d0021b50:	fa073fff 	blx	0xd01f1b54
d0021b54:	fa27fe04 	blx	0xd0a2136c
d0021b58:	fa26fc05 	blx	0xd09e0b74
d0021b5c:	fa06f404 	blx	0xd01deb74
d0021b60:	ea41f505 	b	0xd109ef7c
d0021b64:	fa06010e 	blx	0xd01a1fa4
d0021b68:	ea44f800 	b	0xd115fb70
d0021b6c:	ea410405 	b	0xd1062b88
d0021b70:	d072010c 	rsbsle	r0, r2, ip, lsl #2
d0021b74:	f0011895 			; <UNDEFINED> instruction: 0xf0011895
d0021b78:	eb430101 	bl	0xd10e1f84
d0021b7c:	ea410c03 	b	0xd1064b90
d0021b80:	46630205 	strbtmi	r0, [r3], -r5, lsl #4
d0021b84:	bc00e9dd 			; <UNDEFINED> instruction: 0xbc00e9dd
d0021b88:	bf084563 	svclt	0x00084563
d0021b8c:	d3d7455a 	bicsle	r4, r7, #377487360	; 0x16800000
d0021b90:	020bebb2 	andeq	lr, fp, #182272	; 0x2c800
d0021b94:	0909ea48 	stmdbeq	r9, {r3, r6, r9, fp, sp, lr, pc}
d0021b98:	0a0aea44 	beq	0xd02dc4b0
d0021b9c:	030ceb63 	movweq	lr, #52067	; 0xcb63
d0021ba0:	2301e7ce 	movwcs	lr, #6094	; 0x17ce
d0021ba4:	092df04f 	pusheq	{r0, r1, r2, r3, r6, ip, sp, lr, pc}
d0021ba8:	9a2c469a 	bls	0xd0b33618
d0021bac:	d18c2a00 	orrle	r2, ip, r0, lsl #20
d0021bb0:	f0129a28 			; <UNDEFINED> instruction: 0xf0129a28
d0021bb4:	d16a0610 	cmnle	sl, r0, lsl r6
d0021bb8:	81d8f8df 	ldrsbhi	pc, [r8, #143]	; 0x8f	; <UNPREDICTABLE>
d0021bbc:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d0021bc0:	4291992a 	addsmi	r9, r1, #688128	; 0xa8000
d0021bc4:	9903dd95 	stmdbls	r3, {r0, r2, r4, r7, r8, sl, fp, ip, lr, pc}
d0021bc8:	198a982a 	stmibne	sl, {r1, r3, r5, fp, ip, pc}
d0021bcc:	44131a47 	ldrmi	r1, [r3], #-2631	; 0xfffff5b9
d0021bd0:	443b9a29 	ldrtmi	r9, [fp], #-2601	; 0xfffff5d7
d0021bd4:	d87c429a 	ldmdale	ip!, {r1, r3, r4, r7, r9, lr}^
d0021bd8:	24009b28 	strcs	r9, [r0], #-2856	; 0xfffff4d8
d0021bdc:	0501f003 	streq	pc, [r1, #-3]
d0021be0:	0f00f1ba 	svceq	0x0000f1ba
d0021be4:	b16ed14d 	cmnlt	lr, sp, asr #2
d0021be8:	1000f898 	mulne	r0, r8, r8
d0021bec:	0a10ee18 	beq	0xd045d454
d0021bf0:	ff0ef7ff 			; <UNDEFINED> instruction: 0xff0ef7ff
d0021bf4:	d1052e02 	tstle	r5, r2, lsl #28
d0021bf8:	1001f898 	mulne	r1, r8, r8
d0021bfc:	0a10ee18 	beq	0xd045d464
d0021c00:	ff06f7ff 			; <UNDEFINED> instruction: 0xff06f7ff
d0021c04:	b1471e7e 	hvclt	29166	; 0x71ee
d0021c08:	7a10ee18 	bvc	0xd045d470
d0021c0c:	21303e01 	teqcs	r0, r1, lsl #28
d0021c10:	f7ff4638 			; <UNDEFINED> instruction: 0xf7ff4638
d0021c14:	1c72fefd 	ldclne	14, cr15, [r2], #-1012	; 0xfffffc0c
d0021c18:	9b03d1f8 	blls	0xd0116400
d0021c1c:	af09b163 	svcge	0x0009b163
d0021c20:	ee189b03 	vnmls.f64	d9, d8, d3
d0021c24:	443b8a10 	ldrtmi	r8, [fp], #-2576	; 0xfffff5f0
d0021c28:	f816461e 			; <UNDEFINED> instruction: 0xf816461e
d0021c2c:	46401d01 	strbmi	r1, [r0], -r1, lsl #26
d0021c30:	feeef7ff 	mcr2	7, 7, pc, cr14, cr15, {7}	; <UNPREDICTABLE>
d0021c34:	d1f842b7 	ldrhle	r4, [r8, #39]!	; 0x27
d0021c38:	1e65b155 	mcrne	1, 3, fp, cr5, cr5, {2}
d0021c3c:	ee18b144 	mnfem	f3, f4
d0021c40:	3d014a10 	vstrcc	s8, [r1, #-64]	; 0xffffffc0
d0021c44:	46202120 	strtmi	r2, [r0], -r0, lsr #2
d0021c48:	fee2f7ff 	mcr2	7, 7, pc, cr2, cr15, {7}	; <UNPREDICTABLE>
d0021c4c:	d1f81c6b 	mvnsle	r1, fp, ror #24
d0021c50:	ecbdb01b 	ldc	0, cr11, [sp], #108	; 0x6c
d0021c54:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d0021c58:	99058ff0 	stmdbls	r5, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
d0021c5c:	9903440a 	stmdbls	r3, {r1, r3, sl, lr}
d0021c60:	31017813 	tstcc	r1, r3, lsl r8
d0021c64:	91039a04 	tstls	r3, r4, lsl #20
d0021c68:	3b01f802 	blcc	0xd009fc78
d0021c6c:	030aea59 	movweq	lr, #43609	; 0xaa59
d0021c70:	f43f9204 			; <UNDEFINED> instruction: 0xf43f9204
d0021c74:	2940af19 	stmdbcs	r0, {r0, r3, r4, r8, r9, sl, fp, sp, pc}^
d0021c78:	af16f63f 	svcge	0x0016f63f
d0021c7c:	465746cb 	ldrbmi	r4, [r7], -fp, asr #13
d0021c80:	4649e757 			; <UNDEFINED> instruction: 0x4649e757
d0021c84:	0a10ee18 	beq	0xd045d4ec
d0021c88:	fec2f7ff 	mcr2	7, 6, pc, cr2, cr15, {7}	; <UNPREDICTABLE>
d0021c8c:	e9dde7ab 	ldmib	sp, {r0, r1, r3, r5, r7, r8, r9, sl, sp, lr, pc}^
d0021c90:	430a1206 	movwmi	r1, #41478	; 0xa206
d0021c94:	af19f47f 	svcge	0x0019f47f
d0021c98:	2a089a26 	bcs	0xd0248538
d0021c9c:	9a03d167 	bls	0xd0116240
d0021ca0:	d1642a00 	cmnle	r4, r0, lsl #20
d0021ca4:	21302201 	teqcs	r0, r1, lsl #4
d0021ca8:	80ecf8df 	ldrdhi	pc, [ip], #143	; 0x8f	; <UNPREDICTABLE>
d0021cac:	44f89e2c 	ldrbtmi	r9, [r8], #3628	; 0xe2c
d0021cb0:	f88d9203 			; <UNDEFINED> instruction: 0xf88d9203
d0021cb4:	e7831024 	str	r1, [r3, r4, lsr #32]
d0021cb8:	f04f2301 			; <UNDEFINED> instruction: 0xf04f2301
d0021cbc:	469a092b 	ldrmi	r0, [sl], fp, lsr #18
d0021cc0:	9a2be773 	bls	0xd0b1ba94
d0021cc4:	f8dfb352 			; <UNDEFINED> instruction: 0xf8dfb352
d0021cc8:	260280d4 			; <UNDEFINED> instruction: 0x260280d4
d0021ccc:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d0021cd0:	9a29e776 	bls	0xd0a9bab0
d0021cd4:	9b281ad4 	blls	0xd0a2882c
d0021cd8:	0303f003 	movweq	pc, #12291	; 0x3003	; <UNPREDICTABLE>
d0021cdc:	d1022b02 	tstle	r2, r2, lsl #22
d0021ce0:	2b009b2a 	blcs	0xd0048990
d0021ce4:	9b28db33 	blls	0xd0a589b8
d0021ce8:	0501f013 	streq	pc, [r1, #-19]	; 0xffffffed
d0021cec:	af78f47f 	svcge	0x0078f47f
d0021cf0:	3bfff104 	blcc	0xd001e108
d0021cf4:	d0402c00 	suble	r2, r0, r0, lsl #24
d0021cf8:	ee189402 	cfmuls	mvf9, mvf8, mvf2
d0021cfc:	f10b4a10 			; <UNDEFINED> instruction: 0xf10b4a10
d0021d00:	21203bff 	strdcs	r3, [r0, -pc]!
d0021d04:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0021d08:	f1bbfe83 			; <UNDEFINED> instruction: 0xf1bbfe83
d0021d0c:	d1f63fff 	ldrshle	r3, [r6, #255]!	; 0xff
d0021d10:	f1ba9c02 			; <UNDEFINED> instruction: 0xf1ba9c02
d0021d14:	f43f0f00 			; <UNDEFINED> instruction: 0xf43f0f00
d0021d18:	e7b2af66 	ldr	sl, [r2, r6, ror #30]!
d0021d1c:	8080f8df 	ldrdhi	pc, [r0], pc	; <UNPREDICTABLE>
d0021d20:	9a032602 	bls	0xd00eb530
d0021d24:	e74b44f8 			; <UNDEFINED> instruction: 0xe74b44f8
d0021d28:	a91ab15a 	ldmdbge	sl, {r1, r3, r4, r6, r8, ip, sp, pc}
d0021d2c:	f812188a 			; <UNDEFINED> instruction: 0xf812188a
d0021d30:	2a302c45 	bcs	0xd0c2ce4c
d0021d34:	f8dfd105 			; <UNDEFINED> instruction: 0xf8dfd105
d0021d38:	2600806c 	strcs	r8, [r0], -ip, rrx
d0021d3c:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d0021d40:	f8dfe73e 			; <UNDEFINED> instruction: 0xf8dfe73e
d0021d44:	26018064 	strcs	r8, [r1], -r4, rrx
d0021d48:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d0021d4c:	9b28e738 	blls	0xd0a5ba34
d0021d50:	24004427 	strcs	r4, [r0], #-1063	; 0xfffffbd9
d0021d54:	0501f003 	streq	pc, [r1, #-3]
d0021d58:	0f00f1ba 	svceq	0x0000f1ba
d0021d5c:	af43f43f 	svcge	0x0043f43f
d0021d60:	f8dfe78f 			; <UNDEFINED> instruction: 0xf8dfe78f
d0021d64:	46168048 	ldrmi	r8, [r6], -r8, asr #32
d0021d68:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d0021d6c:	f8dfe728 			; <UNDEFINED> instruction: 0xf8dfe728
d0021d70:	26008040 	strcs	r8, [r0], -r0, asr #32
d0021d74:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d0021d78:	4625e722 	strtmi	lr, [r5], -r2, lsr #14
d0021d7c:	0f00f1ba 	svceq	0x0000f1ba
d0021d80:	af31f43f 	svcge	0x0031f43f
d0021d84:	bf00e77d 	svclt	0x0000e77d
d0021d88:	0000136a 	andeq	r1, r0, sl, ror #6
d0021d8c:	ffffff6e 			; <UNDEFINED> instruction: 0xffffff6e
d0021d90:	000012d8 	ldrdeq	r1, [r0], -r8
d0021d94:	fffffe9e 			; <UNDEFINED> instruction: 0xfffffe9e
d0021d98:	fffffdae 			; <UNDEFINED> instruction: 0xfffffdae
d0021d9c:	fffffd8a 			; <UNDEFINED> instruction: 0xfffffd8a
d0021da0:	fffffd3c 			; <UNDEFINED> instruction: 0xfffffd3c
d0021da4:	fffffd1e 			; <UNDEFINED> instruction: 0xfffffd1e
d0021da8:	fffffd1a 			; <UNDEFINED> instruction: 0xfffffd1a
d0021dac:	fffffcfe 			; <UNDEFINED> instruction: 0xfffffcfe
d0021db0:	fffffce6 			; <UNDEFINED> instruction: 0xfffffce6

Disassembly of section .text.sb_float:

d0021dcc <.text.sb_float>:
d0021dcc:	4ff0e92d 	svcmi	0x00f0e92d
d0021dd0:	bb10ec5c 	bllt	0xd045cf48
d0021dd4:	461eb0df 			; <UNDEFINED> instruction: 0x461eb0df
d0021dd8:	73dcea5f 	bicsvc	lr, ip, #389120	; 0x5f000
d0021ddc:	460446e0 	strmi	r4, [r4], -r0, ror #13
d0021de0:	4615468a 	ldrmi	r4, [r5], -sl, lsl #13
d0021de4:	9a10ee10 	bls	0xd045d62c
d0021de8:	ed8d9304 	stc	3, cr9, [sp, #16]
d0021dec:	d10a0b00 	tstle	sl, r0, lsl #22
d0021df0:	f1000750 			; <UNDEFINED> instruction: 0xf1000750
d0021df4:	009380cb 	addseq	r8, r3, fp, asr #1
d0021df8:	1740f3c3 	strbne	pc, [r0, -r3, asr #7]	; <UNPREDICTABLE>
d0021dfc:	0320f003 	wfieq
d0021e00:	930346bb 	movwls	r4, #14011	; 0x36bb
d0021e04:	2701e003 	strcs	lr, [r1, -r3]
d0021e08:	46bb232d 	ldrtmi	r2, [fp], sp, lsr #6
d0021e0c:	f04f9303 			; <UNDEFINED> instruction: 0xf04f9303
d0021e10:	21000c00 	tstcs	r0, r0, lsl #24
d0021e14:	70fff240 	rscsvc	pc, pc, r0, asr #4
d0021e18:	520af3c8 	andpl	pc, sl, #200, 6	; 0x20000003
d0021e1c:	f1aa458c 			; <UNDEFINED> instruction: 0xf1aa458c
d0021e20:	bf080e41 	svclt	0x00080e41
d0021e24:	fa5f4282 	blx	0xd17f2834
d0021e28:	d03efe8e 	eorsle	pc, lr, lr, lsl #29
d0021e2c:	2b099b68 	blcs	0xd0288bd4
d0021e30:	4afcdd4b 	bmi	0xcff59364
d0021e34:	0918f10d 	ldmdbeq	r8, {r0, r2, r3, r8, ip, sp, lr, pc}
d0021e38:	237046e0 	cmncs	r0, #224, 12	; 0xe000000
d0021e3c:	4649447a 			; <UNDEFINED> instruction: 0x4649447a
d0021e40:	3201203c 	andcc	r2, r1, #60	; 0x3c
d0021e44:	4618e002 	ldrmi	lr, [r8], -r2
d0021e48:	3f01f812 	svccc	0x0001f812
d0021e4c:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d0021e50:	0b01f801 	bleq	0xd009fe5c
d0021e54:	d1f62b00 	mvnsle	r2, r0, lsl #22
d0021e58:	020beb08 	andeq	lr, fp, #8, 22	; 0x2000
d0021e5c:	42b22301 	adcsmi	r2, r2, #67108864	; 0x4000000
d0021e60:	8099f0c0 	addshi	pc, r9, r0, asr #1
d0021e64:	f0052600 			; <UNDEFINED> instruction: 0xf0052600
d0021e68:	2a020203 	bcs	0xd00a267c
d0021e6c:	2b00d102 	blcs	0xd005627c
d0021e70:	8093f040 	addshi	pc, r3, r0, asr #32
d0021e74:	0501f015 	streq	pc, [r1, #-21]	; 0xffffffeb
d0021e78:	80bcf040 	adcshi	pc, ip, r0, asr #32
d0021e7c:	b1361e75 	teqlt	r6, r5, ror lr
d0021e80:	21203d01 			; <UNDEFINED> instruction: 0x21203d01
d0021e84:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0021e88:	1c69fdc3 	stclne	13, cr15, [r9], #-780	; 0xfffffcf4
d0021e8c:	2f00d1f8 	svccs	0x0000d1f8
d0021e90:	8091f000 	addshi	pc, r1, r0
d0021e94:	46209903 	strtmi	r9, [r0], -r3, lsl #18
d0021e98:	fdbaf7ff 	ldc2	7, cr15, [sl, #1020]!	; 0x3fc
d0021e9c:	0f00f1b8 	svceq	0x0000f1b8
d0021ea0:	808df040 	addhi	pc, sp, r0, asr #32
d0021ea4:	e8bdb05f 	pop	{r0, r1, r2, r3, r4, r6, ip, sp, pc}
d0021ea8:	464a8ff0 			; <UNDEFINED> instruction: 0x464a8ff0
d0021eac:	0313f3c8 	tsteq	r3, #200, 6	; 0x20000003	; <UNPREDICTABLE>
d0021eb0:	f0404313 			; <UNDEFINED> instruction: 0xf0404313
d0021eb4:	f1be80ae 			; <UNDEFINED> instruction: 0xf1be80ae
d0021eb8:	f2000f19 	vrecps.f32	d0, d0, d9
d0021ebc:	f8df80d4 			; <UNDEFINED> instruction: 0xf8df80d4
d0021ec0:	234ec368 	movtcs	ip, #58216	; 0xe368
d0021ec4:	44fc2149 	ldrbtmi	r2, [ip], #329	; 0x149
d0021ec8:	9b04e0ab 	blls	0xd015a17c
d0021ecc:	ed9db12b 	ldfd	f3, [sp, #172]	; 0xac
d0021ed0:	eeb17b00 	vmov.f64	d7, #16	; 0x40800000  4.0
d0021ed4:	ed8d7b47 	vstr	d7, [sp, #284]	; 0x11c
d0021ed8:	f1be7b00 			; <UNDEFINED> instruction: 0xf1be7b00
d0021edc:	f00a0f19 			; <UNDEFINED> instruction: 0xf00a0f19
d0021ee0:	bf8c0adf 	svclt	0x008c0adf
d0021ee4:	23012300 	movwcs	r2, #4864	; 0x1300
d0021ee8:	9b689304 	blls	0xd1a46b00
d0021eec:	f2c02b00 	vqdmlsl.s<illegal width 8>	q9, d0, d0
d0021ef0:	f1ba80c5 			; <UNDEFINED> instruction: 0xf1ba80c5
d0021ef4:	f0400f47 			; <UNDEFINED> instruction: 0xf0400f47
d0021ef8:	9b6880c7 	blls	0xd1a4221c
d0021efc:	bf082b00 	svclt	0x00082b00
d0021f00:	93682301 	cmnls	r8, #67108864	; 0x4000000
d0021f04:	7b00ed9d 	blvc	0xd005d580
d0021f08:	7b40eeb5 	blvc	0xd105d9e4
d0021f0c:	fa10eef1 	blx	0xd045dad8
d0021f10:	80d0f000 	sbcshi	pc, r0, r0
d0021f14:	6b04eeb2 	blvs	0xd015d9e4
d0021f18:	7bc6eeb4 	blvc	0xcf1dd9f0
d0021f1c:	fa10eef1 	blx	0xd045dae8
d0021f20:	8170f2c0 	cmnhi	r0, r0, asr #5	; <UNPREDICTABLE>
d0021f24:	0a00f04f 	beq	0xd005e068
d0021f28:	f5bae003 			; <UNDEFINED> instruction: 0xf5bae003
d0021f2c:	f0007f9a 			; <UNDEFINED> instruction: 0xf0007f9a
d0021f30:	ee87810f 	sins	f0, #10.0
d0021f34:	f10a7b06 			; <UNDEFINED> instruction: 0xf10a7b06
d0021f38:	eeb40a01 	vmov.f32	s0, #65	; 0x3e080000  0.1328125
d0021f3c:	eef17bc6 	vsqrt.f64	d23, d6
d0021f40:	daf2fa10 	ble	0xcfce0788
d0021f44:	6b00eeb7 	blvs	0xd005da28
d0021f48:	7bc6eeb4 	blvc	0xcf1dda20
d0021f4c:	fa10eef1 	blx	0xd045db18
d0021f50:	eeb2d511 	mrc	5, 5, sp, cr2, cr1, {0}
d0021f54:	eeb75b04 	vmov.f64	d5, #116	; 0x3fa00000  1.250
d0021f58:	e0036b00 	and	r6, r3, r0, lsl #22
d0021f5c:	7fa2f51a 	svcvc	0x00a2f51a
d0021f60:	80fef000 	rscshi	pc, lr, r0
d0021f64:	7b05ee27 	blvc	0xd019d808
d0021f68:	3afff10a 	bcc	0xd001e398
d0021f6c:	7bc6eeb4 	blvc	0xcf1dda44
d0021f70:	fa10eef1 	blx	0xd045db3c
d0021f74:	9b68d4f2 	blls	0xd1a57344
d0021f78:	f3404553 	vqrshl.u8	q10, <illegal reg q1.5>, q0
d0021f7c:	f11a80f1 			; <UNDEFINED> instruction: 0xf11a80f1
d0021f80:	f2c00f04 			; <UNDEFINED> instruction: 0xf2c00f04
d0021f84:	f10a80ed 			; <UNDEFINED> instruction: 0xf10a80ed
d0021f88:	e0960101 	adds	r0, r6, r1, lsl #2
d0021f8c:	232b2701 			; <UNDEFINED> instruction: 0x232b2701
d0021f90:	930346bb 	movwls	r4, #14011	; 0x36bb
d0021f94:	1ab6e73b 	bne	0xceddbc88
d0021f98:	f005e765 			; <UNDEFINED> instruction: 0xf005e765
d0021f9c:	2f000501 	svccs	0x00000501
d0021fa0:	bb8dd167 	bllt	0xce396544
d0021fa4:	b1361e75 	teqlt	r6, r5, ror lr
d0021fa8:	21303d01 	teqcs	r0, r1, lsl #26
d0021fac:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0021fb0:	1c6afd2f 	stclne	13, cr15, [sl], #-188	; 0xffffff44
d0021fb4:	f1b8d1f8 			; <UNDEFINED> instruction: 0xf1b8d1f8
d0021fb8:	f43f0f00 			; <UNDEFINED> instruction: 0xf43f0f00
d0021fbc:	2500af73 	strcs	sl, [r0, #-3955]	; 0xfffff08d
d0021fc0:	37012700 	strcc	r2, [r1, -r0, lsl #14]
d0021fc4:	1b01f819 	blne	0xd00a0030
d0021fc8:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0021fcc:	4547fd21 	strbmi	pc, [r7, #-3361]	; 0xfffff2df	; <UNPREDICTABLE>
d0021fd0:	2d00d3f7 	stccs	3, cr13, [r0, #-988]	; 0xfffffc24
d0021fd4:	af66f43f 	svcge	0x0066f43f
d0021fd8:	2e001e75 	mcrcs	14, 0, r1, cr0, cr5, {3}
d0021fdc:	af62f43f 	svcge	0x0062f43f
d0021fe0:	21203d01 			; <UNDEFINED> instruction: 0x21203d01
d0021fe4:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0021fe8:	1c6bfd13 	stclne	13, cr15, [fp], #-76	; 0xffffffb4
d0021fec:	b05fd1f8 	ldrshlt	sp, [pc], #-24	; <UNPREDICTABLE>
d0021ff0:	8ff0e8bd 	svchi	0x00f0e8bd
d0021ff4:	f1b8b927 			; <UNDEFINED> instruction: 0xf1b8b927
d0021ff8:	d1e10f00 	mvnle	r0, r0, lsl #30
d0021ffc:	461ee7ec 	ldrmi	lr, [lr], -ip, ror #15
d0022000:	46209903 	strtmi	r9, [r0], -r3, lsl #18
d0022004:	fd04f7ff 	stc2	7, cr15, [r4, #-1020]	; 0xfffffc04
d0022008:	0f00f1b8 	svceq	0x0000f1b8
d002200c:	2501d0e4 	strcs	sp, [r1, #-228]	; 0xffffff1c
d0022010:	f1bee7d6 			; <UNDEFINED> instruction: 0xf1bee7d6
d0022014:	d9470f19 	stmdble	r7, {r0, r3, r4, r8, r9, sl, fp}^
d0022018:	c210f8df 	andsgt	pc, r0, #14614528	; 0xdf0000
d002201c:	216e2361 	cmncs	lr, r1, ror #6
d0022020:	f10d44fc 			; <UNDEFINED> instruction: 0xf10d44fc
d0022024:	f10c0918 			; <UNDEFINED> instruction: 0xf10c0918
d0022028:	ea6f0202 	b	0xd1be2838
d002202c:	46480c0c 	strbmi	r0, [r8], -ip, lsl #24
d0022030:	f812e001 			; <UNDEFINED> instruction: 0xf812e001
d0022034:	f8003b01 			; <UNDEFINED> instruction: 0xf8003b01
d0022038:	eb0c1b01 	bl	0xd0328c44
d002203c:	46190802 	ldrmi	r0, [r9], -r2, lsl #16
d0022040:	d1f62b00 	mvnsle	r2, r0, lsl #22
d0022044:	020beb08 	andeq	lr, fp, #8, 22	; 0x2000
d0022048:	d8a44296 	stmiale	r4!, {r1, r2, r4, r7, r9, lr}
d002204c:	0601f015 			; <UNDEFINED> instruction: 0x0601f015
d0022050:	af1df43f 	svcge	0x001df43f
d0022054:	d1d22f00 	bicsle	r2, r2, r0, lsl #30
d0022058:	0f00f1b8 	svceq	0x0000f1b8
d002205c:	af22f43f 	svcge	0x0022f43f
d0022060:	463e4635 			; <UNDEFINED> instruction: 0x463e4635
d0022064:	f8dfe7ac 			; <UNDEFINED> instruction: 0xf8dfe7ac
d0022068:	236ec1c8 	cmncs	lr, #200, 2	; 0x32
d002206c:	44fc2169 	ldrbtmi	r2, [ip], #361	; 0x169
d0022070:	9903e7d7 	stmdbls	r3, {r0, r1, r2, r4, r6, r7, r8, r9, sl, sp, lr, pc}
d0022074:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0022078:	e792fccb 	ldr	pc, [r2, fp, asr #25]
d002207c:	f1ba2306 			; <UNDEFINED> instruction: 0xf1ba2306
d0022080:	93680f47 	cmnls	r8, #284	; 0x11c
d0022084:	af3ef43f 	svcge	0x003ef43f
d0022088:	0f45f1ba 	svceq	0x0045f1ba
d002208c:	0918f10d 	ldmdbeq	r8, {r0, r2, r3, r8, ip, sp, lr, pc}
d0022090:	9b04d154 	blls	0xd01565e8
d0022094:	0210f005 	andseq	pc, r0, #5
d0022098:	46489968 	strbmi	r9, [r8], -r8, ror #18
d002209c:	0b00ed9d 	bleq	0xd005d718
d00220a0:	fbb6f7ff 	blx	0xcede00a6
d00220a4:	e6d74680 	ldrb	r4, [r7], r0, lsl #13
d00220a8:	c188f8df 	ldrdgt	pc, [r8, pc]
d00220ac:	214e2341 	cmpcs	lr, r1, asr #6
d00220b0:	e7b644fc 			; <UNDEFINED> instruction: 0xe7b644fc
d00220b4:	f04f2101 			; <UNDEFINED> instruction: 0xf04f2101
d00220b8:	9b680a00 	blls	0xd1a248c0
d00220bc:	0918f10d 	ldmdbeq	r8, {r0, r2, r3, r8, ip, sp, lr, pc}
d00220c0:	0210f005 	andseq	pc, r0, #5
d00220c4:	46481a59 			; <UNDEFINED> instruction: 0x46481a59
d00220c8:	ed9d9205 	lfm	f1, 1, [sp, #20]
d00220cc:	f7ff0b00 			; <UNDEFINED> instruction: 0xf7ff0b00
d00220d0:	4680fad7 	pkhtbmi	pc, r0, r7, asr #21	; <UNPREDICTABLE>
d00220d4:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d00220d8:	4649aebf 			; <UNDEFINED> instruction: 0x4649aebf
d00220dc:	9a052300 	bls	0xd016ace4
d00220e0:	3301e003 	movwcc	lr, #4099	; 0x1003
d00220e4:	f0004598 			; <UNDEFINED> instruction: 0xf0004598
d00220e8:	f8118086 			; <UNDEFINED> instruction: 0xf8118086
d00220ec:	282e0b01 	stmdacs	lr!, {r0, r8, r9, fp}
d00220f0:	f1bad1f7 			; <UNDEFINED> instruction: 0xf1bad1f7
d00220f4:	db020f00 	blle	0xd00a5cfc
d00220f8:	42999968 	addsmi	r9, r9, #104, 18	; 0x1a0000
d00220fc:	2a00d334 	bcs	0xd0056dd4
d0022100:	aeaaf47f 	mcrge	4, 5, pc, cr10, cr15, {3}	; <UNPREDICTABLE>
d0022104:	e002464b 	and	r4, r2, fp, asr #12
d0022108:	f43f4590 			; <UNDEFINED> instruction: 0xf43f4590
d002210c:	f813aea5 			; <UNDEFINED> instruction: 0xf813aea5
d0022110:	32011b01 	andcc	r1, r1, #1024	; 0x400
d0022114:	d1f7292e 	mvnsle	r2, lr, lsr #18
d0022118:	0308eb09 	movweq	lr, #35593	; 0x8b09
d002211c:	f813e005 			; <UNDEFINED> instruction: 0xf813e005
d0022120:	29301d01 	ldmdbcs	r0!, {r0, r8, sl, fp, ip}
d0022124:	ae98f47f 	mrcge	4, 4, APSR_nzcv, cr8, cr15, {3}
d0022128:	45904680 	ldrmi	r4, [r0, #1664]	; 0x680
d002212c:	30fff108 	rscscc	pc, pc, r8, lsl #2
d0022130:	f47fd8f5 			; <UNDEFINED> instruction: 0xf47fd8f5
d0022134:	f108ae91 			; <UNDEFINED> instruction: 0xf108ae91
d0022138:	e68d38ff 			; <UNDEFINED> instruction: 0xe68d38ff
d002213c:	0b00ed9d 	bleq	0xd005d7b8
d0022140:	f0059968 			; <UNDEFINED> instruction: 0xf0059968
d0022144:	46480210 			; <UNDEFINED> instruction: 0x46480210
d0022148:	fa9af7ff 	blx	0xce6e014c
d002214c:	e6834680 	str	r4, [r3], r0, lsl #13
d0022150:	6b00eeb7 	blvs	0xd005dc34
d0022154:	7bc6eeb4 	blvc	0xcf1ddc2c
d0022158:	fa10eef1 	blx	0xd045dd24
d002215c:	aef9f53f 	mrcge	5, 7, APSR_nzcv, cr9, cr15, {1}
d0022160:	0210f005 	andseq	pc, r0, #5
d0022164:	0918f10d 	ldmdbeq	r8, {r0, r2, r3, r8, ip, sp, lr, pc}
d0022168:	46489968 	strbmi	r9, [r8], -r8, ror #18
d002216c:	39019b04 	stmdbcc	r1, {r2, r8, r9, fp, ip, pc}
d0022170:	ed9d9204 	lfm	f1, 1, [sp, #16]
d0022174:	f7ff0b00 			; <UNDEFINED> instruction: 0xf7ff0b00
d0022178:	9a04fb4b 	bls	0xd0160eac
d002217c:	2a004680 	bcs	0xd0033b84
d0022180:	ae6af47f 	mcrge	4, 3, pc, cr10, cr15, {3}	; <UNPREDICTABLE>
d0022184:	46424448 	strbmi	r4, [r2], -r8, asr #8
d0022188:	461ae000 	ldrmi	lr, [sl], -r0
d002218c:	2a001e53 	bcs	0xd0029ae0
d0022190:	ae62f43f 	mcrge	4, 3, pc, cr2, cr15, {1}	; <UNPREDICTABLE>
d0022194:	1d01f810 	stcne	8, cr15, [r1, #-64]	; 0xffffffc0
d0022198:	0cdff001 	ldcleq	0, cr15, [pc], {1}
d002219c:	0f45f1bc 	svceq	0x0045f1bc
d00221a0:	eb09d1f3 	bl	0xd0296974
d00221a4:	46180c03 	ldrmi	r0, [r8], -r3, lsl #24
d00221a8:	f81ce005 			; <UNDEFINED> instruction: 0xf81ce005
d00221ac:	f1baad01 			; <UNDEFINED> instruction: 0xf1baad01
d00221b0:	d1220f30 			; <UNDEFINED> instruction: 0xd1220f30
d00221b4:	f1004670 			; <UNDEFINED> instruction: 0xf1004670
d00221b8:	28003eff 	stmdacs	r0, {r0, r1, r2, r3, r4, r5, r6, r7, r9, sl, fp, ip, sp}
d00221bc:	4543d1f5 	strbmi	sp, [r3, #-501]	; 0xfffffe0b
d00221c0:	f1c2d212 			; <UNDEFINED> instruction: 0xf1c2d212
d00221c4:	eb090a01 	bl	0xd02649d0
d00221c8:	f10d0c03 			; <UNDEFINED> instruction: 0xf10d0c03
d00221cc:	44820e17 	strmi	r0, [r2], #3607	; 0xe17
d00221d0:	445344c6 	ldrbmi	r4, [r3], #-1222	; 0xfffffb3a
d00221d4:	3b0144d6 	blcc	0xd0073534
d00221d8:	e001444b 	and	r4, r1, fp, asr #8
d00221dc:	1f01f81c 	svcne	0x0001f81c
d00221e0:	1f01f803 	svcne	0x0001f803
d00221e4:	d1f94573 	mvnsle	r4, r3, ror r5
d00221e8:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d00221ec:	0202eba8 	andeq	lr, r2, #168, 22	; 0x2a000
d00221f0:	0802eb00 	stmdaeq	r2, {r8, r9, fp, sp, lr, pc}
d00221f4:	4643e630 			; <UNDEFINED> instruction: 0x4643e630
d00221f8:	f1bae77b 			; <UNDEFINED> instruction: 0xf1bae77b
d00221fc:	bf080f2e 	svclt	0x00080f2e
d0022200:	e7dc4670 			; <UNDEFINED> instruction: 0xe7dc4670
d0022204:	7b00eeb7 	blvc	0xd005dce8
d0022208:	6b00ed9d 	blvs	0xd005d884
d002220c:	6bc7eeb4 	blvs	0xcf21dce4
d0022210:	fa10eef1 	blx	0xd045dddc
d0022214:	af4ef57f 	svcge	0x004ef57f
d0022218:	0a00f04f 	beq	0xd005e35c
d002221c:	7b00ed9d 	blvc	0xd005d898
d0022220:	bf00e697 	svclt	0x0000e697
d0022224:	ffffff84 			; <UNDEFINED> instruction: 0xffffff84
d0022228:	fffffeee 			; <UNDEFINED> instruction: 0xfffffeee
d002222c:	fffffd90 			; <UNDEFINED> instruction: 0xfffffd90
d0022230:	fffffd4e 			; <UNDEFINED> instruction: 0xfffffd4e
d0022234:	fffffd08 			; <UNDEFINED> instruction: 0xfffffd08

Disassembly of section .text.sb_format.part.0:

d0022268 <.text.sb_format.part.0>:
d0022268:	4ff0e92d 	svcmi	0x00f0e92d
d002226c:	78094688 	stmdavc	r9, {r3, r7, r9, sl, lr}
d0022270:	4683b0a7 	strmi	fp, [r3], r7, lsr #1
d0022274:	f0002900 			; <UNDEFINED> instruction: 0xf0002900
d0022278:	4bfa80b3 	blmi	0xcfec254c
d002227c:	f8df4691 			; <UNDEFINED> instruction: 0xf8df4691
d0022280:	447ba3e8 	ldrbtmi	sl, [fp], #-1000	; 0xfffffc18
d0022284:	4bf99308 	blmi	0xcfe86eac
d0022288:	9309447b 	movwls	r4, #38011	; 0x947b
d002228c:	f0402925 			; <UNDEFINED> instruction: 0xf0402925
d0022290:	f89880fd 			; <UNDEFINED> instruction: 0xf89880fd
d0022294:	2c254001 	stccs	0, cr4, [r5], #-4
d0022298:	80fef000 	rscshi	pc, lr, r0
d002229c:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d00222a0:	f1a42600 			; <UNDEFINED> instruction: 0xf1a42600
d00222a4:	2b100320 	blcs	0xd0422f2c
d00222a8:	e8dfd80a 	ldm	pc, {r1, r3, fp, ip, lr, pc}^	; <UNPREDICTABLE>
d00222ac:	0978f003 	ldmdbeq	r8!, {r0, r1, ip, sp, lr, pc}^
d00222b0:	09097509 	stmdbeq	r9, {r0, r3, r8, sl, ip, sp, lr}
d00222b4:	09090909 	stmdbeq	r9, {r0, r3, r8, fp}
d00222b8:	6f097209 	svcvs	0x00097209
d00222bc:	006a0909 	rsbeq	r0, sl, r9, lsl #18
d00222c0:	f0402c2a 			; <UNDEFINED> instruction: 0xf0402c2a
d00222c4:	f8d980ef 			; <UNDEFINED> instruction: 0xf8d980ef
d00222c8:	f1083000 			; <UNDEFINED> instruction: 0xf1083000
d00222cc:	681d0101 	ldmdavs	sp, {r0, r8}
d00222d0:	2d001d1a 	stccs	13, cr1, [r0, #-104]	; 0xffffff98
d00222d4:	2000f8c9 	andcs	pc, r0, r9, asr #17
d00222d8:	8122f2c0 	smlawthi	r2, r0, r2, pc	; <UNPREDICTABLE>
d00222dc:	5f00f5b5 	svcpl	0x0000f5b5
d00222e0:	4001f898 	mulmi	r1, r8, r8
d00222e4:	f44fbf28 			; <UNDEFINED> instruction: 0xf44fbf28
d00222e8:	2c2e5500 	cfstr32cs	mvfx5, [lr], #-0
d00222ec:	80fbf000 	rscshi	pc, fp, r0
d00222f0:	37fff04f 	ldrbcc	pc, [pc, pc, asr #32]!	; <UNPREDICTABLE>
d00222f4:	f0002c68 			; <UNDEFINED> instruction: 0xf0002c68
d00222f8:	2c6c810d 	stfcsp	f0, [ip], #-52	; 0xffffffcc
d00222fc:	811ef000 	tsthi	lr, r0	; <UNPREDICTABLE>
d0022300:	f0002c7a 			; <UNDEFINED> instruction: 0xf0002c7a
d0022304:	2c748122 	ldfcsp	f0, [r4], #-136	; 0xffffff78
d0022308:	8161f000 	msrhi	SPSR_c, r0
d002230c:	f0002c6a 			; <UNDEFINED> instruction: 0xf0002c6a
d0022310:	230081b3 	movwcs	r8, #435	; 0x1b3
d0022314:	d0632c00 	rsble	r2, r3, r0, lsl #24
d0022318:	f1012c64 			; <UNDEFINED> instruction: 0xf1012c64
d002231c:	d07d0801 	rsbsle	r0, sp, r1, lsl #16
d0022320:	d07b2c69 	rsbsle	r2, fp, r9, ror #24
d0022324:	0262f1a4 	rsbeq	pc, r2, #164, 2	; 0x29
d0022328:	01dff004 	bicseq	pc, pc, r4
d002232c:	f1a1b2d2 			; <UNDEFINED> instruction: 0xf1a1b2d2
d0022330:	2a130c58 	bcs	0xd04e5498
d0022334:	fc8cfabc 	stc2	10, cr15, [ip], {188}	; 0xbc	; <UNPREDICTABLE>
d0022338:	1c5cea4f 	mrrcne	10, 4, lr, ip, cr15
d002233c:	48c8d806 	stmiami	r8, {r1, r2, fp, ip, lr, pc}^
d0022340:	f202fa20 	vpmax.s8	d15, d2, d16
d0022344:	0201f002 	andeq	pc, r1, #2
d0022348:	0c02ea4c 			; <UNDEFINED> instruction: 0x0c02ea4c
d002234c:	0f00f1bc 	svceq	0x0000f1bc
d0022350:	816cf000 	msrhi	SPSR_fs, r0
d0022354:	f0002c6f 			; <UNDEFINED> instruction: 0xf0002c6f
d0022358:	2958811b 	ldmdbcs	r8, {r0, r1, r3, r4, r8, pc}^
d002235c:	811af000 	tsthi	sl, r0	; <UNPREDICTABLE>
d0022360:	bf0c2c62 	svclt	0x000c2c62
d0022364:	210a2102 	tstcs	sl, r2, lsl #2
d0022368:	2b063b01 	blcs	0xd01b0f74
d002236c:	84fdf200 	ldrbthi	pc, [sp], #512	; 0x200	; <UNPREDICTABLE>
d0022370:	f013e8df 			; <UNDEFINED> instruction: 0xf013e8df
d0022374:	0143014b 	cmpeq	r3, fp, asr #2
d0022378:	00480018 	subeq	r0, r8, r8, lsl r0
d002237c:	00180018 	andseq	r0, r8, r8, lsl r0
d0022380:	f0460048 			; <UNDEFINED> instruction: 0xf0460048
d0022384:	f8180602 			; <UNDEFINED> instruction: 0xf8180602
d0022388:	e78a4f01 	str	r4, [sl, r1, lsl #30]
d002238c:	0601f046 	streq	pc, [r1], -r6, asr #32
d0022390:	f046e7f9 			; <UNDEFINED> instruction: 0xf046e7f9
d0022394:	e7f60604 	ldrb	r0, [r6, r4, lsl #12]!
d0022398:	0610f046 	ldreq	pc, [r0], -r6, asr #32
d002239c:	f046e7f3 			; <UNDEFINED> instruction: 0xf046e7f3
d00223a0:	e7f00608 	ldrb	r0, [r0, r8, lsl #12]!
d00223a4:	3000f8d9 	ldrdcc	pc, [r0], -r9
d00223a8:	681a1d18 	ldmdavs	sl, {r3, r4, r8, sl, fp, ip}
d00223ac:	f8c92300 			; <UNDEFINED> instruction: 0xf8c92300
d00223b0:	f1a40000 			; <UNDEFINED> instruction: 0xf1a40000
d00223b4:	f0260058 			; <UNDEFINED> instruction: 0xf0260058
d00223b8:	2400060c 	strcs	r0, [r0], #-1548	; 0xfffff9f4
d00223bc:	fab09704 	blx	0xcec47fd4
d00223c0:	9602f080 	strls	pc, [r2], -r0, lsl #1
d00223c4:	09409503 	stmdbeq	r0, {r0, r1, r8, sl, ip, pc}^
d00223c8:	94069100 	strls	r9, [r6], #-256	; 0xffffff00
d00223cc:	46589005 	ldrbmi	r9, [r8], -r5
d00223d0:	f7ff9401 			; <UNDEFINED> instruction: 0xf7ff9401
d00223d4:	f898fb4d 			; <UNDEFINED> instruction: 0xf898fb4d
d00223d8:	29001000 	stmdbcs	r0, {ip}
d00223dc:	af56f47f 	svcge	0x0056f47f
d00223e0:	300cf8db 	ldrdcc	pc, [ip], -fp
d00223e4:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d00223e8:	465880db 			; <UNDEFINED> instruction: 0x465880db
d00223ec:	fafcf7ff 	blx	0xcff603f0
d00223f0:	300cf8db 	ldrdcc	pc, [ip], -fp
d00223f4:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d00223f8:	f8db80d3 			; <UNDEFINED> instruction: 0xf8db80d3
d00223fc:	b0270008 	eorlt	r0, r7, r8
d0022400:	8ff0e8bd 	svchi	0x00f0e8bd
d0022404:	3000f8d9 	ldrdcc	pc, [r0], -r9
d0022408:	f0233307 			; <UNDEFINED> instruction: 0xf0233307
d002240c:	f1030307 			; <UNDEFINED> instruction: 0xf1030307
d0022410:	f8c90208 			; <UNDEFINED> instruction: 0xf8c90208
d0022414:	e9d32000 	ldmib	r3, {sp}^
d0022418:	e7ca2300 	strb	r2, [sl, r0, lsl #6]
d002241c:	2b063b01 	blcs	0xd01b1028
d0022420:	84acf200 	strthi	pc, [ip], #512	; 0x200
d0022424:	f003e8df 			; <UNDEFINED> instruction: 0xf003e8df
d0022428:	1f04d7e0 	svcne	0x0004d7e0
d002242c:	001f0404 	andseq	r0, pc, r4, lsl #8
d0022430:	3000f8d9 	ldrdcc	pc, [r0], -r9
d0022434:	1d1a6818 	ldcne	8, cr6, [sl, #-96]	; 0xffffffa0
d0022438:	f8c917c1 			; <UNDEFINED> instruction: 0xf8c917c1
d002243c:	28002000 	stmdacs	r0, {sp}
d0022440:	0300f171 	movweq	pc, #369	; 0x171	; <UNPREDICTABLE>
d0022444:	4602db1e 			; <UNDEFINED> instruction: 0x4602db1e
d0022448:	0fc8460b 	svceq	0x00c8460b
d002244c:	2100240a 	tstcs	r0, sl, lsl #8
d0022450:	90019704 	andls	r9, r1, r4, lsl #14
d0022454:	95034658 	strls	r4, [r3, #-1624]	; 0xfffff9a8
d0022458:	91069602 	tstls	r6, r2, lsl #12
d002245c:	94009105 	strls	r9, [r0], #-261	; 0xfffffefb
d0022460:	fb06f7ff 	blx	0xd01e0466
d0022464:	f8d9e7b7 			; <UNDEFINED> instruction: 0xf8d9e7b7
d0022468:	33073000 	movwcc	r3, #28672	; 0x7000
d002246c:	0307f023 	movweq	pc, #28707	; 0x7023	; <UNPREDICTABLE>
d0022470:	0100e9d3 	ldrdeq	lr, [r0, -r3]
d0022474:	0208f103 	andeq	pc, r8, #-1073741824	; 0xc0000000
d0022478:	f8c92800 			; <UNDEFINED> instruction: 0xf8c92800
d002247c:	f1712000 			; <UNDEFINED> instruction: 0xf1712000
d0022480:	dae00300 	ble	0xcf823088
d0022484:	eb614242 	bl	0xd1872d94
d0022488:	e7de0341 	ldrb	r0, [lr, r1, asr #6]
d002248c:	f1084658 			; <UNDEFINED> instruction: 0xf1084658
d0022490:	f7ff0801 			; <UNDEFINED> instruction: 0xf7ff0801
d0022494:	e79efabd 			; <UNDEFINED> instruction: 0xe79efabd
d0022498:	f1084658 			; <UNDEFINED> instruction: 0xf1084658
d002249c:	f7ff0802 			; <UNDEFINED> instruction: 0xf7ff0802
d00224a0:	e798fab7 			; <UNDEFINED> instruction: 0xe798fab7
d00224a4:	0230f1a4 	eorseq	pc, r0, #164, 2	; 0x29
d00224a8:	2b09b2d3 	blcs	0xd028effc
d00224ac:	80e8f200 	rschi	pc, r8, r0, lsl #4
d00224b0:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d00224b4:	f5c22500 			; <UNDEFINED> instruction: 0xf5c22500
d00224b8:	46415300 	strbmi	r5, [r1], -r0, lsl #6
d00224bc:	0085eb05 	addeq	lr, r5, r5, lsl #22
d00224c0:	4303fbaa 	movwmi	pc, #15274	; 0x3baa	; <UNPREDICTABLE>
d00224c4:	4b01f818 	blmi	0xd00a052c
d00224c8:	0fd3ebb5 	svceq	0x00d3ebb5
d00224cc:	0540eb02 	strbeq	lr, [r0, #-2818]	; 0xfffff4fe
d00224d0:	0230f1a4 	eorseq	pc, r0, #164, 2	; 0x29
d00224d4:	f44fbf88 			; <UNDEFINED> instruction: 0xf44fbf88
d00224d8:	b2d35500 	sbcslt	r5, r3, #0, 10
d00224dc:	d9ea2b09 	stmible	sl!, {r0, r3, r8, r9, fp, sp}^
d00224e0:	f47f2c2e 			; <UNDEFINED> instruction: 0xf47f2c2e
d00224e4:	784caf05 	stmdavc	ip, {r0, r2, r8, r9, sl, fp, sp, pc}^
d00224e8:	d1322c2a 	teqle	r2, sl, lsr #24
d00224ec:	3000f8d9 	ldrdcc	pc, [r0], -r9
d00224f0:	681f1c88 	ldmdavs	pc, {r3, r7, sl, fp, ip}	; <UNPREDICTABLE>
d00224f4:	2f001d1a 	svccs	0x00001d1a
d00224f8:	2000f8c9 	andcs	pc, r0, r9, asr #17
d00224fc:	f2c0788c 	vmlal.s8	<illegal reg q11.5>, d16, d12
d0022500:	f5b78091 			; <UNDEFINED> instruction: 0xf5b78091
d0022504:	46015f00 	strmi	r5, [r1], -r0, lsl #30
d0022508:	f44fbf28 			; <UNDEFINED> instruction: 0xf44fbf28
d002250c:	2c685700 	stclcs	7, cr5, [r8], #-0
d0022510:	aef3f47f 	mrcge	4, 7, APSR_nzcv, cr3, cr15, {3}
d0022514:	2c68784c 	stclcs	8, cr7, [r8], #-304	; 0xfffffed0
d0022518:	3101d03e 	tstcc	r1, lr, lsr r0
d002251c:	e6f92302 	ldrbt	r2, [r9], r2, lsl #6
d0022520:	4f00f1b5 	svcmi	0x0000f1b5
d0022524:	0601f046 	streq	pc, [r1], -r6, asr #32
d0022528:	426dd077 	rsbmi	sp, sp, #119	; 0x77
d002252c:	4001f898 	mulmi	r1, r8, r8
d0022530:	5f00f5b5 	svcpl	0x0000f5b5
d0022534:	f44fbf28 			; <UNDEFINED> instruction: 0xf44fbf28
d0022538:	e6d65500 	ldrb	r5, [r6], r0, lsl #10
d002253c:	2c6c784c 	stclcs	8, cr7, [ip], #-304	; 0xfffffed0
d0022540:	8096f000 	addshi	pc, r6, r0
d0022544:	23033101 	movwcs	r3, #12545	; 0x3101
d0022548:	784ce6e4 	stmdavc	ip, {r2, r5, r6, r7, r9, sl, sp, lr, pc}^
d002254c:	31012305 	tstcc	r1, r5, lsl #6
d0022550:	f1a4e6e0 			; <UNDEFINED> instruction: 0xf1a4e6e0
d0022554:	1c480230 	sfmne	f0, 2, [r8], {48}	; 0x30
d0022558:	2b09b2d3 	blcs	0xd028f0ac
d002255c:	80daf200 	sbcshi	pc, sl, r0, lsl #4
d0022560:	27001c88 	strcs	r1, [r0, -r8, lsl #25]
d0022564:	5300f5c2 	movwpl	pc, #1474	; 0x5c2	; <UNPREDICTABLE>
d0022568:	0487eb07 	streq	lr, [r7], #2823	; 0xb07
d002256c:	fbaa4601 	blx	0xceab3d7a
d0022570:	ebb7c303 	bl	0xcee13184
d0022574:	eb020fd3 	bl	0xd00a64c8
d0022578:	f8100744 			; <UNDEFINED> instruction: 0xf8100744
d002257c:	bf884b01 	svclt	0x00884b01
d0022580:	5700f44f 	strpl	pc, [r0, -pc, asr #8]
d0022584:	0230f1a4 	eorseq	pc, r0, #164, 2	; 0x29
d0022588:	2b09b2d3 	blcs	0xd028f0dc
d002258c:	e6b1d9ea 	ldrt	sp, [r1], sl, ror #19
d0022590:	e6e92108 	strbt	r2, [r9], r8, lsl #2
d0022594:	e6e72110 	usat	r2, #7, r0, lsl #2
d0022598:	2301788c 	movwcs	r7, #6284	; 0x188c
d002259c:	e6b93102 	ldrt	r3, [r9], r2, lsl #2
d00225a0:	3000f8db 	ldrdcc	pc, [r0], -fp
d00225a4:	f43f2b00 			; <UNDEFINED> instruction: 0xf43f2b00
d00225a8:	f8dbaf28 			; <UNDEFINED> instruction: 0xf8dbaf28
d00225ac:	2a002004 	bcs	0xd002a5c4
d00225b0:	af23f43f 	svcge	0x0023f43f
d00225b4:	1008f8db 	ldrdne	pc, [r8], -fp
d00225b8:	bf98428a 	svclt	0x0098428a
d00225bc:	31fff102 	mvnscc	pc, r2, lsl #2
d00225c0:	545a2200 	ldrbpl	r2, [sl], #-512	; 0xfffffe00
d00225c4:	0008f8db 	ldrdeq	pc, [r8], -fp
d00225c8:	e8bdb027 	pop	{r0, r1, r2, r5, ip, sp, pc}
d00225cc:	784c8ff0 	stmdavc	ip, {r4, r5, r6, r7, r8, r9, sl, fp, pc}^
d00225d0:	31012306 	tstcc	r1, r6, lsl #6
d00225d4:	f8d9e69e 			; <UNDEFINED> instruction: 0xf8d9e69e
d00225d8:	f9b33000 			; <UNDEFINED> instruction: 0xf9b33000
d00225dc:	1d1a0000 	ldcne	0, cr0, [sl, #-0]
d00225e0:	f8c917c1 			; <UNDEFINED> instruction: 0xf8c917c1
d00225e4:	e72a2000 	str	r2, [sl, -r0]!
d00225e8:	3000f8d9 	ldrdcc	pc, [r0], -r9
d00225ec:	0000f993 	muleq	r0, r3, r9
d00225f0:	17c11d1a 	bfine	r1, sl, (invalid: 26:1)
d00225f4:	2000f8c9 	andcs	pc, r0, r9, asr #17
d00225f8:	f8d9e721 			; <UNDEFINED> instruction: 0xf8d9e721
d00225fc:	1d183000 	ldcne	0, cr3, [r8, #-0]
d0022600:	2300881a 	movwcs	r8, #2074	; 0x81a
d0022604:	0000f8c9 	andeq	pc, r0, r9, asr #17
d0022608:	f8d9e6d3 			; <UNDEFINED> instruction: 0xf8d9e6d3
d002260c:	1d183000 	ldcne	0, cr3, [r8, #-0]
d0022610:	2300781a 	movwcs	r7, #2074	; 0x81a
d0022614:	0000f8c9 	andeq	pc, r0, r9, asr #17
d0022618:	f898e6cb 			; <UNDEFINED> instruction: 0xf898e6cb
d002261c:	f44f4001 	vst4.8	{d20-d23}, [pc], r1
d0022620:	e6625500 	strbt	r5, [r2], -r0, lsl #10
d0022624:	37fff04f 	ldrbcc	pc, [pc, pc, asr #32]!	; <UNPREDICTABLE>
d0022628:	e6634601 	strbt	r4, [r3], -r1, lsl #12
d002262c:	d0592c70 	subsle	r2, r9, r0, ror ip
d0022630:	d0722c73 	rsbsle	r2, r2, r3, ror ip
d0022634:	d0262c63 	eorle	r2, r6, r3, ror #24
d0022638:	0245f1a1 	subeq	pc, r5, #1073741864	; 0x40000028
d002263c:	d93f2a02 	ldmdble	pc!, {r1, r9, fp, sp}	; <UNPREDICTABLE>
d0022640:	f0002941 			; <UNDEFINED> instruction: 0xf0002941
d0022644:	2c6e80af 	stclcs	0, cr8, [lr], #-700	; 0xfffffd44
d0022648:	8216f000 	andshi	pc, r6, #0
d002264c:	21254658 			; <UNDEFINED> instruction: 0x21254658
d0022650:	f9def7ff 			; <UNDEFINED> instruction: 0xf9def7ff
d0022654:	46584621 	ldrbmi	r4, [r8], -r1, lsr #12
d0022658:	f9daf7ff 			; <UNDEFINED> instruction: 0xf9daf7ff
d002265c:	bf00e6bb 	svclt	0x0000e6bb
d0022660:	00082001 	andeq	r2, r8, r1
d0022664:	ffffffce 			; <UNDEFINED> instruction: 0xffffffce
d0022668:	cccccccd 	stclgt	12, cr12, [ip], {205}	; 0xcd
d002266c:	ffffffb4 			; <UNDEFINED> instruction: 0xffffffb4
d0022670:	2304788c 	movwcs	r7, #18572	; 0x488c
d0022674:	e64d3102 	strb	r3, [sp], -r2, lsl #2
d0022678:	2307784c 	movwcs	r7, #30796	; 0x784c
d002267c:	e6493101 	strb	r3, [r9], -r1, lsl #2
d0022680:	25004641 	strcs	r4, [r0, #-1601]	; 0xfffff9bf
d0022684:	2d01e631 	stccs	6, cr14, [r1, #-196]	; 0xffffff3c
d0022688:	2501bf38 	strcs	fp, [r1, #-3896]	; 0xfffff0c8
d002268c:	f10507f6 			; <UNDEFINED> instruction: 0xf10507f6
d0022690:	f14037ff 			; <UNDEFINED> instruction: 0xf14037ff
d0022694:	f8d9818b 			; <UNDEFINED> instruction: 0xf8d9818b
d0022698:	46583000 	ldrbmi	r3, [r8], -r0
d002269c:	1d1a3d02 	ldcne	13, cr3, [sl, #-8]
d00226a0:	f8c97819 			; <UNDEFINED> instruction: 0xf8c97819
d00226a4:	f7ff2000 			; <UNDEFINED> instruction: 0xf7ff2000
d00226a8:	2f00f9b3 	svccs	0x0000f9b3
d00226ac:	ae93f43f 	mrcge	4, 4, APSR_nzcv, cr3, cr15, {1}
d00226b0:	46583d01 	ldrbmi	r3, [r8], -r1, lsl #26
d00226b4:	f7ff2120 			; <UNDEFINED> instruction: 0xf7ff2120
d00226b8:	1c68f9ab 			; <UNDEFINED> instruction: 0x1c68f9ab
d00226bc:	e68ad1f8 			; <UNDEFINED> instruction: 0xe68ad1f8
d00226c0:	0000f8d9 	ldrdeq	pc, [r0], -r9
d00226c4:	462b4621 	strtmi	r4, [fp], -r1, lsr #12
d00226c8:	1dc44632 	stclne	6, cr4, [r4, #200]	; 0xc8
d00226cc:	f0244658 			; <UNDEFINED> instruction: 0xf0244658
d00226d0:	ed940407 	cfldrs	mvf0, [r4, #28]
d00226d4:	34080b00 	strcc	r0, [r8], #-2816	; 0xfffff500
d00226d8:	f8c99700 			; <UNDEFINED> instruction: 0xf8c99700
d00226dc:	f7ff4000 			; <UNDEFINED> instruction: 0xf7ff4000
d00226e0:	e678fb75 			; <UNDEFINED> instruction: 0xe678fb75
d00226e4:	3000f8d9 	ldrdcc	pc, [r0], -r9
d00226e8:	060cf026 	streq	pc, [ip], -r6, lsr #32
d00226ec:	21102401 	tstcs	r0, r1, lsl #8
d00226f0:	46581d1a 			; <UNDEFINED> instruction: 0x46581d1a
d00226f4:	2000f8c9 	andcs	pc, r0, r9, asr #17
d00226f8:	4663681a 			; <UNDEFINED> instruction: 0x4663681a
d00226fc:	f8cd9602 			; <UNDEFINED> instruction: 0xf8cd9602
d0022700:	9704c014 	smladls	r4, r4, r0, ip
d0022704:	f8cd9503 			; <UNDEFINED> instruction: 0xf8cd9503
d0022708:	9406c004 	strls	ip, [r6], #-4
d002270c:	f7ff9100 			; <UNDEFINED> instruction: 0xf7ff9100
d0022710:	e660f9af 	strbt	pc, [r0], -pc, lsr #19	; <UNPREDICTABLE>
d0022714:	27004601 	strcs	r4, [r0, -r1, lsl #12]
d0022718:	f8d9e5ec 			; <UNDEFINED> instruction: 0xf8d9e5ec
d002271c:	1d1a3000 	ldcne	0, cr3, [sl, #-0]
d0022720:	2000f8c9 	andcs	pc, r0, r9, asr #17
d0022724:	9314681b 	tstls	r4, #1769472	; 0x1b0000
d0022728:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d002272c:	781b813b 	ldmdavc	fp, {r0, r1, r3, r4, r5, r8, pc}
d0022730:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d0022734:	0ff88197 	svceq	0x00f88197
d0022738:	f0002f00 			; <UNDEFINED> instruction: 0xf0002f00
d002273c:	9a148193 	bls	0xd0542d90
d0022740:	f8122400 			; <UNDEFINED> instruction: 0xf8122400
d0022744:	34013f01 	strcc	r3, [r1], #-3841	; 0xfffff0ff
d0022748:	42bcb11b 	adcsmi	fp, ip, #-1073741818	; 0xc0000006
d002274c:	2800d3f9 	stmdacs	r0, {r0, r3, r4, r5, r6, r7, r8, r9, ip, lr, pc}
d0022750:	42a5d1f7 	adcmi	sp, r5, #-1073741763	; 0xc000003d
d0022754:	813df200 	teqhi	sp, r0, lsl #4	; <UNPREDICTABLE>
d0022758:	0301f016 	movweq	pc, #4118	; 0x1016	; <UNPREDICTABLE>
d002275c:	f0009312 			; <UNDEFINED> instruction: 0xf0009312
d0022760:	25008189 	strcs	r8, [r0, #-393]	; 0xfffffe77
d0022764:	95149b14 	ldrls	r9, [r4, #-2836]	; 0xfffff4ec
d0022768:	1e5e4625 	cdpne	6, 5, cr4, cr14, cr5, {1}
d002276c:	4637461c 			; <UNDEFINED> instruction: 0x4637461c
d0022770:	f8164658 			; <UNDEFINED> instruction: 0xf8164658
d0022774:	f7ff1f01 			; <UNDEFINED> instruction: 0xf7ff1f01
d0022778:	1cbbf94b 			; <UNDEFINED> instruction: 0x1cbbf94b
d002277c:	429d1b1b 	addsmi	r1, sp, #27648	; 0x6c00
d0022780:	9b12d8f5 	blls	0xd04d8b5c
d0022784:	2b009d14 	blcs	0xd0049bdc
d0022788:	ae25f43f 	mcrge	4, 1, pc, cr5, cr15, {1}	; <UNPREDICTABLE>
d002278c:	2d001e6c 	stccs	14, cr1, [r0, #-432]	; 0xfffffe50
d0022790:	ae21f43f 	mcrge	4, 1, pc, cr1, cr15, {1}	; <UNPREDICTABLE>
d0022794:	21203c01 			; <UNDEFINED> instruction: 0x21203c01
d0022798:	f7ff4658 			; <UNDEFINED> instruction: 0xf7ff4658
d002279c:	1c67f939 			; <UNDEFINED> instruction: 0x1c67f939
d00227a0:	e618d1f8 			; <UNDEFINED> instruction: 0xe618d1f8
d00227a4:	3000f8d9 	ldrdcc	pc, [r0], -r9
d00227a8:	f0233307 			; <UNDEFINED> instruction: 0xf0233307
d00227ac:	ed930307 	ldc	3, cr0, [r3, #28]
d00227b0:	33087b00 	movwcc	r7, #35584	; 0x8b00
d00227b4:	0b17ec51 	bleq	0xd061d900
d00227b8:	3000f8c9 	andcc	pc, r0, r9, asr #17
d00227bc:	ee17460b 	cfmsub32	mvax0, mvfx4, mvfx7, mvfx11
d00227c0:	2b002a10 	blcs	0xd002d008
d00227c4:	7b12ed8d 	blvc	0xd04dde00
d00227c8:	8176f2c0 	cmnhi	r6, r0, asr #5	; <UNPREDICTABLE>
d00227cc:	f1000771 			; <UNDEFINED> instruction: 0xf1000771
d00227d0:	00b18176 	adcseq	r8, r1, r6, ror r1
d00227d4:	0120f001 	msreq	CPSR_, r1
d00227d8:	f3c39114 	vorr.i32	d25, #180	; 0x000000b4
d00227dc:	920c510a 	andls	r5, ip, #-2147483646	; 0x80000002
d00227e0:	72fff240 	rscsvc	pc, pc, #64, 4
d00227e4:	0313f3c3 	tsteq	r3, #201326595	; 0xc000003	; <UNPREDICTABLE>
d00227e8:	42919116 	addsmi	r9, r1, #-2147483643	; 0x80000005
d00227ec:	f000930d 			; <UNDEFINED> instruction: 0xf000930d
d00227f0:	9b16817c 	blls	0xd05c2de8
d00227f4:	bf142b00 	svclt	0x00142b00
d00227f8:	22002201 	andcs	r2, r0, #268435456	; 0x10000000
d00227fc:	f0009217 			; <UNDEFINED> instruction: 0xf0009217
d0022800:	f2a38161 	vmla.f32	d8, d3, d1[1]
d0022804:	2b0033ff 	blcs	0xd002f808
d0022808:	bfb8931a 	svclt	0x00b8931a
d002280c:	9312425b 	tstls	r2, #-1342177275	; 0xb0000005
d0022810:	f0001c78 			; <UNDEFINED> instruction: 0xf0001c78
d0022814:	f5b7818a 			; <UNDEFINED> instruction: 0xf5b7818a
d0022818:	f3405f00 	vpmax.f32	d21, d0, d0
d002281c:	f44f817d 	vst4.16	{d24,d26,d28,d30}, [pc :256]!
d0022820:	e9dd5700 	ldmib	sp, {r8, r9, sl, ip, lr}^
d0022824:	9715230c 	ldrls	r2, [r5, -ip, lsl #6]
d0022828:	230ae9cd 	movwcs	lr, #43469	; 0xa9cd
d002282c:	2100ab22 	tstcs	r0, r2, lsr #22
d0022830:	ee079a12 			; <UNDEFINED> instruction: 0xee079a12
d0022834:	4618ba90 			; <UNDEFINED> instruction: 0x4618ba90
d0022838:	fbaa9321 	blx	0xceac74c6
d002283c:	4694c302 	ldrmi	ip, [r4], r2, lsl #6
d0022840:	3101468e 	smlabbcc	r1, lr, r6, r4
d0022844:	0bd3ea4f 	bleq	0xcf51d188
d0022848:	0f09f1bc 	svceq	0x0009f1bc
d002284c:	038beb0b 	orreq	lr, fp, #11264	; 0x2c00
d0022850:	0343eba2 	movteq	lr, #15266	; 0x3ba2
d0022854:	f103465a 			; <UNDEFINED> instruction: 0xf103465a
d0022858:	b2db0330 	sbcslt	r0, fp, #48, 6	; 0xc0000000
d002285c:	3b01f800 	blcc	0xd00a0864
d0022860:	ee17d8eb 	cdp	8, 1, cr13, cr7, cr11, {7}
d0022864:	931fba90 	tstls	pc, #144, 20	; 0x90000
d0022868:	e080f8cd 	add	pc, r0, sp, asr #17
d002286c:	f0002f00 			; <UNDEFINED> instruction: 0xf0002f00
d0022870:	f00681bd 			; <UNDEFINED> instruction: 0xf00681bd
d0022874:	22040310 	andcs	r0, r4, #16, 6	; 0x40000000
d0022878:	9b14931b 	blls	0xd05474ec
d002287c:	3b009815 	blcc	0xd00488d8
d0022880:	2301bf18 	movwcs	fp, #7960	; 0x1f18
d0022884:	44033302 	strmi	r3, [r3], #-770	; 0xfffffcfe
d0022888:	4413440b 	ldrmi	r4, [r3], #-1035	; 0xfffffbf5
d002288c:	f240429d 	vqsub.s8	d20, d16, d13
d0022890:	f00681b9 			; <UNDEFINED> instruction: 0xf00681b9
d0022894:	f0060101 			; <UNDEFINED> instruction: 0xf0060101
d0022898:	1aea0003 	bne	0xcfaa28ac
d002289c:	0301f081 	movweq	pc, #4225	; 0x1081	; <UNPREDICTABLE>
d00228a0:	901e9116 	andsls	r9, lr, r6, lsl r1
d00228a4:	bf0c2802 	svclt	0x000c2802
d00228a8:	f0032600 			; <UNDEFINED> instruction: 0xf0032600
d00228ac:	92120601 	andsls	r0, r2, #1048576	; 0x100000
d00228b0:	f0002e00 			; <UNDEFINED> instruction: 0xf0002e00
d00228b4:	1e5581a5 	lognedp	f0, f5
d00228b8:	f0002a00 			; <UNDEFINED> instruction: 0xf0002a00
d00228bc:	3d0181b0 	stfccd	f0, [r1, #-704]	; 0xfffffd40
d00228c0:	46582120 	ldrbmi	r2, [r8], -r0, lsr #2
d00228c4:	f8a4f7ff 			; <UNDEFINED> instruction: 0xf8a4f7ff
d00228c8:	d1f81c69 	mvnsle	r1, r9, ror #24
d00228cc:	93162300 	tstls	r6, #0, 6
d00228d0:	2b009b14 	blcs	0xd0049528
d00228d4:	8185f040 	orrhi	pc, r5, r0, asr #32
d00228d8:	46582130 			; <UNDEFINED> instruction: 0x46582130
d00228dc:	f898f7ff 			; <UNDEFINED> instruction: 0xf898f7ff
d00228e0:	46582c41 	ldrbmi	r2, [r8], -r1, asr #24
d00228e4:	2158bf0c 	cmpcs	r8, ip, lsl #30
d00228e8:	f7ff2178 			; <UNDEFINED> instruction: 0xf7ff2178
d00228ec:	9b1ef891 	blls	0xd07e0b38
d00228f0:	d1022b02 	tstle	r2, r2, lsl #22
d00228f4:	f0402e00 			; <UNDEFINED> instruction: 0xf0402e00
d00228f8:	99178195 	ldmdbls	r7, {r0, r2, r4, r7, r8, pc}
d00228fc:	31304658 	teqcc	r0, r8, asr r6
d0022900:	f7ffb2c9 			; <UNDEFINED> instruction: 0xf7ffb2c9
d0022904:	9b15f885 	blls	0xd05a0b20
d0022908:	43139a1b 	tstmi	r3, #110592	; 0x1b000
d002290c:	212ed003 			; <UNDEFINED> instruction: 0x212ed003
d0022910:	f7ff4658 			; <UNDEFINED> instruction: 0xf7ff4658
d0022914:	2c41f87d 	mcrrcs	8, 7, pc, r1, cr13	; <UNPREDICTABLE>
d0022918:	816ff000 	msrhi	SPSR_fsxc, r0
d002291c:	f0002f00 			; <UNDEFINED> instruction: 0xf0002f00
d0022920:	9e08821f 	mcrls	2, 0, r8, cr8, cr15, {0}
d0022924:	250000bb 	strcs	r0, [r0, #-187]	; 0xffffff45
d0022928:	3b049415 	blcc	0xd0147984
d002292c:	e0069314 	and	r9, r6, r4, lsl r3
d0022930:	78193501 	ldmdavc	r9, {r0, r8, sl, ip, sp}
d0022934:	f7ff4658 			; <UNDEFINED> instruction: 0xf7ff4658
d0022938:	42aff86b 	adcmi	pc, pc, #7012352	; 0x6b0000
d002293c:	2d0cd064 	stccs	0, cr13, [ip, #-400]	; 0xfffffe70
d0022940:	dcf54633 	ldclle	6, cr4, [r5], #204	; 0xcc
d0022944:	7185ebc5 	orrvc	lr, r5, r5, asr #23
d0022948:	9c0a9b14 			; <UNDEFINED> instruction: 0x9c0a9b14
d002294c:	460a2f0c 	strmi	r2, [sl], -ip, lsl #30
d0022950:	0181ea4f 	orreq	lr, r1, pc, asr #20
d0022954:	0282eb03 	addeq	lr, r2, #3072	; 0xc00
d0022958:	0330f101 	teqeq	r0, #1073741824	; 0x40000000	; <UNPREDICTABLE>
d002295c:	0110f101 	tsteq	r0, r1, lsl #2	; <UNPREDICTABLE>
d0022960:	0020f1c2 	eoreq	pc, r0, r2, asr #3
d0022964:	0c20f1a2 	stfeqd	f7, [r0], #-648	; 0xfffffd78
d0022968:	f202fa24 	vpmax.s8	d15, d2, d20
d002296c:	f1c39c0b 			; <UNDEFINED> instruction: 0xf1c39c0b
d0022970:	fa040e20 	blx	0xd01261f8
d0022974:	9c0cf000 	stcls	0, cr15, [ip], {-0}
d0022978:	f303fa24 	vpmax.u8	d15, d3, d20
d002297c:	ea429c0d 	b	0xd10c99b8
d0022980:	980d0200 	stmdals	sp, {r9}
d0022984:	fe0efa04 	vseleq.f32	s30, s28, s8
d0022988:	fa209c0b 	blx	0xd08499bc
d002298c:	fa24f101 	blx	0xd095ed98
d0022990:	ea43fc0c 	b	0xd11219c8
d0022994:	dc32030e 	ldcle	3, cr0, [r2], #-56	; 0xffffffc8
d0022998:	020cea42 	andeq	lr, ip, #270336	; 0x42000
d002299c:	030ff002 	movweq	pc, #61442	; 0xf002	; <UNPREDICTABLE>
d00229a0:	e7c54433 			; <UNDEFINED> instruction: 0xe7c54433
d00229a4:	447b4bfb 	ldrbtmi	r4, [fp], #-3067	; 0xfffff405
d00229a8:	e6c49314 			; <UNDEFINED> instruction: 0xe6c49314
d00229ac:	b1373d02 	teqlt	r7, r2, lsl #26
d00229b0:	21203d01 			; <UNDEFINED> instruction: 0x21203d01
d00229b4:	f7ff4658 			; <UNDEFINED> instruction: 0xf7ff4658
d00229b8:	1c6cf82b 	stclne	8, cr15, [ip], #-172	; 0xffffff54
d00229bc:	f8d9d1f8 			; <UNDEFINED> instruction: 0xf8d9d1f8
d00229c0:	46583000 	ldrbmi	r3, [r8], -r0
d00229c4:	78191d1a 	ldmdavc	r9, {r1, r3, r4, r8, sl, fp, ip}
d00229c8:	2000f8c9 	andcs	pc, r0, r9, asr #17
d00229cc:	f820f7ff 			; <UNDEFINED> instruction: 0xf820f7ff
d00229d0:	f016e501 			; <UNDEFINED> instruction: 0xf016e501
d00229d4:	eba50301 	bl	0xce9635e0
d00229d8:	93120504 	tstls	r2, #4, 10	; 0x1000000
d00229dc:	aec2f47f 	mcrge	4, 6, pc, cr2, cr15, {3}	; <UNPREDICTABLE>
d00229e0:	b1351e6e 	teqlt	r5, lr, ror #28
d00229e4:	21203e01 			; <UNDEFINED> instruction: 0x21203e01
d00229e8:	f7ff4658 			; <UNDEFINED> instruction: 0xf7ff4658
d00229ec:	1c73f811 	ldclne	8, cr15, [r3], #-68	; 0xffffffbc
d00229f0:	2c00d1f8 	stfcsd	f5, [r0], {248}	; 0xf8
d00229f4:	aceff43f 	cfstrdge	mvd15, [pc], #252	; 0xd0022af8
d00229f8:	93122300 	tstls	r2, #0, 6
d00229fc:	430be6b2 	movwmi	lr, #46770	; 0xb6b2
d0022a00:	030ff003 	movweq	pc, #61443	; 0xf003	; <UNPREDICTABLE>
d0022a04:	e7934433 			; <UNDEFINED> instruction: 0xe7934433
d0022a08:	2c419c15 	mcrrcs	12, 1, r9, r1, cr5
d0022a0c:	2150bf0c 	cmpcs	r0, ip, lsl #30
d0022a10:	46582170 			; <UNDEFINED> instruction: 0x46582170
d0022a14:	fffcf7fe 			; <UNDEFINED> instruction: 0xfffcf7fe
d0022a18:	9d219b1a 	vstmdbls	r1!, {d9-d21}
d0022a1c:	2b004658 	blcs	0xd0034384
d0022a20:	461c9b20 	ldrmi	r9, [ip], -r0, lsr #22
d0022a24:	212dbfb4 			; <UNDEFINED> instruction: 0x212dbfb4
d0022a28:	f7fe212b 			; <UNDEFINED> instruction: 0xf7fe212b
d0022a2c:	442cfff1 	strtmi	pc, [ip], #-4081	; 0xfffff00f
d0022a30:	e001991f 	and	r9, r1, pc, lsl r9
d0022a34:	1d01f814 	stcne	8, cr15, [r1, #-80]	; 0xffffffb0
d0022a38:	f7fe4658 			; <UNDEFINED> instruction: 0xf7fe4658
d0022a3c:	42a5ffe9 	adcmi	pc, r5, #932	; 0x3a4
d0022a40:	9b16d1f8 	blls	0xd05d7228
d0022a44:	f43f2b00 			; <UNDEFINED> instruction: 0xf43f2b00
d0022a48:	9b12acc6 	blls	0xd04cdd68
d0022a4c:	2b001e5c 	blcs	0xd002a3c4
d0022a50:	acc1f43f 	cfstrdge	mvd15, [r1], {63}	; 0x3f
d0022a54:	21203c01 			; <UNDEFINED> instruction: 0x21203c01
d0022a58:	f7fe4658 			; <UNDEFINED> instruction: 0xf7fe4658
d0022a5c:	1c63ffd9 	stclne	15, cr15, [r3], #-868	; 0xfffffc9c
d0022a60:	e4b8d1f8 	ldrt	sp, [r8], #504	; 0x1f8
d0022a64:	f43f2d00 			; <UNDEFINED> instruction: 0xf43f2d00
d0022a68:	07f2acb6 			; <UNDEFINED> instruction: 0x07f2acb6
d0022a6c:	817af140 	cmnhi	sl, r0, asr #2	; <UNPREDICTABLE>
d0022a70:	e68f1e6c 	str	r1, [pc], ip, ror #28
d0022a74:	e7bc9d12 			; <UNDEFINED> instruction: 0xe7bc9d12
d0022a78:	f8db3b01 			; <UNDEFINED> instruction: 0xf8db3b01
d0022a7c:	2b062008 	blcs	0xd01aaaa4
d0022a80:	e8dfd812 	ldm	pc, {r1, r4, fp, ip, lr, pc}^	; <UNPREDICTABLE>
d0022a84:	014bf013 	cmpeq	fp, r3, lsl r0	; <UNPREDICTABLE>
d0022a88:	00110142 	andseq	r0, r1, r2, asr #2
d0022a8c:	00110007 	andseq	r0, r1, r7
d0022a90:	00070011 	andeq	r0, r7, r1, lsl r0
d0022a94:	3000f8d9 	ldrdcc	pc, [r0], -r9
d0022a98:	1d182100 	ldfnes	f2, [r8, #-0]
d0022a9c:	0000f8c9 	andeq	pc, r0, r9, asr #17
d0022aa0:	e9c3681b 	stmib	r3, {r0, r1, r3, r4, fp, sp, lr}^
d0022aa4:	e4962100 	ldr	r2, [r6], #256	; 0x100
d0022aa8:	3000f8d9 	ldrdcc	pc, [r0], -r9
d0022aac:	f8c91d19 			; <UNDEFINED> instruction: 0xf8c91d19
d0022ab0:	681b1000 	ldmdavs	fp, {ip}
d0022ab4:	e48e601a 	str	r6, [lr], #26
d0022ab8:	9114212d 	tstls	r4, sp, lsr #2
d0022abc:	212be68d 	smlawbcs	fp, sp, r6, lr
d0022ac0:	e68a9114 	pkhbt	r9, sl, r4, lsl #2
d0022ac4:	010ce9dd 	ldrdeq	lr, [ip, -sp]
d0022ac8:	32fef240 	rscscc	pc, lr, #64, 4
d0022acc:	0301ea50 	movweq	lr, #6736	; 0x1a50
d0022ad0:	48af9916 	stmiami	pc!, {r1, r2, r4, r8, fp, ip, pc}	; <UNPREDICTABLE>
d0022ad4:	460bbf0c 	strmi	fp, [fp], -ip, lsl #30
d0022ad8:	93124613 	tstls	r2, #19922944	; 0x1300000
d0022adc:	230ce9dd 	movwcs	lr, #51677	; 0xc9dd
d0022ae0:	460bbf0c 	strmi	fp, [fp], -ip, lsl #30
d0022ae4:	931a4603 	tstls	sl, #3145728	; 0x300000
d0022ae8:	2c41e692 	mcrrcs	6, 9, lr, r1, cr2
d0022aec:	4632462b 	ldrtmi	r4, [r2], -fp, lsr #12
d0022af0:	bf0c4658 	svclt	0x000c4658
d0022af4:	21662146 	cmncs	r6, r6, asr #2
d0022af8:	ed9d9700 	ldc	7, cr9, [sp]
d0022afc:	f7ff0b12 			; <UNDEFINED> instruction: 0xf7ff0b12
d0022b00:	e468f965 	strbt	pc, [r8], #-2405	; 0xfffff69b	; <UNPREDICTABLE>
d0022b04:	463b4631 			; <UNDEFINED> instruction: 0x463b4631
d0022b08:	f8cd462c 			; <UNDEFINED> instruction: 0xf8cd462c
d0022b0c:	9e158048 	cdpls	0, 1, cr8, cr5, cr8, {2}
d0022b10:	461746c8 	ldrmi	r4, [r7], -r8, asr #13
d0022b14:	460d4699 			; <UNDEFINED> instruction: 0x460d4699
d0022b18:	f3402f0c 	vpmax.f32	d18, d0, d12
d0022b1c:	97158090 			; <UNDEFINED> instruction: 0x97158090
d0022b20:	230ce9dd 	movwcs	lr, #51677	; 0xc9dd
d0022b24:	230ae9cd 	movwcs	lr, #43469	; 0xa9cd
d0022b28:	270de680 	strcs	lr, [sp, -r0, lsl #13]
d0022b2c:	46494628 	strbmi	r4, [r9], -r8, lsr #12
d0022b30:	46c12300 	strbmi	r2, [r1], r0, lsl #6
d0022b34:	9615463a 			; <UNDEFINED> instruction: 0x9615463a
d0022b38:	4625469e 			; <UNDEFINED> instruction: 0x4625469e
d0022b3c:	8048f8dd 	ldrdhi	pc, [r8], #-141	; 0xffffff73
d0022b40:	4606460f 	strmi	r4, [r6], -pc, lsl #12
d0022b44:	0c20f1c3 	stfeqd	f7, [r0], #-780	; 0xfffffcf4
d0022b48:	990c980d 	stmdbls	ip, {r0, r2, r3, fp, ip, pc}
d0022b4c:	0420f1a3 	strteq	pc, [r0], #-419	; 0xfffffe5d
d0022b50:	fc0cfa00 	stc2	10, cr15, [ip], {-0}	; <UNPREDICTABLE>
d0022b54:	40e040d9 	ldrdmi	r4, [r0], #9	; <UNPREDICTABLE>
d0022b58:	ea413304 	b	0xd106f770
d0022b5c:	4301010c 	movwmi	r0, #4364	; 0x110c
d0022b60:	010ff001 	tsteq	pc, r1	; <UNPREDICTABLE>
d0022b64:	1e0ae9cd 	vmlsne.f16	s28, s21, s26	; <UNPREDICTABLE>
d0022b68:	010ae9dd 	ldrdeq	lr, [sl, -sp]
d0022b6c:	d1c94301 	bicle	r4, r9, r1, lsl #6
d0022b70:	d1e73a01 	mvnle	r3, r1, lsl #20
d0022b74:	f8cd463b 			; <UNDEFINED> instruction: 0xf8cd463b
d0022b78:	46178048 	ldrmi	r8, [r7], -r8, asr #32
d0022b7c:	469946c8 	ldrmi	r4, [r9], r8, asr #13
d0022b80:	462c4631 			; <UNDEFINED> instruction: 0x462c4631
d0022b84:	460d9e15 			; <UNDEFINED> instruction: 0x460d9e15
d0022b88:	e9dd9715 	ldmib	sp, {r0, r2, r4, r8, r9, sl, ip, pc}^
d0022b8c:	e9cd230c 	stmib	sp, {r2, r3, r8, r9, sp}^
d0022b90:	22012318 	andcs	r2, r1, #24, 6	; 0x60000000
d0022b94:	e9cd2300 	stmib	sp, {r8, r9, sp}^
d0022b98:	22002310 	andcs	r2, r0, #16, 6	; 0x40000000
d0022b9c:	2300f44f 	movwcs	pc, #1103	; 0x44f	; <UNPREDICTABLE>
d0022ba0:	230ee9cd 	movwcs	lr, #59853	; 0xe9cd
d0022ba4:	230ee9dd 	movwcs	lr, #59869	; 0xe9dd
d0022ba8:	0118e9dd 			; <UNDEFINED> instruction: 0x0118e9dd
d0022bac:	bf08428b 	svclt	0x0008428b
d0022bb0:	f0c04282 			; <UNDEFINED> instruction: 0xf0c04282
d0022bb4:	429980c1 	addsmi	r8, r9, #193	; 0xc1
d0022bb8:	4290bf08 	addsmi	fp, r0, #8, 30
d0022bbc:	80b7f000 	adcshi	pc, r7, r0
d0022bc0:	230ae9dd 	movwcs	lr, #43485	; 0xa9dd
d0022bc4:	0110e9dd 			; <UNDEFINED> instruction: 0x0110e9dd
d0022bc8:	bf08428b 	svclt	0x0008428b
d0022bcc:	f47f4282 			; <UNDEFINED> instruction: 0xf47f4282
d0022bd0:	9b17ae2d 	blls	0xd060e48c
d0022bd4:	33012200 	movwcc	r2, #4608	; 0x1200
d0022bd8:	23009317 	movwcs	r9, #791	; 0x317
d0022bdc:	230ae9cd 	movwcs	lr, #43469	; 0xa9cd
d0022be0:	4619e624 	ldrmi	lr, [r9], -r4, lsr #12
d0022be4:	f7fe4658 			; <UNDEFINED> instruction: 0xf7fe4658
d0022be8:	e675ff13 	uhadd16	pc, r5, r3	; <UNPREDICTABLE>
d0022bec:	0310f016 	tsteq	r0, #22	; <UNPREDICTABLE>
d0022bf0:	2204bf14 	andcs	fp, r4, #20, 30	; 0x50
d0022bf4:	931b2203 	tstls	fp, #805306368	; 0x30000000
d0022bf8:	b177e63f 	cmnlt	r7, pc, lsr r6
d0022bfc:	e6919e09 	ldr	r9, [r1], r9, lsl #28
d0022c00:	e665461e 			; <UNDEFINED> instruction: 0xe665461e
d0022c04:	0203f006 	andeq	pc, r3, #6
d0022c08:	0301f006 	movweq	pc, #4102	; 0x1006	; <UNPREDICTABLE>
d0022c0c:	2200921e 	andcs	r9, r0, #-536870911	; 0xe0000001
d0022c10:	0601f083 	streq	pc, [r1], -r3, lsl #1
d0022c14:	92129316 	andsls	r9, r2, #1476395008	; 0x58000000
d0022c18:	2150e65a 	cmpcs	r0, sl, asr r6
d0022c1c:	9b12e6f9 	blls	0xd04dc808
d0022c20:	e6559316 			; <UNDEFINED> instruction: 0xe6559316
d0022c24:	1e5d9b12 	vmovne.s8	r9, d13[0]
d0022c28:	f43f2b00 			; <UNDEFINED> instruction: 0xf43f2b00
d0022c2c:	3d01ae66 	stccc	14, cr10, [r1, #-408]	; 0xfffffe68
d0022c30:	46582130 			; <UNDEFINED> instruction: 0x46582130
d0022c34:	feecf7fe 	mcr2	7, 7, pc, cr12, cr14, {7}	; <UNPREDICTABLE>
d0022c38:	d1f81c6a 	mvnsle	r1, sl, ror #24
d0022c3c:	f1c7e65d 			; <UNDEFINED> instruction: 0xf1c7e65d
d0022c40:	e9dd030d 	ldmib	sp, {r0, r2, r3, r8, r9}^
d0022c44:	009b120c 	addseq	r1, fp, ip, lsl #4
d0022c48:	f1c34618 			; <UNDEFINED> instruction: 0xf1c34618
d0022c4c:	f1a30c20 			; <UNDEFINED> instruction: 0xf1a30c20
d0022c50:	460b0e20 	strmi	r0, [fp], -r0, lsr #28
d0022c54:	fc0cfa02 	stc2	10, cr15, [ip], {2}	; <UNPREDICTABLE>
d0022c58:	32fff04f 	rscscc	pc, pc, #79	; 0x4f
d0022c5c:	f1a040c3 			; <UNDEFINED> instruction: 0xf1a040c3
d0022c60:	930a0120 	movwls	r0, #41248	; 0xa120
d0022c64:	33fff04f 	mvnscc	pc, #79	; 0x4f
d0022c68:	fe0efa03 	vseleq.f32	s30, s28, s6
d0022c6c:	f300fa02 	vpmax.u8	d15, d0, d2
d0022c70:	ea429a0a 	b	0xd10c94a0
d0022c74:	f1c0020c 			; <UNDEFINED> instruction: 0xf1c0020c
d0022c78:	920a0c20 	andls	r0, sl, #32, 24	; 0x2000
d0022c7c:	fa229a0d 	blx	0xd08c94b8
d0022c80:	ea43f101 	b	0xd111f08c
d0022c84:	f04f020e 			; <UNDEFINED> instruction: 0xf04f020e
d0022c88:	fa2333ff 	blx	0xd08efc8c
d0022c8c:	4603fc0c 	strmi	pc, [r3], -ip, lsl #24
d0022c90:	30fff04f 	rscscc	pc, pc, pc, asr #32
d0022c94:	0e21f1a3 	abseqdp	f7, f3
d0022c98:	40989315 	addsmi	r9, r8, r5, lsl r3
d0022c9c:	ea429b0a 	b	0xd10c98cc
d0022ca0:	430b020c 	movwmi	r0, #45580	; 0xb20c
d0022ca4:	921b2101 	andsls	r2, fp, #1073741824	; 0x40000000
d0022ca8:	9b0c930a 	blls	0xd03478d8
d0022cac:	ea239a15 	b	0xd0909508
d0022cb0:	00b80300 	adcseq	r0, r8, r0, lsl #6
d0022cb4:	0c21f1c2 	stfeqd	f7, [r1], #-776	; 0xfffffcf8
d0022cb8:	93189715 	tstls	r8, #5505024	; 0x540000
d0022cbc:	f30efa01 	vpmax.u8	d15, d14, d1
d0022cc0:	0e20f1a0 	abseqdp	f7, f0
d0022cc4:	fc0cfa21 	stc2	10, cr15, [ip], {33}	; 0x21	; <UNPREDICTABLE>
d0022cc8:	9b0d930f 	blls	0xd038790c
d0022ccc:	930b40d3 	movwls	r4, #45267	; 0xb0d3
d0022cd0:	f30efa01 	vpmax.u8	d15, d14, d1
d0022cd4:	0e20f1c0 	abseqdm	f7, f0
d0022cd8:	9b0f9311 	blls	0xd0407924
d0022cdc:	fe0efa21 	vseleq.f32	s30, s28, s3
d0022ce0:	030cea43 	movweq	lr, #51779	; 0xca43
d0022ce4:	3cfff102 	ldfccp	f7, [pc], #8	; 0xd0022cf4
d0022ce8:	930f9a1b 	movwls	r9, #64027	; 0xfa1b
d0022cec:	ea239b0d 	b	0xd0909928
d0022cf0:	fa010202 	blx	0xd0063500
d0022cf4:	930ef30c 	movwls	pc, #58124	; 0xe30c	; <UNPREDICTABLE>
d0022cf8:	92199b11 	andsls	r9, r9, #17408	; 0x4400
d0022cfc:	030eea43 	movweq	lr, #59971	; 0xea43
d0022d00:	fa019311 	blx	0xd008794c
d0022d04:	9310f300 	tstls	r0, #0, 6	; <UNPREDICTABLE>
d0022d08:	f8d9e74c 			; <UNDEFINED> instruction: 0xf8d9e74c
d0022d0c:	1d193000 	ldcne	0, cr3, [r9, #-0]
d0022d10:	1000f8c9 	andne	pc, r0, r9, asr #17
d0022d14:	801a681b 	andshi	r6, sl, fp, lsl r8
d0022d18:	bb5df7ff 	bllt	0xd17a0d1c
d0022d1c:	3000f8d9 	ldrdcc	pc, [r0], -r9
d0022d20:	f8c91d19 			; <UNDEFINED> instruction: 0xf8c91d19
d0022d24:	681b1000 	ldmdavs	fp, {ip}
d0022d28:	f7ff701a 			; <UNDEFINED> instruction: 0xf7ff701a
d0022d2c:	b95fbb54 	ldmdblt	pc, {r2, r4, r6, r8, r9, fp, ip, sp, pc}^	; <UNPREDICTABLE>
d0022d30:	2b009b16 	blcs	0xd0049990
d0022d34:	af44f43f 	svcge	0x0044f43f
d0022d38:	33019b0a 	movwcc	r9, #6922	; 0x1b0a
d0022d3c:	9b0b930a 	blls	0xd030796c
d0022d40:	0300f143 	movweq	pc, #323	; 0x143	; <UNPREDICTABLE>
d0022d44:	e73b930b 	ldr	r9, [fp, -fp, lsl #6]!
d0022d48:	f0039b0a 			; <UNDEFINED> instruction: 0xf0039b0a
d0022d4c:	931c0301 	tstls	ip, #67108864	; 0x4000000
d0022d50:	931d2300 	tstls	sp, #0, 6
d0022d54:	231ce9dd 	tstcs	ip, #3620864	; 0x374000
d0022d58:	f43f4313 			; <UNDEFINED> instruction: 0xf43f4313
d0022d5c:	e7ebaf31 			; <UNDEFINED> instruction: 0xe7ebaf31
d0022d60:	e6562170 			; <UNDEFINED> instruction: 0xe6562170
d0022d64:	24001e6e 	strcs	r1, [r0], #-3694	; 0xfffff192
d0022d68:	f8d9e63c 			; <UNDEFINED> instruction: 0xf8d9e63c
d0022d6c:	23000000 	movwcs	r0, #0
d0022d70:	30046802 	andcc	r6, r4, r2, lsl #16
d0022d74:	0000f8c9 	andeq	pc, r0, r9, asr #17
d0022d78:	bb1bf7ff 	bllt	0xd0720d7c
d0022d7c:	3000f8d9 	ldrdcc	pc, [r0], -r9
d0022d80:	33046818 	movwcc	r6, #18456	; 0x4818
d0022d84:	f8c917c1 			; <UNDEFINED> instruction: 0xf8c917c1
d0022d88:	f7ff3000 			; <UNDEFINED> instruction: 0xf7ff3000
d0022d8c:	bf00bb58 	svclt	0x0000bb58
d0022d90:	fffffc02 			; <UNDEFINED> instruction: 0xfffffc02
d0022d94:	fffff88e 			; <UNDEFINED> instruction: 0xfffff88e

Disassembly of section .text.vsnprintf:

d0022d98 <.text.vsnprintf>:
d0022d98:	b0a7b5f0 	strdlt	fp, [r7], r0	; <UNPREDICTABLE>
d0022d9c:	460e4607 	strmi	r4, [lr], -r7, lsl #12
d0022da0:	4614461d 			; <UNDEFINED> instruction: 0x4614461d
d0022da4:	228c2100 	addcs	r2, ip, #0, 2
d0022da8:	f7fea803 			; <UNDEFINED> instruction: 0xf7fea803
d0022dac:	9701fc31 	smuadxls	r1, r1, ip
d0022db0:	95009602 	strls	r9, [r0, #-1538]	; 0xfffff9fe
d0022db4:	4621b134 			; <UNDEFINED> instruction: 0x4621b134
d0022db8:	a801466a 	stmdage	r1, {r1, r3, r5, r6, r9, sl, lr}
d0022dbc:	fa54f7ff 	blx	0xd1560dc0
d0022dc0:	bdf0b027 	ldcllt	0, cr11, [r0, #156]!	; 0x9c
d0022dc4:	30fff04f 	rscscc	pc, pc, pc, asr #32
d0022dc8:	bf00e7fa 	svclt	0x0000e7fa

Disassembly of section .text.snprintf:

d0022dcc <.text.snprintf>:
d0022dcc:	b500b40c 	strlt	fp, [r0, #-1036]	; 0xfffffbf4
d0022dd0:	ab04b083 	blge	0xd014efe4
d0022dd4:	2b04f853 	blcs	0xd0160f28
d0022dd8:	f7ff9301 			; <UNDEFINED> instruction: 0xf7ff9301
d0022ddc:	b003ffdd 	ldrdlt	pc, [r3], -sp
d0022de0:	eb04f85d 	bl	0xd0160f5c
d0022de4:	4770b002 	ldrbmi	fp, [r0, -r2]!

Disassembly of section .text.memchr:

d0022e10 <.text.memchr>:
d0022e10:	4603b192 			; <UNDEFINED> instruction: 0x4603b192
d0022e14:	b410b2c9 	ldrlt	fp, [r0], #-713	; 0xfffffd37
d0022e18:	e0011884 	and	r1, r1, r4, lsl #17
d0022e1c:	d00742a3 	andle	r4, r7, r3, lsr #5
d0022e20:	f8134618 			; <UNDEFINED> instruction: 0xf8134618
d0022e24:	428a2b01 	addmi	r2, sl, #1024	; 0x400
d0022e28:	f85dd1f8 			; <UNDEFINED> instruction: 0xf85dd1f8
d0022e2c:	47704b04 	ldrbmi	r4, [r0, -r4, lsl #22]!
d0022e30:	f85d2000 			; <UNDEFINED> instruction: 0xf85d2000
d0022e34:	47704b04 	ldrbmi	r4, [r0, -r4, lsl #22]!
d0022e38:	47704610 			; <UNDEFINED> instruction: 0x47704610

Disassembly of section .text.strlen:

d0022e3c <.text.strlen>:
d0022e3c:	b1327802 	teqlt	r2, r2, lsl #16
d0022e40:	f8134603 			; <UNDEFINED> instruction: 0xf8134603
d0022e44:	29001f01 	stmdbcs	r0, {r0, r8, r9, sl, fp, ip}
d0022e48:	1a18d1fb 	bne	0xd065763c
d0022e4c:	46104770 			; <UNDEFINED> instruction: 0x46104770
d0022e50:	bf004770 	svclt	0x00004770

Disassembly of section .text.strcmp:

d0022e54 <.text.strcmp>:
d0022e54:	b1937803 	orrslt	r7, r3, r3, lsl #16
d0022e58:	e002b410 	and	fp, r2, r0, lsl r4
d0022e5c:	3f01f810 	svccc	0x0001f810
d0022e60:	460cb143 	strmi	fp, [ip], -r3, asr #2
d0022e64:	2b01f811 	blcs	0xd00a0eb0
d0022e68:	d0f7429a 	smlalsle	r4, r7, sl, r2
d0022e6c:	f85d1a98 			; <UNDEFINED> instruction: 0xf85d1a98
d0022e70:	47704b04 	ldrbmi	r4, [r0, -r4, lsl #22]!
d0022e74:	f85d7862 			; <UNDEFINED> instruction: 0xf85d7862
d0022e78:	1a984b04 	bne	0xce635a90
d0022e7c:	780a4770 	stmdavc	sl, {r4, r5, r6, r8, r9, sl, lr}
d0022e80:	47701a98 			; <UNDEFINED> instruction: 0x47701a98

Disassembly of section .text.strchr:

d0022e84 <.text.strchr>:
d0022e84:	7803b2c9 	stmdavc	r3, {r0, r3, r6, r7, r9, ip, sp, pc}
d0022e88:	d0064299 	mulle	r6, r9, r2
d0022e8c:	f810b123 			; <UNDEFINED> instruction: 0xf810b123
d0022e90:	428b3f01 	addmi	r3, fp, #1, 30
d0022e94:	4770d1fa 			; <UNDEFINED> instruction: 0x4770d1fa
d0022e98:	47704618 			; <UNDEFINED> instruction: 0x47704618

Disassembly of section .text.strrchr:

d0022e9c <.text.strrchr>:
d0022e9c:	b2c92200 	sbclt	r2, r9, #0, 4
d0022ea0:	4604b410 			; <UNDEFINED> instruction: 0x4604b410
d0022ea4:	3b01f810 	blcc	0xd00a0eec
d0022ea8:	bf08428b 	svclt	0x0008428b
d0022eac:	2b004622 	blcs	0xd003473c
d0022eb0:	4610d1f7 			; <UNDEFINED> instruction: 0x4610d1f7
d0022eb4:	4b04f85d 	blmi	0xd0161030
d0022eb8:	bf004770 	svclt	0x00004770
