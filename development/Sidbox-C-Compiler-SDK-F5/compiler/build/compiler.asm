
/mnt/LinuxDatas/work/SidboxIDE/SidboxIDE/development/Sidbox-C-Compiler-SDK-F5/compiler/build/cgarm/compiler-cgarm/compiler.elf:     file format elf32-littlearm


Disassembly of section .text.read_file:

d001e894 <.text.read_file>:
d001e894:	41ffe92d 	mvnsmi	lr, sp, lsr #18
d001e898:	4b1a461e 	blmi	0xd06b0118
d001e89c:	4690460f 	ldrmi	r4, [r0], pc, lsl #12
d001e8a0:	aa01685b 	bge	0xd0078a14
d001e8a4:	681d2101 	ldmdavs	sp, {r0, r8, sp}
d001e8a8:	47986bab 	ldrmi	r6, [r8, fp, lsr #23]
d001e8ac:	4604b120 	strmi	fp, [r4], -r0, lsr #2
d001e8b0:	b0044620 	andlt	r4, r4, r0, lsr #12
d001e8b4:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d001e8b8:	0002e9cd 	andeq	lr, r2, sp, asr #19
d001e8bc:	a9026ceb 	stmdbge	r2, {r0, r1, r3, r5, r6, r7, sl, fp, sp, lr}
d001e8c0:	47989801 	ldrmi	r9, [r8, r1, lsl #16]
d001e8c4:	b9784604 	ldmdblt	r8!, {r2, r9, sl, lr}^
d001e8c8:	45429a02 	strbmi	r9, [r2, #-2562]	; 0xfffff5fe
d001e8cc:	b15ad817 	cmplt	sl, r7, lsl r8
d001e8d0:	ab036bec 	blge	0xd00f9888
d001e8d4:	98014639 	stmdals	r1, {r0, r3, r4, r5, r9, sl, lr}
d001e8d8:	460447a0 	strmi	r4, [r4], -r0, lsr #15
d001e8dc:	e9ddb920 	ldmib	sp, {r5, r8, fp, ip, sp, pc}^
d001e8e0:	1a240402 	bne	0xd091f8f0
d001e8e4:	2401bf18 	strcs	fp, [r1], #-3864	; 0xfffff0e8
d001e8e8:	98016d6b 	stmdals	r1, {r0, r1, r3, r5, r6, r8, sl, fp, sp, lr}
d001e8ec:	2c004798 	stccs	7, cr4, [r0], {152}	; 0x98
d001e8f0:	4604d1de 			; <UNDEFINED> instruction: 0x4604d1de
d001e8f4:	d1db2800 	bicsle	r2, fp, r0, lsl #16
d001e8f8:	60339b02 	eorsvs	r9, r3, r2, lsl #22
d001e8fc:	f06fe7d8 			; <UNDEFINED> instruction: 0xf06fe7d8
d001e900:	e7f10402 	ldrb	r0, [r1, r2, lsl #8]!
d001e904:	2001f000 	andcs	pc, r1, r0

Disassembly of section .text.read_apicore:

d001e928 <.text.read_apicore>:
d001e928:	460ab507 	strmi	fp, [sl], -r7, lsl #10
d001e92c:	48064601 	stmdami	r6, {r0, r9, sl, lr}
d001e930:	4478ab01 	ldrbtmi	sl, [r8], #-2817	; 0xfffff4ff
d001e934:	ffaef7ff 			; <UNDEFINED> instruction: 0xffaef7ff
d001e938:	9801b918 	stmdals	r1, {r3, r4, r8, fp, ip, sp, pc}
d001e93c:	f85db003 			; <UNDEFINED> instruction: 0xf85db003
d001e940:	2000fb04 	andcs	pc, r0, r4, lsl #22
d001e944:	bf00e7fa 	svclt	0x0000e7fa
d001e948:	ffffffd2 			; <UNDEFINED> instruction: 0xffffffd2

Disassembly of section .text.write_file:

d001e960 <.text.write_file>:
d001e960:	47ffe92d 	ldrbmi	lr, [pc, sp, lsr #18]!
d001e964:	46074b4a 	strmi	r4, [r7], -sl, asr #22
d001e968:	46154688 	ldrmi	r4, [r5], -r8, lsl #13
d001e96c:	681e685b 	ldmdavs	lr, {r0, r1, r3, r4, r6, fp, sp, lr}
d001e970:	fbb4f002 	blx	0xced5a982
d001e974:	03f7f1a0 	mvnseq	pc, #160, 2	; 0x28
d001e978:	f5134604 			; <UNDEFINED> instruction: 0xf5134604
d001e97c:	f2407f81 	vmax.f32	d23, d16, d1
d001e980:	f8df8084 			; <UNDEFINED> instruction: 0xf8df8084
d001e984:	46029110 			; <UNDEFINED> instruction: 0x46029110
d001e988:	f8df4639 			; <UNDEFINED> instruction: 0xf8df4639
d001e98c:	44f9a10c 	ldrbtmi	sl, [r9], #268	; 0x10c
d001e990:	464844fa 			; <UNDEFINED> instruction: 0x464844fa
d001e994:	ff9af000 			; <UNDEFINED> instruction: 0xff9af000
d001e998:	220a4940 	andcs	r4, sl, #64, 18	; 0x100000
d001e99c:	0004eb09 	andeq	lr, r4, r9, lsl #22
d001e9a0:	f0004479 			; <UNDEFINED> instruction: 0xf0004479
d001e9a4:	4622ff93 	qadd8mi	pc, r2, r3	; <UNPREDICTABLE>
d001e9a8:	46504639 			; <UNDEFINED> instruction: 0x46504639
d001e9ac:	ff8ef000 			; <UNDEFINED> instruction: 0xff8ef000
d001e9b0:	220a493b 	andcs	r4, sl, #966656	; 0xec000
d001e9b4:	0004eb0a 	andeq	lr, r4, sl, lsl #22
d001e9b8:	f0004479 			; <UNDEFINED> instruction: 0xf0004479
d001e9bc:	6bb3ff87 	blvs	0xced1e7e0
d001e9c0:	2106aa01 	tstcs	r6, r1, lsl #20
d001e9c4:	47984648 	ldrmi	r4, [r8, r8, asr #12]
d001e9c8:	4604b120 	strmi	fp, [r4], -r0, lsr #2
d001e9cc:	b0044620 	andlt	r4, r4, r0, lsr #12
d001e9d0:	87f0e8bd 			; <UNDEFINED> instruction: 0x87f0e8bd
d001e9d4:	b9759002 	ldmdblt	r5!, {r1, ip, pc}^
d001e9d8:	98016d33 	stmdals	r1, {r0, r1, r4, r5, r8, sl, fp, sp, lr}
d001e9dc:	46044798 			; <UNDEFINED> instruction: 0x46044798
d001e9e0:	98016d73 	stmdals	r1, {r0, r1, r4, r5, r6, r8, sl, fp, sp, lr}
d001e9e4:	b90c4798 	stmdblt	ip, {r3, r4, r7, r8, r9, sl, lr}
d001e9e8:	4604b198 			; <UNDEFINED> instruction: 0x4604b198
d001e9ec:	6db3482d 	ldcvs	8, cr4, [r3, #180]!	; 0xb4
d001e9f0:	47984478 			; <UNDEFINED> instruction: 0x47984478
d001e9f4:	6c34e7ea 	ldcvs	7, cr14, [r4], #-936	; 0xfffffc58
d001e9f8:	462aab02 	strtmi	sl, [sl], -r2, lsl #22
d001e9fc:	98014641 	stmdals	r1, {r0, r6, r9, sl, lr}
d001ea00:	460447a0 	strmi	r4, [r4], -r0, lsr #15
d001ea04:	d1eb2800 	mvnle	r2, r0, lsl #16
d001ea08:	42ab9b02 	adcmi	r9, fp, #2048	; 0x800
d001ea0c:	2401d0e4 	strcs	sp, [r1], #-228	; 0xffffff1c
d001ea10:	6ab3e7e6 	bvs	0xced189b0
d001ea14:	a9034622 	stmdbge	r3, {r1, r5, r9, sl, lr}
d001ea18:	94034638 	strls	r4, [r3], #-1592	; 0xfffff9c8
d001ea1c:	46054798 			; <UNDEFINED> instruction: 0x46054798
d001ea20:	9b03b980 	blls	0xd010d028
d001ea24:	d42407db 	strtle	r0, [r4], #-2011	; 0xfffff825
d001ea28:	4638491f 			; <UNDEFINED> instruction: 0x4638491f
d001ea2c:	44796df3 	ldrbtmi	r6, [r9], #-3571	; 0xfffff20d
d001ea30:	46054798 			; <UNDEFINED> instruction: 0x46054798
d001ea34:	481db1d8 	ldmdami	sp, {r3, r4, r6, r7, r8, ip, sp, pc}
d001ea38:	44786db3 	ldrbtmi	r6, [r8], #-3507	; 0xfffff24d
d001ea3c:	b9d44798 	ldmiblt	r4, {r3, r4, r7, r8, r9, sl, lr}^
d001ea40:	e7c3462c 	strb	r4, [r3, ip, lsr #12]
d001ea44:	d1f62804 	mvnsle	r2, r4, lsl #16
d001ea48:	46394819 			; <UNDEFINED> instruction: 0x46394819
d001ea4c:	44786df3 	ldrbtmi	r6, [r8], #-3571	; 0xfffff20d
d001ea50:	46054798 			; <UNDEFINED> instruction: 0x46054798
d001ea54:	d1ee2800 	mvnle	r2, r0, lsl #16
d001ea58:	d0b72c00 	adcsle	r2, r7, r0, lsl #24
d001ea5c:	6db34815 	ldcvs	8, cr4, [r3, #84]!	; 0x54
d001ea60:	47984478 			; <UNDEFINED> instruction: 0x47984478
d001ea64:	bf183800 	svclt	0x00183800
d001ea68:	42442001 	submi	r2, r4, #1
d001ea6c:	2401e7ae 	strcs	lr, [r1], #-1966	; 0xfffff852
d001ea70:	2507e7ea 	strcs	lr, [r7, #-2026]	; 0xfffff816
d001ea74:	4810e7df 	ldmdami	r0, {r0, r1, r2, r3, r4, r6, r7, r8, r9, sl, sp, lr, pc}
d001ea78:	6df34639 	ldclvs	6, cr4, [r3, #228]!	; 0xe4
d001ea7c:	47984478 			; <UNDEFINED> instruction: 0x47984478
d001ea80:	d0dd2800 	sbcsle	r2, sp, r0, lsl #16
d001ea84:	0401f06f 	streq	pc, [r1], #-111	; 0xffffff91
d001ea88:	2407e7a0 	strcs	lr, [r7], #-1952	; 0xfffff860
d001ea8c:	bf00e79e 	svclt	0x0000e79e
d001ea90:	2001f000 	andcs	pc, r1, r0
d001ea94:	003540f6 	ldrshteq	r4, [r5], -r6
d001ea98:	00252e54 	eoreq	r2, r5, r4, asr lr
d001ea9c:	ffffffa8 			; <UNDEFINED> instruction: 0xffffffa8
d001eaa0:	ffffff9a 			; <UNDEFINED> instruction: 0xffffff9a
d001eaa4:	00354094 	mlaseq	r5, r4, r0, r4
d001eaa8:	00252db6 	strhteq	r2, [r5], -r6
d001eaac:	0035404a 	eorseq	r4, r5, sl, asr #32
d001eab0:	00354036 	eorseq	r4, r5, r6, lsr r0
d001eab4:	00252d84 	eoreq	r2, r5, r4, lsl #27
d001eab8:	00252d68 	eoreq	r2, r5, r8, ror #26

Disassembly of section .text.show_status:

d001eac0 <.text.show_status>:
d001eac0:	46024b09 	strmi	r4, [r2], -r9, lsl #22
d001eac4:	6818447b 	ldmdavs	r8, {r0, r1, r3, r4, r5, r6, sl, lr}
d001eac8:	689b4b06 	ldmvs	fp, {r1, r2, r8, r9, fp, lr}
d001eacc:	68dbb120 	ldmvs	fp, {r5, r8, ip, sp, pc}^
d001ead0:	f8d34611 			; <UNDEFINED> instruction: 0xf8d34611
d001ead4:	471830c4 	ldrmi	r3, [r8, -r4, asr #1]
d001ead8:	4904681b 	stmdbmi	r4, {r0, r1, r3, r4, fp, sp, lr}
d001eadc:	4479681b 	ldrbtmi	r6, [r9], #-2075	; 0xfffff7e5
d001eae0:	bf004718 	svclt	0x00004718
d001eae4:	2001f000 	andcs	pc, r1, r0
d001eae8:	00354240 	eorseq	r4, r5, r0, asr #4
d001eaec:	ffffffda 			; <UNDEFINED> instruction: 0xffffffda

Disassembly of section .text.open_editor:

d001eb68 <.text.open_editor>:
d001eb68:	47ffe92d 	ldrbmi	lr, [pc, sp, lsr #18]!
d001eb6c:	f2404c5d 	vfma.f32	q10, q0, <illegal reg q6.5>
d001eb70:	4607324d 	strmi	r3, [r7], -sp, asr #4
d001eb74:	68a3210c 	stmiavs	r3!, {r2, r3, r8, sp}
d001eb78:	685b2000 	ldmdavs	fp, {sp}^
d001eb7c:	4a5a9202 	bmi	0xd16c338c
d001eb80:	9201447a 	andls	r4, r1, #2046820352	; 0x7a000000
d001eb84:	728ef44f 	addvc	pc, lr, #1325400064	; 0x4f000000
d001eb88:	22119200 	andscs	r9, r1, #0, 4
d001eb8c:	f44f681d 	vst2.8	{d22-d23}, [pc :64]!
d001eb90:	47a873e4 	strmi	r7, [r8, r4, ror #7]!
d001eb94:	46051e43 	strmi	r1, [r5], -r3, asr #28
d001eb98:	2bfdb2db 	blcs	0xcff8b70c
d001eb9c:	4853d907 	ldmdami	r3, {r0, r1, r2, r8, fp, ip, lr, pc}^
d001eba0:	f7ff4478 			; <UNDEFINED> instruction: 0xf7ff4478
d001eba4:	2001ff8d 	andcs	pc, r1, sp, lsl #31
d001eba8:	e8bdb004 	pop	{r2, ip, sp, pc}
d001ebac:	4e5087f0 	mrcmi	7, 2, r8, cr0, cr0, {7}
d001ebb0:	447e212f 	ldrbtmi	r2, [lr], #-303	; 0xfffffed1
d001ebb4:	f0024630 			; <UNDEFINED> instruction: 0xf0024630
d001ebb8:	68a2fac1 	stmiavs	r2!, {r0, r6, r7, r9, fp, ip, sp, lr, pc}
d001ebbc:	68d24603 	ldmvs	r2, {r0, r1, r9, sl, lr}^
d001ebc0:	8018f8d2 			; <UNDEFINED> instruction: 0x8018f8d2
d001ebc4:	d07a2800 	rsbsle	r2, sl, r0, lsl #16
d001ebc8:	26013301 	strcs	r3, [r1], -r1, lsl #6
d001ebcc:	23109301 	tstcs	r0, #67108864	; 0x4000000
d001ebd0:	21082209 	tstcs	r8, r9, lsl #4
d001ebd4:	93004628 	movwls	r4, #1576	; 0x628
d001ebd8:	7387f44f 	orrvc	pc, r7, #1325400064	; 0x4f000000
d001ebdc:	f04f9602 			; <UNDEFINED> instruction: 0xf04f9602
d001ebe0:	47c00918 	bfimi	r0, r8, (invalid: 18:0)
d001ebe4:	4a4368a3 	bmi	0xd10f8e78
d001ebe8:	718ff44f 	orrvc	pc, pc, pc, asr #8
d001ebec:	468068db 	pkhtbmi	r6, r0, fp, asr #17
d001ebf0:	f8cd447a 			; <UNDEFINED> instruction: 0xf8cd447a
d001ebf4:	96029000 	strls	r9, [r2], -r0
d001ebf8:	92014628 	andls	r4, r1, #40, 12	; 0x2800000
d001ebfc:	f8d32204 			; <UNDEFINED> instruction: 0xf8d32204
d001ec00:	2344a008 	movtcs	sl, #16392	; 0x4008
d001ec04:	4b3c47d0 	blmi	0xd0f30b4c
d001ec08:	f44f4a3c 	vst1.8	{d20-d21}, [pc :256], ip
d001ec0c:	447b71b4 	ldrbtmi	r7, [fp], #-436	; 0xfffffe4c
d001ec10:	6018447a 	andsvs	r4, r8, sl, ror r4
d001ec14:	68a34628 	stmiavs	r3!, {r3, r5, r9, sl, lr}
d001ec18:	920168db 	andls	r6, r1, #14352384	; 0xdb0000
d001ec1c:	96022204 	strls	r2, [r2], -r4, lsl #4
d001ec20:	9000f8cd 	andls	pc, r0, sp, asr #17
d001ec24:	9008f8d3 	ldrdls	pc, [r8], -r3
d001ec28:	47c8234e 	strbmi	r2, [r8, lr, asr #6]
d001ec2c:	22004b34 	andcs	r4, r0, #52, 22	; 0xd000
d001ec30:	447b2108 	ldrbtmi	r2, [fp], #-264	; 0xfffffef8
d001ec34:	46286018 			; <UNDEFINED> instruction: 0x46286018
d001ec38:	68db68a3 	ldmvs	fp, {r0, r1, r5, r7, fp, sp, lr}^
d001ec3c:	4a319202 	bmi	0xd0c8344c
d001ec40:	447a9603 	ldrbtmi	r9, [sl], #-1539	; 0xfffff9fd
d001ec44:	22c19201 	sbccs	r9, r1, #268435456	; 0x10000000
d001ec48:	22229200 	eorcs	r9, r2, #0, 4
d001ec4c:	9034f8d3 	ldrsbtls	pc, [r4], -r3	; <UNPREDICTABLE>
d001ec50:	73d7f44f 	bicsvc	pc, r7, #1325400064	; 0x4f000000
d001ec54:	4b2c47c8 	blmi	0xd0b30b7c
d001ec58:	6018447b 	andsvs	r4, r8, fp, ror r4
d001ec5c:	68db68a3 	ldmvs	fp, {r0, r1, r5, r7, fp, sp, lr}^
d001ec60:	9018f8d3 			; <UNDEFINED> instruction: 0x9018f8d3
d001ec64:	d12c2f00 			; <UNDEFINED> instruction: 0xd12c2f00
d001ec68:	447b4b28 	ldrbtmi	r4, [fp], #-2856	; 0xfffff4d8
d001ec6c:	23129301 	tstcs	r2, #67108864	; 0x4000000
d001ec70:	210822eb 	smlattcs	r8, fp, r2, r2
d001ec74:	46289300 	strtmi	r9, [r8], -r0, lsl #6
d001ec78:	73d7f44f 	bicsvc	pc, r7, #1325400064	; 0x4f000000
d001ec7c:	47c89602 	strbmi	r9, [r8, r2, lsl #12]
d001ec80:	447b4b23 	ldrbtmi	r4, [fp], #-2851	; 0xfffff4dd
d001ec84:	f1b86018 			; <UNDEFINED> instruction: 0xf1b86018
d001ec88:	d00c0f00 	andle	r0, ip, r0, lsl #30
d001ec8c:	447b4b21 	ldrbtmi	r4, [fp], #-2849	; 0xfffff4df
d001ec90:	b143681b 	cmplt	r3, fp, lsl r8
d001ec94:	447b4b20 	ldrbtmi	r4, [fp], #-2848	; 0xfffff4e0
d001ec98:	b123681b 			; <UNDEFINED> instruction: 0xb123681b
d001ec9c:	447e4e1f 	ldrbtmi	r4, [lr], #-3615	; 0xfffff1e1
d001eca0:	b1036833 	tstlt	r3, r3, lsr r8
d001eca4:	68a3b980 	stmiavs	r3!, {r7, r8, fp, ip, sp, pc}
d001eca8:	685b4628 	ldmdavs	fp, {r3, r5, r9, sl, lr}^
d001ecac:	4798685b 			; <UNDEFINED> instruction: 0x4798685b
d001ecb0:	22004b1b 	andcs	r4, r0, #27648	; 0x6c00
d001ecb4:	447b481b 	ldrbtmi	r4, [fp], #-2075	; 0xfffff7e5
d001ecb8:	601a4478 	andsvs	r4, sl, r8, ror r4
d001ecbc:	4633e771 			; <UNDEFINED> instruction: 0x4633e771
d001ecc0:	4b19e783 	blmi	0xd0698ad4
d001ecc4:	e7d1447b 			; <UNDEFINED> instruction: 0xe7d1447b
d001ecc8:	462868a3 	strtmi	r6, [r8], -r3, lsr #17
d001eccc:	685b4917 	ldmdavs	fp, {r0, r1, r2, r4, r8, fp, lr}^
d001ecd0:	689b4479 	ldmvs	fp, {r0, r3, r4, r5, r6, sl, lr}
d001ecd4:	68a34798 	stmiavs	r3!, {r3, r4, r7, r8, r9, sl, lr}
d001ecd8:	68db6830 	ldmvs	fp, {r4, r5, fp, sp, lr}^
d001ecdc:	47986ddb 			; <UNDEFINED> instruction: 0x47986ddb
d001ece0:	e7612000 	strb	r2, [r1, -r0]!
d001ece4:	2001f000 	andcs	pc, r1, r0
d001ece8:	ffffff8a 			; <UNDEFINED> instruction: 0xffffff8a
d001ecec:	ffffff73 			; <UNDEFINED> instruction: 0xffffff73
d001ecf0:	00353dd2 	ldrsbteq	r3, [r5], -r2
d001ecf4:	ffffff3f 			; <UNDEFINED> instruction: 0xffffff3f
d001ecf8:	00253d62 	eoreq	r3, r5, r2, ror #26
d001ecfc:	ffffff24 			; <UNDEFINED> instruction: 0xffffff24
d001ed00:	00252cb2 	strhteq	r2, [r5], -r2
d001ed04:	00253d32 	eoreq	r3, r5, r2, lsr sp
d001ed08:	00252c90 	mlaeq	r5, r0, ip, r2
d001ed0c:	fffffe92 			; <UNDEFINED> instruction: 0xfffffe92
d001ed10:	00354082 	eorseq	r4, r5, r2, lsl #1
d001ed14:	00253ce2 	eoreq	r3, r5, r2, ror #25
d001ed18:	00252c4e 	eoreq	r2, r5, lr, asr #24
d001ed1c:	00252c4a 	eoreq	r2, r5, sl, asr #24
d001ed20:	0035404e 	eorseq	r4, r5, lr, asr #32
d001ed24:	fffffe82 			; <UNDEFINED> instruction: 0xfffffe82
d001ed28:	fffffe28 			; <UNDEFINED> instruction: 0xfffffe28
d001ed2c:	00000521 	andeq	r0, r0, r1, lsr #10

Disassembly of section .text.report_file.part.0:

d001edd8 <.text.report_file.part.0>:
d001edd8:	1cc5b537 	cfstr64ne	mvdx11, [r5], {55}	; 0x37
d001eddc:	460b4604 	strmi	r4, [fp], -r4, lsl #12
d001ede0:	4812d108 	ldmdami	r2, {r3, r8, ip, lr, pc}
d001ede4:	f7ff4478 			; <UNDEFINED> instruction: 0xf7ff4478
d001ede8:	1c63fe6b 	stclne	14, cr15, [r3], #-428	; 0xfffffe54
d001edec:	41584258 	cmpmi	r8, r8, asr r2
d001edf0:	bd30b003 	ldclt	0, cr11, [r0, #-12]!
d001edf4:	d1021d20 	tstle	r2, r0, lsr #26
d001edf8:	4478480d 	ldrbtmi	r4, [r8], #-2061	; 0xfffff7f3
d001edfc:	1ca1e7f3 	stcne	7, cr14, [r1], #972	; 0x3cc
d001ee00:	480cd102 	stmdami	ip, {r1, r8, ip, lr, pc}
d001ee04:	e7ee4478 			; <UNDEFINED> instruction: 0xe7ee4478
d001ee08:	d1021c62 	tstle	r2, r2, ror #24
d001ee0c:	4478480a 	ldrbtmi	r4, [r8], #-2058	; 0xfffff7f6
d001ee10:	4d0ae7e9 	stcmi	7, cr14, [sl, #-932]	; 0xfffffc5c
d001ee14:	71c0f44f 	bicvc	pc, r0, pc, asr #8
d001ee18:	447d4a09 	ldrbtmi	r4, [sp], #-2569	; 0xfffff5f7
d001ee1c:	447a9400 	ldrbtmi	r9, [sl], #-1024	; 0xfffffc00
d001ee20:	f0024628 			; <UNDEFINED> instruction: 0xf0024628
d001ee24:	4628f923 	strtmi	pc, [r8], -r3, lsr #18
d001ee28:	bf00e7dd 	svclt	0x0000e7dd
d001ee2c:	ffffff48 			; <UNDEFINED> instruction: 0xffffff48
d001ee30:	ffffff47 			; <UNDEFINED> instruction: 0xffffff47
d001ee34:	ffffff58 			; <UNDEFINED> instruction: 0xffffff58
d001ee38:	ffffff7a 			; <UNDEFINED> instruction: 0xffffff7a
d001ee3c:	00353d6a 	eorseq	r3, r5, sl, ror #26
d001ee40:	ffffff99 			; <UNDEFINED> instruction: 0xffffff99

Disassembly of section .text.read_header:

d001ee44 <.text.read_header>:
d001ee44:	47f0e92d 	ldrbmi	lr, [r0, sp, lsr #18]!
d001ee48:	460d9f09 	strmi	r9, [sp], -r9, lsl #30
d001ee4c:	46984616 			; <UNDEFINED> instruction: 0x46984616
d001ee50:	b9104681 	ldmdblt	r0, {r0, r7, r9, sl, lr}
d001ee54:	e8bd2000 	ldmfd	sp!, {sp}
d001ee58:	290087f0 	stmdbcs	r0, {r4, r5, r6, r7, r8, r9, sl, pc}
d001ee5c:	780bd0fa 	stmdavc	fp, {r1, r3, r4, r5, r6, r7, ip, lr, pc}
d001ee60:	d0f72b00 	rscsle	r2, r7, r0, lsl #22
d001ee64:	d0f52b2f 	rscsle	r2, r5, pc, lsr #22
d001ee68:	4628213a 			; <UNDEFINED> instruction: 0x4628213a
d001ee6c:	f95af002 			; <UNDEFINED> instruction: 0xf95af002
d001ee70:	d1ef2800 	mvnle	r2, r0, lsl #16
d001ee74:	4648212f 	strbmi	r2, [r8], -pc, lsr #2
d001ee78:	f960f002 			; <UNDEFINED> instruction: 0xf960f002
d001ee7c:	d0e92800 	rscle	r2, r9, r0, lsl #16
d001ee80:	0409eba0 	streq	lr, [r9], #-2976	; 0xfffff460
d001ee84:	f0024628 			; <UNDEFINED> instruction: 0xf0024628
d001ee88:	9a0af929 	bls	0xd02dd334
d001ee8c:	46823401 	strmi	r3, [r2], r1, lsl #8
d001ee90:	429a1823 	addsmi	r1, sl, #2293760	; 0x230000
d001ee94:	4622d9de 			; <UNDEFINED> instruction: 0x4622d9de
d001ee98:	46384649 	ldrtmi	r4, [r8], -r9, asr #12
d001ee9c:	fd16f000 	ldc2	0, cr15, [r6, #-0]
d001eea0:	0201f10a 	andeq	pc, r1, #-2147483646	; 0x80000002
d001eea4:	19384629 	ldmdbne	r8!, {r0, r3, r5, r9, sl, lr}
d001eea8:	fd10f000 	ldc2	0, cr15, [r0, #-0]
d001eeac:	9b08b14e 	blls	0xd024b3ec
d001eeb0:	46314642 	ldrtmi	r4, [r1], -r2, asr #12
d001eeb4:	f7ff4638 			; <UNDEFINED> instruction: 0xf7ff4638
d001eeb8:	fab0fced 	blx	0xcec5e274
d001eebc:	0940f080 	stmdbeq	r0, {r7, ip, sp, lr, pc}^
d001eec0:	2001e7c9 	andcs	lr, r1, r9, asr #15
d001eec4:	Address 0x00000000d001eec4 is out of bounds.


Disassembly of section .text.resolve_path.constprop.0:

d001eed4 <.text.resolve_path.constprop.0>:
d001eed4:	460fb5f7 			; <UNDEFINED> instruction: 0x460fb5f7
d001eed8:	46044616 			; <UNDEFINED> instruction: 0x46044616
d001eedc:	2000b910 	andcs	fp, r0, r0, lsl r9
d001eee0:	bdf0b003 	ldcllt	0, cr11, [r0, #12]!
d001eee4:	2b007803 	blcs	0xd003cef8
d001eee8:	f002d0f9 			; <UNDEFINED> instruction: 0xf002d0f9
d001eeec:	4605f8f7 			; <UNDEFINED> instruction: 0x4605f8f7
d001eef0:	f0024638 			; <UNDEFINED> instruction: 0xf0024638
d001eef4:	4285f8f3 	addmi	pc, r5, #15925248	; 0xf30000
d001eef8:	1a2bd9f1 	bne	0xd0b156c4
d001eefc:	44253f01 	strtmi	r3, [r5], #-3841	; 0xfffff0ff
d001ef00:	42ab4423 	adcmi	r4, fp, #587202560	; 0x23000000
d001ef04:	213ad118 	teqcs	sl, r8, lsl r1
d001ef08:	f0024620 			; <UNDEFINED> instruction: 0xf0024620
d001ef0c:	7823f90b 	stmdavc	r3!, {r0, r1, r3, r8, fp, ip, sp, lr, pc}
d001ef10:	d0032b2f 	andle	r2, r3, pc, lsr #22
d001ef14:	7843b1d8 	stmdavc	r3, {r3, r4, r6, r7, r8, ip, sp, pc}^
d001ef18:	d1e02b2f 	mvnle	r2, pc, lsr #22
d001ef1c:	46234a21 	strtmi	r4, [r3], -r1, lsr #20
d001ef20:	7180f44f 	orrvc	pc, r0, pc, asr #8
d001ef24:	447a4630 	ldrbtmi	r4, [sl], #-1584	; 0xfffff9d0
d001ef28:	f8a0f002 			; <UNDEFINED> instruction: 0xf8a0f002
d001ef2c:	28fe3801 	ldmcs	lr!, {r0, fp, ip, sp}^
d001ef30:	2000bf8c 	andcs	fp, r0, ip, lsl #31
d001ef34:	e7d32001 	ldrb	r2, [r3, r1]
d001ef38:	1b01f813 	blne	0xd009cf8c
d001ef3c:	2f01f817 	svccs	0x0001f817
d001ef40:	0120f041 	msreq	CPSR_, r1, asr #32
d001ef44:	0220f042 	eoreq	pc, r0, #66	; 0x42
d001ef48:	d0da4291 	smullsle	r4, sl, r1, r2
d001ef4c:	4b14e7c7 	blmi	0xd0558e70
d001ef50:	7180f44f 	orrvc	pc, r0, pc, asr #8
d001ef54:	685b4d14 	ldmdavs	fp, {r2, r4, r8, sl, fp, lr}^
d001ef58:	681b447d 	ldmdavs	fp, {r0, r2, r3, r4, r5, r6, sl, lr}
d001ef5c:	69db4628 	ldmibvs	fp, {r3, r5, r9, sl, lr}^
d001ef60:	28004798 	stmdacs	r0, {r3, r4, r7, r8, r9, sl, lr}
d001ef64:	782bd1bb 	stmdavc	fp!, {r0, r1, r3, r4, r5, r7, r8, ip, lr, pc}
d001ef68:	d0b82b00 	adcsle	r2, r8, r0, lsl #22
d001ef6c:	f0024628 			; <UNDEFINED> instruction: 0xf0024628
d001ef70:	4428f8b5 	strtmi	pc, [r8], #-2229	; 0xfffff74b
d001ef74:	3c01f810 	stccc	8, cr15, [r1], {16}
d001ef78:	d00d2b2f 	andle	r2, sp, pc, lsr #22
d001ef7c:	447b4b0b 	ldrbtmi	r4, [fp], #-2827	; 0xfffff4f5
d001ef80:	f44f4a0b 	vst1.8	{d20-d21}, [pc], fp
d001ef84:	46307180 	ldrtmi	r7, [r0], -r0, lsl #3
d001ef88:	e9cd447a 	stmib	sp, {r1, r3, r4, r5, r6, sl, lr}^
d001ef8c:	4b093400 	blmi	0xd026bf94
d001ef90:	f002447b 			; <UNDEFINED> instruction: 0xf002447b
d001ef94:	e7c9f86b 	strb	pc, [r9, fp, ror #16]	; <UNPREDICTABLE>
d001ef98:	447b4b07 	ldrbtmi	r4, [fp], #-2823	; 0xfffff4f9
d001ef9c:	bf00e7f0 	svclt	0x0000e7f0
d001efa0:	2001f000 	andcs	pc, r1, r0
d001efa4:	ffffff9f 			; <UNDEFINED> instruction: 0xffffff9f
d001efa8:	00353b2c 	eorseq	r3, r5, ip, lsr #22
d001efac:	ffffff45 			; <UNDEFINED> instruction: 0xffffff45
d001efb0:	ffffff40 			; <UNDEFINED> instruction: 0xffffff40
d001efb4:	00353af4 	ldrshteq	r3, [r5], -r4
d001efb8:	ffffff28 			; <UNDEFINED> instruction: 0xffffff28

Disassembly of section .text.build:

d001f010 <.text.build>:
d001f010:	22004b5b 	andcs	r4, r0, #93184	; 0x16c00
d001f014:	447bb570 	ldrbtmi	fp, [fp], #-1392	; 0xfffffa90
d001f018:	9307b09e 	movwls	fp, #28830	; 0x709e
d001f01c:	4b59a90e 	blmi	0xd168945c
d001f020:	447b9008 	ldrbtmi	r9, [fp], #-8
d001f024:	681b4858 	ldmdavs	fp, {r3, r4, r6, fp, lr}
d001f028:	42934478 	addsmi	r4, r3, #120, 8	; 0x78000000
d001f02c:	4b57d159 	blmi	0xd1613598
d001f030:	9306447b 	movwls	r4, #25723	; 0x647b
d001f034:	d15a2a00 	cmple	sl, r0, lsl #20
d001f038:	a906a807 	stmdbge	r6, {r0, r1, r2, fp, sp, pc}
d001f03c:	2a01ab09 	bcs	0xd0089c68
d001f040:	ab059302 	blge	0xd0183c50
d001f044:	2201bf38 	andcs	fp, r1, #56, 30	; 0xe0
d001f048:	4b519301 	blmi	0xd1483c54
d001f04c:	9300447b 	movwls	r4, #1147	; 0x47b
d001f050:	447b4b50 	ldrbtmi	r4, [fp], #-2896	; 0xfffff4b0
d001f054:	faa6f7ff 	blx	0xce9dd058
d001f058:	28004604 	stmdacs	r0, {r2, r9, sl, lr}
d001f05c:	9c0dd14e 	stflsd	f5, [sp], {78}	; 0x4e
d001f060:	4a4db94c 	bmi	0xd138d598
d001f064:	447a9b0c 	ldrbtmi	r9, [sl], #-2828	; 0xfffff4f4
d001f068:	42936812 	addsmi	r6, r3, #1179648	; 0x120000
d001f06c:	4c4bd243 	sfmmi	f5, 3, [fp], {67}	; 0x43
d001f070:	eb04447c 	bl	0xd0130268
d001f074:	212f2403 			; <UNDEFINED> instruction: 0x212f2403
d001f078:	f0024620 			; <UNDEFINED> instruction: 0xf0024620
d001f07c:	b100f85f 	tstlt	r0, pc, asr r8	; <UNPREDICTABLE>
d001f080:	9b091c44 	blls	0xd0266198
d001f084:	990b9a0a 	stmdbls	fp, {r1, r3, r9, fp, ip, pc}
d001f088:	4b45b90b 	blmi	0xd118d4bc
d001f08c:	4845447b 	stmdami	r5, {r0, r1, r3, r4, r5, r6, sl, lr}^
d001f090:	44789200 	ldrbtmi	r9, [r8], #-512	; 0xfffffe00
d001f094:	4d454a44 	vstrmi	s9, [r5, #-272]	; 0xfffffef0
d001f098:	46239302 	strtmi	r9, [r3], -r2, lsl #6
d001f09c:	447a4604 	ldrbtmi	r4, [sl], #-1540	; 0xfffff9fc
d001f0a0:	447d9101 	ldrbtmi	r9, [sp], #-257	; 0xfffffeff
d001f0a4:	71c0f44f 	bicvc	pc, r0, pc, asr #8
d001f0a8:	ffe0f001 			; <UNDEFINED> instruction: 0xffe0f001
d001f0ac:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d001f0b0:	6828fd07 	stmdavs	r8!, {r0, r1, r2, r8, sl, fp, ip, sp, lr, pc}
d001f0b4:	d0482800 	suble	r2, r8, r0, lsl #16
d001f0b8:	b9849c0d 	stmiblt	r4, {r0, r2, r3, sl, fp, ip, pc}
d001f0bc:	b171990a 	cmnlt	r1, sl, lsl #18
d001f0c0:	b1629a0b 	cmnlt	r2, fp, lsl #20
d001f0c4:	3a014e2d 	bcc	0xd0072980
d001f0c8:	68b33901 	ldmvs	r3!, {r0, r8, fp, ip, sp}
d001f0cc:	f8d368db 			; <UNDEFINED> instruction: 0xf8d368db
d001f0d0:	479830b8 			; <UNDEFINED> instruction: 0x479830b8
d001f0d4:	682868b3 	stmdavs	r8!, {r0, r1, r4, r5, r7, fp, sp, lr}
d001f0d8:	6ddb68db 	ldclvs	8, cr6, [fp, #876]	; 0x36c
d001f0dc:	20004798 	mulcs	r0, r8, r7
d001f0e0:	eb00e033 	bl	0xd00571b4
d001f0e4:	f8412402 			; <UNDEFINED> instruction: 0xf8412402
d001f0e8:	32014022 	andcc	r4, r1, #34	; 0x22
d001f0ec:	4830e79d 	ldmdami	r0!, {r0, r2, r3, r4, r7, r8, r9, sl, sp, lr, pc}
d001f0f0:	4478a90e 	ldrbtmi	sl, [r8], #-2318	; 0xfffff6f2
d001f0f4:	4c2fe7a2 	stcmi	7, cr14, [pc], #-648	; 0xd001ee74
d001f0f8:	e7bc447c 			; <UNDEFINED> instruction: 0xe7bc447c
d001f0fc:	46024d2e 	strmi	r4, [r2], -lr, lsr #26
d001f100:	447d9905 	ldrbtmi	r9, [sp], #-2309	; 0xfffff6fb
d001f104:	f7ff4628 			; <UNDEFINED> instruction: 0xf7ff4628
d001f108:	2800fc2b 	stmdacs	r0, {r0, r1, r3, r5, sl, fp, ip, sp, lr, pc}
d001f10c:	4b2bd131 	blmi	0xd0b135d8
d001f110:	6818447b 	ldmdavs	r8, {r0, r1, r3, r4, r5, r6, sl, lr}
d001f114:	212fb118 			; <UNDEFINED> instruction: 0x212fb118
d001f118:	f0024628 			; <UNDEFINED> instruction: 0xf0024628
d001f11c:	4b28f80f 	blmi	0xd0a5d160
d001f120:	681a447b 	ldmdavs	sl, {r0, r1, r3, r4, r5, r6, sl, lr}
d001f124:	d9152a01 	ldmdble	r5, {r0, r9, fp, sp}
d001f128:	1c43b188 	stfnep	f3, [r3], {136}	; 0x88
d001f12c:	f44f4825 	vst2.8	{d20-d21}, [pc :128], r5
d001f130:	920171c0 	andls	r7, r1, #192, 2	; 0x30
d001f134:	44784a24 	ldrbtmi	r4, [r8], #-2596	; 0xfffff5dc
d001f138:	447a9400 	ldrbtmi	r9, [sl], #-1024	; 0xfffffc00
d001f13c:	ff96f001 			; <UNDEFINED> instruction: 0xff96f001
d001f140:	44784822 	ldrbtmi	r4, [r8], #-2082	; 0xfffff7de
d001f144:	fcbcf7ff 	ldc2	7, cr15, [ip], #1020	; 0x3fc
d001f148:	b01e2001 	andslt	r2, lr, r1
d001f14c:	4b20bd70 	blmi	0xd084e714
d001f150:	e7eb447b 			; <UNDEFINED> instruction: 0xe7eb447b
d001f154:	1c43b150 	stfnep	f3, [r3], {80}	; 0x50
d001f158:	f44f4a1e 	vst1.8	{d20-d21}, [pc :64], lr
d001f15c:	481e71c0 	ldmdami	lr, {r6, r7, r8, ip, sp, lr}
d001f160:	9400447a 	strls	r4, [r0], #-1146	; 0xfffffb86
d001f164:	f0014478 			; <UNDEFINED> instruction: 0xf0014478
d001f168:	e7e9ff81 	strb	pc, [r9, r1, lsl #31]!	; <UNPREDICTABLE>
d001f16c:	447b4b1b 	ldrbtmi	r4, [fp], #-2843	; 0xfffff4e5
d001f170:	491be7f2 	ldmdbmi	fp, {r1, r4, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d001f174:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d001f178:	e7e6fe2f 	strb	pc, [r6, pc, lsr #28]!	; <UNPREDICTABLE>
d001f17c:	2001f000 	andcs	pc, r1, r0
d001f180:	0025395e 	eoreq	r3, r5, lr, asr r9
d001f184:	002528ca 	eoreq	r2, r5, sl, asr #17
d001f188:	002528c8 	eoreq	r2, r5, r8, asr #17
d001f18c:	00353954 	eorseq	r3, r5, r4, asr r9
d001f190:	fffffdf5 			; <UNDEFINED> instruction: 0xfffffdf5
d001f194:	fffff8d3 			; <UNDEFINED> instruction: 0xfffff8d3
d001f198:	00252886 	eoreq	r2, r5, r6, lsl #17
d001f19c:	00252880 	eoreq	r2, r5, r0, lsl #17
d001f1a0:	ffffff2c 			; <UNDEFINED> instruction: 0xffffff2c
d001f1a4:	00353af2 	ldrshteq	r3, [r5], -r2
d001f1a8:	ffffff2d 			; <UNDEFINED> instruction: 0xffffff2d
d001f1ac:	00252846 	eoreq	r2, r5, r6, asr #16
d001f1b0:	002537fe 	strdeq	r3, [r5], -lr	; <UNPREDICTABLE>
d001f1b4:	0035388c 	eorseq	r3, r5, ip, lsl #17
d001f1b8:	002525e2 	eoreq	r2, r5, r2, ror #11
d001f1bc:	00353bf4 	ldrshteq	r3, [r5], -r4
d001f1c0:	002527cc 	eoreq	r2, r5, ip, asr #15
d001f1c4:	00353a4e 	eorseq	r3, r5, lr, asr #20
d001f1c8:	fffffe9d 			; <UNDEFINED> instruction: 0xfffffe9d
d001f1cc:	00353a42 	eorseq	r3, r5, r2, asr #20
d001f1d0:	00252594 	mlaeq	r5, r4, r5, r2
d001f1d4:	fffffe97 			; <UNDEFINED> instruction: 0xfffffe97
d001f1d8:	00353a20 	eorseq	r3, r5, r0, lsr #20
d001f1dc:	00252576 	eoreq	r2, r5, r6, ror r5
d001f1e0:	fffff9c0 			; <UNDEFINED> instruction: 0xfffff9c0

Disassembly of section .text.editor_proc:

d001f1f4 <.text.editor_proc>:
d001f1f4:	460cb513 			; <UNDEFINED> instruction: 0x460cb513
d001f1f8:	d0412900 	suble	r2, r1, r0, lsl #18
d001f1fc:	2b10680b 	blcs	0xd0439230
d001f200:	68cad13e 	stmiavs	sl, {r1, r2, r3, r4, r5, r8, ip, lr, pc}^
d001f204:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d001f208:	d139429a 	teqle	r9, sl	; <illegal shifter operand>
d001f20c:	688b4a1f 	stmvs	fp, {r0, r1, r2, r3, r4, r9, fp, lr}
d001f210:	6812447a 	ldmdavs	r2, {r1, r3, r4, r5, r6, sl, lr}
d001f214:	d0044293 	mulle	r4, r3, r2
d001f218:	447a4a1d 	ldrbtmi	r4, [sl], #-2589	; 0xfffff5e3
d001f21c:	42936812 	addsmi	r6, r3, #1179648	; 0x120000
d001f220:	4b18d12e 	blmi	0xd06536e0
d001f224:	689b481b 	ldmvs	fp, {r0, r1, r3, r4, fp, lr}
d001f228:	4478491b 	ldrbtmi	r4, [r8], #-2331	; 0xfffff6e5
d001f22c:	447968db 	ldrbtmi	r6, [r9], #-2267	; 0xfffff725
d001f230:	6f1b4a15 	svcvs	0x001b4a15
d001f234:	91016800 	tstls	r1, r0, lsl #16
d001f238:	38014798 	stmdacc	r1, {r3, r4, r7, r8, r9, sl, lr}
d001f23c:	f5b09901 			; <UNDEFINED> instruction: 0xf5b09901
d001f240:	d9041f80 	stmdble	r4, {r7, r8, r9, sl, fp, ip}
d001f244:	44784815 	ldrbtmi	r4, [r8], #-2069	; 0xfffff7eb
d001f248:	fc3af7ff 	ldc2	7, cr15, [sl], #-1020	; 0xfffffc04
d001f24c:	4b14e007 	blmi	0xd0557270
d001f250:	447b68a2 	ldrbtmi	r6, [fp], #-2210	; 0xfffff75e
d001f254:	429a681b 	addsmi	r6, sl, #1769472	; 0x1b0000
d001f258:	f7ffd104 			; <UNDEFINED> instruction: 0xf7ffd104
d001f25c:	20f0fed9 	ldrsbtcs	pc, [r0], #233	; 0xe9	; <UNPREDICTABLE>
d001f260:	bd10b002 	ldclt	0, cr11, [r0, #-8]
d001f264:	480f4602 	stmdami	pc, {r1, r9, sl, lr}	; <UNPREDICTABLE>
d001f268:	f7ff4478 			; <UNDEFINED> instruction: 0xf7ff4478
d001f26c:	b910fb79 	ldmdblt	r0, {r0, r3, r4, r5, r6, r8, r9, fp, ip, sp, lr, pc}
d001f270:	4478480d 	ldrbtmi	r4, [r8], #-2061	; 0xfffff7f3
d001f274:	490de7e8 	stmdbmi	sp, {r3, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d001f278:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d001f27c:	e7eefdad 	strb	pc, [lr, sp, lsr #27]!	; <UNPREDICTABLE>
d001f280:	e7ed2000 	strb	r2, [sp, r0]!
d001f284:	2001f000 	andcs	pc, r1, r0
d001f288:	00100001 	andseq	r0, r0, r1
d001f28c:	00253760 	eoreq	r3, r5, r0, ror #14
d001f290:	002526ca 	eoreq	r2, r5, sl, asr #13
d001f294:	002526be 	strhteq	r2, [r5], -lr
d001f298:	00253746 	eoreq	r3, r5, r6, asr #14
d001f29c:	fffffae6 			; <UNDEFINED> instruction: 0xfffffae6
d001f2a0:	00252692 	mlaeq	r5, r2, r6, r2
d001f2a4:	0035371c 	eorseq	r3, r5, ip, lsl r7
d001f2a8:	ffffff6e 			; <UNDEFINED> instruction: 0xffffff6e
d001f2ac:	fffff8b7 			; <UNDEFINED> instruction: 0xfffff8b7

Disassembly of section .text.startup.main:

d001f48c <.text.startup.main>:
d001f48c:	e92d2801 	push	{r0, fp, sp}
d001f490:	46044ff0 			; <UNDEFINED> instruction: 0x46044ff0
d001f494:	ed2d460f 	stc	6, cr4, [sp, #-60]!	; 0xffffffc4
d001f498:	b0978b02 	addslt	r8, r7, r2, lsl #22
d001f49c:	808cf000 	addhi	pc, ip, r0
d001f4a0:	f0402803 			; <UNDEFINED> instruction: 0xf0402803
d001f4a4:	49af8159 	stmibmi	pc!, {r0, r3, r4, r6, r8, pc}	; <UNPREDICTABLE>
d001f4a8:	44796878 	ldrbtmi	r6, [r9], #-2168	; 0xfffff788
d001f4ac:	fe22f001 	cdp2	0, 2, cr15, cr2, cr1, {0}
d001f4b0:	f680fab0 			; <UNDEFINED> instruction: 0xf680fab0
d001f4b4:	49ac0976 	stmibmi	ip!, {r1, r2, r4, r5, r6, r8, fp}
d001f4b8:	44796878 	ldrbtmi	r6, [r9], #-2168	; 0xfffff788
d001f4bc:	fe1af001 	cdp2	0, 1, cr15, cr10, cr1, {0}
d001f4c0:	b966b958 	stmdblt	r6!, {r3, r4, r6, r8, fp, ip, sp, pc}^
d001f4c4:	447848a9 	ldrbtmi	r4, [r8], #-2217	; 0xfffff757
d001f4c8:	f7ff2401 			; <UNDEFINED> instruction: 0xf7ff2401
d001f4cc:	4620faf9 			; <UNDEFINED> instruction: 0x4620faf9
d001f4d0:	ecbdb017 	ldc	0, cr11, [sp], #92	; 0x5c
d001f4d4:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d001f4d8:	2e008ff0 	mcrcs	15, 0, r8, cr0, cr0, {7}
d001f4dc:	f104d05d 			; <UNDEFINED> instruction: 0xf104d05d
d001f4e0:	25004480 	strcs	r4, [r0, #-1152]	; 0xfffffb80
d001f4e4:	46ab3c01 	strtmi	r3, [fp], r1, lsl #24
d001f4e8:	0024f857 	eoreq	pc, r4, r7, asr r8	; <UNPREDICTABLE>
d001f4ec:	f8df2401 			; <UNDEFINED> instruction: 0xf8df2401
d001f4f0:	49a08280 	stmibmi	r0!, {r7, r9, pc}
d001f4f4:	447944f8 	ldrbtmi	r4, [r9], #-1272	; 0xfffffb08
d001f4f8:	f7ff4642 			; <UNDEFINED> instruction: 0xf7ff4642
d001f4fc:	2800fceb 	stmdacs	r0, {r0, r1, r3, r5, r6, r7, sl, fp, ip, sp, lr, pc}
d001f500:	489dd15f 	ldmmi	sp, {r0, r1, r2, r3, r4, r6, r8, ip, lr, pc}
d001f504:	e7df4478 			; <UNDEFINED> instruction: 0xe7df4478
d001f508:	0389ea4f 	orreq	lr, r9, #323584	; 0x4f000
d001f50c:	1a10ee18 	bne	0xd045ad74
d001f510:	0029f857 	eoreq	pc, r9, r7, asr r8	; <UNPREDICTABLE>
d001f514:	0889eb07 	stmeq	r9, {r0, r1, r2, r8, r9, fp, sp, lr, pc}
d001f518:	f0019302 			; <UNDEFINED> instruction: 0xf0019302
d001f51c:	b960fdeb 	stmdblt	r0!, {r0, r1, r3, r5, r6, r7, r8, sl, fp, ip, sp, lr, pc}^
d001f520:	f109b946 			; <UNDEFINED> instruction: 0xf109b946
d001f524:	42a10101 	adcmi	r0, r1, #1073741824	; 0x40000000
d001f528:	f8d8da04 			; <UNDEFINED> instruction: 0xf8d8da04
d001f52c:	78091004 	stmdavc	r9, {r2, ip}
d001f530:	d130292d 	teqle	r0, sp, lsr #18
d001f534:	44784891 	ldrbtmi	r4, [r8], #-2193	; 0xfffff76f
d001f538:	4651e7c6 	ldrbmi	lr, [r1], -r6, asr #15
d001f53c:	0029f857 	eoreq	pc, r9, r7, asr r8	; <UNPREDICTABLE>
d001f540:	fdd8f001 	ldc2l	0, cr15, [r8, #4]
d001f544:	f1bbb978 			; <UNDEFINED> instruction: 0xf1bbb978
d001f548:	d1090f00 	tstle	r9, r0, lsl #30
d001f54c:	0901f109 	stmdbeq	r1, {r0, r3, r8, ip, sp, lr, pc}
d001f550:	da0545a1 	ble	0xd0170bdc
d001f554:	b004f8d8 	ldrdlt	pc, [r4], -r8
d001f558:	1000f89b 	mulne	r0, fp, r8
d001f55c:	d112292d 	tstle	r2, sp, lsr #18
d001f560:	44784887 	ldrbtmi	r4, [r8], #-2183	; 0xfffff779
d001f564:	9b02e7b0 	blls	0xd00d942c
d001f568:	780858f9 	stmdavc	r8, {r0, r3, r4, r5, r6, r7, fp, ip, lr}
d001f56c:	d001282d 	andle	r2, r1, sp, lsr #16
d001f570:	d9022d0f 	stmdble	r2, {r0, r1, r2, r3, r8, sl, fp, sp}
d001f574:	44784883 	ldrbtmi	r4, [r8], #-2179	; 0xfffff77d
d001f578:	ab16e7a6 	blge	0xd05d9418
d001f57c:	0085eb03 	addeq	lr, r5, r3, lsl #22
d001f580:	f8403501 			; <UNDEFINED> instruction: 0xf8403501
d001f584:	f1091c40 			; <UNDEFINED> instruction: 0xf1091c40
d001f588:	45a10901 	strmi	r0, [r1, #2305]!	; 0x901
d001f58c:	b985dbbc 	stmiblt	r5, {r2, r3, r4, r5, r7, r8, r9, fp, ip, lr, pc}
d001f590:	4478487d 	ldrbtmi	r4, [r8], #-2173	; 0xfffff783
d001f594:	2601e798 			; <UNDEFINED> instruction: 0x2601e798
d001f598:	4b7ce7f5 	blmi	0xd1f59574
d001f59c:	0901f04f 	stmdbeq	r1, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d001f5a0:	a1ecf8df 	ldrdge	pc, [ip, #143]!	; 0x8f
d001f5a4:	447b4635 	ldrbtmi	r4, [fp], #-1589	; 0xfffff9cb
d001f5a8:	44fa46b3 	ldrbtmi	r4, [sl], #1715	; 0x6b3
d001f5ac:	3a10ee08 	bcc	0xd045add4
d001f5b0:	9806e7eb 	stmdals	r6, {r0, r1, r3, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d001f5b4:	e79a2400 	ldr	r2, [sl, r0, lsl #8]
d001f5b8:	48762500 	ldmdami	r6!, {r8, sl, sp}^
d001f5bc:	447846ab 	ldrbtmi	r4, [r8], #-1707	; 0xfffff955
d001f5c0:	f1bbe795 			; <UNDEFINED> instruction: 0xf1bbe795
d001f5c4:	d0290f00 	eorle	r0, r9, r0, lsl #30
d001f5c8:	46584a73 			; <UNDEFINED> instruction: 0x46584a73
d001f5cc:	447a4973 	ldrbtmi	r4, [sl], #-2419	; 0xfffff68d
d001f5d0:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d001f5d4:	2800fc7f 	stmdacs	r0, {r0, r1, r2, r3, r4, r5, r6, sl, fp, ip, sp, lr, pc}
d001f5d8:	4871d093 	ldmdami	r1!, {r0, r1, r4, r7, ip, lr, pc}^
d001f5dc:	f0014478 			; <UNDEFINED> instruction: 0xf0014478
d001f5e0:	38f7fd7d 	ldmcc	r7!, {r0, r2, r3, r4, r5, r6, r8, sl, fp, ip, sp, lr, pc}^
d001f5e4:	7f81f510 	svcvc	0x0081f510
d001f5e8:	2c00d98b 			; <UNDEFINED> instruction: 0x2c00d98b
d001f5ec:	8086f040 	addhi	pc, r6, r0, asr #32
d001f5f0:	46274b6c 	strtmi	r4, [r7], -ip, ror #22
d001f5f4:	a1b0f8df 	asrsge	pc, pc	; <illegal shifter operand>	; <UNPREDICTABLE>
d001f5f8:	f8df447b 			; <UNDEFINED> instruction: 0xf8df447b
d001f5fc:	44fab1b0 	ldrbtmi	fp, [sl], #432	; 0x1b0
d001f600:	44fb601c 	ldrbtmi	r6, [fp], #28
d001f604:	447b4b6a 	ldrbtmi	r4, [fp], #-2922	; 0xfffff496
d001f608:	42ac9302 	adcmi	r9, ip, #134217728	; 0x8000000
d001f60c:	2000d11d 	andcs	sp, r0, sp, lsl r1
d001f610:	fcfef7ff 	ldc2l	7, cr15, [lr], #1020	; 0x3fc
d001f614:	f480fab0 	vst3.32			; <UNDEFINED> instruction: 0xf480fab0
d001f618:	e7580964 	ldrb	r0, [r8, -r4, ror #18]
d001f61c:	f0014640 			; <UNDEFINED> instruction: 0xf0014640
d001f620:	1cc3fd5d 	stclne	13, cr15, [r3], {93}	; 0x5d
d001f624:	7f80f5b3 	svcvc	0x0080f5b3
d001f628:	af6bf63f 	svcge	0x006bf63f
d001f62c:	1e464f61 	cdpne	15, 4, cr4, cr6, cr1, {3}
d001f630:	447f4641 	ldrbtmi	r4, [pc], #-1601	; 0xd001f638
d001f634:	46384632 			; <UNDEFINED> instruction: 0x46384632
d001f638:	f948f000 			; <UNDEFINED> instruction: 0xf948f000
d001f63c:	2204495e 	andcs	r4, r4, #1540096	; 0x178000
d001f640:	447919b8 	ldrbtmi	r1, [r9], #-2488	; 0xfffff648
d001f644:	f942f000 			; <UNDEFINED> instruction: 0xf942f000
d001f648:	9a02e7c7 	bls	0xd00d956c
d001f64c:	f8daab06 			; <UNDEFINED> instruction: 0xf8daab06
d001f650:	46598000 	ldrbmi	r8, [r9], -r0
d001f654:	3024f853 	eorcc	pc, r4, r3, asr r8	; <UNPREDICTABLE>
d001f658:	2908eb02 	stmdbcs	r8, {r1, r8, r9, fp, sp, lr, pc}
d001f65c:	93034618 	movwls	r4, #13848	; 0x3618
d001f660:	f7ff464a 			; <UNDEFINED> instruction: 0xf7ff464a
d001f664:	9b03fc37 	blls	0xd011e748
d001f668:	4c54b948 	mrrcmi	9, 4, fp, r4, cr8	; <UNPREDICTABLE>
d001f66c:	447c4a54 	ldrbtmi	r4, [ip], #-2644	; 0xfffff5ac
d001f670:	f44f447a 	vst3.16	{d20-d22}, [pc :256], sl
d001f674:	462071c0 	strtmi	r7, [r0], -r0, asr #3
d001f678:	fcf8f001 	ldc2l	0, cr15, [r8], #4
d001f67c:	2300e01f 	movwcs	lr, #31
d001f680:	0607eb08 	streq	lr, [r7], -r8, lsl #22
d001f684:	1280f5c7 	addne	pc, r0, #834666496	; 0x31c00000
d001f688:	93054648 	movwls	r4, #22088	; 0x5648
d001f68c:	447b4b4d 	ldrbtmi	r4, [fp], #-2893	; 0xfffff4b3
d001f690:	ab05441e 	blge	0xd0170710
d001f694:	f7ff4631 			; <UNDEFINED> instruction: 0xf7ff4631
d001f698:	4601f8fd 			; <UNDEFINED> instruction: 0x4601f8fd
d001f69c:	1cc3b188 	stfnep	f3, [r3], {136}	; 0x88
d001f6a0:	4849d102 	stmdami	r9, {r1, r8, ip, lr, pc}^
d001f6a4:	e70f4478 	smlsdx	pc, r8, r4, r4	; <UNPREDICTABLE>
d001f6a8:	464b4c48 	strbmi	r4, [fp], -r8, asr #24
d001f6ac:	f44f4a48 	vst1.16	{d20-d21}, [pc], r8
d001f6b0:	447c71c0 	ldrbtmi	r7, [ip], #-448	; 0xfffffe40
d001f6b4:	447a9000 	ldrbtmi	r9, [sl], #-0
d001f6b8:	f0014620 			; <UNDEFINED> instruction: 0xf0014620
d001f6bc:	4620fcd7 			; <UNDEFINED> instruction: 0x4620fcd7
d001f6c0:	9a05e702 	bls	0xd01992d0
d001f6c4:	f0014630 			; <UNDEFINED> instruction: 0xf0014630
d001f6c8:	b128fcf3 	strdlt	pc, [r8, -r3]!
d001f6cc:	464b4c41 	strbmi	r4, [fp], -r1, asr #24
d001f6d0:	447c4a41 	ldrbtmi	r4, [ip], #-2625	; 0xfffff5bf
d001f6d4:	e7cc447a 			; <UNDEFINED> instruction: 0xe7cc447a
d001f6d8:	34014b40 	strcc	r4, [r1], #-2880	; 0xfffff4c0
d001f6dc:	447b9a05 	ldrbtmi	r9, [fp], #-2565	; 0xfffff5fb
d001f6e0:	54b04417 	ldrtpl	r4, [r0], #1047	; 0x417
d001f6e4:	6038f843 	eorsvs	pc, r8, r3, asr #16
d001f6e8:	08c8eb03 	stmiaeq	r8, {r0, r1, r8, r9, fp, sp, lr, pc}^
d001f6ec:	3000f8da 	ldrdcc	pc, [r0], -sl
d001f6f0:	2004f8c8 	andcs	pc, r4, r8, asr #17
d001f6f4:	f8ca3301 			; <UNDEFINED> instruction: 0xf8ca3301
d001f6f8:	e7863000 	str	r3, [r6, r0]
d001f6fc:	23004d38 	movwcs	r4, #3384	; 0xd38
d001f700:	f44f4838 	vst2.8	{d20-d21}, [pc :256], r8
d001f704:	447d1280 	ldrbtmi	r1, [sp], #-640	; 0xfffffd80
d001f708:	44789305 	ldrbtmi	r9, [r8], #-773	; 0xfffffcfb
d001f70c:	4629ab05 	strtmi	sl, [r9], -r5, lsl #22
d001f710:	f8c0f7ff 			; <UNDEFINED> instruction: 0xf8c0f7ff
d001f714:	4601b948 	strmi	fp, [r1], -r8, asr #18
d001f718:	46289a05 	strtmi	r9, [r8], -r5, lsl #20
d001f71c:	fcc8f001 	stc2l	0, cr15, [r8], {1}
d001f720:	9b05b980 	blls	0xd018dd28
d001f724:	200054e8 	andcs	r5, r0, r8, ror #9
d001f728:	2804e008 	stmdacs	r4, {r3, sp, lr, pc}
d001f72c:	492ed10c 	stmdbmi	lr!, {r2, r3, r8, ip, lr, pc}
d001f730:	4628227d 			; <UNDEFINED> instruction: 0x4628227d
d001f734:	f0004479 			; <UNDEFINED> instruction: 0xf0004479
d001f738:	2001f8c9 	andcs	pc, r1, r9, asr #17
d001f73c:	fa14f7ff 	blx	0xd055d740
d001f740:	e6c44604 	strb	r4, [r4], r4, lsl #12
d001f744:	0003f06f 	andeq	pc, r3, pc, rrx
d001f748:	44794928 	ldrbtmi	r4, [r9], #-2344	; 0xfffff6d8
d001f74c:	fb44f7ff 	blx	0xd115d752
d001f750:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001f754:	e7e6aebc 			; <UNDEFINED> instruction: 0xe7e6aebc
d001f758:	f77f2800 			; <UNDEFINED> instruction: 0xf77f2800
d001f75c:	2600aeb3 			; <UNDEFINED> instruction: 0x2600aeb3
d001f760:	bf00e6a9 	svclt	0x0000e6a9
d001f764:	fffffe0a 			; <UNDEFINED> instruction: 0xfffffe0a
d001f768:	fffffdfa 			; <UNDEFINED> instruction: 0xfffffdfa
d001f76c:	fffffdf1 			; <UNDEFINED> instruction: 0xfffffdf1
d001f770:	00353490 	mlaseq	r5, r0, r4, r3
d001f774:	fffffedd 			; <UNDEFINED> instruction: 0xfffffedd
d001f778:	fffffed2 			; <UNDEFINED> instruction: 0xfffffed2
d001f77c:	fffffdc9 			; <UNDEFINED> instruction: 0xfffffdc9
d001f780:	fffffdd5 			; <UNDEFINED> instruction: 0xfffffdd5
d001f784:	fffffdf6 			; <UNDEFINED> instruction: 0xfffffdf6
d001f788:	fffffe0a 			; <UNDEFINED> instruction: 0xfffffe0a
d001f78c:	fffffd56 			; <UNDEFINED> instruction: 0xfffffd56
d001f790:	fffffd8a 			; <UNDEFINED> instruction: 0xfffffd8a
d001f794:	fffffcee 			; <UNDEFINED> instruction: 0xfffffcee
d001f798:	00252116 	eoreq	r2, r5, r6, lsl r1
d001f79c:	fffffe3a 			; <UNDEFINED> instruction: 0xfffffe3a
d001f7a0:	00252108 	eoreq	r2, r5, r8, lsl #2
d001f7a4:	002522f4 	strdeq	r2, [r5], -r4	; <UNPREDICTABLE>
d001f7a8:	002522ee 	eoreq	r2, r5, lr, ror #5
d001f7ac:	fffffdd1 			; <UNDEFINED> instruction: 0xfffffdd1
d001f7b0:	002522ea 	eoreq	r2, r5, sl, ror #5
d001f7b4:	002520b2 	strhteq	r2, [r5], -r2
d001f7b8:	fffffdcd 			; <UNDEFINED> instruction: 0xfffffdcd
d001f7bc:	00353516 	eorseq	r3, r5, r6, lsl r5
d001f7c0:	fffffda3 			; <UNDEFINED> instruction: 0xfffffda3
d001f7c4:	002532e6 	eoreq	r3, r5, r6, ror #5
d001f7c8:	fffffd8a 			; <UNDEFINED> instruction: 0xfffffd8a
d001f7cc:	003534d2 	ldrsbteq	r3, [r5], -r2
d001f7d0:	fffffd96 			; <UNDEFINED> instruction: 0xfffffd96
d001f7d4:	003534b2 	ldrhteq	r3, [r5], -r2
d001f7d8:	fffffd8f 			; <UNDEFINED> instruction: 0xfffffd8f
d001f7dc:	00253212 	eoreq	r3, r5, r2, lsl r2
d001f7e0:	0025326e 	eoreq	r3, r5, lr, ror #4
d001f7e4:	0035327a 	eorseq	r3, r5, sl, ror r2
d001f7e8:	000000b8 	strheq	r0, [r0], -r8
d001f7ec:	fffffd31 			; <UNDEFINED> instruction: 0xfffffd31

Disassembly of section .text.initMalloc:

d001f870 <.text.initMalloc>:
d001f870:	f44f4b06 			; <UNDEFINED> instruction: 0xf44f4b06
d001f874:	4a064180 	bmi	0xd01afe7c
d001f878:	589a447b 	ldmpl	sl, {r0, r1, r3, r4, r5, r6, sl, lr}
d001f87c:	4a056011 	bmi	0xd01778c8
d001f880:	4b05589a 	blmi	0xd0175af0
d001f884:	601a447b 	andsvs	r4, sl, fp, ror r4
d001f888:	bf004770 	svclt	0x00004770
d001f88c:	000018e0 	andeq	r1, r0, r0, ror #17
d001f890:	00000004 	andeq	r0, r0, r4
d001f894:	00000000 	andeq	r0, r0, r0
d001f898:	00353484 	eorseq	r3, r5, r4, lsl #9

Disassembly of section .text.applet_entry:

d001f89c <.text.applet_entry>:
d001f89c:	9101b507 	tstls	r1, r7, lsl #10
d001f8a0:	ffe6f7ff 			; <UNDEFINED> instruction: 0xffe6f7ff
d001f8a4:	b0039901 	andlt	r9, r3, r1, lsl #18
d001f8a8:	eb04f85d 	bl	0xd015da24
d001f8ac:	bdeef7ff 	stcllt	7, cr15, [lr, #1020]!	; 0x3fc

Disassembly of section .text.SBV2_CRC32:

d0010178 <.text.SBV2_CRC32>:
d0010178:	4401b530 	strmi	fp, [r1], #-1328	; 0xfffffad0
d001017c:	33fff04f 	mvnscc	pc, #79	; 0x4f
d0010180:	42884d08 	addmi	r4, r8, #8, 26	; 0x200
d0010184:	43d8d101 	bicsmi	sp, r8, #1073741824	; 0x40000000
d0010188:	f810bd30 			; <UNDEFINED> instruction: 0xf810bd30
d001018c:	40532b01 	subsmi	r2, r3, r1, lsl #22
d0010190:	f0132208 			; <UNDEFINED> instruction: 0xf0132208
d0010194:	bf180401 	svclt	0x00180401
d0010198:	3a01462c 	bcc	0xd0061a50
d001019c:	0353ea84 	cmpeq	r3, #132, 20	; 0x84000
d00101a0:	e7eed1f7 			; <UNDEFINED> instruction: 0xe7eed1f7
d00101a4:	edb88320 	ldc	3, cr8, [r8, #128]!	; 0x80

Disassembly of section .text.error:

d00101a8 <.text.error>:
d00101a8:	b5306d83 	ldrlt	r6, [r0, #-3459]!	; 0xfffff27d
d00101ac:	6a45b94b 	bvs	0xd117e6e0
d00101b0:	6b436a84 	blvs	0xd10eabc8
d00101b4:	2030f890 	mlascs	r0, r0, r8, pc	; <UNPREDICTABLE>
d00101b8:	e9c06683 	stmib	r0, {r0, r1, r7, r9, sl, sp, lr}^
d00101bc:	e9c01516 	stmib	r0, {r1, r2, r4, r8, sl, ip}^
d00101c0:	bd304218 	lfmlt	f4, 4, [r0, #-96]!	; 0xffffffa0

Disassembly of section .text.peek:

d00101c4 <.text.peek>:
d00101c4:	441968c3 	ldrmi	r6, [r9], #-2243	; 0xfffff73d
d00101c8:	428b6843 	addmi	r6, fp, #4390912	; 0x430000
d00101cc:	6803bf86 	stmdavs	r3, {r1, r2, r7, r8, r9, sl, fp, ip, sp, pc}
d00101d0:	20005c58 	andcs	r5, r0, r8, asr ip
d00101d4:	Address 0x00000000d00101d4 is out of bounds.


Disassembly of section .text.read_char:

d00101d6 <.text.read_char>:
d00101d6:	460268c3 	strmi	r6, [r2], -r3, asr #17
d00101da:	428b6841 	addmi	r6, fp, #4259840	; 0x410000
d00101de:	d016b510 	andsle	fp, r6, r0, lsl r5
d00101e2:	68011c5c 	stmdavs	r1, {r2, r3, r4, r6, sl, fp, ip}
d00101e6:	5ccc60c4 	stclpl	0, cr6, [ip], {196}	; 0xc4
d00101ea:	d0062c0a 	andle	r2, r6, sl, lsl #24
d00101ee:	d10b2c0d 	tstle	fp, sp, lsl #24
d00101f2:	f7ff2100 			; <UNDEFINED> instruction: 0xf7ff2100
d00101f6:	280affe6 	stmdacs	sl, {r1, r2, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d00101fa:	6913d006 	ldmdbvs	r3, {r1, r2, ip, lr, pc}
d00101fe:	61133301 	tstvs	r3, r1, lsl #6
d0010202:	61532301 	cmpvs	r3, r1, lsl #6
d0010206:	bd104620 	ldclt	6, cr4, [r0, #-128]	; 0xffffff80
d001020a:	33016953 	movwcc	r6, #6483	; 0x1953
d001020e:	2400e7f9 	strcs	lr, [r0], #-2041	; 0xfffff807
d0010212:	Address 0x00000000d0010212 is out of bounds.


Disassembly of section .text.here:

d0010214 <.text.here>:
d0010214:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d0010218:	4604680b 	strmi	r6, [r4], -fp, lsl #16
d001021c:	221868cd 	andscs	r6, r8, #13434880	; 0xcd0000
d0010220:	30047a0f 	andcc	r7, r4, pc, lsl #20
d0010224:	6f8b441d 	svcvs	0x008b441d
d0010228:	e9d12b00 	ldmib	r1, {r8, r9, fp, sp}^
d001022c:	bfa89804 	svclt	0x00a89804
d0010230:	f04f6f4e 			; <UNDEFINED> instruction: 0xf04f6f4e
d0010234:	bfb80100 	svclt	0x00b80100
d0010238:	f00f2600 			; <UNDEFINED> instruction: 0xf00f2600
d001023c:	f44ffb39 			; <UNDEFINED> instruction: 0xf44ffb39
d0010240:	46207380 	strtmi	r7, [r0], -r0, lsl #7
d0010244:	f8c46025 			; <UNDEFINED> instruction: 0xf8c46025
d0010248:	f8c4900c 			; <UNDEFINED> instruction: 0xf8c4900c
d001024c:	61638010 	cmnvs	r3, r0, lsl r0
d0010250:	61e67627 	mvnvs	r7, r7, lsr #12
d0010254:	83f8e8bd 	mvnshi	lr, #12386304	; 0xbd0000

Disassembly of section .text.preproc_active:

d0010258 <.text.preproc_active>:
d0010258:	030cf24d 	movweq	pc, #49741	; 0xc24d	; <UNPREDICTABLE>
d001025c:	b14b58c3 	smlalbtlt	r5, fp, r3, r8
d0010260:	534ff503 	movtpl	pc, #62723	; 0xf503	; <UNPREDICTABLE>
d0010264:	eb003321 	bl	0xd001cef0
d0010268:	79400083 	stmdbvc	r0, {r0, r1, r7}^
d001026c:	bf183800 	svclt	0x00183800
d0010270:	47702001 	ldrbmi	r2, [r0, -r1]!
d0010274:	47702001 	ldrbmi	r2, [r0, -r1]!

Disassembly of section .text.pp_space:

d0010278 <.text.pp_space>:
d0010278:	6a436a81 	bvs	0xd10eac84
d001027c:	d204428b 	andle	r4, r4, #-1342177272	; 0xb0000008
d0010280:	2a20781a 	bcs	0xd082e2f0
d0010284:	2a09d002 	bcs	0xd0284294
d0010288:	4770d000 	ldrbmi	sp, [r0, -r0]!
d001028c:	62433301 	subvs	r3, r3, #67108864	; 0x4000000
d0010290:	Address 0x00000000d0010290 is out of bounds.


Disassembly of section .text.pp_line_end:

d0010292 <.text.pp_line_end>:
d0010292:	4604b510 			; <UNDEFINED> instruction: 0x4604b510
d0010296:	686368e2 	stmdavs	r3!, {r1, r5, r6, r7, fp, sp, lr}^
d001029a:	d207429a 	andle	r4, r7, #-1610612727	; 0xa0000009
d001029e:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d00102a2:	ff8ff7ff 			; <UNDEFINED> instruction: 0xff8ff7ff
d00102a6:	d001280d 	andle	r2, r1, sp, lsl #16
d00102aa:	d100280a 	tstle	r0, sl, lsl #16
d00102ae:	4620bd10 			; <UNDEFINED> instruction: 0x4620bd10
d00102b2:	ff90f7ff 			; <UNDEFINED> instruction: 0xff90f7ff
d00102b6:	Address 0x00000000d00102b6 is out of bounds.


Disassembly of section .text.enum_constant_lookup:

d00102b8 <.text.enum_constant_lookup>:
d00102b8:	337ef500 	cmncc	lr, #0, 10	; <UNPREDICTABLE>
d00102bc:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d00102c0:	4190f8d3 			; <UNDEFINED> instruction: 0x4190f8d3
d00102c4:	46062328 	strmi	r2, [r6], -r8, lsr #6
d00102c8:	1e654688 	cdpne	6, 6, cr4, cr5, cr8, {4}
d00102cc:	0404fb03 	streq	pc, [r4], #-2819	; 0xfffff4fd
d00102d0:	f5044617 			; <UNDEFINED> instruction: 0xf5044617
d00102d4:	34683478 	strbtcc	r3, [r8], #-1144	; 0xfffffb88
d00102d8:	da022d00 	ble	0xd009b6e0
d00102dc:	35fff04f 	ldrbcc	pc, [pc, #79]!	; 0xd0010333	; <UNPREDICTABLE>
d00102e0:	f894e011 			; <UNDEFINED> instruction: 0xf894e011
d00102e4:	7a332024 	bvc	0xd0cd837c
d00102e8:	d002429a 	mulle	r2, sl, r2
d00102ec:	3c283d01 	stccc	13, cr3, [r8], #-4
d00102f0:	6863e7f2 	stmdavs	r3!, {r1, r4, r5, r6, r7, r8, r9, sl, sp, lr, pc}^
d00102f4:	d1f942bb 	ldrhle	r4, [r9, #43]!	; 0x2b
d00102f8:	4641463a 			; <UNDEFINED> instruction: 0x4641463a
d00102fc:	f00f6820 			; <UNDEFINED> instruction: 0xf00f6820
d0010300:	2800faf5 	stmdacs	r0, {r0, r2, r4, r5, r6, r7, r9, fp, ip, sp, lr, pc}
d0010304:	4628d1f2 			; <UNDEFINED> instruction: 0x4628d1f2
d0010308:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d

Disassembly of section .text.pp_take:

d001030c <.text.pp_take>:
d001030c:	460eb570 			; <UNDEFINED> instruction: 0x460eb570
d0010310:	f7ff4604 			; <UNDEFINED> instruction: 0xf7ff4604
d0010314:	4630ffb1 			; <UNDEFINED> instruction: 0x4630ffb1
d0010318:	fee0f010 	mcr2	0, 7, pc, cr0, cr0, {0}	; <UNPREDICTABLE>
d001031c:	46056aa3 	strmi	r6, [r5], -r3, lsr #21
d0010320:	1a1b6a60 	bne	0xd06eaca8
d0010324:	d20142ab 	andle	r4, r1, #-1342177270	; 0xb000000a
d0010328:	bd702000 	ldcllt	0, cr2, [r0, #-0]
d001032c:	4631462a 	ldrtmi	r4, [r1], -sl, lsr #12
d0010330:	fadcf00f 	blx	0xcf74c374
d0010334:	d1f72800 	mvnsle	r2, r0, lsl #16
d0010338:	44286a60 	strtmi	r6, [r8], #-2656	; 0xfffff5a0
d001033c:	20016260 	andcs	r6, r1, r0, ror #4
d0010340:	Address 0x00000000d0010340 is out of bounds.


Disassembly of section .text.macro_index:

d0010342 <.text.macro_index>:
d0010342:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d0010346:	462bf500 	strtmi	pc, [fp], -r0, lsl #10
d001034a:	444ff500 	strbmi	pc, [pc], #-1280	; 0xd0010352	; <UNPREDICTABLE>
d001034e:	46174688 	ldrmi	r4, [r7], -r8, lsl #13
d0010352:	25003688 	strcs	r3, [r0, #-1672]	; 0xfffff978
d0010356:	68233488 	stmdavs	r3!, {r3, r7, sl, ip, sp}
d001035a:	d80242ab 	stmdale	r2, {r0, r1, r3, r5, r7, r9, lr}
d001035e:	30fff04f 	rscscc	pc, pc, pc, asr #32
d0010362:	4630e00b 	ldrtmi	lr, [r0], -fp
d0010366:	feb9f010 	mrc2	0, 5, pc, cr9, cr0, {0}
d001036a:	d10842b8 			; <UNDEFINED> instruction: 0xd10842b8
d001036e:	4641463a 			; <UNDEFINED> instruction: 0x4641463a
d0010372:	f00f4630 			; <UNDEFINED> instruction: 0xf00f4630
d0010376:	b910faba 	ldmdblt	r0, {r1, r3, r4, r5, r7, r9, fp, ip, sp, lr, pc}
d001037a:	e8bd4628 	pop	{r3, r5, r9, sl, lr}
d001037e:	350181f0 	strcc	r8, [r1, #-496]	; 0xfffffe10
d0010382:	e7e83648 	strb	r3, [r8, r8, asr #12]!

Disassembly of section .text.letter:

d0010386 <.text.letter>:
d0010386:	0320f020 	nopeq	{32}
d001038a:	2b193b41 	blcs	0xd065f096
d001038e:	f1a0d904 			; <UNDEFINED> instruction: 0xf1a0d904
d0010392:	4258035f 	subsmi	r0, r8, #2080374785	; 0x7c000001
d0010396:	47704158 			; <UNDEFINED> instruction: 0x47704158
d001039a:	47702001 	ldrbmi	r2, [r0, -r1]!

Disassembly of section .text.valid_api_name:

d00103a4 <.text.valid_api_name>:
d00103a4:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d00103a8:	46884606 	strmi	r4, [r8], r6, lsl #12
d00103ac:	b19a4617 	orrslt	r4, sl, r7, lsl r6
d00103b0:	2204491a 	andcs	r4, r4, #425984	; 0x68000
d00103b4:	f00f4479 			; <UNDEFINED> instruction: 0xf00f4479
d00103b8:	bb58fa99 	bllt	0xd164ee24
d00103bc:	5d302404 	cfldrspl	mvf2, [r0, #-16]!
d00103c0:	ffe1f7ff 			; <UNDEFINED> instruction: 0xffe1f7ff
d00103c4:	2500b330 	strcs	fp, [r0, #-816]	; 0xfffffcd0
d00103c8:	b93a5d32 	ldmdblt	sl!, {r1, r4, r5, r8, sl, fp, ip, lr}
d00103cc:	1e28b327 	cdpne	3, 2, cr11, cr8, cr7, {1}
d00103d0:	2001bf18 	andcs	fp, r1, r8, lsl pc
d00103d4:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d00103d8:	e7f04614 			; <UNDEFINED> instruction: 0xe7f04614
d00103dc:	2a2db197 	bcs	0xd0b7ca40
d00103e0:	1ca3d110 	stfned	f5, [r3], #64	; 0x40
d00103e4:	d20d4543 	andle	r4, sp, #281018368	; 0x10c00000
d00103e8:	5c701c61 	ldclpl	12, cr1, [r0], #-388	; 0xfffffe7c
d00103ec:	d109283e 	tstle	r9, lr, lsr r8
d00103f0:	f7ff5cf0 			; <UNDEFINED> instruction: 0xf7ff5cf0
d00103f4:	b128ffc8 	smlawtlt	r8, r8, pc, pc	; <UNPREDICTABLE>
d00103f8:	460c3501 	strmi	r3, [ip], -r1, lsl #10
d00103fc:	45a03401 	strmi	r3, [r0, #1025]!	; 0x401
d0010400:	e007d8e2 	and	sp, r7, r2, ror #17
d0010404:	f7ff4610 			; <UNDEFINED> instruction: 0xf7ff4610
d0010408:	2800ffbe 	stmdacs	r0, {r1, r2, r3, r4, r5, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d001040c:	3a30d1f6 	bcc	0xd0c44bec
d0010410:	d9f32a09 	ldmible	r3!, {r0, r3, r9, fp, sp}^
d0010414:	e7dd2000 	ldrb	r2, [sp, r0]
d0010418:	e7db2001 	ldrb	r2, [fp, r1]
d001041c:	ffffffe6 			; <UNDEFINED> instruction: 0xffffffe6

Disassembly of section .text.hex_digit:

d0010420 <.text.hex_digit>:
d0010420:	38304603 	ldmdacc	r0!, {r0, r1, r9, sl, lr}
d0010424:	d9082809 	stmdble	r8, {r0, r3, fp, sp}
d0010428:	0020f043 	eoreq	pc, r0, r3, asr #32
d001042c:	0361f1a0 	msreq	SPSR_c, #160, 2	; 0x28
d0010430:	d8012b05 	stmdale	r1, {r0, r2, r8, r9, fp, sp}
d0010434:	47703857 			; <UNDEFINED> instruction: 0x47703857
d0010438:	47702010 			; <UNDEFINED> instruction: 0x47702010

Disassembly of section .text.escape_byte.isra.0:

d0010474 <.text.escape_byte.isra.0>:
d0010474:	47f0e92d 	ldrbmi	lr, [r0, sp, lsr #18]!
d0010478:	46059e09 	strmi	r9, [r5], -r9, lsl #28
d001047c:	f8dd461f 			; <UNDEFINED> instruction: 0xf8dd461f
d0010480:	6830a020 	ldmdavs	r0!, {r5, sp, pc}
d0010484:	8028f8dd 	ldrdhi	pc, [r8], -sp	; <UNPREDICTABLE>
d0010488:	60331c43 	eorsvs	r1, r3, r3, asr #24
d001048c:	2c787804 	ldclcs	8, cr7, [r8], #-16
d0010490:	2c6dd812 	stclcs	8, cr13, [sp], #-72	; 0xffffffb8
d0010494:	2c3fd828 	ldccs	8, cr13, [pc], #-160	; 0xd00103fc
d0010498:	2c21d84e 	stccs	8, cr13, [r1], #-312	; 0xfffffec8
d001049c:	f1a4d90c 			; <UNDEFINED> instruction: 0xf1a4d90c
d00104a0:	fa5f0c22 	blx	0xd17d3530
d00104a4:	f04ffe8c 			; <UNDEFINED> instruction: 0xf04ffe8c
d00104a8:	fa0c0c01 	blx	0xd03134b4
d00104ac:	f8dffc0e 			; <UNDEFINED> instruction: 0xf8dffc0e
d00104b0:	ea1ce160 	b	0xd0748a38
d00104b4:	d13a0f0e 	teqle	sl, lr, lsl #30
d00104b8:	2c073c30 	stccs	12, cr3, [r7], {48}	; 0x30
d00104bc:	4543d86a 	strbmi	sp, [r3, #-2154]	; 0xfffff796
d00104c0:	7843d035 	stmdavc	r3, {r0, r2, r4, r5, ip, lr, pc}^
d00104c4:	2b073b30 	blcs	0xd01df18c
d00104c8:	f100d831 			; <UNDEFINED> instruction: 0xf100d831
d00104cc:	f8c60c02 			; <UNDEFINED> instruction: 0xf8c60c02
d00104d0:	45e0c000 	strbmi	ip, [r0, #0]!
d00104d4:	f1a37843 			; <UNDEFINED> instruction: 0xf1a37843
d00104d8:	eb030330 	bl	0xd00d11a0
d00104dc:	f04004c4 			; <UNDEFINED> instruction: 0xf04004c4
d00104e0:	2cff8086 	ldclcs	0, cr8, [pc], #536	; 0xd0010700
d00104e4:	e022d856 	eor	sp, r2, r6, asr r8
d00104e8:	0c6ef1a4 	stfeqp	f7, [lr], #-656	; 0xfffffd70
d00104ec:	0f0af1bc 	svceq	0x000af1bc
d00104f0:	f20fd8e2 	vadd.i8	<illegal reg q6.5>, <illegal reg q15.5>, q9
d00104f4:	f85e0e0c 			; <UNDEFINED> instruction: 0xf85e0e0c
d00104f8:	44e6c02c 	strbtmi	ip, [r6], #44	; 0x2c
d00104fc:	bf004770 	svclt	0x00004770
d0010500:	00000107 	andeq	r0, r0, r7, lsl #2
d0010504:	ffffffb9 			; <UNDEFINED> instruction: 0xffffffb9
d0010508:	ffffffb9 			; <UNDEFINED> instruction: 0xffffffb9
d001050c:	ffffffb9 			; <UNDEFINED> instruction: 0xffffffb9
d0010510:	0000002d 	andeq	r0, r0, sp, lsr #32
d0010514:	ffffffb9 			; <UNDEFINED> instruction: 0xffffffb9
d0010518:	00000089 	andeq	r0, r0, r9, lsl #1
d001051c:	ffffffb9 			; <UNDEFINED> instruction: 0xffffffb9
d0010520:	0000008d 	andeq	r0, r0, sp, lsl #1
d0010524:	ffffffb9 			; <UNDEFINED> instruction: 0xffffffb9
d0010528:	00000091 	muleq	r0, r1, r0
d001052c:	4620240d 	strtmi	r2, [r0], -sp, lsl #8
d0010530:	87f0e8bd 			; <UNDEFINED> instruction: 0x87f0e8bd
d0010534:	e7fa2408 	ldrb	r2, [sl, r8, lsl #8]!
d0010538:	0c5cf1a4 	ldfeqp	f7, [ip], {164}	; 0xa4
d001053c:	fe8cfa5f 	mcr2	10, 4, pc, cr12, cr15, {2}	; <UNPREDICTABLE>
d0010540:	0f0af1be 	svceq	0x000af1be
d0010544:	f1bcd8b8 			; <UNDEFINED> instruction: 0xf1bcd8b8
d0010548:	d8b50f0a 	ldmle	r5!, {r1, r3, r8, r9, sl, fp}
d001054c:	0e08f20f 	cdpeq	2, 0, cr15, cr8, cr15, {0}
d0010550:	c02cf85e 	eorgt	pc, ip, lr, asr r8	; <UNPREDICTABLE>
d0010554:	477044e6 	ldrbmi	r4, [r0, -r6, ror #9]!
d0010558:	ffffffd7 			; <UNDEFINED> instruction: 0xffffffd7
d001055c:	ffffff61 			; <UNDEFINED> instruction: 0xffffff61
d0010560:	ffffff61 			; <UNDEFINED> instruction: 0xffffff61
d0010564:	ffffff61 			; <UNDEFINED> instruction: 0xffffff61
d0010568:	ffffff61 			; <UNDEFINED> instruction: 0xffffff61
d001056c:	000000b3 	strheq	r0, [r0], -r3
d0010570:	ffffffdd 			; <UNDEFINED> instruction: 0xffffffdd
d0010574:	ffffff61 			; <UNDEFINED> instruction: 0xffffff61
d0010578:	ffffff61 			; <UNDEFINED> instruction: 0xffffff61
d001057c:	ffffff61 			; <UNDEFINED> instruction: 0xffffff61
d0010580:	0000002d 	andeq	r0, r0, sp, lsr #32
d0010584:	e7d2240c 	ldrb	r2, [r2, ip, lsl #8]
d0010588:	e7d02409 	ldrb	r2, [r0, r9, lsl #8]
d001058c:	e7ce240b 	strb	r2, [lr, fp, lsl #8]
d0010590:	d1044543 	tstle	r4, r3, asr #10
d0010594:	b9fc6dac 	ldmiblt	ip!, {r2, r3, r5, r7, r8, sl, fp, sp, lr}^
d0010598:	447b4b1e 	ldrbtmi	r4, [fp], #-2846	; 0xfffff4e2
d001059c:	7840e020 	stmdavc	r0, {r5, sp, lr, pc}^
d00105a0:	ff3ef7ff 			; <UNDEFINED> instruction: 0xff3ef7ff
d00105a4:	d0f52810 	rscsle	r2, r5, r0, lsl r8
d00105a8:	f8d62400 			; <UNDEFINED> instruction: 0xf8d62400
d00105ac:	45c89000 	strbmi	r9, [r8]
d00105b0:	f899d0bd 			; <UNDEFINED> instruction: 0xf899d0bd
d00105b4:	f7ff0000 			; <UNDEFINED> instruction: 0xf7ff0000
d00105b8:	2810ff33 	ldmdacs	r0, {r0, r1, r4, r5, r8, r9, sl, fp, ip, sp, lr, pc}
d00105bc:	f109d0b7 			; <UNDEFINED> instruction: 0xf109d0b7
d00105c0:	01240301 			; <UNDEFINED> instruction: 0x01240301
d00105c4:	f8996033 			; <UNDEFINED> instruction: 0xf8996033
d00105c8:	f7ff0000 			; <UNDEFINED> instruction: 0xf7ff0000
d00105cc:	4404ff29 	strmi	pc, [r4], #-3881	; 0xfffff0d7
d00105d0:	d9ea2cff 	stmible	sl!, {r0, r1, r2, r3, r4, r5, r6, r7, sl, fp, sp}^
d00105d4:	b10c6dac 	smlatblt	ip, ip, sp, r6
d00105d8:	e7a82400 	str	r2, [r8, r0, lsl #8]!
d00105dc:	447b4b0e 	ldrbtmi	r4, [fp], #-2830	; 0xfffff4f2
d00105e0:	a068f8c5 	rsbge	pc, r8, r5, asr #17
d00105e4:	3116e9c5 	tstcc	r6, r5, asr #19
d00105e8:	2718e9c5 	ldrcs	lr, [r8, -r5, asr #19]
d00105ec:	7883e79f 	stmvc	r3, {r0, r1, r2, r3, r4, r7, r8, r9, sl, sp, lr, pc}
d00105f0:	2b073b30 	blcs	0xd01df2b8
d00105f4:	af75f63f 	svcge	0x0075f63f
d00105f8:	60331cc3 	eorsvs	r1, r3, r3, asr #25
d00105fc:	3b307883 	blcc	0xd0c2e810
d0010600:	04c4eb03 	strbeq	lr, [r4], #2819	; 0xb03
d0010604:	240ae76d 	strcs	lr, [sl], #-1901	; 0xfffff893
d0010608:	2407e791 	strcs	lr, [r7], #-1937	; 0xfffff86f
d001060c:	bf00e78f 	svclt	0x0000e78f
d0010610:	20000021 	andcs	r0, r0, r1, lsr #32
d0010614:	fffffeb6 			; <UNDEFINED> instruction: 0xfffffeb6
d0010618:	fffffe5a 			; <UNDEFINED> instruction: 0xfffffe5a

Disassembly of section .text.same_name.isra.0:

d001061c <.text.same_name.isra.0>:
d001061c:	460cb510 			; <UNDEFINED> instruction: 0x460cb510
d0010620:	429c4611 	addsmi	r4, ip, #17825792	; 0x1100000
d0010624:	4622d106 	strtmi	sp, [r2], -r6, lsl #2
d0010628:	f960f00f 			; <UNDEFINED> instruction: 0xf960f00f
d001062c:	f080fab0 			; <UNDEFINED> instruction: 0xf080fab0
d0010630:	bd100940 	vldrlt.16	s0, [r0, #-128]	; 0xffffff80	; <UNPREDICTABLE>
d0010634:	e7fc2000 	ldrb	r2, [ip, r0]!

Disassembly of section .text.find_record.isra.0:

d0010638 <.text.find_record.isra.0>:
d0010638:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d001063c:	3467f500 	strbtcc	pc, [r7], #-1280	; 0xfffffb00	; <UNPREDICTABLE>
d0010640:	4690460f 	ldrmi	r4, [r0], pc, lsl #12
d0010644:	f5042500 			; <UNDEFINED> instruction: 0xf5042500
d0010648:	f50074e4 			; <UNDEFINED> instruction: 0xf50074e4
d001064c:	fa5f3675 	blx	0xd17de028
d0010650:	f8d6f983 			; <UNDEFINED> instruction: 0xf8d6f983
d0010654:	429d3388 	addsmi	r3, sp, #136, 6	; 0x20000002
d0010658:	f04fd302 			; <UNDEFINED> instruction: 0xf04fd302
d001065c:	e00e30ff 	strd	r3, [lr], -pc	; <UNPREDICTABLE>
d0010660:	3264f894 	rsbcc	pc, r4, #148, 16	; 0x940000
d0010664:	4643b96b 	strbmi	fp, [r3], -fp, ror #18
d0010668:	e9d4463a 	ldmib	r4, {r1, r3, r4, r5, r9, sl, lr}^
d001066c:	f7ff0100 			; <UNDEFINED> instruction: 0xf7ff0100
d0010670:	b130ffd5 	teqlt	r0, r5	; <illegal shifter operand>	; <UNPREDICTABLE>
d0010674:	3263f894 	rsbcc	pc, r3, #148, 16	; 0x940000
d0010678:	d102454b 	tstle	r2, fp, asr #10
d001067c:	e8bd4628 	pop	{r3, r5, r9, sl, lr}
d0010680:	350183f8 	strcc	r8, [r1, #-1016]	; 0xfffffc08
d0010684:	741af504 	ldrvc	pc, [sl], #-1284	; 0xfffffafc
d0010688:	Address 0x00000000d0010688 is out of bounds.


Disassembly of section .text.records_equal:

d001068a <.text.records_equal>:
d001068a:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d001068e:	3260f8d0 	rsbcc	pc, r0, #208, 16	; 0xd00000
d0010692:	f0234606 			; <UNDEFINED> instruction: 0xf0234606
d0010696:	f8d1427f 			; <UNDEFINED> instruction: 0xf8d1427f
d001069a:	f0233260 			; <UNDEFINED> instruction: 0xf0233260
d001069e:	429a437f 	addsmi	r4, sl, #-67108863	; 0xfc000001
d00106a2:	2000d002 	andcs	sp, r0, r2
d00106a6:	83f8e8bd 	mvnshi	lr, #12386304	; 0xbd0000
d00106aa:	2263f890 	rsbcs	pc, r3, #144, 16	; 0x900000
d00106ae:	3263f891 	rsbcc	pc, r3, #9502720	; 0x910000
d00106b2:	d1f6429a 			; <UNDEFINED> instruction: 0xd1f6429a
d00106b6:	460c4605 	strmi	r4, [ip], -r5, lsl #12
d00106ba:	f8962700 			; <UNDEFINED> instruction: 0xf8962700
d00106be:	429f3262 	addsmi	r3, pc, #536870918	; 0x20000006
d00106c2:	2001d301 	andcs	sp, r1, r1, lsl #6
d00106c6:	6a63e7ee 	bvs	0xd190a686
d00106ca:	6a2246a9 	bvs	0xd08a2176
d00106ce:	6a6946a0 	bvs	0xd1a62156
d00106d2:	f7ff6a28 			; <UNDEFINED> instruction: 0xf7ff6a28
d00106d6:	2800ffa2 	stmdacs	r0, {r1, r5, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d00106da:	f895d0e3 			; <UNDEFINED> instruction: 0xf895d0e3
d00106de:	f8942040 			; <UNDEFINED> instruction: 0xf8942040
d00106e2:	429a3040 	addsmi	r3, sl, #64	; 0x40
d00106e6:	f895d1dd 			; <UNDEFINED> instruction: 0xf895d1dd
d00106ea:	f8942041 			; <UNDEFINED> instruction: 0xf8942041
d00106ee:	429a3041 	addsmi	r3, sl, #65	; 0x41
d00106f2:	f8b9d1d7 			; <UNDEFINED> instruction: 0xf8b9d1d7
d00106f6:	35242042 	strcc	r2, [r4, #-66]!	; 0xffffffbe
d00106fa:	3042f8b8 	strhcc	pc, [r2], #-136	; 0xffffff78	; <UNPREDICTABLE>
d00106fe:	429a3424 	addsmi	r3, sl, #36, 8	; 0x24000000
d0010702:	3701d1cf 	strcc	sp, [r1, -pc, asr #3]
d0010706:	Address 0x00000000d0010706 is out of bounds.


Disassembly of section .text.find_local.isra.0:

d0010708 <.text.find_local.isra.0>:
d0010708:	e92d4b0e 	push	{r1, r2, r3, r8, r9, fp, lr}
d001070c:	58c641f0 	stmiapl	r6, {r4, r5, r6, r7, r8, lr}^
d0010710:	460f2530 			; <UNDEFINED> instruction: 0x460f2530
d0010714:	fb054690 	blx	0xd016215e
d0010718:	f5000006 			; <UNDEFINED> instruction: 0xf5000006
d001071c:	f20414a4 	vshl.s8	d1, d20, d20
d0010720:	b9166404 	ldmdblt	r6, {r2, sl, sp, lr}
d0010724:	30fff04f 	rscscc	pc, pc, pc, asr #32
d0010728:	6861e00a 	stmdavs	r1!, {r1, r3, sp, lr, pc}^
d001072c:	463a4643 	ldrtmi	r4, [sl], -r3, asr #12
d0010730:	0930f854 	ldmdbeq	r0!, {r2, r4, r6, fp, ip, sp, lr, pc}
d0010734:	f7ff3e01 			; <UNDEFINED> instruction: 0xf7ff3e01
d0010738:	2800ff71 	stmdacs	r0, {r0, r4, r5, r6, r8, r9, sl, fp, ip, sp, lr, pc}
d001073c:	4630d0f1 			; <UNDEFINED> instruction: 0x4630d0f1
d0010740:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d0010744:	00149234 	andseq	r9, r4, r4, lsr r2

Disassembly of section .text.find_global.isra.0:

d0010748 <.text.find_global.isra.0>:
d0010748:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d001074c:	355ff500 	ldrbcc	pc, [pc, #-1280]	; 0xd0010254	; <UNPREDICTABLE>
d0010750:	460f4606 	strmi	r4, [pc], -r6, lsl #12
d0010754:	f5054690 			; <UNDEFINED> instruction: 0xf5054690
d0010758:	24007571 	strcs	r7, [r0], #-1393	; 0xfffffa8f
d001075c:	3967f500 	stmdbcc	r7!, {r8, sl, ip, sp, lr, pc}^
d0010760:	31c4f8d9 	ldrdcc	pc, [r4, #137]	; 0x89
d0010764:	d302429c 	movwle	r4, #8860	; 0x229c
d0010768:	30fff04f 	rscscc	pc, pc, pc, asr #32
d001076c:	f895e00c 			; <UNDEFINED> instruction: 0xf895e00c
d0010770:	7a332029 	bvc	0xd0cd881c
d0010774:	d109429a 			; <UNDEFINED> instruction: 0xd109429a
d0010778:	463a4643 	ldrtmi	r4, [sl], -r3, asr #12
d001077c:	0100e9d5 	ldrdeq	lr, [r0, -r5]
d0010780:	ff4cf7ff 			; <UNDEFINED> instruction: 0xff4cf7ff
d0010784:	4620b110 			; <UNDEFINED> instruction: 0x4620b110
d0010788:	83f8e8bd 	mvnshi	lr, #12386304	; 0xbd0000
d001078c:	353c3401 	ldrcc	r3, [ip, #-1025]!	; 0xfffffbff
d0010790:	Address 0x00000000d0010790 is out of bounds.


Disassembly of section .text.find_alias.isra.0:

d0010792 <.text.find_alias.isra.0>:
d0010792:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d0010796:	3575f500 	ldrbcc	pc, [r5, #-1280]!	; 0xfffffb00	; <UNPREDICTABLE>
d001079a:	460f4606 	strmi	r4, [pc], -r6, lsl #12
d001079e:	f5054690 			; <UNDEFINED> instruction: 0xf5054690
d00107a2:	24007563 	strcs	r7, [r0], #-1379	; 0xfffffa9d
d00107a6:	3978f500 	ldmdbcc	r8!, {r8, sl, ip, sp, lr, pc}^
d00107aa:	308cf8d9 	ldrdcc	pc, [ip], r9
d00107ae:	d302429c 	movwle	r4, #8860	; 0x229c
d00107b2:	30fff04f 	rscscc	pc, pc, pc, asr #32
d00107b6:	f895e00c 			; <UNDEFINED> instruction: 0xf895e00c
d00107ba:	7a332021 	bvc	0xd0cd8846
d00107be:	d109429a 			; <UNDEFINED> instruction: 0xd109429a
d00107c2:	463a4643 	ldrtmi	r4, [sl], -r3, asr #12
d00107c6:	0100e9d5 	ldrdeq	lr, [r0, -r5]
d00107ca:	ff27f7ff 			; <UNDEFINED> instruction: 0xff27f7ff
d00107ce:	4620b110 			; <UNDEFINED> instruction: 0x4620b110
d00107d2:	83f8e8bd 	mvnshi	lr, #12386304	; 0xbd0000
d00107d6:	35243401 	strcc	r3, [r4, #-1025]!	; 0xfffffbff
d00107da:	Address 0x00000000d00107da is out of bounds.


Disassembly of section .text.is_record_type:

d00107dc <.text.is_record_type>:
d00107dc:	f46f6ac3 	vld1.64	{d22-d23}, [pc], r3
d00107e0:	189a728b 	ldmne	sl, {r0, r1, r3, r7, r9, ip, sp, lr}
d00107e4:	b5102a01 	ldrlt	r2, [r0, #-2561]	; 0xfffff5ff
d00107e8:	d8014604 	stmdale	r1, {r2, r9, sl, lr}
d00107ec:	bd102001 	ldclt	0, cr2, [r0, #-4]
d00107f0:	1201f240 	andne	pc, r1, #64, 4
d00107f4:	d10e4293 			; <UNDEFINED> instruction: 0xd10e4293
d00107f8:	698169c2 	stmibvs	r1, {r1, r6, r7, r8, fp, sp, lr}
d00107fc:	ffc9f7ff 			; <UNDEFINED> instruction: 0xffc9f7ff
d0010800:	db081e03 	blle	0xd0218014
d0010804:	fb002024 	blx	0xd001889e
d0010808:	f5004003 			; <UNDEFINED> instruction: 0xf5004003
d001080c:	f8903075 			; <UNDEFINED> instruction: 0xf8903075
d0010810:	2bff33ac 	blcs	0xcffdd6c8
d0010814:	2000d1ea 	andcs	sp, r0, sl, ror #3
d0010818:	Address 0x00000000d0010818 is out of bounds.


Disassembly of section .text.find_function.isra.0:

d001081c <.text.find_function.isra.0>:
d001081c:	47f0e92d 	ldrbmi	lr, [r0, sp, lsr #18]!
d0010820:	46064c12 			; <UNDEFINED> instruction: 0x46064c12
d0010824:	8048f8df 	ldrdhi	pc, [r8], #-143	; 0xffffff71
d0010828:	46924689 	ldrmi	r4, [r2], r9, lsl #13
d001082c:	25004404 	strcs	r4, [r0, #-1028]	; 0xfffffbfc
d0010830:	37fff04f 	ldrbcc	pc, [pc, pc, asr #32]!	; <UNPREDICTABLE>
d0010834:	f8d84480 			; <UNDEFINED> instruction: 0xf8d84480
d0010838:	429d3000 	addsmi	r3, sp, #0
d001083c:	4653d20f 	ldrbmi	sp, [r3], -pc, lsl #4
d0010840:	e9d4464a 	ldmib	r4, {r1, r3, r6, r9, sl, lr}^
d0010844:	f7ff0100 			; <UNDEFINED> instruction: 0xf7ff0100
d0010848:	b160fee9 	msrlt	(UNDEF: 96), r9
d001084c:	3028f894 	mlacc	r8, r4, r8, pc	; <UNPREDICTABLE>
d0010850:	f894b143 			; <UNDEFINED> instruction: 0xf894b143
d0010854:	7a332029 	bvc	0xd0cd8900
d0010858:	d104429a 			; <UNDEFINED> instruction: 0xd104429a
d001085c:	4638462f 	ldrtmi	r4, [r8], -pc, lsr #12
d0010860:	87f0e8bd 			; <UNDEFINED> instruction: 0x87f0e8bd
d0010864:	3501462f 	strcc	r4, [r1, #-1583]	; 0xfffff9d1
d0010868:	e7e43438 			; <UNDEFINED> instruction: 0xe7e43438
d001086c:	0013fe24 	andseq	pc, r3, r4, lsr #28
d0010870:	00143624 	andseq	r3, r4, r4, lsr #12

Disassembly of section .text.name_is.isra.0:

d0010874 <.text.name_is.isra.0>:
d0010874:	460db537 			; <UNDEFINED> instruction: 0x460db537
d0010878:	46104604 	ldrmi	r4, [r0], -r4, lsl #12
d001087c:	f0109201 			; <UNDEFINED> instruction: 0xf0109201
d0010880:	42a8fc2d 	adcmi	pc, r8, #11520	; 0x2d00
d0010884:	99014602 	stmdbls	r1, {r1, r9, sl, lr}
d0010888:	4620d107 	strtmi	sp, [r0], -r7, lsl #2
d001088c:	f82ef00f 			; <UNDEFINED> instruction: 0xf82ef00f
d0010890:	f080fab0 			; <UNDEFINED> instruction: 0xf080fab0
d0010894:	b0030940 	andlt	r0, r3, r0, asr #18
d0010898:	2000bd30 	andcs	fp, r0, r0, lsr sp
d001089c:	Address 0x00000000d001089c is out of bounds.


Disassembly of section .text.find_api_call.isra.0:

d001089e <.text.find_api_call.isra.0>:
d001089e:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d00108a2:	4550f500 	ldrbmi	pc, [r0, #-1280]	; 0xfffffb00	; <UNPREDICTABLE>
d00108a6:	4450f500 	ldrbmi	pc, [r0], #-1280	; 0xfffffb00	; <UNPREDICTABLE>
d00108aa:	4690460f 	ldrmi	r4, [r0], pc, lsl #12
d00108ae:	26003524 	strcs	r3, [r0], -r4, lsr #10
d00108b2:	6823341c 	stmdavs	r3!, {r2, r3, r4, sl, ip, sp}
d00108b6:	d304429e 	movwle	r4, #17054	; 0x429e
d00108ba:	0900f04f 	stmdbeq	r0, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d00108be:	e8bd4648 	pop	{r3, r6, r9, sl, lr}
d00108c2:	462a83f8 			; <UNDEFINED> instruction: 0x462a83f8
d00108c6:	46384641 	ldrtmi	r4, [r8], -r1, asr #12
d00108ca:	f7ff46a9 			; <UNDEFINED> instruction: 0xf7ff46a9
d00108ce:	3554ffd2 	ldrbcc	pc, [r4, #-4050]	; 0xfffff02e	; <UNPREDICTABLE>
d00108d2:	d1f32800 	mvnsle	r2, r0, lsl #16
d00108d6:	e7ec3601 	strb	r3, [ip, r1, lsl #12]!

Disassembly of section .text.find_api_constant.isra.0:

d00108da <.text.find_api_constant.isra.0>:
d00108da:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d00108de:	3582f500 	strcc	pc, [r2, #1280]	; 0x500
d00108e2:	4450f500 	ldrbmi	pc, [r0], #-1280	; 0xfffffb00	; <UNPREDICTABLE>
d00108e6:	4690460f 	ldrmi	r4, [r0], pc, lsl #12
d00108ea:	260035a4 	strcs	r3, [r0], -r4, lsr #11
d00108ee:	68233420 	stmdavs	r3!, {r5, sl, ip, sp}
d00108f2:	d304429e 	movwle	r4, #17054	; 0x429e
d00108f6:	0900f04f 	stmdbeq	r0, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d00108fa:	e8bd4648 	pop	{r3, r6, r9, sl, lr}
d00108fe:	462a83f8 			; <UNDEFINED> instruction: 0x462a83f8
d0010902:	46384641 	ldrtmi	r4, [r8], -r1, asr #12
d0010906:	f7ff46a9 			; <UNDEFINED> instruction: 0xf7ff46a9
d001090a:	3524ffb4 	strcc	pc, [r4, #-4020]!	; 0xfffff04c
d001090e:	d1f32800 	mvnsle	r2, r0, lsl #16
d0010912:	e7ec3601 	strb	r3, [ip, r1, lsl #12]!

Disassembly of section .text.pp_unary:

d001092c <.text.pp_unary>:
d001092c:	e92d6ac3 	push	{r0, r1, r6, r7, r9, fp, sp, lr}
d0010930:	1c5a43f7 	mrrcne	3, 15, r4, sl, cr7
d0010934:	2a204604 	bcs	0xd082214c
d0010938:	d90962c2 	stmdble	r9, {r1, r6, r7, r9, sp, lr}
d001093c:	26002201 	strcs	r2, [r0], -r1, lsl #4
d0010940:	62c32700 	sbcvs	r2, r3, #0, 14
d0010944:	46306302 	ldrtmi	r6, [r0], -r2, lsl #6
d0010948:	b0034639 	andlt	r4, r3, r9, lsr r6
d001094c:	83f0e8bd 	mvnshi	lr, #12386304	; 0xbd0000
d0010950:	44794986 	ldrbtmi	r4, [r9], #-2438	; 0xfffff67a
d0010954:	fcdaf7ff 	ldc2l	7, cr15, [sl], {255}	; 0xff
d0010958:	4620b148 	strtmi	fp, [r0], -r8, asr #2
d001095c:	ffe6f7ff 			; <UNDEFINED> instruction: 0xffe6f7ff
d0010960:	0301ea50 	movweq	lr, #6736	; 0x1a50
d0010964:	2601bf0c 	strcs	fp, [r1], -ip, lsl #30
d0010968:	27002600 	strcs	r2, [r0, -r0, lsl #12]
d001096c:	4980e00a 	stmibmi	r0, {r1, r3, sp, lr, pc}
d0010970:	44794620 	ldrbtmi	r4, [r9], #-1568	; 0xfffff9e0
d0010974:	fccaf7ff 	stc2l	7, cr15, [sl], {255}	; 0xff
d0010978:	4620b140 	strtmi	fp, [r0], -r0, asr #2
d001097c:	ffd6f7ff 			; <UNDEFINED> instruction: 0xffd6f7ff
d0010980:	43cf43c6 	bicmi	r4, pc, #402653187	; 0x18000003
d0010984:	3b016ae3 	blcc	0xd006b518
d0010988:	e7dc62e3 	ldrb	r6, [ip, r3, ror #5]
d001098c:	46204979 			; <UNDEFINED> instruction: 0x46204979
d0010990:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d0010994:	b128fcbb 	msrlt	CPSR_f, fp	; <illegal shifter operand>
d0010998:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d001099c:	4606ffc7 	strmi	pc, [r6], -r7, asr #31
d00109a0:	e7ef460f 	strb	r4, [pc, pc, lsl #12]!
d00109a4:	46204974 			; <UNDEFINED> instruction: 0x46204974
d00109a8:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d00109ac:	b130fcaf 	teqlt	r0, pc, lsr #25	; <UNPREDICTABLE>
d00109b0:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d00109b4:	4246ffbb 	submi	pc, r6, #748	; 0x2ec
d00109b8:	0741eb61 	strbeq	lr, [r1, -r1, ror #22]
d00109bc:	4620e7e2 	strtmi	lr, [r0], -r2, ror #15
d00109c0:	fc5af7ff 	mrrc2	7, 15, pc, sl, cr15	; <UNPREDICTABLE>
d00109c4:	1c5a6ae3 	mrrcne	10, 14, r6, sl, cr3
d00109c8:	62e22a20 	rscvs	r2, r2, #32, 20	; 0x20000
d00109cc:	2201d904 	andcs	sp, r1, #4, 18	; 0x10000
d00109d0:	62e32600 	rscvs	r2, r3, #0, 12
d00109d4:	e7c86322 	strb	r6, [r8, r2, lsr #6]
d00109d8:	44794968 	ldrbtmi	r4, [r9], #-2408	; 0xfffff698
d00109dc:	fc96f7ff 	ldc2	7, cr15, [r6], {255}	; 0xff
d00109e0:	4620b168 	strtmi	fp, [r0], -r8, ror #2
d00109e4:	fb3cf000 	blx	0xd0f4c9ee
d00109e8:	4965460f 	stmdbmi	r5!, {r0, r1, r2, r3, r9, sl, lr}^
d00109ec:	44794606 	ldrbtmi	r4, [r9], #-1542	; 0xfffff9fa
d00109f0:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d00109f4:	bba0fc8b 	bllt	0xce84fc28
d00109f8:	63232301 			; <UNDEFINED> instruction: 0x63232301
d00109fc:	6a65e031 	bvs	0xd1988ac8
d0010a00:	8028f8d4 	ldrdhi	pc, [r8], -r4	; <UNPREDICTABLE>
d0010a04:	d2514545 	subsle	r4, r1, #289406976	; 0x11400000
d0010a08:	f1a07828 			; <UNDEFINED> instruction: 0xf1a07828
d0010a0c:	2b090330 	blcs	0xd02516d4
d0010a10:	eba8d849 	bl	0xcea46b3c
d0010a14:	2b020305 	blcs	0xd0091630
d0010a18:	2830dd27 	ldmdacs	r0!, {r0, r1, r2, r5, r8, sl, fp, ip, lr, pc}
d0010a1c:	786bd12a 	stmdavc	fp!, {r1, r3, r5, r8, ip, lr, pc}^
d0010a20:	03dff003 	bicseq	pc, pc, #3
d0010a24:	d1272b58 			; <UNDEFINED> instruction: 0xd1272b58
d0010a28:	21103502 	tstcs	r0, r2, lsl #10
d0010a2c:	25006265 	strcs	r6, [r0, #-613]	; 0xfffffd9b
d0010a30:	27002600 	strcs	r2, [r0, -r0, lsl #12]
d0010a34:	0901f04f 	stmdbeq	r1, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d0010a38:	45906a62 	ldrmi	r6, [r0, #2658]	; 0xa62
d0010a3c:	8092f240 	addshi	pc, r2, r0, asr #4
d0010a40:	f7ff7810 			; <UNDEFINED> instruction: 0xf7ff7810
d0010a44:	4281fced 	addmi	pc, r1, #60672	; 0xed00
d0010a48:	b91dd818 	ldmdblt	sp, {r3, r4, fp, ip, lr, pc}
d0010a4c:	45902301 	ldrmi	r2, [r0, #769]	; 0x301
d0010a50:	d9066323 	stmdble	r6, {r0, r1, r5, r8, r9, sp, lr}
d0010a54:	f0037813 			; <UNDEFINED> instruction: 0xf0037813
d0010a58:	2b5503df 	blcs	0xd15519dc
d0010a5c:	3201d101 	andcc	sp, r1, #1073741824	; 0x40000000
d0010a60:	6ae36262 	bvs	0xcf8e93f0
d0010a64:	62e33b01 	rscvs	r3, r3, #1024	; 0x400
d0010a68:	2830e78c 	ldmdacs	r0!, {r2, r3, r7, r8, r9, sl, sp, lr, pc}
d0010a6c:	210abf14 	tstcs	sl, r4, lsl pc
d0010a70:	e7dc2108 	ldrb	r2, [ip, r8, lsl #2]
d0010a74:	e7da210a 	ldrb	r2, [sl, sl, lsl #2]
d0010a78:	e7d82108 	ldrb	r2, [r8, r8, lsl #2]
d0010a7c:	35011c53 	strcc	r1, [r1, #-3155]	; 0xfffff3ad
d0010a80:	78106263 	ldmdavc	r0, {r0, r1, r5, r6, r9, sp, lr}
d0010a84:	fcccf7ff 	stc2l	7, cr15, [ip], {255}	; 0xff
d0010a88:	fbb343c3 	blx	0xcece199e
d0010a8c:	42b3f3f1 	adcsmi	pc, r3, #-1006632957	; 0xc4000003
d0010a90:	2306fba1 	movwcs	pc, #27553	; 0x6ba1	; <UNPREDICTABLE>
d0010a94:	f8c4bf38 			; <UNDEFINED> instruction: 0xf8c4bf38
d0010a98:	18169030 	ldmdane	r6, {r4, r5, ip, pc}
d0010a9c:	3307fb01 	movwcc	pc, #31489	; 0x7b01	; <UNPREDICTABLE>
d0010aa0:	0700f143 	streq	pc, [r0, -r3, asr #2]
d0010aa4:	f7ffe7c8 			; <UNDEFINED> instruction: 0xf7ffe7c8
d0010aa8:	b930fc6e 	ldmdblt	r0!, {r1, r2, r3, r5, r6, sl, fp, ip, sp, lr, pc}
d0010aac:	63232301 			; <UNDEFINED> instruction: 0x63232301
d0010ab0:	27002600 	strcs	r2, [r0, -r0, lsl #12]
d0010ab4:	3201e7d5 	andcc	lr, r1, #55836672	; 0x3540000
d0010ab8:	6a626262 	bvs	0xd18a9448
d0010abc:	d9084590 	stmdble	r8, {r4, r7, r8, sl, lr}
d0010ac0:	46087811 			; <UNDEFINED> instruction: 0x46087811
d0010ac4:	fc5ff7ff 	mrrc2	7, 15, pc, pc, cr15	; <UNPREDICTABLE>
d0010ac8:	d1f42800 	mvnsle	r2, r0, lsl #16
d0010acc:	29093930 	stmdbcs	r9, {r4, r5, r8, fp, ip, sp}
d0010ad0:	1b52d9f1 	blne	0xd14c729c
d0010ad4:	d1362a07 	teqle	r6, r7, lsl #20
d0010ad8:	4628492a 	strtmi	r4, [r8], -sl, lsr #18
d0010adc:	44799201 	ldrbtmi	r9, [r9], #-513	; 0xfffffdff
d0010ae0:	ff04f00e 			; <UNDEFINED> instruction: 0xff04f00e
d0010ae4:	bb709a01 	bllt	0xd1c372f0
d0010ae8:	46204927 	strtmi	r4, [r0], -r7, lsr #18
d0010aec:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d0010af0:	4680fc0d 	strmi	pc, [r0], sp, lsl #24
d0010af4:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010af8:	6a61fbbf 	bvs	0xd188f9fc
d0010afc:	42b16aa6 	adcsmi	r6, r1, #679936	; 0xa6000
d0010b00:	7808d003 	stmdavc	r8, {r0, r1, ip, lr, pc}
d0010b04:	fc3ff7ff 	ldc2	7, cr15, [pc], #-1020	; 0xd0010710
d0010b08:	2301b908 	movwcs	fp, #6408	; 0x1908
d0010b0c:	6a626323 	bvs	0xd18a97a0
d0010b10:	d9074296 	stmdble	r7, {r1, r2, r4, r7, r9, lr}
d0010b14:	46287815 			; <UNDEFINED> instruction: 0x46287815
d0010b18:	fc35f7ff 	ldc2	7, cr15, [r5], #-1020	; 0xfffffc04
d0010b1c:	3d30b980 			; <UNDEFINED> instruction: 0x3d30b980
d0010b20:	d90d2d09 	stmdble	sp, {r0, r3, r8, sl, fp, sp}
d0010b24:	68201a52 	stmdavs	r0!, {r1, r4, r6, r9, fp, ip}
d0010b28:	fc0bf7ff 	stc2	7, cr15, [fp], {255}	; 0xff
d0010b2c:	17c12700 	strbne	r2, [r1, r0, lsl #14]
d0010b30:	0ff643ce 	svceq	0x00f643ce
d0010b34:	0f00f1b8 	svceq	0x0000f1b8
d0010b38:	4914d093 	ldmdbmi	r4, {r0, r1, r4, r7, ip, lr, pc}
d0010b3c:	e7574479 			; <UNDEFINED> instruction: 0xe7574479
d0010b40:	62623201 	rsbvs	r3, r2, #268435456	; 0x10000000
d0010b44:	4629e7e3 	strtmi	lr, [r9], -r3, ror #15
d0010b48:	f7ff6820 			; <UNDEFINED> instruction: 0xf7ff6820
d0010b4c:	2800fbfa 	stmdacs	r0, {r1, r3, r4, r5, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d0010b50:	6823dbae 	stmdavs	r3!, {r1, r2, r3, r5, r7, r8, r9, fp, ip, lr, pc}
d0010b54:	fb022248 	blx	0xd009947e
d0010b58:	f5003000 			; <UNDEFINED> instruction: 0xf5003000
d0010b5c:	e9d0402b 	ldmib	r0, {r0, r1, r3, r5, lr}^
d0010b60:	e77e6732 			; <UNDEFINED> instruction: 0xe77e6732
d0010b64:	f47f2d00 			; <UNDEFINED> instruction: 0xf47f2d00
d0010b68:	e76faf7c 			; <UNDEFINED> instruction: 0xe76faf7c
d0010b6c:	ffffffc0 			; <UNDEFINED> instruction: 0xffffffc0
d0010b70:	ffffffa2 			; <UNDEFINED> instruction: 0xffffffa2
d0010b74:	ffffff86 			; <UNDEFINED> instruction: 0xffffff86
d0010b78:	ffffff70 			; <UNDEFINED> instruction: 0xffffff70
d0010b7c:	ffffff40 			; <UNDEFINED> instruction: 0xffffff40
d0010b80:	ffffff2e 			; <UNDEFINED> instruction: 0xffffff2e
d0010b84:	fffffe40 			; <UNDEFINED> instruction: 0xfffffe40
d0010b88:	fffffe2e 			; <UNDEFINED> instruction: 0xfffffe2e
d0010b8c:	fffffde0 			; <UNDEFINED> instruction: 0xfffffde0

Disassembly of section .text.pp_mul:

d0010b98 <.text.pp_mul>:
d0010b98:	4ff0e92d 	svcmi	0x00f0e92d
d0010b9c:	8b02ed2d 	blhi	0xd00cc058
d0010ba0:	4606b089 	strmi	fp, [r6], -r9, lsl #1
d0010ba4:	fec2f7ff 	mcr2	7, 6, pc, cr2, cr15, {7}	; <UNPREDICTABLE>
d0010ba8:	46044b67 	strmi	r4, [r4], -r7, ror #22
d0010bac:	447b460d 	ldrbtmi	r4, [fp], #-1549	; 0xfffff9f3
d0010bb0:	3a10ee08 	bcc	0xd044c3d8
d0010bb4:	447b4b65 	ldrbtmi	r4, [fp], #-2917	; 0xfffff49b
d0010bb8:	3a90ee08 	bcc	0xce44c3e0
d0010bbc:	1a10ee18 	bne	0xd044c424
d0010bc0:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0010bc4:	b178fba3 	cmnlt	r8, r3, lsr #23	; <UNPREDICTABLE>
d0010bc8:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0010bcc:	4361feaf 	msrmi	SPSR_c, #2800	; 0xaf0
d0010bd0:	3400fba4 	strcc	pc, [r0], #-2980	; 0xfffff45c
d0010bd4:	1105fb00 	tstne	r5, r0, lsl #22	; <UNPREDICTABLE>
d0010bd8:	3400e9cd 	strcc	lr, [r0], #-2509	; 0xfffff633
d0010bdc:	440b9b01 	strmi	r9, [fp], #-2817	; 0xfffff4ff
d0010be0:	e9dd9301 	ldmib	sp, {r0, r8, r9, ip, pc}^
d0010be4:	e7e94500 	strb	r4, [r9, r0, lsl #10]!
d0010be8:	1a90ee18 	bne	0xce44c450
d0010bec:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0010bf0:	9006fb8d 	andls	pc, r6, sp, lsl #23
d0010bf4:	4956b938 	ldmdbmi	r6, {r3, r4, r5, r8, fp, ip, sp, pc}^
d0010bf8:	44794630 	ldrbtmi	r4, [r9], #-1584	; 0xfffff9d0
d0010bfc:	fb86f7ff 	blx	0xce1cec02
d0010c00:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d0010c04:	46308099 			; <UNDEFINED> instruction: 0x46308099
d0010c08:	fe90f7ff 	mrc2	7, 4, pc, cr0, cr15, {7}
d0010c0c:	0100e9cd 	smlabteq	r0, sp, r9, lr
d0010c10:	2300e9dd 	movwcs	lr, #2525	; 0x9dd
d0010c14:	d1094313 	tstle	r9, r3, lsl r3
d0010c18:	29006b71 	stmdbcs	r0, {r0, r4, r5, r6, r8, r9, fp, sp, lr}
d0010c1c:	2301d0e1 	movwcs	sp, #4321	; 0x10e1
d0010c20:	63332400 	teqvs	r3, #0, 8
d0010c24:	e9cd2300 	stmib	sp, {r8, r9, sp}^
d0010c28:	e7da3400 	ldrb	r3, [sl, r0, lsl #8]
d0010c2c:	f1752c00 			; <UNDEFINED> instruction: 0xf1752c00
d0010c30:	e9cd0300 	stmib	sp, {r8, r9}^
d0010c34:	da044502 	ble	0xd0122044
d0010c38:	eb654262 	bl	0xd19615c8
d0010c3c:	e9cd0345 	stmib	sp, {r0, r2, r6, r8, r9}^
d0010c40:	e9dd2302 	ldmib	sp, {r1, r8, r9, sp}^
d0010c44:	2a002300 	bcs	0xd001984c
d0010c48:	2304e9cd 	movwcs	lr, #18893	; 0x49cd
d0010c4c:	0300f173 	movweq	pc, #371	; 0x173	; <UNPREDICTABLE>
d0010c50:	e9ddda06 	ldmib	sp, {r1, r2, r9, fp, ip, lr, pc}^
d0010c54:	42522300 	subsmi	r2, r2, #0, 6
d0010c58:	0343eb63 	movteq	lr, #15203	; 0x3b63
d0010c5c:	2304e9cd 	movwcs	lr, #18893	; 0x49cd
d0010c60:	0a00f04f 	beq	0xd004cda4
d0010c64:	0b00f04f 	bleq	0xd004cda8
d0010c68:	f04f213f 			; <UNDEFINED> instruction: 0xf04f213f
d0010c6c:	46570c01 	ldrbmi	r0, [r7], -r1, lsl #24
d0010c70:	eb1a46d8 	bl	0xd06a27d8
d0010c74:	f1c1030a 			; <UNDEFINED> instruction: 0xf1c1030a
d0010c78:	f1a10920 			; <UNDEFINED> instruction: 0xf1a10920
d0010c7c:	461a0e20 	ldrmi	r0, [sl], -r0, lsr #28
d0010c80:	030beb4b 	movweq	lr, #47947	; 0xbb4b
d0010c84:	9b029307 	blls	0xd00b58a8
d0010c88:	b01cf8dd 			; <UNDEFINED> instruction: 0xb01cf8dd
d0010c8c:	f001fa23 			; <UNDEFINED> instruction: 0xf001fa23
d0010c90:	fa039b03 	blx	0xd00f78a4
d0010c94:	fa23f909 	blx	0xd090f0c0
d0010c98:	ea40fe0e 	b	0xd10504d8
d0010c9c:	ea400009 	b	0xd1010cc8
d0010ca0:	f1a1000e 			; <UNDEFINED> instruction: 0xf1a1000e
d0010ca4:	f0000e20 			; <UNDEFINED> instruction: 0xf0000e20
d0010ca8:	ea400001 	b	0xd1010cb4
d0010cac:	f1c10a02 			; <UNDEFINED> instruction: 0xf1c10a02
d0010cb0:	e9dd0020 	ldmib	sp, {r5}^
d0010cb4:	459b2304 	ldrmi	r2, [fp, #772]	; 0x304
d0010cb8:	4592bf08 	ldrmi	fp, [r2, #3848]	; 0xf08
d0010cbc:	fa0cd313 	blx	0xd0345910
d0010cc0:	fa2cfe0e 	blx	0xd0b50500
d0010cc4:	9b04f000 	blls	0xd014cccc
d0010cc8:	0000ea4e 	andeq	lr, r0, lr, asr #20
d0010ccc:	fe01fa0c 	vseleq.f32	s30, s2, s24
d0010cd0:	0a03ebba 	beq	0xd010bbc0
d0010cd4:	ea4e9b05 	b	0xd13b78f0
d0010cd8:	ea400e07 	b	0xd10144fc
d0010cdc:	eb6b0008 	bl	0xd1ad0d04
d0010ce0:	46770b03 	ldrbtmi	r0, [r7], -r3, lsl #22
d0010ce4:	39014680 	stmdbcc	r1, {r7, r9, sl, lr}
d0010ce8:	9b06d2c3 	blls	0xd01c57fc
d0010cec:	9b01b1c3 	blls	0xd007d400
d0010cf0:	0fdb0fea 	svceq	0x00db0fea
d0010cf4:	7fd5ebb3 	svcvc	0x00d5ebb3
d0010cf8:	f04fbf15 			; <UNDEFINED> instruction: 0xf04fbf15
d0010cfc:	f06f4100 			; <UNDEFINED> instruction: 0xf06f4100
d0010d00:	20004100 	andcs	r4, r0, r0, lsl #2
d0010d04:	30fff04f 	rscscc	pc, pc, pc, asr #32
d0010d08:	bf084541 	svclt	0x00084541
d0010d0c:	d38642b8 	orrle	r4, r6, #184, 4	; 0x8000000b
d0010d10:	d002429a 	mulle	r2, sl, r2
d0010d14:	eb68427f 	bl	0xd1a21718
d0010d18:	e9cd0848 	stmib	sp, {r3, r6, fp}^
d0010d1c:	e7607800 	strb	r7, [r0, -r0, lsl #16]!
d0010d20:	f1752c00 			; <UNDEFINED> instruction: 0xf1752c00
d0010d24:	e9cd0300 	stmib	sp, {r8, r9}^
d0010d28:	f6bfab00 			; <UNDEFINED> instruction: 0xf6bfab00
d0010d2c:	f1daaf5a 			; <UNDEFINED> instruction: 0xf1daaf5a
d0010d30:	eb6b0300 	bl	0xd1ad1938
d0010d34:	e776044b 	ldrb	r0, [r6, -fp, asr #8]!
d0010d38:	46294620 	strtmi	r4, [r9], -r0, lsr #12
d0010d3c:	ecbdb009 	ldc	0, cr11, [sp], #36	; 0x24
d0010d40:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d0010d44:	bf008ff0 	svclt	0x00008ff0
d0010d48:	ffffffde 			; <UNDEFINED> instruction: 0xffffffde
d0010d4c:	ffffffd8 			; <UNDEFINED> instruction: 0xffffffd8
d0010d50:	ffffff96 			; <UNDEFINED> instruction: 0xffffff96

Disassembly of section .text.pp_add:

d0010d54 <.text.pp_add>:
d0010d54:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d0010d58:	46064f12 			; <UNDEFINED> instruction: 0x46064f12
d0010d5c:	8048f8df 	ldrdhi	pc, [r8], #-143	; 0xffffff71
d0010d60:	ff1af7ff 			; <UNDEFINED> instruction: 0xff1af7ff
d0010d64:	4604447f 			; <UNDEFINED> instruction: 0x4604447f
d0010d68:	44f8460d 	ldrbtmi	r4, [r8], #1549	; 0x60d
d0010d6c:	46304639 			; <UNDEFINED> instruction: 0x46304639
d0010d70:	faccf7ff 	blx	0xcf34ed74
d0010d74:	4630b130 			; <UNDEFINED> instruction: 0x4630b130
d0010d78:	ff0ef7ff 			; <UNDEFINED> instruction: 0xff0ef7ff
d0010d7c:	eb411824 	bl	0xd1056e14
d0010d80:	e7f30505 	ldrb	r0, [r3, r5, lsl #10]!
d0010d84:	46304641 	ldrtmi	r4, [r0], -r1, asr #12
d0010d88:	fac0f7ff 	blx	0xcf04ed8c
d0010d8c:	4630b130 			; <UNDEFINED> instruction: 0x4630b130
d0010d90:	ff02f7ff 			; <UNDEFINED> instruction: 0xff02f7ff
d0010d94:	eb651a24 	bl	0xd195762c
d0010d98:	e7e70501 	strb	r0, [r7, r1, lsl #10]!
d0010d9c:	46294620 	strtmi	r4, [r9], -r0, lsr #12
d0010da0:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d0010da4:	fffffbb2 			; <UNDEFINED> instruction: 0xfffffbb2
d0010da8:	fffffbae 			; <UNDEFINED> instruction: 0xfffffbae

Disassembly of section .text.pp_shift:

d0010db4 <.text.pp_shift>:
d0010db4:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d0010db8:	805cf8df 	ldrsbhi	pc, [ip], #-143	; 0xffffff71	; <UNPREDICTABLE>
d0010dbc:	f8df4604 			; <UNDEFINED> instruction: 0xf8df4604
d0010dc0:	f7ff905c 			; <UNDEFINED> instruction: 0xf7ff905c
d0010dc4:	44f8ffc7 	ldrbtmi	pc, [r8], #4039	; 0xfc7	; <UNPREDICTABLE>
d0010dc8:	460e4605 	strmi	r4, [lr], -r5, lsl #12
d0010dcc:	464144f9 			; <UNDEFINED> instruction: 0x464144f9
d0010dd0:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010dd4:	b160fa9b 	msrlt	(UNDEF: 96), fp
d0010dd8:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010ddc:	2900ffbb 	stmdbcs	r0, {r0, r1, r3, r4, r5, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0010de0:	2820bf08 	stmdacs	r0!, {r3, r8, r9, sl, fp, ip, sp, pc}
d0010de4:	2301d302 	movwcs	sp, #4866	; 0x1302
d0010de8:	e7f06323 	ldrb	r6, [r0, r3, lsr #6]!
d0010dec:	26004085 	strcs	r4, [r0], -r5, lsl #1
d0010df0:	4649e7ed 	strbmi	lr, [r9], -sp, ror #15
d0010df4:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010df8:	b140fa89 	smlalbblt	pc, r0, r9, sl	; <UNPREDICTABLE>
d0010dfc:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010e00:	2900ffa9 	stmdbcs	r0, {r0, r3, r5, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0010e04:	2820bf08 	stmdacs	r0!, {r3, r8, r9, sl, fp, ip, sp, pc}
d0010e08:	40c5d2ed 	sbcmi	sp, r5, sp, ror #5
d0010e0c:	4628e7ef 	strtmi	lr, [r8], -pc, ror #15
d0010e10:	e8bd4631 	pop	{r0, r4, r5, r9, sl, lr}
d0010e14:	bf0083f8 	svclt	0x000083f8
d0010e18:	ffffffe2 			; <UNDEFINED> instruction: 0xffffffe2
d0010e1c:	ffffffdf 			; <UNDEFINED> instruction: 0xffffffdf

Disassembly of section .text.pp_rel:

d0010e2c <.text.pp_rel>:
d0010e2c:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d0010e30:	46064f24 	strmi	r4, [r6], -r4, lsr #30
d0010e34:	8090f8df 			; <UNDEFINED> instruction: 0x8090f8df
d0010e38:	ffbcf7ff 			; <UNDEFINED> instruction: 0xffbcf7ff
d0010e3c:	908cf8df 	ldrdls	pc, [ip], pc	; <UNPREDICTABLE>
d0010e40:	460d4604 	strmi	r4, [sp], -r4, lsl #12
d0010e44:	44f8447f 	ldrbtmi	r4, [r8], #1151	; 0x47f
d0010e48:	463944f9 			; <UNDEFINED> instruction: 0x463944f9
d0010e4c:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0010e50:	b158fa5d 	cmplt	r8, sp, asr sl	; <UNPREDICTABLE>
d0010e54:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0010e58:	42a0ffad 	adcmi	pc, r0, #692	; 0x2b4
d0010e5c:	0305eb71 	movweq	lr, #23409	; 0x5b71
d0010e60:	2401bfac 	strcs	fp, [r1], #-4012	; 0xfffff054
d0010e64:	b2e42400 	rsclt	r2, r4, #0, 8
d0010e68:	e7ee2500 	strb	r2, [lr, r0, lsl #10]!
d0010e6c:	46304641 	ldrtmi	r4, [r0], -r1, asr #12
d0010e70:	fa4cf7ff 	blx	0xd134ee74
d0010e74:	4630b130 			; <UNDEFINED> instruction: 0x4630b130
d0010e78:	ff9cf7ff 			; <UNDEFINED> instruction: 0xff9cf7ff
d0010e7c:	eb754284 	bl	0xd1d61894
d0010e80:	e7ed0301 	strb	r0, [sp, r1, lsl #6]!
d0010e84:	46304649 	ldrtmi	r4, [r0], -r9, asr #12
d0010e88:	fa40f7ff 	blx	0xd104ee8c
d0010e8c:	4630b148 	ldrtmi	fp, [r0], -r8, asr #2
d0010e90:	ff90f7ff 			; <UNDEFINED> instruction: 0xff90f7ff
d0010e94:	eb754284 	bl	0xd1d618ac
d0010e98:	bfb40301 	svclt	0x00b40301
d0010e9c:	24002401 	strcs	r2, [r0], #-1025	; 0xfffffbff
d0010ea0:	490be7e1 	stmdbmi	fp, {r0, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d0010ea4:	44794630 	ldrbtmi	r4, [r9], #-1584	; 0xfffff9d0
d0010ea8:	fa30f7ff 	blx	0xd0c4eeac
d0010eac:	4630b130 			; <UNDEFINED> instruction: 0x4630b130
d0010eb0:	ff80f7ff 			; <UNDEFINED> instruction: 0xff80f7ff
d0010eb4:	eb7142a0 	bl	0xd1c6193c
d0010eb8:	e7ee0305 	strb	r0, [lr, r5, lsl #6]!
d0010ebc:	46294620 	strtmi	r4, [r9], -r0, lsr #12
d0010ec0:	83f8e8bd 	mvnshi	lr, #12386304	; 0xbd0000
d0010ec4:	ffffffd8 			; <UNDEFINED> instruction: 0xffffffd8
d0010ec8:	ffffffd9 			; <UNDEFINED> instruction: 0xffffffd9
d0010ecc:	ffffffda 			; <UNDEFINED> instruction: 0xffffffda
d0010ed0:	ffffff7e 			; <UNDEFINED> instruction: 0xffffff7e

Disassembly of section .text.pp_eq:

d0010edc <.text.pp_eq>:
d0010edc:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d0010ee0:	46064f15 			; <UNDEFINED> instruction: 0x46064f15
d0010ee4:	8054f8df 	ldrsbhi	pc, [r4], #-143	; 0xffffff71	; <UNPREDICTABLE>
d0010ee8:	ffa0f7ff 			; <UNDEFINED> instruction: 0xffa0f7ff
d0010eec:	4604447f 			; <UNDEFINED> instruction: 0x4604447f
d0010ef0:	44f8460d 	ldrbtmi	r4, [r8], #1549	; 0x60d
d0010ef4:	46304639 			; <UNDEFINED> instruction: 0x46304639
d0010ef8:	fa08f7ff 	blx	0xd024eefc
d0010efc:	4630b150 			; <UNDEFINED> instruction: 0x4630b150
d0010f00:	ff94f7ff 			; <UNDEFINED> instruction: 0xff94f7ff
d0010f04:	bf0642a9 	svclt	0x000642a9
d0010f08:	240142a0 	strcs	r4, [r1], #-672	; 0xfffffd60
d0010f0c:	b2e42400 	rsclt	r2, r4, #0, 8
d0010f10:	e7ef2500 	strb	r2, [pc, r0, lsl #10]!
d0010f14:	46304641 	ldrtmi	r4, [r0], -r1, asr #12
d0010f18:	f9f8f7ff 			; <UNDEFINED> instruction: 0xf9f8f7ff
d0010f1c:	4630b140 	ldrtmi	fp, [r0], -r0, asr #2
d0010f20:	ff84f7ff 			; <UNDEFINED> instruction: 0xff84f7ff
d0010f24:	bf0a42a9 	svclt	0x000a42a9
d0010f28:	240142a0 	strcs	r4, [r1], #-672	; 0xfffffd60
d0010f2c:	e7ee2400 	strb	r2, [lr, r0, lsl #8]!
d0010f30:	46294620 	strtmi	r4, [r9], -r0, lsr #12
d0010f34:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d0010f38:	ffffffe4 			; <UNDEFINED> instruction: 0xffffffe4
d0010f3c:	ffffffe1 			; <UNDEFINED> instruction: 0xffffffe1

Disassembly of section .text.pp_band:

d0010f40 <.text.pp_band>:
d0010f40:	4604b570 			; <UNDEFINED> instruction: 0x4604b570
d0010f44:	ffcaf7ff 			; <UNDEFINED> instruction: 0xffcaf7ff
d0010f48:	460d4606 	strmi	r4, [sp], -r6, lsl #12
d0010f4c:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010f50:	6a63f993 	bvs	0xd190f5a4
d0010f54:	428b6aa1 	addmi	r6, fp, #659456	; 0xa1000
d0010f58:	781ad20f 	ldmdavc	sl, {r0, r1, r2, r3, r9, ip, lr, pc}
d0010f5c:	d10c2a26 	tstle	ip, r6, lsr #20
d0010f60:	42911c5a 	addsmi	r1, r1, #23040	; 0x5a00
d0010f64:	785bd902 	ldmdavc	fp, {r1, r8, fp, ip, lr, pc}^
d0010f68:	d0062b26 	andle	r2, r6, r6, lsr #22
d0010f6c:	62624620 	rsbvs	r4, r2, #32, 12	; 0x2000000
d0010f70:	ffb4f7ff 			; <UNDEFINED> instruction: 0xffb4f7ff
d0010f74:	400d4006 	andmi	r4, sp, r6
d0010f78:	4630e7e8 	ldrtmi	lr, [r0], -r8, ror #15
d0010f7c:	bd704629 	ldcllt	6, cr4, [r0, #-164]!	; 0xffffff5c

Disassembly of section .text.pp_xor:

d0010f84 <.text.pp_xor>:
d0010f84:	4f0ab5f8 	svcmi	0x000ab5f8
d0010f88:	f7ff4606 			; <UNDEFINED> instruction: 0xf7ff4606
d0010f8c:	4605ffd9 			; <UNDEFINED> instruction: 0x4605ffd9
d0010f90:	447f460c 	ldrbtmi	r4, [pc], #-1548	; 0xd0010f98
d0010f94:	46304639 			; <UNDEFINED> instruction: 0x46304639
d0010f98:	f9b8f7ff 			; <UNDEFINED> instruction: 0xf9b8f7ff
d0010f9c:	4628b910 			; <UNDEFINED> instruction: 0x4628b910
d0010fa0:	bdf84621 	ldcllt	6, cr4, [r8, #132]!	; 0x84
d0010fa4:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0010fa8:	4045ffcb 	submi	pc, r5, fp, asr #31
d0010fac:	e7f1404c 	ldrb	r4, [r1, ip, asr #32]!
d0010fb0:	ffffffea 			; <UNDEFINED> instruction: 0xffffffea

Disassembly of section .text.pp_bor:

d0010fb4 <.text.pp_bor>:
d0010fb4:	4604b570 			; <UNDEFINED> instruction: 0x4604b570
d0010fb8:	ffe4f7ff 			; <UNDEFINED> instruction: 0xffe4f7ff
d0010fbc:	460d4606 	strmi	r4, [sp], -r6, lsl #12
d0010fc0:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010fc4:	6a63f959 	bvs	0xd190f530
d0010fc8:	428b6aa1 	addmi	r6, fp, #659456	; 0xa1000
d0010fcc:	781ad20f 	ldmdavc	sl, {r0, r1, r2, r3, r9, ip, lr, pc}
d0010fd0:	d10c2a7c 	tstle	ip, ip, ror sl
d0010fd4:	42911c5a 	addsmi	r1, r1, #23040	; 0x5a00
d0010fd8:	785bd902 	ldmdavc	fp, {r1, r8, fp, ip, lr, pc}^
d0010fdc:	d0062b7c 	andle	r2, r6, ip, ror fp
d0010fe0:	62624620 	rsbvs	r4, r2, #32, 12	; 0x2000000
d0010fe4:	ffcef7ff 			; <UNDEFINED> instruction: 0xffcef7ff
d0010fe8:	430d4306 	movwmi	r4, #54022	; 0xd306
d0010fec:	4630e7e8 	ldrtmi	lr, [r0], -r8, ror #15
d0010ff0:	bd704629 	ldcllt	6, cr4, [r0, #-164]!	; 0xffffff5c

Disassembly of section .text.pp_and:

d0010ff8 <.text.pp_and>:
d0010ff8:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d0010ffc:	46064f16 			; <UNDEFINED> instruction: 0x46064f16
d0011000:	ffd8f7ff 			; <UNDEFINED> instruction: 0xffd8f7ff
d0011004:	460d4604 	strmi	r4, [sp], -r4, lsl #12
d0011008:	4639447f 			; <UNDEFINED> instruction: 0x4639447f
d001100c:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0011010:	b918f97d 	ldmdblt	r8, {r0, r2, r3, r4, r5, r6, r8, fp, ip, sp, lr, pc}
d0011014:	46294620 	strtmi	r4, [r9], -r0, lsr #12
d0011018:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d001101c:	8034f8d6 	ldrsbthi	pc, [r4], -r6	; <UNPREDICTABLE>
d0011020:	0f00f1b8 	svceq	0x0000f1b8
d0011024:	ea54d014 	b	0xd154507c
d0011028:	bf140305 	svclt	0x00140305
d001102c:	23002301 	movwcs	r2, #769	; 0x301
d0011030:	46306373 			; <UNDEFINED> instruction: 0x46306373
d0011034:	ffbef7ff 			; <UNDEFINED> instruction: 0xffbef7ff
d0011038:	0305ea54 	movweq	lr, #23124	; 0x5a54
d001103c:	8034f8c6 	eorshi	pc, r4, r6, asr #17
d0011040:	ea50d008 	b	0xd1445068
d0011044:	bf140301 	svclt	0x00140301
d0011048:	24002401 	strcs	r2, [r0], #-1025	; 0xfffffbff
d001104c:	e7dc17e5 	ldrb	r1, [ip, r5, ror #15]
d0011050:	e7ed4643 	strb	r4, [sp, r3, asr #12]!
d0011054:	e7f92400 	ldrb	r2, [r9, r0, lsl #8]!
d0011058:	ffffffe8 			; <UNDEFINED> instruction: 0xffffffe8

Disassembly of section .text.pp_or:

d0011060 <.text.pp_or>:
d0011060:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d0011064:	46064f15 			; <UNDEFINED> instruction: 0x46064f15
d0011068:	ffc6f7ff 			; <UNDEFINED> instruction: 0xffc6f7ff
d001106c:	460d4604 	strmi	r4, [sp], -r4, lsl #12
d0011070:	4639447f 			; <UNDEFINED> instruction: 0x4639447f
d0011074:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0011078:	b918f949 	ldmdblt	r8, {r0, r3, r6, r8, fp, ip, sp, lr, pc}
d001107c:	46294620 	strtmi	r4, [r9], -r0, lsr #12
d0011080:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d0011084:	8034f8d6 	ldrsbthi	pc, [r4], -r6	; <UNPREDICTABLE>
d0011088:	0f00f1b8 	svceq	0x0000f1b8
d001108c:	ea54d014 	b	0xd15450e4
d0011090:	bf0c0305 	svclt	0x000c0305
d0011094:	23002301 	movwcs	r2, #769	; 0x301
d0011098:	46306373 			; <UNDEFINED> instruction: 0x46306373
d001109c:	ffacf7ff 			; <UNDEFINED> instruction: 0xffacf7ff
d00110a0:	43294320 			; <UNDEFINED> instruction: 0x43294320
d00110a4:	8034f8c6 	eorshi	pc, r4, r6, asr #17
d00110a8:	ea502500 	b	0xd141a4b0
d00110ac:	bf140301 	svclt	0x00140301
d00110b0:	24002401 	strcs	r2, [r0], #-1025	; 0xfffffbff
d00110b4:	e7dcb2e4 	ldrb	fp, [ip, r4, ror #5]
d00110b8:	e7ed4643 	strb	r4, [sp, r3, asr #12]!
d00110bc:	ffffffe8 			; <UNDEFINED> instruction: 0xffffffe8

Disassembly of section .text.pp_value:

d00110f0 <.text.pp_value>:
d00110f0:	b5f0b084 	ldrblt	fp, [r0, #132]!	; 0x84
d00110f4:	4606b08f 	strmi	fp, [r6], -pc, lsl #1
d00110f8:	9000ac15 	andls	sl, r0, r5, lsl ip
d00110fc:	9f1ead01 	svcls	0x001ead01
d0011100:	000ee884 	andeq	lr, lr, r4, lsl #17
d0011104:	c50fcc0f 	strgt	ip, [pc, #-3087]	; 0xd00104fd
d0011108:	000fe894 	muleq	pc, r4, r8	; <UNPREDICTABLE>
d001110c:	000fe885 	andeq	lr, pc, r5, lsl #17
d0011110:	466d9b1d 			; <UNDEFINED> instruction: 0x466d9b1d
d0011114:	970a2401 	strls	r2, [sl, -r1, lsl #8]
d0011118:	23009309 	movwcs	r9, #777	; 0x309
d001111c:	940d4628 	strls	r4, [sp], #-1576	; 0xfffff9d8
d0011120:	930c930b 	movwls	r9, #49931	; 0xc30b
d0011124:	ff9cf7ff 			; <UNDEFINED> instruction: 0xff9cf7ff
d0011128:	e9c39b1f 	stmib	r3, {r0, r1, r2, r3, r4, r8, r9, fp, ip, pc}^
d001112c:	46280100 	strtmi	r0, [r8], -r0, lsl #2
d0011130:	f8a2f7ff 			; <UNDEFINED> instruction: 0xf8a2f7ff
d0011134:	b9139b0c 	ldmdblt	r3, {r2, r3, r8, r9, fp, ip, pc}
d0011138:	42bb9b09 	adcsmi	r9, fp, #9216	; 0x2400
d001113c:	6db0d012 	ldcvs	0, cr13, [r0, #72]!	; 0x48
d0011140:	490ab990 	stmdbmi	sl, {r4, r7, r8, fp, ip, sp, pc}
d0011144:	206cf89d 	mlscs	ip, sp, r8, pc	; <UNPREDICTABLE>
d0011148:	65b14479 	ldrvs	r4, [r1, #1145]!	; 0x479
d001114c:	65f19918 	ldrbvs	r9, [r1, #2328]!	; 0x918
d0011150:	e9c69919 	stmib	r6, {r0, r3, r4, r8, fp, ip, pc}^
d0011154:	9a1c1218 	bls	0xd07159bc
d0011158:	b00f66b2 			; <UNDEFINED> instruction: 0xb00f66b2
d001115c:	40f0e8bd 	ldrhtmi	lr, [r0], #141	; 0x8d
d0011160:	4770b004 	ldrbmi	fp, [r0, -r4]!
d0011164:	e7f84620 	ldrb	r4, [r8, r0, lsr #12]!
d0011168:	e7f62000 	ldrb	r2, [r6, r0]!
d001116c:	ffffff74 			; <UNDEFINED> instruction: 0xffffff74

Disassembly of section .text.enter_header.isra.0:

d0011310 <.text.enter_header.isra.0>:
d0011310:	4ff0e92d 	svcmi	0x00f0e92d
d0011314:	f5ad461e 			; <UNDEFINED> instruction: 0xf5ad461e
d0011318:	6ec37d0d 	cdpvs	13, 12, cr7, cr3, cr13, {0}
d001131c:	9d984604 	ldcls	6, cr4, [r8, #16]
d0011320:	92059104 	andls	r9, r5, #4, 2
d0011324:	6d85b993 	vstrvs.16	s22, [r5, #294]	; 0x126	; <UNPREDICTABLE>
d0011328:	2500b12d 	strcs	fp, [r0, #-301]	; 0xfffffed3
d001132c:	f50d4628 			; <UNDEFINED> instruction: 0xf50d4628
d0011330:	e8bd7d0d 	pop	{r0, r2, r3, r8, sl, fp, ip, sp, lr}
d0011334:	4bfa8ff0 	blmi	0xcfeb52fc
d0011338:	65a3447b 	strvs	r4, [r3, #1147]!	; 0x47b
d001133c:	65e39b04 	strbvs	r9, [r3, #2820]!	; 0xb04
d0011340:	e9c49b05 	stmib	r4, {r0, r2, r8, r9, fp, ip, pc}^
d0011344:	9b963618 	blls	0xce59ebac
d0011348:	e7ef66a3 	strb	r6, [pc, r3, lsr #13]!
d001134c:	2bfe1e6b 	blcs	0xcff98d00
d0011350:	6d85d905 	vstrvs.16	s26, [r5, #10]	; <UNPREDICTABLE>
d0011354:	d1e82d00 	mvnle	r2, r0, lsl #26
d0011358:	447b4bf2 	ldrbtmi	r4, [fp], #-3058	; 0xfffff40e
d001135c:	f10de7ed 			; <UNDEFINED> instruction: 0xf10de7ed
d0011360:	462a0930 			; <UNDEFINED> instruction: 0x462a0930
d0011364:	46489997 			; <UNDEFINED> instruction: 0x46489997
d0011368:	fab0f00e 	blx	0xcec4d3a8
d001136c:	46482300 	strbmi	r2, [r8], -r0, lsl #6
d0011370:	3005f809 	andcc	pc, r5, r9, lsl #16
d0011374:	feb2f00f 	cdp2	0, 11, cr15, cr2, cr15, {0}
d0011378:	d8052802 	stmdale	r5, {r1, fp, sp}
d001137c:	2d006da5 	stccs	13, cr6, [r0, #-660]	; 0xfffffd6c
d0011380:	4be9d1d3 	blmi	0xcfa85ad4
d0011384:	e7d8447b 			; <UNDEFINED> instruction: 0xe7d8447b
d0011388:	49e83802 	stmibmi	r8!, {r1, fp, ip, sp}^
d001138c:	44794448 	ldrbtmi	r4, [r9], #-1096	; 0xfffffbb8
d0011390:	feb0f00f 	cdp2	0, 11, cr15, cr0, cr15, {0}
d0011394:	28004605 	stmdacs	r0, {r0, r2, r9, sl, lr}
d0011398:	ab0bd1f0 	blge	0xd0305b60
d001139c:	7280f44f 	addvc	pc, r0, #1325400064	; 0x4f000000
d00113a0:	7b98f50d 	blvc	0xce64e7dc
d00113a4:	9202900b 	andls	r9, r2, #11
d00113a8:	46024649 	strmi	r4, [r2], -r9, asr #12
d00113ac:	e9cd6ee7 	stmib	sp, {r0, r1, r2, r5, r6, r7, r9, sl, fp, sp, lr}^
d00113b0:	46033b00 	strmi	r3, [r3], -r0, lsl #22
d00113b4:	47b86f60 	ldrmi	r6, [r8, r0, ror #30]!
d00113b8:	f504b1e8 			; <UNDEFINED> instruction: 0xf504b1e8
d00113bc:	46a87700 	strtmi	r7, [r8], r0, lsl #14
d00113c0:	5a2ef504 	bpl	0xd0bce7d8
d00113c4:	3000f8da 	ldrdcc	pc, [r0], -sl
d00113c8:	d2064598 	andle	r4, r6, #152, 10	; 0x26000000
d00113cc:	46594638 			; <UNDEFINED> instruction: 0x46594638
d00113d0:	77a6f507 	strvc	pc, [r6, r7, lsl #10]!
d00113d4:	fe8ef00f 	cdp2	0, 8, cr15, cr14, cr15, {0}
d00113d8:	f8dab998 			; <UNDEFINED> instruction: 0xf8dab998
d00113dc:	45983000 	ldrmi	r3, [r8]
d00113e0:	8103f040 	tsthi	r3, r0, asr #32	; <UNPREDICTABLE>
d00113e4:	0f20f1b8 	svceq	0x0020f1b8
d00113e8:	6da3d10e 	stfvsd	f5, [r3, #56]!	; 0x38
d00113ec:	d19c2b00 	orrsle	r2, ip, r0, lsl #22
d00113f0:	447b4bcf 	ldrbtmi	r4, [fp], #-3023	; 0xfffff431
d00113f4:	6da3e7a1 	stcvs	7, cr14, [r3, #644]!	; 0x284
d00113f8:	d1962b00 	orrsle	r2, r6, r0, lsl #22
d00113fc:	447b4bcd 	ldrbtmi	r4, [fp], #-3021	; 0xfffff433
d0011400:	f108e79b 			; <UNDEFINED> instruction: 0xf108e79b
d0011404:	e7dd0801 	ldrb	r0, [sp, r1, lsl #16]
d0011408:	3384f642 	orrcc	pc, r4, #69206016	; 0x4200000
d001140c:	f5d258e2 			; <UNDEFINED> instruction: 0xf5d258e2
d0011410:	d1054300 	mrsle	r4, SP_abt
d0011414:	2b006da3 	blcs	0xd002caa8
d0011418:	4bc7d187 	blmi	0xcf205a3c
d001141c:	e78c447b 			; <UNDEFINED> instruction: 0xe78c447b
d0011420:	512ef504 	msrpl	CPSR_fsx, r4, lsl #10
d0011424:	7b98f50d 	blvc	0xce64e860
d0011428:	31086f60 	tstcc	r8, r0, ror #30
d001142c:	f8cd6ee7 			; <UNDEFINED> instruction: 0xf8cd6ee7
d0011430:	9106b004 	tstls	r6, r4
d0011434:	7180f44f 	orrvc	pc, r0, pc, asr #8
d0011438:	91029307 	tstls	r2, r7, lsl #6
d001143c:	9109a90b 	tstls	r9, fp, lsl #18
d0011440:	99069100 	stmdbls	r6, {r8, ip, pc}
d0011444:	4649440a 	strbmi	r4, [r9], -sl, lsl #8
d0011448:	9b0747b8 	blls	0xd01e3330
d001144c:	6da5b930 			; <UNDEFINED> instruction: 0x6da5b930
d0011450:	f47f2d00 			; <UNDEFINED> instruction: 0xf47f2d00
d0011454:	4bb9af6a 	blmi	0xcee7d204
d0011458:	e76e447b 			; <UNDEFINED> instruction: 0xe76e447b
d001145c:	68129a09 	ldmdavs	r2, {r0, r3, r9, fp, ip, pc}
d0011460:	d2064293 	andle	r4, r6, #805306377	; 0x30000009
d0011464:	2b006da3 	blcs	0xd002caf8
d0011468:	af5ff47f 	svcge	0x005ff47f
d001146c:	447b4bb4 	ldrbtmi	r4, [fp], #-2996	; 0xfffff44c
d0011470:	f642e763 			; <UNDEFINED> instruction: 0xf642e763
d0011474:	21003384 	smlabbcs	r0, r4, r3, r3
d0011478:	9b0658e0 	blls	0xd01a7800
d001147c:	f00f4418 			; <UNDEFINED> instruction: 0xf00f4418
d0011480:	4681fe17 	pkhbtmi	pc, r1, r7, lsl #28	; <UNPREDICTABLE>
d0011484:	d1ed2800 	mvnle	r2, r0, lsl #16
d0011488:	3000f8da 	ldrdcc	pc, [r0], -sl
d001148c:	70a6f44f 	adcvc	pc, r6, pc, asr #8
d0011490:	33019307 	movwcc	r9, #4871	; 0x1307
d0011494:	3000f8ca 	andcc	pc, r0, sl, asr #17
d0011498:	43439b07 	movtmi	r9, #15111	; 0x3b07
d001149c:	93084658 	movwls	r4, #34392	; 0x8658
d00114a0:	7300f503 	movwvc	pc, #1283	; 0x503	; <UNPREDICTABLE>
d00114a4:	0a03eb04 	beq	0xd010c0bc
d00114a8:	fe18f00f 	cdp2	0, 1, cr15, cr8, cr15, {0}
d00114ac:	1c424659 	mcrrne	6, 5, r4, r2, cr9
d00114b0:	f00e4650 			; <UNDEFINED> instruction: 0xf00e4650
d00114b4:	f642fa0b 			; <UNDEFINED> instruction: 0xf642fa0b
d00114b8:	9b083284 	blls	0xd021ded0
d00114bc:	9a0958a1 	bls	0xd0267748
d00114c0:	681218e3 	ldmdavs	r2, {r0, r1, r5, r6, r7, fp, ip}
d00114c4:	1300f8c3 	movwne	pc, #2243	; 0x8c3	; <UNPREDICTABLE>
d00114c8:	2304f8c3 	movwcs	pc, #18627	; 0x48c3	; <UNPREDICTABLE>
d00114cc:	9308f8c3 	movwls	pc, #35011	; 0x88c3	; <UNPREDICTABLE>
d00114d0:	440b9b06 	strmi	r9, [fp], #-2822	; 0xfffff4fa
d00114d4:	0902eb03 	stmdbeq	r2, {r0, r1, r8, r9, fp, sp, lr, pc}
d00114d8:	4a90469a 	bmi	0xce422f48
d00114dc:	d90945d1 	stmdble	r9, {r0, r4, r6, r7, r8, sl, lr}
d00114e0:	3000f89a 	mulcc	r0, sl, r8
d00114e4:	b2db3b09 	sbcslt	r3, fp, #9216	; 0x2400
d00114e8:	d8032b17 	stmdale	r3, {r0, r1, r2, r4, r8, r9, fp, sp}
d00114ec:	f303fa22 	vpmax.u8	d15, d3, d18
d00114f0:	d41607db 	ldrle	r0, [r6], #-2011	; 0xfffff825
d00114f4:	030aeba9 	movweq	lr, #43945	; 0xaba9
d00114f8:	dd292b01 	fstmdbxle	r9!, {d2-d1}	;@ Deprecated
d00114fc:	3000f89a 	mulcc	r0, sl, r8
d0011500:	d1252b2f 			; <UNDEFINED> instruction: 0xd1252b2f
d0011504:	3001f89a 	mulcc	r1, sl, r8
d0011508:	d10d2b2f 	tstle	sp, pc, lsr #22
d001150c:	0302f10a 	movweq	pc, #8458	; 0x210a	; <UNPREDICTABLE>
d0011510:	469a4599 			; <UNDEFINED> instruction: 0x469a4599
d0011514:	f89ad9ee 			; <UNDEFINED> instruction: 0xf89ad9ee
d0011518:	33011000 	movwcc	r1, #4096	; 0x1000
d001151c:	d1f7290a 	mvnsle	r2, sl, lsl #18
d0011520:	f10ae7dc 			; <UNDEFINED> instruction: 0xf10ae7dc
d0011524:	e7d90a01 	ldrb	r0, [r9, r1, lsl #20]
d0011528:	d1112b2a 	tstle	r1, sl, lsr #22
d001152c:	0a02f10a 	beq	0xd00cd95c
d0011530:	0301f10a 	movweq	pc, #4362	; 0x110a	; <UNPREDICTABLE>
d0011534:	d90b4599 	stmdble	fp, {r0, r3, r4, r7, r8, sl, lr}
d0011538:	1c01f813 	stcne	8, cr15, [r1], {19}
d001153c:	d105292a 	tstle	r5, sl, lsr #18
d0011540:	292f7819 	stmdbcs	pc!, {r0, r3, r4, fp, ip, sp, lr}	; <UNPREDICTABLE>
d0011544:	f10ad102 			; <UNDEFINED> instruction: 0xf10ad102
d0011548:	e7c70a02 	strb	r0, [r7, r2, lsl #20]
d001154c:	e7ef469a 			; <UNDEFINED> instruction: 0xe7ef469a
d0011550:	030aeba9 	movweq	lr, #43945	; 0xaba9
d0011554:	dd422b06 	vstrle	d18, [r2, #-24]	; 0xffffffe8
d0011558:	2207497a 	andcs	r4, r7, #1998848	; 0x1e8000
d001155c:	44794650 	ldrbtmi	r4, [r9], #-1616	; 0xfffff9b0
d0011560:	f9c4f00e 			; <UNDEFINED> instruction: 0xf9c4f00e
d0011564:	f10abbd8 			; <UNDEFINED> instruction: 0xf10abbd8
d0011568:	45b90707 	ldrmi	r0, [r9, #1799]!	; 0x707
d001156c:	f89ad005 			; <UNDEFINED> instruction: 0xf89ad005
d0011570:	2b203007 	blcs	0xd081d594
d0011574:	2b09d001 	blcs	0xd0285580
d0011578:	45b9d131 	ldrmi	sp, [r9, #305]!	; 0x131
d001157c:	d9474639 	stmdble	r7, {r0, r3, r4, r5, r9, sl, lr}^
d0011580:	f813463b 			; <UNDEFINED> instruction: 0xf813463b
d0011584:	2a202b01 	bcs	0xd081c190
d0011588:	2a09d040 	bcs	0xd0285690
d001158c:	463ad03e 			; <UNDEFINED> instruction: 0x463ad03e
d0011590:	f8923701 			; <UNDEFINED> instruction: 0xf8923701
d0011594:	4650a000 	ldrbmi	sl, [r0], -r0
d0011598:	fef5f7fe 	mrc2	7, 7, pc, cr5, cr14, {7}
d001159c:	f1aab920 			; <UNDEFINED> instruction: 0xf1aab920
d00115a0:	f1ba0a30 			; <UNDEFINED> instruction: 0xf1ba0a30
d00115a4:	d8020f09 	stmdale	r2, {r0, r3, r8, r9, sl, fp}
d00115a8:	463a45b9 			; <UNDEFINED> instruction: 0x463a45b9
d00115ac:	1a57d8ef 	bne	0xd1607970
d00115b0:	7808d015 	stmdavc	r8, {r0, r2, r4, ip, lr, pc}
d00115b4:	fee7f7fe 	mcr2	7, 7, pc, cr7, cr14, {7}	; <UNPREDICTABLE>
d00115b8:	2f3fb188 	svccs	0x003fb188
d00115bc:	9b08d80f 	blls	0xd0247600
d00115c0:	f203463a 	vmin.s8	d4, d3, d26
d00115c4:	4420300b 	strtmi	r3, [r0], #-11
d00115c8:	f980f00e 			; <UNDEFINED> instruction: 0xf980f00e
d00115cc:	f44f9b07 			; <UNDEFINED> instruction: 0xf44f9b07
d00115d0:	fb0272a6 	blx	0xd00ae072
d00115d4:	23004203 	movwcs	r4, #515	; 0x203
d00115d8:	f882443a 			; <UNDEFINED> instruction: 0xf882443a
d00115dc:	f642330b 			; <UNDEFINED> instruction: 0xf642330b
d00115e0:	990b3284 	stmdbls	fp, {r2, r7, r9, ip, sp}
d00115e4:	440b58a3 	strmi	r5, [fp], #-2211	; 0xfffff75d
d00115e8:	7a2350a3 	bvc	0xd08e587c
d00115ec:	409f2701 	addsmi	r2, pc, r1, lsl #14
d00115f0:	73a6f44f 			; <UNDEFINED> instruction: 0x73a6f44f
d00115f4:	4308fb03 	movwmi	pc, #35587	; 0x8b03	; <UNPREDICTABLE>
d00115f8:	f893b2bf 			; <UNDEFINED> instruction: 0xf893b2bf
d00115fc:	b14a230a 	cmplt	sl, sl, lsl #6
d0011600:	3308f8b3 	movwcc	pc, #34995	; 0x88b3	; <UNPREDICTABLE>
d0011604:	d005421f 	andle	r4, r5, pc, lsl r2
d0011608:	e68f2501 	str	r2, [pc], r1, lsl #10
d001160c:	e7b4461f 			; <UNDEFINED> instruction: 0xe7b4461f
d0011610:	e7cc463a 			; <UNDEFINED> instruction: 0xe7cc463a
d0011614:	31fcf8d4 	ldrsbcc	pc, [ip, #132]!	; 0x84	; <UNPREDICTABLE>
d0011618:	d1062b0c 	tstle	r6, ip, lsl #22
d001161c:	2b006da3 	blcs	0xd002ccb0
d0011620:	ae83f47f 	mcrge	4, 4, pc, cr3, cr15, {3}	; <UNPREDICTABLE>
d0011624:	447b4b48 	ldrbtmi	r4, [fp], #-2888	; 0xfffff4b8
d0011628:	f44fe687 	vst1.32	{d30-d32}, [pc], r7
d001162c:	fb0171a6 	blx	0xd006dcce
d0011630:	1863f108 	stmdane	r3!, {r3, r8, ip, sp, lr, pc}^
d0011634:	330bf893 	movwcc	pc, #47251	; 0xb893	; <UNPREDICTABLE>
d0011638:	6fa1b94b 	svcvs	0x00a1b94b
d001163c:	d1234541 			; <UNDEFINED> instruction: 0xd1234541
d0011640:	2b006da3 	blcs	0xd002ccd4
d0011644:	ae71f47f 	mrcge	4, 3, APSR_nzcv, cr1, cr15, {3}
d0011648:	447b4b40 	ldrbtmi	r4, [fp], #-2880	; 0xfffff4c0
d001164c:	f201e675 	vmin.s8	q7, <illegal reg q0.5>, <illegal reg q10.5>
d0011650:	f504310b 			; <UNDEFINED> instruction: 0xf504310b
d0011654:	f504492b 			; <UNDEFINED> instruction: 0xf504492b
d0011658:	f04f4b4f 			; <UNDEFINED> instruction: 0xf04f4b4f
d001165c:	44210a00 	strtmi	r0, [r1], #-2560	; 0xfffff600
d0011660:	0988f109 	stmibeq	r8, {r0, r3, r8, ip, sp, lr, pc}
d0011664:	0b88f10b 	bleq	0xce24da98
d0011668:	3000f8db 	ldrdcc	pc, [r0], -fp
d001166c:	d2e4459a 	rscle	r4, r4, #645922816	; 0x26800000
d0011670:	91064648 	tstls	r6, r8, asr #12
d0011674:	0948f109 	stmdbeq	r8, {r0, r3, r8, ip, sp, lr, pc}^
d0011678:	fd3cf00f 	ldc2	0, cr15, [ip, #-60]!	; 0xffffffc4
d001167c:	d0c32800 	sbcle	r2, r3, r0, lsl #16
d0011680:	0a01f10a 	beq	0xd008dab0
d0011684:	e7ef9906 	strb	r9, [pc, r6, lsl #18]!
d0011688:	01fcf8d4 	ldrsbeq	pc, [ip, #132]!	; 0x84	; <UNPREDICTABLE>
d001168c:	f1042200 			; <UNDEFINED> instruction: 0xf1042200
d0011690:	42820c94 	addmi	r0, r2, #148, 24	; 0x9400
d0011694:	1342ea4f 	movtne	lr, #10831	; 0x2a4f
d0011698:	3201d13a 	andcc	sp, r1, #-2147483634	; 0x8000000e
d001169c:	f8d468e5 			; <UNDEFINED> instruction: 0xf8d468e5
d00116a0:	44239074 	strtmi	r9, [r3], #-116	; 0xffffff8c
d00116a4:	21fcf8c4 	mvnscs	pc, r4, asr #17
d00116a8:	020cf24d 	andeq	pc, ip, #-805306364	; 0xd0000004
d00116ac:	e004f8d4 	ldrd	pc, [r4], -r4
d00116b0:	c002f854 	andgt	pc, r2, r4, asr r8	; <UNPREDICTABLE>
d00116b4:	e9d46822 	ldmib	r4, {r1, r5, fp, sp, lr}^
d00116b8:	f8c36004 			; <UNDEFINED> instruction: 0xf8c36004
d00116bc:	25015088 	strcs	r5, [r1, #-136]	; 0xffffff78
d00116c0:	608cf8c3 	addvs	pc, ip, r3, asr #17
d00116c4:	f8c367da 			; <UNDEFINED> instruction: 0xf8c367da
d00116c8:	e9c3c098 	stmib	r3, {r3, r4, r7, lr, pc}^
d00116cc:	e9c30124 	stmib	r3, {r2, r5, r8}^
d00116d0:	f44f9e20 			; <UNDEFINED> instruction: 0xf44f9e20
d00116d4:	fb0373a6 	blx	0xd00ee576
d00116d8:	18e1f308 	stmiane	r1!, {r3, r8, r9, ip, sp, lr, pc}^
d00116dc:	7300f503 	movwvc	pc, #1283	; 0x503	; <UNPREDICTABLE>
d00116e0:	2308f8b1 	movwcs	pc, #34993	; 0x88b1	; <UNPREDICTABLE>
d00116e4:	f8d14423 			; <UNDEFINED> instruction: 0xf8d14423
d00116e8:	43170300 	tstmi	r7, #0, 6
d00116ec:	522ef504 	eorpl	pc, lr, #4, 10	; 0x1000000
d00116f0:	f8a13208 			; <UNDEFINED> instruction: 0xf8a13208
d00116f4:	44027308 	strmi	r7, [r2], #-776	; 0xfffffcf8
d00116f8:	f8d16022 			; <UNDEFINED> instruction: 0xf8d16022
d00116fc:	67632304 	strbvs	r2, [r3, -r4, lsl #6]!
d0011700:	22006062 	andcs	r6, r0, #98	; 0x62
d0011704:	8078f8c4 	rsbshi	pc, r8, r4, asr #17
d0011708:	e9c460e2 	stmib	r4, {r1, r5, r6, r7, sp, lr}^
d001170c:	e60d5504 	str	r5, [sp], -r4, lsl #10
d0011710:	3003f85c 	andcc	pc, r3, ip, asr r8	; <UNPREDICTABLE>
d0011714:	d0934598 	umullsle	r4, r3, r8, r5
d0011718:	e7ba3201 	ldr	r3, [sl, r1, lsl #4]!
d001171c:	00800013 	addeq	r0, r0, r3, lsl r0
d0011720:	fffffe34 			; <UNDEFINED> instruction: 0xfffffe34
d0011724:	fffffe3f 			; <UNDEFINED> instruction: 0xfffffe3f
d0011728:	fffffe35 			; <UNDEFINED> instruction: 0xfffffe35
d001172c:	fffffe28 			; <UNDEFINED> instruction: 0xfffffe28
d0011730:	fffffe1b 			; <UNDEFINED> instruction: 0xfffffe1b
d0011734:	fffffde8 			; <UNDEFINED> instruction: 0xfffffde8
d0011738:	fffffe11 			; <UNDEFINED> instruction: 0xfffffe11
d001173c:	fffffdf9 			; <UNDEFINED> instruction: 0xfffffdf9
d0011740:	fffffe12 			; <UNDEFINED> instruction: 0xfffffe12
d0011744:	fffffd4f 			; <UNDEFINED> instruction: 0xfffffd4f
d0011748:	fffffc8f 			; <UNDEFINED> instruction: 0xfffffc8f
d001174c:	fffffc8b 			; <UNDEFINED> instruction: 0xfffffc8b

Disassembly of section .text.scan:

d00118ec <.text.scan>:
d00118ec:	e92d6d8b 	push	{r0, r1, r3, r7, r8, sl, fp, sp, lr}
d00118f0:	46064ff0 			; <UNDEFINED> instruction: 0x46064ff0
d00118f4:	460cb09d 			; <UNDEFINED> instruction: 0x460cb09d
d00118f8:	f501bba3 			; <UNDEFINED> instruction: 0xf501bba3
d00118fc:	f1084850 			; <UNDEFINED> instruction: 0xf1084850
d0011900:	4620080c 	strtmi	r0, [r0], -ip, lsl #16
d0011904:	fca8f7fe 	stc2	7, cr15, [r8], #1016	; 0x3f8
d0011908:	d14f2800 	cmple	pc, r0, lsl #16
d001190c:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d0011910:	fc58f7fe 	mrrc2	7, 15, pc, r8, cr14	; <UNPREDICTABLE>
d0011914:	d0282820 	eorle	r2, r8, r0, lsr #16
d0011918:	d0262809 	eorle	r2, r6, r9, lsl #16
d001191c:	68e22823 	stmiavs	r2!, {r0, r1, r5, fp, sp}^
d0011920:	d1366863 	teqle	r6, r3, ror #16
d0011924:	d241429a 	suble	r4, r1, #-1610612727	; 0xa0000009
d0011928:	0930f10d 	ldmdbeq	r0!, {r0, r2, r3, r8, ip, sp, lr, pc}
d001192c:	466f4621 	strbtmi	r4, [pc], -r1, lsr #12
d0011930:	4648ad14 			; <UNDEFINED> instruction: 0x4648ad14
d0011934:	fc6ef7fe 	stc2l	7, cr15, [lr], #-1016	; 0xfffffc08
d0011938:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d001193c:	f10dfc4c 			; <UNDEFINED> instruction: 0xf10dfc4c
d0011940:	e8bc0c38 	ldm	ip!, {r3, r4, r5, sl, fp}
d0011944:	c70f000f 	strgt	r0, [pc, -pc]
d0011948:	0003e89c 	muleq	r3, ip, r8
d001194c:	0003e887 	andeq	lr, r3, r7, lsl #17
d0011950:	46284621 	strtmi	r4, [r8], -r1, lsr #12
d0011954:	000ce899 	muleq	ip, r9, r8
d0011958:	fd2af000 	stc2	0, cr15, [sl, #-0]
d001195c:	b1436da3 	smlaltblt	r6, r3, r3, sp
d0011960:	46304621 	ldrtmi	r4, [r0], -r1, lsr #12
d0011964:	fc56f7fe 	mrrc2	7, 15, pc, r6, cr14	; <UNPREDICTABLE>
d0011968:	4620e00f 	strtmi	lr, [r0], -pc
d001196c:	fc33f7fe 	ldc2	7, cr15, [r3], #-1016	; 0xfffffc08
d0011970:	9b19e7cc 	blls	0xd068b8a8
d0011974:	7f97f5b3 	svcvc	0x0097f5b3
d0011978:	462cd0c3 	strtmi	sp, [ip], -r3, asr #1
d001197c:	cc0f4637 	stcgt	6, cr4, [pc], {55}	; 0x37
d0011980:	e894c70f 	ldm	r4, {r0, r1, r2, r3, r8, r9, sl, lr, pc}
d0011984:	e887000f 	stm	r7, {r0, r1, r2, r3}
d0011988:	4630000f 	ldrtmi	r0, [r0], -pc
d001198c:	e8bdb01d 	pop	{r0, r2, r3, r4, ip, sp, pc}
d0011990:	429a8ff0 	addsmi	r8, sl, #240, 30	; 0x3c0
d0011994:	4620d20a 	strtmi	sp, [r0], -sl, lsl #4
d0011998:	fc7bf7fe 	ldc2l	7, cr15, [fp], #-1016	; 0xfffffc08
d001199c:	686368e2 	stmdavs	r3!, {r1, r5, r6, r7, fp, sp, lr}^
d00119a0:	d2ae429a 	adcle	r4, lr, #-1610612727	; 0xa0000009
d00119a4:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d00119a8:	e7aafc16 			; <UNDEFINED> instruction: 0xe7aafc16
d00119ac:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d00119b0:	fc08f7fe 	stc2	7, cr15, [r8], {254}	; 0xfe
d00119b4:	d0f52820 	rscsle	r2, r5, r0, lsr #16
d00119b8:	0309f1a0 	movweq	pc, #37280	; 0x91a0	; <UNPREDICTABLE>
d00119bc:	d9f12b04 	ldmible	r1!, {r2, r8, r9, fp, sp}^
d00119c0:	d170282f 	cmnle	r0, pc, lsr #16
d00119c4:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d00119c8:	fbfcf7fe 	blx	0xcff4f9ca
d00119cc:	d10f282f 	tstle	pc, pc, lsr #16
d00119d0:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d00119d4:	fbf6f7fe 	blx	0xcfdcf9d6
d00119d8:	686368e2 	stmdavs	r3!, {r1, r5, r6, r7, fp, sp, lr}^
d00119dc:	d090429a 	umullsle	r4, r0, sl, r2
d00119e0:	d08e280a 	addle	r2, lr, sl, lsl #16
d00119e4:	d08c280d 	addle	r2, ip, sp, lsl #16
d00119e8:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d00119ec:	e7effbf4 			; <UNDEFINED> instruction: 0xe7effbf4
d00119f0:	d158282a 	cmple	r8, sl, lsr #16
d00119f4:	4621a814 			; <UNDEFINED> instruction: 0x4621a814
d00119f8:	fc0cf7fe 	stc2	7, cr15, [ip], {254}	; 0xfe
d00119fc:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011a00:	4620fbea 	strtmi	pc, [r0], -sl, ror #23
d0011a04:	fbe7f7fe 	blx	0xcfa0fa06
d0011a08:	686368e2 	stmdavs	r3!, {r1, r5, r6, r7, fp, sp, lr}^
d0011a0c:	f000429a 			; <UNDEFINED> instruction: 0xf000429a
d0011a10:	210082c0 	smlabtcs	r0, r0, r2, r8
d0011a14:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011a18:	282afbd5 	stmdacs	sl!, {r0, r2, r4, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d0011a1c:	2101d1f1 	strdcs	sp, [r1, -r1]
d0011a20:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011a24:	282ffbcf 	stmdacs	pc!, {r0, r1, r2, r3, r6, r7, r8, r9, fp, ip, sp, lr, pc}	; <UNPREDICTABLE>
d0011a28:	4620d1eb 	strtmi	sp, [r0], -fp, ror #3
d0011a2c:	fbd3f7fe 	blx	0xcf50fa2e
d0011a30:	3b01e7b8 	blcc	0xd008b918
d0011a34:	0000f8d8 	ldrdeq	pc, [r0], -r8
d0011a38:	1143eb04 	cmpne	r3, r4, lsl #22
d0011a3c:	f8d1015a 			; <UNDEFINED> instruction: 0xf8d1015a
d0011a40:	42881098 	addmi	r1, r8, #152	; 0x98
d0011a44:	f8dfd006 			; <UNDEFINED> instruction: 0xf8dfd006
d0011a48:	447915e4 	ldrbtmi	r1, [r9], #-1508	; 0xfffffa1c
d0011a4c:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011a50:	e785fbab 	str	pc, [r5, fp, lsr #23]
d0011a54:	f8c4327c 			; <UNDEFINED> instruction: 0xf8c4327c
d0011a58:	18a331fc 	stmiane	r3!, {r2, r3, r4, r5, r6, r7, r8, ip, sp}
d0011a5c:	c002f854 	andgt	pc, r2, r4, asr r8	; <UNPREDICTABLE>
d0011a60:	000cf103 	andeq	pc, ip, r3, lsl #2
d0011a64:	689d685f 	ldmvs	sp, {r0, r1, r2, r3, r4, r6, fp, sp, lr}
d0011a68:	e9c4c80f 	stmib	r4, {r0, r1, r2, r3, fp, lr, pc}^
d0011a6c:	22011204 	andcs	r1, r1, #4, 4	; 0x40000000
d0011a70:	c000f8c4 	andgt	pc, r0, r4, asr #17
d0011a74:	60656767 	rsbvs	r6, r5, r7, ror #14
d0011a78:	67a360e0 	strvs	r6, [r3, r0, ror #1]!
d0011a7c:	686368e1 	stmdavs	r3!, {r0, r5, r6, r7, fp, sp, lr}^
d0011a80:	f0404299 			; <UNDEFINED> instruction: 0xf0404299
d0011a84:	f8d48297 			; <UNDEFINED> instruction: 0xf8d48297
d0011a88:	2b0031fc 	blcs	0xd001e280
d0011a8c:	2a00d1d1 	bcs	0xd00461d8
d0011a90:	af37f47f 	svcge	0x0037f47f
d0011a94:	3000f8d8 	ldrdcc	pc, [r0], -r8
d0011a98:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d0011a9c:	f8df828e 			; <UNDEFINED> instruction: 0xf8df828e
d0011aa0:	44791590 	ldrbtmi	r1, [r9], #-1424	; 0xfffffa70
d0011aa4:	2200e7d2 	andcs	lr, r0, #55050240	; 0x3480000
d0011aa8:	4620e7e8 	strtmi	lr, [r0], -r8, ror #15
d0011aac:	fb93f7fe 	blx	0xce50faae
d0011ab0:	46812823 	strmi	r2, [r1], r3, lsr #16
d0011ab4:	f10dd123 			; <UNDEFINED> instruction: 0xf10dd123
d0011ab8:	46ec0e38 			; <UNDEFINED> instruction: 0x46ec0e38
d0011abc:	e8beaf14 	ldm	lr!, {r2, r4, r8, r9, sl, fp, sp, pc}
d0011ac0:	e8ac000f 	stmia	ip!, {r0, r1, r2, r3}
d0011ac4:	e89e000f 	ldm	lr, {r0, r1, r2, r3}
d0011ac8:	e88c0003 	stm	ip, {r0, r1}
d0011acc:	46210003 	strtmi	r0, [r1], -r3
d0011ad0:	e8954638 	ldm	r5, {r3, r4, r5, r9, sl, lr}
d0011ad4:	f000000c 			; <UNDEFINED> instruction: 0xf000000c
d0011ad8:	6da3fc6b 	stcvs	12, cr15, [r3, #428]!	; 0x1ac
d0011adc:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0011ae0:	9b19af3f 	blls	0xd067d7e4
d0011ae4:	7f97f5b3 	svcvc	0x0097f5b3
d0011ae8:	af0bf43f 	svcge	0x000bf43f
d0011aec:	4635463c 			; <UNDEFINED> instruction: 0x4635463c
d0011af0:	c50fcc0f 	strgt	ip, [pc, #-3087]	; 0xd0010ee9
d0011af4:	000fe894 	muleq	pc, r4, r8	; <UNPREDICTABLE>
d0011af8:	000fe885 	andeq	lr, pc, r5, lsl #17
d0011afc:	f7fee745 			; <UNDEFINED> instruction: 0xf7fee745
d0011b00:	4601fc42 	strmi	pc, [r1], -r2, asr #24
d0011b04:	d1402800 	cmple	r0, r0, lsl #16
d0011b08:	0830f1a9 	ldmdaeq	r0!, {r0, r3, r5, r7, r8, ip, sp, lr, pc}
d0011b0c:	0f09f1b8 	svceq	0x0009f1b8
d0011b10:	8111f200 	tsthi	r1, r0, lsl #4	; <UNPREDICTABLE>
d0011b14:	0f30f1b9 	svceq	0x0030f1b9
d0011b18:	8266f000 	rsbhi	pc, r6, #0
d0011b1c:	2100270a 	tstcs	r0, sl, lsl #14
d0011b20:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011b24:	4681fb4f 	strmi	pc, [r1], pc, asr #22
d0011b28:	fc7af7fe 	ldc2l	7, cr15, [sl], #-1016	; 0xfffffc08
d0011b2c:	f2004287 	vhsub.s8	d4, d16, d7
d0011b30:	f04980db 			; <UNDEFINED> instruction: 0xf04980db
d0011b34:	f1b90920 			; <UNDEFINED> instruction: 0xf1b90920
d0011b38:	d1020f75 	tstle	r2, r5, ror pc
d0011b3c:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011b40:	2100fb4a 	tstcs	r0, sl, asr #22	; <UNPREDICTABLE>
d0011b44:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011b48:	f1a0fb3d 			; <UNDEFINED> instruction: 0xf1a0fb3d
d0011b4c:	46020330 			; <UNDEFINED> instruction: 0x46020330
d0011b50:	d90f2b09 	stmdble	pc, {r0, r3, r8, r9, fp, sp}	; <UNPREDICTABLE>
d0011b54:	fc17f7fe 	ldc2	7, cr15, [r7], {254}	; 0xfe
d0011b58:	2a2eb960 	bcs	0xd0bc00e0
d0011b5c:	f1b9d00a 			; <UNDEFINED> instruction: 0xf1b9d00a
d0011b60:	f0000f75 			; <UNDEFINED> instruction: 0xf0000f75
d0011b64:	2f0a80e2 	svccs	0x000a80e2
d0011b68:	80d4f040 	sbcshi	pc, r4, r0, asr #32
d0011b6c:	0f00f1b8 	svceq	0x0000f1b8
d0011b70:	80def280 	sbcshi	pc, lr, r0, lsl #5
d0011b74:	2b006da3 	blcs	0xd002d208
d0011b78:	aef2f47f 	mrcge	4, 7, APSR_nzcv, cr2, cr15, {3}
d0011b7c:	34b4f8df 	ldrtcc	pc, [r4], #2271	; 0x8df	; <UNPREDICTABLE>
d0011b80:	e041447b 	sub	r4, r1, fp, ror r4
d0011b84:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011b88:	2100fb26 	tstcs	r0, r6, lsr #22	; <UNPREDICTABLE>
d0011b8c:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011b90:	4602fb19 			; <UNDEFINED> instruction: 0x4602fb19
d0011b94:	fbf7f7fe 	blx	0xcfe0fb96
d0011b98:	d1f32800 	mvnsle	r2, r0, lsl #16
d0011b9c:	2a093a30 	bcs	0xd0260464
d0011ba0:	6825d9f0 	stmdavs	r5!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
d0011ba4:	68e34680 	stmiavs	r3!, {r7, r9, sl, lr}^
d0011ba8:	948cf8df 	strls	pc, [ip], #2271	; 0x8df
d0011bac:	44f9441d 	ldrbtmi	r4, [r9], #1053	; 0x41d
d0011bb0:	f8591bed 			; <UNDEFINED> instruction: 0xf8591bed
d0011bb4:	46292b04 	strtmi	r2, [r9], -r4, lsl #22
d0011bb8:	f7fe4638 			; <UNDEFINED> instruction: 0xf7fe4638
d0011bbc:	b160fe5b 	msrlt	(UNDEF: 96), fp
d0011bc0:	1007f208 	andne	pc, r7, r8, lsl #4
d0011bc4:	9011950d 	andsls	r9, r1, sp, lsl #10
d0011bc8:	ad0c4634 	stcge	6, cr4, [ip, #-208]	; 0xffffff30
d0011bcc:	c40fcd0f 	strgt	ip, [pc], #-3343	; 0xd0011bd4
d0011bd0:	000fe895 	muleq	pc, r5, r8	; <UNPREDICTABLE>
d0011bd4:	000fe884 	andeq	lr, pc, r4, lsl #17
d0011bd8:	f108e6d7 			; <UNDEFINED> instruction: 0xf108e6d7
d0011bdc:	f1b80801 			; <UNDEFINED> instruction: 0xf1b80801
d0011be0:	d1e60f15 	mvnle	r0, r5, lsl pc
d0011be4:	9454f8df 	ldrbls	pc, [r4], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d0011be8:	44f94680 	ldrbtmi	r4, [r9], #1664	; 0x680
d0011bec:	2b04f859 	blcs	0xd014fd58
d0011bf0:	46384629 	ldrtmi	r4, [r8], -r9, lsr #12
d0011bf4:	fe3ef7fe 	mrc2	7, 1, pc, cr14, cr14, {7}
d0011bf8:	6da3b168 	stfvsd	f3, [r3, #416]!	; 0x1a0
d0011bfc:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0011c00:	f8dfaeaf 			; <UNDEFINED> instruction: 0xf8dfaeaf
d0011c04:	447b343c 	ldrbtmi	r3, [fp], #-1084	; 0xfffffbc4
d0011c08:	9b0665a3 	blls	0xd01ab29c
d0011c0c:	ba18e9c4 	blt	0xd064c324
d0011c10:	9b0765e3 	blls	0xd01eb3a4
d0011c14:	f108e1cc 			; <UNDEFINED> instruction: 0xf108e1cc
d0011c18:	f1b80801 			; <UNDEFINED> instruction: 0xf1b80801
d0011c1c:	d1e50f17 	mvnle	r0, r7, lsl pc
d0011c20:	4639462a 	ldrtmi	r4, [r9], -sl, lsr #12
d0011c24:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011c28:	2800fb47 	stmdacs	r0, {r0, r1, r2, r6, r8, r9, fp, ip, sp, lr, pc}
d0011c2c:	2128db0c 			; <UNDEFINED> instruction: 0x2128db0c
d0011c30:	fb01950d 	blx	0xd007706e
d0011c34:	f5044400 			; <UNDEFINED> instruction: 0xf5044400
d0011c38:	f8d43478 			; <UNDEFINED> instruction: 0xf8d43478
d0011c3c:	930e30b0 	movwls	r3, #57520	; 0xe0b0
d0011c40:	7381f44f 	orrvc	pc, r1, #1325400064	; 0x4f000000
d0011c44:	e7bf9311 			; <UNDEFINED> instruction: 0xe7bf9311
d0011c48:	4639462a 	ldrtmi	r4, [r9], -sl, lsr #12
d0011c4c:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011c50:	2800fb78 	stmdacs	r0, {r3, r4, r5, r6, r8, r9, fp, ip, sp, lr, pc}
d0011c54:	2348db2a 	movtcs	sp, #35626	; 0x8b2a
d0011c58:	4000fb03 	andmi	pc, r0, r3, lsl #22
d0011c5c:	402bf500 	eormi	pc, fp, r0, lsl #10
d0011c60:	e9d030c8 	ldmib	r0, {r3, r6, r7, ip, sp}^
d0011c64:	f1100100 			; <UNDEFINED> instruction: 0xf1100100
d0011c68:	93084300 	movwls	r4, #33536	; 0x8300
d0011c6c:	0300f141 	movweq	pc, #321	; 0x141	; <UNPREDICTABLE>
d0011c70:	e9dd9309 	ldmib	sp, {r0, r3, r8, r9, ip, pc}^
d0011c74:	2b012308 	blcs	0xd005a89c
d0011c78:	f1b2bf08 			; <UNDEFINED> instruction: 0xf1b2bf08
d0011c7c:	d3064f00 	movwle	r4, #28416	; 0x6f00
d0011c80:	2b006da3 	blcs	0xd002d314
d0011c84:	ae6cf47f 	mcrge	4, 3, pc, cr12, cr15, {3}	; <UNPREDICTABLE>
d0011c88:	447b4bee 	ldrbtmi	r4, [fp], #-3054	; 0xfffff412
d0011c8c:	f06fe7bc 			; <UNDEFINED> instruction: 0xf06fe7bc
d0011c90:	23004200 	movwcs	r4, #512	; 0x200
d0011c94:	4282900a 	addmi	r9, r2, #10
d0011c98:	f240418b 	vrhadd.s8	d20, d16, d11
d0011c9c:	bfa81303 	svclt	0x00a81303
d0011ca0:	7381f44f 	orrvc	pc, r1, #1325400064	; 0x4f000000
d0011ca4:	950d9a0a 	strls	r9, [sp, #-2570]	; 0xfffff5f6
d0011ca8:	e7cb920e 	strb	r9, [fp, lr, lsl #4]
d0011cac:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d0011cb0:	4620e7f8 			; <UNDEFINED> instruction: 0x4620e7f8
d0011cb4:	f7fe910a 			; <UNDEFINED> instruction: 0xf7fe910a
d0011cb8:	990afa8e 	stmdbls	sl, {r1, r2, r3, r7, r9, fp, ip, sp, lr, pc}
d0011cbc:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011cc0:	f7fefa81 			; <UNDEFINED> instruction: 0xf7fefa81
d0011cc4:	2810fbad 	ldmdacs	r0, {r0, r2, r3, r5, r7, r8, r9, fp, ip, sp, lr, pc}
d0011cc8:	d1214607 			; <UNDEFINED> instruction: 0xd1214607
d0011ccc:	2b006da3 	blcs	0xd002d360
d0011cd0:	af25f47f 	svcge	0x0025f47f
d0011cd4:	447b4bdc 	ldrbtmi	r4, [fp], #-3036	; 0xfffff424
d0011cd8:	9b0665a3 	blls	0xd01ab36c
d0011cdc:	9b0765e3 	blls	0xd01eb470
d0011ce0:	ba18e9c4 	blt	0xd064c3f8
d0011ce4:	e71a66a3 	ldr	r6, [sl, -r3, lsr #13]
d0011ce8:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011cec:	f7fefa74 			; <UNDEFINED> instruction: 0xf7fefa74
d0011cf0:	43c3fb97 	bicmi	pc, r3, #154624	; 0x25c00
d0011cf4:	f3f7fbb3 			; <UNDEFINED> instruction: 0xf3f7fbb3
d0011cf8:	d2064543 	andle	r4, r6, #281018368	; 0x10c00000
d0011cfc:	2b006da3 	blcs	0xd002d390
d0011d00:	ae2ef47f 	mcrge	4, 1, pc, cr14, cr15, {3}	; <UNPREDICTABLE>
d0011d04:	447b4bd1 	ldrbtmi	r4, [fp], #-3025	; 0xfffff42f
d0011d08:	fb08e77e 	blx	0xd024bb0a
d0011d0c:	e7060807 	str	r0, [r6, -r7, lsl #16]
d0011d10:	e7042710 	smlad	r4, r0, r7, r2
d0011d14:	0f00f1b8 	svceq	0x0000f1b8
d0011d18:	1303f240 	movwne	pc, #12864	; 0x3240	; <UNPREDICTABLE>
d0011d1c:	f44fbfa8 			; <UNDEFINED> instruction: 0xf44fbfa8
d0011d20:	f8cd7381 			; <UNDEFINED> instruction: 0xf8cd7381
d0011d24:	93118038 	tstls	r1, #56	; 0x38
d0011d28:	f240e15c 	vand	q15, q0, q6
d0011d2c:	e7f81303 	ldrb	r1, [r8, r3, lsl #6]!
d0011d30:	7381f44f 	orrvc	pc, r1, #1325400064	; 0x4f000000
d0011d34:	f1b9e7f5 			; <UNDEFINED> instruction: 0xf1b9e7f5
d0011d38:	d0020f22 	andle	r0, r2, r2, lsr #30
d0011d3c:	0f27f1b9 	svceq	0x0027f1b9
d0011d40:	6823d171 	stmdavs	r3!, {r0, r4, r5, r6, r8, ip, lr, pc}
d0011d44:	4701f242 	strmi	pc, [r1, -r2, asr #4]
d0011d48:	68e39308 	stmiavs	r3!, {r3, r8, r9, ip, pc}^
d0011d4c:	68e2930b 	stmiavs	r2!, {r0, r1, r3, r8, r9, ip, pc}^
d0011d50:	429a6863 	addsmi	r6, sl, #6488064	; 0x630000
d0011d54:	4620d05a 			; <UNDEFINED> instruction: 0x4620d05a
d0011d58:	fa3df7fe 	blx	0xd0f8fd58
d0011d5c:	d14a4581 	smlalbble	r4, sl, r1, r5
d0011d60:	f1b99b08 			; <UNDEFINED> instruction: 0xf1b99b08
d0011d64:	68e70f22 	stmiavs	r7!, {r1, r5, r8, r9, sl, fp}^
d0011d68:	eb039a0b 	bl	0xd00f859c
d0011d6c:	f1070802 			; <UNDEFINED> instruction: 0xf1070802
d0011d70:	682733ff 	stmdavs	r7!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, ip, sp}
d0011d74:	eba7441f 	bl	0xce9e2df8
d0011d78:	d0390708 	eorsle	r0, r9, r8, lsl #14
d0011d7c:	0907eb08 	stmdbeq	r7, {r3, r8, r9, fp, sp, lr, pc}
d0011d80:	8050f8cd 	subshi	pc, r0, sp, asr #17
d0011d84:	d10645c8 	smlabtle	r6, r8, r5, r4
d0011d88:	2b006da3 	blcs	0xd002d41c
d0011d8c:	ade8f47f 	cfstrdge	mvd15, [r8, #508]!	; 0x1fc
d0011d90:	447b4baf 	ldrbtmi	r4, [fp], #-2991	; 0xfffff451
d0011d94:	f108e738 			; <UNDEFINED> instruction: 0xf108e738
d0011d98:	9a080301 	bls	0xd02129a4
d0011d9c:	9314990b 	tstls	r4, #180224	; 0x2c000
d0011da0:	2a5c5c52 	bcs	0xd1728ef0
d0011da4:	d10e920a 	tstle	lr, sl, lsl #4
d0011da8:	d00c4599 	mulle	ip, r9, r5
d0011dac:	465aab14 			; <UNDEFINED> instruction: 0x465aab14
d0011db0:	46209906 	strtmi	r9, [r0], -r6, lsl #18
d0011db4:	9b079301 	blls	0xd01f69c0
d0011db8:	9008f8cd 	andls	pc, r8, sp, asr #17
d0011dbc:	46539300 	ldrbmi	r9, [r3], -r0, lsl #6
d0011dc0:	fb58f7fe 	blx	0xd164fdc2
d0011dc4:	9b14900a 	blls	0xd0535df4
d0011dc8:	d00a4599 	mulle	sl, r9, r5
d0011dcc:	b9436da3 	stmdblt	r3, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0011dd0:	447b4ba0 	ldrbtmi	r4, [fp], #-2976	; 0xfffff460
d0011dd4:	9b0665a3 	blls	0xd01ab468
d0011dd8:	9b0765e3 	blls	0xd01eb56c
d0011ddc:	ba18e9c4 	blt	0xd064c4f4
d0011de0:	f44f66a3 	vst1.32	{d22-d24}, [pc :128], r3
d0011de4:	9a0a7381 	bls	0xd02aebf0
d0011de8:	870ce9cd 	strhi	lr, [ip, -sp, asr #19]
d0011dec:	e79a920e 	ldr	r9, [sl, lr, lsl #4]
d0011df0:	7382f44f 	orrvc	pc, r2, #1325400064	; 0x4f000000
d0011df4:	285ce7f7 	ldmdacs	ip, {r0, r1, r2, r4, r5, r6, r7, r8, r9, sl, sp, lr, pc}^
d0011df8:	4620d102 	strtmi	sp, [r0], -r2, lsl #2
d0011dfc:	f9ebf7fe 			; <UNDEFINED> instruction: 0xf9ebf7fe
d0011e00:	d8a4280d 	stmiale	r4!, {r0, r2, r3, fp, sp}
d0011e04:	f000fa27 			; <UNDEFINED> instruction: 0xf000fa27
d0011e08:	d5a007c3 	strle	r0, [r0, #1987]!	; 0x7c3
d0011e0c:	0f22f1b9 	svceq	0x0022f1b9
d0011e10:	4b91d102 	blmi	0xce486220
d0011e14:	e001447b 	and	r4, r1, fp, ror r4
d0011e18:	447b4b90 	ldrbtmi	r4, [fp], #-2960	; 0xfffff470
d0011e1c:	2a006da2 	bcs	0xd002d4ac
d0011e20:	ad9ef47f 	cfldrsge	mvf15, [lr, #508]	; 0x1fc
d0011e24:	900ae6f0 	strdls	lr, [sl], -r0
d0011e28:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011e2c:	f029f9cb 			; <UNDEFINED> instruction: 0xf029f9cb
d0011e30:	46800302 	strmi	r0, [r0], r2, lsl #6
d0011e34:	2b3c990a 	blcs	0xd0f38264
d0011e38:	4581d11e 	strmi	sp, [r1, #286]	; 0x11e
d0011e3c:	4620d11c 			; <UNDEFINED> instruction: 0x4620d11c
d0011e40:	f7fe9106 			; <UNDEFINED> instruction: 0xf7fe9106
d0011e44:	f1b9f9c8 			; <UNDEFINED> instruction: 0xf1b9f9c8
d0011e48:	99060f3c 	stmdbls	r6, {r2, r3, r4, r5, r8, r9, sl, fp}
d0011e4c:	f2404620 	vmax.s8	d20, d0, d16
d0011e50:	bf181727 	svclt	0x00181727
d0011e54:	7794f44f 	ldrvc	pc, [r4, pc, asr #8]
d0011e58:	f9b4f7fe 			; <UNDEFINED> instruction: 0xf9b4f7fe
d0011e5c:	d109283d 	tstle	r9, sp, lsr r8
d0011e60:	f2404620 	vmax.s8	d20, d0, d16
d0011e64:	f7fe172d 			; <UNDEFINED> instruction: 0xf7fe172d
d0011e68:	f1b9f9b6 			; <UNDEFINED> instruction: 0xf1b9f9b6
d0011e6c:	bf080f3c 	svclt	0x00080f3c
d0011e70:	7796f44f 	ldrvc	pc, [r6, pc, asr #8]
d0011e74:	e0b59711 	adcs	r9, r5, r1, lsl r7
d0011e78:	0f3df1b8 	svceq	0x003df1b8
d0011e7c:	80c0f040 	sbchi	pc, r0, r0, asr #32
d0011e80:	0f2bf1b9 	svceq	0x002bf1b9
d0011e84:	f1b9d002 			; <UNDEFINED> instruction: 0xf1b9d002
d0011e88:	d10a0f2d 	tstle	sl, sp, lsr #30
d0011e8c:	f2404620 	vmax.s8	d20, d0, d16
d0011e90:	f7fe1725 			; <UNDEFINED> instruction: 0xf7fe1725
d0011e94:	f1b9f9a0 			; <UNDEFINED> instruction: 0xf1b9f9a0
d0011e98:	bf180f2b 	svclt	0x00180f2b
d0011e9c:	7793f44f 	ldrvc	pc, [r3, pc, asr #8]
d0011ea0:	f1b9e7e8 			; <UNDEFINED> instruction: 0xf1b9e7e8
d0011ea4:	d0050f26 	andle	r0, r5, r6, lsr #30
d0011ea8:	0f7cf1b9 	svceq	0x007cf1b9
d0011eac:	f1b9d002 			; <UNDEFINED> instruction: 0xf1b9d002
d0011eb0:	d10d0f5e 	tstle	sp, lr, asr pc
d0011eb4:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011eb8:	f1b9f98e 			; <UNDEFINED> instruction: 0xf1b9f98e
d0011ebc:	d05f0f26 	subsle	r0, pc, r6, lsr #30
d0011ec0:	0f7cf1b9 	svceq	0x007cf1b9
d0011ec4:	172bf240 	strne	pc, [fp, -r0, asr #4]!
d0011ec8:	f44fbf08 			; <UNDEFINED> instruction: 0xf44fbf08
d0011ecc:	e7d17795 	bfi	r7, r5, #15, #3
d0011ed0:	0f3df1b9 	svceq	0x003df1b9
d0011ed4:	f1a9d112 			; <UNDEFINED> instruction: 0xf1a9d112
d0011ed8:	2b02033c 	blcs	0xd0092bd0
d0011edc:	f1b9d911 			; <UNDEFINED> instruction: 0xf1b9d911
d0011ee0:	d1300f2d 	teqle	r0, sp, lsr #30
d0011ee4:	0f3ef1b8 	svceq	0x003ef1b8
d0011ee8:	4620d13e 			; <UNDEFINED> instruction: 0x4620d13e
d0011eec:	7791f44f 	ldrvc	pc, [r1, pc, asr #8]
d0011ef0:	f971f7fe 			; <UNDEFINED> instruction: 0xf971f7fe
d0011ef4:	f1b9e7be 			; <UNDEFINED> instruction: 0xf1b9e7be
d0011ef8:	d1130f3d 	tstle	r3, sp, lsr pc
d0011efc:	0f21f1b9 	svceq	0x0021f1b9
d0011f00:	4620d1e9 	strtmi	sp, [r0], -r9, ror #3
d0011f04:	f967f7fe 			; <UNDEFINED> instruction: 0xf967f7fe
d0011f08:	0f3df1b9 	svceq	0x003df1b9
d0011f0c:	f1b9d03b 			; <UNDEFINED> instruction: 0xf1b9d03b
d0011f10:	d03b0f21 	eorsle	r0, fp, r1, lsr #30
d0011f14:	0f3cf1b9 	svceq	0x003cf1b9
d0011f18:	171ff240 	ldrne	pc, [pc, -r0, asr #4]
d0011f1c:	f44fbf08 			; <UNDEFINED> instruction: 0xf44fbf08
d0011f20:	e7a7778f 	str	r7, [r7, pc, lsl #15]!
d0011f24:	0f26f1b9 	svceq	0x0026f1b9
d0011f28:	f1b9d002 			; <UNDEFINED> instruction: 0xf1b9d002
d0011f2c:	d10a0f7c 	tstle	sl, ip, ror pc
d0011f30:	f2404620 	vmax.s8	d20, d0, d16
d0011f34:	f7fe1721 			; <UNDEFINED> instruction: 0xf7fe1721
d0011f38:	f1b8f94e 			; <UNDEFINED> instruction: 0xf1b8f94e
d0011f3c:	bf080f26 	svclt	0x00080f26
d0011f40:	7790f44f 	ldrvc	pc, [r0, pc, asr #8]
d0011f44:	f1b9e796 			; <UNDEFINED> instruction: 0xf1b9e796
d0011f48:	d10d0f00 	tstle	sp, r0, lsl #30
d0011f4c:	b9436da3 	stmdblt	r3, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0011f50:	447b4b43 	ldrbtmi	r4, [fp], #-2883	; 0xfffff4bd
d0011f54:	9b0665a3 	blls	0xd01ab5e8
d0011f58:	9b0765e3 	blls	0xd01eb6ec
d0011f5c:	ba18e9c4 	blt	0xd064c674
d0011f60:	f24066a3 	vmax.s8	d22, d16, d19
d0011f64:	e7851705 	str	r1, [r5, r5, lsl #14]
d0011f68:	0f3df1b8 	svceq	0x003df1b8
d0011f6c:	d181464f 	orrle	r4, r1, pc, asr #12
d0011f70:	4649483c 			; <UNDEFINED> instruction: 0x4649483c
d0011f74:	f00f4478 			; <UNDEFINED> instruction: 0xf00f4478
d0011f78:	2800f8d5 	stmdacs	r0, {r0, r2, r4, r6, r7, fp, ip, sp, lr, pc}
d0011f7c:	e779d1e6 	ldrb	sp, [r9, -r6, ror #3]!
d0011f80:	1729f240 	strne	pc, [r9, -r0, asr #4]!
d0011f84:	f44fe776 	vst1.16	{d30}, [pc :256], r6
d0011f88:	e773778e 	ldrb	r7, [r3, -lr, lsl #15]!
d0011f8c:	171df240 	ldrne	pc, [sp, -r0, asr #4]
d0011f90:	6da3e770 	stcvs	7, cr14, [r3, #448]!	; 0x1c0
d0011f94:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0011f98:	4a33ace3 	bmi	0xd0cfd32c
d0011f9c:	3068f89d 	mlscc	r8, sp, r8, pc	; <UNPREDICTABLE>
d0011fa0:	65a2447a 	strvs	r4, [r2, #1146]!	; 0x47a
d0011fa4:	65e29a17 	strbvs	r9, [r2, #2583]!	; 0xa17
d0011fa8:	e9c49a18 	stmib	r4, {r3, r4, r9, fp, ip, pc}^
d0011fac:	9b1b2318 	blls	0xd06dac14
d0011fb0:	e4d566a3 	ldrb	r6, [r5], #1699	; 0x6a3
d0011fb4:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0011fb8:	ad0caca4 	stcge	12, cr10, [ip, #-656]	; 0xfffffd70
d0011fbc:	46284621 	strtmi	r4, [r8], -r1, lsr #12
d0011fc0:	f928f7fe 			; <UNDEFINED> instruction: 0xf928f7fe
d0011fc4:	68e29b0e 	stmiavs	r2!, {r1, r2, r3, r8, r9, fp, ip, pc}^
d0011fc8:	9b0f930a 	blls	0xd03f6bf8
d0011fcc:	93069f0c 	movwls	r9, #28428	; 0x6f0c
d0011fd0:	f8dd9b13 			; <UNDEFINED> instruction: 0xf8dd9b13
d0011fd4:	9307b040 	movwls	fp, #28736	; 0x7040
d0011fd8:	f89d6863 			; <UNDEFINED> instruction: 0xf89d6863
d0011fdc:	429aa048 	addsmi	sl, sl, #72	; 0x48
d0011fe0:	ad63f47f 	cfstrdge	mvd15, [r3, #-508]!	; 0xfffffe04
d0011fe4:	e5f14634 	ldrb	r4, [r1, #1588]!	; 0x634
d0011fe8:	4620900a 	strtmi	r9, [r0], -sl
d0011fec:	f8eaf7fe 			; <UNDEFINED> instruction: 0xf8eaf7fe
d0011ff0:	0020f040 	eoreq	pc, r0, r0, asr #32
d0011ff4:	2878990a 	ldmdacs	r8!, {r1, r3, r8, fp, ip, pc}^
d0011ff8:	ae5bf43f 	mrcge	4, 2, APSR_nzcv, cr11, cr15, {1}
d0011ffc:	e58e2708 	str	r2, [lr, #1800]	; 0x708
d0012000:	f47f45c1 			; <UNDEFINED> instruction: 0xf47f45c1
d0012004:	f1b9af6c 			; <UNDEFINED> instruction: 0xf1b9af6c
d0012008:	d0030f2b 	andle	r0, r3, fp, lsr #30
d001200c:	0f2df1b9 	svceq	0x002df1b9
d0012010:	af71f47f 	svcge	0x0071f47f
d0012014:	f2404620 	vmax.s8	d20, d0, d16
d0012018:	f7fe1723 			; <UNDEFINED> instruction: 0xf7fe1723
d001201c:	f1b8f8dc 			; <UNDEFINED> instruction: 0xf1b8f8dc
d0012020:	bf180f2b 	svclt	0x00180f2b
d0012024:	7792f44f 	ldrvc	pc, [r2, pc, asr #8]
d0012028:	bf00e724 	svclt	0x0000e724
d001202c:	fffffd4d 			; <UNDEFINED> instruction: 0xfffffd4d
d0012030:	fffffd19 			; <UNDEFINED> instruction: 0xfffffd19
d0012034:	fffffce9 			; <UNDEFINED> instruction: 0xfffffce9
d0012038:	0000f5e6 	andeq	pc, r0, r6, ror #11
d001203c:	0000f5fe 	strdeq	pc, [r0], -lr
d0012040:	fffffbd5 			; <UNDEFINED> instruction: 0xfffffbd5
d0012044:	fffffb78 			; <UNDEFINED> instruction: 0xfffffb78
d0012048:	fffffb55 			; <UNDEFINED> instruction: 0xfffffb55
d001204c:	fffffb3e 			; <UNDEFINED> instruction: 0xfffffb3e
d0012050:	fffffb05 			; <UNDEFINED> instruction: 0xfffffb05
d0012054:	fffffac5 			; <UNDEFINED> instruction: 0xfffffac5
d0012058:	fffff938 			; <UNDEFINED> instruction: 0xfffff938
d001205c:	fffff94a 			; <UNDEFINED> instruction: 0xfffff94a
d0012060:	fffff971 			; <UNDEFINED> instruction: 0xfffff971
d0012064:	fffff94b 			; <UNDEFINED> instruction: 0xfffff94b
d0012068:	fffff7e0 			; <UNDEFINED> instruction: 0xfffff7e0

Disassembly of section .text.scan_directive:

d00123b0 <.text.scan_directive>:
d00123b0:	e92db082 	push	{r1, r7, ip, sp, pc}
d00123b4:	ed2d4ff0 	vstr	FPSCR_nzcvqc, [sp, #-448]!	; 0xfffffe40
d00123b8:	b09b8b02 	addslt	r8, fp, r2, lsl #22
d00123bc:	ee08460c 	cfmadd32	mvax0, mvfx4, mvfx8, mvfx12
d00123c0:	a9260a10 	stmdbge	r6!, {r4, r9, fp}
d00123c4:	000ce881 	andeq	lr, ip, r1, lsl #17
d00123c8:	9d299b2a 	vstmdbls	r9!, {d9-d29}
d00123cc:	9b2d9308 	blls	0xd0b76ff4
d00123d0:	a0b0f89d 	umlalsge	pc, r0, sp, r8	; <UNPREDICTABLE>
d00123d4:	68e39309 	stmiavs	r3!, {r0, r3, r8, r9, ip, pc}^
d00123d8:	6963930f 	stmdbvs	r3!, {r0, r1, r2, r3, r8, r9, ip, pc}^
d00123dc:	21009310 	tstcs	r0, r0, lsl r3
d00123e0:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d00123e4:	2820feef 	stmdacs	r0!, {r0, r1, r2, r3, r5, r6, r7, r9, sl, fp, ip, sp, lr, pc}
d00123e8:	2809d02a 	stmdacs	r9, {r1, r3, r5, ip, lr, pc}
d00123ec:	6827d028 	stmdavs	r7!, {r3, r5, ip, lr, pc}
d00123f0:	441f68e3 	ldrmi	r6, [pc], #-2275	; 0xd00123f8
d00123f4:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d00123f8:	fee4f7fd 	mcr2	7, 7, pc, cr4, cr13, {7}	; <UNPREDICTABLE>
d00123fc:	ffc3f7fd 			; <UNDEFINED> instruction: 0xffc3f7fd
d0012400:	bb084681 	bllt	0xd0223e0c
d0012404:	68e36822 	stmiavs	r3!, {r1, r5, fp, sp, lr}^
d0012408:	1bd2441a 	blne	0xcf4a3478
d001240c:	d11f2a07 	tstle	pc, r7, lsl #20
d0012410:	1964f8df 	stmdbne	r4!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d0012414:	920a4638 	andls	r4, sl, #56, 12	; 0x3800000
d0012418:	f00d4479 			; <UNDEFINED> instruction: 0xf00d4479
d001241c:	fab0fa67 	blx	0xcec50dc0
d0012420:	9a0af680 	bls	0xd02cfe28
d0012424:	f04f0976 			; <UNDEFINED> instruction: 0xf04f0976
d0012428:	2a050b00 	bcs	0xd0155030
d001242c:	f8cd46d8 			; <UNDEFINED> instruction: 0xf8cd46d8
d0012430:	f8cdb030 			; <UNDEFINED> instruction: 0xf8cdb030
d0012434:	f8cdb028 			; <UNDEFINED> instruction: 0xf8cdb028
d0012438:	d132b02c 	teqle	r2, ip, lsr #32
d001243c:	bc8cf000 	stclt	0, cr15, [ip], {0}
d0012440:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0012444:	e7cafec8 	strb	pc, [sl, r8, asr #29]	; <UNPREDICTABLE>
d0012448:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d001244c:	e7d1fec4 	ldrb	pc, [r1, r4, asr #29]	; <UNPREDICTABLE>
d0012450:	f0402a06 			; <UNDEFINED> instruction: 0xf0402a06
d0012454:	f8df8465 			; <UNDEFINED> instruction: 0xf8df8465
d0012458:	46381924 	ldrtmi	r1, [r8], -r4, lsr #18
d001245c:	464e920a 	strbmi	r9, [lr], -sl, lsl #4
d0012460:	f00d4479 			; <UNDEFINED> instruction: 0xf00d4479
d0012464:	f8dffa43 			; <UNDEFINED> instruction: 0xf8dffa43
d0012468:	fab01918 	blx	0xcec188d0
d001246c:	9a0af880 	bls	0xd02d0674
d0012470:	46384479 			; <UNDEFINED> instruction: 0x46384479
d0012474:	fa3af00d 	blx	0xd0ece4b0
d0012478:	f380fab0 			; <UNDEFINED> instruction: 0xf380fab0
d001247c:	1904f8df 	stmdbne	r4, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d0012480:	095b4638 	ldmdbeq	fp, {r3, r4, r5, r9, sl, lr}^
d0012484:	44799a0a 	ldrbtmi	r9, [r9], #-2570	; 0xfffff5f6
d0012488:	1858ea4f 	ldmdane	r8, {r0, r1, r2, r3, r6, r9, fp, sp, lr, pc}^
d001248c:	f00d930b 			; <UNDEFINED> instruction: 0xf00d930b
d0012490:	fab0fa2d 	blx	0xcec50d4c
d0012494:	f8cdfb80 			; <UNDEFINED> instruction: 0xf8cdfb80
d0012498:	f8cd9030 			; <UNDEFINED> instruction: 0xf8cd9030
d001249c:	ea4f9028 	b	0xd13f6544
d00124a0:	23001b5b 	movwcs	r1, #2907	; 0xb5b
d00124a4:	930d930e 	movwls	r9, #54030	; 0xd30e
d00124a8:	2a02e03a 	bcs	0xd00ca598
d00124ac:	2a04d022 	bcs	0xd014653c
d00124b0:	d1b8464e 			; <UNDEFINED> instruction: 0xd1b8464e
d00124b4:	18d0f8df 	ldmne	r0, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d00124b8:	920a4638 	andls	r4, sl, #56, 12	; 0x3800000
d00124bc:	447946cb 	ldrbtmi	r4, [r9], #-1739	; 0xfffff935
d00124c0:	f00d46c8 			; <UNDEFINED> instruction: 0xf00d46c8
d00124c4:	fab0fa13 	blx	0xcec50d18
d00124c8:	f8dff380 			; <UNDEFINED> instruction: 0xf8dff380
d00124cc:	463818c0 	ldrtmi	r1, [r8], -r0, asr #17
d00124d0:	9a0a095b 	bls	0xd0294a44
d00124d4:	930e4479 	movwls	r4, #58489	; 0xe479
d00124d8:	fa08f00d 	blx	0xd024e514
d00124dc:	f380fab0 			; <UNDEFINED> instruction: 0xf380fab0
d00124e0:	9034f8cd 	eorsls	pc, r4, sp, asr #17
d00124e4:	9030f8cd 	eorsls	pc, r0, sp, asr #17
d00124e8:	f8cd095b 			; <UNDEFINED> instruction: 0xf8cd095b
d00124ec:	f8cd9028 			; <UNDEFINED> instruction: 0xf8cd9028
d00124f0:	e015902c 	ands	r9, r5, ip, lsr #32
d00124f4:	1898f8df 	ldmne	r8, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d00124f8:	46cb4638 			; <UNDEFINED> instruction: 0x46cb4638
d00124fc:	447946c8 	ldrbtmi	r4, [r9], #-1736	; 0xfffff938
d0012500:	f00d464e 			; <UNDEFINED> instruction: 0xf00d464e
d0012504:	fab0f9f3 	blx	0xcec50cd8
d0012508:	f8cdf380 			; <UNDEFINED> instruction: 0xf8cdf380
d001250c:	095b9038 	ldmdbeq	fp, {r3, r4, r5, ip, pc}^
d0012510:	9030f8cd 	eorsls	pc, r0, sp, asr #17
d0012514:	9028f8cd 	eorls	pc, r8, sp, asr #17
d0012518:	464b930d 	strbmi	r9, [fp], -sp, lsl #6
d001251c:	902cf8cd 	eorls	pc, ip, sp, asr #17
d0012520:	0708ea56 	smlsdeq	r8, r6, sl, lr
d0012524:	815cf000 	cmphi	ip, r0	; <UNPREDICTABLE>
d0012528:	93114620 	tstls	r1, #32, 12	; 0x2000000
d001252c:	fe94f7fd 	mrc2	7, 4, pc, cr4, cr13, {7}
d0012530:	28009b11 	stmdacs	r0, {r0, r4, r8, r9, fp, ip, pc}
d0012534:	8154f000 	cmphi	r4, r0	; <UNPREDICTABLE>
d0012538:	f10d9b0f 			; <UNDEFINED> instruction: 0xf10d9b0f
d001253c:	ae120c98 	mrcge	12, 0, r0, cr2, cr8, {4}
d0012540:	9b1060e3 	blls	0xd042a8d4
d0012544:	e8bc6163 	ldm	ip!, {r0, r1, r5, r6, r8, sp, lr}
d0012548:	c60f000f 	strgt	r0, [pc], -pc
d001254c:	000fe89c 	muleq	pc, ip, r8	; <UNPREDICTABLE>
d0012550:	000fe886 	andeq	lr, pc, r6, lsl #17
d0012554:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d0012558:	fe34f7fd 	mrc2	7, 1, pc, cr4, cr13, {7}
d001255c:	d0332820 	eorsle	r2, r3, r0, lsr #16
d0012560:	d0312809 	eorsle	r2, r1, r9, lsl #16
d0012564:	68e36826 	stmiavs	r3!, {r1, r2, r5, fp, sp, lr}^
d0012568:	2100441e 	tstcs	r0, lr, lsl r4
d001256c:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0012570:	f7fdfe29 			; <UNDEFINED> instruction: 0xf7fdfe29
d0012574:	bb58ff08 	bllt	0xd165219c
d0012578:	68e36822 	stmiavs	r3!, {r1, r5, fp, sp, lr}^
d001257c:	1b92441a 	blne	0xce4a35ec
d0012580:	d1292a07 			; <UNDEFINED> instruction: 0xd1292a07
d0012584:	180cf8df 	stmdane	ip, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d0012588:	44794630 	ldrbtmi	r4, [r9], #-1584	; 0xfffff9d0
d001258c:	f9aef00d 			; <UNDEFINED> instruction: 0xf9aef00d
d0012590:	b3584607 	cmplt	r8, #7340032	; 0x700000
d0012594:	b94b6da3 	stmdblt	fp, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0012598:	37fcf8df 	ubfxcc	pc, pc, #17, #29
d001259c:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d00125a0:	9b083516 	blls	0xd021fa00
d00125a4:	3a18e9c4 	bcc	0xd064ccbc
d00125a8:	66a39b09 	strtvs	r9, [r3], r9, lsl #22
d00125ac:	ee184621 	cfmsub32	mvax1, mvfx4, mvfx8, mvfx1
d00125b0:	f7fd0a10 			; <UNDEFINED> instruction: 0xf7fd0a10
d00125b4:	ee18fe2f 	cdp	14, 1, cr15, cr8, cr15, {1}
d00125b8:	b01b0a10 	andslt	r0, fp, r0, lsl sl
d00125bc:	8b02ecbd 	blhi	0xd00cd8b8
d00125c0:	4ff0e8bd 	svcmi	0x00f0e8bd
d00125c4:	4770b002 	ldrbmi	fp, [r0, -r2]!
d00125c8:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d00125cc:	e7c1fe04 	strb	pc, [r1, r4, lsl #28]	; <UNPREDICTABLE>
d00125d0:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d00125d4:	e7c8fe00 	strb	pc, [r8, r0, lsl #28]	; <UNPREDICTABLE>
d00125d8:	d1db2a06 	bicsle	r2, fp, r6, lsl #20
d00125dc:	17bcf8df 	sbfxne	pc, pc, #17, #29
d00125e0:	44794630 	ldrbtmi	r4, [r9], #-1584	; 0xfffff9d0
d00125e4:	f982f00d 			; <UNDEFINED> instruction: 0xf982f00d
d00125e8:	d1d32800 	bicsle	r2, r3, r0, lsl #16
d00125ec:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d00125f0:	fde8f7fd 	stc2l	7, cr15, [r8, #1012]!	; 0x3f4
d00125f4:	d0162820 	andsle	r2, r6, r0, lsr #16
d00125f8:	d0142809 	andsle	r2, r4, r9, lsl #16
d00125fc:	d0552f00 	subsle	r2, r5, r0, lsl #30
d0012600:	68e76826 	stmiavs	r7!, {r1, r2, r5, fp, sp, lr}^
d0012604:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d0012608:	fddcf7fd 	ldc2l	7, cr15, [ip, #1012]	; 0x3f4
d001260c:	febbf7fd 	mrc2	7, 5, pc, cr11, cr13, {7}
d0012610:	6fa3b968 	svcvs	0x00a3b968
d0012614:	da0e2b00 	ble	0xd039d21c
d0012618:	2b006da3 	blcs	0xd002dcac
d001261c:	f8dfd1c6 			; <UNDEFINED> instruction: 0xf8dfd1c6
d0012620:	447b3780 	ldrbtmi	r3, [fp], #-1920	; 0xfffff880
d0012624:	4620e7bb 			; <UNDEFINED> instruction: 0x4620e7bb
d0012628:	fdd5f7fd 	ldc2l	7, cr15, [r5, #1012]	; 0x3f4
d001262c:	4620e7de 			; <UNDEFINED> instruction: 0x4620e7de
d0012630:	fdd1f7fd 	ldc2l	7, cr15, [r1, #1012]	; 0x3f4
d0012634:	6822e7e6 	stmdavs	r2!, {r1, r2, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d0012638:	68e319f0 	stmiavs	r3!, {r4, r5, r6, r7, r8, fp, ip}^
d001263c:	1a12441a 	bne	0xd04a36ac
d0012640:	d1e92a04 	mvnle	r2, r4, lsl #20
d0012644:	175cf8df 	smmlsne	ip, pc, r8, pc	; <UNPREDICTABLE>
d0012648:	f00d4479 			; <UNDEFINED> instruction: 0xf00d4479
d001264c:	2800f94f 	stmdacs	r0, {r0, r1, r2, r3, r6, r8, fp, ip, sp, lr, pc}
d0012650:	6fa3d1e2 	svcvs	0x00a3d1e2
d0012654:	72a6f44f 	adcvc	pc, r6, #1325400064	; 0x4f000000
d0012658:	4303fb02 	movwmi	pc, #15106	; 0x3b02	; <UNPREDICTABLE>
d001265c:	f8832201 			; <UNDEFINED> instruction: 0xf8832201
d0012660:	2100230a 	tstcs	r0, sl, lsl #6
d0012664:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0012668:	2820fdad 	stmdacs	r0!, {r0, r2, r3, r5, r7, r8, sl, fp, ip, sp, lr, pc}
d001266c:	80b4f000 	adcshi	pc, r4, r0
d0012670:	f0002809 			; <UNDEFINED> instruction: 0xf0002809
d0012674:	68e280b1 	stmiavs	r2!, {r0, r4, r5, r7, pc}^
d0012678:	429a6863 	addsmi	r6, sl, #6488064	; 0x630000
d001267c:	80a6f000 	adchi	pc, r6, r0
d0012680:	f000280d 			; <UNDEFINED> instruction: 0xf000280d
d0012684:	280a80a3 	stmdacs	sl, {r0, r1, r5, r7, pc}
d0012688:	80a0f000 	adchi	pc, r0, r0
d001268c:	d106282f 	tstle	r6, pc, lsr #16
d0012690:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d0012694:	fd96f7fd 	ldc2	7, cr15, [r6, #1012]	; 0x3f4
d0012698:	f000282f 			; <UNDEFINED> instruction: 0xf000282f
d001269c:	6da38097 	stcvs	0, cr8, [r3, #604]!	; 0x25c
d00126a0:	d1832b00 	orrle	r2, r3, r0, lsl #22
d00126a4:	3700f8df 			; <UNDEFINED> instruction: 0x3700f8df
d00126a8:	e778447b 			; <UNDEFINED> instruction: 0xe778447b
d00126ac:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d00126b0:	2822fd92 	stmdacs	r2!, {r1, r4, r7, r8, sl, fp, ip, sp, lr, pc}
d00126b4:	d0094680 	andle	r4, r9, r0, lsl #13
d00126b8:	d01c283c 	andsle	r2, ip, ip, lsr r8
d00126bc:	2b006da3 	blcs	0xd002dd50
d00126c0:	af74f47f 	svcge	0x0074f47f
d00126c4:	36e4f8df 	usatcc	pc, #4, pc, asr #17	; <UNPREDICTABLE>
d00126c8:	e768447b 			; <UNDEFINED> instruction: 0xe768447b
d00126cc:	68264681 	stmdavs	r6!, {r0, r7, r9, sl, lr}
d00126d0:	210068e7 	smlattcs	r0, r7, r8, r6
d00126d4:	68e24620 	stmiavs	r2!, {r5, r9, sl, lr}^
d00126d8:	fd74f7fd 	ldc2l	7, cr15, [r4, #-1012]!	; 0xfffffc0c
d00126dc:	429a6863 	addsmi	r6, sl, #6488064	; 0x630000
d00126e0:	4581d30c 	strmi	sp, [r1, #780]	; 0x30c
d00126e4:	6da3d014 	stcvs	0, cr13, [r3, #80]!	; 0x50
d00126e8:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d00126ec:	f8dfaf5f 			; <UNDEFINED> instruction: 0xf8dfaf5f
d00126f0:	447b36c0 	ldrbtmi	r3, [fp], #-1728	; 0xfffff940
d00126f4:	f04fe753 			; <UNDEFINED> instruction: 0xf04fe753
d00126f8:	e7e8093e 			; <UNDEFINED> instruction: 0xe7e8093e
d00126fc:	d0074581 	andle	r4, r7, r1, lsl #11
d0012700:	d0f0280d 	rscsle	r2, r0, sp, lsl #16
d0012704:	d0ee280a 	rscle	r2, lr, sl, lsl #16
d0012708:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d001270c:	e7e0fd64 	strb	pc, [r0, r4, ror #26]!	; <UNPREDICTABLE>
d0012710:	68264437 	stmdavs	r6!, {r0, r1, r2, r4, r5, sl, lr}
d0012714:	1bf64416 	blne	0xcfda3774
d0012718:	4620d0e5 	strtmi	sp, [r0], -r5, ror #1
d001271c:	fd5bf7fd 	ldc2l	7, cr15, [fp, #-1012]	; 0xfffffc0c
d0012720:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d0012724:	fd4ef7fd 	stc2l	7, cr15, [lr, #-1012]	; 0xfffffc0c
d0012728:	d0f62820 	rscsle	r2, r6, r0, lsr #16
d001272c:	d0f42809 	rscsle	r2, r4, r9, lsl #16
d0012730:	686368e2 	stmdavs	r3!, {r1, r5, r6, r7, fp, sp, lr}^
d0012734:	d013429a 	mulsle	r3, sl, r2
d0012738:	d011280d 	andsle	r2, r1, sp, lsl #16
d001273c:	d00f280a 	andle	r2, pc, sl, lsl #16
d0012740:	d105282f 	tstle	r5, pc, lsr #16
d0012744:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d0012748:	fd3cf7fd 	ldc2	7, cr15, [ip, #-1012]!	; 0xfffffc0c
d001274c:	d007282f 	andle	r2, r7, pc, lsr #16
d0012750:	2b006da3 	blcs	0xd002dde4
d0012754:	af2af47f 	svcge	0x002af47f
d0012758:	3658f8df 			; <UNDEFINED> instruction: 0x3658f8df
d001275c:	e71e447b 			; <UNDEFINED> instruction: 0xe71e447b
d0012760:	d11b2e06 	tstle	fp, r6, lsl #28
d0012764:	1650f8df 			; <UNDEFINED> instruction: 0x1650f8df
d0012768:	46384632 			; <UNDEFINED> instruction: 0x46384632
d001276c:	f00d4479 			; <UNDEFINED> instruction: 0xf00d4479
d0012770:	b998f8bd 	ldmiblt	r8, {r0, r2, r3, r4, r5, r7, fp, ip, sp, lr, pc}
d0012774:	ee189b08 	vnmls.f64	d9, d8, d8
d0012778:	95154a10 	ldrls	r4, [r5, #-2576]	; 0xfffff5f0
d001277c:	9316ad12 	tstls	r6, #1152	; 0x480
d0012780:	7383f44f 	orrvc	pc, r3, #1325400064	; 0x4f000000
d0012784:	a060f88d 	rsbge	pc, r0, sp, lsl #17
d0012788:	9b099317 	blls	0xd02773ec
d001278c:	cd0f9319 	stcgt	3, cr9, [pc, #-100]	; 0xd0012730
d0012790:	e895c40f 	ldm	r5, {r0, r1, r2, r3, sl, lr, pc}
d0012794:	e884000f 	stm	r4, {r0, r1, r2, r3}
d0012798:	e70c000f 	str	r0, [ip, -pc]
d001279c:	0f22f1b8 	svceq	0x0022f1b8
d00127a0:	6da3d007 	stcvs	0, cr13, [r3, #28]!
d00127a4:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d00127a8:	f8dfaf01 			; <UNDEFINED> instruction: 0xf8dfaf01
d00127ac:	447b3610 	ldrbtmi	r3, [fp], #-1552	; 0xfffff9f0
d00127b0:	9b09e6f5 	blls	0xd028c38c
d00127b4:	9a084629 	bls	0xd0224060
d00127b8:	93004620 	movwls	r4, #1568	; 0x620
d00127bc:	96024653 			; <UNDEFINED> instruction: 0x96024653
d00127c0:	f7fe9701 			; <UNDEFINED> instruction: 0xf7fe9701
d00127c4:	2800fda5 	stmdacs	r0, {r0, r2, r5, r7, r8, sl, fp, ip, sp, lr, pc}
d00127c8:	aef0f43f 	mrcge	4, 7, APSR_nzcv, cr0, cr15, {1}
d00127cc:	ee184621 	cfmsub32	mvax1, mvfx4, mvfx8, mvfx1
d00127d0:	f7ff0a10 			; <UNDEFINED> instruction: 0xf7ff0a10
d00127d4:	e6eef88b 	strbt	pc, [lr], fp, lsl #17	; <UNPREDICTABLE>
d00127d8:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d00127dc:	e740fcfc 			; <UNDEFINED> instruction: 0xe740fcfc
d00127e0:	0206ea49 	andeq	lr, r6, #299008	; 0x49000
d00127e4:	ea42990b 	b	0xd10b8c18
d00127e8:	430a0208 	movwmi	r0, #41480	; 0xa208
d00127ec:	430a990a 	movwmi	r9, #43274	; 0xa90a
d00127f0:	430a990c 	movwmi	r9, #43276	; 0xa90c
d00127f4:	ea42990d 	b	0xd10b8c30
d00127f8:	430a020b 	movwmi	r0, #41483	; 0xa20b
d00127fc:	430a990e 	movwmi	r9, #43278	; 0xa90e
d0012800:	d123431a 			; <UNDEFINED> instruction: 0xd123431a
d0012804:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0012808:	b158fd27 	cmplt	r8, r7, lsr #26	; <UNPREDICTABLE>
d001280c:	b94b6da3 	stmdblt	fp, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0012810:	35acf8df 	strcc	pc, [ip, #2271]!	; 0x8df
d0012814:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0012818:	9b083516 	blls	0xd021fc78
d001281c:	3a18e9c4 	bcc	0xd064cf34
d0012820:	66a39b09 	strtvs	r9, [r3], r9, lsl #22
d0012824:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0012828:	2220fd34 	eorcs	pc, r0, #52, 26	; 0xd00
d001282c:	ee182100 	mufe	f2, f0, f0
d0012830:	f00d0a10 			; <UNDEFINED> instruction: 0xf00d0a10
d0012834:	f44ff83d 	vst2.8	{d31-d32}, [pc :256]!
d0012838:	ee187397 	mrc	3, 0, r7, cr8, cr7, {4}
d001283c:	61532a10 	cmpvs	r3, r0, lsl sl
d0012840:	4620e6b9 			; <UNDEFINED> instruction: 0x4620e6b9
d0012844:	f7fd930f 			; <UNDEFINED> instruction: 0xf7fd930f
d0012848:	9b0ffcc6 	blls	0xd0411b68
d001284c:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d0012850:	f7fd930f 			; <UNDEFINED> instruction: 0xf7fd930f
d0012854:	2820fcb7 	stmdacs	r0!, {r0, r1, r2, r4, r5, r7, sl, fp, ip, sp, lr, pc}
d0012858:	d0f29b0f 	rscsle	r9, r2, pc, lsl #22
d001285c:	d0f02809 	rscsle	r2, r0, r9, lsl #16
d0012860:	46209311 			; <UNDEFINED> instruction: 0x46209311
d0012864:	930f6823 	movwls	r6, #63523	; 0xf823
d0012868:	931068e3 	tstls	r0, #14876672	; 0xe30000
d001286c:	9b0f9a10 	blls	0xd03f90b4
d0012870:	f7fd189f 			; <UNDEFINED> instruction: 0xf7fd189f
d0012874:	6821fd0e 	stmdavs	r1!, {r1, r2, r3, r8, sl, fp, ip, sp, lr, pc}
d0012878:	46bc68e2 	ldrtmi	r6, [ip], r2, ror #17
d001287c:	44119b11 	ldrmi	r9, [r1], #-2833	; 0xfffff4ef
d0012880:	0201f10c 	andeq	pc, r1, #12, 2
d0012884:	d301428a 	movwle	r4, #4746	; 0x128a
d0012888:	e033468c 	eors	r4, r3, ip, lsl #13
d001288c:	0c01f812 	stceq	8, cr15, [r1], {18}
d0012890:	d15a282f 	cmple	sl, pc, lsr #16
d0012894:	282f7810 	stmdacs	pc!, {r4, fp, ip, sp, lr}	; <UNPREDICTABLE>
d0012898:	282ad02c 	stmdacs	sl!, {r2, r3, r5, ip, lr, pc}
d001289c:	f10cd155 			; <UNDEFINED> instruction: 0xf10cd155
d00128a0:	1c500202 	lfmne	f0, 2, [r0], {2}
d00128a4:	d2174288 	andsle	r4, r7, #136, 4	; 0x80000008
d00128a8:	6c01f810 	stcvs	8, cr15, [r1], {16}
d00128ac:	d1112e2a 	tstle	r1, sl, lsr #28
d00128b0:	2e2f7806 	cdpcs	8, 2, cr7, cr15, cr6, {0}
d00128b4:	3202d10e 	andcc	sp, r2, #-2147483645	; 0x80000003
d00128b8:	d21a428a 	andsle	r4, sl, #-1610612728	; 0xa0000008
d00128bc:	0b01f812 	bleq	0xd009090c
d00128c0:	d0f92820 	rscsle	r2, r9, r0, lsr #16
d00128c4:	d0f72809 	rscsle	r2, r7, r9, lsl #16
d00128c8:	b99a6da2 	ldmiblt	sl, {r1, r5, r7, r8, sl, fp, sp, lr}
d00128cc:	24f4f8df 	ldrbtcs	pc, [r4], #2271	; 0x8df	; <UNPREDICTABLE>
d00128d0:	e006447a 	and	r4, r6, sl, ror r4
d00128d4:	e7e44602 	strb	r4, [r4, r2, lsl #12]!
d00128d8:	b95a6da2 	ldmdblt	sl, {r1, r5, r7, r8, sl, fp, sp, lr}^
d00128dc:	24e8f8df 	strbtcs	pc, [r8], #2271	; 0x8df	; <UNPREDICTABLE>
d00128e0:	e9c4447a 	stmib	r4, {r1, r3, r4, r5, r6, sl, lr}^
d00128e4:	9a082516 	bls	0xd021bd44
d00128e8:	2a18e9c4 	bcs	0xd064d000
d00128ec:	66a29a09 	strtvs	r9, [r2], r9, lsl #20
d00128f0:	d1e9e000 	mvnle	lr, r0
d00128f4:	42be4666 	adcsmi	r4, lr, #106954752	; 0x6600000
d00128f8:	f816d906 			; <UNDEFINED> instruction: 0xf816d906
d00128fc:	1e712c01 	cdpne	12, 7, cr2, cr1, cr1, {0}
d0012900:	d0242a20 	eorle	r2, r4, r0, lsr #20
d0012904:	d0222a09 	eorle	r2, r2, r9, lsl #20
d0012908:	93114620 	tstls	r1, #32, 12	; 0x2000000
d001290c:	fca4f7fd 	stc2	7, cr15, [r4], #1012	; 0x3f4
d0012910:	46809b0c 	strmi	r9, [r0], ip, lsl #22
d0012914:	000bea43 	andeq	lr, fp, r3, asr #20
d0012918:	43039b0d 	movwmi	r9, #15117	; 0x3b0d
d001291c:	f0009b11 			; <UNDEFINED> instruction: 0xf0009b11
d0012920:	f24d8090 	vqadd.s8	d24, d29, d0
d0012924:	58e3030c 	stmiapl	r3!, {r2, r3, r8, r9}^
d0012928:	d1122b20 	tstle	r2, r0, lsr #22
d001292c:	2b006da3 	blcs	0xd002dfc0
d0012930:	af7bf47f 	svcge	0x007bf47f
d0012934:	3494f8df 	ldrcc	pc, [r4], #2271	; 0x8df
d0012938:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d001293c:	9b083516 	blls	0xd021fd9c
d0012940:	3a18e9c4 	bcc	0xd064d058
d0012944:	66a39b09 	strtvs	r9, [r3], r9, lsl #22
d0012948:	4694e76f 	ldrmi	lr, [r4], pc, ror #14
d001294c:	460ee798 			; <UNDEFINED> instruction: 0x460ee798
d0012950:	f1b8e7d1 			; <UNDEFINED> instruction: 0xf1b8e7d1
d0012954:	d0720f00 	rsbsle	r0, r2, r0, lsl #30
d0012958:	d0542800 	subsle	r2, r4, r0, lsl #16
d001295c:	d00542be 			; <UNDEFINED> instruction: 0xd00542be
d0012960:	9a109b0f 	bls	0xd04395a4
d0012964:	f7fd5c98 			; <UNDEFINED> instruction: 0xf7fd5c98
d0012968:	b958fd0e 	ldmdblt	r8, {r1, r2, r3, r8, sl, fp, ip, sp, lr, pc}^
d001296c:	b94b6da3 	stmdblt	fp, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0012970:	345cf8df 	ldrbcc	pc, [ip], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d0012974:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0012978:	9b083516 	blls	0xd021fdd8
d001297c:	3a18e9c4 	bcc	0xd064d094
d0012980:	66a39b09 	strtvs	r9, [r3], r9, lsl #22
d0012984:	454e46b9 	strbmi	r4, [lr, #-1721]	; 0xfffff947
d0012988:	d917464a 	ldmdble	r7, {r1, r3, r6, r9, sl, lr}
d001298c:	f1097811 			; <UNDEFINED> instruction: 0xf1097811
d0012990:	46080901 	strmi	r0, [r8], -r1, lsl #18
d0012994:	fcf7f7fd 	ldc2l	7, cr15, [r7], #1012	; 0x3f4
d0012998:	d1f42800 	mvnsle	r2, r0, lsl #16
d001299c:	29093930 	stmdbcs	r9, {r4, r5, r8, fp, ip, sp}
d00129a0:	6da3d9f1 			; <UNDEFINED> instruction: 0x6da3d9f1
d00129a4:	f8dfb95b 			; <UNDEFINED> instruction: 0xf8dfb95b
d00129a8:	447b342c 	ldrbtmi	r3, [fp], #-1068	; 0xfffffbd4
d00129ac:	3516e9c4 	ldrcc	lr, [r6, #-2500]	; 0xfffff63c
d00129b0:	e9c49b08 	stmib	r4, {r3, r8, r9, fp, ip, pc}^
d00129b4:	9b093a18 	blls	0xd026121c
d00129b8:	e00066a3 	and	r6, r0, r3, lsr #13
d00129bc:	1bd2d1f1 	blne	0xcf4c7188
d00129c0:	46204639 			; <UNDEFINED> instruction: 0x46204639
d00129c4:	fcbdf7fd 	ldc2	7, cr15, [sp], #1012	; 0x3f4
d00129c8:	0f00f1bb 	svceq	0x0000f1bb
d00129cc:	43c0d100 	bicmi	sp, r0, #0, 2
d00129d0:	f24d0fc0 	vmax.f32	q8, <illegal reg q14.5>, q0
d00129d4:	f1b8030c 			; <UNDEFINED> instruction: 0xf1b8030c
d00129d8:	58e10f00 	stmiapl	r1!, {r8, r9, sl, fp}^
d00129dc:	2000bf08 	andcs	fp, r0, r8, lsl #30
d00129e0:	50e21c4a 	rscpl	r1, r2, sl, asr #24
d00129e4:	0481eb04 	streq	lr, [r1], #2820	; 0xb04
d00129e8:	738cf64c 	orrvc	pc, ip, #76, 12	; 0x4c00000
d00129ec:	f8042200 			; <UNDEFINED> instruction: 0xf8042200
d00129f0:	f64c8003 			; <UNDEFINED> instruction: 0xf64c8003
d00129f4:	54e0738d 	strbtpl	r7, [r0], #909	; 0x38d
d00129f8:	738ef64c 	orrvc	pc, lr, #76, 12	; 0x4c00000
d00129fc:	f64c54e0 			; <UNDEFINED> instruction: 0xf64c54e0
d0012a00:	54e2738f 	strbtpl	r7, [r2], #911	; 0x38f
d0012a04:	2200e711 	andcs	lr, r0, #4456448	; 0x440000
d0012a08:	96062300 	strls	r2, [r6], -r0, lsl #6
d0012a0c:	9705ae29 	strls	sl, [r5, -r9, lsr #28]
d0012a10:	e9cd466d 	stmib	sp, {r0, r2, r3, r5, r6, r9, sl, lr}^
d0012a14:	ab122312 	blge	0xd049b664
d0012a18:	ce0f9307 	cdpgt	3, 0, cr9, cr15, cr7, {0}
d0012a1c:	6833c50f 	ldmdavs	r3!, {r0, r1, r2, r3, r8, sl, lr, pc}
d0012a20:	602b4620 	eorvs	r4, fp, r0, lsr #12
d0012a24:	cb0eab26 	blgt	0xd03bd6c4
d0012a28:	fb62f7fe 	blx	0xd18d0a2a
d0012a2c:	d0d02800 	sbcsle	r2, r0, r0, lsl #16
d0012a30:	2312e9dd 	tstcs	r2, #3620864	; 0x374000
d0012a34:	bf144313 	svclt	0x00144313
d0012a38:	20002001 	andcs	r2, r0, r1
d0012a3c:	4640e7c9 	strbmi	lr, [r0], -r9, asr #15
d0012a40:	9a0ee7c7 	bls	0xd03cc964
d0012a44:	0002ea49 	andeq	lr, r2, r9, asr #20
d0012a48:	0203ea50 	andeq	lr, r3, #80, 20	; 0x50000
d0012a4c:	80a2f000 	adchi	pc, r2, r0
d0012a50:	21fcf8d4 	ldrsbcs	pc, [ip, #132]!	; 0x84	; <UNPREDICTABLE>
d0012a54:	eb04b112 	bl	0xd013eea4
d0012a58:	6f921242 	svcvs	0x00921242
d0012a5c:	010cf24d 	tsteq	ip, sp, asr #4	; <UNPREDICTABLE>
d0012a60:	42915861 	addsmi	r5, r1, #6356992	; 0x610000
d0012a64:	6da3d806 	stcvs	8, cr13, [r3, #24]!
d0012a68:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0012a6c:	4bdaaede 	blmi	0xcf6be5ec
d0012a70:	e762447b 			; <UNDEFINED> instruction: 0xe762447b
d0012a74:	f1b91e4a 			; <UNDEFINED> instruction: 0xf1b91e4a
d0012a78:	d0100f00 	andsle	r0, r0, r0, lsl #30
d0012a7c:	d00a42be 			; <UNDEFINED> instruction: 0xd00a42be
d0012a80:	b9436da3 	stmdblt	r3, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0012a84:	447b4bd5 	ldrbtmi	r4, [fp], #-3029	; 0xfffff42b
d0012a88:	3516e9c4 	ldrcc	lr, [r6, #-2500]	; 0xfffff63c
d0012a8c:	e9c49b08 	stmib	r4, {r3, r8, r9, fp, ip, pc}^
d0012a90:	9b093a18 	blls	0xd02612f8
d0012a94:	f24d66a3 	vmax.s8	d22, d29, d19
d0012a98:	50e2030c 	rscpl	r0, r2, ip, lsl #6
d0012a9c:	ea4fe6c5 	b	0xd140c5b8
d0012aa0:	b3630881 	cmnlt	r3, #8454144	; 0x810000
d0012aa4:	d10642be 			; <UNDEFINED> instruction: 0xd10642be
d0012aa8:	534ff502 	movtpl	pc, #62722	; 0xf502	; <UNPREDICTABLE>
d0012aac:	eb043322 	bl	0xd011f73c
d0012ab0:	79db0383 	ldmibvc	fp, {r0, r1, r7, r8, r9}^
d0012ab4:	6da3b153 	stfvsd	f3, [r3, #332]!	; 0x14c
d0012ab8:	4bc9b943 	blmi	0xcf280fcc
d0012abc:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0012ac0:	9b083516 	blls	0xd021ff20
d0012ac4:	3a18e9c4 	bcc	0xd064d1dc
d0012ac8:	66a39b09 	strtvs	r9, [r3], r9, lsl #22
d0012acc:	f64c4444 			; <UNDEFINED> instruction: 0xf64c4444
d0012ad0:	5ce37388 	stclpl	3, cr7, [r3], #544	; 0x220
d0012ad4:	f64cb13b 			; <UNDEFINED> instruction: 0xf64cb13b
d0012ad8:	f814738a 			; <UNDEFINED> instruction: 0xf814738a
d0012adc:	fab99003 	blx	0xcee76af0
d0012ae0:	ea4ff989 	b	0xd141110c
d0012ae4:	f64c1959 			; <UNDEFINED> instruction: 0xf64c1959
d0012ae8:	f64c7389 			; <UNDEFINED> instruction: 0xf64c7389
d0012aec:	f804728a 			; <UNDEFINED> instruction: 0xf804728a
d0012af0:	23019003 	movwcs	r9, #4099	; 0x1003
d0012af4:	f64c54a3 			; <UNDEFINED> instruction: 0xf64c54a3
d0012af8:	54a3728b 	strtpl	r7, [r3], #651	; 0x28b
d0012afc:	44a0e695 	strtmi	lr, [r0], #1685	; 0x695
d0012b00:	738bf64c 	orrvc	pc, fp, #76, 12	; 0x4c00000
d0012b04:	3003f818 	andcc	pc, r3, r8, lsl r8	; <UNPREDICTABLE>
d0012b08:	6da3b153 	stfvsd	f3, [r3, #332]!	; 0x14c
d0012b0c:	4bb5b943 	blmi	0xced81020
d0012b10:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0012b14:	9b083516 	blls	0xd021ff74
d0012b18:	3a18e9c4 	bcc	0xd064d230
d0012b1c:	66a39b09 	strtvs	r9, [r3], r9, lsl #22
d0012b20:	22002300 	andcs	r2, r0, #0, 6
d0012b24:	2312e9cd 	tstcs	r2, #3358720	; 0x334000
d0012b28:	7388f64c 	orrvc	pc, r8, #76, 12	; 0x4c00000
d0012b2c:	3003f818 	andcc	pc, r3, r8, lsl r8	; <UNPREDICTABLE>
d0012b30:	f64cb923 			; <UNDEFINED> instruction: 0xf64cb923
d0012b34:	f8087289 			; <UNDEFINED> instruction: 0xf8087289
d0012b38:	e6763002 	ldrbt	r3, [r6], -r2
d0012b3c:	798af64c 	stmibvc	sl, {r2, r3, r6, r9, sl, ip, sp, lr, pc}
d0012b40:	3009f818 	andcc	pc, r9, r8, lsl r8	; <UNPREDICTABLE>
d0012b44:	f64cb12b 			; <UNDEFINED> instruction: 0xf64cb12b
d0012b48:	22007389 	andcs	r7, r0, #603979778	; 0x24000002
d0012b4c:	2003f808 	andcs	pc, r3, r8, lsl #16
d0012b50:	9606e66b 	strls	lr, [r6], -fp, ror #12
d0012b54:	ae29ab12 	vmovge.32	d9[1], sl
d0012b58:	93079705 	movwls	r9, #30469	; 0x7705
d0012b5c:	ce0f466d 	cfmadd32gt	mvax3, mvfx4, mvfx15, mvfx13
d0012b60:	6833c50f 	ldmdavs	r3!, {r0, r1, r2, r3, r8, sl, lr, pc}
d0012b64:	602b4620 	eorvs	r4, fp, r0, lsr #12
d0012b68:	cb0eab26 	blgt	0xd03bd808
d0012b6c:	fac0f7fe 	blx	0xcf050b6c
d0012b70:	2312e9dd 	tstcs	r2, #3620864	; 0x374000
d0012b74:	0103ea52 	tsteq	r3, r2, asr sl
d0012b78:	7189f64c 	orrvc	pc, r9, ip, asr #12
d0012b7c:	2001bf14 	andcs	fp, r1, r4, lsl pc
d0012b80:	43132000 	tstmi	r3, #0
d0012b84:	0001f808 	andeq	pc, r1, r8, lsl #16
d0012b88:	ae4ff43f 	mcrge	4, 2, pc, cr15, cr15, {1}	; <UNPREDICTABLE>
d0012b8c:	f8082301 			; <UNDEFINED> instruction: 0xf8082301
d0012b90:	e64a3009 	strb	r3, [sl], -r9
d0012b94:	0f00f1b8 	svceq	0x0000f1b8
d0012b98:	ae47f43f 	mcrge	4, 2, pc, cr7, cr15, {1}	; <UNPREDICTABLE>
d0012b9c:	9a0a9b0b 	bls	0xd02b97d0
d0012ba0:	f43f4313 			; <UNDEFINED> instruction: 0xf43f4313
d0012ba4:	42beae42 	adcsmi	sl, lr, #1056	; 0x420
d0012ba8:	9b0fd023 	blls	0xd0406c3c
d0012bac:	5c989a10 	vldmiapl	r8, {s18-s33}
d0012bb0:	fbe9f7fd 	blx	0xcfa90bae
d0012bb4:	46b8b1e8 	ldrtmi	fp, [r8], r8, ror #3
d0012bb8:	46434546 	strbmi	r4, [r3], -r6, asr #10
d0012bbc:	4642d90d 	strbmi	sp, [r2], -sp, lsl #18
d0012bc0:	802cf8cd 	eorhi	pc, ip, sp, asr #17
d0012bc4:	1b01f812 	blne	0xd0090c14
d0012bc8:	f7fd4608 			; <UNDEFINED> instruction: 0xf7fd4608
d0012bcc:	b9b8fbdc 	ldmiblt	r8!, {r2, r3, r4, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d0012bd0:	0030f1a1 	eorseq	pc, r0, r1, lsr #3
d0012bd4:	28099b0b 	stmdacs	r9, {r0, r1, r3, r8, r9, fp, ip, pc}
d0012bd8:	eba8d912 	bl	0xcea49028
d0012bdc:	f1bb0b07 			; <UNDEFINED> instruction: 0xf1bb0b07
d0012be0:	d90f0f3f 	stmdble	pc, {r0, r1, r2, r3, r4, r5, r8, r9, sl, fp}	; <UNPREDICTABLE>
d0012be4:	2b006da3 	blcs	0xd002e278
d0012be8:	ae1ff47f 	mrcge	4, 0, APSR_nzcv, cr15, cr15, {3}
d0012bec:	447b4b7e 	ldrbtmi	r4, [fp], #-2942	; 0xfffff482
d0012bf0:	6da3e6a3 	stcvs	6, cr14, [r3, #652]!	; 0x28c
d0012bf4:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0012bf8:	4b7cae18 	blmi	0xd1f3e460
d0012bfc:	e69c447b 			; <UNDEFINED> instruction: 0xe69c447b
d0012c00:	e7d94690 	bfi	r4, r0, #13, #13
d0012c04:	4639465a 			; <UNDEFINED> instruction: 0x4639465a
d0012c08:	930b4620 	movwls	r4, #46624	; 0xb620
d0012c0c:	fb99f7fd 	blx	0xce690c0a
d0012c10:	46819a0a 	strmi	r9, [r1], sl, lsl #20
d0012c14:	b34a9b0b 	movtlt	r9, #43787	; 0xab0b
d0012c18:	d9114546 	ldmdble	r1, {r1, r2, r6, r8, sl, lr}
d0012c1c:	3b01f818 	blcc	0xd0090c84
d0012c20:	d0f92b20 	rscsle	r2, r9, r0, lsr #22
d0012c24:	d0f72b09 	rscsle	r2, r7, r9, lsl #22
d0012c28:	b9536da3 	ldmdblt	r3, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0012c2c:	447b4b70 	ldrbtmi	r4, [fp], #-2928	; 0xfffff490
d0012c30:	3516e9c4 	ldrcc	lr, [r6, #-2500]	; 0xfffff63c
d0012c34:	e9c49b08 	stmib	r4, {r3, r8, r9, fp, ip, pc}^
d0012c38:	9b093a18 	blls	0xd02614a0
d0012c3c:	e00066a3 	and	r6, r0, r3, lsr #13
d0012c40:	f1b9d1f2 			; <UNDEFINED> instruction: 0xf1b9d1f2
d0012c44:	f6ff0f00 			; <UNDEFINED> instruction: 0xf6ff0f00
d0012c48:	f64cadf0 			; <UNDEFINED> instruction: 0xf64cadf0
d0012c4c:	22487388 	subcs	r7, r8, #136, 6	; 0x20000002
d0012c50:	fb0258e1 	blx	0xd00a8fde
d0012c54:	39014009 	stmdbcc	r1, {r0, r3, lr}
d0012c58:	f64a50e1 			; <UNDEFINED> instruction: 0xf64a50e1
d0012c5c:	fb023388 	blx	0xd009fa86
d0012c60:	44184101 	ldrmi	r4, [r8], #-257	; 0xfffffeff
d0012c64:	f00c4419 			; <UNDEFINED> instruction: 0xf00c4419
d0012c68:	e5defe31 	ldrb	pc, [lr, #3633]	; 0xe31	; <UNPREDICTABLE>
d0012c6c:	d9134546 	ldmdble	r3, {r1, r2, r6, r8, sl, lr}
d0012c70:	3000f898 	mulcc	r0, r8, r8
d0012c74:	d1062b28 	tstle	r6, r8, lsr #22
d0012c78:	2b006da3 	blcs	0xd002e30c
d0012c7c:	add5f47f 	cfldrdge	mvd15, [r5, #508]	; 0x1fc
d0012c80:	447b4b5c 	ldrbtmi	r4, [fp], #-2908	; 0xfffff4a4
d0012c84:	4546e659 	strbmi	lr, [r6, #-1625]	; 0xfffff9a7
d0012c88:	d0054643 	andle	r4, r5, r3, asr #12
d0012c8c:	2b01f818 	blcs	0xd0090cf4
d0012c90:	d0f82a20 	rscsle	r2, r8, r0, lsr #20
d0012c94:	d0f62a09 	rscsle	r2, r6, r9, lsl #20
d0012c98:	21002001 	tstcs	r0, r1
d0012c9c:	e9cd429e 	stmib	sp, {r1, r2, r3, r4, r7, r9, lr}^
d0012ca0:	d0130112 	andsle	r0, r3, r2, lsl r1
d0012ca4:	aa129606 	bge	0xd04b84c4
d0012ca8:	9305ae29 	movwls	sl, #24105	; 0x5e29
d0012cac:	46ec9207 	strbtmi	r9, [ip], r7, lsl #4
d0012cb0:	e8acce0f 	stmia	ip!, {r0, r1, r2, r3, r9, sl, fp, lr, pc}
d0012cb4:	6833000f 	ldmdavs	r3!, {r0, r1, r2, r3}
d0012cb8:	f8cc4620 			; <UNDEFINED> instruction: 0xf8cc4620
d0012cbc:	ab263000 	blge	0xd099ecc4
d0012cc0:	f7fecb0e 			; <UNDEFINED> instruction: 0xf7fecb0e
d0012cc4:	2800fa15 	stmdacs	r0, {r0, r2, r4, r9, fp, ip, sp, lr, pc}
d0012cc8:	adaff43f 	cfstrsge	mvf15, [pc, #252]!	; 0xd0012dcc
d0012ccc:	0f00f1b9 	svceq	0x0000f1b9
d0012cd0:	f64cda0e 			; <UNDEFINED> instruction: 0xf64cda0e
d0012cd4:	58e07388 	stmiapl	r0!, {r3, r7, r8, r9, ip, sp, lr}^
d0012cd8:	d1062880 	smlabble	r6, r0, r8, r2
d0012cdc:	2b006da3 	blcs	0xd002e370
d0012ce0:	ada3f47f 	cfstrsge	mvf15, [r3, #508]!	; 0x1fc
d0012ce4:	447b4b44 	ldrbtmi	r4, [fp], #-2884	; 0xfffff4bc
d0012ce8:	1c42e627 	mcrrne	6, 2, lr, r2, cr7
d0012cec:	50e24681 	rscpl	r4, r2, r1, lsl #13
d0012cf0:	f64a2048 			; <UNDEFINED> instruction: 0xf64a2048
d0012cf4:	465a3588 	ldrbmi	r3, [sl], -r8, lsl #11
d0012cf8:	fb004639 	blx	0xd00245e6
d0012cfc:	eb09f909 	bl	0xd0291128
d0012d00:	44200005 	strtmi	r0, [r0], #-5
d0012d04:	f00c444c 			; <UNDEFINED> instruction: 0xf00c444c
d0012d08:	2300fde1 	movwcs	pc, #3553	; 0xde1	; <UNPREDICTABLE>
d0012d0c:	f50444a3 			; <UNDEFINED> instruction: 0xf50444a3
d0012d10:	f80b442b 			; <UNDEFINED> instruction: 0xf80b442b
d0012d14:	e9dd3005 	ldmib	sp, {r0, r2, ip, sp}^
d0012d18:	e9c42312 	stmib	r4, {r1, r4, r8, r9, sp}^
d0012d1c:	e5842332 	str	r2, [r4, #818]	; 0x332
d0012d20:	f47f2a05 			; <UNDEFINED> instruction: 0xf47f2a05
d0012d24:	4935abc2 	ldmdbmi	r5!, {r1, r6, r7, r8, r9, fp, sp, pc}
d0012d28:	920b4638 	andls	r4, fp, #56, 12	; 0x3800000
d0012d2c:	447946cb 	ldrbtmi	r4, [r9], #-1739	; 0xfffff935
d0012d30:	f00c46c8 			; <UNDEFINED> instruction: 0xf00c46c8
d0012d34:	fab0fddb 	blx	0xcec524a8
d0012d38:	4931f380 	ldmdbmi	r1!, {r7, r8, r9, ip, sp, lr, pc}
d0012d3c:	095b4638 	ldmdbeq	fp, {r3, r4, r5, r9, sl, lr}^
d0012d40:	44799a0b 	ldrbtmi	r9, [r9], #-2571	; 0xfffff5f5
d0012d44:	930a464e 	movwls	r4, #42574	; 0xa64e
d0012d48:	fdd0f00c 	ldc2l	0, cr15, [r0, #48]	; 0x30
d0012d4c:	f380fab0 			; <UNDEFINED> instruction: 0xf380fab0
d0012d50:	902cf8cd 	eorls	pc, ip, sp, asr #17
d0012d54:	930c095b 	movwls	r0, #51547	; 0xc95b
d0012d58:	2205492a 	andcs	r4, r5, #688128	; 0xa8000
d0012d5c:	44794638 	ldrbtmi	r4, [r9], #-1592	; 0xfffff9c8
d0012d60:	fdc4f00c 	stc2l	0, cr15, [r4, #48]	; 0x30
d0012d64:	fab02300 	blx	0xcec1b96c
d0012d68:	930ef980 	movwls	pc, #59776	; 0xe980	; <UNPREDICTABLE>
d0012d6c:	1959ea4f 	ldmdbne	r9, {r0, r1, r2, r3, r6, r9, fp, sp, lr, pc}^
d0012d70:	f7ff930d 			; <UNDEFINED> instruction: 0xf7ff930d
d0012d74:	bf00bbd5 	svclt	0x0000bbd5
d0012d78:	fffffc50 			; <UNDEFINED> instruction: 0xfffffc50
d0012d7c:	fffffc10 			; <UNDEFINED> instruction: 0xfffffc10
d0012d80:	fffffc07 			; <UNDEFINED> instruction: 0xfffffc07
d0012d84:	fffffbf8 			; <UNDEFINED> instruction: 0xfffffbf8
d0012d88:	fffffbd6 			; <UNDEFINED> instruction: 0xfffffbd6
d0012d8c:	fffffbc5 			; <UNDEFINED> instruction: 0xfffffbc5
d0012d90:	fffffb93 			; <UNDEFINED> instruction: 0xfffffb93
d0012d94:	fffffade 			; <UNDEFINED> instruction: 0xfffffade
d0012d98:	fffffb08 			; <UNDEFINED> instruction: 0xfffffb08
d0012d9c:	fffffa8e 			; <UNDEFINED> instruction: 0xfffffa8e
d0012da0:	fffffaaa 			; <UNDEFINED> instruction: 0xfffffaaa
d0012da4:	fffffa7f 			; <UNDEFINED> instruction: 0xfffffa7f
d0012da8:	fffffafc 			; <UNDEFINED> instruction: 0xfffffafc
d0012dac:	fffffa36 			; <UNDEFINED> instruction: 0xfffffa36
d0012db0:	fffffa29 			; <UNDEFINED> instruction: 0xfffffa29
d0012db4:	fffff9e6 			; <UNDEFINED> instruction: 0xfffff9e6
d0012db8:	fffffa01 			; <UNDEFINED> instruction: 0xfffffa01
d0012dbc:	fffff9c6 			; <UNDEFINED> instruction: 0xfffff9c6
d0012dc0:	fffff890 			; <UNDEFINED> instruction: 0xfffff890
d0012dc4:	fffff925 			; <UNDEFINED> instruction: 0xfffff925
d0012dc8:	fffff8ea 			; <UNDEFINED> instruction: 0xfffff8ea
d0012dcc:	fffff8e5 			; <UNDEFINED> instruction: 0xfffff8e5
d0012dd0:	fffff8c8 			; <UNDEFINED> instruction: 0xfffff8c8
d0012dd4:	fffff8bb 			; <UNDEFINED> instruction: 0xfffff8bb
d0012dd8:	fffff81d 			; <UNDEFINED> instruction: 0xfffff81d
d0012ddc:	fffff82f 			; <UNDEFINED> instruction: 0xfffff82f
d0012de0:	fffff816 			; <UNDEFINED> instruction: 0xfffff816
d0012de4:	fffff7dd 			; <UNDEFINED> instruction: 0xfffff7dd
d0012de8:	fffff736 			; <UNDEFINED> instruction: 0xfffff736
d0012dec:	fffff703 			; <UNDEFINED> instruction: 0xfffff703
d0012df0:	fffff717 			; <UNDEFINED> instruction: 0xfffff717
d0012df4:	fffff6e0 			; <UNDEFINED> instruction: 0xfffff6e0
d0012df8:	fffff6ab 			; <UNDEFINED> instruction: 0xfffff6ab
d0012dfc:	fffff357 			; <UNDEFINED> instruction: 0xfffff357
d0012e00:	fffff349 			; <UNDEFINED> instruction: 0xfffff349
d0012e04:	fffff340 			; <UNDEFINED> instruction: 0xfffff340

Disassembly of section .text.advance:

d0012e08 <.text.advance>:
d0012e08:	f100b570 			; <UNDEFINED> instruction: 0xf100b570
d0012e0c:	46040638 			; <UNDEFINED> instruction: 0x46040638
d0012e10:	0518f100 	ldreq	pc, [r8, #-256]	; 0xffffff00
d0012e14:	ce0fb088 	cdpgt	0, 0, cr11, cr15, cr8, {4}
d0012e18:	e896c50f 	ldm	r6, {r0, r1, r2, r3, r8, sl, lr, pc}
d0012e1c:	e885000f 	stm	r5, {r0, r1, r2, r3}
d0012e20:	466d000f 	strbtmi	r0, [sp], -pc
d0012e24:	34384621 	ldrtcc	r4, [r8], #-1569	; 0xfffff9df
d0012e28:	f7fe4628 			; <UNDEFINED> instruction: 0xf7fe4628
d0012e2c:	cd0ffd5f 	stcgt	13, cr15, [pc, #-380]	; 0xd0012cb8
d0012e30:	e895c40f 	ldm	r5, {r0, r1, r2, r3, sl, lr, pc}
d0012e34:	e884000f 	stm	r4, {r0, r1, r2, r3}
d0012e38:	b008000f 	andlt	r0, r8, pc
d0012e3c:	Address 0x00000000d0012e3c is out of bounds.


Disassembly of section .text.accept:

d0012e3e <.text.accept>:
d0012e3e:	6d83b508 	cfstr32vs	mvfx11, [r3, #32]
d0012e42:	6ac2b933 	bvs	0xcf0c1316
d0012e46:	d105428a 	smlabble	r5, sl, r2, r4
d0012e4a:	ffddf7ff 			; <UNDEFINED> instruction: 0xffddf7ff
d0012e4e:	bd082001 	stclt	0, cr2, [r8, #-4]
d0012e52:	e7fc2000 	ldrb	r2, [ip, r0]!
d0012e56:	e7fa4618 			; <UNDEFINED> instruction: 0xe7fa4618

Disassembly of section .text.expect:

d0012e5a <.text.expect>:
d0012e5a:	4605b570 			; <UNDEFINED> instruction: 0x4605b570
d0012e5e:	f7ff4616 			; <UNDEFINED> instruction: 0xf7ff4616
d0012e62:	4604ffed 	strmi	pc, [r4], -sp, ror #31
d0012e66:	4631b928 	ldrtmi	fp, [r1], -r8, lsr #18
d0012e6a:	f7fd4628 			; <UNDEFINED> instruction: 0xf7fd4628
d0012e6e:	4620f99c 			; <UNDEFINED> instruction: 0x4620f99c
d0012e72:	2401bd70 	strcs	fp, [r1], #-3440	; 0xfffff290
d0012e76:	Address 0x00000000d0012e76 is out of bounds.


Disassembly of section .text.enum_expression:

d0012f70 <.text.enum_expression>:
d0012f70:	e92d2a19 	push	{r0, r3, r4, r9, fp, sp}
d0012f74:	46804ff8 			; <UNDEFINED> instruction: 0x46804ff8
d0012f78:	4692468b 	ldrmi	r4, [r2], fp, lsl #13
d0012f7c:	4995d106 	ldmibmi	r5, {r1, r2, r8, ip, lr, pc}
d0012f80:	f7fd4479 			; <UNDEFINED> instruction: 0xf7fd4479
d0012f84:	2400f911 	strcs	pc, [r0], #-2321	; 0xfffff6ef
d0012f88:	e0f82500 	rscs	r2, r8, r0, lsl #10
d0012f8c:	2e2b6ac6 	vnmulcs.f32	s12, s23, s12
d0012f90:	2e2dd003 	cdpcs	0, 2, cr13, cr13, cr3, {0}
d0012f94:	2e7ed001 	cdpcs	0, 7, cr13, cr14, cr1, {0}
d0012f98:	4640d133 			; <UNDEFINED> instruction: 0x4640d133
d0012f9c:	ff34f7ff 			; <UNDEFINED> instruction: 0xff34f7ff
d0012fa0:	0201f10a 	andeq	pc, r1, #-2147483646	; 0x80000002
d0012fa4:	46402107 	strbmi	r2, [r0], -r7, lsl #2
d0012fa8:	ffe2f7ff 			; <UNDEFINED> instruction: 0xffe2f7ff
d0012fac:	46042e2d 	strmi	r2, [r4], -sp, lsr #28
d0012fb0:	d11f460d 	tstle	pc, sp, lsl #12
d0012fb4:	eb614244 	bl	0xd18638cc
d0012fb8:	f8d80541 			; <UNDEFINED> instruction: 0xf8d80541
d0012fbc:	2e006058 	mcrcs	0, 0, r6, cr0, cr8, {2}
d0012fc0:	80ddf040 	sbcshi	pc, sp, r0, asr #32
d0012fc4:	902cf8d8 	ldrdls	pc, [ip], -r8	; <UNPREDICTABLE>
d0012fc8:	0f5ef1b9 	svceq	0x005ef1b9
d0012fcc:	80ebf000 	rschi	pc, fp, r0
d0012fd0:	80d9f300 	sbcshi	pc, r9, r0, lsl #6
d0012fd4:	0325f1a9 	msreq	CPSR_sc, #1073741866	; 0x4000002a
d0012fd8:	f2002b0a 	vqdmulh.s<illegal width 8>	d2, d0, d10
d0012fdc:	2b0a80cd 	blcs	0xd02b3318
d0012fe0:	80dff200 	sbcshi	pc, pc, r0, lsl #4
d0012fe4:	f003e8df 			; <UNDEFINED> instruction: 0xf003e8df
d0012fe8:	dddde1db 	ldflep	f6, [sp, #876]	; 0x36c
d0012fec:	ddc7dbdd 	vstrle	d29, [r7, #884]	; 0x374
d0012ff0:	00dbddc7 	sbcseq	sp, fp, r7, asr #27
d0012ff4:	d1e02e7e 	mvnle	r2, lr, ror lr
d0012ff8:	43cb43c2 	bicmi	r4, fp, #134217731	; 0x8000003
d0012ffc:	461d4614 			; <UNDEFINED> instruction: 0x461d4614
d0013000:	2128e7db 	ldrdcs	lr, [r8, -fp]!
d0013004:	ff1bf7ff 			; <UNDEFINED> instruction: 0xff1bf7ff
d0013008:	f10ab170 			; <UNDEFINED> instruction: 0xf10ab170
d001300c:	46400201 	strbmi	r0, [r0], -r1, lsl #4
d0013010:	f7ff2101 			; <UNDEFINED> instruction: 0xf7ff2101
d0013014:	4a70ffad 	bmi	0xd1c52ed0
d0013018:	460d4604 	strmi	r4, [sp], -r4, lsl #12
d001301c:	2129447a 			; <UNDEFINED> instruction: 0x2129447a
d0013020:	f7ff4640 			; <UNDEFINED> instruction: 0xf7ff4640
d0013024:	e7c8ff1a 	bfi	pc, sl, (invalid: 30:8)	; <UNPREDICTABLE>
d0013028:	302cf8d8 	ldrdcc	pc, [ip], -r8	; <UNPREDICTABLE>
d001302c:	7281f5a3 	addvc	pc, r1, #683671552	; 0x28c00000
d0013030:	d80a2a01 	stmdale	sl, {r0, r9, fp, sp}
d0013034:	7f81f5b3 	svcvc	0x0081f5b3
d0013038:	4020f8d8 	ldrdmi	pc, [r0], -r8	; <UNPREDICTABLE>
d001303c:	bf0c4640 	svclt	0x000c4640
d0013040:	250017e5 	strcs	r1, [r0, #-2021]	; 0xfffff81b
d0013044:	fee0f7ff 	mcr2	7, 7, pc, cr0, cr15, {7}	; <UNPREDICTABLE>
d0013048:	4964e7b7 	stmdbmi	r4!, {r0, r1, r2, r4, r5, r7, r8, r9, sl, sp, lr, pc}^
d001304c:	46404479 			; <UNDEFINED> instruction: 0x46404479
d0013050:	4640e797 			; <UNDEFINED> instruction: 0x4640e797
d0013054:	fed8f7ff 	mrc2	7, 6, pc, cr8, cr15, {7}
d0013058:	f10a1c71 			; <UNDEFINED> instruction: 0xf10a1c71
d001305c:	46400201 	strbmi	r0, [r0], -r1, lsl #4
d0013060:	ff86f7ff 			; <UNDEFINED> instruction: 0xff86f7ff
d0013064:	3058f8d8 	ldrsbcc	pc, [r8], #-136	; 0xffffff78	; <UNPREDICTABLE>
d0013068:	460f4606 	strmi	r4, [pc], -r6, lsl #12
d001306c:	d18a2b00 	orrle	r2, sl, r0, lsl #22
d0013070:	0f2ff1b9 	svceq	0x002ff1b9
d0013074:	80a7f000 	adchi	pc, r7, r0
d0013078:	0f25f1b9 	svceq	0x0025f1b9
d001307c:	ea56d115 	b	0xd15c74d8
d0013080:	f0000307 			; <UNDEFINED> instruction: 0xf0000307
d0013084:	1c6b80a3 	stclne	0, cr8, [fp], #-652	; 0xfffffd74
d0013088:	f1b4bf08 			; <UNDEFINED> instruction: 0xf1b4bf08
d001308c:	d0044f00 	andle	r4, r4, r0, lsl #30
d0013090:	f3f6fb94 			; <UNDEFINED> instruction: 0xf3f6fb94
d0013094:	4416fb03 	ldrmi	pc, [r6], #-2819	; 0xfffff4fd
d0013098:	1c7be093 	ldclne	0, cr14, [fp], #-588	; 0xfffffdb4
d001309c:	f1b6bf08 			; <UNDEFINED> instruction: 0xf1b6bf08
d00130a0:	d1023fff 	strdle	r3, [r2, -pc]
d00130a4:	4479494e 	ldrbtmi	r4, [r9], #-2382	; 0xfffff6b2
d00130a8:	f46fe7d1 	vld1.64	{d30}, [pc :64], r1
d00130ac:	eb097093 	bl	0xd026f300
d00130b0:	2b010300 	blcs	0xd0053cb8
d00130b4:	2f00d806 	svccs	0x0000d806
d00130b8:	2e20bf08 	cdpcs	15, 2, cr11, cr0, cr8, {0}
d00130bc:	4949d32c 	stmdbmi	r9, {r2, r3, r5, r8, r9, ip, lr, pc}^
d00130c0:	e7c44479 			; <UNDEFINED> instruction: 0xe7c44479
d00130c4:	0f5ef1b9 	svceq	0x005ef1b9
d00130c8:	dc29d04b 	stcle	0, cr13, [r9], #-300	; 0xfffffed4
d00130cc:	0925f1a9 	stmdbeq	r5!, {r0, r3, r5, r7, r8, ip, sp, lr, pc}
d00130d0:	0f0af1b9 	svceq	0x000af1b9
d00130d4:	af71f63f 	svcge	0x0071f63f
d00130d8:	0f0af1b9 	svceq	0x000af1b9
d00130dc:	af6df63f 	svcge	0x006df63f
d00130e0:	f853a302 			; <UNDEFINED> instruction: 0xf853a302
d00130e4:	44132029 	ldrmi	r2, [r3], #-41	; 0xffffffd7
d00130e8:	bf004718 	svclt	0x00004718
d00130ec:	ffffffa5 			; <UNDEFINED> instruction: 0xffffffa5
d00130f0:	0000006d 	andeq	r0, r0, sp, rrx
d00130f4:	fffffecf 			; <UNDEFINED> instruction: 0xfffffecf
d00130f8:	fffffecf 			; <UNDEFINED> instruction: 0xfffffecf
d00130fc:	fffffecf 			; <UNDEFINED> instruction: 0xfffffecf
d0013100:	0000005d 	andeq	r0, r0, sp, asr r0
d0013104:	0000004d 	andeq	r0, r0, sp, asr #32
d0013108:	fffffecf 			; <UNDEFINED> instruction: 0xfffffecf
d001310c:	00000055 	andeq	r0, r0, r5, asr r0
d0013110:	fffffecf 			; <UNDEFINED> instruction: 0xfffffecf
d0013114:	000000d3 	ldrdeq	r0, [r0], -r3
d0013118:	1327f240 	msrne	CPSR_sxc, #64, 4
d001311c:	d0254599 	mlale	r5, r9, r5, r4
d0013120:	7f94f5b9 	svcvc	0x0094f5b9
d0013124:	f1b9d025 			; <UNDEFINED> instruction: 0xf1b9d025
d0013128:	f47f0f7c 			; <UNDEFINED> instruction: 0xf47f0f7c
d001312c:	ea44af46 	b	0xd113ee4c
d0013130:	ea450206 	b	0xd1153950
d0013134:	e7610307 	strb	r0, [r1, -r7, lsl #6]!
d0013138:	eb4719a4 	bl	0xd11d97d0
d001313c:	e73c0505 	ldr	r0, [ip, -r5, lsl #10]!
d0013140:	eb651ba4 	bl	0xd1959fd8
d0013144:	e7380507 	ldr	r0, [r8, -r7, lsl #10]!
d0013148:	f307fb04 	vqrdmulh.s<illegal width 8>	d15, d7, d4
d001314c:	3305fb06 	movwcc	pc, #23302	; 0x5b06	; <UNPREDICTABLE>
d0013150:	4506fba4 	strmi	pc, [r6, #-2980]	; 0xfffff45c
d0013154:	e730441d 			; <UNDEFINED> instruction: 0xe730441d
d0013158:	0206ea04 	andeq	lr, r6, #4, 20	; 0x4000
d001315c:	0307ea05 	movweq	lr, #31237	; 0x7a05
d0013160:	ea84e74c 	b	0xce14ce98
d0013164:	ea850206 	b	0xce153984
d0013168:	e7470307 	strb	r0, [r7, -r7, lsl #6]
d001316c:	250040b4 	strcs	r4, [r0, #-180]	; 0xffffff4c
d0013170:	40f4e723 	rscsmi	lr, r4, r3, lsr #14
d0013174:	2605e7fb 			; <UNDEFINED> instruction: 0x2605e7fb
d0013178:	f77f45b3 			; <UNDEFINED> instruction: 0xf77f45b3
d001317c:	4620af6a 	strtmi	sl, [r0], -sl, ror #30
d0013180:	e8bd4629 	pop	{r0, r3, r5, r9, sl, lr}
d0013184:	f1b98ff8 			; <UNDEFINED> instruction: 0xf1b98ff8
d0013188:	d0100f7c 	andsle	r0, r0, ip, ror pc
d001318c:	7193f46f 	orrsvc	pc, r3, pc, ror #8
d0013190:	0301eb09 	movweq	lr, #6921	; 0x1b09
d0013194:	bf342b02 	svclt	0x00342b02
d0013198:	26002604 	strcs	r2, [r0], -r4, lsl #12
d001319c:	2606e7ec 	strcs	lr, [r6], -ip, ror #15
d00131a0:	2600e7ea 	strcs	lr, [r0], -sl, ror #15
d00131a4:	2602e7e8 	strcs	lr, [r2], -r8, ror #15
d00131a8:	2603e7e6 	strcs	lr, [r3], -r6, ror #15
d00131ac:	2601e7e4 	strcs	lr, [r1], -r4, ror #15
d00131b0:	1c6ae7e2 	stclne	7, cr14, [sl], #-904	; 0xfffffc78
d00131b4:	f1b4bf08 			; <UNDEFINED> instruction: 0xf1b4bf08
d00131b8:	f43f4f00 			; <UNDEFINED> instruction: 0xf43f4f00
d00131bc:	fb94af6e 	blx	0xce53ef7e
d00131c0:	17e5f4f6 			; <UNDEFINED> instruction: 0x17e5f4f6
d00131c4:	ea56e6f9 	b	0xd15ccdb0
d00131c8:	d1f20307 	mvnsle	r0, r7, lsl #6
d00131cc:	44794906 	ldrbtmi	r4, [r9], #-2310	; 0xfffff6fa
d00131d0:	bf00e73d 	svclt	0x0000e73d
d00131d4:	fffffef4 			; <UNDEFINED> instruction: 0xfffffef4
d00131d8:	fffffe79 			; <UNDEFINED> instruction: 0xfffffe79
d00131dc:	fffffe72 			; <UNDEFINED> instruction: 0xfffffe72
d00131e0:	fffffe76 			; <UNDEFINED> instruction: 0xfffffe76
d00131e4:	fffffe7f 			; <UNDEFINED> instruction: 0xfffffe7f
d00131e8:	fffffd29 			; <UNDEFINED> instruction: 0xfffffd29

Disassembly of section .text.record_type:

d0013254 <.text.record_type>:
d0013254:	4ff7e92d 	svcmi	0x00f7e92d
d0013258:	6ac6460d 	bvs	0xcf1a4a94
d001325c:	718bf46f 	orrvc	pc, fp, pc, ror #8
d0013260:	18734604 	ldmdane	r3!, {r2, r9, sl, lr}^
d0013264:	d8362b01 	ldmdale	r6!, {r0, r8, r9, fp, sp}
d0013268:	fdcef7ff 	stc2l	7, cr15, [lr, #1020]	; 0x3fc
d001326c:	6b634a26 	blvs	0xd18e5b0c
d0013270:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d0013274:	4620447a 			; <UNDEFINED> instruction: 0x4620447a
d0013278:	9024f8d4 	ldrdls	pc, [r4], -r4	; <UNPREDICTABLE>
d001327c:	8028f8d4 	ldrdhi	pc, [r8], -r4	; <UNPREDICTABLE>
d0013280:	7030f894 	mlasvc	r0, r4, r8, pc	; <UNPREDICTABLE>
d0013284:	e9d49301 	ldmib	r4, {r0, r8, r9, ip, pc}^
d0013288:	f7ffab06 			; <UNDEFINED> instruction: 0xf7ffab06
d001328c:	b918fde6 	ldmdblt	r8, {r1, r2, r5, r6, r7, r8, sl, fp, ip, sp, lr, pc}
d0013290:	b0032000 	andlt	r2, r3, r0
d0013294:	8ff0e8bd 	svchi	0x00f0e8bd
d0013298:	728cf5a6 	addvc	pc, ip, #696254464	; 0x29800000
d001329c:	46204651 			; <UNDEFINED> instruction: 0x46204651
d00132a0:	41534253 	cmpmi	r3, r3, asr r2
d00132a4:	f7fd465a 			; <UNDEFINED> instruction: 0xf7fd465a
d00132a8:	2800f9c7 	stmdacs	r0, {r0, r1, r2, r6, r7, r8, fp, ip, sp, lr, pc}
d00132ac:	f5b6da11 			; <UNDEFINED> instruction: 0xf5b6da11
d00132b0:	d00b7f8c 	andle	r7, fp, ip, lsl #31
d00132b4:	447b4b15 	ldrbtmi	r4, [fp], #-2837	; 0xfffff4eb
d00132b8:	b92a6da2 	stmdblt	sl!, {r1, r5, r7, r8, sl, fp, sp, lr}
d00132bc:	3916e9c4 	ldmdbcc	r6, {r2, r6, r7, r8, fp, sp, lr, pc}
d00132c0:	e9c49b01 	stmib	r4, {r0, r8, r9, fp, ip, pc}^
d00132c4:	66a38718 	ssatvs	r8, #4, r8, lsl #14
d00132c8:	e7e22001 	strb	r2, [r2, r1]!
d00132cc:	447b4b10 	ldrbtmi	r4, [fp], #-2832	; 0xfffff4f0
d00132d0:	6028e7f2 	strdvs	lr, [r8], -r2	; <UNPREDICTABLE>
d00132d4:	f240e7f8 	vaba.s8	q15, q8, q12
d00132d8:	429e1301 	addsmi	r1, lr, #67108864	; 0x4000000
d00132dc:	69c2d1d8 	stmibvs	r2, {r3, r4, r6, r7, r8, ip, lr, pc}^
d00132e0:	f7fd6981 			; <UNDEFINED> instruction: 0xf7fd6981
d00132e4:	2800fa56 	stmdacs	r0, {r1, r2, r4, r6, r9, fp, ip, sp, lr, pc}
d00132e8:	2324dbd2 			; <UNDEFINED> instruction: 0x2324dbd2
d00132ec:	4000fb03 	andmi	pc, r0, r3, lsl #22
d00132f0:	3075f500 	rsbscc	pc, r5, r0, lsl #10
d00132f4:	33acf890 			; <UNDEFINED> instruction: 0x33acf890
d00132f8:	d0c92bff 	strdle	r2, [r9], #191	; 0xbf
d00132fc:	602b4620 	eorvs	r4, fp, r0, lsr #12
d0013300:	fd82f7ff 	stc2	7, cr15, [r2, #1020]	; 0x3fc
d0013304:	bf00e7e0 	svclt	0x0000e7e0
d0013308:	ffffffbd 			; <UNDEFINED> instruction: 0xffffffbd
d001330c:	ffffff56 			; <UNDEFINED> instruction: 0xffffff56
d0013310:	ffffff1a 			; <UNDEFINED> instruction: 0xffffff1a

Disassembly of section .text.enum_declaration:

d0013440 <.text.enum_declaration>:
d0013440:	f2404ac4 	vpmax.s8	q10, q8, q2
d0013444:	e92d111b 	push	{r0, r1, r3, r4, r8, ip}
d0013448:	447a4ff0 	ldrbtmi	r4, [sl], #-4080	; 0xfffff010
d001344c:	ed2d4604 	stc	6, cr4, [sp, #-16]!
d0013450:	b0978b02 	addslt	r8, r7, r2, lsl #22
d0013454:	fd01f7ff 	stc2	7, cr15, [r1, #-1020]	; 0xfffffc04
d0013458:	28004605 	stmdacs	r0, {r0, r2, r9, sl, lr}
d001345c:	af06d05a 	svcge	0x0006d05a
d0013460:	21002220 	tstcs	r0, r0, lsr #4
d0013464:	f00c4638 			; <UNDEFINED> instruction: 0xf00c4638
d0013468:	f8d4fa23 			; <UNDEFINED> instruction: 0xf8d4fa23
d001346c:	f240a02c 	vhadd.s8	d26, d0, d28
d0013470:	459a1301 	ldrmi	r1, [sl, #769]	; 0x301
d0013474:	f104d137 			; <UNDEFINED> instruction: 0xf104d137
d0013478:	463d0618 			; <UNDEFINED> instruction: 0x463d0618
d001347c:	c50fce0f 	strgt	ip, [pc, #-3599]	; 0xd0012675
d0013480:	000fe896 	muleq	pc, r6, r8	; <UNPREDICTABLE>
d0013484:	000fe885 	andeq	lr, pc, r5, lsl #17
d0013488:	46206a63 	strtmi	r6, [r0], -r3, ror #20
d001348c:	93026b66 	movwls	r6, #11110	; 0x2b66
d0013490:	93036aa3 	movwls	r6, #15011	; 0x3aa3
d0013494:	3030f894 	mlascc	r0, r4, r8, pc	; <UNPREDICTABLE>
d0013498:	8906e9d4 	stmdbhi	r6, {r2, r4, r6, r7, r8, fp, sp, lr, pc}
d001349c:	f7ff9301 			; <UNDEFINED> instruction: 0xf7ff9301
d00134a0:	217bfcb3 	ldrhcs	pc, [fp, #-195]!	; 0xffffff3d	; <UNPREDICTABLE>
d00134a4:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d00134a8:	f240fcca 	sha1c.32	<illegal reg q15.5>, q8, q5
d00134ac:	46051301 	strmi	r1, [r5], -r1, lsl #6
d00134b0:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d00134b4:	459a8121 	ldrmi	r8, [sl, #289]	; 0x121
d00134b8:	f504d161 			; <UNDEFINED> instruction: 0xf504d161
d00134bc:	f04f357e 			; <UNDEFINED> instruction: 0xf04f357e
d00134c0:	f5040a00 			; <UNDEFINED> instruction: 0xf5040a00
d00134c4:	f5053b7f 			; <UNDEFINED> instruction: 0xf5053b7f
d00134c8:	f8db75ca 			; <UNDEFINED> instruction: 0xf8db75ca
d00134cc:	f50b3214 			; <UNDEFINED> instruction: 0xf50b3214
d00134d0:	459a7205 	ldrmi	r7, [sl, #517]	; 0x205
d00134d4:	2b20d30f 	blcs	0xd0848118
d00134d8:	499fd131 	ldmibmi	pc, {r0, r4, r5, r8, ip, lr, pc}	; <UNPREDICTABLE>
d00134dc:	46204479 			; <UNDEFINED> instruction: 0x46204479
d00134e0:	fe62f7fc 	mcr2	7, 3, pc, cr2, cr12, {7}	; <UNPREDICTABLE>
d00134e4:	2600e015 			; <UNDEFINED> instruction: 0x2600e015
d00134e8:	46b146b2 			; <UNDEFINED> instruction: 0x46b146b2
d00134ec:	960146b0 			; <UNDEFINED> instruction: 0x960146b0
d00134f0:	96029603 	strls	r9, [r2], -r3, lsl #12
d00134f4:	f895e7d5 			; <UNDEFINED> instruction: 0xf895e7d5
d00134f8:	7a232020 	bvc	0xd08db580
d00134fc:	d11a429a 			; <UNDEFINED> instruction: 0xd11a429a
d0013500:	4642464b 	strbmi	r4, [r2], -fp, asr #12
d0013504:	0100e9d5 	ldrdeq	lr, [r0, -r5]
d0013508:	f888f7fd 			; <UNDEFINED> instruction: 0xf888f7fd
d001350c:	6da5b198 	stfvsd	f3, [r5, #608]!	; 0x260
d0013510:	2500b135 	strcs	fp, [r0, #-309]	; 0xfffffecb
d0013514:	b0174628 	andslt	r4, r7, r8, lsr #12
d0013518:	8b02ecbd 	blhi	0xd00ce814
d001351c:	8ff0e8bd 	svchi	0x00f0e8bd
d0013520:	447b4b8e 	ldrbtmi	r4, [fp], #-2958	; 0xfffff472
d0013524:	9b0265a3 	blls	0xd00acbb8
d0013528:	65e366a6 	strbvs	r6, [r3, #1702]!	; 0x6a6
d001352c:	66239b03 	strtvs	r9, [r3], -r3, lsl #22
d0013530:	66639b01 	strbtvs	r9, [r3], -r1, lsl #22
d0013534:	f10ae7ee 			; <UNDEFINED> instruction: 0xf10ae7ee
d0013538:	35240a01 	strcc	r0, [r4, #-2561]!	; 0xfffff5ff
d001353c:	1c59e7c5 	mrrcne	7, 12, lr, r9, cr5
d0013540:	0c24f04f 	stceq	0, cr15, [r4], #-316	; 0xfffffec4
d0013544:	6011960d 	andsvs	r9, r1, sp, lsl #12
d0013548:	fb0c9a02 	blx	0xd0339d5a
d001354c:	7a254303 	bvc	0xd0964160
d0013550:	f5039209 			; <UNDEFINED> instruction: 0xf5039209
d0013554:	9a033c7e 	bls	0xd00e2754
d0013558:	76caf50c 	strbvc	pc, [sl], ip, lsl #10	; <UNPREDICTABLE>
d001355c:	f240920a 	vhsub.s8	d25, d0, d10
d0013560:	920b1201 	andls	r1, fp, #268435456	; 0x10000000
d0013564:	e9cd9a01 	stmib	sp, {r0, r9, fp, ip, pc}^
d0013568:	f88d8906 			; <UNDEFINED> instruction: 0xf88d8906
d001356c:	cf0f2030 	svcgt	0x000f2030
d0013570:	e897c60f 	ldm	r7, {r0, r1, r2, r3, r9, sl, lr, pc}
d0013574:	e886000f 	stm	r6, {r0, r1, r2, r3}
d0013578:	f88c000f 			; <UNDEFINED> instruction: 0xf88c000f
d001357c:	4b7851b4 	blmi	0xd1e27c54
d0013580:	35fff04f 	ldrbcc	pc, [pc, #79]!	; 0xd00135d7	; <UNPREDICTABLE>
d0013584:	0b00f04f 	bleq	0xd004f6c8
d0013588:	462e447b 			; <UNDEFINED> instruction: 0x462e447b
d001358c:	3a10ee08 	bcc	0xd044edb4
d0013590:	93036da3 	movwls	r6, #15779	; 0x3da3
d0013594:	f0402b00 			; <UNDEFINED> instruction: 0xf0402b00
d0013598:	6ae3809e 	bvs	0xcf8f3818
d001359c:	f0002b7d 			; <UNDEFINED> instruction: 0xf0002b7d
d00135a0:	f5b3809a 			; <UNDEFINED> instruction: 0xf5b3809a
d00135a4:	f0007f80 			; <UNDEFINED> instruction: 0xf0007f80
d00135a8:	f1048096 			; <UNDEFINED> instruction: 0xf1048096
d00135ac:	af0e0c18 	svcge	0x000e0c18
d00135b0:	8030f894 	mlashi	r0, r4, r8, pc	; <UNPREDICTABLE>
d00135b4:	000fe8bc 			; <UNDEFINED> instruction: 0x000fe8bc
d00135b8:	e89cc70f 	ldm	ip, {r0, r1, r2, r3, r8, r9, sl, lr, pc}
d00135bc:	e887000f 	stm	r7, {r0, r1, r2, r3}
d00135c0:	6a63000f 	bvs	0xd18d3604
d00135c4:	2a10ee18 	bcs	0xd044ee2c
d00135c8:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d00135cc:	93014620 	movwls	r4, #5664	; 0x1620
d00135d0:	6b676aa3 	blvs	0xd19ee064
d00135d4:	e9d49302 	ldmib	r4, {r1, r8, r9, ip, pc}^
d00135d8:	f7ffa906 			; <UNDEFINED> instruction: 0xf7ffa906
d00135dc:	2800fc3e 	stmdacs	r0, {r1, r2, r3, r4, r5, sl, fp, ip, sp, lr, pc}
d00135e0:	464ad097 			; <UNDEFINED> instruction: 0x464ad097
d00135e4:	46204651 			; <UNDEFINED> instruction: 0x46204651
d00135e8:	fe66f7fc 	mcr2	7, 3, pc, cr6, cr12, {7}	; <UNPREDICTABLE>
d00135ec:	db0c2800 	blle	0xd031d5f4
d00135f0:	2b006da3 	blcs	0xd002ec84
d00135f4:	4b5bd18d 	blmi	0xd1707c30
d00135f8:	65a3447b 	strvs	r4, [r3, #1147]!	; 0x47b
d00135fc:	66a79b01 	strtvs	r9, [r7], r1, lsl #22
d0013600:	9b0265e3 	blls	0xd00acd94
d0013604:	3818e9c4 	ldmdacc	r8, {r2, r6, r7, r8, fp, sp, lr, pc}
d0013608:	464ae783 	strbmi	lr, [sl], -r3, lsl #15
d001360c:	46204651 			; <UNDEFINED> instruction: 0x46204651
d0013610:	f8bff7fd 			; <UNDEFINED> instruction: 0xf8bff7fd
d0013614:	daeb2800 	ble	0xcfadd61c
d0013618:	4620213d 			; <UNDEFINED> instruction: 0x4620213d
d001361c:	fc0ff7ff 	stc2	7, cr15, [pc], {255}	; 0xff
d0013620:	9a03b1e0 	bls	0xd00ffda8
d0013624:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d0013628:	fca2f7ff 	stc2	7, cr15, [r2], #1020	; 0x3fc
d001362c:	460e4605 	strmi	r4, [lr], -r5, lsl #12
d0013630:	4300f115 	movwmi	pc, #277	; 0x115	; <UNPREDICTABLE>
d0013634:	32fff04f 	rscscc	pc, pc, #79	; 0x4f
d0013638:	f1469304 			; <UNDEFINED> instruction: 0xf1469304
d001363c:	93050300 	movwls	r0, #21248	; 0x5300
d0013640:	e9dd2300 	ldmib	sp, {r8, r9, sp}^
d0013644:	428b0104 	addmi	r0, fp, #4, 2
d0013648:	4282bf08 	addmi	fp, r2, #8, 30
d001364c:	6da3d20a 	sfmvs	f5, 1, [r3, #40]!	; 0x28
d0013650:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0013654:	4b44af5e 	blmi	0xd113f3d4
d0013658:	e7ce447b 			; <UNDEFINED> instruction: 0xe7ce447b
d001365c:	f1463501 			; <UNDEFINED> instruction: 0xf1463501
d0013660:	e7e50600 	strb	r0, [r5, r0, lsl #12]!
d0013664:	327ef504 	rsbscc	pc, lr, #4, 10	; 0x1000000
d0013668:	3190f8d2 			; <UNDEFINED> instruction: 0x3190f8d2
d001366c:	d1062ba0 	smlatble	r6, r0, fp, r2
d0013670:	2b006da3 	blcs	0xd002ed04
d0013674:	af4df47f 	svcge	0x004df47f
d0013678:	447b4b3c 	ldrbtmi	r4, [fp], #-2876	; 0xfffff4c4
d001367c:	f88de7bd 			; <UNDEFINED> instruction: 0xf88de7bd
d0013680:	1c598050 	mrrcne	0, 5, r8, r9, cr0
d0013684:	0828f04f 	stmdaeq	r8!, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d0013688:	0e38f10d 	rndeqe	f7, #5.0
d001368c:	1190f8c2 	orrsne	pc, r0, r2, asr #17
d0013690:	0b01f10b 	bleq	0xd008fac4
d0013694:	fb089a01 	blx	0xd0239ea2
d0013698:	97154803 	ldrls	r4, [r5, -r3, lsl #16]
d001369c:	3878f508 	ldmdacc	r8!, {r3, r8, sl, ip, sp, lr, pc}^
d00136a0:	9a029211 	bls	0xd00b7eec
d00136a4:	0790f108 	ldreq	pc, [r0, r8, lsl #2]
d00136a8:	c008f894 	mulgt	r8, r4, r8
d00136ac:	e9cd9212 	stmib	sp, {r1, r4, r9, ip, pc}^
d00136b0:	e8bea90e 	ldm	lr!, {r1, r2, r3, r8, fp, sp, pc}
d00136b4:	c70f000f 	strgt	r0, [pc, -pc]
d00136b8:	000fe89e 	muleq	pc, lr, r8	; <UNPREDICTABLE>
d00136bc:	000fe887 	andeq	lr, pc, r7, lsl #17
d00136c0:	4620212c 	strtmi	r2, [r0], -ip, lsr #2
d00136c4:	50b0f8c8 	adcspl	pc, r0, r8, asr #17
d00136c8:	c0b4f888 	adcsgt	pc, r4, r8, lsl #17
d00136cc:	fbb7f7ff 	blx	0xcee116d2
d00136d0:	f47f2800 			; <UNDEFINED> instruction: 0xf47f2800
d00136d4:	f1bbaf5d 			; <UNDEFINED> instruction: 0xf1bbaf5d
d00136d8:	d1020f00 	tstle	r2, r0, lsl #30
d00136dc:	44794924 	ldrbtmi	r4, [r9], #-2340	; 0xfffff6dc
d00136e0:	4a24e6fd 	bmi	0xd094d2dc
d00136e4:	4620217d 			; <UNDEFINED> instruction: 0x4620217d
d00136e8:	b017447a 	andslt	r4, r7, sl, ror r4
d00136ec:	8b02ecbd 	blhi	0xd00ce9e8
d00136f0:	4ff0e8bd 	svcmi	0x00f0e8bd
d00136f4:	bbb1f7ff 	bllt	0xcec916f8
d00136f8:	d111459a 			; <UNDEFINED> instruction: 0xd111459a
d00136fc:	377ef504 	ldrbcc	pc, [lr, -r4, lsl #10]!	; <UNPREDICTABLE>
d0013700:	f5044682 			; <UNDEFINED> instruction: 0xf5044682
d0013704:	f5073b7f 			; <UNDEFINED> instruction: 0xf5073b7f
d0013708:	f8db77ca 			; <UNDEFINED> instruction: 0xf8db77ca
d001370c:	459a3214 	ldrmi	r3, [sl, #532]	; 0x214
d0013710:	6da3d30c 	stcvs	3, cr13, [r3, #48]!	; 0x30
d0013714:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0013718:	4b17aefc 	blmi	0xd05ff310
d001371c:	e701447b 	smlsdx	r1, fp, r4, r4
d0013720:	46204916 			; <UNDEFINED> instruction: 0x46204916
d0013724:	f7fc4479 			; <UNDEFINED> instruction: 0xf7fc4479
d0013728:	e6f3fd3f 			; <UNDEFINED> instruction: 0xe6f3fd3f
d001372c:	2020f897 	mlacs	r0, r7, r8, pc	; <UNPREDICTABLE>
d0013730:	429a7a23 	addsmi	r7, sl, #143360	; 0x23000
d0013734:	f10ad003 			; <UNDEFINED> instruction: 0xf10ad003
d0013738:	37240a01 	strcc	r0, [r4, -r1, lsl #20]!
d001373c:	464be7e5 	strbmi	lr, [fp], -r5, ror #15
d0013740:	e9d74642 	ldmib	r7, {r1, r6, r9, sl, lr}^
d0013744:	f7fc0100 			; <UNDEFINED> instruction: 0xf7fc0100
d0013748:	2800ff69 	stmdacs	r0, {r0, r3, r5, r6, r8, r9, sl, fp, ip, sp, lr, pc}
d001374c:	2501d0f3 	strcs	sp, [r1, #-243]	; 0xffffff0d
d0013750:	bf00e6e0 	svclt	0x0000e6e0
d0013754:	fffffec6 			; <UNDEFINED> instruction: 0xfffffec6
d0013758:	fffffe5c 			; <UNDEFINED> instruction: 0xfffffe5c
d001375c:	fffffdfc 			; <UNDEFINED> instruction: 0xfffffdfc
d0013760:	fffffdc3 			; <UNDEFINED> instruction: 0xfffffdc3
d0013764:	fffffd6f 			; <UNDEFINED> instruction: 0xfffffd6f
d0013768:	fffffd27 			; <UNDEFINED> instruction: 0xfffffd27
d001376c:	fffffd2f 			; <UNDEFINED> instruction: 0xfffffd2f
d0013770:	fffffce3 			; <UNDEFINED> instruction: 0xfffffce3
d0013774:	fffffd00 			; <UNDEFINED> instruction: 0xfffffd00
d0013778:	fffffd0e 			; <UNDEFINED> instruction: 0xfffffd0e
d001377c:	fffffce6 			; <UNDEFINED> instruction: 0xfffffce6

Disassembly of section .text.sizeof_operand:

d0013980 <.text.sizeof_operand>:
d0013980:	4ff0e92d 	svcmi	0x00f0e92d
d0013984:	21284604 			; <UNDEFINED> instruction: 0x21284604
d0013988:	8b02ed2d 	blhi	0xd00cee44
d001398c:	f7ffb08b 			; <UNDEFINED> instruction: 0xf7ffb08b
d0013990:	f240fa56 	vpmin.s8	<illegal reg q15.5>, q0, q3
d0013994:	90021107 	andls	r1, r2, r7, lsl #2
d0013998:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d001399c:	b128fa50 	msrlt	R8_fiq, r0
d00139a0:	4620212a 	strtmi	r2, [r0], -sl, lsr #2
d00139a4:	fa4bf7ff 	blx	0xd13119a8
d00139a8:	e0312704 	eors	r2, r1, r4, lsl #14
d00139ac:	7184f44f 	orrvc	pc, r4, pc, asr #8
d00139b0:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d00139b4:	b190fa44 	orrslt	pc, r0, r4, asr #20
d00139b8:	4620212a 	strtmi	r2, [r0], -sl, lsr #2
d00139bc:	fa3ff7ff 	blx	0xd10119c0
d00139c0:	28004607 	stmdacs	r0, {r0, r1, r2, r9, sl, lr}
d00139c4:	f8dfd1f0 			; <UNDEFINED> instruction: 0xf8dfd1f0
d00139c8:	46201484 	strtmi	r1, [r0], -r4, lsl #9
d00139cc:	f7fc4479 			; <UNDEFINED> instruction: 0xf7fc4479
d00139d0:	4638fbeb 	ldrtmi	pc, [r8], -fp, ror #23	; <UNPREDICTABLE>
d00139d4:	ecbdb00b 	ldc	0, cr11, [sp], #44	; 0x2c
d00139d8:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d00139dc:	6ae28ff0 	bvs	0xcf8b79a4
d00139e0:	131bf240 	tstne	fp, #64, 4	; <UNPREDICTABLE>
d00139e4:	d106429a 			; <UNDEFINED> instruction: 0xd106429a
d00139e8:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d00139ec:	2800fd29 	stmdacs	r0, {r0, r3, r5, r8, sl, fp, ip, sp, lr, pc}
d00139f0:	2700d1da 			; <UNDEFINED> instruction: 0x2700d1da
d00139f4:	f240e7ed 	vabd.s8	q15, q8, <illegal reg q14.5>
d00139f8:	4620110b 	strtmi	r1, [r0], -fp, lsl #2
d00139fc:	fa1ff7ff 	blx	0xd0811a00
d0013a00:	212ab348 			; <UNDEFINED> instruction: 0x212ab348
d0013a04:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0013a08:	2800fa1a 	stmdacs	r0, {r1, r3, r4, r9, fp, ip, sp, lr, pc}
d0013a0c:	2701d1cc 	strcs	sp, [r1, -ip, asr #3]
d0013a10:	4620215b 			; <UNDEFINED> instruction: 0x4620215b
d0013a14:	fa13f7ff 	blx	0xd0511a18
d0013a18:	d0602800 	rsble	r2, r0, r0, lsl #16
d0013a1c:	f5a36ae3 			; <UNDEFINED> instruction: 0xf5a36ae3
d0013a20:	2b017381 	blcs	0xd007082c
d0013a24:	81e3f200 	mvnhi	pc, r0, lsl #4
d0013a28:	2d006a25 	vstrcs	s12, [r0, #-148]	; 0xffffff6c
d0013a2c:	81dff000 	bicshi	pc, pc, r0
d0013a30:	2305fba7 	movwcs	pc, #23463	; 0x5ba7	; <UNPREDICTABLE>
d0013a34:	f0402b00 			; <UNDEFINED> instruction: 0xf0402b00
d0013a38:	462081da 			; <UNDEFINED> instruction: 0x462081da
d0013a3c:	f9e4f7ff 			; <UNDEFINED> instruction: 0xf9e4f7ff
d0013a40:	240cf8df 	strcs	pc, [ip], #-2271	; 0xfffff721
d0013a44:	4620215d 			; <UNDEFINED> instruction: 0x4620215d
d0013a48:	f7ff447a 			; <UNDEFINED> instruction: 0xf7ff447a
d0013a4c:	2800fa06 	stmdacs	r0, {r1, r2, r9, fp, ip, sp, lr, pc}
d0013a50:	436fd0cf 	cmnmi	pc, #207	; 0xcf
d0013a54:	6ae5e043 	bvs	0xcf98bb68
d0013a58:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d0013a5c:	d118429d 			; <UNDEFINED> instruction: 0xd118429d
d0013a60:	69e14afc 	stmibvs	r1!, {r2, r3, r4, r5, r6, r7, r9, fp, lr}^
d0013a64:	69a0447a 	stmibvs	r0!, {r1, r3, r4, r5, r6, sl, lr}
d0013a68:	ff04f7fc 			; <UNDEFINED> instruction: 0xff04f7fc
d0013a6c:	4620b118 			; <UNDEFINED> instruction: 0x4620b118
d0013a70:	f9caf7ff 			; <UNDEFINED> instruction: 0xf9caf7ff
d0013a74:	6ae3e7c5 	bvs	0xcf90d990
d0013a78:	d10a42ab 	smlatble	sl, fp, r2, r4
d0013a7c:	69e14af6 	stmibvs	r1!, {r1, r2, r4, r5, r6, r7, r9, fp, lr}^
d0013a80:	69a0447a 	stmibvs	r0!, {r1, r3, r4, r5, r6, sl, lr}
d0013a84:	fef6f7fc 	mrc2	7, 7, pc, cr6, cr12, {7}
d0013a88:	4620b118 			; <UNDEFINED> instruction: 0x4620b118
d0013a8c:	f9bcf7ff 			; <UNDEFINED> instruction: 0xf9bcf7ff
d0013a90:	4620e786 	strtmi	lr, [r0], -r6, lsl #15
d0013a94:	fea2f7fc 	mcr2	7, 5, pc, cr2, cr12, {7}	; <UNPREDICTABLE>
d0013a98:	2300b1c0 	movwcs	fp, #448	; 0x1c0
d0013a9c:	4620a909 	strtmi	sl, [r0], -r9, lsl #18
d0013aa0:	f7ff9309 			; <UNDEFINED> instruction: 0xf7ff9309
d0013aa4:	2800fbd7 	stmdacs	r0, {r0, r1, r2, r4, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d0013aa8:	212ad0a3 			; <UNDEFINED> instruction: 0x212ad0a3
d0013aac:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0013ab0:	2800f9c6 	stmdacs	r0, {r1, r2, r6, r7, r8, fp, ip, sp, lr, pc}
d0013ab4:	af78f47f 	svcge	0x0078f47f
d0013ab8:	f44f9b09 			; <UNDEFINED> instruction: 0xf44f9b09
d0013abc:	fb02721a 	blx	0xd00b032e
d0013ac0:	f5034303 			; <UNDEFINED> instruction: 0xf5034303
d0013ac4:	8d1f3368 	ldchi	3, cr3, [pc, #-416]	; 0xd001392c
d0013ac8:	e7a100bf 			; <UNDEFINED> instruction: 0xe7a100bf
d0013acc:	f5a36ae3 			; <UNDEFINED> instruction: 0xf5a36ae3
d0013ad0:	2b017381 	blcs	0xd00708dc
d0013ad4:	2704d811 	smladcs	r4, r1, r8, sp
d0013ad8:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0013adc:	9b02f995 	blls	0xd00d2138
d0013ae0:	f43f2b00 			; <UNDEFINED> instruction: 0xf43f2b00
d0013ae4:	4addaf76 	bmi	0xcf77f8c4
d0013ae8:	46202129 	strtmi	r2, [r0], -r9, lsr #2
d0013aec:	f7ff447a 			; <UNDEFINED> instruction: 0xf7ff447a
d0013af0:	2800f9b4 	stmdacs	r0, {r2, r4, r5, r7, r8, fp, ip, sp, lr, pc}
d0013af4:	af6df47f 	svcge	0x006df47f
d0013af8:	212ae77b 			; <UNDEFINED> instruction: 0x212ae77b
d0013afc:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0013b00:	6a63f99e 	bvs	0xd1912180
d0013b04:	46804ad6 	pkhtbmi	r4, r0, r6, asr #21
d0013b08:	f2409300 	vcgt.s8	d25, d0, d0
d0013b0c:	6b631101 	blvs	0xd18d7f18
d0013b10:	4620447a 			; <UNDEFINED> instruction: 0x4620447a
d0013b14:	a028f8d4 	ldrdge	pc, [r8], -r4	; <UNPREDICTABLE>
d0013b18:	9030f894 	mlasls	r0, r4, r8, pc	; <UNPREDICTABLE>
d0013b1c:	e9d49301 	ldmib	r4, {r0, r8, r9, ip, pc}^
d0013b20:	f7ff5606 			; <UNDEFINED> instruction: 0xf7ff5606
d0013b24:	2800f99a 	stmdacs	r0, {r1, r3, r4, r7, r8, fp, ip, sp, lr, pc}
d0013b28:	af63f43f 	svcge	0x0063f43f
d0013b2c:	46294632 			; <UNDEFINED> instruction: 0x46294632
d0013b30:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0013b34:	2800fde9 	stmdacs	r0, {r0, r3, r5, r6, r7, r8, sl, fp, ip, sp, lr, pc}
d0013b38:	8172f280 	cmnhi	r2, r0, lsl #5	; <UNPREDICTABLE>
d0013b3c:	46294632 			; <UNDEFINED> instruction: 0x46294632
d0013b40:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0013b44:	2800fe01 	stmdacs	r0, {r0, r9, sl, fp, ip, sp, lr, pc}
d0013b48:	6da7da0d 			; <UNDEFINED> instruction: 0x6da7da0d
d0013b4c:	f47f2f00 			; <UNDEFINED> instruction: 0xf47f2f00
d0013b50:	4bc4af50 	blmi	0xcf13f898
d0013b54:	65a3447b 	strvs	r4, [r3, #1147]!	; 0x47b
d0013b58:	65e39b00 	strbvs	r9, [r3, #2816]!	; 0xb00
d0013b5c:	e9c49b01 	stmib	r4, {r0, r8, r9, fp, ip, pc}^
d0013b60:	66a3a918 	ssatvs	sl, #4, r8, lsl #18
d0013b64:	233ce735 	teqcs	ip, #13893632	; 0xd40000
d0013b68:	4000fb03 	andmi	pc, r0, r3, lsl #22
d0013b6c:	305ff500 	subscc	pc, pc, r0, lsl #10
d0013b70:	23ecf890 	mvncs	pc, #144, 16	; 0x900000
d0013b74:	53eef890 	mvnpl	pc, #144, 16	; 0x900000
d0013b78:	13fcf8d0 	mvnsne	pc, #208, 16	; 0xd00000
d0013b7c:	030df1a2 	movweq	pc, #53666	; 0xd1a2	; <UNPREDICTABLE>
d0013b80:	d9302b04 	ldmdble	r0!, {r2, r8, r9, fp, sp}
d0013b84:	26001fd3 			; <UNDEFINED> instruction: 0x26001fd3
d0013b88:	d92e2b02 	stmdble	lr!, {r1, r8, r9, fp, sp}
d0013b8c:	d02e2a10 	eorle	r2, lr, r0, lsl sl
d0013b90:	0c11f1a2 	ldfeqd	f7, [r1], {162}	; 0xa2
d0013b94:	0300f1dc 	movweq	pc, #476	; 0x1dc	; <UNPREDICTABLE>
d0013b98:	030ceb43 	movweq	lr, #52035	; 0xcb43
d0013b9c:	f0002a0a 			; <UNDEFINED> instruction: 0xf0002a0a
d0013ba0:	2a13814b 	bcs	0xd04f40d4
d0013ba4:	48a8dc03 	stmiami	r8!, {r0, r1, sl, fp, ip, lr, pc}
d0013ba8:	07c740d0 			; <UNDEFINED> instruction: 0x07c740d0
d0013bac:	1f90d421 	svcne	0x0090d421
d0013bb0:	0b00f1d0 	bleq	0xd00502f8
d0013bb4:	0b00eb4b 	bleq	0xd004e8e8
d0013bb8:	d01d2a07 	andsle	r2, sp, r7, lsl #20
d0013bbc:	d01b2a05 	andsle	r2, fp, r5, lsl #20
d0013bc0:	f1bbb346 			; <UNDEFINED> instruction: 0xf1bbb346
d0013bc4:	f0400f00 			; <UNDEFINED> instruction: 0xf0400f00
d0013bc8:	f44f8122 	vst4.8	{d24,d26,d28,d30}, [pc :128], r2
d0013bcc:	fb02721a 	blx	0xd00b043e
d0013bd0:	f5024205 			; <UNDEFINED> instruction: 0xf5024205
d0013bd4:	8d173268 	lfmhi	f3, 4, [r7, #-416]	; 0xfffffe60
d0013bd8:	0f00f1b8 	svceq	0x0000f1b8
d0013bdc:	00bfd113 	adcseq	sp, pc, r3, lsl r1	; <UNPREDICTABLE>
d0013be0:	434fb363 	movtmi	fp, #62307	; 0xf363
d0013be4:	2601e02a 	strcs	lr, [r1], -sl, lsr #32
d0013be8:	2301e7d0 	movwcs	lr, #6096	; 0x17d0
d0013bec:	2301e7d9 	movwcs	lr, #6105	; 0x17d9
d0013bf0:	f04fe7d9 			; <UNDEFINED> instruction: 0xf04fe7d9
d0013bf4:	e7e10b01 	strb	r0, [r1, r1, lsl #22]!
d0013bf8:	f1b82701 			; <UNDEFINED> instruction: 0xf1b82701
d0013bfc:	d0ef0f00 	rscle	r0, pc, r0, lsl #30
d0013c00:	0f00f1bb 	svceq	0x0000f1bb
d0013c04:	6da7d108 	stfvsd	f5, [r7, #32]!
d0013c08:	f47f2f00 			; <UNDEFINED> instruction: 0xf47f2f00
d0013c0c:	4b96aef2 	blmi	0xce5bf7dc
d0013c10:	e7a0447b 			; <UNDEFINED> instruction: 0xe7a0447b
d0013c14:	e7f02704 	ldrb	r2, [r0, r4, lsl #14]!
d0013c18:	f0402a0e 			; <UNDEFINED> instruction: 0xf0402a0e
d0013c1c:	f44f8112 	vst4.8	{d24,d26,d28,d30}, [pc :64], r2
d0013c20:	fb03731a 	blx	0xd00f0892
d0013c24:	f5034305 			; <UNDEFINED> instruction: 0xf5034305
d0013c28:	8d1f3368 	ldchi	3, cr3, [pc, #-416]	; 0xd0013a90
d0013c2c:	f1a200bf 			; <UNDEFINED> instruction: 0xf1a200bf
d0013c30:	f04f030e 			; <UNDEFINED> instruction: 0xf04f030e
d0013c34:	425e0b00 	subsmi	r0, lr, #0, 22
d0013c38:	465b415e 			; <UNDEFINED> instruction: 0x465b415e
d0013c3c:	4620215b 			; <UNDEFINED> instruction: 0x4620215b
d0013c40:	f7ff9303 			; <UNDEFINED> instruction: 0xf7ff9303
d0013c44:	b378f8fc 	cmnlt	r8, #252, 16	; 0xfc0000	; <UNPREDICTABLE>
d0013c48:	ea539b03 	b	0xd14fa85c
d0013c4c:	d115030b 	tstle	r5, fp, lsl #6
d0013c50:	2f006da7 	svccs	0x00006da7
d0013c54:	aecdf47f 	mcrge	4, 6, pc, cr13, cr15, {3}	; <UNPREDICTABLE>
d0013c58:	447b4b84 	ldrbtmi	r4, [fp], #-2948	; 0xfffff47c
d0013c5c:	2b5be77b 	blcs	0xd170da50
d0013c60:	3701d107 	strcc	sp, [r1, -r7, lsl #2]
d0013c64:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0013c68:	b947f8cf 	stmdblt	r7, {r0, r1, r2, r3, r6, r7, fp, ip, sp, lr, pc}^
d0013c6c:	2704b9a6 	strcs	fp, [r4, -r6, lsr #19]
d0013c70:	2b5de01a 	blcs	0xd178bce0
d0013c74:	f107bf08 			; <UNDEFINED> instruction: 0xf107bf08
d0013c78:	e7f337ff 	udf	#13183	; 0x337f
d0013c7c:	6ae32701 	bvs	0xcf8dd888
d0013c80:	7f80f5b3 	svcvc	0x0080f5b3
d0013c84:	6da2d002 	stcvs	0, cr13, [r2, #8]!
d0013c88:	d0e82a00 	rscle	r2, r8, r0, lsl #20
d0013c8c:	46204978 			; <UNDEFINED> instruction: 0x46204978
d0013c90:	f7fc4479 			; <UNDEFINED> instruction: 0xf7fc4479
d0013c94:	e6acfa89 	strt	pc, [ip], r9, lsl #21
d0013c98:	731af44f 	tstvc	sl, #1325400064	; 0x4f000000	; <UNPREDICTABLE>
d0013c9c:	4305fb03 	movwmi	pc, #23299	; 0x5b03	; <UNPREDICTABLE>
d0013ca0:	3368f503 	msrcc	SPSR_f, #12582912	; 0xc00000
d0013ca4:	00bf8d1f 	adcseq	r8, pc, pc, lsl sp	; <UNPREDICTABLE>
d0013ca8:	447b4b72 	ldrbtmi	r4, [fp], #-2930	; 0xfffff48e
d0013cac:	3a90ee08 	bcc	0xce44f4d4
d0013cb0:	2b2e6ae3 	blcs	0xd0bae844
d0013cb4:	f5b3d014 			; <UNDEFINED> instruction: 0xf5b3d014
d0013cb8:	f47f7f91 			; <UNDEFINED> instruction: 0xf47f7f91
d0013cbc:	f1bbaf10 			; <UNDEFINED> instruction: 0xf1bbaf10
d0013cc0:	d1170f00 	tstle	r7, r0, lsl #30
d0013cc4:	2b006da3 	blcs	0xd002f358
d0013cc8:	ae93f47f 	mrcge	4, 4, APSR_nzcv, cr3, cr15, {3}
d0013ccc:	447b4b6a 	ldrbtmi	r4, [fp], #-2922	; 0xfffff496
d0013cd0:	9b0065a3 	blls	0xd002d364
d0013cd4:	9b0165e3 	blls	0xd006d468
d0013cd8:	a918e9c4 	ldmdbge	r8, {r2, r6, r7, r8, fp, sp, lr, pc}
d0013cdc:	e68866a3 	str	r6, [r8], r3, lsr #13
d0013ce0:	0f00f1bb 	svceq	0x0000f1bb
d0013ce4:	6da7d006 	stcvs	0, cr13, [r7, #24]!
d0013ce8:	f47f2f00 			; <UNDEFINED> instruction: 0xf47f2f00
d0013cec:	4b63ae82 	blmi	0xd18ff6fc
d0013cf0:	e730447b 			; <UNDEFINED> instruction: 0xe730447b
d0013cf4:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0013cf8:	b936f887 	ldmdblt	r6!, {r0, r1, r2, r7, fp, ip, sp, lr, pc}
d0013cfc:	2b006da3 	blcs	0xd002f390
d0013d00:	ae77f47f 	mrcge	4, 3, APSR_nzcv, cr7, cr15, {3}
d0013d04:	447b4b5e 	ldrbtmi	r4, [fp], #-2910	; 0xfffff4a2
d0013d08:	69a3e7e2 	stmibvs	r3!, {r1, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d0013d0c:	2a90ee18 	bcs	0xce44f574
d0013d10:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d0013d14:	ee084620 	cfmadd32	mvax1, mvfx4, mvfx8, mvfx0
d0013d18:	69e33a10 	stmibvs	r3!, {r4, r9, fp, ip, sp}^
d0013d1c:	6a639307 	bvs	0xd18f8940
d0013d20:	6aa39303 	bvs	0xce8f8934
d0013d24:	f8949306 			; <UNDEFINED> instruction: 0xf8949306
d0013d28:	93053030 	movwls	r3, #20528	; 0x5030
d0013d2c:	93046b63 	movwls	r6, #19299	; 0x4b63
d0013d30:	f893f7ff 			; <UNDEFINED> instruction: 0xf893f7ff
d0013d34:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0013d38:	f44fae5c 			; <UNDEFINED> instruction: 0xf44fae5c
d0013d3c:	2700731a 	smladcs	r0, sl, r3, r7
d0013d40:	fb05fb03 	blx	0xd0192956
d0013d44:	f50b9b07 			; <UNDEFINED> instruction: 0xf50b9b07
d0013d48:	44a33867 	strtmi	r3, [r3], #2151	; 0x867
d0013d4c:	78f4f508 	ldmvc	r4!, {r3, r8, sl, ip, sp, lr, pc}^
d0013d50:	3b68f50b 	blcc	0xd1a51184
d0013d54:	f89b44a0 			; <UNDEFINED> instruction: 0xf89b44a0
d0013d58:	42ba202a 	adcsmi	r2, sl, #42	; 0x2a
d0013d5c:	f44fd818 	vst2.8	{d29-d30}, [pc :64], r8
d0013d60:	435d731a 	cmpmi	sp, #1744830464	; 0x68000000
d0013d64:	f5031963 			; <UNDEFINED> instruction: 0xf5031963
d0013d68:	f8933368 			; <UNDEFINED> instruction: 0xf8933368
d0013d6c:	42bb302a 	adcsmi	r3, fp, #42	; 0x2a
d0013d70:	6da7d11c 	stfvsd	f5, [r7, #112]!	; 0x70
d0013d74:	f47f2f00 			; <UNDEFINED> instruction: 0xf47f2f00
d0013d78:	4b42ae3c 	blmi	0xd10bf670
d0013d7c:	65a3447b 	strvs	r4, [r3, #1147]!	; 0x47b
d0013d80:	65e39b03 	strbvs	r9, [r3, #2819]!	; 0xb03
d0013d84:	66239b06 	strtvs	r9, [r3], -r6, lsl #22
d0013d88:	66639b05 	strbtvs	r9, [r3], -r5, lsl #22
d0013d8c:	e6e89b04 	strbt	r9, [r8], r4, lsl #22
d0013d90:	1004f8d8 	ldrdne	pc, [r4], -r8
d0013d94:	2a10ee18 	bcs	0xd044f5fc
d0013d98:	0b24f858 	bleq	0xd0951f00
d0013d9c:	f7fc9307 			; <UNDEFINED> instruction: 0xf7fc9307
d0013da0:	9b07fc3d 	blls	0xd0212e9c
d0013da4:	d1da2800 	bicsle	r2, sl, r0, lsl #16
d0013da8:	e7d43701 	ldrb	r3, [r4, r1, lsl #14]
d0013dac:	fb032324 	blx	0xd00dca46
d0013db0:	44275707 	strtmi	r5, [r7], #-1799	; 0xfffff8f9
d0013db4:	3767f507 	strbcc	pc, [r7, -r7, lsl #10]!	; <UNPREDICTABLE>
d0013db8:	5208f897 	andpl	pc, r8, #9895936	; 0x970000
d0013dbc:	b209f897 	andlt	pc, r9, #9895936	; 0x970000
d0013dc0:	03fff1b5 	mvnseq	pc, #1073741869	; 0x4000002d
d0013dc4:	2301bf18 	movwcs	fp, #7960	; 0x1f18
d0013dc8:	0f00f1bb 	svceq	0x0000f1bb
d0013dcc:	2dffd10d 	ldfcsp	f5, [pc, #52]!	; 0xd0013e08
d0013dd0:	f44fd00a 	vst4.8	{d29-d32}, [pc], sl
d0013dd4:	fb03731a 	blx	0xd00f0a46
d0013dd8:	f5034305 			; <UNDEFINED> instruction: 0xf5034305
d0013ddc:	8d1f3368 	ldchi	3, cr3, [pc, #-416]	; 0xd0013c44
d0013de0:	00bf4633 	adcseq	r4, pc, r3, lsr r6	; <UNPREDICTABLE>
d0013de4:	e763461e 			; <UNDEFINED> instruction: 0xe763461e
d0013de8:	2704465b 	smlsdcs	r4, fp, r6, r4
d0013dec:	6da7e7fa 	stcvs	7, cr14, [r7, #1000]!	; 0x3e8
d0013df0:	f47f2f00 			; <UNDEFINED> instruction: 0xf47f2f00
d0013df4:	4d24adfe 	stcmi	13, cr10, [r4, #-1016]!	; 0xfffffc08
d0013df8:	6aa16a60 	bvs	0xce86e780
d0013dfc:	f894447d 			; <UNDEFINED> instruction: 0xf894447d
d0013e00:	6b632030 	blvs	0xd18dbec8
d0013e04:	5016e9c4 	andspl	lr, r6, r4, asr #19
d0013e08:	1218e9c4 	andsne	lr, r8, #196, 18	; 0x310000
d0013e0c:	f1b8e6a9 			; <UNDEFINED> instruction: 0xf1b8e6a9
d0013e10:	f47f0f00 			; <UNDEFINED> instruction: 0xf47f0f00
d0013e14:	2601af01 	strcs	sl, [r1], -r1, lsl #30
d0013e18:	f04f2704 			; <UNDEFINED> instruction: 0xf04f2704
d0013e1c:	e6df0b01 	ldrb	r0, [pc], r1, lsl #22
d0013e20:	fb032330 	blx	0xd00dcaea
d0013e24:	f5004000 			; <UNDEFINED> instruction: 0xf5004000
d0013e28:	f89010a4 			; <UNDEFINED> instruction: 0xf89010a4
d0013e2c:	f8902655 			; <UNDEFINED> instruction: 0xf8902655
d0013e30:	f8b05656 			; <UNDEFINED> instruction: 0xf8b05656
d0013e34:	e6a1165e 	ssat	r1, #2, lr, asr #12
d0013e38:	d1e82e00 	mvnle	r2, r0, lsl #28
d0013e3c:	0f00f1b8 	svceq	0x0000f1b8
d0013e40:	2704d0ea 	strcs	sp, [r4, -sl, ror #1]
d0013e44:	bf00e6f3 	svclt	0x0000e6f3
d0013e48:	000c5014 	andeq	r5, ip, r4, lsl r0
d0013e4c:	fffffdb0 			; <UNDEFINED> instruction: 0xfffffdb0
d0013e50:	fffffed3 			; <UNDEFINED> instruction: 0xfffffed3
d0013e54:	fffffd3e 			; <UNDEFINED> instruction: 0xfffffd3e
d0013e58:	fffffd2a 			; <UNDEFINED> instruction: 0xfffffd2a
d0013e5c:	fffffe51 			; <UNDEFINED> instruction: 0xfffffe51
d0013e60:	fffffca2 			; <UNDEFINED> instruction: 0xfffffca2
d0013e64:	fffffc87 			; <UNDEFINED> instruction: 0xfffffc87
d0013e68:	fffffbf8 			; <UNDEFINED> instruction: 0xfffffbf8
d0013e6c:	fffffbc7 			; <UNDEFINED> instruction: 0xfffffbc7
d0013e70:	fffffccf 			; <UNDEFINED> instruction: 0xfffffccf
d0013e74:	fffffc07 			; <UNDEFINED> instruction: 0xfffffc07
d0013e78:	fffffb7d 			; <UNDEFINED> instruction: 0xfffffb7d
d0013e7c:	fffffb7c 			; <UNDEFINED> instruction: 0xfffffb7c
d0013e80:	fffffb85 			; <UNDEFINED> instruction: 0xfffffb85
d0013e84:	fffffb54 			; <UNDEFINED> instruction: 0xfffffb54
d0013e88:	fffffaed 			; <UNDEFINED> instruction: 0xfffffaed

Disassembly of section .text.initialize_static_buffer.constprop.0:

d0013ec0 <.text.initialize_static_buffer.constprop.0>:
d0013ec0:	480f4602 	stmdami	pc, {r1, r9, sl, lr}	; <UNPREDICTABLE>
d0013ec4:	f5004478 			; <UNDEFINED> instruction: 0xf5004478
d0013ec8:	f503139f 			; <UNDEFINED> instruction: 0xf503139f
d0013ecc:	681b53f1 	ldmdavs	fp, {r0, r4, r5, r6, r7, r8, r9, ip, lr}
d0013ed0:	2180f5c3 	orrcs	pc, r0, r3, asr #11
d0013ed4:	b5104291 	ldrlt	r4, [r0, #-657]	; 0xfffffd6f
d0013ed8:	490ad206 	stmdbmi	sl, {r1, r2, r9, ip, lr, pc}
d0013edc:	44792400 	ldrbtmi	r2, [r9], #-1024	; 0xfffffc00
d0013ee0:	f962f7fc 			; <UNDEFINED> instruction: 0xf962f7fc
d0013ee4:	bd104620 	ldclt	6, cr4, [r0, #-128]	; 0xffffff80
d0013ee8:	347ff500 	ldrbtcc	pc, [pc], #-1280	; 0xd0013ef0	; <UNPREDICTABLE>
d0013eec:	21000092 	swpcs	r0, r2, [r0]	; <UNPREDICTABLE>
d0013ef0:	7408f504 	strvc	pc, [r8], #-1284	; 0xfffffafc
d0013ef4:	0483eb04 	streq	lr, [r3], #2820	; 0xb04
d0013ef8:	f00b4620 			; <UNDEFINED> instruction: 0xf00b4620
d0013efc:	e7f1fcd9 	ubfx	pc, r9, #25, #18
d0013f00:	00012540 	andeq	r2, r1, r0, asr #10
d0013f04:	ffffffaa 			; <UNDEFINED> instruction: 0xffffffaa

Disassembly of section .text.initialize_large_zero.constprop.0:

d0013f30 <.text.initialize_large_zero.constprop.0>:
d0013f30:	4c16b513 	cfldr32mi	mvfx11, [r6], {19}
d0013f34:	4a16217b 	bmi	0xd059c528
d0013f38:	447a447c 	ldrbtmi	r4, [sl], #-1148	; 0xfffffb84
d0013f3c:	92014620 	andls	r4, r1, #32, 12	; 0x2000000
d0013f40:	ff8bf7fe 			; <UNDEFINED> instruction: 0xff8bf7fe
d0013f44:	6ae3b300 	bvs	0xcf900b4c
d0013f48:	7381f5a3 	orrvc	pc, r1, #683671552	; 0x28c00000
d0013f4c:	d8022b01 	stmdale	r2, {r0, r8, r9, fp, sp}
d0013f50:	9a016a23 	bls	0xd006e7e4
d0013f54:	490fb143 	stmdbmi	pc, {r0, r1, r6, r8, ip, sp, pc}	; <UNPREDICTABLE>
d0013f58:	4479480f 	ldrbtmi	r4, [r9], #-2063	; 0xfffff7f1
d0013f5c:	b0024478 	andlt	r4, r2, r8, ror r4
d0013f60:	4010e8bd 			; <UNDEFINED> instruction: 0x4010e8bd
d0013f64:	b920f7fc 	stmdblt	r0!, {r2, r3, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}
d0013f68:	92014620 	andls	r4, r1, #32, 12	; 0x2000000
d0013f6c:	ff4cf7fe 			; <UNDEFINED> instruction: 0xff4cf7fe
d0013f70:	4620212c 	strtmi	r2, [r0], -ip, lsr #2
d0013f74:	ff63f7fe 			; <UNDEFINED> instruction: 0xff63f7fe
d0013f78:	217d9a01 	cmncs	sp, r1, lsl #20
d0013f7c:	b0024620 	andlt	r4, r2, r0, lsr #12
d0013f80:	4010e8bd 			; <UNDEFINED> instruction: 0x4010e8bd
d0013f84:	bf69f7fe 	svclt	0x0069f7fe
d0013f88:	bd10b002 	ldclt	0, cr11, [r0, #-8]
d0013f8c:	000124cc 	andeq	r2, r1, ip, asr #9
d0013f90:	ffffffca 			; <UNDEFINED> instruction: 0xffffffca
d0013f94:	ffffffaa 			; <UNDEFINED> instruction: 0xffffffaa
d0013f98:	000124a8 	andeq	r2, r1, r8, lsr #9

Disassembly of section .text.add_local.constprop.0:

d0013fd8 <.text.add_local.constprop.0>:
d0013fd8:	e92db084 	push	{r2, r7, ip, sp, pc}
d0013fdc:	4d3547f0 	ldcmi	7, cr4, [r5, #-960]!	; 0xfffffc40
d0013fe0:	447dac08 	ldrbtmi	sl, [sp], #-3080	; 0xfffff3f8
d0013fe4:	000fe884 	andeq	lr, pc, r4, lsl #17
d0013fe8:	9a094601 	bls	0xd02657f4
d0013fec:	f8dd4628 			; <UNDEFINED> instruction: 0xf8dd4628
d0013ff0:	f8dda02c 			; <UNDEFINED> instruction: 0xf8dda02c
d0013ff4:	f89d9030 			; <UNDEFINED> instruction: 0xf89d9030
d0013ff8:	9f0f8038 	svcls	0x000f8038
d0013ffc:	fb84f7fc 	blx	0xce151ff6
d0014000:	db192800 	blle	0xd065e008
d0014004:	fb032330 	blx	0xd00dccce
d0014008:	4b275000 	blmi	0xd09e8010
d001400c:	10a4f500 	adcne	pc, r4, r0, lsl #10
d0014010:	f89058eb 			; <UNDEFINED> instruction: 0xf89058eb
d0014014:	429a2654 	addsmi	r2, sl, #84, 12	; 0x5400000
d0014018:	6dacd10e 	stfvsd	f5, [ip, #56]!	; 0x38
d001401c:	d1412c00 	cmple	r1, r0, lsl #24
d0014020:	66af4b25 	strtvs	r4, [pc], r5, lsr #22
d0014024:	e9c5447b 	stmib	r5, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0014028:	e9c59818 	stmib	r5, {r3, r4, fp, ip, pc}^
d001402c:	46203a16 			; <UNDEFINED> instruction: 0x46203a16
d0014030:	47f0e8bd 			; <UNDEFINED> instruction: 0x47f0e8bd
d0014034:	4770b004 	ldrbmi	fp, [r0, -r4]!
d0014038:	4b1c4e20 	blmi	0xd07278c0
d001403c:	58f4447e 	ldmpl	r4!, {r1, r2, r3, r4, r5, r6, sl, lr}^
d0014040:	d1092c40 	tstle	r9, r0, asr #24
d0014044:	bb6c6db4 	bllt	0xd1b2f71c
d0014048:	66b74b1d 	ssatvs	r4, #24, sp, lsl #22
d001404c:	e9c6447b 	stmib	r6, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0014050:	e9c69818 	stmib	r6, {r3, r4, fp, ip, pc}^
d0014054:	e7ea3a16 			; <UNDEFINED> instruction: 0xe7ea3a16
d0014058:	f1042230 			; <UNDEFINED> instruction: 0xf1042230
d001405c:	af080901 	svcge	0x00080901
d0014060:	fb022100 	blx	0xd009c46a
d0014064:	f8466804 			; <UNDEFINED> instruction: 0xf8466804
d0014068:	f5089003 			; <UNDEFINED> instruction: 0xf5089003
d001406c:	4b0e18a4 	blmi	0xd039a304
d0014070:	6534f208 	ldrvs	pc, [r4, #-520]!	; 0xfffffdf8
d0014074:	a003f816 	andge	pc, r3, r6, lsl r8	; <UNPREDICTABLE>
d0014078:	f00b4628 			; <UNDEFINED> instruction: 0xf00b4628
d001407c:	f888fc19 			; <UNDEFINED> instruction: 0xf888fc19
d0014080:	cf0fa654 	svcgt	0x000fa654
d0014084:	e897c50f 	ldm	r7, {r0, r1, r2, r3, r8, sl, lr, pc}
d0014088:	e885000f 	stm	r5, {r0, r1, r2, r3}
d001408c:	f89d000f 			; <UNDEFINED> instruction: 0xf89d000f
d0014090:	f8883040 			; <UNDEFINED> instruction: 0xf8883040
d0014094:	4b063655 	blmi	0xd01a19f0
d0014098:	459158f2 	ldrmi	r5, [r1, #2290]	; 0x8f2
d001409c:	f846d9c7 			; <UNDEFINED> instruction: 0xf846d9c7
d00140a0:	e7c49003 	strb	r9, [r4, r3]
d00140a4:	e7c22400 	strb	r2, [r2, r0, lsl #8]
d00140a8:	0014923c 	andseq	r9, r4, ip, lsr r2
d00140ac:	00149234 	andseq	r9, r4, r4, lsr r2
d00140b0:	00149238 	andseq	r9, r4, r8, lsr r2
d00140b4:	00012422 	andeq	r2, r1, r2, lsr #8
d00140b8:	ffffff74 			; <UNDEFINED> instruction: 0xffffff74
d00140bc:	000123c8 	andeq	r2, r1, r8, asr #7
d00140c0:	ffffff68 			; <UNDEFINED> instruction: 0xffffff68

Disassembly of section .text.record_definition.constprop.0:

d0014338 <.text.record_definition.constprop.0>:
d0014338:	e92db084 	push	{r2, r7, ip, sp, pc}
d001433c:	f5ad4ff0 			; <UNDEFINED> instruction: 0xf5ad4ff0
d0014340:	f8df7d33 			; <UNDEFINED> instruction: 0xf8df7d33
d0014344:	46065508 	strmi	r5, [r6], -r8, lsl #10
d0014348:	447dacbc 	ldrbtmi	sl, [sp], #-3260	; 0xfffff344
d001434c:	a310f8dd 	tstge	r0, #14483456	; 0xdd0000	; <UNPREDICTABLE>
d0014350:	000fe884 	andeq	lr, pc, r4, lsl #17
d0014354:	217b9bbf 	ldrhcs	r9, [fp, #-191]!	; 0xffffff41
d0014358:	24f4f8df 	ldrbtcs	pc, [r4], #2271	; 0x8df	; <UNPREDICTABLE>
d001435c:	93004628 	movwls	r4, #1576	; 0x628
d0014360:	447a9bc0 	ldrbtmi	r9, [sl], #-3008	; 0xfffff440
d0014364:	93019fbd 	movwls	r9, #8125	; 0x1fbd
d0014368:	3308f89d 	movwcc	pc, #34973	; 0x889d	; <UNPREDICTABLE>
d001436c:	9bc39302 	blls	0xcf0f8f7c
d0014370:	f7fe9303 			; <UNDEFINED> instruction: 0xf7fe9303
d0014374:	b910fd72 	ldmdblt	r0, {r1, r4, r5, r6, r8, sl, fp, ip, sp, lr, pc}
d0014378:	34fff04f 	ldrbtcc	pc, [pc], #79	; 0xd0014380	; <UNPREDICTABLE>
d001437c:	9bc5e232 	blls	0xcf18cc4c
d0014380:	f0402b00 			; <UNDEFINED> instruction: 0xf0402b00
d0014384:	465380a4 	ldrbmi	r8, [r3], -r4, lsr #1
d0014388:	4631463a 			; <UNDEFINED> instruction: 0x4631463a
d001438c:	f7fc4628 			; <UNDEFINED> instruction: 0xf7fc4628
d0014390:	f08af953 			; <UNDEFINED> instruction: 0xf08af953
d0014394:	46040301 	strmi	r0, [r4], -r1, lsl #6
d0014398:	4631463a 			; <UNDEFINED> instruction: 0x4631463a
d001439c:	f7fc4628 			; <UNDEFINED> instruction: 0xf7fc4628
d00143a0:	2800f94b 	stmdacs	r0, {r0, r1, r3, r6, r8, fp, ip, sp, lr, pc}
d00143a4:	824cf2c0 	subhi	pc, ip, #192, 4
d00143a8:	2b006dab 	blcs	0xd002fa5c
d00143ac:	f8dfd1e4 			; <UNDEFINED> instruction: 0xf8dfd1e4
d00143b0:	447b34a4 	ldrbtmi	r3, [fp], #-1188	; 0xfffffb5c
d00143b4:	9b0065ab 	blls	0xd002da68
d00143b8:	9b0165eb 	blls	0xd006db6c
d00143bc:	9b02662b 	blls	0xd00adc70
d00143c0:	9b03666b 	blls	0xd00edd74
d00143c4:	e7d766ab 	ldrb	r6, [r7, fp, lsr #13]
d00143c8:	3275f505 	rsbscc	pc, r5, #20971520	; 0x1400000
d00143cc:	3388f8d2 	orrcc	pc, r8, #13762560	; 0xd20000
d00143d0:	d1062b18 	tstle	r6, r8, lsl fp
d00143d4:	2b006dab 	blcs	0xd002fa88
d00143d8:	f8dfd1ce 			; <UNDEFINED> instruction: 0xf8dfd1ce
d00143dc:	447b347c 	ldrbtmi	r3, [fp], #-1148	; 0xfffffb84
d00143e0:	1c59e7e8 	mrrcne	7, 14, lr, r9, cr8
d00143e4:	469b7a2e 	ldrmi	r7, [fp], lr, lsr #20
d00143e8:	1388f8c2 	orrne	pc, r8, #12713984	; 0xc20000
d00143ec:	721af44f 	andsvc	pc, sl, #1325400064	; 0x4f000000
d00143f0:	fb0299c5 	blx	0xd00bab0e
d00143f4:	f5055503 			; <UNDEFINED> instruction: 0xf5055503
d00143f8:	f5053767 			; <UNDEFINED> instruction: 0xf5053767
d00143fc:	f5073568 			; <UNDEFINED> instruction: 0xf5073568
d0014400:	463877e4 	ldrtmi	r7, [r8], -r4, ror #15
d0014404:	fa54f00b 	blx	0xd1550438
d0014408:	7c3cf50d 	cfldr32vc	mvfx15, [ip], #-52	; 0xffffffcc
d001440c:	a02bf885 	eorge	pc, fp, r5, lsl #17
d0014410:	602ef885 	eorvs	pc, lr, r5, lsl #17
d0014414:	000fe8bc 			; <UNDEFINED> instruction: 0x000fe8bc
d0014418:	e89cc70f 	ldm	ip, {r0, r1, r2, r3, r8, r9, sl, lr, pc}
d001441c:	e887000f 	stm	r7, {r0, r1, r2, r3}
d0014420:	ad18000f 	ldcge	0, cr0, [r8, #-60]	; 0xffffffc4
d0014424:	721af44f 	andsvc	pc, sl, #1325400064	; 0x4f000000
d0014428:	46282100 	strtmi	r2, [r8], -r0, lsl #2
d001442c:	f00b462e 			; <UNDEFINED> instruction: 0xf00b462e
d0014430:	9bc5fa3f 	blls	0xcf192d34
d0014434:	d04e2b00 	suble	r2, lr, r0, lsl #22
d0014438:	f10dafc6 			; <UNDEFINED> instruction: 0xf10dafc6
d001443c:	cf0f093c 	svcgt	0x000f093c
d0014440:	e897c60f 	ldm	r7, {r0, r1, r2, r3, r9, sl, lr, pc}
d0014444:	e886000f 	stm	r6, {r0, r1, r2, r3}
d0014448:	9bc5000f 	blls	0xcf15448c
d001444c:	640cf8df 	strvs	pc, [ip], #-2271	; 0xfffff721
d0014450:	3264f885 	rsbcc	pc, r4, #8716288	; 0x850000
d0014454:	447e2301 	ldrbtmi	r2, [lr], #-769	; 0xfffffcff
d0014458:	a263f885 	rsbge	pc, r3, #8716288	; 0x850000
d001445c:	3265f885 	rsbcc	pc, r5, #8716288	; 0x850000
d0014460:	f8857a33 			; <UNDEFINED> instruction: 0xf8857a33
d0014464:	6db33266 	lfmvs	f3, 4, [r3, #408]!	; 0x198
d0014468:	6af3b92b 	bvs	0xcfd0291c
d001446c:	d0022b7d 	andle	r2, r2, sp, ror fp
d0014470:	7f80f5b3 	svcvc	0x0080f5b3
d0014474:	4dfad131 	ldfmip	f5, [sl, #196]!	; 0xc4
d0014478:	4afa217d 	bmi	0xcfe9ca74
d001447c:	447a447d 	ldrbtmi	r4, [sl], #-1149	; 0xfffffb83
d0014480:	f7fe4628 			; <UNDEFINED> instruction: 0xf7fe4628
d0014484:	2800fcea 	stmdacs	r0, {r1, r3, r5, r6, r7, sl, fp, ip, sp, lr, pc}
d0014488:	af76f43f 	svcge	0x0076f43f
d001448c:	af189bc5 	svcge	0x00189bc5
d0014490:	3518b13b 	ldrcc	fp, [r8, #-315]	; 0xfffffec5
d0014494:	cd0f463e 	stcgt	6, cr4, [pc, #-248]	; 0xd00143a4
d0014498:	e895c60f 	ldm	r5, {r0, r1, r2, r3, r9, sl, lr, pc}
d001449c:	e886000f 	stm	r6, {r0, r1, r2, r3}
d00144a0:	f897000f 			; <UNDEFINED> instruction: 0xf897000f
d00144a4:	2b003262 	blcs	0xd0020e34
d00144a8:	813cf040 	teqhi	ip, r0, asr #32	; <UNPREDICTABLE>
d00144ac:	447b4bee 	ldrbtmi	r4, [fp], #-3054	; 0xfffff412
d00144b0:	2a006d9a 	bcs	0xd002fb20
d00144b4:	af60f47f 	svcge	0x0060f47f
d00144b8:	447a4aec 	ldrbtmi	r4, [sl], #-2796	; 0xfffff514
d00144bc:	9a00659a 	bls	0xd002db2c
d00144c0:	9a0165da 	bls	0xd006dc30
d00144c4:	9a02661a 	bls	0xd00add34
d00144c8:	9a03665a 	bls	0xd00ede38
d00144cc:	f04fe0dd 			; <UNDEFINED> instruction: 0xf04fe0dd
d00144d0:	46a334ff 			; <UNDEFINED> instruction: 0x46a334ff
d00144d4:	afbce7a5 	svcge	0x00bce7a5
d00144d8:	f89de7af 			; <UNDEFINED> instruction: 0xf89de7af
d00144dc:	2b1032c2 	blcs	0xd0420fec
d00144e0:	49e3d105 	stmibmi	r3!, {r0, r2, r8, ip, lr, pc}^
d00144e4:	44794630 	ldrbtmi	r4, [r9], #-1584	; 0xfffff9d0
d00144e8:	fe5ef7fb 	mrc2	7, 2, pc, cr14, cr11, {7}
d00144ec:	23ffe744 	mvnscs	lr, #68, 14	; 0x1100000
d00144f0:	1107f240 	tstne	r7, r0, asr #4	; <UNPREDICTABLE>
d00144f4:	f8c94630 			; <UNDEFINED> instruction: 0xf8c94630
d00144f8:	f7fe3000 			; <UNDEFINED> instruction: 0xf7fe3000
d00144fc:	b1e8fca0 	mvnlt	pc, r0, lsr #25
d0014500:	f8c923ff 			; <UNDEFINED> instruction: 0xf8c923ff
d0014504:	4ddb3000 	ldclmi	0, cr3, [fp]
d0014508:	447d212a 	ldrbtmi	r2, [sp], #-298	; 0xfffffed6
d001450c:	f7fe4628 			; <UNDEFINED> instruction: 0xf7fe4628
d0014510:	9006fc96 	mulls	r6, r6, ip
d0014514:	d14c2800 	cmple	ip, r0, lsl #16
d0014518:	3000f8d9 	ldrdcc	pc, [r0], -r9
d001451c:	d0482bff 	strdle	r2, [r8], #-191	; 0xffffff41
d0014520:	721af44f 	andsvc	pc, sl, #1325400064	; 0x4f000000
d0014524:	5303fb02 	movwpl	pc, #15106	; 0x3b02	; <UNPREDICTABLE>
d0014528:	3368f503 	msrcc	SPSR_f, #12582912	; 0xc00000
d001452c:	302df893 	mlacc	sp, r3, r8, pc	; <UNPREDICTABLE>
d0014530:	d13e2b00 	teqle	lr, r0, lsl #22
d0014534:	462849d0 			; <UNDEFINED> instruction: 0x462849d0
d0014538:	e7d54479 			; <UNDEFINED> instruction: 0xe7d54479
d001453c:	f2406af2 	vpmin.s8	q11, q8, q9
d0014540:	429a1301 	addsmi	r1, sl, #67108864	; 0x4000000
d0014544:	4630d118 			; <UNDEFINED> instruction: 0x4630d118
d0014548:	1206e9d6 	andne	lr, r6, #3506176	; 0x358000
d001454c:	f921f7fc 			; <UNDEFINED> instruction: 0xf921f7fc
d0014550:	db112800 	blle	0xd045e558
d0014554:	e9d64630 	ldmib	r6, {r4, r5, r9, sl, lr}^
d0014558:	f7fc1206 			; <UNDEFINED> instruction: 0xf7fc1206
d001455c:	2324f91a 	msrcs	CPSR_s, #425984	; 0x68000
d0014560:	6000fb03 	andvs	pc, r0, r3, lsl #22
d0014564:	3075f500 	rsbscc	pc, r5, r0, lsl #10
d0014568:	33acf890 			; <UNDEFINED> instruction: 0x33acf890
d001456c:	d1032bff 	strdle	r2, [r3, -pc]
d0014570:	f7fe4630 			; <UNDEFINED> instruction: 0xf7fe4630
d0014574:	e7c6fc49 	strb	pc, [r6, r9, asr #24]	; <UNPREDICTABLE>
d0014578:	f24048c0 	vadd.i8	q10, q8, q0
d001457c:	4478131b 	ldrbtmi	r1, [r8], #-795	; 0xfffffce5
d0014580:	429a6ac2 	addsmi	r6, sl, #794624	; 0xc2000
d0014584:	f7fed103 			; <UNDEFINED> instruction: 0xf7fed103
d0014588:	2800ff5b 	stmdacs	r0, {r0, r1, r3, r4, r6, r8, r9, sl, fp, ip, sp, lr, pc}
d001458c:	48bcd1b8 	ldmmi	ip!, {r3, r4, r5, r7, r8, ip, lr, pc}
d0014590:	44784649 	ldrbtmi	r4, [r8], #-1609	; 0xfffff9b7
d0014594:	fe5ef7fe 	mrc2	7, 2, pc, cr14, cr14, {7}
d0014598:	d1b42800 			; <UNDEFINED> instruction: 0xd1b42800
d001459c:	0f00f1ba 	svceq	0x0000f1ba
d00145a0:	49b8d104 	ldmibmi	r8!, {r2, r8, ip, lr, pc}
d00145a4:	48b84479 	ldmmi	r8!, {r0, r3, r4, r5, r6, sl, lr}
d00145a8:	e79d4478 			; <UNDEFINED> instruction: 0xe79d4478
d00145ac:	447949b7 	ldrbtmi	r4, [r9], #-2487	; 0xfffff649
d00145b0:	4db7e7f9 	ldcmi	7, cr14, [r7, #996]!	; 0x3e4
d00145b4:	447daf10 	ldrbtmi	sl, [sp], #-3856	; 0xfffff0f0
d00145b8:	0c18f105 	ldfeqd	f7, [r8], {5}
d00145bc:	000fe8bc 			; <UNDEFINED> instruction: 0x000fe8bc
d00145c0:	e89cc70f 	ldm	ip, {r0, r1, r2, r3, r8, r9, sl, lr, pc}
d00145c4:	e887000f 	stm	r7, {r0, r1, r2, r3}
d00145c8:	69ab000f 	stmibvs	fp!, {r0, r1, r2, r3}
d00145cc:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d00145d0:	46284ab0 			; <UNDEFINED> instruction: 0x46284ab0
d00145d4:	69eb930b 	stmibvs	fp!, {r0, r1, r3, r8, r9, ip, pc}^
d00145d8:	930a447a 	movwls	r4, #42106	; 0xa47a
d00145dc:	93056a6b 	movwls	r6, #23147	; 0x5a6b
d00145e0:	93096aab 	movwls	r6, #39595	; 0x9aab
d00145e4:	3030f895 	mlascc	r0, r5, r8, pc	; <UNPREDICTABLE>
d00145e8:	6b6b9308 	blvs	0xd1af9210
d00145ec:	f7fe9307 			; <UNDEFINED> instruction: 0xf7fe9307
d00145f0:	2800fc34 	stmdacs	r0, {r2, r4, r5, sl, fp, ip, sp, lr, pc}
d00145f4:	aec0f43f 	mcrge	4, 6, pc, cr0, cr15, {1}	; <UNPREDICTABLE>
d00145f8:	213b4aa7 	teqcs	fp, r7, lsr #21
d00145fc:	447a4628 	ldrbtmi	r4, [sl], #-1576	; 0xfffff9d8
d0014600:	fc2bf7fe 	stc2	7, cr15, [fp], #-1016	; 0xfffffc08
d0014604:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0014608:	ad18aeb7 	ldcge	14, cr10, [r8, #-732]	; 0xfffffd24
d001460c:	46a82700 	strtmi	r2, [r8], r0, lsl #14
d0014610:	c262f898 	rsbgt	pc, r2, #152, 16	; 0x980000
d0014614:	d31c4567 	tstle	ip, #432013312	; 0x19c00000
d0014618:	2b009b06 	blcs	0xd003b238
d001461c:	f8d9d13c 			; <UNDEFINED> instruction: 0xf8d9d13c
d0014620:	2bff3000 	blcs	0xcffe0628
d0014624:	4a9dd038 	bmi	0xce78870c
d0014628:	711af44f 	tstvc	sl, pc, asr #8	; <UNPREDICTABLE>
d001462c:	fb01447a 	blx	0xd006581e
d0014630:	f5032303 			; <UNDEFINED> instruction: 0xf5032303
d0014634:	f8b33368 			; <UNDEFINED> instruction: 0xf8b33368
d0014638:	f1bee028 			; <UNDEFINED> instruction: 0xf1bee028
d001463c:	d12d0f00 			; <UNDEFINED> instruction: 0xd12d0f00
d0014640:	447b4b97 	ldrbtmi	r4, [fp], #-2967	; 0xfffff469
d0014644:	2a006d9a 	bcs	0xd002fcb4
d0014648:	ae96f47f 	mrcge	4, 4, APSR_nzcv, cr6, cr15, {3}
d001464c:	447a4a95 	ldrbtmi	r4, [sl], #-2709	; 0xfffff56b
d0014650:	6a69e013 	bvs	0xd1a8c6a4
d0014654:	f8553524 			; <UNDEFINED> instruction: 0xf8553524
d0014658:	9b0a0c04 	blls	0xd0297670
d001465c:	f7fb9a0b 			; <UNDEFINED> instruction: 0xf7fb9a0b
d0014660:	b1b8ffdd 			; <UNDEFINED> instruction: 0xb1b8ffdd
d0014664:	0f00f1ba 	svceq	0x0000f1ba
d0014668:	4a8fd111 	bmi	0xce408ab4
d001466c:	4b8f447a 	blmi	0xce3e585c
d0014670:	6d99447b 	cfldrsvs	mvf4, [r9, #492]	; 0x1ec
d0014674:	f47f2900 			; <UNDEFINED> instruction: 0xf47f2900
d0014678:	659aae7f 	ldrvs	sl, [sl, #3711]	; 0xe7f
d001467c:	65da9a05 	ldrbvs	r9, [sl, #2565]	; 0xa05
d0014680:	661a9a09 	ldrvs	r9, [sl], -r9, lsl #20
d0014684:	665a9a08 	ldrbvs	r9, [sl], -r8, lsl #20
d0014688:	669a9a07 	ldrvs	r9, [sl], r7, lsl #20
d001468c:	4a88e674 	bmi	0xce24e064
d0014690:	e7ec447a 			; <UNDEFINED> instruction: 0xe7ec447a
d0014694:	e7bb3701 	ldr	r3, [fp, r1, lsl #14]!
d0014698:	0e01f04f 	cdpeq	0, 0, cr15, cr1, cr15, {2}
d001469c:	f8bdab18 			; <UNDEFINED> instruction: 0xf8bdab18
d00146a0:	930482c0 	movwls	r8, #17088	; 0x42c0
d00146a4:	437ff5c8 	cmnmi	pc, #200, 10	; 0x32000000	; <UNPREDICTABLE>
d00146a8:	457333ff 	ldrbmi	r3, [r3, #-1023]!	; 0xfffffc01
d00146ac:	9a04d3c8 	bls	0xd01495d4
d00146b0:	0301f10c 	movweq	pc, #4364	; 0x110c	; <UNPREDICTABLE>
d00146b4:	0f00f1ba 	svceq	0x0000f1ba
d00146b8:	f882ad10 			; <UNDEFINED> instruction: 0xf882ad10
d00146bc:	f8993262 			; <UNDEFINED> instruction: 0xf8993262
d00146c0:	930c3000 	movwls	r3, #49152	; 0xc000
d00146c4:	4643bf0c 	strbmi	fp, [r3], -ip, lsl #30
d00146c8:	930d2300 	movwls	r2, #54016	; 0xd300
d00146cc:	93109b0b 	tstls	r0, #11264	; 0x2c00
d00146d0:	93119b0a 	tstls	r1, #10240	; 0x2800
d00146d4:	93139b05 	tstls	r3, #5120	; 0x1400
d00146d8:	93149b09 	tstls	r4, #9216	; 0x2400
d00146dc:	f88d9b08 			; <UNDEFINED> instruction: 0xf88d9b08
d00146e0:	9b073058 	blls	0xd01e0848
d00146e4:	f04f9317 			; <UNDEFINED> instruction: 0xf04f9317
d00146e8:	fb030324 	blx	0xd00d5382
d00146ec:	cd0f2c0c 	stcgt	12, cr2, [pc, #-48]	; 0xd00146c4
d00146f0:	0720f10c 	streq	pc, [r0, -ip, lsl #2]!
d00146f4:	e895c70f 	ldm	r5, {r0, r1, r2, r3, r8, r9, sl, lr, pc}
d00146f8:	e887000f 	stm	r7, {r0, r1, r2, r3}
d00146fc:	9b0c000f 	blls	0xd0314740
d0014700:	3040f88c 	subcc	pc, r0, ip, lsl #17
d0014704:	f88c9b06 			; <UNDEFINED> instruction: 0xf88c9b06
d0014708:	9b0d3041 	blls	0xd0360814
d001470c:	3042f8ac 	subcc	pc, r2, ip, lsr #17
d0014710:	45f0d006 	ldrbmi	sp, [r0, #6]!
d0014714:	aea7f4bf 	mcrge	4, 5, pc, cr7, cr15, {5}	; <UNPREDICTABLE>
d0014718:	f8a39b04 			; <UNDEFINED> instruction: 0xf8a39b04
d001471c:	e6a2e260 	strt	lr, [r2], r0, ror #4
d0014720:	e7f944c6 	ldrb	r4, [r9, r6, asr #9]!
d0014724:	b18b9bc5 	orrlt	r9, fp, r5, asr #23
d0014728:	f04f4e62 			; <UNDEFINED> instruction: 0xf04f4e62
d001472c:	f10d0800 			; <UNDEFINED> instruction: 0xf10d0800
d0014730:	447e0960 	ldrbtmi	r0, [lr], #-2400	; 0xfffff6a0
d0014734:	3567f506 	strbcc	pc, [r7, #-1286]!	; 0xfffffafa	; <UNPREDICTABLE>
d0014738:	3375f506 	cmncc	r5, #25165824	; 0x1800000	; <UNPREDICTABLE>
d001473c:	75e4f505 	strbvc	pc, [r4, #1285]!	; 0x505	; <UNPREDICTABLE>
d0014740:	9b049304 	blls	0xd0139358
d0014744:	3388f8d3 	orrcc	pc, r8, #13828096	; 0xd30000
d0014748:	d31c4598 	tstle	ip, #152, 10	; 0x26000000
d001474c:	db382c00 	blle	0xd0e1f754
d0014750:	731af44f 	tstvc	sl, #1325400064	; 0x4f000000	; <UNPREDICTABLE>
d0014754:	a8184958 	ldmdage	r8, {r3, r4, r6, r8, fp, lr}
d0014758:	44794363 	ldrbtmi	r4, [r9], #-867	; 0xfffffc9d
d001475c:	3367f503 	msrcc	SPSR_sxc, #12582912	; 0xc00000
d0014760:	73e4f503 	mvnvc	pc, #12582912	; 0xc00000
d0014764:	f7fb4419 			; <UNDEFINED> instruction: 0xf7fb4419
d0014768:	2800ff90 	stmdacs	r0, {r4, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d001476c:	f1bad13a 			; <UNDEFINED> instruction: 0xf1bad13a
d0014770:	d1230f00 			; <UNDEFINED> instruction: 0xd1230f00
d0014774:	447a4a51 	ldrbtmi	r4, [sl], #-2641	; 0xfffff5af
d0014778:	447b4b51 	ldrbtmi	r4, [fp], #-2897	; 0xfffff4af
d001477c:	29006d99 	stmdbcs	r0, {r0, r3, r4, r7, r8, sl, fp, sp, lr}
d0014780:	adfaf47f 	cfldrdge	mvd15, [sl, #508]!	; 0x1fc
d0014784:	f895e69a 			; <UNDEFINED> instruction: 0xf895e69a
d0014788:	b1933264 	orrslt	r3, r3, r4, ror #4
d001478c:	2266f895 	rsbcs	pc, r6, #9764864	; 0x950000
d0014790:	429a7a33 	addsmi	r7, sl, #208896	; 0x33000
d0014794:	e9d9d00d 	ldmib	r9, {r0, r2, r3, ip, lr, pc}^
d0014798:	e9d52300 	ldmib	r5, {r8, r9, sp}^
d001479c:	f7fb0100 			; <UNDEFINED> instruction: 0xf7fb0100
d00147a0:	b130ff3d 	teqlt	r0, sp, lsr pc	; <UNPREDICTABLE>
d00147a4:	46484629 	strbmi	r4, [r8], -r9, lsr #12
d00147a8:	ff6ff7fb 			; <UNDEFINED> instruction: 0xff6ff7fb
d00147ac:	4644b108 	strbmi	fp, [r4], -r8, lsl #2
d00147b0:	f108e7ce 			; <UNDEFINED> instruction: 0xf108e7ce
d00147b4:	f5050801 			; <UNDEFINED> instruction: 0xf5050801
d00147b8:	e7c2751a 	bfi	r7, sl, (invalid: 10:2)
d00147bc:	447a4a41 	ldrbtmi	r4, [sl], #-2625	; 0xfffff5bf
d00147c0:	f1bbe7da 			; <UNDEFINED> instruction: 0xf1bbe7da
d00147c4:	db140f00 	blle	0xd05183cc
d00147c8:	f44f483f 	vst2.8	{d20-d21}, [pc :256]
d00147cc:	465c721a 			; <UNDEFINED> instruction: 0x465c721a
d00147d0:	44784639 	ldrbtmi	r4, [r8], #-1593	; 0xfffff9c7
d00147d4:	000bfb02 	andeq	pc, fp, r2, lsl #22
d00147d8:	3067f500 	rsbcc	pc, r7, r0, lsl #10
d00147dc:	70e4f500 	rscvc	pc, r4, r0, lsl #10
d00147e0:	f874f00b 			; <UNDEFINED> instruction: 0xf874f00b
d00147e4:	f50d4620 			; <UNDEFINED> instruction: 0xf50d4620
d00147e8:	e8bd7d33 	pop	{r0, r1, r4, r5, r8, sl, fp, ip, sp, lr}
d00147ec:	b0044ff0 	strdlt	r4, [r4], -r0
d00147f0:	48364770 	ldmdami	r6!, {r4, r5, r6, r8, r9, sl, lr}
d00147f4:	f5004478 			; <UNDEFINED> instruction: 0xf5004478
d00147f8:	f8d33375 			; <UNDEFINED> instruction: 0xf8d33375
d00147fc:	2c184388 	ldccs	3, cr4, [r8], {136}	; 0x88
d0014800:	6d83d10f 	stfvsd	f5, [r3, #60]	; 0x3c
d0014804:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0014808:	4b31adb7 	blmi	0xd0c7feec
d001480c:	6583447b 	strvs	r4, [r3, #1147]	; 0x47b
d0014810:	65c39b00 	strbvs	r9, [r3, #2816]	; 0xb00
d0014814:	66039b01 	strvs	r9, [r3], -r1, lsl #22
d0014818:	66439b02 	strbvs	r9, [r3], -r2, lsl #22
d001481c:	66839b03 	strvs	r9, [r3], r3, lsl #22
d0014820:	1c62e5aa 	cfstr64ne	mvdx14, [r2], #-680	; 0xfffffd58
d0014824:	f8c34639 			; <UNDEFINED> instruction: 0xf8c34639
d0014828:	f44f2388 	vst2.32	{d18-d21}, [pc], r8
d001482c:	fb02721a 	blx	0xd00b109e
d0014830:	f5000004 			; <UNDEFINED> instruction: 0xf5000004
d0014834:	f5003067 			; <UNDEFINED> instruction: 0xf5003067
d0014838:	f00b70e4 			; <UNDEFINED> instruction: 0xf00b70e4
d001483c:	e7d1f847 	ldrb	pc, [r1, r7, asr #16]	; <UNPREDICTABLE>
d0014840:	f6ff2c00 			; <UNDEFINED> instruction: 0xf6ff2c00
d0014844:	f04fadc1 			; <UNDEFINED> instruction: 0xf04fadc1
d0014848:	e5ea3bff 	strb	r3, [sl, #3071]!	; 0xbff
d001484c:	000120ba 	strheq	r2, [r1], -sl
d0014850:	fffffe63 			; <UNDEFINED> instruction: 0xfffffe63
d0014854:	fffffe32 			; <UNDEFINED> instruction: 0xfffffe32
d0014858:	fffffe33 			; <UNDEFINED> instruction: 0xfffffe33
d001485c:	00011fae 	andeq	r1, r1, lr, lsr #31
d0014860:	00011f88 	andeq	r1, r1, r8, lsl #31
d0014864:	fffffe6d 			; <UNDEFINED> instruction: 0xfffffe6d
d0014868:	00011f56 	andeq	r1, r1, r6, asr pc
d001486c:	fffffe52 			; <UNDEFINED> instruction: 0xfffffe52
d0014870:	fffffd4d 			; <UNDEFINED> instruction: 0xfffffd4d
d0014874:	00011efa 	strdeq	r1, [r1], -sl
d0014878:	fffffd19 			; <UNDEFINED> instruction: 0xfffffd19
d001487c:	00011e86 	andeq	r1, r1, r6, lsl #29
d0014880:	00011e72 	andeq	r1, r1, r2, ror lr
d0014884:	fffffb6a 			; <UNDEFINED> instruction: 0xfffffb6a
d0014888:	00011e5c 	andeq	r1, r1, ip, asr lr
d001488c:	fffffb12 			; <UNDEFINED> instruction: 0xfffffb12
d0014890:	00011e4e 	andeq	r1, r1, lr, asr #28
d0014894:	fffffcad 			; <UNDEFINED> instruction: 0xfffffcad
d0014898:	fffffca2 			; <UNDEFINED> instruction: 0xfffffca2
d001489c:	00011dd8 	ldrdeq	r1, [r1], -r8
d00148a0:	00011dc2 	andeq	r1, r1, r2, asr #27
d00148a4:	fffffc72 			; <UNDEFINED> instruction: 0xfffffc72
d00148a8:	fffffb07 			; <UNDEFINED> instruction: 0xfffffb07
d00148ac:	00011d94 	muleq	r1, r4, sp
d00148b0:	fffffacd 			; <UNDEFINED> instruction: 0xfffffacd
d00148b4:	00011cd2 	ldrdeq	r1, [r1], -r2
d00148b8:	00011caa 	andeq	r1, r1, sl, lsr #25
d00148bc:	fffffa31 			; <UNDEFINED> instruction: 0xfffffa31
d00148c0:	00011c8a 	andeq	r1, r1, sl, lsl #25
d00148c4:	fffff9cc 			; <UNDEFINED> instruction: 0xfffff9cc
d00148c8:	00011c32 	andeq	r1, r1, r2, lsr ip
d00148cc:	00011c10 	andeq	r1, r1, r0, lsl ip
d00148d0:	fffffa05 			; <UNDEFINED> instruction: 0xfffffa05

Disassembly of section .text.load_apicore.constprop.0:

d0014960 <.text.load_apicore.constprop.0>:
d0014960:	47f0e92d 	ldrbmi	lr, [r0, sp, lsr #18]!
d0014964:	b0864603 	addlt	r4, r6, r3, lsl #12
d0014968:	4988b938 	stmibmi	r8, {r3, r4, r5, r8, fp, ip, sp, pc}
d001496c:	44794888 	ldrbtmi	r4, [r9], #-2184	; 0xfffff778
d0014970:	f7fb4478 			; <UNDEFINED> instruction: 0xf7fb4478
d0014974:	2000fc19 	andcs	pc, r0, r9, lsl ip	; <UNPREDICTABLE>
d0014978:	4e86e0a0 	cdpmi	0, 8, cr14, cr6, cr0, {5}
d001497c:	71acf644 			; <UNDEFINED> instruction: 0x71acf644
d0014980:	4630447e 			; <UNDEFINED> instruction: 0x4630447e
d0014984:	28004798 	stmdacs	r0, {r3, r4, r7, r8, r9, sl, lr}
d0014988:	f1a0d0ef 			; <UNDEFINED> instruction: 0xf1a0d0ef
d001498c:	f6440218 			; <UNDEFINED> instruction: 0xf6440218
d0014990:	429a7394 	addsmi	r7, sl, #148, 6	; 0x50000002
d0014994:	80f3f200 	rscshi	pc, r3, r0, lsl #4
d0014998:	22041f04 	andcs	r1, r4, #4, 30
d001499c:	19314668 	ldmdbne	r1!, {r3, r5, r6, r9, sl, lr}
d00149a0:	ff94f00a 			; <UNDEFINED> instruction: 0xff94f00a
d00149a4:	46304621 	ldrtmi	r4, [r0], -r1, lsr #12
d00149a8:	fbe6f7fb 	blx	0xcf9d299e
d00149ac:	42989b00 	addsmi	r9, r8, #0, 22
d00149b0:	80e5f040 	rschi	pc, r5, r0, asr #32
d00149b4:	2214ad01 	andscs	sl, r4, #1, 26	; 0x40
d00149b8:	46284631 			; <UNDEFINED> instruction: 0x46284631
d00149bc:	ff86f00a 			; <UNDEFINED> instruction: 0xff86f00a
d00149c0:	22084975 	andcs	r4, r8, #1916928	; 0x1d4000
d00149c4:	44794628 	ldrbtmi	r4, [r9], #-1576	; 0xfffff9d8
d00149c8:	ff90f00a 			; <UNDEFINED> instruction: 0xff90f00a
d00149cc:	4973b120 	ldmdbmi	r3!, {r5, r8, ip, sp, pc}^
d00149d0:	44794873 	ldrbtmi	r4, [r9], #-2163	; 0xfffff78d
d00149d4:	e7cc4478 			; <UNDEFINED> instruction: 0xe7cc4478
d00149d8:	9a034b6b 	bls	0xd00e778c
d00149dc:	f040429a 			; <UNDEFINED> instruction: 0xf040429a
d00149e0:	9a0480ce 	bls	0xd0134d20
d00149e4:	2b9f1e53 	blcs	0xce7dc338
d00149e8:	80c9f200 	sbchi	pc, r9, r0, lsl #4
d00149ec:	2bc09b05 	blcs	0xcf03b608
d00149f0:	80c5f200 	sbchi	pc, r5, r0, lsl #4
d00149f4:	43512154 	cmpmi	r1, #84, 2
d00149f8:	435a2224 	cmpmi	sl, #36, 4	; 0x40000002
d00149fc:	f107188f 			; <UNDEFINED> instruction: 0xf107188f
d0014a00:	429c0328 	addsmi	r0, ip, #40, 6	; 0xa0000000
d0014a04:	80bbf040 	adcshi	pc, fp, r0, asr #32
d0014a08:	31144c66 	tstcc	r4, r6, ror #24
d0014a0c:	4431447c 	ldrtmi	r4, [r1], #-1148	; 0xfffffb84
d0014a10:	3082f504 	addcc	pc, r2, r4, lsl #10
d0014a14:	f00a30a4 			; <UNDEFINED> instruction: 0xf00a30a4
d0014a18:	f504ff59 			; <UNDEFINED> instruction: 0xf504ff59
d0014a1c:	f107308f 			; <UNDEFINED> instruction: 0xf107308f
d0014a20:	f5040114 			; <UNDEFINED> instruction: 0xf5040114
d0014a24:	2214348f 	andscs	r3, r4, #-1895825408	; 0x8f000000
d0014a28:	70d2f500 	sbcsvc	pc, r2, r0, lsl #10
d0014a2c:	f00a4431 			; <UNDEFINED> instruction: 0xf00a4431
d0014a30:	f8b4ff4d 			; <UNDEFINED> instruction: 0xf8b4ff4d
d0014a34:	f64001b4 			; <UNDEFINED> instruction: 0xf64001b4
d0014a38:	1f0273fc 	svcne	0x000273fc
d0014a3c:	f200429a 	vqsub.s8	d4, d16, d10
d0014a40:	4a59809e 	bmi	0xd1674cc0
d0014a44:	0303f000 	movweq	pc, #12288	; 0x3000	; <UNPREDICTABLE>
d0014a48:	f502447a 			; <UNDEFINED> instruction: 0xf502447a
d0014a4c:	f8b1318f 			; <UNDEFINED> instruction: 0xf8b1318f
d0014a50:	430b11b6 	movwmi	r1, #45494	; 0xb1b6
d0014a54:	8093f040 	addshi	pc, r3, r0, asr #32
d0014a58:	328ff502 	addcc	pc, pc, #8388608	; 0x800000
d0014a5c:	f5022104 			; <UNDEFINED> instruction: 0xf5022104
d0014a60:	f83272d2 			; <UNDEFINED> instruction: 0xf83272d2
d0014a64:	1e4e4b02 	vmlane.f64	d20, d14, d2
d0014a68:	f0404026 			; <UNDEFINED> instruction: 0xf0404026
d0014a6c:	1a418088 	bne	0xd1074c94
d0014a70:	f200428c 	vhsub.s8	d4, d16, d12
d0014a74:	33018084 	movwcc	r8, #4228	; 0x1084
d0014a78:	d1222b08 			; <UNDEFINED> instruction: 0xd1222b08
d0014a7c:	46b04c4b 	ldrtmi	r4, [r0], fp, asr #24
d0014a80:	f6404f4b 			; <UNDEFINED> instruction: 0xf6404f4b
d0014a84:	447c79fc 	ldrbtmi	r7, [ip], #-2556	; 0xfffff604
d0014a88:	f504447f 			; <UNDEFINED> instruction: 0xf504447f
d0014a8c:	37144450 			; <UNDEFINED> instruction: 0x37144450
d0014a90:	9b04346c 	blls	0xd0121c48
d0014a94:	d3194598 	tstle	r9, #152, 10	; 0x26000000
d0014a98:	447c4c46 	ldrbtmi	r4, [ip], #-3142	; 0xfffff3ba
d0014a9c:	3482f504 	strcc	pc, [r2], #1284	; 0x504
d0014aa0:	9b0534a4 	blls	0xd0161d38
d0014aa4:	d361429e 	cmnle	r1, #-536870903	; 0xe0000009
d0014aa8:	447c4c43 	ldrbtmi	r4, [ip], #-3139	; 0xfffff3bd
d0014aac:	4450f504 	ldrbmi	pc, [r0], #-1284	; 0xfffffafc	; <UNPREDICTABLE>
d0014ab0:	3410cd0f 	ldrcc	ip, [r0], #-3343	; 0xfffff2f1
d0014ab4:	682bc40f 	stmdavs	fp!, {r0, r1, r2, r3, sl, lr, pc}
d0014ab8:	60232001 	eorvs	r2, r3, r1
d0014abc:	e8bdb006 	pop	{r1, r2, ip, sp, pc}
d0014ac0:	2b0187f0 	blcs	0xd0076a88
d0014ac4:	2101bf0c 	tstcs	r1, ip, lsl #30
d0014ac8:	e7ca2104 	strb	r2, [sl, r4, lsl #2]
d0014acc:	0a48f1a4 	beq	0xd1251164
d0014ad0:	46392254 			; <UNDEFINED> instruction: 0x46392254
d0014ad4:	f00a4650 			; <UNDEFINED> instruction: 0xf00a4650
d0014ad8:	2201fef9 	andcs	pc, r1, #3984	; 0xf90
d0014adc:	46502140 	ldrbmi	r2, [r0], -r0, asr #2
d0014ae0:	fc60f7fb 	stc2l	7, cr15, [r0], #-1004	; 0xfffffc14
d0014ae4:	d04a2800 	suble	r2, sl, r0, lsl #16
d0014ae8:	2c02f814 	stccs	8, cr15, [r2], {20}
d0014aec:	d8462a0c 	stmdale	r6, {r2, r3, r9, fp, sp}^
d0014af0:	3c01f814 	stccc	8, cr15, [r1], {20}
d0014af4:	b2d93b05 	sbcslt	r3, r9, #5120	; 0x1400
d0014af8:	d840290c 	stmdale	r0, {r2, r3, r8, fp, sp}^
d0014afc:	034ff641 	movteq	pc, #63041	; 0xf641	; <UNPREDICTABLE>
d0014b00:	43db40cb 	bicsmi	r4, fp, #203	; 0xcb
d0014b04:	0301f013 	movweq	pc, #4115	; 0x1013	; <UNPREDICTABLE>
d0014b08:	f834d139 			; <UNDEFINED> instruction: 0xf834d139
d0014b0c:	f64f0c08 			; <UNDEFINED> instruction: 0xf64f0c08
d0014b10:	428871ff 	addmi	r7, r8, #-1073741761	; 0xc000003f
d0014b14:	f834d033 			; <UNDEFINED> instruction: 0xf834d033
d0014b18:	42880c06 	addmi	r0, r8, #1536	; 0x600
d0014b1c:	f1a4d02f 			; <UNDEFINED> instruction: 0xf1a4d02f
d0014b20:	f83c0c08 			; <UNDEFINED> instruction: 0xf83c0c08
d0014b24:	42880b02 	addmi	r0, r8, #2048	; 0x800
d0014b28:	4548d003 	strbmi	sp, [r8, #-3]
d0014b2c:	0780d827 	streq	sp, [r0, r7, lsr #16]
d0014b30:	3301d125 	movwcc	sp, #4389	; 0x1125
d0014b34:	d1f42b03 	mvnsle	r2, r3, lsl #22
d0014b38:	23004621 	movwcs	r4, #1569	; 0x621
d0014b3c:	d806429a 	stmdale	r6, {r1, r3, r4, r7, r9, lr}
d0014b40:	d10f2a0c 	tstle	pc, ip, lsl #20
d0014b44:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d0014b48:	37543454 			; <UNDEFINED> instruction: 0x37543454
d0014b4c:	f811e7a1 			; <UNDEFINED> instruction: 0xf811e7a1
d0014b50:	f1000b01 			; <UNDEFINED> instruction: 0xf1000b01
d0014b54:	f1bc3cff 			; <UNDEFINED> instruction: 0xf1bc3cff
d0014b58:	d8100f15 	ldmdale	r0, {r0, r2, r4, r8, r9, sl, fp}
d0014b5c:	d00e2807 	andle	r2, lr, r7, lsl #16
d0014b60:	e7eb3301 	strb	r3, [fp, r1, lsl #6]!
d0014b64:	b9535ca3 	ldmdblt	r3, {r0, r1, r5, r7, sl, fp, ip, lr}^
d0014b68:	e7e93201 	strb	r3, [r9, r1, lsl #4]!
d0014b6c:	22004620 	andcs	r4, r0, #32, 12	; 0x2000000
d0014b70:	34242120 	strtcc	r2, [r4], #-288	; 0xfffffee0
d0014b74:	fc16f7fb 	ldc2	7, cr15, [r6], {251}	; 0xfb
d0014b78:	3601b108 	strcc	fp, [r1], -r8, lsl #2
d0014b7c:	490fe791 	stmdbmi	pc, {r0, r4, r7, r8, r9, sl, sp, lr, pc}	; <UNPREDICTABLE>
d0014b80:	4479480f 	ldrbtmi	r4, [r9], #-2063	; 0xfffff7f1
d0014b84:	e6f44478 	uxtah	r4, r4, r8, ror #8
d0014b88:	2001f000 	andcs	pc, r1, r0
d0014b8c:	ffffff62 			; <UNDEFINED> instruction: 0xffffff62
d0014b90:	00011a94 	muleq	r1, r4, sl
d0014b94:	0000cad4 	ldrdeq	ip, [r0], -r4
d0014b98:	ffffff35 			; <UNDEFINED> instruction: 0xffffff35
d0014b9c:	ffffff31 			; <UNDEFINED> instruction: 0xffffff31
d0014ba0:	00011a30 	andeq	r1, r1, r0, lsr sl
d0014ba4:	000119f8 	strdeq	r1, [r1], -r8
d0014ba8:	000119bc 			; <UNDEFINED> instruction: 0x000119bc
d0014bac:	0001197e 	andeq	r1, r1, lr, ror r9
d0014bb0:	0000c9cc 	andeq	ip, r0, ip, asr #19
d0014bb4:	0001196a 	andeq	r1, r1, sl, ror #18
d0014bb8:	0001195a 	andeq	r1, r1, sl, asr r9
d0014bbc:	fffffdbe 			; <UNDEFINED> instruction: 0xfffffdbe
d0014bc0:	00011880 	andeq	r1, r1, r0, lsl #17

Disassembly of section .text.accept_sdk_type.constprop.0:

d0014bc4 <.text.accept_sdk_type.constprop.0>:
d0014bc4:	4c0cb538 	cfstr32mi	mvfx11, [ip], {56}	; 0x38
d0014bc8:	031cf24d 	tsteq	ip, #-805306364	; 0xd0000004	; <UNPREDICTABLE>
d0014bcc:	447c4602 	ldrbtmi	r4, [ip], #-1538	; 0xfffff9fe
d0014bd0:	b17b58e3 	cmnlt	fp, r3, ror #17
d0014bd4:	f2406ae5 	vpmax.s8	q11, q8, <illegal reg q10.5>
d0014bd8:	429d1301 	addsmi	r1, sp, #67108864	; 0x4000000
d0014bdc:	e9d4d10a 	ldmib	r4, {r1, r3, r8, ip, lr, pc}^
d0014be0:	f7fb0106 			; <UNDEFINED> instruction: 0xf7fb0106
d0014be4:	b128fe47 	msrlt	R8_fiq, r7
d0014be8:	46204629 	strtmi	r4, [r0], -r9, lsr #12
d0014bec:	4038e8bd 	ldrhtmi	lr, [r8], -sp
d0014bf0:	b925f7fe 	stmdblt	r5!, {r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}
d0014bf4:	bd382000 	ldclt	0, cr2, [r8, #-0]
d0014bf8:	00011836 	andeq	r1, r1, r6, lsr r8

Disassembly of section .text.wide_immediate:

d0014bfc <.text.wide_immediate>:
d0014bfc:	085db530 	ldmdaeq	sp, {r4, r5, r8, sl, ip, sp, pc}^
d0014c00:	3413ea41 	ldrcc	lr, [r3], #-2625	; 0xfffff5bf
d0014c04:	6580f405 	strvs	pc, [r0, #1029]	; 0x405
d0014c08:	011bb2d9 			; <UNDEFINED> instruction: 0x011bb2d9
d0014c0c:	ea41432c 	b	0xd10658c4
d0014c10:	4d0a2202 	sfmmi	f2, 4, [sl, #-8]
d0014c14:	41e0f403 	mvnmi	pc, r3, lsl #8
d0014c18:	447db224 	ldrbtmi	fp, [sp], #-548	; 0xfffffddc
d0014c1c:	4428430a 	strtmi	r4, [r8], #-778	; 0xfffffcf6
d0014c20:	f880b292 			; <UNDEFINED> instruction: 0xf880b292
d0014c24:	f3c44040 	vmla.i<illegal width 8>	q10, q2, d0[0]
d0014c28:	f8802407 			; <UNDEFINED> instruction: 0xf8802407
d0014c2c:	0a122042 	beq	0xd049cd3c
d0014c30:	4041f880 	submi	pc, r1, r0, lsl #17
d0014c34:	2043f880 	subcs	pc, r3, r0, lsl #17
d0014c38:	bf00bd30 	svclt	0x0000bd30
d0014c3c:	0015ca8a 	andseq	ip, r5, sl, lsl #21

Disassembly of section .text.emit:

d0014c5c <.text.emit>:
d0014c5c:	b4306d82 	ldrtlt	r6, [r0], #-3458	; 0xfffff27e
d0014c60:	f500b9b2 			; <UNDEFINED> instruction: 0xf500b9b2
d0014c64:	f8d3338f 			; <UNDEFINED> instruction: 0xf8d3338f
d0014c68:	1cac51b8 	stfnes	f5, [ip], #736	; 0x2e0
d0014c6c:	1f80f5b4 	svcne	0x0080f5b4
d0014c70:	4908d904 	stmdbmi	r8, {r2, r8, fp, ip, lr, pc}
d0014c74:	4479bc30 	ldrbtmi	fp, [r9], #-3120	; 0xfffff3d0
d0014c78:	ba96f7fb 	blt	0xce5d2c6c
d0014c7c:	447a4a06 	ldrbtmi	r4, [sl], #-2566	; 0xfffff5fa
d0014c80:	f882442a 			; <UNDEFINED> instruction: 0xf882442a
d0014c84:	0a091040 	beq	0xd0258d8c
d0014c88:	1041f882 	subne	pc, r1, r2, lsl #17
d0014c8c:	41b8f8c3 			; <UNDEFINED> instruction: 0x41b8f8c3
d0014c90:	4770bc30 			; <UNDEFINED> instruction: 0x4770bc30
d0014c94:	ffffffc6 			; <UNDEFINED> instruction: 0xffffffc6
d0014c98:	0015ca26 	andseq	ip, r5, r6, lsr #20

Disassembly of section .text.load_constant:

d0014c9c <.text.load_constant>:
d0014c9c:	e92d2aff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r9, fp, sp}
d0014ca0:	460541f0 			; <UNDEFINED> instruction: 0x460541f0
d0014ca4:	4614460e 	ldrmi	r4, [r4], -lr, lsl #12
d0014ca8:	2907d80a 	stmdbcs	r7, {r1, r3, fp, ip, lr, pc}
d0014cac:	ea42d808 	b	0xd10cacd4
d0014cb0:	f4412101 	vst4.8	{d18,d20,d22,d24}, [r1], r1
d0014cb4:	e8bd5100 	pop	{r8, ip, lr}
d0014cb8:	b28941f0 	addlt	r4, r9, #240, 2	; 0x3c
d0014cbc:	bfcef7ff 	svclt	0x00cef7ff
d0014cc0:	338ff505 	orrcc	pc, pc, #20971520	; 0x1400000
d0014cc4:	46282100 	strtmi	r2, [r8], -r0, lsl #2
d0014cc8:	71b8f8d3 			; <UNDEFINED> instruction: 0x71b8f8d3
d0014ccc:	ffc6f7ff 			; <UNDEFINED> instruction: 0xffc6f7ff
d0014cd0:	f7ff2100 			; <UNDEFINED> instruction: 0xf7ff2100
d0014cd4:	f5b4ffc3 			; <UNDEFINED> instruction: 0xf5b4ffc3
d0014cd8:	d3053f80 	movwle	r3, #24448	; 0x5f80
d0014cdc:	f7ff2100 			; <UNDEFINED> instruction: 0xf7ff2100
d0014ce0:	2100ffbd 			; <UNDEFINED> instruction: 0x2100ffbd
d0014ce4:	ffbaf7ff 			; <UNDEFINED> instruction: 0xffbaf7ff
d0014ce8:	b9a36dab 	stmiblt	r3!, {r0, r1, r3, r5, r7, r8, sl, fp, sp, lr}
d0014cec:	4632b2a3 	ldrtmi	fp, [r2], -r3, lsr #5
d0014cf0:	2140f24f 	cmpcs	r0, pc, asr #4	; <UNPREDICTABLE>
d0014cf4:	f7ff4638 			; <UNDEFINED> instruction: 0xf7ff4638
d0014cf8:	f5b4ff81 			; <UNDEFINED> instruction: 0xf5b4ff81
d0014cfc:	d30a3f80 	movwle	r3, #44928	; 0xaf80
d0014d00:	b9436dab 	stmdblt	r3, {r0, r1, r3, r5, r7, r8, sl, fp, sp, lr}^
d0014d04:	46320c23 	ldrtmi	r0, [r2], -r3, lsr #24
d0014d08:	f24f1d38 	vmla.f32	d17, d15, d24
d0014d0c:	e8bd21c0 	pop	{r6, r7, r8, sp}
d0014d10:	f7ff41f0 			; <UNDEFINED> instruction: 0xf7ff41f0
d0014d14:	e8bdbf73 	pop	{r0, r1, r4, r5, r6, r8, r9, sl, fp, ip, sp, pc}
d0014d18:	Address 0x00000000d0014d18 is out of bounds.


Disassembly of section .text.constant:

d0014d1a <.text.constant>:
d0014d1a:	2100460a 	tstcs	r0, sl, lsl #12
d0014d1e:	bfbdf7ff 	svclt	0x00bdf7ff

Disassembly of section .text.null_argument:

d0014d28 <.text.null_argument>:
d0014d28:	f5a36ac3 			; <UNDEFINED> instruction: 0xf5a36ac3
d0014d2c:	2a017281 	bcs	0xd0071738
d0014d30:	4604b570 			; <UNDEFINED> instruction: 0x4604b570
d0014d34:	6a03d803 	bvs	0xd010ad48
d0014d38:	2000b1eb 	andcs	fp, r0, fp, ror #3
d0014d3c:	f240bd70 	vmla.f32	<illegal reg q13.5>, q0, q8
d0014d40:	42931201 	addsmi	r1, r3, #268435456	; 0x10000000
d0014d44:	4a10d1f9 	bmi	0xd0449530
d0014d48:	5606e9d0 			; <UNDEFINED> instruction: 0x5606e9d0
d0014d4c:	4631447a 			; <UNDEFINED> instruction: 0x4631447a
d0014d50:	f7fb4628 			; <UNDEFINED> instruction: 0xf7fb4628
d0014d54:	2800fd8f 	stmdacs	r0, {r0, r1, r2, r3, r7, r8, sl, fp, ip, sp, lr, pc}
d0014d58:	4632d0ef 	ldrtmi	sp, [r2], -pc, ror #1
d0014d5c:	46204629 	strtmi	r4, [r0], -r9, lsr #12
d0014d60:	fcd2f7fb 	ldc2l	7, cr15, [r2], {251}	; 0xfb
d0014d64:	dae82800 	ble	0xcfa1ed6c
d0014d68:	46294632 			; <UNDEFINED> instruction: 0x46294632
d0014d6c:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0014d70:	2800fceb 	stmdacs	r0, {r0, r1, r3, r5, r6, r7, sl, fp, ip, sp, lr, pc}
d0014d74:	4620dae1 	strtmi	sp, [r0], -r1, ror #21
d0014d78:	f846f7fe 			; <UNDEFINED> instruction: 0xf846f7fe
d0014d7c:	21004620 	tstcs	r0, r0, lsr #12
d0014d80:	ffcbf7ff 			; <UNDEFINED> instruction: 0xffcbf7ff
d0014d84:	e7d92001 	ldrb	r2, [r9, r1]
d0014d88:	ffffffd2 			; <UNDEFINED> instruction: 0xffffffd2

Disassembly of section .text.load_local:

d0014d8c <.text.load_local>:
d0014d8c:	b570291f 	ldrblt	r2, [r0, #-2335]!	; 0xfffff6e1
d0014d90:	b28db294 	addlt	fp, sp, #148, 4	; 0x40000009
d0014d94:	ea44d80a 	b	0xd114adc4
d0014d98:	f4411185 	vst4.32	{d17,d19,d21,d23}, [r1], r5
d0014d9c:	f04141d0 			; <UNDEFINED> instruction: 0xf04141d0
d0014da0:	b2890138 	addlt	r0, r9, #56, 2
d0014da4:	4070e8bd 	ldrhtmi	lr, [r0], #-141	; 0xffffff73
d0014da8:	bf58f7ff 	svclt	0x0058f7ff
d0014dac:	01d7f64f 	bicseq	pc, r7, pc, asr #12
d0014db0:	ff54f7ff 			; <UNDEFINED> instruction: 0xff54f7ff
d0014db4:	ea4100a9 	b	0xd1055060
d0014db8:	b2893104 	addlt	r3, r9, #4, 2
d0014dbc:	Address 0x00000000d0014dbc is out of bounds.


Disassembly of section .text.store_local:

d0014dbe <.text.store_local>:
d0014dbe:	b570291f 	ldrblt	r2, [r0, #-2335]!	; 0xfffff6e1
d0014dc2:	b28db294 	addlt	fp, sp, #148, 4	; 0x40000009
d0014dc6:	ea44d80a 	b	0xd114adf6
d0014dca:	f4411185 	vst4.32	{d17,d19,d21,d23}, [r1], r5
d0014dce:	f04141c0 			; <UNDEFINED> instruction: 0xf04141c0
d0014dd2:	b2890138 	addlt	r0, r9, #56, 2
d0014dd6:	4070e8bd 	ldrhtmi	lr, [r0], #-141	; 0xffffff73
d0014dda:	bf3ff7ff 	svclt	0x003ff7ff
d0014dde:	01c7f64f 	biceq	pc, r7, pc, asr #12
d0014de2:	ff3bf7ff 			; <UNDEFINED> instruction: 0xff3bf7ff
d0014de6:	ea4100a9 	b	0xd1055092
d0014dea:	b2893104 	addlt	r3, r9, #4, 2
d0014dee:	Address 0x00000000d0014dee is out of bounds.


Disassembly of section .text.local_address:

d0014df0 <.text.local_address>:
d0014df0:	4604b510 			; <UNDEFINED> instruction: 0x4604b510
d0014df4:	2100008a 	smlabbcs	r0, sl, r0, r0
d0014df8:	ff50f7ff 			; <UNDEFINED> instruction: 0xff50f7ff
d0014dfc:	f6414620 			; <UNDEFINED> instruction: 0xf6414620
d0014e00:	e8bd0138 	pop	{r3, r4, r5, r8}
d0014e04:	f7ff4010 			; <UNDEFINED> instruction: 0xf7ff4010
d0014e08:	Address 0x00000000d0014e08 is out of bounds.


Disassembly of section .text.int_double_pointer_value:

d0014e7c <.text.int_double_pointer_value>:
d0014e7c:	4ff8e92d 	svcmi	0x00f8e92d
d0014e80:	f7ff4604 			; <UNDEFINED> instruction: 0xf7ff4604
d0014e84:	bb28ff51 	bllt	0xd0a54bd0
d0014e88:	46202126 	strtmi	r2, [r0], -r6, lsr #2
d0014e8c:	ffd7f7fd 			; <UNDEFINED> instruction: 0xffd7f7fd
d0014e90:	46054a20 	strmi	r4, [r5], -r0, lsr #20
d0014e94:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d0014e98:	4620447a 			; <UNDEFINED> instruction: 0x4620447a
d0014e9c:	9024f8d4 	ldrdls	pc, [r4], -r4	; <UNPREDICTABLE>
d0014ea0:	8028f8d4 	ldrdhi	pc, [r8], -r4	; <UNPREDICTABLE>
d0014ea4:	7030f894 	mlasvc	r0, r4, r8, pc	; <UNPREDICTABLE>
d0014ea8:	e9d46b66 	ldmib	r4, {r1, r2, r5, r6, r8, r9, fp, sp, lr}^
d0014eac:	f7fdab06 			; <UNDEFINED> instruction: 0xf7fdab06
d0014eb0:	b178ffd4 	ldrsblt	pc, [r8, #-244]!	; 0xffffff0c	; <UNPREDICTABLE>
d0014eb4:	465a4651 			; <UNDEFINED> instruction: 0x465a4651
d0014eb8:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0014ebc:	1e01fc25 	cdpne	12, 0, cr15, cr1, cr5, {1}
d0014ec0:	6da3da0a 			; <UNDEFINED> instruction: 0x6da3da0a
d0014ec4:	4b14b933 	blmi	0xd0543398
d0014ec8:	66a6447b 	sxtabvs	r4, r6, fp, ror #8
d0014ecc:	3916e9c4 	ldmdbcc	r6, {r2, r6, r7, r8, fp, sp, lr, pc}
d0014ed0:	8718e9c4 	ldrhi	lr, [r8, -r4, asr #19]
d0014ed4:	8ff8e8bd 	svchi	0x00f8e8bd
d0014ed8:	fb032330 	blx	0xd00ddba2
d0014edc:	f5034301 			; <UNDEFINED> instruction: 0xf5034301
d0014ee0:	f89313a4 			; <UNDEFINED> instruction: 0xf89313a4
d0014ee4:	b1353655 	teqlt	r5, r5, asr r6
d0014ee8:	d10c2b0a 	tstle	ip, sl, lsl #22
d0014eec:	e8bd4620 	pop	{r5, r9, sl, lr}
d0014ef0:	f7ff4ff8 			; <UNDEFINED> instruction: 0xf7ff4ff8
d0014ef4:	2b13bf7d 	blcs	0xd0504cf0
d0014ef8:	462ad105 	strtmi	sp, [sl], -r5, lsl #2
d0014efc:	e8bd4620 	pop	{r5, r9, sl, lr}
d0014f00:	f7ff4ff8 			; <UNDEFINED> instruction: 0xf7ff4ff8
d0014f04:	6da3bf43 	stcvs	15, cr11, [r3, #268]!	; 0x10c
d0014f08:	d1e32b00 	mvnle	r2, r0, lsl #22
d0014f0c:	447b4b03 	ldrbtmi	r4, [fp], #-2819	; 0xfffff4fd
d0014f10:	bf00e7db 	svclt	0x0000e7db
d0014f14:	ffffff6e 			; <UNDEFINED> instruction: 0xffffff6e
d0014f18:	ffffff5e 			; <UNDEFINED> instruction: 0xffffff5e
d0014f1c:	ffffff36 			; <UNDEFINED> instruction: 0xffffff36

Disassembly of section .text.emit_address:

d0014f48 <.text.emit_address>:
d0014f48:	460db570 			; <UNDEFINED> instruction: 0x460db570
d0014f4c:	315ff500 	cmpcc	pc, r0, lsl #10	; <UNPREDICTABLE>
d0014f50:	f8d14604 			; <UNDEFINED> instruction: 0xf8d14604
d0014f54:	f5b333c0 			; <UNDEFINED> instruction: 0xf5b333c0
d0014f58:	d1056f00 	tstle	r5, r0, lsl #30
d0014f5c:	e8bd4917 	pop	{r0, r1, r2, r4, r8, fp, lr}
d0014f60:	44794070 	ldrbtmi	r4, [r9], #-112	; 0xffffff90
d0014f64:	b920f7fb 	stmdblt	r0!, {r0, r1, r3, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}
d0014f68:	26041c58 			; <UNDEFINED> instruction: 0x26041c58
d0014f6c:	03c0f8c1 	biceq	pc, r0, #12648448	; 0xc10000
d0014f70:	fb01210c 	blx	0xd005d3aa
d0014f74:	f5044303 			; <UNDEFINED> instruction: 0xf5044303
d0014f78:	f503318f 			; <UNDEFINED> instruction: 0xf503318f
d0014f7c:	f8d13347 			; <UNDEFINED> instruction: 0xf8d13347
d0014f80:	f8c311b8 			; <UNDEFINED> instruction: 0xf8c311b8
d0014f84:	f8c323c4 			; <UNDEFINED> instruction: 0xf8c323c4
d0014f88:	f88313c0 			; <UNDEFINED> instruction: 0xf88313c0
d0014f8c:	210053c8 	smlabtcs	r0, r8, r3, r5
d0014f90:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0014f94:	3e01fe63 	cdpcc	14, 0, cr15, cr1, cr3, {3}
d0014f98:	f44fd1f9 	vst4.<illegal width 64>	{d29,d31,d33,d35}, [pc :256], r9
d0014f9c:	f7ff4122 			; <UNDEFINED> instruction: 0xf7ff4122
d0014fa0:	2d01fe5d 	stccs	14, cr15, [r1, #-372]	; 0xfffffe8c
d0014fa4:	2141bf0c 	cmpcs	r1, ip, lsl #30
d0014fa8:	f4412100 	vst4.8	{d18,d20,d22,d24}, [r1], r0
d0014fac:	e8bd51c0 	pop	{r6, r7, r8, ip, lr}
d0014fb0:	f0414070 			; <UNDEFINED> instruction: 0xf0414070
d0014fb4:	f7ff0110 			; <UNDEFINED> instruction: 0xf7ff0110
d0014fb8:	bf00be51 	svclt	0x0000be51
d0014fbc:	ffffffba 			; <UNDEFINED> instruction: 0xffffffba

Disassembly of section .text.function_pointer_value.constprop.0:

d0015054 <.text.function_pointer_value.constprop.0>:
d0015054:	4ff7e92d 	svcmi	0x00f7e92d
d0015058:	46054c4c 	strmi	r4, [r5], -ip, asr #24
d001505c:	4620447c 			; <UNDEFINED> instruction: 0x4620447c
d0015060:	fe62f7ff 	mcr2	7, 3, pc, cr2, cr15, {7}	; <UNPREDICTABLE>
d0015064:	2126bb98 			; <UNDEFINED> instruction: 0x2126bb98
d0015068:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d001506c:	4a48fee8 	bmi	0xd1254c14
d0015070:	f2406b63 	vqdmulh.s<illegal width 8>	q11, q0, <illegal reg q9.5>
d0015074:	447a1101 	ldrbtmi	r1, [sl], #-257	; 0xfffffeff
d0015078:	f8d44620 			; <UNDEFINED> instruction: 0xf8d44620
d001507c:	f8d49024 			; <UNDEFINED> instruction: 0xf8d49024
d0015080:	f8948028 			; <UNDEFINED> instruction: 0xf8948028
d0015084:	93017030 	movwls	r7, #4144	; 0x1030
d0015088:	b606e9d4 			; <UNDEFINED> instruction: 0xb606e9d4
d001508c:	fee5f7fd 	mcr2	7, 7, pc, cr5, cr13, {7}	; <UNPREDICTABLE>
d0015090:	4632b1e8 	ldrtmi	fp, [r2], -r8, ror #3
d0015094:	46204659 			; <UNDEFINED> instruction: 0x46204659
d0015098:	fb36f7fb 	blx	0xd0dd308e
d001509c:	0a00f1b0 	beq	0xd0051764
d00150a0:	2030db34 	eorscs	sp, r0, r4, lsr fp
d00150a4:	f00afb00 			; <UNDEFINED> instruction: 0xf00afb00
d00150a8:	f5031823 			; <UNDEFINED> instruction: 0xf5031823
d00150ac:	f89313a4 			; <UNDEFINED> instruction: 0xf89313a4
d00150b0:	2a0c2655 	bcs	0xd031ea0c
d00150b4:	4b37d00e 	blmi	0xd0e090f4
d00150b8:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d00150bc:	4a36b93a 	bmi	0xd0dc35ac
d00150c0:	e9c3447a 	stmib	r3, {r1, r3, r4, r5, r6, sl, lr}^
d00150c4:	9a012916 	bls	0xd005f524
d00150c8:	8718e9c3 	ldrhi	lr, [r8, -r3, asr #19]
d00150cc:	b003669a 	mullt	r3, sl, r6
d00150d0:	8ff0e8bd 	svchi	0x00f0e8bd
d00150d4:	f8937829 			; <UNDEFINED> instruction: 0xf8937829
d00150d8:	428a2657 	addmi	r2, sl, #91226112	; 0x5700000
d00150dc:	f893d1eb 			; <UNDEFINED> instruction: 0xf893d1eb
d00150e0:	786b1658 	stmdavc	fp!, {r3, r4, r6, r9, sl, ip}^
d00150e4:	d1e64299 			; <UNDEFINED> instruction: 0xd1e64299
d00150e8:	10a4f500 	adcne	pc, r4, r0, lsl #10
d00150ec:	f2001ca9 			; <UNDEFINED> instruction: 0xf2001ca9
d00150f0:	44206059 	strtmi	r6, [r0], #-89	; 0xffffffa7
d00150f4:	fbfaf00a 	blx	0xcfed1126
d00150f8:	28004602 	stmdacs	r0, {r1, r9, sl, lr}
d00150fc:	4651d1db 			; <UNDEFINED> instruction: 0x4651d1db
d0015100:	b0034620 	andlt	r4, r3, r0, lsr #12
d0015104:	4ff0e8bd 	svcmi	0x00f0e8bd
d0015108:	be40f7ff 	mcrlt	7, 2, pc, cr0, cr15, {7}	; <UNPREDICTABLE>
d001510c:	46594632 			; <UNDEFINED> instruction: 0x46594632
d0015110:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0015114:	f1b0fb83 			; <UNDEFINED> instruction: 0xf1b0fb83
d0015118:	db260a00 	blle	0xd0997920
d001511c:	46594632 			; <UNDEFINED> instruction: 0x46594632
d0015120:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0015124:	2800fb11 	stmdacs	r0, {r0, r4, r8, r9, fp, ip, sp, lr, pc}
d0015128:	2338da1f 	teqcs	r8, #126976	; 0x1f000
d001512c:	fb034a13 	blx	0xd00e7982
d0015130:	18e1f30a 	stmiane	r1!, {r1, r3, r8, r9, ip, sp, lr, pc}^
d0015134:	b9c25c8a 	stmiblt	r2, {r1, r3, r7, sl, fp, ip, lr}^
d0015138:	78284a11 	stmdavc	r8!, {r0, r4, r9, fp, lr}
d001513c:	42825c8a 	addmi	r5, r2, #35328	; 0x8a00
d0015140:	4810d113 	ldmdami	r0, {r0, r1, r4, r8, ip, lr, pc}
d0015144:	78695c08 	stmdavc	r9!, {r3, sl, fp, ip, lr}^
d0015148:	d10e4288 	smlabble	lr, r8, r2, r4
d001514c:	1ca9480e 	stcne	8, cr4, [r9], #56	; 0x38
d0015150:	44204418 	strtmi	r4, [r0], #-1048	; 0xfffffbe8
d0015154:	fbcaf00a 	blx	0xcf2d1186
d0015158:	4652b938 			; <UNDEFINED> instruction: 0x4652b938
d001515c:	46202102 	strtmi	r2, [r0], -r2, lsl #2
d0015160:	e8bdb003 	pop	{r0, r1, ip, sp, pc}
d0015164:	f7ff4ff0 			; <UNDEFINED> instruction: 0xf7ff4ff0
d0015168:	4b0cbeef 	blmi	0xd0344d2c
d001516c:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d0015170:	d1ac2a00 			; <UNDEFINED> instruction: 0xd1ac2a00
d0015174:	447a4a0a 	ldrbtmi	r4, [sl], #-2570	; 0xfffff5f6
d0015178:	bf00e7a3 	svclt	0x0000e7a3
d001517c:	0013fe49 	andseq	pc, r3, r9, asr #28
d0015180:	0013fe48 	andseq	pc, r3, r8, asr #28
d0015184:	0013fe4b 	andseq	pc, r3, fp, asr #28
d0015188:	0013fe4f 	andseq	pc, r3, pc, asr #28
d001518c:	000113a8 	andeq	r1, r1, r8, lsr #7
d0015190:	ffffff46 			; <UNDEFINED> instruction: 0xffffff46
d0015194:	0001134c 	andeq	r1, r1, ip, asr #6
d0015198:	ffffff34 			; <UNDEFINED> instruction: 0xffffff34
d001519c:	00011298 	muleq	r1, r8, r2
d00151a0:	fffffea6 			; <UNDEFINED> instruction: 0xfffffea6

Disassembly of section .text.local_callback_declaration.constprop.0:

d0015348 <.text.local_callback_declaration.constprop.0>:
d0015348:	47f0e92d 	ldrbmi	lr, [r0, sp, lsr #18]!
d001534c:	b0904e61 	addslt	r4, r0, r1, ror #28
d0015350:	46804a61 	strmi	r4, [r0], r1, ror #20
d0015354:	2128447e 			; <UNDEFINED> instruction: 0x2128447e
d0015358:	4630447a 			; <UNDEFINED> instruction: 0x4630447a
d001535c:	fd7df7fd 	ldc2l	7, cr15, [sp, #-1012]!	; 0xfffffc0c
d0015360:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d0015364:	4a5d80b3 	bmi	0xd1775638
d0015368:	4630212a 	ldrtmi	r2, [r0], -sl, lsr #2
d001536c:	f7fd447a 			; <UNDEFINED> instruction: 0xf7fd447a
d0015370:	2800fd74 	stmdacs	r0, {r2, r4, r5, r6, r8, sl, fp, ip, sp, lr, pc}
d0015374:	80aaf000 	adchi	pc, sl, r0
d0015378:	0518f106 	ldreq	pc, [r8, #-262]	; 0xfffffefa
d001537c:	f10dac08 			; <UNDEFINED> instruction: 0xf10dac08
d0015380:	cd0f0920 	vstrgt.16	s0, [pc, #-64]	; 0xd0015348	; <UNPREDICTABLE>
d0015384:	e895c40f 	ldm	r5, {r0, r1, r2, r3, sl, lr, pc}
d0015388:	e884000f 	stm	r4, {r0, r1, r2, r3}
d001538c:	4a54000f 	bmi	0xd15153d0
d0015390:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d0015394:	447a4630 	ldrbtmi	r4, [sl], #-1584	; 0xfffff9d0
d0015398:	fd5ff7fd 	ldc2l	7, cr15, [pc, #-1012]	; 0xd0014fac
d001539c:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d00153a0:	4a508095 	bmi	0xd14355fc
d00153a4:	46302129 	ldrtmi	r2, [r0], -r9, lsr #2
d00153a8:	f7fd447a 			; <UNDEFINED> instruction: 0xf7fd447a
d00153ac:	2800fd56 	stmdacs	r0, {r1, r2, r4, r6, r8, sl, fp, ip, sp, lr, pc}
d00153b0:	808cf000 	addhi	pc, ip, r0
d00153b4:	21284a4c 			; <UNDEFINED> instruction: 0x21284a4c
d00153b8:	447a4630 	ldrbtmi	r4, [sl], #-1584	; 0xfffff9d0
d00153bc:	fd4df7fd 	stc2l	7, cr15, [sp, #-1012]	; 0xfffffc0c
d00153c0:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d00153c4:	6af38083 	bvs	0xcfcf55d8
d00153c8:	af062400 	svcge	0x00062400
d00153cc:	7f84f5b3 	svcvc	0x0084f5b3
d00153d0:	80bc9406 	adcshi	r9, ip, r6, lsl #8
d00153d4:	d14a71bc 	strhle	r7, [sl, #-28]	; 0xffffffe4
d00153d8:	2b296cf3 	blcs	0xd0a707ac
d00153dc:	4630d149 	ldrtmi	sp, [r0], -r9, asr #2
d00153e0:	fd12f7fd 	ldc2	7, cr15, [r2, #-1012]	; 0xfffffc0c
d00153e4:	21294d41 			; <UNDEFINED> instruction: 0x21294d41
d00153e8:	447d4a41 	ldrbtmi	r4, [sp], #-2625	; 0xfffff5bf
d00153ec:	4628447a 			; <UNDEFINED> instruction: 0x4628447a
d00153f0:	fd33f7fd 	ldc2	7, cr15, [r3, #-1012]!	; 0xfffffc0c
d00153f4:	d0692800 	rsble	r2, r9, r0, lsl #16
d00153f8:	9304230c 	movwls	r2, #17164	; 0x430c
d00153fc:	e913ab10 	ldmdb	r3, {r4, r8, r9, fp, sp, pc}
d0015400:	e88d000f 	stm	sp, {r0, r1, r2, r3}
d0015404:	e899000f 	ldm	r9, {r0, r1, r2, r3}
d0015408:	f7fe000f 			; <UNDEFINED> instruction: 0xf7fe000f
d001540c:	6dabfde5 	stcvs	13, cr15, [fp, #916]!	; 0x394
d0015410:	2b004606 	blcs	0xd0026c30
d0015414:	2330d15a 	teqcs	r0, #-2147483626	; 0x80000016
d0015418:	4018f88d 	andsmi	pc, r8, sp, lsl #17
d001541c:	46392207 	ldrtmi	r2, [r9], -r7, lsl #4
d0015420:	f400fb03 			; <UNDEFINED> instruction: 0xf400fb03
d0015424:	8019f88d 	andshi	pc, r9, sp, lsl #17
d0015428:	f5001928 			; <UNDEFINED> instruction: 0xf5001928
d001542c:	f20010a4 	vhadd.s8	d1, d16, d20
d0015430:	f00a6057 			; <UNDEFINED> instruction: 0xf00a6057
d0015434:	213dfa4b 	teqcs	sp, fp, asr #20	; <UNPREDICTABLE>
d0015438:	f7fd4628 			; <UNDEFINED> instruction: 0xf7fd4628
d001543c:	4601fd00 	strmi	pc, [r1], -r0, lsl #26
d0015440:	d03f2800 	eorsle	r2, pc, r0, lsl #16
d0015444:	10a4f504 	adcne	pc, r4, r4, lsl #10
d0015448:	6057f200 	subsvs	pc, r7, r0, lsl #4
d001544c:	f7ff4428 			; <UNDEFINED> instruction: 0xf7ff4428
d0015450:	4828fe01 	stmdami	r8!, {r0, r9, sl, fp, ip, sp, lr, pc}
d0015454:	22004631 	andcs	r4, r0, #51380224	; 0x3100000
d0015458:	f7ff4478 			; <UNDEFINED> instruction: 0xf7ff4478
d001545c:	4a26fcb0 	bmi	0xd09d4724
d0015460:	447a213b 	ldrbtmi	r2, [sl], #-315	; 0xfffffec5
d0015464:	e8bdb010 	pop	{r4, ip, sp, pc}
d0015468:	f7fd47f0 			; <UNDEFINED> instruction: 0xf7fd47f0
d001546c:	2b29bcf6 	blcs	0xd0a8484c
d0015470:	f8dfd0b8 			; <UNDEFINED> instruction: 0xf8dfd0b8
d0015474:	f10da088 			; <UNDEFINED> instruction: 0xf10da088
d0015478:	4d21061a 	stcmi	6, cr0, [r1, #-104]!	; 0xffffff98
d001547c:	44fa2400 	ldrbtmi	r2, [sl], #1024	; 0x400
d0015480:	4652447d 			; <UNDEFINED> instruction: 0x4652447d
d0015484:	1107f240 	tstne	r7, r0, asr #4	; <UNPREDICTABLE>
d0015488:	f7fd4628 			; <UNDEFINED> instruction: 0xf7fd4628
d001548c:	b1e8fce6 	mvnlt	pc, r6, ror #25
d0015490:	f2402300 	vcgt.s8	d18, d0, d0
d0015494:	34011101 	strcc	r1, [r1], #-257	; 0xfffffeff
d0015498:	f8064628 			; <UNDEFINED> instruction: 0xf8064628
d001549c:	f7fd3b01 			; <UNDEFINED> instruction: 0xf7fd3b01
d00154a0:	212cfcce 	smlawtcs	ip, lr, ip, pc	; <UNPREDICTABLE>
d00154a4:	b2e44628 	rsclt	r4, r4, #40, 12	; 0x2800000
d00154a8:	fcc9f7fd 	stc2l	7, cr15, [r9], {253}	; 0xfd
d00154ac:	d0992800 	addsle	r2, r9, r0, lsl #16
d00154b0:	d1e62c05 	mvnle	r2, r5, lsl #24
d00154b4:	46284913 			; <UNDEFINED> instruction: 0x46284913
d00154b8:	b0104479 	andslt	r4, r0, r9, ror r4
d00154bc:	47f0e8bd 			; <UNDEFINED> instruction: 0x47f0e8bd
d00154c0:	be72f7fa 	mrclt	7, 3, APSR_nzcv, cr2, cr10, {7}
d00154c4:	f7ff4628 			; <UNDEFINED> instruction: 0xf7ff4628
d00154c8:	e7c2fc28 	strb	pc, [r2, r8, lsr #24]	; <UNPREDICTABLE>
d00154cc:	e8bdb010 	pop	{r4, ip, sp, pc}
d00154d0:	bf0087f0 	svclt	0x000087f0
d00154d4:	000110b0 	strheq	r1, [r1], -r0
d00154d8:	fffffe48 			; <UNDEFINED> instruction: 0xfffffe48
d00154dc:	fffffe61 			; <UNDEFINED> instruction: 0xfffffe61
d00154e0:	fffffe64 			; <UNDEFINED> instruction: 0xfffffe64
d00154e4:	fffffe7a 			; <UNDEFINED> instruction: 0xfffffe7a
d00154e8:	fffffe95 			; <UNDEFINED> instruction: 0xfffffe95
d00154ec:	0001101a 	andeq	r1, r1, sl, lsl r0
d00154f0:	fffffef6 			; <UNDEFINED> instruction: 0xfffffef6
d00154f4:	00010fac 	andeq	r0, r1, ip, lsr #31
d00154f8:	fffffeaf 			; <UNDEFINED> instruction: 0xfffffeaf
d00154fc:	fffffe35 			; <UNDEFINED> instruction: 0xfffffe35
d0015500:	00010f84 	andeq	r0, r1, r4, lsl #31
d0015504:	fffffdcc 			; <UNDEFINED> instruction: 0xfffffdcc

Disassembly of section .text.branch:

d0015508 <.text.branch>:
d0015508:	f500b538 			; <UNDEFINED> instruction: 0xf500b538
d001550c:	2100338f 	smlabbcs	r0, pc, r3, r3	; <UNPREDICTABLE>
d0015510:	51b8f8d3 			; <UNDEFINED> instruction: 0x51b8f8d3
d0015514:	fba2f7ff 	blx	0xce8d351a
d0015518:	f7ff2100 			; <UNDEFINED> instruction: 0xf7ff2100
d001551c:	4628fb9f 			; <UNDEFINED> instruction: 0x4628fb9f
d0015520:	Address 0x00000000d0015520 is out of bounds.


Disassembly of section .text.branch_on_value:

d0015522 <.text.branch_on_value>:
d0015522:	460db538 			; <UNDEFINED> instruction: 0x460db538
d0015526:	5120f44f 	msrpl	CPSR_, pc, asr #8
d001552a:	fb97f7ff 	blx	0xce613530
d001552e:	1301f24d 	movwne	pc, #4685	; 0x124d	; <UNPREDICTABLE>
d0015532:	0101f24d 	tsteq	r1, sp, asr #4	; <UNPREDICTABLE>
d0015536:	bf082d00 	svclt	0x00082d00
d001553a:	f7ff4619 			; <UNDEFINED> instruction: 0xf7ff4619
d001553e:	e8bdfb8e 	pop	{r1, r2, r3, r7, r8, r9, fp, ip, sp, lr, pc}
d0015542:	f7ff4038 			; <UNDEFINED> instruction: 0xf7ff4038
d0015546:	Address 0x00000000d0015546 is out of bounds.


Disassembly of section .text.boolean:

d0015548 <.text.boolean>:
d0015548:	0301f24d 	movweq	pc, #4685	; 0x124d	; <UNPREDICTABLE>
d001554c:	2101ea43 	tstcs	r1, r3, asr #20
d0015550:	b289b510 	addlt	fp, r9, #16, 10	; 0x4000000
d0015554:	fb82f7ff 	blx	0xce0d355a
d0015558:	5100f44f 	tstpl	r0, pc, asr #8	; <UNPREDICTABLE>
d001555c:	fb7ef7ff 	blx	0xd1fd3562
d0015560:	4160f44f 	msrmi	SPSR_, pc, asr #8
d0015564:	fb7af7ff 	blx	0xd1ed356a
d0015568:	0101f242 	tsteq	r1, r2, asr #4	; <UNPREDICTABLE>
d001556c:	4010e8bd 			; <UNDEFINED> instruction: 0x4010e8bd
d0015570:	bb74f7ff 	bllt	0xd1d53574

Disassembly of section .text.prepare_call:

d0015574 <.text.prepare_call>:
d0015574:	e92d2904 	push	{r2, r8, fp, sp}
d0015578:	460d43f8 			; <UNDEFINED> instruction: 0x460d43f8
d001557c:	2504bf38 	strcs	fp, [r4, #-3896]	; 0xfffff0c8
d0015580:	460c4607 	strmi	r4, [ip], -r7, lsl #12
d0015584:	f0353d03 			; <UNDEFINED> instruction: 0xf0353d03
d0015588:	d0060501 	andle	r0, r6, r1, lsl #10
d001558c:	4130f445 	teqmi	r0, r5, asr #8	; <UNPREDICTABLE>
d0015590:	0180f041 	orreq	pc, r0, r1, asr #32
d0015594:	f7ffb289 			; <UNDEFINED> instruction: 0xf7ffb289
d0015598:	1f66fb61 	svcne	0x0066fb61
d001559c:	0904f04f 	stmdbeq	r4, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d00155a0:	0846ea4f 	stmdaeq	r6, {r0, r1, r2, r3, r6, r9, fp, sp, lr, pc}^
d00155a4:	0646eb05 	strbeq	lr, [r6], -r5, lsl #22
d00155a8:	45a1b2b6 	strmi	fp, [r1, #694]!	; 0x2b6
d00155ac:	f108d30c 			; <UNDEFINED> instruction: 0xf108d30c
d00155b0:	f04f0608 			; <UNDEFINED> instruction: 0xf04f0608
d00155b4:	442e0800 	strtmi	r0, [lr], #-2048	; 0xfffff800
d00155b8:	45a0b2b6 	strmi	fp, [r0, #694]!	; 0x2b6
d00155bc:	f1b8d026 			; <UNDEFINED> instruction: 0xf1b8d026
d00155c0:	d1120f04 	tstle	r2, r4, lsl #30
d00155c4:	e029bb1d 	eor	fp, r9, sp, lsl fp
d00155c8:	4118f446 	tstmi	r8, r6, asr #8	; <UNPREDICTABLE>
d00155cc:	f7ff4638 			; <UNDEFINED> instruction: 0xf7ff4638
d00155d0:	f1a9fb45 			; <UNDEFINED> instruction: 0xf1a9fb45
d00155d4:	3e020104 	adfccs	f0, f2, f4
d00155d8:	0901f109 	stmdbeq	r1, {r0, r3, r8, ip, sp, lr, pc}
d00155dc:	4110f441 	tstmi	r0, r1, asr #8	; <UNPREDICTABLE>
d00155e0:	b289b2b6 	addlt	fp, r9, #1610612747	; 0x6000000b
d00155e4:	fb3af7ff 	blx	0xd0ed35ea
d00155e8:	fa1fe7df 	blx	0xd080f56c
d00155ec:	4638f388 	ldrtmi	pc, [r8], -r8, lsl #7	; <UNPREDICTABLE>
d00155f0:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d00155f4:	31c3ebc3 	biccc	lr, r3, r3, asr #23
d00155f8:	0141eb06 	cmpeq	r1, r6, lsl #22
d00155fc:	2103ea41 	tstcs	r3, r1, asr #20
d0015600:	4118f441 	tstmi	r8, r1, asr #8	; <UNPREDICTABLE>
d0015604:	f7ffb289 			; <UNDEFINED> instruction: 0xf7ffb289
d0015608:	e7d6fb29 	ldrb	pc, [r6, r9, lsr #22]	; <UNPREDICTABLE>
d001560c:	eb05b125 	bl	0xd0181aa8
d0015610:	46200444 	strtmi	r0, [r0], -r4, asr #8
d0015614:	83f8e8bd 	mvnshi	lr, #12386304	; 0xbd0000
d0015618:	d0fa2c00 	rscsle	r2, sl, r0, lsl #24
d001561c:	46380061 	ldrtmi	r0, [r8], -r1, rrx
d0015620:	f4412400 	vst3.8	{d18-d20}, [r1], r0
d0015624:	b2894130 	addlt	r4, r9, #48, 2
d0015628:	fb18f7ff 	blx	0xd065362e
d001562c:	Address 0x00000000d001562c is out of bounds.


Disassembly of section .text.binary:

d001562e <.text.binary>:
d001562e:	b570292f 	ldrblt	r2, [r0, #-2351]!	; 0xfffff6d1
d0015632:	460e4604 	strmi	r4, [lr], -r4, lsl #12
d0015636:	dc0d4615 	stcle	6, cr4, [sp], {21}
d001563a:	dd102924 	vldrle.16	s4, [r0, #-72]	; 0xffffffb8	; <UNPREDICTABLE>
d001563e:	0325f1a1 	msreq	CPSR_sc, #1073741864	; 0x40000028
d0015642:	d80c2b0a 	stmdale	ip, {r1, r3, r8, r9, fp, sp}
d0015646:	f003e8df 			; <UNDEFINED> instruction: 0xf003e8df
d001564a:	0b0b3f57 	bleq	0xd02e53ae
d001564e:	0b353c0b 	bleq	0xd0d64682
d0015652:	004b0b68 	subeq	r0, fp, r8, ror #22
d0015656:	d039297c 	eorsle	r2, r9, ip, ror r9
d001565a:	295edc12 	ldmdbcs	lr, {r1, r4, sl, fp, ip, lr, pc}^
d001565e:	f244d039 	vqadd.s8	d29, d4, d25
d0015662:	46202181 	strtmi	r2, [r0], -r1, lsl #3
d0015666:	faf9f7ff 	blx	0xcfe9366a
d001566a:	7f90f5b6 	svcvc	0x0090f5b6
d001566e:	f5b6da06 			; <UNDEFINED> instruction: 0xf5b6da06
d0015672:	da547f8e 	ble	0xd15354b2
d0015676:	d0672e3c 	rsble	r2, r7, ip, lsr lr
d001567a:	d06a2e3e 	rsble	r2, sl, lr, lsr lr
d001567e:	e01d2500 	ands	r2, sp, r0, lsl #10
d0015682:	7293f46f 	addsvc	pc, r3, #1862270976	; 0x6f000000
d0015686:	2b01188b 	blcs	0xd005b8ba
d001568a:	f244d8e9 	vadd.i8	<illegal reg q14.5>, q10, <illegal reg q12.5>
d001568e:	f7ff6102 			; <UNDEFINED> instruction: 0xf7ff6102
d0015692:	f244fae4 	vpmax.s8	<illegal reg q15.5>, q10, q10
d0015696:	f7ff6108 			; <UNDEFINED> instruction: 0xf7ff6108
d001569a:	f240fae0 	vpmax.s8	<illegal reg q15.5>, q8, q8
d001569e:	429e1327 	addsmi	r1, lr, #-1677721600	; 0x9c000000
d00156a2:	f244d01a 	vqadd.s8	d29, d4, d10
d00156a6:	f24401d0 	vand	q8, q10, q0
d00156aa:	2d001310 	stccs	3, cr1, [r0, #-64]	; 0xffffffc0
d00156ae:	4619bf08 	ldrmi	fp, [r9], -r8, lsl #30
d00156b2:	f641e001 			; <UNDEFINED> instruction: 0xf641e001
d00156b6:	46200108 	strtmi	r0, [r0], -r8, lsl #2
d00156ba:	facff7ff 	blx	0xcf4136be
d00156be:	bd704628 	ldcllt	6, cr4, [r0, #-160]!	; 0xffffff60
d00156c2:	3148f244 	cmpcc	r8, r4, asr #4	; <UNPREDICTABLE>
d00156c6:	f244e7f7 	vaba.s8	q15, q10, <illegal reg q11.5>
d00156ca:	e7f40108 	ldrb	r0, [r4, r8, lsl #2]!
d00156ce:	3108f244 	tstcc	r8, r4, asr #4	; <UNPREDICTABLE>
d00156d2:	f244e7f2 	vaba.s8	q15, q10, q9
d00156d6:	e7ef0148 	strb	r0, [pc, r8, asr #2]!
d00156da:	0190f244 	orrseq	pc, r0, r4, asr #4
d00156de:	f64fe7eb 			; <UNDEFINED> instruction: 0xf64fe7eb
d00156e2:	f64f3391 			; <UNDEFINED> instruction: 0xf64f3391
d00156e6:	2d0031b1 	stfcss	f3, [r0, #-708]	; 0xfffffd3c
d00156ea:	4619bf08 	ldrmi	fp, [r9], -r8, lsl #30
d00156ee:	fab5f7ff 	blx	0xced936f2
d00156f2:	01f0f24f 	mvnseq	pc, pc, asr #4
d00156f6:	f64fe7df 			; <UNDEFINED> instruction: 0xf64fe7df
d00156fa:	f64f3391 			; <UNDEFINED> instruction: 0xf64f3391
d00156fe:	2d0031b1 	stfcss	f3, [r0, #-708]	; 0xfffffd3c
d0015702:	4619bf08 	ldrmi	fp, [r9], -r8, lsl #30
d0015706:	faa9f7ff 	blx	0xcea9370a
d001570a:	21f0f24f 	mvnscs	pc, pc, asr #4
d001570e:	faa5f7ff 	blx	0xce993712
d0015712:	3150f244 	cmpcc	r0, r4, asr #4	; <UNPREDICTABLE>
d0015716:	faa1f7ff 	blx	0xce89371a
d001571a:	2108f641 	tstcs	r8, r1, asr #12	; <UNPREDICTABLE>
d001571e:	f46fe7cb 	vld1.64	{d30}, [pc], fp
d0015722:	441e738e 	ldrmi	r7, [lr], #-910	; 0xfffffc72
d0015726:	d8032e02 	stmdale	r3, {r1, r9, sl, fp, sp}
d001572a:	f006e8df 			; <UNDEFINED> instruction: 0xf006e8df
d001572e:	00091807 	andeq	r1, r9, r7, lsl #16
d0015732:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d0015736:	ff07f7ff 			; <UNDEFINED> instruction: 0xff07f7ff
d001573a:	2101e7a0 	smlatbcs	r1, r0, r7, lr
d001573e:	2d00e7f9 	stccs	7, cr14, [r0, #-996]	; 0xfffffc1c
d0015742:	2102bf14 	tstcs	r2, r4, lsl pc
d0015746:	e7f4210a 	ldrb	r2, [r4, sl, lsl #2]!
d001574a:	bf142d00 	svclt	0x00142d00
d001574e:	210b2103 	tstcs	fp, r3, lsl #2
d0015752:	2d00e7ef 	stccs	7, cr14, [r0, #-956]	; 0xfffffc44
d0015756:	2108bf14 	tstcs	r8, r4, lsl pc
d001575a:	e7ea210c 	strb	r2, [sl, ip, lsl #2]!
d001575e:	bf142d00 	svclt	0x00142d00
d0015762:	210d2109 	tstcs	sp, r9, lsl #2
d0015766:	Address 0x00000000d0015766 is out of bounds.


Disassembly of section .text.increment_scalar.isra.0:

d00157c4 <.text.increment_scalar.isra.0>:
d00157c4:	4ff8e92d 	svcmi	0x00f8e92d
d00157c8:	a030f8dd 	ldrsbtge	pc, [r0], -sp	; <UNPREDICTABLE>
d00157cc:	460d4604 	strmi	r4, [sp], -r4, lsl #12
d00157d0:	46984617 			; <UNDEFINED> instruction: 0x46984617
d00157d4:	902cf89d 	mlals	ip, sp, r8, pc	; <UNPREDICTABLE>
d00157d8:	b038f8dd 	ldrsbtlt	pc, [r8], -sp	; <UNPREDICTABLE>
d00157dc:	ff94f7fa 			; <UNDEFINED> instruction: 0xff94f7fa
d00157e0:	da6e1e06 	ble	0xd1b9d000
d00157e4:	4629463a 			; <UNDEFINED> instruction: 0x4629463a
d00157e8:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d00157ec:	1e07ffad 	cdpne	15, 0, cr15, cr7, cr13, {5}
d00157f0:	233cdb19 	teqcs	ip, #25600	; 0x6400
d00157f4:	4307fb03 	movwmi	pc, #31491	; 0x7b03	; <UNPREDICTABLE>
d00157f8:	335ff503 	cmpcc	pc, #12582912	; 0xc00000	; <UNPREDICTABLE>
d00157fc:	53ecf893 	mvnpl	pc, #9633792	; 0x930000
d0015800:	33f0f893 	mvnscc	pc, #9633792	; 0x930000
d0015804:	d0692b00 	rsble	r2, r9, r0, lsl #22
d0015808:	b1106da0 	tstlt	r0, r0, lsr #27
d001580c:	e8bd2000 	ldmfd	sp!, {sp}
d0015810:	4b3d8ff8 	blmi	0xd0f797f8
d0015814:	f8c4447b 			; <UNDEFINED> instruction: 0xf8c4447b
d0015818:	e9c4a068 	stmib	r4, {r3, r5, r6, sp, pc}^
d001581c:	9b0a3816 	blls	0xd02a387c
d0015820:	3918e9c4 	ldmdbcc	r8, {r2, r6, r7, r8, fp, sp, lr, pc}
d0015824:	6da0e7f3 	stcvs	7, cr14, [r0, #972]!	; 0x3cc
d0015828:	d1ef2800 	mvnle	r2, r0, lsl #16
d001582c:	447b4b37 	ldrbtmi	r4, [fp], #-2871	; 0xfffff4c9
d0015830:	2200e7f1 	andcs	lr, r0, #63176704	; 0x3c40000
d0015834:	46204631 			; <UNDEFINED> instruction: 0x46204631
d0015838:	faa8f7ff 	blx	0xcea5383c
d001583c:	0f00f1bb 	svceq	0x0000f1bb
d0015840:	f24bd004 	vhadd.s8	d29, d11, d4
d0015844:	46204101 	strtmi	r4, [r0], -r1, lsl #2
d0015848:	fa08f7ff 	blx	0xd025384c
d001584c:	1323f240 	msrne	CPSR_xc, #64, 4
d0015850:	46209a0d 	strtmi	r9, [r0], -sp, lsl #20
d0015854:	bf07429a 	svclt	0x0007429a
d0015858:	0104f243 	tsteq	r4, r3, asr #4	; <UNPREDICTABLE>
d001585c:	0301f243 	movweq	pc, #4675	; 0x1243	; <UNPREDICTABLE>
d0015860:	0104f643 	tsteq	r4, r3, asr #12	; <UNPREDICTABLE>
d0015864:	0301f643 	movweq	pc, #5699	; 0x1643	; <UNPREDICTABLE>
d0015868:	bf182d0a 	svclt	0x00182d0a
d001586c:	f7ff4619 			; <UNDEFINED> instruction: 0xf7ff4619
d0015870:	2d05f9f5 	vstrcs.16	s30, [r5, #-490]	; 0xfffffe16	; <UNPREDICTABLE>
d0015874:	f24bd103 	vrhadd.s8	d29, d11, d3
d0015878:	f7ff21c0 			; <UNDEFINED> instruction: 0xf7ff21c0
d001587c:	2e00f9ef 	vmlscs.f16	s30, s1, s31	; <UNPREDICTABLE>
d0015880:	2200db12 	andcs	sp, r0, #18432	; 0x4800
d0015884:	46204631 			; <UNDEFINED> instruction: 0x46204631
d0015888:	fa99f7ff 	blx	0xce69388c
d001588c:	0f00f1bb 	svceq	0x0000f1bb
d0015890:	f64bd004 			; <UNDEFINED> instruction: 0xf64bd004
d0015894:	46204101 	strtmi	r4, [r0], -r1, lsl #2
d0015898:	f9e0f7ff 			; <UNDEFINED> instruction: 0xf9e0f7ff
d001589c:	d00e2d0a 	andle	r2, lr, sl, lsl #26
d00158a0:	42581e6b 	subsmi	r1, r8, #1712	; 0x6b0
d00158a4:	e7b24158 	sbfx	r4, r8, #2, #19
d00158a8:	463a4620 	ldrtmi	r4, [sl], -r0, lsr #12
d00158ac:	f7ff2101 			; <UNDEFINED> instruction: 0xf7ff2101
d00158b0:	f246fb4b 	vqdmulh.s<illegal width 8>	<illegal reg q15.5>, q3, <illegal reg q5.5>
d00158b4:	46200108 	strtmi	r0, [r0], -r8, lsl #2
d00158b8:	f9d0f7ff 			; <UNDEFINED> instruction: 0xf9d0f7ff
d00158bc:	2004e7e6 	andcs	lr, r4, r6, ror #15
d00158c0:	2330e7a5 	teqcs	r0, #43253760	; 0x2940000
d00158c4:	4306fb03 	movwmi	pc, #27395	; 0x6b03	; <UNPREDICTABLE>
d00158c8:	13a4f503 			; <UNDEFINED> instruction: 0x13a4f503
d00158cc:	2660f893 			; <UNDEFINED> instruction: 0x2660f893
d00158d0:	d1992a00 	orrsle	r2, r9, r0, lsl #20
d00158d4:	5655f893 			; <UNDEFINED> instruction: 0x5655f893
d00158d8:	37fff04f 	ldrbcc	pc, [pc, pc, asr #32]!	; <UNPREDICTABLE>
d00158dc:	2a111eaa 	bcs	0xd045d38c
d00158e0:	4b08d803 	blmi	0xd024b8f4
d00158e4:	07da40d3 			; <UNDEFINED> instruction: 0x07da40d3
d00158e8:	2e00d49d 	mcrcs	4, 0, sp, cr0, cr13, {4}
d00158ec:	4620daa1 	strtmi	sp, [r0], -r1, lsr #21
d00158f0:	2101463a 	tstcs	r1, sl, lsr r6
d00158f4:	fb28f7ff 	blx	0xd0a538fa
d00158f8:	0108f646 	tsteq	r8, r6, asr #12	; <UNPREDICTABLE>
d00158fc:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0015900:	e79bf9ad 	ldr	pc, [fp, sp, lsr #19]
d0015904:	0003fef5 	strdeq	pc, [r3], -r5
d0015908:	ffffff50 			; <UNDEFINED> instruction: 0xffffff50
d001590c:	ffffff63 			; <UNDEFINED> instruction: 0xffffff63

Disassembly of section .text.string_argument:

d0015960 <.text.string_argument>:
d0015960:	f2406ac3 	vpmax.s8	q11, q8, <illegal reg q1.5>
d0015964:	42931201 	addsmi	r1, r3, #268435456	; 0x10000000
d0015968:	4ff0e92d 	svcmi	0x00f0e92d
d001596c:	b0894604 	addlt	r4, r9, r4, lsl #12
d0015970:	e9d0d12d 	ldmib	r0, {r0, r2, r3, r5, r8, ip, lr, pc}^
d0015974:	92051206 	andls	r1, r5, #1610612736	; 0x60000000
d0015978:	f7fa9104 			; <UNDEFINED> instruction: 0xf7fa9104
d001597c:	1e05fee5 	cdpne	14, 0, cr15, cr5, cr5, {7}
d0015980:	9a059904 	bls	0xd017bd98
d0015984:	4943da05 	stmdbmi	r3, {r0, r2, r9, fp, ip, lr, pc}^
d0015988:	44794620 	ldrbtmi	r4, [r9], #-1568	; 0xfffff9e0
d001598c:	fc0cf7fa 	stc2	7, cr15, [ip], {250}	; 0xfa
d0015990:	4620e01a 			; <UNDEFINED> instruction: 0x4620e01a
d0015994:	feb8f7fa 	mrc2	7, 5, pc, cr8, cr10, {7}
d0015998:	daf42800 	ble	0xcfd1f9a0
d001599c:	fb03233c 	blx	0xd00de696
d00159a0:	f5034305 			; <UNDEFINED> instruction: 0xf5034305
d00159a4:	f893335f 			; <UNDEFINED> instruction: 0xf893335f
d00159a8:	2b0733ec 	blcs	0xd01e2960
d00159ac:	4620d1eb 	strtmi	sp, [r0], -fp, ror #3
d00159b0:	fa2af7fd 	blx	0xd0ad39ac
d00159b4:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d00159b8:	f7ff462a 			; <UNDEFINED> instruction: 0xf7ff462a
d00159bc:	f244fac5 	vpmax.s8	<illegal reg q15.5>, q10, <illegal reg q2.5>
d00159c0:	46206108 	strtmi	r6, [r0], -r8, lsl #2
d00159c4:	f94af7ff 			; <UNDEFINED> instruction: 0xf94af7ff
d00159c8:	e8bdb009 	pop	{r0, r3, ip, sp, pc}
d00159cc:	f5b38ff0 			; <UNDEFINED> instruction: 0xf5b38ff0
d00159d0:	d1d87f82 	bicsle	r7, r8, r2, lsl #31
d00159d4:	368ff500 	strcc	pc, [pc], r0, lsl #10
d00159d8:	81bcf8d6 			; <UNDEFINED> instruction: 0x81bcf8d6
d00159dc:	3f00f5b8 	svccc	0x0000f5b8
d00159e0:	f506d02a 			; <UNDEFINED> instruction: 0xf506d02a
d00159e4:	6a6177de 	bvs	0xd1873964
d00159e8:	0b1cf10d 	bleq	0xd0751e24
d00159ec:	f8946aa2 			; <UNDEFINED> instruction: 0xf8946aa2
d00159f0:	f8d49030 			; <UNDEFINED> instruction: 0xf8d49030
d00159f4:	e9d4a034 	ldmib	r4, {r2, r4, r5, sp, pc}^
d00159f8:	95075306 	strls	r5, [r7, #-774]	; 0xfffffcfa
d00159fc:	9807441d 	stmdals	r7, {r0, r2, r3, r4, sl, lr}
d0015a00:	d11c42a8 	tstle	ip, r8, lsr #5
d0015a04:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0015a08:	6ae3f9ff 	bvs	0xcf91420c
d0015a0c:	7f82f5b3 	svcvc	0x0082f5b3
d0015a10:	6da3d102 	stfvsd	f5, [r3, #8]!
d0015a14:	d0e62b00 	rscle	r2, r6, r0, lsl #22
d0015a18:	31bcf8d6 			; <UNDEFINED> instruction: 0x31bcf8d6
d0015a1c:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d0015a20:	44231c5a 	strtmi	r1, [r3], #-3162	; 0xfffff3a6
d0015a24:	338ff503 	orrcc	pc, pc, #12582912	; 0xc00000
d0015a28:	21bcf8c6 			; <UNDEFINED> instruction: 0x21bcf8c6
d0015a2c:	f8834642 			; <UNDEFINED> instruction: 0xf8834642
d0015a30:	f7ff11c0 			; <UNDEFINED> instruction: 0xf7ff11c0
d0015a34:	e7c7fa89 	strb	pc, [r7, r9, lsl #21]	; <UNPREDICTABLE>
d0015a38:	44794917 	ldrbtmi	r4, [r9], #-2327	; 0xfffff6e9
d0015a3c:	683be7a6 	ldmdavs	fp!, {r1, r2, r5, r7, r8, r9, sl, sp, lr, pc}
d0015a40:	f5b33301 			; <UNDEFINED> instruction: 0xf5b33301
d0015a44:	d30b3f00 	movwle	r3, #48896	; 0xbf00
d0015a48:	2b006da3 	blcs	0xd00310dc
d0015a4c:	4b13d1bc 	blmi	0xd050a144
d0015a50:	a068f8c4 	rsbge	pc, r8, r4, asr #17
d0015a54:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0015a58:	e9c42918 	stmib	r4, {r3, r4, r8, fp, sp}^
d0015a5c:	e7b33116 			; <UNDEFINED> instruction: 0xe7b33116
d0015a60:	93071c43 	movwls	r1, #31811	; 0x7c43
d0015a64:	285c7800 	ldmdacs	ip, {fp, ip, sp, lr}^
d0015a68:	464bd106 	strbmi	sp, [fp], -r6, lsl #2
d0015a6c:	95024620 	strls	r4, [r2, #-1568]	; 0xfffff9e0
d0015a70:	ab00e9cd 	blge	0xd00501ac
d0015a74:	fcfef7fa 	ldc2l	7, cr15, [lr], #1000	; 0x3e8
d0015a78:	2b006da3 	blcs	0xd003110c
d0015a7c:	683bd1a4 	ldmdavs	fp!, {r2, r5, r7, r8, ip, lr, pc}
d0015a80:	0c01f103 	stfeqd	f7, [r1], {3}
d0015a84:	f5034423 			; <UNDEFINED> instruction: 0xf5034423
d0015a88:	f8c7338f 			; <UNDEFINED> instruction: 0xf8c7338f
d0015a8c:	f883c000 			; <UNDEFINED> instruction: 0xf883c000
d0015a90:	e7b401c0 	ldr	r0, [r4, r0, asr #3]!
d0015a94:	ffffff82 			; <UNDEFINED> instruction: 0xffffff82
d0015a98:	ffffff04 			; <UNDEFINED> instruction: 0xffffff04
d0015a9c:	fffffeea 			; <UNDEFINED> instruction: 0xfffffeea

Disassembly of section .text.record_member_pointer:

d0015b30 <.text.record_member_pointer>:
d0015b30:	447b4b44 	ldrbtmi	r4, [fp], #-2884	; 0xfffff4bc
d0015b34:	4ff0e92d 	svcmi	0x00f0e92d
d0015b38:	460e4604 	strmi	r4, [lr], -r4, lsl #12
d0015b3c:	8b04ed2d 	blhi	0xd0150ff8
d0015b40:	3a10ee09 	bcc	0xd045136c
d0015b44:	9203b085 	andls	fp, r3, #133	; 0x85
d0015b48:	ee1969a3 	vnmls.f16	s12, s19, s7
d0015b4c:	f2402a10 	vpmin.s8	d18, d0, d0
d0015b50:	46201101 	strtmi	r1, [r0], -r1, lsl #2
d0015b54:	3a10ee08 	bcc	0xd045137c
d0015b58:	f8d469e3 			; <UNDEFINED> instruction: 0xf8d469e3
d0015b5c:	ee08b024 	cdp	0, 0, cr11, cr8, cr4, {1}
d0015b60:	6aa33a90 	bvs	0xce8e45a8
d0015b64:	9030f894 	mlasls	r0, r4, r8, pc	; <UNPREDICTABLE>
d0015b68:	6b639301 	blvs	0xd18fa774
d0015b6c:	f7fd9302 			; <UNDEFINED> instruction: 0xf7fd9302
d0015b70:	b330f974 	teqlt	r0, #116, 18	; 0x1d0000	; <UNPREDICTABLE>
d0015b74:	731af44f 	tstvc	sl, #1325400064	; 0x4f000000	; <UNPREDICTABLE>
d0015b78:	fb032500 	blx	0xd00def82
d0015b7c:	f507f706 			; <UNDEFINED> instruction: 0xf507f706
d0015b80:	44273867 	strtmi	r3, [r7], #-2151	; 0xfffff799
d0015b84:	78f4f508 	ldmvc	r4!, {r3, r8, sl, ip, sp, lr, pc}^
d0015b88:	3768f507 	strbcc	pc, [r8, -r7, lsl #10]!	; <UNPREDICTABLE>
d0015b8c:	0a08eb04 	beq	0xd02507a4
d0015b90:	302af897 	mlacc	sl, r7, r8, pc	; <UNPREDICTABLE>
d0015b94:	d81942ab 	ldmdale	r9, {r0, r1, r3, r5, r7, r9, lr}
d0015b98:	731af44f 	tstvc	sl, #1325400064	; 0x4f000000	; <UNPREDICTABLE>
d0015b9c:	4606fb03 	strmi	pc, [r6], -r3, lsl #22
d0015ba0:	3668f506 	strbtcc	pc, [r8], -r6, lsl #10	; <UNPREDICTABLE>
d0015ba4:	302af896 	mlacc	sl, r6, r8, pc	; <UNPREDICTABLE>
d0015ba8:	d11d42ab 	tstle	sp, fp, lsr #5
d0015bac:	b9436da3 	stmdblt	r3, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0015bb0:	447b4b25 	ldrbtmi	r4, [fp], #-2853	; 0xfffff4db
d0015bb4:	3b16e9c4 	blcc	0xd05d02cc
d0015bb8:	e9c49b01 	stmib	r4, {r0, r8, r9, fp, ip, pc}^
d0015bbc:	9b023918 	blls	0xd00a4024
d0015bc0:	b00566a3 	andlt	r6, r5, r3, lsr #13
d0015bc4:	8b04ecbd 	blhi	0xd0150ec0
d0015bc8:	8ff0e8bd 	svchi	0x00f0e8bd
d0015bcc:	3004f8da 	ldrdcc	pc, [r4], -sl
d0015bd0:	1a90ee18 	bne	0xce451438
d0015bd4:	2b24f85a 	blcs	0xd0953d44
d0015bd8:	0a10ee18 	beq	0xd0451440
d0015bdc:	fd1ef7fa 	ldc2	7, cr15, [lr, #-1000]	; 0xfffffc18
d0015be0:	d1d92800 	bicsle	r2, r9, r0, lsl #16
d0015be4:	e7d33501 	ldrb	r3, [r3, r1, lsl #10]
d0015be8:	fb032324 	blx	0xd00de882
d0015bec:	44258505 	strtmi	r8, [r5], #-1285	; 0xfffffafb
d0015bf0:	f8958c6a 			; <UNDEFINED> instruction: 0xf8958c6a
d0015bf4:	f8957020 			; <UNDEFINED> instruction: 0xf8957020
d0015bf8:	b14a6021 	cmplt	sl, r1, lsr #32
d0015bfc:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d0015c00:	f7ff0092 			; <UNDEFINED> instruction: 0xf7ff0092
d0015c04:	f44ff84b 	vst2.16	{d31-d32}, [pc], fp
d0015c08:	462051c2 	strtmi	r5, [r0], -r2, asr #3
d0015c0c:	f826f7ff 			; <UNDEFINED> instruction: 0xf826f7ff
d0015c10:	d0002fff 	strdle	r2, [r0], -pc	; <UNPREDICTABLE>
d0015c14:	6da3b12e 	stfvsd	f3, [r3, #184]!	; 0xb8
d0015c18:	d1d22b00 	bicsle	r2, r2, r0, lsl #22
d0015c1c:	447b4b0b 	ldrbtmi	r4, [fp], #-2827	; 0xfffff4f5
d0015c20:	212ee7c8 	smlawtcs	lr, r8, r7, lr
d0015c24:	463e4620 	ldrtmi	r4, [lr], -r0, lsr #12
d0015c28:	f909f7fd 			; <UNDEFINED> instruction: 0xf909f7fd
d0015c2c:	d18b2800 	orrle	r2, fp, r0, lsl #16
d0015c30:	42bb9b03 	adcsmi	r9, fp, #3072	; 0xc00
d0015c34:	6da3d0c5 	stcvs	0, cr13, [r3, #788]!	; 0x314
d0015c38:	d1c22b00 	bicle	r2, r2, r0, lsl #22
d0015c3c:	447b4b04 	ldrbtmi	r4, [fp], #-2820	; 0xfffff4fc
d0015c40:	bf00e7b8 	svclt	0x0000e7b8
d0015c44:	ffffff6a 			; <UNDEFINED> instruction: 0xffffff6a
d0015c48:	ffffff08 			; <UNDEFINED> instruction: 0xffffff08
d0015c4c:	fffffeb7 			; <UNDEFINED> instruction: 0xfffffeb7
d0015c50:	fffffebf 			; <UNDEFINED> instruction: 0xfffffebf

Disassembly of section .text.record_pointer_field_address:

d0015d08 <.text.record_pointer_field_address>:
d0015d08:	447b4b4f 	ldrbtmi	r4, [fp], #-2895	; 0xfffff4b1
d0015d0c:	4ff0e92d 	svcmi	0x00f0e92d
d0015d10:	460d4604 	strmi	r4, [sp], -r4, lsl #12
d0015d14:	8b04ed2d 	blhi	0xd01511d0
d0015d18:	3a10ee09 	bcc	0xd0451544
d0015d1c:	9203b085 	andls	fp, r3, #133	; 0x85
d0015d20:	ee1969a3 	vnmls.f16	s12, s19, s7
d0015d24:	f2402a10 	vpmin.s8	d18, d0, d0
d0015d28:	46201101 	strtmi	r1, [r0], -r1, lsl #2
d0015d2c:	3a10ee08 	bcc	0xd0451554
d0015d30:	f8d469e3 			; <UNDEFINED> instruction: 0xf8d469e3
d0015d34:	ee08a024 	cdp	0, 0, cr10, cr8, cr4, {1}
d0015d38:	6b633a90 	blvs	0xd18e4780
d0015d3c:	9028f8d4 	ldrdls	pc, [r8], -r4	; <UNPREDICTABLE>
d0015d40:	8030f894 	mlashi	r0, r4, r8, pc	; <UNPREDICTABLE>
d0015d44:	f7fd9301 			; <UNDEFINED> instruction: 0xf7fd9301
d0015d48:	b330f888 	teqlt	r0, #136, 16	; 0x880000	; <UNPREDICTABLE>
d0015d4c:	731af44f 	tstvc	sl, #1325400064	; 0x4f000000	; <UNPREDICTABLE>
d0015d50:	fb032600 	blx	0xd00df55a
d0015d54:	f507f705 			; <UNDEFINED> instruction: 0xf507f705
d0015d58:	44273b67 	strtmi	r3, [r7], #-2919	; 0xfffff499
d0015d5c:	7bf4f50b 	blvc	0xcfd53190
d0015d60:	3768f507 	strbcc	pc, [r8, -r7, lsl #10]!	; <UNPREDICTABLE>
d0015d64:	030beb04 	movweq	lr, #47876	; 0xbb04
d0015d68:	f8979302 			; <UNDEFINED> instruction: 0xf8979302
d0015d6c:	42b3302a 	adcsmi	r3, r3, #42	; 0x2a
d0015d70:	f44fd818 	vst2.8	{d29-d30}, [pc :64], r8
d0015d74:	fb03731a 	blx	0xd00f29e6
d0015d78:	f5054505 			; <UNDEFINED> instruction: 0xf5054505
d0015d7c:	f8953568 			; <UNDEFINED> instruction: 0xf8953568
d0015d80:	42b3302a 	adcsmi	r3, r3, #42	; 0x2a
d0015d84:	6da3d11e 	stfvsd	f5, [r3, #120]!	; 0x78
d0015d88:	4b30b93b 	blmi	0xd0c4427c
d0015d8c:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0015d90:	9b013a16 	blls	0xd00645f0
d0015d94:	9818e9c4 	ldmdals	r8, {r2, r6, r7, r8, fp, sp, lr, pc}
d0015d98:	b00566a3 	andlt	r6, r5, r3, lsr #13
d0015d9c:	8b04ecbd 	blhi	0xd0151098
d0015da0:	8ff0e8bd 	svchi	0x00f0e8bd
d0015da4:	ee189902 	vnmls.f16	s18, s16, s4
d0015da8:	9b020a10 	blls	0xd00985f0
d0015dac:	2b24f851 	blcs	0xd0953ef8
d0015db0:	9102685b 	tstls	r2, fp, asr r8
d0015db4:	1a90ee18 	bne	0xce45161c
d0015db8:	fc30f7fa 	ldc2	7, cr15, [r0], #-1000	; 0xfffffc18
d0015dbc:	d1d82800 	bicsle	r2, r8, r0, lsl #16
d0015dc0:	e7d23601 	ldrb	r3, [r2, r1, lsl #12]
d0015dc4:	fb032324 	blx	0xd00dea5e
d0015dc8:	4426b606 	strtmi	fp, [r6], #-1542	; 0xfffff9fa
d0015dcc:	f8968c72 			; <UNDEFINED> instruction: 0xf8968c72
d0015dd0:	f8965020 			; <UNDEFINED> instruction: 0xf8965020
d0015dd4:	b14a7021 	cmplt	sl, r1, lsr #32
d0015dd8:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d0015ddc:	f7fe0092 			; <UNDEFINED> instruction: 0xf7fe0092
d0015de0:	f44fff5d 			; <UNDEFINED> instruction: 0xf44fff5d
d0015de4:	462051c2 	strtmi	r5, [r0], -r2, asr #3
d0015de8:	ff38f7fe 			; <UNDEFINED> instruction: 0xff38f7fe
d0015dec:	7191f44f 	orrsvc	pc, r1, pc, asr #8
d0015df0:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0015df4:	b170f824 	cmnlt	r0, r4, lsr #16	; <UNPREDICTABLE>
d0015df8:	2dffb10f 	ldfcsp	f3, [pc, #60]!	; 0xd0015e3c
d0015dfc:	6da3d105 	stfvsd	f5, [r3, #20]!
d0015e00:	d1ca2b00 	bicle	r2, sl, r0, lsl #22
d0015e04:	447b4b12 	ldrbtmi	r4, [fp], #-2834	; 0xfffff4ee
d0015e08:	f44fe7c1 	vst1.64	{d30}, [pc], r1
d0015e0c:	462041d0 			; <UNDEFINED> instruction: 0x462041d0
d0015e10:	ff24f7fe 			; <UNDEFINED> instruction: 0xff24f7fe
d0015e14:	212ee784 	smlawbcs	lr, r4, r7, lr
d0015e18:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0015e1c:	b148f810 	cmplt	r8, r0, lsl r8	; <UNPREDICTABLE>
d0015e20:	2dffb917 			; <UNDEFINED> instruction: 0x2dffb917
d0015e24:	af7cf47f 	svcge	0x007cf47f
d0015e28:	2b006da3 	blcs	0xd00314bc
d0015e2c:	4b09d1b5 	blmi	0xd028a508
d0015e30:	e7ac447b 			; <UNDEFINED> instruction: 0xe7ac447b
d0015e34:	9b03b117 	blls	0xd0102298
d0015e38:	d0ae429d 	umlalle	r4, lr, sp, r2
d0015e3c:	2b006da3 	blcs	0xd00314d0
d0015e40:	4b05d1ab 	blmi	0xd018a4f4
d0015e44:	e7a2447b 			; <UNDEFINED> instruction: 0xe7a2447b
d0015e48:	ffffff46 			; <UNDEFINED> instruction: 0xffffff46
d0015e4c:	fffffee1 			; <UNDEFINED> instruction: 0xfffffee1
d0015e50:	fffffe8f 			; <UNDEFINED> instruction: 0xfffffe8f
d0015e54:	fffffe85 			; <UNDEFINED> instruction: 0xfffffe85
d0015e58:	fffffe92 			; <UNDEFINED> instruction: 0xfffffe92

Disassembly of section .text.struct_double_pointer_value:

d0015f3c <.text.struct_double_pointer_value>:
d0015f3c:	4ff7e92d 	svcmi	0x00f7e92d
d0015f40:	460d4604 	strmi	r4, [sp], -r4, lsl #12
d0015f44:	fef0f7fe 	mrc2	7, 7, pc, cr0, cr14, {7}
d0015f48:	bb404680 	bllt	0xd1027950
d0015f4c:	46202126 	strtmi	r2, [r0], -r6, lsr #2
d0015f50:	ff75f7fc 			; <UNDEFINED> instruction: 0xff75f7fc
d0015f54:	4a3c6a63 	bmi	0xd0f308e8
d0015f58:	93004683 	movwls	r4, #1667	; 0x683
d0015f5c:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d0015f60:	447a6aa3 	ldrbtmi	r6, [sl], #-2723	; 0xfffff55d
d0015f64:	f8944620 			; <UNDEFINED> instruction: 0xf8944620
d0015f68:	6b669030 	blvs	0xd19ba030
d0015f6c:	e9d49301 	ldmib	r4, {r0, r8, r9, ip, pc}^
d0015f70:	f7fc7a06 			; <UNDEFINED> instruction: 0xf7fc7a06
d0015f74:	b190ff72 	orrslt	pc, r0, r2, ror pc	; <UNPREDICTABLE>
d0015f78:	46394652 			; <UNDEFINED> instruction: 0x46394652
d0015f7c:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0015f80:	f1b0fbc3 			; <UNDEFINED> instruction: 0xf1b0fbc3
d0015f84:	da0d0a00 	ble	0xd035878c
d0015f88:	b9436da3 	stmdblt	r3, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0015f8c:	447b4b2f 	ldrbtmi	r4, [fp], #-2863	; 0xfffff4d1
d0015f90:	9b0065a3 	blls	0xd002f624
d0015f94:	65e366a6 	strbvs	r6, [r3, #1702]!	; 0x6a6
d0015f98:	e9c49b01 	stmib	r4, {r0, r8, r9, fp, ip, pc}^
d0015f9c:	b0033918 	andlt	r3, r3, r8, lsl r9
d0015fa0:	8ff0e8bd 	svchi	0x00f0e8bd
d0015fa4:	fb022230 	blx	0xd009e86e
d0015fa8:	f502420a 			; <UNDEFINED> instruction: 0xf502420a
d0015fac:	f89212a4 			; <UNDEFINED> instruction: 0xf89212a4
d0015fb0:	f8927656 			; <UNDEFINED> instruction: 0xf8927656
d0015fb4:	f1bb2655 			; <UNDEFINED> instruction: 0xf1bb2655
d0015fb8:	d0320f00 	eorsle	r0, r2, r0, lsl #30
d0015fbc:	d1212a0e 			; <UNDEFINED> instruction: 0xd1212a0e
d0015fc0:	7191f44f 	orrsvc	pc, r1, pc, asr #8
d0015fc4:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0015fc8:	b160ff3a 	msrlt	SPSR_irq, sl
d0015fcc:	46514642 	ldrbmi	r4, [r1], -r2, asr #12
d0015fd0:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0015fd4:	462afedb 			; <UNDEFINED> instruction: 0x462afedb
d0015fd8:	46204639 			; <UNDEFINED> instruction: 0x46204639
d0015fdc:	e8bdb003 	pop	{r0, r1, ip, sp, pc}
d0015fe0:	f7ff4ff0 			; <UNDEFINED> instruction: 0xf7ff4ff0
d0015fe4:	42afbe91 	adcmi	fp, pc, #2320	; 0x910
d0015fe8:	4651d106 	ldrbmi	sp, [r1], -r6, lsl #2
d0015fec:	b0034620 	andlt	r4, r3, r0, lsr #12
d0015ff0:	4ff0e8bd 	svcmi	0x00f0e8bd
d0015ff4:	befcf7fe 	mrclt	7, 7, APSR_nzcv, cr12, cr14, {7}
d0015ff8:	2b006da3 	blcs	0xd003168c
d0015ffc:	4b14d1cf 	blmi	0xd054a740
d0016000:	e7c5447b 			; <UNDEFINED> instruction: 0xe7c5447b
d0016004:	d1182a0d 	tstle	r8, sp, lsl #20
d0016008:	212e4a12 			; <UNDEFINED> instruction: 0x212e4a12
d001600c:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d0016010:	ff23f7fc 			; <UNDEFINED> instruction: 0xff23f7fc
d0016014:	d0c22800 	sbcle	r2, r2, r0, lsl #16
d0016018:	46204651 			; <UNDEFINED> instruction: 0x46204651
d001601c:	fee8f7fe 	mcr2	7, 7, pc, cr8, cr14, {7}	; <UNPREDICTABLE>
d0016020:	2a12e7d9 	bcs	0xd04cff8c
d0016024:	42afd109 	adcmi	sp, pc, #1073741826	; 0x40000002
d0016028:	465ad107 	ldrbmi	sp, [sl], -r7, lsl #2
d001602c:	46204651 			; <UNDEFINED> instruction: 0x46204651
d0016030:	e8bdb003 	pop	{r0, r1, ip, sp, pc}
d0016034:	f7fe4ff0 			; <UNDEFINED> instruction: 0xf7fe4ff0
d0016038:	6da3bea9 	stcvs	14, cr11, [r3, #676]!	; 0x2a4
d001603c:	d1ae2b00 			; <UNDEFINED> instruction: 0xd1ae2b00
d0016040:	447b4b05 	ldrbtmi	r4, [fp], #-2821	; 0xfffff4fb
d0016044:	bf00e7a4 	svclt	0x0000e7a4
d0016048:	fffffef6 			; <UNDEFINED> instruction: 0xfffffef6
d001604c:	fffffef9 			; <UNDEFINED> instruction: 0xfffffef9
d0016050:	fffffeb7 			; <UNDEFINED> instruction: 0xfffffeb7
d0016054:	fffffed1 			; <UNDEFINED> instruction: 0xfffffed1
d0016058:	fffffeb8 			; <UNDEFINED> instruction: 0xfffffeb8

Disassembly of section .text.copy_record.constprop.0:

d001605c <.text.copy_record.constprop.0>:
d001605c:	4606b570 			; <UNDEFINED> instruction: 0x4606b570
d0016060:	2500480c 	strcs	r4, [r0, #-2060]	; 0xfffff7f4
d0016064:	42b54478 	adcsmi	r4, r5, #120, 8	; 0x78000000
d0016068:	bd70d100 	ldfltp	f5, [r0, #-0]
d001606c:	f64f00ac 			; <UNDEFINED> instruction: 0xf64f00ac
d0016070:	f7fe01d0 			; <UNDEFINED> instruction: 0xf7fe01d0
d0016074:	3501fdf3 	strcc	pc, [r1, #-3571]	; 0xfffff20d
d0016078:	5400f444 	strpl	pc, [r0], #-1092	; 0xfffffbbc
d001607c:	4621b2a4 	strtmi	fp, [r1], -r4, lsr #5
d0016080:	fdecf7fe 	stc2l	7, cr15, [ip, #1016]!	; 0x3f8
d0016084:	01c1f64f 	biceq	pc, r1, pc, asr #12
d0016088:	fde8f7fe 	stc2l	7, cr15, [r8, #1016]!	; 0x3f8
d001608c:	f7fe4621 			; <UNDEFINED> instruction: 0xf7fe4621
d0016090:	e7e8fde5 	strb	pc, [r8, r5, ror #27]!	; <UNPREDICTABLE>
d0016094:	000103a0 	andeq	r0, r1, r0, lsr #7

Disassembly of section .text.patch_branch.isra.0.part.0:

d0016098 <.text.patch_branch.isra.0.part.0>:
d0016098:	2a001a09 	bcs	0xd001c8c4
d001609c:	0104f1a1 	smlatbeq	r4, r1, r1, pc	; <UNPREDICTABLE>
d00160a0:	f44fbf14 			; <UNDEFINED> instruction: 0xf44fbf14
d00160a4:	f44f4250 	vst1.16	{d20-d23}, [pc :64], r0
d00160a8:	b5f04210 	ldrblt	r4, [r0, #528]!	; 0x210
d00160ac:	6600f3c1 	strvs	pc, [r0], -r1, asr #7
d00160b0:	3409f3c1 	strcc	pc, [r9], #-961	; 0xfffffc3f
d00160b4:	ea864f11 	b	0xce1a9d00
d00160b8:	ea4453d1 	b	0xd112b004
d00160bc:	447f2486 	ldrbtmi	r2, [pc], #-1158	; 0xd00160c4
d00160c0:	f44443db 	vst2.<illegal width 64>	{d20-d23}, [r4 :64], fp
d00160c4:	f0034470 			; <UNDEFINED> instruction: 0xf0034470
d00160c8:	ea860501 	b	0xce1974d4
d00160cc:	f3c15391 	vrsra.u64	d21, d1, #63
d00160d0:	183e014a 	ldmdane	lr!, {r1, r3, r6, r8}
d00160d4:	f88643db 			; <UNDEFINED> instruction: 0xf88643db
d00160d8:	0a244040 	beq	0xd09261e0
d00160dc:	0301f003 	movweq	pc, #4099	; 0x1003	; <UNPREDICTABLE>
d00160e0:	4041f886 	submi	pc, r1, r6, lsl #17
d00160e4:	ea4302db 	b	0xd10d6c58
d00160e8:	430b3345 	movwmi	r3, #45893	; 0xb345
d00160ec:	f8864313 			; <UNDEFINED> instruction: 0xf8864313
d00160f0:	0a1b3042 	beq	0xd06e2200
d00160f4:	3043f886 	subcc	pc, r3, r6, lsl #17
d00160f8:	bf00bdf0 	svclt	0x0000bdf0
d00160fc:	0015b5e6 	andseq	fp, r5, r6, ror #11

Disassembly of section .text.patch_branch.isra.0:

d0016100 <.text.patch_branch.isra.0>:
d0016100:	4604b410 			; <UNDEFINED> instruction: 0x4604b410
d0016104:	46114608 	ldrmi	r4, [r1], -r8, lsl #12
d0016108:	b91c461a 	ldmdblt	ip, {r1, r3, r4, r9, sl, lr}
d001610c:	4b04f85d 	blmi	0xd0154288
d0016110:	bfc2f7ff 	svclt	0x00c2f7ff
d0016114:	4b04f85d 	blmi	0xd0154290
d0016118:	Address 0x00000000d0016118 is out of bounds.


Disassembly of section .text.expression:

d001632c <.text.expression>:
d001632c:	4ff0e92d 	svcmi	0x00f0e92d
d0016330:	46046a03 	strmi	r6, [r4], -r3, lsl #20
d0016334:	b024f8d0 	ldrdlt	pc, [r4], -r0	; <UNPREDICTABLE>
d0016338:	9030f890 	mlasls	r0, r0, r8, pc	; <UNPREDICTABLE>
d001633c:	8b06ed2d 	blhi	0xd01d17f8
d0016340:	9203b08d 	andls	fp, r3, #141	; 0x8d
d0016344:	12a4f500 	adcne	pc, r4, #0, 10
d0016348:	f5029306 			; <UNDEFINED> instruction: 0xf5029306
d001634c:	91045292 			; <UNDEFINED> instruction: 0x91045292
d0016350:	a30ae9d0 	movwge	lr, #43472	; 0xa9d0
d0016354:	6b439307 	blvs	0xd10faf78
d0016358:	68139301 	ldmdavs	r3, {r0, r8, r9, ip, pc}
d001635c:	2b203301 	blcs	0xd0822f68
d0016360:	d9046013 	stmdble	r4, {r0, r1, r4, sp, lr}
d0016364:	15d8f8df 	ldrbne	pc, [r8, #2271]	; 0x8df	; <UNPREDICTABLE>
d0016368:	f7f94479 			; <UNDEFINED> instruction: 0xf7f94479
d001636c:	9b03ff1d 	blls	0xd0115fe8
d0016370:	42411ed8 	submi	r1, r1, #216, 28	; 0xd80
d0016374:	46204141 	strtmi	r4, [r0], -r1, asr #2
d0016378:	fbf8f002 	blx	0xcfe5238a
d001637c:	35c4f8df 	strbcc	pc, [r4, #2271]	; 0x8df	; <UNPREDICTABLE>
d0016380:	447b4605 	ldrbtmi	r4, [fp], #-1541	; 0xfffff9fb
d0016384:	f8df9308 			; <UNDEFINED> instruction: 0xf8df9308
d0016388:	447b35c0 	ldrbtmi	r3, [fp], #-1472	; 0xfffffa40
d001638c:	6da69309 	stcvs	3, cr9, [r6, #36]!	; 0x24
d0016390:	6ae7b9b6 	bvs	0xcfa04a70
d0016394:	f0002f7c 			; <UNDEFINED> instruction: 0xf0002f7c
d0016398:	f3008163 	vrhadd.u8	q4, q0, <illegal reg q9.5>
d001639c:	2f2f8132 	svccs	0x002f8132
d00163a0:	8124f300 	msrhi	LR_abt, r0
d00163a4:	f3002f24 	vpmax.f32	d2, d0, d20
d00163a8:	9b048111 	blls	0xd01367f4
d00163ac:	dc0742b3 	sfmle	f4, 4, [r7], {179}	; 0xb3
d00163b0:	d1362d02 	teqle	r6, r2, lsl #26
d00163b4:	1594f8df 	ldrne	pc, [r4, #2271]	; 0x8df
d00163b8:	44794620 	ldrbtmi	r4, [r9], #-1568	; 0xfffff9e0
d00163bc:	fef4f7f9 	mrc2	7, 7, pc, cr4, cr9, {7}
d00163c0:	b9be6da6 	ldmiblt	lr!, {r1, r2, r5, r7, r8, sl, fp, sp, lr}
d00163c4:	2b019b04 	blcs	0xd007cfdc
d00163c8:	213fd114 	teqcs	pc, r4, lsl r1	; <UNPREDICTABLE>
d00163cc:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d00163d0:	b178fd36 	cmnlt	r8, r6, lsr sp	; <UNPREDICTABLE>
d00163d4:	0304f025 	movweq	pc, #16421	; 0x4025	; <UNPREDICTABLE>
d00163d8:	f0402b02 			; <UNDEFINED> instruction: 0xf0402b02
d00163dc:	6da38149 	stfvsd	f0, [r3, #292]!	; 0x124
d00163e0:	f8dfb943 			; <UNDEFINED> instruction: 0xf8dfb943
d00163e4:	447b356c 	ldrbtmi	r3, [fp], #-1388	; 0xfffffa94
d00163e8:	3b16e9c4 	blcc	0xd05d0b00
d00163ec:	e9c49b01 	stmib	r4, {r0, r8, r9, fp, ip, pc}^
d00163f0:	66a3a918 	ssatvs	sl, #4, r8, lsl #18
d00163f4:	3b019b03 	blcc	0xd007d008
d00163f8:	f2002b01 	vqdmulh.s<illegal width 8>	d2, d0, d1
d00163fc:	2d02822a 	sfmcs	f0, 1, [r2, #-168]	; 0xffffff58
d0016400:	6da3d10a 	stfvsd	f5, [r3, #40]!	; 0x28
d0016404:	f8dfb943 			; <UNDEFINED> instruction: 0xf8dfb943
d0016408:	447b354c 	ldrbtmi	r3, [fp], #-1356	; 0xfffffab4
d001640c:	3b16e9c4 	blcc	0xd05d0b24
d0016410:	e9c49b01 	stmib	r4, {r0, r8, r9, fp, ip, pc}^
d0016414:	66a3a918 	ssatvs	sl, #4, r8, lsl #18
d0016418:	2b019b03 	blcs	0xd007d02c
d001641c:	8229f040 	eorhi	pc, r9, #64	; 0x40
d0016420:	4620e21a 			; <UNDEFINED> instruction: 0x4620e21a
d0016424:	f7fc3601 			; <UNDEFINED> instruction: 0xf7fc3601
d0016428:	f5a7fcef 			; <UNDEFINED> instruction: 0xf5a7fcef
d001642c:	2b017390 	blcs	0xd0073274
d0016430:	f240d82f 	vadd.i8	d29, d0, d31
d0016434:	46201521 	strtmi	r1, [r0], -r1, lsr #10
d0016438:	42551b7a 	subsmi	r1, r5, #124928	; 0x1e800
d001643c:	46294155 			; <UNDEFINED> instruction: 0x46294155
d0016440:	f86ff7ff 			; <UNDEFINED> instruction: 0xf86ff7ff
d0016444:	46312202 	ldrtmi	r2, [r1], -r2, lsl #4
d0016448:	46204607 	strtmi	r4, [r0], -r7, lsl #12
d001644c:	368ff504 	strcc	pc, [pc], r4, lsl #10
d0016450:	ff6cf7ff 			; <UNDEFINED> instruction: 0xff6cf7ff
d0016454:	f44f4620 	vst1.8	{d20-d22}, [pc :128], r0
d0016458:	f7fe5120 			; <UNDEFINED> instruction: 0xf7fe5120
d001645c:	2101fbff 	strdcs	pc, [r1, -pc]
d0016460:	f872f7ff 			; <UNDEFINED> instruction: 0xf872f7ff
d0016464:	f850f7ff 			; <UNDEFINED> instruction: 0xf850f7ff
d0016468:	f8d62300 			; <UNDEFINED> instruction: 0xf8d62300
d001646c:	468021b8 			; <UNDEFINED> instruction: 0x468021b8
d0016470:	6da04639 	stcvs	6, cr4, [r0, #228]!	; 0xe4
d0016474:	fe44f7ff 	mcr2	7, 2, pc, cr4, cr15, {7}	; <UNPREDICTABLE>
d0016478:	46204629 	strtmi	r4, [r0], -r9, lsr #12
d001647c:	fc4df7fe 	mcrr2	7, 15, pc, sp, cr14	; <UNPREDICTABLE>
d0016480:	f8d62300 			; <UNDEFINED> instruction: 0xf8d62300
d0016484:	464121b8 			; <UNDEFINED> instruction: 0x464121b8
d0016488:	f7ff6da0 			; <UNDEFINED> instruction: 0xf7ff6da0
d001648c:	2500fe39 	strcs	pc, [r0, #-3641]	; 0xfffff1c7
d0016490:	f5a7e77d 			; <UNDEFINED> instruction: 0xf5a7e77d
d0016494:	2d03738e 	stccs	3, cr7, [r3, #-568]	; 0xfffffdc8
d0016498:	d0029302 	andle	r9, r2, r2, lsl #6
d001649c:	2b021f6b 	blcs	0xd009e250
d00164a0:	9b02d80f 	blls	0xd00cc4e4
d00164a4:	d90c2b01 	stmdble	ip, {r0, r8, r9, fp, sp}
d00164a8:	2b006da3 	blcs	0xd0031b3c
d00164ac:	f8dfd188 			; <UNDEFINED> instruction: 0xf8dfd188
d00164b0:	447b34a8 	ldrbtmi	r3, [fp], #-1192	; 0xfffffb58
d00164b4:	3b16e9c4 	blcc	0xd05d0bcc
d00164b8:	e9c49b01 	stmib	r4, {r0, r8, r9, fp, ip, pc}^
d00164bc:	66a3a918 	ssatvs	sl, #4, r8, lsl #18
d00164c0:	f24be77e 	vaba.s8	q15, <illegal reg q5.5>, q15
d00164c4:	46204103 	strtmi	r4, [r0], -r3, lsl #2
d00164c8:	fbc8f7fe 	blx	0xcf2544ca
d00164cc:	46316a23 	ldrtmi	r6, [r1], -r3, lsr #20
d00164d0:	93052202 	movwls	r2, #20994	; 0x5202
d00164d4:	802cf8d4 	ldrdhi	pc, [ip], -r4	; <UNPREDICTABLE>
d00164d8:	ff28f7ff 			; <UNDEFINED> instruction: 0xff28f7ff
d00164dc:	4106f64b 	tstmi	r6, fp, asr #12	; <UNPREDICTABLE>
d00164e0:	46204606 	strtmi	r4, [r0], -r6, lsl #12
d00164e4:	fbbaf7fe 	blx	0xceed44e6
d00164e8:	f0002d04 			; <UNDEFINED> instruction: 0xf0002d04
d00164ec:	2e0481f3 	mcrcs	1, 0, r8, cr4, cr3, {7}
d00164f0:	2f2bd110 	svccs	0x002bd110
d00164f4:	8203f040 	andhi	pc, r3, #64	; 0x40
d00164f8:	2b011eeb 	blcs	0xd005e0ac
d00164fc:	8202f240 	andhi	pc, r2, #64, 4
d0016500:	46202189 	strtmi	r2, [r0], -r9, lsl #3
d0016504:	fbaaf7fe 	blx	0xcead4506
d0016508:	0108f641 	tsteq	r8, r1, asr #12	; <UNPREDICTABLE>
d001650c:	f7fe2504 			; <UNDEFINED> instruction: 0xf7fe2504
d0016510:	e73cfba5 	ldr	pc, [ip, -r5, lsr #23]!
d0016514:	d0072d03 	andle	r2, r7, r3, lsl #26
d0016518:	d0052e03 	andle	r2, r5, r3, lsl #28
d001651c:	2b021f6b 	blcs	0xd009e2d0
d0016520:	1f73d902 	svcne	0x0073d902
d0016524:	d8392b02 	ldmdale	r9!, {r1, r8, r9, fp, sp}
d0016528:	f5a89b07 			; <UNDEFINED> instruction: 0xf5a89b07
d001652c:	f5a37881 			; <UNDEFINED> instruction: 0xf5a37881
d0016530:	2b017381 	blcs	0xd007333c
d0016534:	9b06bf97 	blls	0xd01c6398
d0016538:	fab32300 	blx	0xcecdf140
d001653c:	095bf383 	ldmdbeq	fp, {r0, r1, r7, r8, r9, ip, sp, lr, pc}^
d0016540:	0f01f1b8 	svceq	0x0001f1b8
d0016544:	9a05bf97 	bls	0xd01863a8
d0016548:	fab22200 	blx	0xcec9ed50
d001654c:	0952f282 	ldmdbeq	r2, {r1, r7, r9, ip, sp, lr, pc}^
d0016550:	d0092d04 	andle	r2, r9, r4, lsl #26
d0016554:	f0402d03 			; <UNDEFINED> instruction: 0xf0402d03
d0016558:	1ef381ba 	mrcne	1, 7, r8, cr3, cr10, {5}
d001655c:	d80c2b01 	stmdale	ip, {r0, r8, r9, fp, sp}
d0016560:	2b019b02 	blcs	0xd007d170
d0016564:	e013d80b 	ands	sp, r3, fp, lsl #16
d0016568:	29011ef1 	stmdbcs	r1, {r0, r4, r5, r6, r7, r9, sl, fp, ip}
d001656c:	2e00d9f8 			; <UNDEFINED> instruction: 0x2e00d9f8
d0016570:	81a0f040 	asrhi	pc, r0, #32	; <UNPREDICTABLE>
d0016574:	d1f32a00 	mvnsle	r2, r0, lsl #20
d0016578:	2e00e001 	cdpcs	0, 0, cr14, cr0, cr1, {0}
d001657c:	6da3d0fa 	stcvs	0, cr13, [r3, #1000]!	; 0x3e8
d0016580:	9b08b933 	blls	0xd0244a54
d0016584:	3b16e9c4 	blcc	0xd05d0c9c
d0016588:	e9c49b01 	stmib	r4, {r0, r8, r9, fp, ip, pc}^
d001658c:	66a3a918 	ssatvs	sl, #4, r8, lsl #18
d0016590:	46392201 	ldrtmi	r2, [r9], -r1, lsl #4
d0016594:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0016598:	e778f84a 	ldrb	pc, [r8, -sl, asr #16]!	; <UNPREDICTABLE>
d001659c:	7393f46f 	orrsvc	pc, r3, #1862270976	; 0x6f000000
d00165a0:	2b0118fb 	blcs	0xd005c994
d00165a4:	2d01d80c 	stccs	8, cr13, [r1, #-48]	; 0xffffffd0
d00165a8:	2500bf14 	strcs	fp, [r0, #-3860]	; 0xfffff0ec
d00165ac:	462a2501 	strtmi	r2, [sl], -r1, lsl #10
d00165b0:	46204639 			; <UNDEFINED> instruction: 0x46204639
d00165b4:	f83bf7ff 			; <UNDEFINED> instruction: 0xf83bf7ff
d00165b8:	bf181e05 	svclt	0x00181e05
d00165bc:	e6e62501 	strbt	r2, [r6], r1, lsl #10
d00165c0:	d0f42d01 	rscsle	r2, r4, r1, lsl #26
d00165c4:	e7ef2e01 	strb	r2, [pc, r1, lsl #28]!
d00165c8:	e6ee2602 	strbt	r2, [lr], r2, lsl #12
d00165cc:	0325f1a7 	msreq	CPSR_sc, #-1073741783	; 0xc0000029
d00165d0:	d8092b0a 	stmdale	r9, {r1, r3, r8, r9, fp, sp}
d00165d4:	f003e8df 			; <UNDEFINED> instruction: 0xf003e8df
d00165d8:	08084842 	stmdaeq	r8, {r1, r6, fp, lr}
d00165dc:	08064208 	stmdaeq	r6, {r3, r9, lr}
d00165e0:	00420806 	subeq	r0, r2, r6, lsl #16
d00165e4:	e6e02609 	strbt	r2, [r0], r9, lsl #12
d00165e8:	e6de2600 	ldrb	r2, [lr], r0, lsl #12
d00165ec:	d03d2f5e 	eorsle	r2, sp, lr, asr pc
d00165f0:	aedbf73f 	mrcge	7, 6, APSR_nzcv, cr11, cr15, {1}
d00165f4:	0302f027 	movweq	pc, #8231	; 0x2027	; <UNPREDICTABLE>
d00165f8:	bf142b3c 	svclt	0x00142b3c
d00165fc:	26072600 	strcs	r2, [r7], -r0, lsl #12
d0016600:	f5a7e6d3 			; <UNDEFINED> instruction: 0xf5a7e6d3
d0016604:	2b0c738e 	blcs	0xd0333444
d0016608:	aecff63f 	mcrge	6, 6, pc, cr15, cr15, {1}	; <UNPREDICTABLE>
d001660c:	d8eb2b0c 	stmiale	fp!, {r2, r3, r8, r9, fp, sp}^
d0016610:	f852a202 			; <UNDEFINED> instruction: 0xf852a202
d0016614:	441a3023 	ldrmi	r3, [sl], #-35	; 0xffffffdd
d0016618:	bf004710 	svclt	0x00004710
d001661c:	00000035 	andeq	r0, r0, r5, lsr r0
d0016620:	00000035 	andeq	r0, r0, r5, lsr r0
d0016624:	00000039 	andeq	r0, r0, r9, lsr r0
d0016628:	00000039 	andeq	r0, r0, r9, lsr r0
d001662c:	ffffffad 			; <UNDEFINED> instruction: 0xffffffad
d0016630:	00000049 	andeq	r0, r0, r9, asr #32
d0016634:	ffffffcd 			; <UNDEFINED> instruction: 0xffffffcd
d0016638:	ffffffcd 			; <UNDEFINED> instruction: 0xffffffcd
d001663c:	ffffffcd 			; <UNDEFINED> instruction: 0xffffffcd
d0016640:	ffffffcd 			; <UNDEFINED> instruction: 0xffffffcd
d0016644:	ffffffcd 			; <UNDEFINED> instruction: 0xffffffcd
d0016648:	0000003d 	andeq	r0, r0, sp, lsr r0
d001664c:	0000003d 	andeq	r0, r0, sp, lsr r0
d0016650:	e6aa2606 	strt	r2, [sl], r6, lsl #12
d0016654:	e6a82607 	strt	r2, [r8], r7, lsl #12
d0016658:	e6a62608 	strt	r2, [r6], r8, lsl #12
d001665c:	e6a4260a 	strt	r2, [r4], sl, lsl #12
d0016660:	e6a22603 	strt	r2, [r2], r3, lsl #12
d0016664:	e6a02601 	strt	r2, [r0], r1, lsl #12
d0016668:	e69e2605 	ldr	r2, [lr], r5, lsl #12
d001666c:	e69c2604 	ldr	r2, [ip], r4, lsl #12
d0016670:	46204631 			; <UNDEFINED> instruction: 0x46204631
d0016674:	ff55f7fe 			; <UNDEFINED> instruction: 0xff55f7fe
d0016678:	463269a3 	ldrtmi	r6, [r2], -r3, lsr #19
d001667c:	ee089904 	vmla.f16	s18, s16, s8
d0016680:	69e33a10 	stmibvs	r3!, {r4, r9, fp, ip, sp}^
d0016684:	46204680 	strtmi	r4, [r0], -r0, lsl #13
d0016688:	3a90ee08 	bcc	0xce451eb0
d001668c:	930a6a23 	movwls	r6, #43555	; 0xaa23
d0016690:	93086ae3 	movwls	r6, #35555	; 0x8ae3
d0016694:	fe4af7ff 	mcr2	7, 2, pc, cr10, cr15, {7}	; <UNPREDICTABLE>
d0016698:	46074ba8 	strmi	r4, [r7], -r8, lsr #23
d001669c:	4620213a 			; <UNDEFINED> instruction: 0x4620213a
d00166a0:	920258e2 	andls	r5, r2, #14811136	; 0xe20000
d00166a4:	447a4aad 	ldrbtmi	r4, [sl], #-2733	; 0xfffff553
d00166a8:	fbd7f7fc 	blx	0xcf6146a2
d00166ac:	93054ba3 	movwls	r4, #23459	; 0x5ba3
d00166b0:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d00166b4:	4620ae9f 			; <UNDEFINED> instruction: 0x4620ae9f
d00166b8:	ff26f7fe 			; <UNDEFINED> instruction: 0xff26f7fe
d00166bc:	328ff504 	addcc	pc, pc, #4, 10	; 0x1000000
d00166c0:	46334641 	ldrtmi	r4, [r3], -r1, asr #12
d00166c4:	21b8f8d2 			; <UNDEFINED> instruction: 0x21b8f8d2
d00166c8:	0a10ee0a 	beq	0xd0451ef8
d00166cc:	f7ff6da0 			; <UNDEFINED> instruction: 0xf7ff6da0
d00166d0:	69a3fd17 	stmibvs	r3!, {r0, r1, r2, r4, r8, sl, fp, ip, sp, lr, pc}
d00166d4:	99044632 	stmdbls	r4, {r1, r4, r5, r9, sl, lr}
d00166d8:	3a10ee09 	bcc	0xd0451f04
d00166dc:	462069e3 	strtmi	r6, [r0], -r3, ror #19
d00166e0:	3a90ee09 	bcc	0xce451f0c
d00166e4:	930b6a23 	movwls	r6, #47651	; 0xba23
d00166e8:	93096ae3 	movwls	r6, #39651	; 0x9ae3
d00166ec:	fe1ef7ff 	mrc2	7, 0, pc, cr14, cr15, {7}
d00166f0:	46809a08 	strmi	r9, [r0], r8, lsl #20
d00166f4:	f5a29b05 			; <UNDEFINED> instruction: 0xf5a29b05
d00166f8:	58e37281 	stmiapl	r3!, {r0, r7, r9, ip, sp, lr}^
d00166fc:	d8202a01 	stmdale	r0!, {r0, r9, fp, sp}
d0016700:	fab29a0a 	blx	0xcecbcf30
d0016704:	0976f682 	ldmdbeq	r6!, {r1, r7, r9, sl, ip, sp, lr, pc}^
d0016708:	f5a29a09 			; <UNDEFINED> instruction: 0xf5a29a09
d001670c:	2a017281 	bcs	0xd0073118
d0016710:	9a0bd82a 	bls	0xd030c7c0
d0016714:	f082fab2 			; <UNDEFINED> instruction: 0xf082fab2
d0016718:	f0270940 			; <UNDEFINED> instruction: 0xf0270940
d001671c:	2a020204 	bcs	0xd0096f34
d0016720:	f028d003 			; <UNDEFINED> instruction: 0xf028d003
d0016724:	2a020204 	bcs	0xd0096f3c
d0016728:	6da3d133 	stfvsd	f5, [r3, #204]!	; 0xcc
d001672c:	d1392b00 	teqle	r9, r0, lsl #22
d0016730:	447b4b8b 	ldrbtmi	r4, [fp], #-2955	; 0xfffff475
d0016734:	3b16e9c4 	blcc	0xd05d0e4c
d0016738:	e9c49b01 	stmib	r4, {r0, r8, r9, fp, ip, pc}^
d001673c:	66a3a918 	ssatvs	sl, #4, r8, lsl #18
d0016740:	f240e030 	vqadd.s8	d30, d0, d16
d0016744:	99081201 	stmdbls	r8, {r0, r9, ip}
d0016748:	d1dd4291 			; <UNDEFINED> instruction: 0xd1dd4291
d001674c:	ee184a85 	vnmls.f32	s8, s17, s10
d0016750:	ee181a90 	vmov	r1, s17
d0016754:	93040a10 	movwls	r0, #18960	; 0x4a10
d0016758:	f7fa447a 			; <UNDEFINED> instruction: 0xf7fa447a
d001675c:	1e06f88b 	cdpne	8, 0, cr15, cr6, cr11, {4}
d0016760:	bf189b04 	svclt	0x00189b04
d0016764:	e7cf2601 	strb	r2, [pc, r1, lsl #12]
d0016768:	1201f240 	andne	pc, r1, #64, 4
d001676c:	42919909 	addsmi	r9, r1, #147456	; 0x24000
d0016770:	4a7dd10d 	bmi	0xd1f8abac
d0016774:	1a90ee19 	bne	0xce451fe0
d0016778:	0a10ee19 	beq	0xd0451fe4
d001677c:	447a9304 	ldrbtmi	r9, [sl], #-772	; 0xfffffcfc
d0016780:	f878f7fa 			; <UNDEFINED> instruction: 0xf878f7fa
d0016784:	9b043800 	blls	0xd012478c
d0016788:	2001bf18 	andcs	fp, r1, r8, lsl pc
d001678c:	2000e7c5 	andcs	lr, r0, r5, asr #15
d0016790:	2f01e7c3 	svccs	0x0001e7c3
d0016794:	f1b8d811 			; <UNDEFINED> instruction: 0xf1b8d811
d0016798:	d83a0f01 	ldmdale	sl!, {r0, r8, r9, sl, fp}
d001679c:	bf142f01 	svclt	0x00142f01
d00167a0:	25014645 	strcs	r4, [r1, #-1605]	; 0xfffff9bb
d00167a4:	328ff504 	addcc	pc, pc, #4, 10	; 0x1000000
d00167a8:	ee1a2300 	cdp	3, 1, cr2, cr10, cr0, {0}
d00167ac:	6da01a10 			; <UNDEFINED> instruction: 0x6da01a10
d00167b0:	21b8f8d2 			; <UNDEFINED> instruction: 0x21b8f8d2
d00167b4:	fca4f7ff 	stc2	7, cr15, [r4], #1020	; 0x3fc
d00167b8:	4547e61c 	strbmi	lr, [r7, #-1564]	; 0xfffff9e4
d00167bc:	2f05d11f 	svccs	0x0005d11f
d00167c0:	2f03d001 	svccs	0x0003d001
d00167c4:	9a02d114 	bls	0xd00cac1c
d00167c8:	d011429a 	mulsle	r1, sl, r2
d00167cc:	b948b9ae 	stmdblt	r8, {r1, r2, r3, r5, r7, r8, fp, ip, sp, pc}^
d00167d0:	b93b6da3 	ldmdblt	fp!, {r0, r1, r5, r7, r8, sl, fp, sp, lr}
d00167d4:	447b4b65 	ldrbtmi	r4, [fp], #-2917	; 0xfffff49b
d00167d8:	3b16e9c4 	blcc	0xd05d0ef0
d00167dc:	e9c49b01 	stmib	r4, {r0, r8, r9, fp, ip, pc}^
d00167e0:	66a3a918 	ssatvs	sl, #4, r8, lsl #18
d00167e4:	461a9b05 	ldrmi	r9, [sl], -r5, lsl #22
d00167e8:	50a39b02 	adcpl	r9, r3, r2, lsl #22
d00167ec:	e7d9463d 			; <UNDEFINED> instruction: 0xe7d9463d
d00167f0:	2e009a02 	vmlacs.f32	s18, s0, s4
d00167f4:	461abf18 	sadd16mi	fp, sl, r8
d00167f8:	93024613 	movwls	r4, #9747	; 0x2613
d00167fc:	2f04e7f2 	svccs	0x0004e7f2
d0016800:	2800d107 	stmdacs	r0, {r0, r1, r2, r8, ip, lr, pc}
d0016804:	f1b8d1f2 			; <UNDEFINED> instruction: 0xf1b8d1f2
d0016808:	d1120f04 	tstle	r2, r4, lsl #30
d001680c:	4645b146 	strbmi	fp, [r5], -r6, asr #2
d0016810:	f1b8e7c8 			; <UNDEFINED> instruction: 0xf1b8e7c8
d0016814:	d1090f04 	tstle	r9, r4, lsl #30
d0016818:	d1f82e00 	mvnsle	r2, r0, lsl #28
d001681c:	d0072f03 	andle	r2, r7, r3, lsl #30
d0016820:	2b006da3 	blcs	0xd0031eb4
d0016824:	4b52d1be 	blmi	0xd14caf24
d0016828:	e783447b 			; <UNDEFINED> instruction: 0xe783447b
d001682c:	d1002f03 	tstle	r0, r3, lsl #30
d0016830:	f1b8b948 			; <UNDEFINED> instruction: 0xf1b8b948
d0016834:	d1f30f03 	mvnsle	r0, r3, lsl #30
d0016838:	d0f12e00 	rscsle	r2, r1, r0, lsl #28
d001683c:	2f039a02 	svccs	0x00039a02
d0016840:	461abf18 	sadd16mi	fp, sl, r8
d0016844:	9b059202 	blls	0xd017b054
d0016848:	461a2503 	ldrmi	r2, [sl], -r3, lsl #10
d001684c:	50a39b02 	adcpl	r9, r3, r2, lsl #22
d0016850:	9b03e7a8 	blls	0xd01106f8
d0016854:	d1192b01 	tstle	r9, r1, lsl #22
d0016858:	2b041eeb 	blcs	0xd011e40c
d001685c:	6da3d809 	stcvs	8, cr13, [r3, #36]!	; 0x24
d0016860:	4b44b93b 	blmi	0xd1144d54
d0016864:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0016868:	9b013b16 	blls	0xd00654c8
d001686c:	a918e9c4 	ldmdbge	r8, {r2, r6, r7, r8, fp, sp, lr, pc}
d0016870:	f50466a3 			; <UNDEFINED> instruction: 0xf50466a3
d0016874:	462814a4 	strtmi	r1, [r8], -r4, lsr #9
d0016878:	5492f504 	ldrpl	pc, [r2], #1284	; 0x504
d001687c:	3b016823 	blcc	0xd0070910
d0016880:	b00d6023 	andlt	r6, sp, r3, lsr #32
d0016884:	8b06ecbd 	blhi	0xd01d1b80
d0016888:	8ff0e8bd 	svchi	0x00f0e8bd
d001688c:	2b049b03 	blcs	0xd013d4a0
d0016890:	1eebd1ef 	urdne<illegal precision>z	f5, #10.0
d0016894:	d9ec2b01 	stmible	ip!, {r0, r8, r9, fp, sp}^
d0016898:	f5a39b07 			; <UNDEFINED> instruction: 0xf5a39b07
d001689c:	2b017381 	blcs	0xd00736a8
d00168a0:	9b06d802 	blls	0xd01cc8b0
d00168a4:	d0e42b00 	rscle	r2, r4, r0, lsl #22
d00168a8:	2b006da3 	blcs	0xd0031f3c
d00168ac:	4b32d1e1 	blmi	0xd0ccb038
d00168b0:	e7d8447b 			; <UNDEFINED> instruction: 0xe7d8447b
d00168b4:	f43f2e04 			; <UNDEFINED> instruction: 0xf43f2e04
d00168b8:	2e03ae62 	cdpcs	14, 0, cr10, cr3, cr2, {3}
d00168bc:	ae5ff47f 	mrcge	4, 2, APSR_nzcv, cr15, cr15, {3}
d00168c0:	f47f2d00 			; <UNDEFINED> instruction: 0xf47f2d00
d00168c4:	2b00ae5c 	blcs	0xd004223c
d00168c8:	ae4af47f 	mcrge	4, 2, pc, cr10, cr15, {3}	; <UNPREDICTABLE>
d00168cc:	2e04e657 	mcrcs	6, 0, lr, cr4, cr7, {2}
d00168d0:	e7f5d1f3 	udf	#23827	; 0x5d13
d00168d4:	d1212f2b 			; <UNDEFINED> instruction: 0xd1212f2b
d00168d8:	f43f2e04 			; <UNDEFINED> instruction: 0xf43f2e04
d00168dc:	2e03ae0d 	cdpcs	14, 0, cr10, cr3, cr13, {0}
d00168e0:	2180d010 	orrcs	sp, r0, r0, lsl r0
d00168e4:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d00168e8:	f641f9b9 			; <UNDEFINED> instruction: 0xf641f9b9
d00168ec:	f6412308 			; <UNDEFINED> instruction: 0xf6412308
d00168f0:	2f2b0108 	svccs	0x002b0108
d00168f4:	4619bf18 	sadd16mi	fp, r9, r8
d00168f8:	f9b0f7fe 			; <UNDEFINED> instruction: 0xf9b0f7fe
d00168fc:	2f2de547 	svccs	0x002de547
d0016900:	ae12f47f 	mrcge	4, 0, APSR_nzcv, cr2, cr15, {3}
d0016904:	2b006da3 	blcs	0xd0031f98
d0016908:	ad41f47f 	cfstrdge	mvd15, [r1, #-508]	; 0xfffffe04
d001690c:	e9c49b09 	stmib	r4, {r0, r3, r8, r9, fp, ip, pc}^
d0016910:	9b013b16 	blls	0xd0065570
d0016914:	a918e9c4 	ldmdbge	r8, {r2, r6, r7, r8, fp, sp, lr, pc}
d0016918:	e53866a3 	ldr	r6, [r8, #-1699]!	; 0xfffff95d
d001691c:	f47f2f2d 			; <UNDEFINED> instruction: 0xf47f2f2d
d0016920:	2e04ae03 	cdpcs	14, 0, cr10, cr4, cr3, {0}
d0016924:	f641d1db 			; <UNDEFINED> instruction: 0xf641d1db
d0016928:	46202108 	strtmi	r2, [r0], -r8, lsl #2
d001692c:	f996f7fe 			; <UNDEFINED> instruction: 0xf996f7fe
d0016930:	5184f44f 	orrpl	pc, r4, pc, asr #8
d0016934:	f992f7fe 			; <UNDEFINED> instruction: 0xf992f7fe
d0016938:	bf00e5a9 	svclt	0x0000e5a9
d001693c:	00149244 	andseq	r9, r4, r4, asr #4
d0016940:	fffffdae 			; <UNDEFINED> instruction: 0xfffffdae
d0016944:	fffffe28 			; <UNDEFINED> instruction: 0xfffffe28
d0016948:	fffffe05 			; <UNDEFINED> instruction: 0xfffffe05
d001694c:	fffffd84 			; <UNDEFINED> instruction: 0xfffffd84
d0016950:	fffffdfa 			; <UNDEFINED> instruction: 0xfffffdfa
d0016954:	fffffeac 			; <UNDEFINED> instruction: 0xfffffeac
d0016958:	fffffcb2 			; <UNDEFINED> instruction: 0xfffffcb2
d001695c:	fffffb60 			; <UNDEFINED> instruction: 0xfffffb60
d0016960:	fffffafb 			; <UNDEFINED> instruction: 0xfffffafb
d0016964:	ffffe5c6 			; <UNDEFINED> instruction: 0xffffe5c6
d0016968:	ffffe5a0 			; <UNDEFINED> instruction: 0xffffe5a0
d001696c:	fffffa7f 			; <UNDEFINED> instruction: 0xfffffa7f
d0016970:	fffffa61 			; <UNDEFINED> instruction: 0xfffffa61
d0016974:	fffffa76 			; <UNDEFINED> instruction: 0xfffffa76
d0016978:	fffffa53 			; <UNDEFINED> instruction: 0xfffffa53

Disassembly of section .text.int_pointer_element:

d00169c0 <.text.int_pointer_element>:
d00169c0:	4615b5f8 			; <UNDEFINED> instruction: 0x4615b5f8
d00169c4:	460f4a53 			; <UNDEFINED> instruction: 0x460f4a53
d00169c8:	447a215b 	ldrbtmi	r2, [sl], #-347	; 0xfffffea5
d00169cc:	f7fc4604 			; <UNDEFINED> instruction: 0xf7fc4604
d00169d0:	b910fa44 	ldmdblt	r0, {r2, r6, r9, fp, ip, sp, lr, pc}
d00169d4:	46282500 	strtmi	r2, [r8], -r0, lsl #10
d00169d8:	f24bbdf8 	vmla.f32	<illegal reg q13.5>, <illegal reg q13.5>, q12
d00169dc:	46204103 	strtmi	r4, [r0], -r3, lsl #2
d00169e0:	f93cf7fe 			; <UNDEFINED> instruction: 0xf93cf7fe
d00169e4:	46112201 	ldrmi	r2, [r1], -r1, lsl #4
d00169e8:	fca0f7ff 	stc2	7, cr15, [r0], #1020	; 0x3fc
d00169ec:	215d4a4a 	cmpcs	sp, sl, asr #20
d00169f0:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d00169f4:	fa31f7fc 	blx	0xd0c949ec
d00169f8:	d0eb2800 	rscle	r2, fp, r0, lsl #16
d00169fc:	4106f64b 	tstmi	r6, fp, asr #12	; <UNPREDICTABLE>
d0016a00:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0016a04:	2180f92b 	orrcs	pc, r0, fp, lsr #18
d0016a08:	f928f7fe 			; <UNDEFINED> instruction: 0xf928f7fe
d0016a0c:	0108f641 	tsteq	r8, r1, asr #12	; <UNPREDICTABLE>
d0016a10:	f924f7fe 			; <UNDEFINED> instruction: 0xf924f7fe
d0016a14:	d13f2d00 	teqle	pc, r0, lsl #26
d0016a18:	2e3d6ae6 	vsubcs.f32	s12, s27, s13
d0016a1c:	f46fd03e 	vld4.8	{d29-d32}, [pc :256], lr
d0016a20:	18737192 	ldmdane	r3!, {r1, r4, r7, r8, ip, sp, lr}^
d0016a24:	d9392b01 	ldmdble	r9!, {r0, r8, r9, fp, sp}
d0016a28:	7294f46f 	addsvc	pc, r4, #1862270976	; 0x6f000000
d0016a2c:	2b0418b3 	blcs	0xd011cd00
d0016a30:	f44fd934 	vst2.8	{d29,d31}, [pc :256], r4
d0016a34:	462041d0 			; <UNDEFINED> instruction: 0x462041d0
d0016a38:	f910f7fe 			; <UNDEFINED> instruction: 0xf910f7fe
d0016a3c:	f641e7cb 			; <UNDEFINED> instruction: 0xf641e7cb
d0016a40:	46200108 	strtmi	r0, [r0], -r8, lsl #2
d0016a44:	f90af7fe 			; <UNDEFINED> instruction: 0xf90af7fe
d0016a48:	4106f64b 	tstmi	r6, fp, asr #12	; <UNPREDICTABLE>
d0016a4c:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0016a50:	f246f905 	vmla.i8	d31, d6, d5
d0016a54:	25020108 	strcs	r0, [r2, #-264]	; 0xfffffef8
d0016a58:	f900f7fe 			; <UNDEFINED> instruction: 0xf900f7fe
d0016a5c:	f641e7bb 			; <UNDEFINED> instruction: 0xf641e7bb
d0016a60:	e7ee2108 	strb	r2, [lr, r8, lsl #2]!
d0016a64:	0108f244 	tsteq	r8, r4, asr #4	; <UNPREDICTABLE>
d0016a68:	f244e7eb 	vabd.s8	q15, q10, <illegal reg q13.5>
d0016a6c:	e7e83108 	strb	r3, [r8, r8, lsl #2]!
d0016a70:	0148f244 	cmpeq	r8, r4, asr #4	; <UNPREDICTABLE>
d0016a74:	f244e7e5 	vabd.s8	q15, q10, <illegal reg q10.5>
d0016a78:	f7fe6102 			; <UNDEFINED> instruction: 0xf7fe6102
d0016a7c:	f244f8ef 	vadd.i8	<illegal reg q15.5>, q10, <illegal reg q15.5>
d0016a80:	f7fe6108 			; <UNDEFINED> instruction: 0xf7fe6108
d0016a84:	f244f8eb 	vadd.i8	<illegal reg q15.5>, q10, <illegal reg q13.5>
d0016a88:	f2440190 	vand	d16, d20, d0
d0016a8c:	f5b61310 			; <UNDEFINED> instruction: 0xf5b61310
d0016a90:	bf187f96 	svclt	0x00187f96
d0016a94:	e7d44619 	bfi	r4, r9, #12, #9
d0016a98:	e79c2504 	ldr	r2, [ip, r4, lsl #10]
d0016a9c:	d0c82f00 	sbcle	r2, r8, r0, lsl #30
d0016aa0:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0016aa4:	f24bf9b1 	vmul.i8	d31, d27, d17
d0016aa8:	46204103 	strtmi	r4, [r0], -r3, lsl #2
d0016aac:	f8d6f7fe 			; <UNDEFINED> instruction: 0xf8d6f7fe
d0016ab0:	d0072e3d 	andle	r2, r7, sp, lsr lr
d0016ab4:	41d0f44f 	bicsmi	pc, r0, pc, asr #8
d0016ab8:	f8d0f7fe 			; <UNDEFINED> instruction: 0xf8d0f7fe
d0016abc:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d0016ac0:	f8ccf7fe 			; <UNDEFINED> instruction: 0xf8ccf7fe
d0016ac4:	46202201 	strtmi	r2, [r0], -r1, lsl #4
d0016ac8:	f7ff4611 			; <UNDEFINED> instruction: 0xf7ff4611
d0016acc:	2e3dfc2f 	cdpcs	12, 3, cr15, cr13, cr15, {1}
d0016ad0:	f64bd0ba 			; <UNDEFINED> instruction: 0xf64bd0ba
d0016ad4:	46204106 	strtmi	r4, [r0], -r6, lsl #2
d0016ad8:	f8c0f7fe 			; <UNDEFINED> instruction: 0xf8c0f7fe
d0016adc:	7392f46f 	orrsvc	pc, r2, #1862270976	; 0x6f000000
d0016ae0:	2b0818f3 	blcs	0xd021ceb4
d0016ae4:	a202d8b0 	andge	sp, r2, #176, 16	; 0xb00000
d0016ae8:	3023f852 	eorcc	pc, r3, r2, asr r8	; <UNPREDICTABLE>
d0016aec:	4710441a 			; <UNDEFINED> instruction: 0x4710441a
d0016af0:	ffffff4f 			; <UNDEFINED> instruction: 0xffffff4f
d0016af4:	ffffff6f 			; <UNDEFINED> instruction: 0xffffff6f
d0016af8:	ffffff59 			; <UNDEFINED> instruction: 0xffffff59
d0016afc:	ffffff59 			; <UNDEFINED> instruction: 0xffffff59
d0016b00:	ffffff75 			; <UNDEFINED> instruction: 0xffffff75
d0016b04:	ffffff7b 			; <UNDEFINED> instruction: 0xffffff7b
d0016b08:	ffffff81 			; <UNDEFINED> instruction: 0xffffff81
d0016b0c:	ffffff87 			; <UNDEFINED> instruction: 0xffffff87
d0016b10:	ffffff87 			; <UNDEFINED> instruction: 0xffffff87
d0016b14:	ffffffae 			; <UNDEFINED> instruction: 0xffffffae
d0016b18:	ffffffaa 			; <UNDEFINED> instruction: 0xffffffaa

Disassembly of section .text.api_call:

d0016df8 <.text.api_call>:
d0016df8:	4ff0e92d 	svcmi	0x00f0e92d
d0016dfc:	8b02ed2d 	blhi	0xd00d22b8
d0016e00:	f891b087 			; <UNDEFINED> instruction: 0xf891b087
d0016e04:	46043046 	strmi	r3, [r4], -r6, asr #32
d0016e08:	0548f101 	strbeq	pc, [r8, #-257]	; 0xfffffeff	; <UNPREDICTABLE>
d0016e0c:	23009303 	movwcs	r9, #771	; 0x303
d0016e10:	93029101 	movwls	r9, #8449	; 0x2101
d0016e14:	34a0f8df 	strtcc	pc, [r0], #2271	; 0x8df
d0016e18:	ee08447b 	mcr	4, 0, r4, cr8, cr11, {3}
d0016e1c:	9b023a10 	blls	0xd00a5664
d0016e20:	42939a03 	addsmi	r9, r3, #12288	; 0x3000
d0016e24:	6da3d202 	sfmvs	f5, 1, [r3, #8]!
d0016e28:	d03e2b00 	eorsle	r2, lr, r0, lsl #22
d0016e2c:	248cf8df 	strcs	pc, [ip], #2271	; 0x8df
d0016e30:	46202129 	strtmi	r2, [r0], -r9, lsr #2
d0016e34:	f7fc447a 			; <UNDEFINED> instruction: 0xf7fc447a
d0016e38:	2800f810 	stmdacs	r0, {r4, fp, ip, sp, lr, pc}
d0016e3c:	8287f000 	addhi	pc, r7, #0
d0016e40:	46209903 	strtmi	r9, [r0], -r3, lsl #18
d0016e44:	fb96f7fe 	blx	0xce5d4e46
d0016e48:	0318f24d 	tsteq	r8, #-805306364	; 0xd0000004	; <UNPREDICTABLE>
d0016e4c:	210c4605 	tstcs	ip, r5, lsl #12
d0016e50:	462058e2 	strtmi	r5, [r0], -r2, ror #17
d0016e54:	ff22f7fd 			; <UNDEFINED> instruction: 0xff22f7fd
d0016e58:	f64f9b01 			; <UNDEFINED> instruction: 0xf64f9b01
d0016e5c:	f8df79ff 			; <UNDEFINED> instruction: 0xf8df79ff
d0016e60:	f1038460 			; <UNDEFINED> instruction: 0xf1038460
d0016e64:	f1030640 			; <UNDEFINED> instruction: 0xf1030640
d0016e68:	f8360746 			; <UNDEFINED> instruction: 0xf8360746
d0016e6c:	454b3b02 	strbmi	r3, [fp, #-2818]	; 0xfffff4fe
d0016e70:	824ef040 	subhi	pc, lr, #64	; 0x40
d0016e74:	71e0f244 	mvnvc	pc, r4, asr #4
d0016e78:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0016e7c:	b125feef 	msrlt	SP_usr, pc
d0016e80:	4130f445 	teqmi	r0, r5, asr #8	; <UNPREDICTABLE>
d0016e84:	f7fdb289 			; <UNDEFINED> instruction: 0xf7fdb289
d0016e88:	9b01fee9 	blls	0xd0096a34
d0016e8c:	3047f893 	umaalcc	pc, r7, r3, r8	; <UNPREDICTABLE>
d0016e90:	f0402b06 			; <UNDEFINED> instruction: 0xf0402b06
d0016e94:	f24b824d 	vhsub.s8	q12, <illegal reg q5.5>, <illegal reg q6.5>
d0016e98:	462021c0 	strtmi	r2, [r0], -r0, asr #3
d0016e9c:	ecbdb007 	ldc	0, cr11, [sp], #28
d0016ea0:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d0016ea4:	f7fd4ff0 			; <UNDEFINED> instruction: 0xf7fd4ff0
d0016ea8:	9b02bed9 	blls	0xd00c6a14
d0016eac:	ee18b12b 	mnfep	f3, #3.0
d0016eb0:	212c2a10 			; <UNDEFINED> instruction: 0x212c2a10
d0016eb4:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0016eb8:	f895ffd0 			; <UNDEFINED> instruction: 0xf895ffd0
d0016ebc:	f10bb000 			; <UNDEFINED> instruction: 0xf10bb000
d0016ec0:	2b1533ff 	blcs	0xd0563ec4
d0016ec4:	81ccf200 	bichi	pc, ip, r0, lsl #4
d0016ec8:	f013e8df 			; <UNDEFINED> instruction: 0xf013e8df
d0016ecc:	00160023 	andseq	r0, r6, r3, lsr #32
d0016ed0:	01ca01ca 	biceq	r0, sl, sl, asr #3
d0016ed4:	01ca01ca 	biceq	r0, sl, sl, asr #3
d0016ed8:	01ca01ca 	biceq	r0, sl, sl, asr #3
d0016edc:	002e002e 	eoreq	r0, lr, lr, lsr #32
d0016ee0:	002e01ca 	eoreq	r0, lr, sl, asr #3
d0016ee4:	019700b1 	ldrheq	r0, [r7, r1]
d0016ee8:	01ca015f 	biceq	r0, sl, pc, asr r1
d0016eec:	00f101ca 	rscseq	r0, r1, sl, asr #3
d0016ef0:	002e00f1 	strdeq	r0, [lr], -r1	; <UNPREDICTABLE>
d0016ef4:	015900f1 	ldrsheq	r0, [r9, #-1]
d0016ef8:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0016efc:	f24bfd31 	vmla.f32	d31, d11, d17
d0016f00:	46204103 	strtmi	r4, [r0], -r3, lsl #2
d0016f04:	feaaf7fd 	mcr2	7, 5, pc, cr10, cr13, {7}	; <UNPREDICTABLE>
d0016f08:	35019b02 	strcc	r9, [r1, #-2818]	; 0xfffff4fe
d0016f0c:	93023301 	movwls	r3, #8961	; 0x2301
d0016f10:	4620e785 	strtmi	lr, [r0], -r5, lsl #15
d0016f14:	ff08f7fd 			; <UNDEFINED> instruction: 0xff08f7fd
d0016f18:	d1f02800 	mvnsle	r2, r0, lsl #16
d0016f1c:	447949e9 	ldrbtmi	r4, [r9], #-2537	; 0xfffff617
d0016f20:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d0016f24:	e7eaf941 	strb	pc, [sl, r1, asr #18]!	; <UNPREDICTABLE>
d0016f28:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0016f2c:	2800fefd 	stmdacs	r0, {r0, r2, r3, r4, r5, r6, r7, r9, sl, fp, ip, sp, lr, pc}
d0016f30:	2126d1e5 			; <UNDEFINED> instruction: 0x2126d1e5
d0016f34:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0016f38:	6ae2ff82 	bvs	0xcf8d6d48
d0016f3c:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d0016f40:	a024f8d4 	ldrdge	pc, [r4], -r4	; <UNPREDICTABLE>
d0016f44:	9028f8d4 	ldrdls	pc, [r8], -r4	; <UNPREDICTABLE>
d0016f48:	f894429a 			; <UNDEFINED> instruction: 0xf894429a
d0016f4c:	6b678030 	blvs	0xd19f7014
d0016f50:	6da3d006 	stcvs	0, cr13, [r3, #24]!
d0016f54:	d1d22b00 	bicsle	r2, r2, r0, lsl #22
d0016f58:	447b4bdb 	ldrbtmi	r4, [fp], #-3035	; 0xfffff425
d0016f5c:	e02e65a3 	eor	r6, lr, r3, lsr #11
d0016f60:	1206e9d4 	andne	lr, r6, #212, 18	; 0x350000
d0016f64:	92054620 	andls	r4, r5, #32, 12	; 0x2000000
d0016f68:	f7f99104 			; <UNDEFINED> instruction: 0xf7f99104
d0016f6c:	1e06fc57 	mcrne	12, 0, pc, cr6, cr7, {2}	; <UNPREDICTABLE>
d0016f70:	9a05dbef 	bls	0xd018df34
d0016f74:	99044620 	stmdbls	r4, {r5, r9, sl, lr}
d0016f78:	fbc6f7f9 	blx	0xcf1d4f66
d0016f7c:	dae82800 	ble	0xcfa20f84
d0016f80:	0f0cf1bb 	svceq	0x000cf1bb
d0016f84:	f1bbd021 			; <UNDEFINED> instruction: 0xf1bbd021
d0016f88:	d0270f14 	eorle	r0, r7, r4, lsl pc
d0016f8c:	0f09f1bb 	svceq	0x0009f1bb
d0016f90:	f8dfd12d 			; <UNDEFINED> instruction: 0xf8dfd12d
d0016f94:	f04fb338 			; <UNDEFINED> instruction: 0xf04fb338
d0016f98:	49cd0c01 	stmibmi	sp, {r0, sl, fp}^
d0016f9c:	44fb2205 	ldrbtmi	r2, [fp], #517	; 0x205
d0016fa0:	23384479 	teqcs	r8, #2030043136	; 0x79000000
d0016fa4:	18e04373 	stmiane	r0!, {r0, r1, r4, r5, r6, r8, r9, lr}^
d0016fa8:	4bc19304 	blmi	0xcf07bbc0
d0016fac:	e003f810 	and	pc, r3, r0, lsl r8	; <UNPREDICTABLE>
d0016fb0:	d02545e6 	eorle	r4, r5, r6, ror #11
d0016fb4:	2b006da3 	blcs	0xd0032648
d0016fb8:	f8c4d1a1 			; <UNDEFINED> instruction: 0xf8c4d1a1
d0016fbc:	f8c4b058 			; <UNDEFINED> instruction: 0xf8c4b058
d0016fc0:	66a7a05c 	ssatvs	sl, #8, ip, asr #0
d0016fc4:	9818e9c4 	ldmdals	r8, {r2, r6, r7, r8, fp, sp, lr, pc}
d0016fc8:	f8dfe799 			; <UNDEFINED> instruction: 0xf8dfe799
d0016fcc:	f04fb308 			; <UNDEFINED> instruction: 0xf04fb308
d0016fd0:	49c10c02 	stmibmi	r1, {r1, sl, fp}^
d0016fd4:	466244fb 			; <UNDEFINED> instruction: 0x466244fb
d0016fd8:	e7e24479 			; <UNDEFINED> instruction: 0xe7e24479
d0016fdc:	b2fcf8df 	rscslt	pc, ip, #14614528	; 0xdf0000
d0016fe0:	0c01f04f 	stceq	0, cr15, [r1], {79}	; 0x4f
d0016fe4:	220349be 	andcs	r4, r3, #3112960	; 0x2f8000
d0016fe8:	447944fb 	ldrbtmi	r4, [r9], #-1275	; 0xfffffb05
d0016fec:	f8dfe7d9 			; <UNDEFINED> instruction: 0xf8dfe7d9
d0016ff0:	f04fb2f4 			; <UNDEFINED> instruction: 0xf04fb2f4
d0016ff4:	49bc0c01 	ldmibmi	ip!, {r0, sl, fp}
d0016ff8:	466244fb 			; <UNDEFINED> instruction: 0x466244fb
d0016ffc:	e7d04479 			; <UNDEFINED> instruction: 0xe7d04479
d0017000:	c2e8f8df 	rscgt	pc, r8, #14614528	; 0xdf0000
d0017004:	000cf810 	andeq	pc, ip, r0, lsl r8	; <UNPREDICTABLE>
d0017008:	d1d34290 			; <UNDEFINED> instruction: 0xd1d34290
d001700c:	48a99b04 	stmiami	r9!, {r2, r8, r9, fp, ip, pc}
d0017010:	44201818 	strtmi	r1, [r0], #-2072	; 0xfffff7e8
d0017014:	fc6af008 	stc2l	0, cr15, [sl], #-32	; 0xffffffe0
d0017018:	d1cb2800 	bicle	r2, fp, r0, lsl #16
d001701c:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0017020:	4632fef3 			; <UNDEFINED> instruction: 0x4632fef3
d0017024:	46202102 	strtmi	r2, [r0], -r2, lsl #2
d0017028:	ff8ef7fd 			; <UNDEFINED> instruction: 0xff8ef7fd
d001702c:	4620e767 	strtmi	lr, [r0], -r7, ror #14
d0017030:	fe7af7fd 	mrc2	7, 3, pc, cr10, cr13, {7}
d0017034:	f47f2800 			; <UNDEFINED> instruction: 0xf47f2800
d0017038:	4aadaf62 	bmi	0xceb82dc8
d001703c:	46202126 	strtmi	r2, [r0], -r6, lsr #2
d0017040:	f7fb447a 			; <UNDEFINED> instruction: 0xf7fb447a
d0017044:	2800ff0a 	stmdacs	r0, {r1, r3, r8, r9, sl, fp, ip, sp, lr, pc}
d0017048:	af59f43f 	svcge	0x0059f43f
d001704c:	f2406ae2 	vpmax.s8	q11, q8, q9
d0017050:	f8d41301 			; <UNDEFINED> instruction: 0xf8d41301
d0017054:	429aa024 	addsmi	sl, sl, #36	; 0x24
d0017058:	9028f8d4 	ldrdls	pc, [r8], -r4	; <UNPREDICTABLE>
d001705c:	8030f894 	mlashi	r0, r4, r8, pc	; <UNPREDICTABLE>
d0017060:	d0066b67 	andle	r6, r6, r7, ror #22
d0017064:	2b006da3 	blcs	0xd00326f8
d0017068:	af49f47f 	svcge	0x0049f47f
d001706c:	447b4ba1 	ldrbtmi	r4, [fp], #-2977	; 0xfffff45f
d0017070:	e9d4e774 	ldmib	r4, {r2, r4, r5, r6, r8, r9, sl, sp, lr, pc}^
d0017074:	46201206 	strtmi	r1, [r0], -r6, lsl #4
d0017078:	91049205 	tstls	r4, r5, lsl #4
d001707c:	fb64f7f9 	blx	0xd195506a
d0017080:	dbef1e06 	blle	0xcfbde8a0
d0017084:	46209a05 	strtmi	r9, [r0], -r5, lsl #20
d0017088:	f7f99904 			; <UNDEFINED> instruction: 0xf7f99904
d001708c:	2800fb3d 	stmdacs	r0, {r0, r2, r3, r4, r5, r8, r9, fp, ip, sp, lr, pc}
d0017090:	233cdae8 	teqcs	ip, #232, 20	; 0xe8000
d0017094:	4306fb03 	movwmi	pc, #27395	; 0x6b03	; <UNPREDICTABLE>
d0017098:	335ff503 	cmpcc	pc, #12582912	; 0xc00000	; <UNPREDICTABLE>
d001709c:	33ecf893 	mvncc	pc, #9633792	; 0x930000
d00170a0:	d1df2b05 	bicsle	r2, pc, r5, lsl #22
d00170a4:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d00170a8:	4632feaf 	ldrtmi	pc, [r2], -pc, lsr #29	; <UNPREDICTABLE>
d00170ac:	f1bbe051 			; <UNDEFINED> instruction: 0xf1bbe051
d00170b0:	d01e0f15 	andsle	r0, lr, r5, lsl pc
d00170b4:	2b13782b 	blcs	0xd04f5168
d00170b8:	4e8fd122 	sinmiep	f5, f2
d00170bc:	4632447e 			; <UNDEFINED> instruction: 0x4632447e
d00170c0:	46202126 	strtmi	r2, [r0], -r6, lsr #2
d00170c4:	fec9f7fb 	mcr2	7, 6, pc, cr9, cr11, {7}	; <UNPREDICTABLE>
d00170c8:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d00170cc:	6ae2af18 	bvs	0xcf8c2d34
d00170d0:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d00170d4:	a024f8d4 	ldrdge	pc, [r4], -r4	; <UNPREDICTABLE>
d00170d8:	f8d4429a 			; <UNDEFINED> instruction: 0xf8d4429a
d00170dc:	f8949028 			; <UNDEFINED> instruction: 0xf8949028
d00170e0:	6b678030 	blvs	0xd19f71a8
d00170e4:	6da3d014 	stcvs	0, cr13, [r3, #80]!	; 0x50
d00170e8:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d00170ec:	65a6af08 	strvs	sl, [r6, #3848]!	; 0xf08
d00170f0:	4620e765 	strtmi	lr, [r0], -r5, ror #14
d00170f4:	fe18f7fd 	mrc2	7, 0, pc, cr8, cr13, {7}
d00170f8:	f47f2800 			; <UNDEFINED> instruction: 0xf47f2800
d00170fc:	e7d9af00 	ldrb	sl, [r9, r0, lsl #30]
d0017100:	d0022b12 	andle	r2, r2, r2, lsl fp
d0017104:	447e4e7d 	ldrbtmi	r4, [lr], #-3709	; 0xfffff183
d0017108:	4e7de7d9 	mrcmi	7, 3, lr, cr13, cr9, {6}
d001710c:	e7d6447e 			; <UNDEFINED> instruction: 0xe7d6447e
d0017110:	1206e9d4 	andne	lr, r6, #212, 18	; 0x350000
d0017114:	92054620 	andls	r4, r5, #32, 12	; 0x2000000
d0017118:	f7f99104 			; <UNDEFINED> instruction: 0xf7f99104
d001711c:	f1b0fb15 			; <UNDEFINED> instruction: 0xf1b0fb15
d0017120:	dbe00b00 	blle	0xcf819d28
d0017124:	46209a05 	strtmi	r9, [r0], -r5, lsl #20
d0017128:	f7f99904 			; <UNDEFINED> instruction: 0xf7f99904
d001712c:	2800faed 	stmdacs	r0, {r0, r2, r3, r5, r6, r7, r9, fp, ip, sp, lr, pc}
d0017130:	782bdad9 	stmdavc	fp!, {r0, r3, r4, r6, r7, r9, fp, ip, lr, pc}
d0017134:	d1162b12 	tstle	r6, r2, lsl fp
d0017138:	fb03233c 	blx	0xd00dfe32
d001713c:	f503430b 			; <UNDEFINED> instruction: 0xf503430b
d0017140:	f893335f 			; <UNDEFINED> instruction: 0xf893335f
d0017144:	2b0133ec 	blcs	0xd00640fc
d0017148:	4620d8cd 	strtmi	sp, [r0], -sp, asr #17
d001714c:	fe5cf7fb 	mrc2	7, 2, pc, cr12, cr11, {7}
d0017150:	2101465a 	tstcs	r1, sl, asr r6
d0017154:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0017158:	f244fef7 			; <UNDEFINED> instruction: 0xf244fef7
d001715c:	46206108 	strtmi	r6, [r0], -r8, lsl #2
d0017160:	fd7cf7fd 	ldc2l	7, cr15, [ip, #-1012]!	; 0xfffffc0c
d0017164:	2b13e6cb 	blcs	0xd0510c98
d0017168:	233cd1ef 	teqcs	ip, #-1073741765	; 0xc000003b
d001716c:	430bfb03 	movwmi	pc, #47875	; 0xbb03	; <UNPREDICTABLE>
d0017170:	335ff503 	cmpcc	pc, #12582912	; 0xc00000	; <UNPREDICTABLE>
d0017174:	33ecf893 	mvncc	pc, #9633792	; 0x930000
d0017178:	d1b42b0f 			; <UNDEFINED> instruction: 0xd1b42b0f
d001717c:	2202e7e5 	andcs	lr, r2, #60030976	; 0x3940000
d0017180:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d0017184:	f8d2f7ff 			; <UNDEFINED> instruction: 0xf8d2f7ff
d0017188:	4620e6b9 			; <UNDEFINED> instruction: 0x4620e6b9
d001718c:	fdccf7fd 	stc2l	7, cr15, [ip, #1012]	; 0x3f4
d0017190:	495cb110 	ldmdbmi	ip, {r4, r8, ip, sp, pc}^
d0017194:	e6c34479 	uxtab16	r4, r3, r9, ror #8
d0017198:	f2406ae2 	vpmax.s8	q11, q8, q9
d001719c:	f8d41301 			; <UNDEFINED> instruction: 0xf8d41301
d00171a0:	429aa024 	addsmi	sl, sl, #36	; 0x24
d00171a4:	9028f8d4 	ldrdls	pc, [r8], -r4	; <UNPREDICTABLE>
d00171a8:	8030f894 	mlashi	r0, r4, r8, pc	; <UNPREDICTABLE>
d00171ac:	d0066b67 	andle	r6, r6, r7, ror #22
d00171b0:	2b006da3 	blcs	0xd0032844
d00171b4:	aea3f47f 	mcrge	4, 5, pc, cr3, cr15, {3}	; <UNPREDICTABLE>
d00171b8:	447b4b53 	ldrbtmi	r4, [fp], #-2899	; 0xfffff4ad
d00171bc:	e9d4e6ce 	ldmib	r4, {r1, r2, r3, r6, r7, r9, sl, sp, lr, pc}^
d00171c0:	46201206 	strtmi	r1, [r0], -r6, lsl #4
d00171c4:	91049205 	tstls	r4, r5, lsl #4
d00171c8:	fabef7f9 	blx	0xcefd51b4
d00171cc:	dbef1e06 	blle	0xcfbde9ec
d00171d0:	46209a05 	strtmi	r9, [r0], -r5, lsl #20
d00171d4:	f7f99904 			; <UNDEFINED> instruction: 0xf7f99904
d00171d8:	2800fa97 	stmdacs	r0, {r0, r1, r2, r4, r7, r9, fp, ip, sp, lr, pc}
d00171dc:	233cdae8 	teqcs	ip, #232, 20	; 0xe8000
d00171e0:	4306fb03 	movwmi	pc, #27395	; 0x6b03	; <UNPREDICTABLE>
d00171e4:	335ff503 	cmpcc	pc, #12582912	; 0xc00000	; <UNPREDICTABLE>
d00171e8:	23ecf893 	mvncs	pc, #9633792	; 0x930000
d00171ec:	d1df2a08 	bicsle	r2, pc, r8, lsl #20
d00171f0:	33fcf8d3 	mvnscc	pc, #13828096	; 0xd30000
d00171f4:	d9db2bff 	ldmible	fp, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, fp, sp}^
d00171f8:	4620e754 			; <UNDEFINED> instruction: 0x4620e754
d00171fc:	fd94f7fd 	ldc2	7, cr15, [r4, #1012]	; 0x3f4
d0017200:	f47f2800 			; <UNDEFINED> instruction: 0xf47f2800
d0017204:	6ae2ae7c 	bvs	0xcf8c2bfc
d0017208:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d001720c:	a024f8d4 	ldrdge	pc, [r4], -r4	; <UNPREDICTABLE>
d0017210:	f8d4429a 			; <UNDEFINED> instruction: 0xf8d4429a
d0017214:	f8949028 			; <UNDEFINED> instruction: 0xf8949028
d0017218:	6b678030 	blvs	0xd19f72e0
d001721c:	6da3d006 	stcvs	0, cr13, [r3, #24]!
d0017220:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0017224:	4b39ae6c 	blmi	0xd0e82bdc
d0017228:	e697447b 			; <UNDEFINED> instruction: 0xe697447b
d001722c:	1206e9d4 	andne	lr, r6, #212, 18	; 0x350000
d0017230:	92054620 	andls	r4, r5, #32, 12	; 0x2000000
d0017234:	f7f99104 			; <UNDEFINED> instruction: 0xf7f99104
d0017238:	1e06fa87 	vmlane.f32	s30, s13, s14
d001723c:	9a05dbef 	bls	0xd018e200
d0017240:	99044620 	stmdbls	r4, {r5, r9, sl, lr}
d0017244:	fa60f7f9 	blx	0xd1855230
d0017248:	dae82800 	ble	0xcfa21250
d001724c:	fb03233c 	blx	0xd00dff46
d0017250:	f5034306 			; <UNDEFINED> instruction: 0xf5034306
d0017254:	f893335f 			; <UNDEFINED> instruction: 0xf893335f
d0017258:	2b0733ec 	blcs	0xd01e4210
d001725c:	e721d1df 			; <UNDEFINED> instruction: 0xe721d1df
d0017260:	46202201 	strtmi	r2, [r0], -r1, lsl #4
d0017264:	f7ff4611 			; <UNDEFINED> instruction: 0xf7ff4611
d0017268:	782bf861 	stmdavc	fp!, {r0, r5, r6, fp, ip, sp, lr, pc}
d001726c:	2b053b03 	blcs	0xd0165e80
d0017270:	ae45f63f 	mcrge	6, 2, pc, cr5, cr15, {1}	; <UNPREDICTABLE>
d0017274:	f852a202 			; <UNDEFINED> instruction: 0xf852a202
d0017278:	441a3023 	ldrmi	r3, [sl], #-35	; 0xffffffdd
d001727c:	bf004710 	svclt	0x00004710
d0017280:	00000019 	andeq	r0, r0, r9, lsl r0
d0017284:	0000001f 	andeq	r0, r0, pc, lsl r0
d0017288:	fffffc7f 			; <UNDEFINED> instruction: 0xfffffc7f
d001728c:	0000002b 	andeq	r0, r0, fp, lsr #32
d0017290:	fffffc7f 			; <UNDEFINED> instruction: 0xfffffc7f
d0017294:	00000025 	andeq	r0, r0, r5, lsr #32
d0017298:	4132f44f 	teqmi	r2, pc, asr #8	; <UNPREDICTABLE>
d001729c:	f24be75f 	vaba.s8	q15, <illegal reg q5.5>, <illegal reg q7.5>
d00172a0:	e75c2180 	ldrb	r2, [ip, -r0, lsl #3]
d00172a4:	2140f24b 	cmpcs	r0, fp, asr #4	; <UNPREDICTABLE>
d00172a8:	f24be759 	vaba.s8	q15, <illegal reg q5.5>, <illegal reg q4.5>
d00172ac:	e75621c0 	ldrb	r2, [r6, -r0, asr #3]
d00172b0:	0013fe4b 	andseq	pc, r3, fp, asr #28
d00172b4:	0013fe4f 	andseq	pc, r3, pc, asr #28
d00172b8:	fffffe86 			; <UNDEFINED> instruction: 0xfffffe86
d00172bc:	ffffff96 			; <UNDEFINED> instruction: 0xffffff96
d00172c0:	ffffc000 			; <UNDEFINED> instruction: 0xffffc000
d00172c4:	fffffda3 			; <UNDEFINED> instruction: 0xfffffda3
d00172c8:	fffffd8b 			; <UNDEFINED> instruction: 0xfffffd8b
d00172cc:	fffffc19 			; <UNDEFINED> instruction: 0xfffffc19
d00172d0:	00007669 	andeq	r7, r0, r9, ror #12
d00172d4:	fffffb67 			; <UNDEFINED> instruction: 0xfffffb67
d00172d8:	000078b6 			; <UNDEFINED> instruction: 0x000078b6
d00172dc:	fffffb99 			; <UNDEFINED> instruction: 0xfffffb99
d00172e0:	00007624 	andeq	r7, r0, r4, lsr #12
d00172e4:	fffffb20 			; <UNDEFINED> instruction: 0xfffffb20
d00172e8:	00007891 	muleq	r0, r1, r8
d00172ec:	0013fe48 	andseq	pc, r3, r8, asr #28
d00172f0:	fffffcd3 			; <UNDEFINED> instruction: 0xfffffcd3
d00172f4:	fffffca5 			; <UNDEFINED> instruction: 0xfffffca5
d00172f8:	fffffb43 			; <UNDEFINED> instruction: 0xfffffb43
d00172fc:	fffffb5f 			; <UNDEFINED> instruction: 0xfffffb5f
d0017300:	fffffb22 			; <UNDEFINED> instruction: 0xfffffb22
d0017304:	fffffbb8 			; <UNDEFINED> instruction: 0xfffffbb8
d0017308:	fffffbb1 			; <UNDEFINED> instruction: 0xfffffbb1
d001730c:	fffffb73 			; <UNDEFINED> instruction: 0xfffffb73
d0017310:	01dcf64f 	bicseq	pc, ip, pc, asr #12
d0017314:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0017318:	f836fca1 			; <UNDEFINED> instruction: 0xf836fca1
d001731c:	ea411c02 	b	0xd105e32c
d0017320:	b2890108 	addlt	r0, r9, #8, 2
d0017324:	fc9af7fd 	ldc2	7, cr15, [sl], {253}	; 0xfd
d0017328:	f47f42be 			; <UNDEFINED> instruction: 0xf47f42be
d001732c:	e5a1ad9e 	str	sl, [r1, #3486]!	; 0xd9e
d0017330:	d1022b08 	tstle	r2, r8, lsl #22
d0017334:	2140f24b 	cmpcs	r0, fp, asr #4	; <UNPREDICTABLE>
d0017338:	2b10e5af 	blcs	0xd04509fc
d001733c:	f24bd102 	vrhadd.s8	d29, d11, d2
d0017340:	e5aa2180 	str	r2, [sl, #384]!	; 0x180
d0017344:	d1022b11 	tstle	r2, r1, lsl fp
d0017348:	4132f44f 	teqmi	r2, pc, asr #8	; <UNPREDICTABLE>
d001734c:	b007e5a5 	andlt	lr, r7, r5, lsr #11
d0017350:	8b02ecbd 	blhi	0xd00d264c
d0017354:	8ff0e8bd 	svchi	0x00f0e8bd

Disassembly of section .text.indirect_call:

d00173bc <.text.indirect_call>:
d00173bc:	fb032330 	blx	0xd00e0086
d00173c0:	e92d0301 	push	{r0, r8, r9}
d00173c4:	f50341f0 			; <UNDEFINED> instruction: 0xf50341f0
d00173c8:	f8df13a4 			; <UNDEFINED> instruction: 0xf8df13a4
d00173cc:	4604809c 			; <UNDEFINED> instruction: 0x4604809c
d00173d0:	f893460d 			; <UNDEFINED> instruction: 0xf893460d
d00173d4:	26007657 			; <UNDEFINED> instruction: 0x26007657
d00173d8:	42be44f8 	adcsmi	r4, lr, #248, 8	; 0xf8000000
d00173dc:	6da3d201 	sfmvs	f5, 1, [r3, #4]!
d00173e0:	4639b363 	ldrtmi	fp, [r9], -r3, ror #6
d00173e4:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d00173e8:	4a20f8c5 	bmi	0xd0855704
d00173ec:	21294606 			; <UNDEFINED> instruction: 0x21294606
d00173f0:	4620447a 			; <UNDEFINED> instruction: 0x4620447a
d00173f4:	fd31f7fb 	ldc2	7, cr15, [r1, #-1004]!	; 0xfffffc14
d00173f8:	f64fb1e8 			; <UNDEFINED> instruction: 0xf64fb1e8
d00173fc:	462001d7 			; <UNDEFINED> instruction: 0x462001d7
d0017400:	fc2cf7fd 	stc2	7, cr15, [ip], #-1012	; 0xfffffc0c
d0017404:	ea414917 	b	0xd1069868
d0017408:	b2890185 	addlt	r0, r9, #1073741857	; 0x40000021
d001740c:	fc26f7fd 	stc2	7, cr15, [r6], #-1012	; 0xfffffc0c
d0017410:	71e0f244 	mvnvc	pc, r4, asr #4
d0017414:	fc22f7fd 	stc2	7, cr15, [r2], #-1012	; 0xfffffc0c
d0017418:	f446b126 	vst4.8	{d27,d29,d31,d33}, [r6 :128], r6
d001741c:	b2894130 	addlt	r4, r9, #48, 2
d0017420:	fc1cf7fd 	ldc2	7, cr15, [ip], {253}	; 0xfd
d0017424:	fb002030 	blx	0xd001f4ee
d0017428:	f5044405 			; <UNDEFINED> instruction: 0xf5044405
d001742c:	f89414a4 			; <UNDEFINED> instruction: 0xf89414a4
d0017430:	2b013658 	blcs	0xd0064d98
d0017434:	2000d014 	andcs	sp, r0, r4, lsl r0
d0017438:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d001743c:	4642b126 	strbmi	fp, [r2], -r6, lsr #2
d0017440:	4620212c 	strtmi	r2, [r0], -ip, lsr #2
d0017444:	fd09f7fb 	stc2	7, cr15, [r9, #-1004]	; 0xfffffc14
d0017448:	46202201 	strtmi	r2, [r0], -r1, lsl #4
d001744c:	46113601 	ldrmi	r3, [r1], -r1, lsl #12
d0017450:	ff6cf7fe 			; <UNDEFINED> instruction: 0xff6cf7fe
d0017454:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d0017458:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d001745c:	e7bcfbff 			; <UNDEFINED> instruction: 0xe7bcfbff
d0017460:	e7e92002 	strb	r2, [r9, r2]!
d0017464:	ffffc000 			; <UNDEFINED> instruction: 0xffffc000
d0017468:	ffffff7c 			; <UNDEFINED> instruction: 0xffffff7c
d001746c:	ffffff94 			; <UNDEFINED> instruction: 0xffffff94

Disassembly of section .text.struct_array_element:

d00174e8 <.text.struct_array_element>:
d00174e8:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d00174ec:	4a244617 	bmi	0xd0928d50
d00174f0:	215b460d 	cmpcs	fp, sp, lsl #12
d00174f4:	4604447a 			; <UNDEFINED> instruction: 0x4604447a
d00174f8:	f7fb461e 			; <UNDEFINED> instruction: 0xf7fb461e
d00174fc:	b3d8fcae 	bicslt	pc, r8, #44544	; 0xae00
d0017500:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d0017504:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0017508:	2201fba9 	andcs	pc, r1, #173056	; 0x2a400
d001750c:	f7fe4611 			; <UNDEFINED> instruction: 0xf7fe4611
d0017510:	4a1cff0d 	bmi	0xd075714c
d0017514:	4620215d 			; <UNDEFINED> instruction: 0x4620215d
d0017518:	f7fb447a 			; <UNDEFINED> instruction: 0xf7fb447a
d001751c:	b358fc9e 	cmplt	r8, #40448	; 0x9e00	; <UNPREDICTABLE>
d0017520:	4106f64b 	tstmi	r6, fp, asr #12	; <UNPREDICTABLE>
d0017524:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0017528:	f44ffb99 			; <UNDEFINED> instruction: 0xf44ffb99
d001752c:	2102701a 	tstcs	r2, sl, lsl r0
d0017530:	4005fb00 	andmi	pc, r5, r0, lsl #22
d0017534:	3068f500 	rsbcc	pc, r8, r0, lsl #10
d0017538:	46208d02 	strtmi	r8, [r0], -r2, lsl #26
d001753c:	f7fd0092 			; <UNDEFINED> instruction: 0xf7fd0092
d0017540:	f244fbad 	vqdmulh.s<illegal width 8>	d31, d20, d29
d0017544:	46203150 			; <UNDEFINED> instruction: 0x46203150
d0017548:	fb88f7fd 	blx	0xce255546
d001754c:	51c2f44f 	bicpl	pc, r2, pc, asr #8
d0017550:	fb84f7fd 	blx	0xce15554e
d0017554:	212eb986 	smlawbcs	lr, r6, r9, fp
d0017558:	fc71f7fb 	ldc2l	7, cr15, [r1], #-1004	; 0xfffffc14
d001755c:	4633b138 			; <UNDEFINED> instruction: 0x4633b138
d0017560:	4629463a 			; <UNDEFINED> instruction: 0x4629463a
d0017564:	e8bd4620 	pop	{r5, r9, sl, lr}
d0017568:	f00041f0 			; <UNDEFINED> instruction: 0xf00041f0
d001756c:	4906bfb7 	stmdbmi	r6, {r0, r1, r2, r4, r5, r7, r8, r9, sl, fp, ip, sp, pc}
d0017570:	44794620 	ldrbtmi	r4, [r9], #-1568	; 0xfffff9e0
d0017574:	fe18f7f8 	mrc2	7, 0, pc, cr8, cr8, {7}
d0017578:	e8bd2003 	pop	{r0, r1, sp}
d001757c:	bf0081f0 	svclt	0x000081f0
d0017580:	ffffff78 			; <UNDEFINED> instruction: 0xffffff78
d0017584:	ffffff74 			; <UNDEFINED> instruction: 0xffffff74
d0017588:	ffffff40 			; <UNDEFINED> instruction: 0xffffff40

Disassembly of section .text.record_value_address:

d0017698 <.text.record_value_address>:
d0017698:	e92d4a54 	push	{r2, r4, r6, r9, fp, lr}
d001769c:	447a4ff0 	ldrbtmi	r4, [sl], #-4080	; 0xfffff010
d00176a0:	4689b087 	strmi	fp, [r9], r7, lsl #1
d00176a4:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d00176a8:	6a454604 	bvs	0xd1168ec0
d00176ac:	f8906a86 			; <UNDEFINED> instruction: 0xf8906a86
d00176b0:	f8d07030 			; <UNDEFINED> instruction: 0xf8d07030
d00176b4:	e9d08034 	ldmib	r0, {r2, r4, r5, pc}^
d00176b8:	f7fbab06 			; <UNDEFINED> instruction: 0xf7fbab06
d00176bc:	b1e0fbce 	mvnlt	pc, lr, asr #23
d00176c0:	46202128 	strtmi	r2, [r0], -r8, lsr #2
d00176c4:	fbbbf7fb 	blx	0xcef156ba
d00176c8:	462bb1d0 			; <UNDEFINED> instruction: 0x462bb1d0
d00176cc:	4651465a 			; <UNDEFINED> instruction: 0x4651465a
d00176d0:	e88d4620 	stm	sp, {r5, r9, sl, lr}
d00176d4:	f00001c0 			; <UNDEFINED> instruction: 0xf00001c0
d00176d8:	2806f959 	stmdacs	r6, {r0, r3, r4, r6, r8, fp, ip, sp, lr, pc}
d00176dc:	4b42d103 	blmi	0xd10cbaf0
d00176e0:	454b58e3 	strbmi	r5, [fp, #-2275]	; 0xfffff71d
d00176e4:	6da3d009 	stcvs	0, cr13, [r3, #36]!	; 0x24
d00176e8:	4b41b93b 	blmi	0xd1085bdc
d00176ec:	f8c4447b 			; <UNDEFINED> instruction: 0xf8c4447b
d00176f0:	e9c48068 	stmib	r4, {r3, r5, r6, pc}^
d00176f4:	e9c43516 	stmib	r4, {r1, r2, r4, r8, sl, ip, sp}^
d00176f8:	b0076718 	andlt	r6, r7, r8, lsl r7
d00176fc:	8ff0e8bd 	svchi	0x00f0e8bd
d0017700:	4651465a 			; <UNDEFINED> instruction: 0x4651465a
d0017704:	f7f84620 			; <UNDEFINED> instruction: 0xf7f84620
d0017708:	1e03ffff 	mcrne	15, 0, pc, cr3, cr15, {7}	; <UNPREDICTABLE>
d001770c:	465ada53 			; <UNDEFINED> instruction: 0x465ada53
d0017710:	46204651 			; <UNDEFINED> instruction: 0x46204651
d0017714:	f7f99305 			; <UNDEFINED> instruction: 0xf7f99305
d0017718:	1e02f817 	mcrne	8, 0, pc, cr2, cr7, {0}	; <UNPREDICTABLE>
d001771c:	da059b05 	ble	0xd017e338
d0017720:	2b006da3 	blcs	0xd0032db4
d0017724:	4b33d1e9 	blmi	0xd0d0bed0
d0017728:	e7e0447b 			; <UNDEFINED> instruction: 0xe7e0447b
d001772c:	fb01213c 	blx	0xd005fc26
d0017730:	f5014102 			; <UNDEFINED> instruction: 0xf5014102
d0017734:	f891315f 			; <UNDEFINED> instruction: 0xf891315f
d0017738:	f891b3ec 			; <UNDEFINED> instruction: 0xf891b3ec
d001773c:	f1bba3ee 			; <UNDEFINED> instruction: 0xf1bba3ee
d0017740:	d1460f0d 	cmple	r6, sp, lsl #30
d0017744:	21014620 	tstcs	r1, r0, lsr #12
d0017748:	fbfef7fd 	blx	0xcffd5746
d001774c:	6108f244 	tstvs	r8, r4, asr #4	; <UNPREDICTABLE>
d0017750:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0017754:	e005fa83 	and	pc, r5, r3, lsl #21
d0017758:	dbf32b00 	blle	0xcfce2360
d001775c:	46204619 			; <UNDEFINED> instruction: 0x46204619
d0017760:	fb46f7fd 	blx	0xd11d575e
d0017764:	0b10f1ab 	bleq	0xd0453e18
d0017768:	0f01f1bb 	svceq	0x0001f1bb
d001776c:	6ae3d80e 	bvs	0xcf90d7ac
d0017770:	d0052b5b 	andle	r2, r5, fp, asr fp
d0017774:	2b006da3 	blcs	0xd0032e08
d0017778:	4b1fd1bf 	blmi	0xd080be7c
d001777c:	e7b6447b 			; <UNDEFINED> instruction: 0xe7b6447b
d0017780:	22002301 	andcs	r2, r0, #67108864	; 0x4000000
d0017784:	46204651 			; <UNDEFINED> instruction: 0x46204651
d0017788:	feaef7ff 	mcr2	7, 5, pc, cr14, cr15, {7}	; <UNPREDICTABLE>
d001778c:	4620212e 	strtmi	r2, [r0], -lr, lsr #2
d0017790:	fb55f7fb 	blx	0xd1595786
d0017794:	464ab138 			; <UNDEFINED> instruction: 0x464ab138
d0017798:	46204651 			; <UNDEFINED> instruction: 0x46204651
d001779c:	e8bdb007 	pop	{r0, r1, r2, ip, sp, pc}
d00177a0:	f7fe4ff0 			; <UNDEFINED> instruction: 0xf7fe4ff0
d00177a4:	45d1b9c5 	ldrbmi	fp, [r1, #2501]	; 0x9c5
d00177a8:	6da3d0a7 	stcvs	0, cr13, [r3, #668]!	; 0x29c
d00177ac:	d1a42b00 			; <UNDEFINED> instruction: 0xd1a42b00
d00177b0:	447b4b12 	ldrbtmi	r4, [fp], #-2834	; 0xfffff4ee
d00177b4:	2230e79b 	eorscs	lr, r0, #40632320	; 0x26c0000
d00177b8:	4203fb02 	andmi	pc, r3, #2048	; 0x800
d00177bc:	12a4f502 	adcne	pc, r4, #8388608	; 0x800000
d00177c0:	b655f892 			; <UNDEFINED> instruction: 0xb655f892
d00177c4:	a656f892 			; <UNDEFINED> instruction: 0xa656f892
d00177c8:	0f0df1bb 	svceq	0x000df1bb
d00177cc:	f04fd0c6 			; <UNDEFINED> instruction: 0xf04fd0c6
d00177d0:	f1ab32ff 			; <UNDEFINED> instruction: 0xf1ab32ff
d00177d4:	2902010f 	stmdbcs	r2, {r0, r1, r2, r3, r8}
d00177d8:	6da3d9be 			; <UNDEFINED> instruction: 0x6da3d9be
d00177dc:	d18c2b00 	orrle	r2, ip, r0, lsl #22
d00177e0:	447b4b07 	ldrbtmi	r4, [fp], #-2823	; 0xfffff4f9
d00177e4:	bf00e783 	svclt	0x0000e783
d00177e8:	00149244 	andseq	r9, r4, r4, asr #4
d00177ec:	fffffeea 			; <UNDEFINED> instruction: 0xfffffeea
d00177f0:	fffffecb 			; <UNDEFINED> instruction: 0xfffffecb
d00177f4:	fffffeca 			; <UNDEFINED> instruction: 0xfffffeca
d00177f8:	fffffec6 			; <UNDEFINED> instruction: 0xfffffec6
d00177fc:	fffffebb 			; <UNDEFINED> instruction: 0xfffffebb
d0017800:	fffffe31 			; <UNDEFINED> instruction: 0xfffffe31

Disassembly of section .text.call.isra.0:

d001798c <.text.call.isra.0>:
d001798c:	4ff0e92d 	svcmi	0x00f0e92d
d0017990:	8b02ed2d 	blhi	0xd00d2e4c
d0017994:	460eb087 	strmi	fp, [lr], -r7, lsl #1
d0017998:	4afd4617 	bmi	0xcff691fc
d001799c:	46049301 	strmi	r9, [r4], -r1, lsl #6
d00179a0:	304cf89d 	umaalcc	pc, ip, sp, r8	; <UNPREDICTABLE>
d00179a4:	4639447a 			; <UNDEFINED> instruction: 0x4639447a
d00179a8:	93024630 	movwls	r4, #9776	; 0x2630
d00179ac:	ff62f7f8 			; <UNDEFINED> instruction: 0xff62f7f8
d00179b0:	4af8b1a8 	bmi	0xcfe44058
d00179b4:	46304639 			; <UNDEFINED> instruction: 0x46304639
d00179b8:	f7f8447a 			; <UNDEFINED> instruction: 0xf7f8447a
d00179bc:	2800ff5b 	stmdacs	r0, {r0, r1, r3, r4, r6, r8, r9, sl, fp, ip, sp, lr, pc}
d00179c0:	4af5d13b 	bmi	0xcfd8beb4
d00179c4:	46304639 			; <UNDEFINED> instruction: 0x46304639
d00179c8:	f7f8447a 			; <UNDEFINED> instruction: 0xf7f8447a
d00179cc:	4605ff53 			; <UNDEFINED> instruction: 0x4605ff53
d00179d0:	2202bb98 	andcs	fp, r2, #152, 22	; 0x26000
d00179d4:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d00179d8:	fca8f7fe 	stc2	7, cr15, [r8], #1016	; 0x3f8
d00179dc:	4aefe033 	bmi	0xcfc0fab0
d00179e0:	46304639 			; <UNDEFINED> instruction: 0x46304639
d00179e4:	f7f8447a 			; <UNDEFINED> instruction: 0xf7f8447a
d00179e8:	2800ff45 	stmdacs	r0, {r0, r2, r6, r8, r9, sl, fp, ip, sp, lr, pc}
d00179ec:	4aecd1e1 	bmi	0xcfb4c178
d00179f0:	46304639 			; <UNDEFINED> instruction: 0x46304639
d00179f4:	f7f8447a 			; <UNDEFINED> instruction: 0xf7f8447a
d00179f8:	2800ff3d 	stmdacs	r0, {r0, r2, r3, r4, r5, r8, r9, sl, fp, ip, sp, lr, pc}
d00179fc:	4ae9d1d9 	bmi	0xcfa8c168
d0017a00:	46304639 			; <UNDEFINED> instruction: 0x46304639
d0017a04:	f7f8447a 			; <UNDEFINED> instruction: 0xf7f8447a
d0017a08:	4605ff35 			; <UNDEFINED> instruction: 0x4605ff35
d0017a0c:	d1d02800 	bicsle	r2, r0, r0, lsl #16
d0017a10:	4631463a 			; <UNDEFINED> instruction: 0x4631463a
d0017a14:	f7f84620 			; <UNDEFINED> instruction: 0xf7f84620
d0017a18:	4680ff42 	strmi	pc, [r0], r2, asr #30
d0017a1c:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d0017a20:	46018088 	strmi	r8, [r1], -r8, lsl #1
d0017a24:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0017a28:	f898f9e7 			; <UNDEFINED> instruction: 0xf898f9e7
d0017a2c:	2d075047 	stccs	0, cr5, [r7, #-284]	; 0xfffffee4
d0017a30:	1f6bd010 	svcne	0x006bd010
d0017a34:	415d425d 	cmpmi	sp, sp, asr r2
d0017a38:	2201e00d 	andcs	lr, r1, #13
d0017a3c:	46202501 	strtmi	r2, [r0], -r1, lsl #10
d0017a40:	f7fe4611 			; <UNDEFINED> instruction: 0xf7fe4611
d0017a44:	4ad8fc73 	bmi	0xcf656c18
d0017a48:	46202129 	strtmi	r2, [r0], -r9, lsr #2
d0017a4c:	f7fb447a 			; <UNDEFINED> instruction: 0xf7fb447a
d0017a50:	b930fa04 	ldmdblt	r0!, {r2, r9, fp, ip, sp, lr, pc}
d0017a54:	46282502 	strtmi	r2, [r8], -r2, lsl #10
d0017a58:	ecbdb007 	ldc	0, cr11, [sp], #28
d0017a5c:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d0017a60:	f8df8ff0 			; <UNDEFINED> instruction: 0xf8df8ff0
d0017a64:	f8149348 			; <UNDEFINED> instruction: 0xf8149348
d0017a68:	b1a91009 			; <UNDEFINED> instruction: 0xb1a91009
d0017a6c:	f8344bbd 			; <UNDEFINED> instruction: 0xf8344bbd
d0017a70:	6da38003 	stcvs	0, cr8, [r3, #12]!
d0017a74:	d1ed2b00 	mvnle	r2, r0, lsl #22
d0017a78:	21014642 	tstcs	r1, r2, asr #12
d0017a7c:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0017a80:	4bb9fa63 	blmi	0xcee96414
d0017a84:	f5b658e6 			; <UNDEFINED> instruction: 0xf5b658e6
d0017a88:	d1426f00 	cmple	r2, r0, lsl #30
d0017a8c:	447949c8 	ldrbtmi	r4, [r9], #-2504	; 0xfffff638
d0017a90:	f7f84620 			; <UNDEFINED> instruction: 0xf7f84620
d0017a94:	e7ddfb89 	ldrb	pc, [sp, r9, lsl #23]	; <UNPREDICTABLE>
d0017a98:	3367f504 	msrcc	SPSR_sxc, #4, 10	; 0x1000000
d0017a9c:	81c4f8d3 	ldrdhi	pc, [r4, #131]	; 0x83
d0017aa0:	0f7ff1b8 	svceq	0x007ff1b8
d0017aa4:	f504d806 			; <UNDEFINED> instruction: 0xf504d806
d0017aa8:	f8da3a7f 			; <UNDEFINED> instruction: 0xf8da3a7f
d0017aac:	f5b6621c 			; <UNDEFINED> instruction: 0xf5b6621c
d0017ab0:	d9072f78 	stmdble	r7, {r3, r4, r5, r6, r8, r9, sl, fp, sp}
d0017ab4:	462049bf 			; <UNDEFINED> instruction: 0x462049bf
d0017ab8:	0800f04f 	stmdaeq	r0, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d0017abc:	f7f84479 			; <UNDEFINED> instruction: 0xf7f84479
d0017ac0:	e7d6fb73 			; <UNDEFINED> instruction: 0xe7d6fb73
d0017ac4:	0201f108 	andeq	pc, r1, #8, 2
d0017ac8:	f8c33607 			; <UNDEFINED> instruction: 0xf8c33607
d0017acc:	223c21c4 	eorscs	r2, ip, #196, 2	; 0x31
d0017ad0:	b008f894 	mullt	r8, r4, r8
d0017ad4:	0607f026 	streq	pc, [r7], -r6, lsr #32
d0017ad8:	4708fb02 	strmi	pc, [r8, -r2, lsl #22]
d0017adc:	375ff507 	ldrbcc	pc, [pc, -r7, lsl #10]	; <UNPREDICTABLE>
d0017ae0:	7071f507 	rsbsvc	pc, r1, r7, lsl #10
d0017ae4:	fee4f007 	cdp2	0, 14, cr15, cr4, cr7, {0}
d0017ae8:	f8c72307 			; <UNDEFINED> instruction: 0xf8c72307
d0017aec:	f88763e8 			; <UNDEFINED> instruction: 0xf88763e8
d0017af0:	f44f33ec 	vst2.<illegal width 64>	{d19-d22}, [pc :128], ip
d0017af4:	f8874300 			; <UNDEFINED> instruction: 0xf8874300
d0017af8:	f8c7b3ed 			; <UNDEFINED> instruction: 0xf8c7b3ed
d0017afc:	441e33fc 	ldrmi	r3, [lr], #-1020	; 0xfffffc04
d0017b00:	f8ca4b98 			; <UNDEFINED> instruction: 0xf8ca4b98
d0017b04:	f824621c 			; <UNDEFINED> instruction: 0xf824621c
d0017b08:	23018003 	movwcs	r8, #4099	; 0x1003
d0017b0c:	3009f804 	andcc	pc, r9, r4, lsl #16
d0017b10:	1c72e7af 	ldclne	7, cr14, [r2], #-700	; 0xfffffd44
d0017b14:	50e24620 	rscpl	r4, r2, r0, lsr #12
d0017b18:	04c6eb04 	strbeq	lr, [r6], #2820	; 0xb04
d0017b1c:	fcf4f7fd 	ldc2l	7, cr15, [r4], #1012	; 0x3f4
d0017b20:	4a934b92 	bmi	0xce4ea970
d0017b24:	f50550e0 			; <UNDEFINED> instruction: 0xf50550e0
d0017b28:	3502437f 	strcc	r4, [r2, #-895]	; 0xfffffc81
d0017b2c:	52a333fd 	adcpl	r3, r3, #-201326589	; 0xf4000003
d0017b30:	463ae791 			; <UNDEFINED> instruction: 0x463ae791
d0017b34:	46204631 			; <UNDEFINED> instruction: 0x46204631
d0017b38:	fe70f7f8 	mrc2	7, 3, pc, cr0, cr8, {7}
d0017b3c:	93001e03 	movwls	r1, #3587	; 0xe03
d0017b40:	6da3da0e 			; <UNDEFINED> instruction: 0x6da3da0e
d0017b44:	d1862b00 	orrle	r2, r6, r0, lsl #22
d0017b48:	447b4b9b 	ldrbtmi	r4, [fp], #-2971	; 0xfffff465
d0017b4c:	9b0165a3 	blls	0xd00711e0
d0017b50:	9b1265e3 	blls	0xd04b12e4
d0017b54:	9b026623 	blls	0xd00b13e8
d0017b58:	9b146663 	blls	0xd05314ec
d0017b5c:	e77a66a3 	ldrb	r6, [sl, -r3, lsr #13]!
d0017b60:	4631463a 			; <UNDEFINED> instruction: 0x4631463a
d0017b64:	f7f84620 			; <UNDEFINED> instruction: 0xf7f84620
d0017b68:	2800fdcf 	stmdacs	r0, {r0, r1, r2, r3, r6, r7, r8, sl, fp, ip, sp, lr, pc}
d0017b6c:	463adae9 	ldrtmi	sp, [sl], -r9, ror #21
d0017b70:	46204631 			; <UNDEFINED> instruction: 0x46204631
d0017b74:	fde8f7f8 	stc2l	7, cr15, [r8, #992]!	; 0x3e0
d0017b78:	dae22800 	ble	0xcf8a1b80
d0017b7c:	23389a00 	teqcs	r8, #0, 20
d0017b80:	4302fb03 	movwmi	pc, #11011	; 0x2b03	; <UNPREDICTABLE>
d0017b84:	5c9a4a7b 	vldmiapl	sl, {s8-s130}
d0017b88:	d1062a04 	tstle	r6, r4, lsl #20
d0017b8c:	2b006da3 	blcs	0xd0033220
d0017b90:	af61f47f 	svcge	0x0061f47f
d0017b94:	447b4b89 	ldrbtmi	r4, [fp], #-2953	; 0xfffff477
d0017b98:	4a77e7d8 	bmi	0xd1e11b00
d0017b9c:	92045c9b 	andls	r5, r4, #39680	; 0x9b00
d0017ba0:	d1782b04 	cmnle	r8, r4, lsl #22
d0017ba4:	23389a00 	teqcs	r8, #0, 20
d0017ba8:	4302fb03 	movwmi	pc, #11011	; 0x2b03	; <UNPREDICTABLE>
d0017bac:	5c9b4a73 	vldmiapl	fp, {s8-s122}
d0017bb0:	721af44f 	andsvc	pc, sl, #1325400064	; 0x4f000000
d0017bb4:	4303fb02 	movwmi	pc, #15106	; 0x3b02	; <UNPREDICTABLE>
d0017bb8:	3368f503 	msrcc	SPSR_f, #12582912	; 0xc00000
d0017bbc:	8028f8b3 	strhthi	pc, [r8], -r3	; <UNPREDICTABLE>
d0017bc0:	0f00f1b8 	svceq	0x0000f1b8
d0017bc4:	4f6ed006 	svcmi	0x006ed006
d0017bc8:	a007f854 	andge	pc, r7, r4, asr r8	; <UNPREDICTABLE>
d0017bcc:	0340f1ca 	movteq	pc, #458	; 0x1ca	; <UNPREDICTABLE>
d0017bd0:	d9354598 	ldmdble	r5!, {r3, r4, r7, r8, sl, lr}
d0017bd4:	f04f497a 			; <UNDEFINED> instruction: 0xf04f497a
d0017bd8:	46200a00 	strtmi	r0, [r0], -r0, lsl #20
d0017bdc:	f7f84479 			; <UNDEFINED> instruction: 0xf7f84479
d0017be0:	6da3fae3 			; <UNDEFINED> instruction: 0x6da3fae3
d0017be4:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0017be8:	4651af35 	uasxmi	sl, r1, r5
d0017bec:	f04f4620 			; <UNDEFINED> instruction: 0xf04f4620
d0017bf0:	f7fd0801 			; <UNDEFINED> instruction: 0xf7fd0801
d0017bf4:	f24bf8fd 	vtst.8	<illegal reg q15.5>, <illegal reg q13.5>, <illegal reg q14.5>
d0017bf8:	46204103 	strtmi	r4, [r0], -r3, lsl #2
d0017bfc:	f82ef7fd 			; <UNDEFINED> instruction: 0xf82ef7fd
d0017c00:	23389a00 	teqcs	r8, #0, 20
d0017c04:	4353495f 	cmpmi	r3, #1556480	; 0x17c000
d0017c08:	5c5118e2 	mrrcpl	8, 14, r1, r1, cr2	; <UNPREDICTABLE>
d0017c0c:	d0462904 	suble	r2, r6, r4, lsl #18
d0017c10:	27004e5d 	smlsdcs	r0, sp, lr, r4
d0017c14:	91acf8df 	ldrdls	pc, [ip, pc]!	; <UNPREDICTABLE>
d0017c18:	4b6b441e 	blmi	0xd1ae8c98
d0017c1c:	447b4491 	ldrbtmi	r4, [fp], #-1169	; 0xfffffb6f
d0017c20:	ee084426 	cdp	4, 0, cr4, cr8, cr6, {1}
d0017c24:	f8993a10 			; <UNDEFINED> instruction: 0xf8993a10
d0017c28:	428f1000 	addmi	r1, pc, #0
d0017c2c:	6da3d202 	sfmvs	f5, 1, [r3, #8]!
d0017c30:	d04e2b00 	suble	r2, lr, r0, lsl #22
d0017c34:	46204441 	strtmi	r4, [r0], -r1, asr #8
d0017c38:	fc9cf7fd 	ldc2	7, cr15, [ip], {253}	; 0xfd
d0017c3c:	e0324606 	eors	r4, r2, r6, lsl #12
d0017c40:	b188f8df 	ldrdlt	pc, [r8, pc]
d0017c44:	0900f04f 	stmdbeq	r0, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d0017c48:	44a34427 	strtmi	r4, [r3], #1063	; 0x427
d0017c4c:	2100683e 	tstcs	r0, lr, lsr r8
d0017c50:	0901f109 	stmdbeq	r1, {r0, r3, r8, ip, sp, lr, pc}
d0017c54:	93031c73 	movwls	r1, #15475	; 0x3c73
d0017c58:	f89b603b 			; <UNDEFINED> instruction: 0xf89b603b
d0017c5c:	93053000 	movwls	r3, #20480	; 0x5000
d0017c60:	fb032330 	blx	0xd00e092a
d0017c64:	461a4606 	ldrmi	r4, [sl], -r6, lsl #12
d0017c68:	16a4f506 	strtne	pc, [r4], r6, lsl #10
d0017c6c:	6034f206 	eorsvs	pc, r4, r6, lsl #4
d0017c70:	fe1ef007 	cdp2	0, 1, cr15, cr14, cr7, {0}
d0017c74:	45c89b05 	strbmi	r9, [r8, #2821]	; 0xb05
d0017c78:	3654f886 	ldrbcc	pc, [r4], -r6, lsl #17	; <UNPREDICTABLE>
d0017c7c:	030bf04f 	movweq	pc, #45135	; 0xb04f	; <UNPREDICTABLE>
d0017c80:	3655f886 	ldrbcc	pc, [r5], -r6, lsl #17	; <UNPREDICTABLE>
d0017c84:	4b41d8e2 	blmi	0xd108e014
d0017c88:	58e29903 	stmiapl	r2!, {r0, r1, r8, fp, ip, pc}^
d0017c8c:	bf844291 	svclt	0x00844291
d0017c90:	50e2460a 	rscpl	r4, r2, sl, lsl #12
d0017c94:	f04fe7a5 			; <UNDEFINED> instruction: 0xf04fe7a5
d0017c98:	46c20800 	strbmi	r0, [r2], r0, lsl #16
d0017c9c:	2600e7b0 			; <UNDEFINED> instruction: 0x2600e7b0
d0017ca0:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0017ca4:	4a4afe5d 	bmi	0xd12d7620
d0017ca8:	46202129 	strtmi	r2, [r0], -r9, lsr #2
d0017cac:	f7fb447a 			; <UNDEFINED> instruction: 0xf7fb447a
d0017cb0:	2800f8d4 	stmdacs	r0, {r2, r4, r6, r7, fp, ip, sp, lr, pc}
d0017cb4:	aecff43f 	mcrge	4, 6, pc, cr15, cr15, {1}	; <UNPREDICTABLE>
d0017cb8:	58e74b2b 	stmiapl	r7!, {r0, r1, r3, r5, r8, r9, fp, lr}^
d0017cbc:	6f00f5b7 	svcvs	0x0000f5b7
d0017cc0:	80a9f040 	adchi	pc, r9, r0, asr #32
d0017cc4:	2b006da3 	blcs	0xd0033358
d0017cc8:	aec5f47f 	mcrge	4, 6, pc, cr5, cr15, {3}	; <UNPREDICTABLE>
d0017ccc:	447b4b41 	ldrbtmi	r4, [fp], #-2881	; 0xfffff4bf
d0017cd0:	b12fe73c 			; <UNDEFINED> instruction: 0xb12fe73c
d0017cd4:	2a10ee18 	bcs	0xd045353c
d0017cd8:	4620212c 	strtmi	r2, [r0], -ip, lsr #2
d0017cdc:	f8bdf7fb 			; <UNDEFINED> instruction: 0xf8bdf7fb
d0017ce0:	bb01f816 	bllt	0xd0095d40
d0017ce4:	0f0df1bb 	svceq	0x000df1bb
d0017ce8:	7931d10a 	ldmdbvc	r1!, {r1, r3, r8, ip, lr, pc}
d0017cec:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0017cf0:	f24bfcd3 	vfma.f32	<illegal reg q15.5>, <illegal reg q13.5>, <illegal reg q1.5>
d0017cf4:	46204103 	strtmi	r4, [r0], -r3, lsl #2
d0017cf8:	f7fc3701 			; <UNDEFINED> instruction: 0xf7fc3701
d0017cfc:	e792ffaf 	ldr	pc, [r2, pc, lsr #31]
d0017d00:	0f0ef1bb 	svceq	0x000ef1bb
d0017d04:	7931d104 	ldmdbvc	r1!, {r2, r8, ip, lr, pc}
d0017d08:	f0004620 			; <UNDEFINED> instruction: 0xf0004620
d0017d0c:	e7f0f931 			; <UNDEFINED> instruction: 0xe7f0f931
d0017d10:	0f12f1bb 	svceq	0x0012f1bb
d0017d14:	7931d104 	ldmdbvc	r1!, {r2, r8, ip, lr, pc}
d0017d18:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0017d1c:	e7e8f90f 	strb	pc, [r8, pc, lsl #18]!	; <UNPREDICTABLE>
d0017d20:	0f13f1bb 	svceq	0x0013f1bb
d0017d24:	4620d103 	strtmi	sp, [r0], -r3, lsl #2
d0017d28:	f8a8f7fd 			; <UNDEFINED> instruction: 0xf8a8f7fd
d0017d2c:	f1bbe7e1 			; <UNDEFINED> instruction: 0xf1bbe7e1
d0017d30:	d1050f0a 	tstle	r5, sl, lsl #30
d0017d34:	21012204 	tstcs	r1, r4, lsl #4
d0017d38:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0017d3c:	e7d8faf7 			; <UNDEFINED> instruction: 0xe7d8faf7
d0017d40:	03fbf00b 	mvnseq	pc, #11
d0017d44:	d1632b02 	cmnle	r3, r2, lsl #22
d0017d48:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0017d4c:	2800ffed 	stmdacs	r0, {r0, r2, r3, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0017d50:	6ae2d1cf 	bvs	0xcf8cc494
d0017d54:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d0017d58:	d03f429a 	mlasle	pc, sl, r2, r4	; <UNPREDICTABLE>
d0017d5c:	4479491e 	ldrbtmi	r4, [r9], #-2334	; 0xfffff6e2
d0017d60:	bf00e696 	svclt	0x0000e696
d0017d64:	0014b29c 	mulseq	r4, ip, r2
d0017d68:	00147628 	andseq	r7, r4, r8, lsr #12
d0017d6c:	00143628 	andseq	r3, r4, r8, lsr #12
d0017d70:	0014362c 	andseq	r3, r4, ip, lsr #12
d0017d74:	0013fe50 	andseq	pc, r3, r0, asr lr	; <UNPREDICTABLE>
d0017d78:	0013fe4b 	andseq	pc, r3, fp, asr #28
d0017d7c:	0013fe4e 	andseq	pc, r3, lr, asr #28
d0017d80:	00149234 	andseq	r9, r4, r4, lsr r2
d0017d84:	0013fe49 	andseq	pc, r3, r9, asr #28
d0017d88:	0013fe4f 	andseq	pc, r3, pc, asr #28
d0017d8c:	00149238 	andseq	r9, r4, r8, lsr r2
d0017d90:	fffffe5c 			; <UNDEFINED> instruction: 0xfffffe5c
d0017d94:	fffffe48 			; <UNDEFINED> instruction: 0xfffffe48
d0017d98:	fffffe44 			; <UNDEFINED> instruction: 0xfffffe44
d0017d9c:	fffffe23 			; <UNDEFINED> instruction: 0xfffffe23
d0017da0:	fffffe18 			; <UNDEFINED> instruction: 0xfffffe18
d0017da4:	fffffe16 			; <UNDEFINED> instruction: 0xfffffe16
d0017da8:	fffffdda 			; <UNDEFINED> instruction: 0xfffffdda
d0017dac:	0014b29e 	mulseq	r4, lr, r2
d0017db0:	fffffde6 			; <UNDEFINED> instruction: 0xfffffde6
d0017db4:	fffffd8c 			; <UNDEFINED> instruction: 0xfffffd8c
d0017db8:	fffffd42 			; <UNDEFINED> instruction: 0xfffffd42
d0017dbc:	fffffd20 			; <UNDEFINED> instruction: 0xfffffd20
d0017dc0:	fffffd06 			; <UNDEFINED> instruction: 0xfffffd06
d0017dc4:	0013fe48 	andseq	pc, r3, r8, asr #28
d0017dc8:	fffffcf6 			; <UNDEFINED> instruction: 0xfffffcf6
d0017dcc:	0014923c 	andseq	r9, r4, ip, lsr r2
d0017dd0:	fffffcb5 			; <UNDEFINED> instruction: 0xfffffcb5
d0017dd4:	fffffba6 			; <UNDEFINED> instruction: 0xfffffba6
d0017dd8:	fffffbd5 			; <UNDEFINED> instruction: 0xfffffbd5
d0017ddc:	462069a1 	strtmi	r6, [r0], -r1, lsr #19
d0017de0:	f7f869e2 			; <UNDEFINED> instruction: 0xf7f869e2
d0017de4:	1e01fc91 	mcrne	12, 0, pc, cr1, cr1, {4}	; <UNPREDICTABLE>
d0017de8:	2330dbb8 	teqcs	r0, #184, 22	; 0x2e000
d0017dec:	fb039103 	blx	0xd00fc202
d0017df0:	f5034301 			; <UNDEFINED> instruction: 0xf5034301
d0017df4:	f89313a4 			; <UNDEFINED> instruction: 0xf89313a4
d0017df8:	455b3655 	ldrbmi	r3, [fp, #-1621]	; 0xfffff9ab
d0017dfc:	4620d1ae 	strtmi	sp, [r0], -lr, lsr #3
d0017e00:	f802f7fb 			; <UNDEFINED> instruction: 0xf802f7fb
d0017e04:	99032200 	stmdbls	r3, {r9, sp}
d0017e08:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0017e0c:	e770ffbf 			; <UNDEFINED> instruction: 0xe770ffbf
d0017e10:	46112201 	ldrmi	r2, [r1], -r1, lsl #4
d0017e14:	1c7ae790 	ldclne	7, cr14, [sl], #-576	; 0xfffffdc0
d0017e18:	eb044620 	bl	0xd01296a0
d0017e1c:	50e207c7 	rscpl	r0, r2, r7, asr #15
d0017e20:	fb72f7fd 	blx	0xd1cd5e1e
d0017e24:	9a004b18 	bls	0xd002aa8c
d0017e28:	330450f8 	movwcc	r5, #16632	; 0x40f8
d0017e2c:	b12e52fa 	strdlt	r5, [lr, -sl]!
d0017e30:	4130f446 	teqmi	r0, r6, asr #8	; <UNPREDICTABLE>
d0017e34:	b2894620 	addlt	r4, r9, #32, 12	; 0x2000000
d0017e38:	ff10f7fc 			; <UNDEFINED> instruction: 0xff10f7fc
d0017e3c:	26389b00 	ldrtcs	r9, [r8], -r0, lsl #22
d0017e40:	4603fb06 	strmi	pc, [r3], -r6, lsl #22
d0017e44:	5cf39b04 	vldmiapl	r3!, {d25-d26}
d0017e48:	d10b2b04 	tstle	fp, r4, lsl #22
d0017e4c:	46204651 			; <UNDEFINED> instruction: 0x46204651
d0017e50:	ffcef7fc 			; <UNDEFINED> instruction: 0xffcef7fc
d0017e54:	25064b0d 	strcs	r4, [r6, #-2829]	; 0xfffff4f3
d0017e58:	f5035cf2 			; <UNDEFINED> instruction: 0xf5035cf2
d0017e5c:	33f64313 	mvnscc	r4, #1275068416	; 0x4c000000
d0017e60:	e5f850e2 	ldrb	r5, [r8, #226]!	; 0xe2
d0017e64:	d1072b05 	tstle	r7, r5, lsl #22
d0017e68:	25034b08 	strcs	r4, [r3, #-2824]	; 0xfffff4f8
d0017e6c:	f5035cf2 			; <UNDEFINED> instruction: 0xf5035cf2
d0017e70:	33f64313 	mvnscc	r4, #1275068416	; 0x4c000000
d0017e74:	e5ee50e2 	strb	r5, [lr, #226]!	; 0xe2
d0017e78:	f43f2b01 			; <UNDEFINED> instruction: 0xf43f2b01
d0017e7c:	2b03adeb 	blcs	0xd0103630
d0017e80:	2504bf08 	strcs	fp, [r4, #-3848]	; 0xfffff0f8
d0017e84:	bf00e5e7 	svclt	0x0000e5e7
d0017e88:	00143628 	andseq	r3, r4, r8, lsr #12
d0017e8c:	0013fe4e 	andseq	pc, r3, lr, asr #28

Disassembly of section .text.struct_pointer_value:

d0017f70 <.text.struct_pointer_value>:
d0017f70:	f2406ac2 	vpmax.s8	q11, q8, q1
d0017f74:	429a1301 	addsmi	r1, sl, #67108864	; 0x4000000
d0017f78:	4ff0e92d 	svcmi	0x00f0e92d
d0017f7c:	460f4604 	strmi	r4, [pc], -r4, lsl #12
d0017f80:	8b02ed2d 	blhi	0xd00d343c
d0017f84:	d14ab087 	smlalbble	fp, sl, r7, r0
d0017f88:	2d286cc5 	stccs	12, cr6, [r8, #-788]!	; 0xfffffcec
d0017f8c:	6b43d147 	blvs	0xd110c4b0
d0017f90:	b024f8d0 	ldrdlt	pc, [r4], -r0	; <UNPREDICTABLE>
d0017f94:	a028f8d0 	ldrdge	pc, [r8], -r0	; <UNPREDICTABLE>
d0017f98:	9030f890 	mlasls	r0, r0, r8, pc	; <UNPREDICTABLE>
d0017f9c:	e9d09304 	ldmib	r0, {r2, r8, r9, ip, pc}^
d0017fa0:	f7fa6806 			; <UNDEFINED> instruction: 0xf7fa6806
d0017fa4:	4ac8ff31 	bmi	0xcf257c70
d0017fa8:	46204629 	strtmi	r4, [r0], -r9, lsr #12
d0017fac:	f7fa447a 			; <UNDEFINED> instruction: 0xf7fa447a
d0017fb0:	b1a8ff54 			; <UNDEFINED> instruction: 0xb1a8ff54
d0017fb4:	46429b04 	strbmi	r9, [r2], -r4, lsl #22
d0017fb8:	46204631 			; <UNDEFINED> instruction: 0x46204631
d0017fbc:	465b9302 	ldrbmi	r9, [fp], -r2, lsl #6
d0017fc0:	9004f8cd 	andls	pc, r4, sp, asr #17
d0017fc4:	a000f8cd 	andge	pc, r0, sp, asr #17
d0017fc8:	fce0f7ff 	stc2l	7, cr15, [r0], #1020	; 0x3fc
d0017fcc:	46054abf 			; <UNDEFINED> instruction: 0x46054abf
d0017fd0:	447a4641 	ldrbtmi	r4, [sl], #-1601	; 0xfffff9bf
d0017fd4:	f7f84630 			; <UNDEFINED> instruction: 0xf7f84630
d0017fd8:	b130fc4d 	teqlt	r0, sp, asr #24	; <UNPREDICTABLE>
d0017fdc:	d1122d03 	tstle	r2, r3, lsl #26
d0017fe0:	ecbdb007 	ldc	0, cr11, [sp], #28
d0017fe4:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d0017fe8:	4ab98ff0 	bmi	0xcee7bfb0
d0017fec:	46304641 	ldrtmi	r4, [r0], -r1, asr #12
d0017ff0:	f7f8447a 			; <UNDEFINED> instruction: 0xf7f8447a
d0017ff4:	2800fc3f 	stmdacs	r0, {r0, r1, r2, r3, r4, r5, sl, fp, ip, sp, lr, pc}
d0017ff8:	2d03d1f0 	stfcsd	f5, [r3, #-960]	; 0xfffffc40
d0017ffc:	4bb1d103 	blmi	0xcec8c410
d0018000:	42bb58e3 	adcsmi	r5, fp, #14876672	; 0xe30000
d0018004:	6da3e7eb 	stcvs	7, cr14, [r3, #940]!	; 0x3ac
d0018008:	d1e92b00 	mvnle	r2, r0, lsl #22
d001800c:	447b4bb1 	ldrbtmi	r4, [fp], #-2993	; 0xfffff44f
d0018010:	3b16e9c4 	blcc	0xd05d2728
d0018014:	e9c49b04 	stmib	r4, {r2, r8, r9, fp, ip, pc}^
d0018018:	66a3a918 	ssatvs	sl, #4, r8, lsl #18
d001801c:	212ae7e0 			; <UNDEFINED> instruction: 0x212ae7e0
d0018020:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0018024:	2800ff0c 	stmdacs	r0, {r2, r3, r8, r9, sl, fp, ip, sp, lr, pc}
d0018028:	6ae2d03c 	bvs	0xcf8cc120
d001802c:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d0018030:	9024f8d4 	ldrdls	pc, [r4], -r4	; <UNPREDICTABLE>
d0018034:	f8d4429a 			; <UNDEFINED> instruction: 0xf8d4429a
d0018038:	f8948028 			; <UNDEFINED> instruction: 0xf8948028
d001803c:	6b656030 	blvs	0xd1970104
d0018040:	6da3d00a 	stcvs	0, cr13, [r3, #40]!	; 0x28
d0018044:	d1cb2b00 	bicle	r2, fp, r0, lsl #22
d0018048:	66a54ba3 	strtvs	r4, [r5], r3, lsr #23
d001804c:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0018050:	e9c48618 	stmib	r4, {r3, r4, r9, sl, pc}^
d0018054:	e7c33916 	bfi	r3, r6, (invalid: 18:3)
d0018058:	1206e9d4 	andne	lr, r6, #212, 18	; 0x350000
d001805c:	f7f84620 			; <UNDEFINED> instruction: 0xf7f84620
d0018060:	f1b0fb53 			; <UNDEFINED> instruction: 0xf1b0fb53
d0018064:	dbec0a00 	blle	0xcfb1a86c
d0018068:	fb032330 	blx	0xd00e0d32
d001806c:	f503430a 			; <UNDEFINED> instruction: 0xf503430a
d0018070:	f89313a4 			; <UNDEFINED> instruction: 0xf89313a4
d0018074:	2a122655 	bcs	0xd04a19d0
d0018078:	f893d1e3 			; <UNDEFINED> instruction: 0xf893d1e3
d001807c:	42bb3656 	adcsmi	r3, fp, #90177536	; 0x5600000
d0018080:	4620d1df 			; <UNDEFINED> instruction: 0x4620d1df
d0018084:	fec0f7fa 	mcr2	7, 6, pc, cr0, cr10, {7}	; <UNPREDICTABLE>
d0018088:	22004651 	andcs	r4, r0, #84934656	; 0x5100000
d001808c:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0018090:	f44ffe7d 			; <UNDEFINED> instruction: 0xf44ffe7d
d0018094:	b00741d0 	ldrdlt	r4, [r7], -r0
d0018098:	8b02ecbd 	blhi	0xd00d3394
d001809c:	4ff0e8bd 	svcmi	0x00f0e8bd
d00180a0:	bddcf7fc 	ldcllt	7, cr15, [ip, #1008]	; 0x3f0
d00180a4:	46202126 	strtmi	r2, [r0], -r6, lsr #2
d00180a8:	fec9f7fa 	mcr2	7, 6, pc, cr9, cr10, {7}	; <UNPREDICTABLE>
d00180ac:	f2406ae3 	vpmax.s8	q11, q8, <illegal reg q9.5>
d00180b0:	46051201 	strmi	r1, [r5], -r1, lsl #4
d00180b4:	f0404293 			; <UNDEFINED> instruction: 0xf0404293
d00180b8:	69a38157 	stmibvs	r3!, {r0, r1, r2, r4, r6, r8, pc}
d00180bc:	69e64620 	stmibvs	r6!, {r5, r9, sl, lr}^
d00180c0:	3a10ee08 	bcc	0xd04538e8
d00180c4:	46326b63 	ldrtmi	r6, [r2], -r3, ror #22
d00180c8:	b024f8d4 	ldrdlt	pc, [r4], -r4	; <UNPREDICTABLE>
d00180cc:	1a10ee18 	bne	0xd0453934
d00180d0:	a028f8d4 	ldrdge	pc, [r8], -r4	; <UNPREDICTABLE>
d00180d4:	9030f894 	mlasls	r0, r4, r8, pc	; <UNPREDICTABLE>
d00180d8:	f7f89304 			; <UNDEFINED> instruction: 0xf7f89304
d00180dc:	f1b0fb15 			; <UNDEFINED> instruction: 0xf1b0fb15
d00180e0:	da220800 	ble	0xd089a0e8
d00180e4:	ee184632 	mrc	6, 0, r4, cr8, cr2, {1}
d00180e8:	46201a10 			; <UNDEFINED> instruction: 0x46201a10
d00180ec:	fb2cf7f8 	blx	0xd0b560d6
d00180f0:	b9ed4603 	stmiblt	sp!, {r0, r1, r9, sl, lr}^
d00180f4:	46314a79 			; <UNDEFINED> instruction: 0x46314a79
d00180f8:	0a10ee18 	beq	0xd0453960
d00180fc:	447a9305 	ldrbtmi	r9, [sl], #-773	; 0xfffffcfb
d0018100:	fbb8f7f8 	blx	0xcee560ea
d0018104:	b1989b05 	orrslt	r9, r8, r5, lsl #22
d0018108:	0f00f1b8 	svceq	0x0000f1b8
d001810c:	2b00da10 	blcs	0xd004e954
d0018110:	4620da0e 	strtmi	sp, [r0], -lr, lsl #20
d0018114:	fe78f7fa 	mrc2	7, 3, pc, cr8, cr10, {7}
d0018118:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d001811c:	ecbdb007 	ldc	0, cr11, [sp], #28
d0018120:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d0018124:	f7fc4ff0 			; <UNDEFINED> instruction: 0xf7fc4ff0
d0018128:	f04fbdf8 			; <UNDEFINED> instruction: 0xf04fbdf8
d001812c:	e7e033ff 			; <UNDEFINED> instruction: 0xe7e033ff
d0018130:	93054620 	movwls	r4, #22048	; 0x5620
d0018134:	fe68f7fa 	mcr2	7, 3, pc, cr8, cr10, {7}	; <UNPREDICTABLE>
d0018138:	0f00f1b8 	svceq	0x0000f1b8
d001813c:	db229b05 	blle	0xd08bed58
d0018140:	fb012130 	blx	0xd006060a
d0018144:	f5014108 			; <UNDEFINED> instruction: 0xf5014108
d0018148:	f89111a4 			; <UNDEFINED> instruction: 0xf89111a4
d001814c:	f8912655 			; <UNDEFINED> instruction: 0xf8912655
d0018150:	f0026656 			; <UNDEFINED> instruction: 0xf0026656
d0018154:	290d01fd 	stmdbcs	sp, {r0, r2, r3, r4, r5, r6, r7, r8}
d0018158:	4641d124 	strbmi	sp, [r1], -r4, lsr #2
d001815c:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0018160:	212efe47 	msrcs	LR_fiq, r7
d0018164:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0018168:	2800fe6a 	stmdacs	r0, {r1, r3, r5, r6, r9, sl, fp, ip, sp, lr, pc}
d001816c:	2d00d060 	stccs	0, cr13, [r0, #-384]	; 0xfffffe80
d0018170:	463ad04a 	ldrtmi	sp, [sl], -sl, asr #32
d0018174:	46204631 			; <UNDEFINED> instruction: 0x46204631
d0018178:	ecbdb007 	ldc	0, cr11, [sp], #28
d001817c:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d0018180:	f7fd4ff0 			; <UNDEFINED> instruction: 0xf7fd4ff0
d0018184:	2b00bcd5 	blcs	0xd00474e0
d0018188:	213cdb5d 	teqcs	ip, sp, asr fp
d001818c:	4103fb01 	tstmi	r3, r1, lsl #22	; <UNPREDICTABLE>
d0018190:	315ff501 	cmpcc	pc, r1, lsl #10	; <UNPREDICTABLE>
d0018194:	23ecf891 	mvncs	pc, #9502720	; 0x910000
d0018198:	63eef891 	mvnvs	pc, #9502720	; 0x910000
d001819c:	01fdf002 	mvnseq	pc, r2
d00181a0:	d026290d 	eorle	r2, r6, sp, lsl #18
d00181a4:	0110f1a2 	tsteq	r0, r2, lsr #3	; <UNPREDICTABLE>
d00181a8:	f2002901 	vmla.i8	d2, d0, d1
d00181ac:	f1b880a5 			; <UNDEFINED> instruction: 0xf1b880a5
d00181b0:	db4b0f00 	blle	0xd12dbdb8
d00181b4:	46204641 	strtmi	r4, [r0], -r1, asr #12
d00181b8:	fe1af7fc 	mrc2	7, 0, pc, cr10, cr12, {7}
d00181bc:	2b5b6ae3 	blcs	0xd16f2d50
d00181c0:	2301d174 	movwcs	sp, #4468	; 0x1174
d00181c4:	d04c2d00 	suble	r2, ip, r0, lsl #26
d00181c8:	22004631 	andcs	r4, r0, #51380224	; 0x3100000
d00181cc:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d00181d0:	212ef98b 	smlawbcs	lr, fp, r9, pc	; <UNPREDICTABLE>
d00181d4:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d00181d8:	2800fe32 	stmdacs	r0, {r1, r4, r5, r9, sl, fp, ip, sp, lr, pc}
d00181dc:	42b7d1c9 	adcsmi	sp, r7, #1073741874	; 0x40000032
d00181e0:	aefef43f 	mrcge	4, 7, APSR_nzcv, cr14, cr15, {1}
d00181e4:	2b006da3 	blcs	0xd0033878
d00181e8:	aefaf47f 	mrcge	4, 7, APSR_nzcv, cr10, cr15, {3}
d00181ec:	447b4b3c 	ldrbtmi	r4, [fp], #-2876	; 0xfffff4c4
d00181f0:	4620e70e 	strtmi	lr, [r0], -lr, lsl #14
d00181f4:	2101461a 	tstcs	r1, sl, lsl r6
d00181f8:	fea6f7fc 	mcr2	7, 5, pc, cr6, cr12, {7}	; <UNPREDICTABLE>
d00181fc:	6108f244 	tstvs	r8, r4, asr #4	; <UNPREDICTABLE>
d0018200:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0018204:	e7acfd2b 	str	pc, [ip, fp, lsr #26]!
d0018208:	462a462b 	strtmi	r4, [sl], -fp, lsr #12
d001820c:	46204631 			; <UNDEFINED> instruction: 0x46204631
d0018210:	f964f000 			; <UNDEFINED> instruction: 0xf964f000
d0018214:	d1042803 	tstle	r4, r3, lsl #16
d0018218:	58e34b2a 	stmiapl	r3!, {r1, r3, r5, r8, r9, fp, lr}^
d001821c:	f43f42bb 			; <UNDEFINED> instruction: 0xf43f42bb
d0018220:	6da3aedf 	stcvs	14, cr10, [r3, #892]!	; 0x37c
d0018224:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0018228:	4b2eaedb 	blmi	0xd0bc3d9c
d001822c:	e6ef447b 	uxtb	r4, fp, ror #8
d0018230:	42b7b115 	adcsmi	fp, r7, #1073741829	; 0x40000005
d0018234:	aed4f43f 	mrcge	4, 6, APSR_nzcv, cr4, cr15, {1}
d0018238:	2b006da3 	blcs	0xd00338cc
d001823c:	aed0f47f 	mrcge	4, 6, APSR_nzcv, cr0, cr15, {3}
d0018240:	447b4b29 	ldrbtmi	r4, [fp], #-2857	; 0xfffff4d7
d0018244:	26ffe6e4 	ldrbtcs	lr, [pc], r4, ror #13
d0018248:	e7ab220b 	str	r2, [fp, fp, lsl #4]!
d001824c:	461a4620 	ldrmi	r4, [sl], -r0, lsr #12
d0018250:	f7fc2101 			; <UNDEFINED> instruction: 0xf7fc2101
d0018254:	f244fe79 			; <UNDEFINED> instruction: 0xf244fe79
d0018258:	46206108 	strtmi	r6, [r0], -r8, lsl #2
d001825c:	fcfef7fc 	ldc2l	7, cr15, [lr], #1008	; 0x3f0
d0018260:	4631e7ac 	ldrtmi	lr, [r1], -ip, lsr #15
d0018264:	4620462a 	strtmi	r4, [r0], -sl, lsr #12
d0018268:	f93ef7ff 			; <UNDEFINED> instruction: 0xf93ef7ff
d001826c:	4620212e 	strtmi	r2, [r0], -lr, lsr #2
d0018270:	fde5f7fa 	stc2l	7, cr15, [r5, #1000]!	; 0x3e8
d0018274:	462bb198 			; <UNDEFINED> instruction: 0x462bb198
d0018278:	4631462a 	ldrtmi	r4, [r1], -sl, lsr #12
d001827c:	f0004620 			; <UNDEFINED> instruction: 0xf0004620
d0018280:	2803f92d 	stmdacs	r3, {r0, r2, r3, r5, r8, fp, ip, sp, lr, pc}
d0018284:	4b0fd104 	blmi	0xd040c69c
d0018288:	42bb58e3 	adcsmi	r5, fp, #14876672	; 0xe30000
d001828c:	aea8f43f 	mcrge	4, 5, pc, cr8, cr15, {1}	; <UNPREDICTABLE>
d0018290:	2b006da3 	blcs	0xd0033924
d0018294:	aea4f47f 	mcrge	4, 5, pc, cr4, cr15, {3}	; <UNPREDICTABLE>
d0018298:	447b4b14 	ldrbtmi	r4, [fp], #-2836	; 0xfffff4ec
d001829c:	6da3e6b8 	stcvs	6, cr14, [r3, #736]!	; 0x2e0
d00182a0:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d00182a4:	4b12ae9d 	blmi	0xd04c3d20
d00182a8:	e6b1447b 	sxtah	r4, r1, fp, ror #8
d00182ac:	42b7b915 	adcsmi	fp, r7, #344064	; 0x54000
d00182b0:	ae96f43f 	mrcge	4, 4, APSR_nzcv, cr6, cr15, {1}
d00182b4:	2b006da3 	blcs	0xd0033948
d00182b8:	ae92f47f 	mrcge	4, 4, APSR_nzcv, cr2, cr15, {3}
d00182bc:	447b4b0d 	ldrbtmi	r4, [fp], #-2829	; 0xfffff4f3
d00182c0:	bf00e6a6 	svclt	0x0000e6a6
d00182c4:	00149244 	andseq	r9, r4, r4, asr #4
d00182c8:	fffffee0 			; <UNDEFINED> instruction: 0xfffffee0
d00182cc:	fffff82e 			; <UNDEFINED> instruction: 0xfffff82e
d00182d0:	fffff81c 			; <UNDEFINED> instruction: 0xfffff81c
d00182d4:	fffffe9f 			; <UNDEFINED> instruction: 0xfffffe9f
d00182d8:	fffffe8e 			; <UNDEFINED> instruction: 0xfffffe8e
d00182dc:	ffffcc20 			; <UNDEFINED> instruction: 0xffffcc20
d00182e0:	ffffd90f 			; <UNDEFINED> instruction: 0xffffd90f
d00182e4:	ffffd8d1 			; <UNDEFINED> instruction: 0xffffd8d1
d00182e8:	ffffd8bb 			; <UNDEFINED> instruction: 0xffffd8bb
d00182ec:	ffffd863 			; <UNDEFINED> instruction: 0xffffd863
d00182f0:	fffffc60 			; <UNDEFINED> instruction: 0xfffffc60
d00182f4:	ffffd83f 			; <UNDEFINED> instruction: 0xffffd83f
d00182f8:	d12e2a0e 			; <UNDEFINED> instruction: 0xd12e2a0e
d00182fc:	0f00f1b8 	svceq	0x0000f1b8
d0018300:	4641db2b 	strbmi	sp, [r1], -fp, lsr #22
d0018304:	46202200 	strtmi	r2, [r0], -r0, lsl #4
d0018308:	fd40f7fc 	stc2l	7, cr15, [r0, #-1008]	; 0xfffffc10
d001830c:	7191f44f 	orrsvc	pc, r1, pc, asr #8
d0018310:	fd95f7fa 	ldc2	7, cr15, [r5, #1000]	; 0x3e8
d0018314:	2d00b1b0 	stfcsd	f3, [r0, #-704]	; 0xfffffd40
d0018318:	af2bf47f 	svcge	0x002bf47f
d001831c:	462a462b 	strtmi	r4, [sl], -fp, lsr #12
d0018320:	46204631 			; <UNDEFINED> instruction: 0x46204631
d0018324:	f8daf000 			; <UNDEFINED> instruction: 0xf8daf000
d0018328:	d1042803 	tstle	r4, r3, lsl #16
d001832c:	58e34b18 	stmiapl	r3!, {r3, r4, r8, r9, fp, lr}^
d0018330:	f43f42bb 			; <UNDEFINED> instruction: 0xf43f42bb
d0018334:	6da3ae55 	stcvs	14, cr10, [r3, #340]!	; 0x154
d0018338:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001833c:	4b15ae51 	blmi	0xd0583c88
d0018340:	e665447b 			; <UNDEFINED> instruction: 0xe665447b
d0018344:	42b7b915 	adcsmi	fp, r7, #344064	; 0x54000
d0018348:	ae4af43f 	mcrge	4, 2, pc, cr10, cr15, {1}	; <UNPREDICTABLE>
d001834c:	2b006da3 	blcs	0xd00339e0
d0018350:	ae46f47f 	mcrge	4, 2, pc, cr6, cr15, {3}	; <UNPREDICTABLE>
d0018354:	447b4b10 	ldrbtmi	r4, [fp], #-2832	; 0xfffff4f0
d0018358:	6da3e65a 	stcvs	6, cr14, [r3, #360]!	; 0x168
d001835c:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0018360:	4b0eae3f 	blmi	0xd03c3c64
d0018364:	e653447b 			; <UNDEFINED> instruction: 0xe653447b
d0018368:	f5a3b938 			; <UNDEFINED> instruction: 0xf5a3b938
d001836c:	2b017381 	blcs	0xd0075178
d0018370:	6a23d803 	bvs	0xd090e384
d0018374:	f43f2b00 			; <UNDEFINED> instruction: 0xf43f2b00
d0018378:	4909aecc 	stmdbmi	r9, {r2, r3, r6, r7, r9, sl, fp, sp, pc}
d001837c:	44794620 	ldrbtmi	r4, [r9], #-1568	; 0xfffff9e0
d0018380:	ecbdb007 	ldc	0, cr11, [sp], #28
d0018384:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d0018388:	f7f74ff0 			; <UNDEFINED> instruction: 0xf7f74ff0
d001838c:	bf00bf0d 	svclt	0x0000bf0d
d0018390:	00149244 	andseq	r9, r4, r4, asr #4
d0018394:	ffffd7bd 			; <UNDEFINED> instruction: 0xffffd7bd
d0018398:	ffffd7a7 			; <UNDEFINED> instruction: 0xffffd7a7
d001839c:	ffffd799 			; <UNDEFINED> instruction: 0xffffd799
d00183a0:	fffffbb4 			; <UNDEFINED> instruction: 0xfffffbb4

Disassembly of section .text.struct_member:

d00184dc <.text.struct_member>:
d00184dc:	4ff0e92d 	svcmi	0x00f0e92d
d00184e0:	4bbf461d 	blmi	0xcefe9d5c
d00184e4:	447b4604 	ldrbtmi	r4, [fp], #-1540	; 0xfffff9fc
d00184e8:	8b02ed2d 	blhi	0xd00d39a4
d00184ec:	3a90ee08 	bcc	0xce453d14
d00184f0:	9103b087 	smlabbls	r3, r7, r0, fp
d00184f4:	69a39204 	stmibvs	r3!, {r2, r9, ip, pc}
d00184f8:	2a90ee18 	bcs	0xce453d60
d00184fc:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d0018500:	ee084620 	cfmadd32	mvax1, mvfx4, mvfx8, mvfx0
d0018504:	69e33a10 	stmibvs	r3!, {r4, r9, fp, ip, sp}^
d0018508:	a024f8d4 	ldrdge	pc, [r4], -r4	; <UNPREDICTABLE>
d001850c:	f8d49301 			; <UNDEFINED> instruction: 0xf8d49301
d0018510:	f8949028 			; <UNDEFINED> instruction: 0xf8949028
d0018514:	6b678030 	blvs	0xd19f85dc
d0018518:	fc9ff7fa 	ldc2	7, cr15, [pc], {250}	; 0xfa
d001851c:	b9089b01 	stmdblt	r8, {r0, r8, r9, fp, ip, pc}
d0018520:	e02e2500 	eor	r2, lr, r0, lsl #10
d0018524:	f44f9a03 	vst1.8	{d25-d26}, [pc], r3
d0018528:	fb01711a 	blx	0xd007499a
d001852c:	f50bfb02 			; <UNDEFINED> instruction: 0xf50bfb02
d0018530:	44a33267 	strtmi	r3, [r3], #615	; 0x267
d0018534:	72f4f502 	rscsvc	pc, r4, #8388608	; 0x800000
d0018538:	3b68f50b 	blcc	0xd1a5596c
d001853c:	18a29202 	stmiane	r2!, {r1, r9, ip, pc}
d0018540:	22004616 	andcs	r4, r0, #23068672	; 0x1600000
d0018544:	f89b9201 			; <UNDEFINED> instruction: 0xf89b9201
d0018548:	9901202a 	stmdbls	r1, {r1, r3, r5, sp}
d001854c:	d81e428a 	ldmdale	lr, {r1, r3, r7, r9, lr}
d0018550:	f44f9b03 			; <UNDEFINED> instruction: 0xf44f9b03
d0018554:	fb02721a 	blx	0xd00b4dc6
d0018558:	9a014103 	bls	0xd006896c
d001855c:	3168f501 	msrcc	SPSR_f, r1, lsl #10
d0018560:	302af891 	mlacc	sl, r1, r8, pc	; <UNPREDICTABLE>
d0018564:	d1244293 			; <UNDEFINED> instruction: 0xd1244293
d0018568:	302bf891 	mlacc	fp, r1, r8, pc	; <UNPREDICTABLE>
d001856c:	4b9db9f3 	blmi	0xce786d40
d0018570:	6da5447b 	cfstrsvs	mvf4, [r5, #492]!	; 0x1ec
d0018574:	d1d32d00 	bicsle	r2, r3, r0, lsl #26
d0018578:	e9c466a7 	stmib	r4, {r0, r1, r2, r5, r7, r9, sl, sp, lr}^
d001857c:	e9c43a16 	stmib	r4, {r1, r2, r4, r9, fp, ip, sp}^
d0018580:	46289818 			; <UNDEFINED> instruction: 0x46289818
d0018584:	ecbdb007 	ldc	0, cr11, [sp], #28
d0018588:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d001858c:	68718ff0 	ldmdavs	r1!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}^
d0018590:	2a10ee18 	bcs	0xd0453df8
d0018594:	0b24f856 	bleq	0xd09566f4
d0018598:	f7f89305 			; <UNDEFINED> instruction: 0xf7f89305
d001859c:	9b05f83f 	blls	0xd01966a0
d00185a0:	d1d52800 	bicsle	r2, r5, r0, lsl #16
d00185a4:	32019a01 	andcc	r9, r1, #4096	; 0x1000
d00185a8:	e7cc9201 	strb	r9, [ip, r1, lsl #4]
d00185ac:	447b4b8e 	ldrbtmi	r4, [fp], #-2958	; 0xfffff472
d00185b0:	2324e7df 			; <UNDEFINED> instruction: 0x2324e7df
d00185b4:	99019a02 	stmdbls	r1, {r1, r9, fp, ip, pc}
d00185b8:	2601fb03 	strcs	pc, [r1], -r3, lsl #22
d00185bc:	8c5a19a3 	mrrchi	9, 10, r1, sl, cr3	; <UNPREDICTABLE>
d00185c0:	6020f893 	mlavs	r0, r3, r8, pc	; <UNPREDICTABLE>
d00185c4:	b021f893 	mlalt	r1, r3, r8, pc	; <UNPREDICTABLE>
d00185c8:	2101b14a 	tstcs	r1, sl, asr #2
d00185cc:	00924620 	addseq	r4, r2, r0, lsr #12
d00185d0:	fb64f7fc 	blx	0xd19565ca
d00185d4:	51c2f44f 	bicpl	pc, r2, pc, asr #8
d00185d8:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d00185dc:	f1bbfb3f 			; <UNDEFINED> instruction: 0xf1bbfb3f
d00185e0:	d06a0f00 	rsble	r0, sl, r0, lsl #30
d00185e4:	7191f44f 	orrsvc	pc, r1, pc, asr #8
d00185e8:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d00185ec:	b170fc28 	cmnlt	r0, r8, lsr #24	; <UNPREDICTABLE>
d00185f0:	d1052eff 	strdle	r2, [r5, -pc]
d00185f4:	2d006da5 	stccs	13, cr6, [r0, #-660]	; 0xfffffd6c
d00185f8:	4b7cd192 	blmi	0xd1f4cc48
d00185fc:	e7bb447b 			; <UNDEFINED> instruction: 0xe7bb447b
d0018600:	41d0f44f 	bicsmi	pc, r0, pc, asr #8
d0018604:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0018608:	9603fb29 	strls	pc, [r3], -r9, lsr #22
d001860c:	6ae3e773 	bvs	0xcf9123e0
d0018610:	d10b2b2e 	tstle	fp, lr, lsr #22
d0018614:	b10b6da3 	smlatblt	fp, r3, sp, r6
d0018618:	e7b22503 	ldr	r2, [r2, r3, lsl #10]!
d001861c:	447b4b74 	ldrbtmi	r4, [fp], #-2932	; 0xfffff48c
d0018620:	e9c466a7 	stmib	r4, {r0, r1, r2, r5, r7, r9, sl, sp, lr}^
d0018624:	e9c43a16 	stmib	r4, {r1, r2, r4, r9, fp, ip, sp}^
d0018628:	e7f59818 			; <UNDEFINED> instruction: 0xe7f59818
d001862c:	6da3b12d 	stfvsd	f3, [r3, #180]!	; 0xb4
d0018630:	d1f12b00 	mvnsle	r2, r0, lsl #22
d0018634:	447b4b6f 	ldrbtmi	r4, [fp], #-2927	; 0xfffff491
d0018638:	9b04e7f2 	blls	0xd0152608
d001863c:	213db1f3 	teqcs	sp, r3	; <illegal shifter operand>
d0018640:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0018644:	b1c8fbfc 	strdlt	pc, [r8, #188]	; 0xbc
d0018648:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d001864c:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0018650:	2efffb05 	vmovcs.f64	d31, #245	; 0xbfa80000 -1.3125000
d0018654:	2204d10e 	andcs	sp, r4, #-2147483645	; 0x80000003
d0018658:	f7fd2101 			; <UNDEFINED> instruction: 0xf7fd2101
d001865c:	f64bfe67 			; <UNDEFINED> instruction: 0xf64bfe67
d0018660:	46204106 	strtmi	r4, [r0], -r6, lsl #2
d0018664:	fafaf7fc 	blx	0xcfed665c
d0018668:	0108f246 	tsteq	r8, r6, asr #4	; <UNPREDICTABLE>
d001866c:	f7fc2502 			; <UNDEFINED> instruction: 0xf7fc2502
d0018670:	e786faf5 			; <UNDEFINED> instruction: 0xe786faf5
d0018674:	f7ff4631 			; <UNDEFINED> instruction: 0xf7ff4631
d0018678:	e7f0fc7b 			; <UNDEFINED> instruction: 0xe7f0fc7b
d001867c:	f46f6ae3 	vld1.64	{d22-d23}, [pc :128], r3
d0018680:	195a7592 	ldmdbne	sl, {r1, r4, r7, r8, sl, ip, sp, lr}^
d0018684:	d9042a01 	stmdble	r4, {r0, r9, fp, sp}
d0018688:	7094f46f 	addsvc	pc, r4, pc, ror #8
d001868c:	2b044403 	blcs	0xd01296a0
d0018690:	6da3d808 	stcvs	8, cr13, [r3, #32]!
d0018694:	4b58b933 	blmi	0xd1646b68
d0018698:	447b66a7 	ldrbtmi	r6, [fp], #-1703	; 0xfffff959
d001869c:	9818e9c4 	ldmdals	r8, {r2, r6, r7, r8, fp, sp, lr, pc}
d00186a0:	3a16e9c4 	bcc	0xd05d2db8
d00186a4:	41d0f44f 	bicsmi	pc, r0, pc, asr #8
d00186a8:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d00186ac:	4b4bfad7 	blmi	0xd1317210
d00186b0:	50e62eff 	strdpl	r2, [r6], #239	; 0xef	; <UNPREDICTABLE>
d00186b4:	2504d1b0 	strcs	sp, [r4, #-432]	; 0xfffffe50
d00186b8:	2effe763 	cdpcs	7, 15, cr14, cr15, cr3, {3}
d00186bc:	212ed00d 			; <UNDEFINED> instruction: 0x212ed00d
d00186c0:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d00186c4:	2800fbbc 	stmdacs	r0, {r2, r3, r4, r5, r7, r8, r9, fp, ip, sp, lr, pc}
d00186c8:	2d00d19f 	stfcsd	f5, [r0, #-636]	; 0xfffffd84
d00186cc:	6da3d1a4 	stfvsd	f5, [r3, #656]!	; 0x290
d00186d0:	d1a12b00 			; <UNDEFINED> instruction: 0xd1a12b00
d00186d4:	447b4b49 	ldrbtmi	r4, [fp], #-2889	; 0xfffff4b7
d00186d8:	6ae6e7a2 	bvs	0xcf9d2568
d00186dc:	d0022e2e 	andle	r2, r2, lr, lsr #28
d00186e0:	7f91f5b6 	svcvc	0x0091f5b6
d00186e4:	4946d105 	stmdbmi	r6, {r0, r2, r8, ip, lr, pc}^
d00186e8:	44794620 	ldrbtmi	r4, [r9], #-1568	; 0xfffff9e0
d00186ec:	fd5cf7f7 	ldc2l	7, cr15, [ip, #-988]	; 0xfffffc24
d00186f0:	2d00e716 	stccs	7, cr14, [r0, #-88]	; 0xffffffa8
d00186f4:	9b04d1df 	blls	0xd014ce78
d00186f8:	d0682b00 	rsble	r2, r8, r0, lsl #22
d00186fc:	d0092e3d 	andle	r2, r9, sp, lsr lr
d0018700:	7192f46f 	orrsvc	pc, r2, pc, ror #8
d0018704:	2b011873 	blcs	0xd005e8d8
d0018708:	f46fd904 	vld2.8	{d29,d31}, [pc], r4
d001870c:	18b37294 	ldmne	r3!, {r2, r4, r7, r9, ip, sp, lr}
d0018710:	d85c2b04 	ldmdale	ip, {r2, r8, r9, fp, sp}^
d0018714:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0018718:	f24bfb77 	vpadd.i8	<illegal reg q15.5>, <illegal reg q5.5>, <illegal reg q11.5>
d001871c:	46204103 	strtmi	r4, [r0], -r3, lsl #2
d0018720:	fa9cf7fc 	blx	0xce756718
d0018724:	d0072e3d 	andle	r2, r7, sp, lsr lr
d0018728:	41d0f44f 	bicsmi	pc, r0, pc, asr #8
d001872c:	fa96f7fc 	blx	0xce5d6724
d0018730:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d0018734:	fa92f7fc 	blx	0xce4d672c
d0018738:	46202201 	strtmi	r2, [r0], -r1, lsl #4
d001873c:	f7fd4611 			; <UNDEFINED> instruction: 0xf7fd4611
d0018740:	2e3dfdf5 	mrccs	13, 1, APSR_nzcv, cr13, cr5, {7}
d0018744:	f64bd08b 			; <UNDEFINED> instruction: 0xf64bd08b
d0018748:	46204106 	strtmi	r4, [r0], -r6, lsl #2
d001874c:	fa86f7fc 	blx	0xce1d6744
d0018750:	7392f46f 	orrsvc	pc, r2, #1862270976	; 0x6f000000
d0018754:	2b0818f3 	blcs	0xd021eb28
d0018758:	a202d881 	andge	sp, r2, #8454144	; 0x810000
d001875c:	3023f852 	eorcc	pc, r3, r2, asr r8	; <UNPREDICTABLE>
d0018760:	4710441a 			; <UNDEFINED> instruction: 0x4710441a
d0018764:	00000025 	andeq	r0, r0, r5, lsr #32
d0018768:	00000031 	andeq	r0, r0, r1, lsr r0
d001876c:	fffffefb 			; <UNDEFINED> instruction: 0xfffffefb
d0018770:	fffffefb 			; <UNDEFINED> instruction: 0xfffffefb
d0018774:	00000037 	andeq	r0, r0, r7, lsr r0
d0018778:	0000003d 	andeq	r0, r0, sp, lsr r0
d001877c:	00000043 	andeq	r0, r0, r3, asr #32
d0018780:	00000049 	andeq	r0, r0, r9, asr #32
d0018784:	00000049 	andeq	r0, r0, r9, asr #32
d0018788:	0108f641 	tsteq	r8, r1, asr #12	; <UNPREDICTABLE>
d001878c:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0018790:	e764fa65 	strb	pc, [r4, -r5, ror #20]!	; <UNPREDICTABLE>
d0018794:	2108f641 	tstcs	r8, r1, asr #12	; <UNPREDICTABLE>
d0018798:	f244e7f8 	vaba.s8	q15, q10, q12
d001879c:	e7f50108 	ldrb	r0, [r5, r8, lsl #2]!
d00187a0:	3108f244 	tstcc	r8, r4, asr #4	; <UNPREDICTABLE>
d00187a4:	f244e7f2 	vaba.s8	q15, q10, q9
d00187a8:	e7ef0148 	strb	r0, [pc, r8, asr #2]!
d00187ac:	6102f244 	tstvs	r2, r4, asr #4	; <UNPREDICTABLE>
d00187b0:	fa54f7fc 	blx	0xd15567a8
d00187b4:	6108f244 	tstvs	r8, r4, asr #4	; <UNPREDICTABLE>
d00187b8:	fa50f7fc 	blx	0xd14567b0
d00187bc:	0190f244 	orrseq	pc, r0, r4, asr #4
d00187c0:	1310f244 	tstne	r0, #68, 4	; 0x40000004	; <UNPREDICTABLE>
d00187c4:	7f96f5b6 	svcvc	0x0096f5b6
d00187c8:	4619bf18 	sadd16mi	fp, r9, r8
d00187cc:	f44fe7de 	vst1.64	{d30}, [pc :64], lr
d00187d0:	462041d0 			; <UNDEFINED> instruction: 0x462041d0
d00187d4:	fa42f7fc 	blx	0xd10d67cc
d00187d8:	bf00e6d3 	svclt	0x0000e6d3
d00187dc:	00149244 	andseq	r9, r4, r4, asr #4
d00187e0:	fffffee3 			; <UNDEFINED> instruction: 0xfffffee3
d00187e4:	fffffe44 			; <UNDEFINED> instruction: 0xfffffe44
d00187e8:	fffffdf2 			; <UNDEFINED> instruction: 0xfffffdf2
d00187ec:	fffffde9 			; <UNDEFINED> instruction: 0xfffffde9
d00187f0:	fffffde9 			; <UNDEFINED> instruction: 0xfffffde9
d00187f4:	fffffdf2 			; <UNDEFINED> instruction: 0xfffffdf2
d00187f8:	fffffdc4 			; <UNDEFINED> instruction: 0xfffffdc4
d00187fc:	fffffdad 			; <UNDEFINED> instruction: 0xfffffdad
d0018800:	fffffdc1 			; <UNDEFINED> instruction: 0xfffffdc1

Disassembly of section .text.unary:

d0018b6c <.text.unary>:
d0018b6c:	4ff0e92d 	svcmi	0x00f0e92d
d0018b70:	b09f6d83 	addslt	r6, pc, r3, lsl #27
d0018b74:	460e4604 	strmi	r4, [lr], -r4, lsl #12
d0018b78:	2b00930a 	blcs	0xd003d7a8
d0018b7c:	853ff040 	ldrhi	pc, [pc, #-64]!	; 0xd0018b44
d0018b80:	18a4f500 	stmiane	r4!, {r8, sl, ip, sp, lr, pc}
d0018b84:	f8d06a83 			; <UNDEFINED> instruction: 0xf8d06a83
d0018b88:	f508b02c 			; <UNDEFINED> instruction: 0xf508b02c
d0018b8c:	93085192 	movwls	r5, #33170	; 0x8192
d0018b90:	3030f890 	mlascc	r0, r0, r8, pc	; <UNPREDICTABLE>
d0018b94:	9309680a 	movwls	r6, #38922	; 0x980a
d0018b98:	6b433201 	blvs	0xd10e53a4
d0018b9c:	93072a20 	movwls	r2, #31264	; 0x7a20
d0018ba0:	9a06e9d0 	bls	0xd01d32e8
d0018ba4:	5708e9d0 			; <UNDEFINED> instruction: 0x5708e9d0
d0018ba8:	d906600a 	stmdble	r6, {r1, r3, sp, lr}
d0018bac:	167cf8df 			; <UNDEFINED> instruction: 0x167cf8df
d0018bb0:	f7f74479 			; <UNDEFINED> instruction: 0xf7f74479
d0018bb4:	2500faf9 	strcs	pc, [r0, #-2809]	; 0xfffff507
d0018bb8:	f44fe0fd 	vst4.<illegal width 64>	{d30-d33}, [pc :256]!
d0018bbc:	f7fa718d 			; <UNDEFINED> instruction: 0xf7fa718d
d0018bc0:	b140f93e 	cmplt	r0, lr, lsr r9	; <UNPREDICTABLE>
d0018bc4:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0018bc8:	4601fedb 			; <UNDEFINED> instruction: 0x4601fedb
d0018bcc:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0018bd0:	2501f8a4 	strcs	pc, [r1, #-2212]	; 0xfffff75c
d0018bd4:	f44fe0ef 	vst4.<illegal width 64>	{d30-d33}, [pc :128]
d0018bd8:	46207181 	strtmi	r7, [r0], -r1, lsl #3
d0018bdc:	f92ff7fa 			; <UNDEFINED> instruction: 0xf92ff7fa
d0018be0:	4620b150 			; <UNDEFINED> instruction: 0x4620b150
d0018be4:	f7fc4629 			; <UNDEFINED> instruction: 0xf7fc4629
d0018be8:	f240f898 	vtst.8	d31, d16, d8
d0018bec:	45831003 	strmi	r1, [r3, #3]
d0018bf0:	2500bf14 	strcs	fp, [r0, #-3860]	; 0xfffff0ec
d0018bf4:	e0de2501 	sbcs	r2, lr, r1, lsl #10
d0018bf8:	1103f240 	tstne	r3, r0, asr #4	; <UNPREDICTABLE>
d0018bfc:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0018c00:	2800f91e 	stmdacs	r0, {r1, r2, r3, r4, r8, fp, ip, sp, lr, pc}
d0018c04:	f240d1ed 	vrhadd.s8	<illegal reg q14.5>, q8, <illegal reg q14.5>
d0018c08:	46201123 	strtmi	r1, [r0], -r3, lsr #2
d0018c0c:	f917f7fa 			; <UNDEFINED> instruction: 0xf917f7fa
d0018c10:	f8dfb1f8 			; <UNDEFINED> instruction: 0xf8dfb1f8
d0018c14:	f240261c 	vmin.s8	d18, d0, d12
d0018c18:	6a631101 	bvs	0xd18dd024
d0018c1c:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d0018c20:	f8946aa7 			; <UNDEFINED> instruction: 0xf8946aa7
d0018c24:	f8d49030 			; <UNDEFINED> instruction: 0xf8d49030
d0018c28:	9307a034 	movwls	sl, #28724	; 0x7034
d0018c2c:	5606e9d4 			; <UNDEFINED> instruction: 0x5606e9d4
d0018c30:	f913f7fa 			; <UNDEFINED> instruction: 0xf913f7fa
d0018c34:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d0018c38:	22008342 	andcs	r8, r0, #134217729	; 0x8000001
d0018c3c:	46299b07 	strtmi	r9, [r9], -r7, lsl #22
d0018c40:	46329204 	ldrtmi	r9, [r2], -r4, lsl #4
d0018c44:	0e80e88d 	cdpeq	8, 8, cr14, cr0, cr13, {4}
d0018c48:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0018c4c:	4605fdbb 			; <UNDEFINED> instruction: 0x4605fdbb
d0018c50:	f44fe0b1 	vst4.32	{d30-d33}, [pc :256], r1
d0018c54:	46207192 			; <UNDEFINED> instruction: 0x46207192
d0018c58:	f8f1f7fa 			; <UNDEFINED> instruction: 0xf8f1f7fa
d0018c5c:	2800900a 	stmdacs	r0, {r1, r3, ip, pc}
d0018c60:	f240d1d7 	vand	<illegal reg q14.5>, q8, <illegal reg q3.5>
d0018c64:	46201101 	strtmi	r1, [r0], -r1, lsl #2
d0018c68:	f8e9f7fa 			; <UNDEFINED> instruction: 0xf8e9f7fa
d0018c6c:	28004605 	stmdacs	r0, {r0, r2, r9, sl, lr}
d0018c70:	830af000 	movwhi	pc, #40960	; 0xa000	; <UNPREDICTABLE>
d0018c74:	25bcf8df 	ldrcs	pc, [ip, #2271]!	; 0x8df
d0018c78:	46484651 			; <UNDEFINED> instruction: 0x46484651
d0018c7c:	f7f7447a 			; <UNDEFINED> instruction: 0xf7f7447a
d0018c80:	2800fdf9 	stmdacs	r0, {r0, r3, r4, r5, r6, r7, r8, sl, fp, ip, sp, lr, pc}
d0018c84:	80a4f000 	adchi	pc, r4, r0
d0018c88:	2b2e6ae3 	blcs	0xd0bb381c
d0018c8c:	80a0f040 	adchi	pc, r0, r0, asr #32
d0018c90:	b5a4f8df 	strlt	pc, [r4, #2271]!	; 0x8df
d0018c94:	f8df2503 			; <UNDEFINED> instruction: 0xf8df2503
d0018c98:	220315a4 	andcs	r1, r3, #164, 10	; 0x29000000
d0018c9c:	a80e44fb 	stmdage	lr, {r0, r1, r3, r4, r5, r6, r7, sl, lr}
d0018ca0:	f0064479 			; <UNDEFINED> instruction: 0xf0064479
d0018ca4:	f8d4fe13 			; <UNDEFINED> instruction: 0xf8d4fe13
d0018ca8:	f1b8802c 			; <UNDEFINED> instruction: 0xf1b8802c
d0018cac:	d0020f2e 	andle	r0, r2, lr, lsr #30
d0018cb0:	7f91f5b8 	svcvc	0x0091f5b8
d0018cb4:	4620d12a 	strtmi	sp, [r0], -sl, lsr #2
d0018cb8:	f8a6f7fa 			; <UNDEFINED> instruction: 0xf8a6f7fa
d0018cbc:	465a6a63 	ldrbmi	r6, [sl], -r3, ror #20
d0018cc0:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d0018cc4:	4620930d 	strtmi	r9, [r0], -sp, lsl #6
d0018cc8:	6b666aa3 	blvs	0xd19b375c
d0018ccc:	f894930b 			; <UNDEFINED> instruction: 0xf894930b
d0018cd0:	e9d43030 	ldmib	r4, {r4, r5, ip, sp}^
d0018cd4:	930c9a06 	movwls	r9, #51718	; 0xca06
d0018cd8:	f8bff7fa 			; <UNDEFINED> instruction: 0xf8bff7fa
d0018cdc:	f1b8b1b0 			; <UNDEFINED> instruction: 0xf1b8b1b0
d0018ce0:	eb050f2e 	bl	0xd015c9a0
d0018ce4:	9b0d020a 	blls	0xd0359514
d0018ce8:	2101bf0c 	tstcs	r1, ip, lsl #30
d0018cec:	440a2102 	strmi	r2, [sl], #-258	; 0xfffffefe
d0018cf0:	d9342a3f 	ldmdble	r4!, {r0, r1, r2, r3, r4, r5, r9, fp, sp}
d0018cf4:	b94a6da2 	stmdblt	sl, {r1, r5, r7, r8, sl, fp, sp, lr}^
d0018cf8:	2544f8df 	strbcs	pc, [r4, #-2271]	; 0xfffff721	; <UNPREDICTABLE>
d0018cfc:	447a66a6 	ldrbtmi	r6, [sl], #-1702	; 0xfffff95a
d0018d00:	2316e9c4 	tstcs	r6, #196, 18	; 0x310000
d0018d04:	66239b0b 	strtvs	r9, [r3], -fp, lsl #22
d0018d08:	66639b0c 	strbtvs	r9, [r3], -ip, lsl #22
d0018d0c:	2200ab1e 	andcs	sl, r0, #30720	; 0x7800
d0018d10:	f803442b 			; <UNDEFINED> instruction: 0xf803442b
d0018d14:	6da32c40 	stcvs	12, cr2, [r3, #256]!	; 0x100
d0018d18:	d14b2b00 	cmple	fp, r0, lsl #22
d0018d1c:	2524f8df 	strcs	pc, [r4, #-2271]!	; 0xfffff721
d0018d20:	46202128 	strtmi	r2, [r0], -r8, lsr #2
d0018d24:	f7fa447a 			; <UNDEFINED> instruction: 0xf7fa447a
d0018d28:	2800f898 	stmdacs	r0, {r3, r4, r7, fp, ip, sp, lr, pc}
d0018d2c:	462ad042 	strtmi	sp, [sl], -r2, asr #32
d0018d30:	4620a90e 	strtmi	sl, [r0], -lr, lsl #18
d0018d34:	fdb3f7f7 	ldc2	7, cr15, [r3, #988]!	; 0x3dc
d0018d38:	b3704605 	cmnlt	r0, #5242880	; 0x500000
d0018d3c:	46204601 	strtmi	r4, [r0], -r1, lsl #12
d0018d40:	f85af7fe 			; <UNDEFINED> instruction: 0xf85af7fe
d0018d44:	3047f895 	umaalcc	pc, r7, r5, r8	; <UNPREDICTABLE>
d0018d48:	d03d2b07 	eorsle	r2, sp, r7, lsl #22
d0018d4c:	2a011f5a 	bcs	0xd0060abc
d0018d50:	2b10d93c 	blcs	0xd044f248
d0018d54:	bf089b0a 	svclt	0x00089b0a
d0018d58:	930a2301 	movwls	r2, #41729	; 0xa301
d0018d5c:	f1b8e02a 			; <UNDEFINED> instruction: 0xf1b8e02a
d0018d60:	ab1e0f2e 	blge	0xd079ca20
d0018d64:	0601f105 	streq	pc, [r1], -r5, lsl #2
d0018d68:	442ba80e 	strtmi	sl, [fp], #-2062	; 0xfffff7f2
d0018d6c:	222dbf18 	eorcs	fp, sp, #24, 30	; 0x60
d0018d70:	bf1c4649 	svclt	0x001c4649
d0018d74:	2c40f803 	mcrrcs	8, 0, pc, r0, cr3	; <UNPREDICTABLE>
d0018d78:	4652ab1e 			; <UNDEFINED> instruction: 0x4652ab1e
d0018d7c:	f803bf0f 			; <UNDEFINED> instruction: 0xf803bf0f
d0018d80:	18f68c40 	ldmne	r6!, {r6, sl, fp, pc}^
d0018d84:	f806233e 			; <UNDEFINED> instruction: 0xf806233e
d0018d88:	bf183c40 	svclt	0x00183c40
d0018d8c:	44301cae 	ldrtmi	r1, [r0], #-3246	; 0xfffff352
d0018d90:	050aeb06 	streq	lr, [sl, #-2822]	; 0xfffff4fa
d0018d94:	fd9af006 	ldc2	0, cr15, [sl, #24]
d0018d98:	6da3e785 	stcvs	7, cr14, [r3, #532]!	; 0x214
d0018d9c:	f8dfb953 			; <UNDEFINED> instruction: 0xf8dfb953
d0018da0:	447b34a8 	ldrbtmi	r3, [fp], #-1192	; 0xfffffb58
d0018da4:	3716e9c4 	ldrcc	lr, [r6, -r4, asr #19]
d0018da8:	66239b08 	strtvs	r9, [r3], -r8, lsl #22
d0018dac:	66639b09 	strbtvs	r9, [r3], -r9, lsl #22
d0018db0:	66a39b07 	strtvs	r9, [r3], r7, lsl #22
d0018db4:	f5049d0a 			; <UNDEFINED> instruction: 0xf5049d0a
d0018db8:	462814a4 	strtmi	r1, [r8], -r4, lsr #9
d0018dbc:	5492f504 	ldrpl	pc, [r2], #1284	; 0x504
d0018dc0:	3b016823 	blcc	0xd0072e54
d0018dc4:	e2816023 	add	r6, r1, #35	; 0x23
d0018dc8:	e7c62302 	strb	r2, [r6, r2, lsl #6]
d0018dcc:	e7c42301 	strb	r2, [r4, r1, lsl #6]
d0018dd0:	46202128 	strtmi	r2, [r0], -r8, lsr #2
d0018dd4:	f833f7fa 			; <UNDEFINED> instruction: 0xf833f7fa
d0018dd8:	b3184605 	tstlt	r8, #5242880	; 0x500000
d0018ddc:	46524649 	ldrbmi	r4, [r2], -r9, asr #12
d0018de0:	f7f74620 			; <UNDEFINED> instruction: 0xf7f74620
d0018de4:	1e01fc91 	mcrne	12, 0, pc, cr1, cr1, {4}	; <UNPREDICTABLE>
d0018de8:	2330db0f 	teqcs	r0, #15360	; 0x3c00
d0018dec:	4301fb03 	movwmi	pc, #6915	; 0x1b03	; <UNPREDICTABLE>
d0018df0:	13a4f503 			; <UNDEFINED> instruction: 0x13a4f503
d0018df4:	3655f893 			; <UNDEFINED> instruction: 0x3655f893
d0018df8:	d1062b0c 	tstle	r6, ip, lsl #22
d0018dfc:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0018e00:	4605fadd 			; <UNDEFINED> instruction: 0x4605fadd
d0018e04:	d1d62d04 	bicsle	r2, r6, r4, lsl #26
d0018e08:	9b07e0d8 	blls	0xd0211170
d0018e0c:	46494652 			; <UNDEFINED> instruction: 0x46494652
d0018e10:	93024620 	movwls	r4, #9760	; 0x2620
d0018e14:	93019b09 	movwls	r9, #6921	; 0x1b09
d0018e18:	93009b08 	movwls	r9, #2824	; 0xb08
d0018e1c:	f7fe463b 			; <UNDEFINED> instruction: 0xf7fe463b
d0018e20:	e7eefdb5 			; <UNDEFINED> instruction: 0xe7eefdb5
d0018e24:	802cf8d4 	ldrdhi	pc, [ip], -r4	; <UNPREDICTABLE>
d0018e28:	7091f46f 	addsvc	pc, r1, pc, ror #8
d0018e2c:	0300eb08 	movweq	lr, #2824	; 0xb08
d0018e30:	d8102b01 	ldmdale	r0, {r0, r8, r9, fp, sp}
d0018e34:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d0018e38:	2301ffe7 	movwcs	pc, #8167	; 0x1fe7	; <UNPREDICTABLE>
d0018e3c:	46494652 			; <UNDEFINED> instruction: 0x46494652
d0018e40:	9b079304 	blls	0xd01fda58
d0018e44:	800cf8cd 	andhi	pc, ip, sp, asr #17
d0018e48:	9b099302 	blls	0xd027da58
d0018e4c:	9b089301 	blls	0xd023da58
d0018e50:	463b9300 	ldrtmi	r9, [fp], -r0, lsl #6
d0018e54:	4652e6f8 			; <UNDEFINED> instruction: 0x4652e6f8
d0018e58:	46204649 	strtmi	r4, [r0], -r9, asr #12
d0018e5c:	fc54f7f7 	mrrc2	7, 15, pc, r4, cr7	; <UNPREDICTABLE>
d0018e60:	46804652 	pkhtbmi	r4, r0, r2, asr #12
d0018e64:	46204649 	strtmi	r4, [r0], -r9, asr #12
d0018e68:	fd37f7f7 	ldc2	7, cr15, [r7, #-988]!	; 0xfffffc24
d0018e6c:	b1204683 	smlawblt	r0, r3, r6, r4
d0018e70:	46206a01 	strtmi	r6, [r0], -r1, lsl #20
d0018e74:	ff51f7fb 			; <UNDEFINED> instruction: 0xff51f7fb
d0018e78:	f1b8e79d 			; <UNDEFINED> instruction: 0xf1b8e79d
d0018e7c:	f2c00f00 			; <UNDEFINED> instruction: 0xf2c00f00
d0018e80:	f04f8104 			; <UNDEFINED> instruction: 0xf04f8104
d0018e84:	fb0a0a30 	blx	0xd029b74e
d0018e88:	f50a4a08 			; <UNDEFINED> instruction: 0xf50a4a08
d0018e8c:	f89a1aa4 			; <UNDEFINED> instruction: 0xf89a1aa4
d0018e90:	f1b99655 			; <UNDEFINED> instruction: 0xf1b99655
d0018e94:	d0020f02 	andle	r0, r2, r2, lsl #30
d0018e98:	0f04f1b9 	svceq	0x0004f1b9
d0018e9c:	6da3d10d 	stfvsd	f5, [r3, #52]!	; 0x34
d0018ea0:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0018ea4:	4be9ae88 	blmi	0xcfa848cc
d0018ea8:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0018eac:	9b083716 	blls	0xd0226b0c
d0018eb0:	9b096623 	blls	0xd0272744
d0018eb4:	9b076663 	blls	0xd01f2848
d0018eb8:	f1b9e0df 			; <UNDEFINED> instruction: 0xf1b9e0df
d0018ebc:	d1060f0c 	tstle	r6, ip, lsl #30
d0018ec0:	4641462a 	strbmi	r4, [r1], -sl, lsr #12
d0018ec4:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0018ec8:	2503ff61 	strcs	pc, [r3, #-3937]	; 0xfffff09f
d0018ecc:	f1b9e773 			; <UNDEFINED> instruction: 0xf1b9e773
d0018ed0:	d1060f13 	tstle	r6, r3, lsl pc
d0018ed4:	4641462a 	strbmi	r4, [r1], -sl, lsr #12
d0018ed8:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0018edc:	2507ff57 	strcs	pc, [r7, #-3927]	; 0xfffff0a9
d0018ee0:	f1b9e769 			; <UNDEFINED> instruction: 0xf1b9e769
d0018ee4:	d10a0f12 	tstle	sl, r2, lsl pc
d0018ee8:	4641462a 	strbmi	r4, [r1], -sl, lsr #12
d0018eec:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0018ef0:	f89aff4d 			; <UNDEFINED> instruction: 0xf89aff4d
d0018ef4:	4bcc2656 	blmi	0xcf322854
d0018ef8:	50e22505 	rscpl	r2, r2, r5, lsl #10
d0018efc:	f1a9e75b 			; <UNDEFINED> instruction: 0xf1a9e75b
d0018f00:	2b01030d 	blcs	0xd0059b3c
d0018f04:	f1b9d83b 			; <UNDEFINED> instruction: 0xf1b9d83b
d0018f08:	d11d0f0d 	tstle	sp, sp, lsl #30
d0018f0c:	46204641 	strtmi	r4, [r0], -r1, asr #12
d0018f10:	ff6ef7fb 			; <UNDEFINED> instruction: 0xff6ef7fb
d0018f14:	4620212e 	strtmi	r2, [r0], -lr, lsr #2
d0018f18:	ff91f7f9 			; <UNDEFINED> instruction: 0xff91f7f9
d0018f1c:	b1604605 	cmnlt	r0, r5, lsl #12
d0018f20:	23002030 	movwcs	r2, #48	; 0x30
d0018f24:	fb004632 	blx	0xd002a7f6
d0018f28:	f5084808 			; <UNDEFINED> instruction: 0xf5084808
d0018f2c:	f89818a4 			; <UNDEFINED> instruction: 0xf89818a4
d0018f30:	46201656 			; <UNDEFINED> instruction: 0x46201656
d0018f34:	fad2f7ff 	blx	0xcf4d6f38
d0018f38:	6da3e689 	stcvs	6, cr14, [r3, #548]!	; 0x224
d0018f3c:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0018f40:	4bc3ae3a 	blmi	0xcf104830
d0018f44:	e7b0447b 			; <UNDEFINED> instruction: 0xe7b0447b
d0018f48:	46412200 	strbmi	r2, [r1], -r0, lsl #4
d0018f4c:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0018f50:	f44fff1d 			; <UNDEFINED> instruction: 0xf44fff1d
d0018f54:	f7f97191 			; <UNDEFINED> instruction: 0xf7f97191
d0018f58:	4603ff72 			; <UNDEFINED> instruction: 0x4603ff72
d0018f5c:	d1df2800 	bicsle	r2, pc, r0, lsl #16
d0018f60:	2a5b6ae2 	bcs	0xd16f3af0
d0018f64:	2230d1b1 	eorscs	sp, r0, #1073741868	; 0x4000002c
d0018f68:	4808fb02 	stmdami	r8, {r1, r8, r9, fp, ip, sp, lr, pc}
d0018f6c:	18a4f508 	stmiane	r4!, {r3, r8, sl, ip, sp, lr, pc}
d0018f70:	f8984632 			; <UNDEFINED> instruction: 0xf8984632
d0018f74:	46201656 			; <UNDEFINED> instruction: 0x46201656
d0018f78:	fab6f7fe 	blx	0xcedd6f78
d0018f7c:	f1b9e667 			; <UNDEFINED> instruction: 0xf1b9e667
d0018f80:	d1140f10 	tstle	r4, r0, lsl pc
d0018f84:	46204641 	strtmi	r4, [r0], -r1, asr #12
d0018f88:	ff32f7fb 			; <UNDEFINED> instruction: 0xff32f7fb
d0018f8c:	2b5b6ae3 	blcs	0xd16f3b20
d0018f90:	2030d106 	eorscs	sp, r0, r6, lsl #2
d0018f94:	fb002300 	blx	0xd0021b9e
d0018f98:	f5084808 			; <UNDEFINED> instruction: 0xf5084808
d0018f9c:	e7e718a4 	strb	r1, [r7, r4, lsr #17]!
d0018fa0:	2b006da3 	blcs	0xd0034634
d0018fa4:	ae07f47f 	mcrge	4, 0, pc, cr7, cr15, {3}	; <UNPREDICTABLE>
d0018fa8:	447b4baa 	ldrbtmi	r4, [fp], #-2986	; 0xfffff456
d0018fac:	f1b9e77d 			; <UNDEFINED> instruction: 0xf1b9e77d
d0018fb0:	d10a0f09 	tstle	sl, r9, lsl #30
d0018fb4:	46204641 	strtmi	r4, [r0], -r1, asr #12
d0018fb8:	ff1af7fb 			; <UNDEFINED> instruction: 0xff1af7fb
d0018fbc:	2b5b6ae3 	blcs	0xd16f3b50
d0018fc0:	8232f040 	eorshi	pc, r2, #64	; 0x40
d0018fc4:	46312200 	ldrtmi	r2, [r1], -r0, lsl #4
d0018fc8:	2200e1d4 	andcs	lr, r0, #212, 2	; 0x35
d0018fcc:	46204641 	strtmi	r4, [r0], -r1, asr #12
d0018fd0:	fedcf7fb 	mrc2	7, 6, pc, cr12, cr11, {7}
d0018fd4:	0f06f1b9 	svceq	0x0006f1b9
d0018fd8:	f44fd151 	vst4.16	{d29,d31,d33,d35}, [pc :64], r1
d0018fdc:	f7f97191 			; <UNDEFINED> instruction: 0xf7f97191
d0018fe0:	2800ff2e 	stmdacs	r0, {r1, r2, r3, r5, r8, r9, sl, fp, ip, sp, lr, pc}
d0018fe4:	af71f43f 	svcge	0x0071f43f
d0018fe8:	f2406aa3 	vpmax.s8	d22, d16, d19
d0018fec:	4a9a1101 	bmi	0xce69d3f8
d0018ff0:	93074620 	movwls	r4, #30240	; 0x7620
d0018ff4:	447a6b63 	ldrbtmi	r6, [sl], #-2915	; 0xfffff49d
d0018ff8:	9024f8d4 	ldrdls	pc, [r4], -r4	; <UNPREDICTABLE>
d0018ffc:	7030f894 	mlasvc	r0, r4, r8, pc	; <UNPREDICTABLE>
d0019000:	e9d49308 	ldmib	r4, {r3, r8, r9, ip, pc}^
d0019004:	f7f9ab06 			; <UNDEFINED> instruction: 0xf7f9ab06
d0019008:	2800ff28 	stmdacs	r0, {r3, r5, r8, r9, sl, fp, ip, sp, lr, pc}
d001900c:	add3f43f 	cfldrdge	mvd15, [r3, #252]	; 0xfc
d0019010:	8248f8df 	subhi	pc, r8, #14614528	; 0xdf0000
d0019014:	44f82600 	ldrbtmi	r2, [r8], #1536	; 0x600
d0019018:	2b04f858 	blcs	0xd0157180
d001901c:	46504659 			; <UNDEFINED> instruction: 0x46504659
d0019020:	fc28f7f7 	stc2	7, cr15, [r8], #-988	; 0xfffffc24
d0019024:	b1c84605 	biclt	r4, r8, r5, lsl #12
d0019028:	03d0f64f 	bicseq	pc, r0, #82837504	; 0x4f00000
d001902c:	0190f64f 	orrseq	pc, r0, pc, asr #12
d0019030:	2e014620 	cfmadd32cs	mvax1, mvfx4, mvfx1, mvfx0
d0019034:	4619bf18 	sadd16mi	fp, r9, r8
d0019038:	fe10f7fb 	mrc2	7, 0, pc, cr0, cr11, {7}
d001903c:	430ff506 	movwmi	pc, #62726	; 0xf506	; <UNPREDICTABLE>
d0019040:	eb0433d0 	bl	0xd0125f88
d0019044:	88990343 	ldmhi	r9, {r0, r1, r6, r8, r9}
d0019048:	fe08f7fb 	mcr2	7, 0, pc, cr8, cr11, {7}	; <UNPREDICTABLE>
d001904c:	f43f2e00 			; <UNDEFINED> instruction: 0xf43f2e00
d0019050:	3e02adc0 	cdpcc	13, 0, cr10, cr2, cr0, {6}
d0019054:	f63f2e01 			; <UNDEFINED> instruction: 0xf63f2e01
d0019058:	e5baadae 	ldr	sl, [sl, #3502]!	; 0xdae
d001905c:	2e083601 	cfmadd32cs	mvax0, mvfx3, mvfx8, mvfx1
d0019060:	6da3d1da 	stfvsd	f5, [r3, #872]!	; 0x368
d0019064:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0019068:	4b7dada6 	blmi	0xd1f84708
d001906c:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0019070:	9b073916 	blls	0xd01e74d0
d0019074:	3718e9c4 	ldrcc	lr, [r8, -r4, asr #19]
d0019078:	66a39b08 	strtvs	r9, [r3], r8, lsl #22
d001907c:	f1b9e69b 			; <UNDEFINED> instruction: 0xf1b9e69b
d0019080:	d09b0f0a 	addsle	r0, fp, sl, lsl #30
d0019084:	0f01f1b9 	svceq	0x0001f1b9
d0019088:	4652e5b2 			; <UNDEFINED> instruction: 0x4652e5b2
d001908c:	46204649 	strtmi	r4, [r0], -r9, asr #12
d0019090:	fb5af7f7 	blx	0xd16d7076
d0019094:	0800f1b0 	stmdaeq	r0, {r4, r5, r7, r8, ip, sp, lr, pc}
d0019098:	80b8f2c0 	adcshi	pc, r8, r0, asr #5
d001909c:	093cf04f 	ldmdbeq	ip!, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d00190a0:	4908fb09 	stmdbmi	r8, {r0, r3, r8, r9, fp, ip, sp, lr, pc}
d00190a4:	395ff509 	ldmdbcc	pc, {r0, r3, r8, sl, ip, sp, lr, pc}^	; <UNPREDICTABLE>
d00190a8:	a3ecf899 	mvnge	pc, #10027008	; 0x990000
d00190ac:	0f07f1ba 	svceq	0x0007f1ba
d00190b0:	4a6cd15f 	bmi	0xd1b4d634
d00190b4:	4620215b 			; <UNDEFINED> instruction: 0x4620215b
d00190b8:	f7f9447a 			; <UNDEFINED> instruction: 0xf7f9447a
d00190bc:	2800fece 	stmdacs	r0, {r1, r2, r3, r6, r7, r9, sl, fp, ip, sp, lr, pc}
d00190c0:	ad79f43f 	cfldrdge	mvd15, [r9, #-252]!	; 0xffffff04
d00190c4:	46202201 	strtmi	r2, [r0], -r1, lsl #4
d00190c8:	f7fd4611 			; <UNDEFINED> instruction: 0xf7fd4611
d00190cc:	4a66f92f 	bmi	0xd19d7590
d00190d0:	4620215d 			; <UNDEFINED> instruction: 0x4620215d
d00190d4:	f7f9447a 			; <UNDEFINED> instruction: 0xf7f9447a
d00190d8:	2800fec0 	stmdacs	r0, {r6, r7, r9, sl, fp, ip, sp, lr, pc}
d00190dc:	ad6bf43f 	cfstrdge	mvd15, [fp, #-252]!	; 0xffffff04
d00190e0:	21014642 	tstcs	r1, r2, asr #12
d00190e4:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d00190e8:	6ae7ff2f 	bvs	0xcfa18dac
d00190ec:	f0002f3d 			; <UNDEFINED> instruction: 0xf0002f3d
d00190f0:	f46f8288 	vld1.32	{d24-d27}, [pc], r8
d00190f4:	187b7192 	ldmdane	fp!, {r1, r4, r7, r8, ip, sp, lr}^
d00190f8:	f2402b01 	vqdmulh.s<illegal width 8>	d18, d0, d1
d00190fc:	f46f8282 	vld1.32	{d24-d27}, [pc], r2
d0019100:	18bb7294 	ldmne	fp!, {r2, r4, r7, r9, ip, sp, lr}
d0019104:	f2402b04 	vqdmulh.s<illegal width 8>	d18, d0, d4
d0019108:	f645827c 			; <UNDEFINED> instruction: 0xf645827c
d001910c:	46204108 	strtmi	r4, [r0], -r8, lsl #2
d0019110:	fda4f7fb 	stc2	7, cr15, [r4, #1004]!	; 0x3ec
d0019114:	f641e64f 			; <UNDEFINED> instruction: 0xf641e64f
d0019118:	46200108 	strtmi	r0, [r0], -r8, lsl #2
d001911c:	fd9ef7fb 	ldc2	7, cr15, [lr, #1004]	; 0x3ec
d0019120:	4106f64b 	tstmi	r6, fp, asr #12	; <UNPREDICTABLE>
d0019124:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0019128:	f247fd99 	vmla.f32	d31, d23, d9
d001912c:	46200108 	strtmi	r0, [r0], -r8, lsl #2
d0019130:	f7fb2502 			; <UNDEFINED> instruction: 0xf7fb2502
d0019134:	e63efd93 			; <UNDEFINED> instruction: 0xe63efd93
d0019138:	2108f641 	tstcs	r8, r1, asr #12	; <UNPREDICTABLE>
d001913c:	f244e7ed 	vabd.s8	q15, q10, <illegal reg q14.5>
d0019140:	e7ea0108 	strb	r0, [sl, r8, lsl #2]!
d0019144:	3108f244 	tstcc	r8, r4, asr #4	; <UNPREDICTABLE>
d0019148:	f244e7e7 	vabd.s8	q15, q10, <illegal reg q11.5>
d001914c:	e7e40148 	strb	r0, [r4, r8, asr #2]!
d0019150:	6102f244 	tstvs	r2, r4, asr #4	; <UNPREDICTABLE>
d0019154:	fd82f7fb 	stc2	7, cr15, [r2, #1004]	; 0x3ec
d0019158:	6108f244 	tstvs	r8, r4, asr #4	; <UNPREDICTABLE>
d001915c:	fd7ef7fb 	ldc2l	7, cr15, [lr, #-1004]!	; 0xfffffc14
d0019160:	0190f244 	orrseq	pc, r0, r4, asr #4
d0019164:	1310f244 	tstne	r0, #68, 4	; 0x40000004	; <UNPREDICTABLE>
d0019168:	7f96f5b7 	svcvc	0x0096f5b7
d001916c:	4619bf18 	sadd16mi	fp, r9, r8
d0019170:	f1bae7d3 			; <UNDEFINED> instruction: 0xf1bae7d3
d0019174:	46420f0f 	strbmi	r0, [r2], -pc, lsl #30
d0019178:	0101f04f 	tsteq	r1, pc, asr #32	; <UNPREDICTABLE>
d001917c:	d1174620 	tstle	r7, r0, lsr #12
d0019180:	fee2f7fb 	mcr2	7, 7, pc, cr2, cr11, {7}	; <UNPREDICTABLE>
d0019184:	6108f244 	tstvs	r8, r4, asr #4	; <UNPREDICTABLE>
d0019188:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d001918c:	212efd67 	msrcs	CPSR_fsx, r7, ror #26
d0019190:	fe55f7f9 	mrc2	7, 2, pc, cr5, cr9, {7}
d0019194:	b1204605 			; <UNDEFINED> instruction: 0xb1204605
d0019198:	4632465b 			; <UNDEFINED> instruction: 0x4632465b
d001919c:	13eef899 	mvnne	pc, #10027008	; 0x990000
d00191a0:	6da3e6c7 	stcvs	6, cr14, [r3, #796]!	; 0x31c
d00191a4:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d00191a8:	4b30ad06 	blmi	0xd0c445c8
d00191ac:	e67c447b 			; <UNDEFINED> instruction: 0xe67c447b
d00191b0:	0f11f1ba 	svceq	0x0011f1ba
d00191b4:	f7fbd115 			; <UNDEFINED> instruction: 0xf7fbd115
d00191b8:	f244fec7 	vceq.f32	<illegal reg q15.5>, q10, <illegal reg q3.5>
d00191bc:	46206108 	strtmi	r6, [r0], -r8, lsl #2
d00191c0:	fd4cf7fb 	stc2l	7, cr15, [ip, #-1004]	; 0xfffffc14
d00191c4:	2b5b6ae3 	blcs	0xd16f3d58
d00191c8:	462bd104 	strtmi	sp, [fp], -r4, lsl #2
d00191cc:	f8994632 			; <UNDEFINED> instruction: 0xf8994632
d00191d0:	e6d013ee 	ldrb	r1, [r0], lr, ror #7
d00191d4:	2b006da3 	blcs	0xd0034868
d00191d8:	acedf47f 	cfstrdge	mvd15, [sp], #508	; 0x1fc
d00191dc:	447b4b24 	ldrbtmi	r4, [fp], #-2852	; 0xfffff4dc
d00191e0:	f1bae663 			; <UNDEFINED> instruction: 0xf1bae663
d00191e4:	d1070f08 	tstle	r7, r8, lsl #30
d00191e8:	feaef7fb 	mcr2	7, 5, pc, cr14, cr11, {7}	; <UNPREDICTABLE>
d00191ec:	6108f244 	tstvs	r8, r4, asr #4	; <UNPREDICTABLE>
d00191f0:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d00191f4:	e6e1fd33 			; <UNDEFINED> instruction: 0xe6e1fd33
d00191f8:	fea6f7fb 	mcr2	7, 5, pc, cr6, cr11, {7}	; <UNPREDICTABLE>
d00191fc:	0108f646 	tsteq	r8, r6, asr #12	; <UNPREDICTABLE>
d0019200:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0019204:	f1bafd2b 			; <UNDEFINED> instruction: 0xf1bafd2b
d0019208:	e4f10f01 	ldrbt	r0, [r1], #3841	; 0xf01
d001920c:	46514a19 			; <UNDEFINED> instruction: 0x46514a19
d0019210:	447a4648 	ldrbtmi	r4, [sl], #-1608	; 0xfffff9b8
d0019214:	fb2ef7f7 	blx	0xd0bd71fa
d0019218:	b3684605 	cmnlt	r8, #5242880	; 0x500000
d001921c:	46204659 			; <UNDEFINED> instruction: 0x46204659
d0019220:	fd7bf7fb 	ldc2l	7, cr15, [fp, #-1004]!	; 0xfffffc14
d0019224:	bf00e651 	svclt	0x0000e651
d0019228:	00149244 	andseq	r9, r4, r4, asr #4
d001922c:	ffffd566 			; <UNDEFINED> instruction: 0xffffd566
d0019230:	fffffbe2 			; <UNDEFINED> instruction: 0xfffffbe2
d0019234:	fffffba5 			; <UNDEFINED> instruction: 0xfffffba5
d0019238:	fffffb89 			; <UNDEFINED> instruction: 0xfffffb89
d001923c:	fffffb81 			; <UNDEFINED> instruction: 0xfffffb81
d0019240:	fffffb43 			; <UNDEFINED> instruction: 0xfffffb43
d0019244:	fffffb4c 			; <UNDEFINED> instruction: 0xfffffb4c
d0019248:	fffffaed 			; <UNDEFINED> instruction: 0xfffffaed
d001924c:	fffffa02 			; <UNDEFINED> instruction: 0xfffffa02
d0019250:	fffff99f 			; <UNDEFINED> instruction: 0xfffff99f
d0019254:	fffff957 			; <UNDEFINED> instruction: 0xfffff957
d0019258:	fffff934 			; <UNDEFINED> instruction: 0xfffff934
d001925c:	0000815e 	andeq	r8, r0, lr, asr r1
d0019260:	fffff8e1 			; <UNDEFINED> instruction: 0xfffff8e1
d0019264:	fffff8b0 			; <UNDEFINED> instruction: 0xfffff8b0
d0019268:	fffff8c0 			; <UNDEFINED> instruction: 0xfffff8c0
d001926c:	fffff737 			; <UNDEFINED> instruction: 0xfffff737
d0019270:	fffff723 			; <UNDEFINED> instruction: 0xfffff723
d0019274:	ffffbb0c 			; <UNDEFINED> instruction: 0xffffbb0c
d0019278:	2b006da3 	blcs	0xd003490c
d001927c:	ac9bf47f 	cfldrsge	mvf15, [fp], {127}	; 0x7f
d0019280:	3480f8df 	strcc	pc, [r0], #2271	; 0x8df
d0019284:	e610447b 			; <UNDEFINED> instruction: 0xe610447b
d0019288:	46202126 	strtmi	r2, [r0], -r6, lsr #2
d001928c:	fdd7f7f9 	ldc2l	7, cr15, [r7, #996]	; 0x3e4
d0019290:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d0019294:	f8df80a6 			; <UNDEFINED> instruction: 0xf8df80a6
d0019298:	f2402470 	vqshl.s8	q9, q8, q0
d001929c:	46201101 	strtmi	r1, [r0], -r1, lsl #2
d00192a0:	447a6a67 	ldrbtmi	r6, [sl], #-2663	; 0xfffff599
d00192a4:	9028f8d4 	ldrdls	pc, [r8], -r4	; <UNPREDICTABLE>
d00192a8:	a030f894 	mlasge	r0, r4, r8, pc	; <UNPREDICTABLE>
d00192ac:	b034f8d4 	ldrsbtlt	pc, [r4], -r4	; <UNPREDICTABLE>
d00192b0:	6306e9d4 	movwvs	lr, #27092	; 0x69d4
d00192b4:	f7f99307 			; <UNDEFINED> instruction: 0xf7f99307
d00192b8:	9b07fdd0 	blls	0xd0218a00
d00192bc:	f508b948 			; <UNDEFINED> instruction: 0xf508b948
d00192c0:	f8d85892 			; <UNDEFINED> instruction: 0xf8d85892
d00192c4:	3b013000 	blcc	0xd00652cc
d00192c8:	3000f8c8 	andcc	pc, r0, r8, asr #17
d00192cc:	e8bdb01f 	pop	{r0, r1, r2, r3, r4, ip, sp, pc}
d00192d0:	461a8ff0 	ssub8mi	r8, sl, r0
d00192d4:	46204631 			; <UNDEFINED> instruction: 0x46204631
d00192d8:	f7f79307 			; <UNDEFINED> instruction: 0xf7f79307
d00192dc:	1e01fa15 			; <UNDEFINED> instruction: 0x1e01fa15
d00192e0:	f2809b07 	vqdmlsl.s<illegal width 8>	<illegal reg q4.5>, d0, d7
d00192e4:	461a81d1 			; <UNDEFINED> instruction: 0x461a81d1
d00192e8:	46204631 			; <UNDEFINED> instruction: 0x46204631
d00192ec:	fa2cf7f7 	blx	0xd0b572d0
d00192f0:	db6f1e02 	blle	0xd1be0b00
d00192f4:	fb06263c 	blx	0xd01a2bee
d00192f8:	f5064602 			; <UNDEFINED> instruction: 0xf5064602
d00192fc:	f896365f 			; <UNDEFINED> instruction: 0xf896365f
d0019300:	f1b883f0 			; <UNDEFINED> instruction: 0xf1b883f0
d0019304:	f0000f00 			; <UNDEFINED> instruction: 0xf0000f00
d0019308:	6da381e0 	stfvsd	f0, [r3, #896]!	; 0x380
d001930c:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0019310:	4bfeac52 	blmi	0xcffc4460
d0019314:	f8c4447b 			; <UNDEFINED> instruction: 0xf8c4447b
d0019318:	e9c4b068 	stmib	r4, {r3, r5, r6, ip, sp, pc}^
d001931c:	e9c43716 	stmib	r4, {r1, r2, r4, r8, r9, sl, ip, sp}^
d0019320:	e5489a18 	strb	r9, [r8, #-2584]	; 0xfffff5e8
d0019324:	d1052b0e 	tstle	r5, lr, lsl #22
d0019328:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d001932c:	f896fd61 			; <UNDEFINED> instruction: 0xf896fd61
d0019330:	e5e02656 	strb	r2, [r0, #1622]!	; 0x656
d0019334:	2b09b15b 	blcs	0xd02858a8
d0019338:	2b0ad009 	blcs	0xd02cd364
d001933c:	6ae3d14a 	bvs	0xcf90d86c
d0019340:	d1432b5b 	cmple	r3, fp, asr fp
d0019344:	46204642 	strtmi	r4, [r0], -r2, asr #12
d0019348:	fd20f7fb 	stc2	7, cr15, [r0, #-1004]!	; 0xfffffc14
d001934c:	4620e032 			; <UNDEFINED> instruction: 0x4620e032
d0019350:	f7fb9107 			; <UNDEFINED> instruction: 0xf7fb9107
d0019354:	2030fd4d 	eorscs	pc, r0, sp, asr #26
d0019358:	6ae39907 	bvs	0xcf8ff77c
d001935c:	4101fb00 	tstmi	r1, r0, lsl #22	; <UNPREDICTABLE>
d0019360:	f5012b5b 			; <UNDEFINED> instruction: 0xf5012b5b
d0019364:	f89111a4 			; <UNDEFINED> instruction: 0xf89111a4
d0019368:	d1073655 	tstle	r7, r5, asr r6
d001936c:	d15b2b09 	cmple	fp, r9, lsl #22
d0019370:	21002201 	tstcs	r0, r1, lsl #4
d0019374:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0019378:	e468fb23 	strbt	pc, [r8], #-2851	; 0xfffff4dd	; <UNPREDICTABLE>
d001937c:	d1532b09 	cmple	r3, r9, lsl #22
d0019380:	2b006da3 	blcs	0xd0034a14
d0019384:	ac17f47f 	cfldrsge	mvf15, [r7], {127}	; 0x7f
d0019388:	447b4be1 	ldrbtmi	r4, [fp], #-3041	; 0xfffff41f
d001938c:	f011e7c3 			; <UNDEFINED> instruction: 0xf011e7c3
d0019390:	d11f08f7 			; <UNDEFINED> instruction: 0xd11f08f7
d0019394:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d0019398:	fdd6f7fb 	ldc2l	7, cr15, [r6, #1004]	; 0x3ec
d001939c:	6108f244 	tstvs	r8, r4, asr #4	; <UNPREDICTABLE>
d00193a0:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d00193a4:	6ae3fc5b 	bvs	0xcf918518
d00193a8:	f8962b5b 			; <UNDEFINED> instruction: 0xf8962b5b
d00193ac:	d10433ec 	smlattle	r4, ip, r3, r3
d00193b0:	d1392b08 	teqle	r9, r8, lsl #22
d00193b4:	46412201 	strbmi	r2, [r1], -r1, lsl #4
d00193b8:	2b08e7dc 	blcs	0xd0253330
d00193bc:	6da3d134 	stfvsd	f5, [r3, #208]!	; 0xd0
d00193c0:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d00193c4:	4bd3abf8 	blmi	0xcf5043ac
d00193c8:	e7a4447b 			; <UNDEFINED> instruction: 0xe7a4447b
d00193cc:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d00193d0:	e584fd0f 	str	pc, [r4, #3343]	; 0xd0f
d00193d4:	2b006da3 	blcs	0xd0034a68
d00193d8:	abedf47f 	blge	0xcfb965dc
d00193dc:	447b4bce 	ldrbtmi	r4, [fp], #-3022	; 0xfffff432
d00193e0:	212ae799 			; <UNDEFINED> instruction: 0x212ae799
d00193e4:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d00193e8:	2800fd2a 	stmdacs	r0, {r1, r3, r5, r8, sl, fp, ip, sp, lr, pc}
d00193ec:	2100d05d 	qaddcs	sp, sp, r0
d00193f0:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d00193f4:	2807fbbb 	stmdacs	r7, {r0, r1, r3, r4, r5, r7, r8, r9, fp, ip, sp, lr, pc}
d00193f8:	d1174605 	tstle	r7, r5, lsl #12
d00193fc:	213db17e 	teqcs	sp, lr, ror r1
d0019400:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d0019404:	b150fd1c 	cmplt	r0, ip, lsl sp	; <UNPREDICTABLE>
d0019408:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d001940c:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0019410:	2204fc25 	andcs	pc, r4, #9472	; 0x2500
d0019414:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d0019418:	ff88f7fc 			; <UNDEFINED> instruction: 0xff88f7fc
d001941c:	f44fe018 	vst4.8	{d30-d33}, [pc :64], r8
d0019420:	462041d0 			; <UNDEFINED> instruction: 0x462041d0
d0019424:	fc1af7fb 	ldc2	7, cr15, [sl], {251}	; 0xfb
d0019428:	e4c42504 	strb	r2, [r4], #1284	; 0x504
d001942c:	d11e2805 	tstle	lr, r5, lsl #16
d0019430:	59674db3 	stmdbpl	r7!, {r0, r1, r4, r5, r7, r8, sl, fp, lr}^
d0019434:	213db1a6 	teqcs	sp, r6, lsr #3
d0019438:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d001943c:	b178fd00 	cmnlt	r8, r0, lsl #26	; <UNPREDICTABLE>
d0019440:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d0019444:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0019448:	4639fc09 	ldrtmi	pc, [r9], -r9, lsl #24	; <UNPREDICTABLE>
d001944c:	fd90f7fe 	ldc2	7, cr15, [r0, #1016]	; 0x3f8
d0019450:	4106f64b 	tstmi	r6, fp, asr #12	; <UNPREDICTABLE>
d0019454:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0019458:	f246fc01 			; <UNDEFINED> instruction: 0xf246fc01
d001945c:	e6660108 	strbt	r0, [r6], -r8, lsl #2
d0019460:	41d0f44f 	bicsmi	pc, r0, pc, asr #8
d0019464:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0019468:	5167fbf9 	strdpl	pc, [r7, #-185]!	; 0xffffff47
d001946c:	2804e52d 	stmdacs	r4, {r0, r2, r3, r5, r8, sl, sp, lr, pc}
d0019470:	6da3d006 	stcvs	0, cr13, [r3, #24]!
d0019474:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0019478:	4ba8ac9e 	blmi	0xcea446f8
d001947c:	e514447b 	ldr	r4, [r4, #-1147]	; 0xfffffb85
d0019480:	213db166 	teqcs	sp, r6, ror #2
d0019484:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d0019488:	b138fcda 	teqlt	r8, sl	; <illegal shifter operand>	; <UNPREDICTABLE>
d001948c:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d0019490:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0019494:	2201fbe3 	andcs	pc, r1, #232448	; 0x38c00
d0019498:	e7bc4611 			; <UNDEFINED> instruction: 0xe7bc4611
d001949c:	41d0f44f 	bicsmi	pc, r0, pc, asr #8
d00194a0:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d00194a4:	f7fffbdb 			; <UNDEFINED> instruction: 0xf7fffbdb
d00194a8:	2128bb86 	smlawbcs	r8, r6, fp, fp
d00194ac:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d00194b0:	2800fcc6 	stmdacs	r0, {r1, r2, r6, r7, sl, fp, ip, sp, lr, pc}
d00194b4:	6ae3d051 	bvs	0xcf90d600
d00194b8:	d1322b2a 	teqle	r2, sl, lsr #22
d00194bc:	f2406ce2 	sha1c.32	q11, q8, q9
d00194c0:	429a1301 	addsmi	r1, sl, #67108864	; 0x4000000
d00194c4:	6be2d12d 	blvs	0xcf8cd980
d00194c8:	6ba14620 	blvs	0xce86ad50
d00194cc:	f91cf7f7 			; <UNDEFINED> instruction: 0xf91cf7f7
d00194d0:	db261e05 	blle	0xd09a0cec
d00194d4:	fb032330 	blx	0xd00e219e
d00194d8:	f5034305 			; <UNDEFINED> instruction: 0xf5034305
d00194dc:	f89313a4 			; <UNDEFINED> instruction: 0xf89313a4
d00194e0:	2b0c3655 	blcs	0xd0326e3c
d00194e4:	4620d11d 			; <UNDEFINED> instruction: 0x4620d11d
d00194e8:	fc8ef7f9 	stc2	7, cr15, [lr], {249}	; 0xf9
d00194ec:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d00194f0:	4a8bfc8b 	bmi	0xce318724
d00194f4:	46202129 	strtmi	r2, [r0], -r9, lsr #2
d00194f8:	f7f9447a 			; <UNDEFINED> instruction: 0xf7f9447a
d00194fc:	2800fcae 	stmdacs	r0, {r1, r2, r3, r5, r7, sl, fp, ip, sp, lr, pc}
d0019500:	ab59f43f 	blge	0xd1696604
d0019504:	21284a87 	smlawbcs	r8, r7, sl, r4
d0019508:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d001950c:	fca5f7f9 	stc2	7, cr15, [r5], #996	; 0x3e4
d0019510:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0019514:	4629ab50 			; <UNDEFINED> instruction: 0x4629ab50
d0019518:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d001951c:	f7ffff4f 			; <UNDEFINED> instruction: 0xf7ffff4f
d0019520:	2200bb96 	andcs	fp, r0, #153600	; 0x25800
d0019524:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d0019528:	ff00f7fc 			; <UNDEFINED> instruction: 0xff00f7fc
d001952c:	46054a7e 			; <UNDEFINED> instruction: 0x46054a7e
d0019530:	447a2129 	ldrbtmi	r2, [sl], #-297	; 0xfffffed7
d0019534:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d0019538:	2d03fc90 	stccs	12, cr15, [r3, #-576]	; 0xfffffdc0
d001953c:	ac62f47f 	cfstrdge	mvd15, [r2], #-508	; 0xfffffe04
d0019540:	7191f44f 	orrsvc	pc, r1, pc, asr #8
d0019544:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d0019548:	2800fc7a 	stmdacs	r0, {r1, r3, r4, r5, r6, sl, fp, ip, sp, lr, pc}
d001954c:	acbdf43f 	cfldrsge	mvf15, [sp], #252	; 0xfc
d0019550:	2300496b 	movwcs	r4, #2411	; 0x96b
d0019554:	58614632 	stmdapl	r1!, {r1, r4, r5, r9, sl, lr}^
d0019558:	212be4eb 			; <UNDEFINED> instruction: 0x212be4eb
d001955c:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d0019560:	b168fc6e 	msrlt	SPSR_f, lr, ror #24
d0019564:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d0019568:	fb00f7ff 	blx	0xd005756e
d001956c:	46052802 	strmi	r2, [r5], -r2, lsl #16
d0019570:	6da3d11f 	stfvsd	f5, [r3, #124]!	; 0x7c
d0019574:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0019578:	4b6cac1e 	blmi	0xd1b445f8
d001957c:	e494447b 	ldr	r4, [r4], #1147	; 0x47b
d0019580:	4620212d 	strtmi	r2, [r0], -sp, lsr #2
d0019584:	fc5bf7f9 	mrrc2	7, 15, pc, fp, cr9	; <UNPREDICTABLE>
d0019588:	d1eb2800 	mvnle	r2, r0, lsl #16
d001958c:	46202121 	strtmi	r2, [r0], -r1, lsr #2
d0019590:	fc55f7f9 	mrrc2	7, 15, pc, r5, cr9	; <UNPREDICTABLE>
d0019594:	d1e52800 	mvnle	r2, r0, lsl #16
d0019598:	4620217e 			; <UNDEFINED> instruction: 0x4620217e
d001959c:	fc4ff7f9 	mcrr2	7, 15, pc, pc, cr9	; <UNPREDICTABLE>
d00195a0:	28004605 	stmdacs	r0, {r0, r2, r9, sl, lr}
d00195a4:	4962d1de 	stmdbmi	r2!, {r1, r2, r3, r4, r6, r7, r8, ip, lr, pc}^
d00195a8:	44794620 	ldrbtmi	r4, [r9], #-1568	; 0xfffff9e0
d00195ac:	fdfcf7f6 	ldc2l	7, cr15, [ip, #984]!	; 0x3d8
d00195b0:	2803e401 	stmdacs	r3, {r0, sl, sp, lr, pc}
d00195b4:	f1bbd109 			; <UNDEFINED> instruction: 0xf1bbd109
d00195b8:	d0160f21 	andsle	r0, r6, r1, lsr #30
d00195bc:	2b006da3 	blcs	0xd0034c50
d00195c0:	ac83f47f 	cfstrsge	mvf15, [r3], {127}	; 0x7f
d00195c4:	447b4b5b 	ldrbtmi	r4, [fp], #-2907	; 0xfffff4a5
d00195c8:	f1bbe46f 			; <UNDEFINED> instruction: 0xf1bbe46f
d00195cc:	d1020f2d 	tstle	r2, sp, lsr #30
d00195d0:	2140f244 	cmpcs	r0, r4, asr #4	; <UNPREDICTABLE>
d00195d4:	f1bbe59b 			; <UNDEFINED> instruction: 0xf1bbe59b
d00195d8:	d1020f7e 	tstle	r2, lr, ror pc
d00195dc:	31c0f244 	biccc	pc, r0, r4, asr #4
d00195e0:	f1bbe595 			; <UNDEFINED> instruction: 0xf1bbe595
d00195e4:	f47f0f21 			; <UNDEFINED> instruction: 0xf47f0f21
d00195e8:	f44fabe6 			; <UNDEFINED> instruction: 0xf44fabe6
d00195ec:	46205120 	strtmi	r5, [r0], -r0, lsr #2
d00195f0:	fb34f7fb 	blx	0xd0d575e6
d00195f4:	f7fb2100 			; <UNDEFINED> instruction: 0xf7fb2100
d00195f8:	f7ffffa7 			; <UNDEFINED> instruction: 0xf7ffffa7
d00195fc:	2000badc 	ldrdcs	fp, [r0], -ip
d0019600:	2e00e664 	cfmadd32cs	mvax3, mvfx14, mvfx0, mvfx4
d0019604:	ad81f43f 	cfstrsge	mvf15, [r1, #252]	; 0xfc
d0019608:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d001960c:	f641fbfd 			; <UNDEFINED> instruction: 0xf641fbfd
d0019610:	46200108 	strtmi	r0, [r0], -r8, lsl #2
d0019614:	fb22f7fb 	blx	0xd08d760a
d0019618:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d001961c:	fb1ef7fb 	blx	0xd07d7612
d0019620:	d0072f3d 	andle	r2, r7, sp, lsr pc
d0019624:	41f0f44f 	mvnsmi	pc, pc, asr #8
d0019628:	fb18f7fb 	blx	0xd065761e
d001962c:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d0019630:	fb14f7fb 	blx	0xd0557626
d0019634:	46202201 	strtmi	r2, [r0], -r1, lsl #4
d0019638:	f7fc4611 			; <UNDEFINED> instruction: 0xf7fc4611
d001963c:	2f3dfe77 	svccs	0x003dfe77
d0019640:	ad6ef43f 	cfstrdge	mvd15, [lr, #-252]!	; 0xffffff04
d0019644:	4106f64b 	tstmi	r6, fp, asr #12	; <UNPREDICTABLE>
d0019648:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d001964c:	f46ffb07 			; <UNDEFINED> instruction: 0xf46ffb07
d0019650:	18fb7392 	ldmne	fp!, {r1, r4, r7, r8, r9, ip, sp, lr}^
d0019654:	f63f2b08 			; <UNDEFINED> instruction: 0xf63f2b08
d0019658:	a202ad63 	andge	sl, r2, #6336	; 0x18c0
d001965c:	3023f852 	eorcc	pc, r3, r2, asr r8	; <UNPREDICTABLE>
d0019660:	4710441a 			; <UNDEFINED> instruction: 0x4710441a
d0019664:	fffffab3 			; <UNDEFINED> instruction: 0xfffffab3
d0019668:	fffffad5 			; <UNDEFINED> instruction: 0xfffffad5
d001966c:	fffffabd 			; <UNDEFINED> instruction: 0xfffffabd
d0019670:	fffffabd 			; <UNDEFINED> instruction: 0xfffffabd
d0019674:	fffffadb 			; <UNDEFINED> instruction: 0xfffffadb
d0019678:	fffffae1 			; <UNDEFINED> instruction: 0xfffffae1
d001967c:	fffffae7 			; <UNDEFINED> instruction: 0xfffffae7
d0019680:	fffffaed 			; <UNDEFINED> instruction: 0xfffffaed
d0019684:	fffffaed 			; <UNDEFINED> instruction: 0xfffffaed
d0019688:	fb062630 	blx	0xd01a2f52
d001968c:	f5064601 			; <UNDEFINED> instruction: 0xf5064601
d0019690:	f89616a4 			; <UNDEFINED> instruction: 0xf89616a4
d0019694:	f1b88660 			; <UNDEFINED> instruction: 0xf1b88660
d0019698:	f47f0f00 			; <UNDEFINED> instruction: 0xf47f0f00
d001969c:	f896ae36 			; <UNDEFINED> instruction: 0xf896ae36
d00196a0:	2b0d3655 	blcs	0xd0366ffc
d00196a4:	ae3ef47f 	mrcge	4, 1, APSR_nzcv, cr14, cr15, {3}
d00196a8:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d00196ac:	4a22fba1 	bmi	0xd08d8538
d00196b0:	4620212e 	strtmi	r2, [r0], -lr, lsr #2
d00196b4:	f7f9447a 			; <UNDEFINED> instruction: 0xf7f9447a
d00196b8:	2800fbd0 	stmdacs	r0, {r4, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d00196bc:	aa7bf43f 	bge	0xd1f167c0
d00196c0:	46422301 	strbmi	r2, [r2], -r1, lsl #6
d00196c4:	1656f896 			; <UNDEFINED> instruction: 0x1656f896
d00196c8:	f896e433 			; <UNDEFINED> instruction: 0xf896e433
d00196cc:	290f13ec 	stmdbcs	pc, {r2, r3, r5, r6, r7, r8, r9, ip}	; <UNPREDICTABLE>
d00196d0:	ae5df47f 	mrcge	4, 2, APSR_nzcv, cr13, cr15, {3}
d00196d4:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d00196d8:	fc36f7fb 	ldc2	7, cr15, [r6], #-1004	; 0xfffffc14
d00196dc:	6108f244 	tstvs	r8, r4, asr #4	; <UNPREDICTABLE>
d00196e0:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d00196e4:	4a15fabb 	bmi	0xd05981d8
d00196e8:	447a212e 	ldrbtmi	r2, [sl], #-302	; 0xfffffed2
d00196ec:	fbb5f7f9 	blx	0xced976da
d00196f0:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d00196f4:	2301aa60 	movwcs	sl, #6752	; 0x1a60
d00196f8:	f8964642 			; <UNDEFINED> instruction: 0xf8964642
d00196fc:	e41813ee 	ldr	r1, [r8], #-1006	; 0xfffffc12
d0019700:	00149244 	andseq	r9, r4, r4, asr #4
d0019704:	fffff734 			; <UNDEFINED> instruction: 0xfffff734
d0019708:	fffff737 			; <UNDEFINED> instruction: 0xfffff737
d001970c:	fffff6e1 			; <UNDEFINED> instruction: 0xfffff6e1
d0019710:	fffff6cc 			; <UNDEFINED> instruction: 0xfffff6cc
d0019714:	fffff68e 			; <UNDEFINED> instruction: 0xfffff68e
d0019718:	fffff6a7 			; <UNDEFINED> instruction: 0xfffff6a7
d001971c:	fffff63f 			; <UNDEFINED> instruction: 0xfffff63f
d0019720:	fffff5f6 			; <UNDEFINED> instruction: 0xfffff5f6
d0019724:	fffff60b 			; <UNDEFINED> instruction: 0xfffff60b
d0019728:	fffff60a 			; <UNDEFINED> instruction: 0xfffff60a
d001972c:	ffffcbc2 			; <UNDEFINED> instruction: 0xffffcbc2
d0019730:	fffff59f 			; <UNDEFINED> instruction: 0xfffff59f
d0019734:	ffffcb9e 			; <UNDEFINED> instruction: 0xffffcb9e
d0019738:	fffff377 			; <UNDEFINED> instruction: 0xfffff377
d001973c:	fffff341 			; <UNDEFINED> instruction: 0xfffff341

Disassembly of section .text.condition.constprop.0:

d001977c <.text.condition.constprop.0>:
d001977c:	4c0ab510 	cfstr32mi	mvfx11, [sl], {16}
d0019780:	4a0a2128 	bmi	0xd02a1c28
d0019784:	447a447c 	ldrbtmi	r4, [sl], #-1148	; 0xfffffb84
d0019788:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d001978c:	2202fb66 	andcs	pc, r2, #104448	; 0x19800
d0019790:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d0019794:	fdcaf7fc 	stc2l	7, cr15, [sl, #1008]	; 0x3f0
d0019798:	46204a05 	strtmi	r4, [r0], -r5, lsl #20
d001979c:	447a2129 	ldrbtmi	r2, [sl], #-297	; 0xfffffed7
d00197a0:	4010e8bd 			; <UNDEFINED> instruction: 0x4010e8bd
d00197a4:	bb59f7f9 	bllt	0xd1697790
d00197a8:	0000cc80 	andeq	ip, r0, r0, lsl #25
d00197ac:	ffffffb6 			; <UNDEFINED> instruction: 0xffffffb6
d00197b0:	ffffffbc 			; <UNDEFINED> instruction: 0xffffffbc

Disassembly of section .text.simple_expression.constprop.0:

d0019954 <.text.simple_expression.constprop.0>:
d0019954:	3428f8df 	strtcc	pc, [r8], #-2271	; 0xfffff721
d0019958:	6cdb447b 	cfldrdvs	mvd4, [fp], {123}	; 0x7b
d001995c:	e92d2b3d 	push	{r0, r2, r3, r4, r5, r8, r9, fp, sp}
d0019960:	b0854ff0 	strdlt	r4, [r5], r0
d0019964:	f46fd01f 	vld4.8	{d29-d32}, [pc :64]
d0019968:	191a7492 	ldmdbne	sl, {r1, r4, r7, sl, ip, sp, lr}
d001996c:	d91a2a01 	ldmdble	sl, {r0, r9, fp, sp}
d0019970:	7094f46f 	addsvc	pc, r4, pc, ror #8
d0019974:	2b044403 	blcs	0xd012a988
d0019978:	2300bf8c 	movwcs	fp, #3980	; 0xf8c
d001997c:	f8df2301 			; <UNDEFINED> instruction: 0xf8df2301
d0019980:	93004404 	movwls	r4, #1028	; 0x404
d0019984:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d0019988:	6ae2447c 	bvs	0xcf8aab80
d001998c:	d101429a 			; <UNDEFINED> instruction: 0xd101429a
d0019990:	b9539b00 	ldmdblt	r3, {r8, r9, fp, ip, pc}^
d0019994:	220348fc 	andcs	r4, r3, #252, 16	; 0xfc0000
d0019998:	44782101 	ldrbtmi	r2, [r8], #-257	; 0xfffffeff
d001999c:	e8bdb005 	pop	{r0, r2, ip, sp, pc}
d00199a0:	f7fc4ff0 			; <UNDEFINED> instruction: 0xf7fc4ff0
d00199a4:	2301bcc3 	movwcs	fp, #7363	; 0x1cc3
d00199a8:	e9d4e7e9 	ldmib	r4, {r0, r3, r5, r6, r7, r8, r9, sl, sp, lr, pc}^
d00199ac:	6b631206 	blvs	0xd18de1cc
d00199b0:	92024620 	andls	r4, r2, #32, 12	; 0x2000000
d00199b4:	91019303 	tstls	r1, r3, lsl #6
d00199b8:	f8d46a67 			; <UNDEFINED> instruction: 0xf8d46a67
d00199bc:	f8948028 			; <UNDEFINED> instruction: 0xf8948028
d00199c0:	f7f69030 			; <UNDEFINED> instruction: 0xf7f69030
d00199c4:	a901fea1 	stmdbge	r1, {r0, r5, r7, r9, sl, fp, ip, sp, lr, pc}
d00199c8:	c90e1e05 	stmdbgt	lr, {r0, r2, r9, sl, fp, ip}
d00199cc:	81c8f280 	bichi	pc, r8, r0, lsl #5
d00199d0:	93014620 	movwls	r4, #5664	; 0x1620
d00199d4:	feb8f7f6 	mrc2	7, 5, pc, cr8, cr6, {7}
d00199d8:	0a00f1b0 	beq	0xd00560a0
d00199dc:	db159b01 	blle	0xd05805e8
d00199e0:	fb02223c 	blx	0xd00a22da
d00199e4:	f504440a 			; <UNDEFINED> instruction: 0xf504440a
d00199e8:	f894345f 			; <UNDEFINED> instruction: 0xf894345f
d00199ec:	b1ba23f0 			; <UNDEFINED> instruction: 0xb1ba23f0
d00199f0:	447a4ae6 	ldrbtmi	r4, [sl], #-2790	; 0xfffff51a
d00199f4:	b9316d91 	ldmdblt	r1!, {r0, r4, r7, r8, sl, fp, sp, lr}
d00199f8:	447949e5 	ldrbtmi	r4, [r9], #-2533	; 0xfffff61b
d00199fc:	e9c26693 	stmib	r2, {r0, r1, r4, r7, r9, sl, sp, lr}^
d0019a00:	e9c21716 	stmib	r2, {r1, r2, r4, r8, r9, sl, ip}^
d0019a04:	b0058918 	andlt	r8, r5, r8, lsl r9
d0019a08:	8ff0e8bd 	svchi	0x00f0e8bd
d0019a0c:	2a006da2 	bcs	0xd003509c
d0019a10:	4ae0d1f9 	bmi	0xcf84e1fc
d0019a14:	e9c4447a 	stmib	r4, {r1, r3, r4, r5, r6, sl, lr}^
d0019a18:	e9c42716 	stmib	r4, {r1, r2, r4, r8, r9, sl, sp}^
d0019a1c:	e01a8918 	ands	r8, sl, r8, lsl r9
d0019a20:	63ecf894 	mvnvs	pc, #148, 16	; 0x940000
d0019a24:	0202f026 	andeq	pc, r2, #38	; 0x26
d0019a28:	d15a2a0d 	cmple	sl, sp, lsl #20
d0019a2c:	93004cda 	movwls	r4, #3290	; 0xcda
d0019a30:	4620447c 			; <UNDEFINED> instruction: 0x4620447c
d0019a34:	f9e8f7f9 			; <UNDEFINED> instruction: 0xf9e8f7f9
d0019a38:	4620213d 			; <UNDEFINED> instruction: 0x4620213d
d0019a3c:	f9fff7f9 			; <UNDEFINED> instruction: 0xf9fff7f9
d0019a40:	6da2b958 			; <UNDEFINED> instruction: 0x6da2b958
d0019a44:	d1de2a00 	bicsle	r2, lr, r0, lsl #20
d0019a48:	9b004ad4 	blls	0xd002c5a0
d0019a4c:	e9c4447a 	stmib	r4, {r1, r3, r4, r5, r6, sl, lr}^
d0019a50:	e9c48918 	stmib	r4, {r3, r4, r8, fp, pc}^
d0019a54:	66a32716 	ssatvs	r2, #4, r6, lsl #14
d0019a58:	2d00e7d5 	stccs	7, cr14, [r0, #-852]	; 0xfffffcac
d0019a5c:	bfac48d0 	svclt	0x00ac48d0
d0019a60:	233c2330 	teqcs	ip, #48, 6	; 0xc0000000
d0019a64:	bfaa4478 	svclt	0x00aa4478
d0019a68:	4405fb03 	strmi	pc, [r5], #-2819	; 0xfffff4fd
d0019a6c:	440afb03 	strmi	pc, [sl], #-2819	; 0xfffff4fd
d0019a70:	14a4f504 	strtne	pc, [r4], #1284	; 0x504
d0019a74:	bfb69000 	svclt	0x00b69000
d0019a78:	345ff504 	ldrbcc	pc, [pc], #-1284	; 0xd0019a80	; <UNPREDICTABLE>
d0019a7c:	4656f894 			; <UNDEFINED> instruction: 0x4656f894
d0019a80:	43eef894 	mvnmi	pc, #148, 16	; 0x940000
d0019a84:	f7fd4621 			; <UNDEFINED> instruction: 0xf7fd4621
d0019a88:	9800fe07 	stmdals	r0, {r0, r1, r2, r9, sl, fp, ip, sp, lr, pc}
d0019a8c:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d0019a90:	f8e4f7fb 			; <UNDEFINED> instruction: 0xf8e4f7fb
d0019a94:	98002d00 	stmdals	r0, {r8, sl, fp, sp}
d0019a98:	4629db18 			; <UNDEFINED> instruction: 0x4629db18
d0019a9c:	f9a8f7fb 			; <UNDEFINED> instruction: 0xf9a8f7fb
d0019aa0:	f24448c0 	vadd.i8	q10, q10, q0
d0019aa4:	44786101 	ldrbtmi	r6, [r8], #-257	; 0xfffffeff
d0019aa8:	f8d8f7fb 			; <UNDEFINED> instruction: 0xf8d8f7fb
d0019aac:	4105f64b 	tstmi	r5, fp, asr #12	; <UNPREDICTABLE>
d0019ab0:	f8d4f7fb 			; <UNDEFINED> instruction: 0xf8d4f7fb
d0019ab4:	731af44f 	tstvc	sl, #1325400064	; 0x4f000000	; <UNPREDICTABLE>
d0019ab8:	0004fb03 	andeq	pc, r4, r3, lsl #22
d0019abc:	3068f500 	rsbcc	pc, r8, r0, lsl #10
d0019ac0:	b0058d00 	andlt	r8, r5, r0, lsl #26
d0019ac4:	4ff0e8bd 	svcmi	0x00f0e8bd
d0019ac8:	bac8f7fc 	blt	0xcf257ac0
d0019acc:	21014652 	tstcs	r1, r2, asr r6
d0019ad0:	f7fb9000 			; <UNDEFINED> instruction: 0xf7fb9000
d0019ad4:	f244fa39 	vpmin.s8	d31, d4, d25
d0019ad8:	98006108 	stmdals	r0, {r3, r8, sp, lr}
d0019adc:	f8bef7fb 			; <UNDEFINED> instruction: 0xf8bef7fb
d0019ae0:	1ff2e7de 	svcne	0x00f2e7de
d0019ae4:	d9032a02 	stmdble	r3, {r1, r9, fp, sp}
d0019ae8:	0210f1a6 	andseq	pc, r0, #-2147483607	; 0x80000029
d0019aec:	d8072a01 	stmdale	r7, {r0, r9, fp, sp}
d0019af0:	447a4aad 	ldrbtmi	r4, [sl], #-2733	; 0xfffff553
d0019af4:	29006d91 	stmdbcs	r0, {r0, r4, r7, r8, sl, fp, sp, lr}
d0019af8:	49acd185 	stmibmi	ip!, {r0, r2, r7, r8, ip, lr, pc}
d0019afc:	e77d4479 			; <UNDEFINED> instruction: 0xe77d4479
d0019b00:	29091eb1 	stmdbcs	r9, {r0, r4, r5, r7, r9, sl, fp, ip}
d0019b04:	f240d80d 	vadd.i8	d29, d0, d13
d0019b08:	40ca2215 	sbcmi	r2, sl, r5, lsl r2
d0019b0c:	d50807d1 	strle	r0, [r8, #-2001]	; 0xfffff82f
d0019b10:	447a4aa7 	ldrbtmi	r4, [sl], #-2727	; 0xfffff559
d0019b14:	29006d91 	stmdbcs	r0, {r0, r4, r7, r8, sl, fp, sp, lr}
d0019b18:	af75f47f 	svcge	0x0075f47f
d0019b1c:	447949a5 	ldrbtmi	r4, [r9], #-2469	; 0xfffff65b
d0019b20:	4ca5e76c 	stcmi	7, cr14, [r5], #432	; 0x1b0
d0019b24:	447c9301 	ldrbtmi	r9, [ip], #-769	; 0xfffffcff
d0019b28:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d0019b2c:	4620f96d 	strtmi	pc, [r0], -sp, ror #18
d0019b30:	b02cf8d4 	ldrdlt	pc, [ip], -r4	; <UNPREDICTABLE>
d0019b34:	f968f7f9 			; <UNDEFINED> instruction: 0xf968f7f9
d0019b38:	9b012e0c 	blls	0xd0065370
d0019b3c:	f1bbd11a 			; <UNDEFINED> instruction: 0xf1bbd11a
d0019b40:	d0060f3d 	andle	r0, r6, sp, lsr pc
d0019b44:	2a006da2 	bcs	0xd00351d4
d0019b48:	af5df47f 	svcge	0x005df47f
d0019b4c:	447a4a9b 	ldrbtmi	r4, [sl], #-2715	; 0xfffff565
d0019b50:	2030e761 	eorscs	lr, r0, r1, ror #14
d0019b54:	4005fb00 	andmi	pc, r5, r0, lsl #22
d0019b58:	10a4f500 	adcne	pc, r4, r0, lsl #10
d0019b5c:	6057f200 	subsvs	pc, r7, r0, lsl #4
d0019b60:	fa78f7fb 	blx	0xd1e57b54
d0019b64:	46292200 	strtmi	r2, [r9], -r0, lsl #4
d0019b68:	b0054620 	andlt	r4, r5, r0, lsr #12
d0019b6c:	4ff0e8bd 	svcmi	0x00f0e8bd
d0019b70:	b925f7fb 	stmdblt	r5!, {r0, r1, r3, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}
d0019b74:	d10d2e13 	tstle	sp, r3, lsl lr
d0019b78:	0f3df1bb 	svceq	0x003df1bb
d0019b7c:	6da2d006 	stcvs	0, cr13, [r2, #24]!
d0019b80:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0019b84:	4a8eaf40 	bmi	0xce3c588c
d0019b88:	e744447a 	smlsldx	r4, r4, sl, r4	; <UNPREDICTABLE>
d0019b8c:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0019b90:	e7e7f975 			; <UNDEFINED> instruction: 0xe7e7f975
d0019b94:	d1142e12 	tstle	r4, r2, lsl lr
d0019b98:	0f3df1bb 	svceq	0x003df1bb
d0019b9c:	6da2d006 	stcvs	0, cr13, [r2, #24]!
d0019ba0:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0019ba4:	4a87af30 	bmi	0xce20586c
d0019ba8:	e734447a 			; <UNDEFINED> instruction: 0xe734447a
d0019bac:	46202330 			; <UNDEFINED> instruction: 0x46202330
d0019bb0:	4305fb03 	movwmi	pc, #23299	; 0x5b03	; <UNPREDICTABLE>
d0019bb4:	13a4f503 			; <UNDEFINED> instruction: 0x13a4f503
d0019bb8:	1656f893 			; <UNDEFINED> instruction: 0x1656f893
d0019bbc:	f9bef7fc 			; <UNDEFINED> instruction: 0xf9bef7fc
d0019bc0:	2e0ee7d0 	mcrcs	7, 0, lr, cr14, cr0, {6}
d0019bc4:	f1bbd114 			; <UNDEFINED> instruction: 0xf1bbd114
d0019bc8:	d0060f3d 	andle	r0, r6, sp, lsr pc
d0019bcc:	2a006da2 	bcs	0xd003525c
d0019bd0:	af19f47f 	svcge	0x0019f47f
d0019bd4:	447a4a7c 	ldrbtmi	r4, [sl], #-2684	; 0xfffff584
d0019bd8:	2330e71d 	teqcs	r0, #7602176	; 0x740000
d0019bdc:	fb034620 	blx	0xd00eb466
d0019be0:	f5034305 			; <UNDEFINED> instruction: 0xf5034305
d0019be4:	f89313a4 			; <UNDEFINED> instruction: 0xf89313a4
d0019be8:	f7fe1656 			; <UNDEFINED> instruction: 0xf7fe1656
d0019bec:	e7b9f9c1 	ldr	pc, [r9, r1, asr #19]!
d0019bf0:	0f3df1bb 	svceq	0x003df1bb
d0019bf4:	80aef000 	adchi	pc, lr, r0
d0019bf8:	d10b2e0a 	tstle	fp, sl, lsl #28
d0019bfc:	7292f46f 	addsvc	pc, r2, #1862270976	; 0x6f000000
d0019c00:	2a01445a 	bcs	0xd006ad70
d0019c04:	6da2d906 			; <UNDEFINED> instruction: 0x6da2d906
d0019c08:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0019c0c:	4a6faefc 	bmi	0xd1c05804
d0019c10:	e700447a 	smlsdx	r0, sl, r4, r4
d0019c14:	db2c2d00 	blle	0xd0b2501c
d0019c18:	2200486d 	andcs	r4, r0, #7143424	; 0x6d0000
d0019c1c:	44784629 	ldrbtmi	r4, [r8], #-1577	; 0xfffff9d7
d0019c20:	f8b4f7fb 			; <UNDEFINED> instruction: 0xf8b4f7fb
d0019c24:	f24b486b 	vadd.i8	q10, <illegal reg q5.5>, <illegal reg q13.5>
d0019c28:	44784103 	ldrbtmi	r4, [r8], #-259	; 0xfffffefd
d0019c2c:	f816f7fb 			; <UNDEFINED> instruction: 0xf816f7fb
d0019c30:	21014f69 	tstcs	r1, r9, ror #30
d0019c34:	447f9a00 	ldrbtmi	r9, [pc], #-2560	; 0xd0019c3c
d0019c38:	f7fc4638 			; <UNDEFINED> instruction: 0xf7fc4638
d0019c3c:	f1bbfb77 			; <UNDEFINED> instruction: 0xf1bbfb77
d0019c40:	d0290f3d 	eorle	r0, r9, sp, lsr pc
d0019c44:	4106f64b 	tstmi	r6, fp, asr #12	; <UNPREDICTABLE>
d0019c48:	f7fb4638 			; <UNDEFINED> instruction: 0xf7fb4638
d0019c4c:	f46ff807 	vld2.8	{d31-d32}, [pc], r7
d0019c50:	2e0a7392 	mcrcs	3, 0, r7, cr10, cr2, {4}
d0019c54:	0403eb0b 	streq	lr, [r3], #-2827	; 0xfffff4f5
d0019c58:	2180d12d 	orrcs	sp, r0, sp, lsr #2
d0019c5c:	fffef7fa 			; <UNDEFINED> instruction: 0xfffef7fa
d0019c60:	d8212c08 	stmdale	r1!, {r3, sl, fp, sp}
d0019c64:	f004e8df 			; <UNDEFINED> instruction: 0xf004e8df
d0019c68:	20204012 	eorcs	r4, r0, r2, lsl r0
d0019c6c:	544f4a45 	strbpl	r4, [pc], #-2629	; 0xd0019c74
d0019c70:	485a0054 	ldmdami	sl, {r2, r4, r6}^
d0019c74:	21014652 	tstcs	r1, r2, asr r6
d0019c78:	90014478 	andls	r4, r1, r8, ror r4
d0019c7c:	f964f7fb 			; <UNDEFINED> instruction: 0xf964f7fb
d0019c80:	0108f646 	tsteq	r8, r6, asr #12	; <UNPREDICTABLE>
d0019c84:	f7fa9801 			; <UNDEFINED> instruction: 0xf7fa9801
d0019c88:	e7cbffe9 	strb	pc, [fp, r9, ror #31]	; <UNPREDICTABLE>
d0019c8c:	f6414854 			; <UNDEFINED> instruction: 0xf6414854
d0019c90:	44780108 	ldrbtmi	r0, [r8], #-264	; 0xfffffef8
d0019c94:	ffe2f7fa 			; <UNDEFINED> instruction: 0xffe2f7fa
d0019c98:	d1052e05 	tstle	r5, r5, lsl #28
d0019c9c:	f24b4851 	vtst.8	q10, <illegal reg q5.5>, <illegal reg q0.5>
d0019ca0:	447821c0 	ldrbtmi	r2, [r8], #-448	; 0xfffffe40
d0019ca4:	ffdaf7fa 			; <UNDEFINED> instruction: 0xffdaf7fa
d0019ca8:	db442d00 	blle	0xd11250b0
d0019cac:	2200484e 	andcs	r4, r0, #5111808	; 0x4e0000
d0019cb0:	44784629 	ldrbtmi	r4, [r8], #-1577	; 0xfffff9d7
d0019cb4:	2c08e759 	stccs	7, cr14, [r8], {89}	; 0x59
d0019cb8:	a302d8ee 	movwge	sp, #10478	; 0x28ee
d0019cbc:	2024f853 	eorcs	pc, r4, r3, asr r8	; <UNPREDICTABLE>
d0019cc0:	47184413 			; <UNDEFINED> instruction: 0x47184413
d0019cc4:	ffffffc9 			; <UNDEFINED> instruction: 0xffffffc9
d0019cc8:	00000025 	andeq	r0, r0, r5, lsr #32
d0019ccc:	ffffffd5 			; <UNDEFINED> instruction: 0xffffffd5
d0019cd0:	ffffffd5 			; <UNDEFINED> instruction: 0xffffffd5
d0019cd4:	0000002f 	andeq	r0, r0, pc, lsr #32
d0019cd8:	00000039 	andeq	r0, r0, r9, lsr r0
d0019cdc:	00000043 	andeq	r0, r0, r3, asr #32
d0019ce0:	0000004d 	andeq	r0, r0, sp, asr #32
d0019ce4:	0000004d 	andeq	r0, r0, sp, asr #32
d0019ce8:	f6414840 			; <UNDEFINED> instruction: 0xf6414840
d0019cec:	44782108 	ldrbtmi	r2, [r8], #-264	; 0xfffffef8
d0019cf0:	483fe7d0 	ldmdami	pc!, {r4, r6, r7, r8, r9, sl, sp, lr, pc}	; <UNPREDICTABLE>
d0019cf4:	0108f244 	tsteq	r8, r4, asr #4	; <UNPREDICTABLE>
d0019cf8:	e7cb4478 			; <UNDEFINED> instruction: 0xe7cb4478
d0019cfc:	f244483d 	vtst.8	d20, d4, d29
d0019d00:	44783108 	ldrbtmi	r3, [r8], #-264	; 0xfffffef8
d0019d04:	483ce7c6 	ldmdami	ip!, {r1, r2, r6, r7, r8, r9, sl, sp, lr, pc}
d0019d08:	0148f244 	cmpeq	r8, r4, asr #4	; <UNPREDICTABLE>
d0019d0c:	e7c14478 			; <UNDEFINED> instruction: 0xe7c14478
d0019d10:	f244483a 	vtst.8	d20, d4, d26
d0019d14:	44786102 	ldrbtmi	r6, [r8], #-258	; 0xfffffefe
d0019d18:	ffa0f7fa 			; <UNDEFINED> instruction: 0xffa0f7fa
d0019d1c:	6108f244 	tstvs	r8, r4, asr #4	; <UNPREDICTABLE>
d0019d20:	ff9cf7fa 			; <UNDEFINED> instruction: 0xff9cf7fa
d0019d24:	0190f244 	orrseq	pc, r0, r4, asr #4
d0019d28:	1310f244 	tstne	r0, #68, 4	; 0x40000004	; <UNPREDICTABLE>
d0019d2c:	7f96f5bb 	svcvc	0x0096f5bb
d0019d30:	4619bf18 	sadd16mi	fp, r9, r8
d0019d34:	4832e7ae 	ldmdami	r2!, {r1, r2, r3, r5, r7, r8, r9, sl, sp, lr, pc}
d0019d38:	21014652 	tstcs	r1, r2, asr r6
d0019d3c:	90004478 	andls	r4, r0, r8, ror r4
d0019d40:	f902f7fb 			; <UNDEFINED> instruction: 0xf902f7fb
d0019d44:	0108f246 	tsteq	r8, r6, asr #4	; <UNPREDICTABLE>
d0019d48:	b0059800 	andlt	r9, r5, r0, lsl #16
d0019d4c:	4ff0e8bd 	svcmi	0x00f0e8bd
d0019d50:	bf84f7fa 	svclt	0x0084f7fa
d0019d54:	9b002e0a 	blls	0xd0025584
d0019d58:	2304bf08 	movwcs	fp, #20232	; 0x4f08
d0019d5c:	e7679300 	strb	r9, [r7, -r0, lsl #6]!
d0019d60:	fb022230 	blx	0xd00a262a
d0019d64:	f5044405 			; <UNDEFINED> instruction: 0xf5044405
d0019d68:	f89414a4 			; <UNDEFINED> instruction: 0xf89414a4
d0019d6c:	2a002660 	bcs	0xd00236f4
d0019d70:	ae3ef47f 	mrcge	4, 1, APSR_nzcv, cr14, cr15, {3}
d0019d74:	6655f894 			; <UNDEFINED> instruction: 0x6655f894
d0019d78:	3afff04f 	bcc	0xd0015ebc
d0019d7c:	bf00e652 	svclt	0x0000e652
d0019d80:	0000caac 	andeq	ip, r0, ip, lsr #21
d0019d84:	0000ca7c 	andeq	ip, r0, ip, ror sl
d0019d88:	0000ca6a 	andeq	ip, r0, sl, ror #20
d0019d8c:	0000ca12 	andeq	ip, r0, r2, lsl sl
d0019d90:	fffffddb 			; <UNDEFINED> instruction: 0xfffffddb
d0019d94:	fffffd9c 			; <UNDEFINED> instruction: 0xfffffd9c
d0019d98:	0000c9d4 	ldrdeq	ip, [r0], -r4
d0019d9c:	fffffda9 			; <UNDEFINED> instruction: 0xfffffda9
d0019da0:	0000c9a0 	andeq	ip, r0, r0, lsr #19
d0019da4:	0000c95e 	andeq	ip, r0, lr, asr r9
d0019da8:	0000c912 	andeq	ip, r0, r2, lsl r9
d0019dac:	fffffd1b 			; <UNDEFINED> instruction: 0xfffffd1b
d0019db0:	0000c8f2 	strdeq	ip, [r0], -r2
d0019db4:	fffffd1f 			; <UNDEFINED> instruction: 0xfffffd1f
d0019db8:	0000c8de 	ldrdeq	ip, [r0], -lr
d0019dbc:	fffffd1b 			; <UNDEFINED> instruction: 0xfffffd1b
d0019dc0:	fffffd12 			; <UNDEFINED> instruction: 0xfffffd12
d0019dc4:	fffffd19 			; <UNDEFINED> instruction: 0xfffffd19
d0019dc8:	fffffd15 			; <UNDEFINED> instruction: 0xfffffd15
d0019dcc:	fffffd0a 			; <UNDEFINED> instruction: 0xfffffd0a
d0019dd0:	0000c7e6 	andeq	ip, r0, r6, ror #15
d0019dd4:	0000c7da 	ldrdeq	ip, [r0], -sl
d0019dd8:	0000c7ce 	andeq	ip, r0, lr, asr #15
d0019ddc:	0000c78c 	andeq	ip, r0, ip, lsl #15
d0019de0:	0000c772 	andeq	ip, r0, r2, ror r7
d0019de4:	0000c762 	andeq	ip, r0, r2, ror #14
d0019de8:	0000c752 	andeq	ip, r0, r2, asr r7
d0019dec:	0000c716 	andeq	ip, r0, r6, lsl r7
d0019df0:	0000c70c 	andeq	ip, r0, ip, lsl #14
d0019df4:	0000c702 	andeq	ip, r0, r2, lsl #14
d0019df8:	0000c6f8 	strdeq	ip, [r0], -r8
d0019dfc:	0000c6ee 	andeq	ip, r0, lr, ror #13
d0019e00:	0000c6c8 	andeq	ip, r0, r8, asr #13

Disassembly of section .text.initialize_scalar.constprop.0:

d0019e64 <.text.initialize_scalar.constprop.0>:
d0019e64:	4ff0e92d 	svcmi	0x00f0e92d
d0019e68:	4607b087 	strmi	fp, [r7], -r7, lsl #1
d0019e6c:	9203460e 	andls	r4, r3, #14680064	; 0xe00000
d0019e70:	4c31b971 			; <UNDEFINED> instruction: 0x4c31b971
d0019e74:	447c2201 	ldrbtmi	r2, [ip], #-513	; 0xfffffdff
d0019e78:	46204611 			; <UNDEFINED> instruction: 0x46204611
d0019e7c:	fa56f7fc 	blx	0xd15d7e74
d0019e80:	46394632 			; <UNDEFINED> instruction: 0x46394632
d0019e84:	b0074620 	andlt	r4, r7, r0, lsr #12
d0019e88:	4ff0e8bd 	svcmi	0x00f0e8bd
d0019e8c:	bf97f7fa 	svclt	0x0097f7fa
d0019e90:	212d4c2a 			; <UNDEFINED> instruction: 0x212d4c2a
d0019e94:	4620447c 			; <UNDEFINED> instruction: 0x4620447c
d0019e98:	ffd1f7f8 			; <UNDEFINED> instruction: 0xffd1f7f8
d0019e9c:	69e269a3 	stmibvs	r2!, {r0, r1, r5, r7, r8, fp, sp, lr}^
d0019ea0:	718df44f 	orrvc	pc, sp, pc, asr #8
d0019ea4:	6b639305 	blvs	0xd18feac0
d0019ea8:	46209002 	strtmi	r9, [r0], -r2
d0019eac:	93019204 	movwls	r9, #4612	; 0x1204
d0019eb0:	9030f894 	mlasls	r0, r4, r8, pc	; <UNPREDICTABLE>
d0019eb4:	5b08e9d4 	blpl	0xd025460c
d0019eb8:	a80ae9d4 	stmdage	sl, {r2, r4, r6, r7, r8, fp, sp, lr, pc}
d0019ebc:	ffbff7f8 			; <UNDEFINED> instruction: 0xffbff7f8
d0019ec0:	9b059a04 	blls	0xd01806d8
d0019ec4:	4620b188 	strtmi	fp, [r0], -r8, lsl #3
d0019ec8:	fd5af7f9 	ldc2l	7, cr15, [sl, #-996]	; 0xfffffc1c
d0019ecc:	9b024605 	blls	0xd00ab6e8
d0019ed0:	426db103 	rsbmi	fp, sp, #-1073741824	; 0xc0000000
d0019ed4:	b3639b03 	cmnlt	r3, #3072	; 0xc00
d0019ed8:	d92a2dff 	stmdble	sl!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, sl, fp, sp}
d0019edc:	447b4b18 	ldrbtmi	r4, [fp], #-2840	; 0xfffff4e8
d0019ee0:	b9ba6d9a 	ldmiblt	sl!, {r1, r3, r4, r7, r8, sl, fp, sp, lr}
d0019ee4:	447a4a17 	ldrbtmi	r4, [sl], #-2583	; 0xfffff5e9
d0019ee8:	f240e00e 	vhadd.s8	d30, d0, d14
d0019eec:	45881101 	strmi	r1, [r8, #257]	; 0x101
d0019ef0:	4619d113 			; <UNDEFINED> instruction: 0x4619d113
d0019ef4:	f7f64620 			; <UNDEFINED> instruction: 0xf7f64620
d0019ef8:	b9c0fcf0 	stmiblt	r0, {r4, r5, r6, r7, sl, fp, ip, sp, lr, pc}^
d0019efc:	447b4b12 	ldrbtmi	r4, [fp], #-2834	; 0xfffff4ee
d0019f00:	b93a6d9a 	ldmdblt	sl!, {r1, r3, r4, r7, r8, sl, fp, sp, lr}
d0019f04:	447a4a11 	ldrbtmi	r4, [sl], #-2577	; 0xfffff5ef
d0019f08:	2b16e9c3 	blcs	0xd05d461c
d0019f0c:	e9c39a01 	stmib	r3, {r0, r9, fp, ip, pc}^
d0019f10:	669aa918 			; <UNDEFINED> instruction: 0x669aa918
d0019f14:	e8bdb007 	pop	{r0, r1, r2, ip, sp, pc}
d0019f18:	f5a88ff0 			; <UNDEFINED> instruction: 0xf5a88ff0
d0019f1c:	f1b87881 			; <UNDEFINED> instruction: 0xf1b87881
d0019f20:	d8eb0f01 	stmiale	fp!, {r0, r8, r9, sl, fp}^
d0019f24:	4478480a 	ldrbtmi	r4, [r8], #-2058	; 0xfffff7f6
d0019f28:	ff6ef7f8 			; <UNDEFINED> instruction: 0xff6ef7f8
d0019f2c:	6a05e7cf 	bvs	0xd0193e70
d0019f30:	f846e7f8 			; <UNDEFINED> instruction: 0xf846e7f8
d0019f34:	e7ed5027 	strb	r5, [sp, r7, lsr #32]!
d0019f38:	0000c58e 	andeq	ip, r0, lr, lsl #11
d0019f3c:	0000c570 	andeq	ip, r0, r0, ror r5
d0019f40:	0000c526 	andeq	ip, r0, r6, lsr #10
d0019f44:	ffffff51 			; <UNDEFINED> instruction: 0xffffff51
d0019f48:	0000c506 	andeq	ip, r0, r6, lsl #10
d0019f4c:	fffffefa 			; <UNDEFINED> instruction: 0xfffffefa
d0019f50:	0000c4de 	ldrdeq	ip, [r0], -lr

Disassembly of section .text.initialize_record.constprop.0:

d001a054 <.text.initialize_record.constprop.0>:
d001a054:	e92d2b21 	push	{r0, r5, r8, r9, fp, sp}
d001a058:	46804ff7 			; <UNDEFINED> instruction: 0x46804ff7
d001a05c:	4615468b 	ldrmi	r4, [r5], -fp, lsl #13
d001a060:	d108469a 			; <UNDEFINED> instruction: 0xd108469a
d001a064:	485c495b 	ldmdami	ip, {r0, r1, r3, r4, r6, r8, fp, lr}^
d001a068:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d001a06c:	e8bdb003 	pop	{r0, r1, ip, sp, pc}
d001a070:	f7f64ff0 			; <UNDEFINED> instruction: 0xf7f64ff0
d001a074:	4e59b899 	mrcmi	8, 2, fp, cr9, cr9, {4}
d001a078:	4a59217b 	bmi	0xd166266c
d001a07c:	447a447e 	ldrbtmi	r4, [sl], #-1150	; 0xfffffb82
d001a080:	f7f84630 			; <UNDEFINED> instruction: 0xf7f84630
d001a084:	2800feea 	stmdacs	r0, {r1, r3, r5, r6, r7, r9, sl, fp, ip, sp, lr, pc}
d001a088:	80a1f000 	adchi	pc, r1, r0
d001a08c:	731af44f 	tstvc	sl, #1325400064	; 0x4f000000	; <UNPREDICTABLE>
d001a090:	0900f04f 	stmdbeq	r0, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d001a094:	f808fb03 			; <UNDEFINED> instruction: 0xf808fb03
d001a098:	3467f508 	strbtcc	pc, [r7], #-1288	; 0xfffffaf8	; <UNPREDICTABLE>
d001a09c:	74f4f504 	ldrbtvc	pc, [r4], #1284	; 0x504	; <UNPREDICTABLE>
d001a0a0:	6db34434 	cfldrsvs	mvf4, [r3, #208]!	; 0xd0
d001a0a4:	d13d2b00 	teqle	sp, r0, lsl #22
d001a0a8:	2b7d6af3 	blcs	0xd1f74c7c
d001a0ac:	f5b3d03a 			; <UNDEFINED> instruction: 0xf5b3d03a
d001a0b0:	d0377f80 	eorsle	r7, r7, r0, lsl #31
d001a0b4:	0208eb06 	andeq	lr, r8, #6144	; 0x1800
d001a0b8:	3268f502 	rsbcc	pc, r8, #8388608	; 0x800000
d001a0bc:	102af892 	mlane	sl, r2, r8, pc	; <UNPREDICTABLE>
d001a0c0:	d9054549 	stmdble	r5, {r0, r3, r6, r8, sl, lr}
d001a0c4:	202bf892 	mlacs	fp, r2, r8, pc	; <UNPREDICTABLE>
d001a0c8:	f1b9b13a 			; <UNDEFINED> instruction: 0xf1b9b13a
d001a0cc:	d0040f00 	andle	r0, r4, r0, lsl #30
d001a0d0:	48454944 	stmdami	r5, {r2, r6, r8, fp, lr}^
d001a0d4:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d001a0d8:	8c67e7c8 	stclhi	7, cr14, [r7], #-800	; 0xfffffce0
d001a0dc:	2021f894 	mlacs	r1, r4, r8, pc	; <UNPREDICTABLE>
d001a0e0:	0020f894 	mlaeq	r0, r4, r8, pc	; <UNPREDICTABLE>
d001a0e4:	2a00445f 	bcs	0xd002b268
d001a0e8:	2d00d051 	stccs	0, cr13, [r0, #-324]	; 0xfffffebc
d001a0ec:	4b3fd03a 	blmi	0xd100e1dc
d001a0f0:	447b4a3f 	ldrbtmi	r4, [fp], #-2623	; 0xfffff5c1
d001a0f4:	9301447a 	movwls	r4, #5242	; 0x147a
d001a0f8:	0106e9d3 	ldrdeq	lr, [r6, -r3]
d001a0fc:	fbbaf7f6 	blx	0xceed80de
d001a100:	b1c89b01 	biclt	r9, r8, r1, lsl #22
d001a104:	f7f84618 			; <UNDEFINED> instruction: 0xf7f84618
d001a108:	2300fe7f 	movwcs	pc, #3711	; 0xe7f	; <UNPREDICTABLE>
d001a10c:	3027f845 	eorcc	pc, r7, r5, asr #16
d001a110:	212c4838 			; <UNDEFINED> instruction: 0x212c4838
d001a114:	0901f109 	stmdbeq	r1, {r0, r3, r8, ip, sp, lr, pc}
d001a118:	44783424 	ldrbtmi	r3, [r8], #-1060	; 0xfffffbdc
d001a11c:	fe8ff7f8 	mcr2	7, 4, pc, cr15, cr8, {7}	; <UNPREDICTABLE>
d001a120:	d1be2800 			; <UNDEFINED> instruction: 0xd1be2800
d001a124:	217d4a34 	cmncs	sp, r4, lsr sl
d001a128:	447a4834 	ldrbtmi	r4, [sl], #-2100	; 0xfffff7cc
d001a12c:	b0034478 	andlt	r4, r3, r8, ror r4
d001a130:	4ff0e8bd 	svcmi	0x00f0e8bd
d001a134:	be91f7f8 	mrclt	7, 4, APSR_nzcv, cr1, cr8, {7}
d001a138:	f5a26ada 			; <UNDEFINED> instruction: 0xf5a26ada
d001a13c:	2a017281 	bcs	0xd0076b48
d001a140:	6a1ad809 	bvs	0xd06d016c
d001a144:	4618b93a 			; <UNDEFINED> instruction: 0x4618b93a
d001a148:	f7f89201 			; <UNDEFINED> instruction: 0xf7f89201
d001a14c:	9a01fe5d 	bls	0xd0099ac8
d001a150:	2027f845 	eorcs	pc, r7, r5, asr #16
d001a154:	492ae7dc 	stmdbmi	sl!, {r2, r3, r4, r6, r7, r8, r9, sl, sp, lr, pc}
d001a158:	4479482a 	ldrbtmi	r4, [r9], #-2090	; 0xfffff7d6
d001a15c:	f7f64478 			; <UNDEFINED> instruction: 0xf7f64478
d001a160:	e7d5f823 	ldrb	pc, [r5, r3, lsr #16]	; <UNPREDICTABLE>
d001a164:	d10c28ff 	strdle	r2, [ip, -pc]
d001a168:	22044827 	andcs	r4, r4, #2555904	; 0x270000
d001a16c:	44782101 	ldrbtmi	r2, [r8], #-257	; 0xfffffeff
d001a170:	f8dcf7fc 			; <UNDEFINED> instruction: 0xf8dcf7fc
d001a174:	22004825 	andcs	r4, r0, #2424832	; 0x250000
d001a178:	44784639 	ldrbtmi	r4, [r8], #-1593	; 0xfffff9c7
d001a17c:	fe1ff7fa 	mrc2	7, 0, pc, cr15, cr10, {7}
d001a180:	4601e7c6 	strmi	lr, [r1], -r6, asr #15
d001a184:	44784822 	ldrbtmi	r4, [r8], #-2082	; 0xfffff7de
d001a188:	fef2f7fd 	mrc2	7, 7, pc, cr2, cr13, {7}
d001a18c:	28ffe7f2 	ldmcs	pc!, {r1, r4, r5, r6, r7, r8, r9, sl, sp, lr, pc}^	; <UNPREDICTABLE>
d001a190:	4629d104 	strtmi	sp, [r9], -r4, lsl #2
d001a194:	f7ff4638 			; <UNDEFINED> instruction: 0xf7ff4638
d001a198:	e7b9fe65 	ldr	pc, [r9, r5, ror #28]!
d001a19c:	d1062b7b 	tstle	r6, fp, ror fp
d001a1a0:	0301f10a 	movweq	pc, #4362	; 0x110a	; <UNPREDICTABLE>
d001a1a4:	4639462a 	ldrtmi	r4, [r9], -sl, lsr #12
d001a1a8:	ff54f7ff 			; <UNDEFINED> instruction: 0xff54f7ff
d001a1ac:	f5a3e7b0 			; <UNDEFINED> instruction: 0xf5a3e7b0
d001a1b0:	2b017381 	blcs	0xd0076fbc
d001a1b4:	4817d806 	ldmdami	r7, {r1, r2, fp, ip, lr, pc}
d001a1b8:	6a034478 	bvs	0xd00eb3a0
d001a1bc:	f7f8b913 			; <UNDEFINED> instruction: 0xf7f8b913
d001a1c0:	e7a5fe23 	str	pc, [r5, r3, lsr #28]!
d001a1c4:	48154914 	ldmdami	r5, {r2, r4, r8, fp, lr}
d001a1c8:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d001a1cc:	b003e74e 	andlt	lr, r3, lr, asr #14
d001a1d0:	8ff0e8bd 	svchi	0x00f0e8bd
d001a1d4:	fffffee8 			; <UNDEFINED> instruction: 0xfffffee8
d001a1d8:	0000c39a 	muleq	r0, sl, r3
d001a1dc:	0000c388 	andeq	ip, r0, r8, lsl #7
d001a1e0:	fffffef2 			; <UNDEFINED> instruction: 0xfffffef2
d001a1e4:	fffffec0 			; <UNDEFINED> instruction: 0xfffffec0
d001a1e8:	0000c32e 	andeq	ip, r0, lr, lsr #6
d001a1ec:	0000c312 	andeq	ip, r0, r2, lsl r3
d001a1f0:	ffffac2a 			; <UNDEFINED> instruction: 0xffffac2a
d001a1f4:	0000c2ea 	andeq	ip, r0, sl, ror #5
d001a1f8:	fffffefe 			; <UNDEFINED> instruction: 0xfffffefe
d001a1fc:	0000c2d8 	ldrdeq	ip, [r0], -r8
d001a200:	fffffe64 			; <UNDEFINED> instruction: 0xfffffe64
d001a204:	0000c2a8 	andeq	ip, r0, r8, lsr #5
d001a208:	0000c296 	muleq	r0, r6, r2
d001a20c:	0000c28a 	andeq	ip, r0, sl, lsl #5
d001a210:	0000c27e 	andeq	ip, r0, lr, ror r2
d001a214:	0000c24c 	andeq	ip, r0, ip, asr #4
d001a218:	fffffe2f 			; <UNDEFINED> instruction: 0xfffffe2f
d001a21c:	0000c23a 	andeq	ip, r0, sl, lsr r2

Disassembly of section .text.initialize_array.constprop.0:

d001a2b8 <.text.initialize_array.constprop.0>:
d001a2b8:	4ff7e92d 	svcmi	0x00f7e92d
d001a2bc:	46154e36 			; <UNDEFINED> instruction: 0x46154e36
d001a2c0:	460c4a36 			; <UNDEFINED> instruction: 0x460c4a36
d001a2c4:	9001447e 	andls	r4, r1, lr, ror r4
d001a2c8:	217b447a 	cmncs	fp, sl, ror r4
d001a2cc:	461f4630 			; <UNDEFINED> instruction: 0x461f4630
d001a2d0:	a030f8dd 	ldrsbtge	pc, [r0], -sp	; <UNPREDICTABLE>
d001a2d4:	fdc1f7f8 	stc2l	7, cr15, [r1, #992]	; 0x3e0
d001a2d8:	d05a2800 	subsle	r2, sl, r0, lsl #16
d001a2dc:	f8df2cff 			; <UNDEFINED> instruction: 0xf8df2cff
d001a2e0:	f04fb0c0 			; <UNDEFINED> instruction: 0xf04fb0c0
d001a2e4:	bf140800 	svclt	0x00140800
d001a2e8:	701af44f 	andsvc	pc, sl, pc, asr #8
d001a2ec:	0901f04f 	stmdbeq	r1, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d001a2f0:	bf1844fb 	svclt	0x001844fb
d001a2f4:	6004fb00 	andvs	pc, r4, r0, lsl #22
d001a2f8:	bf184e2a 	svclt	0x00184e2a
d001a2fc:	3068f500 	rsbcc	pc, r8, r0, lsl #10
d001a300:	bf18447e 	svclt	0x0018447e
d001a304:	9028f8b0 	strhtls	pc, [r8], -r0	; <UNPREDICTABLE>
d001a308:	bb036db3 	bllt	0xd00f59dc
d001a30c:	2b7d6af3 	blcs	0xd1f74ee0
d001a310:	f5b3d01d 			; <UNDEFINED> instruction: 0xf5b3d01d
d001a314:	d01a7f80 	andsle	r7, sl, r0, lsl #31
d001a318:	45429a01 	strbmi	r9, [r2, #-2561]	; 0xfffff5ff
d001a31c:	4922d107 	stmdbmi	r2!, {r0, r1, r2, r8, ip, lr, pc}
d001a320:	44794630 	ldrbtmi	r4, [r9], #-1584	; 0xfffff9d0
d001a324:	e8bdb003 	pop	{r0, r1, ip, sp, pc}
d001a328:	f7f54ff0 			; <UNDEFINED> instruction: 0xf7f54ff0
d001a32c:	2cffbf3d 	ldclcs	15, cr11, [pc], #244	; 0xd001a428
d001a330:	4652d117 			; <UNDEFINED> instruction: 0x4652d117
d001a334:	46284639 			; <UNDEFINED> instruction: 0x46284639
d001a338:	fd94f7ff 	ldc2	7, cr15, [r4, #1020]	; 0x3fc
d001a33c:	4658212c 	ldrbmi	r2, [r8], -ip, lsr #2
d001a340:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d001a344:	f7f8444d 			; <UNDEFINED> instruction: 0xf7f8444d
d001a348:	2800fd7a 	stmdacs	r0, {r1, r3, r4, r5, r6, r8, sl, fp, ip, sp, lr, pc}
d001a34c:	4a17d1dc 	bmi	0xd060eac4
d001a350:	4817217d 	ldmdami	r7, {r0, r2, r3, r4, r5, r6, r8, sp}
d001a354:	4478447a 	ldrbtmi	r4, [r8], #-1146	; 0xfffffb86
d001a358:	e8bdb003 	pop	{r0, r1, ip, sp, pc}
d001a35c:	f7f84ff0 			; <UNDEFINED> instruction: 0xf7f84ff0
d001a360:	2b7bbd7c 	blcs	0xd1f09958
d001a364:	2301d106 	movwcs	sp, #4358	; 0x1106
d001a368:	4629463a 			; <UNDEFINED> instruction: 0x4629463a
d001a36c:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d001a370:	e7e3fe71 			; <UNDEFINED> instruction: 0xe7e3fe71
d001a374:	7381f5a3 	orrvc	pc, r1, #683671552	; 0x28c00000
d001a378:	d8052b01 	stmdale	r5, {r0, r8, r9, fp, sp}
d001a37c:	b91b6a33 	ldmdblt	fp, {r0, r1, r4, r5, r9, fp, sp, lr}
d001a380:	f7f84630 			; <UNDEFINED> instruction: 0xf7f84630
d001a384:	e7d9fd41 	ldrb	pc, [r9, r1, asr #26]	; <UNPREDICTABLE>
d001a388:	480b490a 	stmdami	fp, {r1, r3, r8, fp, lr}
d001a38c:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d001a390:	b003e7c8 	andlt	lr, r3, r8, asr #15
d001a394:	8ff0e8bd 	svchi	0x00f0e8bd
d001a398:	0000c140 	andeq	ip, r0, r0, asr #2
d001a39c:	ffffff54 			; <UNDEFINED> instruction: 0xffffff54
d001a3a0:	0000c114 	andeq	ip, r0, r4, lsl r1
d001a3a4:	0000c104 	andeq	ip, r0, r4, lsl #2
d001a3a8:	ffffff1d 			; <UNDEFINED> instruction: 0xffffff1d
d001a3ac:	ffffff39 			; <UNDEFINED> instruction: 0xffffff39
d001a3b0:	0000c0ae 	andeq	ip, r0, lr, lsr #1
d001a3b4:	fffffed7 			; <UNDEFINED> instruction: 0xfffffed7
d001a3b8:	0000c076 	andeq	ip, r0, r6, ror r0

Disassembly of section .text.local_declaration.constprop.0:

d001a624 <.text.local_declaration.constprop.0>:
d001a624:	4ff0e92d 	svcmi	0x00f0e92d
d001a628:	b0974cf2 			; <UNDEFINED> instruction: 0xb0974cf2
d001a62c:	7185f44f 	orrvc	pc, r5, pc, asr #8
d001a630:	4620447c 			; <UNDEFINED> instruction: 0x4620447c
d001a634:	fc03f7f8 	stc2	7, cr15, [r3], {248}	; 0xf8
d001a638:	f2406ae2 	vpmax.s8	q11, q8, q9
d001a63c:	4605131b 			; <UNDEFINED> instruction: 0x4605131b
d001a640:	d108429a 			; <UNDEFINED> instruction: 0xd108429a
d001a644:	f7f84620 			; <UNDEFINED> instruction: 0xf7f84620
d001a648:	bb88fefb 	bllt	0xce25a23c
d001a64c:	46282501 	strtmi	r2, [r8], -r1, lsl #10
d001a650:	e8bdb017 	pop	{r0, r1, r2, r4, ip, sp, pc}
d001a654:	f2408ff0 	vrecps.f32	q12, q8, q8
d001a658:	46201107 	strtmi	r1, [r0], -r7, lsl #2
d001a65c:	fbeff7f8 	blx	0xcfc18646
d001a660:	6ae3b148 	bvs	0xcf906b88
d001a664:	d1232b28 			; <UNDEFINED> instruction: 0xd1232b28
d001a668:	2b2a6ce3 	blcs	0xd0ab59fc
d001a66c:	2000d120 	andcs	sp, r0, r0, lsr #2
d001a670:	fe6af7fa 	mcr2	7, 3, pc, cr10, cr10, {7}	; <UNPREDICTABLE>
d001a674:	6ae2e7ea 	bvs	0xcf8d4624
d001a678:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d001a67c:	d11c429a 			; <UNDEFINED> instruction: 0xd11c429a
d001a680:	e9d44620 	ldmib	r4, {r5, r9, sl, lr}^
d001a684:	f7f61206 			; <UNDEFINED> instruction: 0xf7f61206
d001a688:	2800f884 	stmdacs	r0, {r2, r7, fp, ip, sp, lr, pc}
d001a68c:	4620db15 			; <UNDEFINED> instruction: 0x4620db15
d001a690:	1206e9d4 	andne	lr, r6, #212, 18	; 0x350000
d001a694:	f87df7f6 			; <UNDEFINED> instruction: 0xf87df7f6
d001a698:	fb032324 	blx	0xd00e3332
d001a69c:	f5004000 			; <UNDEFINED> instruction: 0xf5004000
d001a6a0:	f8903075 			; <UNDEFINED> instruction: 0xf8903075
d001a6a4:	2bff33ac 	blcs	0xcffe755c
d001a6a8:	4620d107 	strtmi	sp, [r0], -r7, lsl #2
d001a6ac:	fbacf7f8 	blx	0xceb58696
d001a6b0:	93092301 	movwls	r2, #37633	; 0x9301
d001a6b4:	93072300 	movwls	r2, #29440	; 0x7300
d001a6b8:	4ccfe201 	sfmmi	f6, 3, [pc], {1}
d001a6bc:	7184f44f 	orrvc	pc, r4, pc, asr #8
d001a6c0:	4620447c 			; <UNDEFINED> instruction: 0x4620447c
d001a6c4:	fbbbf7f8 	blx	0xcef186ae
d001a6c8:	b1704606 	cmnlt	r0, r6, lsl #12
d001a6cc:	2b286ae3 	blcs	0xd0a35260
d001a6d0:	6ce3d104 	stfvsp	f5, [r3], #16
d001a6d4:	d1012b2a 	tstle	r1, sl, lsr #22
d001a6d8:	e7c92001 	strb	r2, [r9, r1]
d001a6dc:	48c849c7 	stmiami	r8, {r0, r1, r2, r6, r7, r8, fp, lr}^
d001a6e0:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d001a6e4:	fd60f7f5 	stc2l	7, cr15, [r0, #-980]!	; 0xfffffc2c
d001a6e8:	4620e7b0 			; <UNDEFINED> instruction: 0x4620e7b0
d001a6ec:	f876f7f6 			; <UNDEFINED> instruction: 0xf876f7f6
d001a6f0:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d001a6f4:	a90d81be 	stmdbge	sp, {r1, r2, r3, r4, r5, r7, r8, pc}
d001a6f8:	960d4620 	strls	r4, [sp], -r0, lsr #12
d001a6fc:	fdaaf7f8 	stc2	7, cr15, [sl, #992]!	; 0x3e0
d001a700:	d0a32800 	adcle	r2, r3, r0, lsl #16
d001a704:	4ab84bbf 	bmi	0xcee2d608
d001a708:	9307447b 	movwls	r4, #29819	; 0x747b
d001a70c:	930b4413 	movwls	r4, #46099	; 0xb413
d001a710:	212a4cbd 			; <UNDEFINED> instruction: 0x212a4cbd
d001a714:	4620447c 			; <UNDEFINED> instruction: 0x4620447c
d001a718:	fb91f7f8 	blx	0xce498702
d001a71c:	28004607 	stmdacs	r0, {r0, r1, r2, r9, sl, lr}
d001a720:	212ad06a 			; <UNDEFINED> instruction: 0x212ad06a
d001a724:	f7f84620 			; <UNDEFINED> instruction: 0xf7f84620
d001a728:	1e03fb8a 	vmlane.f64	d15, d19, d10
d001a72c:	2301bf18 	movwcs	fp, #7960	; 0x1f18
d001a730:	4eb69309 	cdpmi	3, 11, cr9, cr6, cr9, {0}
d001a734:	447eac0e 	ldrbtmi	sl, [lr], #-3086	; 0xfffff3f2
d001a738:	0518f106 	ldreq	pc, [r8, #-262]	; 0xfffffefa
d001a73c:	a030f896 	mlasge	r0, r6, r8, pc	; <UNPREDICTABLE>
d001a740:	b034f8d6 	ldrsbtlt	pc, [r4], -r6	; <UNPREDICTABLE>
d001a744:	c40fcd0f 	strgt	ip, [pc], #-3343	; 0xd001a74c
d001a748:	000fe895 	muleq	pc, r5, r8	; <UNPREDICTABLE>
d001a74c:	000fe884 	andeq	lr, pc, r4, lsl #17
d001a750:	f2404aaf 	vpmax.s8	d20, d16, d31
d001a754:	46301101 	ldrtmi	r1, [r0], -r1, lsl #2
d001a758:	447a6a74 	ldrbtmi	r6, [sl], #-2676	; 0xfffff58c
d001a75c:	f7f86ab5 			; <UNDEFINED> instruction: 0xf7f86ab5
d001a760:	ab0efb7c 	blge	0xd03d9558
d001a764:	2800930a 	stmdacs	r0, {r1, r3, r8, r9, ip, pc}
d001a768:	af70f43f 	svcge	0x0070f43f
d001a76c:	d1452f00 	cmple	r5, r0, lsl #30
d001a770:	215b4630 	cmpcs	fp, r0, lsr r6
d001a774:	fb63f7f8 	blx	0xd191875e
d001a778:	bf181e06 	svclt	0x00181e06
d001a77c:	f8df2601 			; <UNDEFINED> instruction: 0xf8df2601
d001a780:	f44f9294 	vst1.32	{d25-d28}, [pc :64], r4
d001a784:	9b0d721a 	blls	0xd0376ff4
d001a788:	fb0244f9 	blx	0xd00abb76
d001a78c:	f5029203 			; <UNDEFINED> instruction: 0xf5029203
d001a790:	8d123268 	lfmhi	f3, 4, [r2, #-416]	; 0xfffffe60
d001a794:	2e009208 	cdpcs	2, 0, cr9, cr0, cr8, {0}
d001a798:	f8d9d05a 			; <UNDEFINED> instruction: 0xf8d9d05a
d001a79c:	f8d9202c 			; <UNDEFINED> instruction: 0xf8d9202c
d001a7a0:	f5a28020 			; <UNDEFINED> instruction: 0xf5a28020
d001a7a4:	2a017281 	bcs	0xd00771b0
d001a7a8:	f1b8d808 			; <UNDEFINED> instruction: 0xf1b8d808
d001a7ac:	d0050f00 	andle	r0, r5, r0, lsl #30
d001a7b0:	99082240 	stmdbls	r8, {r6, r9, sp}
d001a7b4:	f2f1fbb2 			; <UNDEFINED> instruction: 0xf2f1fbb2
d001a7b8:	d9244590 	stmdble	r4!, {r4, r7, r8, sl, lr}
d001a7bc:	f44f4a96 	vst1.32	{d20-d21}, [pc :64], r6
d001a7c0:	447a711a 	ldrbtmi	r7, [sl], #-282	; 0xfffffee6
d001a7c4:	2303fb01 	movwcs	pc, #15105	; 0x3b01	; <UNPREDICTABLE>
d001a7c8:	3368f503 	msrcc	SPSR_f, #12582912	; 0xc00000
d001a7cc:	302bf893 	mlacc	fp, r3, r8, pc	; <UNPREDICTABLE>
d001a7d0:	4a92b9b3 	bmi	0xce4c8ea4
d001a7d4:	4b92447a 	blmi	0xce4ab9c4
d001a7d8:	6d99447b 	cfldrsvs	mvf4, [r9, #492]	; 0x1ec
d001a7dc:	f47f2900 			; <UNDEFINED> instruction: 0xf47f2900
d001a7e0:	6a5daf35 	bvs	0xd17864bc
d001a7e4:	6b596a9c 	blvs	0xd167525c
d001a7e8:	0030f893 	mlaseq	r0, r3, r8, pc	; <UNPREDICTABLE>
d001a7ec:	e9c36699 	stmib	r3, {r0, r3, r4, r7, r9, sl, sp, lr}^
d001a7f0:	e9c32516 	stmib	r3, {r1, r2, r4, r8, sl, sp}^
d001a7f4:	e7294018 			; <UNDEFINED> instruction: 0xe7294018
d001a7f8:	e79a9009 	ldr	r9, [sl, r9]
d001a7fc:	e7be2600 	ldr	r2, [lr, r0, lsl #12]!
d001a800:	447a4a88 	ldrbtmi	r4, [sl], #-2696	; 0xfffff578
d001a804:	4648e7e7 	strbmi	lr, [r8], -r7, ror #15
d001a808:	fafef7f8 	blx	0xcffd87f0
d001a80c:	215d4a86 	cmpcs	sp, r6, lsl #21
d001a810:	447a4648 	ldrbtmi	r4, [sl], #-1608	; 0xfffff9b8
d001a814:	fb21f7f8 	blx	0xd08987fe
d001a818:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001a81c:	b9d7af17 	ldmiblt	r7, {r0, r1, r2, r4, r8, r9, sl, fp, sp, pc}^
d001a820:	fb089b08 	blx	0xd024144a
d001a824:	4b81f903 	blmi	0xce098c38
d001a828:	447b4a70 	ldrbtmi	r4, [fp], #-2672	; 0xfffff590
d001a82c:	f1c258d2 			; <UNDEFINED> instruction: 0xf1c258d2
d001a830:	454a0240 	strbmi	r0, [sl, #-576]	; 0xfffffdc0
d001a834:	6d9ad212 	lfmvs	f5, 1, [sl, #72]	; 0x48
d001a838:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d001a83c:	4a7caf07 	bmi	0xd1f46460
d001a840:	b068f8c3 	rsblt	pc, r8, r3, asr #17
d001a844:	e9c3447a 	stmib	r3, {r1, r3, r4, r5, r6, sl, lr}^
d001a848:	e9c35a18 	stmib	r3, {r3, r4, r9, fp, ip, lr}^
d001a84c:	e6fd2416 	usat	r2, #29, r6, lsl #8
d001a850:	0801f04f 	stmdaeq	r1, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d001a854:	f04fe7e3 			; <UNDEFINED> instruction: 0xf04fe7e3
d001a858:	e7e40901 	strb	r0, [r4, r1, lsl #18]!
d001a85c:	2b009b09 	blcs	0xd0041488
d001a860:	2f00d15c 	svccs	0x0000d15c
d001a864:	2e00d15c 	mcrcs	1, 0, sp, cr0, cr12, {2}
d001a868:	2310bf14 	tstcs	r0, #20, 30	; 0x50
d001a86c:	9304230d 	movwls	r2, #17165	; 0x430d
d001a870:	9512ab16 	ldrls	sl, [r2, #-2838]	; 0xfffff4ea
d001a874:	a050f88d 	subsge	pc, r0, sp, lsl #17
d001a878:	b054f8cd 	subslt	pc, r4, sp, asr #17
d001a87c:	e9139411 	ldmdb	r3, {r0, r4, sl, ip, pc}
d001a880:	e88d000f 	stm	sp, {r0, r1, r2, r3}
d001a884:	9b0a000f 	blls	0xd029a8c8
d001a888:	f7f9cb0f 			; <UNDEFINED> instruction: 0xf7f9cb0f
d001a88c:	4a69fba5 	bmi	0xd1a99728
d001a890:	447a4605 	ldrbtmi	r4, [sl], #-1541	; 0xfffff9fb
d001a894:	2b006d93 	blcs	0xd0035ee8
d001a898:	aed8f47f 	mrcge	4, 6, APSR_nzcv, cr8, cr15, {3}
d001a89c:	f8df2330 			; <UNDEFINED> instruction: 0xf8df2330
d001a8a0:	f04fa14c 			; <UNDEFINED> instruction: 0xf04fa14c
d001a8a4:	fb030b01 	blx	0xd00dd4b2
d001a8a8:	9a0d2300 	bls	0xd03634b0
d001a8ac:	13a4f503 			; <UNDEFINED> instruction: 0x13a4f503
d001a8b0:	2656f883 	ldrbcs	pc, [r6], -r3, lsl #17	; <UNPREDICTABLE>
d001a8b4:	865ef8a3 	ldrbhi	pc, [lr], -r3, lsr #17	; <UNPREDICTABLE>
d001a8b8:	449a9b07 	ldrmi	r9, [sl], #2823	; 0xb07
d001a8bc:	f8da45d9 			; <UNDEFINED> instruction: 0xf8da45d9
d001a8c0:	d82f4000 	stmdale	pc!, {lr}	; <UNPREDICTABLE>
d001a8c4:	4b4a9a07 	blmi	0xd12c10e8
d001a8c8:	681a4413 	ldmdavs	sl, {r0, r1, r4, sl, lr}
d001a8cc:	bf884294 	svclt	0x00884294
d001a8d0:	2f00601c 	svccs	0x0000601c
d001a8d4:	4c58d047 	mrrcmi	0, 4, sp, r8, cr7
d001a8d8:	447c213d 	ldrbtmi	r2, [ip], #-317	; 0xfffffec3
d001a8dc:	f7f84620 			; <UNDEFINED> instruction: 0xf7f84620
d001a8e0:	4601faae 	strmi	pc, [r1], -lr, lsr #21
d001a8e4:	d03a2800 	eorsle	r2, sl, r0, lsl #16
d001a8e8:	46209b09 	strtmi	r9, [r0], -r9, lsl #22
d001a8ec:	b39b990d 	orrslt	r9, fp, #212992	; 0x34000
d001a8f0:	fb24f7fb 	blx	0xd09588e6
d001a8f4:	22004851 	andcs	r4, r0, #5308416	; 0x510000
d001a8f8:	44784629 	ldrbtmi	r4, [r8], #-1577	; 0xfffff9d7
d001a8fc:	fa5ff7fa 	blx	0xd18188ec
d001a900:	4478484f 	ldrbtmi	r4, [r8], #-2127	; 0xfffff7b1
d001a904:	2b006d83 	blcs	0xd0035f18
d001a908:	80acf000 	adchi	pc, ip, r0
d001a90c:	213b4a4d 	teqcs	fp, sp, asr #20
d001a910:	447a484d 	ldrbtmi	r4, [sl], #-2125	; 0xfffff7b3
d001a914:	f7f84478 			; <UNDEFINED> instruction: 0xf7f84478
d001a918:	e697faa0 	ldr	pc, [r7], r0, lsr #21
d001a91c:	e7a62312 			; <UNDEFINED> instruction: 0xe7a62312
d001a920:	e7a4230e 	str	r2, [r4, lr, lsl #6]!
d001a924:	22301c63 	eorscs	r1, r0, #25344	; 0x6300
d001a928:	f10b2100 			; <UNDEFINED> instruction: 0xf10b2100
d001a92c:	f8ca0b01 			; <UNDEFINED> instruction: 0xf8ca0b01
d001a930:	9b0b3000 	blls	0xd02e6938
d001a934:	930a781b 	movwls	r7, #43035	; 0xa81b
d001a938:	fb029b07 	blx	0xd00c155e
d001a93c:	f5043404 			; <UNDEFINED> instruction: 0xf5043404
d001a940:	f20414a4 	vshl.s8	d1, d20, d20
d001a944:	f0046034 			; <UNDEFINED> instruction: 0xf0046034
d001a948:	9b0affb3 	blls	0xd02da81c
d001a94c:	3654f884 	ldrbcc	pc, [r4], -r4, lsl #17	; <UNPREDICTABLE>
d001a950:	f884230b 			; <UNDEFINED> instruction: 0xf884230b
d001a954:	e7b13655 	sbfx	r3, r5, #12, #18
d001a958:	fb0af7fd 	blx	0xd02d8956
d001a95c:	4620e7ca 	strtmi	lr, [r0], -sl, asr #15
d001a960:	f9dbf7fa 			; <UNDEFINED> instruction: 0xf9dbf7fa
d001a964:	4c39e7c6 	ldcmi	7, cr14, [r9], #-792	; 0xfffffce8
d001a968:	447c213d 	ldrbtmi	r2, [ip], #-317	; 0xfffffec3
d001a96c:	f7f84620 			; <UNDEFINED> instruction: 0xf7f84620
d001a970:	2800fa66 	stmdacs	r0, {r1, r2, r5, r6, r9, fp, ip, sp, lr, pc}
d001a974:	b9ded0c4 	ldmiblt	lr, {r2, r6, r7, ip, lr, pc}^
d001a978:	2b7b6ae3 	blcs	0xd1ef550c
d001a97c:	990dd018 	stmdbls	sp, {r3, r4, ip, lr, pc}
d001a980:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d001a984:	4620fe89 	strtmi	pc, [r0], -r9, lsl #29
d001a988:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d001a98c:	f966f7fa 			; <UNDEFINED> instruction: 0xf966f7fa
d001a990:	f7fa4629 			; <UNDEFINED> instruction: 0xf7fa4629
d001a994:	4620fa2d 	strtmi	pc, [r0], -sp, lsr #20
d001a998:	6101f244 	tstvs	r1, r4, asr #4	; <UNPREDICTABLE>
d001a99c:	f95ef7fa 			; <UNDEFINED> instruction: 0xf95ef7fa
d001a9a0:	4105f64b 	tstmi	r5, fp, asr #12	; <UNPREDICTABLE>
d001a9a4:	f95af7fa 			; <UNDEFINED> instruction: 0xf95af7fa
d001a9a8:	f7fb9808 			; <UNDEFINED> instruction: 0xf7fb9808
d001a9ac:	e7a7fb57 	sbfx	pc, r7, #22, #8
d001a9b0:	21004827 	tstcs	r0, r7, lsr #16
d001a9b4:	44782400 	ldrbtmi	r2, [r8], #-1024	; 0xfffffc00
d001a9b8:	f9aff7fa 			; <UNDEFINED> instruction: 0xf9aff7fa
d001a9bc:	44784825 	ldrbtmi	r4, [r8], #-2085	; 0xfffff7db
d001a9c0:	d10a45a1 	smlatble	sl, r1, r5, r4
d001a9c4:	2e00980d 	cdpcs	8, 0, cr9, cr0, cr13, {0}
d001a9c8:	2300d046 	movwcs	sp, #70	; 0x46
d001a9cc:	462a4601 	strtmi	r4, [sl], -r1, lsl #12
d001a9d0:	93004640 	movwls	r4, #1600	; 0x640
d001a9d4:	fc70f7ff 	ldc2l	7, cr15, [r0], #-1020	; 0xfffffc04
d001a9d8:	1929e792 	stmdbne	r9!, {r1, r4, r7, r8, r9, sl, sp, lr, pc}
d001a9dc:	34012200 	strcc	r2, [r1], #-512	; 0xfffffe00
d001a9e0:	f9edf7fa 			; <UNDEFINED> instruction: 0xf9edf7fa
d001a9e4:	bf00e7ec 	svclt	0x0000e7ec
d001a9e8:	0014923c 	andseq	r9, r4, ip, lsr r2
d001a9ec:	00149234 	andseq	r9, r4, r4, lsr r2
d001a9f0:	00149238 	andseq	r9, r4, r8, lsr r2
d001a9f4:	0000bdd4 	ldrdeq	fp, [r0], -r4
d001a9f8:	0000bd44 	andeq	fp, r0, r4, asr #26
d001a9fc:	fffffd2b 			; <UNDEFINED> instruction: 0xfffffd2b
d001aa00:	0000bd22 	andeq	fp, r0, r2, lsr #26
d001aa04:	0000bcfc 	strdeq	fp, [r0], -ip
d001aa08:	0000bcf0 	strdeq	fp, [r0], -r0
d001aa0c:	0000bcce 	andeq	fp, r0, lr, asr #25
d001aa10:	fffffcea 			; <UNDEFINED> instruction: 0xfffffcea
d001aa14:	0000bc7c 	andeq	fp, r0, ip, ror ip
d001aa18:	0000bc42 	andeq	fp, r0, r2, asr #24
d001aa1c:	fffffc0d 			; <UNDEFINED> instruction: 0xfffffc0d
d001aa20:	0000bc2c 	andeq	fp, r0, ip, lsr #24
d001aa24:	fffffbb6 			; <UNDEFINED> instruction: 0xfffffbb6
d001aa28:	fffffc50 			; <UNDEFINED> instruction: 0xfffffc50
d001aa2c:	0000bbda 	ldrdeq	fp, [r0], -sl
d001aa30:	fffffc43 			; <UNDEFINED> instruction: 0xfffffc43
d001aa34:	0000bb72 	andeq	fp, r0, r2, ror fp
d001aa38:	0000bb2a 	andeq	fp, r0, sl, lsr #22
d001aa3c:	0000bb0a 	andeq	fp, r0, sl, lsl #22
d001aa40:	0000bb02 	andeq	fp, r0, r2, lsl #22
d001aa44:	fffffba3 			; <UNDEFINED> instruction: 0xfffffba3
d001aa48:	0000baf0 	strdeq	fp, [r0], -r0
d001aa4c:	0000ba9a 	muleq	r0, sl, sl
d001aa50:	0000ba4e 	andeq	fp, r0, lr, asr #20
d001aa54:	0000ba46 	andeq	fp, r0, r6, asr #20
d001aa58:	46322301 	ldrtmi	r2, [r2], -r1, lsl #6
d001aa5c:	f7ff4629 			; <UNDEFINED> instruction: 0xf7ff4629
d001aa60:	e74dfaf9 			; <UNDEFINED> instruction: 0xe74dfaf9
d001aa64:	f7f8212c 			; <UNDEFINED> instruction: 0xf7f8212c
d001aa68:	2800f9ea 	stmdacs	r0, {r1, r3, r5, r6, r7, r8, fp, ip, sp, lr, pc}
d001aa6c:	ae50f47f 	mrcge	4, 2, APSR_nzcv, cr0, cr15, {3}
d001aa70:	6ae2e74c 	bvs	0xcf8d47a8
d001aa74:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d001aa78:	d007429a 	mulle	r7, sl, r2
d001aa7c:	f43f2d00 			; <UNDEFINED> instruction: 0xf43f2d00
d001aa80:	49bdade6 	ldmibmi	sp!, {r1, r2, r5, r6, r7, r8, sl, fp, sp, pc}
d001aa84:	447948bd 	ldrbtmi	r4, [r9], #-2237	; 0xfffff743
d001aa88:	e62b4478 			; <UNDEFINED> instruction: 0xe62b4478
d001aa8c:	1206e9d4 	andne	lr, r6, #212, 18	; 0x350000
d001aa90:	f7f54620 			; <UNDEFINED> instruction: 0xf7f54620
d001aa94:	2800fe39 	stmdacs	r0, {r0, r3, r4, r5, r9, sl, fp, ip, sp, lr, pc}
d001aa98:	48b9daf0 	ldmmi	r9!, {r4, r5, r6, r7, r9, fp, ip, lr, pc}
d001aa9c:	f7fa4478 			; <UNDEFINED> instruction: 0xf7fa4478
d001aaa0:	2800f891 	stmdacs	r0, {r0, r4, r7, fp, ip, sp, lr, pc}
d001aaa4:	815ff040 	cmphi	pc, r0, asr #32	; <UNPREDICTABLE>
d001aaa8:	447848b6 	ldrbtmi	r4, [r8], #-2230	; 0xfffff74a
d001aaac:	f88af7fa 			; <UNDEFINED> instruction: 0xf88af7fa
d001aab0:	d04a2800 	suble	r2, sl, r0, lsl #16
d001aab4:	93072305 	movwls	r2, #29445	; 0x7305
d001aab8:	d1e22d00 	mvnle	r2, r0, lsl #26
d001aabc:	4bb29509 	blmi	0xcecbfee8
d001aac0:	447b4aaa 	ldrbtmi	r4, [fp], #-2730	; 0xfffff556
d001aac4:	44139308 	ldrmi	r9, [r3], #-776	; 0xfffffcf8
d001aac8:	9b09930b 	blls	0xd027f6fc
d001aacc:	d0432b00 	suble	r2, r3, r0, lsl #22
d001aad0:	212a4cae 			; <UNDEFINED> instruction: 0x212a4cae
d001aad4:	4620447c 			; <UNDEFINED> instruction: 0x4620447c
d001aad8:	f9b1f7f8 			; <UNDEFINED> instruction: 0xf9b1f7f8
d001aadc:	d03b2800 	eorsle	r2, fp, r0, lsl #16
d001aae0:	4620212a 	strtmi	r2, [r0], -sl, lsr #2
d001aae4:	f9abf7f8 			; <UNDEFINED> instruction: 0xf9abf7f8
d001aae8:	bf142800 	svclt	0x00142800
d001aaec:	260a2613 			; <UNDEFINED> instruction: 0x260a2613
d001aaf0:	af0e4ca7 	svcge	0x000e4ca7
d001aaf4:	f104447c 			; <UNDEFINED> instruction: 0xf104447c
d001aaf8:	f8d40c18 			; <UNDEFINED> instruction: 0xf8d40c18
d001aafc:	f8d4a024 			; <UNDEFINED> instruction: 0xf8d4a024
d001ab00:	f8949028 			; <UNDEFINED> instruction: 0xf8949028
d001ab04:	e8bc8030 	ldm	ip!, {r4, r5, pc}
d001ab08:	c70f000f 	strgt	r0, [pc, -pc]
d001ab0c:	000fe89c 	muleq	pc, ip, r8	; <UNPREDICTABLE>
d001ab10:	000fe887 	andeq	lr, pc, r7, lsl #17
d001ab14:	f2404a9f 	vpmin.s8	d20, d16, d15
d001ab18:	46201101 	strtmi	r1, [r0], -r1, lsl #2
d001ab1c:	447a6b67 	ldrbtmi	r6, [sl], #-2919	; 0xfffff499
d001ab20:	f99bf7f8 			; <UNDEFINED> instruction: 0xf99bf7f8
d001ab24:	930aab0e 	movwls	sl, #43790	; 0xab0e
d001ab28:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001ab2c:	b1adad8f 			; <UNDEFINED> instruction: 0xb1adad8f
d001ab30:	6da3b1a6 	stfvsd	f3, [r3, #664]!	; 0x298
d001ab34:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001ab38:	4b97ad89 	blmi	0xce606164
d001ab3c:	66a7447b 	sxtabvs	r4, r7, fp, ror #8
d001ab40:	3a16e9c4 	bcc	0xd05d5258
d001ab44:	9818e9c4 	ldmdals	r8, {r2, r6, r7, r8, fp, sp, lr, pc}
d001ab48:	4894e580 	ldmmi	r4, {r7, r8, sl, sp, lr, pc}
d001ab4c:	f7fa4478 			; <UNDEFINED> instruction: 0xf7fa4478
d001ab50:	2800f839 	stmdacs	r0, {r0, r3, r4, r5, fp, ip, sp, lr, pc}
d001ab54:	e791d1ae 	ldr	sp, [r1, lr, lsr #3]
d001ab58:	e7c99e07 	strb	r9, [r9, r7, lsl #28]
d001ab5c:	215b4c90 			; <UNDEFINED> instruction: 0x215b4c90
d001ab60:	4620447c 			; <UNDEFINED> instruction: 0x4620447c
d001ab64:	f96bf7f8 			; <UNDEFINED> instruction: 0xf96bf7f8
d001ab68:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d001ab6c:	b13580a8 	teqlt	r5, r8, lsr #1
d001ab70:	2b006da3 	blcs	0xd0036204
d001ab74:	ad6af47f 	cfstrdge	mvd15, [sl, #-508]!	; 0xfffffe04
d001ab78:	447b4b8a 	ldrbtmi	r4, [fp], #-2954	; 0xfffff476
d001ab7c:	b136e7df 	teqlt	r6, pc	; <illegal shifter operand>
d001ab80:	2b006da3 	blcs	0xd0036214
d001ab84:	ad62f47f 	cfstrdge	mvd15, [r2, #-508]!	; 0xfffffe04
d001ab88:	447b4b87 	ldrbtmi	r4, [fp], #-2951	; 0xfffff479
d001ab8c:	6ae3e7d7 	bvs	0xcf914af0
d001ab90:	b020f8d4 	ldrdlt	pc, [r0], -r4	; <UNPREDICTABLE>
d001ab94:	7381f5a3 	orrvc	pc, r1, #683671552	; 0x28c00000
d001ab98:	d8092b01 	stmdale	r9, {r0, r8, r9, fp, sp}
d001ab9c:	0f00f1bb 	svceq	0x0000f1bb
d001aba0:	4e73d006 	cdpmi	0, 7, cr13, cr3, cr6, {0}
d001aba4:	68334426 	ldmdavs	r3!, {r1, r2, r5, sl, lr}
d001aba8:	0340f1c3 	movteq	pc, #451	; 0x1c3	; <UNPREDICTABLE>
d001abac:	d912459b 	ldmdble	r2, {r0, r1, r3, r4, r7, r8, sl, lr}
d001abb0:	447b4b7e 	ldrbtmi	r4, [fp], #-2942	; 0xfffff482
d001abb4:	2a006d9a 	bcs	0xd0036224
d001abb8:	ad48f47f 	cfstrdge	mvd15, [r8, #-508]	; 0xfffffe04
d001abbc:	6a5c4d7c 	bvs	0xd172e1b4
d001abc0:	447d6a98 	ldrbtmi	r6, [sp], #-2712	; 0xfffff568
d001abc4:	f8936b5a 			; <UNDEFINED> instruction: 0xf8936b5a
d001abc8:	669a1030 			; <UNDEFINED> instruction: 0x669a1030
d001abcc:	5416e9c3 	ldrpl	lr, [r6], #-2499	; 0xfffff63d
d001abd0:	0118e9c3 	tsteq	r8, r3, asr #19
d001abd4:	4620e53a 			; <UNDEFINED> instruction: 0x4620e53a
d001abd8:	f916f7f8 			; <UNDEFINED> instruction: 0xf916f7f8
d001abdc:	215d4a75 	cmpcs	sp, r5, ror sl
d001abe0:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d001abe4:	f939f7f8 			; <UNDEFINED> instruction: 0xf939f7f8
d001abe8:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001abec:	2309ad2f 	movwcs	sl, #40239	; 0x9d2f
d001abf0:	f8cd9715 			; <UNDEFINED> instruction: 0xf8cd9715
d001abf4:	93049048 	movwls	r9, #16456	; 0x4048
d001abf8:	f88dab16 			; <UNDEFINED> instruction: 0xf88dab16
d001abfc:	f8cd8050 			; <UNDEFINED> instruction: 0xf8cd8050
d001ac00:	e913a044 	ldmdb	r3, {r2, r6, sp, pc}
d001ac04:	e88d000f 	stm	sp, {r0, r1, r2, r3}
d001ac08:	9b0a000f 	blls	0xd029ac4c
d001ac0c:	f7f9cb0f 			; <UNDEFINED> instruction: 0xf7f9cb0f
d001ac10:	6da3f9e3 			; <UNDEFINED> instruction: 0x6da3f9e3
d001ac14:	2b004607 	blcs	0xd002c438
d001ac18:	ad18f47f 	cfldrsge	mvf15, [r8, #-508]	; 0xfffffe04
d001ac1c:	f04f2330 			; <UNDEFINED> instruction: 0xf04f2330
d001ac20:	fb030801 	blx	0xd00dcc2e
d001ac24:	f5044400 			; <UNDEFINED> instruction: 0xf5044400
d001ac28:	f8a414a4 			; <UNDEFINED> instruction: 0xf8a414a4
d001ac2c:	45c3b65e 	strbmi	fp, [r3, #1630]	; 0x65e
d001ac30:	d12c6834 			; <UNDEFINED> instruction: 0xd12c6834
d001ac34:	213d9a08 	teqcs	sp, r8, lsl #20
d001ac38:	44134b4e 	ldrmi	r4, [r3], #-2894	; 0xfffff4b2
d001ac3c:	42a2681a 	adcmi	r6, r2, #1703936	; 0x1a0000
d001ac40:	601cbf38 	andsvs	fp, ip, r8, lsr pc
d001ac44:	447c4c5c 	ldrbtmi	r4, [ip], #-3164	; 0xfffff3a4
d001ac48:	f7f84620 			; <UNDEFINED> instruction: 0xf7f84620
d001ac4c:	b198f8f8 			; <UNDEFINED> instruction: 0xb198f8f8
d001ac50:	21004620 	tstcs	r0, r0, lsr #12
d001ac54:	f861f7fa 			; <UNDEFINED> instruction: 0xf861f7fa
d001ac58:	46202600 	strtmi	r2, [r0], -r0, lsl #12
d001ac5c:	360119b9 			; <UNDEFINED> instruction: 0x360119b9
d001ac60:	f7fa2200 			; <UNDEFINED> instruction: 0xf7fa2200
d001ac64:	45b0f8ac 	ldrmi	pc, [r0, #2220]!	; 0x8ac
d001ac68:	2300d1f8 	movwcs	sp, #504	; 0x1f8
d001ac6c:	21ff463a 	mvnscs	r4, sl, lsr r6
d001ac70:	93004640 	movwls	r4, #1600	; 0x640
d001ac74:	fb20f7ff 	blx	0xd0858c7a
d001ac78:	44784850 	ldrbtmi	r4, [r8], #-2128	; 0xfffff7b0
d001ac7c:	2b006d83 	blcs	0xd0036290
d001ac80:	4a4fd06a 	bmi	0xd140ee30
d001ac84:	484f213b 	stmdami	pc, {r0, r1, r3, r4, r5, r8, sp}^	; <UNPREDICTABLE>
d001ac88:	4478447a 	ldrbtmi	r4, [r8], #-1146	; 0xfffffb86
d001ac8c:	1c63e643 	stclne	6, cr14, [r3], #-268	; 0xfffffef4
d001ac90:	21002230 	tstcs	r0, r0, lsr r2
d001ac94:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d001ac98:	9b0b6033 	blls	0xd02f2d6c
d001ac9c:	9000f893 	mulls	r0, r3, r8
d001aca0:	fb029b08 	blx	0xd00c18ca
d001aca4:	f5043404 			; <UNDEFINED> instruction: 0xf5043404
d001aca8:	f20414a4 	vshl.s8	d1, d20, d20
d001acac:	f0046034 			; <UNDEFINED> instruction: 0xf0046034
d001acb0:	230bfdff 	movwcs	pc, #48639	; 0xbdff	; <UNPREDICTABLE>
d001acb4:	9654f884 	ldrbls	pc, [r4], -r4, lsl #17	; <UNPREDICTABLE>
d001acb8:	3655f884 	ldrbcc	pc, [r5], -r4, lsl #17	; <UNPREDICTABLE>
d001acbc:	b2f3e7b7 	rscslt	lr, r3, #47972352	; 0x2dc0000
d001acc0:	9048f8cd 	subls	pc, r8, sp, asr #17
d001acc4:	8050f88d 	subshi	pc, r0, sp, lsl #17
d001acc8:	ab169304 	blge	0xd05bf8e0
d001accc:	f8cd9715 			; <UNDEFINED> instruction: 0xf8cd9715
d001acd0:	e913a044 	ldmdb	r3, {r2, r6, sp, pc}
d001acd4:	e88d000f 	stm	sp, {r0, r1, r2, r3}
d001acd8:	9b0a000f 	blls	0xd029ad1c
d001acdc:	f7f9cb0f 			; <UNDEFINED> instruction: 0xf7f9cb0f
d001ace0:	6da3f97b 			; <UNDEFINED> instruction: 0x6da3f97b
d001ace4:	2b004683 	blcs	0xd002c6f8
d001ace8:	acb0f47f 	cfldrsge	mvf15, [r0], #508	; 0x1fc
d001acec:	213d2330 	teqcs	sp, r0, lsr r3
d001acf0:	4300fb03 	movwmi	pc, #2819	; 0xb03	; <UNPREDICTABLE>
d001acf4:	f5034620 			; <UNDEFINED> instruction: 0xf5034620
d001acf8:	f88313a4 			; <UNDEFINED> instruction: 0xf88313a4
d001acfc:	f7f85660 			; <UNDEFINED> instruction: 0xf7f85660
d001ad00:	b1e0f89e 			; <UNDEFINED> instruction: 0xb1e0f89e
d001ad04:	d1092e13 	tstle	r9, r3, lsl lr
d001ad08:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d001ad0c:	482ef8b7 	stmdami	lr!, {r0, r1, r2, r4, r5, r7, fp, ip, sp, lr, pc}
d001ad10:	46592200 	ldrbmi	r2, [r9], -r0, lsl #4
d001ad14:	f7fa4478 			; <UNDEFINED> instruction: 0xf7fa4478
d001ad18:	e7adf852 	sbfx	pc, r2, #16, #14
d001ad1c:	f04f2e0a 			; <UNDEFINED> instruction: 0xf04f2e0a
d001ad20:	46200101 	strtmi	r0, [r0], -r1, lsl #2
d001ad24:	2204bf0c 	andcs	fp, r4, #12, 30	; 0x30
d001ad28:	f7fb2201 			; <UNDEFINED> instruction: 0xf7fb2201
d001ad2c:	2e05faff 			; <UNDEFINED> instruction: 0x2e05faff
d001ad30:	f24bd1ed 	vrhadd.s8	<illegal reg q14.5>, <illegal reg q13.5>, <illegal reg q14.5>
d001ad34:	462021c0 	strtmi	r2, [r0], -r0, asr #3
d001ad38:	ff90f7f9 			; <UNDEFINED> instruction: 0xff90f7f9
d001ad3c:	2d00e7e7 	stccs	7, cr14, [r0, #-924]	; 0xfffffc64
d001ad40:	6da3d09a 	stcvs	0, cr13, [r3, #616]!	; 0x268
d001ad44:	d1972b00 	orrsle	r2, r7, r0, lsl #22
d001ad48:	66a74b20 	strtvs	r4, [r7], r0, lsr #22
d001ad4c:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d001ad50:	e9c49818 	stmib	r4, {r3, r4, fp, ip, pc}^
d001ad54:	e78f3a16 	usada8	pc, r6, sl, r3	; <UNPREDICTABLE>
d001ad58:	f7f8212c 			; <UNDEFINED> instruction: 0xf7f8212c
d001ad5c:	2800f870 	stmdacs	r0, {r4, r5, r6, fp, ip, sp, lr, pc}
d001ad60:	aeb3f47f 	mrcge	4, 5, APSR_nzcv, cr3, cr15, {3}
d001ad64:	2301e78d 	movwcs	lr, #6029	; 0x178d
d001ad68:	bf00e6a5 	svclt	0x0000e6a5
d001ad6c:	0014923c 	andseq	r9, r4, ip, lsr r2
d001ad70:	00149234 	andseq	r9, r4, r4, lsr r2
d001ad74:	00149238 	andseq	r9, r4, r8, lsr r2
d001ad78:	fffffa64 			; <UNDEFINED> instruction: 0xfffffa64
d001ad7c:	0000b97c 	andeq	fp, r0, ip, ror r9
d001ad80:	fffffa3c 			; <UNDEFINED> instruction: 0xfffffa3c
d001ad84:	fffffa37 			; <UNDEFINED> instruction: 0xfffffa37
d001ad88:	0000b942 	andeq	fp, r0, r2, asr #18
d001ad8c:	0000b930 	andeq	fp, r0, r0, lsr r9
d001ad90:	0000b910 	andeq	fp, r0, r0, lsl r9
d001ad94:	fffffa06 			; <UNDEFINED> instruction: 0xfffffa06
d001ad98:	fffff9ae 			; <UNDEFINED> instruction: 0xfffff9ae
d001ad9c:	ffff8c56 			; <UNDEFINED> instruction: 0xffff8c56
d001ada0:	0000b8a4 	andeq	fp, r0, r4, lsr #17
d001ada4:	fffff9c9 			; <UNDEFINED> instruction: 0xfffff9c9
d001ada8:	fffff9dc 			; <UNDEFINED> instruction: 0xfffff9dc
d001adac:	0000b852 	andeq	fp, r0, r2, asr r8
d001adb0:	fffff9c8 			; <UNDEFINED> instruction: 0xfffff9c8
d001adb4:	fffff9d9 			; <UNDEFINED> instruction: 0xfffff9d9
d001adb8:	0000b7be 			; <UNDEFINED> instruction: 0x0000b7be
d001adbc:	0000b78a 	andeq	fp, r0, sl, lsl #15
d001adc0:	fffff977 			; <UNDEFINED> instruction: 0xfffff977
d001adc4:	0000b77a 	andeq	fp, r0, sl, ror r7
d001adc8:	0000b6f0 	strdeq	fp, [r0], -r0
d001adcc:	fffff893 			; <UNDEFINED> instruction: 0xfffff893

Disassembly of section .text.statement.constprop.0:

d001b12c <.text.statement.constprop.0>:
d001b12c:	4ff0e92d 	svcmi	0x00f0e92d
d001b130:	447c4cd8 	ldrbtmi	r4, [ip], #-3288	; 0xfffff328
d001b134:	ed2d6da3 	stc	13, cr6, [sp, #-652]!	; 0xfffffd74
d001b138:	b08f8b02 	addlt	r8, pc, r2, lsl #22
d001b13c:	f504bb3b 			; <UNDEFINED> instruction: 0xf504bb3b
d001b140:	f50717a4 			; <UNDEFINED> instruction: 0xf50717a4
d001b144:	68135292 	ldmdavs	r3, {r1, r4, r7, r9, ip, lr}
d001b148:	2b203301 	blcs	0xd0827d54
d001b14c:	d9036013 	stmdble	r3, {r0, r1, r4, sp, lr}
d001b150:	447949d1 	ldrbtmi	r4, [r9], #-2513	; 0xfffff62f
d001b154:	e0604620 	rsb	r4, r0, r0, lsr #12
d001b158:	4620217b 			; <UNDEFINED> instruction: 0x4620217b
d001b15c:	fe6ff7f7 	mcr2	7, 3, pc, cr15, cr7, {7}	; <UNPREDICTABLE>
d001b160:	b1c84606 	biclt	r4, r8, r6, lsl #12
d001b164:	4ec84dc7 	cdpmi	13, 12, cr4, cr8, cr7, {6}
d001b168:	59a75963 	stmibpl	r7!, {r0, r1, r5, r6, r8, fp, ip, lr}
d001b16c:	51633301 	cmnpl	r3, r1, lsl #6
d001b170:	fd26f000 	stc2	0, cr15, [r6, #-0]
d001b174:	51a75963 			; <UNDEFINED> instruction: 0x51a75963
d001b178:	51633b01 	cmnpl	r3, r1, lsl #22
d001b17c:	447b4bc7 	ldrbtmi	r4, [fp], #-3015	; 0xfffff439
d001b180:	13a4f503 			; <UNDEFINED> instruction: 0x13a4f503
d001b184:	5392f503 	orrspl	pc, r2, #12582912	; 0xc00000
d001b188:	3a01681a 	bcc	0xd00751f8
d001b18c:	b00f601a 	andlt	r6, pc, sl, lsl r0	; <UNPREDICTABLE>
d001b190:	8b02ecbd 	blhi	0xd00d648c
d001b194:	8ff0e8bd 	svchi	0x00f0e8bd
d001b198:	7186f44f 	orrvc	pc, r6, pc, asr #8
d001b19c:	f7f74620 			; <UNDEFINED> instruction: 0xf7f74620
d001b1a0:	4680fe4e 	strmi	pc, [r0], lr, asr #28
d001b1a4:	f7feb350 			; <UNDEFINED> instruction: 0xf7feb350
d001b1a8:	4631fae9 	ldrtmi	pc, [r1], -r9, ror #21	; <UNPREDICTABLE>
d001b1ac:	f5044620 			; <UNDEFINED> instruction: 0xf5044620
d001b1b0:	f7fa378f 			; <UNDEFINED> instruction: 0xf7fa378f
d001b1b4:	4605f9b6 			; <UNDEFINED> instruction: 0x4605f9b6
d001b1b8:	ffb8f7ff 			; <UNDEFINED> instruction: 0xffb8f7ff
d001b1bc:	110df240 	tstne	sp, r0, asr #4	; <UNPREDICTABLE>
d001b1c0:	f7f74620 			; <UNDEFINED> instruction: 0xf7f74620
d001b1c4:	4603fe3c 			; <UNDEFINED> instruction: 0x4603fe3c
d001b1c8:	4620b1a0 	strtmi	fp, [r0], -r0, lsr #3
d001b1cc:	f99cf7fa 			; <UNDEFINED> instruction: 0xf99cf7fa
d001b1d0:	46334680 	ldrtmi	r4, [r3], -r0, lsl #13
d001b1d4:	21b8f8d7 			; <UNDEFINED> instruction: 0x21b8f8d7
d001b1d8:	6da04629 	stcvs	6, cr4, [r0, #164]!	; 0xa4
d001b1dc:	ff90f7fa 			; <UNDEFINED> instruction: 0xff90f7fa
d001b1e0:	ffa4f7ff 			; <UNDEFINED> instruction: 0xffa4f7ff
d001b1e4:	f8d74633 			; <UNDEFINED> instruction: 0xf8d74633
d001b1e8:	464121b8 			; <UNDEFINED> instruction: 0x464121b8
d001b1ec:	f7fa6da0 			; <UNDEFINED> instruction: 0xf7fa6da0
d001b1f0:	e7c3ff87 	strb	pc, [r3, r7, lsl #31]	; <UNPREDICTABLE>
d001b1f4:	21b8f8d7 			; <UNDEFINED> instruction: 0x21b8f8d7
d001b1f8:	e7f74629 	ldrb	r4, [r7, r9, lsr #12]!
d001b1fc:	7187f44f 	orrvc	pc, r7, pc, asr #8
d001b200:	f7f74620 			; <UNDEFINED> instruction: 0xf7f74620
d001b204:	2800fe1c 	stmdacs	r0, {r2, r3, r4, r9, sl, fp, ip, sp, lr, pc}
d001b208:	4da0d075 	stcmi	0, cr13, [r0, #468]!	; 0x1d4
d001b20c:	2b205963 	blcs	0xd08317a0
d001b210:	49a3d106 	stmibmi	r3!, {r1, r2, r8, ip, lr, pc}
d001b214:	447948a3 	ldrbtmi	r4, [r9], #-2211	; 0xfffff75d
d001b218:	f7f44478 			; <UNDEFINED> instruction: 0xf7f44478
d001b21c:	e7adffc5 	str	pc, [sp, r5, asr #31]!
d001b220:	f5044b9b 			; <UNDEFINED> instruction: 0xf5044b9b
d001b224:	58e619a5 	stmiapl	r6!, {r0, r2, r5, r7, r8, fp, ip}^
d001b228:	338ff504 	orrcc	pc, pc, #4, 10	; 0x1000000
d001b22c:	71b8f8d3 			; <UNDEFINED> instruction: 0x71b8f8d3
d001b230:	faa4f7fe 	blx	0xce959230
d001b234:	46204641 	strtmi	r4, [r0], -r1, asr #12
d001b238:	f973f7fa 			; <UNDEFINED> instruction: 0xf973f7fa
d001b23c:	46805963 	strmi	r5, [r0], r3, ror #18
d001b240:	51633301 	cmnpl	r3, r1, lsl #6
d001b244:	3250f8d9 	subscc	pc, r0, #14221312	; 0xd90000
d001b248:	d1312b40 	teqle	r1, r0, asr #22
d001b24c:	46204996 			; <UNDEFINED> instruction: 0x46204996
d001b250:	f7f44479 			; <UNDEFINED> instruction: 0xf7f44479
d001b254:	f8dfffa9 			; <UNDEFINED> instruction: 0xf8dfffa9
d001b258:	4c8d9254 	sfmmi	f1, 1, [sp], {84}	; 0x54
d001b25c:	f8df44f9 			; <UNDEFINED> instruction: 0xf8df44f9
d001b260:	f859a250 			; <UNDEFINED> instruction: 0xf859a250
d001b264:	46483005 	strbmi	r3, [r8], -r5
d001b268:	44fa444c 	ldrbtmi	r4, [sl], #1100	; 0x44c
d001b26c:	f8493b01 			; <UNDEFINED> instruction: 0xf8493b01
d001b270:	f5063005 			; <UNDEFINED> instruction: 0xf5063005
d001b274:	f7fa3524 			; <UNDEFINED> instruction: 0xf7fa3524
d001b278:	2300f947 	movwcs	pc, #2375	; 0x947	; <UNPREDICTABLE>
d001b27c:	463a4601 	ldrtmi	r4, [sl], -r1, lsl #12
d001b280:	0058f8d9 	ldrsbeq	pc, [r8], #-137	; 0xffffff77	; <UNPREDICTABLE>
d001b284:	254af205 	strbcs	pc, [sl, #-517]	; 0xfffffdfb	; <UNPREDICTABLE>
d001b288:	ff3af7fa 			; <UNDEFINED> instruction: 0xff3af7fa
d001b28c:	328ff509 	addcc	pc, pc, #37748736	; 0x2400000
d001b290:	eb094641 	bl	0xd026cb9c
d001b294:	46b005c5 	ldrtmi	r0, [r0], r5, asr #11
d001b298:	f8d22300 			; <UNDEFINED> instruction: 0xf8d22300
d001b29c:	f8d921b8 			; <UNDEFINED> instruction: 0xf8d921b8
d001b2a0:	f7fa0058 			; <UNDEFINED> instruction: 0xf7fa0058
d001b2a4:	6823ff2d 	stmdavs	r3!, {r0, r2, r3, r5, r8, r9, sl, fp, ip, sp, lr, pc}
d001b2a8:	d3124598 	tstle	r2, #152, 10	; 0x26000000
d001b2ac:	e7656026 	strb	r6, [r5, -r6, lsr #32]!
d001b2b0:	1c5a441c 	cfldrdne	mvd4, [sl], {28}
d001b2b4:	f5042301 			; <UNDEFINED> instruction: 0xf5042301
d001b2b8:	f8c914a5 			; <UNDEFINED> instruction: 0xf8c914a5
d001b2bc:	f8842250 			; <UNDEFINED> instruction: 0xf8842250
d001b2c0:	f7ff3254 			; <UNDEFINED> instruction: 0xf7ff3254
d001b2c4:	f8d9ff33 			; <UNDEFINED> instruction: 0xf8d9ff33
d001b2c8:	3b013250 	blcc	0xd0067c10
d001b2cc:	3250f8c9 	subscc	pc, r0, #13172736	; 0xc90000
d001b2d0:	792be7c1 	stmdbvc	fp!, {r0, r6, r7, r8, r9, sl, sp, lr, pc}
d001b2d4:	b1636829 	cmnlt	r3, r9, lsr #16
d001b2d8:	338ff509 	orrcc	pc, pc, #37748736	; 0x2400000
d001b2dc:	21b8f8d3 			; <UNDEFINED> instruction: 0x21b8f8d3
d001b2e0:	f8da2300 			; <UNDEFINED> instruction: 0xf8da2300
d001b2e4:	f1080058 	cps	#24
d001b2e8:	35080801 	strcc	r0, [r8, #-2049]	; 0xfffff7ff
d001b2ec:	ff08f7fa 			; <UNDEFINED> instruction: 0xff08f7fa
d001b2f0:	463ae7d9 			; <UNDEFINED> instruction: 0x463ae7d9
d001b2f4:	f240e7f4 	vaba.s8	q15, q8, q10
d001b2f8:	46201113 			; <UNDEFINED> instruction: 0x46201113
d001b2fc:	fd9ff7f7 	ldc2	7, cr15, [pc, #988]	; 0xd001b6e0
d001b300:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d001b304:	4d618101 	stfmip	f0, [r1, #-4]!
d001b308:	2b205963 	blcs	0xd083189c
d001b30c:	4a69d081 	bmi	0xd1a8f518
d001b310:	46202128 	strtmi	r2, [r0], -r8, lsr #2
d001b314:	f7f7447a 			; <UNDEFINED> instruction: 0xf7f7447a
d001b318:	2800fda0 	stmdacs	r0, {r5, r7, r8, sl, fp, ip, sp, lr, pc}
d001b31c:	af2ef43f 	svcge	0x002ef43f
d001b320:	4e584f59 	mrcmi	15, 2, r4, cr8, cr9, {2}
d001b324:	930059e3 	movwls	r5, #2531	; 0x9e3
d001b328:	f8544b59 			; <UNDEFINED> instruction: 0xf8544b59
d001b32c:	59a38003 	stmibpl	r3!, {r0, r1, pc}
d001b330:	51a33301 			; <UNDEFINED> instruction: 0x51a33301
d001b334:	f976f7ff 			; <UNDEFINED> instruction: 0xf976f7ff
d001b338:	b9689701 	stmdblt	r8!, {r0, r8, r9, sl, ip, pc}^
d001b33c:	4620213b 			; <UNDEFINED> instruction: 0x4620213b
d001b340:	fd7df7f7 	ldc2l	7, cr15, [sp, #-988]!	; 0xfffffc24
d001b344:	f7feb940 			; <UNDEFINED> instruction: 0xf7feb940
d001b348:	4a5bfb05 	bmi	0xd1719f64
d001b34c:	213b485b 	teqcs	fp, fp, asr r8
d001b350:	4478447a 	ldrbtmi	r4, [r8], #-1146	; 0xfffffb86
d001b354:	fd81f7f7 	stc2	7, cr15, [r1, #988]	; 0x3dc
d001b358:	447c4c59 	ldrbtmi	r4, [ip], #-3161	; 0xfffff3a7
d001b35c:	338ff504 	orrcc	pc, pc, #4, 10	; 0x1000000
d001b360:	b1b8f8d3 			; <UNDEFINED> instruction: 0xb1b8f8d3
d001b364:	2b3b6ae3 	blcs	0xd0ef5ef8
d001b368:	2202d079 	andcs	sp, r2, #121	; 0x79
d001b36c:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d001b370:	ffdcf7fa 			; <UNDEFINED> instruction: 0xffdcf7fa
d001b374:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d001b378:	f8d3f7fa 			; <UNDEFINED> instruction: 0xf8d3f7fa
d001b37c:	4c514607 	mrrcmi	6, 0, r4, r1, cr7
d001b380:	4a51213b 	bmi	0xd1463874
d001b384:	447a447c 	ldrbtmi	r4, [sl], #-1148	; 0xfffffb84
d001b388:	f7f74620 			; <UNDEFINED> instruction: 0xf7f74620
d001b38c:	4620fd66 	strtmi	pc, [r0], -r6, ror #26
d001b390:	f8baf7fa 			; <UNDEFINED> instruction: 0xf8baf7fa
d001b394:	338ff504 	orrcc	pc, pc, #4, 10	; 0x1000000
d001b398:	f8d34682 			; <UNDEFINED> instruction: 0xf8d34682
d001b39c:	6ae391b8 	bvs	0xcf8ffa84
d001b3a0:	d0012b29 	andle	r2, r1, r9, lsr #22
d001b3a4:	fad6f7fe 	blx	0xcf5d93a4
d001b3a8:	21294c48 			; <UNDEFINED> instruction: 0x21294c48
d001b3ac:	447c4a48 	ldrbtmi	r4, [ip], #-2632	; 0xfffff5b8
d001b3b0:	4620447a 			; <UNDEFINED> instruction: 0x4620447a
d001b3b4:	fd51f7f7 	ldc2l	7, cr15, [r1, #-988]	; 0xfffffc24
d001b3b8:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d001b3bc:	2300f8a5 	movwcs	pc, #2213	; 0x8a5	; <UNPREDICTABLE>
d001b3c0:	465a4601 	ldrbmi	r4, [sl], -r1, lsl #12
d001b3c4:	f7fa6da0 			; <UNDEFINED> instruction: 0xf7fa6da0
d001b3c8:	f504fe9b 			; <UNDEFINED> instruction: 0xf504fe9b
d001b3cc:	2300328f 	movwcs	r3, #655	; 0x28f
d001b3d0:	f8d24651 			; <UNDEFINED> instruction: 0xf8d24651
d001b3d4:	f50421b8 			; <UNDEFINED> instruction: 0xf50421b8
d001b3d8:	6da01aa5 			; <UNDEFINED> instruction: 0x6da01aa5
d001b3dc:	fe90f7fa 	mrc2	7, 4, pc, cr0, cr10, {7}
d001b3e0:	33015963 	movwcc	r5, #6499	; 0x1963
d001b3e4:	f8da5163 			; <UNDEFINED> instruction: 0xf8da5163
d001b3e8:	2b403250 	blcs	0xd1027d30
d001b3ec:	4939d139 	ldmdbmi	r9!, {r0, r3, r4, r5, r8, ip, lr, pc}
d001b3f0:	44794620 	ldrbtmi	r4, [r9], #-1568	; 0xfffff9e0
d001b3f4:	fed8f7f4 	mrc2	7, 6, pc, cr8, cr4, {7}
d001b3f8:	447c4c37 	ldrbtmi	r4, [ip], #-3127	; 0xfffff3c9
d001b3fc:	46205963 	strtmi	r5, [r0], -r3, ror #18
d001b400:	51633b01 	cmnpl	r3, r1, lsl #22
d001b404:	f880f7fa 			; <UNDEFINED> instruction: 0xf880f7fa
d001b408:	46012300 	strmi	r2, [r1], -r0, lsl #6
d001b40c:	6da0464a 	stcvs	6, cr4, [r0, #296]!	; 0x128
d001b410:	fe76f7fa 	mrc2	7, 3, pc, cr6, cr10, {7}
d001b414:	f504b147 			; <UNDEFINED> instruction: 0xf504b147
d001b418:	2300328f 	movwcs	r3, #655	; 0x28f
d001b41c:	6da04639 	stcvs	6, cr4, [r0, #228]!	; 0xe4
d001b420:	21b8f8d2 			; <UNDEFINED> instruction: 0x21b8f8d2
d001b424:	fe6cf7fa 	mcr2	7, 3, pc, cr12, cr10, {7}	; <UNPREDICTABLE>
d001b428:	3524f508 	strcc	pc, [r4, #-1288]!	; 0xfffffaf8
d001b42c:	4f184c2b 	svcmi	0x00184c2b
d001b430:	447c46c2 	ldrbtmi	r4, [ip], #-1730	; 0xfffff93e
d001b434:	254af205 	strbcs	pc, [sl, #-517]	; 0xfffffdfb	; <UNPREDICTABLE>
d001b438:	b0a4f8df 	ldrdlt	pc, [r4], pc	; <UNPREDICTABLE>
d001b43c:	05c5eb04 	strbeq	lr, [r5, #2820]	; 0xb04
d001b440:	44fb4427 	ldrbtmi	r4, [fp], #1063	; 0x427
d001b444:	459a683b 	ldrmi	r6, [sl, #2107]	; 0x83b
d001b448:	9b01d34c 	blls	0xd0090180
d001b44c:	8000f8c7 	andhi	pc, r0, r7, asr #17
d001b450:	9b00461a 	blls	0xd002ccc0
d001b454:	59a350a3 	stmibpl	r3!, {r0, r1, r5, r7, ip, lr}
d001b458:	51a33b01 			; <UNDEFINED> instruction: 0x51a33b01
d001b45c:	2700e68e 	strcs	lr, [r0, -lr, lsl #13]
d001b460:	441ce78d 	ldrmi	lr, [ip], #-1933	; 0xfffff873
d001b464:	23011c5a 	movwcs	r1, #7258	; 0x1c5a
d001b468:	14a5f504 	strtne	pc, [r5], #1284	; 0x504
d001b46c:	2250f8ca 	subscs	pc, r0, #13238272	; 0xca0000
d001b470:	3254f884 	subscc	pc, r4, #132, 16	; 0x840000
d001b474:	fe5af7ff 	mrc2	7, 2, pc, cr10, cr15, {7}
d001b478:	3250f8da 	subscc	pc, r0, #14286848	; 0xda0000
d001b47c:	f8ca3b01 			; <UNDEFINED> instruction: 0xf8ca3b01
d001b480:	e7b93250 	sbfx	r3, r0, #4, #26
d001b484:	0014923c 	andseq	r9, r4, ip, lsr r2
d001b488:	00149234 	andseq	r9, r4, r4, lsr r2
d001b48c:	00149248 	andseq	r9, r4, r8, asr #4
d001b490:	0014924c 	andseq	r9, r4, ip, asr #4
d001b494:	0000b2d2 	ldrdeq	fp, [r0], -r2
d001b498:	ffffafc4 			; <UNDEFINED> instruction: 0xffffafc4
d001b49c:	0000b286 	andeq	fp, r0, r6, lsl #5
d001b4a0:	fffffc09 			; <UNDEFINED> instruction: 0xfffffc09
d001b4a4:	0000b1ec 	andeq	fp, r0, ip, ror #3
d001b4a8:	fffffbe5 			; <UNDEFINED> instruction: 0xfffffbe5
d001b4ac:	0000b1a8 	andeq	fp, r0, r8, lsr #3
d001b4b0:	0000b19a 	muleq	r0, sl, r1
d001b4b4:	fffffb46 			; <UNDEFINED> instruction: 0xfffffb46
d001b4b8:	fffffb21 			; <UNDEFINED> instruction: 0xfffffb21
d001b4bc:	0000b0b2 	strheq	fp, [r0], -r2
d001b4c0:	0000b0aa 	andeq	fp, r0, sl, lsr #1
d001b4c4:	0000b080 	andeq	fp, r0, r0, lsl #1
d001b4c8:	fffffb0e 			; <UNDEFINED> instruction: 0xfffffb0e
d001b4cc:	0000b056 	andeq	fp, r0, r6, asr r0
d001b4d0:	fffffb05 			; <UNDEFINED> instruction: 0xfffffb05
d001b4d4:	fffffa43 			; <UNDEFINED> instruction: 0xfffffa43
d001b4d8:	0000b00a 	andeq	fp, r0, sl
d001b4dc:	0000afd2 	ldrdeq	sl, [r0], -r2
d001b4e0:	0000afc2 	andeq	sl, r0, r2, asr #31
d001b4e4:	6829792b 	stmdavs	r9!, {r0, r1, r3, r5, r8, fp, ip, sp, lr}
d001b4e8:	f504b163 			; <UNDEFINED> instruction: 0xf504b163
d001b4ec:	f8d3338f 			; <UNDEFINED> instruction: 0xf8d3338f
d001b4f0:	230021b8 	movwcs	r2, #440	; 0x1b8
d001b4f4:	0058f8db 	ldrsbeq	pc, [r8], #-139	; 0xffffff75	; <UNPREDICTABLE>
d001b4f8:	0a01f10a 	beq	0xd0097928
d001b4fc:	f7fa3508 			; <UNDEFINED> instruction: 0xf7fa3508
d001b500:	e79ffdff 			; <UNDEFINED> instruction: 0xe79ffdff
d001b504:	e7f4464a 	ldrb	r4, [r4, sl, asr #12]!
d001b508:	718af44f 	orrvc	pc, sl, pc, asr #8
d001b50c:	f7f74620 			; <UNDEFINED> instruction: 0xf7f74620
d001b510:	4606fc96 			; <UNDEFINED> instruction: 0x4606fc96
d001b514:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d001b518:	f504821f 			; <UNDEFINED> instruction: 0xf504821f
d001b51c:	f8d313a5 			; <UNDEFINED> instruction: 0xf8d313a5
d001b520:	2b403250 	blcs	0xd1027e68
d001b524:	49bdd102 	ldmibmi	sp!, {r1, r8, ip, lr, pc}
d001b528:	e6134479 			; <UNDEFINED> instruction: 0xe6134479
d001b52c:	f8544bb7 			; <UNDEFINED> instruction: 0xf8544bb7
d001b530:	930bb003 	movwls	fp, #45059	; 0xb003
d001b534:	7f80f5bb 	svcvc	0x0080f5bb
d001b538:	49b9d102 	ldmibmi	r9!, {r1, r8, ip, lr, pc}
d001b53c:	e6094479 			; <UNDEFINED> instruction: 0xe6094479
d001b540:	58e24bb3 	stmiapl	r2!, {r0, r1, r4, r5, r7, r8, r9, fp, lr}^
d001b544:	2a409301 	bcs	0xd1040150
d001b548:	d10c9202 	tstle	ip, r2, lsl #4
d001b54c:	48b649b5 	ldmmi	r6!, {r0, r2, r4, r5, r7, r8, fp, lr}
d001b550:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d001b554:	fe28f7f4 	mcr2	7, 1, pc, cr8, cr4, {7}	; <UNPREDICTABLE>
d001b558:	4bb49a01 	blmi	0xced41d64
d001b55c:	9a024611 	bls	0xd00acda8
d001b560:	505a447b 	subspl	r4, sl, fp, ror r4
d001b564:	4cb2e60a 	ldcmi	6, cr14, [r2], #40	; 0x28
d001b568:	4ab22128 	bmi	0xceca3a10
d001b56c:	447a447c 	ldrbtmi	r4, [sl], #-1148	; 0xfffffb84
d001b570:	13a5f504 			; <UNDEFINED> instruction: 0x13a5f504
d001b574:	f8d34620 			; <UNDEFINED> instruction: 0xf8d34620
d001b578:	93033294 	movwls	r3, #12948	; 0x3294
d001b57c:	fc6df7f7 	stc2l	7, cr15, [sp], #-988	; 0xfffffc24
d001b580:	d0e92800 	rscle	r2, r9, r0, lsl #16
d001b584:	46202201 	strtmi	r2, [r0], -r1, lsl #4
d001b588:	f7fa4611 			; <UNDEFINED> instruction: 0xf7fa4611
d001b58c:	4aaafecf 	bmi	0xceadb0d0
d001b590:	46202129 	strtmi	r2, [r0], -r9, lsr #2
d001b594:	f7f7447a 			; <UNDEFINED> instruction: 0xf7f7447a
d001b598:	2800fc60 	stmdacs	r0, {r5, r6, sl, fp, ip, sp, lr, pc}
d001b59c:	4aa7d0dc 	bmi	0xcea0f914
d001b5a0:	4620217b 			; <UNDEFINED> instruction: 0x4620217b
d001b5a4:	f7f7447a 			; <UNDEFINED> instruction: 0xf7f7447a
d001b5a8:	2800fc58 	stmdacs	r0, {r3, r4, r6, sl, fp, ip, sp, lr, pc}
d001b5ac:	9b01d0d4 	blls	0xd008f904
d001b5b0:	0a00f04f 	beq	0xd00576f4
d001b5b4:	f8549a01 			; <UNDEFINED> instruction: 0xf8549a01
d001b5b8:	4d969003 	ldcmi	0, cr9, [r6, #12]
d001b5bc:	0301f109 	movweq	pc, #4361	; 0x1109	; <UNPREDICTABLE>
d001b5c0:	4a9550a3 	bmi	0xce56f854
d001b5c4:	428b58a1 	addmi	r5, fp, #10551296	; 0xa10000
d001b5c8:	0100f04f 	tsteq	r0, pc, asr #32	; <UNPREDICTABLE>
d001b5cc:	50a3bf88 	adcpl	fp, r3, r8, lsl #31
d001b5d0:	4c9b2230 	lfmmi	f2, 4, [fp], {48}	; 0x30
d001b5d4:	fb02447c 	blx	0xd00ac7ce
d001b5d8:	5d674609 	stclpl	6, cr4, [r7, #-36]!	; 0xffffffdc
d001b5dc:	16a4f506 	strtne	pc, [r4], r6, lsl #10
d001b5e0:	6034f206 	eorsvs	pc, r4, r6, lsl #4
d001b5e4:	f964f004 			; <UNDEFINED> instruction: 0xf964f004
d001b5e8:	2200230b 	andcs	r2, r0, #738197504	; 0x2c000000
d001b5ec:	f8864649 			; <UNDEFINED> instruction: 0xf8864649
d001b5f0:	46203655 			; <UNDEFINED> instruction: 0x46203655
d001b5f4:	7654f886 	ldrbvc	pc, [r4], -r6, lsl #17	; <UNPREDICTABLE>
d001b5f8:	fbe1f7f9 	blx	0xcf8995e6
d001b5fc:	ff84f7f9 			; <UNDEFINED> instruction: 0xff84f7f9
d001b600:	f5045963 			; <UNDEFINED> instruction: 0xf5045963
d001b604:	950a12a5 	strls	r1, [sl, #-677]	; 0xfffffd5b
d001b608:	ee083301 	cdp	3, 0, cr3, cr8, cr1, {0}
d001b60c:	f8cd0a10 			; <UNDEFINED> instruction: 0xf8cd0a10
d001b610:	5163a000 	cmnpl	r3, r0
d001b614:	3250f8d2 	subscc	pc, r0, #13762560	; 0xd20000
d001b618:	1c594d8a 	mrrcne	13, 8, r4, r9, cr10
d001b61c:	447d4423 	ldrbtmi	r4, [sp], #-1059	; 0xfffffbdd
d001b620:	13a5f503 			; <UNDEFINED> instruction: 0x13a5f503
d001b624:	1250f8c2 	subsne	pc, r0, #12713984	; 0xc20000
d001b628:	f8832202 			; <UNDEFINED> instruction: 0xf8832202
d001b62c:	4b772254 	blmi	0xd1de3f84
d001b630:	930d18eb 	movwls	r1, #55531	; 0xd8eb
d001b634:	bb1b6da3 	bllt	0xd06f6cc8
d001b638:	2b7d6ae3 	blcs	0xd1f761cc
d001b63c:	f5b3d020 			; <UNDEFINED> instruction: 0xf5b3d020
d001b640:	d01d7f80 	andsle	r7, sp, r0, lsl #31
d001b644:	1215f240 	andsne	pc, r5, #64, 4
d001b648:	f0404293 			; <UNDEFINED> instruction: 0xf0404293
d001b64c:	46208128 	strtmi	r8, [r0], -r8, lsr #2
d001b650:	fbdaf7f7 	blx	0xcf6d9636
d001b654:	212d6a63 			; <UNDEFINED> instruction: 0x212d6a63
d001b658:	93044620 	movwls	r4, #17952	; 0x4620
d001b65c:	f8946aa3 			; <UNDEFINED> instruction: 0xf8946aa3
d001b660:	93058030 	movwls	r8, #20528	; 0x5030
d001b664:	93066b63 	movwls	r6, #27491	; 0x6b63
d001b668:	fbe9f7f7 	blx	0xcfa9964e
d001b66c:	f5a36ae3 			; <UNDEFINED> instruction: 0xf5a36ae3
d001b670:	2b017381 	blcs	0xd007847c
d001b674:	4974d971 	ldmdbmi	r4!, {r0, r4, r5, r6, r8, fp, ip, lr, pc}^
d001b678:	44794620 	ldrbtmi	r4, [r9], #-1568	; 0xfffff9e0
d001b67c:	fd94f7f4 	ldc2	7, cr15, [r4, #976]	; 0x3d0
d001b680:	217d4c72 	cmncs	sp, r2, ror ip
d001b684:	f50b4a72 			; <UNDEFINED> instruction: 0xf50b4a72
d001b688:	447c3525 	ldrbtmi	r3, [ip], #-1317	; 0xfffffadb
d001b68c:	817cf8df 	ldrsbhi	pc, [ip, #-143]!	; 0xffffff71	; <UNPREDICTABLE>
d001b690:	f205447a 	vqshl.s8	q2, q13, <illegal reg q2.5>
d001b694:	46201553 			; <UNDEFINED> instruction: 0x46201553
d001b698:	f7f7465f 			; <UNDEFINED> instruction: 0xf7f7465f
d001b69c:	f504fbde 			; <UNDEFINED> instruction: 0xf504fbde
d001b6a0:	462012a5 	strtmi	r1, [r0], -r5, lsr #5
d001b6a4:	05c5eb04 	strbeq	lr, [r5, #2820]	; 0xb04
d001b6a8:	3250f8d2 	subscc	pc, r0, #13762560	; 0xd20000
d001b6ac:	3b0144a0 	blcc	0xd006c934
d001b6b0:	3250f8c2 	subscc	pc, r0, #12713984	; 0xc20000
d001b6b4:	9a0a9b0a 	bls	0xd02c22e4
d001b6b8:	3b0158e3 	blcc	0xd0071a4c
d001b6bc:	f7f950a3 			; <UNDEFINED> instruction: 0xf7f950a3
d001b6c0:	f504ff23 			; <UNDEFINED> instruction: 0xf504ff23
d001b6c4:	4606328f 	strmi	r3, [r6], -pc, lsl #5
d001b6c8:	ee182300 	cdp	3, 1, cr2, cr8, cr0, {0}
d001b6cc:	f8d21a10 			; <UNDEFINED> instruction: 0xf8d21a10
d001b6d0:	6da021b8 	stfvss	f2, [r0, #736]!	; 0x2e0
d001b6d4:	fd14f7fa 	ldc2	7, cr15, [r4, #-1000]	; 0xfffffc18
d001b6d8:	3000f8d8 	ldrdcc	pc, [r0], -r8
d001b6dc:	429f3508 	addsmi	r3, pc, #8, 10	; 0x2000000
d001b6e0:	810ff0c0 	smlabthi	pc, r0, r0, pc	; <UNPREDICTABLE>
d001b6e4:	46209b00 	strtmi	r9, [r0], -r0, lsl #22
d001b6e8:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d001b6ec:	f7f98128 			; <UNDEFINED> instruction: 0xf7f98128
d001b6f0:	4601ff0b 	strmi	pc, [r1], -fp, lsl #30
d001b6f4:	24006da0 	strcs	r6, [r0], #-3488	; 0xfffff260
d001b6f8:	9a002300 	bls	0xd0024300
d001b6fc:	fd00f7fa 	stc2	7, cr15, [r0, #-1000]	; 0xfffffc18
d001b700:	46314d54 			; <UNDEFINED> instruction: 0x46314d54
d001b704:	f505447d 			; <UNDEFINED> instruction: 0xf505447d
d001b708:	6da8338f 	stcvs	3, cr3, [r8, #572]!	; 0x23c
d001b70c:	81b8f8d3 			; <UNDEFINED> instruction: 0x81b8f8d3
d001b710:	46422300 	strbmi	r2, [r2], -r0, lsl #6
d001b714:	fcf4f7fa 	ldc2l	7, cr15, [r4], #1000	; 0x3e8
d001b718:	2300b12c 	movwcs	fp, #300	; 0x12c
d001b71c:	46214642 	strtmi	r4, [r1], -r2, asr #12
d001b720:	f7fa6da8 			; <UNDEFINED> instruction: 0xf7fa6da8
d001b724:	4c4cfced 	mcrrmi	12, 14, pc, ip, cr13	; <UNPREDICTABLE>
d001b728:	447c9d03 	ldrbtmi	r9, [ip], #-3331	; 0xfffff2fd
d001b72c:	17a5f504 	strne	pc, [r5, r4, lsl #10]!
d001b730:	7626f507 	strtvc	pc, [r6], -r7, lsl #10
d001b734:	2294f8d7 	addscs	pc, r4, #14090240	; 0xd70000
d001b738:	f0c04295 			; <UNDEFINED> instruction: 0xf0c04295
d001b73c:	9a038104 	bls	0xd00fbb54
d001b740:	f8c79b0b 			; <UNDEFINED> instruction: 0xf8c79b0b
d001b744:	f8442294 			; <UNDEFINED> instruction: 0xf8442294
d001b748:	f1bab003 			; <UNDEFINED> instruction: 0xf1bab003
d001b74c:	f47f0f00 			; <UNDEFINED> instruction: 0xf47f0f00
d001b750:	4942af03 	stmdbmi	r2, {r0, r1, r8, r9, sl, fp, sp, pc}^
d001b754:	44794620 	ldrbtmi	r4, [r9], #-1568	; 0xfffff9e0
d001b758:	6a26e6fc 	bvs	0xd09d5350
d001b75c:	4276b100 	rsbsmi	fp, r6, #0, 2
d001b760:	f7f74628 			; <UNDEFINED> instruction: 0xf7f74628
d001b764:	4a3efb51 	bmi	0xd0fda4b0
d001b768:	4628213a 			; <UNDEFINED> instruction: 0x4628213a
d001b76c:	f7f7447a 			; <UNDEFINED> instruction: 0xf7f7447a
d001b770:	2800fb74 	stmdacs	r0, {r2, r4, r5, r6, r8, r9, fp, ip, sp, lr, pc}
d001b774:	9b0dd084 	blls	0xd038f98c
d001b778:	4f3a4659 	svcmi	0x003a4659
d001b77c:	0c00f04f 	stceq	0, cr15, [r0], {79}	; 0x4f
d001b780:	447f681b 	ldrbtmi	r6, [pc], #-2075	; 0xd001b788
d001b784:	e064f8d5 	ldrd	pc, [r4], #-133	; 0xffffff7b	; <UNPREDICTABLE>
d001b788:	0216e9d5 	andseq	lr, r6, #3489792	; 0x354000
d001b78c:	9209970c 	andls	r9, r9, #12, 14	; 0x300000
d001b790:	92086e2a 	andls	r6, r8, #672	; 0x2a0
d001b794:	92076eaa 	andls	r6, r7, #2720	; 0xaa0
d001b798:	447a4a33 	ldrbtmi	r4, [sl], #-2611	; 0xfffff5cd
d001b79c:	12a5f502 	adcne	pc, r5, #8388608	; 0x800000
d001b7a0:	229cf602 	addscs	pc, ip, #2097152	; 0x200000
d001b7a4:	d3204299 			; <UNDEFINED> instruction: 0xd3204299
d001b7a8:	0f00f1bc 	svceq	0x0000f1bc
d001b7ac:	4a2fd009 	bmi	0xd0c0f7d8
d001b7b0:	447a9909 	ldrbtmi	r9, [sl], #-2313	; 0xfffff6f7
d001b7b4:	990865d1 	stmdbls	r8, {r0, r4, r6, r7, r8, sl, sp, lr}
d001b7b8:	e9c26590 	stmib	r2, {r4, r7, r8, sl, sp, lr}^
d001b7bc:	99071e18 	stmdbls	r7, {r3, r4, r9, sl, fp, ip}
d001b7c0:	f5b36691 			; <UNDEFINED> instruction: 0xf5b36691
d001b7c4:	d1577f80 	cmple	r7, r0, lsl #31
d001b7c8:	447b4b29 	ldrbtmi	r4, [fp], #-2857	; 0xfffff4d7
d001b7cc:	b94a6d9a 	stmdblt	sl, {r1, r3, r4, r7, r8, sl, fp, sp, lr}^
d001b7d0:	447a4a28 	ldrbtmi	r4, [sl], #-2600	; 0xfffff5d8
d001b7d4:	9a04659a 	bls	0xd0134e44
d001b7d8:	9a0565da 	bls	0xd0174f48
d001b7dc:	2818e9c3 	ldmdacs	r8, {r0, r1, r6, r7, r8, fp, sp, lr, pc}
d001b7e0:	669a9a06 	ldrvs	r9, [sl], r6, lsl #20
d001b7e4:	0a01f10a 	beq	0xd0097c14
d001b7e8:	f852e724 			; <UNDEFINED> instruction: 0xf852e724
d001b7ec:	42b77031 	adcsmi	r7, r7, #49	; 0x31
d001b7f0:	b948d10a 	stmdblt	r8, {r1, r3, r8, ip, lr, pc}^
d001b7f4:	46c69806 	strbmi	r9, [r6], r6, lsl #16
d001b7f8:	0c01f04f 	stceq	0, cr15, [r1], {79}	; 0x4f
d001b7fc:	98059007 	stmdals	r5, {r0, r1, r2, ip, pc}
d001b800:	98049008 	stmdals	r4, {r3, ip, pc}
d001b804:	980c9009 	stmdals	ip, {r0, r3, ip, pc}
d001b808:	e7cb3101 	strb	r3, [fp, r1, lsl #2]
d001b80c:	0014b298 	mulseq	r4, r8, r2
d001b810:	00149234 	andseq	r9, r4, r4, lsr r2
d001b814:	0014923c 	andseq	r9, r4, ip, lsr r2
d001b818:	00149238 	andseq	r9, r4, r8, lsr r2
d001b81c:	fffff90d 			; <UNDEFINED> instruction: 0xfffff90d
d001b820:	fffff995 			; <UNDEFINED> instruction: 0xfffff995
d001b824:	fffff99d 			; <UNDEFINED> instruction: 0xfffff99d
d001b828:	0000aeb2 			; <UNDEFINED> instruction: 0x0000aeb2
d001b82c:	0000aea4 	andeq	sl, r0, r4, lsr #29
d001b830:	0000ae98 	muleq	r0, r8, lr
d001b834:	fffff9ad 			; <UNDEFINED> instruction: 0xfffff9ad
d001b838:	fffff9a1 			; <UNDEFINED> instruction: 0xfffff9a1
d001b83c:	fffff9b6 			; <UNDEFINED> instruction: 0xfffff9b6
d001b840:	0000ae30 	andeq	sl, r0, r0, lsr lr
d001b844:	0000ade6 	andeq	sl, r0, r6, ror #27
d001b848:	fffff904 			; <UNDEFINED> instruction: 0xfffff904
d001b84c:	0000ad7a 	andeq	sl, r0, sl, ror sp
d001b850:	fffff96b 			; <UNDEFINED> instruction: 0xfffff96b
d001b854:	0000ad00 	andeq	sl, r0, r0, lsl #26
d001b858:	0000acda 	ldrdeq	sl, [r0], -sl	; <UNPREDICTABLE>
d001b85c:	fffff8c4 			; <UNDEFINED> instruction: 0xfffff8c4
d001b860:	fffff837 			; <UNDEFINED> instruction: 0xfffff837
d001b864:	fffff64a 			; <UNDEFINED> instruction: 0xfffff64a
d001b868:	0000ac6a 	andeq	sl, r0, sl, ror #24
d001b86c:	0000ac52 	andeq	sl, r0, r2, asr ip
d001b870:	0000ac3a 	andeq	sl, r0, sl, lsr ip
d001b874:	fffff6ff 			; <UNDEFINED> instruction: 0xfffff6ff
d001b878:	1c5849b3 	mrrcne	9, 11, r4, r8, cr3	; <UNPREDICTABLE>
d001b87c:	f5034aaf 			; <UNDEFINED> instruction: 0xf5034aaf
d001b880:	44793325 	ldrbtmi	r3, [r9], #-805	; 0xfffffcdb
d001b884:	1353f203 	cmpne	r3, #805306368	; 0x30000000	; <UNPREDICTABLE>
d001b888:	f5015050 			; <UNDEFINED> instruction: 0xf5015050
d001b88c:	f8d2328f 			; <UNDEFINED> instruction: 0xf8d2328f
d001b890:	f84121b8 			; <UNDEFINED> instruction: 0xf84121b8
d001b894:	eb012033 	bl	0xd0063968
d001b898:	605e03c3 	subsvs	r0, lr, r3, asr #7
d001b89c:	f44fe7a2 	vst1.32	{d30}, [pc :128], r2
d001b8a0:	4620718b 	strtmi	r7, [r0], -fp, lsl #3
d001b8a4:	facbf7f7 	blx	0xcf319888
d001b8a8:	6a63b318 	bvs	0xd1908510
d001b8ac:	4aa7213a 	bmi	0xce9e3d9c
d001b8b0:	461f4620 	ldrmi	r4, [pc], -r0, lsr #12
d001b8b4:	447a6aa3 	ldrbtmi	r6, [sl], #-2723	; 0xfffff55d
d001b8b8:	8030f894 	mlashi	r0, r4, r8, pc	; <UNPREDICTABLE>
d001b8bc:	93046b66 	movwls	r6, #19302	; 0x4b66
d001b8c0:	facbf7f7 	blx	0xcf3198a4
d001b8c4:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001b8c8:	9b00aedb 	blls	0xd004743c
d001b8cc:	6da3b15b 	stfvsd	f3, [r3, #364]!	; 0x16c
d001b8d0:	d1872b00 	orrle	r2, r7, r0, lsl #22
d001b8d4:	65e74b9e 	strbvs	r4, [r7, #2974]!	; 0xb9e
d001b8d8:	66a6447b 	sxtabvs	r4, r6, fp, ror #8
d001b8dc:	9b0465a3 	blls	0xd0134f70
d001b8e0:	3818e9c4 	ldmdacc	r8, {r2, r6, r7, r8, fp, sp, lr, pc}
d001b8e4:	f504e77e 			; <UNDEFINED> instruction: 0xf504e77e
d001b8e8:	f8d3338f 			; <UNDEFINED> instruction: 0xf8d3338f
d001b8ec:	930031b8 	movwls	r3, #440	; 0x1b8
d001b8f0:	f7fee778 			; <UNDEFINED> instruction: 0xf7fee778
d001b8f4:	2800fe97 	stmdacs	r0, {r0, r1, r2, r4, r7, r9, sl, fp, ip, sp, lr, pc}
d001b8f8:	ae9cf47f 	mrcge	4, 4, APSR_nzcv, cr12, cr15, {3}
d001b8fc:	fc16f7ff 	ldc2	7, cr15, [r6], {255}	; 0xff
d001b900:	4620e698 			; <UNDEFINED> instruction: 0x4620e698
d001b904:	46492200 	strbmi	r2, [r9], -r0, lsl #4
d001b908:	f7f93701 			; <UNDEFINED> instruction: 0xf7f93701
d001b90c:	f855fa3f 			; <UNDEFINED> instruction: 0xf855fa3f
d001b910:	21012c04 	tstcs	r1, r4, lsl #24
d001b914:	f9c2f7f9 			; <UNDEFINED> instruction: 0xf9c2f7f9
d001b918:	f2444620 	vmax.s8	d20, d4, d16
d001b91c:	f7f92188 			; <UNDEFINED> instruction: 0xf7f92188
d001b920:	f24df99d 	vmul.i8	d31, d29, d13
d001b924:	f7f91101 			; <UNDEFINED> instruction: 0xf7f91101
d001b928:	f7f9f999 			; <UNDEFINED> instruction: 0xf7f9f999
d001b92c:	2300fded 	movwcs	pc, #3565	; 0xded	; <UNPREDICTABLE>
d001b930:	f8554601 			; <UNDEFINED> instruction: 0xf8554601
d001b934:	6da02c08 	stcvs	12, cr2, [r0, #32]!
d001b938:	fbe2f7fa 	blx	0xcf8d992a
d001b93c:	f7f9e6cc 			; <UNDEFINED> instruction: 0xf7f9e6cc
d001b940:	4604fde3 	strmi	pc, [r4], -r3, ror #27
d001b944:	f856e6dc 			; <UNDEFINED> instruction: 0xf856e6dc
d001b948:	23001025 	movwcs	r1, #37	; 0x25
d001b94c:	6da04642 	stcvs	6, cr4, [r0, #264]!	; 0x108
d001b950:	f7fa3501 			; <UNDEFINED> instruction: 0xf7fa3501
d001b954:	e6edfbd5 	usat	pc, #13, r5, asr #23	; <UNPREDICTABLE>
d001b958:	f46f6ae5 	vld1.64	{d22-d23}, [pc :128], r5
d001b95c:	18ab7288 	stmiane	fp!, {r3, r7, r9, ip, sp, lr}
d001b960:	d8622b01 	stmdale	r2!, {r0, r8, r9, fp, sp}^
d001b964:	1311f240 	tstne	r1, #64, 4	; <UNPREDICTABLE>
d001b968:	d00c429d 	mulle	ip, sp, r2
d001b96c:	58e34b74 	stmiapl	r3!, {r2, r4, r5, r6, r8, r9, fp, lr}^
d001b970:	4878b19b 	ldmdami	r8!, {r0, r1, r3, r4, r7, r8, ip, sp, pc}^
d001b974:	44784b73 	ldrbtmi	r4, [r8], #-2931	; 0xfffff48d
d001b978:	f5b358c3 			; <UNDEFINED> instruction: 0xf5b358c3
d001b97c:	d1237f00 			; <UNDEFINED> instruction: 0xd1237f00
d001b980:	44794975 	ldrbtmi	r4, [r9], #-2421	; 0xfffff68b
d001b984:	f504e449 			; <UNDEFINED> instruction: 0xf504e449
d001b988:	f8d414a5 			; <UNDEFINED> instruction: 0xf8d414a5
d001b98c:	b93b3250 	ldmdblt	fp!, {r4, r6, r9, ip, sp}
d001b990:	44794972 	ldrbtmi	r4, [r9], #-2418	; 0xfffff68e
d001b994:	44784872 	ldrbtmi	r4, [r8], #-2162	; 0xfffff78e
d001b998:	4972e43f 	ldmdbmi	r2!, {r0, r1, r2, r3, r4, r5, sl, sp, lr, pc}^
d001b99c:	e7f94479 			; <UNDEFINED> instruction: 0xe7f94479
d001b9a0:	44784871 	ldrbtmi	r4, [r8], #-2161	; 0xfffff78f
d001b9a4:	f5034403 			; <UNDEFINED> instruction: 0xf5034403
d001b9a8:	f89313a5 			; <UNDEFINED> instruction: 0xf89313a5
d001b9ac:	2b023253 	blcs	0xd00a8300
d001b9b0:	f500d1df 			; <UNDEFINED> instruction: 0xf500d1df
d001b9b4:	f8d313a5 			; <UNDEFINED> instruction: 0xf8d313a5
d001b9b8:	f5b33294 			; <UNDEFINED> instruction: 0xf5b33294
d001b9bc:	d1027f00 	tstle	r2, r0, lsl #30
d001b9c0:	4479496a 	ldrbtmi	r4, [r9], #-2410	; 0xfffff696
d001b9c4:	2601e429 	strcs	lr, [r1], -r9, lsr #8
d001b9c8:	447c4c69 	ldrbtmi	r4, [ip], #-3177	; 0xfffff397
d001b9cc:	f7f74620 			; <UNDEFINED> instruction: 0xf7f74620
d001b9d0:	4a68fa1b 	bmi	0xd1a5a244
d001b9d4:	4620213b 			; <UNDEFINED> instruction: 0x4620213b
d001b9d8:	f7f7447a 			; <UNDEFINED> instruction: 0xf7f7447a
d001b9dc:	4620fa3e 			; <UNDEFINED> instruction: 0x4620fa3e
d001b9e0:	fd92f7f9 	ldc2	7, cr15, [r2, #996]	; 0x3e4
d001b9e4:	f504b16e 			; <UNDEFINED> instruction: 0xf504b16e
d001b9e8:	f8d212a5 			; <UNDEFINED> instruction: 0xf8d212a5
d001b9ec:	1c593294 	lfmne	f3, 2, [r9], {148}	; 0x94
d001b9f0:	23a5f503 			; <UNDEFINED> instruction: 0x23a5f503
d001b9f4:	f8c233a6 			; <UNDEFINED> instruction: 0xf8c233a6
d001b9f8:	f8441294 			; <UNDEFINED> instruction: 0xf8441294
d001b9fc:	f7ff0023 			; <UNDEFINED> instruction: 0xf7ff0023
d001ba00:	4a50bbbd 	bmi	0xd144a8fc
d001ba04:	1c5958a3 	mrrcne	8, 10, r5, r9, cr3
d001ba08:	3324f503 	msrcc	CPSR_s, #12582912	; 0xc00000
d001ba0c:	234af203 	movtcs	pc, #41475	; 0xa203	; <UNPREDICTABLE>
d001ba10:	f84450a1 			; <UNDEFINED> instruction: 0xf84450a1
d001ba14:	eb040033 	bl	0xd011bae8
d001ba18:	f24004c3 	vshl.s8	q8, <illegal reg q1.5>, q8
d001ba1c:	1aeb1311 	bne	0xcfae0668
d001ba20:	415d425d 	cmpmi	sp, sp, asr r2
d001ba24:	f7ff7125 			; <UNDEFINED> instruction: 0xf7ff7125
d001ba28:	f240bba9 	vqdmulh.s<illegal width 8>	d27, d16, d25
d001ba2c:	4620110f 	strtmi	r1, [r0], -pc, lsl #2
d001ba30:	fa05f7f7 	blx	0xd0199a14
d001ba34:	d06f2800 	rsble	r2, pc, r0, lsl #16
d001ba38:	3630f897 			; <UNDEFINED> instruction: 0x3630f897
d001ba3c:	d11f2b04 	tstle	pc, r4, lsl #22
d001ba40:	447c4c4d 	ldrbtmi	r4, [ip], #-3149	; 0xfffff3b3
d001ba44:	15a4f504 	strne	pc, [r4, #1284]!	; 0x504
d001ba48:	f8954620 			; <UNDEFINED> instruction: 0xf8954620
d001ba4c:	f7fb1631 			; <UNDEFINED> instruction: 0xf7fb1631
d001ba50:	f895fe23 			; <UNDEFINED> instruction: 0xf895fe23
d001ba54:	22011632 	andcs	r1, r1, #52428800	; 0x3200000
d001ba58:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d001ba5c:	f895f997 			; <UNDEFINED> instruction: 0xf895f997
d001ba60:	f44f3631 	vst1.8	{d19-d21}, [pc :256], r1
d001ba64:	fb02721a 	blx	0xd00b82d6
d001ba68:	f5034303 			; <UNDEFINED> instruction: 0xf5034303
d001ba6c:	8d183368 	ldchi	3, cr3, [r8, #-416]	; 0xfffffe60
d001ba70:	faf4f7fa 	blx	0xcfd59a60
d001ba74:	6108f244 	tstvs	r8, r4, asr #4	; <UNPREDICTABLE>
d001ba78:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d001ba7c:	e009f8ef 	and	pc, r9, pc, ror #17
d001ba80:	d11a2b05 	tstle	sl, r5, lsl #22
d001ba84:	4478483d 	ldrbtmi	r4, [r8], #-2109	; 0xfffff7c3
d001ba88:	13a4f500 			; <UNDEFINED> instruction: 0x13a4f500
d001ba8c:	1631f893 			; <UNDEFINED> instruction: 0x1631f893
d001ba90:	fa6ef7fc 	blx	0xd1bd9a88
d001ba94:	213b4c3a 	teqcs	fp, sl, lsr ip
d001ba98:	447c4a3a 	ldrbtmi	r4, [ip], #-2618	; 0xfffff5c6
d001ba9c:	4620447a 			; <UNDEFINED> instruction: 0x4620447a
d001baa0:	f9dbf7f7 			; <UNDEFINED> instruction: 0xf9dbf7f7
d001baa4:	13a4f504 			; <UNDEFINED> instruction: 0x13a4f504
d001baa8:	562cf8d3 			; <UNDEFINED> instruction: 0x562cf8d3
d001baac:	6f80f5b5 	svcvs	0x0080f5b5
d001bab0:	4935d123 	ldmdbmi	r5!, {r0, r1, r5, r8, ip, lr, pc}
d001bab4:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d001bab8:	2b01bb4d 	blcs	0xd008a7f4
d001babc:	4c33d013 	ldcmi	0, cr13, [r3], #-76	; 0xffffffb4
d001bac0:	f04f2b03 			; <UNDEFINED> instruction: 0xf04f2b03
d001bac4:	447c0101 	ldrbtmi	r0, [ip], #-257	; 0xfffffeff
d001bac8:	2204bf0c 	andcs	fp, r4, #12, 30	; 0x30
d001bacc:	46202201 	strtmi	r2, [r0], -r1, lsl #4
d001bad0:	fc2cf7fa 	stc2	7, cr15, [ip], #-1000	; 0xfffffc18
d001bad4:	13a4f504 			; <UNDEFINED> instruction: 0x13a4f504
d001bad8:	3630f893 			; <UNDEFINED> instruction: 0x3630f893
d001badc:	d1d92b02 	bicsle	r2, r9, r2, lsl #22
d001bae0:	21c0f24b 	biccs	pc, r0, fp, asr #4
d001bae4:	482ae7c8 	stmdami	sl!, {r3, r6, r7, r8, r9, sl, sp, lr, pc}
d001bae8:	6ac34478 	bvs	0xcf0eccd0
d001baec:	d0d12b3b 	sbcsle	r2, r1, fp, lsr fp
d001baf0:	44794928 	ldrbtmi	r4, [r9], #-2344	; 0xfffff6d8
d001baf4:	fb58f7f4 	blx	0xd1659ace
d001baf8:	1c6ae7cc 	stclne	7, cr14, [sl], #-816	; 0xfffffcd0
d001bafc:	25a3f505 	strcs	pc, [r3, #1285]!	; 0x505
d001bb00:	f2054620 	vmax.s8	d4, d5, d16
d001bb04:	f8c3558a 			; <UNDEFINED> instruction: 0xf8c3558a
d001bb08:	f7f9262c 			; <UNDEFINED> instruction: 0xf7f9262c
d001bb0c:	eb04fcfd 	bl	0xd015af08
d001bb10:	60600485 	rsbvs	r0, r0, r5, lsl #9
d001bb14:	bb32f7ff 	bllt	0xd0cd9b18
d001bb18:	4620213b 			; <UNDEFINED> instruction: 0x4620213b
d001bb1c:	f98ff7f7 			; <UNDEFINED> instruction: 0xf98ff7f7
d001bb20:	f47f2800 			; <UNDEFINED> instruction: 0xf47f2800
d001bb24:	f7fdab2b 			; <UNDEFINED> instruction: 0xf7fdab2b
d001bb28:	4a1bff15 	bmi	0xd071b784
d001bb2c:	213b481b 	teqcs	fp, fp, lsl r8
d001bb30:	4478447a 	ldrbtmi	r4, [r8], #-1146	; 0xfffffb86
d001bb34:	f991f7f7 			; <UNDEFINED> instruction: 0xf991f7f7
d001bb38:	bb20f7ff 	bllt	0xd0859b3c
d001bb3c:	0014b298 	mulseq	r4, r8, r2
d001bb40:	00149248 	andseq	r9, r4, r8, asr #4
d001bb44:	0014924c 	andseq	r9, r4, ip, asr #4
d001bb48:	0000ab82 	andeq	sl, r0, r2, lsl #23
d001bb4c:	fffff70b 			; <UNDEFINED> instruction: 0xfffff70b
d001bb50:	fffff704 			; <UNDEFINED> instruction: 0xfffff704
d001bb54:	0000aa8e 	andeq	sl, r0, lr, lsl #21
d001bb58:	fffff6d9 			; <UNDEFINED> instruction: 0xfffff6d9
d001bb5c:	fffff46e 			; <UNDEFINED> instruction: 0xfffff46e
d001bb60:	0000aa6e 	andeq	sl, r0, lr, ror #20
d001bb64:	fffff44c 			; <UNDEFINED> instruction: 0xfffff44c
d001bb68:	0000aa62 	andeq	sl, r0, r2, ror #20
d001bb6c:	fffff682 			; <UNDEFINED> instruction: 0xfffff682
d001bb70:	0000aa3a 	andeq	sl, r0, sl, lsr sl
d001bb74:	fffff6a5 			; <UNDEFINED> instruction: 0xfffff6a5
d001bb78:	0000a9c2 	andeq	sl, r0, r2, asr #19
d001bb7c:	0000a97e 	andeq	sl, r0, lr, ror r9
d001bb80:	0000a96a 	andeq	sl, r0, sl, ror #18
d001bb84:	fffff632 			; <UNDEFINED> instruction: 0xfffff632
d001bb88:	fffff634 			; <UNDEFINED> instruction: 0xfffff634
d001bb8c:	0000a93e 	andeq	sl, r0, lr, lsr r9
d001bb90:	0000a91c 	andeq	sl, r0, ip, lsl r9
d001bb94:	fffff5b0 			; <UNDEFINED> instruction: 0xfffff5b0
d001bb98:	fffff5d9 			; <UNDEFINED> instruction: 0xfffff5d9
d001bb9c:	0000a8d2 	ldrdeq	sl, [r0], -r2

Disassembly of section .text.block.constprop.0:

d001bbc0 <.text.block.constprop.0>:
d001bbc0:	4c0db510 	cfstr32mi	mvfx11, [sp], {16}
d001bbc4:	6da3447c 	cfstrsvs	mvf4, [r3, #496]!	; 0x1f0
d001bbc8:	6ae3b92b 	bvs	0xcf90a07c
d001bbcc:	d0022b7d 	andle	r2, r2, sp, ror fp
d001bbd0:	7f80f5b3 	svcvc	0x0080f5b3
d001bbd4:	4a09d108 	bmi	0xd028fffc
d001bbd8:	4809217d 	stmdami	r9, {r0, r2, r3, r4, r5, r6, r8, sp}
d001bbdc:	4478447a 	ldrbtmi	r4, [r8], #-1146	; 0xfffffb86
d001bbe0:	4010e8bd 			; <UNDEFINED> instruction: 0x4010e8bd
d001bbe4:	b939f7f7 	ldmdblt	r9!, {r0, r1, r2, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}
d001bbe8:	fd1cf7fe 	ldc2	7, cr15, [ip, #-1016]	; 0xfffffc08
d001bbec:	d1ea2800 	mvnle	r2, r0, lsl #16
d001bbf0:	fa9cf7ff 	blx	0xce759bf4
d001bbf4:	bf00e7e7 	svclt	0x0000e7e7
d001bbf8:	0000a840 	andeq	sl, r0, r0, asr #16
d001bbfc:	ffffffc0 			; <UNDEFINED> instruction: 0xffffffc0
d001bc00:	0000a826 	andeq	sl, r0, r6, lsr #16

Disassembly of section .text.global_declaration.constprop.0:

d001bd84 <.text.global_declaration.constprop.0>:
d001bd84:	e92db084 	push	{r2, r7, ip, sp, pc}
d001bd88:	b08b4ff0 	strdlt	r4, [fp], r0
d001bd8c:	b35cf8df 	cmplt	ip, #14614528	; 0xdf0000	; <UNPREDICTABLE>
d001bd90:	44fbac14 	ldrbtmi	sl, [fp], #3092	; 0xc14
d001bd94:	f89d9004 			; <UNDEFINED> instruction: 0xf89d9004
d001bd98:	9f1d6070 	svcls	0x001d6070
d001bd9c:	000fe884 	andeq	lr, pc, r4, lsl #17
d001bda0:	46019a15 			; <UNDEFINED> instruction: 0x46019a15
d001bda4:	f8dd4658 			; <UNDEFINED> instruction: 0xf8dd4658
d001bda8:	9205a05c 	andls	sl, r5, #92	; 0x5c
d001bdac:	9060f8dd 	ldrdls	pc, [r0], #-141	; 0xffffff73	; <UNPREDICTABLE>
d001bdb0:	8068f89d 	mlshi	r8, sp, r8, pc	; <UNPREDICTABLE>
d001bdb4:	f7f49d1b 			; <UNDEFINED> instruction: 0xf7f49d1b
d001bdb8:	9a05fd31 	bls	0xd019b284
d001bdbc:	99044604 	stmdbls	r4, {r2, r9, sl, lr}
d001bdc0:	f7f44658 			; <UNDEFINED> instruction: 0xf7f44658
d001bdc4:	2800fce6 	stmdacs	r0, {r1, r2, r5, r6, r7, sl, fp, ip, sp, lr, pc}
d001bdc8:	9a059904 	bls	0xd01821e0
d001bdcc:	4bc8db0f 	blmi	0xcf252a10
d001bdd0:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d001bdd4:	4ac7b932 	bmi	0xcf20a2a4
d001bdd8:	447a669d 	ldrbtmi	r6, [sl], #-1693	; 0xfffff963
d001bddc:	9818e9c3 	ldmdals	r8, {r0, r1, r6, r7, r8, fp, sp, lr, pc}
d001bde0:	2a16e9c3 	bcs	0xd05d64f4
d001bde4:	e8bdb00b 	pop	{r0, r1, r3, ip, sp, pc}
d001bde8:	b0044ff0 	strdlt	r4, [r4], -r0
d001bdec:	46584770 			; <UNDEFINED> instruction: 0x46584770
d001bdf0:	91049205 	tstls	r4, r5, lsl #4
d001bdf4:	fca8f7f4 	stc2	7, cr15, [r8], #976	; 0x3d0
d001bdf8:	dae82800 	ble	0xcfa25e00
d001bdfc:	99042c00 	stmdbls	r4, {sl, fp, sp}
d001be00:	db089a05 	blle	0xd024261c
d001be04:	4bb82038 	blmi	0xcee23eec
d001be08:	b404fb00 	strlt	pc, [r4], #-2816	; 0xfffff500
d001be0c:	f89b5ce0 			; <UNDEFINED> instruction: 0xf89b5ce0
d001be10:	42983008 	addsmi	r3, r8, #8
d001be14:	4cb8d0db 	ldcmi	0, cr13, [r8], #876	; 0x36c
d001be18:	447c9205 	ldrbtmi	r9, [ip], #-517	; 0xfffffdfb
d001be1c:	46209104 	strtmi	r9, [r0], -r4, lsl #2
d001be20:	fd5bf7f4 	ldc2l	7, cr15, [fp, #-976]	; 0xfffffc30
d001be24:	9a059904 	bls	0xd018223c
d001be28:	d1d02800 	bicsle	r2, r0, r0, lsl #16
d001be2c:	f7f44620 			; <UNDEFINED> instruction: 0xf7f44620
d001be30:	2800fd36 	stmdacs	r0, {r1, r2, r4, r5, r8, sl, fp, ip, sp, lr, pc}
d001be34:	f504d1cb 			; <UNDEFINED> instruction: 0xf504d1cb
d001be38:	f8d33367 			; <UNDEFINED> instruction: 0xf8d33367
d001be3c:	2b8031c4 	blcs	0xce028554
d001be40:	6da3d10a 	stfvsd	f5, [r3, #40]!	; 0x28
d001be44:	d1cd2b00 	bicle	r2, sp, r0, lsl #22
d001be48:	447b4bac 	ldrbtmi	r4, [fp], #-2988	; 0xfffff454
d001be4c:	e9c466a5 	stmib	r4, {r0, r2, r5, r7, r9, sl, sp, lr}^
d001be50:	e9c43a16 	stmib	r4, {r1, r2, r4, r9, fp, ip, sp}^
d001be54:	e7c59818 	bfi	r9, r8, (invalid: 16:5)
d001be58:	4620215b 			; <UNDEFINED> instruction: 0x4620215b
d001be5c:	ffeff7f6 			; <UNDEFINED> instruction: 0xffeff7f6
d001be60:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d001be64:	b12f8085 	smlawblt	pc, r5, r0, r8	; <UNPREDICTABLE>
d001be68:	2b006da3 	blcs	0xd00374fc
d001be6c:	4ba4d1ba 	blmi	0xce95055c
d001be70:	e7eb447b 			; <UNDEFINED> instruction: 0xe7eb447b
d001be74:	d0062e05 	andle	r2, r6, r5, lsl #28
d001be78:	6da3b12e 	stfvsd	f3, [r3, #184]!	; 0xb8
d001be7c:	d1b12b00 			; <UNDEFINED> instruction: 0xd1b12b00
d001be80:	447b4ba0 	ldrbtmi	r4, [fp], #-2976	; 0xfffff460
d001be84:	4ba0e7e2 	blmi	0xce855e14
d001be88:	6ad8447b 	bvs	0xcf62d07c
d001be8c:	c024f8d3 	ldrdgt	pc, [r4], -r3	; <UNPREDICTABLE>
d001be90:	7081f5a0 	addvc	pc, r1, r0, lsr #11
d001be94:	f8936a9c 			; <UNDEFINED> instruction: 0xf8936a9c
d001be98:	28011030 	stmdacs	r1, {r4, r5, ip}
d001be9c:	d8016b5a 	stmdale	r1, {r1, r3, r4, r6, r8, r9, fp, sp, lr}
d001bea0:	b9606a18 	stmdblt	r0!, {r3, r4, r9, fp, sp, lr}^
d001bea4:	447b4b99 	ldrbtmi	r4, [fp], #-2969	; 0xfffff467
d001bea8:	28006d98 	stmdacs	r0, {r3, r4, r7, r8, sl, fp, sp, lr}
d001beac:	4898d19a 	ldmmi	r8, {r1, r3, r4, r7, r8, ip, lr, pc}
d001beb0:	669a4478 			; <UNDEFINED> instruction: 0x669a4478
d001beb4:	0c16e9c3 			; <UNDEFINED> instruction: 0x0c16e9c3
d001beb8:	4118e9c3 	tstmi	r8, r3, asr #19
d001bebc:	b946e792 	stmdblt	r6, {r1, r4, r7, r8, r9, sl, sp, lr, pc}^
d001bec0:	2f80f5b0 	svccs	0x0080f5b0
d001bec4:	6d98d921 	vldrvs.16	s26, [r8, #66]	; 0x42	; <UNPREDICTABLE>
d001bec8:	d18b2800 	orrle	r2, fp, r0, lsl #16
d001becc:	44784891 	ldrbtmi	r4, [r8], #-2193	; 0xfffff76f
d001bed0:	2501e7ef 	strcs	lr, [r1, #-2031]	; 0xfffff811
d001bed4:	447b4b90 	ldrbtmi	r4, [fp], #-2960	; 0xfffff470
d001bed8:	337ff503 	cmncc	pc, #12582912	; 0xc00000	; <UNPREDICTABLE>
d001bedc:	321cf8d3 	andscc	pc, ip, #13828096	; 0xd30000
d001bee0:	3303b916 	movwcc	fp, #14614	; 0x3916
d001bee4:	0303f023 	movweq	pc, #12323	; 0x3023	; <UNPREDICTABLE>
d001bee8:	1f80f5b3 	svcne	0x0080f5b3
d001beec:	4345d804 	movtmi	sp, #22532	; 0x5804
d001bef0:	1380f5c3 	orrne	pc, r0, #817889280	; 0x30c00000
d001bef4:	d90a429d 	stmdble	sl, {r0, r2, r3, r4, r7, r9, lr}
d001bef8:	447b4b88 	ldrbtmi	r4, [fp], #-2952	; 0xfffff478
d001befc:	28006d98 	stmdacs	r0, {r3, r4, r7, r8, sl, fp, sp, lr}
d001bf00:	af70f47f 	svcge	0x0070f47f
d001bf04:	44784886 	ldrbtmi	r4, [r8], #-2182	; 0xfffff77a
d001bf08:	2504e7d3 	strcs	lr, [r4, #-2003]	; 0xfffff82d
d001bf0c:	4885e7e2 	stmmi	r5, {r1, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d001bf10:	90044478 	andls	r4, r4, r8, ror r4
d001bf14:	ff78f7f6 			; <UNDEFINED> instruction: 0xff78f7f6
d001bf18:	215d4a83 	cmpcs	sp, r3, lsl #21
d001bf1c:	447a9804 	ldrbtmi	r9, [sl], #-2052	; 0xfffff7fc
d001bf20:	ff9bf7f6 			; <UNDEFINED> instruction: 0xff9bf7f6
d001bf24:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001bf28:	bb26af5d 	bllt	0xd09c7ca4
d001bf2c:	0a95ea4f 	beq	0xce596870
d001bf30:	f8df2608 			; <UNDEFINED> instruction: 0xf8df2608
d001bf34:	213d81f8 	teqcs	sp, r8	; <illegal shifter operand>
d001bf38:	f50844f8 			; <UNDEFINED> instruction: 0xf50844f8
d001bf3c:	4640199f 			; <UNDEFINED> instruction: 0x4640199f
d001bf40:	59f1f509 	ldmibpl	r1!, {r0, r3, r8, sl, ip, sp, lr, pc}^
d001bf44:	3000f8d9 	ldrdcc	pc, [r0], -r9
d001bf48:	f7f69304 			; <UNDEFINED> instruction: 0xf7f69304
d001bf4c:	2800ff78 	stmdacs	r0, {r3, r4, r5, r6, r8, r9, sl, fp, ip, sp, lr, pc}
d001bf50:	8102f000 	mrshi	pc, (UNDEF: 2)	; <UNPREDICTABLE>
d001bf54:	2b011ff3 	blcs	0xd0063f28
d001bf58:	f8d9d835 			; <UNDEFINED> instruction: 0xf8d9d835
d001bf5c:	f5c33000 			; <UNDEFINED> instruction: 0xf5c33000
d001bf60:	45532380 	ldrbmi	r2, [r3, #-896]	; 0xfffffc80
d001bf64:	f7f7d20a 			; <UNDEFINED> instruction: 0xf7f7d20a
d001bf68:	2300ffe3 	movwcs	pc, #4067	; 0xfe3	; <UNPREDICTABLE>
d001bf6c:	e0642400 	rsb	r2, r4, r0, lsl #8
d001bf70:	46824605 	strmi	r4, [r2], r5, lsl #12
d001bf74:	46aae7dd 	ssatmi	lr, #11, sp, asr #15
d001bf78:	e7da2607 	ldrb	r2, [sl, r7, lsl #12]
d001bf7c:	f7f74650 			; <UNDEFINED> instruction: 0xf7f74650
d001bf80:	4604ff9f 			; <UNDEFINED> instruction: 0x4604ff9f
d001bf84:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001bf88:	1ff2af2d 	svcne	0x00f2af2d
d001bf8c:	425321ff 	subsmi	r2, r3, #-1073741761	; 0xc000003f
d001bf90:	22004153 	andcs	r4, r0, #-1073741804	; 0xc0000014
d001bf94:	46039300 	strmi	r9, [r3], -r0, lsl #6
d001bf98:	f7fe4650 			; <UNDEFINED> instruction: 0xf7fe4650
d001bf9c:	4620f98d 	strtmi	pc, [r0], -sp, lsl #19
d001bfa0:	038aeb04 	orreq	lr, sl, #4, 22	; 0x1000
d001bfa4:	d0e04283 	rscle	r4, r0, r3, lsl #5
d001bfa8:	2b04f850 	blcs	0xd015a0f0
d001bfac:	d0f92a00 	rscsle	r2, r9, r0, lsl #20
d001bfb0:	447b4b5f 	ldrbtmi	r4, [fp], #-2911	; 0xfffff4a1
d001bfb4:	139ff503 	orrsne	pc, pc, #12582912	; 0xc00000
d001bfb8:	53f1f503 	mvnspl	pc, #12582912	; 0xc00000
d001bfbc:	4452681a 	ldrbmi	r6, [r2], #-2074	; 0xfffff7e6
d001bfc0:	2301601a 	movwcs	r6, #4122	; 0x101a
d001bfc4:	212de7d2 	ldrdcs	lr, [sp, -r2]!
d001bfc8:	f7f64640 			; <UNDEFINED> instruction: 0xf7f64640
d001bfcc:	f8d8ff38 			; <UNDEFINED> instruction: 0xf8d8ff38
d001bfd0:	46813024 	strmi	r3, [r1], r4, lsr #32
d001bfd4:	718df44f 	orrvc	pc, sp, pc, asr #8
d001bfd8:	46409305 	strbmi	r9, [r0], -r5, lsl #6
d001bfdc:	3028f8d8 	ldrdcc	pc, [r8], -r8	; <UNPREDICTABLE>
d001bfe0:	402cf8d8 	ldrdmi	pc, [ip], -r8	; <UNPREDICTABLE>
d001bfe4:	f8989306 			; <UNDEFINED> instruction: 0xf8989306
d001bfe8:	e9d83030 	ldmib	r8, {r4, r5, ip, sp}^
d001bfec:	9307b206 	movwls	fp, #29190	; 0x7206
d001bff0:	3034f8d8 	ldrsbtcc	pc, [r4], -r8	; <UNPREDICTABLE>
d001bff4:	93089209 	movwls	r9, #33289	; 0x8209
d001bff8:	ff21f7f6 			; <UNDEFINED> instruction: 0xff21f7f6
d001bffc:	b1209a09 			; <UNDEFINED> instruction: 0xb1209a09
d001c000:	f7f74640 			; <UNDEFINED> instruction: 0xf7f74640
d001c004:	4604fcbd 			; <UNDEFINED> instruction: 0x4604fcbd
d001c008:	f240e00e 	vhadd.s8	d30, d0, d14
d001c00c:	429c1301 	addsmi	r1, ip, #67108864	; 0x4000000
d001c010:	4659d13d 			; <UNDEFINED> instruction: 0x4659d13d
d001c014:	f7f44640 			; <UNDEFINED> instruction: 0xf7f44640
d001c018:	2800fc60 	stmdacs	r0, {r5, r6, sl, fp, ip, sp, lr, pc}
d001c01c:	8092f000 	addshi	pc, r2, r0
d001c020:	46406a04 	strbmi	r6, [r0], -r4, lsl #20
d001c024:	fef0f7f6 	mrc2	7, 7, pc, cr0, cr6, {7}
d001c028:	0f00f1b9 	svceq	0x0000f1b9
d001c02c:	4264d000 	rsbmi	sp, r4, #0
d001c030:	f04f2e05 			; <UNDEFINED> instruction: 0xf04f2e05
d001c034:	bf080300 	svclt	0x00080300
d001c038:	f8dfb2e4 			; <UNDEFINED> instruction: 0xf8dfb2e4
d001c03c:	213b80f8 	ldrshcs	r8, [fp, -r8]!	; <UNPREDICTABLE>
d001c040:	44f84a3d 	ldrbtmi	r4, [r8], #2621	; 0xa3d
d001c044:	447a9302 	ldrbtmi	r9, [sl], #-770	; 0xfffffcfe
d001c048:	f7f64640 			; <UNDEFINED> instruction: 0xf7f64640
d001c04c:	2800ff06 	stmdacs	r0, {r1, r2, r8, r9, sl, fp, ip, sp, lr, pc}
d001c050:	aec8f43f 	mcrge	4, 6, pc, cr8, cr15, {1}	; <UNPREDICTABLE>
d001c054:	9b021ff2 	blls	0xd00a4024
d001c058:	f2002a01 	vpmax.s8	d2, d0, d1
d001c05c:	2b0080d8 	blcs	0xd003c3c4
d001c060:	2e08d07c 	mcrcs	0, 0, sp, cr8, cr12, {3}
d001c064:	f508d108 			; <UNDEFINED> instruction: 0xf508d108
d001c068:	f8d8387f 			; <UNDEFINED> instruction: 0xf8d8387f
d001c06c:	32032218 	andcc	r2, r3, #24, 4	; 0x80000001
d001c070:	0203f022 	andeq	pc, r3, #34	; 0x22
d001c074:	2218f8c8 	andscs	pc, r8, #200, 16	; 0xc80000
d001c078:	447a4a30 	ldrbtmi	r4, [sl], #-2608	; 0xfffff5d0
d001c07c:	327ff502 	rsbscc	pc, pc, #8388608	; 0x800000
d001c080:	8218f8d2 	andshi	pc, r8, #13762560	; 0xd20000
d001c084:	0105eb08 	tsteq	r5, r8, lsl #22
d001c088:	1218f8c2 	andsne	pc, r8, #12713984	; 0xc20000
d001c08c:	f5a4e07b 			; <UNDEFINED> instruction: 0xf5a4e07b
d001c090:	2c017481 	cfstrscs	mvf7, [r1], {129}	; 0x81
d001c094:	4602d856 			; <UNDEFINED> instruction: 0x4602d856
d001c098:	46402101 	strbmi	r2, [r0], -r1, lsl #2
d001c09c:	ff68f7f6 			; <UNDEFINED> instruction: 0xff68f7f6
d001c0a0:	3058f8d8 	ldrsbcc	pc, [r8], #-136	; 0xffffff78	; <UNPREDICTABLE>
d001c0a4:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001c0a8:	f110ae9d 			; <UNDEFINED> instruction: 0xf110ae9d
d001c0ac:	93024300 	movwls	r4, #8960	; 0x2300
d001c0b0:	0300f141 	movweq	pc, #321	; 0x141	; <UNPREDICTABLE>
d001c0b4:	e9dd9303 	ldmib	sp, {r0, r1, r8, r9, ip, pc}^
d001c0b8:	2c013402 	cfstrscs	mvf3, [r1], {2}
d001c0bc:	f1b3bf08 			; <UNDEFINED> instruction: 0xf1b3bf08
d001c0c0:	d3a04f00 	movle	r4, #0, 30
d001c0c4:	447b4b1e 	ldrbtmi	r4, [fp], #-2846	; 0xfffff4e2
d001c0c8:	3058f8c8 	subscc	pc, r8, r8, asr #17
d001c0cc:	f8c89b05 			; <UNDEFINED> instruction: 0xf8c89b05
d001c0d0:	9b06305c 	blls	0xd01a8248
d001c0d4:	3060f8c8 	rsbcc	pc, r0, r8, asr #17
d001c0d8:	f8c89b07 			; <UNDEFINED> instruction: 0xf8c89b07
d001c0dc:	9b083064 	blls	0xd0228274
d001c0e0:	3068f8c8 	rsbcc	pc, r8, r8, asr #17
d001c0e4:	bf00e67e 	svclt	0x0000e67e
d001c0e8:	0013fe4d 	andseq	pc, r3, sp, asr #28
d001c0ec:	0000a672 	andeq	sl, r0, r2, ror r6
d001c0f0:	0000a634 	andeq	sl, r0, r4, lsr r6
d001c0f4:	fffffe26 			; <UNDEFINED> instruction: 0xfffffe26
d001c0f8:	0000a5ea 	andeq	sl, r0, sl, ror #11
d001c0fc:	fffffdd0 			; <UNDEFINED> instruction: 0xfffffdd0
d001c100:	fffffdcf 			; <UNDEFINED> instruction: 0xfffffdcf
d001c104:	fffffde7 			; <UNDEFINED> instruction: 0xfffffde7
d001c108:	0000a57c 	andeq	sl, r0, ip, ror r5
d001c10c:	0000a55e 	andeq	sl, r0, lr, asr r5
d001c110:	fffffdea 			; <UNDEFINED> instruction: 0xfffffdea
d001c114:	fffffdfd 			; <UNDEFINED> instruction: 0xfffffdfd
d001c118:	0000a52e 	andeq	sl, r0, lr, lsr #10
d001c11c:	0000a50a 	andeq	sl, r0, sl, lsl #10
d001c120:	fffffde4 			; <UNDEFINED> instruction: 0xfffffde4
d001c124:	0000a4f4 	strdeq	sl, [r0], -r4
d001c128:	fffffdec 			; <UNDEFINED> instruction: 0xfffffdec
d001c12c:	0000a4cc 	andeq	sl, r0, ip, asr #9
d001c130:	0000a452 	andeq	sl, r0, r2, asr r4
d001c134:	0000a3c2 	andeq	sl, r0, r2, asr #7
d001c138:	fffffd13 			; <UNDEFINED> instruction: 0xfffffd13
d001c13c:	0000a38a 	andeq	sl, r0, sl, lsl #7
d001c140:	fffffc6b 			; <UNDEFINED> instruction: 0xfffffc6b
d001c144:	483a4939 	ldmdami	sl!, {r0, r3, r4, r5, r8, fp, lr}
d001c148:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d001c14c:	e8bdb00b 	pop	{r0, r1, r3, ip, sp, pc}
d001c150:	b0044ff0 	strdlt	r4, [r4], -r0
d001c154:	b828f7f4 	stmdalt	r8!, {r2, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}
d001c158:	e7694604 	strb	r4, [r9, -r4, lsl #12]!
d001c15c:	d1082e08 	tstle	r8, r8, lsl #28
d001c160:	387ff508 	ldmdacc	pc!, {r3, r8, sl, ip, sp, lr, pc}^	; <UNPREDICTABLE>
d001c164:	221cf8d8 	andscs	pc, ip, #216, 16	; 0xd80000
d001c168:	f0223203 			; <UNDEFINED> instruction: 0xf0223203
d001c16c:	f8c80203 			; <UNDEFINED> instruction: 0xf8c80203
d001c170:	4a30221c 	bmi	0xd0c249e8
d001c174:	f502447a 			; <UNDEFINED> instruction: 0xf502447a
d001c178:	f8d2327f 			; <UNDEFINED> instruction: 0xf8d2327f
d001c17c:	eb08821c 	bl	0xd023c9f4
d001c180:	f8c20105 			; <UNDEFINED> instruction: 0xf8c20105
d001c184:	4a2c121c 	bmi	0xd0b209fc
d001c188:	fa5f2b00 	blx	0xd17e6d90
d001c18c:	447af987 	ldrbtmi	pc, [sl], #-2439	; 0xfffff679	; <UNPREDICTABLE>
d001c190:	f04fbf08 			; <UNDEFINED> instruction: 0xf04fbf08
d001c194:	2e080a00 	vmlacs.f32	s0, s16, s0
d001c198:	3167f502 	msrcc	SPSR_sxc, r2, lsl #10
d001c19c:	b008f892 	mullt	r8, r2, r8
d001c1a0:	f8d1b2da 			; <UNDEFINED> instruction: 0xf8d1b2da
d001c1a4:	920201c4 	andls	r0, r2, #196, 2	; 0x31
d001c1a8:	0c01f100 	stfeqd	f7, [r1], {-0}
d001c1ac:	c1c4f8c1 	bicgt	pc, r4, r1, asr #17
d001c1b0:	08add137 	stmiaeq	sp!, {r0, r1, r2, r4, r5, r8, ip, lr, pc}
d001c1b4:	223c4f21 	eorscs	r4, ip, #33, 30	; 0x84
d001c1b8:	447f2100 	ldrbtmi	r2, [pc], #-256	; 0xd001c1c0
d001c1bc:	7700fb02 	strvc	pc, [r0, -r2, lsl #22]
d001c1c0:	375ff507 	ldrbcc	pc, [pc, -r7, lsl #10]	; <UNPREDICTABLE>
d001c1c4:	7371f507 	cmnvc	r1, #29360128	; 0x1c00000	; <UNPREDICTABLE>
d001c1c8:	f0034618 			; <UNDEFINED> instruction: 0xf0034618
d001c1cc:	f10dfb71 			; <UNDEFINED> instruction: 0xf10dfb71
d001c1d0:	46840e50 	pkhtbmi	r0, r4, r0, asr #28
d001c1d4:	43e4f8c7 	mvnmi	pc, #13041664	; 0xc70000
d001c1d8:	83e8f8c7 	mvnhi	pc, #13041664	; 0xc70000
d001c1dc:	63ecf887 	mvnvs	pc, #8847360	; 0x870000
d001c1e0:	b3edf887 	mvnlt	pc, #8847360	; 0x870000
d001c1e4:	93f0f887 	mvnsls	pc, #8847360	; 0x870000
d001c1e8:	a3f8f8c7 	mvnsge	pc, #13041664	; 0xc70000
d001c1ec:	53fcf8c7 	mvnspl	pc, #13041664	; 0xc70000
d001c1f0:	000fe8be 			; <UNDEFINED> instruction: 0x000fe8be
d001c1f4:	000fe8ac 	andeq	lr, pc, ip, lsr #17
d001c1f8:	000fe89e 	muleq	pc, lr, r8	; <UNPREDICTABLE>
d001c1fc:	000fe88c 	andeq	lr, pc, ip, lsl #17
d001c200:	f8879b02 			; <UNDEFINED> instruction: 0xf8879b02
d001c204:	9b0433ef 	blls	0xd01291c8
d001c208:	33f4f8c7 	mvnscc	pc, #13041664	; 0xc70000
d001c20c:	f508e5ea 			; <UNDEFINED> instruction: 0xf508e5ea
d001c210:	f8d2327f 			; <UNDEFINED> instruction: 0xf8d2327f
d001c214:	31031218 	tstcc	r3, r8, lsl r2
d001c218:	0803f021 	stmdaeq	r3, {r0, r5, ip, sp, lr, pc}
d001c21c:	0104f108 	tsteq	r4, r8, lsl #2	; <UNPREDICTABLE>
d001c220:	2e07e732 	mcrcs	7, 0, lr, cr7, cr2, {1}
d001c224:	2500bf18 	strcs	fp, [r0, #-3864]	; 0xfffff0e8
d001c228:	bf00e7c4 	svclt	0x0000e7c4
d001c22c:	ffffdcb8 			; <UNDEFINED> instruction: 0xffffdcb8
d001c230:	0000a2ba 			; <UNDEFINED> instruction: 0x0000a2ba
d001c234:	0000a290 	muleq	r0, r0, r2
d001c238:	0000a276 	andeq	sl, r0, r6, ror r2
d001c23c:	0000a24a 	andeq	sl, r0, sl, asr #4

Disassembly of section .text.sidc_compile_project.part.0:

d001ca08 <.text.sidc_compile_project.part.0>:
d001ca08:	4ff0e92d 	svcmi	0x00f0e92d
d001ca0c:	931cb0e5 	tstls	ip, #229	; 0xe5
d001ca10:	90182300 	andsls	r2, r8, r0, lsl #6
d001ca14:	921a3004 	andsls	r3, sl, #4
d001ca18:	9119461a 	tstls	r9, sl, lsl r6
d001ca1c:	428b991a 	addmi	r9, fp, #425984	; 0x68000
d001ca20:	809cf040 	addshi	pc, ip, r0, asr #32
d001ca24:	21004ca3 	smlatbcs	r0, r3, ip, r4
d001ca28:	447c4a9e 	ldrbtmi	r4, [ip], #-2718	; 0xfffff562
d001ca2c:	f0024620 			; <UNDEFINED> instruction: 0xf0024620
d001ca30:	9b6eff3f 	blls	0xd1bdc734
d001ca34:	22bc48a0 	adcscs	r4, ip, #160, 16	; 0xa00000
d001ca38:	9b1c66e3 	blls	0xd07365cc
d001ca3c:	499f4478 	ldmibmi	pc, {r3, r4, r5, r6, sl, lr}	; <UNPREDICTABLE>
d001ca40:	f04f6723 			; <UNDEFINED> instruction: 0xf04f6723
d001ca44:	447933ff 	ldrbtmi	r3, [r9], #-1023	; 0xfffffc01
d001ca48:	67a33040 	strvs	r3, [r3, r0, asr #32]!
d001ca4c:	ff3ef002 			; <UNDEFINED> instruction: 0xff3ef002
d001ca50:	348ff504 	strcc	pc, [pc], #1284	; 0xd001ca58
d001ca54:	4a9423bc 	bmi	0xce52594c
d001ca58:	31b8f8c4 			; <UNDEFINED> instruction: 0x31b8f8c4
d001ca5c:	93162300 	tstls	r6, #0, 6
d001ca60:	447b4b97 	ldrbtmi	r4, [fp], #-2967	; 0xfffff469
d001ca64:	931e4413 	tstls	lr, #318767104	; 0x13000000
d001ca68:	9a1a4c96 	bls	0xd06afcc8
d001ca6c:	447c9916 	ldrbtmi	r9, [ip], #-2326	; 0xfffff6ea
d001ca70:	6da3428a 	sfmvs	f4, 4, [r3, #552]!	; 0x228
d001ca74:	836cf001 	msrhi	SPSR_fs, #1
d001ca78:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d001ca7c:	48928090 	ldmmi	r2, {r4, r7, pc}
d001ca80:	44784b8a 	ldrbtmi	r4, [r8], #-2954	; 0xfffff476
d001ca84:	2d005cc5 	stccs	12, cr5, [r0, #-788]	; 0xfffffcec
d001ca88:	8391f001 	orrshi	pc, r1, #1
d001ca8c:	2c006d84 	stccs	13, cr6, [r0], {132}	; 0x84
d001ca90:	838cf041 	orrhi	pc, ip, #65	; 0x41
d001ca94:	338ff500 	orrcc	pc, pc, #0, 10
d001ca98:	f8d34d8c 			; <UNDEFINED> instruction: 0xf8d34d8c
d001ca9c:	447d61b8 	ldrbtmi	r6, [sp], #-440	; 0xfffffe48
d001caa0:	34027869 	strcc	r7, [r2], #-2153	; 0xfffff797
d001caa4:	3b02f815 	blcc	0xd00dab00
d001caa8:	2101ea43 	tstcs	r1, r3, asr #20
d001caac:	f8d6f7f8 			; <UNDEFINED> instruction: 0xf8d6f7f8
d001cab0:	d1f52cce 	mvnsle	r2, lr, asr #25
d001cab4:	338ff500 	orrcc	pc, pc, #0, 10
d001cab8:	24004f85 	strcs	r4, [r0], #-3973	; 0xfffff07b
d001cabc:	51b8f8d3 			; <UNDEFINED> instruction: 0x51b8f8d3
d001cac0:	7879447f 	ldmdavc	r9!, {r0, r1, r2, r3, r4, r5, r6, sl, lr}^
d001cac4:	f8173402 			; <UNDEFINED> instruction: 0xf8173402
d001cac8:	ea433b02 	b	0xd10eb6d8
d001cacc:	f7f82101 			; <UNDEFINED> instruction: 0xf7f82101
d001cad0:	2cf2f8c5 	ldclcs	8, cr15, [r2], #788	; 0x314
d001cad4:	4c7fd1f5 	ldfmip	f5, [pc], #-980	; 0xd001c708
d001cad8:	0800f04f 	stmdaeq	r0, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d001cadc:	447c4f74 	ldrbtmi	r4, [ip], #-3956	; 0xfffff08c
d001cae0:	a1f4f8df 	ldrsbge	pc, [r4, #143]!	; 0x8f	; <UNPREDICTABLE>
d001cae4:	91f4f8df 	ldrsbls	pc, [r4, #143]!	; 0x8f	; <UNPREDICTABLE>
d001cae8:	44a24427 	strtmi	r4, [r2], #1063	; 0x427
d001caec:	3000f8da 	ldrdcc	pc, [r0], -sl
d001caf0:	d2034598 	andle	r4, r3, #152, 10	; 0x26000000
d001caf4:	2b006da3 	blcs	0xd0038188
d001caf8:	835cf001 	cmphi	ip, #1	; <UNPREDICTABLE>
d001cafc:	447b4b78 	ldrbtmi	r4, [fp], #-2936	; 0xfffff488
d001cb00:	328ff503 	addcc	pc, pc, #12582912	; 0xc00000
d001cb04:	337ff503 	cmncc	pc, #12582912	; 0xc00000	; <UNPREDICTABLE>
d001cb08:	126ee9d2 	rsbne	lr, lr, #3440640	; 0x348000
d001cb0c:	6218f8d3 	andsvs	pc, r8, #13828096	; 0xd30000
d001cb10:	0a02eb01 	beq	0xd00d771c
d001cb14:	0703f10a 	streq	pc, [r3, -sl, lsl #2]
d001cb18:	0703f027 	streq	pc, [r3, -r7, lsr #32]
d001cb1c:	f0012e00 			; <UNDEFINED> instruction: 0xf0012e00
d001cb20:	443e8377 	ldrtmi	r8, [lr], #-887	; 0xfffffc89
d001cb24:	031ff106 	tsteq	pc, #-2147483647	; 0x80000001	; <UNPREDICTABLE>
d001cb28:	1f80f5b6 	svcne	0x0080f5b6
d001cb2c:	031ff023 	tsteq	pc, #35	; 0x23	; <UNPREDICTABLE>
d001cb30:	d905930f 	stmdble	r5, {r0, r1, r2, r3, r8, r9, ip, pc}
d001cb34:	486c496b 	stmdami	ip!, {r0, r1, r3, r5, r6, r8, fp, lr}^
d001cb38:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d001cb3c:	fb34f7f3 	blx	0xd0d5ab12
d001cb40:	f04f4c6a 			; <UNDEFINED> instruction: 0xf04f4c6a
d001cb44:	447c0b00 	ldrbtmi	r0, [ip], #-2816	; 0xfffff500
d001cb48:	f50446d9 			; <UNDEFINED> instruction: 0xf50446d9
d001cb4c:	f5043847 			; <UNDEFINED> instruction: 0xf5043847
d001cb50:	f508335f 			; <UNDEFINED> instruction: 0xf508335f
d001cb54:	93107870 	tstls	r0, #112, 16	; 0x700000
d001cb58:	bb86f001 	bllt	0xce1d8b64
d001cb5c:	f8519918 			; <UNDEFINED> instruction: 0xf8519918
d001cb60:	b1291033 			; <UNDEFINED> instruction: 0xb1291033
d001cb64:	1033f850 	eorsne	pc, r3, r0, asr r8	; <UNPREDICTABLE>
d001cb68:	1480f5c2 	strne	pc, [r0], #1474	; 0x5c2
d001cb6c:	d91342a1 	ldmdble	r3, {r0, r5, r7, r9, lr}
d001cb70:	2a019a1a 	bcs	0xd00833e0
d001cb74:	4a5ed00d 	bmi	0xd17d0bb0
d001cb78:	9970447a 	ldmdbls	r0!, {r1, r3, r4, r5, r6, sl, lr}^
d001cb7c:	600a2500 	andvs	r2, sl, r0, lsl #10
d001cb80:	60cb2201 	sbcvs	r2, fp, r1, lsl #4
d001cb84:	608a604a 	addvs	r6, sl, sl, asr #32
d001cb88:	4628610d 	strtmi	r6, [r8], -sp, lsl #2
d001cb8c:	e8bdb065 	pop	{r0, r2, r5, r6, ip, sp, pc}
d001cb90:	4a588ff0 	bmi	0xd1640b58
d001cb94:	e7f0447a 			; <UNDEFINED> instruction: 0xe7f0447a
d001cb98:	3301440a 	movwcc	r4, #5130	; 0x140a
d001cb9c:	9b16e73e 	blls	0xd05d689c
d001cba0:	72239a16 	eorvc	r9, r3, #90112	; 0x16000
d001cba4:	f8539b18 			; <UNDEFINED> instruction: 0xf8539b18
d001cba8:	60233032 	eorvs	r3, r3, r2, lsr r0
d001cbac:	b3839b19 	orrlt	r9, r3, #25600	; 0x6400
d001cbb0:	3022f853 	eorcc	pc, r2, r3, asr r8	; <UNPREDICTABLE>
d001cbb4:	99164c50 	ldmdbls	r6, {r4, r6, sl, fp, lr}
d001cbb8:	4d50447c 	cfldrdmi	mvd4, [r0, #-496]	; 0xfffffe10
d001cbbc:	f04f6763 			; <UNDEFINED> instruction: 0xf04f6763
d001cbc0:	f50433ff 			; <UNDEFINED> instruction: 0xf50433ff
d001cbc4:	f5044250 			; <UNDEFINED> instruction: 0xf5044250
d001cbc8:	67a34650 	sbfxvs	r4, r0, #12, #4
d001cbcc:	46202300 	strtmi	r2, [r0], -r0, lsl #6
d001cbd0:	60d3361c 	sbcsvs	r3, r3, ip, lsl r6
d001cbd4:	424ff504 	submi	pc, pc, #4, 10	; 0x1000000
d001cbd8:	31fcf8c4 	mvnscc	pc, r4, asr #17
d001cbdc:	f8c2447d 			; <UNDEFINED> instruction: 0xf8c2447d
d001cbe0:	9a183088 	bls	0xd0628e08
d001cbe4:	f8523204 			; <UNDEFINED> instruction: 0xf8523204
d001cbe8:	60e32031 	rscvs	r2, r3, r1, lsr r0
d001cbec:	60622301 	rsbvs	r2, r2, r1, lsl #6
d001cbf0:	3304e9c4 	movwcc	lr, #18884	; 0x49c4
d001cbf4:	f908f7f6 			; <UNDEFINED> instruction: 0xf908f7f6
d001cbf8:	f7f64620 			; <UNDEFINED> instruction: 0xf7f64620
d001cbfc:	6ae2f905 	bvs	0xcf8db018
d001cc00:	f5b26da3 			; <UNDEFINED> instruction: 0xf5b26da3
d001cc04:	d1117f83 	tstle	r1, r3, lsl #31
d001cc08:	9b16b12b 	blls	0xd05c90bc
d001cc0c:	93163301 	tstls	r6, #67108864	; 0x4000000
d001cc10:	9b19e72a 	blls	0xd06968c0
d001cc14:	6833e7ce 	ldmdavs	r3!, {r1, r2, r3, r6, r7, r8, r9, sl, sp, lr, pc}
d001cc18:	4628b11b 			; <UNDEFINED> instruction: 0x4628b11b
d001cc1c:	f8f4f7f6 			; <UNDEFINED> instruction: 0xf8f4f7f6
d001cc20:	981ce7ed 	ldmdals	ip, {r0, r2, r3, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d001cc24:	fe9cf7f7 	mrc2	7, 4, pc, cr12, cr7, {7}
d001cc28:	d1f62800 	mvnsle	r2, r0, lsl #16
d001cc2c:	447c4c34 	ldrbtmi	r4, [ip], #-3124	; 0xfffff3cc
d001cc30:	2e006da6 	cdpcs	13, 0, cr6, cr0, cr6, {5}
d001cc34:	6ae3d1e9 	bvs	0xcf9113e0
d001cc38:	7f80f5b3 	svcvc	0x0080f5b3
d001cc3c:	f240d0e5 	vhadd.s8	<illegal reg q14.5>, q8, <illegal reg q10.5>
d001cc40:	46201119 			; <UNDEFINED> instruction: 0x46201119
d001cc44:	f8fbf7f6 			; <UNDEFINED> instruction: 0xf8fbf7f6
d001cc48:	28004607 	stmdacs	r0, {r0, r1, r2, r9, sl, lr}
d001cc4c:	81a1f000 			; <UNDEFINED> instruction: 0x81a1f000
d001cc50:	0718f104 	ldreq	pc, [r8, -r4, lsl #2]
d001cc54:	f8d4ad2c 			; <UNDEFINED> instruction: 0xf8d4ad2c
d001cc58:	f894802c 			; <UNDEFINED> instruction: 0xf894802c
d001cc5c:	cf0f9030 	svcgt	0x000f9030
d001cc60:	e897c50f 	ldm	r7, {r0, r1, r2, r3, r8, sl, lr, pc}
d001cc64:	e885000f 	stm	r5, {r0, r1, r2, r3}
d001cc68:	6a63000f 	bvs	0xd18dccac
d001cc6c:	1107f240 	tstne	r7, r0, asr #4	; <UNPREDICTABLE>
d001cc70:	930f4620 	movwls	r4, #63008	; 0xf620
d001cc74:	93106aa3 	tstls	r0, #667648	; 0xa3000
d001cc78:	e9d46b63 	ldmib	r4, {r0, r1, r5, r6, r8, r9, fp, sp, lr}^
d001cc7c:	9311ba06 	tstls	r1, #24576	; 0x6000
d001cc80:	f8ddf7f6 			; <UNDEFINED> instruction: 0xf8ddf7f6
d001cc84:	28004607 	stmdacs	r0, {r0, r1, r2, r9, sl, lr}
d001cc88:	812bf040 	msrhi	CPSR_fxc, r0, asr #32
d001cc8c:	f2406ae6 	vpmax.s8	q11, q8, q11
d001cc90:	429e131b 	addsmi	r1, lr, #1811939328	; 0x6c000000
d001cc94:	4620d136 			; <UNDEFINED> instruction: 0x4620d136
d001cc98:	fbd2f7f6 	blx	0xcf4dac7a
d001cc9c:	d0c52800 	sbcle	r2, r5, r0, lsl #16
d001cca0:	e078463e 	rsbs	r4, r8, lr, lsr r6
d001cca4:	0014b2a0 	andseq	fp, r4, r0, lsr #5
d001cca8:	00149234 	andseq	r9, r4, r4, lsr r2
d001ccac:	0014b29e 	mulseq	r4, lr, r2
d001ccb0:	00143628 	andseq	r3, r4, r8, lsr #12
d001ccb4:	000099da 	ldrdeq	r9, [r0], -sl
d001ccb8:	00154c68 	andseq	r4, r5, r8, ror #24
d001ccbc:	00001d8b 	andeq	r1, r0, fp, lsl #27
d001ccc0:	000099a2 	andeq	r9, r0, r2, lsr #19
d001ccc4:	00009996 	muleq	r0, r6, r9
d001ccc8:	00009982 	andeq	r9, r0, r2, lsl #19
d001cccc:	00001b73 	andeq	r1, r0, r3, ror fp
d001ccd0:	00001c1f 	andeq	r1, r0, pc, lsl ip
d001ccd4:	00009926 	andeq	r9, r0, r6, lsr #18
d001ccd8:	00147628 	andseq	r7, r4, r8, lsr #12
d001ccdc:	0013fe4a 	andseq	pc, r3, sl, asr #28
d001cce0:	00009906 	andeq	r9, r0, r6, lsl #18
d001cce4:	fffffe84 			; <UNDEFINED> instruction: 0xfffffe84
d001cce8:	000098ca 	andeq	r9, r0, sl, asr #17
d001ccec:	000098be 			; <UNDEFINED> instruction: 0x000098be
d001ccf0:	fffff6d9 			; <UNDEFINED> instruction: 0xfffff6d9
d001ccf4:	fffff6a8 			; <UNDEFINED> instruction: 0xfffff6a8
d001ccf8:	0000984c 	andeq	r9, r0, ip, asr #16
d001ccfc:	00009828 	andeq	r9, r0, r8, lsr #16
d001cd00:	000097d6 	ldrdeq	r9, [r0], -r6
d001cd04:	758bf46f 	strvc	pc, [fp, #1135]	; 0x46f
d001cd08:	2b011973 	blcs	0xd00632dc
d001cd0c:	f5a6d84c 			; <UNDEFINED> instruction: 0xf5a6d84c
d001cd10:	ad2c708c 	stcge	0, cr7, [ip, #-560]!	; 0xfffffdd0
d001cd14:	41464246 	cmpmi	r6, r6, asr #4
d001cd18:	f7f64620 			; <UNDEFINED> instruction: 0xf7f64620
d001cd1c:	f104f875 			; <UNDEFINED> instruction: 0xf104f875
d001cd20:	f8d40c18 			; <UNDEFINED> instruction: 0xf8d40c18
d001cd24:	f894802c 			; <UNDEFINED> instruction: 0xf894802c
d001cd28:	e8bc9030 	ldm	ip!, {r4, r5, ip, pc}
d001cd2c:	c50f000f 	strgt	r0, [pc, #-15]	; 0xd001cd25
d001cd30:	000fe89c 	muleq	pc, ip, r8	; <UNPREDICTABLE>
d001cd34:	000fe885 	andeq	lr, pc, r5, lsl #17
d001cd38:	930f6a63 	movwls	r6, #64099	; 0xfa63
d001cd3c:	93106aa3 	tstls	r0, #667648	; 0xa3000
d001cd40:	93116b63 	tstls	r1, #101376	; 0x18c00
d001cd44:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d001cd48:	e9d44598 	ldmib	r4, {r3, r4, r7, r8, sl, lr}^
d001cd4c:	d102ba06 	tstle	r2, r6, lsl #20
d001cd50:	f7f64620 			; <UNDEFINED> instruction: 0xf7f64620
d001cd54:	f8dff859 			; <UNDEFINED> instruction: 0xf8dff859
d001cd58:	447c4c20 	ldrbtmi	r4, [ip], #-3104	; 0xfffff3e0
d001cd5c:	2b7b6ae3 	blcs	0xd1ef78f0
d001cd60:	80c1f000 	sbchi	pc, r1, r0
d001cd64:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d001cd68:	d1164598 			; <UNDEFINED> instruction: 0xd1164598
d001cd6c:	46524633 			; <UNDEFINED> instruction: 0x46524633
d001cd70:	46204659 			; <UNDEFINED> instruction: 0x46204659
d001cd74:	fc60f7f3 	stc2l	7, cr15, [r0], #-972	; 0xfffffc34
d001cd78:	da331e05 	ble	0xd0ce4594
d001cd7c:	b9536da3 	ldmdblt	r3, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d001cd80:	3bf8f8df 	blcc	0xcfe5b104
d001cd84:	65a3447b 	strvs	r4, [r3, #1147]!	; 0x47b
d001cd88:	65e39b0f 	strbvs	r9, [r3, #2831]!	; 0xb0f
d001cd8c:	e9c49b10 	stmib	r4, {r4, r8, r9, fp, ip, pc}^
d001cd90:	9b113918 	blls	0xd046b1f8
d001cd94:	25ff66a3 	ldrbcs	r6, [pc, #1699]!	; 0xd001d43f
d001cd98:	f8dfe024 			; <UNDEFINED> instruction: 0xf8dfe024
d001cd9c:	46201be4 	strtmi	r1, [r0], -r4, ror #23
d001cda0:	f7f34479 			; <UNDEFINED> instruction: 0xf7f34479
d001cda4:	e7f6fa01 	ldrb	pc, [r6, r1, lsl #20]!	; <UNPREDICTABLE>
d001cda8:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d001cdac:	f040429e 			; <UNDEFINED> instruction: 0xf040429e
d001cdb0:	46208094 			; <UNDEFINED> instruction: 0x46208094
d001cdb4:	1206e9d4 	andne	lr, r6, #212, 18	; 0x350000
d001cdb8:	fcebf7f3 	stc2l	7, cr15, [fp], #972	; 0x3cc
d001cdbc:	da062800 	ble	0xd01a6dc4
d001cdc0:	1bc0f8df 	blne	0xcf05b144
d001cdc4:	46204479 			; <UNDEFINED> instruction: 0x46204479
d001cdc8:	f9eef7f3 			; <UNDEFINED> instruction: 0xf9eef7f3
d001cdcc:	2324e768 			; <UNDEFINED> instruction: 0x2324e768
d001cdd0:	fb03463e 	blx	0xd00ee6d2
d001cdd4:	f5004000 			; <UNDEFINED> instruction: 0xf5004000
d001cdd8:	f8903075 			; <UNDEFINED> instruction: 0xf8903075
d001cddc:	462053ac 	strtmi	r5, [r0], -ip, lsr #7
d001cde0:	f812f7f6 			; <UNDEFINED> instruction: 0xf812f7f6
d001cde4:	4ba0f8df 	blmi	0xce85b168
d001cde8:	6da3447c 	cfstrsvs	mvf4, [r3, #496]!	; 0x1f0
d001cdec:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001cdf0:	b34faf1d 	movtlt	sl, #65309	; 0xff1d
d001cdf4:	af2c9b0f 	svcge	0x002c9b0f
d001cdf8:	90c8f88d 	sbcls	pc, r8, sp, lsl #17
d001cdfc:	932fad06 			; <UNDEFINED> instruction: 0x932fad06
d001ce00:	e9cd9b10 	stmib	sp, {r4, r8, r9, fp, ip, pc}^
d001ce04:	9b113830 	blls	0xd046aecc
d001ce08:	ba2ce9cd 	blt	0xd0b57544
d001ce0c:	cf0f9333 	svcgt	0x000f9333
d001ce10:	e897c50f 	ldm	r7, {r0, r1, r2, r3, r8, sl, lr, pc}
d001ce14:	e885000f 	stm	r5, {r0, r1, r2, r3}
d001ce18:	f240000f 	vhadd.s8	d16, d0, d15
d001ce1c:	96041301 	strls	r1, [r4], -r1, lsl #6
d001ce20:	0303ebb8 	movweq	lr, #15288	; 0x3bb8
d001ce24:	2301bf18 	movwcs	fp, #7960	; 0x1f18
d001ce28:	ab309305 	blge	0xd0c41a44
d001ce2c:	e88dcb0f 	stm	sp, {r0, r1, r2, r3, r8, r9, fp, lr, pc}
d001ce30:	ab2c000f 	blge	0xd0b1ce74
d001ce34:	f7f7cb0f 			; <UNDEFINED> instruction: 0xf7f7cb0f
d001ce38:	1e05fa7f 			; <UNDEFINED> instruction: 0x1e05fa7f
d001ce3c:	aef6f6ff 	mrcge	6, 7, APSR_nzcv, cr6, cr15, {7}
d001ce40:	2b006da3 	blcs	0xd00384d4
d001ce44:	aef2f47f 	mrcge	4, 7, APSR_nzcv, cr2, cr15, {3}
d001ce48:	4b40f8df 	blmi	0xd105b1cc
d001ce4c:	447cae34 	ldrbtmi	sl, [ip], #-3636	; 0xfffff1cc
d001ce50:	0718f104 	ldreq	pc, [r8, -r4, lsl #2]
d001ce54:	c60fcf0f 	strgt	ip, [pc], -pc, lsl #30
d001ce58:	000fe897 	muleq	pc, r7, r8	; <UNPREDICTABLE>
d001ce5c:	000fe886 	andeq	lr, pc, r6, lsl #17
d001ce60:	2b2cf8df 	blcs	0xd0b5b1e4
d001ce64:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d001ce68:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d001ce6c:	fff5f7f5 			; <UNDEFINED> instruction: 0xfff5f7f5
d001ce70:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001ce74:	f8dfaedb 			; <UNDEFINED> instruction: 0xf8dfaedb
d001ce78:	213b2b1c 	teqcs	fp, ip, lsl fp
d001ce7c:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d001ce80:	ffebf7f5 			; <UNDEFINED> instruction: 0xffebf7f5
d001ce84:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001ce88:	af34aed1 	svcge	0x0034aed1
d001ce8c:	f8ddae3c 			; <UNDEFINED> instruction: 0xf8ddae3c
d001ce90:	f8dd90dc 			; <UNDEFINED> instruction: 0xf8dd90dc
d001ce94:	cf0f80e0 	svcgt	0x000f80e0
d001ce98:	ba34e9dd 	blt	0xd0d57614
d001ce9c:	e897c60f 	ldm	r7, {r0, r1, r2, r3, r9, sl, lr, pc}
d001cea0:	e886000f 	stm	r6, {r0, r1, r2, r3}
d001cea4:	4652000f 	ldrbmi	r0, [r2], -pc
d001cea8:	46204659 			; <UNDEFINED> instruction: 0x46204659
d001ceac:	70e8f89d 	smlalvc	pc, r8, sp, r8	; <UNPREDICTABLE>
d001ceb0:	f7f39e3b 			; <UNDEFINED> instruction: 0xf7f39e3b
d001ceb4:	2800fc49 	stmdacs	r0, {r0, r3, r6, sl, fp, ip, sp, lr, pc}
d001ceb8:	f8dfdb17 			; <UNDEFINED> instruction: 0xf8dfdb17
d001cebc:	447b3adc 	ldrbtmi	r3, [fp], #-2780	; 0xfffff524
d001cec0:	2a006d9a 	bcs	0xd0038530
d001cec4:	aeb2f47f 	mrcge	4, 5, APSR_nzcv, cr2, cr15, {3}
d001cec8:	2ad0f8df 	bcs	0xcf45b24c
d001cecc:	447a669e 	ldrbtmi	r6, [sl], #-1694	; 0xfffff962
d001ced0:	8718e9c3 	ldrhi	lr, [r8, -r3, asr #19]
d001ced4:	2916e9c3 	ldmdbcs	r6, {r0, r1, r6, r7, r8, fp, sp, lr, pc}
d001ced8:	f8dfe6a8 			; <UNDEFINED> instruction: 0xf8dfe6a8
d001cedc:	44791ac4 	ldrbtmi	r1, [r9], #-2756	; 0xfffff53c
d001cee0:	4637e771 			; <UNDEFINED> instruction: 0x4637e771
d001cee4:	2701e757 	smlsdcs	r1, r7, r7, lr
d001cee8:	4652e755 			; <UNDEFINED> instruction: 0x4652e755
d001ceec:	46204659 			; <UNDEFINED> instruction: 0x46204659
d001cef0:	fc94f7f3 	ldc2	7, cr15, [r4], {243}	; 0xf3
d001cef4:	dae02800 	ble	0xcf826efc
d001cef8:	46594652 			; <UNDEFINED> instruction: 0x46594652
d001cefc:	f7f34620 			; <UNDEFINED> instruction: 0xf7f34620
d001cf00:	2800fc48 	stmdacs	r0, {r3, r6, sl, fp, ip, sp, lr, pc}
d001cf04:	2324db16 			; <UNDEFINED> instruction: 0x2324db16
d001cf08:	4000fb03 	andmi	pc, r0, r3, lsl #22
d001cf0c:	3075f500 	rsbscc	pc, r5, r0, lsl #10
d001cf10:	33acf890 			; <UNDEFINED> instruction: 0x33acf890
d001cf14:	f43f429d 			; <UNDEFINED> instruction: 0xf43f429d
d001cf18:	6da3ae89 	stcvs	14, cr10, [r3, #548]!	; 0x224
d001cf1c:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001cf20:	f8dfae85 			; <UNDEFINED> instruction: 0xf8dfae85
d001cf24:	447b3a80 	ldrbtmi	r3, [fp], #-2688	; 0xfffff580
d001cf28:	3916e9c4 	ldmdbcc	r6, {r2, r6, r7, r8, fp, sp, lr, pc}
d001cf2c:	8718e9c4 	ldrhi	lr, [r8, -r4, asr #19]
d001cf30:	e67b66a6 	ldrbt	r6, [fp], -r6, lsr #13
d001cf34:	3278f504 	rsbscc	pc, r8, #4, 10	; 0x1000000
d001cf38:	308cf8d2 	ldrdcc	pc, [ip], r2
d001cf3c:	d1072b40 	tstle	r7, r0, asr #22
d001cf40:	2b006da3 	blcs	0xd00385d4
d001cf44:	ae72f47f 	mrcge	4, 3, APSR_nzcv, cr2, cr15, {3}
d001cf48:	3a5cf8df 	bcc	0xd175b2cc
d001cf4c:	e7eb447b 			; <UNDEFINED> instruction: 0xe7eb447b
d001cf50:	f8941c59 			; <UNDEFINED> instruction: 0xf8941c59
d001cf54:	f88dc008 			; <UNDEFINED> instruction: 0xf88dc008
d001cf58:	af3c7108 	svcge	0x003c7108
d001cf5c:	108cf8c2 	addne	pc, ip, r2, asr #17
d001cf60:	96432224 	strbls	r2, [r3], -r4, lsr #4
d001cf64:	4403fb02 	strmi	pc, [r3], #-2818	; 0xfffff4fe
d001cf68:	8100f8cd 	smlabthi	r0, sp, r8, pc	; <UNPREDICTABLE>
d001cf6c:	3475f504 	ldrbtcc	pc, [r5], #-1284	; 0xfffffafc	; <UNPREDICTABLE>
d001cf70:	90fcf8cd 	rscsls	pc, ip, sp, asr #17
d001cf74:	7663f504 	strbtvc	pc, [r3], -r4, lsl #10	; <UNPREDICTABLE>
d001cf78:	53acf884 			; <UNDEFINED> instruction: 0x53acf884
d001cf7c:	c3adf884 			; <UNDEFINED> instruction: 0xc3adf884
d001cf80:	ba3ce9cd 	blt	0xd0f576bc
d001cf84:	c60fcf0f 	strgt	ip, [pc], -pc, lsl #30
d001cf88:	000fe897 	muleq	pc, r7, r8	; <UNPREDICTABLE>
d001cf8c:	000fe886 	andeq	lr, pc, r6, lsl #17
d001cf90:	6ae5e64c 	bvs	0xcf9968c8
d001cf94:	718bf46f 	orrvc	pc, fp, pc, ror #8
d001cf98:	2b01186b 	blcs	0xd006314c
d001cf9c:	f8d4d85d 			; <UNDEFINED> instruction: 0xf8d4d85d
d001cfa0:	f240a04c 	vhadd.s8	q13, q0, q6
d001cfa4:	459a1301 	ldrmi	r1, [sl, #769]	; 0x301
d001cfa8:	4620d157 			; <UNDEFINED> instruction: 0x4620d157
d001cfac:	f7f5ae3c 			; <UNDEFINED> instruction: 0xf7f5ae3c
d001cfb0:	f104ff2b 			; <UNDEFINED> instruction: 0xf104ff2b
d001cfb4:	f8d40c18 			; <UNDEFINED> instruction: 0xf8d40c18
d001cfb8:	f8d4b024 			; <UNDEFINED> instruction: 0xf8d4b024
d001cfbc:	f8949028 			; <UNDEFINED> instruction: 0xf8949028
d001cfc0:	e8bc8030 	ldm	ip!, {r4, r5, pc}
d001cfc4:	c60f000f 	strgt	r0, [pc], -pc
d001cfc8:	000fe89c 	muleq	pc, ip, r8	; <UNPREDICTABLE>
d001cfcc:	000fe886 	andeq	lr, pc, r6, lsl #17
d001cfd0:	29d8f8df 	ldmibcs	r8, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d001cfd4:	46204651 			; <UNDEFINED> instruction: 0x46204651
d001cfd8:	447a6b66 	ldrbtmi	r6, [sl], #-2918	; 0xfffff49a
d001cfdc:	ff3df7f5 			; <UNDEFINED> instruction: 0xff3df7f5
d001cfe0:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001cfe4:	6ae3ae23 	bvs	0xcf908878
d001cfe8:	d12a2b7b 			; <UNDEFINED> instruction: 0xd12a2b7b
d001cfec:	0cf0f10d 	ldfeqp	f7, [r0], #52	; 0x34
d001cff0:	f8cd9643 			; <UNDEFINED> instruction: 0xf8cd9643
d001cff4:	ae069100 	mvfges	f1, f0
d001cff8:	8108f88d 	smlabbhi	r8, sp, r8, pc	; <UNPREDICTABLE>
d001cffc:	b0fcf8cd 	rscslt	pc, ip, sp, asr #17
d001d000:	000fe8bc 			; <UNDEFINED> instruction: 0x000fe8bc
d001d004:	e89cc60f 	ldm	ip, {r0, r1, r2, r3, r9, sl, lr, pc}
d001d008:	e886000f 	stm	r6, {r0, r1, r2, r3}
d001d00c:	f5a5000f 			; <UNDEFINED> instruction: 0xf5a5000f
d001d010:	ab40728c 	blge	0xd1039a48
d001d014:	42559705 	subsmi	r9, r5, #1310720	; 0x140000
d001d018:	95044155 	strls	r4, [r4, #-341]	; 0xfffffeab
d001d01c:	e88dcb0f 	stm	sp, {r0, r1, r2, r3, r8, r9, fp, lr, pc}
d001d020:	ab3c000f 	blge	0xd0f1d064
d001d024:	f7f7cb0f 			; <UNDEFINED> instruction: 0xf7f7cb0f
d001d028:	6da3f987 			; <UNDEFINED> instruction: 0x6da3f987
d001d02c:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001d030:	f8dfadfd 			; <UNDEFINED> instruction: 0xf8dfadfd
d001d034:	213b297c 	teqcs	fp, ip, ror r9
d001d038:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d001d03c:	ff0df7f5 			; <UNDEFINED> instruction: 0xff0df7f5
d001d040:	6da3e5f4 	cfstr32vs	mvfx14, [r3, #976]!	; 0x3d0
d001d044:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001d048:	f8dfadf1 			; <UNDEFINED> instruction: 0xf8dfadf1
d001d04c:	447b3968 	ldrbtmi	r3, [fp], #-2408	; 0xfffff698
d001d050:	9818e9c4 	ldmdals	r8, {r2, r6, r7, r8, fp, sp, lr, pc}
d001d054:	3b16e9c4 	blcc	0xd05d776c
d001d058:	f8dfe76a 			; <UNDEFINED> instruction: 0xf8dfe76a
d001d05c:	f44f595c 	vst2.16	{d21,d23}, [pc :64], ip
d001d060:	447d7183 	ldrbtmi	r7, [sp], #-387	; 0xfffffe7d
d001d064:	f7f54628 			; <UNDEFINED> instruction: 0xf7f54628
d001d068:	b150feea 	cmplt	r0, sl, ror #29	; <UNPREDICTABLE>
d001d06c:	4350f505 	cmpmi	r0, #20971520	; 0x1400000	; <UNPREDICTABLE>
d001d070:	681b331c 	ldmdavs	fp, {r2, r3, r4, r8, r9, ip, sp}
d001d074:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001d078:	6f28add9 	svcvs	0x0028add9
d001d07c:	fc70f7f7 	ldc2l	7, cr15, [r0], #-988	; 0xfffffc24
d001d080:	f44fe5d4 	vst3.<illegal width 64>	{d30,d32,d34}, [pc :64], r4
d001d084:	46287188 	strtmi	r7, [r8], -r8, lsl #3
d001d088:	fed9f7f5 	mrc2	7, 6, pc, cr9, cr5, {7}
d001d08c:	7185f44f 	orrvc	pc, r5, pc, asr #8
d001d090:	46289014 			; <UNDEFINED> instruction: 0x46289014
d001d094:	fed3f7f5 	mrc2	7, 6, pc, cr3, cr5, {7}
d001d098:	f2406aea 	vpmax.s8	q11, q8, q13
d001d09c:	4604131b 			; <UNDEFINED> instruction: 0x4604131b
d001d0a0:	429a4628 	addsmi	r4, sl, #40, 12	; 0x2800000
d001d0a4:	f7f6d14c 			; <UNDEFINED> instruction: 0xf7f6d14c
d001d0a8:	2800f9cb 	stmdacs	r0, {r0, r1, r3, r6, r7, r8, fp, ip, sp, lr, pc}
d001d0ac:	adbef43f 	cfldrsge	mvf15, [lr, #252]!	; 0xfc
d001d0b0:	4628213b 			; <UNDEFINED> instruction: 0x4628213b
d001d0b4:	fec3f7f5 	mcr2	7, 6, pc, cr3, cr5, {7}	; <UNPREDICTABLE>
d001d0b8:	28004606 	stmdacs	r0, {r1, r2, r9, sl, lr}
d001d0bc:	adb6f47f 	cfldrsge	mvf15, [r6, #508]!	; 0x1fc
d001d0c0:	0c18f105 	ldfeqd	f7, [r8], {5}
d001d0c4:	f8d5af3c 			; <UNDEFINED> instruction: 0xf8d5af3c
d001d0c8:	f8d5a024 			; <UNDEFINED> instruction: 0xf8d5a024
d001d0cc:	f8959028 			; <UNDEFINED> instruction: 0xf8959028
d001d0d0:	e8bc8030 	ldm	ip!, {r4, r5, pc}
d001d0d4:	c70f000f 	strgt	r0, [pc, -pc]
d001d0d8:	000fe89c 	muleq	pc, ip, r8	; <UNPREDICTABLE>
d001d0dc:	000fe887 	andeq	lr, pc, r7, lsl #17
d001d0e0:	28d8f8df 	ldmcs	r8, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d001d0e4:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d001d0e8:	6b6f4628 	blvs	0xd1bee990
d001d0ec:	f7f5447a 			; <UNDEFINED> instruction: 0xf7f5447a
d001d0f0:	f10dfeb4 			; <UNDEFINED> instruction: 0xf10dfeb4
d001d0f4:	28000cf0 	stmdacs	r0, {r4, r5, r6, r7, sl, fp}
d001d0f8:	ad98f43f 	cfldrsge	mvf15, [r8, #252]	; 0xfc
d001d0fc:	43239b14 			; <UNDEFINED> instruction: 0x43239b14
d001d100:	6dabd10c 	stfvsd	f5, [fp, #48]!	; 0x30
d001d104:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001d108:	f8dfad91 			; <UNDEFINED> instruction: 0xf8dfad91
d001d10c:	66af38b4 			; <UNDEFINED> instruction: 0x66af38b4
d001d110:	e9c5447b 	stmib	r5, {r0, r1, r3, r4, r5, r6, sl, lr}^
d001d114:	e9c59818 	stmib	r5, {r3, r4, fp, ip, pc}^
d001d118:	e5873a16 	str	r3, [r7, #2582]	; 0xa16
d001d11c:	f8cdab40 			; <UNDEFINED> instruction: 0xf8cdab40
d001d120:	f88d9100 			; <UNDEFINED> instruction: 0xf88d9100
d001d124:	97438108 	strbls	r8, [r3, -r8, lsl #2]
d001d128:	96049405 	strls	r9, [r4], -r5, lsl #8
d001d12c:	a0fcf8cd 	rscsge	pc, ip, sp, asr #17
d001d130:	e88dcb0f 	stm	sp, {r0, r1, r2, r3, r8, r9, fp, lr, pc}
d001d134:	e89c000f 	ldm	ip, {r0, r1, r2, r3}
d001d138:	f7fe000f 			; <UNDEFINED> instruction: 0xf7fe000f
d001d13c:	e575fe23 	ldrb	pc, [r5, #-3619]!	; 0xfffff1dd	; <UNPREDICTABLE>
d001d140:	fb4cf7f3 	blx	0xd135b116
d001d144:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d001d148:	b12481d5 	ldrdlt	r8, [r4, -r5]!
d001d14c:	1874f8df 	ldmdane	r4!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d001d150:	46284479 			; <UNDEFINED> instruction: 0x46284479
d001d154:	a934e265 	ldmdbge	r4!, {r0, r2, r5, r6, r9, sp, lr, pc}
d001d158:	94344628 	ldrtls	r4, [r4], #-1576	; 0xfffff9d8
d001d15c:	f87af7f6 			; <UNDEFINED> instruction: 0xf87af7f6
d001d160:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001d164:	f105ad63 			; <UNDEFINED> instruction: 0xf105ad63
d001d168:	212a0718 			; <UNDEFINED> instruction: 0x212a0718
d001d16c:	ae3c4628 	cfmsuba32ge	mvax1, mvax4, mvfx12, mvfx8
d001d170:	fe65f7f5 	mcr2	7, 3, pc, cr5, cr5, {7}	; <UNPREDICTABLE>
d001d174:	f8954604 			; <UNDEFINED> instruction: 0xf8954604
d001d178:	cf0fa030 	svcgt	0x000fa030
d001d17c:	e897c60f 	ldm	r7, {r0, r1, r2, r3, r9, sl, lr, pc}
d001d180:	e886000f 	stm	r6, {r0, r1, r2, r3}
d001d184:	6a6b000f 	bvs	0xd1add1c8
d001d188:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d001d18c:	2838f8df 	ldmdacs	r8!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d001d190:	93114628 	tstls	r1, #40, 12	; 0x2800000
d001d194:	447a6aab 	ldrbtmi	r6, [sl], #-2731	; 0xfffff555
d001d198:	6b6b9310 	blvs	0xd1b01de0
d001d19c:	9b06e9d5 	blls	0xd01d78f8
d001d1a0:	f7f5930f 			; <UNDEFINED> instruction: 0xf7f5930f
d001d1a4:	2800fe5a 	stmdacs	r0, {r1, r3, r4, r6, r9, sl, fp, ip, sp, lr, pc}
d001d1a8:	ad40f43f 	cfstrdge	mvd15, [r0, #-252]	; 0xffffff04
d001d1ac:	2b286aeb 	blcs	0xd0a37d60
d001d1b0:	9b34d14a 	blls	0xd0d516e0
d001d1b4:	ae3c2c00 	cdpge	12, 3, cr2, cr12, cr0, {0}
d001d1b8:	9317ac24 	tstls	r7, #36, 24	; 0x2400
d001d1bc:	2305bf14 	movwcs	fp, #24340	; 0x5f14
d001d1c0:	f88d2304 			; <UNDEFINED> instruction: 0xf88d2304
d001d1c4:	4625a108 	strtmi	sl, [r5], -r8, lsl #2
d001d1c8:	9b119313 	blls	0xd0481e1c
d001d1cc:	9b10933f 	blls	0xd0441ed0
d001d1d0:	9b0f9340 	blls	0xd0401ed8
d001d1d4:	9b3ce9cd 	blls	0xd0f57910
d001d1d8:	ce0f9343 	cdpgt	3, 0, cr9, cr15, cr3, {2}
d001d1dc:	e896c50f 	ldm	r6, {r0, r1, r2, r3, r8, sl, lr, pc}
d001d1e0:	e885000f 	stm	r5, {r0, r1, r2, r3}
d001d1e4:	9b11000f 	blls	0xd045d228
d001d1e8:	f8cdae2c 			; <UNDEFINED> instruction: 0xf8cdae2c
d001d1ec:	9327b094 			; <UNDEFINED> instruction: 0x9327b094
d001d1f0:	93289b10 			; <UNDEFINED> instruction: 0x93289b10
d001d1f4:	f88d9b0f 			; <UNDEFINED> instruction: 0xf88d9b0f
d001d1f8:	932ba0a8 			; <UNDEFINED> instruction: 0x932ba0a8
d001d1fc:	c60fcc0f 	strgt	ip, [pc], -pc, lsl #24
d001d200:	000fe895 	muleq	pc, r5, r8	; <UNPREDICTABLE>
d001d204:	000fe886 	andeq	lr, pc, r6, lsl #17
d001d208:	47c0f8df 			; <UNDEFINED> instruction: 0x47c0f8df
d001d20c:	f8df2128 			; <UNDEFINED> instruction: 0xf8df2128
d001d210:	447c27c0 	ldrbtmi	r2, [ip], #-1984	; 0xfffff840
d001d214:	4620447a 			; <UNDEFINED> instruction: 0x4620447a
d001d218:	fe1ff7f5 	mrc2	7, 0, pc, cr15, cr5, {7}
d001d21c:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001d220:	465aad05 	ldrbmi	sl, [sl], -r5, lsl #26
d001d224:	46204649 	strtmi	r4, [r0], -r9, asr #12
d001d228:	fab3f7f3 	blx	0xced1b1fc
d001d22c:	f2c02800 	vmlal.s8	q9, d0, d0
d001d230:	f8df8230 			; <UNDEFINED> instruction: 0xf8df8230
d001d234:	447b37a0 	ldrbtmi	r3, [fp], #-1952	; 0xfffff860
d001d238:	2a006d9a 	bcs	0xd00388a8
d001d23c:	acf6f47f 	cfldrdge	mvd15, [r6], #508	; 0x1fc
d001d240:	2794f8df 			; <UNDEFINED> instruction: 0x2794f8df
d001d244:	e01c447a 	ands	r4, ip, sl, ror r4
d001d248:	6dabb17c 	stfvsd	f3, [fp, #496]!	; 0x1f0
d001d24c:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001d250:	f8dfaced 			; <UNDEFINED> instruction: 0xf8dfaced
d001d254:	447b3788 	ldrbtmi	r3, [fp], #-1928	; 0xfffff878
d001d258:	9b1165ab 	blls	0xd047690c
d001d25c:	9b1065eb 	blls	0xd0436a10
d001d260:	3a18e9c5 	bcc	0xd065797c
d001d264:	66ab9b0f 	strtvs	r9, [fp], pc, lsl #22
d001d268:	9b14e4e0 	blls	0xd05565f0
d001d26c:	6dabb98b 			; <UNDEFINED> instruction: 0x6dabb98b
d001d270:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001d274:	f8dfacdb 			; <UNDEFINED> instruction: 0xf8dfacdb
d001d278:	f8df3768 			; <UNDEFINED> instruction: 0xf8df3768
d001d27c:	447b2768 	ldrbtmi	r2, [fp], #-1896	; 0xfffff898
d001d280:	659a447a 	ldrvs	r4, [sl, #1146]	; 0x47a
d001d284:	65da9a11 	ldrbvs	r9, [sl, #2577]	; 0xa11
d001d288:	e9c39a10 	stmib	r3, {r4, r9, fp, ip, pc}^
d001d28c:	9a0f2a18 	bls	0xd03e7af4
d001d290:	4628e03e 			; <UNDEFINED> instruction: 0x4628e03e
d001d294:	f7f5215b 			; <UNDEFINED> instruction: 0xf7f5215b
d001d298:	9b34fdd2 	blls	0xd0d5c9e8
d001d29c:	721af44f 	andsvc	pc, sl, #1325400064	; 0x4f000000
d001d2a0:	fb024680 	blx	0xd00aecaa
d001d2a4:	f5055503 			; <UNDEFINED> instruction: 0xf5055503
d001d2a8:	8d2e3568 	cfstr32hi	mvfx3, [lr, #-416]!	; 0xfffffe60
d001d2ac:	d0762800 	rsbsle	r2, r6, r0, lsl #16
d001d2b0:	5734f8df 			; <UNDEFINED> instruction: 0x5734f8df
d001d2b4:	6aea447d 	bvs	0xcfaae4b0
d001d2b8:	7281f5a2 	addvc	pc, r1, #679477248	; 0x28800000
d001d2bc:	d8082a01 	stmdale	r8, {r0, r9, fp, sp}
d001d2c0:	b1376a2f 	teqlt	r7, pc, lsr #20
d001d2c4:	f44f00b1 	vst4.32	{d16-d19}, [pc :256], r1
d001d2c8:	fbb21280 	blx	0xceca1cd2
d001d2cc:	4297f2f1 	addsmi	pc, r7, #268435471	; 0x1000000f
d001d2d0:	f8dfd924 			; <UNDEFINED> instruction: 0xf8dfd924
d001d2d4:	f44f2718 	vst1.8	{d18}, [pc :64], r8
d001d2d8:	447a711a 	ldrbtmi	r7, [sl], #-282	; 0xfffffee6
d001d2dc:	2303fb01 	movwcs	pc, #15105	; 0x3b01	; <UNPREDICTABLE>
d001d2e0:	3368f503 	msrcc	SPSR_f, #12582912	; 0xc00000
d001d2e4:	302bf893 	mlacc	fp, r3, r8, pc	; <UNPREDICTABLE>
d001d2e8:	f8dfb9a3 			; <UNDEFINED> instruction: 0xf8dfb9a3
d001d2ec:	447c4704 	ldrbtmi	r4, [ip], #-1796	; 0xfffff8fc
d001d2f0:	3700f8df 			; <UNDEFINED> instruction: 0x3700f8df
d001d2f4:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d001d2f8:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d001d2fc:	6a58ac97 	bvs	0xd1648560
d001d300:	f8936a99 			; <UNDEFINED> instruction: 0xf8936a99
d001d304:	6b5a5030 	blvs	0xd16b13cc
d001d308:	4016e9c3 	andsmi	lr, r6, r3, asr #19
d001d30c:	1518e9c3 	ldrne	lr, [r8, #-2499]	; 0xfffff63d
d001d310:	e48b669a 	str	r6, [fp], #1690	; 0x69a
d001d314:	46e0f8df 	usatmi	pc, #0, pc, asr #17	; <UNPREDICTABLE>
d001d318:	e7e9447c 			; <UNDEFINED> instruction: 0xe7e9447c
d001d31c:	f7f54628 			; <UNDEFINED> instruction: 0xf7f54628
d001d320:	f8dffd73 			; <UNDEFINED> instruction: 0xf8dffd73
d001d324:	215d26d8 	ldrsbcs	r2, [sp, #-104]	; 0xffffff98
d001d328:	447a4628 	ldrbtmi	r4, [sl], #-1576	; 0xfffff9d8
d001d32c:	fd95f7f5 	ldc2	7, cr15, [r5, #980]	; 0x3d4
d001d330:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001d334:	f8dfac7b 			; <UNDEFINED> instruction: 0xf8dfac7b
d001d338:	213d06c8 	teqcs	sp, r8, asr #13
d001d33c:	4478437e 	ldrbtmi	r4, [r8], #-894	; 0xfffffc82
d001d340:	159ff500 	ldrne	pc, [pc, #1280]	; 0xd001d848
d001d344:	55f1f505 	ldrbpl	pc, [r1, #1285]!	; 0x505	; <UNPREDICTABLE>
d001d348:	9312682b 	tstls	r2, #2818048	; 0x2b0000
d001d34c:	fd77f7f5 	ldc2l	7, cr15, [r7, #-980]!	; 0xfffffc2c
d001d350:	682bb130 	stmdavs	fp!, {r4, r5, r8, ip, sp, pc}
d001d354:	2380f5c3 	orrcs	pc, r0, #817889280	; 0x30c00000
d001d358:	d922429e 	stmdble	r2!, {r1, r2, r3, r4, r7, r9, lr}
d001d35c:	fde8f7f6 	stc2l	7, cr15, [r8, #984]!	; 0x3d8
d001d360:	56a0f8df 	ssatpl	pc, #1, pc, asr #17	; <UNPREDICTABLE>
d001d364:	f8df213b 			; <UNDEFINED> instruction: 0xf8df213b
d001d368:	447d26a0 	ldrbtmi	r2, [sp], #-1696	; 0xfffff960
d001d36c:	4628447a 			; <UNDEFINED> instruction: 0x4628447a
d001d370:	fd73f7f5 	ldc2l	7, cr15, [r3, #-980]!	; 0xfffffc2c
d001d374:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001d378:	465aac59 			; <UNDEFINED> instruction: 0x465aac59
d001d37c:	46284649 	strtmi	r4, [r8], -r9, asr #12
d001d380:	fa07f7f3 	blx	0xd021b354
d001d384:	db2e2800 	blle	0xd0ba738c
d001d388:	3680f8df 	pkhtbcc	pc, r0, pc, asr #17	; <UNPREDICTABLE>
d001d38c:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d001d390:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d001d394:	f8dfac4b 			; <UNDEFINED> instruction: 0xf8dfac4b
d001d398:	447a2678 	ldrbtmi	r2, [sl], #-1656	; 0xfffff988
d001d39c:	2701e771 	smlsdxcs	r1, r1, r7, lr
d001d3a0:	4630e7c9 	ldrtmi	lr, [r0], -r9, asr #15
d001d3a4:	fd8cf7f6 	stc2	7, cr15, [ip, #984]	; 0x3d8
d001d3a8:	28004605 	stmdacs	r0, {r0, r2, r9, sl, lr}
d001d3ac:	ac3ef43f 	cfldrsge	mvf15, [lr], #-252	; 0xffffff04
d001d3b0:	f1b89834 			; <UNDEFINED> instruction: 0xf1b89834
d001d3b4:	d0100f00 	andsle	r0, r0, r0, lsl #30
d001d3b8:	46012200 	strmi	r2, [r1], -r0, lsl #4
d001d3bc:	4638462b 	ldrtmi	r4, [r8], -fp, lsr #12
d001d3c0:	f7fc9200 			; <UNDEFINED> instruction: 0xf7fc9200
d001d3c4:	2300ff79 	movwcs	pc, #3961	; 0xf79	; <UNPREDICTABLE>
d001d3c8:	d0c9429e 	smullle	r4, r9, lr, r2
d001d3cc:	2023f855 	eorcs	pc, r3, r5, asr r8	; <UNPREDICTABLE>
d001d3d0:	f0412a00 			; <UNDEFINED> instruction: 0xf0412a00
d001d3d4:	330180bb 	movwcc	r8, #4283	; 0x10bb
d001d3d8:	2301e7f6 	movwcs	lr, #6134	; 0x17f6
d001d3dc:	4641462a 	strbmi	r4, [r1], -sl, lsr #12
d001d3e0:	fe38f7fc 	mrc2	7, 1, pc, cr8, cr12, {7}
d001d3e4:	465ae7ef 	ldrbmi	lr, [sl], -pc, ror #15
d001d3e8:	46284649 	strtmi	r4, [r8], -r9, asr #12
d001d3ec:	f9acf7f3 			; <UNDEFINED> instruction: 0xf9acf7f3
d001d3f0:	dac92800 	ble	0xcf2673f8
d001d3f4:	4649465a 			; <UNDEFINED> instruction: 0x4649465a
d001d3f8:	f7f34628 			; <UNDEFINED> instruction: 0xf7f34628
d001d3fc:	2800fa0f 	stmdacs	r0, {r0, r1, r2, r3, r9, fp, ip, sp, lr, pc}
d001d400:	f505dac2 			; <UNDEFINED> instruction: 0xf505dac2
d001d404:	00b33267 	adcseq	r3, r3, r7, ror #4
d001d408:	11c4f8d2 	ldrdne	pc, [r4, #130]	; 0x82
d001d40c:	d0082980 	andle	r2, r8, r0, lsl #19
d001d410:	327ff505 	rsbscc	pc, pc, #20971520	; 0x1400000
d001d414:	f8d2b984 			; <UNDEFINED> instruction: 0xf8d2b984
d001d418:	f5c3521c 			; <UNDEFINED> instruction: 0xf5c3521c
d001d41c:	42851080 	addmi	r1, r5, #128	; 0x80
d001d420:	f8dfd961 			; <UNDEFINED> instruction: 0xf8dfd961
d001d424:	447b35f0 	ldrbtmi	r3, [fp], #-1520	; 0xfffffa10
d001d428:	2a006d9a 	bcs	0xd0038a98
d001d42c:	abfef47f 	blge	0xcffda630
d001d430:	25e4f8df 	strbcs	pc, [r4, #2271]!	; 0x8df	; <UNPREDICTABLE>
d001d434:	e724447a 			; <UNDEFINED> instruction: 0xe724447a
d001d438:	5218f8d2 	andspl	pc, r8, #13762560	; 0xd20000
d001d43c:	f0253503 			; <UNDEFINED> instruction: 0xf0253503
d001d440:	442b0503 	strtmi	r0, [fp], #-1283	; 0xfffffafd
d001d444:	3218f8c2 	andscc	pc, r8, #12713984	; 0xc20000
d001d448:	35d0f8df 	ldrbcc	pc, [r0, #2271]	; 0x8df	; <UNPREDICTABLE>
d001d44c:	0f00f1b8 	svceq	0x0000f1b8
d001d450:	0001f101 	andeq	pc, r1, r1, lsl #2
d001d454:	f884fa5f 			; <UNDEFINED> instruction: 0xf884fa5f
d001d458:	f503447b 			; <UNDEFINED> instruction: 0xf503447b
d001d45c:	f8c23267 			; <UNDEFINED> instruction: 0xf8c23267
d001d460:	bf1401c4 	svclt	0x001401c4
d001d464:	220f2211 	andcs	r2, pc, #268435457	; 0x10000001
d001d468:	92152c00 	andsls	r2, r5, #0, 24
d001d46c:	2600bf08 	strcs	fp, [r0], -r8, lsl #30
d001d470:	92137a1a 	andsls	r7, r3, #106496	; 0x1a000
d001d474:	20d0f89d 	smullscs	pc, r0, sp, r8	; <UNPREDICTABLE>
d001d478:	223c9214 	eorscs	r9, ip, #20, 4	; 0x40000001
d001d47c:	3401fb02 	strcc	pc, [r1], #-2818	; 0xfffff4fe
d001d480:	f5042100 			; <UNDEFINED> instruction: 0xf5042100
d001d484:	f504345f 			; <UNDEFINED> instruction: 0xf504345f
d001d488:	46187371 			; <UNDEFINED> instruction: 0x46187371
d001d48c:	fa10f002 	blx	0xd045949c
d001d490:	f10d9a11 			; <UNDEFINED> instruction: 0xf10d9a11
d001d494:	f88d0ef0 			; <UNDEFINED> instruction: 0xf88d0ef0
d001d498:	923fa108 	eorsls	sl, pc, #8, 2
d001d49c:	9a104684 	bls	0xd042eeb4
d001d4a0:	53e8f8c4 	mvnpl	pc, #196, 16	; 0xc40000
d001d4a4:	9a0f9240 	bls	0xd0401dac
d001d4a8:	9b3ce9cd 	blls	0xd0f57be4
d001d4ac:	e8be9243 	ldm	lr!, {r0, r1, r6, r9, ip, pc}
d001d4b0:	e8ac000f 	stmia	ip!, {r0, r1, r2, r3}
d001d4b4:	e89e000f 	ldm	lr, {r0, r1, r2, r3}
d001d4b8:	e88c000f 	stm	ip, {r0, r1, r2, r3}
d001d4bc:	9b15000f 	blls	0xd055d500
d001d4c0:	33ecf884 	mvncc	pc, #132, 16	; 0x840000
d001d4c4:	f8849b13 			; <UNDEFINED> instruction: 0xf8849b13
d001d4c8:	9b1433ed 	blls	0xd052a484
d001d4cc:	33eef884 	mvncc	pc, #132, 16	; 0x840000
d001d4d0:	83eff884 	mvnhi	pc, #132, 16	; 0x840000
d001d4d4:	f8c49b12 			; <UNDEFINED> instruction: 0xf8c49b12
d001d4d8:	f8c463f8 			; <UNDEFINED> instruction: 0xf8c463f8
d001d4dc:	f8c433f4 			; <UNDEFINED> instruction: 0xf8c433f4
d001d4e0:	f7ff73fc 			; <UNDEFINED> instruction: 0xf7ff73fc
d001d4e4:	3503bba3 	strcc	fp, [r3, #-2979]	; 0xfffff45d
d001d4e8:	0503f025 	streq	pc, [r3, #-37]	; 0xffffffdb
d001d4ec:	f8c2442b 			; <UNDEFINED> instruction: 0xf8c2442b
d001d4f0:	e7a9321c 			; <UNDEFINED> instruction: 0xe7a9321c
d001d4f4:	b9239b14 	stmdblt	r3!, {r2, r4, r8, r9, fp, ip, pc}
d001d4f8:	1109f240 	tstne	r9, r0, asr #4	; <UNPREDICTABLE>
d001d4fc:	f7f54628 			; <UNDEFINED> instruction: 0xf7f54628
d001d500:	f8dffc9e 			; <UNDEFINED> instruction: 0xf8dffc9e
d001d504:	f44f051c 	vst3.8	{d16,d18,d20}, [pc :64], ip
d001d508:	44787184 	ldrbtmi	r7, [r8], #-388	; 0xfffffe7c
d001d50c:	fc97f7f5 	ldc2	7, cr15, [r7], {245}	; 0xf5
d001d510:	28004605 	stmdacs	r0, {r0, r2, r9, sl, lr}
d001d514:	8089f040 	addhi	pc, r9, r0, asr #32
d001d518:	0508f8df 	streq	pc, [r8, #-2271]	; 0xfffff721
d001d51c:	f7f74478 			; <UNDEFINED> instruction: 0xf7f74478
d001d520:	4682fb51 	pkhtbmi	pc, r2, r1, asr #22	; <UNPREDICTABLE>
d001d524:	f0402800 			; <UNDEFINED> instruction: 0xf0402800
d001d528:	9b148083 	blls	0xd053d73c
d001d52c:	f8dfb9a3 			; <UNDEFINED> instruction: 0xf8dfb9a3
d001d530:	f24054f8 	vqshl.s8	<illegal reg q10.5>, q12, q8
d001d534:	447d1107 	ldrbtmi	r1, [sp], #-263	; 0xfffffef9
d001d538:	f7f54628 			; <UNDEFINED> instruction: 0xf7f54628
d001d53c:	2800fc80 	stmdacs	r0, {r7, sl, fp, ip, sp, lr, pc}
d001d540:	f8dfd04b 			; <UNDEFINED> instruction: 0xf8dfd04b
d001d544:	212a04e8 	smulwtcs	sl, r8, r4
d001d548:	f7f54478 			; <UNDEFINED> instruction: 0xf7f54478
d001d54c:	2800fc78 	stmdacs	r0, {r3, r4, r5, r6, sl, fp, ip, sp, lr, pc}
d001d550:	2500d074 	strcs	sp, [r0, #-116]	; 0xffffff8c
d001d554:	e0152303 	ands	r2, r5, r3, lsl #6
d001d558:	04d4f8df 	ldrbeq	pc, [r4], #2271	; 0x8df	; <UNPREDICTABLE>
d001d55c:	f7f74478 			; <UNDEFINED> instruction: 0xf7f74478
d001d560:	2800fb31 	stmdacs	r0, {r0, r4, r5, r8, r9, fp, ip, sp, lr, pc}
d001d564:	f8dfd166 			; <UNDEFINED> instruction: 0xf8dfd166
d001d568:	447804cc 	ldrbtmi	r0, [r8], #-1228	; 0xfffffb34
d001d56c:	fb2af7f7 	blx	0xd0adb552
d001d570:	f8dfb930 			; <UNDEFINED> instruction: 0xf8dfb930
d001d574:	447804c4 	ldrbtmi	r0, [r8], #-1220	; 0xfffffb3c
d001d578:	fb24f7f7 	blx	0xd095b55e
d001d57c:	d0d62800 	sbcsle	r2, r6, r0, lsl #16
d001d580:	23002505 	movwcs	r2, #1285	; 0x505
d001d584:	f8df9313 			; <UNDEFINED> instruction: 0xf8df9313
d001d588:	af2c64b4 	svcge	0x002c64b4
d001d58c:	f106447e 			; <UNDEFINED> instruction: 0xf106447e
d001d590:	f8960c18 			; <UNDEFINED> instruction: 0xf8960c18
d001d594:	e8bca030 	ldm	ip!, {r4, r5, sp, pc}
d001d598:	c70f000f 	strgt	r0, [pc, -pc]
d001d59c:	000fe89c 	muleq	pc, ip, r8	; <UNPREDICTABLE>
d001d5a0:	000fe887 	andeq	lr, pc, r7, lsl #17
d001d5a4:	f2406a73 	vpmin.s8	q11, q0, <illegal reg q9.5>
d001d5a8:	f8df1101 			; <UNDEFINED> instruction: 0xf8df1101
d001d5ac:	46302494 			; <UNDEFINED> instruction: 0x46302494
d001d5b0:	6ab39311 	bvs	0xced021fc
d001d5b4:	9310447a 	tstls	r0, #2046820352	; 0x7a000000
d001d5b8:	e9d66b73 	ldmib	r6, {r0, r1, r4, r5, r6, r8, r9, fp, sp, lr}^
d001d5bc:	930f9b06 	movwls	r9, #64262	; 0xfb06
d001d5c0:	fc4bf7f5 	mcrr2	7, 15, pc, fp, cr5	; <UNPREDICTABLE>
d001d5c4:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001d5c8:	9b14ab31 	blls	0xd0548294
d001d5cc:	2c00bbcb 			; <UNDEFINED> instruction: 0x2c00bbcb
d001d5d0:	87c8f040 	strbhi	pc, [r8, r0, asr #32]	; <UNPREDICTABLE>
d001d5d4:	931723ff 	tstls	r7, #-67108861	; 0xfc000003
d001d5d8:	6aeae616 	bvs	0xcfad6e38
d001d5dc:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d001d5e0:	d118429a 			; <UNDEFINED> instruction: 0xd118429a
d001d5e4:	e9d54628 	ldmib	r5, {r3, r5, r9, sl, lr}^
d001d5e8:	f7f31206 			; <UNDEFINED> instruction: 0xf7f31206
d001d5ec:	2800f8d2 	stmdacs	r0, {r1, r4, r6, r7, fp, ip, sp, lr, pc}
d001d5f0:	4628db11 			; <UNDEFINED> instruction: 0x4628db11
d001d5f4:	1206e9d5 	andne	lr, r6, #3489792	; 0x354000
d001d5f8:	f8cbf7f3 			; <UNDEFINED> instruction: 0xf8cbf7f3
d001d5fc:	fb032324 	blx	0xd00e6296
d001d600:	f5005000 			; <UNDEFINED> instruction: 0xf5005000
d001d604:	f8903075 			; <UNDEFINED> instruction: 0xf8903075
d001d608:	2bff33ac 	blcs	0xcffea4c0
d001d60c:	4628d103 	strtmi	sp, [r8], -r3, lsl #2
d001d610:	fbfaf7f5 	blx	0xcfedb5ee
d001d614:	f8dfe795 			; <UNDEFINED> instruction: 0xf8dfe795
d001d618:	f8df142c 			; <UNDEFINED> instruction: 0xf8df142c
d001d61c:	4479042c 	ldrbtmi	r0, [r9], #-1068	; 0xfffffbd4
d001d620:	f7f24478 			; <UNDEFINED> instruction: 0xf7f24478
d001d624:	f7fffdc1 			; <UNDEFINED> instruction: 0xf7fffdc1
d001d628:	2500bb01 	strcs	fp, [r0, #-2817]	; 0xfffff4ff
d001d62c:	e7a92301 	str	r2, [r9, r1, lsl #6]!
d001d630:	e7a72302 	str	r2, [r7, r2, lsl #6]!
d001d634:	f8cd2501 			; <UNDEFINED> instruction: 0xf8cd2501
d001d638:	e7a4a04c 	str	sl, [r4, ip, asr #32]!
d001d63c:	90134605 	andsls	r4, r3, r5, lsl #12
d001d640:	9b13e7a1 	blls	0xd05174cc
d001d644:	2d00b93b 	vstrcs.16	s22, [r0, #-118]	; 0xffffff8a	; <UNPREDICTABLE>
d001d648:	8748f040 	strbhi	pc, [r8, -r0, asr #32]	; <UNPREDICTABLE>
d001d64c:	447b4bff 	ldrbtmi	r4, [fp], #-3071	; 0xfffff401
d001d650:	2b286adb 	blcs	0xd0a381c4
d001d654:	2c00d10a 	stfcsd	f5, [r0], {10}
d001d658:	4bfdd0bc 	blmi	0xcff91950
d001d65c:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d001d660:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d001d664:	4afbaae3 	bmi	0xcff081f8
d001d668:	e60a447a 			; <UNDEFINED> instruction: 0xe60a447a
d001d66c:	f88d9b11 			; <UNDEFINED> instruction: 0xf88d9b11
d001d670:	932fa0c8 			; <UNDEFINED> instruction: 0x932fa0c8
d001d674:	94059b10 	strls	r9, [r5], #-2832	; 0xfffff4f0
d001d678:	9b0f9330 	blls	0xd0402340
d001d67c:	93339504 	teqls	r3, #4, 10	; 0x1000000
d001d680:	cb0fab30 	blgt	0xd0408348
d001d684:	000fe88d 	andeq	lr, pc, sp, lsl #17
d001d688:	e9cdab2c 	stmib	sp, {r2, r3, r5, r8, r9, fp, sp, pc}^
d001d68c:	cb0f9b2c 	blgt	0xd0404344
d001d690:	465ae553 			; <UNDEFINED> instruction: 0x465ae553
d001d694:	46204649 	strtmi	r4, [r0], -r9, asr #12
d001d698:	f856f7f3 			; <UNDEFINED> instruction: 0xf856f7f3
d001d69c:	f6bf2800 			; <UNDEFINED> instruction: 0xf6bf2800
d001d6a0:	4aedadc8 	bmi	0xcfb88dc8
d001d6a4:	46484659 			; <UNDEFINED> instruction: 0x46484659
d001d6a8:	f7f3447a 			; <UNDEFINED> instruction: 0xf7f3447a
d001d6ac:	bb40f8e3 	bllt	0xd105ba40
d001d6b0:	46594aea 	ldrbmi	r4, [r9], -sl, ror #21
d001d6b4:	447a4648 	ldrbtmi	r4, [sl], #-1608	; 0xfffff9b8
d001d6b8:	f8dcf7f3 			; <UNDEFINED> instruction: 0xf8dcf7f3
d001d6bc:	4ae8bb18 	bmi	0xcfa4c324
d001d6c0:	46484659 			; <UNDEFINED> instruction: 0x46484659
d001d6c4:	f7f3447a 			; <UNDEFINED> instruction: 0xf7f3447a
d001d6c8:	2800f8d5 	stmdacs	r0, {r0, r2, r4, r6, r7, fp, ip, sp, lr, pc}
d001d6cc:	2300bf0c 	movwcs	fp, #3852	; 0xf0c
d001d6d0:	4ae4230c 	bmi	0xcf926308
d001d6d4:	46484659 			; <UNDEFINED> instruction: 0x46484659
d001d6d8:	447a9315 	ldrbtmi	r9, [sl], #-789	; 0xfffffceb
d001d6dc:	f8caf7f3 			; <UNDEFINED> instruction: 0xf8caf7f3
d001d6e0:	901b9b15 	andsls	r9, fp, r5, lsl fp
d001d6e4:	d0104303 	andsle	r4, r0, r3, lsl #6
d001d6e8:	9a139b14 	bls	0xd0504340
d001d6ec:	d00c4313 	andle	r4, ip, r3, lsl r3
d001d6f0:	447b4bdd 	ldrbtmi	r4, [fp], #-3037	; 0xfffff423
d001d6f4:	2a006d9a 	bcs	0xd0038d64
d001d6f8:	aa98f47f 	bge	0xce65a8fc
d001d6fc:	447a4adb 	ldrbtmi	r4, [sl], #-2779	; 0xfffff525
d001d700:	2304e5bf 	movwcs	lr, #17855	; 0x45bf
d001d704:	2308e7e5 	movwcs	lr, #34789	; 0x87e5
d001d708:	9b15e7e3 	blls	0xd059769c
d001d70c:	ac202500 	cfstr32ge	mvfx2, [r0], #-0
d001d710:	95202b04 	strls	r2, [r0, #-2820]!	; 0xfffff4fc
d001d714:	5084f88d 	addpl	pc, r4, sp, lsl #17
d001d718:	f88d9522 			; <UNDEFINED> instruction: 0xf88d9522
d001d71c:	d149508c 	smlalbble	r5, r9, ip, r0
d001d720:	f44f4dd3 			; <UNDEFINED> instruction: 0xf44f4dd3
d001d724:	4ad37185 	bmi	0xcf4f9d40
d001d728:	447a447d 	ldrbtmi	r4, [sl], #-1149	; 0xfffffb83
d001d72c:	92124628 	andsls	r4, r2, #40, 12	; 0x2800000
d001d730:	fb93f7f5 	blx	0xce51b70e
d001d734:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001d738:	9a12aa79 	bls	0xd04c8124
d001d73c:	110bf240 	tstne	fp, r0, asr #4	; <UNPREDICTABLE>
d001d740:	f7f54628 			; <UNDEFINED> instruction: 0xf7f54628
d001d744:	2800fb8a 	stmdacs	r0, {r1, r3, r7, r8, r9, fp, ip, sp, lr, pc}
d001d748:	aa70f43f 	bge	0xd1c5a84c
d001d74c:	212a9a12 			; <UNDEFINED> instruction: 0x212a9a12
d001d750:	f7f54628 			; <UNDEFINED> instruction: 0xf7f54628
d001d754:	2800fb82 	stmdacs	r0, {r1, r7, r8, r9, fp, ip, sp, lr, pc}
d001d758:	aa68f43f 	bge	0xd1a5a85c
d001d75c:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d001d760:	f7f54628 			; <UNDEFINED> instruction: 0xf7f54628
d001d764:	2302fb6c 	movwcs	pc, #11116	; 0x2b6c	; <UNPREDICTABLE>
d001d768:	23017023 	movwcs	r7, #4131	; 0x1023
d001d76c:	4cc29312 	stclmi	3, cr9, [r2], {18}
d001d770:	4ac22129 	bmi	0xcf0a5c1c
d001d774:	447a447c 	ldrbtmi	r4, [sl], #-1148	; 0xfffffb84
d001d778:	f7f54620 			; <UNDEFINED> instruction: 0xf7f54620
d001d77c:	2800fb6e 	stmdacs	r0, {r1, r2, r3, r5, r6, r8, r9, fp, ip, sp, lr, pc}
d001d780:	aa54f43f 	bge	0xd155a884
d001d784:	2b049b13 	blcs	0xd01443d8
d001d788:	81def040 	bicshi	pc, lr, r0, asr #32
d001d78c:	2b059b12 	blcs	0xd01843dc
d001d790:	81daf040 	bicshi	pc, sl, r0, asr #32
d001d794:	2b006da3 	blcs	0xd0038e28
d001d798:	aa48f47f 	bge	0xd125a99c
d001d79c:	447b4bb8 	ldrbtmi	r4, [fp], #-3000	; 0xfffff448
d001d7a0:	9b1165a3 	blls	0xd0476e34
d001d7a4:	9b1065e3 	blls	0xd0436f38
d001d7a8:	3a18e9c4 	bcc	0xd0657ec0
d001d7ac:	66a39b0f 	strtvs	r9, [r3], pc, lsl #22
d001d7b0:	ba3cf7ff 	blt	0xd0f5b7b4
d001d7b4:	447848b3 	ldrbtmi	r4, [r8], #-2227	; 0xfffff74d
d001d7b8:	f5b36ac3 			; <UNDEFINED> instruction: 0xf5b36ac3
d001d7bc:	d1067f84 	smlabble	r6, r4, pc, r7	; <UNPREDICTABLE>
d001d7c0:	2b296cc3 	blcs	0xd0a78ad4
d001d7c4:	f7f5d103 			; <UNDEFINED> instruction: 0xf7f5d103
d001d7c8:	9512fb1f 	ldrls	pc, [r2, #-2847]	; 0xfffff4e1
d001d7cc:	4daee7cf 	stcmi	7, cr14, [lr, #828]!	; 0x33c
d001d7d0:	4eae2300 	cdpmi	3, 10, cr2, cr14, cr0, {0}
d001d7d4:	447dac20 	ldrbtmi	sl, [sp], #-3104	; 0xfffff3e0
d001d7d8:	447e9312 	ldrbtmi	r9, [lr], #-786	; 0xfffffcee
d001d7dc:	4850f505 	ldmdami	r0, {r0, r2, r8, sl, ip, sp, lr, pc}^
d001d7e0:	081cf108 	ldmdaeq	ip, {r3, r8, ip, sp, lr, pc}
d001d7e4:	2b019b12 	blcs	0xd0084434
d001d7e8:	9b1bd151 	blls	0xd0711d34
d001d7ec:	d04e2b00 	suble	r2, lr, r0, lsl #22
d001d7f0:	931dab20 	tstls	sp, #32, 22	; 0x8000
d001d7f4:	2b00781b 	blcs	0xd003b868
d001d7f8:	4fa5d149 	svcmi	0x00a5d149
d001d7fc:	110bf240 	tstne	fp, r0, asr #4	; <UNPREDICTABLE>
d001d800:	4638447f 			; <UNDEFINED> instruction: 0x4638447f
d001d804:	fb1bf7f5 	blx	0xd071b7e2
d001d808:	d0402800 	suble	r2, r0, r0, lsl #16
d001d80c:	212a4aa1 			; <UNDEFINED> instruction: 0x212a4aa1
d001d810:	447a4638 	ldrbtmi	r4, [sl], #-1592	; 0xfffff9c8
d001d814:	f7f5921f 			; <UNDEFINED> instruction: 0xf7f5921f
d001d818:	2800fb20 	stmdacs	r0, {r5, r8, r9, fp, ip, sp, lr, pc}
d001d81c:	aa06f43f 	bge	0xd01da920
d001d820:	212a9a1f 			; <UNDEFINED> instruction: 0x212a9a1f
d001d824:	f7f54638 			; <UNDEFINED> instruction: 0xf7f54638
d001d828:	2800fb18 	stmdacs	r0, {r3, r4, r8, r9, fp, ip, sp, lr, pc}
d001d82c:	a9fef43f 	ldmibge	lr!, {r0, r1, r2, r3, r4, r5, sl, ip, sp, lr, pc}^
d001d830:	9a1d2304 	bls	0xd0766448
d001d834:	4f987053 	svcmi	0x00987053
d001d838:	0cf0f10d 	ldfeqp	f7, [r0], #52	; 0x34
d001d83c:	447f9b12 	ldrbtmi	r9, [pc], #-2834	; 0xd001d844
d001d840:	1c43eb0c 	mcrrne	11, 0, lr, r3, cr12
d001d844:	0e18f107 	mnfeqe	f7, f7
d001d848:	000fe8be 			; <UNDEFINED> instruction: 0x000fe8be
d001d84c:	000fe8ac 	andeq	lr, pc, ip, lsr #17
d001d850:	000fe89e 	muleq	pc, lr, r8	; <UNPREDICTABLE>
d001d854:	000fe88c 	andeq	lr, pc, ip, lsl #17
d001d858:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d001d85c:	f7f54638 			; <UNDEFINED> instruction: 0xf7f54638
d001d860:	9b12faee 	blls	0xd04dc420
d001d864:	93123301 	tstls	r2, #67108864	; 0x4000000
d001d868:	3b01f814 	blcc	0xd009b8c0
d001d86c:	f43f2b04 			; <UNDEFINED> instruction: 0xf43f2b04
d001d870:	212caf7e 			; <UNDEFINED> instruction: 0x212caf7e
d001d874:	f7f54638 			; <UNDEFINED> instruction: 0xf7f54638
d001d878:	2800fae2 	stmdacs	r0, {r1, r5, r6, r7, r9, fp, ip, sp, lr, pc}
d001d87c:	af77f43f 	svcge	0x0077f43f
d001d880:	2b059b12 	blcs	0xd01844d0
d001d884:	4985d1ae 	stmibmi	r5, {r1, r2, r3, r5, r7, r8, ip, lr, pc}
d001d888:	44794638 	ldrbtmi	r4, [r9], #-1592	; 0xfffff9c8
d001d88c:	4630e6c9 	ldrtmi	lr, [r0], -r9, asr #13
d001d890:	ffa4f7f2 			; <UNDEFINED> instruction: 0xffa4f7f2
d001d894:	2300b1e8 	movwcs	fp, #488	; 0x1e8
d001d898:	4630a934 			; <UNDEFINED> instruction: 0x4630a934
d001d89c:	f7f59334 			; <UNDEFINED> instruction: 0xf7f59334
d001d8a0:	2800fcd9 	stmdacs	r0, {r0, r3, r4, r6, r7, sl, fp, ip, sp, lr, pc}
d001d8a4:	a9c2f43f 	stmibge	r2, {r0, r1, r2, r3, r4, r5, sl, ip, sp, lr, pc}^
d001d8a8:	4630212a 	ldrtmi	r2, [r0], -sl, lsr #2
d001d8ac:	fac7f7f5 	blx	0xcf21b888
d001d8b0:	212ab168 			; <UNDEFINED> instruction: 0x212ab168
d001d8b4:	f7f54630 			; <UNDEFINED> instruction: 0xf7f54630
d001d8b8:	2800fac2 	stmdacs	r0, {r1, r6, r7, r9, fp, ip, sp, lr, pc}
d001d8bc:	2312bf14 	tstcs	r2, #20, 30	; 0x50
d001d8c0:	7023230e 	eorvc	r2, r3, lr, lsl #6
d001d8c4:	9a34ab22 	bls	0xd0d48554
d001d8c8:	54ca9912 	strbpl	r9, [sl], #2322	; 0x912
d001d8cc:	230de7b3 	movwcs	lr, #55219	; 0xd7b3
d001d8d0:	6af2e7f7 	bvs	0xcfcd78b4
d001d8d4:	131bf240 	tstne	fp, #64, 4	; <UNPREDICTABLE>
d001d8d8:	d025429a 	mlale	r5, sl, r2, r4
d001d8dc:	f2404f70 	vrecps.f32	q10, q0, q8
d001d8e0:	447f1107 	ldrbtmi	r1, [pc], #-263	; 0xd001d8e8
d001d8e4:	f7f54638 			; <UNDEFINED> instruction: 0xf7f54638
d001d8e8:	bb10faaa 	bllt	0xd045c398
d001d8ec:	f2406afa 	vpmin.s8	q11, q8, q13
d001d8f0:	429a1301 	addsmi	r1, sl, #67108864	; 0x4000000
d001d8f4:	4638d12e 	ldrtmi	sp, [r8], -lr, lsr #2
d001d8f8:	1206e9d7 	andne	lr, r6, #3522560	; 0x35c000
d001d8fc:	ff49f7f2 			; <UNDEFINED> instruction: 0xff49f7f2
d001d900:	db272800 	blle	0xd09e7908
d001d904:	e9d74638 	ldmib	r7, {r3, r4, r5, r9, sl, lr}^
d001d908:	f7f21206 			; <UNDEFINED> instruction: 0xf7f21206
d001d90c:	2324ff42 	msrcs	CPSR_s, #264	; 0x108
d001d910:	7000fb03 	andvc	pc, r0, r3, lsl #22
d001d914:	3075f500 	rsbscc	pc, r5, r0, lsl #10
d001d918:	33acf890 			; <UNDEFINED> instruction: 0x33acf890
d001d91c:	d1192bff 			; <UNDEFINED> instruction: 0xd1192bff
d001d920:	f7f54638 			; <UNDEFINED> instruction: 0xf7f54638
d001d924:	e004fa71 	and	pc, r4, r1, ror sl	; <UNPREDICTABLE>
d001d928:	f7f54630 			; <UNDEFINED> instruction: 0xf7f54630
d001d92c:	2800fd89 	stmdacs	r0, {r0, r3, r7, r8, sl, fp, ip, sp, lr, pc}
d001d930:	4f5cd0d4 	svcmi	0x005cd0d4
d001d934:	447f212a 	ldrbtmi	r2, [pc], #-298	; 0xd001d93c
d001d938:	f7f54638 			; <UNDEFINED> instruction: 0xf7f54638
d001d93c:	b138fa80 	teqlt	r8, r0, lsl #21	; <UNPREDICTABLE>
d001d940:	4638212a 	ldrtmi	r2, [r8], -sl, lsr #2
d001d944:	fa7bf7f5 	blx	0xd1f1b920
d001d948:	bf142800 	svclt	0x00142800
d001d94c:	200a2013 	andcs	r2, sl, r3, lsl r0
d001d950:	e7707020 	ldrb	r7, [r0, -r0, lsr #32]!
d001d954:	44784854 	ldrbtmi	r4, [r8], #-2132	; 0xfffff7ac
d001d958:	f934f7f7 			; <UNDEFINED> instruction: 0xf934f7f7
d001d95c:	2303b110 	movwcs	fp, #12560	; 0x3110
d001d960:	e7687023 	strb	r7, [r8, -r3, lsr #32]!
d001d964:	44784851 	ldrbtmi	r4, [r8], #-2129	; 0xfffff7af
d001d968:	f92cf7f7 			; <UNDEFINED> instruction: 0xf92cf7f7
d001d96c:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d001d970:	2301809f 	movwcs	r8, #4255	; 0x109f
d001d974:	bf00e7f4 	svclt	0x0000e7f4
d001d978:	000096aa 	andeq	r9, r0, sl, lsr #13
d001d97c:	fffff52c 			; <UNDEFINED> instruction: 0xfffff52c
d001d980:	fffff52a 			; <UNDEFINED> instruction: 0xfffff52a
d001d984:	fffff52e 			; <UNDEFINED> instruction: 0xfffff52e
d001d988:	0000961c 	andeq	r9, r0, ip, lsl r6
d001d98c:	000095b6 			; <UNDEFINED> instruction: 0x000095b6
d001d990:	fffff4bc 			; <UNDEFINED> instruction: 0xfffff4bc
d001d994:	fffff4bf 			; <UNDEFINED> instruction: 0xfffff4bf
d001d998:	00009546 	andeq	r9, r0, r6, asr #10
d001d99c:	fffff48a 			; <UNDEFINED> instruction: 0xfffff48a
d001d9a0:	fffff42c 			; <UNDEFINED> instruction: 0xfffff42c
d001d9a4:	fffff462 			; <UNDEFINED> instruction: 0xfffff462
d001d9a8:	fffff45c 			; <UNDEFINED> instruction: 0xfffff45c
d001d9ac:	ffff6257 			; <UNDEFINED> instruction: 0xffff6257
d001d9b0:	fffff38c 			; <UNDEFINED> instruction: 0xfffff38c
d001d9b4:	fffff39d 			; <UNDEFINED> instruction: 0xfffff39d
d001d9b8:	000093a2 	andeq	r9, r0, r2, lsr #7
d001d9bc:	fffff321 			; <UNDEFINED> instruction: 0xfffff321
d001d9c0:	fffff319 			; <UNDEFINED> instruction: 0xfffff319
d001d9c4:	fffff302 			; <UNDEFINED> instruction: 0xfffff302
d001d9c8:	fffff2ec 			; <UNDEFINED> instruction: 0xfffff2ec
d001d9cc:	000091f2 	strdeq	r9, [r0], -r2
d001d9d0:	ffffac78 			; <UNDEFINED> instruction: 0xffffac78
d001d9d4:	000091ce 	andeq	r9, r0, lr, asr #3
d001d9d8:	ffffe9bc 			; <UNDEFINED> instruction: 0xffffe9bc
d001d9dc:	fffff24d 			; <UNDEFINED> instruction: 0xfffff24d
d001d9e0:	00009186 	andeq	r9, r0, r6, lsl #3
d001d9e4:	fffff256 			; <UNDEFINED> instruction: 0xfffff256
d001d9e8:	00009150 	andeq	r9, r0, r0, asr r1
d001d9ec:	0000912a 	andeq	r9, r0, sl, lsr #2
d001d9f0:	ffffefa1 			; <UNDEFINED> instruction: 0xffffefa1
d001d9f4:	00009110 	andeq	r9, r0, r0, lsl r1
d001d9f8:	ffffef57 			; <UNDEFINED> instruction: 0xffffef57
d001d9fc:	ffffd138 			; <UNDEFINED> instruction: 0xffffd138
d001da00:	000090c6 	andeq	r9, r0, r6, asr #1
d001da04:	0000909a 	muleq	r0, sl, r0
d001da08:	fffff195 			; <UNDEFINED> instruction: 0xfffff195
d001da0c:	00009078 	andeq	r9, r0, r8, ror r0
d001da10:	ffffe866 			; <UNDEFINED> instruction: 0xffffe866
d001da14:	00008fde 	ldrdeq	r8, [r0], -lr
d001da18:	fffff0fa 			; <UNDEFINED> instruction: 0xfffff0fa
d001da1c:	00008fac 	andeq	r8, r0, ip, lsr #31
d001da20:	00008efa 	strdeq	r8, [r0], -sl
d001da24:	fffff03b 			; <UNDEFINED> instruction: 0xfffff03b
d001da28:	00008ece 	andeq	r8, r0, lr, asr #29
d001da2c:	00008ebc 			; <UNDEFINED> instruction: 0x00008ebc
d001da30:	ffffcf7c 			; <UNDEFINED> instruction: 0xffffcf7c
d001da34:	ffffcf77 			; <UNDEFINED> instruction: 0xffffcf77
d001da38:	ffff622c 			; <UNDEFINED> instruction: 0xffff622c
d001da3c:	00008e78 	andeq	r8, r0, r8, ror lr
d001da40:	ffffefe9 			; <UNDEFINED> instruction: 0xffffefe9
d001da44:	ffffef49 			; <UNDEFINED> instruction: 0xffffef49
d001da48:	00008de4 	andeq	r8, r0, r4, ror #27
d001da4c:	00008db6 			; <UNDEFINED> instruction: 0x00008db6
d001da50:	00008da8 	andeq	r8, r0, r8, lsr #27
d001da54:	ffffef75 			; <UNDEFINED> instruction: 0xffffef75
d001da58:	ffffef57 			; <UNDEFINED> instruction: 0xffffef57
d001da5c:	ffffef58 			; <UNDEFINED> instruction: 0xffffef58
d001da60:	ffffef57 			; <UNDEFINED> instruction: 0xffffef57
d001da64:	ffffef50 			; <UNDEFINED> instruction: 0xffffef50
d001da68:	00008d12 	andeq	r8, r0, r2, lsl sp
d001da6c:	ffffef31 			; <UNDEFINED> instruction: 0xffffef31
d001da70:	00008cdc 	ldrdeq	r8, [r0], -ip
d001da74:	ffffef45 			; <UNDEFINED> instruction: 0xffffef45
d001da78:	00008c90 	muleq	r0, r0, ip
d001da7c:	fffff044 			; <UNDEFINED> instruction: 0xfffff044
d001da80:	fffff03e 			; <UNDEFINED> instruction: 0xfffff03e
d001da84:	00008c4e 	andeq	r8, r0, lr, asr #24
d001da88:	00008c2e 	andeq	r8, r0, lr, lsr #24
d001da8c:	00008c2a 	andeq	r8, r0, sl, lsr #24
d001da90:	00008c04 	andeq	r8, r0, r4, lsl #24
d001da94:	ffffeeb2 			; <UNDEFINED> instruction: 0xffffeeb2
d001da98:	00008bc6 	andeq	r8, r0, r6, asr #23
d001da9c:	ffffee10 			; <UNDEFINED> instruction: 0xffffee10
d001daa0:	00008b22 	andeq	r8, r0, r2, lsr #22
d001daa4:	00008ace 	andeq	r8, r0, lr, asr #21
d001daa8:	ffff5e54 			; <UNDEFINED> instruction: 0xffff5e54
d001daac:	ffffcb72 			; <UNDEFINED> instruction: 0xffffcb72
d001dab0:	44784897 	ldrbtmi	r4, [r8], #-2199	; 0xfffff769
d001dab4:	f886f7f7 			; <UNDEFINED> instruction: 0xf886f7f7
d001dab8:	2305b108 	movwcs	fp, #20744	; 0x5108
d001dabc:	4895e750 	ldmmi	r5, {r4, r6, r8, r9, sl, sp, lr, pc}
d001dac0:	f7f74478 			; <UNDEFINED> instruction: 0xf7f74478
d001dac4:	2800f87f 	stmdacs	r0, {r0, r1, r2, r3, r4, r5, r6, fp, ip, sp, lr, pc}
d001dac8:	f8d8d1f7 			; <UNDEFINED> instruction: 0xf8d8d1f7
d001dacc:	b3b33000 			; <UNDEFINED> instruction: 0xb3b33000
d001dad0:	7185f44f 	orrvc	pc, r5, pc, asr #8
d001dad4:	f7f54628 			; <UNDEFINED> instruction: 0xf7f54628
d001dad8:	b1e0f9b2 	strhlt	pc, [r0, #146]!	; 0x92	; <UNPREDICTABLE>
d001dadc:	4478488e 	ldrbtmi	r4, [r8], #-2190	; 0xfffff772
d001dae0:	f870f7f7 			; <UNDEFINED> instruction: 0xf870f7f7
d001dae4:	498db920 	stmibmi	sp, {r5, r8, fp, ip, sp, pc}
d001dae8:	4479488d 	ldrbtmi	r4, [r9], #-2189	; 0xfffff773
d001daec:	e5984478 	ldr	r4, [r8, #1144]	; 0x478
d001daf0:	212a4a8c 	smlawbcs	sl, ip, sl, r4
d001daf4:	447a4628 	ldrbtmi	r4, [sl], #-1576	; 0xfffff9d8
d001daf8:	f9aff7f5 			; <UNDEFINED> instruction: 0xf9aff7f5
d001dafc:	d0f22800 	rscsle	r2, r2, r0, lsl #16
d001db00:	338ff505 	orrcc	pc, pc, #20971520	; 0x1400000
d001db04:	31b4f8b3 			; <UNDEFINED> instruction: 0x31b4f8b3
d001db08:	4987b91b 	stmibmi	r7, {r0, r1, r3, r4, r8, fp, ip, sp, pc}
d001db0c:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d001db10:	2306bb20 	movwcs	fp, #27424	; 0x6b20
d001db14:	f8d8e724 			; <UNDEFINED> instruction: 0xf8d8e724
d001db18:	b1833000 	orrlt	r3, r3, r0
d001db1c:	7184f44f 	orrvc	pc, r4, pc, asr #8
d001db20:	f7f54628 			; <UNDEFINED> instruction: 0xf7f54628
d001db24:	b150f98c 	cmplt	r0, ip, lsl #19	; <UNPREDICTABLE>
d001db28:	212a4a80 	smlawbcs	sl, r0, sl, r4
d001db2c:	447a4628 	ldrbtmi	r4, [sl], #-1576	; 0xfffff9d8
d001db30:	f993f7f5 			; <UNDEFINED> instruction: 0xf993f7f5
d001db34:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001db38:	2302a879 	movwcs	sl, #10361	; 0x2879
d001db3c:	497ce710 	ldmdbmi	ip!, {r4, r8, r9, sl, sp, lr, pc}^
d001db40:	4479487c 	ldrbtmi	r4, [r9], #-2172	; 0xfffff784
d001db44:	e56c4478 	strb	r4, [ip, #-1144]!	; 0xfffffb88
d001db48:	071b9b15 			; <UNDEFINED> instruction: 0x071b9b15
d001db4c:	9b12d502 	blls	0xd04d2f5c
d001db50:	d1432b00 	cmple	r3, r0, lsl #22
d001db54:	24004e78 	strcs	r4, [r0], #-3704	; 0xfffff188
d001db58:	447e4d65 	ldrbtmi	r4, [lr], #-3429	; 0xfffff29b
d001db5c:	44354f65 	ldrtmi	r4, [r5], #-3941	; 0xfffff09b
d001db60:	683b4437 	ldmdavs	fp!, {r0, r1, r2, r4, r5, sl, lr}
d001db64:	d21a429c 	andsle	r4, sl, #156, 4	; 0xc0000009
d001db68:	464a2338 			; <UNDEFINED> instruction: 0x464a2338
d001db6c:	f804fb03 			; <UNDEFINED> instruction: 0xf804fb03
d001db70:	e9d5465b 	ldmib	r5, {r0, r1, r3, r4, r6, r9, sl, lr}^
d001db74:	f7f20100 			; <UNDEFINED> instruction: 0xf7f20100
d001db78:	2800fd51 	stmdacs	r0, {r0, r4, r6, r8, sl, fp, ip, sp, lr, pc}
d001db7c:	f895d038 			; <UNDEFINED> instruction: 0xf895d038
d001db80:	f89d2028 			; <UNDEFINED> instruction: 0xf89d2028
d001db84:	429a3050 	addsmi	r3, sl, #80	; 0x50
d001db88:	9b14d132 	blls	0xd0552058
d001db8c:	f895b123 			; <UNDEFINED> instruction: 0xf895b123
d001db90:	7a332029 	bvc	0xd0ce5c3c
d001db94:	d12b429a 			; <UNDEFINED> instruction: 0xd12b429a
d001db98:	f2802c00 	vmull.s8	q1, d0, d0
d001db9c:	4c6784ac 	cfstrdmi	mvd8, [r7], #-688	; 0xfffffd50
d001dba0:	4649465a 			; <UNDEFINED> instruction: 0x4649465a
d001dba4:	4620447c 			; <UNDEFINED> instruction: 0x4620447c
d001dba8:	fe38f7f2 	mrc2	7, 1, pc, cr8, cr2, {7}
d001dbac:	f2c02800 	vmlal.s8	q9, d0, d0
d001dbb0:	465a84bc 			; <UNDEFINED> instruction: 0x465a84bc
d001dbb4:	46204649 	strtmi	r4, [r0], -r9, asr #12
d001dbb8:	fe30f7f2 	mrc2	7, 1, pc, cr0, cr2, {7}
d001dbbc:	fb032338 	blx	0xd00e68a6
d001dbc0:	4b4d4000 	blmi	0xd136dbc8
d001dbc4:	7a235cc2 	bvc	0xd08f4ed4
d001dbc8:	f040429a 			; <UNDEFINED> instruction: 0xf040429a
d001dbcc:	6da384ae 	cfstrsvs	mvf8, [r3, #696]!	; 0x2b8
d001dbd0:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001dbd4:	4b5aa82b 	blmi	0xd16c7c88
d001dbd8:	e5e1447b 	strb	r4, [r1, #1147]!	; 0x47b
d001dbdc:	447b4b59 	ldrbtmi	r4, [fp], #-2905	; 0xfffff4a7
d001dbe0:	2a006d9a 	bcs	0xd0039250
d001dbe4:	a822f47f 	stmdage	r2!, {r0, r1, r2, r3, r4, r5, r6, sl, ip, sp, lr, pc}
d001dbe8:	447a4a57 	ldrbtmi	r4, [sl], #-2647	; 0xfffff5a9
d001dbec:	bb49f7ff 	bllt	0xd129bbf0
d001dbf0:	35383401 	ldrcc	r3, [r8, #-1025]!	; 0xfffffbff
d001dbf4:	1c62e7b5 	stclne	7, cr14, [r2], #-724	; 0xfffffd2c
d001dbf8:	f8952100 			; <UNDEFINED> instruction: 0xf8952100
d001dbfc:	601a8008 	andsvs	r8, sl, r8
d001dc00:	4b3b2238 	blmi	0xd0ee64e8
d001dc04:	f704fb02 			; <UNDEFINED> instruction: 0xf704fb02
d001dc08:	199819ee 	ldmibne	r8, {r1, r2, r3, r5, r6, r7, r8, fp, ip}
d001dc0c:	fe50f001 	cdp2	0, 5, cr15, cr0, cr1, {0}
d001dc10:	f10d9a11 			; <UNDEFINED> instruction: 0xf10d9a11
d001dc14:	f88d0eb0 			; <UNDEFINED> instruction: 0xf88d0eb0
d001dc18:	922fa0c8 	eorls	sl, pc, #200	; 0xc8
d001dc1c:	9a104684 	bls	0xd042f634
d001dc20:	9a0f9230 	bls	0xd04024e8
d001dc24:	9b2ce9cd 	blls	0xd0b58360
d001dc28:	e8be9233 	ldm	lr!, {r0, r1, r4, r5, r9, ip, pc}
d001dc2c:	e8ac000f 	stmia	ip!, {r0, r1, r2, r3}
d001dc30:	e89e000f 	ldm	lr, {r0, r1, r2, r3}
d001dc34:	e88c000f 	stm	ip, {r0, r1, r2, r3}
d001dc38:	9a15000f 	bls	0xd055dc7c
d001dc3c:	4b2fa920 	blmi	0xd0c080c4
d001dc40:	50f2482f 	rscspl	r4, r2, pc, lsr #16
d001dc44:	9a123304 	bls	0xd04aa85c
d001dc48:	54f24438 	ldrbtpl	r4, [r2], #1080	; 0x438
d001dc4c:	9a153301 	bls	0xd056a858
d001dc50:	54f24428 	ldrbtpl	r4, [r2], #1064	; 0x428
d001dc54:	4b2b3a00 	blmi	0xd0aec45c
d001dc58:	2201bf18 	andcs	fp, r1, #24, 30	; 0x60
d001dc5c:	330154f2 	movwcc	r5, #5362	; 0x14f2
d001dc60:	54f29a13 	ldrbtpl	r9, [r2], #2579	; 0xa13
d001dc64:	9a143301 	bls	0xd052a870
d001dc68:	330154f2 	movwcc	r5, #5362	; 0x14f2
d001dc6c:	f8069a17 			; <UNDEFINED> instruction: 0xf8069a17
d001dc70:	33018003 	movwcc	r8, #4099	; 0x1003
d001dc74:	9a1254f2 	bls	0xd04b3044
d001dc78:	fe28f001 	cdp2	0, 2, cr15, cr8, cr1, {0}
d001dc7c:	9a124822 	bls	0xd04afd0c
d001dc80:	4438a922 	ldrtmi	sl, [r8], #-2338	; 0xfffff6de
d001dc84:	f0014428 			; <UNDEFINED> instruction: 0xf0014428
d001dc88:	4d30fe21 	ldcmi	14, cr15, [r0, #-132]!	; 0xffffff7c
d001dc8c:	447d213b 	ldrbtmi	r2, [sp], #-315	; 0xfffffec5
d001dc90:	f7f54628 			; <UNDEFINED> instruction: 0xf7f54628
d001dc94:	2800f8d4 	stmdacs	r0, {r2, r4, r6, r7, fp, ip, sp, lr, pc}
d001dc98:	afc8f47e 	svcge	0x00c8f47e
d001dc9c:	4f192338 	svcmi	0x00192338
d001dca0:	5404fb03 	strpl	pc, [r4], #-2819	; 0xfffff4fd
d001dca4:	2e005de6 	cdpcs	13, 0, cr5, cr0, cr6, {7}
d001dca8:	6dabd054 	stcvs	0, cr13, [fp, #336]!	; 0x150
d001dcac:	f47e2b00 			; <UNDEFINED> instruction: 0xf47e2b00
d001dcb0:	4b27afbd 	blmi	0xd0a09bac
d001dcb4:	f7ff447b 			; <UNDEFINED> instruction: 0xf7ff447b
d001dcb8:	4a14bacf 	bmi	0xd054c7fc
d001dcbc:	9a175c9b 	bls	0xd05f4f30
d001dcc0:	f0404293 			; <UNDEFINED> instruction: 0xf0404293
d001dcc4:	480e8428 	stmdami	lr, {r3, r5, sl, pc}
d001dcc8:	9a12a920 	bls	0xd04c8150
d001dccc:	44284440 	strtmi	r4, [r8], #-1088	; 0xfffffbc0
d001dcd0:	fe0cf001 	cdp2	0, 0, cr15, cr12, cr1, {0}
d001dcd4:	f0402800 			; <UNDEFINED> instruction: 0xf0402800
d001dcd8:	480b841e 	stmdami	fp, {r1, r2, r3, r4, sl, pc}
d001dcdc:	9a12a922 	bls	0xd04c816c
d001dce0:	44284440 	strtmi	r4, [r8], #-1088	; 0xfffffbc0
d001dce4:	fe02f001 	cdp2	0, 0, cr15, cr2, cr1, {0}
d001dce8:	d0ce2800 	sbcle	r2, lr, r0, lsl #16
d001dcec:	bc13f000 	ldclt	0, cr15, [r3], {-0}
d001dcf0:	0013fe24 	andseq	pc, r3, r4, lsr #28
d001dcf4:	00143624 	andseq	r3, r4, r4, lsr #12
d001dcf8:	0013fe4d 	andseq	pc, r3, sp, asr #28
d001dcfc:	0013fe44 	andseq	pc, r3, r4, asr #28
d001dd00:	0013fe4f 	andseq	pc, r3, pc, asr #28
d001dd04:	0013fe4a 	andseq	pc, r3, sl, asr #28
d001dd08:	0013fe54 	andseq	pc, r3, r4, asr lr	; <UNPREDICTABLE>
d001dd0c:	0013fe4e 	andseq	pc, r3, lr, asr #28
d001dd10:	ffffca2f 			; <UNDEFINED> instruction: 0xffffca2f
d001dd14:	ffff5ce2 			; <UNDEFINED> instruction: 0xffff5ce2
d001dd18:	ffffec13 			; <UNDEFINED> instruction: 0xffffec13
d001dd1c:	ffffec13 			; <UNDEFINED> instruction: 0xffffec13
d001dd20:	00008918 	andeq	r8, r0, r8, lsl r9
d001dd24:	ffffec2e 			; <UNDEFINED> instruction: 0xffffec2e
d001dd28:	ffffec3d 			; <UNDEFINED> instruction: 0xffffec3d
d001dd2c:	ffffec46 			; <UNDEFINED> instruction: 0xffffec46
d001dd30:	ffffec54 			; <UNDEFINED> instruction: 0xffffec54
d001dd34:	000088c0 	andeq	r8, r0, r0, asr #17
d001dd38:	000088aa 	andeq	r8, r0, sl, lsr #17
d001dd3c:	00008860 	andeq	r8, r0, r0, ror #16
d001dd40:	ffffec69 			; <UNDEFINED> instruction: 0xffffec69
d001dd44:	00008826 	andeq	r8, r0, r6, lsr #16
d001dd48:	ffffec34 			; <UNDEFINED> instruction: 0xffffec34
d001dd4c:	00008776 	andeq	r8, r0, r6, ror r7
d001dd50:	ffffec02 			; <UNDEFINED> instruction: 0xffffec02
d001dd54:	217b4acc 	cmncs	fp, ip, asr #21
d001dd58:	447a4628 	ldrbtmi	r4, [sl], #-1576	; 0xfffff9d8
d001dd5c:	f87df7f5 			; <UNDEFINED> instruction: 0xf87df7f5
d001dd60:	f43e2800 			; <UNDEFINED> instruction: 0xf43e2800
d001dd64:	f505af63 			; <UNDEFINED> instruction: 0xf505af63
d001dd68:	4bc2398f 	blmi	0xcf0ac3ac
d001dd6c:	0801f04f 	stmdaeq	r1, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d001dd70:	f8d94628 			; <UNDEFINED> instruction: 0xf8d94628
d001dd74:	f24b21b8 	vand	d18, d27, d24
d001dd78:	f8045180 			; <UNDEFINED> instruction: 0xf8045180
d001dd7c:	f5058007 			; <UNDEFINED> instruction: 0xf5058007
d001dd80:	50e217a4 	rscpl	r1, r2, r4, lsr #15
d001dd84:	4313f503 	tstmi	r3, #12582912	; 0xc00000	; <UNPREDICTABLE>
d001dd88:	662cf8c7 	strtvs	pc, [ip], -r7, asr #17
d001dd8c:	f88733f8 			; <UNDEFINED> instruction: 0xf88733f8
d001dd90:	515e6632 	cmppl	lr, r2, lsr r6
d001dd94:	515e3b04 	cmppl	lr, r4, lsl #22
d001dd98:	515e3b04 	cmppl	lr, r4, lsl #22
d001dd9c:	515e3318 	cmppl	lr, r8, lsl r3
d001dda0:	515e3b04 	cmppl	lr, r4, lsl #22
d001dda4:	5301f503 	movwpl	pc, #5379	; 0x1503	; <UNPREDICTABLE>
d001dda8:	515e3310 	cmppl	lr, r0, lsl r3
d001ddac:	13a5f505 			; <UNDEFINED> instruction: 0x13a5f505
d001ddb0:	6294f8c3 	addsvs	pc, r4, #12779520	; 0xc30000
d001ddb4:	6250f8c3 	subsvs	pc, r0, #12779520	; 0xc30000
d001ddb8:	5ce34baf 	fstmiaxpl	r3!, {d20-d106}	;@ Deprecated
d001ddbc:	3630f887 	ldrtcc	pc, [r0], -r7, lsl #17	; <UNPREDICTABLE>
d001ddc0:	5ce34bae 	vstmiapl	r3!, {d20-<overflow reg d42>}
d001ddc4:	3631f887 	ldrtcc	pc, [r1], -r7, lsl #17	; <UNPREDICTABLE>
d001ddc8:	ff48f7f6 			; <UNDEFINED> instruction: 0xff48f7f6
d001ddcc:	31b8f8d9 			; <UNDEFINED> instruction: 0x31b8f8d9
d001ddd0:	93154631 	tstls	r5, #51380224	; 0x3100000
d001ddd4:	ff42f7f6 			; <UNDEFINED> instruction: 0xff42f7f6
d001ddd8:	412ff44f 	msrmi	CPSR_fsxc, pc, asr #8
d001dddc:	ff3ef7f6 			; <UNDEFINED> instruction: 0xff3ef7f6
d001dde0:	2b049b13 	blcs	0xd0144a34
d001dde4:	8082f040 	addhi	pc, r2, r0, asr #32
d001dde8:	46312218 			; <UNDEFINED> instruction: 0x46312218
d001ddec:	f001a836 			; <UNDEFINED> instruction: 0xf001a836
d001ddf0:	4ba6fd5f 	blmi	0xce9dd374
d001ddf4:	9334447b 	teqls	r4, #2063597568	; 0x7b000000
d001ddf8:	93352314 	teqls	r5, #20, 6	; 0x50000000
d001ddfc:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d001de00:	230b9339 	movwcs	r9, #45881	; 0xb339
d001de04:	ab389304 	blge	0xd0e42a1c
d001de08:	e88dcb0f 	stm	sp, {r0, r1, r2, r3, r8, r9, fp, lr, pc}
d001de0c:	ab34000f 	blge	0xd0d1de50
d001de10:	f7f6cb0f 			; <UNDEFINED> instruction: 0xf7f6cb0f
d001de14:	4632f8e1 	ldrtmi	pc, [r2], -r1, ror #17	; <UNPREDICTABLE>
d001de18:	f887b2c1 			; <UNDEFINED> instruction: 0xf887b2c1
d001de1c:	46280632 			; <UNDEFINED> instruction: 0x46280632
d001de20:	ffcdf7f6 			; <UNDEFINED> instruction: 0xffcdf7f6
d001de24:	804cf8cd 	subhi	pc, ip, sp, asr #17
d001de28:	21002214 	tstcs	r0, r4, lsl r2
d001de2c:	2400a834 	strcs	sl, [r0], #-2100	; 0xfffff7cc
d001de30:	fd3ef001 	ldc2	0, cr15, [lr, #-4]!
d001de34:	f10dab20 			; <UNDEFINED> instruction: 0xf10dab20
d001de38:	f10d0b88 			; <UNDEFINED> instruction: 0xf10d0b88
d001de3c:	461e0af0 			; <UNDEFINED> instruction: 0x461e0af0
d001de40:	4b93930f 	blmi	0xce502a84
d001de44:	447b9410 	ldrbtmi	r9, [fp], #-1040	; 0xfffffbf0
d001de48:	9b129317 	blls	0xd04c2aac
d001de4c:	d14f42a3 	smlaltble	r4, pc, r3, r2	; <UNPREDICTABLE>
d001de50:	24004e90 	strcs	r4, [r0], #-3728	; 0xfffff170
d001de54:	447e4d90 	ldrbtmi	r4, [lr], #-3472	; 0xfffff270
d001de58:	9b12447d 	blls	0xd04af054
d001de5c:	f04042a3 			; <UNDEFINED> instruction: 0xf04042a3
d001de60:	f7fd8139 			; <UNDEFINED> instruction: 0xf7fd8139
d001de64:	488dfead 	stmmi	sp, {r0, r2, r3, r5, r7, r9, sl, fp, ip, sp, lr, pc}
d001de68:	f5004478 			; <UNDEFINED> instruction: 0xf5004478
d001de6c:	f89313a4 			; <UNDEFINED> instruction: 0xf89313a4
d001de70:	2b013630 	blcs	0xd006b738
d001de74:	2100d002 	tstcs	r0, r2
d001de78:	ff4ff7f6 			; <UNDEFINED> instruction: 0xff4ff7f6
d001de7c:	44784888 	ldrbtmi	r4, [r8], #-2184	; 0xfffff778
d001de80:	338ff500 	orrcc	pc, pc, #0, 10
d001de84:	81b8f8d3 			; <UNDEFINED> instruction: 0x81b8f8d3
d001de88:	581c4b7d 	ldmdapl	ip, {r0, r2, r3, r4, r5, r6, r8, r9, fp, lr}
d001de8c:	f0243401 			; <UNDEFINED> instruction: 0xf0243401
d001de90:	b2a50401 	adclt	r0, r5, #16777216	; 0x1000000
d001de94:	4130f445 	teqmi	r0, r5, asr #8	; <UNPREDICTABLE>
d001de98:	fee0f7f6 	mcr2	7, 7, pc, cr0, cr6, {7}	; <UNPREDICTABLE>
d001de9c:	5180f64b 	orrpl	pc, r0, fp, asr #12
d001dea0:	fedcf7f6 	mrc2	7, 6, pc, cr12, cr6, {7}
d001dea4:	2b006d83 	blcs	0xd00394b8
d001dea8:	aec0f47e 	mcrge	4, 6, pc, cr0, cr14, {3}	; <UNPREDICTABLE>
d001deac:	f4454b7d 			; <UNDEFINED> instruction: 0xf4454b7d
d001deb0:	9a154530 	bls	0xd056f378
d001deb4:	f045447b 			; <UNDEFINED> instruction: 0xf045447b
d001deb8:	441a0580 	ldrmi	r0, [sl], #-1408	; 0xfffffa80
d001debc:	5040f882 	subpl	pc, r0, r2, lsl #17
d001dec0:	f8820a2d 			; <UNDEFINED> instruction: 0xf8820a2d
d001dec4:	9a105041 	bls	0xd0431fd0
d001dec8:	3402b142 	strcc	fp, [r2], #-322	; 0xfffffebe
d001decc:	00a44413 	adceq	r4, r4, r3, lsl r4
d001ded0:	f883b2a4 			; <UNDEFINED> instruction: 0xf883b2a4
d001ded4:	0a244040 	beq	0xd092dfdc
d001ded8:	4041f883 	submi	pc, r1, r3, lsl #17
d001dedc:	26004c72 			; <UNDEFINED> instruction: 0x26004c72
d001dee0:	447c4d68 	ldrbtmi	r4, [ip], #-3432	; 0xfffff298
d001dee4:	f5044425 			; <UNDEFINED> instruction: 0xf5044425
d001dee8:	e12a17a4 			; <UNDEFINED> instruction: 0xe12a17a4
d001deec:	e79b9613 			; <UNDEFINED> instruction: 0xe79b9613
d001def0:	2014f8da 			; <UNDEFINED> instruction: 0x2014f8da
d001def4:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d001def8:	d014429a 	mulsle	r4, sl, r2
d001defc:	447b4b6b 	ldrbtmi	r4, [fp], #-2923	; 0xfffff495
d001df00:	2a006d9a 	bcs	0xd0039570
d001df04:	ae92f47e 	mrcge	4, 4, APSR_nzcv, cr2, cr14, {3}
d001df08:	eb02aa3c 	bl	0xd00c8800
d001df0c:	68e51444 	stmiavs	r5!, {r2, r6, sl, ip}^
d001df10:	69e26920 	stmibvs	r2!, {r5, r8, fp, sp, lr}^
d001df14:	4c667e21 	stclmi	14, cr7, [r6], #-132	; 0xffffff7c
d001df18:	e9c3447c 	stmib	r3, {r2, r3, r4, r5, r6, sl, lr}^
d001df1c:	e9c34516 	stmib	r3, {r1, r2, r4, r8, sl, lr}^
d001df20:	f7ff0118 			; <UNDEFINED> instruction: 0xf7ff0118
d001df24:	7832b9f5 	ldmdavc	r2!, {r0, r2, r4, r5, r6, r7, r8, fp, ip, sp, pc}
d001df28:	2a0d9614 	bcs	0xd0383780
d001df2c:	f89bd11d 			; <UNDEFINED> instruction: 0xf89bd11d
d001df30:	f44f3000 	vst4.8	{d19-d22}, [pc], r0
d001df34:	9817711a 	ldmdals	r7, {r1, r3, r4, r8, ip, sp, lr}
d001df38:	0303fb01 	movweq	pc, #15105	; 0x3b01	; <UNPREDICTABLE>
d001df3c:	3368f503 	msrcc	SPSR_f, #12582912	; 0xc00000
d001df40:	8028f8b3 	strhthi	pc, [r8], -r3	; <UNPREDICTABLE>
d001df44:	0f00f1b8 	svceq	0x0000f1b8
d001df48:	4b5ad111 	blmi	0xd16d2394
d001df4c:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d001df50:	f47e2a00 			; <UNDEFINED> instruction: 0xf47e2a00
d001df54:	aa3cae6b 	bge	0xd0f49908
d001df58:	1444eb02 	strbne	lr, [r4], #-2818	; 0xfffff4fe
d001df5c:	692068e5 	stmdbvs	r0!, {r0, r2, r5, r6, r7, fp, sp, lr}
d001df60:	7e2169e2 	vnmulvc.f16	s12, s3, s5	; <UNPREDICTABLE>
d001df64:	447c4c54 	ldrbtmi	r4, [ip], #-3156	; 0xfffff3ac
d001df68:	f04fe7d7 			; <UNDEFINED> instruction: 0xf04fe7d7
d001df6c:	9b1e0801 	blls	0xd079ff78
d001df70:	f1c3681b 			; <UNDEFINED> instruction: 0xf1c3681b
d001df74:	45430340 	strbmi	r0, [r3, #-832]	; 0xfffffcc0
d001df78:	ab64d3e7 	blge	0xd1952f1c
d001df7c:	eb039204 	bl	0xd0102794
d001df80:	f1a31344 			; <UNDEFINED> instruction: 0xf1a31344
d001df84:	3b9005a0 	blcc	0xce41f60c
d001df88:	e88dcb0f 	stm	sp, {r0, r1, r2, r3, r8, r9, fp, lr, pc}
d001df8c:	e895000f 	ldm	r5, {r0, r1, r2, r3}
d001df90:	f7f6000f 			; <UNDEFINED> instruction: 0xf7f6000f
d001df94:	ab34f821 	blge	0xd0d5c020
d001df98:	f8434607 			; <UNDEFINED> instruction: 0xf8434607
d001df9c:	78330024 	ldmdavc	r3!, {r2, r5}
d001dfa0:	020df1a3 	andeq	pc, sp, #-1073741784	; 0xc0000028
d001dfa4:	d9012a01 	stmdble	r1, {r0, r9, fp, sp}
d001dfa8:	d10a2b12 	tstle	sl, r2, lsl fp
d001dfac:	22304b43 	eorscs	r4, r0, #68608	; 0x10c00
d001dfb0:	fb02447b 	blx	0xd00af1a6
d001dfb4:	f89b3307 			; <UNDEFINED> instruction: 0xf89b3307
d001dfb8:	f5032000 			; <UNDEFINED> instruction: 0xf5032000
d001dfbc:	f88313a4 			; <UNDEFINED> instruction: 0xf88313a4
d001dfc0:	4a3f2656 	bmi	0xd0fe7920
d001dfc4:	f8df2301 			; <UNDEFINED> instruction: 0xf8df2301
d001dfc8:	447a90fc 	ldrbtmi	r9, [sl], #-252	; 0xffffff04
d001dfcc:	92114491 	andsls	r4, r1, #-1862270976	; 0x91000000
d001dfd0:	1c6ae013 	stclne	0, cr14, [sl], #-76	; 0xffffffb4
d001dfd4:	9b11931b 	blls	0xd0482c48
d001dfd8:	f8c92100 			; <UNDEFINED> instruction: 0xf8c92100
d001dfdc:	22302000 	eorscs	r2, r0, #0
d001dfe0:	3505fb02 	strcc	pc, [r5, #-2818]	; 0xfffff4fe
d001dfe4:	15a4f505 	strne	pc, [r4, #1285]!	; 0x505
d001dfe8:	6034f205 	eorsvs	pc, r4, r5, lsl #4
d001dfec:	fc60f001 	stc2l	0, cr15, [r0], #-4
d001dff0:	220b9b1b 	andcs	r9, fp, #27648	; 0x6c00
d001dff4:	f8853301 			; <UNDEFINED> instruction: 0xf8853301
d001dff8:	45982655 	ldrmi	r2, [r8, #1621]	; 0x655
d001dffc:	5000f8d9 	ldrdpl	pc, [r0], -r9
d001e000:	4b1fd1e7 	blmi	0xd08127a4
d001e004:	441a9a11 	ldrmi	r9, [sl], #-2577	; 0xfffff5ef
d001e008:	68124613 	ldmdavs	r2, {r0, r1, r4, r9, sl, lr}
d001e00c:	bf3842aa 	svclt	0x003842aa
d001e010:	2c04601d 	stccs	0, cr6, [r4], {29}
d001e014:	eb049b13 	bl	0xd0144c68
d001e018:	d10e0503 	tstle	lr, r3, lsl #10
d001e01c:	f64f482a 			; <UNDEFINED> instruction: 0xf64f482a
d001e020:	250001d7 	strcs	r0, [r0, #-471]	; 0xfffffe29
d001e024:	f7f64478 			; <UNDEFINED> instruction: 0xf7f64478
d001e028:	2100fe19 	tstcs	r0, r9, lsl lr	; <UNPREDICTABLE>
d001e02c:	338ff500 	orrcc	pc, pc, #0, 10
d001e030:	31b8f8d3 			; <UNDEFINED> instruction: 0x31b8f8d3
d001e034:	f7f69310 			; <UNDEFINED> instruction: 0xf7f69310
d001e038:	9b14fe11 	blls	0xd055d884
d001e03c:	781b3601 	ldmdavc	fp, {r0, r9, sl, ip, sp}
d001e040:	d10b2b05 	tstle	fp, r5, lsl #22
d001e044:	4821b2a9 	stmdami	r1!, {r0, r3, r5, r7, r9, ip, sp, pc}
d001e048:	01c1ea41 	biceq	lr, r1, r1, asr #20
d001e04c:	f4414478 	vst3.16	{d20-d22}, [r1 :256], r8
d001e050:	f0414132 			; <UNDEFINED> instruction: 0xf0414132
d001e054:	b28901c0 	addlt	r0, r9, #192, 2	; 0x30
d001e058:	fe00f7f6 	mcr2	7, 0, pc, cr0, cr6, {7}	; <UNPREDICTABLE>
d001e05c:	462a481c 			; <UNDEFINED> instruction: 0x462a481c
d001e060:	34014639 	strcc	r4, [r1], #-1593	; 0xfffff9c7
d001e064:	f10b4478 			; <UNDEFINED> instruction: 0xf10b4478
d001e068:	f10a0b01 			; <UNDEFINED> instruction: 0xf10a0b01
d001e06c:	f7f60a20 			; <UNDEFINED> instruction: 0xf7f60a20
d001e070:	e6eafea6 	strbt	pc, [sl], r6, lsr #29	; <UNPREDICTABLE>
d001e074:	0013fe44 	andseq	pc, r3, r4, asr #28
d001e078:	0013fe4b 	andseq	pc, r3, fp, asr #28
d001e07c:	0013fe4e 	andseq	pc, r3, lr, asr #28
d001e080:	00149238 	andseq	r9, r4, r8, lsr r2
d001e084:	0014762c 	andseq	r7, r4, ip, lsr #12
d001e088:	ffffeb75 			; <UNDEFINED> instruction: 0xffffeb75
d001e08c:	ffffeafb 			; <UNDEFINED> instruction: 0xffffeafb
d001e090:	000085be 			; <UNDEFINED> instruction: 0x000085be
d001e094:	000085ae 	andeq	r8, r0, lr, lsr #11
d001e098:	000085ac 	andeq	r8, r0, ip, lsr #11
d001e09c:	0000859c 	muleq	r0, ip, r5
d001e0a0:	00008586 	andeq	r8, r0, r6, lsl #11
d001e0a4:	001537f0 			; <UNDEFINED> instruction: 0x001537f0
d001e0a8:	00008522 	andeq	r8, r0, r2, lsr #10
d001e0ac:	00008506 	andeq	r8, r0, r6, lsl #10
d001e0b0:	ffffe9ec 			; <UNDEFINED> instruction: 0xffffe9ec
d001e0b4:	000084b8 			; <UNDEFINED> instruction: 0x000084b8
d001e0b8:	ffffe9ca 			; <UNDEFINED> instruction: 0xffffe9ca
d001e0bc:	00008454 	andeq	r8, r0, r4, asr r4
d001e0c0:	0000843a 	andeq	r8, r0, sl, lsr r4
d001e0c4:	00149234 	andseq	r9, r4, r4, lsr r2
d001e0c8:	000083e0 	andeq	r8, r0, r0, ror #7
d001e0cc:	000083b8 			; <UNDEFINED> instruction: 0x000083b8
d001e0d0:	000083a0 	andeq	r8, r0, r0, lsr #7
d001e0d4:	f8129a0f 			; <UNDEFINED> instruction: 0xf8129a0f
d001e0d8:	2b0d3b01 	blcs	0xd036cce4
d001e0dc:	d001920f 	andle	r9, r1, pc, lsl #4
d001e0e0:	e6ba3401 	ldrt	r3, [sl], r1, lsl #8
d001e0e4:	f44fab34 			; <UNDEFINED> instruction: 0xf44fab34
d001e0e8:	f04f721a 			; <UNDEFINED> instruction: 0xf04f721a
d001e0ec:	46300900 	ldrtmi	r0, [r0], -r0, lsl #18
d001e0f0:	7024f853 	eorvc	pc, r4, r3, asr r8	; <UNPREDICTABLE>
d001e0f4:	5ce3ab22 	vstmiapl	r3!, {d26-<overflow reg d42>}
d001e0f8:	fb024639 	blx	0xd00af9e6
d001e0fc:	22016303 	andcs	r6, r1, #201326592	; 0xc000000
d001e100:	3368f503 	msrcc	SPSR_f, #12582912	; 0xc00000
d001e104:	8028f8b3 	strhthi	pc, [r8], -r3	; <UNPREDICTABLE>
d001e108:	fe40f7f6 	mcr2	7, 2, pc, cr0, cr6, {7}	; <UNPREDICTABLE>
d001e10c:	d9e745c8 	stmible	r7!, {r3, r6, r7, r8, sl, lr}^
d001e110:	f64f4628 			; <UNDEFINED> instruction: 0xf64f4628
d001e114:	f7f601d1 			; <UNDEFINED> instruction: 0xf7f601d1
d001e118:	ea4ffda1 	b	0xd141d7a4
d001e11c:	b2890189 	addlt	r0, r9, #1073741858	; 0x40000022
d001e120:	fd9cf7f6 	ldc2	7, cr15, [ip, #984]	; 0x3d8
d001e124:	0109eb07 	tsteq	r9, r7, lsl #22
d001e128:	f1092200 			; <UNDEFINED> instruction: 0xf1092200
d001e12c:	f7f60901 			; <UNDEFINED> instruction: 0xf7f60901
d001e130:	e7ebfe46 	strb	pc, [fp, r6, asr #28]!	; <UNPREDICTABLE>
d001e134:	23003601 	movwcs	r3, #1537	; 0x601
d001e138:	f8554642 			; <UNDEFINED> instruction: 0xf8554642
d001e13c:	f7f71b04 			; <UNDEFINED> instruction: 0xf7f71b04
d001e140:	f8d7ffdf 			; <UNDEFINED> instruction: 0xf8d7ffdf
d001e144:	6da0362c 	stcvs	6, cr3, [r0, #176]!	; 0xb0
d001e148:	d3f3429e 	mvnsle	r4, #-536870903	; 0xe0000009
d001e14c:	bd6ef7fe 	stcllt	7, cr15, [lr, #-1016]!	; 0xfffffc08
d001e150:	f47e2b00 			; <UNDEFINED> instruction: 0xf47e2b00
d001e154:	49c7ac94 	stmibmi	r7, {r2, r4, r7, sl, fp, sp, pc}^
d001e158:	46202204 	strtmi	r2, [r0], -r4, lsl #4
d001e15c:	f7f24479 			; <UNDEFINED> instruction: 0xf7f24479
d001e160:	2800fb5d 	stmdacs	r0, {r0, r2, r3, r4, r6, r8, r9, fp, ip, sp, lr, pc}
d001e164:	2338db0c 	teqcs	r8, #12, 22	; 0x3000
d001e168:	4400fb03 	strmi	pc, [r0], #-2819	; 0xfffff4fd
d001e16c:	5ce34bbb 	fstmiaxpl	r3!, {d20-d112}	;@ Deprecated
d001e170:	4bbbb133 	blmi	0xcef0a644
d001e174:	b15b5ce3 	cmplt	fp, r3, ror #25
d001e178:	5ce34bba 	vstmiapl	r3!, {d20-<overflow reg d48>}
d001e17c:	d0072b04 	andle	r2, r7, r4, lsl #22
d001e180:	48be49bd 	ldmmi	lr!, {r0, r2, r3, r4, r5, r7, r8, fp, lr}
d001e184:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d001e188:	f80ef7f2 			; <UNDEFINED> instruction: 0xf80ef7f2
d001e18c:	bc77f7fe 	ldcllt	7, cr15, [r7], #-1016	; 0xfffffc08
d001e190:	23384cbb 	teqcs	r8, #47872	; 0xbb00
d001e194:	447c4ab4 	ldrbtmi	r4, [ip], #-2740	; 0xfffff54c
d001e198:	4000fb03 	andmi	pc, r0, r3, lsl #22
d001e19c:	58822300 	stmpl	r2, {r8, r9, sp}
d001e1a0:	6da04619 	stcvs	6, cr4, [r0, #100]!	; 0x64
d001e1a4:	ffacf7f7 			; <UNDEFINED> instruction: 0xffacf7f7
d001e1a8:	bc69f7fe 	stcllt	7, cr15, [r9], #-1016	; 0xfffffc08
d001e1ac:	462e2500 	strtmi	r2, [lr], -r0, lsl #10
d001e1b0:	bc91f7fe 	ldclt	7, cr15, [r1], {254}	; 0xfe
d001e1b4:	683888b9 	ldmdavs	r8!, {r0, r3, r4, r5, r7, fp, pc}
d001e1b8:	b29b1ccb 	addslt	r1, fp, #51968	; 0xcb00
d001e1bc:	d8092b01 	stmdale	r9, {r0, r8, r9, fp, sp}
d001e1c0:	73fef64f 	mvnsvc	pc, #82837504	; 0x4f00000
d001e1c4:	42992201 	addsmi	r2, r9, #268435456	; 0x10000000
d001e1c8:	4631bf0c 	ldrtmi	fp, [r1], -ip, lsl #30
d001e1cc:	f7f74629 			; <UNDEFINED> instruction: 0xf7f74629
d001e1d0:	e014ff63 	ands	pc, r4, r3, ror #30
d001e1d4:	43592338 	cmpmi	r9, #56, 6	; 0xe0000000
d001e1d8:	f8131863 			; <UNDEFINED> instruction: 0xf8131863
d001e1dc:	b99a2009 	ldmiblt	sl, {r0, r3, sp}
d001e1e0:	f8df4ba2 			; <UNDEFINED> instruction: 0xf8df4ba2
d001e1e4:	440bc2a0 	strmi	ip, [fp], #-672	; 0xfffffd60
d001e1e8:	442344fc 	strtmi	r4, [r3], #-1276	; 0xfffffb04
d001e1ec:	691968d8 	ldmdbvs	r9, {r3, r4, r6, r7, fp, sp, lr}
d001e1f0:	7e1b69da 			; <UNDEFINED> instruction: 0x7e1b69da
d001e1f4:	e9c466a2 	stmib	r4, {r1, r5, r7, r9, sl, sp, lr}^
d001e1f8:	e9c4c016 	stmib	r4, {r1, r2, r4, lr, pc}^
d001e1fc:	f1081318 			; <UNDEFINED> instruction: 0xf1081318
d001e200:	37080801 	strcc	r0, [r8, -r1, lsl #16]
d001e204:	bc72f7fe 	ldcllt	7, cr15, [r2], #-1016	; 0xfffffc08
d001e208:	22014997 	andcs	r4, r1, #2473984	; 0x25c000
d001e20c:	e7de5859 			; <UNDEFINED> instruction: 0xe7de5859
d001e210:	f7fe4656 			; <UNDEFINED> instruction: 0xf7fe4656
d001e214:	f898bc87 			; <UNDEFINED> instruction: 0xf898bc87
d001e218:	e9d82008 	ldmib	r8, {r3, sp}^
d001e21c:	bb620100 	bllt	0xd189e624
d001e220:	338ff504 	orrcc	pc, pc, #4, 10	; 0x1000000
d001e224:	51b8f8d3 			; <UNDEFINED> instruction: 0x51b8f8d3
d001e228:	f100440d 			; <UNDEFINED> instruction: 0xf100440d
d001e22c:	f102030c 			; <UNDEFINED> instruction: 0xf102030c
d001e230:	f24f3cff 	vfma.f32	<illegal reg q9.5>, <illegal reg q15.5>, <illegal reg q15.5>
d001e234:	90112140 	andsls	r2, r1, r0, asr #2
d001e238:	0303f023 	movweq	pc, #12323	; 0x3023	; <UNPREDICTABLE>
d001e23c:	0200f1dc 	andeq	pc, r0, #220, 2	; 0x37
d001e240:	0b01f10b 	bleq	0xd009a674
d001e244:	080cf108 	stmdaeq	ip, {r3, r8, ip, sp, lr, pc}
d001e248:	0503eba5 	streq	lr, [r3, #-2981]	; 0xfffff45b
d001e24c:	020ceb42 	andeq	lr, ip, #67584	; 0x10800
d001e250:	9212b2ab 	andsls	fp, r2, #-1342177270	; 0xb000000a
d001e254:	fcd2f7f6 	ldc2l	7, cr15, [r2], {246}	; 0xf6
d001e258:	0c2b9811 	stceq	8, cr9, [fp], #-68	; 0xffffffbc
d001e25c:	f24f9a12 	vpmin.s8	d25, d15, d2
d001e260:	300421c0 	andcc	r2, r4, r0, asr #3
d001e264:	fccaf7f6 	stc2l	7, cr15, [sl], {246}	; 0xf6
d001e268:	6da39a10 			; <UNDEFINED> instruction: 0x6da39a10
d001e26c:	23c0f8d2 	biccs	pc, r0, #13762560	; 0xd20000
d001e270:	d2504593 	subsle	r4, r0, #616562688	; 0x24c00000
d001e274:	d0ce2b00 	sbcle	r2, lr, r0, lsl #22
d001e278:	2a01e03b 	bcs	0xd009636c
d001e27c:	233cd125 	teqcs	ip, #1073741833	; 0x40000009
d001e280:	4301fb03 	movwmi	pc, #6915	; 0x1b03	; <UNPREDICTABLE>
d001e284:	335ff503 	cmpcc	pc, #12582912	; 0xc00000	; <UNPREDICTABLE>
d001e288:	53eff893 	mvnpl	pc, #9633792	; 0x930000
d001e28c:	f893b9dd 			; <UNDEFINED> instruction: 0xf893b9dd
d001e290:	3b0733ec 	blcc	0xd01eb248
d001e294:	2b0ab2db 	blcs	0xd02cae08
d001e298:	f240d815 	vtst.8	d29, d0, d5
d001e29c:	fa255503 	blx	0xd09736b0
d001e2a0:	f013f303 			; <UNDEFINED> instruction: 0xf013f303
d001e2a4:	9b0f0f01 	blls	0xd03e1eb0
d001e2a8:	463dbf0c 	ldrtmi	fp, [sp], -ip, lsl #30
d001e2ac:	f8df461d 			; <UNDEFINED> instruction: 0xf8df461d
d001e2b0:	233cc1d8 	teqcs	ip, #216, 2	; 0x36
d001e2b4:	fb0344fc 	blx	0xd00ef6ae
d001e2b8:	f501c101 			; <UNDEFINED> instruction: 0xf501c101
d001e2bc:	f8d1315f 			; <UNDEFINED> instruction: 0xf8d1315f
d001e2c0:	441d33e8 	ldrmi	r3, [sp], #-1000	; 0xfffffc18
d001e2c4:	463de7b1 			; <UNDEFINED> instruction: 0x463de7b1
d001e2c8:	2538e7f1 	ldrcs	lr, [r8, #-2033]!	; 0xfffff80f
d001e2cc:	4963434d 	stmdbmi	r3!, {r0, r2, r3, r6, r8, r9, lr}^
d001e2d0:	5c591963 	mrrcpl	9, 6, r1, r9, cr3	; <UNPREDICTABLE>
d001e2d4:	4b65b9c1 	blmi	0xd198c9e0
d001e2d8:	4d6c442b 	cfstrdmi	mvd4, [ip, #-172]!	; 0xffffff54
d001e2dc:	447d4423 	ldrbtmi	r4, [sp], #-1059	; 0xfffffbdd
d001e2e0:	691968d8 	ldmdbvs	r9, {r3, r4, r6, r7, fp, sp, lr}
d001e2e4:	7e1b69da 			; <UNDEFINED> instruction: 0x7e1b69da
d001e2e8:	e9c466a2 	stmib	r4, {r1, r5, r7, r9, sl, sp, lr}^
d001e2ec:	e9c45016 	stmib	r4, {r1, r2, r4, ip, lr}^
d001e2f0:	4c671318 	stclmi	3, cr1, [r7], #-96	; 0xffffffa0
d001e2f4:	447c9d70 	ldrbtmi	r9, [ip], #-3440	; 0xfffff290
d001e2f8:	cc0f3458 	cfstrsgt	mvf3, [pc], {88}	; 0x58
d001e2fc:	6823c50f 	stmdavs	r3!, {r0, r1, r2, r3, r8, sl, lr, pc}
d001e300:	2500602b 	strcs	r6, [r0, #-43]	; 0xffffffd5
d001e304:	bc41f7fe 	mcrrlt	7, 15, pc, r1, cr14	; <UNPREDICTABLE>
d001e308:	f44f4957 	vst2.16	{d20,d22}, [pc :64], r7
d001e30c:	585d5900 	ldmdapl	sp, {r8, fp, ip, lr}^
d001e310:	0501f045 	streq	pc, [r1, #-69]	; 0xffffffbb
d001e314:	9310e789 	tstls	r0, #35913728	; 0x2240000
d001e318:	d1ea2b00 	mvnle	r2, r0, lsl #22
d001e31c:	8174f8df 	ldrsbhi	pc, [r4, #-143]!	; 0xffffff71	; <UNPREDICTABLE>
d001e320:	318ff504 	orrcc	pc, pc, r4, lsl #10
d001e324:	f8df1cf5 			; <UNDEFINED> instruction: 0xf8df1cf5
d001e328:	44f8b170 	ldrbtmi	fp, [r8], #368	; 0x170
d001e32c:	01b8f8d1 			; <UNDEFINED> instruction: 0x01b8f8d1
d001e330:	21bcf8d1 			; <UNDEFINED> instruction: 0x21bcf8d1
d001e334:	71e0f501 	mvnvc	pc, r1, lsl #10
d001e338:	0840f108 	stmdaeq	r0, {r3, r8, ip, sp, lr, pc}^
d001e33c:	0503f025 	streq	pc, [r3, #-37]	; 0xffffffdb
d001e340:	345ff504 	ldrbcc	pc, [pc], #-1284	; 0xd001e348	; <UNPREDICTABLE>
d001e344:	444044fb 	strbmi	r4, [r0], #-1275	; 0xfffffb05
d001e348:	fac0f001 	blx	0xcf05a354
d001e34c:	eb089b10 	bl	0xd0244f94
d001e350:	eba5000a 	bl	0xce95e380
d001e354:	4619020a 	ldrmi	r0, [r9], -sl, lsl #4
d001e358:	7479f504 	ldrbtvc	pc, [r9], #-1284	; 0xfffffafc	; <UNPREDICTABLE>
d001e35c:	faa8f001 	blx	0xcea5a368
d001e360:	f10b9b10 			; <UNDEFINED> instruction: 0xf10b9b10
d001e364:	46980b40 	ldrmi	r0, [r8], r0, asr #22
d001e368:	a130f8df 	teqge	r0, pc	; <illegal shifter operand>	; <UNPREDICTABLE>
d001e36c:	f50a44fa 			; <UNDEFINED> instruction: 0xf50a44fa
d001e370:	f8d33367 			; <UNDEFINED> instruction: 0xf8d33367
d001e374:	459831c4 	ldrmi	r3, [r8, #452]	; 0x1c4
d001e378:	2740d342 	strbcs	sp, [r0, -r2, asr #6]
d001e37c:	2100ac3c 	tstcs	r0, ip, lsr ip
d001e380:	3a7ff50a 	bcc	0xd201b7b0
d001e384:	4620463a 			; <UNDEFINED> instruction: 0x4620463a
d001e388:	fa92f001 	blx	0xce4da394
d001e38c:	22084944 	andcs	r4, r8, #68, 18	; 0x110000
d001e390:	44794620 	ldrbtmi	r4, [r9], #-1568	; 0xfffff9e0
d001e394:	f001443d 			; <UNDEFINED> instruction: 0xf001443d
d001e398:	2302fa99 	movwcs	pc, #10905	; 0x2a99	; <UNPREDICTABLE>
d001e39c:	46319a0f 	ldrtmi	r9, [r1], -pc, lsl #20
d001e3a0:	9124f8cd 	smlawtls	r4, sp, r8, pc	; <UNPREDICTABLE>
d001e3a4:	373ee9cd 	ldrcc	lr, [lr, -sp, asr #19]!
d001e3a8:	321cf8da 	andscc	pc, ip, #14286848	; 0xda0000
d001e3ac:	331f4f3d 	tstcc	pc, #61, 30	; 0xf4
d001e3b0:	4413447f 	ldrmi	r4, [r3], #-1151	; 0xfffffb81
d001e3b4:	0040f107 	subeq	pc, r0, r7, lsl #2
d001e3b8:	031ff023 	tsteq	pc, #35	; 0x23	; <UNPREDICTABLE>
d001e3bc:	9342444b 	movtls	r4, #9291	; 0x244b
d001e3c0:	93432301 	movtls	r2, #13057	; 0x3301
d001e3c4:	e9cd4b2a 	stmib	sp, {r1, r3, r5, r8, r9, fp, lr}^
d001e3c8:	23203544 			; <UNDEFINED> instruction: 0x23203544
d001e3cc:	f1b99347 			; <UNDEFINED> instruction: 0xf1b99347
d001e3d0:	bf180300 	svclt	0x00180300
d001e3d4:	e9cd2301 	stmib	sp, {r0, r8, r9, sp}^
d001e3d8:	934a5640 	movtls	r5, #42560	; 0xa640
d001e3dc:	f7f1463e 			; <UNDEFINED> instruction: 0xf7f1463e
d001e3e0:	904bfecb 	subls	pc, fp, fp, asr #29
d001e3e4:	c60fcc0f 	strgt	ip, [pc], -pc, lsl #24
d001e3e8:	c60fcc0f 	strgt	ip, [pc], -pc, lsl #24
d001e3ec:	c60fcc0f 	strgt	ip, [pc], -pc, lsl #24
d001e3f0:	000fe894 	muleq	pc, r4, r8	; <UNPREDICTABLE>
d001e3f4:	000fe886 	andeq	lr, pc, r6, lsl #17
d001e3f8:	601f9b6f 	andsvs	r9, pc, pc, ror #22
d001e3fc:	bbc5f7fe 	bllt	0xcf19c3fc
d001e400:	2b007ae3 	blcs	0xd003cf94
d001e404:	4b28d054 	blmi	0xd0a5255c
d001e408:	0a00f04f 	beq	0xd005a54c
d001e40c:	e014447b 	ands	r4, r4, fp, ror r4
d001e410:	68606922 	stmdavs	r0!, {r1, r5, r8, fp, sp, lr}^
d001e414:	44384452 	ldrtmi	r4, [r8], #-1106	; 0xfffffbae
d001e418:	427ff502 	rsbsmi	pc, pc, #8388608	; 0x800000
d001e41c:	f8533288 			; <UNDEFINED> instruction: 0xf8533288
d001e420:	7a221022 	bvc	0xd08a24b0
d001e424:	2a07913c 	bcs	0xd020291c
d001e428:	4a20d10e 	bmi	0xd0852868
d001e42c:	4452447a 	ldrbmi	r4, [r2], #-1146	; 0xfffffb86
d001e430:	f8804410 			; <UNDEFINED> instruction: 0xf8804410
d001e434:	f10a1040 			; <UNDEFINED> instruction: 0xf10a1040
d001e438:	69620a01 	stmdbvs	r2!, {r0, r9, fp}^
d001e43c:	d3e74592 	mvnle	r4, #612368384	; 0x24800000
d001e440:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d001e444:	e78f343c 			; <UNDEFINED> instruction: 0xe78f343c
d001e448:	008aeb00 	addeq	lr, sl, r0, lsl #22
d001e44c:	a93c2204 	ldmdbge	ip!, {r2, r9, sp}
d001e450:	44589310 	ldrbmi	r9, [r8], #-784	; 0xfffffcf0
d001e454:	fa3af001 	blx	0xd0eda460
d001e458:	e7ec9b10 			; <UNDEFINED> instruction: 0xe7ec9b10
d001e45c:	0013fe4a 	andseq	pc, r3, sl, asr #28
d001e460:	0013fe48 	andseq	pc, r3, r8, asr #28
d001e464:	0013fe50 	andseq	pc, r3, r0, asr lr	; <UNPREDICTABLE>
d001e468:	0013fe44 	andseq	pc, r3, r4, asr #28
d001e46c:	0013fe24 	andseq	pc, r3, r4, lsr #28
d001e470:	d0010000 	andle	r0, r1, r0
d001e474:	ffffe4ce 			; <UNDEFINED> instruction: 0xffffe4ce
d001e478:	ffffe7dd 			; <UNDEFINED> instruction: 0xffffe7dd
d001e47c:	0000827e 	andeq	r8, r0, lr, ror r2
d001e480:	0000826e 	andeq	r8, r0, lr, ror #4
d001e484:	ffffe7b2 			; <UNDEFINED> instruction: 0xffffe7b2
d001e488:	00008150 	andeq	r8, r0, r0, asr r1
d001e48c:	ffffe701 			; <UNDEFINED> instruction: 0xffffe701
d001e490:	0000810e 	andeq	r8, r0, lr, lsl #2
d001e494:	0015337a 	andseq	r3, r5, sl, ror r3
d001e498:	00153360 	andseq	r3, r5, r0, ror #6
d001e49c:	00008098 	muleq	r0, r8, r0
d001e4a0:	0000026e 	andeq	r0, r0, lr, ror #4
d001e4a4:	001532f4 			; <UNDEFINED> instruction: 0x001532f4
d001e4a8:	00007ff8 	strdeq	r7, [r0], -r8
d001e4ac:	00153278 	andseq	r3, r5, r8, ror r2
d001e4b0:	3b077a23 	blcc	0xd01fcd44
d001e4b4:	2b0ab2db 	blcs	0xd02cb028
d001e4b8:	f240d805 	vadd.i8	d29, d0, d5
d001e4bc:	fa225203 	blx	0xd08b2cd0
d001e4c0:	07d9f303 	ldrbeq	pc, [r9, r3, lsl #6]	; <UNPREDICTABLE>
d001e4c4:	4b2ed4bc 	blmi	0xd0bd37bc
d001e4c8:	68602204 	stmdavs	r0!, {r2, r9, sp}^
d001e4cc:	447b4621 	ldrbtmi	r4, [fp], #-1569	; 0xfffff9df
d001e4d0:	33404438 	movtcc	r4, #1080	; 0x438
d001e4d4:	f0014418 			; <UNDEFINED> instruction: 0xf0014418
d001e4d8:	e7b1f9f9 			; <UNDEFINED> instruction: 0xe7b1f9f9
d001e4dc:	f43f2c00 			; <UNDEFINED> instruction: 0xf43f2c00
d001e4e0:	4b28a8c5 	blmi	0xd0a487fc
d001e4e4:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d001e4e8:	f47e2a00 			; <UNDEFINED> instruction: 0xf47e2a00
d001e4ec:	4a26ab9f 	bmi	0xd09c9370
d001e4f0:	f7fe447a 			; <UNDEFINED> instruction: 0xf7fe447a
d001e4f4:	4d25bec6 	stcmi	14, cr11, [r5, #-792]!	; 0xfffffce8
d001e4f8:	4a1e2338 	bmi	0xd07a71e0
d001e4fc:	9912447d 	ldmdbls	r2, {r0, r2, r3, r4, r5, r6, sl, lr}
d001e500:	5304fb03 	movwpl	pc, #19203	; 0x4b03	; <UNPREDICTABLE>
d001e504:	42915c9a 	addsmi	r5, r1, #39424	; 0x9a00
d001e508:	4a1bd105 	bmi	0xd0712924
d001e50c:	5c9a9913 			; <UNDEFINED> instruction: 0x5c9a9913
d001e510:	f43f428a 			; <UNDEFINED> instruction: 0xf43f428a
d001e514:	4b1eabd2 	blmi	0xd07c9464
d001e518:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d001e51c:	f47e2a00 			; <UNDEFINED> instruction: 0xf47e2a00
d001e520:	4a1cab85 	bmi	0xd074933c
d001e524:	f7fe447a 			; <UNDEFINED> instruction: 0xf7fe447a
d001e528:	4d1bbeac 	ldcmi	14, cr11, [fp, #-688]	; 0xfffffd50
d001e52c:	447d4b13 	ldrbtmi	r4, [sp], #-2835	; 0xfffff4ed
d001e530:	681c442b 	ldmdavs	ip, {r0, r1, r3, r5, sl, lr}
d001e534:	7f80f5b4 	svcvc	0x0080f5b4
d001e538:	ab5df47f 	blge	0xd179b73c
d001e53c:	2b006dab 	blcs	0xd0039bf0
d001e540:	ab74f47e 	blge	0xd1d5b740
d001e544:	447b4b15 	ldrbtmi	r4, [fp], #-2837	; 0xfffff4eb
d001e548:	be86f7fe 	mcrlt	7, 4, pc, cr6, cr14, {7}	; <UNPREDICTABLE>
d001e54c:	24014b14 	strcs	r4, [r1], #-2836	; 0xfffff4ec
d001e550:	f503447b 			; <UNDEFINED> instruction: 0xf503447b
d001e554:	f503139f 			; <UNDEFINED> instruction: 0xf503139f
d001e558:	681a53f1 	ldmdavs	sl, {r0, r4, r5, r6, r7, r8, r9, ip, lr}
d001e55c:	601a4432 	andsvs	r4, sl, r2, lsr r4
d001e560:	befef7fe 	mrclt	7, 7, APSR_nzcv, cr14, cr14, {7}
d001e564:	2b009b13 	blcs	0xd00451b8
d001e568:	a877f47f 	ldmdage	r7!, {r0, r1, r2, r3, r4, r5, r6, sl, ip, sp, lr, pc}^
d001e56c:	d1b82d00 			; <UNDEFINED> instruction: 0xd1b82d00
d001e570:	b86cf7ff 	stmdalt	ip!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}^
d001e574:	0013fe48 	andseq	pc, r3, r8, asr #28
d001e578:	0013fe4b 	andseq	pc, r3, fp, asr #28
d001e57c:	00143624 	andseq	r3, r4, r4, lsr #12
d001e580:	001531d6 			; <UNDEFINED> instruction: 0x001531d6
d001e584:	00007f20 	andeq	r7, r0, r0, lsr #30
d001e588:	ffffe0c9 			; <UNDEFINED> instruction: 0xffffe0c9
d001e58c:	00007f08 	andeq	r7, r0, r8, lsl #30
d001e590:	00007eec 	andeq	r7, r0, ip, ror #29
d001e594:	ffffe362 			; <UNDEFINED> instruction: 0xffffe362
d001e598:	00007ed6 	ldrdeq	r7, [r0], -r6
d001e59c:	ffffe32d 			; <UNDEFINED> instruction: 0xffffe32d
d001e5a0:	00007eb4 			; <UNDEFINED> instruction: 0x00007eb4

Disassembly of section .text.sidc_compile_project:

d001e5a4 <.text.sidc_compile_project>:
d001e5a4:	43f7e92d 	mvnsmi	lr, #737280	; 0xb4000
d001e5a8:	802cf8dd 	ldrdhi	pc, [ip], -sp	; <UNPREDICTABLE>
d001e5ac:	9c0c460f 	stcls	6, cr4, [ip], {15}
d001e5b0:	46052100 	strmi	r2, [r5], -r0, lsl #2
d001e5b4:	46204616 			; <UNDEFINED> instruction: 0x46204616
d001e5b8:	f8c82214 			; <UNDEFINED> instruction: 0xf8c82214
d001e5bc:	f8dd1000 			; <UNDEFINED> instruction: 0xf8dd1000
d001e5c0:	93019028 	movwls	r9, #4136	; 0x1028
d001e5c4:	f974f001 			; <UNDEFINED> instruction: 0xf974f001
d001e5c8:	1e72b185 	expned	f3, f5
d001e5cc:	2a0f9b01 	bcs	0xd04051d8
d001e5d0:	4632d80c 	ldrtmi	sp, [r2], -ip, lsl #16
d001e5d4:	46284639 			; <UNDEFINED> instruction: 0x46284639
d001e5d8:	f8cd940c 			; <UNDEFINED> instruction: 0xf8cd940c
d001e5dc:	f8cd802c 			; <UNDEFINED> instruction: 0xf8cd802c
d001e5e0:	b0039028 	andlt	r9, r3, r8, lsr #32
d001e5e4:	43f0e8bd 	mvnsmi	lr, #12386304	; 0xbd0000
d001e5e8:	ba0ef7fe 	blt	0xd03dc5e8
d001e5ec:	447d4d04 	ldrbtmi	r4, [sp], #-3332	; 0xfffff2fc
d001e5f0:	c40fcd0f 	strgt	ip, [pc], #-3343	; 0xd001e5f8
d001e5f4:	2000682b 	andcs	r6, r0, fp, lsr #16
d001e5f8:	b0036023 	andlt	r6, r3, r3, lsr #32
d001e5fc:	83f0e8bd 	mvnshi	lr, #12386304	; 0xbd0000
d001e600:	00002b72 	andeq	r2, r0, r2, ror fp

Disassembly of section .text.memset:

d001f8b0 <.text.memset>:
d001f8b0:	b2c9b15a 	sbclt	fp, r9, #-2147483626	; 0x80000016
d001f8b4:	b4104603 	ldrlt	r4, [r0], #-1539	; 0xfffff9fd
d001f8b8:	461a1884 	ldrmi	r1, [sl], -r4, lsl #17
d001f8bc:	42a33301 	adcmi	r3, r3, #67108864	; 0x4000000
d001f8c0:	d1fa7011 	mvnsle	r7, r1, lsl r0
d001f8c4:	4b04f85d 	blmi	0xd015da40
d001f8c8:	47704770 			; <UNDEFINED> instruction: 0x47704770

Disassembly of section .text.memcpy:

d001f8cc <.text.memcpy>:
d001f8cc:	4603b162 	strmi	fp, [r3], -r2, ror #2
d001f8d0:	1885b430 	stmne	r5, {r4, r5, sl, ip, sp, pc}
d001f8d4:	461c780a 	ldrmi	r7, [ip], -sl, lsl #16
d001f8d8:	31013301 	tstcc	r1, r1, lsl #6
d001f8dc:	42abb2d2 	adcmi	fp, fp, #536870925	; 0x2000000d
d001f8e0:	d1f77022 	mvnsle	r7, r2, lsr #32
d001f8e4:	4770bc30 			; <UNDEFINED> instruction: 0x4770bc30
d001f8e8:	bf004770 	svclt	0x00004770

Disassembly of section .text.memcmp:

d001f8ec <.text.memcmp>:
d001f8ec:	46034402 	strmi	r4, [r3], -r2, lsl #8
d001f8f0:	d0134290 	mulsle	r3, r0, r2
d001f8f4:	e002b470 	and	fp, r2, r0, ror r4
d001f8f8:	46034290 			; <UNDEFINED> instruction: 0x46034290
d001f8fc:	f813d00b 			; <UNDEFINED> instruction: 0xf813d00b
d001f900:	f8115b01 			; <UNDEFINED> instruction: 0xf8115b01
d001f904:	46184b01 	ldrmi	r4, [r8], -r1, lsl #22
d001f908:	42a5b2ee 	adcmi	fp, r5, #-536870898	; 0xe000000e
d001f90c:	d0f3b2e3 	rscsle	fp, r3, r3, ror #5
d001f910:	bc701af0 			; <UNDEFINED> instruction: 0xbc701af0
d001f914:	20004770 	andcs	r4, r0, r0, ror r7
d001f918:	4770bc70 			; <UNDEFINED> instruction: 0x4770bc70
d001f91c:	47702000 	ldrbmi	r2, [r0, -r0]!

Disassembly of section .text.sb_f_fixed:

d001f920 <.text.sb_f_fixed>:
d001f920:	0b40eeb5 	bleq	0xd105b3fc
d001f924:	4ff0e92d 	svcmi	0x00f0e92d
d001f928:	fa10eef1 	blx	0xd045b4f4
d001f92c:	d0354606 	eorsle	r4, r5, r6, lsl #12
d001f930:	6b04eeb2 	blvs	0xd015b400
d001f934:	eeb02400 	cdp	4, 11, cr2, cr0, cr0, {0}
d001f938:	eeb47b40 	vcmp.f64	d7, d0
d001f93c:	eef10bc6 	vsqrt.f64	d16, d6
d001f940:	da22fa10 	ble	0xd08de188
d001f944:	6b00eeb7 	blvs	0xd005b428
d001f948:	7bc6eeb4 	blvc	0xcf1db420
d001f94c:	fa10eef1 	blx	0xd045b518
d001f950:	80a6f140 	adchi	pc, r6, r0, asr #2
d001f954:	5b04eeb2 	blpl	0xd015b424
d001f958:	73a1f46f 			; <UNDEFINED> instruction: 0x73a1f46f
d001f95c:	eeb4e004 	cdp	0, 11, cr14, cr4, cr4, {0}
d001f960:	eef17bc6 	vsqrt.f64	d23, d6
d001f964:	d504fa10 	strle	pc, [r4, #-2576]	; 0xfffff5f0
d001f968:	ee273c01 	cdp	12, 2, cr3, cr7, cr1, {0}
d001f96c:	429c7b05 	addsmi	r7, ip, #5120	; 0x1400
d001f970:	ea24daf5 	b	0xd095654c
d001f974:	ea6f73e4 	b	0xd1bfc90c
d001f978:	459c0c01 	ldrmi	r0, [ip, #3073]	; 0xc01
d001f97c:	2000dd16 	andcs	sp, r0, r6, lsl sp
d001f980:	8ff0e8bd 	svchi	0x00f0e8bd
d001f984:	7f9af5b4 	svcvc	0x009af5b4
d001f988:	ee87d0dc 	mcr	0, 4, sp, cr7, cr12, {6}
d001f98c:	34017b06 	strcc	r7, [r1], #-2822	; 0xfffff4fa
d001f990:	7bc6eeb4 	blvc	0xcf1db468
d001f994:	fa10eef1 	blx	0xd045b560
d001f998:	e7d3daf4 			; <UNDEFINED> instruction: 0xe7d3daf4
d001f99c:	eeb02300 	cdp	3, 11, cr2, cr0, cr0, {0}
d001f9a0:	461c7b40 	ldrmi	r7, [ip], -r0, asr #22
d001f9a4:	0c01ea6f 			; <UNDEFINED> instruction: 0x0c01ea6f
d001f9a8:	dce8459c 	cfstr64le	mvdx4, [r8], #624	; 0x270
d001f9ac:	0b00f04f 	bleq	0xd005baf0
d001f9b0:	5b04eeb2 	blpl	0xd015b480
d001f9b4:	0902ea41 	stmdbeq	r2, {r0, r6, r9, fp, sp, lr, pc}
d001f9b8:	38fff10c 	ldmcc	pc!, {r2, r3, r8, ip, sp, lr, pc}^	; <UNPREDICTABLE>
d001f9bc:	43f74658 	mvnsmi	r4, #88, 12	; 0x5800000
d001f9c0:	0a30f04f 	beq	0xd0c5bb04
d001f9c4:	4b38ed9f 	blmi	0xd0e5b048
d001f9c8:	0b40eeb5 	bleq	0xd105b4a4
d001f9cc:	fa10eef1 	blx	0xd045b598
d001f9d0:	42a3d030 	adcmi	sp, r3, #48	; 0x30
d001f9d4:	eefddc2e 	cdp	12, 15, cr13, cr13, cr14, {1}
d001f9d8:	f10b6bc7 			; <UNDEFINED> instruction: 0xf10b6bc7
d001f9dc:	ee160b01 	vnmls.f64	d0, d6, d1
d001f9e0:	ee161a90 	vmov	r1, s13
d001f9e4:	29092a90 	stmdbcs	r9, {r4, r7, r9, fp, sp}
d001f9e8:	2209bfa8 	andcs	fp, r9, #168, 30	; 0x2a0
d001f9ec:	0f11f1bb 	svceq	0x0011f1bb
d001f9f0:	72e2ea22 	rscvc	lr, r2, #139264	; 0x22000
d001f9f4:	2a90ee06 	bcs	0xce45b214
d001f9f8:	6be6eeb8 	blvs	0xcf9db4e0
d001f9fc:	7b46ee37 	blvc	0xd11db2e0
d001fa00:	7b05ee27 	blvc	0xd019b2a4
d001fa04:	459cdc16 	ldrmi	sp, [ip, #3094]	; 0xc16
d001fa08:	3230d018 	eorscc	sp, r0, #24
d001fa0c:	5432b2d2 	ldrtpl	fp, [r2], #-722	; 0xfffffd2e
d001fa10:	3b013001 	blcc	0xd006ba1c
d001fa14:	d0b34543 	adcsle	r4, r3, r3, asr #10
d001fa18:	d1d51c59 	bicsle	r1, r5, r9, asr ip
d001fa1c:	0f00f1b9 	svceq	0x0000f1b9
d001fa20:	eeb5d0d2 	mrc	0, 5, sp, cr5, cr2, {6}
d001fa24:	f04f0b40 			; <UNDEFINED> instruction: 0xf04f0b40
d001fa28:	5432022e 	ldrtpl	r0, [r2], #-558	; 0xfffffdd2
d001fa2c:	eef13001 	cdp	0, 15, cr3, cr1, cr1, {0}
d001fa30:	d1cefa10 	bicle	pc, lr, r0, lsl sl	; <UNPREDICTABLE>
d001fa34:	d0ec459c 	smlalle	r4, ip, ip, r5
d001fa38:	e7e82230 			; <UNDEFINED> instruction: 0xe7e82230
d001fa3c:	dd1e2905 	vldrle.16	s4, [lr, #-10]	; <UNPREDICTABLE>
d001fa40:	dd172800 	ldcle	8, cr2, [r7, #-0]
d001fa44:	0e00eb06 	vmlaeq.f64	d14, d0, d6
d001fa48:	f8124672 			; <UNDEFINED> instruction: 0xf8124672
d001fa4c:	292e1d01 	stmdbcs	lr!, {r0, r8, sl, fp, ip}
d001fa50:	0502eb07 	streq	lr, [r2, #-2823]	; 0xfffff4f9
d001fa54:	2938d003 	ldmdbcs	r8!, {r0, r1, ip, lr, pc}
d001fa58:	f882d91f 			; <UNDEFINED> instruction: 0xf882d91f
d001fa5c:	3501a000 	strcc	sl, [r1, #-0]
d001fa60:	2800d1f3 	stmdacs	r0, {r0, r1, r4, r5, r6, r7, r8, ip, lr, pc}
d001fa64:	4672dd06 	ldrbtmi	sp, [r2], -r6, lsl #26
d001fa68:	1c01f812 	stcne	8, cr15, [r1], {18}
d001fa6c:	1901f802 	stmdbne	r1, {r1, fp, ip, sp, lr, pc}
d001fa70:	d1f94296 			; <UNDEFINED> instruction: 0xd1f94296
d001fa74:	0231f04f 	eorseq	pc, r1, #79	; 0x4f
d001fa78:	70323001 	eorsvc	r3, r2, r1
d001fa7c:	d1c8e7c9 	bicle	lr, r8, r9, asr #15
d001fa80:	7bc4eeb4 	blvc	0xcf15b558
d001fa84:	fa10eef1 	blx	0xd045b650
d001fa88:	2800dcda 	stmdacs	r0, {r1, r3, r4, r6, r7, sl, fp, ip, lr, pc}
d001fa8c:	1832d0c1 	ldmdane	r2!, {r0, r6, r7, ip, lr, pc}
d001fa90:	2c01f812 	stccs	8, cr15, [r1], {18}
d001fa94:	d5bc07d2 	ldrle	r0, [ip, #2002]!	; 0x7d2
d001fa98:	3101e7d2 	ldrdcc	lr, [r1, -r2]
d001fa9c:	e7b87011 			; <UNDEFINED> instruction: 0xe7b87011
d001faa0:	e77f4623 	ldrb	r4, [pc, -r3, lsr #12]!
d001faa4:	8000f3af 	andhi	pc, r0, pc, lsr #7
d001faa8:	812dea11 			; <UNDEFINED> instruction: 0x812dea11
d001faac:	3d719799 	ldclcc	7, cr9, [r1, #-612]!	; 0xfffffd9c

Disassembly of section .text.sb_f_exponent:

d001fab0 <.text.sb_f_exponent>:
d001fab0:	0b40eeb5 	bleq	0xd105b58c
d001fab4:	4ff0e92d 	svcmi	0x00f0e92d
d001fab8:	fa10eef1 	blx	0xd045b684
d001fabc:	d0344607 	eorsle	r4, r4, r7, lsl #12
d001fac0:	6b04eeb2 	blvs	0xd015b590
d001fac4:	0bc6eeb4 	bleq	0xcf1db59c
d001fac8:	fa10eef1 	blx	0xd045b694
d001facc:	80cef2c0 	sbchi	pc, lr, r0, asr #5
d001fad0:	7b40eeb0 	blvc	0xd105b598
d001fad4:	e0022400 	and	r2, r2, r0, lsl #8
d001fad8:	7f9af5b4 	svcvc	0x009af5b4
d001fadc:	ee87d007 	cdp	0, 8, cr13, cr7, cr7, {0}
d001fae0:	34017b06 	strcc	r7, [r1], #-2822	; 0xfffff4fa
d001fae4:	7bc6eeb4 	blvc	0xcf1db5bc
d001fae8:	fa10eef1 	blx	0xd045b6b4
d001faec:	eeb7daf4 			; <UNDEFINED> instruction: 0xeeb7daf4
d001faf0:	eeb46b00 	vmov.f64	d6, #64	; 0x3e000000  0.125
d001faf4:	eef17bc6 	vsqrt.f64	d23, d6
d001faf8:	d519fa10 	ldrle	pc, [r9, #-2576]	; 0xfffff5f0
d001fafc:	5b04eeb2 	blpl	0xd015b5cc
d001fb00:	70a1f46f 	adcvc	pc, r1, pc, ror #8
d001fb04:	eeb4e004 	cdp	0, 11, cr14, cr4, cr4, {0}
d001fb08:	eef17bc6 	vsqrt.f64	d23, d6
d001fb0c:	d50ffa10 	strle	pc, [pc, #-2576]	; 0xd001f104
d001fb10:	ee273c01 	cdp	12, 2, cr3, cr7, cr1, {0}
d001fb14:	42847b05 	addmi	r7, r4, #5120	; 0x1400
d001fb18:	f111daf5 			; <UNDEFINED> instruction: 0xf111daf5
d001fb1c:	d50a0e01 	strle	r0, [sl, #-3585]	; 0xfffff1ff
d001fb20:	2102463e 	tstcs	r2, lr, lsr r6
d001fb24:	22002501 	andcs	r2, r0, #4194304	; 0x400000
d001fb28:	eeb0e062 	cdp	0, 11, cr14, cr0, cr2, {3}
d001fb2c:	24007b40 	strcs	r7, [r0], #-2880	; 0xfffff4c0
d001fb30:	0e01f111 	mcreq	1, 0, pc, cr1, cr1, {0}	; <UNPREDICTABLE>
d001fb34:	2500d4f4 	strcs	sp, [r0, #-1268]	; 0xfffffb0c
d001fb38:	5b04eeb2 	blpl	0xd015b608
d001fb3c:	0902ea41 	stmdbeq	r2, {r0, r6, r9, fp, sp, lr, pc}
d001fb40:	462a1c88 	strtmi	r1, [sl], -r8, lsl #25
d001fb44:	0807ea6f 	stmdaeq	r7, {r0, r1, r2, r3, r5, r6, r9, fp, sp, lr, pc}
d001fb48:	0a30f04f 	beq	0xd0c5bc8c
d001fb4c:	0b2ef04f 	bleq	0xd0bdbc90
d001fb50:	4b49ed9f 	blmi	0xd129b1d4
d001fb54:	0b40eeb5 	bleq	0xd105b630
d001fb58:	fa10eef1 	blx	0xd045b724
d001fb5c:	4575d114 	ldrbmi	sp, [r5, #-276]!	; 0xfffffeec
d001fb60:	2130d002 	teqcs	r0, r2
d001fb64:	320154b9 	andcc	r5, r1, #-1191182336	; 0xb9000000
d001fb68:	42853501 	addmi	r3, r5, #4194304	; 0x400000
d001fb6c:	2d01d03d 	stccs	0, cr13, [r1, #-244]	; 0xffffff0c
d001fb70:	f1b9d1f0 			; <UNDEFINED> instruction: 0xf1b9d1f0
d001fb74:	d0ed0f00 	rscle	r0, sp, r0, lsl #30
d001fb78:	0b40eeb5 	bleq	0xd105b654
d001fb7c:	b002f807 	andlt	pc, r2, r7, lsl #16
d001fb80:	eef13201 	cdp	2, 15, cr3, cr1, cr1, {0}
d001fb84:	d0eafa10 	rscle	pc, sl, r0, lsl sl	; <UNPREDICTABLE>
d001fb88:	6bc7eefd 	blvs	0xcf21b784
d001fb8c:	6a90ee16 	bvs	0xce45b3ec
d001fb90:	1a90ee16 	bne	0xce45b3f0
d001fb94:	bfa82e09 	svclt	0x00a82e09
d001fb98:	45752109 	ldrbmi	r2, [r5, #-265]!	; 0xfffffef7
d001fb9c:	71e1ea21 	mvnvc	lr, r1, lsr #20
d001fba0:	1a90ee06 	bne	0xce45b3c0
d001fba4:	6be6eeb8 	blvs	0xcf9db68c
d001fba8:	7b46ee37 	blvc	0xd11db48c
d001fbac:	7b05ee27 	blvc	0xd019b450
d001fbb0:	3130d002 	teqcc	r0, r2
d001fbb4:	e7d5b2c9 	ldrb	fp, [r5, r9, asr #5]
d001fbb8:	dd462e05 	stclle	14, cr2, [r6, #-20]	; 0xffffffec
d001fbbc:	dd0d2a00 	vstrle	s4, [sp, #-0]
d001fbc0:	f81118b9 			; <UNDEFINED> instruction: 0xf81118b9
d001fbc4:	2e2e6d01 	cdpcs	13, 2, cr6, cr14, cr1, {0}
d001fbc8:	0c01eb08 			; <UNDEFINED> instruction: 0x0c01eb08
d001fbcc:	2e38d003 	cdpcs	0, 3, cr13, cr8, cr3, {0}
d001fbd0:	f881d949 			; <UNDEFINED> instruction: 0xf881d949
d001fbd4:	f1bca000 			; <UNDEFINED> instruction: 0xf1bca000
d001fbd8:	d1f23fff 	ldrshle	r3, [r2, #255]!	; 0xff
d001fbdc:	f04f3501 			; <UNDEFINED> instruction: 0xf04f3501
d001fbe0:	34010131 	strcc	r0, [r1], #-305	; 0xfffffecf
d001fbe4:	70394285 	eorsvc	r4, r9, r5, lsl #5
d001fbe8:	18bed1c1 	ldmne	lr!, {r0, r6, r7, r8, ip, lr, pc}
d001fbec:	1c911c55 	ldcne	12, cr1, [r1], {85}	; 0x55
d001fbf0:	bf142b00 	svclt	0x00142b00
d001fbf4:	20652045 	rsbcs	r2, r5, r5, asr #32
d001fbf8:	70302c00 	eorsvc	r2, r0, r0, lsl #24
d001fbfc:	232dbfb4 			; <UNDEFINED> instruction: 0x232dbfb4
d001fc00:	2c00232b 	stccs	3, cr2, [r0], {43}	; 0x2b
d001fc04:	bfb8557b 	svclt	0x00b8557b
d001fc08:	2c634264 	sfmcs	f4, 2, [r3], #-400	; 0xfffffe70
d001fc0c:	4b1cdd06 	blmi	0xd075702c
d001fc10:	0304fba3 	movweq	pc, #19363	; 0x4ba3	; <UNPREDICTABLE>
d001fc14:	3330095b 	teqcc	r0, #1490944	; 0x16c000
d001fc18:	1cd1547b 	cfldrdne	mvd5, [r1], {123}	; 0x7b
d001fc1c:	187d4a19 	ldmdane	sp!, {r0, r3, r4, r9, fp, lr}^
d001fc20:	0304fba2 	movweq	pc, #19362	; 0x4ba2	; <UNPREDICTABLE>
d001fc24:	08db1c88 	ldmeq	fp, {r3, r7, sl, fp, ip}^
d001fc28:	6203fba2 	andvs	pc, r3, #165888	; 0x28800
d001fc2c:	0683eb03 	streq	lr, [r3], r3, lsl #22
d001fc30:	eba408d2 	bl	0xce921f80
d001fc34:	eb020446 	bl	0xd00a0d54
d001fc38:	34300282 	ldrtcc	r0, [r0], #-642	; 0xfffffd7e
d001fc3c:	0342eba3 	movteq	lr, #11171	; 0x2ba3
d001fc40:	547b3330 	ldrbtpl	r3, [fp], #-816	; 0xfffffcd0
d001fc44:	e8bd706c 	pop	{r2, r3, r5, r6, ip, sp, lr}
d001fc48:	d18d8ff0 	strdle	r8, [sp, r0]
d001fc4c:	7bc4eeb4 	blvc	0xcf15b724
d001fc50:	fa10eef1 	blx	0xd045b81c
d001fc54:	2a00dcb2 	bcs	0xd0056f24
d001fc58:	18b9d086 	ldmne	r9!, {r1, r2, r7, ip, lr, pc}
d001fc5c:	1c01f811 	stcne	8, cr15, [r1], {17}
d001fc60:	d58107c9 	strle	r0, [r1, #1993]	; 0x7c9
d001fc64:	3601e7aa 	strcc	lr, [r1], -sl, lsr #15
d001fc68:	e77d700e 	ldrb	r7, [sp, -lr]!
d001fc6c:	7b40eeb0 	blvc	0xd105b734
d001fc70:	e73c2400 	ldr	r2, [ip, -r0, lsl #8]!
d001fc74:	8000f3af 	andhi	pc, r0, pc, lsr #7
d001fc78:	812dea11 			; <UNDEFINED> instruction: 0x812dea11
d001fc7c:	3d719799 	ldclcc	7, cr9, [r1, #-612]!	; 0xfffffd9c
d001fc80:	51eb851f 	mvnpl	r8, pc, lsl r5
d001fc84:	cccccccd 	stclgt	12, cr12, [ip], {205}	; 0xcd

Disassembly of section .text.sb_flush.part.0:

d001fc88 <.text.sb_flush.part.0>:
d001fc88:	2090f8d0 			; <UNDEFINED> instruction: 0x2090f8d0
d001fc8c:	4b07b16a 	blmi	0xd020c23c
d001fc90:	0110f100 	tsteq	r0, r0, lsl #2	; <UNPREDICTABLE>
d001fc94:	681b689b 	ldmdavs	fp, {r0, r1, r3, r4, r7, fp, sp, lr}
d001fc98:	685bb510 	ldmdavs	fp, {r4, r8, sl, ip, sp, pc}^
d001fc9c:	20004604 	andcs	r4, r0, r4, lsl #12
d001fca0:	23004798 	movwcs	r4, #1944	; 0x798
d001fca4:	3090f8c4 	addscc	pc, r0, r4, asr #17
d001fca8:	4770bd10 			; <UNDEFINED> instruction: 0x4770bd10
d001fcac:	2001f000 	andcs	pc, r1, r0

Disassembly of section .text.sb_char:

d001fcb0 <.text.sb_char>:
d001fcb0:	b51068c3 	ldrlt	r6, [r0, #-2243]	; 0xfffff73d
d001fcb4:	b1834604 	orrlt	r4, r3, r4, lsl #12
d001fcb8:	3090f8d0 			; <UNDEFINED> instruction: 0x3090f8d0
d001fcbc:	44031c5a 	strmi	r1, [r3], #-3162	; 0xfffff3a6
d001fcc0:	f8c02a80 			; <UNDEFINED> instruction: 0xf8c02a80
d001fcc4:	74192090 	ldrvc	r2, [r9], #-144	; 0xffffff70
d001fcc8:	68a3d013 	stmiavs	r3!, {r0, r1, r4, ip, lr, pc}
d001fccc:	4200f06f 	andmi	pc, r0, #111	; 0x6f
d001fcd0:	d2014293 	andle	r4, r1, #805306377	; 0x30000009
d001fcd4:	60a33301 	adcvs	r3, r3, r1, lsl #6
d001fcd8:	6800bd10 	stmdavs	r0, {r4, r8, sl, fp, ip, sp, pc}
d001fcdc:	d0f42800 	rscsle	r2, r4, r0, lsl #16
d001fce0:	68a36862 	stmiavs	r3!, {r1, r5, r6, fp, sp, lr}
d001fce4:	bf182a00 	svclt	0x00182a00
d001fce8:	42933a01 	addsmi	r3, r3, #4096	; 0x1000
d001fcec:	54c1d2ee 	strbpl	sp, [r1], #750	; 0x2ee
d001fcf0:	f7ffe7eb 			; <UNDEFINED> instruction: 0xf7ffe7eb
d001fcf4:	68a3ffc9 	stmiavs	r3!, {r0, r3, r6, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d001fcf8:	bf00e7e8 	svclt	0x0000e7e8

Disassembly of section .text.sb_number:

d001fd10 <.text.sb_number>:
d001fd10:	4ff0e92d 	svcmi	0x00f0e92d
d001fd14:	8b02ed2d 	blhi	0xd00db1d0
d001fd18:	ee08b09b 	mcr	0, 0, fp, cr8, cr11, {4}
d001fd1c:	93070a10 	movwls	r0, #31248	; 0x7a10
d001fd20:	92069b2b 	andls	r9, r6, #44032	; 0xac00
d001fd24:	d13e2b00 	teqle	lr, r0, lsl #22
d001fd28:	e9dd4bbf 	ldmib	sp, {r0, r1, r2, r3, r4, r5, r7, r8, r9, fp, lr}^
d001fd2c:	447b1206 	ldrbtmi	r1, [fp], #-518	; 0xfffffdfa
d001fd30:	460b9305 	strmi	r9, [fp], -r5, lsl #6
d001fd34:	d13e4313 	teqle	lr, r3, lsl r3
d001fd38:	9a2a9b2a 	bls	0xd0ac69e8
d001fd3c:	bf183b00 	svclt	0x00183b00
d001fd40:	2a002301 	bcs	0xd002894c
d001fd44:	9303d137 	movwls	sp, #12599	; 0x3137
d001fd48:	2b009b27 	blcs	0xd00469ec
d001fd4c:	9b28d179 	blls	0xd0a54338
d001fd50:	f1000759 			; <UNDEFINED> instruction: 0xf1000759
d001fd54:	ea4f8101 	b	0xd1400160
d001fd58:	9a2c0983 	bls	0xd0b2236c
d001fd5c:	1a40f3c9 	bne	0xd105cc88
d001fd60:	0920f009 	stmdbeq	r0!, {r0, r3, ip, sp, lr, pc}
d001fd64:	2a004653 	bcs	0xd00316b8
d001fd68:	9a26d072 	bls	0xd09d3f38
d001fd6c:	f0002a10 			; <UNDEFINED> instruction: 0xf0002a10
d001fd70:	9a2680f8 	bls	0xd09c0158
d001fd74:	f0002a02 			; <UNDEFINED> instruction: 0xf0002a02
d001fd78:	9a268144 	bls	0xd09c0290
d001fd7c:	9a032a08 	bls	0xd00ea5a4
d001fd80:	8122f000 	msrhi	CPSR_x, r0
d001fd84:	2600992a 	strcs	r9, [r0], -sl, lsr #18
d001fd88:	82a0f8df 	adchi	pc, r0, #14614528	; 0xdf0000
d001fd8c:	44f84291 	ldrbtmi	r4, [r8], #657	; 0x291
d001fd90:	9a03dc69 	bls	0xd0116f3c
d001fd94:	19942700 	ldmibne	r4, {r8, r9, sl, sp}
d001fd98:	44239a29 	strtmi	r9, [r3], #-2601	; 0xfffff5d7
d001fd9c:	f0c04293 			; <UNDEFINED> instruction: 0xf0c04293
d001fda0:	463c80e8 	ldrtmi	r8, [ip], -r8, ror #1
d001fda4:	4ba2e0e7 	blmi	0xce8d8148
d001fda8:	1206e9dd 	andne	lr, r6, #3620864	; 0x374000
d001fdac:	9305447b 	movwls	r4, #21627	; 0x547b
d001fdb0:	4313460b 	tstmi	r3, #11534336	; 0xb00000
d001fdb4:	ab09d0c0 	blge	0xd02940bc
d001fdb8:	26012200 	strcs	r2, [r1], -r0, lsl #4
d001fdbc:	e9dd9304 	ldmib	sp, {r2, r8, r9, ip, pc}^
d001fdc0:	469b3406 	ldrmi	r3, [fp], r6, lsl #8
d001fdc4:	46272300 	strtmi	r2, [r7], -r0, lsl #6
d001fdc8:	9b269303 	blls	0xd09c49dc
d001fdcc:	e9cd4619 	stmib	sp, {r0, r3, r4, r9, sl, lr}^
d001fdd0:	23001200 	movwcs	r1, #512	; 0x200
d001fdd4:	0ffa203f 	svceq	0x00fa203f
d001fdd8:	b008f8cd 	andlt	pc, r8, sp, asr #17
d001fddc:	469a4699 			; <UNDEFINED> instruction: 0x469a4699
d001fde0:	99023801 	stmdbls	r2, {r0, fp, ip, sp}
d001fde4:	0420f1c0 	strteq	pc, [r0], #-448	; 0xfffffe40
d001fde8:	0520f1a0 	streq	pc, [r0, #-416]!	; 0xfffffe60
d001fdec:	f1b040c1 			; <UNDEFINED> instruction: 0xf1b040c1
d001fdf0:	fa073fff 	blx	0xd01efdf4
d001fdf4:	fa27fe04 	blx	0xd0a1f60c
d001fdf8:	fa26fc05 	blx	0xd09dee14
d001fdfc:	fa06f404 	blx	0xd01dce14
d001fe00:	ea41f505 	b	0xd109d21c
d001fe04:	fa06010e 	blx	0xd01a0244
d001fe08:	ea44f800 	b	0xd115de10
d001fe0c:	ea410405 	b	0xd1060e28
d001fe10:	d072010c 	rsbsle	r0, r2, ip, lsl #2
d001fe14:	f0011895 			; <UNDEFINED> instruction: 0xf0011895
d001fe18:	eb430101 	bl	0xd10e0224
d001fe1c:	ea410c03 	b	0xd1062e30
d001fe20:	46630205 	strbtmi	r0, [r3], -r5, lsl #4
d001fe24:	bc00e9dd 			; <UNDEFINED> instruction: 0xbc00e9dd
d001fe28:	bf084563 	svclt	0x00084563
d001fe2c:	d3d7455a 	bicsle	r4, r7, #377487360	; 0x16800000
d001fe30:	020bebb2 	andeq	lr, fp, #182272	; 0x2c800
d001fe34:	0909ea48 	stmdbeq	r9, {r3, r6, r9, fp, sp, lr, pc}
d001fe38:	0a0aea44 	beq	0xd02da750
d001fe3c:	030ceb63 	movweq	lr, #52067	; 0xcb63
d001fe40:	2301e7ce 	movwcs	lr, #6094	; 0x17ce
d001fe44:	092df04f 	pusheq	{r0, r1, r2, r3, r6, ip, sp, lr, pc}
d001fe48:	9a2c469a 	bls	0xd0b318b8
d001fe4c:	d18c2a00 	orrle	r2, ip, r0, lsl #20
d001fe50:	f0129a28 			; <UNDEFINED> instruction: 0xf0129a28
d001fe54:	d16a0610 	cmnle	sl, r0, lsl r6
d001fe58:	81d8f8df 	ldrsbhi	pc, [r8, #143]	; 0x8f	; <UNPREDICTABLE>
d001fe5c:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d001fe60:	4291992a 	addsmi	r9, r1, #688128	; 0xa8000
d001fe64:	9903dd95 	stmdbls	r3, {r0, r2, r4, r7, r8, sl, fp, ip, lr, pc}
d001fe68:	198a982a 	stmibne	sl, {r1, r3, r5, fp, ip, pc}
d001fe6c:	44131a47 	ldrmi	r1, [r3], #-2631	; 0xfffff5b9
d001fe70:	443b9a29 	ldrtmi	r9, [fp], #-2601	; 0xfffff5d7
d001fe74:	d87c429a 	ldmdale	ip!, {r1, r3, r4, r7, r9, lr}^
d001fe78:	24009b28 	strcs	r9, [r0], #-2856	; 0xfffff4d8
d001fe7c:	0501f003 	streq	pc, [r1, #-3]
d001fe80:	0f00f1ba 	svceq	0x0000f1ba
d001fe84:	b16ed14d 	cmnlt	lr, sp, asr #2
d001fe88:	1000f898 	mulne	r0, r8, r8
d001fe8c:	0a10ee18 	beq	0xd045b6f4
d001fe90:	ff0ef7ff 			; <UNDEFINED> instruction: 0xff0ef7ff
d001fe94:	d1052e02 	tstle	r5, r2, lsl #28
d001fe98:	1001f898 	mulne	r1, r8, r8
d001fe9c:	0a10ee18 	beq	0xd045b704
d001fea0:	ff06f7ff 			; <UNDEFINED> instruction: 0xff06f7ff
d001fea4:	b1471e7e 	hvclt	29166	; 0x71ee
d001fea8:	7a10ee18 	bvc	0xd045b710
d001feac:	21303e01 	teqcs	r0, r1, lsl #28
d001feb0:	f7ff4638 			; <UNDEFINED> instruction: 0xf7ff4638
d001feb4:	1c72fefd 	ldclne	14, cr15, [r2], #-1012	; 0xfffffc0c
d001feb8:	9b03d1f8 	blls	0xd01146a0
d001febc:	af09b163 	svcge	0x0009b163
d001fec0:	ee189b03 	vnmls.f64	d9, d8, d3
d001fec4:	443b8a10 	ldrtmi	r8, [fp], #-2576	; 0xfffff5f0
d001fec8:	f816461e 			; <UNDEFINED> instruction: 0xf816461e
d001fecc:	46401d01 	strbmi	r1, [r0], -r1, lsl #26
d001fed0:	feeef7ff 	mcr2	7, 7, pc, cr14, cr15, {7}	; <UNPREDICTABLE>
d001fed4:	d1f842b7 	ldrhle	r4, [r8, #39]!	; 0x27
d001fed8:	1e65b155 	mcrne	1, 3, fp, cr5, cr5, {2}
d001fedc:	ee18b144 	mnfem	f3, f4
d001fee0:	3d014a10 	vstrcc	s8, [r1, #-64]	; 0xffffffc0
d001fee4:	46202120 	strtmi	r2, [r0], -r0, lsr #2
d001fee8:	fee2f7ff 	mcr2	7, 7, pc, cr2, cr15, {7}	; <UNPREDICTABLE>
d001feec:	d1f81c6b 	mvnsle	r1, fp, ror #24
d001fef0:	ecbdb01b 	ldc	0, cr11, [sp], #108	; 0x6c
d001fef4:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d001fef8:	99058ff0 	stmdbls	r5, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
d001fefc:	9903440a 	stmdbls	r3, {r1, r3, sl, lr}
d001ff00:	31017813 	tstcc	r1, r3, lsl r8
d001ff04:	91039a04 	tstls	r3, r4, lsl #20
d001ff08:	3b01f802 	blcc	0xd009df18
d001ff0c:	030aea59 	movweq	lr, #43609	; 0xaa59
d001ff10:	f43f9204 			; <UNDEFINED> instruction: 0xf43f9204
d001ff14:	2940af19 	stmdbcs	r0, {r0, r3, r4, r8, r9, sl, fp, sp, pc}^
d001ff18:	af16f63f 	svcge	0x0016f63f
d001ff1c:	465746cb 	ldrbmi	r4, [r7], -fp, asr #13
d001ff20:	4649e757 			; <UNDEFINED> instruction: 0x4649e757
d001ff24:	0a10ee18 	beq	0xd045b78c
d001ff28:	fec2f7ff 	mcr2	7, 6, pc, cr2, cr15, {7}	; <UNPREDICTABLE>
d001ff2c:	e9dde7ab 	ldmib	sp, {r0, r1, r3, r5, r7, r8, r9, sl, sp, lr, pc}^
d001ff30:	430a1206 	movwmi	r1, #41478	; 0xa206
d001ff34:	af19f47f 	svcge	0x0019f47f
d001ff38:	2a089a26 	bcs	0xd02467d8
d001ff3c:	9a03d167 	bls	0xd01144e0
d001ff40:	d1642a00 	cmnle	r4, r0, lsl #20
d001ff44:	21302201 	teqcs	r0, r1, lsl #4
d001ff48:	80ecf8df 	ldrdhi	pc, [ip], #143	; 0x8f	; <UNPREDICTABLE>
d001ff4c:	44f89e2c 	ldrbtmi	r9, [r8], #3628	; 0xe2c
d001ff50:	f88d9203 			; <UNDEFINED> instruction: 0xf88d9203
d001ff54:	e7831024 	str	r1, [r3, r4, lsr #32]
d001ff58:	f04f2301 			; <UNDEFINED> instruction: 0xf04f2301
d001ff5c:	469a092b 	ldrmi	r0, [sl], fp, lsr #18
d001ff60:	9a2be773 	bls	0xd0b19d34
d001ff64:	f8dfb352 			; <UNDEFINED> instruction: 0xf8dfb352
d001ff68:	260280d4 			; <UNDEFINED> instruction: 0x260280d4
d001ff6c:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d001ff70:	9a29e776 	bls	0xd0a99d50
d001ff74:	9b281ad4 	blls	0xd0a26acc
d001ff78:	0303f003 	movweq	pc, #12291	; 0x3003	; <UNPREDICTABLE>
d001ff7c:	d1022b02 	tstle	r2, r2, lsl #22
d001ff80:	2b009b2a 	blcs	0xd0046c30
d001ff84:	9b28db33 	blls	0xd0a56c58
d001ff88:	0501f013 	streq	pc, [r1, #-19]	; 0xffffffed
d001ff8c:	af78f47f 	svcge	0x0078f47f
d001ff90:	3bfff104 	blcc	0xd001c3a8
d001ff94:	d0402c00 	suble	r2, r0, r0, lsl #24
d001ff98:	ee189402 	cfmuls	mvf9, mvf8, mvf2
d001ff9c:	f10b4a10 			; <UNDEFINED> instruction: 0xf10b4a10
d001ffa0:	21203bff 	strdcs	r3, [r0, -pc]!
d001ffa4:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d001ffa8:	f1bbfe83 			; <UNDEFINED> instruction: 0xf1bbfe83
d001ffac:	d1f63fff 	ldrshle	r3, [r6, #255]!	; 0xff
d001ffb0:	f1ba9c02 			; <UNDEFINED> instruction: 0xf1ba9c02
d001ffb4:	f43f0f00 			; <UNDEFINED> instruction: 0xf43f0f00
d001ffb8:	e7b2af66 	ldr	sl, [r2, r6, ror #30]!
d001ffbc:	8080f8df 	ldrdhi	pc, [r0], pc	; <UNPREDICTABLE>
d001ffc0:	9a032602 	bls	0xd00e97d0
d001ffc4:	e74b44f8 			; <UNDEFINED> instruction: 0xe74b44f8
d001ffc8:	a91ab15a 	ldmdbge	sl, {r1, r3, r4, r6, r8, ip, sp, pc}
d001ffcc:	f812188a 			; <UNDEFINED> instruction: 0xf812188a
d001ffd0:	2a302c45 	bcs	0xd0c2b0ec
d001ffd4:	f8dfd105 			; <UNDEFINED> instruction: 0xf8dfd105
d001ffd8:	2600806c 	strcs	r8, [r0], -ip, rrx
d001ffdc:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d001ffe0:	f8dfe73e 			; <UNDEFINED> instruction: 0xf8dfe73e
d001ffe4:	26018064 	strcs	r8, [r1], -r4, rrx
d001ffe8:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d001ffec:	9b28e738 	blls	0xd0a59cd4
d001fff0:	24004427 	strcs	r4, [r0], #-1063	; 0xfffffbd9
d001fff4:	0501f003 	streq	pc, [r1, #-3]
d001fff8:	0f00f1ba 	svceq	0x0000f1ba
d001fffc:	af43f43f 	svcge	0x0043f43f
d0020000:	f8dfe78f 			; <UNDEFINED> instruction: 0xf8dfe78f
d0020004:	46168048 	ldrmi	r8, [r6], -r8, asr #32
d0020008:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d002000c:	f8dfe728 			; <UNDEFINED> instruction: 0xf8dfe728
d0020010:	26008040 	strcs	r8, [r0], -r0, asr #32
d0020014:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d0020018:	4625e722 	strtmi	lr, [r5], -r2, lsr #14
d002001c:	0f00f1ba 	svceq	0x0000f1ba
d0020020:	af31f43f 	svcge	0x0031f43f
d0020024:	bf00e77d 	svclt	0x0000e77d
d0020028:	0000136a 	andeq	r1, r0, sl, ror #6
d002002c:	ffffff6e 			; <UNDEFINED> instruction: 0xffffff6e
d0020030:	000012d8 	ldrdeq	r1, [r0], -r8
d0020034:	fffffe9e 			; <UNDEFINED> instruction: 0xfffffe9e
d0020038:	fffffdae 			; <UNDEFINED> instruction: 0xfffffdae
d002003c:	fffffd8a 			; <UNDEFINED> instruction: 0xfffffd8a
d0020040:	fffffd3c 			; <UNDEFINED> instruction: 0xfffffd3c
d0020044:	fffffd1e 			; <UNDEFINED> instruction: 0xfffffd1e
d0020048:	fffffd1a 			; <UNDEFINED> instruction: 0xfffffd1a
d002004c:	fffffcfe 			; <UNDEFINED> instruction: 0xfffffcfe
d0020050:	fffffce6 			; <UNDEFINED> instruction: 0xfffffce6

Disassembly of section .text.sb_float:

d002006c <.text.sb_float>:
d002006c:	4ff0e92d 	svcmi	0x00f0e92d
d0020070:	bb10ec5c 	bllt	0xd045b1e8
d0020074:	461eb0df 			; <UNDEFINED> instruction: 0x461eb0df
d0020078:	73dcea5f 	bicsvc	lr, ip, #389120	; 0x5f000
d002007c:	460446e0 	strmi	r4, [r4], -r0, ror #13
d0020080:	4615468a 	ldrmi	r4, [r5], -sl, lsl #13
d0020084:	9a10ee10 	bls	0xd045b8cc
d0020088:	ed8d9304 	stc	3, cr9, [sp, #16]
d002008c:	d10a0b00 	tstle	sl, r0, lsl #22
d0020090:	f1000750 			; <UNDEFINED> instruction: 0xf1000750
d0020094:	009380cb 	addseq	r8, r3, fp, asr #1
d0020098:	1740f3c3 	strbne	pc, [r0, -r3, asr #7]	; <UNPREDICTABLE>
d002009c:	0320f003 	wfieq
d00200a0:	930346bb 	movwls	r4, #14011	; 0x36bb
d00200a4:	2701e003 	strcs	lr, [r1, -r3]
d00200a8:	46bb232d 	ldrtmi	r2, [fp], sp, lsr #6
d00200ac:	f04f9303 			; <UNDEFINED> instruction: 0xf04f9303
d00200b0:	21000c00 	tstcs	r0, r0, lsl #24
d00200b4:	70fff240 	rscsvc	pc, pc, r0, asr #4
d00200b8:	520af3c8 	andpl	pc, sl, #200, 6	; 0x20000003
d00200bc:	f1aa458c 			; <UNDEFINED> instruction: 0xf1aa458c
d00200c0:	bf080e41 	svclt	0x00080e41
d00200c4:	fa5f4282 	blx	0xd17f0ad4
d00200c8:	d03efe8e 	eorsle	pc, lr, lr, lsl #29
d00200cc:	2b099b68 	blcs	0xd0286e74
d00200d0:	4afcdd4b 	bmi	0xcff57604
d00200d4:	0918f10d 	ldmdbeq	r8, {r0, r2, r3, r8, ip, sp, lr, pc}
d00200d8:	237046e0 	cmncs	r0, #224, 12	; 0xe000000
d00200dc:	4649447a 			; <UNDEFINED> instruction: 0x4649447a
d00200e0:	3201203c 	andcc	r2, r1, #60	; 0x3c
d00200e4:	4618e002 	ldrmi	lr, [r8], -r2
d00200e8:	3f01f812 	svccc	0x0001f812
d00200ec:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d00200f0:	0b01f801 	bleq	0xd009e0fc
d00200f4:	d1f62b00 	mvnsle	r2, r0, lsl #22
d00200f8:	020beb08 	andeq	lr, fp, #8, 22	; 0x2000
d00200fc:	42b22301 	adcsmi	r2, r2, #67108864	; 0x4000000
d0020100:	8099f0c0 	addshi	pc, r9, r0, asr #1
d0020104:	f0052600 			; <UNDEFINED> instruction: 0xf0052600
d0020108:	2a020203 	bcs	0xd00a091c
d002010c:	2b00d102 	blcs	0xd005451c
d0020110:	8093f040 	addshi	pc, r3, r0, asr #32
d0020114:	0501f015 	streq	pc, [r1, #-21]	; 0xffffffeb
d0020118:	80bcf040 	adcshi	pc, ip, r0, asr #32
d002011c:	b1361e75 	teqlt	r6, r5, ror lr
d0020120:	21203d01 			; <UNDEFINED> instruction: 0x21203d01
d0020124:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0020128:	1c69fdc3 	stclne	13, cr15, [r9], #-780	; 0xfffffcf4
d002012c:	2f00d1f8 	svccs	0x0000d1f8
d0020130:	8091f000 	addshi	pc, r1, r0
d0020134:	46209903 	strtmi	r9, [r0], -r3, lsl #18
d0020138:	fdbaf7ff 	ldc2	7, cr15, [sl, #1020]!	; 0x3fc
d002013c:	0f00f1b8 	svceq	0x0000f1b8
d0020140:	808df040 	addhi	pc, sp, r0, asr #32
d0020144:	e8bdb05f 	pop	{r0, r1, r2, r3, r4, r6, ip, sp, pc}
d0020148:	464a8ff0 			; <UNDEFINED> instruction: 0x464a8ff0
d002014c:	0313f3c8 	tsteq	r3, #200, 6	; 0x20000003	; <UNPREDICTABLE>
d0020150:	f0404313 			; <UNDEFINED> instruction: 0xf0404313
d0020154:	f1be80ae 			; <UNDEFINED> instruction: 0xf1be80ae
d0020158:	f2000f19 	vrecps.f32	d0, d0, d9
d002015c:	f8df80d4 			; <UNDEFINED> instruction: 0xf8df80d4
d0020160:	234ec368 	movtcs	ip, #58216	; 0xe368
d0020164:	44fc2149 	ldrbtmi	r2, [ip], #329	; 0x149
d0020168:	9b04e0ab 	blls	0xd015841c
d002016c:	ed9db12b 	ldfd	f3, [sp, #172]	; 0xac
d0020170:	eeb17b00 	vmov.f64	d7, #16	; 0x40800000  4.0
d0020174:	ed8d7b47 	vstr	d7, [sp, #284]	; 0x11c
d0020178:	f1be7b00 			; <UNDEFINED> instruction: 0xf1be7b00
d002017c:	f00a0f19 			; <UNDEFINED> instruction: 0xf00a0f19
d0020180:	bf8c0adf 	svclt	0x008c0adf
d0020184:	23012300 	movwcs	r2, #4864	; 0x1300
d0020188:	9b689304 	blls	0xd1a44da0
d002018c:	f2c02b00 	vqdmlsl.s<illegal width 8>	q9, d0, d0
d0020190:	f1ba80c5 			; <UNDEFINED> instruction: 0xf1ba80c5
d0020194:	f0400f47 			; <UNDEFINED> instruction: 0xf0400f47
d0020198:	9b6880c7 	blls	0xd1a404bc
d002019c:	bf082b00 	svclt	0x00082b00
d00201a0:	93682301 	cmnls	r8, #67108864	; 0x4000000
d00201a4:	7b00ed9d 	blvc	0xd005b820
d00201a8:	7b40eeb5 	blvc	0xd105bc84
d00201ac:	fa10eef1 	blx	0xd045bd78
d00201b0:	80d0f000 	sbcshi	pc, r0, r0
d00201b4:	6b04eeb2 	blvs	0xd015bc84
d00201b8:	7bc6eeb4 	blvc	0xcf1dbc90
d00201bc:	fa10eef1 	blx	0xd045bd88
d00201c0:	8170f2c0 	cmnhi	r0, r0, asr #5	; <UNPREDICTABLE>
d00201c4:	0a00f04f 	beq	0xd005c308
d00201c8:	f5bae003 			; <UNDEFINED> instruction: 0xf5bae003
d00201cc:	f0007f9a 			; <UNDEFINED> instruction: 0xf0007f9a
d00201d0:	ee87810f 	sins	f0, #10.0
d00201d4:	f10a7b06 			; <UNDEFINED> instruction: 0xf10a7b06
d00201d8:	eeb40a01 	vmov.f32	s0, #65	; 0x3e080000  0.1328125
d00201dc:	eef17bc6 	vsqrt.f64	d23, d6
d00201e0:	daf2fa10 	ble	0xcfcdea28
d00201e4:	6b00eeb7 	blvs	0xd005bcc8
d00201e8:	7bc6eeb4 	blvc	0xcf1dbcc0
d00201ec:	fa10eef1 	blx	0xd045bdb8
d00201f0:	eeb2d511 	mrc	5, 5, sp, cr2, cr1, {0}
d00201f4:	eeb75b04 	vmov.f64	d5, #116	; 0x3fa00000  1.250
d00201f8:	e0036b00 	and	r6, r3, r0, lsl #22
d00201fc:	7fa2f51a 	svcvc	0x00a2f51a
d0020200:	80fef000 	rscshi	pc, lr, r0
d0020204:	7b05ee27 	blvc	0xd019baa8
d0020208:	3afff10a 	bcc	0xd001c638
d002020c:	7bc6eeb4 	blvc	0xcf1dbce4
d0020210:	fa10eef1 	blx	0xd045bddc
d0020214:	9b68d4f2 	blls	0xd1a555e4
d0020218:	f3404553 	vqrshl.u8	q10, <illegal reg q1.5>, q0
d002021c:	f11a80f1 			; <UNDEFINED> instruction: 0xf11a80f1
d0020220:	f2c00f04 			; <UNDEFINED> instruction: 0xf2c00f04
d0020224:	f10a80ed 			; <UNDEFINED> instruction: 0xf10a80ed
d0020228:	e0960101 	adds	r0, r6, r1, lsl #2
d002022c:	232b2701 			; <UNDEFINED> instruction: 0x232b2701
d0020230:	930346bb 	movwls	r4, #14011	; 0x36bb
d0020234:	1ab6e73b 	bne	0xcedd9f28
d0020238:	f005e765 			; <UNDEFINED> instruction: 0xf005e765
d002023c:	2f000501 	svccs	0x00000501
d0020240:	bb8dd167 	bllt	0xce3947e4
d0020244:	b1361e75 	teqlt	r6, r5, ror lr
d0020248:	21303d01 	teqcs	r0, r1, lsl #26
d002024c:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0020250:	1c6afd2f 	stclne	13, cr15, [sl], #-188	; 0xffffff44
d0020254:	f1b8d1f8 			; <UNDEFINED> instruction: 0xf1b8d1f8
d0020258:	f43f0f00 			; <UNDEFINED> instruction: 0xf43f0f00
d002025c:	2500af73 	strcs	sl, [r0, #-3955]	; 0xfffff08d
d0020260:	37012700 	strcc	r2, [r1, -r0, lsl #14]
d0020264:	1b01f819 	blne	0xd009e2d0
d0020268:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d002026c:	4547fd21 	strbmi	pc, [r7, #-3361]	; 0xfffff2df	; <UNPREDICTABLE>
d0020270:	2d00d3f7 	stccs	3, cr13, [r0, #-988]	; 0xfffffc24
d0020274:	af66f43f 	svcge	0x0066f43f
d0020278:	2e001e75 	mcrcs	14, 0, r1, cr0, cr5, {3}
d002027c:	af62f43f 	svcge	0x0062f43f
d0020280:	21203d01 			; <UNDEFINED> instruction: 0x21203d01
d0020284:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0020288:	1c6bfd13 	stclne	13, cr15, [fp], #-76	; 0xffffffb4
d002028c:	b05fd1f8 	ldrshlt	sp, [pc], #-24	; <UNPREDICTABLE>
d0020290:	8ff0e8bd 	svchi	0x00f0e8bd
d0020294:	f1b8b927 			; <UNDEFINED> instruction: 0xf1b8b927
d0020298:	d1e10f00 	mvnle	r0, r0, lsl #30
d002029c:	461ee7ec 	ldrmi	lr, [lr], -ip, ror #15
d00202a0:	46209903 	strtmi	r9, [r0], -r3, lsl #18
d00202a4:	fd04f7ff 	stc2	7, cr15, [r4, #-1020]	; 0xfffffc04
d00202a8:	0f00f1b8 	svceq	0x0000f1b8
d00202ac:	2501d0e4 	strcs	sp, [r1, #-228]	; 0xffffff1c
d00202b0:	f1bee7d6 			; <UNDEFINED> instruction: 0xf1bee7d6
d00202b4:	d9470f19 	stmdble	r7, {r0, r3, r4, r8, r9, sl, fp}^
d00202b8:	c210f8df 	andsgt	pc, r0, #14614528	; 0xdf0000
d00202bc:	216e2361 	cmncs	lr, r1, ror #6
d00202c0:	f10d44fc 			; <UNDEFINED> instruction: 0xf10d44fc
d00202c4:	f10c0918 			; <UNDEFINED> instruction: 0xf10c0918
d00202c8:	ea6f0202 	b	0xd1be0ad8
d00202cc:	46480c0c 	strbmi	r0, [r8], -ip, lsl #24
d00202d0:	f812e001 			; <UNDEFINED> instruction: 0xf812e001
d00202d4:	f8003b01 			; <UNDEFINED> instruction: 0xf8003b01
d00202d8:	eb0c1b01 	bl	0xd0326ee4
d00202dc:	46190802 	ldrmi	r0, [r9], -r2, lsl #16
d00202e0:	d1f62b00 	mvnsle	r2, r0, lsl #22
d00202e4:	020beb08 	andeq	lr, fp, #8, 22	; 0x2000
d00202e8:	d8a44296 	stmiale	r4!, {r1, r2, r4, r7, r9, lr}
d00202ec:	0601f015 			; <UNDEFINED> instruction: 0x0601f015
d00202f0:	af1df43f 	svcge	0x001df43f
d00202f4:	d1d22f00 	bicsle	r2, r2, r0, lsl #30
d00202f8:	0f00f1b8 	svceq	0x0000f1b8
d00202fc:	af22f43f 	svcge	0x0022f43f
d0020300:	463e4635 			; <UNDEFINED> instruction: 0x463e4635
d0020304:	f8dfe7ac 			; <UNDEFINED> instruction: 0xf8dfe7ac
d0020308:	236ec1c8 	cmncs	lr, #200, 2	; 0x32
d002030c:	44fc2169 	ldrbtmi	r2, [ip], #361	; 0x169
d0020310:	9903e7d7 	stmdbls	r3, {r0, r1, r2, r4, r6, r7, r8, r9, sl, sp, lr, pc}
d0020314:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0020318:	e792fccb 	ldr	pc, [r2, fp, asr #25]
d002031c:	f1ba2306 			; <UNDEFINED> instruction: 0xf1ba2306
d0020320:	93680f47 	cmnls	r8, #284	; 0x11c
d0020324:	af3ef43f 	svcge	0x003ef43f
d0020328:	0f45f1ba 	svceq	0x0045f1ba
d002032c:	0918f10d 	ldmdbeq	r8, {r0, r2, r3, r8, ip, sp, lr, pc}
d0020330:	9b04d154 	blls	0xd0154888
d0020334:	0210f005 	andseq	pc, r0, #5
d0020338:	46489968 	strbmi	r9, [r8], -r8, ror #18
d002033c:	0b00ed9d 	bleq	0xd005b9b8
d0020340:	fbb6f7ff 	blx	0xcedde346
d0020344:	e6d74680 	ldrb	r4, [r7], r0, lsl #13
d0020348:	c188f8df 	ldrdgt	pc, [r8, pc]
d002034c:	214e2341 	cmpcs	lr, r1, asr #6
d0020350:	e7b644fc 			; <UNDEFINED> instruction: 0xe7b644fc
d0020354:	f04f2101 			; <UNDEFINED> instruction: 0xf04f2101
d0020358:	9b680a00 	blls	0xd1a22b60
d002035c:	0918f10d 	ldmdbeq	r8, {r0, r2, r3, r8, ip, sp, lr, pc}
d0020360:	0210f005 	andseq	pc, r0, #5
d0020364:	46481a59 			; <UNDEFINED> instruction: 0x46481a59
d0020368:	ed9d9205 	lfm	f1, 1, [sp, #20]
d002036c:	f7ff0b00 			; <UNDEFINED> instruction: 0xf7ff0b00
d0020370:	4680fad7 	pkhtbmi	pc, r0, r7, asr #21	; <UNPREDICTABLE>
d0020374:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0020378:	4649aebf 			; <UNDEFINED> instruction: 0x4649aebf
d002037c:	9a052300 	bls	0xd0168f84
d0020380:	3301e003 	movwcc	lr, #4099	; 0x1003
d0020384:	f0004598 			; <UNDEFINED> instruction: 0xf0004598
d0020388:	f8118086 			; <UNDEFINED> instruction: 0xf8118086
d002038c:	282e0b01 	stmdacs	lr!, {r0, r8, r9, fp}
d0020390:	f1bad1f7 			; <UNDEFINED> instruction: 0xf1bad1f7
d0020394:	db020f00 	blle	0xd00a3f9c
d0020398:	42999968 	addsmi	r9, r9, #104, 18	; 0x1a0000
d002039c:	2a00d334 	bcs	0xd0055074
d00203a0:	aeaaf47f 	mcrge	4, 5, pc, cr10, cr15, {3}	; <UNPREDICTABLE>
d00203a4:	e002464b 	and	r4, r2, fp, asr #12
d00203a8:	f43f4590 			; <UNDEFINED> instruction: 0xf43f4590
d00203ac:	f813aea5 			; <UNDEFINED> instruction: 0xf813aea5
d00203b0:	32011b01 	andcc	r1, r1, #1024	; 0x400
d00203b4:	d1f7292e 	mvnsle	r2, lr, lsr #18
d00203b8:	0308eb09 	movweq	lr, #35593	; 0x8b09
d00203bc:	f813e005 			; <UNDEFINED> instruction: 0xf813e005
d00203c0:	29301d01 	ldmdbcs	r0!, {r0, r8, sl, fp, ip}
d00203c4:	ae98f47f 	mrcge	4, 4, APSR_nzcv, cr8, cr15, {3}
d00203c8:	45904680 	ldrmi	r4, [r0, #1664]	; 0x680
d00203cc:	30fff108 	rscscc	pc, pc, r8, lsl #2
d00203d0:	f47fd8f5 			; <UNDEFINED> instruction: 0xf47fd8f5
d00203d4:	f108ae91 			; <UNDEFINED> instruction: 0xf108ae91
d00203d8:	e68d38ff 			; <UNDEFINED> instruction: 0xe68d38ff
d00203dc:	0b00ed9d 	bleq	0xd005ba58
d00203e0:	f0059968 			; <UNDEFINED> instruction: 0xf0059968
d00203e4:	46480210 			; <UNDEFINED> instruction: 0x46480210
d00203e8:	fa9af7ff 	blx	0xce6de3ec
d00203ec:	e6834680 	str	r4, [r3], r0, lsl #13
d00203f0:	6b00eeb7 	blvs	0xd005bed4
d00203f4:	7bc6eeb4 	blvc	0xcf1dbecc
d00203f8:	fa10eef1 	blx	0xd045bfc4
d00203fc:	aef9f53f 	mrcge	5, 7, APSR_nzcv, cr9, cr15, {1}
d0020400:	0210f005 	andseq	pc, r0, #5
d0020404:	0918f10d 	ldmdbeq	r8, {r0, r2, r3, r8, ip, sp, lr, pc}
d0020408:	46489968 	strbmi	r9, [r8], -r8, ror #18
d002040c:	39019b04 	stmdbcc	r1, {r2, r8, r9, fp, ip, pc}
d0020410:	ed9d9204 	lfm	f1, 1, [sp, #16]
d0020414:	f7ff0b00 			; <UNDEFINED> instruction: 0xf7ff0b00
d0020418:	9a04fb4b 	bls	0xd015f14c
d002041c:	2a004680 	bcs	0xd0031e24
d0020420:	ae6af47f 	mcrge	4, 3, pc, cr10, cr15, {3}	; <UNPREDICTABLE>
d0020424:	46424448 	strbmi	r4, [r2], -r8, asr #8
d0020428:	461ae000 	ldrmi	lr, [sl], -r0
d002042c:	2a001e53 	bcs	0xd0027d80
d0020430:	ae62f43f 	mcrge	4, 3, pc, cr2, cr15, {1}	; <UNPREDICTABLE>
d0020434:	1d01f810 	stcne	8, cr15, [r1, #-64]	; 0xffffffc0
d0020438:	0cdff001 	ldcleq	0, cr15, [pc], {1}
d002043c:	0f45f1bc 	svceq	0x0045f1bc
d0020440:	eb09d1f3 	bl	0xd0294c14
d0020444:	46180c03 	ldrmi	r0, [r8], -r3, lsl #24
d0020448:	f81ce005 			; <UNDEFINED> instruction: 0xf81ce005
d002044c:	f1baad01 			; <UNDEFINED> instruction: 0xf1baad01
d0020450:	d1220f30 			; <UNDEFINED> instruction: 0xd1220f30
d0020454:	f1004670 			; <UNDEFINED> instruction: 0xf1004670
d0020458:	28003eff 	stmdacs	r0, {r0, r1, r2, r3, r4, r5, r6, r7, r9, sl, fp, ip, sp}
d002045c:	4543d1f5 	strbmi	sp, [r3, #-501]	; 0xfffffe0b
d0020460:	f1c2d212 			; <UNDEFINED> instruction: 0xf1c2d212
d0020464:	eb090a01 	bl	0xd0262c70
d0020468:	f10d0c03 			; <UNDEFINED> instruction: 0xf10d0c03
d002046c:	44820e17 	strmi	r0, [r2], #3607	; 0xe17
d0020470:	445344c6 	ldrbmi	r4, [r3], #-1222	; 0xfffffb3a
d0020474:	3b0144d6 	blcc	0xd00717d4
d0020478:	e001444b 	and	r4, r1, fp, asr #8
d002047c:	1f01f81c 	svcne	0x0001f81c
d0020480:	1f01f803 	svcne	0x0001f803
d0020484:	d1f94573 	mvnsle	r4, r3, ror r5
d0020488:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d002048c:	0202eba8 	andeq	lr, r2, #168, 22	; 0x2a000
d0020490:	0802eb00 	stmdaeq	r2, {r8, r9, fp, sp, lr, pc}
d0020494:	4643e630 			; <UNDEFINED> instruction: 0x4643e630
d0020498:	f1bae77b 			; <UNDEFINED> instruction: 0xf1bae77b
d002049c:	bf080f2e 	svclt	0x00080f2e
d00204a0:	e7dc4670 			; <UNDEFINED> instruction: 0xe7dc4670
d00204a4:	7b00eeb7 	blvc	0xd005bf88
d00204a8:	6b00ed9d 	blvs	0xd005bb24
d00204ac:	6bc7eeb4 	blvs	0xcf21bf84
d00204b0:	fa10eef1 	blx	0xd045c07c
d00204b4:	af4ef57f 	svcge	0x004ef57f
d00204b8:	0a00f04f 	beq	0xd005c5fc
d00204bc:	7b00ed9d 	blvc	0xd005bb38
d00204c0:	bf00e697 	svclt	0x0000e697
d00204c4:	ffffff84 			; <UNDEFINED> instruction: 0xffffff84
d00204c8:	fffffeee 			; <UNDEFINED> instruction: 0xfffffeee
d00204cc:	fffffd90 			; <UNDEFINED> instruction: 0xfffffd90
d00204d0:	fffffd4e 			; <UNDEFINED> instruction: 0xfffffd4e
d00204d4:	fffffd08 			; <UNDEFINED> instruction: 0xfffffd08

Disassembly of section .text.sb_format.part.0:

d0020508 <.text.sb_format.part.0>:
d0020508:	4ff0e92d 	svcmi	0x00f0e92d
d002050c:	78094688 	stmdavc	r9, {r3, r7, r9, sl, lr}
d0020510:	4683b0a7 	strmi	fp, [r3], r7, lsr #1
d0020514:	f0002900 			; <UNDEFINED> instruction: 0xf0002900
d0020518:	4bfa80b3 	blmi	0xcfec07ec
d002051c:	f8df4691 			; <UNDEFINED> instruction: 0xf8df4691
d0020520:	447ba3e8 	ldrbtmi	sl, [fp], #-1000	; 0xfffffc18
d0020524:	4bf99308 	blmi	0xcfe8514c
d0020528:	9309447b 	movwls	r4, #38011	; 0x947b
d002052c:	f0402925 			; <UNDEFINED> instruction: 0xf0402925
d0020530:	f89880fd 			; <UNDEFINED> instruction: 0xf89880fd
d0020534:	2c254001 	stccs	0, cr4, [r5], #-4
d0020538:	80fef000 	rscshi	pc, lr, r0
d002053c:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d0020540:	f1a42600 			; <UNDEFINED> instruction: 0xf1a42600
d0020544:	2b100320 	blcs	0xd04211cc
d0020548:	e8dfd80a 	ldm	pc, {r1, r3, fp, ip, lr, pc}^	; <UNPREDICTABLE>
d002054c:	0978f003 	ldmdbeq	r8!, {r0, r1, ip, sp, lr, pc}^
d0020550:	09097509 	stmdbeq	r9, {r0, r3, r8, sl, ip, sp, lr}
d0020554:	09090909 	stmdbeq	r9, {r0, r3, r8, fp}
d0020558:	6f097209 	svcvs	0x00097209
d002055c:	006a0909 	rsbeq	r0, sl, r9, lsl #18
d0020560:	f0402c2a 			; <UNDEFINED> instruction: 0xf0402c2a
d0020564:	f8d980ef 			; <UNDEFINED> instruction: 0xf8d980ef
d0020568:	f1083000 			; <UNDEFINED> instruction: 0xf1083000
d002056c:	681d0101 	ldmdavs	sp, {r0, r8}
d0020570:	2d001d1a 	stccs	13, cr1, [r0, #-104]	; 0xffffff98
d0020574:	2000f8c9 	andcs	pc, r0, r9, asr #17
d0020578:	8122f2c0 	smlawthi	r2, r0, r2, pc	; <UNPREDICTABLE>
d002057c:	5f00f5b5 	svcpl	0x0000f5b5
d0020580:	4001f898 	mulmi	r1, r8, r8
d0020584:	f44fbf28 			; <UNDEFINED> instruction: 0xf44fbf28
d0020588:	2c2e5500 	cfstr32cs	mvfx5, [lr], #-0
d002058c:	80fbf000 	rscshi	pc, fp, r0
d0020590:	37fff04f 	ldrbcc	pc, [pc, pc, asr #32]!	; <UNPREDICTABLE>
d0020594:	f0002c68 			; <UNDEFINED> instruction: 0xf0002c68
d0020598:	2c6c810d 	stfcsp	f0, [ip], #-52	; 0xffffffcc
d002059c:	811ef000 	tsthi	lr, r0	; <UNPREDICTABLE>
d00205a0:	f0002c7a 			; <UNDEFINED> instruction: 0xf0002c7a
d00205a4:	2c748122 	ldfcsp	f0, [r4], #-136	; 0xffffff78
d00205a8:	8161f000 	msrhi	SPSR_c, r0
d00205ac:	f0002c6a 			; <UNDEFINED> instruction: 0xf0002c6a
d00205b0:	230081b3 	movwcs	r8, #435	; 0x1b3
d00205b4:	d0632c00 	rsble	r2, r3, r0, lsl #24
d00205b8:	f1012c64 			; <UNDEFINED> instruction: 0xf1012c64
d00205bc:	d07d0801 	rsbsle	r0, sp, r1, lsl #16
d00205c0:	d07b2c69 	rsbsle	r2, fp, r9, ror #24
d00205c4:	0262f1a4 	rsbeq	pc, r2, #164, 2	; 0x29
d00205c8:	01dff004 	bicseq	pc, pc, r4
d00205cc:	f1a1b2d2 			; <UNDEFINED> instruction: 0xf1a1b2d2
d00205d0:	2a130c58 	bcs	0xd04e3738
d00205d4:	fc8cfabc 	stc2	10, cr15, [ip], {188}	; 0xbc	; <UNPREDICTABLE>
d00205d8:	1c5cea4f 	mrrcne	10, 4, lr, ip, cr15
d00205dc:	48c8d806 	stmiami	r8, {r1, r2, fp, ip, lr, pc}^
d00205e0:	f202fa20 	vpmax.s8	d15, d2, d16
d00205e4:	0201f002 	andeq	pc, r1, #2
d00205e8:	0c02ea4c 			; <UNDEFINED> instruction: 0x0c02ea4c
d00205ec:	0f00f1bc 	svceq	0x0000f1bc
d00205f0:	816cf000 	msrhi	SPSR_fs, r0
d00205f4:	f0002c6f 			; <UNDEFINED> instruction: 0xf0002c6f
d00205f8:	2958811b 	ldmdbcs	r8, {r0, r1, r3, r4, r8, pc}^
d00205fc:	811af000 	tsthi	sl, r0	; <UNPREDICTABLE>
d0020600:	bf0c2c62 	svclt	0x000c2c62
d0020604:	210a2102 	tstcs	sl, r2, lsl #2
d0020608:	2b063b01 	blcs	0xd01af214
d002060c:	84fdf200 	ldrbthi	pc, [sp], #512	; 0x200	; <UNPREDICTABLE>
d0020610:	f013e8df 			; <UNDEFINED> instruction: 0xf013e8df
d0020614:	0143014b 	cmpeq	r3, fp, asr #2
d0020618:	00480018 	subeq	r0, r8, r8, lsl r0
d002061c:	00180018 	andseq	r0, r8, r8, lsl r0
d0020620:	f0460048 			; <UNDEFINED> instruction: 0xf0460048
d0020624:	f8180602 			; <UNDEFINED> instruction: 0xf8180602
d0020628:	e78a4f01 	str	r4, [sl, r1, lsl #30]
d002062c:	0601f046 	streq	pc, [r1], -r6, asr #32
d0020630:	f046e7f9 			; <UNDEFINED> instruction: 0xf046e7f9
d0020634:	e7f60604 	ldrb	r0, [r6, r4, lsl #12]!
d0020638:	0610f046 	ldreq	pc, [r0], -r6, asr #32
d002063c:	f046e7f3 			; <UNDEFINED> instruction: 0xf046e7f3
d0020640:	e7f00608 	ldrb	r0, [r0, r8, lsl #12]!
d0020644:	3000f8d9 	ldrdcc	pc, [r0], -r9
d0020648:	681a1d18 	ldmdavs	sl, {r3, r4, r8, sl, fp, ip}
d002064c:	f8c92300 			; <UNDEFINED> instruction: 0xf8c92300
d0020650:	f1a40000 			; <UNDEFINED> instruction: 0xf1a40000
d0020654:	f0260058 			; <UNDEFINED> instruction: 0xf0260058
d0020658:	2400060c 	strcs	r0, [r0], #-1548	; 0xfffff9f4
d002065c:	fab09704 	blx	0xcec46274
d0020660:	9602f080 	strls	pc, [r2], -r0, lsl #1
d0020664:	09409503 	stmdbeq	r0, {r0, r1, r8, sl, ip, pc}^
d0020668:	94069100 	strls	r9, [r6], #-256	; 0xffffff00
d002066c:	46589005 	ldrbmi	r9, [r8], -r5
d0020670:	f7ff9401 			; <UNDEFINED> instruction: 0xf7ff9401
d0020674:	f898fb4d 			; <UNDEFINED> instruction: 0xf898fb4d
d0020678:	29001000 	stmdbcs	r0, {ip}
d002067c:	af56f47f 	svcge	0x0056f47f
d0020680:	300cf8db 	ldrdcc	pc, [ip], -fp
d0020684:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d0020688:	465880db 			; <UNDEFINED> instruction: 0x465880db
d002068c:	fafcf7ff 	blx	0xcff5e690
d0020690:	300cf8db 	ldrdcc	pc, [ip], -fp
d0020694:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d0020698:	f8db80d3 			; <UNDEFINED> instruction: 0xf8db80d3
d002069c:	b0270008 	eorlt	r0, r7, r8
d00206a0:	8ff0e8bd 	svchi	0x00f0e8bd
d00206a4:	3000f8d9 	ldrdcc	pc, [r0], -r9
d00206a8:	f0233307 			; <UNDEFINED> instruction: 0xf0233307
d00206ac:	f1030307 			; <UNDEFINED> instruction: 0xf1030307
d00206b0:	f8c90208 			; <UNDEFINED> instruction: 0xf8c90208
d00206b4:	e9d32000 	ldmib	r3, {sp}^
d00206b8:	e7ca2300 	strb	r2, [sl, r0, lsl #6]
d00206bc:	2b063b01 	blcs	0xd01af2c8
d00206c0:	84acf200 	strthi	pc, [ip], #512	; 0x200
d00206c4:	f003e8df 			; <UNDEFINED> instruction: 0xf003e8df
d00206c8:	1f04d7e0 	svcne	0x0004d7e0
d00206cc:	001f0404 	andseq	r0, pc, r4, lsl #8
d00206d0:	3000f8d9 	ldrdcc	pc, [r0], -r9
d00206d4:	1d1a6818 	ldcne	8, cr6, [sl, #-96]	; 0xffffffa0
d00206d8:	f8c917c1 			; <UNDEFINED> instruction: 0xf8c917c1
d00206dc:	28002000 	stmdacs	r0, {sp}
d00206e0:	0300f171 	movweq	pc, #369	; 0x171	; <UNPREDICTABLE>
d00206e4:	4602db1e 			; <UNDEFINED> instruction: 0x4602db1e
d00206e8:	0fc8460b 	svceq	0x00c8460b
d00206ec:	2100240a 	tstcs	r0, sl, lsl #8
d00206f0:	90019704 	andls	r9, r1, r4, lsl #14
d00206f4:	95034658 	strls	r4, [r3, #-1624]	; 0xfffff9a8
d00206f8:	91069602 	tstls	r6, r2, lsl #12
d00206fc:	94009105 	strls	r9, [r0], #-261	; 0xfffffefb
d0020700:	fb06f7ff 	blx	0xd01de706
d0020704:	f8d9e7b7 			; <UNDEFINED> instruction: 0xf8d9e7b7
d0020708:	33073000 	movwcc	r3, #28672	; 0x7000
d002070c:	0307f023 	movweq	pc, #28707	; 0x7023	; <UNPREDICTABLE>
d0020710:	0100e9d3 	ldrdeq	lr, [r0, -r3]
d0020714:	0208f103 	andeq	pc, r8, #-1073741824	; 0xc0000000
d0020718:	f8c92800 			; <UNDEFINED> instruction: 0xf8c92800
d002071c:	f1712000 			; <UNDEFINED> instruction: 0xf1712000
d0020720:	dae00300 	ble	0xcf821328
d0020724:	eb614242 	bl	0xd1871034
d0020728:	e7de0341 	ldrb	r0, [lr, r1, asr #6]
d002072c:	f1084658 			; <UNDEFINED> instruction: 0xf1084658
d0020730:	f7ff0801 			; <UNDEFINED> instruction: 0xf7ff0801
d0020734:	e79efabd 			; <UNDEFINED> instruction: 0xe79efabd
d0020738:	f1084658 			; <UNDEFINED> instruction: 0xf1084658
d002073c:	f7ff0802 			; <UNDEFINED> instruction: 0xf7ff0802
d0020740:	e798fab7 			; <UNDEFINED> instruction: 0xe798fab7
d0020744:	0230f1a4 	eorseq	pc, r0, #164, 2	; 0x29
d0020748:	2b09b2d3 	blcs	0xd028d29c
d002074c:	80e8f200 	rschi	pc, r8, r0, lsl #4
d0020750:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d0020754:	f5c22500 			; <UNDEFINED> instruction: 0xf5c22500
d0020758:	46415300 	strbmi	r5, [r1], -r0, lsl #6
d002075c:	0085eb05 	addeq	lr, r5, r5, lsl #22
d0020760:	4303fbaa 	movwmi	pc, #15274	; 0x3baa	; <UNPREDICTABLE>
d0020764:	4b01f818 	blmi	0xd009e7cc
d0020768:	0fd3ebb5 	svceq	0x00d3ebb5
d002076c:	0540eb02 	strbeq	lr, [r0, #-2818]	; 0xfffff4fe
d0020770:	0230f1a4 	eorseq	pc, r0, #164, 2	; 0x29
d0020774:	f44fbf88 			; <UNDEFINED> instruction: 0xf44fbf88
d0020778:	b2d35500 	sbcslt	r5, r3, #0, 10
d002077c:	d9ea2b09 	stmible	sl!, {r0, r3, r8, r9, fp, sp}^
d0020780:	f47f2c2e 			; <UNDEFINED> instruction: 0xf47f2c2e
d0020784:	784caf05 	stmdavc	ip, {r0, r2, r8, r9, sl, fp, sp, pc}^
d0020788:	d1322c2a 	teqle	r2, sl, lsr #24
d002078c:	3000f8d9 	ldrdcc	pc, [r0], -r9
d0020790:	681f1c88 	ldmdavs	pc, {r3, r7, sl, fp, ip}	; <UNPREDICTABLE>
d0020794:	2f001d1a 	svccs	0x00001d1a
d0020798:	2000f8c9 	andcs	pc, r0, r9, asr #17
d002079c:	f2c0788c 	vmlal.s8	<illegal reg q11.5>, d16, d12
d00207a0:	f5b78091 			; <UNDEFINED> instruction: 0xf5b78091
d00207a4:	46015f00 	strmi	r5, [r1], -r0, lsl #30
d00207a8:	f44fbf28 			; <UNDEFINED> instruction: 0xf44fbf28
d00207ac:	2c685700 	stclcs	7, cr5, [r8], #-0
d00207b0:	aef3f47f 	mrcge	4, 7, APSR_nzcv, cr3, cr15, {3}
d00207b4:	2c68784c 	stclcs	8, cr7, [r8], #-304	; 0xfffffed0
d00207b8:	3101d03e 	tstcc	r1, lr, lsr r0
d00207bc:	e6f92302 	ldrbt	r2, [r9], r2, lsl #6
d00207c0:	4f00f1b5 	svcmi	0x0000f1b5
d00207c4:	0601f046 	streq	pc, [r1], -r6, asr #32
d00207c8:	426dd077 	rsbmi	sp, sp, #119	; 0x77
d00207cc:	4001f898 	mulmi	r1, r8, r8
d00207d0:	5f00f5b5 	svcpl	0x0000f5b5
d00207d4:	f44fbf28 			; <UNDEFINED> instruction: 0xf44fbf28
d00207d8:	e6d65500 	ldrb	r5, [r6], r0, lsl #10
d00207dc:	2c6c784c 	stclcs	8, cr7, [ip], #-304	; 0xfffffed0
d00207e0:	8096f000 	addshi	pc, r6, r0
d00207e4:	23033101 	movwcs	r3, #12545	; 0x3101
d00207e8:	784ce6e4 	stmdavc	ip, {r2, r5, r6, r7, r9, sl, sp, lr, pc}^
d00207ec:	31012305 	tstcc	r1, r5, lsl #6
d00207f0:	f1a4e6e0 			; <UNDEFINED> instruction: 0xf1a4e6e0
d00207f4:	1c480230 	sfmne	f0, 2, [r8], {48}	; 0x30
d00207f8:	2b09b2d3 	blcs	0xd028d34c
d00207fc:	80daf200 	sbcshi	pc, sl, r0, lsl #4
d0020800:	27001c88 	strcs	r1, [r0, -r8, lsl #25]
d0020804:	5300f5c2 	movwpl	pc, #1474	; 0x5c2	; <UNPREDICTABLE>
d0020808:	0487eb07 	streq	lr, [r7], #2823	; 0xb07
d002080c:	fbaa4601 	blx	0xceab201a
d0020810:	ebb7c303 	bl	0xcee11424
d0020814:	eb020fd3 	bl	0xd00a4768
d0020818:	f8100744 			; <UNDEFINED> instruction: 0xf8100744
d002081c:	bf884b01 	svclt	0x00884b01
d0020820:	5700f44f 	strpl	pc, [r0, -pc, asr #8]
d0020824:	0230f1a4 	eorseq	pc, r0, #164, 2	; 0x29
d0020828:	2b09b2d3 	blcs	0xd028d37c
d002082c:	e6b1d9ea 	ldrt	sp, [r1], sl, ror #19
d0020830:	e6e92108 	strbt	r2, [r9], r8, lsl #2
d0020834:	e6e72110 	usat	r2, #7, r0, lsl #2
d0020838:	2301788c 	movwcs	r7, #6284	; 0x188c
d002083c:	e6b93102 	ldrt	r3, [r9], r2, lsl #2
d0020840:	3000f8db 	ldrdcc	pc, [r0], -fp
d0020844:	f43f2b00 			; <UNDEFINED> instruction: 0xf43f2b00
d0020848:	f8dbaf28 			; <UNDEFINED> instruction: 0xf8dbaf28
d002084c:	2a002004 	bcs	0xd0028864
d0020850:	af23f43f 	svcge	0x0023f43f
d0020854:	1008f8db 	ldrdne	pc, [r8], -fp
d0020858:	bf98428a 	svclt	0x0098428a
d002085c:	31fff102 	mvnscc	pc, r2, lsl #2
d0020860:	545a2200 	ldrbpl	r2, [sl], #-512	; 0xfffffe00
d0020864:	0008f8db 	ldrdeq	pc, [r8], -fp
d0020868:	e8bdb027 	pop	{r0, r1, r2, r5, ip, sp, pc}
d002086c:	784c8ff0 	stmdavc	ip, {r4, r5, r6, r7, r8, r9, sl, fp, pc}^
d0020870:	31012306 	tstcc	r1, r6, lsl #6
d0020874:	f8d9e69e 			; <UNDEFINED> instruction: 0xf8d9e69e
d0020878:	f9b33000 			; <UNDEFINED> instruction: 0xf9b33000
d002087c:	1d1a0000 	ldcne	0, cr0, [sl, #-0]
d0020880:	f8c917c1 			; <UNDEFINED> instruction: 0xf8c917c1
d0020884:	e72a2000 	str	r2, [sl, -r0]!
d0020888:	3000f8d9 	ldrdcc	pc, [r0], -r9
d002088c:	0000f993 	muleq	r0, r3, r9
d0020890:	17c11d1a 	bfine	r1, sl, (invalid: 26:1)
d0020894:	2000f8c9 	andcs	pc, r0, r9, asr #17
d0020898:	f8d9e721 			; <UNDEFINED> instruction: 0xf8d9e721
d002089c:	1d183000 	ldcne	0, cr3, [r8, #-0]
d00208a0:	2300881a 	movwcs	r8, #2074	; 0x81a
d00208a4:	0000f8c9 	andeq	pc, r0, r9, asr #17
d00208a8:	f8d9e6d3 			; <UNDEFINED> instruction: 0xf8d9e6d3
d00208ac:	1d183000 	ldcne	0, cr3, [r8, #-0]
d00208b0:	2300781a 	movwcs	r7, #2074	; 0x81a
d00208b4:	0000f8c9 	andeq	pc, r0, r9, asr #17
d00208b8:	f898e6cb 			; <UNDEFINED> instruction: 0xf898e6cb
d00208bc:	f44f4001 	vst4.8	{d20-d23}, [pc], r1
d00208c0:	e6625500 	strbt	r5, [r2], -r0, lsl #10
d00208c4:	37fff04f 	ldrbcc	pc, [pc, pc, asr #32]!	; <UNPREDICTABLE>
d00208c8:	e6634601 	strbt	r4, [r3], -r1, lsl #12
d00208cc:	d0592c70 	subsle	r2, r9, r0, ror ip
d00208d0:	d0722c73 	rsbsle	r2, r2, r3, ror ip
d00208d4:	d0262c63 	eorle	r2, r6, r3, ror #24
d00208d8:	0245f1a1 	subeq	pc, r5, #1073741864	; 0x40000028
d00208dc:	d93f2a02 	ldmdble	pc!, {r1, r9, fp, sp}	; <UNPREDICTABLE>
d00208e0:	f0002941 			; <UNDEFINED> instruction: 0xf0002941
d00208e4:	2c6e80af 	stclcs	0, cr8, [lr], #-700	; 0xfffffd44
d00208e8:	8216f000 	andshi	pc, r6, #0
d00208ec:	21254658 			; <UNDEFINED> instruction: 0x21254658
d00208f0:	f9def7ff 			; <UNDEFINED> instruction: 0xf9def7ff
d00208f4:	46584621 	ldrbmi	r4, [r8], -r1, lsr #12
d00208f8:	f9daf7ff 			; <UNDEFINED> instruction: 0xf9daf7ff
d00208fc:	bf00e6bb 	svclt	0x0000e6bb
d0020900:	00082001 	andeq	r2, r8, r1
d0020904:	ffffffce 			; <UNDEFINED> instruction: 0xffffffce
d0020908:	cccccccd 	stclgt	12, cr12, [ip], {205}	; 0xcd
d002090c:	ffffffb4 			; <UNDEFINED> instruction: 0xffffffb4
d0020910:	2304788c 	movwcs	r7, #18572	; 0x488c
d0020914:	e64d3102 	strb	r3, [sp], -r2, lsl #2
d0020918:	2307784c 	movwcs	r7, #30796	; 0x784c
d002091c:	e6493101 	strb	r3, [r9], -r1, lsl #2
d0020920:	25004641 	strcs	r4, [r0, #-1601]	; 0xfffff9bf
d0020924:	2d01e631 	stccs	6, cr14, [r1, #-196]	; 0xffffff3c
d0020928:	2501bf38 	strcs	fp, [r1, #-3896]	; 0xfffff0c8
d002092c:	f10507f6 			; <UNDEFINED> instruction: 0xf10507f6
d0020930:	f14037ff 			; <UNDEFINED> instruction: 0xf14037ff
d0020934:	f8d9818b 			; <UNDEFINED> instruction: 0xf8d9818b
d0020938:	46583000 	ldrbmi	r3, [r8], -r0
d002093c:	1d1a3d02 	ldcne	13, cr3, [sl, #-8]
d0020940:	f8c97819 			; <UNDEFINED> instruction: 0xf8c97819
d0020944:	f7ff2000 			; <UNDEFINED> instruction: 0xf7ff2000
d0020948:	2f00f9b3 	svccs	0x0000f9b3
d002094c:	ae93f43f 	mrcge	4, 4, APSR_nzcv, cr3, cr15, {1}
d0020950:	46583d01 	ldrbmi	r3, [r8], -r1, lsl #26
d0020954:	f7ff2120 			; <UNDEFINED> instruction: 0xf7ff2120
d0020958:	1c68f9ab 			; <UNDEFINED> instruction: 0x1c68f9ab
d002095c:	e68ad1f8 			; <UNDEFINED> instruction: 0xe68ad1f8
d0020960:	0000f8d9 	ldrdeq	pc, [r0], -r9
d0020964:	462b4621 	strtmi	r4, [fp], -r1, lsr #12
d0020968:	1dc44632 	stclne	6, cr4, [r4, #200]	; 0xc8
d002096c:	f0244658 			; <UNDEFINED> instruction: 0xf0244658
d0020970:	ed940407 	cfldrs	mvf0, [r4, #28]
d0020974:	34080b00 	strcc	r0, [r8], #-2816	; 0xfffff500
d0020978:	f8c99700 			; <UNDEFINED> instruction: 0xf8c99700
d002097c:	f7ff4000 			; <UNDEFINED> instruction: 0xf7ff4000
d0020980:	e678fb75 			; <UNDEFINED> instruction: 0xe678fb75
d0020984:	3000f8d9 	ldrdcc	pc, [r0], -r9
d0020988:	060cf026 	streq	pc, [ip], -r6, lsr #32
d002098c:	21102401 	tstcs	r0, r1, lsl #8
d0020990:	46581d1a 			; <UNDEFINED> instruction: 0x46581d1a
d0020994:	2000f8c9 	andcs	pc, r0, r9, asr #17
d0020998:	4663681a 			; <UNDEFINED> instruction: 0x4663681a
d002099c:	f8cd9602 			; <UNDEFINED> instruction: 0xf8cd9602
d00209a0:	9704c014 	smladls	r4, r4, r0, ip
d00209a4:	f8cd9503 			; <UNDEFINED> instruction: 0xf8cd9503
d00209a8:	9406c004 	strls	ip, [r6], #-4
d00209ac:	f7ff9100 			; <UNDEFINED> instruction: 0xf7ff9100
d00209b0:	e660f9af 	strbt	pc, [r0], -pc, lsr #19	; <UNPREDICTABLE>
d00209b4:	27004601 	strcs	r4, [r0, -r1, lsl #12]
d00209b8:	f8d9e5ec 			; <UNDEFINED> instruction: 0xf8d9e5ec
d00209bc:	1d1a3000 	ldcne	0, cr3, [sl, #-0]
d00209c0:	2000f8c9 	andcs	pc, r0, r9, asr #17
d00209c4:	9314681b 	tstls	r4, #1769472	; 0x1b0000
d00209c8:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d00209cc:	781b813b 	ldmdavc	fp, {r0, r1, r3, r4, r5, r8, pc}
d00209d0:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d00209d4:	0ff88197 	svceq	0x00f88197
d00209d8:	f0002f00 			; <UNDEFINED> instruction: 0xf0002f00
d00209dc:	9a148193 	bls	0xd0541030
d00209e0:	f8122400 			; <UNDEFINED> instruction: 0xf8122400
d00209e4:	34013f01 	strcc	r3, [r1], #-3841	; 0xfffff0ff
d00209e8:	42bcb11b 	adcsmi	fp, ip, #-1073741818	; 0xc0000006
d00209ec:	2800d3f9 	stmdacs	r0, {r0, r3, r4, r5, r6, r7, r8, r9, ip, lr, pc}
d00209f0:	42a5d1f7 	adcmi	sp, r5, #-1073741763	; 0xc000003d
d00209f4:	813df200 	teqhi	sp, r0, lsl #4	; <UNPREDICTABLE>
d00209f8:	0301f016 	movweq	pc, #4118	; 0x1016	; <UNPREDICTABLE>
d00209fc:	f0009312 			; <UNDEFINED> instruction: 0xf0009312
d0020a00:	25008189 	strcs	r8, [r0, #-393]	; 0xfffffe77
d0020a04:	95149b14 	ldrls	r9, [r4, #-2836]	; 0xfffff4ec
d0020a08:	1e5e4625 	cdpne	6, 5, cr4, cr14, cr5, {1}
d0020a0c:	4637461c 			; <UNDEFINED> instruction: 0x4637461c
d0020a10:	f8164658 			; <UNDEFINED> instruction: 0xf8164658
d0020a14:	f7ff1f01 			; <UNDEFINED> instruction: 0xf7ff1f01
d0020a18:	1cbbf94b 			; <UNDEFINED> instruction: 0x1cbbf94b
d0020a1c:	429d1b1b 	addsmi	r1, sp, #27648	; 0x6c00
d0020a20:	9b12d8f5 	blls	0xd04d6dfc
d0020a24:	2b009d14 	blcs	0xd0047e7c
d0020a28:	ae25f43f 	mcrge	4, 1, pc, cr5, cr15, {1}	; <UNPREDICTABLE>
d0020a2c:	2d001e6c 	stccs	14, cr1, [r0, #-432]	; 0xfffffe50
d0020a30:	ae21f43f 	mcrge	4, 1, pc, cr1, cr15, {1}	; <UNPREDICTABLE>
d0020a34:	21203c01 			; <UNDEFINED> instruction: 0x21203c01
d0020a38:	f7ff4658 			; <UNDEFINED> instruction: 0xf7ff4658
d0020a3c:	1c67f939 			; <UNDEFINED> instruction: 0x1c67f939
d0020a40:	e618d1f8 			; <UNDEFINED> instruction: 0xe618d1f8
d0020a44:	3000f8d9 	ldrdcc	pc, [r0], -r9
d0020a48:	f0233307 			; <UNDEFINED> instruction: 0xf0233307
d0020a4c:	ed930307 	ldc	3, cr0, [r3, #28]
d0020a50:	33087b00 	movwcc	r7, #35584	; 0x8b00
d0020a54:	0b17ec51 	bleq	0xd061bba0
d0020a58:	3000f8c9 	andcc	pc, r0, r9, asr #17
d0020a5c:	ee17460b 	cfmsub32	mvax0, mvfx4, mvfx7, mvfx11
d0020a60:	2b002a10 	blcs	0xd002b2a8
d0020a64:	7b12ed8d 	blvc	0xd04dc0a0
d0020a68:	8176f2c0 	cmnhi	r6, r0, asr #5	; <UNPREDICTABLE>
d0020a6c:	f1000771 			; <UNDEFINED> instruction: 0xf1000771
d0020a70:	00b18176 	adcseq	r8, r1, r6, ror r1
d0020a74:	0120f001 	msreq	CPSR_, r1
d0020a78:	f3c39114 	vorr.i32	d25, #180	; 0x000000b4
d0020a7c:	920c510a 	andls	r5, ip, #-2147483646	; 0x80000002
d0020a80:	72fff240 	rscsvc	pc, pc, #64, 4
d0020a84:	0313f3c3 	tsteq	r3, #201326595	; 0xc000003	; <UNPREDICTABLE>
d0020a88:	42919116 	addsmi	r9, r1, #-2147483643	; 0x80000005
d0020a8c:	f000930d 			; <UNDEFINED> instruction: 0xf000930d
d0020a90:	9b16817c 	blls	0xd05c1088
d0020a94:	bf142b00 	svclt	0x00142b00
d0020a98:	22002201 	andcs	r2, r0, #268435456	; 0x10000000
d0020a9c:	f0009217 			; <UNDEFINED> instruction: 0xf0009217
d0020aa0:	f2a38161 	vmla.f32	d8, d3, d1[1]
d0020aa4:	2b0033ff 	blcs	0xd002daa8
d0020aa8:	bfb8931a 	svclt	0x00b8931a
d0020aac:	9312425b 	tstls	r2, #-1342177275	; 0xb0000005
d0020ab0:	f0001c78 			; <UNDEFINED> instruction: 0xf0001c78
d0020ab4:	f5b7818a 			; <UNDEFINED> instruction: 0xf5b7818a
d0020ab8:	f3405f00 	vpmax.f32	d21, d0, d0
d0020abc:	f44f817d 	vst4.16	{d24,d26,d28,d30}, [pc :256]!
d0020ac0:	e9dd5700 	ldmib	sp, {r8, r9, sl, ip, lr}^
d0020ac4:	9715230c 	ldrls	r2, [r5, -ip, lsl #6]
d0020ac8:	230ae9cd 	movwcs	lr, #43469	; 0xa9cd
d0020acc:	2100ab22 	tstcs	r0, r2, lsr #22
d0020ad0:	ee079a12 			; <UNDEFINED> instruction: 0xee079a12
d0020ad4:	4618ba90 			; <UNDEFINED> instruction: 0x4618ba90
d0020ad8:	fbaa9321 	blx	0xceac5766
d0020adc:	4694c302 	ldrmi	ip, [r4], r2, lsl #6
d0020ae0:	3101468e 	smlabbcc	r1, lr, r6, r4
d0020ae4:	0bd3ea4f 	bleq	0xcf51b428
d0020ae8:	0f09f1bc 	svceq	0x0009f1bc
d0020aec:	038beb0b 	orreq	lr, fp, #11264	; 0x2c00
d0020af0:	0343eba2 	movteq	lr, #15266	; 0x3ba2
d0020af4:	f103465a 			; <UNDEFINED> instruction: 0xf103465a
d0020af8:	b2db0330 	sbcslt	r0, fp, #48, 6	; 0xc0000000
d0020afc:	3b01f800 	blcc	0xd009eb04
d0020b00:	ee17d8eb 	cdp	8, 1, cr13, cr7, cr11, {7}
d0020b04:	931fba90 	tstls	pc, #144, 20	; 0x90000
d0020b08:	e080f8cd 	add	pc, r0, sp, asr #17
d0020b0c:	f0002f00 			; <UNDEFINED> instruction: 0xf0002f00
d0020b10:	f00681bd 			; <UNDEFINED> instruction: 0xf00681bd
d0020b14:	22040310 	andcs	r0, r4, #16, 6	; 0x40000000
d0020b18:	9b14931b 	blls	0xd054578c
d0020b1c:	3b009815 	blcc	0xd0046b78
d0020b20:	2301bf18 	movwcs	fp, #7960	; 0x1f18
d0020b24:	44033302 	strmi	r3, [r3], #-770	; 0xfffffcfe
d0020b28:	4413440b 	ldrmi	r4, [r3], #-1035	; 0xfffffbf5
d0020b2c:	f240429d 	vqsub.s8	d20, d16, d13
d0020b30:	f00681b9 			; <UNDEFINED> instruction: 0xf00681b9
d0020b34:	f0060101 			; <UNDEFINED> instruction: 0xf0060101
d0020b38:	1aea0003 	bne	0xcfaa0b4c
d0020b3c:	0301f081 	movweq	pc, #4225	; 0x1081	; <UNPREDICTABLE>
d0020b40:	901e9116 	andsls	r9, lr, r6, lsl r1
d0020b44:	bf0c2802 	svclt	0x000c2802
d0020b48:	f0032600 			; <UNDEFINED> instruction: 0xf0032600
d0020b4c:	92120601 	andsls	r0, r2, #1048576	; 0x100000
d0020b50:	f0002e00 			; <UNDEFINED> instruction: 0xf0002e00
d0020b54:	1e5581a5 	lognedp	f0, f5
d0020b58:	f0002a00 			; <UNDEFINED> instruction: 0xf0002a00
d0020b5c:	3d0181b0 	stfccd	f0, [r1, #-704]	; 0xfffffd40
d0020b60:	46582120 	ldrbmi	r2, [r8], -r0, lsr #2
d0020b64:	f8a4f7ff 			; <UNDEFINED> instruction: 0xf8a4f7ff
d0020b68:	d1f81c69 	mvnsle	r1, r9, ror #24
d0020b6c:	93162300 	tstls	r6, #0, 6
d0020b70:	2b009b14 	blcs	0xd00477c8
d0020b74:	8185f040 	orrhi	pc, r5, r0, asr #32
d0020b78:	46582130 			; <UNDEFINED> instruction: 0x46582130
d0020b7c:	f898f7ff 			; <UNDEFINED> instruction: 0xf898f7ff
d0020b80:	46582c41 	ldrbmi	r2, [r8], -r1, asr #24
d0020b84:	2158bf0c 	cmpcs	r8, ip, lsl #30
d0020b88:	f7ff2178 			; <UNDEFINED> instruction: 0xf7ff2178
d0020b8c:	9b1ef891 	blls	0xd07dedd8
d0020b90:	d1022b02 	tstle	r2, r2, lsl #22
d0020b94:	f0402e00 			; <UNDEFINED> instruction: 0xf0402e00
d0020b98:	99178195 	ldmdbls	r7, {r0, r2, r4, r7, r8, pc}
d0020b9c:	31304658 	teqcc	r0, r8, asr r6
d0020ba0:	f7ffb2c9 			; <UNDEFINED> instruction: 0xf7ffb2c9
d0020ba4:	9b15f885 	blls	0xd059edc0
d0020ba8:	43139a1b 	tstmi	r3, #110592	; 0x1b000
d0020bac:	212ed003 			; <UNDEFINED> instruction: 0x212ed003
d0020bb0:	f7ff4658 			; <UNDEFINED> instruction: 0xf7ff4658
d0020bb4:	2c41f87d 	mcrrcs	8, 7, pc, r1, cr13	; <UNPREDICTABLE>
d0020bb8:	816ff000 	msrhi	SPSR_fsxc, r0
d0020bbc:	f0002f00 			; <UNDEFINED> instruction: 0xf0002f00
d0020bc0:	9e08821f 	mcrls	2, 0, r8, cr8, cr15, {0}
d0020bc4:	250000bb 	strcs	r0, [r0, #-187]	; 0xffffff45
d0020bc8:	3b049415 	blcc	0xd0145c24
d0020bcc:	e0069314 	and	r9, r6, r4, lsl r3
d0020bd0:	78193501 	ldmdavc	r9, {r0, r8, sl, ip, sp}
d0020bd4:	f7ff4658 			; <UNDEFINED> instruction: 0xf7ff4658
d0020bd8:	42aff86b 	adcmi	pc, pc, #7012352	; 0x6b0000
d0020bdc:	2d0cd064 	stccs	0, cr13, [ip, #-400]	; 0xfffffe70
d0020be0:	dcf54633 	ldclle	6, cr4, [r5], #204	; 0xcc
d0020be4:	7185ebc5 	orrvc	lr, r5, r5, asr #23
d0020be8:	9c0a9b14 			; <UNDEFINED> instruction: 0x9c0a9b14
d0020bec:	460a2f0c 	strmi	r2, [sl], -ip, lsl #30
d0020bf0:	0181ea4f 	orreq	lr, r1, pc, asr #20
d0020bf4:	0282eb03 	addeq	lr, r2, #3072	; 0xc00
d0020bf8:	0330f101 	teqeq	r0, #1073741824	; 0x40000000	; <UNPREDICTABLE>
d0020bfc:	0110f101 	tsteq	r0, r1, lsl #2	; <UNPREDICTABLE>
d0020c00:	0020f1c2 	eoreq	pc, r0, r2, asr #3
d0020c04:	0c20f1a2 	stfeqd	f7, [r0], #-648	; 0xfffffd78
d0020c08:	f202fa24 	vpmax.s8	d15, d2, d20
d0020c0c:	f1c39c0b 			; <UNDEFINED> instruction: 0xf1c39c0b
d0020c10:	fa040e20 	blx	0xd0124498
d0020c14:	9c0cf000 	stcls	0, cr15, [ip], {-0}
d0020c18:	f303fa24 	vpmax.u8	d15, d3, d20
d0020c1c:	ea429c0d 	b	0xd10c7c58
d0020c20:	980d0200 	stmdals	sp, {r9}
d0020c24:	fe0efa04 	vseleq.f32	s30, s28, s8
d0020c28:	fa209c0b 	blx	0xd0847c5c
d0020c2c:	fa24f101 	blx	0xd095d038
d0020c30:	ea43fc0c 	b	0xd111fc68
d0020c34:	dc32030e 	ldcle	3, cr0, [r2], #-56	; 0xffffffc8
d0020c38:	020cea42 	andeq	lr, ip, #270336	; 0x42000
d0020c3c:	030ff002 	movweq	pc, #61442	; 0xf002	; <UNPREDICTABLE>
d0020c40:	e7c54433 			; <UNDEFINED> instruction: 0xe7c54433
d0020c44:	447b4bfb 	ldrbtmi	r4, [fp], #-3067	; 0xfffff405
d0020c48:	e6c49314 			; <UNDEFINED> instruction: 0xe6c49314
d0020c4c:	b1373d02 	teqlt	r7, r2, lsl #26
d0020c50:	21203d01 			; <UNDEFINED> instruction: 0x21203d01
d0020c54:	f7ff4658 			; <UNDEFINED> instruction: 0xf7ff4658
d0020c58:	1c6cf82b 	stclne	8, cr15, [ip], #-172	; 0xffffff54
d0020c5c:	f8d9d1f8 			; <UNDEFINED> instruction: 0xf8d9d1f8
d0020c60:	46583000 	ldrbmi	r3, [r8], -r0
d0020c64:	78191d1a 	ldmdavc	r9, {r1, r3, r4, r8, sl, fp, ip}
d0020c68:	2000f8c9 	andcs	pc, r0, r9, asr #17
d0020c6c:	f820f7ff 			; <UNDEFINED> instruction: 0xf820f7ff
d0020c70:	f016e501 			; <UNDEFINED> instruction: 0xf016e501
d0020c74:	eba50301 	bl	0xce961880
d0020c78:	93120504 	tstls	r2, #4, 10	; 0x1000000
d0020c7c:	aec2f47f 	mcrge	4, 6, pc, cr2, cr15, {3}	; <UNPREDICTABLE>
d0020c80:	b1351e6e 	teqlt	r5, lr, ror #28
d0020c84:	21203e01 			; <UNDEFINED> instruction: 0x21203e01
d0020c88:	f7ff4658 			; <UNDEFINED> instruction: 0xf7ff4658
d0020c8c:	1c73f811 	ldclne	8, cr15, [r3], #-68	; 0xffffffbc
d0020c90:	2c00d1f8 	stfcsd	f5, [r0], {248}	; 0xf8
d0020c94:	aceff43f 	cfstrdge	mvd15, [pc], #252	; 0xd0020d98
d0020c98:	93122300 	tstls	r2, #0, 6
d0020c9c:	430be6b2 	movwmi	lr, #46770	; 0xb6b2
d0020ca0:	030ff003 	movweq	pc, #61443	; 0xf003	; <UNPREDICTABLE>
d0020ca4:	e7934433 			; <UNDEFINED> instruction: 0xe7934433
d0020ca8:	2c419c15 	mcrrcs	12, 1, r9, r1, cr5
d0020cac:	2150bf0c 	cmpcs	r0, ip, lsl #30
d0020cb0:	46582170 			; <UNDEFINED> instruction: 0x46582170
d0020cb4:	fffcf7fe 			; <UNDEFINED> instruction: 0xfffcf7fe
d0020cb8:	9d219b1a 	vstmdbls	r1!, {d9-d21}
d0020cbc:	2b004658 	blcs	0xd0032624
d0020cc0:	461c9b20 	ldrmi	r9, [ip], -r0, lsr #22
d0020cc4:	212dbfb4 			; <UNDEFINED> instruction: 0x212dbfb4
d0020cc8:	f7fe212b 			; <UNDEFINED> instruction: 0xf7fe212b
d0020ccc:	442cfff1 	strtmi	pc, [ip], #-4081	; 0xfffff00f
d0020cd0:	e001991f 	and	r9, r1, pc, lsl r9
d0020cd4:	1d01f814 	stcne	8, cr15, [r1, #-80]	; 0xffffffb0
d0020cd8:	f7fe4658 			; <UNDEFINED> instruction: 0xf7fe4658
d0020cdc:	42a5ffe9 	adcmi	pc, r5, #932	; 0x3a4
d0020ce0:	9b16d1f8 	blls	0xd05d54c8
d0020ce4:	f43f2b00 			; <UNDEFINED> instruction: 0xf43f2b00
d0020ce8:	9b12acc6 	blls	0xd04cc008
d0020cec:	2b001e5c 	blcs	0xd0028664
d0020cf0:	acc1f43f 	cfstrdge	mvd15, [r1], {63}	; 0x3f
d0020cf4:	21203c01 			; <UNDEFINED> instruction: 0x21203c01
d0020cf8:	f7fe4658 			; <UNDEFINED> instruction: 0xf7fe4658
d0020cfc:	1c63ffd9 	stclne	15, cr15, [r3], #-868	; 0xfffffc9c
d0020d00:	e4b8d1f8 	ldrt	sp, [r8], #504	; 0x1f8
d0020d04:	f43f2d00 			; <UNDEFINED> instruction: 0xf43f2d00
d0020d08:	07f2acb6 			; <UNDEFINED> instruction: 0x07f2acb6
d0020d0c:	817af140 	cmnhi	sl, r0, asr #2	; <UNPREDICTABLE>
d0020d10:	e68f1e6c 	str	r1, [pc], ip, ror #28
d0020d14:	e7bc9d12 			; <UNDEFINED> instruction: 0xe7bc9d12
d0020d18:	f8db3b01 			; <UNDEFINED> instruction: 0xf8db3b01
d0020d1c:	2b062008 	blcs	0xd01a8d44
d0020d20:	e8dfd812 	ldm	pc, {r1, r4, fp, ip, lr, pc}^	; <UNPREDICTABLE>
d0020d24:	014bf013 	cmpeq	fp, r3, lsl r0	; <UNPREDICTABLE>
d0020d28:	00110142 	andseq	r0, r1, r2, asr #2
d0020d2c:	00110007 	andseq	r0, r1, r7
d0020d30:	00070011 	andeq	r0, r7, r1, lsl r0
d0020d34:	3000f8d9 	ldrdcc	pc, [r0], -r9
d0020d38:	1d182100 	ldfnes	f2, [r8, #-0]
d0020d3c:	0000f8c9 	andeq	pc, r0, r9, asr #17
d0020d40:	e9c3681b 	stmib	r3, {r0, r1, r3, r4, fp, sp, lr}^
d0020d44:	e4962100 	ldr	r2, [r6], #256	; 0x100
d0020d48:	3000f8d9 	ldrdcc	pc, [r0], -r9
d0020d4c:	f8c91d19 			; <UNDEFINED> instruction: 0xf8c91d19
d0020d50:	681b1000 	ldmdavs	fp, {ip}
d0020d54:	e48e601a 	str	r6, [lr], #26
d0020d58:	9114212d 	tstls	r4, sp, lsr #2
d0020d5c:	212be68d 	smlawbcs	fp, sp, r6, lr
d0020d60:	e68a9114 	pkhbt	r9, sl, r4, lsl #2
d0020d64:	010ce9dd 	ldrdeq	lr, [ip, -sp]
d0020d68:	32fef240 	rscscc	pc, lr, #64, 4
d0020d6c:	0301ea50 	movweq	lr, #6736	; 0x1a50
d0020d70:	48af9916 	stmiami	pc!, {r1, r2, r4, r8, fp, ip, pc}	; <UNPREDICTABLE>
d0020d74:	460bbf0c 	strmi	fp, [fp], -ip, lsl #30
d0020d78:	93124613 	tstls	r2, #19922944	; 0x1300000
d0020d7c:	230ce9dd 	movwcs	lr, #51677	; 0xc9dd
d0020d80:	460bbf0c 	strmi	fp, [fp], -ip, lsl #30
d0020d84:	931a4603 	tstls	sl, #3145728	; 0x300000
d0020d88:	2c41e692 	mcrrcs	6, 9, lr, r1, cr2
d0020d8c:	4632462b 	ldrtmi	r4, [r2], -fp, lsr #12
d0020d90:	bf0c4658 	svclt	0x000c4658
d0020d94:	21662146 	cmncs	r6, r6, asr #2
d0020d98:	ed9d9700 	ldc	7, cr9, [sp]
d0020d9c:	f7ff0b12 			; <UNDEFINED> instruction: 0xf7ff0b12
d0020da0:	e468f965 	strbt	pc, [r8], #-2405	; 0xfffff69b	; <UNPREDICTABLE>
d0020da4:	463b4631 			; <UNDEFINED> instruction: 0x463b4631
d0020da8:	f8cd462c 			; <UNDEFINED> instruction: 0xf8cd462c
d0020dac:	9e158048 	cdpls	0, 1, cr8, cr5, cr8, {2}
d0020db0:	461746c8 	ldrmi	r4, [r7], -r8, asr #13
d0020db4:	460d4699 			; <UNDEFINED> instruction: 0x460d4699
d0020db8:	f3402f0c 	vpmax.f32	d18, d0, d12
d0020dbc:	97158090 			; <UNDEFINED> instruction: 0x97158090
d0020dc0:	230ce9dd 	movwcs	lr, #51677	; 0xc9dd
d0020dc4:	230ae9cd 	movwcs	lr, #43469	; 0xa9cd
d0020dc8:	270de680 	strcs	lr, [sp, -r0, lsl #13]
d0020dcc:	46494628 	strbmi	r4, [r9], -r8, lsr #12
d0020dd0:	46c12300 	strbmi	r2, [r1], r0, lsl #6
d0020dd4:	9615463a 			; <UNDEFINED> instruction: 0x9615463a
d0020dd8:	4625469e 			; <UNDEFINED> instruction: 0x4625469e
d0020ddc:	8048f8dd 	ldrdhi	pc, [r8], #-141	; 0xffffff73
d0020de0:	4606460f 	strmi	r4, [r6], -pc, lsl #12
d0020de4:	0c20f1c3 	stfeqd	f7, [r0], #-780	; 0xfffffcf4
d0020de8:	990c980d 	stmdbls	ip, {r0, r2, r3, fp, ip, pc}
d0020dec:	0420f1a3 	strteq	pc, [r0], #-419	; 0xfffffe5d
d0020df0:	fc0cfa00 	stc2	10, cr15, [ip], {-0}	; <UNPREDICTABLE>
d0020df4:	40e040d9 	ldrdmi	r4, [r0], #9	; <UNPREDICTABLE>
d0020df8:	ea413304 	b	0xd106da10
d0020dfc:	4301010c 	movwmi	r0, #4364	; 0x110c
d0020e00:	010ff001 	tsteq	pc, r1	; <UNPREDICTABLE>
d0020e04:	1e0ae9cd 	vmlsne.f16	s28, s21, s26	; <UNPREDICTABLE>
d0020e08:	010ae9dd 	ldrdeq	lr, [sl, -sp]
d0020e0c:	d1c94301 	bicle	r4, r9, r1, lsl #6
d0020e10:	d1e73a01 	mvnle	r3, r1, lsl #20
d0020e14:	f8cd463b 			; <UNDEFINED> instruction: 0xf8cd463b
d0020e18:	46178048 	ldrmi	r8, [r7], -r8, asr #32
d0020e1c:	469946c8 	ldrmi	r4, [r9], r8, asr #13
d0020e20:	462c4631 			; <UNDEFINED> instruction: 0x462c4631
d0020e24:	460d9e15 			; <UNDEFINED> instruction: 0x460d9e15
d0020e28:	e9dd9715 	ldmib	sp, {r0, r2, r4, r8, r9, sl, ip, pc}^
d0020e2c:	e9cd230c 	stmib	sp, {r2, r3, r8, r9, sp}^
d0020e30:	22012318 	andcs	r2, r1, #24, 6	; 0x60000000
d0020e34:	e9cd2300 	stmib	sp, {r8, r9, sp}^
d0020e38:	22002310 	andcs	r2, r0, #16, 6	; 0x40000000
d0020e3c:	2300f44f 	movwcs	pc, #1103	; 0x44f	; <UNPREDICTABLE>
d0020e40:	230ee9cd 	movwcs	lr, #59853	; 0xe9cd
d0020e44:	230ee9dd 	movwcs	lr, #59869	; 0xe9dd
d0020e48:	0118e9dd 			; <UNDEFINED> instruction: 0x0118e9dd
d0020e4c:	bf08428b 	svclt	0x0008428b
d0020e50:	f0c04282 			; <UNDEFINED> instruction: 0xf0c04282
d0020e54:	429980c1 	addsmi	r8, r9, #193	; 0xc1
d0020e58:	4290bf08 	addsmi	fp, r0, #8, 30
d0020e5c:	80b7f000 	adcshi	pc, r7, r0
d0020e60:	230ae9dd 	movwcs	lr, #43485	; 0xa9dd
d0020e64:	0110e9dd 			; <UNDEFINED> instruction: 0x0110e9dd
d0020e68:	bf08428b 	svclt	0x0008428b
d0020e6c:	f47f4282 			; <UNDEFINED> instruction: 0xf47f4282
d0020e70:	9b17ae2d 	blls	0xd060c72c
d0020e74:	33012200 	movwcc	r2, #4608	; 0x1200
d0020e78:	23009317 	movwcs	r9, #791	; 0x317
d0020e7c:	230ae9cd 	movwcs	lr, #43469	; 0xa9cd
d0020e80:	4619e624 	ldrmi	lr, [r9], -r4, lsr #12
d0020e84:	f7fe4658 			; <UNDEFINED> instruction: 0xf7fe4658
d0020e88:	e675ff13 	uhadd16	pc, r5, r3	; <UNPREDICTABLE>
d0020e8c:	0310f016 	tsteq	r0, #22	; <UNPREDICTABLE>
d0020e90:	2204bf14 	andcs	fp, r4, #20, 30	; 0x50
d0020e94:	931b2203 	tstls	fp, #805306368	; 0x30000000
d0020e98:	b177e63f 	cmnlt	r7, pc, lsr r6
d0020e9c:	e6919e09 	ldr	r9, [r1], r9, lsl #28
d0020ea0:	e665461e 			; <UNDEFINED> instruction: 0xe665461e
d0020ea4:	0203f006 	andeq	pc, r3, #6
d0020ea8:	0301f006 	movweq	pc, #4102	; 0x1006	; <UNPREDICTABLE>
d0020eac:	2200921e 	andcs	r9, r0, #-536870911	; 0xe0000001
d0020eb0:	0601f083 	streq	pc, [r1], -r3, lsl #1
d0020eb4:	92129316 	andsls	r9, r2, #1476395008	; 0x58000000
d0020eb8:	2150e65a 	cmpcs	r0, sl, asr r6
d0020ebc:	9b12e6f9 	blls	0xd04daaa8
d0020ec0:	e6559316 			; <UNDEFINED> instruction: 0xe6559316
d0020ec4:	1e5d9b12 	vmovne.s8	r9, d13[0]
d0020ec8:	f43f2b00 			; <UNDEFINED> instruction: 0xf43f2b00
d0020ecc:	3d01ae66 	stccc	14, cr10, [r1, #-408]	; 0xfffffe68
d0020ed0:	46582130 			; <UNDEFINED> instruction: 0x46582130
d0020ed4:	feecf7fe 	mcr2	7, 7, pc, cr12, cr14, {7}	; <UNPREDICTABLE>
d0020ed8:	d1f81c6a 	mvnsle	r1, sl, ror #24
d0020edc:	f1c7e65d 			; <UNDEFINED> instruction: 0xf1c7e65d
d0020ee0:	e9dd030d 	ldmib	sp, {r0, r2, r3, r8, r9}^
d0020ee4:	009b120c 	addseq	r1, fp, ip, lsl #4
d0020ee8:	f1c34618 			; <UNDEFINED> instruction: 0xf1c34618
d0020eec:	f1a30c20 			; <UNDEFINED> instruction: 0xf1a30c20
d0020ef0:	460b0e20 	strmi	r0, [fp], -r0, lsr #28
d0020ef4:	fc0cfa02 	stc2	10, cr15, [ip], {2}	; <UNPREDICTABLE>
d0020ef8:	32fff04f 	rscscc	pc, pc, #79	; 0x4f
d0020efc:	f1a040c3 			; <UNDEFINED> instruction: 0xf1a040c3
d0020f00:	930a0120 	movwls	r0, #41248	; 0xa120
d0020f04:	33fff04f 	mvnscc	pc, #79	; 0x4f
d0020f08:	fe0efa03 	vseleq.f32	s30, s28, s6
d0020f0c:	f300fa02 	vpmax.u8	d15, d0, d2
d0020f10:	ea429a0a 	b	0xd10c7740
d0020f14:	f1c0020c 			; <UNDEFINED> instruction: 0xf1c0020c
d0020f18:	920a0c20 	andls	r0, sl, #32, 24	; 0x2000
d0020f1c:	fa229a0d 	blx	0xd08c7758
d0020f20:	ea43f101 	b	0xd111d32c
d0020f24:	f04f020e 			; <UNDEFINED> instruction: 0xf04f020e
d0020f28:	fa2333ff 	blx	0xd08edf2c
d0020f2c:	4603fc0c 	strmi	pc, [r3], -ip, lsl #24
d0020f30:	30fff04f 	rscscc	pc, pc, pc, asr #32
d0020f34:	0e21f1a3 	abseqdp	f7, f3
d0020f38:	40989315 	addsmi	r9, r8, r5, lsl r3
d0020f3c:	ea429b0a 	b	0xd10c7b6c
d0020f40:	430b020c 	movwmi	r0, #45580	; 0xb20c
d0020f44:	921b2101 	andsls	r2, fp, #1073741824	; 0x40000000
d0020f48:	9b0c930a 	blls	0xd0345b78
d0020f4c:	ea239a15 	b	0xd09077a8
d0020f50:	00b80300 	adcseq	r0, r8, r0, lsl #6
d0020f54:	0c21f1c2 	stfeqd	f7, [r1], #-776	; 0xfffffcf8
d0020f58:	93189715 	tstls	r8, #5505024	; 0x540000
d0020f5c:	f30efa01 	vpmax.u8	d15, d14, d1
d0020f60:	0e20f1a0 	abseqdp	f7, f0
d0020f64:	fc0cfa21 	stc2	10, cr15, [ip], {33}	; 0x21	; <UNPREDICTABLE>
d0020f68:	9b0d930f 	blls	0xd0385bac
d0020f6c:	930b40d3 	movwls	r4, #45267	; 0xb0d3
d0020f70:	f30efa01 	vpmax.u8	d15, d14, d1
d0020f74:	0e20f1c0 	abseqdm	f7, f0
d0020f78:	9b0f9311 	blls	0xd0405bc4
d0020f7c:	fe0efa21 	vseleq.f32	s30, s28, s3
d0020f80:	030cea43 	movweq	lr, #51779	; 0xca43
d0020f84:	3cfff102 	ldfccp	f7, [pc], #8	; 0xd0020f94
d0020f88:	930f9a1b 	movwls	r9, #64027	; 0xfa1b
d0020f8c:	ea239b0d 	b	0xd0907bc8
d0020f90:	fa010202 	blx	0xd00617a0
d0020f94:	930ef30c 	movwls	pc, #58124	; 0xe30c	; <UNPREDICTABLE>
d0020f98:	92199b11 	andsls	r9, r9, #17408	; 0x4400
d0020f9c:	030eea43 	movweq	lr, #59971	; 0xea43
d0020fa0:	fa019311 	blx	0xd0085bec
d0020fa4:	9310f300 	tstls	r0, #0, 6	; <UNPREDICTABLE>
d0020fa8:	f8d9e74c 			; <UNDEFINED> instruction: 0xf8d9e74c
d0020fac:	1d193000 	ldcne	0, cr3, [r9, #-0]
d0020fb0:	1000f8c9 	andne	pc, r0, r9, asr #17
d0020fb4:	801a681b 	andshi	r6, sl, fp, lsl r8
d0020fb8:	bb5df7ff 	bllt	0xd179efbc
d0020fbc:	3000f8d9 	ldrdcc	pc, [r0], -r9
d0020fc0:	f8c91d19 			; <UNDEFINED> instruction: 0xf8c91d19
d0020fc4:	681b1000 	ldmdavs	fp, {ip}
d0020fc8:	f7ff701a 			; <UNDEFINED> instruction: 0xf7ff701a
d0020fcc:	b95fbb54 	ldmdblt	pc, {r2, r4, r6, r8, r9, fp, ip, sp, pc}^	; <UNPREDICTABLE>
d0020fd0:	2b009b16 	blcs	0xd0047c30
d0020fd4:	af44f43f 	svcge	0x0044f43f
d0020fd8:	33019b0a 	movwcc	r9, #6922	; 0x1b0a
d0020fdc:	9b0b930a 	blls	0xd0305c0c
d0020fe0:	0300f143 	movweq	pc, #323	; 0x143	; <UNPREDICTABLE>
d0020fe4:	e73b930b 	ldr	r9, [fp, -fp, lsl #6]!
d0020fe8:	f0039b0a 			; <UNDEFINED> instruction: 0xf0039b0a
d0020fec:	931c0301 	tstls	ip, #67108864	; 0x4000000
d0020ff0:	931d2300 	tstls	sp, #0, 6
d0020ff4:	231ce9dd 	tstcs	ip, #3620864	; 0x374000
d0020ff8:	f43f4313 			; <UNDEFINED> instruction: 0xf43f4313
d0020ffc:	e7ebaf31 			; <UNDEFINED> instruction: 0xe7ebaf31
d0021000:	e6562170 			; <UNDEFINED> instruction: 0xe6562170
d0021004:	24001e6e 	strcs	r1, [r0], #-3694	; 0xfffff192
d0021008:	f8d9e63c 			; <UNDEFINED> instruction: 0xf8d9e63c
d002100c:	23000000 	movwcs	r0, #0
d0021010:	30046802 	andcc	r6, r4, r2, lsl #16
d0021014:	0000f8c9 	andeq	pc, r0, r9, asr #17
d0021018:	bb1bf7ff 	bllt	0xd071f01c
d002101c:	3000f8d9 	ldrdcc	pc, [r0], -r9
d0021020:	33046818 	movwcc	r6, #18456	; 0x4818
d0021024:	f8c917c1 			; <UNDEFINED> instruction: 0xf8c917c1
d0021028:	f7ff3000 			; <UNDEFINED> instruction: 0xf7ff3000
d002102c:	bf00bb58 	svclt	0x0000bb58
d0021030:	fffffc02 			; <UNDEFINED> instruction: 0xfffffc02
d0021034:	fffff88e 			; <UNDEFINED> instruction: 0xfffff88e

Disassembly of section .text.vsnprintf:

d0021038 <.text.vsnprintf>:
d0021038:	b0a7b5f0 	strdlt	fp, [r7], r0	; <UNPREDICTABLE>
d002103c:	460e4607 	strmi	r4, [lr], -r7, lsl #12
d0021040:	4614461d 			; <UNDEFINED> instruction: 0x4614461d
d0021044:	228c2100 	addcs	r2, ip, #0, 2
d0021048:	f7fea803 			; <UNDEFINED> instruction: 0xf7fea803
d002104c:	9701fc31 	smuadxls	r1, r1, ip
d0021050:	95009602 	strls	r9, [r0, #-1538]	; 0xfffff9fe
d0021054:	4621b134 			; <UNDEFINED> instruction: 0x4621b134
d0021058:	a801466a 	stmdage	r1, {r1, r3, r5, r6, r9, sl, lr}
d002105c:	fa54f7ff 	blx	0xd155f060
d0021060:	bdf0b027 	ldcllt	0, cr11, [r0, #156]!	; 0x9c
d0021064:	30fff04f 	rscscc	pc, pc, pc, asr #32
d0021068:	bf00e7fa 	svclt	0x0000e7fa

Disassembly of section .text.snprintf:

d002106c <.text.snprintf>:
d002106c:	b500b40c 	strlt	fp, [r0, #-1036]	; 0xfffffbf4
d0021070:	ab04b083 	blge	0xd014d284
d0021074:	2b04f853 	blcs	0xd015f1c8
d0021078:	f7ff9301 			; <UNDEFINED> instruction: 0xf7ff9301
d002107c:	b003ffdd 	ldrdlt	pc, [r3], -sp
d0021080:	eb04f85d 	bl	0xd015f1fc
d0021084:	4770b002 	ldrbmi	fp, [r0, -r2]!

Disassembly of section .text.memchr:

d00210b0 <.text.memchr>:
d00210b0:	4603b192 			; <UNDEFINED> instruction: 0x4603b192
d00210b4:	b410b2c9 	ldrlt	fp, [r0], #-713	; 0xfffffd37
d00210b8:	e0011884 	and	r1, r1, r4, lsl #17
d00210bc:	d00742a3 	andle	r4, r7, r3, lsr #5
d00210c0:	f8134618 			; <UNDEFINED> instruction: 0xf8134618
d00210c4:	428a2b01 	addmi	r2, sl, #1024	; 0x400
d00210c8:	f85dd1f8 			; <UNDEFINED> instruction: 0xf85dd1f8
d00210cc:	47704b04 	ldrbmi	r4, [r0, -r4, lsl #22]!
d00210d0:	f85d2000 			; <UNDEFINED> instruction: 0xf85d2000
d00210d4:	47704b04 	ldrbmi	r4, [r0, -r4, lsl #22]!
d00210d8:	47704610 			; <UNDEFINED> instruction: 0x47704610

Disassembly of section .text.strlen:

d00210dc <.text.strlen>:
d00210dc:	b1327802 	teqlt	r2, r2, lsl #16
d00210e0:	f8134603 			; <UNDEFINED> instruction: 0xf8134603
d00210e4:	29001f01 	stmdbcs	r0, {r0, r8, r9, sl, fp, ip}
d00210e8:	1a18d1fb 	bne	0xd06558dc
d00210ec:	46104770 			; <UNDEFINED> instruction: 0x46104770
d00210f0:	bf004770 	svclt	0x00004770

Disassembly of section .text.strcmp:

d00210f4 <.text.strcmp>:
d00210f4:	b1937803 	orrslt	r7, r3, r3, lsl #16
d00210f8:	e002b410 	and	fp, r2, r0, lsl r4
d00210fc:	3f01f810 	svccc	0x0001f810
d0021100:	460cb143 	strmi	fp, [ip], -r3, asr #2
d0021104:	2b01f811 	blcs	0xd009f150
d0021108:	d0f7429a 	smlalsle	r4, r7, sl, r2
d002110c:	f85d1a98 			; <UNDEFINED> instruction: 0xf85d1a98
d0021110:	47704b04 	ldrbmi	r4, [r0, -r4, lsl #22]!
d0021114:	f85d7862 			; <UNDEFINED> instruction: 0xf85d7862
d0021118:	1a984b04 	bne	0xce633d30
d002111c:	780a4770 	stmdavc	sl, {r4, r5, r6, r8, r9, sl, lr}
d0021120:	47701a98 			; <UNDEFINED> instruction: 0x47701a98

Disassembly of section .text.strchr:

d0021124 <.text.strchr>:
d0021124:	7803b2c9 	stmdavc	r3, {r0, r3, r6, r7, r9, ip, sp, pc}
d0021128:	d0064299 	mulle	r6, r9, r2
d002112c:	f810b123 			; <UNDEFINED> instruction: 0xf810b123
d0021130:	428b3f01 	addmi	r3, fp, #1, 30
d0021134:	4770d1fa 			; <UNDEFINED> instruction: 0x4770d1fa
d0021138:	47704618 			; <UNDEFINED> instruction: 0x47704618

Disassembly of section .text.strrchr:

d002113c <.text.strrchr>:
d002113c:	b2c92200 	sbclt	r2, r9, #0, 4
d0021140:	4604b410 			; <UNDEFINED> instruction: 0x4604b410
d0021144:	3b01f810 	blcc	0xd009f18c
d0021148:	bf08428b 	svclt	0x0008428b
d002114c:	2b004622 	blcs	0xd00329dc
d0021150:	4610d1f7 			; <UNDEFINED> instruction: 0x4610d1f7
d0021154:	4b04f85d 	blmi	0xd015f2d0
d0021158:	bf004770 	svclt	0x00004770
