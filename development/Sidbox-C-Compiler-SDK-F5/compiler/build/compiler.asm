
/mnt/LinuxDatas/work/SidboxIDE/SidboxIDE/development/Sidbox-C-Compiler-SDK-F5/compiler/build/cgarm/compiler-cgarm/compiler.elf:     file format elf32-littlearm


Disassembly of section .text.show_status:

d001f858 <.text.show_status>:
d001f858:	46024b0d 	strmi	r4, [r2], -sp, lsl #22
d001f85c:	b513447b 	ldrlt	r4, [r3, #-1147]	; 0xfffffb85
d001f860:	4c0a6818 	stcmi	8, cr6, [sl], {24}
d001f864:	68a3b138 	stmiavs	r3!, {r3, r4, r5, r8, ip, sp, pc}
d001f868:	92014611 	andls	r4, r1, #17825792	; 0x1100000
d001f86c:	f8d368db 			; <UNDEFINED> instruction: 0xf8d368db
d001f870:	479830c4 	ldrmi	r3, [r8, r4, asr #1]
d001f874:	68a39a01 	stmiavs	r3!, {r0, r9, fp, ip, pc}
d001f878:	49062000 	stmdbmi	r6, {sp}
d001f87c:	4479681b 	ldrbtmi	r6, [r9], #-2075	; 0xfffff7e5
d001f880:	b002681b 	andlt	r6, r2, fp, lsl r8
d001f884:	4010e8bd 			; <UNDEFINED> instruction: 0x4010e8bd
d001f888:	bf004718 	svclt	0x00004718
d001f88c:	2001f000 	andcs	pc, r1, r0
d001f890:	00154b18 	andseq	r4, r5, r8, lsl fp
d001f894:	ffffffd2 			; <UNDEFINED> instruction: 0xffffffd2

Disassembly of section .text.read_file:

d001f898 <.text.read_file>:
d001f898:	41ffe92d 	mvnsmi	lr, sp, lsr #18
d001f89c:	4b1a461e 	blmi	0xd06b111c
d001f8a0:	4690460f 	ldrmi	r4, [r0], pc, lsl #12
d001f8a4:	aa01685b 	bge	0xd0079a18
d001f8a8:	681d2101 	ldmdavs	sp, {r0, r8, sp}
d001f8ac:	47986bab 	ldrmi	r6, [r8, fp, lsr #23]
d001f8b0:	4604b120 	strmi	fp, [r4], -r0, lsr #2
d001f8b4:	b0044620 	andlt	r4, r4, r0, lsr #12
d001f8b8:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d001f8bc:	0002e9cd 	andeq	lr, r2, sp, asr #19
d001f8c0:	a9026ceb 	stmdbge	r2, {r0, r1, r3, r5, r6, r7, sl, fp, sp, lr}
d001f8c4:	47989801 	ldrmi	r9, [r8, r1, lsl #16]
d001f8c8:	b9784604 	ldmdblt	r8!, {r2, r9, sl, lr}^
d001f8cc:	45429a02 	strbmi	r9, [r2, #-2562]	; 0xfffff5fe
d001f8d0:	b15ad817 	cmplt	sl, r7, lsl r8
d001f8d4:	ab036bec 	blge	0xd00fa88c
d001f8d8:	98014639 	stmdals	r1, {r0, r3, r4, r5, r9, sl, lr}
d001f8dc:	460447a0 	strmi	r4, [r4], -r0, lsr #15
d001f8e0:	e9ddb920 	ldmib	sp, {r5, r8, fp, ip, sp, pc}^
d001f8e4:	1a240402 	bne	0xd09208f4
d001f8e8:	2401bf18 	strcs	fp, [r1], #-3864	; 0xfffff0e8
d001f8ec:	98016d6b 	stmdals	r1, {r0, r1, r3, r5, r6, r8, sl, fp, sp, lr}
d001f8f0:	2c004798 	stccs	7, cr4, [r0], {152}	; 0x98
d001f8f4:	4604d1de 			; <UNDEFINED> instruction: 0x4604d1de
d001f8f8:	d1db2800 	bicsle	r2, fp, r0, lsl #16
d001f8fc:	60339b02 	eorsvs	r9, r3, r2, lsl #22
d001f900:	f06fe7d8 			; <UNDEFINED> instruction: 0xf06fe7d8
d001f904:	e7f10402 	ldrb	r0, [r1, r2, lsl #8]!
d001f908:	2001f000 	andcs	pc, r1, r0

Disassembly of section .text.read_apicore:

d001f92c <.text.read_apicore>:
d001f92c:	460ab507 	strmi	fp, [sl], -r7, lsl #10
d001f930:	48064601 	stmdami	r6, {r0, r9, sl, lr}
d001f934:	4478ab01 	ldrbtmi	sl, [r8], #-2817	; 0xfffff4ff
d001f938:	ffaef7ff 			; <UNDEFINED> instruction: 0xffaef7ff
d001f93c:	9801b918 	stmdals	r1, {r3, r4, r8, fp, ip, sp, pc}
d001f940:	f85db003 			; <UNDEFINED> instruction: 0xf85db003
d001f944:	2000fb04 	andcs	pc, r0, r4, lsl #22
d001f948:	bf00e7fa 	svclt	0x0000e7fa
d001f94c:	ffffffd2 			; <UNDEFINED> instruction: 0xffffffd2

Disassembly of section .text.open_editor:

d001f9c8 <.text.open_editor>:
d001f9c8:	47ffe92d 	ldrbmi	lr, [pc, sp, lsr #18]!
d001f9cc:	f2404c5d 	vfma.f32	q10, q0, <illegal reg q6.5>
d001f9d0:	4607324d 	strmi	r3, [r7], -sp, asr #4
d001f9d4:	68a3210c 	stmiavs	r3!, {r2, r3, r8, sp}
d001f9d8:	685b2000 	ldmdavs	fp, {sp}^
d001f9dc:	4a5a9202 	bmi	0xd16c41ec
d001f9e0:	9201447a 	andls	r4, r1, #2046820352	; 0x7a000000
d001f9e4:	728ef44f 	addvc	pc, lr, #1325400064	; 0x4f000000
d001f9e8:	22119200 	andscs	r9, r1, #0, 4
d001f9ec:	f44f681d 	vst2.8	{d22-d23}, [pc :64]!
d001f9f0:	47a873e4 	strmi	r7, [r8, r4, ror #7]!
d001f9f4:	46051e43 	strmi	r1, [r5], -r3, asr #28
d001f9f8:	2bfdb2db 	blcs	0xcff8c56c
d001f9fc:	4853d907 	ldmdami	r3, {r0, r1, r2, r8, fp, ip, lr, pc}^
d001fa00:	f7ff4478 			; <UNDEFINED> instruction: 0xf7ff4478
d001fa04:	2001ff29 	andcs	pc, r1, r9, lsr #30
d001fa08:	e8bdb004 	pop	{r2, ip, sp, pc}
d001fa0c:	4e5087f0 	mrcmi	7, 2, r8, cr0, cr0, {7}
d001fa10:	447e212f 	ldrbtmi	r2, [lr], #-303	; 0xfffffed1
d001fa14:	f0024630 			; <UNDEFINED> instruction: 0xf0024630
d001fa18:	68a2feb9 	stmiavs	r2!, {r0, r3, r4, r5, r7, r9, sl, fp, ip, sp, lr, pc}
d001fa1c:	68d24603 	ldmvs	r2, {r0, r1, r9, sl, lr}^
d001fa20:	8018f8d2 			; <UNDEFINED> instruction: 0x8018f8d2
d001fa24:	d07a2800 	rsbsle	r2, sl, r0, lsl #16
d001fa28:	26013301 	strcs	r3, [r1], -r1, lsl #6
d001fa2c:	23109301 	tstcs	r0, #67108864	; 0x4000000
d001fa30:	21082209 	tstcs	r8, r9, lsl #4
d001fa34:	93004628 	movwls	r4, #1576	; 0x628
d001fa38:	7387f44f 	orrvc	pc, r7, #1325400064	; 0x4f000000
d001fa3c:	f04f9602 			; <UNDEFINED> instruction: 0xf04f9602
d001fa40:	47c00918 	bfimi	r0, r8, (invalid: 18:0)
d001fa44:	4a4368a3 	bmi	0xd10f9cd8
d001fa48:	718ff44f 	orrvc	pc, pc, pc, asr #8
d001fa4c:	468068db 	pkhtbmi	r6, r0, fp, asr #17
d001fa50:	f8cd447a 			; <UNDEFINED> instruction: 0xf8cd447a
d001fa54:	96029000 	strls	r9, [r2], -r0
d001fa58:	92014628 	andls	r4, r1, #40, 12	; 0x2800000
d001fa5c:	f8d32204 			; <UNDEFINED> instruction: 0xf8d32204
d001fa60:	2344a008 	movtcs	sl, #16392	; 0x4008
d001fa64:	4b3c47d0 	blmi	0xd0f319ac
d001fa68:	f44f4a3c 	vst1.8	{d20-d21}, [pc :256], ip
d001fa6c:	447b71b4 	ldrbtmi	r7, [fp], #-436	; 0xfffffe4c
d001fa70:	6018447a 	andsvs	r4, r8, sl, ror r4
d001fa74:	68a34628 	stmiavs	r3!, {r3, r5, r9, sl, lr}
d001fa78:	920168db 	andls	r6, r1, #14352384	; 0xdb0000
d001fa7c:	96022204 	strls	r2, [r2], -r4, lsl #4
d001fa80:	9000f8cd 	andls	pc, r0, sp, asr #17
d001fa84:	9008f8d3 	ldrdls	pc, [r8], -r3
d001fa88:	47c8234e 	strbmi	r2, [r8, lr, asr #6]
d001fa8c:	22004b34 	andcs	r4, r0, #52, 22	; 0xd000
d001fa90:	447b2108 	ldrbtmi	r2, [fp], #-264	; 0xfffffef8
d001fa94:	46286018 			; <UNDEFINED> instruction: 0x46286018
d001fa98:	68db68a3 	ldmvs	fp, {r0, r1, r5, r7, fp, sp, lr}^
d001fa9c:	4a319202 	bmi	0xd0c842ac
d001faa0:	447a9603 	ldrbtmi	r9, [sl], #-1539	; 0xfffff9fd
d001faa4:	22c19201 	sbccs	r9, r1, #268435456	; 0x10000000
d001faa8:	22229200 	eorcs	r9, r2, #0, 4
d001faac:	9034f8d3 	ldrsbtls	pc, [r4], -r3	; <UNPREDICTABLE>
d001fab0:	73d7f44f 	bicsvc	pc, r7, #1325400064	; 0x4f000000
d001fab4:	4b2c47c8 	blmi	0xd0b319dc
d001fab8:	6018447b 	andsvs	r4, r8, fp, ror r4
d001fabc:	68db68a3 	ldmvs	fp, {r0, r1, r5, r7, fp, sp, lr}^
d001fac0:	9018f8d3 			; <UNDEFINED> instruction: 0x9018f8d3
d001fac4:	d12c2f00 			; <UNDEFINED> instruction: 0xd12c2f00
d001fac8:	447b4b28 	ldrbtmi	r4, [fp], #-2856	; 0xfffff4d8
d001facc:	23129301 	tstcs	r2, #67108864	; 0x4000000
d001fad0:	210822eb 	smlattcs	r8, fp, r2, r2
d001fad4:	46289300 	strtmi	r9, [r8], -r0, lsl #6
d001fad8:	73d7f44f 	bicsvc	pc, r7, #1325400064	; 0x4f000000
d001fadc:	47c89602 	strbmi	r9, [r8, r2, lsl #12]
d001fae0:	447b4b23 	ldrbtmi	r4, [fp], #-2851	; 0xfffff4dd
d001fae4:	f1b86018 			; <UNDEFINED> instruction: 0xf1b86018
d001fae8:	d00c0f00 	andle	r0, ip, r0, lsl #30
d001faec:	447b4b21 	ldrbtmi	r4, [fp], #-2849	; 0xfffff4df
d001faf0:	b143681b 	cmplt	r3, fp, lsl r8
d001faf4:	447b4b20 	ldrbtmi	r4, [fp], #-2848	; 0xfffff4e0
d001faf8:	b123681b 			; <UNDEFINED> instruction: 0xb123681b
d001fafc:	447e4e1f 	ldrbtmi	r4, [lr], #-3615	; 0xfffff1e1
d001fb00:	b1036833 	tstlt	r3, r3, lsr r8
d001fb04:	68a3b980 	stmiavs	r3!, {r7, r8, fp, ip, sp, pc}
d001fb08:	685b4628 	ldmdavs	fp, {r3, r5, r9, sl, lr}^
d001fb0c:	4798685b 			; <UNDEFINED> instruction: 0x4798685b
d001fb10:	22004b1b 	andcs	r4, r0, #27648	; 0x6c00
d001fb14:	447b481b 	ldrbtmi	r4, [fp], #-2075	; 0xfffff7e5
d001fb18:	601a4478 	andsvs	r4, sl, r8, ror r4
d001fb1c:	4633e771 			; <UNDEFINED> instruction: 0x4633e771
d001fb20:	4b19e783 	blmi	0xd0699934
d001fb24:	e7d1447b 			; <UNDEFINED> instruction: 0xe7d1447b
d001fb28:	462868a3 	strtmi	r6, [r8], -r3, lsr #17
d001fb2c:	685b4917 	ldmdavs	fp, {r0, r1, r2, r4, r8, fp, lr}^
d001fb30:	689b4479 	ldmvs	fp, {r0, r3, r4, r5, r6, sl, lr}
d001fb34:	68a34798 	stmiavs	r3!, {r3, r4, r7, r8, r9, sl, lr}
d001fb38:	68db6830 	ldmvs	fp, {r4, r5, fp, sp, lr}^
d001fb3c:	47986ddb 			; <UNDEFINED> instruction: 0x47986ddb
d001fb40:	e7612000 	strb	r2, [r1, -r0]!
d001fb44:	2001f000 	andcs	pc, r1, r0
d001fb48:	ffffff8a 			; <UNDEFINED> instruction: 0xffffff8a
d001fb4c:	ffffff73 			; <UNDEFINED> instruction: 0xffffff73
d001fb50:	001545e2 	andseq	r4, r5, r2, ror #11
d001fb54:	ffffff3f 			; <UNDEFINED> instruction: 0xffffff3f
d001fb58:	00054572 	andeq	r4, r5, r2, ror r5
d001fb5c:	ffffff24 			; <UNDEFINED> instruction: 0xffffff24
d001fb60:	000534c2 	andeq	r3, r5, r2, asr #9
d001fb64:	00054542 	andeq	r4, r5, r2, asr #10
d001fb68:	000534a0 	andeq	r3, r5, r0, lsr #9
d001fb6c:	fffffe92 			; <UNDEFINED> instruction: 0xfffffe92
d001fb70:	00154892 	mulseq	r5, r2, r8
d001fb74:	000544f2 	strdeq	r4, [r5], -r2
d001fb78:	0005345e 	andeq	r3, r5, lr, asr r4
d001fb7c:	0005345a 	andeq	r3, r5, sl, asr r4
d001fb80:	0015485e 	andseq	r4, r5, lr, asr r8
d001fb84:	fffffe82 			; <UNDEFINED> instruction: 0xfffffe82
d001fb88:	fffffe28 			; <UNDEFINED> instruction: 0xfffffe28
d001fb8c:	00000bb5 			; <UNDEFINED> instruction: 0x00000bb5

Disassembly of section .text.stream_open_file:

d001fb90 <.text.stream_open_file>:
d001fb90:	4e0cb570 	cfrshl64mi	mvdx12, mvdx0, fp
d001fb94:	f241460c 	vmax.s8	d20, d1, d12
d001fb98:	21000218 	tstcs	r0, r8, lsl r2
d001fb9c:	f0014605 			; <UNDEFINED> instruction: 0xf0014605
d001fba0:	6873f9ad 	ldmdavs	r3!, {r0, r2, r3, r5, r7, r8, fp, ip, sp, lr, pc}^
d001fba4:	681b4620 	ldmdavs	fp, {r5, r9, sl, lr}
d001fba8:	47986d9b 			; <UNDEFINED> instruction: 0x47986d9b
d001fbac:	462a6873 			; <UNDEFINED> instruction: 0x462a6873
d001fbb0:	681b2107 	ldmdavs	fp, {r0, r1, r2, r8, sp}
d001fbb4:	6b9b4620 	blvs	0xce6f143c
d001fbb8:	fab04798 	blx	0xcec31a20
d001fbbc:	0940f080 	stmdbeq	r0, {r7, ip, sp, lr, pc}^
d001fbc0:	bf00bd70 	svclt	0x0000bd70
d001fbc4:	2001f000 	andcs	pc, r1, r0

Disassembly of section .text.console_compile_progress:

d001fbf4 <.text.console_compile_progress>:
d001fbf4:	43f7e92d 	mvnsmi	lr, #737280	; 0xb4000
d001fbf8:	46184c23 	ldrmi	r4, [r8], -r3, lsr #24
d001fbfc:	2b0068a3 	blcs	0xd0039e90
d001fc00:	68a3d03e 	stmiavs	r3!, {r1, r2, r3, r4, r5, ip, lr, pc}
d001fc04:	2b00681b 	blcs	0xd0039c78
d001fc08:	b998d03a 	ldmiblt	r8, {r1, r3, r4, r5, ip, lr, pc}
d001fc0c:	460a68a3 	strmi	r6, [sl], -r3, lsr #17
d001fc10:	681b491e 	ldmdavs	fp, {r1, r2, r3, r4, r8, fp, lr}
d001fc14:	681b4479 	ldmdavs	fp, {r0, r3, r4, r5, r6, sl, lr}
d001fc18:	4b1d4798 	blmi	0xd0771a80
d001fc1c:	681b447b 	ldmdavs	fp, {r0, r1, r3, r4, r5, r6, sl, lr}
d001fc20:	68a3bb73 	stmiavs	r3!, {r0, r1, r4, r5, r6, r8, r9, fp, ip, sp, pc}
d001fc24:	b35b689b 	cmplt	fp, #10158080	; 0x9b0000
d001fc28:	689b68a3 	ldmvs	fp, {r0, r1, r5, r7, fp, sp, lr}
d001fc2c:	e8bdb003 	pop	{r0, r1, ip, sp, pc}
d001fc30:	471843f0 			; <UNDEFINED> instruction: 0x471843f0
d001fc34:	23002564 	movwcs	r2, #1380	; 0x564
d001fc38:	fcf5fbb0 	ldc2l	11, cr15, [r5], #704	; 0x2c0	; <UNPREDICTABLE>
d001fc3c:	fb0546a9 	blx	0xd01716ea
d001fc40:	f1050e1c 			; <UNDEFINED> instruction: 0xf1050e1c
d001fc44:	42ab0801 	adcmi	r0, fp, #65536	; 0x10000
d001fc48:	68a5d30a 	stmiavs	r5!, {r1, r3, r8, r9, ip, lr, pc}
d001fc4c:	9200682d 	andls	r6, r0, #2949120	; 0x2d0000
d001fc50:	4910460a 	ldmdbmi	r0, {r1, r3, r9, sl, lr}
d001fc54:	20009001 	andcs	r9, r0, r1
d001fc58:	4479682d 	ldrbtmi	r6, [r9], #-2093	; 0xfffff7d3
d001fc5c:	e7dc47a8 	ldrb	r4, [ip, r8, lsr #15]
d001fc60:	0703eb08 	streq	lr, [r3, -r8, lsl #22]
d001fc64:	fb07087f 	blx	0xd01e1e6a
d001fc68:	3663f60e 	strbtcc	pc, [r3], -lr, lsl #12	; <UNPREDICTABLE>
d001fc6c:	f6f9fbb6 			; <UNDEFINED> instruction: 0xf6f9fbb6
d001fc70:	660cfb07 	strvs	pc, [ip], -r7, lsl #22
d001fc74:	d20142b2 	andle	r4, r1, #536870923	; 0x2000000b
d001fc78:	e7e21e7d 			; <UNDEFINED> instruction: 0xe7e21e7d
d001fc7c:	e7e2463b 			; <UNDEFINED> instruction: 0xe7e2463b
d001fc80:	e8bdb003 	pop	{r0, r1, ip, sp, pc}
d001fc84:	bf0083f0 	svclt	0x000083f0
d001fc88:	2001f000 	andcs	pc, r1, r0
d001fc8c:	ffffffb0 			; <UNDEFINED> instruction: 0xffffffb0
d001fc90:	0005333c 	andeq	r3, r5, ip, lsr r3
d001fc94:	ffffff78 			; <UNDEFINED> instruction: 0xffffff78

Disassembly of section .text.stream_flush_page.part.0:

d001fc98 <.text.stream_flush_page.part.0>:
d001fc98:	685b4b16 	ldmdavs	fp, {r1, r2, r4, r8, r9, fp, lr}^
d001fc9c:	681fb5f7 	ldmdavs	pc, {r0, r1, r2, r4, r5, r6, r7, r8, sl, ip, sp, pc}	; <UNPREDICTABLE>
d001fca0:	0504f241 	streq	pc, [r4, #-577]	; 0xfffffdbf
d001fca4:	46042300 	strmi	r2, [r4], -r0, lsl #6
d001fca8:	93015941 	movwls	r5, #6465	; 0x1941
d001fcac:	6c7b6800 	ldclvs	8, cr6, [fp], #-0
d001fcb0:	b1104798 			; <UNDEFINED> instruction: 0xb1104798
d001fcb4:	b0032000 	andlt	r2, r3, r0
d001fcb8:	f241bdf0 	vmla.f32	<illegal reg q13.5>, <illegal reg q8.5>, q8
d001fcbc:	6c3f0608 	ldcvs	6, cr0, [pc], #-32	; 0xd001fca4
d001fcc0:	1d21ab01 	fstmdbxne	r1!, {d10-d9}	;@ Deprecated
d001fcc4:	682059a2 	stmdavs	r0!, {r1, r5, r7, r8, fp, ip, lr}
d001fcc8:	280047b8 	stmdacs	r0, {r3, r4, r5, r7, r8, r9, sl, lr}
d001fccc:	59a3d1f2 	stmibpl	r3!, {r1, r4, r5, r6, r7, r8, ip, lr, pc}
d001fcd0:	42939a01 	addsmi	r9, r3, #4096	; 0x1000
d001fcd4:	5962d1ee 	stmdbpl	r2!, {r1, r2, r3, r5, r6, r7, r8, ip, lr, pc}^
d001fcd8:	44132001 	ldrmi	r2, [r3], #-1
d001fcdc:	020cf241 	andeq	pc, ip, #268435460	; 0x10000004
d001fce0:	428b58a1 	addmi	r5, fp, #10551296	; 0xa10000
d001fce4:	50a3bf88 	adcpl	fp, r3, r8, lsl #31
d001fce8:	0314f241 	tsteq	r4, #268435460	; 0x10000004	; <UNPREDICTABLE>
d001fcec:	50e22200 	rscpl	r2, r2, r0, lsl #4
d001fcf0:	bf00e7e1 	svclt	0x0000e7e1
d001fcf4:	2001f000 	andcs	pc, r1, r0

Disassembly of section .text.stream_io_read:

d001fcf8 <.text.stream_io_read>:
d001fcf8:	43f7e92d 	mvnsmi	lr, #737280	; 0xb4000
d001fcfc:	46059f0a 	strmi	r9, [r5], -sl, lsl #30
d001fd00:	46984616 			; <UNDEFINED> instruction: 0x46984616
d001fd04:	f500b161 			; <UNDEFINED> instruction: 0xf500b161
d001fd08:	34185480 	ldrcc	r5, [r8], #-1152	; 0xfffffb80
d001fd0c:	b94b6823 	stmdblt	fp, {r0, r1, r5, fp, sp, lr}^
d001fd10:	1330f242 	teqne	r0, #536870916	; 0x20000004	; <UNPREDICTABLE>
d001fd14:	20002201 	andcs	r2, r0, r1, lsl #4
d001fd18:	b00350ea 	andlt	r5, r3, sl, ror #1
d001fd1c:	83f0e8bd 	mvnshi	lr, #12386304	; 0xbd0000
d001fd20:	e7f34604 	ldrb	r4, [r3, r4, lsl #12]!
d001fd24:	0314f241 	tsteq	r4, #268435460	; 0x10000004	; <UNPREDICTABLE>
d001fd28:	bb1b58e3 	bllt	0xd06f60bc
d001fd2c:	030cf241 	movweq	pc, #49729	; 0xc241	; <UNPREDICTABLE>
d001fd30:	429658e2 	addsmi	r5, r6, #14811136	; 0xe20000
d001fd34:	1b92d8ec 	blne	0xce4d60ec
d001fd38:	d8e94297 	stmiale	r9!, {r0, r1, r2, r4, r7, r9, lr}^
d001fd3c:	4b10b1c7 	blmi	0xd044c460
d001fd40:	68204631 	stmdavs	r0!, {r0, r4, r5, r9, sl, lr}
d001fd44:	f8d3685b 			; <UNDEFINED> instruction: 0xf8d3685b
d001fd48:	23009000 	movwcs	r9, #0
d001fd4c:	f8d99301 			; <UNDEFINED> instruction: 0xf8d99301
d001fd50:	47983044 	ldrmi	r3, [r8, r4, asr #32]
d001fd54:	d1db2800 	bicsle	r2, fp, r0, lsl #16
d001fd58:	603cf8d9 	ldrsbtvs	pc, [ip], -r9	; <UNPREDICTABLE>
d001fd5c:	463aab01 	ldrtmi	sl, [sl], -r1, lsl #22
d001fd60:	68204641 	stmdavs	r0!, {r0, r6, r9, sl, lr}
d001fd64:	280047b0 	stmdacs	r0, {r4, r5, r7, r8, r9, sl, lr}
d001fd68:	9b01d1d2 	blls	0xd00944b8
d001fd6c:	d1cf429f 			; <UNDEFINED> instruction: 0xd1cf429f
d001fd70:	e7d22001 	ldrb	r2, [r2, r1]
d001fd74:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d001fd78:	2800ff8f 	stmdacs	r0, {r0, r1, r2, r3, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d001fd7c:	e7d5d0c8 	ldrb	sp, [r5, r8, asr #1]
d001fd80:	2001f000 	andcs	pc, r1, r0

Disassembly of section .text.report_file.part.0:

d001fe2c <.text.report_file.part.0>:
d001fe2c:	1cc5b537 	cfstr64ne	mvdx11, [r5], {55}	; 0x37
d001fe30:	460b4604 	strmi	r4, [fp], -r4, lsl #12
d001fe34:	4812d108 	ldmdami	r2, {r3, r8, ip, lr, pc}
d001fe38:	f7ff4478 			; <UNDEFINED> instruction: 0xf7ff4478
d001fe3c:	1c63fd0d 	stclne	13, cr15, [r3], #-52	; 0xffffffcc
d001fe40:	41584258 	cmpmi	r8, r8, asr r2
d001fe44:	bd30b003 	ldclt	0, cr11, [r0, #-12]!
d001fe48:	d1021d20 	tstle	r2, r0, lsr #26
d001fe4c:	4478480d 	ldrbtmi	r4, [r8], #-2061	; 0xfffff7f3
d001fe50:	1ca1e7f3 	stcne	7, cr14, [r1], #972	; 0x3cc
d001fe54:	480cd102 	stmdami	ip, {r1, r8, ip, lr, pc}
d001fe58:	e7ee4478 			; <UNDEFINED> instruction: 0xe7ee4478
d001fe5c:	d1021c62 	tstle	r2, r2, ror #24
d001fe60:	4478480a 	ldrbtmi	r4, [r8], #-2058	; 0xfffff7f6
d001fe64:	4d0ae7e9 	stcmi	7, cr14, [sl, #-932]	; 0xfffffc5c
d001fe68:	71c0f44f 	bicvc	pc, r0, pc, asr #8
d001fe6c:	447d4a09 	ldrbtmi	r4, [sp], #-2569	; 0xfffff5f7
d001fe70:	447a9400 	ldrbtmi	r9, [sl], #-1024	; 0xfffffc00
d001fe74:	f0024628 			; <UNDEFINED> instruction: 0xf0024628
d001fe78:	4628fc21 	strtmi	pc, [r8], -r1, lsr #24
d001fe7c:	bf00e7dd 	svclt	0x0000e7dd
d001fe80:	ffffff48 			; <UNDEFINED> instruction: 0xffffff48
d001fe84:	ffffff47 			; <UNDEFINED> instruction: 0xffffff47
d001fe88:	ffffff58 			; <UNDEFINED> instruction: 0xffffff58
d001fe8c:	ffffff7a 			; <UNDEFINED> instruction: 0xffffff7a
d001fe90:	00154386 	andseq	r4, r5, r6, lsl #7
d001fe94:	ffffff99 			; <UNDEFINED> instruction: 0xffffff99

Disassembly of section .text.read_header:

d001fe98 <.text.read_header>:
d001fe98:	47f0e92d 	ldrbmi	lr, [r0, sp, lsr #18]!
d001fe9c:	460d9f09 	strmi	r9, [sp], -r9, lsl #30
d001fea0:	46984616 			; <UNDEFINED> instruction: 0x46984616
d001fea4:	b9104681 	ldmdblt	r0, {r0, r7, r9, sl, lr}
d001fea8:	e8bd2000 	ldmfd	sp!, {sp}
d001feac:	290087f0 	stmdbcs	r0, {r4, r5, r6, r7, r8, r9, sl, pc}
d001feb0:	780bd0fa 	stmdavc	fp, {r1, r3, r4, r5, r6, r7, ip, lr, pc}
d001feb4:	d0f72b00 	rscsle	r2, r7, r0, lsl #22
d001feb8:	d0f52b2f 	rscsle	r2, r5, pc, lsr #22
d001febc:	4628213a 			; <UNDEFINED> instruction: 0x4628213a
d001fec0:	fc58f002 	mrrc2	0, 0, pc, r8, cr2	; <UNPREDICTABLE>
d001fec4:	d1ef2800 	mvnle	r2, r0, lsl #16
d001fec8:	4648212f 	strbmi	r2, [r8], -pc, lsr #2
d001fecc:	fc5ef002 	mrrc2	0, 0, pc, lr, cr2	; <UNPREDICTABLE>
d001fed0:	d0e92800 	rscle	r2, r9, r0, lsl #16
d001fed4:	0409eba0 	streq	lr, [r9], #-2976	; 0xfffff460
d001fed8:	f0024628 			; <UNDEFINED> instruction: 0xf0024628
d001fedc:	9a0afc27 	bls	0xd02def80
d001fee0:	46823401 	strmi	r3, [r2], r1, lsl #8
d001fee4:	429a1823 	addsmi	r1, sl, #2293760	; 0x230000
d001fee8:	4622d9de 			; <UNDEFINED> instruction: 0x4622d9de
d001feec:	46384649 	ldrtmi	r4, [r8], -r9, asr #12
d001fef0:	f812f001 			; <UNDEFINED> instruction: 0xf812f001
d001fef4:	0201f10a 	andeq	pc, r1, #-2147483646	; 0x80000002
d001fef8:	19384629 	ldmdbne	r8!, {r0, r3, r5, r9, sl, lr}
d001fefc:	f80cf001 			; <UNDEFINED> instruction: 0xf80cf001
d001ff00:	9b08b14e 	blls	0xd024c440
d001ff04:	46314642 	ldrtmi	r4, [r1], -r2, asr #12
d001ff08:	f7ff4638 			; <UNDEFINED> instruction: 0xf7ff4638
d001ff0c:	fab0fcc5 	blx	0xcec5f228
d001ff10:	0940f080 	stmdbeq	r0, {r7, ip, sp, lr, pc}^
d001ff14:	2001e7c9 	andcs	lr, r1, r9, asr #15
d001ff18:	Address 0x00000000d001ff18 is out of bounds.


Disassembly of section .text.resolve_path.constprop.0:

d001ff28 <.text.resolve_path.constprop.0>:
d001ff28:	460fb5f7 			; <UNDEFINED> instruction: 0x460fb5f7
d001ff2c:	46044616 			; <UNDEFINED> instruction: 0x46044616
d001ff30:	2000b910 	andcs	fp, r0, r0, lsl r9
d001ff34:	bdf0b003 	ldcllt	0, cr11, [r0, #12]!
d001ff38:	2b007803 	blcs	0xd003df4c
d001ff3c:	f002d0f9 			; <UNDEFINED> instruction: 0xf002d0f9
d001ff40:	4605fbf5 			; <UNDEFINED> instruction: 0x4605fbf5
d001ff44:	f0024638 			; <UNDEFINED> instruction: 0xf0024638
d001ff48:	4285fbf1 	addmi	pc, r5, #246784	; 0x3c400
d001ff4c:	1a2bd9f1 	bne	0xd0b16718
d001ff50:	44253f01 	strtmi	r3, [r5], #-3841	; 0xfffff0ff
d001ff54:	42ab4423 	adcmi	r4, fp, #587202560	; 0x23000000
d001ff58:	213ad118 	teqcs	sl, r8, lsl r1
d001ff5c:	f0024620 			; <UNDEFINED> instruction: 0xf0024620
d001ff60:	7823fc09 	stmdavc	r3!, {r0, r3, sl, fp, ip, sp, lr, pc}
d001ff64:	d0032b2f 	andle	r2, r3, pc, lsr #22
d001ff68:	7843b1d8 	stmdavc	r3, {r3, r4, r6, r7, r8, ip, sp, pc}^
d001ff6c:	d1e02b2f 	mvnle	r2, pc, lsr #22
d001ff70:	46234a21 	strtmi	r4, [r3], -r1, lsr #20
d001ff74:	7180f44f 	orrvc	pc, r0, pc, asr #8
d001ff78:	447a4630 	ldrbtmi	r4, [sl], #-1584	; 0xfffff9d0
d001ff7c:	fb9ef002 	blx	0xce7dbf8e
d001ff80:	28fe3801 	ldmcs	lr!, {r0, fp, ip, sp}^
d001ff84:	2000bf8c 	andcs	fp, r0, ip, lsl #31
d001ff88:	e7d32001 	ldrb	r2, [r3, r1]
d001ff8c:	1b01f813 	blne	0xd009dfe0
d001ff90:	2f01f817 	svccs	0x0001f817
d001ff94:	0120f041 	msreq	CPSR_, r1, asr #32
d001ff98:	0220f042 	eoreq	pc, r0, #66	; 0x42
d001ff9c:	d0da4291 	smullsle	r4, sl, r1, r2
d001ffa0:	4b14e7c7 	blmi	0xd0559ec4
d001ffa4:	7180f44f 	orrvc	pc, r0, pc, asr #8
d001ffa8:	685b4d14 	ldmdavs	fp, {r2, r4, r8, sl, fp, lr}^
d001ffac:	681b447d 	ldmdavs	fp, {r0, r2, r3, r4, r5, r6, sl, lr}
d001ffb0:	69db4628 	ldmibvs	fp, {r3, r5, r9, sl, lr}^
d001ffb4:	28004798 	stmdacs	r0, {r3, r4, r7, r8, r9, sl, lr}
d001ffb8:	782bd1bb 	stmdavc	fp!, {r0, r1, r3, r4, r5, r7, r8, ip, lr, pc}
d001ffbc:	d0b82b00 	adcsle	r2, r8, r0, lsl #22
d001ffc0:	f0024628 			; <UNDEFINED> instruction: 0xf0024628
d001ffc4:	4428fbb3 	strtmi	pc, [r8], #-2995	; 0xfffff44d
d001ffc8:	3c01f810 	stccc	8, cr15, [r1], {16}
d001ffcc:	d00d2b2f 	andle	r2, sp, pc, lsr #22
d001ffd0:	447b4b0b 	ldrbtmi	r4, [fp], #-2827	; 0xfffff4f5
d001ffd4:	f44f4a0b 	vst1.8	{d20-d21}, [pc], fp
d001ffd8:	46307180 	ldrtmi	r7, [r0], -r0, lsl #3
d001ffdc:	e9cd447a 	stmib	sp, {r1, r3, r4, r5, r6, sl, lr}^
d001ffe0:	4b093400 	blmi	0xd026cfe8
d001ffe4:	f002447b 			; <UNDEFINED> instruction: 0xf002447b
d001ffe8:	e7c9fb69 	strb	pc, [r9, r9, ror #22]	; <UNPREDICTABLE>
d001ffec:	447b4b07 	ldrbtmi	r4, [fp], #-2823	; 0xfffff4f9
d001fff0:	bf00e7f0 	svclt	0x0000e7f0
d001fff4:	2001f000 	andcs	pc, r1, r0
d001fff8:	ffffff9f 			; <UNDEFINED> instruction: 0xffffff9f
d001fffc:	00154148 	andseq	r4, r5, r8, asr #2
d0020000:	ffffff45 			; <UNDEFINED> instruction: 0xffffff45
d0020004:	ffffff40 			; <UNDEFINED> instruction: 0xffffff40
d0020008:	00154110 	andseq	r4, r5, r0, lsl r1
d002000c:	ffffff28 			; <UNDEFINED> instruction: 0xffffff28

Disassembly of section .text.stream_close_file:

d0020010 <.text.stream_close_file>:
d0020010:	b5706803 	ldrblt	r6, [r0, #-2051]!	; 0xfffff7fd
d0020014:	b9134605 	ldmdblt	r3, {r0, r2, r9, sl, lr}
d0020018:	46202401 	strtmi	r2, [r0], -r1, lsl #8
d002001c:	f241bd70 	vmla.f32	<illegal reg q13.5>, <illegal reg q0.5>, q8
d0020020:	4e0f0314 	mcrmi	3, 0, r0, cr15, cr4, {0}
d0020024:	b9a358c3 	stmiblt	r3!, {r0, r1, r6, r7, fp, ip, lr}
d0020028:	68286873 	stmdavs	r8!, {r0, r1, r4, r5, r6, fp, sp, lr}
d002002c:	6d1b681b 	ldcvs	8, cr6, [fp, #-108]	; 0xffffff94
d0020030:	fab04798 	blx	0xcec31e98
d0020034:	0964f480 	stmdbeq	r4!, {r7, sl, ip, sp, lr, pc}^
d0020038:	68286873 	stmdavs	r8!, {r0, r1, r4, r5, r6, fp, sp, lr}
d002003c:	6d5b681b 	ldclvs	8, cr6, [fp, #-108]	; 0xffffff94
d0020040:	23004798 	movwcs	r4, #1944	; 0x798
d0020044:	2c00602b 	stccs	0, cr6, [r0], {43}	; 0x2b
d0020048:	2800d0e7 	stmdacs	r0, {r0, r1, r2, r5, r6, r7, ip, lr, pc}
d002004c:	461cd0e4 	ldrmi	sp, [ip], -r4, ror #1
d0020050:	f7ffe7e3 			; <UNDEFINED> instruction: 0xf7ffe7e3
d0020054:	4604fe21 	strmi	pc, [r4], -r1, lsr #28
d0020058:	d0ed2800 	rscle	r2, sp, r0, lsl #16
d002005c:	bf00e7e4 	svclt	0x0000e7e4
d0020060:	2001f000 	andcs	pc, r1, r0

Disassembly of section .text.stream_io_write:

d0020064 <.text.stream_io_write>:
d0020064:	4ff0e92d 	svcmi	0x00f0e92d
d0020068:	4616b087 	ldrmi	fp, [r6], -r7, lsl #1
d002006c:	9001461f 	andls	r4, r1, pc, lsl r6
d0020070:	f500b141 			; <UNDEFINED> instruction: 0xf500b141
d0020074:	35185580 	ldrcc	r5, [r8, #-1408]	; 0xfffffa80
d0020078:	b92b9b10 	stmdblt	fp!, {r4, r8, r9, fp, ip, pc}
d002007c:	b0072001 	andlt	r2, r7, r1
d0020080:	8ff0e8bd 	svchi	0x00f0e8bd
d0020084:	e7f79d01 	ldrb	r9, [r7, r1, lsl #26]!
d0020088:	2b00682b 	blcs	0xd003a13c
d002008c:	9b10d05a 	blls	0xd04541fc
d0020090:	429e43db 	addsmi	r4, lr, #1811939331	; 0x6c000003
d0020094:	f505d856 			; <UNDEFINED> instruction: 0xf505d856
d0020098:	f1095980 			; <UNDEFINED> instruction: 0xf1095980
d002009c:	f4260910 	vld2.8	{d0,d2}, [r6 :64], r0
d00200a0:	f505647f 			; <UNDEFINED> instruction: 0xf505647f
d00200a4:	f8d95880 			; <UNDEFINED> instruction: 0xf8d95880
d00200a8:	f0243000 			; <UNDEFINED> instruction: 0xf0243000
d00200ac:	f108040f 			; <UNDEFINED> instruction: 0xf108040f
d00200b0:	b1230814 			; <UNDEFINED> instruction: 0xb1230814
d00200b4:	0304f241 	movweq	pc, #16961	; 0x4241	; <UNPREDICTABLE>
d00200b8:	429c58eb 	addsmi	r5, ip, #15400960	; 0xeb0000
d00200bc:	f8d8d01c 			; <UNDEFINED> instruction: 0xf8d8d01c
d00200c0:	2b003000 	blcs	0xd002c0c8
d00200c4:	f105d139 			; <UNDEFINED> instruction: 0xf105d139
d00200c8:	f44f0a04 	vst1.8	{d16-d17}, [pc], r4
d00200cc:	21005280 	smlabbcs	r0, r0, r2, r5
d00200d0:	f0004650 			; <UNDEFINED> instruction: 0xf0004650
d00200d4:	f241ff13 	vrecps.f32	d31, d1, d3
d00200d8:	f2410304 	vcgt.s8	d16, d1, d4
d00200dc:	50ec0208 	rscpl	r0, ip, r8, lsl #4
d00200e0:	f8c92301 			; <UNDEFINED> instruction: 0xf8c92301
d00200e4:	18ab3000 	stmiane	fp!, {ip, sp}
d00200e8:	23009302 	movwcs	r9, #770	; 0x302
d00200ec:	f24150ab 	vhadd.s8	d21, d17, d27
d00200f0:	58aa020c 	stmiapl	sl!, {r2, r3, r9}
d00200f4:	d32c4294 			; <UNDEFINED> instruction: 0xd32c4294
d00200f8:	0a04eba6 	beq	0xd015af98
d00200fc:	9b101ba4 	blls	0xd0426f94
d0020100:	f5041d28 			; <UNDEFINED> instruction: 0xf5041d28
d0020104:	46395480 	ldrtmi	r5, [r9], -r0, lsl #9
d0020108:	429c4450 	addsmi	r4, ip, #80, 8	; 0x50000000
d002010c:	461cbf28 	ldrmi	fp, [ip], -r8, lsr #30
d0020110:	44264622 	strtmi	r4, [r6], #-1570	; 0xfffff9de
d0020114:	ff00f000 			; <UNDEFINED> instruction: 0xff00f000
d0020118:	0208f241 	andeq	pc, r8, #268435460	; 0x10000004
d002011c:	0304eb0a 	movweq	lr, #19210	; 0x4b0a
d0020120:	58a94427 	stmiapl	r9!, {r0, r1, r2, r5, sl, lr}
d0020124:	bf88428b 	svclt	0x0088428b
d0020128:	230150ab 	movwcs	r5, #4267	; 0x10ab
d002012c:	3000f8c8 	andcc	pc, r0, r8, asr #17
d0020130:	1b1b9b10 	blne	0xd0706d78
d0020134:	d1b29310 			; <UNDEFINED> instruction: 0xd1b29310
d0020138:	4628e7a0 	strtmi	lr, [r8], -r0, lsr #15
d002013c:	fdacf7ff 	stc2	7, cr15, [ip, #1020]!	; 0x3fc
d0020140:	d1c02800 	bicle	r2, r0, r0, lsl #16
d0020144:	1330f242 	teqne	r0, #536870916	; 0x20000004	; <UNPREDICTABLE>
d0020148:	99012201 	stmdbls	r1, {r0, r9, sp}
d002014c:	50ca2000 	sbcpl	r2, sl, r0
d0020150:	9305e795 	movwls	lr, #22421	; 0x5795
d0020154:	4b114621 	blmi	0xd04719e0
d0020158:	685b6828 	ldmdavs	fp, {r3, r5, fp, sp, lr}^
d002015c:	f8d39203 			; <UNDEFINED> instruction: 0xf8d39203
d0020160:	f8dbb000 			; <UNDEFINED> instruction: 0xf8dbb000
d0020164:	47983044 	ldrmi	r3, [r8, r4, asr #32]
d0020168:	d1eb2800 	mvnle	r2, r0, lsl #16
d002016c:	ab059a03 	blge	0xd0186980
d0020170:	b03cf8db 	ldrsbtlt	pc, [ip], -fp	; <UNPREDICTABLE>
d0020174:	1b124651 	blne	0xd04b1ac0
d0020178:	f5b26828 			; <UNDEFINED> instruction: 0xf5b26828
d002017c:	bf285f80 	svclt	0x00285f80
d0020180:	5280f44f 	addpl	pc, r0, #1325400064	; 0x4f000000
d0020184:	47d89203 	ldrbmi	r9, [r8, r3, lsl #4]
d0020188:	d1db2800 	bicsle	r2, fp, r0, lsl #16
d002018c:	9a039b05 	bls	0xd0106da8
d0020190:	d1d7429a 			; <UNDEFINED> instruction: 0xd1d7429a
d0020194:	601a9b02 	andsvs	r9, sl, r2, lsl #22
d0020198:	bf00e7ae 	svclt	0x0000e7ae
d002019c:	2001f000 	andcs	pc, r1, r0

Disassembly of section .text.build:

d0020270 <.text.build>:
d0020270:	49ae4bad 	stmibmi	lr!, {r0, r2, r3, r5, r7, r8, r9, fp, lr}
d0020274:	4479447b 	ldrbtmi	r4, [r9], #-1147	; 0xfffffb85
d0020278:	4ff0e92d 	svcmi	0x00f0e92d
d002027c:	2500b0a5 	strcs	fp, [r0, #-165]	; 0xffffff5b
d0020280:	300ae9cd 	andcc	lr, sl, sp, asr #19
d0020284:	aa144baa 	bge	0xd0533134
d0020288:	681b447b 	ldmdavs	fp, {r0, r1, r3, r4, r5, r6, sl, lr}
d002028c:	d17242ab 	cmnle	r2, fp, lsr #5
d0020290:	447b4ba8 	ldrbtmi	r4, [fp], #-2984	; 0xfffff458
d0020294:	2d009306 	stccs	3, cr9, [r0, #-24]	; 0xffffffe8
d0020298:	4ba7d073 	blmi	0xcea1446c
d002029c:	0b50f10d 	bleq	0xd145c6d8
d00202a0:	9304447b 	movwls	r4, #17531	; 0x447b
d00202a4:	2d014c9f 	stccs	12, cr4, [r1, #-636]	; 0xfffffd84
d00202a8:	f04f49a4 			; <UNDEFINED> instruction: 0xf04f49a4
d00202ac:	68a30000 	stmiavs	r3!, {}	; <UNPREDICTABLE>
d00202b0:	2501bf38 	strcs	fp, [r1, #-3896]	; 0xfffff0c8
d00202b4:	681b4479 	ldmdavs	fp, {r0, r3, r4, r5, r6, sl, lr}
d00202b8:	681b462a 	ldmdavs	fp, {r1, r3, r5, r9, sl, lr}
d00202bc:	4ba04798 	blmi	0xce832124
d00202c0:	681b447b 	ldmdavs	fp, {r0, r1, r3, r4, r5, r6, sl, lr}
d00202c4:	68a3b92b 	stmiavs	r3!, {r0, r1, r3, r5, r8, fp, ip, sp, pc}
d00202c8:	b113689b 			; <UNDEFINED> instruction: 0xb113689b
d00202cc:	689b68a3 	ldmvs	fp, {r0, r1, r5, r7, fp, sp, lr}
d00202d0:	4b9c4798 	blmi	0xce732138
d00202d4:	4618447b 			; <UNDEFINED> instruction: 0x4618447b
d00202d8:	f0029305 			; <UNDEFINED> instruction: 0xf0029305
d00202dc:	38f7fa27 	ldmcc	r7!, {r0, r1, r2, r5, r9, fp, ip, sp, lr, pc}^
d00202e0:	f5109b05 			; <UNDEFINED> instruction: 0xf5109b05
d00202e4:	d8517f81 	ldmdale	r1, {r0, r7, r8, r9, sl, fp, ip, sp, lr}^
d00202e8:	9b0f2606 	blls	0xd03e9b08
d00202ec:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d00202f0:	9d1381c3 	ldflsd	f0, [r3, #-780]	; 0xfffffcf4
d00202f4:	4a94b955 	bmi	0xce54e850
d00202f8:	447a9b12 	ldrbtmi	r9, [sl], #-2834	; 0xfffff4ee
d00202fc:	42936812 	addsmi	r6, r3, #1179648	; 0x120000
d0020300:	81a5f080 			; <UNDEFINED> instruction: 0x81a5f080
d0020304:	447d4d91 	ldrbtmi	r4, [sp], #-3473	; 0xfffff26f
d0020308:	2503eb05 	strcs	lr, [r3, #-2821]	; 0xfffff4fb
d002030c:	4628212f 	strtmi	r2, [r8], -pc, lsr #2
d0020310:	fa3cf002 	blx	0xd0f5c320
d0020314:	1c45b100 	stfnep	f3, [r5], {-0}
d0020318:	f44f9b0f 			; <UNDEFINED> instruction: 0xf44f9b0f
d002031c:	488c71c0 	stmmi	ip, {r6, r7, r8, ip, sp, lr}
d0020320:	9b119302 	blls	0xd0484f30
d0020324:	4a8b4478 	bmi	0xce2f150c
d0020328:	9b109301 	blls	0xd0444f34
d002032c:	4f8a447a 	svcmi	0x008a447a
d0020330:	462b9300 	strtmi	r9, [fp], -r0, lsl #6
d0020334:	447f4605 	ldrbtmi	r4, [pc], #-1541	; 0xd002033c
d0020338:	f9c0f002 			; <UNDEFINED> instruction: 0xf9c0f002
d002033c:	f7ff4628 			; <UNDEFINED> instruction: 0xf7ff4628
d0020340:	6838fa8b 	ldmdavs	r8!, {r0, r1, r3, r7, r9, fp, ip, sp, lr, pc}
d0020344:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d0020348:	9d1380ea 	ldcls	0, cr8, [r3, #-936]	; 0xfffffc58
d002034c:	9e10b98d 	vnmlsls.f16	s22, s1, s26	; <UNPREDICTABLE>
d0020350:	f0002e00 			; <UNDEFINED> instruction: 0xf0002e00
d0020354:	9a1180c4 	bls	0xd048066c
d0020358:	68a3b15a 	stmiavs	r3!, {r1, r3, r4, r6, r8, ip, sp, pc}
d002035c:	1e713a01 	vaddne.f32	s7, s2, s2
d0020360:	f8d368db 			; <UNDEFINED> instruction: 0xf8d368db
d0020364:	479830b8 			; <UNDEFINED> instruction: 0x479830b8
d0020368:	683868a3 	ldmdavs	r8!, {r0, r1, r5, r7, fp, sp, lr}
d002036c:	6ddb68db 	ldclvs	8, cr6, [fp, #876]	; 0x36c
d0020370:	26004798 			; <UNDEFINED> instruction: 0x26004798
d0020374:	eb01e0b3 	bl	0xd0098648
d0020378:	f8422005 			; <UNDEFINED> instruction: 0xf8422005
d002037c:	35010025 	strcc	r0, [r1, #-37]	; 0xffffffdb
d0020380:	ab0ae784 	blge	0xd02da198
d0020384:	0b18f10d 	bleq	0xd065c7c0
d0020388:	e78b9304 	str	r9, [fp, r4, lsl #6]
d002038c:	81ccf8df 	ldrdhi	pc, [ip, #143]	; 0x8f
d0020390:	7180f44f 	orrvc	pc, r0, pc, asr #8
d0020394:	f04f4a72 			; <UNDEFINED> instruction: 0xf04f4a72
d0020398:	44f80a00 	ldrbtmi	r0, [r8], #2560	; 0xa00
d002039c:	447a4e71 	ldrbtmi	r4, [sl], #-3697	; 0xfffff18f
d00203a0:	447e9305 	ldrbtmi	r9, [lr], #-773	; 0xfffffcfb
d00203a4:	f0024640 			; <UNDEFINED> instruction: 0xf0024640
d00203a8:	4a6ff989 	bmi	0xd1c1e9d4
d00203ac:	f506486f 			; <UNDEFINED> instruction: 0xf506486f
d00203b0:	9b055700 	blls	0xd0175fb8
d00203b4:	f44f447a 	vst3.16	{d20-d22}, [pc :256], sl
d00203b8:	44787180 	ldrbtmi	r7, [r8], #-384	; 0xfffffe80
d00203bc:	f97ef002 			; <UNDEFINED> instruction: 0xf97ef002
d00203c0:	4a6b3730 	bmi	0xd1aee088
d00203c4:	7180f44f 	orrvc	pc, r0, pc, asr #8
d00203c8:	46389b05 	ldrtmi	r9, [r8], -r5, lsl #22
d00203cc:	f002447a 			; <UNDEFINED> instruction: 0xf002447a
d00203d0:	f242f975 	vmul.i8	<illegal reg q15.5>, q1, <illegal reg q10.5>
d00203d4:	46411330 			; <UNDEFINED> instruction: 0x46411330
d00203d8:	f8464630 			; <UNDEFINED> instruction: 0xf8464630
d00203dc:	f7ffa003 			; <UNDEFINED> instruction: 0xf7ffa003
d00203e0:	b908fbd7 	stmdblt	r8, {r0, r1, r2, r4, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d00203e4:	e7802601 	str	r2, [r0, r1, lsl #12]
d00203e8:	5980f506 	stmibpl	r0, {r1, r2, r8, sl, ip, sp, lr, pc}
d00203ec:	f1094639 			; <UNDEFINED> instruction: 0xf1094639
d00203f0:	46480918 			; <UNDEFINED> instruction: 0x46480918
d00203f4:	fbccf7ff 	blx	0xcf35e3fa
d00203f8:	4630b940 	ldrtmi	fp, [r0], -r0, asr #18
d00203fc:	fe08f7ff 	mcr2	7, 0, pc, cr8, cr15, {7}	; <UNPREDICTABLE>
d0020400:	46406863 	strbmi	r6, [r0], -r3, ror #16
d0020404:	6d9b681b 	ldcvs	8, cr6, [fp, #108]	; 0x6c
d0020408:	e7eb4798 			; <UNDEFINED> instruction: 0xe7eb4798
d002040c:	447b4b59 	ldrbtmi	r4, [fp], #-2905	; 0xfffff4a7
d0020410:	0007e893 	muleq	r7, r3, r8
d0020414:	e883ab0c 	stm	r3, {r2, r3, r8, r9, fp, sp, pc}
d0020418:	48570007 	ldmdami	r7, {r0, r1, r2}^
d002041c:	93054651 	movwls	r4, #22097	; 0x5651
d0020420:	f7fe4478 			; <UNDEFINED> instruction: 0xf7fe4478
d0020424:	9b05fca1 	blls	0xd019f6b0
d0020428:	4659aa0f 	ldrbmi	sl, [r9], -pc, lsl #20
d002042c:	4b539301 	blmi	0xd1505038
d0020430:	462a9202 	strtmi	r9, [sl], -r2, lsl #4
d0020434:	9804447b 	stmdals	r4, {r0, r1, r3, r4, r5, r6, sl, lr}
d0020438:	4b519300 	blmi	0xd1485040
d002043c:	f7fe447b 			; <UNDEFINED> instruction: 0xf7fe447b
d0020440:	4651fc9f 			; <UNDEFINED> instruction: 0x4651fc9f
d0020444:	46504605 	ldrbmi	r4, [r0], -r5, lsl #12
d0020448:	fc8ef7fe 	stc2	7, cr15, [lr], {254}	; 0xfe
d002044c:	f7ff4648 			; <UNDEFINED> instruction: 0xf7ff4648
d0020450:	4681fddf 	pkhtbmi	pc, r1, pc, asr #27	; <UNPREDICTABLE>
d0020454:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0020458:	6863fddb 	stmdavs	r3!, {r0, r1, r3, r4, r6, r7, r8, sl, fp, ip, sp, lr, pc}^
d002045c:	46382800 	ldrtmi	r2, [r8], -r0, lsl #16
d0020460:	bf08681b 	svclt	0x0008681b
d0020464:	0900f04f 	stmdbeq	r0, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d0020468:	47986d9b 			; <UNDEFINED> instruction: 0x47986d9b
d002046c:	0f00f1b9 	svceq	0x0000f1b9
d0020470:	b125d005 			; <UNDEFINED> instruction: 0xb125d005
d0020474:	1330f242 	teqne	r0, #536870916	; 0x20000004	; <UNPREDICTABLE>
d0020478:	2f0058f7 	svccs	0x000058f7
d002047c:	6863d033 	stmdavs	r3!, {r0, r1, r4, r5, ip, lr, pc}^
d0020480:	681b4840 	ldmdavs	fp, {r6, fp, lr}
d0020484:	6d9b4478 	cfldrsvs	mvf4, [fp, #480]	; 0x1e0
d0020488:	2d004798 	stccs	7, cr4, [r0, #-608]	; 0xfffffda0
d002048c:	2601bf14 			; <UNDEFINED> instruction: 0x2601bf14
d0020490:	f43f2600 			; <UNDEFINED> instruction: 0xf43f2600
d0020494:	2e00af2a 	cdpcs	15, 0, cr10, cr0, cr10, {1}
d0020498:	4b3bd13c 	blmi	0xd0f14990
d002049c:	6818447b 	ldmdavs	r8, {r0, r1, r3, r4, r5, r6, sl, lr}
d00204a0:	483ab120 	ldmdami	sl!, {r5, r8, ip, sp, pc}
d00204a4:	4478212f 	ldrbtmi	r2, [r8], #-303	; 0xfffffed1
d00204a8:	f970f002 			; <UNDEFINED> instruction: 0xf970f002
d00204ac:	447b4b38 	ldrbtmi	r4, [fp], #-2872	; 0xfffff4c8
d00204b0:	2a01681a 	bcs	0xd007a520
d00204b4:	80d1f240 	sbcshi	pc, r1, r0, asr #4
d00204b8:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d00204bc:	1c4380cb 	mcrrne	0, 12, r8, r3, cr11
d00204c0:	f44f4834 	vst2.8	{d20-d21}, [pc :256], r4
d00204c4:	920171c0 	andls	r7, r1, #192, 2	; 0x30
d00204c8:	44784a33 	ldrbtmi	r4, [r8], #-2611	; 0xfffff5cd
d00204cc:	447a9500 	ldrbtmi	r9, [sl], #-1280	; 0xfffffb00
d00204d0:	f8f4f002 			; <UNDEFINED> instruction: 0xf8f4f002
d00204d4:	26014831 			; <UNDEFINED> instruction: 0x26014831
d00204d8:	f7ff4478 			; <UNDEFINED> instruction: 0xf7ff4478
d00204dc:	4630f9bd 			; <UNDEFINED> instruction: 0x4630f9bd
d00204e0:	e8bdb025 	pop	{r0, r2, r5, ip, sp, pc}
d00204e4:	68638ff0 	stmdavs	r3!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}^
d00204e8:	a908aa07 	stmdbge	r8, {r0, r1, r2, r9, fp, sp, pc}
d00204ec:	681b4640 	ldmdavs	fp, {r6, r9, sl, lr}
d00204f0:	6a9b9707 	bvs	0xce706114
d00204f4:	47989708 	ldrmi	r9, [r8, r8, lsl #14]
d00204f8:	9b08b928 	blls	0xd024e9a0
d00204fc:	d40207da 	strle	r0, [r2], #-2010	; 0xfffff826
d0020500:	429d9b07 	addsmi	r9, sp, #7168	; 0x1c00
d0020504:	6863d050 	stmdavs	r3!, {r4, r6, ip, lr, pc}^
d0020508:	48252601 	stmdami	r5!, {r0, r9, sl, sp}
d002050c:	4478681b 	ldrbtmi	r6, [r8], #-2075	; 0xfffff7e5
d0020510:	47986d9b 			; <UNDEFINED> instruction: 0x47986d9b
d0020514:	46304923 	ldrtmi	r4, [r0], -r3, lsr #18
d0020518:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d002051c:	4606fc87 	strmi	pc, [r6], -r7, lsl #25
d0020520:	bf00e7dd 	svclt	0x0000e7dd
d0020524:	2001f000 	andcs	pc, r1, r0
d0020528:	00053d70 	andeq	r3, r5, r0, ror sp
d002052c:	00052cea 	andeq	r2, r5, sl, ror #25
d0020530:	00052cd4 	ldrdeq	r2, [r5], -r4
d0020534:	00153d62 	andseq	r3, r5, r2, ror #26
d0020538:	00053cc0 	andeq	r3, r5, r0, asr #25
d002053c:	fffffee8 			; <UNDEFINED> instruction: 0xfffffee8
d0020540:	00052c98 	muleq	r5, r8, ip
d0020544:	00052a80 	andeq	r2, r5, r0, lsl #21
d0020548:	00052c62 	andeq	r2, r5, r2, ror #24
d002054c:	00052c5a 	andeq	r2, r5, sl, asr ip
d0020550:	00153ed0 			; <UNDEFINED> instruction: 0x00153ed0
d0020554:	fffffee0 			; <UNDEFINED> instruction: 0xfffffee0
d0020558:	00052c22 	andeq	r2, r5, r2, lsr #24
d002055c:	00153d5a 	andseq	r3, r5, sl, asr sp
d0020560:	fffffe25 			; <UNDEFINED> instruction: 0xfffffe25
d0020564:	00153fd6 			; <UNDEFINED> instruction: 0x00153fd6
d0020568:	fffffe1b 			; <UNDEFINED> instruction: 0xfffffe1b
d002056c:	00052a9a 	muleq	r5, sl, sl
d0020570:	fffffe0f 			; <UNDEFINED> instruction: 0xfffffe0f
d0020574:	0000249a 	muleq	r0, sl, r4
d0020578:	fffff7d1 			; <UNDEFINED> instruction: 0xfffff7d1
d002057c:	fffffa61 			; <UNDEFINED> instruction: 0xfffffa61
d0020580:	fffff4ed 			; <UNDEFINED> instruction: 0xfffff4ed
d0020584:	00153c70 	andseq	r3, r5, r0, ror ip
d0020588:	00153ed8 			; <UNDEFINED> instruction: 0x00153ed8
d002058c:	000528ae 	andeq	r2, r5, lr, lsr #17
d0020590:	00052aae 	andeq	r2, r5, lr, lsr #21
d0020594:	00153d2a 	andseq	r3, r5, sl, lsr #26
d0020598:	fffffd4a 			; <UNDEFINED> instruction: 0xfffffd4a
d002059c:	00153d1c 	andseq	r3, r5, ip, lsl sp
d00205a0:	00153be6 	andseq	r3, r5, r6, ror #23
d00205a4:	fffff47c 			; <UNDEFINED> instruction: 0xfffff47c
d00205a8:	493768a3 	ldmdbmi	r7!, {r0, r1, r5, r7, fp, sp, lr}
d00205ac:	4479681b 	ldrbtmi	r6, [r9], #-2075	; 0xfffff7e5
d00205b0:	4798681b 			; <UNDEFINED> instruction: 0x4798681b
d00205b4:	447b4b35 	ldrbtmi	r4, [fp], #-2869	; 0xfffff4cb
d00205b8:	b92b681b 	stmdblt	fp!, {r0, r1, r3, r4, fp, sp, lr}
d00205bc:	689b68a3 	ldmvs	fp, {r0, r1, r5, r7, fp, sp, lr}
d00205c0:	68a3b113 	stmiavs	r3!, {r0, r1, r4, r8, ip, sp, pc}
d00205c4:	4798689b 			; <UNDEFINED> instruction: 0x4798689b
d00205c8:	22006863 	andcs	r6, r0, #6488064	; 0x630000
d00205cc:	80c0f8df 	ldrdhi	pc, [r0], #143	; 0x8f
d00205d0:	681ca909 	ldmdavs	ip, {r0, r3, r8, fp, sp, pc}
d00205d4:	920944f8 	andls	r4, r9, #248, 8	; 0xf8000000
d00205d8:	46406aa3 	strbmi	r6, [r0], -r3, lsr #21
d00205dc:	46064798 			; <UNDEFINED> instruction: 0x46064798
d00205e0:	9b09b970 	blls	0xd028eba8
d00205e4:	d42407db 	strtle	r0, [r4], #-2011	; 0xfffff825
d00205e8:	4640492a 	strbmi	r4, [r0], -sl, lsr #18
d00205ec:	44796de3 	ldrbtmi	r6, [r9], #-3555	; 0xfffff21d
d00205f0:	46064798 			; <UNDEFINED> instruction: 0x46064798
d00205f4:	4828b1d8 	stmdami	r8!, {r3, r4, r6, r7, r8, ip, sp, pc}
d00205f8:	44786da3 	ldrbtmi	r6, [r8], #-3491	; 0xfffff25d
d00205fc:	e74a4798 			; <UNDEFINED> instruction: 0xe74a4798
d0020600:	d1f82804 	mvnsle	r2, r4, lsl #16
d0020604:	48264925 	stmdami	r6!, {r0, r2, r5, r8, fp, lr}
d0020608:	6de34479 	cfstrdvs	mvd4, [r3, #484]!	; 0x1e4
d002060c:	91044478 	tstls	r4, r8, ror r4
d0020610:	99044798 	stmdbls	r4, {r3, r4, r7, r8, r9, sl, lr}
d0020614:	b1704606 	cmnlt	r0, r6, lsl #12
d0020618:	d0ec2f00 	rscle	r2, ip, r0, lsl #30
d002061c:	6de34821 	stclvs	8, cr4, [r3, #132]!	; 0x84
d0020620:	47984478 			; <UNDEFINED> instruction: 0x47984478
d0020624:	d0e62800 	rscle	r2, r6, r0, lsl #16
d0020628:	0601f06f 	streq	pc, [r1], -pc, rrx
d002062c:	2701e772 	smlsdxcs	r1, r2, r7, lr
d0020630:	2607e7e8 	strcs	lr, [r7], -r8, ror #15
d0020634:	2f00e7df 	svccs	0x0000e7df
d0020638:	af2ff43f 	svcge	0x002ff43f
d002063c:	6da3481a 	stcvs	8, cr4, [r3, #104]!	; 0x68
d0020640:	47984478 			; <UNDEFINED> instruction: 0x47984478
d0020644:	bf183800 	svclt	0x00183800
d0020648:	42462001 	submi	r2, r6, #1
d002064c:	4d17e723 	ldcmi	7, cr14, [r7, #-140]	; 0xffffff74
d0020650:	e65b447d 			; <UNDEFINED> instruction: 0xe65b447d
d0020654:	447b4b16 	ldrbtmi	r4, [fp], #-2838	; 0xfffff4ea
d0020658:	b150e732 	cmplt	r0, r2, lsr r7
d002065c:	4a151c43 	bmi	0xd0567770
d0020660:	71c0f44f 	bicvc	pc, r0, pc, asr #8
d0020664:	447a4814 	ldrbtmi	r4, [sl], #-2068	; 0xfffff7ec
d0020668:	44789500 	ldrbtmi	r9, [r8], #-1280	; 0xfffffb00
d002066c:	f826f002 			; <UNDEFINED> instruction: 0xf826f002
d0020670:	4b12e730 	blmi	0xd04da338
d0020674:	e7f2447b 			; <UNDEFINED> instruction: 0xe7f2447b
d0020678:	f47f2e00 			; <UNDEFINED> instruction: 0xf47f2e00
d002067c:	4810af4b 	ldmdami	r0, {r0, r1, r3, r6, r8, r9, sl, fp, sp, pc}
d0020680:	f7ff4478 			; <UNDEFINED> instruction: 0xf7ff4478
d0020684:	e72af8e9 	str	pc, [sl, -r9, ror #17]!
d0020688:	fffffc39 			; <UNDEFINED> instruction: 0xfffffc39
d002068c:	000529a2 	andeq	r2, r5, r2, lsr #19
d0020690:	00052780 	andeq	r2, r5, r0, lsl #15
d0020694:	00052866 	andeq	r2, r5, r6, ror #16
d0020698:	00153afa 			; <UNDEFINED> instruction: 0x00153afa
d002069c:	0005274c 	andeq	r2, r5, ip, asr #14
d00206a0:	00153ae8 	andseq	r3, r5, r8, ror #21
d00206a4:	00052834 	andeq	r2, r5, r4, lsr r8
d00206a8:	00052814 	andeq	r2, r5, r4, lsl r8
d00206ac:	001539a4 	andseq	r3, r5, r4, lsr #19
d00206b0:	000526fe 	strdeq	r2, [r5], -lr
d00206b4:	fffffbd2 			; <UNDEFINED> instruction: 0xfffffbd2
d00206b8:	00153b8a 	andseq	r3, r5, sl, lsl #23
d00206bc:	000526e0 	andeq	r2, r5, r0, ror #13
d00206c0:	fffffbcc 			; <UNDEFINED> instruction: 0xfffffbcc

Disassembly of section .text.editor_proc:

d00206e8 <.text.editor_proc>:
d00206e8:	47ffe92d 	ldrbmi	lr, [pc, sp, lsr #18]!
d00206ec:	2900460c 	stmdbcs	r0, {r2, r3, r9, sl, lr}
d00206f0:	80d1f000 	sbcshi	pc, r1, r0
d00206f4:	2b10680b 	blcs	0xd043a728
d00206f8:	80cdf040 	sbchi	pc, sp, r0, asr #32
d00206fc:	f24068ca 	vadd.i8	q11, q8, q5
d0020700:	429a1301 	addsmi	r1, sl, #67108864	; 0x4000000
d0020704:	80c7f040 	sbchi	pc, r7, r0, asr #32
d0020708:	688b4a66 	stmvs	fp, {r1, r2, r5, r6, r9, fp, lr}
d002070c:	6812447a 	ldmdavs	r2, {r1, r3, r4, r5, r6, sl, lr}
d0020710:	d0054293 	mulle	r5, r3, r2
d0020714:	447a4a64 	ldrbtmi	r4, [sl], #-2660	; 0xfffff59c
d0020718:	42936812 	addsmi	r6, r3, #1179648	; 0x120000
d002071c:	80bbf040 	adcshi	pc, fp, r0, asr #32
d0020720:	f8df4d5e 			; <UNDEFINED> instruction: 0xf8df4d5e
d0020724:	68ab8188 	stmiavs	fp!, {r3, r7, r8, pc}
d0020728:	44f84861 	ldrbtmi	r4, [r8], #2145	; 0x861
d002072c:	447868db 	ldrbtmi	r6, [r8], #-2267	; 0xfffff725
d0020730:	6f1b4a5b 	svcvs	0x001b4a5b
d0020734:	68004641 	stmdavs	r0, {r0, r6, r9, sl, lr}
d0020738:	1e474798 	mcrne	7, 2, r4, cr7, cr8, {4}
d002073c:	1f80f5b7 	svcne	0x0080f5b7
d0020740:	485cd904 	ldmdami	ip, {r2, r8, fp, ip, lr, pc}^
d0020744:	f7ff4478 			; <UNDEFINED> instruction: 0xf7ff4478
d0020748:	e008f887 	and	pc, r8, r7, lsl #17
d002074c:	68a24b5a 	stmiavs	r2!, {r1, r3, r4, r6, r8, r9, fp, lr}
d0020750:	681b447b 	ldmdavs	fp, {r0, r1, r3, r4, r5, r6, sl, lr}
d0020754:	d106429a 			; <UNDEFINED> instruction: 0xd106429a
d0020758:	f7ff4638 			; <UNDEFINED> instruction: 0xf7ff4638
d002075c:	20f0fd89 	rscscs	pc, r0, r9, lsl #27
d0020760:	e8bdb004 	pop	{r2, ip, sp, pc}
d0020764:	f8df87f0 			; <UNDEFINED> instruction: 0xf8df87f0
d0020768:	686ba154 	stmdavs	fp!, {r2, r4, r6, r8, sp, pc}^
d002076c:	681e44fa 	ldmdavs	lr, {r1, r3, r4, r5, r6, r7, sl, lr}
d0020770:	f0014650 			; <UNDEFINED> instruction: 0xf0014650
d0020774:	f1a0ffdb 			; <UNDEFINED> instruction: 0xf1a0ffdb
d0020778:	460403f7 			; <UNDEFINED> instruction: 0x460403f7
d002077c:	7f81f513 	svcvc	0x0081f513
d0020780:	8087f240 	addhi	pc, r7, r0, asr #4
d0020784:	46024d4e 	strmi	r4, [r2], -lr, asr #26
d0020788:	f8df4651 			; <UNDEFINED> instruction: 0xf8df4651
d002078c:	447d9138 	ldrbtmi	r9, [sp], #-312	; 0xfffffec8
d0020790:	462844f9 			; <UNDEFINED> instruction: 0x462844f9
d0020794:	fbc0f000 	blx	0xcf05c79e
d0020798:	220a494b 	andcs	r4, sl, #1228800	; 0x12c000
d002079c:	44791928 	ldrbtmi	r1, [r9], #-2344	; 0xfffff6d8
d00207a0:	fbbaf000 	blx	0xceedc7aa
d00207a4:	46514622 	ldrbmi	r4, [r1], -r2, lsr #12
d00207a8:	f0004648 			; <UNDEFINED> instruction: 0xf0004648
d00207ac:	4947fbb5 	stmdbmi	r7, {r0, r2, r4, r5, r7, r8, r9, fp, ip, sp, lr, pc}^
d00207b0:	eb09220a 	bl	0xd0268fe0
d00207b4:	44790004 	ldrbtmi	r0, [r9], #-4
d00207b8:	fbaef000 	blx	0xcebdc7c2
d00207bc:	aa016bb3 	bge	0xd007b690
d00207c0:	46282106 	strtmi	r2, [r8], -r6, lsl #2
d00207c4:	b9804798 	stmiblt	r0, {r3, r4, r7, r8, r9, sl, lr}
d00207c8:	b99f9002 	ldmiblt	pc, {r1, ip, pc}	; <UNPREDICTABLE>
d00207cc:	98016d33 	stmdals	r1, {r0, r1, r4, r5, r8, sl, fp, sp, lr}
d00207d0:	46054798 			; <UNDEFINED> instruction: 0x46054798
d00207d4:	98016d73 	stmdals	r1, {r0, r1, r4, r5, r6, r8, sl, fp, sp, lr}
d00207d8:	b90d4798 	stmdblt	sp, {r3, r4, r7, r8, r9, sl, lr}
d00207dc:	4605b1c0 	strmi	fp, [r5], -r0, asr #3
d00207e0:	6db3483b 	ldcvs	8, cr4, [r3, #236]!	; 0xec
d00207e4:	47984478 			; <UNDEFINED> instruction: 0x47984478
d00207e8:	493a4628 	ldmdbmi	sl!, {r3, r5, r9, sl, lr}
d00207ec:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d00207f0:	e7b4fb1d 			; <UNDEFINED> instruction: 0xe7b4fb1d
d00207f4:	ab026c34 	blge	0xd00bb8cc
d00207f8:	4641463a 			; <UNDEFINED> instruction: 0x4641463a
d00207fc:	47a09801 	strmi	r9, [r0, r1, lsl #16]!
d0020800:	28004605 	stmdacs	r0, {r0, r2, r9, sl, lr}
d0020804:	9b02d1e6 	blls	0xd00d4fa4
d0020808:	d0df429f 	smullsle	r4, pc, pc, r2	; <UNPREDICTABLE>
d002080c:	e7e12501 	strb	r2, [r1, r1, lsl #10]!
d0020810:	462a4f31 	qasxmi	r4, sl, r1
d0020814:	a9036ab3 	stmdbge	r3, {r0, r1, r4, r5, r7, r9, fp, sp, lr}
d0020818:	9503447f 	strls	r4, [r3, #-1151]	; 0xfffffb81
d002081c:	47984638 			; <UNDEFINED> instruction: 0x47984638
d0020820:	b9804604 	stmiblt	r0, {r2, r9, sl, lr}
d0020824:	07db9b03 	ldrbeq	r9, [fp, r3, lsl #22]
d0020828:	492cd423 	stmdbmi	ip!, {r0, r1, r5, sl, ip, lr, pc}
d002082c:	6df34638 	ldclvs	6, cr4, [r3, #224]!	; 0xe0
d0020830:	47984479 			; <UNDEFINED> instruction: 0x47984479
d0020834:	b1d04604 	bicslt	r4, r0, r4, lsl #12
d0020838:	6db34829 	ldcvs	8, cr4, [r3, #164]!	; 0xa4
d002083c:	47984478 			; <UNDEFINED> instruction: 0x47984478
d0020840:	4620b9cd 	strtmi	fp, [r0], -sp, asr #19
d0020844:	2804e7d1 	stmdacs	r4, {r0, r4, r6, r7, r8, r9, sl, sp, lr, pc}
d0020848:	4926d1f6 	stmdbmi	r6!, {r1, r2, r4, r5, r6, r7, r8, ip, lr, pc}
d002084c:	6df34826 	ldclvs	8, cr4, [r3, #152]!	; 0x98
d0020850:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d0020854:	46044798 			; <UNDEFINED> instruction: 0x46044798
d0020858:	d1ed2800 	mvnle	r2, r0, lsl #16
d002085c:	4823b1b5 	stmdami	r3!, {r0, r2, r4, r5, r7, r8, ip, sp, pc}
d0020860:	44786db3 	ldrbtmi	r6, [r8], #-3507	; 0xfffff24d
d0020864:	b1884798 			; <UNDEFINED> instruction: 0xb1884798
d0020868:	30fff04f 	rscscc	pc, pc, pc, asr #32
d002086c:	2501e7bd 	strcs	lr, [r1, #-1981]	; 0xfffff843
d0020870:	2407e7eb 	strcs	lr, [r7], #-2027	; 0xfffff815
d0020874:	491ee7e0 	ldmdbmi	lr, {r5, r6, r7, r8, r9, sl, sp, lr, pc}
d0020878:	6df3481e 	ldclvs	8, cr4, [r3, #120]!	; 0x78
d002087c:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d0020880:	28004798 	stmdacs	r0, {r3, r4, r7, r8, r9, sl, lr}
d0020884:	f06fd0dd 			; <UNDEFINED> instruction: 0xf06fd0dd
d0020888:	e7ae0001 	str	r0, [lr, r1]!
d002088c:	4478481a 	ldrbtmi	r4, [r8], #-2074	; 0xfffff7e6
d0020890:	2007e759 	andcs	lr, r7, r9, asr r7
d0020894:	2000e7a9 	andcs	lr, r0, r9, lsr #15
d0020898:	bf00e762 	svclt	0x0000e762
d002089c:	2001f000 	andcs	pc, r1, r0
d00208a0:	00100001 	andseq	r0, r0, r1
d00208a4:	000538d4 	ldrdeq	r3, [r5], -r4
d00208a8:	0005283e 	andeq	r2, r5, lr, lsr r8
d00208ac:	000538ba 			; <UNDEFINED> instruction: 0x000538ba
d00208b0:	0005282a 	andeq	r2, r5, sl, lsr #16
d00208b4:	fffff63c 			; <UNDEFINED> instruction: 0xfffff63c
d00208b8:	00052804 	andeq	r2, r5, r4, lsl #16
d00208bc:	00153888 	andseq	r3, r5, r8, lsl #17
d00208c0:	00153966 	andseq	r3, r5, r6, ror #18
d00208c4:	000526c4 	andeq	r2, r5, r4, asr #13
d00208c8:	ffffff22 			; <UNDEFINED> instruction: 0xffffff22
d00208cc:	ffffff14 			; <UNDEFINED> instruction: 0xffffff14
d00208d0:	00153910 	andseq	r3, r5, r0, lsl r9
d00208d4:	fffff1a3 			; <UNDEFINED> instruction: 0xfffff1a3
d00208d8:	001537dc 			; <UNDEFINED> instruction: 0x001537dc
d00208dc:	00052624 	andeq	r2, r5, r4, lsr #12
d00208e0:	001538b8 			; <UNDEFINED> instruction: 0x001538b8
d00208e4:	001537a4 	andseq	r3, r5, r4, lsr #15
d00208e8:	001538a2 	andseq	r3, r5, r2, lsr #17
d00208ec:	000525f2 	strdeq	r2, [r5], -r2	; <UNPREDICTABLE>
d00208f0:	00153778 	andseq	r3, r5, r8, ror r7
d00208f4:	000525d6 	ldrdeq	r2, [r5], -r6
d00208f8:	fffffe46 			; <UNDEFINED> instruction: 0xfffffe46

Disassembly of section .text.startup.main:

d0020ad8 <.text.startup.main>:
d0020ad8:	e92d2801 	push	{r0, fp, sp}
d0020adc:	46044ff0 			; <UNDEFINED> instruction: 0x46044ff0
d0020ae0:	ed2d460f 	stc	6, cr4, [sp, #-60]!	; 0xffffffc4
d0020ae4:	b0978b02 	addslt	r8, r7, r2, lsl #22
d0020ae8:	808cf000 	addhi	pc, ip, r0
d0020aec:	f0402803 			; <UNDEFINED> instruction: 0xf0402803
d0020af0:	49af8159 	stmibmi	pc!, {r0, r3, r4, r6, r8, pc}	; <UNPREDICTABLE>
d0020af4:	44796878 	ldrbtmi	r6, [r9], #-2168	; 0xfffff788
d0020af8:	fe24f001 	cdp2	0, 2, cr15, cr4, cr1, {0}
d0020afc:	f680fab0 			; <UNDEFINED> instruction: 0xf680fab0
d0020b00:	49ac0976 	stmibmi	ip!, {r1, r2, r4, r5, r6, r8, fp}
d0020b04:	44796878 	ldrbtmi	r6, [r9], #-2168	; 0xfffff788
d0020b08:	fe1cf001 	cdp2	0, 1, cr15, cr12, cr1, {0}
d0020b0c:	b966b958 	stmdblt	r6!, {r3, r4, r6, r8, fp, ip, sp, pc}^
d0020b10:	447848a9 	ldrbtmi	r4, [r8], #-2217	; 0xfffff757
d0020b14:	f7fe2401 			; <UNDEFINED> instruction: 0xf7fe2401
d0020b18:	4620fe9f 			; <UNDEFINED> instruction: 0x4620fe9f
d0020b1c:	ecbdb017 	ldc	0, cr11, [sp], #92	; 0x5c
d0020b20:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d0020b24:	2e008ff0 	mcrcs	15, 0, r8, cr0, cr0, {7}
d0020b28:	f104d05d 			; <UNDEFINED> instruction: 0xf104d05d
d0020b2c:	25004480 	strcs	r4, [r0, #-1152]	; 0xfffffb80
d0020b30:	46ab3c01 	strtmi	r3, [fp], r1, lsl #24
d0020b34:	0024f857 	eoreq	pc, r4, r7, asr r8	; <UNPREDICTABLE>
d0020b38:	f8df2401 			; <UNDEFINED> instruction: 0xf8df2401
d0020b3c:	49a08280 	stmibmi	r0!, {r7, r9, pc}
d0020b40:	447944f8 	ldrbtmi	r4, [r9], #-1272	; 0xfffffb08
d0020b44:	f7ff4642 			; <UNDEFINED> instruction: 0xf7ff4642
d0020b48:	2800f9ef 	stmdacs	r0, {r0, r1, r2, r3, r5, r6, r7, r8, fp, ip, sp, lr, pc}
d0020b4c:	489dd15f 	ldmmi	sp, {r0, r1, r2, r3, r4, r6, r8, ip, lr, pc}
d0020b50:	e7df4478 			; <UNDEFINED> instruction: 0xe7df4478
d0020b54:	0389ea4f 	orreq	lr, r9, #323584	; 0x4f000
d0020b58:	1a10ee18 	bne	0xd045c3c0
d0020b5c:	0029f857 	eoreq	pc, r9, r7, asr r8	; <UNPREDICTABLE>
d0020b60:	0889eb07 	stmeq	r9, {r0, r1, r2, r8, r9, fp, sp, lr, pc}
d0020b64:	f0019302 			; <UNDEFINED> instruction: 0xf0019302
d0020b68:	b960fded 	stmdblt	r0!, {r0, r2, r3, r5, r6, r7, r8, sl, fp, ip, sp, lr, pc}^
d0020b6c:	f109b946 			; <UNDEFINED> instruction: 0xf109b946
d0020b70:	42a10101 	adcmi	r0, r1, #1073741824	; 0x40000000
d0020b74:	f8d8da04 			; <UNDEFINED> instruction: 0xf8d8da04
d0020b78:	78091004 	stmdavc	r9, {r2, ip}
d0020b7c:	d130292d 	teqle	r0, sp, lsr #18
d0020b80:	44784891 	ldrbtmi	r4, [r8], #-2193	; 0xfffff76f
d0020b84:	4651e7c6 	ldrbmi	lr, [r1], -r6, asr #15
d0020b88:	0029f857 	eoreq	pc, r9, r7, asr r8	; <UNPREDICTABLE>
d0020b8c:	fddaf001 	ldc2l	0, cr15, [sl, #4]
d0020b90:	f1bbb978 			; <UNDEFINED> instruction: 0xf1bbb978
d0020b94:	d1090f00 	tstle	r9, r0, lsl #30
d0020b98:	0901f109 	stmdbeq	r1, {r0, r3, r8, ip, sp, lr, pc}
d0020b9c:	da0545a1 	ble	0xd0172228
d0020ba0:	b004f8d8 	ldrdlt	pc, [r4], -r8
d0020ba4:	1000f89b 	mulne	r0, fp, r8
d0020ba8:	d112292d 	tstle	r2, sp, lsr #18
d0020bac:	44784887 	ldrbtmi	r4, [r8], #-2183	; 0xfffff779
d0020bb0:	9b02e7b0 	blls	0xd00daa78
d0020bb4:	780858f9 	stmdavc	r8, {r0, r3, r4, r5, r6, r7, fp, ip, lr}
d0020bb8:	d001282d 	andle	r2, r1, sp, lsr #16
d0020bbc:	d9022d0f 	stmdble	r2, {r0, r1, r2, r3, r8, sl, fp, sp}
d0020bc0:	44784883 	ldrbtmi	r4, [r8], #-2179	; 0xfffff77d
d0020bc4:	ab16e7a6 	blge	0xd05daa64
d0020bc8:	0085eb03 	addeq	lr, r5, r3, lsl #22
d0020bcc:	f8403501 			; <UNDEFINED> instruction: 0xf8403501
d0020bd0:	f1091c40 			; <UNDEFINED> instruction: 0xf1091c40
d0020bd4:	45a10901 	strmi	r0, [r1, #2305]!	; 0x901
d0020bd8:	b985dbbc 	stmiblt	r5, {r2, r3, r4, r5, r7, r8, r9, fp, ip, lr, pc}
d0020bdc:	4478487d 	ldrbtmi	r4, [r8], #-2173	; 0xfffff783
d0020be0:	2601e798 			; <UNDEFINED> instruction: 0x2601e798
d0020be4:	4b7ce7f5 	blmi	0xd1f5abc0
d0020be8:	0901f04f 	stmdbeq	r1, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d0020bec:	a1ecf8df 	ldrdge	pc, [ip, #143]!	; 0x8f
d0020bf0:	447b4635 	ldrbtmi	r4, [fp], #-1589	; 0xfffff9cb
d0020bf4:	44fa46b3 	ldrbtmi	r4, [sl], #1715	; 0x6b3
d0020bf8:	3a10ee08 	bcc	0xd045c420
d0020bfc:	9806e7eb 	stmdals	r6, {r0, r1, r3, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d0020c00:	e79a2400 	ldr	r2, [sl, r0, lsl #8]
d0020c04:	48762500 	ldmdami	r6!, {r8, sl, sp}^
d0020c08:	447846ab 	ldrbtmi	r4, [r8], #-1707	; 0xfffff955
d0020c0c:	f1bbe795 			; <UNDEFINED> instruction: 0xf1bbe795
d0020c10:	d0290f00 	eorle	r0, r9, r0, lsl #30
d0020c14:	46584a73 			; <UNDEFINED> instruction: 0x46584a73
d0020c18:	447a4973 	ldrbtmi	r4, [sl], #-2419	; 0xfffff68d
d0020c1c:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d0020c20:	2800f983 	stmdacs	r0, {r0, r1, r7, r8, fp, ip, sp, lr, pc}
d0020c24:	4871d093 	ldmdami	r1!, {r0, r1, r4, r7, ip, lr, pc}^
d0020c28:	f0014478 			; <UNDEFINED> instruction: 0xf0014478
d0020c2c:	38f7fd7f 	ldmcc	r7!, {r0, r1, r2, r3, r4, r5, r6, r8, sl, fp, ip, sp, lr, pc}^
d0020c30:	7f81f510 	svcvc	0x0081f510
d0020c34:	2c00d98b 			; <UNDEFINED> instruction: 0x2c00d98b
d0020c38:	8086f040 	addhi	pc, r6, r0, asr #32
d0020c3c:	46274b6c 	strtmi	r4, [r7], -ip, ror #22
d0020c40:	a1b0f8df 	asrsge	pc, pc	; <illegal shifter operand>	; <UNPREDICTABLE>
d0020c44:	f8df447b 			; <UNDEFINED> instruction: 0xf8df447b
d0020c48:	44fab1b0 	ldrbtmi	fp, [sl], #432	; 0x1b0
d0020c4c:	44fb601c 	ldrbtmi	r6, [fp], #28
d0020c50:	447b4b6a 	ldrbtmi	r4, [fp], #-2922	; 0xfffff496
d0020c54:	42ac9302 	adcmi	r9, ip, #134217728	; 0x8000000
d0020c58:	2000d11d 	andcs	sp, r0, sp, lsl r1
d0020c5c:	fb08f7ff 	blx	0xd025ec62
d0020c60:	f480fab0 	vst3.32			; <UNDEFINED> instruction: 0xf480fab0
d0020c64:	e7580964 	ldrb	r0, [r8, -r4, ror #18]
d0020c68:	f0014640 			; <UNDEFINED> instruction: 0xf0014640
d0020c6c:	1cc3fd5f 	stclne	13, cr15, [r3], {95}	; 0x5f
d0020c70:	7f80f5b3 	svcvc	0x0080f5b3
d0020c74:	af6bf63f 	svcge	0x006bf63f
d0020c78:	1e464f61 	cdpne	15, 4, cr4, cr6, cr1, {3}
d0020c7c:	447f4641 	ldrbtmi	r4, [pc], #-1601	; 0xd0020c84
d0020c80:	46384632 			; <UNDEFINED> instruction: 0x46384632
d0020c84:	f948f000 			; <UNDEFINED> instruction: 0xf948f000
d0020c88:	2204495e 	andcs	r4, r4, #1540096	; 0x178000
d0020c8c:	447919b8 	ldrbtmi	r1, [r9], #-2488	; 0xfffff648
d0020c90:	f942f000 			; <UNDEFINED> instruction: 0xf942f000
d0020c94:	9a02e7c7 	bls	0xd00dabb8
d0020c98:	f8daab06 			; <UNDEFINED> instruction: 0xf8daab06
d0020c9c:	46598000 	ldrbmi	r8, [r9], -r0
d0020ca0:	3024f853 	eorcc	pc, r4, r3, asr r8	; <UNPREDICTABLE>
d0020ca4:	2908eb02 	stmdbcs	r8, {r1, r8, r9, fp, sp, lr, pc}
d0020ca8:	93034618 	movwls	r4, #13848	; 0x3618
d0020cac:	f7ff464a 			; <UNDEFINED> instruction: 0xf7ff464a
d0020cb0:	9b03f93b 	blls	0xd011f1a4
d0020cb4:	4c54b948 	mrrcmi	9, 4, fp, r4, cr8	; <UNPREDICTABLE>
d0020cb8:	447c4a54 	ldrbtmi	r4, [ip], #-2644	; 0xfffff5ac
d0020cbc:	f44f447a 	vst3.16	{d20-d22}, [pc :256], sl
d0020cc0:	462071c0 	strtmi	r7, [r0], -r0, asr #3
d0020cc4:	fcfaf001 	ldc2l	0, cr15, [sl], #4
d0020cc8:	2300e01f 	movwcs	lr, #31
d0020ccc:	0607eb08 	streq	lr, [r7], -r8, lsl #22
d0020cd0:	1280f5c7 	addne	pc, r0, #834666496	; 0x31c00000
d0020cd4:	93054648 	movwls	r4, #22088	; 0x5648
d0020cd8:	447b4b4d 	ldrbtmi	r4, [fp], #-2893	; 0xfffff4b3
d0020cdc:	ab05441e 	blge	0xd0171d5c
d0020ce0:	f7fe4631 			; <UNDEFINED> instruction: 0xf7fe4631
d0020ce4:	4601fdd9 			; <UNDEFINED> instruction: 0x4601fdd9
d0020ce8:	1cc3b188 	stfnep	f3, [r3], {136}	; 0x88
d0020cec:	4849d102 	stmdami	r9, {r1, r8, ip, lr, pc}^
d0020cf0:	e70f4478 	smlsdx	pc, r8, r4, r4	; <UNPREDICTABLE>
d0020cf4:	464b4c48 	strbmi	r4, [fp], -r8, asr #24
d0020cf8:	f44f4a48 	vst1.16	{d20-d21}, [pc], r8
d0020cfc:	447c71c0 	ldrbtmi	r7, [ip], #-448	; 0xfffffe40
d0020d00:	447a9000 	ldrbtmi	r9, [sl], #-0
d0020d04:	f0014620 			; <UNDEFINED> instruction: 0xf0014620
d0020d08:	4620fcd9 			; <UNDEFINED> instruction: 0x4620fcd9
d0020d0c:	9a05e702 	bls	0xd019a91c
d0020d10:	f0014630 			; <UNDEFINED> instruction: 0xf0014630
d0020d14:	b128fcf5 	strdlt	pc, [r8, -r5]!
d0020d18:	464b4c41 	strbmi	r4, [fp], -r1, asr #24
d0020d1c:	447c4a41 	ldrbtmi	r4, [ip], #-2625	; 0xfffff5bf
d0020d20:	e7cc447a 			; <UNDEFINED> instruction: 0xe7cc447a
d0020d24:	34014b40 	strcc	r4, [r1], #-2880	; 0xfffff4c0
d0020d28:	447b9a05 	ldrbtmi	r9, [fp], #-2565	; 0xfffff5fb
d0020d2c:	54b04417 	ldrtpl	r4, [r0], #1047	; 0x417
d0020d30:	6038f843 	eorsvs	pc, r8, r3, asr #16
d0020d34:	08c8eb03 	stmiaeq	r8, {r0, r1, r8, r9, fp, sp, lr, pc}^
d0020d38:	3000f8da 	ldrdcc	pc, [r0], -sl
d0020d3c:	2004f8c8 	andcs	pc, r4, r8, asr #17
d0020d40:	f8ca3301 			; <UNDEFINED> instruction: 0xf8ca3301
d0020d44:	e7863000 	str	r3, [r6, r0]
d0020d48:	23004d38 	movwcs	r4, #3384	; 0xd38
d0020d4c:	f44f4838 	vst2.8	{d20-d21}, [pc :256], r8
d0020d50:	447d1280 	ldrbtmi	r1, [sp], #-640	; 0xfffffd80
d0020d54:	44789305 	ldrbtmi	r9, [r8], #-773	; 0xfffffcfb
d0020d58:	4629ab05 	strtmi	sl, [r9], -r5, lsl #22
d0020d5c:	fd9cf7fe 	ldc2	7, cr15, [ip, #1016]	; 0x3f8
d0020d60:	4601b948 	strmi	fp, [r1], -r8, asr #18
d0020d64:	46289a05 	strtmi	r9, [r8], -r5, lsl #20
d0020d68:	fccaf001 	stc2l	0, cr15, [sl], {1}
d0020d6c:	9b05b980 	blls	0xd018f374
d0020d70:	200054e8 	andcs	r5, r0, r8, ror #9
d0020d74:	2804e008 	stmdacs	r4, {r3, sp, lr, pc}
d0020d78:	492ed10c 	stmdbmi	lr!, {r2, r3, r8, ip, lr, pc}
d0020d7c:	4628227d 			; <UNDEFINED> instruction: 0x4628227d
d0020d80:	f0004479 			; <UNDEFINED> instruction: 0xf0004479
d0020d84:	2001f8c9 	andcs	pc, r1, r9, asr #17
d0020d88:	fe1ef7fe 	mrc2	7, 0, pc, cr14, cr14, {7}
d0020d8c:	e6c44604 	strb	r4, [r4], r4, lsl #12
d0020d90:	0003f06f 	andeq	pc, r3, pc, rrx
d0020d94:	44794928 	ldrbtmi	r4, [r9], #-2344	; 0xfffff6d8
d0020d98:	f848f7ff 			; <UNDEFINED> instruction: 0xf848f7ff
d0020d9c:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0020da0:	e7e6aebc 			; <UNDEFINED> instruction: 0xe7e6aebc
d0020da4:	f77f2800 			; <UNDEFINED> instruction: 0xf77f2800
d0020da8:	2600aeb3 			; <UNDEFINED> instruction: 0x2600aeb3
d0020dac:	bf00e6a9 	svclt	0x0000e6a9
d0020db0:	fffffe0a 			; <UNDEFINED> instruction: 0xfffffe0a
d0020db4:	fffffdfa 			; <UNDEFINED> instruction: 0xfffffdfa
d0020db8:	fffffdf1 			; <UNDEFINED> instruction: 0xfffffdf1
d0020dbc:	001534b4 			; <UNDEFINED> instruction: 0x001534b4
d0020dc0:	fffffedd 			; <UNDEFINED> instruction: 0xfffffedd
d0020dc4:	fffffed2 			; <UNDEFINED> instruction: 0xfffffed2
d0020dc8:	fffffdc9 			; <UNDEFINED> instruction: 0xfffffdc9
d0020dcc:	fffffdd5 			; <UNDEFINED> instruction: 0xfffffdd5
d0020dd0:	fffffdf6 			; <UNDEFINED> instruction: 0xfffffdf6
d0020dd4:	fffffe0a 			; <UNDEFINED> instruction: 0xfffffe0a
d0020dd8:	fffffd56 			; <UNDEFINED> instruction: 0xfffffd56
d0020ddc:	fffffd8a 			; <UNDEFINED> instruction: 0xfffffd8a
d0020de0:	fffffcee 			; <UNDEFINED> instruction: 0xfffffcee
d0020de4:	0005213a 	andeq	r2, r5, sl, lsr r1
d0020de8:	fffffe3a 			; <UNDEFINED> instruction: 0xfffffe3a
d0020dec:	0005212c 	andeq	r2, r5, ip, lsr #2
d0020df0:	00052318 	andeq	r2, r5, r8, lsl r3
d0020df4:	00052312 	andeq	r2, r5, r2, lsl r3
d0020df8:	fffffdd1 			; <UNDEFINED> instruction: 0xfffffdd1
d0020dfc:	0005230e 	andeq	r2, r5, lr, lsl #6
d0020e00:	000520d6 	ldrdeq	r2, [r5], -r6
d0020e04:	fffffdcd 			; <UNDEFINED> instruction: 0xfffffdcd
d0020e08:	0015353a 	andseq	r3, r5, sl, lsr r5
d0020e0c:	fffffda3 			; <UNDEFINED> instruction: 0xfffffda3
d0020e10:	0005330a 	andeq	r3, r5, sl, lsl #6
d0020e14:	fffffd8a 			; <UNDEFINED> instruction: 0xfffffd8a
d0020e18:	001534f6 			; <UNDEFINED> instruction: 0x001534f6
d0020e1c:	fffffd96 			; <UNDEFINED> instruction: 0xfffffd96
d0020e20:	001534d6 			; <UNDEFINED> instruction: 0x001534d6
d0020e24:	fffffd8f 			; <UNDEFINED> instruction: 0xfffffd8f
d0020e28:	00053236 	andeq	r3, r5, r6, lsr r2
d0020e2c:	00053292 	muleq	r5, r2, r2
d0020e30:	0015329e 	mulseq	r5, lr, r2
d0020e34:	000000b8 	strheq	r0, [r0], -r8
d0020e38:	fffffd31 			; <UNDEFINED> instruction: 0xfffffd31

Disassembly of section .text.initMalloc:

d0020ebc <.text.initMalloc>:
d0020ebc:	f44f4b06 			; <UNDEFINED> instruction: 0xf44f4b06
d0020ec0:	4a064180 	bmi	0xd01b14c8
d0020ec4:	589a447b 	ldmpl	sl, {r0, r1, r3, r4, r5, r6, sl, lr}
d0020ec8:	4a056011 	bmi	0xd0178f14
d0020ecc:	4b05589a 	blmi	0xd017713c
d0020ed0:	601a447b 	andsvs	r4, sl, fp, ror r4
d0020ed4:	bf004770 	svclt	0x00004770
d0020ed8:	000018e4 	andeq	r1, r0, r4, ror #17
d0020edc:	00000004 	andeq	r0, r0, r4
d0020ee0:	00000000 	andeq	r0, r0, r0
d0020ee4:	001555dc 			; <UNDEFINED> instruction: 0x001555dc

Disassembly of section .text.applet_entry:

d0020ee8 <.text.applet_entry>:
d0020ee8:	9101b507 	tstls	r1, r7, lsl #10
d0020eec:	ffe6f7ff 			; <UNDEFINED> instruction: 0xffe6f7ff
d0020ef0:	b0039901 	andlt	r9, r3, r1, lsl #18
d0020ef4:	eb04f85d 	bl	0xd015f070
d0020ef8:	bdeef7ff 	stcllt	7, cr15, [lr, #1020]!	; 0x3fc

Disassembly of section .text.progress_report:

d0010198 <.text.progress_report>:
d0010198:	4a084613 	bmi	0xd02219ec
d001019c:	b410447a 	ldrlt	r4, [r0], #-1146	; 0xfffffb86
d00101a0:	b1446814 	cmplt	r4, r4, lsl r8
d00101a4:	4601460a 	strmi	r4, [r1], -sl, lsl #12
d00101a8:	46a44805 	strtmi	r4, [r4], r5, lsl #16
d00101ac:	4b04f85d 	blmi	0xd014e328
d00101b0:	68004478 	stmdavs	r0, {r3, r4, r5, r6, sl, lr}
d00101b4:	f85d4760 			; <UNDEFINED> instruction: 0xf85d4760
d00101b8:	47704b04 	ldrbmi	r4, [r0, -r4, lsl #22]!
d00101bc:	00062ba0 	andeq	r2, r6, r0, lsr #23
d00101c0:	00062b90 	muleq	r6, r0, fp

Disassembly of section .text.progress_parse:

d00101d4 <.text.progress_parse>:
d00101d4:	4b18b538 	blmi	0xd063d6bc
d00101d8:	681b447b 	ldmdavs	fp, {r0, r1, r3, r4, r5, r6, sl, lr}
d00101dc:	6f83b35b 	svcvs	0x0083b35b
d00101e0:	da282b00 	ble	0xd0a1ade8
d00101e4:	447b4b15 	ldrbtmi	r4, [fp], #-2837	; 0xfffff4eb
d00101e8:	f5b2681a 			; <UNDEFINED> instruction: 0xf5b2681a
d00101ec:	d3224f00 			; <UNDEFINED> instruction: 0xd3224f00
d00101f0:	447d4d13 	ldrbtmi	r4, [sp], #-3347	; 0xfffff2ed
d00101f4:	2b64682b 	blcs	0xd192a2a8
d00101f8:	68c1d81d 	stmiavs	r1, {r0, r2, r3, r4, fp, ip, lr, pc}^
d00101fc:	44784811 	ldrbtmi	r4, [r8], #-2065	; 0xfffff7ef
d0010200:	44016800 	strmi	r6, [r1], #-2048	; 0xfffff800
d0010204:	f002fb03 			; <UNDEFINED> instruction: 0xf002fb03
d0010208:	30632364 	rsbcc	r2, r3, r4, ror #6
d001020c:	fbb04291 	blx	0xcec20c5a
d0010210:	bf28f0f3 	svclt	0x0028f0f3
d0010214:	42814611 	addmi	r4, r1, #17825792	; 0x1100000
d0010218:	434bd30d 	movtmi	sp, #45837	; 0xb30d
d001021c:	fbb3480a 	blx	0xcece224e
d0010220:	4478f4f2 	ldrbtmi	pc, [r8], #-1266	; 0xfffffb0e	; <UNPREDICTABLE>
d0010224:	ffb8f7ff 			; <UNDEFINED> instruction: 0xffb8f7ff
d0010228:	fbb42305 	blx	0xced18e46
d001022c:	3301f3f3 	movwcc	pc, #5107	; 0x13f3	; <UNPREDICTABLE>
d0010230:	0383eb03 	orreq	lr, r3, #3072	; 0xc00
d0010234:	bd38602b 	ldclt	0, cr6, [r8, #-172]!	; 0xffffff54
d0010238:	00062b64 	andeq	r2, r6, r4, ror #22
d001023c:	00062b66 	andeq	r2, r6, r6, ror #22
d0010240:	00062b52 	andeq	r2, r6, r2, asr fp
d0010244:	00062b4a 	andeq	r2, r6, sl, asr #22
d0010248:	ffffff9e 			; <UNDEFINED> instruction: 0xffffff9e

Disassembly of section .text.error:

d001024c <.text.error>:
d001024c:	b5306d83 	ldrlt	r6, [r0, #-3459]!	; 0xfffff27d
d0010250:	6a45b94b 	bvs	0xd117e784
d0010254:	6b436a84 	blvs	0xd10eac6c
d0010258:	2030f890 	mlascs	r0, r0, r8, pc	; <UNPREDICTABLE>
d001025c:	e9c06683 	stmib	r0, {r0, r1, r7, r9, sl, sp, lr}^
d0010260:	e9c01516 	stmib	r0, {r1, r2, r4, r8, sl, ip}^
d0010264:	bd304218 	lfmlt	f4, 4, [r0, #-96]!	; 0xffffffa0

Disassembly of section .text.peek:

d0010268 <.text.peek>:
d0010268:	441968c3 	ldrmi	r6, [r9], #-2243	; 0xfffff73d
d001026c:	428b6843 	addmi	r6, fp, #4390912	; 0x430000
d0010270:	6803bf86 	stmdavs	r3, {r1, r2, r7, r8, r9, sl, fp, ip, sp, pc}
d0010274:	20005c58 	andcs	r5, r0, r8, asr ip
d0010278:	Address 0x00000000d0010278 is out of bounds.


Disassembly of section .text.read_char:

d001027a <.text.read_char>:
d001027a:	460268c3 	strmi	r6, [r2], -r3, asr #17
d001027e:	428b6841 	addmi	r6, fp, #4259840	; 0x410000
d0010282:	d016b510 	andsle	fp, r6, r0, lsl r5
d0010286:	68011c5c 	stmdavs	r1, {r2, r3, r4, r6, sl, fp, ip}
d001028a:	5ccc60c4 	stclpl	0, cr6, [ip], {196}	; 0xc4
d001028e:	d0062c0a 	andle	r2, r6, sl, lsl #24
d0010292:	d10b2c0d 	tstle	fp, sp, lsl #24
d0010296:	f7ff2100 			; <UNDEFINED> instruction: 0xf7ff2100
d001029a:	280affe6 	stmdacs	sl, {r1, r2, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d001029e:	6913d006 	ldmdbvs	r3, {r1, r2, ip, lr, pc}
d00102a2:	61133301 	tstvs	r3, r1, lsl #6
d00102a6:	61532301 	cmpvs	r3, r1, lsl #6
d00102aa:	bd104620 	ldclt	6, cr4, [r0, #-128]	; 0xffffff80
d00102ae:	33016953 	movwcc	r6, #6483	; 0x1953
d00102b2:	2400e7f9 	strcs	lr, [r0], #-2041	; 0xfffff807
d00102b6:	Address 0x00000000d00102b6 is out of bounds.


Disassembly of section .text.here:

d00102b8 <.text.here>:
d00102b8:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d00102bc:	4604680b 	strmi	r6, [r4], -fp, lsl #16
d00102c0:	221868cd 	andscs	r6, r8, #13434880	; 0xcd0000
d00102c4:	30047a0f 	andcc	r7, r4, pc, lsl #20
d00102c8:	6f8b441d 	svcvs	0x008b441d
d00102cc:	e9d12b00 	ldmib	r1, {r8, r9, fp, sp}^
d00102d0:	bfa89804 	svclt	0x00a89804
d00102d4:	f04f6f4e 			; <UNDEFINED> instruction: 0xf04f6f4e
d00102d8:	bfb80100 	svclt	0x00b80100
d00102dc:	f0102600 			; <UNDEFINED> instruction: 0xf0102600
d00102e0:	f44ffe0d 			; <UNDEFINED> instruction: 0xf44ffe0d
d00102e4:	46207380 	strtmi	r7, [r0], -r0, lsl #7
d00102e8:	f8c46025 			; <UNDEFINED> instruction: 0xf8c46025
d00102ec:	f8c4900c 			; <UNDEFINED> instruction: 0xf8c4900c
d00102f0:	61638010 	cmnvs	r3, r0, lsl r0
d00102f4:	61e67627 	mvnvs	r7, r7, lsr #12
d00102f8:	83f8e8bd 	mvnshi	lr, #12386304	; 0xbd0000

Disassembly of section .text.preproc_active:

d00102fc <.text.preproc_active>:
d00102fc:	030cf24d 	movweq	pc, #49741	; 0xc24d	; <UNPREDICTABLE>
d0010300:	b14b58c3 	smlalbtlt	r5, fp, r3, r8
d0010304:	534ff503 	movtpl	pc, #62723	; 0xf503	; <UNPREDICTABLE>
d0010308:	eb003321 	bl	0xd001cf94
d001030c:	79400083 	stmdbvc	r0, {r0, r1, r7}^
d0010310:	bf183800 	svclt	0x00183800
d0010314:	47702001 	ldrbmi	r2, [r0, -r1]!
d0010318:	47702001 	ldrbmi	r2, [r0, -r1]!

Disassembly of section .text.pp_space:

d001031c <.text.pp_space>:
d001031c:	6a436a81 	bvs	0xd10ead28
d0010320:	d204428b 	andle	r4, r4, #-1342177272	; 0xb0000008
d0010324:	2a20781a 	bcs	0xd082e394
d0010328:	2a09d002 	bcs	0xd0284338
d001032c:	4770d000 	ldrbmi	sp, [r0, -r0]!
d0010330:	62433301 	subvs	r3, r3, #67108864	; 0x4000000
d0010334:	Address 0x00000000d0010334 is out of bounds.


Disassembly of section .text.pp_line_end:

d0010336 <.text.pp_line_end>:
d0010336:	4604b510 			; <UNDEFINED> instruction: 0x4604b510
d001033a:	686368e2 	stmdavs	r3!, {r1, r5, r6, r7, fp, sp, lr}^
d001033e:	d207429a 	andle	r4, r7, #-1610612727	; 0xa0000009
d0010342:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d0010346:	ff8ff7ff 			; <UNDEFINED> instruction: 0xff8ff7ff
d001034a:	d001280d 	andle	r2, r1, sp, lsl #16
d001034e:	d100280a 	tstle	r0, sl, lsl #16
d0010352:	4620bd10 			; <UNDEFINED> instruction: 0x4620bd10
d0010356:	ff90f7ff 			; <UNDEFINED> instruction: 0xff90f7ff
d001035a:	Address 0x00000000d001035a is out of bounds.


Disassembly of section .text.enum_constant_lookup:

d001035c <.text.enum_constant_lookup>:
d001035c:	337ef500 	cmncc	lr, #0, 10	; <UNPREDICTABLE>
d0010360:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d0010364:	4190f8d3 			; <UNDEFINED> instruction: 0x4190f8d3
d0010368:	46062328 	strmi	r2, [r6], -r8, lsr #6
d001036c:	1e654688 	cdpne	6, 6, cr4, cr5, cr8, {4}
d0010370:	0404fb03 	streq	pc, [r4], #-2819	; 0xfffff4fd
d0010374:	f5044617 			; <UNDEFINED> instruction: 0xf5044617
d0010378:	34683478 	strbtcc	r3, [r8], #-1144	; 0xfffffb88
d001037c:	da022d00 	ble	0xd009b784
d0010380:	35fff04f 	ldrbcc	pc, [pc, #79]!	; 0xd00103d7	; <UNPREDICTABLE>
d0010384:	f894e011 			; <UNDEFINED> instruction: 0xf894e011
d0010388:	7a332024 	bvc	0xd0cd8420
d001038c:	d002429a 	mulle	r2, sl, r2
d0010390:	3c283d01 	stccc	13, cr3, [r8], #-4
d0010394:	6863e7f2 	stmdavs	r3!, {r1, r4, r5, r6, r7, r8, r9, sl, sp, lr, pc}^
d0010398:	d1f942bb 	ldrhle	r4, [r9, #43]!	; 0x2b
d001039c:	4641463a 			; <UNDEFINED> instruction: 0x4641463a
d00103a0:	f0106820 			; <UNDEFINED> instruction: 0xf0106820
d00103a4:	2800fdc9 	stmdacs	r0, {r0, r3, r6, r7, r8, sl, fp, ip, sp, lr, pc}
d00103a8:	4628d1f2 			; <UNDEFINED> instruction: 0x4628d1f2
d00103ac:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d

Disassembly of section .text.pp_take:

d00103b0 <.text.pp_take>:
d00103b0:	460eb570 			; <UNDEFINED> instruction: 0x460eb570
d00103b4:	f7ff4604 			; <UNDEFINED> instruction: 0xf7ff4604
d00103b8:	4630ffb1 			; <UNDEFINED> instruction: 0x4630ffb1
d00103bc:	f9b6f012 			; <UNDEFINED> instruction: 0xf9b6f012
d00103c0:	46056aa3 	strmi	r6, [r5], -r3, lsr #21
d00103c4:	1a1b6a60 	bne	0xd06ead4c
d00103c8:	d20142ab 	andle	r4, r1, #-1342177270	; 0xb000000a
d00103cc:	bd702000 	ldcllt	0, cr2, [r0, #-0]
d00103d0:	4631462a 	ldrtmi	r4, [r1], -sl, lsr #12
d00103d4:	fdb0f010 	ldc2	0, cr15, [r0, #64]!	; 0x40
d00103d8:	d1f72800 	mvnsle	r2, r0, lsl #16
d00103dc:	44286a60 	strtmi	r6, [r8], #-2656	; 0xfffff5a0
d00103e0:	20016260 	andcs	r6, r1, r0, ror #4
d00103e4:	Address 0x00000000d00103e4 is out of bounds.


Disassembly of section .text.macro_index:

d00103e6 <.text.macro_index>:
d00103e6:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d00103ea:	462bf500 	strtmi	pc, [fp], -r0, lsl #10
d00103ee:	444ff500 	strbmi	pc, [pc], #-1280	; 0xd00103f6	; <UNPREDICTABLE>
d00103f2:	46174688 	ldrmi	r4, [r7], -r8, lsl #13
d00103f6:	25003688 	strcs	r3, [r0, #-1672]	; 0xfffff978
d00103fa:	68233488 	stmdavs	r3!, {r3, r7, sl, ip, sp}
d00103fe:	d80242ab 	stmdale	r2, {r0, r1, r3, r5, r7, r9, lr}
d0010402:	30fff04f 	rscscc	pc, pc, pc, asr #32
d0010406:	4630e00b 	ldrtmi	lr, [r0], -fp
d001040a:	f98ff012 			; <UNDEFINED> instruction: 0xf98ff012
d001040e:	d10842b8 			; <UNDEFINED> instruction: 0xd10842b8
d0010412:	4641463a 			; <UNDEFINED> instruction: 0x4641463a
d0010416:	f0104630 			; <UNDEFINED> instruction: 0xf0104630
d001041a:	b910fd8e 	ldmdblt	r0, {r1, r2, r3, r7, r8, sl, fp, ip, sp, lr, pc}
d001041e:	e8bd4628 	pop	{r3, r5, r9, sl, lr}
d0010422:	350181f0 	strcc	r8, [r1, #-496]	; 0xfffffe10
d0010426:	e7e83648 	strb	r3, [r8, r8, asr #12]!

Disassembly of section .text.letter:

d001042a <.text.letter>:
d001042a:	0320f020 	nopeq	{32}
d001042e:	2b193b41 	blcs	0xd065f13a
d0010432:	f1a0d904 			; <UNDEFINED> instruction: 0xf1a0d904
d0010436:	4258035f 	subsmi	r0, r8, #2080374785	; 0x7c000001
d001043a:	47704158 			; <UNDEFINED> instruction: 0x47704158
d001043e:	47702001 	ldrbmi	r2, [r0, -r1]!

Disassembly of section .text.valid_api_name:

d0010448 <.text.valid_api_name>:
d0010448:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d001044c:	46884606 	strmi	r4, [r8], r6, lsl #12
d0010450:	b19a4617 	orrslt	r4, sl, r7, lsl r6
d0010454:	2204491a 	andcs	r4, r4, #425984	; 0x68000
d0010458:	f0104479 			; <UNDEFINED> instruction: 0xf0104479
d001045c:	bb58fd6d 	bllt	0xd164fa18
d0010460:	5d302404 	cfldrspl	mvf2, [r0, #-16]!
d0010464:	ffe1f7ff 			; <UNDEFINED> instruction: 0xffe1f7ff
d0010468:	2500b330 	strcs	fp, [r0, #-816]	; 0xfffffcd0
d001046c:	b93a5d32 	ldmdblt	sl!, {r1, r4, r5, r8, sl, fp, ip, lr}
d0010470:	1e28b327 	cdpne	3, 2, cr11, cr8, cr7, {1}
d0010474:	2001bf18 	andcs	fp, r1, r8, lsl pc
d0010478:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d001047c:	e7f04614 			; <UNDEFINED> instruction: 0xe7f04614
d0010480:	2a2db197 	bcs	0xd0b7cae4
d0010484:	1ca3d110 	stfned	f5, [r3], #64	; 0x40
d0010488:	d20d4543 	andle	r4, sp, #281018368	; 0x10c00000
d001048c:	5c701c61 	ldclpl	12, cr1, [r0], #-388	; 0xfffffe7c
d0010490:	d109283e 	tstle	r9, lr, lsr r8
d0010494:	f7ff5cf0 			; <UNDEFINED> instruction: 0xf7ff5cf0
d0010498:	b128ffc8 	smlawtlt	r8, r8, pc, pc	; <UNPREDICTABLE>
d001049c:	460c3501 	strmi	r3, [ip], -r1, lsl #10
d00104a0:	45a03401 	strmi	r3, [r0, #1025]!	; 0x401
d00104a4:	e007d8e2 	and	sp, r7, r2, ror #17
d00104a8:	f7ff4610 			; <UNDEFINED> instruction: 0xf7ff4610
d00104ac:	2800ffbe 	stmdacs	r0, {r1, r2, r3, r4, r5, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d00104b0:	3a30d1f6 	bcc	0xd0c44c90
d00104b4:	d9f32a09 	ldmible	r3!, {r0, r3, r9, fp, sp}^
d00104b8:	e7dd2000 	ldrb	r2, [sp, r0]
d00104bc:	e7db2001 	ldrb	r2, [fp, r1]
d00104c0:	ffffffe6 			; <UNDEFINED> instruction: 0xffffffe6

Disassembly of section .text.hex_digit:

d00104c4 <.text.hex_digit>:
d00104c4:	38304603 	ldmdacc	r0!, {r0, r1, r9, sl, lr}
d00104c8:	d9082809 	stmdble	r8, {r0, r3, fp, sp}
d00104cc:	0020f043 	eoreq	pc, r0, r3, asr #32
d00104d0:	0361f1a0 	msreq	SPSR_c, #160, 2	; 0x28
d00104d4:	d8012b05 	stmdale	r1, {r0, r2, r8, r9, fp, sp}
d00104d8:	47703857 			; <UNDEFINED> instruction: 0x47703857
d00104dc:	47702010 			; <UNDEFINED> instruction: 0x47702010

Disassembly of section .text.escape_byte.isra.0:

d0010518 <.text.escape_byte.isra.0>:
d0010518:	47f0e92d 	ldrbmi	lr, [r0, sp, lsr #18]!
d001051c:	46059e09 	strmi	r9, [r5], -r9, lsl #28
d0010520:	f8dd461f 			; <UNDEFINED> instruction: 0xf8dd461f
d0010524:	6830a020 	ldmdavs	r0!, {r5, sp, pc}
d0010528:	8028f8dd 	ldrdhi	pc, [r8], -sp	; <UNPREDICTABLE>
d001052c:	60331c43 	eorsvs	r1, r3, r3, asr #24
d0010530:	2c787804 	ldclcs	8, cr7, [r8], #-16
d0010534:	2c6dd812 	stclcs	8, cr13, [sp], #-72	; 0xffffffb8
d0010538:	2c3fd828 	ldccs	8, cr13, [pc], #-160	; 0xd00104a0
d001053c:	2c21d84e 	stccs	8, cr13, [r1], #-312	; 0xfffffec8
d0010540:	f1a4d90c 			; <UNDEFINED> instruction: 0xf1a4d90c
d0010544:	fa5f0c22 	blx	0xd17d35d4
d0010548:	f04ffe8c 			; <UNDEFINED> instruction: 0xf04ffe8c
d001054c:	fa0c0c01 	blx	0xd0313558
d0010550:	f8dffc0e 			; <UNDEFINED> instruction: 0xf8dffc0e
d0010554:	ea1ce160 	b	0xd0748adc
d0010558:	d13a0f0e 	teqle	sl, lr, lsl #30
d001055c:	2c073c30 	stccs	12, cr3, [r7], {48}	; 0x30
d0010560:	4543d86a 	strbmi	sp, [r3, #-2154]	; 0xfffff796
d0010564:	7843d035 	stmdavc	r3, {r0, r2, r4, r5, ip, lr, pc}^
d0010568:	2b073b30 	blcs	0xd01df230
d001056c:	f100d831 			; <UNDEFINED> instruction: 0xf100d831
d0010570:	f8c60c02 			; <UNDEFINED> instruction: 0xf8c60c02
d0010574:	45e0c000 	strbmi	ip, [r0, #0]!
d0010578:	f1a37843 			; <UNDEFINED> instruction: 0xf1a37843
d001057c:	eb030330 	bl	0xd00d1244
d0010580:	f04004c4 			; <UNDEFINED> instruction: 0xf04004c4
d0010584:	2cff8086 	ldclcs	0, cr8, [pc], #536	; 0xd00107a4
d0010588:	e022d856 	eor	sp, r2, r6, asr r8
d001058c:	0c6ef1a4 	stfeqp	f7, [lr], #-656	; 0xfffffd70
d0010590:	0f0af1bc 	svceq	0x000af1bc
d0010594:	f20fd8e2 	vadd.i8	<illegal reg q6.5>, <illegal reg q15.5>, q9
d0010598:	f85e0e0c 			; <UNDEFINED> instruction: 0xf85e0e0c
d001059c:	44e6c02c 	strbtmi	ip, [r6], #44	; 0x2c
d00105a0:	bf004770 	svclt	0x00004770
d00105a4:	00000107 	andeq	r0, r0, r7, lsl #2
d00105a8:	ffffffb9 			; <UNDEFINED> instruction: 0xffffffb9
d00105ac:	ffffffb9 			; <UNDEFINED> instruction: 0xffffffb9
d00105b0:	ffffffb9 			; <UNDEFINED> instruction: 0xffffffb9
d00105b4:	0000002d 	andeq	r0, r0, sp, lsr #32
d00105b8:	ffffffb9 			; <UNDEFINED> instruction: 0xffffffb9
d00105bc:	00000089 	andeq	r0, r0, r9, lsl #1
d00105c0:	ffffffb9 			; <UNDEFINED> instruction: 0xffffffb9
d00105c4:	0000008d 	andeq	r0, r0, sp, lsl #1
d00105c8:	ffffffb9 			; <UNDEFINED> instruction: 0xffffffb9
d00105cc:	00000091 	muleq	r0, r1, r0
d00105d0:	4620240d 	strtmi	r2, [r0], -sp, lsl #8
d00105d4:	87f0e8bd 			; <UNDEFINED> instruction: 0x87f0e8bd
d00105d8:	e7fa2408 	ldrb	r2, [sl, r8, lsl #8]!
d00105dc:	0c5cf1a4 	ldfeqp	f7, [ip], {164}	; 0xa4
d00105e0:	fe8cfa5f 	mcr2	10, 4, pc, cr12, cr15, {2}	; <UNPREDICTABLE>
d00105e4:	0f0af1be 	svceq	0x000af1be
d00105e8:	f1bcd8b8 			; <UNDEFINED> instruction: 0xf1bcd8b8
d00105ec:	d8b50f0a 	ldmle	r5!, {r1, r3, r8, r9, sl, fp}
d00105f0:	0e08f20f 	cdpeq	2, 0, cr15, cr8, cr15, {0}
d00105f4:	c02cf85e 	eorgt	pc, ip, lr, asr r8	; <UNPREDICTABLE>
d00105f8:	477044e6 	ldrbmi	r4, [r0, -r6, ror #9]!
d00105fc:	ffffffd7 			; <UNDEFINED> instruction: 0xffffffd7
d0010600:	ffffff61 			; <UNDEFINED> instruction: 0xffffff61
d0010604:	ffffff61 			; <UNDEFINED> instruction: 0xffffff61
d0010608:	ffffff61 			; <UNDEFINED> instruction: 0xffffff61
d001060c:	ffffff61 			; <UNDEFINED> instruction: 0xffffff61
d0010610:	000000b3 	strheq	r0, [r0], -r3
d0010614:	ffffffdd 			; <UNDEFINED> instruction: 0xffffffdd
d0010618:	ffffff61 			; <UNDEFINED> instruction: 0xffffff61
d001061c:	ffffff61 			; <UNDEFINED> instruction: 0xffffff61
d0010620:	ffffff61 			; <UNDEFINED> instruction: 0xffffff61
d0010624:	0000002d 	andeq	r0, r0, sp, lsr #32
d0010628:	e7d2240c 	ldrb	r2, [r2, ip, lsl #8]
d001062c:	e7d02409 	ldrb	r2, [r0, r9, lsl #8]
d0010630:	e7ce240b 	strb	r2, [lr, fp, lsl #8]
d0010634:	d1044543 	tstle	r4, r3, asr #10
d0010638:	b9fc6dac 	ldmiblt	ip!, {r2, r3, r5, r7, r8, sl, fp, sp, lr}^
d001063c:	447b4b1e 	ldrbtmi	r4, [fp], #-2846	; 0xfffff4e2
d0010640:	7840e020 	stmdavc	r0, {r5, sp, lr, pc}^
d0010644:	ff3ef7ff 			; <UNDEFINED> instruction: 0xff3ef7ff
d0010648:	d0f52810 	rscsle	r2, r5, r0, lsl r8
d001064c:	f8d62400 			; <UNDEFINED> instruction: 0xf8d62400
d0010650:	45c89000 	strbmi	r9, [r8]
d0010654:	f899d0bd 			; <UNDEFINED> instruction: 0xf899d0bd
d0010658:	f7ff0000 			; <UNDEFINED> instruction: 0xf7ff0000
d001065c:	2810ff33 	ldmdacs	r0, {r0, r1, r4, r5, r8, r9, sl, fp, ip, sp, lr, pc}
d0010660:	f109d0b7 			; <UNDEFINED> instruction: 0xf109d0b7
d0010664:	01240301 			; <UNDEFINED> instruction: 0x01240301
d0010668:	f8996033 			; <UNDEFINED> instruction: 0xf8996033
d001066c:	f7ff0000 			; <UNDEFINED> instruction: 0xf7ff0000
d0010670:	4404ff29 	strmi	pc, [r4], #-3881	; 0xfffff0d7
d0010674:	d9ea2cff 	stmible	sl!, {r0, r1, r2, r3, r4, r5, r6, r7, sl, fp, sp}^
d0010678:	b10c6dac 	smlatblt	ip, ip, sp, r6
d001067c:	e7a82400 	str	r2, [r8, r0, lsl #8]!
d0010680:	447b4b0e 	ldrbtmi	r4, [fp], #-2830	; 0xfffff4f2
d0010684:	a068f8c5 	rsbge	pc, r8, r5, asr #17
d0010688:	3116e9c5 	tstcc	r6, r5, asr #19
d001068c:	2718e9c5 	ldrcs	lr, [r8, -r5, asr #19]
d0010690:	7883e79f 	stmvc	r3, {r0, r1, r2, r3, r4, r7, r8, r9, sl, sp, lr, pc}
d0010694:	2b073b30 	blcs	0xd01df35c
d0010698:	af75f63f 	svcge	0x0075f63f
d001069c:	60331cc3 	eorsvs	r1, r3, r3, asr #25
d00106a0:	3b307883 	blcc	0xd0c2e8b4
d00106a4:	04c4eb03 	strbeq	lr, [r4], #2819	; 0xb03
d00106a8:	240ae76d 	strcs	lr, [sl], #-1901	; 0xfffff893
d00106ac:	2407e791 	strcs	lr, [r7], #-1937	; 0xfffff86f
d00106b0:	bf00e78f 	svclt	0x0000e78f
d00106b4:	20000021 	andcs	r0, r0, r1, lsr #32
d00106b8:	fffffeb6 			; <UNDEFINED> instruction: 0xfffffeb6
d00106bc:	fffffe5a 			; <UNDEFINED> instruction: 0xfffffe5a

Disassembly of section .text.same_name.isra.0:

d00106c0 <.text.same_name.isra.0>:
d00106c0:	460cb510 			; <UNDEFINED> instruction: 0x460cb510
d00106c4:	429c4611 	addsmi	r4, ip, #17825792	; 0x1100000
d00106c8:	4622d106 	strtmi	sp, [r2], -r6, lsl #2
d00106cc:	fc34f010 	ldc2	0, cr15, [r4], #-64	; 0xffffffc0
d00106d0:	f080fab0 			; <UNDEFINED> instruction: 0xf080fab0
d00106d4:	bd100940 	vldrlt.16	s0, [r0, #-128]	; 0xffffff80	; <UNPREDICTABLE>
d00106d8:	e7fc2000 	ldrb	r2, [ip, r0]!

Disassembly of section .text.find_record.isra.0:

d00106dc <.text.find_record.isra.0>:
d00106dc:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d00106e0:	3467f500 	strbtcc	pc, [r7], #-1280	; 0xfffffb00	; <UNPREDICTABLE>
d00106e4:	4690460f 	ldrmi	r4, [r0], pc, lsl #12
d00106e8:	f5042500 			; <UNDEFINED> instruction: 0xf5042500
d00106ec:	f50074e4 			; <UNDEFINED> instruction: 0xf50074e4
d00106f0:	fa5f3675 	blx	0xd17de0cc
d00106f4:	f8d6f983 			; <UNDEFINED> instruction: 0xf8d6f983
d00106f8:	429d3388 	addsmi	r3, sp, #136, 6	; 0x20000002
d00106fc:	f04fd302 			; <UNDEFINED> instruction: 0xf04fd302
d0010700:	e00e30ff 	strd	r3, [lr], -pc	; <UNPREDICTABLE>
d0010704:	3264f894 	rsbcc	pc, r4, #148, 16	; 0x940000
d0010708:	4643b96b 	strbmi	fp, [r3], -fp, ror #18
d001070c:	e9d4463a 	ldmib	r4, {r1, r3, r4, r5, r9, sl, lr}^
d0010710:	f7ff0100 			; <UNDEFINED> instruction: 0xf7ff0100
d0010714:	b130ffd5 	teqlt	r0, r5	; <illegal shifter operand>	; <UNPREDICTABLE>
d0010718:	3263f894 	rsbcc	pc, r3, #148, 16	; 0x940000
d001071c:	d102454b 	tstle	r2, fp, asr #10
d0010720:	e8bd4628 	pop	{r3, r5, r9, sl, lr}
d0010724:	350183f8 	strcc	r8, [r1, #-1016]	; 0xfffffc08
d0010728:	741af504 	ldrvc	pc, [sl], #-1284	; 0xfffffafc
d001072c:	Address 0x00000000d001072c is out of bounds.


Disassembly of section .text.records_equal:

d001072e <.text.records_equal>:
d001072e:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d0010732:	3260f8d0 	rsbcc	pc, r0, #208, 16	; 0xd00000
d0010736:	f0234606 			; <UNDEFINED> instruction: 0xf0234606
d001073a:	f8d1427f 			; <UNDEFINED> instruction: 0xf8d1427f
d001073e:	f0233260 			; <UNDEFINED> instruction: 0xf0233260
d0010742:	429a437f 	addsmi	r4, sl, #-67108863	; 0xfc000001
d0010746:	2000d002 	andcs	sp, r0, r2
d001074a:	83f8e8bd 	mvnshi	lr, #12386304	; 0xbd0000
d001074e:	2263f890 	rsbcs	pc, r3, #144, 16	; 0x900000
d0010752:	3263f891 	rsbcc	pc, r3, #9502720	; 0x910000
d0010756:	d1f6429a 			; <UNDEFINED> instruction: 0xd1f6429a
d001075a:	460c4605 	strmi	r4, [ip], -r5, lsl #12
d001075e:	f8962700 			; <UNDEFINED> instruction: 0xf8962700
d0010762:	429f3262 	addsmi	r3, pc, #536870918	; 0x20000006
d0010766:	2001d301 	andcs	sp, r1, r1, lsl #6
d001076a:	6a63e7ee 	bvs	0xd190a72a
d001076e:	6a2246a9 	bvs	0xd08a221a
d0010772:	6a6946a0 	bvs	0xd1a621fa
d0010776:	f7ff6a28 			; <UNDEFINED> instruction: 0xf7ff6a28
d001077a:	2800ffa2 	stmdacs	r0, {r1, r5, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d001077e:	f895d0e3 			; <UNDEFINED> instruction: 0xf895d0e3
d0010782:	f8942040 			; <UNDEFINED> instruction: 0xf8942040
d0010786:	429a3040 	addsmi	r3, sl, #64	; 0x40
d001078a:	f895d1dd 			; <UNDEFINED> instruction: 0xf895d1dd
d001078e:	f8942041 			; <UNDEFINED> instruction: 0xf8942041
d0010792:	429a3041 	addsmi	r3, sl, #65	; 0x41
d0010796:	f8b9d1d7 			; <UNDEFINED> instruction: 0xf8b9d1d7
d001079a:	35242042 	strcc	r2, [r4, #-66]!	; 0xffffffbe
d001079e:	3042f8b8 	strhcc	pc, [r2], #-136	; 0xffffff78	; <UNPREDICTABLE>
d00107a2:	429a3424 	addsmi	r3, sl, #36, 8	; 0x24000000
d00107a6:	3701d1cf 	strcc	sp, [r1, -pc, asr #3]
d00107aa:	Address 0x00000000d00107aa is out of bounds.


Disassembly of section .text.find_local.isra.0:

d00107ac <.text.find_local.isra.0>:
d00107ac:	2392f500 	orrscs	pc, r2, #0, 10
d00107b0:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d00107b4:	6238f8d3 	eorsvs	pc, r8, #13828096	; 0xd30000
d00107b8:	460f2530 			; <UNDEFINED> instruction: 0x460f2530
d00107bc:	fb054690 	blx	0xd0162206
d00107c0:	f5000006 			; <UNDEFINED> instruction: 0xf5000006
d00107c4:	f5042490 			; <UNDEFINED> instruction: 0xf5042490
d00107c8:	b91664c1 	ldmdblt	r6, {r0, r6, r7, sl, sp, lr}
d00107cc:	30fff04f 	rscscc	pc, pc, pc, asr #32
d00107d0:	6861e00a 	stmdavs	r1!, {r1, r3, sp, lr, pc}^
d00107d4:	463a4643 	ldrtmi	r4, [sl], -r3, asr #12
d00107d8:	0930f854 	ldmdbeq	r0!, {r2, r4, r6, fp, ip, sp, lr, pc}
d00107dc:	f7ff3e01 			; <UNDEFINED> instruction: 0xf7ff3e01
d00107e0:	2800ff6f 	stmdacs	r0, {r0, r1, r2, r3, r5, r6, r8, r9, sl, fp, ip, sp, lr, pc}
d00107e4:	4630d0f1 			; <UNDEFINED> instruction: 0x4630d0f1
d00107e8:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d

Disassembly of section .text.find_global.isra.0:

d00107ec <.text.find_global.isra.0>:
d00107ec:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d00107f0:	355ff500 	ldrbcc	pc, [pc, #-1280]	; 0xd00102f8	; <UNPREDICTABLE>
d00107f4:	460f4606 	strmi	r4, [pc], -r6, lsl #12
d00107f8:	f5054690 			; <UNDEFINED> instruction: 0xf5054690
d00107fc:	24007571 	strcs	r7, [r0], #-1393	; 0xfffffa8f
d0010800:	3967f500 	stmdbcc	r7!, {r8, sl, ip, sp, lr, pc}^
d0010804:	31c4f8d9 	ldrdcc	pc, [r4, #137]	; 0x89
d0010808:	d302429c 	movwle	r4, #8860	; 0x229c
d001080c:	30fff04f 	rscscc	pc, pc, pc, asr #32
d0010810:	f895e00c 			; <UNDEFINED> instruction: 0xf895e00c
d0010814:	7a332029 	bvc	0xd0cd88c0
d0010818:	d109429a 			; <UNDEFINED> instruction: 0xd109429a
d001081c:	463a4643 	ldrtmi	r4, [sl], -r3, asr #12
d0010820:	0100e9d5 	ldrdeq	lr, [r0, -r5]
d0010824:	ff4cf7ff 			; <UNDEFINED> instruction: 0xff4cf7ff
d0010828:	4620b110 			; <UNDEFINED> instruction: 0x4620b110
d001082c:	83f8e8bd 	mvnshi	lr, #12386304	; 0xbd0000
d0010830:	353c3401 	ldrcc	r3, [ip, #-1025]!	; 0xfffffbff
d0010834:	Address 0x00000000d0010834 is out of bounds.


Disassembly of section .text.find_alias.isra.0:

d0010836 <.text.find_alias.isra.0>:
d0010836:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d001083a:	3575f500 	ldrbcc	pc, [r5, #-1280]!	; 0xfffffb00	; <UNPREDICTABLE>
d001083e:	460f4606 	strmi	r4, [pc], -r6, lsl #12
d0010842:	f5054690 			; <UNDEFINED> instruction: 0xf5054690
d0010846:	24007563 	strcs	r7, [r0], #-1379	; 0xfffffa9d
d001084a:	3978f500 	ldmdbcc	r8!, {r8, sl, ip, sp, lr, pc}^
d001084e:	308cf8d9 	ldrdcc	pc, [ip], r9
d0010852:	d302429c 	movwle	r4, #8860	; 0x229c
d0010856:	30fff04f 	rscscc	pc, pc, pc, asr #32
d001085a:	f895e00c 			; <UNDEFINED> instruction: 0xf895e00c
d001085e:	7a332021 	bvc	0xd0cd88ea
d0010862:	d109429a 			; <UNDEFINED> instruction: 0xd109429a
d0010866:	463a4643 	ldrtmi	r4, [sl], -r3, asr #12
d001086a:	0100e9d5 	ldrdeq	lr, [r0, -r5]
d001086e:	ff27f7ff 			; <UNDEFINED> instruction: 0xff27f7ff
d0010872:	4620b110 			; <UNDEFINED> instruction: 0x4620b110
d0010876:	83f8e8bd 	mvnshi	lr, #12386304	; 0xbd0000
d001087a:	35243401 	strcc	r3, [r4, #-1025]!	; 0xfffffbff
d001087e:	Address 0x00000000d001087e is out of bounds.


Disassembly of section .text.is_record_type:

d0010880 <.text.is_record_type>:
d0010880:	f46f6ac3 	vld1.64	{d22-d23}, [pc], r3
d0010884:	189a728b 	ldmne	sl, {r0, r1, r3, r7, r9, ip, sp, lr}
d0010888:	b5102a01 	ldrlt	r2, [r0, #-2561]	; 0xfffff5ff
d001088c:	d8014604 	stmdale	r1, {r2, r9, sl, lr}
d0010890:	bd102001 	ldclt	0, cr2, [r0, #-4]
d0010894:	1201f240 	andne	pc, r1, #64, 4
d0010898:	d10e4293 			; <UNDEFINED> instruction: 0xd10e4293
d001089c:	698169c2 	stmibvs	r1, {r1, r6, r7, r8, fp, sp, lr}
d00108a0:	ffc9f7ff 			; <UNDEFINED> instruction: 0xffc9f7ff
d00108a4:	db081e03 	blle	0xd02180b8
d00108a8:	fb002024 	blx	0xd0018942
d00108ac:	f5004003 			; <UNDEFINED> instruction: 0xf5004003
d00108b0:	f8903075 			; <UNDEFINED> instruction: 0xf8903075
d00108b4:	2bff33ac 	blcs	0xcffdd76c
d00108b8:	2000d1ea 	andcs	sp, r0, sl, ror #3
d00108bc:	Address 0x00000000d00108bc is out of bounds.


Disassembly of section .text.find_function.isra.0:

d00108be <.text.find_function.isra.0>:
d00108be:	47f0e92d 	ldrbmi	lr, [r0, sp, lsr #18]!
d00108c2:	347ff500 	ldrbtcc	pc, [pc], #-1280	; 0xd00108ca	; <UNPREDICTABLE>
d00108c6:	46884606 	strmi	r4, [r8], r6, lsl #12
d00108ca:	f5044691 			; <UNDEFINED> instruction: 0xf5044691
d00108ce:	2500740a 	strcs	r7, [r0, #-1034]	; 0xfffffbf6
d00108d2:	37fff04f 	ldrbcc	pc, [pc, pc, asr #32]!	; <UNPREDICTABLE>
d00108d6:	2a86f500 	bcs	0xce1cdcde
d00108da:	3628f8da 			; <UNDEFINED> instruction: 0x3628f8da
d00108de:	d20f429d 	andle	r4, pc, #-805306359	; 0xd0000009
d00108e2:	4642464b 	strbmi	r4, [r2], -fp, asr #12
d00108e6:	0100e9d4 	ldrdeq	lr, [r0, -r4]
d00108ea:	fee9f7ff 	mcr2	7, 7, pc, cr9, cr15, {7}	; <UNPREDICTABLE>
d00108ee:	f894b160 			; <UNDEFINED> instruction: 0xf894b160
d00108f2:	b1433028 	cmplt	r3, r8, lsr #32
d00108f6:	2029f894 	mlacs	r9, r4, r8, pc	; <UNPREDICTABLE>
d00108fa:	429a7a33 	addsmi	r7, sl, #208896	; 0x33000
d00108fe:	462fd104 	strtmi	sp, [pc], -r4, lsl #2
d0010902:	e8bd4638 	pop	{r3, r4, r5, r9, sl, lr}
d0010906:	462f87f0 			; <UNDEFINED> instruction: 0x462f87f0
d001090a:	34383501 	ldrtcc	r3, [r8], #-1281	; 0xfffffaff
d001090e:	Address 0x00000000d001090e is out of bounds.


Disassembly of section .text.name_is.isra.0:

d0010910 <.text.name_is.isra.0>:
d0010910:	460db537 			; <UNDEFINED> instruction: 0x460db537
d0010914:	46104604 	ldrmi	r4, [r0], -r4, lsl #12
d0010918:	f0119201 			; <UNDEFINED> instruction: 0xf0119201
d001091c:	42a8ff07 	adcmi	pc, r8, #7, 30
d0010920:	99014602 	stmdbls	r1, {r1, r9, sl, lr}
d0010924:	4620d107 	strtmi	sp, [r0], -r7, lsl #2
d0010928:	fb06f010 	blx	0xd01cc972
d001092c:	f080fab0 			; <UNDEFINED> instruction: 0xf080fab0
d0010930:	b0030940 	andlt	r0, r3, r0, asr #18
d0010934:	2000bd30 	andcs	fp, r0, r0, lsr sp
d0010938:	Address 0x00000000d0010938 is out of bounds.


Disassembly of section .text.find_api_call.isra.0:

d001093a <.text.find_api_call.isra.0>:
d001093a:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d001093e:	4550f500 	ldrbmi	pc, [r0, #-1280]	; 0xfffffb00	; <UNPREDICTABLE>
d0010942:	4450f500 	ldrbmi	pc, [r0], #-1280	; 0xfffffb00	; <UNPREDICTABLE>
d0010946:	4690460f 	ldrmi	r4, [r0], pc, lsl #12
d001094a:	26003524 	strcs	r3, [r0], -r4, lsr #10
d001094e:	6823341c 	stmdavs	r3!, {r2, r3, r4, sl, ip, sp}
d0010952:	d304429e 	movwle	r4, #17054	; 0x429e
d0010956:	0900f04f 	stmdbeq	r0, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d001095a:	e8bd4648 	pop	{r3, r6, r9, sl, lr}
d001095e:	462a83f8 			; <UNDEFINED> instruction: 0x462a83f8
d0010962:	46384641 	ldrtmi	r4, [r8], -r1, asr #12
d0010966:	f7ff46a9 			; <UNDEFINED> instruction: 0xf7ff46a9
d001096a:	3554ffd2 	ldrbcc	pc, [r4, #-4050]	; 0xfffff02e	; <UNPREDICTABLE>
d001096e:	d1f32800 	mvnsle	r2, r0, lsl #16
d0010972:	e7ec3601 	strb	r3, [ip, r1, lsl #12]!

Disassembly of section .text.find_api_constant.isra.0:

d0010976 <.text.find_api_constant.isra.0>:
d0010976:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d001097a:	3582f500 	strcc	pc, [r2, #1280]	; 0x500
d001097e:	4450f500 	ldrbmi	pc, [r0], #-1280	; 0xfffffb00	; <UNPREDICTABLE>
d0010982:	4690460f 	ldrmi	r4, [r0], pc, lsl #12
d0010986:	260035a4 	strcs	r3, [r0], -r4, lsr #11
d001098a:	68233420 	stmdavs	r3!, {r5, sl, ip, sp}
d001098e:	d304429e 	movwle	r4, #17054	; 0x429e
d0010992:	0900f04f 	stmdbeq	r0, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d0010996:	e8bd4648 	pop	{r3, r6, r9, sl, lr}
d001099a:	462a83f8 			; <UNDEFINED> instruction: 0x462a83f8
d001099e:	46384641 	ldrtmi	r4, [r8], -r1, asr #12
d00109a2:	f7ff46a9 			; <UNDEFINED> instruction: 0xf7ff46a9
d00109a6:	3524ffb4 	strcc	pc, [r4, #-4020]!	; 0xfffff04c
d00109aa:	d1f32800 	mvnsle	r2, r0, lsl #16
d00109ae:	e7ec3601 	strb	r3, [ip, r1, lsl #12]!

Disassembly of section .text.pp_unary:

d00109c8 <.text.pp_unary>:
d00109c8:	e92d6ac3 	push	{r0, r1, r6, r7, r9, fp, sp, lr}
d00109cc:	1c5a43f7 	mrrcne	3, 15, r4, sl, cr7
d00109d0:	2a204604 	bcs	0xd08221e8
d00109d4:	d90962c2 	stmdble	r9, {r1, r6, r7, r9, sp, lr}
d00109d8:	26002201 	strcs	r2, [r0], -r1, lsl #4
d00109dc:	62c32700 	sbcvs	r2, r3, #0, 14
d00109e0:	46306302 	ldrtmi	r6, [r0], -r2, lsl #6
d00109e4:	b0034639 	andlt	r4, r3, r9, lsr r6
d00109e8:	83f0e8bd 	mvnshi	lr, #12386304	; 0xbd0000
d00109ec:	44794986 	ldrbtmi	r4, [r9], #-2438	; 0xfffff67a
d00109f0:	fcdef7ff 	ldc2l	7, cr15, [lr], {255}	; 0xff
d00109f4:	4620b148 	strtmi	fp, [r0], -r8, asr #2
d00109f8:	ffe6f7ff 			; <UNDEFINED> instruction: 0xffe6f7ff
d00109fc:	0301ea50 	movweq	lr, #6736	; 0x1a50
d0010a00:	2601bf0c 	strcs	fp, [r1], -ip, lsl #30
d0010a04:	27002600 	strcs	r2, [r0, -r0, lsl #12]
d0010a08:	4980e00a 	stmibmi	r0, {r1, r3, sp, lr, pc}
d0010a0c:	44794620 	ldrbtmi	r4, [r9], #-1568	; 0xfffff9e0
d0010a10:	fccef7ff 	stc2l	7, cr15, [lr], {255}	; 0xff
d0010a14:	4620b140 	strtmi	fp, [r0], -r0, asr #2
d0010a18:	ffd6f7ff 			; <UNDEFINED> instruction: 0xffd6f7ff
d0010a1c:	43cf43c6 	bicmi	r4, pc, #402653187	; 0x18000003
d0010a20:	3b016ae3 	blcc	0xd006b5b4
d0010a24:	e7dc62e3 	ldrb	r6, [ip, r3, ror #5]
d0010a28:	46204979 			; <UNDEFINED> instruction: 0x46204979
d0010a2c:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d0010a30:	b128fcbf 	msrlt	CPSR_f, pc	; <illegal shifter operand>
d0010a34:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010a38:	4606ffc7 	strmi	pc, [r6], -r7, asr #31
d0010a3c:	e7ef460f 	strb	r4, [pc, pc, lsl #12]!
d0010a40:	46204974 			; <UNDEFINED> instruction: 0x46204974
d0010a44:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d0010a48:	b130fcb3 	teqlt	r0, r3	; <illegal shifter operand>	; <UNPREDICTABLE>
d0010a4c:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010a50:	4246ffbb 	submi	pc, r6, #748	; 0x2ec
d0010a54:	0741eb61 	strbeq	lr, [r1, -r1, ror #22]
d0010a58:	4620e7e2 	strtmi	lr, [r0], -r2, ror #15
d0010a5c:	fc5ef7ff 	mrrc2	7, 15, pc, lr, cr15	; <UNPREDICTABLE>
d0010a60:	1c5a6ae3 	mrrcne	10, 14, r6, sl, cr3
d0010a64:	62e22a20 	rscvs	r2, r2, #32, 20	; 0x20000
d0010a68:	2201d904 	andcs	sp, r1, #4, 18	; 0x10000
d0010a6c:	62e32600 	rscvs	r2, r3, #0, 12
d0010a70:	e7c86322 	strb	r6, [r8, r2, lsr #6]
d0010a74:	44794968 	ldrbtmi	r4, [r9], #-2408	; 0xfffff698
d0010a78:	fc9af7ff 	ldc2	7, cr15, [sl], {255}	; 0xff
d0010a7c:	4620b168 	strtmi	fp, [r0], -r8, ror #2
d0010a80:	fb3cf000 	blx	0xd0f4ca8a
d0010a84:	4965460f 	stmdbmi	r5!, {r0, r1, r2, r3, r9, sl, lr}^
d0010a88:	44794606 	ldrbtmi	r4, [r9], #-1542	; 0xfffff9fa
d0010a8c:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010a90:	bba0fc8f 	bllt	0xce84fcd4
d0010a94:	63232301 			; <UNDEFINED> instruction: 0x63232301
d0010a98:	6a65e031 	bvs	0xd1988b64
d0010a9c:	8028f8d4 	ldrdhi	pc, [r8], -r4	; <UNPREDICTABLE>
d0010aa0:	d2514545 	subsle	r4, r1, #289406976	; 0x11400000
d0010aa4:	f1a07828 			; <UNDEFINED> instruction: 0xf1a07828
d0010aa8:	2b090330 	blcs	0xd0251770
d0010aac:	eba8d849 	bl	0xcea46bd8
d0010ab0:	2b020305 	blcs	0xd00916cc
d0010ab4:	2830dd27 	ldmdacs	r0!, {r0, r1, r2, r5, r8, sl, fp, ip, lr, pc}
d0010ab8:	786bd12a 	stmdavc	fp!, {r1, r3, r5, r8, ip, lr, pc}^
d0010abc:	03dff003 	bicseq	pc, pc, #3
d0010ac0:	d1272b58 			; <UNDEFINED> instruction: 0xd1272b58
d0010ac4:	21103502 	tstcs	r0, r2, lsl #10
d0010ac8:	25006265 	strcs	r6, [r0, #-613]	; 0xfffffd9b
d0010acc:	27002600 	strcs	r2, [r0, -r0, lsl #12]
d0010ad0:	0901f04f 	stmdbeq	r1, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d0010ad4:	45906a62 	ldrmi	r6, [r0, #2658]	; 0xa62
d0010ad8:	8092f240 	addshi	pc, r2, r0, asr #4
d0010adc:	f7ff7810 			; <UNDEFINED> instruction: 0xf7ff7810
d0010ae0:	4281fcf1 	addmi	pc, r1, #61696	; 0xf100
d0010ae4:	b91dd818 	ldmdblt	sp, {r3, r4, fp, ip, lr, pc}
d0010ae8:	45902301 	ldrmi	r2, [r0, #769]	; 0x301
d0010aec:	d9066323 	stmdble	r6, {r0, r1, r5, r8, r9, sp, lr}
d0010af0:	f0037813 			; <UNDEFINED> instruction: 0xf0037813
d0010af4:	2b5503df 	blcs	0xd1551a78
d0010af8:	3201d101 	andcc	sp, r1, #1073741824	; 0x40000000
d0010afc:	6ae36262 	bvs	0xcf8e948c
d0010b00:	62e33b01 	rscvs	r3, r3, #1024	; 0x400
d0010b04:	2830e78c 	ldmdacs	r0!, {r2, r3, r7, r8, r9, sl, sp, lr, pc}
d0010b08:	210abf14 	tstcs	sl, r4, lsl pc
d0010b0c:	e7dc2108 	ldrb	r2, [ip, r8, lsl #2]
d0010b10:	e7da210a 	ldrb	r2, [sl, sl, lsl #2]
d0010b14:	e7d82108 	ldrb	r2, [r8, r8, lsl #2]
d0010b18:	35011c53 	strcc	r1, [r1, #-3155]	; 0xfffff3ad
d0010b1c:	78106263 	ldmdavc	r0, {r0, r1, r5, r6, r9, sp, lr}
d0010b20:	fcd0f7ff 	ldc2l	7, cr15, [r0], {255}	; 0xff
d0010b24:	fbb343c3 	blx	0xcece1a3a
d0010b28:	42b3f3f1 	adcsmi	pc, r3, #-1006632957	; 0xc4000003
d0010b2c:	2306fba1 	movwcs	pc, #27553	; 0x6ba1	; <UNPREDICTABLE>
d0010b30:	f8c4bf38 			; <UNDEFINED> instruction: 0xf8c4bf38
d0010b34:	18169030 	ldmdane	r6, {r4, r5, ip, pc}
d0010b38:	3307fb01 	movwcc	pc, #31489	; 0x7b01	; <UNPREDICTABLE>
d0010b3c:	0700f143 	streq	pc, [r0, -r3, asr #2]
d0010b40:	f7ffe7c8 			; <UNDEFINED> instruction: 0xf7ffe7c8
d0010b44:	b930fc72 	ldmdblt	r0!, {r1, r4, r5, r6, sl, fp, ip, sp, lr, pc}
d0010b48:	63232301 			; <UNDEFINED> instruction: 0x63232301
d0010b4c:	27002600 	strcs	r2, [r0, -r0, lsl #12]
d0010b50:	3201e7d5 	andcc	lr, r1, #55836672	; 0x3540000
d0010b54:	6a626262 	bvs	0xd18a94e4
d0010b58:	d9084590 	stmdble	r8, {r4, r7, r8, sl, lr}
d0010b5c:	46087811 			; <UNDEFINED> instruction: 0x46087811
d0010b60:	fc63f7ff 	stc2l	7, cr15, [r3], #-1020	; 0xfffffc04
d0010b64:	d1f42800 	mvnsle	r2, r0, lsl #16
d0010b68:	29093930 	stmdbcs	r9, {r4, r5, r8, fp, ip, sp}
d0010b6c:	1b52d9f1 	blne	0xd14c7338
d0010b70:	d1362a07 	teqle	r6, r7, lsl #20
d0010b74:	4628492a 	strtmi	r4, [r8], -sl, lsr #18
d0010b78:	44799201 	ldrbtmi	r9, [r9], #-513	; 0xfffffdff
d0010b7c:	f9dcf010 			; <UNDEFINED> instruction: 0xf9dcf010
d0010b80:	bb709a01 	bllt	0xd1c3738c
d0010b84:	46204927 	strtmi	r4, [r0], -r7, lsr #18
d0010b88:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d0010b8c:	4680fc11 	pkhbtmi	pc, r0, r1, lsl #24	; <UNPREDICTABLE>
d0010b90:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010b94:	6a61fbc3 	bvs	0xd188faa8
d0010b98:	42b16aa6 	adcsmi	r6, r1, #679936	; 0xa6000
d0010b9c:	7808d003 	stmdavc	r8, {r0, r1, ip, lr, pc}
d0010ba0:	fc43f7ff 	mcrr2	7, 15, pc, r3, cr15	; <UNPREDICTABLE>
d0010ba4:	2301b908 	movwcs	fp, #6408	; 0x1908
d0010ba8:	6a626323 	bvs	0xd18a983c
d0010bac:	d9074296 	stmdble	r7, {r1, r2, r4, r7, r9, lr}
d0010bb0:	46287815 			; <UNDEFINED> instruction: 0x46287815
d0010bb4:	fc39f7ff 	ldc2	7, cr15, [r9], #-1020	; 0xfffffc04
d0010bb8:	3d30b980 			; <UNDEFINED> instruction: 0x3d30b980
d0010bbc:	d90d2d09 	stmdble	sp, {r0, r3, r8, sl, fp, sp}
d0010bc0:	68201a52 	stmdavs	r0!, {r1, r4, r6, r9, fp, ip}
d0010bc4:	fc0ff7ff 	stc2	7, cr15, [pc], {255}	; 0xff
d0010bc8:	17c12700 	strbne	r2, [r1, r0, lsl #14]
d0010bcc:	0ff643ce 	svceq	0x00f643ce
d0010bd0:	0f00f1b8 	svceq	0x0000f1b8
d0010bd4:	4914d093 	ldmdbmi	r4, {r0, r1, r4, r7, ip, lr, pc}
d0010bd8:	e7574479 			; <UNDEFINED> instruction: 0xe7574479
d0010bdc:	62623201 	rsbvs	r3, r2, #268435456	; 0x10000000
d0010be0:	4629e7e3 	strtmi	lr, [r9], -r3, ror #15
d0010be4:	f7ff6820 			; <UNDEFINED> instruction: 0xf7ff6820
d0010be8:	2800fbfe 	stmdacs	r0, {r1, r2, r3, r4, r5, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d0010bec:	6823dbae 	stmdavs	r3!, {r1, r2, r3, r5, r7, r8, r9, fp, ip, lr, pc}
d0010bf0:	fb022248 	blx	0xd009951a
d0010bf4:	f5003000 			; <UNDEFINED> instruction: 0xf5003000
d0010bf8:	e9d0402b 	ldmib	r0, {r0, r1, r3, r5, lr}^
d0010bfc:	e77e6732 			; <UNDEFINED> instruction: 0xe77e6732
d0010c00:	f47f2d00 			; <UNDEFINED> instruction: 0xf47f2d00
d0010c04:	e76faf7c 			; <UNDEFINED> instruction: 0xe76faf7c
d0010c08:	ffffffc0 			; <UNDEFINED> instruction: 0xffffffc0
d0010c0c:	ffffffa2 			; <UNDEFINED> instruction: 0xffffffa2
d0010c10:	ffffff86 			; <UNDEFINED> instruction: 0xffffff86
d0010c14:	ffffff70 			; <UNDEFINED> instruction: 0xffffff70
d0010c18:	ffffff40 			; <UNDEFINED> instruction: 0xffffff40
d0010c1c:	ffffff2e 			; <UNDEFINED> instruction: 0xffffff2e
d0010c20:	fffffe40 			; <UNDEFINED> instruction: 0xfffffe40
d0010c24:	fffffe2e 			; <UNDEFINED> instruction: 0xfffffe2e
d0010c28:	fffffde0 			; <UNDEFINED> instruction: 0xfffffde0

Disassembly of section .text.pp_mul:

d0010c34 <.text.pp_mul>:
d0010c34:	4ff0e92d 	svcmi	0x00f0e92d
d0010c38:	8b02ed2d 	blhi	0xd00cc0f4
d0010c3c:	4606b089 	strmi	fp, [r6], -r9, lsl #1
d0010c40:	fec2f7ff 	mcr2	7, 6, pc, cr2, cr15, {7}	; <UNPREDICTABLE>
d0010c44:	46044b67 	strmi	r4, [r4], -r7, ror #22
d0010c48:	447b460d 	ldrbtmi	r4, [fp], #-1549	; 0xfffff9f3
d0010c4c:	3a10ee08 	bcc	0xd044c474
d0010c50:	447b4b65 	ldrbtmi	r4, [fp], #-2917	; 0xfffff49b
d0010c54:	3a90ee08 	bcc	0xce44c47c
d0010c58:	1a10ee18 	bne	0xd044c4c0
d0010c5c:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0010c60:	b178fba7 	cmnlt	r8, r7, lsr #23	; <UNPREDICTABLE>
d0010c64:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0010c68:	4361feaf 	msrmi	SPSR_c, #2800	; 0xaf0
d0010c6c:	3400fba4 	strcc	pc, [r0], #-2980	; 0xfffff45c
d0010c70:	1105fb00 	tstne	r5, r0, lsl #22	; <UNPREDICTABLE>
d0010c74:	3400e9cd 	strcc	lr, [r0], #-2509	; 0xfffff633
d0010c78:	440b9b01 	strmi	r9, [fp], #-2817	; 0xfffff4ff
d0010c7c:	e9dd9301 	ldmib	sp, {r0, r8, r9, ip, pc}^
d0010c80:	e7e94500 	strb	r4, [r9, r0, lsl #10]!
d0010c84:	1a90ee18 	bne	0xce44c4ec
d0010c88:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0010c8c:	9006fb91 	mulls	r6, r1, fp
d0010c90:	4956b938 	ldmdbmi	r6, {r3, r4, r5, r8, fp, ip, sp, pc}^
d0010c94:	44794630 	ldrbtmi	r4, [r9], #-1584	; 0xfffff9d0
d0010c98:	fb8af7ff 	blx	0xce2cec9e
d0010c9c:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d0010ca0:	46308099 			; <UNDEFINED> instruction: 0x46308099
d0010ca4:	fe90f7ff 	mrc2	7, 4, pc, cr0, cr15, {7}
d0010ca8:	0100e9cd 	smlabteq	r0, sp, r9, lr
d0010cac:	2300e9dd 	movwcs	lr, #2525	; 0x9dd
d0010cb0:	d1094313 	tstle	r9, r3, lsl r3
d0010cb4:	29006b71 	stmdbcs	r0, {r0, r4, r5, r6, r8, r9, fp, sp, lr}
d0010cb8:	2301d0e1 	movwcs	sp, #4321	; 0x10e1
d0010cbc:	63332400 	teqvs	r3, #0, 8
d0010cc0:	e9cd2300 	stmib	sp, {r8, r9, sp}^
d0010cc4:	e7da3400 	ldrb	r3, [sl, r0, lsl #8]
d0010cc8:	f1752c00 			; <UNDEFINED> instruction: 0xf1752c00
d0010ccc:	e9cd0300 	stmib	sp, {r8, r9}^
d0010cd0:	da044502 	ble	0xd01220e0
d0010cd4:	eb654262 	bl	0xd1961664
d0010cd8:	e9cd0345 	stmib	sp, {r0, r2, r6, r8, r9}^
d0010cdc:	e9dd2302 	ldmib	sp, {r1, r8, r9, sp}^
d0010ce0:	2a002300 	bcs	0xd00198e8
d0010ce4:	2304e9cd 	movwcs	lr, #18893	; 0x49cd
d0010ce8:	0300f173 	movweq	pc, #371	; 0x173	; <UNPREDICTABLE>
d0010cec:	e9ddda06 	ldmib	sp, {r1, r2, r9, fp, ip, lr, pc}^
d0010cf0:	42522300 	subsmi	r2, r2, #0, 6
d0010cf4:	0343eb63 	movteq	lr, #15203	; 0x3b63
d0010cf8:	2304e9cd 	movwcs	lr, #18893	; 0x49cd
d0010cfc:	0a00f04f 	beq	0xd004ce40
d0010d00:	0b00f04f 	bleq	0xd004ce44
d0010d04:	f04f213f 			; <UNDEFINED> instruction: 0xf04f213f
d0010d08:	46570c01 	ldrbmi	r0, [r7], -r1, lsl #24
d0010d0c:	eb1a46d8 	bl	0xd06a2874
d0010d10:	f1c1030a 			; <UNDEFINED> instruction: 0xf1c1030a
d0010d14:	f1a10920 			; <UNDEFINED> instruction: 0xf1a10920
d0010d18:	461a0e20 	ldrmi	r0, [sl], -r0, lsr #28
d0010d1c:	030beb4b 	movweq	lr, #47947	; 0xbb4b
d0010d20:	9b029307 	blls	0xd00b5944
d0010d24:	b01cf8dd 			; <UNDEFINED> instruction: 0xb01cf8dd
d0010d28:	f001fa23 			; <UNDEFINED> instruction: 0xf001fa23
d0010d2c:	fa039b03 	blx	0xd00f7940
d0010d30:	fa23f909 	blx	0xd090f15c
d0010d34:	ea40fe0e 	b	0xd1050574
d0010d38:	ea400009 	b	0xd1010d64
d0010d3c:	f1a1000e 			; <UNDEFINED> instruction: 0xf1a1000e
d0010d40:	f0000e20 			; <UNDEFINED> instruction: 0xf0000e20
d0010d44:	ea400001 	b	0xd1010d50
d0010d48:	f1c10a02 			; <UNDEFINED> instruction: 0xf1c10a02
d0010d4c:	e9dd0020 	ldmib	sp, {r5}^
d0010d50:	459b2304 	ldrmi	r2, [fp, #772]	; 0x304
d0010d54:	4592bf08 	ldrmi	fp, [r2, #3848]	; 0xf08
d0010d58:	fa0cd313 	blx	0xd03459ac
d0010d5c:	fa2cfe0e 	blx	0xd0b5059c
d0010d60:	9b04f000 	blls	0xd014cd68
d0010d64:	0000ea4e 	andeq	lr, r0, lr, asr #20
d0010d68:	fe01fa0c 	vseleq.f32	s30, s2, s24
d0010d6c:	0a03ebba 	beq	0xd010bc5c
d0010d70:	ea4e9b05 	b	0xd13b798c
d0010d74:	ea400e07 	b	0xd1014598
d0010d78:	eb6b0008 	bl	0xd1ad0da0
d0010d7c:	46770b03 	ldrbtmi	r0, [r7], -r3, lsl #22
d0010d80:	39014680 	stmdbcc	r1, {r7, r9, sl, lr}
d0010d84:	9b06d2c3 	blls	0xd01c5898
d0010d88:	9b01b1c3 	blls	0xd007d49c
d0010d8c:	0fdb0fea 	svceq	0x00db0fea
d0010d90:	7fd5ebb3 	svcvc	0x00d5ebb3
d0010d94:	f04fbf15 			; <UNDEFINED> instruction: 0xf04fbf15
d0010d98:	f06f4100 			; <UNDEFINED> instruction: 0xf06f4100
d0010d9c:	20004100 	andcs	r4, r0, r0, lsl #2
d0010da0:	30fff04f 	rscscc	pc, pc, pc, asr #32
d0010da4:	bf084541 	svclt	0x00084541
d0010da8:	d38642b8 	orrle	r4, r6, #184, 4	; 0x8000000b
d0010dac:	d002429a 	mulle	r2, sl, r2
d0010db0:	eb68427f 	bl	0xd1a217b4
d0010db4:	e9cd0848 	stmib	sp, {r3, r6, fp}^
d0010db8:	e7607800 	strb	r7, [r0, -r0, lsl #16]!
d0010dbc:	f1752c00 			; <UNDEFINED> instruction: 0xf1752c00
d0010dc0:	e9cd0300 	stmib	sp, {r8, r9}^
d0010dc4:	f6bfab00 			; <UNDEFINED> instruction: 0xf6bfab00
d0010dc8:	f1daaf5a 			; <UNDEFINED> instruction: 0xf1daaf5a
d0010dcc:	eb6b0300 	bl	0xd1ad19d4
d0010dd0:	e776044b 	ldrb	r0, [r6, -fp, asr #8]!
d0010dd4:	46294620 	strtmi	r4, [r9], -r0, lsr #12
d0010dd8:	ecbdb009 	ldc	0, cr11, [sp], #36	; 0x24
d0010ddc:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d0010de0:	bf008ff0 	svclt	0x00008ff0
d0010de4:	ffffffde 			; <UNDEFINED> instruction: 0xffffffde
d0010de8:	ffffffd8 			; <UNDEFINED> instruction: 0xffffffd8
d0010dec:	ffffff96 			; <UNDEFINED> instruction: 0xffffff96

Disassembly of section .text.pp_add:

d0010df0 <.text.pp_add>:
d0010df0:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d0010df4:	46064f12 			; <UNDEFINED> instruction: 0x46064f12
d0010df8:	8048f8df 	ldrdhi	pc, [r8], #-143	; 0xffffff71
d0010dfc:	ff1af7ff 			; <UNDEFINED> instruction: 0xff1af7ff
d0010e00:	4604447f 			; <UNDEFINED> instruction: 0x4604447f
d0010e04:	44f8460d 	ldrbtmi	r4, [r8], #1549	; 0x60d
d0010e08:	46304639 			; <UNDEFINED> instruction: 0x46304639
d0010e0c:	fad0f7ff 	blx	0xcf44ee10
d0010e10:	4630b130 			; <UNDEFINED> instruction: 0x4630b130
d0010e14:	ff0ef7ff 			; <UNDEFINED> instruction: 0xff0ef7ff
d0010e18:	eb411824 	bl	0xd1056eb0
d0010e1c:	e7f30505 	ldrb	r0, [r3, r5, lsl #10]!
d0010e20:	46304641 	ldrtmi	r4, [r0], -r1, asr #12
d0010e24:	fac4f7ff 	blx	0xcf14ee28
d0010e28:	4630b130 			; <UNDEFINED> instruction: 0x4630b130
d0010e2c:	ff02f7ff 			; <UNDEFINED> instruction: 0xff02f7ff
d0010e30:	eb651a24 	bl	0xd19576c8
d0010e34:	e7e70501 	strb	r0, [r7, r1, lsl #10]!
d0010e38:	46294620 	strtmi	r4, [r9], -r0, lsr #12
d0010e3c:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d0010e40:	fffffbb2 			; <UNDEFINED> instruction: 0xfffffbb2
d0010e44:	fffffbae 			; <UNDEFINED> instruction: 0xfffffbae

Disassembly of section .text.pp_shift:

d0010e50 <.text.pp_shift>:
d0010e50:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d0010e54:	805cf8df 	ldrsbhi	pc, [ip], #-143	; 0xffffff71	; <UNPREDICTABLE>
d0010e58:	f8df4604 			; <UNDEFINED> instruction: 0xf8df4604
d0010e5c:	f7ff905c 			; <UNDEFINED> instruction: 0xf7ff905c
d0010e60:	44f8ffc7 	ldrbtmi	pc, [r8], #4039	; 0xfc7	; <UNPREDICTABLE>
d0010e64:	460e4605 	strmi	r4, [lr], -r5, lsl #12
d0010e68:	464144f9 			; <UNDEFINED> instruction: 0x464144f9
d0010e6c:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010e70:	b160fa9f 	msrlt	(UNDEF: 96), pc
d0010e74:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010e78:	2900ffbb 	stmdbcs	r0, {r0, r1, r3, r4, r5, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0010e7c:	2820bf08 	stmdacs	r0!, {r3, r8, r9, sl, fp, ip, sp, pc}
d0010e80:	2301d302 	movwcs	sp, #4866	; 0x1302
d0010e84:	e7f06323 	ldrb	r6, [r0, r3, lsr #6]!
d0010e88:	26004085 	strcs	r4, [r0], -r5, lsl #1
d0010e8c:	4649e7ed 	strbmi	lr, [r9], -sp, ror #15
d0010e90:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010e94:	b140fa8d 	smlalbblt	pc, r0, sp, sl	; <UNPREDICTABLE>
d0010e98:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010e9c:	2900ffa9 	stmdbcs	r0, {r0, r3, r5, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0010ea0:	2820bf08 	stmdacs	r0!, {r3, r8, r9, sl, fp, ip, sp, pc}
d0010ea4:	40c5d2ed 	sbcmi	sp, r5, sp, ror #5
d0010ea8:	4628e7ef 	strtmi	lr, [r8], -pc, ror #15
d0010eac:	e8bd4631 	pop	{r0, r4, r5, r9, sl, lr}
d0010eb0:	bf0083f8 	svclt	0x000083f8
d0010eb4:	ffffffe2 			; <UNDEFINED> instruction: 0xffffffe2
d0010eb8:	ffffffdf 			; <UNDEFINED> instruction: 0xffffffdf

Disassembly of section .text.pp_rel:

d0010ec8 <.text.pp_rel>:
d0010ec8:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d0010ecc:	46064f24 	strmi	r4, [r6], -r4, lsr #30
d0010ed0:	8090f8df 			; <UNDEFINED> instruction: 0x8090f8df
d0010ed4:	ffbcf7ff 			; <UNDEFINED> instruction: 0xffbcf7ff
d0010ed8:	908cf8df 	ldrdls	pc, [ip], pc	; <UNPREDICTABLE>
d0010edc:	460d4604 	strmi	r4, [sp], -r4, lsl #12
d0010ee0:	44f8447f 	ldrbtmi	r4, [r8], #1151	; 0x47f
d0010ee4:	463944f9 			; <UNDEFINED> instruction: 0x463944f9
d0010ee8:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0010eec:	b158fa61 	cmplt	r8, r1, ror #20	; <UNPREDICTABLE>
d0010ef0:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0010ef4:	42a0ffad 	adcmi	pc, r0, #692	; 0x2b4
d0010ef8:	0305eb71 	movweq	lr, #23409	; 0x5b71
d0010efc:	2401bfac 	strcs	fp, [r1], #-4012	; 0xfffff054
d0010f00:	b2e42400 	rsclt	r2, r4, #0, 8
d0010f04:	e7ee2500 	strb	r2, [lr, r0, lsl #10]!
d0010f08:	46304641 	ldrtmi	r4, [r0], -r1, asr #12
d0010f0c:	fa50f7ff 	blx	0xd144ef10
d0010f10:	4630b130 			; <UNDEFINED> instruction: 0x4630b130
d0010f14:	ff9cf7ff 			; <UNDEFINED> instruction: 0xff9cf7ff
d0010f18:	eb754284 	bl	0xd1d61930
d0010f1c:	e7ed0301 	strb	r0, [sp, r1, lsl #6]!
d0010f20:	46304649 	ldrtmi	r4, [r0], -r9, asr #12
d0010f24:	fa44f7ff 	blx	0xd114ef28
d0010f28:	4630b148 	ldrtmi	fp, [r0], -r8, asr #2
d0010f2c:	ff90f7ff 			; <UNDEFINED> instruction: 0xff90f7ff
d0010f30:	eb754284 	bl	0xd1d61948
d0010f34:	bfb40301 	svclt	0x00b40301
d0010f38:	24002401 	strcs	r2, [r0], #-1025	; 0xfffffbff
d0010f3c:	490be7e1 	stmdbmi	fp, {r0, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d0010f40:	44794630 	ldrbtmi	r4, [r9], #-1584	; 0xfffff9d0
d0010f44:	fa34f7ff 	blx	0xd0d4ef48
d0010f48:	4630b130 			; <UNDEFINED> instruction: 0x4630b130
d0010f4c:	ff80f7ff 			; <UNDEFINED> instruction: 0xff80f7ff
d0010f50:	eb7142a0 	bl	0xd1c619d8
d0010f54:	e7ee0305 	strb	r0, [lr, r5, lsl #6]!
d0010f58:	46294620 	strtmi	r4, [r9], -r0, lsr #12
d0010f5c:	83f8e8bd 	mvnshi	lr, #12386304	; 0xbd0000
d0010f60:	ffffffd8 			; <UNDEFINED> instruction: 0xffffffd8
d0010f64:	ffffffd9 			; <UNDEFINED> instruction: 0xffffffd9
d0010f68:	ffffffda 			; <UNDEFINED> instruction: 0xffffffda
d0010f6c:	ffffff7e 			; <UNDEFINED> instruction: 0xffffff7e

Disassembly of section .text.pp_eq:

d0010f78 <.text.pp_eq>:
d0010f78:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d0010f7c:	46064f15 			; <UNDEFINED> instruction: 0x46064f15
d0010f80:	8054f8df 	ldrsbhi	pc, [r4], #-143	; 0xffffff71	; <UNPREDICTABLE>
d0010f84:	ffa0f7ff 			; <UNDEFINED> instruction: 0xffa0f7ff
d0010f88:	4604447f 			; <UNDEFINED> instruction: 0x4604447f
d0010f8c:	44f8460d 	ldrbtmi	r4, [r8], #1549	; 0x60d
d0010f90:	46304639 			; <UNDEFINED> instruction: 0x46304639
d0010f94:	fa0cf7ff 	blx	0xd034ef98
d0010f98:	4630b150 			; <UNDEFINED> instruction: 0x4630b150
d0010f9c:	ff94f7ff 			; <UNDEFINED> instruction: 0xff94f7ff
d0010fa0:	bf0642a9 	svclt	0x000642a9
d0010fa4:	240142a0 	strcs	r4, [r1], #-672	; 0xfffffd60
d0010fa8:	b2e42400 	rsclt	r2, r4, #0, 8
d0010fac:	e7ef2500 	strb	r2, [pc, r0, lsl #10]!
d0010fb0:	46304641 	ldrtmi	r4, [r0], -r1, asr #12
d0010fb4:	f9fcf7ff 			; <UNDEFINED> instruction: 0xf9fcf7ff
d0010fb8:	4630b140 	ldrtmi	fp, [r0], -r0, asr #2
d0010fbc:	ff84f7ff 			; <UNDEFINED> instruction: 0xff84f7ff
d0010fc0:	bf0a42a9 	svclt	0x000a42a9
d0010fc4:	240142a0 	strcs	r4, [r1], #-672	; 0xfffffd60
d0010fc8:	e7ee2400 	strb	r2, [lr, r0, lsl #8]!
d0010fcc:	46294620 	strtmi	r4, [r9], -r0, lsr #12
d0010fd0:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d0010fd4:	ffffffe4 			; <UNDEFINED> instruction: 0xffffffe4
d0010fd8:	ffffffe1 			; <UNDEFINED> instruction: 0xffffffe1

Disassembly of section .text.pp_band:

d0010fdc <.text.pp_band>:
d0010fdc:	4604b570 			; <UNDEFINED> instruction: 0x4604b570
d0010fe0:	ffcaf7ff 			; <UNDEFINED> instruction: 0xffcaf7ff
d0010fe4:	460d4606 	strmi	r4, [sp], -r6, lsl #12
d0010fe8:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010fec:	6a63f997 	bvs	0xd190f650
d0010ff0:	428b6aa1 	addmi	r6, fp, #659456	; 0xa1000
d0010ff4:	781ad20f 	ldmdavc	sl, {r0, r1, r2, r3, r9, ip, lr, pc}
d0010ff8:	d10c2a26 	tstle	ip, r6, lsr #20
d0010ffc:	42911c5a 	addsmi	r1, r1, #23040	; 0x5a00
d0011000:	785bd902 	ldmdavc	fp, {r1, r8, fp, ip, lr, pc}^
d0011004:	d0062b26 	andle	r2, r6, r6, lsr #22
d0011008:	62624620 	rsbvs	r4, r2, #32, 12	; 0x2000000
d001100c:	ffb4f7ff 			; <UNDEFINED> instruction: 0xffb4f7ff
d0011010:	400d4006 	andmi	r4, sp, r6
d0011014:	4630e7e8 	ldrtmi	lr, [r0], -r8, ror #15
d0011018:	bd704629 	ldcllt	6, cr4, [r0, #-164]!	; 0xffffff5c

Disassembly of section .text.pp_xor:

d0011020 <.text.pp_xor>:
d0011020:	4f0ab5f8 	svcmi	0x000ab5f8
d0011024:	f7ff4606 			; <UNDEFINED> instruction: 0xf7ff4606
d0011028:	4605ffd9 			; <UNDEFINED> instruction: 0x4605ffd9
d001102c:	447f460c 	ldrbtmi	r4, [pc], #-1548	; 0xd0011034
d0011030:	46304639 			; <UNDEFINED> instruction: 0x46304639
d0011034:	f9bcf7ff 			; <UNDEFINED> instruction: 0xf9bcf7ff
d0011038:	4628b910 			; <UNDEFINED> instruction: 0x4628b910
d001103c:	bdf84621 	ldcllt	6, cr4, [r8, #132]!	; 0x84
d0011040:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0011044:	4045ffcb 	submi	pc, r5, fp, asr #31
d0011048:	e7f1404c 	ldrb	r4, [r1, ip, asr #32]!
d001104c:	ffffffea 			; <UNDEFINED> instruction: 0xffffffea

Disassembly of section .text.pp_bor:

d0011050 <.text.pp_bor>:
d0011050:	4604b570 			; <UNDEFINED> instruction: 0x4604b570
d0011054:	ffe4f7ff 			; <UNDEFINED> instruction: 0xffe4f7ff
d0011058:	460d4606 	strmi	r4, [sp], -r6, lsl #12
d001105c:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0011060:	6a63f95d 	bvs	0xd190f5dc
d0011064:	428b6aa1 	addmi	r6, fp, #659456	; 0xa1000
d0011068:	781ad20f 	ldmdavc	sl, {r0, r1, r2, r3, r9, ip, lr, pc}
d001106c:	d10c2a7c 	tstle	ip, ip, ror sl
d0011070:	42911c5a 	addsmi	r1, r1, #23040	; 0x5a00
d0011074:	785bd902 	ldmdavc	fp, {r1, r8, fp, ip, lr, pc}^
d0011078:	d0062b7c 	andle	r2, r6, ip, ror fp
d001107c:	62624620 	rsbvs	r4, r2, #32, 12	; 0x2000000
d0011080:	ffcef7ff 			; <UNDEFINED> instruction: 0xffcef7ff
d0011084:	430d4306 	movwmi	r4, #54022	; 0xd306
d0011088:	4630e7e8 	ldrtmi	lr, [r0], -r8, ror #15
d001108c:	bd704629 	ldcllt	6, cr4, [r0, #-164]!	; 0xffffff5c

Disassembly of section .text.pp_and:

d0011094 <.text.pp_and>:
d0011094:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d0011098:	46064f16 			; <UNDEFINED> instruction: 0x46064f16
d001109c:	ffd8f7ff 			; <UNDEFINED> instruction: 0xffd8f7ff
d00110a0:	460d4604 	strmi	r4, [sp], -r4, lsl #12
d00110a4:	4639447f 			; <UNDEFINED> instruction: 0x4639447f
d00110a8:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d00110ac:	b918f981 	ldmdblt	r8, {r0, r7, r8, fp, ip, sp, lr, pc}
d00110b0:	46294620 	strtmi	r4, [r9], -r0, lsr #12
d00110b4:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d00110b8:	8034f8d6 	ldrsbthi	pc, [r4], -r6	; <UNPREDICTABLE>
d00110bc:	0f00f1b8 	svceq	0x0000f1b8
d00110c0:	ea54d014 	b	0xd1545118
d00110c4:	bf140305 	svclt	0x00140305
d00110c8:	23002301 	movwcs	r2, #769	; 0x301
d00110cc:	46306373 			; <UNDEFINED> instruction: 0x46306373
d00110d0:	ffbef7ff 			; <UNDEFINED> instruction: 0xffbef7ff
d00110d4:	0305ea54 	movweq	lr, #23124	; 0x5a54
d00110d8:	8034f8c6 	eorshi	pc, r4, r6, asr #17
d00110dc:	ea50d008 	b	0xd1445104
d00110e0:	bf140301 	svclt	0x00140301
d00110e4:	24002401 	strcs	r2, [r0], #-1025	; 0xfffffbff
d00110e8:	e7dc17e5 	ldrb	r1, [ip, r5, ror #15]
d00110ec:	e7ed4643 	strb	r4, [sp, r3, asr #12]!
d00110f0:	e7f92400 	ldrb	r2, [r9, r0, lsl #8]!
d00110f4:	ffffffe8 			; <UNDEFINED> instruction: 0xffffffe8

Disassembly of section .text.pp_or:

d00110fc <.text.pp_or>:
d00110fc:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d0011100:	46064f15 			; <UNDEFINED> instruction: 0x46064f15
d0011104:	ffc6f7ff 			; <UNDEFINED> instruction: 0xffc6f7ff
d0011108:	460d4604 	strmi	r4, [sp], -r4, lsl #12
d001110c:	4639447f 			; <UNDEFINED> instruction: 0x4639447f
d0011110:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0011114:	b918f94d 	ldmdblt	r8, {r0, r2, r3, r6, r8, fp, ip, sp, lr, pc}
d0011118:	46294620 	strtmi	r4, [r9], -r0, lsr #12
d001111c:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d0011120:	8034f8d6 	ldrsbthi	pc, [r4], -r6	; <UNPREDICTABLE>
d0011124:	0f00f1b8 	svceq	0x0000f1b8
d0011128:	ea54d014 	b	0xd1545180
d001112c:	bf0c0305 	svclt	0x000c0305
d0011130:	23002301 	movwcs	r2, #769	; 0x301
d0011134:	46306373 			; <UNDEFINED> instruction: 0x46306373
d0011138:	ffacf7ff 			; <UNDEFINED> instruction: 0xffacf7ff
d001113c:	43294320 			; <UNDEFINED> instruction: 0x43294320
d0011140:	8034f8c6 	eorshi	pc, r4, r6, asr #17
d0011144:	ea502500 	b	0xd141a54c
d0011148:	bf140301 	svclt	0x00140301
d001114c:	24002401 	strcs	r2, [r0], #-1025	; 0xfffffbff
d0011150:	e7dcb2e4 	ldrb	fp, [ip, r4, ror #5]
d0011154:	e7ed4643 	strb	r4, [sp, r3, asr #12]!
d0011158:	ffffffe8 			; <UNDEFINED> instruction: 0xffffffe8

Disassembly of section .text.pp_value:

d001118c <.text.pp_value>:
d001118c:	b5f0b084 	ldrblt	fp, [r0, #132]!	; 0x84
d0011190:	4606b08f 	strmi	fp, [r6], -pc, lsl #1
d0011194:	9000ac15 	andls	sl, r0, r5, lsl ip
d0011198:	9f1ead01 	svcls	0x001ead01
d001119c:	000ee884 	andeq	lr, lr, r4, lsl #17
d00111a0:	c50fcc0f 	strgt	ip, [pc, #-3087]	; 0xd0010599
d00111a4:	000fe894 	muleq	pc, r4, r8	; <UNPREDICTABLE>
d00111a8:	000fe885 	andeq	lr, pc, r5, lsl #17
d00111ac:	466d9b1d 			; <UNDEFINED> instruction: 0x466d9b1d
d00111b0:	970a2401 	strls	r2, [sl, -r1, lsl #8]
d00111b4:	23009309 	movwcs	r9, #777	; 0x309
d00111b8:	940d4628 	strls	r4, [sp], #-1576	; 0xfffff9d8
d00111bc:	930c930b 	movwls	r9, #49931	; 0xc30b
d00111c0:	ff9cf7ff 			; <UNDEFINED> instruction: 0xff9cf7ff
d00111c4:	e9c39b1f 	stmib	r3, {r0, r1, r2, r3, r4, r8, r9, fp, ip, pc}^
d00111c8:	46280100 	strtmi	r0, [r8], -r0, lsl #2
d00111cc:	f8a6f7ff 			; <UNDEFINED> instruction: 0xf8a6f7ff
d00111d0:	b9139b0c 	ldmdblt	r3, {r2, r3, r8, r9, fp, ip, pc}
d00111d4:	42bb9b09 	adcsmi	r9, fp, #9216	; 0x2400
d00111d8:	6db0d012 	ldcvs	0, cr13, [r0, #72]!	; 0x48
d00111dc:	490ab990 	stmdbmi	sl, {r4, r7, r8, fp, ip, sp, pc}
d00111e0:	206cf89d 	mlscs	ip, sp, r8, pc	; <UNPREDICTABLE>
d00111e4:	65b14479 	ldrvs	r4, [r1, #1145]!	; 0x479
d00111e8:	65f19918 	ldrbvs	r9, [r1, #2328]!	; 0x918
d00111ec:	e9c69919 	stmib	r6, {r0, r3, r4, r8, fp, ip, pc}^
d00111f0:	9a1c1218 	bls	0xd0715a58
d00111f4:	b00f66b2 			; <UNDEFINED> instruction: 0xb00f66b2
d00111f8:	40f0e8bd 	ldrhtmi	lr, [r0], #141	; 0x8d
d00111fc:	4770b004 	ldrbmi	fp, [r0, -r4]!
d0011200:	e7f84620 	ldrb	r4, [r8, r0, lsr #12]!
d0011204:	e7f62000 	ldrb	r2, [r6, r0]!
d0011208:	ffffff74 			; <UNDEFINED> instruction: 0xffffff74

Disassembly of section .text.enter_header.isra.0:

d00113ac <.text.enter_header.isra.0>:
d00113ac:	4ff0e92d 	svcmi	0x00f0e92d
d00113b0:	f5ad461e 			; <UNDEFINED> instruction: 0xf5ad461e
d00113b4:	6ec37d0d 	cdpvs	13, 12, cr7, cr3, cr13, {0}
d00113b8:	9d984604 	ldcls	6, cr4, [r8, #16]
d00113bc:	92059104 	andls	r9, r5, #4, 2
d00113c0:	6d85b993 	vstrvs.16	s22, [r5, #294]	; 0x126	; <UNPREDICTABLE>
d00113c4:	2500b12d 	strcs	fp, [r0, #-301]	; 0xfffffed3
d00113c8:	f50d4628 			; <UNDEFINED> instruction: 0xf50d4628
d00113cc:	e8bd7d0d 	pop	{r0, r2, r3, r8, sl, fp, ip, sp, lr}
d00113d0:	4bfa8ff0 	blmi	0xcfeb5398
d00113d4:	65a3447b 	strvs	r4, [r3, #1147]!	; 0x47b
d00113d8:	65e39b04 	strbvs	r9, [r3, #2820]!	; 0xb04
d00113dc:	e9c49b05 	stmib	r4, {r0, r2, r8, r9, fp, ip, pc}^
d00113e0:	9b963618 	blls	0xce59ec48
d00113e4:	e7ef66a3 	strb	r6, [pc, r3, lsr #13]!
d00113e8:	2bfe1e6b 	blcs	0xcff98d9c
d00113ec:	6d85d905 	vstrvs.16	s26, [r5, #10]	; <UNPREDICTABLE>
d00113f0:	d1e82d00 	mvnle	r2, r0, lsl #26
d00113f4:	447b4bf2 	ldrbtmi	r4, [fp], #-3058	; 0xfffff40e
d00113f8:	f10de7ed 			; <UNDEFINED> instruction: 0xf10de7ed
d00113fc:	462a0930 			; <UNDEFINED> instruction: 0x462a0930
d0011400:	46489997 			; <UNDEFINED> instruction: 0x46489997
d0011404:	fd88f00f 	stc2	0, cr15, [r8, #60]	; 0x3c
d0011408:	46482300 	strbmi	r2, [r8], -r0, lsl #6
d001140c:	3005f809 	andcc	pc, r5, r9, lsl #16
d0011410:	f98cf011 			; <UNDEFINED> instruction: 0xf98cf011
d0011414:	d8052802 	stmdale	r5, {r1, fp, sp}
d0011418:	2d006da5 	stccs	13, cr6, [r0, #-660]	; 0xfffffd6c
d001141c:	4be9d1d3 	blmi	0xcfa85b70
d0011420:	e7d8447b 			; <UNDEFINED> instruction: 0xe7d8447b
d0011424:	49e83802 	stmibmi	r8!, {r1, fp, ip, sp}^
d0011428:	44794448 	ldrbtmi	r4, [r9], #-1096	; 0xfffffbb8
d001142c:	f98af011 			; <UNDEFINED> instruction: 0xf98af011
d0011430:	28004605 	stmdacs	r0, {r0, r2, r9, sl, lr}
d0011434:	ab0bd1f0 	blge	0xd0305bfc
d0011438:	7280f44f 	addvc	pc, r0, #1325400064	; 0x4f000000
d001143c:	7b98f50d 	blvc	0xce64e878
d0011440:	9202900b 	andls	r9, r2, #11
d0011444:	46024649 	strmi	r4, [r2], -r9, asr #12
d0011448:	e9cd6ee7 	stmib	sp, {r0, r1, r2, r5, r6, r7, r9, sl, fp, sp, lr}^
d001144c:	46033b00 	strmi	r3, [r3], -r0, lsl #22
d0011450:	47b86f60 	ldrmi	r6, [r8, r0, ror #30]!
d0011454:	f504b1e8 			; <UNDEFINED> instruction: 0xf504b1e8
d0011458:	46a87700 	strtmi	r7, [r8], r0, lsl #14
d001145c:	5a2ef504 	bpl	0xd0bce874
d0011460:	3000f8da 	ldrdcc	pc, [r0], -sl
d0011464:	d2064598 	andle	r4, r6, #152, 10	; 0x26000000
d0011468:	46594638 			; <UNDEFINED> instruction: 0x46594638
d001146c:	77a6f507 	strvc	pc, [r6, r7, lsl #10]!
d0011470:	f968f011 			; <UNDEFINED> instruction: 0xf968f011
d0011474:	f8dab998 			; <UNDEFINED> instruction: 0xf8dab998
d0011478:	45983000 	ldrmi	r3, [r8]
d001147c:	8103f040 	tsthi	r3, r0, asr #32	; <UNPREDICTABLE>
d0011480:	0f20f1b8 	svceq	0x0020f1b8
d0011484:	6da3d10e 	stfvsd	f5, [r3, #56]!	; 0x38
d0011488:	d19c2b00 	orrsle	r2, ip, r0, lsl #22
d001148c:	447b4bcf 	ldrbtmi	r4, [fp], #-3023	; 0xfffff431
d0011490:	6da3e7a1 	stcvs	7, cr14, [r3, #644]!	; 0x284
d0011494:	d1962b00 	orrsle	r2, r6, r0, lsl #22
d0011498:	447b4bcd 	ldrbtmi	r4, [fp], #-3021	; 0xfffff433
d001149c:	f108e79b 			; <UNDEFINED> instruction: 0xf108e79b
d00114a0:	e7dd0801 	ldrb	r0, [sp, r1, lsl #16]
d00114a4:	3384f642 	orrcc	pc, r4, #69206016	; 0x4200000
d00114a8:	f5d258e2 			; <UNDEFINED> instruction: 0xf5d258e2
d00114ac:	d1054300 	mrsle	r4, SP_abt
d00114b0:	2b006da3 	blcs	0xd002cb44
d00114b4:	4bc7d187 	blmi	0xcf205ad8
d00114b8:	e78c447b 			; <UNDEFINED> instruction: 0xe78c447b
d00114bc:	512ef504 	msrpl	CPSR_fsx, r4, lsl #10
d00114c0:	7b98f50d 	blvc	0xce64e8fc
d00114c4:	31086f60 	tstcc	r8, r0, ror #30
d00114c8:	f8cd6ee7 			; <UNDEFINED> instruction: 0xf8cd6ee7
d00114cc:	9106b004 	tstls	r6, r4
d00114d0:	7180f44f 	orrvc	pc, r0, pc, asr #8
d00114d4:	91029307 	tstls	r2, r7, lsl #6
d00114d8:	9109a90b 	tstls	r9, fp, lsl #18
d00114dc:	99069100 	stmdbls	r6, {r8, ip, pc}
d00114e0:	4649440a 	strbmi	r4, [r9], -sl, lsl #8
d00114e4:	9b0747b8 	blls	0xd01e33cc
d00114e8:	6da5b930 			; <UNDEFINED> instruction: 0x6da5b930
d00114ec:	f47f2d00 			; <UNDEFINED> instruction: 0xf47f2d00
d00114f0:	4bb9af6a 	blmi	0xcee7d2a0
d00114f4:	e76e447b 			; <UNDEFINED> instruction: 0xe76e447b
d00114f8:	68129a09 	ldmdavs	r2, {r0, r3, r9, fp, ip, pc}
d00114fc:	d2064293 	andle	r4, r6, #805306377	; 0x30000009
d0011500:	2b006da3 	blcs	0xd002cb94
d0011504:	af5ff47f 	svcge	0x005ff47f
d0011508:	447b4bb4 	ldrbtmi	r4, [fp], #-2996	; 0xfffff44c
d001150c:	f642e763 			; <UNDEFINED> instruction: 0xf642e763
d0011510:	21003384 	smlabbcs	r0, r4, r3, r3
d0011514:	9b0658e0 	blls	0xd01a789c
d0011518:	f0114418 			; <UNDEFINED> instruction: 0xf0114418
d001151c:	4681f8f1 			; <UNDEFINED> instruction: 0x4681f8f1
d0011520:	d1ed2800 	mvnle	r2, r0, lsl #16
d0011524:	3000f8da 	ldrdcc	pc, [r0], -sl
d0011528:	70a6f44f 	adcvc	pc, r6, pc, asr #8
d001152c:	33019307 	movwcc	r9, #4871	; 0x1307
d0011530:	3000f8ca 	andcc	pc, r0, sl, asr #17
d0011534:	43439b07 	movtmi	r9, #15111	; 0x3b07
d0011538:	93084658 	movwls	r4, #34392	; 0x8658
d001153c:	7300f503 	movwvc	pc, #1283	; 0x503	; <UNPREDICTABLE>
d0011540:	0a03eb04 	beq	0xd010c158
d0011544:	f8f2f011 			; <UNDEFINED> instruction: 0xf8f2f011
d0011548:	1c424659 	mcrrne	6, 5, r4, r2, cr9
d001154c:	f00f4650 			; <UNDEFINED> instruction: 0xf00f4650
d0011550:	f642fce3 			; <UNDEFINED> instruction: 0xf642fce3
d0011554:	9b083284 	blls	0xd021df6c
d0011558:	9a0958a1 	bls	0xd02677e4
d001155c:	681218e3 	ldmdavs	r2, {r0, r1, r5, r6, r7, fp, ip}
d0011560:	1300f8c3 	movwne	pc, #2243	; 0x8c3	; <UNPREDICTABLE>
d0011564:	2304f8c3 	movwcs	pc, #18627	; 0x48c3	; <UNPREDICTABLE>
d0011568:	9308f8c3 	movwls	pc, #35011	; 0x88c3	; <UNPREDICTABLE>
d001156c:	440b9b06 	strmi	r9, [fp], #-2822	; 0xfffff4fa
d0011570:	0902eb03 	stmdbeq	r2, {r0, r1, r8, r9, fp, sp, lr, pc}
d0011574:	4a90469a 	bmi	0xce422fe4
d0011578:	d90945d1 	stmdble	r9, {r0, r4, r6, r7, r8, sl, lr}
d001157c:	3000f89a 	mulcc	r0, sl, r8
d0011580:	b2db3b09 	sbcslt	r3, fp, #9216	; 0x2400
d0011584:	d8032b17 	stmdale	r3, {r0, r1, r2, r4, r8, r9, fp, sp}
d0011588:	f303fa22 	vpmax.u8	d15, d3, d18
d001158c:	d41607db 	ldrle	r0, [r6], #-2011	; 0xfffff825
d0011590:	030aeba9 	movweq	lr, #43945	; 0xaba9
d0011594:	dd292b01 	fstmdbxle	r9!, {d2-d1}	;@ Deprecated
d0011598:	3000f89a 	mulcc	r0, sl, r8
d001159c:	d1252b2f 			; <UNDEFINED> instruction: 0xd1252b2f
d00115a0:	3001f89a 	mulcc	r1, sl, r8
d00115a4:	d10d2b2f 	tstle	sp, pc, lsr #22
d00115a8:	0302f10a 	movweq	pc, #8458	; 0x210a	; <UNPREDICTABLE>
d00115ac:	469a4599 			; <UNDEFINED> instruction: 0x469a4599
d00115b0:	f89ad9ee 			; <UNDEFINED> instruction: 0xf89ad9ee
d00115b4:	33011000 	movwcc	r1, #4096	; 0x1000
d00115b8:	d1f7290a 	mvnsle	r2, sl, lsl #18
d00115bc:	f10ae7dc 			; <UNDEFINED> instruction: 0xf10ae7dc
d00115c0:	e7d90a01 	ldrb	r0, [r9, r1, lsl #20]
d00115c4:	d1112b2a 	tstle	r1, sl, lsr #22
d00115c8:	0a02f10a 	beq	0xd00cd9f8
d00115cc:	0301f10a 	movweq	pc, #4362	; 0x110a	; <UNPREDICTABLE>
d00115d0:	d90b4599 	stmdble	fp, {r0, r3, r4, r7, r8, sl, lr}
d00115d4:	1c01f813 	stcne	8, cr15, [r1], {19}
d00115d8:	d105292a 	tstle	r5, sl, lsr #18
d00115dc:	292f7819 	stmdbcs	pc!, {r0, r3, r4, fp, ip, sp, lr}	; <UNPREDICTABLE>
d00115e0:	f10ad102 			; <UNDEFINED> instruction: 0xf10ad102
d00115e4:	e7c70a02 	strb	r0, [r7, r2, lsl #20]
d00115e8:	e7ef469a 			; <UNDEFINED> instruction: 0xe7ef469a
d00115ec:	030aeba9 	movweq	lr, #43945	; 0xaba9
d00115f0:	dd422b06 	vstrle	d18, [r2, #-24]	; 0xffffffe8
d00115f4:	2207497a 	andcs	r4, r7, #1998848	; 0x1e8000
d00115f8:	44794650 	ldrbtmi	r4, [r9], #-1616	; 0xfffff9b0
d00115fc:	fc9cf00f 	ldc2	0, cr15, [ip], {15}
d0011600:	f10abbd8 			; <UNDEFINED> instruction: 0xf10abbd8
d0011604:	45b90707 	ldrmi	r0, [r9, #1799]!	; 0x707
d0011608:	f89ad005 			; <UNDEFINED> instruction: 0xf89ad005
d001160c:	2b203007 	blcs	0xd081d630
d0011610:	2b09d001 	blcs	0xd028561c
d0011614:	45b9d131 	ldrmi	sp, [r9, #305]!	; 0x131
d0011618:	d9474639 	stmdble	r7, {r0, r3, r4, r5, r9, sl, lr}^
d001161c:	f813463b 			; <UNDEFINED> instruction: 0xf813463b
d0011620:	2a202b01 	bcs	0xd081c22c
d0011624:	2a09d040 	bcs	0xd028572c
d0011628:	463ad03e 			; <UNDEFINED> instruction: 0x463ad03e
d001162c:	f8923701 			; <UNDEFINED> instruction: 0xf8923701
d0011630:	4650a000 	ldrbmi	sl, [r0], -r0
d0011634:	fef9f7fe 	mrc2	7, 7, pc, cr9, cr14, {7}
d0011638:	f1aab920 			; <UNDEFINED> instruction: 0xf1aab920
d001163c:	f1ba0a30 			; <UNDEFINED> instruction: 0xf1ba0a30
d0011640:	d8020f09 	stmdale	r2, {r0, r3, r8, r9, sl, fp}
d0011644:	463a45b9 			; <UNDEFINED> instruction: 0x463a45b9
d0011648:	1a57d8ef 	bne	0xd1607a0c
d001164c:	7808d015 	stmdavc	r8, {r0, r2, r4, ip, lr, pc}
d0011650:	feebf7fe 	mcr2	7, 7, pc, cr11, cr14, {7}	; <UNPREDICTABLE>
d0011654:	2f3fb188 	svccs	0x003fb188
d0011658:	9b08d80f 	blls	0xd024769c
d001165c:	f203463a 	vmin.s8	d4, d3, d26
d0011660:	4420300b 	strtmi	r3, [r0], #-11
d0011664:	fc58f00f 	mrrc2	0, 0, pc, r8, cr15	; <UNPREDICTABLE>
d0011668:	f44f9b07 			; <UNDEFINED> instruction: 0xf44f9b07
d001166c:	fb0272a6 	blx	0xd00ae10e
d0011670:	23004203 	movwcs	r4, #515	; 0x203
d0011674:	f882443a 			; <UNDEFINED> instruction: 0xf882443a
d0011678:	f642330b 			; <UNDEFINED> instruction: 0xf642330b
d001167c:	990b3284 	stmdbls	fp, {r2, r7, r9, ip, sp}
d0011680:	440b58a3 	strmi	r5, [fp], #-2211	; 0xfffff75d
d0011684:	7a2350a3 	bvc	0xd08e5918
d0011688:	409f2701 	addsmi	r2, pc, r1, lsl #14
d001168c:	73a6f44f 			; <UNDEFINED> instruction: 0x73a6f44f
d0011690:	4308fb03 	movwmi	pc, #35587	; 0x8b03	; <UNPREDICTABLE>
d0011694:	f893b2bf 			; <UNDEFINED> instruction: 0xf893b2bf
d0011698:	b14a230a 	cmplt	sl, sl, lsl #6
d001169c:	3308f8b3 	movwcc	pc, #34995	; 0x88b3	; <UNPREDICTABLE>
d00116a0:	d005421f 	andle	r4, r5, pc, lsl r2
d00116a4:	e68f2501 	str	r2, [pc], r1, lsl #10
d00116a8:	e7b4461f 			; <UNDEFINED> instruction: 0xe7b4461f
d00116ac:	e7cc463a 			; <UNDEFINED> instruction: 0xe7cc463a
d00116b0:	31fcf8d4 	ldrsbcc	pc, [ip, #132]!	; 0x84	; <UNPREDICTABLE>
d00116b4:	d1062b0c 	tstle	r6, ip, lsl #22
d00116b8:	2b006da3 	blcs	0xd002cd4c
d00116bc:	ae83f47f 	mcrge	4, 4, pc, cr3, cr15, {3}	; <UNPREDICTABLE>
d00116c0:	447b4b48 	ldrbtmi	r4, [fp], #-2888	; 0xfffff4b8
d00116c4:	f44fe687 	vst1.32	{d30-d32}, [pc], r7
d00116c8:	fb0171a6 	blx	0xd006dd6a
d00116cc:	1863f108 	stmdane	r3!, {r3, r8, ip, sp, lr, pc}^
d00116d0:	330bf893 	movwcc	pc, #47251	; 0xb893	; <UNPREDICTABLE>
d00116d4:	6fa1b94b 	svcvs	0x00a1b94b
d00116d8:	d1234541 			; <UNDEFINED> instruction: 0xd1234541
d00116dc:	2b006da3 	blcs	0xd002cd70
d00116e0:	ae71f47f 	mrcge	4, 3, APSR_nzcv, cr1, cr15, {3}
d00116e4:	447b4b40 	ldrbtmi	r4, [fp], #-2880	; 0xfffff4c0
d00116e8:	f201e675 	vmin.s8	q7, <illegal reg q0.5>, <illegal reg q10.5>
d00116ec:	f504310b 			; <UNDEFINED> instruction: 0xf504310b
d00116f0:	f504492b 			; <UNDEFINED> instruction: 0xf504492b
d00116f4:	f04f4b4f 			; <UNDEFINED> instruction: 0xf04f4b4f
d00116f8:	44210a00 	strtmi	r0, [r1], #-2560	; 0xfffff600
d00116fc:	0988f109 	stmibeq	r8, {r0, r3, r8, ip, sp, lr, pc}
d0011700:	0b88f10b 	bleq	0xce24db34
d0011704:	3000f8db 	ldrdcc	pc, [r0], -fp
d0011708:	d2e4459a 	rscle	r4, r4, #645922816	; 0x26800000
d001170c:	91064648 	tstls	r6, r8, asr #12
d0011710:	0948f109 	stmdbeq	r8, {r0, r3, r8, ip, sp, lr, pc}^
d0011714:	f816f011 			; <UNDEFINED> instruction: 0xf816f011
d0011718:	d0c32800 	sbcle	r2, r3, r0, lsl #16
d001171c:	0a01f10a 	beq	0xd008db4c
d0011720:	e7ef9906 	strb	r9, [pc, r6, lsl #18]!
d0011724:	01fcf8d4 	ldrsbeq	pc, [ip, #132]!	; 0x84	; <UNPREDICTABLE>
d0011728:	f1042200 			; <UNDEFINED> instruction: 0xf1042200
d001172c:	42820c94 	addmi	r0, r2, #148, 24	; 0x9400
d0011730:	1342ea4f 	movtne	lr, #10831	; 0x2a4f
d0011734:	3201d13a 	andcc	sp, r1, #-2147483634	; 0x8000000e
d0011738:	f8d468e5 			; <UNDEFINED> instruction: 0xf8d468e5
d001173c:	44239074 	strtmi	r9, [r3], #-116	; 0xffffff8c
d0011740:	21fcf8c4 	mvnscs	pc, r4, asr #17
d0011744:	020cf24d 	andeq	pc, ip, #-805306364	; 0xd0000004
d0011748:	e004f8d4 	ldrd	pc, [r4], -r4
d001174c:	c002f854 	andgt	pc, r2, r4, asr r8	; <UNPREDICTABLE>
d0011750:	e9d46822 	ldmib	r4, {r1, r5, fp, sp, lr}^
d0011754:	f8c36004 			; <UNDEFINED> instruction: 0xf8c36004
d0011758:	25015088 	strcs	r5, [r1, #-136]	; 0xffffff78
d001175c:	608cf8c3 	addvs	pc, ip, r3, asr #17
d0011760:	f8c367da 			; <UNDEFINED> instruction: 0xf8c367da
d0011764:	e9c3c098 	stmib	r3, {r3, r4, r7, lr, pc}^
d0011768:	e9c30124 	stmib	r3, {r2, r5, r8}^
d001176c:	f44f9e20 			; <UNDEFINED> instruction: 0xf44f9e20
d0011770:	fb0373a6 	blx	0xd00ee612
d0011774:	18e1f308 	stmiane	r1!, {r3, r8, r9, ip, sp, lr, pc}^
d0011778:	7300f503 	movwvc	pc, #1283	; 0x503	; <UNPREDICTABLE>
d001177c:	2308f8b1 	movwcs	pc, #34993	; 0x88b1	; <UNPREDICTABLE>
d0011780:	f8d14423 			; <UNDEFINED> instruction: 0xf8d14423
d0011784:	43170300 	tstmi	r7, #0, 6
d0011788:	522ef504 	eorpl	pc, lr, #4, 10	; 0x1000000
d001178c:	f8a13208 			; <UNDEFINED> instruction: 0xf8a13208
d0011790:	44027308 	strmi	r7, [r2], #-776	; 0xfffffcf8
d0011794:	f8d16022 			; <UNDEFINED> instruction: 0xf8d16022
d0011798:	67632304 	strbvs	r2, [r3, -r4, lsl #6]!
d001179c:	22006062 	andcs	r6, r0, #98	; 0x62
d00117a0:	8078f8c4 	rsbshi	pc, r8, r4, asr #17
d00117a4:	e9c460e2 	stmib	r4, {r1, r5, r6, r7, sp, lr}^
d00117a8:	e60d5504 	str	r5, [sp], -r4, lsl #10
d00117ac:	3003f85c 	andcc	pc, r3, ip, asr r8	; <UNPREDICTABLE>
d00117b0:	d0934598 	umullsle	r4, r3, r8, r5
d00117b4:	e7ba3201 	ldr	r3, [sl, r1, lsl #4]!
d00117b8:	00800013 	addeq	r0, r0, r3, lsl r0
d00117bc:	fffffe34 			; <UNDEFINED> instruction: 0xfffffe34
d00117c0:	fffffe3f 			; <UNDEFINED> instruction: 0xfffffe3f
d00117c4:	fffffe35 			; <UNDEFINED> instruction: 0xfffffe35
d00117c8:	fffffe28 			; <UNDEFINED> instruction: 0xfffffe28
d00117cc:	fffffe1b 			; <UNDEFINED> instruction: 0xfffffe1b
d00117d0:	fffffde8 			; <UNDEFINED> instruction: 0xfffffde8
d00117d4:	fffffe11 			; <UNDEFINED> instruction: 0xfffffe11
d00117d8:	fffffdf9 			; <UNDEFINED> instruction: 0xfffffdf9
d00117dc:	fffffe12 			; <UNDEFINED> instruction: 0xfffffe12
d00117e0:	fffffd4f 			; <UNDEFINED> instruction: 0xfffffd4f
d00117e4:	fffffc8f 			; <UNDEFINED> instruction: 0xfffffc8f
d00117e8:	fffffc8b 			; <UNDEFINED> instruction: 0xfffffc8b

Disassembly of section .text.scan:

d0011988 <.text.scan>:
d0011988:	e92d6d8b 	push	{r0, r1, r3, r7, r8, sl, fp, sp, lr}
d001198c:	46064ff0 			; <UNDEFINED> instruction: 0x46064ff0
d0011990:	460cb09d 			; <UNDEFINED> instruction: 0x460cb09d
d0011994:	f501bba3 			; <UNDEFINED> instruction: 0xf501bba3
d0011998:	f1084850 			; <UNDEFINED> instruction: 0xf1084850
d001199c:	4620080c 	strtmi	r0, [r0], -ip, lsl #16
d00119a0:	fcacf7fe 	stc2	7, cr15, [ip], #1016	; 0x3f8
d00119a4:	d14f2800 	cmple	pc, r0, lsl #16
d00119a8:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d00119ac:	fc5cf7fe 	mrrc2	7, 15, pc, ip, cr14	; <UNPREDICTABLE>
d00119b0:	d0282820 	eorle	r2, r8, r0, lsr #16
d00119b4:	d0262809 	eorle	r2, r6, r9, lsl #16
d00119b8:	68e22823 	stmiavs	r2!, {r0, r1, r5, fp, sp}^
d00119bc:	d1366863 	teqle	r6, r3, ror #16
d00119c0:	d241429a 	suble	r4, r1, #-1610612727	; 0xa0000009
d00119c4:	0930f10d 	ldmdbeq	r0!, {r0, r2, r3, r8, ip, sp, lr, pc}
d00119c8:	466f4621 	strbtmi	r4, [pc], -r1, lsr #12
d00119cc:	4648ad14 			; <UNDEFINED> instruction: 0x4648ad14
d00119d0:	fc72f7fe 	ldc2l	7, cr15, [r2], #-1016	; 0xfffffc08
d00119d4:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d00119d8:	f10dfc50 			; <UNDEFINED> instruction: 0xf10dfc50
d00119dc:	e8bc0c38 	ldm	ip!, {r3, r4, r5, sl, fp}
d00119e0:	c70f000f 	strgt	r0, [pc, -pc]
d00119e4:	0003e89c 	muleq	r3, ip, r8
d00119e8:	0003e887 	andeq	lr, r3, r7, lsl #17
d00119ec:	46284621 	strtmi	r4, [r8], -r1, lsr #12
d00119f0:	000ce899 	muleq	ip, r9, r8
d00119f4:	fd2af000 	stc2	0, cr15, [sl, #-0]
d00119f8:	b1436da3 	smlaltblt	r6, r3, r3, sp
d00119fc:	46304621 	ldrtmi	r4, [r0], -r1, lsr #12
d0011a00:	fc5af7fe 	mrrc2	7, 15, pc, sl, cr14	; <UNPREDICTABLE>
d0011a04:	4620e00f 	strtmi	lr, [r0], -pc
d0011a08:	fc37f7fe 	ldc2	7, cr15, [r7], #-1016	; 0xfffffc08
d0011a0c:	9b19e7cc 	blls	0xd068b944
d0011a10:	7f97f5b3 	svcvc	0x0097f5b3
d0011a14:	462cd0c3 	strtmi	sp, [ip], -r3, asr #1
d0011a18:	cc0f4637 	stcgt	6, cr4, [pc], {55}	; 0x37
d0011a1c:	e894c70f 	ldm	r4, {r0, r1, r2, r3, r8, r9, sl, lr, pc}
d0011a20:	e887000f 	stm	r7, {r0, r1, r2, r3}
d0011a24:	4630000f 	ldrtmi	r0, [r0], -pc
d0011a28:	e8bdb01d 	pop	{r0, r2, r3, r4, ip, sp, pc}
d0011a2c:	429a8ff0 	addsmi	r8, sl, #240, 30	; 0x3c0
d0011a30:	4620d20a 	strtmi	sp, [r0], -sl, lsl #4
d0011a34:	fc7ff7fe 	ldc2l	7, cr15, [pc], #-1016	; 0xd0011644
d0011a38:	686368e2 	stmdavs	r3!, {r1, r5, r6, r7, fp, sp, lr}^
d0011a3c:	d2ae429a 	adcle	r4, lr, #-1610612727	; 0xa0000009
d0011a40:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011a44:	e7aafc1a 			; <UNDEFINED> instruction: 0xe7aafc1a
d0011a48:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d0011a4c:	fc0cf7fe 	stc2	7, cr15, [ip], {254}	; 0xfe
d0011a50:	d0f52820 	rscsle	r2, r5, r0, lsr #16
d0011a54:	0309f1a0 	movweq	pc, #37280	; 0x91a0	; <UNPREDICTABLE>
d0011a58:	d9f12b04 	ldmible	r1!, {r2, r8, r9, fp, sp}^
d0011a5c:	d170282f 	cmnle	r0, pc, lsr #16
d0011a60:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d0011a64:	fc00f7fe 	stc2	7, cr15, [r0], {254}	; 0xfe
d0011a68:	d10f282f 	tstle	pc, pc, lsr #16
d0011a6c:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d0011a70:	fbfaf7fe 	blx	0xcfecfa72
d0011a74:	686368e2 	stmdavs	r3!, {r1, r5, r6, r7, fp, sp, lr}^
d0011a78:	d090429a 	umullsle	r4, r0, sl, r2
d0011a7c:	d08e280a 	addle	r2, lr, sl, lsl #16
d0011a80:	d08c280d 	addle	r2, ip, sp, lsl #16
d0011a84:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011a88:	e7effbf8 			; <UNDEFINED> instruction: 0xe7effbf8
d0011a8c:	d158282a 	cmple	r8, sl, lsr #16
d0011a90:	4621a814 			; <UNDEFINED> instruction: 0x4621a814
d0011a94:	fc10f7fe 	ldc2	7, cr15, [r0], {254}	; 0xfe
d0011a98:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011a9c:	4620fbee 	strtmi	pc, [r0], -lr, ror #23
d0011aa0:	fbebf7fe 	blx	0xcfb0faa2
d0011aa4:	686368e2 	stmdavs	r3!, {r1, r5, r6, r7, fp, sp, lr}^
d0011aa8:	f000429a 			; <UNDEFINED> instruction: 0xf000429a
d0011aac:	210082c0 	smlabtcs	r0, r0, r2, r8
d0011ab0:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011ab4:	282afbd9 	stmdacs	sl!, {r0, r3, r4, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d0011ab8:	2101d1f1 	strdcs	sp, [r1, -r1]
d0011abc:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011ac0:	282ffbd3 	stmdacs	pc!, {r0, r1, r4, r6, r7, r8, r9, fp, ip, sp, lr, pc}	; <UNPREDICTABLE>
d0011ac4:	4620d1eb 	strtmi	sp, [r0], -fp, ror #3
d0011ac8:	fbd7f7fe 	blx	0xcf60faca
d0011acc:	3b01e7b8 	blcc	0xd008b9b4
d0011ad0:	0000f8d8 	ldrdeq	pc, [r0], -r8
d0011ad4:	1143eb04 	cmpne	r3, r4, lsl #22
d0011ad8:	f8d1015a 			; <UNDEFINED> instruction: 0xf8d1015a
d0011adc:	42881098 	addmi	r1, r8, #152	; 0x98
d0011ae0:	f8dfd006 			; <UNDEFINED> instruction: 0xf8dfd006
d0011ae4:	447915e4 	ldrbtmi	r1, [r9], #-1508	; 0xfffffa1c
d0011ae8:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011aec:	e785fbaf 	str	pc, [r5, pc, lsr #23]
d0011af0:	f8c4327c 			; <UNDEFINED> instruction: 0xf8c4327c
d0011af4:	18a331fc 	stmiane	r3!, {r2, r3, r4, r5, r6, r7, r8, ip, sp}
d0011af8:	c002f854 	andgt	pc, r2, r4, asr r8	; <UNPREDICTABLE>
d0011afc:	000cf103 	andeq	pc, ip, r3, lsl #2
d0011b00:	689d685f 	ldmvs	sp, {r0, r1, r2, r3, r4, r6, fp, sp, lr}
d0011b04:	e9c4c80f 	stmib	r4, {r0, r1, r2, r3, fp, lr, pc}^
d0011b08:	22011204 	andcs	r1, r1, #4, 4	; 0x40000000
d0011b0c:	c000f8c4 	andgt	pc, r0, r4, asr #17
d0011b10:	60656767 	rsbvs	r6, r5, r7, ror #14
d0011b14:	67a360e0 	strvs	r6, [r3, r0, ror #1]!
d0011b18:	686368e1 	stmdavs	r3!, {r0, r5, r6, r7, fp, sp, lr}^
d0011b1c:	f0404299 			; <UNDEFINED> instruction: 0xf0404299
d0011b20:	f8d48297 			; <UNDEFINED> instruction: 0xf8d48297
d0011b24:	2b0031fc 	blcs	0xd001e31c
d0011b28:	2a00d1d1 	bcs	0xd0046274
d0011b2c:	af37f47f 	svcge	0x0037f47f
d0011b30:	3000f8d8 	ldrdcc	pc, [r0], -r8
d0011b34:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d0011b38:	f8df828e 			; <UNDEFINED> instruction: 0xf8df828e
d0011b3c:	44791590 	ldrbtmi	r1, [r9], #-1424	; 0xfffffa70
d0011b40:	2200e7d2 	andcs	lr, r0, #55050240	; 0x3480000
d0011b44:	4620e7e8 	strtmi	lr, [r0], -r8, ror #15
d0011b48:	fb97f7fe 	blx	0xce60fb4a
d0011b4c:	46812823 	strmi	r2, [r1], r3, lsr #16
d0011b50:	f10dd123 			; <UNDEFINED> instruction: 0xf10dd123
d0011b54:	46ec0e38 			; <UNDEFINED> instruction: 0x46ec0e38
d0011b58:	e8beaf14 	ldm	lr!, {r2, r4, r8, r9, sl, fp, sp, pc}
d0011b5c:	e8ac000f 	stmia	ip!, {r0, r1, r2, r3}
d0011b60:	e89e000f 	ldm	lr, {r0, r1, r2, r3}
d0011b64:	e88c0003 	stm	ip, {r0, r1}
d0011b68:	46210003 	strtmi	r0, [r1], -r3
d0011b6c:	e8954638 	ldm	r5, {r3, r4, r5, r9, sl, lr}
d0011b70:	f000000c 			; <UNDEFINED> instruction: 0xf000000c
d0011b74:	6da3fc6b 	stcvs	12, cr15, [r3, #428]!	; 0x1ac
d0011b78:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0011b7c:	9b19af3f 	blls	0xd067d880
d0011b80:	7f97f5b3 	svcvc	0x0097f5b3
d0011b84:	af0bf43f 	svcge	0x000bf43f
d0011b88:	4635463c 			; <UNDEFINED> instruction: 0x4635463c
d0011b8c:	c50fcc0f 	strgt	ip, [pc, #-3087]	; 0xd0010f85
d0011b90:	000fe894 	muleq	pc, r4, r8	; <UNPREDICTABLE>
d0011b94:	000fe885 	andeq	lr, pc, r5, lsl #17
d0011b98:	f7fee745 			; <UNDEFINED> instruction: 0xf7fee745
d0011b9c:	4601fc46 	strmi	pc, [r1], -r6, asr #24
d0011ba0:	d1402800 	cmple	r0, r0, lsl #16
d0011ba4:	0830f1a9 	ldmdaeq	r0!, {r0, r3, r5, r7, r8, ip, sp, lr, pc}
d0011ba8:	0f09f1b8 	svceq	0x0009f1b8
d0011bac:	8111f200 	tsthi	r1, r0, lsl #4	; <UNPREDICTABLE>
d0011bb0:	0f30f1b9 	svceq	0x0030f1b9
d0011bb4:	8266f000 	rsbhi	pc, r6, #0
d0011bb8:	2100270a 	tstcs	r0, sl, lsl #14
d0011bbc:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011bc0:	4681fb53 	pkhtbmi	pc, r1, r3, asr #22	; <UNPREDICTABLE>
d0011bc4:	fc7ef7fe 	ldc2l	7, cr15, [lr], #-1016	; 0xfffffc08
d0011bc8:	f2004287 	vhsub.s8	d4, d16, d7
d0011bcc:	f04980db 			; <UNDEFINED> instruction: 0xf04980db
d0011bd0:	f1b90920 			; <UNDEFINED> instruction: 0xf1b90920
d0011bd4:	d1020f75 	tstle	r2, r5, ror pc
d0011bd8:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011bdc:	2100fb4e 	tstcs	r0, lr, asr #22	; <UNPREDICTABLE>
d0011be0:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011be4:	f1a0fb41 			; <UNDEFINED> instruction: 0xf1a0fb41
d0011be8:	46020330 			; <UNDEFINED> instruction: 0x46020330
d0011bec:	d90f2b09 	stmdble	pc, {r0, r3, r8, r9, fp, sp}	; <UNPREDICTABLE>
d0011bf0:	fc1bf7fe 	ldc2	7, cr15, [fp], {254}	; 0xfe
d0011bf4:	2a2eb960 	bcs	0xd0bc017c
d0011bf8:	f1b9d00a 			; <UNDEFINED> instruction: 0xf1b9d00a
d0011bfc:	f0000f75 			; <UNDEFINED> instruction: 0xf0000f75
d0011c00:	2f0a80e2 	svccs	0x000a80e2
d0011c04:	80d4f040 	sbcshi	pc, r4, r0, asr #32
d0011c08:	0f00f1b8 	svceq	0x0000f1b8
d0011c0c:	80def280 	sbcshi	pc, lr, r0, lsl #5
d0011c10:	2b006da3 	blcs	0xd002d2a4
d0011c14:	aef2f47f 	mrcge	4, 7, APSR_nzcv, cr2, cr15, {3}
d0011c18:	34b4f8df 	ldrtcc	pc, [r4], #2271	; 0x8df	; <UNPREDICTABLE>
d0011c1c:	e041447b 	sub	r4, r1, fp, ror r4
d0011c20:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011c24:	2100fb2a 	tstcs	r0, sl, lsr #22	; <UNPREDICTABLE>
d0011c28:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011c2c:	4602fb1d 			; <UNDEFINED> instruction: 0x4602fb1d
d0011c30:	fbfbf7fe 	blx	0xcff0fc32
d0011c34:	d1f32800 	mvnsle	r2, r0, lsl #16
d0011c38:	2a093a30 	bcs	0xd0260500
d0011c3c:	6825d9f0 	stmdavs	r5!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
d0011c40:	68e34680 	stmiavs	r3!, {r7, r9, sl, lr}^
d0011c44:	948cf8df 	strls	pc, [ip], #2271	; 0x8df
d0011c48:	44f9441d 	ldrbtmi	r4, [r9], #1053	; 0x41d
d0011c4c:	f8591bed 			; <UNDEFINED> instruction: 0xf8591bed
d0011c50:	46292b04 	strtmi	r2, [r9], -r4, lsl #22
d0011c54:	f7fe4638 			; <UNDEFINED> instruction: 0xf7fe4638
d0011c58:	b160fe5b 	msrlt	(UNDEF: 96), fp
d0011c5c:	1007f208 	andne	pc, r7, r8, lsl #4
d0011c60:	9011950d 	andsls	r9, r1, sp, lsl #10
d0011c64:	ad0c4634 	stcge	6, cr4, [ip, #-208]	; 0xffffff30
d0011c68:	c40fcd0f 	strgt	ip, [pc], #-3343	; 0xd0011c70
d0011c6c:	000fe895 	muleq	pc, r5, r8	; <UNPREDICTABLE>
d0011c70:	000fe884 	andeq	lr, pc, r4, lsl #17
d0011c74:	f108e6d7 			; <UNDEFINED> instruction: 0xf108e6d7
d0011c78:	f1b80801 			; <UNDEFINED> instruction: 0xf1b80801
d0011c7c:	d1e60f15 	mvnle	r0, r5, lsl pc
d0011c80:	9454f8df 	ldrbls	pc, [r4], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d0011c84:	44f94680 	ldrbtmi	r4, [r9], #1664	; 0x680
d0011c88:	2b04f859 	blcs	0xd014fdf4
d0011c8c:	46384629 	ldrtmi	r4, [r8], -r9, lsr #12
d0011c90:	fe3ef7fe 	mrc2	7, 1, pc, cr14, cr14, {7}
d0011c94:	6da3b168 	stfvsd	f3, [r3, #416]!	; 0x1a0
d0011c98:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0011c9c:	f8dfaeaf 			; <UNDEFINED> instruction: 0xf8dfaeaf
d0011ca0:	447b343c 	ldrbtmi	r3, [fp], #-1084	; 0xfffffbc4
d0011ca4:	9b0665a3 	blls	0xd01ab338
d0011ca8:	ba18e9c4 	blt	0xd064c3c0
d0011cac:	9b0765e3 	blls	0xd01eb440
d0011cb0:	f108e1cc 			; <UNDEFINED> instruction: 0xf108e1cc
d0011cb4:	f1b80801 			; <UNDEFINED> instruction: 0xf1b80801
d0011cb8:	d1e50f17 	mvnle	r0, r7, lsl pc
d0011cbc:	4639462a 	ldrtmi	r4, [r9], -sl, lsr #12
d0011cc0:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011cc4:	2800fb4b 	stmdacs	r0, {r0, r1, r3, r6, r8, r9, fp, ip, sp, lr, pc}
d0011cc8:	2128db0c 			; <UNDEFINED> instruction: 0x2128db0c
d0011ccc:	fb01950d 	blx	0xd007710a
d0011cd0:	f5044400 			; <UNDEFINED> instruction: 0xf5044400
d0011cd4:	f8d43478 			; <UNDEFINED> instruction: 0xf8d43478
d0011cd8:	930e30b0 	movwls	r3, #57520	; 0xe0b0
d0011cdc:	7381f44f 	orrvc	pc, r1, #1325400064	; 0x4f000000
d0011ce0:	e7bf9311 			; <UNDEFINED> instruction: 0xe7bf9311
d0011ce4:	4639462a 	ldrtmi	r4, [r9], -sl, lsr #12
d0011ce8:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011cec:	2800fb7c 	stmdacs	r0, {r2, r3, r4, r5, r6, r8, r9, fp, ip, sp, lr, pc}
d0011cf0:	2348db2a 	movtcs	sp, #35626	; 0x8b2a
d0011cf4:	4000fb03 	andmi	pc, r0, r3, lsl #22
d0011cf8:	402bf500 	eormi	pc, fp, r0, lsl #10
d0011cfc:	e9d030c8 	ldmib	r0, {r3, r6, r7, ip, sp}^
d0011d00:	f1100100 			; <UNDEFINED> instruction: 0xf1100100
d0011d04:	93084300 	movwls	r4, #33536	; 0x8300
d0011d08:	0300f141 	movweq	pc, #321	; 0x141	; <UNPREDICTABLE>
d0011d0c:	e9dd9309 	ldmib	sp, {r0, r3, r8, r9, ip, pc}^
d0011d10:	2b012308 	blcs	0xd005a938
d0011d14:	f1b2bf08 			; <UNDEFINED> instruction: 0xf1b2bf08
d0011d18:	d3064f00 	movwle	r4, #28416	; 0x6f00
d0011d1c:	2b006da3 	blcs	0xd002d3b0
d0011d20:	ae6cf47f 	mcrge	4, 3, pc, cr12, cr15, {3}	; <UNPREDICTABLE>
d0011d24:	447b4bee 	ldrbtmi	r4, [fp], #-3054	; 0xfffff412
d0011d28:	f06fe7bc 			; <UNDEFINED> instruction: 0xf06fe7bc
d0011d2c:	23004200 	movwcs	r4, #512	; 0x200
d0011d30:	4282900a 	addmi	r9, r2, #10
d0011d34:	f240418b 	vrhadd.s8	d20, d16, d11
d0011d38:	bfa81303 	svclt	0x00a81303
d0011d3c:	7381f44f 	orrvc	pc, r1, #1325400064	; 0x4f000000
d0011d40:	950d9a0a 	strls	r9, [sp, #-2570]	; 0xfffff5f6
d0011d44:	e7cb920e 	strb	r9, [fp, lr, lsl #4]
d0011d48:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d0011d4c:	4620e7f8 			; <UNDEFINED> instruction: 0x4620e7f8
d0011d50:	f7fe910a 			; <UNDEFINED> instruction: 0xf7fe910a
d0011d54:	990afa92 	stmdbls	sl, {r1, r4, r7, r9, fp, ip, sp, lr, pc}
d0011d58:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011d5c:	f7fefa85 			; <UNDEFINED> instruction: 0xf7fefa85
d0011d60:	2810fbb1 	ldmdacs	r0, {r0, r4, r5, r7, r8, r9, fp, ip, sp, lr, pc}
d0011d64:	d1214607 			; <UNDEFINED> instruction: 0xd1214607
d0011d68:	2b006da3 	blcs	0xd002d3fc
d0011d6c:	af25f47f 	svcge	0x0025f47f
d0011d70:	447b4bdc 	ldrbtmi	r4, [fp], #-3036	; 0xfffff424
d0011d74:	9b0665a3 	blls	0xd01ab408
d0011d78:	9b0765e3 	blls	0xd01eb50c
d0011d7c:	ba18e9c4 	blt	0xd064c494
d0011d80:	e71a66a3 	ldr	r6, [sl, -r3, lsr #13]
d0011d84:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011d88:	f7fefa78 			; <UNDEFINED> instruction: 0xf7fefa78
d0011d8c:	43c3fb9b 	bicmi	pc, r3, #158720	; 0x26c00
d0011d90:	f3f7fbb3 			; <UNDEFINED> instruction: 0xf3f7fbb3
d0011d94:	d2064543 	andle	r4, r6, #281018368	; 0x10c00000
d0011d98:	2b006da3 	blcs	0xd002d42c
d0011d9c:	ae2ef47f 	mcrge	4, 1, pc, cr14, cr15, {3}	; <UNPREDICTABLE>
d0011da0:	447b4bd1 	ldrbtmi	r4, [fp], #-3025	; 0xfffff42f
d0011da4:	fb08e77e 	blx	0xd024bba6
d0011da8:	e7060807 	str	r0, [r6, -r7, lsl #16]
d0011dac:	e7042710 	smlad	r4, r0, r7, r2
d0011db0:	0f00f1b8 	svceq	0x0000f1b8
d0011db4:	1303f240 	movwne	pc, #12864	; 0x3240	; <UNPREDICTABLE>
d0011db8:	f44fbfa8 			; <UNDEFINED> instruction: 0xf44fbfa8
d0011dbc:	f8cd7381 			; <UNDEFINED> instruction: 0xf8cd7381
d0011dc0:	93118038 	tstls	r1, #56	; 0x38
d0011dc4:	f240e15c 	vand	q15, q0, q6
d0011dc8:	e7f81303 	ldrb	r1, [r8, r3, lsl #6]!
d0011dcc:	7381f44f 	orrvc	pc, r1, #1325400064	; 0x4f000000
d0011dd0:	f1b9e7f5 			; <UNDEFINED> instruction: 0xf1b9e7f5
d0011dd4:	d0020f22 	andle	r0, r2, r2, lsr #30
d0011dd8:	0f27f1b9 	svceq	0x0027f1b9
d0011ddc:	6823d171 	stmdavs	r3!, {r0, r4, r5, r6, r8, ip, lr, pc}
d0011de0:	4701f242 	strmi	pc, [r1, -r2, asr #4]
d0011de4:	68e39308 	stmiavs	r3!, {r3, r8, r9, ip, pc}^
d0011de8:	68e2930b 	stmiavs	r2!, {r0, r1, r3, r8, r9, ip, pc}^
d0011dec:	429a6863 	addsmi	r6, sl, #6488064	; 0x630000
d0011df0:	4620d05a 			; <UNDEFINED> instruction: 0x4620d05a
d0011df4:	fa41f7fe 	blx	0xd108fdf4
d0011df8:	d14a4581 	smlalbble	r4, sl, r1, r5
d0011dfc:	f1b99b08 			; <UNDEFINED> instruction: 0xf1b99b08
d0011e00:	68e70f22 	stmiavs	r7!, {r1, r5, r8, r9, sl, fp}^
d0011e04:	eb039a0b 	bl	0xd00f8638
d0011e08:	f1070802 			; <UNDEFINED> instruction: 0xf1070802
d0011e0c:	682733ff 	stmdavs	r7!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, ip, sp}
d0011e10:	eba7441f 	bl	0xce9e2e94
d0011e14:	d0390708 	eorsle	r0, r9, r8, lsl #14
d0011e18:	0907eb08 	stmdbeq	r7, {r3, r8, r9, fp, sp, lr, pc}
d0011e1c:	8050f8cd 	subshi	pc, r0, sp, asr #17
d0011e20:	d10645c8 	smlabtle	r6, r8, r5, r4
d0011e24:	2b006da3 	blcs	0xd002d4b8
d0011e28:	ade8f47f 	cfstrdge	mvd15, [r8, #508]!	; 0x1fc
d0011e2c:	447b4baf 	ldrbtmi	r4, [fp], #-2991	; 0xfffff451
d0011e30:	f108e738 			; <UNDEFINED> instruction: 0xf108e738
d0011e34:	9a080301 	bls	0xd0212a40
d0011e38:	9314990b 	tstls	r4, #180224	; 0x2c000
d0011e3c:	2a5c5c52 	bcs	0xd1728f8c
d0011e40:	d10e920a 	tstle	lr, sl, lsl #4
d0011e44:	d00c4599 	mulle	ip, r9, r5
d0011e48:	465aab14 			; <UNDEFINED> instruction: 0x465aab14
d0011e4c:	46209906 	strtmi	r9, [r0], -r6, lsl #18
d0011e50:	9b079301 	blls	0xd01f6a5c
d0011e54:	9008f8cd 	andls	pc, r8, sp, asr #17
d0011e58:	46539300 	ldrbmi	r9, [r3], -r0, lsl #6
d0011e5c:	fb5cf7fe 	blx	0xd174fe5e
d0011e60:	9b14900a 	blls	0xd0535e90
d0011e64:	d00a4599 	mulle	sl, r9, r5
d0011e68:	b9436da3 	stmdblt	r3, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0011e6c:	447b4ba0 	ldrbtmi	r4, [fp], #-2976	; 0xfffff460
d0011e70:	9b0665a3 	blls	0xd01ab504
d0011e74:	9b0765e3 	blls	0xd01eb608
d0011e78:	ba18e9c4 	blt	0xd064c590
d0011e7c:	f44f66a3 	vst1.32	{d22-d24}, [pc :128], r3
d0011e80:	9a0a7381 	bls	0xd02aec8c
d0011e84:	870ce9cd 	strhi	lr, [ip, -sp, asr #19]
d0011e88:	e79a920e 	ldr	r9, [sl, lr, lsl #4]
d0011e8c:	7382f44f 	orrvc	pc, r2, #1325400064	; 0x4f000000
d0011e90:	285ce7f7 	ldmdacs	ip, {r0, r1, r2, r4, r5, r6, r7, r8, r9, sl, sp, lr, pc}^
d0011e94:	4620d102 	strtmi	sp, [r0], -r2, lsl #2
d0011e98:	f9eff7fe 			; <UNDEFINED> instruction: 0xf9eff7fe
d0011e9c:	d8a4280d 	stmiale	r4!, {r0, r2, r3, fp, sp}
d0011ea0:	f000fa27 			; <UNDEFINED> instruction: 0xf000fa27
d0011ea4:	d5a007c3 	strle	r0, [r0, #1987]!	; 0x7c3
d0011ea8:	0f22f1b9 	svceq	0x0022f1b9
d0011eac:	4b91d102 	blmi	0xce4862bc
d0011eb0:	e001447b 	and	r4, r1, fp, ror r4
d0011eb4:	447b4b90 	ldrbtmi	r4, [fp], #-2960	; 0xfffff470
d0011eb8:	2a006da2 	bcs	0xd002d548
d0011ebc:	ad9ef47f 	cfldrsge	mvf15, [lr, #508]	; 0x1fc
d0011ec0:	900ae6f0 	strdls	lr, [sl], -r0
d0011ec4:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011ec8:	f029f9cf 			; <UNDEFINED> instruction: 0xf029f9cf
d0011ecc:	46800302 	strmi	r0, [r0], r2, lsl #6
d0011ed0:	2b3c990a 	blcs	0xd0f38300
d0011ed4:	4581d11e 	strmi	sp, [r1, #286]	; 0x11e
d0011ed8:	4620d11c 			; <UNDEFINED> instruction: 0x4620d11c
d0011edc:	f7fe9106 			; <UNDEFINED> instruction: 0xf7fe9106
d0011ee0:	f1b9f9cc 			; <UNDEFINED> instruction: 0xf1b9f9cc
d0011ee4:	99060f3c 	stmdbls	r6, {r2, r3, r4, r5, r8, r9, sl, fp}
d0011ee8:	f2404620 	vmax.s8	d20, d0, d16
d0011eec:	bf181727 	svclt	0x00181727
d0011ef0:	7794f44f 	ldrvc	pc, [r4, pc, asr #8]
d0011ef4:	f9b8f7fe 			; <UNDEFINED> instruction: 0xf9b8f7fe
d0011ef8:	d109283d 	tstle	r9, sp, lsr r8
d0011efc:	f2404620 	vmax.s8	d20, d0, d16
d0011f00:	f7fe172d 			; <UNDEFINED> instruction: 0xf7fe172d
d0011f04:	f1b9f9ba 			; <UNDEFINED> instruction: 0xf1b9f9ba
d0011f08:	bf080f3c 	svclt	0x00080f3c
d0011f0c:	7796f44f 	ldrvc	pc, [r6, pc, asr #8]
d0011f10:	e0b59711 	adcs	r9, r5, r1, lsl r7
d0011f14:	0f3df1b8 	svceq	0x003df1b8
d0011f18:	80c0f040 	sbchi	pc, r0, r0, asr #32
d0011f1c:	0f2bf1b9 	svceq	0x002bf1b9
d0011f20:	f1b9d002 			; <UNDEFINED> instruction: 0xf1b9d002
d0011f24:	d10a0f2d 	tstle	sl, sp, lsr #30
d0011f28:	f2404620 	vmax.s8	d20, d0, d16
d0011f2c:	f7fe1725 			; <UNDEFINED> instruction: 0xf7fe1725
d0011f30:	f1b9f9a4 			; <UNDEFINED> instruction: 0xf1b9f9a4
d0011f34:	bf180f2b 	svclt	0x00180f2b
d0011f38:	7793f44f 	ldrvc	pc, [r3, pc, asr #8]
d0011f3c:	f1b9e7e8 			; <UNDEFINED> instruction: 0xf1b9e7e8
d0011f40:	d0050f26 	andle	r0, r5, r6, lsr #30
d0011f44:	0f7cf1b9 	svceq	0x007cf1b9
d0011f48:	f1b9d002 			; <UNDEFINED> instruction: 0xf1b9d002
d0011f4c:	d10d0f5e 	tstle	sp, lr, asr pc
d0011f50:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011f54:	f1b9f992 			; <UNDEFINED> instruction: 0xf1b9f992
d0011f58:	d05f0f26 	subsle	r0, pc, r6, lsr #30
d0011f5c:	0f7cf1b9 	svceq	0x007cf1b9
d0011f60:	172bf240 	strne	pc, [fp, -r0, asr #4]!
d0011f64:	f44fbf08 			; <UNDEFINED> instruction: 0xf44fbf08
d0011f68:	e7d17795 	bfi	r7, r5, #15, #3
d0011f6c:	0f3df1b9 	svceq	0x003df1b9
d0011f70:	f1a9d112 			; <UNDEFINED> instruction: 0xf1a9d112
d0011f74:	2b02033c 	blcs	0xd0092c6c
d0011f78:	f1b9d911 			; <UNDEFINED> instruction: 0xf1b9d911
d0011f7c:	d1300f2d 	teqle	r0, sp, lsr #30
d0011f80:	0f3ef1b8 	svceq	0x003ef1b8
d0011f84:	4620d13e 			; <UNDEFINED> instruction: 0x4620d13e
d0011f88:	7791f44f 	ldrvc	pc, [r1, pc, asr #8]
d0011f8c:	f975f7fe 			; <UNDEFINED> instruction: 0xf975f7fe
d0011f90:	f1b9e7be 			; <UNDEFINED> instruction: 0xf1b9e7be
d0011f94:	d1130f3d 	tstle	r3, sp, lsr pc
d0011f98:	0f21f1b9 	svceq	0x0021f1b9
d0011f9c:	4620d1e9 	strtmi	sp, [r0], -r9, ror #3
d0011fa0:	f96bf7fe 			; <UNDEFINED> instruction: 0xf96bf7fe
d0011fa4:	0f3df1b9 	svceq	0x003df1b9
d0011fa8:	f1b9d03b 			; <UNDEFINED> instruction: 0xf1b9d03b
d0011fac:	d03b0f21 	eorsle	r0, fp, r1, lsr #30
d0011fb0:	0f3cf1b9 	svceq	0x003cf1b9
d0011fb4:	171ff240 	ldrne	pc, [pc, -r0, asr #4]
d0011fb8:	f44fbf08 			; <UNDEFINED> instruction: 0xf44fbf08
d0011fbc:	e7a7778f 	str	r7, [r7, pc, lsl #15]!
d0011fc0:	0f26f1b9 	svceq	0x0026f1b9
d0011fc4:	f1b9d002 			; <UNDEFINED> instruction: 0xf1b9d002
d0011fc8:	d10a0f7c 	tstle	sl, ip, ror pc
d0011fcc:	f2404620 	vmax.s8	d20, d0, d16
d0011fd0:	f7fe1721 			; <UNDEFINED> instruction: 0xf7fe1721
d0011fd4:	f1b8f952 			; <UNDEFINED> instruction: 0xf1b8f952
d0011fd8:	bf080f26 	svclt	0x00080f26
d0011fdc:	7790f44f 	ldrvc	pc, [r0, pc, asr #8]
d0011fe0:	f1b9e796 			; <UNDEFINED> instruction: 0xf1b9e796
d0011fe4:	d10d0f00 	tstle	sp, r0, lsl #30
d0011fe8:	b9436da3 	stmdblt	r3, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0011fec:	447b4b43 	ldrbtmi	r4, [fp], #-2883	; 0xfffff4bd
d0011ff0:	9b0665a3 	blls	0xd01ab684
d0011ff4:	9b0765e3 	blls	0xd01eb788
d0011ff8:	ba18e9c4 	blt	0xd064c710
d0011ffc:	f24066a3 	vmax.s8	d22, d16, d19
d0012000:	e7851705 	str	r1, [r5, r5, lsl #14]
d0012004:	0f3df1b8 	svceq	0x003df1b8
d0012008:	d181464f 	orrle	r4, r1, pc, asr #12
d001200c:	4649483c 			; <UNDEFINED> instruction: 0x4649483c
d0012010:	f0104478 			; <UNDEFINED> instruction: 0xf0104478
d0012014:	2800fbaf 	stmdacs	r0, {r0, r1, r2, r3, r5, r7, r8, r9, fp, ip, sp, lr, pc}
d0012018:	e779d1e6 	ldrb	sp, [r9, -r6, ror #3]!
d001201c:	1729f240 	strne	pc, [r9, -r0, asr #4]!
d0012020:	f44fe776 	vst1.16	{d30}, [pc :256], r6
d0012024:	e773778e 	ldrb	r7, [r3, -lr, lsl #15]!
d0012028:	171df240 	ldrne	pc, [sp, -r0, asr #4]
d001202c:	6da3e770 	stcvs	7, cr14, [r3, #448]!	; 0x1c0
d0012030:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0012034:	4a33ace3 	bmi	0xd0cfd3c8
d0012038:	3068f89d 	mlscc	r8, sp, r8, pc	; <UNPREDICTABLE>
d001203c:	65a2447a 	strvs	r4, [r2, #1146]!	; 0x47a
d0012040:	65e29a17 	strbvs	r9, [r2, #2583]!	; 0xa17
d0012044:	e9c49a18 	stmib	r4, {r3, r4, r9, fp, ip, pc}^
d0012048:	9b1b2318 	blls	0xd06dacb0
d001204c:	e4d566a3 	ldrb	r6, [r5], #1699	; 0x6a3
d0012050:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0012054:	ad0caca4 	stcge	12, cr10, [ip, #-656]	; 0xfffffd70
d0012058:	46284621 	strtmi	r4, [r8], -r1, lsr #12
d001205c:	f92cf7fe 			; <UNDEFINED> instruction: 0xf92cf7fe
d0012060:	68e29b0e 	stmiavs	r2!, {r1, r2, r3, r8, r9, fp, ip, pc}^
d0012064:	9b0f930a 	blls	0xd03f6c94
d0012068:	93069f0c 	movwls	r9, #28428	; 0x6f0c
d001206c:	f8dd9b13 			; <UNDEFINED> instruction: 0xf8dd9b13
d0012070:	9307b040 	movwls	fp, #28736	; 0x7040
d0012074:	f89d6863 			; <UNDEFINED> instruction: 0xf89d6863
d0012078:	429aa048 	addsmi	sl, sl, #72	; 0x48
d001207c:	ad63f47f 	cfstrdge	mvd15, [r3, #-508]!	; 0xfffffe04
d0012080:	e5f14634 	ldrb	r4, [r1, #1588]!	; 0x634
d0012084:	4620900a 	strtmi	r9, [r0], -sl
d0012088:	f8eef7fe 			; <UNDEFINED> instruction: 0xf8eef7fe
d001208c:	0020f040 	eoreq	pc, r0, r0, asr #32
d0012090:	2878990a 	ldmdacs	r8!, {r1, r3, r8, fp, ip, pc}^
d0012094:	ae5bf43f 	mrcge	4, 2, APSR_nzcv, cr11, cr15, {1}
d0012098:	e58e2708 	str	r2, [lr, #1800]	; 0x708
d001209c:	f47f45c1 			; <UNDEFINED> instruction: 0xf47f45c1
d00120a0:	f1b9af6c 			; <UNDEFINED> instruction: 0xf1b9af6c
d00120a4:	d0030f2b 	andle	r0, r3, fp, lsr #30
d00120a8:	0f2df1b9 	svceq	0x002df1b9
d00120ac:	af71f47f 	svcge	0x0071f47f
d00120b0:	f2404620 	vmax.s8	d20, d0, d16
d00120b4:	f7fe1723 			; <UNDEFINED> instruction: 0xf7fe1723
d00120b8:	f1b8f8e0 			; <UNDEFINED> instruction: 0xf1b8f8e0
d00120bc:	bf180f2b 	svclt	0x00180f2b
d00120c0:	7792f44f 	ldrvc	pc, [r2, pc, asr #8]
d00120c4:	bf00e724 	svclt	0x0000e724
d00120c8:	fffffd4d 			; <UNDEFINED> instruction: 0xfffffd4d
d00120cc:	fffffd19 			; <UNDEFINED> instruction: 0xfffffd19
d00120d0:	fffffce9 			; <UNDEFINED> instruction: 0xfffffce9
d00120d4:	00010bae 	andeq	r0, r1, lr, lsr #23
d00120d8:	00010bc6 	andeq	r0, r1, r6, asr #23
d00120dc:	fffffbd5 			; <UNDEFINED> instruction: 0xfffffbd5
d00120e0:	fffffb78 			; <UNDEFINED> instruction: 0xfffffb78
d00120e4:	fffffb55 			; <UNDEFINED> instruction: 0xfffffb55
d00120e8:	fffffb3e 			; <UNDEFINED> instruction: 0xfffffb3e
d00120ec:	fffffb05 			; <UNDEFINED> instruction: 0xfffffb05
d00120f0:	fffffac5 			; <UNDEFINED> instruction: 0xfffffac5
d00120f4:	fffff938 			; <UNDEFINED> instruction: 0xfffff938
d00120f8:	fffff94a 			; <UNDEFINED> instruction: 0xfffff94a
d00120fc:	fffff971 			; <UNDEFINED> instruction: 0xfffff971
d0012100:	fffff94b 			; <UNDEFINED> instruction: 0xfffff94b
d0012104:	fffff7e0 			; <UNDEFINED> instruction: 0xfffff7e0

Disassembly of section .text.scan_directive:

d001244c <.text.scan_directive>:
d001244c:	e92db082 	push	{r1, r7, ip, sp, pc}
d0012450:	ed2d4ff0 	vstr	FPSCR_nzcvqc, [sp, #-448]!	; 0xfffffe40
d0012454:	b09b8b02 	addslt	r8, fp, r2, lsl #22
d0012458:	ee08460c 	cfmadd32	mvax0, mvfx4, mvfx8, mvfx12
d001245c:	a9260a10 	stmdbge	r6!, {r4, r9, fp}
d0012460:	000ce881 	andeq	lr, ip, r1, lsl #17
d0012464:	9d299b2a 	vstmdbls	r9!, {d9-d29}
d0012468:	9b2d9308 	blls	0xd0b77090
d001246c:	a0b0f89d 	umlalsge	pc, r0, sp, r8	; <UNPREDICTABLE>
d0012470:	68e39309 	stmiavs	r3!, {r0, r3, r8, r9, ip, pc}^
d0012474:	6963930f 	stmdbvs	r3!, {r0, r1, r2, r3, r8, r9, ip, pc}^
d0012478:	21009310 	tstcs	r0, r0, lsl r3
d001247c:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0012480:	2820fef3 	stmdacs	r0!, {r0, r1, r4, r5, r6, r7, r9, sl, fp, ip, sp, lr, pc}
d0012484:	2809d02a 	stmdacs	r9, {r1, r3, r5, ip, lr, pc}
d0012488:	6827d028 	stmdavs	r7!, {r3, r5, ip, lr, pc}
d001248c:	441f68e3 	ldrmi	r6, [pc], #-2275	; 0xd0012494
d0012490:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d0012494:	fee8f7fd 	mcr2	7, 7, pc, cr8, cr13, {7}	; <UNPREDICTABLE>
d0012498:	ffc7f7fd 			; <UNDEFINED> instruction: 0xffc7f7fd
d001249c:	bb084681 	bllt	0xd0223ea8
d00124a0:	68e36822 	stmiavs	r3!, {r1, r5, fp, sp, lr}^
d00124a4:	1bd2441a 	blne	0xcf4a3514
d00124a8:	d11f2a07 	tstle	pc, r7, lsl #20
d00124ac:	1964f8df 	stmdbne	r4!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d00124b0:	920a4638 	andls	r4, sl, #56, 12	; 0x3800000
d00124b4:	f00e4479 			; <UNDEFINED> instruction: 0xf00e4479
d00124b8:	fab0fd3f 	blx	0xcec519bc
d00124bc:	9a0af680 	bls	0xd02cfec4
d00124c0:	f04f0976 			; <UNDEFINED> instruction: 0xf04f0976
d00124c4:	2a050b00 	bcs	0xd01550cc
d00124c8:	f8cd46d8 			; <UNDEFINED> instruction: 0xf8cd46d8
d00124cc:	f8cdb030 			; <UNDEFINED> instruction: 0xf8cdb030
d00124d0:	f8cdb028 			; <UNDEFINED> instruction: 0xf8cdb028
d00124d4:	d132b02c 	teqle	r2, ip, lsr #32
d00124d8:	bc8cf000 	stclt	0, cr15, [ip], {0}
d00124dc:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d00124e0:	e7cafecc 	strb	pc, [sl, ip, asr #29]	; <UNPREDICTABLE>
d00124e4:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d00124e8:	e7d1fec8 	ldrb	pc, [r1, r8, asr #29]	; <UNPREDICTABLE>
d00124ec:	f0402a06 			; <UNDEFINED> instruction: 0xf0402a06
d00124f0:	f8df8465 			; <UNDEFINED> instruction: 0xf8df8465
d00124f4:	46381924 	ldrtmi	r1, [r8], -r4, lsr #18
d00124f8:	464e920a 	strbmi	r9, [lr], -sl, lsl #4
d00124fc:	f00e4479 			; <UNDEFINED> instruction: 0xf00e4479
d0012500:	f8dffd1b 			; <UNDEFINED> instruction: 0xf8dffd1b
d0012504:	fab01918 	blx	0xcec1896c
d0012508:	9a0af880 	bls	0xd02d0710
d001250c:	46384479 			; <UNDEFINED> instruction: 0x46384479
d0012510:	fd12f00e 	ldc2	0, cr15, [r2, #-56]	; 0xffffffc8
d0012514:	f380fab0 			; <UNDEFINED> instruction: 0xf380fab0
d0012518:	1904f8df 	stmdbne	r4, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d001251c:	095b4638 	ldmdbeq	fp, {r3, r4, r5, r9, sl, lr}^
d0012520:	44799a0a 	ldrbtmi	r9, [r9], #-2570	; 0xfffff5f6
d0012524:	1858ea4f 	ldmdane	r8, {r0, r1, r2, r3, r6, r9, fp, sp, lr, pc}^
d0012528:	f00e930b 			; <UNDEFINED> instruction: 0xf00e930b
d001252c:	fab0fd05 	blx	0xcec51948
d0012530:	f8cdfb80 			; <UNDEFINED> instruction: 0xf8cdfb80
d0012534:	f8cd9030 			; <UNDEFINED> instruction: 0xf8cd9030
d0012538:	ea4f9028 	b	0xd13f65e0
d001253c:	23001b5b 	movwcs	r1, #2907	; 0xb5b
d0012540:	930d930e 	movwls	r9, #54030	; 0xd30e
d0012544:	2a02e03a 	bcs	0xd00ca634
d0012548:	2a04d022 	bcs	0xd01465d8
d001254c:	d1b8464e 			; <UNDEFINED> instruction: 0xd1b8464e
d0012550:	18d0f8df 	ldmne	r0, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d0012554:	920a4638 	andls	r4, sl, #56, 12	; 0x3800000
d0012558:	447946cb 	ldrbtmi	r4, [r9], #-1739	; 0xfffff935
d001255c:	f00e46c8 			; <UNDEFINED> instruction: 0xf00e46c8
d0012560:	fab0fceb 	blx	0xcec51914
d0012564:	f8dff380 			; <UNDEFINED> instruction: 0xf8dff380
d0012568:	463818c0 	ldrtmi	r1, [r8], -r0, asr #17
d001256c:	9a0a095b 	bls	0xd0294ae0
d0012570:	930e4479 	movwls	r4, #58489	; 0xe479
d0012574:	fce0f00e 	stc2l	0, cr15, [r0], #56	; 0x38
d0012578:	f380fab0 			; <UNDEFINED> instruction: 0xf380fab0
d001257c:	9034f8cd 	eorsls	pc, r4, sp, asr #17
d0012580:	9030f8cd 	eorsls	pc, r0, sp, asr #17
d0012584:	f8cd095b 			; <UNDEFINED> instruction: 0xf8cd095b
d0012588:	f8cd9028 			; <UNDEFINED> instruction: 0xf8cd9028
d001258c:	e015902c 	ands	r9, r5, ip, lsr #32
d0012590:	1898f8df 	ldmne	r8, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d0012594:	46cb4638 			; <UNDEFINED> instruction: 0x46cb4638
d0012598:	447946c8 	ldrbtmi	r4, [r9], #-1736	; 0xfffff938
d001259c:	f00e464e 			; <UNDEFINED> instruction: 0xf00e464e
d00125a0:	fab0fccb 	blx	0xcec518d4
d00125a4:	f8cdf380 			; <UNDEFINED> instruction: 0xf8cdf380
d00125a8:	095b9038 	ldmdbeq	fp, {r3, r4, r5, ip, pc}^
d00125ac:	9030f8cd 	eorsls	pc, r0, sp, asr #17
d00125b0:	9028f8cd 	eorls	pc, r8, sp, asr #17
d00125b4:	464b930d 	strbmi	r9, [fp], -sp, lsl #6
d00125b8:	902cf8cd 	eorls	pc, ip, sp, asr #17
d00125bc:	0708ea56 	smlsdeq	r8, r6, sl, lr
d00125c0:	815cf000 	cmphi	ip, r0	; <UNPREDICTABLE>
d00125c4:	93114620 	tstls	r1, #32, 12	; 0x2000000
d00125c8:	fe98f7fd 	mrc2	7, 4, pc, cr8, cr13, {7}
d00125cc:	28009b11 	stmdacs	r0, {r0, r4, r8, r9, fp, ip, pc}
d00125d0:	8154f000 	cmphi	r4, r0	; <UNPREDICTABLE>
d00125d4:	f10d9b0f 			; <UNDEFINED> instruction: 0xf10d9b0f
d00125d8:	ae120c98 	mrcge	12, 0, r0, cr2, cr8, {4}
d00125dc:	9b1060e3 	blls	0xd042a970
d00125e0:	e8bc6163 	ldm	ip!, {r0, r1, r5, r6, r8, sp, lr}
d00125e4:	c60f000f 	strgt	r0, [pc], -pc
d00125e8:	000fe89c 	muleq	pc, ip, r8	; <UNPREDICTABLE>
d00125ec:	000fe886 	andeq	lr, pc, r6, lsl #17
d00125f0:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d00125f4:	fe38f7fd 	mrc2	7, 1, pc, cr8, cr13, {7}
d00125f8:	d0332820 	eorsle	r2, r3, r0, lsr #16
d00125fc:	d0312809 	eorsle	r2, r1, r9, lsl #16
d0012600:	68e36826 	stmiavs	r3!, {r1, r2, r5, fp, sp, lr}^
d0012604:	2100441e 	tstcs	r0, lr, lsl r4
d0012608:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d001260c:	f7fdfe2d 			; <UNDEFINED> instruction: 0xf7fdfe2d
d0012610:	bb58ff0c 	bllt	0xd1652248
d0012614:	68e36822 	stmiavs	r3!, {r1, r5, fp, sp, lr}^
d0012618:	1b92441a 	blne	0xce4a3688
d001261c:	d1292a07 			; <UNDEFINED> instruction: 0xd1292a07
d0012620:	180cf8df 	stmdane	ip, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d0012624:	44794630 	ldrbtmi	r4, [r9], #-1584	; 0xfffff9d0
d0012628:	fc86f00e 	stc2	0, cr15, [r6], {14}
d001262c:	b3584607 	cmplt	r8, #7340032	; 0x700000
d0012630:	b94b6da3 	stmdblt	fp, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0012634:	37fcf8df 	ubfxcc	pc, pc, #17, #29
d0012638:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d001263c:	9b083516 	blls	0xd021fa9c
d0012640:	3a18e9c4 	bcc	0xd064cd58
d0012644:	66a39b09 	strtvs	r9, [r3], r9, lsl #22
d0012648:	ee184621 	cfmsub32	mvax1, mvfx4, mvfx8, mvfx1
d001264c:	f7fd0a10 			; <UNDEFINED> instruction: 0xf7fd0a10
d0012650:	ee18fe33 	mrc	14, 0, APSR_nzcv, cr8, cr3, {1}
d0012654:	b01b0a10 	andslt	r0, fp, r0, lsl sl
d0012658:	8b02ecbd 	blhi	0xd00cd954
d001265c:	4ff0e8bd 	svcmi	0x00f0e8bd
d0012660:	4770b002 	ldrbmi	fp, [r0, -r2]!
d0012664:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0012668:	e7c1fe08 	strb	pc, [r1, r8, lsl #28]	; <UNPREDICTABLE>
d001266c:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0012670:	e7c8fe04 	strb	pc, [r8, r4, lsl #28]	; <UNPREDICTABLE>
d0012674:	d1db2a06 	bicsle	r2, fp, r6, lsl #20
d0012678:	17bcf8df 	sbfxne	pc, pc, #17, #29
d001267c:	44794630 	ldrbtmi	r4, [r9], #-1584	; 0xfffff9d0
d0012680:	fc5af00e 	mrrc2	0, 0, pc, sl, cr14	; <UNPREDICTABLE>
d0012684:	d1d32800 	bicsle	r2, r3, r0, lsl #16
d0012688:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d001268c:	fdecf7fd 	stc2l	7, cr15, [ip, #1012]!	; 0x3f4
d0012690:	d0162820 	andsle	r2, r6, r0, lsr #16
d0012694:	d0142809 	andsle	r2, r4, r9, lsl #16
d0012698:	d0552f00 	subsle	r2, r5, r0, lsl #30
d001269c:	68e76826 	stmiavs	r7!, {r1, r2, r5, fp, sp, lr}^
d00126a0:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d00126a4:	fde0f7fd 	stc2l	7, cr15, [r0, #1012]!	; 0x3f4
d00126a8:	febff7fd 	mrc2	7, 5, pc, cr15, cr13, {7}
d00126ac:	6fa3b968 	svcvs	0x00a3b968
d00126b0:	da0e2b00 	ble	0xd039d2b8
d00126b4:	2b006da3 	blcs	0xd002dd48
d00126b8:	f8dfd1c6 			; <UNDEFINED> instruction: 0xf8dfd1c6
d00126bc:	447b3780 	ldrbtmi	r3, [fp], #-1920	; 0xfffff880
d00126c0:	4620e7bb 			; <UNDEFINED> instruction: 0x4620e7bb
d00126c4:	fdd9f7fd 	ldc2l	7, cr15, [r9, #1012]	; 0x3f4
d00126c8:	4620e7de 			; <UNDEFINED> instruction: 0x4620e7de
d00126cc:	fdd5f7fd 	ldc2l	7, cr15, [r5, #1012]	; 0x3f4
d00126d0:	6822e7e6 	stmdavs	r2!, {r1, r2, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d00126d4:	68e319f0 	stmiavs	r3!, {r4, r5, r6, r7, r8, fp, ip}^
d00126d8:	1a12441a 	bne	0xd04a3748
d00126dc:	d1e92a04 	mvnle	r2, r4, lsl #20
d00126e0:	175cf8df 	smmlsne	ip, pc, r8, pc	; <UNPREDICTABLE>
d00126e4:	f00e4479 			; <UNDEFINED> instruction: 0xf00e4479
d00126e8:	2800fc27 	stmdacs	r0, {r0, r1, r2, r5, sl, fp, ip, sp, lr, pc}
d00126ec:	6fa3d1e2 	svcvs	0x00a3d1e2
d00126f0:	72a6f44f 	adcvc	pc, r6, #1325400064	; 0x4f000000
d00126f4:	4303fb02 	movwmi	pc, #15106	; 0x3b02	; <UNPREDICTABLE>
d00126f8:	f8832201 			; <UNDEFINED> instruction: 0xf8832201
d00126fc:	2100230a 	tstcs	r0, sl, lsl #6
d0012700:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0012704:	2820fdb1 	stmdacs	r0!, {r0, r4, r5, r7, r8, sl, fp, ip, sp, lr, pc}
d0012708:	80b4f000 	adcshi	pc, r4, r0
d001270c:	f0002809 			; <UNDEFINED> instruction: 0xf0002809
d0012710:	68e280b1 	stmiavs	r2!, {r0, r4, r5, r7, pc}^
d0012714:	429a6863 	addsmi	r6, sl, #6488064	; 0x630000
d0012718:	80a6f000 	adchi	pc, r6, r0
d001271c:	f000280d 			; <UNDEFINED> instruction: 0xf000280d
d0012720:	280a80a3 	stmdacs	sl, {r0, r1, r5, r7, pc}
d0012724:	80a0f000 	adchi	pc, r0, r0
d0012728:	d106282f 	tstle	r6, pc, lsr #16
d001272c:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d0012730:	fd9af7fd 	ldc2	7, cr15, [sl, #1012]	; 0x3f4
d0012734:	f000282f 			; <UNDEFINED> instruction: 0xf000282f
d0012738:	6da38097 	stcvs	0, cr8, [r3, #604]!	; 0x25c
d001273c:	d1832b00 	orrle	r2, r3, r0, lsl #22
d0012740:	3700f8df 			; <UNDEFINED> instruction: 0x3700f8df
d0012744:	e778447b 			; <UNDEFINED> instruction: 0xe778447b
d0012748:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d001274c:	2822fd96 	stmdacs	r2!, {r1, r2, r4, r7, r8, sl, fp, ip, sp, lr, pc}
d0012750:	d0094680 	andle	r4, r9, r0, lsl #13
d0012754:	d01c283c 	andsle	r2, ip, ip, lsr r8
d0012758:	2b006da3 	blcs	0xd002ddec
d001275c:	af74f47f 	svcge	0x0074f47f
d0012760:	36e4f8df 	usatcc	pc, #4, pc, asr #17	; <UNPREDICTABLE>
d0012764:	e768447b 			; <UNDEFINED> instruction: 0xe768447b
d0012768:	68264681 	stmdavs	r6!, {r0, r7, r9, sl, lr}
d001276c:	210068e7 	smlattcs	r0, r7, r8, r6
d0012770:	68e24620 	stmiavs	r2!, {r5, r9, sl, lr}^
d0012774:	fd78f7fd 	ldc2l	7, cr15, [r8, #-1012]!	; 0xfffffc0c
d0012778:	429a6863 	addsmi	r6, sl, #6488064	; 0x630000
d001277c:	4581d30c 	strmi	sp, [r1, #780]	; 0x30c
d0012780:	6da3d014 	stcvs	0, cr13, [r3, #80]!	; 0x50
d0012784:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0012788:	f8dfaf5f 			; <UNDEFINED> instruction: 0xf8dfaf5f
d001278c:	447b36c0 	ldrbtmi	r3, [fp], #-1728	; 0xfffff940
d0012790:	f04fe753 			; <UNDEFINED> instruction: 0xf04fe753
d0012794:	e7e8093e 			; <UNDEFINED> instruction: 0xe7e8093e
d0012798:	d0074581 	andle	r4, r7, r1, lsl #11
d001279c:	d0f0280d 	rscsle	r2, r0, sp, lsl #16
d00127a0:	d0ee280a 	rscle	r2, lr, sl, lsl #16
d00127a4:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d00127a8:	e7e0fd68 	strb	pc, [r0, r8, ror #26]!	; <UNPREDICTABLE>
d00127ac:	68264437 	stmdavs	r6!, {r0, r1, r2, r4, r5, sl, lr}
d00127b0:	1bf64416 	blne	0xcfda3810
d00127b4:	4620d0e5 	strtmi	sp, [r0], -r5, ror #1
d00127b8:	fd5ff7fd 	ldc2l	7, cr15, [pc, #-1012]	; 0xd00123cc
d00127bc:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d00127c0:	fd52f7fd 	ldc2l	7, cr15, [r2, #-1012]	; 0xfffffc0c
d00127c4:	d0f62820 	rscsle	r2, r6, r0, lsr #16
d00127c8:	d0f42809 	rscsle	r2, r4, r9, lsl #16
d00127cc:	686368e2 	stmdavs	r3!, {r1, r5, r6, r7, fp, sp, lr}^
d00127d0:	d013429a 	mulsle	r3, sl, r2
d00127d4:	d011280d 	andsle	r2, r1, sp, lsl #16
d00127d8:	d00f280a 	andle	r2, pc, sl, lsl #16
d00127dc:	d105282f 	tstle	r5, pc, lsr #16
d00127e0:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d00127e4:	fd40f7fd 	stc2l	7, cr15, [r0, #-1012]	; 0xfffffc0c
d00127e8:	d007282f 	andle	r2, r7, pc, lsr #16
d00127ec:	2b006da3 	blcs	0xd002de80
d00127f0:	af2af47f 	svcge	0x002af47f
d00127f4:	3658f8df 			; <UNDEFINED> instruction: 0x3658f8df
d00127f8:	e71e447b 			; <UNDEFINED> instruction: 0xe71e447b
d00127fc:	d11b2e06 	tstle	fp, r6, lsl #28
d0012800:	1650f8df 			; <UNDEFINED> instruction: 0x1650f8df
d0012804:	46384632 			; <UNDEFINED> instruction: 0x46384632
d0012808:	f00e4479 			; <UNDEFINED> instruction: 0xf00e4479
d001280c:	b998fb95 	ldmiblt	r8, {r0, r2, r4, r7, r8, r9, fp, ip, sp, lr, pc}
d0012810:	ee189b08 	vnmls.f64	d9, d8, d8
d0012814:	95154a10 	ldrls	r4, [r5, #-2576]	; 0xfffff5f0
d0012818:	9316ad12 	tstls	r6, #1152	; 0x480
d001281c:	7383f44f 	orrvc	pc, r3, #1325400064	; 0x4f000000
d0012820:	a060f88d 	rsbge	pc, r0, sp, lsl #17
d0012824:	9b099317 	blls	0xd0277488
d0012828:	cd0f9319 	stcgt	3, cr9, [pc, #-100]	; 0xd00127cc
d001282c:	e895c40f 	ldm	r5, {r0, r1, r2, r3, sl, lr, pc}
d0012830:	e884000f 	stm	r4, {r0, r1, r2, r3}
d0012834:	e70c000f 	str	r0, [ip, -pc]
d0012838:	0f22f1b8 	svceq	0x0022f1b8
d001283c:	6da3d007 	stcvs	0, cr13, [r3, #28]!
d0012840:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0012844:	f8dfaf01 			; <UNDEFINED> instruction: 0xf8dfaf01
d0012848:	447b3610 	ldrbtmi	r3, [fp], #-1552	; 0xfffff9f0
d001284c:	9b09e6f5 	blls	0xd028c428
d0012850:	9a084629 	bls	0xd02240fc
d0012854:	93004620 	movwls	r4, #1568	; 0x620
d0012858:	96024653 			; <UNDEFINED> instruction: 0x96024653
d001285c:	f7fe9701 			; <UNDEFINED> instruction: 0xf7fe9701
d0012860:	2800fda5 	stmdacs	r0, {r0, r2, r5, r7, r8, sl, fp, ip, sp, lr, pc}
d0012864:	aef0f43f 	mrcge	4, 7, APSR_nzcv, cr0, cr15, {1}
d0012868:	ee184621 	cfmsub32	mvax1, mvfx4, mvfx8, mvfx1
d001286c:	f7ff0a10 			; <UNDEFINED> instruction: 0xf7ff0a10
d0012870:	e6eef88b 	strbt	pc, [lr], fp, lsl #17	; <UNPREDICTABLE>
d0012874:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0012878:	e740fd00 	strb	pc, [r0, -r0, lsl #26]	; <UNPREDICTABLE>
d001287c:	0206ea49 	andeq	lr, r6, #299008	; 0x49000
d0012880:	ea42990b 	b	0xd10b8cb4
d0012884:	430a0208 	movwmi	r0, #41480	; 0xa208
d0012888:	430a990a 	movwmi	r9, #43274	; 0xa90a
d001288c:	430a990c 	movwmi	r9, #43276	; 0xa90c
d0012890:	ea42990d 	b	0xd10b8ccc
d0012894:	430a020b 	movwmi	r0, #41483	; 0xa20b
d0012898:	430a990e 	movwmi	r9, #43278	; 0xa90e
d001289c:	d123431a 			; <UNDEFINED> instruction: 0xd123431a
d00128a0:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d00128a4:	b158fd2b 	cmplt	r8, fp, lsr #26	; <UNPREDICTABLE>
d00128a8:	b94b6da3 	stmdblt	fp, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d00128ac:	35acf8df 	strcc	pc, [ip, #2271]!	; 0x8df
d00128b0:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d00128b4:	9b083516 	blls	0xd021fd14
d00128b8:	3a18e9c4 	bcc	0xd064cfd0
d00128bc:	66a39b09 	strtvs	r9, [r3], r9, lsl #22
d00128c0:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d00128c4:	2220fd38 	eorcs	pc, r0, #56, 26	; 0xe00
d00128c8:	ee182100 	mufe	f2, f0, f0
d00128cc:	f00e0a10 			; <UNDEFINED> instruction: 0xf00e0a10
d00128d0:	f44ffb15 			; <UNDEFINED> instruction: 0xf44ffb15
d00128d4:	ee187397 	mrc	3, 0, r7, cr8, cr7, {4}
d00128d8:	61532a10 	cmpvs	r3, r0, lsl sl
d00128dc:	4620e6b9 			; <UNDEFINED> instruction: 0x4620e6b9
d00128e0:	f7fd930f 			; <UNDEFINED> instruction: 0xf7fd930f
d00128e4:	9b0ffcca 	blls	0xd0411c14
d00128e8:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d00128ec:	f7fd930f 			; <UNDEFINED> instruction: 0xf7fd930f
d00128f0:	2820fcbb 	stmdacs	r0!, {r0, r1, r3, r4, r5, r7, sl, fp, ip, sp, lr, pc}
d00128f4:	d0f29b0f 	rscsle	r9, r2, pc, lsl #22
d00128f8:	d0f02809 	rscsle	r2, r0, r9, lsl #16
d00128fc:	46209311 			; <UNDEFINED> instruction: 0x46209311
d0012900:	930f6823 	movwls	r6, #63523	; 0xf823
d0012904:	931068e3 	tstls	r0, #14876672	; 0xe30000
d0012908:	9b0f9a10 	blls	0xd03f9150
d001290c:	f7fd189f 			; <UNDEFINED> instruction: 0xf7fd189f
d0012910:	6821fd12 	stmdavs	r1!, {r1, r4, r8, sl, fp, ip, sp, lr, pc}
d0012914:	46bc68e2 	ldrtmi	r6, [ip], r2, ror #17
d0012918:	44119b11 	ldrmi	r9, [r1], #-2833	; 0xfffff4ef
d001291c:	0201f10c 	andeq	pc, r1, #12, 2
d0012920:	d301428a 	movwle	r4, #4746	; 0x128a
d0012924:	e033468c 	eors	r4, r3, ip, lsl #13
d0012928:	0c01f812 	stceq	8, cr15, [r1], {18}
d001292c:	d15a282f 	cmple	sl, pc, lsr #16
d0012930:	282f7810 	stmdacs	pc!, {r4, fp, ip, sp, lr}	; <UNPREDICTABLE>
d0012934:	282ad02c 	stmdacs	sl!, {r2, r3, r5, ip, lr, pc}
d0012938:	f10cd155 			; <UNDEFINED> instruction: 0xf10cd155
d001293c:	1c500202 	lfmne	f0, 2, [r0], {2}
d0012940:	d2174288 	andsle	r4, r7, #136, 4	; 0x80000008
d0012944:	6c01f810 	stcvs	8, cr15, [r1], {16}
d0012948:	d1112e2a 	tstle	r1, sl, lsr #28
d001294c:	2e2f7806 	cdpcs	8, 2, cr7, cr15, cr6, {0}
d0012950:	3202d10e 	andcc	sp, r2, #-2147483645	; 0x80000003
d0012954:	d21a428a 	andsle	r4, sl, #-1610612728	; 0xa0000008
d0012958:	0b01f812 	bleq	0xd00909a8
d001295c:	d0f92820 	rscsle	r2, r9, r0, lsr #16
d0012960:	d0f72809 	rscsle	r2, r7, r9, lsl #16
d0012964:	b99a6da2 	ldmiblt	sl, {r1, r5, r7, r8, sl, fp, sp, lr}
d0012968:	24f4f8df 	ldrbtcs	pc, [r4], #2271	; 0x8df	; <UNPREDICTABLE>
d001296c:	e006447a 	and	r4, r6, sl, ror r4
d0012970:	e7e44602 	strb	r4, [r4, r2, lsl #12]!
d0012974:	b95a6da2 	ldmdblt	sl, {r1, r5, r7, r8, sl, fp, sp, lr}^
d0012978:	24e8f8df 	strbtcs	pc, [r8], #2271	; 0x8df	; <UNPREDICTABLE>
d001297c:	e9c4447a 	stmib	r4, {r1, r3, r4, r5, r6, sl, lr}^
d0012980:	9a082516 	bls	0xd021bde0
d0012984:	2a18e9c4 	bcs	0xd064d09c
d0012988:	66a29a09 	strtvs	r9, [r2], r9, lsl #20
d001298c:	d1e9e000 	mvnle	lr, r0
d0012990:	42be4666 	adcsmi	r4, lr, #106954752	; 0x6600000
d0012994:	f816d906 			; <UNDEFINED> instruction: 0xf816d906
d0012998:	1e712c01 	cdpne	12, 7, cr2, cr1, cr1, {0}
d001299c:	d0242a20 	eorle	r2, r4, r0, lsr #20
d00129a0:	d0222a09 	eorle	r2, r2, r9, lsl #20
d00129a4:	93114620 	tstls	r1, #32, 12	; 0x2000000
d00129a8:	fca8f7fd 	stc2	7, cr15, [r8], #1012	; 0x3f4
d00129ac:	46809b0c 	strmi	r9, [r0], ip, lsl #22
d00129b0:	000bea43 	andeq	lr, fp, r3, asr #20
d00129b4:	43039b0d 	movwmi	r9, #15117	; 0x3b0d
d00129b8:	f0009b11 			; <UNDEFINED> instruction: 0xf0009b11
d00129bc:	f24d8090 	vqadd.s8	d24, d29, d0
d00129c0:	58e3030c 	stmiapl	r3!, {r2, r3, r8, r9}^
d00129c4:	d1122b20 	tstle	r2, r0, lsr #22
d00129c8:	2b006da3 	blcs	0xd002e05c
d00129cc:	af7bf47f 	svcge	0x007bf47f
d00129d0:	3494f8df 	ldrcc	pc, [r4], #2271	; 0x8df
d00129d4:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d00129d8:	9b083516 	blls	0xd021fe38
d00129dc:	3a18e9c4 	bcc	0xd064d0f4
d00129e0:	66a39b09 	strtvs	r9, [r3], r9, lsl #22
d00129e4:	4694e76f 	ldrmi	lr, [r4], pc, ror #14
d00129e8:	460ee798 			; <UNDEFINED> instruction: 0x460ee798
d00129ec:	f1b8e7d1 			; <UNDEFINED> instruction: 0xf1b8e7d1
d00129f0:	d0720f00 	rsbsle	r0, r2, r0, lsl #30
d00129f4:	d0542800 	subsle	r2, r4, r0, lsl #16
d00129f8:	d00542be 			; <UNDEFINED> instruction: 0xd00542be
d00129fc:	9a109b0f 	bls	0xd0439640
d0012a00:	f7fd5c98 			; <UNDEFINED> instruction: 0xf7fd5c98
d0012a04:	b958fd12 	ldmdblt	r8, {r1, r4, r8, sl, fp, ip, sp, lr, pc}^
d0012a08:	b94b6da3 	stmdblt	fp, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0012a0c:	345cf8df 	ldrbcc	pc, [ip], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d0012a10:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0012a14:	9b083516 	blls	0xd021fe74
d0012a18:	3a18e9c4 	bcc	0xd064d130
d0012a1c:	66a39b09 	strtvs	r9, [r3], r9, lsl #22
d0012a20:	454e46b9 	strbmi	r4, [lr, #-1721]	; 0xfffff947
d0012a24:	d917464a 	ldmdble	r7, {r1, r3, r6, r9, sl, lr}
d0012a28:	f1097811 			; <UNDEFINED> instruction: 0xf1097811
d0012a2c:	46080901 	strmi	r0, [r8], -r1, lsl #18
d0012a30:	fcfbf7fd 	ldc2l	7, cr15, [fp], #1012	; 0x3f4
d0012a34:	d1f42800 	mvnsle	r2, r0, lsl #16
d0012a38:	29093930 	stmdbcs	r9, {r4, r5, r8, fp, ip, sp}
d0012a3c:	6da3d9f1 			; <UNDEFINED> instruction: 0x6da3d9f1
d0012a40:	f8dfb95b 			; <UNDEFINED> instruction: 0xf8dfb95b
d0012a44:	447b342c 	ldrbtmi	r3, [fp], #-1068	; 0xfffffbd4
d0012a48:	3516e9c4 	ldrcc	lr, [r6, #-2500]	; 0xfffff63c
d0012a4c:	e9c49b08 	stmib	r4, {r3, r8, r9, fp, ip, pc}^
d0012a50:	9b093a18 	blls	0xd02612b8
d0012a54:	e00066a3 	and	r6, r0, r3, lsr #13
d0012a58:	1bd2d1f1 	blne	0xcf4c7224
d0012a5c:	46204639 			; <UNDEFINED> instruction: 0x46204639
d0012a60:	fcc1f7fd 	stc2l	7, cr15, [r1], {253}	; 0xfd
d0012a64:	0f00f1bb 	svceq	0x0000f1bb
d0012a68:	43c0d100 	bicmi	sp, r0, #0, 2
d0012a6c:	f24d0fc0 	vmax.f32	q8, <illegal reg q14.5>, q0
d0012a70:	f1b8030c 			; <UNDEFINED> instruction: 0xf1b8030c
d0012a74:	58e10f00 	stmiapl	r1!, {r8, r9, sl, fp}^
d0012a78:	2000bf08 	andcs	fp, r0, r8, lsl #30
d0012a7c:	50e21c4a 	rscpl	r1, r2, sl, asr #24
d0012a80:	0481eb04 	streq	lr, [r1], #2820	; 0xb04
d0012a84:	738cf64c 	orrvc	pc, ip, #76, 12	; 0x4c00000
d0012a88:	f8042200 			; <UNDEFINED> instruction: 0xf8042200
d0012a8c:	f64c8003 			; <UNDEFINED> instruction: 0xf64c8003
d0012a90:	54e0738d 	strbtpl	r7, [r0], #909	; 0x38d
d0012a94:	738ef64c 	orrvc	pc, lr, #76, 12	; 0x4c00000
d0012a98:	f64c54e0 			; <UNDEFINED> instruction: 0xf64c54e0
d0012a9c:	54e2738f 	strbtpl	r7, [r2], #911	; 0x38f
d0012aa0:	2200e711 	andcs	lr, r0, #4456448	; 0x440000
d0012aa4:	96062300 	strls	r2, [r6], -r0, lsl #6
d0012aa8:	9705ae29 	strls	sl, [r5, -r9, lsr #28]
d0012aac:	e9cd466d 	stmib	sp, {r0, r2, r3, r5, r6, r9, sl, lr}^
d0012ab0:	ab122312 	blge	0xd049b700
d0012ab4:	ce0f9307 	cdpgt	3, 0, cr9, cr15, cr7, {0}
d0012ab8:	6833c50f 	ldmdavs	r3!, {r0, r1, r2, r3, r8, sl, lr, pc}
d0012abc:	602b4620 	eorvs	r4, fp, r0, lsr #12
d0012ac0:	cb0eab26 	blgt	0xd03bd760
d0012ac4:	fb62f7fe 	blx	0xd18d0ac6
d0012ac8:	d0d02800 	sbcsle	r2, r0, r0, lsl #16
d0012acc:	2312e9dd 	tstcs	r2, #3620864	; 0x374000
d0012ad0:	bf144313 	svclt	0x00144313
d0012ad4:	20002001 	andcs	r2, r0, r1
d0012ad8:	4640e7c9 	strbmi	lr, [r0], -r9, asr #15
d0012adc:	9a0ee7c7 	bls	0xd03cca00
d0012ae0:	0002ea49 	andeq	lr, r2, r9, asr #20
d0012ae4:	0203ea50 	andeq	lr, r3, #80, 20	; 0x50000
d0012ae8:	80a2f000 	adchi	pc, r2, r0
d0012aec:	21fcf8d4 	ldrsbcs	pc, [ip, #132]!	; 0x84	; <UNPREDICTABLE>
d0012af0:	eb04b112 	bl	0xd013ef40
d0012af4:	6f921242 	svcvs	0x00921242
d0012af8:	010cf24d 	tsteq	ip, sp, asr #4	; <UNPREDICTABLE>
d0012afc:	42915861 	addsmi	r5, r1, #6356992	; 0x610000
d0012b00:	6da3d806 	stcvs	8, cr13, [r3, #24]!
d0012b04:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0012b08:	4bdaaede 	blmi	0xcf6be688
d0012b0c:	e762447b 			; <UNDEFINED> instruction: 0xe762447b
d0012b10:	f1b91e4a 			; <UNDEFINED> instruction: 0xf1b91e4a
d0012b14:	d0100f00 	andsle	r0, r0, r0, lsl #30
d0012b18:	d00a42be 			; <UNDEFINED> instruction: 0xd00a42be
d0012b1c:	b9436da3 	stmdblt	r3, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0012b20:	447b4bd5 	ldrbtmi	r4, [fp], #-3029	; 0xfffff42b
d0012b24:	3516e9c4 	ldrcc	lr, [r6, #-2500]	; 0xfffff63c
d0012b28:	e9c49b08 	stmib	r4, {r3, r8, r9, fp, ip, pc}^
d0012b2c:	9b093a18 	blls	0xd0261394
d0012b30:	f24d66a3 	vmax.s8	d22, d29, d19
d0012b34:	50e2030c 	rscpl	r0, r2, ip, lsl #6
d0012b38:	ea4fe6c5 	b	0xd140c654
d0012b3c:	b3630881 	cmnlt	r3, #8454144	; 0x810000
d0012b40:	d10642be 			; <UNDEFINED> instruction: 0xd10642be
d0012b44:	534ff502 	movtpl	pc, #62722	; 0xf502	; <UNPREDICTABLE>
d0012b48:	eb043322 	bl	0xd011f7d8
d0012b4c:	79db0383 	ldmibvc	fp, {r0, r1, r7, r8, r9}^
d0012b50:	6da3b153 	stfvsd	f3, [r3, #332]!	; 0x14c
d0012b54:	4bc9b943 	blmi	0xcf281068
d0012b58:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0012b5c:	9b083516 	blls	0xd021ffbc
d0012b60:	3a18e9c4 	bcc	0xd064d278
d0012b64:	66a39b09 	strtvs	r9, [r3], r9, lsl #22
d0012b68:	f64c4444 			; <UNDEFINED> instruction: 0xf64c4444
d0012b6c:	5ce37388 	stclpl	3, cr7, [r3], #544	; 0x220
d0012b70:	f64cb13b 			; <UNDEFINED> instruction: 0xf64cb13b
d0012b74:	f814738a 			; <UNDEFINED> instruction: 0xf814738a
d0012b78:	fab99003 	blx	0xcee76b8c
d0012b7c:	ea4ff989 	b	0xd14111a8
d0012b80:	f64c1959 			; <UNDEFINED> instruction: 0xf64c1959
d0012b84:	f64c7389 			; <UNDEFINED> instruction: 0xf64c7389
d0012b88:	f804728a 			; <UNDEFINED> instruction: 0xf804728a
d0012b8c:	23019003 	movwcs	r9, #4099	; 0x1003
d0012b90:	f64c54a3 			; <UNDEFINED> instruction: 0xf64c54a3
d0012b94:	54a3728b 	strtpl	r7, [r3], #651	; 0x28b
d0012b98:	44a0e695 	strtmi	lr, [r0], #1685	; 0x695
d0012b9c:	738bf64c 	orrvc	pc, fp, #76, 12	; 0x4c00000
d0012ba0:	3003f818 	andcc	pc, r3, r8, lsl r8	; <UNPREDICTABLE>
d0012ba4:	6da3b153 	stfvsd	f3, [r3, #332]!	; 0x14c
d0012ba8:	4bb5b943 	blmi	0xced810bc
d0012bac:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0012bb0:	9b083516 	blls	0xd0220010
d0012bb4:	3a18e9c4 	bcc	0xd064d2cc
d0012bb8:	66a39b09 	strtvs	r9, [r3], r9, lsl #22
d0012bbc:	22002300 	andcs	r2, r0, #0, 6
d0012bc0:	2312e9cd 	tstcs	r2, #3358720	; 0x334000
d0012bc4:	7388f64c 	orrvc	pc, r8, #76, 12	; 0x4c00000
d0012bc8:	3003f818 	andcc	pc, r3, r8, lsl r8	; <UNPREDICTABLE>
d0012bcc:	f64cb923 			; <UNDEFINED> instruction: 0xf64cb923
d0012bd0:	f8087289 			; <UNDEFINED> instruction: 0xf8087289
d0012bd4:	e6763002 	ldrbt	r3, [r6], -r2
d0012bd8:	798af64c 	stmibvc	sl, {r2, r3, r6, r9, sl, ip, sp, lr, pc}
d0012bdc:	3009f818 	andcc	pc, r9, r8, lsl r8	; <UNPREDICTABLE>
d0012be0:	f64cb12b 			; <UNDEFINED> instruction: 0xf64cb12b
d0012be4:	22007389 	andcs	r7, r0, #603979778	; 0x24000002
d0012be8:	2003f808 	andcs	pc, r3, r8, lsl #16
d0012bec:	9606e66b 	strls	lr, [r6], -fp, ror #12
d0012bf0:	ae29ab12 	vmovge.32	d9[1], sl
d0012bf4:	93079705 	movwls	r9, #30469	; 0x7705
d0012bf8:	ce0f466d 	cfmadd32gt	mvax3, mvfx4, mvfx15, mvfx13
d0012bfc:	6833c50f 	ldmdavs	r3!, {r0, r1, r2, r3, r8, sl, lr, pc}
d0012c00:	602b4620 	eorvs	r4, fp, r0, lsr #12
d0012c04:	cb0eab26 	blgt	0xd03bd8a4
d0012c08:	fac0f7fe 	blx	0xcf050c08
d0012c0c:	2312e9dd 	tstcs	r2, #3620864	; 0x374000
d0012c10:	0103ea52 	tsteq	r3, r2, asr sl
d0012c14:	7189f64c 	orrvc	pc, r9, ip, asr #12
d0012c18:	2001bf14 	andcs	fp, r1, r4, lsl pc
d0012c1c:	43132000 	tstmi	r3, #0
d0012c20:	0001f808 	andeq	pc, r1, r8, lsl #16
d0012c24:	ae4ff43f 	mcrge	4, 2, pc, cr15, cr15, {1}	; <UNPREDICTABLE>
d0012c28:	f8082301 			; <UNDEFINED> instruction: 0xf8082301
d0012c2c:	e64a3009 	strb	r3, [sl], -r9
d0012c30:	0f00f1b8 	svceq	0x0000f1b8
d0012c34:	ae47f43f 	mcrge	4, 2, pc, cr7, cr15, {1}	; <UNPREDICTABLE>
d0012c38:	9a0a9b0b 	bls	0xd02b986c
d0012c3c:	f43f4313 			; <UNDEFINED> instruction: 0xf43f4313
d0012c40:	42beae42 	adcsmi	sl, lr, #1056	; 0x420
d0012c44:	9b0fd023 	blls	0xd0406cd8
d0012c48:	5c989a10 	vldmiapl	r8, {s18-s33}
d0012c4c:	fbedf7fd 	blx	0xcfb90c4a
d0012c50:	46b8b1e8 	ldrtmi	fp, [r8], r8, ror #3
d0012c54:	46434546 	strbmi	r4, [r3], -r6, asr #10
d0012c58:	4642d90d 	strbmi	sp, [r2], -sp, lsl #18
d0012c5c:	802cf8cd 	eorhi	pc, ip, sp, asr #17
d0012c60:	1b01f812 	blne	0xd0090cb0
d0012c64:	f7fd4608 			; <UNDEFINED> instruction: 0xf7fd4608
d0012c68:	b9b8fbe0 	ldmiblt	r8!, {r5, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d0012c6c:	0030f1a1 	eorseq	pc, r0, r1, lsr #3
d0012c70:	28099b0b 	stmdacs	r9, {r0, r1, r3, r8, r9, fp, ip, pc}
d0012c74:	eba8d912 	bl	0xcea490c4
d0012c78:	f1bb0b07 			; <UNDEFINED> instruction: 0xf1bb0b07
d0012c7c:	d90f0f3f 	stmdble	pc, {r0, r1, r2, r3, r4, r5, r8, r9, sl, fp}	; <UNPREDICTABLE>
d0012c80:	2b006da3 	blcs	0xd002e314
d0012c84:	ae1ff47f 	mrcge	4, 0, APSR_nzcv, cr15, cr15, {3}
d0012c88:	447b4b7e 	ldrbtmi	r4, [fp], #-2942	; 0xfffff482
d0012c8c:	6da3e6a3 	stcvs	6, cr14, [r3, #652]!	; 0x28c
d0012c90:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0012c94:	4b7cae18 	blmi	0xd1f3e4fc
d0012c98:	e69c447b 			; <UNDEFINED> instruction: 0xe69c447b
d0012c9c:	e7d94690 	bfi	r4, r0, #13, #13
d0012ca0:	4639465a 			; <UNDEFINED> instruction: 0x4639465a
d0012ca4:	930b4620 	movwls	r4, #46624	; 0xb620
d0012ca8:	fb9df7fd 	blx	0xce790ca6
d0012cac:	46819a0a 	strmi	r9, [r1], sl, lsl #20
d0012cb0:	b34a9b0b 	movtlt	r9, #43787	; 0xab0b
d0012cb4:	d9114546 	ldmdble	r1, {r1, r2, r6, r8, sl, lr}
d0012cb8:	3b01f818 	blcc	0xd0090d20
d0012cbc:	d0f92b20 	rscsle	r2, r9, r0, lsr #22
d0012cc0:	d0f72b09 	rscsle	r2, r7, r9, lsl #22
d0012cc4:	b9536da3 	ldmdblt	r3, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0012cc8:	447b4b70 	ldrbtmi	r4, [fp], #-2928	; 0xfffff490
d0012ccc:	3516e9c4 	ldrcc	lr, [r6, #-2500]	; 0xfffff63c
d0012cd0:	e9c49b08 	stmib	r4, {r3, r8, r9, fp, ip, pc}^
d0012cd4:	9b093a18 	blls	0xd026153c
d0012cd8:	e00066a3 	and	r6, r0, r3, lsr #13
d0012cdc:	f1b9d1f2 			; <UNDEFINED> instruction: 0xf1b9d1f2
d0012ce0:	f6ff0f00 			; <UNDEFINED> instruction: 0xf6ff0f00
d0012ce4:	f64cadf0 			; <UNDEFINED> instruction: 0xf64cadf0
d0012ce8:	22487388 	subcs	r7, r8, #136, 6	; 0x20000002
d0012cec:	fb0258e1 	blx	0xd00a907a
d0012cf0:	39014009 	stmdbcc	r1, {r0, r3, lr}
d0012cf4:	f64a50e1 			; <UNDEFINED> instruction: 0xf64a50e1
d0012cf8:	fb023388 	blx	0xd009fb22
d0012cfc:	44184101 	ldrmi	r4, [r8], #-257	; 0xfffffeff
d0012d00:	f00e4419 			; <UNDEFINED> instruction: 0xf00e4419
d0012d04:	e5def909 	ldrb	pc, [lr, #2313]	; 0x909	; <UNPREDICTABLE>
d0012d08:	d9134546 	ldmdble	r3, {r1, r2, r6, r8, sl, lr}
d0012d0c:	3000f898 	mulcc	r0, r8, r8
d0012d10:	d1062b28 	tstle	r6, r8, lsr #22
d0012d14:	2b006da3 	blcs	0xd002e3a8
d0012d18:	add5f47f 	cfldrdge	mvd15, [r5, #508]	; 0x1fc
d0012d1c:	447b4b5c 	ldrbtmi	r4, [fp], #-2908	; 0xfffff4a4
d0012d20:	4546e659 	strbmi	lr, [r6, #-1625]	; 0xfffff9a7
d0012d24:	d0054643 	andle	r4, r5, r3, asr #12
d0012d28:	2b01f818 	blcs	0xd0090d90
d0012d2c:	d0f82a20 	rscsle	r2, r8, r0, lsr #20
d0012d30:	d0f62a09 	rscsle	r2, r6, r9, lsl #20
d0012d34:	21002001 	tstcs	r0, r1
d0012d38:	e9cd429e 	stmib	sp, {r1, r2, r3, r4, r7, r9, lr}^
d0012d3c:	d0130112 	andsle	r0, r3, r2, lsl r1
d0012d40:	aa129606 	bge	0xd04b8560
d0012d44:	9305ae29 	movwls	sl, #24105	; 0x5e29
d0012d48:	46ec9207 	strbtmi	r9, [ip], r7, lsl #4
d0012d4c:	e8acce0f 	stmia	ip!, {r0, r1, r2, r3, r9, sl, fp, lr, pc}
d0012d50:	6833000f 	ldmdavs	r3!, {r0, r1, r2, r3}
d0012d54:	f8cc4620 			; <UNDEFINED> instruction: 0xf8cc4620
d0012d58:	ab263000 	blge	0xd099ed60
d0012d5c:	f7fecb0e 			; <UNDEFINED> instruction: 0xf7fecb0e
d0012d60:	2800fa15 	stmdacs	r0, {r0, r2, r4, r9, fp, ip, sp, lr, pc}
d0012d64:	adaff43f 	cfstrsge	mvf15, [pc, #252]!	; 0xd0012e68
d0012d68:	0f00f1b9 	svceq	0x0000f1b9
d0012d6c:	f64cda0e 			; <UNDEFINED> instruction: 0xf64cda0e
d0012d70:	58e07388 	stmiapl	r0!, {r3, r7, r8, r9, ip, sp, lr}^
d0012d74:	d1062880 	smlabble	r6, r0, r8, r2
d0012d78:	2b006da3 	blcs	0xd002e40c
d0012d7c:	ada3f47f 	cfstrsge	mvf15, [r3, #508]!	; 0x1fc
d0012d80:	447b4b44 	ldrbtmi	r4, [fp], #-2884	; 0xfffff4bc
d0012d84:	1c42e627 	mcrrne	6, 2, lr, r2, cr7
d0012d88:	50e24681 	rscpl	r4, r2, r1, lsl #13
d0012d8c:	f64a2048 			; <UNDEFINED> instruction: 0xf64a2048
d0012d90:	465a3588 	ldrbmi	r3, [sl], -r8, lsl #11
d0012d94:	fb004639 	blx	0xd0024682
d0012d98:	eb09f909 	bl	0xd02911c4
d0012d9c:	44200005 	strtmi	r0, [r0], #-5
d0012da0:	f00e444c 			; <UNDEFINED> instruction: 0xf00e444c
d0012da4:	2300f8b9 	movwcs	pc, #2233	; 0x8b9	; <UNPREDICTABLE>
d0012da8:	f50444a3 			; <UNDEFINED> instruction: 0xf50444a3
d0012dac:	f80b442b 			; <UNDEFINED> instruction: 0xf80b442b
d0012db0:	e9dd3005 	ldmib	sp, {r0, r2, ip, sp}^
d0012db4:	e9c42312 	stmib	r4, {r1, r4, r8, r9, sp}^
d0012db8:	e5842332 	str	r2, [r4, #818]	; 0x332
d0012dbc:	f47f2a05 			; <UNDEFINED> instruction: 0xf47f2a05
d0012dc0:	4935abc2 	ldmdbmi	r5!, {r1, r6, r7, r8, r9, fp, sp, pc}
d0012dc4:	920b4638 	andls	r4, fp, #56, 12	; 0x3800000
d0012dc8:	447946cb 	ldrbtmi	r4, [r9], #-1739	; 0xfffff935
d0012dcc:	f00e46c8 			; <UNDEFINED> instruction: 0xf00e46c8
d0012dd0:	fab0f8b3 	blx	0xcec510a4
d0012dd4:	4931f380 	ldmdbmi	r1!, {r7, r8, r9, ip, sp, lr, pc}
d0012dd8:	095b4638 	ldmdbeq	fp, {r3, r4, r5, r9, sl, lr}^
d0012ddc:	44799a0b 	ldrbtmi	r9, [r9], #-2571	; 0xfffff5f5
d0012de0:	930a464e 	movwls	r4, #42574	; 0xa64e
d0012de4:	f8a8f00e 			; <UNDEFINED> instruction: 0xf8a8f00e
d0012de8:	f380fab0 			; <UNDEFINED> instruction: 0xf380fab0
d0012dec:	902cf8cd 	eorls	pc, ip, sp, asr #17
d0012df0:	930c095b 	movwls	r0, #51547	; 0xc95b
d0012df4:	2205492a 	andcs	r4, r5, #688128	; 0xa8000
d0012df8:	44794638 	ldrbtmi	r4, [r9], #-1592	; 0xfffff9c8
d0012dfc:	f89cf00e 			; <UNDEFINED> instruction: 0xf89cf00e
d0012e00:	fab02300 	blx	0xcec1ba08
d0012e04:	930ef980 	movwls	pc, #59776	; 0xe980	; <UNPREDICTABLE>
d0012e08:	1959ea4f 	ldmdbne	r9, {r0, r1, r2, r3, r6, r9, fp, sp, lr, pc}^
d0012e0c:	f7ff930d 			; <UNDEFINED> instruction: 0xf7ff930d
d0012e10:	bf00bbd5 	svclt	0x0000bbd5
d0012e14:	fffffc50 			; <UNDEFINED> instruction: 0xfffffc50
d0012e18:	fffffc10 			; <UNDEFINED> instruction: 0xfffffc10
d0012e1c:	fffffc07 			; <UNDEFINED> instruction: 0xfffffc07
d0012e20:	fffffbf8 			; <UNDEFINED> instruction: 0xfffffbf8
d0012e24:	fffffbd6 			; <UNDEFINED> instruction: 0xfffffbd6
d0012e28:	fffffbc5 			; <UNDEFINED> instruction: 0xfffffbc5
d0012e2c:	fffffb93 			; <UNDEFINED> instruction: 0xfffffb93
d0012e30:	fffffade 			; <UNDEFINED> instruction: 0xfffffade
d0012e34:	fffffb08 			; <UNDEFINED> instruction: 0xfffffb08
d0012e38:	fffffa8e 			; <UNDEFINED> instruction: 0xfffffa8e
d0012e3c:	fffffaaa 			; <UNDEFINED> instruction: 0xfffffaaa
d0012e40:	fffffa7f 			; <UNDEFINED> instruction: 0xfffffa7f
d0012e44:	fffffafc 			; <UNDEFINED> instruction: 0xfffffafc
d0012e48:	fffffa36 			; <UNDEFINED> instruction: 0xfffffa36
d0012e4c:	fffffa29 			; <UNDEFINED> instruction: 0xfffffa29
d0012e50:	fffff9e6 			; <UNDEFINED> instruction: 0xfffff9e6
d0012e54:	fffffa01 			; <UNDEFINED> instruction: 0xfffffa01
d0012e58:	fffff9c6 			; <UNDEFINED> instruction: 0xfffff9c6
d0012e5c:	fffff890 			; <UNDEFINED> instruction: 0xfffff890
d0012e60:	fffff925 			; <UNDEFINED> instruction: 0xfffff925
d0012e64:	fffff8ea 			; <UNDEFINED> instruction: 0xfffff8ea
d0012e68:	fffff8e5 			; <UNDEFINED> instruction: 0xfffff8e5
d0012e6c:	fffff8c8 			; <UNDEFINED> instruction: 0xfffff8c8
d0012e70:	fffff8bb 			; <UNDEFINED> instruction: 0xfffff8bb
d0012e74:	fffff81d 			; <UNDEFINED> instruction: 0xfffff81d
d0012e78:	fffff82f 			; <UNDEFINED> instruction: 0xfffff82f
d0012e7c:	fffff816 			; <UNDEFINED> instruction: 0xfffff816
d0012e80:	fffff7dd 			; <UNDEFINED> instruction: 0xfffff7dd
d0012e84:	fffff736 			; <UNDEFINED> instruction: 0xfffff736
d0012e88:	fffff703 			; <UNDEFINED> instruction: 0xfffff703
d0012e8c:	fffff717 			; <UNDEFINED> instruction: 0xfffff717
d0012e90:	fffff6e0 			; <UNDEFINED> instruction: 0xfffff6e0
d0012e94:	fffff6ab 			; <UNDEFINED> instruction: 0xfffff6ab
d0012e98:	fffff357 			; <UNDEFINED> instruction: 0xfffff357
d0012e9c:	fffff349 			; <UNDEFINED> instruction: 0xfffff349
d0012ea0:	fffff340 			; <UNDEFINED> instruction: 0xfffff340

Disassembly of section .text.advance:

d0012ea4 <.text.advance>:
d0012ea4:	f100b570 			; <UNDEFINED> instruction: 0xf100b570
d0012ea8:	46060538 			; <UNDEFINED> instruction: 0x46060538
d0012eac:	0418f100 	ldreq	pc, [r8], #-256	; 0xffffff00
d0012eb0:	cd0fb088 	stcgt	0, cr11, [pc, #-544]	; 0xd0012c98
d0012eb4:	e895c40f 	ldm	r5, {r0, r1, r2, r3, sl, lr, pc}
d0012eb8:	e884000f 	stm	r4, {r0, r1, r2, r3}
d0012ebc:	466c000f 	strbtmi	r0, [ip], -pc
d0012ec0:	f1064631 			; <UNDEFINED> instruction: 0xf1064631
d0012ec4:	46200538 			; <UNDEFINED> instruction: 0x46200538
d0012ec8:	fd5ef7fe 	ldc2l	7, cr15, [lr, #-1016]	; 0xfffffc08
d0012ecc:	c50fcc0f 	strgt	ip, [pc, #-3087]	; 0xd00122c5
d0012ed0:	000fe894 	muleq	pc, r4, r8	; <UNPREDICTABLE>
d0012ed4:	000fe885 	andeq	lr, pc, r5, lsl #17
d0012ed8:	b0084630 	andlt	r4, r8, r0, lsr r6
d0012edc:	4070e8bd 	ldrhtmi	lr, [r0], #-141	; 0xffffff73
d0012ee0:	b978f7fd 	ldmdblt	r8!, {r0, r2, r3, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}^

Disassembly of section .text.accept:

d0012ee4 <.text.accept>:
d0012ee4:	6d83b508 	cfstr32vs	mvfx11, [r3, #32]
d0012ee8:	6ac2b933 	bvs	0xcf0c13bc
d0012eec:	d105428a 	smlabble	r5, sl, r2, r4
d0012ef0:	ffd8f7ff 			; <UNDEFINED> instruction: 0xffd8f7ff
d0012ef4:	bd082001 	stclt	0, cr2, [r8, #-4]
d0012ef8:	e7fc2000 	ldrb	r2, [ip, r0]!
d0012efc:	e7fa4618 			; <UNDEFINED> instruction: 0xe7fa4618

Disassembly of section .text.expect:

d0012f00 <.text.expect>:
d0012f00:	4605b570 			; <UNDEFINED> instruction: 0x4605b570
d0012f04:	f7ff4616 			; <UNDEFINED> instruction: 0xf7ff4616
d0012f08:	4604ffed 	strmi	pc, [r4], -sp, ror #31
d0012f0c:	4631b928 	ldrtmi	fp, [r1], -r8, lsr #18
d0012f10:	f7fd4628 			; <UNDEFINED> instruction: 0xf7fd4628
d0012f14:	4620f99b 			; <UNDEFINED> instruction: 0x4620f99b
d0012f18:	2401bd70 	strcs	fp, [r1], #-3440	; 0xfffff290
d0012f1c:	Address 0x00000000d0012f1c is out of bounds.


Disassembly of section .text.enum_expression:

d0013014 <.text.enum_expression>:
d0013014:	e92d2a19 	push	{r0, r3, r4, r9, fp, sp}
d0013018:	46804ff8 			; <UNDEFINED> instruction: 0x46804ff8
d001301c:	4692468b 	ldrmi	r4, [r2], fp, lsl #13
d0013020:	4995d106 	ldmibmi	r5, {r1, r2, r8, ip, lr, pc}
d0013024:	f7fd4479 			; <UNDEFINED> instruction: 0xf7fd4479
d0013028:	2400f911 	strcs	pc, [r0], #-2321	; 0xfffff6ef
d001302c:	e0f82500 	rscs	r2, r8, r0, lsl #10
d0013030:	2e2b6ac6 	vnmulcs.f32	s12, s23, s12
d0013034:	2e2dd003 	cdpcs	0, 2, cr13, cr13, cr3, {0}
d0013038:	2e7ed001 	cdpcs	0, 7, cr13, cr14, cr1, {0}
d001303c:	4640d133 			; <UNDEFINED> instruction: 0x4640d133
d0013040:	ff30f7ff 			; <UNDEFINED> instruction: 0xff30f7ff
d0013044:	0201f10a 	andeq	pc, r1, #-2147483646	; 0x80000002
d0013048:	46402107 	strbmi	r2, [r0], -r7, lsl #2
d001304c:	ffe2f7ff 			; <UNDEFINED> instruction: 0xffe2f7ff
d0013050:	46042e2d 	strmi	r2, [r4], -sp, lsr #28
d0013054:	d11f460d 	tstle	pc, sp, lsl #12
d0013058:	eb614244 	bl	0xd1863970
d001305c:	f8d80541 			; <UNDEFINED> instruction: 0xf8d80541
d0013060:	2e006058 	mcrcs	0, 0, r6, cr0, cr8, {2}
d0013064:	80ddf040 	sbcshi	pc, sp, r0, asr #32
d0013068:	902cf8d8 	ldrdls	pc, [ip], -r8	; <UNPREDICTABLE>
d001306c:	0f5ef1b9 	svceq	0x005ef1b9
d0013070:	80ebf000 	rschi	pc, fp, r0
d0013074:	80d9f300 	sbcshi	pc, r9, r0, lsl #6
d0013078:	0325f1a9 	msreq	CPSR_sc, #1073741866	; 0x4000002a
d001307c:	f2002b0a 	vqdmulh.s<illegal width 8>	d2, d0, d10
d0013080:	2b0a80cd 	blcs	0xd02b33bc
d0013084:	80dff200 	sbcshi	pc, pc, r0, lsl #4
d0013088:	f003e8df 			; <UNDEFINED> instruction: 0xf003e8df
d001308c:	dddde1db 	ldflep	f6, [sp, #876]	; 0x36c
d0013090:	ddc7dbdd 	vstrle	d29, [r7, #884]	; 0x374
d0013094:	00dbddc7 	sbcseq	sp, fp, r7, asr #27
d0013098:	d1e02e7e 	mvnle	r2, lr, ror lr
d001309c:	43cb43c2 	bicmi	r4, fp, #134217731	; 0x8000003
d00130a0:	461d4614 			; <UNDEFINED> instruction: 0x461d4614
d00130a4:	2128e7db 	ldrdcs	lr, [r8, -fp]!
d00130a8:	ff1cf7ff 			; <UNDEFINED> instruction: 0xff1cf7ff
d00130ac:	f10ab170 			; <UNDEFINED> instruction: 0xf10ab170
d00130b0:	46400201 	strbmi	r0, [r0], -r1, lsl #4
d00130b4:	f7ff2101 			; <UNDEFINED> instruction: 0xf7ff2101
d00130b8:	4a70ffad 	bmi	0xd1c52f74
d00130bc:	460d4604 	strmi	r4, [sp], -r4, lsl #12
d00130c0:	2129447a 			; <UNDEFINED> instruction: 0x2129447a
d00130c4:	f7ff4640 			; <UNDEFINED> instruction: 0xf7ff4640
d00130c8:	e7c8ff1b 	bfi	pc, fp, (invalid: 30:8)	; <UNPREDICTABLE>
d00130cc:	302cf8d8 	ldrdcc	pc, [ip], -r8	; <UNPREDICTABLE>
d00130d0:	7281f5a3 	addvc	pc, r1, #683671552	; 0x28c00000
d00130d4:	d80a2a01 	stmdale	sl, {r0, r9, fp, sp}
d00130d8:	7f81f5b3 	svcvc	0x0081f5b3
d00130dc:	4020f8d8 	ldrdmi	pc, [r0], -r8	; <UNPREDICTABLE>
d00130e0:	bf0c4640 	svclt	0x000c4640
d00130e4:	250017e5 	strcs	r1, [r0, #-2021]	; 0xfffff81b
d00130e8:	fedcf7ff 	mrc2	7, 6, pc, cr12, cr15, {7}
d00130ec:	4964e7b7 	stmdbmi	r4!, {r0, r1, r2, r4, r5, r7, r8, r9, sl, sp, lr, pc}^
d00130f0:	46404479 			; <UNDEFINED> instruction: 0x46404479
d00130f4:	4640e797 			; <UNDEFINED> instruction: 0x4640e797
d00130f8:	fed4f7ff 	mrc2	7, 6, pc, cr4, cr15, {7}
d00130fc:	f10a1c71 			; <UNDEFINED> instruction: 0xf10a1c71
d0013100:	46400201 	strbmi	r0, [r0], -r1, lsl #4
d0013104:	ff86f7ff 			; <UNDEFINED> instruction: 0xff86f7ff
d0013108:	3058f8d8 	ldrsbcc	pc, [r8], #-136	; 0xffffff78	; <UNPREDICTABLE>
d001310c:	460f4606 	strmi	r4, [pc], -r6, lsl #12
d0013110:	d18a2b00 	orrle	r2, sl, r0, lsl #22
d0013114:	0f2ff1b9 	svceq	0x002ff1b9
d0013118:	80a7f000 	adchi	pc, r7, r0
d001311c:	0f25f1b9 	svceq	0x0025f1b9
d0013120:	ea56d115 	b	0xd15c757c
d0013124:	f0000307 			; <UNDEFINED> instruction: 0xf0000307
d0013128:	1c6b80a3 	stclne	0, cr8, [fp], #-652	; 0xfffffd74
d001312c:	f1b4bf08 			; <UNDEFINED> instruction: 0xf1b4bf08
d0013130:	d0044f00 	andle	r4, r4, r0, lsl #30
d0013134:	f3f6fb94 			; <UNDEFINED> instruction: 0xf3f6fb94
d0013138:	4416fb03 	ldrmi	pc, [r6], #-2819	; 0xfffff4fd
d001313c:	1c7be093 	ldclne	0, cr14, [fp], #-588	; 0xfffffdb4
d0013140:	f1b6bf08 			; <UNDEFINED> instruction: 0xf1b6bf08
d0013144:	d1023fff 	strdle	r3, [r2, -pc]
d0013148:	4479494e 	ldrbtmi	r4, [r9], #-2382	; 0xfffff6b2
d001314c:	f46fe7d1 	vld1.64	{d30}, [pc :64], r1
d0013150:	eb097093 	bl	0xd026f3a4
d0013154:	2b010300 	blcs	0xd0053d5c
d0013158:	2f00d806 	svccs	0x0000d806
d001315c:	2e20bf08 	cdpcs	15, 2, cr11, cr0, cr8, {0}
d0013160:	4949d32c 	stmdbmi	r9, {r2, r3, r5, r8, r9, ip, lr, pc}^
d0013164:	e7c44479 			; <UNDEFINED> instruction: 0xe7c44479
d0013168:	0f5ef1b9 	svceq	0x005ef1b9
d001316c:	dc29d04b 	stcle	0, cr13, [r9], #-300	; 0xfffffed4
d0013170:	0925f1a9 	stmdbeq	r5!, {r0, r3, r5, r7, r8, ip, sp, lr, pc}
d0013174:	0f0af1b9 	svceq	0x000af1b9
d0013178:	af71f63f 	svcge	0x0071f63f
d001317c:	0f0af1b9 	svceq	0x000af1b9
d0013180:	af6df63f 	svcge	0x006df63f
d0013184:	f853a302 			; <UNDEFINED> instruction: 0xf853a302
d0013188:	44132029 	ldrmi	r2, [r3], #-41	; 0xffffffd7
d001318c:	bf004718 	svclt	0x00004718
d0013190:	ffffffa5 			; <UNDEFINED> instruction: 0xffffffa5
d0013194:	0000006d 	andeq	r0, r0, sp, rrx
d0013198:	fffffecf 			; <UNDEFINED> instruction: 0xfffffecf
d001319c:	fffffecf 			; <UNDEFINED> instruction: 0xfffffecf
d00131a0:	fffffecf 			; <UNDEFINED> instruction: 0xfffffecf
d00131a4:	0000005d 	andeq	r0, r0, sp, asr r0
d00131a8:	0000004d 	andeq	r0, r0, sp, asr #32
d00131ac:	fffffecf 			; <UNDEFINED> instruction: 0xfffffecf
d00131b0:	00000055 	andeq	r0, r0, r5, asr r0
d00131b4:	fffffecf 			; <UNDEFINED> instruction: 0xfffffecf
d00131b8:	000000d3 	ldrdeq	r0, [r0], -r3
d00131bc:	1327f240 	msrne	CPSR_sxc, #64, 4
d00131c0:	d0254599 	mlale	r5, r9, r5, r4
d00131c4:	7f94f5b9 	svcvc	0x0094f5b9
d00131c8:	f1b9d025 			; <UNDEFINED> instruction: 0xf1b9d025
d00131cc:	f47f0f7c 			; <UNDEFINED> instruction: 0xf47f0f7c
d00131d0:	ea44af46 	b	0xd113eef0
d00131d4:	ea450206 	b	0xd11539f4
d00131d8:	e7610307 	strb	r0, [r1, -r7, lsl #6]!
d00131dc:	eb4719a4 	bl	0xd11d9874
d00131e0:	e73c0505 	ldr	r0, [ip, -r5, lsl #10]!
d00131e4:	eb651ba4 	bl	0xd195a07c
d00131e8:	e7380507 	ldr	r0, [r8, -r7, lsl #10]!
d00131ec:	f307fb04 	vqrdmulh.s<illegal width 8>	d15, d7, d4
d00131f0:	3305fb06 	movwcc	pc, #23302	; 0x5b06	; <UNPREDICTABLE>
d00131f4:	4506fba4 	strmi	pc, [r6, #-2980]	; 0xfffff45c
d00131f8:	e730441d 			; <UNDEFINED> instruction: 0xe730441d
d00131fc:	0206ea04 	andeq	lr, r6, #4, 20	; 0x4000
d0013200:	0307ea05 	movweq	lr, #31237	; 0x7a05
d0013204:	ea84e74c 	b	0xce14cf3c
d0013208:	ea850206 	b	0xce153a28
d001320c:	e7470307 	strb	r0, [r7, -r7, lsl #6]
d0013210:	250040b4 	strcs	r4, [r0, #-180]	; 0xffffff4c
d0013214:	40f4e723 	rscsmi	lr, r4, r3, lsr #14
d0013218:	2605e7fb 			; <UNDEFINED> instruction: 0x2605e7fb
d001321c:	f77f45b3 			; <UNDEFINED> instruction: 0xf77f45b3
d0013220:	4620af6a 	strtmi	sl, [r0], -sl, ror #30
d0013224:	e8bd4629 	pop	{r0, r3, r5, r9, sl, lr}
d0013228:	f1b98ff8 			; <UNDEFINED> instruction: 0xf1b98ff8
d001322c:	d0100f7c 	andsle	r0, r0, ip, ror pc
d0013230:	7193f46f 	orrsvc	pc, r3, pc, ror #8
d0013234:	0301eb09 	movweq	lr, #6921	; 0x1b09
d0013238:	bf342b02 	svclt	0x00342b02
d001323c:	26002604 	strcs	r2, [r0], -r4, lsl #12
d0013240:	2606e7ec 	strcs	lr, [r6], -ip, ror #15
d0013244:	2600e7ea 	strcs	lr, [r0], -sl, ror #15
d0013248:	2602e7e8 	strcs	lr, [r2], -r8, ror #15
d001324c:	2603e7e6 	strcs	lr, [r3], -r6, ror #15
d0013250:	2601e7e4 	strcs	lr, [r1], -r4, ror #15
d0013254:	1c6ae7e2 	stclne	7, cr14, [sl], #-904	; 0xfffffc78
d0013258:	f1b4bf08 			; <UNDEFINED> instruction: 0xf1b4bf08
d001325c:	f43f4f00 			; <UNDEFINED> instruction: 0xf43f4f00
d0013260:	fb94af6e 	blx	0xce53f022
d0013264:	17e5f4f6 			; <UNDEFINED> instruction: 0x17e5f4f6
d0013268:	ea56e6f9 	b	0xd15cce54
d001326c:	d1f20307 	mvnsle	r0, r7, lsl #6
d0013270:	44794906 	ldrbtmi	r4, [r9], #-2310	; 0xfffff6fa
d0013274:	bf00e73d 	svclt	0x0000e73d
d0013278:	fffffef6 			; <UNDEFINED> instruction: 0xfffffef6
d001327c:	fffffe7b 			; <UNDEFINED> instruction: 0xfffffe7b
d0013280:	fffffe74 			; <UNDEFINED> instruction: 0xfffffe74
d0013284:	fffffe78 			; <UNDEFINED> instruction: 0xfffffe78
d0013288:	fffffe81 			; <UNDEFINED> instruction: 0xfffffe81
d001328c:	fffffd2b 			; <UNDEFINED> instruction: 0xfffffd2b

Disassembly of section .text.record_type:

d00132f8 <.text.record_type>:
d00132f8:	4ff7e92d 	svcmi	0x00f7e92d
d00132fc:	6ac6460d 	bvs	0xcf1a4b38
d0013300:	718bf46f 	orrvc	pc, fp, pc, ror #8
d0013304:	18734604 	ldmdane	r3!, {r2, r9, sl, lr}^
d0013308:	d8362b01 	ldmdale	r6!, {r0, r8, r9, fp, sp}
d001330c:	fdcaf7ff 	stc2l	7, cr15, [sl, #1020]	; 0x3fc
d0013310:	6b634a26 	blvs	0xd18e5bb0
d0013314:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d0013318:	4620447a 			; <UNDEFINED> instruction: 0x4620447a
d001331c:	9024f8d4 	ldrdls	pc, [r4], -r4	; <UNPREDICTABLE>
d0013320:	8028f8d4 	ldrdhi	pc, [r8], -r4	; <UNPREDICTABLE>
d0013324:	7030f894 	mlasvc	r0, r4, r8, pc	; <UNPREDICTABLE>
d0013328:	e9d49301 	ldmib	r4, {r0, r8, r9, ip, pc}^
d001332c:	f7ffab06 			; <UNDEFINED> instruction: 0xf7ffab06
d0013330:	b918fde7 	ldmdblt	r8, {r0, r1, r2, r5, r6, r7, r8, sl, fp, ip, sp, lr, pc}
d0013334:	b0032000 	andlt	r2, r3, r0
d0013338:	8ff0e8bd 	svchi	0x00f0e8bd
d001333c:	728cf5a6 	addvc	pc, ip, #696254464	; 0x29800000
d0013340:	46204651 			; <UNDEFINED> instruction: 0x46204651
d0013344:	41534253 	cmpmi	r3, r3, asr r2
d0013348:	f7fd465a 			; <UNDEFINED> instruction: 0xf7fd465a
d001334c:	2800f9c7 	stmdacs	r0, {r0, r1, r2, r6, r7, r8, fp, ip, sp, lr, pc}
d0013350:	f5b6da11 			; <UNDEFINED> instruction: 0xf5b6da11
d0013354:	d00b7f8c 	andle	r7, fp, ip, lsl #31
d0013358:	447b4b15 	ldrbtmi	r4, [fp], #-2837	; 0xfffff4eb
d001335c:	b92a6da2 	stmdblt	sl!, {r1, r5, r7, r8, sl, fp, sp, lr}
d0013360:	3916e9c4 	ldmdbcc	r6, {r2, r6, r7, r8, fp, sp, lr, pc}
d0013364:	e9c49b01 	stmib	r4, {r0, r8, r9, fp, ip, pc}^
d0013368:	66a38718 	ssatvs	r8, #4, r8, lsl #14
d001336c:	e7e22001 	strb	r2, [r2, r1]!
d0013370:	447b4b10 	ldrbtmi	r4, [fp], #-2832	; 0xfffff4f0
d0013374:	6028e7f2 	strdvs	lr, [r8], -r2	; <UNPREDICTABLE>
d0013378:	f240e7f8 	vaba.s8	q15, q8, q12
d001337c:	429e1301 	addsmi	r1, lr, #67108864	; 0x4000000
d0013380:	69c2d1d8 	stmibvs	r2, {r3, r4, r6, r7, r8, ip, lr, pc}^
d0013384:	f7fd6981 			; <UNDEFINED> instruction: 0xf7fd6981
d0013388:	2800fa56 	stmdacs	r0, {r1, r2, r4, r6, r9, fp, ip, sp, lr, pc}
d001338c:	2324dbd2 			; <UNDEFINED> instruction: 0x2324dbd2
d0013390:	4000fb03 	andmi	pc, r0, r3, lsl #22
d0013394:	3075f500 	rsbscc	pc, r5, r0, lsl #10
d0013398:	33acf890 			; <UNDEFINED> instruction: 0x33acf890
d001339c:	d0c92bff 	strdle	r2, [r9], #191	; 0xbf
d00133a0:	602b4620 	eorvs	r4, fp, r0, lsr #12
d00133a4:	fd7ef7ff 	ldc2l	7, cr15, [lr, #-1020]!	; 0xfffffc04
d00133a8:	bf00e7e0 	svclt	0x0000e7e0
d00133ac:	ffffffbd 			; <UNDEFINED> instruction: 0xffffffbd
d00133b0:	ffffff56 			; <UNDEFINED> instruction: 0xffffff56
d00133b4:	ffffff1a 			; <UNDEFINED> instruction: 0xffffff1a

Disassembly of section .text.enum_declaration:

d00134e4 <.text.enum_declaration>:
d00134e4:	f2404ac4 	vpmax.s8	q10, q8, q2
d00134e8:	e92d111b 	push	{r0, r1, r3, r4, r8, ip}
d00134ec:	447a4ff0 	ldrbtmi	r4, [sl], #-4080	; 0xfffff010
d00134f0:	ed2d4604 	stc	6, cr4, [sp, #-16]!
d00134f4:	b0978b02 	addslt	r8, r7, r2, lsl #22
d00134f8:	fd02f7ff 	stc2	7, cr15, [r2, #-1020]	; 0xfffffc04
d00134fc:	28004605 	stmdacs	r0, {r0, r2, r9, sl, lr}
d0013500:	af06d05a 	svcge	0x0006d05a
d0013504:	21002220 	tstcs	r0, r0, lsr #4
d0013508:	f00d4638 			; <UNDEFINED> instruction: 0xf00d4638
d001350c:	f8d4fcf7 			; <UNDEFINED> instruction: 0xf8d4fcf7
d0013510:	f240a02c 	vhadd.s8	d26, d0, d28
d0013514:	459a1301 	ldrmi	r1, [sl, #769]	; 0x301
d0013518:	f104d137 			; <UNDEFINED> instruction: 0xf104d137
d001351c:	463d0618 			; <UNDEFINED> instruction: 0x463d0618
d0013520:	c50fce0f 	strgt	ip, [pc, #-3599]	; 0xd0012719
d0013524:	000fe896 	muleq	pc, r6, r8	; <UNPREDICTABLE>
d0013528:	000fe885 	andeq	lr, pc, r5, lsl #17
d001352c:	46206a63 	strtmi	r6, [r0], -r3, ror #20
d0013530:	93026b66 	movwls	r6, #11110	; 0x2b66
d0013534:	93036aa3 	movwls	r6, #15011	; 0x3aa3
d0013538:	3030f894 	mlascc	r0, r4, r8, pc	; <UNPREDICTABLE>
d001353c:	8906e9d4 	stmdbhi	r6, {r2, r4, r6, r7, r8, fp, sp, lr, pc}
d0013540:	f7ff9301 			; <UNDEFINED> instruction: 0xf7ff9301
d0013544:	217bfcaf 	cmncs	fp, pc, lsr #25	; <UNPREDICTABLE>
d0013548:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d001354c:	f240fccb 	sha1c.32	<illegal reg q15.5>, q8, <illegal reg q5.5>
d0013550:	46051301 	strmi	r1, [r5], -r1, lsl #6
d0013554:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d0013558:	459a8121 	ldrmi	r8, [sl, #289]	; 0x121
d001355c:	f504d161 			; <UNDEFINED> instruction: 0xf504d161
d0013560:	f04f357e 			; <UNDEFINED> instruction: 0xf04f357e
d0013564:	f5040a00 			; <UNDEFINED> instruction: 0xf5040a00
d0013568:	f5053b7f 			; <UNDEFINED> instruction: 0xf5053b7f
d001356c:	f8db75ca 			; <UNDEFINED> instruction: 0xf8db75ca
d0013570:	f50b3214 			; <UNDEFINED> instruction: 0xf50b3214
d0013574:	459a7205 	ldrmi	r7, [sl, #517]	; 0x205
d0013578:	2b20d30f 	blcs	0xd08481bc
d001357c:	499fd131 	ldmibmi	pc, {r0, r4, r5, r8, ip, lr, pc}	; <UNPREDICTABLE>
d0013580:	46204479 			; <UNDEFINED> instruction: 0x46204479
d0013584:	fe62f7fc 	mcr2	7, 3, pc, cr2, cr12, {7}	; <UNPREDICTABLE>
d0013588:	2600e015 			; <UNDEFINED> instruction: 0x2600e015
d001358c:	46b146b2 			; <UNDEFINED> instruction: 0x46b146b2
d0013590:	960146b0 			; <UNDEFINED> instruction: 0x960146b0
d0013594:	96029603 	strls	r9, [r2], -r3, lsl #12
d0013598:	f895e7d5 			; <UNDEFINED> instruction: 0xf895e7d5
d001359c:	7a232020 	bvc	0xd08db624
d00135a0:	d11a429a 			; <UNDEFINED> instruction: 0xd11a429a
d00135a4:	4642464b 	strbmi	r4, [r2], -fp, asr #12
d00135a8:	0100e9d5 	ldrdeq	lr, [r0, -r5]
d00135ac:	f888f7fd 			; <UNDEFINED> instruction: 0xf888f7fd
d00135b0:	6da5b198 	stfvsd	f3, [r5, #608]!	; 0x260
d00135b4:	2500b135 	strcs	fp, [r0, #-309]	; 0xfffffecb
d00135b8:	b0174628 	andslt	r4, r7, r8, lsr #12
d00135bc:	8b02ecbd 	blhi	0xd00ce8b8
d00135c0:	8ff0e8bd 	svchi	0x00f0e8bd
d00135c4:	447b4b8e 	ldrbtmi	r4, [fp], #-2958	; 0xfffff472
d00135c8:	9b0265a3 	blls	0xd00acc5c
d00135cc:	65e366a6 	strbvs	r6, [r3, #1702]!	; 0x6a6
d00135d0:	66239b03 	strtvs	r9, [r3], -r3, lsl #22
d00135d4:	66639b01 	strbtvs	r9, [r3], -r1, lsl #22
d00135d8:	f10ae7ee 			; <UNDEFINED> instruction: 0xf10ae7ee
d00135dc:	35240a01 	strcc	r0, [r4, #-2561]!	; 0xfffff5ff
d00135e0:	1c59e7c5 	mrrcne	7, 12, lr, r9, cr5
d00135e4:	0c24f04f 	stceq	0, cr15, [r4], #-316	; 0xfffffec4
d00135e8:	6011960d 	andsvs	r9, r1, sp, lsl #12
d00135ec:	fb0c9a02 	blx	0xd0339dfe
d00135f0:	7a254303 	bvc	0xd0964204
d00135f4:	f5039209 			; <UNDEFINED> instruction: 0xf5039209
d00135f8:	9a033c7e 	bls	0xd00e27f8
d00135fc:	76caf50c 	strbvc	pc, [sl], ip, lsl #10	; <UNPREDICTABLE>
d0013600:	f240920a 	vhsub.s8	d25, d0, d10
d0013604:	920b1201 	andls	r1, fp, #268435456	; 0x10000000
d0013608:	e9cd9a01 	stmib	sp, {r0, r9, fp, ip, pc}^
d001360c:	f88d8906 			; <UNDEFINED> instruction: 0xf88d8906
d0013610:	cf0f2030 	svcgt	0x000f2030
d0013614:	e897c60f 	ldm	r7, {r0, r1, r2, r3, r9, sl, lr, pc}
d0013618:	e886000f 	stm	r6, {r0, r1, r2, r3}
d001361c:	f88c000f 			; <UNDEFINED> instruction: 0xf88c000f
d0013620:	4b7851b4 	blmi	0xd1e27cf8
d0013624:	35fff04f 	ldrbcc	pc, [pc, #79]!	; 0xd001367b	; <UNPREDICTABLE>
d0013628:	0b00f04f 	bleq	0xd004f76c
d001362c:	462e447b 			; <UNDEFINED> instruction: 0x462e447b
d0013630:	3a10ee08 	bcc	0xd044ee58
d0013634:	93036da3 	movwls	r6, #15779	; 0x3da3
d0013638:	f0402b00 			; <UNDEFINED> instruction: 0xf0402b00
d001363c:	6ae3809e 	bvs	0xcf8f38bc
d0013640:	f0002b7d 			; <UNDEFINED> instruction: 0xf0002b7d
d0013644:	f5b3809a 			; <UNDEFINED> instruction: 0xf5b3809a
d0013648:	f0007f80 			; <UNDEFINED> instruction: 0xf0007f80
d001364c:	f1048096 			; <UNDEFINED> instruction: 0xf1048096
d0013650:	af0e0c18 	svcge	0x000e0c18
d0013654:	8030f894 	mlashi	r0, r4, r8, pc	; <UNPREDICTABLE>
d0013658:	000fe8bc 			; <UNDEFINED> instruction: 0x000fe8bc
d001365c:	e89cc70f 	ldm	ip, {r0, r1, r2, r3, r8, r9, sl, lr, pc}
d0013660:	e887000f 	stm	r7, {r0, r1, r2, r3}
d0013664:	6a63000f 	bvs	0xd18d36a8
d0013668:	2a10ee18 	bcs	0xd044eed0
d001366c:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d0013670:	93014620 	movwls	r4, #5664	; 0x1620
d0013674:	6b676aa3 	blvs	0xd19ee108
d0013678:	e9d49302 	ldmib	r4, {r1, r8, r9, ip, pc}^
d001367c:	f7ffa906 			; <UNDEFINED> instruction: 0xf7ffa906
d0013680:	2800fc3f 	stmdacs	r0, {r0, r1, r2, r3, r4, r5, sl, fp, ip, sp, lr, pc}
d0013684:	464ad097 			; <UNDEFINED> instruction: 0x464ad097
d0013688:	46204651 			; <UNDEFINED> instruction: 0x46204651
d001368c:	fe66f7fc 	mcr2	7, 3, pc, cr6, cr12, {7}	; <UNPREDICTABLE>
d0013690:	db0c2800 	blle	0xd031d698
d0013694:	2b006da3 	blcs	0xd002ed28
d0013698:	4b5bd18d 	blmi	0xd1707cd4
d001369c:	65a3447b 	strvs	r4, [r3, #1147]!	; 0x47b
d00136a0:	66a79b01 	strtvs	r9, [r7], r1, lsl #22
d00136a4:	9b0265e3 	blls	0xd00ace38
d00136a8:	3818e9c4 	ldmdacc	r8, {r2, r6, r7, r8, fp, sp, lr, pc}
d00136ac:	464ae783 	strbmi	lr, [sl], -r3, lsl #15
d00136b0:	46204651 			; <UNDEFINED> instruction: 0x46204651
d00136b4:	f8bff7fd 			; <UNDEFINED> instruction: 0xf8bff7fd
d00136b8:	daeb2800 	ble	0xcfadd6c0
d00136bc:	4620213d 			; <UNDEFINED> instruction: 0x4620213d
d00136c0:	fc10f7ff 	ldc2	7, cr15, [r0], {255}	; 0xff
d00136c4:	9a03b1e0 	bls	0xd00ffe4c
d00136c8:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d00136cc:	fca2f7ff 	stc2	7, cr15, [r2], #1020	; 0x3fc
d00136d0:	460e4605 	strmi	r4, [lr], -r5, lsl #12
d00136d4:	4300f115 	movwmi	pc, #277	; 0x115	; <UNPREDICTABLE>
d00136d8:	32fff04f 	rscscc	pc, pc, #79	; 0x4f
d00136dc:	f1469304 			; <UNDEFINED> instruction: 0xf1469304
d00136e0:	93050300 	movwls	r0, #21248	; 0x5300
d00136e4:	e9dd2300 	ldmib	sp, {r8, r9, sp}^
d00136e8:	428b0104 	addmi	r0, fp, #4, 2
d00136ec:	4282bf08 	addmi	fp, r2, #8, 30
d00136f0:	6da3d20a 	sfmvs	f5, 1, [r3, #40]!	; 0x28
d00136f4:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d00136f8:	4b44af5e 	blmi	0xd113f478
d00136fc:	e7ce447b 			; <UNDEFINED> instruction: 0xe7ce447b
d0013700:	f1463501 			; <UNDEFINED> instruction: 0xf1463501
d0013704:	e7e50600 	strb	r0, [r5, r0, lsl #12]!
d0013708:	327ef504 	rsbscc	pc, lr, #4, 10	; 0x1000000
d001370c:	3190f8d2 			; <UNDEFINED> instruction: 0x3190f8d2
d0013710:	d1062ba0 	smlatble	r6, r0, fp, r2
d0013714:	2b006da3 	blcs	0xd002eda8
d0013718:	af4df47f 	svcge	0x004df47f
d001371c:	447b4b3c 	ldrbtmi	r4, [fp], #-2876	; 0xfffff4c4
d0013720:	f88de7bd 			; <UNDEFINED> instruction: 0xf88de7bd
d0013724:	1c598050 	mrrcne	0, 5, r8, r9, cr0
d0013728:	0828f04f 	stmdaeq	r8!, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d001372c:	0e38f10d 	rndeqe	f7, #5.0
d0013730:	1190f8c2 	orrsne	pc, r0, r2, asr #17
d0013734:	0b01f10b 	bleq	0xd008fb68
d0013738:	fb089a01 	blx	0xd0239f46
d001373c:	97154803 	ldrls	r4, [r5, -r3, lsl #16]
d0013740:	3878f508 	ldmdacc	r8!, {r3, r8, sl, ip, sp, lr, pc}^
d0013744:	9a029211 	bls	0xd00b7f90
d0013748:	0790f108 	ldreq	pc, [r0, r8, lsl #2]
d001374c:	c008f894 	mulgt	r8, r4, r8
d0013750:	e9cd9212 	stmib	sp, {r1, r4, r9, ip, pc}^
d0013754:	e8bea90e 	ldm	lr!, {r1, r2, r3, r8, fp, sp, pc}
d0013758:	c70f000f 	strgt	r0, [pc, -pc]
d001375c:	000fe89e 	muleq	pc, lr, r8	; <UNPREDICTABLE>
d0013760:	000fe887 	andeq	lr, pc, r7, lsl #17
d0013764:	4620212c 	strtmi	r2, [r0], -ip, lsr #2
d0013768:	50b0f8c8 	adcspl	pc, r0, r8, asr #17
d001376c:	c0b4f888 	adcsgt	pc, r4, r8, lsl #17
d0013770:	fbb8f7ff 	blx	0xcee51776
d0013774:	f47f2800 			; <UNDEFINED> instruction: 0xf47f2800
d0013778:	f1bbaf5d 			; <UNDEFINED> instruction: 0xf1bbaf5d
d001377c:	d1020f00 	tstle	r2, r0, lsl #30
d0013780:	44794924 	ldrbtmi	r4, [r9], #-2340	; 0xfffff6dc
d0013784:	4a24e6fd 	bmi	0xd094d380
d0013788:	4620217d 			; <UNDEFINED> instruction: 0x4620217d
d001378c:	b017447a 	andslt	r4, r7, sl, ror r4
d0013790:	8b02ecbd 	blhi	0xd00cea8c
d0013794:	4ff0e8bd 	svcmi	0x00f0e8bd
d0013798:	bbb2f7ff 	bllt	0xcecd179c
d001379c:	d111459a 			; <UNDEFINED> instruction: 0xd111459a
d00137a0:	377ef504 	ldrbcc	pc, [lr, -r4, lsl #10]!	; <UNPREDICTABLE>
d00137a4:	f5044682 			; <UNDEFINED> instruction: 0xf5044682
d00137a8:	f5073b7f 			; <UNDEFINED> instruction: 0xf5073b7f
d00137ac:	f8db77ca 			; <UNDEFINED> instruction: 0xf8db77ca
d00137b0:	459a3214 	ldrmi	r3, [sl, #532]	; 0x214
d00137b4:	6da3d30c 	stcvs	3, cr13, [r3, #48]!	; 0x30
d00137b8:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d00137bc:	4b17aefc 	blmi	0xd05ff3b4
d00137c0:	e701447b 	smlsdx	r1, fp, r4, r4
d00137c4:	46204916 			; <UNDEFINED> instruction: 0x46204916
d00137c8:	f7fc4479 			; <UNDEFINED> instruction: 0xf7fc4479
d00137cc:	e6f3fd3f 			; <UNDEFINED> instruction: 0xe6f3fd3f
d00137d0:	2020f897 	mlacs	r0, r7, r8, pc	; <UNPREDICTABLE>
d00137d4:	429a7a23 	addsmi	r7, sl, #143360	; 0x23000
d00137d8:	f10ad003 			; <UNDEFINED> instruction: 0xf10ad003
d00137dc:	37240a01 	strcc	r0, [r4, -r1, lsl #20]!
d00137e0:	464be7e5 	strbmi	lr, [fp], -r5, ror #15
d00137e4:	e9d74642 	ldmib	r7, {r1, r6, r9, sl, lr}^
d00137e8:	f7fc0100 			; <UNDEFINED> instruction: 0xf7fc0100
d00137ec:	2800ff69 	stmdacs	r0, {r0, r3, r5, r6, r8, r9, sl, fp, ip, sp, lr, pc}
d00137f0:	2501d0f3 	strcs	sp, [r1, #-243]	; 0xffffff0d
d00137f4:	bf00e6e0 	svclt	0x0000e6e0
d00137f8:	fffffec6 			; <UNDEFINED> instruction: 0xfffffec6
d00137fc:	fffffe5c 			; <UNDEFINED> instruction: 0xfffffe5c
d0013800:	fffffdfc 			; <UNDEFINED> instruction: 0xfffffdfc
d0013804:	fffffdc3 			; <UNDEFINED> instruction: 0xfffffdc3
d0013808:	fffffd6f 			; <UNDEFINED> instruction: 0xfffffd6f
d001380c:	fffffd27 			; <UNDEFINED> instruction: 0xfffffd27
d0013810:	fffffd2f 			; <UNDEFINED> instruction: 0xfffffd2f
d0013814:	fffffce3 			; <UNDEFINED> instruction: 0xfffffce3
d0013818:	fffffd00 			; <UNDEFINED> instruction: 0xfffffd00
d001381c:	fffffd0e 			; <UNDEFINED> instruction: 0xfffffd0e
d0013820:	fffffce6 			; <UNDEFINED> instruction: 0xfffffce6

Disassembly of section .text.sizeof_operand:

d0013a24 <.text.sizeof_operand>:
d0013a24:	4ff0e92d 	svcmi	0x00f0e92d
d0013a28:	21284604 			; <UNDEFINED> instruction: 0x21284604
d0013a2c:	8b02ed2d 	blhi	0xd00ceee8
d0013a30:	f7ffb08b 			; <UNDEFINED> instruction: 0xf7ffb08b
d0013a34:	f240fa57 	vpmin.s8	<illegal reg q15.5>, q0, <illegal reg q3.5>
d0013a38:	90021107 	andls	r1, r2, r7, lsl #2
d0013a3c:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0013a40:	b128fa51 	msrlt	R8_fiq, r1
d0013a44:	4620212a 	strtmi	r2, [r0], -sl, lsr #2
d0013a48:	fa4cf7ff 	blx	0xd1351a4c
d0013a4c:	e0312704 	eors	r2, r1, r4, lsl #14
d0013a50:	7184f44f 	orrvc	pc, r4, pc, asr #8
d0013a54:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0013a58:	b190fa45 	orrslt	pc, r0, r5, asr #20
d0013a5c:	4620212a 	strtmi	r2, [r0], -sl, lsr #2
d0013a60:	fa40f7ff 	blx	0xd1051a64
d0013a64:	28004607 	stmdacs	r0, {r0, r1, r2, r9, sl, lr}
d0013a68:	f8dfd1f0 			; <UNDEFINED> instruction: 0xf8dfd1f0
d0013a6c:	46201484 	strtmi	r1, [r0], -r4, lsl #9
d0013a70:	f7fc4479 			; <UNDEFINED> instruction: 0xf7fc4479
d0013a74:	4638fbeb 	ldrtmi	pc, [r8], -fp, ror #23	; <UNPREDICTABLE>
d0013a78:	ecbdb00b 	ldc	0, cr11, [sp], #44	; 0x2c
d0013a7c:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d0013a80:	6ae28ff0 	bvs	0xcf8b7a48
d0013a84:	131bf240 	tstne	fp, #64, 4	; <UNPREDICTABLE>
d0013a88:	d106429a 			; <UNDEFINED> instruction: 0xd106429a
d0013a8c:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0013a90:	2800fd29 	stmdacs	r0, {r0, r3, r5, r8, sl, fp, ip, sp, lr, pc}
d0013a94:	2700d1da 			; <UNDEFINED> instruction: 0x2700d1da
d0013a98:	f240e7ed 	vabd.s8	q15, q8, <illegal reg q14.5>
d0013a9c:	4620110b 	strtmi	r1, [r0], -fp, lsl #2
d0013aa0:	fa20f7ff 	blx	0xd0851aa4
d0013aa4:	212ab348 			; <UNDEFINED> instruction: 0x212ab348
d0013aa8:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0013aac:	2800fa1b 	stmdacs	r0, {r0, r1, r3, r4, r9, fp, ip, sp, lr, pc}
d0013ab0:	2701d1cc 	strcs	sp, [r1, -ip, asr #3]
d0013ab4:	4620215b 			; <UNDEFINED> instruction: 0x4620215b
d0013ab8:	fa14f7ff 	blx	0xd0551abc
d0013abc:	d0602800 	rsble	r2, r0, r0, lsl #16
d0013ac0:	f5a36ae3 			; <UNDEFINED> instruction: 0xf5a36ae3
d0013ac4:	2b017381 	blcs	0xd00708d0
d0013ac8:	81e3f200 	mvnhi	pc, r0, lsl #4
d0013acc:	2d006a25 	vstrcs	s12, [r0, #-148]	; 0xffffff6c
d0013ad0:	81dff000 	bicshi	pc, pc, r0
d0013ad4:	2305fba7 	movwcs	pc, #23463	; 0x5ba7	; <UNPREDICTABLE>
d0013ad8:	f0402b00 			; <UNDEFINED> instruction: 0xf0402b00
d0013adc:	462081da 			; <UNDEFINED> instruction: 0x462081da
d0013ae0:	f9e0f7ff 			; <UNDEFINED> instruction: 0xf9e0f7ff
d0013ae4:	240cf8df 	strcs	pc, [ip], #-2271	; 0xfffff721
d0013ae8:	4620215d 			; <UNDEFINED> instruction: 0x4620215d
d0013aec:	f7ff447a 			; <UNDEFINED> instruction: 0xf7ff447a
d0013af0:	2800fa07 	stmdacs	r0, {r0, r1, r2, r9, fp, ip, sp, lr, pc}
d0013af4:	436fd0cf 	cmnmi	pc, #207	; 0xcf
d0013af8:	6ae5e043 	bvs	0xcf98bc0c
d0013afc:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d0013b00:	d118429d 			; <UNDEFINED> instruction: 0xd118429d
d0013b04:	69e14afc 	stmibvs	r1!, {r2, r3, r4, r5, r6, r7, r9, fp, lr}^
d0013b08:	69a0447a 	stmibvs	r0!, {r1, r3, r4, r5, r6, sl, lr}
d0013b0c:	ff00f7fc 			; <UNDEFINED> instruction: 0xff00f7fc
d0013b10:	4620b118 			; <UNDEFINED> instruction: 0x4620b118
d0013b14:	f9c6f7ff 			; <UNDEFINED> instruction: 0xf9c6f7ff
d0013b18:	6ae3e7c5 	bvs	0xcf90da34
d0013b1c:	d10a42ab 	smlatble	sl, fp, r2, r4
d0013b20:	69e14af6 	stmibvs	r1!, {r1, r2, r4, r5, r6, r7, r9, fp, lr}^
d0013b24:	69a0447a 	stmibvs	r0!, {r1, r3, r4, r5, r6, sl, lr}
d0013b28:	fef2f7fc 	mrc2	7, 7, pc, cr2, cr12, {7}
d0013b2c:	4620b118 			; <UNDEFINED> instruction: 0x4620b118
d0013b30:	f9b8f7ff 			; <UNDEFINED> instruction: 0xf9b8f7ff
d0013b34:	4620e786 	strtmi	lr, [r0], -r6, lsl #15
d0013b38:	fea2f7fc 	mcr2	7, 5, pc, cr2, cr12, {7}	; <UNPREDICTABLE>
d0013b3c:	2300b1c0 	movwcs	fp, #448	; 0x1c0
d0013b40:	4620a909 	strtmi	sl, [r0], -r9, lsl #18
d0013b44:	f7ff9309 			; <UNDEFINED> instruction: 0xf7ff9309
d0013b48:	2800fbd7 	stmdacs	r0, {r0, r1, r2, r4, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d0013b4c:	212ad0a3 			; <UNDEFINED> instruction: 0x212ad0a3
d0013b50:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0013b54:	2800f9c7 	stmdacs	r0, {r0, r1, r2, r6, r7, r8, fp, ip, sp, lr, pc}
d0013b58:	af78f47f 	svcge	0x0078f47f
d0013b5c:	f44f9b09 			; <UNDEFINED> instruction: 0xf44f9b09
d0013b60:	fb02721a 	blx	0xd00b03d2
d0013b64:	f5034303 			; <UNDEFINED> instruction: 0xf5034303
d0013b68:	8d1f3368 	ldchi	3, cr3, [pc, #-416]	; 0xd00139d0
d0013b6c:	e7a100bf 			; <UNDEFINED> instruction: 0xe7a100bf
d0013b70:	f5a36ae3 			; <UNDEFINED> instruction: 0xf5a36ae3
d0013b74:	2b017381 	blcs	0xd0070980
d0013b78:	2704d811 	smladcs	r4, r1, r8, sp
d0013b7c:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0013b80:	9b02f991 	blls	0xd00d21cc
d0013b84:	f43f2b00 			; <UNDEFINED> instruction: 0xf43f2b00
d0013b88:	4addaf76 	bmi	0xcf77f968
d0013b8c:	46202129 	strtmi	r2, [r0], -r9, lsr #2
d0013b90:	f7ff447a 			; <UNDEFINED> instruction: 0xf7ff447a
d0013b94:	2800f9b5 	stmdacs	r0, {r0, r2, r4, r5, r7, r8, fp, ip, sp, lr, pc}
d0013b98:	af6df47f 	svcge	0x006df47f
d0013b9c:	212ae77b 			; <UNDEFINED> instruction: 0x212ae77b
d0013ba0:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0013ba4:	6a63f99f 	bvs	0xd1912228
d0013ba8:	46804ad6 	pkhtbmi	r4, r0, r6, asr #21
d0013bac:	f2409300 	vcgt.s8	d25, d0, d0
d0013bb0:	6b631101 	blvs	0xd18d7fbc
d0013bb4:	4620447a 			; <UNDEFINED> instruction: 0x4620447a
d0013bb8:	a028f8d4 	ldrdge	pc, [r8], -r4	; <UNPREDICTABLE>
d0013bbc:	9030f894 	mlasls	r0, r4, r8, pc	; <UNPREDICTABLE>
d0013bc0:	e9d49301 	ldmib	r4, {r0, r8, r9, ip, pc}^
d0013bc4:	f7ff5606 			; <UNDEFINED> instruction: 0xf7ff5606
d0013bc8:	2800f99b 	stmdacs	r0, {r0, r1, r3, r4, r7, r8, fp, ip, sp, lr, pc}
d0013bcc:	af63f43f 	svcge	0x0063f43f
d0013bd0:	46294632 			; <UNDEFINED> instruction: 0x46294632
d0013bd4:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0013bd8:	2800fde9 	stmdacs	r0, {r0, r3, r5, r6, r7, r8, sl, fp, ip, sp, lr, pc}
d0013bdc:	8172f280 	cmnhi	r2, r0, lsl #5	; <UNPREDICTABLE>
d0013be0:	46294632 			; <UNDEFINED> instruction: 0x46294632
d0013be4:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0013be8:	2800fe01 	stmdacs	r0, {r0, r9, sl, fp, ip, sp, lr, pc}
d0013bec:	6da7da0d 			; <UNDEFINED> instruction: 0x6da7da0d
d0013bf0:	f47f2f00 			; <UNDEFINED> instruction: 0xf47f2f00
d0013bf4:	4bc4af50 	blmi	0xcf13f93c
d0013bf8:	65a3447b 	strvs	r4, [r3, #1147]!	; 0x47b
d0013bfc:	65e39b00 	strbvs	r9, [r3, #2816]!	; 0xb00
d0013c00:	e9c49b01 	stmib	r4, {r0, r8, r9, fp, ip, pc}^
d0013c04:	66a3a918 	ssatvs	sl, #4, r8, lsl #18
d0013c08:	233ce735 	teqcs	ip, #13893632	; 0xd40000
d0013c0c:	4000fb03 	andmi	pc, r0, r3, lsl #22
d0013c10:	305ff500 	subscc	pc, pc, r0, lsl #10
d0013c14:	23ecf890 	mvncs	pc, #144, 16	; 0x900000
d0013c18:	53eef890 	mvnpl	pc, #144, 16	; 0x900000
d0013c1c:	13fcf8d0 	mvnsne	pc, #208, 16	; 0xd00000
d0013c20:	030df1a2 	movweq	pc, #53666	; 0xd1a2	; <UNPREDICTABLE>
d0013c24:	d9302b04 	ldmdble	r0!, {r2, r8, r9, fp, sp}
d0013c28:	26001fd3 			; <UNDEFINED> instruction: 0x26001fd3
d0013c2c:	d92e2b02 	stmdble	lr!, {r1, r8, r9, fp, sp}
d0013c30:	d02e2a10 	eorle	r2, lr, r0, lsl sl
d0013c34:	0c11f1a2 	ldfeqd	f7, [r1], {162}	; 0xa2
d0013c38:	0300f1dc 	movweq	pc, #476	; 0x1dc	; <UNPREDICTABLE>
d0013c3c:	030ceb43 	movweq	lr, #52035	; 0xcb43
d0013c40:	f0002a0a 			; <UNDEFINED> instruction: 0xf0002a0a
d0013c44:	2a13814b 	bcs	0xd04f4178
d0013c48:	48a8dc03 	stmiami	r8!, {r0, r1, sl, fp, ip, lr, pc}
d0013c4c:	07c740d0 			; <UNDEFINED> instruction: 0x07c740d0
d0013c50:	1f90d421 	svcne	0x0090d421
d0013c54:	0b00f1d0 	bleq	0xd005039c
d0013c58:	0b00eb4b 	bleq	0xd004e98c
d0013c5c:	d01d2a07 	andsle	r2, sp, r7, lsl #20
d0013c60:	d01b2a05 	andsle	r2, fp, r5, lsl #20
d0013c64:	f1bbb346 			; <UNDEFINED> instruction: 0xf1bbb346
d0013c68:	f0400f00 			; <UNDEFINED> instruction: 0xf0400f00
d0013c6c:	f44f8122 	vst4.8	{d24,d26,d28,d30}, [pc :128], r2
d0013c70:	fb02721a 	blx	0xd00b04e2
d0013c74:	f5024205 			; <UNDEFINED> instruction: 0xf5024205
d0013c78:	8d173268 	lfmhi	f3, 4, [r7, #-416]	; 0xfffffe60
d0013c7c:	0f00f1b8 	svceq	0x0000f1b8
d0013c80:	00bfd113 	adcseq	sp, pc, r3, lsl r1	; <UNPREDICTABLE>
d0013c84:	434fb363 	movtmi	fp, #62307	; 0xf363
d0013c88:	2601e02a 	strcs	lr, [r1], -sl, lsr #32
d0013c8c:	2301e7d0 	movwcs	lr, #6096	; 0x17d0
d0013c90:	2301e7d9 	movwcs	lr, #6105	; 0x17d9
d0013c94:	f04fe7d9 			; <UNDEFINED> instruction: 0xf04fe7d9
d0013c98:	e7e10b01 	strb	r0, [r1, r1, lsl #22]!
d0013c9c:	f1b82701 			; <UNDEFINED> instruction: 0xf1b82701
d0013ca0:	d0ef0f00 	rscle	r0, pc, r0, lsl #30
d0013ca4:	0f00f1bb 	svceq	0x0000f1bb
d0013ca8:	6da7d108 	stfvsd	f5, [r7, #32]!
d0013cac:	f47f2f00 			; <UNDEFINED> instruction: 0xf47f2f00
d0013cb0:	4b96aef2 	blmi	0xce5bf880
d0013cb4:	e7a0447b 			; <UNDEFINED> instruction: 0xe7a0447b
d0013cb8:	e7f02704 	ldrb	r2, [r0, r4, lsl #14]!
d0013cbc:	f0402a0e 			; <UNDEFINED> instruction: 0xf0402a0e
d0013cc0:	f44f8112 	vst4.8	{d24,d26,d28,d30}, [pc :64], r2
d0013cc4:	fb03731a 	blx	0xd00f0936
d0013cc8:	f5034305 			; <UNDEFINED> instruction: 0xf5034305
d0013ccc:	8d1f3368 	ldchi	3, cr3, [pc, #-416]	; 0xd0013b34
d0013cd0:	f1a200bf 			; <UNDEFINED> instruction: 0xf1a200bf
d0013cd4:	f04f030e 			; <UNDEFINED> instruction: 0xf04f030e
d0013cd8:	425e0b00 	subsmi	r0, lr, #0, 22
d0013cdc:	465b415e 			; <UNDEFINED> instruction: 0x465b415e
d0013ce0:	4620215b 			; <UNDEFINED> instruction: 0x4620215b
d0013ce4:	f7ff9303 			; <UNDEFINED> instruction: 0xf7ff9303
d0013ce8:	b378f8fd 	cmnlt	r8, #16580608	; 0xfd0000	; <UNPREDICTABLE>
d0013cec:	ea539b03 	b	0xd14fa900
d0013cf0:	d115030b 	tstle	r5, fp, lsl #6
d0013cf4:	2f006da7 	svccs	0x00006da7
d0013cf8:	aecdf47f 	mcrge	4, 6, pc, cr13, cr15, {3}	; <UNPREDICTABLE>
d0013cfc:	447b4b84 	ldrbtmi	r4, [fp], #-2948	; 0xfffff47c
d0013d00:	2b5be77b 	blcs	0xd170daf4
d0013d04:	3701d107 	strcc	sp, [r1, -r7, lsl #2]
d0013d08:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0013d0c:	b947f8cb 	stmdblt	r7, {r0, r1, r3, r6, r7, fp, ip, sp, lr, pc}^
d0013d10:	2704b9a6 	strcs	fp, [r4, -r6, lsr #19]
d0013d14:	2b5de01a 	blcs	0xd178bd84
d0013d18:	f107bf08 			; <UNDEFINED> instruction: 0xf107bf08
d0013d1c:	e7f337ff 	udf	#13183	; 0x337f
d0013d20:	6ae32701 	bvs	0xcf8dd92c
d0013d24:	7f80f5b3 	svcvc	0x0080f5b3
d0013d28:	6da2d002 	stcvs	0, cr13, [r2, #8]!
d0013d2c:	d0e82a00 	rscle	r2, r8, r0, lsl #20
d0013d30:	46204978 			; <UNDEFINED> instruction: 0x46204978
d0013d34:	f7fc4479 			; <UNDEFINED> instruction: 0xf7fc4479
d0013d38:	e6acfa89 	strt	pc, [ip], r9, lsl #21
d0013d3c:	731af44f 	tstvc	sl, #1325400064	; 0x4f000000	; <UNPREDICTABLE>
d0013d40:	4305fb03 	movwmi	pc, #23299	; 0x5b03	; <UNPREDICTABLE>
d0013d44:	3368f503 	msrcc	SPSR_f, #12582912	; 0xc00000
d0013d48:	00bf8d1f 	adcseq	r8, pc, pc, lsl sp	; <UNPREDICTABLE>
d0013d4c:	447b4b72 	ldrbtmi	r4, [fp], #-2930	; 0xfffff48e
d0013d50:	3a90ee08 	bcc	0xce44f578
d0013d54:	2b2e6ae3 	blcs	0xd0bae8e8
d0013d58:	f5b3d014 			; <UNDEFINED> instruction: 0xf5b3d014
d0013d5c:	f47f7f91 			; <UNDEFINED> instruction: 0xf47f7f91
d0013d60:	f1bbaf10 			; <UNDEFINED> instruction: 0xf1bbaf10
d0013d64:	d1170f00 	tstle	r7, r0, lsl #30
d0013d68:	2b006da3 	blcs	0xd002f3fc
d0013d6c:	ae93f47f 	mrcge	4, 4, APSR_nzcv, cr3, cr15, {3}
d0013d70:	447b4b6a 	ldrbtmi	r4, [fp], #-2922	; 0xfffff496
d0013d74:	9b0065a3 	blls	0xd002d408
d0013d78:	9b0165e3 	blls	0xd006d50c
d0013d7c:	a918e9c4 	ldmdbge	r8, {r2, r6, r7, r8, fp, sp, lr, pc}
d0013d80:	e68866a3 	str	r6, [r8], r3, lsr #13
d0013d84:	0f00f1bb 	svceq	0x0000f1bb
d0013d88:	6da7d006 	stcvs	0, cr13, [r7, #24]!
d0013d8c:	f47f2f00 			; <UNDEFINED> instruction: 0xf47f2f00
d0013d90:	4b63ae82 	blmi	0xd18ff7a0
d0013d94:	e730447b 			; <UNDEFINED> instruction: 0xe730447b
d0013d98:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0013d9c:	b936f883 	ldmdblt	r6!, {r0, r1, r7, fp, ip, sp, lr, pc}
d0013da0:	2b006da3 	blcs	0xd002f434
d0013da4:	ae77f47f 	mrcge	4, 3, APSR_nzcv, cr7, cr15, {3}
d0013da8:	447b4b5e 	ldrbtmi	r4, [fp], #-2910	; 0xfffff4a2
d0013dac:	69a3e7e2 	stmibvs	r3!, {r1, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d0013db0:	2a90ee18 	bcs	0xce44f618
d0013db4:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d0013db8:	ee084620 	cfmadd32	mvax1, mvfx4, mvfx8, mvfx0
d0013dbc:	69e33a10 	stmibvs	r3!, {r4, r9, fp, ip, sp}^
d0013dc0:	6a639307 	bvs	0xd18f89e4
d0013dc4:	6aa39303 	bvs	0xce8f89d8
d0013dc8:	f8949306 			; <UNDEFINED> instruction: 0xf8949306
d0013dcc:	93053030 	movwls	r3, #20528	; 0x5030
d0013dd0:	93046b63 	movwls	r6, #19299	; 0x4b63
d0013dd4:	f894f7ff 			; <UNDEFINED> instruction: 0xf894f7ff
d0013dd8:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0013ddc:	f44fae5c 			; <UNDEFINED> instruction: 0xf44fae5c
d0013de0:	2700731a 	smladcs	r0, sl, r3, r7
d0013de4:	fb05fb03 	blx	0xd01929fa
d0013de8:	f50b9b07 			; <UNDEFINED> instruction: 0xf50b9b07
d0013dec:	44a33867 	strtmi	r3, [r3], #2151	; 0x867
d0013df0:	78f4f508 	ldmvc	r4!, {r3, r8, sl, ip, sp, lr, pc}^
d0013df4:	3b68f50b 	blcc	0xd1a51228
d0013df8:	f89b44a0 			; <UNDEFINED> instruction: 0xf89b44a0
d0013dfc:	42ba202a 	adcsmi	r2, sl, #42	; 0x2a
d0013e00:	f44fd818 	vst2.8	{d29-d30}, [pc :64], r8
d0013e04:	435d731a 	cmpmi	sp, #1744830464	; 0x68000000
d0013e08:	f5031963 			; <UNDEFINED> instruction: 0xf5031963
d0013e0c:	f8933368 			; <UNDEFINED> instruction: 0xf8933368
d0013e10:	42bb302a 	adcsmi	r3, fp, #42	; 0x2a
d0013e14:	6da7d11c 	stfvsd	f5, [r7, #112]!	; 0x70
d0013e18:	f47f2f00 			; <UNDEFINED> instruction: 0xf47f2f00
d0013e1c:	4b42ae3c 	blmi	0xd10bf714
d0013e20:	65a3447b 	strvs	r4, [r3, #1147]!	; 0x47b
d0013e24:	65e39b03 	strbvs	r9, [r3, #2819]!	; 0xb03
d0013e28:	66239b06 	strtvs	r9, [r3], -r6, lsl #22
d0013e2c:	66639b05 	strbtvs	r9, [r3], -r5, lsl #22
d0013e30:	e6e89b04 	strbt	r9, [r8], r4, lsl #22
d0013e34:	1004f8d8 	ldrdne	pc, [r4], -r8
d0013e38:	2a10ee18 	bcs	0xd044f6a0
d0013e3c:	0b24f858 	bleq	0xd0951fa4
d0013e40:	f7fc9307 			; <UNDEFINED> instruction: 0xf7fc9307
d0013e44:	9b07fc3d 	blls	0xd0212f40
d0013e48:	d1da2800 	bicsle	r2, sl, r0, lsl #16
d0013e4c:	e7d43701 	ldrb	r3, [r4, r1, lsl #14]
d0013e50:	fb032324 	blx	0xd00dcaea
d0013e54:	44275707 	strtmi	r5, [r7], #-1799	; 0xfffff8f9
d0013e58:	3767f507 	strbcc	pc, [r7, -r7, lsl #10]!	; <UNPREDICTABLE>
d0013e5c:	5208f897 	andpl	pc, r8, #9895936	; 0x970000
d0013e60:	b209f897 	andlt	pc, r9, #9895936	; 0x970000
d0013e64:	03fff1b5 	mvnseq	pc, #1073741869	; 0x4000002d
d0013e68:	2301bf18 	movwcs	fp, #7960	; 0x1f18
d0013e6c:	0f00f1bb 	svceq	0x0000f1bb
d0013e70:	2dffd10d 	ldfcsp	f5, [pc, #52]!	; 0xd0013eac
d0013e74:	f44fd00a 	vst4.8	{d29-d32}, [pc], sl
d0013e78:	fb03731a 	blx	0xd00f0aea
d0013e7c:	f5034305 			; <UNDEFINED> instruction: 0xf5034305
d0013e80:	8d1f3368 	ldchi	3, cr3, [pc, #-416]	; 0xd0013ce8
d0013e84:	00bf4633 	adcseq	r4, pc, r3, lsr r6	; <UNPREDICTABLE>
d0013e88:	e763461e 			; <UNDEFINED> instruction: 0xe763461e
d0013e8c:	2704465b 	smlsdcs	r4, fp, r6, r4
d0013e90:	6da7e7fa 	stcvs	7, cr14, [r7, #1000]!	; 0x3e8
d0013e94:	f47f2f00 			; <UNDEFINED> instruction: 0xf47f2f00
d0013e98:	4d24adfe 	stcmi	13, cr10, [r4, #-1016]!	; 0xfffffc08
d0013e9c:	6aa16a60 	bvs	0xce86e824
d0013ea0:	f894447d 			; <UNDEFINED> instruction: 0xf894447d
d0013ea4:	6b632030 	blvs	0xd18dbf6c
d0013ea8:	5016e9c4 	andspl	lr, r6, r4, asr #19
d0013eac:	1218e9c4 	andsne	lr, r8, #196, 18	; 0x310000
d0013eb0:	f1b8e6a9 			; <UNDEFINED> instruction: 0xf1b8e6a9
d0013eb4:	f47f0f00 			; <UNDEFINED> instruction: 0xf47f0f00
d0013eb8:	2601af01 	strcs	sl, [r1], -r1, lsl #30
d0013ebc:	f04f2704 			; <UNDEFINED> instruction: 0xf04f2704
d0013ec0:	e6df0b01 	ldrb	r0, [pc], r1, lsl #22
d0013ec4:	fb032330 	blx	0xd00dcb8e
d0013ec8:	f5004000 			; <UNDEFINED> instruction: 0xf5004000
d0013ecc:	f8902090 			; <UNDEFINED> instruction: 0xf8902090
d0013ed0:	f8902659 			; <UNDEFINED> instruction: 0xf8902659
d0013ed4:	f8b0565a 			; <UNDEFINED> instruction: 0xf8b0565a
d0013ed8:	e6a11662 	strt	r1, [r1], r2, ror #12
d0013edc:	d1e82e00 	mvnle	r2, r0, lsl #28
d0013ee0:	0f00f1b8 	svceq	0x0000f1b8
d0013ee4:	2704d0ea 	strcs	sp, [r4, -sl, ror #1]
d0013ee8:	bf00e6f3 	svclt	0x0000e6f3
d0013eec:	000c5014 	andeq	r5, ip, r4, lsl r0
d0013ef0:	fffffdb0 			; <UNDEFINED> instruction: 0xfffffdb0
d0013ef4:	fffffed3 			; <UNDEFINED> instruction: 0xfffffed3
d0013ef8:	fffffd3e 			; <UNDEFINED> instruction: 0xfffffd3e
d0013efc:	fffffd2a 			; <UNDEFINED> instruction: 0xfffffd2a
d0013f00:	fffffe51 			; <UNDEFINED> instruction: 0xfffffe51
d0013f04:	fffffca2 			; <UNDEFINED> instruction: 0xfffffca2
d0013f08:	fffffc87 			; <UNDEFINED> instruction: 0xfffffc87
d0013f0c:	fffffbf8 			; <UNDEFINED> instruction: 0xfffffbf8
d0013f10:	fffffbc7 			; <UNDEFINED> instruction: 0xfffffbc7
d0013f14:	fffffccf 			; <UNDEFINED> instruction: 0xfffffccf
d0013f18:	fffffc07 			; <UNDEFINED> instruction: 0xfffffc07
d0013f1c:	fffffb7d 			; <UNDEFINED> instruction: 0xfffffb7d
d0013f20:	fffffb7c 			; <UNDEFINED> instruction: 0xfffffb7c
d0013f24:	fffffb85 			; <UNDEFINED> instruction: 0xfffffb85
d0013f28:	fffffb54 			; <UNDEFINED> instruction: 0xfffffb54
d0013f2c:	fffffaed 			; <UNDEFINED> instruction: 0xfffffaed

Disassembly of section .text.initialize_large_zero.constprop.0:

d0013f58 <.text.initialize_large_zero.constprop.0>:
d0013f58:	4c16b513 	cfldr32mi	mvfx11, [r6], {19}
d0013f5c:	4a16217b 	bmi	0xd059c550
d0013f60:	447a447c 	ldrbtmi	r4, [sl], #-1148	; 0xfffffb84
d0013f64:	92014620 	andls	r4, r1, #32, 12	; 0x2000000
d0013f68:	ffcaf7fe 			; <UNDEFINED> instruction: 0xffcaf7fe
d0013f6c:	6ae3b300 	bvs	0xcf900b74
d0013f70:	7381f5a3 	orrvc	pc, r1, #683671552	; 0x28c00000
d0013f74:	d8022b01 	stmdale	r2, {r0, r8, r9, fp, sp}
d0013f78:	9a016a23 	bls	0xd006e80c
d0013f7c:	490fb143 	stmdbmi	pc, {r0, r1, r6, r8, ip, sp, pc}	; <UNPREDICTABLE>
d0013f80:	4479480f 	ldrbtmi	r4, [r9], #-2063	; 0xfffff7f1
d0013f84:	b0024478 	andlt	r4, r2, r8, ror r4
d0013f88:	4010e8bd 			; <UNDEFINED> instruction: 0x4010e8bd
d0013f8c:	b95ef7fc 	ldmdblt	lr, {r2, r3, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}^
d0013f90:	92014620 	andls	r4, r1, #32, 12	; 0x2000000
d0013f94:	ff86f7fe 			; <UNDEFINED> instruction: 0xff86f7fe
d0013f98:	4620212c 	strtmi	r2, [r0], -ip, lsr #2
d0013f9c:	ffa2f7fe 			; <UNDEFINED> instruction: 0xffa2f7fe
d0013fa0:	217d9a01 	cmncs	sp, r1, lsl #20
d0013fa4:	b0024620 	andlt	r4, r2, r0, lsr #12
d0013fa8:	4010e8bd 			; <UNDEFINED> instruction: 0x4010e8bd
d0013fac:	bfa8f7fe 	svclt	0x00a8f7fe
d0013fb0:	bd10b002 	ldclt	0, cr11, [r0, #-8]
d0013fb4:	00013b34 	andeq	r3, r1, r4, lsr fp
d0013fb8:	ffffffca 			; <UNDEFINED> instruction: 0xffffffca
d0013fbc:	ffffffaa 			; <UNDEFINED> instruction: 0xffffffaa
d0013fc0:	00013b10 	andeq	r3, r1, r0, lsl fp

Disassembly of section .text.add_local.constprop.0:

d0014000 <.text.add_local.constprop.0>:
d0014000:	e92db084 	push	{r2, r7, ip, sp, pc}
d0014004:	4d3447f0 	ldcmi	7, cr4, [r4, #-960]!	; 0xfffffc40
d0014008:	447dac08 	ldrbtmi	sl, [sp], #-3080	; 0xfffff3f8
d001400c:	000fe884 	andeq	lr, pc, r4, lsl #17
d0014010:	9a094601 	bls	0xd026581c
d0014014:	f8dd4628 			; <UNDEFINED> instruction: 0xf8dd4628
d0014018:	f8dda02c 			; <UNDEFINED> instruction: 0xf8dda02c
d001401c:	f89d9030 			; <UNDEFINED> instruction: 0xf89d9030
d0014020:	9e0f8038 	mcrls	0, 0, r8, cr15, cr8, {1}
d0014024:	fbc2f7fc 	blx	0xcf0d201e
d0014028:	db1b2800 	blle	0xd06de030
d001402c:	fb032330 	blx	0xd00dccf6
d0014030:	f5055000 			; <UNDEFINED> instruction: 0xf5055000
d0014034:	f5002392 			; <UNDEFINED> instruction: 0xf5002392
d0014038:	f8d32090 			; <UNDEFINED> instruction: 0xf8d32090
d001403c:	f8903240 			; <UNDEFINED> instruction: 0xf8903240
d0014040:	429a2658 	addsmi	r2, sl, #88, 12	; 0x5800000
d0014044:	6dacd10e 	stfvsd	f5, [ip, #56]!	; 0x38
d0014048:	d1422c00 	cmple	r2, r0, lsl #24
d001404c:	66ae4b23 	strtvs	r4, [lr], r3, lsr #22
d0014050:	e9c5447b 	stmib	r5, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0014054:	e9c59818 	stmib	r5, {r3, r4, fp, ip, pc}^
d0014058:	46203a16 			; <UNDEFINED> instruction: 0x46203a16
d001405c:	47f0e8bd 			; <UNDEFINED> instruction: 0x47f0e8bd
d0014060:	4770b004 	ldrbmi	fp, [r0, -r4]!
d0014064:	447b4b1e 	ldrbtmi	r4, [fp], #-2846	; 0xfffff4e2
d0014068:	2792f503 	ldrcs	pc, [r2, r3, lsl #10]
d001406c:	4238f8d7 	eorsmi	pc, r8, #14090240	; 0xd70000
d0014070:	d1092c40 	tstle	r9, r0, asr #24
d0014074:	bb646d9c 	bllt	0xd192f6ec
d0014078:	669e4a1a 			; <UNDEFINED> instruction: 0x669e4a1a
d001407c:	e9c3447a 	stmib	r3, {r1, r3, r4, r5, r6, sl, lr}^
d0014080:	e9c39818 	stmib	r3, {r3, r4, fp, ip, pc}^
d0014084:	e7e82a16 			; <UNDEFINED> instruction: 0xe7e82a16
d0014088:	f1042230 			; <UNDEFINED> instruction: 0xf1042230
d001408c:	ae080801 	cdpge	8, 0, cr0, cr8, cr1, {0}
d0014090:	fb022100 	blx	0xd009c49a
d0014094:	f8973304 			; <UNDEFINED> instruction: 0xf8973304
d0014098:	f8c79240 			; <UNDEFINED> instruction: 0xf8c79240
d001409c:	f5038238 			; <UNDEFINED> instruction: 0xf5038238
d00140a0:	f50a2a90 			; <UNDEFINED> instruction: 0xf50a2a90
d00140a4:	462865c7 	strtmi	r6, [r8], -r7, asr #11
d00140a8:	ff28f00c 			; <UNDEFINED> instruction: 0xff28f00c
d00140ac:	9658f88a 	ldrbls	pc, [r8], -sl, lsl #17	; <UNPREDICTABLE>
d00140b0:	c50fce0f 	strgt	ip, [pc, #-3599]	; 0xd00132a9
d00140b4:	000fe896 	muleq	pc, r6, r8	; <UNPREDICTABLE>
d00140b8:	000fe885 	andeq	lr, pc, r5, lsl #17
d00140bc:	3040f89d 	umaalcc	pc, r0, sp, r8	; <UNPREDICTABLE>
d00140c0:	3659f88a 	ldrbcc	pc, [r9], -sl, lsl #17	; <UNPREDICTABLE>
d00140c4:	323cf8d7 	eorscc	pc, ip, #14090240	; 0xd70000
d00140c8:	d9c64598 	stmible	r6, {r3, r4, r7, r8, sl, lr}^
d00140cc:	823cf8c7 	eorshi	pc, ip, #13041664	; 0xc70000
d00140d0:	2400e7c3 	strcs	lr, [r0], #-1987	; 0xfffff83d
d00140d4:	bf00e7c1 	svclt	0x0000e7c1
d00140d8:	00013a8a 	andeq	r3, r1, sl, lsl #21
d00140dc:	ffffff70 			; <UNDEFINED> instruction: 0xffffff70
d00140e0:	00013a2e 	andeq	r3, r1, lr, lsr #20
d00140e4:	ffffff60 			; <UNDEFINED> instruction: 0xffffff60

Disassembly of section .text.record_definition.constprop.0:

d001435c <.text.record_definition.constprop.0>:
d001435c:	e92db084 	push	{r2, r7, ip, sp, pc}
d0014360:	f5ad4ff0 			; <UNDEFINED> instruction: 0xf5ad4ff0
d0014364:	f8df7d33 			; <UNDEFINED> instruction: 0xf8df7d33
d0014368:	46065508 	strmi	r5, [r6], -r8, lsl #10
d001436c:	447dacbc 	ldrbtmi	sl, [sp], #-3260	; 0xfffff344
d0014370:	a310f8dd 	tstge	r0, #14483456	; 0xdd0000	; <UNPREDICTABLE>
d0014374:	000fe884 	andeq	lr, pc, r4, lsl #17
d0014378:	217b9bbf 	ldrhcs	r9, [fp, #-191]!	; 0xffffff41
d001437c:	24f4f8df 	ldrbtcs	pc, [r4], #2271	; 0x8df	; <UNPREDICTABLE>
d0014380:	93004628 	movwls	r4, #1576	; 0x628
d0014384:	447a9bc0 	ldrbtmi	r9, [sl], #-3008	; 0xfffff440
d0014388:	93019fbd 	movwls	r9, #8125	; 0x1fbd
d001438c:	3308f89d 	movwcc	pc, #34973	; 0x889d	; <UNPREDICTABLE>
d0014390:	9bc39302 	blls	0xcf0f8fa0
d0014394:	f7fe9303 			; <UNDEFINED> instruction: 0xf7fe9303
d0014398:	b910fdb3 	ldmdblt	r0, {r0, r1, r4, r5, r7, r8, sl, fp, ip, sp, lr, pc}
d001439c:	34fff04f 	ldrbtcc	pc, [pc], #79	; 0xd00143a4	; <UNPREDICTABLE>
d00143a0:	9bc5e232 	blls	0xcf18cc70
d00143a4:	f0402b00 			; <UNDEFINED> instruction: 0xf0402b00
d00143a8:	465380a4 	ldrbmi	r8, [r3], -r4, lsr #1
d00143ac:	4631463a 			; <UNDEFINED> instruction: 0x4631463a
d00143b0:	f7fc4628 			; <UNDEFINED> instruction: 0xf7fc4628
d00143b4:	f08af993 			; <UNDEFINED> instruction: 0xf08af993
d00143b8:	46040301 	strmi	r0, [r4], -r1, lsl #6
d00143bc:	4631463a 			; <UNDEFINED> instruction: 0x4631463a
d00143c0:	f7fc4628 			; <UNDEFINED> instruction: 0xf7fc4628
d00143c4:	2800f98b 	stmdacs	r0, {r0, r1, r3, r7, r8, fp, ip, sp, lr, pc}
d00143c8:	824cf2c0 	subhi	pc, ip, #192, 4
d00143cc:	2b006dab 	blcs	0xd002fa80
d00143d0:	f8dfd1e4 			; <UNDEFINED> instruction: 0xf8dfd1e4
d00143d4:	447b34a4 	ldrbtmi	r3, [fp], #-1188	; 0xfffffb5c
d00143d8:	9b0065ab 	blls	0xd002da8c
d00143dc:	9b0165eb 	blls	0xd006db90
d00143e0:	9b02662b 	blls	0xd00adc94
d00143e4:	9b03666b 	blls	0xd00edd98
d00143e8:	e7d766ab 	ldrb	r6, [r7, fp, lsr #13]
d00143ec:	3275f505 	rsbscc	pc, r5, #20971520	; 0x1400000
d00143f0:	3388f8d2 	orrcc	pc, r8, #13762560	; 0xd20000
d00143f4:	d1062b18 	tstle	r6, r8, lsl fp
d00143f8:	2b006dab 	blcs	0xd002faac
d00143fc:	f8dfd1ce 			; <UNDEFINED> instruction: 0xf8dfd1ce
d0014400:	447b347c 	ldrbtmi	r3, [fp], #-1148	; 0xfffffb84
d0014404:	1c59e7e8 	mrrcne	7, 14, lr, r9, cr8
d0014408:	469b7a2e 	ldrmi	r7, [fp], lr, lsr #20
d001440c:	1388f8c2 	orrne	pc, r8, #12713984	; 0xc20000
d0014410:	721af44f 	andsvc	pc, sl, #1325400064	; 0x4f000000
d0014414:	fb0299c5 	blx	0xd00bab32
d0014418:	f5055503 			; <UNDEFINED> instruction: 0xf5055503
d001441c:	f5053767 			; <UNDEFINED> instruction: 0xf5053767
d0014420:	f5073568 			; <UNDEFINED> instruction: 0xf5073568
d0014424:	463877e4 	ldrtmi	r7, [r8], -r4, ror #15
d0014428:	fd68f00c 	stc2l	0, cr15, [r8, #-48]!	; 0xffffffd0
d001442c:	7c3cf50d 	cfldr32vc	mvfx15, [ip], #-52	; 0xffffffcc
d0014430:	a02bf885 	eorge	pc, fp, r5, lsl #17
d0014434:	602ef885 	eorvs	pc, lr, r5, lsl #17
d0014438:	000fe8bc 			; <UNDEFINED> instruction: 0x000fe8bc
d001443c:	e89cc70f 	ldm	ip, {r0, r1, r2, r3, r8, r9, sl, lr, pc}
d0014440:	e887000f 	stm	r7, {r0, r1, r2, r3}
d0014444:	ad18000f 	ldcge	0, cr0, [r8, #-60]	; 0xffffffc4
d0014448:	721af44f 	andsvc	pc, sl, #1325400064	; 0x4f000000
d001444c:	46282100 	strtmi	r2, [r8], -r0, lsl #2
d0014450:	f00c462e 			; <UNDEFINED> instruction: 0xf00c462e
d0014454:	9bc5fd53 	blls	0xcf1939a8
d0014458:	d04e2b00 	suble	r2, lr, r0, lsl #22
d001445c:	f10dafc6 			; <UNDEFINED> instruction: 0xf10dafc6
d0014460:	cf0f093c 	svcgt	0x000f093c
d0014464:	e897c60f 	ldm	r7, {r0, r1, r2, r3, r9, sl, lr, pc}
d0014468:	e886000f 	stm	r6, {r0, r1, r2, r3}
d001446c:	9bc5000f 	blls	0xcf1544b0
d0014470:	640cf8df 	strvs	pc, [ip], #-2271	; 0xfffff721
d0014474:	3264f885 	rsbcc	pc, r4, #8716288	; 0x850000
d0014478:	447e2301 	ldrbtmi	r2, [lr], #-769	; 0xfffffcff
d001447c:	a263f885 	rsbge	pc, r3, #8716288	; 0x850000
d0014480:	3265f885 	rsbcc	pc, r5, #8716288	; 0x850000
d0014484:	f8857a33 			; <UNDEFINED> instruction: 0xf8857a33
d0014488:	6db33266 	lfmvs	f3, 4, [r3, #408]!	; 0x198
d001448c:	6af3b92b 	bvs	0xcfd02940
d0014490:	d0022b7d 	andle	r2, r2, sp, ror fp
d0014494:	7f80f5b3 	svcvc	0x0080f5b3
d0014498:	4dfad131 	ldfmip	f5, [sl, #196]!	; 0xc4
d001449c:	4afa217d 	bmi	0xcfe9ca98
d00144a0:	447a447d 	ldrbtmi	r4, [sl], #-1149	; 0xfffffb83
d00144a4:	f7fe4628 			; <UNDEFINED> instruction: 0xf7fe4628
d00144a8:	2800fd2b 	stmdacs	r0, {r0, r1, r3, r5, r8, sl, fp, ip, sp, lr, pc}
d00144ac:	af76f43f 	svcge	0x0076f43f
d00144b0:	af189bc5 	svcge	0x00189bc5
d00144b4:	3518b13b 	ldrcc	fp, [r8, #-315]	; 0xfffffec5
d00144b8:	cd0f463e 	stcgt	6, cr4, [pc, #-248]	; 0xd00143c8
d00144bc:	e895c60f 	ldm	r5, {r0, r1, r2, r3, r9, sl, lr, pc}
d00144c0:	e886000f 	stm	r6, {r0, r1, r2, r3}
d00144c4:	f897000f 			; <UNDEFINED> instruction: 0xf897000f
d00144c8:	2b003262 	blcs	0xd0020e58
d00144cc:	813cf040 	teqhi	ip, r0, asr #32	; <UNPREDICTABLE>
d00144d0:	447b4bee 	ldrbtmi	r4, [fp], #-3054	; 0xfffff412
d00144d4:	2a006d9a 	bcs	0xd002fb44
d00144d8:	af60f47f 	svcge	0x0060f47f
d00144dc:	447a4aec 	ldrbtmi	r4, [sl], #-2796	; 0xfffff514
d00144e0:	9a00659a 	bls	0xd002db50
d00144e4:	9a0165da 	bls	0xd006dc54
d00144e8:	9a02661a 	bls	0xd00add58
d00144ec:	9a03665a 	bls	0xd00ede5c
d00144f0:	f04fe0dd 			; <UNDEFINED> instruction: 0xf04fe0dd
d00144f4:	46a334ff 			; <UNDEFINED> instruction: 0x46a334ff
d00144f8:	afbce7a5 	svcge	0x00bce7a5
d00144fc:	f89de7af 			; <UNDEFINED> instruction: 0xf89de7af
d0014500:	2b1032c2 	blcs	0xd0421010
d0014504:	49e3d105 	stmibmi	r3!, {r0, r2, r8, ip, lr, pc}^
d0014508:	44794630 	ldrbtmi	r4, [r9], #-1584	; 0xfffff9d0
d001450c:	fe9ef7fb 	mrc2	7, 4, pc, cr14, cr11, {7}
d0014510:	23ffe744 	mvnscs	lr, #68, 14	; 0x1100000
d0014514:	1107f240 	tstne	r7, r0, asr #4	; <UNPREDICTABLE>
d0014518:	f8c94630 			; <UNDEFINED> instruction: 0xf8c94630
d001451c:	f7fe3000 			; <UNDEFINED> instruction: 0xf7fe3000
d0014520:	b1e8fce1 	mvnlt	pc, r1, ror #25
d0014524:	f8c923ff 			; <UNDEFINED> instruction: 0xf8c923ff
d0014528:	4ddb3000 	ldclmi	0, cr3, [fp]
d001452c:	447d212a 	ldrbtmi	r2, [sp], #-298	; 0xfffffed6
d0014530:	f7fe4628 			; <UNDEFINED> instruction: 0xf7fe4628
d0014534:	9006fcd7 	ldrdls	pc, [r6], -r7
d0014538:	d14c2800 	cmple	ip, r0, lsl #16
d001453c:	3000f8d9 	ldrdcc	pc, [r0], -r9
d0014540:	d0482bff 	strdle	r2, [r8], #-191	; 0xffffff41
d0014544:	721af44f 	andsvc	pc, sl, #1325400064	; 0x4f000000
d0014548:	5303fb02 	movwpl	pc, #15106	; 0x3b02	; <UNPREDICTABLE>
d001454c:	3368f503 	msrcc	SPSR_f, #12582912	; 0xc00000
d0014550:	302df893 	mlacc	sp, r3, r8, pc	; <UNPREDICTABLE>
d0014554:	d13e2b00 	teqle	lr, r0, lsl #22
d0014558:	462849d0 			; <UNDEFINED> instruction: 0x462849d0
d001455c:	e7d54479 			; <UNDEFINED> instruction: 0xe7d54479
d0014560:	f2406af2 	vpmin.s8	q11, q8, q9
d0014564:	429a1301 	addsmi	r1, sl, #67108864	; 0x4000000
d0014568:	4630d118 			; <UNDEFINED> instruction: 0x4630d118
d001456c:	1206e9d6 	andne	lr, r6, #3506176	; 0x358000
d0014570:	f961f7fc 			; <UNDEFINED> instruction: 0xf961f7fc
d0014574:	db112800 	blle	0xd045e57c
d0014578:	e9d64630 	ldmib	r6, {r4, r5, r9, sl, lr}^
d001457c:	f7fc1206 			; <UNDEFINED> instruction: 0xf7fc1206
d0014580:	2324f95a 	msrcs	CPSR_s, #1474560	; 0x168000
d0014584:	6000fb03 	andvs	pc, r0, r3, lsl #22
d0014588:	3075f500 	rsbscc	pc, r5, r0, lsl #10
d001458c:	33acf890 			; <UNDEFINED> instruction: 0x33acf890
d0014590:	d1032bff 	strdle	r2, [r3, -pc]
d0014594:	f7fe4630 			; <UNDEFINED> instruction: 0xf7fe4630
d0014598:	e7c6fc85 	strb	pc, [r6, r5, lsl #25]	; <UNPREDICTABLE>
d001459c:	f24048c0 	vadd.i8	q10, q8, q0
d00145a0:	4478131b 	ldrbtmi	r1, [r8], #-795	; 0xfffffce5
d00145a4:	429a6ac2 	addsmi	r6, sl, #794624	; 0xc2000
d00145a8:	f7fed103 			; <UNDEFINED> instruction: 0xf7fed103
d00145ac:	2800ff9b 	stmdacs	r0, {r0, r1, r3, r4, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d00145b0:	48bcd1b8 	ldmmi	ip!, {r3, r4, r5, r7, r8, ip, lr, pc}
d00145b4:	44784649 	ldrbtmi	r4, [r8], #-1609	; 0xfffff9b7
d00145b8:	fe9ef7fe 	mrc2	7, 4, pc, cr14, cr14, {7}
d00145bc:	d1b42800 			; <UNDEFINED> instruction: 0xd1b42800
d00145c0:	0f00f1ba 	svceq	0x0000f1ba
d00145c4:	49b8d104 	ldmibmi	r8!, {r2, r8, ip, lr, pc}
d00145c8:	48b84479 	ldmmi	r8!, {r0, r3, r4, r5, r6, sl, lr}
d00145cc:	e79d4478 			; <UNDEFINED> instruction: 0xe79d4478
d00145d0:	447949b7 	ldrbtmi	r4, [r9], #-2487	; 0xfffff649
d00145d4:	4db7e7f9 	ldcmi	7, cr14, [r7, #996]!	; 0x3e4
d00145d8:	447daf10 	ldrbtmi	sl, [sp], #-3856	; 0xfffff0f0
d00145dc:	0c18f105 	ldfeqd	f7, [r8], {5}
d00145e0:	000fe8bc 			; <UNDEFINED> instruction: 0x000fe8bc
d00145e4:	e89cc70f 	ldm	ip, {r0, r1, r2, r3, r8, r9, sl, lr, pc}
d00145e8:	e887000f 	stm	r7, {r0, r1, r2, r3}
d00145ec:	69ab000f 	stmibvs	fp!, {r0, r1, r2, r3}
d00145f0:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d00145f4:	46284ab0 			; <UNDEFINED> instruction: 0x46284ab0
d00145f8:	69eb930b 	stmibvs	fp!, {r0, r1, r3, r8, r9, ip, pc}^
d00145fc:	930a447a 	movwls	r4, #42106	; 0xa47a
d0014600:	93056a6b 	movwls	r6, #23147	; 0x5a6b
d0014604:	93096aab 	movwls	r6, #39595	; 0x9aab
d0014608:	3030f895 	mlascc	r0, r5, r8, pc	; <UNPREDICTABLE>
d001460c:	6b6b9308 	blvs	0xd1af9234
d0014610:	f7fe9307 			; <UNDEFINED> instruction: 0xf7fe9307
d0014614:	2800fc75 	stmdacs	r0, {r0, r2, r4, r5, r6, sl, fp, ip, sp, lr, pc}
d0014618:	aec0f43f 	mcrge	4, 6, pc, cr0, cr15, {1}	; <UNPREDICTABLE>
d001461c:	213b4aa7 	teqcs	fp, r7, lsr #21
d0014620:	447a4628 	ldrbtmi	r4, [sl], #-1576	; 0xfffff9d8
d0014624:	fc6cf7fe 	stc2l	7, cr15, [ip], #-1016	; 0xfffffc08
d0014628:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001462c:	ad18aeb7 	ldcge	14, cr10, [r8, #-732]	; 0xfffffd24
d0014630:	46a82700 	strtmi	r2, [r8], r0, lsl #14
d0014634:	c262f898 	rsbgt	pc, r2, #152, 16	; 0x980000
d0014638:	d31c4567 	tstle	ip, #432013312	; 0x19c00000
d001463c:	2b009b06 	blcs	0xd003b25c
d0014640:	f8d9d13c 			; <UNDEFINED> instruction: 0xf8d9d13c
d0014644:	2bff3000 	blcs	0xcffe064c
d0014648:	4a9dd038 	bmi	0xce788730
d001464c:	711af44f 	tstvc	sl, pc, asr #8	; <UNPREDICTABLE>
d0014650:	fb01447a 	blx	0xd0065842
d0014654:	f5032303 			; <UNDEFINED> instruction: 0xf5032303
d0014658:	f8b33368 			; <UNDEFINED> instruction: 0xf8b33368
d001465c:	f1bee028 			; <UNDEFINED> instruction: 0xf1bee028
d0014660:	d12d0f00 			; <UNDEFINED> instruction: 0xd12d0f00
d0014664:	447b4b97 	ldrbtmi	r4, [fp], #-2967	; 0xfffff469
d0014668:	2a006d9a 	bcs	0xd002fcd8
d001466c:	ae96f47f 	mrcge	4, 4, APSR_nzcv, cr6, cr15, {3}
d0014670:	447a4a95 	ldrbtmi	r4, [sl], #-2709	; 0xfffff56b
d0014674:	6a69e013 	bvs	0xd1a8c6c8
d0014678:	f8553524 			; <UNDEFINED> instruction: 0xf8553524
d001467c:	9b0a0c04 	blls	0xd0297694
d0014680:	f7fc9a0b 			; <UNDEFINED> instruction: 0xf7fc9a0b
d0014684:	b1b8f81d 			; <UNDEFINED> instruction: 0xb1b8f81d
d0014688:	0f00f1ba 	svceq	0x0000f1ba
d001468c:	4a8fd111 	bmi	0xce408ad8
d0014690:	4b8f447a 	blmi	0xce3e5880
d0014694:	6d99447b 	cfldrsvs	mvf4, [r9, #492]	; 0x1ec
d0014698:	f47f2900 			; <UNDEFINED> instruction: 0xf47f2900
d001469c:	659aae7f 	ldrvs	sl, [sl, #3711]	; 0xe7f
d00146a0:	65da9a05 	ldrbvs	r9, [sl, #2565]	; 0xa05
d00146a4:	661a9a09 	ldrvs	r9, [sl], -r9, lsl #20
d00146a8:	665a9a08 	ldrbvs	r9, [sl], -r8, lsl #20
d00146ac:	669a9a07 	ldrvs	r9, [sl], r7, lsl #20
d00146b0:	4a88e674 	bmi	0xce24e088
d00146b4:	e7ec447a 			; <UNDEFINED> instruction: 0xe7ec447a
d00146b8:	e7bb3701 	ldr	r3, [fp, r1, lsl #14]!
d00146bc:	0e01f04f 	cdpeq	0, 0, cr15, cr1, cr15, {2}
d00146c0:	f8bdab18 			; <UNDEFINED> instruction: 0xf8bdab18
d00146c4:	930482c0 	movwls	r8, #17088	; 0x42c0
d00146c8:	437ff5c8 	cmnmi	pc, #200, 10	; 0x32000000	; <UNPREDICTABLE>
d00146cc:	457333ff 	ldrbmi	r3, [r3, #-1023]!	; 0xfffffc01
d00146d0:	9a04d3c8 	bls	0xd01495f8
d00146d4:	0301f10c 	movweq	pc, #4364	; 0x110c	; <UNPREDICTABLE>
d00146d8:	0f00f1ba 	svceq	0x0000f1ba
d00146dc:	f882ad10 			; <UNDEFINED> instruction: 0xf882ad10
d00146e0:	f8993262 			; <UNDEFINED> instruction: 0xf8993262
d00146e4:	930c3000 	movwls	r3, #49152	; 0xc000
d00146e8:	4643bf0c 	strbmi	fp, [r3], -ip, lsl #30
d00146ec:	930d2300 	movwls	r2, #54016	; 0xd300
d00146f0:	93109b0b 	tstls	r0, #11264	; 0x2c00
d00146f4:	93119b0a 	tstls	r1, #10240	; 0x2800
d00146f8:	93139b05 	tstls	r3, #5120	; 0x1400
d00146fc:	93149b09 	tstls	r4, #9216	; 0x2400
d0014700:	f88d9b08 			; <UNDEFINED> instruction: 0xf88d9b08
d0014704:	9b073058 	blls	0xd01e086c
d0014708:	f04f9317 			; <UNDEFINED> instruction: 0xf04f9317
d001470c:	fb030324 	blx	0xd00d53a6
d0014710:	cd0f2c0c 	stcgt	12, cr2, [pc, #-48]	; 0xd00146e8
d0014714:	0720f10c 	streq	pc, [r0, -ip, lsl #2]!
d0014718:	e895c70f 	ldm	r5, {r0, r1, r2, r3, r8, r9, sl, lr, pc}
d001471c:	e887000f 	stm	r7, {r0, r1, r2, r3}
d0014720:	9b0c000f 	blls	0xd0314764
d0014724:	3040f88c 	subcc	pc, r0, ip, lsl #17
d0014728:	f88c9b06 			; <UNDEFINED> instruction: 0xf88c9b06
d001472c:	9b0d3041 	blls	0xd0360838
d0014730:	3042f8ac 	subcc	pc, r2, ip, lsr #17
d0014734:	45f0d006 	ldrbmi	sp, [r0, #6]!
d0014738:	aea7f4bf 	mcrge	4, 5, pc, cr7, cr15, {5}	; <UNPREDICTABLE>
d001473c:	f8a39b04 			; <UNDEFINED> instruction: 0xf8a39b04
d0014740:	e6a2e260 	strt	lr, [r2], r0, ror #4
d0014744:	e7f944c6 	ldrb	r4, [r9, r6, asr #9]!
d0014748:	b18b9bc5 	orrlt	r9, fp, r5, asr #23
d001474c:	f04f4e62 			; <UNDEFINED> instruction: 0xf04f4e62
d0014750:	f10d0800 			; <UNDEFINED> instruction: 0xf10d0800
d0014754:	447e0960 	ldrbtmi	r0, [lr], #-2400	; 0xfffff6a0
d0014758:	3567f506 	strbcc	pc, [r7, #-1286]!	; 0xfffffafa	; <UNPREDICTABLE>
d001475c:	3375f506 	cmncc	r5, #25165824	; 0x1800000	; <UNPREDICTABLE>
d0014760:	75e4f505 	strbvc	pc, [r4, #1285]!	; 0x505	; <UNPREDICTABLE>
d0014764:	9b049304 	blls	0xd013937c
d0014768:	3388f8d3 	orrcc	pc, r8, #13828096	; 0xd30000
d001476c:	d31c4598 	tstle	ip, #152, 10	; 0x26000000
d0014770:	db382c00 	blle	0xd0e1f778
d0014774:	731af44f 	tstvc	sl, #1325400064	; 0x4f000000	; <UNPREDICTABLE>
d0014778:	a8184958 	ldmdage	r8, {r3, r4, r6, r8, fp, lr}
d001477c:	44794363 	ldrbtmi	r4, [r9], #-867	; 0xfffffc9d
d0014780:	3367f503 	msrcc	SPSR_sxc, #12582912	; 0xc00000
d0014784:	73e4f503 	mvnvc	pc, #12582912	; 0xc00000
d0014788:	f7fb4419 			; <UNDEFINED> instruction: 0xf7fb4419
d001478c:	2800ffd0 	stmdacs	r0, {r4, r6, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0014790:	f1bad13a 			; <UNDEFINED> instruction: 0xf1bad13a
d0014794:	d1230f00 			; <UNDEFINED> instruction: 0xd1230f00
d0014798:	447a4a51 	ldrbtmi	r4, [sl], #-2641	; 0xfffff5af
d001479c:	447b4b51 	ldrbtmi	r4, [fp], #-2897	; 0xfffff4af
d00147a0:	29006d99 	stmdbcs	r0, {r0, r3, r4, r7, r8, sl, fp, sp, lr}
d00147a4:	adfaf47f 	cfldrdge	mvd15, [sl, #508]!	; 0x1fc
d00147a8:	f895e69a 			; <UNDEFINED> instruction: 0xf895e69a
d00147ac:	b1933264 	orrslt	r3, r3, r4, ror #4
d00147b0:	2266f895 	rsbcs	pc, r6, #9764864	; 0x950000
d00147b4:	429a7a33 	addsmi	r7, sl, #208896	; 0x33000
d00147b8:	e9d9d00d 	ldmib	r9, {r0, r2, r3, ip, lr, pc}^
d00147bc:	e9d52300 	ldmib	r5, {r8, r9, sp}^
d00147c0:	f7fb0100 			; <UNDEFINED> instruction: 0xf7fb0100
d00147c4:	b130ff7d 	teqlt	r0, sp, ror pc	; <UNPREDICTABLE>
d00147c8:	46484629 	strbmi	r4, [r8], -r9, lsr #12
d00147cc:	ffaff7fb 			; <UNDEFINED> instruction: 0xffaff7fb
d00147d0:	4644b108 	strbmi	fp, [r4], -r8, lsl #2
d00147d4:	f108e7ce 			; <UNDEFINED> instruction: 0xf108e7ce
d00147d8:	f5050801 			; <UNDEFINED> instruction: 0xf5050801
d00147dc:	e7c2751a 	bfi	r7, sl, (invalid: 10:2)
d00147e0:	447a4a41 	ldrbtmi	r4, [sl], #-2625	; 0xfffff5bf
d00147e4:	f1bbe7da 			; <UNDEFINED> instruction: 0xf1bbe7da
d00147e8:	db140f00 	blle	0xd05183f0
d00147ec:	f44f483f 	vst2.8	{d20-d21}, [pc :256]
d00147f0:	465c721a 			; <UNDEFINED> instruction: 0x465c721a
d00147f4:	44784639 	ldrbtmi	r4, [r8], #-1593	; 0xfffff9c7
d00147f8:	000bfb02 	andeq	pc, fp, r2, lsl #22
d00147fc:	3067f500 	rsbcc	pc, r7, r0, lsl #10
d0014800:	70e4f500 	rscvc	pc, r4, r0, lsl #10
d0014804:	fb88f00c 	blx	0xce25083e
d0014808:	f50d4620 			; <UNDEFINED> instruction: 0xf50d4620
d001480c:	e8bd7d33 	pop	{r0, r1, r4, r5, r8, sl, fp, ip, sp, lr}
d0014810:	b0044ff0 	strdlt	r4, [r4], -r0
d0014814:	48364770 	ldmdami	r6!, {r4, r5, r6, r8, r9, sl, lr}
d0014818:	f5004478 			; <UNDEFINED> instruction: 0xf5004478
d001481c:	f8d33375 			; <UNDEFINED> instruction: 0xf8d33375
d0014820:	2c184388 	ldccs	3, cr4, [r8], {136}	; 0x88
d0014824:	6d83d10f 	stfvsd	f5, [r3, #60]	; 0x3c
d0014828:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001482c:	4b31adb7 	blmi	0xd0c7ff10
d0014830:	6583447b 	strvs	r4, [r3, #1147]	; 0x47b
d0014834:	65c39b00 	strbvs	r9, [r3, #2816]	; 0xb00
d0014838:	66039b01 	strvs	r9, [r3], -r1, lsl #22
d001483c:	66439b02 	strbvs	r9, [r3], -r2, lsl #22
d0014840:	66839b03 	strvs	r9, [r3], r3, lsl #22
d0014844:	1c62e5aa 	cfstr64ne	mvdx14, [r2], #-680	; 0xfffffd58
d0014848:	f8c34639 			; <UNDEFINED> instruction: 0xf8c34639
d001484c:	f44f2388 	vst2.32	{d18-d21}, [pc], r8
d0014850:	fb02721a 	blx	0xd00b10c2
d0014854:	f5000004 			; <UNDEFINED> instruction: 0xf5000004
d0014858:	f5003067 			; <UNDEFINED> instruction: 0xf5003067
d001485c:	f00c70e4 			; <UNDEFINED> instruction: 0xf00c70e4
d0014860:	e7d1fb5b 			; <UNDEFINED> instruction: 0xe7d1fb5b
d0014864:	f6ff2c00 			; <UNDEFINED> instruction: 0xf6ff2c00
d0014868:	f04fadc1 			; <UNDEFINED> instruction: 0xf04fadc1
d001486c:	e5ea3bff 	strb	r3, [sl, #3071]!	; 0xbff
d0014870:	00013726 	andeq	r3, r1, r6, lsr #14
d0014874:	fffffe63 			; <UNDEFINED> instruction: 0xfffffe63
d0014878:	fffffe32 			; <UNDEFINED> instruction: 0xfffffe32
d001487c:	fffffe33 			; <UNDEFINED> instruction: 0xfffffe33
d0014880:	0001361a 	andeq	r3, r1, sl, lsl r6
d0014884:	000135f4 	strdeq	r3, [r1], -r4
d0014888:	fffffe6d 			; <UNDEFINED> instruction: 0xfffffe6d
d001488c:	000135c2 	andeq	r3, r1, r2, asr #11
d0014890:	fffffe52 			; <UNDEFINED> instruction: 0xfffffe52
d0014894:	fffffd4d 			; <UNDEFINED> instruction: 0xfffffd4d
d0014898:	00013566 	andeq	r3, r1, r6, ror #10
d001489c:	fffffd19 			; <UNDEFINED> instruction: 0xfffffd19
d00148a0:	000134f2 	strdeq	r3, [r1], -r2
d00148a4:	000134de 	ldrdeq	r3, [r1], -lr
d00148a8:	fffffb6a 			; <UNDEFINED> instruction: 0xfffffb6a
d00148ac:	000134c8 	andeq	r3, r1, r8, asr #9
d00148b0:	fffffb12 			; <UNDEFINED> instruction: 0xfffffb12
d00148b4:	000134ba 			; <UNDEFINED> instruction: 0x000134ba
d00148b8:	fffffcad 			; <UNDEFINED> instruction: 0xfffffcad
d00148bc:	fffffca2 			; <UNDEFINED> instruction: 0xfffffca2
d00148c0:	00013444 	andeq	r3, r1, r4, asr #8
d00148c4:	0001342e 	andeq	r3, r1, lr, lsr #8
d00148c8:	fffffc72 			; <UNDEFINED> instruction: 0xfffffc72
d00148cc:	fffffb07 			; <UNDEFINED> instruction: 0xfffffb07
d00148d0:	00013400 	andeq	r3, r1, r0, lsl #8
d00148d4:	fffffacd 			; <UNDEFINED> instruction: 0xfffffacd
d00148d8:	0001333e 	andeq	r3, r1, lr, lsr r3
d00148dc:	00013316 	andeq	r3, r1, r6, lsl r3
d00148e0:	fffffa31 			; <UNDEFINED> instruction: 0xfffffa31
d00148e4:	000132f6 	strdeq	r3, [r1], -r6
d00148e8:	fffff9cc 			; <UNDEFINED> instruction: 0xfffff9cc
d00148ec:	0001329e 	muleq	r1, lr, r2
d00148f0:	0001327c 	andeq	r3, r1, ip, ror r2
d00148f4:	fffffa05 			; <UNDEFINED> instruction: 0xfffffa05

Disassembly of section .text.accept_sdk_type.constprop.0:

d00148f8 <.text.accept_sdk_type.constprop.0>:
d00148f8:	4c0cb538 	cfstr32mi	mvfx11, [ip], {56}	; 0x38
d00148fc:	031cf24d 	tsteq	ip, #-805306364	; 0xd0000004	; <UNPREDICTABLE>
d0014900:	447c4602 	ldrbtmi	r4, [ip], #-1538	; 0xfffff9fe
d0014904:	b17b58e3 	cmnlt	fp, r3, ror #17
d0014908:	f2406ae5 	vpmax.s8	q11, q8, <illegal reg q10.5>
d001490c:	429d1301 	addsmi	r1, sp, #67108864	; 0x4000000
d0014910:	e9d4d10a 	ldmib	r4, {r1, r3, r8, ip, lr, pc}^
d0014914:	f7fb0106 			; <UNDEFINED> instruction: 0xf7fb0106
d0014918:	b128fffb 	strdlt	pc, [r8, -fp]!
d001491c:	46204629 	strtmi	r4, [r0], -r9, lsr #12
d0014920:	4038e8bd 	ldrhtmi	lr, [r8], -sp
d0014924:	badef7fe 	blt	0xcf7d2924
d0014928:	bd382000 	ldclt	0, cr2, [r8, #-0]
d001492c:	00013192 	muleq	r1, r2, r1

Disassembly of section .text.stream_read.constprop.0:

d0014950 <.text.stream_read.constprop.0>:
d0014950:	4c0fb537 	cfstr32mi	mvfx11, [pc], {55}	; 0x37
d0014954:	6da4447c 	cfstrsvs	mvf4, [r4, #496]!	; 0x1f0
d0014958:	4c0eb94c 			; <UNDEFINED> instruction: 0x4c0eb94c
d001495c:	6824447c 	stmdavs	r4!, {r2, r3, r4, r5, r6, sl, lr}
d0014960:	490db93c 	stmdbmi	sp, {r2, r3, r4, r5, r8, fp, ip, sp, pc}
d0014964:	4479480d 	ldrbtmi	r4, [r9], #-2061	; 0xfffff7f3
d0014968:	f7fb4478 			; <UNDEFINED> instruction: 0xf7fb4478
d001496c:	2000fc6f 	andcs	pc, r0, pc, ror #24
d0014970:	68a5e00b 	stmiavs	r5!, {r0, r1, r3, sp, lr, pc}
d0014974:	d0f42d00 	rscsle	r2, r4, r0, lsl #26
d0014978:	46139300 	ldrmi	r9, [r3], -r0, lsl #6
d001497c:	4601460a 	strmi	r4, [r1], -sl, lsl #12
d0014980:	47a86820 	strmi	r6, [r8, r0, lsr #16]!
d0014984:	d0ec2800 	rscle	r2, ip, r0, lsl #16
d0014988:	b0032001 	andlt	r2, r3, r1
d001498c:	bf00bd30 	svclt	0x0000bd30
d0014990:	00013140 	andeq	r3, r1, r0, asr #2
d0014994:	0005e3f4 	strdeq	lr, [r5], -r4
d0014998:	ffffffc6 			; <UNDEFINED> instruction: 0xffffffc6
d001499c:	0001312c 	andeq	r3, r1, ip, lsr #2

Disassembly of section .text.stream_write.constprop.0:

d00149c0 <.text.stream_write.constprop.0>:
d00149c0:	4c0fb537 	cfstr32mi	mvfx11, [pc], {55}	; 0x37
d00149c4:	6da4447c 	cfstrsvs	mvf4, [r4, #496]!	; 0x1f0
d00149c8:	4c0eb94c 			; <UNDEFINED> instruction: 0x4c0eb94c
d00149cc:	6824447c 	stmdavs	r4!, {r2, r3, r4, r5, r6, sl, lr}
d00149d0:	490db93c 	stmdbmi	sp, {r2, r3, r4, r5, r8, fp, ip, sp, pc}
d00149d4:	4479480d 	ldrbtmi	r4, [r9], #-2061	; 0xfffff7f3
d00149d8:	f7fb4478 			; <UNDEFINED> instruction: 0xf7fb4478
d00149dc:	2000fc37 	andcs	pc, r0, r7, lsr ip	; <UNPREDICTABLE>
d00149e0:	6865e00b 	stmdavs	r5!, {r0, r1, r3, sp, lr, pc}^
d00149e4:	d0f42d00 	rscsle	r2, r4, r0, lsl #26
d00149e8:	46139300 	ldrmi	r9, [r3], -r0, lsl #6
d00149ec:	4601460a 	strmi	r4, [r1], -sl, lsl #12
d00149f0:	47a86820 	strmi	r6, [r8, r0, lsr #16]!
d00149f4:	d0ec2800 	rscle	r2, ip, r0, lsl #16
d00149f8:	b0032001 	andlt	r2, r3, r1
d00149fc:	bf00bd30 	svclt	0x0000bd30
d0014a00:	000130d0 	ldrdeq	r3, [r1], -r0
d0014a04:	0005e384 	andeq	lr, r5, r4, lsl #7
d0014a08:	ffffffc6 			; <UNDEFINED> instruction: 0xffffffc6
d0014a0c:	000130bc 	strheq	r3, [r1], -ip

Disassembly of section .text.image_write.constprop.0:

d0014a48 <.text.image_write.constprop.0>:
d0014a48:	0fbef5b0 	svceq	0x00bef5b0
d0014a4c:	f5c0d803 			; <UNDEFINED> instruction: 0xf5c0d803
d0014a50:	429303be 	addsmi	r0, r3, #-134217726	; 0xf8000002
d0014a54:	4906d205 	stmdbmi	r6, {r0, r2, r9, ip, lr, pc}
d0014a58:	44794806 	ldrbtmi	r4, [r9], #-2054	; 0xfffff7fa
d0014a5c:	f7fb4478 			; <UNDEFINED> instruction: 0xf7fb4478
d0014a60:	4613bbf5 			; <UNDEFINED> instruction: 0x4613bbf5
d0014a64:	f100460a 			; <UNDEFINED> instruction: 0xf100460a
d0014a68:	20000140 	andcs	r0, r0, r0, asr #2
d0014a6c:	bfa8f7ff 	svclt	0x00a8f7ff
d0014a70:	ffffffb2 			; <UNDEFINED> instruction: 0xffffffb2
d0014a74:	00013038 	andeq	r3, r1, r8, lsr r0

Disassembly of section .text.put16:

d0014a78 <.text.put16>:
d0014a78:	2202b507 	andcs	fp, r2, #29360128	; 0x1c00000
d0014a7c:	1004f8ad 	andne	pc, r4, sp, lsr #17
d0014a80:	f7ffa901 			; <UNDEFINED> instruction: 0xf7ffa901
d0014a84:	b003ffe1 	andlt	pc, r3, r1, ror #31
d0014a88:	fb04f85d 	blx	0xd0152c06

Disassembly of section .text.emit:

d0014ab0 <.text.emit>:
d0014ab0:	b5106d83 	ldrlt	r6, [r0, #-3459]	; 0xfffff27d
d0014ab4:	f500b9a3 			; <UNDEFINED> instruction: 0xf500b9a3
d0014ab8:	4a0a348f 	bmi	0xd02a1cfc
d0014abc:	31b8f8d4 			; <UNDEFINED> instruction: 0x31b8f8d4
d0014ac0:	d9054293 	stmdble	r5, {r0, r1, r4, r7, r9, lr}
d0014ac4:	e8bd4908 	pop	{r3, r8, fp, lr}
d0014ac8:	44794010 	ldrbtmi	r4, [r9], #-16
d0014acc:	bbbef7fb 	bllt	0xcefd2ac0
d0014ad0:	f7ff4618 			; <UNDEFINED> instruction: 0xf7ff4618
d0014ad4:	f8d4ffd1 			; <UNDEFINED> instruction: 0xf8d4ffd1
d0014ad8:	330231b8 	movwcc	r3, #8632	; 0x21b8
d0014adc:	31b8f8c4 			; <UNDEFINED> instruction: 0x31b8f8c4
d0014ae0:	bf00bd10 	svclt	0x0000bd10
d0014ae4:	005efffe 	ldrsheq	pc, [lr], #-254	; 0xffffff02	; <UNPREDICTABLE>
d0014ae8:	ffffffbe 			; <UNDEFINED> instruction: 0xffffffbe

Disassembly of section .text.load_local:

d0014aec <.text.load_local>:
d0014aec:	b570291f 	ldrblt	r2, [r0, #-2335]!	; 0xfffff6e1
d0014af0:	b2944606 	addslt	r4, r4, #6291456	; 0x600000
d0014af4:	d80ab28d 	stmdale	sl, {r0, r2, r3, r7, r9, ip, sp, pc}
d0014af8:	1185ea44 	orrne	lr, r5, r4, asr #20
d0014afc:	41d0f441 	bicsmi	pc, r0, r1, asr #8
d0014b00:	0138f041 	teqeq	r8, r1, asr #32	; <UNPREDICTABLE>
d0014b04:	e8bdb289 	pop	{r0, r3, r7, r9, ip, sp, pc}
d0014b08:	f7ff4070 			; <UNDEFINED> instruction: 0xf7ff4070
d0014b0c:	f64fbfd1 			; <UNDEFINED> instruction: 0xf64fbfd1
d0014b10:	f7ff01d7 			; <UNDEFINED> instruction: 0xf7ff01d7
d0014b14:	4630ffcd 	ldrtmi	pc, [r0], -sp, asr #31	; <UNPREDICTABLE>
d0014b18:	ea4100a9 	b	0xd1054dc4
d0014b1c:	b2893104 	addlt	r3, r9, #4, 2
d0014b20:	Address 0x00000000d0014b20 is out of bounds.


Disassembly of section .text.store_local:

d0014b22 <.text.store_local>:
d0014b22:	b570291f 	ldrblt	r2, [r0, #-2335]!	; 0xfffff6e1
d0014b26:	b2944606 	addslt	r4, r4, #6291456	; 0x600000
d0014b2a:	d80ab28d 	stmdale	sl, {r0, r2, r3, r7, r9, ip, sp, pc}
d0014b2e:	1185ea44 	orrne	lr, r5, r4, asr #20
d0014b32:	41c0f441 	bicmi	pc, r0, r1, asr #8
d0014b36:	0138f041 	teqeq	r8, r1, asr #32	; <UNPREDICTABLE>
d0014b3a:	e8bdb289 	pop	{r0, r3, r7, r9, ip, sp, pc}
d0014b3e:	f7ff4070 			; <UNDEFINED> instruction: 0xf7ff4070
d0014b42:	f64fbfb6 			; <UNDEFINED> instruction: 0xf64fbfb6
d0014b46:	f7ff01c7 			; <UNDEFINED> instruction: 0xf7ff01c7
d0014b4a:	4630ffb2 			; <UNDEFINED> instruction: 0x4630ffb2
d0014b4e:	ea4100a9 	b	0xd1054dfa
d0014b52:	b2893104 	addlt	r3, r9, #4, 2
d0014b56:	Address 0x00000000d0014b56 is out of bounds.


Disassembly of section .text.emit_address:

d0014b80 <.text.emit_address>:
d0014b80:	460db570 			; <UNDEFINED> instruction: 0x460db570
d0014b84:	315ff500 	cmpcc	pc, r0, lsl #10	; <UNPREDICTABLE>
d0014b88:	f8d14604 			; <UNDEFINED> instruction: 0xf8d14604
d0014b8c:	f5b333c0 			; <UNDEFINED> instruction: 0xf5b333c0
d0014b90:	d1056f00 	tstle	r5, r0, lsl #30
d0014b94:	e8bd4918 	pop	{r3, r4, r8, fp, lr}
d0014b98:	44794070 	ldrbtmi	r4, [r9], #-112	; 0xffffff90
d0014b9c:	bb56f7fb 	bllt	0xd15d2b90
d0014ba0:	26041c58 			; <UNDEFINED> instruction: 0x26041c58
d0014ba4:	03c0f8c1 	biceq	pc, r0, #12648448	; 0xc10000
d0014ba8:	fb01210c 	blx	0xd005cfe2
d0014bac:	f5044303 			; <UNDEFINED> instruction: 0xf5044303
d0014bb0:	f503318f 			; <UNDEFINED> instruction: 0xf503318f
d0014bb4:	f8d13347 			; <UNDEFINED> instruction: 0xf8d13347
d0014bb8:	f8c311b8 			; <UNDEFINED> instruction: 0xf8c311b8
d0014bbc:	f8c323c4 			; <UNDEFINED> instruction: 0xf8c323c4
d0014bc0:	f88313c0 			; <UNDEFINED> instruction: 0xf88313c0
d0014bc4:	210053c8 	smlabtcs	r0, r8, r3, r5
d0014bc8:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0014bcc:	3e01ff71 	mcrcc	15, 0, pc, cr1, cr1, {3}	; <UNPREDICTABLE>
d0014bd0:	4620d1f9 			; <UNDEFINED> instruction: 0x4620d1f9
d0014bd4:	4122f44f 	msrmi	CPSR_x, pc, asr #8
d0014bd8:	ff6af7ff 			; <UNDEFINED> instruction: 0xff6af7ff
d0014bdc:	bf0c2d01 	svclt	0x000c2d01
d0014be0:	21002141 	tstcs	r0, r1, asr #2
d0014be4:	f4414620 	vst1.8	{d20-d22}, [r1 :128], r0
d0014be8:	e8bd51c0 	pop	{r6, r7, r8, ip, lr}
d0014bec:	f0414070 			; <UNDEFINED> instruction: 0xf0414070
d0014bf0:	f7ff0110 			; <UNDEFINED> instruction: 0xf7ff0110
d0014bf4:	bf00bf5d 	svclt	0x0000bf5d
d0014bf8:	ffffffba 			; <UNDEFINED> instruction: 0xffffffba

Disassembly of section .text.branch:

d0014bfc <.text.branch>:
d0014bfc:	f500b538 			; <UNDEFINED> instruction: 0xf500b538
d0014c00:	4604338f 	strmi	r3, [r4], -pc, lsl #7
d0014c04:	f8d32100 			; <UNDEFINED> instruction: 0xf8d32100
d0014c08:	f7ff51b8 			; <UNDEFINED> instruction: 0xf7ff51b8
d0014c0c:	4620ff51 	qsaxmi	pc, r0, r1	; <UNPREDICTABLE>
d0014c10:	f7ff2100 			; <UNDEFINED> instruction: 0xf7ff2100
d0014c14:	4628ff4d 	strtmi	pc, [r8], -sp, asr #30
d0014c18:	Address 0x00000000d0014c18 is out of bounds.


Disassembly of section .text.branch_on_value:

d0014c1a <.text.branch_on_value>:
d0014c1a:	460db538 			; <UNDEFINED> instruction: 0x460db538
d0014c1e:	5120f44f 	msrpl	CPSR_, pc, asr #8
d0014c22:	f7ff4604 			; <UNDEFINED> instruction: 0xf7ff4604
d0014c26:	f24dff44 	vmax.f32	<illegal reg q15.5>, <illegal reg q6.5>, q2
d0014c2a:	f24d1301 	vcgt.s8	d17, d13, d1
d0014c2e:	46200101 	strtmi	r0, [r0], -r1, lsl #2
d0014c32:	bf082d00 	svclt	0x00082d00
d0014c36:	f7ff4619 			; <UNDEFINED> instruction: 0xf7ff4619
d0014c3a:	4620ff3a 	qasxmi	pc, r0, sl	; <UNPREDICTABLE>
d0014c3e:	4038e8bd 	ldrhtmi	lr, [r8], -sp
d0014c42:	bfdbf7ff 	svclt	0x00dbf7ff

Disassembly of section .text.boolean:

d0014c46 <.text.boolean>:
d0014c46:	0301f24d 	movweq	pc, #4685	; 0x124d	; <UNPREDICTABLE>
d0014c4a:	2101ea43 	tstcs	r1, r3, asr #20
d0014c4e:	4604b510 			; <UNDEFINED> instruction: 0x4604b510
d0014c52:	f7ffb289 			; <UNDEFINED> instruction: 0xf7ffb289
d0014c56:	f44fff2c 			; <UNDEFINED> instruction: 0xf44fff2c
d0014c5a:	46205100 	strtmi	r5, [r0], -r0, lsl #2
d0014c5e:	ff27f7ff 			; <UNDEFINED> instruction: 0xff27f7ff
d0014c62:	f44f4620 	vst1.8	{d20-d22}, [pc :128], r0
d0014c66:	f7ff4160 			; <UNDEFINED> instruction: 0xf7ff4160
d0014c6a:	4620ff22 	strtmi	pc, [r0], -r2, lsr #30
d0014c6e:	0101f242 	tsteq	r1, r2, asr #4	; <UNPREDICTABLE>
d0014c72:	4010e8bd 			; <UNDEFINED> instruction: 0x4010e8bd
d0014c76:	bf1bf7ff 	svclt	0x001bf7ff

Disassembly of section .text.prepare_call:

d0014c7a <.text.prepare_call>:
d0014c7a:	e92d2904 	push	{r2, r8, fp, sp}
d0014c7e:	460d43f8 			; <UNDEFINED> instruction: 0x460d43f8
d0014c82:	2504bf38 	strcs	fp, [r4, #-3896]	; 0xfffff0c8
d0014c86:	460c4607 	strmi	r4, [ip], -r7, lsl #12
d0014c8a:	f0353d03 			; <UNDEFINED> instruction: 0xf0353d03
d0014c8e:	d0060501 	andle	r0, r6, r1, lsl #10
d0014c92:	4130f445 	teqmi	r0, r5, asr #8	; <UNPREDICTABLE>
d0014c96:	0180f041 	orreq	pc, r0, r1, asr #32
d0014c9a:	f7ffb289 			; <UNDEFINED> instruction: 0xf7ffb289
d0014c9e:	1f66ff08 	svcne	0x0066ff08
d0014ca2:	0904f04f 	stmdbeq	r4, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d0014ca6:	0846ea4f 	stmdaeq	r6, {r0, r1, r2, r3, r6, r9, fp, sp, lr, pc}^
d0014caa:	0646eb05 	strbeq	lr, [r6], -r5, lsl #22
d0014cae:	45a1b2b6 	strmi	fp, [r1, #694]!	; 0x2b6
d0014cb2:	f108d30c 			; <UNDEFINED> instruction: 0xf108d30c
d0014cb6:	f04f0608 			; <UNDEFINED> instruction: 0xf04f0608
d0014cba:	442e0800 	strtmi	r0, [lr], #-2048	; 0xfffff800
d0014cbe:	45a0b2b6 	strmi	fp, [r0, #694]!	; 0x2b6
d0014cc2:	f1b8d027 			; <UNDEFINED> instruction: 0xf1b8d027
d0014cc6:	d1130f04 	tstle	r3, r4, lsl #30
d0014cca:	e02abb25 	eor	fp, sl, r5, lsr #22
d0014cce:	4118f446 	tstmi	r8, r6, asr #8	; <UNPREDICTABLE>
d0014cd2:	f7ff4638 			; <UNDEFINED> instruction: 0xf7ff4638
d0014cd6:	f1a9feec 			; <UNDEFINED> instruction: 0xf1a9feec
d0014cda:	3e020104 	adfccs	f0, f2, f4
d0014cde:	f4414638 	vst1.8	{d20-d22}, [r1 :256], r8
d0014ce2:	f1094110 			; <UNDEFINED> instruction: 0xf1094110
d0014ce6:	b2b60901 	adcslt	r0, r6, #16384	; 0x4000
d0014cea:	f7ffb289 			; <UNDEFINED> instruction: 0xf7ffb289
d0014cee:	e7defee0 	ldrb	pc, [lr, r0, ror #29]	; <UNPREDICTABLE>
d0014cf2:	f388fa1f 	vmovl.u8	<illegal reg q7.5>, d15
d0014cf6:	f1084638 			; <UNDEFINED> instruction: 0xf1084638
d0014cfa:	ebc30801 	bl	0xcf0d6d06
d0014cfe:	eb0631c3 	bl	0xd01a1412
d0014d02:	ea410141 	b	0xd105520e
d0014d06:	f4412103 	vst4.8	{d18,d20,d22,d24}, [r1], r3
d0014d0a:	b2894118 	addlt	r4, r9, #24, 2
d0014d0e:	fecff7ff 	mcr2	7, 6, pc, cr15, cr15, {7}	; <UNPREDICTABLE>
d0014d12:	b125e7d5 	ldrdlt	lr, [r5, -r5]!
d0014d16:	0444eb05 	strbeq	lr, [r4], #-2821	; 0xfffff4fb
d0014d1a:	e8bd4620 	pop	{r5, r9, sl, lr}
d0014d1e:	2c0083f8 	stccs	3, cr8, [r0], {248}	; 0xf8
d0014d22:	0061d0fa 	strdeq	sp, [r1], #-10	; <UNPREDICTABLE>
d0014d26:	24004638 	strcs	r4, [r0], #-1592	; 0xfffff9c8
d0014d2a:	4130f441 	teqmi	r0, r1, asr #8	; <UNPREDICTABLE>
d0014d2e:	f7ffb289 			; <UNDEFINED> instruction: 0xf7ffb289
d0014d32:	e7f1febe 			; <UNDEFINED> instruction: 0xe7f1febe

Disassembly of section .text.binary:

d0014d36 <.text.binary>:
d0014d36:	b570292f 	ldrblt	r2, [r0, #-2351]!	; 0xfffff6d1
d0014d3a:	460e4604 	strmi	r4, [lr], -r4, lsl #12
d0014d3e:	dc0d4615 	stcle	6, cr4, [sp], {21}
d0014d42:	dd102924 	vldrle.16	s4, [r0, #-72]	; 0xffffffb8	; <UNPREDICTABLE>
d0014d46:	0325f1a1 	msreq	CPSR_sc, #1073741864	; 0x40000028
d0014d4a:	d80c2b0a 	stmdale	ip, {r1, r3, r8, r9, fp, sp}
d0014d4e:	f003e8df 			; <UNDEFINED> instruction: 0xf003e8df
d0014d52:	0b0b4058 	bleq	0xd02e4eba
d0014d56:	0b363d0b 	bleq	0xd0da418a
d0014d5a:	004c0b6b 	subeq	r0, ip, fp, ror #22
d0014d5e:	d03a297c 	eorsle	r2, sl, ip, ror r9
d0014d62:	295edc12 	ldmdbcs	lr, {r1, r4, sl, fp, ip, lr, pc}^
d0014d66:	f244d03a 	vqadd.s8	d29, d4, d26
d0014d6a:	46202181 	strtmi	r2, [r0], -r1, lsl #3
d0014d6e:	fe9ff7ff 	mrc2	7, 4, pc, cr15, cr15, {7}
d0014d72:	7f90f5b6 	svcvc	0x0090f5b6
d0014d76:	f5b6da06 			; <UNDEFINED> instruction: 0xf5b6da06
d0014d7a:	da577f8e 	ble	0xd15f4bba
d0014d7e:	d06a2e3c 	rsble	r2, sl, ip, lsr lr
d0014d82:	d06d2e3e 	rsble	r2, sp, lr, lsr lr
d0014d86:	e01e2500 	ands	r2, lr, r0, lsl #10
d0014d8a:	7293f46f 	addsvc	pc, r3, #1862270976	; 0x6f000000
d0014d8e:	2b01188b 	blcs	0xd005afc2
d0014d92:	f244d8e9 	vadd.i8	<illegal reg q14.5>, q10, <illegal reg q12.5>
d0014d96:	f7ff6102 			; <UNDEFINED> instruction: 0xf7ff6102
d0014d9a:	f244fe8a 	vceq.f32	d31, d20, d10
d0014d9e:	46206108 	strtmi	r6, [r0], -r8, lsl #2
d0014da2:	fe85f7ff 	mcr2	7, 4, pc, cr5, cr15, {7}	; <UNPREDICTABLE>
d0014da6:	1327f240 	msrne	CPSR_sxc, #64, 4
d0014daa:	d01a429e 	mulsle	sl, lr, r2
d0014dae:	01d0f244 	bicseq	pc, r0, r4, asr #4
d0014db2:	1310f244 	tstne	r0, #68, 4	; 0x40000004	; <UNPREDICTABLE>
d0014db6:	bf082d00 	svclt	0x00082d00
d0014dba:	e0014619 	and	r4, r1, r9, lsl r6
d0014dbe:	0108f641 	tsteq	r8, r1, asr #12	; <UNPREDICTABLE>
d0014dc2:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0014dc6:	4628fe74 			; <UNDEFINED> instruction: 0x4628fe74
d0014dca:	f244bd70 	vmla.f32	<illegal reg q13.5>, q2, q8
d0014dce:	e7f73148 	ldrb	r3, [r7, r8, asr #2]!
d0014dd2:	0108f244 	tsteq	r8, r4, asr #4	; <UNPREDICTABLE>
d0014dd6:	f244e7f4 	vaba.s8	q15, q10, q10
d0014dda:	e7f23108 	ldrb	r3, [r2, r8, lsl #2]!
d0014dde:	0148f244 	cmpeq	r8, r4, asr #4	; <UNPREDICTABLE>
d0014de2:	f244e7ef 	vabd.s8	q15, q10, <illegal reg q15.5>
d0014de6:	e7eb0190 			; <UNDEFINED> instruction: 0xe7eb0190
d0014dea:	3391f64f 	orrscc	pc, r1, #82837504	; 0x4f00000
d0014dee:	31b1f64f 			; <UNDEFINED> instruction: 0x31b1f64f
d0014df2:	bf082d00 	svclt	0x00082d00
d0014df6:	f7ff4619 			; <UNDEFINED> instruction: 0xf7ff4619
d0014dfa:	f24ffe5a 			; <UNDEFINED> instruction: 0xf24ffe5a
d0014dfe:	e7df01f0 			; <UNDEFINED> instruction: 0xe7df01f0
d0014e02:	3391f64f 	orrscc	pc, r1, #82837504	; 0x4f00000
d0014e06:	31b1f64f 			; <UNDEFINED> instruction: 0x31b1f64f
d0014e0a:	bf082d00 	svclt	0x00082d00
d0014e0e:	f7ff4619 			; <UNDEFINED> instruction: 0xf7ff4619
d0014e12:	f24ffe4e 	vceq.f32	<illegal reg q15.5>, <illegal reg q7.5>, q7
d0014e16:	462021f0 			; <UNDEFINED> instruction: 0x462021f0
d0014e1a:	fe49f7ff 	mcr2	7, 2, pc, cr9, cr15, {7}	; <UNPREDICTABLE>
d0014e1e:	3150f244 	cmpcc	r0, r4, asr #4	; <UNPREDICTABLE>
d0014e22:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0014e26:	f641fe44 			; <UNDEFINED> instruction: 0xf641fe44
d0014e2a:	e7c92108 	strb	r2, [r9, r8, lsl #2]
d0014e2e:	738ef46f 	orrvc	pc, lr, #1862270976	; 0x6f000000
d0014e32:	2e02441e 	cfmvdlrcs	mvd2, r4
d0014e36:	e8dfd803 	ldm	pc, {r0, r1, fp, ip, lr, pc}^	; <UNPREDICTABLE>
d0014e3a:	1807f006 	stmdane	r7, {r1, r2, ip, sp, lr, pc}
d0014e3e:	21000009 	tstcs	r0, r9
d0014e42:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0014e46:	e79dfeff 			; <UNDEFINED> instruction: 0xe79dfeff
d0014e4a:	e7f92101 	ldrb	r2, [r9, r1, lsl #2]!
d0014e4e:	bf142d00 	svclt	0x00142d00
d0014e52:	210a2102 	tstcs	sl, r2, lsl #2
d0014e56:	2d00e7f4 	stccs	7, cr14, [r0, #-976]	; 0xfffffc30
d0014e5a:	2103bf14 	tstcs	r3, r4, lsl pc
d0014e5e:	e7ef210b 	strb	r2, [pc, fp, lsl #2]!
d0014e62:	bf142d00 	svclt	0x00142d00
d0014e66:	210c2108 	tstcs	ip, r8, lsl #2
d0014e6a:	2d00e7ea 	stccs	7, cr14, [r0, #-936]	; 0xfffffc58
d0014e6e:	2109bf14 	tstcs	r9, r4, lsl pc
d0014e72:	e7e5210d 	strb	r2, [r5, sp, lsl #2]!

Disassembly of section .text.increment_scalar.isra.0:

d0014ed0 <.text.increment_scalar.isra.0>:
d0014ed0:	4ff8e92d 	svcmi	0x00f8e92d
d0014ed4:	a030f8dd 	ldrsbtge	pc, [r0], -sp	; <UNPREDICTABLE>
d0014ed8:	460d4604 	strmi	r4, [sp], -r4, lsl #12
d0014edc:	46984617 			; <UNDEFINED> instruction: 0x46984617
d0014ee0:	902cf89d 	mlals	ip, sp, r8, pc	; <UNPREDICTABLE>
d0014ee4:	b038f8dd 	ldrsbtlt	pc, [r8], -sp	; <UNPREDICTABLE>
d0014ee8:	fc60f7fb 	stc2l	7, cr15, [r0], #-1004	; 0xfffffc14
d0014eec:	da6f1e06 	ble	0xd1bdc70c
d0014ef0:	4629463a 			; <UNDEFINED> instruction: 0x4629463a
d0014ef4:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0014ef8:	1e07fc79 	mcrne	12, 0, pc, cr7, cr9, {3}	; <UNPREDICTABLE>
d0014efc:	233cdb19 	teqcs	ip, #25600	; 0x6400
d0014f00:	4307fb03 	movwmi	pc, #31491	; 0x7b03	; <UNPREDICTABLE>
d0014f04:	335ff503 	cmpcc	pc, #12582912	; 0xc00000	; <UNPREDICTABLE>
d0014f08:	53ecf893 	mvnpl	pc, #9633792	; 0x930000
d0014f0c:	33f0f893 	mvnscc	pc, #9633792	; 0x930000
d0014f10:	d06a2b00 	rsble	r2, sl, r0, lsl #22
d0014f14:	b1106da0 	tstlt	r0, r0, lsr #27
d0014f18:	e8bd2000 	ldmfd	sp!, {sp}
d0014f1c:	4b3e8ff8 	blmi	0xd0fb8f04
d0014f20:	f8c4447b 			; <UNDEFINED> instruction: 0xf8c4447b
d0014f24:	e9c4a068 	stmib	r4, {r3, r5, r6, sp, pc}^
d0014f28:	9b0a3816 	blls	0xd02a2f88
d0014f2c:	3918e9c4 	ldmdbcc	r8, {r2, r6, r7, r8, fp, sp, lr, pc}
d0014f30:	6da0e7f3 	stcvs	7, cr14, [r0, #972]!	; 0x3cc
d0014f34:	d1ef2800 	mvnle	r2, r0, lsl #16
d0014f38:	447b4b38 	ldrbtmi	r4, [fp], #-2872	; 0xfffff4c8
d0014f3c:	2200e7f1 	andcs	lr, r0, #63176704	; 0x3c40000
d0014f40:	46204631 			; <UNDEFINED> instruction: 0x46204631
d0014f44:	fdd2f7ff 	ldc2l	7, cr15, [r2, #1020]	; 0x3fc
d0014f48:	0f00f1bb 	svceq	0x0000f1bb
d0014f4c:	f24bd004 	vhadd.s8	d29, d11, d4
d0014f50:	46204101 	strtmi	r4, [r0], -r1, lsl #2
d0014f54:	fdacf7ff 	stc2	7, cr15, [ip, #1020]!	; 0x3fc
d0014f58:	1323f240 	msrne	CPSR_xc, #64, 4
d0014f5c:	46209a0d 	strtmi	r9, [r0], -sp, lsl #20
d0014f60:	bf07429a 	svclt	0x0007429a
d0014f64:	0104f243 	tsteq	r4, r3, asr #4	; <UNPREDICTABLE>
d0014f68:	0301f243 	movweq	pc, #4675	; 0x1243	; <UNPREDICTABLE>
d0014f6c:	0104f643 	tsteq	r4, r3, asr #12	; <UNPREDICTABLE>
d0014f70:	0301f643 	movweq	pc, #5699	; 0x1643	; <UNPREDICTABLE>
d0014f74:	bf182d0a 	svclt	0x00182d0a
d0014f78:	f7ff4619 			; <UNDEFINED> instruction: 0xf7ff4619
d0014f7c:	2d05fd99 	stccs	13, cr15, [r5, #-612]	; 0xfffffd9c
d0014f80:	f24bd104 	vrhadd.s8	d29, d11, d4
d0014f84:	462021c0 	strtmi	r2, [r0], -r0, asr #3
d0014f88:	fd92f7ff 	ldc2	7, cr15, [r2, #1020]	; 0x3fc
d0014f8c:	db122e00 	blle	0xd04a0794
d0014f90:	46312200 	ldrtmi	r2, [r1], -r0, lsl #4
d0014f94:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0014f98:	f1bbfdc4 			; <UNDEFINED> instruction: 0xf1bbfdc4
d0014f9c:	d0040f00 	andle	r0, r4, r0, lsl #30
d0014fa0:	4101f64b 	tstmi	r1, fp, asr #12	; <UNPREDICTABLE>
d0014fa4:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0014fa8:	2d0afd83 	stccs	13, cr15, [sl, #-524]	; 0xfffffdf4
d0014fac:	1e6bd00e 	cdpne	0, 6, cr13, cr11, cr14, {0}
d0014fb0:	41584258 	cmpmi	r8, r8, asr r2
d0014fb4:	4620e7b1 			; <UNDEFINED> instruction: 0x4620e7b1
d0014fb8:	2101463a 	tstcs	r1, sl, lsr r6
d0014fbc:	fde0f7ff 	stc2l	7, cr15, [r0, #1020]!	; 0x3fc
d0014fc0:	0108f246 	tsteq	r8, r6, asr #4	; <UNPREDICTABLE>
d0014fc4:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0014fc8:	e7e6fd73 			; <UNDEFINED> instruction: 0xe7e6fd73
d0014fcc:	e7a42004 	str	r2, [r4, r4]!
d0014fd0:	fb032330 	blx	0xd00ddc9a
d0014fd4:	f5034306 			; <UNDEFINED> instruction: 0xf5034306
d0014fd8:	f8932390 			; <UNDEFINED> instruction: 0xf8932390
d0014fdc:	2a002664 	bcs	0xd001e974
d0014fe0:	f893d198 			; <UNDEFINED> instruction: 0xf893d198
d0014fe4:	f04f5659 			; <UNDEFINED> instruction: 0xf04f5659
d0014fe8:	1eaa37ff 	mcrne	7, 5, r3, cr10, cr15, {7}
d0014fec:	d8032a11 	stmdale	r3, {r0, r4, r9, fp, sp}
d0014ff0:	40d34b08 	sbcsmi	r4, r3, r8, lsl #22
d0014ff4:	d49c07da 	ldrle	r0, [ip], #2010	; 0x7da
d0014ff8:	daa02e00 	ble	0xce820800
d0014ffc:	463a4620 	ldrtmi	r4, [sl], -r0, lsr #12
d0015000:	f7ff2101 			; <UNDEFINED> instruction: 0xf7ff2101
d0015004:	f646fdbd 			; <UNDEFINED> instruction: 0xf646fdbd
d0015008:	46200108 	strtmi	r0, [r0], -r8, lsl #2
d001500c:	fd50f7ff 	ldc2l	7, cr15, [r0, #-1020]	; 0xfffffc04
d0015010:	bf00e79a 	svclt	0x0000e79a
d0015014:	0003fef5 	strdeq	pc, [r3], -r5
d0015018:	ffffff52 			; <UNDEFINED> instruction: 0xffffff52
d001501c:	ffffff65 			; <UNDEFINED> instruction: 0xffffff65

Disassembly of section .text.string_argument:

d0015070 <.text.string_argument>:
d0015070:	f2406ac3 	vpmax.s8	q11, q8, <illegal reg q1.5>
d0015074:	42931201 	addsmi	r1, r3, #268435456	; 0x10000000
d0015078:	4ff0e92d 	svcmi	0x00f0e92d
d001507c:	b0894604 	addlt	r4, r9, r4, lsl #12
d0015080:	e9d0d12d 	ldmib	r0, {r0, r2, r3, r5, r8, ip, lr, pc}^
d0015084:	92051206 	andls	r1, r5, #1610612736	; 0x60000000
d0015088:	f7fb9104 			; <UNDEFINED> instruction: 0xf7fb9104
d001508c:	1e05fbaf 	vmlane.f64	d15, d21, d31
d0015090:	9a059904 	bls	0xd017b4a8
d0015094:	4943da05 	stmdbmi	r3, {r0, r2, r9, fp, ip, lr, pc}^
d0015098:	44794620 	ldrbtmi	r4, [r9], #-1568	; 0xfffff9e0
d001509c:	f8d6f7fb 			; <UNDEFINED> instruction: 0xf8d6f7fb
d00150a0:	4620e01a 			; <UNDEFINED> instruction: 0x4620e01a
d00150a4:	fb82f7fb 	blx	0xce0d309a
d00150a8:	daf42800 	ble	0xcfd1f0b0
d00150ac:	fb03233c 	blx	0xd00ddda6
d00150b0:	f5034305 			; <UNDEFINED> instruction: 0xf5034305
d00150b4:	f893335f 			; <UNDEFINED> instruction: 0xf893335f
d00150b8:	2b0733ec 	blcs	0xd01e2070
d00150bc:	4620d1eb 	strtmi	sp, [r0], -fp, ror #3
d00150c0:	fef0f7fd 	mrc2	7, 7, pc, cr0, cr13, {7}
d00150c4:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d00150c8:	f7ff462a 			; <UNDEFINED> instruction: 0xf7ff462a
d00150cc:	f244fd59 	vmla.f32	<illegal reg q15.5>, q2, <illegal reg q4.5>
d00150d0:	46206108 	strtmi	r6, [r0], -r8, lsl #2
d00150d4:	fcecf7ff 	stc2l	7, cr15, [ip], #1020	; 0x3fc
d00150d8:	e8bdb009 	pop	{r0, r3, ip, sp, pc}
d00150dc:	f5b38ff0 			; <UNDEFINED> instruction: 0xf5b38ff0
d00150e0:	d1d87f82 	bicsle	r7, r8, r2, lsl #31
d00150e4:	368ff500 	strcc	pc, [pc], r0, lsl #10
d00150e8:	81bcf8d6 			; <UNDEFINED> instruction: 0x81bcf8d6
d00150ec:	3f00f5b8 	svccc	0x0000f5b8
d00150f0:	f506d02a 			; <UNDEFINED> instruction: 0xf506d02a
d00150f4:	6a6177de 	bvs	0xd1873074
d00150f8:	0b1cf10d 	bleq	0xd0751534
d00150fc:	f8946aa2 			; <UNDEFINED> instruction: 0xf8946aa2
d0015100:	f8d49030 			; <UNDEFINED> instruction: 0xf8d49030
d0015104:	e9d4a034 	ldmib	r4, {r2, r4, r5, sp, pc}^
d0015108:	95075306 	strls	r5, [r7, #-774]	; 0xfffffcfa
d001510c:	9807441d 	stmdals	r7, {r0, r2, r3, r4, sl, lr}
d0015110:	d11c42a8 	tstle	ip, r8, lsr #5
d0015114:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0015118:	6ae3fec5 	bvs	0xcf914c34
d001511c:	7f82f5b3 	svcvc	0x0082f5b3
d0015120:	6da3d102 	stfvsd	f5, [r3, #8]!
d0015124:	d0e62b00 	rscle	r2, r6, r0, lsl #22
d0015128:	31bcf8d6 			; <UNDEFINED> instruction: 0x31bcf8d6
d001512c:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d0015130:	44231c5a 	strtmi	r1, [r3], #-3162	; 0xfffff3a6
d0015134:	338ff503 	orrcc	pc, pc, #12582912	; 0xc00000
d0015138:	21bcf8c6 			; <UNDEFINED> instruction: 0x21bcf8c6
d001513c:	f8834642 			; <UNDEFINED> instruction: 0xf8834642
d0015140:	f7ff11c0 			; <UNDEFINED> instruction: 0xf7ff11c0
d0015144:	e7c7fd1d 	bfi	pc, sp, (invalid: 26:7)	; <UNPREDICTABLE>
d0015148:	44794917 	ldrbtmi	r4, [r9], #-2327	; 0xfffff6e9
d001514c:	683be7a6 	ldmdavs	fp!, {r1, r2, r5, r7, r8, r9, sl, sp, lr, pc}
d0015150:	f5b33301 			; <UNDEFINED> instruction: 0xf5b33301
d0015154:	d30b3f00 	movwle	r3, #48896	; 0xbf00
d0015158:	2b006da3 	blcs	0xd00307ec
d001515c:	4b13d1bc 	blmi	0xd0509854
d0015160:	a068f8c4 	rsbge	pc, r8, r4, asr #17
d0015164:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0015168:	e9c42918 	stmib	r4, {r3, r4, r8, fp, sp}^
d001516c:	e7b33116 			; <UNDEFINED> instruction: 0xe7b33116
d0015170:	93071c43 	movwls	r1, #31811	; 0x7c43
d0015174:	285c7800 	ldmdacs	ip, {fp, ip, sp, lr}^
d0015178:	464bd106 	strbmi	sp, [fp], -r6, lsl #2
d001517c:	95024620 	strls	r4, [r2, #-1568]	; 0xfffff9e0
d0015180:	ab00e9cd 	blge	0xd004f8bc
d0015184:	f9c8f7fb 			; <UNDEFINED> instruction: 0xf9c8f7fb
d0015188:	2b006da3 	blcs	0xd003081c
d001518c:	683bd1a4 	ldmdavs	fp!, {r2, r5, r7, r8, ip, lr, pc}
d0015190:	0c01f103 	stfeqd	f7, [r1], {3}
d0015194:	f5034423 			; <UNDEFINED> instruction: 0xf5034423
d0015198:	f8c7338f 			; <UNDEFINED> instruction: 0xf8c7338f
d001519c:	f883c000 			; <UNDEFINED> instruction: 0xf883c000
d00151a0:	e7b401c0 	ldr	r0, [r4, r0, asr #3]!
d00151a4:	ffffff82 			; <UNDEFINED> instruction: 0xffffff82
d00151a8:	ffffff04 			; <UNDEFINED> instruction: 0xffffff04
d00151ac:	fffffeea 			; <UNDEFINED> instruction: 0xfffffeea

Disassembly of section .text.copy_record.constprop.0:

d00151b0 <.text.copy_record.constprop.0>:
d00151b0:	4e0fb5f8 	mcrmi	5, 0, fp, cr15, cr8, {7}
d00151b4:	25004607 	strcs	r4, [r0, #-1543]	; 0xfffff9f9
d00151b8:	42bd447e 	adcsmi	r4, sp, #2113929216	; 0x7e000000
d00151bc:	bdf8d100 	ldfltp	f5, [r8]
d00151c0:	f64f00ac 			; <UNDEFINED> instruction: 0xf64f00ac
d00151c4:	463001d0 			; <UNDEFINED> instruction: 0x463001d0
d00151c8:	f4443501 	vst3.8	{d19,d21,d23}, [r4], r1
d00151cc:	f7ff5400 			; <UNDEFINED> instruction: 0xf7ff5400
d00151d0:	4630fc6f 	ldrtmi	pc, [r0], -pc, ror #24	; <UNPREDICTABLE>
d00151d4:	4621b2a4 	strtmi	fp, [r1], -r4, lsr #5
d00151d8:	fc6af7ff 	stc2l	7, cr15, [sl], #-1020	; 0xfffffc04
d00151dc:	01c1f64f 	biceq	pc, r1, pc, asr #12
d00151e0:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d00151e4:	4621fc65 	strtmi	pc, [r1], -r5, ror #24
d00151e8:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d00151ec:	e7e4fc61 	strb	pc, [r4, r1, ror #24]!	; <UNPREDICTABLE>
d00151f0:	000128dc 	ldrdeq	r2, [r1], -ip

Disassembly of section .text.wide_immediate:

d00151f4 <.text.wide_immediate>:
d00151f4:	461cb570 			; <UNDEFINED> instruction: 0x461cb570
d00151f8:	4605085b 			; <UNDEFINED> instruction: 0x4605085b
d00151fc:	f4034616 	vst1.8	{d4-d6}, [r3 :64], r6
d0015200:	ea416380 	b	0xd106e008
d0015204:	43193114 	tstmi	r9, #20, 2
d0015208:	fc36f7ff 	ldc2	7, cr15, [r6], #-1020	; 0xfffffc04
d001520c:	b2e11ca8 	rsclt	r1, r1, #168, 24	; 0xa800
d0015210:	ea410124 	b	0xd10556a8
d0015214:	f4042206 	vst1.8	{d2-d5}, [r4], r6
d0015218:	431444e0 	tstmi	r4, #224, 8	; 0xe0000000
d001521c:	e8bdb2a1 	pop	{r0, r5, r7, r9, ip, sp, pc}
d0015220:	f7ff4070 			; <UNDEFINED> instruction: 0xf7ff4070
d0015224:	Address 0x00000000d0015224 is out of bounds.


Disassembly of section .text.load_constant:

d0015226 <.text.load_constant>:
d0015226:	e92d2aff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r9, fp, sp}
d001522a:	460541f0 			; <UNDEFINED> instruction: 0x460541f0
d001522e:	4614460e 	ldrmi	r4, [r4], -lr, lsl #12
d0015232:	2907d80a 	stmdbcs	r7, {r1, r3, fp, ip, lr, pc}
d0015236:	ea42d808 	b	0xd10cb25e
d001523a:	f4412101 	vst4.8	{d18,d20,d22,d24}, [r1], r1
d001523e:	e8bd5100 	pop	{r8, ip, lr}
d0015242:	b28941f0 	addlt	r4, r9, #240, 2	; 0x3c
d0015246:	bc33f7ff 	ldclt	7, cr15, [r3], #-1020	; 0xfffffc04
d001524a:	338ff505 	orrcc	pc, pc, #20971520	; 0x1400000
d001524e:	46282100 	strtmi	r2, [r8], -r0, lsl #2
d0015252:	71b8f8d3 			; <UNDEFINED> instruction: 0x71b8f8d3
d0015256:	fc2bf7ff 	stc2	7, cr15, [fp], #-1020	; 0xfffffc04
d001525a:	46282100 	strtmi	r2, [r8], -r0, lsl #2
d001525e:	fc27f7ff 	stc2	7, cr15, [r7], #-1020	; 0xfffffc04
d0015262:	3f80f5b4 	svccc	0x0080f5b4
d0015266:	2100d307 	tstcs	r0, r7, lsl #6
d001526a:	f7ff4628 			; <UNDEFINED> instruction: 0xf7ff4628
d001526e:	2100fc20 	tstcs	r0, r0, lsr #24	; <UNPREDICTABLE>
d0015272:	f7ff4628 			; <UNDEFINED> instruction: 0xf7ff4628
d0015276:	6dabfc1c 	stcvs	12, cr15, [fp, #112]!	; 0x70
d001527a:	b2a3b9a3 	adclt	fp, r3, #2670592	; 0x28c000
d001527e:	f24f4632 	vmin.s8	d20, d15, d18
d0015282:	46382140 	ldrtmi	r2, [r8], -r0, asr #2
d0015286:	ffb5f7ff 			; <UNDEFINED> instruction: 0xffb5f7ff
d001528a:	3f80f5b4 	svccc	0x0080f5b4
d001528e:	6dabd30a 	stcvs	3, cr13, [fp, #40]!	; 0x28
d0015292:	0c23b943 			; <UNDEFINED> instruction: 0x0c23b943
d0015296:	1d384632 	ldcne	6, cr4, [r8, #-200]!	; 0xffffff38
d001529a:	21c0f24f 	biccs	pc, r0, pc, asr #4
d001529e:	41f0e8bd 	ldrhmi	lr, [r0, #141]!	; 0x8d
d00152a2:	bfa7f7ff 	svclt	0x00a7f7ff
d00152a6:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d

Disassembly of section .text.constant:

d00152aa <.text.constant>:
d00152aa:	2100460a 	tstcs	r0, sl, lsl #12
d00152ae:	bfbaf7ff 	svclt	0x00baf7ff

Disassembly of section .text.null_argument:

d00152b8 <.text.null_argument>:
d00152b8:	f5a36ac3 			; <UNDEFINED> instruction: 0xf5a36ac3
d00152bc:	2a017281 	bcs	0xd0071cc8
d00152c0:	4604b570 			; <UNDEFINED> instruction: 0x4604b570
d00152c4:	6a03d803 	bvs	0xd010b2d8
d00152c8:	2000b1eb 	andcs	fp, r0, fp, ror #3
d00152cc:	f240bd70 	vmla.f32	<illegal reg q13.5>, q0, q8
d00152d0:	42931201 	addsmi	r1, r3, #268435456	; 0x10000000
d00152d4:	4a10d1f9 	bmi	0xd0449ac0
d00152d8:	5606e9d0 			; <UNDEFINED> instruction: 0x5606e9d0
d00152dc:	4631447a 			; <UNDEFINED> instruction: 0x4631447a
d00152e0:	f7fb4628 			; <UNDEFINED> instruction: 0xf7fb4628
d00152e4:	2800fb15 	stmdacs	r0, {r0, r2, r4, r8, r9, fp, ip, sp, lr, pc}
d00152e8:	4632d0ef 	ldrtmi	sp, [r2], -pc, ror #1
d00152ec:	46204629 	strtmi	r4, [r0], -r9, lsr #12
d00152f0:	fa5cf7fb 	blx	0xd17532e4
d00152f4:	dae82800 	ble	0xcfa1f2fc
d00152f8:	46294632 			; <UNDEFINED> instruction: 0x46294632
d00152fc:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0015300:	2800fa75 	stmdacs	r0, {r0, r2, r4, r5, r6, r9, fp, ip, sp, lr, pc}
d0015304:	4620dae1 	strtmi	sp, [r0], -r1, ror #21
d0015308:	fdccf7fd 	stc2l	7, cr15, [ip, #1012]	; 0x3f4
d001530c:	21004620 	tstcs	r0, r0, lsr #12
d0015310:	ffcbf7ff 			; <UNDEFINED> instruction: 0xffcbf7ff
d0015314:	e7d92001 	ldrb	r2, [r9, r1]
d0015318:	ffffffd2 			; <UNDEFINED> instruction: 0xffffffd2

Disassembly of section .text.function_pointer_value.constprop.0:

d00153b0 <.text.function_pointer_value.constprop.0>:
d00153b0:	4ff7e92d 	svcmi	0x00f7e92d
d00153b4:	46054c4a 	strmi	r4, [r5], -sl, asr #24
d00153b8:	4620447c 			; <UNDEFINED> instruction: 0x4620447c
d00153bc:	ff7cf7ff 			; <UNDEFINED> instruction: 0xff7cf7ff
d00153c0:	2126bb98 			; <UNDEFINED> instruction: 0x2126bb98
d00153c4:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d00153c8:	4a46fd8d 	bmi	0xd11d4a04
d00153cc:	f2406b63 	vqdmulh.s<illegal width 8>	q11, q0, <illegal reg q9.5>
d00153d0:	447a1101 	ldrbtmi	r1, [sl], #-257	; 0xfffffeff
d00153d4:	f8d44620 			; <UNDEFINED> instruction: 0xf8d44620
d00153d8:	f8d49024 			; <UNDEFINED> instruction: 0xf8d49024
d00153dc:	f8948028 			; <UNDEFINED> instruction: 0xf8948028
d00153e0:	93017030 	movwls	r7, #4144	; 0x1030
d00153e4:	b606e9d4 			; <UNDEFINED> instruction: 0xb606e9d4
d00153e8:	fd8af7fd 	stc2	7, cr15, [sl, #1012]	; 0x3f4
d00153ec:	4632b1e8 	ldrtmi	fp, [r2], -r8, ror #3
d00153f0:	46204659 			; <UNDEFINED> instruction: 0x46204659
d00153f4:	f9daf7fb 			; <UNDEFINED> instruction: 0xf9daf7fb
d00153f8:	0a00f1b0 	beq	0xd0051ac0
d00153fc:	2030db34 	eorscs	sp, r0, r4, lsr fp
d0015400:	f00afb00 			; <UNDEFINED> instruction: 0xf00afb00
d0015404:	f5031823 			; <UNDEFINED> instruction: 0xf5031823
d0015408:	f8932390 			; <UNDEFINED> instruction: 0xf8932390
d001540c:	2a0c2659 	bcs	0xd031ed78
d0015410:	4b35d00e 	blmi	0xd0d89450
d0015414:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d0015418:	4a34b93a 	bmi	0xd0d43908
d001541c:	e9c3447a 	stmib	r3, {r1, r3, r4, r5, r6, sl, lr}^
d0015420:	9a012916 	bls	0xd005f880
d0015424:	8718e9c3 	ldrhi	lr, [r8, -r3, asr #19]
d0015428:	b003669a 	mullt	r3, sl, r6
d001542c:	8ff0e8bd 	svchi	0x00f0e8bd
d0015430:	f8937829 			; <UNDEFINED> instruction: 0xf8937829
d0015434:	428a265b 	addmi	r2, sl, #95420416	; 0x5b00000
d0015438:	f893d1eb 			; <UNDEFINED> instruction: 0xf893d1eb
d001543c:	786b165c 	stmdavc	fp!, {r2, r3, r4, r6, r9, sl, ip}^
d0015440:	d1e64299 			; <UNDEFINED> instruction: 0xd1e64299
d0015444:	2090f500 	addscs	pc, r0, r0, lsl #10
d0015448:	f2001ca9 			; <UNDEFINED> instruction: 0xf2001ca9
d001544c:	4420605d 	strtmi	r6, [r0], #-93	; 0xffffffa3
d0015450:	fd72f00b 	ldc2l	0, cr15, [r2, #-44]!	; 0xffffffd4
d0015454:	28004602 	stmdacs	r0, {r1, r9, sl, lr}
d0015458:	4651d1db 			; <UNDEFINED> instruction: 0x4651d1db
d001545c:	b0034620 	andlt	r4, r3, r0, lsr #12
d0015460:	4ff0e8bd 	svcmi	0x00f0e8bd
d0015464:	bb42f7ff 	bllt	0xd10d3468
d0015468:	46594632 			; <UNDEFINED> instruction: 0x46594632
d001546c:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0015470:	f1b0fa26 			; <UNDEFINED> instruction: 0xf1b0fa26
d0015474:	db2a0a00 	blle	0xd0a97c7c
d0015478:	46594632 			; <UNDEFINED> instruction: 0x46594632
d001547c:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0015480:	2800f9b5 	stmdacs	r0, {r0, r2, r4, r5, r7, r8, fp, ip, sp, lr, pc}
d0015484:	2338da23 	teqcs	r8, #143360	; 0x23000
d0015488:	f30afb03 	vqrdmulh.s<illegal width 8>	d15, d10, d3
d001548c:	f50118e1 			; <UNDEFINED> instruction: 0xf50118e1
d0015490:	f891317f 			; <UNDEFINED> instruction: 0xf891317f
d0015494:	b9d2224d 	ldmiblt	r2, {r0, r2, r3, r6, r9, sp}^
d0015498:	f8917828 			; <UNDEFINED> instruction: 0xf8917828
d001549c:	4282224c 	addmi	r2, r2, #76, 4	; 0xc0000004
d00154a0:	f891d115 			; <UNDEFINED> instruction: 0xf891d115
d00154a4:	7869024f 	stmdavc	r9!, {r0, r1, r2, r3, r6, r9}^
d00154a8:	d1104288 	tstle	r0, r8, lsl #5
d00154ac:	337ff503 	cmncc	pc, #12582912	; 0xc00000	; <UNPREDICTABLE>
d00154b0:	f2031ca9 			; <UNDEFINED> instruction: 0xf2031ca9
d00154b4:	18e02353 	stmiane	r0!, {r0, r1, r4, r6, r8, r9, sp}^
d00154b8:	fd3ef00b 	ldc2	0, cr15, [lr, #-44]!	; 0xffffffd4
d00154bc:	4652b938 			; <UNDEFINED> instruction: 0x4652b938
d00154c0:	46202102 	strtmi	r2, [r0], -r2, lsl #2
d00154c4:	e8bdb003 	pop	{r0, r1, ip, sp, pc}
d00154c8:	f7ff4ff0 			; <UNDEFINED> instruction: 0xf7ff4ff0
d00154cc:	4b08bb59 	blmi	0xd0244238
d00154d0:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d00154d4:	d1a82a00 			; <UNDEFINED> instruction: 0xd1a82a00
d00154d8:	447a4a06 	ldrbtmi	r4, [sl], #-2566	; 0xfffff5fa
d00154dc:	bf00e79f 	svclt	0x0000e79f
d00154e0:	000126dc 	ldrdeq	r2, [r1], -ip
d00154e4:	ffffff46 			; <UNDEFINED> instruction: 0xffffff46
d00154e8:	00012680 	andeq	r2, r1, r0, lsl #13
d00154ec:	ffffff34 			; <UNDEFINED> instruction: 0xffffff34
d00154f0:	000125c4 	andeq	r2, r1, r4, asr #11
d00154f4:	fffffe9e 			; <UNDEFINED> instruction: 0xfffffe9e

Disassembly of section .text.local_callback_declaration.constprop.0:

d001569c <.text.local_callback_declaration.constprop.0>:
d001569c:	47f0e92d 	ldrbmi	lr, [r0, sp, lsr #18]!
d00156a0:	b0924e62 	addslt	r4, r2, r2, ror #28
d00156a4:	46804a62 	strmi	r4, [r0], r2, ror #20
d00156a8:	2128447e 			; <UNDEFINED> instruction: 0x2128447e
d00156ac:	4630447a 			; <UNDEFINED> instruction: 0x4630447a
d00156b0:	fc26f7fd 	stc2	7, cr15, [r6], #-1012	; 0xfffffc0c
d00156b4:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d00156b8:	4a5e80b5 	bmi	0xd17b5994
d00156bc:	4630212a 	ldrtmi	r2, [r0], -sl, lsr #2
d00156c0:	f7fd447a 			; <UNDEFINED> instruction: 0xf7fd447a
d00156c4:	2800fc1d 	stmdacs	r0, {r0, r2, r3, r4, sl, fp, ip, sp, lr, pc}
d00156c8:	80acf000 	adchi	pc, ip, r0
d00156cc:	0518f106 	ldreq	pc, [r8, #-262]	; 0xfffffefa
d00156d0:	f10dac0a 			; <UNDEFINED> instruction: 0xf10dac0a
d00156d4:	cd0f0928 	vstrgt.16	s0, [pc, #-80]	; 0xd001568c	; <UNPREDICTABLE>
d00156d8:	e895c40f 	ldm	r5, {r0, r1, r2, r3, sl, lr, pc}
d00156dc:	e884000f 	stm	r4, {r0, r1, r2, r3}
d00156e0:	4a55000f 	bmi	0xd1555724
d00156e4:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d00156e8:	447a4630 	ldrbtmi	r4, [sl], #-1584	; 0xfffff9d0
d00156ec:	fc08f7fd 	stc2	7, cr15, [r8], {253}	; 0xfd
d00156f0:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d00156f4:	4a518097 	bmi	0xd1475958
d00156f8:	46302129 	ldrtmi	r2, [r0], -r9, lsr #2
d00156fc:	f7fd447a 			; <UNDEFINED> instruction: 0xf7fd447a
d0015700:	2800fbff 	stmdacs	r0, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d0015704:	808ef000 	addhi	pc, lr, r0
d0015708:	21284a4d 			; <UNDEFINED> instruction: 0x21284a4d
d001570c:	447a4630 	ldrbtmi	r4, [sl], #-1584	; 0xfffff9d0
d0015710:	fbf6f7fd 	blx	0xcfdd370e
d0015714:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d0015718:	6af38085 	bvs	0xcfcf5934
d001571c:	af082400 	svcge	0x00082400
d0015720:	7f84f5b3 	svcvc	0x0084f5b3
d0015724:	80bc9408 	adcshi	r9, ip, r8, lsl #8
d0015728:	d14c71bc 	strhle	r7, [ip, #-28]	; 0xffffffe4
d001572c:	2b296cf3 	blcs	0xd0a70b00
d0015730:	4630d14b 	ldrtmi	sp, [r0], -fp, asr #2
d0015734:	fbb6f7fd 	blx	0xcedd3732
d0015738:	21294d42 			; <UNDEFINED> instruction: 0x21294d42
d001573c:	447d4a42 	ldrbtmi	r4, [sp], #-2626	; 0xfffff5be
d0015740:	4628447a 			; <UNDEFINED> instruction: 0x4628447a
d0015744:	fbdcf7fd 	blx	0xcf753742
d0015748:	d06b2800 	rsble	r2, fp, r0, lsl #16
d001574c:	9304230c 	movwls	r2, #17164	; 0x430c
d0015750:	e913ab12 	ldmdb	r3, {r1, r4, r8, r9, fp, sp, pc}
d0015754:	e88d000f 	stm	sp, {r0, r1, r2, r3}
d0015758:	e899000f 	ldm	r9, {r0, r1, r2, r3}
d001575c:	f7fe000f 			; <UNDEFINED> instruction: 0xf7fe000f
d0015760:	6dabfc4f 	stcvs	12, cr15, [fp, #316]!	; 0x13c
d0015764:	2b004606 	blcs	0xd0026f84
d0015768:	2330d15c 	teqcs	r0, #92, 2
d001576c:	4020f88d 	eormi	pc, r0, sp, lsl #17
d0015770:	46392207 	ldrtmi	r2, [r9], -r7, lsl #4
d0015774:	f400fb03 			; <UNDEFINED> instruction: 0xf400fb03
d0015778:	8021f88d 	eorhi	pc, r1, sp, lsl #17
d001577c:	f5001928 			; <UNDEFINED> instruction: 0xf5001928
d0015780:	f2002090 	vqadd.s8	d2, d16, d0
d0015784:	f00b605b 			; <UNDEFINED> instruction: 0xf00b605b
d0015788:	213dfbc7 	teqcs	sp, r7, asr #23	; <UNPREDICTABLE>
d001578c:	f7fd4628 			; <UNDEFINED> instruction: 0xf7fd4628
d0015790:	4601fba9 	strmi	pc, [r1], -r9, lsr #23
d0015794:	d0412800 	suble	r2, r1, r0, lsl #16
d0015798:	2090f504 	addscs	pc, r0, r4, lsl #10
d001579c:	605bf200 	subsvs	pc, fp, r0, lsl #4
d00157a0:	f7ff4428 			; <UNDEFINED> instruction: 0xf7ff4428
d00157a4:	4829fe05 	stmdami	r9!, {r0, r2, r9, sl, fp, ip, sp, lr, pc}
d00157a8:	22004631 	andcs	r4, r0, #51380224	; 0x3100000
d00157ac:	90074478 	andls	r4, r7, r8, ror r4
d00157b0:	f9b7f7ff 			; <UNDEFINED> instruction: 0xf9b7f7ff
d00157b4:	213b4a26 	teqcs	fp, r6, lsr #20
d00157b8:	447a9807 	ldrbtmi	r9, [sl], #-2055	; 0xfffff7f9
d00157bc:	e8bdb012 	pop	{r1, r4, ip, sp, pc}
d00157c0:	f7fd47f0 			; <UNDEFINED> instruction: 0xf7fd47f0
d00157c4:	2b29bb9d 	blcs	0xd0a84640
d00157c8:	f8dfd0b6 			; <UNDEFINED> instruction: 0xf8dfd0b6
d00157cc:	f10da088 			; <UNDEFINED> instruction: 0xf10da088
d00157d0:	4d210622 	stcmi	6, cr0, [r1, #-136]!	; 0xffffff78
d00157d4:	44fa2400 	ldrbtmi	r2, [sl], #1024	; 0x400
d00157d8:	4652447d 			; <UNDEFINED> instruction: 0x4652447d
d00157dc:	1107f240 	tstne	r7, r0, asr #4	; <UNPREDICTABLE>
d00157e0:	f7fd4628 			; <UNDEFINED> instruction: 0xf7fd4628
d00157e4:	b1e8fb8d 	mvnlt	pc, sp, lsl #23
d00157e8:	f2402300 	vcgt.s8	d18, d0, d0
d00157ec:	34011101 	strcc	r1, [r1], #-257	; 0xfffffeff
d00157f0:	f8064628 			; <UNDEFINED> instruction: 0xf8064628
d00157f4:	f7fd3b01 			; <UNDEFINED> instruction: 0xf7fd3b01
d00157f8:	212cfb75 	msrcs	LR_mon, r5
d00157fc:	b2e44628 	rsclt	r4, r4, #40, 12	; 0x2800000
d0015800:	fb70f7fd 	blx	0xd1c537fe
d0015804:	d0972800 	addsle	r2, r7, r0, lsl #16
d0015808:	d1e62c05 	mvnle	r2, r5, lsl #24
d001580c:	46284913 			; <UNDEFINED> instruction: 0x46284913
d0015810:	b0124479 	andslt	r4, r2, r9, ror r4
d0015814:	47f0e8bd 			; <UNDEFINED> instruction: 0x47f0e8bd
d0015818:	bd18f7fa 	ldclt	7, cr15, [r8, #-1000]	; 0xfffffc18
d001581c:	f7ff4628 			; <UNDEFINED> instruction: 0xf7ff4628
d0015820:	e7c0fd44 	strb	pc, [r0, r4, asr #26]	; <UNPREDICTABLE>
d0015824:	e8bdb012 	pop	{r1, r4, ip, sp, pc}
d0015828:	bf0087f0 	svclt	0x000087f0
d001582c:	000123ec 	andeq	r2, r1, ip, ror #7
d0015830:	fffffe48 			; <UNDEFINED> instruction: 0xfffffe48
d0015834:	fffffe61 			; <UNDEFINED> instruction: 0xfffffe61
d0015838:	fffffe64 			; <UNDEFINED> instruction: 0xfffffe64
d001583c:	fffffe7a 			; <UNDEFINED> instruction: 0xfffffe7a
d0015840:	fffffe95 			; <UNDEFINED> instruction: 0xfffffe95
d0015844:	00012356 	andeq	r2, r1, r6, asr r3
d0015848:	fffffef6 			; <UNDEFINED> instruction: 0xfffffef6
d001584c:	000122e8 	andeq	r2, r1, r8, ror #5
d0015850:	fffffeab 			; <UNDEFINED> instruction: 0xfffffeab
d0015854:	fffffe31 			; <UNDEFINED> instruction: 0xfffffe31
d0015858:	000122bc 			; <UNDEFINED> instruction: 0x000122bc
d001585c:	fffffdc8 			; <UNDEFINED> instruction: 0xfffffdc8

Disassembly of section .text.local_address:

d0015860 <.text.local_address>:
d0015860:	4604b510 			; <UNDEFINED> instruction: 0x4604b510
d0015864:	2100008a 	smlabbcs	r0, sl, r0, r0
d0015868:	fcddf7ff 	ldc2l	7, cr15, [sp], {255}	; 0xff
d001586c:	f6414620 			; <UNDEFINED> instruction: 0xf6414620
d0015870:	e8bd0138 	pop	{r3, r4, r5, r8}
d0015874:	f7ff4010 			; <UNDEFINED> instruction: 0xf7ff4010
d0015878:	Address 0x00000000d0015878 is out of bounds.


Disassembly of section .text.int_double_pointer_value:

d00158ec <.text.int_double_pointer_value>:
d00158ec:	4ff8e92d 	svcmi	0x00f8e92d
d00158f0:	f7ff4604 			; <UNDEFINED> instruction: 0xf7ff4604
d00158f4:	bb28fce1 	bllt	0xd0a54c80
d00158f8:	46202126 	strtmi	r2, [r0], -r6, lsr #2
d00158fc:	faf2f7fd 	blx	0xcfcd38f8
d0015900:	46054a20 	strmi	r4, [r5], -r0, lsr #20
d0015904:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d0015908:	4620447a 			; <UNDEFINED> instruction: 0x4620447a
d001590c:	9024f8d4 	ldrdls	pc, [r4], -r4	; <UNPREDICTABLE>
d0015910:	8028f8d4 	ldrdhi	pc, [r8], -r4	; <UNPREDICTABLE>
d0015914:	7030f894 	mlasvc	r0, r4, r8, pc	; <UNPREDICTABLE>
d0015918:	e9d46b66 	ldmib	r4, {r1, r2, r5, r6, r8, r9, fp, sp, lr}^
d001591c:	f7fdab06 			; <UNDEFINED> instruction: 0xf7fdab06
d0015920:	b178faef 	cmnlt	r8, pc, ror #21	; <UNPREDICTABLE>
d0015924:	465a4651 			; <UNDEFINED> instruction: 0x465a4651
d0015928:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d001592c:	1e01ff3f 	mcrne	15, 0, pc, cr1, cr15, {1}	; <UNPREDICTABLE>
d0015930:	6da3da0a 			; <UNDEFINED> instruction: 0x6da3da0a
d0015934:	4b14b933 	blmi	0xd0543e08
d0015938:	66a6447b 	sxtabvs	r4, r6, fp, ror #8
d001593c:	3916e9c4 	ldmdbcc	r6, {r2, r6, r7, r8, fp, sp, lr, pc}
d0015940:	8718e9c4 	ldrhi	lr, [r8, -r4, asr #19]
d0015944:	8ff8e8bd 	svchi	0x00f8e8bd
d0015948:	fb032330 	blx	0xd00de612
d001594c:	f5034301 			; <UNDEFINED> instruction: 0xf5034301
d0015950:	f8932390 			; <UNDEFINED> instruction: 0xf8932390
d0015954:	b1353659 	teqlt	r5, r9, asr r6
d0015958:	d10c2b0a 	tstle	ip, sl, lsl #22
d001595c:	e8bd4620 	pop	{r5, r9, sl, lr}
d0015960:	f7ff4ff8 			; <UNDEFINED> instruction: 0xf7ff4ff8
d0015964:	2b13bf7d 	blcs	0xd0505760
d0015968:	462ad105 	strtmi	sp, [sl], -r5, lsl #2
d001596c:	e8bd4620 	pop	{r5, r9, sl, lr}
d0015970:	f7ff4ff8 			; <UNDEFINED> instruction: 0xf7ff4ff8
d0015974:	6da3b8bb 	stcvs	8, cr11, [r3, #748]!	; 0x2ec
d0015978:	d1e32b00 	mvnle	r2, r0, lsl #22
d001597c:	447b4b03 	ldrbtmi	r4, [fp], #-2819	; 0xfffff4fd
d0015980:	bf00e7db 	svclt	0x0000e7db
d0015984:	ffffff6e 			; <UNDEFINED> instruction: 0xffffff6e
d0015988:	ffffff5e 			; <UNDEFINED> instruction: 0xffffff5e
d001598c:	ffffff36 			; <UNDEFINED> instruction: 0xffffff36

Disassembly of section .text.record_member_pointer:

d0015a20 <.text.record_member_pointer>:
d0015a20:	447b4b44 	ldrbtmi	r4, [fp], #-2884	; 0xfffff4bc
d0015a24:	4ff0e92d 	svcmi	0x00f0e92d
d0015a28:	460e4604 	strmi	r4, [lr], -r4, lsl #12
d0015a2c:	8b04ed2d 	blhi	0xd0150ee8
d0015a30:	3a10ee09 	bcc	0xd045125c
d0015a34:	9203b085 	andls	fp, r3, #133	; 0x85
d0015a38:	ee1969a3 	vnmls.f16	s12, s19, s7
d0015a3c:	f2402a10 	vpmin.s8	d18, d0, d0
d0015a40:	46201101 	strtmi	r1, [r0], -r1, lsl #2
d0015a44:	3a10ee08 	bcc	0xd045126c
d0015a48:	f8d469e3 			; <UNDEFINED> instruction: 0xf8d469e3
d0015a4c:	ee08b024 	cdp	0, 0, cr11, cr8, cr4, {1}
d0015a50:	6aa33a90 	bvs	0xce8e4498
d0015a54:	9030f894 	mlasls	r0, r4, r8, pc	; <UNPREDICTABLE>
d0015a58:	6b639301 	blvs	0xd18fa664
d0015a5c:	f7fd9302 			; <UNDEFINED> instruction: 0xf7fd9302
d0015a60:	b330fa4f 	teqlt	r0, #323584	; 0x4f000	; <UNPREDICTABLE>
d0015a64:	731af44f 	tstvc	sl, #1325400064	; 0x4f000000	; <UNPREDICTABLE>
d0015a68:	fb032500 	blx	0xd00dee72
d0015a6c:	f507f706 			; <UNDEFINED> instruction: 0xf507f706
d0015a70:	44273867 	strtmi	r3, [r7], #-2151	; 0xfffff799
d0015a74:	78f4f508 	ldmvc	r4!, {r3, r8, sl, ip, sp, lr, pc}^
d0015a78:	3768f507 	strbcc	pc, [r8, -r7, lsl #10]!	; <UNPREDICTABLE>
d0015a7c:	0a08eb04 	beq	0xd0250694
d0015a80:	302af897 	mlacc	sl, r7, r8, pc	; <UNPREDICTABLE>
d0015a84:	d81942ab 	ldmdale	r9, {r0, r1, r3, r5, r7, r9, lr}
d0015a88:	731af44f 	tstvc	sl, #1325400064	; 0x4f000000	; <UNPREDICTABLE>
d0015a8c:	4606fb03 	strmi	pc, [r6], -r3, lsl #22
d0015a90:	3668f506 	strbtcc	pc, [r8], -r6, lsl #10	; <UNPREDICTABLE>
d0015a94:	302af896 	mlacc	sl, r6, r8, pc	; <UNPREDICTABLE>
d0015a98:	d11d42ab 	tstle	sp, fp, lsr #5
d0015a9c:	b9436da3 	stmdblt	r3, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0015aa0:	447b4b25 	ldrbtmi	r4, [fp], #-2853	; 0xfffff4db
d0015aa4:	3b16e9c4 	blcc	0xd05d01bc
d0015aa8:	e9c49b01 	stmib	r4, {r0, r8, r9, fp, ip, pc}^
d0015aac:	9b023918 	blls	0xd00a3f14
d0015ab0:	b00566a3 	andlt	r6, r5, r3, lsr #13
d0015ab4:	8b04ecbd 	blhi	0xd0150db0
d0015ab8:	8ff0e8bd 	svchi	0x00f0e8bd
d0015abc:	3004f8da 	ldrdcc	pc, [r4], -sl
d0015ac0:	1a90ee18 	bne	0xce451328
d0015ac4:	2b24f85a 	blcs	0xd0953c34
d0015ac8:	0a10ee18 	beq	0xd0451330
d0015acc:	fdf8f7fa 	ldc2l	7, cr15, [r8, #1000]!	; 0x3e8
d0015ad0:	d1d92800 	bicsle	r2, r9, r0, lsl #16
d0015ad4:	e7d33501 	ldrb	r3, [r3, r1, lsl #10]
d0015ad8:	fb032324 	blx	0xd00de772
d0015adc:	44258505 	strtmi	r8, [r5], #-1285	; 0xfffffafb
d0015ae0:	f8958c6a 			; <UNDEFINED> instruction: 0xf8958c6a
d0015ae4:	f8957020 			; <UNDEFINED> instruction: 0xf8957020
d0015ae8:	b14a6021 	cmplt	sl, r1, lsr #32
d0015aec:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d0015af0:	f7ff0092 			; <UNDEFINED> instruction: 0xf7ff0092
d0015af4:	f44ffb98 			; <UNDEFINED> instruction: 0xf44ffb98
d0015af8:	462051c2 	strtmi	r5, [r0], -r2, asr #3
d0015afc:	ffd8f7fe 			; <UNDEFINED> instruction: 0xffd8f7fe
d0015b00:	d0002fff 	strdle	r2, [r0], -pc	; <UNPREDICTABLE>
d0015b04:	6da3b12e 	stfvsd	f3, [r3, #184]!	; 0xb8
d0015b08:	d1d22b00 	bicsle	r2, r2, r0, lsl #22
d0015b0c:	447b4b0b 	ldrbtmi	r4, [fp], #-2827	; 0xfffff4f5
d0015b10:	212ee7c8 	smlawtcs	lr, r8, r7, lr
d0015b14:	463e4620 	ldrtmi	r4, [lr], -r0, lsr #12
d0015b18:	f9e4f7fd 			; <UNDEFINED> instruction: 0xf9e4f7fd
d0015b1c:	d18b2800 	orrle	r2, fp, r0, lsl #16
d0015b20:	42bb9b03 	adcsmi	r9, fp, #3072	; 0xc00
d0015b24:	6da3d0c5 	stcvs	0, cr13, [r3, #788]!	; 0x314
d0015b28:	d1c22b00 	bicle	r2, r2, r0, lsl #22
d0015b2c:	447b4b04 	ldrbtmi	r4, [fp], #-2820	; 0xfffff4fc
d0015b30:	bf00e7b8 	svclt	0x0000e7b8
d0015b34:	ffffff6a 			; <UNDEFINED> instruction: 0xffffff6a
d0015b38:	ffffff08 			; <UNDEFINED> instruction: 0xffffff08
d0015b3c:	fffffeb7 			; <UNDEFINED> instruction: 0xfffffeb7
d0015b40:	fffffebf 			; <UNDEFINED> instruction: 0xfffffebf

Disassembly of section .text.record_pointer_field_address:

d0015bf8 <.text.record_pointer_field_address>:
d0015bf8:	447b4b4f 	ldrbtmi	r4, [fp], #-2895	; 0xfffff4b1
d0015bfc:	4ff0e92d 	svcmi	0x00f0e92d
d0015c00:	460d4604 	strmi	r4, [sp], -r4, lsl #12
d0015c04:	8b04ed2d 	blhi	0xd01510c0
d0015c08:	3a10ee09 	bcc	0xd0451434
d0015c0c:	9203b085 	andls	fp, r3, #133	; 0x85
d0015c10:	ee1969a3 	vnmls.f16	s12, s19, s7
d0015c14:	f2402a10 	vpmin.s8	d18, d0, d0
d0015c18:	46201101 	strtmi	r1, [r0], -r1, lsl #2
d0015c1c:	3a10ee08 	bcc	0xd0451444
d0015c20:	f8d469e3 			; <UNDEFINED> instruction: 0xf8d469e3
d0015c24:	ee08a024 	cdp	0, 0, cr10, cr8, cr4, {1}
d0015c28:	6b633a90 	blvs	0xd18e4670
d0015c2c:	9028f8d4 	ldrdls	pc, [r8], -r4	; <UNPREDICTABLE>
d0015c30:	8030f894 	mlashi	r0, r4, r8, pc	; <UNPREDICTABLE>
d0015c34:	f7fd9301 			; <UNDEFINED> instruction: 0xf7fd9301
d0015c38:	b330f963 	teqlt	r0, #1622016	; 0x18c000	; <UNPREDICTABLE>
d0015c3c:	731af44f 	tstvc	sl, #1325400064	; 0x4f000000	; <UNPREDICTABLE>
d0015c40:	fb032600 	blx	0xd00df44a
d0015c44:	f507f705 			; <UNDEFINED> instruction: 0xf507f705
d0015c48:	44273b67 	strtmi	r3, [r7], #-2919	; 0xfffff499
d0015c4c:	7bf4f50b 	blvc	0xcfd53080
d0015c50:	3768f507 	strbcc	pc, [r8, -r7, lsl #10]!	; <UNPREDICTABLE>
d0015c54:	030beb04 	movweq	lr, #47876	; 0xbb04
d0015c58:	f8979302 			; <UNDEFINED> instruction: 0xf8979302
d0015c5c:	42b3302a 	adcsmi	r3, r3, #42	; 0x2a
d0015c60:	f44fd818 	vst2.8	{d29-d30}, [pc :64], r8
d0015c64:	fb03731a 	blx	0xd00f28d6
d0015c68:	f5054505 			; <UNDEFINED> instruction: 0xf5054505
d0015c6c:	f8953568 			; <UNDEFINED> instruction: 0xf8953568
d0015c70:	42b3302a 	adcsmi	r3, r3, #42	; 0x2a
d0015c74:	6da3d11e 	stfvsd	f5, [r3, #120]!	; 0x78
d0015c78:	4b30b93b 	blmi	0xd0c4416c
d0015c7c:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0015c80:	9b013a16 	blls	0xd00644e0
d0015c84:	9818e9c4 	ldmdals	r8, {r2, r6, r7, r8, fp, sp, lr, pc}
d0015c88:	b00566a3 	andlt	r6, r5, r3, lsr #13
d0015c8c:	8b04ecbd 	blhi	0xd0150f88
d0015c90:	8ff0e8bd 	svchi	0x00f0e8bd
d0015c94:	ee189902 	vnmls.f16	s18, s16, s4
d0015c98:	9b020a10 	blls	0xd00984e0
d0015c9c:	2b24f851 	blcs	0xd0953de8
d0015ca0:	9102685b 	tstls	r2, fp, asr r8
d0015ca4:	1a90ee18 	bne	0xce45150c
d0015ca8:	fd0af7fa 	stc2	7, cr15, [sl, #-1000]	; 0xfffffc18
d0015cac:	d1d82800 	bicsle	r2, r8, r0, lsl #16
d0015cb0:	e7d23601 	ldrb	r3, [r2, r1, lsl #12]
d0015cb4:	fb032324 	blx	0xd00de94e
d0015cb8:	4426b606 	strtmi	fp, [r6], #-1542	; 0xfffff9fa
d0015cbc:	f8968c72 			; <UNDEFINED> instruction: 0xf8968c72
d0015cc0:	f8965020 			; <UNDEFINED> instruction: 0xf8965020
d0015cc4:	b14a7021 	cmplt	sl, r1, lsr #32
d0015cc8:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d0015ccc:	f7ff0092 			; <UNDEFINED> instruction: 0xf7ff0092
d0015cd0:	f44ffaaa 	vst1.32	{d31-d32}, [pc :128], sl
d0015cd4:	462051c2 	strtmi	r5, [r0], -r2, asr #3
d0015cd8:	feeaf7fe 	mcr2	7, 7, pc, cr10, cr14, {7}	; <UNPREDICTABLE>
d0015cdc:	7191f44f 	orrsvc	pc, r1, pc, asr #8
d0015ce0:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0015ce4:	b170f8ff 	ldrshlt	pc, [r0, #-143]!	; 0xffffff71	; <UNPREDICTABLE>
d0015ce8:	2dffb10f 	ldfcsp	f3, [pc, #60]!	; 0xd0015d2c
d0015cec:	6da3d105 	stfvsd	f5, [r3, #20]!
d0015cf0:	d1ca2b00 	bicle	r2, sl, r0, lsl #22
d0015cf4:	447b4b12 	ldrbtmi	r4, [fp], #-2834	; 0xfffff4ee
d0015cf8:	f44fe7c1 	vst1.64	{d30}, [pc], r1
d0015cfc:	462041d0 			; <UNDEFINED> instruction: 0x462041d0
d0015d00:	fed6f7fe 	mrc2	7, 6, pc, cr6, cr14, {7}
d0015d04:	212ee784 	smlawbcs	lr, r4, r7, lr
d0015d08:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0015d0c:	b148f8eb 	smlalttlt	pc, r8, fp, r8	; <UNPREDICTABLE>
d0015d10:	2dffb917 			; <UNDEFINED> instruction: 0x2dffb917
d0015d14:	af7cf47f 	svcge	0x007cf47f
d0015d18:	2b006da3 	blcs	0xd00313ac
d0015d1c:	4b09d1b5 	blmi	0xd028a3f8
d0015d20:	e7ac447b 			; <UNDEFINED> instruction: 0xe7ac447b
d0015d24:	9b03b117 	blls	0xd0102188
d0015d28:	d0ae429d 	umlalle	r4, lr, sp, r2
d0015d2c:	2b006da3 	blcs	0xd00313c0
d0015d30:	4b05d1ab 	blmi	0xd018a3e4
d0015d34:	e7a2447b 			; <UNDEFINED> instruction: 0xe7a2447b
d0015d38:	ffffff46 			; <UNDEFINED> instruction: 0xffffff46
d0015d3c:	fffffee1 			; <UNDEFINED> instruction: 0xfffffee1
d0015d40:	fffffe8f 			; <UNDEFINED> instruction: 0xfffffe8f
d0015d44:	fffffe85 			; <UNDEFINED> instruction: 0xfffffe85
d0015d48:	fffffe92 			; <UNDEFINED> instruction: 0xfffffe92

Disassembly of section .text.struct_double_pointer_value:

d0015e2c <.text.struct_double_pointer_value>:
d0015e2c:	4ff7e92d 	svcmi	0x00f7e92d
d0015e30:	460d4604 	strmi	r4, [sp], -r4, lsl #12
d0015e34:	fa40f7ff 	blx	0xd1053e38
d0015e38:	bb404680 	bllt	0xd1027840
d0015e3c:	46202126 	strtmi	r2, [r0], -r6, lsr #2
d0015e40:	f850f7fd 			; <UNDEFINED> instruction: 0xf850f7fd
d0015e44:	4a3c6a63 	bmi	0xd0f307d8
d0015e48:	93004683 	movwls	r4, #1667	; 0x683
d0015e4c:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d0015e50:	447a6aa3 	ldrbtmi	r6, [sl], #-2723	; 0xfffff55d
d0015e54:	f8944620 			; <UNDEFINED> instruction: 0xf8944620
d0015e58:	6b669030 	blvs	0xd19b9f20
d0015e5c:	e9d49301 	ldmib	r4, {r0, r8, r9, ip, pc}^
d0015e60:	f7fd7a06 			; <UNDEFINED> instruction: 0xf7fd7a06
d0015e64:	b190f84d 	orrslt	pc, r0, sp, asr #16
d0015e68:	46394652 			; <UNDEFINED> instruction: 0x46394652
d0015e6c:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0015e70:	f1b0fc9d 			; <UNDEFINED> instruction: 0xf1b0fc9d
d0015e74:	da0d0a00 	ble	0xd035867c
d0015e78:	b9436da3 	stmdblt	r3, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0015e7c:	447b4b2f 	ldrbtmi	r4, [fp], #-2863	; 0xfffff4d1
d0015e80:	9b0065a3 	blls	0xd002f514
d0015e84:	65e366a6 	strbvs	r6, [r3, #1702]!	; 0x6a6
d0015e88:	e9c49b01 	stmib	r4, {r0, r8, r9, fp, ip, pc}^
d0015e8c:	b0033918 	andlt	r3, r3, r8, lsl r9
d0015e90:	8ff0e8bd 	svchi	0x00f0e8bd
d0015e94:	fb022230 	blx	0xd009e75e
d0015e98:	f502420a 			; <UNDEFINED> instruction: 0xf502420a
d0015e9c:	f8922290 			; <UNDEFINED> instruction: 0xf8922290
d0015ea0:	f892765a 			; <UNDEFINED> instruction: 0xf892765a
d0015ea4:	f1bb2659 			; <UNDEFINED> instruction: 0xf1bb2659
d0015ea8:	d0320f00 	eorsle	r0, r2, r0, lsl #30
d0015eac:	d1212a0e 			; <UNDEFINED> instruction: 0xd1212a0e
d0015eb0:	7191f44f 	orrsvc	pc, r1, pc, asr #8
d0015eb4:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0015eb8:	b160f815 	msrlt	SPSR_, r5, lsl r8
d0015ebc:	46514642 	ldrbmi	r4, [r1], -r2, asr #12
d0015ec0:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0015ec4:	462afe13 			; <UNDEFINED> instruction: 0x462afe13
d0015ec8:	46204639 			; <UNDEFINED> instruction: 0x46204639
d0015ecc:	e8bdb003 	pop	{r0, r1, ip, sp, pc}
d0015ed0:	f7ff4ff0 			; <UNDEFINED> instruction: 0xf7ff4ff0
d0015ed4:	42afbe91 	adcmi	fp, pc, #2320	; 0x910
d0015ed8:	4651d106 	ldrbmi	sp, [r1], -r6, lsl #2
d0015edc:	b0034620 	andlt	r4, r3, r0, lsr #12
d0015ee0:	4ff0e8bd 	svcmi	0x00f0e8bd
d0015ee4:	bcbcf7ff 	ldclt	7, cr15, [ip], #1020	; 0x3fc
d0015ee8:	2b006da3 	blcs	0xd003157c
d0015eec:	4b14d1cf 	blmi	0xd054a630
d0015ef0:	e7c5447b 			; <UNDEFINED> instruction: 0xe7c5447b
d0015ef4:	d1182a0d 	tstle	r8, sp, lsl #20
d0015ef8:	212e4a12 			; <UNDEFINED> instruction: 0x212e4a12
d0015efc:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d0015f00:	fffef7fc 			; <UNDEFINED> instruction: 0xfffef7fc
d0015f04:	d0c22800 	sbcle	r2, r2, r0, lsl #16
d0015f08:	46204651 			; <UNDEFINED> instruction: 0x46204651
d0015f0c:	fca8f7ff 	stc2	7, cr15, [r8], #1020	; 0x3fc
d0015f10:	2a12e7d9 	bcs	0xd04cfe7c
d0015f14:	42afd109 	adcmi	sp, pc, #1073741826	; 0x40000002
d0015f18:	465ad107 	ldrbmi	sp, [sl], -r7, lsl #2
d0015f1c:	46204651 			; <UNDEFINED> instruction: 0x46204651
d0015f20:	e8bdb003 	pop	{r0, r1, ip, sp, pc}
d0015f24:	f7fe4ff0 			; <UNDEFINED> instruction: 0xf7fe4ff0
d0015f28:	6da3bde1 	stcvs	13, cr11, [r3, #900]!	; 0x384
d0015f2c:	d1ae2b00 			; <UNDEFINED> instruction: 0xd1ae2b00
d0015f30:	447b4b05 	ldrbtmi	r4, [fp], #-2821	; 0xfffff4fb
d0015f34:	bf00e7a4 	svclt	0x0000e7a4
d0015f38:	fffffef6 			; <UNDEFINED> instruction: 0xfffffef6
d0015f3c:	fffffef9 			; <UNDEFINED> instruction: 0xfffffef9
d0015f40:	fffffeb7 			; <UNDEFINED> instruction: 0xfffffeb7
d0015f44:	fffffed1 			; <UNDEFINED> instruction: 0xfffffed1
d0015f48:	fffffeb8 			; <UNDEFINED> instruction: 0xfffffeb8

Disassembly of section .text.patch_branch.isra.0.part.0:

d0015f4c <.text.patch_branch.isra.0.part.0>:
d0015f4c:	e92d1a09 	push	{r0, r3, r9, fp, ip}
d0015f50:	1f0d41f0 	svcne	0x000d41f0
d0015f54:	46064690 			; <UNDEFINED> instruction: 0x46064690
d0015f58:	6300f3c5 	movwvs	pc, #965	; 0x3c5	; <UNPREDICTABLE>
d0015f5c:	3109f3c5 	smlabtcc	r9, r5, r3, pc	; <UNPREDICTABLE>
d0015f60:	54d5ea83 	ldrbpl	lr, [r5], #2691	; 0xa83
d0015f64:	2183ea41 	orrcs	lr, r3, r1, asr #20
d0015f68:	f44143e4 	vst2.<illegal width 64>	{d20-d23}, [r1 :128], r4
d0015f6c:	f0044170 			; <UNDEFINED> instruction: 0xf0044170
d0015f70:	ea830701 	b	0xce0d7b7c
d0015f74:	f7fe5495 			; <UNDEFINED> instruction: 0xf7fe5495
d0015f78:	f3c5fd7f 	vmvn.i32	<illegal reg q15.5>, #14680063	; 0x00dfffff
d0015f7c:	43e4054a 	mvnmi	r0, #310378496	; 0x12800000
d0015f80:	0f00f1b8 	svceq	0x0000f1b8
d0015f84:	0002f106 	andeq	pc, r2, r6, lsl #2
d0015f88:	0401f004 	streq	pc, [r1], #-4
d0015f8c:	f44fbf14 			; <UNDEFINED> instruction: 0xf44fbf14
d0015f90:	f44f4150 	vst4.16	{d20,d22,d24,d26}, [pc :64], r0
d0015f94:	02e44110 	rsceq	r4, r4, #16, 2
d0015f98:	3447ea44 	strbcc	lr, [r7], #-2628	; 0xfffff5bc
d0015f9c:	4321432c 			; <UNDEFINED> instruction: 0x4321432c
d0015fa0:	41f0e8bd 	ldrhmi	lr, [r0, #141]!	; 0x8d
d0015fa4:	bd68f7fe 	stcllt	7, cr15, [r8, #-1016]!	; 0xfffffc08

Disassembly of section .text.patch_branch.isra.0:

d0015fa8 <.text.patch_branch.isra.0>:
d0015fa8:	4604b410 			; <UNDEFINED> instruction: 0x4604b410
d0015fac:	46114608 	ldrmi	r4, [r1], -r8, lsl #12
d0015fb0:	b91c461a 	ldmdblt	ip, {r1, r3, r4, r9, sl, lr}
d0015fb4:	4b04f85d 	blmi	0xd0154130
d0015fb8:	bfc8f7ff 	svclt	0x00c8f7ff
d0015fbc:	4b04f85d 	blmi	0xd0154138
d0015fc0:	Address 0x00000000d0015fc0 is out of bounds.


Disassembly of section .text.expression:

d00161d4 <.text.expression>:
d00161d4:	4ff0e92d 	svcmi	0x00f0e92d
d00161d8:	46046a03 	strmi	r6, [r4], -r3, lsl #20
d00161dc:	9024f8d0 	ldrdls	pc, [r4], -r0	; <UNPREDICTABLE>
d00161e0:	a030f890 	mlasge	r0, r0, r8, pc	; <UNPREDICTABLE>
d00161e4:	8b06ed2d 	blhi	0xd01d16a0
d00161e8:	9305b08d 	movwls	fp, #20621	; 0x508d
d00161ec:	f5009203 			; <UNDEFINED> instruction: 0xf5009203
d00161f0:	91042292 			; <UNDEFINED> instruction: 0x91042292
d00161f4:	b30ae9d0 	movwlt	lr, #43472	; 0xa9d0
d00161f8:	6b439306 	blvs	0xd10fae18
d00161fc:	f8d29301 			; <UNDEFINED> instruction: 0xf8d29301
d0016200:	33013244 	movwcc	r3, #4676	; 0x1244
d0016204:	f8c22b20 			; <UNDEFINED> instruction: 0xf8c22b20
d0016208:	d9043244 	stmdble	r4, {r2, r6, r9, ip, sp}
d001620c:	15e8f8df 	strbne	pc, [r8, #2271]!	; 0x8df	; <UNPREDICTABLE>
d0016210:	f7fa4479 			; <UNDEFINED> instruction: 0xf7fa4479
d0016214:	9b03f81b 	blls	0xd0114288
d0016218:	42411ed8 	submi	r1, r1, #216, 28	; 0xd80
d001621c:	46204141 	strtmi	r4, [r0], -r1, asr #2
d0016220:	fc08f002 	stc2	0, cr15, [r8], {2}
d0016224:	35d4f8df 	ldrbcc	pc, [r4, #2271]	; 0x8df	; <UNPREDICTABLE>
d0016228:	447b4605 	ldrbtmi	r4, [fp], #-1541	; 0xfffff9fb
d001622c:	f8df9308 			; <UNDEFINED> instruction: 0xf8df9308
d0016230:	447b35d0 	ldrbtmi	r3, [fp], #-1488	; 0xfffffa30
d0016234:	6da69309 	stcvs	3, cr9, [r6, #36]!	; 0x24
d0016238:	6ae7b9b6 	bvs	0xcfa04918
d001623c:	f0002f7c 			; <UNDEFINED> instruction: 0xf0002f7c
d0016240:	f3008167 	vrhadd.u8	q4, q0, <illegal reg q11.5>
d0016244:	2f2f8136 	svccs	0x002f8136
d0016248:	8128f300 	msrhi	(UNDEF: 56), r0
d001624c:	f3002f24 	vpmax.f32	d2, d0, d20
d0016250:	9b048115 	blls	0xd01366ac
d0016254:	dc0742b3 	sfmle	f4, 4, [r7], {179}	; 0xb3
d0016258:	d1362d02 	teqle	r6, r2, lsl #26
d001625c:	15a4f8df 	strne	pc, [r4, #2271]!	; 0x8df
d0016260:	44794620 	ldrbtmi	r4, [r9], #-1568	; 0xfffff9e0
d0016264:	fff2f7f9 			; <UNDEFINED> instruction: 0xfff2f7f9
d0016268:	b9be6da6 	ldmiblt	lr!, {r1, r2, r5, r7, r8, sl, fp, sp, lr}
d001626c:	2b019b04 	blcs	0xd007ce84
d0016270:	213fd114 	teqcs	pc, r4, lsl r1	; <UNPREDICTABLE>
d0016274:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0016278:	b178fe35 	cmnlt	r8, r5, lsr lr	; <UNPREDICTABLE>
d001627c:	0304f025 	movweq	pc, #16421	; 0x4025	; <UNPREDICTABLE>
d0016280:	f0402b02 			; <UNDEFINED> instruction: 0xf0402b02
d0016284:	6da3814d 	stfvsd	f0, [r3, #308]!	; 0x134
d0016288:	f8dfb943 			; <UNDEFINED> instruction: 0xf8dfb943
d001628c:	447b357c 	ldrbtmi	r3, [fp], #-1404	; 0xfffffa84
d0016290:	3916e9c4 	ldmdbcc	r6, {r2, r6, r7, r8, fp, sp, lr, pc}
d0016294:	e9c49b01 	stmib	r4, {r0, r8, r9, fp, ip, pc}^
d0016298:	66a3ba18 	ssatvs	fp, #4, r8, lsl #20
d001629c:	3b019b03 	blcc	0xd007ceb0
d00162a0:	f2002b01 	vqdmulh.s<illegal width 8>	d2, d0, d1
d00162a4:	2d028232 	sfmcs	f0, 1, [r2, #-200]	; 0xffffff38
d00162a8:	6da3d10a 	stfvsd	f5, [r3, #40]!	; 0x28
d00162ac:	f8dfb943 			; <UNDEFINED> instruction: 0xf8dfb943
d00162b0:	447b355c 	ldrbtmi	r3, [fp], #-1372	; 0xfffffaa4
d00162b4:	3916e9c4 	ldmdbcc	r6, {r2, r6, r7, r8, fp, sp, lr, pc}
d00162b8:	e9c49b01 	stmib	r4, {r0, r8, r9, fp, ip, pc}^
d00162bc:	66a3ba18 	ssatvs	fp, #4, r8, lsl #20
d00162c0:	2b019b03 	blcs	0xd007ced4
d00162c4:	8231f040 	eorshi	pc, r1, #64	; 0x40
d00162c8:	4620e222 	strtmi	lr, [r0], -r2, lsr #4
d00162cc:	f7fc3601 			; <UNDEFINED> instruction: 0xf7fc3601
d00162d0:	f5a7fde9 			; <UNDEFINED> instruction: 0xf5a7fde9
d00162d4:	2b017390 	blcs	0xd007311c
d00162d8:	f240d831 	vtst.8	d29, d0, d17
d00162dc:	46201521 	strtmi	r1, [r0], -r1, lsr #10
d00162e0:	42551b7a 	subsmi	r1, r5, #124928	; 0x1e800
d00162e4:	46294155 			; <UNDEFINED> instruction: 0x46294155
d00162e8:	fc97f7fe 	ldc2	7, cr15, [r7], {254}	; 0xfe
d00162ec:	46312202 	ldrtmi	r2, [r1], -r2, lsl #4
d00162f0:	46204607 	strtmi	r4, [r0], -r7, lsl #12
d00162f4:	368ff504 	strcc	pc, [pc], r4, lsl #10
d00162f8:	ff6cf7ff 			; <UNDEFINED> instruction: 0xff6cf7ff
d00162fc:	5120f44f 	msrpl	CPSR_, pc, asr #8
d0016300:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0016304:	2101fbd5 	ldrdcs	pc, [r1, -r5]
d0016308:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d001630c:	4620fc9c 			; <UNDEFINED> instruction: 0x4620fc9c
d0016310:	fc74f7fe 	ldc2l	7, cr15, [r4], #-1016	; 0xfffffc08
d0016314:	f8d62300 			; <UNDEFINED> instruction: 0xf8d62300
d0016318:	468021b8 			; <UNDEFINED> instruction: 0x468021b8
d001631c:	6da04639 	stcvs	6, cr4, [r0, #228]!	; 0xe4
d0016320:	fe42f7ff 	mcr2	7, 2, pc, cr2, cr15, {7}	; <UNPREDICTABLE>
d0016324:	46204629 	strtmi	r4, [r0], -r9, lsr #12
d0016328:	ffbff7fe 			; <UNDEFINED> instruction: 0xffbff7fe
d001632c:	f8d62300 			; <UNDEFINED> instruction: 0xf8d62300
d0016330:	464121b8 			; <UNDEFINED> instruction: 0x464121b8
d0016334:	f7ff6da0 			; <UNDEFINED> instruction: 0xf7ff6da0
d0016338:	2500fe37 	strcs	pc, [r0, #-3639]	; 0xfffff1c9
d001633c:	f5a7e77b 			; <UNDEFINED> instruction: 0xf5a7e77b
d0016340:	2d03738e 	stccs	3, cr7, [r3, #-568]	; 0xfffffdc8
d0016344:	d0029302 	andle	r9, r2, r2, lsl #6
d0016348:	2b021f6b 	blcs	0xd009e0fc
d001634c:	9b02d80f 	blls	0xd00cc390
d0016350:	d90c2b01 	stmdble	ip, {r0, r8, r9, fp, sp}
d0016354:	2b006da3 	blcs	0xd00319e8
d0016358:	f8dfd186 			; <UNDEFINED> instruction: 0xf8dfd186
d001635c:	447b34b4 	ldrbtmi	r3, [fp], #-1204	; 0xfffffb4c
d0016360:	3916e9c4 	ldmdbcc	r6, {r2, r6, r7, r8, fp, sp, lr, pc}
d0016364:	e9c49b01 	stmib	r4, {r0, r8, r9, fp, ip, pc}^
d0016368:	66a3ba18 	ssatvs	fp, #4, r8, lsl #20
d001636c:	f24be77c 	vaba.s8	q15, <illegal reg q5.5>, q14
d0016370:	46204103 	strtmi	r4, [r0], -r3, lsl #2
d0016374:	fb9cf7fe 	blx	0xce754376
d0016378:	46316a23 	ldrtmi	r6, [r1], -r3, lsr #20
d001637c:	46202202 	strtmi	r2, [r0], -r2, lsl #4
d0016380:	f8d49307 			; <UNDEFINED> instruction: 0xf8d49307
d0016384:	f7ff802c 			; <UNDEFINED> instruction: 0xf7ff802c
d0016388:	f64bff25 			; <UNDEFINED> instruction: 0xf64bff25
d001638c:	46064106 	strmi	r4, [r6], -r6, lsl #2
d0016390:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0016394:	2d04fb8d 	vstrcs	d15, [r4, #-564]	; 0xfffffdcc
d0016398:	81f8f000 	mvnshi	pc, r0
d001639c:	d1112e04 	tstle	r1, r4, lsl #28
d00163a0:	f0402f2b 			; <UNDEFINED> instruction: 0xf0402f2b
d00163a4:	1eeb8209 	cdpne	2, 14, cr8, cr11, cr9, {0}
d00163a8:	f2402b01 	vqdmulh.s<illegal width 8>	d18, d0, d1
d00163ac:	21898208 	orrcs	r8, r9, r8, lsl #4
d00163b0:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d00163b4:	f641fb7d 			; <UNDEFINED> instruction: 0xf641fb7d
d00163b8:	46200108 	strtmi	r0, [r0], -r8, lsl #2
d00163bc:	f7fe2504 			; <UNDEFINED> instruction: 0xf7fe2504
d00163c0:	e738fb77 			; <UNDEFINED> instruction: 0xe738fb77
d00163c4:	d0072d03 	andle	r2, r7, r3, lsl #26
d00163c8:	d0052e03 	andle	r2, r5, r3, lsl #28
d00163cc:	2b021f6b 	blcs	0xd009e180
d00163d0:	1f73d902 	svcne	0x0073d902
d00163d4:	d8392b02 	ldmdale	r9!, {r1, r8, r9, fp, sp}
d00163d8:	f5a89b06 			; <UNDEFINED> instruction: 0xf5a89b06
d00163dc:	f5a37881 			; <UNDEFINED> instruction: 0xf5a37881
d00163e0:	2b017381 	blcs	0xd00731ec
d00163e4:	9b05bf97 	blls	0xd0186248
d00163e8:	fab32300 	blx	0xcecdeff0
d00163ec:	095bf383 	ldmdbeq	fp, {r0, r1, r7, r8, r9, ip, sp, lr, pc}^
d00163f0:	0f01f1b8 	svceq	0x0001f1b8
d00163f4:	9a07bf97 	bls	0xd0206258
d00163f8:	fab22200 	blx	0xcec9ec00
d00163fc:	0952f282 	ldmdbeq	r2, {r1, r7, r9, ip, sp, lr, pc}^
d0016400:	d0092d04 	andle	r2, r9, r4, lsl #26
d0016404:	f0402d03 			; <UNDEFINED> instruction: 0xf0402d03
d0016408:	1ef381be 	mrcne	1, 7, r8, cr3, cr14, {5}
d001640c:	d80c2b01 	stmdale	ip, {r0, r8, r9, fp, sp}
d0016410:	2b019b02 	blcs	0xd007d020
d0016414:	e013d80b 	ands	sp, r3, fp, lsl #16
d0016418:	29011ef1 	stmdbcs	r1, {r0, r4, r5, r6, r7, r9, sl, fp, ip}
d001641c:	2e00d9f8 			; <UNDEFINED> instruction: 0x2e00d9f8
d0016420:	81a4f040 			; <UNDEFINED> instruction: 0x81a4f040
d0016424:	d1f32a00 	mvnsle	r2, r0, lsl #20
d0016428:	2e00e001 	cdpcs	0, 0, cr14, cr0, cr1, {0}
d001642c:	6da3d0fa 	stcvs	0, cr13, [r3, #1000]!	; 0x3e8
d0016430:	9b08b933 	blls	0xd0244904
d0016434:	3916e9c4 	ldmdbcc	r6, {r2, r6, r7, r8, fp, sp, lr, pc}
d0016438:	e9c49b01 	stmib	r4, {r0, r8, r9, fp, ip, pc}^
d001643c:	66a3ba18 	ssatvs	fp, #4, r8, lsl #20
d0016440:	46392201 	ldrtmi	r2, [r9], -r1, lsl #4
d0016444:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0016448:	e776fc76 			; <UNDEFINED> instruction: 0xe776fc76
d001644c:	7393f46f 	orrsvc	pc, r3, #1862270976	; 0x6f000000
d0016450:	2b0118fb 	blcs	0xd005c844
d0016454:	2d01d80c 	stccs	8, cr13, [r1, #-48]	; 0xffffffd0
d0016458:	2500bf14 	strcs	fp, [r0, #-3860]	; 0xfffff0ec
d001645c:	462a2501 	strtmi	r2, [sl], -r1, lsl #10
d0016460:	46204639 			; <UNDEFINED> instruction: 0x46204639
d0016464:	fc67f7fe 	stc2l	7, cr15, [r7], #-1016	; 0xfffffc08
d0016468:	bf181e05 	svclt	0x00181e05
d001646c:	e6e22501 	strbt	r2, [r2], r1, lsl #10
d0016470:	d0f42d01 	rscsle	r2, r4, r1, lsl #26
d0016474:	e7ef2e01 	strb	r2, [pc, r1, lsl #28]!
d0016478:	e6ea2602 	strbt	r2, [sl], r2, lsl #12
d001647c:	0325f1a7 	msreq	CPSR_sc, #-1073741783	; 0xc0000029
d0016480:	d8092b0a 	stmdale	r9, {r1, r3, r8, r9, fp, sp}
d0016484:	f003e8df 			; <UNDEFINED> instruction: 0xf003e8df
d0016488:	08084842 	stmdaeq	r8, {r1, r6, fp, lr}
d001648c:	08064208 	stmdaeq	r6, {r3, r9, lr}
d0016490:	00420806 	subeq	r0, r2, r6, lsl #16
d0016494:	e6dc2609 	ldrb	r2, [ip], r9, lsl #12
d0016498:	e6da2600 	ldrb	r2, [sl], r0, lsl #12
d001649c:	d03d2f5e 	eorsle	r2, sp, lr, asr pc
d00164a0:	aed7f73f 	mrcge	7, 6, APSR_nzcv, cr7, cr15, {1}
d00164a4:	0302f027 	movweq	pc, #8231	; 0x2027	; <UNPREDICTABLE>
d00164a8:	bf142b3c 	svclt	0x00142b3c
d00164ac:	26072600 	strcs	r2, [r7], -r0, lsl #12
d00164b0:	f5a7e6cf 			; <UNDEFINED> instruction: 0xf5a7e6cf
d00164b4:	2b0c738e 	blcs	0xd03332f4
d00164b8:	aecbf63f 	mcrge	6, 6, pc, cr11, cr15, {1}	; <UNPREDICTABLE>
d00164bc:	d8eb2b0c 	stmiale	fp!, {r2, r3, r8, r9, fp, sp}^
d00164c0:	f852a202 			; <UNDEFINED> instruction: 0xf852a202
d00164c4:	441a3023 	ldrmi	r3, [sl], #-35	; 0xffffffdd
d00164c8:	bf004710 	svclt	0x00004710
d00164cc:	00000035 	andeq	r0, r0, r5, lsr r0
d00164d0:	00000035 	andeq	r0, r0, r5, lsr r0
d00164d4:	00000039 	andeq	r0, r0, r9, lsr r0
d00164d8:	00000039 	andeq	r0, r0, r9, lsr r0
d00164dc:	ffffffad 			; <UNDEFINED> instruction: 0xffffffad
d00164e0:	00000049 	andeq	r0, r0, r9, asr #32
d00164e4:	ffffffcd 			; <UNDEFINED> instruction: 0xffffffcd
d00164e8:	ffffffcd 			; <UNDEFINED> instruction: 0xffffffcd
d00164ec:	ffffffcd 			; <UNDEFINED> instruction: 0xffffffcd
d00164f0:	ffffffcd 			; <UNDEFINED> instruction: 0xffffffcd
d00164f4:	ffffffcd 			; <UNDEFINED> instruction: 0xffffffcd
d00164f8:	0000003d 	andeq	r0, r0, sp, lsr r0
d00164fc:	0000003d 	andeq	r0, r0, sp, lsr r0
d0016500:	e6a62606 	strt	r2, [r6], r6, lsl #12
d0016504:	e6a42607 	strt	r2, [r4], r7, lsl #12
d0016508:	e6a22608 	strt	r2, [r2], r8, lsl #12
d001650c:	e6a0260a 	strt	r2, [r0], sl, lsl #12
d0016510:	e69e2603 	ldr	r2, [lr], r3, lsl #12
d0016514:	e69c2601 	ldr	r2, [ip], r1, lsl #12
d0016518:	e69a2605 	ldr	r2, [sl], r5, lsl #12
d001651c:	e6982604 	ldr	r2, [r8], r4, lsl #12
d0016520:	46204631 			; <UNDEFINED> instruction: 0x46204631
d0016524:	fb79f7fe 	blx	0xd1e94526
d0016528:	463269a3 	ldrtmi	r6, [r2], -r3, lsr #19
d001652c:	ee089904 	vmla.f16	s18, s16, s8
d0016530:	69e33a10 	stmibvs	r3!, {r4, r9, fp, ip, sp}^
d0016534:	46204680 	strtmi	r4, [r0], -r0, lsl #13
d0016538:	3a90ee08 	bcc	0xce451d60
d001653c:	930a6a23 	movwls	r6, #43555	; 0xaa23
d0016540:	93076ae3 	movwls	r6, #31459	; 0x7ae3
d0016544:	fe46f7ff 	mcr2	7, 2, pc, cr6, cr15, {7}	; <UNPREDICTABLE>
d0016548:	2392f504 	orrscs	pc, r2, #4, 10	; 0x1000000
d001654c:	46074ab1 			; <UNDEFINED> instruction: 0x46074ab1
d0016550:	9309213a 	movwls	r2, #37178	; 0x913a
d0016554:	f8d3447a 			; <UNDEFINED> instruction: 0xf8d3447a
d0016558:	46203248 	strtmi	r3, [r0], -r8, asr #4
d001655c:	f7fc9302 			; <UNDEFINED> instruction: 0xf7fc9302
d0016560:	2800fccf 	stmdacs	r0, {r0, r1, r2, r3, r6, r7, sl, fp, ip, sp, lr, pc}
d0016564:	ae9af43f 	mrcge	4, 4, APSR_nzcv, cr10, cr15, {1}
d0016568:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d001656c:	f504fb47 			; <UNDEFINED> instruction: 0xf504fb47
d0016570:	4641328f 	strbmi	r3, [r1], -pc, lsl #5
d0016574:	f8d24633 			; <UNDEFINED> instruction: 0xf8d24633
d0016578:	ee0a21b8 	mcr	1, 0, r2, cr10, cr8, {5}
d001657c:	6da00a10 			; <UNDEFINED> instruction: 0x6da00a10
d0016580:	fd12f7ff 	ldc2	7, cr15, [r2, #-1020]	; 0xfffffc04
d0016584:	463269a3 	ldrtmi	r6, [r2], -r3, lsr #19
d0016588:	ee099904 	vmla.f16	s18, s18, s8
d001658c:	69e33a10 	stmibvs	r3!, {r4, r9, fp, ip, sp}^
d0016590:	ee094620 	cfmadd32	mvax1, mvfx4, mvfx9, mvfx0
d0016594:	6a233a90 	bvs	0xd08e4fdc
d0016598:	6ae3930b 	bvs	0xcf8fb1cc
d001659c:	f7ff9308 			; <UNDEFINED> instruction: 0xf7ff9308
d00165a0:	9a07fe19 	bls	0xd0215e0c
d00165a4:	9b094680 	blls	0xd0267fac
d00165a8:	7281f5a2 	addvc	pc, r1, #679477248	; 0x28800000
d00165ac:	3248f8d3 	subcc	pc, r8, #13828096	; 0xd30000
d00165b0:	d8202a01 	stmdale	r0!, {r0, r9, fp, sp}
d00165b4:	fab29a0a 	blx	0xcecbcde4
d00165b8:	0976f682 	ldmdbeq	r6!, {r1, r7, r9, sl, ip, sp, lr, pc}^
d00165bc:	f5a29a08 			; <UNDEFINED> instruction: 0xf5a29a08
d00165c0:	2a017281 	bcs	0xd0072fcc
d00165c4:	9a0bd82a 	bls	0xd030c674
d00165c8:	f082fab2 			; <UNDEFINED> instruction: 0xf082fab2
d00165cc:	f0270940 			; <UNDEFINED> instruction: 0xf0270940
d00165d0:	2a020204 	bcs	0xd0096de8
d00165d4:	f028d003 			; <UNDEFINED> instruction: 0xf028d003
d00165d8:	2a020204 	bcs	0xd0096df0
d00165dc:	6da3d133 	stfvsd	f5, [r3, #204]!	; 0xcc
d00165e0:	d1392b00 	teqle	r9, r0, lsl #22
d00165e4:	447b4b8c 	ldrbtmi	r4, [fp], #-2956	; 0xfffff474
d00165e8:	3916e9c4 	ldmdbcc	r6, {r2, r6, r7, r8, fp, sp, lr, pc}
d00165ec:	e9c49b01 	stmib	r4, {r0, r8, r9, fp, ip, pc}^
d00165f0:	66a3ba18 	ssatvs	fp, #4, r8, lsl #20
d00165f4:	f240e030 	vqadd.s8	d30, d0, d16
d00165f8:	99071201 	stmdbls	r7, {r0, r9, ip}
d00165fc:	d1dd4291 			; <UNDEFINED> instruction: 0xd1dd4291
d0016600:	ee184a86 	vnmls.f32	s8, s17, s12
d0016604:	ee181a90 	vmov	r1, s17
d0016608:	93040a10 	movwls	r0, #18960	; 0x4a10
d001660c:	f7fa447a 			; <UNDEFINED> instruction: 0xf7fa447a
d0016610:	1e06f97f 			; <UNDEFINED> instruction: 0x1e06f97f
d0016614:	bf189b04 	svclt	0x00189b04
d0016618:	e7cf2601 	strb	r2, [pc, r1, lsl #12]
d001661c:	1201f240 	andne	pc, r1, #64, 4
d0016620:	42919908 	addsmi	r9, r1, #8, 18	; 0x20000
d0016624:	4a7ed10d 	bmi	0xd1fcaa60
d0016628:	1a90ee19 	bne	0xce451e94
d001662c:	0a10ee19 	beq	0xd0451e98
d0016630:	447a9304 	ldrbtmi	r9, [sl], #-772	; 0xfffffcfc
d0016634:	f96cf7fa 			; <UNDEFINED> instruction: 0xf96cf7fa
d0016638:	9b043800 	blls	0xd0124640
d001663c:	2001bf18 	andcs	fp, r1, r8, lsl pc
d0016640:	2000e7c5 	andcs	lr, r0, r5, asr #15
d0016644:	2f01e7c3 	svccs	0x0001e7c3
d0016648:	f1b8d811 			; <UNDEFINED> instruction: 0xf1b8d811
d001664c:	d83b0f01 	ldmdale	fp!, {r0, r8, r9, sl, fp}
d0016650:	bf142f01 	svclt	0x00142f01
d0016654:	25014645 	strcs	r4, [r1, #-1605]	; 0xfffff9bb
d0016658:	328ff504 	addcc	pc, pc, #4, 10	; 0x1000000
d001665c:	ee1a2300 	cdp	3, 1, cr2, cr10, cr0, {0}
d0016660:	6da01a10 			; <UNDEFINED> instruction: 0x6da01a10
d0016664:	21b8f8d2 			; <UNDEFINED> instruction: 0x21b8f8d2
d0016668:	fc9ef7ff 	ldc2	7, cr15, [lr], {255}	; 0xff
d001666c:	4547e616 	strbmi	lr, [r7, #-1558]	; 0xfffff9ea
d0016670:	2f05d120 	svccs	0x0005d120
d0016674:	2f03d001 	svccs	0x0003d001
d0016678:	9a02d115 	bls	0xd00caad4
d001667c:	d012429a 	mulsle	r2, sl, r2
d0016680:	b948b9b6 	stmdblt	r8, {r1, r2, r4, r5, r7, r8, fp, ip, sp, pc}^
d0016684:	b93b6da3 	ldmdblt	fp!, {r0, r1, r5, r7, r8, sl, fp, sp, lr}
d0016688:	447b4b66 	ldrbtmi	r4, [fp], #-2918	; 0xfffff49a
d001668c:	3916e9c4 	ldmdbcc	r6, {r2, r6, r7, r8, fp, sp, lr, pc}
d0016690:	e9c49b01 	stmib	r4, {r0, r8, r9, fp, ip, pc}^
d0016694:	66a3ba18 	ssatvs	fp, #4, r8, lsl #20
d0016698:	2392f504 	orrscs	pc, r2, #4, 10	; 0x1000000
d001669c:	f8c39a02 			; <UNDEFINED> instruction: 0xf8c39a02
d00166a0:	463d2248 	ldrtmi	r2, [sp], -r8, asr #4
d00166a4:	9a02e7d8 	bls	0xd00d060c
d00166a8:	bf182e00 	svclt	0x00182e00
d00166ac:	4613461a 			; <UNDEFINED> instruction: 0x4613461a
d00166b0:	e7f19302 	ldrb	r9, [r1, r2, lsl #6]!
d00166b4:	d1072f04 	tstle	r7, r4, lsl #30
d00166b8:	d1f22800 	mvnsle	r2, r0, lsl #16
d00166bc:	0f04f1b8 	svceq	0x0004f1b8
d00166c0:	b146d112 	cmplt	r6, r2, lsl r1
d00166c4:	e7c74645 	strb	r4, [r7, r5, asr #12]
d00166c8:	0f04f1b8 	svceq	0x0004f1b8
d00166cc:	2e00d109 	mvfcss	f5, #1.0
d00166d0:	2f03d1f8 	svccs	0x0003d1f8
d00166d4:	6da3d007 	stcvs	0, cr13, [r3, #28]!
d00166d8:	d1bd2b00 			; <UNDEFINED> instruction: 0xd1bd2b00
d00166dc:	447b4b52 	ldrbtmi	r4, [fp], #-2898	; 0xfffff4ae
d00166e0:	2f03e782 	svccs	0x0003e782
d00166e4:	b948d100 	stmdblt	r8, {r8, ip, lr, pc}^
d00166e8:	0f03f1b8 	svceq	0x0003f1b8
d00166ec:	2e00d1f3 	mcrcs	1, 0, sp, cr0, cr3, {7}
d00166f0:	9a02d0f1 	bls	0xd00caabc
d00166f4:	bf182f03 	svclt	0x00182f03
d00166f8:	9202461a 	andls	r4, r2, #27262976	; 0x1a00000
d00166fc:	2392f504 	orrscs	pc, r2, #4, 10	; 0x1000000
d0016700:	25039a02 	strcs	r9, [r3, #-2562]	; 0xfffff5fe
d0016704:	2248f8c3 	subcs	pc, r8, #12779520	; 0xc30000
d0016708:	9b03e7a6 	blls	0xd01105a8
d001670c:	d1192b01 	tstle	r9, r1, lsl #22
d0016710:	2b041eeb 	blcs	0xd011e2c4
d0016714:	6da3d809 	stcvs	8, cr13, [r3, #36]!	; 0x24
d0016718:	4b44b93b 	blmi	0xd1144c0c
d001671c:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0016720:	9b013916 	blls	0xd0064b80
d0016724:	ba18e9c4 	blt	0xd0650e3c
d0016728:	f50466a3 			; <UNDEFINED> instruction: 0xf50466a3
d001672c:	46282492 			; <UNDEFINED> instruction: 0x46282492
d0016730:	3244f8d4 	subcc	pc, r4, #212, 16	; 0xd40000
d0016734:	f8c43b01 			; <UNDEFINED> instruction: 0xf8c43b01
d0016738:	b00d3244 	andlt	r3, sp, r4, asr #4
d001673c:	8b06ecbd 	blhi	0xd01d1a38
d0016740:	8ff0e8bd 	svchi	0x00f0e8bd
d0016744:	2b049b03 	blcs	0xd013d358
d0016748:	1eebd1ef 	urdne<illegal precision>z	f5, #10.0
d001674c:	d9ec2b01 	stmible	ip!, {r0, r8, r9, fp, sp}^
d0016750:	f5a39b06 			; <UNDEFINED> instruction: 0xf5a39b06
d0016754:	2b017381 	blcs	0xd0073560
d0016758:	9b05d802 	blls	0xd018c768
d001675c:	d0e42b00 	rscle	r2, r4, r0, lsl #22
d0016760:	2b006da3 	blcs	0xd0031df4
d0016764:	4b32d1e1 	blmi	0xd0ccaef0
d0016768:	e7d8447b 			; <UNDEFINED> instruction: 0xe7d8447b
d001676c:	f43f2e04 			; <UNDEFINED> instruction: 0xf43f2e04
d0016770:	2e03ae5e 	mcrcs	14, 0, sl, cr3, cr14, {2}
d0016774:	ae5bf47f 	mrcge	4, 2, APSR_nzcv, cr11, cr15, {3}
d0016778:	f47f2d00 			; <UNDEFINED> instruction: 0xf47f2d00
d001677c:	2b00ae58 	blcs	0xd00420e4
d0016780:	ae46f47f 	mcrge	4, 2, pc, cr6, cr15, {3}	; <UNPREDICTABLE>
d0016784:	2e04e653 	mcrcs	6, 0, lr, cr4, cr3, {2}
d0016788:	e7f5d1f3 	udf	#23827	; 0x5d13
d001678c:	d1222f2b 			; <UNDEFINED> instruction: 0xd1222f2b
d0016790:	f43f2e04 			; <UNDEFINED> instruction: 0xf43f2e04
d0016794:	2e03ae08 	cdpcs	14, 0, cr10, cr3, cr8, {0}
d0016798:	4620d011 			; <UNDEFINED> instruction: 0x4620d011
d001679c:	f7fe2180 			; <UNDEFINED> instruction: 0xf7fe2180
d00167a0:	f641f987 			; <UNDEFINED> instruction: 0xf641f987
d00167a4:	f6412308 			; <UNDEFINED> instruction: 0xf6412308
d00167a8:	46200108 	strtmi	r0, [r0], -r8, lsl #2
d00167ac:	bf182f2b 	svclt	0x00182f2b
d00167b0:	f7fe4619 			; <UNDEFINED> instruction: 0xf7fe4619
d00167b4:	e53ef97d 	ldr	pc, [lr, #-2429]!	; 0xfffff683
d00167b8:	f47f2f2d 			; <UNDEFINED> instruction: 0xf47f2f2d
d00167bc:	6da3ae0d 	stcvs	14, cr10, [r3, #52]!	; 0x34
d00167c0:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d00167c4:	9b09ad38 	blls	0xd0281cac
d00167c8:	3916e9c4 	ldmdbcc	r6, {r2, r6, r7, r8, fp, sp, lr, pc}
d00167cc:	e9c49b01 	stmib	r4, {r0, r8, r9, fp, ip, pc}^
d00167d0:	66a3ba18 	ssatvs	fp, #4, r8, lsl #20
d00167d4:	2f2de52f 	svccs	0x002de52f
d00167d8:	adfef47f 	cfldrdge	mvd15, [lr, #508]!	; 0x1fc
d00167dc:	d1da2e04 	bicsle	r2, sl, r4, lsl #28
d00167e0:	f6414620 			; <UNDEFINED> instruction: 0xf6414620
d00167e4:	f7fe2108 			; <UNDEFINED> instruction: 0xf7fe2108
d00167e8:	f44ff963 	vst2.16	{d31,d33}, [pc :128], r3
d00167ec:	46205184 	strtmi	r5, [r0], -r4, lsl #3
d00167f0:	f95ef7fe 			; <UNDEFINED> instruction: 0xf95ef7fe
d00167f4:	bf00e5a1 	svclt	0x0000e5a1
d00167f8:	fffffdae 			; <UNDEFINED> instruction: 0xfffffdae
d00167fc:	fffffe28 			; <UNDEFINED> instruction: 0xfffffe28
d0016800:	fffffe05 			; <UNDEFINED> instruction: 0xfffffe05
d0016804:	fffffd84 			; <UNDEFINED> instruction: 0xfffffd84
d0016808:	fffffdfa 			; <UNDEFINED> instruction: 0xfffffdfa
d001680c:	fffffeac 			; <UNDEFINED> instruction: 0xfffffeac
d0016810:	fffffcae 			; <UNDEFINED> instruction: 0xfffffcae
d0016814:	fffffb5a 			; <UNDEFINED> instruction: 0xfffffb5a
d0016818:	fffffaef 			; <UNDEFINED> instruction: 0xfffffaef
d001681c:	ffffeca2 			; <UNDEFINED> instruction: 0xffffeca2
d0016820:	ffffec7c 			; <UNDEFINED> instruction: 0xffffec7c
d0016824:	fffffa73 			; <UNDEFINED> instruction: 0xfffffa73
d0016828:	fffffa53 			; <UNDEFINED> instruction: 0xfffffa53
d001682c:	fffffa66 			; <UNDEFINED> instruction: 0xfffffa66
d0016830:	fffffa43 			; <UNDEFINED> instruction: 0xfffffa43

Disassembly of section .text.int_pointer_element:

d0016878 <.text.int_pointer_element>:
d0016878:	4615b5f8 			; <UNDEFINED> instruction: 0x4615b5f8
d001687c:	460f4a57 			; <UNDEFINED> instruction: 0x460f4a57
d0016880:	447a215b 	ldrbtmi	r2, [sl], #-347	; 0xfffffea5
d0016884:	f7fc4604 			; <UNDEFINED> instruction: 0xf7fc4604
d0016888:	b910fb3b 	ldmdblt	r0, {r0, r1, r3, r4, r5, r8, r9, fp, ip, sp, lr, pc}
d001688c:	46282500 	strtmi	r2, [r8], -r0, lsl #10
d0016890:	f24bbdf8 	vmla.f32	<illegal reg q13.5>, <illegal reg q13.5>, q12
d0016894:	46204103 	strtmi	r4, [r0], -r3, lsl #2
d0016898:	f90af7fe 			; <UNDEFINED> instruction: 0xf90af7fe
d001689c:	46202201 	strtmi	r2, [r0], -r1, lsl #4
d00168a0:	f7ff4611 			; <UNDEFINED> instruction: 0xf7ff4611
d00168a4:	4a4efc97 	bmi	0xd13d5b08
d00168a8:	4620215d 			; <UNDEFINED> instruction: 0x4620215d
d00168ac:	f7fc447a 			; <UNDEFINED> instruction: 0xf7fc447a
d00168b0:	2800fb27 	stmdacs	r0, {r0, r1, r2, r5, r8, r9, fp, ip, sp, lr, pc}
d00168b4:	f64bd0ea 			; <UNDEFINED> instruction: 0xf64bd0ea
d00168b8:	46204106 	strtmi	r4, [r0], -r6, lsl #2
d00168bc:	f8f8f7fe 			; <UNDEFINED> instruction: 0xf8f8f7fe
d00168c0:	46202180 	strtmi	r2, [r0], -r0, lsl #3
d00168c4:	f8f4f7fe 			; <UNDEFINED> instruction: 0xf8f4f7fe
d00168c8:	0108f641 	tsteq	r8, r1, asr #12	; <UNPREDICTABLE>
d00168cc:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d00168d0:	2d00f8ef 	stccs	8, cr15, [r0, #-956]	; 0xfffffc44
d00168d4:	6ae6d142 	bvs	0xcf9cade4
d00168d8:	d0412e3d 	suble	r2, r1, sp, lsr lr
d00168dc:	7192f46f 	orrsvc	pc, r2, pc, ror #8
d00168e0:	2b011873 	blcs	0xd005cab4
d00168e4:	f46fd93c 	vld2.8	{d29,d31}, [pc :256], ip
d00168e8:	18b37294 	ldmne	r3!, {r2, r4, r7, r9, ip, sp, lr}
d00168ec:	d9372b04 	ldmdble	r7!, {r2, r8, r9, fp, sp}
d00168f0:	41d0f44f 	bicsmi	pc, r0, pc, asr #8
d00168f4:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d00168f8:	e7c8f8db 			; <UNDEFINED> instruction: 0xe7c8f8db
d00168fc:	0108f641 	tsteq	r8, r1, asr #12	; <UNPREDICTABLE>
d0016900:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0016904:	f64bf8d5 			; <UNDEFINED> instruction: 0xf64bf8d5
d0016908:	46204106 	strtmi	r4, [r0], -r6, lsl #2
d001690c:	f8d0f7fe 			; <UNDEFINED> instruction: 0xf8d0f7fe
d0016910:	0108f246 	tsteq	r8, r6, asr #4	; <UNPREDICTABLE>
d0016914:	25024620 	strcs	r4, [r2, #-1568]	; 0xfffff9e0
d0016918:	f8caf7fe 			; <UNDEFINED> instruction: 0xf8caf7fe
d001691c:	f641e7b7 			; <UNDEFINED> instruction: 0xf641e7b7
d0016920:	e7ed2108 	strb	r2, [sp, r8, lsl #2]!
d0016924:	0108f244 	tsteq	r8, r4, asr #4	; <UNPREDICTABLE>
d0016928:	f244e7ea 	vabd.s8	q15, q10, q13
d001692c:	e7e73108 	strb	r3, [r7, r8, lsl #2]!
d0016930:	0148f244 	cmpeq	r8, r4, asr #4	; <UNPREDICTABLE>
d0016934:	f244e7e4 	vabd.s8	q15, q10, q10
d0016938:	46206102 	strtmi	r6, [r0], -r2, lsl #2
d001693c:	f8b8f7fe 			; <UNDEFINED> instruction: 0xf8b8f7fe
d0016940:	6108f244 	tstvs	r8, r4, asr #4	; <UNPREDICTABLE>
d0016944:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0016948:	f244f8b3 	vtst.8	d31, d20, d19
d001694c:	f2440190 	vand	d16, d20, d0
d0016950:	f5b61310 			; <UNDEFINED> instruction: 0xf5b61310
d0016954:	bf187f96 	svclt	0x00187f96
d0016958:	e7d14619 	bfi	r4, r9, #12, #6
d001695c:	e7962504 	ldr	r2, [r6, r4, lsl #10]
d0016960:	d0c52f00 	sbcle	r2, r5, r0, lsl #30
d0016964:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0016968:	f24bfa9d 	vpmin.s8	d31, d27, d13
d001696c:	46204103 	strtmi	r4, [r0], -r3, lsl #2
d0016970:	f89ef7fe 			; <UNDEFINED> instruction: 0xf89ef7fe
d0016974:	d0092e3d 	andle	r2, r9, sp, lsr lr
d0016978:	41d0f44f 	bicsmi	pc, r0, pc, asr #8
d001697c:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0016980:	f24bf897 	vtst.8	d31, d27, d7
d0016984:	46204103 	strtmi	r4, [r0], -r3, lsl #2
d0016988:	f892f7fe 			; <UNDEFINED> instruction: 0xf892f7fe
d001698c:	46202201 	strtmi	r2, [r0], -r1, lsl #4
d0016990:	f7ff4611 			; <UNDEFINED> instruction: 0xf7ff4611
d0016994:	2e3dfc1f 	mrccs	12, 1, APSR_nzcv, cr13, cr15, {0}
d0016998:	f64bd0b5 			; <UNDEFINED> instruction: 0xf64bd0b5
d001699c:	46204106 	strtmi	r4, [r0], -r6, lsl #2
d00169a0:	f886f7fe 			; <UNDEFINED> instruction: 0xf886f7fe
d00169a4:	7392f46f 	orrsvc	pc, r2, #1862270976	; 0x6f000000
d00169a8:	2b0818f3 	blcs	0xd021cd7c
d00169ac:	a202d8ab 	andge	sp, r2, #11206656	; 0xab0000
d00169b0:	3023f852 	eorcc	pc, r3, r2, asr r8	; <UNPREDICTABLE>
d00169b4:	4710441a 			; <UNDEFINED> instruction: 0x4710441a
d00169b8:	ffffff45 			; <UNDEFINED> instruction: 0xffffff45
d00169bc:	ffffff67 			; <UNDEFINED> instruction: 0xffffff67
d00169c0:	ffffff4f 			; <UNDEFINED> instruction: 0xffffff4f
d00169c4:	ffffff4f 			; <UNDEFINED> instruction: 0xffffff4f
d00169c8:	ffffff6d 			; <UNDEFINED> instruction: 0xffffff6d
d00169cc:	ffffff73 			; <UNDEFINED> instruction: 0xffffff73
d00169d0:	ffffff79 			; <UNDEFINED> instruction: 0xffffff79
d00169d4:	ffffff7f 			; <UNDEFINED> instruction: 0xffffff7f
d00169d8:	ffffff7f 			; <UNDEFINED> instruction: 0xffffff7f
d00169dc:	ffffffae 			; <UNDEFINED> instruction: 0xffffffae
d00169e0:	ffffffa8 			; <UNDEFINED> instruction: 0xffffffa8

Disassembly of section .text.api_call:

d0016cc0 <.text.api_call>:
d0016cc0:	4ff0e92d 	svcmi	0x00f0e92d
d0016cc4:	8b02ed2d 	blhi	0xd00d2180
d0016cc8:	f891b089 			; <UNDEFINED> instruction: 0xf891b089
d0016ccc:	46043046 	strmi	r3, [r4], -r6, asr #32
d0016cd0:	0548f101 	strbeq	pc, [r8, #-257]	; 0xfffffeff	; <UNPREDICTABLE>
d0016cd4:	23009303 	movwcs	r9, #771	; 0x303
d0016cd8:	93029101 	movwls	r9, #8449	; 0x2101
d0016cdc:	34f0f8df 	ldrbtcc	pc, [r0], #2271	; 0x8df	; <UNPREDICTABLE>
d0016ce0:	ee08447b 	mcr	4, 0, r4, cr8, cr11, {3}
d0016ce4:	f8df3a10 			; <UNDEFINED> instruction: 0xf8df3a10
d0016ce8:	447b34ec 	ldrbtmi	r3, [fp], #-1260	; 0xfffffb14
d0016cec:	f8df9304 			; <UNDEFINED> instruction: 0xf8df9304
d0016cf0:	447b34e8 	ldrbtmi	r3, [fp], #-1256	; 0xfffffb18
d0016cf4:	9b029305 	blls	0xd00bb910
d0016cf8:	42939a03 	addsmi	r9, r3, #12288	; 0x3000
d0016cfc:	6da3d202 	sfmvs	f5, 1, [r3, #8]!
d0016d00:	d03f2b00 	eorsle	r2, pc, r0, lsl #22
d0016d04:	24d4f8df 	ldrbcs	pc, [r4], #2271	; 0x8df	; <UNPREDICTABLE>
d0016d08:	46202129 	strtmi	r2, [r0], -r9, lsr #2
d0016d0c:	f7fc447a 			; <UNDEFINED> instruction: 0xf7fc447a
d0016d10:	2800f8f7 	stmdacs	r0, {r0, r1, r2, r4, r5, r6, r7, fp, ip, sp, lr, pc}
d0016d14:	8256f000 	subshi	pc, r6, #0
d0016d18:	46209903 	strtmi	r9, [r0], -r3, lsl #18
d0016d1c:	ffadf7fd 			; <UNDEFINED> instruction: 0xffadf7fd
d0016d20:	0318f24d 	tsteq	r8, #-805306364	; 0xd0000004	; <UNPREDICTABLE>
d0016d24:	210c4605 	tstcs	ip, r5, lsl #12
d0016d28:	462058e2 	strtmi	r5, [r0], -r2, ror #17
d0016d2c:	fa7bf7fe 	blx	0xd1f14d2c
d0016d30:	f64f9b01 			; <UNDEFINED> instruction: 0xf64f9b01
d0016d34:	f8df79ff 			; <UNDEFINED> instruction: 0xf8df79ff
d0016d38:	f10384a8 			; <UNDEFINED> instruction: 0xf10384a8
d0016d3c:	f1030640 			; <UNDEFINED> instruction: 0xf1030640
d0016d40:	f8360746 			; <UNDEFINED> instruction: 0xf8360746
d0016d44:	454b3b02 	strbmi	r3, [fp, #-2818]	; 0xfffff4fe
d0016d48:	821cf040 	andshi	pc, ip, #64	; 0x40
d0016d4c:	71e0f244 	mvnvc	pc, r4, asr #4
d0016d50:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0016d54:	b12dfead 	msrlt	SP_fiq, sp
d0016d58:	4130f445 	teqmi	r0, r5, asr #8	; <UNPREDICTABLE>
d0016d5c:	b2894620 	addlt	r4, r9, #32, 12	; 0x2000000
d0016d60:	fea6f7fd 	mcr2	7, 5, pc, cr6, cr13, {7}	; <UNPREDICTABLE>
d0016d64:	f8939b01 			; <UNDEFINED> instruction: 0xf8939b01
d0016d68:	2b063047 	blcs	0xd01a2e8c
d0016d6c:	821bf040 	andshi	pc, fp, #64	; 0x40
d0016d70:	21c0f24b 	biccs	pc, r0, fp, asr #4
d0016d74:	b0094620 	andlt	r4, r9, r0, lsr #12
d0016d78:	8b02ecbd 	blhi	0xd00d2074
d0016d7c:	4ff0e8bd 	svcmi	0x00f0e8bd
d0016d80:	be96f7fd 	mrclt	7, 4, APSR_nzcv, cr6, cr13, {7}
d0016d84:	b12b9b02 			; <UNDEFINED> instruction: 0xb12b9b02
d0016d88:	2a10ee18 	bcs	0xd04525f0
d0016d8c:	4620212c 	strtmi	r2, [r0], -ip, lsr #2
d0016d90:	f8b6f7fc 			; <UNDEFINED> instruction: 0xf8b6f7fc
d0016d94:	b000f895 	mullt	r0, r5, r8
d0016d98:	33fff10b 	mvnscc	pc, #-1073741822	; 0xc0000002
d0016d9c:	f2002b15 	vpadd.i8	d2, d0, d5
d0016da0:	e8df81c9 	ldm	pc, {r0, r3, r6, r7, r8, pc}^	; <UNPREDICTABLE>
d0016da4:	0023f013 	eoreq	pc, r3, r3, lsl r0	; <UNPREDICTABLE>
d0016da8:	01c70016 	biceq	r0, r7, r6, lsl r0
d0016dac:	01c701c7 	biceq	r0, r7, r7, asr #3
d0016db0:	01c701c7 	biceq	r0, r7, r7, asr #3
d0016db4:	002e01c7 	eoreq	r0, lr, r7, asr #3
d0016db8:	01c7002e 	biceq	r0, r7, lr, lsr #32
d0016dbc:	00b0002e 	adcseq	r0, r0, lr, lsr #32
d0016dc0:	015e0195 			; <UNDEFINED> instruction: 0x015e0195
d0016dc4:	01c701c7 	biceq	r0, r7, r7, asr #3
d0016dc8:	00f000f0 	ldrshteq	r0, [r0], #0
d0016dcc:	00f0002e 	rscseq	r0, r0, lr, lsr #32
d0016dd0:	46200158 			; <UNDEFINED> instruction: 0x46200158
d0016dd4:	f94cf7fe 			; <UNDEFINED> instruction: 0xf94cf7fe
d0016dd8:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d0016ddc:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0016de0:	9b02fe67 	blls	0xd00d6784
d0016de4:	33013501 	movwcc	r3, #5377	; 0x1501
d0016de8:	e7849302 	str	r9, [r4, r2, lsl #6]
d0016dec:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0016df0:	2800fa63 	stmdacs	r0, {r0, r1, r5, r6, r9, fp, ip, sp, lr, pc}
d0016df4:	49fbd1f0 	ldmibmi	fp!, {r4, r5, r6, r7, r8, ip, lr, pc}^
d0016df8:	46204479 			; <UNDEFINED> instruction: 0x46204479
d0016dfc:	fa26f7f9 	blx	0xd09d4de8
d0016e00:	4620e7ea 	strtmi	lr, [r0], -sl, ror #15
d0016e04:	fa58f7fe 	blx	0xd1654e04
d0016e08:	d1e52800 	mvnle	r2, r0, lsl #16
d0016e0c:	46202126 	strtmi	r2, [r0], -r6, lsr #2
d0016e10:	f868f7fc 			; <UNDEFINED> instruction: 0xf868f7fc
d0016e14:	f2406ae2 	vpmax.s8	q11, q8, q9
d0016e18:	f8d41301 			; <UNDEFINED> instruction: 0xf8d41301
d0016e1c:	f8d4a024 			; <UNDEFINED> instruction: 0xf8d4a024
d0016e20:	429a9028 	addsmi	r9, sl, #40	; 0x28
d0016e24:	8030f894 	mlashi	r0, r4, r8, pc	; <UNPREDICTABLE>
d0016e28:	d0066b67 	andle	r6, r6, r7, ror #22
d0016e2c:	2b006da3 	blcs	0xd00324c0
d0016e30:	4bedd1d2 	blmi	0xcfb8b580
d0016e34:	65a3447b 	strvs	r4, [r3, #1147]!	; 0x47b
d0016e38:	e9d4e02e 	ldmib	r4, {r1, r2, r3, r5, sp, lr, pc}^
d0016e3c:	46201206 	strtmi	r1, [r0], -r6, lsl #4
d0016e40:	91069207 	tstls	r6, r7, lsl #4
d0016e44:	fd3bf7f9 	ldc2	7, cr15, [fp, #-996]!	; 0xfffffc1c
d0016e48:	dbef1e06 	blle	0xcfbde668
d0016e4c:	46209a07 	strtmi	r9, [r0], -r7, lsl #20
d0016e50:	f7f99906 			; <UNDEFINED> instruction: 0xf7f99906
d0016e54:	2800fcab 	stmdacs	r0, {r0, r1, r3, r5, r7, sl, fp, ip, sp, lr, pc}
d0016e58:	f1bbdae8 			; <UNDEFINED> instruction: 0xf1bbdae8
d0016e5c:	d0210f0c 	eorle	r0, r1, ip, lsl #30
d0016e60:	0f14f1bb 	svceq	0x0014f1bb
d0016e64:	f1bbd027 			; <UNDEFINED> instruction: 0xf1bbd027
d0016e68:	d12d0f09 			; <UNDEFINED> instruction: 0xd12d0f09
d0016e6c:	b37cf8df 	cmnlt	ip, #14614528	; 0xdf0000	; <UNPREDICTABLE>
d0016e70:	0c01f04f 	stceq	0, cr15, [r1], {79}	; 0x4f
d0016e74:	220549de 	andcs	r4, r5, #3637248	; 0x378000
d0016e78:	447944fb 	ldrbtmi	r4, [r9], #-1275	; 0xfffffb05
d0016e7c:	43732338 	cmnmi	r3, #56, 6	; 0xe0000000
d0016e80:	f50018e0 			; <UNDEFINED> instruction: 0xf50018e0
d0016e84:	f890307f 			; <UNDEFINED> instruction: 0xf890307f
d0016e88:	45e6e24f 	strbmi	lr, [r6, #591]!	; 0x24f
d0016e8c:	6da3d025 	stcvs	0, cr13, [r3, #148]!	; 0x94
d0016e90:	d1a12b00 			; <UNDEFINED> instruction: 0xd1a12b00
d0016e94:	b058f8c4 	subslt	pc, r8, r4, asr #17
d0016e98:	a05cf8c4 	subsge	pc, ip, r4, asr #17
d0016e9c:	e9c466a7 	stmib	r4, {r0, r1, r2, r5, r7, r9, sl, sp, lr}^
d0016ea0:	e7999818 			; <UNDEFINED> instruction: 0xe7999818
d0016ea4:	b34cf8df 	movtlt	pc, #51423	; 0xc8df	; <UNPREDICTABLE>
d0016ea8:	0c02f04f 	stceq	0, cr15, [r2], {79}	; 0x4f
d0016eac:	44fb49d2 	ldrbtmi	r4, [fp], #2514	; 0x9d2
d0016eb0:	44794662 	ldrbtmi	r4, [r9], #-1634	; 0xfffff99e
d0016eb4:	f8dfe7e2 			; <UNDEFINED> instruction: 0xf8dfe7e2
d0016eb8:	f04fb344 			; <UNDEFINED> instruction: 0xf04fb344
d0016ebc:	49d00c01 	ldmibmi	r0, {r0, sl, fp}^
d0016ec0:	44fb2203 	ldrbtmi	r2, [fp], #515	; 0x203
d0016ec4:	e7d94479 			; <UNDEFINED> instruction: 0xe7d94479
d0016ec8:	b338f8df 	teqlt	r8, #14614528	; 0xdf0000	; <UNPREDICTABLE>
d0016ecc:	0c01f04f 	stceq	0, cr15, [r1], {79}	; 0x4f
d0016ed0:	44fb49cd 	ldrbtmi	r4, [fp], #2509	; 0x9cd
d0016ed4:	44794662 	ldrbtmi	r4, [r9], #-1634	; 0xfffff99e
d0016ed8:	f890e7d0 			; <UNDEFINED> instruction: 0xf890e7d0
d0016edc:	4290024c 	addsmi	r0, r0, #76, 4	; 0xc0000004
d0016ee0:	f503d1d5 			; <UNDEFINED> instruction: 0xf503d1d5
d0016ee4:	f200307f 	vqadd.s8	<illegal reg q1.5>, q0, <illegal reg q15.5>
d0016ee8:	44202053 	strtmi	r2, [r0], #-83	; 0xffffffad
d0016eec:	f824f00a 			; <UNDEFINED> instruction: 0xf824f00a
d0016ef0:	d1cc2800 	bicle	r2, ip, r0, lsl #16
d0016ef4:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0016ef8:	4632ffd5 			; <UNDEFINED> instruction: 0x4632ffd5
d0016efc:	46202102 	strtmi	r2, [r0], -r2, lsl #2
d0016f00:	fe3ef7fd 	mrc2	7, 1, pc, cr14, cr13, {7}
d0016f04:	4620e768 	strtmi	lr, [r0], -r8, ror #14
d0016f08:	f9d6f7fe 			; <UNDEFINED> instruction: 0xf9d6f7fe
d0016f0c:	f47f2800 			; <UNDEFINED> instruction: 0xf47f2800
d0016f10:	4abeaf63 	bmi	0xcefc2ca4
d0016f14:	46202126 	strtmi	r2, [r0], -r6, lsr #2
d0016f18:	f7fb447a 			; <UNDEFINED> instruction: 0xf7fb447a
d0016f1c:	2800fff1 	stmdacs	r0, {r0, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0016f20:	af5af43f 	svcge	0x005af43f
d0016f24:	f2406ae2 	vpmax.s8	q11, q8, q9
d0016f28:	f8d41301 			; <UNDEFINED> instruction: 0xf8d41301
d0016f2c:	429aa024 	addsmi	sl, sl, #36	; 0x24
d0016f30:	9028f8d4 	ldrdls	pc, [r8], -r4	; <UNPREDICTABLE>
d0016f34:	8030f894 	mlashi	r0, r4, r8, pc	; <UNPREDICTABLE>
d0016f38:	d0066b67 	andle	r6, r6, r7, ror #22
d0016f3c:	2b006da3 	blcs	0xd00325d0
d0016f40:	af4af47f 	svcge	0x004af47f
d0016f44:	447b4bb2 	ldrbtmi	r4, [fp], #-2994	; 0xfffff44e
d0016f48:	e9d4e775 	ldmib	r4, {r0, r2, r4, r5, r6, r8, r9, sl, sp, lr, pc}^
d0016f4c:	46201206 	strtmi	r1, [r0], -r6, lsl #4
d0016f50:	91069207 	tstls	r6, r7, lsl #4
d0016f54:	fc4af7f9 	mcrr2	7, 15, pc, sl, cr9	; <UNPREDICTABLE>
d0016f58:	dbef1e06 	blle	0xcfbde778
d0016f5c:	46209a07 	strtmi	r9, [r0], -r7, lsl #20
d0016f60:	f7f99906 			; <UNDEFINED> instruction: 0xf7f99906
d0016f64:	2800fc23 	stmdacs	r0, {r0, r1, r5, sl, fp, ip, sp, lr, pc}
d0016f68:	233cdae8 	teqcs	ip, #232, 20	; 0xe8000
d0016f6c:	4306fb03 	movwmi	pc, #27395	; 0x6b03	; <UNPREDICTABLE>
d0016f70:	335ff503 	cmpcc	pc, #12582912	; 0xc00000	; <UNPREDICTABLE>
d0016f74:	33ecf893 	mvncc	pc, #9633792	; 0x930000
d0016f78:	d1df2b05 	bicsle	r2, pc, r5, lsl #22
d0016f7c:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0016f80:	4632ff91 	shadd8mi	pc, r2, r1	; <UNPREDICTABLE>
d0016f84:	f1bbe051 			; <UNDEFINED> instruction: 0xf1bbe051
d0016f88:	d01e0f15 	andsle	r0, lr, r5, lsl pc
d0016f8c:	2b13782b 	blcs	0xd04f5040
d0016f90:	4ea0d122 	tanmisp	f5, f2
d0016f94:	4632447e 			; <UNDEFINED> instruction: 0x4632447e
d0016f98:	46202126 	strtmi	r2, [r0], -r6, lsr #2
d0016f9c:	ffb0f7fb 			; <UNDEFINED> instruction: 0xffb0f7fb
d0016fa0:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0016fa4:	6ae2af19 	bvs	0xcf8c2c10
d0016fa8:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d0016fac:	a024f8d4 	ldrdge	pc, [r4], -r4	; <UNPREDICTABLE>
d0016fb0:	f8d4429a 			; <UNDEFINED> instruction: 0xf8d4429a
d0016fb4:	f8949028 			; <UNDEFINED> instruction: 0xf8949028
d0016fb8:	6b678030 	blvs	0xd19f7080
d0016fbc:	6da3d014 	stcvs	0, cr13, [r3, #80]!	; 0x50
d0016fc0:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0016fc4:	65a6af09 	strvs	sl, [r6, #3849]!	; 0xf09
d0016fc8:	4620e766 	strtmi	lr, [r0], -r6, ror #14
d0016fcc:	f974f7fe 			; <UNDEFINED> instruction: 0xf974f7fe
d0016fd0:	f47f2800 			; <UNDEFINED> instruction: 0xf47f2800
d0016fd4:	e7d9af01 	ldrb	sl, [r9, r1, lsl #30]
d0016fd8:	d0022b12 	andle	r2, r2, r2, lsl fp
d0016fdc:	447e4e8e 	ldrbtmi	r4, [lr], #-3726	; 0xfffff172
d0016fe0:	4e8ee7d9 	mcrmi	7, 4, lr, cr14, cr9, {6}
d0016fe4:	e7d6447e 			; <UNDEFINED> instruction: 0xe7d6447e
d0016fe8:	1206e9d4 	andne	lr, r6, #212, 18	; 0x350000
d0016fec:	92074620 	andls	r4, r7, #32, 12	; 0x2000000
d0016ff0:	f7f99106 			; <UNDEFINED> instruction: 0xf7f99106
d0016ff4:	f1b0fbfb 			; <UNDEFINED> instruction: 0xf1b0fbfb
d0016ff8:	dbe00b00 	blle	0xcf819c00
d0016ffc:	46209a07 	strtmi	r9, [r0], -r7, lsl #20
d0017000:	f7f99906 			; <UNDEFINED> instruction: 0xf7f99906
d0017004:	2800fbd3 	stmdacs	r0, {r0, r1, r4, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d0017008:	782bdad9 	stmdavc	fp!, {r0, r3, r4, r6, r7, r9, fp, ip, lr, pc}
d001700c:	d1162b12 	tstle	r6, r2, lsl fp
d0017010:	fb03233c 	blx	0xd00dfd0a
d0017014:	f503430b 			; <UNDEFINED> instruction: 0xf503430b
d0017018:	f893335f 			; <UNDEFINED> instruction: 0xf893335f
d001701c:	2b0133ec 	blcs	0xd0063fd4
d0017020:	4620d8cd 	strtmi	sp, [r0], -sp, asr #17
d0017024:	ff3ef7fb 			; <UNDEFINED> instruction: 0xff3ef7fb
d0017028:	2101465a 	tstcs	r1, sl, asr r6
d001702c:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0017030:	f244fda7 	vadd.f32	d31, d20, d23
d0017034:	46206108 	strtmi	r6, [r0], -r8, lsl #2
d0017038:	fd3af7fd 	ldc2	7, cr15, [sl, #-1012]!	; 0xfffffc0c
d001703c:	2b13e6cc 	blcs	0xd0510b74
d0017040:	233cd1ef 	teqcs	ip, #-1073741765	; 0xc000003b
d0017044:	430bfb03 	movwmi	pc, #47875	; 0xbb03	; <UNPREDICTABLE>
d0017048:	335ff503 	cmpcc	pc, #12582912	; 0xc00000	; <UNPREDICTABLE>
d001704c:	33ecf893 	mvncc	pc, #9633792	; 0x930000
d0017050:	d1b42b0f 			; <UNDEFINED> instruction: 0xd1b42b0f
d0017054:	2202e7e5 	andcs	lr, r2, #60030976	; 0x3940000
d0017058:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d001705c:	f8baf7ff 			; <UNDEFINED> instruction: 0xf8baf7ff
d0017060:	4620e6ba 			; <UNDEFINED> instruction: 0x4620e6ba
d0017064:	f928f7fe 			; <UNDEFINED> instruction: 0xf928f7fe
d0017068:	496db110 	stmdbmi	sp!, {r4, r8, ip, sp, pc}^
d001706c:	e6c44479 	uxtab16	r4, r4, r9, ror #8
d0017070:	f2406ae2 	vpmax.s8	q11, q8, q9
d0017074:	f8d41301 			; <UNDEFINED> instruction: 0xf8d41301
d0017078:	429aa024 	addsmi	sl, sl, #36	; 0x24
d001707c:	9028f8d4 	ldrdls	pc, [r8], -r4	; <UNPREDICTABLE>
d0017080:	8030f894 	mlashi	r0, r4, r8, pc	; <UNPREDICTABLE>
d0017084:	d0056b67 	andle	r6, r5, r7, ror #22
d0017088:	2b006da3 	blcs	0xd003271c
d001708c:	aea4f47f 	mcrge	4, 5, pc, cr4, cr15, {3}	; <UNPREDICTABLE>
d0017090:	e6d09b05 	ldrb	r9, [r0], r5, lsl #22
d0017094:	1206e9d4 	andne	lr, r6, #212, 18	; 0x350000
d0017098:	92074620 	andls	r4, r7, #32, 12	; 0x2000000
d001709c:	f7f99106 			; <UNDEFINED> instruction: 0xf7f99106
d00170a0:	1e06fba5 	vmlane.f64	d15, d22, d21
d00170a4:	9a07dbf0 	bls	0xd020e06c
d00170a8:	99064620 	stmdbls	r6, {r5, r9, sl, lr}
d00170ac:	fb7ef7f9 	blx	0xd1fd509a
d00170b0:	dae92800 	ble	0xcfa610b8
d00170b4:	fb03233c 	blx	0xd00dfdae
d00170b8:	f5034306 			; <UNDEFINED> instruction: 0xf5034306
d00170bc:	f893335f 			; <UNDEFINED> instruction: 0xf893335f
d00170c0:	2a0823ec 	bcs	0xd0220078
d00170c4:	f8d3d1e0 			; <UNDEFINED> instruction: 0xf8d3d1e0
d00170c8:	2bff33fc 	blcs	0xcffe40c0
d00170cc:	e755d9dc 	smmls	r5, ip, r9, sp
d00170d0:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d00170d4:	2800f8f1 	stmdacs	r0, {r0, r4, r5, r6, r7, fp, ip, sp, lr, pc}
d00170d8:	ae7ef47f 	mrcge	4, 3, APSR_nzcv, cr14, cr15, {3}
d00170dc:	f2406ae2 	vpmax.s8	q11, q8, q9
d00170e0:	f8d41301 			; <UNDEFINED> instruction: 0xf8d41301
d00170e4:	429aa024 	addsmi	sl, sl, #36	; 0x24
d00170e8:	9028f8d4 	ldrdls	pc, [r8], -r4	; <UNPREDICTABLE>
d00170ec:	8030f894 	mlashi	r0, r4, r8, pc	; <UNPREDICTABLE>
d00170f0:	d0056b67 	andle	r6, r5, r7, ror #22
d00170f4:	2b006da3 	blcs	0xd0032788
d00170f8:	ae6ef47f 	mcrge	4, 3, pc, cr14, cr15, {3}	; <UNPREDICTABLE>
d00170fc:	e69a9b04 	ldr	r9, [sl], r4, lsl #22
d0017100:	1206e9d4 	andne	lr, r6, #212, 18	; 0x350000
d0017104:	92074620 	andls	r4, r7, #32, 12	; 0x2000000
d0017108:	f7f99106 			; <UNDEFINED> instruction: 0xf7f99106
d001710c:	1e06fb6f 	vmlsne.f64	d15, d6, d31
d0017110:	9a07dbf0 	bls	0xd020e0d8
d0017114:	99064620 	stmdbls	r6, {r5, r9, sl, lr}
d0017118:	fb48f7f9 	blx	0xd1255106
d001711c:	dae92800 	ble	0xcfa61124
d0017120:	fb03233c 	blx	0xd00dfe1a
d0017124:	f5034306 			; <UNDEFINED> instruction: 0xf5034306
d0017128:	f893335f 			; <UNDEFINED> instruction: 0xf893335f
d001712c:	2b0733ec 	blcs	0xd01e40e4
d0017130:	e723d1e0 	str	sp, [r3, -r0, ror #3]!
d0017134:	46202201 	strtmi	r2, [r0], -r1, lsl #4
d0017138:	f7ff4611 			; <UNDEFINED> instruction: 0xf7ff4611
d001713c:	782bf84b 	stmdavc	fp!, {r0, r1, r3, r6, fp, ip, sp, lr, pc}
d0017140:	2b053b03 	blcs	0xd0165d54
d0017144:	ae48f63f 	mcrge	6, 2, pc, cr8, cr15, {1}	; <UNPREDICTABLE>
d0017148:	f852a202 			; <UNDEFINED> instruction: 0xf852a202
d001714c:	441a3023 	ldrmi	r3, [sl], #-35	; 0xffffffdd
d0017150:	bf004710 	svclt	0x00004710
d0017154:	00000019 	andeq	r0, r0, r9, lsl r0
d0017158:	0000001f 	andeq	r0, r0, pc, lsl r0
d001715c:	fffffc85 			; <UNDEFINED> instruction: 0xfffffc85
d0017160:	0000002b 	andeq	r0, r0, fp, lsr #32
d0017164:	fffffc85 			; <UNDEFINED> instruction: 0xfffffc85
d0017168:	00000025 	andeq	r0, r0, r5, lsr #32
d001716c:	4132f44f 	teqmi	r2, pc, asr #8	; <UNPREDICTABLE>
d0017170:	f24be761 	vabd.s8	q15, <illegal reg q5.5>, <illegal reg q8.5>
d0017174:	e75e2180 	ldrb	r2, [lr, -r0, lsl #3]
d0017178:	2140f24b 	cmpcs	r0, fp, asr #4	; <UNPREDICTABLE>
d001717c:	f24be75b 	vaba.s8	q15, <illegal reg q5.5>, <illegal reg q5.5>
d0017180:	e75821c0 	ldrb	r2, [r8, -r0, asr #3]
d0017184:	01dcf64f 	bicseq	pc, ip, pc, asr #12
d0017188:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d001718c:	f836fc91 			; <UNDEFINED> instruction: 0xf836fc91
d0017190:	46201c02 	strtmi	r1, [r0], -r2, lsl #24
d0017194:	0108ea41 	tsteq	r8, r1, asr #20
d0017198:	f7fdb289 			; <UNDEFINED> instruction: 0xf7fdb289
d001719c:	42befc89 	adcsmi	pc, lr, #35072	; 0x8900
d00171a0:	adcff47f 	cfstrdge	mvd15, [pc, #508]	; 0xd00173a4
d00171a4:	2b08e5d2 	blcs	0xd02508f4
d00171a8:	f24bd102 	vrhadd.s8	d29, d11, d2
d00171ac:	e5e12140 	strb	r2, [r1, #320]!	; 0x140
d00171b0:	d1022b10 	tstle	r2, r0, lsl fp
d00171b4:	2180f24b 	orrcs	pc, r0, fp, asr #4
d00171b8:	2b11e5dc 	blcs	0xd0490930
d00171bc:	f44fd102 	vst4.8	{d29,d31,d33,d35}, [pc], r2
d00171c0:	e5d74132 	ldrb	r4, [r7, #306]	; 0x132
d00171c4:	ecbdb009 	ldc	0, cr11, [sp], #36	; 0x24
d00171c8:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d00171cc:	bf008ff0 	svclt	0x00008ff0
d00171d0:	fffffe86 			; <UNDEFINED> instruction: 0xfffffe86
d00171d4:	ffffff79 			; <UNDEFINED> instruction: 0xffffff79
d00171d8:	ffffff41 			; <UNDEFINED> instruction: 0xffffff41
d00171dc:	ffffff86 			; <UNDEFINED> instruction: 0xffffff86
d00171e0:	ffffc000 			; <UNDEFINED> instruction: 0xffffc000
d00171e4:	fffffd91 			; <UNDEFINED> instruction: 0xfffffd91
d00171e8:	fffffd79 			; <UNDEFINED> instruction: 0xfffffd79
d00171ec:	fffffc07 			; <UNDEFINED> instruction: 0xfffffc07
d00171f0:	00007f4f 	andeq	r7, r0, pc, asr #30
d00171f4:	fffffb55 			; <UNDEFINED> instruction: 0xfffffb55
d00171f8:	0000819c 	muleq	r0, ip, r1
d00171fc:	fffffb87 			; <UNDEFINED> instruction: 0xfffffb87
d0017200:	00007f0a 	andeq	r7, r0, sl, lsl #30
d0017204:	fffffb0e 			; <UNDEFINED> instruction: 0xfffffb0e
d0017208:	00008177 	andeq	r8, r0, r7, ror r1
d001720c:	fffffcc3 			; <UNDEFINED> instruction: 0xfffffcc3
d0017210:	fffffc95 			; <UNDEFINED> instruction: 0xfffffc95
d0017214:	fffffb33 			; <UNDEFINED> instruction: 0xfffffb33
d0017218:	fffffb4f 			; <UNDEFINED> instruction: 0xfffffb4f
d001721c:	fffffb12 			; <UNDEFINED> instruction: 0xfffffb12
d0017220:	fffffba8 			; <UNDEFINED> instruction: 0xfffffba8

Disassembly of section .text.indirect_call:

d0017288 <.text.indirect_call>:
d0017288:	fb032330 	blx	0xd00dff52
d001728c:	e92d0301 	push	{r0, r8, r9}
d0017290:	f50341f0 			; <UNDEFINED> instruction: 0xf50341f0
d0017294:	f8df2390 			; <UNDEFINED> instruction: 0xf8df2390
d0017298:	460480a4 	strmi	r8, [r4], -r4, lsr #1
d001729c:	f893460d 			; <UNDEFINED> instruction: 0xf893460d
d00172a0:	2600765b 			; <UNDEFINED> instruction: 0x2600765b
d00172a4:	42be44f8 	adcsmi	r4, lr, #248, 8	; 0xf8000000
d00172a8:	6da3d201 	sfmvs	f5, 1, [r3, #4]!
d00172ac:	4639b37b 			; <UNDEFINED> instruction: 0x4639b37b
d00172b0:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d00172b4:	4a22fce2 	bmi	0xd08d6644
d00172b8:	21294606 			; <UNDEFINED> instruction: 0x21294606
d00172bc:	4620447a 			; <UNDEFINED> instruction: 0x4620447a
d00172c0:	fe1ef7fb 	mrc2	7, 0, pc, cr14, cr11, {7}
d00172c4:	f64fb300 			; <UNDEFINED> instruction: 0xf64fb300
d00172c8:	462001d7 			; <UNDEFINED> instruction: 0x462001d7
d00172cc:	fbf0f7fd 	blx	0xcfc552ca
d00172d0:	46204919 			; <UNDEFINED> instruction: 0x46204919
d00172d4:	0185ea41 	orreq	lr, r5, r1, asr #20
d00172d8:	f7fdb289 			; <UNDEFINED> instruction: 0xf7fdb289
d00172dc:	f244fbe9 	vqdmulh.s<illegal width 8>	<illegal reg q15.5>, q10, <illegal reg q12.5>
d00172e0:	462071e0 	strtmi	r7, [r0], -r0, ror #3
d00172e4:	fbe4f7fd 	blx	0xcf9552e2
d00172e8:	f446b12e 	vst4.8	{d27,d29,d31,d33}, [r6 :128], lr
d00172ec:	46204130 			; <UNDEFINED> instruction: 0x46204130
d00172f0:	f7fdb289 			; <UNDEFINED> instruction: 0xf7fdb289
d00172f4:	2030fbdd 	ldrsbtcs	pc, [r0], -sp	; <UNPREDICTABLE>
d00172f8:	4405fb00 	strmi	pc, [r5], #-2816	; 0xfffff500
d00172fc:	2490f504 	ldrcs	pc, [r0], #1284	; 0x504
d0017300:	365cf894 			; <UNDEFINED> instruction: 0x365cf894
d0017304:	d0142b01 	andsle	r2, r4, r1, lsl #22
d0017308:	e8bd2000 	ldmfd	sp!, {sp}
d001730c:	b12681f0 	strdlt	r8, [r6, -r0]!
d0017310:	212c4642 			; <UNDEFINED> instruction: 0x212c4642
d0017314:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0017318:	2201fdf3 	andcs	pc, r1, #15552	; 0x3cc0
d001731c:	36014620 	strcc	r4, [r1], -r0, lsr #12
d0017320:	f7fe4611 			; <UNDEFINED> instruction: 0xf7fe4611
d0017324:	f24bff57 	vrecps.f32	<illegal reg q15.5>, <illegal reg q5.5>, <illegal reg q3.5>
d0017328:	46204103 	strtmi	r4, [r0], -r3, lsl #2
d001732c:	fbc0f7fd 	blx	0xcf05532a
d0017330:	2002e7b9 			; <UNDEFINED> instruction: 0x2002e7b9
d0017334:	bf00e7e9 	svclt	0x0000e7e9
d0017338:	ffffc000 			; <UNDEFINED> instruction: 0xffffc000
d001733c:	ffffff7c 			; <UNDEFINED> instruction: 0xffffff7c
d0017340:	ffffff94 			; <UNDEFINED> instruction: 0xffffff94

Disassembly of section .text.struct_array_element:

d00173bc <.text.struct_array_element>:
d00173bc:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d00173c0:	4a264617 	bmi	0xd09a8c24
d00173c4:	215b460d 	cmpcs	fp, sp, lsl #12
d00173c8:	4604447a 			; <UNDEFINED> instruction: 0x4604447a
d00173cc:	f7fb461e 			; <UNDEFINED> instruction: 0xf7fb461e
d00173d0:	2800fd97 	stmdacs	r0, {r0, r1, r2, r4, r7, r8, sl, fp, ip, sp, lr, pc}
d00173d4:	f24bd03e 	vqadd.s8	d29, d11, d30
d00173d8:	46204103 	strtmi	r4, [r0], -r3, lsl #2
d00173dc:	fb68f7fd 	blx	0xd1a553da
d00173e0:	46202201 	strtmi	r2, [r0], -r1, lsl #4
d00173e4:	f7fe4611 			; <UNDEFINED> instruction: 0xf7fe4611
d00173e8:	4a1dfef5 	bmi	0xd0796fc4
d00173ec:	4620215d 			; <UNDEFINED> instruction: 0x4620215d
d00173f0:	f7fb447a 			; <UNDEFINED> instruction: 0xf7fb447a
d00173f4:	b368fd85 	msrlt	SPSR_f, #8512	; 0x2140
d00173f8:	4106f64b 	tstmi	r6, fp, asr #12	; <UNPREDICTABLE>
d00173fc:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0017400:	f44ffb57 			; <UNDEFINED> instruction: 0xf44ffb57
d0017404:	2102701a 	tstcs	r2, sl, lsl r0
d0017408:	4005fb00 	andmi	pc, r5, r0, lsl #22
d001740c:	3068f500 	rsbcc	pc, r8, r0, lsl #10
d0017410:	46208d02 	strtmi	r8, [r0], -r2, lsl #26
d0017414:	f7fd0092 			; <UNDEFINED> instruction: 0xf7fd0092
d0017418:	f244ff06 	vmax.f32	d31, d4, d6
d001741c:	46203150 			; <UNDEFINED> instruction: 0x46203150
d0017420:	fb46f7fd 	blx	0xd11d541e
d0017424:	51c2f44f 	bicpl	pc, r2, pc, asr #8
d0017428:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d001742c:	b98efb41 	stmiblt	lr, {r0, r6, r8, r9, fp, ip, sp, lr, pc}
d0017430:	4620212e 	strtmi	r2, [r0], -lr, lsr #2
d0017434:	fd56f7fb 	ldc2l	7, cr15, [r6, #-1004]	; 0xfffffc14
d0017438:	4633b138 			; <UNDEFINED> instruction: 0x4633b138
d001743c:	4629463a 			; <UNDEFINED> instruction: 0x4629463a
d0017440:	e8bd4620 	pop	{r5, r9, sl, lr}
d0017444:	f00041f0 			; <UNDEFINED> instruction: 0xf00041f0
d0017448:	4906bfa5 	stmdbmi	r6, {r0, r2, r5, r7, r8, r9, sl, fp, ip, sp, pc}
d001744c:	44794620 	ldrbtmi	r4, [r9], #-1568	; 0xfffff9e0
d0017450:	fefcf7f8 	mrc2	7, 7, pc, cr12, cr8, {7}
d0017454:	e8bd2003 	pop	{r0, r1, sp}
d0017458:	bf0081f0 	svclt	0x000081f0
d001745c:	ffffff78 			; <UNDEFINED> instruction: 0xffffff78
d0017460:	ffffff70 			; <UNDEFINED> instruction: 0xffffff70
d0017464:	ffffff38 			; <UNDEFINED> instruction: 0xffffff38

Disassembly of section .text.record_value_address:

d0017574 <.text.record_value_address>:
d0017574:	e92d4a54 	push	{r2, r4, r6, r9, fp, lr}
d0017578:	447a4ff0 	ldrbtmi	r4, [sl], #-4080	; 0xfffff010
d001757c:	4689b087 	strmi	fp, [r9], r7, lsl #1
d0017580:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d0017584:	6a454604 	bvs	0xd1168d9c
d0017588:	f8906a86 			; <UNDEFINED> instruction: 0xf8906a86
d001758c:	f8d07030 			; <UNDEFINED> instruction: 0xf8d07030
d0017590:	e9d08034 	ldmib	r0, {r2, r4, r5, pc}^
d0017594:	f7fbab06 			; <UNDEFINED> instruction: 0xf7fbab06
d0017598:	b1f0fcb3 	ldrhlt	pc, [r0, #195]!	; 0xc3	; <UNPREDICTABLE>
d001759c:	46202128 	strtmi	r2, [r0], -r8, lsr #2
d00175a0:	fca0f7fb 	stc2	7, cr15, [r0], #1004	; 0x3ec
d00175a4:	462bb1e0 	strtmi	fp, [fp], -r0, ror #3
d00175a8:	4651465a 			; <UNDEFINED> instruction: 0x4651465a
d00175ac:	e88d4620 	stm	sp, {r5, r9, sl, lr}
d00175b0:	f00001c0 			; <UNDEFINED> instruction: 0xf00001c0
d00175b4:	2806f959 	stmdacs	r6, {r0, r3, r4, r6, r8, fp, ip, sp, lr, pc}
d00175b8:	f504d105 			; <UNDEFINED> instruction: 0xf504d105
d00175bc:	f8d32392 			; <UNDEFINED> instruction: 0xf8d32392
d00175c0:	454b3248 	strbmi	r3, [fp, #-584]	; 0xfffffdb8
d00175c4:	6da3d009 	stcvs	0, cr13, [r3, #36]!	; 0x24
d00175c8:	4b40b93b 	blmi	0xd1045abc
d00175cc:	f8c4447b 			; <UNDEFINED> instruction: 0xf8c4447b
d00175d0:	e9c48068 	stmib	r4, {r3, r5, r6, pc}^
d00175d4:	e9c43516 	stmib	r4, {r1, r2, r4, r8, sl, ip, sp}^
d00175d8:	b0076718 	andlt	r6, r7, r8, lsl r7
d00175dc:	8ff0e8bd 	svchi	0x00f0e8bd
d00175e0:	4651465a 			; <UNDEFINED> instruction: 0x4651465a
d00175e4:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d00175e8:	1e03f8e1 	cdpne	8, 0, cr15, cr3, cr1, {7}
d00175ec:	465ada53 			; <UNDEFINED> instruction: 0x465ada53
d00175f0:	46204651 			; <UNDEFINED> instruction: 0x46204651
d00175f4:	f7f99305 			; <UNDEFINED> instruction: 0xf7f99305
d00175f8:	1e02f8f9 	mcrne	8, 0, pc, cr2, cr9, {7}	; <UNPREDICTABLE>
d00175fc:	da059b05 	ble	0xd017e218
d0017600:	2b006da3 	blcs	0xd0032c94
d0017604:	4b32d1e9 	blmi	0xd0ccbdb0
d0017608:	e7e0447b 			; <UNDEFINED> instruction: 0xe7e0447b
d001760c:	fb01213c 	blx	0xd005fb06
d0017610:	f5014102 			; <UNDEFINED> instruction: 0xf5014102
d0017614:	f891315f 			; <UNDEFINED> instruction: 0xf891315f
d0017618:	f891b3ec 			; <UNDEFINED> instruction: 0xf891b3ec
d001761c:	f1bba3ee 			; <UNDEFINED> instruction: 0xf1bba3ee
d0017620:	d1460f0d 	cmple	r6, sp, lsl #30
d0017624:	21014620 	tstcs	r1, r0, lsr #12
d0017628:	faaaf7fd 	blx	0xcead5624
d001762c:	6108f244 	tstvs	r8, r4, asr #4	; <UNPREDICTABLE>
d0017630:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0017634:	e005fa3d 	and	pc, r5, sp, lsr sl	; <UNPREDICTABLE>
d0017638:	dbf32b00 	blle	0xcfce2240
d001763c:	46204619 			; <UNDEFINED> instruction: 0x46204619
d0017640:	f90ef7fe 			; <UNDEFINED> instruction: 0xf90ef7fe
d0017644:	0b10f1ab 	bleq	0xd0453cf8
d0017648:	0f01f1bb 	svceq	0x0001f1bb
d001764c:	6ae3d80e 	bvs	0xcf90d68c
d0017650:	d0052b5b 	andle	r2, r5, fp, asr fp
d0017654:	2b006da3 	blcs	0xd0032ce8
d0017658:	4b1ed1bf 	blmi	0xd07cbd5c
d001765c:	e7b6447b 			; <UNDEFINED> instruction: 0xe7b6447b
d0017660:	22002301 	andcs	r2, r0, #67108864	; 0x4000000
d0017664:	46204651 			; <UNDEFINED> instruction: 0x46204651
d0017668:	fea8f7ff 	mcr2	7, 5, pc, cr8, cr15, {7}	; <UNPREDICTABLE>
d001766c:	4620212e 	strtmi	r2, [r0], -lr, lsr #2
d0017670:	fc38f7fb 	ldc2	7, cr15, [r8], #-1004	; 0xfffffc14
d0017674:	464ab138 			; <UNDEFINED> instruction: 0x464ab138
d0017678:	46204651 			; <UNDEFINED> instruction: 0x46204651
d001767c:	e8bdb007 	pop	{r0, r1, r2, ip, sp, pc}
d0017680:	f7fe4ff0 			; <UNDEFINED> instruction: 0xf7fe4ff0
d0017684:	45d1b9cd 	ldrbmi	fp, [r1, #2509]	; 0x9cd
d0017688:	6da3d0a7 	stcvs	0, cr13, [r3, #668]!	; 0x29c
d001768c:	d1a42b00 			; <UNDEFINED> instruction: 0xd1a42b00
d0017690:	447b4b11 	ldrbtmi	r4, [fp], #-2833	; 0xfffff4ef
d0017694:	2230e79b 	eorscs	lr, r0, #40632320	; 0x26c0000
d0017698:	4203fb02 	andmi	pc, r3, #2048	; 0x800
d001769c:	2290f502 	addscs	pc, r0, #8388608	; 0x800000
d00176a0:	b659f892 			; <UNDEFINED> instruction: 0xb659f892
d00176a4:	a65af892 			; <UNDEFINED> instruction: 0xa65af892
d00176a8:	0f0df1bb 	svceq	0x000df1bb
d00176ac:	f04fd0c6 			; <UNDEFINED> instruction: 0xf04fd0c6
d00176b0:	f1ab32ff 			; <UNDEFINED> instruction: 0xf1ab32ff
d00176b4:	2902010f 	stmdbcs	r2, {r0, r1, r2, r3, r8}
d00176b8:	6da3d9be 			; <UNDEFINED> instruction: 0x6da3d9be
d00176bc:	d18c2b00 	orrle	r2, ip, r0, lsl #22
d00176c0:	447b4b06 	ldrbtmi	r4, [fp], #-2822	; 0xfffff4fa
d00176c4:	bf00e783 	svclt	0x0000e783
d00176c8:	fffffeea 			; <UNDEFINED> instruction: 0xfffffeea
d00176cc:	fffffec7 			; <UNDEFINED> instruction: 0xfffffec7
d00176d0:	fffffec6 			; <UNDEFINED> instruction: 0xfffffec6
d00176d4:	fffffec2 			; <UNDEFINED> instruction: 0xfffffec2
d00176d8:	fffffeb7 			; <UNDEFINED> instruction: 0xfffffeb7
d00176dc:	fffffe2d 			; <UNDEFINED> instruction: 0xfffffe2d

Disassembly of section .text.call.isra.0:

d0017868 <.text.call.isra.0>:
d0017868:	4ff0e92d 	svcmi	0x00f0e92d
d001786c:	460eb087 	strmi	fp, [lr], -r7, lsl #1
d0017870:	f8df4617 			; <UNDEFINED> instruction: 0xf8df4617
d0017874:	9302248c 	movwls	r2, #9356	; 0x248c
d0017878:	f89d4604 			; <UNDEFINED> instruction: 0xf89d4604
d001787c:	447a3044 	ldrbtmi	r3, [sl], #-68	; 0xffffffbc
d0017880:	46304639 			; <UNDEFINED> instruction: 0x46304639
d0017884:	f7f99303 			; <UNDEFINED> instruction: 0xf7f99303
d0017888:	b1b8f843 			; <UNDEFINED> instruction: 0xb1b8f843
d001788c:	2474f8df 	ldrbtcs	pc, [r4], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d0017890:	46304639 			; <UNDEFINED> instruction: 0x46304639
d0017894:	f7f9447a 			; <UNDEFINED> instruction: 0xf7f9447a
d0017898:	2800f83b 	stmdacs	r0, {r0, r1, r3, r4, r5, fp, ip, sp, lr, pc}
d001789c:	f8dfd13f 			; <UNDEFINED> instruction: 0xf8dfd13f
d00178a0:	46392468 	ldrtmi	r2, [r9], -r8, ror #8
d00178a4:	447a4630 	ldrbtmi	r4, [sl], #-1584	; 0xfffff9d0
d00178a8:	f832f7f9 			; <UNDEFINED> instruction: 0xf832f7f9
d00178ac:	bbb04605 	bllt	0xcec290c8
d00178b0:	21012202 	tstcs	r1, r2, lsl #4
d00178b4:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d00178b8:	e036fc8d 	eors	pc, r6, sp, lsl #25
d00178bc:	244cf8df 	strbcs	pc, [ip], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d00178c0:	46304639 			; <UNDEFINED> instruction: 0x46304639
d00178c4:	f7f9447a 			; <UNDEFINED> instruction: 0xf7f9447a
d00178c8:	2800f823 	stmdacs	r0, {r0, r1, r5, fp, ip, sp, lr, pc}
d00178cc:	f8dfd1de 			; <UNDEFINED> instruction: 0xf8dfd1de
d00178d0:	46392440 	ldrtmi	r2, [r9], -r0, asr #8
d00178d4:	447a4630 	ldrbtmi	r4, [sl], #-1584	; 0xfffff9d0
d00178d8:	f81af7f9 			; <UNDEFINED> instruction: 0xf81af7f9
d00178dc:	d1d52800 	bicsle	r2, r5, r0, lsl #16
d00178e0:	2430f8df 	ldrtcs	pc, [r0], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d00178e4:	46304639 			; <UNDEFINED> instruction: 0x46304639
d00178e8:	f7f9447a 			; <UNDEFINED> instruction: 0xf7f9447a
d00178ec:	4605f811 			; <UNDEFINED> instruction: 0x4605f811
d00178f0:	d1cb2800 	bicle	r2, fp, r0, lsl #16
d00178f4:	4631463a 			; <UNDEFINED> instruction: 0x4631463a
d00178f8:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d00178fc:	4680f81e 	pkhbtmi	pc, r0, lr, lsl #16	; <UNPREDICTABLE>
d0017900:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d0017904:	46018089 	strmi	r8, [r1], -r9, lsl #1
d0017908:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d001790c:	f898f9d9 			; <UNDEFINED> instruction: 0xf898f9d9
d0017910:	2d075047 	stccs	0, cr5, [r7, #-284]	; 0xfffffee4
d0017914:	1f6bd010 	svcne	0x006bd010
d0017918:	415d425d 	cmpmi	sp, sp, asr r2
d001791c:	2201e00d 	andcs	lr, r1, #13
d0017920:	46202501 	strtmi	r2, [r0], -r1, lsl #10
d0017924:	f7fe4611 			; <UNDEFINED> instruction: 0xf7fe4611
d0017928:	4afbfc55 	bmi	0xcff16a84
d001792c:	46202129 	strtmi	r2, [r0], -r9, lsr #2
d0017930:	f7fb447a 			; <UNDEFINED> instruction: 0xf7fb447a
d0017934:	b920fae5 	stmdblt	r0!, {r0, r2, r5, r6, r7, r9, fp, ip, sp, lr, pc}
d0017938:	46282502 	strtmi	r2, [r8], -r2, lsl #10
d001793c:	e8bdb007 	pop	{r0, r1, r2, ip, sp, pc}
d0017940:	f5048ff0 			; <UNDEFINED> instruction: 0xf5048ff0
d0017944:	f8992996 			; <UNDEFINED> instruction: 0xf8992996
d0017948:	b1b112a2 			; <UNDEFINED> instruction: 0xb1b112a2
d001794c:	82a0f8b9 	adchi	pc, r0, #12124160	; 0xb90000
d0017950:	2b006da3 	blcs	0xd0032fe4
d0017954:	4642d1f0 			; <UNDEFINED> instruction: 0x4642d1f0
d0017958:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d001795c:	f910f7fd 			; <UNDEFINED> instruction: 0xf910f7fd
d0017960:	238ef504 	orrcs	pc, lr, #4, 10	; 0x1000000
d0017964:	662cf8d3 			; <UNDEFINED> instruction: 0x662cf8d3
d0017968:	6f00f5b6 	svcvs	0x0000f5b6
d001796c:	49ebd141 	stmibmi	fp!, {r0, r6, r8, ip, lr, pc}^
d0017970:	46204479 			; <UNDEFINED> instruction: 0x46204479
d0017974:	fc6af7f8 	stc2l	7, cr15, [sl], #-992	; 0xfffffc20
d0017978:	f504e7de 			; <UNDEFINED> instruction: 0xf504e7de
d001797c:	f8d33367 			; <UNDEFINED> instruction: 0xf8d33367
d0017980:	f1b881c4 			; <UNDEFINED> instruction: 0xf1b881c4
d0017984:	d8060f7f 	stmdale	r6, {r0, r1, r2, r3, r4, r5, r6, r8, r9, sl, fp}
d0017988:	3a7ff504 	bcc	0xd2014da0
d001798c:	621cf8da 	andsvs	pc, ip, #14286848	; 0xda0000
d0017990:	2f78f5b6 	svccs	0x0078f5b6
d0017994:	49e2d907 	stmibmi	r2!, {r0, r1, r2, r8, fp, ip, lr, pc}^
d0017998:	f04f4620 			; <UNDEFINED> instruction: 0xf04f4620
d001799c:	44790800 	ldrbtmi	r0, [r9], #-2048	; 0xfffff800
d00179a0:	fc54f7f8 	mrrc2	7, 15, pc, r4, cr8	; <UNPREDICTABLE>
d00179a4:	f108e7d4 			; <UNDEFINED> instruction: 0xf108e7d4
d00179a8:	36070201 	strcc	r0, [r7], -r1, lsl #4
d00179ac:	21c4f8c3 	biccs	pc, r4, r3, asr #17
d00179b0:	f894223c 			; <UNDEFINED> instruction: 0xf894223c
d00179b4:	f026b008 			; <UNDEFINED> instruction: 0xf026b008
d00179b8:	fb020607 	blx	0xd00991de
d00179bc:	f5074708 			; <UNDEFINED> instruction: 0xf5074708
d00179c0:	f507375f 			; <UNDEFINED> instruction: 0xf507375f
d00179c4:	f0097071 			; <UNDEFINED> instruction: 0xf0097071
d00179c8:	2307fa99 	movwcs	pc, #31385	; 0x7a99	; <UNPREDICTABLE>
d00179cc:	63e8f8c7 	mvnvs	pc, #13041664	; 0xc70000
d00179d0:	33ecf887 	mvncc	pc, #8847360	; 0x870000
d00179d4:	4300f44f 	movwmi	pc, #1103	; 0x44f	; <UNPREDICTABLE>
d00179d8:	b3edf887 	mvnlt	pc, #8847360	; 0x870000
d00179dc:	33fcf8c7 	mvnscc	pc, #13041664	; 0xc70000
d00179e0:	2301441e 	movwcs	r4, #5150	; 0x141e
d00179e4:	621cf8ca 	andsvs	pc, ip, #13238272	; 0xca0000
d00179e8:	82a0f8a9 	adchi	pc, r0, #11075584	; 0xa90000
d00179ec:	32a2f889 	adccc	pc, r2, #8978432	; 0x890000
d00179f0:	1c72e7ae 	ldclne	7, cr14, [r2], #-696	; 0xfffffd48
d00179f4:	eb044620 	bl	0xd012927c
d00179f8:	f8c304c6 			; <UNDEFINED> instruction: 0xf8c304c6
d00179fc:	f7fd262c 			; <UNDEFINED> instruction: 0xf7fd262c
d0017a00:	f505f8fd 			; <UNDEFINED> instruction: 0xf505f8fd
d0017a04:	f504437f 			; <UNDEFINED> instruction: 0xf504437f
d0017a08:	35022486 	strcc	r2, [r2, #-1158]	; 0xfffffb7a
d0017a0c:	f8c433fd 			; <UNDEFINED> instruction: 0xf8c433fd
d0017a10:	f8a4062c 			; <UNDEFINED> instruction: 0xf8a4062c
d0017a14:	e7903630 			; <UNDEFINED> instruction: 0xe7903630
d0017a18:	4631463a 			; <UNDEFINED> instruction: 0x4631463a
d0017a1c:	f7f84620 			; <UNDEFINED> instruction: 0xf7f84620
d0017a20:	1e03ff4e 	cdpne	15, 0, cr15, cr3, cr14, {2}
d0017a24:	da0e9301 	ble	0xd03bc630
d0017a28:	2b006da3 	blcs	0xd00330bc
d0017a2c:	4bbdd185 	blmi	0xcef8c048
d0017a30:	65a3447b 	strvs	r4, [r3, #1147]!	; 0x47b
d0017a34:	65e39b02 	strbvs	r9, [r3, #2818]!	; 0xb02
d0017a38:	66239b10 			; <UNDEFINED> instruction: 0x66239b10
d0017a3c:	66639b03 	strbtvs	r9, [r3], -r3, lsl #22
d0017a40:	66a39b12 	ssatvs	r9, #4, r2, lsl #22
d0017a44:	463ae779 			; <UNDEFINED> instruction: 0x463ae779
d0017a48:	46204631 			; <UNDEFINED> instruction: 0x46204631
d0017a4c:	feaef7f8 	mcr2	7, 5, pc, cr14, cr8, {7}	; <UNPREDICTABLE>
d0017a50:	dae92800 	ble	0xcfa61a58
d0017a54:	4631463a 			; <UNDEFINED> instruction: 0x4631463a
d0017a58:	f7f84620 			; <UNDEFINED> instruction: 0xf7f84620
d0017a5c:	2800fec7 	stmdacs	r0, {r0, r1, r2, r6, r7, r9, sl, fp, ip, sp, lr, pc}
d0017a60:	2338dae2 	teqcs	r8, #925696	; 0xe2000
d0017a64:	fb039a01 	blx	0xd00fe272
d0017a68:	f5024202 			; <UNDEFINED> instruction: 0xf5024202
d0017a6c:	f892327f 			; <UNDEFINED> instruction: 0xf892327f
d0017a70:	29041254 	stmdbcs	r4, {r2, r4, r6, r9, ip}
d0017a74:	6da3d106 	stfvsd	f5, [r3, #24]!
d0017a78:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0017a7c:	4baaaf5e 	blmi	0xceac37fc
d0017a80:	e7d6447b 			; <UNDEFINED> instruction: 0xe7d6447b
d0017a84:	224ff892 	subcs	pc, pc, #9568256	; 0x920000
d0017a88:	d1782a04 	cmnle	r8, r4, lsl #20
d0017a8c:	fb039a01 	blx	0xd00fe29a
d0017a90:	f44f4302 	vst2.8	{d20-d23}, [pc], r2
d0017a94:	f503721a 			; <UNDEFINED> instruction: 0xf503721a
d0017a98:	f893337f 			; <UNDEFINED> instruction: 0xf893337f
d0017a9c:	fb023252 	blx	0xd00a43ee
d0017aa0:	f5034303 			; <UNDEFINED> instruction: 0xf5034303
d0017aa4:	f8b33368 			; <UNDEFINED> instruction: 0xf8b33368
d0017aa8:	f1baa028 			; <UNDEFINED> instruction: 0xf1baa028
d0017aac:	d0070f00 	andle	r0, r7, r0, lsl #30
d0017ab0:	2692f504 	ldrcs	pc, [r2], r4, lsl #10
d0017ab4:	9238f8d6 	eorsls	pc, r8, #14024704	; 0xd60000
d0017ab8:	0340f1c9 	movteq	pc, #457	; 0x1c9	; <UNPREDICTABLE>
d0017abc:	d939459a 	ldmdble	r9!, {r1, r3, r4, r7, r8, sl, lr}
d0017ac0:	f04f499a 			; <UNDEFINED> instruction: 0xf04f499a
d0017ac4:	46200900 	strtmi	r0, [r0], -r0, lsl #18
d0017ac8:	f7f84479 			; <UNDEFINED> instruction: 0xf7f84479
d0017acc:	6da3fbbf 			; <UNDEFINED> instruction: 0x6da3fbbf
d0017ad0:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0017ad4:	4649af31 			; <UNDEFINED> instruction: 0x4649af31
d0017ad8:	f04f4620 			; <UNDEFINED> instruction: 0xf04f4620
d0017adc:	f7fd0801 			; <UNDEFINED> instruction: 0xf7fd0801
d0017ae0:	f24bfebf 			; <UNDEFINED> instruction: 0xf24bfebf
d0017ae4:	46204103 	strtmi	r4, [r0], -r3, lsl #2
d0017ae8:	ffe2f7fc 			; <UNDEFINED> instruction: 0xffe2f7fc
d0017aec:	26389b01 	ldrtcs	r9, [r8], -r1, lsl #22
d0017af0:	eb04435e 	bl	0xd0128870
d0017af4:	f50a0a06 			; <UNDEFINED> instruction: 0xf50a0a06
d0017af8:	f89a3a7f 			; <UNDEFINED> instruction: 0xf89a3a7f
d0017afc:	2b04324d 	blcs	0xd0124438
d0017b00:	f506d041 			; <UNDEFINED> instruction: 0xf506d041
d0017b04:	f8cd367f 			; <UNDEFINED> instruction: 0xf8cd367f
d0017b08:	f8dfa010 			; <UNDEFINED> instruction: 0xf8dfa010
d0017b0c:	2700a224 	strcs	sl, [r0, -r4, lsr #4]
d0017b10:	2653f206 	ldrbcs	pc, [r3], -r6, lsl #4	; <UNPREDICTABLE>
d0017b14:	442644fa 	strtmi	r4, [r6], #-1274	; 0xfffffb06
d0017b18:	f8939b04 			; <UNDEFINED> instruction: 0xf8939b04
d0017b1c:	428f124c 	addmi	r1, pc, #76, 4	; 0xc0000004
d0017b20:	6da3d202 	sfmvs	f5, 1, [r3, #8]!
d0017b24:	d0492b00 	suble	r2, r9, r0, lsl #22
d0017b28:	46204441 	strtmi	r4, [r0], -r1, asr #8
d0017b2c:	f8a5f7fd 			; <UNDEFINED> instruction: 0xf8a5f7fd
d0017b30:	e02c4606 	eor	r4, ip, r6, lsl #12
d0017b34:	f8d62300 			; <UNDEFINED> instruction: 0xf8d62300
d0017b38:	21007238 	tstcs	r0, r8, lsr r2
d0017b3c:	23309304 	teqcs	r0, #4, 6	; 0x10000000
d0017b40:	0801f107 	stmdaeq	r1, {r0, r1, r2, r8, ip, sp, lr, pc}
d0017b44:	b240f896 	sublt	pc, r0, #9830400	; 0x960000
d0017b48:	4707fb03 	strmi	pc, [r7, -r3, lsl #22]
d0017b4c:	f8c6461a 			; <UNDEFINED> instruction: 0xf8c6461a
d0017b50:	f5078238 			; <UNDEFINED> instruction: 0xf5078238
d0017b54:	f5072790 			; <UNDEFINED> instruction: 0xf5072790
d0017b58:	f00960c7 			; <UNDEFINED> instruction: 0xf00960c7
d0017b5c:	9b04f9cf 	blls	0xd01562a0
d0017b60:	f887220b 			; <UNDEFINED> instruction: 0xf887220b
d0017b64:	3301b658 	movwcc	fp, #5720	; 0x1658
d0017b68:	2659f887 	ldrbcs	pc, [r9], -r7, lsl #17	; <UNPREDICTABLE>
d0017b6c:	d8e2459a 	stmiale	r2!, {r1, r3, r4, r7, r8, sl, lr}^
d0017b70:	323cf8d6 	eorscc	pc, ip, #14024704	; 0xd60000
d0017b74:	bf884598 	svclt	0x00884598
d0017b78:	823cf8c6 	eorshi	pc, ip, #12976128	; 0xc60000
d0017b7c:	f04fe7a7 			; <UNDEFINED> instruction: 0xf04fe7a7
d0017b80:	46c10800 	strbmi	r0, [r1], r0, lsl #16
d0017b84:	2600e7b2 			; <UNDEFINED> instruction: 0x2600e7b2
d0017b88:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0017b8c:	4a69fa71 	bmi	0xd1a96558
d0017b90:	46202129 	strtmi	r2, [r0], -r9, lsr #2
d0017b94:	f7fb447a 			; <UNDEFINED> instruction: 0xf7fb447a
d0017b98:	2800f9b3 	stmdacs	r0, {r0, r1, r4, r5, r7, r8, fp, ip, sp, lr, pc}
d0017b9c:	aecdf43f 	mcrge	4, 6, pc, cr13, cr15, {1}	; <UNPREDICTABLE>
d0017ba0:	238ef504 	orrcs	pc, lr, #4, 10	; 0x1000000
d0017ba4:	762cf8d3 			; <UNDEFINED> instruction: 0x762cf8d3
d0017ba8:	6f00f5b7 	svcvs	0x0000f5b7
d0017bac:	6da3d16a 	stfvsd	f5, [r3, #424]!	; 0x1a8
d0017bb0:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0017bb4:	4b60aec2 	blmi	0xd18436c4
d0017bb8:	e73a447b 			; <UNDEFINED> instruction: 0xe73a447b
d0017bbc:	4652b127 	ldrbmi	fp, [r2], -r7, lsr #2
d0017bc0:	4620212c 	strtmi	r2, [r0], -ip, lsr #2
d0017bc4:	f99cf7fb 			; <UNDEFINED> instruction: 0xf99cf7fb
d0017bc8:	bb01f816 	bllt	0xd0095c28
d0017bcc:	0f0df1bb 	svceq	0x000df1bb
d0017bd0:	7931d10a 	ldmdbvc	r1!, {r1, r3, r8, ip, lr, pc}
d0017bd4:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0017bd8:	f24bfccd 	sha1c.32	<illegal reg q15.5>, <illegal reg q13.5>, <illegal reg q6.5>
d0017bdc:	46204103 	strtmi	r4, [r0], -r3, lsl #2
d0017be0:	f7fc3701 			; <UNDEFINED> instruction: 0xf7fc3701
d0017be4:	e797ff65 	ldr	pc, [r7, r5, ror #30]
d0017be8:	0f0ef1bb 	svceq	0x000ef1bb
d0017bec:	7931d104 	ldmdbvc	r1!, {r2, r8, ip, lr, pc}
d0017bf0:	f0004620 			; <UNDEFINED> instruction: 0xf0004620
d0017bf4:	e7f0f915 			; <UNDEFINED> instruction: 0xe7f0f915
d0017bf8:	0f12f1bb 	svceq	0x0012f1bb
d0017bfc:	7931d104 	ldmdbvc	r1!, {r2, r8, ip, lr, pc}
d0017c00:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0017c04:	e7e8f913 			; <UNDEFINED> instruction: 0xe7e8f913
d0017c08:	0f13f1bb 	svceq	0x0013f1bb
d0017c0c:	4620d103 	strtmi	sp, [r0], -r3, lsl #2
d0017c10:	fe6cf7fd 	mcr2	7, 3, pc, cr12, cr13, {7}	; <UNPREDICTABLE>
d0017c14:	f1bbe7e1 			; <UNDEFINED> instruction: 0xf1bbe7e1
d0017c18:	d1050f0a 	tstle	r5, sl, lsl #30
d0017c1c:	21012204 	tstcs	r1, r4, lsl #4
d0017c20:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0017c24:	e7d8fad7 			; <UNDEFINED> instruction: 0xe7d8fad7
d0017c28:	03fbf00b 	mvnseq	pc, #11
d0017c2c:	d1262b02 			; <UNDEFINED> instruction: 0xd1262b02
d0017c30:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0017c34:	2800fb41 	stmdacs	r0, {r0, r6, r8, r9, fp, ip, sp, lr, pc}
d0017c38:	6ae2d1cf 	bvs	0xcf8cc37c
d0017c3c:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d0017c40:	d002429a 	mulle	r2, sl, r2
d0017c44:	4479493d 	ldrbtmi	r4, [r9], #-2365	; 0xfffff6c3
d0017c48:	69a1e693 	stmibvs	r1!, {r0, r1, r4, r7, r9, sl, sp, lr, pc}
d0017c4c:	69e24620 	stmibvs	r2!, {r5, r9, sl, lr}^
d0017c50:	fdacf7f8 	stc2	7, cr15, [ip, #992]!	; 0x3e0
d0017c54:	dbf51e01 	blle	0xcfd5f460
d0017c58:	91052330 	tstls	r5, r0, lsr r3
d0017c5c:	4301fb03 	movwmi	pc, #6915	; 0x1b03	; <UNPREDICTABLE>
d0017c60:	2390f503 	orrscs	pc, r0, #12582912	; 0xc00000
d0017c64:	3659f893 			; <UNDEFINED> instruction: 0x3659f893
d0017c68:	d1eb455b 	mvnle	r4, fp, asr r5
d0017c6c:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0017c70:	2200f919 	andcs	pc, r0, #409600	; 0x64000
d0017c74:	46209905 	strtmi	r9, [r0], -r5, lsl #18
d0017c78:	ff38f7fc 			; <UNDEFINED> instruction: 0xff38f7fc
d0017c7c:	2201e7ad 	andcs	lr, r1, #45350912	; 0x2b40000
d0017c80:	e7cd4611 	bfi	r4, r1, #12, #2
d0017c84:	eb041c7a 	bl	0xd011ee74
d0017c88:	462007c7 	strtmi	r0, [r0], -r7, asr #15
d0017c8c:	262cf8c3 	strtcs	pc, [ip], -r3, asr #17
d0017c90:	2786f507 	strcs	pc, [r6, r7, lsl #10]
d0017c94:	ffb2f7fc 			; <UNDEFINED> instruction: 0xffb2f7fc
d0017c98:	f8c79b01 			; <UNDEFINED> instruction: 0xf8c79b01
d0017c9c:	f8a7062c 			; <UNDEFINED> instruction: 0xf8a7062c
d0017ca0:	b12e3630 			; <UNDEFINED> instruction: 0xb12e3630
d0017ca4:	4130f446 	teqmi	r0, r6, asr #8	; <UNPREDICTABLE>
d0017ca8:	b2894620 	addlt	r4, r9, #32, 12	; 0x2000000
d0017cac:	ff00f7fc 			; <UNDEFINED> instruction: 0xff00f7fc
d0017cb0:	26389b01 	ldrtcs	r9, [r8], -r1, lsl #22
d0017cb4:	4603fb06 	strmi	pc, [r3], -r6, lsl #22
d0017cb8:	367ff506 	ldrbtcc	pc, [pc], -r6, lsl #10	; <UNPREDICTABLE>
d0017cbc:	324ff896 	subcc	pc, pc, #9830400	; 0x960000
d0017cc0:	d10b2b04 	tstle	fp, r4, lsl #22
d0017cc4:	46494620 	strbmi	r4, [r9], -r0, lsr #12
d0017cc8:	fdcaf7fd 	stc2l	7, cr15, [sl, #1012]	; 0x3f4
d0017ccc:	2492f504 	ldrcs	pc, [r2], #1284	; 0x504
d0017cd0:	3252f896 	subscc	pc, r2, #9830400	; 0x960000
d0017cd4:	f8c42506 			; <UNDEFINED> instruction: 0xf8c42506
d0017cd8:	e62e3248 	strt	r3, [lr], -r8, asr #4
d0017cdc:	d1072b05 	tstle	r7, r5, lsl #22
d0017ce0:	2492f504 	ldrcs	pc, [r2], #1284	; 0x504
d0017ce4:	3252f896 	subscc	pc, r2, #9830400	; 0x960000
d0017ce8:	f8c42503 			; <UNDEFINED> instruction: 0xf8c42503
d0017cec:	e6243248 	strt	r3, [r4], -r8, asr #4
d0017cf0:	f43f2b01 			; <UNDEFINED> instruction: 0xf43f2b01
d0017cf4:	2b03ae21 	blcs	0xd0103580
d0017cf8:	2504bf08 	strcs	fp, [r4, #-3848]	; 0xfffff0f8
d0017cfc:	bf00e61d 	svclt	0x0000e61d
d0017d00:	fffffe5e 			; <UNDEFINED> instruction: 0xfffffe5e
d0017d04:	fffffe48 			; <UNDEFINED> instruction: 0xfffffe48
d0017d08:	fffffe42 			; <UNDEFINED> instruction: 0xfffffe42
d0017d0c:	fffffe1f 			; <UNDEFINED> instruction: 0xfffffe1f
d0017d10:	fffffe12 			; <UNDEFINED> instruction: 0xfffffe12
d0017d14:	fffffe0e 			; <UNDEFINED> instruction: 0xfffffe0e
d0017d18:	fffffdd2 			; <UNDEFINED> instruction: 0xfffffdd2
d0017d1c:	fffffde0 			; <UNDEFINED> instruction: 0xfffffde0
d0017d20:	fffffd86 			; <UNDEFINED> instruction: 0xfffffd86
d0017d24:	fffffd38 			; <UNDEFINED> instruction: 0xfffffd38
d0017d28:	fffffd12 			; <UNDEFINED> instruction: 0xfffffd12
d0017d2c:	fffffcf6 			; <UNDEFINED> instruction: 0xfffffcf6
d0017d30:	fffffcdc 			; <UNDEFINED> instruction: 0xfffffcdc
d0017d34:	fffffca9 			; <UNDEFINED> instruction: 0xfffffca9
d0017d38:	fffffb98 			; <UNDEFINED> instruction: 0xfffffb98
d0017d3c:	fffffbc9 			; <UNDEFINED> instruction: 0xfffffbc9

Disassembly of section .text.struct_pointer_value:

d0017e20 <.text.struct_pointer_value>:
d0017e20:	f2406ac2 	vpmax.s8	q11, q8, q1
d0017e24:	429a1301 	addsmi	r1, sl, #67108864	; 0x4000000
d0017e28:	4ff0e92d 	svcmi	0x00f0e92d
d0017e2c:	460f4604 	strmi	r4, [pc], -r4, lsl #12
d0017e30:	8b02ed2d 	blhi	0xd00d32ec
d0017e34:	d14cb087 	smlalbble	fp, ip, r7, r0
d0017e38:	2d286cc5 	stccs	12, cr6, [r8, #-788]!	; 0xfffffcec
d0017e3c:	6b43d149 	blvs	0xd110c368
d0017e40:	b024f8d0 	ldrdlt	pc, [r4], -r0	; <UNPREDICTABLE>
d0017e44:	a028f8d0 	ldrdge	pc, [r8], -r0	; <UNPREDICTABLE>
d0017e48:	9030f890 	mlasls	r0, r0, r8, pc	; <UNPREDICTABLE>
d0017e4c:	e9d09304 	ldmib	r0, {r2, r8, r9, ip, pc}^
d0017e50:	f7fb6806 			; <UNDEFINED> instruction: 0xf7fb6806
d0017e54:	4af1f827 	bmi	0xcfc95ef8
d0017e58:	46204629 	strtmi	r4, [r0], -r9, lsr #12
d0017e5c:	f7fb447a 			; <UNDEFINED> instruction: 0xf7fb447a
d0017e60:	b1a8f84f 			; <UNDEFINED> instruction: 0xb1a8f84f
d0017e64:	46429b04 	strbmi	r9, [r2], -r4, lsl #22
d0017e68:	46204631 			; <UNDEFINED> instruction: 0x46204631
d0017e6c:	465b9302 	ldrbmi	r9, [fp], -r2, lsl #6
d0017e70:	9004f8cd 	andls	pc, r4, sp, asr #17
d0017e74:	a000f8cd 	andge	pc, r0, sp, asr #17
d0017e78:	fcf6f7ff 	ldc2l	7, cr15, [r6], #1020	; 0x3fc
d0017e7c:	46054ae8 	strmi	r4, [r5], -r8, ror #21
d0017e80:	447a4641 	ldrbtmi	r4, [sl], #-1601	; 0xfffff9bf
d0017e84:	f7f84630 			; <UNDEFINED> instruction: 0xf7f84630
d0017e88:	b130fd43 	teqlt	r0, r3, asr #26	; <UNPREDICTABLE>
d0017e8c:	d1142d03 	tstle	r4, r3, lsl #26
d0017e90:	ecbdb007 	ldc	0, cr11, [sp], #28
d0017e94:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d0017e98:	4ae28ff0 	bmi	0xcf8bbe60
d0017e9c:	46304641 	ldrtmi	r4, [r0], -r1, asr #12
d0017ea0:	f7f8447a 			; <UNDEFINED> instruction: 0xf7f8447a
d0017ea4:	2800fd35 	stmdacs	r0, {r0, r2, r4, r5, r8, sl, fp, ip, sp, lr, pc}
d0017ea8:	2d03d1f0 	stfcsd	f5, [r3, #-960]	; 0xfffffc40
d0017eac:	f504d105 			; <UNDEFINED> instruction: 0xf504d105
d0017eb0:	f8d32392 			; <UNDEFINED> instruction: 0xf8d32392
d0017eb4:	42bb3248 	adcsmi	r3, fp, #72, 4	; 0x80000004
d0017eb8:	6da3e7e9 	stcvs	7, cr14, [r3, #932]!	; 0x3a4
d0017ebc:	d1e72b00 	mvnle	r2, r0, lsl #22
d0017ec0:	447b4bd9 	ldrbtmi	r4, [fp], #-3033	; 0xfffff427
d0017ec4:	3b16e9c4 	blcc	0xd05d25dc
d0017ec8:	e9c49b04 	stmib	r4, {r2, r8, r9, fp, ip, pc}^
d0017ecc:	66a3a918 	ssatvs	sl, #4, r8, lsl #18
d0017ed0:	212ae7de 	ldrdcs	lr, [sl, -lr]!	; <UNPREDICTABLE>
d0017ed4:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0017ed8:	2800f805 	stmdacs	r0, {r0, r2, fp, ip, sp, lr, pc}
d0017edc:	6ae2d03d 	bvs	0xcf8cbfd8
d0017ee0:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d0017ee4:	9024f8d4 	ldrdls	pc, [r4], -r4	; <UNPREDICTABLE>
d0017ee8:	f8d4429a 			; <UNDEFINED> instruction: 0xf8d4429a
d0017eec:	f8948028 			; <UNDEFINED> instruction: 0xf8948028
d0017ef0:	6b656030 	blvs	0xd196ffb8
d0017ef4:	6da3d00a 	stcvs	0, cr13, [r3, #40]!	; 0x28
d0017ef8:	d1c92b00 	bicle	r2, r9, r0, lsl #22
d0017efc:	66a54bcb 	strtvs	r4, [r5], fp, asr #23
d0017f00:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0017f04:	e9c48618 	stmib	r4, {r3, r4, r9, sl, pc}^
d0017f08:	e7c13916 	bfi	r3, r6, (invalid: 18:1)
d0017f0c:	1206e9d4 	andne	lr, r6, #212, 18	; 0x350000
d0017f10:	f7f84620 			; <UNDEFINED> instruction: 0xf7f84620
d0017f14:	f1b0fc4b 			; <UNDEFINED> instruction: 0xf1b0fc4b
d0017f18:	dbec0a00 	blle	0xcfb1a720
d0017f1c:	fb032330 	blx	0xd00e0be6
d0017f20:	f503430a 			; <UNDEFINED> instruction: 0xf503430a
d0017f24:	f8932390 			; <UNDEFINED> instruction: 0xf8932390
d0017f28:	2a122659 	bcs	0xd04a1894
d0017f2c:	f893d1e3 			; <UNDEFINED> instruction: 0xf893d1e3
d0017f30:	42bb365a 	adcsmi	r3, fp, #94371840	; 0x5a00000
d0017f34:	4620d1df 			; <UNDEFINED> instruction: 0x4620d1df
d0017f38:	ffb4f7fa 			; <UNDEFINED> instruction: 0xffb4f7fa
d0017f3c:	46204651 			; <UNDEFINED> instruction: 0x46204651
d0017f40:	f7fc2200 			; <UNDEFINED> instruction: 0xf7fc2200
d0017f44:	f44ffdd3 			; <UNDEFINED> instruction: 0xf44ffdd3
d0017f48:	462041d0 			; <UNDEFINED> instruction: 0x462041d0
d0017f4c:	ecbdb007 	ldc	0, cr11, [sp], #28
d0017f50:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d0017f54:	f7fc4ff0 			; <UNDEFINED> instruction: 0xf7fc4ff0
d0017f58:	2126bdab 			; <UNDEFINED> instruction: 0x2126bdab
d0017f5c:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0017f60:	6ae3ffc1 	bvs	0xcf917e6c
d0017f64:	1201f240 	andne	pc, r1, #64, 4
d0017f68:	42934605 	addsmi	r4, r3, #5242880	; 0x500000
d0017f6c:	8143f040 	cmphi	r3, r0, asr #32	; <UNPREDICTABLE>
d0017f70:	462069a3 	strtmi	r6, [r0], -r3, lsr #19
d0017f74:	ee0869e6 	vmls.f16	s12, s17, s13
d0017f78:	6b633a10 	blvs	0xd18e67c0
d0017f7c:	f8d44632 			; <UNDEFINED> instruction: 0xf8d44632
d0017f80:	ee18b024 	cdp	0, 1, cr11, cr8, cr4, {1}
d0017f84:	f8d41a10 			; <UNDEFINED> instruction: 0xf8d41a10
d0017f88:	f894a028 			; <UNDEFINED> instruction: 0xf894a028
d0017f8c:	93049030 	movwls	r9, #16432	; 0x4030
d0017f90:	fc0cf7f8 	stc2	7, cr15, [ip], {248}	; 0xf8
d0017f94:	0800f1b0 	stmdaeq	r0, {r4, r5, r7, r8, ip, sp, lr, pc}
d0017f98:	4632da22 	ldrtmi	sp, [r2], -r2, lsr #20
d0017f9c:	1a10ee18 	bne	0xd0453804
d0017fa0:	f7f84620 			; <UNDEFINED> instruction: 0xf7f84620
d0017fa4:	4603fc23 	strmi	pc, [r3], -r3, lsr #24
d0017fa8:	4aa1b9ed 	bmi	0xce886764
d0017fac:	ee184631 	mrc	6, 0, r4, cr8, cr1, {1}
d0017fb0:	93050a10 	movwls	r0, #23056	; 0x5a10
d0017fb4:	f7f8447a 			; <UNDEFINED> instruction: 0xf7f8447a
d0017fb8:	9b05fcab 	blls	0xd019726c
d0017fbc:	f1b8b198 			; <UNDEFINED> instruction: 0xf1b8b198
d0017fc0:	da100f00 	ble	0xd041bbc8
d0017fc4:	da0e2b00 	ble	0xd03a2bcc
d0017fc8:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0017fcc:	2100ff6b 	tstcs	r0, fp, ror #30	; <UNPREDICTABLE>
d0017fd0:	b0074620 	andlt	r4, r7, r0, lsr #12
d0017fd4:	8b02ecbd 	blhi	0xd00d32d0
d0017fd8:	4ff0e8bd 	svcmi	0x00f0e8bd
d0017fdc:	b965f7fd 	stmdblt	r5!, {r0, r2, r3, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}^
d0017fe0:	33fff04f 	mvnscc	pc, #79	; 0x4f
d0017fe4:	4620e7e0 	strtmi	lr, [r0], -r0, ror #15
d0017fe8:	f7fa9305 			; <UNDEFINED> instruction: 0xf7fa9305
d0017fec:	f1b8ff5b 			; <UNDEFINED> instruction: 0xf1b8ff5b
d0017ff0:	9b050f00 	blls	0xd015bbf8
d0017ff4:	2130db22 	teqcs	r0, r2, lsr #22
d0017ff8:	4108fb01 	tstmi	r8, r1, lsl #22	; <UNPREDICTABLE>
d0017ffc:	2190f501 	orrscs	pc, r0, r1, lsl #10
d0018000:	2659f891 			; <UNDEFINED> instruction: 0x2659f891
d0018004:	665af891 			; <UNDEFINED> instruction: 0x665af891
d0018008:	01fdf002 	mvnseq	pc, r2
d001800c:	d124290d 			; <UNDEFINED> instruction: 0xd124290d
d0018010:	46204641 	strtmi	r4, [r0], -r1, asr #12
d0018014:	fc24f7fd 	stc2	7, cr15, [r4], #-1012	; 0xfffffc0c
d0018018:	4620212e 	strtmi	r2, [r0], -lr, lsr #2
d001801c:	ff62f7fa 			; <UNDEFINED> instruction: 0xff62f7fa
d0018020:	d0622800 	rsble	r2, r2, r0, lsl #16
d0018024:	d04a2d00 	suble	r2, sl, r0, lsl #26
d0018028:	4631463a 			; <UNDEFINED> instruction: 0x4631463a
d001802c:	b0074620 	andlt	r4, r7, r0, lsr #12
d0018030:	8b02ecbd 	blhi	0xd00d332c
d0018034:	4ff0e8bd 	svcmi	0x00f0e8bd
d0018038:	bcf2f7fd 	ldcllt	7, cr15, [r2], #1012	; 0x3f4
d001803c:	db5f2b00 	blle	0xd17e2c44
d0018040:	fb01213c 	blx	0xd006053a
d0018044:	f5014103 			; <UNDEFINED> instruction: 0xf5014103
d0018048:	f891315f 			; <UNDEFINED> instruction: 0xf891315f
d001804c:	f89123ec 			; <UNDEFINED> instruction: 0xf89123ec
d0018050:	f00263ee 			; <UNDEFINED> instruction: 0xf00263ee
d0018054:	290d01fd 	stmdbcs	sp, {r0, r2, r3, r4, r5, r6, r7, r8}
d0018058:	f1a2d026 			; <UNDEFINED> instruction: 0xf1a2d026
d001805c:	29010110 	stmdbcs	r1, {r4, r8}
d0018060:	808ef200 	addhi	pc, lr, r0, lsl #4
d0018064:	0f00f1b8 	svceq	0x0000f1b8
d0018068:	4641db4d 	strbmi	sp, [r1], -sp, asr #22
d001806c:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0018070:	6ae3fbf7 	bvs	0xcf917054
d0018074:	d1782b5b 	cmnle	r8, fp, asr fp
d0018078:	2d002301 	stccs	3, cr2, [r0, #-4]
d001807c:	4631d04e 	ldrtmi	sp, [r1], -lr, asr #32
d0018080:	46202200 	strtmi	r2, [r0], -r0, lsl #4
d0018084:	f99af7ff 			; <UNDEFINED> instruction: 0xf99af7ff
d0018088:	4620212e 	strtmi	r2, [r0], -lr, lsr #2
d001808c:	ff2af7fa 			; <UNDEFINED> instruction: 0xff2af7fa
d0018090:	d1c92800 	bicle	r2, r9, r0, lsl #16
d0018094:	f43f42b7 			; <UNDEFINED> instruction: 0xf43f42b7
d0018098:	6da3aefb 	stcvs	14, cr10, [r3, #1004]!	; 0x3ec
d001809c:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d00180a0:	4b64aef7 	blmi	0xd1943c84
d00180a4:	e70d447b 	smlsdx	sp, fp, r4, r4
d00180a8:	461a4620 	ldrmi	r4, [sl], -r0, lsr #12
d00180ac:	f7fc2101 			; <UNDEFINED> instruction: 0xf7fc2101
d00180b0:	f244fd67 	vadd.f32	<illegal reg q15.5>, q2, <illegal reg q11.5>
d00180b4:	46206108 	strtmi	r6, [r0], -r8, lsl #2
d00180b8:	fcfaf7fc 	ldc2l	7, cr15, [sl], #1008	; 0x3f0
d00180bc:	462be7ac 	strtmi	lr, [fp], -ip, lsr #15
d00180c0:	4631462a 	ldrtmi	r4, [r1], -sl, lsr #12
d00180c4:	f0004620 			; <UNDEFINED> instruction: 0xf0004620
d00180c8:	2803f965 	stmdacs	r3, {r0, r2, r5, r6, r8, fp, ip, sp, lr, pc}
d00180cc:	f504d106 			; <UNDEFINED> instruction: 0xf504d106
d00180d0:	f8d32392 			; <UNDEFINED> instruction: 0xf8d32392
d00180d4:	42bb3248 	adcsmi	r3, fp, #72, 4	; 0x80000004
d00180d8:	aedaf43f 	mrcge	4, 6, APSR_nzcv, cr10, cr15, {1}
d00180dc:	2b006da3 	blcs	0xd0033770
d00180e0:	aed6f47f 	mrcge	4, 6, APSR_nzcv, cr6, cr15, {3}
d00180e4:	447b4b54 	ldrbtmi	r4, [fp], #-2900	; 0xfffff4ac
d00180e8:	b115e6ec 	tstlt	r5, ip, ror #13
d00180ec:	f43f42b7 			; <UNDEFINED> instruction: 0xf43f42b7
d00180f0:	6da3aecf 	stcvs	14, cr10, [r3, #828]!	; 0x33c
d00180f4:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d00180f8:	4b50aecb 	blmi	0xd1443c2c
d00180fc:	e6e1447b 	uxtab	r4, r1, fp, ror #8
d0018100:	220b26ff 	andcs	r2, fp, #267386880	; 0xff00000
d0018104:	4620e7a9 	strtmi	lr, [r0], -r9, lsr #15
d0018108:	2101461a 	tstcs	r1, sl, lsl r6
d001810c:	fd38f7fc 	ldc2	7, cr15, [r8, #-1008]!	; 0xfffffc10
d0018110:	6108f244 	tstvs	r8, r4, asr #4	; <UNPREDICTABLE>
d0018114:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0018118:	e7aafccb 	str	pc, [sl, fp, asr #25]!
d001811c:	462a4631 			; <UNDEFINED> instruction: 0x462a4631
d0018120:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0018124:	212ef94b 	msrcs	CPSR_fsx, fp, asr #18
d0018128:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d001812c:	b1a8fedb 	ldrdlt	pc, [r8, fp]!
d0018130:	462a462b 	strtmi	r4, [sl], -fp, lsr #12
d0018134:	46204631 			; <UNDEFINED> instruction: 0x46204631
d0018138:	f92cf000 			; <UNDEFINED> instruction: 0xf92cf000
d001813c:	d1062803 	tstle	r6, r3, lsl #16
d0018140:	2392f504 	orrscs	pc, r2, #4, 10	; 0x1000000
d0018144:	3248f8d3 	subcc	pc, r8, #13828096	; 0xd30000
d0018148:	f43f42bb 			; <UNDEFINED> instruction: 0xf43f42bb
d001814c:	6da3aea1 	stcvs	14, cr10, [r3, #644]!	; 0x284
d0018150:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0018154:	4b3aae9d 	blmi	0xd0ec3bd0
d0018158:	e6b3447b 	sxtah	r4, r3, fp, ror #8
d001815c:	2b006da3 	blcs	0xd00337f0
d0018160:	ae96f47f 	mrcge	4, 4, APSR_nzcv, cr6, cr15, {3}
d0018164:	447b4b37 	ldrbtmi	r4, [fp], #-2871	; 0xfffff4c9
d0018168:	b915e6ac 	ldmdblt	r5, {r2, r3, r5, r7, r9, sl, sp, lr, pc}
d001816c:	f43f42b7 			; <UNDEFINED> instruction: 0xf43f42b7
d0018170:	6da3ae8f 	stcvs	14, cr10, [r3, #572]!	; 0x23c
d0018174:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0018178:	4b33ae8b 	blmi	0xd0d03bac
d001817c:	e6a1447b 	sxtab	r4, r1, fp, ror #8
d0018180:	d1312a0e 	teqle	r1, lr, lsl #20
d0018184:	0f00f1b8 	svceq	0x0000f1b8
d0018188:	4641db2e 	strbmi	sp, [r1], -lr, lsr #22
d001818c:	22004620 	andcs	r4, r0, #32, 12	; 0x2000000
d0018190:	fcacf7fc 	stc2	7, cr15, [ip], #1008	; 0x3f0
d0018194:	7191f44f 	orrsvc	pc, r1, pc, asr #8
d0018198:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d001819c:	b1c0fea3 	biclt	pc, r0, r3, lsr #29
d00181a0:	f47f2d00 			; <UNDEFINED> instruction: 0xf47f2d00
d00181a4:	462baf41 	strtmi	sl, [fp], -r1, asr #30
d00181a8:	4631462a 	ldrtmi	r4, [r1], -sl, lsr #12
d00181ac:	f0004620 			; <UNDEFINED> instruction: 0xf0004620
d00181b0:	2803f8f1 	stmdacs	r3, {r0, r4, r5, r6, r7, fp, ip, sp, lr, pc}
d00181b4:	f504d106 			; <UNDEFINED> instruction: 0xf504d106
d00181b8:	f8d32392 			; <UNDEFINED> instruction: 0xf8d32392
d00181bc:	42bb3248 	adcsmi	r3, fp, #72, 4	; 0x80000004
d00181c0:	ae66f43f 	mcrge	4, 3, pc, cr6, cr15, {1}	; <UNPREDICTABLE>
d00181c4:	2b006da3 	blcs	0xd0033858
d00181c8:	ae62f47f 	mcrge	4, 3, pc, cr2, cr15, {3}	; <UNPREDICTABLE>
d00181cc:	447b4b1f 	ldrbtmi	r4, [fp], #-2847	; 0xfffff4e1
d00181d0:	b915e678 	ldmdblt	r5, {r3, r4, r5, r6, r9, sl, sp, lr, pc}
d00181d4:	f43f42b7 			; <UNDEFINED> instruction: 0xf43f42b7
d00181d8:	6da3ae5b 	stcvs	14, cr10, [r3, #364]!	; 0x16c
d00181dc:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d00181e0:	4b1bae57 	blmi	0xd0703b44
d00181e4:	e66d447b 			; <UNDEFINED> instruction: 0xe66d447b
d00181e8:	2b006da3 	blcs	0xd003387c
d00181ec:	ae50f47f 	mrcge	4, 2, APSR_nzcv, cr0, cr15, {3}
d00181f0:	447b4b18 	ldrbtmi	r4, [fp], #-2840	; 0xfffff4e8
d00181f4:	b938e666 	ldmdblt	r8!, {r1, r2, r5, r6, r9, sl, sp, lr, pc}
d00181f8:	7381f5a3 	orrvc	pc, r1, #683671552	; 0x28c00000
d00181fc:	d8032b01 	stmdale	r3, {r0, r8, r9, fp, sp}
d0018200:	2b006a23 	blcs	0xd0032a94
d0018204:	aee0f43f 	mcrge	4, 7, pc, cr0, cr15, {1}	; <UNPREDICTABLE>
d0018208:	46204913 			; <UNDEFINED> instruction: 0x46204913
d001820c:	b0074479 	andlt	r4, r7, r9, ror r4
d0018210:	8b02ecbd 	blhi	0xd00d350c
d0018214:	4ff0e8bd 	svcmi	0x00f0e8bd
d0018218:	b818f7f8 	ldmdalt	r8, {r3, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}
d001821c:	fffffee0 			; <UNDEFINED> instruction: 0xfffffee0
d0018220:	fffff85a 			; <UNDEFINED> instruction: 0xfffff85a
d0018224:	fffff848 			; <UNDEFINED> instruction: 0xfffff848
d0018228:	fffffe9b 			; <UNDEFINED> instruction: 0xfffffe9b
d001822c:	fffffe8a 			; <UNDEFINED> instruction: 0xfffffe8a
d0018230:	ffffd2fa 			; <UNDEFINED> instruction: 0xffffd2fa
d0018234:	ffffd949 			; <UNDEFINED> instruction: 0xffffd949
d0018238:	ffffd907 			; <UNDEFINED> instruction: 0xffffd907
d001823c:	ffffd8f1 			; <UNDEFINED> instruction: 0xffffd8f1
d0018240:	ffffd895 			; <UNDEFINED> instruction: 0xffffd895
d0018244:	fffffc52 			; <UNDEFINED> instruction: 0xfffffc52
d0018248:	ffffd871 			; <UNDEFINED> instruction: 0xffffd871
d001824c:	ffffd81f 			; <UNDEFINED> instruction: 0xffffd81f
d0018250:	ffffd809 			; <UNDEFINED> instruction: 0xffffd809
d0018254:	ffffd7fb 			; <UNDEFINED> instruction: 0xffffd7fb
d0018258:	fffffbd6 			; <UNDEFINED> instruction: 0xfffffbd6

Disassembly of section .text.struct_member:

d0018394 <.text.struct_member>:
d0018394:	4ff0e92d 	svcmi	0x00f0e92d
d0018398:	4bc3461d 	blmi	0xcf0e9c14
d001839c:	447b4604 	ldrbtmi	r4, [fp], #-1540	; 0xfffff9fc
d00183a0:	8b02ed2d 	blhi	0xd00d385c
d00183a4:	3a90ee08 	bcc	0xce453bcc
d00183a8:	9103b087 	smlabbls	r3, r7, r0, fp
d00183ac:	69a39204 	stmibvs	r3!, {r2, r9, ip, pc}
d00183b0:	2a90ee18 	bcs	0xce453c18
d00183b4:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d00183b8:	ee084620 	cfmadd32	mvax1, mvfx4, mvfx8, mvfx0
d00183bc:	69e33a10 	stmibvs	r3!, {r4, r9, fp, ip, sp}^
d00183c0:	a024f8d4 	ldrdge	pc, [r4], -r4	; <UNPREDICTABLE>
d00183c4:	f8d49301 			; <UNDEFINED> instruction: 0xf8d49301
d00183c8:	f8949028 			; <UNDEFINED> instruction: 0xf8949028
d00183cc:	6b678030 	blvs	0xd19f8494
d00183d0:	fd96f7fa 	ldc2	7, cr15, [r6, #1000]	; 0x3e8
d00183d4:	b9089b01 	stmdblt	r8, {r0, r8, r9, fp, ip, pc}
d00183d8:	e02e2500 	eor	r2, lr, r0, lsl #10
d00183dc:	f44f9a03 	vst1.8	{d25-d26}, [pc], r3
d00183e0:	fb01711a 	blx	0xd0074852
d00183e4:	f50bfb02 			; <UNDEFINED> instruction: 0xf50bfb02
d00183e8:	44a33267 	strtmi	r3, [r3], #615	; 0x267
d00183ec:	72f4f502 	rscsvc	pc, r4, #8388608	; 0x800000
d00183f0:	3b68f50b 	blcc	0xd1a55824
d00183f4:	18a29202 	stmiane	r2!, {r1, r9, ip, pc}
d00183f8:	22004616 	andcs	r4, r0, #23068672	; 0x1600000
d00183fc:	f89b9201 			; <UNDEFINED> instruction: 0xf89b9201
d0018400:	9901202a 	stmdbls	r1, {r1, r3, r5, sp}
d0018404:	d81e428a 	ldmdale	lr, {r1, r3, r7, r9, lr}
d0018408:	f44f9b03 			; <UNDEFINED> instruction: 0xf44f9b03
d001840c:	fb02721a 	blx	0xd00b4c7e
d0018410:	9a014103 	bls	0xd0068824
d0018414:	3168f501 	msrcc	SPSR_f, r1, lsl #10
d0018418:	302af891 	mlacc	sl, r1, r8, pc	; <UNPREDICTABLE>
d001841c:	d1244293 			; <UNDEFINED> instruction: 0xd1244293
d0018420:	302bf891 	mlacc	fp, r1, r8, pc	; <UNPREDICTABLE>
d0018424:	4ba1b9f3 	blmi	0xce886bf8
d0018428:	6da5447b 	cfstrsvs	mvf4, [r5, #492]!	; 0x1ec
d001842c:	d1d32d00 	bicsle	r2, r3, r0, lsl #26
d0018430:	e9c466a7 	stmib	r4, {r0, r1, r2, r5, r7, r9, sl, sp, lr}^
d0018434:	e9c43a16 	stmib	r4, {r1, r2, r4, r9, fp, ip, sp}^
d0018438:	46289818 			; <UNDEFINED> instruction: 0x46289818
d001843c:	ecbdb007 	ldc	0, cr11, [sp], #28
d0018440:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d0018444:	68718ff0 	ldmdavs	r1!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}^
d0018448:	2a10ee18 	bcs	0xd0453cb0
d001844c:	0b24f856 	bleq	0xd09565ac
d0018450:	f7f89305 			; <UNDEFINED> instruction: 0xf7f89305
d0018454:	9b05f935 	blls	0xd0196930
d0018458:	d1d52800 	bicsle	r2, r5, r0, lsl #16
d001845c:	32019a01 	andcc	r9, r1, #4096	; 0x1000
d0018460:	e7cc9201 	strb	r9, [ip, r1, lsl #4]
d0018464:	447b4b92 	ldrbtmi	r4, [fp], #-2962	; 0xfffff46e
d0018468:	2324e7df 			; <UNDEFINED> instruction: 0x2324e7df
d001846c:	99019a02 	stmdbls	r1, {r1, r9, fp, ip, pc}
d0018470:	2601fb03 	strcs	pc, [r1], -r3, lsl #22
d0018474:	8c5a19a3 	mrrchi	9, 10, r1, sl, cr3	; <UNPREDICTABLE>
d0018478:	6020f893 	mlavs	r0, r3, r8, pc	; <UNPREDICTABLE>
d001847c:	b021f893 	mlalt	r1, r3, r8, pc	; <UNPREDICTABLE>
d0018480:	2101b14a 	tstcs	r1, sl, asr #2
d0018484:	00924620 	addseq	r4, r2, r0, lsr #12
d0018488:	fecdf7fc 	mcr2	7, 6, pc, cr13, cr12, {7}	; <UNPREDICTABLE>
d001848c:	51c2f44f 	bicpl	pc, r2, pc, asr #8
d0018490:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0018494:	f1bbfb0d 			; <UNDEFINED> instruction: 0xf1bbfb0d
d0018498:	d06f0f00 	rsble	r0, pc, r0, lsl #30
d001849c:	7191f44f 	orrsvc	pc, r1, pc, asr #8
d00184a0:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d00184a4:	b170fd1f 	cmnlt	r0, pc, lsl sp	; <UNPREDICTABLE>
d00184a8:	d1052eff 	strdle	r2, [r5, -pc]
d00184ac:	2d006da5 	stccs	13, cr6, [r0, #-660]	; 0xfffffd6c
d00184b0:	4b80d192 	blmi	0xce04cb00
d00184b4:	e7bb447b 			; <UNDEFINED> instruction: 0xe7bb447b
d00184b8:	41d0f44f 	bicsmi	pc, r0, pc, asr #8
d00184bc:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d00184c0:	9603faf7 			; <UNDEFINED> instruction: 0x9603faf7
d00184c4:	6ae3e773 	bvs	0xcf912298
d00184c8:	d10b2b2e 	tstle	fp, lr, lsr #22
d00184cc:	b10b6da3 	smlatblt	fp, r3, sp, r6
d00184d0:	e7b22503 	ldr	r2, [r2, r3, lsl #10]!
d00184d4:	447b4b78 	ldrbtmi	r4, [fp], #-2936	; 0xfffff488
d00184d8:	e9c466a7 	stmib	r4, {r0, r1, r2, r5, r7, r9, sl, sp, lr}^
d00184dc:	e9c43a16 	stmib	r4, {r1, r2, r4, r9, fp, ip, sp}^
d00184e0:	e7f59818 			; <UNDEFINED> instruction: 0xe7f59818
d00184e4:	6da3b12d 	stfvsd	f3, [r3, #180]!	; 0xb4
d00184e8:	d1f12b00 	mvnsle	r2, r0, lsl #22
d00184ec:	447b4b73 	ldrbtmi	r4, [fp], #-2931	; 0xfffff48d
d00184f0:	9b04e7f2 	blls	0xd01524c0
d00184f4:	213db30b 	teqcs	sp, fp, lsl #6
d00184f8:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d00184fc:	b1e0fcf3 	strdlt	pc, [r0, #195]!	; 0xc3
d0018500:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d0018504:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0018508:	2efffad3 	mrccs	10, 7, APSR_nzcv, cr15, cr3, {6}
d001850c:	2204d110 	andcs	sp, r4, #16, 2
d0018510:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d0018514:	fe5ef7fd 	mrc2	7, 2, pc, cr14, cr13, {7}
d0018518:	4106f64b 	tstmi	r6, fp, asr #12	; <UNPREDICTABLE>
d001851c:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0018520:	f246fac7 	vpmax.s8	<illegal reg q15.5>, q11, <illegal reg q3.5>
d0018524:	46200108 	strtmi	r0, [r0], -r8, lsl #2
d0018528:	f7fc2502 			; <UNDEFINED> instruction: 0xf7fc2502
d001852c:	e784fac1 	str	pc, [r4, r1, asr #21]
d0018530:	46204631 			; <UNDEFINED> instruction: 0x46204631
d0018534:	fc74f7ff 	ldc2l	7, cr15, [r4], #-1020	; 0xfffffc04
d0018538:	6ae3e7ee 	bvs	0xcf9124f8
d001853c:	7592f46f 	ldrvc	pc, [r2, #1135]	; 0x46f
d0018540:	2a01195a 	bcs	0xd005eab0
d0018544:	f46fd904 	vld2.8	{d29,d31}, [pc], r4
d0018548:	44037094 	strmi	r7, [r3], #-148	; 0xffffff6c
d001854c:	d8082b04 	stmdale	r8, {r2, r8, r9, fp, sp}
d0018550:	b9336da3 	ldmdblt	r3!, {r0, r1, r5, r7, r8, sl, fp, sp, lr}
d0018554:	66a74b5a 	ssatvs	r4, #8, sl, asr #22
d0018558:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d001855c:	e9c49818 	stmib	r4, {r3, r4, fp, ip, pc}^
d0018560:	46203a16 			; <UNDEFINED> instruction: 0x46203a16
d0018564:	41d0f44f 	bicsmi	pc, r0, pc, asr #8
d0018568:	faa2f7fc 	blx	0xce8d6560
d001856c:	2492f504 	ldrcs	pc, [r2], #1284	; 0x504
d0018570:	f8c42eff 			; <UNDEFINED> instruction: 0xf8c42eff
d0018574:	d1ab6248 			; <UNDEFINED> instruction: 0xd1ab6248
d0018578:	e75e2504 	ldrb	r2, [lr, -r4, lsl #10]
d001857c:	d00d2eff 	strdle	r2, [sp], -pc	; <UNPREDICTABLE>
d0018580:	4620212e 	strtmi	r2, [r0], -lr, lsr #2
d0018584:	fcaef7fa 	stc2	7, cr15, [lr], #1000	; 0x3e8
d0018588:	d19a2800 	orrsle	r2, sl, r0, lsl #16
d001858c:	d19f2d00 	orrsle	r2, pc, r0, lsl #26
d0018590:	2b006da3 	blcs	0xd0033c24
d0018594:	4b4bd19c 	blmi	0xd130cc0c
d0018598:	e79d447b 			; <UNDEFINED> instruction: 0xe79d447b
d001859c:	2e2e6ae6 	vnmulcs.f32	s12, s29, s13
d00185a0:	f5b6d002 			; <UNDEFINED> instruction: 0xf5b6d002
d00185a4:	d1057f91 			; <UNDEFINED> instruction: 0xd1057f91
d00185a8:	46204947 	strtmi	r4, [r0], -r7, asr #18
d00185ac:	f7f74479 			; <UNDEFINED> instruction: 0xf7f74479
d00185b0:	e711fe4d 	ldr	pc, [r1, -sp, asr #28]
d00185b4:	d1df2d00 	bicsle	r2, pc, r0, lsl #26
d00185b8:	2b009b04 	blcs	0xd003f1d0
d00185bc:	2e3dd06d 	cdpcs	0, 3, cr13, cr13, cr13, {3}
d00185c0:	f46fd009 	vld4.8	{d29-d32}, [pc], r9
d00185c4:	18737192 	ldmdane	r3!, {r1, r4, r7, r8, ip, sp, lr}^
d00185c8:	d9042b01 	stmdble	r4, {r0, r8, r9, fp, sp}
d00185cc:	7294f46f 	addsvc	pc, r4, #1862270976	; 0x6f000000
d00185d0:	2b0418b3 	blcs	0xd011e8a4
d00185d4:	4620d861 	strtmi	sp, [r0], -r1, ror #16
d00185d8:	fc64f7fa 	stc2l	7, cr15, [r4], #-1000	; 0xfffffc18
d00185dc:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d00185e0:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d00185e4:	2e3dfa65 	vsubcs.f32	s30, s26, s11
d00185e8:	f44fd009 	vst4.8	{d29-d32}, [pc], r9
d00185ec:	462041d0 			; <UNDEFINED> instruction: 0x462041d0
d00185f0:	fa5ef7fc 	blx	0xd17d65e8
d00185f4:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d00185f8:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d00185fc:	2201fa59 	andcs	pc, r1, #364544	; 0x59000
d0018600:	46114620 	ldrmi	r4, [r1], -r0, lsr #12
d0018604:	fde6f7fd 	stc2l	7, cr15, [r6, #1012]!	; 0x3f4
d0018608:	d0852e3d 	addle	r2, r5, sp, lsr lr
d001860c:	4106f64b 	tstmi	r6, fp, asr #12	; <UNPREDICTABLE>
d0018610:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0018614:	f46ffa4d 	vld1.16	{d31-d32}, [pc]!
d0018618:	18f37392 	ldmne	r3!, {r1, r4, r7, r8, r9, ip, sp, lr}^
d001861c:	f63f2b08 			; <UNDEFINED> instruction: 0xf63f2b08
d0018620:	a202af7b 	andge	sl, r2, #492	; 0x1ec
d0018624:	3023f852 	eorcc	pc, r3, r2, asr r8	; <UNPREDICTABLE>
d0018628:	4710441a 			; <UNDEFINED> instruction: 0x4710441a
d001862c:	00000025 	andeq	r0, r0, r5, lsr #32
d0018630:	00000031 	andeq	r0, r0, r1, lsr r0
d0018634:	fffffeed 			; <UNDEFINED> instruction: 0xfffffeed
d0018638:	fffffeed 			; <UNDEFINED> instruction: 0xfffffeed
d001863c:	00000037 	andeq	r0, r0, r7, lsr r0
d0018640:	0000003d 	andeq	r0, r0, sp, lsr r0
d0018644:	00000043 	andeq	r0, r0, r3, asr #32
d0018648:	00000049 	andeq	r0, r0, r9, asr #32
d001864c:	00000049 	andeq	r0, r0, r9, asr #32
d0018650:	0108f641 	tsteq	r8, r1, asr #12	; <UNPREDICTABLE>
d0018654:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0018658:	e75dfa2b 	ldrb	pc, [sp, -fp, lsr #20]	; <UNPREDICTABLE>
d001865c:	2108f641 	tstcs	r8, r1, asr #12	; <UNPREDICTABLE>
d0018660:	f244e7f8 	vaba.s8	q15, q10, q12
d0018664:	e7f50108 	ldrb	r0, [r5, r8, lsl #2]!
d0018668:	3108f244 	tstcc	r8, r4, asr #4	; <UNPREDICTABLE>
d001866c:	f244e7f2 	vaba.s8	q15, q10, q9
d0018670:	e7ef0148 	strb	r0, [pc, r8, asr #2]!
d0018674:	6102f244 	tstvs	r2, r4, asr #4	; <UNPREDICTABLE>
d0018678:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d001867c:	f244fa19 	vpmin.s8	d31, d4, d9
d0018680:	46206108 	strtmi	r6, [r0], -r8, lsl #2
d0018684:	fa14f7fc 	blx	0xd055667c
d0018688:	0190f244 	orrseq	pc, r0, r4, asr #4
d001868c:	1310f244 	tstne	r0, #68, 4	; 0x40000004	; <UNPREDICTABLE>
d0018690:	7f96f5b6 	svcvc	0x0096f5b6
d0018694:	4619bf18 	sadd16mi	fp, r9, r8
d0018698:	f44fe7dc 	vst1.64	{d30}, [pc :64], ip
d001869c:	462041d0 			; <UNDEFINED> instruction: 0x462041d0
d00186a0:	fa06f7fc 	blx	0xd01d6698
d00186a4:	bf00e6c9 	svclt	0x0000e6c9
d00186a8:	fffffee3 			; <UNDEFINED> instruction: 0xfffffee3
d00186ac:	fffffe44 			; <UNDEFINED> instruction: 0xfffffe44
d00186b0:	fffffdf2 			; <UNDEFINED> instruction: 0xfffffdf2
d00186b4:	fffffde9 			; <UNDEFINED> instruction: 0xfffffde9
d00186b8:	fffffde9 			; <UNDEFINED> instruction: 0xfffffde9
d00186bc:	fffffdf2 			; <UNDEFINED> instruction: 0xfffffdf2
d00186c0:	fffffdbe 			; <UNDEFINED> instruction: 0xfffffdbe
d00186c4:	fffffda3 			; <UNDEFINED> instruction: 0xfffffda3
d00186c8:	fffffdb7 			; <UNDEFINED> instruction: 0xfffffdb7

Disassembly of section .text.unary:

d0018a34 <.text.unary>:
d0018a34:	4ff0e92d 	svcmi	0x00f0e92d
d0018a38:	b058f8d0 	ldrsblt	pc, [r8], #-128	; 0xffffff80	; <UNPREDICTABLE>
d0018a3c:	460e4604 	strmi	r4, [lr], -r4, lsl #12
d0018a40:	8b02ed2d 	blhi	0xd00d3efc
d0018a44:	f1bbb09d 			; <UNDEFINED> instruction: 0xf1bbb09d
d0018a48:	f0400f00 			; <UNDEFINED> instruction: 0xf0400f00
d0018a4c:	6a838527 	bvs	0xce0f9ef0
d0018a50:	93076ac7 	movwls	r6, #31431	; 0x7ac7
d0018a54:	3030f890 	mlascc	r0, r0, r8, pc	; <UNPREDICTABLE>
d0018a58:	6b439308 	blvs	0xd10fd680
d0018a5c:	f5009306 			; <UNDEFINED> instruction: 0xf5009306
d0018a60:	f8d32392 			; <UNDEFINED> instruction: 0xf8d32392
d0018a64:	93092244 	movwls	r2, #37444	; 0x9244
d0018a68:	2a203201 	bcs	0xd0825274
d0018a6c:	9a06e9d0 	bls	0xd01d31b4
d0018a70:	5808e9d0 	stmdapl	r8, {r4, r6, r7, r8, fp, sp, lr, pc}
d0018a74:	2244f8c3 	subcs	pc, r4, #12779520	; 0xc30000
d0018a78:	f8dfd906 			; <UNDEFINED> instruction: 0xf8dfd906
d0018a7c:	44791b2c 	ldrbtmi	r1, [r9], #-2860	; 0xfffff4d4
d0018a80:	fbe4f7f7 	blx	0xcf956a66
d0018a84:	e0d12500 	sbcs	r2, r1, r0, lsl #10
d0018a88:	718df44f 	orrvc	pc, sp, pc, asr #8
d0018a8c:	fa2af7fa 	blx	0xd0ad6a7c
d0018a90:	4620b140 	strtmi	fp, [r0], -r0, asr #2
d0018a94:	ffc6f7fa 			; <UNDEFINED> instruction: 0xffc6f7fa
d0018a98:	46204601 	strtmi	r4, [r0], -r1, lsl #12
d0018a9c:	fc05f7fc 	stc2	7, cr15, [r5], {252}	; 0xfc
d0018aa0:	e0c32501 	sbc	r2, r3, r1, lsl #10
d0018aa4:	7181f44f 	orrvc	pc, r1, pc, asr #8
d0018aa8:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0018aac:	b150fa1b 	cmplt	r0, fp, lsl sl	; <UNPREDICTABLE>
d0018ab0:	46294620 	strtmi	r4, [r9], -r0, lsr #12
d0018ab4:	fbf9f7fc 	blx	0xcfe96aae
d0018ab8:	1003f240 	andne	pc, r3, r0, asr #4
d0018abc:	bf144287 	svclt	0x00144287
d0018ac0:	25012500 	strcs	r2, [r1, #-1280]	; 0xfffffb00
d0018ac4:	f240e0b2 	vqadd.s8	d30, d16, d18
d0018ac8:	46201103 	strtmi	r1, [r0], -r3, lsl #2
d0018acc:	fa0af7fa 	blx	0xd02d6abc
d0018ad0:	d1ed2800 	mvnle	r2, r0, lsl #16
d0018ad4:	1123f240 	msrne	R11_usr, r0
d0018ad8:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0018adc:	b308fa03 	movwlt	pc, #35331	; 0x8a03	; <UNPREDICTABLE>
d0018ae0:	2ac8f8df 	bcs	0xcf256e64
d0018ae4:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d0018ae8:	46206a63 	strtmi	r6, [r0], -r3, ror #20
d0018aec:	f8d4447a 			; <UNDEFINED> instruction: 0xf8d4447a
d0018af0:	f8948028 			; <UNDEFINED> instruction: 0xf8948028
d0018af4:	f8d49030 			; <UNDEFINED> instruction: 0xf8d49030
d0018af8:	9306a034 	movwls	sl, #24628	; 0x6034
d0018afc:	5606e9d4 			; <UNDEFINED> instruction: 0x5606e9d4
d0018b00:	f9fef7fa 			; <UNDEFINED> instruction: 0xf9fef7fa
d0018b04:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d0018b08:	22008325 	andcs	r8, r0, #-1811939328	; 0x94000000
d0018b0c:	46299b06 	strtmi	r9, [r9], -r6, lsl #22
d0018b10:	92049703 	andls	r9, r4, #786432	; 0xc0000
d0018b14:	e88d4632 	stm	sp, {r1, r4, r5, r9, sl, lr}
d0018b18:	46200700 	strtmi	r0, [r0], -r0, lsl #14
d0018b1c:	f9d8f7fc 			; <UNDEFINED> instruction: 0xf9d8f7fc
d0018b20:	e0834605 	add	r4, r3, r5, lsl #12
d0018b24:	7192f44f 	orrsvc	pc, r2, pc, asr #8
d0018b28:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0018b2c:	4683f9db 	pkhtbmi	pc, r3, fp, asr #19	; <UNPREDICTABLE>
d0018b30:	d1d52800 	bicsle	r2, r5, r0, lsl #16
d0018b34:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d0018b38:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0018b3c:	4605f9d3 			; <UNDEFINED> instruction: 0x4605f9d3
d0018b40:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d0018b44:	f8df82ee 			; <UNDEFINED> instruction: 0xf8df82ee
d0018b48:	46512a68 	ldrbmi	r2, [r1], -r8, ror #20
d0018b4c:	447a4648 	ldrbtmi	r4, [sl], #-1608	; 0xfffff9b8
d0018b50:	fedef7f7 	mrc2	7, 6, pc, cr14, cr7, {7}
d0018b54:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d0018b58:	6ae380a5 	bvs	0xcf8f8df4
d0018b5c:	f0402b2e 			; <UNDEFINED> instruction: 0xf0402b2e
d0018b60:	f8df80a1 			; <UNDEFINED> instruction: 0xf8df80a1
d0018b64:	25039a50 	strcs	r9, [r3, #-2640]	; 0xfffff5b0
d0018b68:	1a4cf8df 	bne	0xd1356eec
d0018b6c:	44f92203 	ldrbtmi	r2, [r9], #515	; 0x203
d0018b70:	4479a80c 	ldrbtmi	sl, [r9], #-2060	; 0xfffff7f4
d0018b74:	f9d0f008 			; <UNDEFINED> instruction: 0xf9d0f008
d0018b78:	2f2e6ae7 	svccs	0x002e6ae7
d0018b7c:	f5b7d002 			; <UNDEFINED> instruction: 0xf5b7d002
d0018b80:	d12c7f91 			; <UNDEFINED> instruction: 0xd12c7f91
d0018b84:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0018b88:	69a3f98d 	stmibvs	r3!, {r0, r2, r3, r7, r8, fp, ip, sp, lr, pc}
d0018b8c:	f240464a 	vmax.s8	q10, q0, q5
d0018b90:	ee081101 	adfe	f1, f0, f1
d0018b94:	6a633a10 	bvs	0xd18e73dc
d0018b98:	f8d44620 			; <UNDEFINED> instruction: 0xf8d44620
d0018b9c:	930ba01c 	movwls	sl, #45084	; 0xb01c
d0018ba0:	6b666aa3 	blvs	0xd19b3634
d0018ba4:	f8949309 			; <UNDEFINED> instruction: 0xf8949309
d0018ba8:	930a3030 	movwls	r3, #41008	; 0xa030
d0018bac:	f9a8f7fa 			; <UNDEFINED> instruction: 0xf9a8f7fa
d0018bb0:	2f2eb1a8 	svccs	0x002eb1a8
d0018bb4:	020aeb05 	andeq	lr, sl, #5120	; 0x1400
d0018bb8:	bf0c9b0b 	svclt	0x000c9b0b
d0018bbc:	21022101 	tstcs	r2, r1, lsl #2
d0018bc0:	2a3f440a 	bcs	0xd0fe9bf0
d0018bc4:	6da2d93b 			; <UNDEFINED> instruction: 0x6da2d93b
d0018bc8:	f8dfb94a 			; <UNDEFINED> instruction: 0xf8dfb94a
d0018bcc:	66a629f0 			; <UNDEFINED> instruction: 0x66a629f0
d0018bd0:	e9c4447a 	stmib	r4, {r1, r3, r4, r5, r6, sl, lr}^
d0018bd4:	9b092316 	blls	0xd0261834
d0018bd8:	9b0a6623 	blls	0xd02b246c
d0018bdc:	ab1c6663 	blge	0xd0732570
d0018be0:	442b2200 	strtmi	r2, [fp], #-512	; 0xfffffe00
d0018be4:	2c40f803 	mcrrcs	8, 0, pc, r0, cr3	; <UNPREDICTABLE>
d0018be8:	b9f36da3 	ldmiblt	r3!, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0018bec:	29d0f8df 	ldmibcs	r0, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d0018bf0:	46202128 	strtmi	r2, [r0], -r8, lsr #2
d0018bf4:	f7fa447a 			; <UNDEFINED> instruction: 0xf7fa447a
d0018bf8:	b1b0f983 	lslslt	pc, r3, #19	; <UNPREDICTABLE>
d0018bfc:	a90c462a 	stmdbge	ip, {r1, r3, r5, r9, sl, lr}
d0018c00:	f7f74620 			; <UNDEFINED> instruction: 0xf7f74620
d0018c04:	4605fe9a 			; <UNDEFINED> instruction: 0x4605fe9a
d0018c08:	d0362800 	eorsle	r2, r6, r0, lsl #16
d0018c0c:	46204601 	strtmi	r4, [r0], -r1, lsl #12
d0018c10:	f856f7fe 			; <UNDEFINED> instruction: 0xf856f7fe
d0018c14:	3047f895 	umaalcc	pc, r7, r5, r8	; <UNPREDICTABLE>
d0018c18:	d03d2b07 	eorsle	r2, sp, r7, lsl #22
d0018c1c:	2a011f5a 	bcs	0xd006098c
d0018c20:	2b10d93d 	blcs	0xd044f11c
d0018c24:	f04fbf08 			; <UNDEFINED> instruction: 0xf04fbf08
d0018c28:	465d0b01 	ldrbmi	r0, [sp], -r1, lsl #22
d0018c2c:	2492f504 	ldrcs	pc, [r2], #1284	; 0x504
d0018c30:	f8d44628 			; <UNDEFINED> instruction: 0xf8d44628
d0018c34:	3b013244 	blcc	0xd006554c
d0018c38:	3244f8c4 	subcc	pc, r4, #196, 16	; 0xc40000
d0018c3c:	2f2ee291 	svccs	0x002ee291
d0018c40:	f105ab1c 			; <UNDEFINED> instruction: 0xf105ab1c
d0018c44:	a80c0601 	stmdage	ip, {r0, r9, sl}
d0018c48:	bf18442b 	svclt	0x0018442b
d0018c4c:	ee18222d 	cdp	2, 1, cr2, cr8, cr13, {1}
d0018c50:	bf1c1a10 	svclt	0x001c1a10
d0018c54:	2c40f803 	mcrrcs	8, 0, pc, r0, cr3	; <UNPREDICTABLE>
d0018c58:	4652ab1c 			; <UNDEFINED> instruction: 0x4652ab1c
d0018c5c:	f803bf0f 			; <UNDEFINED> instruction: 0xf803bf0f
d0018c60:	18f67c40 	ldmne	r6!, {r6, sl, fp, ip, sp, lr}^
d0018c64:	f806233e 			; <UNDEFINED> instruction: 0xf806233e
d0018c68:	bf183c40 	svclt	0x00183c40
d0018c6c:	44301cae 	ldrtmi	r1, [r0], #-3246	; 0xfffff352
d0018c70:	050aeb06 	streq	lr, [sl, #-2822]	; 0xfffff4fa
d0018c74:	f950f008 			; <UNDEFINED> instruction: 0xf950f008
d0018c78:	6da3e77e 	stcvs	7, cr14, [r3, #504]!	; 0x1f8
d0018c7c:	d1d42b00 	bicsle	r2, r4, r0, lsl #22
d0018c80:	3940f8df 	stmdbcc	r0, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d0018c84:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0018c88:	9b073816 	blls	0xd01e6ce8
d0018c8c:	9b086623 	blls	0xd0232520
d0018c90:	9b066663 	blls	0xd01b2624
d0018c94:	e7c866a3 	strb	r6, [r8, r3, lsr #13]
d0018c98:	0b02f04f 	bleq	0xd00d4ddc
d0018c9c:	f04fe7c5 			; <UNDEFINED> instruction: 0xf04fe7c5
d0018ca0:	e7c20b01 	strb	r0, [r2, r1, lsl #22]
d0018ca4:	46202128 	strtmi	r2, [r0], -r8, lsr #2
d0018ca8:	f91cf7fa 			; <UNDEFINED> instruction: 0xf91cf7fa
d0018cac:	b3184605 	tstlt	r8, #5242880	; 0x500000
d0018cb0:	46524649 	ldrbmi	r4, [r2], -r9, asr #12
d0018cb4:	f7f74620 			; <UNDEFINED> instruction: 0xf7f74620
d0018cb8:	1e01fd79 	mcrne	13, 0, pc, cr1, cr9, {3}	; <UNPREDICTABLE>
d0018cbc:	2330db0f 	teqcs	r0, #15360	; 0x3c00
d0018cc0:	4301fb03 	movwmi	pc, #6915	; 0x1b03	; <UNPREDICTABLE>
d0018cc4:	2390f503 	orrscs	pc, r0, #12582912	; 0xc00000
d0018cc8:	3659f893 			; <UNDEFINED> instruction: 0x3659f893
d0018ccc:	d1062b0c 	tstle	r6, ip, lsl #22
d0018cd0:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0018cd4:	4605fad9 			; <UNDEFINED> instruction: 0x4605fad9
d0018cd8:	d1a72d04 			; <UNDEFINED> instruction: 0xd1a72d04
d0018cdc:	9b06e0d9 	blls	0xd01d1048
d0018ce0:	46494652 			; <UNDEFINED> instruction: 0x46494652
d0018ce4:	93024620 	movwls	r4, #9760	; 0x2620
d0018ce8:	93019b08 	movwls	r9, #6920	; 0x1b08
d0018cec:	93009b07 	movwls	r9, #2823	; 0xb07
d0018cf0:	f7fe4643 			; <UNDEFINED> instruction: 0xf7fe4643
d0018cf4:	e7eefdb9 			; <UNDEFINED> instruction: 0xe7eefdb9
d0018cf8:	f46f6ae7 	vld1.64	{d22-d23}, [pc :128], r7
d0018cfc:	183b7091 	ldmdane	fp!, {r0, r4, r7, ip, sp, lr}
d0018d00:	d80f2b01 	stmdale	pc, {r0, r8, r9, fp, sp}	; <UNPREDICTABLE>
d0018d04:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0018d08:	2301f8cd 	movwcs	pc, #6349	; 0x18cd	; <UNPREDICTABLE>
d0018d0c:	46494652 			; <UNDEFINED> instruction: 0x46494652
d0018d10:	9b069304 	blls	0xd01bd928
d0018d14:	93029703 	movwls	r9, #9987	; 0x2703
d0018d18:	93019b08 	movwls	r9, #6920	; 0x1b08
d0018d1c:	93009b07 	movwls	r9, #2823	; 0xb07
d0018d20:	e6fa4643 	ldrbt	r4, [sl], r3, asr #12
d0018d24:	46494652 			; <UNDEFINED> instruction: 0x46494652
d0018d28:	f7f74620 			; <UNDEFINED> instruction: 0xf7f74620
d0018d2c:	4652fd3f 			; <UNDEFINED> instruction: 0x4652fd3f
d0018d30:	46494607 	strbmi	r4, [r9], -r7, lsl #12
d0018d34:	f7f74620 			; <UNDEFINED> instruction: 0xf7f74620
d0018d38:	4683fe1e 	pkhbtmi	pc, r3, lr, lsl #28	; <UNPREDICTABLE>
d0018d3c:	6a01b120 	bvs	0xd00851c4
d0018d40:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0018d44:	e771fab2 			; <UNDEFINED> instruction: 0xe771fab2
d0018d48:	f2c02f00 			; <UNDEFINED> instruction: 0xf2c02f00
d0018d4c:	f04f810d 			; <UNDEFINED> instruction: 0xf04f810d
d0018d50:	fb0a0a30 	blx	0xd029b61a
d0018d54:	f50a4a07 			; <UNDEFINED> instruction: 0xf50a4a07
d0018d58:	f89a2a90 			; <UNDEFINED> instruction: 0xf89a2a90
d0018d5c:	f1b99659 			; <UNDEFINED> instruction: 0xf1b99659
d0018d60:	d0020f02 	andle	r0, r2, r2, lsl #30
d0018d64:	0f04f1b9 	svceq	0x0004f1b9
d0018d68:	6da3d10e 	stfvsd	f5, [r3, #56]!	; 0x38
d0018d6c:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0018d70:	f8dfae89 			; <UNDEFINED> instruction: 0xf8dfae89
d0018d74:	447b3854 	ldrbtmi	r3, [fp], #-2132	; 0xfffff7ac
d0018d78:	3816e9c4 	ldmdacc	r6, {r2, r6, r7, r8, fp, sp, lr, pc}
d0018d7c:	66239b07 	strtvs	r9, [r3], -r7, lsl #22
d0018d80:	66639b08 	strbtvs	r9, [r3], -r8, lsl #22
d0018d84:	e0e79b06 	rsc	r9, r7, r6, lsl #22
d0018d88:	0f0cf1b9 	svceq	0x000cf1b9
d0018d8c:	462ad106 	strtmi	sp, [sl], -r6, lsl #2
d0018d90:	46204639 			; <UNDEFINED> instruction: 0x46204639
d0018d94:	feaaf7fb 	mcr2	7, 5, pc, cr10, cr11, {7}	; <UNPREDICTABLE>
d0018d98:	e7472503 	strb	r2, [r7, -r3, lsl #10]
d0018d9c:	0f13f1b9 	svceq	0x0013f1b9
d0018da0:	462ad106 	strtmi	sp, [sl], -r6, lsl #2
d0018da4:	46204639 			; <UNDEFINED> instruction: 0x46204639
d0018da8:	fea0f7fb 	mcr2	7, 5, pc, cr0, cr11, {7}	; <UNPREDICTABLE>
d0018dac:	e73d2507 	ldr	r2, [sp, -r7, lsl #10]!
d0018db0:	0f12f1b9 	svceq	0x0012f1b9
d0018db4:	462ad10b 	strtmi	sp, [sl], -fp, lsl #2
d0018db8:	46204639 			; <UNDEFINED> instruction: 0x46204639
d0018dbc:	fe96f7fb 	mrc2	7, 4, pc, cr6, cr11, {7}
d0018dc0:	365af89a 			; <UNDEFINED> instruction: 0x365af89a
d0018dc4:	25059a09 	strcs	r9, [r5, #-2569]	; 0xfffff5f7
d0018dc8:	3248f8c2 	subcc	pc, r8, #12713984	; 0xc20000
d0018dcc:	f1a9e72e 			; <UNDEFINED> instruction: 0xf1a9e72e
d0018dd0:	2b01030d 	blcs	0xd0059a0c
d0018dd4:	f1b9d83d 			; <UNDEFINED> instruction: 0xf1b9d83d
d0018dd8:	d11e0f0d 	tstle	lr, sp, lsl #30
d0018ddc:	46204639 			; <UNDEFINED> instruction: 0x46204639
d0018de0:	fd3ef7fc 	ldc2	7, cr15, [lr, #-1008]!	; 0xfffffc10
d0018de4:	4620212e 	strtmi	r2, [r0], -lr, lsr #2
d0018de8:	f87cf7fa 			; <UNDEFINED> instruction: 0xf87cf7fa
d0018dec:	b1604605 	cmnlt	r0, r5, lsl #12
d0018df0:	23002030 	movwcs	r2, #48	; 0x30
d0018df4:	fb004632 	blx	0xd002a6c6
d0018df8:	f5074707 			; <UNDEFINED> instruction: 0xf5074707
d0018dfc:	f8972790 			; <UNDEFINED> instruction: 0xf8972790
d0018e00:	4620165a 			; <UNDEFINED> instruction: 0x4620165a
d0018e04:	fac6f7ff 	blx	0xcf1d6e08
d0018e08:	6da3e68a 	stcvs	6, cr14, [r3, #552]!	; 0x228
d0018e0c:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0018e10:	f8dfae39 			; <UNDEFINED> instruction: 0xf8dfae39
d0018e14:	447b37b8 	ldrbtmi	r3, [fp], #-1976	; 0xfffff848
d0018e18:	2200e7ae 	andcs	lr, r0, #45613056	; 0x2b80000
d0018e1c:	46204639 			; <UNDEFINED> instruction: 0x46204639
d0018e20:	fe64f7fb 	mcr2	7, 3, pc, cr4, cr11, {7}	; <UNPREDICTABLE>
d0018e24:	7191f44f 	orrsvc	pc, r1, pc, asr #8
d0018e28:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0018e2c:	4603f85b 			; <UNDEFINED> instruction: 0x4603f85b
d0018e30:	d1dd2800 	bicsle	r2, sp, r0, lsl #16
d0018e34:	2a5b6ae2 	bcs	0xd16f39c4
d0018e38:	2230d1ae 	eorscs	sp, r0, #-2147483605	; 0x8000002b
d0018e3c:	4707fb02 	strmi	pc, [r7, -r2, lsl #22]
d0018e40:	2790f507 	ldrcs	pc, [r0, r7, lsl #10]
d0018e44:	f8974632 			; <UNDEFINED> instruction: 0xf8974632
d0018e48:	4620165a 			; <UNDEFINED> instruction: 0x4620165a
d0018e4c:	fab6f7fe 	blx	0xcedd6e4c
d0018e50:	f1b9e666 			; <UNDEFINED> instruction: 0xf1b9e666
d0018e54:	d1150f10 	tstle	r5, r0, lsl pc
d0018e58:	46204639 			; <UNDEFINED> instruction: 0x46204639
d0018e5c:	fd00f7fc 	stc2	7, cr15, [r0, #-1008]	; 0xfffffc10
d0018e60:	2b5b6ae3 	blcs	0xd16f39f4
d0018e64:	2030d106 	eorscs	sp, r0, r6, lsl #2
d0018e68:	fb002300 	blx	0xd0021a72
d0018e6c:	f5074707 			; <UNDEFINED> instruction: 0xf5074707
d0018e70:	e7e72790 			; <UNDEFINED> instruction: 0xe7e72790
d0018e74:	2b006da3 	blcs	0xd0034508
d0018e78:	ae04f47f 	mcrge	4, 0, pc, cr4, cr15, {3}	; <UNPREDICTABLE>
d0018e7c:	3750f8df 	smmlscc	r0, pc, r8, pc	; <UNPREDICTABLE>
d0018e80:	e779447b 			; <UNDEFINED> instruction: 0xe779447b
d0018e84:	0f09f1b9 	svceq	0x0009f1b9
d0018e88:	4639d10a 	ldrtmi	sp, [r9], -sl, lsl #2
d0018e8c:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0018e90:	6ae3fce7 	bvs	0xcf918234
d0018e94:	f0402b5b 			; <UNDEFINED> instruction: 0xf0402b5b
d0018e98:	22008213 	andcs	r8, r0, #805306369	; 0x30000001
d0018e9c:	e1b54631 			; <UNDEFINED> instruction: 0xe1b54631
d0018ea0:	46392200 	ldrtmi	r2, [r9], -r0, lsl #4
d0018ea4:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0018ea8:	f1b9fe21 			; <UNDEFINED> instruction: 0xf1b9fe21
d0018eac:	d1550f06 	cmple	r5, r6, lsl #30
d0018eb0:	7191f44f 	orrsvc	pc, r1, pc, asr #8
d0018eb4:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0018eb8:	2800f815 	stmdacs	r0, {r0, r2, r4, fp, ip, sp, lr, pc}
d0018ebc:	af6cf43f 	svcge	0x006cf43f
d0018ec0:	f2406aa3 	vpmax.s8	d22, d16, d19
d0018ec4:	f8df1101 			; <UNDEFINED> instruction: 0xf8df1101
d0018ec8:	4620270c 	strtmi	r2, [r0], -ip, lsl #14
d0018ecc:	6b639306 	blvs	0xd18fdaec
d0018ed0:	f8d4447a 			; <UNDEFINED> instruction: 0xf8d4447a
d0018ed4:	f8949024 			; <UNDEFINED> instruction: 0xf8949024
d0018ed8:	93077030 	movwls	r7, #28720	; 0x7030
d0018edc:	ab06e9d4 	blge	0xd01d3634
d0018ee0:	f80ef7fa 			; <UNDEFINED> instruction: 0xf80ef7fa
d0018ee4:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0018ee8:	f8dfadcd 			; <UNDEFINED> instruction: 0xf8dfadcd
d0018eec:	260086ec 	strcs	r8, [r0], -ip, ror #13
d0018ef0:	f85844f8 			; <UNDEFINED> instruction: 0xf85844f8
d0018ef4:	46592b04 	ldrbmi	r2, [r9], -r4, lsl #22
d0018ef8:	f7f74650 			; <UNDEFINED> instruction: 0xf7f74650
d0018efc:	4605fd09 	strmi	pc, [r5], -r9, lsl #26
d0018f00:	f64fb1d0 			; <UNDEFINED> instruction: 0xf64fb1d0
d0018f04:	f64f03d0 			; <UNDEFINED> instruction: 0xf64f03d0
d0018f08:	46200190 			; <UNDEFINED> instruction: 0x46200190
d0018f0c:	bf182e01 	svclt	0x00182e01
d0018f10:	f7fb4619 			; <UNDEFINED> instruction: 0xf7fb4619
d0018f14:	f506fdcd 			; <UNDEFINED> instruction: 0xf506fdcd
d0018f18:	4620430f 	strtmi	r4, [r0], -pc, lsl #6
d0018f1c:	eb0433d0 	bl	0xd0125e64
d0018f20:	88990343 	ldmhi	r9, {r0, r1, r6, r8, r9}
d0018f24:	fdc4f7fb 	stc2l	7, cr15, [r4, #1004]	; 0x3ec
d0018f28:	f43f2e00 			; <UNDEFINED> instruction: 0xf43f2e00
d0018f2c:	3e02adb9 	mcrcc	13, 0, sl, cr2, cr9, {5}
d0018f30:	f63f2e01 			; <UNDEFINED> instruction: 0xf63f2e01
d0018f34:	e5b3ada7 	ldr	sl, [r3, #3495]!	; 0xda7
d0018f38:	2e083601 	cfmadd32cs	mvax0, mvfx3, mvfx8, mvfx1
d0018f3c:	6da3d1d9 	stfvsd	f5, [r3, #868]!	; 0x364
d0018f40:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0018f44:	f8dfad9f 			; <UNDEFINED> instruction: 0xf8dfad9f
d0018f48:	447b3694 	ldrbtmi	r3, [fp], #-1684	; 0xfffff96c
d0018f4c:	3916e9c4 	ldmdbcc	r6, {r2, r6, r7, r8, fp, sp, lr, pc}
d0018f50:	e9c49b06 	stmib	r4, {r1, r2, r8, r9, fp, ip, pc}^
d0018f54:	9b073718 	blls	0xd01e6bbc
d0018f58:	e66766a3 	strbt	r6, [r7], -r3, lsr #13
d0018f5c:	0f0af1b9 	svceq	0x000af1b9
d0018f60:	f1b9d097 			; <UNDEFINED> instruction: 0xf1b9d097
d0018f64:	e5aa0f01 	str	r0, [sl, #3841]!	; 0xf01
d0018f68:	46494652 			; <UNDEFINED> instruction: 0x46494652
d0018f6c:	f7f74620 			; <UNDEFINED> instruction: 0xf7f74620
d0018f70:	1e07fc3d 	mcrne	12, 0, pc, cr7, cr13, {1}	; <UNPREDICTABLE>
d0018f74:	80bff2c0 	adcshi	pc, pc, r0, asr #5
d0018f78:	093cf04f 	ldmdbeq	ip!, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d0018f7c:	4907fb09 	stmdbmi	r7, {r0, r3, r8, r9, fp, ip, sp, lr, pc}
d0018f80:	395ff509 	ldmdbcc	pc, {r0, r3, r8, sl, ip, sp, lr, pc}^	; <UNPREDICTABLE>
d0018f84:	a3ecf899 	mvnge	pc, #10027008	; 0x990000
d0018f88:	0f07f1ba 	svceq	0x0007f1ba
d0018f8c:	f8dfd163 			; <UNDEFINED> instruction: 0xf8dfd163
d0018f90:	215b2650 	cmpcs	fp, r0, asr r6
d0018f94:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d0018f98:	ffb2f7f9 			; <UNDEFINED> instruction: 0xffb2f7f9
d0018f9c:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0018fa0:	2201ad71 	andcs	sl, r1, #7232	; 0x1c40
d0018fa4:	46114620 	ldrmi	r4, [r1], -r0, lsr #12
d0018fa8:	f914f7fd 			; <UNDEFINED> instruction: 0xf914f7fd
d0018fac:	2634f8df 			; <UNDEFINED> instruction: 0x2634f8df
d0018fb0:	4620215d 			; <UNDEFINED> instruction: 0x4620215d
d0018fb4:	f7f9447a 			; <UNDEFINED> instruction: 0xf7f9447a
d0018fb8:	2800ffa3 	stmdacs	r0, {r0, r1, r5, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0018fbc:	ad62f43f 	cfstrdge	mvd15, [r2, #-252]!	; 0xffffff04
d0018fc0:	2101463a 	tstcs	r1, sl, lsr r6
d0018fc4:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0018fc8:	6ae7fddb 	bvs	0xcfa1873c
d0018fcc:	f0002f3d 			; <UNDEFINED> instruction: 0xf0002f3d
d0018fd0:	f46f8267 	vld1.16	{d24-d27}, [pc :128], r7
d0018fd4:	187b7192 	ldmdane	fp!, {r1, r4, r7, r8, ip, sp, lr}^
d0018fd8:	f2402b01 	vqdmulh.s<illegal width 8>	d18, d0, d1
d0018fdc:	f46f8261 	vld1.16	{d24-d27}, [pc :128], r1
d0018fe0:	18bb7294 	ldmne	fp!, {r2, r4, r7, r9, ip, sp, lr}
d0018fe4:	f2402b04 	vqdmulh.s<illegal width 8>	d18, d0, d4
d0018fe8:	f645825b 			; <UNDEFINED> instruction: 0xf645825b
d0018fec:	46204108 	strtmi	r4, [r0], -r8, lsl #2
d0018ff0:	fd5ef7fb 	ldc2l	7, cr15, [lr, #-1004]	; 0xfffffc14
d0018ff4:	f641e61a 			; <UNDEFINED> instruction: 0xf641e61a
d0018ff8:	46200108 	strtmi	r0, [r0], -r8, lsl #2
d0018ffc:	fd58f7fb 	ldc2l	7, cr15, [r8, #-1004]	; 0xfffffc14
d0019000:	4106f64b 	tstmi	r6, fp, asr #12	; <UNPREDICTABLE>
d0019004:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0019008:	f247fd53 	vmla.f32	<illegal reg q15.5>, <illegal reg q3.5>, <illegal reg q1.5>
d001900c:	46200108 	strtmi	r0, [r0], -r8, lsl #2
d0019010:	f7fb2502 			; <UNDEFINED> instruction: 0xf7fb2502
d0019014:	e609fd4d 	str	pc, [r9], -sp, asr #26
d0019018:	2108f641 	tstcs	r8, r1, asr #12	; <UNPREDICTABLE>
d001901c:	f244e7ed 	vabd.s8	q15, q10, <illegal reg q14.5>
d0019020:	e7ea0108 	strb	r0, [sl, r8, lsl #2]!
d0019024:	3108f244 	tstcc	r8, r4, asr #4	; <UNPREDICTABLE>
d0019028:	f244e7e7 	vabd.s8	q15, q10, <illegal reg q11.5>
d001902c:	e7e40148 	strb	r0, [r4, r8, asr #2]!
d0019030:	6102f244 	tstvs	r2, r4, asr #4	; <UNPREDICTABLE>
d0019034:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0019038:	f244fd3b 	vmla.f32	d31, d4, d27
d001903c:	46206108 	strtmi	r6, [r0], -r8, lsl #2
d0019040:	fd36f7fb 	ldc2	7, cr15, [r6, #-1004]!	; 0xfffffc14
d0019044:	0190f244 	orrseq	pc, r0, r4, asr #4
d0019048:	1310f244 	tstne	r0, #68, 4	; 0x40000004	; <UNPREDICTABLE>
d001904c:	7f96f5b7 	svcvc	0x0096f5b7
d0019050:	4619bf18 	sadd16mi	fp, r9, r8
d0019054:	f1bae7d1 			; <UNDEFINED> instruction: 0xf1bae7d1
d0019058:	463a0f0f 	ldrtmi	r0, [sl], -pc, lsl #30
d001905c:	0101f04f 	tsteq	r1, pc, asr #32	; <UNPREDICTABLE>
d0019060:	d1194620 	tstle	r9, r0, lsr #12
d0019064:	fd8cf7fb 	stc2	7, cr15, [ip, #1004]	; 0x3ec
d0019068:	6108f244 	tstvs	r8, r4, asr #4	; <UNPREDICTABLE>
d001906c:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0019070:	212efd1f 	msrcs	CPSR_fsx, pc, lsl sp
d0019074:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d0019078:	4605ff35 			; <UNDEFINED> instruction: 0x4605ff35
d001907c:	465bb120 	ldrbmi	fp, [fp], -r0, lsr #2
d0019080:	f8994632 			; <UNDEFINED> instruction: 0xf8994632
d0019084:	e6bc13ee 	ldrt	r1, [ip], lr, ror #7
d0019088:	2b006da3 	blcs	0xd003471c
d001908c:	acfaf47f 	cfldrdge	mvd15, [sl], #508	; 0x1fc
d0019090:	3554f8df 	ldrbcc	pc, [r4, #-2271]	; 0xfffff721	; <UNPREDICTABLE>
d0019094:	e66f447b 			; <UNDEFINED> instruction: 0xe66f447b
d0019098:	0f11f1ba 	svceq	0x0011f1ba
d001909c:	f7fbd116 			; <UNDEFINED> instruction: 0xf7fbd116
d00190a0:	f244fd6f 	vadd.f32	<illegal reg q15.5>, q2, <illegal reg q15.5>
d00190a4:	46206108 	strtmi	r6, [r0], -r8, lsl #2
d00190a8:	fd02f7fb 	stc2	7, cr15, [r2, #-1004]	; 0xfffffc14
d00190ac:	2b5b6ae3 	blcs	0xd16f3c40
d00190b0:	462bd104 	strtmi	sp, [fp], -r4, lsl #2
d00190b4:	f8994632 			; <UNDEFINED> instruction: 0xf8994632
d00190b8:	e6c613ee 	strb	r1, [r6], lr, ror #7
d00190bc:	2b006da3 	blcs	0xd0034750
d00190c0:	ace0f47f 	cfstrdge	mvd15, [r0], #508	; 0x1fc
d00190c4:	3524f8df 	strcc	pc, [r4, #-2271]!	; 0xfffff721
d00190c8:	e655447b 			; <UNDEFINED> instruction: 0xe655447b
d00190cc:	0f08f1ba 	svceq	0x0008f1ba
d00190d0:	f7fbd107 			; <UNDEFINED> instruction: 0xf7fbd107
d00190d4:	f244fd55 	vmla.f32	<illegal reg q15.5>, q2, <illegal reg q2.5>
d00190d8:	46206108 	strtmi	r6, [r0], -r8, lsl #2
d00190dc:	fce8f7fb 	stc2l	7, cr15, [r8], #1004	; 0x3ec
d00190e0:	f7fbe6d7 			; <UNDEFINED> instruction: 0xf7fbe6d7
d00190e4:	f646fd4d 			; <UNDEFINED> instruction: 0xf646fd4d
d00190e8:	46200108 	strtmi	r0, [r0], -r8, lsl #2
d00190ec:	fce0f7fb 	stc2l	7, cr15, [r0], #1004	; 0x3ec
d00190f0:	0f01f1ba 	svceq	0x0001f1ba
d00190f4:	f8dfe4e3 			; <UNDEFINED> instruction: 0xf8dfe4e3
d00190f8:	465124f8 			; <UNDEFINED> instruction: 0x465124f8
d00190fc:	447a4648 	ldrbtmi	r4, [sl], #-1608	; 0xfffff9b8
d0019100:	fc06f7f7 	stc2	7, cr15, [r6], {247}	; 0xf7
d0019104:	b1204605 			; <UNDEFINED> instruction: 0xb1204605
d0019108:	46204659 			; <UNDEFINED> instruction: 0x46204659
d001910c:	f8cdf7fc 			; <UNDEFINED> instruction: 0xf8cdf7fc
d0019110:	6da3e642 	stcvs	6, cr14, [r3, #264]!	; 0x108
d0019114:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0019118:	f8dfacb5 			; <UNDEFINED> instruction: 0xf8dfacb5
d001911c:	447b34d8 	ldrbtmi	r3, [fp], #-1240	; 0xfffffb28
d0019120:	2126e62a 			; <UNDEFINED> instruction: 0x2126e62a
d0019124:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d0019128:	2800fedd 	stmdacs	r0, {r0, r2, r3, r4, r6, r7, r9, sl, fp, ip, sp, lr, pc}
d001912c:	80a5f000 	adchi	pc, r5, r0
d0019130:	24c4f8df 	strbcs	pc, [r4], #2271	; 0x8df	; <UNPREDICTABLE>
d0019134:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d0019138:	6a674620 	bvs	0xd19ea9c0
d001913c:	f8d4447a 			; <UNDEFINED> instruction: 0xf8d4447a
d0019140:	f8948028 			; <UNDEFINED> instruction: 0xf8948028
d0019144:	f8d49030 			; <UNDEFINED> instruction: 0xf8d49030
d0019148:	e9d4a034 	ldmib	r4, {r2, r4, r5, sp, pc}^
d001914c:	f7f96b06 			; <UNDEFINED> instruction: 0xf7f96b06
d0019150:	b958fed7 	ldmdblt	r8, {r0, r1, r2, r4, r6, r7, r9, sl, fp, ip, sp, lr, pc}^
d0019154:	9a099b09 	bls	0xd027fd80
d0019158:	3244f8d3 	subcc	pc, r4, #13828096	; 0xd30000
d001915c:	f8c23b01 			; <UNDEFINED> instruction: 0xf8c23b01
d0019160:	b01d3244 	andslt	r3, sp, r4, asr #4
d0019164:	8b02ecbd 	blhi	0xd00d4460
d0019168:	8ff0e8bd 	svchi	0x00f0e8bd
d001916c:	465a4631 			; <UNDEFINED> instruction: 0x465a4631
d0019170:	f7f74620 			; <UNDEFINED> instruction: 0xf7f74620
d0019174:	1e01fb1b 	vmovne.32	d1[0], pc
d0019178:	81d8f280 	bicshi	pc, r8, r0, lsl #5
d001917c:	4631465a 			; <UNDEFINED> instruction: 0x4631465a
d0019180:	f7f74620 			; <UNDEFINED> instruction: 0xf7f74620
d0019184:	1e02fb33 	vmovne.16	d2[0], pc
d0019188:	263cdb70 			; <UNDEFINED> instruction: 0x263cdb70
d001918c:	4602fb06 	strmi	pc, [r2], -r6, lsl #22
d0019190:	365ff506 	ldrbcc	pc, [pc], -r6, lsl #10	; <UNPREDICTABLE>
d0019194:	b3f0f896 	mvnslt	pc, #9830400	; 0x960000
d0019198:	0f00f1bb 	svceq	0x0000f1bb
d001919c:	81e7f000 	mvnhi	pc, r0
d00191a0:	2b006da3 	blcs	0xd0034834
d00191a4:	ac6ef47f 	cfstrdge	mvd15, [lr], #-508	; 0xfffffe04
d00191a8:	3450f8df 	ldrbcc	pc, [r0], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d00191ac:	f8c4447b 			; <UNDEFINED> instruction: 0xf8c4447b
d00191b0:	e9c4a068 	stmib	r4, {r3, r5, r6, sp, pc}^
d00191b4:	e9c43716 	stmib	r4, {r1, r2, r4, r8, r9, sl, ip, sp}^
d00191b8:	e5378918 	ldr	r8, [r7, #-2328]!	; 0xfffff6e8
d00191bc:	d1052b0e 	tstle	r5, lr, lsl #22
d00191c0:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d00191c4:	f896fb4d 			; <UNDEFINED> instruction: 0xf896fb4d
d00191c8:	e5fb365a 	ldrb	r3, [fp, #1626]!	; 0x65a
d00191cc:	2b09b15b 	blcs	0xd0285740
d00191d0:	2b0ad009 	blcs	0xd02cd1fc
d00191d4:	6ae3d14a 	bvs	0xcf90d704
d00191d8:	d1432b5b 	cmple	r3, fp, asr fp
d00191dc:	4620465a 			; <UNDEFINED> instruction: 0x4620465a
d00191e0:	fc84f7fb 	stc2	7, cr15, [r4], {251}	; 0xfb
d00191e4:	4620e032 			; <UNDEFINED> instruction: 0x4620e032
d00191e8:	f7fc9106 			; <UNDEFINED> instruction: 0xf7fc9106
d00191ec:	2030fb39 	eorscs	pc, r0, r9, lsr fp	; <UNPREDICTABLE>
d00191f0:	6ae39906 	bvs	0xcf8ff610
d00191f4:	4101fb00 	tstmi	r1, r0, lsl #22	; <UNPREDICTABLE>
d00191f8:	f5012b5b 			; <UNDEFINED> instruction: 0xf5012b5b
d00191fc:	f8912190 			; <UNDEFINED> instruction: 0xf8912190
d0019200:	d1073659 	tstle	r7, r9, asr r6
d0019204:	d15b2b09 	cmple	fp, r9, lsl #22
d0019208:	21002201 	tstcs	r0, r1, lsl #4
d001920c:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0019210:	e485fb33 	str	pc, [r5], #2867	; 0xb33
d0019214:	d1532b09 	cmple	r3, r9, lsl #22
d0019218:	2b006da3 	blcs	0xd00348ac
d001921c:	ac32f47f 	cfldrsge	mvf15, [r2], #-508	; 0xfffffe04
d0019220:	447b4bf7 	ldrbtmi	r4, [fp], #-3063	; 0xfffff409
d0019224:	f011e7c3 			; <UNDEFINED> instruction: 0xf011e7c3
d0019228:	d11f0bf7 			; <UNDEFINED> instruction: 0xd11f0bf7
d001922c:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d0019230:	fca6f7fb 	stc2	7, cr15, [r6], #1004	; 0x3ec
d0019234:	6108f244 	tstvs	r8, r4, asr #4	; <UNPREDICTABLE>
d0019238:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d001923c:	6ae3fc39 	bvs	0xcf918328
d0019240:	f8962b5b 			; <UNDEFINED> instruction: 0xf8962b5b
d0019244:	d10433ec 	smlattle	r4, ip, r3, r3
d0019248:	d1392b08 	teqle	r9, r8, lsl #22
d001924c:	46592201 	ldrbmi	r2, [r9], -r1, lsl #4
d0019250:	2b08e7dc 	blcs	0xd02531c8
d0019254:	6da3d134 	stfvsd	f5, [r3, #208]!	; 0xd0
d0019258:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001925c:	4be9ac13 	blmi	0xcfa842b0
d0019260:	e7a4447b 			; <UNDEFINED> instruction: 0xe7a4447b
d0019264:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0019268:	e59ffafb 	ldr	pc, [pc, #2811]	; 0xd0019d6b
d001926c:	2b006da3 	blcs	0xd0034900
d0019270:	ac08f47f 	cfstrsge	mvf15, [r8], {127}	; 0x7f
d0019274:	447b4be4 	ldrbtmi	r4, [fp], #-3044	; 0xfffff41c
d0019278:	212ae799 			; <UNDEFINED> instruction: 0x212ae799
d001927c:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d0019280:	2800fe31 	stmdacs	r0, {r0, r4, r5, r9, sl, fp, ip, sp, lr, pc}
d0019284:	2100d061 	tstcs	r0, r1, rrx
d0019288:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d001928c:	2807fbd3 	stmdacs	r7, {r0, r1, r4, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d0019290:	d1174605 	tstle	r7, r5, lsl #12
d0019294:	213db17e 	teqcs	sp, lr, ror r1
d0019298:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d001929c:	b150fe23 	cmplt	r0, r3, lsr #28	; <UNPREDICTABLE>
d00192a0:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d00192a4:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d00192a8:	2204fc03 	andcs	pc, r4, #768	; 0x300
d00192ac:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d00192b0:	ff90f7fc 			; <UNDEFINED> instruction: 0xff90f7fc
d00192b4:	f44fe01a 	vst4.8	{d30-d33}, [pc :64], sl
d00192b8:	462041d0 			; <UNDEFINED> instruction: 0x462041d0
d00192bc:	fbf8f7fb 	blx	0xcfe572b2
d00192c0:	e4b32504 	ldrt	r2, [r3], #1284	; 0x504
d00192c4:	d1222805 			; <UNDEFINED> instruction: 0xd1222805
d00192c8:	f8d39b09 			; <UNDEFINED> instruction: 0xf8d39b09
d00192cc:	b1ae5248 			; <UNDEFINED> instruction: 0xb1ae5248
d00192d0:	4620213d 			; <UNDEFINED> instruction: 0x4620213d
d00192d4:	fe06f7f9 	mcr2	7, 0, pc, cr6, cr9, {7}	; <UNPREDICTABLE>
d00192d8:	f24bb180 	vrhadd.s8	d27, d27, d0
d00192dc:	46204103 	strtmi	r4, [r0], -r3, lsl #2
d00192e0:	fbe6f7fb 	blx	0xcf9d72d6
d00192e4:	46204629 	strtmi	r4, [r0], -r9, lsr #12
d00192e8:	fd9af7fe 	ldc2	7, cr15, [sl, #1016]	; 0x3f8
d00192ec:	4106f64b 	tstmi	r6, fp, asr #12	; <UNPREDICTABLE>
d00192f0:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d00192f4:	f246fbdd 	vpadd.i8	<illegal reg q15.5>, q11, <illegal reg q6.5>
d00192f8:	e6880108 	str	r0, [r8], r8, lsl #2
d00192fc:	41d0f44f 	bicsmi	pc, r0, pc, asr #8
d0019300:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0019304:	9b09fbd5 	blls	0xd0298260
d0019308:	5248f8c3 	subpl	pc, r8, #12779520	; 0xc30000
d001930c:	2804e544 	stmdacs	r4, {r2, r6, r8, sl, sp, lr, pc}
d0019310:	6da3d006 	stcvs	0, cr13, [r3, #24]!
d0019314:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0019318:	4bbcac89 	blmi	0xcef44544
d001931c:	e52b447b 	str	r4, [fp, #-1147]!	; 0xfffffb85
d0019320:	213db166 	teqcs	sp, r6, ror #2
d0019324:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d0019328:	b138fddd 	teqlt	r8, sp	; <illegal shifter operand>	; <UNPREDICTABLE>
d001932c:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d0019330:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0019334:	2201fbbd 	andcs	pc, r1, #193536	; 0x2f400
d0019338:	e7b84611 			; <UNDEFINED> instruction: 0xe7b84611
d001933c:	41d0f44f 	bicsmi	pc, r0, pc, asr #8
d0019340:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0019344:	f7fffbb5 			; <UNDEFINED> instruction: 0xf7fffbb5
d0019348:	2128bb9d 			; <UNDEFINED> instruction: 0x2128bb9d
d001934c:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d0019350:	2800fdc9 	stmdacs	r0, {r0, r3, r6, r7, r8, sl, fp, ip, sp, lr, pc}
d0019354:	6ae3d052 	bvs	0xcf90d4a4
d0019358:	d1322b2a 	teqle	r2, sl, lsr #22
d001935c:	f2406ce2 	sha1c.32	q11, q8, q9
d0019360:	429a1301 	addsmi	r1, sl, #67108864	; 0x4000000
d0019364:	6be2d12d 	blvs	0xcf8cd820
d0019368:	6ba14620 	blvs	0xce86abf0
d001936c:	fa1ef7f7 	blx	0xd07d7350
d0019370:	db261e05 	blle	0xd09a0b8c
d0019374:	fb032330 	blx	0xd00e203e
d0019378:	f5034305 			; <UNDEFINED> instruction: 0xf5034305
d001937c:	f8932390 			; <UNDEFINED> instruction: 0xf8932390
d0019380:	2b0c3659 	blcs	0xd0326cec
d0019384:	4620d11d 			; <UNDEFINED> instruction: 0x4620d11d
d0019388:	fd8cf7f9 	stc2	7, cr15, [ip, #996]	; 0x3e4
d001938c:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d0019390:	4a9ffd89 	bmi	0xce8189bc
d0019394:	46202129 	strtmi	r2, [r0], -r9, lsr #2
d0019398:	f7f9447a 			; <UNDEFINED> instruction: 0xf7f9447a
d001939c:	2800fdb1 	stmdacs	r0, {r0, r4, r5, r7, r8, sl, fp, ip, sp, lr, pc}
d00193a0:	ab70f43f 	blge	0xd1c564a4
d00193a4:	21284a9b 			; <UNDEFINED> instruction: 0x21284a9b
d00193a8:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d00193ac:	fda8f7f9 	stc2	7, cr15, [r8, #996]!	; 0x3e4
d00193b0:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d00193b4:	4629ab67 	strtmi	sl, [r9], -r7, ror #22
d00193b8:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d00193bc:	f7ffff65 			; <UNDEFINED> instruction: 0xf7ffff65
d00193c0:	2200bbaf 	andcs	fp, r0, #179200	; 0x2bc00
d00193c4:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d00193c8:	ff04f7fc 			; <UNDEFINED> instruction: 0xff04f7fc
d00193cc:	46054a92 			; <UNDEFINED> instruction: 0x46054a92
d00193d0:	447a2129 	ldrbtmi	r2, [sl], #-297	; 0xfffffed7
d00193d4:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d00193d8:	2d03fd93 	stccs	13, cr15, [r3, #-588]	; 0xfffffdb4
d00193dc:	ac7cf47f 	cfldrdge	mvd15, [ip], #-508	; 0xfffffe04
d00193e0:	7191f44f 	orrsvc	pc, r1, pc, asr #8
d00193e4:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d00193e8:	2800fd7d 	stmdacs	r0, {r0, r2, r3, r4, r5, r6, r8, sl, fp, ip, sp, lr, pc}
d00193ec:	acd4f43f 	cfldrdge	mvd15, [r4], {63}	; 0x3f
d00193f0:	23009909 	movwcs	r9, #2313	; 0x909
d00193f4:	f8d14632 			; <UNDEFINED> instruction: 0xf8d14632
d00193f8:	e5021248 	str	r1, [r2, #-584]	; 0xfffffdb8
d00193fc:	4620212b 	strtmi	r2, [r0], -fp, lsr #2
d0019400:	fd70f7f9 	ldc2l	7, cr15, [r0, #-996]!	; 0xfffffc1c
d0019404:	2100b168 	tstcs	r0, r8, ror #2
d0019408:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d001940c:	2802fb13 	stmdacs	r2, {r0, r1, r4, r8, r9, fp, ip, sp, lr, pc}
d0019410:	d1204605 			; <UNDEFINED> instruction: 0xd1204605
d0019414:	2b006da3 	blcs	0xd0034aa8
d0019418:	ac08f47f 	cfstrsge	mvf15, [r8], {127}	; 0x7f
d001941c:	447b4b7f 	ldrbtmi	r4, [fp], #-2943	; 0xfffff481
d0019420:	212de4aa 			; <UNDEFINED> instruction: 0x212de4aa
d0019424:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d0019428:	2800fd5d 	stmdacs	r0, {r0, r2, r3, r4, r6, r8, sl, fp, ip, sp, lr, pc}
d001942c:	2121d1eb 			; <UNDEFINED> instruction: 0x2121d1eb
d0019430:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d0019434:	2800fd57 	stmdacs	r0, {r0, r1, r2, r4, r6, r8, sl, fp, ip, sp, lr, pc}
d0019438:	217ed1e5 	cmncs	lr, r5, ror #3
d001943c:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d0019440:	4605fd51 			; <UNDEFINED> instruction: 0x4605fd51
d0019444:	d1de2800 	bicsle	r2, lr, r0, lsl #16
d0019448:	46204975 			; <UNDEFINED> instruction: 0x46204975
d001944c:	f7f64479 			; <UNDEFINED> instruction: 0xf7f64479
d0019450:	f7fffefd 			; <UNDEFINED> instruction: 0xf7fffefd
d0019454:	2803bbeb 	stmdacs	r3, {r0, r1, r3, r5, r6, r7, r8, r9, fp, ip, sp, pc}
d0019458:	2f21d108 	svccs	0x0021d108
d001945c:	6da3d013 	stcvs	0, cr13, [r3, #76]!	; 0x4c
d0019460:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0019464:	4b6fac99 	blmi	0xd1c046d0
d0019468:	e485447b 	str	r4, [r5], #1147	; 0x47b
d001946c:	d1022f2d 	tstle	r2, sp, lsr #30
d0019470:	2140f244 	cmpcs	r0, r4, asr #4	; <UNPREDICTABLE>
d0019474:	2f7ee5bb 	svccs	0x007ee5bb
d0019478:	f244d102 	vrhadd.s8	d29, d4, d2
d001947c:	e5b631c0 	ldr	r3, [r6, #448]!	; 0x1c0
d0019480:	f47f2f21 			; <UNDEFINED> instruction: 0xf47f2f21
d0019484:	4620abd3 			; <UNDEFINED> instruction: 0x4620abd3
d0019488:	5120f44f 	msrpl	CPSR_, pc, asr #8
d001948c:	fb10f7fb 	blx	0xd0457482
d0019490:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d0019494:	fbd7f7fb 	blx	0xcf61748a
d0019498:	baf4f7ff 	blt	0xcfd5749c
d001949c:	e6602000 	strbt	r2, [r0], -r0
d00194a0:	f43f2e00 			; <UNDEFINED> instruction: 0xf43f2e00
d00194a4:	4620ada2 	strtmi	sl, [r0], -r2, lsr #27
d00194a8:	fcfcf7f9 	ldc2l	7, cr15, [ip], #996	; 0x3e4
d00194ac:	0108f641 	tsteq	r8, r1, asr #12	; <UNPREDICTABLE>
d00194b0:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d00194b4:	f24bfafd 	vpmin.s8	<illegal reg q15.5>, <illegal reg q13.5>, <illegal reg q14.5>
d00194b8:	46204103 	strtmi	r4, [r0], -r3, lsl #2
d00194bc:	faf8f7fb 	blx	0xcfe574b0
d00194c0:	d0092f3d 	andle	r2, r9, sp, lsr pc
d00194c4:	41f0f44f 	mvnsmi	pc, pc, asr #8
d00194c8:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d00194cc:	f24bfaf1 	vpmin.s8	<illegal reg q15.5>, <illegal reg q13.5>, <illegal reg q8.5>
d00194d0:	46204103 	strtmi	r4, [r0], -r3, lsl #2
d00194d4:	faecf7fb 	blx	0xcfb574c8
d00194d8:	46202201 	strtmi	r2, [r0], -r1, lsl #4
d00194dc:	f7fc4611 			; <UNDEFINED> instruction: 0xf7fc4611
d00194e0:	2f3dfe79 	svccs	0x003dfe79
d00194e4:	ad8cf43f 	cfstrsge	mvf15, [ip, #252]	; 0xfc
d00194e8:	4106f64b 	tstmi	r6, fp, asr #12	; <UNPREDICTABLE>
d00194ec:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d00194f0:	f46ffadf 	vld1.64	{d31-d32}, [pc :64]
d00194f4:	18fb7392 	ldmne	fp!, {r1, r4, r7, r8, r9, ip, sp, lr}^
d00194f8:	f63f2b08 			; <UNDEFINED> instruction: 0xf63f2b08
d00194fc:	a202ad81 	andge	sl, r2, #8256	; 0x2040
d0019500:	3023f852 	eorcc	pc, r3, r2, asr r8	; <UNPREDICTABLE>
d0019504:	4710441a 			; <UNDEFINED> instruction: 0x4710441a
d0019508:	fffffaef 			; <UNDEFINED> instruction: 0xfffffaef
d001950c:	fffffb11 			; <UNDEFINED> instruction: 0xfffffb11
d0019510:	fffffaf9 			; <UNDEFINED> instruction: 0xfffffaf9
d0019514:	fffffaf9 			; <UNDEFINED> instruction: 0xfffffaf9
d0019518:	fffffb17 			; <UNDEFINED> instruction: 0xfffffb17
d001951c:	fffffb1d 			; <UNDEFINED> instruction: 0xfffffb1d
d0019520:	fffffb23 			; <UNDEFINED> instruction: 0xfffffb23
d0019524:	fffffb29 			; <UNDEFINED> instruction: 0xfffffb29
d0019528:	fffffb29 			; <UNDEFINED> instruction: 0xfffffb29
d001952c:	fb062630 	blx	0xd01a2df6
d0019530:	f5064601 			; <UNDEFINED> instruction: 0xf5064601
d0019534:	f8962690 			; <UNDEFINED> instruction: 0xf8962690
d0019538:	f1bbb664 			; <UNDEFINED> instruction: 0xf1bbb664
d001953c:	f47f0f00 			; <UNDEFINED> instruction: 0xf47f0f00
d0019540:	f896ae2f 			; <UNDEFINED> instruction: 0xf896ae2f
d0019544:	2b0d3659 	blcs	0xd0366eb0
d0019548:	ae38f47f 	mrcge	4, 1, APSR_nzcv, cr8, cr15, {3}
d001954c:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0019550:	4a35f987 	bmi	0xd0d97b74
d0019554:	4620212e 	strtmi	r2, [r0], -lr, lsr #2
d0019558:	f7f9447a 			; <UNDEFINED> instruction: 0xf7f9447a
d001955c:	2800fcd1 	stmdacs	r0, {r0, r4, r6, r7, sl, fp, ip, sp, lr, pc}
d0019560:	aa90f43f 	bge	0xce456664
d0019564:	465a2301 	ldrbmi	r2, [sl], -r1, lsl #6
d0019568:	165af896 			; <UNDEFINED> instruction: 0x165af896
d001956c:	f896e449 			; <UNDEFINED> instruction: 0xf896e449
d0019570:	290f13ec 	stmdbcs	pc, {r2, r3, r5, r6, r7, r8, r9, ip}	; <UNPREDICTABLE>
d0019574:	ae57f47f 	mrcge	4, 2, APSR_nzcv, cr7, cr15, {3}
d0019578:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d001957c:	fb00f7fb 	blx	0xd0057572
d0019580:	6108f244 	tstvs	r8, r4, asr #4	; <UNPREDICTABLE>
d0019584:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0019588:	4a28fa93 	bmi	0xd0a57fdc
d001958c:	4620212e 	strtmi	r2, [r0], -lr, lsr #2
d0019590:	f7f9447a 			; <UNDEFINED> instruction: 0xf7f9447a
d0019594:	2800fcb5 	stmdacs	r0, {r0, r2, r4, r5, r7, sl, fp, ip, sp, lr, pc}
d0019598:	aa74f43f 	bge	0xd1d5669c
d001959c:	465a2301 	ldrbmi	r2, [sl], -r1, lsl #6
d00195a0:	13eef896 	mvnne	pc, #9830400	; 0x960000
d00195a4:	bf00e42d 	svclt	0x0000e42d
d00195a8:	ffffd540 			; <UNDEFINED> instruction: 0xffffd540
d00195ac:	fffffbdc 			; <UNDEFINED> instruction: 0xfffffbdc
d00195b0:	fffffb9b 			; <UNDEFINED> instruction: 0xfffffb9b
d00195b4:	fffffb7f 			; <UNDEFINED> instruction: 0xfffffb7f
d00195b8:	fffffb77 			; <UNDEFINED> instruction: 0xfffffb77
d00195bc:	fffffb39 			; <UNDEFINED> instruction: 0xfffffb39
d00195c0:	fffffb44 			; <UNDEFINED> instruction: 0xfffffb44
d00195c4:	fffffad3 			; <UNDEFINED> instruction: 0xfffffad3
d00195c8:	fffff9fc 			; <UNDEFINED> instruction: 0xfffff9fc
d00195cc:	fffff995 			; <UNDEFINED> instruction: 0xfffff995
d00195d0:	fffff949 			; <UNDEFINED> instruction: 0xfffff949
d00195d4:	fffff922 			; <UNDEFINED> instruction: 0xfffff922
d00195d8:	000098e8 	andeq	r9, r0, r8, ror #17
d00195dc:	fffff8cb 			; <UNDEFINED> instruction: 0xfffff8cb
d00195e0:	fffff89a 			; <UNDEFINED> instruction: 0xfffff89a
d00195e4:	fffff8a8 			; <UNDEFINED> instruction: 0xfffff8a8
d00195e8:	fffff717 			; <UNDEFINED> instruction: 0xfffff717
d00195ec:	fffff701 			; <UNDEFINED> instruction: 0xfffff701
d00195f0:	ffffc1b0 			; <UNDEFINED> instruction: 0xffffc1b0
d00195f4:	fffff762 			; <UNDEFINED> instruction: 0xfffff762
d00195f8:	fffff765 			; <UNDEFINED> instruction: 0xfffff765
d00195fc:	fffff711 			; <UNDEFINED> instruction: 0xfffff711
d0019600:	fffff6fc 			; <UNDEFINED> instruction: 0xfffff6fc
d0019604:	fffff6be 			; <UNDEFINED> instruction: 0xfffff6be
d0019608:	fffff6d7 			; <UNDEFINED> instruction: 0xfffff6d7
d001960c:	fffff667 			; <UNDEFINED> instruction: 0xfffff667
d0019610:	fffff61e 			; <UNDEFINED> instruction: 0xfffff61e
d0019614:	fffff633 			; <UNDEFINED> instruction: 0xfffff633
d0019618:	fffff632 			; <UNDEFINED> instruction: 0xfffff632
d001961c:	ffffcbc8 			; <UNDEFINED> instruction: 0xffffcbc8
d0019620:	fffff5c5 			; <UNDEFINED> instruction: 0xfffff5c5
d0019624:	ffffcba4 			; <UNDEFINED> instruction: 0xffffcba4
d0019628:	fffff39b 			; <UNDEFINED> instruction: 0xfffff39b
d001962c:	fffff363 			; <UNDEFINED> instruction: 0xfffff363

Disassembly of section .text.condition.constprop.0:

d001966c <.text.condition.constprop.0>:
d001966c:	4c0ab510 	cfstr32mi	mvfx11, [sl], {16}
d0019670:	4a0a2128 	bmi	0xd02a1b18
d0019674:	447a447c 	ldrbtmi	r4, [sl], #-1148	; 0xfffffb84
d0019678:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d001967c:	2202fc41 	andcs	pc, r2, #16640	; 0x4100
d0019680:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d0019684:	fda6f7fc 	stc2	7, cr15, [r6, #1008]!	; 0x3f0
d0019688:	46204a05 	strtmi	r4, [r0], -r5, lsl #20
d001968c:	447a2129 	ldrbtmi	r2, [sl], #-297	; 0xfffffed7
d0019690:	4010e8bd 			; <UNDEFINED> instruction: 0x4010e8bd
d0019694:	bc34f7f9 	ldclt	7, cr15, [r4], #-996	; 0xfffffc1c
d0019698:	0000e420 	andeq	lr, r0, r0, lsr #8
d001969c:	ffffffb6 			; <UNDEFINED> instruction: 0xffffffb6
d00196a0:	ffffffbc 			; <UNDEFINED> instruction: 0xffffffbc

Disassembly of section .text.simple_expression.constprop.0:

d0019844 <.text.simple_expression.constprop.0>:
d0019844:	3434f8df 	ldrtcc	pc, [r4], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d0019848:	6cdb447b 	cfldrdvs	mvd4, [fp], {123}	; 0x7b
d001984c:	e92d2b3d 	push	{r0, r2, r3, r4, r5, r8, r9, fp, sp}
d0019850:	b0854ff0 	strdlt	r4, [r5], r0
d0019854:	f46fd01f 	vld4.8	{d29-d32}, [pc :64]
d0019858:	191a7492 	ldmdbne	sl, {r1, r4, r7, sl, ip, sp, lr}
d001985c:	d91a2a01 	ldmdble	sl, {r0, r9, fp, sp}
d0019860:	7094f46f 	addsvc	pc, r4, pc, ror #8
d0019864:	2b044403 	blcs	0xd012a878
d0019868:	2300bf8c 	movwcs	fp, #3980	; 0xf8c
d001986c:	f8df2301 			; <UNDEFINED> instruction: 0xf8df2301
d0019870:	93004410 	movwls	r4, #1040	; 0x410
d0019874:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d0019878:	6ae2447c 	bvs	0xcf8aaa70
d001987c:	d101429a 			; <UNDEFINED> instruction: 0xd101429a
d0019880:	b9539b00 	ldmdblt	r3, {r8, r9, fp, ip, pc}^
d0019884:	220348ff 	andcs	r4, r3, #16711680	; 0xff0000
d0019888:	44782101 	ldrbtmi	r2, [r8], #-257	; 0xfffffeff
d001988c:	e8bdb005 	pop	{r0, r2, ip, sp, pc}
d0019890:	f7fc4ff0 			; <UNDEFINED> instruction: 0xf7fc4ff0
d0019894:	2301bc9f 	movwcs	fp, #7327	; 0x1c9f
d0019898:	e9d4e7e9 	ldmib	r4, {r0, r3, r5, r6, r7, r8, r9, sl, sp, lr, pc}^
d001989c:	6b631206 	blvs	0xd18de0bc
d00198a0:	92024620 	andls	r4, r2, #32, 12	; 0x2000000
d00198a4:	91019303 	tstls	r1, r3, lsl #6
d00198a8:	f8d46a67 			; <UNDEFINED> instruction: 0xf8d46a67
d00198ac:	f8948028 			; <UNDEFINED> instruction: 0xf8948028
d00198b0:	f7f69030 			; <UNDEFINED> instruction: 0xf7f69030
d00198b4:	a901ff7b 	stmdbge	r1, {r0, r1, r3, r4, r5, r6, r8, r9, sl, fp, ip, sp, lr, pc}
d00198b8:	c90e1e05 	stmdbgt	lr, {r0, r2, r9, sl, fp, ip}
d00198bc:	81cff280 	bichi	pc, pc, r0, lsl #5
d00198c0:	93014620 	movwls	r4, #5664	; 0x1620
d00198c4:	ff92f7f6 			; <UNDEFINED> instruction: 0xff92f7f6
d00198c8:	0a00f1b0 	beq	0xd0055f90
d00198cc:	db159b01 	blle	0xd05804d8
d00198d0:	fb02223c 	blx	0xd00a21ca
d00198d4:	f504440a 			; <UNDEFINED> instruction: 0xf504440a
d00198d8:	f894345f 			; <UNDEFINED> instruction: 0xf894345f
d00198dc:	b1ba23f0 			; <UNDEFINED> instruction: 0xb1ba23f0
d00198e0:	447a4ae9 	ldrbtmi	r4, [sl], #-2793	; 0xfffff517
d00198e4:	b9316d91 	ldmdblt	r1!, {r0, r4, r7, r8, sl, fp, sp, lr}
d00198e8:	447949e8 	ldrbtmi	r4, [r9], #-2536	; 0xfffff618
d00198ec:	e9c26693 	stmib	r2, {r0, r1, r4, r7, r9, sl, sp, lr}^
d00198f0:	e9c21716 	stmib	r2, {r1, r2, r4, r8, r9, sl, ip}^
d00198f4:	b0058918 	andlt	r8, r5, r8, lsl r9
d00198f8:	8ff0e8bd 	svchi	0x00f0e8bd
d00198fc:	2a006da2 	bcs	0xd0034f8c
d0019900:	4ae3d1f9 	bmi	0xcf90e0ec
d0019904:	e9c4447a 	stmib	r4, {r1, r3, r4, r5, r6, sl, lr}^
d0019908:	e9c42716 	stmib	r4, {r1, r2, r4, r8, r9, sl, sp}^
d001990c:	e01a8918 	ands	r8, sl, r8, lsl r9
d0019910:	63ecf894 	mvnvs	pc, #148, 16	; 0x940000
d0019914:	0202f026 	andeq	pc, r2, #38	; 0x26
d0019918:	d15c2a0d 	cmple	ip, sp, lsl #20
d001991c:	93004cdd 	movwls	r4, #3293	; 0xcdd
d0019920:	4620447c 			; <UNDEFINED> instruction: 0x4620447c
d0019924:	fabef7f9 	blx	0xcefd7910
d0019928:	4620213d 			; <UNDEFINED> instruction: 0x4620213d
d001992c:	fadaf7f9 	blx	0xcf6d7918
d0019930:	6da2b958 			; <UNDEFINED> instruction: 0x6da2b958
d0019934:	d1de2a00 	bicsle	r2, lr, r0, lsl #20
d0019938:	9b004ad7 	blls	0xd002c49c
d001993c:	e9c4447a 	stmib	r4, {r1, r3, r4, r5, r6, sl, lr}^
d0019940:	e9c48918 	stmib	r4, {r3, r4, r8, fp, pc}^
d0019944:	66a32716 	ssatvs	r2, #4, r6, lsl #14
d0019948:	2d00e7d5 	stccs	7, cr14, [r0, #-852]	; 0xfffffcac
d001994c:	bfac48d3 	svclt	0x00ac48d3
d0019950:	233c2330 	teqcs	ip, #48, 6	; 0xc0000000
d0019954:	bfaa4478 	svclt	0x00aa4478
d0019958:	4405fb03 	strmi	pc, [r5], #-2819	; 0xfffff4fd
d001995c:	440afb03 	strmi	pc, [sl], #-2819	; 0xfffff4fd
d0019960:	2490f504 	ldrcs	pc, [r0], #1284	; 0x504
d0019964:	bfb69000 	svclt	0x00b69000
d0019968:	345ff504 	ldrbcc	pc, [pc], #-1284	; 0xd0019970	; <UNPREDICTABLE>
d001996c:	465af894 			; <UNDEFINED> instruction: 0x465af894
d0019970:	43eef894 	mvnmi	pc, #148, 16	; 0x940000
d0019974:	f7fd4621 			; <UNDEFINED> instruction: 0xf7fd4621
d0019978:	9800fdfd 	stmdals	r0, {r0, r2, r3, r4, r5, r6, r7, r8, sl, fp, ip, sp, lr, pc}
d001997c:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d0019980:	f896f7fb 			; <UNDEFINED> instruction: 0xf896f7fb
d0019984:	98002d00 	stmdals	r0, {r8, sl, fp, sp}
d0019988:	4629db1a 			; <UNDEFINED> instruction: 0x4629db1a
d001998c:	ff68f7fb 			; <UNDEFINED> instruction: 0xff68f7fb
d0019990:	f24448c3 	vadd.i8	q10, q10, <illegal reg q1.5>
d0019994:	44786101 	ldrbtmi	r6, [r8], #-257	; 0xfffffeff
d0019998:	f7fb4605 			; <UNDEFINED> instruction: 0xf7fb4605
d001999c:	f64bf889 			; <UNDEFINED> instruction: 0xf64bf889
d00199a0:	46284105 	strtmi	r4, [r8], -r5, lsl #2
d00199a4:	f884f7fb 			; <UNDEFINED> instruction: 0xf884f7fb
d00199a8:	701af44f 	andsvc	pc, sl, pc, asr #8
d00199ac:	5004fb00 	andpl	pc, r4, r0, lsl #22
d00199b0:	3068f500 	rsbcc	pc, r8, r0, lsl #10
d00199b4:	b0058d00 	andlt	r8, r5, r0, lsl #26
d00199b8:	4ff0e8bd 	svcmi	0x00f0e8bd
d00199bc:	bbf8f7fb 	bllt	0xcfe579b0
d00199c0:	21014652 	tstcs	r1, r2, asr r6
d00199c4:	f7fb9000 			; <UNDEFINED> instruction: 0xf7fb9000
d00199c8:	f244f8db 	vtst.8	<illegal reg q15.5>, q10, <illegal reg q5.5>
d00199cc:	98006108 	stmdals	r0, {r3, r8, sp, lr}
d00199d0:	f86ef7fb 			; <UNDEFINED> instruction: 0xf86ef7fb
d00199d4:	1ff2e7dc 	svcne	0x00f2e7dc
d00199d8:	d9032a02 	stmdble	r3, {r1, r9, fp, sp}
d00199dc:	0210f1a6 	andseq	pc, r0, #-2147483607	; 0x80000029
d00199e0:	d8072a01 	stmdale	r7, {r0, r9, fp, sp}
d00199e4:	447a4aaf 	ldrbtmi	r4, [sl], #-2735	; 0xfffff551
d00199e8:	29006d91 	stmdbcs	r0, {r0, r4, r7, r8, sl, fp, sp, lr}
d00199ec:	49aed183 	stmibmi	lr!, {r0, r1, r7, r8, ip, lr, pc}
d00199f0:	e77b4479 			; <UNDEFINED> instruction: 0xe77b4479
d00199f4:	29091eb1 	stmdbcs	r9, {r0, r4, r5, r7, r9, sl, fp, ip}
d00199f8:	f240d80d 	vadd.i8	d29, d0, d13
d00199fc:	40ca2215 	sbcmi	r2, sl, r5, lsl r2
d0019a00:	d50807d1 	strle	r0, [r8, #-2001]	; 0xfffff82f
d0019a04:	447a4aa9 	ldrbtmi	r4, [sl], #-2729	; 0xfffff557
d0019a08:	29006d91 	stmdbcs	r0, {r0, r4, r7, r8, sl, fp, sp, lr}
d0019a0c:	af73f47f 	svcge	0x0073f47f
d0019a10:	447949a7 	ldrbtmi	r4, [r9], #-2471	; 0xfffff659
d0019a14:	4ca7e76a 	stcmi	7, cr14, [r7], #424	; 0x1a8
d0019a18:	447c9301 	ldrbtmi	r9, [ip], #-769	; 0xfffffcff
d0019a1c:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d0019a20:	4620fa41 	strtmi	pc, [r0], -r1, asr #20
d0019a24:	b02cf8d4 	ldrdlt	pc, [ip], -r4	; <UNPREDICTABLE>
d0019a28:	fa3cf7f9 	blx	0xd0f57a14
d0019a2c:	9b012e0c 	blls	0xd0065264
d0019a30:	f1bbd11a 			; <UNDEFINED> instruction: 0xf1bbd11a
d0019a34:	d0060f3d 	andle	r0, r6, sp, lsr pc
d0019a38:	2a006da2 	bcs	0xd00350c8
d0019a3c:	af5bf47f 	svcge	0x005bf47f
d0019a40:	447a4a9d 	ldrbtmi	r4, [sl], #-2717	; 0xfffff563
d0019a44:	2030e75f 	eorscs	lr, r0, pc, asr r7
d0019a48:	4005fb00 	andmi	pc, r5, r0, lsl #22
d0019a4c:	2090f500 	addscs	pc, r0, r0, lsl #10
d0019a50:	605bf200 	subsvs	pc, fp, r0, lsl #4
d0019a54:	fcacf7fb 	stc2	7, cr15, [ip], #1004	; 0x3ec
d0019a58:	46292200 	strtmi	r2, [r9], -r0, lsl #4
d0019a5c:	b0054620 	andlt	r4, r5, r0, lsr #12
d0019a60:	4ff0e8bd 	svcmi	0x00f0e8bd
d0019a64:	b85df7fb 	ldmdalt	sp, {r0, r1, r3, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}^
d0019a68:	d10d2e13 	tstle	sp, r3, lsl lr
d0019a6c:	0f3df1bb 	svceq	0x003df1bb
d0019a70:	6da2d006 	stcvs	0, cr13, [r2, #24]!
d0019a74:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0019a78:	4a90af3e 	bmi	0xce445778
d0019a7c:	e742447a 	smlsldx	r4, r2, sl, r4
d0019a80:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0019a84:	e7e7ff33 			; <UNDEFINED> instruction: 0xe7e7ff33
d0019a88:	d1142e12 	tstle	r4, r2, lsl lr
d0019a8c:	0f3df1bb 	svceq	0x003df1bb
d0019a90:	6da2d006 	stcvs	0, cr13, [r2, #24]!
d0019a94:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0019a98:	4a89af2e 	bmi	0xce285758
d0019a9c:	e732447a 			; <UNDEFINED> instruction: 0xe732447a
d0019aa0:	46202330 			; <UNDEFINED> instruction: 0x46202330
d0019aa4:	4305fb03 	movwmi	pc, #23299	; 0x5b03	; <UNPREDICTABLE>
d0019aa8:	2390f503 	orrscs	pc, r0, #12582912	; 0xc00000
d0019aac:	165af893 			; <UNDEFINED> instruction: 0x165af893
d0019ab0:	f9bcf7fc 			; <UNDEFINED> instruction: 0xf9bcf7fc
d0019ab4:	2e0ee7d0 	mcrcs	7, 0, lr, cr14, cr0, {6}
d0019ab8:	f1bbd114 			; <UNDEFINED> instruction: 0xf1bbd114
d0019abc:	d0060f3d 	andle	r0, r6, sp, lsr pc
d0019ac0:	2a006da2 	bcs	0xd0035150
d0019ac4:	af17f47f 	svcge	0x0017f47f
d0019ac8:	447a4a7e 	ldrbtmi	r4, [sl], #-2686	; 0xfffff582
d0019acc:	2330e71b 	teqcs	r0, #7077888	; 0x6c0000
d0019ad0:	fb034620 	blx	0xd00eb35a
d0019ad4:	f5034305 			; <UNDEFINED> instruction: 0xf5034305
d0019ad8:	f8932390 			; <UNDEFINED> instruction: 0xf8932390
d0019adc:	f7fe165a 			; <UNDEFINED> instruction: 0xf7fe165a
d0019ae0:	e7b9f99f 			; <UNDEFINED> instruction: 0xe7b9f99f
d0019ae4:	0f3df1bb 	svceq	0x003df1bb
d0019ae8:	80b3f000 	adcshi	pc, r3, r0
d0019aec:	d10b2e0a 	tstle	fp, sl, lsl #28
d0019af0:	7292f46f 	addsvc	pc, r2, #1862270976	; 0x6f000000
d0019af4:	2a01445a 	bcs	0xd006ac64
d0019af8:	6da2d906 			; <UNDEFINED> instruction: 0x6da2d906
d0019afc:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0019b00:	4a71aefa 	bmi	0xd1c856f0
d0019b04:	e6fe447a 	uxtah	r4, lr, sl, ror #8
d0019b08:	db2d2d00 	blle	0xd0b64f10
d0019b0c:	2200486f 	andcs	r4, r0, #7274496	; 0x6f0000
d0019b10:	44784629 	ldrbtmi	r4, [r8], #-1577	; 0xfffff9d7
d0019b14:	ffeaf7fa 			; <UNDEFINED> instruction: 0xffeaf7fa
d0019b18:	f24b486d 	vadd.i8	q10, <illegal reg q5.5>, <illegal reg q14.5>
d0019b1c:	44784103 	ldrbtmi	r4, [r8], #-259	; 0xfffffefd
d0019b20:	ffc6f7fa 			; <UNDEFINED> instruction: 0xffc6f7fa
d0019b24:	21014f6b 	tstcs	r1, fp, ror #30
d0019b28:	447f9a00 	ldrbtmi	r9, [pc], #-2560	; 0xd0019b30
d0019b2c:	f7fc4638 			; <UNDEFINED> instruction: 0xf7fc4638
d0019b30:	f1bbfb51 			; <UNDEFINED> instruction: 0xf1bbfb51
d0019b34:	d02a0f3d 	eorle	r0, sl, sp, lsr pc
d0019b38:	4106f64b 	tstmi	r6, fp, asr #12	; <UNPREDICTABLE>
d0019b3c:	f7fa4638 			; <UNDEFINED> instruction: 0xf7fa4638
d0019b40:	f46fffb7 			; <UNDEFINED> instruction: 0xf46fffb7
d0019b44:	2e0a7392 	mcrcs	3, 0, r7, cr10, cr2, {4}
d0019b48:	0403eb0b 	streq	lr, [r3], #-2827	; 0xfffff4f5
d0019b4c:	2180d12e 	orrcs	sp, r0, lr, lsr #2
d0019b50:	f7fa4638 			; <UNDEFINED> instruction: 0xf7fa4638
d0019b54:	2c08ffad 	stccs	15, cr15, [r8], {173}	; 0xad
d0019b58:	e8dfd821 	ldm	pc, {r0, r5, fp, ip, lr, pc}^	; <UNPREDICTABLE>
d0019b5c:	4112f004 	tstmi	r2, r4	; <UNPREDICTABLE>
d0019b60:	4b462020 	blmi	0xd11a1be8
d0019b64:	00555550 	subseq	r5, r5, r0, asr r5
d0019b68:	4652485b 			; <UNDEFINED> instruction: 0x4652485b
d0019b6c:	44782101 	ldrbtmi	r2, [r8], #-257	; 0xfffffeff
d0019b70:	f7fb9001 			; <UNDEFINED> instruction: 0xf7fb9001
d0019b74:	f646f805 			; <UNDEFINED> instruction: 0xf646f805
d0019b78:	98010108 	stmdals	r1, {r3, r8}
d0019b7c:	ff98f7fa 			; <UNDEFINED> instruction: 0xff98f7fa
d0019b80:	4856e7ca 	ldmdami	r6, {r1, r3, r6, r7, r8, r9, sl, sp, lr, pc}^
d0019b84:	0108f641 	tsteq	r8, r1, asr #12	; <UNPREDICTABLE>
d0019b88:	f7fa4478 			; <UNDEFINED> instruction: 0xf7fa4478
d0019b8c:	2e05ff91 	mcrcs	15, 0, pc, cr5, cr1, {4}	; <UNPREDICTABLE>
d0019b90:	4853d105 	ldmdami	r3, {r0, r2, r8, ip, lr, pc}^
d0019b94:	21c0f24b 	biccs	pc, r0, fp, asr #4
d0019b98:	f7fa4478 			; <UNDEFINED> instruction: 0xf7fa4478
d0019b9c:	2d00ff89 	stccs	15, cr15, [r0, #-548]	; 0xfffffddc
d0019ba0:	4850db48 	ldmdami	r0, {r3, r6, r8, r9, fp, ip, lr, pc}^
d0019ba4:	46292200 	strtmi	r2, [r9], -r0, lsl #4
d0019ba8:	e7584478 			; <UNDEFINED> instruction: 0xe7584478
d0019bac:	d8ee2c08 	stmiale	lr!, {r3, sl, fp, sp}^
d0019bb0:	f853a302 			; <UNDEFINED> instruction: 0xf853a302
d0019bb4:	44132024 	ldrmi	r2, [r3], #-36	; 0xffffffdc
d0019bb8:	bf004718 	svclt	0x00004718
d0019bbc:	ffffffc7 			; <UNDEFINED> instruction: 0xffffffc7
d0019bc0:	00000025 	andeq	r0, r0, r5, lsr #32
d0019bc4:	ffffffd3 			; <UNDEFINED> instruction: 0xffffffd3
d0019bc8:	ffffffd3 			; <UNDEFINED> instruction: 0xffffffd3
d0019bcc:	0000002f 	andeq	r0, r0, pc, lsr #32
d0019bd0:	00000039 	andeq	r0, r0, r9, lsr r0
d0019bd4:	00000043 	andeq	r0, r0, r3, asr #32
d0019bd8:	0000004d 	andeq	r0, r0, sp, asr #32
d0019bdc:	0000004d 	andeq	r0, r0, sp, asr #32
d0019be0:	f6414841 			; <UNDEFINED> instruction: 0xf6414841
d0019be4:	44782108 	ldrbtmi	r2, [r8], #-264	; 0xfffffef8
d0019be8:	4840e7cf 	stmdami	r0, {r0, r1, r2, r3, r6, r7, r8, r9, sl, sp, lr, pc}^
d0019bec:	0108f244 	tsteq	r8, r4, asr #4	; <UNPREDICTABLE>
d0019bf0:	e7ca4478 			; <UNDEFINED> instruction: 0xe7ca4478
d0019bf4:	f244483e 	vtst.8	d20, d4, d30
d0019bf8:	44783108 	ldrbtmi	r3, [r8], #-264	; 0xfffffef8
d0019bfc:	483de7c5 	ldmdami	sp!, {r0, r2, r6, r7, r8, r9, sl, sp, lr, pc}
d0019c00:	0148f244 	cmpeq	r8, r4, asr #4	; <UNPREDICTABLE>
d0019c04:	e7c04478 			; <UNDEFINED> instruction: 0xe7c04478
d0019c08:	f244483b 	vtst.8	d20, d4, d27
d0019c0c:	44786102 	ldrbtmi	r6, [r8], #-258	; 0xfffffefe
d0019c10:	f7fa9000 			; <UNDEFINED> instruction: 0xf7fa9000
d0019c14:	f244ff4d 	vmax.f32	<illegal reg q15.5>, q2, <illegal reg q6.5>
d0019c18:	98006108 	stmdals	r0, {r3, r8, sp, lr}
d0019c1c:	ff48f7fa 			; <UNDEFINED> instruction: 0xff48f7fa
d0019c20:	0190f244 	orrseq	pc, r0, r4, asr #4
d0019c24:	1310f244 	tstne	r0, #68, 4	; 0x40000004	; <UNPREDICTABLE>
d0019c28:	f5bb9800 			; <UNDEFINED> instruction: 0xf5bb9800
d0019c2c:	bf187f96 	svclt	0x00187f96
d0019c30:	e7aa4619 			; <UNDEFINED> instruction: 0xe7aa4619
d0019c34:	46524831 			; <UNDEFINED> instruction: 0x46524831
d0019c38:	44782101 	ldrbtmi	r2, [r8], #-257	; 0xfffffeff
d0019c3c:	f7fa9000 			; <UNDEFINED> instruction: 0xf7fa9000
d0019c40:	f246ff9f 	vrecps.f32	d31, d22, d15
d0019c44:	98000108 	stmdals	r0, {r3, r8}
d0019c48:	e8bdb005 	pop	{r0, r2, ip, sp, pc}
d0019c4c:	f7fa4ff0 			; <UNDEFINED> instruction: 0xf7fa4ff0
d0019c50:	2e0abf2f 	cdpcs	15, 0, cr11, cr10, cr15, {1}
d0019c54:	bf089b00 	svclt	0x00089b00
d0019c58:	93002304 	movwls	r2, #772	; 0x304
d0019c5c:	2230e762 	eorscs	lr, r0, #25690112	; 0x1880000
d0019c60:	4405fb02 	strmi	pc, [r5], #-2818	; 0xfffff4fe
d0019c64:	2490f504 	ldrcs	pc, [r0], #1284	; 0x504
d0019c68:	2664f894 			; <UNDEFINED> instruction: 0x2664f894
d0019c6c:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0019c70:	f894ae37 			; <UNDEFINED> instruction: 0xf894ae37
d0019c74:	f04f6659 			; <UNDEFINED> instruction: 0xf04f6659
d0019c78:	e64b3aff 			; <UNDEFINED> instruction: 0xe64b3aff
d0019c7c:	0000e24c 	andeq	lr, r0, ip, asr #4
d0019c80:	0000e21c 	andeq	lr, r0, ip, lsl r2
d0019c84:	0000e20a 	andeq	lr, r0, sl, lsl #4
d0019c88:	0000e1b2 			; <UNDEFINED> instruction: 0x0000e1b2
d0019c8c:	fffffddb 			; <UNDEFINED> instruction: 0xfffffddb
d0019c90:	fffffd9c 			; <UNDEFINED> instruction: 0xfffffd9c
d0019c94:	0000e174 	andeq	lr, r0, r4, ror r1
d0019c98:	fffffda9 			; <UNDEFINED> instruction: 0xfffffda9
d0019c9c:	0000e140 	andeq	lr, r0, r0, asr #2
d0019ca0:	0000e0fe 	strdeq	lr, [r0], -lr	; <UNPREDICTABLE>
d0019ca4:	0000e0ae 	andeq	lr, r0, lr, lsr #1
d0019ca8:	fffffd17 			; <UNDEFINED> instruction: 0xfffffd17
d0019cac:	0000e08e 	andeq	lr, r0, lr, lsl #1
d0019cb0:	fffffd1b 			; <UNDEFINED> instruction: 0xfffffd1b
d0019cb4:	0000e07a 	andeq	lr, r0, sl, ror r0
d0019cb8:	fffffd17 			; <UNDEFINED> instruction: 0xfffffd17
d0019cbc:	fffffd0e 			; <UNDEFINED> instruction: 0xfffffd0e
d0019cc0:	fffffd15 			; <UNDEFINED> instruction: 0xfffffd15
d0019cc4:	fffffd11 			; <UNDEFINED> instruction: 0xfffffd11
d0019cc8:	fffffd06 			; <UNDEFINED> instruction: 0xfffffd06
d0019ccc:	0000df82 	andeq	sp, r0, r2, lsl #31
d0019cd0:	0000df76 	andeq	sp, r0, r6, ror pc
d0019cd4:	0000df6a 	andeq	sp, r0, sl, ror #30
d0019cd8:	0000df26 	andeq	sp, r0, r6, lsr #30
d0019cdc:	0000df0c 	andeq	sp, r0, ip, lsl #30
d0019ce0:	0000defc 	strdeq	sp, [r0], -ip
d0019ce4:	0000deec 	andeq	sp, r0, ip, ror #29
d0019ce8:	0000deae 	andeq	sp, r0, lr, lsr #29
d0019cec:	0000dea4 	andeq	sp, r0, r4, lsr #29
d0019cf0:	0000de9a 	muleq	r0, sl, lr
d0019cf4:	0000de90 	muleq	r0, r0, lr
d0019cf8:	0000de86 	andeq	sp, r0, r6, lsl #29
d0019cfc:	0000de5a 	andeq	sp, r0, sl, asr lr

Disassembly of section .text.initialize_scalar.constprop.0:

d0019d60 <.text.initialize_scalar.constprop.0>:
d0019d60:	4ff0e92d 	svcmi	0x00f0e92d
d0019d64:	4606b087 	strmi	fp, [r6], -r7, lsl #1
d0019d68:	9201460d 	andls	r4, r1, #13631488	; 0xd00000
d0019d6c:	4c39b971 			; <UNDEFINED> instruction: 0x4c39b971
d0019d70:	447c2201 	ldrbtmi	r2, [ip], #-513	; 0xfffffdff
d0019d74:	46204611 			; <UNDEFINED> instruction: 0x46204611
d0019d78:	fa2cf7fc 	blx	0xd0b57d70
d0019d7c:	4631462a 	ldrtmi	r4, [r1], -sl, lsr #12
d0019d80:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0019d84:	b007fece 	andlt	pc, r7, lr, asr #29
d0019d88:	8ff0e8bd 	svchi	0x00f0e8bd
d0019d8c:	212d4c32 			; <UNDEFINED> instruction: 0x212d4c32
d0019d90:	4620447c 			; <UNDEFINED> instruction: 0x4620447c
d0019d94:	f8a6f7f9 			; <UNDEFINED> instruction: 0xf8a6f7f9
d0019d98:	69e269a3 	stmibvs	r2!, {r0, r1, r5, r7, r8, fp, sp, lr}^
d0019d9c:	718df44f 	orrvc	pc, sp, pc, asr #8
d0019da0:	46209000 	strtmi	r9, [r0], -r0
d0019da4:	92029303 	andls	r9, r2, #201326592	; 0xc000000
d0019da8:	9030f894 	mlasls	r0, r4, r8, pc	; <UNPREDICTABLE>
d0019dac:	8034f8d4 	ldrsbthi	pc, [r4], -r4	; <UNPREDICTABLE>
d0019db0:	5b08e9d4 	blpl	0xd0254508
d0019db4:	a70ae9d4 			; <UNDEFINED> instruction: 0xa70ae9d4
d0019db8:	f894f7f9 			; <UNDEFINED> instruction: 0xf894f7f9
d0019dbc:	9b039a02 	blls	0xd01005cc
d0019dc0:	4620b190 			; <UNDEFINED> instruction: 0x4620b190
d0019dc4:	fe2ef7f9 	mcr2	7, 1, pc, cr14, cr9, {7}	; <UNPREDICTABLE>
d0019dc8:	9b004605 	blls	0xd002b5e4
d0019dcc:	426db103 	rsbmi	fp, sp, #-1073741824	; 0xc0000000
d0019dd0:	b35b9b01 	cmplt	fp, #1024	; 0x400
d0019dd4:	d9292dff 	stmdble	r9!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, sl, fp, sp}
d0019dd8:	447b4b20 	ldrbtmi	r4, [fp], #-2848	; 0xfffff4e0
d0019ddc:	2a006d9a 	bcs	0xd003544c
d0019de0:	4a1fd1d1 	bmi	0xd080e52c
d0019de4:	e00f447a 	and	r4, pc, sl, ror r4	; <UNPREDICTABLE>
d0019de8:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d0019dec:	d112428f 	tstle	r2, pc, lsl #5
d0019df0:	46204619 			; <UNDEFINED> instruction: 0x46204619
d0019df4:	fdbff7f6 	ldc2	7, cr15, [pc, #984]!	; 0xd001a1d4
d0019df8:	4b1ab9b0 	blmi	0xd06c84c0
d0019dfc:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d0019e00:	d1c02a00 	bicle	r2, r0, r0, lsl #20
d0019e04:	447a4a18 	ldrbtmi	r4, [sl], #-2584	; 0xfffff5e8
d0019e08:	8068f8c3 	rsbhi	pc, r8, r3, asr #17
d0019e0c:	2b16e9c3 	blcs	0xd05d4520
d0019e10:	a918e9c3 	ldmdbge	r8, {r0, r1, r6, r7, r8, fp, sp, lr, pc}
d0019e14:	f5a7e7b7 			; <UNDEFINED> instruction: 0xf5a7e7b7
d0019e18:	2f017781 	svccs	0x00017781
d0019e1c:	4813d8ed 	ldmdami	r3, {r0, r2, r3, r5, r6, r7, fp, ip, lr, pc}
d0019e20:	f7f94478 			; <UNDEFINED> instruction: 0xf7f94478
d0019e24:	e7d0f83f 			; <UNDEFINED> instruction: 0xe7d0f83f
d0019e28:	e7f86a05 	ldrb	r6, [r8, r5, lsl #20]!
d0019e2c:	95054b10 	strls	r4, [r5, #-2832]	; 0xfffff4f0
d0019e30:	f503447b 			; <UNDEFINED> instruction: 0xf503447b
d0019e34:	f8d3337f 			; <UNDEFINED> instruction: 0xf8d3337f
d0019e38:	44311224 	ldrtmi	r1, [r1], #-548	; 0xfffffddc
d0019e3c:	2201b115 	andcs	fp, r1, #1073741829	; 0x40000005
d0019e40:	2220f883 	eorcs	pc, r0, #8585216	; 0x830000
d0019e44:	aa052304 	bge	0xd0162a5c
d0019e48:	20010089 	andcs	r0, r1, r9, lsl #1
d0019e4c:	fdb8f7fa 	ldc2	7, cr15, [r8, #1000]!	; 0x3e8
d0019e50:	bf00e799 	svclt	0x0000e799
d0019e54:	0000dd22 	andeq	sp, r0, r2, lsr #26
d0019e58:	0000dd04 	andeq	sp, r0, r4, lsl #26
d0019e5c:	0000dcba 			; <UNDEFINED> instruction: 0x0000dcba
d0019e60:	ffffff4f 			; <UNDEFINED> instruction: 0xffffff4f
d0019e64:	0000dc98 	muleq	r0, r8, ip
d0019e68:	fffffef6 			; <UNDEFINED> instruction: 0xfffffef6
d0019e6c:	0000dc74 	andeq	sp, r0, r4, ror ip
d0019e70:	0000dc64 	andeq	sp, r0, r4, ror #24

Disassembly of section .text.initialize_record.constprop.0:

d0019f74 <.text.initialize_record.constprop.0>:
d0019f74:	e92d2b21 	push	{r0, r5, r8, r9, fp, sp}
d0019f78:	46064ff8 			; <UNDEFINED> instruction: 0x46064ff8
d0019f7c:	4617468b 	ldrmi	r4, [r7], -fp, lsl #13
d0019f80:	d107469a 			; <UNDEFINED> instruction: 0xd107469a
d0019f84:	48554954 	ldmdami	r5, {r2, r4, r6, r8, fp, lr}^
d0019f88:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d0019f8c:	4ff8e8bd 	svcmi	0x00f8e8bd
d0019f90:	b95cf7f6 	ldmdblt	ip, {r1, r2, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}^
d0019f94:	217b4d52 	cmncs	fp, r2, asr sp
d0019f98:	447d4a52 	ldrbtmi	r4, [sp], #-2642	; 0xfffff5ae
d0019f9c:	4628447a 			; <UNDEFINED> instruction: 0x4628447a
d0019fa0:	ffaef7f8 			; <UNDEFINED> instruction: 0xffaef7f8
d0019fa4:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d0019fa8:	f44f8094 	vst4.32	{d24-d27}, [pc :64], r4
d0019fac:	f04f731a 			; <UNDEFINED> instruction: 0xf04f731a
d0019fb0:	435e0900 	cmpmi	lr, #0, 18
d0019fb4:	3467f506 	strbtcc	pc, [r7], #-1286	; 0xfffffafa	; <UNPREDICTABLE>
d0019fb8:	74f4f504 	ldrbtvc	pc, [r4], #1284	; 0x504	; <UNPREDICTABLE>
d0019fbc:	6dab442c 	cfstrsvs	mvf4, [fp, #176]!	; 0xb0
d0019fc0:	d1392b00 	teqle	r9, r0, lsl #22
d0019fc4:	2b7d6aeb 	blcs	0xd1f74b78
d0019fc8:	f5b3d036 			; <UNDEFINED> instruction: 0xf5b3d036
d0019fcc:	d0337f80 	eorsle	r7, r3, r0, lsl #31
d0019fd0:	f50219aa 			; <UNDEFINED> instruction: 0xf50219aa
d0019fd4:	f8923268 			; <UNDEFINED> instruction: 0xf8923268
d0019fd8:	4549102a 	strbmi	r1, [r9, #-42]	; 0xffffffd6
d0019fdc:	f892d905 			; <UNDEFINED> instruction: 0xf892d905
d0019fe0:	b13a202b 	teqlt	sl, fp, lsr #32
d0019fe4:	0f00f1b9 	svceq	0x0000f1b9
d0019fe8:	493fd004 	ldmdbmi	pc!, {r2, ip, lr, pc}	; <UNPREDICTABLE>
d0019fec:	4479483f 	ldrbtmi	r4, [r9], #-2111	; 0xfffff7c1
d0019ff0:	e7cb4478 			; <UNDEFINED> instruction: 0xe7cb4478
d0019ff4:	8022f8b4 	strhthi	pc, [r2], -r4	; <UNPREDICTABLE>
d0019ff8:	2021f894 	mlacs	r1, r4, r8, pc	; <UNPREDICTABLE>
d0019ffc:	0020f894 	mlaeq	r0, r4, r8, pc	; <UNPREDICTABLE>
d001a000:	2a0044d8 	bcs	0xd002b368
d001a004:	b38fd047 	orrlt	sp, pc, #71	; 0x47
d001a008:	80e4f8df 	ldrdhi	pc, [r4], #143	; 0x8f	; <UNPREDICTABLE>
d001a00c:	44f84a39 	ldrbtmi	r4, [r8], #2617	; 0xa39
d001a010:	e9d8447a 	ldmib	r8, {r1, r3, r4, r5, r6, sl, lr}^
d001a014:	f7f60106 			; <UNDEFINED> instruction: 0xf7f60106
d001a018:	b1b0fc7b 	rorslt	pc, fp, ip	; <UNPREDICTABLE>
d001a01c:	44784836 	ldrbtmi	r4, [r8], #-2102	; 0xfffff7ca
d001a020:	ff40f7f8 			; <UNDEFINED> instruction: 0xff40f7f8
d001a024:	212c4835 			; <UNDEFINED> instruction: 0x212c4835
d001a028:	0901f109 	stmdbeq	r1, {r0, r3, r8, ip, sp, lr, pc}
d001a02c:	44783424 	ldrbtmi	r3, [r8], #-1060	; 0xfffffbdc
d001a030:	ff58f7f8 			; <UNDEFINED> instruction: 0xff58f7f8
d001a034:	d1c22800 	bicle	r2, r2, r0, lsl #16
d001a038:	217d4a31 	cmncs	sp, r1, lsr sl
d001a03c:	447a4831 	ldrbtmi	r4, [sl], #-2097	; 0xfffff7cf
d001a040:	e8bd4478 	pop	{r3, r4, r5, r6, sl, lr}
d001a044:	f7f84ff8 			; <UNDEFINED> instruction: 0xf7f84ff8
d001a048:	f8d8bf5b 			; <UNDEFINED> instruction: 0xf8d8bf5b
d001a04c:	f5a3302c 			; <UNDEFINED> instruction: 0xf5a3302c
d001a050:	2b017381 	blcs	0xd0076e5c
d001a054:	f8d8d803 			; <UNDEFINED> instruction: 0xf8d8d803
d001a058:	2b003020 	blcs	0xd00260e0
d001a05c:	492ad0de 	stmdbmi	sl!, {r1, r2, r3, r4, r6, r7, ip, lr, pc}
d001a060:	4479482a 	ldrbtmi	r4, [r9], #-2090	; 0xfffff7d6
d001a064:	f7f64478 			; <UNDEFINED> instruction: 0xf7f64478
d001a068:	e7dbf8f1 			; <UNDEFINED> instruction: 0xe7dbf8f1
d001a06c:	d10c28ff 	strdle	r2, [ip, -pc]
d001a070:	22044827 	andcs	r4, r4, #2555904	; 0x270000
d001a074:	44782101 	ldrbtmi	r2, [r8], #-257	; 0xfffffeff
d001a078:	f8acf7fc 			; <UNDEFINED> instruction: 0xf8acf7fc
d001a07c:	22004825 	andcs	r4, r0, #2424832	; 0x250000
d001a080:	44784641 	ldrbtmi	r4, [r8], #-1601	; 0xfffff9bf
d001a084:	fd4df7fa 	stc2l	7, cr15, [sp, #-1000]	; 0xfffffc18
d001a088:	4601e7cc 	strmi	lr, [r1], -ip, asr #15
d001a08c:	44784822 	ldrbtmi	r4, [r8], #-2082	; 0xfffff7de
d001a090:	fec6f7fd 	mcr2	7, 6, pc, cr6, cr13, {7}	; <UNPREDICTABLE>
d001a094:	28ffe7f2 	ldmcs	pc!, {r1, r4, r5, r6, r7, r8, r9, sl, sp, lr, pc}^	; <UNPREDICTABLE>
d001a098:	4639d104 	ldrtmi	sp, [r9], -r4, lsl #2
d001a09c:	f7ff4640 			; <UNDEFINED> instruction: 0xf7ff4640
d001a0a0:	e7bffe5f 	sbfx	pc, pc, #28, #32
d001a0a4:	d1062b7b 	tstle	r6, fp, ror fp
d001a0a8:	0301f10a 	movweq	pc, #4362	; 0x110a	; <UNPREDICTABLE>
d001a0ac:	4641463a 			; <UNDEFINED> instruction: 0x4641463a
d001a0b0:	ff60f7ff 			; <UNDEFINED> instruction: 0xff60f7ff
d001a0b4:	f5a3e7b6 			; <UNDEFINED> instruction: 0xf5a3e7b6
d001a0b8:	2b017381 	blcs	0xd0076ec4
d001a0bc:	4b17d804 	blmi	0xd06100d4
d001a0c0:	6a1b447b 	bvs	0xd06eb2b4
d001a0c4:	d0a92b00 	adcle	r2, r9, r0, lsl #22
d001a0c8:	48164915 	ldmdami	r6, {r0, r2, r4, r8, fp, lr}
d001a0cc:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d001a0d0:	e8bde75c 	pop	{r2, r3, r4, r6, r8, r9, sl, sp, lr, pc}
d001a0d4:	bf008ff8 	svclt	0x00008ff8
d001a0d8:	fffffee8 			; <UNDEFINED> instruction: 0xfffffee8
d001a0dc:	0000db0a 	andeq	sp, r0, sl, lsl #22
d001a0e0:	0000dafa 	strdeq	sp, [r0], -sl
d001a0e4:	fffffef4 			; <UNDEFINED> instruction: 0xfffffef4
d001a0e8:	fffffec6 			; <UNDEFINED> instruction: 0xfffffec6
d001a0ec:	0000daa4 	andeq	sp, r0, r4, lsr #21
d001a0f0:	0000da86 	andeq	sp, r0, r6, lsl #21
d001a0f4:	ffffb29e 			; <UNDEFINED> instruction: 0xffffb29e
d001a0f8:	0000da76 	andeq	sp, r0, r6, ror sl
d001a0fc:	0000da66 	andeq	sp, r0, r6, ror #20
d001a100:	ffffff0a 			; <UNDEFINED> instruction: 0xffffff0a
d001a104:	0000da54 	andeq	sp, r0, r4, asr sl
d001a108:	fffffe7c 			; <UNDEFINED> instruction: 0xfffffe7c
d001a10c:	0000da30 	andeq	sp, r0, r0, lsr sl
d001a110:	0000da1e 	andeq	sp, r0, lr, lsl sl
d001a114:	0000da12 	andeq	sp, r0, r2, lsl sl
d001a118:	0000da06 	andeq	sp, r0, r6, lsl #20
d001a11c:	0000d9d4 	ldrdeq	sp, [r0], -r4
d001a120:	fffffe4b 			; <UNDEFINED> instruction: 0xfffffe4b
d001a124:	0000d9c6 	andeq	sp, r0, r6, asr #19

Disassembly of section .text.initialize_array.constprop.0:

d001a1c0 <.text.initialize_array.constprop.0>:
d001a1c0:	4ff7e92d 	svcmi	0x00f7e92d
d001a1c4:	46154e36 			; <UNDEFINED> instruction: 0x46154e36
d001a1c8:	460c4a36 			; <UNDEFINED> instruction: 0x460c4a36
d001a1cc:	9001447e 	andls	r4, r1, lr, ror r4
d001a1d0:	217b447a 	cmncs	fp, sl, ror r4
d001a1d4:	461f4630 			; <UNDEFINED> instruction: 0x461f4630
d001a1d8:	a030f8dd 	ldrsbtge	pc, [r0], -sp	; <UNPREDICTABLE>
d001a1dc:	fe90f7f8 	mrc2	7, 4, pc, cr0, cr8, {7}
d001a1e0:	d05a2800 	subsle	r2, sl, r0, lsl #16
d001a1e4:	f8df2cff 			; <UNDEFINED> instruction: 0xf8df2cff
d001a1e8:	f04fb0c0 			; <UNDEFINED> instruction: 0xf04fb0c0
d001a1ec:	bf140800 	svclt	0x00140800
d001a1f0:	701af44f 	andsvc	pc, sl, pc, asr #8
d001a1f4:	0901f04f 	stmdbeq	r1, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d001a1f8:	bf1844fb 	svclt	0x001844fb
d001a1fc:	6004fb00 	andvs	pc, r4, r0, lsl #22
d001a200:	bf184e2a 	svclt	0x00184e2a
d001a204:	3068f500 	rsbcc	pc, r8, r0, lsl #10
d001a208:	bf18447e 	svclt	0x0018447e
d001a20c:	9028f8b0 	strhtls	pc, [r8], -r0	; <UNPREDICTABLE>
d001a210:	bb036db3 	bllt	0xd00f58e4
d001a214:	2b7d6af3 	blcs	0xd1f74de8
d001a218:	f5b3d01d 			; <UNDEFINED> instruction: 0xf5b3d01d
d001a21c:	d01a7f80 	andsle	r7, sl, r0, lsl #31
d001a220:	45429a01 	strbmi	r9, [r2, #-2561]	; 0xfffff5ff
d001a224:	4922d107 	stmdbmi	r2!, {r0, r1, r2, r8, ip, lr, pc}
d001a228:	44794630 	ldrbtmi	r4, [r9], #-1584	; 0xfffff9d0
d001a22c:	e8bdb003 	pop	{r0, r1, ip, sp, pc}
d001a230:	f7f64ff0 			; <UNDEFINED> instruction: 0xf7f64ff0
d001a234:	2cffb80b 	ldclcs	8, cr11, [pc], #44	; 0xd001a268
d001a238:	4652d117 			; <UNDEFINED> instruction: 0x4652d117
d001a23c:	46284639 			; <UNDEFINED> instruction: 0x46284639
d001a240:	fd8ef7ff 	stc2	7, cr15, [lr, #1020]	; 0x3fc
d001a244:	4658212c 	ldrbmi	r2, [r8], -ip, lsr #2
d001a248:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d001a24c:	f7f8444d 			; <UNDEFINED> instruction: 0xf7f8444d
d001a250:	2800fe49 	stmdacs	r0, {r0, r3, r6, r9, sl, fp, ip, sp, lr, pc}
d001a254:	4a17d1dc 	bmi	0xd060e9cc
d001a258:	4817217d 	ldmdami	r7, {r0, r2, r3, r4, r5, r6, r8, sp}
d001a25c:	4478447a 	ldrbtmi	r4, [r8], #-1146	; 0xfffffb86
d001a260:	e8bdb003 	pop	{r0, r1, ip, sp, pc}
d001a264:	f7f84ff0 			; <UNDEFINED> instruction: 0xf7f84ff0
d001a268:	2b7bbe4b 	blcs	0xd1f09b9c
d001a26c:	2301d106 	movwcs	sp, #4358	; 0x1106
d001a270:	4629463a 			; <UNDEFINED> instruction: 0x4629463a
d001a274:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d001a278:	e7e3fe7d 			; <UNDEFINED> instruction: 0xe7e3fe7d
d001a27c:	7381f5a3 	orrvc	pc, r1, #683671552	; 0x28c00000
d001a280:	d8052b01 	stmdale	r5, {r0, r8, r9, fp, sp}
d001a284:	b91b6a33 	ldmdblt	fp, {r0, r1, r4, r5, r9, fp, sp, lr}
d001a288:	f7f84630 			; <UNDEFINED> instruction: 0xf7f84630
d001a28c:	e7d9fe0b 	ldrb	pc, [r9, fp, lsl #28]	; <UNPREDICTABLE>
d001a290:	480b490a 	stmdami	fp, {r1, r3, r8, fp, lr}
d001a294:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d001a298:	b003e7c8 	andlt	lr, r3, r8, asr #15
d001a29c:	8ff0e8bd 	svchi	0x00f0e8bd
d001a2a0:	0000d8c8 	andeq	sp, r0, r8, asr #17
d001a2a4:	ffffff54 			; <UNDEFINED> instruction: 0xffffff54
d001a2a8:	0000d89c 	muleq	r0, ip, r8
d001a2ac:	0000d88c 	andeq	sp, r0, ip, lsl #17
d001a2b0:	ffffff1d 			; <UNDEFINED> instruction: 0xffffff1d
d001a2b4:	ffffff39 			; <UNDEFINED> instruction: 0xffffff39
d001a2b8:	0000d836 	andeq	sp, r0, r6, lsr r8
d001a2bc:	fffffed7 			; <UNDEFINED> instruction: 0xfffffed7
d001a2c0:	0000d7fe 	strdeq	sp, [r0], -lr

Disassembly of section .text.local_declaration.constprop.0:

d001a52c <.text.local_declaration.constprop.0>:
d001a52c:	4ff0e92d 	svcmi	0x00f0e92d
d001a530:	472cf8df 			; <UNDEFINED> instruction: 0x472cf8df
d001a534:	7185f44f 	orrvc	pc, r5, pc, asr #8
d001a538:	ed2d447c 	cfstrs	mvf4, [sp, #-496]!	; 0xfffffe10
d001a53c:	46208b02 	strtmi	r8, [r0], -r2, lsl #22
d001a540:	f7f8b099 			; <UNDEFINED> instruction: 0xf7f8b099
d001a544:	6ae2fccf 	bvs	0xcf8d9888
d001a548:	131bf240 	tstne	fp, #64, 4	; <UNPREDICTABLE>
d001a54c:	429a4605 	addsmi	r4, sl, #5242880	; 0x500000
d001a550:	4620d10a 	strtmi	sp, [r0], -sl, lsl #2
d001a554:	ffc6f7f8 			; <UNDEFINED> instruction: 0xffc6f7f8
d001a558:	2501bb98 	strcs	fp, [r1, #-2968]	; 0xfffff468
d001a55c:	b0194628 	andslt	r4, r9, r8, lsr #12
d001a560:	8b02ecbd 	blhi	0xd00d585c
d001a564:	8ff0e8bd 	svchi	0x00f0e8bd
d001a568:	1107f240 	tstne	r7, r0, asr #4	; <UNPREDICTABLE>
d001a56c:	f7f84620 			; <UNDEFINED> instruction: 0xf7f84620
d001a570:	b148fcb9 	strhlt	pc, [r8, #-201]	; 0xffffff37	; <UNPREDICTABLE>
d001a574:	2b286ae3 	blcs	0xd0a35108
d001a578:	6ce3d123 	stfvsp	f5, [r3], #140	; 0x8c
d001a57c:	d1202b2a 			; <UNDEFINED> instruction: 0xd1202b2a
d001a580:	f7fb2000 			; <UNDEFINED> instruction: 0xf7fb2000
d001a584:	e7e8f88b 	strb	pc, [r8, fp, lsl #17]!	; <UNPREDICTABLE>
d001a588:	f2406ae2 	vpmax.s8	q11, q8, q9
d001a58c:	429a1301 	addsmi	r1, sl, #67108864	; 0x4000000
d001a590:	4620d11c 			; <UNDEFINED> instruction: 0x4620d11c
d001a594:	1206e9d4 	andne	lr, r6, #212, 18	; 0x350000
d001a598:	f94df7f6 			; <UNDEFINED> instruction: 0xf94df7f6
d001a59c:	db152800 	blle	0xd05645a4
d001a5a0:	e9d44620 	ldmib	r4, {r5, r9, sl, lr}^
d001a5a4:	f7f61206 			; <UNDEFINED> instruction: 0xf7f61206
d001a5a8:	2324f946 	msrcs	CPSR_s, #1146880	; 0x118000
d001a5ac:	4000fb03 	andmi	pc, r0, r3, lsl #22
d001a5b0:	3075f500 	rsbscc	pc, r5, r0, lsl #10
d001a5b4:	33acf890 			; <UNDEFINED> instruction: 0x33acf890
d001a5b8:	d1072bff 	strdle	r2, [r7, -pc]
d001a5bc:	f7f84620 			; <UNDEFINED> instruction: 0xf7f84620
d001a5c0:	2301fc71 	movwcs	pc, #7281	; 0x1c71	; <UNPREDICTABLE>
d001a5c4:	23009308 	movwcs	r9, #776	; 0x308
d001a5c8:	e1e19307 	mvn	r9, r7, lsl #6
d001a5cc:	4694f8df 			; <UNDEFINED> instruction: 0x4694f8df
d001a5d0:	7184f44f 	orrvc	pc, r4, pc, asr #8
d001a5d4:	4620447c 			; <UNDEFINED> instruction: 0x4620447c
d001a5d8:	fc84f7f8 	stc2	7, cr15, [r4], {248}	; 0xf8
d001a5dc:	b1804606 	orrlt	r4, r0, r6, lsl #12
d001a5e0:	2b286ae3 	blcs	0xd0a35174
d001a5e4:	6ce3d104 	stfvsp	f5, [r3], #16
d001a5e8:	d1012b2a 	tstle	r1, sl, lsr #22
d001a5ec:	e7c82001 	strb	r2, [r8, r1]
d001a5f0:	1674f8df 			; <UNDEFINED> instruction: 0x1674f8df
d001a5f4:	0674f8df 			; <UNDEFINED> instruction: 0x0674f8df
d001a5f8:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d001a5fc:	fe26f7f5 	mcr2	7, 1, pc, cr6, cr5, {7}	; <UNPREDICTABLE>
d001a600:	4620e7ab 	strtmi	lr, [r0], -fp, lsr #15
d001a604:	f93cf7f6 			; <UNDEFINED> instruction: 0xf93cf7f6
d001a608:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d001a60c:	a90f819b 	stmdbge	pc, {r0, r1, r3, r4, r7, r8, pc}	; <UNPREDICTABLE>
d001a610:	960f4620 	strls	r4, [pc], -r0, lsr #12
d001a614:	fe70f7f8 	mrc2	7, 3, pc, cr0, cr8, {7}
d001a618:	d09e2800 	addsle	r2, lr, r0, lsl #16
d001a61c:	7650f8df 			; <UNDEFINED> instruction: 0x7650f8df
d001a620:	4a10ee08 	bmi	0xd0455e48
d001a624:	f507447f 			; <UNDEFINED> instruction: 0xf507447f
d001a628:	930c2392 	movwls	r2, #50066	; 0xc392
d001a62c:	ee18212a 	mufep	f2, f0, #2.0
d001a630:	f7f80a10 			; <UNDEFINED> instruction: 0xf7f80a10
d001a634:	9007fc57 	andls	pc, r7, r7, asr ip	; <UNPREDICTABLE>
d001a638:	d0712800 	rsbsle	r2, r1, r0, lsl #16
d001a63c:	ee18212a 	mufep	f2, f0, #2.0
d001a640:	f7f80a10 			; <UNDEFINED> instruction: 0xf7f80a10
d001a644:	1e03fc4f 	cdpne	12, 0, cr15, cr3, cr15, {2}
d001a648:	2301bf18 	movwcs	fp, #7960	; 0x1f18
d001a64c:	6624f8df 			; <UNDEFINED> instruction: 0x6624f8df
d001a650:	9309ac10 	movwls	sl, #39952	; 0x9c10
d001a654:	f106447e 			; <UNDEFINED> instruction: 0xf106447e
d001a658:	f8960518 			; <UNDEFINED> instruction: 0xf8960518
d001a65c:	f8d69030 			; <UNDEFINED> instruction: 0xf8d69030
d001a660:	cd0fb034 	stcgt	0, cr11, [pc, #-208]	; 0xd001a598
d001a664:	e895c40f 	ldm	r5, {r0, r1, r2, r3, sl, lr, pc}
d001a668:	e884000f 	stm	r4, {r0, r1, r2, r3}
d001a66c:	f8df000f 			; <UNDEFINED> instruction: 0xf8df000f
d001a670:	f2402608 	vmax.s8	d18, d0, d8
d001a674:	46301101 	ldrtmi	r1, [r0], -r1, lsl #2
d001a678:	447a6a75 	ldrbtmi	r6, [sl], #-2677	; 0xfffff58b
d001a67c:	f7f86ab4 			; <UNDEFINED> instruction: 0xf7f86ab4
d001a680:	ab10fc3f 	blge	0xd0459784
d001a684:	2800930a 	stmdacs	r0, {r1, r3, r8, r9, ip, pc}
d001a688:	af67f43f 	svcge	0x0067f43f
d001a68c:	2b009b07 	blcs	0xd00412b0
d001a690:	4630d148 	ldrtmi	sp, [r0], -r8, asr #2
d001a694:	f7f8215b 			; <UNDEFINED> instruction: 0xf7f8215b
d001a698:	1e06fc25 	cdpne	12, 0, cr15, cr6, cr5, {1}
d001a69c:	2601bf18 			; <UNDEFINED> instruction: 0x2601bf18
d001a6a0:	a5d8f8df 	ldrbge	pc, [r8, #2271]	; 0x8df	; <UNPREDICTABLE>
d001a6a4:	721af44f 	andsvc	pc, sl, #1325400064	; 0x4f000000
d001a6a8:	44fa9b0f 	ldrbtmi	r9, [sl], #2831	; 0xb0f
d001a6ac:	a203fb02 	andge	pc, r3, #2048	; 0x800
d001a6b0:	3268f502 	rsbcc	pc, r8, #8388608	; 0x800000
d001a6b4:	92088d12 	andls	r8, r8, #1152	; 0x480
d001a6b8:	d0602e00 	rsble	r2, r0, r0, lsl #28
d001a6bc:	202cf8da 	ldrdcs	pc, [ip], -sl	; <UNPREDICTABLE>
d001a6c0:	8020f8da 	ldrdhi	pc, [r0], -sl	; <UNPREDICTABLE>
d001a6c4:	7281f5a2 	addvc	pc, r1, #679477248	; 0x28800000
d001a6c8:	d8082a01 	stmdale	r8, {r0, r9, fp, sp}
d001a6cc:	0f00f1b8 	svceq	0x0000f1b8
d001a6d0:	2240d005 	subcs	sp, r0, #5
d001a6d4:	fbb29908 	blx	0xcecc0afe
d001a6d8:	4590f2f1 	ldrmi	pc, [r0, #753]	; 0x2f1
d001a6dc:	f8dfd928 			; <UNDEFINED> instruction: 0xf8dfd928
d001a6e0:	f44f25a0 	vst3.32	{d18,d20,d22}, [pc :128], r0
d001a6e4:	447a711a 	ldrbtmi	r7, [sl], #-282	; 0xfffffee6
d001a6e8:	2303fb01 	movwcs	pc, #15105	; 0x3b01	; <UNPREDICTABLE>
d001a6ec:	3368f503 	msrcc	SPSR_f, #12582912	; 0xc00000
d001a6f0:	302bf893 	mlacc	fp, r3, r8, pc	; <UNPREDICTABLE>
d001a6f4:	f8dfb9c3 			; <UNDEFINED> instruction: 0xf8dfb9c3
d001a6f8:	447a258c 	ldrbtmi	r2, [sl], #-1420	; 0xfffffa74
d001a6fc:	3588f8df 	strcc	pc, [r8, #2271]	; 0x8df
d001a700:	6d99447b 	cfldrsvs	mvf4, [r9, #492]	; 0x1ec
d001a704:	f47f2900 			; <UNDEFINED> instruction: 0xf47f2900
d001a708:	6a5daf28 	bvs	0xd17863b0
d001a70c:	6b596a9c 	blvs	0xd1675184
d001a710:	0030f893 	mlaseq	r0, r3, r8, pc	; <UNPREDICTABLE>
d001a714:	e9c36699 	stmib	r3, {r0, r3, r4, r7, r9, sl, sp, lr}^
d001a718:	e9c32516 	stmib	r3, {r1, r2, r4, r8, sl, sp}^
d001a71c:	e71c4018 			; <UNDEFINED> instruction: 0xe71c4018
d001a720:	e7939b07 	ldr	r9, [r3, r7, lsl #22]
d001a724:	e7bb2600 	ldr	r2, [fp, r0, lsl #12]!
d001a728:	2560f8df 	strbcs	pc, [r0, #-2271]!	; 0xfffff721	; <UNPREDICTABLE>
d001a72c:	e7e5447a 			; <UNDEFINED> instruction: 0xe7e5447a
d001a730:	f7f84650 			; <UNDEFINED> instruction: 0xf7f84650
d001a734:	f8dffbb7 			; <UNDEFINED> instruction: 0xf8dffbb7
d001a738:	215d2558 	cmpcs	sp, r8, asr r5
d001a73c:	447a4650 	ldrbtmi	r4, [sl], #-1616	; 0xfffff9b0
d001a740:	fbdef7f8 	blx	0xcf7d872a
d001a744:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001a748:	9b07af08 	blls	0xd0206370
d001a74c:	9b08b9d3 	blls	0xd0248ea0
d001a750:	fa03fb08 	blx	0xd0119378
d001a754:	f8d39b0c 			; <UNDEFINED> instruction: 0xf8d39b0c
d001a758:	f1c33238 			; <UNDEFINED> instruction: 0xf1c33238
d001a75c:	45530340 	ldrbmi	r0, [r3, #-832]	; 0xfffffcc0
d001a760:	6dbbd213 	lfmvs	f5, 1, [fp, #76]!	; 0x4c
d001a764:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001a768:	f8dfaef8 			; <UNDEFINED> instruction: 0xf8dfaef8
d001a76c:	f8c73528 			; <UNDEFINED> instruction: 0xf8c73528
d001a770:	447bb068 	ldrbtmi	fp, [fp], #-104	; 0xffffff98
d001a774:	4918e9c7 	ldmdbmi	r8, {r0, r1, r2, r6, r7, r8, fp, sp, lr, pc}
d001a778:	3516e9c7 	ldrcc	lr, [r6, #-2503]	; 0xfffff639
d001a77c:	f04fe6ed 			; <UNDEFINED> instruction: 0xf04fe6ed
d001a780:	e7e20801 	strb	r0, [r2, r1, lsl #16]!
d001a784:	0a01f04f 	beq	0xd00968c8
d001a788:	9b09e7e4 	blls	0xd0294720
d001a78c:	d1622b00 	cmnle	r2, r0, lsl #22
d001a790:	2b009b07 	blcs	0xd00413b4
d001a794:	2e00d161 	mvfcssz	f5, f1
d001a798:	2310bf14 	tstcs	r0, #20, 30	; 0x50
d001a79c:	9304230d 	movwls	r2, #17165	; 0x430d
d001a7a0:	9414ab18 	ldrls	sl, [r4], #-2840	; 0xfffff4e8
d001a7a4:	9058f88d 	subsls	pc, r8, sp, lsl #17
d001a7a8:	b05cf8cd 	subslt	pc, ip, sp, asr #17
d001a7ac:	e9139513 	ldmdb	r3, {r0, r1, r4, r8, sl, ip, pc}
d001a7b0:	e88d000f 	stm	sp, {r0, r1, r2, r3}
d001a7b4:	9b0a000f 	blls	0xd029a7f8
d001a7b8:	f7f9cb0f 			; <UNDEFINED> instruction: 0xf7f9cb0f
d001a7bc:	f8dffc21 			; <UNDEFINED> instruction: 0xf8dffc21
d001a7c0:	460524d8 			; <UNDEFINED> instruction: 0x460524d8
d001a7c4:	6d93447a 	cfldrsvs	mvf4, [r3, #488]	; 0x1e8
d001a7c8:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001a7cc:	2130aec6 	teqcs	r0, r6, asr #29
d001a7d0:	0b01f04f 	bleq	0xd0096914
d001a7d4:	2992f502 	ldmibcs	r2, {r1, r8, sl, ip, sp, lr, pc}
d001a7d8:	fb01920a 	blx	0xd007f00a
d001a7dc:	980f2300 	stmdals	pc, {r8, r9, sp}	; <UNPREDICTABLE>
d001a7e0:	f503910b 			; <UNDEFINED> instruction: 0xf503910b
d001a7e4:	f8832390 			; <UNDEFINED> instruction: 0xf8832390
d001a7e8:	f8a3065a 			; <UNDEFINED> instruction: 0xf8a3065a
d001a7ec:	45da8662 	ldrbmi	r8, [sl, #1634]	; 0x662
d001a7f0:	4238f8d9 	eorsmi	pc, r8, #14221312	; 0xd90000
d001a7f4:	f8d9d833 			; <UNDEFINED> instruction: 0xf8d9d833
d001a7f8:	429c323c 	addsmi	r3, ip, #60, 4	; 0xc0000003
d001a7fc:	bf889b07 	svclt	0x00889b07
d001a800:	423cf8c9 	eorsmi	pc, ip, #13172736	; 0xc90000
d001a804:	d04c2b00 	suble	r2, ip, r0, lsl #22
d001a808:	4490f8df 	ldrmi	pc, [r0], #2271	; 0x8df
d001a80c:	447c213d 	ldrbtmi	r2, [ip], #-317	; 0xfffffec3
d001a810:	f7f84620 			; <UNDEFINED> instruction: 0xf7f84620
d001a814:	4601fb67 	strmi	pc, [r1], -r7, ror #22
d001a818:	d03e2800 	eorsle	r2, lr, r0, lsl #16
d001a81c:	46209b09 	strtmi	r9, [r0], -r9, lsl #22
d001a820:	b3bb990f 			; <UNDEFINED> instruction: 0xb3bb990f
d001a824:	fb02f7fb 	blx	0xd00d881a
d001a828:	0474f8df 	ldrbteq	pc, [r4], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d001a82c:	46292200 	strtmi	r2, [r9], -r0, lsl #4
d001a830:	f7fa4478 			; <UNDEFINED> instruction: 0xf7fa4478
d001a834:	f8dff976 			; <UNDEFINED> instruction: 0xf8dff976
d001a838:	4478046c 	ldrbtmi	r0, [r8], #-1132	; 0xfffffb94
d001a83c:	2b006d83 	blcs	0xd0035e50
d001a840:	f8dfd079 			; <UNDEFINED> instruction: 0xf8dfd079
d001a844:	213b2464 	teqcs	fp, r4, ror #8
d001a848:	0460f8df 	strbteq	pc, [r0], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d001a84c:	4478447a 	ldrbtmi	r4, [r8], #-1146	; 0xfffffb86
d001a850:	fb56f7f8 	blx	0xd15d883a
d001a854:	2312e681 	tstcs	r2, #135266304	; 0x8100000
d001a858:	230ee7a1 	movwcs	lr, #59297	; 0xe7a1
d001a85c:	1c63e79f 	stclne	7, cr14, [r3], #-636	; 0xfffffd84
d001a860:	21009a0a 	tstcs	r0, sl, lsl #20
d001a864:	0b01f10b 	bleq	0xd0096c98
d001a868:	3238f8c9 	eorscc	pc, r8, #13172736	; 0xc90000
d001a86c:	3240f899 	subcc	pc, r0, #10027008	; 0x990000
d001a870:	9b0b930d 	blls	0xd02ff4ac
d001a874:	2404fb03 	strcs	pc, [r4], #-2819	; 0xfffff4fd
d001a878:	f5042230 			; <UNDEFINED> instruction: 0xf5042230
d001a87c:	f5042490 			; <UNDEFINED> instruction: 0xf5042490
d001a880:	f00660c7 			; <UNDEFINED> instruction: 0xf00660c7
d001a884:	9b0dfb3b 	blls	0xd0399578
d001a888:	3658f884 	ldrbcc	pc, [r8], -r4, lsl #17	; <UNPREDICTABLE>
d001a88c:	f884230b 			; <UNDEFINED> instruction: 0xf884230b
d001a890:	e7ac3659 	sbfx	r3, r9, #12, #13
d001a894:	fac4f7fd 	blx	0xcf158890
d001a898:	4620e7c6 	strtmi	lr, [r0], -r6, asr #15
d001a89c:	fd05f7fa 	stc2	7, cr15, [r5, #-1000]	; 0xfffffc18
d001a8a0:	f8dfe7c2 			; <UNDEFINED> instruction: 0xf8dfe7c2
d001a8a4:	213d440c 	teqcs	sp, ip, lsl #8
d001a8a8:	4620447c 			; <UNDEFINED> instruction: 0x4620447c
d001a8ac:	fb1af7f8 	blx	0xd06d8896
d001a8b0:	d0c02800 	sbcle	r2, r0, r0, lsl #16
d001a8b4:	6ae3b9ee 	bvs	0xcf909074
d001a8b8:	d01a2b7b 	andsle	r2, sl, fp, ror fp
d001a8bc:	4620990f 	strtmi	r9, [r0], -pc, lsl #18
d001a8c0:	fe58f7fc 	mrc2	7, 2, pc, cr8, cr12, {7}
d001a8c4:	f24b4620 	vmax.s8	d20, d11, d16
d001a8c8:	f7fa4103 			; <UNDEFINED> instruction: 0xf7fa4103
d001a8cc:	4629f8f1 			; <UNDEFINED> instruction: 0x4629f8f1
d001a8d0:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d001a8d4:	4620ffc5 	strtmi	pc, [r0], -r5, asr #31
d001a8d8:	6101f244 	tstvs	r1, r4, asr #4	; <UNPREDICTABLE>
d001a8dc:	f8e8f7fa 			; <UNDEFINED> instruction: 0xf8e8f7fa
d001a8e0:	f64b4620 			; <UNDEFINED> instruction: 0xf64b4620
d001a8e4:	f7fa4105 			; <UNDEFINED> instruction: 0xf7fa4105
d001a8e8:	9808f8e3 	stmdals	r8, {r0, r1, r5, r6, r7, fp, ip, sp, lr, pc}
d001a8ec:	fc60f7fa 	stc2l	7, cr15, [r0], #-1000	; 0xfffffc18
d001a8f0:	f8dfe7a1 			; <UNDEFINED> instruction: 0xf8dfe7a1
d001a8f4:	240093c0 	strcs	r9, [r0], #-960	; 0xfffffc40
d001a8f8:	210048ef 	smlattcs	r0, pc, r8, r4
d001a8fc:	447844f9 	ldrbtmi	r4, [r8], #-1273	; 0xfffffb07
d001a900:	fcd3f7fa 	ldc2l	7, cr15, [r3], {250}	; 0xfa
d001a904:	d10945a2 	smlatble	r9, r2, r5, r4
d001a908:	b176980f 	cmnlt	r6, pc, lsl #16
d001a90c:	46012300 	strmi	r2, [r1], -r0, lsl #6
d001a910:	4640462a 	strbmi	r4, [r0], -sl, lsr #12
d001a914:	f7ff9300 			; <UNDEFINED> instruction: 0xf7ff9300
d001a918:	e78cfc53 			; <UNDEFINED> instruction: 0xe78cfc53
d001a91c:	22001929 	andcs	r1, r0, #671744	; 0xa4000
d001a920:	34014648 	strcc	r4, [r1], #-1608	; 0xfffff9b8
d001a924:	f8fdf7fa 			; <UNDEFINED> instruction: 0xf8fdf7fa
d001a928:	2301e7ec 	movwcs	lr, #6124	; 0x17ec
d001a92c:	46294632 			; <UNDEFINED> instruction: 0x46294632
d001a930:	fb20f7ff 	blx	0xd0858936
d001a934:	212ce77f 			; <UNDEFINED> instruction: 0x212ce77f
d001a938:	fad4f7f8 	blx	0xcf558920
d001a93c:	f47f2800 			; <UNDEFINED> instruction: 0xf47f2800
d001a940:	e77eae75 			; <UNDEFINED> instruction: 0xe77eae75
d001a944:	f2406ae2 	vpmax.s8	q11, q8, q9
d001a948:	429a1301 	addsmi	r1, sl, #67108864	; 0x4000000
d001a94c:	2d00d007 	stccs	0, cr13, [r0, #-28]	; 0xffffffe4
d001a950:	ae04f43f 	cfmvdhrge	mvd4, pc
d001a954:	48da49d9 	ldmmi	sl, {r0, r3, r4, r6, r7, r8, fp, lr}^
d001a958:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d001a95c:	e9d4e64e 	ldmib	r4, {r1, r2, r3, r6, r9, sl, sp, lr, pc}^
d001a960:	46201206 	strtmi	r1, [r0], -r6, lsl #4
d001a964:	ff22f7f5 			; <UNDEFINED> instruction: 0xff22f7f5
d001a968:	daf02800 	ble	0xcfc24970
d001a96c:	447848d5 	ldrbtmi	r4, [r8], #-2261	; 0xfffff72b
d001a970:	ffc2f7f9 			; <UNDEFINED> instruction: 0xffc2f7f9
d001a974:	f0402800 			; <UNDEFINED> instruction: 0xf0402800
d001a978:	48d38171 	ldmmi	r3, {r0, r4, r5, r6, r8, pc}^
d001a97c:	f7f94478 			; <UNDEFINED> instruction: 0xf7f94478
d001a980:	2800ffbb 	stmdacs	r0, {r0, r1, r3, r4, r5, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d001a984:	2305d051 	movwcs	sp, #20561	; 0x5051
d001a988:	2d009307 	stccs	3, cr9, [r0, #-28]	; 0xffffffe4
d001a98c:	9508d1e2 	strls	sp, [r8, #-482]	; 0xfffffe1e
d001a990:	4ccf4bce 	vstmiami	pc, {d20-<overflow reg d58>}
d001a994:	447c447b 	ldrbtmi	r4, [ip], #-1147	; 0xfffffb85
d001a998:	3a10ee08 	bcc	0xd04561c0
d001a99c:	2392f504 	orrscs	pc, r2, #4, 10	; 0x1000000
d001a9a0:	9b08930a 	blls	0xd023f5d0
d001a9a4:	d0472b00 	suble	r2, r7, r0, lsl #22
d001a9a8:	ee18212a 	mufep	f2, f0, #2.0
d001a9ac:	f7f80a10 			; <UNDEFINED> instruction: 0xf7f80a10
d001a9b0:	2800fa99 	stmdacs	r0, {r0, r3, r4, r7, r9, fp, ip, sp, lr, pc}
d001a9b4:	212ad040 			; <UNDEFINED> instruction: 0x212ad040
d001a9b8:	0a10ee18 	beq	0xd0456220
d001a9bc:	fa92f7f8 	blx	0xce4d89a4
d001a9c0:	bf142800 	svclt	0x00142800
d001a9c4:	270a2713 	smladcs	sl, r3, r7, r2
d001a9c8:	f10d4ec2 			; <UNDEFINED> instruction: 0xf10d4ec2
d001a9cc:	447e0c40 	ldrbtmi	r0, [lr], #-3136	; 0xfffff3c0
d001a9d0:	0e18f106 	mnfeqe	f7, f6
d001a9d4:	b024f8d6 	ldrdlt	pc, [r4], -r6	; <UNPREDICTABLE>
d001a9d8:	a028f8d6 	ldrdge	pc, [r8], -r6	; <UNPREDICTABLE>
d001a9dc:	9030f896 	mlasls	r0, r6, r8, pc	; <UNPREDICTABLE>
d001a9e0:	8034f8d6 	ldrsbthi	pc, [r4], -r6	; <UNPREDICTABLE>
d001a9e4:	000fe8be 			; <UNDEFINED> instruction: 0x000fe8be
d001a9e8:	000fe8ac 	andeq	lr, pc, ip, lsr #17
d001a9ec:	000fe89e 	muleq	pc, lr, r8	; <UNPREDICTABLE>
d001a9f0:	000fe88c 	andeq	lr, pc, ip, lsl #17
d001a9f4:	f2404ab8 	vpmin.s8	d20, d16, d24
d001a9f8:	46301101 	ldrtmi	r1, [r0], -r1, lsl #2
d001a9fc:	f7f8447a 			; <UNDEFINED> instruction: 0xf7f8447a
d001aa00:	ab10fa7f 	blge	0xd0459404
d001aa04:	28009309 	stmdacs	r0, {r0, r3, r8, r9, ip, pc}
d001aa08:	ada7f43f 	cfstrsge	mvf15, [r7, #252]!	; 0xfc
d001aa0c:	b1afb1b5 			; <UNDEFINED> instruction: 0xb1afb1b5
d001aa10:	2b006db3 	blcs	0xd00360e4
d001aa14:	ada1f47f 	cfstrsge	mvf15, [r1, #508]!	; 0x1fc
d001aa18:	f8c64bb0 			; <UNDEFINED> instruction: 0xf8c64bb0
d001aa1c:	447b8068 	ldrbtmi	r8, [fp], #-104	; 0xffffff98
d001aa20:	a918e9c6 	ldmdbge	r8, {r1, r2, r6, r7, r8, fp, sp, lr, pc}
d001aa24:	3b16e9c6 	blcc	0xd05d5144
d001aa28:	48ade597 	stmiami	sp!, {r0, r1, r2, r4, r7, r8, sl, sp, lr, pc}
d001aa2c:	f7f94478 			; <UNDEFINED> instruction: 0xf7f94478
d001aa30:	2800ff63 	stmdacs	r0, {r0, r1, r5, r6, r8, r9, sl, fp, ip, sp, lr, pc}
d001aa34:	e78ad1a7 	str	sp, [sl, r7, lsr #3]
d001aa38:	e7c59f07 	strb	r9, [r5, r7, lsl #30]
d001aa3c:	4620215b 			; <UNDEFINED> instruction: 0x4620215b
d001aa40:	fa50f7f8 	blx	0xd1458a28
d001aa44:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d001aa48:	b16580b3 	strhlt	r8, [r5, #-3]!
d001aa4c:	2b006da3 	blcs	0xd00360e0
d001aa50:	ad83f47f 	cfstrsge	mvf15, [r3, #508]	; 0x1fc
d001aa54:	447b4ba3 	ldrbtmi	r4, [fp], #-2979	; 0xfffff45d
d001aa58:	8068f8c4 	rsbhi	pc, r8, r4, asr #17
d001aa5c:	3b16e9c4 	blcc	0xd05d5174
d001aa60:	a918e9c4 	ldmdbge	r8, {r2, r6, r7, r8, fp, sp, lr, pc}
d001aa64:	b137e579 	teqlt	r7, r9, ror r5
d001aa68:	2b006da3 	blcs	0xd00360fc
d001aa6c:	ad75f47f 	cfldrdge	mvd15, [r5, #-508]!	; 0xfffffe04
d001aa70:	447b4b9d 	ldrbtmi	r4, [fp], #-2973	; 0xfffff463
d001aa74:	6ae3e7f0 	bvs	0xcf914a3c
d001aa78:	f5a36a26 			; <UNDEFINED> instruction: 0xf5a36a26
d001aa7c:	2b017381 	blcs	0xd0077888
d001aa80:	b136d807 	teqlt	r6, r7, lsl #16
d001aa84:	f8d39b0a 			; <UNDEFINED> instruction: 0xf8d39b0a
d001aa88:	f1c33238 			; <UNDEFINED> instruction: 0xf1c33238
d001aa8c:	429e0340 	addsmi	r0, lr, #64, 6
d001aa90:	4b96d912 	blmi	0xce5d0ee0
d001aa94:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d001aa98:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d001aa9c:	4d94ad5e 	ldcmi	13, cr10, [r4, #376]	; 0x178
d001aaa0:	6a986a5c 	bvs	0xce635418
d001aaa4:	6b5a447d 	blvs	0xd16abca0
d001aaa8:	1030f893 	mlasne	r0, r3, r8, pc	; <UNPREDICTABLE>
d001aaac:	e9c3669a 	stmib	r3, {r1, r3, r4, r7, r9, sl, sp, lr}^
d001aab0:	e9c35416 	stmib	r3, {r1, r2, r4, sl, ip, lr}^
d001aab4:	e5500118 	ldrb	r0, [r0, #-280]	; 0xfffffee8
d001aab8:	f7f84620 			; <UNDEFINED> instruction: 0xf7f84620
d001aabc:	4a8df9f3 	bmi	0xce399290
d001aac0:	4620215d 			; <UNDEFINED> instruction: 0x4620215d
d001aac4:	f7f8447a 			; <UNDEFINED> instruction: 0xf7f8447a
d001aac8:	2800fa1b 	stmdacs	r0, {r0, r1, r3, r4, r9, fp, ip, sp, lr, pc}
d001aacc:	ad45f43f 	cfstrdge	mvd15, [r5, #-252]	; 0xffffff04
d001aad0:	f88d2309 			; <UNDEFINED> instruction: 0xf88d2309
d001aad4:	f8cd9058 			; <UNDEFINED> instruction: 0xf8cd9058
d001aad8:	9304a050 	movwls	sl, #16464	; 0x4050
d001aadc:	f8cdab18 			; <UNDEFINED> instruction: 0xf8cdab18
d001aae0:	f8cd805c 			; <UNDEFINED> instruction: 0xf8cd805c
d001aae4:	e913b04c 	ldmdb	r3, {r2, r3, r6, ip, sp, pc}
d001aae8:	e88d000f 	stm	sp, {r0, r1, r2, r3}
d001aaec:	9b09000f 	blls	0xd025ab30
d001aaf0:	f7f9cb0f 			; <UNDEFINED> instruction: 0xf7f9cb0f
d001aaf4:	6da3fa85 			; <UNDEFINED> instruction: 0x6da3fa85
d001aaf8:	2b004681 	blcs	0xd002c504
d001aafc:	ad2df47f 	cfstrsge	mvf15, [sp, #-508]!	; 0xfffffe04
d001ab00:	0b30f04f 	bleq	0xd0c56c44
d001ab04:	0801f04f 	stmdaeq	r1, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d001ab08:	2a92f504 	bcs	0xce4d7f20
d001ab0c:	fb0b9409 	blx	0xd02ffb3a
d001ab10:	f5034300 			; <UNDEFINED> instruction: 0xf5034300
d001ab14:	f8a32390 			; <UNDEFINED> instruction: 0xf8a32390
d001ab18:	45466662 	strbmi	r6, [r6, #-1634]	; 0xfffff99e
d001ab1c:	7238f8da 	eorsvc	pc, r8, #14286848	; 0xda0000
d001ab20:	f8dad12c 			; <UNDEFINED> instruction: 0xf8dad12c
d001ab24:	213d323c 	teqcs	sp, ip, lsr r2
d001ab28:	bf3842bb 	svclt	0x003842bb
d001ab2c:	723cf8ca 	eorsvc	pc, ip, #13238272	; 0xca0000
d001ab30:	447f4f71 	ldrbtmi	r4, [pc], #-3953	; 0xd001ab38
d001ab34:	f7f84638 			; <UNDEFINED> instruction: 0xf7f84638
d001ab38:	b1a0f9d5 	ldrdlt	pc, [r0, r5]!
d001ab3c:	21002600 	tstcs	r0, r0, lsl #12
d001ab40:	f7fa4638 			; <UNDEFINED> instruction: 0xf7fa4638
d001ab44:	eb09fbb2 	bl	0xd0299a14
d001ab48:	36010106 	strcc	r0, [r1], -r6, lsl #2
d001ab4c:	46382200 	ldrtmi	r2, [r8], -r0, lsl #4
d001ab50:	ffe7f7f9 			; <UNDEFINED> instruction: 0xffe7f7f9
d001ab54:	d1f645b0 	ldrhle	r4, [r6, #80]!	; 0x50
d001ab58:	464a2300 	strbmi	r2, [sl], -r0, lsl #6
d001ab5c:	464021ff 			; <UNDEFINED> instruction: 0x464021ff
d001ab60:	f7ff9300 			; <UNDEFINED> instruction: 0xf7ff9300
d001ab64:	4865fb2d 	stmdami	r5!, {r0, r2, r3, r5, r8, r9, fp, ip, sp, lr, pc}^
d001ab68:	6d834478 	cfstrsvs	mvf4, [r3, #480]	; 0x1e0
d001ab6c:	d06e2b00 	rsble	r2, lr, r0, lsl #22
d001ab70:	213b4a63 	teqcs	fp, r3, ror #20
d001ab74:	447a4863 	ldrbtmi	r4, [sl], #-2147	; 0xfffff79d
d001ab78:	e6694478 			; <UNDEFINED> instruction: 0xe6694478
d001ab7c:	22301c7b 	eorscs	r1, r0, #31488	; 0x7b00
d001ab80:	f1082100 			; <UNDEFINED> instruction: 0xf1082100
d001ab84:	f8ca0801 			; <UNDEFINED> instruction: 0xf8ca0801
d001ab88:	f89a3238 			; <UNDEFINED> instruction: 0xf89a3238
d001ab8c:	930b3240 	movwls	r3, #45632	; 0xb240
d001ab90:	fb0b9b09 	blx	0xd03017be
d001ab94:	f5073707 			; <UNDEFINED> instruction: 0xf5073707
d001ab98:	f5072790 			; <UNDEFINED> instruction: 0xf5072790
d001ab9c:	f00660c7 			; <UNDEFINED> instruction: 0xf00660c7
d001aba0:	9b0bf9ad 	blls	0xd031925c
d001aba4:	3658f887 	ldrbcc	pc, [r8], -r7, lsl #17	; <UNPREDICTABLE>
d001aba8:	f887230b 			; <UNDEFINED> instruction: 0xf887230b
d001abac:	e7b43659 	sbfx	r3, r9, #12, #21
d001abb0:	f8cdb2fb 			; <UNDEFINED> instruction: 0xf8cdb2fb
d001abb4:	f88da050 			; <UNDEFINED> instruction: 0xf88da050
d001abb8:	93049058 	movwls	r9, #16472	; 0x4058
d001abbc:	f8cdab18 			; <UNDEFINED> instruction: 0xf8cdab18
d001abc0:	f8cd805c 			; <UNDEFINED> instruction: 0xf8cd805c
d001abc4:	e913b04c 	ldmdb	r3, {r2, r3, r6, ip, sp, pc}
d001abc8:	e88d000f 	stm	sp, {r0, r1, r2, r3}
d001abcc:	9b09000f 	blls	0xd025ac10
d001abd0:	f7f9cb0f 			; <UNDEFINED> instruction: 0xf7f9cb0f
d001abd4:	6da3fa15 			; <UNDEFINED> instruction: 0x6da3fa15
d001abd8:	2b004606 	blcs	0xd002c3f8
d001abdc:	acbdf47f 	cfldrsge	mvf15, [sp], #508	; 0x1fc
d001abe0:	213d2330 	teqcs	sp, r0, lsr r3
d001abe4:	4300fb03 	movwmi	pc, #2819	; 0xb03	; <UNPREDICTABLE>
d001abe8:	f5034620 			; <UNDEFINED> instruction: 0xf5034620
d001abec:	f8832390 			; <UNDEFINED> instruction: 0xf8832390
d001abf0:	f7f85664 			; <UNDEFINED> instruction: 0xf7f85664
d001abf4:	b1e0f977 	mvnlt	pc, r7, ror r9	; <UNPREDICTABLE>
d001abf8:	d1092f13 	tstle	r9, r3, lsl pc
d001abfc:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d001ac00:	4841fe75 	stmdami	r1, {r0, r2, r4, r5, r6, r9, sl, fp, ip, sp, lr, pc}^
d001ac04:	46312200 	ldrtmi	r2, [r1], -r0, lsl #4
d001ac08:	f7f94478 			; <UNDEFINED> instruction: 0xf7f94478
d001ac0c:	e7aaff8a 	str	pc, [sl, sl, lsl #31]!
d001ac10:	f04f2f0a 			; <UNDEFINED> instruction: 0xf04f2f0a
d001ac14:	46200101 	strtmi	r0, [r0], -r1, lsl #2
d001ac18:	2204bf0c 	andcs	fp, r4, #12, 30	; 0x30
d001ac1c:	f7fb2201 			; <UNDEFINED> instruction: 0xf7fb2201
d001ac20:	2f05fad9 	svccs	0x0005fad9
d001ac24:	f24bd1ed 	vrhadd.s8	<illegal reg q14.5>, <illegal reg q13.5>, <illegal reg q14.5>
d001ac28:	462021c0 	strtmi	r2, [r0], -r0, asr #3
d001ac2c:	ff40f7f9 			; <UNDEFINED> instruction: 0xff40f7f9
d001ac30:	2d00e7e7 	stccs	7, cr14, [r0, #-924]	; 0xfffffc64
d001ac34:	6da3d097 	stcvs	0, cr13, [r3, #604]!	; 0x25c
d001ac38:	d1942b00 	orrsle	r2, r4, r0, lsl #22
d001ac3c:	f8c44b33 			; <UNDEFINED> instruction: 0xf8c44b33
d001ac40:	447b8068 	ldrbtmi	r8, [fp], #-104	; 0xffffff98
d001ac44:	a918e9c4 	ldmdbge	r8, {r2, r6, r7, r8, fp, sp, lr, pc}
d001ac48:	3b16e9c4 	blcc	0xd05d5360
d001ac4c:	212ce78b 	smlawbcs	ip, fp, r7, lr
d001ac50:	f948f7f8 			; <UNDEFINED> instruction: 0xf948f7f8
d001ac54:	f47f2800 			; <UNDEFINED> instruction: 0xf47f2800
d001ac58:	e789aea4 	str	sl, [r9, r4, lsr #29]
d001ac5c:	e6932301 	ldr	r2, [r3], r1, lsl #6
d001ac60:	0000d55c 	andeq	sp, r0, ip, asr r5
d001ac64:	0000d4c0 	andeq	sp, r0, r0, asr #9
d001ac68:	fffffd1b 			; <UNDEFINED> instruction: 0xfffffd1b
d001ac6c:	0000d49a 	muleq	r0, sl, r4
d001ac70:	0000d470 	andeq	sp, r0, r0, ror r4
d001ac74:	0000d440 	andeq	sp, r0, r0, asr #8
d001ac78:	fffffcd2 			; <UNDEFINED> instruction: 0xfffffcd2
d001ac7c:	0000d3ea 	andeq	sp, r0, sl, ror #7
d001ac80:	0000d3ae 	andeq	sp, r0, lr, lsr #7
d001ac84:	fffffbef 			; <UNDEFINED> instruction: 0xfffffbef
d001ac88:	0000d394 	muleq	r0, r4, r3
d001ac8c:	fffffb94 			; <UNDEFINED> instruction: 0xfffffb94
d001ac90:	fffffc2c 			; <UNDEFINED> instruction: 0xfffffc2c
d001ac94:	fffffc1d 			; <UNDEFINED> instruction: 0xfffffc1d
d001ac98:	0000d2d0 	ldrdeq	sp, [r0], -r0
d001ac9c:	0000d286 	andeq	sp, r0, r6, lsl #5
d001aca0:	0000d264 	andeq	sp, r0, r4, ror #4
d001aca4:	0000d25a 	andeq	sp, r0, sl, asr r2
d001aca8:	fffffb71 			; <UNDEFINED> instruction: 0xfffffb71
d001acac:	0000d246 	andeq	sp, r0, r6, asr #4
d001acb0:	0000d1ec 	andeq	sp, r0, ip, ror #3
d001acb4:	0000d198 	muleq	r0, r8, r1
d001acb8:	0000d196 	muleq	r0, r6, r1
d001acbc:	fffffa9a 			; <UNDEFINED> instruction: 0xfffffa9a
d001acc0:	0000d13a 	andeq	sp, r0, sl, lsr r1
d001acc4:	fffffa72 			; <UNDEFINED> instruction: 0xfffffa72
d001acc8:	fffffa6d 			; <UNDEFINED> instruction: 0xfffffa6d
d001accc:	0000d100 	andeq	sp, r0, r0, lsl #2
d001acd0:	0000d0fe 	strdeq	sp, [r0], -lr
d001acd4:	0000d0c6 	andeq	sp, r0, r6, asr #1
d001acd8:	fffffa30 			; <UNDEFINED> instruction: 0xfffffa30
d001acdc:	fffff9d4 			; <UNDEFINED> instruction: 0xfffff9d4
d001ace0:	ffff8e1a 			; <UNDEFINED> instruction: 0xffff8e1a
d001ace4:	fffff9f5 			; <UNDEFINED> instruction: 0xfffff9f5
d001ace8:	fffff9fc 			; <UNDEFINED> instruction: 0xfffff9fc
d001acec:	0000d000 	andeq	sp, r0, r0
d001acf0:	fffff9ee 			; <UNDEFINED> instruction: 0xfffff9ee
d001acf4:	fffff9ff 			; <UNDEFINED> instruction: 0xfffff9ff
d001acf8:	0000cf62 	andeq	ip, r0, r2, ror #30
d001acfc:	0000cf2c 	andeq	ip, r0, ip, lsr #30
d001ad00:	fffff991 			; <UNDEFINED> instruction: 0xfffff991
d001ad04:	0000cf1c 	andeq	ip, r0, ip, lsl pc
d001ad08:	0000ce8c 	andeq	ip, r0, ip, lsl #29
d001ad0c:	fffff8a5 			; <UNDEFINED> instruction: 0xfffff8a5

Disassembly of section .text.block.constprop.0:

d001ad30 <.text.block.constprop.0>:
d001ad30:	4c0db510 	cfstr32mi	mvfx11, [sp], {16}
d001ad34:	6da3447c 	cfstrsvs	mvf4, [r3, #496]!	; 0x1f0
d001ad38:	6ae3b92b 	bvs	0xcf9091ec
d001ad3c:	d0022b7d 	andle	r2, r2, sp, ror fp
d001ad40:	7f80f5b3 	svcvc	0x0080f5b3
d001ad44:	4a09d108 	bmi	0xd028f16c
d001ad48:	4809217d 	stmdami	r9, {r0, r2, r3, r4, r5, r6, r8, sp}
d001ad4c:	4478447a 	ldrbtmi	r4, [r8], #-1146	; 0xfffffb86
d001ad50:	4010e8bd 			; <UNDEFINED> instruction: 0x4010e8bd
d001ad54:	b8d4f7f8 	ldmlt	r4, {r3, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}^
d001ad58:	fbe8f7ff 	blx	0xcfa58d5e
d001ad5c:	d1ea2800 	mvnle	r2, r0, lsl #16
d001ad60:	f9b6f000 			; <UNDEFINED> instruction: 0xf9b6f000
d001ad64:	bf00e7e7 	svclt	0x0000e7e7
d001ad68:	0000cd60 	andeq	ip, r0, r0, ror #26
d001ad6c:	ffffffc0 			; <UNDEFINED> instruction: 0xffffffc0
d001ad70:	0000cd46 	andeq	ip, r0, r6, asr #26

Disassembly of section .text.statement.constprop.0:

d001b0d0 <.text.statement.constprop.0>:
d001b0d0:	4ff0e92d 	svcmi	0x00f0e92d
d001b0d4:	49c4f8df 	stmibmi	r4, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d001b0d8:	6da3447c 	cfstrsvs	mvf4, [r3, #496]!	; 0x1f0
d001b0dc:	8b02ed2d 	blhi	0xd00d6598
d001b0e0:	bb6bb089 	bllt	0xd1b0730c
d001b0e4:	2592f504 	ldrcs	pc, [r2, #1284]	; 0x504
d001b0e8:	3244f8d5 	subcc	pc, r4, #13959168	; 0xd50000
d001b0ec:	2b203301 	blcs	0xd0827cf8
d001b0f0:	3244f8c5 	subcc	pc, r4, #12910592	; 0xc50000
d001b0f4:	f8dfd904 			; <UNDEFINED> instruction: 0xf8dfd904
d001b0f8:	447919a8 	ldrbtmi	r1, [r9], #-2472	; 0xfffff658
d001b0fc:	e0674620 	rsb	r4, r7, r0, lsr #12
d001b100:	4620217b 			; <UNDEFINED> instruction: 0x4620217b
d001b104:	feeef7f7 	mcr2	7, 7, pc, cr14, cr7, {7}	; <UNPREDICTABLE>
d001b108:	b1f04606 	mvnslt	r4, r6, lsl #12
d001b10c:	3240f8d5 	subcc	pc, r0, #13959168	; 0xd50000
d001b110:	4238f8d5 	eorsmi	pc, r8, #13959168	; 0xd50000
d001b114:	f8c53301 			; <UNDEFINED> instruction: 0xf8c53301
d001b118:	f7ff3240 			; <UNDEFINED> instruction: 0xf7ff3240
d001b11c:	f8d5fe09 			; <UNDEFINED> instruction: 0xf8d5fe09
d001b120:	f8c53240 			; <UNDEFINED> instruction: 0xf8c53240
d001b124:	3b014238 	blcc	0xd006ba0c
d001b128:	3240f8c5 	subcc	pc, r0, #12910592	; 0xc50000
d001b12c:	3974f8df 	ldmdbcc	r4!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d001b130:	f503447b 			; <UNDEFINED> instruction: 0xf503447b
d001b134:	f8d32392 			; <UNDEFINED> instruction: 0xf8d32392
d001b138:	3a012244 	bcc	0xd0063a50
d001b13c:	2244f8c3 	subcs	pc, r4, #12779520	; 0xc30000
d001b140:	ecbdb009 	ldc	0, cr11, [sp], #36	; 0x24
d001b144:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d001b148:	f44f8ff0 			; <UNDEFINED> instruction: 0xf44f8ff0
d001b14c:	46207186 	strtmi	r7, [r0], -r6, lsl #3
d001b150:	fec8f7f7 	mcr2	7, 6, pc, cr8, cr7, {7}	; <UNPREDICTABLE>
d001b154:	b3504680 	cmplt	r0, #128, 12	; 0x8000000
d001b158:	fa88f7fe 	blx	0xce259158
d001b15c:	46204631 			; <UNDEFINED> instruction: 0x46204631
d001b160:	378ff504 	strcc	pc, [pc, r4, lsl #10]
d001b164:	fd59f7f9 	ldc2l	7, cr15, [r9, #-996]	; 0xfffffc1c
d001b168:	f7ff4605 			; <UNDEFINED> instruction: 0xf7ff4605
d001b16c:	f240ffb1 	vrecps.f32	d31, d16, d17
d001b170:	4620110d 	strtmi	r1, [r0], -sp, lsl #2
d001b174:	feb6f7f7 	mrc2	7, 5, pc, cr6, cr7, {7}
d001b178:	b1a04603 	lsllt	r4, r3, #12
d001b17c:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d001b180:	4680fd3d 			; <UNDEFINED> instruction: 0x4680fd3d
d001b184:	f8d74633 			; <UNDEFINED> instruction: 0xf8d74633
d001b188:	462921b8 			; <UNDEFINED> instruction: 0x462921b8
d001b18c:	f7fa6da0 			; <UNDEFINED> instruction: 0xf7fa6da0
d001b190:	f7ffff0b 			; <UNDEFINED> instruction: 0xf7ffff0b
d001b194:	4633ff9d 	shadd8mi	pc, r3, sp	; <UNPREDICTABLE>
d001b198:	21b8f8d7 			; <UNDEFINED> instruction: 0x21b8f8d7
d001b19c:	6da04641 	stcvs	6, cr4, [r0, #260]!	; 0x104
d001b1a0:	ff02f7fa 			; <UNDEFINED> instruction: 0xff02f7fa
d001b1a4:	f8d7e7c2 			; <UNDEFINED> instruction: 0xf8d7e7c2
d001b1a8:	462921b8 			; <UNDEFINED> instruction: 0x462921b8
d001b1ac:	f44fe7f7 	vst1.64	{d30}, [pc :256], r7
d001b1b0:	46207187 	strtmi	r7, [r0], -r7, lsl #3
d001b1b4:	fe96f7f7 	mrc2	7, 4, pc, cr6, cr7, {7}
d001b1b8:	d07a2800 	rsbsle	r2, sl, r0, lsl #16
d001b1bc:	324cf8d5 	subcc	pc, ip, #13959168	; 0xd50000
d001b1c0:	d1082b20 	tstle	r8, r0, lsr #22
d001b1c4:	18e0f8df 	stmiane	r0!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d001b1c8:	08e0f8df 	stmiaeq	r0!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d001b1cc:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d001b1d0:	f83cf7f5 			; <UNDEFINED> instruction: 0xf83cf7f5
d001b1d4:	f504e7aa 			; <UNDEFINED> instruction: 0xf504e7aa
d001b1d8:	f8d5338f 			; <UNDEFINED> instruction: 0xf8d5338f
d001b1dc:	f8d36250 			; <UNDEFINED> instruction: 0xf8d36250
d001b1e0:	f7fe71b8 			; <UNDEFINED> instruction: 0xf7fe71b8
d001b1e4:	4641fa43 	strbmi	pc, [r1], -r3, asr #20	; <UNPREDICTABLE>
d001b1e8:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d001b1ec:	f8d5fd16 			; <UNDEFINED> instruction: 0xf8d5fd16
d001b1f0:	4680324c 	strmi	r3, [r0], ip, asr #4
d001b1f4:	f8c53301 			; <UNDEFINED> instruction: 0xf8c53301
d001b1f8:	f504324c 			; <UNDEFINED> instruction: 0xf504324c
d001b1fc:	f8d52594 			; <UNDEFINED> instruction: 0xf8d52594
d001b200:	2b403254 	blcs	0xd1027b58
d001b204:	f8dfd132 			; <UNDEFINED> instruction: 0xf8dfd132
d001b208:	462018a8 	strtmi	r1, [r0], -r8, lsr #17
d001b20c:	f7f54479 			; <UNDEFINED> instruction: 0xf7f54479
d001b210:	f8dff81d 			; <UNDEFINED> instruction: 0xf8dff81d
d001b214:	f8df58a0 			; <UNDEFINED> instruction: 0xf8df58a0
d001b218:	447da8a0 	ldrbtmi	sl, [sp], #-2208	; 0xfffff760
d001b21c:	f50544fa 			; <UNDEFINED> instruction: 0xf50544fa
d001b220:	eb052992 	bl	0xd0165870
d001b224:	462804c6 	strtmi	r0, [r8], -r6, asr #9
d001b228:	324cf8d9 	subcc	pc, ip, #14221312	; 0xd90000
d001b22c:	2492f504 	ldrcs	pc, [r2], #1284	; 0x504
d001b230:	f5043b01 			; <UNDEFINED> instruction: 0xf5043b01
d001b234:	f8c97415 			; <UNDEFINED> instruction: 0xf8c97415
d001b238:	f7f9324c 			; <UNDEFINED> instruction: 0xf7f9324c
d001b23c:	2300fcdf 	movwcs	pc, #3295	; 0xcdf	; <UNPREDICTABLE>
d001b240:	463a4601 	ldrtmi	r4, [sl], -r1, lsl #12
d001b244:	f7fa6da8 			; <UNDEFINED> instruction: 0xf7fa6da8
d001b248:	f505feaf 			; <UNDEFINED> instruction: 0xf505feaf
d001b24c:	4641328f 	strbmi	r3, [r1], -pc, lsl #5
d001b250:	230046b0 	movwcs	r4, #1712	; 0x6b0
d001b254:	21b8f8d2 			; <UNDEFINED> instruction: 0x21b8f8d2
d001b258:	f7fa6da8 			; <UNDEFINED> instruction: 0xf7fa6da8
d001b25c:	f8d9fea5 			; <UNDEFINED> instruction: 0xf8d9fea5
d001b260:	45902250 	ldrmi	r2, [r0, #592]	; 0x250
d001b264:	f8c9d313 			; <UNDEFINED> instruction: 0xf8c9d313
d001b268:	e75f6250 			; <UNDEFINED> instruction: 0xe75f6250
d001b26c:	1c5a441c 	cfldrdne	mvd4, [sl], {28}
d001b270:	f5042301 			; <UNDEFINED> instruction: 0xf5042301
d001b274:	f8c52494 			; <UNDEFINED> instruction: 0xf8c52494
d001b278:	f8842254 			; <UNDEFINED> instruction: 0xf8842254
d001b27c:	f7ff3258 			; <UNDEFINED> instruction: 0xf7ff3258
d001b280:	f8d5ff27 			; <UNDEFINED> instruction: 0xf8d5ff27
d001b284:	3b013254 	blcc	0xd0067bdc
d001b288:	3254f8c5 	subscc	pc, r4, #12910592	; 0xc50000
d001b28c:	7923e7c1 	stmdbvc	r3!, {r0, r6, r7, r8, r9, sl, sp, lr, pc}
d001b290:	b1636821 	cmnlt	r3, r1, lsr #16
d001b294:	338ff505 	orrcc	pc, pc, #20971520	; 0x1400000
d001b298:	21b8f8d3 			; <UNDEFINED> instruction: 0x21b8f8d3
d001b29c:	f8da2300 			; <UNDEFINED> instruction: 0xf8da2300
d001b2a0:	f1080058 	cps	#24
d001b2a4:	34080801 	strcc	r0, [r8], #-2049	; 0xfffff7ff
d001b2a8:	fe7ef7fa 	mrc2	7, 3, pc, cr14, cr10, {7}
d001b2ac:	463ae7d7 			; <UNDEFINED> instruction: 0x463ae7d7
d001b2b0:	f240e7f4 	vaba.s8	q15, q8, q10
d001b2b4:	46201113 			; <UNDEFINED> instruction: 0x46201113
d001b2b8:	fe14f7f7 	mrc2	7, 0, pc, cr4, cr7, {7}
d001b2bc:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d001b2c0:	f8d580e8 			; <UNDEFINED> instruction: 0xf8d580e8
d001b2c4:	2b20324c 	blcs	0xd0827bfc
d001b2c8:	af7cf43f 	svcge	0x007cf43f
d001b2cc:	27ecf8df 	ubfxcs	pc, pc, #17, #13
d001b2d0:	46202128 	strtmi	r2, [r0], -r8, lsr #2
d001b2d4:	f7f7447a 			; <UNDEFINED> instruction: 0xf7f7447a
d001b2d8:	2800fe13 	stmdacs	r0, {r0, r1, r4, r9, sl, fp, ip, sp, lr, pc}
d001b2dc:	af26f43f 	svcge	0x0026f43f
d001b2e0:	3240f8d5 	subcc	pc, r0, #13959168	; 0xd50000
d001b2e4:	7238f8d5 	eorsvc	pc, r8, #13959168	; 0xd50000
d001b2e8:	f8d53301 			; <UNDEFINED> instruction: 0xf8d53301
d001b2ec:	f8c56250 			; <UNDEFINED> instruction: 0xf8c56250
d001b2f0:	f7ff3240 			; <UNDEFINED> instruction: 0xf7ff3240
d001b2f4:	b978f91b 	ldmdblt	r8!, {r0, r1, r3, r4, r8, fp, ip, sp, lr, pc}^
d001b2f8:	4620213b 			; <UNDEFINED> instruction: 0x4620213b
d001b2fc:	fdf2f7f7 	ldc2l	7, cr15, [r2, #988]!	; 0x3dc
d001b300:	f7feb950 			; <UNDEFINED> instruction: 0xf7feb950
d001b304:	f8dffa9f 			; <UNDEFINED> instruction: 0xf8dffa9f
d001b308:	f8df27b8 			; <UNDEFINED> instruction: 0xf8df27b8
d001b30c:	213b07b8 	teqcs	fp, r8	; <illegal shifter operand>
d001b310:	4478447a 	ldrbtmi	r4, [r8], #-1146	; 0xfffffb86
d001b314:	fdf4f7f7 	ldc2l	7, cr15, [r4, #988]!	; 0x3dc
d001b318:	47acf8df 	sbfxmi	pc, pc, #17, #13
d001b31c:	f504447c 			; <UNDEFINED> instruction: 0xf504447c
d001b320:	f8d3338f 			; <UNDEFINED> instruction: 0xf8d3338f
d001b324:	6ae391b8 	bvs	0xcf8ffa0c
d001b328:	f0002b3b 			; <UNDEFINED> instruction: 0xf0002b3b
d001b32c:	2202808c 	andcs	r8, r2, #140	; 0x8c
d001b330:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d001b334:	ff4ef7fa 			; <UNDEFINED> instruction: 0xff4ef7fa
d001b338:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d001b33c:	fc6df7f9 	stc2l	7, cr15, [sp], #-996	; 0xfffffc1c
d001b340:	f8df4680 			; <UNDEFINED> instruction: 0xf8df4680
d001b344:	213b4788 	teqcs	fp, r8, lsl #15
d001b348:	2784f8df 			; <UNDEFINED> instruction: 0x2784f8df
d001b34c:	447a447c 	ldrbtmi	r4, [sl], #-1148	; 0xfffffb84
d001b350:	f7f74620 			; <UNDEFINED> instruction: 0xf7f74620
d001b354:	4620fdd5 			; <UNDEFINED> instruction: 0x4620fdd5
d001b358:	fc50f7f9 	mrrc2	7, 15, pc, r0, cr9	; <UNPREDICTABLE>
d001b35c:	338ff504 	orrcc	pc, pc, #4, 10	; 0x1000000
d001b360:	f8d34682 			; <UNDEFINED> instruction: 0xf8d34682
d001b364:	6ae351b8 	bvs	0xcf8efa4c
d001b368:	d0012b29 	andle	r2, r1, r9, lsr #22
d001b36c:	fa6af7fe 	blx	0xd1ad936c
d001b370:	4760f8df 			; <UNDEFINED> instruction: 0x4760f8df
d001b374:	f8df2129 			; <UNDEFINED> instruction: 0xf8df2129
d001b378:	447c2760 	ldrbtmi	r2, [ip], #-1888	; 0xfffff8a0
d001b37c:	4620447a 			; <UNDEFINED> instruction: 0x4620447a
d001b380:	fdbef7f7 	ldc2	7, cr15, [lr, #988]!	; 0x3dc
d001b384:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d001b388:	464afc39 			; <UNDEFINED> instruction: 0x464afc39
d001b38c:	23004601 	movwcs	r4, #1537	; 0x601
d001b390:	f5046da0 			; <UNDEFINED> instruction: 0xf5046da0
d001b394:	f7fa2994 			; <UNDEFINED> instruction: 0xf7fa2994
d001b398:	f504fe07 			; <UNDEFINED> instruction: 0xf504fe07
d001b39c:	2300328f 	movwcs	r3, #655	; 0x28f
d001b3a0:	f8d24651 			; <UNDEFINED> instruction: 0xf8d24651
d001b3a4:	6da021b8 	stfvss	f2, [r0, #736]!	; 0x2e0
d001b3a8:	fdfef7fa 	ldc2l	7, cr15, [lr, #1000]!	; 0x3e8
d001b3ac:	2292f504 	addscs	pc, r2, #4, 10	; 0x1000000
d001b3b0:	324cf8d2 	subcc	pc, ip, #13762560	; 0xd20000
d001b3b4:	f8c23301 			; <UNDEFINED> instruction: 0xf8c23301
d001b3b8:	f8d9324c 			; <UNDEFINED> instruction: 0xf8d9324c
d001b3bc:	2b403254 	blcs	0xd1027d14
d001b3c0:	f8dfd144 			; <UNDEFINED> instruction: 0xf8dfd144
d001b3c4:	46201718 			; <UNDEFINED> instruction: 0x46201718
d001b3c8:	f7f44479 			; <UNDEFINED> instruction: 0xf7f44479
d001b3cc:	f8dfff3f 			; <UNDEFINED> instruction: 0xf8dfff3f
d001b3d0:	447c4710 	ldrbtmi	r4, [ip], #-1808	; 0xfffff8f0
d001b3d4:	2292f504 	addscs	pc, r2, #4, 10	; 0x1000000
d001b3d8:	f8d24620 			; <UNDEFINED> instruction: 0xf8d24620
d001b3dc:	3b01324c 	blcc	0xd0067d14
d001b3e0:	324cf8c2 	subcc	pc, ip, #12713984	; 0xc20000
d001b3e4:	fc0af7f9 	stc2	7, cr15, [sl], {249}	; 0xf9
d001b3e8:	46012300 	strmi	r2, [r1], -r0, lsl #6
d001b3ec:	6da0462a 	stcvs	6, cr4, [r0, #168]!	; 0xa8
d001b3f0:	fddaf7fa 	ldc2l	7, cr15, [sl, #1000]	; 0x3e8
d001b3f4:	0f00f1b8 	svceq	0x0000f1b8
d001b3f8:	f504d008 			; <UNDEFINED> instruction: 0xf504d008
d001b3fc:	2300328f 	movwcs	r3, #655	; 0x28f
d001b400:	6da04641 	stcvs	6, cr4, [r0, #260]!	; 0x104
d001b404:	21b8f8d2 			; <UNDEFINED> instruction: 0x21b8f8d2
d001b408:	fdcef7fa 	stc2l	7, cr15, [lr, #1000]	; 0x3e8
d001b40c:	f8df00f4 			; <UNDEFINED> instruction: 0xf8df00f4
d001b410:	f8df86d4 			; <UNDEFINED> instruction: 0xf8df86d4
d001b414:	46b2b6d4 	ssatmi	fp, #19, r4, asr #13
d001b418:	2492f504 	ldrcs	pc, [r2], #1284	; 0x504
d001b41c:	44fb44f8 	ldrbtmi	r4, [fp], #1272	; 0x4f8
d001b420:	7415f504 	ldrvc	pc, [r5], #-1284	; 0xfffffafc
d001b424:	2992f508 	ldmibcs	r2, {r3, r8, sl, ip, sp, lr, pc}
d001b428:	f8d94444 			; <UNDEFINED> instruction: 0xf8d94444
d001b42c:	45922250 	ldrmi	r2, [r2, #592]	; 0x250
d001b430:	f8d9d31d 			; <UNDEFINED> instruction: 0xf8d9d31d
d001b434:	f8c93240 			; <UNDEFINED> instruction: 0xf8c93240
d001b438:	3b016250 	blcc	0xd0073d80
d001b43c:	7238f8c9 	eorsvc	pc, r8, #13172736	; 0xc90000
d001b440:	3240f8c9 	subcc	pc, r0, #13172736	; 0xc90000
d001b444:	f04fe672 			; <UNDEFINED> instruction: 0xf04fe672
d001b448:	e77a0800 	ldrb	r0, [sl, -r0, lsl #16]!
d001b44c:	1c5a441c 	cfldrdne	mvd4, [sl], {28}
d001b450:	f5042301 			; <UNDEFINED> instruction: 0xf5042301
d001b454:	f8c92494 			; <UNDEFINED> instruction: 0xf8c92494
d001b458:	f8842254 			; <UNDEFINED> instruction: 0xf8842254
d001b45c:	f7ff3258 			; <UNDEFINED> instruction: 0xf7ff3258
d001b460:	f8d9fe37 			; <UNDEFINED> instruction: 0xf8d9fe37
d001b464:	3b013254 	blcc	0xd0067dbc
d001b468:	3254f8c9 	subscc	pc, r4, #13172736	; 0xc90000
d001b46c:	7923e7af 	stmdbvc	r3!, {r0, r1, r2, r3, r5, r7, r8, r9, sl, sp, lr, pc}
d001b470:	b1636821 	cmnlt	r3, r1, lsr #16
d001b474:	338ff508 	orrcc	pc, pc, #8, 10	; 0x2000000
d001b478:	21b8f8d3 			; <UNDEFINED> instruction: 0x21b8f8d3
d001b47c:	f8db2300 			; <UNDEFINED> instruction: 0xf8db2300
d001b480:	f10a0058 	cpsie	f,#24
d001b484:	34080a01 	strcc	r0, [r8], #-2561	; 0xfffff5ff
d001b488:	fd8ef7fa 	stc2	7, cr15, [lr, #1000]	; 0x3e8
d001b48c:	462ae7cd 	strtmi	lr, [sl], -sp, asr #15
d001b490:	f44fe7f4 	vst1.64	{d30}, [pc :256], r4
d001b494:	4620718a 	strtmi	r7, [r0], -sl, lsl #3
d001b498:	fd24f7f7 	stc2	7, cr15, [r4, #-988]!	; 0xfffffc24
d001b49c:	28004607 	stmdacs	r0, {r0, r1, r2, r9, sl, lr}
d001b4a0:	8203f000 	andhi	pc, r3, #0
d001b4a4:	2394f504 	orrscs	pc, r4, #4, 10	; 0x1000000
d001b4a8:	3254f8d3 	subscc	pc, r4, #13828096	; 0xd30000
d001b4ac:	d1032b40 	tstle	r3, r0, asr #22
d001b4b0:	1638f8df 			; <UNDEFINED> instruction: 0x1638f8df
d001b4b4:	e6214479 			; <UNDEFINED> instruction: 0xe6214479
d001b4b8:	2396f504 	orrscs	pc, r6, #4, 10	; 0x1000000
d001b4bc:	329cf8d3 	addscc	pc, ip, #13828096	; 0xd30000
d001b4c0:	7f80f5b3 	svcvc	0x0080f5b3
d001b4c4:	d1039300 	mrsle	r9, SP_svc
d001b4c8:	1624f8df 			; <UNDEFINED> instruction: 0x1624f8df
d001b4cc:	e6154479 			; <UNDEFINED> instruction: 0xe6154479
d001b4d0:	3238f8d5 	eorscc	pc, r8, #13959168	; 0xd50000
d001b4d4:	93012b40 	movwls	r2, #6976	; 0x1b40
d001b4d8:	f8dfd110 			; <UNDEFINED> instruction: 0xf8dfd110
d001b4dc:	f8df1618 			; <UNDEFINED> instruction: 0xf8df1618
d001b4e0:	44790618 	ldrbtmi	r0, [r9], #-1560	; 0xfffff9e8
d001b4e4:	f7f44478 			; <UNDEFINED> instruction: 0xf7f44478
d001b4e8:	f8dffeb1 			; <UNDEFINED> instruction: 0xf8dffeb1
d001b4ec:	9a013610 	bls	0xd0068d34
d001b4f0:	f503447b 			; <UNDEFINED> instruction: 0xf503447b
d001b4f4:	f8c32392 			; <UNDEFINED> instruction: 0xf8c32392
d001b4f8:	e6172238 			; <UNDEFINED> instruction: 0xe6172238
d001b4fc:	4600f8df 			; <UNDEFINED> instruction: 0x4600f8df
d001b500:	f8df2128 			; <UNDEFINED> instruction: 0xf8df2128
d001b504:	447c2600 	ldrbtmi	r2, [ip], #-1536	; 0xfffffa00
d001b508:	f504447a 			; <UNDEFINED> instruction: 0xf504447a
d001b50c:	46202394 			; <UNDEFINED> instruction: 0x46202394
d001b510:	3298f8d3 	addscc	pc, r8, #13828096	; 0xd30000
d001b514:	f7f79302 			; <UNDEFINED> instruction: 0xf7f79302
d001b518:	2800fcf3 	stmdacs	r0, {r0, r1, r4, r5, r6, r7, sl, fp, ip, sp, lr, pc}
d001b51c:	2201d0e5 	andcs	sp, r1, #229	; 0xe5
d001b520:	46114620 	ldrmi	r4, [r1], -r0, lsr #12
d001b524:	fe56f7fa 	mrc2	7, 2, pc, cr6, cr10, {7}
d001b528:	25dcf8df 	ldrbcs	pc, [ip, #2271]	; 0x8df	; <UNPREDICTABLE>
d001b52c:	46202129 	strtmi	r2, [r0], -r9, lsr #2
d001b530:	f7f7447a 			; <UNDEFINED> instruction: 0xf7f7447a
d001b534:	2800fce5 	stmdacs	r0, {r0, r2, r5, r6, r7, sl, fp, ip, sp, lr, pc}
d001b538:	f8dfd0d7 			; <UNDEFINED> instruction: 0xf8dfd0d7
d001b53c:	217b25d0 	ldrsbcs	r2, [fp, #-80]!	; 0xffffffb0
d001b540:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d001b544:	fcdcf7f7 	ldc2l	7, cr15, [ip], {247}	; 0xf7
d001b548:	d0ce2800 	sbcle	r2, lr, r0, lsl #16
d001b54c:	2492f504 	ldrcs	pc, [r2], #1284	; 0x504
d001b550:	f8d42100 			; <UNDEFINED> instruction: 0xf8d42100
d001b554:	f8d48238 			; <UNDEFINED> instruction: 0xf8d48238
d001b558:	f108223c 			; <UNDEFINED> instruction: 0xf108223c
d001b55c:	42930301 	addsmi	r0, r3, #67108864	; 0x4000000
d001b560:	3238f8c4 	eorscc	pc, r8, #196, 16	; 0xc40000
d001b564:	0230f04f 	eorseq	pc, r0, #79	; 0x4f
d001b568:	f8c4bf88 			; <UNDEFINED> instruction: 0xf8c4bf88
d001b56c:	f8df323c 			; <UNDEFINED> instruction: 0xf8df323c
d001b570:	447c45a0 	ldrbtmi	r4, [ip], #-1440	; 0xfffffa60
d001b574:	4508fb02 	strmi	pc, [r8, #-2818]	; 0xfffff4fe
d001b578:	2692f504 	ldrcs	pc, [r2], r4, lsl #10
d001b57c:	2590f505 	ldrcs	pc, [r0, #1285]	; 0x505
d001b580:	7240f896 	subvc	pc, r0, #9830400	; 0x960000
d001b584:	60c7f505 	sbcvs	pc, r7, r5, lsl #10
d001b588:	fcb8f005 	ldc2	0, cr15, [r8], #20
d001b58c:	2200230b 	andcs	r2, r0, #738197504	; 0x2c000000
d001b590:	f8854641 			; <UNDEFINED> instruction: 0xf8854641
d001b594:	46203659 			; <UNDEFINED> instruction: 0x46203659
d001b598:	7658f885 	ldrbvc	pc, [r8], -r5, lsl #17	; <UNPREDICTABLE>
d001b59c:	fac1f7f9 	blx	0xcf099588
d001b5a0:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d001b5a4:	f8d6fb2b 			; <UNDEFINED> instruction: 0xf8d6fb2b
d001b5a8:	f5043240 			; <UNDEFINED> instruction: 0xf5043240
d001b5ac:	ee082294 	mcr	2, 0, r2, cr8, cr4, {4}
d001b5b0:	33010a10 	movwcc	r0, #6672	; 0x1a10
d001b5b4:	3240f8c6 	subcc	pc, r0, #12976128	; 0xc60000
d001b5b8:	f8d22600 			; <UNDEFINED> instruction: 0xf8d22600
d001b5bc:	46373254 			; <UNDEFINED> instruction: 0x46373254
d001b5c0:	1c59441c 	cfldrdne	mvd4, [r9], {28}
d001b5c4:	f5042302 			; <UNDEFINED> instruction: 0xf5042302
d001b5c8:	f8c22494 			; <UNDEFINED> instruction: 0xf8c22494
d001b5cc:	f8841254 			; <UNDEFINED> instruction: 0xf8841254
d001b5d0:	f8df3258 			; <UNDEFINED> instruction: 0xf8df3258
d001b5d4:	447b3540 	ldrbtmi	r3, [fp], #-1344	; 0xfffffac0
d001b5d8:	2595f503 	ldrcs	pc, [r5, #1283]	; 0x503
d001b5dc:	7528f505 	strvc	pc, [r8, #-1285]!	; 0xfffffafb
d001b5e0:	4534f8df 	ldrmi	pc, [r4, #-2271]!	; 0xfffff721
d001b5e4:	6da3447c 	cfstrsvs	mvf4, [r3, #496]!	; 0x1f0
d001b5e8:	6ae3bb23 	bvs	0xcf90a27c
d001b5ec:	d0212b7d 	eorle	r2, r1, sp, ror fp
d001b5f0:	7f80f5b3 	svcvc	0x0080f5b3
d001b5f4:	f240d01e 	vqadd.s8	d29, d0, d14
d001b5f8:	42931215 	addsmi	r1, r3, #1342177281	; 0x50000001
d001b5fc:	80f4f040 	rscshi	pc, r4, r0, asr #32
d001b600:	f7f74620 			; <UNDEFINED> instruction: 0xf7f74620
d001b604:	6a63fc4f 	bvs	0xd191a748
d001b608:	4620212d 	strtmi	r2, [r0], -sp, lsr #2
d001b60c:	6aa39303 	bvs	0xce900220
d001b610:	a030f894 	mlasge	r0, r4, r8, pc	; <UNPREDICTABLE>
d001b614:	6b639304 	blvs	0xd190022c
d001b618:	f7f79305 			; <UNDEFINED> instruction: 0xf7f79305
d001b61c:	6ae3fc63 	bvs	0xcf91a7b0
d001b620:	7381f5a3 	orrvc	pc, r1, #683671552	; 0x28c00000
d001b624:	d9792b01 	ldmdble	r9!, {r0, r8, r9, fp, sp}^
d001b628:	14f0f8df 	ldrbtne	pc, [r0], #2271	; 0x8df	; <UNPREDICTABLE>
d001b62c:	44794620 	ldrbtmi	r4, [r9], #-1568	; 0xfffff9e0
d001b630:	fe0cf7f4 	mcr2	7, 0, pc, cr12, cr4, {7}	; <UNPREDICTABLE>
d001b634:	44e8f8df 	strbtmi	pc, [r8], #2271	; 0x8df	; <UNPREDICTABLE>
d001b638:	f8df217d 			; <UNDEFINED> instruction: 0xf8df217d
d001b63c:	447c24e8 	ldrbtmi	r2, [ip], #-1256	; 0xfffffb18
d001b640:	4620447a 			; <UNDEFINED> instruction: 0x4620447a
d001b644:	2b96f504 	blcs	0xce5d8a5c
d001b648:	fc5af7f7 	mrrc2	7, 15, pc, sl, cr7	; <UNPREDICTABLE>
d001b64c:	2294f504 	addscs	pc, r4, #4, 10	; 0x1000000
d001b650:	f8d24620 			; <UNDEFINED> instruction: 0xf8d24620
d001b654:	3b013254 	blcc	0xd0067fac
d001b658:	3254f8c2 	subscc	pc, r4, #12713984	; 0xc20000
d001b65c:	2292f504 	addscs	pc, r2, #4, 10	; 0x1000000
d001b660:	3240f8d2 	subcc	pc, r0, #13762560	; 0xd20000
d001b664:	f8c23b01 			; <UNDEFINED> instruction: 0xf8c23b01
d001b668:	f7f93240 			; <UNDEFINED> instruction: 0xf7f93240
d001b66c:	f504fac7 			; <UNDEFINED> instruction: 0xf504fac7
d001b670:	2300328f 	movwcs	r3, #655	; 0x28f
d001b674:	ee184681 	cfmsub32	mvax4, mvfx4, mvfx8, mvfx1
d001b678:	f8d21a10 			; <UNDEFINED> instruction: 0xf8d21a10
d001b67c:	6da021b8 	stfvss	f2, [r0, #736]!	; 0x2e0
d001b680:	fc92f7fa 	ldc2	7, cr15, [r2], {250}	; 0xfa
d001b684:	eb049b00 	bl	0xd014228c
d001b688:	469a05c3 	ldrmi	r0, [sl], r3, asr #11
d001b68c:	2595f505 	ldrcs	pc, [r5, #1285]	; 0x505
d001b690:	7527f505 	strvc	pc, [r7, #-1285]!	; 0xfffffafb
d001b694:	329cf8db 	addscc	pc, ip, #14352384	; 0xdb0000
d001b698:	459a3508 	ldrmi	r3, [sl, #1288]	; 0x508
d001b69c:	80d6f0c0 	sbcshi	pc, r6, r0, asr #1
d001b6a0:	2f004620 	svccs	0x00004620
d001b6a4:	80f4f000 	rscshi	pc, r4, r0
d001b6a8:	faa8f7f9 	blx	0xcea59694
d001b6ac:	6da04601 	stcvs	6, cr4, [r0, #4]!
d001b6b0:	23002400 	movwcs	r2, #1024	; 0x400
d001b6b4:	f7fa463a 			; <UNDEFINED> instruction: 0xf7fa463a
d001b6b8:	f8dffc77 			; <UNDEFINED> instruction: 0xf8dffc77
d001b6bc:	4649546c 	strbmi	r5, [r9], -ip, ror #8
d001b6c0:	f505447d 			; <UNDEFINED> instruction: 0xf505447d
d001b6c4:	6da8338f 	stcvs	3, cr3, [r8, #572]!	; 0x23c
d001b6c8:	a1b8f8d3 			; <UNDEFINED> instruction: 0xa1b8f8d3
d001b6cc:	46522300 	ldrbmi	r2, [r2], -r0, lsl #6
d001b6d0:	fc6af7fa 	stc2l	7, cr15, [sl], #-1000	; 0xfffffc18
d001b6d4:	2300b12c 	movwcs	fp, #300	; 0x12c
d001b6d8:	46214652 			; <UNDEFINED> instruction: 0x46214652
d001b6dc:	f7fa6da8 			; <UNDEFINED> instruction: 0xf7fa6da8
d001b6e0:	f8dffc63 			; <UNDEFINED> instruction: 0xf8dffc63
d001b6e4:	9d024448 	cfstrsls	mvf4, [r2, #-288]	; 0xfffffee0
d001b6e8:	f504447c 			; <UNDEFINED> instruction: 0xf504447c
d001b6ec:	f5082894 			; <UNDEFINED> instruction: 0xf5082894
d001b6f0:	f8d87727 			; <UNDEFINED> instruction: 0xf8d87727
d001b6f4:	42952298 	addsmi	r2, r5, #152, 4	; 0x80000009
d001b6f8:	80cef0c0 	sbchi	pc, lr, r0, asr #1
d001b6fc:	f5049a02 			; <UNDEFINED> instruction: 0xf5049a02
d001b700:	f8c82396 			; <UNDEFINED> instruction: 0xf8c82396
d001b704:	9a002298 	bls	0xd002416c
d001b708:	229cf8c3 	addscs	pc, ip, #12779520	; 0xc30000
d001b70c:	f47f2e00 			; <UNDEFINED> instruction: 0xf47f2e00
d001b710:	f8dfaeec 			; <UNDEFINED> instruction: 0xf8dfaeec
d001b714:	4620141c 			; <UNDEFINED> instruction: 0x4620141c
d001b718:	e6e44479 	uxtab	r4, r4, r9, ror #8
d001b71c:	9020f8d4 	ldrdls	pc, [r0], -r4	; <UNPREDICTABLE>
d001b720:	f1c9b108 			; <UNDEFINED> instruction: 0xf1c9b108
d001b724:	f8df0900 			; <UNDEFINED> instruction: 0xf8df0900
d001b728:	447c440c 	ldrbtmi	r4, [ip], #-1036	; 0xfffffbf4
d001b72c:	f7f74620 			; <UNDEFINED> instruction: 0xf7f74620
d001b730:	f8dffbb9 			; <UNDEFINED> instruction: 0xf8dffbb9
d001b734:	213a2404 	teqcs	sl, r4, lsl #8
d001b738:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d001b73c:	fbe0f7f7 	blx	0xcf859722
d001b740:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001b744:	6ea2af77 	mcrvs	15, 5, sl, cr2, cr7, {3}
d001b748:	2396f504 	orrscs	pc, r6, #4, 10	; 0x1000000
d001b74c:	920649fb 	andls	r4, r6, #4112384	; 0x3ec000
d001b750:	f8d34479 			; <UNDEFINED> instruction: 0xf8d34479
d001b754:	9a00329c 	bls	0xd00281cc
d001b758:	e9d49107 	ldmib	r4, {r0, r1, r2, r8, ip, pc}^
d001b75c:	e9d40e16 	ldmib	r4, {r1, r2, r4, r9, sl, fp}^
d001b760:	2400cb18 	strcs	ip, [r0], #-2840	; 0xfffff4e8
d001b764:	d31b429a 	tstle	fp, #-1610612727	; 0xa0000009
d001b768:	4af5b13c 	bmi	0xcfd87c60
d001b76c:	447a9906 	ldrbtmi	r9, [sl], #-2310	; 0xfffff6fa
d001b770:	0e16e9c2 	vnmlaeq.f16	s28, s13, s4	; <UNPREDICTABLE>
d001b774:	cb18e9c2 	blgt	0xd0655e84
d001b778:	f5b36691 			; <UNDEFINED> instruction: 0xf5b36691
d001b77c:	d11f7f80 	tstle	pc, r0, lsl #31
d001b780:	447b4bf0 	ldrbtmi	r4, [fp], #-3056	; 0xfffff410
d001b784:	b94a6d9a 	stmdblt	sl, {r1, r3, r4, r7, r8, sl, fp, sp, lr}^
d001b788:	447a4aef 	ldrbtmi	r4, [sl], #-2799	; 0xfffff511
d001b78c:	9a03659a 	bls	0xd00f4dfc
d001b790:	9a0465da 	bls	0xd0134f00
d001b794:	2a18e9c3 	bcs	0xd0655ea8
d001b798:	669a9a05 	ldrvs	r9, [sl], r5, lsl #20
d001b79c:	e71f3601 	ldr	r3, [pc, -r1, lsl #12]
d001b7a0:	1032f855 	eorsne	pc, r2, r5, asr r8	; <UNPREDICTABLE>
d001b7a4:	d1094549 	tstle	r9, r9, asr #10
d001b7a8:	9905b940 	stmdbls	r5, {r6, r8, fp, ip, sp, pc}
d001b7ac:	f8dd46d3 			; <UNDEFINED> instruction: 0xf8dd46d3
d001b7b0:	2401c010 	strcs	ip, [r1], #-16
d001b7b4:	e00cf8dd 	ldrd	pc, [ip], -sp
d001b7b8:	91069807 	tstls	r6, r7, lsl #16
d001b7bc:	e7d13201 	ldrb	r3, [r1, r1, lsl #4]
d001b7c0:	4ae21c58 	bmi	0xcf8a2928
d001b7c4:	4315f503 	tstmi	r5, #12582912	; 0xc00000	; <UNPREDICTABLE>
d001b7c8:	3353447a 	cmpcc	r3, #2046820352	; 0x7a000000
d001b7cc:	2196f502 	orrscs	pc, r6, r2, lsl #10
d001b7d0:	03c3eb02 	biceq	lr, r3, #2048	; 0x800
d001b7d4:	328ff502 	addcc	pc, pc, #8388608	; 0x800000
d001b7d8:	029cf8c1 	addseq	pc, ip, #12648448	; 0xc10000
d001b7dc:	21b8f8d2 			; <UNDEFINED> instruction: 0x21b8f8d2
d001b7e0:	9008f8c3 	andls	pc, r8, r3, asr #17
d001b7e4:	e7d9605a 			; <UNDEFINED> instruction: 0xe7d9605a
d001b7e8:	718bf44f 	orrvc	pc, fp, pc, asr #8
d001b7ec:	f7f74620 			; <UNDEFINED> instruction: 0xf7f74620
d001b7f0:	b318fb79 	tstlt	r8, #123904	; 0x1e400	; <UNPREDICTABLE>
d001b7f4:	213a4ad6 	teqcs	sl, r6	; <illegal shifter operand>
d001b7f8:	46206a63 	strtmi	r6, [r0], -r3, ror #20
d001b7fc:	f8d4447a 			; <UNDEFINED> instruction: 0xf8d4447a
d001b800:	f894b028 			; <UNDEFINED> instruction: 0xf894b028
d001b804:	f8d4a030 			; <UNDEFINED> instruction: 0xf8d4a030
d001b808:	93039034 	movwls	r9, #12340	; 0x3034
d001b80c:	fb78f7f7 	blx	0xd1e597f2
d001b810:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001b814:	b167af0f 	cmnlt	r7, pc, lsl #30
d001b818:	2a006da2 	bcs	0xd0036ea8
d001b81c:	4acdd1be 	bmi	0xcf38ff1c
d001b820:	447a9b03 	ldrbtmi	r9, [sl], #-2819	; 0xfffff4fd
d001b824:	9068f8c4 	rsbls	pc, r8, r4, asr #17
d001b828:	65a265e3 	strvs	r6, [r2, #1507]!	; 0x5e3
d001b82c:	ba18e9c4 	blt	0xd0655f44
d001b830:	f504e7b4 			; <UNDEFINED> instruction: 0xf504e7b4
d001b834:	f8d4348f 			; <UNDEFINED> instruction: 0xf8d4348f
d001b838:	e7af71b8 			; <UNDEFINED> instruction: 0xe7af71b8
d001b83c:	fe76f7fe 	mrc2	7, 3, pc, cr6, cr14, {7}
d001b840:	f47f2800 			; <UNDEFINED> instruction: 0xf47f2800
d001b844:	f7ffaecd 			; <UNDEFINED> instruction: 0xf7ffaecd
d001b848:	e6c9fc43 	strb	pc, [r9], r3, asr #24	; <UNPREDICTABLE>
d001b84c:	46412200 	strbmi	r2, [r1], -r0, lsl #4
d001b850:	f10a4620 			; <UNDEFINED> instruction: 0xf10a4620
d001b854:	f7f90a01 			; <UNDEFINED> instruction: 0xf7f90a01
d001b858:	f855f949 			; <UNDEFINED> instruction: 0xf855f949
d001b85c:	21012c04 	tstcs	r1, r4, lsl #24
d001b860:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d001b864:	f244fce0 	sha1c.32	<illegal reg q15.5>, q10, q8
d001b868:	46202188 	strtmi	r2, [r0], -r8, lsl #3
d001b86c:	f920f7f9 			; <UNDEFINED> instruction: 0xf920f7f9
d001b870:	1101f24d 	tstne	r1, sp, asr #4	; <UNPREDICTABLE>
d001b874:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d001b878:	4620f91b 			; <UNDEFINED> instruction: 0x4620f91b
d001b87c:	f9bef7f9 			; <UNDEFINED> instruction: 0xf9bef7f9
d001b880:	46012300 	strmi	r2, [r1], -r0, lsl #6
d001b884:	2c08f855 	stccs	8, cr15, [r8], {85}	; 0x55
d001b888:	f7fa6da0 			; <UNDEFINED> instruction: 0xf7fa6da0
d001b88c:	e701fb8d 	str	pc, [r1, -sp, lsl #23]
d001b890:	f9b4f7f9 			; <UNDEFINED> instruction: 0xf9b4f7f9
d001b894:	e7104604 	ldr	r4, [r0, -r4, lsl #12]
d001b898:	1025f857 	eorne	pc, r5, r7, asr r8	; <UNPREDICTABLE>
d001b89c:	46522300 	ldrbmi	r2, [r2], -r0, lsl #6
d001b8a0:	35016da0 	strcc	r6, [r1, #-3488]	; 0xfffff260
d001b8a4:	fb80f7fa 	blx	0xce059896
d001b8a8:	6ae6e723 	bvs	0xcf9d553c
d001b8ac:	7288f46f 	addvc	pc, r8, #1862270976	; 0x6f000000
d001b8b0:	2b0118b3 	blcs	0xd0061b84
d001b8b4:	f240d866 	vadd.i8	<illegal reg q14.5>, q0, q11
d001b8b8:	429e1311 	addsmi	r1, lr, #1140850688	; 0x44000000
d001b8bc:	f8d5d00e 			; <UNDEFINED> instruction: 0xf8d5d00e
d001b8c0:	b1ab324c 			; <UNDEFINED> instruction: 0xb1ab324c
d001b8c4:	447848a4 	ldrbtmi	r4, [r8], #-2212	; 0xfffff75c
d001b8c8:	2392f500 	orrscs	pc, r2, #0, 10
d001b8cc:	3250f8d3 	subscc	pc, r0, #13828096	; 0xd30000
d001b8d0:	7f00f5b3 	svcvc	0x0000f5b3
d001b8d4:	49a1d123 	stmibmi	r1!, {r0, r1, r5, r8, ip, lr, pc}
d001b8d8:	e4794479 	ldrbt	r4, [r9], #-1145	; 0xfffffb87
d001b8dc:	2494f504 	ldrcs	pc, [r4], #1284	; 0x504
d001b8e0:	3254f8d4 	subscc	pc, r4, #212, 16	; 0xd40000
d001b8e4:	499eb93b 	ldmibmi	lr, {r0, r1, r3, r4, r5, r8, fp, ip, sp, pc}
d001b8e8:	489e4479 	ldmmi	lr, {r0, r3, r4, r5, r6, sl, lr}
d001b8ec:	e46f4478 	strbt	r4, [pc], #-1144	; 0xd001b8f4
d001b8f0:	4479499d 	ldrbtmi	r4, [r9], #-2461	; 0xfffff663
d001b8f4:	489de7f9 	ldmmi	sp, {r0, r3, r4, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d001b8f8:	44034478 	strmi	r4, [r3], #-1144	; 0xfffffb88
d001b8fc:	2394f503 	orrscs	pc, r4, #12582912	; 0xc00000
d001b900:	3257f893 	subscc	pc, r7, #9633792	; 0x930000
d001b904:	d1dd2b02 	bicsle	r2, sp, r2, lsl #22
d001b908:	2394f500 	orrscs	pc, r4, #0, 10
d001b90c:	3298f8d3 	addscc	pc, r8, #13828096	; 0xd30000
d001b910:	7f00f5b3 	svcvc	0x0000f5b3
d001b914:	4996d102 	ldmibmi	r6, {r1, r8, ip, lr, pc}
d001b918:	e4594479 	ldrb	r4, [r9], #-1145	; 0xfffffb87
d001b91c:	4c952701 	ldcmi	7, cr2, [r5], {1}
d001b920:	4620447c 			; <UNDEFINED> instruction: 0x4620447c
d001b924:	fabef7f7 	blx	0xcefd9908
d001b928:	213b4a93 	teqcs	fp, r3	; <illegal shifter operand>
d001b92c:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d001b930:	fae6f7f7 	blx	0xcf9d9914
d001b934:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d001b938:	b177f961 	cmnlt	r7, r1, ror #18	; <UNPREDICTABLE>
d001b93c:	2294f504 	addscs	pc, r4, #4, 10	; 0x1000000
d001b940:	3298f8d2 	addscc	pc, r8, #13762560	; 0xd20000
d001b944:	f5031c59 			; <UNDEFINED> instruction: 0xf5031c59
d001b948:	33a63394 			; <UNDEFINED> instruction: 0x33a63394
d001b94c:	1298f8c2 	addsne	pc, r8, #12713984	; 0xc20000
d001b950:	0483eb04 	streq	lr, [r3], #2820	; 0xb04
d001b954:	f7ff6060 			; <UNDEFINED> instruction: 0xf7ff6060
d001b958:	f504bbe9 			; <UNDEFINED> instruction: 0xf504bbe9
d001b95c:	f8d22292 			; <UNDEFINED> instruction: 0xf8d22292
d001b960:	1c593250 	lfmne	f3, 2, [r9], {80}	; 0x50
d001b964:	4312f503 	tstmi	r2, #12582912	; 0xc00000	; <UNPREDICTABLE>
d001b968:	f8c2334a 			; <UNDEFINED> instruction: 0xf8c2334a
d001b96c:	eb041250 	bl	0xd01202b4
d001b970:	f24004c3 	vshl.s8	q8, <illegal reg q1.5>, q8
d001b974:	1af31311 	bne	0xcfce05c0
d001b978:	425e6060 	subsmi	r6, lr, #96	; 0x60
d001b97c:	7226415e 	eorvc	r4, r6, #-2147483625	; 0x80000017
d001b980:	bbd4f7ff 	bllt	0xcf559984
d001b984:	110ff240 	tstne	pc, r0, asr #4	; <UNPREDICTABLE>
d001b988:	f7f74620 			; <UNDEFINED> instruction: 0xf7f74620
d001b98c:	2800faab 	stmdacs	r0, {r0, r1, r3, r5, r7, r9, fp, ip, sp, lr, pc}
d001b990:	f504d071 			; <UNDEFINED> instruction: 0xf504d071
d001b994:	f8942490 			; <UNDEFINED> instruction: 0xf8942490
d001b998:	2b043634 	blcs	0xd0129270
d001b99c:	4c77d11f 	ldfmip	f5, [r7], #-124	; 0xffffff84
d001b9a0:	f504447c 			; <UNDEFINED> instruction: 0xf504447c
d001b9a4:	46202590 			; <UNDEFINED> instruction: 0x46202590
d001b9a8:	1635f895 			; <UNDEFINED> instruction: 0x1635f895
d001b9ac:	fde2f7fb 	stc2l	7, cr15, [r2, #1004]!	; 0x3ec
d001b9b0:	1636f895 			; <UNDEFINED> instruction: 0x1636f895
d001b9b4:	46202201 	strtmi	r2, [r0], -r1, lsl #4
d001b9b8:	f898f7f9 			; <UNDEFINED> instruction: 0xf898f7f9
d001b9bc:	3635f895 			; <UNDEFINED> instruction: 0x3635f895
d001b9c0:	721af44f 	andsvc	pc, sl, #1325400064	; 0x4f000000
d001b9c4:	4303fb02 	movwmi	pc, #15106	; 0x3b02	; <UNPREDICTABLE>
d001b9c8:	3368f503 	msrcc	SPSR_f, #12582912	; 0xc00000
d001b9cc:	f7f98d18 			; <UNDEFINED> instruction: 0xf7f98d18
d001b9d0:	f244fbef 	vqdmulh.s<illegal width 8>	<illegal reg q15.5>, q10, <illegal reg q15.5>
d001b9d4:	46206108 	strtmi	r6, [r0], -r8, lsl #2
d001b9d8:	f86af7f9 			; <UNDEFINED> instruction: 0xf86af7f9
d001b9dc:	2b05e009 	blcs	0xd0193a08
d001b9e0:	4867d11b 	stmdami	r7!, {r0, r1, r3, r4, r8, ip, lr, pc}^
d001b9e4:	f5004478 			; <UNDEFINED> instruction: 0xf5004478
d001b9e8:	f8932390 			; <UNDEFINED> instruction: 0xf8932390
d001b9ec:	f7fc1635 			; <UNDEFINED> instruction: 0xf7fc1635
d001b9f0:	4d64fa17 	vstmdbmi	r4!, {s31-s53}
d001b9f4:	4a64213b 	bmi	0xd1923ee8
d001b9f8:	447a447d 	ldrbtmi	r4, [sl], #-1149	; 0xfffffb83
d001b9fc:	f7f74628 			; <UNDEFINED> instruction: 0xf7f74628
d001ba00:	f505fa7f 			; <UNDEFINED> instruction: 0xf505fa7f
d001ba04:	f8d32390 			; <UNDEFINED> instruction: 0xf8d32390
d001ba08:	f5b44630 			; <UNDEFINED> instruction: 0xf5b44630
d001ba0c:	d1246f80 	smlawble	r4, r0, pc, r6	; <UNPREDICTABLE>
d001ba10:	4628495e 			; <UNDEFINED> instruction: 0x4628495e
d001ba14:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d001ba18:	2b01bbdb 	blcs	0xd008a98c
d001ba1c:	4c5cd013 	mrrcmi	0, 1, sp, ip, cr3
d001ba20:	f04f2b03 			; <UNDEFINED> instruction: 0xf04f2b03
d001ba24:	447c0101 	ldrbtmi	r0, [ip], #-257	; 0xfffffeff
d001ba28:	2204bf0c 	andcs	fp, r4, #12, 30	; 0x30
d001ba2c:	46202201 	strtmi	r2, [r0], -r1, lsl #4
d001ba30:	fbd0f7fa 	blx	0xcf459a22
d001ba34:	2390f504 	orrscs	pc, r0, #4, 10	; 0x1000000
d001ba38:	3634f893 			; <UNDEFINED> instruction: 0x3634f893
d001ba3c:	d1d82b02 	bicsle	r2, r8, r2, lsl #22
d001ba40:	21c0f24b 	biccs	pc, r0, fp, asr #4
d001ba44:	4853e7c7 	ldmdami	r3, {r0, r1, r2, r6, r7, r8, r9, sl, sp, lr, pc}^
d001ba48:	6ac34478 	bvs	0xcf0ecc30
d001ba4c:	d0d02b3b 	sbcsle	r2, r0, fp, lsr fp
d001ba50:	44794951 	ldrbtmi	r4, [r9], #-2385	; 0xfffff6af
d001ba54:	fbfaf7f4 	blx	0xcfed9a2e
d001ba58:	1c62e7cb 	stclne	7, cr14, [r2], #-812	; 0xfffffcd4
d001ba5c:	348ef504 	strcc	pc, [lr], #1284	; 0x504
d001ba60:	f5044628 			; <UNDEFINED> instruction: 0xf5044628
d001ba64:	f8c374c6 			; <UNDEFINED> instruction: 0xf8c374c6
d001ba68:	f7f92630 			; <UNDEFINED> instruction: 0xf7f92630
d001ba6c:	f845f8c7 			; <UNDEFINED> instruction: 0xf845f8c7
d001ba70:	f7ff0024 			; <UNDEFINED> instruction: 0xf7ff0024
d001ba74:	213bbb5b 	teqcs	fp, fp, asr fp
d001ba78:	f7f74620 			; <UNDEFINED> instruction: 0xf7f74620
d001ba7c:	2800fa33 	stmdacs	r0, {r0, r1, r4, r5, r9, fp, ip, sp, lr, pc}
d001ba80:	ab54f47f 	blge	0xd1558c84
d001ba84:	fedef7fd 	mrc2	7, 6, pc, cr14, cr13, {7}
d001ba88:	48454a44 	stmdami	r5, {r2, r6, r9, fp, lr}^
d001ba8c:	447a213b 	ldrbtmi	r2, [sl], #-315	; 0xfffffec5
d001ba90:	f7f74478 			; <UNDEFINED> instruction: 0xf7f74478
d001ba94:	f7fffa35 			; <UNDEFINED> instruction: 0xf7fffa35
d001ba98:	bf00bb49 	svclt	0x0000bb49
d001ba9c:	0000c9bc 			; <UNDEFINED> instruction: 0x0000c9bc
d001baa0:	ffffaec4 			; <UNDEFINED> instruction: 0xffffaec4
d001baa4:	0000c964 	andeq	ip, r0, r4, ror #18
d001baa8:	fffffbf7 			; <UNDEFINED> instruction: 0xfffffbf7
d001baac:	0000c8c6 	andeq	ip, r0, r6, asr #17
d001bab0:	fffffbcd 			; <UNDEFINED> instruction: 0xfffffbcd
d001bab4:	0000c87a 	andeq	ip, r0, sl, ror r8
d001bab8:	0000c878 	andeq	ip, r0, r8, ror r8
d001babc:	fffffb2a 			; <UNDEFINED> instruction: 0xfffffb2a
d001bac0:	fffffb05 			; <UNDEFINED> instruction: 0xfffffb05
d001bac4:	0000c782 	andeq	ip, r0, r2, lsl #15
d001bac8:	0000c778 	andeq	ip, r0, r8, ror r7
d001bacc:	0000c748 	andeq	ip, r0, r8, asr #14
d001bad0:	fffffaea 			; <UNDEFINED> instruction: 0xfffffaea
d001bad4:	0000c71a 	andeq	ip, r0, sl, lsl r7
d001bad8:	fffffadd 			; <UNDEFINED> instruction: 0xfffffadd
d001badc:	fffffa11 			; <UNDEFINED> instruction: 0xfffffa11
d001bae0:	0000c6c2 	andeq	ip, r0, r2, asr #13
d001bae4:	0000c678 	andeq	ip, r0, r8, ror r6
d001bae8:	0000c676 	andeq	ip, r0, r6, ror r6
d001baec:	fffff925 			; <UNDEFINED> instruction: 0xfffff925
d001baf0:	fffff9a9 			; <UNDEFINED> instruction: 0xfffff9a9
d001baf4:	fffff9af 			; <UNDEFINED> instruction: 0xfffff9af
d001baf8:	0000c5b0 			; <UNDEFINED> instruction: 0x0000c5b0
d001bafc:	0000c5a4 	andeq	ip, r0, r4, lsr #11
d001bb00:	0000c58e 	andeq	ip, r0, lr, lsl #11
d001bb04:	fffff9b7 			; <UNDEFINED> instruction: 0xfffff9b7
d001bb08:	fffff9a9 			; <UNDEFINED> instruction: 0xfffff9a9
d001bb0c:	fffff9bc 			; <UNDEFINED> instruction: 0xfffff9bc
d001bb10:	0000c522 	andeq	ip, r0, r2, lsr #10
d001bb14:	0000c4be 			; <UNDEFINED> instruction: 0x0000c4be
d001bb18:	0000c4b0 			; <UNDEFINED> instruction: 0x0000c4b0
d001bb1c:	fffff8f4 			; <UNDEFINED> instruction: 0xfffff8f4
d001bb20:	0000c456 	andeq	ip, r0, r6, asr r4
d001bb24:	fffff95f 			; <UNDEFINED> instruction: 0xfffff95f
d001bb28:	0000c3d4 	ldrdeq	ip, [r0], -r4
d001bb2c:	0000c3ac 	andeq	ip, r0, ip, lsr #7
d001bb30:	fffff8a6 			; <UNDEFINED> instruction: 0xfffff8a6
d001bb34:	0000c36a 	andeq	ip, r0, sl, ror #6
d001bb38:	fffff80d 			; <UNDEFINED> instruction: 0xfffff80d
d001bb3c:	fffff620 			; <UNDEFINED> instruction: 0xfffff620
d001bb40:	0000c326 	andeq	ip, r0, r6, lsr #6
d001bb44:	0000c312 	andeq	ip, r0, r2, lsl r3
d001bb48:	fffff6eb 			; <UNDEFINED> instruction: 0xfffff6eb
d001bb4c:	0000c2cc 	andeq	ip, r0, ip, asr #5
d001bb50:	fffff769 			; <UNDEFINED> instruction: 0xfffff769
d001bb54:	fffff75e 			; <UNDEFINED> instruction: 0xfffff75e
d001bb58:	0000c1ce 	andeq	ip, r0, lr, asr #3
d001bb5c:	fffff727 			; <UNDEFINED> instruction: 0xfffff727
d001bb60:	fffff4bc 			; <UNDEFINED> instruction: 0xfffff4bc
d001bb64:	0000c1a8 	andeq	ip, r0, r8, lsr #3
d001bb68:	fffff49a 			; <UNDEFINED> instruction: 0xfffff49a
d001bb6c:	0000c19c 	muleq	r0, ip, r1
d001bb70:	fffff6d0 			; <UNDEFINED> instruction: 0xfffff6d0
d001bb74:	0000c174 	andeq	ip, r0, r4, ror r1
d001bb78:	fffff6f3 			; <UNDEFINED> instruction: 0xfffff6f3
d001bb7c:	0000c0f4 	strdeq	ip, [r0], -r4
d001bb80:	0000c0b0 	strheq	ip, [r0], -r0
d001bb84:	0000c09c 	muleq	r0, ip, r0
d001bb88:	fffff678 			; <UNDEFINED> instruction: 0xfffff678
d001bb8c:	fffff678 			; <UNDEFINED> instruction: 0xfffff678
d001bb90:	0000c06e 	andeq	ip, r0, lr, rrx
d001bb94:	0000c04c 	andeq	ip, r0, ip, asr #32
d001bb98:	fffff5f4 			; <UNDEFINED> instruction: 0xfffff5f4
d001bb9c:	fffff61f 			; <UNDEFINED> instruction: 0xfffff61f
d001bba0:	0000c004 	andeq	ip, r0, r4

Disassembly of section .text.initialize_static_buffer.constprop.0:

d001bbd8 <.text.initialize_static_buffer.constprop.0>:
d001bbd8:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d001bbdc:	481a4604 	ldmdami	sl, {r2, r9, sl, lr}
d001bbe0:	f5004478 			; <UNDEFINED> instruction: 0xf5004478
d001bbe4:	f8d3337f 			; <UNDEFINED> instruction: 0xf8d3337f
d001bbe8:	f5c55224 			; <UNDEFINED> instruction: 0xf5c55224
d001bbec:	42a313be 	adcmi	r1, r3, #-134217726	; 0xf8000002
d001bbf0:	4916d206 	ldmdbmi	r6, {r1, r2, r9, ip, lr, pc}
d001bbf4:	f7f44479 			; <UNDEFINED> instruction: 0xf7f44479
d001bbf8:	2000fb29 	andcs	pc, r0, r9, lsr #22
d001bbfc:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d001bc00:	804cf8df 	ldrdhi	pc, [ip], #-143	; 0xffffff71
d001bc04:	00a400ad 	adceq	r0, r4, sp, lsr #1
d001bc08:	44f84606 	ldrbtmi	r4, [r8], #1542	; 0x606
d001bc0c:	b1046db0 			; <UNDEFINED> instruction: 0xb1046db0
d001bc10:	4b10b150 	blmi	0xd0448158
d001bc14:	fab02200 	blx	0xcec2441c
d001bc18:	447bf080 	ldrbtmi	pc, [fp], #-128	; 0xffffff80	; <UNPREDICTABLE>
d001bc1c:	f5030940 			; <UNDEFINED> instruction: 0xf5030940
d001bc20:	f883337f 			; <UNDEFINED> instruction: 0xf883337f
d001bc24:	e7e92220 	strb	r2, [r9, r0, lsr #4]!
d001bc28:	6f80f5b4 	svcvs	0x0080f5b4
d001bc2c:	46294627 	strtmi	r4, [r9], -r7, lsr #12
d001bc30:	bf284642 	svclt	0x00284642
d001bc34:	6780f44f 	strvs	pc, [r0, pc, asr #8]
d001bc38:	463b2001 	ldrtmi	r2, [fp], -r1
d001bc3c:	1be4443d 	blne	0xcf92cd38
d001bc40:	febef7f8 	mrc2	7, 5, pc, cr14, cr8, {7}
d001bc44:	bf00e7e2 	svclt	0x0000e7e2
d001bc48:	0000beb4 			; <UNDEFINED> instruction: 0x0000beb4
d001bc4c:	ffffffac 			; <UNDEFINED> instruction: 0xffffffac
d001bc50:	00003846 	andeq	r3, r0, r6, asr #16
d001bc54:	0000be7a 	andeq	fp, r0, sl, ror lr

Disassembly of section .text.global_declaration.constprop.0:

d001bdd8 <.text.global_declaration.constprop.0>:
d001bdd8:	e92db084 	push	{r2, r7, ip, sp, pc}
d001bddc:	b08b4ff0 	strdlt	r4, [fp], r0
d001bde0:	b42cf8df 	strtlt	pc, [ip], #-2271	; 0xfffff721
d001bde4:	44fbac14 	ldrbtmi	sl, [fp], #3092	; 0xc14
d001bde8:	f89d9004 			; <UNDEFINED> instruction: 0xf89d9004
d001bdec:	9f1d6070 	svcls	0x001d6070
d001bdf0:	000fe884 	andeq	lr, pc, r4, lsl #17
d001bdf4:	46019a15 			; <UNDEFINED> instruction: 0x46019a15
d001bdf8:	f8dd4658 			; <UNDEFINED> instruction: 0xf8dd4658
d001bdfc:	9205a05c 	andls	sl, r5, #92	; 0x5c
d001be00:	9060f8dd 	ldrdls	pc, [r0], #-141	; 0xffffff73	; <UNPREDICTABLE>
d001be04:	8068f89d 	mlshi	r8, sp, r8, pc	; <UNPREDICTABLE>
d001be08:	f7f49d1b 			; <UNDEFINED> instruction: 0xf7f49d1b
d001be0c:	9a05fd58 	bls	0xd019b374
d001be10:	99044604 	stmdbls	r4, {r2, r9, sl, lr}
d001be14:	f7f44658 			; <UNDEFINED> instruction: 0xf7f44658
d001be18:	2800fd0e 	stmdacs	r0, {r1, r2, r3, r8, sl, fp, ip, sp, lr, pc}
d001be1c:	9a059904 	bls	0xd0182234
d001be20:	4bfcdb0f 	blmi	0xcff52a64
d001be24:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d001be28:	4afbb932 	bmi	0xcff0a2f8
d001be2c:	447a669d 	ldrbtmi	r6, [sl], #-1693	; 0xfffff963
d001be30:	9818e9c3 	ldmdals	r8, {r0, r1, r6, r7, r8, fp, sp, lr, pc}
d001be34:	2a16e9c3 	bcs	0xd05d6548
d001be38:	e8bdb00b 	pop	{r0, r1, r3, ip, sp, pc}
d001be3c:	b0044ff0 	strdlt	r4, [r4], -r0
d001be40:	46584770 			; <UNDEFINED> instruction: 0x46584770
d001be44:	91049205 	tstls	r4, r5, lsl #4
d001be48:	fcd0f7f4 	ldc2l	7, cr15, [r0], {244}	; 0xf4
d001be4c:	dae82800 	ble	0xcfa25e54
d001be50:	99042c00 	stmdbls	r4, {sl, fp, sp}
d001be54:	db0a9a05 	blle	0xd02c2670
d001be58:	f89b2038 			; <UNDEFINED> instruction: 0xf89b2038
d001be5c:	fb003008 	blx	0xd0027e86
d001be60:	f504b404 			; <UNDEFINED> instruction: 0xf504b404
d001be64:	f894347f 			; <UNDEFINED> instruction: 0xf894347f
d001be68:	42980251 	addsmi	r0, r8, #268435461	; 0x10000005
d001be6c:	4cebd0d9 	stclmi	0, cr13, [fp], #868	; 0x364
d001be70:	447c9205 	ldrbtmi	r9, [ip], #-517	; 0xfffffdfb
d001be74:	46209104 	strtmi	r9, [r0], -r4, lsl #2
d001be78:	fd7df7f4 	ldc2l	7, cr15, [sp, #-976]!	; 0xfffffc30
d001be7c:	9a059904 	bls	0xd0182294
d001be80:	d1ce2800 	bicle	r2, lr, r0, lsl #16
d001be84:	f7f44620 			; <UNDEFINED> instruction: 0xf7f44620
d001be88:	2800fd58 	stmdacs	r0, {r3, r4, r6, r8, sl, fp, ip, sp, lr, pc}
d001be8c:	f504d1c9 			; <UNDEFINED> instruction: 0xf504d1c9
d001be90:	f8d33367 			; <UNDEFINED> instruction: 0xf8d33367
d001be94:	2b8031c4 	blcs	0xce0285ac
d001be98:	6da3d10a 	stfvsd	f5, [r3, #40]!	; 0x28
d001be9c:	d1cb2b00 	bicle	r2, fp, r0, lsl #22
d001bea0:	447b4bdf 	ldrbtmi	r4, [fp], #-3039	; 0xfffff421
d001bea4:	e9c466a5 	stmib	r4, {r0, r2, r5, r7, r9, sl, sp, lr}^
d001bea8:	e9c43a16 	stmib	r4, {r1, r2, r4, r9, fp, ip, sp}^
d001beac:	e7c39818 	bfi	r9, r8, (invalid: 16:3)
d001beb0:	4620215b 			; <UNDEFINED> instruction: 0x4620215b
d001beb4:	f816f7f7 			; <UNDEFINED> instruction: 0xf816f7f7
d001beb8:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d001bebc:	b12f80ae 			; <UNDEFINED> instruction: 0xb12f80ae
d001bec0:	2b006da3 	blcs	0xd0037554
d001bec4:	4bd7d1b8 	blmi	0xcf6105ac
d001bec8:	e7eb447b 			; <UNDEFINED> instruction: 0xe7eb447b
d001becc:	d0062e05 	andle	r2, r6, r5, lsl #28
d001bed0:	6da3b12e 	stfvsd	f3, [r3, #184]!	; 0xb8
d001bed4:	d1af2b00 			; <UNDEFINED> instruction: 0xd1af2b00
d001bed8:	447b4bd3 	ldrbtmi	r4, [fp], #-3027	; 0xfffff42d
d001bedc:	4bd3e7e2 	blmi	0xcf515e6c
d001bee0:	6ad8447b 	bvs	0xcf62d0d4
d001bee4:	c024f8d3 	ldrdgt	pc, [r4], -r3	; <UNPREDICTABLE>
d001bee8:	7081f5a0 	addvc	pc, r1, r0, lsr #11
d001beec:	f8936a9c 			; <UNDEFINED> instruction: 0xf8936a9c
d001bef0:	28011030 	stmdacs	r1, {r4, r5, ip}
d001bef4:	d8016b5a 	stmdale	r1, {r1, r3, r4, r6, r8, r9, fp, sp, lr}
d001bef8:	b9606a18 	stmdblt	r0!, {r3, r4, r9, fp, sp, lr}^
d001befc:	447b4bcc 	ldrbtmi	r4, [fp], #-3020	; 0xfffff434
d001bf00:	28006d98 	stmdacs	r0, {r3, r4, r7, r8, sl, fp, sp, lr}
d001bf04:	48cbd198 	stmiami	fp, {r3, r4, r7, r8, ip, lr, pc}^
d001bf08:	669a4478 			; <UNDEFINED> instruction: 0x669a4478
d001bf0c:	0c16e9c3 			; <UNDEFINED> instruction: 0x0c16e9c3
d001bf10:	4118e9c3 	tstmi	r8, r3, asr #19
d001bf14:	b946e790 	stmdblt	r6, {r4, r7, r8, r9, sl, sp, lr, pc}^
d001bf18:	2f80f5b0 	svccs	0x0080f5b0
d001bf1c:	6d98d921 	vldrvs.16	s26, [r8, #66]	; 0x42	; <UNPREDICTABLE>
d001bf20:	d1892800 	orrle	r2, r9, r0, lsl #16
d001bf24:	447848c4 	ldrbtmi	r4, [r8], #-2244	; 0xfffff73c
d001bf28:	2501e7ef 	strcs	lr, [r1, #-2031]	; 0xfffff811
d001bf2c:	447b4bc3 	ldrbtmi	r4, [fp], #-3011	; 0xfffff43d
d001bf30:	337ff503 	cmncc	pc, #12582912	; 0xc00000	; <UNPREDICTABLE>
d001bf34:	321cf8d3 	andscc	pc, ip, #13828096	; 0xd30000
d001bf38:	3303b916 	movwcc	fp, #14614	; 0x3916
d001bf3c:	0303f023 	movweq	pc, #12323	; 0x3023	; <UNPREDICTABLE>
d001bf40:	1f80f5b3 	svcne	0x0080f5b3
d001bf44:	4345d804 	movtmi	sp, #22532	; 0x5804
d001bf48:	1380f5c3 	orrne	pc, r0, #817889280	; 0x30c00000
d001bf4c:	d90a429d 	stmdble	sl, {r0, r2, r3, r4, r7, r9, lr}
d001bf50:	447b4bbb 	ldrbtmi	r4, [fp], #-3003	; 0xfffff445
d001bf54:	28006d98 	stmdacs	r0, {r3, r4, r7, r8, sl, fp, sp, lr}
d001bf58:	af6ef47f 	svcge	0x006ef47f
d001bf5c:	447848b9 	ldrbtmi	r4, [r8], #-2233	; 0xfffff747
d001bf60:	2504e7d3 	strcs	lr, [r4, #-2003]	; 0xfffff82d
d001bf64:	48b8e7e2 	ldmmi	r8!, {r1, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d001bf68:	90044478 	andls	r4, r4, r8, ror r4
d001bf6c:	ff9af7f6 			; <UNDEFINED> instruction: 0xff9af7f6
d001bf70:	215d4ab6 	ldrhcs	r4, [sp, #-166]	; 0xffffff5a
d001bf74:	447a9804 	ldrbtmi	r9, [sl], #-2052	; 0xfffff7fc
d001bf78:	ffc2f7f6 			; <UNDEFINED> instruction: 0xffc2f7f6
d001bf7c:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001bf80:	2e00af5b 	mcrcs	15, 0, sl, cr0, cr11, {2}
d001bf84:	ea4fd14c 	b	0xd14104bc
d001bf88:	26080a95 			; <UNDEFINED> instruction: 0x26080a95
d001bf8c:	82c0f8df 	sbchi	pc, r0, #14614528	; 0xdf0000
d001bf90:	44f8213d 	ldrbtmi	r2, [r8], #317	; 0x13d
d001bf94:	397ff508 	ldmdbcc	pc!, {r3, r8, sl, ip, sp, lr, pc}^	; <UNPREDICTABLE>
d001bf98:	f8d94640 			; <UNDEFINED> instruction: 0xf8d94640
d001bf9c:	93043224 	movwls	r3, #16932	; 0x4224
d001bfa0:	ffa0f7f6 			; <UNDEFINED> instruction: 0xffa0f7f6
d001bfa4:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d001bfa8:	1ff380c9 	svcne	0x00f380c9
d001bfac:	d8552b01 	ldmdale	r5, {r0, r8, r9, fp, sp}^
d001bfb0:	3224f8d9 	eorcc	pc, r4, #14221312	; 0xd90000
d001bfb4:	13bef5c3 			; <UNDEFINED> instruction: 0x13bef5c3
d001bfb8:	d2344553 	eorsle	r4, r4, #348127232	; 0x14c00000
d001bfbc:	ffccf7f7 			; <UNDEFINED> instruction: 0xffccf7f7
d001bfc0:	24002300 	strcs	r2, [r0], #-768	; 0xfffffd00
d001bfc4:	828cf8df 	addhi	pc, ip, #14614528	; 0xdf0000
d001bfc8:	4aa3213b 	bmi	0xce8e44bc
d001bfcc:	930244f8 	movwls	r4, #9464	; 0x24f8
d001bfd0:	4640447a 			; <UNDEFINED> instruction: 0x4640447a
d001bfd4:	ff94f7f6 			; <UNDEFINED> instruction: 0xff94f7f6
d001bfd8:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001bfdc:	1ff2af2d 	svcne	0x00f2af2d
d001bfe0:	2a019b02 	bcs	0xd0082bf0
d001bfe4:	8105f200 	mrshi	pc, SP_usr	; <UNPREDICTABLE>
d001bfe8:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d001bfec:	2e0880a9 	cdpcs	0, 0, cr8, cr8, cr9, {5}
d001bff0:	f508d108 			; <UNDEFINED> instruction: 0xf508d108
d001bff4:	f8d8387f 			; <UNDEFINED> instruction: 0xf8d8387f
d001bff8:	32032218 	andcc	r2, r3, #24, 4	; 0x80000001
d001bffc:	0203f022 	andeq	pc, r3, #34	; 0x22
d001c000:	2218f8c8 	andscs	pc, r8, #200, 16	; 0xc80000
d001c004:	447a4a95 	ldrbtmi	r4, [sl], #-2709	; 0xfffff56b
d001c008:	327ff502 	rsbscc	pc, pc, #8388608	; 0x800000
d001c00c:	8218f8d2 	andshi	pc, r8, #13762560	; 0xd20000
d001c010:	0105eb08 	tsteq	r5, r8, lsl #22
d001c014:	1218f8c2 	andsne	pc, r8, #12713984	; 0xc20000
d001c018:	4605e0a7 	strmi	lr, [r5], -r7, lsr #1
d001c01c:	e7b54682 	ldr	r4, [r5, r2, lsl #13]!
d001c020:	260746aa 	strcs	r4, [r7], -sl, lsr #13
d001c024:	4650e7b2 			; <UNDEFINED> instruction: 0x4650e7b2
d001c028:	fdd6f7ff 	ldc2l	7, cr15, [r6, #1020]	; 0x3fc
d001c02c:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001c030:	1ff2af03 	svcne	0x00f2af03
d001c034:	465021ff 			; <UNDEFINED> instruction: 0x465021ff
d001c038:	41534253 	cmpmi	r3, r3, asr r2
d001c03c:	93002200 	movwls	r2, #512	; 0x200
d001c040:	f7fe2301 			; <UNDEFINED> instruction: 0xf7fe2301
d001c044:	f899f8bd 			; <UNDEFINED> instruction: 0xf899f8bd
d001c048:	2b003220 	blcs	0xd00288d0
d001c04c:	f8d9d0b9 			; <UNDEFINED> instruction: 0xf8d9d0b9
d001c050:	44533224 	ldrbmi	r3, [r3], #-548	; 0xfffffddc
d001c054:	3224f8c9 	eorcc	pc, r4, #13172736	; 0xc90000
d001c058:	e7b22301 	ldr	r2, [r2, r1, lsl #6]!
d001c05c:	4640212d 	strbmi	r2, [r0], -sp, lsr #2
d001c060:	ff40f7f6 			; <UNDEFINED> instruction: 0xff40f7f6
d001c064:	3024f8d8 	ldrdcc	pc, [r4], -r8	; <UNPREDICTABLE>
d001c068:	f44f4681 	vst1.32	{d20-d22}, [pc], r1
d001c06c:	9305718d 	movwls	r7, #20877	; 0x518d
d001c070:	f8d84640 			; <UNDEFINED> instruction: 0xf8d84640
d001c074:	f8d83028 			; <UNDEFINED> instruction: 0xf8d83028
d001c078:	9306402c 	movwls	r4, #24620	; 0x602c
d001c07c:	3030f898 	mlascc	r0, r8, r8, pc	; <UNPREDICTABLE>
d001c080:	b206e9d8 	andlt	lr, r6, #216, 18	; 0x360000
d001c084:	f8d89307 			; <UNDEFINED> instruction: 0xf8d89307
d001c088:	92093034 	andls	r3, r9, #52	; 0x34
d001c08c:	f7f69308 			; <UNDEFINED> instruction: 0xf7f69308
d001c090:	9a09ff29 	bls	0xd029bd3c
d001c094:	4640b120 	strbmi	fp, [r0], -r0, lsr #2
d001c098:	fcc4f7f7 	stc2l	7, cr15, [r4], {247}	; 0xf7
d001c09c:	e00d4604 	and	r4, sp, r4, lsl #12
d001c0a0:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d001c0a4:	d113429c 			; <UNDEFINED> instruction: 0xd113429c
d001c0a8:	46404659 			; <UNDEFINED> instruction: 0x46404659
d001c0ac:	fc63f7f4 	stc2l	7, cr15, [r3], #-976	; 0xfffffc30
d001c0b0:	d0392800 	eorsle	r2, r9, r0, lsl #16
d001c0b4:	46406a04 	strbmi	r6, [r0], -r4, lsl #20
d001c0b8:	fef4f7f6 	mrc2	7, 7, pc, cr4, cr6, {7}
d001c0bc:	0f00f1b9 	svceq	0x0000f1b9
d001c0c0:	4264d000 	rsbmi	sp, r4, #0
d001c0c4:	f04f2e05 			; <UNDEFINED> instruction: 0xf04f2e05
d001c0c8:	bf080300 	svclt	0x00080300
d001c0cc:	e779b2e4 	ldrb	fp, [r9, -r4, ror #5]!
d001c0d0:	7481f5a4 	strvc	pc, [r1], #1444	; 0x5a4
d001c0d4:	d8272c01 	stmdale	r7!, {r0, sl, fp, sp}
d001c0d8:	21014602 	tstcs	r1, r2, lsl #12
d001c0dc:	f7f64640 			; <UNDEFINED> instruction: 0xf7f64640
d001c0e0:	f8d8ff99 			; <UNDEFINED> instruction: 0xf8d8ff99
d001c0e4:	2b003058 	blcs	0xd002824c
d001c0e8:	aea6f47f 	mcrge	4, 5, pc, cr6, cr15, {3}	; <UNPREDICTABLE>
d001c0ec:	4300f110 	movwmi	pc, #272	; 0x110	; <UNPREDICTABLE>
d001c0f0:	f1419302 			; <UNDEFINED> instruction: 0xf1419302
d001c0f4:	93030300 	movwls	r0, #13056	; 0x3300
d001c0f8:	3402e9dd 	strcc	lr, [r2], #-2525	; 0xfffff623
d001c0fc:	bf082c01 	svclt	0x00082c01
d001c100:	4f00f1b3 	svcmi	0x0000f1b3
d001c104:	4b56d3ca 	blmi	0xd15d1034
d001c108:	f8c8447b 			; <UNDEFINED> instruction: 0xf8c8447b
d001c10c:	9b053058 	blls	0xd0168274
d001c110:	305cf8c8 	subscc	pc, ip, r8, asr #17
d001c114:	f8c89b06 			; <UNDEFINED> instruction: 0xf8c89b06
d001c118:	9b073060 	blls	0xd01e82a0
d001c11c:	3064f8c8 	rsbcc	pc, r4, r8, asr #17
d001c120:	f8c89b08 			; <UNDEFINED> instruction: 0xf8c89b08
d001c124:	e6873068 	str	r3, [r7], r8, rrx
d001c128:	484f494e 	stmdami	pc, {r1, r2, r3, r6, r8, fp, lr}^	; <UNPREDICTABLE>
d001c12c:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d001c130:	e8bdb00b 	pop	{r0, r1, r3, ip, sp, pc}
d001c134:	b0044ff0 	strdlt	r4, [r4], -r0
d001c138:	b888f7f4 	stmlt	r8, {r2, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}
d001c13c:	e7c14604 	strb	r4, [r1, r4, lsl #12]
d001c140:	d1082e08 	tstle	r8, r8, lsl #28
d001c144:	387ff508 	ldmdacc	pc!, {r3, r8, sl, ip, sp, lr, pc}^	; <UNPREDICTABLE>
d001c148:	221cf8d8 	andscs	pc, ip, #216, 16	; 0xd80000
d001c14c:	f0223203 			; <UNDEFINED> instruction: 0xf0223203
d001c150:	f8c80203 			; <UNDEFINED> instruction: 0xf8c80203
d001c154:	4a45221c 	bmi	0xd11649cc
d001c158:	f502447a 			; <UNDEFINED> instruction: 0xf502447a
d001c15c:	f8d2327f 			; <UNDEFINED> instruction: 0xf8d2327f
d001c160:	eb08821c 	bl	0xd023c9d8
d001c164:	f8c20105 			; <UNDEFINED> instruction: 0xf8c20105
d001c168:	4a41121c 	bmi	0xd10609e0
d001c16c:	fa5f2b00 	blx	0xd17e6d74
d001c170:	447af987 	ldrbtmi	pc, [sl], #-2439	; 0xfffff679	; <UNPREDICTABLE>
d001c174:	f04fbf08 			; <UNDEFINED> instruction: 0xf04fbf08
d001c178:	2e080a00 	vmlacs.f32	s0, s16, s0
d001c17c:	3167f502 	msrcc	SPSR_sxc, r2, lsl #10
d001c180:	b008f892 	mullt	r8, r2, r8
d001c184:	f8d1b2da 			; <UNDEFINED> instruction: 0xf8d1b2da
d001c188:	920201c4 	andls	r0, r2, #196, 2	; 0x31
d001c18c:	0c01f100 	stfeqd	f7, [r1], {-0}
d001c190:	c1c4f8c1 	bicgt	pc, r4, r1, asr #17
d001c194:	08add137 	stmiaeq	sp!, {r0, r1, r2, r4, r5, r8, ip, lr, pc}
d001c198:	223c4f36 	eorscs	r4, ip, #54, 30	; 0xd8
d001c19c:	447f2100 	ldrbtmi	r2, [pc], #-256	; 0xd001c1a4
d001c1a0:	7700fb02 	strvc	pc, [r0, -r2, lsl #22]
d001c1a4:	375ff507 	ldrbcc	pc, [pc, -r7, lsl #10]	; <UNPREDICTABLE>
d001c1a8:	7371f507 	cmnvc	r1, #29360128	; 0x1c00000	; <UNPREDICTABLE>
d001c1ac:	f0044618 			; <UNDEFINED> instruction: 0xf0044618
d001c1b0:	f10dfea5 			; <UNDEFINED> instruction: 0xf10dfea5
d001c1b4:	46840e50 	pkhtbmi	r0, r4, r0, asr #28
d001c1b8:	43e4f8c7 	mvnmi	pc, #13041664	; 0xc70000
d001c1bc:	83e8f8c7 	mvnhi	pc, #13041664	; 0xc70000
d001c1c0:	63ecf887 	mvnvs	pc, #8847360	; 0x870000
d001c1c4:	b3edf887 	mvnlt	pc, #8847360	; 0x870000
d001c1c8:	93f0f887 	mvnsls	pc, #8847360	; 0x870000
d001c1cc:	a3f8f8c7 	mvnsge	pc, #13041664	; 0xc70000
d001c1d0:	53fcf8c7 	mvnspl	pc, #13041664	; 0xc70000
d001c1d4:	000fe8be 			; <UNDEFINED> instruction: 0x000fe8be
d001c1d8:	000fe8ac 	andeq	lr, pc, ip, lsr #17
d001c1dc:	000fe89e 	muleq	pc, lr, r8	; <UNPREDICTABLE>
d001c1e0:	000fe88c 	andeq	lr, pc, ip, lsl #17
d001c1e4:	f8879b02 			; <UNDEFINED> instruction: 0xf8879b02
d001c1e8:	9b0433ef 	blls	0xd01291ac
d001c1ec:	33f4f8c7 	mvnscc	pc, #13041664	; 0xc70000
d001c1f0:	f508e622 			; <UNDEFINED> instruction: 0xf508e622
d001c1f4:	f8d2327f 			; <UNDEFINED> instruction: 0xf8d2327f
d001c1f8:	31031218 	tstcc	r3, r8, lsl r2
d001c1fc:	0803f021 	stmdaeq	r3, {r0, r5, ip, sp, lr, pc}
d001c200:	0104f108 	tsteq	r4, r8, lsl #2	; <UNPREDICTABLE>
d001c204:	2e07e706 	cdpcs	7, 0, cr14, cr7, cr6, {0}
d001c208:	2500bf18 	strcs	fp, [r0, #-3864]	; 0xfffff0e8
d001c20c:	bf00e7c4 	svclt	0x0000e7c4
d001c210:	0000bcae 	andeq	fp, r0, lr, lsr #25
d001c214:	0000bc70 	andeq	fp, r0, r0, ror ip
d001c218:	fffffe26 			; <UNDEFINED> instruction: 0xfffffe26
d001c21c:	0000bc22 	andeq	fp, r0, r2, lsr #24
d001c220:	fffffdcc 			; <UNDEFINED> instruction: 0xfffffdcc
d001c224:	fffffdcb 			; <UNDEFINED> instruction: 0xfffffdcb
d001c228:	fffffde3 			; <UNDEFINED> instruction: 0xfffffde3
d001c22c:	0000bbb4 			; <UNDEFINED> instruction: 0x0000bbb4
d001c230:	0000bb96 	muleq	r0, r6, fp
d001c234:	fffffde6 			; <UNDEFINED> instruction: 0xfffffde6
d001c238:	fffffdf9 			; <UNDEFINED> instruction: 0xfffffdf9
d001c23c:	0000bb66 	andeq	fp, r0, r6, ror #22
d001c240:	0000bb42 	andeq	fp, r0, r2, asr #22
d001c244:	fffffde0 			; <UNDEFINED> instruction: 0xfffffde0
d001c248:	0000bb2c 	andeq	fp, r0, ip, lsr #22
d001c24c:	fffffde8 			; <UNDEFINED> instruction: 0xfffffde8
d001c250:	0000bb02 	andeq	fp, r0, r2, lsl #22
d001c254:	0000bac8 	andeq	fp, r0, r8, asr #21
d001c258:	fffffddd 			; <UNDEFINED> instruction: 0xfffffddd
d001c25c:	0000ba8e 	andeq	fp, r0, lr, lsl #21
d001c260:	fffffc7d 			; <UNDEFINED> instruction: 0xfffffc7d
d001c264:	ffffdbd0 			; <UNDEFINED> instruction: 0xffffdbd0
d001c268:	0000b966 	andeq	fp, r0, r6, ror #18
d001c26c:	0000b93c 	andeq	fp, r0, ip, lsr r9
d001c270:	0000b922 	andeq	fp, r0, r2, lsr #18
d001c274:	0000b8f6 	strdeq	fp, [r0], -r6

Disassembly of section .text.load_apicore.constprop.0:

d001c304 <.text.load_apicore.constprop.0>:
d001c304:	47f0e92d 	ldrbmi	lr, [r0, sp, lsr #18]!
d001c308:	b0864603 	addlt	r4, r6, r3, lsl #12
d001c30c:	4992b938 	ldmibmi	r2, {r3, r4, r5, r8, fp, ip, sp, pc}
d001c310:	44794892 	ldrbtmi	r4, [r9], #-2194	; 0xfffff76e
d001c314:	f7f34478 			; <UNDEFINED> instruction: 0xf7f34478
d001c318:	2000ff99 	mulcs	r0, r9, pc	; <UNPREDICTABLE>
d001c31c:	4c90e0b2 	ldcmi	0, cr14, [r0], {178}	; 0xb2
d001c320:	71acf644 			; <UNDEFINED> instruction: 0x71acf644
d001c324:	4620447c 			; <UNDEFINED> instruction: 0x4620447c
d001c328:	28004798 	stmdacs	r0, {r3, r4, r7, r8, r9, sl, lr}
d001c32c:	f1a0d0ef 			; <UNDEFINED> instruction: 0xf1a0d0ef
d001c330:	f6440218 			; <UNDEFINED> instruction: 0xf6440218
d001c334:	429a7394 	addsmi	r7, sl, #148, 6	; 0x50000002
d001c338:	8105f200 	mrshi	pc, SP_usr	; <UNPREDICTABLE>
d001c33c:	22041f06 	andcs	r1, r4, #6, 30
d001c340:	4d834668 	stcmi	6, cr4, [r3, #416]	; 0x1a0
d001c344:	f00419a1 			; <UNDEFINED> instruction: 0xf00419a1
d001c348:	4622fde7 	strtmi	pc, [r2], -r7, ror #27
d001c34c:	33fff04f 	mvnscc	pc, #79	; 0x4f
d001c350:	f8122100 			; <UNDEFINED> instruction: 0xf8122100
d001c354:	24080b01 	strcs	r0, [r8], #-2817	; 0xfffff4ff
d001c358:	f0134043 			; <UNDEFINED> instruction: 0xf0134043
d001c35c:	bf180001 	svclt	0x00180001
d001c360:	3c014628 	stccc	6, cr4, [r1], {40}	; 0x28
d001c364:	0353ea80 	cmpeq	r3, #128, 20	; 0x80000
d001c368:	3101d1f7 	strdcc	sp, [r1, -r7]
d001c36c:	d8f0428e 	ldmle	r0!, {r1, r2, r3, r7, r9, lr}^
d001c370:	9a0043db 	bls	0xd002d2e4
d001c374:	f040429a 			; <UNDEFINED> instruction: 0xf040429a
d001c378:	4f7a80e6 	svcmi	0x007a80e6
d001c37c:	2214ad01 	andscs	sl, r4, #1, 26	; 0x40
d001c380:	4628447f 			; <UNDEFINED> instruction: 0x4628447f
d001c384:	f0044639 			; <UNDEFINED> instruction: 0xf0044639
d001c388:	4977fdc7 	ldmdbmi	r7!, {r0, r1, r2, r6, r7, r8, sl, fp, ip, sp, lr, pc}^
d001c38c:	46282208 	strtmi	r2, [r8], -r8, lsl #4
d001c390:	f0044479 			; <UNDEFINED> instruction: 0xf0044479
d001c394:	b120fdd1 	ldrdlt	pc, [r0, -r1]!
d001c398:	48754974 	ldmdami	r5!, {r2, r4, r5, r6, r8, fp, lr}^
d001c39c:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d001c3a0:	4b6ce7b9 	blmi	0xd1b5628c
d001c3a4:	429a9a03 	addsmi	r9, sl, #12288	; 0x3000
d001c3a8:	80cdf040 	sbchi	pc, sp, r0, asr #32
d001c3ac:	1e539a04 	vnmlsne.f32	s19, s6, s8
d001c3b0:	f2002b9f 	vpadd.i8	d2, d16, d15
d001c3b4:	9b0580c8 	blls	0xd017c6dc
d001c3b8:	f2002bc0 	vqdmulh.s<illegal width 8>	q1, q8, q0
d001c3bc:	215480c4 	cmpcs	r4, r4, asr #1
d001c3c0:	22244351 	eorcs	r4, r4, #1140850689	; 0x44000001
d001c3c4:	eb01435a 	bl	0xd006d134
d001c3c8:	f1080802 			; <UNDEFINED> instruction: 0xf1080802
d001c3cc:	429e0328 	addsmi	r0, lr, #40, 6	; 0xa0000000
d001c3d0:	80b9f040 	adcshi	pc, r9, r0, asr #32
d001c3d4:	31144e67 	tstcc	r4, r7, ror #28
d001c3d8:	4439447e 	ldrtmi	r4, [r9], #-1150	; 0xfffffb82
d001c3dc:	3082f506 	addcc	pc, r2, r6, lsl #10
d001c3e0:	f00430a4 			; <UNDEFINED> instruction: 0xf00430a4
d001c3e4:	f506fd99 			; <UNDEFINED> instruction: 0xf506fd99
d001c3e8:	f108308f 			; <UNDEFINED> instruction: 0xf108308f
d001c3ec:	f5060114 			; <UNDEFINED> instruction: 0xf5060114
d001c3f0:	2214368f 	andscs	r3, r4, #149946368	; 0x8f00000
d001c3f4:	70d2f500 	sbcsvc	pc, r2, r0, lsl #10
d001c3f8:	f0044439 			; <UNDEFINED> instruction: 0xf0044439
d001c3fc:	f8b6fd8d 			; <UNDEFINED> instruction: 0xf8b6fd8d
d001c400:	f64011b4 			; <UNDEFINED> instruction: 0xf64011b4
d001c404:	1f0a73fc 	svcne	0x000a73fc
d001c408:	f200429a 	vqsub.s8	d4, d16, d10
d001c40c:	f001809c 			; <UNDEFINED> instruction: 0xf001809c
d001c410:	f8b60303 			; <UNDEFINED> instruction: 0xf8b60303
d001c414:	431321b6 	tstmi	r3, #-2147483603	; 0x8000002d
d001c418:	8095f040 	addshi	pc, r5, r0, asr #32
d001c41c:	22044b56 	andcs	r4, r4, #88064	; 0x15800
d001c420:	f503447b 			; <UNDEFINED> instruction: 0xf503447b
d001c424:	f503338f 			; <UNDEFINED> instruction: 0xf503338f
d001c428:	f83373d2 			; <UNDEFINED> instruction: 0xf83373d2
d001c42c:	1e560b02 	vnmlsne.f64	d16, d6, d2
d001c430:	f0404006 			; <UNDEFINED> instruction: 0xf0404006
d001c434:	1a8a8088 	bne	0xce2bc65c
d001c438:	f2004290 	vqsub.s8	d4, d16, d0
d001c43c:	34018084 	strcc	r8, [r1], #-132	; 0xffffff7c
d001c440:	d1222c08 			; <UNDEFINED> instruction: 0xd1222c08
d001c444:	46b04c4d 	ldrtmi	r4, [r0], sp, asr #24
d001c448:	f6404f4d 			; <UNDEFINED> instruction: 0xf6404f4d
d001c44c:	447c79fc 	ldrbtmi	r7, [ip], #-2556	; 0xfffff604
d001c450:	f504447f 			; <UNDEFINED> instruction: 0xf504447f
d001c454:	37144450 			; <UNDEFINED> instruction: 0x37144450
d001c458:	9b04346c 	blls	0xd0129610
d001c45c:	d3194598 	tstle	r9, #152, 10	; 0x26000000
d001c460:	447c4c48 	ldrbtmi	r4, [ip], #-3144	; 0xfffff3b8
d001c464:	3482f504 	strcc	pc, [r2], #1284	; 0x504
d001c468:	9b0534a4 	blls	0xd0169700
d001c46c:	d361429e 	cmnle	r1, #-536870903	; 0xe0000009
d001c470:	447c4c45 	ldrbtmi	r4, [ip], #-3141	; 0xfffff3bb
d001c474:	4450f504 	ldrbmi	pc, [r0], #-1284	; 0xfffffafc	; <UNPREDICTABLE>
d001c478:	3410cd0f 	ldrcc	ip, [r0], #-3343	; 0xfffff2f1
d001c47c:	682bc40f 	stmdavs	fp!, {r0, r1, r2, r3, sl, lr, pc}
d001c480:	60232001 	eorvs	r2, r3, r1
d001c484:	e8bdb006 	pop	{r1, r2, ip, sp, pc}
d001c488:	2c0187f0 	stccs	7, cr8, [r1], {240}	; 0xf0
d001c48c:	2201bf0c 	andcs	fp, r1, #12, 30	; 0x30
d001c490:	e7ca2204 	strb	r2, [sl, r4, lsl #4]
d001c494:	0a48f1a4 	beq	0xd1258b2c
d001c498:	46392254 			; <UNDEFINED> instruction: 0x46392254
d001c49c:	f0044650 			; <UNDEFINED> instruction: 0xf0044650
d001c4a0:	2201fd3b 	andcs	pc, r1, #3776	; 0xec0
d001c4a4:	46502140 	ldrbmi	r2, [r0], -r0, asr #2
d001c4a8:	ffcef7f3 			; <UNDEFINED> instruction: 0xffcef7f3
d001c4ac:	d04a2800 	suble	r2, sl, r0, lsl #16
d001c4b0:	2c02f814 	stccs	8, cr15, [r2], {20}
d001c4b4:	d8462a0c 	stmdale	r6, {r2, r3, r9, fp, sp}^
d001c4b8:	3c01f814 	stccc	8, cr15, [r1], {20}
d001c4bc:	b2d93b05 	sbcslt	r3, r9, #5120	; 0x1400
d001c4c0:	d840290c 	stmdale	r0, {r2, r3, r8, fp, sp}^
d001c4c4:	034ff641 	movteq	pc, #63041	; 0xf641	; <UNPREDICTABLE>
d001c4c8:	43db40cb 	bicsmi	r4, fp, #203	; 0xcb
d001c4cc:	0301f013 	movweq	pc, #4115	; 0x1013	; <UNPREDICTABLE>
d001c4d0:	f834d139 			; <UNDEFINED> instruction: 0xf834d139
d001c4d4:	f64f0c08 			; <UNDEFINED> instruction: 0xf64f0c08
d001c4d8:	428871ff 	addmi	r7, r8, #-1073741761	; 0xc000003f
d001c4dc:	f834d033 			; <UNDEFINED> instruction: 0xf834d033
d001c4e0:	42880c06 	addmi	r0, r8, #1536	; 0x600
d001c4e4:	f1a4d02f 			; <UNDEFINED> instruction: 0xf1a4d02f
d001c4e8:	f83c0c08 			; <UNDEFINED> instruction: 0xf83c0c08
d001c4ec:	42880b02 	addmi	r0, r8, #2048	; 0x800
d001c4f0:	4548d003 	strbmi	sp, [r8, #-3]
d001c4f4:	0780d827 	streq	sp, [r0, r7, lsr #16]
d001c4f8:	3301d125 	movwcc	sp, #4389	; 0x1125
d001c4fc:	d1f42b03 	mvnsle	r2, r3, lsl #22
d001c500:	23004621 	movwcs	r4, #1569	; 0x621
d001c504:	d806429a 	stmdale	r6, {r1, r3, r4, r7, r9, lr}
d001c508:	d10f2a0c 	tstle	pc, ip, lsl #20
d001c50c:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d001c510:	37543454 			; <UNDEFINED> instruction: 0x37543454
d001c514:	f811e7a1 			; <UNDEFINED> instruction: 0xf811e7a1
d001c518:	f1000b01 			; <UNDEFINED> instruction: 0xf1000b01
d001c51c:	f1bc3cff 			; <UNDEFINED> instruction: 0xf1bc3cff
d001c520:	d8100f15 	ldmdale	r0, {r0, r2, r4, r8, r9, sl, fp}
d001c524:	d00e2807 	andle	r2, lr, r7, lsl #16
d001c528:	e7eb3301 	strb	r3, [fp, r1, lsl #6]!
d001c52c:	b9535ca3 	ldmdblt	r3, {r0, r1, r5, r7, sl, fp, ip, lr}^
d001c530:	e7e93201 	strb	r3, [r9, r1, lsl #4]!
d001c534:	22004620 	andcs	r4, r0, #32, 12	; 0x2000000
d001c538:	34242120 	strtcc	r2, [r4], #-288	; 0xfffffee0
d001c53c:	ff84f7f3 			; <UNDEFINED> instruction: 0xff84f7f3
d001c540:	3601b108 	strcc	fp, [r1], -r8, lsl #2
d001c544:	4911e791 	ldmdbmi	r1, {r0, r4, r7, r8, r9, sl, sp, lr, pc}
d001c548:	44794811 	ldrbtmi	r4, [r9], #-2065	; 0xfffff7ef
d001c54c:	e6e24478 	uxtab	r4, r2, r8, ror #8
d001c550:	edb88320 	ldc	3, cr8, [r8, #128]!	; 0x80
d001c554:	2001f000 	andcs	pc, r1, r0
d001c558:	ffffff62 			; <UNDEFINED> instruction: 0xffffff62
d001c55c:	0000b780 	andeq	fp, r0, r0, lsl #15
d001c560:	000067c0 	andeq	r6, r0, r0, asr #15
d001c564:	00006764 	andeq	r6, r0, r4, ror #14
d001c568:	ffffff0f 			; <UNDEFINED> instruction: 0xffffff0f
d001c56c:	ffffff0b 			; <UNDEFINED> instruction: 0xffffff0b
d001c570:	0000b6f6 	strdeq	fp, [r0], -r6
d001c574:	0000b6bc 			; <UNDEFINED> instruction: 0x0000b6bc
d001c578:	0000b674 	andeq	fp, r0, r4, ror r6
d001c57c:	0000b646 	andeq	fp, r0, r6, asr #12
d001c580:	00006694 	muleq	r0, r4, r6
d001c584:	0000b632 	andeq	fp, r0, r2, lsr r6
d001c588:	0000b622 	andeq	fp, r0, r2, lsr #12
d001c58c:	fffffd9a 			; <UNDEFINED> instruction: 0xfffffd9a
d001c590:	0000b548 	andeq	fp, r0, r8, asr #10

Disassembly of section .text.compile_backend.constprop.0:

d001cdc0 <.text.compile_backend.constprop.0>:
d001cdc0:	4ff0e92d 	svcmi	0x00f0e92d
d001cdc4:	8b02ed2d 	blhi	0xd00d8280
d001cdc8:	5ddcf2ad 	lfmpl	f7, 3, [ip, #692]	; 0x2b4
d001cdcc:	22144614 	andscs	r4, r4, #20, 12	; 0x1400000
d001cdd0:	911d9019 	tstls	sp, r9, lsl r0
d001cdd4:	f8dd2100 			; <UNDEFINED> instruction: 0xf8dd2100
d001cdd8:	9320060c 			; <UNDEFINED> instruction: 0x9320060c
d001cddc:	f88ef004 			; <UNDEFINED> instruction: 0xf88ef004
d001cde0:	b1139b19 	tstlt	r3, r9, lsl fp
d001cde4:	2b0f1e63 	blcs	0xd03e4778
d001cde8:	4dc7d909 	vstrmi.16	s27, [r7, #18]	; <UNPREDICTABLE>
d001cdec:	460cf8dd 			; <UNDEFINED> instruction: 0x460cf8dd
d001cdf0:	cd0f447d 	cfstrsgt	mvf4, [pc, #-500]	; 0xd001cc04
d001cdf4:	682bc40f 	stmdavs	fp!, {r0, r1, r2, r3, sl, lr, pc}
d001cdf8:	20006023 	andcs	r6, r0, r3, lsr #32
d001cdfc:	2300e01e 	movwcs	lr, #30
d001ce00:	93179316 	tstls	r7, #1476395008	; 0x58000000
d001ce04:	1d1a9b19 	vldrne	d9, [sl, #-100]	; 0xffffff9c
d001ce08:	99179b19 	ldmdbls	r7, {r0, r3, r4, r8, r9, fp, ip, pc}
d001ce0c:	3031f853 	eorscc	pc, r1, r3, asr r8	; <UNPREDICTABLE>
d001ce10:	f852b133 			; <UNDEFINED> instruction: 0xf852b133
d001ce14:	99163031 	ldmdbls	r6, {r0, r4, r5, ip, sp}
d001ce18:	1180f5c1 	orrne	pc, r0, r1, asr #11
d001ce1c:	d918428b 	ldmdble	r8, {r0, r1, r3, r7, r9, lr}
d001ce20:	d0132c01 	andsle	r2, r3, r1, lsl #24
d001ce24:	447b4bb9 	ldrbtmi	r4, [fp], #-3001	; 0xfffff447
d001ce28:	260cf8dd 			; <UNDEFINED> instruction: 0x260cf8dd
d001ce2c:	60132000 	andsvs	r2, r3, r0
d001ce30:	61102301 	tstvs	r0, r1, lsl #6
d001ce34:	60936053 	addsvs	r6, r3, r3, asr r0
d001ce38:	60d39b17 	sbcsvs	r9, r3, r7, lsl fp
d001ce3c:	5ddcf20d 	lfmpl	f7, 3, [ip, #52]	; 0x34
d001ce40:	8b02ecbd 	blhi	0xd00d813c
d001ce44:	8ff0e8bd 	svchi	0x00f0e8bd
d001ce48:	e7dd9317 	bfi	r9, r7, #6, #24
d001ce4c:	447b4bb0 	ldrbtmi	r4, [fp], #-2992	; 0xfffff450
d001ce50:	9916e7ea 	ldmdbls	r6, {r1, r3, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d001ce54:	9b174419 	blls	0xd05edec0
d001ce58:	91163301 	tstls	r6, r1, lsl #6
d001ce5c:	d1f3429c 			; <UNDEFINED> instruction: 0xd1f3429c
d001ce60:	25004bac 	strcs	r4, [r0, #-2988]	; 0xfffff454
d001ce64:	22054cac 	andcs	r4, r5, #172, 24	; 0xac00
d001ce68:	48ac447b 	stmiami	ip!, {r0, r1, r3, r4, r5, r6, sl, lr}
d001ce6c:	6019447c 	andsvs	r4, r9, ip, ror r4
d001ce70:	4bab4478 	blmi	0xceaee058
d001ce74:	601d447b 	andsvs	r4, sp, fp, ror r4
d001ce78:	447b4baa 	ldrbtmi	r4, [fp], #-2986	; 0xfffff456
d001ce7c:	460a601a 			; <UNDEFINED> instruction: 0x460a601a
d001ce80:	f7f34629 			; <UNDEFINED> instruction: 0xf7f34629
d001ce84:	4a9ff989 	bmi	0xce81b4b0
d001ce88:	46204629 	strtmi	r4, [r0], -r9, lsr #12
d001ce8c:	f836f004 			; <UNDEFINED> instruction: 0xf836f004
d001ce90:	3608f8dd 			; <UNDEFINED> instruction: 0x3608f8dd
d001ce94:	22bc49a4 	adcscs	r4, ip, #164, 18	; 0x290000
d001ce98:	462866e3 	strtmi	r6, [r8], -r3, ror #13
d001ce9c:	44799b20 	ldrbtmi	r9, [r9], #-2848	; 0xfffff4e0
d001cea0:	f04f6723 			; <UNDEFINED> instruction: 0xf04f6723
d001cea4:	67a333ff 			; <UNDEFINED> instruction: 0x67a333ff
d001cea8:	fdcef7f7 	stc2l	7, cr15, [lr, #988]	; 0x3dc
d001ceac:	b14b6da3 	smlaltblt	r6, fp, r3, sp
d001ceb0:	f8dd4c9e 			; <UNDEFINED> instruction: 0xf8dd4c9e
d001ceb4:	447c560c 	ldrbtmi	r5, [ip], #-1548	; 0xfffff9f4
d001ceb8:	cc0f3458 	cfstrsgt	mvf3, [pc], {88}	; 0x58
d001cebc:	6823c50f 	stmdavs	r3!, {r0, r1, r2, r3, r8, sl, lr, pc}
d001cec0:	e79a602b 	ldr	r6, [sl, fp, lsr #32]
d001cec4:	22bc9318 	adcscs	r9, ip, #24, 6	; 0x60000000
d001cec8:	f5044b99 			; <UNDEFINED> instruction: 0xf5044b99
d001cecc:	447b348f 	ldrbtmi	r3, [fp], #-1167	; 0xfffffb71
d001ced0:	21b8f8c4 			; <UNDEFINED> instruction: 0x21b8f8c4
d001ced4:	931e9a19 	tstls	lr, #102400	; 0x19000
d001ced8:	4350f503 	cmpmi	r0, #12582912	; 0xc00000	; <UNPREDICTABLE>
d001cedc:	331c921a 	tstcc	ip, #-1610612735	; 0xa0000001
d001cee0:	4b94931f 	blmi	0xce541b64
d001cee4:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d001cee8:	f0002a00 			; <UNDEFINED> instruction: 0xf0002a00
d001ceec:	4892808c 	ldmmi	r2, {r2, r3, r7, pc}
d001cef0:	f5004478 			; <UNDEFINED> instruction: 0xf5004478
d001cef4:	f8932396 			; <UNDEFINED> instruction: 0xf8932396
d001cef8:	2d0052a2 	sfmcs	f5, 4, [r0, #-648]	; 0xfffffd78
d001cefc:	83bdf001 			; <UNDEFINED> instruction: 0x83bdf001
d001cf00:	2d006d85 	stccs	13, cr6, [r0, #-532]	; 0xfffffdec
d001cf04:	83b8f041 			; <UNDEFINED> instruction: 0x83b8f041
d001cf08:	338ff500 	orrcc	pc, pc, #0, 10
d001cf0c:	46044e8b 	strmi	r4, [r4], -fp, lsl #29
d001cf10:	71b8f8d3 			; <UNDEFINED> instruction: 0x71b8f8d3
d001cf14:	7871447e 	ldmdavc	r1!, {r1, r2, r3, r4, r5, r6, sl, lr}^
d001cf18:	f8163502 			; <UNDEFINED> instruction: 0xf8163502
d001cf1c:	46203b02 	strtmi	r3, [r0], -r2, lsl #22
d001cf20:	2101ea43 	tstcs	r1, r3, asr #20
d001cf24:	fdc4f7f7 	stc2l	7, cr15, [r4, #988]	; 0x3dc
d001cf28:	d1f42dce 	mvnsle	r2, lr, asr #27
d001cf2c:	338ff504 	orrcc	pc, pc, #4, 10	; 0x1000000
d001cf30:	820cf8df 	andhi	pc, ip, #14614528	; 0xdf0000
d001cf34:	f8d32600 			; <UNDEFINED> instruction: 0xf8d32600
d001cf38:	44f851b8 	ldrbtmi	r5, [r8], #440	; 0x1b8
d001cf3c:	1001f898 	mulne	r1, r8, r8
d001cf40:	f8183602 			; <UNDEFINED> instruction: 0xf8183602
d001cf44:	46203b02 	strtmi	r3, [r0], -r2, lsl #22
d001cf48:	2101ea43 	tstcs	r1, r3, asr #20
d001cf4c:	fdb0f7f7 	ldc2	7, cr15, [r0, #988]!	; 0x3dc
d001cf50:	d1f32ef2 	ldrshle	r2, [r3, #226]!	; 0xe2
d001cf54:	f04f4c7b 			; <UNDEFINED> instruction: 0xf04f4c7b
d001cf58:	f8df0a00 			; <UNDEFINED> instruction: 0xf8df0a00
d001cf5c:	447c91ec 	ldrbtmi	r9, [ip], #-492	; 0xfffffe14
d001cf60:	f50444f9 			; <UNDEFINED> instruction: 0xf50444f9
d001cf64:	f5042686 			; <UNDEFINED> instruction: 0xf5042686
d001cf68:	f206288e 	vadd.i8	d2, d22, d14
d001cf6c:	f8d8662c 			; <UNDEFINED> instruction: 0xf8d8662c
d001cf70:	459a362c 	ldrmi	r3, [sl, #1580]	; 0x62c
d001cf74:	6da3d203 	sfmvs	f5, 1, [r3, #12]!
d001cf78:	f0012b00 			; <UNDEFINED> instruction: 0xf0012b00
d001cf7c:	4b738381 	blmi	0xd1cfdd88
d001cf80:	f503447b 			; <UNDEFINED> instruction: 0xf503447b
d001cf84:	f503328f 			; <UNDEFINED> instruction: 0xf503328f
d001cf88:	e9d2337f 	ldmib	r2, {r0, r1, r2, r3, r4, r5, r6, r8, r9, ip, sp}^
d001cf8c:	f8d3126e 			; <UNDEFINED> instruction: 0xf8d3126e
d001cf90:	eb014218 	bl	0xd006d7f8
d001cf94:	f1080802 			; <UNDEFINED> instruction: 0xf1080802
d001cf98:	f0270703 			; <UNDEFINED> instruction: 0xf0270703
d001cf9c:	2c000703 	stccs	7, cr0, [r0], {3}
d001cfa0:	839ef001 	orrshi	pc, lr, #1
d001cfa4:	f104443c 			; <UNDEFINED> instruction: 0xf104443c
d001cfa8:	45a0031f 	strmi	r0, [r0, #799]!	; 0x31f
d001cfac:	031ff023 	tsteq	pc, #35	; 0x23	; <UNPREDICTABLE>
d001cfb0:	d811930f 	ldmdale	r1, {r0, r1, r2, r3, r8, r9, ip, pc}
d001cfb4:	0fbef5b4 	svceq	0x00bef5b4
d001cfb8:	45b8d80e 	ldrmi	sp, [r8, #2062]!	; 0x80e
d001cfbc:	429cd80c 	addsmi	sp, ip, #12, 16	; 0xc0000
d001cfc0:	4b63d80a 	blmi	0xd1912ff0
d001cfc4:	447b9a0f 	ldrbtmi	r9, [fp], #-2575	; 0xfffff5f1
d001cfc8:	02bef5c2 	adcseq	pc, lr, #813694976	; 0x30800000
d001cfcc:	337ff503 	cmncc	pc, #12582912	; 0xc00000	; <UNPREDICTABLE>
d001cfd0:	121cf8d3 	andsne	pc, ip, #13828096	; 0xd30000
d001cfd4:	d9054291 	stmdble	r5, {r0, r4, r7, r9, lr}
d001cfd8:	485f495e 	ldmdami	pc, {r1, r2, r3, r4, r6, r8, fp, lr}^	; <UNPREDICTABLE>
d001cfdc:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d001cfe0:	f934f7f3 			; <UNDEFINED> instruction: 0xf934f7f3
d001cfe4:	f04f4d5d 			; <UNDEFINED> instruction: 0xf04f4d5d
d001cfe8:	4b5d0a00 	blmi	0xd175f7f0
d001cfec:	f8cd447d 			; <UNDEFINED> instruction: 0xf8cd447d
d001cff0:	447ba040 	ldrbtmi	sl, [fp], #-64	; 0xffffffc0
d001cff4:	3947f505 	stmdbcc	r7, {r0, r2, r8, sl, ip, sp, lr, pc}^
d001cff8:	3b5ff505 	blcc	0xd181a414
d001cffc:	f5099311 			; <UNDEFINED> instruction: 0xf5099311
d001d000:	f0017970 			; <UNDEFINED> instruction: 0xf0017970
d001d004:	9a18bb96 	bls	0xd064be64
d001d008:	721a9918 	andsvc	r9, sl, #24, 18	; 0x60000
d001d00c:	f8529a19 			; <UNDEFINED> instruction: 0xf8529a19
d001d010:	601a2031 	andsvs	r2, sl, r1, lsr r0
d001d014:	b37b9b1d 	cmnlt	fp, #29696	; 0x7400
d001d018:	3021f853 	eorcc	pc, r1, r3, asr r8	; <UNPREDICTABLE>
d001d01c:	447c4c51 	ldrbtmi	r4, [ip], #-3153	; 0xfffff3af
d001d020:	f04f6763 			; <UNDEFINED> instruction: 0xf04f6763
d001d024:	f50433ff 			; <UNDEFINED> instruction: 0xf50433ff
d001d028:	46204250 			; <UNDEFINED> instruction: 0x46204250
d001d02c:	230067a3 	movwcs	r6, #1955	; 0x7a3
d001d030:	f50460d3 			; <UNDEFINED> instruction: 0xf50460d3
d001d034:	f8c4424f 			; <UNDEFINED> instruction: 0xf8c4424f
d001d038:	f8c231fc 			; <UNDEFINED> instruction: 0xf8c231fc
d001d03c:	9a1a3088 	bls	0xd06a9264
d001d040:	60e36852 	rscvs	r6, r3, r2, asr r8
d001d044:	60622301 	rsbvs	r2, r2, r1, lsl #6
d001d048:	3304e9c4 	movwcc	lr, #18884	; 0x49c4
d001d04c:	ff2af7f5 			; <UNDEFINED> instruction: 0xff2af7f5
d001d050:	4c454620 	mcrrmi	6, 2, r4, r5, cr0
d001d054:	ff26f7f5 			; <UNDEFINED> instruction: 0xff26f7f5
d001d058:	9a1e447c 	bls	0xd07ae250
d001d05c:	6ad29b1e 	bvs	0xcf4c3cdc
d001d060:	f5b26d9b 			; <UNDEFINED> instruction: 0xf5b26d9b
d001d064:	d10e7f83 	smlabble	lr, r3, pc, r7	; <UNPREDICTABLE>
d001d068:	9b1fb96b 	blls	0xd080b61c
d001d06c:	b12b681b 			; <UNDEFINED> instruction: 0xb12b681b
d001d070:	f7f54620 			; <UNDEFINED> instruction: 0xf7f54620
d001d074:	e7f0ff17 			; <UNDEFINED> instruction: 0xe7f0ff17
d001d078:	e7cf9b1d 	bfi	r9, sp, (invalid: 22:15)
d001d07c:	f7ff9820 			; <UNDEFINED> instruction: 0xf7ff9820
d001d080:	2800f941 	stmdacs	r0, {r0, r6, r8, fp, ip, sp, lr, pc}
d001d084:	4b39d1f4 	blmi	0xd0e9185c
d001d088:	ee08447b 	mcr	4, 0, r4, cr8, cr11, {3}
d001d08c:	f5033a10 			; <UNDEFINED> instruction: 0xf5033a10
d001d090:	331c4350 	tstcc	ip, #80, 6	; 0x40000001
d001d094:	e154931c 	cmp	r4, ip, lsl r3
d001d098:	1119f240 	tstne	r9, r0, asr #4	; <UNPREDICTABLE>
d001d09c:	f7f54620 			; <UNDEFINED> instruction: 0xf7f54620
d001d0a0:	4607ff21 	strmi	pc, [r7], -r1, lsr #30
d001d0a4:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d001d0a8:	ad2e81ca 	stfged	f0, [lr, #-808]!	; 0xfffffcd8
d001d0ac:	0c18f104 	ldfeqd	f7, [r8], {4}
d001d0b0:	802cf8d4 	ldrdhi	pc, [ip], -r4	; <UNPREDICTABLE>
d001d0b4:	f894462f 			; <UNDEFINED> instruction: 0xf894462f
d001d0b8:	e8bc9030 	ldm	ip!, {r4, r5, ip, pc}
d001d0bc:	c70f000f 	strgt	r0, [pc, -pc]
d001d0c0:	000fe89c 	muleq	pc, ip, r8	; <UNPREDICTABLE>
d001d0c4:	000fe887 	andeq	lr, pc, r7, lsl #17
d001d0c8:	f2406a63 	vpmax.s8	q11, q0, <illegal reg q9.5>
d001d0cc:	46201107 	strtmi	r1, [r0], -r7, lsl #2
d001d0d0:	6aa3930f 	bvs	0xce901d14
d001d0d4:	6b639310 	blvs	0xd1901d1c
d001d0d8:	ba06e9d4 	blt	0xd01d7830
d001d0dc:	f7f59311 			; <UNDEFINED> instruction: 0xf7f59311
d001d0e0:	4607ff01 	strmi	pc, [r7], -r1, lsl #30
d001d0e4:	f0402800 			; <UNDEFINED> instruction: 0xf0402800
d001d0e8:	6ae68154 	bvs	0xcf9bd640
d001d0ec:	131bf240 	tstne	fp, #64, 4	; <UNPREDICTABLE>
d001d0f0:	d13d429e 	teqle	sp, lr	; <illegal shifter operand>
d001d0f4:	f7f64620 			; <UNDEFINED> instruction: 0xf7f64620
d001d0f8:	2800f9f5 	stmdacs	r0, {r0, r2, r4, r5, r6, r7, r8, fp, ip, sp, lr, pc}
d001d0fc:	8121f000 	msrhi	CPSR_c, r0
d001d100:	e07e463e 	rsbs	r4, lr, lr, lsr r6
d001d104:	0004b2a8 	andeq	fp, r4, r8, lsr #5
d001d108:	000059c0 	andeq	r5, r0, r0, asr #19
d001d10c:	fffff77f 			; <UNDEFINED> instruction: 0xfffff77f
d001d110:	fffff742 			; <UNDEFINED> instruction: 0xfffff742
d001d114:	00055ee4 	andeq	r5, r5, r4, ror #29
d001d118:	0000ac28 	andeq	sl, r0, r8, lsr #24
d001d11c:	ffff3350 			; <UNDEFINED> instruction: 0xffff3350
d001d120:	00055ed4 	ldrdeq	r5, [r5], -r4
d001d124:	00055eca 	andeq	r5, r5, sl, asr #29
d001d128:	000020f3 	strdeq	r2, [r0], -r3
d001d12c:	0000abde 	ldrdeq	sl, [r0], -lr
d001d130:	0000abc6 	andeq	sl, r0, r6, asr #23
d001d134:	0000abb0 			; <UNDEFINED> instruction: 0x0000abb0
d001d138:	0000aba4 	andeq	sl, r0, r4, lsr #23
d001d13c:	00001ebd 			; <UNDEFINED> instruction: 0x00001ebd
d001d140:	00001f65 	andeq	r1, r0, r5, ror #30
d001d144:	0000ab36 	andeq	sl, r0, r6, lsr fp
d001d148:	fffffd99 			; <UNDEFINED> instruction: 0xfffffd99
d001d14c:	0000ab14 	andeq	sl, r0, r4, lsl fp
d001d150:	0000aace 	andeq	sl, r0, lr, asr #21
d001d154:	fffffd3f 			; <UNDEFINED> instruction: 0xfffffd3f
d001d158:	0000aab6 			; <UNDEFINED> instruction: 0x0000aab6
d001d15c:	0000aaa8 	andeq	sl, r0, r8, lsr #21
d001d160:	0000aaa2 	andeq	sl, r0, r2, lsr #21
d001d164:	0000aa76 	andeq	sl, r0, r6, ror sl
d001d168:	0000aa3c 	andeq	sl, r0, ip, lsr sl
d001d16c:	0000aa0c 	andeq	sl, r0, ip, lsl #20
d001d170:	7c8bf46f 	cfstrsvc	mvf15, [fp], {111}	; 0x6f
d001d174:	030ceb06 	movweq	lr, #51974	; 0xcb06
d001d178:	d84b2b01 	stmdale	fp, {r0, r8, r9, fp, sp}^
d001d17c:	708cf5a6 	addvc	pc, ip, r6, lsr #11
d001d180:	41464246 	cmpmi	r6, r6, asr #4
d001d184:	f7f54620 			; <UNDEFINED> instruction: 0xf7f54620
d001d188:	f104fe8d 			; <UNDEFINED> instruction: 0xf104fe8d
d001d18c:	f8d40c18 			; <UNDEFINED> instruction: 0xf8d40c18
d001d190:	f894802c 			; <UNDEFINED> instruction: 0xf894802c
d001d194:	e8bc9030 	ldm	ip!, {r4, r5, ip, pc}
d001d198:	c50f000f 	strgt	r0, [pc, #-15]	; 0xd001d191
d001d19c:	000fe89c 	muleq	pc, ip, r8	; <UNPREDICTABLE>
d001d1a0:	000fe885 	andeq	lr, pc, r5, lsl #17
d001d1a4:	930f6a63 	movwls	r6, #64099	; 0xfa63
d001d1a8:	93106aa3 	tstls	r0, #667648	; 0xa3000
d001d1ac:	93116b63 	tstls	r1, #101376	; 0x18c00
d001d1b0:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d001d1b4:	e9d44598 	ldmib	r4, {r3, r4, r7, r8, sl, lr}^
d001d1b8:	d102ba06 	tstle	r2, r6, lsl #20
d001d1bc:	f7f54620 			; <UNDEFINED> instruction: 0xf7f54620
d001d1c0:	f8dffe71 			; <UNDEFINED> instruction: 0xf8dffe71
d001d1c4:	447c4c18 	ldrbtmi	r4, [ip], #-3096	; 0xfffff3e8
d001d1c8:	2b7b6ae3 	blcs	0xd1ef7d5c
d001d1cc:	80e3f000 	rschi	pc, r3, r0
d001d1d0:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d001d1d4:	d1164598 			; <UNDEFINED> instruction: 0xd1164598
d001d1d8:	46524633 			; <UNDEFINED> instruction: 0x46524633
d001d1dc:	46204659 			; <UNDEFINED> instruction: 0x46204659
d001d1e0:	fa7cf7f3 	blx	0xd1f5b1b4
d001d1e4:	da331e05 	ble	0xd0ce4a00
d001d1e8:	b9536da3 	ldmdblt	r3, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d001d1ec:	3bf0f8df 	blcc	0xcfc5b570
d001d1f0:	65a3447b 	strvs	r4, [r3, #1147]!	; 0x47b
d001d1f4:	65e39b0f 	strbvs	r9, [r3, #2831]!	; 0xb0f
d001d1f8:	e9c49b10 	stmib	r4, {r4, r8, r9, fp, ip, pc}^
d001d1fc:	9b113918 	blls	0xd046b664
d001d200:	25ff66a3 	ldrbcs	r6, [pc, #1699]!	; 0xd001d8ab
d001d204:	f8dfe024 			; <UNDEFINED> instruction: 0xf8dfe024
d001d208:	46201bdc 			; <UNDEFINED> instruction: 0x46201bdc
d001d20c:	f7f34479 			; <UNDEFINED> instruction: 0xf7f34479
d001d210:	e7f6f81d 			; <UNDEFINED> instruction: 0xe7f6f81d
d001d214:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d001d218:	f040429e 			; <UNDEFINED> instruction: 0xf040429e
d001d21c:	462080b6 			; <UNDEFINED> instruction: 0x462080b6
d001d220:	1206e9d4 	andne	lr, r6, #212, 18	; 0x350000
d001d224:	fb07f7f3 	blx	0xd021b1fa
d001d228:	da062800 	ble	0xd01a7230
d001d22c:	1bb8f8df 	blne	0xcee5b5b0
d001d230:	46204479 			; <UNDEFINED> instruction: 0x46204479
d001d234:	f80af7f3 			; <UNDEFINED> instruction: 0xf80af7f3
d001d238:	2324e762 			; <UNDEFINED> instruction: 0x2324e762
d001d23c:	fb03463e 	blx	0xd00eeb3e
d001d240:	f5004000 			; <UNDEFINED> instruction: 0xf5004000
d001d244:	f8903075 			; <UNDEFINED> instruction: 0xf8903075
d001d248:	462053ac 	strtmi	r5, [r0], -ip, lsr #7
d001d24c:	fe2af7f5 	mcr2	7, 1, pc, cr10, cr5, {7}	; <UNPREDICTABLE>
d001d250:	4b98f8df 	blmi	0xce65b5d4
d001d254:	6da3447c 	cfstrsvs	mvf4, [r3, #496]!	; 0x1f0
d001d258:	d1722b00 	cmnle	r2, r0, lsl #22
d001d25c:	9b0fb357 	blls	0xd0409fc0
d001d260:	f88daf2e 			; <UNDEFINED> instruction: 0xf88daf2e
d001d264:	f10d90d0 			; <UNDEFINED> instruction: 0xf10d90d0
d001d268:	93310c18 	teqls	r1, #24, 24	; 0x1800
d001d26c:	9b10463d 	blls	0xd042eb68
d001d270:	3832e9cd 	ldmdacc	r2!, {r0, r2, r3, r6, r7, r8, fp, sp, lr, pc}
d001d274:	e9cd9b11 	stmib	sp, {r0, r4, r8, r9, fp, ip, pc}^
d001d278:	9335ba2e 	teqls	r5, #188416	; 0x2e000
d001d27c:	e8accd0f 	stmia	ip!, {r0, r1, r2, r3, r8, sl, fp, lr, pc}
d001d280:	e895000f 	ldm	r5, {r0, r1, r2, r3}
d001d284:	e88c000f 	stm	ip, {r0, r1, r2, r3}
d001d288:	f240000f 	vhadd.s8	d16, d0, d15
d001d28c:	96041301 	strls	r1, [r4], -r1, lsl #6
d001d290:	0303ebb8 	movweq	lr, #15288	; 0x3bb8
d001d294:	2301bf18 	movwcs	fp, #7960	; 0x1f18
d001d298:	e8959305 	ldm	r5, {r0, r2, r8, r9, ip, pc}
d001d29c:	e88d000f 	stm	sp, {r0, r1, r2, r3}
d001d2a0:	e897000f 	ldm	r7, {r0, r1, r2, r3}
d001d2a4:	f7f7000f 			; <UNDEFINED> instruction: 0xf7f7000f
d001d2a8:	1e05f859 	mcrne	8, 0, pc, cr5, cr9, {2}	; <UNPREDICTABLE>
d001d2ac:	6da3db49 			; <UNDEFINED> instruction: 0x6da3db49
d001d2b0:	d1462b00 	cmple	r6, r0, lsl #22
d001d2b4:	4b38f8df 	blmi	0xd0e5b638
d001d2b8:	447caf36 	ldrbtmi	sl, [ip], #-3894	; 0xfffff0ca
d001d2bc:	f104463e 			; <UNDEFINED> instruction: 0xf104463e
d001d2c0:	e8bc0c18 	ldm	ip!, {r3, r4, sl, fp}
d001d2c4:	c60f000f 	strgt	r0, [pc], -pc
d001d2c8:	000fe89c 	muleq	pc, ip, r8	; <UNPREDICTABLE>
d001d2cc:	000fe886 	andeq	lr, pc, r6, lsl #17
d001d2d0:	2b20f8df 	blcs	0xd085b654
d001d2d4:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d001d2d8:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d001d2dc:	fe10f7f5 	mrc2	7, 0, pc, cr0, cr5, {7}
d001d2e0:	f8dfb378 			; <UNDEFINED> instruction: 0xf8dfb378
d001d2e4:	213b2b14 	teqcs	fp, r4, lsl fp
d001d2e8:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d001d2ec:	fe08f7f5 	mcr2	7, 0, pc, cr8, cr5, {7}	; <UNPREDICTABLE>
d001d2f0:	46beb338 			; <UNDEFINED> instruction: 0x46beb338
d001d2f4:	f8d7ae76 			; <UNDEFINED> instruction: 0xf8d7ae76
d001d2f8:	46b4a00c 	ldrtmi	sl, [r4], ip
d001d2fc:	8018f897 	mulshi	r8, r7, r8
d001d300:	000fe8be 			; <UNDEFINED> instruction: 0x000fe8be
d001d304:	000fe8ac 	andeq	lr, pc, ip, lsr #17
d001d308:	000fe89e 	muleq	pc, lr, r8	; <UNPREDICTABLE>
d001d30c:	000fe88c 	andeq	lr, pc, ip, lsl #17
d001d310:	1b00e9d7 	blne	0xd0057a74
d001d314:	46204681 	strtmi	r4, [r0], -r1, lsl #13
d001d318:	910f465a 	tstls	pc, sl, asr r6	; <UNPREDICTABLE>
d001d31c:	f7f369ff 			; <UNDEFINED> instruction: 0xf7f369ff
d001d320:	2800fa65 	stmdacs	r0, {r0, r2, r5, r6, r9, fp, ip, sp, lr, pc}
d001d324:	db38990f 	blle	0xd0e43768
d001d328:	3ad0f8df 	bcc	0xcf45b6ac
d001d32c:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d001d330:	f8dfb93a 			; <UNDEFINED> instruction: 0xf8dfb93a
d001d334:	669f2acc 	ldrvs	r2, [pc], ip, asr #21
d001d338:	e9c3447a 	stmib	r3, {r1, r3, r4, r5, r6, sl, lr}^
d001d33c:	e9c39818 	stmib	r3, {r3, r4, fp, ip, pc}^
d001d340:	f8df2a16 			; <UNDEFINED> instruction: 0xf8df2a16
d001d344:	447c4ac0 	ldrbtmi	r4, [ip], #-2752	; 0xfffff540
d001d348:	b9266da6 	stmdblt	r6!, {r1, r2, r5, r7, r8, sl, fp, sp, lr}
d001d34c:	f5b36ae3 			; <UNDEFINED> instruction: 0xf5b36ae3
d001d350:	f47f7f80 			; <UNDEFINED> instruction: 0xf47f7f80
d001d354:	f8dfaea1 			; <UNDEFINED> instruction: 0xf8dfaea1
d001d358:	9b1a2ab0 	blls	0xd06a7e20
d001d35c:	685b447a 	ldmdavs	fp, {r1, r3, r4, r5, r6, sl, lr}^
d001d360:	440b6811 	strmi	r6, [fp], #-2065	; 0xfffff7ef
d001d364:	b9266013 	stmdblt	r6!, {r0, r1, r4, sp, lr}
d001d368:	0aa0f8df 	beq	0xce85b6ec
d001d36c:	f7f24478 			; <UNDEFINED> instruction: 0xf7f24478
d001d370:	9a1aff31 	bls	0xd06dd03c
d001d374:	32089918 	andcc	r9, r8, #24, 18	; 0x60000
d001d378:	921a9b18 	andsls	r9, sl, #24, 22	; 0x6000
d001d37c:	9a173301 	bls	0xd05e9f88
d001d380:	f001428a 			; <UNDEFINED> instruction: 0xf001428a
d001d384:	9318811f 	tstls	r8, #-1073741817	; 0xc0000007
d001d388:	f8dfe5ab 			; <UNDEFINED> instruction: 0xf8dfe5ab
d001d38c:	44791a84 	ldrbtmi	r1, [r9], #-2692	; 0xfffff57c
d001d390:	4637e74f 	ldrtmi	lr, [r7], -pc, asr #14
d001d394:	2701e735 	smladxcs	r1, r5, r7, lr
d001d398:	465ae733 			; <UNDEFINED> instruction: 0x465ae733
d001d39c:	910f4620 	tstls	pc, r0, lsr #12
d001d3a0:	fa8df7f3 	blx	0xce39b374
d001d3a4:	990f2800 	stmdbls	pc, {fp, sp}	; <UNPREDICTABLE>
d001d3a8:	465adabe 			; <UNDEFINED> instruction: 0x465adabe
d001d3ac:	910f4620 	tstls	pc, r0, lsr #12
d001d3b0:	fa41f7f3 	blx	0xd109b384
d001d3b4:	990f2800 	stmdbls	pc, {fp, sp}	; <UNPREDICTABLE>
d001d3b8:	2324db14 			; <UNDEFINED> instruction: 0x2324db14
d001d3bc:	4000fb03 	andmi	pc, r0, r3, lsl #22
d001d3c0:	3075f500 	rsbscc	pc, r5, r0, lsl #10
d001d3c4:	33acf890 			; <UNDEFINED> instruction: 0x33acf890
d001d3c8:	d0ba429d 	umlalsle	r4, sl, sp, r2
d001d3cc:	2b006da3 	blcs	0xd0038a60
d001d3d0:	f8dfd1b7 			; <UNDEFINED> instruction: 0xf8dfd1b7
d001d3d4:	447b3a40 	ldrbtmi	r3, [fp], #-2624	; 0xfffff5c0
d001d3d8:	e9c466a7 	stmib	r4, {r0, r1, r2, r5, r7, r9, sl, sp, lr}^
d001d3dc:	e9c43a16 	stmib	r4, {r1, r2, r4, r9, fp, ip, sp}^
d001d3e0:	e7ae9818 			; <UNDEFINED> instruction: 0xe7ae9818
d001d3e4:	3278f504 	rsbscc	pc, r8, #4, 10	; 0x1000000
d001d3e8:	308cf8d2 	ldrdcc	pc, [ip], r2
d001d3ec:	d1062b40 	tstle	r6, r0, asr #22
d001d3f0:	2b006da3 	blcs	0xd0038a84
d001d3f4:	f8dfd1a5 			; <UNDEFINED> instruction: 0xf8dfd1a5
d001d3f8:	447b3a20 	ldrbtmi	r3, [fp], #-2592	; 0xfffff5e0
d001d3fc:	1c58e7ec 	mrrcne	7, 14, lr, r8, cr12
d001d400:	c008f894 	mulgt	r8, r4, r8
d001d404:	a00cf8c6 	andge	pc, ip, r6, asr #17
d001d408:	008cf8c2 	addeq	pc, ip, r2, asr #17
d001d40c:	61f72224 	mvnsvs	r2, r4, lsr #4
d001d410:	4403fb02 	strmi	pc, [r3], #-2818	; 0xfffff4fe
d001d414:	9010f8c6 	andsls	pc, r0, r6, asr #17
d001d418:	3475f504 	ldrbtcc	pc, [r5], #-1284	; 0xfffffafc	; <UNPREDICTABLE>
d001d41c:	8018f886 	andshi	pc, r8, r6, lsl #17
d001d420:	1b00e9c6 	blne	0xd0057b40
d001d424:	7763f504 	strbvc	pc, [r3, -r4, lsl #10]!	; <UNPREDICTABLE>
d001d428:	53acf884 			; <UNDEFINED> instruction: 0x53acf884
d001d42c:	c3adf884 			; <UNDEFINED> instruction: 0xc3adf884
d001d430:	c70fce0f 	strgt	ip, [pc, -pc, lsl #28]
d001d434:	000fe896 	muleq	pc, r6, r8	; <UNPREDICTABLE>
d001d438:	000fe887 	andeq	lr, pc, r7, lsl #17
d001d43c:	6ae6e781 	bvs	0xcf9d7248
d001d440:	718bf46f 	orrvc	pc, fp, pc, ror #8
d001d444:	2b011873 	blcs	0xd0063618
d001d448:	f8d4d864 			; <UNDEFINED> instruction: 0xf8d4d864
d001d44c:	f240b04c 	vhadd.s8	<illegal reg q13.5>, q0, q6
d001d450:	459b1301 	ldrmi	r1, [fp, #769]	; 0x301
d001d454:	4620d15e 			; <UNDEFINED> instruction: 0x4620d15e
d001d458:	f7f5ad76 			; <UNDEFINED> instruction: 0xf7f5ad76
d001d45c:	f104fd23 			; <UNDEFINED> instruction: 0xf104fd23
d001d460:	46ac0e18 	ssatmi	r0, #13, r8, lsl #28
d001d464:	a028f8d4 	ldrdge	pc, [r8], -r4	; <UNPREDICTABLE>
d001d468:	9030f894 	mlasls	r0, r4, r8, pc	; <UNPREDICTABLE>
d001d46c:	8034f8d4 	ldrsbthi	pc, [r4], -r4	; <UNPREDICTABLE>
d001d470:	000fe8be 			; <UNDEFINED> instruction: 0x000fe8be
d001d474:	000fe8ac 	andeq	lr, pc, ip, lsr #17
d001d478:	000fe89e 	muleq	pc, lr, r8	; <UNPREDICTABLE>
d001d47c:	000fe88c 	andeq	lr, pc, ip, lsl #17
d001d480:	2998f8df 	ldmibcs	r8, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d001d484:	6a634659 	bvs	0xd18eedf0
d001d488:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d001d48c:	f7f5930f 			; <UNDEFINED> instruction: 0xf7f5930f
d001d490:	2800fd37 	stmdacs	r0, {r0, r1, r2, r4, r5, r8, sl, fp, ip, sp, lr, pc}
d001d494:	af55f43f 	svcge	0x0055f43f
d001d498:	9b0f6ae2 	blls	0xd03f8028
d001d49c:	d12b2a7b 			; <UNDEFINED> instruction: 0xd12b2a7b
d001d4a0:	f8c546ac 			; <UNDEFINED> instruction: 0xf8c546ac
d001d4a4:	f885a010 			; <UNDEFINED> instruction: 0xf885a010
d001d4a8:	f10d9018 			; <UNDEFINED> instruction: 0xf10d9018
d001d4ac:	f8c50e18 			; <UNDEFINED> instruction: 0xf8c50e18
d001d4b0:	60eb801c 	rscvs	r8, fp, ip, lsl r0
d001d4b4:	000fe8bc 			; <UNDEFINED> instruction: 0x000fe8bc
d001d4b8:	000fe8ae 	andeq	lr, pc, lr, lsr #17
d001d4bc:	000fe89c 	muleq	pc, ip, r8	; <UNPREDICTABLE>
d001d4c0:	000fe88e 	andeq	lr, pc, lr, lsl #17
d001d4c4:	728cf5a6 	addvc	pc, ip, #696254464	; 0x29800000
d001d4c8:	42569705 	subsmi	r9, r6, #1310720	; 0x140000
d001d4cc:	96044156 			; <UNDEFINED> instruction: 0x96044156
d001d4d0:	000fe89c 	muleq	pc, ip, r8	; <UNPREDICTABLE>
d001d4d4:	000fe88d 	andeq	lr, pc, sp, lsl #17
d001d4d8:	000fe895 	muleq	pc, r5, r8	; <UNPREDICTABLE>
d001d4dc:	ff3ef7f6 			; <UNDEFINED> instruction: 0xff3ef7f6
d001d4e0:	2b006da3 	blcs	0xd0038b74
d001d4e4:	af2df47f 	svcge	0x002df47f
d001d4e8:	2934f8df 	ldmdbcs	r4!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d001d4ec:	4620213b 			; <UNDEFINED> instruction: 0x4620213b
d001d4f0:	f7f5447a 			; <UNDEFINED> instruction: 0xf7f5447a
d001d4f4:	e724fd05 	str	pc, [r4, -r5, lsl #26]!
d001d4f8:	2a006da2 	bcs	0xd0038b88
d001d4fc:	af21f47f 	svcge	0x0021f47f
d001d500:	2920f8df 	stmdbcs	r0!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d001d504:	8068f8c4 	rsbhi	pc, r8, r4, asr #17
d001d508:	e9c4447a 	stmib	r4, {r1, r3, r4, r5, r6, sl, lr}^
d001d50c:	e9c4a918 	stmib	r4, {r3, r4, r8, fp, sp, pc}^
d001d510:	e7162316 			; <UNDEFINED> instruction: 0xe7162316
d001d514:	5910f8df 	ldmdbpl	r0, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d001d518:	7183f44f 	orrvc	pc, r3, pc, asr #8
d001d51c:	4628447d 			; <UNDEFINED> instruction: 0x4628447d
d001d520:	fce0f7f5 	stc2l	7, cr15, [r0], #980	; 0x3d4
d001d524:	f505b150 			; <UNDEFINED> instruction: 0xf505b150
d001d528:	331c4350 	tstcc	ip, #80, 6	; 0x40000001
d001d52c:	2b00681b 	blcs	0xd00375a0
d001d530:	af07f47f 	svcge	0x0007f47f
d001d534:	f7fe6f28 			; <UNDEFINED> instruction: 0xf7fe6f28
d001d538:	e702fee5 	str	pc, [r2, -r5, ror #29]
d001d53c:	7188f44f 	orrvc	pc, r8, pc, asr #8
d001d540:	f7f54628 			; <UNDEFINED> instruction: 0xf7f54628
d001d544:	f44ffccf 			; <UNDEFINED> instruction: 0xf44ffccf
d001d548:	90147185 	andsls	r7, r4, r5, lsl #3
d001d54c:	f7f54628 			; <UNDEFINED> instruction: 0xf7f54628
d001d550:	6aeafcc9 	bvs	0xcfadc87c
d001d554:	131bf240 	tstne	fp, #64, 4	; <UNPREDICTABLE>
d001d558:	46284604 	strtmi	r4, [r8], -r4, lsl #12
d001d55c:	d14f429a 			; <UNDEFINED> instruction: 0xd14f429a
d001d560:	ffc0f7f5 			; <UNDEFINED> instruction: 0xffc0f7f5
d001d564:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001d568:	213baeec 	teqcs	fp, ip, ror #29
d001d56c:	f7f54628 			; <UNDEFINED> instruction: 0xf7f54628
d001d570:	4607fcb9 			; <UNDEFINED> instruction: 0x4607fcb9
d001d574:	f47f2800 			; <UNDEFINED> instruction: 0xf47f2800
d001d578:	ae76aee4 	cdpge	14, 7, cr10, cr6, cr4, {7}
d001d57c:	0e18f105 	mnfeqe	f7, f5
d001d580:	b024f8d5 	ldrdlt	pc, [r4], -r5	; <UNPREDICTABLE>
d001d584:	f8d546b4 			; <UNDEFINED> instruction: 0xf8d546b4
d001d588:	f895a028 			; <UNDEFINED> instruction: 0xf895a028
d001d58c:	f8d59030 			; <UNDEFINED> instruction: 0xf8d59030
d001d590:	e8be8034 	ldm	lr!, {r2, r4, r5, pc}
d001d594:	e8ac000f 	stmia	ip!, {r0, r1, r2, r3}
d001d598:	e89e000f 	ldm	lr, {r0, r1, r2, r3}
d001d59c:	e88c000f 	stm	ip, {r0, r1, r2, r3}
d001d5a0:	f8df000f 			; <UNDEFINED> instruction: 0xf8df000f
d001d5a4:	f2402888 	vadd.i8	d18, d16, d8
d001d5a8:	46281101 	strtmi	r1, [r8], -r1, lsl #2
d001d5ac:	f7f5447a 			; <UNDEFINED> instruction: 0xf7f5447a
d001d5b0:	2800fca7 	stmdacs	r0, {r0, r1, r2, r5, r7, sl, fp, ip, sp, lr, pc}
d001d5b4:	aec5f43f 	mcrge	4, 6, pc, cr5, cr15, {1}	; <UNPREDICTABLE>
d001d5b8:	43239b14 			; <UNDEFINED> instruction: 0x43239b14
d001d5bc:	6dabd10d 	stfvsd	f5, [fp, #52]!	; 0x34
d001d5c0:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001d5c4:	f8dfaebe 			; <UNDEFINED> instruction: 0xf8dfaebe
d001d5c8:	f8c53868 			; <UNDEFINED> instruction: 0xf8c53868
d001d5cc:	447b8068 	ldrbtmi	r8, [fp], #-104	; 0xffffff98
d001d5d0:	a918e9c5 	ldmdbge	r8, {r0, r2, r6, r7, r8, fp, sp, lr, pc}
d001d5d4:	3b16e9c5 	blcc	0xd05d7cf0
d001d5d8:	ab7ae6b3 	blge	0xd1ed70ac
d001d5dc:	b00cf8c6 	andlt	pc, ip, r6, asr #17
d001d5e0:	a010f8c6 	andsge	pc, r0, r6, asr #17
d001d5e4:	9018f886 	andsls	pc, r8, r6, lsl #17
d001d5e8:	801cf8c6 	andshi	pc, ip, r6, asr #17
d001d5ec:	97049405 	strls	r9, [r4, -r5, lsl #8]
d001d5f0:	e88dcb0f 	stm	sp, {r0, r1, r2, r3, r8, r9, fp, lr, pc}
d001d5f4:	e896000f 	ldm	r6, {r0, r1, r2, r3}
d001d5f8:	f7fe000f 			; <UNDEFINED> instruction: 0xf7fe000f
d001d5fc:	e6a0fbed 	strt	pc, [r0], sp, ror #23
d001d600:	f93ef7f3 			; <UNDEFINED> instruction: 0xf93ef7f3
d001d604:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d001d608:	b13481da 	teqlt	r4, sl	; <illegal shifter operand>
d001d60c:	1824f8df 	stmdane	r4!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d001d610:	44794628 	ldrbtmi	r4, [r9], #-1576	; 0xfffff9d8
d001d614:	fe1af7f2 	mrc2	7, 0, pc, cr10, cr2, {7}
d001d618:	af36e693 	svcge	0x0036e693
d001d61c:	603c4628 	eorsvs	r4, ip, r8, lsr #12
d001d620:	f7f54639 			; <UNDEFINED> instruction: 0xf7f54639
d001d624:	2800fe69 	stmdacs	r0, {r0, r3, r5, r6, r9, sl, fp, ip, sp, lr, pc}
d001d628:	ae8bf43f 	mcrge	4, 4, pc, cr11, cr15, {1}	; <UNPREDICTABLE>
d001d62c:	4628212a 	strtmi	r2, [r8], -sl, lsr #2
d001d630:	fc58f7f5 	mrrc2	7, 15, pc, r8, cr5	; <UNPREDICTABLE>
d001d634:	f105ae76 			; <UNDEFINED> instruction: 0xf105ae76
d001d638:	46040e18 			; <UNDEFINED> instruction: 0x46040e18
d001d63c:	f89546b4 			; <UNDEFINED> instruction: 0xf89546b4
d001d640:	e8be9030 	ldm	lr!, {r4, r5, ip, pc}
d001d644:	e8ac000f 	stmia	ip!, {r0, r1, r2, r3}
d001d648:	e89e000f 	ldm	lr, {r0, r1, r2, r3}
d001d64c:	e88c000f 	stm	ip, {r0, r1, r2, r3}
d001d650:	6a6b000f 	bvs	0xd1add694
d001d654:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d001d658:	27dcf8df 			; <UNDEFINED> instruction: 0x27dcf8df
d001d65c:	930f4628 	movwls	r4, #63016	; 0xf628
d001d660:	447a6aab 	ldrbtmi	r6, [sl], #-2731	; 0xfffff555
d001d664:	6b6b9311 	blvs	0xd1b022b0
d001d668:	ba06e9d5 	blt	0xd01d7dc4
d001d66c:	f7f59310 			; <UNDEFINED> instruction: 0xf7f59310
d001d670:	2800fc47 	stmdacs	r0, {r0, r1, r2, r6, sl, fp, ip, sp, lr, pc}
d001d674:	ae65f43f 	mcrge	4, 3, pc, cr5, cr15, {1}	; <UNPREDICTABLE>
d001d678:	2b286aeb 	blcs	0xd0a3822c
d001d67c:	683bd145 	ldmdavs	fp!, {r0, r2, r6, r8, ip, lr, pc}
d001d680:	ac262c00 	stcge	12, cr2, [r6], #-0
d001d684:	9018f886 	andsls	pc, r8, r6, lsl #17
d001d688:	bf14931b 	svclt	0x0014931b
d001d68c:	23042305 	movwcs	r2, #17157	; 0x4305
d001d690:	93134625 	tstls	r3, #38797312	; 0x2500000
d001d694:	60f39b0f 	rscsvs	r9, r3, pc, lsl #22
d001d698:	61339b11 	teqvs	r3, r1, lsl fp
d001d69c:	e9c69b10 	stmib	r6, {r4, r8, r9, fp, ip, pc}^
d001d6a0:	61f3ba00 	mvnsvs	fp, r0, lsl #20
d001d6a4:	c50fce0f 	strgt	ip, [pc, #-3599]	; 0xd001c89d
d001d6a8:	000fe896 	muleq	pc, r6, r8	; <UNPREDICTABLE>
d001d6ac:	000fe885 	andeq	lr, pc, r5, lsl #17
d001d6b0:	ae2e9b10 	vmovge.32	d14[1], r9
d001d6b4:	b098f8cd 	addslt	pc, r8, sp, asr #17
d001d6b8:	90b0f88d 	adcsls	pc, r0, sp, lsl #17
d001d6bc:	cc0f932d 	stcgt	3, cr9, [pc], {45}	; 0x2d
d001d6c0:	e895c60f 	ldm	r5, {r0, r1, r2, r3, r9, sl, lr, pc}
d001d6c4:	e886000f 	stm	r6, {r0, r1, r2, r3}
d001d6c8:	f8df000f 			; <UNDEFINED> instruction: 0xf8df000f
d001d6cc:	21284770 			; <UNDEFINED> instruction: 0x21284770
d001d6d0:	276cf8df 			; <UNDEFINED> instruction: 0x276cf8df
d001d6d4:	447a447c 	ldrbtmi	r4, [sl], #-1148	; 0xfffffb84
d001d6d8:	f7f54620 			; <UNDEFINED> instruction: 0xf7f54620
d001d6dc:	2800fc11 	stmdacs	r0, {r0, r4, sl, fp, ip, sp, lr, pc}
d001d6e0:	ae2ff43f 	mcrge	4, 1, pc, cr15, cr15, {1}	; <UNPREDICTABLE>
d001d6e4:	46594652 			; <UNDEFINED> instruction: 0x46594652
d001d6e8:	f7f34620 			; <UNDEFINED> instruction: 0xf7f34620
d001d6ec:	2800f8a4 	stmdacs	r0, {r2, r5, r7, fp, ip, sp, lr, pc}
d001d6f0:	822af2c0 	eorhi	pc, sl, #192, 4
d001d6f4:	374cf8df 			; <UNDEFINED> instruction: 0x374cf8df
d001d6f8:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d001d6fc:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d001d700:	f8dfae20 			; <UNDEFINED> instruction: 0xf8dfae20
d001d704:	447a2744 	ldrbtmi	r2, [sl], #-1860	; 0xfffff8bc
d001d708:	b17ce01c 	cmnlt	ip, ip, lsl r0
d001d70c:	2b006dab 	blcs	0xd0038dc0
d001d710:	ae17f47f 	mrcge	4, 0, APSR_nzcv, cr7, cr15, {3}
d001d714:	3734f8df 			; <UNDEFINED> instruction: 0x3734f8df
d001d718:	65ab447b 	strvs	r4, [fp, #1147]!	; 0x47b
d001d71c:	65eb9b0f 	strbvs	r9, [fp, #2831]!	; 0xb0f
d001d720:	e9c59b11 	stmib	r5, {r0, r4, r8, r9, fp, ip, pc}^
d001d724:	9b103918 	blls	0xd042bb8c
d001d728:	e60a66ab 	str	r6, [sl], -fp, lsr #13
d001d72c:	b98b9b14 	stmiblt	fp, {r2, r4, r8, r9, fp, ip, pc}
d001d730:	2b006dab 	blcs	0xd0038de4
d001d734:	ae05f47f 	mcrge	4, 0, pc, cr5, cr15, {3}	; <UNPREDICTABLE>
d001d738:	3714f8df 			; <UNDEFINED> instruction: 0x3714f8df
d001d73c:	2714f8df 			; <UNDEFINED> instruction: 0x2714f8df
d001d740:	447a447b 	ldrbtmi	r4, [sl], #-1147	; 0xfffffb85
d001d744:	9a0f659a 	bls	0xd03f6db4
d001d748:	9a1165da 	bls	0xd0476eb8
d001d74c:	2918e9c3 	ldmdbcs	r8, {r0, r1, r6, r7, r8, fp, sp, lr, pc}
d001d750:	e03e9a10 	eors	r9, lr, r0, lsl sl
d001d754:	215b4628 	cmpcs	fp, r8, lsr #12
d001d758:	fbc4f7f5 	blx	0xcf15b736
d001d75c:	f44f683b 	vst2.8	{d22-d23}, [pc :256], fp
d001d760:	4680721a 	pkhbtmi	r7, r0, sl, lsl #4
d001d764:	5503fb02 	strpl	pc, [r3, #-2818]	; 0xfffff4fe
d001d768:	3568f505 	strbcc	pc, [r8, #-1285]!	; 0xfffffafb	; <UNPREDICTABLE>
d001d76c:	28008d2e 	stmdacs	r0, {r1, r2, r3, r5, r8, sl, fp, pc}
d001d770:	f8dfd076 			; <UNDEFINED> instruction: 0xf8dfd076
d001d774:	447d56e4 	ldrbtmi	r5, [sp], #-1764	; 0xfffff91c
d001d778:	f5a26aea 			; <UNDEFINED> instruction: 0xf5a26aea
d001d77c:	2a017281 	bcs	0xd007a188
d001d780:	6a2fd808 	bvs	0xd0c137a8
d001d784:	00b1b137 	adcseq	fp, r1, r7, lsr r1
d001d788:	1280f44f 	addne	pc, r0, #1325400064	; 0x4f000000
d001d78c:	f2f1fbb2 			; <UNDEFINED> instruction: 0xf2f1fbb2
d001d790:	d9244297 	stmdble	r4!, {r0, r1, r2, r4, r7, r9, lr}
d001d794:	26c4f8df 			; <UNDEFINED> instruction: 0x26c4f8df
d001d798:	711af44f 	tstvc	sl, pc, asr #8	; <UNPREDICTABLE>
d001d79c:	fb01447a 	blx	0xd006e98e
d001d7a0:	f5032303 			; <UNDEFINED> instruction: 0xf5032303
d001d7a4:	f8933368 			; <UNDEFINED> instruction: 0xf8933368
d001d7a8:	b9a3302b 	stmiblt	r3!, {r0, r1, r3, r5, ip, sp}
d001d7ac:	46b0f8df 	ssatmi	pc, #17, pc, asr #17	; <UNPREDICTABLE>
d001d7b0:	f8df447c 			; <UNDEFINED> instruction: 0xf8df447c
d001d7b4:	447b36b0 	ldrbtmi	r3, [fp], #-1712	; 0xfffff950
d001d7b8:	2a006d9a 	bcs	0xd0038e28
d001d7bc:	adc1f47f 	cfstrdge	mvd15, [r1, #508]	; 0x1fc
d001d7c0:	6a996a58 	bvs	0xce678128
d001d7c4:	5030f893 	mlaspl	r0, r3, r8, pc	; <UNPREDICTABLE>
d001d7c8:	e9c36b5a 	stmib	r3, {r1, r3, r4, r6, r8, r9, fp, sp, lr}^
d001d7cc:	e9c34016 	stmib	r3, {r1, r2, r4, lr}^
d001d7d0:	669a1518 			; <UNDEFINED> instruction: 0x669a1518
d001d7d4:	f8dfe5b5 			; <UNDEFINED> instruction: 0xf8dfe5b5
d001d7d8:	447c4690 	ldrbtmi	r4, [ip], #-1680	; 0xfffff970
d001d7dc:	4628e7e9 	strtmi	lr, [r8], -r9, ror #15
d001d7e0:	fb60f7f5 	blx	0xd185b7be
d001d7e4:	2684f8df 	pkhtbcs	pc, r4, pc, asr #17	; <UNPREDICTABLE>
d001d7e8:	4628215d 			; <UNDEFINED> instruction: 0x4628215d
d001d7ec:	f7f5447a 			; <UNDEFINED> instruction: 0xf7f5447a
d001d7f0:	2800fb87 	stmdacs	r0, {r0, r1, r2, r7, r8, r9, fp, ip, sp, lr, pc}
d001d7f4:	ada5f43f 	cfstrsge	mvf15, [r5, #252]!	; 0xfc
d001d7f8:	0674f8df 			; <UNDEFINED> instruction: 0x0674f8df
d001d7fc:	437e213d 	cmnmi	lr, #1073741839	; 0x4000000f
d001d800:	f5004478 			; <UNDEFINED> instruction: 0xf5004478
d001d804:	f8d5357f 			; <UNDEFINED> instruction: 0xf8d5357f
d001d808:	93123224 	tstls	r2, #36, 4	; 0x40000002
d001d80c:	fb6af7f5 	blx	0xd1adb7ea
d001d810:	f8d5b138 			; <UNDEFINED> instruction: 0xf8d5b138
d001d814:	f5c33224 			; <UNDEFINED> instruction: 0xf5c33224
d001d818:	429e13be 	addsmi	r1, lr, #-134217726	; 0xf8000002
d001d81c:	f7f6d922 			; <UNDEFINED> instruction: 0xf7f6d922
d001d820:	f8dffb9b 			; <UNDEFINED> instruction: 0xf8dffb9b
d001d824:	213b5650 	teqcs	fp, r0, asr r6
d001d828:	264cf8df 			; <UNDEFINED> instruction: 0x264cf8df
d001d82c:	447a447d 	ldrbtmi	r4, [sl], #-1149	; 0xfffffb83
d001d830:	f7f54628 			; <UNDEFINED> instruction: 0xf7f54628
d001d834:	2800fb65 	stmdacs	r0, {r0, r2, r5, r6, r8, r9, fp, ip, sp, lr, pc}
d001d838:	ad83f43f 	cfstrsge	mvf15, [r3, #252]	; 0xfc
d001d83c:	46594652 			; <UNDEFINED> instruction: 0x46594652
d001d840:	f7f24628 			; <UNDEFINED> instruction: 0xf7f24628
d001d844:	2800fff8 	stmdacs	r0, {r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d001d848:	f8dfdb33 			; <UNDEFINED> instruction: 0xf8dfdb33
d001d84c:	447b3630 	ldrbtmi	r3, [fp], #-1584	; 0xfffff9d0
d001d850:	2a006d9a 	bcs	0xd0038ec0
d001d854:	ad75f47f 	cfldrdge	mvd15, [r5, #-508]!	; 0xfffffe04
d001d858:	2624f8df 			; <UNDEFINED> instruction: 0x2624f8df
d001d85c:	e771447a 			; <UNDEFINED> instruction: 0xe771447a
d001d860:	e7c92701 	strb	r2, [r9, r1, lsl #14]
d001d864:	f7fe4630 			; <UNDEFINED> instruction: 0xf7fe4630
d001d868:	2800f9b7 	stmdacs	r0, {r0, r1, r2, r4, r5, r7, r8, fp, ip, sp, lr, pc}
d001d86c:	ad69f43f 	cfstrdge	mvd15, [r9, #-252]!	; 0xffffff04
d001d870:	f1b89836 			; <UNDEFINED> instruction: 0xf1b89836
d001d874:	d0160f00 	andsle	r0, r6, r0, lsl #30
d001d878:	46012200 	strmi	r2, [r1], -r0, lsl #4
d001d87c:	46382301 	ldrtmi	r2, [r8], -r1, lsl #6
d001d880:	f7fc9200 			; <UNDEFINED> instruction: 0xf7fc9200
d001d884:	f8dffc9d 			; <UNDEFINED> instruction: 0xf8dffc9d
d001d888:	447b35fc 	ldrbtmi	r3, [fp], #-1532	; 0xfffffa04
d001d88c:	337ff503 	cmncc	pc, #12582912	; 0xc00000	; <UNPREDICTABLE>
d001d890:	2220f893 	eorcs	pc, r0, #9633792	; 0x930000
d001d894:	d0c42a00 	sbcle	r2, r4, r0, lsl #20
d001d898:	2224f8d3 	eorcs	pc, r4, #13828096	; 0xd30000
d001d89c:	44322401 	ldrtmi	r2, [r2], #-1025	; 0xfffffbff
d001d8a0:	2224f8c3 	eorcs	pc, r4, #12779520	; 0xc30000
d001d8a4:	2301e7bd 	movwcs	lr, #6077	; 0x17bd
d001d8a8:	461a4641 	ldrmi	r4, [sl], -r1, asr #12
d001d8ac:	fb62f7fc 	blx	0xd18db8a6
d001d8b0:	4652e7e9 	ldrbmi	lr, [r2], -r9, ror #15
d001d8b4:	46284659 			; <UNDEFINED> instruction: 0x46284659
d001d8b8:	ff98f7f2 			; <UNDEFINED> instruction: 0xff98f7f2
d001d8bc:	dac42800 	ble	0xcf1278c4
d001d8c0:	46594652 			; <UNDEFINED> instruction: 0x46594652
d001d8c4:	f7f24628 			; <UNDEFINED> instruction: 0xf7f24628
d001d8c8:	2800fffa 	stmdacs	r0, {r1, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d001d8cc:	f505dabd 			; <UNDEFINED> instruction: 0xf505dabd
d001d8d0:	00b33267 	adcseq	r3, r3, r7, ror #4
d001d8d4:	11c4f8d2 	ldrdne	pc, [r4, #130]	; 0x82
d001d8d8:	d0082980 	andle	r2, r8, r0, lsl #19
d001d8dc:	327ff505 	rsbscc	pc, pc, #20971520	; 0x1400000
d001d8e0:	f8d2b984 			; <UNDEFINED> instruction: 0xf8d2b984
d001d8e4:	f5c3521c 			; <UNDEFINED> instruction: 0xf5c3521c
d001d8e8:	42851080 	addmi	r1, r5, #128	; 0x80
d001d8ec:	f8dfd960 			; <UNDEFINED> instruction: 0xf8dfd960
d001d8f0:	447b3598 	ldrbtmi	r3, [fp], #-1432	; 0xfffffa68
d001d8f4:	2a006d9a 	bcs	0xd0038f64
d001d8f8:	ad23f47f 	cfstrsge	mvf15, [r3, #-508]!	; 0xfffffe04
d001d8fc:	258cf8df 	strcs	pc, [ip, #2271]	; 0x8df
d001d900:	e71f447a 			; <UNDEFINED> instruction: 0xe71f447a
d001d904:	5218f8d2 	andspl	pc, r8, #13762560	; 0xd20000
d001d908:	f0253503 			; <UNDEFINED> instruction: 0xf0253503
d001d90c:	442b0503 	strtmi	r0, [fp], #-1283	; 0xfffffafd
d001d910:	3218f8c2 	andscc	pc, r8, #12713984	; 0xc20000
d001d914:	3578f8df 	ldrbcc	pc, [r8, #-2271]!	; 0xfffff721	; <UNPREDICTABLE>
d001d918:	0f00f1b8 	svceq	0x0000f1b8
d001d91c:	0001f101 	andeq	pc, r1, r1, lsl #2
d001d920:	f884fa5f 			; <UNDEFINED> instruction: 0xf884fa5f
d001d924:	f503447b 			; <UNDEFINED> instruction: 0xf503447b
d001d928:	f8c23267 			; <UNDEFINED> instruction: 0xf8c23267
d001d92c:	bf1401c4 	svclt	0x001401c4
d001d930:	220f2211 	andcs	r2, pc, #268435457	; 0x10000001
d001d934:	92152c00 	andsls	r2, r5, #0, 24
d001d938:	2600bf08 	strcs	fp, [r0], -r8, lsl #30
d001d93c:	92137a1a 	andsls	r7, r3, #106496	; 0x1a000
d001d940:	20d8f89d 	smullscs	pc, r8, sp, r8	; <UNPREDICTABLE>
d001d944:	223c9214 	eorscs	r9, ip, #20, 4	; 0x40000001
d001d948:	3401fb02 	strcc	pc, [r1], #-2818	; 0xfffff4fe
d001d94c:	f5042100 			; <UNDEFINED> instruction: 0xf5042100
d001d950:	f504345f 			; <UNDEFINED> instruction: 0xf504345f
d001d954:	46187371 			; <UNDEFINED> instruction: 0x46187371
d001d958:	fad0f003 	blx	0xcf45996c
d001d95c:	f50d9a0f 			; <UNDEFINED> instruction: 0xf50d9a0f
d001d960:	f88d7cec 			; <UNDEFINED> instruction: 0xf88d7cec
d001d964:	927991f0 	rsbsls	r9, r9, #240, 2	; 0x3c
d001d968:	9a114686 	bls	0xd046f388
d001d96c:	53e8f8c4 	mvnpl	pc, #196, 16	; 0xc40000
d001d970:	9a10927a 	bls	0xd0442360
d001d974:	ba76e9cd 	blt	0xd1dd80b0
d001d978:	e8bc927d 	ldm	ip!, {r0, r2, r3, r4, r5, r6, r9, ip, pc}
d001d97c:	e8ae000f 	stmia	lr!, {r0, r1, r2, r3}
d001d980:	e89c000f 	ldm	ip, {r0, r1, r2, r3}
d001d984:	e88e000f 	stm	lr, {r0, r1, r2, r3}
d001d988:	9b15000f 	blls	0xd055d9cc
d001d98c:	33ecf884 	mvncc	pc, #132, 16	; 0x840000
d001d990:	f8849b13 			; <UNDEFINED> instruction: 0xf8849b13
d001d994:	9b1433ed 	blls	0xd052a950
d001d998:	33eef884 	mvncc	pc, #132, 16	; 0x840000
d001d99c:	83eff884 	mvnhi	pc, #132, 16	; 0x840000
d001d9a0:	f8c49b12 			; <UNDEFINED> instruction: 0xf8c49b12
d001d9a4:	f8c463f8 			; <UNDEFINED> instruction: 0xf8c463f8
d001d9a8:	f8c433f4 			; <UNDEFINED> instruction: 0xf8c433f4
d001d9ac:	e4c873fc 	strb	r7, [r8], #1020	; 0x3fc
d001d9b0:	f0253503 			; <UNDEFINED> instruction: 0xf0253503
d001d9b4:	442b0503 	strtmi	r0, [fp], #-1283	; 0xfffffafd
d001d9b8:	321cf8c2 	andscc	pc, ip, #12713984	; 0xc20000
d001d9bc:	9b14e7aa 	blls	0xd055786c
d001d9c0:	f240b923 	vmla.i8	d27, d0, d19
d001d9c4:	46281109 	strtmi	r1, [r8], -r9, lsl #2
d001d9c8:	fa8cf7f5 	blx	0xce35b9a4
d001d9cc:	04c4f8df 	strbeq	pc, [r4], #2271	; 0x8df	; <UNPREDICTABLE>
d001d9d0:	7184f44f 	orrvc	pc, r4, pc, asr #8
d001d9d4:	f7f54478 			; <UNDEFINED> instruction: 0xf7f54478
d001d9d8:	4605fa85 	strmi	pc, [r5], -r5, lsl #21
d001d9dc:	f0402800 			; <UNDEFINED> instruction: 0xf0402800
d001d9e0:	f8df8083 			; <UNDEFINED> instruction: 0xf8df8083
d001d9e4:	447804b4 	ldrbtmi	r0, [r8], #-1204	; 0xfffffb4c
d001d9e8:	ff86f7f6 			; <UNDEFINED> instruction: 0xff86f7f6
d001d9ec:	28004682 	stmdacs	r0, {r1, r7, r9, sl, lr}
d001d9f0:	9b14d17d 	blls	0xd0551fec
d001d9f4:	f8dfb9a3 			; <UNDEFINED> instruction: 0xf8dfb9a3
d001d9f8:	f24054a4 	vshl.s8	d21, d20, d16
d001d9fc:	447d1107 	ldrbtmi	r1, [sp], #-263	; 0xfffffef9
d001da00:	f7f54628 			; <UNDEFINED> instruction: 0xf7f54628
d001da04:	2800fa6f 	stmdacs	r0, {r0, r1, r2, r3, r5, r6, r9, fp, ip, sp, lr, pc}
d001da08:	f8dfd04b 			; <UNDEFINED> instruction: 0xf8dfd04b
d001da0c:	212a0494 			; <UNDEFINED> instruction: 0x212a0494
d001da10:	f7f54478 			; <UNDEFINED> instruction: 0xf7f54478
d001da14:	2800fa67 	stmdacs	r0, {r0, r1, r2, r5, r6, r9, fp, ip, sp, lr, pc}
d001da18:	2500d06f 	strcs	sp, [r0, #-111]	; 0xffffff91
d001da1c:	e0152303 	ands	r2, r5, r3, lsl #6
d001da20:	0480f8df 	streq	pc, [r0], #2271	; 0x8df
d001da24:	f7f64478 			; <UNDEFINED> instruction: 0xf7f64478
d001da28:	2800ff67 	stmdacs	r0, {r0, r1, r2, r5, r6, r8, r9, sl, fp, ip, sp, lr, pc}
d001da2c:	f8dfd161 			; <UNDEFINED> instruction: 0xf8dfd161
d001da30:	44780478 	ldrbtmi	r0, [r8], #-1144	; 0xfffffb88
d001da34:	ff60f7f6 			; <UNDEFINED> instruction: 0xff60f7f6
d001da38:	f8dfb930 			; <UNDEFINED> instruction: 0xf8dfb930
d001da3c:	44780470 	ldrbtmi	r0, [r8], #-1136	; 0xfffffb90
d001da40:	ff5af7f6 			; <UNDEFINED> instruction: 0xff5af7f6
d001da44:	d0d62800 	sbcsle	r2, r6, r0, lsl #16
d001da48:	23002505 	movwcs	r2, #1285	; 0x505
d001da4c:	f8df9313 			; <UNDEFINED> instruction: 0xf8df9313
d001da50:	af2e6460 	svcge	0x002e6460
d001da54:	f106447e 			; <UNDEFINED> instruction: 0xf106447e
d001da58:	f8960c18 			; <UNDEFINED> instruction: 0xf8960c18
d001da5c:	e8bc9030 	ldm	ip!, {r4, r5, ip, pc}
d001da60:	c70f000f 	strgt	r0, [pc, -pc]
d001da64:	000fe89c 	muleq	pc, ip, r8	; <UNPREDICTABLE>
d001da68:	000fe887 	andeq	lr, pc, r7, lsl #17
d001da6c:	f2406a73 	vpmin.s8	q11, q0, <illegal reg q9.5>
d001da70:	f8df1101 			; <UNDEFINED> instruction: 0xf8df1101
d001da74:	46302440 	ldrtmi	r2, [r0], -r0, asr #8
d001da78:	6ab3930f 	bvs	0xced026bc
d001da7c:	9311447a 	tstls	r1, #2046820352	; 0x7a000000
d001da80:	e9d66b73 	ldmib	r6, {r0, r1, r4, r5, r6, r8, r9, fp, sp, lr}^
d001da84:	9310ba06 	tstls	r0, #24576	; 0x6000
d001da88:	fa3af7f5 	blx	0xd0edba64
d001da8c:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001da90:	9b14ac58 	blls	0xd0548bf8
d001da94:	2c00bba3 			; <UNDEFINED> instruction: 0x2c00bba3
d001da98:	814ff041 	cmphi	pc, r1, asr #32	; <UNPREDICTABLE>
d001da9c:	931b23ff 	tstls	fp, #-67108861	; 0xfc000003
d001daa0:	6aeae613 	bvs	0xcfad72f4
d001daa4:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d001daa8:	d118429a 			; <UNDEFINED> instruction: 0xd118429a
d001daac:	e9d54628 	ldmib	r5, {r3, r5, r9, sl, lr}^
d001dab0:	f7f21206 			; <UNDEFINED> instruction: 0xf7f21206
d001dab4:	2800fec0 	stmdacs	r0, {r6, r7, r9, sl, fp, ip, sp, lr, pc}
d001dab8:	4628db11 			; <UNDEFINED> instruction: 0x4628db11
d001dabc:	1206e9d5 	andne	lr, r6, #3489792	; 0x354000
d001dac0:	feb9f7f2 	mrc2	7, 5, pc, cr9, cr2, {7}
d001dac4:	fb032324 	blx	0xd00e675e
d001dac8:	f5005000 			; <UNDEFINED> instruction: 0xf5005000
d001dacc:	f8903075 			; <UNDEFINED> instruction: 0xf8903075
d001dad0:	2bff33ac 	blcs	0xcffea988
d001dad4:	4628d103 	strtmi	sp, [r8], -r3, lsl #2
d001dad8:	f9e4f7f5 			; <UNDEFINED> instruction: 0xf9e4f7f5
d001dadc:	49f6e795 	ldmibmi	r6!, {r0, r2, r4, r7, r8, r9, sl, sp, lr, pc}^
d001dae0:	447948f6 	ldrbtmi	r4, [r9], #-2294	; 0xfffff70a
d001dae4:	e5954478 	ldr	r4, [r5, #1144]	; 0x478
d001dae8:	23012500 	movwcs	r2, #5376	; 0x1500
d001daec:	2302e7ae 	movwcs	lr, #10158	; 0x27ae
d001daf0:	2501e7ac 	strcs	lr, [r1, #-1964]	; 0xfffff854
d001daf4:	a04cf8cd 	subge	pc, ip, sp, asr #17
d001daf8:	4605e7a9 	strmi	lr, [r5], -r9, lsr #15
d001dafc:	e7a69013 			; <UNDEFINED> instruction: 0xe7a69013
d001db00:	b93b9b13 	ldmdblt	fp!, {r0, r1, r4, r8, r9, fp, ip, pc}
d001db04:	f0412d00 			; <UNDEFINED> instruction: 0xf0412d00
d001db08:	4bed80dd 	blmi	0xcfb7de84
d001db0c:	6adb447b 	bvs	0xcf6eed00
d001db10:	d10a2b28 	tstle	sl, r8, lsr #22
d001db14:	d0c12c00 	sbcle	r2, r1, r0, lsl #24
d001db18:	447b4bea 	ldrbtmi	r4, [fp], #-3050	; 0xfffff416
d001db1c:	2a006d9a 	bcs	0xd003918c
d001db20:	ac0ff47f 	cfstrsge	mvf15, [pc], {127}	; 0x7f
d001db24:	447a4ae8 	ldrbtmi	r4, [sl], #-2792	; 0xfffff518
d001db28:	9b0fe60c 	blls	0xd0417360
d001db2c:	f88dae2e 			; <UNDEFINED> instruction: 0xf88dae2e
d001db30:	933190d0 	teqls	r1, #208	; 0xd0
d001db34:	94059b11 	strls	r9, [r5], #-2833	; 0xfffff4ef
d001db38:	9b109332 	blls	0xd0442808
d001db3c:	93359504 	teqls	r5, #4, 10	; 0x1000000
d001db40:	e9cdab32 	stmib	sp, {r1, r4, r5, r8, r9, fp, sp, pc}^
d001db44:	e553ba2e 	ldrb	fp, [r3, #-2606]	; 0xfffff5d2
d001db48:	46594652 			; <UNDEFINED> instruction: 0x46594652
d001db4c:	f7f24620 			; <UNDEFINED> instruction: 0xf7f24620
d001db50:	2800fe4d 	stmdacs	r0, {r0, r2, r3, r6, r9, sl, fp, ip, sp, lr, pc}
d001db54:	adcef6bf 	stclge	6, cr15, [lr, #764]	; 0x2fc
d001db58:	46514adc 			; <UNDEFINED> instruction: 0x46514adc
d001db5c:	447a4658 	ldrbtmi	r4, [sl], #-1624	; 0xfffff9a8
d001db60:	fed6f7f2 	mrc2	7, 6, pc, cr6, cr2, {7}
d001db64:	4adabb40 	bmi	0xcf6cc86c
d001db68:	46584651 			; <UNDEFINED> instruction: 0x46584651
d001db6c:	f7f2447a 			; <UNDEFINED> instruction: 0xf7f2447a
d001db70:	bb18fecf 	bllt	0xd065d6b4
d001db74:	46514ad7 			; <UNDEFINED> instruction: 0x46514ad7
d001db78:	447a4658 	ldrbtmi	r4, [sl], #-1624	; 0xfffff9a8
d001db7c:	fec8f7f2 	mcr2	7, 6, pc, cr8, cr2, {7}	; <UNPREDICTABLE>
d001db80:	bf0c2800 	svclt	0x000c2800
d001db84:	230c2300 	movwcs	r2, #49920	; 0xc300
d001db88:	46514ad3 			; <UNDEFINED> instruction: 0x46514ad3
d001db8c:	93154658 	tstls	r5, #88, 12	; 0x5800000
d001db90:	f7f2447a 			; <UNDEFINED> instruction: 0xf7f2447a
d001db94:	9b15febd 	blls	0xd059d690
d001db98:	43034607 	movwmi	r4, #13831	; 0x3607
d001db9c:	9b14d010 	blls	0xd0551be4
d001dba0:	43139a13 	tstmi	r3, #77824	; 0x13000
d001dba4:	4bcdd00c 	blmi	0xcf391bdc
d001dba8:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d001dbac:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d001dbb0:	4acbabc8 	bmi	0xcf308ad8
d001dbb4:	e5c5447a 	strb	r4, [r5, #1146]	; 0x47a
d001dbb8:	e7e52304 	strb	r2, [r5, r4, lsl #6]!
d001dbbc:	e7e32308 	strb	r2, [r3, r8, lsl #6]!
d001dbc0:	25009b15 	strcs	r9, [r0, #-2837]	; 0xfffff4eb
d001dbc4:	2b04ac22 	blcs	0xd0148c54
d001dbc8:	f88d9522 			; <UNDEFINED> instruction: 0xf88d9522
d001dbcc:	9524508c 	strls	r5, [r4, #-140]!	; 0xffffff74
d001dbd0:	5094f88d 	addspl	pc, r4, sp, lsl #17
d001dbd4:	4dc3d149 	stfmip	f5, [r3, #292]	; 0x124
d001dbd8:	7185f44f 	orrvc	pc, r5, pc, asr #8
d001dbdc:	447d4ac2 	ldrbtmi	r4, [sp], #-2754	; 0xfffff53e
d001dbe0:	4628447a 			; <UNDEFINED> instruction: 0x4628447a
d001dbe4:	f7f59212 			; <UNDEFINED> instruction: 0xf7f59212
d001dbe8:	2800f98b 	stmdacs	r0, {r0, r1, r3, r7, r8, fp, ip, sp, lr, pc}
d001dbec:	aba9f43f 	blge	0xcea9acf0
d001dbf0:	f2409a12 	vpmin.s8	d25, d0, d2
d001dbf4:	4628110b 	strtmi	r1, [r8], -fp, lsl #2
d001dbf8:	f982f7f5 			; <UNDEFINED> instruction: 0xf982f7f5
d001dbfc:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001dc00:	9a12aba0 	bls	0xd04c8a88
d001dc04:	4628212a 	strtmi	r2, [r8], -sl, lsr #2
d001dc08:	f97af7f5 			; <UNDEFINED> instruction: 0xf97af7f5
d001dc0c:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001dc10:	f240ab98 	vpadd.i8	d26, d16, d8
d001dc14:	46281101 	strtmi	r1, [r8], -r1, lsl #2
d001dc18:	f964f7f5 			; <UNDEFINED> instruction: 0xf964f7f5
d001dc1c:	70232302 	eorvc	r2, r3, r2, lsl #6
d001dc20:	93122301 	tstls	r2, #67108864	; 0x4000000
d001dc24:	21294cb1 			; <UNDEFINED> instruction: 0x21294cb1
d001dc28:	447c4ab1 	ldrbtmi	r4, [ip], #-2737	; 0xfffff54f
d001dc2c:	4620447a 			; <UNDEFINED> instruction: 0x4620447a
d001dc30:	f966f7f5 			; <UNDEFINED> instruction: 0xf966f7f5
d001dc34:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001dc38:	9b13ab84 	blls	0xd0508a50
d001dc3c:	f0402b04 			; <UNDEFINED> instruction: 0xf0402b04
d001dc40:	9b1281f3 	blls	0xd04be414
d001dc44:	f0402b05 			; <UNDEFINED> instruction: 0xf0402b05
d001dc48:	6da381ef 	stfvsd	f0, [r3, #956]!	; 0x3bc
d001dc4c:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001dc50:	4ba8ab78 	blmi	0xcea48a38
d001dc54:	65a3447b 	strvs	r4, [r3, #1147]!	; 0x47b
d001dc58:	65e39b0f 	strbvs	r9, [r3, #2831]!	; 0xb0f
d001dc5c:	e9c49b11 	stmib	r4, {r0, r4, r8, r9, fp, ip, pc}^
d001dc60:	9b103918 	blls	0xd042c0c8
d001dc64:	f7ff66a3 			; <UNDEFINED> instruction: 0xf7ff66a3
d001dc68:	48a3bb6c 	stmiami	r3!, {r2, r3, r5, r6, r8, r9, fp, ip, sp, pc}
d001dc6c:	6ac34478 	bvs	0xcf0eee54
d001dc70:	7f84f5b3 	svcvc	0x0084f5b3
d001dc74:	6cc3d106 	stfvsp	f5, [r3], {6}
d001dc78:	d1032b29 	tstle	r3, r9, lsr #22
d001dc7c:	f912f7f5 			; <UNDEFINED> instruction: 0xf912f7f5
d001dc80:	e7cf9512 	bfi	r9, r2, #10, #6
d001dc84:	23004d9d 	movwcs	r4, #3485	; 0xd9d
d001dc88:	447dac22 	ldrbtmi	sl, [sp], #-3106	; 0xfffff3de
d001dc8c:	9b129312 	blls	0xd04c28dc
d001dc90:	d14f2b01 	cmple	pc, r1, lsl #22
d001dc94:	d04d2f00 	suble	r2, sp, r0, lsl #30
d001dc98:	3088f89d 	umullcc	pc, r8, sp, r8	; <UNPREDICTABLE>
d001dc9c:	2b00ae22 	blcs	0xd004952c
d001dca0:	f8dfd148 			; <UNDEFINED> instruction: 0xf8dfd148
d001dca4:	f240825c 	vqsub.s8	q12, q0, q6
d001dca8:	44f8110b 	ldrbtmi	r1, [r8], #267	; 0x10b
d001dcac:	f7f54640 			; <UNDEFINED> instruction: 0xf7f54640
d001dcb0:	2800f919 	stmdacs	r0, {r0, r3, r4, r8, fp, ip, sp, lr, pc}
d001dcb4:	4a93d03e 	bmi	0xce511db4
d001dcb8:	4640212a 	strbmi	r2, [r0], -sl, lsr #2
d001dcbc:	9221447a 	eorls	r4, r1, #2046820352	; 0x7a000000
d001dcc0:	f91ef7f5 			; <UNDEFINED> instruction: 0xf91ef7f5
d001dcc4:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001dcc8:	9a21ab3c 	bls	0xd08889c0
d001dccc:	4640212a 	strbmi	r2, [r0], -sl, lsr #2
d001dcd0:	f916f7f5 			; <UNDEFINED> instruction: 0xf916f7f5
d001dcd4:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001dcd8:	2304ab34 	movwcs	sl, #19252	; 0x4b34
d001dcdc:	4e8a7073 	mcrmi	0, 4, r7, cr10, cr3, {3}
d001dce0:	7cecf50d 	cfstr64vc	mvdx15, [ip], #52	; 0x34
d001dce4:	447e9b12 	ldrbtmi	r9, [lr], #-2834	; 0xfffff4ee
d001dce8:	1c43eb0c 	mcrrne	11, 0, lr, r3, cr12
d001dcec:	0e18f106 	mnfeqe	f7, f6
d001dcf0:	000fe8be 			; <UNDEFINED> instruction: 0x000fe8be
d001dcf4:	000fe8ac 	andeq	lr, pc, ip, lsr #17
d001dcf8:	000fe89e 	muleq	pc, lr, r8	; <UNPREDICTABLE>
d001dcfc:	000fe88c 	andeq	lr, pc, ip, lsl #17
d001dd00:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d001dd04:	f7f54630 			; <UNDEFINED> instruction: 0xf7f54630
d001dd08:	9b12f8ed 	blls	0xd04dc0c4
d001dd0c:	93123301 	tstls	r2, #67108864	; 0x4000000
d001dd10:	3b01f814 	blcc	0xd009bd68
d001dd14:	d0852b04 	addle	r2, r5, r4, lsl #22
d001dd18:	4630212c 	ldrtmi	r2, [r0], -ip, lsr #2
d001dd1c:	f8e2f7f5 			; <UNDEFINED> instruction: 0xf8e2f7f5
d001dd20:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001dd24:	9b12af7f 	blls	0xd04c9b28
d001dd28:	d1b02b05 	lslsle	r2, r5, #22
d001dd2c:	46304977 			; <UNDEFINED> instruction: 0x46304977
d001dd30:	e46f4479 	strbt	r4, [pc], #-1145	; 0xd001dd38
d001dd34:	f7f24628 			; <UNDEFINED> instruction: 0xf7f24628
d001dd38:	b1e8fda3 	mvnlt	pc, r3, lsr #27
d001dd3c:	a9362300 	ldmdbge	r6!, {r8, r9, sp}
d001dd40:	600b4628 	andvs	r4, fp, r8, lsr #12
d001dd44:	fad8f7f5 	blx	0xcf65bd20
d001dd48:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001dd4c:	212aaafa 	strdcs	sl, [sl, -sl]!	; <UNPREDICTABLE>
d001dd50:	f7f54628 			; <UNDEFINED> instruction: 0xf7f54628
d001dd54:	b168f8c7 	msrlt	SPSR_f, r7, asr #17
d001dd58:	4628212a 	strtmi	r2, [r8], -sl, lsr #2
d001dd5c:	f8c2f7f5 			; <UNDEFINED> instruction: 0xf8c2f7f5
d001dd60:	bf142800 	svclt	0x00142800
d001dd64:	230e2312 	movwcs	r2, #58130	; 0xe312
d001dd68:	ab247023 	blge	0xd0939dfc
d001dd6c:	99129a36 	ldmdbls	r2, {r1, r2, r4, r5, r9, fp, ip, pc}
d001dd70:	e7b454ca 	ldr	r5, [r4, sl, asr #9]!
d001dd74:	e7f7230d 	ldrb	r2, [r7, sp, lsl #6]!
d001dd78:	f2406aea 	vpmax.s8	q11, q8, q13
d001dd7c:	429a131b 	addsmi	r1, sl, #1811939328	; 0x6c000000
d001dd80:	80c8f000 	sbchi	pc, r8, r0
d001dd84:	f2404e62 	vceq.f32	q10, q0, q9
d001dd88:	447e1107 	ldrbtmi	r1, [lr], #-263	; 0xfffffef9
d001dd8c:	f7f54630 			; <UNDEFINED> instruction: 0xf7f54630
d001dd90:	2800f8a9 	stmdacs	r0, {r0, r3, r5, r7, fp, ip, sp, lr, pc}
d001dd94:	80c4f040 	sbchi	pc, r4, r0, asr #32
d001dd98:	f2406af2 	vpmin.s8	q11, q8, q9
d001dd9c:	429a1301 	addsmi	r1, sl, #67108864	; 0x4000000
d001dda0:	80d0f040 	sbcshi	pc, r0, r0, asr #32
d001dda4:	e9d64630 	ldmib	r6, {r4, r5, r9, sl, lr}^
d001dda8:	f7f21206 			; <UNDEFINED> instruction: 0xf7f21206
d001ddac:	2800fd44 	stmdacs	r0, {r2, r6, r8, sl, fp, ip, sp, lr, pc}
d001ddb0:	80c8f2c0 	sbchi	pc, r8, r0, asr #5
d001ddb4:	e9d64630 	ldmib	r6, {r4, r5, r9, sl, lr}^
d001ddb8:	f7f21206 			; <UNDEFINED> instruction: 0xf7f21206
d001ddbc:	2324fd3c 	msrcs	CPSR_s, #60, 26	; 0xf00
d001ddc0:	6000fb03 	andvs	pc, r0, r3, lsl #22
d001ddc4:	3075f500 	rsbscc	pc, r5, r0, lsl #10
d001ddc8:	33acf890 			; <UNDEFINED> instruction: 0x33acf890
d001ddcc:	f0402bff 			; <UNDEFINED> instruction: 0xf0402bff
d001ddd0:	463080b9 			; <UNDEFINED> instruction: 0x463080b9
d001ddd4:	f866f7f5 			; <UNDEFINED> instruction: 0xf866f7f5
d001ddd8:	bf00e0a2 	svclt	0x0000e0a2
d001dddc:	0000a8ce 	andeq	sl, r0, lr, asr #17
d001dde0:	fffff414 			; <UNDEFINED> instruction: 0xfffff414
d001dde4:	fffff412 			; <UNDEFINED> instruction: 0xfffff412
d001dde8:	fffff416 			; <UNDEFINED> instruction: 0xfffff416
d001ddec:	0000a840 	andeq	sl, r0, r0, asr #16
d001ddf0:	0000a7da 	ldrdeq	sl, [r0], -sl	; <UNPREDICTABLE>
d001ddf4:	fffff3a0 			; <UNDEFINED> instruction: 0xfffff3a0
d001ddf8:	fffff3a7 			; <UNDEFINED> instruction: 0xfffff3a7
d001ddfc:	0000a768 	andeq	sl, r0, r8, ror #14
d001de00:	fffff374 			; <UNDEFINED> instruction: 0xfffff374
d001de04:	0000a74e 	andeq	sl, r0, lr, asr #14
d001de08:	000559ec 	andeq	r5, r5, ip, ror #19
d001de0c:	0000a728 	andeq	sl, r0, r8, lsr #14
d001de10:	fffff2d0 			; <UNDEFINED> instruction: 0xfffff2d0
d001de14:	fffff306 			; <UNDEFINED> instruction: 0xfffff306
d001de18:	fffff302 			; <UNDEFINED> instruction: 0xfffff302
d001de1c:	ffff5e4b 			; <UNDEFINED> instruction: 0xffff5e4b
d001de20:	fffff22a 			; <UNDEFINED> instruction: 0xfffff22a
d001de24:	fffff237 			; <UNDEFINED> instruction: 0xfffff237
d001de28:	0000a578 	andeq	sl, r0, r8, ror r5
d001de2c:	fffff1b5 			; <UNDEFINED> instruction: 0xfffff1b5
d001de30:	fffff1af 			; <UNDEFINED> instruction: 0xfffff1af
d001de34:	fffff194 			; <UNDEFINED> instruction: 0xfffff194
d001de38:	fffff174 			; <UNDEFINED> instruction: 0xfffff174
d001de3c:	0000a3c0 	andeq	sl, r0, r0, asr #7
d001de40:	ffffa666 			; <UNDEFINED> instruction: 0xffffa666
d001de44:	0000a39c 	muleq	r0, ip, r3
d001de48:	ffffe54e 			; <UNDEFINED> instruction: 0xffffe54e
d001de4c:	fffff0df 			; <UNDEFINED> instruction: 0xfffff0df
d001de50:	0000a354 	andeq	sl, r0, r4, asr r3
d001de54:	fffff0e8 			; <UNDEFINED> instruction: 0xfffff0e8
d001de58:	0000a31e 	andeq	sl, r0, lr, lsl r3
d001de5c:	0000a2f8 	strdeq	sl, [r0], -r8
d001de60:	ffffee33 			; <UNDEFINED> instruction: 0xffffee33
d001de64:	0000a2de 	ldrdeq	sl, [r0], -lr
d001de68:	ffffede9 			; <UNDEFINED> instruction: 0xffffede9
d001de6c:	ffffcb7e 			; <UNDEFINED> instruction: 0xffffcb7e
d001de70:	0000a294 	muleq	r0, r4, r2
d001de74:	0000a268 	andeq	sl, r0, r8, ror #4
d001de78:	fffff027 			; <UNDEFINED> instruction: 0xfffff027
d001de7c:	0000a246 	andeq	sl, r0, r6, asr #4
d001de80:	ffffe3f8 			; <UNDEFINED> instruction: 0xffffe3f8
d001de84:	0000a20a 	andeq	sl, r0, sl, lsl #4
d001de88:	0000a1a2 	andeq	sl, r0, r2, lsr #3
d001de8c:	ffffef82 			; <UNDEFINED> instruction: 0xffffef82
d001de90:	0000a170 	andeq	sl, r0, r0, ror r1
d001de94:	0000a0c0 	andeq	sl, r0, r0, asr #1
d001de98:	ffffeec5 			; <UNDEFINED> instruction: 0xffffeec5
d001de9c:	0000a096 	muleq	r0, r6, r0
d001dea0:	0000a084 	andeq	sl, r0, r4, lsl #1
d001dea4:	ffffc9bc 			; <UNDEFINED> instruction: 0xffffc9bc
d001dea8:	ffffc9b7 			; <UNDEFINED> instruction: 0xffffc9b7
d001deac:	ffff5e08 			; <UNDEFINED> instruction: 0xffff5e08
d001deb0:	0000a040 	andeq	sl, r0, r0, asr #32
d001deb4:	ffffee75 			; <UNDEFINED> instruction: 0xffffee75
d001deb8:	ffffedd9 			; <UNDEFINED> instruction: 0xffffedd9
d001debc:	00009fb0 			; <UNDEFINED> instruction: 0x00009fb0
d001dec0:	00009f88 	andeq	r9, r0, r8, lsl #31
d001dec4:	00009f7a 	andeq	r9, r0, sl, ror pc
d001dec8:	ffffee0b 			; <UNDEFINED> instruction: 0xffffee0b
d001decc:	ffffedf5 			; <UNDEFINED> instruction: 0xffffedf5
d001ded0:	ffffedf6 			; <UNDEFINED> instruction: 0xffffedf6
d001ded4:	ffffedf5 			; <UNDEFINED> instruction: 0xffffedf5
d001ded8:	ffffedee 			; <UNDEFINED> instruction: 0xffffedee
d001dedc:	00009eec 	andeq	r9, r0, ip, ror #29
d001dee0:	ffffedcf 			; <UNDEFINED> instruction: 0xffffedcf
d001dee4:	00009eb6 			; <UNDEFINED> instruction: 0x00009eb6
d001dee8:	ffffede3 			; <UNDEFINED> instruction: 0xffffede3
d001deec:	00009e6a 	andeq	r9, r0, sl, ror #28
d001def0:	ffffeee2 			; <UNDEFINED> instruction: 0xffffeee2
d001def4:	ffffeedc 			; <UNDEFINED> instruction: 0xffffeedc
d001def8:	00009e28 	andeq	r9, r0, r8, lsr #28
d001defc:	00009e0a 	andeq	r9, r0, sl, lsl #28
d001df00:	00009dea 	andeq	r9, r0, sl, ror #27
d001df04:	ffffed5c 			; <UNDEFINED> instruction: 0xffffed5c
d001df08:	00009dae 	andeq	r9, r0, lr, lsr #27
d001df0c:	ffffecbe 			; <UNDEFINED> instruction: 0xffffecbe
d001df10:	00009d0a 	andeq	r9, r0, sl, lsl #26
d001df14:	f7f54628 			; <UNDEFINED> instruction: 0xf7f54628
d001df18:	2800fae5 	stmdacs	r0, {r0, r2, r5, r6, r7, r9, fp, ip, sp, lr, pc}
d001df1c:	af32f43f 	svcge	0x0032f43f
d001df20:	6c98f8df 	ldcvs	8, cr15, [r8], {223}	; 0xdf
d001df24:	447e212a 	ldrbtmi	r2, [lr], #-298	; 0xfffffed6
d001df28:	f7f44630 			; <UNDEFINED> instruction: 0xf7f44630
d001df2c:	b138ffdb 	teqlt	r8, fp	; <illegal shifter operand>	; <UNPREDICTABLE>
d001df30:	4630212a 	ldrtmi	r2, [r0], -sl, lsr #2
d001df34:	ffd6f7f4 			; <UNDEFINED> instruction: 0xffd6f7f4
d001df38:	bf142800 	svclt	0x00142800
d001df3c:	200a2013 	andcs	r2, sl, r3, lsl r0
d001df40:	e6cc7020 	strb	r7, [ip], r0, lsr #32
d001df44:	0c78f8df 	ldcleq	8, cr15, [r8], #-892	; 0xfffffc84
d001df48:	f7f64478 			; <UNDEFINED> instruction: 0xf7f64478
d001df4c:	b110fcd5 			; <UNDEFINED> instruction: 0xb110fcd5
d001df50:	70232303 	eorvc	r2, r3, r3, lsl #6
d001df54:	f8dfe6c3 			; <UNDEFINED> instruction: 0xf8dfe6c3
d001df58:	44780c6c 	ldrbtmi	r0, [r8], #-3180	; 0xfffff394
d001df5c:	fcccf7f6 	stc2l	7, cr15, [ip], {246}	; 0xf6
d001df60:	2301b108 	movwcs	fp, #4360	; 0x1108
d001df64:	f8dfe7f5 			; <UNDEFINED> instruction: 0xf8dfe7f5
d001df68:	44780c60 	ldrbtmi	r0, [r8], #-3168	; 0xfffff3a0
d001df6c:	fcc4f7f6 	stc2l	7, cr15, [r4], {246}	; 0xf6
d001df70:	2305b108 	movwcs	fp, #20744	; 0x5108
d001df74:	f8dfe7ed 			; <UNDEFINED> instruction: 0xf8dfe7ed
d001df78:	44780c54 	ldrbtmi	r0, [r8], #-3156	; 0xfffff3ac
d001df7c:	fcbcf7f6 	ldc2	7, cr15, [ip], #984	; 0x3d8
d001df80:	d1f62800 	mvnsle	r2, r0, lsl #16
d001df84:	681b9b1c 	ldmdavs	fp, {r2, r3, r4, r8, r9, fp, ip, pc}
d001df88:	d0452b00 	suble	r2, r5, r0, lsl #22
d001df8c:	7185f44f 	orrvc	pc, r5, pc, asr #8
d001df90:	0a10ee18 	beq	0xd04597f8
d001df94:	ffa6f7f4 			; <UNDEFINED> instruction: 0xffa6f7f4
d001df98:	f8dfb338 			; <UNDEFINED> instruction: 0xf8dfb338
d001df9c:	44780c34 	ldrbtmi	r0, [r8], #-3124	; 0xfffff3cc
d001dfa0:	fcaaf7f6 	stc2	7, cr15, [sl], #984	; 0x3d8
d001dfa4:	f8dfb938 			; <UNDEFINED> instruction: 0xf8dfb938
d001dfa8:	f8df1c2c 			; <UNDEFINED> instruction: 0xf8df1c2c
d001dfac:	44790c2c 	ldrbtmi	r0, [r9], #-3116	; 0xfffff3d4
d001dfb0:	f7ff4478 			; <UNDEFINED> instruction: 0xf7ff4478
d001dfb4:	f8dfbb2f 			; <UNDEFINED> instruction: 0xf8dfbb2f
d001dfb8:	212a2c24 			; <UNDEFINED> instruction: 0x212a2c24
d001dfbc:	0a10ee18 	beq	0xd0459824
d001dfc0:	f7f4447a 			; <UNDEFINED> instruction: 0xf7f4447a
d001dfc4:	2800ff9d 	stmdacs	r0, {r0, r2, r3, r4, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d001dfc8:	ee18d0ed 	cdp	0, 1, cr13, cr8, cr13, {7}
d001dfcc:	f5033a10 			; <UNDEFINED> instruction: 0xf5033a10
d001dfd0:	f8b3338f 			; <UNDEFINED> instruction: 0xf8b3338f
d001dfd4:	b93331b4 	ldmdblt	r3!, {r2, r4, r5, r7, r8, ip, sp}
d001dfd8:	1c04f8df 	stcne	8, cr15, [r4], {223}	; 0xdf
d001dfdc:	0a10ee18 	beq	0xd0459844
d001dfe0:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d001dfe4:	2306bb17 	movwcs	fp, #27415	; 0x6b17
d001dfe8:	9b1ce7b3 	blls	0xd0757ebc
d001dfec:	b19b681b 	orrslt	r6, fp, fp, lsl r8
d001dff0:	7184f44f 	orrvc	pc, r4, pc, asr #8
d001dff4:	0a10ee18 	beq	0xd045985c
d001dff8:	ff74f7f4 			; <UNDEFINED> instruction: 0xff74f7f4
d001dffc:	f8dfb160 			; <UNDEFINED> instruction: 0xf8dfb160
d001e000:	212a2be4 			; <UNDEFINED> instruction: 0x212a2be4
d001e004:	0a10ee18 	beq	0xd045986c
d001e008:	f7f4447a 			; <UNDEFINED> instruction: 0xf7f4447a
d001e00c:	2800ff79 	stmdacs	r0, {r0, r3, r4, r5, r6, r8, r9, sl, fp, ip, sp, lr, pc}
d001e010:	a997f43f 	ldmibge	r7, {r0, r1, r2, r3, r4, r5, sl, ip, sp, lr, pc}
d001e014:	e79c2302 	ldr	r2, [ip, r2, lsl #6]
d001e018:	1bccf8df 	blne	0xcf35c39c
d001e01c:	0bccf8df 	bleq	0xcf35c3a0
d001e020:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d001e024:	baf6f7ff 	blt	0xcfddc028
d001e028:	071b9b15 			; <UNDEFINED> instruction: 0x071b9b15
d001e02c:	9b12d502 	blls	0xd04d343c
d001e030:	d14b2b00 	cmple	fp, r0, lsl #22
d001e034:	7bb8f8df 	blvc	0xcee5c3b8
d001e038:	447f2400 	ldrbtmi	r2, [pc], #-1024	; 0xd001e040
d001e03c:	357ff507 	ldrbcc	pc, [pc, #-1287]!	; 0xd001db3d	; <UNPREDICTABLE>
d001e040:	2886f507 	stmcs	r6, {r0, r1, r2, r8, sl, ip, sp, lr, pc}
d001e044:	750af505 	strvc	pc, [sl, #-1285]	; 0xfffffafb
d001e048:	3628f8d8 			; <UNDEFINED> instruction: 0x3628f8d8
d001e04c:	d21a429c 	andsle	r4, sl, #156, 4	; 0xc0000009
d001e050:	465a2338 			; <UNDEFINED> instruction: 0x465a2338
d001e054:	f604fb03 			; <UNDEFINED> instruction: 0xf604fb03
d001e058:	e9d54653 	ldmib	r5, {r0, r1, r4, r6, r9, sl, lr}^
d001e05c:	f7f20100 			; <UNDEFINED> instruction: 0xf7f20100
d001e060:	2800fb2f 	stmdacs	r0, {r0, r1, r2, r3, r5, r8, r9, fp, ip, sp, lr, pc}
d001e064:	f895d03e 			; <UNDEFINED> instruction: 0xf895d03e
d001e068:	f89d2028 			; <UNDEFINED> instruction: 0xf89d2028
d001e06c:	429a3050 	addsmi	r3, sl, #80	; 0x50
d001e070:	9b14d138 	blls	0xd0552558
d001e074:	f895b123 			; <UNDEFINED> instruction: 0xf895b123
d001e078:	7a3b2029 	bvc	0xd0ee6124
d001e07c:	d131429a 	teqle	r1, sl	; <illegal shifter operand>
d001e080:	f2802c00 	vmull.s8	q1, d0, d0
d001e084:	f8df862c 			; <UNDEFINED> instruction: 0xf8df862c
d001e088:	46524b6c 	ldrbmi	r4, [r2], -ip, ror #22
d001e08c:	447c4659 	ldrbtmi	r4, [ip], #-1625	; 0xfffff9a7
d001e090:	f7f24620 			; <UNDEFINED> instruction: 0xf7f24620
d001e094:	2800fc14 	stmdacs	r0, {r2, r4, sl, fp, ip, sp, lr, pc}
d001e098:	863df2c0 	ldrthi	pc, [sp], -r0, asr #5	; <UNPREDICTABLE>
d001e09c:	46594652 			; <UNDEFINED> instruction: 0x46594652
d001e0a0:	f7f24620 			; <UNDEFINED> instruction: 0xf7f24620
d001e0a4:	2338fc0c 	teqcs	r8, #12, 24	; 0xc00	; <UNPREDICTABLE>
d001e0a8:	4000fb03 	andmi	pc, r0, r3, lsl #22
d001e0ac:	f5007a23 			; <UNDEFINED> instruction: 0xf5007a23
d001e0b0:	f890307f 			; <UNDEFINED> instruction: 0xf890307f
d001e0b4:	429a2251 	addsmi	r2, sl, #268435461	; 0x10000005
d001e0b8:	862df040 	strthi	pc, [sp], -r0, asr #32
d001e0bc:	2b006da3 	blcs	0xd0039750
d001e0c0:	a93ff47f 	ldmdbge	pc!, {r0, r1, r2, r3, r4, r5, r6, sl, ip, sp, lr, pc}	; <UNPREDICTABLE>
d001e0c4:	3b30f8df 	blcc	0xd0c5c448
d001e0c8:	e5c4447b 	strb	r4, [r4, #1147]	; 0x47b
d001e0cc:	3b30f8df 	blcc	0xd0c5c450
d001e0d0:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d001e0d4:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d001e0d8:	f8dfa934 			; <UNDEFINED> instruction: 0xf8dfa934
d001e0dc:	447a2b28 	ldrbtmi	r2, [sl], #-2856	; 0xfffff4d8
d001e0e0:	bb30f7ff 	bllt	0xd0c5c0e4
d001e0e4:	35383401 	ldrcc	r3, [r8, #-1025]!	; 0xfffffbff
d001e0e8:	1c62e7ae 	stclne	7, cr14, [r2], #-696	; 0xfffffd48
d001e0ec:	f8952100 			; <UNDEFINED> instruction: 0xf8952100
d001e0f0:	f8c38008 			; <UNDEFINED> instruction: 0xf8c38008
d001e0f4:	22382628 	eorscs	r2, r8, #40, 12	; 0x2800000
d001e0f8:	f704fb02 			; <UNDEFINED> instruction: 0xf704fb02
d001e0fc:	f50719ee 			; <UNDEFINED> instruction: 0xf50719ee
d001e100:	f506377f 			; <UNDEFINED> instruction: 0xf506377f
d001e104:	f506367f 			; <UNDEFINED> instruction: 0xf506367f
d001e108:	4618730a 	ldrmi	r7, [r8], -sl, lsl #6
d001e10c:	fef6f002 	cdp2	0, 15, cr15, cr6, cr2, {0}
d001e110:	f10d9a0f 			; <UNDEFINED> instruction: 0xf10d9a0f
d001e114:	f88d0cb8 			; <UNDEFINED> instruction: 0xf88d0cb8
d001e118:	923190d0 	eorsls	r9, r1, #208	; 0xd0
d001e11c:	9a114686 	bls	0xd046fb3c
d001e120:	9a109232 	bls	0xd04429f0
d001e124:	ba2ee9cd 	blt	0xd0bd8860
d001e128:	e8bc9235 	ldm	ip!, {r0, r2, r4, r5, r9, ip, pc}
d001e12c:	e8ae000f 	stmia	lr!, {r0, r1, r2, r3}
d001e130:	e89c000f 	ldm	ip, {r0, r1, r2, r3}
d001e134:	e88e000f 	stm	lr, {r0, r1, r2, r3}
d001e138:	9b15000f 	blls	0xd055e17c
d001e13c:	2053f207 	subscs	pc, r3, r7, lsl #4
d001e140:	7716f507 	ldrvc	pc, [r6, -r7, lsl #10]
d001e144:	f8c6a922 			; <UNDEFINED> instruction: 0xf8c6a922
d001e148:	44283248 	strtmi	r3, [r8], #-584	; 0xfffffdb8
d001e14c:	f8869b12 			; <UNDEFINED> instruction: 0xf8869b12
d001e150:	9b15324c 	blls	0xd056aa88
d001e154:	324df886 	subcc	pc, sp, #8781824	; 0x860000
d001e158:	bf183b00 	svclt	0x00183b00
d001e15c:	f8862301 			; <UNDEFINED> instruction: 0xf8862301
d001e160:	9b13324e 	blls	0xd04eaaa0
d001e164:	f8869a12 			; <UNDEFINED> instruction: 0xf8869a12
d001e168:	9b14324f 	blls	0xd052aaac
d001e16c:	8251f886 	subshi	pc, r1, #8781824	; 0x860000
d001e170:	3250f886 	subscc	pc, r0, #8781824	; 0x860000
d001e174:	f8869b1b 			; <UNDEFINED> instruction: 0xf8869b1b
d001e178:	f0023252 			; <UNDEFINED> instruction: 0xf0023252
d001e17c:	9a12fecd 	bls	0xd04ddcb8
d001e180:	19e8a924 	stmibne	r8!, {r2, r5, r8, fp, sp, pc}^
d001e184:	fec8f002 	cdp2	0, 12, cr15, cr8, cr2, {0}
d001e188:	5a7cf8df 	bpl	0xd1f5c50c
d001e18c:	447d213b 	ldrbtmi	r2, [sp], #-315	; 0xfffffec5
d001e190:	f7f44628 			; <UNDEFINED> instruction: 0xf7f44628
d001e194:	2800fea7 	stmdacs	r0, {r0, r1, r2, r5, r7, r9, sl, fp, ip, sp, lr, pc}
d001e198:	a8d3f47f 	ldmge	r3, {r0, r1, r2, r3, r4, r5, r6, sl, ip, sp, lr, pc}^
d001e19c:	fb032338 	blx	0xd00e6e86
d001e1a0:	f5045404 			; <UNDEFINED> instruction: 0xf5045404
d001e1a4:	f894347f 			; <UNDEFINED> instruction: 0xf894347f
d001e1a8:	b32e624e 			; <UNDEFINED> instruction: 0xb32e624e
d001e1ac:	2b006dab 	blcs	0xd0039860
d001e1b0:	a8c7f47f 	stmiage	r7, {r0, r1, r2, r3, r4, r5, r6, sl, ip, sp, lr, pc}^
d001e1b4:	3a54f8df 	bcc	0xd155c538
d001e1b8:	f7ff447b 			; <UNDEFINED> instruction: 0xf7ff447b
d001e1bc:	f893baae 			; <UNDEFINED> instruction: 0xf893baae
d001e1c0:	9a1b3252 	bls	0xd06eab10
d001e1c4:	f0404293 			; <UNDEFINED> instruction: 0xf0404293
d001e1c8:	f506859c 			; <UNDEFINED> instruction: 0xf506859c
d001e1cc:	9a12367f 	bls	0xd04abbd0
d001e1d0:	f206a922 	vmla.i8	d10, d6, d18
d001e1d4:	44282053 	strtmi	r2, [r8], #-83	; 0xffffffad
d001e1d8:	feaef002 	cdp2	0, 10, cr15, cr14, cr2, {0}
d001e1dc:	f0402800 			; <UNDEFINED> instruction: 0xf0402800
d001e1e0:	f5068590 			; <UNDEFINED> instruction: 0xf5068590
d001e1e4:	9a127616 	bls	0xd04bba44
d001e1e8:	19a8a924 	stmibne	r8!, {r2, r5, r8, fp, sp, pc}
d001e1ec:	fea4f002 	cdp2	0, 10, cr15, cr4, cr2, {0}
d001e1f0:	d0c92800 	sbcle	r2, r9, r0, lsl #16
d001e1f4:	bd85f000 	stclt	0, cr15, [r5]
d001e1f8:	2a14f8df 	bcs	0xd055c57c
d001e1fc:	4628217b 			; <UNDEFINED> instruction: 0x4628217b
d001e200:	f7f4447a 			; <UNDEFINED> instruction: 0xf7f4447a
d001e204:	2800fe7d 	stmdacs	r0, {r0, r2, r3, r4, r5, r6, r9, sl, fp, ip, sp, lr, pc}
d001e208:	a89bf43f 	ldmge	fp, {r0, r1, r2, r3, r4, r5, sl, ip, sp, lr, pc}
d001e20c:	398ff505 	stmibcc	pc, {r0, r2, r8, sl, ip, sp, lr, pc}	; <UNPREDICTABLE>
d001e210:	2790f505 	ldrcs	pc, [r0, r5, lsl #10]
d001e214:	0801f04f 	stmdaeq	r1, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d001e218:	5180f24b 	orrpl	pc, r0, fp, asr #4
d001e21c:	31b8f8d9 			; <UNDEFINED> instruction: 0x31b8f8d9
d001e220:	f8844628 			; <UNDEFINED> instruction: 0xf8844628
d001e224:	f8c4824e 			; <UNDEFINED> instruction: 0xf8c4824e
d001e228:	f5053248 			; <UNDEFINED> instruction: 0xf5053248
d001e22c:	f8c72392 			; <UNDEFINED> instruction: 0xf8c72392
d001e230:	f8c36630 			; <UNDEFINED> instruction: 0xf8c36630
d001e234:	f8c36240 			; <UNDEFINED> instruction: 0xf8c36240
d001e238:	f8c36250 			; <UNDEFINED> instruction: 0xf8c36250
d001e23c:	f887624c 			; <UNDEFINED> instruction: 0xf887624c
d001e240:	e9c36636 	stmib	r3, {r1, r2, r4, r5, r9, sl, sp, lr}^
d001e244:	f505668e 			; <UNDEFINED> instruction: 0xf505668e
d001e248:	f8c32396 			; <UNDEFINED> instruction: 0xf8c32396
d001e24c:	f505629c 			; <UNDEFINED> instruction: 0xf505629c
d001e250:	f8c32394 			; <UNDEFINED> instruction: 0xf8c32394
d001e254:	f8c36298 			; <UNDEFINED> instruction: 0xf8c36298
d001e258:	f8946254 			; <UNDEFINED> instruction: 0xf8946254
d001e25c:	f887324f 			; <UNDEFINED> instruction: 0xf887324f
d001e260:	f8943634 			; <UNDEFINED> instruction: 0xf8943634
d001e264:	f8873252 			; <UNDEFINED> instruction: 0xf8873252
d001e268:	f7f63635 			; <UNDEFINED> instruction: 0xf7f63635
d001e26c:	f8d9fc21 			; <UNDEFINED> instruction: 0xf8d9fc21
d001e270:	463131b8 			; <UNDEFINED> instruction: 0x463131b8
d001e274:	ee084628 	cfmadd32	mvax1, mvfx4, mvfx8, mvfx8
d001e278:	f7f63a90 			; <UNDEFINED> instruction: 0xf7f63a90
d001e27c:	f44ffc19 			; <UNDEFINED> instruction: 0xf44ffc19
d001e280:	4628412f 	strtmi	r4, [r8], -pc, lsr #2
d001e284:	fc14f7f6 	ldc2	7, cr15, [r4], {246}	; 0xf6
d001e288:	2b049b13 	blcs	0xd0144edc
d001e28c:	808ef040 	addhi	pc, lr, r0, asr #32
d001e290:	46312218 			; <UNDEFINED> instruction: 0x46312218
d001e294:	ac36a838 	ldcge	8, cr10, [r6], #-224	; 0xffffff20
d001e298:	fe30f002 	cdp2	0, 3, cr15, cr0, cr2, {0}
d001e29c:	3974f8df 	ldmdbcc	r4!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d001e2a0:	9336447b 	teqls	r6, #2063597568	; 0x7b000000
d001e2a4:	93372314 	teqls	r7, #20, 6	; 0x50000000
d001e2a8:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d001e2ac:	230b933b 	movwcs	r9, #45883	; 0xb33b
d001e2b0:	ab3a9304 	blge	0xd0ec2ec8
d001e2b4:	e88dcb0f 	stm	sp, {r0, r1, r2, r3, r8, r9, fp, lr, pc}
d001e2b8:	e894000f 	ldm	r4, {r0, r1, r2, r3}
d001e2bc:	f7f5000f 			; <UNDEFINED> instruction: 0xf7f5000f
d001e2c0:	4632fe9f 			; <UNDEFINED> instruction: 0x4632fe9f
d001e2c4:	f887b2c1 			; <UNDEFINED> instruction: 0xf887b2c1
d001e2c8:	46280636 			; <UNDEFINED> instruction: 0x46280636
d001e2cc:	fc29f7f6 	stc2	7, cr15, [r9], #-984	; 0xfffffc28
d001e2d0:	8044f8cd 	subhi	pc, r4, sp, asr #17
d001e2d4:	21002214 	tstcs	r0, r4, lsl r2
d001e2d8:	2400a836 	strcs	sl, [r0], #-2102	; 0xfffff7ca
d001e2dc:	fe0ef002 	cdp2	0, 0, cr15, cr14, cr2, {0}
d001e2e0:	f10dab22 			; <UNDEFINED> instruction: 0xf10dab22
d001e2e4:	f50d0b90 			; <UNDEFINED> instruction: 0xf50d0b90
d001e2e8:	461e7aec 	ldrmi	r7, [lr], -ip, ror #21
d001e2ec:	f8df9310 			; <UNDEFINED> instruction: 0xf8df9310
d001e2f0:	940f3928 	strls	r3, [pc], #-2344	; 0xd001e2f8
d001e2f4:	9315447b 	tstls	r5, #2063597568	; 0x7b000000
d001e2f8:	3920f8df 	stmdbcc	r0!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d001e2fc:	f503447b 			; <UNDEFINED> instruction: 0xf503447b
d001e300:	931b2392 	tstls	fp, #1207959554	; 0x48000002
d001e304:	42a39b12 	adcmi	r9, r3, #18432	; 0x4800
d001e308:	f8dfd152 			; <UNDEFINED> instruction: 0xf8dfd152
d001e30c:	24006914 	strcs	r6, [r0], #-2324	; 0xfffff6ec
d001e310:	5910f8df 	ldmdbpl	r0, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d001e314:	447d447e 	ldrbtmi	r4, [sp], #-1150	; 0xfffffb82
d001e318:	42a39b12 	adcmi	r9, r3, #18432	; 0x4800
d001e31c:	8112f040 	tsthi	r2, r0, asr #32	; <UNPREDICTABLE>
d001e320:	fd06f7fc 	stc2	7, cr15, [r6, #-1008]	; 0xfffffc10
d001e324:	0900f8df 	stmdbeq	r0, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d001e328:	f5004478 			; <UNDEFINED> instruction: 0xf5004478
d001e32c:	f8932390 			; <UNDEFINED> instruction: 0xf8932390
d001e330:	2b013634 	blcs	0xd006bc08
d001e334:	2100d002 	tstcs	r0, r2
d001e338:	ffb7f7f6 			; <UNDEFINED> instruction: 0xffb7f7f6
d001e33c:	58ecf8df 	stmiapl	ip!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d001e340:	f505447d 			; <UNDEFINED> instruction: 0xf505447d
d001e344:	4628338f 	strtmi	r3, [r8], -pc, lsl #7
d001e348:	61b8f8d3 			; <UNDEFINED> instruction: 0x61b8f8d3
d001e34c:	2392f505 	orrscs	pc, r2, #20971520	; 0x1400000
d001e350:	423cf8d3 	eorsmi	pc, ip, #13828096	; 0xd30000
d001e354:	f0243401 			; <UNDEFINED> instruction: 0xf0243401
d001e358:	b2a70401 	adclt	r0, r7, #16777216	; 0x1000000
d001e35c:	4130f447 	teqmi	r0, r7, asr #8	; <UNPREDICTABLE>
d001e360:	fba6f7f6 	blx	0xce9dc342
d001e364:	5180f64b 	orrpl	pc, r0, fp, asr #12
d001e368:	f7f64628 			; <UNDEFINED> instruction: 0xf7f64628
d001e36c:	6dabfba1 			; <UNDEFINED> instruction: 0x6dabfba1
d001e370:	f47e2b00 			; <UNDEFINED> instruction: 0xf47e2b00
d001e374:	f447afe6 			; <UNDEFINED> instruction: 0xf447afe6
d001e378:	ee184130 	mrc	1, 0, r4, cr8, cr0, {1}
d001e37c:	f0410a90 			; <UNDEFINED> instruction: 0xf0410a90
d001e380:	f7f60180 			; <UNDEFINED> instruction: 0xf7f60180
d001e384:	9b0ffb79 	blls	0xd041d170
d001e388:	1ca1b12b 	stfned	f3, [r1], #172	; 0xac
d001e38c:	00894618 	addeq	r4, r9, r8, lsl r6
d001e390:	f7f6b289 			; <UNDEFINED> instruction: 0xf7f6b289
d001e394:	f8dffb71 			; <UNDEFINED> instruction: 0xf8dffb71
d001e398:	27004898 			; <UNDEFINED> instruction: 0x27004898
d001e39c:	f504447c 			; <UNDEFINED> instruction: 0xf504447c
d001e3a0:	f504258e 			; <UNDEFINED> instruction: 0xf504258e
d001e3a4:	f5052890 			; <UNDEFINED> instruction: 0xf5052890
d001e3a8:	e10465c6 	smlabt	r4, r6, r5, r6
d001e3ac:	e7919611 			; <UNDEFINED> instruction: 0xe7919611
d001e3b0:	2014f8da 			; <UNDEFINED> instruction: 0x2014f8da
d001e3b4:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d001e3b8:	d016429a 	mulsle	r6, sl, r2
d001e3bc:	3874f8df 	ldmdacc	r4!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d001e3c0:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d001e3c4:	f47e2a00 			; <UNDEFINED> instruction: 0xf47e2a00
d001e3c8:	aa76afbc 	bge	0xd1dca2c0
d001e3cc:	1444eb02 	strbne	lr, [r4], #-2818	; 0xfffff4fe
d001e3d0:	692068e5 	stmdbvs	r0!, {r0, r2, r5, r6, r7, fp, sp, lr}
d001e3d4:	7e2169e2 	vnmulvc.f16	s12, s3, s5	; <UNPREDICTABLE>
d001e3d8:	485cf8df 	ldmdami	ip, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d001e3dc:	e9c3447c 	stmib	r3, {r2, r3, r4, r5, r6, sl, lr}^
d001e3e0:	e9c34516 	stmib	r3, {r1, r2, r4, r8, sl, lr}^
d001e3e4:	f7ff0118 			; <UNDEFINED> instruction: 0xf7ff0118
d001e3e8:	7832b9f4 	ldmdavc	r2!, {r2, r4, r5, r6, r7, r8, fp, ip, sp, pc}
d001e3ec:	2a0d9614 	bcs	0xd0383c44
d001e3f0:	f89bd11f 			; <UNDEFINED> instruction: 0xf89bd11f
d001e3f4:	f44f3000 	vst4.8	{d19-d22}, [pc], r0
d001e3f8:	9815711a 	ldmdals	r5, {r1, r3, r4, r8, ip, sp, lr}
d001e3fc:	0303fb01 	movweq	pc, #15105	; 0x3b01	; <UNPREDICTABLE>
d001e400:	3368f503 	msrcc	SPSR_f, #12582912	; 0xc00000
d001e404:	9028f8b3 	strhtls	pc, [r8], -r3	; <UNPREDICTABLE>
d001e408:	0f00f1b9 	svceq	0x0000f1b9
d001e40c:	f8dfd113 			; <UNDEFINED> instruction: 0xf8dfd113
d001e410:	447b382c 	ldrbtmi	r3, [fp], #-2092	; 0xfffff7d4
d001e414:	2a006d9a 	bcs	0xd0039a84
d001e418:	af93f47e 	svcge	0x0093f47e
d001e41c:	eb02aa76 	bl	0xd00c8dfc
d001e420:	68e51444 	stmiavs	r5!, {r2, r6, sl, ip}^
d001e424:	69e26920 	stmibvs	r2!, {r5, r8, fp, sp, lr}^
d001e428:	f8df7e21 			; <UNDEFINED> instruction: 0xf8df7e21
d001e42c:	447c4814 	ldrbtmi	r4, [ip], #-2068	; 0xfffff7ec
d001e430:	f04fe7d5 			; <UNDEFINED> instruction: 0xf04fe7d5
d001e434:	9b1b0901 	blls	0xd06e0840
d001e438:	3238f8d3 	eorscc	pc, r8, #13828096	; 0xd30000
d001e43c:	0340f1c3 	movteq	pc, #451	; 0x1c3	; <UNPREDICTABLE>
d001e440:	d3e4454b 	mvnle	r4, #314572800	; 0x12c00000
d001e444:	9204ad76 	andls	sl, r4, #7552	; 0x1d80
d001e448:	1544eb05 	strbne	lr, [r4, #-2821]	; 0xfffff4fb
d001e44c:	0310f105 	tsteq	r0, #1073741825	; 0x40000001	; <UNPREDICTABLE>
d001e450:	e88dcb0f 	stm	sp, {r0, r1, r2, r3, r8, r9, fp, lr, pc}
d001e454:	e895000f 	ldm	r5, {r0, r1, r2, r3}
d001e458:	f7f5000f 			; <UNDEFINED> instruction: 0xf7f5000f
d001e45c:	ab36fdd1 	blge	0xd0dddba8
d001e460:	f8434607 			; <UNDEFINED> instruction: 0xf8434607
d001e464:	78330024 	ldmdavc	r3!, {r2, r5}
d001e468:	020df1a3 	andeq	pc, sp, #-1073741784	; 0xc0000028
d001e46c:	d9012a01 	stmdble	r1, {r0, r9, fp, sp}
d001e470:	d10b2b12 	tstle	fp, r2, lsl fp
d001e474:	37ccf8df 			; <UNDEFINED> instruction: 0x37ccf8df
d001e478:	447b2230 	ldrbtmi	r2, [fp], #-560	; 0xfffffdd0
d001e47c:	3307fb02 	movwcc	pc, #31490	; 0x7b02	; <UNPREDICTABLE>
d001e480:	2000f89b 	mulcs	r0, fp, r8
d001e484:	2390f503 	orrscs	pc, r0, #12582912	; 0xc00000
d001e488:	265af883 	ldrbcs	pc, [sl], -r3, lsl #17	; <UNPREDICTABLE>
d001e48c:	27b8f8df 	sbfxcs	pc, pc, #17, #25
d001e490:	447a2301 	ldrbtmi	r2, [sl], #-769	; 0xfffffcff
d001e494:	2892f502 	ldmcs	r2, {r1, r8, sl, ip, sp, lr, pc}
d001e498:	e0139213 	ands	r9, r3, r3, lsl r2
d001e49c:	93211c6a 			; <UNDEFINED> instruction: 0x93211c6a
d001e4a0:	21009b13 	tstcs	r0, r3, lsl fp
d001e4a4:	2238f8c8 	eorscs	pc, r8, #200, 16	; 0xc80000
d001e4a8:	fb022230 	blx	0xd00a6d72
d001e4ac:	f5053505 			; <UNDEFINED> instruction: 0xf5053505
d001e4b0:	f5052590 			; <UNDEFINED> instruction: 0xf5052590
d001e4b4:	f00260c7 			; <UNDEFINED> instruction: 0xf00260c7
d001e4b8:	9b21fd21 	blls	0xd089d944
d001e4bc:	3301220b 	movwcc	r2, #4619	; 0x120b
d001e4c0:	2659f885 	ldrbcs	pc, [r9], -r5, lsl #17	; <UNPREDICTABLE>
d001e4c4:	f8d84599 			; <UNDEFINED> instruction: 0xf8d84599
d001e4c8:	d1e75238 	mvnle	r5, r8, lsr r2
d001e4cc:	323cf8d8 	eorscc	pc, ip, #216, 16	; 0xd80000
d001e4d0:	9b11429d 	blls	0xd046ef4c
d001e4d4:	f8c8bf88 			; <UNDEFINED> instruction: 0xf8c8bf88
d001e4d8:	2c04523c 	sfmcs	f5, 4, [r4], {60}	; 0x3c
d001e4dc:	0503eb04 	streq	lr, [r3, #-2820]	; 0xfffff4fc
d001e4e0:	f8dfd111 			; <UNDEFINED> instruction: 0xf8dfd111
d001e4e4:	f64f0768 			; <UNDEFINED> instruction: 0xf64f0768
d001e4e8:	250001d7 	strcs	r0, [r0, #-471]	; 0xfffffe29
d001e4ec:	900f4478 	andls	r4, pc, r8, ror r4	; <UNPREDICTABLE>
d001e4f0:	fadef7f6 	blx	0xcf7dc4d0
d001e4f4:	2100980f 	tstcs	r0, pc, lsl #16
d001e4f8:	338ff500 	orrcc	pc, pc, #0, 10
d001e4fc:	31b8f8d3 			; <UNDEFINED> instruction: 0x31b8f8d3
d001e500:	f7f6930f 			; <UNDEFINED> instruction: 0xf7f6930f
d001e504:	9b14fad5 	blls	0xd055d060
d001e508:	781b3601 	ldmdavc	fp, {r0, r9, sl, ip, sp}
d001e50c:	d10c2b05 	tstle	ip, r5, lsl #22
d001e510:	f8dfb2a9 			; <UNDEFINED> instruction: 0xf8dfb2a9
d001e514:	ea41073c 	b	0xd106020c
d001e518:	447801c1 	ldrbtmi	r0, [r8], #-449	; 0xfffffe3f
d001e51c:	4132f441 	teqmi	r2, r1, asr #8	; <UNPREDICTABLE>
d001e520:	01c0f041 	biceq	pc, r0, r1, asr #32
d001e524:	f7f6b289 			; <UNDEFINED> instruction: 0xf7f6b289
d001e528:	f8dffac3 			; <UNDEFINED> instruction: 0xf8dffac3
d001e52c:	462a0728 	strtmi	r0, [sl], -r8, lsr #14
d001e530:	34014639 	strcc	r4, [r1], #-1593	; 0xfffff9c7
d001e534:	f10b4478 			; <UNDEFINED> instruction: 0xf10b4478
d001e538:	f10a0b01 			; <UNDEFINED> instruction: 0xf10a0b01
d001e53c:	f7f60a20 			; <UNDEFINED> instruction: 0xf7f60a20
d001e540:	e6dffaf0 			; <UNDEFINED> instruction: 0xe6dffaf0
d001e544:	f8129a10 			; <UNDEFINED> instruction: 0xf8129a10
d001e548:	2b0d3b01 	blcs	0xd036d154
d001e54c:	d0019210 	andle	r9, r1, r0, lsl r2
d001e550:	e6e13401 	strbt	r3, [r1], r1, lsl #8
d001e554:	f44fab36 			; <UNDEFINED> instruction: 0xf44fab36
d001e558:	f04f721a 			; <UNDEFINED> instruction: 0xf04f721a
d001e55c:	46300900 	ldrtmi	r0, [r0], -r0, lsl #18
d001e560:	7024f853 	eorvc	pc, r4, r3, asr r8	; <UNPREDICTABLE>
d001e564:	5ce3ab24 	vstmiapl	r3!, {d26-<overflow reg d43>}
d001e568:	fb024639 	blx	0xd00afe56
d001e56c:	22016303 	andcs	r6, r1, #201326592	; 0xc000000
d001e570:	3368f503 	msrcc	SPSR_f, #12582912	; 0xc00000
d001e574:	8028f8b3 	strhthi	pc, [r8], -r3	; <UNPREDICTABLE>
d001e578:	fab8f7f6 	blx	0xcee5c558
d001e57c:	d9e745c8 	stmible	r7!, {r3, r6, r7, r8, sl, lr}^
d001e580:	01d1f64f 	bicseq	pc, r1, pc, asr #12
d001e584:	f7f64628 			; <UNDEFINED> instruction: 0xf7f64628
d001e588:	4628fa93 			; <UNDEFINED> instruction: 0x4628fa93
d001e58c:	0189ea4f 	orreq	lr, r9, pc, asr #20
d001e590:	f7f6b289 			; <UNDEFINED> instruction: 0xf7f6b289
d001e594:	eb07fa8d 	bl	0xd021cfd0
d001e598:	22000109 	andcs	r0, r0, #1073741826	; 0x40000002
d001e59c:	f1094628 			; <UNDEFINED> instruction: 0xf1094628
d001e5a0:	f7f60901 			; <UNDEFINED> instruction: 0xf7f60901
d001e5a4:	e7e9fabe 			; <UNDEFINED> instruction: 0xe7e9fabe
d001e5a8:	23003701 	movwcs	r3, #1793	; 0x701
d001e5ac:	f8554632 			; <UNDEFINED> instruction: 0xf8554632
d001e5b0:	f7f71b04 			; <UNDEFINED> instruction: 0xf7f71b04
d001e5b4:	f8d8fcf9 			; <UNDEFINED> instruction: 0xf8d8fcf9
d001e5b8:	6da03630 	stcvs	6, cr3, [r0, #192]!	; 0xc0
d001e5bc:	d3f3429f 	mvnsle	r4, #-268435447	; 0xf0000009
d001e5c0:	bebff7fe 	mrclt	7, 5, APSR_nzcv, cr15, cr14, {7}
d001e5c4:	4690f8df 			; <UNDEFINED> instruction: 0x4690f8df
d001e5c8:	6da3447c 	cfstrsvs	mvf4, [r3, #496]!	; 0x1f0
d001e5cc:	f47e2b00 			; <UNDEFINED> instruction: 0xf47e2b00
d001e5d0:	f8dfac8e 			; <UNDEFINED> instruction: 0xf8dfac8e
d001e5d4:	447b3688 	ldrbtmi	r3, [fp], #-1672	; 0xfffff978
d001e5d8:	2b64681b 	blcs	0xd193864c
d001e5dc:	f8dfd92f 			; <UNDEFINED> instruction: 0xf8dfd92f
d001e5e0:	22004680 	andcs	r4, r0, #128, 12	; 0x8000000
d001e5e4:	067cf8df 			; <UNDEFINED> instruction: 0x067cf8df
d001e5e8:	4611447c 			; <UNDEFINED> instruction: 0x4611447c
d001e5ec:	f7f14478 			; <UNDEFINED> instruction: 0xf7f14478
d001e5f0:	6da3fdd3 	stcvs	13, cr15, [r3, #844]!	; 0x34c
d001e5f4:	f47e2b00 			; <UNDEFINED> instruction: 0xf47e2b00
d001e5f8:	f8dfac7a 			; <UNDEFINED> instruction: 0xf8dfac7a
d001e5fc:	2204166c 	andcs	r1, r4, #108, 12	; 0x6c00000
d001e600:	44794620 	ldrbtmi	r4, [r9], #-1568	; 0xfffff9e0
d001e604:	f95bf7f2 			; <UNDEFINED> instruction: 0xf95bf7f2
d001e608:	db0e2800 	blle	0xd03a8610
d001e60c:	fb032338 	blx	0xd00e72f6
d001e610:	f5034300 			; <UNDEFINED> instruction: 0xf5034300
d001e614:	f893337f 			; <UNDEFINED> instruction: 0xf893337f
d001e618:	b132224e 	teqlt	r2, lr, asr #4
d001e61c:	224cf893 	subcs	pc, ip, #9633792	; 0x930000
d001e620:	f893b1ca 			; <UNDEFINED> instruction: 0xf893b1ca
d001e624:	2b043254 	blcs	0xd012af7c
d001e628:	f8dfd015 			; <UNDEFINED> instruction: 0xf8dfd015
d001e62c:	f8df1640 			; <UNDEFINED> instruction: 0xf8df1640
d001e630:	44790640 	ldrbtmi	r0, [r9], #-1600	; 0xfffff9c0
d001e634:	f7f14478 			; <UNDEFINED> instruction: 0xf7f14478
d001e638:	f7fefe09 			; <UNDEFINED> instruction: 0xf7fefe09
d001e63c:	9a16bc58 	bls	0xd05cd7a4
d001e640:	0630f8df 			; <UNDEFINED> instruction: 0x0630f8df
d001e644:	44784611 	ldrbtmi	r4, [r8], #-1553	; 0xfffff9ef
d001e648:	fda6f7f1 	stc2	7, cr15, [r6, #964]!	; 0x3c4
d001e64c:	2b006da3 	blcs	0xd0039ce0
d001e650:	ac4df47e 	cfstrdge	mvd15, [sp], {126}	; 0x7e
d001e654:	f8dfe7c3 			; <UNDEFINED> instruction: 0xf8dfe7c3
d001e658:	23384620 	teqcs	r8, #32, 12	; 0x2000000
d001e65c:	fb03447c 	blx	0xd00ef856
d001e660:	23004000 	movwcs	r4, #0
d001e664:	307ff500 	rsbscc	pc, pc, r0, lsl #10
d001e668:	f8d04619 			; <UNDEFINED> instruction: 0xf8d04619
d001e66c:	6da02248 	sfmvs	f2, 4, [r0, #288]!	; 0x120
d001e670:	fc9af7f7 	ldc2	7, cr15, [sl], {247}	; 0xf7
d001e674:	bc3bf7fe 	ldclt	7, cr15, [fp], #-1016	; 0xfffffc08
d001e678:	462f2500 	strtmi	r2, [pc], -r0, lsl #10
d001e67c:	bc6af7fe 	stcllt	7, cr15, [sl], #-1016	; 0xfffffc08
d001e680:	683088b3 	ldmdavs	r0!, {r0, r1, r4, r5, r7, fp, pc}
d001e684:	b2921cda 	addslt	r1, r2, #55808	; 0xda00
d001e688:	d8092a01 	stmdale	r9, {r0, r9, fp, sp}
d001e68c:	71fef64f 	mvnsvc	pc, pc, asr #12
d001e690:	428b2201 	addmi	r2, fp, #268435456	; 0x10000000
d001e694:	4639bf0c 	ldrtmi	fp, [r9], -ip, lsl #30
d001e698:	f7f74629 			; <UNDEFINED> instruction: 0xf7f74629
d001e69c:	e016fc57 	ands	pc, r6, r7, asr ip	; <UNPREDICTABLE>
d001e6a0:	43592138 	cmpmi	r9, #56, 2
d001e6a4:	f5031863 			; <UNDEFINED> instruction: 0xf5031863
d001e6a8:	f893337f 			; <UNDEFINED> instruction: 0xf893337f
d001e6ac:	b99a224e 	ldmiblt	sl, {r1, r2, r3, r6, r9, sp}
d001e6b0:	317ff501 	cmncc	pc, r1, lsl #10	; <UNPREDICTABLE>
d001e6b4:	710af501 	tstvc	sl, r1, lsl #10	; <UNPREDICTABLE>
d001e6b8:	f8d14421 			; <UNDEFINED> instruction: 0xf8d14421
d001e6bc:	6908c00c 	stmdbvs	r8, {r2, r3, lr, pc}
d001e6c0:	7e0a69cb 	vmlsvc.f16	s12, s21, s22	; <UNPREDICTABLE>
d001e6c4:	e9c466a3 	stmib	r4, {r0, r1, r5, r7, r9, sl, sp, lr}^
d001e6c8:	e9c49c16 	stmib	r4, {r1, r2, r4, sl, fp, ip, pc}^
d001e6cc:	f10a0218 			; <UNDEFINED> instruction: 0xf10a0218
d001e6d0:	36080a01 	strcc	r0, [r8], -r1, lsl #20
d001e6d4:	bc4bf7fe 	mcrrlt	7, 15, pc, fp, cr14	; <UNPREDICTABLE>
d001e6d8:	f8d32201 			; <UNDEFINED> instruction: 0xf8d32201
d001e6dc:	e7dc1248 	ldrb	r1, [ip, r8, asr #4]
d001e6e0:	f7fe4644 			; <UNDEFINED> instruction: 0xf7fe4644
d001e6e4:	f899bc60 			; <UNDEFINED> instruction: 0xf899bc60
d001e6e8:	e9d92008 	ldmib	r9, {r3, sp}^
d001e6ec:	bb4a0100 	bllt	0xd129eaf4
d001e6f0:	338ff505 	orrcc	pc, pc, #20971520	; 0x1400000
d001e6f4:	31b8f8d3 			; <UNDEFINED> instruction: 0x31b8f8d3
d001e6f8:	f100440b 			; <UNDEFINED> instruction: 0xf100440b
d001e6fc:	1e51060c 	cdpne	6, 5, cr0, cr1, cr12, {0}
d001e700:	f10a9012 			; <UNDEFINED> instruction: 0xf10a9012
d001e704:	f0260a01 			; <UNDEFINED> instruction: 0xf0260a01
d001e708:	424a0603 	submi	r0, sl, #3145728	; 0x300000
d001e70c:	090cf109 	stmdbeq	ip, {r0, r3, r8, ip, sp, lr, pc}
d001e710:	0606eba3 	streq	lr, [r6], -r3, lsr #23
d001e714:	f24f414a 	vrhadd.s8	q10, <illegal reg q7.5>, q5
d001e718:	b2b32140 	adcslt	r2, r3, #64, 2
d001e71c:	f7f69213 			; <UNDEFINED> instruction: 0xf7f69213
d001e720:	9812fd69 	ldmdals	r2, {r0, r3, r5, r6, r8, sl, fp, ip, sp, lr, pc}
d001e724:	9a130c33 	bls	0xd04e17f8
d001e728:	21c0f24f 	biccs	pc, r0, pc, asr #4
d001e72c:	f7f63004 			; <UNDEFINED> instruction: 0xf7f63004
d001e730:	f8dbfd61 			; <UNDEFINED> instruction: 0xf8dbfd61
d001e734:	6daa33c0 	stcvs	3, cr3, [sl, #768]!	; 0x300
d001e738:	d24d459a 	suble	r4, sp, #645922816	; 0x26800000
d001e73c:	d0d22a00 	sbcsle	r2, r2, r0, lsl #20
d001e740:	bbb6f7fe 	bllt	0xceddc740
d001e744:	d1242a01 			; <UNDEFINED> instruction: 0xd1242a01
d001e748:	fb03233c 	blx	0xd00e7442
d001e74c:	f5035301 			; <UNDEFINED> instruction: 0xf5035301
d001e750:	f893335f 			; <UNDEFINED> instruction: 0xf893335f
d001e754:	b9d663ef 	ldmiblt	r6, {r0, r1, r2, r3, r5, r6, r7, r8, r9, sp, lr}^
d001e758:	33ecf893 	mvncc	pc, #9633792	; 0x930000
d001e75c:	b2db3b07 	sbcslt	r3, fp, #7168	; 0x1c00
d001e760:	d8142b0a 	ldmdale	r4, {r1, r3, r8, r9, fp, sp}
d001e764:	5603f240 	strpl	pc, [r3], -r0, asr #4
d001e768:	f303fa26 	vpmax.u8	d15, d3, d22
d001e76c:	0f01f013 	svceq	0x0001f013
d001e770:	bf0c9b0f 	svclt	0x000c9b0f
d001e774:	461e463e 			; <UNDEFINED> instruction: 0x461e463e
d001e778:	0c3cf04f 	ldceq	0, cr15, [ip], #-316	; 0xfffffec4
d001e77c:	fb0c9b11 	blx	0xd03453ca
d001e780:	f5033301 			; <UNDEFINED> instruction: 0xf5033301
d001e784:	f8d3335f 			; <UNDEFINED> instruction: 0xf8d3335f
d001e788:	443333e8 	ldrtmi	r3, [r3], #-1000	; 0xfffffc18
d001e78c:	463ee7b5 			; <UNDEFINED> instruction: 0x463ee7b5
d001e790:	2338e7f2 	teqcs	r8, #63438848	; 0x3c80000
d001e794:	18e9434b 	stmiane	r9!, {r0, r1, r3, r6, r8, r9, lr}^
d001e798:	317ff501 	cmncc	pc, r1, lsl #10	; <UNPREDICTABLE>
d001e79c:	624ef891 	subvs	pc, lr, #9502720	; 0x910000
d001e7a0:	f503b996 			; <UNDEFINED> instruction: 0xf503b996
d001e7a4:	f8df337f 			; <UNDEFINED> instruction: 0xf8df337f
d001e7a8:	f50344d4 			; <UNDEFINED> instruction: 0xf50344d4
d001e7ac:	447c730a 	ldrbtmi	r7, [ip], #-778	; 0xfffffcf6
d001e7b0:	68d8442b 	ldmvs	r8, {r0, r1, r3, r5, sl, lr}^
d001e7b4:	69da6919 	ldmibvs	sl, {r0, r3, r4, r8, fp, sp, lr}^
d001e7b8:	66aa7e1b 	ssatvs	r7, #11, fp, lsl #28
d001e7bc:	4016e9c5 	andsmi	lr, r6, r5, asr #19
d001e7c0:	1318e9c5 	tstne	r8, #3227648	; 0x314000
d001e7c4:	bb74f7fe 	bllt	0xd1d5c7c4
d001e7c8:	3248f8d1 	subcc	pc, r8, #13697024	; 0xd10000
d001e7cc:	5100f44f 	tstpl	r0, pc, asr #8	; <UNPREDICTABLE>
d001e7d0:	0301f043 	movweq	pc, #4163	; 0x1043	; <UNPREDICTABLE>
d001e7d4:	e7909110 			; <UNDEFINED> instruction: 0xe7909110
d001e7d8:	f47e2a00 			; <UNDEFINED> instruction: 0xf47e2a00
d001e7dc:	f8dfab69 			; <UNDEFINED> instruction: 0xf8dfab69
d001e7e0:	f50504a0 			; <UNDEFINED> instruction: 0xf50504a0
d001e7e4:	4611358f 	ldrmi	r3, [r1], -pc, lsl #11
d001e7e8:	6498f8df 	ldrvs	pc, [r8], #2271	; 0x8df
d001e7ec:	f8df4478 			; <UNDEFINED> instruction: 0xf8df4478
d001e7f0:	f7f1a498 			; <UNDEFINED> instruction: 0xf7f1a498
d001e7f4:	f8d5fcd1 			; <UNDEFINED> instruction: 0xf8d5fcd1
d001e7f8:	f50521bc 			; <UNDEFINED> instruction: 0xf50521bc
d001e7fc:	f8d571e0 			; <UNDEFINED> instruction: 0xf8d571e0
d001e800:	f7f601b8 			; <UNDEFINED> instruction: 0xf7f601b8
d001e804:	1ce3f921 			; <UNDEFINED> instruction: 0x1ce3f921
d001e808:	44fa447e 	ldrbtmi	r4, [sl], #1150	; 0x47e
d001e80c:	0303f023 	movweq	pc, #12323	; 0x3023	; <UNPREDICTABLE>
d001e810:	0508eba3 	streq	lr, [r8, #-2979]	; 0xfffff45d
d001e814:	b11d9311 	tstlt	sp, r1, lsl r3
d001e818:	2b006db3 	blcs	0xd0039eec
d001e81c:	80aef000 	adchi	pc, lr, r0
d001e820:	3468f8df 	strbtcc	pc, [r8], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d001e824:	0a00f04f 	beq	0xd005a968
d001e828:	f503447b 			; <UNDEFINED> instruction: 0xf503447b
d001e82c:	9312355f 	tstls	r2, #398458880	; 0x17c00000
d001e830:	3367f503 	msrcc	SPSR_sxc, #12582912	; 0xc00000
d001e834:	7579f505 	ldrbvc	pc, [r9, #-1285]!	; 0xfffffafb	; <UNPREDICTABLE>
d001e838:	f8df9313 			; <UNDEFINED> instruction: 0xf8df9313
d001e83c:	447b3454 	ldrbtmi	r3, [fp], #-1108	; 0xfffffbac
d001e840:	9b139314 	blls	0xd0503498
d001e844:	31c4f8d3 	ldrdcc	pc, [r4, #131]	; 0x83
d001e848:	d204459a 	andle	r4, r4, #645922816	; 0x26800000
d001e84c:	6d9e9b12 	vldrvs	d9, [lr, #72]	; 0x48
d001e850:	f0002e00 			; <UNDEFINED> instruction: 0xf0002e00
d001e854:	ad3680a2 	ldcge	0, cr8, [r6, #-648]!	; 0xfffffd78
d001e858:	21002640 	tstcs	r0, r0, asr #12
d001e85c:	9434f8df 	ldrtls	pc, [r4], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d001e860:	46284632 			; <UNDEFINED> instruction: 0x46284632
d001e864:	fb4af002 	blx	0xd12da876
d001e868:	142cf8df 	strtne	pc, [ip], #-2271	; 0xfffff721
d001e86c:	46282208 	strtmi	r2, [r8], -r8, lsl #4
d001e870:	44f94479 	ldrbtmi	r4, [r9], #1145	; 0x479
d001e874:	fb50f002 	blx	0xd145a886
d001e878:	990f2302 	stmdbls	pc, {r1, r8, r9, sp}	; <UNPREDICTABLE>
d001e87c:	e9c59a11 	stmib	r5, {r0, r4, r9, fp, ip, pc}^
d001e880:	f5093602 			; <UNDEFINED> instruction: 0xf5093602
d001e884:	4432337f 	ldrtmi	r3, [r2], #-895	; 0xfffffc81
d001e888:	6058f8d9 	ldrsbvs	pc, [r8], #-137	; 0xffffff77	; <UNPREDICTABLE>
d001e88c:	321cf8d3 	andscc	pc, ip, #13828096	; 0xd30000
d001e890:	440b331f 	strmi	r3, [fp], #-799	; 0xfffffce1
d001e894:	f0239910 			; <UNDEFINED> instruction: 0xf0239910
d001e898:	6369031f 	cmnvs	r9, #2080374784	; 0x7c000000
d001e89c:	61ab440b 			; <UNDEFINED> instruction: 0x61ab440b
d001e8a0:	61eb2301 	mvnvs	r2, r1, lsl #6
d001e8a4:	e9c54bc4 	stmib	r5, {r2, r6, r7, r8, r9, fp, lr}^
d001e8a8:	23203208 			; <UNDEFINED> instruction: 0x23203208
d001e8ac:	1e0b62eb 	cdpne	2, 0, cr6, cr11, cr11, {7}
d001e8b0:	2301bf18 	movwcs	fp, #7960	; 0x1f18
d001e8b4:	2404e9c5 	strcs	lr, [r4], #-2501	; 0xfffff63b
d001e8b8:	2e0063ab 	cdpcs	3, 0, cr6, cr0, cr11, {5}
d001e8bc:	aaf8f47e 	bge	0xcfe5babc
d001e8c0:	462248f6 			; <UNDEFINED> instruction: 0x462248f6
d001e8c4:	f8df4631 			; <UNDEFINED> instruction: 0xf8df4631
d001e8c8:	4478b3d8 	ldrbtmi	fp, [r8], #-984	; 0xfffffc28
d001e8cc:	37fff04f 	ldrbcc	pc, [pc, pc, asr #32]!	; <UNPREDICTABLE>
d001e8d0:	fc62f7f1 	stc2l	7, cr15, [r2], #-964	; 0xfffffc3c
d001e8d4:	f04f2364 			; <UNDEFINED> instruction: 0xf04f2364
d001e8d8:	44fb080a 	ldrbtmi	r0, [fp], #2058	; 0x80a
d001e8dc:	9040f8cd 	subls	pc, r0, sp, asr #17
d001e8e0:	faf3fbb4 	blx	0xcfd1d7b8
d001e8e4:	431afb03 	tstmi	sl, #3072	; 0xc00	; <UNPREDICTABLE>
d001e8e8:	9b10930f 	blls	0xd044352c
d001e8ec:	f8d342b4 			; <UNDEFINED> instruction: 0xf8d342b4
d001e8f0:	f2409058 	vqadd.s8	<illegal reg q12.5>, q0, q4
d001e8f4:	f1b980fd 			; <UNDEFINED> instruction: 0xf1b980fd
d001e8f8:	f0000f00 			; <UNDEFINED> instruction: 0xf0000f00
d001e8fc:	4be980a0 	blmi	0xcfa7eb84
d001e900:	447b43ff 	ldrbtmi	r4, [fp], #-1023	; 0xfffffc01
d001e904:	6d9b63ef 	ldcvs	3, cr6, [fp, #956]	; 0x3bc
d001e908:	f47e2b00 			; <UNDEFINED> instruction: 0xf47e2b00
d001e90c:	49e6aad1 	stmibmi	r6!, {r0, r4, r6, r7, r9, fp, sp, pc}^
d001e910:	46282208 	strtmi	r2, [r8], -r8, lsl #4
d001e914:	4479692c 	ldrbtmi	r6, [r9], #-2348	; 0xfffff6d4
d001e918:	fb0ef002 	blx	0xd03da92a
d001e91c:	68abbb38 	stmiavs	fp!, {r3, r4, r5, r8, r9, fp, ip, sp, pc}
d001e920:	d1242b02 			; <UNDEFINED> instruction: 0xd1242b02
d001e924:	2b4068eb 	blcs	0xd1038cd8
d001e928:	692bd121 	stmdbvs	fp!, {r0, r5, r8, ip, lr, pc}
d001e92c:	d11e429c 			; <UNDEFINED> instruction: 0xd11e429c
d001e930:	2b206aeb 	blcs	0xd08394e4
d001e934:	6baed11b 	blvs	0xcebd2da8
d001e938:	d8182e01 	ldmdale	r8, {r0, r9, sl, fp, sp}
d001e93c:	1e4b6969 	vmlsne.f16	s13, s22, s19	; <UNPREDICTABLE>
d001e940:	0fbef5b3 	svceq	0x00bef5b3
d001e944:	69aad213 	stmibvs	sl!, {r0, r1, r4, r9, ip, lr, pc}
d001e948:	f5b31e53 			; <UNDEFINED> instruction: 0xf5b31e53
d001e94c:	d20e0fbe 	andle	r0, lr, #760	; 0x2f8
d001e950:	d10c06d7 	ldrdle	r0, [ip, -r7]
d001e954:	d80a4291 	stmdale	sl, {r0, r4, r7, r9, lr}
d001e958:	1a506b2b 	bne	0xd143960c
d001e95c:	d8064283 	stmdale	r6, {r0, r1, r7, r9, lr}
d001e960:	2e006b68 	vmlscs.f64	d6, d0, d24
d001e964:	80d5f040 	sbcshi	pc, r5, r0, asr #32
d001e968:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d001e96c:	49cf80e3 	stmibmi	pc, {r0, r1, r5, r6, r7, pc}^	; <UNPREDICTABLE>
d001e970:	447948cf 	ldrbtmi	r4, [r9], #-2255	; 0xfffff731
d001e974:	f7f14478 			; <UNDEFINED> instruction: 0xf7f14478
d001e978:	e10bfc69 	tst	fp, r9, ror #24	; <UNPREDICTABLE>
d001e97c:	6f80f5b5 	svcvs	0x0080f5b5
d001e980:	464046a9 	strbmi	r4, [r0], -r9, lsr #13
d001e984:	bf284651 	svclt	0x00284651
d001e988:	6980f44f 	stmibvs	r0, {r0, r1, r2, r3, r6, sl, ip, sp, lr, pc}
d001e98c:	44c8464a 	strbmi	r4, [r8], #1610	; 0x64a
d001e990:	0509eba5 	streq	lr, [r9, #-2981]	; 0xfffff45b
d001e994:	f858f7f6 			; <UNDEFINED> instruction: 0xf858f7f6
d001e998:	7aebe73d 	bvc	0xcfb18694
d001e99c:	d03c2b00 	eorsle	r2, ip, r0, lsl #22
d001e9a0:	7becf50d 	blvc	0xcfb5bddc
d001e9a4:	eba3e027 	bl	0xce916a48
d001e9a8:	69290806 	stmdbvs	r9!, {r1, r2, fp}
d001e9ac:	2001465a 	andcs	r4, r1, sl, asr r6
d001e9b0:	7f80f5b8 	svcvc	0x0080f5b8
d001e9b4:	bf284431 	svclt	0x00284431
d001e9b8:	7880f44f 	stmvc	r0, {r0, r1, r2, r3, r6, sl, ip, sp, lr, pc}
d001e9bc:	ea4f0089 	b	0xd13debe8
d001e9c0:	93150388 	tstls	r5, #136, 6	; 0x20000002
d001e9c4:	ffc4f7f5 			; <UNDEFINED> instruction: 0xffc4f7f5
d001e9c8:	7a2ab1f0 	bvc	0xd0acb190
d001e9cc:	2a076868 	bcs	0xd01f8b74
d001e9d0:	44389b15 	ldrtmi	r9, [r8], #-2837	; 0xfffff4eb
d001e9d4:	ab36d11c 	blge	0xd0dd2e4c
d001e9d8:	4619465a 			; <UNDEFINED> instruction: 0x4619465a
d001e9dc:	0901f109 	stmdbeq	r1, {r0, r3, r8, ip, sp, lr, pc}
d001e9e0:	cb04f852 	blgt	0xd015cb30
d001e9e4:	f80345c8 			; <UNDEFINED> instruction: 0xf80345c8
d001e9e8:	d1f7cb01 	mvnsle	ip, r1, lsl #22
d001e9ec:	44304642 	ldrtmi	r4, [r0], #-1602	; 0xfffff9be
d001e9f0:	f7f64446 			; <UNDEFINED> instruction: 0xf7f64446
d001e9f4:	696bf829 	stmdbvs	fp!, {r0, r3, r5, fp, ip, sp, lr, pc}^
d001e9f8:	d90542b3 	stmdble	r5, {r0, r1, r4, r5, r7, r9, lr}
d001e9fc:	f8d29a14 			; <UNDEFINED> instruction: 0xf8d29a14
d001ea00:	f1b99058 			; <UNDEFINED> instruction: 0xf1b99058
d001ea04:	d0ce0f00 	sbcle	r0, lr, r0, lsl #30
d001ea08:	0a01f10a 	beq	0xd009ae38
d001ea0c:	e718353c 			; <UNDEFINED> instruction: 0xe718353c
d001ea10:	4659461a 			; <UNDEFINED> instruction: 0x4659461a
d001ea14:	0086eb00 	addeq	lr, r6, r0, lsl #22
d001ea18:	7a2be7ea 	bvc	0xd0b189c8
d001ea1c:	b2db3b07 	sbcslt	r3, fp, #7168	; 0x1c00
d001ea20:	d8052b0a 	stmdale	r5, {r1, r3, r8, r9, fp, sp}
d001ea24:	5203f240 	andpl	pc, r3, #64, 4
d001ea28:	f303fa22 	vpmax.u8	d15, d3, d18
d001ea2c:	d4eb07db 	strbtle	r0, [fp], #2011	; 0x7db
d001ea30:	22046868 	andcs	r6, r4, #104, 16	; 0x680000
d001ea34:	44384629 	ldrtmi	r4, [r8], #-1577	; 0xfffff9d7
d001ea38:	f806f7f6 			; <UNDEFINED> instruction: 0xf806f7f6
d001ea3c:	1ba3e7e4 	blne	0xce9189d4
d001ea40:	f106aa76 			; <UNDEFINED> instruction: 0xf106aa76
d001ea44:	46480140 	strbmi	r0, [r8], -r0, asr #2
d001ea48:	6f80f5b3 	svcvs	0x0080f5b3
d001ea4c:	bf289211 	svclt	0x00289211
d001ea50:	6380f44f 	orrvs	pc, r0, #1325400064	; 0x4f000000
d001ea54:	f7f59312 			; <UNDEFINED> instruction: 0xf7f59312
d001ea58:	2800ff7b 	stmdacs	r0, {r0, r1, r3, r4, r5, r6, r8, r9, sl, fp, ip, sp, lr, pc}
d001ea5c:	9a11d048 	bls	0xd0492b84
d001ea60:	9b124649 	blls	0xd04b038c
d001ea64:	f81c4694 			; <UNDEFINED> instruction: 0xf81c4694
d001ea68:	f04f0b01 			; <UNDEFINED> instruction: 0xf04f0b01
d001ea6c:	40470908 	submi	r0, r7, r8, lsl #18
d001ea70:	0001f017 	andeq	pc, r1, r7, lsl r0	; <UNPREDICTABLE>
d001ea74:	bf184a61 	svclt	0x00184a61
d001ea78:	f1b94610 			; <UNDEFINED> instruction: 0xf1b94610
d001ea7c:	ea800901 	b	0xce020e88
d001ea80:	d1f50757 	mvnsle	r0, r7, asr r7
d001ea84:	428b3101 	addmi	r3, fp, #1073741824	; 0x40000000
d001ea88:	441ed1ed 	ldrmi	sp, [lr], #-493	; 0xfffffe13
d001ea8c:	3000f8db 	ldrdcc	pc, [r0], -fp
d001ea90:	f43f2b00 			; <UNDEFINED> instruction: 0xf43f2b00
d001ea94:	f5b4af2a 			; <UNDEFINED> instruction: 0xf5b4af2a
d001ea98:	f4ff4f00 			; <UNDEFINED> instruction: 0xf4ff4f00
d001ea9c:	2164af26 	cmncs	r4, r6, lsr #30
d001eaa0:	e00c468c 	and	r4, ip, ip, lsl #13
d001eaa4:	0209eb00 	andeq	lr, r9, #0, 22
d001eaa8:	08529b0f 	ldmdaeq	r2, {r0, r1, r2, r3, r8, r9, fp, ip, pc}^
d001eaac:	33634353 	cmncc	r3, #1275068417	; 0x4c000001
d001eab0:	f3fcfbb3 			; <UNDEFINED> instruction: 0xf3fcfbb3
d001eab4:	330afb02 	movwcc	pc, #43778	; 0xab02	; <UNPREDICTABLE>
d001eab8:	d217429e 	andsle	r4, r7, #-536870903	; 0xe0000009
d001eabc:	1c481e51 	mcrrne	14, 5, r1, r8, cr1
d001eac0:	d3ef4589 	mvnle	r4, #574619648	; 0x22400000
d001eac4:	f4ff45c1 			; <UNDEFINED> instruction: 0xf4ff45c1
d001eac8:	f1b8af10 			; <UNDEFINED> instruction: 0xf1b8af10
d001eacc:	f63f0f64 			; <UNDEFINED> instruction: 0xf63f0f64
d001ead0:	4878af0c 	ldmdami	r8!, {r2, r3, r8, r9, sl, fp, sp, pc}^
d001ead4:	080af04f 	stmdaeq	sl, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d001ead8:	46314622 	ldrtmi	r4, [r1], -r2, lsr #12
d001eadc:	f7f14478 			; <UNDEFINED> instruction: 0xf7f14478
d001eae0:	fbb9fb5b 	blx	0xcee9d856
d001eae4:	fb09f9f8 	blx	0xd029d2ce
d001eae8:	e6fe8808 	ldrbt	r8, [lr], r8, lsl #16
d001eaec:	e7e74691 			; <UNDEFINED> instruction: 0xe7e74691
d001eaf0:	447b4b71 	ldrbtmi	r4, [fp], #-2929	; 0xfffff48f
d001eaf4:	2b006d9b 	blcs	0xd003a168
d001eaf8:	af01f47f 	svcge	0x0001f47f
d001eafc:	0f64f1b8 	svceq	0x0064f1b8
d001eb00:	aefdf63f 	mrcge	6, 7, APSR_nzcv, cr13, cr15, {1}
d001eb04:	4622486d 	strtmi	r4, [r2], -sp, ror #16
d001eb08:	44784621 	ldrbtmi	r4, [r8], #-1569	; 0xfffff9df
d001eb0c:	fb44f7f1 	blx	0xd115cada
d001eb10:	f5b0e6f5 			; <UNDEFINED> instruction: 0xf5b0e6f5
d001eb14:	f4ff5f80 			; <UNDEFINED> instruction: 0xf4ff5f80
d001eb18:	ea43af2a 	b	0xd110a7c8
d001eb1c:	06f60600 	ldrbteq	r0, [r6], r0, lsl #12
d001eb20:	af25f47f 	svcge	0x0025f47f
d001eb24:	42831ad3 	addmi	r1, r3, #864256	; 0xd3000
d001eb28:	af21f4ff 	svcge	0x0021f4ff
d001eb2c:	42831a5b 	addmi	r1, r3, #372736	; 0x5b000
d001eb30:	af1df4ff 	svcge	0x001df4ff
d001eb34:	2b0069eb 	blcs	0xd00392e8
d001eb38:	af19f43f 	svcge	0x0019f43f
d001eb3c:	f57f07d8 			; <UNDEFINED> instruction: 0xf57f07d8
d001eb40:	f023af16 			; <UNDEFINED> instruction: 0xf023af16
d001eb44:	42990301 	addsmi	r0, r9, #67108864	; 0x4000000
d001eb48:	af11f67f 	svcge	0x0011f67f
d001eb4c:	2b3f6a6b 	blcs	0xd0ff9500
d001eb50:	af0df67f 	svcge	0x000df67f
d001eb54:	0040f1a3 	subeq	pc, r0, r3, lsr #3
d001eb58:	f63f4281 			; <UNDEFINED> instruction: 0xf63f4281
d001eb5c:	429caf08 	addsmi	sl, ip, #8, 30
d001eb60:	af05f4ff 	svcge	0x0005f4ff
d001eb64:	43231ae4 			; <UNDEFINED> instruction: 0x43231ae4
d001eb68:	f47f079b 			; <UNDEFINED> instruction: 0xf47f079b
d001eb6c:	6aabaf00 	bvs	0xceb0a774
d001eb70:	0f94ebb3 	svceq	0x0094ebb3
d001eb74:	aefbf47f 	mrcge	4, 7, APSR_nzcv, cr11, cr15, {3}
d001eb78:	f1036a2b 			; <UNDEFINED> instruction: 0xf1036a2b
d001eb7c:	f5b15140 			; <UNDEFINED> instruction: 0xf5b15140
d001eb80:	f4bf0fc0 			; <UNDEFINED> instruction: 0xf4bf0fc0
d001eb84:	f1c3aef4 			; <UNDEFINED> instruction: 0xf1c3aef4
d001eb88:	f5034350 			; <UNDEFINED> instruction: 0xf5034350
d001eb8c:	429a03c0 	addsmi	r0, sl, #192, 6
d001eb90:	aeedf63f 	mcrge	6, 7, pc, cr13, cr15, {1}	; <UNPREDICTABLE>
d001eb94:	447c4c4a 	ldrbtmi	r4, [ip], #-3146	; 0xfffff3b6
d001eb98:	29006da1 	stmdbcs	r0, {r0, r5, r7, r8, sl, fp, sp, lr}
d001eb9c:	a988f47e 	stmibge	r8, {r1, r2, r3, r4, r5, r6, sl, ip, sp, lr, pc}
d001eba0:	462a2340 	strtmi	r2, [sl], -r0, asr #6
d001eba4:	f7f54608 			; <UNDEFINED> instruction: 0xf7f54608
d001eba8:	6da3ff0b 	stcvs	15, cr15, [r3, #44]!	; 0x2c
d001ebac:	f47e2b00 			; <UNDEFINED> instruction: 0xf47e2b00
d001ebb0:	6928a97f 	stmdbvs	r8!, {r0, r1, r2, r3, r4, r5, r6, r8, fp, sp, pc}
d001ebb4:	b942f7fe 	stmdblt	r2, {r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}^
d001ebb8:	d0010000 	andle	r0, r1, r0
d001ebbc:	00009b6e 	andeq	r9, r0, lr, ror #22
d001ebc0:	ffff5906 			; <UNDEFINED> instruction: 0xffff5906
d001ebc4:	ffffc486 			; <UNDEFINED> instruction: 0xffffc486
d001ebc8:	ffffc47f 			; <UNDEFINED> instruction: 0xffffc47f
d001ebcc:	ffff58cc 			; <UNDEFINED> instruction: 0xffff58cc
d001ebd0:	ffffeaa7 			; <UNDEFINED> instruction: 0xffffeaa7
d001ebd4:	ffffeaa3 			; <UNDEFINED> instruction: 0xffffeaa3
d001ebd8:	00009ae4 	andeq	r9, r0, r4, ror #21
d001ebdc:	ffffeab8 			; <UNDEFINED> instruction: 0xffffeab8
d001ebe0:	ffffeabd 			; <UNDEFINED> instruction: 0xffffeabd
d001ebe4:	ffffeac0 			; <UNDEFINED> instruction: 0xffffeac0
d001ebe8:	ffffeaca 			; <UNDEFINED> instruction: 0xffffeaca
d001ebec:	00009a72 	andeq	r9, r0, r2, ror sl
d001ebf0:	00009a5a 	andeq	r9, r0, sl, asr sl
d001ebf4:	00009a06 	andeq	r9, r0, r6, lsl #20
d001ebf8:	ffffeacd 			; <UNDEFINED> instruction: 0xffffeacd
d001ebfc:	edb88320 	ldc	3, cr8, [r8, #128]!	; 0x80
d001ec00:	000099c4 	andeq	r9, r0, r4, asr #19
d001ec04:	ffffea94 			; <UNDEFINED> instruction: 0xffffea94
d001ec08:	00009906 	andeq	r9, r0, r6, lsl #18
d001ec0c:	ffffea52 			; <UNDEFINED> instruction: 0xffffea52
d001ec10:	ffffea23 			; <UNDEFINED> instruction: 0xffffea23
d001ec14:	ffffe9a3 			; <UNDEFINED> instruction: 0xffffe9a3
d001ec18:	000097a0 	andeq	r9, r0, r0, lsr #15
d001ec1c:	00009798 	muleq	r0, r8, r7
d001ec20:	00009780 	andeq	r9, r0, r0, lsl #15
d001ec24:	0000977e 	andeq	r9, r0, lr, ror r7
d001ec28:	0000976c 	andeq	r9, r0, ip, ror #14
d001ec2c:	00009754 	andeq	r9, r0, r4, asr r7
d001ec30:	000096f8 	strdeq	r9, [r0], -r8
d001ec34:	000096d4 	ldrdeq	r9, [r0], -r4
d001ec38:	ffffe87c 			; <UNDEFINED> instruction: 0xffffe87c
d001ec3c:	00009682 	andeq	r9, r0, r2, lsl #13
d001ec40:	ffffe856 			; <UNDEFINED> instruction: 0xffffe856
d001ec44:	0000961a 	andeq	r9, r0, sl, lsl r6
d001ec48:	00009602 	andeq	r9, r0, r2, lsl #12
d001ec4c:	000095a8 	andeq	r9, r0, r8, lsr #11
d001ec50:	0000957a 	andeq	r9, r0, sl, ror r5
d001ec54:	00009560 	andeq	r9, r0, r0, ror #10
d001ec58:	000094cc 	andeq	r9, r0, ip, asr #9
d001ec5c:	0005476e 	andeq	r4, r5, lr, ror #14
d001ec60:	000094ac 	andeq	r9, r0, ip, lsr #9
d001ec64:	ffffe6c9 			; <UNDEFINED> instruction: 0xffffe6c9
d001ec68:	ffffe37c 			; <UNDEFINED> instruction: 0xffffe37c
d001ec6c:	ffffe68e 			; <UNDEFINED> instruction: 0xffffe68e
d001ec70:	00009460 	andeq	r9, r0, r0, ror #8
d001ec74:	ffff1b7a 			; <UNDEFINED> instruction: 0xffff1b7a
d001ec78:	00009438 	andeq	r9, r0, r8, lsr r4
d001ec7c:	ffffe5a2 			; <UNDEFINED> instruction: 0xffffe5a2
d001ec80:	ffffe588 			; <UNDEFINED> instruction: 0xffffe588
d001ec84:	0000928c 	andeq	r9, r0, ip, lsl #5
d001ec88:	00000846 	andeq	r0, r0, r6, asr #16
d001ec8c:	0000926c 	andeq	r9, r0, ip, ror #4
d001ec90:	00009256 	andeq	r9, r0, r6, asr r2
d001ec94:	00009222 	andeq	r9, r0, r2, lsr #4
d001ec98:	00000550 	andeq	r0, r0, r0, asr r5
d001ec9c:	ffffe4b5 			; <UNDEFINED> instruction: 0xffffe4b5
d001eca0:	00054462 	andeq	r4, r5, r2, ror #8
d001eca4:	00009192 	muleq	r0, r2, r1
d001eca8:	000004aa 	andeq	r0, r0, sl, lsr #9
d001ecac:	ffffe411 			; <UNDEFINED> instruction: 0xffffe411
d001ecb0:	00009120 	andeq	r9, r0, r0, lsr #2
d001ecb4:	ffffe2a3 			; <UNDEFINED> instruction: 0xffffe2a3
d001ecb8:	00008fa2 	andeq	r8, r0, r2, lsr #31
d001ecbc:	ffffe275 			; <UNDEFINED> instruction: 0xffffe275
d001ecc0:	00008efe 	strdeq	r8, [r0], -lr
d001ecc4:	f43e2c00 			; <UNDEFINED> instruction: 0xf43e2c00
d001ecc8:	4b20af30 	blmi	0xd084a990
d001eccc:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d001ecd0:	f47e2a00 			; <UNDEFINED> instruction: 0xf47e2a00
d001ecd4:	4a1eab36 	bmi	0xd07c99b4
d001ecd8:	f7fe447a 			; <UNDEFINED> instruction: 0xf7fe447a
d001ecdc:	4d1dbd33 	ldcmi	13, cr11, [sp, #-204]	; 0xffffff34
d001ece0:	99122338 	ldmdbls	r2, {r3, r4, r5, r8, r9, sp}
d001ece4:	fb03447d 	blx	0xd00efee2
d001ece8:	f5035304 			; <UNDEFINED> instruction: 0xf5035304
d001ecec:	f893337f 			; <UNDEFINED> instruction: 0xf893337f
d001ecf0:	4291224c 	addsmi	r2, r1, #76, 4	; 0xc0000004
d001ecf4:	f893d105 			; <UNDEFINED> instruction: 0xf893d105
d001ecf8:	9913224f 	ldmdbls	r3, {r0, r1, r2, r3, r6, r9, sp}
d001ecfc:	f43f428a 			; <UNDEFINED> instruction: 0xf43f428a
d001ed00:	4b15aa5e 	blmi	0xd0589680
d001ed04:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d001ed08:	f47e2a00 			; <UNDEFINED> instruction: 0xf47e2a00
d001ed0c:	4a13ab1a 	bmi	0xd050997c
d001ed10:	f7fe447a 			; <UNDEFINED> instruction: 0xf7fe447a
d001ed14:	4d12bd17 	ldcmi	13, cr11, [r2, #-92]	; 0xffffffa4
d001ed18:	f505447d 			; <UNDEFINED> instruction: 0xf505447d
d001ed1c:	f8d32386 			; <UNDEFINED> instruction: 0xf8d32386
d001ed20:	f5b44628 			; <UNDEFINED> instruction: 0xf5b44628
d001ed24:	f47f7f80 			; <UNDEFINED> instruction: 0xf47f7f80
d001ed28:	6daba9e0 			; <UNDEFINED> instruction: 0x6daba9e0
d001ed2c:	f47e2b00 			; <UNDEFINED> instruction: 0xf47e2b00
d001ed30:	4b0cab08 	blmi	0xd0349958
d001ed34:	f7fe447b 			; <UNDEFINED> instruction: 0xf7fe447b
d001ed38:	9b13bcf0 	blls	0xd050e100
d001ed3c:	f47e2b00 			; <UNDEFINED> instruction: 0xf47e2b00
d001ed40:	2d00aeeb 	stccs	14, cr10, [r0, #-940]	; 0xfffffc54
d001ed44:	f7fed1c1 			; <UNDEFINED> instruction: 0xf7fed1c1
d001ed48:	bf00bee0 	svclt	0x0000bee0
d001ed4c:	00008dc8 	andeq	r8, r0, r8, asr #27
d001ed50:	ffffdc35 			; <UNDEFINED> instruction: 0xffffdc35
d001ed54:	00008db0 			; <UNDEFINED> instruction: 0x00008db0
d001ed58:	00008d90 	muleq	r0, r0, sp
d001ed5c:	ffffdeca 			; <UNDEFINED> instruction: 0xffffdeca
d001ed60:	00008d7c 	andeq	r8, r0, ip, ror sp
d001ed64:	ffffde93 			; <UNDEFINED> instruction: 0xffffde93

Disassembly of section .text.sidc_set_progress_callback:

d001ed68 <.text.sidc_set_progress_callback>:
d001ed68:	447b4b03 	ldrbtmi	r4, [fp], #-2819	; 0xfffff4fd
d001ed6c:	4b036018 	blmi	0xd00f6dd4
d001ed70:	6019447b 	andsvs	r4, r9, fp, ror r4
d001ed74:	bf004770 	svclt	0x00004770
d001ed78:	00053fd2 	ldrdeq	r3, [r5], -r2
d001ed7c:	00053fd0 	ldrdeq	r3, [r5], -r0

Disassembly of section .text.sidc_compile_project_stream:

d001ed80 <.text.sidc_compile_project_stream>:
d001ed80:	9d07b573 	cfstr32ls	mvfx11, [r7, #-460]	; 0xfffffe34
d001ed84:	b11d9c08 	tstlt	sp, r8, lsl #24
d001ed88:	b10e686e 	tstlt	lr, lr, ror #16
d001ed8c:	b94e68ae 	stmdblt	lr, {r1, r2, r3, r5, r7, fp, sp, lr}^
d001ed90:	447d4d0a 	ldrbtmi	r4, [sp], #-3338	; 0xfffff2f6
d001ed94:	cd0f3514 	cfstr32gt	mvfx3, [pc, #-80]	; 0xd001ed4c
d001ed98:	682bc40f 	stmdavs	fp!, {r0, r1, r2, r3, sl, lr, pc}
d001ed9c:	60232000 	eorvs	r2, r3, r0
d001eda0:	bd70b002 	ldcllt	0, cr11, [r0, #-8]!
d001eda4:	447e4e06 	ldrbtmi	r4, [lr], #-3590	; 0xfffff1fa
d001eda8:	94016035 	strls	r6, [r1], #-53	; 0xffffffcb
d001edac:	94009c06 	strls	r9, [r0], #-3078	; 0xfffff3fa
d001edb0:	f806f7fe 			; <UNDEFINED> instruction: 0xf806f7fe
d001edb4:	60332300 	eorsvs	r2, r3, r0, lsl #6
d001edb8:	bf00e7f2 	svclt	0x0000e7f2
d001edbc:	00003a1e 	andeq	r3, r0, lr, lsl sl
d001edc0:	00053faa 	andeq	r3, r5, sl, lsr #31

Disassembly of section .text.memset:

d0020efc <.text.memset>:
d0020efc:	b2c9b15a 	sbclt	fp, r9, #-2147483626	; 0x80000016
d0020f00:	b4104603 	ldrlt	r4, [r0], #-1539	; 0xfffff9fd
d0020f04:	461a1884 	ldrmi	r1, [sl], -r4, lsl #17
d0020f08:	42a33301 	adcmi	r3, r3, #67108864	; 0x4000000
d0020f0c:	d1fa7011 	mvnsle	r7, r1, lsl r0
d0020f10:	4b04f85d 	blmi	0xd015f08c
d0020f14:	47704770 			; <UNDEFINED> instruction: 0x47704770

Disassembly of section .text.memcpy:

d0020f18 <.text.memcpy>:
d0020f18:	4603b162 	strmi	fp, [r3], -r2, ror #2
d0020f1c:	1885b430 	stmne	r5, {r4, r5, sl, ip, sp, pc}
d0020f20:	461c780a 	ldrmi	r7, [ip], -sl, lsl #16
d0020f24:	31013301 	tstcc	r1, r1, lsl #6
d0020f28:	42abb2d2 	adcmi	fp, fp, #536870925	; 0x2000000d
d0020f2c:	d1f77022 	mvnsle	r7, r2, lsr #32
d0020f30:	4770bc30 			; <UNDEFINED> instruction: 0x4770bc30
d0020f34:	bf004770 	svclt	0x00004770

Disassembly of section .text.memcmp:

d0020f38 <.text.memcmp>:
d0020f38:	46034402 	strmi	r4, [r3], -r2, lsl #8
d0020f3c:	d0134290 	mulsle	r3, r0, r2
d0020f40:	e002b470 	and	fp, r2, r0, ror r4
d0020f44:	46034290 			; <UNDEFINED> instruction: 0x46034290
d0020f48:	f813d00b 			; <UNDEFINED> instruction: 0xf813d00b
d0020f4c:	f8115b01 			; <UNDEFINED> instruction: 0xf8115b01
d0020f50:	46184b01 	ldrmi	r4, [r8], -r1, lsl #22
d0020f54:	42a5b2ee 	adcmi	fp, r5, #-536870898	; 0xe000000e
d0020f58:	d0f3b2e3 	rscsle	fp, r3, r3, ror #5
d0020f5c:	bc701af0 			; <UNDEFINED> instruction: 0xbc701af0
d0020f60:	20004770 	andcs	r4, r0, r0, ror r7
d0020f64:	4770bc70 			; <UNDEFINED> instruction: 0x4770bc70
d0020f68:	47702000 	ldrbmi	r2, [r0, -r0]!

Disassembly of section .text.sb_f_fixed:

d0020f70 <.text.sb_f_fixed>:
d0020f70:	0b40eeb5 	bleq	0xd105ca4c
d0020f74:	4ff0e92d 	svcmi	0x00f0e92d
d0020f78:	fa10eef1 	blx	0xd045cb44
d0020f7c:	d0354606 	eorsle	r4, r5, r6, lsl #12
d0020f80:	6b04eeb2 	blvs	0xd015ca50
d0020f84:	eeb02400 	cdp	4, 11, cr2, cr0, cr0, {0}
d0020f88:	eeb47b40 	vcmp.f64	d7, d0
d0020f8c:	eef10bc6 	vsqrt.f64	d16, d6
d0020f90:	da22fa10 	ble	0xd08df7d8
d0020f94:	6b00eeb7 	blvs	0xd005ca78
d0020f98:	7bc6eeb4 	blvc	0xcf1dca70
d0020f9c:	fa10eef1 	blx	0xd045cb68
d0020fa0:	80a6f140 	adchi	pc, r6, r0, asr #2
d0020fa4:	5b04eeb2 	blpl	0xd015ca74
d0020fa8:	73a1f46f 			; <UNDEFINED> instruction: 0x73a1f46f
d0020fac:	eeb4e004 	cdp	0, 11, cr14, cr4, cr4, {0}
d0020fb0:	eef17bc6 	vsqrt.f64	d23, d6
d0020fb4:	d504fa10 	strle	pc, [r4, #-2576]	; 0xfffff5f0
d0020fb8:	ee273c01 	cdp	12, 2, cr3, cr7, cr1, {0}
d0020fbc:	429c7b05 	addsmi	r7, ip, #5120	; 0x1400
d0020fc0:	ea24daf5 	b	0xd0957b9c
d0020fc4:	ea6f73e4 	b	0xd1bfdf5c
d0020fc8:	459c0c01 	ldrmi	r0, [ip, #3073]	; 0xc01
d0020fcc:	2000dd16 	andcs	sp, r0, r6, lsl sp
d0020fd0:	8ff0e8bd 	svchi	0x00f0e8bd
d0020fd4:	7f9af5b4 	svcvc	0x009af5b4
d0020fd8:	ee87d0dc 	mcr	0, 4, sp, cr7, cr12, {6}
d0020fdc:	34017b06 	strcc	r7, [r1], #-2822	; 0xfffff4fa
d0020fe0:	7bc6eeb4 	blvc	0xcf1dcab8
d0020fe4:	fa10eef1 	blx	0xd045cbb0
d0020fe8:	e7d3daf4 			; <UNDEFINED> instruction: 0xe7d3daf4
d0020fec:	eeb02300 	cdp	3, 11, cr2, cr0, cr0, {0}
d0020ff0:	461c7b40 	ldrmi	r7, [ip], -r0, asr #22
d0020ff4:	0c01ea6f 			; <UNDEFINED> instruction: 0x0c01ea6f
d0020ff8:	dce8459c 	cfstr64le	mvdx4, [r8], #624	; 0x270
d0020ffc:	0b00f04f 	bleq	0xd005d140
d0021000:	5b04eeb2 	blpl	0xd015cad0
d0021004:	0902ea41 	stmdbeq	r2, {r0, r6, r9, fp, sp, lr, pc}
d0021008:	38fff10c 	ldmcc	pc!, {r2, r3, r8, ip, sp, lr, pc}^	; <UNPREDICTABLE>
d002100c:	43f74658 	mvnsmi	r4, #88, 12	; 0x5800000
d0021010:	0a30f04f 	beq	0xd0c5d154
d0021014:	4b38ed9f 	blmi	0xd0e5c698
d0021018:	0b40eeb5 	bleq	0xd105caf4
d002101c:	fa10eef1 	blx	0xd045cbe8
d0021020:	42a3d030 	adcmi	sp, r3, #48	; 0x30
d0021024:	eefddc2e 	cdp	12, 15, cr13, cr13, cr14, {1}
d0021028:	f10b6bc7 			; <UNDEFINED> instruction: 0xf10b6bc7
d002102c:	ee160b01 	vnmls.f64	d0, d6, d1
d0021030:	ee161a90 	vmov	r1, s13
d0021034:	29092a90 	stmdbcs	r9, {r4, r7, r9, fp, sp}
d0021038:	2209bfa8 	andcs	fp, r9, #168, 30	; 0x2a0
d002103c:	0f11f1bb 	svceq	0x0011f1bb
d0021040:	72e2ea22 	rscvc	lr, r2, #139264	; 0x22000
d0021044:	2a90ee06 	bcs	0xce45c864
d0021048:	6be6eeb8 	blvs	0xcf9dcb30
d002104c:	7b46ee37 	blvc	0xd11dc930
d0021050:	7b05ee27 	blvc	0xd019c8f4
d0021054:	459cdc16 	ldrmi	sp, [ip, #3094]	; 0xc16
d0021058:	3230d018 	eorscc	sp, r0, #24
d002105c:	5432b2d2 	ldrtpl	fp, [r2], #-722	; 0xfffffd2e
d0021060:	3b013001 	blcc	0xd006d06c
d0021064:	d0b34543 	adcsle	r4, r3, r3, asr #10
d0021068:	d1d51c59 	bicsle	r1, r5, r9, asr ip
d002106c:	0f00f1b9 	svceq	0x0000f1b9
d0021070:	eeb5d0d2 	mrc	0, 5, sp, cr5, cr2, {6}
d0021074:	f04f0b40 			; <UNDEFINED> instruction: 0xf04f0b40
d0021078:	5432022e 	ldrtpl	r0, [r2], #-558	; 0xfffffdd2
d002107c:	eef13001 	cdp	0, 15, cr3, cr1, cr1, {0}
d0021080:	d1cefa10 	bicle	pc, lr, r0, lsl sl	; <UNPREDICTABLE>
d0021084:	d0ec459c 	smlalle	r4, ip, ip, r5
d0021088:	e7e82230 			; <UNDEFINED> instruction: 0xe7e82230
d002108c:	dd1e2905 	vldrle.16	s4, [lr, #-10]	; <UNPREDICTABLE>
d0021090:	dd172800 	ldcle	8, cr2, [r7, #-0]
d0021094:	0e00eb06 	vmlaeq.f64	d14, d0, d6
d0021098:	f8124672 			; <UNDEFINED> instruction: 0xf8124672
d002109c:	292e1d01 	stmdbcs	lr!, {r0, r8, sl, fp, ip}
d00210a0:	0502eb07 	streq	lr, [r2, #-2823]	; 0xfffff4f9
d00210a4:	2938d003 	ldmdbcs	r8!, {r0, r1, ip, lr, pc}
d00210a8:	f882d91f 			; <UNDEFINED> instruction: 0xf882d91f
d00210ac:	3501a000 	strcc	sl, [r1, #-0]
d00210b0:	2800d1f3 	stmdacs	r0, {r0, r1, r4, r5, r6, r7, r8, ip, lr, pc}
d00210b4:	4672dd06 	ldrbtmi	sp, [r2], -r6, lsl #26
d00210b8:	1c01f812 	stcne	8, cr15, [r1], {18}
d00210bc:	1901f802 	stmdbne	r1, {r1, fp, ip, sp, lr, pc}
d00210c0:	d1f94296 			; <UNDEFINED> instruction: 0xd1f94296
d00210c4:	0231f04f 	eorseq	pc, r1, #79	; 0x4f
d00210c8:	70323001 	eorsvc	r3, r2, r1
d00210cc:	d1c8e7c9 	bicle	lr, r8, r9, asr #15
d00210d0:	7bc4eeb4 	blvc	0xcf15cba8
d00210d4:	fa10eef1 	blx	0xd045cca0
d00210d8:	2800dcda 	stmdacs	r0, {r1, r3, r4, r6, r7, sl, fp, ip, lr, pc}
d00210dc:	1832d0c1 	ldmdane	r2!, {r0, r6, r7, ip, lr, pc}
d00210e0:	2c01f812 	stccs	8, cr15, [r1], {18}
d00210e4:	d5bc07d2 	ldrle	r0, [ip, #2002]!	; 0x7d2
d00210e8:	3101e7d2 	ldrdcc	lr, [r1, -r2]
d00210ec:	e7b87011 			; <UNDEFINED> instruction: 0xe7b87011
d00210f0:	e77f4623 	ldrb	r4, [pc, -r3, lsr #12]!
d00210f4:	8000f3af 	andhi	pc, r0, pc, lsr #7
d00210f8:	812dea11 			; <UNDEFINED> instruction: 0x812dea11
d00210fc:	3d719799 	ldclcc	7, cr9, [r1, #-612]!	; 0xfffffd9c

Disassembly of section .text.sb_f_exponent:

d0021100 <.text.sb_f_exponent>:
d0021100:	0b40eeb5 	bleq	0xd105cbdc
d0021104:	4ff0e92d 	svcmi	0x00f0e92d
d0021108:	fa10eef1 	blx	0xd045ccd4
d002110c:	d0344607 	eorsle	r4, r4, r7, lsl #12
d0021110:	6b04eeb2 	blvs	0xd015cbe0
d0021114:	0bc6eeb4 	bleq	0xcf1dcbec
d0021118:	fa10eef1 	blx	0xd045cce4
d002111c:	80cef2c0 	sbchi	pc, lr, r0, asr #5
d0021120:	7b40eeb0 	blvc	0xd105cbe8
d0021124:	e0022400 	and	r2, r2, r0, lsl #8
d0021128:	7f9af5b4 	svcvc	0x009af5b4
d002112c:	ee87d007 	cdp	0, 8, cr13, cr7, cr7, {0}
d0021130:	34017b06 	strcc	r7, [r1], #-2822	; 0xfffff4fa
d0021134:	7bc6eeb4 	blvc	0xcf1dcc0c
d0021138:	fa10eef1 	blx	0xd045cd04
d002113c:	eeb7daf4 			; <UNDEFINED> instruction: 0xeeb7daf4
d0021140:	eeb46b00 	vmov.f64	d6, #64	; 0x3e000000  0.125
d0021144:	eef17bc6 	vsqrt.f64	d23, d6
d0021148:	d519fa10 	ldrle	pc, [r9, #-2576]	; 0xfffff5f0
d002114c:	5b04eeb2 	blpl	0xd015cc1c
d0021150:	70a1f46f 	adcvc	pc, r1, pc, ror #8
d0021154:	eeb4e004 	cdp	0, 11, cr14, cr4, cr4, {0}
d0021158:	eef17bc6 	vsqrt.f64	d23, d6
d002115c:	d50ffa10 	strle	pc, [pc, #-2576]	; 0xd0020754
d0021160:	ee273c01 	cdp	12, 2, cr3, cr7, cr1, {0}
d0021164:	42847b05 	addmi	r7, r4, #5120	; 0x1400
d0021168:	f111daf5 			; <UNDEFINED> instruction: 0xf111daf5
d002116c:	d50a0e01 	strle	r0, [sl, #-3585]	; 0xfffff1ff
d0021170:	2102463e 	tstcs	r2, lr, lsr r6
d0021174:	22002501 	andcs	r2, r0, #4194304	; 0x400000
d0021178:	eeb0e062 	cdp	0, 11, cr14, cr0, cr2, {3}
d002117c:	24007b40 	strcs	r7, [r0], #-2880	; 0xfffff4c0
d0021180:	0e01f111 	mcreq	1, 0, pc, cr1, cr1, {0}	; <UNPREDICTABLE>
d0021184:	2500d4f4 	strcs	sp, [r0, #-1268]	; 0xfffffb0c
d0021188:	5b04eeb2 	blpl	0xd015cc58
d002118c:	0902ea41 	stmdbeq	r2, {r0, r6, r9, fp, sp, lr, pc}
d0021190:	462a1c88 	strtmi	r1, [sl], -r8, lsl #25
d0021194:	0807ea6f 	stmdaeq	r7, {r0, r1, r2, r3, r5, r6, r9, fp, sp, lr, pc}
d0021198:	0a30f04f 	beq	0xd0c5d2dc
d002119c:	0b2ef04f 	bleq	0xd0bdd2e0
d00211a0:	4b49ed9f 	blmi	0xd129c824
d00211a4:	0b40eeb5 	bleq	0xd105cc80
d00211a8:	fa10eef1 	blx	0xd045cd74
d00211ac:	4575d114 	ldrbmi	sp, [r5, #-276]!	; 0xfffffeec
d00211b0:	2130d002 	teqcs	r0, r2
d00211b4:	320154b9 	andcc	r5, r1, #-1191182336	; 0xb9000000
d00211b8:	42853501 	addmi	r3, r5, #4194304	; 0x400000
d00211bc:	2d01d03d 	stccs	0, cr13, [r1, #-244]	; 0xffffff0c
d00211c0:	f1b9d1f0 			; <UNDEFINED> instruction: 0xf1b9d1f0
d00211c4:	d0ed0f00 	rscle	r0, sp, r0, lsl #30
d00211c8:	0b40eeb5 	bleq	0xd105cca4
d00211cc:	b002f807 	andlt	pc, r2, r7, lsl #16
d00211d0:	eef13201 	cdp	2, 15, cr3, cr1, cr1, {0}
d00211d4:	d0eafa10 	rscle	pc, sl, r0, lsl sl	; <UNPREDICTABLE>
d00211d8:	6bc7eefd 	blvs	0xcf21cdd4
d00211dc:	6a90ee16 	bvs	0xce45ca3c
d00211e0:	1a90ee16 	bne	0xce45ca40
d00211e4:	bfa82e09 	svclt	0x00a82e09
d00211e8:	45752109 	ldrbmi	r2, [r5, #-265]!	; 0xfffffef7
d00211ec:	71e1ea21 	mvnvc	lr, r1, lsr #20
d00211f0:	1a90ee06 	bne	0xce45ca10
d00211f4:	6be6eeb8 	blvs	0xcf9dccdc
d00211f8:	7b46ee37 	blvc	0xd11dcadc
d00211fc:	7b05ee27 	blvc	0xd019caa0
d0021200:	3130d002 	teqcc	r0, r2
d0021204:	e7d5b2c9 	ldrb	fp, [r5, r9, asr #5]
d0021208:	dd462e05 	stclle	14, cr2, [r6, #-20]	; 0xffffffec
d002120c:	dd0d2a00 	vstrle	s4, [sp, #-0]
d0021210:	f81118b9 			; <UNDEFINED> instruction: 0xf81118b9
d0021214:	2e2e6d01 	cdpcs	13, 2, cr6, cr14, cr1, {0}
d0021218:	0c01eb08 			; <UNDEFINED> instruction: 0x0c01eb08
d002121c:	2e38d003 	cdpcs	0, 3, cr13, cr8, cr3, {0}
d0021220:	f881d949 			; <UNDEFINED> instruction: 0xf881d949
d0021224:	f1bca000 			; <UNDEFINED> instruction: 0xf1bca000
d0021228:	d1f23fff 	ldrshle	r3, [r2, #255]!	; 0xff
d002122c:	f04f3501 			; <UNDEFINED> instruction: 0xf04f3501
d0021230:	34010131 	strcc	r0, [r1], #-305	; 0xfffffecf
d0021234:	70394285 	eorsvc	r4, r9, r5, lsl #5
d0021238:	18bed1c1 	ldmne	lr!, {r0, r6, r7, r8, ip, lr, pc}
d002123c:	1c911c55 	ldcne	12, cr1, [r1], {85}	; 0x55
d0021240:	bf142b00 	svclt	0x00142b00
d0021244:	20652045 	rsbcs	r2, r5, r5, asr #32
d0021248:	70302c00 	eorsvc	r2, r0, r0, lsl #24
d002124c:	232dbfb4 			; <UNDEFINED> instruction: 0x232dbfb4
d0021250:	2c00232b 	stccs	3, cr2, [r0], {43}	; 0x2b
d0021254:	bfb8557b 	svclt	0x00b8557b
d0021258:	2c634264 	sfmcs	f4, 2, [r3], #-400	; 0xfffffe70
d002125c:	4b1cdd06 	blmi	0xd075867c
d0021260:	0304fba3 	movweq	pc, #19363	; 0x4ba3	; <UNPREDICTABLE>
d0021264:	3330095b 	teqcc	r0, #1490944	; 0x16c000
d0021268:	1cd1547b 	cfldrdne	mvd5, [r1], {123}	; 0x7b
d002126c:	187d4a19 	ldmdane	sp!, {r0, r3, r4, r9, fp, lr}^
d0021270:	0304fba2 	movweq	pc, #19362	; 0x4ba2	; <UNPREDICTABLE>
d0021274:	08db1c88 	ldmeq	fp, {r3, r7, sl, fp, ip}^
d0021278:	6203fba2 	andvs	pc, r3, #165888	; 0x28800
d002127c:	0683eb03 	streq	lr, [r3], r3, lsl #22
d0021280:	eba408d2 	bl	0xce9235d0
d0021284:	eb020446 	bl	0xd00a23a4
d0021288:	34300282 	ldrtcc	r0, [r0], #-642	; 0xfffffd7e
d002128c:	0342eba3 	movteq	lr, #11171	; 0x2ba3
d0021290:	547b3330 	ldrbtpl	r3, [fp], #-816	; 0xfffffcd0
d0021294:	e8bd706c 	pop	{r2, r3, r5, r6, ip, sp, lr}
d0021298:	d18d8ff0 	strdle	r8, [sp, r0]
d002129c:	7bc4eeb4 	blvc	0xcf15cd74
d00212a0:	fa10eef1 	blx	0xd045ce6c
d00212a4:	2a00dcb2 	bcs	0xd0058574
d00212a8:	18b9d086 	ldmne	r9!, {r1, r2, r7, ip, lr, pc}
d00212ac:	1c01f811 	stcne	8, cr15, [r1], {17}
d00212b0:	d58107c9 	strle	r0, [r1, #1993]	; 0x7c9
d00212b4:	3601e7aa 	strcc	lr, [r1], -sl, lsr #15
d00212b8:	e77d700e 	ldrb	r7, [sp, -lr]!
d00212bc:	7b40eeb0 	blvc	0xd105cd84
d00212c0:	e73c2400 	ldr	r2, [ip, -r0, lsl #8]!
d00212c4:	8000f3af 	andhi	pc, r0, pc, lsr #7
d00212c8:	812dea11 			; <UNDEFINED> instruction: 0x812dea11
d00212cc:	3d719799 	ldclcc	7, cr9, [r1, #-612]!	; 0xfffffd9c
d00212d0:	51eb851f 	mvnpl	r8, pc, lsl r5
d00212d4:	cccccccd 	stclgt	12, cr12, [ip], {205}	; 0xcd

Disassembly of section .text.sb_flush.part.0:

d00212d8 <.text.sb_flush.part.0>:
d00212d8:	2090f8d0 			; <UNDEFINED> instruction: 0x2090f8d0
d00212dc:	4b07b16a 	blmi	0xd020d88c
d00212e0:	0110f100 	tsteq	r0, r0, lsl #2	; <UNPREDICTABLE>
d00212e4:	681b689b 	ldmdavs	fp, {r0, r1, r3, r4, r7, fp, sp, lr}
d00212e8:	685bb510 	ldmdavs	fp, {r4, r8, sl, ip, sp, pc}^
d00212ec:	20004604 	andcs	r4, r0, r4, lsl #12
d00212f0:	23004798 	movwcs	r4, #1944	; 0x798
d00212f4:	3090f8c4 	addscc	pc, r0, r4, asr #17
d00212f8:	4770bd10 			; <UNDEFINED> instruction: 0x4770bd10
d00212fc:	2001f000 	andcs	pc, r1, r0

Disassembly of section .text.sb_char:

d0021300 <.text.sb_char>:
d0021300:	b51068c3 	ldrlt	r6, [r0, #-2243]	; 0xfffff73d
d0021304:	b1834604 	orrlt	r4, r3, r4, lsl #12
d0021308:	3090f8d0 			; <UNDEFINED> instruction: 0x3090f8d0
d002130c:	44031c5a 	strmi	r1, [r3], #-3162	; 0xfffff3a6
d0021310:	f8c02a80 			; <UNDEFINED> instruction: 0xf8c02a80
d0021314:	74192090 	ldrvc	r2, [r9], #-144	; 0xffffff70
d0021318:	68a3d013 	stmiavs	r3!, {r0, r1, r4, ip, lr, pc}
d002131c:	4200f06f 	andmi	pc, r0, #111	; 0x6f
d0021320:	d2014293 	andle	r4, r1, #805306377	; 0x30000009
d0021324:	60a33301 	adcvs	r3, r3, r1, lsl #6
d0021328:	6800bd10 	stmdavs	r0, {r4, r8, sl, fp, ip, sp, pc}
d002132c:	d0f42800 	rscsle	r2, r4, r0, lsl #16
d0021330:	68a36862 	stmiavs	r3!, {r1, r5, r6, fp, sp, lr}
d0021334:	bf182a00 	svclt	0x00182a00
d0021338:	42933a01 	addsmi	r3, r3, #4096	; 0x1000
d002133c:	54c1d2ee 	strbpl	sp, [r1], #750	; 0x2ee
d0021340:	f7ffe7eb 			; <UNDEFINED> instruction: 0xf7ffe7eb
d0021344:	68a3ffc9 	stmiavs	r3!, {r0, r3, r6, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0021348:	bf00e7e8 	svclt	0x0000e7e8

Disassembly of section .text.sb_number:

d0021360 <.text.sb_number>:
d0021360:	4ff0e92d 	svcmi	0x00f0e92d
d0021364:	8b02ed2d 	blhi	0xd00dc820
d0021368:	ee08b09b 	mcr	0, 0, fp, cr8, cr11, {4}
d002136c:	93070a10 	movwls	r0, #31248	; 0x7a10
d0021370:	92069b2b 	andls	r9, r6, #44032	; 0xac00
d0021374:	d13e2b00 	teqle	lr, r0, lsl #22
d0021378:	e9dd4bbf 	ldmib	sp, {r0, r1, r2, r3, r4, r5, r7, r8, r9, fp, lr}^
d002137c:	447b1206 	ldrbtmi	r1, [fp], #-518	; 0xfffffdfa
d0021380:	460b9305 	strmi	r9, [fp], -r5, lsl #6
d0021384:	d13e4313 	teqle	lr, r3, lsl r3
d0021388:	9a2a9b2a 	bls	0xd0ac8038
d002138c:	bf183b00 	svclt	0x00183b00
d0021390:	2a002301 	bcs	0xd0029f9c
d0021394:	9303d137 	movwls	sp, #12599	; 0x3137
d0021398:	2b009b27 	blcs	0xd004803c
d002139c:	9b28d179 	blls	0xd0a55988
d00213a0:	f1000759 			; <UNDEFINED> instruction: 0xf1000759
d00213a4:	ea4f8101 	b	0xd14017b0
d00213a8:	9a2c0983 	bls	0xd0b239bc
d00213ac:	1a40f3c9 	bne	0xd105e2d8
d00213b0:	0920f009 	stmdbeq	r0!, {r0, r3, ip, sp, lr, pc}
d00213b4:	2a004653 	bcs	0xd0032d08
d00213b8:	9a26d072 	bls	0xd09d5588
d00213bc:	f0002a10 			; <UNDEFINED> instruction: 0xf0002a10
d00213c0:	9a2680f8 	bls	0xd09c17a8
d00213c4:	f0002a02 			; <UNDEFINED> instruction: 0xf0002a02
d00213c8:	9a268144 	bls	0xd09c18e0
d00213cc:	9a032a08 	bls	0xd00ebbf4
d00213d0:	8122f000 	msrhi	CPSR_x, r0
d00213d4:	2600992a 	strcs	r9, [r0], -sl, lsr #18
d00213d8:	82a0f8df 	adchi	pc, r0, #14614528	; 0xdf0000
d00213dc:	44f84291 	ldrbtmi	r4, [r8], #657	; 0x291
d00213e0:	9a03dc69 	bls	0xd011858c
d00213e4:	19942700 	ldmibne	r4, {r8, r9, sl, sp}
d00213e8:	44239a29 	strtmi	r9, [r3], #-2601	; 0xfffff5d7
d00213ec:	f0c04293 			; <UNDEFINED> instruction: 0xf0c04293
d00213f0:	463c80e8 	ldrtmi	r8, [ip], -r8, ror #1
d00213f4:	4ba2e0e7 	blmi	0xce8d9798
d00213f8:	1206e9dd 	andne	lr, r6, #3620864	; 0x374000
d00213fc:	9305447b 	movwls	r4, #21627	; 0x547b
d0021400:	4313460b 	tstmi	r3, #11534336	; 0xb00000
d0021404:	ab09d0c0 	blge	0xd029570c
d0021408:	26012200 	strcs	r2, [r1], -r0, lsl #4
d002140c:	e9dd9304 	ldmib	sp, {r2, r8, r9, ip, pc}^
d0021410:	469b3406 	ldrmi	r3, [fp], r6, lsl #8
d0021414:	46272300 	strtmi	r2, [r7], -r0, lsl #6
d0021418:	9b269303 	blls	0xd09c602c
d002141c:	e9cd4619 	stmib	sp, {r0, r3, r4, r9, sl, lr}^
d0021420:	23001200 	movwcs	r1, #512	; 0x200
d0021424:	0ffa203f 	svceq	0x00fa203f
d0021428:	b008f8cd 	andlt	pc, r8, sp, asr #17
d002142c:	469a4699 			; <UNDEFINED> instruction: 0x469a4699
d0021430:	99023801 	stmdbls	r2, {r0, fp, ip, sp}
d0021434:	0420f1c0 	strteq	pc, [r0], #-448	; 0xfffffe40
d0021438:	0520f1a0 	streq	pc, [r0, #-416]!	; 0xfffffe60
d002143c:	f1b040c1 			; <UNDEFINED> instruction: 0xf1b040c1
d0021440:	fa073fff 	blx	0xd01f1444
d0021444:	fa27fe04 	blx	0xd0a20c5c
d0021448:	fa26fc05 	blx	0xd09e0464
d002144c:	fa06f404 	blx	0xd01de464
d0021450:	ea41f505 	b	0xd109e86c
d0021454:	fa06010e 	blx	0xd01a1894
d0021458:	ea44f800 	b	0xd115f460
d002145c:	ea410405 	b	0xd1062478
d0021460:	d072010c 	rsbsle	r0, r2, ip, lsl #2
d0021464:	f0011895 			; <UNDEFINED> instruction: 0xf0011895
d0021468:	eb430101 	bl	0xd10e1874
d002146c:	ea410c03 	b	0xd1064480
d0021470:	46630205 	strbtmi	r0, [r3], -r5, lsl #4
d0021474:	bc00e9dd 			; <UNDEFINED> instruction: 0xbc00e9dd
d0021478:	bf084563 	svclt	0x00084563
d002147c:	d3d7455a 	bicsle	r4, r7, #377487360	; 0x16800000
d0021480:	020bebb2 	andeq	lr, fp, #182272	; 0x2c800
d0021484:	0909ea48 	stmdbeq	r9, {r3, r6, r9, fp, sp, lr, pc}
d0021488:	0a0aea44 	beq	0xd02dbda0
d002148c:	030ceb63 	movweq	lr, #52067	; 0xcb63
d0021490:	2301e7ce 	movwcs	lr, #6094	; 0x17ce
d0021494:	092df04f 	pusheq	{r0, r1, r2, r3, r6, ip, sp, lr, pc}
d0021498:	9a2c469a 	bls	0xd0b32f08
d002149c:	d18c2a00 	orrle	r2, ip, r0, lsl #20
d00214a0:	f0129a28 			; <UNDEFINED> instruction: 0xf0129a28
d00214a4:	d16a0610 	cmnle	sl, r0, lsl r6
d00214a8:	81d8f8df 	ldrsbhi	pc, [r8, #143]	; 0x8f	; <UNPREDICTABLE>
d00214ac:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d00214b0:	4291992a 	addsmi	r9, r1, #688128	; 0xa8000
d00214b4:	9903dd95 	stmdbls	r3, {r0, r2, r4, r7, r8, sl, fp, ip, lr, pc}
d00214b8:	198a982a 	stmibne	sl, {r1, r3, r5, fp, ip, pc}
d00214bc:	44131a47 	ldrmi	r1, [r3], #-2631	; 0xfffff5b9
d00214c0:	443b9a29 	ldrtmi	r9, [fp], #-2601	; 0xfffff5d7
d00214c4:	d87c429a 	ldmdale	ip!, {r1, r3, r4, r7, r9, lr}^
d00214c8:	24009b28 	strcs	r9, [r0], #-2856	; 0xfffff4d8
d00214cc:	0501f003 	streq	pc, [r1, #-3]
d00214d0:	0f00f1ba 	svceq	0x0000f1ba
d00214d4:	b16ed14d 	cmnlt	lr, sp, asr #2
d00214d8:	1000f898 	mulne	r0, r8, r8
d00214dc:	0a10ee18 	beq	0xd045cd44
d00214e0:	ff0ef7ff 			; <UNDEFINED> instruction: 0xff0ef7ff
d00214e4:	d1052e02 	tstle	r5, r2, lsl #28
d00214e8:	1001f898 	mulne	r1, r8, r8
d00214ec:	0a10ee18 	beq	0xd045cd54
d00214f0:	ff06f7ff 			; <UNDEFINED> instruction: 0xff06f7ff
d00214f4:	b1471e7e 	hvclt	29166	; 0x71ee
d00214f8:	7a10ee18 	bvc	0xd045cd60
d00214fc:	21303e01 	teqcs	r0, r1, lsl #28
d0021500:	f7ff4638 			; <UNDEFINED> instruction: 0xf7ff4638
d0021504:	1c72fefd 	ldclne	14, cr15, [r2], #-1012	; 0xfffffc0c
d0021508:	9b03d1f8 	blls	0xd0115cf0
d002150c:	af09b163 	svcge	0x0009b163
d0021510:	ee189b03 	vnmls.f64	d9, d8, d3
d0021514:	443b8a10 	ldrtmi	r8, [fp], #-2576	; 0xfffff5f0
d0021518:	f816461e 			; <UNDEFINED> instruction: 0xf816461e
d002151c:	46401d01 	strbmi	r1, [r0], -r1, lsl #26
d0021520:	feeef7ff 	mcr2	7, 7, pc, cr14, cr15, {7}	; <UNPREDICTABLE>
d0021524:	d1f842b7 	ldrhle	r4, [r8, #39]!	; 0x27
d0021528:	1e65b155 	mcrne	1, 3, fp, cr5, cr5, {2}
d002152c:	ee18b144 	mnfem	f3, f4
d0021530:	3d014a10 	vstrcc	s8, [r1, #-64]	; 0xffffffc0
d0021534:	46202120 	strtmi	r2, [r0], -r0, lsr #2
d0021538:	fee2f7ff 	mcr2	7, 7, pc, cr2, cr15, {7}	; <UNPREDICTABLE>
d002153c:	d1f81c6b 	mvnsle	r1, fp, ror #24
d0021540:	ecbdb01b 	ldc	0, cr11, [sp], #108	; 0x6c
d0021544:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d0021548:	99058ff0 	stmdbls	r5, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
d002154c:	9903440a 	stmdbls	r3, {r1, r3, sl, lr}
d0021550:	31017813 	tstcc	r1, r3, lsl r8
d0021554:	91039a04 	tstls	r3, r4, lsl #20
d0021558:	3b01f802 	blcc	0xd009f568
d002155c:	030aea59 	movweq	lr, #43609	; 0xaa59
d0021560:	f43f9204 			; <UNDEFINED> instruction: 0xf43f9204
d0021564:	2940af19 	stmdbcs	r0, {r0, r3, r4, r8, r9, sl, fp, sp, pc}^
d0021568:	af16f63f 	svcge	0x0016f63f
d002156c:	465746cb 	ldrbmi	r4, [r7], -fp, asr #13
d0021570:	4649e757 			; <UNDEFINED> instruction: 0x4649e757
d0021574:	0a10ee18 	beq	0xd045cddc
d0021578:	fec2f7ff 	mcr2	7, 6, pc, cr2, cr15, {7}	; <UNPREDICTABLE>
d002157c:	e9dde7ab 	ldmib	sp, {r0, r1, r3, r5, r7, r8, r9, sl, sp, lr, pc}^
d0021580:	430a1206 	movwmi	r1, #41478	; 0xa206
d0021584:	af19f47f 	svcge	0x0019f47f
d0021588:	2a089a26 	bcs	0xd0247e28
d002158c:	9a03d167 	bls	0xd0115b30
d0021590:	d1642a00 	cmnle	r4, r0, lsl #20
d0021594:	21302201 	teqcs	r0, r1, lsl #4
d0021598:	80ecf8df 	ldrdhi	pc, [ip], #143	; 0x8f	; <UNPREDICTABLE>
d002159c:	44f89e2c 	ldrbtmi	r9, [r8], #3628	; 0xe2c
d00215a0:	f88d9203 			; <UNDEFINED> instruction: 0xf88d9203
d00215a4:	e7831024 	str	r1, [r3, r4, lsr #32]
d00215a8:	f04f2301 			; <UNDEFINED> instruction: 0xf04f2301
d00215ac:	469a092b 	ldrmi	r0, [sl], fp, lsr #18
d00215b0:	9a2be773 	bls	0xd0b1b384
d00215b4:	f8dfb352 			; <UNDEFINED> instruction: 0xf8dfb352
d00215b8:	260280d4 			; <UNDEFINED> instruction: 0x260280d4
d00215bc:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d00215c0:	9a29e776 	bls	0xd0a9b3a0
d00215c4:	9b281ad4 	blls	0xd0a2811c
d00215c8:	0303f003 	movweq	pc, #12291	; 0x3003	; <UNPREDICTABLE>
d00215cc:	d1022b02 	tstle	r2, r2, lsl #22
d00215d0:	2b009b2a 	blcs	0xd0048280
d00215d4:	9b28db33 	blls	0xd0a582a8
d00215d8:	0501f013 	streq	pc, [r1, #-19]	; 0xffffffed
d00215dc:	af78f47f 	svcge	0x0078f47f
d00215e0:	3bfff104 	blcc	0xd001d9f8
d00215e4:	d0402c00 	suble	r2, r0, r0, lsl #24
d00215e8:	ee189402 	cfmuls	mvf9, mvf8, mvf2
d00215ec:	f10b4a10 			; <UNDEFINED> instruction: 0xf10b4a10
d00215f0:	21203bff 	strdcs	r3, [r0, -pc]!
d00215f4:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d00215f8:	f1bbfe83 			; <UNDEFINED> instruction: 0xf1bbfe83
d00215fc:	d1f63fff 	ldrshle	r3, [r6, #255]!	; 0xff
d0021600:	f1ba9c02 			; <UNDEFINED> instruction: 0xf1ba9c02
d0021604:	f43f0f00 			; <UNDEFINED> instruction: 0xf43f0f00
d0021608:	e7b2af66 	ldr	sl, [r2, r6, ror #30]!
d002160c:	8080f8df 	ldrdhi	pc, [r0], pc	; <UNPREDICTABLE>
d0021610:	9a032602 	bls	0xd00eae20
d0021614:	e74b44f8 			; <UNDEFINED> instruction: 0xe74b44f8
d0021618:	a91ab15a 	ldmdbge	sl, {r1, r3, r4, r6, r8, ip, sp, pc}
d002161c:	f812188a 			; <UNDEFINED> instruction: 0xf812188a
d0021620:	2a302c45 	bcs	0xd0c2c73c
d0021624:	f8dfd105 			; <UNDEFINED> instruction: 0xf8dfd105
d0021628:	2600806c 	strcs	r8, [r0], -ip, rrx
d002162c:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d0021630:	f8dfe73e 			; <UNDEFINED> instruction: 0xf8dfe73e
d0021634:	26018064 	strcs	r8, [r1], -r4, rrx
d0021638:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d002163c:	9b28e738 	blls	0xd0a5b324
d0021640:	24004427 	strcs	r4, [r0], #-1063	; 0xfffffbd9
d0021644:	0501f003 	streq	pc, [r1, #-3]
d0021648:	0f00f1ba 	svceq	0x0000f1ba
d002164c:	af43f43f 	svcge	0x0043f43f
d0021650:	f8dfe78f 			; <UNDEFINED> instruction: 0xf8dfe78f
d0021654:	46168048 	ldrmi	r8, [r6], -r8, asr #32
d0021658:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d002165c:	f8dfe728 			; <UNDEFINED> instruction: 0xf8dfe728
d0021660:	26008040 	strcs	r8, [r0], -r0, asr #32
d0021664:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d0021668:	4625e722 	strtmi	lr, [r5], -r2, lsr #14
d002166c:	0f00f1ba 	svceq	0x0000f1ba
d0021670:	af31f43f 	svcge	0x0031f43f
d0021674:	bf00e77d 	svclt	0x0000e77d
d0021678:	0000136a 	andeq	r1, r0, sl, ror #6
d002167c:	ffffff6e 			; <UNDEFINED> instruction: 0xffffff6e
d0021680:	000012d8 	ldrdeq	r1, [r0], -r8
d0021684:	fffffe9e 			; <UNDEFINED> instruction: 0xfffffe9e
d0021688:	fffffdae 			; <UNDEFINED> instruction: 0xfffffdae
d002168c:	fffffd8a 			; <UNDEFINED> instruction: 0xfffffd8a
d0021690:	fffffd3c 			; <UNDEFINED> instruction: 0xfffffd3c
d0021694:	fffffd1e 			; <UNDEFINED> instruction: 0xfffffd1e
d0021698:	fffffd1a 			; <UNDEFINED> instruction: 0xfffffd1a
d002169c:	fffffcfe 			; <UNDEFINED> instruction: 0xfffffcfe
d00216a0:	fffffce6 			; <UNDEFINED> instruction: 0xfffffce6

Disassembly of section .text.sb_float:

d00216bc <.text.sb_float>:
d00216bc:	4ff0e92d 	svcmi	0x00f0e92d
d00216c0:	bb10ec5c 	bllt	0xd045c838
d00216c4:	461eb0df 			; <UNDEFINED> instruction: 0x461eb0df
d00216c8:	73dcea5f 	bicsvc	lr, ip, #389120	; 0x5f000
d00216cc:	460446e0 	strmi	r4, [r4], -r0, ror #13
d00216d0:	4615468a 	ldrmi	r4, [r5], -sl, lsl #13
d00216d4:	9a10ee10 	bls	0xd045cf1c
d00216d8:	ed8d9304 	stc	3, cr9, [sp, #16]
d00216dc:	d10a0b00 	tstle	sl, r0, lsl #22
d00216e0:	f1000750 			; <UNDEFINED> instruction: 0xf1000750
d00216e4:	009380cb 	addseq	r8, r3, fp, asr #1
d00216e8:	1740f3c3 	strbne	pc, [r0, -r3, asr #7]	; <UNPREDICTABLE>
d00216ec:	0320f003 	wfieq
d00216f0:	930346bb 	movwls	r4, #14011	; 0x36bb
d00216f4:	2701e003 	strcs	lr, [r1, -r3]
d00216f8:	46bb232d 	ldrtmi	r2, [fp], sp, lsr #6
d00216fc:	f04f9303 			; <UNDEFINED> instruction: 0xf04f9303
d0021700:	21000c00 	tstcs	r0, r0, lsl #24
d0021704:	70fff240 	rscsvc	pc, pc, r0, asr #4
d0021708:	520af3c8 	andpl	pc, sl, #200, 6	; 0x20000003
d002170c:	f1aa458c 			; <UNDEFINED> instruction: 0xf1aa458c
d0021710:	bf080e41 	svclt	0x00080e41
d0021714:	fa5f4282 	blx	0xd17f2124
d0021718:	d03efe8e 	eorsle	pc, lr, lr, lsl #29
d002171c:	2b099b68 	blcs	0xd02884c4
d0021720:	4afcdd4b 	bmi	0xcff58c54
d0021724:	0918f10d 	ldmdbeq	r8, {r0, r2, r3, r8, ip, sp, lr, pc}
d0021728:	237046e0 	cmncs	r0, #224, 12	; 0xe000000
d002172c:	4649447a 			; <UNDEFINED> instruction: 0x4649447a
d0021730:	3201203c 	andcc	r2, r1, #60	; 0x3c
d0021734:	4618e002 	ldrmi	lr, [r8], -r2
d0021738:	3f01f812 	svccc	0x0001f812
d002173c:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d0021740:	0b01f801 	bleq	0xd009f74c
d0021744:	d1f62b00 	mvnsle	r2, r0, lsl #22
d0021748:	020beb08 	andeq	lr, fp, #8, 22	; 0x2000
d002174c:	42b22301 	adcsmi	r2, r2, #67108864	; 0x4000000
d0021750:	8099f0c0 	addshi	pc, r9, r0, asr #1
d0021754:	f0052600 			; <UNDEFINED> instruction: 0xf0052600
d0021758:	2a020203 	bcs	0xd00a1f6c
d002175c:	2b00d102 	blcs	0xd0055b6c
d0021760:	8093f040 	addshi	pc, r3, r0, asr #32
d0021764:	0501f015 	streq	pc, [r1, #-21]	; 0xffffffeb
d0021768:	80bcf040 	adcshi	pc, ip, r0, asr #32
d002176c:	b1361e75 	teqlt	r6, r5, ror lr
d0021770:	21203d01 			; <UNDEFINED> instruction: 0x21203d01
d0021774:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0021778:	1c69fdc3 	stclne	13, cr15, [r9], #-780	; 0xfffffcf4
d002177c:	2f00d1f8 	svccs	0x0000d1f8
d0021780:	8091f000 	addshi	pc, r1, r0
d0021784:	46209903 	strtmi	r9, [r0], -r3, lsl #18
d0021788:	fdbaf7ff 	ldc2	7, cr15, [sl, #1020]!	; 0x3fc
d002178c:	0f00f1b8 	svceq	0x0000f1b8
d0021790:	808df040 	addhi	pc, sp, r0, asr #32
d0021794:	e8bdb05f 	pop	{r0, r1, r2, r3, r4, r6, ip, sp, pc}
d0021798:	464a8ff0 			; <UNDEFINED> instruction: 0x464a8ff0
d002179c:	0313f3c8 	tsteq	r3, #200, 6	; 0x20000003	; <UNPREDICTABLE>
d00217a0:	f0404313 			; <UNDEFINED> instruction: 0xf0404313
d00217a4:	f1be80ae 			; <UNDEFINED> instruction: 0xf1be80ae
d00217a8:	f2000f19 	vrecps.f32	d0, d0, d9
d00217ac:	f8df80d4 			; <UNDEFINED> instruction: 0xf8df80d4
d00217b0:	234ec368 	movtcs	ip, #58216	; 0xe368
d00217b4:	44fc2149 	ldrbtmi	r2, [ip], #329	; 0x149
d00217b8:	9b04e0ab 	blls	0xd0159a6c
d00217bc:	ed9db12b 	ldfd	f3, [sp, #172]	; 0xac
d00217c0:	eeb17b00 	vmov.f64	d7, #16	; 0x40800000  4.0
d00217c4:	ed8d7b47 	vstr	d7, [sp, #284]	; 0x11c
d00217c8:	f1be7b00 			; <UNDEFINED> instruction: 0xf1be7b00
d00217cc:	f00a0f19 			; <UNDEFINED> instruction: 0xf00a0f19
d00217d0:	bf8c0adf 	svclt	0x008c0adf
d00217d4:	23012300 	movwcs	r2, #4864	; 0x1300
d00217d8:	9b689304 	blls	0xd1a463f0
d00217dc:	f2c02b00 	vqdmlsl.s<illegal width 8>	q9, d0, d0
d00217e0:	f1ba80c5 			; <UNDEFINED> instruction: 0xf1ba80c5
d00217e4:	f0400f47 			; <UNDEFINED> instruction: 0xf0400f47
d00217e8:	9b6880c7 	blls	0xd1a41b0c
d00217ec:	bf082b00 	svclt	0x00082b00
d00217f0:	93682301 	cmnls	r8, #67108864	; 0x4000000
d00217f4:	7b00ed9d 	blvc	0xd005ce70
d00217f8:	7b40eeb5 	blvc	0xd105d2d4
d00217fc:	fa10eef1 	blx	0xd045d3c8
d0021800:	80d0f000 	sbcshi	pc, r0, r0
d0021804:	6b04eeb2 	blvs	0xd015d2d4
d0021808:	7bc6eeb4 	blvc	0xcf1dd2e0
d002180c:	fa10eef1 	blx	0xd045d3d8
d0021810:	8170f2c0 	cmnhi	r0, r0, asr #5	; <UNPREDICTABLE>
d0021814:	0a00f04f 	beq	0xd005d958
d0021818:	f5bae003 			; <UNDEFINED> instruction: 0xf5bae003
d002181c:	f0007f9a 			; <UNDEFINED> instruction: 0xf0007f9a
d0021820:	ee87810f 	sins	f0, #10.0
d0021824:	f10a7b06 			; <UNDEFINED> instruction: 0xf10a7b06
d0021828:	eeb40a01 	vmov.f32	s0, #65	; 0x3e080000  0.1328125
d002182c:	eef17bc6 	vsqrt.f64	d23, d6
d0021830:	daf2fa10 	ble	0xcfce0078
d0021834:	6b00eeb7 	blvs	0xd005d318
d0021838:	7bc6eeb4 	blvc	0xcf1dd310
d002183c:	fa10eef1 	blx	0xd045d408
d0021840:	eeb2d511 	mrc	5, 5, sp, cr2, cr1, {0}
d0021844:	eeb75b04 	vmov.f64	d5, #116	; 0x3fa00000  1.250
d0021848:	e0036b00 	and	r6, r3, r0, lsl #22
d002184c:	7fa2f51a 	svcvc	0x00a2f51a
d0021850:	80fef000 	rscshi	pc, lr, r0
d0021854:	7b05ee27 	blvc	0xd019d0f8
d0021858:	3afff10a 	bcc	0xd001dc88
d002185c:	7bc6eeb4 	blvc	0xcf1dd334
d0021860:	fa10eef1 	blx	0xd045d42c
d0021864:	9b68d4f2 	blls	0xd1a56c34
d0021868:	f3404553 	vqrshl.u8	q10, <illegal reg q1.5>, q0
d002186c:	f11a80f1 			; <UNDEFINED> instruction: 0xf11a80f1
d0021870:	f2c00f04 			; <UNDEFINED> instruction: 0xf2c00f04
d0021874:	f10a80ed 			; <UNDEFINED> instruction: 0xf10a80ed
d0021878:	e0960101 	adds	r0, r6, r1, lsl #2
d002187c:	232b2701 			; <UNDEFINED> instruction: 0x232b2701
d0021880:	930346bb 	movwls	r4, #14011	; 0x36bb
d0021884:	1ab6e73b 	bne	0xceddb578
d0021888:	f005e765 			; <UNDEFINED> instruction: 0xf005e765
d002188c:	2f000501 	svccs	0x00000501
d0021890:	bb8dd167 	bllt	0xce395e34
d0021894:	b1361e75 	teqlt	r6, r5, ror lr
d0021898:	21303d01 	teqcs	r0, r1, lsl #26
d002189c:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d00218a0:	1c6afd2f 	stclne	13, cr15, [sl], #-188	; 0xffffff44
d00218a4:	f1b8d1f8 			; <UNDEFINED> instruction: 0xf1b8d1f8
d00218a8:	f43f0f00 			; <UNDEFINED> instruction: 0xf43f0f00
d00218ac:	2500af73 	strcs	sl, [r0, #-3955]	; 0xfffff08d
d00218b0:	37012700 	strcc	r2, [r1, -r0, lsl #14]
d00218b4:	1b01f819 	blne	0xd009f920
d00218b8:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d00218bc:	4547fd21 	strbmi	pc, [r7, #-3361]	; 0xfffff2df	; <UNPREDICTABLE>
d00218c0:	2d00d3f7 	stccs	3, cr13, [r0, #-988]	; 0xfffffc24
d00218c4:	af66f43f 	svcge	0x0066f43f
d00218c8:	2e001e75 	mcrcs	14, 0, r1, cr0, cr5, {3}
d00218cc:	af62f43f 	svcge	0x0062f43f
d00218d0:	21203d01 			; <UNDEFINED> instruction: 0x21203d01
d00218d4:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d00218d8:	1c6bfd13 	stclne	13, cr15, [fp], #-76	; 0xffffffb4
d00218dc:	b05fd1f8 	ldrshlt	sp, [pc], #-24	; <UNPREDICTABLE>
d00218e0:	8ff0e8bd 	svchi	0x00f0e8bd
d00218e4:	f1b8b927 			; <UNDEFINED> instruction: 0xf1b8b927
d00218e8:	d1e10f00 	mvnle	r0, r0, lsl #30
d00218ec:	461ee7ec 	ldrmi	lr, [lr], -ip, ror #15
d00218f0:	46209903 	strtmi	r9, [r0], -r3, lsl #18
d00218f4:	fd04f7ff 	stc2	7, cr15, [r4, #-1020]	; 0xfffffc04
d00218f8:	0f00f1b8 	svceq	0x0000f1b8
d00218fc:	2501d0e4 	strcs	sp, [r1, #-228]	; 0xffffff1c
d0021900:	f1bee7d6 			; <UNDEFINED> instruction: 0xf1bee7d6
d0021904:	d9470f19 	stmdble	r7, {r0, r3, r4, r8, r9, sl, fp}^
d0021908:	c210f8df 	andsgt	pc, r0, #14614528	; 0xdf0000
d002190c:	216e2361 	cmncs	lr, r1, ror #6
d0021910:	f10d44fc 			; <UNDEFINED> instruction: 0xf10d44fc
d0021914:	f10c0918 			; <UNDEFINED> instruction: 0xf10c0918
d0021918:	ea6f0202 	b	0xd1be2128
d002191c:	46480c0c 	strbmi	r0, [r8], -ip, lsl #24
d0021920:	f812e001 			; <UNDEFINED> instruction: 0xf812e001
d0021924:	f8003b01 			; <UNDEFINED> instruction: 0xf8003b01
d0021928:	eb0c1b01 	bl	0xd0328534
d002192c:	46190802 	ldrmi	r0, [r9], -r2, lsl #16
d0021930:	d1f62b00 	mvnsle	r2, r0, lsl #22
d0021934:	020beb08 	andeq	lr, fp, #8, 22	; 0x2000
d0021938:	d8a44296 	stmiale	r4!, {r1, r2, r4, r7, r9, lr}
d002193c:	0601f015 			; <UNDEFINED> instruction: 0x0601f015
d0021940:	af1df43f 	svcge	0x001df43f
d0021944:	d1d22f00 	bicsle	r2, r2, r0, lsl #30
d0021948:	0f00f1b8 	svceq	0x0000f1b8
d002194c:	af22f43f 	svcge	0x0022f43f
d0021950:	463e4635 			; <UNDEFINED> instruction: 0x463e4635
d0021954:	f8dfe7ac 			; <UNDEFINED> instruction: 0xf8dfe7ac
d0021958:	236ec1c8 	cmncs	lr, #200, 2	; 0x32
d002195c:	44fc2169 	ldrbtmi	r2, [ip], #361	; 0x169
d0021960:	9903e7d7 	stmdbls	r3, {r0, r1, r2, r4, r6, r7, r8, r9, sl, sp, lr, pc}
d0021964:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0021968:	e792fccb 	ldr	pc, [r2, fp, asr #25]
d002196c:	f1ba2306 			; <UNDEFINED> instruction: 0xf1ba2306
d0021970:	93680f47 	cmnls	r8, #284	; 0x11c
d0021974:	af3ef43f 	svcge	0x003ef43f
d0021978:	0f45f1ba 	svceq	0x0045f1ba
d002197c:	0918f10d 	ldmdbeq	r8, {r0, r2, r3, r8, ip, sp, lr, pc}
d0021980:	9b04d154 	blls	0xd0155ed8
d0021984:	0210f005 	andseq	pc, r0, #5
d0021988:	46489968 	strbmi	r9, [r8], -r8, ror #18
d002198c:	0b00ed9d 	bleq	0xd005d008
d0021990:	fbb6f7ff 	blx	0xceddf996
d0021994:	e6d74680 	ldrb	r4, [r7], r0, lsl #13
d0021998:	c188f8df 	ldrdgt	pc, [r8, pc]
d002199c:	214e2341 	cmpcs	lr, r1, asr #6
d00219a0:	e7b644fc 			; <UNDEFINED> instruction: 0xe7b644fc
d00219a4:	f04f2101 			; <UNDEFINED> instruction: 0xf04f2101
d00219a8:	9b680a00 	blls	0xd1a241b0
d00219ac:	0918f10d 	ldmdbeq	r8, {r0, r2, r3, r8, ip, sp, lr, pc}
d00219b0:	0210f005 	andseq	pc, r0, #5
d00219b4:	46481a59 			; <UNDEFINED> instruction: 0x46481a59
d00219b8:	ed9d9205 	lfm	f1, 1, [sp, #20]
d00219bc:	f7ff0b00 			; <UNDEFINED> instruction: 0xf7ff0b00
d00219c0:	4680fad7 	pkhtbmi	pc, r0, r7, asr #21	; <UNPREDICTABLE>
d00219c4:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d00219c8:	4649aebf 			; <UNDEFINED> instruction: 0x4649aebf
d00219cc:	9a052300 	bls	0xd016a5d4
d00219d0:	3301e003 	movwcc	lr, #4099	; 0x1003
d00219d4:	f0004598 			; <UNDEFINED> instruction: 0xf0004598
d00219d8:	f8118086 			; <UNDEFINED> instruction: 0xf8118086
d00219dc:	282e0b01 	stmdacs	lr!, {r0, r8, r9, fp}
d00219e0:	f1bad1f7 			; <UNDEFINED> instruction: 0xf1bad1f7
d00219e4:	db020f00 	blle	0xd00a55ec
d00219e8:	42999968 	addsmi	r9, r9, #104, 18	; 0x1a0000
d00219ec:	2a00d334 	bcs	0xd00566c4
d00219f0:	aeaaf47f 	mcrge	4, 5, pc, cr10, cr15, {3}	; <UNPREDICTABLE>
d00219f4:	e002464b 	and	r4, r2, fp, asr #12
d00219f8:	f43f4590 			; <UNDEFINED> instruction: 0xf43f4590
d00219fc:	f813aea5 			; <UNDEFINED> instruction: 0xf813aea5
d0021a00:	32011b01 	andcc	r1, r1, #1024	; 0x400
d0021a04:	d1f7292e 	mvnsle	r2, lr, lsr #18
d0021a08:	0308eb09 	movweq	lr, #35593	; 0x8b09
d0021a0c:	f813e005 			; <UNDEFINED> instruction: 0xf813e005
d0021a10:	29301d01 	ldmdbcs	r0!, {r0, r8, sl, fp, ip}
d0021a14:	ae98f47f 	mrcge	4, 4, APSR_nzcv, cr8, cr15, {3}
d0021a18:	45904680 	ldrmi	r4, [r0, #1664]	; 0x680
d0021a1c:	30fff108 	rscscc	pc, pc, r8, lsl #2
d0021a20:	f47fd8f5 			; <UNDEFINED> instruction: 0xf47fd8f5
d0021a24:	f108ae91 			; <UNDEFINED> instruction: 0xf108ae91
d0021a28:	e68d38ff 			; <UNDEFINED> instruction: 0xe68d38ff
d0021a2c:	0b00ed9d 	bleq	0xd005d0a8
d0021a30:	f0059968 			; <UNDEFINED> instruction: 0xf0059968
d0021a34:	46480210 			; <UNDEFINED> instruction: 0x46480210
d0021a38:	fa9af7ff 	blx	0xce6dfa3c
d0021a3c:	e6834680 	str	r4, [r3], r0, lsl #13
d0021a40:	6b00eeb7 	blvs	0xd005d524
d0021a44:	7bc6eeb4 	blvc	0xcf1dd51c
d0021a48:	fa10eef1 	blx	0xd045d614
d0021a4c:	aef9f53f 	mrcge	5, 7, APSR_nzcv, cr9, cr15, {1}
d0021a50:	0210f005 	andseq	pc, r0, #5
d0021a54:	0918f10d 	ldmdbeq	r8, {r0, r2, r3, r8, ip, sp, lr, pc}
d0021a58:	46489968 	strbmi	r9, [r8], -r8, ror #18
d0021a5c:	39019b04 	stmdbcc	r1, {r2, r8, r9, fp, ip, pc}
d0021a60:	ed9d9204 	lfm	f1, 1, [sp, #16]
d0021a64:	f7ff0b00 			; <UNDEFINED> instruction: 0xf7ff0b00
d0021a68:	9a04fb4b 	bls	0xd016079c
d0021a6c:	2a004680 	bcs	0xd0033474
d0021a70:	ae6af47f 	mcrge	4, 3, pc, cr10, cr15, {3}	; <UNPREDICTABLE>
d0021a74:	46424448 	strbmi	r4, [r2], -r8, asr #8
d0021a78:	461ae000 	ldrmi	lr, [sl], -r0
d0021a7c:	2a001e53 	bcs	0xd00293d0
d0021a80:	ae62f43f 	mcrge	4, 3, pc, cr2, cr15, {1}	; <UNPREDICTABLE>
d0021a84:	1d01f810 	stcne	8, cr15, [r1, #-64]	; 0xffffffc0
d0021a88:	0cdff001 	ldcleq	0, cr15, [pc], {1}
d0021a8c:	0f45f1bc 	svceq	0x0045f1bc
d0021a90:	eb09d1f3 	bl	0xd0296264
d0021a94:	46180c03 	ldrmi	r0, [r8], -r3, lsl #24
d0021a98:	f81ce005 			; <UNDEFINED> instruction: 0xf81ce005
d0021a9c:	f1baad01 			; <UNDEFINED> instruction: 0xf1baad01
d0021aa0:	d1220f30 			; <UNDEFINED> instruction: 0xd1220f30
d0021aa4:	f1004670 			; <UNDEFINED> instruction: 0xf1004670
d0021aa8:	28003eff 	stmdacs	r0, {r0, r1, r2, r3, r4, r5, r6, r7, r9, sl, fp, ip, sp}
d0021aac:	4543d1f5 	strbmi	sp, [r3, #-501]	; 0xfffffe0b
d0021ab0:	f1c2d212 			; <UNDEFINED> instruction: 0xf1c2d212
d0021ab4:	eb090a01 	bl	0xd02642c0
d0021ab8:	f10d0c03 			; <UNDEFINED> instruction: 0xf10d0c03
d0021abc:	44820e17 	strmi	r0, [r2], #3607	; 0xe17
d0021ac0:	445344c6 	ldrbmi	r4, [r3], #-1222	; 0xfffffb3a
d0021ac4:	3b0144d6 	blcc	0xd0072e24
d0021ac8:	e001444b 	and	r4, r1, fp, asr #8
d0021acc:	1f01f81c 	svcne	0x0001f81c
d0021ad0:	1f01f803 	svcne	0x0001f803
d0021ad4:	d1f94573 	mvnsle	r4, r3, ror r5
d0021ad8:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d0021adc:	0202eba8 	andeq	lr, r2, #168, 22	; 0x2a000
d0021ae0:	0802eb00 	stmdaeq	r2, {r8, r9, fp, sp, lr, pc}
d0021ae4:	4643e630 			; <UNDEFINED> instruction: 0x4643e630
d0021ae8:	f1bae77b 			; <UNDEFINED> instruction: 0xf1bae77b
d0021aec:	bf080f2e 	svclt	0x00080f2e
d0021af0:	e7dc4670 			; <UNDEFINED> instruction: 0xe7dc4670
d0021af4:	7b00eeb7 	blvc	0xd005d5d8
d0021af8:	6b00ed9d 	blvs	0xd005d174
d0021afc:	6bc7eeb4 	blvs	0xcf21d5d4
d0021b00:	fa10eef1 	blx	0xd045d6cc
d0021b04:	af4ef57f 	svcge	0x004ef57f
d0021b08:	0a00f04f 	beq	0xd005dc4c
d0021b0c:	7b00ed9d 	blvc	0xd005d188
d0021b10:	bf00e697 	svclt	0x0000e697
d0021b14:	ffffff84 			; <UNDEFINED> instruction: 0xffffff84
d0021b18:	fffffeee 			; <UNDEFINED> instruction: 0xfffffeee
d0021b1c:	fffffd90 			; <UNDEFINED> instruction: 0xfffffd90
d0021b20:	fffffd4e 			; <UNDEFINED> instruction: 0xfffffd4e
d0021b24:	fffffd08 			; <UNDEFINED> instruction: 0xfffffd08

Disassembly of section .text.sb_format.part.0:

d0021b58 <.text.sb_format.part.0>:
d0021b58:	4ff0e92d 	svcmi	0x00f0e92d
d0021b5c:	78094688 	stmdavc	r9, {r3, r7, r9, sl, lr}
d0021b60:	4683b0a7 	strmi	fp, [r3], r7, lsr #1
d0021b64:	f0002900 			; <UNDEFINED> instruction: 0xf0002900
d0021b68:	4bfa80b3 	blmi	0xcfec1e3c
d0021b6c:	f8df4691 			; <UNDEFINED> instruction: 0xf8df4691
d0021b70:	447ba3e8 	ldrbtmi	sl, [fp], #-1000	; 0xfffffc18
d0021b74:	4bf99308 	blmi	0xcfe8679c
d0021b78:	9309447b 	movwls	r4, #38011	; 0x947b
d0021b7c:	f0402925 			; <UNDEFINED> instruction: 0xf0402925
d0021b80:	f89880fd 			; <UNDEFINED> instruction: 0xf89880fd
d0021b84:	2c254001 	stccs	0, cr4, [r5], #-4
d0021b88:	80fef000 	rscshi	pc, lr, r0
d0021b8c:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d0021b90:	f1a42600 			; <UNDEFINED> instruction: 0xf1a42600
d0021b94:	2b100320 	blcs	0xd042281c
d0021b98:	e8dfd80a 	ldm	pc, {r1, r3, fp, ip, lr, pc}^	; <UNPREDICTABLE>
d0021b9c:	0978f003 	ldmdbeq	r8!, {r0, r1, ip, sp, lr, pc}^
d0021ba0:	09097509 	stmdbeq	r9, {r0, r3, r8, sl, ip, sp, lr}
d0021ba4:	09090909 	stmdbeq	r9, {r0, r3, r8, fp}
d0021ba8:	6f097209 	svcvs	0x00097209
d0021bac:	006a0909 	rsbeq	r0, sl, r9, lsl #18
d0021bb0:	f0402c2a 			; <UNDEFINED> instruction: 0xf0402c2a
d0021bb4:	f8d980ef 			; <UNDEFINED> instruction: 0xf8d980ef
d0021bb8:	f1083000 			; <UNDEFINED> instruction: 0xf1083000
d0021bbc:	681d0101 	ldmdavs	sp, {r0, r8}
d0021bc0:	2d001d1a 	stccs	13, cr1, [r0, #-104]	; 0xffffff98
d0021bc4:	2000f8c9 	andcs	pc, r0, r9, asr #17
d0021bc8:	8122f2c0 	smlawthi	r2, r0, r2, pc	; <UNPREDICTABLE>
d0021bcc:	5f00f5b5 	svcpl	0x0000f5b5
d0021bd0:	4001f898 	mulmi	r1, r8, r8
d0021bd4:	f44fbf28 			; <UNDEFINED> instruction: 0xf44fbf28
d0021bd8:	2c2e5500 	cfstr32cs	mvfx5, [lr], #-0
d0021bdc:	80fbf000 	rscshi	pc, fp, r0
d0021be0:	37fff04f 	ldrbcc	pc, [pc, pc, asr #32]!	; <UNPREDICTABLE>
d0021be4:	f0002c68 			; <UNDEFINED> instruction: 0xf0002c68
d0021be8:	2c6c810d 	stfcsp	f0, [ip], #-52	; 0xffffffcc
d0021bec:	811ef000 	tsthi	lr, r0	; <UNPREDICTABLE>
d0021bf0:	f0002c7a 			; <UNDEFINED> instruction: 0xf0002c7a
d0021bf4:	2c748122 	ldfcsp	f0, [r4], #-136	; 0xffffff78
d0021bf8:	8161f000 	msrhi	SPSR_c, r0
d0021bfc:	f0002c6a 			; <UNDEFINED> instruction: 0xf0002c6a
d0021c00:	230081b3 	movwcs	r8, #435	; 0x1b3
d0021c04:	d0632c00 	rsble	r2, r3, r0, lsl #24
d0021c08:	f1012c64 			; <UNDEFINED> instruction: 0xf1012c64
d0021c0c:	d07d0801 	rsbsle	r0, sp, r1, lsl #16
d0021c10:	d07b2c69 	rsbsle	r2, fp, r9, ror #24
d0021c14:	0262f1a4 	rsbeq	pc, r2, #164, 2	; 0x29
d0021c18:	01dff004 	bicseq	pc, pc, r4
d0021c1c:	f1a1b2d2 			; <UNDEFINED> instruction: 0xf1a1b2d2
d0021c20:	2a130c58 	bcs	0xd04e4d88
d0021c24:	fc8cfabc 	stc2	10, cr15, [ip], {188}	; 0xbc	; <UNPREDICTABLE>
d0021c28:	1c5cea4f 	mrrcne	10, 4, lr, ip, cr15
d0021c2c:	48c8d806 	stmiami	r8, {r1, r2, fp, ip, lr, pc}^
d0021c30:	f202fa20 	vpmax.s8	d15, d2, d16
d0021c34:	0201f002 	andeq	pc, r1, #2
d0021c38:	0c02ea4c 			; <UNDEFINED> instruction: 0x0c02ea4c
d0021c3c:	0f00f1bc 	svceq	0x0000f1bc
d0021c40:	816cf000 	msrhi	SPSR_fs, r0
d0021c44:	f0002c6f 			; <UNDEFINED> instruction: 0xf0002c6f
d0021c48:	2958811b 	ldmdbcs	r8, {r0, r1, r3, r4, r8, pc}^
d0021c4c:	811af000 	tsthi	sl, r0	; <UNPREDICTABLE>
d0021c50:	bf0c2c62 	svclt	0x000c2c62
d0021c54:	210a2102 	tstcs	sl, r2, lsl #2
d0021c58:	2b063b01 	blcs	0xd01b0864
d0021c5c:	84fdf200 	ldrbthi	pc, [sp], #512	; 0x200	; <UNPREDICTABLE>
d0021c60:	f013e8df 			; <UNDEFINED> instruction: 0xf013e8df
d0021c64:	0143014b 	cmpeq	r3, fp, asr #2
d0021c68:	00480018 	subeq	r0, r8, r8, lsl r0
d0021c6c:	00180018 	andseq	r0, r8, r8, lsl r0
d0021c70:	f0460048 			; <UNDEFINED> instruction: 0xf0460048
d0021c74:	f8180602 			; <UNDEFINED> instruction: 0xf8180602
d0021c78:	e78a4f01 	str	r4, [sl, r1, lsl #30]
d0021c7c:	0601f046 	streq	pc, [r1], -r6, asr #32
d0021c80:	f046e7f9 			; <UNDEFINED> instruction: 0xf046e7f9
d0021c84:	e7f60604 	ldrb	r0, [r6, r4, lsl #12]!
d0021c88:	0610f046 	ldreq	pc, [r0], -r6, asr #32
d0021c8c:	f046e7f3 			; <UNDEFINED> instruction: 0xf046e7f3
d0021c90:	e7f00608 	ldrb	r0, [r0, r8, lsl #12]!
d0021c94:	3000f8d9 	ldrdcc	pc, [r0], -r9
d0021c98:	681a1d18 	ldmdavs	sl, {r3, r4, r8, sl, fp, ip}
d0021c9c:	f8c92300 			; <UNDEFINED> instruction: 0xf8c92300
d0021ca0:	f1a40000 			; <UNDEFINED> instruction: 0xf1a40000
d0021ca4:	f0260058 			; <UNDEFINED> instruction: 0xf0260058
d0021ca8:	2400060c 	strcs	r0, [r0], #-1548	; 0xfffff9f4
d0021cac:	fab09704 	blx	0xcec478c4
d0021cb0:	9602f080 	strls	pc, [r2], -r0, lsl #1
d0021cb4:	09409503 	stmdbeq	r0, {r0, r1, r8, sl, ip, pc}^
d0021cb8:	94069100 	strls	r9, [r6], #-256	; 0xffffff00
d0021cbc:	46589005 	ldrbmi	r9, [r8], -r5
d0021cc0:	f7ff9401 			; <UNDEFINED> instruction: 0xf7ff9401
d0021cc4:	f898fb4d 			; <UNDEFINED> instruction: 0xf898fb4d
d0021cc8:	29001000 	stmdbcs	r0, {ip}
d0021ccc:	af56f47f 	svcge	0x0056f47f
d0021cd0:	300cf8db 	ldrdcc	pc, [ip], -fp
d0021cd4:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d0021cd8:	465880db 			; <UNDEFINED> instruction: 0x465880db
d0021cdc:	fafcf7ff 	blx	0xcff5fce0
d0021ce0:	300cf8db 	ldrdcc	pc, [ip], -fp
d0021ce4:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d0021ce8:	f8db80d3 			; <UNDEFINED> instruction: 0xf8db80d3
d0021cec:	b0270008 	eorlt	r0, r7, r8
d0021cf0:	8ff0e8bd 	svchi	0x00f0e8bd
d0021cf4:	3000f8d9 	ldrdcc	pc, [r0], -r9
d0021cf8:	f0233307 			; <UNDEFINED> instruction: 0xf0233307
d0021cfc:	f1030307 			; <UNDEFINED> instruction: 0xf1030307
d0021d00:	f8c90208 			; <UNDEFINED> instruction: 0xf8c90208
d0021d04:	e9d32000 	ldmib	r3, {sp}^
d0021d08:	e7ca2300 	strb	r2, [sl, r0, lsl #6]
d0021d0c:	2b063b01 	blcs	0xd01b0918
d0021d10:	84acf200 	strthi	pc, [ip], #512	; 0x200
d0021d14:	f003e8df 			; <UNDEFINED> instruction: 0xf003e8df
d0021d18:	1f04d7e0 	svcne	0x0004d7e0
d0021d1c:	001f0404 	andseq	r0, pc, r4, lsl #8
d0021d20:	3000f8d9 	ldrdcc	pc, [r0], -r9
d0021d24:	1d1a6818 	ldcne	8, cr6, [sl, #-96]	; 0xffffffa0
d0021d28:	f8c917c1 			; <UNDEFINED> instruction: 0xf8c917c1
d0021d2c:	28002000 	stmdacs	r0, {sp}
d0021d30:	0300f171 	movweq	pc, #369	; 0x171	; <UNPREDICTABLE>
d0021d34:	4602db1e 			; <UNDEFINED> instruction: 0x4602db1e
d0021d38:	0fc8460b 	svceq	0x00c8460b
d0021d3c:	2100240a 	tstcs	r0, sl, lsl #8
d0021d40:	90019704 	andls	r9, r1, r4, lsl #14
d0021d44:	95034658 	strls	r4, [r3, #-1624]	; 0xfffff9a8
d0021d48:	91069602 	tstls	r6, r2, lsl #12
d0021d4c:	94009105 	strls	r9, [r0], #-261	; 0xfffffefb
d0021d50:	fb06f7ff 	blx	0xd01dfd56
d0021d54:	f8d9e7b7 			; <UNDEFINED> instruction: 0xf8d9e7b7
d0021d58:	33073000 	movwcc	r3, #28672	; 0x7000
d0021d5c:	0307f023 	movweq	pc, #28707	; 0x7023	; <UNPREDICTABLE>
d0021d60:	0100e9d3 	ldrdeq	lr, [r0, -r3]
d0021d64:	0208f103 	andeq	pc, r8, #-1073741824	; 0xc0000000
d0021d68:	f8c92800 			; <UNDEFINED> instruction: 0xf8c92800
d0021d6c:	f1712000 			; <UNDEFINED> instruction: 0xf1712000
d0021d70:	dae00300 	ble	0xcf822978
d0021d74:	eb614242 	bl	0xd1872684
d0021d78:	e7de0341 	ldrb	r0, [lr, r1, asr #6]
d0021d7c:	f1084658 			; <UNDEFINED> instruction: 0xf1084658
d0021d80:	f7ff0801 			; <UNDEFINED> instruction: 0xf7ff0801
d0021d84:	e79efabd 			; <UNDEFINED> instruction: 0xe79efabd
d0021d88:	f1084658 			; <UNDEFINED> instruction: 0xf1084658
d0021d8c:	f7ff0802 			; <UNDEFINED> instruction: 0xf7ff0802
d0021d90:	e798fab7 			; <UNDEFINED> instruction: 0xe798fab7
d0021d94:	0230f1a4 	eorseq	pc, r0, #164, 2	; 0x29
d0021d98:	2b09b2d3 	blcs	0xd028e8ec
d0021d9c:	80e8f200 	rschi	pc, r8, r0, lsl #4
d0021da0:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d0021da4:	f5c22500 			; <UNDEFINED> instruction: 0xf5c22500
d0021da8:	46415300 	strbmi	r5, [r1], -r0, lsl #6
d0021dac:	0085eb05 	addeq	lr, r5, r5, lsl #22
d0021db0:	4303fbaa 	movwmi	pc, #15274	; 0x3baa	; <UNPREDICTABLE>
d0021db4:	4b01f818 	blmi	0xd009fe1c
d0021db8:	0fd3ebb5 	svceq	0x00d3ebb5
d0021dbc:	0540eb02 	strbeq	lr, [r0, #-2818]	; 0xfffff4fe
d0021dc0:	0230f1a4 	eorseq	pc, r0, #164, 2	; 0x29
d0021dc4:	f44fbf88 			; <UNDEFINED> instruction: 0xf44fbf88
d0021dc8:	b2d35500 	sbcslt	r5, r3, #0, 10
d0021dcc:	d9ea2b09 	stmible	sl!, {r0, r3, r8, r9, fp, sp}^
d0021dd0:	f47f2c2e 			; <UNDEFINED> instruction: 0xf47f2c2e
d0021dd4:	784caf05 	stmdavc	ip, {r0, r2, r8, r9, sl, fp, sp, pc}^
d0021dd8:	d1322c2a 	teqle	r2, sl, lsr #24
d0021ddc:	3000f8d9 	ldrdcc	pc, [r0], -r9
d0021de0:	681f1c88 	ldmdavs	pc, {r3, r7, sl, fp, ip}	; <UNPREDICTABLE>
d0021de4:	2f001d1a 	svccs	0x00001d1a
d0021de8:	2000f8c9 	andcs	pc, r0, r9, asr #17
d0021dec:	f2c0788c 	vmlal.s8	<illegal reg q11.5>, d16, d12
d0021df0:	f5b78091 			; <UNDEFINED> instruction: 0xf5b78091
d0021df4:	46015f00 	strmi	r5, [r1], -r0, lsl #30
d0021df8:	f44fbf28 			; <UNDEFINED> instruction: 0xf44fbf28
d0021dfc:	2c685700 	stclcs	7, cr5, [r8], #-0
d0021e00:	aef3f47f 	mrcge	4, 7, APSR_nzcv, cr3, cr15, {3}
d0021e04:	2c68784c 	stclcs	8, cr7, [r8], #-304	; 0xfffffed0
d0021e08:	3101d03e 	tstcc	r1, lr, lsr r0
d0021e0c:	e6f92302 	ldrbt	r2, [r9], r2, lsl #6
d0021e10:	4f00f1b5 	svcmi	0x0000f1b5
d0021e14:	0601f046 	streq	pc, [r1], -r6, asr #32
d0021e18:	426dd077 	rsbmi	sp, sp, #119	; 0x77
d0021e1c:	4001f898 	mulmi	r1, r8, r8
d0021e20:	5f00f5b5 	svcpl	0x0000f5b5
d0021e24:	f44fbf28 			; <UNDEFINED> instruction: 0xf44fbf28
d0021e28:	e6d65500 	ldrb	r5, [r6], r0, lsl #10
d0021e2c:	2c6c784c 	stclcs	8, cr7, [ip], #-304	; 0xfffffed0
d0021e30:	8096f000 	addshi	pc, r6, r0
d0021e34:	23033101 	movwcs	r3, #12545	; 0x3101
d0021e38:	784ce6e4 	stmdavc	ip, {r2, r5, r6, r7, r9, sl, sp, lr, pc}^
d0021e3c:	31012305 	tstcc	r1, r5, lsl #6
d0021e40:	f1a4e6e0 			; <UNDEFINED> instruction: 0xf1a4e6e0
d0021e44:	1c480230 	sfmne	f0, 2, [r8], {48}	; 0x30
d0021e48:	2b09b2d3 	blcs	0xd028e99c
d0021e4c:	80daf200 	sbcshi	pc, sl, r0, lsl #4
d0021e50:	27001c88 	strcs	r1, [r0, -r8, lsl #25]
d0021e54:	5300f5c2 	movwpl	pc, #1474	; 0x5c2	; <UNPREDICTABLE>
d0021e58:	0487eb07 	streq	lr, [r7], #2823	; 0xb07
d0021e5c:	fbaa4601 	blx	0xceab366a
d0021e60:	ebb7c303 	bl	0xcee12a74
d0021e64:	eb020fd3 	bl	0xd00a5db8
d0021e68:	f8100744 			; <UNDEFINED> instruction: 0xf8100744
d0021e6c:	bf884b01 	svclt	0x00884b01
d0021e70:	5700f44f 	strpl	pc, [r0, -pc, asr #8]
d0021e74:	0230f1a4 	eorseq	pc, r0, #164, 2	; 0x29
d0021e78:	2b09b2d3 	blcs	0xd028e9cc
d0021e7c:	e6b1d9ea 	ldrt	sp, [r1], sl, ror #19
d0021e80:	e6e92108 	strbt	r2, [r9], r8, lsl #2
d0021e84:	e6e72110 	usat	r2, #7, r0, lsl #2
d0021e88:	2301788c 	movwcs	r7, #6284	; 0x188c
d0021e8c:	e6b93102 	ldrt	r3, [r9], r2, lsl #2
d0021e90:	3000f8db 	ldrdcc	pc, [r0], -fp
d0021e94:	f43f2b00 			; <UNDEFINED> instruction: 0xf43f2b00
d0021e98:	f8dbaf28 			; <UNDEFINED> instruction: 0xf8dbaf28
d0021e9c:	2a002004 	bcs	0xd0029eb4
d0021ea0:	af23f43f 	svcge	0x0023f43f
d0021ea4:	1008f8db 	ldrdne	pc, [r8], -fp
d0021ea8:	bf98428a 	svclt	0x0098428a
d0021eac:	31fff102 	mvnscc	pc, r2, lsl #2
d0021eb0:	545a2200 	ldrbpl	r2, [sl], #-512	; 0xfffffe00
d0021eb4:	0008f8db 	ldrdeq	pc, [r8], -fp
d0021eb8:	e8bdb027 	pop	{r0, r1, r2, r5, ip, sp, pc}
d0021ebc:	784c8ff0 	stmdavc	ip, {r4, r5, r6, r7, r8, r9, sl, fp, pc}^
d0021ec0:	31012306 	tstcc	r1, r6, lsl #6
d0021ec4:	f8d9e69e 			; <UNDEFINED> instruction: 0xf8d9e69e
d0021ec8:	f9b33000 			; <UNDEFINED> instruction: 0xf9b33000
d0021ecc:	1d1a0000 	ldcne	0, cr0, [sl, #-0]
d0021ed0:	f8c917c1 			; <UNDEFINED> instruction: 0xf8c917c1
d0021ed4:	e72a2000 	str	r2, [sl, -r0]!
d0021ed8:	3000f8d9 	ldrdcc	pc, [r0], -r9
d0021edc:	0000f993 	muleq	r0, r3, r9
d0021ee0:	17c11d1a 	bfine	r1, sl, (invalid: 26:1)
d0021ee4:	2000f8c9 	andcs	pc, r0, r9, asr #17
d0021ee8:	f8d9e721 			; <UNDEFINED> instruction: 0xf8d9e721
d0021eec:	1d183000 	ldcne	0, cr3, [r8, #-0]
d0021ef0:	2300881a 	movwcs	r8, #2074	; 0x81a
d0021ef4:	0000f8c9 	andeq	pc, r0, r9, asr #17
d0021ef8:	f8d9e6d3 			; <UNDEFINED> instruction: 0xf8d9e6d3
d0021efc:	1d183000 	ldcne	0, cr3, [r8, #-0]
d0021f00:	2300781a 	movwcs	r7, #2074	; 0x81a
d0021f04:	0000f8c9 	andeq	pc, r0, r9, asr #17
d0021f08:	f898e6cb 			; <UNDEFINED> instruction: 0xf898e6cb
d0021f0c:	f44f4001 	vst4.8	{d20-d23}, [pc], r1
d0021f10:	e6625500 	strbt	r5, [r2], -r0, lsl #10
d0021f14:	37fff04f 	ldrbcc	pc, [pc, pc, asr #32]!	; <UNPREDICTABLE>
d0021f18:	e6634601 	strbt	r4, [r3], -r1, lsl #12
d0021f1c:	d0592c70 	subsle	r2, r9, r0, ror ip
d0021f20:	d0722c73 	rsbsle	r2, r2, r3, ror ip
d0021f24:	d0262c63 	eorle	r2, r6, r3, ror #24
d0021f28:	0245f1a1 	subeq	pc, r5, #1073741864	; 0x40000028
d0021f2c:	d93f2a02 	ldmdble	pc!, {r1, r9, fp, sp}	; <UNPREDICTABLE>
d0021f30:	f0002941 			; <UNDEFINED> instruction: 0xf0002941
d0021f34:	2c6e80af 	stclcs	0, cr8, [lr], #-700	; 0xfffffd44
d0021f38:	8216f000 	andshi	pc, r6, #0
d0021f3c:	21254658 			; <UNDEFINED> instruction: 0x21254658
d0021f40:	f9def7ff 			; <UNDEFINED> instruction: 0xf9def7ff
d0021f44:	46584621 	ldrbmi	r4, [r8], -r1, lsr #12
d0021f48:	f9daf7ff 			; <UNDEFINED> instruction: 0xf9daf7ff
d0021f4c:	bf00e6bb 	svclt	0x0000e6bb
d0021f50:	00082001 	andeq	r2, r8, r1
d0021f54:	ffffffce 			; <UNDEFINED> instruction: 0xffffffce
d0021f58:	cccccccd 	stclgt	12, cr12, [ip], {205}	; 0xcd
d0021f5c:	ffffffb4 			; <UNDEFINED> instruction: 0xffffffb4
d0021f60:	2304788c 	movwcs	r7, #18572	; 0x488c
d0021f64:	e64d3102 	strb	r3, [sp], -r2, lsl #2
d0021f68:	2307784c 	movwcs	r7, #30796	; 0x784c
d0021f6c:	e6493101 	strb	r3, [r9], -r1, lsl #2
d0021f70:	25004641 	strcs	r4, [r0, #-1601]	; 0xfffff9bf
d0021f74:	2d01e631 	stccs	6, cr14, [r1, #-196]	; 0xffffff3c
d0021f78:	2501bf38 	strcs	fp, [r1, #-3896]	; 0xfffff0c8
d0021f7c:	f10507f6 			; <UNDEFINED> instruction: 0xf10507f6
d0021f80:	f14037ff 			; <UNDEFINED> instruction: 0xf14037ff
d0021f84:	f8d9818b 			; <UNDEFINED> instruction: 0xf8d9818b
d0021f88:	46583000 	ldrbmi	r3, [r8], -r0
d0021f8c:	1d1a3d02 	ldcne	13, cr3, [sl, #-8]
d0021f90:	f8c97819 			; <UNDEFINED> instruction: 0xf8c97819
d0021f94:	f7ff2000 			; <UNDEFINED> instruction: 0xf7ff2000
d0021f98:	2f00f9b3 	svccs	0x0000f9b3
d0021f9c:	ae93f43f 	mrcge	4, 4, APSR_nzcv, cr3, cr15, {1}
d0021fa0:	46583d01 	ldrbmi	r3, [r8], -r1, lsl #26
d0021fa4:	f7ff2120 			; <UNDEFINED> instruction: 0xf7ff2120
d0021fa8:	1c68f9ab 			; <UNDEFINED> instruction: 0x1c68f9ab
d0021fac:	e68ad1f8 			; <UNDEFINED> instruction: 0xe68ad1f8
d0021fb0:	0000f8d9 	ldrdeq	pc, [r0], -r9
d0021fb4:	462b4621 	strtmi	r4, [fp], -r1, lsr #12
d0021fb8:	1dc44632 	stclne	6, cr4, [r4, #200]	; 0xc8
d0021fbc:	f0244658 			; <UNDEFINED> instruction: 0xf0244658
d0021fc0:	ed940407 	cfldrs	mvf0, [r4, #28]
d0021fc4:	34080b00 	strcc	r0, [r8], #-2816	; 0xfffff500
d0021fc8:	f8c99700 			; <UNDEFINED> instruction: 0xf8c99700
d0021fcc:	f7ff4000 			; <UNDEFINED> instruction: 0xf7ff4000
d0021fd0:	e678fb75 			; <UNDEFINED> instruction: 0xe678fb75
d0021fd4:	3000f8d9 	ldrdcc	pc, [r0], -r9
d0021fd8:	060cf026 	streq	pc, [ip], -r6, lsr #32
d0021fdc:	21102401 	tstcs	r0, r1, lsl #8
d0021fe0:	46581d1a 			; <UNDEFINED> instruction: 0x46581d1a
d0021fe4:	2000f8c9 	andcs	pc, r0, r9, asr #17
d0021fe8:	4663681a 			; <UNDEFINED> instruction: 0x4663681a
d0021fec:	f8cd9602 			; <UNDEFINED> instruction: 0xf8cd9602
d0021ff0:	9704c014 	smladls	r4, r4, r0, ip
d0021ff4:	f8cd9503 			; <UNDEFINED> instruction: 0xf8cd9503
d0021ff8:	9406c004 	strls	ip, [r6], #-4
d0021ffc:	f7ff9100 			; <UNDEFINED> instruction: 0xf7ff9100
d0022000:	e660f9af 	strbt	pc, [r0], -pc, lsr #19	; <UNPREDICTABLE>
d0022004:	27004601 	strcs	r4, [r0, -r1, lsl #12]
d0022008:	f8d9e5ec 			; <UNDEFINED> instruction: 0xf8d9e5ec
d002200c:	1d1a3000 	ldcne	0, cr3, [sl, #-0]
d0022010:	2000f8c9 	andcs	pc, r0, r9, asr #17
d0022014:	9314681b 	tstls	r4, #1769472	; 0x1b0000
d0022018:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d002201c:	781b813b 	ldmdavc	fp, {r0, r1, r3, r4, r5, r8, pc}
d0022020:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d0022024:	0ff88197 	svceq	0x00f88197
d0022028:	f0002f00 			; <UNDEFINED> instruction: 0xf0002f00
d002202c:	9a148193 	bls	0xd0542680
d0022030:	f8122400 			; <UNDEFINED> instruction: 0xf8122400
d0022034:	34013f01 	strcc	r3, [r1], #-3841	; 0xfffff0ff
d0022038:	42bcb11b 	adcsmi	fp, ip, #-1073741818	; 0xc0000006
d002203c:	2800d3f9 	stmdacs	r0, {r0, r3, r4, r5, r6, r7, r8, r9, ip, lr, pc}
d0022040:	42a5d1f7 	adcmi	sp, r5, #-1073741763	; 0xc000003d
d0022044:	813df200 	teqhi	sp, r0, lsl #4	; <UNPREDICTABLE>
d0022048:	0301f016 	movweq	pc, #4118	; 0x1016	; <UNPREDICTABLE>
d002204c:	f0009312 			; <UNDEFINED> instruction: 0xf0009312
d0022050:	25008189 	strcs	r8, [r0, #-393]	; 0xfffffe77
d0022054:	95149b14 	ldrls	r9, [r4, #-2836]	; 0xfffff4ec
d0022058:	1e5e4625 	cdpne	6, 5, cr4, cr14, cr5, {1}
d002205c:	4637461c 			; <UNDEFINED> instruction: 0x4637461c
d0022060:	f8164658 			; <UNDEFINED> instruction: 0xf8164658
d0022064:	f7ff1f01 			; <UNDEFINED> instruction: 0xf7ff1f01
d0022068:	1cbbf94b 			; <UNDEFINED> instruction: 0x1cbbf94b
d002206c:	429d1b1b 	addsmi	r1, sp, #27648	; 0x6c00
d0022070:	9b12d8f5 	blls	0xd04d844c
d0022074:	2b009d14 	blcs	0xd00494cc
d0022078:	ae25f43f 	mcrge	4, 1, pc, cr5, cr15, {1}	; <UNPREDICTABLE>
d002207c:	2d001e6c 	stccs	14, cr1, [r0, #-432]	; 0xfffffe50
d0022080:	ae21f43f 	mcrge	4, 1, pc, cr1, cr15, {1}	; <UNPREDICTABLE>
d0022084:	21203c01 			; <UNDEFINED> instruction: 0x21203c01
d0022088:	f7ff4658 			; <UNDEFINED> instruction: 0xf7ff4658
d002208c:	1c67f939 			; <UNDEFINED> instruction: 0x1c67f939
d0022090:	e618d1f8 			; <UNDEFINED> instruction: 0xe618d1f8
d0022094:	3000f8d9 	ldrdcc	pc, [r0], -r9
d0022098:	f0233307 			; <UNDEFINED> instruction: 0xf0233307
d002209c:	ed930307 	ldc	3, cr0, [r3, #28]
d00220a0:	33087b00 	movwcc	r7, #35584	; 0x8b00
d00220a4:	0b17ec51 	bleq	0xd061d1f0
d00220a8:	3000f8c9 	andcc	pc, r0, r9, asr #17
d00220ac:	ee17460b 	cfmsub32	mvax0, mvfx4, mvfx7, mvfx11
d00220b0:	2b002a10 	blcs	0xd002c8f8
d00220b4:	7b12ed8d 	blvc	0xd04dd6f0
d00220b8:	8176f2c0 	cmnhi	r6, r0, asr #5	; <UNPREDICTABLE>
d00220bc:	f1000771 			; <UNDEFINED> instruction: 0xf1000771
d00220c0:	00b18176 	adcseq	r8, r1, r6, ror r1
d00220c4:	0120f001 	msreq	CPSR_, r1
d00220c8:	f3c39114 	vorr.i32	d25, #180	; 0x000000b4
d00220cc:	920c510a 	andls	r5, ip, #-2147483646	; 0x80000002
d00220d0:	72fff240 	rscsvc	pc, pc, #64, 4
d00220d4:	0313f3c3 	tsteq	r3, #201326595	; 0xc000003	; <UNPREDICTABLE>
d00220d8:	42919116 	addsmi	r9, r1, #-2147483643	; 0x80000005
d00220dc:	f000930d 			; <UNDEFINED> instruction: 0xf000930d
d00220e0:	9b16817c 	blls	0xd05c26d8
d00220e4:	bf142b00 	svclt	0x00142b00
d00220e8:	22002201 	andcs	r2, r0, #268435456	; 0x10000000
d00220ec:	f0009217 			; <UNDEFINED> instruction: 0xf0009217
d00220f0:	f2a38161 	vmla.f32	d8, d3, d1[1]
d00220f4:	2b0033ff 	blcs	0xd002f0f8
d00220f8:	bfb8931a 	svclt	0x00b8931a
d00220fc:	9312425b 	tstls	r2, #-1342177275	; 0xb0000005
d0022100:	f0001c78 			; <UNDEFINED> instruction: 0xf0001c78
d0022104:	f5b7818a 			; <UNDEFINED> instruction: 0xf5b7818a
d0022108:	f3405f00 	vpmax.f32	d21, d0, d0
d002210c:	f44f817d 	vst4.16	{d24,d26,d28,d30}, [pc :256]!
d0022110:	e9dd5700 	ldmib	sp, {r8, r9, sl, ip, lr}^
d0022114:	9715230c 	ldrls	r2, [r5, -ip, lsl #6]
d0022118:	230ae9cd 	movwcs	lr, #43469	; 0xa9cd
d002211c:	2100ab22 	tstcs	r0, r2, lsr #22
d0022120:	ee079a12 			; <UNDEFINED> instruction: 0xee079a12
d0022124:	4618ba90 			; <UNDEFINED> instruction: 0x4618ba90
d0022128:	fbaa9321 	blx	0xceac6db6
d002212c:	4694c302 	ldrmi	ip, [r4], r2, lsl #6
d0022130:	3101468e 	smlabbcc	r1, lr, r6, r4
d0022134:	0bd3ea4f 	bleq	0xcf51ca78
d0022138:	0f09f1bc 	svceq	0x0009f1bc
d002213c:	038beb0b 	orreq	lr, fp, #11264	; 0x2c00
d0022140:	0343eba2 	movteq	lr, #15266	; 0x3ba2
d0022144:	f103465a 			; <UNDEFINED> instruction: 0xf103465a
d0022148:	b2db0330 	sbcslt	r0, fp, #48, 6	; 0xc0000000
d002214c:	3b01f800 	blcc	0xd00a0154
d0022150:	ee17d8eb 	cdp	8, 1, cr13, cr7, cr11, {7}
d0022154:	931fba90 	tstls	pc, #144, 20	; 0x90000
d0022158:	e080f8cd 	add	pc, r0, sp, asr #17
d002215c:	f0002f00 			; <UNDEFINED> instruction: 0xf0002f00
d0022160:	f00681bd 			; <UNDEFINED> instruction: 0xf00681bd
d0022164:	22040310 	andcs	r0, r4, #16, 6	; 0x40000000
d0022168:	9b14931b 	blls	0xd0546ddc
d002216c:	3b009815 	blcc	0xd00481c8
d0022170:	2301bf18 	movwcs	fp, #7960	; 0x1f18
d0022174:	44033302 	strmi	r3, [r3], #-770	; 0xfffffcfe
d0022178:	4413440b 	ldrmi	r4, [r3], #-1035	; 0xfffffbf5
d002217c:	f240429d 	vqsub.s8	d20, d16, d13
d0022180:	f00681b9 			; <UNDEFINED> instruction: 0xf00681b9
d0022184:	f0060101 			; <UNDEFINED> instruction: 0xf0060101
d0022188:	1aea0003 	bne	0xcfaa219c
d002218c:	0301f081 	movweq	pc, #4225	; 0x1081	; <UNPREDICTABLE>
d0022190:	901e9116 	andsls	r9, lr, r6, lsl r1
d0022194:	bf0c2802 	svclt	0x000c2802
d0022198:	f0032600 			; <UNDEFINED> instruction: 0xf0032600
d002219c:	92120601 	andsls	r0, r2, #1048576	; 0x100000
d00221a0:	f0002e00 			; <UNDEFINED> instruction: 0xf0002e00
d00221a4:	1e5581a5 	lognedp	f0, f5
d00221a8:	f0002a00 			; <UNDEFINED> instruction: 0xf0002a00
d00221ac:	3d0181b0 	stfccd	f0, [r1, #-704]	; 0xfffffd40
d00221b0:	46582120 	ldrbmi	r2, [r8], -r0, lsr #2
d00221b4:	f8a4f7ff 			; <UNDEFINED> instruction: 0xf8a4f7ff
d00221b8:	d1f81c69 	mvnsle	r1, r9, ror #24
d00221bc:	93162300 	tstls	r6, #0, 6
d00221c0:	2b009b14 	blcs	0xd0048e18
d00221c4:	8185f040 	orrhi	pc, r5, r0, asr #32
d00221c8:	46582130 			; <UNDEFINED> instruction: 0x46582130
d00221cc:	f898f7ff 			; <UNDEFINED> instruction: 0xf898f7ff
d00221d0:	46582c41 	ldrbmi	r2, [r8], -r1, asr #24
d00221d4:	2158bf0c 	cmpcs	r8, ip, lsl #30
d00221d8:	f7ff2178 			; <UNDEFINED> instruction: 0xf7ff2178
d00221dc:	9b1ef891 	blls	0xd07e0428
d00221e0:	d1022b02 	tstle	r2, r2, lsl #22
d00221e4:	f0402e00 			; <UNDEFINED> instruction: 0xf0402e00
d00221e8:	99178195 	ldmdbls	r7, {r0, r2, r4, r7, r8, pc}
d00221ec:	31304658 	teqcc	r0, r8, asr r6
d00221f0:	f7ffb2c9 			; <UNDEFINED> instruction: 0xf7ffb2c9
d00221f4:	9b15f885 	blls	0xd05a0410
d00221f8:	43139a1b 	tstmi	r3, #110592	; 0x1b000
d00221fc:	212ed003 			; <UNDEFINED> instruction: 0x212ed003
d0022200:	f7ff4658 			; <UNDEFINED> instruction: 0xf7ff4658
d0022204:	2c41f87d 	mcrrcs	8, 7, pc, r1, cr13	; <UNPREDICTABLE>
d0022208:	816ff000 	msrhi	SPSR_fsxc, r0
d002220c:	f0002f00 			; <UNDEFINED> instruction: 0xf0002f00
d0022210:	9e08821f 	mcrls	2, 0, r8, cr8, cr15, {0}
d0022214:	250000bb 	strcs	r0, [r0, #-187]	; 0xffffff45
d0022218:	3b049415 	blcc	0xd0147274
d002221c:	e0069314 	and	r9, r6, r4, lsl r3
d0022220:	78193501 	ldmdavc	r9, {r0, r8, sl, ip, sp}
d0022224:	f7ff4658 			; <UNDEFINED> instruction: 0xf7ff4658
d0022228:	42aff86b 	adcmi	pc, pc, #7012352	; 0x6b0000
d002222c:	2d0cd064 	stccs	0, cr13, [ip, #-400]	; 0xfffffe70
d0022230:	dcf54633 	ldclle	6, cr4, [r5], #204	; 0xcc
d0022234:	7185ebc5 	orrvc	lr, r5, r5, asr #23
d0022238:	9c0a9b14 			; <UNDEFINED> instruction: 0x9c0a9b14
d002223c:	460a2f0c 	strmi	r2, [sl], -ip, lsl #30
d0022240:	0181ea4f 	orreq	lr, r1, pc, asr #20
d0022244:	0282eb03 	addeq	lr, r2, #3072	; 0xc00
d0022248:	0330f101 	teqeq	r0, #1073741824	; 0x40000000	; <UNPREDICTABLE>
d002224c:	0110f101 	tsteq	r0, r1, lsl #2	; <UNPREDICTABLE>
d0022250:	0020f1c2 	eoreq	pc, r0, r2, asr #3
d0022254:	0c20f1a2 	stfeqd	f7, [r0], #-648	; 0xfffffd78
d0022258:	f202fa24 	vpmax.s8	d15, d2, d20
d002225c:	f1c39c0b 			; <UNDEFINED> instruction: 0xf1c39c0b
d0022260:	fa040e20 	blx	0xd0125ae8
d0022264:	9c0cf000 	stcls	0, cr15, [ip], {-0}
d0022268:	f303fa24 	vpmax.u8	d15, d3, d20
d002226c:	ea429c0d 	b	0xd10c92a8
d0022270:	980d0200 	stmdals	sp, {r9}
d0022274:	fe0efa04 	vseleq.f32	s30, s28, s8
d0022278:	fa209c0b 	blx	0xd08492ac
d002227c:	fa24f101 	blx	0xd095e688
d0022280:	ea43fc0c 	b	0xd11212b8
d0022284:	dc32030e 	ldcle	3, cr0, [r2], #-56	; 0xffffffc8
d0022288:	020cea42 	andeq	lr, ip, #270336	; 0x42000
d002228c:	030ff002 	movweq	pc, #61442	; 0xf002	; <UNPREDICTABLE>
d0022290:	e7c54433 			; <UNDEFINED> instruction: 0xe7c54433
d0022294:	447b4bfb 	ldrbtmi	r4, [fp], #-3067	; 0xfffff405
d0022298:	e6c49314 			; <UNDEFINED> instruction: 0xe6c49314
d002229c:	b1373d02 	teqlt	r7, r2, lsl #26
d00222a0:	21203d01 			; <UNDEFINED> instruction: 0x21203d01
d00222a4:	f7ff4658 			; <UNDEFINED> instruction: 0xf7ff4658
d00222a8:	1c6cf82b 	stclne	8, cr15, [ip], #-172	; 0xffffff54
d00222ac:	f8d9d1f8 			; <UNDEFINED> instruction: 0xf8d9d1f8
d00222b0:	46583000 	ldrbmi	r3, [r8], -r0
d00222b4:	78191d1a 	ldmdavc	r9, {r1, r3, r4, r8, sl, fp, ip}
d00222b8:	2000f8c9 	andcs	pc, r0, r9, asr #17
d00222bc:	f820f7ff 			; <UNDEFINED> instruction: 0xf820f7ff
d00222c0:	f016e501 			; <UNDEFINED> instruction: 0xf016e501
d00222c4:	eba50301 	bl	0xce962ed0
d00222c8:	93120504 	tstls	r2, #4, 10	; 0x1000000
d00222cc:	aec2f47f 	mcrge	4, 6, pc, cr2, cr15, {3}	; <UNPREDICTABLE>
d00222d0:	b1351e6e 	teqlt	r5, lr, ror #28
d00222d4:	21203e01 			; <UNDEFINED> instruction: 0x21203e01
d00222d8:	f7ff4658 			; <UNDEFINED> instruction: 0xf7ff4658
d00222dc:	1c73f811 	ldclne	8, cr15, [r3], #-68	; 0xffffffbc
d00222e0:	2c00d1f8 	stfcsd	f5, [r0], {248}	; 0xf8
d00222e4:	aceff43f 	cfstrdge	mvd15, [pc], #252	; 0xd00223e8
d00222e8:	93122300 	tstls	r2, #0, 6
d00222ec:	430be6b2 	movwmi	lr, #46770	; 0xb6b2
d00222f0:	030ff003 	movweq	pc, #61443	; 0xf003	; <UNPREDICTABLE>
d00222f4:	e7934433 			; <UNDEFINED> instruction: 0xe7934433
d00222f8:	2c419c15 	mcrrcs	12, 1, r9, r1, cr5
d00222fc:	2150bf0c 	cmpcs	r0, ip, lsl #30
d0022300:	46582170 			; <UNDEFINED> instruction: 0x46582170
d0022304:	fffcf7fe 			; <UNDEFINED> instruction: 0xfffcf7fe
d0022308:	9d219b1a 	vstmdbls	r1!, {d9-d21}
d002230c:	2b004658 	blcs	0xd0033c74
d0022310:	461c9b20 	ldrmi	r9, [ip], -r0, lsr #22
d0022314:	212dbfb4 			; <UNDEFINED> instruction: 0x212dbfb4
d0022318:	f7fe212b 			; <UNDEFINED> instruction: 0xf7fe212b
d002231c:	442cfff1 	strtmi	pc, [ip], #-4081	; 0xfffff00f
d0022320:	e001991f 	and	r9, r1, pc, lsl r9
d0022324:	1d01f814 	stcne	8, cr15, [r1, #-80]	; 0xffffffb0
d0022328:	f7fe4658 			; <UNDEFINED> instruction: 0xf7fe4658
d002232c:	42a5ffe9 	adcmi	pc, r5, #932	; 0x3a4
d0022330:	9b16d1f8 	blls	0xd05d6b18
d0022334:	f43f2b00 			; <UNDEFINED> instruction: 0xf43f2b00
d0022338:	9b12acc6 	blls	0xd04cd658
d002233c:	2b001e5c 	blcs	0xd0029cb4
d0022340:	acc1f43f 	cfstrdge	mvd15, [r1], {63}	; 0x3f
d0022344:	21203c01 			; <UNDEFINED> instruction: 0x21203c01
d0022348:	f7fe4658 			; <UNDEFINED> instruction: 0xf7fe4658
d002234c:	1c63ffd9 	stclne	15, cr15, [r3], #-868	; 0xfffffc9c
d0022350:	e4b8d1f8 	ldrt	sp, [r8], #504	; 0x1f8
d0022354:	f43f2d00 			; <UNDEFINED> instruction: 0xf43f2d00
d0022358:	07f2acb6 			; <UNDEFINED> instruction: 0x07f2acb6
d002235c:	817af140 	cmnhi	sl, r0, asr #2	; <UNPREDICTABLE>
d0022360:	e68f1e6c 	str	r1, [pc], ip, ror #28
d0022364:	e7bc9d12 			; <UNDEFINED> instruction: 0xe7bc9d12
d0022368:	f8db3b01 			; <UNDEFINED> instruction: 0xf8db3b01
d002236c:	2b062008 	blcs	0xd01aa394
d0022370:	e8dfd812 	ldm	pc, {r1, r4, fp, ip, lr, pc}^	; <UNPREDICTABLE>
d0022374:	014bf013 	cmpeq	fp, r3, lsl r0	; <UNPREDICTABLE>
d0022378:	00110142 	andseq	r0, r1, r2, asr #2
d002237c:	00110007 	andseq	r0, r1, r7
d0022380:	00070011 	andeq	r0, r7, r1, lsl r0
d0022384:	3000f8d9 	ldrdcc	pc, [r0], -r9
d0022388:	1d182100 	ldfnes	f2, [r8, #-0]
d002238c:	0000f8c9 	andeq	pc, r0, r9, asr #17
d0022390:	e9c3681b 	stmib	r3, {r0, r1, r3, r4, fp, sp, lr}^
d0022394:	e4962100 	ldr	r2, [r6], #256	; 0x100
d0022398:	3000f8d9 	ldrdcc	pc, [r0], -r9
d002239c:	f8c91d19 			; <UNDEFINED> instruction: 0xf8c91d19
d00223a0:	681b1000 	ldmdavs	fp, {ip}
d00223a4:	e48e601a 	str	r6, [lr], #26
d00223a8:	9114212d 	tstls	r4, sp, lsr #2
d00223ac:	212be68d 	smlawbcs	fp, sp, r6, lr
d00223b0:	e68a9114 	pkhbt	r9, sl, r4, lsl #2
d00223b4:	010ce9dd 	ldrdeq	lr, [ip, -sp]
d00223b8:	32fef240 	rscscc	pc, lr, #64, 4
d00223bc:	0301ea50 	movweq	lr, #6736	; 0x1a50
d00223c0:	48af9916 	stmiami	pc!, {r1, r2, r4, r8, fp, ip, pc}	; <UNPREDICTABLE>
d00223c4:	460bbf0c 	strmi	fp, [fp], -ip, lsl #30
d00223c8:	93124613 	tstls	r2, #19922944	; 0x1300000
d00223cc:	230ce9dd 	movwcs	lr, #51677	; 0xc9dd
d00223d0:	460bbf0c 	strmi	fp, [fp], -ip, lsl #30
d00223d4:	931a4603 	tstls	sl, #3145728	; 0x300000
d00223d8:	2c41e692 	mcrrcs	6, 9, lr, r1, cr2
d00223dc:	4632462b 	ldrtmi	r4, [r2], -fp, lsr #12
d00223e0:	bf0c4658 	svclt	0x000c4658
d00223e4:	21662146 	cmncs	r6, r6, asr #2
d00223e8:	ed9d9700 	ldc	7, cr9, [sp]
d00223ec:	f7ff0b12 			; <UNDEFINED> instruction: 0xf7ff0b12
d00223f0:	e468f965 	strbt	pc, [r8], #-2405	; 0xfffff69b	; <UNPREDICTABLE>
d00223f4:	463b4631 			; <UNDEFINED> instruction: 0x463b4631
d00223f8:	f8cd462c 			; <UNDEFINED> instruction: 0xf8cd462c
d00223fc:	9e158048 	cdpls	0, 1, cr8, cr5, cr8, {2}
d0022400:	461746c8 	ldrmi	r4, [r7], -r8, asr #13
d0022404:	460d4699 			; <UNDEFINED> instruction: 0x460d4699
d0022408:	f3402f0c 	vpmax.f32	d18, d0, d12
d002240c:	97158090 			; <UNDEFINED> instruction: 0x97158090
d0022410:	230ce9dd 	movwcs	lr, #51677	; 0xc9dd
d0022414:	230ae9cd 	movwcs	lr, #43469	; 0xa9cd
d0022418:	270de680 	strcs	lr, [sp, -r0, lsl #13]
d002241c:	46494628 	strbmi	r4, [r9], -r8, lsr #12
d0022420:	46c12300 	strbmi	r2, [r1], r0, lsl #6
d0022424:	9615463a 			; <UNDEFINED> instruction: 0x9615463a
d0022428:	4625469e 			; <UNDEFINED> instruction: 0x4625469e
d002242c:	8048f8dd 	ldrdhi	pc, [r8], #-141	; 0xffffff73
d0022430:	4606460f 	strmi	r4, [r6], -pc, lsl #12
d0022434:	0c20f1c3 	stfeqd	f7, [r0], #-780	; 0xfffffcf4
d0022438:	990c980d 	stmdbls	ip, {r0, r2, r3, fp, ip, pc}
d002243c:	0420f1a3 	strteq	pc, [r0], #-419	; 0xfffffe5d
d0022440:	fc0cfa00 	stc2	10, cr15, [ip], {-0}	; <UNPREDICTABLE>
d0022444:	40e040d9 	ldrdmi	r4, [r0], #9	; <UNPREDICTABLE>
d0022448:	ea413304 	b	0xd106f060
d002244c:	4301010c 	movwmi	r0, #4364	; 0x110c
d0022450:	010ff001 	tsteq	pc, r1	; <UNPREDICTABLE>
d0022454:	1e0ae9cd 	vmlsne.f16	s28, s21, s26	; <UNPREDICTABLE>
d0022458:	010ae9dd 	ldrdeq	lr, [sl, -sp]
d002245c:	d1c94301 	bicle	r4, r9, r1, lsl #6
d0022460:	d1e73a01 	mvnle	r3, r1, lsl #20
d0022464:	f8cd463b 			; <UNDEFINED> instruction: 0xf8cd463b
d0022468:	46178048 	ldrmi	r8, [r7], -r8, asr #32
d002246c:	469946c8 	ldrmi	r4, [r9], r8, asr #13
d0022470:	462c4631 			; <UNDEFINED> instruction: 0x462c4631
d0022474:	460d9e15 			; <UNDEFINED> instruction: 0x460d9e15
d0022478:	e9dd9715 	ldmib	sp, {r0, r2, r4, r8, r9, sl, ip, pc}^
d002247c:	e9cd230c 	stmib	sp, {r2, r3, r8, r9, sp}^
d0022480:	22012318 	andcs	r2, r1, #24, 6	; 0x60000000
d0022484:	e9cd2300 	stmib	sp, {r8, r9, sp}^
d0022488:	22002310 	andcs	r2, r0, #16, 6	; 0x40000000
d002248c:	2300f44f 	movwcs	pc, #1103	; 0x44f	; <UNPREDICTABLE>
d0022490:	230ee9cd 	movwcs	lr, #59853	; 0xe9cd
d0022494:	230ee9dd 	movwcs	lr, #59869	; 0xe9dd
d0022498:	0118e9dd 			; <UNDEFINED> instruction: 0x0118e9dd
d002249c:	bf08428b 	svclt	0x0008428b
d00224a0:	f0c04282 			; <UNDEFINED> instruction: 0xf0c04282
d00224a4:	429980c1 	addsmi	r8, r9, #193	; 0xc1
d00224a8:	4290bf08 	addsmi	fp, r0, #8, 30
d00224ac:	80b7f000 	adcshi	pc, r7, r0
d00224b0:	230ae9dd 	movwcs	lr, #43485	; 0xa9dd
d00224b4:	0110e9dd 			; <UNDEFINED> instruction: 0x0110e9dd
d00224b8:	bf08428b 	svclt	0x0008428b
d00224bc:	f47f4282 			; <UNDEFINED> instruction: 0xf47f4282
d00224c0:	9b17ae2d 	blls	0xd060dd7c
d00224c4:	33012200 	movwcc	r2, #4608	; 0x1200
d00224c8:	23009317 	movwcs	r9, #791	; 0x317
d00224cc:	230ae9cd 	movwcs	lr, #43469	; 0xa9cd
d00224d0:	4619e624 	ldrmi	lr, [r9], -r4, lsr #12
d00224d4:	f7fe4658 			; <UNDEFINED> instruction: 0xf7fe4658
d00224d8:	e675ff13 	uhadd16	pc, r5, r3	; <UNPREDICTABLE>
d00224dc:	0310f016 	tsteq	r0, #22	; <UNPREDICTABLE>
d00224e0:	2204bf14 	andcs	fp, r4, #20, 30	; 0x50
d00224e4:	931b2203 	tstls	fp, #805306368	; 0x30000000
d00224e8:	b177e63f 	cmnlt	r7, pc, lsr r6
d00224ec:	e6919e09 	ldr	r9, [r1], r9, lsl #28
d00224f0:	e665461e 			; <UNDEFINED> instruction: 0xe665461e
d00224f4:	0203f006 	andeq	pc, r3, #6
d00224f8:	0301f006 	movweq	pc, #4102	; 0x1006	; <UNPREDICTABLE>
d00224fc:	2200921e 	andcs	r9, r0, #-536870911	; 0xe0000001
d0022500:	0601f083 	streq	pc, [r1], -r3, lsl #1
d0022504:	92129316 	andsls	r9, r2, #1476395008	; 0x58000000
d0022508:	2150e65a 	cmpcs	r0, sl, asr r6
d002250c:	9b12e6f9 	blls	0xd04dc0f8
d0022510:	e6559316 			; <UNDEFINED> instruction: 0xe6559316
d0022514:	1e5d9b12 	vmovne.s8	r9, d13[0]
d0022518:	f43f2b00 			; <UNDEFINED> instruction: 0xf43f2b00
d002251c:	3d01ae66 	stccc	14, cr10, [r1, #-408]	; 0xfffffe68
d0022520:	46582130 			; <UNDEFINED> instruction: 0x46582130
d0022524:	feecf7fe 	mcr2	7, 7, pc, cr12, cr14, {7}	; <UNPREDICTABLE>
d0022528:	d1f81c6a 	mvnsle	r1, sl, ror #24
d002252c:	f1c7e65d 			; <UNDEFINED> instruction: 0xf1c7e65d
d0022530:	e9dd030d 	ldmib	sp, {r0, r2, r3, r8, r9}^
d0022534:	009b120c 	addseq	r1, fp, ip, lsl #4
d0022538:	f1c34618 			; <UNDEFINED> instruction: 0xf1c34618
d002253c:	f1a30c20 			; <UNDEFINED> instruction: 0xf1a30c20
d0022540:	460b0e20 	strmi	r0, [fp], -r0, lsr #28
d0022544:	fc0cfa02 	stc2	10, cr15, [ip], {2}	; <UNPREDICTABLE>
d0022548:	32fff04f 	rscscc	pc, pc, #79	; 0x4f
d002254c:	f1a040c3 			; <UNDEFINED> instruction: 0xf1a040c3
d0022550:	930a0120 	movwls	r0, #41248	; 0xa120
d0022554:	33fff04f 	mvnscc	pc, #79	; 0x4f
d0022558:	fe0efa03 	vseleq.f32	s30, s28, s6
d002255c:	f300fa02 	vpmax.u8	d15, d0, d2
d0022560:	ea429a0a 	b	0xd10c8d90
d0022564:	f1c0020c 			; <UNDEFINED> instruction: 0xf1c0020c
d0022568:	920a0c20 	andls	r0, sl, #32, 24	; 0x2000
d002256c:	fa229a0d 	blx	0xd08c8da8
d0022570:	ea43f101 	b	0xd111e97c
d0022574:	f04f020e 			; <UNDEFINED> instruction: 0xf04f020e
d0022578:	fa2333ff 	blx	0xd08ef57c
d002257c:	4603fc0c 	strmi	pc, [r3], -ip, lsl #24
d0022580:	30fff04f 	rscscc	pc, pc, pc, asr #32
d0022584:	0e21f1a3 	abseqdp	f7, f3
d0022588:	40989315 	addsmi	r9, r8, r5, lsl r3
d002258c:	ea429b0a 	b	0xd10c91bc
d0022590:	430b020c 	movwmi	r0, #45580	; 0xb20c
d0022594:	921b2101 	andsls	r2, fp, #1073741824	; 0x40000000
d0022598:	9b0c930a 	blls	0xd03471c8
d002259c:	ea239a15 	b	0xd0908df8
d00225a0:	00b80300 	adcseq	r0, r8, r0, lsl #6
d00225a4:	0c21f1c2 	stfeqd	f7, [r1], #-776	; 0xfffffcf8
d00225a8:	93189715 	tstls	r8, #5505024	; 0x540000
d00225ac:	f30efa01 	vpmax.u8	d15, d14, d1
d00225b0:	0e20f1a0 	abseqdp	f7, f0
d00225b4:	fc0cfa21 	stc2	10, cr15, [ip], {33}	; 0x21	; <UNPREDICTABLE>
d00225b8:	9b0d930f 	blls	0xd03871fc
d00225bc:	930b40d3 	movwls	r4, #45267	; 0xb0d3
d00225c0:	f30efa01 	vpmax.u8	d15, d14, d1
d00225c4:	0e20f1c0 	abseqdm	f7, f0
d00225c8:	9b0f9311 	blls	0xd0407214
d00225cc:	fe0efa21 	vseleq.f32	s30, s28, s3
d00225d0:	030cea43 	movweq	lr, #51779	; 0xca43
d00225d4:	3cfff102 	ldfccp	f7, [pc], #8	; 0xd00225e4
d00225d8:	930f9a1b 	movwls	r9, #64027	; 0xfa1b
d00225dc:	ea239b0d 	b	0xd0909218
d00225e0:	fa010202 	blx	0xd0062df0
d00225e4:	930ef30c 	movwls	pc, #58124	; 0xe30c	; <UNPREDICTABLE>
d00225e8:	92199b11 	andsls	r9, r9, #17408	; 0x4400
d00225ec:	030eea43 	movweq	lr, #59971	; 0xea43
d00225f0:	fa019311 	blx	0xd008723c
d00225f4:	9310f300 	tstls	r0, #0, 6	; <UNPREDICTABLE>
d00225f8:	f8d9e74c 			; <UNDEFINED> instruction: 0xf8d9e74c
d00225fc:	1d193000 	ldcne	0, cr3, [r9, #-0]
d0022600:	1000f8c9 	andne	pc, r0, r9, asr #17
d0022604:	801a681b 	andshi	r6, sl, fp, lsl r8
d0022608:	bb5df7ff 	bllt	0xd17a060c
d002260c:	3000f8d9 	ldrdcc	pc, [r0], -r9
d0022610:	f8c91d19 			; <UNDEFINED> instruction: 0xf8c91d19
d0022614:	681b1000 	ldmdavs	fp, {ip}
d0022618:	f7ff701a 			; <UNDEFINED> instruction: 0xf7ff701a
d002261c:	b95fbb54 	ldmdblt	pc, {r2, r4, r6, r8, r9, fp, ip, sp, pc}^	; <UNPREDICTABLE>
d0022620:	2b009b16 	blcs	0xd0049280
d0022624:	af44f43f 	svcge	0x0044f43f
d0022628:	33019b0a 	movwcc	r9, #6922	; 0x1b0a
d002262c:	9b0b930a 	blls	0xd030725c
d0022630:	0300f143 	movweq	pc, #323	; 0x143	; <UNPREDICTABLE>
d0022634:	e73b930b 	ldr	r9, [fp, -fp, lsl #6]!
d0022638:	f0039b0a 			; <UNDEFINED> instruction: 0xf0039b0a
d002263c:	931c0301 	tstls	ip, #67108864	; 0x4000000
d0022640:	931d2300 	tstls	sp, #0, 6
d0022644:	231ce9dd 	tstcs	ip, #3620864	; 0x374000
d0022648:	f43f4313 			; <UNDEFINED> instruction: 0xf43f4313
d002264c:	e7ebaf31 			; <UNDEFINED> instruction: 0xe7ebaf31
d0022650:	e6562170 			; <UNDEFINED> instruction: 0xe6562170
d0022654:	24001e6e 	strcs	r1, [r0], #-3694	; 0xfffff192
d0022658:	f8d9e63c 			; <UNDEFINED> instruction: 0xf8d9e63c
d002265c:	23000000 	movwcs	r0, #0
d0022660:	30046802 	andcc	r6, r4, r2, lsl #16
d0022664:	0000f8c9 	andeq	pc, r0, r9, asr #17
d0022668:	bb1bf7ff 	bllt	0xd072066c
d002266c:	3000f8d9 	ldrdcc	pc, [r0], -r9
d0022670:	33046818 	movwcc	r6, #18456	; 0x4818
d0022674:	f8c917c1 			; <UNDEFINED> instruction: 0xf8c917c1
d0022678:	f7ff3000 			; <UNDEFINED> instruction: 0xf7ff3000
d002267c:	bf00bb58 	svclt	0x0000bb58
d0022680:	fffffc02 			; <UNDEFINED> instruction: 0xfffffc02
d0022684:	fffff88e 			; <UNDEFINED> instruction: 0xfffff88e

Disassembly of section .text.vsnprintf:

d0022688 <.text.vsnprintf>:
d0022688:	b0a7b5f0 	strdlt	fp, [r7], r0	; <UNPREDICTABLE>
d002268c:	460e4607 	strmi	r4, [lr], -r7, lsl #12
d0022690:	4614461d 			; <UNDEFINED> instruction: 0x4614461d
d0022694:	228c2100 	addcs	r2, ip, #0, 2
d0022698:	f7fea803 			; <UNDEFINED> instruction: 0xf7fea803
d002269c:	9701fc2f 	strls	pc, [r1, -pc, lsr #24]
d00226a0:	95009602 	strls	r9, [r0, #-1538]	; 0xfffff9fe
d00226a4:	4621b134 			; <UNDEFINED> instruction: 0x4621b134
d00226a8:	a801466a 	stmdage	r1, {r1, r3, r5, r6, r9, sl, lr}
d00226ac:	fa54f7ff 	blx	0xd15606b0
d00226b0:	bdf0b027 	ldcllt	0, cr11, [r0, #156]!	; 0x9c
d00226b4:	30fff04f 	rscscc	pc, pc, pc, asr #32
d00226b8:	bf00e7fa 	svclt	0x0000e7fa

Disassembly of section .text.snprintf:

d00226bc <.text.snprintf>:
d00226bc:	b500b40c 	strlt	fp, [r0, #-1036]	; 0xfffffbf4
d00226c0:	ab04b083 	blge	0xd014e8d4
d00226c4:	2b04f853 	blcs	0xd0160818
d00226c8:	f7ff9301 			; <UNDEFINED> instruction: 0xf7ff9301
d00226cc:	b003ffdd 	ldrdlt	pc, [r3], -sp
d00226d0:	eb04f85d 	bl	0xd016084c
d00226d4:	4770b002 	ldrbmi	fp, [r0, -r2]!

Disassembly of section .text.memchr:

d0022700 <.text.memchr>:
d0022700:	4603b192 			; <UNDEFINED> instruction: 0x4603b192
d0022704:	b410b2c9 	ldrlt	fp, [r0], #-713	; 0xfffffd37
d0022708:	e0011884 	and	r1, r1, r4, lsl #17
d002270c:	d00742a3 	andle	r4, r7, r3, lsr #5
d0022710:	f8134618 			; <UNDEFINED> instruction: 0xf8134618
d0022714:	428a2b01 	addmi	r2, sl, #1024	; 0x400
d0022718:	f85dd1f8 			; <UNDEFINED> instruction: 0xf85dd1f8
d002271c:	47704b04 	ldrbmi	r4, [r0, -r4, lsl #22]!
d0022720:	f85d2000 			; <UNDEFINED> instruction: 0xf85d2000
d0022724:	47704b04 	ldrbmi	r4, [r0, -r4, lsl #22]!
d0022728:	47704610 			; <UNDEFINED> instruction: 0x47704610

Disassembly of section .text.strlen:

d002272c <.text.strlen>:
d002272c:	b1327802 	teqlt	r2, r2, lsl #16
d0022730:	f8134603 			; <UNDEFINED> instruction: 0xf8134603
d0022734:	29001f01 	stmdbcs	r0, {r0, r8, r9, sl, fp, ip}
d0022738:	1a18d1fb 	bne	0xd0656f2c
d002273c:	46104770 			; <UNDEFINED> instruction: 0x46104770
d0022740:	bf004770 	svclt	0x00004770

Disassembly of section .text.strcmp:

d0022744 <.text.strcmp>:
d0022744:	b1937803 	orrslt	r7, r3, r3, lsl #16
d0022748:	e002b410 	and	fp, r2, r0, lsl r4
d002274c:	3f01f810 	svccc	0x0001f810
d0022750:	460cb143 	strmi	fp, [ip], -r3, asr #2
d0022754:	2b01f811 	blcs	0xd00a07a0
d0022758:	d0f7429a 	smlalsle	r4, r7, sl, r2
d002275c:	f85d1a98 			; <UNDEFINED> instruction: 0xf85d1a98
d0022760:	47704b04 	ldrbmi	r4, [r0, -r4, lsl #22]!
d0022764:	f85d7862 			; <UNDEFINED> instruction: 0xf85d7862
d0022768:	1a984b04 	bne	0xce635380
d002276c:	780a4770 	stmdavc	sl, {r4, r5, r6, r8, r9, sl, lr}
d0022770:	47701a98 			; <UNDEFINED> instruction: 0x47701a98

Disassembly of section .text.strchr:

d0022774 <.text.strchr>:
d0022774:	7803b2c9 	stmdavc	r3, {r0, r3, r6, r7, r9, ip, sp, pc}
d0022778:	d0064299 	mulle	r6, r9, r2
d002277c:	f810b123 			; <UNDEFINED> instruction: 0xf810b123
d0022780:	428b3f01 	addmi	r3, fp, #1, 30
d0022784:	4770d1fa 			; <UNDEFINED> instruction: 0x4770d1fa
d0022788:	47704618 			; <UNDEFINED> instruction: 0x47704618

Disassembly of section .text.strrchr:

d002278c <.text.strrchr>:
d002278c:	b2c92200 	sbclt	r2, r9, #0, 4
d0022790:	4604b410 			; <UNDEFINED> instruction: 0x4604b410
d0022794:	3b01f810 	blcc	0xd00a07dc
d0022798:	bf08428b 	svclt	0x0008428b
d002279c:	2b004622 	blcs	0xd003402c
d00227a0:	4610d1f7 			; <UNDEFINED> instruction: 0x4610d1f7
d00227a4:	4b04f85d 	blmi	0xd0160920
d00227a8:	bf004770 	svclt	0x00004770
