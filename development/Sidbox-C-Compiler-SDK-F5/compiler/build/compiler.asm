
/mnt/LinuxDatas/work/SidboxIDE/SidboxIDE/development/Sidbox-C-Compiler-SDK-F5/compiler/build/cgarm/compiler-cgarm/compiler.elf:     file format elf32-littlearm


Disassembly of section .text.initMalloc:

d001f3a4 <.text.initMalloc>:
d001f3a4:	f44f4b06 			; <UNDEFINED> instruction: 0xf44f4b06
d001f3a8:	4a064180 	bmi	0xd01af9b0
d001f3ac:	589a447b 	ldmpl	sl, {r0, r1, r3, r4, r5, r6, sl, lr}
d001f3b0:	4a056011 	bmi	0xd01773fc
d001f3b4:	4b05589a 	blmi	0xd0175624
d001f3b8:	601a447b 	andsvs	r4, sl, fp, ror r4
d001f3bc:	bf004770 	svclt	0x00004770
d001f3c0:	000018e4 	andeq	r1, r0, r4, ror #17
d001f3c4:	00000004 	andeq	r0, r0, r4
d001f3c8:	00000000 	andeq	r0, r0, r0
d001f3cc:	00060c48 	andeq	r0, r6, r8, asr #24

Disassembly of section .text.applet_entry:

d001f3d0 <.text.applet_entry>:
d001f3d0:	9101b507 	tstls	r1, r7, lsl #10
d001f3d4:	ffe6f7ff 			; <UNDEFINED> instruction: 0xffe6f7ff
d001f3d8:	b0039901 	andlt	r9, r3, r1, lsl #18
d001f3dc:	eb04f85d 	bl	0xd015d558
d001f3e0:	bdeef7ff 	stcllt	7, cr15, [lr, #1020]!	; 0x3fc

Disassembly of section .text.read_file:

d001e3c4 <.text.read_file>:
d001e3c4:	41ffe92d 	mvnsmi	lr, sp, lsr #18
d001e3c8:	4b1a461e 	blmi	0xd06afc48
d001e3cc:	4690460f 	ldrmi	r4, [r0], pc, lsl #12
d001e3d0:	aa01685b 	bge	0xd0078544
d001e3d4:	681d2101 	ldmdavs	sp, {r0, r8, sp}
d001e3d8:	47986bab 	ldrmi	r6, [r8, fp, lsr #23]
d001e3dc:	4604b120 	strmi	fp, [r4], -r0, lsr #2
d001e3e0:	b0044620 	andlt	r4, r4, r0, lsr #12
d001e3e4:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d001e3e8:	0002e9cd 	andeq	lr, r2, sp, asr #19
d001e3ec:	a9026ceb 	stmdbge	r2, {r0, r1, r3, r5, r6, r7, sl, fp, sp, lr}
d001e3f0:	47989801 	ldrmi	r9, [r8, r1, lsl #16]
d001e3f4:	b9784604 	ldmdblt	r8!, {r2, r9, sl, lr}^
d001e3f8:	45429a02 	strbmi	r9, [r2, #-2562]	; 0xfffff5fe
d001e3fc:	b15ad817 	cmplt	sl, r7, lsl r8
d001e400:	ab036bec 	blge	0xd00f93b8
d001e404:	98014639 	stmdals	r1, {r0, r3, r4, r5, r9, sl, lr}
d001e408:	460447a0 	strmi	r4, [r4], -r0, lsr #15
d001e40c:	e9ddb920 	ldmib	sp, {r5, r8, fp, ip, sp, pc}^
d001e410:	1a240402 	bne	0xd091f420
d001e414:	2401bf18 	strcs	fp, [r1], #-3864	; 0xfffff0e8
d001e418:	98016d6b 	stmdals	r1, {r0, r1, r3, r5, r6, r8, sl, fp, sp, lr}
d001e41c:	2c004798 	stccs	7, cr4, [r0], {152}	; 0x98
d001e420:	4604d1de 			; <UNDEFINED> instruction: 0x4604d1de
d001e424:	d1db2800 	bicsle	r2, fp, r0, lsl #16
d001e428:	60339b02 	eorsvs	r9, r3, r2, lsl #22
d001e42c:	f06fe7d8 			; <UNDEFINED> instruction: 0xf06fe7d8
d001e430:	e7f10402 	ldrb	r0, [r1, r2, lsl #8]!
d001e434:	2001f000 	andcs	pc, r1, r0

Disassembly of section .text.read_apicore:

d001e458 <.text.read_apicore>:
d001e458:	460ab507 	strmi	fp, [sl], -r7, lsl #10
d001e45c:	48064601 	stmdami	r6, {r0, r9, sl, lr}
d001e460:	4478ab01 	ldrbtmi	sl, [r8], #-2817	; 0xfffff4ff
d001e464:	ffaef7ff 			; <UNDEFINED> instruction: 0xffaef7ff
d001e468:	9801b918 	stmdals	r1, {r3, r4, r8, fp, ip, sp, pc}
d001e46c:	f85db003 			; <UNDEFINED> instruction: 0xf85db003
d001e470:	2000fb04 	andcs	pc, r0, r4, lsl #22
d001e474:	bf00e7fa 	svclt	0x0000e7fa
d001e478:	ffffffd2 			; <UNDEFINED> instruction: 0xffffffd2

Disassembly of section .text.write_file:

d001e490 <.text.write_file>:
d001e490:	47ffe92d 	ldrbmi	lr, [pc, sp, lsr #18]!
d001e494:	46074b4a 	strmi	r4, [r7], -sl, asr #22
d001e498:	46154688 	ldrmi	r4, [r5], -r8, lsl #13
d001e49c:	681e685b 	ldmdavs	lr, {r0, r1, r3, r4, r6, fp, sp, lr}
d001e4a0:	fbb8f002 	blx	0xcee5a4b2
d001e4a4:	03f7f1a0 	mvnseq	pc, #160, 2	; 0x28
d001e4a8:	f5134604 			; <UNDEFINED> instruction: 0xf5134604
d001e4ac:	f2407f81 	vmax.f32	d23, d16, d1
d001e4b0:	f8df8084 			; <UNDEFINED> instruction: 0xf8df8084
d001e4b4:	46029110 			; <UNDEFINED> instruction: 0x46029110
d001e4b8:	f8df4639 			; <UNDEFINED> instruction: 0xf8df4639
d001e4bc:	44f9a10c 	ldrbtmi	sl, [r9], #268	; 0x10c
d001e4c0:	464844fa 			; <UNDEFINED> instruction: 0x464844fa
d001e4c4:	ff9cf000 			; <UNDEFINED> instruction: 0xff9cf000
d001e4c8:	220a4940 	andcs	r4, sl, #64, 18	; 0x100000
d001e4cc:	0004eb09 	andeq	lr, r4, r9, lsl #22
d001e4d0:	f0004479 			; <UNDEFINED> instruction: 0xf0004479
d001e4d4:	4622ff95 	qadd8mi	pc, r2, r5	; <UNPREDICTABLE>
d001e4d8:	46504639 			; <UNDEFINED> instruction: 0x46504639
d001e4dc:	ff90f000 			; <UNDEFINED> instruction: 0xff90f000
d001e4e0:	220a493b 	andcs	r4, sl, #966656	; 0xec000
d001e4e4:	0004eb0a 	andeq	lr, r4, sl, lsl #22
d001e4e8:	f0004479 			; <UNDEFINED> instruction: 0xf0004479
d001e4ec:	6bb3ff89 	blvs	0xced1e318
d001e4f0:	2106aa01 	tstcs	r6, r1, lsl #20
d001e4f4:	47984648 	ldrmi	r4, [r8, r8, asr #12]
d001e4f8:	4604b120 	strmi	fp, [r4], -r0, lsr #2
d001e4fc:	b0044620 	andlt	r4, r4, r0, lsr #12
d001e500:	87f0e8bd 			; <UNDEFINED> instruction: 0x87f0e8bd
d001e504:	b9759002 	ldmdblt	r5!, {r1, ip, pc}^
d001e508:	98016d33 	stmdals	r1, {r0, r1, r4, r5, r8, sl, fp, sp, lr}
d001e50c:	46044798 			; <UNDEFINED> instruction: 0x46044798
d001e510:	98016d73 	stmdals	r1, {r0, r1, r4, r5, r6, r8, sl, fp, sp, lr}
d001e514:	b90c4798 	stmdblt	ip, {r3, r4, r7, r8, r9, sl, lr}
d001e518:	4604b198 			; <UNDEFINED> instruction: 0x4604b198
d001e51c:	6db3482d 	ldcvs	8, cr4, [r3, #180]!	; 0xb4
d001e520:	47984478 			; <UNDEFINED> instruction: 0x47984478
d001e524:	6c34e7ea 	ldcvs	7, cr14, [r4], #-936	; 0xfffffc58
d001e528:	462aab02 	strtmi	sl, [sl], -r2, lsl #22
d001e52c:	98014641 	stmdals	r1, {r0, r6, r9, sl, lr}
d001e530:	460447a0 	strmi	r4, [r4], -r0, lsr #15
d001e534:	d1eb2800 	mvnle	r2, r0, lsl #16
d001e538:	42ab9b02 	adcmi	r9, fp, #2048	; 0x800
d001e53c:	2401d0e4 	strcs	sp, [r1], #-228	; 0xffffff1c
d001e540:	6ab3e7e6 	bvs	0xced184e0
d001e544:	a9034622 	stmdbge	r3, {r1, r5, r9, sl, lr}
d001e548:	94034638 	strls	r4, [r3], #-1592	; 0xfffff9c8
d001e54c:	46054798 			; <UNDEFINED> instruction: 0x46054798
d001e550:	9b03b980 	blls	0xd010cb58
d001e554:	d42407db 	strtle	r0, [r4], #-2011	; 0xfffff825
d001e558:	4638491f 			; <UNDEFINED> instruction: 0x4638491f
d001e55c:	44796df3 	ldrbtmi	r6, [r9], #-3571	; 0xfffff20d
d001e560:	46054798 			; <UNDEFINED> instruction: 0x46054798
d001e564:	481db1d8 	ldmdami	sp, {r3, r4, r6, r7, r8, ip, sp, pc}
d001e568:	44786db3 	ldrbtmi	r6, [r8], #-3507	; 0xfffff24d
d001e56c:	b9d44798 	ldmiblt	r4, {r3, r4, r7, r8, r9, sl, lr}^
d001e570:	e7c3462c 	strb	r4, [r3, ip, lsr #12]
d001e574:	d1f62804 	mvnsle	r2, r4, lsl #16
d001e578:	46394819 			; <UNDEFINED> instruction: 0x46394819
d001e57c:	44786df3 	ldrbtmi	r6, [r8], #-3571	; 0xfffff20d
d001e580:	46054798 			; <UNDEFINED> instruction: 0x46054798
d001e584:	d1ee2800 	mvnle	r2, r0, lsl #16
d001e588:	d0b72c00 	adcsle	r2, r7, r0, lsl #24
d001e58c:	6db34815 	ldcvs	8, cr4, [r3, #84]!	; 0x54
d001e590:	47984478 			; <UNDEFINED> instruction: 0x47984478
d001e594:	bf183800 	svclt	0x00183800
d001e598:	42442001 	submi	r2, r4, #1
d001e59c:	2401e7ae 	strcs	lr, [r1], #-1966	; 0xfffff852
d001e5a0:	2507e7ea 	strcs	lr, [r7, #-2026]	; 0xfffff816
d001e5a4:	4810e7df 	ldmdami	r0, {r0, r1, r2, r3, r4, r6, r7, r8, r9, sl, sp, lr, pc}
d001e5a8:	6df34639 	ldclvs	6, cr4, [r3, #228]!	; 0xe4
d001e5ac:	47984478 			; <UNDEFINED> instruction: 0x47984478
d001e5b0:	d0dd2800 	sbcsle	r2, sp, r0, lsl #16
d001e5b4:	0401f06f 	streq	pc, [r1], #-111	; 0xffffff91
d001e5b8:	2407e7a0 	strcs	lr, [r7], #-1952	; 0xfffff860
d001e5bc:	bf00e79e 	svclt	0x0000e79e
d001e5c0:	2001f000 	andcs	pc, r1, r0
d001e5c4:	000618be 			; <UNDEFINED> instruction: 0x000618be
d001e5c8:	0004061c 	andeq	r0, r4, ip, lsl r6
d001e5cc:	ffffffa8 			; <UNDEFINED> instruction: 0xffffffa8
d001e5d0:	ffffff9a 			; <UNDEFINED> instruction: 0xffffff9a
d001e5d4:	0006185c 	andeq	r1, r6, ip, asr r8
d001e5d8:	0004057e 	andeq	r0, r4, lr, ror r5
d001e5dc:	00061812 	andeq	r1, r6, r2, lsl r8
d001e5e0:	000617fe 	strdeq	r1, [r6], -lr
d001e5e4:	0004054c 	andeq	r0, r4, ip, asr #10
d001e5e8:	00040530 	andeq	r0, r4, r0, lsr r5

Disassembly of section .text.show_status:

d001e5f0 <.text.show_status>:
d001e5f0:	46024b09 	strmi	r4, [r2], -r9, lsl #22
d001e5f4:	6818447b 	ldmdavs	r8, {r0, r1, r3, r4, r5, r6, sl, lr}
d001e5f8:	689b4b06 	ldmvs	fp, {r1, r2, r8, r9, fp, lr}
d001e5fc:	68dbb120 	ldmvs	fp, {r5, r8, ip, sp, pc}^
d001e600:	f8d34611 			; <UNDEFINED> instruction: 0xf8d34611
d001e604:	471830c4 	ldrmi	r3, [r8, -r4, asr #1]
d001e608:	4904681b 	stmdbmi	r4, {r0, r1, r3, r4, fp, sp, lr}
d001e60c:	4479681b 	ldrbtmi	r6, [r9], #-2075	; 0xfffff7e5
d001e610:	bf004718 	svclt	0x00004718
d001e614:	2001f000 	andcs	pc, r1, r0
d001e618:	00061a08 	andeq	r1, r6, r8, lsl #20
d001e61c:	ffffffda 			; <UNDEFINED> instruction: 0xffffffda

Disassembly of section .text.open_editor:

d001e698 <.text.open_editor>:
d001e698:	47ffe92d 	ldrbmi	lr, [pc, sp, lsr #18]!
d001e69c:	f2404c5d 	vfma.f32	q10, q0, <illegal reg q6.5>
d001e6a0:	4607324d 	strmi	r3, [r7], -sp, asr #4
d001e6a4:	68a3210c 	stmiavs	r3!, {r2, r3, r8, sp}
d001e6a8:	685b2000 	ldmdavs	fp, {sp}^
d001e6ac:	4a5a9202 	bmi	0xd16c2ebc
d001e6b0:	9201447a 	andls	r4, r1, #2046820352	; 0x7a000000
d001e6b4:	728ef44f 	addvc	pc, lr, #1325400064	; 0x4f000000
d001e6b8:	22119200 	andscs	r9, r1, #0, 4
d001e6bc:	f44f681d 	vst2.8	{d22-d23}, [pc :64]!
d001e6c0:	47a873e4 	strmi	r7, [r8, r4, ror #7]!
d001e6c4:	46051e43 	strmi	r1, [r5], -r3, asr #28
d001e6c8:	2bfdb2db 	blcs	0xcff8b23c
d001e6cc:	4853d907 	ldmdami	r3, {r0, r1, r2, r8, fp, ip, lr, pc}^
d001e6d0:	f7ff4478 			; <UNDEFINED> instruction: 0xf7ff4478
d001e6d4:	2001ff8d 	andcs	pc, r1, sp, lsl #31
d001e6d8:	e8bdb004 	pop	{r2, ip, sp, pc}
d001e6dc:	4e5087f0 	mrcmi	7, 2, r8, cr0, cr0, {7}
d001e6e0:	447e212f 	ldrbtmi	r2, [lr], #-303	; 0xfffffed1
d001e6e4:	f0024630 			; <UNDEFINED> instruction: 0xf0024630
d001e6e8:	68a2fac5 	stmiavs	r2!, {r0, r2, r6, r7, r9, fp, ip, sp, lr, pc}
d001e6ec:	68d24603 	ldmvs	r2, {r0, r1, r9, sl, lr}^
d001e6f0:	8018f8d2 			; <UNDEFINED> instruction: 0x8018f8d2
d001e6f4:	d07a2800 	rsbsle	r2, sl, r0, lsl #16
d001e6f8:	26013301 	strcs	r3, [r1], -r1, lsl #6
d001e6fc:	23109301 	tstcs	r0, #67108864	; 0x4000000
d001e700:	21082209 	tstcs	r8, r9, lsl #4
d001e704:	93004628 	movwls	r4, #1576	; 0x628
d001e708:	7387f44f 	orrvc	pc, r7, #1325400064	; 0x4f000000
d001e70c:	f04f9602 			; <UNDEFINED> instruction: 0xf04f9602
d001e710:	47c00918 	bfimi	r0, r8, (invalid: 18:0)
d001e714:	4a4368a3 	bmi	0xd10f89a8
d001e718:	718ff44f 	orrvc	pc, pc, pc, asr #8
d001e71c:	468068db 	pkhtbmi	r6, r0, fp, asr #17
d001e720:	f8cd447a 			; <UNDEFINED> instruction: 0xf8cd447a
d001e724:	96029000 	strls	r9, [r2], -r0
d001e728:	92014628 	andls	r4, r1, #40, 12	; 0x2800000
d001e72c:	f8d32204 			; <UNDEFINED> instruction: 0xf8d32204
d001e730:	2344a008 	movtcs	sl, #16392	; 0x4008
d001e734:	4b3c47d0 	blmi	0xd0f3067c
d001e738:	f44f4a3c 	vst1.8	{d20-d21}, [pc :256], ip
d001e73c:	447b71b4 	ldrbtmi	r7, [fp], #-436	; 0xfffffe4c
d001e740:	6018447a 	andsvs	r4, r8, sl, ror r4
d001e744:	68a34628 	stmiavs	r3!, {r3, r5, r9, sl, lr}
d001e748:	920168db 	andls	r6, r1, #14352384	; 0xdb0000
d001e74c:	96022204 	strls	r2, [r2], -r4, lsl #4
d001e750:	9000f8cd 	andls	pc, r0, sp, asr #17
d001e754:	9008f8d3 	ldrdls	pc, [r8], -r3
d001e758:	47c8234e 	strbmi	r2, [r8, lr, asr #6]
d001e75c:	22004b34 	andcs	r4, r0, #52, 22	; 0xd000
d001e760:	447b2108 	ldrbtmi	r2, [fp], #-264	; 0xfffffef8
d001e764:	46286018 			; <UNDEFINED> instruction: 0x46286018
d001e768:	68db68a3 	ldmvs	fp, {r0, r1, r5, r7, fp, sp, lr}^
d001e76c:	4a319202 	bmi	0xd0c82f7c
d001e770:	447a9603 	ldrbtmi	r9, [sl], #-1539	; 0xfffff9fd
d001e774:	22c19201 	sbccs	r9, r1, #268435456	; 0x10000000
d001e778:	22229200 	eorcs	r9, r2, #0, 4
d001e77c:	9034f8d3 	ldrsbtls	pc, [r4], -r3	; <UNPREDICTABLE>
d001e780:	73d7f44f 	bicsvc	pc, r7, #1325400064	; 0x4f000000
d001e784:	4b2c47c8 	blmi	0xd0b306ac
d001e788:	6018447b 	andsvs	r4, r8, fp, ror r4
d001e78c:	68db68a3 	ldmvs	fp, {r0, r1, r5, r7, fp, sp, lr}^
d001e790:	9018f8d3 			; <UNDEFINED> instruction: 0x9018f8d3
d001e794:	d12c2f00 			; <UNDEFINED> instruction: 0xd12c2f00
d001e798:	447b4b28 	ldrbtmi	r4, [fp], #-2856	; 0xfffff4d8
d001e79c:	23129301 	tstcs	r2, #67108864	; 0x4000000
d001e7a0:	210822eb 	smlattcs	r8, fp, r2, r2
d001e7a4:	46289300 	strtmi	r9, [r8], -r0, lsl #6
d001e7a8:	73d7f44f 	bicsvc	pc, r7, #1325400064	; 0x4f000000
d001e7ac:	47c89602 	strbmi	r9, [r8, r2, lsl #12]
d001e7b0:	447b4b23 	ldrbtmi	r4, [fp], #-2851	; 0xfffff4dd
d001e7b4:	f1b86018 			; <UNDEFINED> instruction: 0xf1b86018
d001e7b8:	d00c0f00 	andle	r0, ip, r0, lsl #30
d001e7bc:	447b4b21 	ldrbtmi	r4, [fp], #-2849	; 0xfffff4df
d001e7c0:	b143681b 	cmplt	r3, fp, lsl r8
d001e7c4:	447b4b20 	ldrbtmi	r4, [fp], #-2848	; 0xfffff4e0
d001e7c8:	b123681b 			; <UNDEFINED> instruction: 0xb123681b
d001e7cc:	447e4e1f 	ldrbtmi	r4, [lr], #-3615	; 0xfffff1e1
d001e7d0:	b1036833 	tstlt	r3, r3, lsr r8
d001e7d4:	68a3b980 	stmiavs	r3!, {r7, r8, fp, ip, sp, pc}
d001e7d8:	685b4628 	ldmdavs	fp, {r3, r5, r9, sl, lr}^
d001e7dc:	4798685b 			; <UNDEFINED> instruction: 0x4798685b
d001e7e0:	22004b1b 	andcs	r4, r0, #27648	; 0x6c00
d001e7e4:	447b481b 	ldrbtmi	r4, [fp], #-2075	; 0xfffff7e5
d001e7e8:	601a4478 	andsvs	r4, sl, r8, ror r4
d001e7ec:	4633e771 			; <UNDEFINED> instruction: 0x4633e771
d001e7f0:	4b19e783 	blmi	0xd0698604
d001e7f4:	e7d1447b 			; <UNDEFINED> instruction: 0xe7d1447b
d001e7f8:	462868a3 	strtmi	r6, [r8], -r3, lsr #17
d001e7fc:	685b4917 	ldmdavs	fp, {r0, r1, r2, r4, r8, fp, lr}^
d001e800:	689b4479 	ldmvs	fp, {r0, r3, r4, r5, r6, sl, lr}
d001e804:	68a34798 	stmiavs	r3!, {r3, r4, r7, r8, r9, sl, lr}
d001e808:	68db6830 	ldmvs	fp, {r4, r5, fp, sp, lr}^
d001e80c:	47986ddb 			; <UNDEFINED> instruction: 0x47986ddb
d001e810:	e7612000 	strb	r2, [r1, -r0]!
d001e814:	2001f000 	andcs	pc, r1, r0
d001e818:	ffffff8a 			; <UNDEFINED> instruction: 0xffffff8a
d001e81c:	ffffff73 			; <UNDEFINED> instruction: 0xffffff73
d001e820:	0006159a 	muleq	r6, sl, r5
d001e824:	ffffff3f 			; <UNDEFINED> instruction: 0xffffff3f
d001e828:	0004152a 	andeq	r1, r4, sl, lsr #10
d001e82c:	ffffff24 			; <UNDEFINED> instruction: 0xffffff24
d001e830:	0004047a 	andeq	r0, r4, sl, ror r4
d001e834:	000414fa 	strdeq	r1, [r4], -sl
d001e838:	00040458 	andeq	r0, r4, r8, asr r4
d001e83c:	fffffe92 			; <UNDEFINED> instruction: 0xfffffe92
d001e840:	0006184a 	andeq	r1, r6, sl, asr #16
d001e844:	000414aa 	andeq	r1, r4, sl, lsr #9
d001e848:	00040416 	andeq	r0, r4, r6, lsl r4
d001e84c:	00040412 	andeq	r0, r4, r2, lsl r4
d001e850:	00061816 	andeq	r1, r6, r6, lsl r8
d001e854:	fffffe82 			; <UNDEFINED> instruction: 0xfffffe82
d001e858:	fffffe28 			; <UNDEFINED> instruction: 0xfffffe28
d001e85c:	00000521 	andeq	r0, r0, r1, lsr #10

Disassembly of section .text.report_file.part.0:

d001e908 <.text.report_file.part.0>:
d001e908:	1cc5b537 	cfstr64ne	mvdx11, [r5], {55}	; 0x37
d001e90c:	460b4604 	strmi	r4, [fp], -r4, lsl #12
d001e910:	4812d108 	ldmdami	r2, {r3, r8, ip, lr, pc}
d001e914:	f7ff4478 			; <UNDEFINED> instruction: 0xf7ff4478
d001e918:	1c63fe6b 	stclne	14, cr15, [r3], #-428	; 0xfffffe54
d001e91c:	41584258 	cmpmi	r8, r8, asr r2
d001e920:	bd30b003 	ldclt	0, cr11, [r0, #-12]!
d001e924:	d1021d20 	tstle	r2, r0, lsr #26
d001e928:	4478480d 	ldrbtmi	r4, [r8], #-2061	; 0xfffff7f3
d001e92c:	1ca1e7f3 	stcne	7, cr14, [r1], #972	; 0x3cc
d001e930:	480cd102 	stmdami	ip, {r1, r8, ip, lr, pc}
d001e934:	e7ee4478 			; <UNDEFINED> instruction: 0xe7ee4478
d001e938:	d1021c62 	tstle	r2, r2, ror #24
d001e93c:	4478480a 	ldrbtmi	r4, [r8], #-2058	; 0xfffff7f6
d001e940:	4d0ae7e9 	stcmi	7, cr14, [sl, #-932]	; 0xfffffc5c
d001e944:	71c0f44f 	bicvc	pc, r0, pc, asr #8
d001e948:	447d4a09 	ldrbtmi	r4, [sp], #-2569	; 0xfffff5f7
d001e94c:	447a9400 	ldrbtmi	r9, [sl], #-1024	; 0xfffffc00
d001e950:	f0024628 			; <UNDEFINED> instruction: 0xf0024628
d001e954:	4628f927 	strtmi	pc, [r8], -r7, lsr #18
d001e958:	bf00e7dd 	svclt	0x0000e7dd
d001e95c:	ffffff48 			; <UNDEFINED> instruction: 0xffffff48
d001e960:	ffffff49 			; <UNDEFINED> instruction: 0xffffff49
d001e964:	ffffff5a 			; <UNDEFINED> instruction: 0xffffff5a
d001e968:	ffffff7c 			; <UNDEFINED> instruction: 0xffffff7c
d001e96c:	00061532 	andeq	r1, r6, r2, lsr r5
d001e970:	ffffff9b 			; <UNDEFINED> instruction: 0xffffff9b

Disassembly of section .text.read_header:

d001e974 <.text.read_header>:
d001e974:	47f0e92d 	ldrbmi	lr, [r0, sp, lsr #18]!
d001e978:	460d9f09 	strmi	r9, [sp], -r9, lsl #30
d001e97c:	46984616 			; <UNDEFINED> instruction: 0x46984616
d001e980:	b9104681 	ldmdblt	r0, {r0, r7, r9, sl, lr}
d001e984:	e8bd2000 	ldmfd	sp!, {sp}
d001e988:	290087f0 	stmdbcs	r0, {r4, r5, r6, r7, r8, r9, sl, pc}
d001e98c:	780bd0fa 	stmdavc	fp, {r1, r3, r4, r5, r6, r7, ip, lr, pc}
d001e990:	d0f72b00 	rscsle	r2, r7, r0, lsl #22
d001e994:	d0f52b2f 	rscsle	r2, r5, pc, lsr #22
d001e998:	4628213a 			; <UNDEFINED> instruction: 0x4628213a
d001e99c:	f95ef002 			; <UNDEFINED> instruction: 0xf95ef002
d001e9a0:	d1ef2800 	mvnle	r2, r0, lsl #16
d001e9a4:	4648212f 	strbmi	r2, [r8], -pc, lsr #2
d001e9a8:	f964f002 			; <UNDEFINED> instruction: 0xf964f002
d001e9ac:	d0e92800 	rscle	r2, r9, r0, lsl #16
d001e9b0:	0409eba0 	streq	lr, [r9], #-2976	; 0xfffff460
d001e9b4:	f0024628 			; <UNDEFINED> instruction: 0xf0024628
d001e9b8:	9a0af92d 	bls	0xd02dce74
d001e9bc:	46823401 	strmi	r3, [r2], r1, lsl #8
d001e9c0:	429a1823 	addsmi	r1, sl, #2293760	; 0x230000
d001e9c4:	4622d9de 			; <UNDEFINED> instruction: 0x4622d9de
d001e9c8:	46384649 	ldrtmi	r4, [r8], -r9, asr #12
d001e9cc:	fd18f000 	ldc2	0, cr15, [r8, #-0]
d001e9d0:	0201f10a 	andeq	pc, r1, #-2147483646	; 0x80000002
d001e9d4:	19384629 	ldmdbne	r8!, {r0, r3, r5, r9, sl, lr}
d001e9d8:	fd12f000 	ldc2	0, cr15, [r2, #-0]
d001e9dc:	9b08b14e 	blls	0xd024af1c
d001e9e0:	46314642 	ldrtmi	r4, [r1], -r2, asr #12
d001e9e4:	f7ff4638 			; <UNDEFINED> instruction: 0xf7ff4638
d001e9e8:	fab0fced 	blx	0xcec5dda4
d001e9ec:	0940f080 	stmdbeq	r0, {r7, ip, sp, lr, pc}^
d001e9f0:	2001e7c9 	andcs	lr, r1, r9, asr #15
d001e9f4:	Address 0x00000000d001e9f4 is out of bounds.


Disassembly of section .text.resolve_path.constprop.0:

d001ea04 <.text.resolve_path.constprop.0>:
d001ea04:	460fb5f7 			; <UNDEFINED> instruction: 0x460fb5f7
d001ea08:	46044616 			; <UNDEFINED> instruction: 0x46044616
d001ea0c:	2000b910 	andcs	fp, r0, r0, lsl r9
d001ea10:	bdf0b003 	ldcllt	0, cr11, [r0, #12]!
d001ea14:	2b007803 	blcs	0xd003ca28
d001ea18:	f002d0f9 			; <UNDEFINED> instruction: 0xf002d0f9
d001ea1c:	4605f8fb 			; <UNDEFINED> instruction: 0x4605f8fb
d001ea20:	f0024638 			; <UNDEFINED> instruction: 0xf0024638
d001ea24:	4285f8f7 	addmi	pc, r5, #16187392	; 0xf70000
d001ea28:	1a2bd9f1 	bne	0xd0b151f4
d001ea2c:	44253f01 	strtmi	r3, [r5], #-3841	; 0xfffff0ff
d001ea30:	42ab4423 	adcmi	r4, fp, #587202560	; 0x23000000
d001ea34:	213ad118 	teqcs	sl, r8, lsl r1
d001ea38:	f0024620 			; <UNDEFINED> instruction: 0xf0024620
d001ea3c:	7823f90f 	stmdavc	r3!, {r0, r1, r2, r3, r8, fp, ip, sp, lr, pc}
d001ea40:	d0032b2f 	andle	r2, r3, pc, lsr #22
d001ea44:	7843b1d8 	stmdavc	r3, {r3, r4, r6, r7, r8, ip, sp, pc}^
d001ea48:	d1e02b2f 	mvnle	r2, pc, lsr #22
d001ea4c:	46234a21 	strtmi	r4, [r3], -r1, lsr #20
d001ea50:	7180f44f 	orrvc	pc, r0, pc, asr #8
d001ea54:	447a4630 	ldrbtmi	r4, [sl], #-1584	; 0xfffff9d0
d001ea58:	f8a4f002 			; <UNDEFINED> instruction: 0xf8a4f002
d001ea5c:	28fe3801 	ldmcs	lr!, {r0, fp, ip, sp}^
d001ea60:	2000bf8c 	andcs	fp, r0, ip, lsl #31
d001ea64:	e7d32001 	ldrb	r2, [r3, r1]
d001ea68:	1b01f813 	blne	0xd009cabc
d001ea6c:	2f01f817 	svccs	0x0001f817
d001ea70:	0120f041 	msreq	CPSR_, r1, asr #32
d001ea74:	0220f042 	eoreq	pc, r0, #66	; 0x42
d001ea78:	d0da4291 	smullsle	r4, sl, r1, r2
d001ea7c:	4b14e7c7 	blmi	0xd05589a0
d001ea80:	7180f44f 	orrvc	pc, r0, pc, asr #8
d001ea84:	685b4d14 	ldmdavs	fp, {r2, r4, r8, sl, fp, lr}^
d001ea88:	681b447d 	ldmdavs	fp, {r0, r2, r3, r4, r5, r6, sl, lr}
d001ea8c:	69db4628 	ldmibvs	fp, {r3, r5, r9, sl, lr}^
d001ea90:	28004798 	stmdacs	r0, {r3, r4, r7, r8, r9, sl, lr}
d001ea94:	782bd1bb 	stmdavc	fp!, {r0, r1, r3, r4, r5, r7, r8, ip, lr, pc}
d001ea98:	d0b82b00 	adcsle	r2, r8, r0, lsl #22
d001ea9c:	f0024628 			; <UNDEFINED> instruction: 0xf0024628
d001eaa0:	4428f8b9 	strtmi	pc, [r8], #-2233	; 0xfffff747
d001eaa4:	3c01f810 	stccc	8, cr15, [r1], {16}
d001eaa8:	d00d2b2f 	andle	r2, sp, pc, lsr #22
d001eaac:	447b4b0b 	ldrbtmi	r4, [fp], #-2827	; 0xfffff4f5
d001eab0:	f44f4a0b 	vst1.8	{d20-d21}, [pc], fp
d001eab4:	46307180 	ldrtmi	r7, [r0], -r0, lsl #3
d001eab8:	e9cd447a 	stmib	sp, {r1, r3, r4, r5, r6, sl, lr}^
d001eabc:	4b093400 	blmi	0xd026bac4
d001eac0:	f002447b 			; <UNDEFINED> instruction: 0xf002447b
d001eac4:	e7c9f86f 	strb	pc, [r9, pc, ror #16]	; <UNPREDICTABLE>
d001eac8:	447b4b07 	ldrbtmi	r4, [fp], #-2823	; 0xfffff4f9
d001eacc:	bf00e7f0 	svclt	0x0000e7f0
d001ead0:	2001f000 	andcs	pc, r1, r0
d001ead4:	ffffff9f 			; <UNDEFINED> instruction: 0xffffff9f
d001ead8:	000612f4 	strdeq	r1, [r6], -r4
d001eadc:	ffffff45 			; <UNDEFINED> instruction: 0xffffff45
d001eae0:	ffffff40 			; <UNDEFINED> instruction: 0xffffff40
d001eae4:	000612bc 			; <UNDEFINED> instruction: 0x000612bc
d001eae8:	ffffff28 			; <UNDEFINED> instruction: 0xffffff28

Disassembly of section .text.build:

d001eb40 <.text.build>:
d001eb40:	22004b5b 	andcs	r4, r0, #93184	; 0x16c00
d001eb44:	447bb570 	ldrbtmi	fp, [fp], #-1392	; 0xfffffa90
d001eb48:	9307b09e 	movwls	fp, #28830	; 0x709e
d001eb4c:	4b59a90e 	blmi	0xd1688f8c
d001eb50:	447b9008 	ldrbtmi	r9, [fp], #-8
d001eb54:	681b4858 	ldmdavs	fp, {r3, r4, r6, fp, lr}
d001eb58:	42934478 	addsmi	r4, r3, #120, 8	; 0x78000000
d001eb5c:	4b57d159 	blmi	0xd16130c8
d001eb60:	9306447b 	movwls	r4, #25723	; 0x647b
d001eb64:	d15a2a00 	cmple	sl, r0, lsl #20
d001eb68:	a906a807 	stmdbge	r6, {r0, r1, r2, fp, sp, pc}
d001eb6c:	2a01ab09 	bcs	0xd0089798
d001eb70:	ab059302 	blge	0xd0183780
d001eb74:	2201bf38 	andcs	fp, r1, #56, 30	; 0xe0
d001eb78:	4b519301 	blmi	0xd1483784
d001eb7c:	9300447b 	movwls	r4, #1147	; 0x47b
d001eb80:	447b4b50 	ldrbtmi	r4, [fp], #-2896	; 0xfffff4b0
d001eb84:	faa6f7ff 	blx	0xce9dcb88
d001eb88:	28004604 	stmdacs	r0, {r2, r9, sl, lr}
d001eb8c:	9c0dd14e 	stflsd	f5, [sp], {78}	; 0x4e
d001eb90:	4a4db94c 	bmi	0xd138d0c8
d001eb94:	447a9b0c 	ldrbtmi	r9, [sl], #-2828	; 0xfffff4f4
d001eb98:	42936812 	addsmi	r6, r3, #1179648	; 0x120000
d001eb9c:	4c4bd243 	sfmmi	f5, 3, [fp], {67}	; 0x43
d001eba0:	eb04447c 	bl	0xd012fd98
d001eba4:	212f2403 			; <UNDEFINED> instruction: 0x212f2403
d001eba8:	f0024620 			; <UNDEFINED> instruction: 0xf0024620
d001ebac:	b100f863 	tstlt	r0, r3, ror #16	; <UNPREDICTABLE>
d001ebb0:	9b091c44 	blls	0xd0265cc8
d001ebb4:	990b9a0a 	stmdbls	fp, {r1, r3, r9, fp, ip, pc}
d001ebb8:	4b45b90b 	blmi	0xd118cfec
d001ebbc:	4845447b 	stmdami	r5, {r0, r1, r3, r4, r5, r6, sl, lr}^
d001ebc0:	44789200 	ldrbtmi	r9, [r8], #-512	; 0xfffffe00
d001ebc4:	4d454a44 	vstrmi	s9, [r5, #-272]	; 0xfffffef0
d001ebc8:	46239302 	strtmi	r9, [r3], -r2, lsl #6
d001ebcc:	447a4604 	ldrbtmi	r4, [sl], #-1540	; 0xfffff9fc
d001ebd0:	447d9101 	ldrbtmi	r9, [sp], #-257	; 0xfffffeff
d001ebd4:	71c0f44f 	bicvc	pc, r0, pc, asr #8
d001ebd8:	ffe4f001 			; <UNDEFINED> instruction: 0xffe4f001
d001ebdc:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d001ebe0:	6828fd07 	stmdavs	r8!, {r0, r1, r2, r8, sl, fp, ip, sp, lr, pc}
d001ebe4:	d0482800 	suble	r2, r8, r0, lsl #16
d001ebe8:	b9849c0d 	stmiblt	r4, {r0, r2, r3, sl, fp, ip, pc}
d001ebec:	b171990a 	cmnlt	r1, sl, lsl #18
d001ebf0:	b1629a0b 	cmnlt	r2, fp, lsl #20
d001ebf4:	3a014e2d 	bcc	0xd00724b0
d001ebf8:	68b33901 	ldmvs	r3!, {r0, r8, fp, ip, sp}
d001ebfc:	f8d368db 			; <UNDEFINED> instruction: 0xf8d368db
d001ec00:	479830b8 			; <UNDEFINED> instruction: 0x479830b8
d001ec04:	682868b3 	stmdavs	r8!, {r0, r1, r4, r5, r7, fp, sp, lr}
d001ec08:	6ddb68db 	ldclvs	8, cr6, [fp, #876]	; 0x36c
d001ec0c:	20004798 	mulcs	r0, r8, r7
d001ec10:	eb00e033 	bl	0xd0056ce4
d001ec14:	f8412402 			; <UNDEFINED> instruction: 0xf8412402
d001ec18:	32014022 	andcc	r4, r1, #34	; 0x22
d001ec1c:	4830e79d 	ldmdami	r0!, {r0, r2, r3, r4, r7, r8, r9, sl, sp, lr, pc}
d001ec20:	4478a90e 	ldrbtmi	sl, [r8], #-2318	; 0xfffff6f2
d001ec24:	4c2fe7a2 	stcmi	7, cr14, [pc], #-648	; 0xd001e9a4
d001ec28:	e7bc447c 			; <UNDEFINED> instruction: 0xe7bc447c
d001ec2c:	46024d2e 	strmi	r4, [r2], -lr, lsr #26
d001ec30:	447d9905 	ldrbtmi	r9, [sp], #-2309	; 0xfffff6fb
d001ec34:	f7ff4628 			; <UNDEFINED> instruction: 0xf7ff4628
d001ec38:	2800fc2b 	stmdacs	r0, {r0, r1, r3, r5, sl, fp, ip, sp, lr, pc}
d001ec3c:	4b2bd131 	blmi	0xd0b13108
d001ec40:	6818447b 	ldmdavs	r8, {r0, r1, r3, r4, r5, r6, sl, lr}
d001ec44:	212fb118 			; <UNDEFINED> instruction: 0x212fb118
d001ec48:	f0024628 			; <UNDEFINED> instruction: 0xf0024628
d001ec4c:	4b28f813 	blmi	0xd0a5cca0
d001ec50:	681a447b 	ldmdavs	sl, {r0, r1, r3, r4, r5, r6, sl, lr}
d001ec54:	d9152a01 	ldmdble	r5, {r0, r9, fp, sp}
d001ec58:	1c43b188 	stfnep	f3, [r3], {136}	; 0x88
d001ec5c:	f44f4825 	vst2.8	{d20-d21}, [pc :128], r5
d001ec60:	920171c0 	andls	r7, r1, #192, 2	; 0x30
d001ec64:	44784a24 	ldrbtmi	r4, [r8], #-2596	; 0xfffff5dc
d001ec68:	447a9400 	ldrbtmi	r9, [sl], #-1024	; 0xfffffc00
d001ec6c:	ff9af001 			; <UNDEFINED> instruction: 0xff9af001
d001ec70:	44784822 	ldrbtmi	r4, [r8], #-2082	; 0xfffff7de
d001ec74:	fcbcf7ff 	ldc2	7, cr15, [ip], #1020	; 0x3fc
d001ec78:	b01e2001 	andslt	r2, lr, r1
d001ec7c:	4b20bd70 	blmi	0xd084e244
d001ec80:	e7eb447b 			; <UNDEFINED> instruction: 0xe7eb447b
d001ec84:	1c43b150 	stfnep	f3, [r3], {80}	; 0x50
d001ec88:	f44f4a1e 	vst1.8	{d20-d21}, [pc :64], lr
d001ec8c:	481e71c0 	ldmdami	lr, {r6, r7, r8, ip, sp, lr}
d001ec90:	9400447a 	strls	r4, [r0], #-1146	; 0xfffffb86
d001ec94:	f0014478 			; <UNDEFINED> instruction: 0xf0014478
d001ec98:	e7e9ff85 	strb	pc, [r9, r5, lsl #31]!	; <UNPREDICTABLE>
d001ec9c:	447b4b1b 	ldrbtmi	r4, [fp], #-2843	; 0xfffff4e5
d001eca0:	491be7f2 	ldmdbmi	fp, {r1, r4, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d001eca4:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d001eca8:	e7e6fe2f 	strb	pc, [r6, pc, lsr #28]!	; <UNPREDICTABLE>
d001ecac:	2001f000 	andcs	pc, r1, r0
d001ecb0:	00041126 	andeq	r1, r4, r6, lsr #2
d001ecb4:	00040092 	muleq	r4, r2, r0
d001ecb8:	00040090 	muleq	r4, r0, r0
d001ecbc:	0006111c 	andeq	r1, r6, ip, lsl r1
d001ecc0:	fffffdf5 			; <UNDEFINED> instruction: 0xfffffdf5
d001ecc4:	fffff8d3 			; <UNDEFINED> instruction: 0xfffff8d3
d001ecc8:	0004004e 	andeq	r0, r4, lr, asr #32
d001eccc:	00040048 	andeq	r0, r4, r8, asr #32
d001ecd0:	ffffff2c 			; <UNDEFINED> instruction: 0xffffff2c
d001ecd4:	000612ba 			; <UNDEFINED> instruction: 0x000612ba
d001ecd8:	ffffff2d 			; <UNDEFINED> instruction: 0xffffff2d
d001ecdc:	0004000e 	andeq	r0, r4, lr
d001ece0:	00040fc6 	andeq	r0, r4, r6, asr #31
d001ece4:	00061054 	andeq	r1, r6, r4, asr r0
d001ece8:	0003fdaa 	andeq	pc, r3, sl, lsr #27
d001ecec:	000613bc 			; <UNDEFINED> instruction: 0x000613bc
d001ecf0:	0003ff94 	muleq	r3, r4, pc	; <UNPREDICTABLE>
d001ecf4:	00061216 	andeq	r1, r6, r6, lsl r2
d001ecf8:	fffffe9d 			; <UNDEFINED> instruction: 0xfffffe9d
d001ecfc:	0006120a 	andeq	r1, r6, sl, lsl #4
d001ed00:	0003fd5c 	andeq	pc, r3, ip, asr sp	; <UNPREDICTABLE>
d001ed04:	fffffe97 			; <UNDEFINED> instruction: 0xfffffe97
d001ed08:	000611e8 	andeq	r1, r6, r8, ror #3
d001ed0c:	0003fd3e 	andeq	pc, r3, lr, lsr sp	; <UNPREDICTABLE>
d001ed10:	fffff9c0 			; <UNDEFINED> instruction: 0xfffff9c0

Disassembly of section .text.editor_proc:

d001ed24 <.text.editor_proc>:
d001ed24:	460cb513 			; <UNDEFINED> instruction: 0x460cb513
d001ed28:	d0412900 	suble	r2, r1, r0, lsl #18
d001ed2c:	2b10680b 	blcs	0xd0438d60
d001ed30:	68cad13e 	stmiavs	sl, {r1, r2, r3, r4, r5, r8, ip, lr, pc}^
d001ed34:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d001ed38:	d139429a 	teqle	r9, sl	; <illegal shifter operand>
d001ed3c:	688b4a1f 	stmvs	fp, {r0, r1, r2, r3, r4, r9, fp, lr}
d001ed40:	6812447a 	ldmdavs	r2, {r1, r3, r4, r5, r6, sl, lr}
d001ed44:	d0044293 	mulle	r4, r3, r2
d001ed48:	447a4a1d 	ldrbtmi	r4, [sl], #-2589	; 0xfffff5e3
d001ed4c:	42936812 	addsmi	r6, r3, #1179648	; 0x120000
d001ed50:	4b18d12e 	blmi	0xd0653210
d001ed54:	689b481b 	ldmvs	fp, {r0, r1, r3, r4, fp, lr}
d001ed58:	4478491b 	ldrbtmi	r4, [r8], #-2331	; 0xfffff6e5
d001ed5c:	447968db 	ldrbtmi	r6, [r9], #-2267	; 0xfffff725
d001ed60:	6f1b4a15 	svcvs	0x001b4a15
d001ed64:	91016800 	tstls	r1, r0, lsl #16
d001ed68:	38014798 	stmdacc	r1, {r3, r4, r7, r8, r9, sl, lr}
d001ed6c:	f5b09901 			; <UNDEFINED> instruction: 0xf5b09901
d001ed70:	d9043f00 	stmdble	r4, {r8, r9, sl, fp, ip, sp}
d001ed74:	44784815 	ldrbtmi	r4, [r8], #-2069	; 0xfffff7eb
d001ed78:	fc3af7ff 	ldc2	7, cr15, [sl], #-1020	; 0xfffffc04
d001ed7c:	4b14e007 	blmi	0xd0556da0
d001ed80:	447b68a2 	ldrbtmi	r6, [fp], #-2210	; 0xfffff75e
d001ed84:	429a681b 	addsmi	r6, sl, #1769472	; 0x1b0000
d001ed88:	f7ffd104 			; <UNDEFINED> instruction: 0xf7ffd104
d001ed8c:	20f0fed9 	ldrsbtcs	pc, [r0], #233	; 0xe9	; <UNPREDICTABLE>
d001ed90:	bd10b002 	ldclt	0, cr11, [r0, #-8]
d001ed94:	480f4602 	stmdami	pc, {r1, r9, sl, lr}	; <UNPREDICTABLE>
d001ed98:	f7ff4478 			; <UNDEFINED> instruction: 0xf7ff4478
d001ed9c:	b910fb79 	ldmdblt	r0, {r0, r3, r4, r5, r6, r8, r9, fp, ip, sp, lr, pc}
d001eda0:	4478480d 	ldrbtmi	r4, [r8], #-2061	; 0xfffff7f3
d001eda4:	490de7e8 	stmdbmi	sp, {r3, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d001eda8:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d001edac:	e7eefdad 	strb	pc, [lr, sp, lsr #27]!	; <UNPREDICTABLE>
d001edb0:	e7ed2000 	strb	r2, [sp, r0]!
d001edb4:	2001f000 	andcs	pc, r1, r0
d001edb8:	00020001 	andeq	r0, r2, r1
d001edbc:	00040f28 	andeq	r0, r4, r8, lsr #30
d001edc0:	0003fe92 	muleq	r3, r2, lr
d001edc4:	0003fe86 	andeq	pc, r3, r6, lsl #29
d001edc8:	00040f0e 	andeq	r0, r4, lr, lsl #30
d001edcc:	fffffae6 			; <UNDEFINED> instruction: 0xfffffae6
d001edd0:	0003fe5a 	andeq	pc, r3, sl, asr lr	; <UNPREDICTABLE>
d001edd4:	00060ee4 	andeq	r0, r6, r4, ror #29
d001edd8:	ffffff6e 			; <UNDEFINED> instruction: 0xffffff6e
d001eddc:	fffff8b7 			; <UNDEFINED> instruction: 0xfffff8b7

Disassembly of section .text.startup.main:

d001efc0 <.text.startup.main>:
d001efc0:	e92d2801 	push	{r0, fp, sp}
d001efc4:	46044ff0 			; <UNDEFINED> instruction: 0x46044ff0
d001efc8:	ed2d460f 	stc	6, cr4, [sp, #-60]!	; 0xffffffc4
d001efcc:	b0978b02 	addslt	r8, r7, r2, lsl #22
d001efd0:	808cf000 	addhi	pc, ip, r0
d001efd4:	f0402803 			; <UNDEFINED> instruction: 0xf0402803
d001efd8:	49af8159 	stmibmi	pc!, {r0, r3, r4, r6, r8, pc}	; <UNPREDICTABLE>
d001efdc:	44796878 	ldrbtmi	r6, [r9], #-2168	; 0xfffff788
d001efe0:	fe24f001 	cdp2	0, 2, cr15, cr4, cr1, {0}
d001efe4:	f680fab0 			; <UNDEFINED> instruction: 0xf680fab0
d001efe8:	49ac0976 	stmibmi	ip!, {r1, r2, r4, r5, r6, r8, fp}
d001efec:	44796878 	ldrbtmi	r6, [r9], #-2168	; 0xfffff788
d001eff0:	fe1cf001 	cdp2	0, 1, cr15, cr12, cr1, {0}
d001eff4:	b966b958 	stmdblt	r6!, {r3, r4, r6, r8, fp, ip, sp, pc}^
d001eff8:	447848a9 	ldrbtmi	r4, [r8], #-2217	; 0xfffff757
d001effc:	f7ff2401 			; <UNDEFINED> instruction: 0xf7ff2401
d001f000:	4620faf7 			; <UNDEFINED> instruction: 0x4620faf7
d001f004:	ecbdb017 	ldc	0, cr11, [sp], #92	; 0x5c
d001f008:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d001f00c:	2e008ff0 	mcrcs	15, 0, r8, cr0, cr0, {7}
d001f010:	f104d05d 			; <UNDEFINED> instruction: 0xf104d05d
d001f014:	25004480 	strcs	r4, [r0, #-1152]	; 0xfffffb80
d001f018:	46ab3c01 	strtmi	r3, [fp], r1, lsl #24
d001f01c:	0024f857 	eoreq	pc, r4, r7, asr r8	; <UNPREDICTABLE>
d001f020:	f8df2401 			; <UNDEFINED> instruction: 0xf8df2401
d001f024:	49a08280 	stmibmi	r0!, {r7, r9, pc}
d001f028:	447944f8 	ldrbtmi	r4, [r9], #-1272	; 0xfffffb08
d001f02c:	f7ff4642 			; <UNDEFINED> instruction: 0xf7ff4642
d001f030:	2800fce9 	stmdacs	r0, {r0, r3, r5, r6, r7, sl, fp, ip, sp, lr, pc}
d001f034:	489dd15f 	ldmmi	sp, {r0, r1, r2, r3, r4, r6, r8, ip, lr, pc}
d001f038:	e7df4478 			; <UNDEFINED> instruction: 0xe7df4478
d001f03c:	0389ea4f 	orreq	lr, r9, #323584	; 0x4f000
d001f040:	1a10ee18 	bne	0xd045a8a8
d001f044:	0029f857 	eoreq	pc, r9, r7, asr r8	; <UNPREDICTABLE>
d001f048:	0889eb07 	stmeq	r9, {r0, r1, r2, r8, r9, fp, sp, lr, pc}
d001f04c:	f0019302 			; <UNDEFINED> instruction: 0xf0019302
d001f050:	b960fded 	stmdblt	r0!, {r0, r2, r3, r5, r6, r7, r8, sl, fp, ip, sp, lr, pc}^
d001f054:	f109b946 			; <UNDEFINED> instruction: 0xf109b946
d001f058:	42a10101 	adcmi	r0, r1, #1073741824	; 0x40000000
d001f05c:	f8d8da04 			; <UNDEFINED> instruction: 0xf8d8da04
d001f060:	78091004 	stmdavc	r9, {r2, ip}
d001f064:	d130292d 	teqle	r0, sp, lsr #18
d001f068:	44784891 	ldrbtmi	r4, [r8], #-2193	; 0xfffff76f
d001f06c:	4651e7c6 	ldrbmi	lr, [r1], -r6, asr #15
d001f070:	0029f857 	eoreq	pc, r9, r7, asr r8	; <UNPREDICTABLE>
d001f074:	fddaf001 	ldc2l	0, cr15, [sl, #4]
d001f078:	f1bbb978 			; <UNDEFINED> instruction: 0xf1bbb978
d001f07c:	d1090f00 	tstle	r9, r0, lsl #30
d001f080:	0901f109 	stmdbeq	r1, {r0, r3, r8, ip, sp, lr, pc}
d001f084:	da0545a1 	ble	0xd0170710
d001f088:	b004f8d8 	ldrdlt	pc, [r4], -r8
d001f08c:	1000f89b 	mulne	r0, fp, r8
d001f090:	d112292d 	tstle	r2, sp, lsr #18
d001f094:	44784887 	ldrbtmi	r4, [r8], #-2183	; 0xfffff779
d001f098:	9b02e7b0 	blls	0xd00d8f60
d001f09c:	780858f9 	stmdavc	r8, {r0, r3, r4, r5, r6, r7, fp, ip, lr}
d001f0a0:	d001282d 	andle	r2, r1, sp, lsr #16
d001f0a4:	d9022d0f 	stmdble	r2, {r0, r1, r2, r3, r8, sl, fp, sp}
d001f0a8:	44784883 	ldrbtmi	r4, [r8], #-2179	; 0xfffff77d
d001f0ac:	ab16e7a6 	blge	0xd05d8f4c
d001f0b0:	0085eb03 	addeq	lr, r5, r3, lsl #22
d001f0b4:	f8403501 			; <UNDEFINED> instruction: 0xf8403501
d001f0b8:	f1091c40 			; <UNDEFINED> instruction: 0xf1091c40
d001f0bc:	45a10901 	strmi	r0, [r1, #2305]!	; 0x901
d001f0c0:	b985dbbc 	stmiblt	r5, {r2, r3, r4, r5, r7, r8, r9, fp, ip, lr, pc}
d001f0c4:	4478487d 	ldrbtmi	r4, [r8], #-2173	; 0xfffff783
d001f0c8:	2601e798 			; <UNDEFINED> instruction: 0x2601e798
d001f0cc:	4b7ce7f5 	blmi	0xd1f590a8
d001f0d0:	0901f04f 	stmdbeq	r1, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d001f0d4:	a1ecf8df 	ldrdge	pc, [ip, #143]!	; 0x8f
d001f0d8:	447b4635 	ldrbtmi	r4, [fp], #-1589	; 0xfffff9cb
d001f0dc:	44fa46b3 	ldrbtmi	r4, [sl], #1715	; 0x6b3
d001f0e0:	3a10ee08 	bcc	0xd045a908
d001f0e4:	9806e7eb 	stmdals	r6, {r0, r1, r3, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d001f0e8:	e79a2400 	ldr	r2, [sl, r0, lsl #8]
d001f0ec:	48762500 	ldmdami	r6!, {r8, sl, sp}^
d001f0f0:	447846ab 	ldrbtmi	r4, [r8], #-1707	; 0xfffff955
d001f0f4:	f1bbe795 			; <UNDEFINED> instruction: 0xf1bbe795
d001f0f8:	d0290f00 	eorle	r0, r9, r0, lsl #30
d001f0fc:	46584a73 			; <UNDEFINED> instruction: 0x46584a73
d001f100:	447a4973 	ldrbtmi	r4, [sl], #-2419	; 0xfffff68d
d001f104:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d001f108:	2800fc7d 	stmdacs	r0, {r0, r2, r3, r4, r5, r6, sl, fp, ip, sp, lr, pc}
d001f10c:	4871d093 	ldmdami	r1!, {r0, r1, r4, r7, ip, lr, pc}^
d001f110:	f0014478 			; <UNDEFINED> instruction: 0xf0014478
d001f114:	38f7fd7f 	ldmcc	r7!, {r0, r1, r2, r3, r4, r5, r6, r8, sl, fp, ip, sp, lr, pc}^
d001f118:	7f81f510 	svcvc	0x0081f510
d001f11c:	2c00d98b 			; <UNDEFINED> instruction: 0x2c00d98b
d001f120:	8086f040 	addhi	pc, r6, r0, asr #32
d001f124:	46274b6c 	strtmi	r4, [r7], -ip, ror #22
d001f128:	a1b0f8df 	asrsge	pc, pc	; <illegal shifter operand>	; <UNPREDICTABLE>
d001f12c:	f8df447b 			; <UNDEFINED> instruction: 0xf8df447b
d001f130:	44fab1b0 	ldrbtmi	fp, [sl], #432	; 0x1b0
d001f134:	44fb601c 	ldrbtmi	r6, [fp], #28
d001f138:	447b4b6a 	ldrbtmi	r4, [fp], #-2922	; 0xfffff496
d001f13c:	42ac9302 	adcmi	r9, ip, #134217728	; 0x8000000
d001f140:	2000d11d 	andcs	sp, r0, sp, lsl r1
d001f144:	fcfcf7ff 	ldc2l	7, cr15, [ip], #1020	; 0x3fc
d001f148:	f480fab0 	vst3.32			; <UNDEFINED> instruction: 0xf480fab0
d001f14c:	e7580964 	ldrb	r0, [r8, -r4, ror #18]
d001f150:	f0014640 			; <UNDEFINED> instruction: 0xf0014640
d001f154:	1cc3fd5f 	stclne	13, cr15, [r3], {95}	; 0x5f
d001f158:	7f80f5b3 	svcvc	0x0080f5b3
d001f15c:	af6bf63f 	svcge	0x006bf63f
d001f160:	1e464f61 	cdpne	15, 4, cr4, cr6, cr1, {3}
d001f164:	447f4641 	ldrbtmi	r4, [pc], #-1601	; 0xd001f16c
d001f168:	46384632 			; <UNDEFINED> instruction: 0x46384632
d001f16c:	f948f000 			; <UNDEFINED> instruction: 0xf948f000
d001f170:	2204495e 	andcs	r4, r4, #1540096	; 0x178000
d001f174:	447919b8 	ldrbtmi	r1, [r9], #-2488	; 0xfffff648
d001f178:	f942f000 			; <UNDEFINED> instruction: 0xf942f000
d001f17c:	9a02e7c7 	bls	0xd00d90a0
d001f180:	f8daab06 			; <UNDEFINED> instruction: 0xf8daab06
d001f184:	46598000 	ldrbmi	r8, [r9], -r0
d001f188:	3024f853 	eorcc	pc, r4, r3, asr r8	; <UNPREDICTABLE>
d001f18c:	2908eb02 	stmdbcs	r8, {r1, r8, r9, fp, sp, lr, pc}
d001f190:	93034618 	movwls	r4, #13848	; 0x3618
d001f194:	f7ff464a 			; <UNDEFINED> instruction: 0xf7ff464a
d001f198:	9b03fc35 	blls	0xd011e274
d001f19c:	4c54b948 	mrrcmi	9, 4, fp, r4, cr8	; <UNPREDICTABLE>
d001f1a0:	447c4a54 	ldrbtmi	r4, [ip], #-2644	; 0xfffff5ac
d001f1a4:	f44f447a 	vst3.16	{d20-d22}, [pc :256], sl
d001f1a8:	462071c0 	strtmi	r7, [r0], -r0, asr #3
d001f1ac:	fcfaf001 	ldc2l	0, cr15, [sl], #4
d001f1b0:	2300e01f 	movwcs	lr, #31
d001f1b4:	0607eb08 	streq	lr, [r7], -r8, lsl #22
d001f1b8:	3200f5c7 	andcc	pc, r0, #834666496	; 0x31c00000
d001f1bc:	93054648 	movwls	r4, #22088	; 0x5648
d001f1c0:	447b4b4d 	ldrbtmi	r4, [fp], #-2893	; 0xfffff4b3
d001f1c4:	ab05441e 	blge	0xd0170244
d001f1c8:	f7ff4631 			; <UNDEFINED> instruction: 0xf7ff4631
d001f1cc:	4601f8fb 			; <UNDEFINED> instruction: 0x4601f8fb
d001f1d0:	1cc3b188 	stfnep	f3, [r3], {136}	; 0x88
d001f1d4:	4849d102 	stmdami	r9, {r1, r8, ip, lr, pc}^
d001f1d8:	e70f4478 	smlsdx	pc, r8, r4, r4	; <UNPREDICTABLE>
d001f1dc:	464b4c48 	strbmi	r4, [fp], -r8, asr #24
d001f1e0:	f44f4a48 	vst1.16	{d20-d21}, [pc], r8
d001f1e4:	447c71c0 	ldrbtmi	r7, [ip], #-448	; 0xfffffe40
d001f1e8:	447a9000 	ldrbtmi	r9, [sl], #-0
d001f1ec:	f0014620 			; <UNDEFINED> instruction: 0xf0014620
d001f1f0:	4620fcd9 			; <UNDEFINED> instruction: 0x4620fcd9
d001f1f4:	9a05e702 	bls	0xd0198e04
d001f1f8:	f0014630 			; <UNDEFINED> instruction: 0xf0014630
d001f1fc:	b128fcf5 	strdlt	pc, [r8, -r5]!
d001f200:	464b4c41 	strbmi	r4, [fp], -r1, asr #24
d001f204:	447c4a41 	ldrbtmi	r4, [ip], #-2625	; 0xfffff5bf
d001f208:	e7cc447a 			; <UNDEFINED> instruction: 0xe7cc447a
d001f20c:	34014b40 	strcc	r4, [r1], #-2880	; 0xfffff4c0
d001f210:	447b9a05 	ldrbtmi	r9, [fp], #-2565	; 0xfffff5fb
d001f214:	54b04417 	ldrtpl	r4, [r0], #1047	; 0x417
d001f218:	6038f843 	eorsvs	pc, r8, r3, asr #16
d001f21c:	08c8eb03 	stmiaeq	r8, {r0, r1, r8, r9, fp, sp, lr, pc}^
d001f220:	3000f8da 	ldrdcc	pc, [r0], -sl
d001f224:	2004f8c8 	andcs	pc, r4, r8, asr #17
d001f228:	f8ca3301 			; <UNDEFINED> instruction: 0xf8ca3301
d001f22c:	e7863000 	str	r3, [r6, r0]
d001f230:	23004d38 	movwcs	r4, #3384	; 0xd38
d001f234:	f44f4838 	vst2.8	{d20-d21}, [pc :256], r8
d001f238:	447d3200 	ldrbtmi	r3, [sp], #-512	; 0xfffffe00
d001f23c:	44789305 	ldrbtmi	r9, [r8], #-773	; 0xfffffcfb
d001f240:	4629ab05 	strtmi	sl, [r9], -r5, lsl #22
d001f244:	f8bef7ff 			; <UNDEFINED> instruction: 0xf8bef7ff
d001f248:	4601b948 	strmi	fp, [r1], -r8, asr #18
d001f24c:	46289a05 	strtmi	r9, [r8], -r5, lsl #20
d001f250:	fccaf001 	stc2l	0, cr15, [sl], {1}
d001f254:	9b05b980 	blls	0xd018d85c
d001f258:	200054e8 	andcs	r5, r0, r8, ror #9
d001f25c:	2804e008 	stmdacs	r4, {r3, sp, lr, pc}
d001f260:	492ed10c 	stmdbmi	lr!, {r2, r3, r8, ip, lr, pc}
d001f264:	4628227d 			; <UNDEFINED> instruction: 0x4628227d
d001f268:	f0004479 			; <UNDEFINED> instruction: 0xf0004479
d001f26c:	2001f8c9 	andcs	pc, r1, r9, asr #17
d001f270:	fa12f7ff 	blx	0xd04dd274
d001f274:	e6c44604 	strb	r4, [r4], r4, lsl #12
d001f278:	0003f06f 	andeq	pc, r3, pc, rrx
d001f27c:	44794928 	ldrbtmi	r4, [r9], #-2344	; 0xfffff6d8
d001f280:	fb42f7ff 	blx	0xd10dd286
d001f284:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001f288:	e7e6aebc 			; <UNDEFINED> instruction: 0xe7e6aebc
d001f28c:	f77f2800 			; <UNDEFINED> instruction: 0xf77f2800
d001f290:	2600aeb3 			; <UNDEFINED> instruction: 0x2600aeb3
d001f294:	bf00e6a9 	svclt	0x0000e6a9
d001f298:	fffffe06 			; <UNDEFINED> instruction: 0xfffffe06
d001f29c:	fffffdf6 			; <UNDEFINED> instruction: 0xfffffdf6
d001f2a0:	fffffded 			; <UNDEFINED> instruction: 0xfffffded
d001f2a4:	00060c54 	andeq	r0, r6, r4, asr ip
d001f2a8:	fffffed9 			; <UNDEFINED> instruction: 0xfffffed9
d001f2ac:	fffffece 			; <UNDEFINED> instruction: 0xfffffece
d001f2b0:	fffffdc5 			; <UNDEFINED> instruction: 0xfffffdc5
d001f2b4:	fffffdd1 			; <UNDEFINED> instruction: 0xfffffdd1
d001f2b8:	fffffdf2 			; <UNDEFINED> instruction: 0xfffffdf2
d001f2bc:	fffffe06 			; <UNDEFINED> instruction: 0xfffffe06
d001f2c0:	fffffd52 			; <UNDEFINED> instruction: 0xfffffd52
d001f2c4:	fffffd86 			; <UNDEFINED> instruction: 0xfffffd86
d001f2c8:	fffffcea 			; <UNDEFINED> instruction: 0xfffffcea
d001f2cc:	0003f8da 	ldrdeq	pc, [r3], -sl
d001f2d0:	fffffe36 			; <UNDEFINED> instruction: 0xfffffe36
d001f2d4:	0003f8cc 	andeq	pc, r3, ip, asr #17
d001f2d8:	0003fab8 			; <UNDEFINED> instruction: 0x0003fab8
d001f2dc:	0003fab2 			; <UNDEFINED> instruction: 0x0003fab2
d001f2e0:	fffffdcd 			; <UNDEFINED> instruction: 0xfffffdcd
d001f2e4:	0003faae 	andeq	pc, r3, lr, lsr #21
d001f2e8:	0003f876 	andeq	pc, r3, r6, ror r8	; <UNPREDICTABLE>
d001f2ec:	fffffdc9 			; <UNDEFINED> instruction: 0xfffffdc9
d001f2f0:	00060cda 	ldrdeq	r0, [r6], -sl
d001f2f4:	fffffd9f 			; <UNDEFINED> instruction: 0xfffffd9f
d001f2f8:	00040aaa 	andeq	r0, r4, sl, lsr #21
d001f2fc:	fffffd86 			; <UNDEFINED> instruction: 0xfffffd86
d001f300:	00060c96 	muleq	r6, r6, ip
d001f304:	fffffd94 			; <UNDEFINED> instruction: 0xfffffd94
d001f308:	00060c76 	andeq	r0, r6, r6, ror ip
d001f30c:	fffffd8d 			; <UNDEFINED> instruction: 0xfffffd8d
d001f310:	000409d6 	ldrdeq	r0, [r4], -r6
d001f314:	00040a32 	andeq	r0, r4, r2, lsr sl
d001f318:	00060a3e 	andeq	r0, r6, lr, lsr sl
d001f31c:	000000b8 	strheq	r0, [r0], -r8
d001f320:	fffffd2f 			; <UNDEFINED> instruction: 0xfffffd2f

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
d001023c:	f44ff8d3 	vst2.<illegal width 64>	{d31-d32}, [pc :64], r3
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
d00102b8:	33f6f500 	mvnscc	pc, #0, 10
d00102bc:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d00102c0:	23286f1c 			; <UNDEFINED> instruction: 0x23286f1c
d00102c4:	46884606 	strmi	r4, [r8], r6, lsl #12
d00102c8:	fb031e65 	blx	0xd00d7c66
d00102cc:	46170404 	ldrmi	r0, [r7], -r4, lsl #8
d00102d0:	34e9f504 	strbtcc	pc, [r9], #1284	; 0x504	; <UNPREDICTABLE>
d00102d4:	74a4f504 	strtvc	pc, [r4], #1284	; 0x504
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
d0010300:	2800f88f 	stmdacs	r0, {r0, r1, r2, r3, r7, fp, ip, sp, lr, pc}
d0010304:	4628d1f2 			; <UNDEFINED> instruction: 0x4628d1f2
d0010308:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d

Disassembly of section .text.pp_take:

d001030c <.text.pp_take>:
d001030c:	460eb570 			; <UNDEFINED> instruction: 0x460eb570
d0010310:	f7ff4604 			; <UNDEFINED> instruction: 0xf7ff4604
d0010314:	4630ffb1 			; <UNDEFINED> instruction: 0x4630ffb1
d0010318:	fc7cf010 	ldc2l	0, cr15, [ip], #-64	; 0xffffffc0
d001031c:	46056aa3 	strmi	r6, [r5], -r3, lsr #21
d0010320:	1a1b6a60 	bne	0xd06eaca8
d0010324:	d20142ab 	andle	r4, r1, #-1342177270	; 0xb000000a
d0010328:	bd702000 	ldcllt	0, cr2, [r0, #-0]
d001032c:	4631462a 	ldrtmi	r4, [r1], -sl, lsr #12
d0010330:	f876f00f 			; <UNDEFINED> instruction: 0xf876f00f
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
d0010366:	fc55f010 	mrrc2	0, 1, pc, r5, cr0	; <UNPREDICTABLE>
d001036a:	d10842b8 			; <UNDEFINED> instruction: 0xd10842b8
d001036e:	4641463a 			; <UNDEFINED> instruction: 0x4641463a
d0010372:	f00f4630 			; <UNDEFINED> instruction: 0xf00f4630
d0010376:	b910f854 	ldmdblt	r0, {r2, r4, r6, fp, ip, sp, lr, pc}
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
d00103b8:	bb58f833 	bllt	0xd164e48c
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
d0010628:	fefaf00e 	cdp2	0, 15, cr15, cr10, cr14, {0}
d001062c:	f080fab0 			; <UNDEFINED> instruction: 0xf080fab0
d0010630:	bd100940 	vldrlt.16	s0, [r0, #-128]	; 0xffffff80	; <UNPREDICTABLE>
d0010634:	e7fc2000 	ldrb	r2, [ip, r0]!

Disassembly of section .text.find_record.isra.0:

d0010638 <.text.find_record.isra.0>:
d0010638:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d001063c:	34c8f500 	strbcc	pc, [r8], #1280	; 0x500	; <UNPREDICTABLE>
d0010640:	4690460f 	ldrmi	r4, [r0], pc, lsl #12
d0010644:	34a82500 	strtcc	r2, [r8], #1280	; 0x500
d0010648:	36e5f500 	strbtcc	pc, [r5], r0, lsl #10	; <UNPREDICTABLE>
d001064c:	f983fa5f 			; <UNDEFINED> instruction: 0xf983fa5f
d0010650:	429d6eb3 	addsmi	r6, sp, #2864	; 0xb30
d0010654:	f04fd302 			; <UNDEFINED> instruction: 0xf04fd302
d0010658:	e00e30ff 	strd	r3, [lr], -pc	; <UNPREDICTABLE>
d001065c:	3264f894 	rsbcc	pc, r4, #148, 16	; 0x940000
d0010660:	4643b96b 	strbmi	fp, [r3], -fp, ror #18
d0010664:	e9d4463a 	ldmib	r4, {r1, r3, r4, r5, r9, sl, lr}^
d0010668:	f7ff0100 			; <UNDEFINED> instruction: 0xf7ff0100
d001066c:	b130ffd7 	teqlt	r0, r7	; <illegal shifter operand>	; <UNPREDICTABLE>
d0010670:	3263f894 	rsbcc	pc, r3, #148, 16	; 0x940000
d0010674:	d102454b 	tstle	r2, fp, asr #10
d0010678:	e8bd4628 	pop	{r3, r5, r9, sl, lr}
d001067c:	350183f8 	strcc	r8, [r1, #-1016]	; 0xfffffc08
d0010680:	741af504 	ldrvc	pc, [sl], #-1284	; 0xfffffafc
d0010684:	Address 0x00000000d0010684 is out of bounds.


Disassembly of section .text.records_equal:

d0010686 <.text.records_equal>:
d0010686:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d001068a:	3260f8d0 	rsbcc	pc, r0, #208, 16	; 0xd00000
d001068e:	f0234606 			; <UNDEFINED> instruction: 0xf0234606
d0010692:	f8d1427f 			; <UNDEFINED> instruction: 0xf8d1427f
d0010696:	f0233260 			; <UNDEFINED> instruction: 0xf0233260
d001069a:	429a437f 	addsmi	r4, sl, #-67108863	; 0xfc000001
d001069e:	2000d002 	andcs	sp, r0, r2
d00106a2:	83f8e8bd 	mvnshi	lr, #12386304	; 0xbd0000
d00106a6:	2263f890 	rsbcs	pc, r3, #144, 16	; 0x900000
d00106aa:	3263f891 	rsbcc	pc, r3, #9502720	; 0x910000
d00106ae:	d1f6429a 			; <UNDEFINED> instruction: 0xd1f6429a
d00106b2:	460c4605 	strmi	r4, [ip], -r5, lsl #12
d00106b6:	f8962700 			; <UNDEFINED> instruction: 0xf8962700
d00106ba:	429f3262 	addsmi	r3, pc, #536870918	; 0x20000006
d00106be:	2001d301 	andcs	sp, r1, r1, lsl #6
d00106c2:	6a63e7ee 	bvs	0xd190a682
d00106c6:	6a2246a9 	bvs	0xd08a2172
d00106ca:	6a6946a0 	bvs	0xd1a62152
d00106ce:	f7ff6a28 			; <UNDEFINED> instruction: 0xf7ff6a28
d00106d2:	2800ffa4 	stmdacs	r0, {r2, r5, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d00106d6:	f895d0e3 			; <UNDEFINED> instruction: 0xf895d0e3
d00106da:	f8942040 			; <UNDEFINED> instruction: 0xf8942040
d00106de:	429a3040 	addsmi	r3, sl, #64	; 0x40
d00106e2:	f895d1dd 			; <UNDEFINED> instruction: 0xf895d1dd
d00106e6:	f8942041 			; <UNDEFINED> instruction: 0xf8942041
d00106ea:	429a3041 	addsmi	r3, sl, #65	; 0x41
d00106ee:	f8b9d1d7 			; <UNDEFINED> instruction: 0xf8b9d1d7
d00106f2:	35242042 	strcc	r2, [r4, #-66]!	; 0xffffffbe
d00106f6:	3042f8b8 	strhcc	pc, [r2], #-136	; 0xffffff78	; <UNPREDICTABLE>
d00106fa:	429a3424 	addsmi	r3, sl, #36, 8	; 0x24000000
d00106fe:	3701d1cf 	strcc	sp, [r1, -pc, asr #3]
d0010702:	Address 0x00000000d0010702 is out of bounds.


Disassembly of section .text.find_local.isra.0:

d0010704 <.text.find_local.isra.0>:
d0010704:	3325f500 	msrcc	CPSR_sc, #0, 10
d0010708:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d001070c:	6114f8d3 			; <UNDEFINED> instruction: 0x6114f8d3
d0010710:	460f2530 			; <UNDEFINED> instruction: 0x460f2530
d0010714:	fb054690 	blx	0xd016215e
d0010718:	f5000006 			; <UNDEFINED> instruction: 0xf5000006
d001071c:	34e43422 	strbtcc	r3, [r4], #1058	; 0x422
d0010720:	f04fb916 			; <UNDEFINED> instruction: 0xf04fb916
d0010724:	e00a30ff 	strd	r3, [sl], -pc	; <UNPREDICTABLE>
d0010728:	46436861 	strbmi	r6, [r3], -r1, ror #16
d001072c:	f854463a 			; <UNDEFINED> instruction: 0xf854463a
d0010730:	3e010930 			; <UNDEFINED> instruction: 0x3e010930
d0010734:	ff72f7ff 			; <UNDEFINED> instruction: 0xff72f7ff
d0010738:	d0f12800 	rscsle	r2, r1, r0, lsl #16
d001073c:	e8bd4630 	pop	{r4, r5, r9, sl, lr}
d0010740:	Address 0x00000000d0010740 is out of bounds.


Disassembly of section .text.find_global.isra.0:

d0010742 <.text.find_global.isra.0>:
d0010742:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d0010746:	35baf500 	ldrcc	pc, [sl, #1280]!	; 0x500
d001074a:	460f4606 	strmi	r4, [pc], -r6, lsl #12
d001074e:	35a44690 	strcc	r4, [r4, #1680]!	; 0x690
d0010752:	f5002400 			; <UNDEFINED> instruction: 0xf5002400
d0010756:	f8d939c8 			; <UNDEFINED> instruction: 0xf8d939c8
d001075a:	429c30a4 	addsmi	r3, ip, #164	; 0xa4
d001075e:	f04fd302 			; <UNDEFINED> instruction: 0xf04fd302
d0010762:	e00c30ff 	strd	r3, [ip], -pc	; <UNPREDICTABLE>
d0010766:	2029f895 	mlacs	r9, r5, r8, pc	; <UNPREDICTABLE>
d001076a:	429a7a33 	addsmi	r7, sl, #208896	; 0x33000
d001076e:	4643d109 	strbmi	sp, [r3], -r9, lsl #2
d0010772:	e9d5463a 	ldmib	r5, {r1, r3, r4, r5, r9, sl, lr}^
d0010776:	f7ff0100 			; <UNDEFINED> instruction: 0xf7ff0100
d001077a:	b110ff50 	tstlt	r0, r0, asr pc	; <UNPREDICTABLE>
d001077e:	e8bd4620 	pop	{r5, r9, sl, lr}
d0010782:	340183f8 	strcc	r8, [r1], #-1016	; 0xfffffc08
d0010786:	e7e63538 			; <UNDEFINED> instruction: 0xe7e63538

Disassembly of section .text.find_alias.isra.0:

d001078a <.text.find_alias.isra.0>:
d001078a:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d001078e:	35e5f500 	strbcc	pc, [r5, #1280]!	; 0x500	; <UNPREDICTABLE>
d0010792:	460f4606 	strmi	r4, [pc], -r6, lsl #12
d0010796:	356c4690 	strbcc	r4, [ip, #-1680]!	; 0xfffff970
d001079a:	f5002400 			; <UNDEFINED> instruction: 0xf5002400
d001079e:	f8d939e9 			; <UNDEFINED> instruction: 0xf8d939e9
d00107a2:	429c316c 	addsmi	r3, ip, #108, 2
d00107a6:	f04fd302 			; <UNDEFINED> instruction: 0xf04fd302
d00107aa:	e00c30ff 	strd	r3, [ip], -pc	; <UNPREDICTABLE>
d00107ae:	2021f895 	mlacs	r1, r5, r8, pc	; <UNPREDICTABLE>
d00107b2:	429a7a33 	addsmi	r7, sl, #208896	; 0x33000
d00107b6:	4643d109 	strbmi	sp, [r3], -r9, lsl #2
d00107ba:	e9d5463a 	ldmib	r5, {r1, r3, r4, r5, r9, sl, lr}^
d00107be:	f7ff0100 			; <UNDEFINED> instruction: 0xf7ff0100
d00107c2:	b110ff2c 	tstlt	r0, ip, lsr #30	; <UNPREDICTABLE>
d00107c6:	e8bd4620 	pop	{r5, r9, sl, lr}
d00107ca:	340183f8 	strcc	r8, [r1], #-1016	; 0xfffffc08
d00107ce:	e7e63524 	strb	r3, [r6, r4, lsr #10]!

Disassembly of section .text.is_record_type:

d00107d2 <.text.is_record_type>:
d00107d2:	f46f6ac3 	vld1.64	{d22-d23}, [pc], r3
d00107d6:	189a728b 	ldmne	sl, {r0, r1, r3, r7, r9, ip, sp, lr}
d00107da:	b5102a01 	ldrlt	r2, [r0, #-2561]	; 0xfffff5ff
d00107de:	d8014604 	stmdale	r1, {r2, r9, sl, lr}
d00107e2:	bd102001 	ldclt	0, cr2, [r0, #-4]
d00107e6:	1201f240 	andne	pc, r1, #64, 4
d00107ea:	d10e4293 			; <UNDEFINED> instruction: 0xd10e4293
d00107ee:	698169c2 	stmibvs	r1, {r1, r6, r7, r8, fp, sp, lr}
d00107f2:	ffcaf7ff 			; <UNDEFINED> instruction: 0xffcaf7ff
d00107f6:	db081e03 	blle	0xd021800a
d00107fa:	fb002024 	blx	0xd0018894
d00107fe:	f5004003 			; <UNDEFINED> instruction: 0xf5004003
d0010802:	f89030e5 			; <UNDEFINED> instruction: 0xf89030e5
d0010806:	2bff308c 	blcs	0xcffdca3e
d001080a:	2000d1ea 	andcs	sp, r0, sl, ror #3
d001080e:	Address 0x00000000d001080e is out of bounds.


Disassembly of section .text.find_function.isra.0:

d0010810 <.text.find_function.isra.0>:
d0010810:	47f0e92d 	ldrbmi	lr, [r0, sp, lsr #18]!
d0010814:	3400f500 	strcc	pc, [r0], #-1280	; 0xfffffb00
d0010818:	46884606 	strmi	r4, [r8], r6, lsl #12
d001081c:	f5044691 			; <UNDEFINED> instruction: 0xf5044691
d0010820:	25007482 	strcs	r7, [r0, #-1154]	; 0xfffffb7e
d0010824:	37fff04f 	ldrbcc	pc, [pc, pc, asr #32]!	; <UNPREDICTABLE>
d0010828:	3a0ef500 	bcc	0xd03cdc30
d001082c:	3104f8da 	ldrdcc	pc, [r4, -sl]
d0010830:	d20f429d 	andle	r4, pc, #-805306359	; 0xd0000009
d0010834:	4642464b 	strbmi	r4, [r2], -fp, asr #12
d0010838:	0100e9d4 	ldrdeq	lr, [r0, -r4]
d001083c:	feeef7ff 	mcr2	7, 7, pc, cr14, cr15, {7}	; <UNPREDICTABLE>
d0010840:	f894b160 			; <UNDEFINED> instruction: 0xf894b160
d0010844:	b1433028 	cmplt	r3, r8, lsr #32
d0010848:	2029f894 	mlacs	r9, r4, r8, pc	; <UNPREDICTABLE>
d001084c:	429a7a33 	addsmi	r7, sl, #208896	; 0x33000
d0010850:	462fd104 	strtmi	sp, [pc], -r4, lsl #2
d0010854:	e8bd4638 	pop	{r3, r4, r5, r9, sl, lr}
d0010858:	462f87f0 			; <UNDEFINED> instruction: 0x462f87f0
d001085c:	34383501 	ldrtcc	r3, [r8], #-1281	; 0xfffffaff
d0010860:	Address 0x00000000d0010860 is out of bounds.


Disassembly of section .text.name_is.isra.0:

d0010862 <.text.name_is.isra.0>:
d0010862:	460db537 			; <UNDEFINED> instruction: 0x460db537
d0010866:	46104604 	ldrmi	r4, [r0], -r4, lsl #12
d001086a:	f0109201 			; <UNDEFINED> instruction: 0xf0109201
d001086e:	42a8f9d2 	adcmi	pc, r8, #3440640	; 0x348000
d0010872:	99014602 	stmdbls	r1, {r1, r9, sl, lr}
d0010876:	4620d107 	strtmi	sp, [r0], -r7, lsl #2
d001087a:	fdd1f00e 	ldc2l	0, cr15, [r1, #56]	; 0x38
d001087e:	f080fab0 			; <UNDEFINED> instruction: 0xf080fab0
d0010882:	b0030940 	andlt	r0, r3, r0, asr #18
d0010886:	2000bd30 	andcs	fp, r0, r0, lsr sp
d001088a:	Address 0x00000000d001088a is out of bounds.


Disassembly of section .text.find_api_call.isra.0:

d001088c <.text.find_api_call.isra.0>:
d001088c:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d0010890:	4550f500 	ldrbmi	pc, [r0, #-1280]	; 0xfffffb00	; <UNPREDICTABLE>
d0010894:	4450f500 	ldrbmi	pc, [r0], #-1280	; 0xfffffb00	; <UNPREDICTABLE>
d0010898:	4690460f 	ldrmi	r4, [r0], pc, lsl #12
d001089c:	26003524 	strcs	r3, [r0], -r4, lsr #10
d00108a0:	6823341c 	stmdavs	r3!, {r2, r3, r4, sl, ip, sp}
d00108a4:	d304429e 	movwle	r4, #17054	; 0x429e
d00108a8:	0900f04f 	stmdbeq	r0, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d00108ac:	e8bd4648 	pop	{r3, r6, r9, sl, lr}
d00108b0:	462a83f8 			; <UNDEFINED> instruction: 0x462a83f8
d00108b4:	46384641 	ldrtmi	r4, [r8], -r1, asr #12
d00108b8:	f7ff46a9 			; <UNDEFINED> instruction: 0xf7ff46a9
d00108bc:	3554ffd2 	ldrbcc	pc, [r4, #-4050]	; 0xfffff02e	; <UNPREDICTABLE>
d00108c0:	d1f32800 	mvnsle	r2, r0, lsl #16
d00108c4:	e7ec3601 	strb	r3, [ip, r1, lsl #12]!

Disassembly of section .text.find_api_constant.isra.0:

d00108c8 <.text.find_api_constant.isra.0>:
d00108c8:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d00108cc:	456af500 	strbmi	pc, [sl, #-1280]!	; 0xfffffb00	; <UNPREDICTABLE>
d00108d0:	4450f500 	ldrbmi	pc, [r0], #-1280	; 0xfffffb00	; <UNPREDICTABLE>
d00108d4:	4690460f 	ldrmi	r4, [r0], pc, lsl #12
d00108d8:	26003564 	strcs	r3, [r0], -r4, ror #10
d00108dc:	68233420 	stmdavs	r3!, {r5, sl, ip, sp}
d00108e0:	d304429e 	movwle	r4, #17054	; 0x429e
d00108e4:	0900f04f 	stmdbeq	r0, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d00108e8:	e8bd4648 	pop	{r3, r6, r9, sl, lr}
d00108ec:	462a83f8 			; <UNDEFINED> instruction: 0x462a83f8
d00108f0:	46384641 	ldrtmi	r4, [r8], -r1, asr #12
d00108f4:	f7ff46a9 			; <UNDEFINED> instruction: 0xf7ff46a9
d00108f8:	3524ffb4 	strcc	pc, [r4, #-4020]!	; 0xfffff04c
d00108fc:	d1f32800 	mvnsle	r2, r0, lsl #16
d0010900:	e7ec3601 	strb	r3, [ip, r1, lsl #12]!

Disassembly of section .text.pp_unary:

d0010918 <.text.pp_unary>:
d0010918:	e92d6ac3 	push	{r0, r1, r6, r7, r9, fp, sp, lr}
d001091c:	1c5a43f7 	mrrcne	3, 15, r4, sl, cr7
d0010920:	2a204604 	bcs	0xd0822138
d0010924:	d90962c2 	stmdble	r9, {r1, r6, r7, r9, sp, lr}
d0010928:	26002201 	strcs	r2, [r0], -r1, lsl #4
d001092c:	62c32700 	sbcvs	r2, r3, #0, 14
d0010930:	46306302 	ldrtmi	r6, [r0], -r2, lsl #6
d0010934:	b0034639 	andlt	r4, r3, r9, lsr r6
d0010938:	83f0e8bd 	mvnshi	lr, #12386304	; 0xbd0000
d001093c:	44794986 	ldrbtmi	r4, [r9], #-2438	; 0xfffff67a
d0010940:	fce4f7ff 	stc2l	7, cr15, [r4], #1020	; 0x3fc
d0010944:	4620b148 	strtmi	fp, [r0], -r8, asr #2
d0010948:	ffe6f7ff 			; <UNDEFINED> instruction: 0xffe6f7ff
d001094c:	0301ea50 	movweq	lr, #6736	; 0x1a50
d0010950:	2601bf0c 	strcs	fp, [r1], -ip, lsl #30
d0010954:	27002600 	strcs	r2, [r0, -r0, lsl #12]
d0010958:	4980e00a 	stmibmi	r0, {r1, r3, sp, lr, pc}
d001095c:	44794620 	ldrbtmi	r4, [r9], #-1568	; 0xfffff9e0
d0010960:	fcd4f7ff 	ldc2l	7, cr15, [r4], {255}	; 0xff
d0010964:	4620b140 	strtmi	fp, [r0], -r0, asr #2
d0010968:	ffd6f7ff 			; <UNDEFINED> instruction: 0xffd6f7ff
d001096c:	43cf43c6 	bicmi	r4, pc, #402653187	; 0x18000003
d0010970:	3b016ae3 	blcc	0xd006b504
d0010974:	e7dc62e3 	ldrb	r6, [ip, r3, ror #5]
d0010978:	46204979 			; <UNDEFINED> instruction: 0x46204979
d001097c:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d0010980:	b128fcc5 	smlawtlt	r8, r5, ip, pc	; <UNPREDICTABLE>
d0010984:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010988:	4606ffc7 	strmi	pc, [r6], -r7, asr #31
d001098c:	e7ef460f 	strb	r4, [pc, pc, lsl #12]!
d0010990:	46204974 			; <UNDEFINED> instruction: 0x46204974
d0010994:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d0010998:	b130fcb9 	teqlt	r0, r9	; <illegal shifter operand>	; <UNPREDICTABLE>
d001099c:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d00109a0:	4246ffbb 	submi	pc, r6, #748	; 0x2ec
d00109a4:	0741eb61 	strbeq	lr, [r1, -r1, ror #22]
d00109a8:	4620e7e2 	strtmi	lr, [r0], -r2, ror #15
d00109ac:	fc64f7ff 	stc2l	7, cr15, [r4], #-1020	; 0xfffffc04
d00109b0:	1c5a6ae3 	mrrcne	10, 14, r6, sl, cr3
d00109b4:	62e22a20 	rscvs	r2, r2, #32, 20	; 0x20000
d00109b8:	2201d904 	andcs	sp, r1, #4, 18	; 0x10000
d00109bc:	62e32600 	rscvs	r2, r3, #0, 12
d00109c0:	e7c86322 	strb	r6, [r8, r2, lsr #6]
d00109c4:	44794968 	ldrbtmi	r4, [r9], #-2408	; 0xfffff698
d00109c8:	fca0f7ff 	stc2	7, cr15, [r0], #1020	; 0x3fc
d00109cc:	4620b168 	strtmi	fp, [r0], -r8, ror #2
d00109d0:	fb3cf000 	blx	0xd0f4c9da
d00109d4:	4965460f 	stmdbmi	r5!, {r0, r1, r2, r3, r9, sl, lr}^
d00109d8:	44794606 	ldrbtmi	r4, [r9], #-1542	; 0xfffff9fa
d00109dc:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d00109e0:	bba0fc95 	bllt	0xce84fc3c
d00109e4:	63232301 			; <UNDEFINED> instruction: 0x63232301
d00109e8:	6a65e031 	bvs	0xd1988ab4
d00109ec:	8028f8d4 	ldrdhi	pc, [r8], -r4	; <UNPREDICTABLE>
d00109f0:	d2514545 	subsle	r4, r1, #289406976	; 0x11400000
d00109f4:	f1a07828 			; <UNDEFINED> instruction: 0xf1a07828
d00109f8:	2b090330 	blcs	0xd02516c0
d00109fc:	eba8d849 	bl	0xcea46b28
d0010a00:	2b020305 	blcs	0xd009161c
d0010a04:	2830dd27 	ldmdacs	r0!, {r0, r1, r2, r5, r8, sl, fp, ip, lr, pc}
d0010a08:	786bd12a 	stmdavc	fp!, {r1, r3, r5, r8, ip, lr, pc}^
d0010a0c:	03dff003 	bicseq	pc, pc, #3
d0010a10:	d1272b58 			; <UNDEFINED> instruction: 0xd1272b58
d0010a14:	21103502 	tstcs	r0, r2, lsl #10
d0010a18:	25006265 	strcs	r6, [r0, #-613]	; 0xfffffd9b
d0010a1c:	27002600 	strcs	r2, [r0, -r0, lsl #12]
d0010a20:	0901f04f 	stmdbeq	r1, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d0010a24:	45906a62 	ldrmi	r6, [r0, #2658]	; 0xa62
d0010a28:	8092f240 	addshi	pc, r2, r0, asr #4
d0010a2c:	f7ff7810 			; <UNDEFINED> instruction: 0xf7ff7810
d0010a30:	4281fcf7 	addmi	pc, r1, #63232	; 0xf700
d0010a34:	b91dd818 	ldmdblt	sp, {r3, r4, fp, ip, lr, pc}
d0010a38:	45902301 	ldrmi	r2, [r0, #769]	; 0x301
d0010a3c:	d9066323 	stmdble	r6, {r0, r1, r5, r8, r9, sp, lr}
d0010a40:	f0037813 			; <UNDEFINED> instruction: 0xf0037813
d0010a44:	2b5503df 	blcs	0xd15519c8
d0010a48:	3201d101 	andcc	sp, r1, #1073741824	; 0x40000000
d0010a4c:	6ae36262 	bvs	0xcf8e93dc
d0010a50:	62e33b01 	rscvs	r3, r3, #1024	; 0x400
d0010a54:	2830e78c 	ldmdacs	r0!, {r2, r3, r7, r8, r9, sl, sp, lr, pc}
d0010a58:	210abf14 	tstcs	sl, r4, lsl pc
d0010a5c:	e7dc2108 	ldrb	r2, [ip, r8, lsl #2]
d0010a60:	e7da210a 	ldrb	r2, [sl, sl, lsl #2]
d0010a64:	e7d82108 	ldrb	r2, [r8, r8, lsl #2]
d0010a68:	35011c53 	strcc	r1, [r1, #-3155]	; 0xfffff3ad
d0010a6c:	78106263 	ldmdavc	r0, {r0, r1, r5, r6, r9, sp, lr}
d0010a70:	fcd6f7ff 	ldc2l	7, cr15, [r6], {255}	; 0xff
d0010a74:	fbb343c3 	blx	0xcece198a
d0010a78:	42b3f3f1 	adcsmi	pc, r3, #-1006632957	; 0xc4000003
d0010a7c:	2306fba1 	movwcs	pc, #27553	; 0x6ba1	; <UNPREDICTABLE>
d0010a80:	f8c4bf38 			; <UNDEFINED> instruction: 0xf8c4bf38
d0010a84:	18169030 	ldmdane	r6, {r4, r5, ip, pc}
d0010a88:	3307fb01 	movwcc	pc, #31489	; 0x7b01	; <UNPREDICTABLE>
d0010a8c:	0700f143 	streq	pc, [r0, -r3, asr #2]
d0010a90:	f7ffe7c8 			; <UNDEFINED> instruction: 0xf7ffe7c8
d0010a94:	b930fc78 	ldmdblt	r0!, {r3, r4, r5, r6, sl, fp, ip, sp, lr, pc}
d0010a98:	63232301 			; <UNDEFINED> instruction: 0x63232301
d0010a9c:	27002600 	strcs	r2, [r0, -r0, lsl #12]
d0010aa0:	3201e7d5 	andcc	lr, r1, #55836672	; 0x3540000
d0010aa4:	6a626262 	bvs	0xd18a9434
d0010aa8:	d9084590 	stmdble	r8, {r4, r7, r8, sl, lr}
d0010aac:	46087811 			; <UNDEFINED> instruction: 0x46087811
d0010ab0:	fc69f7ff 	stc2l	7, cr15, [r9], #-1020	; 0xfffffc04
d0010ab4:	d1f42800 	mvnsle	r2, r0, lsl #16
d0010ab8:	29093930 	stmdbcs	r9, {r4, r5, r8, fp, ip, sp}
d0010abc:	1b52d9f1 	blne	0xd14c7288
d0010ac0:	d1362a07 	teqle	r6, r7, lsl #20
d0010ac4:	4628492a 	strtmi	r4, [r8], -sl, lsr #18
d0010ac8:	44799201 	ldrbtmi	r9, [r9], #-513	; 0xfffffdff
d0010acc:	fca8f00e 	stc2	0, cr15, [r8], #56	; 0x38
d0010ad0:	bb709a01 	bllt	0xd1c372dc
d0010ad4:	46204927 	strtmi	r4, [r0], -r7, lsr #18
d0010ad8:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d0010adc:	4680fc17 	pkhbtmi	pc, r0, r7, lsl #24	; <UNPREDICTABLE>
d0010ae0:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010ae4:	6a61fbc9 	bvs	0xd188fa10
d0010ae8:	42b16aa6 	adcsmi	r6, r1, #679936	; 0xa6000
d0010aec:	7808d003 	stmdavc	r8, {r0, r1, ip, lr, pc}
d0010af0:	fc49f7ff 	mcrr2	7, 15, pc, r9, cr15	; <UNPREDICTABLE>
d0010af4:	2301b908 	movwcs	fp, #6408	; 0x1908
d0010af8:	6a626323 	bvs	0xd18a978c
d0010afc:	d9074296 	stmdble	r7, {r1, r2, r4, r7, r9, lr}
d0010b00:	46287815 			; <UNDEFINED> instruction: 0x46287815
d0010b04:	fc3ff7ff 	ldc2	7, cr15, [pc], #-1020	; 0xd0010710
d0010b08:	3d30b980 			; <UNDEFINED> instruction: 0x3d30b980
d0010b0c:	d90d2d09 	stmdble	sp, {r0, r3, r8, sl, fp, sp}
d0010b10:	68201a52 	stmdavs	r0!, {r1, r4, r6, r9, fp, ip}
d0010b14:	fc15f7ff 	ldc2	7, cr15, [r5], {255}	; 0xff
d0010b18:	17c12700 	strbne	r2, [r1, r0, lsl #14]
d0010b1c:	0ff643ce 	svceq	0x00f643ce
d0010b20:	0f00f1b8 	svceq	0x0000f1b8
d0010b24:	4914d093 	ldmdbmi	r4, {r0, r1, r4, r7, ip, lr, pc}
d0010b28:	e7574479 			; <UNDEFINED> instruction: 0xe7574479
d0010b2c:	62623201 	rsbvs	r3, r2, #268435456	; 0x10000000
d0010b30:	4629e7e3 	strtmi	lr, [r9], -r3, ror #15
d0010b34:	f7ff6820 			; <UNDEFINED> instruction: 0xf7ff6820
d0010b38:	2800fc04 	stmdacs	r0, {r2, sl, fp, ip, sp, lr, pc}
d0010b3c:	6823dbae 	stmdavs	r3!, {r1, r2, r3, r5, r7, r8, r9, fp, ip, lr, pc}
d0010b40:	fb022248 	blx	0xd009946a
d0010b44:	f5003000 			; <UNDEFINED> instruction: 0xf5003000
d0010b48:	e9d0402b 	ldmib	r0, {r0, r1, r3, r5, lr}^
d0010b4c:	e77e6732 			; <UNDEFINED> instruction: 0xe77e6732
d0010b50:	f47f2d00 			; <UNDEFINED> instruction: 0xf47f2d00
d0010b54:	e76faf7c 			; <UNDEFINED> instruction: 0xe76faf7c
d0010b58:	ffffffc2 			; <UNDEFINED> instruction: 0xffffffc2
d0010b5c:	ffffffa4 			; <UNDEFINED> instruction: 0xffffffa4
d0010b60:	ffffff88 			; <UNDEFINED> instruction: 0xffffff88
d0010b64:	ffffff72 			; <UNDEFINED> instruction: 0xffffff72
d0010b68:	ffffff42 			; <UNDEFINED> instruction: 0xffffff42
d0010b6c:	ffffff30 			; <UNDEFINED> instruction: 0xffffff30
d0010b70:	fffffe42 			; <UNDEFINED> instruction: 0xfffffe42
d0010b74:	fffffe30 			; <UNDEFINED> instruction: 0xfffffe30
d0010b78:	fffffde2 			; <UNDEFINED> instruction: 0xfffffde2

Disassembly of section .text.pp_mul:

d0010b84 <.text.pp_mul>:
d0010b84:	4ff0e92d 	svcmi	0x00f0e92d
d0010b88:	8b02ed2d 	blhi	0xd00cc044
d0010b8c:	4606b089 	strmi	fp, [r6], -r9, lsl #1
d0010b90:	fec2f7ff 	mcr2	7, 6, pc, cr2, cr15, {7}	; <UNPREDICTABLE>
d0010b94:	46044b67 	strmi	r4, [r4], -r7, ror #22
d0010b98:	447b460d 	ldrbtmi	r4, [fp], #-1549	; 0xfffff9f3
d0010b9c:	3a10ee08 	bcc	0xd044c3c4
d0010ba0:	447b4b65 	ldrbtmi	r4, [fp], #-2917	; 0xfffff49b
d0010ba4:	3a90ee08 	bcc	0xce44c3cc
d0010ba8:	1a10ee18 	bne	0xd044c410
d0010bac:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0010bb0:	b178fbad 	cmnlt	r8, sp, lsr #23	; <UNPREDICTABLE>
d0010bb4:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0010bb8:	4361feaf 	msrmi	SPSR_c, #2800	; 0xaf0
d0010bbc:	3400fba4 	strcc	pc, [r0], #-2980	; 0xfffff45c
d0010bc0:	1105fb00 	tstne	r5, r0, lsl #22	; <UNPREDICTABLE>
d0010bc4:	3400e9cd 	strcc	lr, [r0], #-2509	; 0xfffff633
d0010bc8:	440b9b01 	strmi	r9, [fp], #-2817	; 0xfffff4ff
d0010bcc:	e9dd9301 	ldmib	sp, {r0, r8, r9, ip, pc}^
d0010bd0:	e7e94500 	strb	r4, [r9, r0, lsl #10]!
d0010bd4:	1a90ee18 	bne	0xce44c43c
d0010bd8:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0010bdc:	9006fb97 	mulls	r6, r7, fp
d0010be0:	4956b938 	ldmdbmi	r6, {r3, r4, r5, r8, fp, ip, sp, pc}^
d0010be4:	44794630 	ldrbtmi	r4, [r9], #-1584	; 0xfffff9d0
d0010be8:	fb90f7ff 	blx	0xce44ebee
d0010bec:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d0010bf0:	46308099 			; <UNDEFINED> instruction: 0x46308099
d0010bf4:	fe90f7ff 	mrc2	7, 4, pc, cr0, cr15, {7}
d0010bf8:	0100e9cd 	smlabteq	r0, sp, r9, lr
d0010bfc:	2300e9dd 	movwcs	lr, #2525	; 0x9dd
d0010c00:	d1094313 	tstle	r9, r3, lsl r3
d0010c04:	29006b71 	stmdbcs	r0, {r0, r4, r5, r6, r8, r9, fp, sp, lr}
d0010c08:	2301d0e1 	movwcs	sp, #4321	; 0x10e1
d0010c0c:	63332400 	teqvs	r3, #0, 8
d0010c10:	e9cd2300 	stmib	sp, {r8, r9, sp}^
d0010c14:	e7da3400 	ldrb	r3, [sl, r0, lsl #8]
d0010c18:	f1752c00 			; <UNDEFINED> instruction: 0xf1752c00
d0010c1c:	e9cd0300 	stmib	sp, {r8, r9}^
d0010c20:	da044502 	ble	0xd0122030
d0010c24:	eb654262 	bl	0xd19615b4
d0010c28:	e9cd0345 	stmib	sp, {r0, r2, r6, r8, r9}^
d0010c2c:	e9dd2302 	ldmib	sp, {r1, r8, r9, sp}^
d0010c30:	2a002300 	bcs	0xd0019838
d0010c34:	2304e9cd 	movwcs	lr, #18893	; 0x49cd
d0010c38:	0300f173 	movweq	pc, #371	; 0x173	; <UNPREDICTABLE>
d0010c3c:	e9ddda06 	ldmib	sp, {r1, r2, r9, fp, ip, lr, pc}^
d0010c40:	42522300 	subsmi	r2, r2, #0, 6
d0010c44:	0343eb63 	movteq	lr, #15203	; 0x3b63
d0010c48:	2304e9cd 	movwcs	lr, #18893	; 0x49cd
d0010c4c:	0a00f04f 	beq	0xd004cd90
d0010c50:	0b00f04f 	bleq	0xd004cd94
d0010c54:	f04f213f 			; <UNDEFINED> instruction: 0xf04f213f
d0010c58:	46570c01 	ldrbmi	r0, [r7], -r1, lsl #24
d0010c5c:	eb1a46d8 	bl	0xd06a27c4
d0010c60:	f1c1030a 			; <UNDEFINED> instruction: 0xf1c1030a
d0010c64:	f1a10920 			; <UNDEFINED> instruction: 0xf1a10920
d0010c68:	461a0e20 	ldrmi	r0, [sl], -r0, lsr #28
d0010c6c:	030beb4b 	movweq	lr, #47947	; 0xbb4b
d0010c70:	9b029307 	blls	0xd00b5894
d0010c74:	b01cf8dd 			; <UNDEFINED> instruction: 0xb01cf8dd
d0010c78:	f001fa23 			; <UNDEFINED> instruction: 0xf001fa23
d0010c7c:	fa039b03 	blx	0xd00f7890
d0010c80:	fa23f909 	blx	0xd090f0ac
d0010c84:	ea40fe0e 	b	0xd10504c4
d0010c88:	ea400009 	b	0xd1010cb4
d0010c8c:	f1a1000e 			; <UNDEFINED> instruction: 0xf1a1000e
d0010c90:	f0000e20 			; <UNDEFINED> instruction: 0xf0000e20
d0010c94:	ea400001 	b	0xd1010ca0
d0010c98:	f1c10a02 			; <UNDEFINED> instruction: 0xf1c10a02
d0010c9c:	e9dd0020 	ldmib	sp, {r5}^
d0010ca0:	459b2304 	ldrmi	r2, [fp, #772]	; 0x304
d0010ca4:	4592bf08 	ldrmi	fp, [r2, #3848]	; 0xf08
d0010ca8:	fa0cd313 	blx	0xd03458fc
d0010cac:	fa2cfe0e 	blx	0xd0b504ec
d0010cb0:	9b04f000 	blls	0xd014ccb8
d0010cb4:	0000ea4e 	andeq	lr, r0, lr, asr #20
d0010cb8:	fe01fa0c 	vseleq.f32	s30, s2, s24
d0010cbc:	0a03ebba 	beq	0xd010bbac
d0010cc0:	ea4e9b05 	b	0xd13b78dc
d0010cc4:	ea400e07 	b	0xd10144e8
d0010cc8:	eb6b0008 	bl	0xd1ad0cf0
d0010ccc:	46770b03 	ldrbtmi	r0, [r7], -r3, lsl #22
d0010cd0:	39014680 	stmdbcc	r1, {r7, r9, sl, lr}
d0010cd4:	9b06d2c3 	blls	0xd01c57e8
d0010cd8:	9b01b1c3 	blls	0xd007d3ec
d0010cdc:	0fdb0fea 	svceq	0x00db0fea
d0010ce0:	7fd5ebb3 	svcvc	0x00d5ebb3
d0010ce4:	f04fbf15 			; <UNDEFINED> instruction: 0xf04fbf15
d0010ce8:	f06f4100 			; <UNDEFINED> instruction: 0xf06f4100
d0010cec:	20004100 	andcs	r4, r0, r0, lsl #2
d0010cf0:	30fff04f 	rscscc	pc, pc, pc, asr #32
d0010cf4:	bf084541 	svclt	0x00084541
d0010cf8:	d38642b8 	orrle	r4, r6, #184, 4	; 0x8000000b
d0010cfc:	d002429a 	mulle	r2, sl, r2
d0010d00:	eb68427f 	bl	0xd1a21704
d0010d04:	e9cd0848 	stmib	sp, {r3, r6, fp}^
d0010d08:	e7607800 	strb	r7, [r0, -r0, lsl #16]!
d0010d0c:	f1752c00 			; <UNDEFINED> instruction: 0xf1752c00
d0010d10:	e9cd0300 	stmib	sp, {r8, r9}^
d0010d14:	f6bfab00 			; <UNDEFINED> instruction: 0xf6bfab00
d0010d18:	f1daaf5a 			; <UNDEFINED> instruction: 0xf1daaf5a
d0010d1c:	eb6b0300 	bl	0xd1ad1924
d0010d20:	e776044b 	ldrb	r0, [r6, -fp, asr #8]!
d0010d24:	46294620 	strtmi	r4, [r9], -r0, lsr #12
d0010d28:	ecbdb009 	ldc	0, cr11, [sp], #36	; 0x24
d0010d2c:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d0010d30:	bf008ff0 	svclt	0x00008ff0
d0010d34:	ffffffde 			; <UNDEFINED> instruction: 0xffffffde
d0010d38:	ffffffd8 			; <UNDEFINED> instruction: 0xffffffd8
d0010d3c:	ffffff96 			; <UNDEFINED> instruction: 0xffffff96

Disassembly of section .text.pp_add:

d0010d40 <.text.pp_add>:
d0010d40:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d0010d44:	46064f12 			; <UNDEFINED> instruction: 0x46064f12
d0010d48:	8048f8df 	ldrdhi	pc, [r8], #-143	; 0xffffff71
d0010d4c:	ff1af7ff 			; <UNDEFINED> instruction: 0xff1af7ff
d0010d50:	4604447f 			; <UNDEFINED> instruction: 0x4604447f
d0010d54:	44f8460d 	ldrbtmi	r4, [r8], #1549	; 0x60d
d0010d58:	46304639 			; <UNDEFINED> instruction: 0x46304639
d0010d5c:	fad6f7ff 	blx	0xcf5ced60
d0010d60:	4630b130 			; <UNDEFINED> instruction: 0x4630b130
d0010d64:	ff0ef7ff 			; <UNDEFINED> instruction: 0xff0ef7ff
d0010d68:	eb411824 	bl	0xd1056e00
d0010d6c:	e7f30505 	ldrb	r0, [r3, r5, lsl #10]!
d0010d70:	46304641 	ldrtmi	r4, [r0], -r1, asr #12
d0010d74:	facaf7ff 	blx	0xcf2ced78
d0010d78:	4630b130 			; <UNDEFINED> instruction: 0x4630b130
d0010d7c:	ff02f7ff 			; <UNDEFINED> instruction: 0xff02f7ff
d0010d80:	eb651a24 	bl	0xd1957618
d0010d84:	e7e70501 	strb	r0, [r7, r1, lsl #10]!
d0010d88:	46294620 	strtmi	r4, [r9], -r0, lsr #12
d0010d8c:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d0010d90:	fffffbb4 			; <UNDEFINED> instruction: 0xfffffbb4
d0010d94:	fffffbb0 			; <UNDEFINED> instruction: 0xfffffbb0

Disassembly of section .text.pp_shift:

d0010da0 <.text.pp_shift>:
d0010da0:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d0010da4:	805cf8df 	ldrsbhi	pc, [ip], #-143	; 0xffffff71	; <UNPREDICTABLE>
d0010da8:	f8df4604 			; <UNDEFINED> instruction: 0xf8df4604
d0010dac:	f7ff905c 			; <UNDEFINED> instruction: 0xf7ff905c
d0010db0:	44f8ffc7 	ldrbtmi	pc, [r8], #4039	; 0xfc7	; <UNPREDICTABLE>
d0010db4:	460e4605 	strmi	r4, [lr], -r5, lsl #12
d0010db8:	464144f9 			; <UNDEFINED> instruction: 0x464144f9
d0010dbc:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010dc0:	b160faa5 	msrlt	(UNDEF: 96), r5
d0010dc4:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010dc8:	2900ffbb 	stmdbcs	r0, {r0, r1, r3, r4, r5, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0010dcc:	2820bf08 	stmdacs	r0!, {r3, r8, r9, sl, fp, ip, sp, pc}
d0010dd0:	2301d302 	movwcs	sp, #4866	; 0x1302
d0010dd4:	e7f06323 	ldrb	r6, [r0, r3, lsr #6]!
d0010dd8:	26004085 	strcs	r4, [r0], -r5, lsl #1
d0010ddc:	4649e7ed 	strbmi	lr, [r9], -sp, ror #15
d0010de0:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010de4:	b140fa93 			; <UNDEFINED> instruction: 0xb140fa93
d0010de8:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010dec:	2900ffa9 	stmdbcs	r0, {r0, r3, r5, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0010df0:	2820bf08 	stmdacs	r0!, {r3, r8, r9, sl, fp, ip, sp, pc}
d0010df4:	40c5d2ed 	sbcmi	sp, r5, sp, ror #5
d0010df8:	4628e7ef 	strtmi	lr, [r8], -pc, ror #15
d0010dfc:	e8bd4631 	pop	{r0, r4, r5, r9, sl, lr}
d0010e00:	bf0083f8 	svclt	0x000083f8
d0010e04:	ffffffe2 			; <UNDEFINED> instruction: 0xffffffe2
d0010e08:	ffffffdf 			; <UNDEFINED> instruction: 0xffffffdf

Disassembly of section .text.pp_rel:

d0010e18 <.text.pp_rel>:
d0010e18:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d0010e1c:	46064f24 	strmi	r4, [r6], -r4, lsr #30
d0010e20:	8090f8df 			; <UNDEFINED> instruction: 0x8090f8df
d0010e24:	ffbcf7ff 			; <UNDEFINED> instruction: 0xffbcf7ff
d0010e28:	908cf8df 	ldrdls	pc, [ip], pc	; <UNPREDICTABLE>
d0010e2c:	460d4604 	strmi	r4, [sp], -r4, lsl #12
d0010e30:	44f8447f 	ldrbtmi	r4, [r8], #1151	; 0x47f
d0010e34:	463944f9 			; <UNDEFINED> instruction: 0x463944f9
d0010e38:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0010e3c:	b158fa67 	cmplt	r8, r7, ror #20	; <UNPREDICTABLE>
d0010e40:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0010e44:	42a0ffad 	adcmi	pc, r0, #692	; 0x2b4
d0010e48:	0305eb71 	movweq	lr, #23409	; 0x5b71
d0010e4c:	2401bfac 	strcs	fp, [r1], #-4012	; 0xfffff054
d0010e50:	b2e42400 	rsclt	r2, r4, #0, 8
d0010e54:	e7ee2500 	strb	r2, [lr, r0, lsl #10]!
d0010e58:	46304641 	ldrtmi	r4, [r0], -r1, asr #12
d0010e5c:	fa56f7ff 	blx	0xd15cee60
d0010e60:	4630b130 			; <UNDEFINED> instruction: 0x4630b130
d0010e64:	ff9cf7ff 			; <UNDEFINED> instruction: 0xff9cf7ff
d0010e68:	eb754284 	bl	0xd1d61880
d0010e6c:	e7ed0301 	strb	r0, [sp, r1, lsl #6]!
d0010e70:	46304649 	ldrtmi	r4, [r0], -r9, asr #12
d0010e74:	fa4af7ff 	blx	0xd12cee78
d0010e78:	4630b148 	ldrtmi	fp, [r0], -r8, asr #2
d0010e7c:	ff90f7ff 			; <UNDEFINED> instruction: 0xff90f7ff
d0010e80:	eb754284 	bl	0xd1d61898
d0010e84:	bfb40301 	svclt	0x00b40301
d0010e88:	24002401 	strcs	r2, [r0], #-1025	; 0xfffffbff
d0010e8c:	490be7e1 	stmdbmi	fp, {r0, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d0010e90:	44794630 	ldrbtmi	r4, [r9], #-1584	; 0xfffff9d0
d0010e94:	fa3af7ff 	blx	0xd0ecee98
d0010e98:	4630b130 			; <UNDEFINED> instruction: 0x4630b130
d0010e9c:	ff80f7ff 			; <UNDEFINED> instruction: 0xff80f7ff
d0010ea0:	eb7142a0 	bl	0xd1c61928
d0010ea4:	e7ee0305 	strb	r0, [lr, r5, lsl #6]!
d0010ea8:	46294620 	strtmi	r4, [r9], -r0, lsr #12
d0010eac:	83f8e8bd 	mvnshi	lr, #12386304	; 0xbd0000
d0010eb0:	ffffffd8 			; <UNDEFINED> instruction: 0xffffffd8
d0010eb4:	ffffffd9 			; <UNDEFINED> instruction: 0xffffffd9
d0010eb8:	ffffffda 			; <UNDEFINED> instruction: 0xffffffda
d0010ebc:	ffffff7e 			; <UNDEFINED> instruction: 0xffffff7e

Disassembly of section .text.pp_eq:

d0010ec8 <.text.pp_eq>:
d0010ec8:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d0010ecc:	46064f15 			; <UNDEFINED> instruction: 0x46064f15
d0010ed0:	8054f8df 	ldrsbhi	pc, [r4], #-143	; 0xffffff71	; <UNPREDICTABLE>
d0010ed4:	ffa0f7ff 			; <UNDEFINED> instruction: 0xffa0f7ff
d0010ed8:	4604447f 			; <UNDEFINED> instruction: 0x4604447f
d0010edc:	44f8460d 	ldrbtmi	r4, [r8], #1549	; 0x60d
d0010ee0:	46304639 			; <UNDEFINED> instruction: 0x46304639
d0010ee4:	fa12f7ff 	blx	0xd04ceee8
d0010ee8:	4630b150 			; <UNDEFINED> instruction: 0x4630b150
d0010eec:	ff94f7ff 			; <UNDEFINED> instruction: 0xff94f7ff
d0010ef0:	bf0642a9 	svclt	0x000642a9
d0010ef4:	240142a0 	strcs	r4, [r1], #-672	; 0xfffffd60
d0010ef8:	b2e42400 	rsclt	r2, r4, #0, 8
d0010efc:	e7ef2500 	strb	r2, [pc, r0, lsl #10]!
d0010f00:	46304641 	ldrtmi	r4, [r0], -r1, asr #12
d0010f04:	fa02f7ff 	blx	0xd00cef08
d0010f08:	4630b140 	ldrtmi	fp, [r0], -r0, asr #2
d0010f0c:	ff84f7ff 			; <UNDEFINED> instruction: 0xff84f7ff
d0010f10:	bf0a42a9 	svclt	0x000a42a9
d0010f14:	240142a0 	strcs	r4, [r1], #-672	; 0xfffffd60
d0010f18:	e7ee2400 	strb	r2, [lr, r0, lsl #8]!
d0010f1c:	46294620 	strtmi	r4, [r9], -r0, lsr #12
d0010f20:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d0010f24:	ffffffe4 			; <UNDEFINED> instruction: 0xffffffe4
d0010f28:	ffffffe1 			; <UNDEFINED> instruction: 0xffffffe1

Disassembly of section .text.pp_band:

d0010f2c <.text.pp_band>:
d0010f2c:	4604b570 			; <UNDEFINED> instruction: 0x4604b570
d0010f30:	ffcaf7ff 			; <UNDEFINED> instruction: 0xffcaf7ff
d0010f34:	460d4606 	strmi	r4, [sp], -r6, lsl #12
d0010f38:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010f3c:	6a63f99d 	bvs	0xd190f5b8
d0010f40:	428b6aa1 	addmi	r6, fp, #659456	; 0xa1000
d0010f44:	781ad20f 	ldmdavc	sl, {r0, r1, r2, r3, r9, ip, lr, pc}
d0010f48:	d10c2a26 	tstle	ip, r6, lsr #20
d0010f4c:	42911c5a 	addsmi	r1, r1, #23040	; 0x5a00
d0010f50:	785bd902 	ldmdavc	fp, {r1, r8, fp, ip, lr, pc}^
d0010f54:	d0062b26 	andle	r2, r6, r6, lsr #22
d0010f58:	62624620 	rsbvs	r4, r2, #32, 12	; 0x2000000
d0010f5c:	ffb4f7ff 			; <UNDEFINED> instruction: 0xffb4f7ff
d0010f60:	400d4006 	andmi	r4, sp, r6
d0010f64:	4630e7e8 	ldrtmi	lr, [r0], -r8, ror #15
d0010f68:	bd704629 	ldcllt	6, cr4, [r0, #-164]!	; 0xffffff5c

Disassembly of section .text.pp_xor:

d0010f70 <.text.pp_xor>:
d0010f70:	4f0ab5f8 	svcmi	0x000ab5f8
d0010f74:	f7ff4606 			; <UNDEFINED> instruction: 0xf7ff4606
d0010f78:	4605ffd9 			; <UNDEFINED> instruction: 0x4605ffd9
d0010f7c:	447f460c 	ldrbtmi	r4, [pc], #-1548	; 0xd0010f84
d0010f80:	46304639 			; <UNDEFINED> instruction: 0x46304639
d0010f84:	f9c2f7ff 			; <UNDEFINED> instruction: 0xf9c2f7ff
d0010f88:	4628b910 			; <UNDEFINED> instruction: 0x4628b910
d0010f8c:	bdf84621 	ldcllt	6, cr4, [r8, #132]!	; 0x84
d0010f90:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0010f94:	4045ffcb 	submi	pc, r5, fp, asr #31
d0010f98:	e7f1404c 	ldrb	r4, [r1, ip, asr #32]!
d0010f9c:	ffffffea 			; <UNDEFINED> instruction: 0xffffffea

Disassembly of section .text.pp_bor:

d0010fa0 <.text.pp_bor>:
d0010fa0:	4604b570 			; <UNDEFINED> instruction: 0x4604b570
d0010fa4:	ffe4f7ff 			; <UNDEFINED> instruction: 0xffe4f7ff
d0010fa8:	460d4606 	strmi	r4, [sp], -r6, lsl #12
d0010fac:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010fb0:	6a63f963 	bvs	0xd190f544
d0010fb4:	428b6aa1 	addmi	r6, fp, #659456	; 0xa1000
d0010fb8:	781ad20f 	ldmdavc	sl, {r0, r1, r2, r3, r9, ip, lr, pc}
d0010fbc:	d10c2a7c 	tstle	ip, ip, ror sl
d0010fc0:	42911c5a 	addsmi	r1, r1, #23040	; 0x5a00
d0010fc4:	785bd902 	ldmdavc	fp, {r1, r8, fp, ip, lr, pc}^
d0010fc8:	d0062b7c 	andle	r2, r6, ip, ror fp
d0010fcc:	62624620 	rsbvs	r4, r2, #32, 12	; 0x2000000
d0010fd0:	ffcef7ff 			; <UNDEFINED> instruction: 0xffcef7ff
d0010fd4:	430d4306 	movwmi	r4, #54022	; 0xd306
d0010fd8:	4630e7e8 	ldrtmi	lr, [r0], -r8, ror #15
d0010fdc:	bd704629 	ldcllt	6, cr4, [r0, #-164]!	; 0xffffff5c

Disassembly of section .text.pp_and:

d0010fe4 <.text.pp_and>:
d0010fe4:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d0010fe8:	46064f16 			; <UNDEFINED> instruction: 0x46064f16
d0010fec:	ffd8f7ff 			; <UNDEFINED> instruction: 0xffd8f7ff
d0010ff0:	460d4604 	strmi	r4, [sp], -r4, lsl #12
d0010ff4:	4639447f 			; <UNDEFINED> instruction: 0x4639447f
d0010ff8:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0010ffc:	b918f987 	ldmdblt	r8, {r0, r1, r2, r7, r8, fp, ip, sp, lr, pc}
d0011000:	46294620 	strtmi	r4, [r9], -r0, lsr #12
d0011004:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d0011008:	8034f8d6 	ldrsbthi	pc, [r4], -r6	; <UNPREDICTABLE>
d001100c:	0f00f1b8 	svceq	0x0000f1b8
d0011010:	ea54d014 	b	0xd1545068
d0011014:	bf140305 	svclt	0x00140305
d0011018:	23002301 	movwcs	r2, #769	; 0x301
d001101c:	46306373 			; <UNDEFINED> instruction: 0x46306373
d0011020:	ffbef7ff 			; <UNDEFINED> instruction: 0xffbef7ff
d0011024:	0305ea54 	movweq	lr, #23124	; 0x5a54
d0011028:	8034f8c6 	eorshi	pc, r4, r6, asr #17
d001102c:	ea50d008 	b	0xd1445054
d0011030:	bf140301 	svclt	0x00140301
d0011034:	24002401 	strcs	r2, [r0], #-1025	; 0xfffffbff
d0011038:	e7dc17e5 	ldrb	r1, [ip, r5, ror #15]
d001103c:	e7ed4643 	strb	r4, [sp, r3, asr #12]!
d0011040:	e7f92400 	ldrb	r2, [r9, r0, lsl #8]!
d0011044:	ffffffe8 			; <UNDEFINED> instruction: 0xffffffe8

Disassembly of section .text.pp_or:

d001104c <.text.pp_or>:
d001104c:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d0011050:	46064f15 			; <UNDEFINED> instruction: 0x46064f15
d0011054:	ffc6f7ff 			; <UNDEFINED> instruction: 0xffc6f7ff
d0011058:	460d4604 	strmi	r4, [sp], -r4, lsl #12
d001105c:	4639447f 			; <UNDEFINED> instruction: 0x4639447f
d0011060:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0011064:	b918f953 	ldmdblt	r8, {r0, r1, r4, r6, r8, fp, ip, sp, lr, pc}
d0011068:	46294620 	strtmi	r4, [r9], -r0, lsr #12
d001106c:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d0011070:	8034f8d6 	ldrsbthi	pc, [r4], -r6	; <UNPREDICTABLE>
d0011074:	0f00f1b8 	svceq	0x0000f1b8
d0011078:	ea54d014 	b	0xd15450d0
d001107c:	bf0c0305 	svclt	0x000c0305
d0011080:	23002301 	movwcs	r2, #769	; 0x301
d0011084:	46306373 			; <UNDEFINED> instruction: 0x46306373
d0011088:	ffacf7ff 			; <UNDEFINED> instruction: 0xffacf7ff
d001108c:	43294320 			; <UNDEFINED> instruction: 0x43294320
d0011090:	8034f8c6 	eorshi	pc, r4, r6, asr #17
d0011094:	ea502500 	b	0xd141a49c
d0011098:	bf140301 	svclt	0x00140301
d001109c:	24002401 	strcs	r2, [r0], #-1025	; 0xfffffbff
d00110a0:	e7dcb2e4 	ldrb	fp, [ip, r4, ror #5]
d00110a4:	e7ed4643 	strb	r4, [sp, r3, asr #12]!
d00110a8:	ffffffe8 			; <UNDEFINED> instruction: 0xffffffe8

Disassembly of section .text.pp_value:

d00110dc <.text.pp_value>:
d00110dc:	b5f0b084 	ldrblt	fp, [r0, #132]!	; 0x84
d00110e0:	4606b08f 	strmi	fp, [r6], -pc, lsl #1
d00110e4:	9000ac15 	andls	sl, r0, r5, lsl ip
d00110e8:	9f1ead01 	svcls	0x001ead01
d00110ec:	000ee884 	andeq	lr, lr, r4, lsl #17
d00110f0:	c50fcc0f 	strgt	ip, [pc, #-3087]	; 0xd00104e9
d00110f4:	000fe894 	muleq	pc, r4, r8	; <UNPREDICTABLE>
d00110f8:	000fe885 	andeq	lr, pc, r5, lsl #17
d00110fc:	466d9b1d 			; <UNDEFINED> instruction: 0x466d9b1d
d0011100:	970a2401 	strls	r2, [sl, -r1, lsl #8]
d0011104:	23009309 	movwcs	r9, #777	; 0x309
d0011108:	940d4628 	strls	r4, [sp], #-1576	; 0xfffff9d8
d001110c:	930c930b 	movwls	r9, #49931	; 0xc30b
d0011110:	ff9cf7ff 			; <UNDEFINED> instruction: 0xff9cf7ff
d0011114:	e9c39b1f 	stmib	r3, {r0, r1, r2, r3, r4, r8, r9, fp, ip, pc}^
d0011118:	46280100 	strtmi	r0, [r8], -r0, lsl #2
d001111c:	f8acf7ff 			; <UNDEFINED> instruction: 0xf8acf7ff
d0011120:	b9139b0c 	ldmdblt	r3, {r2, r3, r8, r9, fp, ip, pc}
d0011124:	42bb9b09 	adcsmi	r9, fp, #9216	; 0x2400
d0011128:	6db0d012 	ldcvs	0, cr13, [r0, #72]!	; 0x48
d001112c:	490ab990 	stmdbmi	sl, {r4, r7, r8, fp, ip, sp, pc}
d0011130:	206cf89d 	mlscs	ip, sp, r8, pc	; <UNPREDICTABLE>
d0011134:	65b14479 	ldrvs	r4, [r1, #1145]!	; 0x479
d0011138:	65f19918 	ldrbvs	r9, [r1, #2328]!	; 0x918
d001113c:	e9c69919 	stmib	r6, {r0, r3, r4, r8, fp, ip, pc}^
d0011140:	9a1c1218 	bls	0xd07159a8
d0011144:	b00f66b2 			; <UNDEFINED> instruction: 0xb00f66b2
d0011148:	40f0e8bd 	ldrhtmi	lr, [r0], #141	; 0x8d
d001114c:	4770b004 	ldrbmi	fp, [r0, -r4]!
d0011150:	e7f84620 	ldrb	r4, [r8, r0, lsr #12]!
d0011154:	e7f62000 	ldrb	r2, [r6, r0]!
d0011158:	ffffff74 			; <UNDEFINED> instruction: 0xffffff74

Disassembly of section .text.enter_header.isra.0:

d00112fc <.text.enter_header.isra.0>:
d00112fc:	4ff0e92d 	svcmi	0x00f0e92d
d0011300:	f5ad461e 			; <UNDEFINED> instruction: 0xf5ad461e
d0011304:	6ec37d0d 	cdpvs	13, 12, cr7, cr3, cr13, {0}
d0011308:	9d984604 	ldcls	6, cr4, [r8, #16]
d001130c:	92059104 	andls	r9, r5, #4, 2
d0011310:	6d85b993 	vstrvs.16	s22, [r5, #294]	; 0x126	; <UNPREDICTABLE>
d0011314:	2500b12d 	strcs	fp, [r0, #-301]	; 0xfffffed3
d0011318:	f50d4628 			; <UNDEFINED> instruction: 0xf50d4628
d001131c:	e8bd7d0d 	pop	{r0, r2, r3, r8, sl, fp, ip, sp, lr}
d0011320:	4bfa8ff0 	blmi	0xcfeb52e8
d0011324:	65a3447b 	strvs	r4, [r3, #1147]!	; 0x47b
d0011328:	65e39b04 	strbvs	r9, [r3, #2820]!	; 0xb04
d001132c:	e9c49b05 	stmib	r4, {r0, r2, r8, r9, fp, ip, pc}^
d0011330:	9b963618 	blls	0xce59eb98
d0011334:	e7ef66a3 	strb	r6, [pc, r3, lsr #13]!
d0011338:	2bfe1e6b 	blcs	0xcff98cec
d001133c:	6d85d905 	vstrvs.16	s26, [r5, #10]	; <UNPREDICTABLE>
d0011340:	d1e82d00 	mvnle	r2, r0, lsl #26
d0011344:	447b4bf2 	ldrbtmi	r4, [fp], #-3058	; 0xfffff40e
d0011348:	f10de7ed 			; <UNDEFINED> instruction: 0xf10de7ed
d001134c:	462a0930 			; <UNDEFINED> instruction: 0x462a0930
d0011350:	46489997 			; <UNDEFINED> instruction: 0x46489997
d0011354:	f854f00e 			; <UNDEFINED> instruction: 0xf854f00e
d0011358:	46482300 	strbmi	r2, [r8], -r0, lsl #6
d001135c:	3005f809 	andcc	pc, r5, r9, lsl #16
d0011360:	fc58f00f 	mrrc2	0, 0, pc, r8, cr15	; <UNPREDICTABLE>
d0011364:	d8052802 	stmdale	r5, {r1, fp, sp}
d0011368:	2d006da5 	stccs	13, cr6, [r0, #-660]	; 0xfffffd6c
d001136c:	4be9d1d3 	blmi	0xcfa85ac0
d0011370:	e7d8447b 			; <UNDEFINED> instruction: 0xe7d8447b
d0011374:	49e83802 	stmibmi	r8!, {r1, fp, ip, sp}^
d0011378:	44794448 	ldrbtmi	r4, [r9], #-1096	; 0xfffffbb8
d001137c:	fc56f00f 	mrrc2	0, 0, pc, r6, cr15	; <UNPREDICTABLE>
d0011380:	28004605 	stmdacs	r0, {r0, r2, r9, sl, lr}
d0011384:	ab0bd1f0 	blge	0xd0305b4c
d0011388:	7280f44f 	addvc	pc, r0, #1325400064	; 0x4f000000
d001138c:	7b98f50d 	blvc	0xce64e7c8
d0011390:	9202900b 	andls	r9, r2, #11
d0011394:	46024649 	strmi	r4, [r2], -r9, asr #12
d0011398:	e9cd6ee7 	stmib	sp, {r0, r1, r2, r5, r6, r7, r9, sl, fp, sp, lr}^
d001139c:	46033b00 	strmi	r3, [r3], -r0, lsl #22
d00113a0:	47b86f60 	ldrmi	r6, [r8, r0, ror #30]!
d00113a4:	f504b1e8 			; <UNDEFINED> instruction: 0xf504b1e8
d00113a8:	46a87700 	strtmi	r7, [r8], r0, lsl #14
d00113ac:	5a2ef504 	bpl	0xd0bce7c4
d00113b0:	3000f8da 	ldrdcc	pc, [r0], -sl
d00113b4:	d2064598 	andle	r4, r6, #152, 10	; 0x26000000
d00113b8:	46594638 			; <UNDEFINED> instruction: 0x46594638
d00113bc:	77a6f507 	strvc	pc, [r6, r7, lsl #10]!
d00113c0:	fc34f00f 	ldc2	0, cr15, [r4], #-60	; 0xffffffc4
d00113c4:	f8dab998 			; <UNDEFINED> instruction: 0xf8dab998
d00113c8:	45983000 	ldrmi	r3, [r8]
d00113cc:	8103f040 	tsthi	r3, r0, asr #32	; <UNPREDICTABLE>
d00113d0:	0f20f1b8 	svceq	0x0020f1b8
d00113d4:	6da3d10e 	stfvsd	f5, [r3, #56]!	; 0x38
d00113d8:	d19c2b00 	orrsle	r2, ip, r0, lsl #22
d00113dc:	447b4bcf 	ldrbtmi	r4, [fp], #-3023	; 0xfffff431
d00113e0:	6da3e7a1 	stcvs	7, cr14, [r3, #644]!	; 0x284
d00113e4:	d1962b00 	orrsle	r2, r6, r0, lsl #22
d00113e8:	447b4bcd 	ldrbtmi	r4, [fp], #-3021	; 0xfffff433
d00113ec:	f108e79b 			; <UNDEFINED> instruction: 0xf108e79b
d00113f0:	e7dd0801 	ldrb	r0, [sp, r1, lsl #16]
d00113f4:	3384f642 	orrcc	pc, r4, #69206016	; 0x4200000
d00113f8:	f5d258e2 			; <UNDEFINED> instruction: 0xf5d258e2
d00113fc:	d1054300 	mrsle	r4, SP_abt
d0011400:	2b006da3 	blcs	0xd002ca94
d0011404:	4bc7d187 	blmi	0xcf205a28
d0011408:	e78c447b 			; <UNDEFINED> instruction: 0xe78c447b
d001140c:	512ef504 	msrpl	CPSR_fsx, r4, lsl #10
d0011410:	7b98f50d 	blvc	0xce64e84c
d0011414:	31086f60 	tstcc	r8, r0, ror #30
d0011418:	f8cd6ee7 			; <UNDEFINED> instruction: 0xf8cd6ee7
d001141c:	9106b004 	tstls	r6, r4
d0011420:	7180f44f 	orrvc	pc, r0, pc, asr #8
d0011424:	91029307 	tstls	r2, r7, lsl #6
d0011428:	9109a90b 	tstls	r9, fp, lsl #18
d001142c:	99069100 	stmdbls	r6, {r8, ip, pc}
d0011430:	4649440a 	strbmi	r4, [r9], -sl, lsl #8
d0011434:	9b0747b8 	blls	0xd01e331c
d0011438:	6da5b930 			; <UNDEFINED> instruction: 0x6da5b930
d001143c:	f47f2d00 			; <UNDEFINED> instruction: 0xf47f2d00
d0011440:	4bb9af6a 	blmi	0xcee7d1f0
d0011444:	e76e447b 			; <UNDEFINED> instruction: 0xe76e447b
d0011448:	68129a09 	ldmdavs	r2, {r0, r3, r9, fp, ip, pc}
d001144c:	d2064293 	andle	r4, r6, #805306377	; 0x30000009
d0011450:	2b006da3 	blcs	0xd002cae4
d0011454:	af5ff47f 	svcge	0x005ff47f
d0011458:	447b4bb4 	ldrbtmi	r4, [fp], #-2996	; 0xfffff44c
d001145c:	f642e763 			; <UNDEFINED> instruction: 0xf642e763
d0011460:	21003384 	smlabbcs	r0, r4, r3, r3
d0011464:	9b0658e0 	blls	0xd01a77ec
d0011468:	f00f4418 			; <UNDEFINED> instruction: 0xf00f4418
d001146c:	4681fbbd 			; <UNDEFINED> instruction: 0x4681fbbd
d0011470:	d1ed2800 	mvnle	r2, r0, lsl #16
d0011474:	3000f8da 	ldrdcc	pc, [r0], -sl
d0011478:	70a6f44f 	adcvc	pc, r6, pc, asr #8
d001147c:	33019307 	movwcc	r9, #4871	; 0x1307
d0011480:	3000f8ca 	andcc	pc, r0, sl, asr #17
d0011484:	43439b07 	movtmi	r9, #15111	; 0x3b07
d0011488:	93084658 	movwls	r4, #34392	; 0x8658
d001148c:	7300f503 	movwvc	pc, #1283	; 0x503	; <UNPREDICTABLE>
d0011490:	0a03eb04 	beq	0xd010c0a8
d0011494:	fbbef00f 	blx	0xcefcd4da
d0011498:	1c424659 	mcrrne	6, 5, r4, r2, cr9
d001149c:	f00d4650 			; <UNDEFINED> instruction: 0xf00d4650
d00114a0:	f642ffaf 			; <UNDEFINED> instruction: 0xf642ffaf
d00114a4:	9b083284 	blls	0xd021debc
d00114a8:	9a0958a1 	bls	0xd0267734
d00114ac:	681218e3 	ldmdavs	r2, {r0, r1, r5, r6, r7, fp, ip}
d00114b0:	1300f8c3 	movwne	pc, #2243	; 0x8c3	; <UNPREDICTABLE>
d00114b4:	2304f8c3 	movwcs	pc, #18627	; 0x48c3	; <UNPREDICTABLE>
d00114b8:	9308f8c3 	movwls	pc, #35011	; 0x88c3	; <UNPREDICTABLE>
d00114bc:	440b9b06 	strmi	r9, [fp], #-2822	; 0xfffff4fa
d00114c0:	0902eb03 	stmdbeq	r2, {r0, r1, r8, r9, fp, sp, lr, pc}
d00114c4:	4a90469a 	bmi	0xce422f34
d00114c8:	d90945d1 	stmdble	r9, {r0, r4, r6, r7, r8, sl, lr}
d00114cc:	3000f89a 	mulcc	r0, sl, r8
d00114d0:	b2db3b09 	sbcslt	r3, fp, #9216	; 0x2400
d00114d4:	d8032b17 	stmdale	r3, {r0, r1, r2, r4, r8, r9, fp, sp}
d00114d8:	f303fa22 	vpmax.u8	d15, d3, d18
d00114dc:	d41607db 	ldrle	r0, [r6], #-2011	; 0xfffff825
d00114e0:	030aeba9 	movweq	lr, #43945	; 0xaba9
d00114e4:	dd292b01 	fstmdbxle	r9!, {d2-d1}	;@ Deprecated
d00114e8:	3000f89a 	mulcc	r0, sl, r8
d00114ec:	d1252b2f 			; <UNDEFINED> instruction: 0xd1252b2f
d00114f0:	3001f89a 	mulcc	r1, sl, r8
d00114f4:	d10d2b2f 	tstle	sp, pc, lsr #22
d00114f8:	0302f10a 	movweq	pc, #8458	; 0x210a	; <UNPREDICTABLE>
d00114fc:	469a4599 			; <UNDEFINED> instruction: 0x469a4599
d0011500:	f89ad9ee 			; <UNDEFINED> instruction: 0xf89ad9ee
d0011504:	33011000 	movwcc	r1, #4096	; 0x1000
d0011508:	d1f7290a 	mvnsle	r2, sl, lsl #18
d001150c:	f10ae7dc 			; <UNDEFINED> instruction: 0xf10ae7dc
d0011510:	e7d90a01 	ldrb	r0, [r9, r1, lsl #20]
d0011514:	d1112b2a 	tstle	r1, sl, lsr #22
d0011518:	0a02f10a 	beq	0xd00cd948
d001151c:	0301f10a 	movweq	pc, #4362	; 0x110a	; <UNPREDICTABLE>
d0011520:	d90b4599 	stmdble	fp, {r0, r3, r4, r7, r8, sl, lr}
d0011524:	1c01f813 	stcne	8, cr15, [r1], {19}
d0011528:	d105292a 	tstle	r5, sl, lsr #18
d001152c:	292f7819 	stmdbcs	pc!, {r0, r3, r4, fp, ip, sp, lr}	; <UNPREDICTABLE>
d0011530:	f10ad102 			; <UNDEFINED> instruction: 0xf10ad102
d0011534:	e7c70a02 	strb	r0, [r7, r2, lsl #20]
d0011538:	e7ef469a 			; <UNDEFINED> instruction: 0xe7ef469a
d001153c:	030aeba9 	movweq	lr, #43945	; 0xaba9
d0011540:	dd422b06 	vstrle	d18, [r2, #-24]	; 0xffffffe8
d0011544:	2207497a 	andcs	r4, r7, #1998848	; 0x1e8000
d0011548:	44794650 	ldrbtmi	r4, [r9], #-1616	; 0xfffff9b0
d001154c:	ff68f00d 			; <UNDEFINED> instruction: 0xff68f00d
d0011550:	f10abbd8 			; <UNDEFINED> instruction: 0xf10abbd8
d0011554:	45b90707 	ldrmi	r0, [r9, #1799]!	; 0x707
d0011558:	f89ad005 			; <UNDEFINED> instruction: 0xf89ad005
d001155c:	2b203007 	blcs	0xd081d580
d0011560:	2b09d001 	blcs	0xd028556c
d0011564:	45b9d131 	ldrmi	sp, [r9, #305]!	; 0x131
d0011568:	d9474639 	stmdble	r7, {r0, r3, r4, r5, r9, sl, lr}^
d001156c:	f813463b 			; <UNDEFINED> instruction: 0xf813463b
d0011570:	2a202b01 	bcs	0xd081c17c
d0011574:	2a09d040 	bcs	0xd028567c
d0011578:	463ad03e 			; <UNDEFINED> instruction: 0x463ad03e
d001157c:	f8923701 			; <UNDEFINED> instruction: 0xf8923701
d0011580:	4650a000 	ldrbmi	sl, [r0], -r0
d0011584:	fefff7fe 	mrc2	7, 7, pc, cr15, cr14, {7}
d0011588:	f1aab920 			; <UNDEFINED> instruction: 0xf1aab920
d001158c:	f1ba0a30 			; <UNDEFINED> instruction: 0xf1ba0a30
d0011590:	d8020f09 	stmdale	r2, {r0, r3, r8, r9, sl, fp}
d0011594:	463a45b9 			; <UNDEFINED> instruction: 0x463a45b9
d0011598:	1a57d8ef 	bne	0xd160795c
d001159c:	7808d015 	stmdavc	r8, {r0, r2, r4, ip, lr, pc}
d00115a0:	fef1f7fe 	mrc2	7, 7, pc, cr1, cr14, {7}
d00115a4:	2f3fb188 	svccs	0x003fb188
d00115a8:	9b08d80f 	blls	0xd02475ec
d00115ac:	f203463a 	vmin.s8	d4, d3, d26
d00115b0:	4420300b 	strtmi	r3, [r0], #-11
d00115b4:	ff24f00d 			; <UNDEFINED> instruction: 0xff24f00d
d00115b8:	f44f9b07 			; <UNDEFINED> instruction: 0xf44f9b07
d00115bc:	fb0272a6 	blx	0xd00ae05e
d00115c0:	23004203 	movwcs	r4, #515	; 0x203
d00115c4:	f882443a 			; <UNDEFINED> instruction: 0xf882443a
d00115c8:	f642330b 			; <UNDEFINED> instruction: 0xf642330b
d00115cc:	990b3284 	stmdbls	fp, {r2, r7, r9, ip, sp}
d00115d0:	440b58a3 	strmi	r5, [fp], #-2211	; 0xfffff75d
d00115d4:	7a2350a3 	bvc	0xd08e5868
d00115d8:	409f2701 	addsmi	r2, pc, r1, lsl #14
d00115dc:	73a6f44f 			; <UNDEFINED> instruction: 0x73a6f44f
d00115e0:	4308fb03 	movwmi	pc, #35587	; 0x8b03	; <UNPREDICTABLE>
d00115e4:	f893b2bf 			; <UNDEFINED> instruction: 0xf893b2bf
d00115e8:	b14a230a 	cmplt	sl, sl, lsl #6
d00115ec:	3308f8b3 	movwcc	pc, #34995	; 0x88b3	; <UNPREDICTABLE>
d00115f0:	d005421f 	andle	r4, r5, pc, lsl r2
d00115f4:	e68f2501 	str	r2, [pc], r1, lsl #10
d00115f8:	e7b4461f 			; <UNDEFINED> instruction: 0xe7b4461f
d00115fc:	e7cc463a 			; <UNDEFINED> instruction: 0xe7cc463a
d0011600:	31fcf8d4 	ldrsbcc	pc, [ip, #132]!	; 0x84	; <UNPREDICTABLE>
d0011604:	d1062b0c 	tstle	r6, ip, lsl #22
d0011608:	2b006da3 	blcs	0xd002cc9c
d001160c:	ae83f47f 	mcrge	4, 4, pc, cr3, cr15, {3}	; <UNPREDICTABLE>
d0011610:	447b4b48 	ldrbtmi	r4, [fp], #-2888	; 0xfffff4b8
d0011614:	f44fe687 	vst1.32	{d30-d32}, [pc], r7
d0011618:	fb0171a6 	blx	0xd006dcba
d001161c:	1863f108 	stmdane	r3!, {r3, r8, ip, sp, lr, pc}^
d0011620:	330bf893 	movwcc	pc, #47251	; 0xb893	; <UNPREDICTABLE>
d0011624:	6fa1b94b 	svcvs	0x00a1b94b
d0011628:	d1234541 			; <UNDEFINED> instruction: 0xd1234541
d001162c:	2b006da3 	blcs	0xd002ccc0
d0011630:	ae71f47f 	mrcge	4, 3, APSR_nzcv, cr1, cr15, {3}
d0011634:	447b4b40 	ldrbtmi	r4, [fp], #-2880	; 0xfffff4c0
d0011638:	f201e675 	vmin.s8	q7, <illegal reg q0.5>, <illegal reg q10.5>
d001163c:	f504310b 			; <UNDEFINED> instruction: 0xf504310b
d0011640:	f504492b 			; <UNDEFINED> instruction: 0xf504492b
d0011644:	f04f4b4f 			; <UNDEFINED> instruction: 0xf04f4b4f
d0011648:	44210a00 	strtmi	r0, [r1], #-2560	; 0xfffff600
d001164c:	0988f109 	stmibeq	r8, {r0, r3, r8, ip, sp, lr, pc}
d0011650:	0b88f10b 	bleq	0xce24da84
d0011654:	3000f8db 	ldrdcc	pc, [r0], -fp
d0011658:	d2e4459a 	rscle	r4, r4, #645922816	; 0x26800000
d001165c:	91064648 	tstls	r6, r8, asr #12
d0011660:	0948f109 	stmdbeq	r8, {r0, r3, r8, ip, sp, lr, pc}^
d0011664:	fae2f00f 	blx	0xcf8cd6a8
d0011668:	d0c32800 	sbcle	r2, r3, r0, lsl #16
d001166c:	0a01f10a 	beq	0xd008da9c
d0011670:	e7ef9906 	strb	r9, [pc, r6, lsl #18]!
d0011674:	01fcf8d4 	ldrsbeq	pc, [ip, #132]!	; 0x84	; <UNPREDICTABLE>
d0011678:	f1042200 			; <UNDEFINED> instruction: 0xf1042200
d001167c:	42820c94 	addmi	r0, r2, #148, 24	; 0x9400
d0011680:	1342ea4f 	movtne	lr, #10831	; 0x2a4f
d0011684:	3201d13a 	andcc	sp, r1, #-2147483634	; 0x8000000e
d0011688:	f8d468e5 			; <UNDEFINED> instruction: 0xf8d468e5
d001168c:	44239074 	strtmi	r9, [r3], #-116	; 0xffffff8c
d0011690:	21fcf8c4 	mvnscs	pc, r4, asr #17
d0011694:	020cf24d 	andeq	pc, ip, #-805306364	; 0xd0000004
d0011698:	e004f8d4 	ldrd	pc, [r4], -r4
d001169c:	c002f854 	andgt	pc, r2, r4, asr r8	; <UNPREDICTABLE>
d00116a0:	e9d46822 	ldmib	r4, {r1, r5, fp, sp, lr}^
d00116a4:	f8c36004 			; <UNDEFINED> instruction: 0xf8c36004
d00116a8:	25015088 	strcs	r5, [r1, #-136]	; 0xffffff78
d00116ac:	608cf8c3 	addvs	pc, ip, r3, asr #17
d00116b0:	f8c367da 			; <UNDEFINED> instruction: 0xf8c367da
d00116b4:	e9c3c098 	stmib	r3, {r3, r4, r7, lr, pc}^
d00116b8:	e9c30124 	stmib	r3, {r2, r5, r8}^
d00116bc:	f44f9e20 			; <UNDEFINED> instruction: 0xf44f9e20
d00116c0:	fb0373a6 	blx	0xd00ee562
d00116c4:	18e1f308 	stmiane	r1!, {r3, r8, r9, ip, sp, lr, pc}^
d00116c8:	7300f503 	movwvc	pc, #1283	; 0x503	; <UNPREDICTABLE>
d00116cc:	2308f8b1 	movwcs	pc, #34993	; 0x88b1	; <UNPREDICTABLE>
d00116d0:	f8d14423 			; <UNDEFINED> instruction: 0xf8d14423
d00116d4:	43170300 	tstmi	r7, #0, 6
d00116d8:	522ef504 	eorpl	pc, lr, #4, 10	; 0x1000000
d00116dc:	f8a13208 			; <UNDEFINED> instruction: 0xf8a13208
d00116e0:	44027308 	strmi	r7, [r2], #-776	; 0xfffffcf8
d00116e4:	f8d16022 			; <UNDEFINED> instruction: 0xf8d16022
d00116e8:	67632304 	strbvs	r2, [r3, -r4, lsl #6]!
d00116ec:	22006062 	andcs	r6, r0, #98	; 0x62
d00116f0:	8078f8c4 	rsbshi	pc, r8, r4, asr #17
d00116f4:	e9c460e2 	stmib	r4, {r1, r5, r6, r7, sp, lr}^
d00116f8:	e60d5504 	str	r5, [sp], -r4, lsl #10
d00116fc:	3003f85c 	andcc	pc, r3, ip, asr r8	; <UNPREDICTABLE>
d0011700:	d0934598 	umullsle	r4, r3, r8, r5
d0011704:	e7ba3201 	ldr	r3, [sl, r1, lsl #4]!
d0011708:	00800013 	addeq	r0, r0, r3, lsl r0
d001170c:	fffffe34 			; <UNDEFINED> instruction: 0xfffffe34
d0011710:	fffffe3f 			; <UNDEFINED> instruction: 0xfffffe3f
d0011714:	fffffe35 			; <UNDEFINED> instruction: 0xfffffe35
d0011718:	fffffe28 			; <UNDEFINED> instruction: 0xfffffe28
d001171c:	fffffe1b 			; <UNDEFINED> instruction: 0xfffffe1b
d0011720:	fffffde8 			; <UNDEFINED> instruction: 0xfffffde8
d0011724:	fffffe11 			; <UNDEFINED> instruction: 0xfffffe11
d0011728:	fffffdf9 			; <UNDEFINED> instruction: 0xfffffdf9
d001172c:	fffffe12 			; <UNDEFINED> instruction: 0xfffffe12
d0011730:	fffffd4f 			; <UNDEFINED> instruction: 0xfffffd4f
d0011734:	fffffc8f 			; <UNDEFINED> instruction: 0xfffffc8f
d0011738:	fffffc8b 			; <UNDEFINED> instruction: 0xfffffc8b

Disassembly of section .text.scan:

d00118d8 <.text.scan>:
d00118d8:	e92d6d8b 	push	{r0, r1, r3, r7, r8, sl, fp, sp, lr}
d00118dc:	46064ff0 			; <UNDEFINED> instruction: 0x46064ff0
d00118e0:	460cb09d 			; <UNDEFINED> instruction: 0x460cb09d
d00118e4:	f501bba3 			; <UNDEFINED> instruction: 0xf501bba3
d00118e8:	f1084850 			; <UNDEFINED> instruction: 0xf1084850
d00118ec:	4620080c 	strtmi	r0, [r0], -ip, lsl #16
d00118f0:	fcb2f7fe 	ldc2	7, cr15, [r2], #1016	; 0x3f8
d00118f4:	d14f2800 	cmple	pc, r0, lsl #16
d00118f8:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d00118fc:	fc62f7fe 	stc2l	7, cr15, [r2], #-1016	; 0xfffffc08
d0011900:	d0282820 	eorle	r2, r8, r0, lsr #16
d0011904:	d0262809 	eorle	r2, r6, r9, lsl #16
d0011908:	68e22823 	stmiavs	r2!, {r0, r1, r5, fp, sp}^
d001190c:	d1366863 	teqle	r6, r3, ror #16
d0011910:	d241429a 	suble	r4, r1, #-1610612727	; 0xa0000009
d0011914:	0930f10d 	ldmdbeq	r0!, {r0, r2, r3, r8, ip, sp, lr, pc}
d0011918:	466f4621 	strbtmi	r4, [pc], -r1, lsr #12
d001191c:	4648ad14 			; <UNDEFINED> instruction: 0x4648ad14
d0011920:	fc78f7fe 	ldc2l	7, cr15, [r8], #-1016	; 0xfffffc08
d0011924:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011928:	f10dfc56 			; <UNDEFINED> instruction: 0xf10dfc56
d001192c:	e8bc0c38 	ldm	ip!, {r3, r4, r5, sl, fp}
d0011930:	c70f000f 	strgt	r0, [pc, -pc]
d0011934:	0003e89c 	muleq	r3, ip, r8
d0011938:	0003e887 	andeq	lr, r3, r7, lsl #17
d001193c:	46284621 	strtmi	r4, [r8], -r1, lsr #12
d0011940:	000ce899 	muleq	ip, r9, r8
d0011944:	fd2af000 	stc2	0, cr15, [sl, #-0]
d0011948:	b1436da3 	smlaltblt	r6, r3, r3, sp
d001194c:	46304621 	ldrtmi	r4, [r0], -r1, lsr #12
d0011950:	fc60f7fe 	stc2l	7, cr15, [r0], #-1016	; 0xfffffc08
d0011954:	4620e00f 	strtmi	lr, [r0], -pc
d0011958:	fc3df7fe 	ldc2	7, cr15, [sp], #-1016	; 0xfffffc08
d001195c:	9b19e7cc 	blls	0xd068b894
d0011960:	7f97f5b3 	svcvc	0x0097f5b3
d0011964:	462cd0c3 	strtmi	sp, [ip], -r3, asr #1
d0011968:	cc0f4637 	stcgt	6, cr4, [pc], {55}	; 0x37
d001196c:	e894c70f 	ldm	r4, {r0, r1, r2, r3, r8, r9, sl, lr, pc}
d0011970:	e887000f 	stm	r7, {r0, r1, r2, r3}
d0011974:	4630000f 	ldrtmi	r0, [r0], -pc
d0011978:	e8bdb01d 	pop	{r0, r2, r3, r4, ip, sp, pc}
d001197c:	429a8ff0 	addsmi	r8, sl, #240, 30	; 0x3c0
d0011980:	4620d20a 	strtmi	sp, [r0], -sl, lsl #4
d0011984:	fc85f7fe 	stc2	7, cr15, [r5], {254}	; 0xfe
d0011988:	686368e2 	stmdavs	r3!, {r1, r5, r6, r7, fp, sp, lr}^
d001198c:	d2ae429a 	adcle	r4, lr, #-1610612727	; 0xa0000009
d0011990:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011994:	e7aafc20 	str	pc, [sl, r0, lsr #24]!
d0011998:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d001199c:	fc12f7fe 	ldc2	7, cr15, [r2], {254}	; 0xfe
d00119a0:	d0f52820 	rscsle	r2, r5, r0, lsr #16
d00119a4:	0309f1a0 	movweq	pc, #37280	; 0x91a0	; <UNPREDICTABLE>
d00119a8:	d9f12b04 	ldmible	r1!, {r2, r8, r9, fp, sp}^
d00119ac:	d170282f 	cmnle	r0, pc, lsr #16
d00119b0:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d00119b4:	fc06f7fe 	stc2	7, cr15, [r6], {254}	; 0xfe
d00119b8:	d10f282f 	tstle	pc, pc, lsr #16
d00119bc:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d00119c0:	fc00f7fe 	stc2	7, cr15, [r0], {254}	; 0xfe
d00119c4:	686368e2 	stmdavs	r3!, {r1, r5, r6, r7, fp, sp, lr}^
d00119c8:	d090429a 	umullsle	r4, r0, sl, r2
d00119cc:	d08e280a 	addle	r2, lr, sl, lsl #16
d00119d0:	d08c280d 	addle	r2, ip, sp, lsl #16
d00119d4:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d00119d8:	e7effbfe 			; <UNDEFINED> instruction: 0xe7effbfe
d00119dc:	d158282a 	cmple	r8, sl, lsr #16
d00119e0:	4621a814 			; <UNDEFINED> instruction: 0x4621a814
d00119e4:	fc16f7fe 	ldc2	7, cr15, [r6], {254}	; 0xfe
d00119e8:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d00119ec:	4620fbf4 			; <UNDEFINED> instruction: 0x4620fbf4
d00119f0:	fbf1f7fe 	blx	0xcfc8f9f2
d00119f4:	686368e2 	stmdavs	r3!, {r1, r5, r6, r7, fp, sp, lr}^
d00119f8:	f000429a 			; <UNDEFINED> instruction: 0xf000429a
d00119fc:	210082c0 	smlabtcs	r0, r0, r2, r8
d0011a00:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011a04:	282afbdf 	stmdacs	sl!, {r0, r1, r2, r3, r4, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d0011a08:	2101d1f1 	strdcs	sp, [r1, -r1]
d0011a0c:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011a10:	282ffbd9 	stmdacs	pc!, {r0, r3, r4, r6, r7, r8, r9, fp, ip, sp, lr, pc}	; <UNPREDICTABLE>
d0011a14:	4620d1eb 	strtmi	sp, [r0], -fp, ror #3
d0011a18:	fbddf7fe 	blx	0xcf78fa1a
d0011a1c:	3b01e7b8 	blcc	0xd008b904
d0011a20:	0000f8d8 	ldrdeq	pc, [r0], -r8
d0011a24:	1143eb04 	cmpne	r3, r4, lsl #22
d0011a28:	f8d1015a 			; <UNDEFINED> instruction: 0xf8d1015a
d0011a2c:	42881098 	addmi	r1, r8, #152	; 0x98
d0011a30:	f8dfd006 			; <UNDEFINED> instruction: 0xf8dfd006
d0011a34:	447915e4 	ldrbtmi	r1, [r9], #-1508	; 0xfffffa1c
d0011a38:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011a3c:	e785fbb5 			; <UNDEFINED> instruction: 0xe785fbb5
d0011a40:	f8c4327c 			; <UNDEFINED> instruction: 0xf8c4327c
d0011a44:	18a331fc 	stmiane	r3!, {r2, r3, r4, r5, r6, r7, r8, ip, sp}
d0011a48:	c002f854 	andgt	pc, r2, r4, asr r8	; <UNPREDICTABLE>
d0011a4c:	000cf103 	andeq	pc, ip, r3, lsl #2
d0011a50:	689d685f 	ldmvs	sp, {r0, r1, r2, r3, r4, r6, fp, sp, lr}
d0011a54:	e9c4c80f 	stmib	r4, {r0, r1, r2, r3, fp, lr, pc}^
d0011a58:	22011204 	andcs	r1, r1, #4, 4	; 0x40000000
d0011a5c:	c000f8c4 	andgt	pc, r0, r4, asr #17
d0011a60:	60656767 	rsbvs	r6, r5, r7, ror #14
d0011a64:	67a360e0 	strvs	r6, [r3, r0, ror #1]!
d0011a68:	686368e1 	stmdavs	r3!, {r0, r5, r6, r7, fp, sp, lr}^
d0011a6c:	f0404299 			; <UNDEFINED> instruction: 0xf0404299
d0011a70:	f8d48297 			; <UNDEFINED> instruction: 0xf8d48297
d0011a74:	2b0031fc 	blcs	0xd001e26c
d0011a78:	2a00d1d1 	bcs	0xd00461c4
d0011a7c:	af37f47f 	svcge	0x0037f47f
d0011a80:	3000f8d8 	ldrdcc	pc, [r0], -r8
d0011a84:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d0011a88:	f8df828e 			; <UNDEFINED> instruction: 0xf8df828e
d0011a8c:	44791590 	ldrbtmi	r1, [r9], #-1424	; 0xfffffa70
d0011a90:	2200e7d2 	andcs	lr, r0, #55050240	; 0x3480000
d0011a94:	4620e7e8 	strtmi	lr, [r0], -r8, ror #15
d0011a98:	fb9df7fe 	blx	0xce78fa9a
d0011a9c:	46812823 	strmi	r2, [r1], r3, lsr #16
d0011aa0:	f10dd123 			; <UNDEFINED> instruction: 0xf10dd123
d0011aa4:	46ec0e38 			; <UNDEFINED> instruction: 0x46ec0e38
d0011aa8:	e8beaf14 	ldm	lr!, {r2, r4, r8, r9, sl, fp, sp, pc}
d0011aac:	e8ac000f 	stmia	ip!, {r0, r1, r2, r3}
d0011ab0:	e89e000f 	ldm	lr, {r0, r1, r2, r3}
d0011ab4:	e88c0003 	stm	ip, {r0, r1}
d0011ab8:	46210003 	strtmi	r0, [r1], -r3
d0011abc:	e8954638 	ldm	r5, {r3, r4, r5, r9, sl, lr}
d0011ac0:	f000000c 			; <UNDEFINED> instruction: 0xf000000c
d0011ac4:	6da3fc6b 	stcvs	12, cr15, [r3, #428]!	; 0x1ac
d0011ac8:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0011acc:	9b19af3f 	blls	0xd067d7d0
d0011ad0:	7f97f5b3 	svcvc	0x0097f5b3
d0011ad4:	af0bf43f 	svcge	0x000bf43f
d0011ad8:	4635463c 			; <UNDEFINED> instruction: 0x4635463c
d0011adc:	c50fcc0f 	strgt	ip, [pc, #-3087]	; 0xd0010ed5
d0011ae0:	000fe894 	muleq	pc, r4, r8	; <UNPREDICTABLE>
d0011ae4:	000fe885 	andeq	lr, pc, r5, lsl #17
d0011ae8:	f7fee745 			; <UNDEFINED> instruction: 0xf7fee745
d0011aec:	4601fc4c 	strmi	pc, [r1], -ip, asr #24
d0011af0:	d1402800 	cmple	r0, r0, lsl #16
d0011af4:	0830f1a9 	ldmdaeq	r0!, {r0, r3, r5, r7, r8, ip, sp, lr, pc}
d0011af8:	0f09f1b8 	svceq	0x0009f1b8
d0011afc:	8111f200 	tsthi	r1, r0, lsl #4	; <UNPREDICTABLE>
d0011b00:	0f30f1b9 	svceq	0x0030f1b9
d0011b04:	8266f000 	rsbhi	pc, r6, #0
d0011b08:	2100270a 	tstcs	r0, sl, lsl #14
d0011b0c:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011b10:	4681fb59 	pkhtbmi	pc, r1, r9, asr #22	; <UNPREDICTABLE>
d0011b14:	fc84f7fe 	stc2	7, cr15, [r4], {254}	; 0xfe
d0011b18:	f2004287 	vhsub.s8	d4, d16, d7
d0011b1c:	f04980db 			; <UNDEFINED> instruction: 0xf04980db
d0011b20:	f1b90920 			; <UNDEFINED> instruction: 0xf1b90920
d0011b24:	d1020f75 	tstle	r2, r5, ror pc
d0011b28:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011b2c:	2100fb54 	tstcs	r0, r4, asr fp	; <UNPREDICTABLE>
d0011b30:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011b34:	f1a0fb47 			; <UNDEFINED> instruction: 0xf1a0fb47
d0011b38:	46020330 			; <UNDEFINED> instruction: 0x46020330
d0011b3c:	d90f2b09 	stmdble	pc, {r0, r3, r8, r9, fp, sp}	; <UNPREDICTABLE>
d0011b40:	fc21f7fe 	stc2	7, cr15, [r1], #-1016	; 0xfffffc08
d0011b44:	2a2eb960 	bcs	0xd0bc00cc
d0011b48:	f1b9d00a 			; <UNDEFINED> instruction: 0xf1b9d00a
d0011b4c:	f0000f75 			; <UNDEFINED> instruction: 0xf0000f75
d0011b50:	2f0a80e2 	svccs	0x000a80e2
d0011b54:	80d4f040 	sbcshi	pc, r4, r0, asr #32
d0011b58:	0f00f1b8 	svceq	0x0000f1b8
d0011b5c:	80def280 	sbcshi	pc, lr, r0, lsl #5
d0011b60:	2b006da3 	blcs	0xd002d1f4
d0011b64:	aef2f47f 	mrcge	4, 7, APSR_nzcv, cr2, cr15, {3}
d0011b68:	34b4f8df 	ldrtcc	pc, [r4], #2271	; 0x8df	; <UNPREDICTABLE>
d0011b6c:	e041447b 	sub	r4, r1, fp, ror r4
d0011b70:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011b74:	2100fb30 	tstcs	r0, r0, lsr fp	; <UNPREDICTABLE>
d0011b78:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011b7c:	4602fb23 	strmi	pc, [r2], -r3, lsr #22
d0011b80:	fc01f7fe 	stc2	7, cr15, [r1], {254}	; 0xfe
d0011b84:	d1f32800 	mvnsle	r2, r0, lsl #16
d0011b88:	2a093a30 	bcs	0xd0260450
d0011b8c:	6825d9f0 	stmdavs	r5!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
d0011b90:	68e34680 	stmiavs	r3!, {r7, r9, sl, lr}^
d0011b94:	948cf8df 	strls	pc, [ip], #2271	; 0x8df
d0011b98:	44f9441d 	ldrbtmi	r4, [r9], #1053	; 0x41d
d0011b9c:	f8591bed 			; <UNDEFINED> instruction: 0xf8591bed
d0011ba0:	46292b04 	strtmi	r2, [r9], -r4, lsl #22
d0011ba4:	f7fe4638 			; <UNDEFINED> instruction: 0xf7fe4638
d0011ba8:	b160fe5c 	msrlt	(UNDEF: 96), ip
d0011bac:	1007f208 	andne	pc, r7, r8, lsl #4
d0011bb0:	9011950d 	andsls	r9, r1, sp, lsl #10
d0011bb4:	ad0c4634 	stcge	6, cr4, [ip, #-208]	; 0xffffff30
d0011bb8:	c40fcd0f 	strgt	ip, [pc], #-3343	; 0xd0011bc0
d0011bbc:	000fe895 	muleq	pc, r5, r8	; <UNPREDICTABLE>
d0011bc0:	000fe884 	andeq	lr, pc, r4, lsl #17
d0011bc4:	f108e6d7 			; <UNDEFINED> instruction: 0xf108e6d7
d0011bc8:	f1b80801 			; <UNDEFINED> instruction: 0xf1b80801
d0011bcc:	d1e60f15 	mvnle	r0, r5, lsl pc
d0011bd0:	9454f8df 	ldrbls	pc, [r4], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d0011bd4:	44f94680 	ldrbtmi	r4, [r9], #1664	; 0x680
d0011bd8:	2b04f859 	blcs	0xd014fd44
d0011bdc:	46384629 	ldrtmi	r4, [r8], -r9, lsr #12
d0011be0:	fe3ff7fe 	mrc2	7, 1, pc, cr15, cr14, {7}
d0011be4:	6da3b168 	stfvsd	f3, [r3, #416]!	; 0x1a0
d0011be8:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0011bec:	f8dfaeaf 			; <UNDEFINED> instruction: 0xf8dfaeaf
d0011bf0:	447b343c 	ldrbtmi	r3, [fp], #-1084	; 0xfffffbc4
d0011bf4:	9b0665a3 	blls	0xd01ab288
d0011bf8:	ba18e9c4 	blt	0xd064c310
d0011bfc:	9b0765e3 	blls	0xd01eb390
d0011c00:	f108e1cc 			; <UNDEFINED> instruction: 0xf108e1cc
d0011c04:	f1b80801 			; <UNDEFINED> instruction: 0xf1b80801
d0011c08:	d1e50f17 	mvnle	r0, r7, lsl pc
d0011c0c:	4639462a 	ldrtmi	r4, [r9], -sl, lsr #12
d0011c10:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011c14:	2800fb51 	stmdacs	r0, {r0, r4, r6, r8, r9, fp, ip, sp, lr, pc}
d0011c18:	2128db0c 			; <UNDEFINED> instruction: 0x2128db0c
d0011c1c:	fb01950d 	blx	0xd007705a
d0011c20:	f5044400 			; <UNDEFINED> instruction: 0xf5044400
d0011c24:	f8d434e9 			; <UNDEFINED> instruction: 0xf8d434e9
d0011c28:	930e3190 	movwls	r3, #57744	; 0xe190
d0011c2c:	7381f44f 	orrvc	pc, r1, #1325400064	; 0x4f000000
d0011c30:	e7bf9311 			; <UNDEFINED> instruction: 0xe7bf9311
d0011c34:	4639462a 	ldrtmi	r4, [r9], -sl, lsr #12
d0011c38:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011c3c:	2800fb82 	stmdacs	r0, {r1, r7, r8, r9, fp, ip, sp, lr, pc}
d0011c40:	2348db2a 	movtcs	sp, #35626	; 0x8b2a
d0011c44:	4000fb03 	andmi	pc, r0, r3, lsl #22
d0011c48:	402bf500 	eormi	pc, fp, r0, lsl #10
d0011c4c:	e9d030c8 	ldmib	r0, {r3, r6, r7, ip, sp}^
d0011c50:	f1100100 			; <UNDEFINED> instruction: 0xf1100100
d0011c54:	93084300 	movwls	r4, #33536	; 0x8300
d0011c58:	0300f141 	movweq	pc, #321	; 0x141	; <UNPREDICTABLE>
d0011c5c:	e9dd9309 	ldmib	sp, {r0, r3, r8, r9, ip, pc}^
d0011c60:	2b012308 	blcs	0xd005a888
d0011c64:	f1b2bf08 			; <UNDEFINED> instruction: 0xf1b2bf08
d0011c68:	d3064f00 	movwle	r4, #28416	; 0x6f00
d0011c6c:	2b006da3 	blcs	0xd002d300
d0011c70:	ae6cf47f 	mcrge	4, 3, pc, cr12, cr15, {3}	; <UNPREDICTABLE>
d0011c74:	447b4bee 	ldrbtmi	r4, [fp], #-3054	; 0xfffff412
d0011c78:	f06fe7bc 			; <UNDEFINED> instruction: 0xf06fe7bc
d0011c7c:	23004200 	movwcs	r4, #512	; 0x200
d0011c80:	4282900a 	addmi	r9, r2, #10
d0011c84:	f240418b 	vrhadd.s8	d20, d16, d11
d0011c88:	bfa81303 	svclt	0x00a81303
d0011c8c:	7381f44f 	orrvc	pc, r1, #1325400064	; 0x4f000000
d0011c90:	950d9a0a 	strls	r9, [sp, #-2570]	; 0xfffff5f6
d0011c94:	e7cb920e 	strb	r9, [fp, lr, lsl #4]
d0011c98:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d0011c9c:	4620e7f8 			; <UNDEFINED> instruction: 0x4620e7f8
d0011ca0:	f7fe910a 			; <UNDEFINED> instruction: 0xf7fe910a
d0011ca4:	990afa98 	stmdbls	sl, {r3, r4, r7, r9, fp, ip, sp, lr, pc}
d0011ca8:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011cac:	f7fefa8b 			; <UNDEFINED> instruction: 0xf7fefa8b
d0011cb0:	2810fbb7 	ldmdacs	r0, {r0, r1, r2, r4, r5, r7, r8, r9, fp, ip, sp, lr, pc}
d0011cb4:	d1214607 			; <UNDEFINED> instruction: 0xd1214607
d0011cb8:	2b006da3 	blcs	0xd002d34c
d0011cbc:	af25f47f 	svcge	0x0025f47f
d0011cc0:	447b4bdc 	ldrbtmi	r4, [fp], #-3036	; 0xfffff424
d0011cc4:	9b0665a3 	blls	0xd01ab358
d0011cc8:	9b0765e3 	blls	0xd01eb45c
d0011ccc:	ba18e9c4 	blt	0xd064c3e4
d0011cd0:	e71a66a3 	ldr	r6, [sl, -r3, lsr #13]
d0011cd4:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011cd8:	f7fefa7e 			; <UNDEFINED> instruction: 0xf7fefa7e
d0011cdc:	43c3fba1 	bicmi	pc, r3, #164864	; 0x28400
d0011ce0:	f3f7fbb3 			; <UNDEFINED> instruction: 0xf3f7fbb3
d0011ce4:	d2064543 	andle	r4, r6, #281018368	; 0x10c00000
d0011ce8:	2b006da3 	blcs	0xd002d37c
d0011cec:	ae2ef47f 	mcrge	4, 1, pc, cr14, cr15, {3}	; <UNPREDICTABLE>
d0011cf0:	447b4bd1 	ldrbtmi	r4, [fp], #-3025	; 0xfffff42f
d0011cf4:	fb08e77e 	blx	0xd024baf6
d0011cf8:	e7060807 	str	r0, [r6, -r7, lsl #16]
d0011cfc:	e7042710 	smlad	r4, r0, r7, r2
d0011d00:	0f00f1b8 	svceq	0x0000f1b8
d0011d04:	1303f240 	movwne	pc, #12864	; 0x3240	; <UNPREDICTABLE>
d0011d08:	f44fbfa8 			; <UNDEFINED> instruction: 0xf44fbfa8
d0011d0c:	f8cd7381 			; <UNDEFINED> instruction: 0xf8cd7381
d0011d10:	93118038 	tstls	r1, #56	; 0x38
d0011d14:	f240e15c 	vand	q15, q0, q6
d0011d18:	e7f81303 	ldrb	r1, [r8, r3, lsl #6]!
d0011d1c:	7381f44f 	orrvc	pc, r1, #1325400064	; 0x4f000000
d0011d20:	f1b9e7f5 			; <UNDEFINED> instruction: 0xf1b9e7f5
d0011d24:	d0020f22 	andle	r0, r2, r2, lsr #30
d0011d28:	0f27f1b9 	svceq	0x0027f1b9
d0011d2c:	6823d171 	stmdavs	r3!, {r0, r4, r5, r6, r8, ip, lr, pc}
d0011d30:	4701f242 	strmi	pc, [r1, -r2, asr #4]
d0011d34:	68e39308 	stmiavs	r3!, {r3, r8, r9, ip, pc}^
d0011d38:	68e2930b 	stmiavs	r2!, {r0, r1, r3, r8, r9, ip, pc}^
d0011d3c:	429a6863 	addsmi	r6, sl, #6488064	; 0x630000
d0011d40:	4620d05a 			; <UNDEFINED> instruction: 0x4620d05a
d0011d44:	fa47f7fe 	blx	0xd120fd44
d0011d48:	d14a4581 	smlalbble	r4, sl, r1, r5
d0011d4c:	f1b99b08 			; <UNDEFINED> instruction: 0xf1b99b08
d0011d50:	68e70f22 	stmiavs	r7!, {r1, r5, r8, r9, sl, fp}^
d0011d54:	eb039a0b 	bl	0xd00f8588
d0011d58:	f1070802 			; <UNDEFINED> instruction: 0xf1070802
d0011d5c:	682733ff 	stmdavs	r7!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, ip, sp}
d0011d60:	eba7441f 	bl	0xce9e2de4
d0011d64:	d0390708 	eorsle	r0, r9, r8, lsl #14
d0011d68:	0907eb08 	stmdbeq	r7, {r3, r8, r9, fp, sp, lr, pc}
d0011d6c:	8050f8cd 	subshi	pc, r0, sp, asr #17
d0011d70:	d10645c8 	smlabtle	r6, r8, r5, r4
d0011d74:	2b006da3 	blcs	0xd002d408
d0011d78:	ade8f47f 	cfstrdge	mvd15, [r8, #508]!	; 0x1fc
d0011d7c:	447b4baf 	ldrbtmi	r4, [fp], #-2991	; 0xfffff451
d0011d80:	f108e738 			; <UNDEFINED> instruction: 0xf108e738
d0011d84:	9a080301 	bls	0xd0212990
d0011d88:	9314990b 	tstls	r4, #180224	; 0x2c000
d0011d8c:	2a5c5c52 	bcs	0xd1728edc
d0011d90:	d10e920a 	tstle	lr, sl, lsl #4
d0011d94:	d00c4599 	mulle	ip, r9, r5
d0011d98:	465aab14 			; <UNDEFINED> instruction: 0x465aab14
d0011d9c:	46209906 	strtmi	r9, [r0], -r6, lsl #18
d0011da0:	9b079301 	blls	0xd01f69ac
d0011da4:	9008f8cd 	andls	pc, r8, sp, asr #17
d0011da8:	46539300 	ldrbmi	r9, [r3], -r0, lsl #6
d0011dac:	fb62f7fe 	blx	0xd18cfdae
d0011db0:	9b14900a 	blls	0xd0535de0
d0011db4:	d00a4599 	mulle	sl, r9, r5
d0011db8:	b9436da3 	stmdblt	r3, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0011dbc:	447b4ba0 	ldrbtmi	r4, [fp], #-2976	; 0xfffff460
d0011dc0:	9b0665a3 	blls	0xd01ab454
d0011dc4:	9b0765e3 	blls	0xd01eb558
d0011dc8:	ba18e9c4 	blt	0xd064c4e0
d0011dcc:	f44f66a3 	vst1.32	{d22-d24}, [pc :128], r3
d0011dd0:	9a0a7381 	bls	0xd02aebdc
d0011dd4:	870ce9cd 	strhi	lr, [ip, -sp, asr #19]
d0011dd8:	e79a920e 	ldr	r9, [sl, lr, lsl #4]
d0011ddc:	7382f44f 	orrvc	pc, r2, #1325400064	; 0x4f000000
d0011de0:	285ce7f7 	ldmdacs	ip, {r0, r1, r2, r4, r5, r6, r7, r8, r9, sl, sp, lr, pc}^
d0011de4:	4620d102 	strtmi	sp, [r0], -r2, lsl #2
d0011de8:	f9f5f7fe 			; <UNDEFINED> instruction: 0xf9f5f7fe
d0011dec:	d8a4280d 	stmiale	r4!, {r0, r2, r3, fp, sp}
d0011df0:	f000fa27 			; <UNDEFINED> instruction: 0xf000fa27
d0011df4:	d5a007c3 	strle	r0, [r0, #1987]!	; 0x7c3
d0011df8:	0f22f1b9 	svceq	0x0022f1b9
d0011dfc:	4b91d102 	blmi	0xce48620c
d0011e00:	e001447b 	and	r4, r1, fp, ror r4
d0011e04:	447b4b90 	ldrbtmi	r4, [fp], #-2960	; 0xfffff470
d0011e08:	2a006da2 	bcs	0xd002d498
d0011e0c:	ad9ef47f 	cfldrsge	mvf15, [lr, #508]	; 0x1fc
d0011e10:	900ae6f0 	strdls	lr, [sl], -r0
d0011e14:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011e18:	f029f9d5 			; <UNDEFINED> instruction: 0xf029f9d5
d0011e1c:	46800302 	strmi	r0, [r0], r2, lsl #6
d0011e20:	2b3c990a 	blcs	0xd0f38250
d0011e24:	4581d11e 	strmi	sp, [r1, #286]	; 0x11e
d0011e28:	4620d11c 			; <UNDEFINED> instruction: 0x4620d11c
d0011e2c:	f7fe9106 			; <UNDEFINED> instruction: 0xf7fe9106
d0011e30:	f1b9f9d2 			; <UNDEFINED> instruction: 0xf1b9f9d2
d0011e34:	99060f3c 	stmdbls	r6, {r2, r3, r4, r5, r8, r9, sl, fp}
d0011e38:	f2404620 	vmax.s8	d20, d0, d16
d0011e3c:	bf181727 	svclt	0x00181727
d0011e40:	7794f44f 	ldrvc	pc, [r4, pc, asr #8]
d0011e44:	f9bef7fe 			; <UNDEFINED> instruction: 0xf9bef7fe
d0011e48:	d109283d 	tstle	r9, sp, lsr r8
d0011e4c:	f2404620 	vmax.s8	d20, d0, d16
d0011e50:	f7fe172d 			; <UNDEFINED> instruction: 0xf7fe172d
d0011e54:	f1b9f9c0 			; <UNDEFINED> instruction: 0xf1b9f9c0
d0011e58:	bf080f3c 	svclt	0x00080f3c
d0011e5c:	7796f44f 	ldrvc	pc, [r6, pc, asr #8]
d0011e60:	e0b59711 	adcs	r9, r5, r1, lsl r7
d0011e64:	0f3df1b8 	svceq	0x003df1b8
d0011e68:	80c0f040 	sbchi	pc, r0, r0, asr #32
d0011e6c:	0f2bf1b9 	svceq	0x002bf1b9
d0011e70:	f1b9d002 			; <UNDEFINED> instruction: 0xf1b9d002
d0011e74:	d10a0f2d 	tstle	sl, sp, lsr #30
d0011e78:	f2404620 	vmax.s8	d20, d0, d16
d0011e7c:	f7fe1725 			; <UNDEFINED> instruction: 0xf7fe1725
d0011e80:	f1b9f9aa 			; <UNDEFINED> instruction: 0xf1b9f9aa
d0011e84:	bf180f2b 	svclt	0x00180f2b
d0011e88:	7793f44f 	ldrvc	pc, [r3, pc, asr #8]
d0011e8c:	f1b9e7e8 			; <UNDEFINED> instruction: 0xf1b9e7e8
d0011e90:	d0050f26 	andle	r0, r5, r6, lsr #30
d0011e94:	0f7cf1b9 	svceq	0x007cf1b9
d0011e98:	f1b9d002 			; <UNDEFINED> instruction: 0xf1b9d002
d0011e9c:	d10d0f5e 	tstle	sp, lr, asr pc
d0011ea0:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011ea4:	f1b9f998 			; <UNDEFINED> instruction: 0xf1b9f998
d0011ea8:	d05f0f26 	subsle	r0, pc, r6, lsr #30
d0011eac:	0f7cf1b9 	svceq	0x007cf1b9
d0011eb0:	172bf240 	strne	pc, [fp, -r0, asr #4]!
d0011eb4:	f44fbf08 			; <UNDEFINED> instruction: 0xf44fbf08
d0011eb8:	e7d17795 	bfi	r7, r5, #15, #3
d0011ebc:	0f3df1b9 	svceq	0x003df1b9
d0011ec0:	f1a9d112 			; <UNDEFINED> instruction: 0xf1a9d112
d0011ec4:	2b02033c 	blcs	0xd0092bbc
d0011ec8:	f1b9d911 			; <UNDEFINED> instruction: 0xf1b9d911
d0011ecc:	d1300f2d 	teqle	r0, sp, lsr #30
d0011ed0:	0f3ef1b8 	svceq	0x003ef1b8
d0011ed4:	4620d13e 			; <UNDEFINED> instruction: 0x4620d13e
d0011ed8:	7791f44f 	ldrvc	pc, [r1, pc, asr #8]
d0011edc:	f97bf7fe 			; <UNDEFINED> instruction: 0xf97bf7fe
d0011ee0:	f1b9e7be 			; <UNDEFINED> instruction: 0xf1b9e7be
d0011ee4:	d1130f3d 	tstle	r3, sp, lsr pc
d0011ee8:	0f21f1b9 	svceq	0x0021f1b9
d0011eec:	4620d1e9 	strtmi	sp, [r0], -r9, ror #3
d0011ef0:	f971f7fe 			; <UNDEFINED> instruction: 0xf971f7fe
d0011ef4:	0f3df1b9 	svceq	0x003df1b9
d0011ef8:	f1b9d03b 			; <UNDEFINED> instruction: 0xf1b9d03b
d0011efc:	d03b0f21 	eorsle	r0, fp, r1, lsr #30
d0011f00:	0f3cf1b9 	svceq	0x003cf1b9
d0011f04:	171ff240 	ldrne	pc, [pc, -r0, asr #4]
d0011f08:	f44fbf08 			; <UNDEFINED> instruction: 0xf44fbf08
d0011f0c:	e7a7778f 	str	r7, [r7, pc, lsl #15]!
d0011f10:	0f26f1b9 	svceq	0x0026f1b9
d0011f14:	f1b9d002 			; <UNDEFINED> instruction: 0xf1b9d002
d0011f18:	d10a0f7c 	tstle	sl, ip, ror pc
d0011f1c:	f2404620 	vmax.s8	d20, d0, d16
d0011f20:	f7fe1721 			; <UNDEFINED> instruction: 0xf7fe1721
d0011f24:	f1b8f958 			; <UNDEFINED> instruction: 0xf1b8f958
d0011f28:	bf080f26 	svclt	0x00080f26
d0011f2c:	7790f44f 	ldrvc	pc, [r0, pc, asr #8]
d0011f30:	f1b9e796 			; <UNDEFINED> instruction: 0xf1b9e796
d0011f34:	d10d0f00 	tstle	sp, r0, lsl #30
d0011f38:	b9436da3 	stmdblt	r3, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0011f3c:	447b4b43 	ldrbtmi	r4, [fp], #-2883	; 0xfffff4bd
d0011f40:	9b0665a3 	blls	0xd01ab5d4
d0011f44:	9b0765e3 	blls	0xd01eb6d8
d0011f48:	ba18e9c4 	blt	0xd064c660
d0011f4c:	f24066a3 	vmax.s8	d22, d16, d19
d0011f50:	e7851705 	str	r1, [r5, r5, lsl #14]
d0011f54:	0f3df1b8 	svceq	0x003df1b8
d0011f58:	d181464f 	orrle	r4, r1, pc, asr #12
d0011f5c:	4649483c 			; <UNDEFINED> instruction: 0x4649483c
d0011f60:	f00e4478 			; <UNDEFINED> instruction: 0xf00e4478
d0011f64:	2800fe7b 	stmdacs	r0, {r0, r1, r3, r4, r5, r6, r9, sl, fp, ip, sp, lr, pc}
d0011f68:	e779d1e6 	ldrb	sp, [r9, -r6, ror #3]!
d0011f6c:	1729f240 	strne	pc, [r9, -r0, asr #4]!
d0011f70:	f44fe776 	vst1.16	{d30}, [pc :256], r6
d0011f74:	e773778e 	ldrb	r7, [r3, -lr, lsl #15]!
d0011f78:	171df240 	ldrne	pc, [sp, -r0, asr #4]
d0011f7c:	6da3e770 	stcvs	7, cr14, [r3, #448]!	; 0x1c0
d0011f80:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0011f84:	4a33ace3 	bmi	0xd0cfd318
d0011f88:	3068f89d 	mlscc	r8, sp, r8, pc	; <UNPREDICTABLE>
d0011f8c:	65a2447a 	strvs	r4, [r2, #1146]!	; 0x47a
d0011f90:	65e29a17 	strbvs	r9, [r2, #2583]!	; 0xa17
d0011f94:	e9c49a18 	stmib	r4, {r3, r4, r9, fp, ip, pc}^
d0011f98:	9b1b2318 	blls	0xd06dac00
d0011f9c:	e4d566a3 	ldrb	r6, [r5], #1699	; 0x6a3
d0011fa0:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0011fa4:	ad0caca4 	stcge	12, cr10, [ip, #-656]	; 0xfffffd70
d0011fa8:	46284621 	strtmi	r4, [r8], -r1, lsr #12
d0011fac:	f932f7fe 			; <UNDEFINED> instruction: 0xf932f7fe
d0011fb0:	68e29b0e 	stmiavs	r2!, {r1, r2, r3, r8, r9, fp, ip, pc}^
d0011fb4:	9b0f930a 	blls	0xd03f6be4
d0011fb8:	93069f0c 	movwls	r9, #28428	; 0x6f0c
d0011fbc:	f8dd9b13 			; <UNDEFINED> instruction: 0xf8dd9b13
d0011fc0:	9307b040 	movwls	fp, #28736	; 0x7040
d0011fc4:	f89d6863 			; <UNDEFINED> instruction: 0xf89d6863
d0011fc8:	429aa048 	addsmi	sl, sl, #72	; 0x48
d0011fcc:	ad63f47f 	cfstrdge	mvd15, [r3, #-508]!	; 0xfffffe04
d0011fd0:	e5f14634 	ldrb	r4, [r1, #1588]!	; 0x634
d0011fd4:	4620900a 	strtmi	r9, [r0], -sl
d0011fd8:	f8f4f7fe 			; <UNDEFINED> instruction: 0xf8f4f7fe
d0011fdc:	0020f040 	eoreq	pc, r0, r0, asr #32
d0011fe0:	2878990a 	ldmdacs	r8!, {r1, r3, r8, fp, ip, pc}^
d0011fe4:	ae5bf43f 	mrcge	4, 2, APSR_nzcv, cr11, cr15, {1}
d0011fe8:	e58e2708 	str	r2, [lr, #1800]	; 0x708
d0011fec:	f47f45c1 			; <UNDEFINED> instruction: 0xf47f45c1
d0011ff0:	f1b9af6c 			; <UNDEFINED> instruction: 0xf1b9af6c
d0011ff4:	d0030f2b 	andle	r0, r3, fp, lsr #30
d0011ff8:	0f2df1b9 	svceq	0x002df1b9
d0011ffc:	af71f47f 	svcge	0x0071f47f
d0012000:	f2404620 	vmax.s8	d20, d0, d16
d0012004:	f7fe1723 			; <UNDEFINED> instruction: 0xf7fe1723
d0012008:	f1b8f8e6 			; <UNDEFINED> instruction: 0xf1b8f8e6
d001200c:	bf180f2b 	svclt	0x00180f2b
d0012010:	7792f44f 	ldrvc	pc, [r2, pc, asr #8]
d0012014:	bf00e724 	svclt	0x0000e724
d0012018:	fffffd4d 			; <UNDEFINED> instruction: 0xfffffd4d
d001201c:	fffffd19 			; <UNDEFINED> instruction: 0xfffffd19
d0012020:	fffffce9 			; <UNDEFINED> instruction: 0xfffffce9
d0012024:	0000f132 	andeq	pc, r0, r2, lsr r1	; <UNPREDICTABLE>
d0012028:	0000f14a 	andeq	pc, r0, sl, asr #2
d001202c:	fffffbd5 			; <UNDEFINED> instruction: 0xfffffbd5
d0012030:	fffffb78 			; <UNDEFINED> instruction: 0xfffffb78
d0012034:	fffffb55 			; <UNDEFINED> instruction: 0xfffffb55
d0012038:	fffffb3e 			; <UNDEFINED> instruction: 0xfffffb3e
d001203c:	fffffb05 			; <UNDEFINED> instruction: 0xfffffb05
d0012040:	fffffac5 			; <UNDEFINED> instruction: 0xfffffac5
d0012044:	fffff938 			; <UNDEFINED> instruction: 0xfffff938
d0012048:	fffff94a 			; <UNDEFINED> instruction: 0xfffff94a
d001204c:	fffff971 			; <UNDEFINED> instruction: 0xfffff971
d0012050:	fffff94b 			; <UNDEFINED> instruction: 0xfffff94b
d0012054:	fffff7e0 			; <UNDEFINED> instruction: 0xfffff7e0

Disassembly of section .text.scan_directive:

d001239c <.text.scan_directive>:
d001239c:	e92db082 	push	{r1, r7, ip, sp, pc}
d00123a0:	ed2d4ff0 	vstr	FPSCR_nzcvqc, [sp, #-448]!	; 0xfffffe40
d00123a4:	b09b8b02 	addslt	r8, fp, r2, lsl #22
d00123a8:	ee08460c 	cfmadd32	mvax0, mvfx4, mvfx8, mvfx12
d00123ac:	a9260a10 	stmdbge	r6!, {r4, r9, fp}
d00123b0:	000ce881 	andeq	lr, ip, r1, lsl #17
d00123b4:	9d299b2a 	vstmdbls	r9!, {d9-d29}
d00123b8:	9b2d9308 	blls	0xd0b76fe0
d00123bc:	a0b0f89d 	umlalsge	pc, r0, sp, r8	; <UNPREDICTABLE>
d00123c0:	68e39309 	stmiavs	r3!, {r0, r3, r8, r9, ip, pc}^
d00123c4:	6963930f 	stmdbvs	r3!, {r0, r1, r2, r3, r8, r9, ip, pc}^
d00123c8:	21009310 	tstcs	r0, r0, lsl r3
d00123cc:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d00123d0:	2820fef9 	stmdacs	r0!, {r0, r3, r4, r5, r6, r7, r9, sl, fp, ip, sp, lr, pc}
d00123d4:	2809d02a 	stmdacs	r9, {r1, r3, r5, ip, lr, pc}
d00123d8:	6827d028 	stmdavs	r7!, {r3, r5, ip, lr, pc}
d00123dc:	441f68e3 	ldrmi	r6, [pc], #-2275	; 0xd00123e4
d00123e0:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d00123e4:	feeef7fd 	mcr2	7, 7, pc, cr14, cr13, {7}	; <UNPREDICTABLE>
d00123e8:	ffcdf7fd 			; <UNDEFINED> instruction: 0xffcdf7fd
d00123ec:	bb084681 	bllt	0xd0223df8
d00123f0:	68e36822 	stmiavs	r3!, {r1, r5, fp, sp, lr}^
d00123f4:	1bd2441a 	blne	0xcf4a3464
d00123f8:	d11f2a07 	tstle	pc, r7, lsl #20
d00123fc:	1964f8df 	stmdbne	r4!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d0012400:	920a4638 	andls	r4, sl, #56, 12	; 0x3800000
d0012404:	f00d4479 			; <UNDEFINED> instruction: 0xf00d4479
d0012408:	fab0f80b 	blx	0xcec5043c
d001240c:	9a0af680 	bls	0xd02cfe14
d0012410:	f04f0976 			; <UNDEFINED> instruction: 0xf04f0976
d0012414:	2a050b00 	bcs	0xd015501c
d0012418:	f8cd46d8 			; <UNDEFINED> instruction: 0xf8cd46d8
d001241c:	f8cdb030 			; <UNDEFINED> instruction: 0xf8cdb030
d0012420:	f8cdb028 			; <UNDEFINED> instruction: 0xf8cdb028
d0012424:	d132b02c 	teqle	r2, ip, lsr #32
d0012428:	bc8cf000 	stclt	0, cr15, [ip], {0}
d001242c:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0012430:	e7cafed2 			; <UNDEFINED> instruction: 0xe7cafed2
d0012434:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0012438:	e7d1fece 	ldrb	pc, [r1, lr, asr #29]	; <UNPREDICTABLE>
d001243c:	f0402a06 			; <UNDEFINED> instruction: 0xf0402a06
d0012440:	f8df8465 			; <UNDEFINED> instruction: 0xf8df8465
d0012444:	46381924 	ldrtmi	r1, [r8], -r4, lsr #18
d0012448:	464e920a 	strbmi	r9, [lr], -sl, lsl #4
d001244c:	f00c4479 			; <UNDEFINED> instruction: 0xf00c4479
d0012450:	f8dfffe7 			; <UNDEFINED> instruction: 0xf8dfffe7
d0012454:	fab01918 	blx	0xcec188bc
d0012458:	9a0af880 	bls	0xd02d0660
d001245c:	46384479 			; <UNDEFINED> instruction: 0x46384479
d0012460:	ffdef00c 			; <UNDEFINED> instruction: 0xffdef00c
d0012464:	f380fab0 			; <UNDEFINED> instruction: 0xf380fab0
d0012468:	1904f8df 	stmdbne	r4, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d001246c:	095b4638 	ldmdbeq	fp, {r3, r4, r5, r9, sl, lr}^
d0012470:	44799a0a 	ldrbtmi	r9, [r9], #-2570	; 0xfffff5f6
d0012474:	1858ea4f 	ldmdane	r8, {r0, r1, r2, r3, r6, r9, fp, sp, lr, pc}^
d0012478:	f00c930b 			; <UNDEFINED> instruction: 0xf00c930b
d001247c:	fab0ffd1 	blx	0xcec523c8
d0012480:	f8cdfb80 			; <UNDEFINED> instruction: 0xf8cdfb80
d0012484:	f8cd9030 			; <UNDEFINED> instruction: 0xf8cd9030
d0012488:	ea4f9028 	b	0xd13f6530
d001248c:	23001b5b 	movwcs	r1, #2907	; 0xb5b
d0012490:	930d930e 	movwls	r9, #54030	; 0xd30e
d0012494:	2a02e03a 	bcs	0xd00ca584
d0012498:	2a04d022 	bcs	0xd0146528
d001249c:	d1b8464e 			; <UNDEFINED> instruction: 0xd1b8464e
d00124a0:	18d0f8df 	ldmne	r0, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d00124a4:	920a4638 	andls	r4, sl, #56, 12	; 0x3800000
d00124a8:	447946cb 	ldrbtmi	r4, [r9], #-1739	; 0xfffff935
d00124ac:	f00c46c8 			; <UNDEFINED> instruction: 0xf00c46c8
d00124b0:	fab0ffb7 	blx	0xcec52394
d00124b4:	f8dff380 			; <UNDEFINED> instruction: 0xf8dff380
d00124b8:	463818c0 	ldrtmi	r1, [r8], -r0, asr #17
d00124bc:	9a0a095b 	bls	0xd0294a30
d00124c0:	930e4479 	movwls	r4, #58489	; 0xe479
d00124c4:	ffacf00c 			; <UNDEFINED> instruction: 0xffacf00c
d00124c8:	f380fab0 			; <UNDEFINED> instruction: 0xf380fab0
d00124cc:	9034f8cd 	eorsls	pc, r4, sp, asr #17
d00124d0:	9030f8cd 	eorsls	pc, r0, sp, asr #17
d00124d4:	f8cd095b 			; <UNDEFINED> instruction: 0xf8cd095b
d00124d8:	f8cd9028 			; <UNDEFINED> instruction: 0xf8cd9028
d00124dc:	e015902c 	ands	r9, r5, ip, lsr #32
d00124e0:	1898f8df 	ldmne	r8, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d00124e4:	46cb4638 			; <UNDEFINED> instruction: 0x46cb4638
d00124e8:	447946c8 	ldrbtmi	r4, [r9], #-1736	; 0xfffff938
d00124ec:	f00c464e 			; <UNDEFINED> instruction: 0xf00c464e
d00124f0:	fab0ff97 	blx	0xcec52354
d00124f4:	f8cdf380 			; <UNDEFINED> instruction: 0xf8cdf380
d00124f8:	095b9038 	ldmdbeq	fp, {r3, r4, r5, ip, pc}^
d00124fc:	9030f8cd 	eorsls	pc, r0, sp, asr #17
d0012500:	9028f8cd 	eorls	pc, r8, sp, asr #17
d0012504:	464b930d 	strbmi	r9, [fp], -sp, lsl #6
d0012508:	902cf8cd 	eorls	pc, ip, sp, asr #17
d001250c:	0708ea56 	smlsdeq	r8, r6, sl, lr
d0012510:	815cf000 	cmphi	ip, r0	; <UNPREDICTABLE>
d0012514:	93114620 	tstls	r1, #32, 12	; 0x2000000
d0012518:	fe9ef7fd 	mrc2	7, 4, pc, cr14, cr13, {7}
d001251c:	28009b11 	stmdacs	r0, {r0, r4, r8, r9, fp, ip, pc}
d0012520:	8154f000 	cmphi	r4, r0	; <UNPREDICTABLE>
d0012524:	f10d9b0f 			; <UNDEFINED> instruction: 0xf10d9b0f
d0012528:	ae120c98 	mrcge	12, 0, r0, cr2, cr8, {4}
d001252c:	9b1060e3 	blls	0xd042a8c0
d0012530:	e8bc6163 	ldm	ip!, {r0, r1, r5, r6, r8, sp, lr}
d0012534:	c60f000f 	strgt	r0, [pc], -pc
d0012538:	000fe89c 	muleq	pc, ip, r8	; <UNPREDICTABLE>
d001253c:	000fe886 	andeq	lr, pc, r6, lsl #17
d0012540:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d0012544:	fe3ef7fd 	mrc2	7, 1, pc, cr14, cr13, {7}
d0012548:	d0332820 	eorsle	r2, r3, r0, lsr #16
d001254c:	d0312809 	eorsle	r2, r1, r9, lsl #16
d0012550:	68e36826 	stmiavs	r3!, {r1, r2, r5, fp, sp, lr}^
d0012554:	2100441e 	tstcs	r0, lr, lsl r4
d0012558:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d001255c:	f7fdfe33 			; <UNDEFINED> instruction: 0xf7fdfe33
d0012560:	bb58ff12 	bllt	0xd16521b0
d0012564:	68e36822 	stmiavs	r3!, {r1, r5, fp, sp, lr}^
d0012568:	1b92441a 	blne	0xce4a35d8
d001256c:	d1292a07 			; <UNDEFINED> instruction: 0xd1292a07
d0012570:	180cf8df 	stmdane	ip, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d0012574:	44794630 	ldrbtmi	r4, [r9], #-1584	; 0xfffff9d0
d0012578:	ff52f00c 			; <UNDEFINED> instruction: 0xff52f00c
d001257c:	b3584607 	cmplt	r8, #7340032	; 0x700000
d0012580:	b94b6da3 	stmdblt	fp, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0012584:	37fcf8df 	ubfxcc	pc, pc, #17, #29
d0012588:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d001258c:	9b083516 	blls	0xd021f9ec
d0012590:	3a18e9c4 	bcc	0xd064cca8
d0012594:	66a39b09 	strtvs	r9, [r3], r9, lsl #22
d0012598:	ee184621 	cfmsub32	mvax1, mvfx4, mvfx8, mvfx1
d001259c:	f7fd0a10 			; <UNDEFINED> instruction: 0xf7fd0a10
d00125a0:	ee18fe39 	mrc	14, 0, APSR_nzcv, cr8, cr9, {1}
d00125a4:	b01b0a10 	andslt	r0, fp, r0, lsl sl
d00125a8:	8b02ecbd 	blhi	0xd00cd8a4
d00125ac:	4ff0e8bd 	svcmi	0x00f0e8bd
d00125b0:	4770b002 	ldrbmi	fp, [r0, -r2]!
d00125b4:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d00125b8:	e7c1fe0e 	strb	pc, [r1, lr, lsl #28]	; <UNPREDICTABLE>
d00125bc:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d00125c0:	e7c8fe0a 	strb	pc, [r8, sl, lsl #28]	; <UNPREDICTABLE>
d00125c4:	d1db2a06 	bicsle	r2, fp, r6, lsl #20
d00125c8:	17bcf8df 	sbfxne	pc, pc, #17, #29
d00125cc:	44794630 	ldrbtmi	r4, [r9], #-1584	; 0xfffff9d0
d00125d0:	ff26f00c 			; <UNDEFINED> instruction: 0xff26f00c
d00125d4:	d1d32800 	bicsle	r2, r3, r0, lsl #16
d00125d8:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d00125dc:	fdf2f7fd 	ldc2l	7, cr15, [r2, #1012]!	; 0x3f4
d00125e0:	d0162820 	andsle	r2, r6, r0, lsr #16
d00125e4:	d0142809 	andsle	r2, r4, r9, lsl #16
d00125e8:	d0552f00 	subsle	r2, r5, r0, lsl #30
d00125ec:	68e76826 	stmiavs	r7!, {r1, r2, r5, fp, sp, lr}^
d00125f0:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d00125f4:	fde6f7fd 	stc2l	7, cr15, [r6, #1012]!	; 0x3f4
d00125f8:	fec5f7fd 	mcr2	7, 6, pc, cr5, cr13, {7}	; <UNPREDICTABLE>
d00125fc:	6fa3b968 	svcvs	0x00a3b968
d0012600:	da0e2b00 	ble	0xd039d208
d0012604:	2b006da3 	blcs	0xd002dc98
d0012608:	f8dfd1c6 			; <UNDEFINED> instruction: 0xf8dfd1c6
d001260c:	447b3780 	ldrbtmi	r3, [fp], #-1920	; 0xfffff880
d0012610:	4620e7bb 			; <UNDEFINED> instruction: 0x4620e7bb
d0012614:	fddff7fd 	ldc2l	7, cr15, [pc, #1012]	; 0xd0012a10
d0012618:	4620e7de 			; <UNDEFINED> instruction: 0x4620e7de
d001261c:	fddbf7fd 	ldc2l	7, cr15, [fp, #1012]	; 0x3f4
d0012620:	6822e7e6 	stmdavs	r2!, {r1, r2, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d0012624:	68e319f0 	stmiavs	r3!, {r4, r5, r6, r7, r8, fp, ip}^
d0012628:	1a12441a 	bne	0xd04a3698
d001262c:	d1e92a04 	mvnle	r2, r4, lsl #20
d0012630:	175cf8df 	smmlsne	ip, pc, r8, pc	; <UNPREDICTABLE>
d0012634:	f00c4479 			; <UNDEFINED> instruction: 0xf00c4479
d0012638:	2800fef3 	stmdacs	r0, {r0, r1, r4, r5, r6, r7, r9, sl, fp, ip, sp, lr, pc}
d001263c:	6fa3d1e2 	svcvs	0x00a3d1e2
d0012640:	72a6f44f 	adcvc	pc, r6, #1325400064	; 0x4f000000
d0012644:	4303fb02 	movwmi	pc, #15106	; 0x3b02	; <UNPREDICTABLE>
d0012648:	f8832201 			; <UNDEFINED> instruction: 0xf8832201
d001264c:	2100230a 	tstcs	r0, sl, lsl #6
d0012650:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0012654:	2820fdb7 	stmdacs	r0!, {r0, r1, r2, r4, r5, r7, r8, sl, fp, ip, sp, lr, pc}
d0012658:	80b4f000 	adcshi	pc, r4, r0
d001265c:	f0002809 			; <UNDEFINED> instruction: 0xf0002809
d0012660:	68e280b1 	stmiavs	r2!, {r0, r4, r5, r7, pc}^
d0012664:	429a6863 	addsmi	r6, sl, #6488064	; 0x630000
d0012668:	80a6f000 	adchi	pc, r6, r0
d001266c:	f000280d 			; <UNDEFINED> instruction: 0xf000280d
d0012670:	280a80a3 	stmdacs	sl, {r0, r1, r5, r7, pc}
d0012674:	80a0f000 	adchi	pc, r0, r0
d0012678:	d106282f 	tstle	r6, pc, lsr #16
d001267c:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d0012680:	fda0f7fd 	stc2	7, cr15, [r0, #1012]!	; 0x3f4
d0012684:	f000282f 			; <UNDEFINED> instruction: 0xf000282f
d0012688:	6da38097 	stcvs	0, cr8, [r3, #604]!	; 0x25c
d001268c:	d1832b00 	orrle	r2, r3, r0, lsl #22
d0012690:	3700f8df 			; <UNDEFINED> instruction: 0x3700f8df
d0012694:	e778447b 			; <UNDEFINED> instruction: 0xe778447b
d0012698:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d001269c:	2822fd9c 	stmdacs	r2!, {r2, r3, r4, r7, r8, sl, fp, ip, sp, lr, pc}
d00126a0:	d0094680 	andle	r4, r9, r0, lsl #13
d00126a4:	d01c283c 	andsle	r2, ip, ip, lsr r8
d00126a8:	2b006da3 	blcs	0xd002dd3c
d00126ac:	af74f47f 	svcge	0x0074f47f
d00126b0:	36e4f8df 	usatcc	pc, #4, pc, asr #17	; <UNPREDICTABLE>
d00126b4:	e768447b 			; <UNDEFINED> instruction: 0xe768447b
d00126b8:	68264681 	stmdavs	r6!, {r0, r7, r9, sl, lr}
d00126bc:	210068e7 	smlattcs	r0, r7, r8, r6
d00126c0:	68e24620 	stmiavs	r2!, {r5, r9, sl, lr}^
d00126c4:	fd7ef7fd 	ldc2l	7, cr15, [lr, #-1012]!	; 0xfffffc0c
d00126c8:	429a6863 	addsmi	r6, sl, #6488064	; 0x630000
d00126cc:	4581d30c 	strmi	sp, [r1, #780]	; 0x30c
d00126d0:	6da3d014 	stcvs	0, cr13, [r3, #80]!	; 0x50
d00126d4:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d00126d8:	f8dfaf5f 			; <UNDEFINED> instruction: 0xf8dfaf5f
d00126dc:	447b36c0 	ldrbtmi	r3, [fp], #-1728	; 0xfffff940
d00126e0:	f04fe753 			; <UNDEFINED> instruction: 0xf04fe753
d00126e4:	e7e8093e 			; <UNDEFINED> instruction: 0xe7e8093e
d00126e8:	d0074581 	andle	r4, r7, r1, lsl #11
d00126ec:	d0f0280d 	rscsle	r2, r0, sp, lsl #16
d00126f0:	d0ee280a 	rscle	r2, lr, sl, lsl #16
d00126f4:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d00126f8:	e7e0fd6e 	strb	pc, [r0, lr, ror #26]!	; <UNPREDICTABLE>
d00126fc:	68264437 	stmdavs	r6!, {r0, r1, r2, r4, r5, sl, lr}
d0012700:	1bf64416 	blne	0xcfda3760
d0012704:	4620d0e5 	strtmi	sp, [r0], -r5, ror #1
d0012708:	fd65f7fd 	stc2l	7, cr15, [r5, #-1012]!	; 0xfffffc0c
d001270c:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d0012710:	fd58f7fd 	ldc2l	7, cr15, [r8, #-1012]	; 0xfffffc0c
d0012714:	d0f62820 	rscsle	r2, r6, r0, lsr #16
d0012718:	d0f42809 	rscsle	r2, r4, r9, lsl #16
d001271c:	686368e2 	stmdavs	r3!, {r1, r5, r6, r7, fp, sp, lr}^
d0012720:	d013429a 	mulsle	r3, sl, r2
d0012724:	d011280d 	andsle	r2, r1, sp, lsl #16
d0012728:	d00f280a 	andle	r2, pc, sl, lsl #16
d001272c:	d105282f 	tstle	r5, pc, lsr #16
d0012730:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d0012734:	fd46f7fd 	stc2l	7, cr15, [r6, #-1012]	; 0xfffffc0c
d0012738:	d007282f 	andle	r2, r7, pc, lsr #16
d001273c:	2b006da3 	blcs	0xd002ddd0
d0012740:	af2af47f 	svcge	0x002af47f
d0012744:	3658f8df 			; <UNDEFINED> instruction: 0x3658f8df
d0012748:	e71e447b 			; <UNDEFINED> instruction: 0xe71e447b
d001274c:	d11b2e06 	tstle	fp, r6, lsl #28
d0012750:	1650f8df 			; <UNDEFINED> instruction: 0x1650f8df
d0012754:	46384632 			; <UNDEFINED> instruction: 0x46384632
d0012758:	f00c4479 			; <UNDEFINED> instruction: 0xf00c4479
d001275c:	b998fe61 	ldmiblt	r8, {r0, r5, r6, r9, sl, fp, ip, sp, lr, pc}
d0012760:	ee189b08 	vnmls.f64	d9, d8, d8
d0012764:	95154a10 	ldrls	r4, [r5, #-2576]	; 0xfffff5f0
d0012768:	9316ad12 	tstls	r6, #1152	; 0x480
d001276c:	7383f44f 	orrvc	pc, r3, #1325400064	; 0x4f000000
d0012770:	a060f88d 	rsbge	pc, r0, sp, lsl #17
d0012774:	9b099317 	blls	0xd02773d8
d0012778:	cd0f9319 	stcgt	3, cr9, [pc, #-100]	; 0xd001271c
d001277c:	e895c40f 	ldm	r5, {r0, r1, r2, r3, sl, lr, pc}
d0012780:	e884000f 	stm	r4, {r0, r1, r2, r3}
d0012784:	e70c000f 	str	r0, [ip, -pc]
d0012788:	0f22f1b8 	svceq	0x0022f1b8
d001278c:	6da3d007 	stcvs	0, cr13, [r3, #28]!
d0012790:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0012794:	f8dfaf01 			; <UNDEFINED> instruction: 0xf8dfaf01
d0012798:	447b3610 	ldrbtmi	r3, [fp], #-1552	; 0xfffff9f0
d001279c:	9b09e6f5 	blls	0xd028c378
d00127a0:	9a084629 	bls	0xd022404c
d00127a4:	93004620 	movwls	r4, #1568	; 0x620
d00127a8:	96024653 			; <UNDEFINED> instruction: 0x96024653
d00127ac:	f7fe9701 			; <UNDEFINED> instruction: 0xf7fe9701
d00127b0:	2800fda5 	stmdacs	r0, {r0, r2, r5, r7, r8, sl, fp, ip, sp, lr, pc}
d00127b4:	aef0f43f 	mrcge	4, 7, APSR_nzcv, cr0, cr15, {1}
d00127b8:	ee184621 	cfmsub32	mvax1, mvfx4, mvfx8, mvfx1
d00127bc:	f7ff0a10 			; <UNDEFINED> instruction: 0xf7ff0a10
d00127c0:	e6eef88b 	strbt	pc, [lr], fp, lsl #17	; <UNPREDICTABLE>
d00127c4:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d00127c8:	e740fd06 	strb	pc, [r0, -r6, lsl #26]	; <UNPREDICTABLE>
d00127cc:	0206ea49 	andeq	lr, r6, #299008	; 0x49000
d00127d0:	ea42990b 	b	0xd10b8c04
d00127d4:	430a0208 	movwmi	r0, #41480	; 0xa208
d00127d8:	430a990a 	movwmi	r9, #43274	; 0xa90a
d00127dc:	430a990c 	movwmi	r9, #43276	; 0xa90c
d00127e0:	ea42990d 	b	0xd10b8c1c
d00127e4:	430a020b 	movwmi	r0, #41483	; 0xa20b
d00127e8:	430a990e 	movwmi	r9, #43278	; 0xa90e
d00127ec:	d123431a 			; <UNDEFINED> instruction: 0xd123431a
d00127f0:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d00127f4:	b158fd31 	cmplt	r8, r1, lsr sp	; <UNPREDICTABLE>
d00127f8:	b94b6da3 	stmdblt	fp, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d00127fc:	35acf8df 	strcc	pc, [ip, #2271]!	; 0x8df
d0012800:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0012804:	9b083516 	blls	0xd021fc64
d0012808:	3a18e9c4 	bcc	0xd064cf20
d001280c:	66a39b09 	strtvs	r9, [r3], r9, lsl #22
d0012810:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0012814:	2220fd3e 	eorcs	pc, r0, #3968	; 0xf80
d0012818:	ee182100 	mufe	f2, f0, f0
d001281c:	f00c0a10 			; <UNDEFINED> instruction: 0xf00c0a10
d0012820:	f44ffde1 			; <UNDEFINED> instruction: 0xf44ffde1
d0012824:	ee187397 	mrc	3, 0, r7, cr8, cr7, {4}
d0012828:	61532a10 	cmpvs	r3, r0, lsl sl
d001282c:	4620e6b9 			; <UNDEFINED> instruction: 0x4620e6b9
d0012830:	f7fd930f 			; <UNDEFINED> instruction: 0xf7fd930f
d0012834:	9b0ffcd0 	blls	0xd0411b7c
d0012838:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d001283c:	f7fd930f 			; <UNDEFINED> instruction: 0xf7fd930f
d0012840:	2820fcc1 	stmdacs	r0!, {r0, r6, r7, sl, fp, ip, sp, lr, pc}
d0012844:	d0f29b0f 	rscsle	r9, r2, pc, lsl #22
d0012848:	d0f02809 	rscsle	r2, r0, r9, lsl #16
d001284c:	46209311 			; <UNDEFINED> instruction: 0x46209311
d0012850:	930f6823 	movwls	r6, #63523	; 0xf823
d0012854:	931068e3 	tstls	r0, #14876672	; 0xe30000
d0012858:	9b0f9a10 	blls	0xd03f90a0
d001285c:	f7fd189f 			; <UNDEFINED> instruction: 0xf7fd189f
d0012860:	6821fd18 	stmdavs	r1!, {r3, r4, r8, sl, fp, ip, sp, lr, pc}
d0012864:	46bc68e2 	ldrtmi	r6, [ip], r2, ror #17
d0012868:	44119b11 	ldrmi	r9, [r1], #-2833	; 0xfffff4ef
d001286c:	0201f10c 	andeq	pc, r1, #12, 2
d0012870:	d301428a 	movwle	r4, #4746	; 0x128a
d0012874:	e033468c 	eors	r4, r3, ip, lsl #13
d0012878:	0c01f812 	stceq	8, cr15, [r1], {18}
d001287c:	d15a282f 	cmple	sl, pc, lsr #16
d0012880:	282f7810 	stmdacs	pc!, {r4, fp, ip, sp, lr}	; <UNPREDICTABLE>
d0012884:	282ad02c 	stmdacs	sl!, {r2, r3, r5, ip, lr, pc}
d0012888:	f10cd155 			; <UNDEFINED> instruction: 0xf10cd155
d001288c:	1c500202 	lfmne	f0, 2, [r0], {2}
d0012890:	d2174288 	andsle	r4, r7, #136, 4	; 0x80000008
d0012894:	6c01f810 	stcvs	8, cr15, [r1], {16}
d0012898:	d1112e2a 	tstle	r1, sl, lsr #28
d001289c:	2e2f7806 	cdpcs	8, 2, cr7, cr15, cr6, {0}
d00128a0:	3202d10e 	andcc	sp, r2, #-2147483645	; 0x80000003
d00128a4:	d21a428a 	andsle	r4, sl, #-1610612728	; 0xa0000008
d00128a8:	0b01f812 	bleq	0xd00908f8
d00128ac:	d0f92820 	rscsle	r2, r9, r0, lsr #16
d00128b0:	d0f72809 	rscsle	r2, r7, r9, lsl #16
d00128b4:	b99a6da2 	ldmiblt	sl, {r1, r5, r7, r8, sl, fp, sp, lr}
d00128b8:	24f4f8df 	ldrbtcs	pc, [r4], #2271	; 0x8df	; <UNPREDICTABLE>
d00128bc:	e006447a 	and	r4, r6, sl, ror r4
d00128c0:	e7e44602 	strb	r4, [r4, r2, lsl #12]!
d00128c4:	b95a6da2 	ldmdblt	sl, {r1, r5, r7, r8, sl, fp, sp, lr}^
d00128c8:	24e8f8df 	strbtcs	pc, [r8], #2271	; 0x8df	; <UNPREDICTABLE>
d00128cc:	e9c4447a 	stmib	r4, {r1, r3, r4, r5, r6, sl, lr}^
d00128d0:	9a082516 	bls	0xd021bd30
d00128d4:	2a18e9c4 	bcs	0xd064cfec
d00128d8:	66a29a09 	strtvs	r9, [r2], r9, lsl #20
d00128dc:	d1e9e000 	mvnle	lr, r0
d00128e0:	42be4666 	adcsmi	r4, lr, #106954752	; 0x6600000
d00128e4:	f816d906 			; <UNDEFINED> instruction: 0xf816d906
d00128e8:	1e712c01 	cdpne	12, 7, cr2, cr1, cr1, {0}
d00128ec:	d0242a20 	eorle	r2, r4, r0, lsr #20
d00128f0:	d0222a09 	eorle	r2, r2, r9, lsl #20
d00128f4:	93114620 	tstls	r1, #32, 12	; 0x2000000
d00128f8:	fcaef7fd 	stc2	7, cr15, [lr], #1012	; 0x3f4
d00128fc:	46809b0c 	strmi	r9, [r0], ip, lsl #22
d0012900:	000bea43 	andeq	lr, fp, r3, asr #20
d0012904:	43039b0d 	movwmi	r9, #15117	; 0x3b0d
d0012908:	f0009b11 			; <UNDEFINED> instruction: 0xf0009b11
d001290c:	f24d8090 	vqadd.s8	d24, d29, d0
d0012910:	58e3030c 	stmiapl	r3!, {r2, r3, r8, r9}^
d0012914:	d1122b20 	tstle	r2, r0, lsr #22
d0012918:	2b006da3 	blcs	0xd002dfac
d001291c:	af7bf47f 	svcge	0x007bf47f
d0012920:	3494f8df 	ldrcc	pc, [r4], #2271	; 0x8df
d0012924:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0012928:	9b083516 	blls	0xd021fd88
d001292c:	3a18e9c4 	bcc	0xd064d044
d0012930:	66a39b09 	strtvs	r9, [r3], r9, lsl #22
d0012934:	4694e76f 	ldrmi	lr, [r4], pc, ror #14
d0012938:	460ee798 			; <UNDEFINED> instruction: 0x460ee798
d001293c:	f1b8e7d1 			; <UNDEFINED> instruction: 0xf1b8e7d1
d0012940:	d0720f00 	rsbsle	r0, r2, r0, lsl #30
d0012944:	d0542800 	subsle	r2, r4, r0, lsl #16
d0012948:	d00542be 			; <UNDEFINED> instruction: 0xd00542be
d001294c:	9a109b0f 	bls	0xd0439590
d0012950:	f7fd5c98 			; <UNDEFINED> instruction: 0xf7fd5c98
d0012954:	b958fd18 	ldmdblt	r8, {r3, r4, r8, sl, fp, ip, sp, lr, pc}^
d0012958:	b94b6da3 	stmdblt	fp, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d001295c:	345cf8df 	ldrbcc	pc, [ip], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d0012960:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0012964:	9b083516 	blls	0xd021fdc4
d0012968:	3a18e9c4 	bcc	0xd064d080
d001296c:	66a39b09 	strtvs	r9, [r3], r9, lsl #22
d0012970:	454e46b9 	strbmi	r4, [lr, #-1721]	; 0xfffff947
d0012974:	d917464a 	ldmdble	r7, {r1, r3, r6, r9, sl, lr}
d0012978:	f1097811 			; <UNDEFINED> instruction: 0xf1097811
d001297c:	46080901 	strmi	r0, [r8], -r1, lsl #18
d0012980:	fd01f7fd 	stc2	7, cr15, [r1, #-1012]	; 0xfffffc0c
d0012984:	d1f42800 	mvnsle	r2, r0, lsl #16
d0012988:	29093930 	stmdbcs	r9, {r4, r5, r8, fp, ip, sp}
d001298c:	6da3d9f1 			; <UNDEFINED> instruction: 0x6da3d9f1
d0012990:	f8dfb95b 			; <UNDEFINED> instruction: 0xf8dfb95b
d0012994:	447b342c 	ldrbtmi	r3, [fp], #-1068	; 0xfffffbd4
d0012998:	3516e9c4 	ldrcc	lr, [r6, #-2500]	; 0xfffff63c
d001299c:	e9c49b08 	stmib	r4, {r3, r8, r9, fp, ip, pc}^
d00129a0:	9b093a18 	blls	0xd0261208
d00129a4:	e00066a3 	and	r6, r0, r3, lsr #13
d00129a8:	1bd2d1f1 	blne	0xcf4c7174
d00129ac:	46204639 			; <UNDEFINED> instruction: 0x46204639
d00129b0:	fcc7f7fd 	stc2l	7, cr15, [r7], {253}	; 0xfd
d00129b4:	0f00f1bb 	svceq	0x0000f1bb
d00129b8:	43c0d100 	bicmi	sp, r0, #0, 2
d00129bc:	f24d0fc0 	vmax.f32	q8, <illegal reg q14.5>, q0
d00129c0:	f1b8030c 			; <UNDEFINED> instruction: 0xf1b8030c
d00129c4:	58e10f00 	stmiapl	r1!, {r8, r9, sl, fp}^
d00129c8:	2000bf08 	andcs	fp, r0, r8, lsl #30
d00129cc:	50e21c4a 	rscpl	r1, r2, sl, asr #24
d00129d0:	0481eb04 	streq	lr, [r1], #2820	; 0xb04
d00129d4:	738cf64c 	orrvc	pc, ip, #76, 12	; 0x4c00000
d00129d8:	f8042200 			; <UNDEFINED> instruction: 0xf8042200
d00129dc:	f64c8003 			; <UNDEFINED> instruction: 0xf64c8003
d00129e0:	54e0738d 	strbtpl	r7, [r0], #909	; 0x38d
d00129e4:	738ef64c 	orrvc	pc, lr, #76, 12	; 0x4c00000
d00129e8:	f64c54e0 			; <UNDEFINED> instruction: 0xf64c54e0
d00129ec:	54e2738f 	strbtpl	r7, [r2], #911	; 0x38f
d00129f0:	2200e711 	andcs	lr, r0, #4456448	; 0x440000
d00129f4:	96062300 	strls	r2, [r6], -r0, lsl #6
d00129f8:	9705ae29 	strls	sl, [r5, -r9, lsr #28]
d00129fc:	e9cd466d 	stmib	sp, {r0, r2, r3, r5, r6, r9, sl, lr}^
d0012a00:	ab122312 	blge	0xd049b650
d0012a04:	ce0f9307 	cdpgt	3, 0, cr9, cr15, cr7, {0}
d0012a08:	6833c50f 	ldmdavs	r3!, {r0, r1, r2, r3, r8, sl, lr, pc}
d0012a0c:	602b4620 	eorvs	r4, fp, r0, lsr #12
d0012a10:	cb0eab26 	blgt	0xd03bd6b0
d0012a14:	fb62f7fe 	blx	0xd18d0a16
d0012a18:	d0d02800 	sbcsle	r2, r0, r0, lsl #16
d0012a1c:	2312e9dd 	tstcs	r2, #3620864	; 0x374000
d0012a20:	bf144313 	svclt	0x00144313
d0012a24:	20002001 	andcs	r2, r0, r1
d0012a28:	4640e7c9 	strbmi	lr, [r0], -r9, asr #15
d0012a2c:	9a0ee7c7 	bls	0xd03cc950
d0012a30:	0002ea49 	andeq	lr, r2, r9, asr #20
d0012a34:	0203ea50 	andeq	lr, r3, #80, 20	; 0x50000
d0012a38:	80a2f000 	adchi	pc, r2, r0
d0012a3c:	21fcf8d4 	ldrsbcs	pc, [ip, #132]!	; 0x84	; <UNPREDICTABLE>
d0012a40:	eb04b112 	bl	0xd013ee90
d0012a44:	6f921242 	svcvs	0x00921242
d0012a48:	010cf24d 	tsteq	ip, sp, asr #4	; <UNPREDICTABLE>
d0012a4c:	42915861 	addsmi	r5, r1, #6356992	; 0x610000
d0012a50:	6da3d806 	stcvs	8, cr13, [r3, #24]!
d0012a54:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0012a58:	4bdaaede 	blmi	0xcf6be5d8
d0012a5c:	e762447b 			; <UNDEFINED> instruction: 0xe762447b
d0012a60:	f1b91e4a 			; <UNDEFINED> instruction: 0xf1b91e4a
d0012a64:	d0100f00 	andsle	r0, r0, r0, lsl #30
d0012a68:	d00a42be 			; <UNDEFINED> instruction: 0xd00a42be
d0012a6c:	b9436da3 	stmdblt	r3, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0012a70:	447b4bd5 	ldrbtmi	r4, [fp], #-3029	; 0xfffff42b
d0012a74:	3516e9c4 	ldrcc	lr, [r6, #-2500]	; 0xfffff63c
d0012a78:	e9c49b08 	stmib	r4, {r3, r8, r9, fp, ip, pc}^
d0012a7c:	9b093a18 	blls	0xd02612e4
d0012a80:	f24d66a3 	vmax.s8	d22, d29, d19
d0012a84:	50e2030c 	rscpl	r0, r2, ip, lsl #6
d0012a88:	ea4fe6c5 	b	0xd140c5a4
d0012a8c:	b3630881 	cmnlt	r3, #8454144	; 0x810000
d0012a90:	d10642be 			; <UNDEFINED> instruction: 0xd10642be
d0012a94:	534ff502 	movtpl	pc, #62722	; 0xf502	; <UNPREDICTABLE>
d0012a98:	eb043322 	bl	0xd011f728
d0012a9c:	79db0383 	ldmibvc	fp, {r0, r1, r7, r8, r9}^
d0012aa0:	6da3b153 	stfvsd	f3, [r3, #332]!	; 0x14c
d0012aa4:	4bc9b943 	blmi	0xcf280fb8
d0012aa8:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0012aac:	9b083516 	blls	0xd021ff0c
d0012ab0:	3a18e9c4 	bcc	0xd064d1c8
d0012ab4:	66a39b09 	strtvs	r9, [r3], r9, lsl #22
d0012ab8:	f64c4444 			; <UNDEFINED> instruction: 0xf64c4444
d0012abc:	5ce37388 	stclpl	3, cr7, [r3], #544	; 0x220
d0012ac0:	f64cb13b 			; <UNDEFINED> instruction: 0xf64cb13b
d0012ac4:	f814738a 			; <UNDEFINED> instruction: 0xf814738a
d0012ac8:	fab99003 	blx	0xcee76adc
d0012acc:	ea4ff989 	b	0xd14110f8
d0012ad0:	f64c1959 			; <UNDEFINED> instruction: 0xf64c1959
d0012ad4:	f64c7389 			; <UNDEFINED> instruction: 0xf64c7389
d0012ad8:	f804728a 			; <UNDEFINED> instruction: 0xf804728a
d0012adc:	23019003 	movwcs	r9, #4099	; 0x1003
d0012ae0:	f64c54a3 			; <UNDEFINED> instruction: 0xf64c54a3
d0012ae4:	54a3728b 	strtpl	r7, [r3], #651	; 0x28b
d0012ae8:	44a0e695 	strtmi	lr, [r0], #1685	; 0x695
d0012aec:	738bf64c 	orrvc	pc, fp, #76, 12	; 0x4c00000
d0012af0:	3003f818 	andcc	pc, r3, r8, lsl r8	; <UNPREDICTABLE>
d0012af4:	6da3b153 	stfvsd	f3, [r3, #332]!	; 0x14c
d0012af8:	4bb5b943 	blmi	0xced8100c
d0012afc:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0012b00:	9b083516 	blls	0xd021ff60
d0012b04:	3a18e9c4 	bcc	0xd064d21c
d0012b08:	66a39b09 	strtvs	r9, [r3], r9, lsl #22
d0012b0c:	22002300 	andcs	r2, r0, #0, 6
d0012b10:	2312e9cd 	tstcs	r2, #3358720	; 0x334000
d0012b14:	7388f64c 	orrvc	pc, r8, #76, 12	; 0x4c00000
d0012b18:	3003f818 	andcc	pc, r3, r8, lsl r8	; <UNPREDICTABLE>
d0012b1c:	f64cb923 			; <UNDEFINED> instruction: 0xf64cb923
d0012b20:	f8087289 			; <UNDEFINED> instruction: 0xf8087289
d0012b24:	e6763002 	ldrbt	r3, [r6], -r2
d0012b28:	798af64c 	stmibvc	sl, {r2, r3, r6, r9, sl, ip, sp, lr, pc}
d0012b2c:	3009f818 	andcc	pc, r9, r8, lsl r8	; <UNPREDICTABLE>
d0012b30:	f64cb12b 			; <UNDEFINED> instruction: 0xf64cb12b
d0012b34:	22007389 	andcs	r7, r0, #603979778	; 0x24000002
d0012b38:	2003f808 	andcs	pc, r3, r8, lsl #16
d0012b3c:	9606e66b 	strls	lr, [r6], -fp, ror #12
d0012b40:	ae29ab12 	vmovge.32	d9[1], sl
d0012b44:	93079705 	movwls	r9, #30469	; 0x7705
d0012b48:	ce0f466d 	cfmadd32gt	mvax3, mvfx4, mvfx15, mvfx13
d0012b4c:	6833c50f 	ldmdavs	r3!, {r0, r1, r2, r3, r8, sl, lr, pc}
d0012b50:	602b4620 	eorvs	r4, fp, r0, lsr #12
d0012b54:	cb0eab26 	blgt	0xd03bd7f4
d0012b58:	fac0f7fe 	blx	0xcf050b58
d0012b5c:	2312e9dd 	tstcs	r2, #3620864	; 0x374000
d0012b60:	0103ea52 	tsteq	r3, r2, asr sl
d0012b64:	7189f64c 	orrvc	pc, r9, ip, asr #12
d0012b68:	2001bf14 	andcs	fp, r1, r4, lsl pc
d0012b6c:	43132000 	tstmi	r3, #0
d0012b70:	0001f808 	andeq	pc, r1, r8, lsl #16
d0012b74:	ae4ff43f 	mcrge	4, 2, pc, cr15, cr15, {1}	; <UNPREDICTABLE>
d0012b78:	f8082301 			; <UNDEFINED> instruction: 0xf8082301
d0012b7c:	e64a3009 	strb	r3, [sl], -r9
d0012b80:	0f00f1b8 	svceq	0x0000f1b8
d0012b84:	ae47f43f 	mcrge	4, 2, pc, cr7, cr15, {1}	; <UNPREDICTABLE>
d0012b88:	9a0a9b0b 	bls	0xd02b97bc
d0012b8c:	f43f4313 			; <UNDEFINED> instruction: 0xf43f4313
d0012b90:	42beae42 	adcsmi	sl, lr, #1056	; 0x420
d0012b94:	9b0fd023 	blls	0xd0406c28
d0012b98:	5c989a10 	vldmiapl	r8, {s18-s33}
d0012b9c:	fbf3f7fd 	blx	0xcfd10b9a
d0012ba0:	46b8b1e8 	ldrtmi	fp, [r8], r8, ror #3
d0012ba4:	46434546 	strbmi	r4, [r3], -r6, asr #10
d0012ba8:	4642d90d 	strbmi	sp, [r2], -sp, lsl #18
d0012bac:	802cf8cd 	eorhi	pc, ip, sp, asr #17
d0012bb0:	1b01f812 	blne	0xd0090c00
d0012bb4:	f7fd4608 			; <UNDEFINED> instruction: 0xf7fd4608
d0012bb8:	b9b8fbe6 	ldmiblt	r8!, {r1, r2, r5, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d0012bbc:	0030f1a1 	eorseq	pc, r0, r1, lsr #3
d0012bc0:	28099b0b 	stmdacs	r9, {r0, r1, r3, r8, r9, fp, ip, pc}
d0012bc4:	eba8d912 	bl	0xcea49014
d0012bc8:	f1bb0b07 			; <UNDEFINED> instruction: 0xf1bb0b07
d0012bcc:	d90f0f3f 	stmdble	pc, {r0, r1, r2, r3, r4, r5, r8, r9, sl, fp}	; <UNPREDICTABLE>
d0012bd0:	2b006da3 	blcs	0xd002e264
d0012bd4:	ae1ff47f 	mrcge	4, 0, APSR_nzcv, cr15, cr15, {3}
d0012bd8:	447b4b7e 	ldrbtmi	r4, [fp], #-2942	; 0xfffff482
d0012bdc:	6da3e6a3 	stcvs	6, cr14, [r3, #652]!	; 0x28c
d0012be0:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0012be4:	4b7cae18 	blmi	0xd1f3e44c
d0012be8:	e69c447b 			; <UNDEFINED> instruction: 0xe69c447b
d0012bec:	e7d94690 	bfi	r4, r0, #13, #13
d0012bf0:	4639465a 			; <UNDEFINED> instruction: 0x4639465a
d0012bf4:	930b4620 	movwls	r4, #46624	; 0xb620
d0012bf8:	fba3f7fd 	blx	0xce910bf6
d0012bfc:	46819a0a 	strmi	r9, [r1], sl, lsl #20
d0012c00:	b34a9b0b 	movtlt	r9, #43787	; 0xab0b
d0012c04:	d9114546 	ldmdble	r1, {r1, r2, r6, r8, sl, lr}
d0012c08:	3b01f818 	blcc	0xd0090c70
d0012c0c:	d0f92b20 	rscsle	r2, r9, r0, lsr #22
d0012c10:	d0f72b09 	rscsle	r2, r7, r9, lsl #22
d0012c14:	b9536da3 	ldmdblt	r3, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0012c18:	447b4b70 	ldrbtmi	r4, [fp], #-2928	; 0xfffff490
d0012c1c:	3516e9c4 	ldrcc	lr, [r6, #-2500]	; 0xfffff63c
d0012c20:	e9c49b08 	stmib	r4, {r3, r8, r9, fp, ip, pc}^
d0012c24:	9b093a18 	blls	0xd026148c
d0012c28:	e00066a3 	and	r6, r0, r3, lsr #13
d0012c2c:	f1b9d1f2 			; <UNDEFINED> instruction: 0xf1b9d1f2
d0012c30:	f6ff0f00 			; <UNDEFINED> instruction: 0xf6ff0f00
d0012c34:	f64cadf0 			; <UNDEFINED> instruction: 0xf64cadf0
d0012c38:	22487388 	subcs	r7, r8, #136, 6	; 0x20000002
d0012c3c:	fb0258e1 	blx	0xd00a8fca
d0012c40:	39014009 	stmdbcc	r1, {r0, r3, lr}
d0012c44:	f64a50e1 			; <UNDEFINED> instruction: 0xf64a50e1
d0012c48:	fb023388 	blx	0xd009fa72
d0012c4c:	44184101 	ldrmi	r4, [r8], #-257	; 0xfffffeff
d0012c50:	f00c4419 			; <UNDEFINED> instruction: 0xf00c4419
d0012c54:	e5defbd5 	ldrb	pc, [lr, #3029]	; 0xbd5	; <UNPREDICTABLE>
d0012c58:	d9134546 	ldmdble	r3, {r1, r2, r6, r8, sl, lr}
d0012c5c:	3000f898 	mulcc	r0, r8, r8
d0012c60:	d1062b28 	tstle	r6, r8, lsr #22
d0012c64:	2b006da3 	blcs	0xd002e2f8
d0012c68:	add5f47f 	cfldrdge	mvd15, [r5, #508]	; 0x1fc
d0012c6c:	447b4b5c 	ldrbtmi	r4, [fp], #-2908	; 0xfffff4a4
d0012c70:	4546e659 	strbmi	lr, [r6, #-1625]	; 0xfffff9a7
d0012c74:	d0054643 	andle	r4, r5, r3, asr #12
d0012c78:	2b01f818 	blcs	0xd0090ce0
d0012c7c:	d0f82a20 	rscsle	r2, r8, r0, lsr #20
d0012c80:	d0f62a09 	rscsle	r2, r6, r9, lsl #20
d0012c84:	21002001 	tstcs	r0, r1
d0012c88:	e9cd429e 	stmib	sp, {r1, r2, r3, r4, r7, r9, lr}^
d0012c8c:	d0130112 	andsle	r0, r3, r2, lsl r1
d0012c90:	aa129606 	bge	0xd04b84b0
d0012c94:	9305ae29 	movwls	sl, #24105	; 0x5e29
d0012c98:	46ec9207 	strbtmi	r9, [ip], r7, lsl #4
d0012c9c:	e8acce0f 	stmia	ip!, {r0, r1, r2, r3, r9, sl, fp, lr, pc}
d0012ca0:	6833000f 	ldmdavs	r3!, {r0, r1, r2, r3}
d0012ca4:	f8cc4620 			; <UNDEFINED> instruction: 0xf8cc4620
d0012ca8:	ab263000 	blge	0xd099ecb0
d0012cac:	f7fecb0e 			; <UNDEFINED> instruction: 0xf7fecb0e
d0012cb0:	2800fa15 	stmdacs	r0, {r0, r2, r4, r9, fp, ip, sp, lr, pc}
d0012cb4:	adaff43f 	cfstrsge	mvf15, [pc, #252]!	; 0xd0012db8
d0012cb8:	0f00f1b9 	svceq	0x0000f1b9
d0012cbc:	f64cda0e 			; <UNDEFINED> instruction: 0xf64cda0e
d0012cc0:	58e07388 	stmiapl	r0!, {r3, r7, r8, r9, ip, sp, lr}^
d0012cc4:	d1062880 	smlabble	r6, r0, r8, r2
d0012cc8:	2b006da3 	blcs	0xd002e35c
d0012ccc:	ada3f47f 	cfstrsge	mvf15, [r3, #508]!	; 0x1fc
d0012cd0:	447b4b44 	ldrbtmi	r4, [fp], #-2884	; 0xfffff4bc
d0012cd4:	1c42e627 	mcrrne	6, 2, lr, r2, cr7
d0012cd8:	50e24681 	rscpl	r4, r2, r1, lsl #13
d0012cdc:	f64a2048 			; <UNDEFINED> instruction: 0xf64a2048
d0012ce0:	465a3588 	ldrbmi	r3, [sl], -r8, lsl #11
d0012ce4:	fb004639 	blx	0xd00245d2
d0012ce8:	eb09f909 	bl	0xd0291114
d0012cec:	44200005 	strtmi	r0, [r0], #-5
d0012cf0:	f00c444c 			; <UNDEFINED> instruction: 0xf00c444c
d0012cf4:	2300fb85 	movwcs	pc, #2949	; 0xb85	; <UNPREDICTABLE>
d0012cf8:	f50444a3 			; <UNDEFINED> instruction: 0xf50444a3
d0012cfc:	f80b442b 			; <UNDEFINED> instruction: 0xf80b442b
d0012d00:	e9dd3005 	ldmib	sp, {r0, r2, ip, sp}^
d0012d04:	e9c42312 	stmib	r4, {r1, r4, r8, r9, sp}^
d0012d08:	e5842332 	str	r2, [r4, #818]	; 0x332
d0012d0c:	f47f2a05 			; <UNDEFINED> instruction: 0xf47f2a05
d0012d10:	4935abc2 	ldmdbmi	r5!, {r1, r6, r7, r8, r9, fp, sp, pc}
d0012d14:	920b4638 	andls	r4, fp, #56, 12	; 0x3800000
d0012d18:	447946cb 	ldrbtmi	r4, [r9], #-1739	; 0xfffff935
d0012d1c:	f00c46c8 			; <UNDEFINED> instruction: 0xf00c46c8
d0012d20:	fab0fb7f 	blx	0xcec51b24
d0012d24:	4931f380 	ldmdbmi	r1!, {r7, r8, r9, ip, sp, lr, pc}
d0012d28:	095b4638 	ldmdbeq	fp, {r3, r4, r5, r9, sl, lr}^
d0012d2c:	44799a0b 	ldrbtmi	r9, [r9], #-2571	; 0xfffff5f5
d0012d30:	930a464e 	movwls	r4, #42574	; 0xa64e
d0012d34:	fb74f00c 	blx	0xd1d4ed6e
d0012d38:	f380fab0 			; <UNDEFINED> instruction: 0xf380fab0
d0012d3c:	902cf8cd 	eorls	pc, ip, sp, asr #17
d0012d40:	930c095b 	movwls	r0, #51547	; 0xc95b
d0012d44:	2205492a 	andcs	r4, r5, #688128	; 0xa8000
d0012d48:	44794638 	ldrbtmi	r4, [r9], #-1592	; 0xfffff9c8
d0012d4c:	fb68f00c 	blx	0xd1a4ed86
d0012d50:	fab02300 	blx	0xcec1b958
d0012d54:	930ef980 	movwls	pc, #59776	; 0xe980	; <UNPREDICTABLE>
d0012d58:	1959ea4f 	ldmdbne	r9, {r0, r1, r2, r3, r6, r9, fp, sp, lr, pc}^
d0012d5c:	f7ff930d 			; <UNDEFINED> instruction: 0xf7ff930d
d0012d60:	bf00bbd5 	svclt	0x0000bbd5
d0012d64:	fffffc50 			; <UNDEFINED> instruction: 0xfffffc50
d0012d68:	fffffc10 			; <UNDEFINED> instruction: 0xfffffc10
d0012d6c:	fffffc07 			; <UNDEFINED> instruction: 0xfffffc07
d0012d70:	fffffbf8 			; <UNDEFINED> instruction: 0xfffffbf8
d0012d74:	fffffbd6 			; <UNDEFINED> instruction: 0xfffffbd6
d0012d78:	fffffbc5 			; <UNDEFINED> instruction: 0xfffffbc5
d0012d7c:	fffffb93 			; <UNDEFINED> instruction: 0xfffffb93
d0012d80:	fffffade 			; <UNDEFINED> instruction: 0xfffffade
d0012d84:	fffffb08 			; <UNDEFINED> instruction: 0xfffffb08
d0012d88:	fffffa8e 			; <UNDEFINED> instruction: 0xfffffa8e
d0012d8c:	fffffaaa 			; <UNDEFINED> instruction: 0xfffffaaa
d0012d90:	fffffa7f 			; <UNDEFINED> instruction: 0xfffffa7f
d0012d94:	fffffafc 			; <UNDEFINED> instruction: 0xfffffafc
d0012d98:	fffffa36 			; <UNDEFINED> instruction: 0xfffffa36
d0012d9c:	fffffa29 			; <UNDEFINED> instruction: 0xfffffa29
d0012da0:	fffff9e6 			; <UNDEFINED> instruction: 0xfffff9e6
d0012da4:	fffffa01 			; <UNDEFINED> instruction: 0xfffffa01
d0012da8:	fffff9c6 			; <UNDEFINED> instruction: 0xfffff9c6
d0012dac:	fffff890 			; <UNDEFINED> instruction: 0xfffff890
d0012db0:	fffff925 			; <UNDEFINED> instruction: 0xfffff925
d0012db4:	fffff8ea 			; <UNDEFINED> instruction: 0xfffff8ea
d0012db8:	fffff8e5 			; <UNDEFINED> instruction: 0xfffff8e5
d0012dbc:	fffff8c8 			; <UNDEFINED> instruction: 0xfffff8c8
d0012dc0:	fffff8bb 			; <UNDEFINED> instruction: 0xfffff8bb
d0012dc4:	fffff81d 			; <UNDEFINED> instruction: 0xfffff81d
d0012dc8:	fffff82f 			; <UNDEFINED> instruction: 0xfffff82f
d0012dcc:	fffff816 			; <UNDEFINED> instruction: 0xfffff816
d0012dd0:	fffff7dd 			; <UNDEFINED> instruction: 0xfffff7dd
d0012dd4:	fffff736 			; <UNDEFINED> instruction: 0xfffff736
d0012dd8:	fffff703 			; <UNDEFINED> instruction: 0xfffff703
d0012ddc:	fffff717 			; <UNDEFINED> instruction: 0xfffff717
d0012de0:	fffff6e0 			; <UNDEFINED> instruction: 0xfffff6e0
d0012de4:	fffff6ab 			; <UNDEFINED> instruction: 0xfffff6ab
d0012de8:	fffff357 			; <UNDEFINED> instruction: 0xfffff357
d0012dec:	fffff349 			; <UNDEFINED> instruction: 0xfffff349
d0012df0:	fffff340 			; <UNDEFINED> instruction: 0xfffff340

Disassembly of section .text.advance:

d0012df4 <.text.advance>:
d0012df4:	f100b570 			; <UNDEFINED> instruction: 0xf100b570
d0012df8:	46040638 			; <UNDEFINED> instruction: 0x46040638
d0012dfc:	0518f100 	ldreq	pc, [r8, #-256]	; 0xffffff00
d0012e00:	ce0fb088 	cdpgt	0, 0, cr11, cr15, cr8, {4}
d0012e04:	e896c50f 	ldm	r6, {r0, r1, r2, r3, r8, sl, lr, pc}
d0012e08:	e885000f 	stm	r5, {r0, r1, r2, r3}
d0012e0c:	466d000f 	strbtmi	r0, [sp], -pc
d0012e10:	34384621 	ldrtcc	r4, [r8], #-1569	; 0xfffff9df
d0012e14:	f7fe4628 			; <UNDEFINED> instruction: 0xf7fe4628
d0012e18:	cd0ffd5f 	stcgt	13, cr15, [pc, #-380]	; 0xd0012ca4
d0012e1c:	e895c40f 	ldm	r5, {r0, r1, r2, r3, sl, lr, pc}
d0012e20:	e884000f 	stm	r4, {r0, r1, r2, r3}
d0012e24:	b008000f 	andlt	r0, r8, pc
d0012e28:	Address 0x00000000d0012e28 is out of bounds.


Disassembly of section .text.accept:

d0012e2a <.text.accept>:
d0012e2a:	6d83b508 	cfstr32vs	mvfx11, [r3, #32]
d0012e2e:	6ac2b933 	bvs	0xcf0c1302
d0012e32:	d105428a 	smlabble	r5, sl, r2, r4
d0012e36:	ffddf7ff 			; <UNDEFINED> instruction: 0xffddf7ff
d0012e3a:	bd082001 	stclt	0, cr2, [r8, #-4]
d0012e3e:	e7fc2000 	ldrb	r2, [ip, r0]!
d0012e42:	e7fa4618 			; <UNDEFINED> instruction: 0xe7fa4618

Disassembly of section .text.expect:

d0012e46 <.text.expect>:
d0012e46:	4605b570 			; <UNDEFINED> instruction: 0x4605b570
d0012e4a:	f7ff4616 			; <UNDEFINED> instruction: 0xf7ff4616
d0012e4e:	4604ffed 	strmi	pc, [r4], -sp, ror #31
d0012e52:	4631b928 	ldrtmi	fp, [r1], -r8, lsr #18
d0012e56:	f7fd4628 			; <UNDEFINED> instruction: 0xf7fd4628
d0012e5a:	4620f9a6 	strtmi	pc, [r0], -r6, lsr #19
d0012e5e:	2401bd70 	strcs	fp, [r1], #-3440	; 0xfffff290
d0012e62:	Address 0x00000000d0012e62 is out of bounds.


Disassembly of section .text.enum_expression:

d0012f5c <.text.enum_expression>:
d0012f5c:	e92d2a19 	push	{r0, r3, r4, r9, fp, sp}
d0012f60:	46804ff8 			; <UNDEFINED> instruction: 0x46804ff8
d0012f64:	4692468b 	ldrmi	r4, [r2], fp, lsl #13
d0012f68:	4995d106 	ldmibmi	r5, {r1, r2, r8, ip, lr, pc}
d0012f6c:	f7fd4479 			; <UNDEFINED> instruction: 0xf7fd4479
d0012f70:	2400f91b 	strcs	pc, [r0], #-2331	; 0xfffff6e5
d0012f74:	e0f82500 	rscs	r2, r8, r0, lsl #10
d0012f78:	2e2b6ac6 	vnmulcs.f32	s12, s23, s12
d0012f7c:	2e2dd003 	cdpcs	0, 2, cr13, cr13, cr3, {0}
d0012f80:	2e7ed001 	cdpcs	0, 7, cr13, cr14, cr1, {0}
d0012f84:	4640d133 			; <UNDEFINED> instruction: 0x4640d133
d0012f88:	ff34f7ff 			; <UNDEFINED> instruction: 0xff34f7ff
d0012f8c:	0201f10a 	andeq	pc, r1, #-2147483646	; 0x80000002
d0012f90:	46402107 	strbmi	r2, [r0], -r7, lsl #2
d0012f94:	ffe2f7ff 			; <UNDEFINED> instruction: 0xffe2f7ff
d0012f98:	46042e2d 	strmi	r2, [r4], -sp, lsr #28
d0012f9c:	d11f460d 	tstle	pc, sp, lsl #12
d0012fa0:	eb614244 	bl	0xd18638b8
d0012fa4:	f8d80541 			; <UNDEFINED> instruction: 0xf8d80541
d0012fa8:	2e006058 	mcrcs	0, 0, r6, cr0, cr8, {2}
d0012fac:	80ddf040 	sbcshi	pc, sp, r0, asr #32
d0012fb0:	902cf8d8 	ldrdls	pc, [ip], -r8	; <UNPREDICTABLE>
d0012fb4:	0f5ef1b9 	svceq	0x005ef1b9
d0012fb8:	80ebf000 	rschi	pc, fp, r0
d0012fbc:	80d9f300 	sbcshi	pc, r9, r0, lsl #6
d0012fc0:	0325f1a9 	msreq	CPSR_sc, #1073741866	; 0x4000002a
d0012fc4:	f2002b0a 	vqdmulh.s<illegal width 8>	d2, d0, d10
d0012fc8:	2b0a80cd 	blcs	0xd02b3304
d0012fcc:	80dff200 	sbcshi	pc, pc, r0, lsl #4
d0012fd0:	f003e8df 			; <UNDEFINED> instruction: 0xf003e8df
d0012fd4:	dddde1db 	ldflep	f6, [sp, #876]	; 0x36c
d0012fd8:	ddc7dbdd 	vstrle	d29, [r7, #884]	; 0x374
d0012fdc:	00dbddc7 	sbcseq	sp, fp, r7, asr #27
d0012fe0:	d1e02e7e 	mvnle	r2, lr, ror lr
d0012fe4:	43cb43c2 	bicmi	r4, fp, #134217731	; 0x8000003
d0012fe8:	461d4614 			; <UNDEFINED> instruction: 0x461d4614
d0012fec:	2128e7db 	ldrdcs	lr, [r8, -fp]!
d0012ff0:	ff1bf7ff 			; <UNDEFINED> instruction: 0xff1bf7ff
d0012ff4:	f10ab170 			; <UNDEFINED> instruction: 0xf10ab170
d0012ff8:	46400201 	strbmi	r0, [r0], -r1, lsl #4
d0012ffc:	f7ff2101 			; <UNDEFINED> instruction: 0xf7ff2101
d0013000:	4a70ffad 	bmi	0xd1c52ebc
d0013004:	460d4604 	strmi	r4, [sp], -r4, lsl #12
d0013008:	2129447a 			; <UNDEFINED> instruction: 0x2129447a
d001300c:	f7ff4640 			; <UNDEFINED> instruction: 0xf7ff4640
d0013010:	e7c8ff1a 	bfi	pc, sl, (invalid: 30:8)	; <UNPREDICTABLE>
d0013014:	302cf8d8 	ldrdcc	pc, [ip], -r8	; <UNPREDICTABLE>
d0013018:	7281f5a3 	addvc	pc, r1, #683671552	; 0x28c00000
d001301c:	d80a2a01 	stmdale	sl, {r0, r9, fp, sp}
d0013020:	7f81f5b3 	svcvc	0x0081f5b3
d0013024:	4020f8d8 	ldrdmi	pc, [r0], -r8	; <UNPREDICTABLE>
d0013028:	bf0c4640 	svclt	0x000c4640
d001302c:	250017e5 	strcs	r1, [r0, #-2021]	; 0xfffff81b
d0013030:	fee0f7ff 	mcr2	7, 7, pc, cr0, cr15, {7}	; <UNPREDICTABLE>
d0013034:	4964e7b7 	stmdbmi	r4!, {r0, r1, r2, r4, r5, r7, r8, r9, sl, sp, lr, pc}^
d0013038:	46404479 			; <UNDEFINED> instruction: 0x46404479
d001303c:	4640e797 			; <UNDEFINED> instruction: 0x4640e797
d0013040:	fed8f7ff 	mrc2	7, 6, pc, cr8, cr15, {7}
d0013044:	f10a1c71 			; <UNDEFINED> instruction: 0xf10a1c71
d0013048:	46400201 	strbmi	r0, [r0], -r1, lsl #4
d001304c:	ff86f7ff 			; <UNDEFINED> instruction: 0xff86f7ff
d0013050:	3058f8d8 	ldrsbcc	pc, [r8], #-136	; 0xffffff78	; <UNPREDICTABLE>
d0013054:	460f4606 	strmi	r4, [pc], -r6, lsl #12
d0013058:	d18a2b00 	orrle	r2, sl, r0, lsl #22
d001305c:	0f2ff1b9 	svceq	0x002ff1b9
d0013060:	80a7f000 	adchi	pc, r7, r0
d0013064:	0f25f1b9 	svceq	0x0025f1b9
d0013068:	ea56d115 	b	0xd15c74c4
d001306c:	f0000307 			; <UNDEFINED> instruction: 0xf0000307
d0013070:	1c6b80a3 	stclne	0, cr8, [fp], #-652	; 0xfffffd74
d0013074:	f1b4bf08 			; <UNDEFINED> instruction: 0xf1b4bf08
d0013078:	d0044f00 	andle	r4, r4, r0, lsl #30
d001307c:	f3f6fb94 			; <UNDEFINED> instruction: 0xf3f6fb94
d0013080:	4416fb03 	ldrmi	pc, [r6], #-2819	; 0xfffff4fd
d0013084:	1c7be093 	ldclne	0, cr14, [fp], #-588	; 0xfffffdb4
d0013088:	f1b6bf08 			; <UNDEFINED> instruction: 0xf1b6bf08
d001308c:	d1023fff 	strdle	r3, [r2, -pc]
d0013090:	4479494e 	ldrbtmi	r4, [r9], #-2382	; 0xfffff6b2
d0013094:	f46fe7d1 	vld1.64	{d30}, [pc :64], r1
d0013098:	eb097093 	bl	0xd026f2ec
d001309c:	2b010300 	blcs	0xd0053ca4
d00130a0:	2f00d806 	svccs	0x0000d806
d00130a4:	2e20bf08 	cdpcs	15, 2, cr11, cr0, cr8, {0}
d00130a8:	4949d32c 	stmdbmi	r9, {r2, r3, r5, r8, r9, ip, lr, pc}^
d00130ac:	e7c44479 			; <UNDEFINED> instruction: 0xe7c44479
d00130b0:	0f5ef1b9 	svceq	0x005ef1b9
d00130b4:	dc29d04b 	stcle	0, cr13, [r9], #-300	; 0xfffffed4
d00130b8:	0925f1a9 	stmdbeq	r5!, {r0, r3, r5, r7, r8, ip, sp, lr, pc}
d00130bc:	0f0af1b9 	svceq	0x000af1b9
d00130c0:	af71f63f 	svcge	0x0071f63f
d00130c4:	0f0af1b9 	svceq	0x000af1b9
d00130c8:	af6df63f 	svcge	0x006df63f
d00130cc:	f853a302 			; <UNDEFINED> instruction: 0xf853a302
d00130d0:	44132029 	ldrmi	r2, [r3], #-41	; 0xffffffd7
d00130d4:	bf004718 	svclt	0x00004718
d00130d8:	ffffffa5 			; <UNDEFINED> instruction: 0xffffffa5
d00130dc:	0000006d 	andeq	r0, r0, sp, rrx
d00130e0:	fffffecf 			; <UNDEFINED> instruction: 0xfffffecf
d00130e4:	fffffecf 			; <UNDEFINED> instruction: 0xfffffecf
d00130e8:	fffffecf 			; <UNDEFINED> instruction: 0xfffffecf
d00130ec:	0000005d 	andeq	r0, r0, sp, asr r0
d00130f0:	0000004d 	andeq	r0, r0, sp, asr #32
d00130f4:	fffffecf 			; <UNDEFINED> instruction: 0xfffffecf
d00130f8:	00000055 	andeq	r0, r0, r5, asr r0
d00130fc:	fffffecf 			; <UNDEFINED> instruction: 0xfffffecf
d0013100:	000000d3 	ldrdeq	r0, [r0], -r3
d0013104:	1327f240 	msrne	CPSR_sxc, #64, 4
d0013108:	d0254599 	mlale	r5, r9, r5, r4
d001310c:	7f94f5b9 	svcvc	0x0094f5b9
d0013110:	f1b9d025 			; <UNDEFINED> instruction: 0xf1b9d025
d0013114:	f47f0f7c 			; <UNDEFINED> instruction: 0xf47f0f7c
d0013118:	ea44af46 	b	0xd113ee38
d001311c:	ea450206 	b	0xd115393c
d0013120:	e7610307 	strb	r0, [r1, -r7, lsl #6]!
d0013124:	eb4719a4 	bl	0xd11d97bc
d0013128:	e73c0505 	ldr	r0, [ip, -r5, lsl #10]!
d001312c:	eb651ba4 	bl	0xd1959fc4
d0013130:	e7380507 	ldr	r0, [r8, -r7, lsl #10]!
d0013134:	f307fb04 	vqrdmulh.s<illegal width 8>	d15, d7, d4
d0013138:	3305fb06 	movwcc	pc, #23302	; 0x5b06	; <UNPREDICTABLE>
d001313c:	4506fba4 	strmi	pc, [r6, #-2980]	; 0xfffff45c
d0013140:	e730441d 			; <UNDEFINED> instruction: 0xe730441d
d0013144:	0206ea04 	andeq	lr, r6, #4, 20	; 0x4000
d0013148:	0307ea05 	movweq	lr, #31237	; 0x7a05
d001314c:	ea84e74c 	b	0xce14ce84
d0013150:	ea850206 	b	0xce153970
d0013154:	e7470307 	strb	r0, [r7, -r7, lsl #6]
d0013158:	250040b4 	strcs	r4, [r0, #-180]	; 0xffffff4c
d001315c:	40f4e723 	rscsmi	lr, r4, r3, lsr #14
d0013160:	2605e7fb 			; <UNDEFINED> instruction: 0x2605e7fb
d0013164:	f77f45b3 			; <UNDEFINED> instruction: 0xf77f45b3
d0013168:	4620af6a 	strtmi	sl, [r0], -sl, ror #30
d001316c:	e8bd4629 	pop	{r0, r3, r5, r9, sl, lr}
d0013170:	f1b98ff8 			; <UNDEFINED> instruction: 0xf1b98ff8
d0013174:	d0100f7c 	andsle	r0, r0, ip, ror pc
d0013178:	7193f46f 	orrsvc	pc, r3, pc, ror #8
d001317c:	0301eb09 	movweq	lr, #6921	; 0x1b09
d0013180:	bf342b02 	svclt	0x00342b02
d0013184:	26002604 	strcs	r2, [r0], -r4, lsl #12
d0013188:	2606e7ec 	strcs	lr, [r6], -ip, ror #15
d001318c:	2600e7ea 	strcs	lr, [r0], -sl, ror #15
d0013190:	2602e7e8 	strcs	lr, [r2], -r8, ror #15
d0013194:	2603e7e6 	strcs	lr, [r3], -r6, ror #15
d0013198:	2601e7e4 	strcs	lr, [r1], -r4, ror #15
d001319c:	1c6ae7e2 	stclne	7, cr14, [sl], #-904	; 0xfffffc78
d00131a0:	f1b4bf08 			; <UNDEFINED> instruction: 0xf1b4bf08
d00131a4:	f43f4f00 			; <UNDEFINED> instruction: 0xf43f4f00
d00131a8:	fb94af6e 	blx	0xce53ef6a
d00131ac:	17e5f4f6 			; <UNDEFINED> instruction: 0x17e5f4f6
d00131b0:	ea56e6f9 	b	0xd15ccd9c
d00131b4:	d1f20307 	mvnsle	r0, r7, lsl #6
d00131b8:	44794906 	ldrbtmi	r4, [r9], #-2310	; 0xfffff6fa
d00131bc:	bf00e73d 	svclt	0x0000e73d
d00131c0:	fffffef4 			; <UNDEFINED> instruction: 0xfffffef4
d00131c4:	fffffe79 			; <UNDEFINED> instruction: 0xfffffe79
d00131c8:	fffffe72 			; <UNDEFINED> instruction: 0xfffffe72
d00131cc:	fffffe76 			; <UNDEFINED> instruction: 0xfffffe76
d00131d0:	fffffe7f 			; <UNDEFINED> instruction: 0xfffffe7f
d00131d4:	fffffd29 			; <UNDEFINED> instruction: 0xfffffd29

Disassembly of section .text.record_type:

d0013240 <.text.record_type>:
d0013240:	4ff7e92d 	svcmi	0x00f7e92d
d0013244:	6ac6460d 	bvs	0xcf1a4a80
d0013248:	718bf46f 	orrvc	pc, fp, pc, ror #8
d001324c:	18734604 	ldmdane	r3!, {r2, r9, sl, lr}^
d0013250:	d8362b01 	ldmdale	r6!, {r0, r8, r9, fp, sp}
d0013254:	fdcef7ff 	stc2l	7, cr15, [lr, #1020]	; 0x3fc
d0013258:	6b634a26 	blvs	0xd18e5af8
d001325c:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d0013260:	4620447a 			; <UNDEFINED> instruction: 0x4620447a
d0013264:	9024f8d4 	ldrdls	pc, [r4], -r4	; <UNPREDICTABLE>
d0013268:	8028f8d4 	ldrdhi	pc, [r8], -r4	; <UNPREDICTABLE>
d001326c:	7030f894 	mlasvc	r0, r4, r8, pc	; <UNPREDICTABLE>
d0013270:	e9d49301 	ldmib	r4, {r0, r8, r9, ip, pc}^
d0013274:	f7ffab06 			; <UNDEFINED> instruction: 0xf7ffab06
d0013278:	b918fde6 	ldmdblt	r8, {r1, r2, r5, r6, r7, r8, sl, fp, ip, sp, lr, pc}
d001327c:	b0032000 	andlt	r2, r3, r0
d0013280:	8ff0e8bd 	svchi	0x00f0e8bd
d0013284:	728cf5a6 	addvc	pc, ip, #696254464	; 0x29800000
d0013288:	46204651 			; <UNDEFINED> instruction: 0x46204651
d001328c:	41534253 	cmpmi	r3, r3, asr r2
d0013290:	f7fd465a 			; <UNDEFINED> instruction: 0xf7fd465a
d0013294:	2800f9d1 	stmdacs	r0, {r0, r4, r6, r7, r8, fp, ip, sp, lr, pc}
d0013298:	f5b6da11 			; <UNDEFINED> instruction: 0xf5b6da11
d001329c:	d00b7f8c 	andle	r7, fp, ip, lsl #31
d00132a0:	447b4b15 	ldrbtmi	r4, [fp], #-2837	; 0xfffff4eb
d00132a4:	b92a6da2 	stmdblt	sl!, {r1, r5, r7, r8, sl, fp, sp, lr}
d00132a8:	3916e9c4 	ldmdbcc	r6, {r2, r6, r7, r8, fp, sp, lr, pc}
d00132ac:	e9c49b01 	stmib	r4, {r0, r8, r9, fp, ip, pc}^
d00132b0:	66a38718 	ssatvs	r8, #4, r8, lsl #14
d00132b4:	e7e22001 	strb	r2, [r2, r1]!
d00132b8:	447b4b10 	ldrbtmi	r4, [fp], #-2832	; 0xfffff4f0
d00132bc:	6028e7f2 	strdvs	lr, [r8], -r2	; <UNPREDICTABLE>
d00132c0:	f240e7f8 	vaba.s8	q15, q8, q12
d00132c4:	429e1301 	addsmi	r1, lr, #67108864	; 0x4000000
d00132c8:	69c2d1d8 	stmibvs	r2, {r3, r4, r6, r7, r8, ip, lr, pc}^
d00132cc:	f7fd6981 			; <UNDEFINED> instruction: 0xf7fd6981
d00132d0:	2800fa5c 	stmdacs	r0, {r2, r3, r4, r6, r9, fp, ip, sp, lr, pc}
d00132d4:	2324dbd2 			; <UNDEFINED> instruction: 0x2324dbd2
d00132d8:	4000fb03 	andmi	pc, r0, r3, lsl #22
d00132dc:	30e5f500 	rsccc	pc, r5, r0, lsl #10
d00132e0:	308cf890 	umullcc	pc, ip, r0, r8	; <UNPREDICTABLE>
d00132e4:	d0c92bff 	strdle	r2, [r9], #191	; 0xbf
d00132e8:	602b4620 	eorvs	r4, fp, r0, lsr #12
d00132ec:	fd82f7ff 	stc2	7, cr15, [r2, #1020]	; 0x3fc
d00132f0:	bf00e7e0 	svclt	0x0000e7e0
d00132f4:	ffffffbd 			; <UNDEFINED> instruction: 0xffffffbd
d00132f8:	ffffff56 			; <UNDEFINED> instruction: 0xffffff56
d00132fc:	ffffff1a 			; <UNDEFINED> instruction: 0xffffff1a

Disassembly of section .text.enum_declaration:

d001342c <.text.enum_declaration>:
d001342c:	f2404ac2 	vpmax.s8	q10, q8, q1
d0013430:	e92d111b 	push	{r0, r1, r3, r4, r8, ip}
d0013434:	447a4ff0 	ldrbtmi	r4, [sl], #-4080	; 0xfffff010
d0013438:	ed2d4604 	stc	6, cr4, [sp, #-16]!
d001343c:	b0978b02 	addslt	r8, r7, r2, lsl #22
d0013440:	fd01f7ff 	stc2	7, cr15, [r1, #-1020]	; 0xfffffc04
d0013444:	28004605 	stmdacs	r0, {r0, r2, r9, sl, lr}
d0013448:	af06d059 	svcge	0x0006d059
d001344c:	21002220 	tstcs	r0, r0, lsr #4
d0013450:	f00b4638 			; <UNDEFINED> instruction: 0xf00b4638
d0013454:	f8d4ffc7 			; <UNDEFINED> instruction: 0xf8d4ffc7
d0013458:	f240a02c 	vhadd.s8	d26, d0, d28
d001345c:	459a1301 	ldrmi	r1, [sl, #769]	; 0x301
d0013460:	f104d136 			; <UNDEFINED> instruction: 0xf104d136
d0013464:	463d0618 			; <UNDEFINED> instruction: 0x463d0618
d0013468:	c50fce0f 	strgt	ip, [pc, #-3599]	; 0xd0012661
d001346c:	000fe896 	muleq	pc, r6, r8	; <UNPREDICTABLE>
d0013470:	000fe885 	andeq	lr, pc, r5, lsl #17
d0013474:	46206a63 	strtmi	r6, [r0], -r3, ror #20
d0013478:	93026b66 	movwls	r6, #11110	; 0x2b66
d001347c:	93036aa3 	movwls	r6, #15011	; 0x3aa3
d0013480:	3030f894 	mlascc	r0, r4, r8, pc	; <UNPREDICTABLE>
d0013484:	8906e9d4 	stmdbhi	r6, {r2, r4, r6, r7, r8, fp, sp, lr, pc}
d0013488:	f7ff9301 			; <UNDEFINED> instruction: 0xf7ff9301
d001348c:	217bfcb3 	ldrhcs	pc, [fp, #-195]!	; 0xffffff3d	; <UNPREDICTABLE>
d0013490:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0013494:	f240fcca 	sha1c.32	<illegal reg q15.5>, q8, q5
d0013498:	46051301 	strmi	r1, [r5], -r1, lsl #6
d001349c:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d00134a0:	459a811e 	ldrmi	r8, [sl, #286]	; 0x11e
d00134a4:	f504d160 			; <UNDEFINED> instruction: 0xf504d160
d00134a8:	f04f35f6 			; <UNDEFINED> instruction: 0xf04f35f6
d00134ac:	f5040a00 			; <UNDEFINED> instruction: 0xf5040a00
d00134b0:	35743bf8 	ldrbcc	r3, [r4, #-3064]!	; 0xfffff408
d00134b4:	30f4f8db 	ldrsbtcc	pc, [r4], #139	; 0x8b	; <UNPREDICTABLE>
d00134b8:	02f4f10b 	rscseq	pc, r4, #-1073741822	; 0xc0000002
d00134bc:	d30f459a 	movwle	r4, #62874	; 0xf59a
d00134c0:	d1312b20 	teqle	r1, r0, lsr #22
d00134c4:	4479499d 	ldrbtmi	r4, [r9], #-2461	; 0xfffff663
d00134c8:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d00134cc:	e015fe6d 	ands	pc, r5, sp, ror #28
d00134d0:	46b22600 	ldrtmi	r2, [r2], r0, lsl #12
d00134d4:	46b046b1 			; <UNDEFINED> instruction: 0x46b046b1
d00134d8:	96039601 	strls	r9, [r3], -r1, lsl #12
d00134dc:	e7d69602 	ldrb	r9, [r6, r2, lsl #12]
d00134e0:	2020f895 	mlacs	r0, r5, r8, pc	; <UNPREDICTABLE>
d00134e4:	429a7a23 	addsmi	r7, sl, #143360	; 0x23000
d00134e8:	464bd11a 			; <UNDEFINED> instruction: 0x464bd11a
d00134ec:	e9d54642 	ldmib	r5, {r1, r6, r9, sl, lr}^
d00134f0:	f7fd0100 			; <UNDEFINED> instruction: 0xf7fd0100
d00134f4:	b198f893 			; <UNDEFINED> instruction: 0xb198f893
d00134f8:	b1356da5 	teqlt	r5, r5, lsr #27
d00134fc:	46282500 	strtmi	r2, [r8], -r0, lsl #10
d0013500:	ecbdb017 	ldc	0, cr11, [sp], #92	; 0x5c
d0013504:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d0013508:	4b8d8ff0 	blmi	0xce3774d0
d001350c:	65a3447b 	strvs	r4, [r3, #1147]!	; 0x47b
d0013510:	66a69b02 	strtvs	r9, [r6], r2, lsl #22
d0013514:	9b0365e3 	blls	0xd00ecca8
d0013518:	9b016623 	blls	0xd006cdac
d001351c:	e7ee6663 	strb	r6, [lr, r3, ror #12]!
d0013520:	0a01f10a 	beq	0xd008f950
d0013524:	e7c53524 	strb	r3, [r5, r4, lsr #10]
d0013528:	f04f1c59 			; <UNDEFINED> instruction: 0xf04f1c59
d001352c:	960d0c24 	strls	r0, [sp], -r4, lsr #24
d0013530:	9a026011 	bls	0xd00ab57c
d0013534:	4303fb0c 	movwmi	pc, #15116	; 0x3b0c	; <UNPREDICTABLE>
d0013538:	92097a25 	andls	r7, r9, #151552	; 0x25000
d001353c:	3cf6f503 	cfldr64cc	mvdx15, [r6], #12
d0013540:	f10c9a03 			; <UNDEFINED> instruction: 0xf10c9a03
d0013544:	920a0674 	andls	r0, sl, #116, 12	; 0x7400000
d0013548:	1201f240 	andne	pc, r1, #64, 4
d001354c:	9a01920b 	bls	0xd0077d80
d0013550:	8906e9cd 	stmdbhi	r6, {r0, r2, r3, r6, r7, r8, fp, sp, lr, pc}
d0013554:	2030f88d 	eorscs	pc, r0, sp, lsl #17
d0013558:	c60fcf0f 	strgt	ip, [pc], -pc, lsl #30
d001355c:	000fe897 	muleq	pc, r7, r8	; <UNPREDICTABLE>
d0013560:	000fe886 	andeq	lr, pc, r6, lsl #17
d0013564:	5094f88c 	addspl	pc, r4, ip, lsl #17
d0013568:	f04f4b76 			; <UNDEFINED> instruction: 0xf04f4b76
d001356c:	f04f35ff 			; <UNDEFINED> instruction: 0xf04f35ff
d0013570:	447b0b00 	ldrbtmi	r0, [fp], #-2816	; 0xfffff500
d0013574:	ee08462e 	cfmadd32	mvax1, mvfx4, mvfx8, mvfx14
d0013578:	6da33a10 			; <UNDEFINED> instruction: 0x6da33a10
d001357c:	2b009303 	blcs	0xd0038190
d0013580:	809cf040 	addshi	pc, ip, r0, asr #32
d0013584:	2b7d6ae3 	blcs	0xd1f6e118
d0013588:	8098f000 	addshi	pc, r8, r0
d001358c:	7f80f5b3 	svcvc	0x0080f5b3
d0013590:	8094f000 	addshi	pc, r4, r0
d0013594:	0c18f104 	ldfeqd	f7, [r8], {4}
d0013598:	f894af0e 			; <UNDEFINED> instruction: 0xf894af0e
d001359c:	e8bc8030 	ldm	ip!, {r4, r5, pc}
d00135a0:	c70f000f 	strgt	r0, [pc, -pc]
d00135a4:	000fe89c 	muleq	pc, ip, r8	; <UNPREDICTABLE>
d00135a8:	000fe887 	andeq	lr, pc, r7, lsl #17
d00135ac:	ee186a63 	vnmla.f32	s12, s16, s7
d00135b0:	f2402a10 	vpmin.s8	d18, d0, d0
d00135b4:	46201101 	strtmi	r1, [r0], -r1, lsl #2
d00135b8:	6aa39301 	bvs	0xce8f81c4
d00135bc:	93026b67 	movwls	r6, #11111	; 0x2b67
d00135c0:	a906e9d4 	stmdbge	r6, {r2, r4, r6, r7, r8, fp, sp, lr, pc}
d00135c4:	fc3ff7ff 	ldc2	7, cr15, [pc], #-1020	; 0xd00131d0
d00135c8:	d0972800 	addsle	r2, r7, r0, lsl #16
d00135cc:	4651464a 	ldrbmi	r4, [r1], -sl, asr #12
d00135d0:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d00135d4:	2800fe71 	stmdacs	r0, {r0, r4, r5, r6, r9, sl, fp, ip, sp, lr, pc}
d00135d8:	6da3db0c 			; <UNDEFINED> instruction: 0x6da3db0c
d00135dc:	d18d2b00 	orrle	r2, sp, r0, lsl #22
d00135e0:	447b4b59 	ldrbtmi	r4, [fp], #-2905	; 0xfffff4a7
d00135e4:	9b0165a3 	blls	0xd006cc78
d00135e8:	65e366a7 	strbvs	r6, [r3, #1703]!	; 0x6a7
d00135ec:	e9c49b02 	stmib	r4, {r1, r8, r9, fp, ip, pc}^
d00135f0:	e7833818 	usada8	r3, r8, r8, r3
d00135f4:	4651464a 	ldrbmi	r4, [r1], -sl, asr #12
d00135f8:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d00135fc:	2800f8c6 	stmdacs	r0, {r1, r2, r6, r7, fp, ip, sp, lr, pc}
d0013600:	213ddaeb 	teqcs	sp, fp, ror #21
d0013604:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0013608:	b1e0fc10 	mvnlt	pc, r0, lsl ip	; <UNPREDICTABLE>
d001360c:	21019a03 	tstcs	r1, r3, lsl #20
d0013610:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0013614:	4605fca3 	strmi	pc, [r5], -r3, lsr #25
d0013618:	f115460e 			; <UNDEFINED> instruction: 0xf115460e
d001361c:	f04f4300 			; <UNDEFINED> instruction: 0xf04f4300
d0013620:	930432ff 	movwls	r3, #17151	; 0x42ff
d0013624:	0300f146 	movweq	pc, #326	; 0x146	; <UNPREDICTABLE>
d0013628:	23009305 	movwcs	r9, #773	; 0x305
d001362c:	0104e9dd 	ldrdeq	lr, [r4, -sp]
d0013630:	bf08428b 	svclt	0x0008428b
d0013634:	d20a4282 	andle	r4, sl, #536870920	; 0x20000008
d0013638:	2b006da3 	blcs	0xd002eccc
d001363c:	af5ef47f 	svcge	0x005ef47f
d0013640:	447b4b42 	ldrbtmi	r4, [fp], #-2882	; 0xfffff4be
d0013644:	3501e7ce 	strcc	lr, [r1, #-1998]	; 0xfffff832
d0013648:	0600f146 	streq	pc, [r0], -r6, asr #2
d001364c:	f504e7e5 			; <UNDEFINED> instruction: 0xf504e7e5
d0013650:	6f1332f6 	svcvs	0x001332f6
d0013654:	d1062ba0 	smlatble	r6, r0, fp, r2
d0013658:	2b006da3 	blcs	0xd002ecec
d001365c:	af4ef47f 	svcge	0x004ef47f
d0013660:	447b4b3b 	ldrbtmi	r4, [fp], #-2875	; 0xfffff4c5
d0013664:	f88de7be 			; <UNDEFINED> instruction: 0xf88de7be
d0013668:	1c598050 	mrrcne	0, 5, r8, r9, cr0
d001366c:	0828f04f 	stmdaeq	r8!, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d0013670:	0e38f10d 	rndeqe	f7, #5.0
d0013674:	f10b6711 			; <UNDEFINED> instruction: 0xf10b6711
d0013678:	9a010b01 	bls	0xd0056284
d001367c:	4803fb08 	stmdami	r3, {r3, r8, r9, fp, ip, sp, lr, pc}
d0013680:	f5089715 			; <UNDEFINED> instruction: 0xf5089715
d0013684:	921138e9 	andsls	r3, r1, #15269888	; 0xe90000
d0013688:	f5089a02 			; <UNDEFINED> instruction: 0xf5089a02
d001368c:	f89477b8 			; <UNDEFINED> instruction: 0xf89477b8
d0013690:	9212c008 	andsls	ip, r2, #8
d0013694:	a90ee9cd 	stmdbge	lr, {r0, r2, r3, r6, r7, r8, fp, sp, lr, pc}
d0013698:	000fe8be 			; <UNDEFINED> instruction: 0x000fe8be
d001369c:	e89ec70f 	ldm	lr, {r0, r1, r2, r3, r8, r9, sl, lr, pc}
d00136a0:	e887000f 	stm	r7, {r0, r1, r2, r3}
d00136a4:	212c000f 			; <UNDEFINED> instruction: 0x212c000f
d00136a8:	f8c84620 			; <UNDEFINED> instruction: 0xf8c84620
d00136ac:	f8885190 			; <UNDEFINED> instruction: 0xf8885190
d00136b0:	f7ffc194 			; <UNDEFINED> instruction: 0xf7ffc194
d00136b4:	2800fbba 	stmdacs	r0, {r1, r3, r4, r5, r7, r8, r9, fp, ip, sp, lr, pc}
d00136b8:	af5ff47f 	svcge	0x005ff47f
d00136bc:	0f00f1bb 	svceq	0x0000f1bb
d00136c0:	4924d102 	stmdbmi	r4!, {r1, r8, ip, lr, pc}
d00136c4:	e6ff4479 	uxth	r4, r9, ror #8
d00136c8:	217d4a23 	cmncs	sp, r3, lsr #20
d00136cc:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d00136d0:	ecbdb017 	ldc	0, cr11, [sp], #92	; 0x5c
d00136d4:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d00136d8:	f7ff4ff0 			; <UNDEFINED> instruction: 0xf7ff4ff0
d00136dc:	459abbb4 	ldrmi	fp, [sl, #2996]	; 0xbb4
d00136e0:	f504d110 			; <UNDEFINED> instruction: 0xf504d110
d00136e4:	468237f6 			; <UNDEFINED> instruction: 0x468237f6
d00136e8:	3bf8f504 	blcc	0xcfe50b00
d00136ec:	f8db3774 			; <UNDEFINED> instruction: 0xf8db3774
d00136f0:	459a30f4 	ldrmi	r3, [sl, #244]	; 0xf4
d00136f4:	6da3d30c 	stcvs	3, cr13, [r3, #48]!	; 0x30
d00136f8:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d00136fc:	4b17aeff 	blmi	0xd05ff300
d0013700:	e704447b 	smlsdx	r4, fp, r4, r4
d0013704:	46204916 			; <UNDEFINED> instruction: 0x46204916
d0013708:	f7fc4479 			; <UNDEFINED> instruction: 0xf7fc4479
d001370c:	e6f6fd4d 	ldrbt	pc, [r6], sp, asr #26	; <UNPREDICTABLE>
d0013710:	2020f897 	mlacs	r0, r7, r8, pc	; <UNPREDICTABLE>
d0013714:	429a7a23 	addsmi	r7, sl, #143360	; 0x23000
d0013718:	f10ad003 			; <UNDEFINED> instruction: 0xf10ad003
d001371c:	37240a01 	strcc	r0, [r4, -r1, lsl #20]!
d0013720:	464be7e5 	strbmi	lr, [fp], -r5, ror #15
d0013724:	e9d74642 	ldmib	r7, {r1, r6, r9, sl, lr}^
d0013728:	f7fc0100 			; <UNDEFINED> instruction: 0xf7fc0100
d001372c:	2800ff77 	stmdacs	r0, {r0, r1, r2, r4, r5, r6, r8, r9, sl, fp, ip, sp, lr, pc}
d0013730:	2501d0f3 	strcs	sp, [r1, #-243]	; 0xffffff0d
d0013734:	bf00e6e3 	svclt	0x0000e6e3
d0013738:	fffffec6 			; <UNDEFINED> instruction: 0xfffffec6
d001373c:	fffffe5e 			; <UNDEFINED> instruction: 0xfffffe5e
d0013740:	fffffdfe 			; <UNDEFINED> instruction: 0xfffffdfe
d0013744:	fffffdc5 			; <UNDEFINED> instruction: 0xfffffdc5
d0013748:	fffffd71 			; <UNDEFINED> instruction: 0xfffffd71
d001374c:	fffffd29 			; <UNDEFINED> instruction: 0xfffffd29
d0013750:	fffffd33 			; <UNDEFINED> instruction: 0xfffffd33
d0013754:	fffffce9 			; <UNDEFINED> instruction: 0xfffffce9
d0013758:	fffffd06 			; <UNDEFINED> instruction: 0xfffffd06
d001375c:	fffffd16 			; <UNDEFINED> instruction: 0xfffffd16
d0013760:	fffffcee 			; <UNDEFINED> instruction: 0xfffffcee

Disassembly of section .text.sizeof_operand:

d0013964 <.text.sizeof_operand>:
d0013964:	4ff0e92d 	svcmi	0x00f0e92d
d0013968:	21284604 			; <UNDEFINED> instruction: 0x21284604
d001396c:	8b02ed2d 	blhi	0xd00cee28
d0013970:	f7ffb08b 			; <UNDEFINED> instruction: 0xf7ffb08b
d0013974:	f240fa5a 	vpmin.s8	<illegal reg q15.5>, q0, q5
d0013978:	90021107 	andls	r1, r2, r7, lsl #2
d001397c:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0013980:	b128fa54 	msrlt	R8_fiq, r4
d0013984:	4620212a 	strtmi	r2, [r0], -sl, lsr #2
d0013988:	fa4ff7ff 	blx	0xd141198c
d001398c:	e0312704 	eors	r2, r1, r4, lsl #14
d0013990:	7184f44f 	orrvc	pc, r4, pc, asr #8
d0013994:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0013998:	b190fa48 	orrslt	pc, r0, r8, asr #20
d001399c:	4620212a 	strtmi	r2, [r0], -sl, lsr #2
d00139a0:	fa43f7ff 	blx	0xd11119a4
d00139a4:	28004607 	stmdacs	r0, {r0, r1, r2, r9, sl, lr}
d00139a8:	f8dfd1f0 			; <UNDEFINED> instruction: 0xf8dfd1f0
d00139ac:	4620148c 	strtmi	r1, [r0], -ip, lsl #9
d00139b0:	f7fc4479 			; <UNDEFINED> instruction: 0xf7fc4479
d00139b4:	4638fbf9 			; <UNDEFINED> instruction: 0x4638fbf9
d00139b8:	ecbdb00b 	ldc	0, cr11, [sp], #44	; 0x2c
d00139bc:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d00139c0:	6ae28ff0 	bvs	0xcf8b7988
d00139c4:	131bf240 	tstne	fp, #64, 4	; <UNPREDICTABLE>
d00139c8:	d106429a 			; <UNDEFINED> instruction: 0xd106429a
d00139cc:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d00139d0:	2800fd2d 	stmdacs	r0, {r0, r2, r3, r5, r8, sl, fp, ip, sp, lr, pc}
d00139d4:	2700d1da 			; <UNDEFINED> instruction: 0x2700d1da
d00139d8:	f240e7ed 	vabd.s8	q15, q8, <illegal reg q14.5>
d00139dc:	4620110b 	strtmi	r1, [r0], -fp, lsl #2
d00139e0:	fa23f7ff 	blx	0xd09119e4
d00139e4:	212ab348 			; <UNDEFINED> instruction: 0x212ab348
d00139e8:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d00139ec:	2800fa1e 	stmdacs	r0, {r1, r2, r3, r4, r9, fp, ip, sp, lr, pc}
d00139f0:	2701d1cc 	strcs	sp, [r1, -ip, asr #3]
d00139f4:	4620215b 			; <UNDEFINED> instruction: 0x4620215b
d00139f8:	fa17f7ff 	blx	0xd06119fc
d00139fc:	d0612800 	rsble	r2, r1, r0, lsl #16
d0013a00:	f5a36ae3 			; <UNDEFINED> instruction: 0xf5a36ae3
d0013a04:	2b017381 	blcs	0xd0070810
d0013a08:	81e8f200 	mvnhi	pc, r0, lsl #4
d0013a0c:	2d006a25 	vstrcs	s12, [r0, #-148]	; 0xffffff6c
d0013a10:	81e4f000 	mvnhi	pc, r0
d0013a14:	2305fba7 	movwcs	pc, #23463	; 0x5ba7	; <UNPREDICTABLE>
d0013a18:	f0402b00 			; <UNDEFINED> instruction: 0xf0402b00
d0013a1c:	462081df 			; <UNDEFINED> instruction: 0x462081df
d0013a20:	f9e8f7ff 			; <UNDEFINED> instruction: 0xf9e8f7ff
d0013a24:	2414f8df 	ldrcs	pc, [r4], #-2271	; 0xfffff721
d0013a28:	4620215d 			; <UNDEFINED> instruction: 0x4620215d
d0013a2c:	f7ff447a 			; <UNDEFINED> instruction: 0xf7ff447a
d0013a30:	2800fa0a 	stmdacs	r0, {r1, r3, r9, fp, ip, sp, lr, pc}
d0013a34:	436fd0cf 	cmnmi	pc, #207	; 0xcf
d0013a38:	6ae5e044 	bvs	0xcf98bb50
d0013a3c:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d0013a40:	d118429d 			; <UNDEFINED> instruction: 0xd118429d
d0013a44:	69e14afe 	stmibvs	r1!, {r1, r2, r3, r4, r5, r6, r7, r9, fp, lr}^
d0013a48:	69a0447a 	stmibvs	r0!, {r1, r3, r4, r5, r6, sl, lr}
d0013a4c:	ff09f7fc 			; <UNDEFINED> instruction: 0xff09f7fc
d0013a50:	4620b118 			; <UNDEFINED> instruction: 0x4620b118
d0013a54:	f9cef7ff 			; <UNDEFINED> instruction: 0xf9cef7ff
d0013a58:	6ae3e7c5 	bvs	0xcf90d974
d0013a5c:	d10a42ab 	smlatble	sl, fp, r2, r4
d0013a60:	69e14af8 	stmibvs	r1!, {r3, r4, r5, r6, r7, r9, fp, lr}^
d0013a64:	69a0447a 	stmibvs	r0!, {r1, r3, r4, r5, r6, sl, lr}
d0013a68:	fefbf7fc 	mrc2	7, 7, pc, cr11, cr12, {7}
d0013a6c:	4620b118 			; <UNDEFINED> instruction: 0x4620b118
d0013a70:	f9c0f7ff 			; <UNDEFINED> instruction: 0xf9c0f7ff
d0013a74:	4620e786 	strtmi	lr, [r0], -r6, lsl #15
d0013a78:	feabf7fc 	mcr2	7, 5, pc, cr11, cr12, {7}	; <UNPREDICTABLE>
d0013a7c:	2300b1c8 	movwcs	fp, #456	; 0x1c8
d0013a80:	4620a909 	strtmi	sl, [r0], -r9, lsl #18
d0013a84:	f7ff9309 			; <UNDEFINED> instruction: 0xf7ff9309
d0013a88:	2800fbdb 	stmdacs	r0, {r0, r1, r3, r4, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d0013a8c:	212ad0a3 			; <UNDEFINED> instruction: 0x212ad0a3
d0013a90:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0013a94:	2800f9ca 	stmdacs	r0, {r1, r3, r6, r7, r8, fp, ip, sp, lr, pc}
d0013a98:	af78f47f 	svcge	0x0078f47f
d0013a9c:	f44f9b09 			; <UNDEFINED> instruction: 0xf44f9b09
d0013aa0:	fb02721a 	blx	0xd00b0312
d0013aa4:	f5034303 			; <UNDEFINED> instruction: 0xf5034303
d0013aa8:	f8b333c9 			; <UNDEFINED> instruction: 0xf8b333c9
d0013aac:	00bf7108 	adcseq	r7, pc, r8, lsl #2
d0013ab0:	6ae3e7a0 	bvs	0xcf90d938
d0013ab4:	7381f5a3 	orrvc	pc, r1, #683671552	; 0x28c00000
d0013ab8:	d8112b01 	ldmdale	r1, {r0, r8, r9, fp, sp}
d0013abc:	46202704 	strtmi	r2, [r0], -r4, lsl #14
d0013ac0:	f998f7ff 			; <UNDEFINED> instruction: 0xf998f7ff
d0013ac4:	2b009b02 	blcs	0xd003a6d4
d0013ac8:	af75f43f 	svcge	0x0075f43f
d0013acc:	21294ade 	ldrdcs	r4, [r9, -lr]!
d0013ad0:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d0013ad4:	f9b7f7ff 			; <UNDEFINED> instruction: 0xf9b7f7ff
d0013ad8:	f47f2800 			; <UNDEFINED> instruction: 0xf47f2800
d0013adc:	e77aaf6c 	ldrb	sl, [sl, -ip, ror #30]!
d0013ae0:	4620212a 	strtmi	r2, [r0], -sl, lsr #2
d0013ae4:	f9a1f7ff 			; <UNDEFINED> instruction: 0xf9a1f7ff
d0013ae8:	4ad86a63 	bmi	0xcf62e47c
d0013aec:	93004680 	movwls	r4, #1664	; 0x680
d0013af0:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d0013af4:	447a6b63 	ldrbtmi	r6, [sl], #-2915	; 0xfffff49d
d0013af8:	f8d44620 			; <UNDEFINED> instruction: 0xf8d44620
d0013afc:	f894a028 			; <UNDEFINED> instruction: 0xf894a028
d0013b00:	93019030 	movwls	r9, #4144	; 0x1030
d0013b04:	5606e9d4 			; <UNDEFINED> instruction: 0x5606e9d4
d0013b08:	f99df7ff 			; <UNDEFINED> instruction: 0xf99df7ff
d0013b0c:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0013b10:	4632af62 	ldrtmi	sl, [r2], -r2, ror #30
d0013b14:	46204629 	strtmi	r4, [r0], -r9, lsr #12
d0013b18:	fdf4f7fc 	ldc2l	7, cr15, [r4, #1008]!	; 0x3f0
d0013b1c:	f2802800 	vmlal.s8	q1, d0, d0
d0013b20:	46328176 			; <UNDEFINED> instruction: 0x46328176
d0013b24:	46204629 	strtmi	r4, [r0], -r9, lsr #12
d0013b28:	fe0bf7fc 	mcr2	7, 0, pc, cr11, cr12, {7}	; <UNPREDICTABLE>
d0013b2c:	da0d2800 	ble	0xd035db34
d0013b30:	2f006da7 	svccs	0x00006da7
d0013b34:	af4ff47f 	svcge	0x004ff47f
d0013b38:	447b4bc5 	ldrbtmi	r4, [fp], #-3013	; 0xfffff43b
d0013b3c:	9b0065a3 	blls	0xd002d1d0
d0013b40:	9b0165e3 	blls	0xd006d2d4
d0013b44:	a918e9c4 	ldmdbge	r8, {r2, r6, r7, r8, fp, sp, lr, pc}
d0013b48:	e73466a3 	ldr	r6, [r4, -r3, lsr #13]!
d0013b4c:	fb032338 	blx	0xd00dc836
d0013b50:	f5004000 			; <UNDEFINED> instruction: 0xf5004000
d0013b54:	f89030ba 			; <UNDEFINED> instruction: 0xf89030ba
d0013b58:	f89020cc 			; <UNDEFINED> instruction: 0xf89020cc
d0013b5c:	f8d050ce 			; <UNDEFINED> instruction: 0xf8d050ce
d0013b60:	f1a210d8 			; <UNDEFINED> instruction: 0xf1a210d8
d0013b64:	2b04030d 	blcs	0xd01147a0
d0013b68:	1fd3d931 	svcne	0x00d3d931
d0013b6c:	2b022600 	blcs	0xd009d374
d0013b70:	2a10d92f 	bcs	0xd044a034
d0013b74:	f1a2d02f 			; <UNDEFINED> instruction: 0xf1a2d02f
d0013b78:	f1dc0c11 			; <UNDEFINED> instruction: 0xf1dc0c11
d0013b7c:	eb430300 	bl	0xd10d4784
d0013b80:	2a0a030c 	bcs	0xd02947b8
d0013b84:	814ff000 	mrshi	pc, SPSR	; <UNPREDICTABLE>
d0013b88:	dc032a13 			; <UNDEFINED> instruction: 0xdc032a13
d0013b8c:	40d048a9 	sbcsmi	r4, r0, r9, lsr #17
d0013b90:	d42207c7 	strtle	r0, [r2], #-1991	; 0xfffff839
d0013b94:	f1d01f90 			; <UNDEFINED> instruction: 0xf1d01f90
d0013b98:	eb4b0b00 	bl	0xd12d67a0
d0013b9c:	2a070b00 	bcs	0xd01d67a4
d0013ba0:	2a05d01e 	bcs	0xd0187c20
d0013ba4:	b34ed01c 	movtlt	sp, #57372	; 0xe01c
d0013ba8:	0f00f1bb 	svceq	0x0000f1bb
d0013bac:	8126f040 	msrhi	CPSR_sx, r0, asr #32
d0013bb0:	721af44f 	andsvc	pc, sl, #1325400064	; 0x4f000000
d0013bb4:	4205fb02 	andmi	pc, r5, #2048	; 0x800
d0013bb8:	32c9f502 	sbccc	pc, r9, #8388608	; 0x800000
d0013bbc:	7108f8b2 			; <UNDEFINED> instruction: 0x7108f8b2
d0013bc0:	0f00f1b8 	svceq	0x0000f1b8
d0013bc4:	00bfd113 	adcseq	sp, pc, r3, lsl r1	; <UNPREDICTABLE>
d0013bc8:	434fb36b 	movtmi	fp, #62315	; 0xf36b
d0013bcc:	2601e02b 	strcs	lr, [r1], -fp, lsr #32
d0013bd0:	2301e7cf 	movwcs	lr, #6095	; 0x17cf
d0013bd4:	2301e7d8 	movwcs	lr, #6104	; 0x17d8
d0013bd8:	f04fe7d8 			; <UNDEFINED> instruction: 0xf04fe7d8
d0013bdc:	e7e00b01 	strb	r0, [r0, r1, lsl #22]!
d0013be0:	f1b82701 			; <UNDEFINED> instruction: 0xf1b82701
d0013be4:	d0ef0f00 	rscle	r0, pc, r0, lsl #30
d0013be8:	0f00f1bb 	svceq	0x0000f1bb
d0013bec:	6da7d108 	stfvsd	f5, [r7, #32]!
d0013bf0:	f47f2f00 			; <UNDEFINED> instruction: 0xf47f2f00
d0013bf4:	4b97aef0 	blmi	0xce5ff7bc
d0013bf8:	e79f447b 			; <UNDEFINED> instruction: 0xe79f447b
d0013bfc:	e7f02704 	ldrb	r2, [r0, r4, lsl #14]!
d0013c00:	f0402a0e 			; <UNDEFINED> instruction: 0xf0402a0e
d0013c04:	f44f8115 	vst4.8	{d24,d26,d28,d30}, [pc :64], r5
d0013c08:	fb03731a 	blx	0xd00f087a
d0013c0c:	f5034305 			; <UNDEFINED> instruction: 0xf5034305
d0013c10:	f8b333c9 			; <UNDEFINED> instruction: 0xf8b333c9
d0013c14:	00bf7108 	adcseq	r7, pc, r8, lsl #2
d0013c18:	030ef1a2 	movweq	pc, #57762	; 0xe1a2	; <UNPREDICTABLE>
d0013c1c:	0b00f04f 	bleq	0xd004fd60
d0013c20:	415e425e 	cmpmi	lr, lr, asr r2
d0013c24:	215b465b 	cmpcs	fp, fp, asr r6
d0013c28:	93034620 	movwls	r4, #13856	; 0x3620
d0013c2c:	f8fdf7ff 			; <UNDEFINED> instruction: 0xf8fdf7ff
d0013c30:	9b03b380 	blls	0xd0100a38
d0013c34:	030bea53 	movweq	lr, #47699	; 0xba53
d0013c38:	6da7d115 	stfvsd	f5, [r7, #84]!	; 0x54
d0013c3c:	f47f2f00 			; <UNDEFINED> instruction: 0xf47f2f00
d0013c40:	4b85aeca 	blmi	0xce17f770
d0013c44:	e779447b 			; <UNDEFINED> instruction: 0xe779447b
d0013c48:	d1072b5b 	tstle	r7, fp, asr fp
d0013c4c:	46203701 	strtmi	r3, [r0], -r1, lsl #14
d0013c50:	f8d0f7ff 			; <UNDEFINED> instruction: 0xf8d0f7ff
d0013c54:	b9a6b947 	stmiblt	r6!, {r0, r1, r2, r6, r8, fp, ip, sp, pc}
d0013c58:	e01b2704 	ands	r2, fp, r4, lsl #14
d0013c5c:	bf082b5d 	svclt	0x00082b5d
d0013c60:	37fff107 	ldrbcc	pc, [pc, r7, lsl #2]!	; <UNPREDICTABLE>
d0013c64:	2701e7f3 			; <UNDEFINED> instruction: 0x2701e7f3
d0013c68:	f5b36ae3 			; <UNDEFINED> instruction: 0xf5b36ae3
d0013c6c:	d0027f80 	andle	r7, r2, r0, lsl #31
d0013c70:	2a006da2 	bcs	0xd002f300
d0013c74:	4979d0e8 	ldmdbmi	r9!, {r3, r5, r6, r7, ip, lr, pc}^
d0013c78:	44794620 	ldrbtmi	r4, [r9], #-1568	; 0xfffff9e0
d0013c7c:	fa94f7fc 	blx	0xce551c74
d0013c80:	f44fe6a9 	vst1.32	{d30-d32}, [pc :128], r9
d0013c84:	fb03731a 	blx	0xd00f08f6
d0013c88:	f5034305 			; <UNDEFINED> instruction: 0xf5034305
d0013c8c:	f8b333c9 			; <UNDEFINED> instruction: 0xf8b333c9
d0013c90:	00bf7108 	adcseq	r7, pc, r8, lsl #2
d0013c94:	447b4b72 	ldrbtmi	r4, [fp], #-2930	; 0xfffff48e
d0013c98:	3a90ee08 	bcc	0xce44f4c0
d0013c9c:	2b2e6ae3 	blcs	0xd0bae830
d0013ca0:	f5b3d014 			; <UNDEFINED> instruction: 0xf5b3d014
d0013ca4:	f47f7f91 			; <UNDEFINED> instruction: 0xf47f7f91
d0013ca8:	f1bbaf0d 			; <UNDEFINED> instruction: 0xf1bbaf0d
d0013cac:	d1170f00 	tstle	r7, r0, lsl #30
d0013cb0:	2b006da3 	blcs	0xd002f344
d0013cb4:	ae8ff47f 	mcrge	4, 4, pc, cr15, cr15, {3}	; <UNPREDICTABLE>
d0013cb8:	447b4b6a 	ldrbtmi	r4, [fp], #-2922	; 0xfffff496
d0013cbc:	9b0065a3 	blls	0xd002d350
d0013cc0:	9b0165e3 	blls	0xd006d454
d0013cc4:	a918e9c4 	ldmdbge	r8, {r2, r6, r7, r8, fp, sp, lr, pc}
d0013cc8:	e68466a3 	str	r6, [r4], r3, lsr #13
d0013ccc:	0f00f1bb 	svceq	0x0000f1bb
d0013cd0:	6da7d006 	stcvs	0, cr13, [r7, #24]!
d0013cd4:	f47f2f00 			; <UNDEFINED> instruction: 0xf47f2f00
d0013cd8:	4b63ae7e 	blmi	0xd18ff6d8
d0013cdc:	e72d447b 			; <UNDEFINED> instruction: 0xe72d447b
d0013ce0:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0013ce4:	b936f887 	ldmdblt	r6!, {r0, r1, r2, r7, fp, ip, sp, lr, pc}
d0013ce8:	2b006da3 	blcs	0xd002f37c
d0013cec:	ae73f47f 	mrcge	4, 3, APSR_nzcv, cr3, cr15, {3}
d0013cf0:	447b4b5e 	ldrbtmi	r4, [fp], #-2910	; 0xfffff4a2
d0013cf4:	69a3e7e2 	stmibvs	r3!, {r1, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d0013cf8:	2a90ee18 	bcs	0xce44f560
d0013cfc:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d0013d00:	ee084620 	cfmadd32	mvax1, mvfx4, mvfx8, mvfx0
d0013d04:	69e33a10 	stmibvs	r3!, {r4, r9, fp, ip, sp}^
d0013d08:	6a639307 	bvs	0xd18f892c
d0013d0c:	6aa39303 	bvs	0xce8f8920
d0013d10:	f8949306 			; <UNDEFINED> instruction: 0xf8949306
d0013d14:	93053030 	movwls	r3, #20528	; 0x5030
d0013d18:	93046b63 	movwls	r6, #19299	; 0x4b63
d0013d1c:	f893f7ff 			; <UNDEFINED> instruction: 0xf893f7ff
d0013d20:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0013d24:	f44fae58 			; <UNDEFINED> instruction: 0xf44fae58
d0013d28:	2700731a 	smladcs	r0, sl, r3, r7
d0013d2c:	fb05fb03 	blx	0xd0192942
d0013d30:	f50b9b07 			; <UNDEFINED> instruction: 0xf50b9b07
d0013d34:	44a338c8 	strtmi	r3, [r3], #2248	; 0x8c8
d0013d38:	08c8f108 	stmiaeq	r8, {r3, r8, ip, sp, lr, pc}^
d0013d3c:	3bc9f50b 	blcc	0xcf291170
d0013d40:	f89b44a0 			; <UNDEFINED> instruction: 0xf89b44a0
d0013d44:	42ba210a 	adcsmi	r2, sl, #-2147483646	; 0x80000002
d0013d48:	f44fd818 	vst2.8	{d29-d30}, [pc :64], r8
d0013d4c:	435d731a 	cmpmi	sp, #1744830464	; 0x68000000
d0013d50:	f5031963 			; <UNDEFINED> instruction: 0xf5031963
d0013d54:	f89333c9 			; <UNDEFINED> instruction: 0xf89333c9
d0013d58:	42bb310a 	adcsmi	r3, fp, #-2147483646	; 0x80000002
d0013d5c:	6da7d11c 	stfvsd	f5, [r7, #112]!	; 0x70
d0013d60:	f47f2f00 			; <UNDEFINED> instruction: 0xf47f2f00
d0013d64:	4b42ae38 	blmi	0xd10bf64c
d0013d68:	65a3447b 	strvs	r4, [r3, #1147]!	; 0x47b
d0013d6c:	65e39b03 	strbvs	r9, [r3, #2819]!	; 0xb03
d0013d70:	66239b06 	strtvs	r9, [r3], -r6, lsl #22
d0013d74:	66639b05 	strbtvs	r9, [r3], -r5, lsl #22
d0013d78:	e6e59b04 	strbt	r9, [r5], r4, lsl #22
d0013d7c:	1004f8d8 	ldrdne	pc, [r4], -r8
d0013d80:	2a10ee18 	bcs	0xd044f5e8
d0013d84:	0b24f858 	bleq	0xd0951eec
d0013d88:	f7fc9307 			; <UNDEFINED> instruction: 0xf7fc9307
d0013d8c:	9b07fc47 	blls	0xd0212eb0
d0013d90:	d1da2800 	bicsle	r2, sl, r0, lsl #16
d0013d94:	e7d43701 	ldrb	r3, [r4, r1, lsl #14]
d0013d98:	fb032324 	blx	0xd00dca32
d0013d9c:	44275707 	strtmi	r5, [r7], #-1799	; 0xfffff8f9
d0013da0:	37c8f507 	strbcc	pc, [r8, r7, lsl #10]	; <UNPREDICTABLE>
d0013da4:	50e8f897 	smlalpl	pc, r8, r7, r8	; <UNPREDICTABLE>
d0013da8:	b0e9f897 	smlallt	pc, r9, r7, r8	; <UNPREDICTABLE>
d0013dac:	03fff1b5 	mvnseq	pc, #1073741869	; 0x4000002d
d0013db0:	2301bf18 	movwcs	fp, #7960	; 0x1f18
d0013db4:	0f00f1bb 	svceq	0x0000f1bb
d0013db8:	2dffd10e 	ldfcsp	f5, [pc, #56]!	; 0xd0013df8
d0013dbc:	f44fd00b 	vst4.8	{d29-d32}, [pc], fp
d0013dc0:	fb03731a 	blx	0xd00f0a32
d0013dc4:	f5034305 			; <UNDEFINED> instruction: 0xf5034305
d0013dc8:	f8b333c9 			; <UNDEFINED> instruction: 0xf8b333c9
d0013dcc:	46337108 	ldrtmi	r7, [r3], -r8, lsl #2
d0013dd0:	461e00bf 			; <UNDEFINED> instruction: 0x461e00bf
d0013dd4:	465be762 	ldrbmi	lr, [fp], -r2, ror #14
d0013dd8:	e7fa2704 	ldrb	r2, [sl, r4, lsl #14]!
d0013ddc:	2f006da7 	svccs	0x00006da7
d0013de0:	adf9f47f 	cfldrdge	mvd15, [r9, #508]!	; 0x1fc
d0013de4:	6a604d23 	bvs	0xd1827278
d0013de8:	447d6aa1 	ldrbtmi	r6, [sp], #-2721	; 0xfffff55f
d0013dec:	2030f894 	mlascs	r0, r4, r8, pc	; <UNPREDICTABLE>
d0013df0:	e9c46b63 	stmib	r4, {r0, r1, r5, r6, r8, r9, fp, sp, lr}^
d0013df4:	e9c45016 	stmib	r4, {r1, r2, r4, ip, lr}^
d0013df8:	e6a51218 	ssat	r1, #6, r8, lsl #4
d0013dfc:	0f00f1b8 	svceq	0x0000f1b8
d0013e00:	aefef47f 	mrcge	4, 7, APSR_nzcv, cr14, cr15, {3}
d0013e04:	27042601 	strcs	r2, [r4, -r1, lsl #12]
d0013e08:	0b01f04f 	bleq	0xd008ff4c
d0013e0c:	2330e6dc 	teqcs	r0, #220, 12	; 0xdc00000
d0013e10:	4000fb03 	andmi	pc, r0, r3, lsl #22
d0013e14:	3022f500 	eorcc	pc, r2, r0, lsl #10
d0013e18:	2135f890 	teqcs	r5, r0	; <illegal shifter operand>	; <UNPREDICTABLE>
d0013e1c:	5136f890 	teqpl	r6, r0	; <illegal shifter operand>	; <UNPREDICTABLE>
d0013e20:	113ef8b0 	teqne	lr, r0	; <illegal shifter operand>	; <UNPREDICTABLE>
d0013e24:	2e00e69d 	mcrcs	6, 0, lr, cr0, cr13, {4}
d0013e28:	f1b8d1e8 			; <UNDEFINED> instruction: 0xf1b8d1e8
d0013e2c:	d0ea0f00 	rscle	r0, sl, r0, lsl #30
d0013e30:	e6f12704 	ldrbt	r2, [r1], r4, lsl #14
d0013e34:	000c5014 	andeq	r5, ip, r4, lsl r0
d0013e38:	fffffdb0 			; <UNDEFINED> instruction: 0xfffffdb0
d0013e3c:	fffffed3 			; <UNDEFINED> instruction: 0xfffffed3
d0013e40:	fffffd3e 			; <UNDEFINED> instruction: 0xfffffd3e
d0013e44:	fffffd2a 			; <UNDEFINED> instruction: 0xfffffd2a
d0013e48:	fffffe4f 			; <UNDEFINED> instruction: 0xfffffe4f
d0013e4c:	fffffca0 			; <UNDEFINED> instruction: 0xfffffca0
d0013e50:	fffffc85 			; <UNDEFINED> instruction: 0xfffffc85
d0013e54:	fffffbf4 			; <UNDEFINED> instruction: 0xfffffbf4
d0013e58:	fffffbc1 			; <UNDEFINED> instruction: 0xfffffbc1
d0013e5c:	fffffcc9 			; <UNDEFINED> instruction: 0xfffffcc9
d0013e60:	fffffbff 			; <UNDEFINED> instruction: 0xfffffbff
d0013e64:	fffffb75 			; <UNDEFINED> instruction: 0xfffffb75
d0013e68:	fffffb74 			; <UNDEFINED> instruction: 0xfffffb74
d0013e6c:	fffffb7d 			; <UNDEFINED> instruction: 0xfffffb7d
d0013e70:	fffffb4c 			; <UNDEFINED> instruction: 0xfffffb4c
d0013e74:	fffffae3 			; <UNDEFINED> instruction: 0xfffffae3

Disassembly of section .text.initialize_static_buffer.constprop.0:

d0013eac <.text.initialize_static_buffer.constprop.0>:
d0013eac:	480f4602 	stmdami	pc, {r1, r9, sl, lr}	; <UNPREDICTABLE>
d0013eb0:	f5004478 			; <UNDEFINED> instruction: 0xf5004478
d0013eb4:	f8d33300 			; <UNDEFINED> instruction: 0xf8d33300
d0013eb8:	f5c33100 			; <UNDEFINED> instruction: 0xf5c33100
d0013ebc:	42916180 	addsmi	r6, r1, #128, 2
d0013ec0:	d206b510 	andle	fp, r6, #16, 10	; 0x4000000
d0013ec4:	2400490a 	strcs	r4, [r0], #-2314	; 0xfffff6f6
d0013ec8:	f7fc4479 			; <UNDEFINED> instruction: 0xf7fc4479
d0013ecc:	4620f96d 	strtmi	pc, [r0], -sp, ror #18
d0013ed0:	f500bd10 			; <UNDEFINED> instruction: 0xf500bd10
d0013ed4:	009234f8 			; <UNDEFINED> instruction: 0x009234f8
d0013ed8:	f5042100 			; <UNDEFINED> instruction: 0xf5042100
d0013edc:	eb047480 	bl	0xd01310e4
d0013ee0:	46200483 	strtmi	r0, [r0], -r3, lsl #9
d0013ee4:	fa7ef00b 	blx	0xd1fcff18
d0013ee8:	bf00e7f1 	svclt	0x0000e7f1
d0013eec:	0000f56c 	andeq	pc, r0, ip, ror #10
d0013ef0:	ffffffac 			; <UNDEFINED> instruction: 0xffffffac

Disassembly of section .text.initialize_large_zero.constprop.0:

d0013f1c <.text.initialize_large_zero.constprop.0>:
d0013f1c:	4c16b513 	cfldr32mi	mvfx11, [r6], {19}
d0013f20:	4a16217b 	bmi	0xd059c514
d0013f24:	447a447c 	ldrbtmi	r4, [sl], #-1148	; 0xfffffb84
d0013f28:	92014620 	andls	r4, r1, #32, 12	; 0x2000000
d0013f2c:	ff8bf7fe 			; <UNDEFINED> instruction: 0xff8bf7fe
d0013f30:	6ae3b300 	bvs	0xcf900b38
d0013f34:	7381f5a3 	orrvc	pc, r1, #683671552	; 0x28c00000
d0013f38:	d8022b01 	stmdale	r2, {r0, r8, r9, fp, sp}
d0013f3c:	9a016a23 	bls	0xd006e7d0
d0013f40:	490fb143 	stmdbmi	pc, {r0, r1, r6, r8, ip, sp, pc}	; <UNPREDICTABLE>
d0013f44:	4479480f 	ldrbtmi	r4, [r9], #-2063	; 0xfffff7f1
d0013f48:	b0024478 	andlt	r4, r2, r8, ror r4
d0013f4c:	4010e8bd 			; <UNDEFINED> instruction: 0x4010e8bd
d0013f50:	b92af7fc 	stmdblt	sl!, {r2, r3, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}
d0013f54:	92014620 	andls	r4, r1, #32, 12	; 0x2000000
d0013f58:	ff4cf7fe 			; <UNDEFINED> instruction: 0xff4cf7fe
d0013f5c:	4620212c 	strtmi	r2, [r0], -ip, lsr #2
d0013f60:	ff63f7fe 			; <UNDEFINED> instruction: 0xff63f7fe
d0013f64:	217d9a01 	cmncs	sp, r1, lsl #20
d0013f68:	b0024620 	andlt	r4, r2, r0, lsr #12
d0013f6c:	4010e8bd 			; <UNDEFINED> instruction: 0x4010e8bd
d0013f70:	bf69f7fe 	svclt	0x0069f7fe
d0013f74:	bd10b002 	ldclt	0, cr11, [r0, #-8]
d0013f78:	0000f4f8 	strdeq	pc, [r0], -r8
d0013f7c:	ffffffca 			; <UNDEFINED> instruction: 0xffffffca
d0013f80:	ffffffaa 			; <UNDEFINED> instruction: 0xffffffaa
d0013f84:	0000f4d4 	ldrdeq	pc, [r0], -r4

Disassembly of section .text.add_local.constprop.0:

d0013fc4 <.text.add_local.constprop.0>:
d0013fc4:	e92db084 	push	{r2, r7, ip, sp, pc}
d0013fc8:	4d3447f0 	ldcmi	7, cr4, [r4, #-960]!	; 0xfffffc40
d0013fcc:	447dac08 	ldrbtmi	sl, [sp], #-3080	; 0xfffff3f8
d0013fd0:	000fe884 	andeq	lr, pc, r4, lsl #17
d0013fd4:	9a094601 	bls	0xd02657e0
d0013fd8:	f8dd4628 			; <UNDEFINED> instruction: 0xf8dd4628
d0013fdc:	f8dda02c 			; <UNDEFINED> instruction: 0xf8dda02c
d0013fe0:	f89d9030 			; <UNDEFINED> instruction: 0xf89d9030
d0013fe4:	9e0f8038 	mcrls	0, 0, r8, cr15, cr8, {1}
d0013fe8:	fb8cf7fc 	blx	0xce351fe2
d0013fec:	db1b2800 	blle	0xd06ddff4
d0013ff0:	fb032330 	blx	0xd00dccba
d0013ff4:	f5055000 			; <UNDEFINED> instruction: 0xf5055000
d0013ff8:	f5003325 			; <UNDEFINED> instruction: 0xf5003325
d0013ffc:	f8d33022 			; <UNDEFINED> instruction: 0xf8d33022
d0014000:	f890311c 			; <UNDEFINED> instruction: 0xf890311c
d0014004:	429a2134 	addsmi	r2, sl, #52, 2
d0014008:	6dacd10e 	stfvsd	f5, [ip, #56]!	; 0x38
d001400c:	d1422c00 	cmple	r2, r0, lsl #24
d0014010:	66ae4b23 	strtvs	r4, [lr], r3, lsr #22
d0014014:	e9c5447b 	stmib	r5, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0014018:	e9c59818 	stmib	r5, {r3, r4, fp, ip, pc}^
d001401c:	46203a16 			; <UNDEFINED> instruction: 0x46203a16
d0014020:	47f0e8bd 			; <UNDEFINED> instruction: 0x47f0e8bd
d0014024:	4770b004 	ldrbmi	fp, [r0, -r4]!
d0014028:	447b4b1e 	ldrbtmi	r4, [fp], #-2846	; 0xfffff4e2
d001402c:	3725f503 	strcc	pc, [r5, -r3, lsl #10]!
d0014030:	4114f8d7 			; <UNDEFINED> instruction: 0x4114f8d7
d0014034:	d1092c40 	tstle	r9, r0, asr #24
d0014038:	bb646d9c 	bllt	0xd192f6b0
d001403c:	669e4a1a 			; <UNDEFINED> instruction: 0x669e4a1a
d0014040:	e9c3447a 	stmib	r3, {r1, r3, r4, r5, r6, sl, lr}^
d0014044:	e9c39818 	stmib	r3, {r3, r4, fp, ip, pc}^
d0014048:	e7e82a16 			; <UNDEFINED> instruction: 0xe7e82a16
d001404c:	f1042230 			; <UNDEFINED> instruction: 0xf1042230
d0014050:	ae080801 	cdpge	8, 0, cr0, cr8, cr1, {0}
d0014054:	fb022100 	blx	0xd009c45e
d0014058:	f8973304 			; <UNDEFINED> instruction: 0xf8973304
d001405c:	f8c7911c 			; <UNDEFINED> instruction: 0xf8c7911c
d0014060:	f5038114 			; <UNDEFINED> instruction: 0xf5038114
d0014064:	f50a3a22 			; <UNDEFINED> instruction: 0xf50a3a22
d0014068:	4628758a 	strtmi	r7, [r8], -sl, lsl #11
d001406c:	f9baf00b 			; <UNDEFINED> instruction: 0xf9baf00b
d0014070:	9134f88a 	teqls	r4, sl, lsl #17	; <UNPREDICTABLE>
d0014074:	c50fce0f 	strgt	ip, [pc, #-3599]	; 0xd001326d
d0014078:	000fe896 	muleq	pc, r6, r8	; <UNPREDICTABLE>
d001407c:	000fe885 	andeq	lr, pc, r5, lsl #17
d0014080:	3040f89d 	umaalcc	pc, r0, sp, r8	; <UNPREDICTABLE>
d0014084:	3135f88a 	teqcc	r5, sl, lsl #17	; <UNPREDICTABLE>
d0014088:	3118f8d7 			; <UNDEFINED> instruction: 0x3118f8d7
d001408c:	d9c64598 	stmible	r6, {r3, r4, r7, r8, sl, lr}^
d0014090:	8118f8c7 	tsthi	r8, r7, asr #17	; <UNPREDICTABLE>
d0014094:	2400e7c3 	strcs	lr, [r0], #-1987	; 0xfffff83d
d0014098:	bf00e7c1 	svclt	0x0000e7c1
d001409c:	0000f44e 	andeq	pc, r0, lr, asr #8
d00140a0:	ffffff70 			; <UNDEFINED> instruction: 0xffffff70
d00140a4:	0000f3f2 	strdeq	pc, [r0], -r2
d00140a8:	ffffff60 			; <UNDEFINED> instruction: 0xffffff60

Disassembly of section .text.record_definition.constprop.0:

d0014320 <.text.record_definition.constprop.0>:
d0014320:	e92db084 	push	{r2, r7, ip, sp, pc}
d0014324:	f5ad4ff0 			; <UNDEFINED> instruction: 0xf5ad4ff0
d0014328:	f8df7d33 			; <UNDEFINED> instruction: 0xf8df7d33
d001432c:	460654f4 			; <UNDEFINED> instruction: 0x460654f4
d0014330:	447dacbc 	ldrbtmi	sl, [sp], #-3260	; 0xfffff344
d0014334:	a310f8dd 	tstge	r0, #14483456	; 0xdd0000	; <UNPREDICTABLE>
d0014338:	000fe884 	andeq	lr, pc, r4, lsl #17
d001433c:	217b9bbf 	ldrhcs	r9, [fp, #-191]!	; 0xffffff41
d0014340:	24e0f8df 	strbtcs	pc, [r0], #2271	; 0x8df	; <UNPREDICTABLE>
d0014344:	93004628 	movwls	r4, #1576	; 0x628
d0014348:	447a9bc0 	ldrbtmi	r9, [sl], #-3008	; 0xfffff440
d001434c:	93019fbd 	movwls	r9, #8125	; 0x1fbd
d0014350:	3308f89d 	movwcc	pc, #34973	; 0x889d	; <UNPREDICTABLE>
d0014354:	9bc39302 	blls	0xcf0f8f64
d0014358:	f7fe9303 			; <UNDEFINED> instruction: 0xf7fe9303
d001435c:	b910fd74 	ldmdblt	r0, {r2, r4, r5, r6, r8, sl, fp, ip, sp, lr, pc}
d0014360:	34fff04f 	ldrbtcc	pc, [pc], #79	; 0xd0014368	; <UNPREDICTABLE>
d0014364:	9bc5e22b 	blls	0xcf18cc18
d0014368:	f0402b00 			; <UNDEFINED> instruction: 0xf0402b00
d001436c:	465380a1 	ldrbmi	r8, [r3], -r1, lsr #1
d0014370:	4631463a 			; <UNDEFINED> instruction: 0x4631463a
d0014374:	f7fc4628 			; <UNDEFINED> instruction: 0xf7fc4628
d0014378:	f08af95f 			; <UNDEFINED> instruction: 0xf08af95f
d001437c:	46040301 	strmi	r0, [r4], -r1, lsl #6
d0014380:	4631463a 			; <UNDEFINED> instruction: 0x4631463a
d0014384:	f7fc4628 			; <UNDEFINED> instruction: 0xf7fc4628
d0014388:	2800f957 	stmdacs	r0, {r0, r1, r2, r4, r6, r8, fp, ip, sp, lr, pc}
d001438c:	8242f2c0 	subhi	pc, r2, #192, 4
d0014390:	2b006dab 	blcs	0xd002fa44
d0014394:	f8dfd1e4 			; <UNDEFINED> instruction: 0xf8dfd1e4
d0014398:	447b3490 	ldrbtmi	r3, [fp], #-1168	; 0xfffffb70
d001439c:	9b0065ab 	blls	0xd002da50
d00143a0:	9b0165eb 	blls	0xd006db54
d00143a4:	9b02662b 	blls	0xd00adc58
d00143a8:	9b03666b 	blls	0xd00edd5c
d00143ac:	e7d766ab 	ldrb	r6, [r7, fp, lsr #13]
d00143b0:	32e5f505 	rsccc	pc, r5, #20971520	; 0x1400000
d00143b4:	2b186e93 	blcs	0xd062fe08
d00143b8:	6dabd106 	stfvsd	f5, [fp, #24]!
d00143bc:	d1cf2b00 	bicle	r2, pc, r0, lsl #22
d00143c0:	3468f8df 	strbtcc	pc, [r8], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d00143c4:	e7e9447b 			; <UNDEFINED> instruction: 0xe7e9447b
d00143c8:	7a2e1c59 	bvc	0xd0b9b534
d00143cc:	6691469b 			; <UNDEFINED> instruction: 0x6691469b
d00143d0:	721af44f 	andsvc	pc, sl, #1325400064	; 0x4f000000
d00143d4:	fb0299c5 	blx	0xd00baaf2
d00143d8:	f5055503 			; <UNDEFINED> instruction: 0xf5055503
d00143dc:	f50537c8 			; <UNDEFINED> instruction: 0xf50537c8
d00143e0:	37a835c9 	strcc	r3, [r8, r9, asr #11]!
d00143e4:	f00a4638 			; <UNDEFINED> instruction: 0xf00a4638
d00143e8:	f50dfffd 			; <UNDEFINED> instruction: 0xf50dfffd
d00143ec:	f8857c3c 			; <UNDEFINED> instruction: 0xf8857c3c
d00143f0:	f885a10b 			; <UNDEFINED> instruction: 0xf885a10b
d00143f4:	e8bc610e 	ldm	ip!, {r1, r2, r3, r8, sp, lr}
d00143f8:	c70f000f 	strgt	r0, [pc, -pc]
d00143fc:	000fe89c 	muleq	pc, ip, r8	; <UNPREDICTABLE>
d0014400:	000fe887 	andeq	lr, pc, r7, lsl #17
d0014404:	f44fad18 			; <UNDEFINED> instruction: 0xf44fad18
d0014408:	2100721a 	tstcs	r0, sl, lsl r2
d001440c:	462e4628 	strtmi	r4, [lr], -r8, lsr #12
d0014410:	ffe8f00a 			; <UNDEFINED> instruction: 0xffe8f00a
d0014414:	2b009bc5 	blcs	0xd003b330
d0014418:	afc6d04e 	svcge	0x00c6d04e
d001441c:	093cf10d 	ldmdbeq	ip!, {r0, r2, r3, r8, ip, sp, lr, pc}
d0014420:	c60fcf0f 	strgt	ip, [pc], -pc, lsl #30
d0014424:	000fe897 	muleq	pc, r7, r8	; <UNPREDICTABLE>
d0014428:	000fe886 	andeq	lr, pc, r6, lsl #17
d001442c:	f8df9bc5 			; <UNDEFINED> instruction: 0xf8df9bc5
d0014430:	f8856400 			; <UNDEFINED> instruction: 0xf8856400
d0014434:	23013264 	movwcs	r3, #4708	; 0x1264
d0014438:	f885447e 			; <UNDEFINED> instruction: 0xf885447e
d001443c:	f885a263 			; <UNDEFINED> instruction: 0xf885a263
d0014440:	7a333265 	bvc	0xd0ce0ddc
d0014444:	3266f885 	rsbcc	pc, r6, #8716288	; 0x850000
d0014448:	b92b6db3 	stmdblt	fp!, {r0, r1, r4, r5, r7, r8, sl, fp, sp, lr}
d001444c:	2b7d6af3 	blcs	0xd1f6f020
d0014450:	f5b3d002 			; <UNDEFINED> instruction: 0xf5b3d002
d0014454:	d1317f80 	teqle	r1, r0, lsl #31
d0014458:	217d4df6 	ldrshcs	r4, [sp, #-214]!	; 0xffffff2a
d001445c:	447d4af6 	ldrbtmi	r4, [sp], #-2806	; 0xfffff50a
d0014460:	4628447a 			; <UNDEFINED> instruction: 0x4628447a
d0014464:	fceff7fe 	stc2l	7, cr15, [pc], #1016	; 0xd0014864
d0014468:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001446c:	9bc5af79 	blls	0xcf180258
d0014470:	b13baf18 	teqlt	fp, r8, lsl pc
d0014474:	463e3518 			; <UNDEFINED> instruction: 0x463e3518
d0014478:	c60fcd0f 	strgt	ip, [pc], -pc, lsl #26
d001447c:	000fe895 	muleq	pc, r5, r8	; <UNPREDICTABLE>
d0014480:	000fe886 	andeq	lr, pc, r6, lsl #17
d0014484:	3262f897 	rsbcc	pc, r2, #9895936	; 0x970000
d0014488:	f0402b00 			; <UNDEFINED> instruction: 0xf0402b00
d001448c:	4beb813c 	blmi	0xcfaf4984
d0014490:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d0014494:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0014498:	4ae9af63 	bmi	0xcfa8022c
d001449c:	659a447a 	ldrvs	r4, [sl, #1146]	; 0x47a
d00144a0:	65da9a00 	ldrbvs	r9, [sl, #2560]	; 0xa00
d00144a4:	661a9a01 	ldrvs	r9, [sl], -r1, lsl #20
d00144a8:	665a9a02 	ldrbvs	r9, [sl], -r2, lsl #20
d00144ac:	e0dd9a03 	sbcs	r9, sp, r3, lsl #20
d00144b0:	34fff04f 	ldrbtcc	pc, [pc], #79	; 0xd00144b8	; <UNPREDICTABLE>
d00144b4:	e7a546a3 	str	r4, [r5, r3, lsr #13]!
d00144b8:	e7afafbc 			; <UNDEFINED> instruction: 0xe7afafbc
d00144bc:	32c2f89d 	sbccc	pc, r2, #10289152	; 0x9d0000
d00144c0:	d1052b10 	tstle	r5, r0, lsl fp
d00144c4:	463049df 			; <UNDEFINED> instruction: 0x463049df
d00144c8:	f7fb4479 			; <UNDEFINED> instruction: 0xf7fb4479
d00144cc:	e747fe6d 	strb	pc, [r7, -sp, ror #28]	; <UNPREDICTABLE>
d00144d0:	f24023ff 	vcge.s8	q9, q8, <illegal reg q15.5>
d00144d4:	46301107 	ldrtmi	r1, [r0], -r7, lsl #2
d00144d8:	3000f8c9 	andcc	pc, r0, r9, asr #17
d00144dc:	fca5f7fe 	stc2	7, cr15, [r5], #1016	; 0x3f8
d00144e0:	23ffb1e8 	mvnscs	fp, #232, 2	; 0x3a
d00144e4:	3000f8c9 	andcc	pc, r0, r9, asr #17
d00144e8:	212a4dd7 	ldrdcs	r4, [sl, -r7]!
d00144ec:	4628447d 			; <UNDEFINED> instruction: 0x4628447d
d00144f0:	fc9bf7fe 	ldc2	7, cr15, [fp], {254}	; 0xfe
d00144f4:	28009006 	stmdacs	r0, {r1, r2, ip, pc}
d00144f8:	f8d9d14c 			; <UNDEFINED> instruction: 0xf8d9d14c
d00144fc:	2bff3000 	blcs	0xcffe0504
d0014500:	f44fd048 	vst4.16	{d29-d32}, [pc], r8
d0014504:	fb02721a 	blx	0xd00b0d76
d0014508:	f5035303 			; <UNDEFINED> instruction: 0xf5035303
d001450c:	f89333c9 			; <UNDEFINED> instruction: 0xf89333c9
d0014510:	2b00310d 	blcs	0xd002094c
d0014514:	49cdd13e 	stmibmi	sp, {r1, r2, r3, r4, r5, r8, ip, lr, pc}^
d0014518:	44794628 	ldrbtmi	r4, [r9], #-1576	; 0xfffff9d8
d001451c:	6af2e7d5 	bvs	0xcfcce478
d0014520:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d0014524:	d118429a 			; <UNDEFINED> instruction: 0xd118429a
d0014528:	e9d64630 	ldmib	r6, {r4, r5, r9, sl, lr}^
d001452c:	f7fc1206 			; <UNDEFINED> instruction: 0xf7fc1206
d0014530:	2800f92c 	stmdacs	r0, {r2, r3, r5, r8, fp, ip, sp, lr, pc}
d0014534:	4630db11 			; <UNDEFINED> instruction: 0x4630db11
d0014538:	1206e9d6 	andne	lr, r6, #3506176	; 0x358000
d001453c:	f925f7fc 			; <UNDEFINED> instruction: 0xf925f7fc
d0014540:	fb032324 	blx	0xd00dd1da
d0014544:	f5006000 			; <UNDEFINED> instruction: 0xf5006000
d0014548:	f89030e5 			; <UNDEFINED> instruction: 0xf89030e5
d001454c:	2bff308c 	blcs	0xcffe0784
d0014550:	4630d103 	ldrtmi	sp, [r0], -r3, lsl #2
d0014554:	fc4ef7fe 	mcrr2	7, 15, pc, lr, cr14	; <UNPREDICTABLE>
d0014558:	48bde7c6 	popmi	{r1, r2, r6, r7, r8, r9, sl, sp, lr, pc}
d001455c:	131bf240 	tstne	fp, #64, 4	; <UNPREDICTABLE>
d0014560:	6ac24478 	bvs	0xcf0a5748
d0014564:	d103429a 			; <UNDEFINED> instruction: 0xd103429a
d0014568:	ff60f7fe 			; <UNDEFINED> instruction: 0xff60f7fe
d001456c:	d1b82800 			; <UNDEFINED> instruction: 0xd1b82800
d0014570:	464948b8 			; <UNDEFINED> instruction: 0x464948b8
d0014574:	f7fe4478 			; <UNDEFINED> instruction: 0xf7fe4478
d0014578:	2800fe63 	stmdacs	r0, {r0, r1, r5, r6, r9, sl, fp, ip, sp, lr, pc}
d001457c:	f1bad1b4 			; <UNDEFINED> instruction: 0xf1bad1b4
d0014580:	d1040f00 	tstle	r4, r0, lsl #30
d0014584:	447949b4 	ldrbtmi	r4, [r9], #-2484	; 0xfffff64c
d0014588:	447848b4 	ldrbtmi	r4, [r8], #-2228	; 0xfffff74c
d001458c:	49b4e79d 	ldmibmi	r4!, {r0, r2, r3, r4, r7, r8, r9, sl, sp, lr, pc}
d0014590:	e7f94479 			; <UNDEFINED> instruction: 0xe7f94479
d0014594:	af104db3 	svcge	0x00104db3
d0014598:	f105447d 			; <UNDEFINED> instruction: 0xf105447d
d001459c:	e8bc0c18 	ldm	ip!, {r3, r4, sl, fp}
d00145a0:	c70f000f 	strgt	r0, [pc, -pc]
d00145a4:	000fe89c 	muleq	pc, ip, r8	; <UNPREDICTABLE>
d00145a8:	000fe887 	andeq	lr, pc, r7, lsl #17
d00145ac:	f24069ab 	vmla.i8	d22, d16, d27
d00145b0:	4aad1101 	bmi	0xceb589bc
d00145b4:	930b4628 	movwls	r4, #46632	; 0xb628
d00145b8:	447a69eb 	ldrbtmi	r6, [sl], #-2539	; 0xfffff615
d00145bc:	6a6b930a 	bvs	0xd1af91ec
d00145c0:	6aab9305 	bvs	0xceaf91dc
d00145c4:	f8959309 			; <UNDEFINED> instruction: 0xf8959309
d00145c8:	93083030 	movwls	r3, #32816	; 0x8030
d00145cc:	93076b6b 	movwls	r6, #31595	; 0x7b6b
d00145d0:	fc39f7fe 	ldc2	7, cr15, [r9], #-1016	; 0xfffffc08
d00145d4:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d00145d8:	4aa4aec3 	bmi	0xce9400ec
d00145dc:	4628213b 			; <UNDEFINED> instruction: 0x4628213b
d00145e0:	f7fe447a 			; <UNDEFINED> instruction: 0xf7fe447a
d00145e4:	2800fc30 	stmdacs	r0, {r4, r5, sl, fp, ip, sp, lr, pc}
d00145e8:	aebaf43f 	mrcge	4, 5, APSR_nzcv, cr10, cr15, {1}
d00145ec:	2700ad18 	smladcs	r0, r8, sp, sl
d00145f0:	f89846a8 			; <UNDEFINED> instruction: 0xf89846a8
d00145f4:	4567c262 	strbmi	ip, [r7, #-610]!	; 0xfffffd9e
d00145f8:	9b06d31c 	blls	0xd01c9270
d00145fc:	d13c2b00 	teqle	ip, r0, lsl #22
d0014600:	3000f8d9 	ldrdcc	pc, [r0], -r9
d0014604:	d0382bff 	ldrshtle	r2, [r8], -pc
d0014608:	f44f4a99 	vst1.32	{d20-d21}, [pc :64], r9
d001460c:	447a711a 	ldrbtmi	r7, [sl], #-282	; 0xfffffee6
d0014610:	2303fb01 	movwcs	pc, #15105	; 0x3b01	; <UNPREDICTABLE>
d0014614:	33c9f503 	biccc	pc, r9, #12582912	; 0xc00000
d0014618:	e108f8b3 			; <UNDEFINED> instruction: 0xe108f8b3
d001461c:	0f00f1be 	svceq	0x0000f1be
d0014620:	4b94d12d 	blmi	0xce548adc
d0014624:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d0014628:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d001462c:	4a92ae99 	bmi	0xce4c0098
d0014630:	e013447a 	ands	r4, r3, sl, ror r4
d0014634:	35246a69 	strcc	r6, [r4, #-2665]!	; 0xfffff597
d0014638:	0c04f855 	stceq	8, cr15, [r4], {85}	; 0x55
d001463c:	9a0b9b0a 	bls	0xd02fb26c
d0014640:	ffecf7fb 			; <UNDEFINED> instruction: 0xffecf7fb
d0014644:	f1bab1b8 			; <UNDEFINED> instruction: 0xf1bab1b8
d0014648:	d1110f00 	tstle	r1, r0, lsl #30
d001464c:	447a4a8b 	ldrbtmi	r4, [sl], #-2699	; 0xfffff575
d0014650:	447b4b8b 	ldrbtmi	r4, [fp], #-2955	; 0xfffff475
d0014654:	29006d99 	stmdbcs	r0, {r0, r3, r4, r7, r8, sl, fp, sp, lr}
d0014658:	ae82f47f 	mcrge	4, 4, pc, cr2, cr15, {3}	; <UNPREDICTABLE>
d001465c:	9a05659a 	bls	0xd016dccc
d0014660:	9a0965da 	bls	0xd026ddd0
d0014664:	9a08661a 	bls	0xd022ded4
d0014668:	9a07665a 	bls	0xd01edfd8
d001466c:	e677669a 			; <UNDEFINED> instruction: 0xe677669a
d0014670:	447a4a84 	ldrbtmi	r4, [sl], #-2692	; 0xfffff57c
d0014674:	3701e7ec 	strcc	lr, [r1, -ip, ror #15]
d0014678:	f04fe7bb 			; <UNDEFINED> instruction: 0xf04fe7bb
d001467c:	ab180e01 	blge	0xd0617e88
d0014680:	82c0f8bd 	sbchi	pc, r0, #12386304	; 0xbd0000
d0014684:	f5c89304 			; <UNDEFINED> instruction: 0xf5c89304
d0014688:	33ff437f 	mvnscc	r4, #-67108863	; 0xfc000001
d001468c:	d3c84573 	bicle	r4, r8, #482344960	; 0x1cc00000
d0014690:	f10c9a04 			; <UNDEFINED> instruction: 0xf10c9a04
d0014694:	f1ba0301 			; <UNDEFINED> instruction: 0xf1ba0301
d0014698:	ad100f00 	ldcge	15, cr0, [r0, #-0]
d001469c:	3262f882 	rsbcc	pc, r2, #8519680	; 0x820000
d00146a0:	3000f899 	mulcc	r0, r9, r8
d00146a4:	bf0c930c 	svclt	0x000c930c
d00146a8:	23004643 	movwcs	r4, #1603	; 0x643
d00146ac:	9b0b930d 	blls	0xd02f92e8
d00146b0:	9b0a9310 	blls	0xd02b92f8
d00146b4:	9b059311 	blls	0xd0179300
d00146b8:	9b099313 	blls	0xd027930c
d00146bc:	9b089314 	blls	0xd0239314
d00146c0:	3058f88d 	subscc	pc, r8, sp, lsl #17
d00146c4:	93179b07 	tstls	r7, #7168	; 0x1c00
d00146c8:	0324f04f 	msreq	CPSR_s, #79	; 0x4f
d00146cc:	2c0cfb03 			; <UNDEFINED> instruction: 0x2c0cfb03
d00146d0:	f10ccd0f 			; <UNDEFINED> instruction: 0xf10ccd0f
d00146d4:	c70f0720 	strgt	r0, [pc, -r0, lsr #14]
d00146d8:	000fe895 	muleq	pc, r5, r8	; <UNPREDICTABLE>
d00146dc:	000fe887 	andeq	lr, pc, r7, lsl #17
d00146e0:	f88c9b0c 			; <UNDEFINED> instruction: 0xf88c9b0c
d00146e4:	9b063040 	blls	0xd01a07ec
d00146e8:	3041f88c 	subcc	pc, r1, ip, lsl #17
d00146ec:	f8ac9b0d 			; <UNDEFINED> instruction: 0xf8ac9b0d
d00146f0:	d0063042 	andle	r3, r6, r2, asr #32
d00146f4:	f4bf45f0 			; <UNDEFINED> instruction: 0xf4bf45f0
d00146f8:	9b04aea7 	blls	0xd014019c
d00146fc:	e260f8a3 	rsb	pc, r0, #10682368	; 0xa30000
d0014700:	44c6e6a2 	strbmi	lr, [r6], #1698	; 0x6a2
d0014704:	9bc5e7f9 	blls	0xcf18e6f0
d0014708:	4e5fb17b 	mrcmi	1, 2, fp, cr15, cr11, {3}
d001470c:	0800f04f 	stmdaeq	r0, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d0014710:	0960f10d 	stmdbeq	r0!, {r0, r2, r3, r8, ip, sp, lr, pc}^
d0014714:	f506447e 			; <UNDEFINED> instruction: 0xf506447e
d0014718:	f50635c8 			; <UNDEFINED> instruction: 0xf50635c8
d001471c:	35a833e5 	strcc	r3, [r8, #997]!	; 0x3e5
d0014720:	9b049304 	blls	0xd0139338
d0014724:	45986e9b 	ldrmi	r6, [r8, #3739]	; 0xe9b
d0014728:	2c00d31b 	stccs	3, cr13, [r0], {27}
d001472c:	f44fdb37 			; <UNDEFINED> instruction: 0xf44fdb37
d0014730:	4956731a 	ldmdbmi	r6, {r1, r3, r4, r8, r9, ip, sp, lr}^
d0014734:	4363a818 	cmnmi	r3, #24, 16	; 0x180000
d0014738:	f5034479 			; <UNDEFINED> instruction: 0xf5034479
d001473c:	33a833c8 			; <UNDEFINED> instruction: 0x33a833c8
d0014740:	f7fb4419 			; <UNDEFINED> instruction: 0xf7fb4419
d0014744:	2800ffa0 	stmdacs	r0, {r5, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0014748:	f1bad139 			; <UNDEFINED> instruction: 0xf1bad139
d001474c:	d1230f00 			; <UNDEFINED> instruction: 0xd1230f00
d0014750:	447a4a4f 	ldrbtmi	r4, [sl], #-2639	; 0xfffff5b1
d0014754:	447b4b4f 	ldrbtmi	r4, [fp], #-2895	; 0xfffff4b1
d0014758:	29006d99 	stmdbcs	r0, {r0, r3, r4, r7, r8, sl, fp, sp, lr}
d001475c:	ae00f47f 	mcrge	4, 0, pc, cr0, cr15, {3}	; <UNPREDICTABLE>
d0014760:	f895e69d 			; <UNDEFINED> instruction: 0xf895e69d
d0014764:	b1933264 	orrslt	r3, r3, r4, ror #4
d0014768:	2266f895 	rsbcs	pc, r6, #9764864	; 0x950000
d001476c:	429a7a33 	addsmi	r7, sl, #208896	; 0x33000
d0014770:	e9d9d00d 	ldmib	r9, {r0, r2, r3, ip, lr, pc}^
d0014774:	e9d52300 	ldmib	r5, {r8, r9, sp}^
d0014778:	f7fb0100 			; <UNDEFINED> instruction: 0xf7fb0100
d001477c:	b130ff4f 	teqlt	r0, pc, asr #30	; <UNPREDICTABLE>
d0014780:	46484629 	strbmi	r4, [r8], -r9, lsr #12
d0014784:	ff7ff7fb 			; <UNDEFINED> instruction: 0xff7ff7fb
d0014788:	4644b108 	strbmi	fp, [r4], -r8, lsl #2
d001478c:	f108e7cf 			; <UNDEFINED> instruction: 0xf108e7cf
d0014790:	f5050801 			; <UNDEFINED> instruction: 0xf5050801
d0014794:	e7c4751a 	bfi	r7, sl, (invalid: 10:4)
d0014798:	447a4a3f 	ldrbtmi	r4, [sl], #-2623	; 0xfffff5c1
d001479c:	f1bbe7da 			; <UNDEFINED> instruction: 0xf1bbe7da
d00147a0:	db130f00 	blle	0xd04d83a8
d00147a4:	f44f483d 	vst2.8	{d20-d21}, [pc :256]!
d00147a8:	465c721a 			; <UNDEFINED> instruction: 0x465c721a
d00147ac:	44784639 	ldrbtmi	r4, [r8], #-1593	; 0xfffff9c7
d00147b0:	000bfb02 	andeq	pc, fp, r2, lsl #22
d00147b4:	30c8f500 	sbccc	pc, r8, r0, lsl #10
d00147b8:	f00a30a8 			; <UNDEFINED> instruction: 0xf00a30a8
d00147bc:	4620fe21 	strtmi	pc, [r0], -r1, lsr #28
d00147c0:	7d33f50d 	cfldr32vc	mvfx15, [r3, #-52]!	; 0xffffffcc
d00147c4:	4ff0e8bd 	svcmi	0x00f0e8bd
d00147c8:	4770b004 	ldrbmi	fp, [r0, -r4]!
d00147cc:	44784834 	ldrbtmi	r4, [r8], #-2100	; 0xfffff7cc
d00147d0:	33e5f500 	mvncc	pc, #0, 10
d00147d4:	2c186e9c 	ldccs	14, cr6, [r8], {156}	; 0x9c
d00147d8:	6d83d10f 	stfvsd	f5, [r3, #60]	; 0x3c
d00147dc:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d00147e0:	4b30adbf 	blmi	0xd0c3fee4
d00147e4:	6583447b 	strvs	r4, [r3, #1147]	; 0x47b
d00147e8:	65c39b00 	strbvs	r9, [r3, #2816]	; 0xb00
d00147ec:	66039b01 	strvs	r9, [r3], -r1, lsl #22
d00147f0:	66439b02 	strbvs	r9, [r3], -r2, lsl #22
d00147f4:	66839b03 	strvs	r9, [r3], r3, lsl #22
d00147f8:	1c62e5b2 	cfstr64ne	mvdx14, [r2], #-712	; 0xfffffd38
d00147fc:	669a4639 			; <UNDEFINED> instruction: 0x669a4639
d0014800:	721af44f 	andsvc	pc, sl, #1325400064	; 0x4f000000
d0014804:	0004fb02 	andeq	pc, r4, r2, lsl #22
d0014808:	30c8f500 	sbccc	pc, r8, r0, lsl #10
d001480c:	f00a30a8 			; <UNDEFINED> instruction: 0xf00a30a8
d0014810:	e7d4fdf7 			; <UNDEFINED> instruction: 0xe7d4fdf7
d0014814:	f6ff2c00 			; <UNDEFINED> instruction: 0xf6ff2c00
d0014818:	f04fadcb 			; <UNDEFINED> instruction: 0xf04fadcb
d001481c:	e5f13bff 	ldrb	r3, [r1, #3071]!	; 0xbff
d0014820:	0000f0ea 	andeq	pc, r0, sl, ror #1
d0014824:	fffffe63 			; <UNDEFINED> instruction: 0xfffffe63
d0014828:	fffffe32 			; <UNDEFINED> instruction: 0xfffffe32
d001482c:	fffffe35 			; <UNDEFINED> instruction: 0xfffffe35
d0014830:	0000efe4 	andeq	lr, r0, r4, ror #31
d0014834:	0000efbe 			; <UNDEFINED> instruction: 0x0000efbe
d0014838:	fffffe73 			; <UNDEFINED> instruction: 0xfffffe73
d001483c:	0000ef8c 	andeq	lr, r0, ip, lsl #31
d0014840:	fffffe58 			; <UNDEFINED> instruction: 0xfffffe58
d0014844:	fffffd53 			; <UNDEFINED> instruction: 0xfffffd53
d0014848:	0000ef30 	andeq	lr, r0, r0, lsr pc
d001484c:	fffffd1f 			; <UNDEFINED> instruction: 0xfffffd1f
d0014850:	0000eebc 			; <UNDEFINED> instruction: 0x0000eebc
d0014854:	0000eea8 	andeq	lr, r0, r8, lsr #29
d0014858:	fffffb70 			; <UNDEFINED> instruction: 0xfffffb70
d001485c:	0000ee92 	muleq	r0, r2, lr
d0014860:	fffffb18 			; <UNDEFINED> instruction: 0xfffffb18
d0014864:	0000ee84 	andeq	lr, r0, r4, lsl #29
d0014868:	fffffcb3 			; <UNDEFINED> instruction: 0xfffffcb3
d001486c:	fffffca8 			; <UNDEFINED> instruction: 0xfffffca8
d0014870:	0000ee0e 	andeq	lr, r0, lr, lsl #28
d0014874:	0000edf8 	strdeq	lr, [r0], -r8
d0014878:	fffffc78 			; <UNDEFINED> instruction: 0xfffffc78
d001487c:	fffffb0d 			; <UNDEFINED> instruction: 0xfffffb0d
d0014880:	0000edca 	andeq	lr, r0, sl, asr #27
d0014884:	fffffad3 			; <UNDEFINED> instruction: 0xfffffad3
d0014888:	0000ed08 	andeq	lr, r0, r8, lsl #26
d001488c:	0000ece4 	andeq	lr, r0, r4, ror #25
d0014890:	fffffa3d 			; <UNDEFINED> instruction: 0xfffffa3d
d0014894:	0000ecc6 	andeq	lr, r0, r6, asr #25
d0014898:	fffff9d8 			; <UNDEFINED> instruction: 0xfffff9d8
d001489c:	0000ec6e 	andeq	lr, r0, lr, ror #24
d00148a0:	0000ec4e 	andeq	lr, r0, lr, asr #24
d00148a4:	fffffa15 			; <UNDEFINED> instruction: 0xfffffa15

Disassembly of section .text.load_apicore.constprop.0:

d0014938 <.text.load_apicore.constprop.0>:
d0014938:	47f0e92d 	ldrbmi	lr, [r0, sp, lsr #18]!
d001493c:	b0864603 	addlt	r4, r6, r3, lsl #12
d0014940:	4983b938 	stmibmi	r3, {r3, r4, r5, r8, fp, ip, sp, pc}
d0014944:	44794883 	ldrbtmi	r4, [r9], #-2179	; 0xfffff77d
d0014948:	f7fb4478 			; <UNDEFINED> instruction: 0xf7fb4478
d001494c:	2000fc2d 	andcs	pc, r0, sp, lsr #24
d0014950:	4e81e09b 	mcrmi	0, 4, lr, cr1, cr11, {4}
d0014954:	418cf242 	orrmi	pc, ip, r2, asr #4
d0014958:	4630447e 			; <UNDEFINED> instruction: 0x4630447e
d001495c:	28004798 	stmdacs	r0, {r3, r4, r7, r8, r9, sl, lr}
d0014960:	f1a0d0ef 			; <UNDEFINED> instruction: 0xf1a0d0ef
d0014964:	f2420218 	vqsub.s8	d16, d2, d8
d0014968:	429a4374 	addsmi	r4, sl, #116, 6	; 0xd0000001
d001496c:	80e9f200 	rschi	pc, r9, r0, lsl #4
d0014970:	22041f04 	andcs	r1, r4, #4, 30
d0014974:	19314668 	ldmdbne	r1!, {r3, r5, r6, r9, sl, lr}
d0014978:	fd42f00a 	stc2l	0, cr15, [r2, #-40]	; 0xffffffd8
d001497c:	46304621 	ldrtmi	r4, [r0], -r1, lsr #12
d0014980:	fbfaf7fb 	blx	0xcfed2976
d0014984:	42989b00 	addsmi	r9, r8, #0, 22
d0014988:	80dbf040 	sbcshi	pc, fp, r0, asr #32
d001498c:	2214ad01 	andscs	sl, r4, #1, 26	; 0x40
d0014990:	46284631 			; <UNDEFINED> instruction: 0x46284631
d0014994:	fd34f00a 	ldc2	0, cr15, [r4, #-40]!	; 0xffffffd8
d0014998:	22084970 	andcs	r4, r8, #112, 18	; 0x1c0000
d001499c:	44794628 	ldrbtmi	r4, [r9], #-1576	; 0xfffff9d8
d00149a0:	fd3ef00a 	ldc2	0, cr15, [lr, #-40]!	; 0xffffffd8
d00149a4:	496eb120 	stmdbmi	lr!, {r5, r8, ip, sp, pc}^
d00149a8:	4479486e 	ldrbtmi	r4, [r9], #-2158	; 0xfffff792
d00149ac:	e7cc4478 			; <UNDEFINED> instruction: 0xe7cc4478
d00149b0:	9a034b66 	bls	0xd00e7750
d00149b4:	f040429a 			; <UNDEFINED> instruction: 0xf040429a
d00149b8:	9a0480c4 	bls	0xd0134cd0
d00149bc:	2b4f1e53 	blcs	0xd13dc310
d00149c0:	80bff200 	adcshi	pc, pc, r0, lsl #4
d00149c4:	2b489b05 	blcs	0xd123b5e0
d00149c8:	80bbf200 	adcshi	pc, fp, r0, lsl #4
d00149cc:	43512154 	cmpmi	r1, #84, 2
d00149d0:	435a2224 	cmpmi	sl, #36, 4	; 0x40000002
d00149d4:	f107188f 			; <UNDEFINED> instruction: 0xf107188f
d00149d8:	429c0328 	addsmi	r0, ip, #40, 6	; 0xa0000000
d00149dc:	80b1f040 	adcshi	pc, r1, r0, asr #32
d00149e0:	31144c61 	tstcc	r4, r1, ror #24
d00149e4:	4431447c 	ldrtmi	r4, [r1], #-1148	; 0xfffffb84
d00149e8:	406af504 	rsbmi	pc, sl, r4, lsl #10
d00149ec:	f00a3064 			; <UNDEFINED> instruction: 0xf00a3064
d00149f0:	f107fd07 			; <UNDEFINED> instruction: 0xf107fd07
d00149f4:	f5040114 			; <UNDEFINED> instruction: 0xf5040114
d00149f8:	22144074 	andscs	r4, r4, #116	; 0x74
d00149fc:	30844431 	addcc	r4, r4, r1, lsr r4
d0014a00:	fcfef00a 	ldc2l	0, cr15, [lr], #40	; 0x28
d0014a04:	4394f24f 	orrsmi	pc, r4, #-268435452	; 0xf0000004
d0014a08:	f6405ae0 			; <UNDEFINED> instruction: 0xf6405ae0
d0014a0c:	1f0273fc 	svcne	0x000273fc
d0014a10:	f200429a 	vqsub.s8	d4, d16, d10
d0014a14:	4a558096 	bmi	0xd1574c74
d0014a18:	4196f24f 	orrsmi	pc, r6, pc, asr #4
d0014a1c:	0303f000 	movweq	pc, #12288	; 0x3000	; <UNPREDICTABLE>
d0014a20:	5a51447a 	bpl	0xd1465c10
d0014a24:	f040430b 			; <UNDEFINED> instruction: 0xf040430b
d0014a28:	f502808c 			; <UNDEFINED> instruction: 0xf502808c
d0014a2c:	21044274 	tstcs	r4, r4, ror r2
d0014a30:	f8323284 			; <UNDEFINED> instruction: 0xf8323284
d0014a34:	1e4e4b02 	vmlane.f64	d20, d14, d2
d0014a38:	f0404026 			; <UNDEFINED> instruction: 0xf0404026
d0014a3c:	1a418082 	bne	0xd1074c4c
d0014a40:	d87e428c 	ldmdale	lr!, {r2, r3, r7, r9, lr}^
d0014a44:	2b083301 	blcs	0xd0221650
d0014a48:	4c49d122 	stfmip	f5, [r9], {34}	; 0x22
d0014a4c:	4f4946b0 	svcmi	0x004946b0
d0014a50:	79fcf640 	ldmibvc	ip!, {r6, r9, sl, ip, sp, lr, pc}^
d0014a54:	447f447c 	ldrbtmi	r4, [pc], #-1148	; 0xd0014a5c
d0014a58:	4450f504 	ldrbmi	pc, [r0], #-1284	; 0xfffffafc	; <UNPREDICTABLE>
d0014a5c:	346c3714 	strbtcc	r3, [ip], #-1812	; 0xfffff8ec
d0014a60:	45989b04 	ldrmi	r9, [r8, #2820]	; 0xb04
d0014a64:	4c44d319 	mcrrmi	3, 1, sp, r4, cr9
d0014a68:	f504447c 			; <UNDEFINED> instruction: 0xf504447c
d0014a6c:	3464446a 	strbtcc	r4, [r4], #-1130	; 0xfffffb96
d0014a70:	429e9b05 	addsmi	r9, lr, #5120	; 0x1400
d0014a74:	4c41d35c 	mcrrmi	3, 5, sp, r1, cr12
d0014a78:	f504447c 			; <UNDEFINED> instruction: 0xf504447c
d0014a7c:	cd0f4450 	cfstrsgt	mvf4, [pc, #-320]	; 0xd0014944
d0014a80:	c40f3410 	strgt	r3, [pc], #-1040	; 0xd0014a88
d0014a84:	2001682b 	andcs	r6, r1, fp, lsr #16
d0014a88:	b0066023 	andlt	r6, r6, r3, lsr #32
d0014a8c:	87f0e8bd 			; <UNDEFINED> instruction: 0x87f0e8bd
d0014a90:	bf0c2b01 	svclt	0x000c2b01
d0014a94:	21042101 	tstcs	r4, r1, lsl #2
d0014a98:	f1a4e7cb 			; <UNDEFINED> instruction: 0xf1a4e7cb
d0014a9c:	22540a48 	subscs	r0, r4, #72, 20	; 0x48000
d0014aa0:	46504639 			; <UNDEFINED> instruction: 0x46504639
d0014aa4:	fcacf00a 	stc2	0, cr15, [ip], #40	; 0x28
d0014aa8:	21402201 	cmpcs	r0, r1, lsl #4
d0014aac:	f7fb4650 			; <UNDEFINED> instruction: 0xf7fb4650
d0014ab0:	2800fc79 	stmdacs	r0, {r0, r3, r4, r5, r6, sl, fp, ip, sp, lr, pc}
d0014ab4:	f814d045 			; <UNDEFINED> instruction: 0xf814d045
d0014ab8:	2a0c2c02 	bcs	0xd031fac8
d0014abc:	f814d841 			; <UNDEFINED> instruction: 0xf814d841
d0014ac0:	1f593c01 	svcne	0x00593c01
d0014ac4:	d9012903 	stmdble	r1, {r0, r1, r8, fp, sp}
d0014ac8:	d13a2b0b 	teqle	sl, fp, lsl #22
d0014acc:	1c08f834 	stcne	8, cr15, [r8], {52}	; 0x34
d0014ad0:	73fff64f 	mvnsvc	pc, #82837504	; 0x4f00000
d0014ad4:	d0344299 	mlasle	r4, r9, r2, r4
d0014ad8:	1c06f834 	stcne	8, cr15, [r6], {52}	; 0x34
d0014adc:	d0304299 	mlasle	r0, r9, r2, r4
d0014ae0:	0c08f1a4 	stfeqd	f7, [r8], {164}	; 0xa4
d0014ae4:	f83c2100 			; <UNDEFINED> instruction: 0xf83c2100
d0014ae8:	42980b02 	addsmi	r0, r8, #2048	; 0x800
d0014aec:	4548d003 	strbmi	sp, [r8, #-3]
d0014af0:	0780d827 	streq	sp, [r0, r7, lsr #16]
d0014af4:	3101d125 	tstcc	r1, r5, lsr #2
d0014af8:	d1f42903 	mvnsle	r2, r3, lsl #18
d0014afc:	23004621 	movwcs	r4, #1569	; 0x621
d0014b00:	d806429a 	stmdale	r6, {r1, r3, r4, r7, r9, lr}
d0014b04:	d10f2a0c 	tstle	pc, ip, lsl #20
d0014b08:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d0014b0c:	37543454 			; <UNDEFINED> instruction: 0x37543454
d0014b10:	f811e7a6 			; <UNDEFINED> instruction: 0xf811e7a6
d0014b14:	f1000b01 			; <UNDEFINED> instruction: 0xf1000b01
d0014b18:	f1bc3cff 			; <UNDEFINED> instruction: 0xf1bc3cff
d0014b1c:	d8100f0e 	ldmdale	r0, {r1, r2, r3, r8, r9, sl, fp}
d0014b20:	d00e2807 	andle	r2, lr, r7, lsl #16
d0014b24:	e7eb3301 	strb	r3, [fp, r1, lsl #6]!
d0014b28:	b9535ca3 	ldmdblt	r3, {r0, r1, r5, r7, sl, fp, ip, lr}^
d0014b2c:	e7e93201 	strb	r3, [r9, r1, lsl #4]!
d0014b30:	22004620 	andcs	r4, r0, #32, 12	; 0x2000000
d0014b34:	34242120 	strtcc	r2, [r4], #-288	; 0xfffffee0
d0014b38:	fc34f7fb 	ldc2	7, cr15, [r4], #-1004	; 0xfffffc14
d0014b3c:	3601b108 	strcc	fp, [r1], -r8, lsl #2
d0014b40:	490fe796 	stmdbmi	pc, {r1, r2, r4, r7, r8, r9, sl, sp, lr, pc}	; <UNPREDICTABLE>
d0014b44:	4479480f 	ldrbtmi	r4, [r9], #-2063	; 0xfffff7f1
d0014b48:	e6fe4478 	uxtah	r4, lr, r8, ror #8
d0014b4c:	2001f000 	andcs	pc, r1, r0
d0014b50:	ffffff5e 			; <UNDEFINED> instruction: 0xffffff5e
d0014b54:	0000ead4 	ldrdeq	lr, [r0], -r4
d0014b58:	0000c634 	andeq	ip, r0, r4, lsr r6
d0014b5c:	ffffff2f 			; <UNDEFINED> instruction: 0xffffff2f
d0014b60:	ffffff2b 			; <UNDEFINED> instruction: 0xffffff2b
d0014b64:	0000ea70 	andeq	lr, r0, r0, ror sl
d0014b68:	0000ea38 	andeq	lr, r0, r8, lsr sl
d0014b6c:	0000e9fc 	strdeq	lr, [r0], -ip
d0014b70:	0000e9c8 	andeq	lr, r0, r8, asr #19
d0014b74:	0000c536 	andeq	ip, r0, r6, lsr r5
d0014b78:	0000e9b4 			; <UNDEFINED> instruction: 0x0000e9b4
d0014b7c:	0000e9a4 	andeq	lr, r0, r4, lsr #19
d0014b80:	fffffdd3 			; <UNDEFINED> instruction: 0xfffffdd3
d0014b84:	0000e8d4 	ldrdeq	lr, [r0], -r4

Disassembly of section .text.accept_sdk_type.constprop.0:

d0014b88 <.text.accept_sdk_type.constprop.0>:
d0014b88:	4c0cb538 	cfstr32mi	mvfx11, [ip], {56}	; 0x38
d0014b8c:	031cf24d 	tsteq	ip, #-805306364	; 0xd0000004	; <UNPREDICTABLE>
d0014b90:	447c4602 	ldrbtmi	r4, [ip], #-1538	; 0xfffff9fe
d0014b94:	b17b58e3 	cmnlt	fp, r3, ror #17
d0014b98:	f2406ae5 	vpmax.s8	q11, q8, <illegal reg q10.5>
d0014b9c:	429d1301 	addsmi	r1, sp, #67108864	; 0x4000000
d0014ba0:	e9d4d10a 	ldmib	r4, {r1, r3, r8, ip, lr, pc}^
d0014ba4:	f7fb0106 			; <UNDEFINED> instruction: 0xf7fb0106
d0014ba8:	b128fe5c 	msrlt	R8_fiq, ip
d0014bac:	46204629 	strtmi	r4, [r0], -r9, lsr #12
d0014bb0:	4038e8bd 	ldrhtmi	lr, [r8], -sp
d0014bb4:	b939f7fe 	ldmdblt	r9!, {r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}
d0014bb8:	bd382000 	ldclt	0, cr2, [r8, #-0]
d0014bbc:	0000e88a 	andeq	lr, r0, sl, lsl #17

Disassembly of section .text.wide_immediate:

d0014bc0 <.text.wide_immediate>:
d0014bc0:	085db530 	ldmdaeq	sp, {r4, r5, r8, sl, ip, sp, pc}^
d0014bc4:	3413ea41 	ldrcc	lr, [r3], #-2625	; 0xfffff5bf
d0014bc8:	6580f405 	strvs	pc, [r0, #1029]	; 0x405
d0014bcc:	011bb2d9 			; <UNDEFINED> instruction: 0x011bb2d9
d0014bd0:	ea41432c 	b	0xd1065888
d0014bd4:	4d0a2202 	sfmmi	f2, 4, [sl, #-8]
d0014bd8:	41e0f403 	mvnmi	pc, r3, lsl #8
d0014bdc:	447db224 	ldrbtmi	fp, [sp], #-548	; 0xfffffddc
d0014be0:	4428430a 	strtmi	r4, [r8], #-778	; 0xfffffcf6
d0014be4:	f880b292 			; <UNDEFINED> instruction: 0xf880b292
d0014be8:	f3c44040 	vmla.i<illegal width 8>	q10, q2, d0[0]
d0014bec:	f8802407 			; <UNDEFINED> instruction: 0xf8802407
d0014bf0:	0a122042 	beq	0xd049cd00
d0014bf4:	4041f880 	submi	pc, r1, r0, lsl #17
d0014bf8:	2043f880 	subcs	pc, r3, r0, lsl #17
d0014bfc:	bf00bd30 	svclt	0x0000bd30
d0014c00:	00039dbe 			; <UNDEFINED> instruction: 0x00039dbe

Disassembly of section .text.emit:

d0014c20 <.text.emit>:
d0014c20:	b4706d82 	ldrbtlt	r6, [r0], #-3458	; 0xfffff27e
d0014c24:	f24fb9a2 	vmla.i8	d27, d31, d18
d0014c28:	59064498 	stmdbpl	r6, {r3, r4, r7, sl, lr}
d0014c2c:	f5b51cb5 			; <UNDEFINED> instruction: 0xf5b51cb5
d0014c30:	d9043f80 	stmdble	r4, {r7, r8, r9, sl, fp, ip, sp}
d0014c34:	bc704907 			; <UNDEFINED> instruction: 0xbc704907
d0014c38:	f7fb4479 			; <UNDEFINED> instruction: 0xf7fb4479
d0014c3c:	4a06bab5 	bmi	0xd01c3718
d0014c40:	4432447a 	ldrtmi	r4, [r2], #-1146	; 0xfffffb86
d0014c44:	1040f882 	subne	pc, r0, r2, lsl #17
d0014c48:	f8820a09 			; <UNDEFINED> instruction: 0xf8820a09
d0014c4c:	51051041 	tstpl	r5, r1, asr #32
d0014c50:	4770bc70 			; <UNDEFINED> instruction: 0x4770bc70
d0014c54:	ffffffc8 			; <UNDEFINED> instruction: 0xffffffc8
d0014c58:	00039d5c 	andeq	r9, r3, ip, asr sp

Disassembly of section .text.load_constant:

d0014c5c <.text.load_constant>:
d0014c5c:	e92d2aff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r9, fp, sp}
d0014c60:	460541f0 			; <UNDEFINED> instruction: 0x460541f0
d0014c64:	4614460e 	ldrmi	r4, [r4], -lr, lsl #12
d0014c68:	2907d80a 	stmdbcs	r7, {r1, r3, fp, ip, lr, pc}
d0014c6c:	ea42d808 	b	0xd10cac94
d0014c70:	f4412101 	vst4.8	{d18,d20,d22,d24}, [r1], r1
d0014c74:	e8bd5100 	pop	{r8, ip, lr}
d0014c78:	b28941f0 	addlt	r4, r9, #240, 2	; 0x3c
d0014c7c:	bfd0f7ff 	svclt	0x00d0f7ff
d0014c80:	4398f24f 	orrsmi	pc, r8, #-268435452	; 0xf0000004
d0014c84:	46282100 	strtmi	r2, [r8], -r0, lsl #2
d0014c88:	f7ff58ef 			; <UNDEFINED> instruction: 0xf7ff58ef
d0014c8c:	2100ffc9 	smlabtcs	r0, r9, pc, pc	; <UNPREDICTABLE>
d0014c90:	ffc6f7ff 			; <UNDEFINED> instruction: 0xffc6f7ff
d0014c94:	3f80f5b4 	svccc	0x0080f5b4
d0014c98:	2100d305 	tstcs	r0, r5, lsl #6
d0014c9c:	ffc0f7ff 			; <UNDEFINED> instruction: 0xffc0f7ff
d0014ca0:	f7ff2100 			; <UNDEFINED> instruction: 0xf7ff2100
d0014ca4:	6dabffbd 	stcvs	15, cr15, [fp, #756]!	; 0x2f4
d0014ca8:	b2a3b9a3 	adclt	fp, r3, #2670592	; 0x28c000
d0014cac:	f24f4632 	vmin.s8	d20, d15, d18
d0014cb0:	46382140 	ldrtmi	r2, [r8], -r0, asr #2
d0014cb4:	ff84f7ff 			; <UNDEFINED> instruction: 0xff84f7ff
d0014cb8:	3f80f5b4 	svccc	0x0080f5b4
d0014cbc:	6dabd30a 	stcvs	3, cr13, [fp, #40]!	; 0x28
d0014cc0:	0c23b943 			; <UNDEFINED> instruction: 0x0c23b943
d0014cc4:	1d384632 	ldcne	6, cr4, [r8, #-200]!	; 0xffffff38
d0014cc8:	21c0f24f 	biccs	pc, r0, pc, asr #4
d0014ccc:	41f0e8bd 	ldrhmi	lr, [r0, #141]!	; 0x8d
d0014cd0:	bf76f7ff 	svclt	0x0076f7ff
d0014cd4:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d

Disassembly of section .text.constant:

d0014cd8 <.text.constant>:
d0014cd8:	2100460a 	tstcs	r0, sl, lsl #12
d0014cdc:	bfbef7ff 	svclt	0x00bef7ff

Disassembly of section .text.null_argument:

d0014ce8 <.text.null_argument>:
d0014ce8:	f5a36ac3 			; <UNDEFINED> instruction: 0xf5a36ac3
d0014cec:	2a017281 	bcs	0xd00716f8
d0014cf0:	4604b570 			; <UNDEFINED> instruction: 0x4604b570
d0014cf4:	6a03d803 	bvs	0xd010ad08
d0014cf8:	2000b1eb 	andcs	fp, r0, fp, ror #3
d0014cfc:	f240bd70 	vmla.f32	<illegal reg q13.5>, q0, q8
d0014d00:	42931201 	addsmi	r1, r3, #268435456	; 0x10000000
d0014d04:	4a10d1f9 	bmi	0xd04494f0
d0014d08:	5606e9d0 			; <UNDEFINED> instruction: 0x5606e9d0
d0014d0c:	4631447a 			; <UNDEFINED> instruction: 0x4631447a
d0014d10:	f7fb4628 			; <UNDEFINED> instruction: 0xf7fb4628
d0014d14:	2800fda6 	stmdacs	r0, {r1, r2, r5, r7, r8, sl, fp, ip, sp, lr, pc}
d0014d18:	4632d0ef 	ldrtmi	sp, [r2], -pc, ror #1
d0014d1c:	46204629 	strtmi	r4, [r0], -r9, lsr #12
d0014d20:	fcf0f7fb 	ldc2l	7, cr15, [r0], #1004	; 0x3ec
d0014d24:	dae82800 	ble	0xcfa1ed2c
d0014d28:	46294632 			; <UNDEFINED> instruction: 0x46294632
d0014d2c:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0014d30:	2800fd08 	stmdacs	r0, {r3, r8, sl, fp, ip, sp, lr, pc}
d0014d34:	4620dae1 	strtmi	sp, [r0], -r1, ror #21
d0014d38:	f85cf7fe 			; <UNDEFINED> instruction: 0xf85cf7fe
d0014d3c:	21004620 	tstcs	r0, r0, lsr #12
d0014d40:	ffcaf7ff 			; <UNDEFINED> instruction: 0xffcaf7ff
d0014d44:	e7d92001 	ldrb	r2, [r9, r1]
d0014d48:	ffffffd0 			; <UNDEFINED> instruction: 0xffffffd0

Disassembly of section .text.load_local:

d0014d4c <.text.load_local>:
d0014d4c:	b570291f 	ldrblt	r2, [r0, #-2335]!	; 0xfffff6e1
d0014d50:	b28db294 	addlt	fp, sp, #148, 4	; 0x40000009
d0014d54:	ea44d80a 	b	0xd114ad84
d0014d58:	f4411185 	vst4.32	{d17,d19,d21,d23}, [r1], r5
d0014d5c:	f04141d0 			; <UNDEFINED> instruction: 0xf04141d0
d0014d60:	b2890138 	addlt	r0, r9, #56, 2
d0014d64:	4070e8bd 	ldrhtmi	lr, [r0], #-141	; 0xffffff73
d0014d68:	bf5af7ff 	svclt	0x005af7ff
d0014d6c:	01d7f64f 	bicseq	pc, r7, pc, asr #12
d0014d70:	ff56f7ff 			; <UNDEFINED> instruction: 0xff56f7ff
d0014d74:	ea4100a9 	b	0xd1055020
d0014d78:	b2893104 	addlt	r3, r9, #4, 2
d0014d7c:	Address 0x00000000d0014d7c is out of bounds.


Disassembly of section .text.store_local:

d0014d7e <.text.store_local>:
d0014d7e:	b570291f 	ldrblt	r2, [r0, #-2335]!	; 0xfffff6e1
d0014d82:	b28db294 	addlt	fp, sp, #148, 4	; 0x40000009
d0014d86:	ea44d80a 	b	0xd114adb6
d0014d8a:	f4411185 	vst4.32	{d17,d19,d21,d23}, [r1], r5
d0014d8e:	f04141c0 			; <UNDEFINED> instruction: 0xf04141c0
d0014d92:	b2890138 	addlt	r0, r9, #56, 2
d0014d96:	4070e8bd 	ldrhtmi	lr, [r0], #-141	; 0xffffff73
d0014d9a:	bf41f7ff 	svclt	0x0041f7ff
d0014d9e:	01c7f64f 	biceq	pc, r7, pc, asr #12
d0014da2:	ff3df7ff 			; <UNDEFINED> instruction: 0xff3df7ff
d0014da6:	ea4100a9 	b	0xd1055052
d0014daa:	b2893104 	addlt	r3, r9, #4, 2
d0014dae:	Address 0x00000000d0014dae is out of bounds.


Disassembly of section .text.local_address:

d0014db0 <.text.local_address>:
d0014db0:	4604b510 			; <UNDEFINED> instruction: 0x4604b510
d0014db4:	2100008a 	smlabbcs	r0, sl, r0, r0
d0014db8:	ff50f7ff 			; <UNDEFINED> instruction: 0xff50f7ff
d0014dbc:	f6414620 			; <UNDEFINED> instruction: 0xf6414620
d0014dc0:	e8bd0138 	pop	{r3, r4, r5, r8}
d0014dc4:	f7ff4010 			; <UNDEFINED> instruction: 0xf7ff4010
d0014dc8:	Address 0x00000000d0014dc8 is out of bounds.


Disassembly of section .text.int_double_pointer_value:

d0014e3c <.text.int_double_pointer_value>:
d0014e3c:	4ff8e92d 	svcmi	0x00f8e92d
d0014e40:	f7ff4604 			; <UNDEFINED> instruction: 0xf7ff4604
d0014e44:	bb28ff51 	bllt	0xd0a54b90
d0014e48:	46202126 	strtmi	r2, [r0], -r6, lsr #2
d0014e4c:	ffedf7fd 			; <UNDEFINED> instruction: 0xffedf7fd
d0014e50:	46054a20 	strmi	r4, [r5], -r0, lsr #20
d0014e54:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d0014e58:	4620447a 			; <UNDEFINED> instruction: 0x4620447a
d0014e5c:	9024f8d4 	ldrdls	pc, [r4], -r4	; <UNPREDICTABLE>
d0014e60:	8028f8d4 	ldrdhi	pc, [r8], -r4	; <UNPREDICTABLE>
d0014e64:	7030f894 	mlasvc	r0, r4, r8, pc	; <UNPREDICTABLE>
d0014e68:	e9d46b66 	ldmib	r4, {r1, r2, r5, r6, r8, r9, fp, sp, lr}^
d0014e6c:	f7fdab06 			; <UNDEFINED> instruction: 0xf7fdab06
d0014e70:	b178ffea 	cmnlt	r8, sl, ror #31	; <UNPREDICTABLE>
d0014e74:	465a4651 			; <UNDEFINED> instruction: 0x465a4651
d0014e78:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0014e7c:	1e01fc43 	cdpne	12, 0, cr15, cr1, cr3, {2}
d0014e80:	6da3da0a 			; <UNDEFINED> instruction: 0x6da3da0a
d0014e84:	4b14b933 	blmi	0xd0543358
d0014e88:	66a6447b 	sxtabvs	r4, r6, fp, ror #8
d0014e8c:	3916e9c4 	ldmdbcc	r6, {r2, r6, r7, r8, fp, sp, lr, pc}
d0014e90:	8718e9c4 	ldrhi	lr, [r8, -r4, asr #19]
d0014e94:	8ff8e8bd 	svchi	0x00f8e8bd
d0014e98:	fb032330 	blx	0xd00ddb62
d0014e9c:	f5034301 			; <UNDEFINED> instruction: 0xf5034301
d0014ea0:	f8933322 			; <UNDEFINED> instruction: 0xf8933322
d0014ea4:	b1353135 	teqlt	r5, r5, lsr r1
d0014ea8:	d10c2b0a 	tstle	ip, sl, lsl #22
d0014eac:	e8bd4620 	pop	{r5, r9, sl, lr}
d0014eb0:	f7ff4ff8 			; <UNDEFINED> instruction: 0xf7ff4ff8
d0014eb4:	2b13bf7d 	blcs	0xd0504cb0
d0014eb8:	462ad105 	strtmi	sp, [sl], -r5, lsl #2
d0014ebc:	e8bd4620 	pop	{r5, r9, sl, lr}
d0014ec0:	f7ff4ff8 			; <UNDEFINED> instruction: 0xf7ff4ff8
d0014ec4:	6da3bf43 	stcvs	15, cr11, [r3, #268]!	; 0x10c
d0014ec8:	d1e32b00 	mvnle	r2, r0, lsl #22
d0014ecc:	447b4b03 	ldrbtmi	r4, [fp], #-2819	; 0xfffff4fd
d0014ed0:	bf00e7db 	svclt	0x0000e7db
d0014ed4:	ffffff6e 			; <UNDEFINED> instruction: 0xffffff6e
d0014ed8:	ffffff5e 			; <UNDEFINED> instruction: 0xffffff5e
d0014edc:	ffffff36 			; <UNDEFINED> instruction: 0xffffff36

Disassembly of section .text.emit_address:

d0014f08 <.text.emit_address>:
d0014f08:	460db570 			; <UNDEFINED> instruction: 0x460db570
d0014f0c:	31baf500 			; <UNDEFINED> instruction: 0x31baf500
d0014f10:	f8d14604 			; <UNDEFINED> instruction: 0xf8d14604
d0014f14:	f5b330a0 			; <UNDEFINED> instruction: 0xf5b330a0
d0014f18:	d1056f00 	tstle	r5, r0, lsl #30
d0014f1c:	e8bd4916 	pop	{r1, r2, r4, r8, fp, lr}
d0014f20:	44794070 	ldrbtmi	r4, [r9], #-112	; 0xffffff90
d0014f24:	b940f7fb 	stmdblt	r0, {r0, r1, r3, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}^
d0014f28:	eb041c58 	bl	0xd011c090
d0014f2c:	260403c3 	strcs	r0, [r4], -r3, asr #7
d0014f30:	00a0f8c1 	adceq	pc, r0, r1, asr #17
d0014f34:	4198f24f 	orrsmi	pc, r8, pc, asr #4
d0014f38:	339af503 	orrscc	pc, sl, #12582912	; 0xc00000
d0014f3c:	f8a35861 			; <UNDEFINED> instruction: 0xf8a35861
d0014f40:	f8c320a4 			; <UNDEFINED> instruction: 0xf8c320a4
d0014f44:	f88310a0 			; <UNDEFINED> instruction: 0xf88310a0
d0014f48:	210050a6 	smlatbcs	r0, r6, r0, r5
d0014f4c:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0014f50:	3e01fe67 	cdpcc	14, 0, cr15, cr1, cr7, {3}
d0014f54:	f44fd1f9 	vst4.<illegal width 64>	{d29,d31,d33,d35}, [pc :256], r9
d0014f58:	f7ff4122 			; <UNDEFINED> instruction: 0xf7ff4122
d0014f5c:	2d01fe61 	stccs	14, cr15, [r1, #-388]	; 0xfffffe7c
d0014f60:	2141bf0c 	cmpcs	r1, ip, lsl #30
d0014f64:	f4412100 	vst4.8	{d18,d20,d22,d24}, [r1], r0
d0014f68:	e8bd51c0 	pop	{r6, r7, r8, ip, lr}
d0014f6c:	f0414070 			; <UNDEFINED> instruction: 0xf0414070
d0014f70:	f7ff0110 			; <UNDEFINED> instruction: 0xf7ff0110
d0014f74:	bf00be55 	svclt	0x0000be55
d0014f78:	ffffffba 			; <UNDEFINED> instruction: 0xffffffba

Disassembly of section .text.function_pointer_value.constprop.0:

d0015010 <.text.function_pointer_value.constprop.0>:
d0015010:	4ff7e92d 	svcmi	0x00f7e92d
d0015014:	46054c4a 	strmi	r4, [r5], -sl, asr #24
d0015018:	4620447c 			; <UNDEFINED> instruction: 0x4620447c
d001501c:	fe64f7ff 	mcr2	7, 3, pc, cr4, cr15, {7}	; <UNPREDICTABLE>
d0015020:	2126bb98 			; <UNDEFINED> instruction: 0x2126bb98
d0015024:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0015028:	4a46ff00 	bmi	0xd11d4c30
d001502c:	f2406b63 	vqdmulh.s<illegal width 8>	q11, q0, <illegal reg q9.5>
d0015030:	447a1101 	ldrbtmi	r1, [sl], #-257	; 0xfffffeff
d0015034:	f8d44620 			; <UNDEFINED> instruction: 0xf8d44620
d0015038:	f8d49024 			; <UNDEFINED> instruction: 0xf8d49024
d001503c:	f8948028 			; <UNDEFINED> instruction: 0xf8948028
d0015040:	93017030 	movwls	r7, #4144	; 0x1030
d0015044:	b606e9d4 			; <UNDEFINED> instruction: 0xb606e9d4
d0015048:	fefdf7fd 	mrc2	7, 7, pc, cr13, cr13, {7}
d001504c:	4632b1e8 	ldrtmi	fp, [r2], -r8, ror #3
d0015050:	46204659 			; <UNDEFINED> instruction: 0x46204659
d0015054:	fb56f7fb 	blx	0xd15d304a
d0015058:	0a00f1b0 	beq	0xd0051720
d001505c:	2030db34 	eorscs	sp, r0, r4, lsr fp
d0015060:	f00afb00 			; <UNDEFINED> instruction: 0xf00afb00
d0015064:	f5031823 			; <UNDEFINED> instruction: 0xf5031823
d0015068:	f8933322 			; <UNDEFINED> instruction: 0xf8933322
d001506c:	2a0c2135 	bcs	0xd031d548
d0015070:	4b35d00e 	blmi	0xd0d890b0
d0015074:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d0015078:	4a34b93a 	bmi	0xd0d43568
d001507c:	e9c3447a 	stmib	r3, {r1, r3, r4, r5, r6, sl, lr}^
d0015080:	9a012916 	bls	0xd005f4e0
d0015084:	8718e9c3 	ldrhi	lr, [r8, -r3, asr #19]
d0015088:	b003669a 	mullt	r3, sl, r6
d001508c:	8ff0e8bd 	svchi	0x00f0e8bd
d0015090:	f8937829 			; <UNDEFINED> instruction: 0xf8937829
d0015094:	428a2137 	addmi	r2, sl, #-1073741811	; 0xc000000d
d0015098:	f893d1eb 			; <UNDEFINED> instruction: 0xf893d1eb
d001509c:	786b1138 	stmdavc	fp!, {r3, r4, r5, r8, ip}^
d00150a0:	d1e64299 			; <UNDEFINED> instruction: 0xd1e64299
d00150a4:	3022f500 	eorcc	pc, r2, r0, lsl #10
d00150a8:	f2001ca9 			; <UNDEFINED> instruction: 0xf2001ca9
d00150ac:	44201039 	strtmi	r1, [r0], #-57	; 0xffffffc7
d00150b0:	f9b6f00a 			; <UNDEFINED> instruction: 0xf9b6f00a
d00150b4:	28004602 	stmdacs	r0, {r1, r9, sl, lr}
d00150b8:	4651d1db 			; <UNDEFINED> instruction: 0x4651d1db
d00150bc:	b0034620 	andlt	r4, r3, r0, lsr #12
d00150c0:	4ff0e8bd 	svcmi	0x00f0e8bd
d00150c4:	be42f7ff 	mcrlt	7, 2, pc, cr2, cr15, {7}	; <UNPREDICTABLE>
d00150c8:	46594632 			; <UNDEFINED> instruction: 0x46594632
d00150cc:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d00150d0:	f1b0fb9f 			; <UNDEFINED> instruction: 0xf1b0fb9f
d00150d4:	db2a0a00 	blle	0xd0a978dc
d00150d8:	46594632 			; <UNDEFINED> instruction: 0x46594632
d00150dc:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d00150e0:	2800fb30 	stmdacs	r0, {r4, r5, r8, r9, fp, ip, sp, lr, pc}
d00150e4:	2338da23 	teqcs	r8, #143360	; 0x23000
d00150e8:	f30afb03 	vqrdmulh.s<illegal width 8>	d15, d10, d3
d00150ec:	f50118e1 			; <UNDEFINED> instruction: 0xf50118e1
d00150f0:	f8913100 			; <UNDEFINED> instruction: 0xf8913100
d00150f4:	b9d22129 	ldmiblt	r2, {r0, r3, r5, r8, sp}^
d00150f8:	f8917828 			; <UNDEFINED> instruction: 0xf8917828
d00150fc:	42822128 	addmi	r2, r2, #40, 2
d0015100:	f891d115 			; <UNDEFINED> instruction: 0xf891d115
d0015104:	7869012b 	stmdavc	r9!, {r0, r1, r3, r5, r8}^
d0015108:	d1104288 	tstle	r0, r8, lsl #5
d001510c:	3300f503 	movwcc	pc, #1283	; 0x503	; <UNPREDICTABLE>
d0015110:	f2031ca9 			; <UNDEFINED> instruction: 0xf2031ca9
d0015114:	18e0132f 	stmiane	r0!, {r0, r1, r2, r3, r5, r8, r9, ip}^
d0015118:	f982f00a 			; <UNDEFINED> instruction: 0xf982f00a
d001511c:	4652b938 			; <UNDEFINED> instruction: 0x4652b938
d0015120:	46202102 	strtmi	r2, [r0], -r2, lsl #2
d0015124:	e8bdb003 	pop	{r0, r1, ip, sp, pc}
d0015128:	f7ff4ff0 			; <UNDEFINED> instruction: 0xf7ff4ff0
d001512c:	4b08beed 	blmi	0xd0244ce8
d0015130:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d0015134:	d1a82a00 			; <UNDEFINED> instruction: 0xd1a82a00
d0015138:	447a4a06 	ldrbtmi	r4, [sl], #-2566	; 0xfffff5fa
d001513c:	bf00e79f 	svclt	0x0000e79f
d0015140:	0000e404 	andeq	lr, r0, r4, lsl #8
d0015144:	ffffff46 			; <UNDEFINED> instruction: 0xffffff46
d0015148:	0000e3a8 	andeq	lr, r0, r8, lsr #7
d001514c:	ffffff34 			; <UNDEFINED> instruction: 0xffffff34
d0015150:	0000e2ec 	andeq	lr, r0, ip, ror #5
d0015154:	fffffe9e 			; <UNDEFINED> instruction: 0xfffffe9e

Disassembly of section .text.local_callback_declaration.constprop.0:

d00152fc <.text.local_callback_declaration.constprop.0>:
d00152fc:	47f0e92d 	ldrbmi	lr, [r0, sp, lsr #18]!
d0015300:	b0904e61 	addslt	r4, r0, r1, ror #28
d0015304:	46804a61 	strmi	r4, [r0], r1, ror #20
d0015308:	2128447e 			; <UNDEFINED> instruction: 0x2128447e
d001530c:	4630447a 			; <UNDEFINED> instruction: 0x4630447a
d0015310:	fd99f7fd 	ldc2	7, cr15, [r9, #1012]	; 0x3f4
d0015314:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d0015318:	4a5d80b3 	bmi	0xd17755ec
d001531c:	4630212a 	ldrtmi	r2, [r0], -sl, lsr #2
d0015320:	f7fd447a 			; <UNDEFINED> instruction: 0xf7fd447a
d0015324:	2800fd90 	stmdacs	r0, {r4, r7, r8, sl, fp, ip, sp, lr, pc}
d0015328:	80aaf000 	adchi	pc, sl, r0
d001532c:	0518f106 	ldreq	pc, [r8, #-262]	; 0xfffffefa
d0015330:	f10dac08 			; <UNDEFINED> instruction: 0xf10dac08
d0015334:	cd0f0920 	vstrgt.16	s0, [pc, #-64]	; 0xd00152fc	; <UNPREDICTABLE>
d0015338:	e895c40f 	ldm	r5, {r0, r1, r2, r3, sl, lr, pc}
d001533c:	e884000f 	stm	r4, {r0, r1, r2, r3}
d0015340:	4a54000f 	bmi	0xd1515384
d0015344:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d0015348:	447a4630 	ldrbtmi	r4, [sl], #-1584	; 0xfffff9d0
d001534c:	fd7bf7fd 	ldc2l	7, cr15, [fp, #-1012]!	; 0xfffffc0c
d0015350:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d0015354:	4a508095 	bmi	0xd14355b0
d0015358:	46302129 	ldrtmi	r2, [r0], -r9, lsr #2
d001535c:	f7fd447a 			; <UNDEFINED> instruction: 0xf7fd447a
d0015360:	2800fd72 	stmdacs	r0, {r1, r4, r5, r6, r8, sl, fp, ip, sp, lr, pc}
d0015364:	808cf000 	addhi	pc, ip, r0
d0015368:	21284a4c 			; <UNDEFINED> instruction: 0x21284a4c
d001536c:	447a4630 	ldrbtmi	r4, [sl], #-1584	; 0xfffff9d0
d0015370:	fd69f7fd 	stc2l	7, cr15, [r9, #-1012]!	; 0xfffffc0c
d0015374:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d0015378:	6af38083 	bvs	0xcfcf558c
d001537c:	af062400 	svcge	0x00062400
d0015380:	7f84f5b3 	svcvc	0x0084f5b3
d0015384:	80bc9406 	adcshi	r9, ip, r6, lsl #8
d0015388:	d14a71bc 	strhle	r7, [sl, #-28]	; 0xffffffe4
d001538c:	2b296cf3 	blcs	0xd0a70760
d0015390:	4630d149 	ldrtmi	sp, [r0], -r9, asr #2
d0015394:	fd2ef7fd 	stc2	7, cr15, [lr, #-1012]!	; 0xfffffc0c
d0015398:	21294d41 			; <UNDEFINED> instruction: 0x21294d41
d001539c:	447d4a41 	ldrbtmi	r4, [sp], #-2625	; 0xfffff5bf
d00153a0:	4628447a 			; <UNDEFINED> instruction: 0x4628447a
d00153a4:	fd4ff7fd 	stc2l	7, cr15, [pc, #-1012]	; 0xd0014fb8
d00153a8:	d0692800 	rsble	r2, r9, r0, lsl #16
d00153ac:	9304230c 	movwls	r2, #17164	; 0x430c
d00153b0:	e913ab10 	ldmdb	r3, {r4, r8, r9, fp, sp, pc}
d00153b4:	e88d000f 	stm	sp, {r0, r1, r2, r3}
d00153b8:	e899000f 	ldm	r9, {r0, r1, r2, r3}
d00153bc:	f7fe000f 			; <UNDEFINED> instruction: 0xf7fe000f
d00153c0:	6dabfe01 	stcvs	14, cr15, [fp, #4]!
d00153c4:	2b004606 	blcs	0xd0026be4
d00153c8:	2330d15a 	teqcs	r0, #-2147483626	; 0x80000016
d00153cc:	4018f88d 	andsmi	pc, r8, sp, lsl #17
d00153d0:	46392207 	ldrtmi	r2, [r9], -r7, lsl #4
d00153d4:	f400fb03 			; <UNDEFINED> instruction: 0xf400fb03
d00153d8:	8019f88d 	andshi	pc, r9, sp, lsl #17
d00153dc:	f5001928 			; <UNDEFINED> instruction: 0xf5001928
d00153e0:	f2003022 	vhadd.s8	d3, d0, d18
d00153e4:	f00a1037 			; <UNDEFINED> instruction: 0xf00a1037
d00153e8:	213df80b 	teqcs	sp, fp, lsl #16	; <UNPREDICTABLE>
d00153ec:	f7fd4628 			; <UNDEFINED> instruction: 0xf7fd4628
d00153f0:	4601fd1c 			; <UNDEFINED> instruction: 0x4601fd1c
d00153f4:	d03f2800 	eorsle	r2, pc, r0, lsl #16
d00153f8:	3022f504 	eorcc	pc, r2, r4, lsl #10
d00153fc:	1037f200 	eorsne	pc, r7, r0, lsl #4
d0015400:	f7ff4428 			; <UNDEFINED> instruction: 0xf7ff4428
d0015404:	4828fe05 	stmdami	r8!, {r0, r2, r9, sl, fp, ip, sp, lr, pc}
d0015408:	22004631 	andcs	r4, r0, #51380224	; 0x3100000
d001540c:	f7ff4478 			; <UNDEFINED> instruction: 0xf7ff4478
d0015410:	4a26fcb6 	bmi	0xd09d46f0
d0015414:	447a213b 	ldrbtmi	r2, [sl], #-315	; 0xfffffec5
d0015418:	e8bdb010 	pop	{r4, ip, sp, pc}
d001541c:	f7fd47f0 			; <UNDEFINED> instruction: 0xf7fd47f0
d0015420:	2b29bd12 	blcs	0xd0a84870
d0015424:	f8dfd0b8 			; <UNDEFINED> instruction: 0xf8dfd0b8
d0015428:	f10da088 			; <UNDEFINED> instruction: 0xf10da088
d001542c:	4d21061a 	stcmi	6, cr0, [r1, #-104]!	; 0xffffff98
d0015430:	44fa2400 	ldrbtmi	r2, [sl], #1024	; 0x400
d0015434:	4652447d 			; <UNDEFINED> instruction: 0x4652447d
d0015438:	1107f240 	tstne	r7, r0, asr #4	; <UNPREDICTABLE>
d001543c:	f7fd4628 			; <UNDEFINED> instruction: 0xf7fd4628
d0015440:	b1e8fd02 	mvnlt	pc, r2, lsl #26
d0015444:	f2402300 	vcgt.s8	d18, d0, d0
d0015448:	34011101 	strcc	r1, [r1], #-257	; 0xfffffeff
d001544c:	f8064628 			; <UNDEFINED> instruction: 0xf8064628
d0015450:	f7fd3b01 			; <UNDEFINED> instruction: 0xf7fd3b01
d0015454:	212cfcea 	msrcs	CPSR_fs, sl, ror #25
d0015458:	b2e44628 	rsclt	r4, r4, #40, 12	; 0x2800000
d001545c:	fce5f7fd 	stc2l	7, cr15, [r5], #1012	; 0x3f4
d0015460:	d0992800 	addsle	r2, r9, r0, lsl #16
d0015464:	d1e62c05 	mvnle	r2, r5, lsl #24
d0015468:	46284913 			; <UNDEFINED> instruction: 0x46284913
d001546c:	b0104479 	andslt	r4, r0, r9, ror r4
d0015470:	47f0e8bd 			; <UNDEFINED> instruction: 0x47f0e8bd
d0015474:	be98f7fa 	mrclt	7, 4, APSR_nzcv, cr8, cr10, {7}
d0015478:	f7ff4628 			; <UNDEFINED> instruction: 0xf7ff4628
d001547c:	e7c2fc2d 	strb	pc, [r2, sp, lsr #24]	; <UNPREDICTABLE>
d0015480:	e8bdb010 	pop	{r4, ip, sp, pc}
d0015484:	bf0087f0 	svclt	0x000087f0
d0015488:	0000e114 	andeq	lr, r0, r4, lsl r1
d001548c:	fffffe48 			; <UNDEFINED> instruction: 0xfffffe48
d0015490:	fffffe61 			; <UNDEFINED> instruction: 0xfffffe61
d0015494:	fffffe64 			; <UNDEFINED> instruction: 0xfffffe64
d0015498:	fffffe7a 			; <UNDEFINED> instruction: 0xfffffe7a
d001549c:	fffffe95 			; <UNDEFINED> instruction: 0xfffffe95
d00154a0:	0000e07e 	andeq	lr, r0, lr, ror r0
d00154a4:	fffffef6 			; <UNDEFINED> instruction: 0xfffffef6
d00154a8:	0000e010 	andeq	lr, r0, r0, lsl r0
d00154ac:	fffffeaf 			; <UNDEFINED> instruction: 0xfffffeaf
d00154b0:	fffffe35 			; <UNDEFINED> instruction: 0xfffffe35
d00154b4:	0000dfe8 	andeq	sp, r0, r8, ror #31
d00154b8:	fffffdcc 			; <UNDEFINED> instruction: 0xfffffdcc

Disassembly of section .text.branch:

d00154bc <.text.branch>:
d00154bc:	f24fb538 	vqrshl.s8	d27, d24, d15
d00154c0:	21004398 			; <UNDEFINED> instruction: 0x21004398
d00154c4:	f7ff58c5 			; <UNDEFINED> instruction: 0xf7ff58c5
d00154c8:	2100fbab 	smlatbcs	r0, fp, fp, pc	; <UNPREDICTABLE>
d00154cc:	fba8f7ff 	blx	0xcea534d2
d00154d0:	bd384628 	ldclt	6, cr4, [r8, #-160]!	; 0xffffff60

Disassembly of section .text.branch_on_value:

d00154d4 <.text.branch_on_value>:
d00154d4:	460db538 			; <UNDEFINED> instruction: 0x460db538
d00154d8:	5120f44f 	msrpl	CPSR_, pc, asr #8
d00154dc:	fba0f7ff 	blx	0xce8534e2
d00154e0:	1301f24d 	movwne	pc, #4685	; 0x124d	; <UNPREDICTABLE>
d00154e4:	0101f24d 	tsteq	r1, sp, asr #4	; <UNPREDICTABLE>
d00154e8:	bf082d00 	svclt	0x00082d00
d00154ec:	f7ff4619 			; <UNDEFINED> instruction: 0xf7ff4619
d00154f0:	e8bdfb97 	pop	{r0, r1, r2, r4, r7, r8, r9, fp, ip, sp, lr, pc}
d00154f4:	f7ff4038 			; <UNDEFINED> instruction: 0xf7ff4038
d00154f8:	Address 0x00000000d00154f8 is out of bounds.


Disassembly of section .text.boolean:

d00154fa <.text.boolean>:
d00154fa:	0301f24d 	movweq	pc, #4685	; 0x124d	; <UNPREDICTABLE>
d00154fe:	2101ea43 	tstcs	r1, r3, asr #20
d0015502:	b289b510 	addlt	fp, r9, #16, 10	; 0x4000000
d0015506:	fb8bf7ff 	blx	0xce31350c
d001550a:	5100f44f 	tstpl	r0, pc, asr #8	; <UNPREDICTABLE>
d001550e:	fb87f7ff 	blx	0xce213514
d0015512:	4160f44f 	msrmi	SPSR_, pc, asr #8
d0015516:	fb83f7ff 	blx	0xce11351c
d001551a:	0101f242 	tsteq	r1, r2, asr #4	; <UNPREDICTABLE>
d001551e:	4010e8bd 			; <UNDEFINED> instruction: 0x4010e8bd
d0015522:	bb7df7ff 	bllt	0xd1f93526

Disassembly of section .text.prepare_call:

d0015526 <.text.prepare_call>:
d0015526:	e92d2904 	push	{r2, r8, fp, sp}
d001552a:	460d43f8 			; <UNDEFINED> instruction: 0x460d43f8
d001552e:	2504bf38 	strcs	fp, [r4, #-3896]	; 0xfffff0c8
d0015532:	460c4607 	strmi	r4, [ip], -r7, lsl #12
d0015536:	f0353d03 			; <UNDEFINED> instruction: 0xf0353d03
d001553a:	d0060501 	andle	r0, r6, r1, lsl #10
d001553e:	4130f445 	teqmi	r0, r5, asr #8	; <UNPREDICTABLE>
d0015542:	0180f041 	orreq	pc, r0, r1, asr #32
d0015546:	f7ffb289 			; <UNDEFINED> instruction: 0xf7ffb289
d001554a:	1f66fb6a 	svcne	0x0066fb6a
d001554e:	0904f04f 	stmdbeq	r4, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d0015552:	0846ea4f 	stmdaeq	r6, {r0, r1, r2, r3, r6, r9, fp, sp, lr, pc}^
d0015556:	0646eb05 	strbeq	lr, [r6], -r5, lsl #22
d001555a:	45a1b2b6 	strmi	fp, [r1, #694]!	; 0x2b6
d001555e:	f108d30c 			; <UNDEFINED> instruction: 0xf108d30c
d0015562:	f04f0608 			; <UNDEFINED> instruction: 0xf04f0608
d0015566:	442e0800 	strtmi	r0, [lr], #-2048	; 0xfffff800
d001556a:	45a0b2b6 	strmi	fp, [r0, #694]!	; 0x2b6
d001556e:	f1b8d026 			; <UNDEFINED> instruction: 0xf1b8d026
d0015572:	d1120f04 	tstle	r2, r4, lsl #30
d0015576:	e029bb1d 	eor	fp, r9, sp, lsl fp
d001557a:	4118f446 	tstmi	r8, r6, asr #8	; <UNPREDICTABLE>
d001557e:	f7ff4638 			; <UNDEFINED> instruction: 0xf7ff4638
d0015582:	f1a9fb4e 			; <UNDEFINED> instruction: 0xf1a9fb4e
d0015586:	3e020104 	adfccs	f0, f2, f4
d001558a:	0901f109 	stmdbeq	r1, {r0, r3, r8, ip, sp, lr, pc}
d001558e:	4110f441 	tstmi	r0, r1, asr #8	; <UNPREDICTABLE>
d0015592:	b289b2b6 	addlt	fp, r9, #1610612747	; 0x6000000b
d0015596:	fb43f7ff 	blx	0xd111359c
d001559a:	fa1fe7df 	blx	0xd080f51e
d001559e:	4638f388 	ldrtmi	pc, [r8], -r8, lsl #7	; <UNPREDICTABLE>
d00155a2:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d00155a6:	31c3ebc3 	biccc	lr, r3, r3, asr #23
d00155aa:	0141eb06 	cmpeq	r1, r6, lsl #22
d00155ae:	2103ea41 	tstcs	r3, r1, asr #20
d00155b2:	4118f441 	tstmi	r8, r1, asr #8	; <UNPREDICTABLE>
d00155b6:	f7ffb289 			; <UNDEFINED> instruction: 0xf7ffb289
d00155ba:	e7d6fb32 			; <UNDEFINED> instruction: 0xe7d6fb32
d00155be:	eb05b125 	bl	0xd0181a5a
d00155c2:	46200444 	strtmi	r0, [r0], -r4, asr #8
d00155c6:	83f8e8bd 	mvnshi	lr, #12386304	; 0xbd0000
d00155ca:	d0fa2c00 	rscsle	r2, sl, r0, lsl #24
d00155ce:	46380061 	ldrtmi	r0, [r8], -r1, rrx
d00155d2:	f4412400 	vst3.8	{d18-d20}, [r1], r0
d00155d6:	b2894130 	addlt	r4, r9, #48, 2
d00155da:	fb21f7ff 	blx	0xd08935e0
d00155de:	Address 0x00000000d00155de is out of bounds.


Disassembly of section .text.binary:

d00155e0 <.text.binary>:
d00155e0:	b570292f 	ldrblt	r2, [r0, #-2351]!	; 0xfffff6d1
d00155e4:	460e4604 	strmi	r4, [lr], -r4, lsl #12
d00155e8:	dc0d4615 	stcle	6, cr4, [sp], {21}
d00155ec:	dd102924 	vldrle.16	s4, [r0, #-72]	; 0xffffffb8	; <UNPREDICTABLE>
d00155f0:	0325f1a1 	msreq	CPSR_sc, #1073741864	; 0x40000028
d00155f4:	d80c2b0a 	stmdale	ip, {r1, r3, r8, r9, fp, sp}
d00155f8:	f003e8df 			; <UNDEFINED> instruction: 0xf003e8df
d00155fc:	0b0b3f57 	bleq	0xd02e5360
d0015600:	0b353c0b 	bleq	0xd0d64634
d0015604:	004b0b68 	subeq	r0, fp, r8, ror #22
d0015608:	d039297c 	eorsle	r2, r9, ip, ror r9
d001560c:	295edc12 	ldmdbcs	lr, {r1, r4, sl, fp, ip, lr, pc}^
d0015610:	f244d039 	vqadd.s8	d29, d4, d25
d0015614:	46202181 	strtmi	r2, [r0], -r1, lsl #3
d0015618:	fb02f7ff 	blx	0xd00d361e
d001561c:	7f90f5b6 	svcvc	0x0090f5b6
d0015620:	f5b6da06 			; <UNDEFINED> instruction: 0xf5b6da06
d0015624:	da547f8e 	ble	0xd1535464
d0015628:	d0672e3c 	rsble	r2, r7, ip, lsr lr
d001562c:	d06a2e3e 	rsble	r2, sl, lr, lsr lr
d0015630:	e01d2500 	ands	r2, sp, r0, lsl #10
d0015634:	7293f46f 	addsvc	pc, r3, #1862270976	; 0x6f000000
d0015638:	2b01188b 	blcs	0xd005b86c
d001563c:	f244d8e9 	vadd.i8	<illegal reg q14.5>, q10, <illegal reg q12.5>
d0015640:	f7ff6102 			; <UNDEFINED> instruction: 0xf7ff6102
d0015644:	f244faed 	vpmax.s8	<illegal reg q15.5>, q10, <illegal reg q14.5>
d0015648:	f7ff6108 			; <UNDEFINED> instruction: 0xf7ff6108
d001564c:	f240fae9 	vpmax.s8	<illegal reg q15.5>, q8, <illegal reg q12.5>
d0015650:	429e1327 	addsmi	r1, lr, #-1677721600	; 0x9c000000
d0015654:	f244d01a 	vqadd.s8	d29, d4, d10
d0015658:	f24401d0 	vand	q8, q10, q0
d001565c:	2d001310 	stccs	3, cr1, [r0, #-64]	; 0xffffffc0
d0015660:	4619bf08 	ldrmi	fp, [r9], -r8, lsl #30
d0015664:	f641e001 			; <UNDEFINED> instruction: 0xf641e001
d0015668:	46200108 	strtmi	r0, [r0], -r8, lsl #2
d001566c:	fad8f7ff 	blx	0xcf653670
d0015670:	bd704628 	ldcllt	6, cr4, [r0, #-160]!	; 0xffffff60
d0015674:	3148f244 	cmpcc	r8, r4, asr #4	; <UNPREDICTABLE>
d0015678:	f244e7f7 	vaba.s8	q15, q10, <illegal reg q11.5>
d001567c:	e7f40108 	ldrb	r0, [r4, r8, lsl #2]!
d0015680:	3108f244 	tstcc	r8, r4, asr #4	; <UNPREDICTABLE>
d0015684:	f244e7f2 	vaba.s8	q15, q10, q9
d0015688:	e7ef0148 	strb	r0, [pc, r8, asr #2]!
d001568c:	0190f244 	orrseq	pc, r0, r4, asr #4
d0015690:	f64fe7eb 			; <UNDEFINED> instruction: 0xf64fe7eb
d0015694:	f64f3391 			; <UNDEFINED> instruction: 0xf64f3391
d0015698:	2d0031b1 	stfcss	f3, [r0, #-708]	; 0xfffffd3c
d001569c:	4619bf08 	ldrmi	fp, [r9], -r8, lsl #30
d00156a0:	fabef7ff 	blx	0xcefd36a4
d00156a4:	01f0f24f 	mvnseq	pc, pc, asr #4
d00156a8:	f64fe7df 			; <UNDEFINED> instruction: 0xf64fe7df
d00156ac:	f64f3391 			; <UNDEFINED> instruction: 0xf64f3391
d00156b0:	2d0031b1 	stfcss	f3, [r0, #-708]	; 0xfffffd3c
d00156b4:	4619bf08 	ldrmi	fp, [r9], -r8, lsl #30
d00156b8:	fab2f7ff 	blx	0xcecd36bc
d00156bc:	21f0f24f 	mvnscs	pc, pc, asr #4
d00156c0:	faaef7ff 	blx	0xcebd36c4
d00156c4:	3150f244 	cmpcc	r0, r4, asr #4	; <UNPREDICTABLE>
d00156c8:	faaaf7ff 	blx	0xcead36cc
d00156cc:	2108f641 	tstcs	r8, r1, asr #12	; <UNPREDICTABLE>
d00156d0:	f46fe7cb 	vld1.64	{d30}, [pc], fp
d00156d4:	441e738e 	ldrmi	r7, [lr], #-910	; 0xfffffc72
d00156d8:	d8032e02 	stmdale	r3, {r1, r9, sl, fp, sp}
d00156dc:	f006e8df 			; <UNDEFINED> instruction: 0xf006e8df
d00156e0:	00091807 	andeq	r1, r9, r7, lsl #16
d00156e4:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d00156e8:	ff07f7ff 			; <UNDEFINED> instruction: 0xff07f7ff
d00156ec:	2101e7a0 	smlatbcs	r1, r0, r7, lr
d00156f0:	2d00e7f9 	stccs	7, cr14, [r0, #-996]	; 0xfffffc1c
d00156f4:	2102bf14 	tstcs	r2, r4, lsl pc
d00156f8:	e7f4210a 	ldrb	r2, [r4, sl, lsl #2]!
d00156fc:	bf142d00 	svclt	0x00142d00
d0015700:	210b2103 	tstcs	fp, r3, lsl #2
d0015704:	2d00e7ef 	stccs	7, cr14, [r0, #-956]	; 0xfffffc44
d0015708:	2108bf14 	tstcs	r8, r4, lsl pc
d001570c:	e7ea210c 	strb	r2, [sl, ip, lsl #2]!
d0015710:	bf142d00 	svclt	0x00142d00
d0015714:	210d2109 	tstcs	sp, r9, lsl #2
d0015718:	Address 0x00000000d0015718 is out of bounds.


Disassembly of section .text.increment_scalar.isra.0:

d0015774 <.text.increment_scalar.isra.0>:
d0015774:	4ff8e92d 	svcmi	0x00f8e92d
d0015778:	a030f8dd 	ldrsbtge	pc, [r0], -sp	; <UNPREDICTABLE>
d001577c:	460d4604 	strmi	r4, [sp], -r4, lsl #12
d0015780:	46984617 			; <UNDEFINED> instruction: 0x46984617
d0015784:	902cf89d 	mlals	ip, sp, r8, pc	; <UNPREDICTABLE>
d0015788:	b038f8dd 	ldrsbtlt	pc, [r8], -sp	; <UNPREDICTABLE>
d001578c:	ffbaf7fa 			; <UNDEFINED> instruction: 0xffbaf7fa
d0015790:	da6e1e06 	ble	0xd1b9cfb0
d0015794:	4629463a 			; <UNDEFINED> instruction: 0x4629463a
d0015798:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d001579c:	1e07ffd2 	mcrne	15, 0, pc, cr7, cr2, {6}	; <UNPREDICTABLE>
d00157a0:	2338db19 	teqcs	r8, #25600	; 0x6400
d00157a4:	4307fb03 	movwmi	pc, #31491	; 0x7b03	; <UNPREDICTABLE>
d00157a8:	33baf503 			; <UNDEFINED> instruction: 0x33baf503
d00157ac:	50ccf893 	smullpl	pc, ip, r3, r8	; <UNPREDICTABLE>
d00157b0:	30d0f893 	smullscc	pc, r0, r3, r8	; <UNPREDICTABLE>
d00157b4:	d0692b00 	rsble	r2, r9, r0, lsl #22
d00157b8:	b1106da0 	tstlt	r0, r0, lsr #27
d00157bc:	e8bd2000 	ldmfd	sp!, {sp}
d00157c0:	4b3d8ff8 	blmi	0xd0f797a8
d00157c4:	f8c4447b 			; <UNDEFINED> instruction: 0xf8c4447b
d00157c8:	e9c4a068 	stmib	r4, {r3, r5, r6, sp, pc}^
d00157cc:	9b0a3816 	blls	0xd02a382c
d00157d0:	3918e9c4 	ldmdbcc	r8, {r2, r6, r7, r8, fp, sp, lr, pc}
d00157d4:	6da0e7f3 	stcvs	7, cr14, [r0, #972]!	; 0x3cc
d00157d8:	d1ef2800 	mvnle	r2, r0, lsl #16
d00157dc:	447b4b37 	ldrbtmi	r4, [fp], #-2871	; 0xfffff4c9
d00157e0:	2200e7f1 	andcs	lr, r0, #63176704	; 0x3c40000
d00157e4:	46204631 			; <UNDEFINED> instruction: 0x46204631
d00157e8:	fab0f7ff 	blx	0xcec537ec
d00157ec:	0f00f1bb 	svceq	0x0000f1bb
d00157f0:	f24bd004 	vhadd.s8	d29, d11, d4
d00157f4:	46204101 	strtmi	r4, [r0], -r1, lsl #2
d00157f8:	fa12f7ff 	blx	0xd04d37fc
d00157fc:	1323f240 	msrne	CPSR_xc, #64, 4
d0015800:	46209a0d 	strtmi	r9, [r0], -sp, lsl #20
d0015804:	bf07429a 	svclt	0x0007429a
d0015808:	0104f243 	tsteq	r4, r3, asr #4	; <UNPREDICTABLE>
d001580c:	0301f243 	movweq	pc, #4675	; 0x1243	; <UNPREDICTABLE>
d0015810:	0104f643 	tsteq	r4, r3, asr #12	; <UNPREDICTABLE>
d0015814:	0301f643 	movweq	pc, #5699	; 0x1643	; <UNPREDICTABLE>
d0015818:	bf182d0a 	svclt	0x00182d0a
d001581c:	f7ff4619 			; <UNDEFINED> instruction: 0xf7ff4619
d0015820:	2d05f9ff 	vstrcs.16	s30, [r5, #-510]	; 0xfffffe02	; <UNPREDICTABLE>
d0015824:	f24bd103 	vrhadd.s8	d29, d11, d3
d0015828:	f7ff21c0 			; <UNDEFINED> instruction: 0xf7ff21c0
d001582c:	2e00f9f9 			; <UNDEFINED> instruction: 0x2e00f9f9
d0015830:	2200db12 	andcs	sp, r0, #18432	; 0x4800
d0015834:	46204631 			; <UNDEFINED> instruction: 0x46204631
d0015838:	faa1f7ff 	blx	0xce89383c
d001583c:	0f00f1bb 	svceq	0x0000f1bb
d0015840:	f64bd004 			; <UNDEFINED> instruction: 0xf64bd004
d0015844:	46204101 	strtmi	r4, [r0], -r1, lsl #2
d0015848:	f9eaf7ff 			; <UNDEFINED> instruction: 0xf9eaf7ff
d001584c:	d00e2d0a 	andle	r2, lr, sl, lsl #26
d0015850:	42581e6b 	subsmi	r1, r8, #1712	; 0x6b0
d0015854:	e7b24158 	sbfx	r4, r8, #2, #19
d0015858:	463a4620 	ldrtmi	r4, [sl], -r0, lsr #12
d001585c:	f7ff2101 			; <UNDEFINED> instruction: 0xf7ff2101
d0015860:	f246fb53 	vpadd.i8	<illegal reg q15.5>, q3, <illegal reg q1.5>
d0015864:	46200108 	strtmi	r0, [r0], -r8, lsl #2
d0015868:	f9daf7ff 			; <UNDEFINED> instruction: 0xf9daf7ff
d001586c:	2004e7e6 	andcs	lr, r4, r6, ror #15
d0015870:	2330e7a5 	teqcs	r0, #43253760	; 0x2940000
d0015874:	4306fb03 	movwmi	pc, #27395	; 0x6b03	; <UNPREDICTABLE>
d0015878:	3322f503 	msrcc	CPSR_x, #12582912	; 0xc00000
d001587c:	2140f893 			; <UNDEFINED> instruction: 0x2140f893
d0015880:	d1992a00 	orrsle	r2, r9, r0, lsl #20
d0015884:	5135f893 	teqpl	r5, r3	; <illegal shifter operand>	; <UNPREDICTABLE>
d0015888:	37fff04f 	ldrbcc	pc, [pc, pc, asr #32]!	; <UNPREDICTABLE>
d001588c:	2a111eaa 	bcs	0xd045d33c
d0015890:	4b08d803 	blmi	0xd024b8a4
d0015894:	07da40d3 			; <UNDEFINED> instruction: 0x07da40d3
d0015898:	2e00d49d 	mcrcs	4, 0, sp, cr0, cr13, {4}
d001589c:	4620daa1 	strtmi	sp, [r0], -r1, lsr #21
d00158a0:	2101463a 	tstcs	r1, sl, lsr r6
d00158a4:	fb30f7ff 	blx	0xd0c538aa
d00158a8:	0108f646 	tsteq	r8, r6, asr #12	; <UNPREDICTABLE>
d00158ac:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d00158b0:	e79bf9b7 			; <UNDEFINED> instruction: 0xe79bf9b7
d00158b4:	0003fef5 	strdeq	pc, [r3], -r5
d00158b8:	ffffff52 			; <UNDEFINED> instruction: 0xffffff52
d00158bc:	ffffff65 			; <UNDEFINED> instruction: 0xffffff65

Disassembly of section .text.string_argument:

d0015910 <.text.string_argument>:
d0015910:	f2406ac3 	vpmax.s8	q11, q8, <illegal reg q1.5>
d0015914:	42931201 	addsmi	r1, r3, #268435456	; 0x10000000
d0015918:	43f0e92d 	mvnsmi	lr, #737280	; 0xb4000
d001591c:	b0894604 	addlt	r4, r9, r4, lsl #12
d0015920:	e9d0d12d 	ldmib	r0, {r0, r2, r3, r5, r8, ip, lr, pc}^
d0015924:	92051206 	andls	r1, r5, #1610612736	; 0x60000000
d0015928:	f7fa9104 			; <UNDEFINED> instruction: 0xf7fa9104
d001592c:	1e05ff0a 	cdpne	15, 0, cr15, cr5, cr10, {0}
d0015930:	9a059904 	bls	0xd017bd48
d0015934:	4942da05 	stmdbmi	r2, {r0, r2, r9, fp, ip, lr, pc}^
d0015938:	44794620 	ldrbtmi	r4, [r9], #-1568	; 0xfffff9e0
d001593c:	fc34f7fa 	ldc2	7, cr15, [r4], #-1000	; 0xfffffc18
d0015940:	4620e01a 			; <UNDEFINED> instruction: 0x4620e01a
d0015944:	fedef7fa 	mrc2	7, 6, pc, cr14, cr10, {7}
d0015948:	daf42800 	ble	0xcfd1f950
d001594c:	fb032338 	blx	0xd00de636
d0015950:	f5034305 			; <UNDEFINED> instruction: 0xf5034305
d0015954:	f89333ba 			; <UNDEFINED> instruction: 0xf89333ba
d0015958:	2b0730cc 	blcs	0xd01e1c90
d001595c:	4620d1eb 	strtmi	sp, [r0], -fp, ror #3
d0015960:	fa48f7fd 	blx	0xd125395c
d0015964:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d0015968:	f7ff462a 			; <UNDEFINED> instruction: 0xf7ff462a
d001596c:	f244facd 	vpmax.s8	<illegal reg q15.5>, q10, <illegal reg q6.5>
d0015970:	46206108 	strtmi	r6, [r0], -r8, lsl #2
d0015974:	f954f7ff 			; <UNDEFINED> instruction: 0xf954f7ff
d0015978:	e8bdb009 	pop	{r0, r3, ip, sp, pc}
d001597c:	f5b383f0 			; <UNDEFINED> instruction: 0xf5b383f0
d0015980:	d1d87f82 	bicsle	r7, r8, r2, lsl #31
d0015984:	459cf24f 	ldrmi	pc, [ip, #591]	; 0x24f
d0015988:	f5b75947 			; <UNDEFINED> instruction: 0xf5b75947
d001598c:	d0264f80 	eorle	r4, r6, r0, lsl #31
d0015990:	6a614405 	bvs	0xd18669ac
d0015994:	f8946aa2 			; <UNDEFINED> instruction: 0xf8946aa2
d0015998:	f8d48030 			; <UNDEFINED> instruction: 0xf8d48030
d001599c:	e9d49034 	ldmib	r4, {r2, r4, r5, ip, pc}^
d00159a0:	96076306 	strls	r6, [r7], -r6, lsl #6
d00159a4:	9807441e 	stmdals	r7, {r1, r2, r3, r4, sl, lr}
d00159a8:	d11b42b0 			; <UNDEFINED> instruction: 0xd11b42b0
d00159ac:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d00159b0:	6ae3fa21 	bvs	0xcf91423c
d00159b4:	7f82f5b3 	svcvc	0x0082f5b3
d00159b8:	6da3d102 	stfvsd	f5, [r3, #8]!
d00159bc:	d0e82b00 	rscle	r2, r8, r0, lsl #22
d00159c0:	429cf24f 	addsmi	pc, ip, #-268435452	; 0xf0000004
d00159c4:	58a34620 	stmiapl	r3!, {r5, r9, sl, lr}
d00159c8:	44231c59 	strtmi	r1, [r3], #-3161	; 0xfffff3a7
d00159cc:	210050a1 	smlatbcs	r0, r1, r0, r5
d00159d0:	42a0f24f 	adcmi	pc, r0, #-268435452	; 0xf0000004
d00159d4:	463a5499 			; <UNDEFINED> instruction: 0x463a5499
d00159d8:	fa96f7ff 	blx	0xce5d39dc
d00159dc:	4919e7cc 	ldmdbmi	r9, {r2, r3, r6, r7, r8, r9, sl, sp, lr, pc}
d00159e0:	e7ab4479 			; <UNDEFINED> instruction: 0xe7ab4479
d00159e4:	3301682b 	movwcc	r6, #6187	; 0x182b
d00159e8:	4f80f5b3 	svcmi	0x0080f5b3
d00159ec:	6da3d30b 	stcvs	3, cr13, [r3, #44]!	; 0x2c
d00159f0:	d1c12b00 	bicle	r2, r1, r0, lsl #22
d00159f4:	f8c44b14 			; <UNDEFINED> instruction: 0xf8c44b14
d00159f8:	447b9068 	ldrbtmi	r9, [fp], #-104	; 0xffffff98
d00159fc:	2818e9c4 	ldmdacs	r8, {r2, r6, r7, r8, fp, sp, lr, pc}
d0015a00:	3116e9c4 	tstcc	r6, r4, asr #19
d0015a04:	1c43e7b8 	mcrrne	7, 11, lr, r3, cr8
d0015a08:	78009307 	stmdavc	r0, {r0, r1, r2, r8, r9, ip, pc}
d0015a0c:	d108285c 	tstle	r8, ip, asr r8
d0015a10:	4620ab07 	strtmi	sl, [r0], -r7, lsl #22
d0015a14:	93019602 	movwls	r9, #5634	; 0x1602
d0015a18:	f8cd4643 			; <UNDEFINED> instruction: 0xf8cd4643
d0015a1c:	f7fa9000 			; <UNDEFINED> instruction: 0xf7fa9000
d0015a20:	6da3fd29 	stcvs	13, cr15, [r3, #164]!	; 0xa4
d0015a24:	d1a72b00 			; <UNDEFINED> instruction: 0xd1a72b00
d0015a28:	f103682b 			; <UNDEFINED> instruction: 0xf103682b
d0015a2c:	44230c01 	strtmi	r0, [r3], #-3073	; 0xfffff3ff
d0015a30:	c000f8c5 	andgt	pc, r0, r5, asr #17
d0015a34:	4ca0f24f 	sfmmi	f7, 1, [r0], #316	; 0x13c
d0015a38:	000cf803 	andeq	pc, ip, r3, lsl #16
d0015a3c:	bf00e7b3 	svclt	0x0000e7b3
d0015a40:	ffffff82 			; <UNDEFINED> instruction: 0xffffff82
d0015a44:	ffffff0e 			; <UNDEFINED> instruction: 0xffffff0e
d0015a48:	fffffef4 			; <UNDEFINED> instruction: 0xfffffef4

Disassembly of section .text.record_member_pointer:

d0015adc <.text.record_member_pointer>:
d0015adc:	447b4b44 	ldrbtmi	r4, [fp], #-2884	; 0xfffff4bc
d0015ae0:	4ff0e92d 	svcmi	0x00f0e92d
d0015ae4:	460e4604 	strmi	r4, [lr], -r4, lsl #12
d0015ae8:	8b04ed2d 	blhi	0xd0150fa4
d0015aec:	3a10ee09 	bcc	0xd0451318
d0015af0:	9203b085 	andls	fp, r3, #133	; 0x85
d0015af4:	ee1969a3 	vnmls.f16	s12, s19, s7
d0015af8:	f2402a10 	vpmin.s8	d18, d0, d0
d0015afc:	46201101 	strtmi	r1, [r0], -r1, lsl #2
d0015b00:	3a10ee08 	bcc	0xd0451328
d0015b04:	f8d469e3 			; <UNDEFINED> instruction: 0xf8d469e3
d0015b08:	ee08b024 	cdp	0, 0, cr11, cr8, cr4, {1}
d0015b0c:	6aa33a90 	bvs	0xce8e4554
d0015b10:	9030f894 	mlasls	r0, r4, r8, pc	; <UNPREDICTABLE>
d0015b14:	6b639301 	blvs	0xd18fa720
d0015b18:	f7fd9302 			; <UNDEFINED> instruction: 0xf7fd9302
d0015b1c:	b330f994 	teqlt	r0, #148, 18	; 0x250000	; <UNPREDICTABLE>
d0015b20:	731af44f 	tstvc	sl, #1325400064	; 0x4f000000	; <UNPREDICTABLE>
d0015b24:	fb032500 	blx	0xd00def2e
d0015b28:	f507f706 			; <UNDEFINED> instruction: 0xf507f706
d0015b2c:	442738c8 	strtmi	r3, [r7], #-2248	; 0xfffff738
d0015b30:	08c8f108 	stmiaeq	r8, {r3, r8, ip, sp, lr, pc}^
d0015b34:	37c9f507 	strbcc	pc, [r9, r7, lsl #10]	; <UNPREDICTABLE>
d0015b38:	0a08eb04 	beq	0xd0250750
d0015b3c:	310af897 			; <UNDEFINED> instruction: 0x310af897
d0015b40:	d81942ab 	ldmdale	r9, {r0, r1, r3, r5, r7, r9, lr}
d0015b44:	731af44f 	tstvc	sl, #1325400064	; 0x4f000000	; <UNPREDICTABLE>
d0015b48:	4606fb03 	strmi	pc, [r6], -r3, lsl #22
d0015b4c:	36c9f506 	strbcc	pc, [r9], r6, lsl #10	; <UNPREDICTABLE>
d0015b50:	310af896 			; <UNDEFINED> instruction: 0x310af896
d0015b54:	d11d42ab 	tstle	sp, fp, lsr #5
d0015b58:	b9436da3 	stmdblt	r3, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0015b5c:	447b4b25 	ldrbtmi	r4, [fp], #-2853	; 0xfffff4db
d0015b60:	3b16e9c4 	blcc	0xd05d0278
d0015b64:	e9c49b01 	stmib	r4, {r0, r8, r9, fp, ip, pc}^
d0015b68:	9b023918 	blls	0xd00a3fd0
d0015b6c:	b00566a3 	andlt	r6, r5, r3, lsr #13
d0015b70:	8b04ecbd 	blhi	0xd0150e6c
d0015b74:	8ff0e8bd 	svchi	0x00f0e8bd
d0015b78:	3004f8da 	ldrdcc	pc, [r4], -sl
d0015b7c:	1a90ee18 	bne	0xce4513e4
d0015b80:	2b24f85a 	blcs	0xd0953cf0
d0015b84:	0a10ee18 	beq	0xd04513ec
d0015b88:	fd48f7fa 	stc2l	7, cr15, [r8, #-1000]	; 0xfffffc18
d0015b8c:	d1d92800 	bicsle	r2, r9, r0, lsl #16
d0015b90:	e7d33501 	ldrb	r3, [r3, r1, lsl #10]
d0015b94:	fb032324 	blx	0xd00de82e
d0015b98:	44258505 	strtmi	r8, [r5], #-1285	; 0xfffffafb
d0015b9c:	f8958c6a 			; <UNDEFINED> instruction: 0xf8958c6a
d0015ba0:	f8957020 			; <UNDEFINED> instruction: 0xf8957020
d0015ba4:	b14a6021 	cmplt	sl, r1, lsr #32
d0015ba8:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d0015bac:	f7ff0092 			; <UNDEFINED> instruction: 0xf7ff0092
d0015bb0:	f44ff855 	vst2.16	{d31-d32}, [pc :64], r5
d0015bb4:	462051c2 	strtmi	r5, [r0], -r2, asr #3
d0015bb8:	f832f7ff 			; <UNDEFINED> instruction: 0xf832f7ff
d0015bbc:	d0002fff 	strdle	r2, [r0], -pc	; <UNPREDICTABLE>
d0015bc0:	6da3b12e 	stfvsd	f3, [r3, #184]!	; 0xb8
d0015bc4:	d1d22b00 	bicsle	r2, r2, r0, lsl #22
d0015bc8:	447b4b0b 	ldrbtmi	r4, [fp], #-2827	; 0xfffff4f5
d0015bcc:	212ee7c8 	smlawtcs	lr, r8, r7, lr
d0015bd0:	463e4620 	ldrtmi	r4, [lr], -r0, lsr #12
d0015bd4:	f929f7fd 			; <UNDEFINED> instruction: 0xf929f7fd
d0015bd8:	d18b2800 	orrle	r2, fp, r0, lsl #16
d0015bdc:	42bb9b03 	adcsmi	r9, fp, #3072	; 0xc00
d0015be0:	6da3d0c5 	stcvs	0, cr13, [r3, #788]!	; 0x314
d0015be4:	d1c22b00 	bicle	r2, r2, r0, lsl #22
d0015be8:	447b4b04 	ldrbtmi	r4, [fp], #-2820	; 0xfffff4fc
d0015bec:	bf00e7b8 	svclt	0x0000e7b8
d0015bf0:	ffffff6a 			; <UNDEFINED> instruction: 0xffffff6a
d0015bf4:	ffffff08 			; <UNDEFINED> instruction: 0xffffff08
d0015bf8:	fffffeb7 			; <UNDEFINED> instruction: 0xfffffeb7
d0015bfc:	fffffebf 			; <UNDEFINED> instruction: 0xfffffebf

Disassembly of section .text.record_pointer_field_address:

d0015cb4 <.text.record_pointer_field_address>:
d0015cb4:	447b4b4f 	ldrbtmi	r4, [fp], #-2895	; 0xfffff4b1
d0015cb8:	4ff0e92d 	svcmi	0x00f0e92d
d0015cbc:	460d4604 	strmi	r4, [sp], -r4, lsl #12
d0015cc0:	8b04ed2d 	blhi	0xd015117c
d0015cc4:	3a10ee09 	bcc	0xd04514f0
d0015cc8:	9203b085 	andls	fp, r3, #133	; 0x85
d0015ccc:	ee1969a3 	vnmls.f16	s12, s19, s7
d0015cd0:	f2402a10 	vpmin.s8	d18, d0, d0
d0015cd4:	46201101 	strtmi	r1, [r0], -r1, lsl #2
d0015cd8:	3a10ee08 	bcc	0xd0451500
d0015cdc:	f8d469e3 			; <UNDEFINED> instruction: 0xf8d469e3
d0015ce0:	ee08a024 	cdp	0, 0, cr10, cr8, cr4, {1}
d0015ce4:	6b633a90 	blvs	0xd18e472c
d0015ce8:	9028f8d4 	ldrdls	pc, [r8], -r4	; <UNPREDICTABLE>
d0015cec:	8030f894 	mlashi	r0, r4, r8, pc	; <UNPREDICTABLE>
d0015cf0:	f7fd9301 			; <UNDEFINED> instruction: 0xf7fd9301
d0015cf4:	b330f8a8 	teqlt	r0, #168, 16	; 0xa80000	; <UNPREDICTABLE>
d0015cf8:	731af44f 	tstvc	sl, #1325400064	; 0x4f000000	; <UNPREDICTABLE>
d0015cfc:	fb032600 	blx	0xd00df506
d0015d00:	f507f705 			; <UNDEFINED> instruction: 0xf507f705
d0015d04:	44273bc8 	strtmi	r3, [r7], #-3016	; 0xfffff438
d0015d08:	0bc8f10b 	bleq	0xcf25213c
d0015d0c:	37c9f507 	strbcc	pc, [r9, r7, lsl #10]	; <UNPREDICTABLE>
d0015d10:	030beb04 	movweq	lr, #47876	; 0xbb04
d0015d14:	f8979302 			; <UNDEFINED> instruction: 0xf8979302
d0015d18:	42b3310a 	adcsmi	r3, r3, #-2147483646	; 0x80000002
d0015d1c:	f44fd818 	vst2.8	{d29-d30}, [pc :64], r8
d0015d20:	fb03731a 	blx	0xd00f2992
d0015d24:	f5054505 			; <UNDEFINED> instruction: 0xf5054505
d0015d28:	f89535c9 			; <UNDEFINED> instruction: 0xf89535c9
d0015d2c:	42b3310a 	adcsmi	r3, r3, #-2147483646	; 0x80000002
d0015d30:	6da3d11e 	stfvsd	f5, [r3, #120]!	; 0x78
d0015d34:	4b30b93b 	blmi	0xd0c44228
d0015d38:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0015d3c:	9b013a16 	blls	0xd006459c
d0015d40:	9818e9c4 	ldmdals	r8, {r2, r6, r7, r8, fp, sp, lr, pc}
d0015d44:	b00566a3 	andlt	r6, r5, r3, lsr #13
d0015d48:	8b04ecbd 	blhi	0xd0151044
d0015d4c:	8ff0e8bd 	svchi	0x00f0e8bd
d0015d50:	ee189902 	vnmls.f16	s18, s16, s4
d0015d54:	9b020a10 	blls	0xd009859c
d0015d58:	2b24f851 	blcs	0xd0953ea4
d0015d5c:	9102685b 	tstls	r2, fp, asr r8
d0015d60:	1a90ee18 	bne	0xce4515c8
d0015d64:	fc5af7fa 	mrrc2	7, 15, pc, sl, cr10	; <UNPREDICTABLE>
d0015d68:	d1d82800 	bicsle	r2, r8, r0, lsl #16
d0015d6c:	e7d23601 	ldrb	r3, [r2, r1, lsl #12]
d0015d70:	fb032324 	blx	0xd00dea0a
d0015d74:	4426b606 	strtmi	fp, [r6], #-1542	; 0xfffff9fa
d0015d78:	f8968c72 			; <UNDEFINED> instruction: 0xf8968c72
d0015d7c:	f8965020 			; <UNDEFINED> instruction: 0xf8965020
d0015d80:	b14a7021 	cmplt	sl, r1, lsr #32
d0015d84:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d0015d88:	f7fe0092 			; <UNDEFINED> instruction: 0xf7fe0092
d0015d8c:	f44fff67 			; <UNDEFINED> instruction: 0xf44fff67
d0015d90:	462051c2 	strtmi	r5, [r0], -r2, asr #3
d0015d94:	ff44f7fe 			; <UNDEFINED> instruction: 0xff44f7fe
d0015d98:	7191f44f 	orrsvc	pc, r1, pc, asr #8
d0015d9c:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0015da0:	b170f844 	cmnlt	r0, r4, asr #16	; <UNPREDICTABLE>
d0015da4:	2dffb10f 	ldfcsp	f3, [pc, #60]!	; 0xd0015de8
d0015da8:	6da3d105 	stfvsd	f5, [r3, #20]!
d0015dac:	d1ca2b00 	bicle	r2, sl, r0, lsl #22
d0015db0:	447b4b12 	ldrbtmi	r4, [fp], #-2834	; 0xfffff4ee
d0015db4:	f44fe7c1 	vst1.64	{d30}, [pc], r1
d0015db8:	462041d0 			; <UNDEFINED> instruction: 0x462041d0
d0015dbc:	ff30f7fe 			; <UNDEFINED> instruction: 0xff30f7fe
d0015dc0:	212ee784 	smlawbcs	lr, r4, r7, lr
d0015dc4:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0015dc8:	b148f830 	cmplt	r8, r0, lsr r8	; <UNPREDICTABLE>
d0015dcc:	2dffb917 			; <UNDEFINED> instruction: 0x2dffb917
d0015dd0:	af7cf47f 	svcge	0x007cf47f
d0015dd4:	2b006da3 	blcs	0xd0031468
d0015dd8:	4b09d1b5 	blmi	0xd028a4b4
d0015ddc:	e7ac447b 			; <UNDEFINED> instruction: 0xe7ac447b
d0015de0:	9b03b117 	blls	0xd0102244
d0015de4:	d0ae429d 	umlalle	r4, lr, sp, r2
d0015de8:	2b006da3 	blcs	0xd003147c
d0015dec:	4b05d1ab 	blmi	0xd018a4a0
d0015df0:	e7a2447b 			; <UNDEFINED> instruction: 0xe7a2447b
d0015df4:	ffffff46 			; <UNDEFINED> instruction: 0xffffff46
d0015df8:	fffffee1 			; <UNDEFINED> instruction: 0xfffffee1
d0015dfc:	fffffe8f 			; <UNDEFINED> instruction: 0xfffffe8f
d0015e00:	fffffe85 			; <UNDEFINED> instruction: 0xfffffe85
d0015e04:	fffffe92 			; <UNDEFINED> instruction: 0xfffffe92

Disassembly of section .text.struct_double_pointer_value:

d0015ee8 <.text.struct_double_pointer_value>:
d0015ee8:	4ff7e92d 	svcmi	0x00f7e92d
d0015eec:	460d4604 	strmi	r4, [sp], -r4, lsl #12
d0015ef0:	fefaf7fe 	mrc2	7, 7, pc, cr10, cr14, {7}
d0015ef4:	bb404680 	bllt	0xd10278fc
d0015ef8:	46202126 	strtmi	r2, [r0], -r6, lsr #2
d0015efc:	ff95f7fc 			; <UNDEFINED> instruction: 0xff95f7fc
d0015f00:	4a3c6a63 	bmi	0xd0f30894
d0015f04:	93004683 	movwls	r4, #1667	; 0x683
d0015f08:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d0015f0c:	447a6aa3 	ldrbtmi	r6, [sl], #-2723	; 0xfffff55d
d0015f10:	f8944620 			; <UNDEFINED> instruction: 0xf8944620
d0015f14:	6b669030 	blvs	0xd19b9fdc
d0015f18:	e9d49301 	ldmib	r4, {r0, r8, r9, ip, pc}^
d0015f1c:	f7fc7a06 			; <UNDEFINED> instruction: 0xf7fc7a06
d0015f20:	b190ff92 			; <UNDEFINED> instruction: 0xb190ff92
d0015f24:	46394652 			; <UNDEFINED> instruction: 0x46394652
d0015f28:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0015f2c:	f1b0fbeb 			; <UNDEFINED> instruction: 0xf1b0fbeb
d0015f30:	da0d0a00 	ble	0xd0358738
d0015f34:	b9436da3 	stmdblt	r3, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0015f38:	447b4b2f 	ldrbtmi	r4, [fp], #-2863	; 0xfffff4d1
d0015f3c:	9b0065a3 	blls	0xd002f5d0
d0015f40:	65e366a6 	strbvs	r6, [r3, #1702]!	; 0x6a6
d0015f44:	e9c49b01 	stmib	r4, {r0, r8, r9, fp, ip, pc}^
d0015f48:	b0033918 	andlt	r3, r3, r8, lsl r9
d0015f4c:	8ff0e8bd 	svchi	0x00f0e8bd
d0015f50:	fb022230 	blx	0xd009e81a
d0015f54:	f502420a 			; <UNDEFINED> instruction: 0xf502420a
d0015f58:	f8923222 			; <UNDEFINED> instruction: 0xf8923222
d0015f5c:	f8927136 			; <UNDEFINED> instruction: 0xf8927136
d0015f60:	f1bb2135 			; <UNDEFINED> instruction: 0xf1bb2135
d0015f64:	d0320f00 	eorsle	r0, r2, r0, lsl #30
d0015f68:	d1212a0e 			; <UNDEFINED> instruction: 0xd1212a0e
d0015f6c:	7191f44f 	orrsvc	pc, r1, pc, asr #8
d0015f70:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0015f74:	b160ff5a 	msrlt	SPSR_irq, sl
d0015f78:	46514642 	ldrbmi	r4, [r1], -r2, asr #12
d0015f7c:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0015f80:	462afee5 	strtmi	pc, [sl], -r5, ror #29
d0015f84:	46204639 			; <UNDEFINED> instruction: 0x46204639
d0015f88:	e8bdb003 	pop	{r0, r1, ip, sp, pc}
d0015f8c:	f7ff4ff0 			; <UNDEFINED> instruction: 0xf7ff4ff0
d0015f90:	42afbe91 	adcmi	fp, pc, #2320	; 0x910
d0015f94:	4651d106 	ldrbmi	sp, [r1], -r6, lsl #2
d0015f98:	b0034620 	andlt	r4, r3, r0, lsr #12
d0015f9c:	4ff0e8bd 	svcmi	0x00f0e8bd
d0015fa0:	bf06f7fe 	svclt	0x0006f7fe
d0015fa4:	2b006da3 	blcs	0xd0031638
d0015fa8:	4b14d1cf 	blmi	0xd054a6ec
d0015fac:	e7c5447b 			; <UNDEFINED> instruction: 0xe7c5447b
d0015fb0:	d1182a0d 	tstle	r8, sp, lsl #20
d0015fb4:	212e4a12 			; <UNDEFINED> instruction: 0x212e4a12
d0015fb8:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d0015fbc:	ff43f7fc 			; <UNDEFINED> instruction: 0xff43f7fc
d0015fc0:	d0c22800 	sbcle	r2, r2, r0, lsl #16
d0015fc4:	46204651 			; <UNDEFINED> instruction: 0x46204651
d0015fc8:	fef2f7fe 	mrc2	7, 7, pc, cr2, cr14, {7}
d0015fcc:	2a12e7d9 	bcs	0xd04cff38
d0015fd0:	42afd109 	adcmi	sp, pc, #1073741826	; 0x40000002
d0015fd4:	465ad107 	ldrbmi	sp, [sl], -r7, lsl #2
d0015fd8:	46204651 			; <UNDEFINED> instruction: 0x46204651
d0015fdc:	e8bdb003 	pop	{r0, r1, ip, sp, pc}
d0015fe0:	f7fe4ff0 			; <UNDEFINED> instruction: 0xf7fe4ff0
d0015fe4:	6da3beb3 	stcvs	14, cr11, [r3, #716]!	; 0x2cc
d0015fe8:	d1ae2b00 			; <UNDEFINED> instruction: 0xd1ae2b00
d0015fec:	447b4b05 	ldrbtmi	r4, [fp], #-2821	; 0xfffff4fb
d0015ff0:	bf00e7a4 	svclt	0x0000e7a4
d0015ff4:	fffffef6 			; <UNDEFINED> instruction: 0xfffffef6
d0015ff8:	fffffef9 			; <UNDEFINED> instruction: 0xfffffef9
d0015ffc:	fffffeb7 			; <UNDEFINED> instruction: 0xfffffeb7
d0016000:	fffffed1 			; <UNDEFINED> instruction: 0xfffffed1
d0016004:	fffffeb8 			; <UNDEFINED> instruction: 0xfffffeb8

Disassembly of section .text.copy_record.constprop.0:

d0016008 <.text.copy_record.constprop.0>:
d0016008:	4606b570 			; <UNDEFINED> instruction: 0x4606b570
d001600c:	2500480c 	strcs	r4, [r0, #-2060]	; 0xfffff7f4
d0016010:	42b54478 	adcsmi	r4, r5, #120, 8	; 0x78000000
d0016014:	bd70d100 	ldfltp	f5, [r0, #-0]
d0016018:	f64f00ac 			; <UNDEFINED> instruction: 0xf64f00ac
d001601c:	f7fe01d0 			; <UNDEFINED> instruction: 0xf7fe01d0
d0016020:	3501fdff 	strcc	pc, [r1, #-3583]	; 0xfffff201
d0016024:	5400f444 	strpl	pc, [r0], #-1092	; 0xfffffbbc
d0016028:	4621b2a4 	strtmi	fp, [r1], -r4, lsr #5
d001602c:	fdf8f7fe 	ldc2l	7, cr15, [r8, #1016]!	; 0x3f8
d0016030:	01c1f64f 	biceq	pc, r1, pc, asr #12
d0016034:	fdf4f7fe 	ldc2l	7, cr15, [r4, #1016]!	; 0x3f8
d0016038:	f7fe4621 			; <UNDEFINED> instruction: 0xf7fe4621
d001603c:	e7e8fdf1 			; <UNDEFINED> instruction: 0xe7e8fdf1
d0016040:	0000d40c 	andeq	sp, r0, ip, lsl #8

Disassembly of section .text.patch_branch.isra.0.part.0:

d0016044 <.text.patch_branch.isra.0.part.0>:
d0016044:	2a001a09 	bcs	0xd001c870
d0016048:	0104f1a1 	smlatbeq	r4, r1, r1, pc	; <UNPREDICTABLE>
d001604c:	f44fbf14 			; <UNDEFINED> instruction: 0xf44fbf14
d0016050:	f44f4250 	vst1.16	{d20-d23}, [pc :64], r0
d0016054:	b5f04210 	ldrblt	r4, [r0, #528]!	; 0x210
d0016058:	6600f3c1 	strvs	pc, [r0], -r1, asr #7
d001605c:	3409f3c1 	strcc	pc, [r9], #-961	; 0xfffffc3f
d0016060:	ea864f11 	b	0xce1a9cac
d0016064:	ea4453d1 	b	0xd112afb0
d0016068:	447f2486 	ldrbtmi	r2, [pc], #-1158	; 0xd0016070
d001606c:	f44443db 	vst2.<illegal width 64>	{d20-d23}, [r4 :64], fp
d0016070:	f0034470 			; <UNDEFINED> instruction: 0xf0034470
d0016074:	ea860501 	b	0xce197480
d0016078:	f3c15391 	vrsra.u64	d21, d1, #63
d001607c:	183e014a 	ldmdane	lr!, {r1, r3, r6, r8}
d0016080:	f88643db 			; <UNDEFINED> instruction: 0xf88643db
d0016084:	0a244040 	beq	0xd092618c
d0016088:	0301f003 	movweq	pc, #4099	; 0x1003	; <UNPREDICTABLE>
d001608c:	4041f886 	submi	pc, r1, r6, lsl #17
d0016090:	ea4302db 	b	0xd10d6c04
d0016094:	430b3345 	movwmi	r3, #45893	; 0xb345
d0016098:	f8864313 			; <UNDEFINED> instruction: 0xf8864313
d001609c:	0a1b3042 	beq	0xd06e21ac
d00160a0:	3043f886 	subcc	pc, r3, r6, lsl #17
d00160a4:	bf00bdf0 	svclt	0x0000bdf0
d00160a8:	00038932 	andeq	r8, r3, r2, lsr r9

Disassembly of section .text.patch_branch.isra.0:

d00160ac <.text.patch_branch.isra.0>:
d00160ac:	4604b410 			; <UNDEFINED> instruction: 0x4604b410
d00160b0:	46114608 	ldrmi	r4, [r1], -r8, lsl #12
d00160b4:	b91c461a 	ldmdblt	ip, {r1, r3, r4, r9, sl, lr}
d00160b8:	4b04f85d 	blmi	0xd0154234
d00160bc:	bfc2f7ff 	svclt	0x00c2f7ff
d00160c0:	4b04f85d 	blmi	0xd015423c
d00160c4:	Address 0x00000000d00160c4 is out of bounds.


Disassembly of section .text.expression:

d0016204 <.text.expression>:
d0016204:	4ff0e92d 	svcmi	0x00f0e92d
d0016208:	b08b6a03 	addlt	r6, fp, r3, lsl #20
d001620c:	f5004690 			; <UNDEFINED> instruction: 0xf5004690
d0016210:	93043225 	movwls	r3, #16933	; 0x4225
d0016214:	6a434604 	bvs	0xd10e7a2c
d0016218:	7030f890 	mlasvc	r0, r0, r8, pc	; <UNPREDICTABLE>
d001621c:	91069301 	tstls	r6, r1, lsl #6
d0016220:	630ae9d0 	movwvs	lr, #43472	; 0xa9d0
d0016224:	6b439305 	blvs	0xd10fae40
d0016228:	f8d29302 			; <UNDEFINED> instruction: 0xf8d29302
d001622c:	33013120 	movwcc	r3, #4384	; 0x1120
d0016230:	f8c22b20 			; <UNDEFINED> instruction: 0xf8c22b20
d0016234:	d9043120 	stmdble	r4, {r5, r8, ip, sp}
d0016238:	1414f8df 	ldrne	pc, [r4], #-2271	; 0xfffff721
d001623c:	f7f94479 			; <UNDEFINED> instruction: 0xf7f94479
d0016240:	f1a8ffb3 			; <UNDEFINED> instruction: 0xf1a8ffb3
d0016244:	42410003 	submi	r0, r1, #3
d0016248:	46204141 	strtmi	r4, [r0], -r1, asr #2
d001624c:	f9fcf002 			; <UNDEFINED> instruction: 0xf9fcf002
d0016250:	3400f8df 	strcc	pc, [r0], #-2271	; 0xfffff721
d0016254:	447b4605 	ldrbtmi	r4, [fp], #-1541	; 0xfffff9fb
d0016258:	4bff9307 	blmi	0xcfffae7c
d001625c:	9308447b 	movwls	r4, #33915	; 0x847b
d0016260:	9058f8d4 	ldrsbls	pc, [r8], #-132	; 0xffffff7c	; <UNPREDICTABLE>
d0016264:	0f00f1b9 	svceq	0x0000f1b9
d0016268:	f8d4d119 			; <UNDEFINED> instruction: 0xf8d4d119
d001626c:	f1baa02c 			; <UNDEFINED> instruction: 0xf1baa02c
d0016270:	f0000f7c 			; <UNDEFINED> instruction: 0xf0000f7c
d0016274:	f300816b 	vrhadd.u8	q4, q0, <illegal reg q13.5>
d0016278:	f1ba8137 			; <UNDEFINED> instruction: 0xf1ba8137
d001627c:	f3000f2f 	vpmax.f32	d0, d0, d31
d0016280:	f1ba8125 			; <UNDEFINED> instruction: 0xf1ba8125
d0016284:	f3000f24 	vpmax.f32	d0, d0, d20
d0016288:	9b06810f 	blls	0xd01b66cc
d001628c:	dc06454b 	cfstr32le	mvfx4, [r6], {75}	; 0x4b
d0016290:	d11b2d02 	tstle	fp, r2, lsl #26
d0016294:	462049f1 			; <UNDEFINED> instruction: 0x462049f1
d0016298:	f7f94479 			; <UNDEFINED> instruction: 0xf7f94479
d001629c:	f108ff85 			; <UNDEFINED> instruction: 0xf108ff85
d00162a0:	2b0133ff 	blcs	0xd00632a4
d00162a4:	815ef200 	cmphi	lr, r0, lsl #4	; <UNPREDICTABLE>
d00162a8:	d10a2d02 	tstle	sl, r2, lsl #26
d00162ac:	b9436da3 	stmdblt	r3, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d00162b0:	447b4beb 	ldrbtmi	r4, [fp], #-3051	; 0xfffff415
d00162b4:	9b0165a3 	blls	0xd006f948
d00162b8:	9b0265e3 	blls	0xd00afa4c
d00162bc:	6718e9c4 	ldrvs	lr, [r8, -r4, asr #19]
d00162c0:	f1b866a3 			; <UNDEFINED> instruction: 0xf1b866a3
d00162c4:	f0400f01 			; <UNDEFINED> instruction: 0xf0400f01
d00162c8:	e14e815e 	cmp	lr, lr, asr r1
d00162cc:	f1094620 			; <UNDEFINED> instruction: 0xf1094620
d00162d0:	f7fc0901 			; <UNDEFINED> instruction: 0xf7fc0901
d00162d4:	f5aafd8f 			; <UNDEFINED> instruction: 0xf5aafd8f
d00162d8:	2b017390 	blcs	0xd0073120
d00162dc:	f240d830 	vtst.8	d29, d0, d16
d00162e0:	46201521 	strtmi	r1, [r0], -r1, lsr #10
d00162e4:	4b98f24f 	blmi	0xce652c28
d00162e8:	0205ebaa 	andeq	lr, r5, #174080	; 0x2a800
d00162ec:	41554255 	cmpmi	r5, r5, asr r2
d00162f0:	f7ff4629 			; <UNDEFINED> instruction: 0xf7ff4629
d00162f4:	2202f8ef 	andcs	pc, r2, #15663104	; 0xef0000
d00162f8:	46824649 	strmi	r4, [r2], r9, asr #12
d00162fc:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0016300:	4620ff81 	strtmi	pc, [r0], -r1, lsl #31
d0016304:	5120f44f 	msrpl	CPSR_, pc, asr #8
d0016308:	fc8af7fe 	stc2	7, cr15, [sl], {254}	; 0xfe
d001630c:	f7ff2101 			; <UNDEFINED> instruction: 0xf7ff2101
d0016310:	f7fff8f4 			; <UNDEFINED> instruction: 0xf7fff8f4
d0016314:	2300f8d3 	movwcs	pc, #2259	; 0x8d3	; <UNPREDICTABLE>
d0016318:	200bf854 	andcs	pc, fp, r4, asr r8	; <UNPREDICTABLE>
d001631c:	46514681 	ldrbmi	r4, [r1], -r1, lsl #13
d0016320:	f7ff6da0 			; <UNDEFINED> instruction: 0xf7ff6da0
d0016324:	4629fec3 	strtmi	pc, [r9], -r3, asr #29
d0016328:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d001632c:	2300fcd5 	movwcs	pc, #3285	; 0xcd5	; <UNPREDICTABLE>
d0016330:	200bf854 	andcs	pc, fp, r4, asr r8	; <UNPREDICTABLE>
d0016334:	6da04649 	stcvs	6, cr4, [r0, #292]!	; 0x124
d0016338:	feb8f7ff 	mrc2	7, 5, pc, cr8, cr15, {7}
d001633c:	e78f2500 	str	r2, [pc, r0, lsl #10]
d0016340:	738ef5aa 	orrvc	pc, lr, #713031680	; 0x2a800000
d0016344:	93032d03 	movwls	r2, #15619	; 0x3d03
d0016348:	1f6bd002 	svcne	0x006bd002
d001634c:	d80f2b02 	stmdale	pc, {r1, r8, r9, fp, sp}	; <UNPREDICTABLE>
d0016350:	2b019b03 	blcs	0xd007cf64
d0016354:	6da3d90c 			; <UNDEFINED> instruction: 0x6da3d90c
d0016358:	d1a02b00 	lslle	r2, r0, #22
d001635c:	447b4bc1 	ldrbtmi	r4, [fp], #-3009	; 0xfffff43f
d0016360:	9b0165a3 	blls	0xd006f9f4
d0016364:	9b0265e3 	blls	0xd00afaf8
d0016368:	6718e9c4 	ldrvs	lr, [r8, -r4, asr #19]
d001636c:	e79666a3 	ldr	r6, [r6, r3, lsr #13]
d0016370:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d0016374:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0016378:	6a23fc53 	bvs	0xd09154cc
d001637c:	22024649 	andcs	r4, r2, #76546048	; 0x4900000
d0016380:	f8d49309 			; <UNDEFINED> instruction: 0xf8d49309
d0016384:	f7ffb02c 			; <UNDEFINED> instruction: 0xf7ffb02c
d0016388:	f64bff3d 			; <UNDEFINED> instruction: 0xf64bff3d
d001638c:	46814106 	strmi	r4, [r1], r6, lsl #2
d0016390:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0016394:	2d04fc45 	stccs	12, cr15, [r4, #-276]	; 0xfffffeec
d0016398:	f0009b09 			; <UNDEFINED> instruction: 0xf0009b09
d001639c:	f1b9811e 			; <UNDEFINED> instruction: 0xf1b9811e
d00163a0:	d1110f04 	tstle	r1, r4, lsl #30
d00163a4:	0f2bf1ba 	svceq	0x002bf1ba
d00163a8:	8130f040 	teqhi	r0, r0, asr #32	; <UNPREDICTABLE>
d00163ac:	2b011eeb 	blcs	0xd005df60
d00163b0:	8130f240 	teqhi	r0, r0, asr #4	; <UNPREDICTABLE>
d00163b4:	46202189 	strtmi	r2, [r0], -r9, lsl #3
d00163b8:	fc32f7fe 	ldc2	7, cr15, [r2], #-1016	; 0xfffffc08
d00163bc:	0108f641 	tsteq	r8, r1, asr #12	; <UNPREDICTABLE>
d00163c0:	f7fe2504 			; <UNDEFINED> instruction: 0xf7fe2504
d00163c4:	e74bfc2d 	strb	pc, [fp, -sp, lsr #24]	; <UNPREDICTABLE>
d00163c8:	d0092d03 	andle	r2, r9, r3, lsl #26
d00163cc:	0f03f1b9 	svceq	0x0003f1b9
d00163d0:	1f6ad006 	svcne	0x006ad006
d00163d4:	d9032a02 	stmdble	r3, {r1, r9, fp, sp}
d00163d8:	0205f1a9 	andeq	pc, r5, #1073741866	; 0x4000002a
d00163dc:	d8492a02 	stmdale	r9, {r1, r9, fp, sp}^
d00163e0:	f5ab9a05 			; <UNDEFINED> instruction: 0xf5ab9a05
d00163e4:	f5a27b81 			; <UNDEFINED> instruction: 0xf5a27b81
d00163e8:	2a017281 	bcs	0xd0072df4
d00163ec:	9a04bf97 	bls	0xd0146250
d00163f0:	fab22200 	blx	0xcec9ebf8
d00163f4:	0952f282 	ldmdbeq	r2, {r1, r7, r9, ip, sp, lr, pc}^
d00163f8:	0f01f1bb 	svceq	0x0001f1bb
d00163fc:	fab3bf96 	blx	0xced0625c
d0016400:	2300f383 	movwcs	pc, #899	; 0x383	; <UNPREDICTABLE>
d0016404:	2d04095b 	vstrcs.16	s0, [r4, #-182]	; 0xffffff4a	; <UNPREDICTABLE>
d0016408:	2d03d009 	stccs	0, cr13, [r3, #-36]	; 0xffffffdc
d001640c:	f1a9d10b 			; <UNDEFINED> instruction: 0xf1a9d10b
d0016410:	2a010203 	bcs	0xd0056c24
d0016414:	9b03d812 	blls	0xd010c464
d0016418:	d8132b01 	ldmdale	r3, {r0, r8, r9, fp, sp}
d001641c:	f1a9e01c 			; <UNDEFINED> instruction: 0xf1a9e01c
d0016420:	29010103 	stmdbcs	r1, {r0, r1, r8}
d0016424:	f1b9d9f7 			; <UNDEFINED> instruction: 0xf1b9d9f7
d0016428:	f0400f04 			; <UNDEFINED> instruction: 0xf0400f04
d001642c:	2d0380cb 	stccs	0, cr8, [r3, #-812]	; 0xfffffcd4
d0016430:	2d04d0f1 	stccs	0, cr13, [r4, #-964]	; 0xfffffc3c
d0016434:	e005d119 	and	sp, r5, r9, lsl r1
d0016438:	d1132d03 	tstle	r3, r3, lsl #26
d001643c:	0f00f1b9 	svceq	0x0000f1b9
d0016440:	80c7f000 	sbchi	pc, r7, r0
d0016444:	b93b6da3 	ldmdblt	fp!, {r0, r1, r5, r7, r8, sl, fp, sp, lr}
d0016448:	65a39b07 	strvs	r9, [r3, #2823]!	; 0xb07
d001644c:	65e39b01 	strbvs	r9, [r3, #2817]!	; 0xb01
d0016450:	e9c49b02 	stmib	r4, {r1, r8, r9, fp, ip, pc}^
d0016454:	66a36718 	ssatvs	r6, #4, r8, lsl #14
d0016458:	46512201 	ldrbmi	r2, [r1], -r1, lsl #4
d001645c:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0016460:	e76bf8bf 			; <UNDEFINED> instruction: 0xe76bf8bf
d0016464:	0f03f1b9 	svceq	0x0003f1b9
d0016468:	2d00d1ec 	stfcsd	f5, [r0, #-944]	; 0xfffffc50
d001646c:	2a00d1ea 	bcs	0xd004ac1c
d0016470:	e7e7d1d1 	ubfx	sp, r1, #3, #8
d0016474:	7393f46f 	orrsvc	pc, r3, #1862270976	; 0x6f000000
d0016478:	2b014453 	blcs	0xd00675cc
d001647c:	2d01d80c 	stccs	8, cr13, [r1, #-48]	; 0xffffffd0
d0016480:	2500bf14 	strcs	fp, [r0, #-3860]	; 0xfffff0ec
d0016484:	462a2501 	strtmi	r2, [sl], -r1, lsl #10
d0016488:	46204651 			; <UNDEFINED> instruction: 0x46204651
d001648c:	f8a8f7ff 			; <UNDEFINED> instruction: 0xf8a8f7ff
d0016490:	bf181e05 	svclt	0x00181e05
d0016494:	e6e32501 	strbt	r2, [r3], r1, lsl #10
d0016498:	d0f42d01 	rscsle	r2, r4, r1, lsl #26
d001649c:	0f01f1b9 	svceq	0x0001f1b9
d00164a0:	f04fe7ee 			; <UNDEFINED> instruction: 0xf04fe7ee
d00164a4:	e6f00902 	ldrbt	r0, [r0], r2, lsl #18
d00164a8:	0325f1aa 	msreq	CPSR_sc, #-2147483606	; 0x8000002a
d00164ac:	d80a2b0a 	stmdale	sl, {r1, r3, r8, r9, fp, sp}
d00164b0:	f003e8df 			; <UNDEFINED> instruction: 0xf003e8df
d00164b4:	09095249 	stmdbeq	r9, {r0, r3, r6, r9, ip, lr}
d00164b8:	09064909 	stmdbeq	r6, {r0, r3, r8, fp, lr}
d00164bc:	00490906 	subeq	r0, r9, r6, lsl #18
d00164c0:	0909f04f 	stmdbeq	r9, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d00164c4:	f04fe6e1 			; <UNDEFINED> instruction: 0xf04fe6e1
d00164c8:	e6de0900 	ldrb	r0, [lr], r0, lsl #18
d00164cc:	0f5ef1ba 	svceq	0x005ef1ba
d00164d0:	f73fd045 			; <UNDEFINED> instruction: 0xf73fd045
d00164d4:	f02aaeda 			; <UNDEFINED> instruction: 0xf02aaeda
d00164d8:	2b3c0302 	blcs	0xd0f170e8
d00164dc:	f04fbf14 			; <UNDEFINED> instruction: 0xf04fbf14
d00164e0:	f04f0900 			; <UNDEFINED> instruction: 0xf04f0900
d00164e4:	e6d00907 	ldrb	r0, [r0], r7, lsl #18
d00164e8:	738ef5aa 	orrvc	pc, lr, #713031680	; 0x2a800000
d00164ec:	f63f2b0c 			; <UNDEFINED> instruction: 0xf63f2b0c
d00164f0:	2b0caecc 	blcs	0xd0342028
d00164f4:	a202d8e7 	andge	sp, r2, #15138816	; 0xe70000
d00164f8:	3023f852 	eorcc	pc, r3, r2, asr r8	; <UNPREDICTABLE>
d00164fc:	4710441a 			; <UNDEFINED> instruction: 0x4710441a
d0016500:	00000035 	andeq	r0, r0, r5, lsr r0
d0016504:	00000035 	andeq	r0, r0, r5, lsr r0
d0016508:	0000003b 	andeq	r0, r0, fp, lsr r0
d001650c:	0000003b 	andeq	r0, r0, fp, lsr r0
d0016510:	ffffffa3 			; <UNDEFINED> instruction: 0xffffffa3
d0016514:	00000053 	andeq	r0, r0, r3, asr r0
d0016518:	ffffffc7 			; <UNDEFINED> instruction: 0xffffffc7
d001651c:	ffffffc7 			; <UNDEFINED> instruction: 0xffffffc7
d0016520:	ffffffc7 			; <UNDEFINED> instruction: 0xffffffc7
d0016524:	ffffffc7 			; <UNDEFINED> instruction: 0xffffffc7
d0016528:	ffffffc7 			; <UNDEFINED> instruction: 0xffffffc7
d001652c:	00000041 	andeq	r0, r0, r1, asr #32
d0016530:	00000041 	andeq	r0, r0, r1, asr #32
d0016534:	0906f04f 	stmdbeq	r6, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d0016538:	f04fe6a7 			; <UNDEFINED> instruction: 0xf04fe6a7
d001653c:	e6a40907 	strt	r0, [r4], r7, lsl #18
d0016540:	0908f04f 	stmdbeq	r8, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d0016544:	f04fe6a1 			; <UNDEFINED> instruction: 0xf04fe6a1
d0016548:	e69e090a 	ldr	r0, [lr], sl, lsl #18
d001654c:	0903f04f 	stmdbeq	r3, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d0016550:	f04fe69b 			; <UNDEFINED> instruction: 0xf04fe69b
d0016554:	e6980901 	ldr	r0, [r8], r1, lsl #18
d0016558:	0905f04f 	stmdbeq	r5, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d001655c:	f04fe695 			; <UNDEFINED> instruction: 0xf04fe695
d0016560:	e6920904 	ldr	r0, [r2], r4, lsl #18
d0016564:	0f01f1b8 	svceq	0x0001f1b8
d0016568:	1eebd118 	mcrne	1, 7, sp, cr11, cr8, {0}
d001656c:	d80a2b04 	stmdale	sl, {r2, r8, r9, fp, sp}
d0016570:	b9436da3 	stmdblt	r3, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0016574:	447b4b3c 	ldrbtmi	r4, [fp], #-2876	; 0xfffff4c4
d0016578:	9b0165a3 	blls	0xd006fc0c
d001657c:	9b0265e3 	blls	0xd00afd10
d0016580:	6718e9c4 	ldrvs	lr, [r8, -r4, asr #19]
d0016584:	f50466a3 			; <UNDEFINED> instruction: 0xf50466a3
d0016588:	46283425 	strtmi	r3, [r8], -r5, lsr #8
d001658c:	3120f8d4 	ldrdcc	pc, [r0, -r4]!
d0016590:	f8c43b01 			; <UNDEFINED> instruction: 0xf8c43b01
d0016594:	b00b3120 	andlt	r3, fp, r0, lsr #2
d0016598:	8ff0e8bd 	svchi	0x00f0e8bd
d001659c:	0f04f1b8 	svceq	0x0004f1b8
d00165a0:	1eebd1f1 	mcrne	1, 7, sp, cr11, cr1, {7}
d00165a4:	d9ee2b01 	stmible	lr!, {r0, r8, r9, fp, sp}^
d00165a8:	f5a39b05 			; <UNDEFINED> instruction: 0xf5a39b05
d00165ac:	2b017381 	blcs	0xd00733b8
d00165b0:	9b04d802 	blls	0xd014c5c0
d00165b4:	d0e62b00 	rscle	r2, r6, r0, lsl #22
d00165b8:	2b006da3 	blcs	0xd0031c4c
d00165bc:	4b2bd1e3 	blmi	0xd0b0ad50
d00165c0:	e7d9447b 			; <UNDEFINED> instruction: 0xe7d9447b
d00165c4:	f47f2d04 			; <UNDEFINED> instruction: 0xf47f2d04
d00165c8:	f1b9af37 			; <UNDEFINED> instruction: 0xf1b9af37
d00165cc:	f47f0f00 			; <UNDEFINED> instruction: 0xf47f0f00
d00165d0:	2b00af49 	blcs	0xd00422fc
d00165d4:	af1ff47f 	svcge	0x001ff47f
d00165d8:	f1bae734 			; <UNDEFINED> instruction: 0xf1bae734
d00165dc:	d1260f2b 			; <UNDEFINED> instruction: 0xd1260f2b
d00165e0:	0f04f1b9 	svceq	0x0004f1b9
d00165e4:	aee2f43f 	mcrge	4, 7, pc, cr2, cr15, {1}	; <UNPREDICTABLE>
d00165e8:	0f03f1b9 	svceq	0x0003f1b9
d00165ec:	2180d012 	orrcs	sp, r0, r2, lsl r0
d00165f0:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d00165f4:	f641fb15 			; <UNDEFINED> instruction: 0xf641fb15
d00165f8:	f6412308 			; <UNDEFINED> instruction: 0xf6412308
d00165fc:	f1ba0108 			; <UNDEFINED> instruction: 0xf1ba0108
d0016600:	bf180f2b 	svclt	0x00180f2b
d0016604:	f7fe4619 			; <UNDEFINED> instruction: 0xf7fe4619
d0016608:	e629fb0b 	strt	pc, [r9], -fp, lsl #22
d001660c:	0f2df1ba 	svceq	0x002df1ba
d0016610:	aee6f47f 	mcrge	4, 7, pc, cr6, cr15, {3}	; <UNPREDICTABLE>
d0016614:	2b006da3 	blcs	0xd0031ca8
d0016618:	ae22f47f 	mcrge	4, 1, pc, cr2, cr15, {3}	; <UNPREDICTABLE>
d001661c:	65a39b08 	strvs	r9, [r3, #2824]!	; 0xb08
d0016620:	65e39b01 	strbvs	r9, [r3, #2817]!	; 0xb01
d0016624:	e9c49b02 	stmib	r4, {r1, r8, r9, fp, ip, pc}^
d0016628:	66a36718 	ssatvs	r6, #4, r8, lsl #14
d001662c:	f1bae618 			; <UNDEFINED> instruction: 0xf1bae618
d0016630:	f47f0f2d 			; <UNDEFINED> instruction: 0xf47f0f2d
d0016634:	f1b9aed5 			; <UNDEFINED> instruction: 0xf1b9aed5
d0016638:	d1d50f04 	bicsle	r0, r5, r4, lsl #30
d001663c:	2108f641 	tstcs	r8, r1, asr #12	; <UNPREDICTABLE>
d0016640:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0016644:	f44ffaed 	vst1.64	{d31-d32}, [pc :128]!
d0016648:	f7fe5184 			; <UNDEFINED> instruction: 0xf7fe5184
d001664c:	e675fae9 	ldrbt	pc, [r5], -r9, ror #21	; <UNPREDICTABLE>
d0016650:	fffffe86 			; <UNDEFINED> instruction: 0xfffffe86
d0016654:	ffffff00 			; <UNDEFINED> instruction: 0xffffff00
d0016658:	fffffedf 			; <UNDEFINED> instruction: 0xfffffedf
d001665c:	fffffe52 			; <UNDEFINED> instruction: 0xfffffe52
d0016660:	fffffeda 			; <UNDEFINED> instruction: 0xfffffeda
d0016664:	fffffdb2 			; <UNDEFINED> instruction: 0xfffffdb2
d0016668:	fffffc3a 			; <UNDEFINED> instruction: 0xfffffc3a
d001666c:	fffffc19 			; <UNDEFINED> instruction: 0xfffffc19

Disassembly of section .text.int_pointer_element:

d00166b4 <.text.int_pointer_element>:
d00166b4:	4615b5f8 			; <UNDEFINED> instruction: 0x4615b5f8
d00166b8:	460f4a53 			; <UNDEFINED> instruction: 0x460f4a53
d00166bc:	447a215b 	ldrbtmi	r2, [sl], #-347	; 0xfffffea5
d00166c0:	f7fc4604 			; <UNDEFINED> instruction: 0xf7fc4604
d00166c4:	b910fbc0 	ldmdblt	r0, {r6, r7, r8, r9, fp, ip, sp, lr, pc}
d00166c8:	46282500 	strtmi	r2, [r8], -r0, lsl #10
d00166cc:	f24bbdf8 	vmla.f32	<illegal reg q13.5>, <illegal reg q13.5>, q12
d00166d0:	46204103 	strtmi	r4, [r0], -r3, lsl #2
d00166d4:	faa4f7fe 	blx	0xce9546d4
d00166d8:	46112201 	ldrmi	r2, [r1], -r1, lsl #4
d00166dc:	fd92f7ff 	ldc2	7, cr15, [r2, #1020]	; 0x3fc
d00166e0:	215d4a4a 	cmpcs	sp, sl, asr #20
d00166e4:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d00166e8:	fbadf7fc 	blx	0xceb946e2
d00166ec:	d0eb2800 	rscle	r2, fp, r0, lsl #16
d00166f0:	4106f64b 	tstmi	r6, fp, asr #12	; <UNPREDICTABLE>
d00166f4:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d00166f8:	2180fa93 			; <UNDEFINED> instruction: 0x2180fa93
d00166fc:	fa90f7fe 	blx	0xce4546fc
d0016700:	0108f641 	tsteq	r8, r1, asr #12	; <UNPREDICTABLE>
d0016704:	fa8cf7fe 	blx	0xce354704
d0016708:	d13f2d00 	teqle	pc, r0, lsl #26
d001670c:	2e3d6ae6 	vsubcs.f32	s12, s27, s13
d0016710:	f46fd03e 	vld4.8	{d29-d32}, [pc :256], lr
d0016714:	18737192 	ldmdane	r3!, {r1, r4, r7, r8, ip, sp, lr}^
d0016718:	d9392b01 	ldmdble	r9!, {r0, r8, r9, fp, sp}
d001671c:	7294f46f 	addsvc	pc, r4, #1862270976	; 0x6f000000
d0016720:	2b0418b3 	blcs	0xd011c9f4
d0016724:	f44fd934 	vst2.8	{d29,d31}, [pc :256], r4
d0016728:	462041d0 			; <UNDEFINED> instruction: 0x462041d0
d001672c:	fa78f7fe 	blx	0xd1e5472c
d0016730:	f641e7cb 			; <UNDEFINED> instruction: 0xf641e7cb
d0016734:	46200108 	strtmi	r0, [r0], -r8, lsl #2
d0016738:	fa72f7fe 	blx	0xd1cd4738
d001673c:	4106f64b 	tstmi	r6, fp, asr #12	; <UNPREDICTABLE>
d0016740:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0016744:	f246fa6d 	vpmax.s8	<illegal reg q15.5>, q3, <illegal reg q14.5>
d0016748:	25020108 	strcs	r0, [r2, #-264]	; 0xfffffef8
d001674c:	fa68f7fe 	blx	0xd1a5474c
d0016750:	f641e7bb 			; <UNDEFINED> instruction: 0xf641e7bb
d0016754:	e7ee2108 	strb	r2, [lr, r8, lsl #2]!
d0016758:	0108f244 	tsteq	r8, r4, asr #4	; <UNPREDICTABLE>
d001675c:	f244e7eb 	vabd.s8	q15, q10, <illegal reg q13.5>
d0016760:	e7e83108 	strb	r3, [r8, r8, lsl #2]!
d0016764:	0148f244 	cmpeq	r8, r4, asr #4	; <UNPREDICTABLE>
d0016768:	f244e7e5 	vabd.s8	q15, q10, <illegal reg q10.5>
d001676c:	f7fe6102 			; <UNDEFINED> instruction: 0xf7fe6102
d0016770:	f244fa57 	vpmin.s8	<illegal reg q15.5>, q2, <illegal reg q3.5>
d0016774:	f7fe6108 			; <UNDEFINED> instruction: 0xf7fe6108
d0016778:	f244fa53 	vpmin.s8	<illegal reg q15.5>, q2, <illegal reg q1.5>
d001677c:	f2440190 	vand	d16, d20, d0
d0016780:	f5b61310 			; <UNDEFINED> instruction: 0xf5b61310
d0016784:	bf187f96 	svclt	0x00187f96
d0016788:	e7d44619 	bfi	r4, r9, #12, #9
d001678c:	e79c2504 	ldr	r2, [ip, r4, lsl #10]
d0016790:	d0c82f00 	sbcle	r2, r8, r0, lsl #30
d0016794:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0016798:	f24bfb2d 	vqdmulh.s<illegal width 8>	d31, d11, d29
d001679c:	46204103 	strtmi	r4, [r0], -r3, lsl #2
d00167a0:	fa3ef7fe 	blx	0xd0fd47a0
d00167a4:	d0072e3d 	andle	r2, r7, sp, lsr lr
d00167a8:	41d0f44f 	bicsmi	pc, r0, pc, asr #8
d00167ac:	fa38f7fe 	blx	0xd0e547ac
d00167b0:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d00167b4:	fa34f7fe 	blx	0xd0d547b4
d00167b8:	46202201 	strtmi	r2, [r0], -r1, lsl #4
d00167bc:	f7ff4611 			; <UNDEFINED> instruction: 0xf7ff4611
d00167c0:	2e3dfd21 	cdpcs	13, 3, cr15, cr13, cr1, {1}
d00167c4:	f64bd0ba 			; <UNDEFINED> instruction: 0xf64bd0ba
d00167c8:	46204106 	strtmi	r4, [r0], -r6, lsl #2
d00167cc:	fa28f7fe 	blx	0xd0a547cc
d00167d0:	7392f46f 	orrsvc	pc, r2, #1862270976	; 0x6f000000
d00167d4:	2b0818f3 	blcs	0xd021cba8
d00167d8:	a202d8b0 	andge	sp, r2, #176, 16	; 0xb00000
d00167dc:	3023f852 	eorcc	pc, r3, r2, asr r8	; <UNPREDICTABLE>
d00167e0:	4710441a 			; <UNDEFINED> instruction: 0x4710441a
d00167e4:	ffffff4f 			; <UNDEFINED> instruction: 0xffffff4f
d00167e8:	ffffff6f 			; <UNDEFINED> instruction: 0xffffff6f
d00167ec:	ffffff59 			; <UNDEFINED> instruction: 0xffffff59
d00167f0:	ffffff59 			; <UNDEFINED> instruction: 0xffffff59
d00167f4:	ffffff75 			; <UNDEFINED> instruction: 0xffffff75
d00167f8:	ffffff7b 			; <UNDEFINED> instruction: 0xffffff7b
d00167fc:	ffffff81 			; <UNDEFINED> instruction: 0xffffff81
d0016800:	ffffff87 			; <UNDEFINED> instruction: 0xffffff87
d0016804:	ffffff87 			; <UNDEFINED> instruction: 0xffffff87
d0016808:	ffffffae 			; <UNDEFINED> instruction: 0xffffffae
d001680c:	ffffffaa 			; <UNDEFINED> instruction: 0xffffffaa

Disassembly of section .text.api_call:

d0016a18 <.text.api_call>:
d0016a18:	4ff0e92d 	svcmi	0x00f0e92d
d0016a1c:	8b02ed2d 	blhi	0xd00d1ed8
d0016a20:	f891b089 			; <UNDEFINED> instruction: 0xf891b089
d0016a24:	46043046 	strmi	r3, [r4], -r6, asr #32
d0016a28:	9303460d 	movwls	r4, #13837	; 0x360d
d0016a2c:	0348f101 	movteq	pc, #33025	; 0x8101	; <UNPREDICTABLE>
d0016a30:	23009302 	movwcs	r9, #770	; 0x302
d0016a34:	4bf99301 	blmi	0xcfe7b640
d0016a38:	ee08447b 	mcr	4, 0, r4, cr8, cr11, {3}
d0016a3c:	4bf83a10 	blmi	0xcfe25284
d0016a40:	9304447b 	movwls	r4, #17531	; 0x447b
d0016a44:	447b4bf7 	ldrbtmi	r4, [fp], #-3063	; 0xfffff409
d0016a48:	9b019305 	blls	0xd007b664
d0016a4c:	42939a03 	addsmi	r9, r3, #12288	; 0x3000
d0016a50:	6da3d202 	sfmvs	f5, 1, [r3, #8]!
d0016a54:	d03b2b00 	eorsle	r2, fp, r0, lsl #22
d0016a58:	21294af3 	strdcs	r4, [r9, -r3]!
d0016a5c:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d0016a60:	f9f1f7fc 			; <UNDEFINED> instruction: 0xf9f1f7fc
d0016a64:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d0016a68:	990381d4 	stmdbls	r3, {r2, r4, r6, r7, r8, pc}
d0016a6c:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0016a70:	f24dfd5a 	vmla.f32	<illegal reg q15.5>, <illegal reg q6.5>, q5
d0016a74:	f1050318 			; <UNDEFINED> instruction: 0xf1050318
d0016a78:	f1050740 			; <UNDEFINED> instruction: 0xf1050740
d0016a7c:	f64f0846 			; <UNDEFINED> instruction: 0xf64f0846
d0016a80:	f8df7aff 			; <UNDEFINED> instruction: 0xf8df7aff
d0016a84:	460693a8 	strmi	r9, [r6], -r8, lsr #7
d0016a88:	210c58e2 	smlattcs	ip, r2, r8, r5
d0016a8c:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0016a90:	f837f8e5 			; <UNDEFINED> instruction: 0xf837f8e5
d0016a94:	45533b02 	ldrbmi	r3, [r3, #-2818]	; 0xfffff4fe
d0016a98:	81a6f040 			; <UNDEFINED> instruction: 0x81a6f040
d0016a9c:	71e0f244 	mvnvc	pc, r4, asr #4
d0016aa0:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0016aa4:	b126f8bd 	msrlt	CPSR_sx, sp	; <illegal shifter operand>
d0016aa8:	4130f446 	teqmi	r0, r6, asr #8	; <UNPREDICTABLE>
d0016aac:	f7feb289 			; <UNDEFINED> instruction: 0xf7feb289
d0016ab0:	f895f8b7 			; <UNDEFINED> instruction: 0xf895f8b7
d0016ab4:	2b063047 	blcs	0xd01a2bd8
d0016ab8:	81a6f040 			; <UNDEFINED> instruction: 0x81a6f040
d0016abc:	21c0f24b 	biccs	pc, r0, fp, asr #4
d0016ac0:	b0094620 	andlt	r4, r9, r0, lsr #12
d0016ac4:	8b02ecbd 	blhi	0xd00d1dc0
d0016ac8:	4ff0e8bd 	svcmi	0x00f0e8bd
d0016acc:	b8a8f7fe 	stmialt	r8!, {r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}
d0016ad0:	b12b9b01 			; <UNDEFINED> instruction: 0xb12b9b01
d0016ad4:	2a10ee18 	bcs	0xd045233c
d0016ad8:	4620212c 	strtmi	r2, [r0], -ip, lsr #2
d0016adc:	f9b3f7fc 			; <UNDEFINED> instruction: 0xf9b3f7fc
d0016ae0:	f8939b02 			; <UNDEFINED> instruction: 0xf8939b02
d0016ae4:	f10bb000 			; <UNDEFINED> instruction: 0xf10bb000
d0016ae8:	2b0e33ff 	blcs	0xd03a3aec
d0016aec:	8153f200 	cmphi	r3, r0, lsl #4	; <UNPREDICTABLE>
d0016af0:	f013e8df 			; <UNDEFINED> instruction: 0xf013e8df
d0016af4:	000f001e 	andeq	r0, pc, lr, lsl r0	; <UNPREDICTABLE>
d0016af8:	01510151 	cmpeq	r1, r1, asr r1
d0016afc:	01510151 	cmpeq	r1, r1, asr r1
d0016b00:	01510151 	cmpeq	r1, r1, asr r1
d0016b04:	00290029 	eoreq	r0, r9, r9, lsr #32
d0016b08:	00290151 	eoreq	r0, r9, r1, asr r1
d0016b0c:	011f009f 			; <UNDEFINED> instruction: 0x011f009f
d0016b10:	462000e8 	strtmi	r0, [r0], -r8, ror #1
d0016b14:	fefcf7fe 	mrc2	7, 7, pc, cr12, cr14, {7}
d0016b18:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d0016b1c:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0016b20:	9b01f87f 	blls	0xd0094d24
d0016b24:	93013301 	movwls	r3, #4865	; 0x1301
d0016b28:	33019b02 	movwcc	r9, #6914	; 0x1b02
d0016b2c:	e78c9302 	str	r9, [ip, r2, lsl #6]
d0016b30:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0016b34:	2800f8d9 	stmdacs	r0, {r0, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d0016b38:	49bdd1ee 	ldmibmi	sp!, {r1, r2, r3, r5, r6, r7, r8, ip, lr, pc}
d0016b3c:	46204479 			; <UNDEFINED> instruction: 0x46204479
d0016b40:	fb32f7f9 	blx	0xd0cd4b2e
d0016b44:	4620e7e8 	strtmi	lr, [r0], -r8, ror #15
d0016b48:	f8cef7fe 			; <UNDEFINED> instruction: 0xf8cef7fe
d0016b4c:	d1e32800 	mvnle	r2, r0, lsl #16
d0016b50:	46202126 	strtmi	r2, [r0], -r6, lsr #2
d0016b54:	f969f7fc 			; <UNDEFINED> instruction: 0xf969f7fc
d0016b58:	f2406ae2 	vpmax.s8	q11, q8, q9
d0016b5c:	f8d41301 			; <UNDEFINED> instruction: 0xf8d41301
d0016b60:	f8d4a024 			; <UNDEFINED> instruction: 0xf8d4a024
d0016b64:	429a9028 	addsmi	r9, sl, #40	; 0x28
d0016b68:	8030f894 	mlashi	r0, r4, r8, pc	; <UNPREDICTABLE>
d0016b6c:	d0066b67 	andle	r6, r6, r7, ror #22
d0016b70:	2b006da3 	blcs	0xd0032204
d0016b74:	4bafd1d0 	blmi	0xcec0b2bc
d0016b78:	65a3447b 	strvs	r4, [r3, #1147]!	; 0x47b
d0016b7c:	e9d4e02b 	ldmib	r4, {r0, r1, r3, r5, sp, lr, pc}^
d0016b80:	46201206 	strtmi	r1, [r0], -r6, lsl #4
d0016b84:	91069207 	tstls	r6, r7, lsl #4
d0016b88:	fe42f7f9 	mcr2	7, 2, pc, cr2, cr9, {7}	; <UNPREDICTABLE>
d0016b8c:	dbef1e06 	blle	0xcfbde3ac
d0016b90:	46209a07 	strtmi	r9, [r0], -r7, lsl #20
d0016b94:	f7f99906 			; <UNDEFINED> instruction: 0xf7f99906
d0016b98:	2800fdb5 	stmdacs	r0, {r0, r2, r4, r5, r7, r8, sl, fp, ip, sp, lr, pc}
d0016b9c:	f1bbdae8 			; <UNDEFINED> instruction: 0xf1bbdae8
d0016ba0:	d01e0f09 	andsle	r0, lr, r9, lsl #30
d0016ba4:	0f0cf1bb 	svceq	0x000cf1bb
d0016ba8:	f8dfd124 			; <UNDEFINED> instruction: 0xf8dfd124
d0016bac:	f04fb28c 			; <UNDEFINED> instruction: 0xf04fb28c
d0016bb0:	49a20c02 	stmibmi	r2!, {r1, sl, fp}
d0016bb4:	466244fb 			; <UNDEFINED> instruction: 0x466244fb
d0016bb8:	23384479 	teqcs	r8, #2030043136	; 0x79000000
d0016bbc:	18e04373 	stmiane	r0!, {r0, r1, r4, r5, r6, r8, r9, lr}^
d0016bc0:	3000f500 	andcc	pc, r0, r0, lsl #10
d0016bc4:	e12bf890 	msr	CPSR_fxc, r0	; <illegal shifter operand>
d0016bc8:	d01c45e6 	andsle	r4, ip, r6, ror #11
d0016bcc:	2b006da3 	blcs	0xd0032260
d0016bd0:	f8c4d1a2 			; <UNDEFINED> instruction: 0xf8c4d1a2
d0016bd4:	f8c4b058 			; <UNDEFINED> instruction: 0xf8c4b058
d0016bd8:	66a7a05c 	ssatvs	sl, #8, ip, asr #0
d0016bdc:	9818e9c4 	ldmdals	r8, {r2, r6, r7, r8, fp, sp, lr, pc}
d0016be0:	f8dfe79a 			; <UNDEFINED> instruction: 0xf8dfe79a
d0016be4:	f04fb25c 			; <UNDEFINED> instruction: 0xf04fb25c
d0016be8:	49960c01 	ldmibmi	r6, {r0, sl, fp}
d0016bec:	44fb2205 	ldrbtmi	r2, [fp], #517	; 0x205
d0016bf0:	e7e24479 			; <UNDEFINED> instruction: 0xe7e24479
d0016bf4:	b250f8df 	subslt	pc, r0, #14614528	; 0xdf0000
d0016bf8:	0c01f04f 	stceq	0, cr15, [r1], {79}	; 0x4f
d0016bfc:	44fb4993 	ldrbtmi	r4, [fp], #2451	; 0x993
d0016c00:	44794662 	ldrbtmi	r4, [r9], #-1634	; 0xfffff99e
d0016c04:	f890e7d9 			; <UNDEFINED> instruction: 0xf890e7d9
d0016c08:	42900128 	addsmi	r0, r0, #40, 2
d0016c0c:	f503d1de 			; <UNDEFINED> instruction: 0xf503d1de
d0016c10:	f2003000 	vhadd.s8	d3, d0, d0
d0016c14:	4420102f 	strtmi	r1, [r0], #-47	; 0xffffffd1
d0016c18:	fc02f008 	stc2	0, cr15, [r2], {8}
d0016c1c:	d1d52800 	bicsle	r2, r5, r0, lsl #16
d0016c20:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0016c24:	4632f8e7 	ldrtmi	pc, [r2], -r7, ror #17	; <UNPREDICTABLE>
d0016c28:	46202102 	strtmi	r2, [r0], -r2, lsl #2
d0016c2c:	f96cf7fe 			; <UNDEFINED> instruction: 0xf96cf7fe
d0016c30:	4620e772 			; <UNDEFINED> instruction: 0x4620e772
d0016c34:	f858f7fe 			; <UNDEFINED> instruction: 0xf858f7fe
d0016c38:	f47f2800 			; <UNDEFINED> instruction: 0xf47f2800
d0016c3c:	4a84af6d 	bmi	0xce1429f8
d0016c40:	46202126 	strtmi	r2, [r0], -r6, lsr #2
d0016c44:	f7fc447a 			; <UNDEFINED> instruction: 0xf7fc447a
d0016c48:	2800f8fe 	stmdacs	r0, {r1, r2, r3, r4, r5, r6, r7, fp, ip, sp, lr, pc}
d0016c4c:	af64f43f 	svcge	0x0064f43f
d0016c50:	f2406ae2 	vpmax.s8	q11, q8, q9
d0016c54:	f8d41301 			; <UNDEFINED> instruction: 0xf8d41301
d0016c58:	429aa024 	addsmi	sl, sl, #36	; 0x24
d0016c5c:	9028f8d4 	ldrdls	pc, [r8], -r4	; <UNPREDICTABLE>
d0016c60:	8030f894 	mlashi	r0, r4, r8, pc	; <UNPREDICTABLE>
d0016c64:	d0066b67 	andle	r6, r6, r7, ror #22
d0016c68:	2b006da3 	blcs	0xd00322fc
d0016c6c:	af54f47f 	svcge	0x0054f47f
d0016c70:	447b4b78 	ldrbtmi	r4, [fp], #-2936	; 0xfffff488
d0016c74:	e9d4e781 	ldmib	r4, {r0, r7, r8, r9, sl, sp, lr, pc}^
d0016c78:	46201206 	strtmi	r1, [r0], -r6, lsl #4
d0016c7c:	91069207 	tstls	r6, r7, lsl #4
d0016c80:	fd5ff7f9 	ldc2l	7, cr15, [pc, #-996]	; 0xd00168a4
d0016c84:	dbef1e06 	blle	0xcfbde4a4
d0016c88:	46209a07 	strtmi	r9, [r0], -r7, lsl #20
d0016c8c:	f7f99906 			; <UNDEFINED> instruction: 0xf7f99906
d0016c90:	2800fd39 	stmdacs	r0, {r0, r3, r4, r5, r8, sl, fp, ip, sp, lr, pc}
d0016c94:	2338dae8 	teqcs	r8, #232, 20	; 0xe8000
d0016c98:	4306fb03 	movwmi	pc, #27395	; 0x6b03	; <UNPREDICTABLE>
d0016c9c:	33baf503 			; <UNDEFINED> instruction: 0x33baf503
d0016ca0:	30ccf893 	smullcc	pc, ip, r3, r8	; <UNPREDICTABLE>
d0016ca4:	d1df2b05 	bicsle	r2, pc, r5, lsl #22
d0016ca8:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0016cac:	2101f8a3 	smlatbcs	r1, r3, r8, pc	; <UNPREDICTABLE>
d0016cb0:	46204632 			; <UNDEFINED> instruction: 0x46204632
d0016cb4:	f928f7fe 			; <UNDEFINED> instruction: 0xf928f7fe
d0016cb8:	6108f244 	tstvs	r8, r4, asr #4	; <UNPREDICTABLE>
d0016cbc:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0016cc0:	e729ffaf 	str	pc, [r9, -pc, lsr #31]!
d0016cc4:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0016cc8:	b110f80f 	tstlt	r0, pc, lsl #16	; <UNPREDICTABLE>
d0016ccc:	44794962 	ldrbtmi	r4, [r9], #-2402	; 0xfffff69e
d0016cd0:	6ae2e735 	bvs	0xcf8d09ac
d0016cd4:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d0016cd8:	a024f8d4 	ldrdge	pc, [r4], -r4	; <UNPREDICTABLE>
d0016cdc:	f8d4429a 			; <UNDEFINED> instruction: 0xf8d4429a
d0016ce0:	f8949028 			; <UNDEFINED> instruction: 0xf8949028
d0016ce4:	6b678030 	blvs	0xd19f6dac
d0016ce8:	6da3d005 	stcvs	0, cr13, [r3, #20]!
d0016cec:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0016cf0:	9b05af13 	blls	0xd0182944
d0016cf4:	e9d4e741 	ldmib	r4, {r0, r6, r8, r9, sl, sp, lr, pc}^
d0016cf8:	46201206 	strtmi	r1, [r0], -r6, lsl #4
d0016cfc:	91069207 	tstls	r6, r7, lsl #4
d0016d00:	fd1ff7f9 	ldc2	7, cr15, [pc, #-996]	; 0xd0016924
d0016d04:	dbf01e06 	blle	0xcfc1e524
d0016d08:	46209a07 	strtmi	r9, [r0], -r7, lsl #20
d0016d0c:	f7f99906 			; <UNDEFINED> instruction: 0xf7f99906
d0016d10:	2800fcf9 	stmdacs	r0, {r0, r3, r4, r5, r6, r7, sl, fp, ip, sp, lr, pc}
d0016d14:	2338dae9 	teqcs	r8, #954368	; 0xe9000
d0016d18:	4306fb03 	movwmi	pc, #27395	; 0x6b03	; <UNPREDICTABLE>
d0016d1c:	33baf503 			; <UNDEFINED> instruction: 0x33baf503
d0016d20:	20ccf893 	smullcs	pc, ip, r3, r8	; <UNPREDICTABLE>
d0016d24:	d1e02a08 	mvnle	r2, r8, lsl #20
d0016d28:	30d8f8d3 	ldrsbcc	pc, [r8], #131	; 0x83	; <UNPREDICTABLE>
d0016d2c:	d9dc2bff 	ldmible	ip, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, fp, sp}^
d0016d30:	4620e7ba 			; <UNDEFINED> instruction: 0x4620e7ba
d0016d34:	ffd8f7fd 			; <UNDEFINED> instruction: 0xffd8f7fd
d0016d38:	f47f2800 			; <UNDEFINED> instruction: 0xf47f2800
d0016d3c:	6ae2aeed 	bvs	0xcf8c28f8
d0016d40:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d0016d44:	a024f8d4 	ldrdge	pc, [r4], -r4	; <UNPREDICTABLE>
d0016d48:	f8d4429a 			; <UNDEFINED> instruction: 0xf8d4429a
d0016d4c:	f8949028 			; <UNDEFINED> instruction: 0xf8949028
d0016d50:	6b678030 	blvs	0xd19f6e18
d0016d54:	6da3d005 	stcvs	0, cr13, [r3, #20]!
d0016d58:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0016d5c:	9b04aedd 	blls	0xd01428d8
d0016d60:	e9d4e70b 	ldmib	r4, {r0, r1, r3, r8, r9, sl, sp, lr, pc}^
d0016d64:	46201206 	strtmi	r1, [r0], -r6, lsl #4
d0016d68:	91069207 	tstls	r6, r7, lsl #4
d0016d6c:	fce9f7f9 	stc2l	7, cr15, [r9], #996	; 0x3e4
d0016d70:	dbf01e06 	blle	0xcfc1e590
d0016d74:	46209a07 	strtmi	r9, [r0], -r7, lsl #20
d0016d78:	f7f99906 			; <UNDEFINED> instruction: 0xf7f99906
d0016d7c:	2800fcc3 	stmdacs	r0, {r0, r1, r6, r7, sl, fp, ip, sp, lr, pc}
d0016d80:	2338dae9 	teqcs	r8, #954368	; 0xe9000
d0016d84:	4306fb03 	movwmi	pc, #27395	; 0x6b03	; <UNPREDICTABLE>
d0016d88:	33baf503 			; <UNDEFINED> instruction: 0x33baf503
d0016d8c:	30ccf893 	smullcc	pc, ip, r3, r8	; <UNPREDICTABLE>
d0016d90:	d1e02b07 	mvnle	r2, r7, lsl #22
d0016d94:	2201e788 	andcs	lr, r1, #136, 14	; 0x2200000
d0016d98:	46114620 	ldrmi	r4, [r1], -r0, lsr #12
d0016d9c:	fa32f7ff 	blx	0xd0cd4da0
d0016da0:	781b9b02 	ldmdavc	fp, {r1, r8, r9, fp, ip, pc}
d0016da4:	2b053b03 	blcs	0xd01659b8
d0016da8:	aeb6f63f 	mrcge	6, 5, APSR_nzcv, cr6, cr15, {1}
d0016dac:	f852a202 			; <UNDEFINED> instruction: 0xf852a202
d0016db0:	441a3023 	ldrmi	r3, [sl], #-35	; 0xffffffdd
d0016db4:	bf004710 	svclt	0x00004710
d0016db8:	00000019 	andeq	r0, r0, r9, lsl r0
d0016dbc:	0000001f 	andeq	r0, r0, pc, lsl r0
d0016dc0:	fffffd61 			; <UNDEFINED> instruction: 0xfffffd61
d0016dc4:	0000002b 	andeq	r0, r0, fp, lsr #32
d0016dc8:	fffffd61 			; <UNDEFINED> instruction: 0xfffffd61
d0016dcc:	00000025 	andeq	r0, r0, r5, lsr #32
d0016dd0:	4132f44f 	teqmi	r2, pc, asr #8	; <UNPREDICTABLE>
d0016dd4:	f24be772 	vaba.s8	q15, <illegal reg q5.5>, q9
d0016dd8:	e76f2180 	strb	r2, [pc, -r0, lsl #3]!
d0016ddc:	2140f24b 	cmpcs	r0, fp, asr #4	; <UNPREDICTABLE>
d0016de0:	f24be76c 	vabd.s8	q15, <illegal reg q5.5>, q14
d0016de4:	e76921c0 	strb	r2, [r9, -r0, asr #3]!
d0016de8:	01dcf64f 	bicseq	pc, ip, pc, asr #12
d0016dec:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0016df0:	f837ff17 			; <UNDEFINED> instruction: 0xf837ff17
d0016df4:	ea411c02 	b	0xd105de04
d0016df8:	b2890109 	addlt	r0, r9, #1073741826	; 0x40000002
d0016dfc:	ff10f7fd 			; <UNDEFINED> instruction: 0xff10f7fd
d0016e00:	f47f4547 			; <UNDEFINED> instruction: 0xf47f4547
d0016e04:	e649ae46 	strb	sl, [r9], -r6, asr #28
d0016e08:	d1022b08 	tstle	r2, r8, lsl #22
d0016e0c:	2140f24b 	cmpcs	r0, fp, asr #4	; <UNPREDICTABLE>
d0016e10:	b009e656 	andlt	lr, r9, r6, asr r6
d0016e14:	8b02ecbd 	blhi	0xd00d2110
d0016e18:	8ff0e8bd 	svchi	0x00f0e8bd
d0016e1c:	fffffe85 			; <UNDEFINED> instruction: 0xfffffe85
d0016e20:	ffffff7a 			; <UNDEFINED> instruction: 0xffffff7a
d0016e24:	ffffff44 			; <UNDEFINED> instruction: 0xffffff44
d0016e28:	ffffff8b 			; <UNDEFINED> instruction: 0xffffff8b
d0016e2c:	ffffc000 			; <UNDEFINED> instruction: 0xffffc000
d0016e30:	fffffda4 			; <UNDEFINED> instruction: 0xfffffda4
d0016e34:	fffffd8c 			; <UNDEFINED> instruction: 0xfffffd8c
d0016e38:	fffffcc3 			; <UNDEFINED> instruction: 0xfffffcc3
d0016e3c:	00007803 	andeq	r7, r0, r3, lsl #16
d0016e40:	fffffc41 			; <UNDEFINED> instruction: 0xfffffc41
d0016e44:	00007549 	andeq	r7, r0, r9, asr #10
d0016e48:	fffffc0e 			; <UNDEFINED> instruction: 0xfffffc0e
d0016e4c:	000077b8 			; <UNDEFINED> instruction: 0x000077b8
d0016e50:	fffffcee 			; <UNDEFINED> instruction: 0xfffffcee
d0016e54:	fffffcc0 			; <UNDEFINED> instruction: 0xfffffcc0
d0016e58:	fffffc9d 			; <UNDEFINED> instruction: 0xfffffc9d

Disassembly of section .text.indirect_call:

d0016ec0 <.text.indirect_call>:
d0016ec0:	fb032330 	blx	0xd00dfb8a
d0016ec4:	e92d0301 	push	{r0, r8, r9}
d0016ec8:	f50341f0 			; <UNDEFINED> instruction: 0xf50341f0
d0016ecc:	f8df3322 			; <UNDEFINED> instruction: 0xf8df3322
d0016ed0:	4604809c 			; <UNDEFINED> instruction: 0x4604809c
d0016ed4:	f893460d 			; <UNDEFINED> instruction: 0xf893460d
d0016ed8:	26007137 			; <UNDEFINED> instruction: 0x26007137
d0016edc:	42be44f8 	adcsmi	r4, lr, #248, 8	; 0xf8000000
d0016ee0:	6da3d201 	sfmvs	f5, 1, [r3, #4]!
d0016ee4:	4639b363 	ldrtmi	fp, [r9], -r3, ror #6
d0016ee8:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0016eec:	4a20fb1c 	bmi	0xd0855b64
d0016ef0:	21294606 			; <UNDEFINED> instruction: 0x21294606
d0016ef4:	4620447a 			; <UNDEFINED> instruction: 0x4620447a
d0016ef8:	ffa5f7fb 			; <UNDEFINED> instruction: 0xffa5f7fb
d0016efc:	f64fb1e8 			; <UNDEFINED> instruction: 0xf64fb1e8
d0016f00:	462001d7 			; <UNDEFINED> instruction: 0x462001d7
d0016f04:	fe8cf7fd 	mcr2	7, 4, pc, cr12, cr13, {7}	; <UNPREDICTABLE>
d0016f08:	ea414917 	b	0xd106936c
d0016f0c:	b2890185 	addlt	r0, r9, #1073741857	; 0x40000021
d0016f10:	fe86f7fd 	mcr2	7, 4, pc, cr6, cr13, {7}	; <UNPREDICTABLE>
d0016f14:	71e0f244 	mvnvc	pc, r4, asr #4
d0016f18:	fe82f7fd 	mcr2	7, 4, pc, cr2, cr13, {7}	; <UNPREDICTABLE>
d0016f1c:	f446b126 	vst4.8	{d27,d29,d31,d33}, [r6 :128], r6
d0016f20:	b2894130 	addlt	r4, r9, #48, 2
d0016f24:	fe7cf7fd 	mrc2	7, 3, pc, cr12, cr13, {7}
d0016f28:	fb002030 	blx	0xd001eff2
d0016f2c:	f5044405 			; <UNDEFINED> instruction: 0xf5044405
d0016f30:	f8943422 			; <UNDEFINED> instruction: 0xf8943422
d0016f34:	2b013138 	blcs	0xd006341c
d0016f38:	2000d014 	andcs	sp, r0, r4, lsl r0
d0016f3c:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d0016f40:	4642b126 	strbmi	fp, [r2], -r6, lsr #2
d0016f44:	4620212c 	strtmi	r2, [r0], -ip, lsr #2
d0016f48:	ff7df7fb 			; <UNDEFINED> instruction: 0xff7df7fb
d0016f4c:	46202201 	strtmi	r2, [r0], -r1, lsl #4
d0016f50:	46113601 	ldrmi	r3, [r1], -r1, lsl #12
d0016f54:	f956f7ff 			; <UNDEFINED> instruction: 0xf956f7ff
d0016f58:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d0016f5c:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0016f60:	e7bcfe5f 	sbfx	pc, pc, #28, #29
d0016f64:	e7e92002 	strb	r2, [r9, r2]!
d0016f68:	ffffc000 			; <UNDEFINED> instruction: 0xffffc000
d0016f6c:	ffffff7c 			; <UNDEFINED> instruction: 0xffffff7c
d0016f70:	ffffff94 			; <UNDEFINED> instruction: 0xffffff94

Disassembly of section .text.struct_array_element:

d0016fec <.text.struct_array_element>:
d0016fec:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d0016ff0:	4a244617 	bmi	0xd0928854
d0016ff4:	215b460d 	cmpcs	fp, sp, lsl #12
d0016ff8:	4604447a 			; <UNDEFINED> instruction: 0x4604447a
d0016ffc:	f7fb461e 			; <UNDEFINED> instruction: 0xf7fb461e
d0017000:	b3e0ff22 	mvnlt	pc, #34, 30	; 0x88
d0017004:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d0017008:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d001700c:	2201fe09 	andcs	pc, r1, #9, 28	; 0x90
d0017010:	f7ff4611 			; <UNDEFINED> instruction: 0xf7ff4611
d0017014:	4a1cf8f7 	bmi	0xd07553f8
d0017018:	4620215d 			; <UNDEFINED> instruction: 0x4620215d
d001701c:	f7fb447a 			; <UNDEFINED> instruction: 0xf7fb447a
d0017020:	b360ff12 	msrlt	SPSR_, #18, 30	; 0x48
d0017024:	4106f64b 	tstmi	r6, fp, asr #12	; <UNPREDICTABLE>
d0017028:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d001702c:	f44ffdf9 			; <UNDEFINED> instruction: 0xf44ffdf9
d0017030:	2102701a 	tstcs	r2, sl, lsl r0
d0017034:	4005fb00 	andmi	pc, r5, r0, lsl #22
d0017038:	30c9f500 	sbccc	pc, r9, r0, lsl #10
d001703c:	2108f8b0 			; <UNDEFINED> instruction: 0x2108f8b0
d0017040:	00924620 	addseq	r4, r2, r0, lsr #12
d0017044:	fe0af7fd 	mcr2	7, 0, pc, cr10, cr13, {7}	; <UNPREDICTABLE>
d0017048:	3150f244 	cmpcc	r0, r4, asr #4	; <UNPREDICTABLE>
d001704c:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0017050:	f44ffde7 			; <UNDEFINED> instruction: 0xf44ffde7
d0017054:	f7fd51c2 			; <UNDEFINED> instruction: 0xf7fd51c2
d0017058:	b986fde3 	stmiblt	r6, {r0, r1, r5, r6, r7, r8, sl, fp, ip, sp, lr, pc}
d001705c:	f7fb212e 			; <UNDEFINED> instruction: 0xf7fb212e
d0017060:	b138fee4 	teqlt	r8, r4, ror #29	; <UNPREDICTABLE>
d0017064:	463a4633 			; <UNDEFINED> instruction: 0x463a4633
d0017068:	46204629 	strtmi	r4, [r0], -r9, lsr #12
d001706c:	41f0e8bd 	ldrhmi	lr, [r0, #141]!	; 0x8d
d0017070:	bfa2f000 	svclt	0x00a2f000
d0017074:	46204905 	strtmi	r4, [r0], -r5, lsl #18
d0017078:	f7f94479 			; <UNDEFINED> instruction: 0xf7f94479
d001707c:	2003f895 	mulcs	r3, r5, r8
d0017080:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d0017084:	ffffff78 			; <UNDEFINED> instruction: 0xffffff78
d0017088:	ffffff74 			; <UNDEFINED> instruction: 0xffffff74
d001708c:	ffffff3e 			; <UNDEFINED> instruction: 0xffffff3e

Disassembly of section .text.record_value_address:

d001719c <.text.record_value_address>:
d001719c:	e92d4a54 	push	{r2, r4, r6, r9, fp, lr}
d00171a0:	447a4ff0 	ldrbtmi	r4, [sl], #-4080	; 0xfffff010
d00171a4:	4689b087 	strmi	fp, [r9], r7, lsl #1
d00171a8:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d00171ac:	6a454604 	bvs	0xd11689c4
d00171b0:	f8906a86 			; <UNDEFINED> instruction: 0xf8906a86
d00171b4:	f8d07030 			; <UNDEFINED> instruction: 0xf8d07030
d00171b8:	e9d08034 	ldmib	r0, {r2, r4, r5, pc}^
d00171bc:	f7fbab06 			; <UNDEFINED> instruction: 0xf7fbab06
d00171c0:	b1f0fe42 	mvnslt	pc, r2, asr #28
d00171c4:	46202128 	strtmi	r2, [r0], -r8, lsr #2
d00171c8:	fe2ff7fb 	mcr2	7, 1, pc, cr15, cr11, {7}	; <UNPREDICTABLE>
d00171cc:	462bb1e0 	strtmi	fp, [fp], -r0, ror #3
d00171d0:	4651465a 			; <UNDEFINED> instruction: 0x4651465a
d00171d4:	e88d4620 	stm	sp, {r5, r9, sl, lr}
d00171d8:	f00001c0 			; <UNDEFINED> instruction: 0xf00001c0
d00171dc:	2806f959 	stmdacs	r6, {r0, r3, r4, r6, r8, fp, ip, sp, lr, pc}
d00171e0:	f504d105 			; <UNDEFINED> instruction: 0xf504d105
d00171e4:	f8d33325 			; <UNDEFINED> instruction: 0xf8d33325
d00171e8:	454b3124 	strbmi	r3, [fp, #-292]	; 0xfffffedc
d00171ec:	6da3d009 	stcvs	0, cr13, [r3, #36]!	; 0x24
d00171f0:	4b40b93b 	blmi	0xd10456e4
d00171f4:	f8c4447b 			; <UNDEFINED> instruction: 0xf8c4447b
d00171f8:	e9c48068 	stmib	r4, {r3, r5, r6, pc}^
d00171fc:	e9c43516 	stmib	r4, {r1, r2, r4, r8, sl, ip, sp}^
d0017200:	b0076718 	andlt	r6, r7, r8, lsl r7
d0017204:	8ff0e8bd 	svchi	0x00f0e8bd
d0017208:	4651465a 			; <UNDEFINED> instruction: 0x4651465a
d001720c:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d0017210:	1e03fa79 			; <UNDEFINED> instruction: 0x1e03fa79
d0017214:	465ada53 			; <UNDEFINED> instruction: 0x465ada53
d0017218:	46204651 			; <UNDEFINED> instruction: 0x46204651
d001721c:	f7f99305 			; <UNDEFINED> instruction: 0xf7f99305
d0017220:	1e02fa90 	vmovne	s5, pc
d0017224:	da059b05 	ble	0xd017de40
d0017228:	2b006da3 	blcs	0xd00328bc
d001722c:	4b32d1e9 	blmi	0xd0ccb9d8
d0017230:	e7e0447b 			; <UNDEFINED> instruction: 0xe7e0447b
d0017234:	fb012138 	blx	0xd005f71e
d0017238:	f5014102 			; <UNDEFINED> instruction: 0xf5014102
d001723c:	f89131ba 			; <UNDEFINED> instruction: 0xf89131ba
d0017240:	f891b0cc 			; <UNDEFINED> instruction: 0xf891b0cc
d0017244:	f1bba0ce 			; <UNDEFINED> instruction: 0xf1bba0ce
d0017248:	d1460f0d 	cmple	r6, sp, lsl #30
d001724c:	21014620 	tstcs	r1, r0, lsr #12
d0017250:	fe5af7fd 	mrc2	7, 2, pc, cr10, cr13, {7}
d0017254:	6108f244 	tstvs	r8, r4, asr #4	; <UNPREDICTABLE>
d0017258:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d001725c:	e005fce1 	and	pc, r5, r1, ror #25
d0017260:	dbf32b00 	blle	0xcfce1e68
d0017264:	46204619 			; <UNDEFINED> instruction: 0x46204619
d0017268:	fda2f7fd 	stc2	7, cr15, [r2, #1012]!	; 0x3f4
d001726c:	0b10f1ab 	bleq	0xd0453920
d0017270:	0f01f1bb 	svceq	0x0001f1bb
d0017274:	6ae3d80e 	bvs	0xcf90d2b4
d0017278:	d0052b5b 	andle	r2, r5, fp, asr fp
d001727c:	2b006da3 	blcs	0xd0032910
d0017280:	4b1ed1bf 	blmi	0xd07cb984
d0017284:	e7b6447b 			; <UNDEFINED> instruction: 0xe7b6447b
d0017288:	22002301 	andcs	r2, r0, #67108864	; 0x4000000
d001728c:	46204651 			; <UNDEFINED> instruction: 0x46204651
d0017290:	feacf7ff 	mcr2	7, 5, pc, cr12, cr15, {7}	; <UNPREDICTABLE>
d0017294:	4620212e 	strtmi	r2, [r0], -lr, lsr #2
d0017298:	fdc7f7fb 	stc2l	7, cr15, [r7, #1004]	; 0x3ec
d001729c:	464ab138 			; <UNDEFINED> instruction: 0x464ab138
d00172a0:	46204651 			; <UNDEFINED> instruction: 0x46204651
d00172a4:	e8bdb007 	pop	{r0, r1, r2, ip, sp, pc}
d00172a8:	f7fe4ff0 			; <UNDEFINED> instruction: 0xf7fe4ff0
d00172ac:	45d1bc17 	ldrbmi	fp, [r1, #3095]	; 0xc17
d00172b0:	6da3d0a7 	stcvs	0, cr13, [r3, #668]!	; 0x29c
d00172b4:	d1a42b00 			; <UNDEFINED> instruction: 0xd1a42b00
d00172b8:	447b4b11 	ldrbtmi	r4, [fp], #-2833	; 0xfffff4ef
d00172bc:	2230e79b 	eorscs	lr, r0, #40632320	; 0x26c0000
d00172c0:	4203fb02 	andmi	pc, r3, #2048	; 0x800
d00172c4:	3222f502 	eorcc	pc, r2, #8388608	; 0x800000
d00172c8:	b135f892 	teqlt	r5, r2	; <illegal shifter operand>	; <UNPREDICTABLE>
d00172cc:	a136f892 	teqge	r6, r2	; <illegal shifter operand>	; <UNPREDICTABLE>
d00172d0:	0f0df1bb 	svceq	0x000df1bb
d00172d4:	f04fd0c6 			; <UNDEFINED> instruction: 0xf04fd0c6
d00172d8:	f1ab32ff 			; <UNDEFINED> instruction: 0xf1ab32ff
d00172dc:	2902010f 	stmdbcs	r2, {r0, r1, r2, r3, r8}
d00172e0:	6da3d9be 			; <UNDEFINED> instruction: 0x6da3d9be
d00172e4:	d18c2b00 	orrle	r2, ip, r0, lsl #22
d00172e8:	447b4b06 	ldrbtmi	r4, [fp], #-2822	; 0xfffff4fa
d00172ec:	bf00e783 	svclt	0x0000e783
d00172f0:	fffffeea 			; <UNDEFINED> instruction: 0xfffffeea
d00172f4:	fffffec7 			; <UNDEFINED> instruction: 0xfffffec7
d00172f8:	fffffec6 			; <UNDEFINED> instruction: 0xfffffec6
d00172fc:	fffffec2 			; <UNDEFINED> instruction: 0xfffffec2
d0017300:	fffffeb7 			; <UNDEFINED> instruction: 0xfffffeb7
d0017304:	fffffe2d 			; <UNDEFINED> instruction: 0xfffffe2d

Disassembly of section .text.call.isra.0:

d0017490 <.text.call.isra.0>:
d0017490:	4ff0e92d 	svcmi	0x00f0e92d
d0017494:	460eb087 	strmi	fp, [lr], -r7, lsl #1
d0017498:	f8df4617 			; <UNDEFINED> instruction: 0xf8df4617
d001749c:	9302248c 	movwls	r2, #9356	; 0x248c
d00174a0:	f89d4604 			; <UNDEFINED> instruction: 0xf89d4604
d00174a4:	447a3044 	ldrbtmi	r3, [sl], #-68	; 0xffffffbc
d00174a8:	46304639 			; <UNDEFINED> instruction: 0x46304639
d00174ac:	f7f99303 			; <UNDEFINED> instruction: 0xf7f99303
d00174b0:	b1b8f9d8 			; <UNDEFINED> instruction: 0xb1b8f9d8
d00174b4:	2474f8df 	ldrbtcs	pc, [r4], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d00174b8:	46304639 			; <UNDEFINED> instruction: 0x46304639
d00174bc:	f7f9447a 			; <UNDEFINED> instruction: 0xf7f9447a
d00174c0:	2800f9d0 	stmdacs	r0, {r4, r6, r7, r8, fp, ip, sp, lr, pc}
d00174c4:	f8dfd13f 			; <UNDEFINED> instruction: 0xf8dfd13f
d00174c8:	46392468 	ldrtmi	r2, [r9], -r8, ror #8
d00174cc:	447a4630 	ldrbtmi	r4, [sl], #-1584	; 0xfffff9d0
d00174d0:	f9c7f7f9 			; <UNDEFINED> instruction: 0xf9c7f7f9
d00174d4:	bbb04605 	bllt	0xcec28cf0
d00174d8:	21012202 	tstcs	r1, r2, lsl #4
d00174dc:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d00174e0:	e036fe91 	mlas	r6, r1, lr, pc	; <UNPREDICTABLE>
d00174e4:	244cf8df 	strbcs	pc, [ip], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d00174e8:	46304639 			; <UNDEFINED> instruction: 0x46304639
d00174ec:	f7f9447a 			; <UNDEFINED> instruction: 0xf7f9447a
d00174f0:	2800f9b8 	stmdacs	r0, {r3, r4, r5, r7, r8, fp, ip, sp, lr, pc}
d00174f4:	f8dfd1de 			; <UNDEFINED> instruction: 0xf8dfd1de
d00174f8:	46392440 	ldrtmi	r2, [r9], -r0, asr #8
d00174fc:	447a4630 	ldrbtmi	r4, [sl], #-1584	; 0xfffff9d0
d0017500:	f9aff7f9 			; <UNDEFINED> instruction: 0xf9aff7f9
d0017504:	d1d52800 	bicsle	r2, r5, r0, lsl #16
d0017508:	2430f8df 	ldrtcs	pc, [r0], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d001750c:	46304639 			; <UNDEFINED> instruction: 0x46304639
d0017510:	f7f9447a 			; <UNDEFINED> instruction: 0xf7f9447a
d0017514:	4605f9a6 	strmi	pc, [r5], -r6, lsr #19
d0017518:	d1cb2800 	bicle	r2, fp, r0, lsl #16
d001751c:	4631463a 			; <UNDEFINED> instruction: 0x4631463a
d0017520:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d0017524:	4680f9b3 			; <UNDEFINED> instruction: 0x4680f9b3
d0017528:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d001752c:	46018089 	strmi	r8, [r1], -r9, lsl #1
d0017530:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0017534:	f898fa71 			; <UNDEFINED> instruction: 0xf898fa71
d0017538:	2d075047 	stccs	0, cr5, [r7, #-284]	; 0xfffffee4
d001753c:	1f6bd010 	svcne	0x006bd010
d0017540:	415d425d 	cmpmi	sp, sp, asr r2
d0017544:	2201e00d 	andcs	lr, r1, #13
d0017548:	46202501 	strtmi	r2, [r0], -r1, lsl #10
d001754c:	f7fe4611 			; <UNDEFINED> instruction: 0xf7fe4611
d0017550:	4afbfe59 	bmi	0xcff16ebc
d0017554:	46202129 	strtmi	r2, [r0], -r9, lsr #2
d0017558:	f7fb447a 			; <UNDEFINED> instruction: 0xf7fb447a
d001755c:	b920fc74 	stmdblt	r0!, {r2, r4, r5, r6, sl, fp, ip, sp, lr, pc}
d0017560:	46282502 	strtmi	r2, [r8], -r2, lsl #10
d0017564:	e8bdb007 	pop	{r0, r1, r2, ip, sp, pc}
d0017568:	f5048ff0 			; <UNDEFINED> instruction: 0xf5048ff0
d001756c:	f899392d 			; <UNDEFINED> instruction: 0xf899392d
d0017570:	b1b1117e 			; <UNDEFINED> instruction: 0xb1b1117e
d0017574:	817cf8b9 	ldrhhi	pc, [ip, #-137]!	; 0xffffff77	; <UNPREDICTABLE>
d0017578:	2b006da3 	blcs	0xd0032c0c
d001757c:	4642d1f0 			; <UNDEFINED> instruction: 0x4642d1f0
d0017580:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d0017584:	fcc0f7fd 	stc2l	7, cr15, [r0], {253}	; 0xfd
d0017588:	331ef504 	tstcc	lr, #4, 10	; 0x1000000	; <UNPREDICTABLE>
d001758c:	6108f8d3 	ldrdvs	pc, [r8, -r3]
d0017590:	6f00f5b6 	svcvs	0x0000f5b6
d0017594:	49ebd141 	stmibmi	fp!, {r0, r6, r8, ip, lr, pc}^
d0017598:	46204479 			; <UNDEFINED> instruction: 0x46204479
d001759c:	fe04f7f8 	mcr2	7, 0, pc, cr4, cr8, {7}	; <UNPREDICTABLE>
d00175a0:	f504e7de 			; <UNDEFINED> instruction: 0xf504e7de
d00175a4:	f8d333c8 			; <UNDEFINED> instruction: 0xf8d333c8
d00175a8:	f1b880a4 			; <UNDEFINED> instruction: 0xf1b880a4
d00175ac:	d8060f7f 	stmdale	r6, {r0, r1, r2, r3, r4, r5, r6, r8, r9, sl, fp}
d00175b0:	3af8f504 	bcc	0xcfe549c8
d00175b4:	60fcf8da 	ldrsbtvs	pc, [ip], #138	; 0x8a	; <UNPREDICTABLE>
d00175b8:	3f60f5b6 	svccc	0x0060f5b6
d00175bc:	49e2d907 	stmibmi	r2!, {r0, r1, r2, r8, fp, ip, lr, pc}^
d00175c0:	f04f4620 			; <UNDEFINED> instruction: 0xf04f4620
d00175c4:	44790800 	ldrbtmi	r0, [r9], #-2048	; 0xfffff800
d00175c8:	fdeef7f8 	stc2l	7, cr15, [lr, #992]!	; 0x3e0
d00175cc:	f108e7d4 			; <UNDEFINED> instruction: 0xf108e7d4
d00175d0:	36070201 	strcc	r0, [r7], -r1, lsl #4
d00175d4:	20a4f8c3 	adccs	pc, r4, r3, asr #17
d00175d8:	f8942238 			; <UNDEFINED> instruction: 0xf8942238
d00175dc:	f026b008 			; <UNDEFINED> instruction: 0xf026b008
d00175e0:	fb020607 	blx	0xd0098e06
d00175e4:	f5074708 			; <UNDEFINED> instruction: 0xf5074708
d00175e8:	f10737ba 			; <UNDEFINED> instruction: 0xf10737ba
d00175ec:	f00700a4 			; <UNDEFINED> instruction: 0xf00700a4
d00175f0:	2307fef9 	movwcs	pc, #32505	; 0x7ef9	; <UNPREDICTABLE>
d00175f4:	60c8f8c7 	sbcvs	pc, r8, r7, asr #17
d00175f8:	30ccf887 	sbccc	pc, ip, r7, lsl #17
d00175fc:	4300f44f 	movwmi	pc, #1103	; 0x44f	; <UNPREDICTABLE>
d0017600:	b0cdf887 	sbclt	pc, sp, r7, lsl #17
d0017604:	30d8f8c7 	sbcscc	pc, r8, r7, asr #17
d0017608:	2301441e 	movwcs	r4, #5150	; 0x141e
d001760c:	60fcf8ca 	rscsvs	pc, ip, sl, asr #17
d0017610:	817cf8a9 	cmnhi	ip, r9, lsr #17	; <UNPREDICTABLE>
d0017614:	317ef889 	cmncc	lr, r9, lsl #17	; <UNPREDICTABLE>
d0017618:	1c72e7ae 	ldclne	7, cr14, [r2], #-696	; 0xfffffd48
d001761c:	eb044620 	bl	0xd0128ea4
d0017620:	f8c304c6 			; <UNDEFINED> instruction: 0xf8c304c6
d0017624:	f7fd2108 			; <UNDEFINED> instruction: 0xf7fd2108
d0017628:	f505ff49 			; <UNDEFINED> instruction: 0xf505ff49
d001762c:	f504437f 			; <UNDEFINED> instruction: 0xf504437f
d0017630:	3502340e 	strcc	r3, [r2, #-1038]	; 0xfffffbf2
d0017634:	f8c433fd 			; <UNDEFINED> instruction: 0xf8c433fd
d0017638:	f8a40108 			; <UNDEFINED> instruction: 0xf8a40108
d001763c:	e790310c 	ldr	r3, [r0, ip, lsl #2]
d0017640:	4631463a 			; <UNDEFINED> instruction: 0x4631463a
d0017644:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d0017648:	1e03f8e3 	cdpne	8, 0, cr15, cr3, cr3, {7}
d001764c:	da0e9301 	ble	0xd03bc258
d0017650:	2b006da3 	blcs	0xd0032ce4
d0017654:	4bbdd185 	blmi	0xcef8bc70
d0017658:	65a3447b 	strvs	r4, [r3, #1147]!	; 0x47b
d001765c:	65e39b02 	strbvs	r9, [r3, #2818]!	; 0xb02
d0017660:	66239b10 			; <UNDEFINED> instruction: 0x66239b10
d0017664:	66639b03 	strbtvs	r9, [r3], -r3, lsl #22
d0017668:	66a39b12 	ssatvs	r9, #4, r2, lsl #22
d001766c:	463ae779 			; <UNDEFINED> instruction: 0x463ae779
d0017670:	46204631 			; <UNDEFINED> instruction: 0x46204631
d0017674:	f846f7f9 			; <UNDEFINED> instruction: 0xf846f7f9
d0017678:	dae92800 	ble	0xcfa61680
d001767c:	4631463a 			; <UNDEFINED> instruction: 0x4631463a
d0017680:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d0017684:	2800f85e 	stmdacs	r0, {r1, r2, r3, r4, r6, fp, ip, sp, lr, pc}
d0017688:	2338dae2 	teqcs	r8, #925696	; 0xe2000
d001768c:	fb039a01 	blx	0xd00fde9a
d0017690:	f5024202 			; <UNDEFINED> instruction: 0xf5024202
d0017694:	f8923200 			; <UNDEFINED> instruction: 0xf8923200
d0017698:	29041130 	stmdbcs	r4, {r4, r5, r8, ip}
d001769c:	6da3d106 	stfvsd	f5, [r3, #24]!
d00176a0:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d00176a4:	4baaaf5e 	blmi	0xceac3424
d00176a8:	e7d6447b 			; <UNDEFINED> instruction: 0xe7d6447b
d00176ac:	212bf892 	msrcs	CPSR_fxc, r2	; <illegal shifter operand>
d00176b0:	d1782a04 	cmnle	r8, r4, lsl #20
d00176b4:	fb039a01 	blx	0xd00fdec2
d00176b8:	f44f4302 	vst2.8	{d20-d23}, [pc], r2
d00176bc:	f503721a 			; <UNDEFINED> instruction: 0xf503721a
d00176c0:	f8933300 			; <UNDEFINED> instruction: 0xf8933300
d00176c4:	fb02312e 	blx	0xd00a3b86
d00176c8:	f5034303 			; <UNDEFINED> instruction: 0xf5034303
d00176cc:	f8b333c9 			; <UNDEFINED> instruction: 0xf8b333c9
d00176d0:	f1baa108 			; <UNDEFINED> instruction: 0xf1baa108
d00176d4:	d0070f00 	andle	r0, r7, r0, lsl #30
d00176d8:	3625f504 	strtcc	pc, [r5], -r4, lsl #10
d00176dc:	9114f8d6 			; <UNDEFINED> instruction: 0x9114f8d6
d00176e0:	0340f1c9 	movteq	pc, #457	; 0x1c9	; <UNPREDICTABLE>
d00176e4:	d939459a 	ldmdble	r9!, {r1, r3, r4, r7, r8, sl, lr}
d00176e8:	f04f499a 			; <UNDEFINED> instruction: 0xf04f499a
d00176ec:	46200900 	strtmi	r0, [r0], -r0, lsl #18
d00176f0:	f7f84479 			; <UNDEFINED> instruction: 0xf7f84479
d00176f4:	6da3fd59 	stcvs	13, cr15, [r3, #356]!	; 0x164
d00176f8:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d00176fc:	4649af31 			; <UNDEFINED> instruction: 0x4649af31
d0017700:	f04f4620 			; <UNDEFINED> instruction: 0xf04f4620
d0017704:	f7fd0801 			; <UNDEFINED> instruction: 0xf7fd0801
d0017708:	f24bfb53 	vpadd.i8	<illegal reg q15.5>, <illegal reg q5.5>, <illegal reg q1.5>
d001770c:	46204103 	strtmi	r4, [r0], -r3, lsl #2
d0017710:	fa86f7fd 	blx	0xce1d570c
d0017714:	26389b01 	ldrtcs	r9, [r8], -r1, lsl #22
d0017718:	eb04435e 	bl	0xd0128498
d001771c:	f50a0a06 			; <UNDEFINED> instruction: 0xf50a0a06
d0017720:	f89a3a00 			; <UNDEFINED> instruction: 0xf89a3a00
d0017724:	2b043129 	blcs	0xd0123bd0
d0017728:	f506d041 			; <UNDEFINED> instruction: 0xf506d041
d001772c:	f8cd3600 			; <UNDEFINED> instruction: 0xf8cd3600
d0017730:	f8dfa010 			; <UNDEFINED> instruction: 0xf8dfa010
d0017734:	2700a224 	strcs	sl, [r0, -r4, lsr #4]
d0017738:	162ff206 	strtne	pc, [pc], -r6, lsl #4
d001773c:	442644fa 	strtmi	r4, [r6], #-1274	; 0xfffffb06
d0017740:	f8939b04 			; <UNDEFINED> instruction: 0xf8939b04
d0017744:	428f1128 	addmi	r1, pc, #40, 2
d0017748:	6da3d202 	sfmvs	f5, 1, [r3, #8]!
d001774c:	d0492b00 	suble	r2, r9, r0, lsl #22
d0017750:	46204441 	strtmi	r4, [r0], -r1, asr #8
d0017754:	fee7f7fd 	mcr2	7, 7, pc, cr7, cr13, {7}	; <UNPREDICTABLE>
d0017758:	e02c4606 	eor	r4, ip, r6, lsl #12
d001775c:	f8d62300 			; <UNDEFINED> instruction: 0xf8d62300
d0017760:	21007114 	tstcs	r0, r4, lsl r1
d0017764:	23309304 	teqcs	r0, #4, 6	; 0x10000000
d0017768:	0801f107 	stmdaeq	r1, {r0, r1, r2, r8, ip, sp, lr, pc}
d001776c:	b11cf896 			; <UNDEFINED> instruction: 0xb11cf896
d0017770:	4707fb03 	strmi	pc, [r7, -r3, lsl #22]
d0017774:	f8c6461a 			; <UNDEFINED> instruction: 0xf8c6461a
d0017778:	f5078114 			; <UNDEFINED> instruction: 0xf5078114
d001777c:	f5073722 			; <UNDEFINED> instruction: 0xf5073722
d0017780:	f007708a 			; <UNDEFINED> instruction: 0xf007708a
d0017784:	9b04fe2f 	blls	0xd0157048
d0017788:	f887220b 			; <UNDEFINED> instruction: 0xf887220b
d001778c:	3301b134 	movwcc	fp, #4404	; 0x1134
d0017790:	2135f887 	teqcs	r5, r7, lsl #17	; <UNPREDICTABLE>
d0017794:	d8e2459a 	stmiale	r2!, {r1, r3, r4, r7, r8, sl, lr}^
d0017798:	3118f8d6 			; <UNDEFINED> instruction: 0x3118f8d6
d001779c:	bf884598 	svclt	0x00884598
d00177a0:	8118f8c6 	tsthi	r8, r6, asr #17	; <UNPREDICTABLE>
d00177a4:	f04fe7a7 			; <UNDEFINED> instruction: 0xf04fe7a7
d00177a8:	46c10800 	strbmi	r0, [r1], r0, lsl #16
d00177ac:	2600e7b2 			; <UNDEFINED> instruction: 0x2600e7b2
d00177b0:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d00177b4:	4a69f8ad 	bmi	0xd1a95a70
d00177b8:	46202129 	strtmi	r2, [r0], -r9, lsr #2
d00177bc:	f7fb447a 			; <UNDEFINED> instruction: 0xf7fb447a
d00177c0:	2800fb42 	stmdacs	r0, {r1, r6, r8, r9, fp, ip, sp, lr, pc}
d00177c4:	aecdf43f 	mcrge	4, 6, pc, cr13, cr15, {1}	; <UNPREDICTABLE>
d00177c8:	331ef504 	tstcc	lr, #4, 10	; 0x1000000	; <UNPREDICTABLE>
d00177cc:	7108f8d3 	ldrdvc	pc, [r8, -r3]
d00177d0:	6f00f5b7 	svcvs	0x0000f5b7
d00177d4:	6da3d16a 	stfvsd	f5, [r3, #424]!	; 0x1a8
d00177d8:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d00177dc:	4b60aec2 	blmi	0xd18432ec
d00177e0:	e73a447b 			; <UNDEFINED> instruction: 0xe73a447b
d00177e4:	4652b127 	ldrbmi	fp, [r2], -r7, lsr #2
d00177e8:	4620212c 	strtmi	r2, [r0], -ip, lsr #2
d00177ec:	fb2bf7fb 	blx	0xd0b157e2
d00177f0:	bb01f816 	bllt	0xd0095850
d00177f4:	0f0df1bb 	svceq	0x000df1bb
d00177f8:	7931d10a 	ldmdbvc	r1!, {r1, r3, r8, ip, lr, pc}
d00177fc:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0017800:	f24bfccd 	sha1c.32	<illegal reg q15.5>, <illegal reg q13.5>, <illegal reg q6.5>
d0017804:	46204103 	strtmi	r4, [r0], -r3, lsl #2
d0017808:	f7fd3701 			; <UNDEFINED> instruction: 0xf7fd3701
d001780c:	e797fa09 	ldr	pc, [r7, r9, lsl #20]
d0017810:	0f0ef1bb 	svceq	0x000ef1bb
d0017814:	7931d104 	ldmdbvc	r1!, {r2, r8, ip, lr, pc}
d0017818:	f0004620 			; <UNDEFINED> instruction: 0xf0004620
d001781c:	e7f0f915 			; <UNDEFINED> instruction: 0xe7f0f915
d0017820:	0f12f1bb 	svceq	0x0012f1bb
d0017824:	7931d104 	ldmdbvc	r1!, {r2, r8, ip, lr, pc}
d0017828:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d001782c:	e7e8fb5d 	ubfx	pc, sp, #22, #9
d0017830:	0f13f1bb 	svceq	0x0013f1bb
d0017834:	4620d103 	strtmi	sp, [r0], -r3, lsl #2
d0017838:	fb00f7fd 	blx	0xd0055836
d001783c:	f1bbe7e1 			; <UNDEFINED> instruction: 0xf1bbe7e1
d0017840:	d1050f0a 	tstle	r5, sl, lsl #30
d0017844:	21012204 	tstcs	r1, r4, lsl #4
d0017848:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d001784c:	e7d8fcdb 			; <UNDEFINED> instruction: 0xe7d8fcdb
d0017850:	03fbf00b 	mvnseq	pc, #11
d0017854:	d1262b02 			; <UNDEFINED> instruction: 0xd1262b02
d0017858:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d001785c:	2800fa45 	stmdacs	r0, {r0, r2, r6, r9, fp, ip, sp, lr, pc}
d0017860:	6ae2d1cf 	bvs	0xcf8cbfa4
d0017864:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d0017868:	d002429a 	mulle	r2, sl, r2
d001786c:	4479493d 	ldrbtmi	r4, [r9], #-2365	; 0xfffff6c3
d0017870:	69a1e693 	stmibvs	r1!, {r0, r1, r4, r7, r9, sl, sp, lr, pc}
d0017874:	69e24620 	stmibvs	r2!, {r5, r9, sl, lr}^
d0017878:	ff44f7f8 			; <UNDEFINED> instruction: 0xff44f7f8
d001787c:	dbf51e01 	blle	0xcfd5f088
d0017880:	91052330 	tstls	r5, r0, lsr r3
d0017884:	4301fb03 	movwmi	pc, #6915	; 0x1b03	; <UNPREDICTABLE>
d0017888:	3322f503 	msrcc	CPSR_x, #12582912	; 0xc00000
d001788c:	3135f893 	teqcc	r5, r3	; <illegal shifter operand>	; <UNPREDICTABLE>
d0017890:	d1eb455b 	mvnle	r4, fp, asr r5
d0017894:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0017898:	2200faad 	andcs	pc, r0, #708608	; 0xad000
d001789c:	46209905 	strtmi	r9, [r0], -r5, lsl #18
d00178a0:	fa54f7fd 	blx	0xd155589c
d00178a4:	2201e7ad 	andcs	lr, r1, #45350912	; 0x2b40000
d00178a8:	e7cd4611 	bfi	r4, r1, #12, #2
d00178ac:	eb041c7a 	bl	0xd011ea9c
d00178b0:	462007c7 	strtmi	r0, [r0], -r7, asr #15
d00178b4:	2108f8c3 	smlabtcs	r8, r3, r8, pc	; <UNPREDICTABLE>
d00178b8:	370ef507 	strcc	pc, [lr, -r7, lsl #10]
d00178bc:	fdfef7fd 	ldc2l	7, cr15, [lr, #1012]!	; 0x3f4
d00178c0:	f8c79b01 			; <UNDEFINED> instruction: 0xf8c79b01
d00178c4:	f8a70108 			; <UNDEFINED> instruction: 0xf8a70108
d00178c8:	b12e310c 			; <UNDEFINED> instruction: 0xb12e310c
d00178cc:	4130f446 	teqmi	r0, r6, asr #8	; <UNPREDICTABLE>
d00178d0:	b2894620 	addlt	r4, r9, #32, 12	; 0x2000000
d00178d4:	f9a4f7fd 			; <UNDEFINED> instruction: 0xf9a4f7fd
d00178d8:	26389b01 	ldrtcs	r9, [r8], -r1, lsl #22
d00178dc:	4603fb06 	strmi	pc, [r3], -r6, lsl #22
d00178e0:	3600f506 	strcc	pc, [r0], -r6, lsl #10
d00178e4:	312bf896 	msrcc	CPSR_fxc, r6	; <illegal shifter operand>
d00178e8:	d10b2b04 	tstle	fp, r4, lsl #22
d00178ec:	46494620 	strbmi	r4, [r9], -r0, lsr #12
d00178f0:	fa5ef7fd 	blx	0xd17d58ec
d00178f4:	3425f504 	strtcc	pc, [r5], #-1284	; 0xfffffafc
d00178f8:	312ef896 	msrcc	CPSR_fsx, r6	; <illegal shifter operand>
d00178fc:	f8c42506 			; <UNDEFINED> instruction: 0xf8c42506
d0017900:	e62e3124 	strt	r3, [lr], -r4, lsr #2
d0017904:	d1072b05 	tstle	r7, r5, lsl #22
d0017908:	3425f504 	strtcc	pc, [r5], #-1284	; 0xfffffafc
d001790c:	312ef896 	msrcc	CPSR_fsx, r6	; <illegal shifter operand>
d0017910:	f8c42503 			; <UNDEFINED> instruction: 0xf8c42503
d0017914:	e6243124 	strt	r3, [r4], -r4, lsr #2
d0017918:	f43f2b01 			; <UNDEFINED> instruction: 0xf43f2b01
d001791c:	2b03ae21 	blcs	0xd01031a8
d0017920:	2504bf08 	strcs	fp, [r4, #-3848]	; 0xfffff0f8
d0017924:	bf00e61d 	svclt	0x0000e61d
d0017928:	fffffe5e 			; <UNDEFINED> instruction: 0xfffffe5e
d001792c:	fffffe48 			; <UNDEFINED> instruction: 0xfffffe48
d0017930:	fffffe42 			; <UNDEFINED> instruction: 0xfffffe42
d0017934:	fffffe1f 			; <UNDEFINED> instruction: 0xfffffe1f
d0017938:	fffffe12 			; <UNDEFINED> instruction: 0xfffffe12
d001793c:	fffffe0e 			; <UNDEFINED> instruction: 0xfffffe0e
d0017940:	fffffdd2 			; <UNDEFINED> instruction: 0xfffffdd2
d0017944:	fffffde0 			; <UNDEFINED> instruction: 0xfffffde0
d0017948:	fffffd86 			; <UNDEFINED> instruction: 0xfffffd86
d001794c:	fffffd38 			; <UNDEFINED> instruction: 0xfffffd38
d0017950:	fffffd12 			; <UNDEFINED> instruction: 0xfffffd12
d0017954:	fffffcf6 			; <UNDEFINED> instruction: 0xfffffcf6
d0017958:	fffffcdc 			; <UNDEFINED> instruction: 0xfffffcdc
d001795c:	fffffca9 			; <UNDEFINED> instruction: 0xfffffca9
d0017960:	fffffb98 			; <UNDEFINED> instruction: 0xfffffb98
d0017964:	fffffbc9 			; <UNDEFINED> instruction: 0xfffffbc9

Disassembly of section .text.struct_pointer_value:

d0017a48 <.text.struct_pointer_value>:
d0017a48:	f2406ac2 	vpmax.s8	q11, q8, q1
d0017a4c:	429a1301 	addsmi	r1, sl, #67108864	; 0x4000000
d0017a50:	4ff0e92d 	svcmi	0x00f0e92d
d0017a54:	460f4604 	strmi	r4, [pc], -r4, lsl #12
d0017a58:	8b02ed2d 	blhi	0xd00d2f14
d0017a5c:	d14cb087 	smlalbble	fp, ip, r7, r0
d0017a60:	2d286cc5 	stccs	12, cr6, [r8, #-788]!	; 0xfffffcec
d0017a64:	6b43d149 	blvs	0xd110bf90
d0017a68:	b024f8d0 	ldrdlt	pc, [r4], -r0	; <UNPREDICTABLE>
d0017a6c:	a028f8d0 	ldrdge	pc, [r8], -r0	; <UNPREDICTABLE>
d0017a70:	9030f890 	mlasls	r0, r0, r8, pc	; <UNPREDICTABLE>
d0017a74:	e9d09304 	ldmib	r0, {r2, r8, r9, ip, pc}^
d0017a78:	f7fb6806 			; <UNDEFINED> instruction: 0xf7fb6806
d0017a7c:	4af0f9bb 	bmi	0xcfc56170
d0017a80:	46204629 	strtmi	r4, [r0], -r9, lsr #12
d0017a84:	f7fb447a 			; <UNDEFINED> instruction: 0xf7fb447a
d0017a88:	b1a8f9de 	ldrdlt	pc, [r8, lr]!
d0017a8c:	46429b04 	strbmi	r9, [r2], -r4, lsl #22
d0017a90:	46204631 			; <UNDEFINED> instruction: 0x46204631
d0017a94:	465b9302 	ldrbmi	r9, [fp], -r2, lsl #6
d0017a98:	9004f8cd 	andls	pc, r4, sp, asr #17
d0017a9c:	a000f8cd 	andge	pc, r0, sp, asr #17
d0017aa0:	fcf6f7ff 	ldc2l	7, cr15, [r6], #1020	; 0x3fc
d0017aa4:	46054ae7 	strmi	r4, [r5], -r7, ror #21
d0017aa8:	447a4641 	ldrbtmi	r4, [sl], #-1601	; 0xfffff9bf
d0017aac:	f7f84630 			; <UNDEFINED> instruction: 0xf7f84630
d0017ab0:	b130fed8 	teqlt	r0, r8	; <illegal shifter operand>	; <UNPREDICTABLE>
d0017ab4:	d1142d03 	tstle	r4, r3, lsl #26
d0017ab8:	ecbdb007 	ldc	0, cr11, [sp], #28
d0017abc:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d0017ac0:	4ae18ff0 	bmi	0xcf87ba88
d0017ac4:	46304641 	ldrtmi	r4, [r0], -r1, asr #12
d0017ac8:	f7f8447a 			; <UNDEFINED> instruction: 0xf7f8447a
d0017acc:	2800feca 	stmdacs	r0, {r1, r3, r6, r7, r9, sl, fp, ip, sp, lr, pc}
d0017ad0:	2d03d1f0 	stfcsd	f5, [r3, #-960]	; 0xfffffc40
d0017ad4:	f504d105 			; <UNDEFINED> instruction: 0xf504d105
d0017ad8:	f8d33325 			; <UNDEFINED> instruction: 0xf8d33325
d0017adc:	42bb3124 	adcsmi	r3, fp, #36, 2
d0017ae0:	6da3e7e9 	stcvs	7, cr14, [r3, #932]!	; 0x3a4
d0017ae4:	d1e72b00 	mvnle	r2, r0, lsl #22
d0017ae8:	447b4bd8 	ldrbtmi	r4, [fp], #-3032	; 0xfffff428
d0017aec:	3b16e9c4 	blcc	0xd05d2204
d0017af0:	e9c49b04 	stmib	r4, {r2, r8, r9, fp, ip, pc}^
d0017af4:	66a3a918 	ssatvs	sl, #4, r8, lsl #18
d0017af8:	212ae7de 	ldrdcs	lr, [sl, -lr]!	; <UNPREDICTABLE>
d0017afc:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0017b00:	2800f994 	stmdacs	r0, {r2, r4, r7, r8, fp, ip, sp, lr, pc}
d0017b04:	6ae2d03c 	bvs	0xcf8cbbfc
d0017b08:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d0017b0c:	9024f8d4 	ldrdls	pc, [r4], -r4	; <UNPREDICTABLE>
d0017b10:	f8d4429a 			; <UNDEFINED> instruction: 0xf8d4429a
d0017b14:	f8948028 			; <UNDEFINED> instruction: 0xf8948028
d0017b18:	6b656030 	blvs	0xd196fbe0
d0017b1c:	6da3d00a 	stcvs	0, cr13, [r3, #40]!	; 0x28
d0017b20:	d1c92b00 	bicle	r2, r9, r0, lsl #22
d0017b24:	66a54bca 	strtvs	r4, [r5], sl, asr #23
d0017b28:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0017b2c:	e9c48618 	stmib	r4, {r3, r4, r9, sl, pc}^
d0017b30:	e7c13916 	bfi	r3, r6, (invalid: 18:1)
d0017b34:	1206e9d4 	andne	lr, r6, #212, 18	; 0x350000
d0017b38:	f7f84620 			; <UNDEFINED> instruction: 0xf7f84620
d0017b3c:	f1b0fde3 			; <UNDEFINED> instruction: 0xf1b0fde3
d0017b40:	dbec0a00 	blle	0xcfb1a348
d0017b44:	fb032330 	blx	0xd00e080e
d0017b48:	f503430a 			; <UNDEFINED> instruction: 0xf503430a
d0017b4c:	f8933322 			; <UNDEFINED> instruction: 0xf8933322
d0017b50:	2a122135 	bcs	0xd04a002c
d0017b54:	f893d1e3 			; <UNDEFINED> instruction: 0xf893d1e3
d0017b58:	42bb3136 	adcsmi	r3, fp, #-2147483635	; 0x8000000d
d0017b5c:	4620d1df 			; <UNDEFINED> instruction: 0x4620d1df
d0017b60:	f948f7fb 			; <UNDEFINED> instruction: 0xf948f7fb
d0017b64:	22004651 	andcs	r4, r0, #84934656	; 0x5100000
d0017b68:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0017b6c:	f44ff8ef 	vst2.<illegal width 64>	{d31-d32}, [pc :128]
d0017b70:	b00741d0 	ldrdlt	r4, [r7], -r0
d0017b74:	8b02ecbd 	blhi	0xd00d2e70
d0017b78:	4ff0e8bd 	svcmi	0x00f0e8bd
d0017b7c:	b850f7fd 	ldmdalt	r0, {r0, r2, r3, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}^
d0017b80:	46202126 	strtmi	r2, [r0], -r6, lsr #2
d0017b84:	f951f7fb 			; <UNDEFINED> instruction: 0xf951f7fb
d0017b88:	f2406ae3 	vpmax.s8	q11, q8, <illegal reg q9.5>
d0017b8c:	46051201 	strmi	r1, [r5], -r1, lsl #4
d0017b90:	f0404293 			; <UNDEFINED> instruction: 0xf0404293
d0017b94:	69a38142 	stmibvs	r3!, {r1, r6, r8, pc}
d0017b98:	69e64620 	stmibvs	r6!, {r5, r9, sl, lr}^
d0017b9c:	3a10ee08 	bcc	0xd04533c4
d0017ba0:	46326b63 	ldrtmi	r6, [r2], -r3, ror #22
d0017ba4:	b024f8d4 	ldrdlt	pc, [r4], -r4	; <UNPREDICTABLE>
d0017ba8:	1a10ee18 	bne	0xd0453410
d0017bac:	a028f8d4 	ldrdge	pc, [r8], -r4	; <UNPREDICTABLE>
d0017bb0:	9030f894 	mlasls	r0, r4, r8, pc	; <UNPREDICTABLE>
d0017bb4:	f7f89304 			; <UNDEFINED> instruction: 0xf7f89304
d0017bb8:	f1b0fda5 			; <UNDEFINED> instruction: 0xf1b0fda5
d0017bbc:	da220800 	ble	0xd0899bc4
d0017bc0:	ee184632 	mrc	6, 0, r4, cr8, cr2, {1}
d0017bc4:	46201a10 			; <UNDEFINED> instruction: 0x46201a10
d0017bc8:	fdbbf7f8 	ldc2	7, cr15, [fp, #992]!	; 0x3e0
d0017bcc:	b9ed4603 	stmiblt	sp!, {r0, r1, r9, sl, lr}^
d0017bd0:	46314aa0 	ldrtmi	r4, [r1], -r0, lsr #21
d0017bd4:	0a10ee18 	beq	0xd045343c
d0017bd8:	447a9305 	ldrbtmi	r9, [sl], #-773	; 0xfffffcfb
d0017bdc:	fe41f7f8 	mcr2	7, 2, pc, cr1, cr8, {7}	; <UNPREDICTABLE>
d0017be0:	b1989b05 	orrslt	r9, r8, r5, lsl #22
d0017be4:	0f00f1b8 	svceq	0x0000f1b8
d0017be8:	2b00da10 	blcs	0xd004e430
d0017bec:	4620da0e 	strtmi	sp, [r0], -lr, lsl #20
d0017bf0:	f900f7fb 			; <UNDEFINED> instruction: 0xf900f7fb
d0017bf4:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d0017bf8:	ecbdb007 	ldc	0, cr11, [sp], #28
d0017bfc:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d0017c00:	f7fd4ff0 			; <UNDEFINED> instruction: 0xf7fd4ff0
d0017c04:	f04fb869 			; <UNDEFINED> instruction: 0xf04fb869
d0017c08:	e7e033ff 			; <UNDEFINED> instruction: 0xe7e033ff
d0017c0c:	93054620 	movwls	r4, #22048	; 0x5620
d0017c10:	f8f0f7fb 			; <UNDEFINED> instruction: 0xf8f0f7fb
d0017c14:	0f00f1b8 	svceq	0x0000f1b8
d0017c18:	db229b05 	blle	0xd08be834
d0017c1c:	fb012130 	blx	0xd00600e6
d0017c20:	f5014108 			; <UNDEFINED> instruction: 0xf5014108
d0017c24:	f8913122 			; <UNDEFINED> instruction: 0xf8913122
d0017c28:	f8912135 			; <UNDEFINED> instruction: 0xf8912135
d0017c2c:	f0026136 			; <UNDEFINED> instruction: 0xf0026136
d0017c30:	290d01fd 	stmdbcs	sp, {r0, r2, r3, r4, r5, r6, r7, r8}
d0017c34:	4641d124 	strbmi	sp, [r1], -r4, lsr #2
d0017c38:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0017c3c:	212ef8b9 	msrcs	CPSR_fsx, r9	; <illegal shifter operand>
d0017c40:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0017c44:	2800f8f2 	stmdacs	r0, {r1, r4, r5, r6, r7, fp, ip, sp, lr, pc}
d0017c48:	2d00d062 	stccs	0, cr13, [r0, #-392]	; 0xfffffe78
d0017c4c:	463ad04a 	ldrtmi	sp, [sl], -sl, asr #32
d0017c50:	46204631 			; <UNDEFINED> instruction: 0x46204631
d0017c54:	ecbdb007 	ldc	0, cr11, [sp], #28
d0017c58:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d0017c5c:	f7fd4ff0 			; <UNDEFINED> instruction: 0xf7fd4ff0
d0017c60:	2b00bf3d 	blcs	0xd004795c
d0017c64:	2138db5f 	teqcs	r8, pc, asr fp
d0017c68:	4103fb01 	tstmi	r3, r1, lsl #22	; <UNPREDICTABLE>
d0017c6c:	31baf501 			; <UNDEFINED> instruction: 0x31baf501
d0017c70:	20ccf891 	smullcs	pc, ip, r1, r8	; <UNPREDICTABLE>
d0017c74:	60cef891 	smullvs	pc, lr, r1, r8	; <UNPREDICTABLE>
d0017c78:	01fdf002 	mvnseq	pc, r2
d0017c7c:	d026290d 	eorle	r2, r6, sp, lsl #18
d0017c80:	0110f1a2 	tsteq	r0, r2, lsr #3	; <UNPREDICTABLE>
d0017c84:	f2002901 	vmla.i8	d2, d0, d1
d0017c88:	f1b8808e 			; <UNDEFINED> instruction: 0xf1b8808e
d0017c8c:	db4d0f00 	blle	0xd135b894
d0017c90:	46204641 	strtmi	r4, [r0], -r1, asr #12
d0017c94:	f88cf7fd 			; <UNDEFINED> instruction: 0xf88cf7fd
d0017c98:	2b5b6ae3 	blcs	0xd16f282c
d0017c9c:	2301d178 	movwcs	sp, #4472	; 0x1178
d0017ca0:	d04e2d00 	suble	r2, lr, r0, lsl #26
d0017ca4:	22004631 	andcs	r4, r0, #51380224	; 0x3100000
d0017ca8:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0017cac:	212ef99f 	msrcs	CPSR_fsx, pc	; <illegal shifter operand>
d0017cb0:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0017cb4:	2800f8ba 	stmdacs	r0, {r1, r3, r4, r5, r7, fp, ip, sp, lr, pc}
d0017cb8:	42b7d1c9 	adcsmi	sp, r7, #1073741874	; 0x40000032
d0017cbc:	aefcf43f 	mrcge	4, 7, APSR_nzcv, cr12, cr15, {1}
d0017cc0:	2b006da3 	blcs	0xd0033354
d0017cc4:	aef8f47f 	mrcge	4, 7, APSR_nzcv, cr8, cr15, {3}
d0017cc8:	447b4b63 	ldrbtmi	r4, [fp], #-2915	; 0xfffff49d
d0017ccc:	4620e70e 	strtmi	lr, [r0], -lr, lsl #14
d0017cd0:	2101461a 	tstcs	r1, sl, lsl r6
d0017cd4:	f918f7fd 			; <UNDEFINED> instruction: 0xf918f7fd
d0017cd8:	6108f244 	tstvs	r8, r4, asr #4	; <UNPREDICTABLE>
d0017cdc:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0017ce0:	e7acff9f 			; <UNDEFINED> instruction: 0xe7acff9f
d0017ce4:	462a462b 	strtmi	r4, [sl], -fp, lsr #12
d0017ce8:	46204631 			; <UNDEFINED> instruction: 0x46204631
d0017cec:	f964f000 			; <UNDEFINED> instruction: 0xf964f000
d0017cf0:	d1062803 	tstle	r6, r3, lsl #16
d0017cf4:	3325f504 	msrcc	CPSR_sc, #4, 10	; 0x1000000
d0017cf8:	3124f8d3 	ldrdcc	pc, [r4, -r3]!
d0017cfc:	f43f42bb 			; <UNDEFINED> instruction: 0xf43f42bb
d0017d00:	6da3aedb 	stcvs	14, cr10, [r3, #876]!	; 0x36c
d0017d04:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0017d08:	4b54aed7 	blmi	0xd154386c
d0017d0c:	e6ed447b 	uxtab	r4, sp, fp, ror #8
d0017d10:	42b7b115 	adcsmi	fp, r7, #1073741829	; 0x40000005
d0017d14:	aed0f43f 	mrcge	4, 6, APSR_nzcv, cr0, cr15, {1}
d0017d18:	2b006da3 	blcs	0xd00333ac
d0017d1c:	aeccf47f 	mcrge	4, 6, pc, cr12, cr15, {3}	; <UNPREDICTABLE>
d0017d20:	447b4b4f 	ldrbtmi	r4, [fp], #-2895	; 0xfffff4b1
d0017d24:	26ffe6e2 	ldrbtcs	lr, [pc], r2, ror #13
d0017d28:	e7a9220b 	str	r2, [r9, fp, lsl #4]!
d0017d2c:	461a4620 	ldrmi	r4, [sl], -r0, lsr #12
d0017d30:	f7fd2101 			; <UNDEFINED> instruction: 0xf7fd2101
d0017d34:	f244f8e9 	vadd.i8	<illegal reg q15.5>, q10, <illegal reg q12.5>
d0017d38:	46206108 	strtmi	r6, [r0], -r8, lsl #2
d0017d3c:	ff70f7fc 			; <UNDEFINED> instruction: 0xff70f7fc
d0017d40:	4631e7aa 	ldrtmi	lr, [r1], -sl, lsr #15
d0017d44:	4620462a 	strtmi	r4, [r0], -sl, lsr #12
d0017d48:	f950f7ff 			; <UNDEFINED> instruction: 0xf950f7ff
d0017d4c:	4620212e 	strtmi	r2, [r0], -lr, lsr #2
d0017d50:	f86bf7fb 			; <UNDEFINED> instruction: 0xf86bf7fb
d0017d54:	462bb1a8 	strtmi	fp, [fp], -r8, lsr #3
d0017d58:	4631462a 	ldrtmi	r4, [r1], -sl, lsr #12
d0017d5c:	f0004620 			; <UNDEFINED> instruction: 0xf0004620
d0017d60:	2803f92b 	stmdacs	r3, {r0, r1, r3, r5, r8, fp, ip, sp, lr, pc}
d0017d64:	f504d106 			; <UNDEFINED> instruction: 0xf504d106
d0017d68:	f8d33325 			; <UNDEFINED> instruction: 0xf8d33325
d0017d6c:	42bb3124 	adcsmi	r3, fp, #36, 2
d0017d70:	aea2f43f 	mcrge	4, 5, pc, cr2, cr15, {1}	; <UNPREDICTABLE>
d0017d74:	2b006da3 	blcs	0xd0033408
d0017d78:	ae9ef47f 	mrcge	4, 4, APSR_nzcv, cr14, cr15, {3}
d0017d7c:	447b4b39 	ldrbtmi	r4, [fp], #-2873	; 0xfffff4c7
d0017d80:	6da3e6b4 	stcvs	6, cr14, [r3, #720]!	; 0x2d0
d0017d84:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0017d88:	4b37ae97 	blmi	0xd0e037ec
d0017d8c:	e6ad447b 	sxtab	r4, sp, fp, ror #8
d0017d90:	42b7b915 	adcsmi	fp, r7, #344064	; 0x54000
d0017d94:	ae90f43f 	mrcge	4, 4, APSR_nzcv, cr0, cr15, {1}
d0017d98:	2b006da3 	blcs	0xd003342c
d0017d9c:	ae8cf47f 	mcrge	4, 4, pc, cr12, cr15, {3}	; <UNPREDICTABLE>
d0017da0:	447b4b32 	ldrbtmi	r4, [fp], #-2866	; 0xfffff4ce
d0017da4:	2a0ee6a2 	bcs	0xd03d1834
d0017da8:	f1b8d130 			; <UNDEFINED> instruction: 0xf1b8d130
d0017dac:	db2d0f00 	blle	0xd0b5b9b4
d0017db0:	22004641 	andcs	r4, r0, #68157440	; 0x4100000
d0017db4:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0017db8:	f44fffc9 			; <UNDEFINED> instruction: 0xf44fffc9
d0017dbc:	f7fb7191 			; <UNDEFINED> instruction: 0xf7fb7191
d0017dc0:	b1c0f834 	biclt	pc, r0, r4, lsr r8	; <UNPREDICTABLE>
d0017dc4:	f47f2d00 			; <UNDEFINED> instruction: 0xf47f2d00
d0017dc8:	462baf42 	strtmi	sl, [fp], -r2, asr #30
d0017dcc:	4631462a 	ldrtmi	r4, [r1], -sl, lsr #12
d0017dd0:	f0004620 			; <UNDEFINED> instruction: 0xf0004620
d0017dd4:	2803f8f1 	stmdacs	r3, {r0, r4, r5, r6, r7, fp, ip, sp, lr, pc}
d0017dd8:	f504d106 			; <UNDEFINED> instruction: 0xf504d106
d0017ddc:	f8d33325 			; <UNDEFINED> instruction: 0xf8d33325
d0017de0:	42bb3124 	adcsmi	r3, fp, #36, 2
d0017de4:	ae68f43f 	mcrge	4, 3, pc, cr8, cr15, {1}	; <UNPREDICTABLE>
d0017de8:	2b006da3 	blcs	0xd003347c
d0017dec:	ae64f47f 	mcrge	4, 3, pc, cr4, cr15, {3}	; <UNPREDICTABLE>
d0017df0:	447b4b1f 	ldrbtmi	r4, [fp], #-2847	; 0xfffff4e1
d0017df4:	b915e67a 	ldmdblt	r5, {r1, r3, r4, r5, r6, r9, sl, sp, lr, pc}
d0017df8:	f43f42b7 			; <UNDEFINED> instruction: 0xf43f42b7
d0017dfc:	6da3ae5d 	stcvs	14, cr10, [r3, #372]!	; 0x174
d0017e00:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0017e04:	4b1bae59 	blmi	0xd0703770
d0017e08:	e66f447b 			; <UNDEFINED> instruction: 0xe66f447b
d0017e0c:	2b006da3 	blcs	0xd00334a0
d0017e10:	ae52f47f 	mrcge	4, 2, APSR_nzcv, cr2, cr15, {3}
d0017e14:	447b4b18 	ldrbtmi	r4, [fp], #-2840	; 0xfffff4e8
d0017e18:	b938e668 	ldmdblt	r8!, {r3, r5, r6, r9, sl, sp, lr, pc}
d0017e1c:	7381f5a3 	orrvc	pc, r1, #683671552	; 0x28c00000
d0017e20:	d8032b01 	stmdale	r3, {r0, r8, r9, fp, sp}
d0017e24:	2b006a23 	blcs	0xd00326b8
d0017e28:	aee1f43f 	mcrge	4, 7, pc, cr1, cr15, {1}	; <UNPREDICTABLE>
d0017e2c:	46204913 			; <UNDEFINED> instruction: 0x46204913
d0017e30:	b0074479 	andlt	r4, r7, r9, ror r4
d0017e34:	8b02ecbd 	blhi	0xd00d3130
d0017e38:	4ff0e8bd 	svcmi	0x00f0e8bd
d0017e3c:	b9b4f7f8 	ldmiblt	r4!, {r3, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}
d0017e40:	fffffee0 			; <UNDEFINED> instruction: 0xfffffee0
d0017e44:	fffff85a 			; <UNDEFINED> instruction: 0xfffff85a
d0017e48:	fffff848 			; <UNDEFINED> instruction: 0xfffff848
d0017e4c:	fffffe9b 			; <UNDEFINED> instruction: 0xfffffe9b
d0017e50:	fffffe8a 			; <UNDEFINED> instruction: 0xfffffe8a
d0017e54:	ffffd102 			; <UNDEFINED> instruction: 0xffffd102
d0017e58:	ffffdddf 			; <UNDEFINED> instruction: 0xffffdddf
d0017e5c:	ffffdd9d 			; <UNDEFINED> instruction: 0xffffdd9d
d0017e60:	ffffdd87 			; <UNDEFINED> instruction: 0xffffdd87
d0017e64:	ffffdd2b 			; <UNDEFINED> instruction: 0xffffdd2b
d0017e68:	fffffc54 			; <UNDEFINED> instruction: 0xfffffc54
d0017e6c:	ffffdd07 			; <UNDEFINED> instruction: 0xffffdd07
d0017e70:	ffffdcb7 			; <UNDEFINED> instruction: 0xffffdcb7
d0017e74:	ffffdca1 			; <UNDEFINED> instruction: 0xffffdca1
d0017e78:	ffffdc93 			; <UNDEFINED> instruction: 0xffffdc93
d0017e7c:	fffffbda 			; <UNDEFINED> instruction: 0xfffffbda

Disassembly of section .text.struct_member:

d0017fb8 <.text.struct_member>:
d0017fb8:	4ff0e92d 	svcmi	0x00f0e92d
d0017fbc:	4bbf461d 	blmi	0xcefe9838
d0017fc0:	447b4604 	ldrbtmi	r4, [fp], #-1540	; 0xfffff9fc
d0017fc4:	8b02ed2d 	blhi	0xd00d3480
d0017fc8:	3a90ee08 	bcc	0xce4537f0
d0017fcc:	9103b087 	smlabbls	r3, r7, r0, fp
d0017fd0:	69a39204 	stmibvs	r3!, {r2, r9, ip, pc}
d0017fd4:	2a90ee18 	bcs	0xce45383c
d0017fd8:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d0017fdc:	ee084620 	cfmadd32	mvax1, mvfx4, mvfx8, mvfx0
d0017fe0:	69e33a10 	stmibvs	r3!, {r4, r9, fp, ip, sp}^
d0017fe4:	a024f8d4 	ldrdge	pc, [r4], -r4	; <UNPREDICTABLE>
d0017fe8:	f8d49301 			; <UNDEFINED> instruction: 0xf8d49301
d0017fec:	f8949028 			; <UNDEFINED> instruction: 0xf8949028
d0017ff0:	6b678030 	blvs	0xd19f80b8
d0017ff4:	ff27f7fa 			; <UNDEFINED> instruction: 0xff27f7fa
d0017ff8:	b9089b01 	stmdblt	r8, {r0, r8, r9, fp, ip, pc}
d0017ffc:	e02d2500 	eor	r2, sp, r0, lsl #10
d0018000:	f44f9a03 	vst1.8	{d25-d26}, [pc], r3
d0018004:	fb01711a 	blx	0xd0074476
d0018008:	f50bfb02 			; <UNDEFINED> instruction: 0xf50bfb02
d001800c:	44a332c8 	strtmi	r3, [r3], #712	; 0x2c8
d0018010:	f50b32c8 			; <UNDEFINED> instruction: 0xf50b32c8
d0018014:	92023bc9 	andls	r3, r2, #205824	; 0x32400
d0018018:	461618a2 	ldrmi	r1, [r6], -r2, lsr #17
d001801c:	92012200 	andls	r2, r1, #0, 4
d0018020:	210af89b 			; <UNDEFINED> instruction: 0x210af89b
d0018024:	428a9901 	addmi	r9, sl, #16384	; 0x4000
d0018028:	9b03d81e 	blls	0xd010e0a8
d001802c:	721af44f 	andsvc	pc, sl, #1325400064	; 0x4f000000
d0018030:	4103fb02 	tstmi	r3, r2, lsl #22	; <UNPREDICTABLE>
d0018034:	f5019a01 			; <UNDEFINED> instruction: 0xf5019a01
d0018038:	f89131c9 			; <UNDEFINED> instruction: 0xf89131c9
d001803c:	4293310a 	addsmi	r3, r3, #-2147483646	; 0x80000002
d0018040:	f891d124 			; <UNDEFINED> instruction: 0xf891d124
d0018044:	b9f3310b 	ldmiblt	r3!, {r0, r1, r3, r8, ip, sp}^
d0018048:	447b4b9d 	ldrbtmi	r4, [fp], #-2973	; 0xfffff463
d001804c:	2d006da5 	stccs	13, cr6, [r0, #-660]	; 0xfffffd6c
d0018050:	66a7d1d4 	ssatvs	sp, #8, r4, asr #3
d0018054:	3a16e9c4 	bcc	0xd05d276c
d0018058:	9818e9c4 	ldmdals	r8, {r2, r6, r7, r8, fp, sp, lr, pc}
d001805c:	b0074628 	andlt	r4, r7, r8, lsr #12
d0018060:	8b02ecbd 	blhi	0xd00d335c
d0018064:	8ff0e8bd 	svchi	0x00f0e8bd
d0018068:	ee186871 	mrc	8, 0, r6, cr8, cr1, {3}
d001806c:	f8562a10 			; <UNDEFINED> instruction: 0xf8562a10
d0018070:	93050b24 	movwls	r0, #23332	; 0x5b24
d0018074:	fad2f7f8 	blx	0xcf4d605c
d0018078:	28009b05 	stmdacs	r0, {r0, r2, r8, r9, fp, ip, pc}
d001807c:	9a01d1d5 	bls	0xd008c7d8
d0018080:	92013201 	andls	r3, r1, #268435456	; 0x10000000
d0018084:	4b8fe7cc 	blmi	0xce411fbc
d0018088:	e7df447b 			; <UNDEFINED> instruction: 0xe7df447b
d001808c:	9a022324 	bls	0xd00a0d24
d0018090:	fb039901 	blx	0xd00fe49e
d0018094:	19a32601 	stmibne	r3!, {r0, r9, sl, sp}
d0018098:	f8938c5a 			; <UNDEFINED> instruction: 0xf8938c5a
d001809c:	f8936020 			; <UNDEFINED> instruction: 0xf8936020
d00180a0:	b14ab021 	cmplt	sl, r1, lsr #32
d00180a4:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d00180a8:	f7fc0092 			; <UNDEFINED> instruction: 0xf7fc0092
d00180ac:	f44ffdd7 			; <UNDEFINED> instruction: 0xf44ffdd7
d00180b0:	462051c2 	strtmi	r5, [r0], -r2, asr #3
d00180b4:	fdb4f7fc 	ldc2	7, cr15, [r4, #1008]!	; 0x3f0
d00180b8:	0f00f1bb 	svceq	0x0000f1bb
d00180bc:	f44fd06c 	vst4.16	{d29-d32}, [pc :128], ip
d00180c0:	46207191 			; <UNDEFINED> instruction: 0x46207191
d00180c4:	feb1f7fa 	mrc2	7, 5, pc, cr1, cr10, {7}
d00180c8:	2effb170 	mrccs	1, 7, fp, cr15, cr0, {3}
d00180cc:	6da5d105 	stfvsd	f5, [r5, #20]!
d00180d0:	d1932d00 	orrsle	r2, r3, r0, lsl #26
d00180d4:	447b4b7c 	ldrbtmi	r4, [fp], #-2940	; 0xfffff484
d00180d8:	f44fe7bb 	vst1.32	{d30}, [pc :256], fp
d00180dc:	462041d0 			; <UNDEFINED> instruction: 0x462041d0
d00180e0:	fd9ef7fc 	ldc2	7, cr15, [lr, #1008]	; 0x3f0
d00180e4:	e7749603 	ldrb	r9, [r4, -r3, lsl #12]!
d00180e8:	2b2e6ae3 	blcs	0xd0bb2c7c
d00180ec:	6da3d10b 	stfvsd	f5, [r3, #44]!	; 0x2c
d00180f0:	2503b10b 	strcs	fp, [r3, #-267]	; 0xfffffef5
d00180f4:	4b75e7b2 	blmi	0xd1d91fc4
d00180f8:	66a7447b 	sxtabvs	r4, r7, fp, ror #8
d00180fc:	3a16e9c4 	bcc	0xd05d2814
d0018100:	9818e9c4 	ldmdals	r8, {r2, r6, r7, r8, fp, sp, lr, pc}
d0018104:	b12de7f5 	strdlt	lr, [sp, -r5]!
d0018108:	2b006da3 	blcs	0xd003379c
d001810c:	4b70d1f1 	blmi	0xd1c4c8d8
d0018110:	e7f2447b 			; <UNDEFINED> instruction: 0xe7f2447b
d0018114:	b1f39b04 	mvnslt	r9, r4, lsl #22
d0018118:	4620213d 			; <UNDEFINED> instruction: 0x4620213d
d001811c:	fe85f7fa 	mcr2	7, 4, pc, cr5, cr10, {7}	; <UNPREDICTABLE>
d0018120:	f24bb1c8 	vrhadd.s8	<illegal reg q13.5>, <illegal reg q13.5>, q4
d0018124:	46204103 	strtmi	r4, [r0], -r3, lsl #2
d0018128:	fd7af7fc 	ldc2l	7, cr15, [sl, #-1008]!	; 0xfffffc10
d001812c:	d10e2eff 	strdle	r2, [lr, -pc]
d0018130:	21012204 	tstcs	r1, r4, lsl #4
d0018134:	f866f7fe 			; <UNDEFINED> instruction: 0xf866f7fe
d0018138:	4106f64b 	tstmi	r6, fp, asr #12	; <UNPREDICTABLE>
d001813c:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0018140:	f246fd6f 	vadd.f32	<illegal reg q15.5>, q3, <illegal reg q15.5>
d0018144:	25020108 	strcs	r0, [r2, #-264]	; 0xfffffef8
d0018148:	fd6af7fc 	stc2l	7, cr15, [sl, #-1008]!	; 0xfffffc10
d001814c:	4631e786 	ldrtmi	lr, [r1], -r6, lsl #15
d0018150:	fc7af7ff 	ldc2l	7, cr15, [sl], #-1020	; 0xfffffc04
d0018154:	6ae3e7f0 	bvs	0xcf91211c
d0018158:	7592f46f 	ldrvc	pc, [r2, #1135]	; 0x46f
d001815c:	2a01195a 	bcs	0xd005e6cc
d0018160:	f46fd904 	vld2.8	{d29,d31}, [pc], r4
d0018164:	44037094 	strmi	r7, [r3], #-148	; 0xffffff6c
d0018168:	d8082b04 	stmdale	r8, {r2, r8, r9, fp, sp}
d001816c:	b9336da3 	ldmdblt	r3!, {r0, r1, r5, r7, r8, sl, fp, sp, lr}
d0018170:	66a74b58 	ssatvs	r4, #8, r8, asr #22
d0018174:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0018178:	e9c49818 	stmib	r4, {r3, r4, fp, ip, pc}^
d001817c:	46203a16 			; <UNDEFINED> instruction: 0x46203a16
d0018180:	41d0f44f 	bicsmi	pc, r0, pc, asr #8
d0018184:	fd4cf7fc 	stc2l	7, cr15, [ip, #-1008]	; 0xfffffc10
d0018188:	3425f504 	strtcc	pc, [r5], #-1284	; 0xfffffafc
d001818c:	f8c42eff 			; <UNDEFINED> instruction: 0xf8c42eff
d0018190:	d1ae6124 			; <UNDEFINED> instruction: 0xd1ae6124
d0018194:	e7612504 	strb	r2, [r1, -r4, lsl #10]!
d0018198:	d00d2eff 	strdle	r2, [sp], -pc	; <UNPREDICTABLE>
d001819c:	4620212e 	strtmi	r2, [r0], -lr, lsr #2
d00181a0:	fe43f7fa 	mcr2	7, 2, pc, cr3, cr10, {7}	; <UNPREDICTABLE>
d00181a4:	d19d2800 	orrsle	r2, sp, r0, lsl #16
d00181a8:	d1a22d00 			; <UNDEFINED> instruction: 0xd1a22d00
d00181ac:	2b006da3 	blcs	0xd0033840
d00181b0:	4b49d19f 	blmi	0xd128c834
d00181b4:	e7a0447b 			; <UNDEFINED> instruction: 0xe7a0447b
d00181b8:	2e2e6ae6 	vnmulcs.f32	s12, s29, s13
d00181bc:	f5b6d002 			; <UNDEFINED> instruction: 0xf5b6d002
d00181c0:	d1057f91 			; <UNDEFINED> instruction: 0xd1057f91
d00181c4:	46204945 	strtmi	r4, [r0], -r5, asr #18
d00181c8:	f7f74479 			; <UNDEFINED> instruction: 0xf7f74479
d00181cc:	e715ffed 	ldr	pc, [r5, -sp, ror #31]
d00181d0:	d1df2d00 	bicsle	r2, pc, r0, lsl #26
d00181d4:	2b009b04 	blcs	0xd003edec
d00181d8:	2e3dd069 	cdpcs	0, 3, cr13, cr13, cr9, {3}
d00181dc:	f46fd009 	vld4.8	{d29-d32}, [pc], r9
d00181e0:	18737192 	ldmdane	r3!, {r1, r4, r7, r8, ip, sp, lr}^
d00181e4:	d9042b01 	stmdble	r4, {r0, r8, r9, fp, sp}
d00181e8:	7294f46f 	addsvc	pc, r4, #1862270976	; 0x6f000000
d00181ec:	2b0418b3 	blcs	0xd011e4c0
d00181f0:	4620d85d 			; <UNDEFINED> instruction: 0x4620d85d
d00181f4:	fdfef7fa 	ldc2l	7, cr15, [lr, #1000]!	; 0x3e8
d00181f8:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d00181fc:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0018200:	2e3dfd0f 	cdpcs	13, 3, cr15, cr13, cr15, {0}
d0018204:	f44fd007 	vst4.8	{d29-d32}, [pc], r7
d0018208:	f7fc41d0 			; <UNDEFINED> instruction: 0xf7fc41d0
d001820c:	f24bfd09 	vadd.f32	d31, d11, d9
d0018210:	f7fc4103 			; <UNDEFINED> instruction: 0xf7fc4103
d0018214:	2201fd05 	andcs	pc, r1, #320	; 0x140
d0018218:	46114620 	ldrmi	r4, [r1], -r0, lsr #12
d001821c:	fff2f7fd 			; <UNDEFINED> instruction: 0xfff2f7fd
d0018220:	d0892e3d 	addle	r2, r9, sp, lsr lr
d0018224:	4106f64b 	tstmi	r6, fp, asr #12	; <UNPREDICTABLE>
d0018228:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d001822c:	f46ffcf9 			; <UNDEFINED> instruction: 0xf46ffcf9
d0018230:	18f37392 	ldmne	r3!, {r1, r4, r7, r8, r9, ip, sp, lr}^
d0018234:	f63f2b08 			; <UNDEFINED> instruction: 0xf63f2b08
d0018238:	a202af7f 	andge	sl, r2, #508	; 0x1fc
d001823c:	3023f852 	eorcc	pc, r3, r2, asr r8	; <UNPREDICTABLE>
d0018240:	4710441a 			; <UNDEFINED> instruction: 0x4710441a
d0018244:	00000025 	andeq	r0, r0, r5, lsr #32
d0018248:	00000031 	andeq	r0, r0, r1, lsr r0
d001824c:	fffffef5 			; <UNDEFINED> instruction: 0xfffffef5
d0018250:	fffffef5 			; <UNDEFINED> instruction: 0xfffffef5
d0018254:	00000037 	andeq	r0, r0, r7, lsr r0
d0018258:	0000003d 	andeq	r0, r0, sp, lsr r0
d001825c:	00000043 	andeq	r0, r0, r3, asr #32
d0018260:	00000049 	andeq	r0, r0, r9, asr #32
d0018264:	00000049 	andeq	r0, r0, r9, asr #32
d0018268:	0108f641 	tsteq	r8, r1, asr #12	; <UNPREDICTABLE>
d001826c:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0018270:	e761fcd7 			; <UNDEFINED> instruction: 0xe761fcd7
d0018274:	2108f641 	tstcs	r8, r1, asr #12	; <UNPREDICTABLE>
d0018278:	f244e7f8 	vaba.s8	q15, q10, q12
d001827c:	e7f50108 	ldrb	r0, [r5, r8, lsl #2]!
d0018280:	3108f244 	tstcc	r8, r4, asr #4	; <UNPREDICTABLE>
d0018284:	f244e7f2 	vaba.s8	q15, q10, q9
d0018288:	e7ef0148 	strb	r0, [pc, r8, asr #2]!
d001828c:	6102f244 	tstvs	r2, r4, asr #4	; <UNPREDICTABLE>
d0018290:	fcc6f7fc 	stc2l	7, cr15, [r6], {252}	; 0xfc
d0018294:	6108f244 	tstvs	r8, r4, asr #4	; <UNPREDICTABLE>
d0018298:	fcc2f7fc 	stc2l	7, cr15, [r2], {252}	; 0xfc
d001829c:	0190f244 	orrseq	pc, r0, r4, asr #4
d00182a0:	1310f244 	tstne	r0, #68, 4	; 0x40000004	; <UNPREDICTABLE>
d00182a4:	7f96f5b6 	svcvc	0x0096f5b6
d00182a8:	4619bf18 	sadd16mi	fp, r9, r8
d00182ac:	f44fe7de 	vst1.64	{d30}, [pc :64], lr
d00182b0:	462041d0 			; <UNDEFINED> instruction: 0x462041d0
d00182b4:	fcb4f7fc 	ldc2	7, cr15, [r4], #1008	; 0x3f0
d00182b8:	bf00e6d0 	svclt	0x0000e6d0
d00182bc:	fffffee3 			; <UNDEFINED> instruction: 0xfffffee3
d00182c0:	fffffe46 			; <UNDEFINED> instruction: 0xfffffe46
d00182c4:	fffffdf4 			; <UNDEFINED> instruction: 0xfffffdf4
d00182c8:	fffffdeb 			; <UNDEFINED> instruction: 0xfffffdeb
d00182cc:	fffffdeb 			; <UNDEFINED> instruction: 0xfffffdeb
d00182d0:	fffffdf4 			; <UNDEFINED> instruction: 0xfffffdf4
d00182d4:	fffffdc6 			; <UNDEFINED> instruction: 0xfffffdc6
d00182d8:	fffffdab 			; <UNDEFINED> instruction: 0xfffffdab
d00182dc:	fffffdbf 			; <UNDEFINED> instruction: 0xfffffdbf

Disassembly of section .text.unary:

d0018648 <.text.unary>:
d0018648:	4ff0e92d 	svcmi	0x00f0e92d
d001864c:	b058f8d0 	ldrsblt	pc, [r8], #-128	; 0xffffff80	; <UNPREDICTABLE>
d0018650:	460e4604 	strmi	r4, [lr], -r4, lsl #12
d0018654:	8b02ed2d 	blhi	0xd00d3b10
d0018658:	f1bbb09d 			; <UNDEFINED> instruction: 0xf1bbb09d
d001865c:	f0400f00 			; <UNDEFINED> instruction: 0xf0400f00
d0018660:	6a83851c 	bvs	0xce0f9ad8
d0018664:	93076ac7 	movwls	r6, #31431	; 0x7ac7
d0018668:	3030f890 	mlascc	r0, r0, r8, pc	; <UNPREDICTABLE>
d001866c:	6b439308 	blvs	0xd10fd294
d0018670:	f5009306 			; <UNDEFINED> instruction: 0xf5009306
d0018674:	f8d33325 			; <UNDEFINED> instruction: 0xf8d33325
d0018678:	93092120 	movwls	r2, #37152	; 0x9120
d001867c:	2a203201 	bcs	0xd0824e88
d0018680:	9a06e9d0 	bls	0xd01d2dc8
d0018684:	5808e9d0 	stmdapl	r8, {r4, r6, r7, r8, fp, sp, lr, pc}
d0018688:	2120f8c3 	smlawtcs	r0, r3, r8, pc	; <UNPREDICTABLE>
d001868c:	f8dfd906 			; <UNDEFINED> instruction: 0xf8dfd906
d0018690:	44791b0c 	ldrbtmi	r1, [r9], #-2828	; 0xfffff4f4
d0018694:	fd88f7f7 	stc2	7, cr15, [r8, #988]	; 0x3dc
d0018698:	e0d12500 	sbcs	r2, r1, r0, lsl #10
d001869c:	718df44f 	orrvc	pc, sp, pc, asr #8
d00186a0:	fbc3f7fa 	blx	0xcf116692
d00186a4:	4620b140 	strtmi	fp, [r0], -r0, asr #2
d00186a8:	f95cf7fb 			; <UNDEFINED> instruction: 0xf95cf7fb
d00186ac:	46204601 	strtmi	r4, [r0], -r1, lsl #12
d00186b0:	fb12f7fc 	blx	0xd04d66aa
d00186b4:	e0c32501 	sbc	r2, r3, r1, lsl #10
d00186b8:	7181f44f 	orrvc	pc, r1, pc, asr #8
d00186bc:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d00186c0:	b150fbb4 	ldrhlt	pc, [r0, #-180]	; 0xffffff4c	; <UNPREDICTABLE>
d00186c4:	46294620 	strtmi	r4, [r9], -r0, lsr #12
d00186c8:	fb06f7fc 	blx	0xd01d66c2
d00186cc:	1003f240 	andne	pc, r3, r0, asr #4
d00186d0:	bf144287 	svclt	0x00144287
d00186d4:	25012500 	strcs	r2, [r1, #-1280]	; 0xfffffb00
d00186d8:	f240e0b2 	vqadd.s8	d30, d16, d18
d00186dc:	46201103 	strtmi	r1, [r0], -r3, lsl #2
d00186e0:	fba3f7fa 	blx	0xce9166d2
d00186e4:	d1ed2800 	mvnle	r2, r0, lsl #16
d00186e8:	1123f240 	msrne	R11_usr, r0
d00186ec:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d00186f0:	b308fb9c 	movwlt	pc, #35740	; 0x8b9c	; <UNPREDICTABLE>
d00186f4:	2aa8f8df 	bcs	0xcea56a78
d00186f8:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d00186fc:	46206a63 	strtmi	r6, [r0], -r3, ror #20
d0018700:	f8d4447a 			; <UNDEFINED> instruction: 0xf8d4447a
d0018704:	f8948028 			; <UNDEFINED> instruction: 0xf8948028
d0018708:	f8d49030 			; <UNDEFINED> instruction: 0xf8d49030
d001870c:	9306a034 	movwls	sl, #24628	; 0x6034
d0018710:	5606e9d4 			; <UNDEFINED> instruction: 0x5606e9d4
d0018714:	fb97f7fa 	blx	0xce616706
d0018718:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d001871c:	2200831c 	andcs	r8, r0, #28, 6	; 0x70000000
d0018720:	46299b06 	strtmi	r9, [r9], -r6, lsl #22
d0018724:	92049703 	andls	r9, r4, #786432	; 0xc0000
d0018728:	e88d4632 	stm	sp, {r1, r4, r5, r9, sl, lr}
d001872c:	46200700 	strtmi	r0, [r0], -r0, lsl #14
d0018730:	f820f7fd 			; <UNDEFINED> instruction: 0xf820f7fd
d0018734:	e0834605 	add	r4, r3, r5, lsl #12
d0018738:	7192f44f 	orrsvc	pc, r2, pc, asr #8
d001873c:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0018740:	4683fb74 			; <UNDEFINED> instruction: 0x4683fb74
d0018744:	d1d52800 	bicsle	r2, r5, r0, lsl #16
d0018748:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d001874c:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0018750:	4605fb6c 	strmi	pc, [r5], -ip, ror #22
d0018754:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d0018758:	f8df82e5 			; <UNDEFINED> instruction: 0xf8df82e5
d001875c:	46512a48 	ldrbmi	r2, [r1], -r8, asr #20
d0018760:	447a4648 	ldrbtmi	r4, [sl], #-1608	; 0xfffff9b8
d0018764:	f87df7f8 			; <UNDEFINED> instruction: 0xf87df7f8
d0018768:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d001876c:	6ae380a2 	bvs	0xcf8f89fc
d0018770:	f0402b2e 			; <UNDEFINED> instruction: 0xf0402b2e
d0018774:	f8df809e 			; <UNDEFINED> instruction: 0xf8df809e
d0018778:	25039a30 	strcs	r9, [r3, #-2608]	; 0xfffff5d0
d001877c:	1a2cf8df 	bne	0xd0b56b00
d0018780:	44f92203 	ldrbtmi	r2, [r9], #515	; 0x203
d0018784:	4479a80c 	ldrbtmi	sl, [r9], #-2060	; 0xfffff7f4
d0018788:	fe3af006 	cdp2	0, 3, cr15, cr10, cr6, {0}
d001878c:	2f2e6ae7 	svccs	0x002e6ae7
d0018790:	f5b7d002 			; <UNDEFINED> instruction: 0xf5b7d002
d0018794:	d12c7f91 			; <UNDEFINED> instruction: 0xd12c7f91
d0018798:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d001879c:	69a3fb2b 	stmibvs	r3!, {r0, r1, r3, r5, r8, r9, fp, ip, sp, lr, pc}
d00187a0:	f240464a 	vmax.s8	q10, q0, q5
d00187a4:	ee081101 	adfe	f1, f0, f1
d00187a8:	6a633a10 	bvs	0xd18e6ff0
d00187ac:	f8d44620 			; <UNDEFINED> instruction: 0xf8d44620
d00187b0:	930ba01c 	movwls	sl, #45084	; 0xb01c
d00187b4:	6b666aa3 	blvs	0xd19b3248
d00187b8:	f8949309 			; <UNDEFINED> instruction: 0xf8949309
d00187bc:	930a3030 	movwls	r3, #41008	; 0xa030
d00187c0:	fb41f7fa 	blx	0xd10967b2
d00187c4:	2f2eb1a8 	svccs	0x002eb1a8
d00187c8:	020aeb05 	andeq	lr, sl, #5120	; 0x1400
d00187cc:	bf0c9b0b 	svclt	0x000c9b0b
d00187d0:	21022101 	tstcs	r2, r1, lsl #2
d00187d4:	2a3f440a 	bcs	0xd0fe9804
d00187d8:	6da2d93b 			; <UNDEFINED> instruction: 0x6da2d93b
d00187dc:	f8dfb94a 			; <UNDEFINED> instruction: 0xf8dfb94a
d00187e0:	66a629d0 	ssatvs	r2, #7, r0, asr #19
d00187e4:	e9c4447a 	stmib	r4, {r1, r3, r4, r5, r6, sl, lr}^
d00187e8:	9b092316 	blls	0xd0261448
d00187ec:	9b0a6623 	blls	0xd02b2080
d00187f0:	ab1c6663 	blge	0xd0732184
d00187f4:	442b2200 	strtmi	r2, [fp], #-512	; 0xfffffe00
d00187f8:	2c40f803 	mcrrcs	8, 0, pc, r0, cr3	; <UNPREDICTABLE>
d00187fc:	b9f36da3 	ldmiblt	r3!, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0018800:	29b0f8df 	ldmibcs	r0!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d0018804:	46202128 	strtmi	r2, [r0], -r8, lsr #2
d0018808:	f7fa447a 			; <UNDEFINED> instruction: 0xf7fa447a
d001880c:	b1b0fb1c 	lslslt	pc, ip, fp	; <UNPREDICTABLE>
d0018810:	a90c462a 	stmdbge	ip, {r1, r3, r5, r9, sl, lr}
d0018814:	f7f84620 			; <UNDEFINED> instruction: 0xf7f84620
d0018818:	4605f839 			; <UNDEFINED> instruction: 0x4605f839
d001881c:	d0362800 	eorsle	r2, r6, r0, lsl #16
d0018820:	46204601 	strtmi	r4, [r0], -r1, lsl #12
d0018824:	f8f8f7fe 			; <UNDEFINED> instruction: 0xf8f8f7fe
d0018828:	b047f895 	umaallt	pc, r7, r5, r8	; <UNPREDICTABLE>
d001882c:	0f07f1bb 	svceq	0x0007f1bb
d0018830:	f1abd03c 			; <UNDEFINED> instruction: 0xf1abd03c
d0018834:	f1d50505 			; <UNDEFINED> instruction: 0xf1d50505
d0018838:	eb4b0b00 	bl	0xd12db440
d001883c:	465d0b05 	ldrbmi	r0, [sp], -r5, lsl #22
d0018840:	3425f504 	strtcc	pc, [r5], #-1284	; 0xfffffafc
d0018844:	f8d44628 			; <UNDEFINED> instruction: 0xf8d44628
d0018848:	3b013120 	blcc	0xd0064cd0
d001884c:	3120f8c4 	smlawtcc	r0, r4, r8, pc	; <UNPREDICTABLE>
d0018850:	2f2ee288 	svccs	0x002ee288
d0018854:	f105ab1c 			; <UNDEFINED> instruction: 0xf105ab1c
d0018858:	a80c0601 	stmdage	ip, {r0, r9, sl}
d001885c:	bf18442b 	svclt	0x0018442b
d0018860:	ee18222d 	cdp	2, 1, cr2, cr8, cr13, {1}
d0018864:	bf1c1a10 	svclt	0x001c1a10
d0018868:	2c40f803 	mcrrcs	8, 0, pc, r0, cr3	; <UNPREDICTABLE>
d001886c:	4652ab1c 			; <UNDEFINED> instruction: 0x4652ab1c
d0018870:	f803bf0f 			; <UNDEFINED> instruction: 0xf803bf0f
d0018874:	18f67c40 	ldmne	r6!, {r6, sl, fp, ip, sp, lr}^
d0018878:	f806233e 			; <UNDEFINED> instruction: 0xf806233e
d001887c:	bf183c40 	svclt	0x00183c40
d0018880:	44301cae 	ldrtmi	r1, [r0], #-3246	; 0xfffff352
d0018884:	050aeb06 	streq	lr, [sl, #-2822]	; 0xfffff4fa
d0018888:	fdbaf006 	ldc2	0, cr15, [sl, #24]!
d001888c:	6da3e77e 	stcvs	7, cr14, [r3, #504]!	; 0x1f8
d0018890:	d1d42b00 	bicsle	r2, r4, r0, lsl #22
d0018894:	3920f8df 	stmdbcc	r0!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d0018898:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d001889c:	9b073816 	blls	0xd01e68fc
d00188a0:	9b086623 	blls	0xd0232134
d00188a4:	9b066663 	blls	0xd01b2238
d00188a8:	e7c866a3 	strb	r6, [r8, r3, lsr #13]
d00188ac:	0b02f04f 	bleq	0xd00d49f0
d00188b0:	2128e7c5 	smlawtcs	r8, r5, r7, lr
d00188b4:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d00188b8:	4605fab8 			; <UNDEFINED> instruction: 0x4605fab8
d00188bc:	4649b318 			; <UNDEFINED> instruction: 0x4649b318
d00188c0:	46204652 			; <UNDEFINED> instruction: 0x46204652
d00188c4:	ff1ef7f7 			; <UNDEFINED> instruction: 0xff1ef7f7
d00188c8:	db0f1e01 	blle	0xd03e00d4
d00188cc:	fb032330 	blx	0xd00e1596
d00188d0:	f5034301 			; <UNDEFINED> instruction: 0xf5034301
d00188d4:	f8933322 			; <UNDEFINED> instruction: 0xf8933322
d00188d8:	2b0c3135 	blcs	0xd0324db4
d00188dc:	4620d106 	strtmi	sp, [r0], -r6, lsl #2
d00188e0:	faeef7fe 	blx	0xcfbd68e0
d00188e4:	2d044605 	stccs	6, cr4, [r4, #-20]	; 0xffffffec
d00188e8:	e0d8d1aa 	sbcs	sp, r8, sl, lsr #3
d00188ec:	46529b06 	ldrbmi	r9, [r2], -r6, lsl #22
d00188f0:	46204649 	strtmi	r4, [r0], -r9, asr #12
d00188f4:	9b089302 	blls	0xd023d504
d00188f8:	9b079301 	blls	0xd01fd504
d00188fc:	46439300 	strbmi	r9, [r3], -r0, lsl #6
d0018900:	fdc6f7fe 	stc2l	7, cr15, [r6, #1016]	; 0x3f8
d0018904:	6ae7e7ee 	bvs	0xcfa128c4
d0018908:	7091f46f 	addsvc	pc, r1, pc, ror #8
d001890c:	2b01183b 	blcs	0xd005ea00
d0018910:	4620d80f 	strtmi	sp, [r0], -pc, lsl #16
d0018914:	fa6ef7fa 	blx	0xd1bd6904
d0018918:	46522301 	ldrbmi	r2, [r2], -r1, lsl #6
d001891c:	93044649 	movwls	r4, #17993	; 0x4649
d0018920:	97039b06 	strls	r9, [r3, -r6, lsl #22]
d0018924:	9b089302 	blls	0xd023d534
d0018928:	9b079301 	blls	0xd01fd534
d001892c:	46439300 	strbmi	r9, [r3], -r0, lsl #6
d0018930:	4652e6fd 			; <UNDEFINED> instruction: 0x4652e6fd
d0018934:	46204649 	strtmi	r4, [r0], -r9, asr #12
d0018938:	fee4f7f7 	mcr2	7, 7, pc, cr4, cr7, {7}	; <UNPREDICTABLE>
d001893c:	46074652 			; <UNDEFINED> instruction: 0x46074652
d0018940:	46204649 	strtmi	r4, [r0], -r9, asr #12
d0018944:	ffc0f7f7 			; <UNDEFINED> instruction: 0xffc0f7f7
d0018948:	b1204683 	smlawblt	r0, r3, r6, r4
d001894c:	46206a01 	strtmi	r6, [r0], -r1, lsl #20
d0018950:	f9c2f7fc 			; <UNDEFINED> instruction: 0xf9c2f7fc
d0018954:	2f00e774 	svccs	0x0000e774
d0018958:	810af2c0 	smlabthi	sl, r0, r2, pc	; <UNPREDICTABLE>
d001895c:	0a30f04f 	beq	0xd0c54aa0
d0018960:	4a07fb0a 	bmi	0xd0217590
d0018964:	3a22f50a 	bcc	0xd08d5d94
d0018968:	9135f89a 	teqls	r5, sl	; <illegal shifter operand>	; <UNPREDICTABLE>
d001896c:	0f02f1b9 	svceq	0x0002f1b9
d0018970:	f1b9d002 			; <UNDEFINED> instruction: 0xf1b9d002
d0018974:	d10e0f04 	tstle	lr, r4, lsl #30
d0018978:	2b006da3 	blcs	0xd003400c
d001897c:	ae8cf47f 	mcrge	4, 4, pc, cr12, cr15, {3}	; <UNPREDICTABLE>
d0018980:	3838f8df 	ldmdacc	r8!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d0018984:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0018988:	9b073816 	blls	0xd01e69e8
d001898c:	9b086623 	blls	0xd0232220
d0018990:	9b066663 	blls	0xd01b2324
d0018994:	f1b9e0e4 			; <UNDEFINED> instruction: 0xf1b9e0e4
d0018998:	d1060f0c 	tstle	r6, ip, lsl #30
d001899c:	4639462a 	ldrtmi	r4, [r9], -sl, lsr #12
d00189a0:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d00189a4:	2503f9d3 	strcs	pc, [r3, #-2515]	; 0xfffff62d
d00189a8:	f1b9e74a 			; <UNDEFINED> instruction: 0xf1b9e74a
d00189ac:	d1060f13 	tstle	r6, r3, lsl pc
d00189b0:	4639462a 	ldrtmi	r4, [r9], -sl, lsr #12
d00189b4:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d00189b8:	2507f9c9 	strcs	pc, [r7, #-2505]	; 0xfffff637
d00189bc:	f1b9e740 			; <UNDEFINED> instruction: 0xf1b9e740
d00189c0:	d10b0f12 	tstle	fp, r2, lsl pc
d00189c4:	4639462a 	ldrtmi	r4, [r9], -sl, lsr #12
d00189c8:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d00189cc:	f89af9bf 			; <UNDEFINED> instruction: 0xf89af9bf
d00189d0:	9a093136 	bls	0xd0264eb0
d00189d4:	f8c22505 			; <UNDEFINED> instruction: 0xf8c22505
d00189d8:	e7313124 	ldr	r3, [r1, -r4, lsr #2]!
d00189dc:	030df1a9 	movweq	pc, #53673	; 0xd1a9	; <UNPREDICTABLE>
d00189e0:	d83c2b01 	ldmdale	ip!, {r0, r8, r9, fp, sp}
d00189e4:	0f0df1b9 	svceq	0x000df1b9
d00189e8:	4639d11e 			; <UNDEFINED> instruction: 0x4639d11e
d00189ec:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d00189f0:	212ef9df 	ldrdcs	pc, [lr, -pc]!	; <UNPREDICTABLE>
d00189f4:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d00189f8:	4605fa18 			; <UNDEFINED> instruction: 0x4605fa18
d00189fc:	2030b160 	eorscs	fp, r0, r0, ror #2
d0018a00:	46322300 	ldrtmi	r2, [r2], -r0, lsl #6
d0018a04:	4707fb00 	strmi	pc, [r7, -r0, lsl #22]
d0018a08:	3722f507 	strcc	pc, [r2, -r7, lsl #10]!
d0018a0c:	1136f897 	teqne	r6, r7	; <illegal shifter operand>	; <UNPREDICTABLE>
d0018a10:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0018a14:	e68dfad1 	pkhtb	pc, sp, r1, asr #21	; <UNPREDICTABLE>
d0018a18:	2b006da3 	blcs	0xd00340ac
d0018a1c:	ae3cf47f 	mrcge	4, 1, APSR_nzcv, cr12, cr15, {3}
d0018a20:	379cf8df 			; <UNDEFINED> instruction: 0x379cf8df
d0018a24:	e7ae447b 			; <UNDEFINED> instruction: 0xe7ae447b
d0018a28:	46392200 	ldrtmi	r2, [r9], -r0, lsl #4
d0018a2c:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0018a30:	f44ff98d 	vst2.32	{d31,d33}, [pc]!
d0018a34:	f7fa7191 			; <UNDEFINED> instruction: 0xf7fa7191
d0018a38:	4603f9f8 			; <UNDEFINED> instruction: 0x4603f9f8
d0018a3c:	d1de2800 	bicsle	r2, lr, r0, lsl #16
d0018a40:	2a5b6ae2 	bcs	0xd16f35d0
d0018a44:	2230d1af 	eorscs	sp, r0, #-1073741781	; 0xc000002b
d0018a48:	4707fb02 	strmi	pc, [r7, -r2, lsl #22]
d0018a4c:	3722f507 	strcc	pc, [r2, -r7, lsl #10]!
d0018a50:	f8974632 			; <UNDEFINED> instruction: 0xf8974632
d0018a54:	46201136 			; <UNDEFINED> instruction: 0x46201136
d0018a58:	fac8f7fe 	blx	0xcf256a58
d0018a5c:	f1b9e66a 			; <UNDEFINED> instruction: 0xf1b9e66a
d0018a60:	d1150f10 	tstle	r5, r0, lsl pc
d0018a64:	46204639 			; <UNDEFINED> instruction: 0x46204639
d0018a68:	f9a2f7fc 			; <UNDEFINED> instruction: 0xf9a2f7fc
d0018a6c:	2b5b6ae3 	blcs	0xd16f3600
d0018a70:	2030d106 	eorscs	sp, r0, r6, lsl #2
d0018a74:	fb002300 	blx	0xd002167e
d0018a78:	f5074707 			; <UNDEFINED> instruction: 0xf5074707
d0018a7c:	e7e73722 	strb	r3, [r7, r2, lsr #14]!
d0018a80:	2b006da3 	blcs	0xd0034114
d0018a84:	ae08f47f 	mcrge	4, 0, pc, cr8, cr15, {3}	; <UNPREDICTABLE>
d0018a88:	3738f8df 			; <UNDEFINED> instruction: 0x3738f8df
d0018a8c:	e77a447b 			; <UNDEFINED> instruction: 0xe77a447b
d0018a90:	0f09f1b9 	svceq	0x0009f1b9
d0018a94:	4639d10a 	ldrtmi	sp, [r9], -sl, lsl #2
d0018a98:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0018a9c:	6ae3f989 	bvs	0xcf9170c8
d0018aa0:	f0402b5b 			; <UNDEFINED> instruction: 0xf0402b5b
d0018aa4:	2200820e 	andcs	r8, r0, #-536870912	; 0xe0000000
d0018aa8:	e1b04631 	lsrs	r4, r1, r6
d0018aac:	46392200 	ldrtmi	r2, [r9], -r0, lsl #4
d0018ab0:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0018ab4:	f1b9f94b 			; <UNDEFINED> instruction: 0xf1b9f94b
d0018ab8:	d1530f06 	cmple	r3, r6, lsl #30
d0018abc:	7191f44f 	orrsvc	pc, r1, pc, asr #8
d0018ac0:	f9b3f7fa 			; <UNDEFINED> instruction: 0xf9b3f7fa
d0018ac4:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0018ac8:	6aa3af6e 	bvs	0xce904888
d0018acc:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d0018ad0:	26f4f8df 	usatcs	pc, #20, pc, asr #17	; <UNPREDICTABLE>
d0018ad4:	93064620 	movwls	r4, #26144	; 0x6620
d0018ad8:	447a6b63 	ldrbtmi	r6, [sl], #-2915	; 0xfffff49d
d0018adc:	9024f8d4 	ldrdls	pc, [r4], -r4	; <UNPREDICTABLE>
d0018ae0:	7030f894 	mlasvc	r0, r4, r8, pc	; <UNPREDICTABLE>
d0018ae4:	e9d49307 	ldmib	r4, {r0, r1, r2, r8, r9, ip, pc}^
d0018ae8:	f7faab06 			; <UNDEFINED> instruction: 0xf7faab06
d0018aec:	2800f9ac 	stmdacs	r0, {r2, r3, r5, r7, r8, fp, ip, sp, lr, pc}
d0018af0:	add2f43f 	cfldrdge	mvd15, [r2, #252]	; 0xfc
d0018af4:	86d4f8df 			; <UNDEFINED> instruction: 0x86d4f8df
d0018af8:	44f82600 	ldrbtmi	r2, [r8], #1536	; 0x600
d0018afc:	2b04f858 	blcs	0xd0156c64
d0018b00:	46504659 			; <UNDEFINED> instruction: 0x46504659
d0018b04:	feadf7f7 	mcr2	7, 5, pc, cr13, cr7, {7}	; <UNPREDICTABLE>
d0018b08:	b1c84605 	biclt	r4, r8, r5, lsl #12
d0018b0c:	03d0f64f 	bicseq	pc, r0, #82837504	; 0x4f00000
d0018b10:	0190f64f 	orrseq	pc, r0, pc, asr #12
d0018b14:	2e014620 	cfmadd32cs	mvax1, mvfx4, mvfx1, mvfx0
d0018b18:	4619bf18 	sadd16mi	fp, r9, r8
d0018b1c:	f880f7fc 			; <UNDEFINED> instruction: 0xf880f7fc
d0018b20:	43f4f506 	mvnsmi	pc, #25165824	; 0x1800000
d0018b24:	eb043340 	bl	0xd012582c
d0018b28:	88990343 	ldmhi	r9, {r0, r1, r6, r8, r9}
d0018b2c:	f878f7fc 			; <UNDEFINED> instruction: 0xf878f7fc
d0018b30:	f43f2e00 			; <UNDEFINED> instruction: 0xf43f2e00
d0018b34:	3e02adbf 	mcrcc	13, 0, sl, cr2, cr15, {5}
d0018b38:	f63f2e01 			; <UNDEFINED> instruction: 0xf63f2e01
d0018b3c:	e5b9adad 	ldr	sl, [r9, #3501]!	; 0xdad
d0018b40:	2e083601 	cfmadd32cs	mvax0, mvfx3, mvfx8, mvfx1
d0018b44:	6da3d1da 	stfvsd	f5, [r3, #872]!	; 0x368
d0018b48:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0018b4c:	f8dfada5 			; <UNDEFINED> instruction: 0xf8dfada5
d0018b50:	447b3680 	ldrbtmi	r3, [fp], #-1664	; 0xfffff980
d0018b54:	3916e9c4 	ldmdbcc	r6, {r2, r6, r7, r8, fp, sp, lr, pc}
d0018b58:	e9c49b06 	stmib	r4, {r1, r2, r8, r9, fp, ip, pc}^
d0018b5c:	9b073718 	blls	0xd01e67c4
d0018b60:	e66d66a3 	strbt	r6, [sp], -r3, lsr #13
d0018b64:	0f0af1b9 	svceq	0x000af1b9
d0018b68:	f1b9d099 			; <UNDEFINED> instruction: 0xf1b9d099
d0018b6c:	e5b00f01 	ldr	r0, [r0, #3841]!	; 0xf01
d0018b70:	46494652 			; <UNDEFINED> instruction: 0x46494652
d0018b74:	f7f74620 			; <UNDEFINED> instruction: 0xf7f74620
d0018b78:	1e07fde4 	cdpne	13, 0, cr15, cr7, cr4, {7}
d0018b7c:	80bcf2c0 	adcshi	pc, ip, r0, asr #5
d0018b80:	0938f04f 	ldmdbeq	r8!, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d0018b84:	4907fb09 	stmdbmi	r7, {r0, r3, r8, r9, fp, ip, sp, lr, pc}
d0018b88:	39baf509 	ldmibcc	sl!, {r0, r3, r8, sl, ip, sp, lr, pc}
d0018b8c:	a0ccf899 	smullge	pc, ip, r9, r8	; <UNPREDICTABLE>
d0018b90:	0f07f1ba 	svceq	0x0007f1ba
d0018b94:	f8dfd161 			; <UNDEFINED> instruction: 0xf8dfd161
d0018b98:	215b263c 	cmpcs	fp, ip, lsr r6
d0018b9c:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d0018ba0:	f951f7fa 			; <UNDEFINED> instruction: 0xf951f7fa
d0018ba4:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0018ba8:	2201ad77 	andcs	sl, r1, #7616	; 0x1dc0
d0018bac:	46114620 	ldrmi	r4, [r1], -r0, lsr #12
d0018bb0:	fb28f7fd 	blx	0xd0a56bae
d0018bb4:	2620f8df 			; <UNDEFINED> instruction: 0x2620f8df
d0018bb8:	4620215d 			; <UNDEFINED> instruction: 0x4620215d
d0018bbc:	f7fa447a 			; <UNDEFINED> instruction: 0xf7fa447a
d0018bc0:	2800f942 	stmdacs	r0, {r1, r6, r8, fp, ip, sp, lr, pc}
d0018bc4:	ad68f43f 	cfstrdge	mvd15, [r8, #-252]!	; 0xffffff04
d0018bc8:	2101463a 	tstcs	r1, sl, lsr r6
d0018bcc:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0018bd0:	6ae7f99b 	bvs	0xcfa17244
d0018bd4:	f0002f3d 			; <UNDEFINED> instruction: 0xf0002f3d
d0018bd8:	f46f8262 	vld1.16	{d24-d27}, [pc :128], r2
d0018bdc:	187b7192 	ldmdane	fp!, {r1, r4, r7, r8, ip, sp, lr}^
d0018be0:	f2402b01 	vqdmulh.s<illegal width 8>	d18, d0, d1
d0018be4:	f46f825c 	vld1.16	{d24-d27}, [pc :64], ip
d0018be8:	18bb7294 	ldmne	fp!, {r2, r4, r7, r9, ip, sp, lr}
d0018bec:	f2402b04 	vqdmulh.s<illegal width 8>	d18, d0, d4
d0018bf0:	f6458256 			; <UNDEFINED> instruction: 0xf6458256
d0018bf4:	46204108 	strtmi	r4, [r0], -r8, lsl #2
d0018bf8:	f812f7fc 			; <UNDEFINED> instruction: 0xf812f7fc
d0018bfc:	f641e620 			; <UNDEFINED> instruction: 0xf641e620
d0018c00:	46200108 	strtmi	r0, [r0], -r8, lsl #2
d0018c04:	f80cf7fc 			; <UNDEFINED> instruction: 0xf80cf7fc
d0018c08:	4106f64b 	tstmi	r6, fp, asr #12	; <UNPREDICTABLE>
d0018c0c:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0018c10:	f247f807 	vadd.i8	d31, d7, d7
d0018c14:	46200108 	strtmi	r0, [r0], -r8, lsl #2
d0018c18:	f7fc2502 			; <UNDEFINED> instruction: 0xf7fc2502
d0018c1c:	e60ff801 	str	pc, [pc], -r1, lsl #16
d0018c20:	2108f641 	tstcs	r8, r1, asr #12	; <UNPREDICTABLE>
d0018c24:	f244e7ed 	vabd.s8	q15, q10, <illegal reg q14.5>
d0018c28:	e7ea0108 	strb	r0, [sl, r8, lsl #2]!
d0018c2c:	3108f244 	tstcc	r8, r4, asr #4	; <UNPREDICTABLE>
d0018c30:	f244e7e7 	vabd.s8	q15, q10, <illegal reg q11.5>
d0018c34:	e7e40148 	strb	r0, [r4, r8, asr #2]!
d0018c38:	6102f244 	tstvs	r2, r4, asr #4	; <UNPREDICTABLE>
d0018c3c:	fff0f7fb 			; <UNDEFINED> instruction: 0xfff0f7fb
d0018c40:	6108f244 	tstvs	r8, r4, asr #4	; <UNPREDICTABLE>
d0018c44:	ffecf7fb 			; <UNDEFINED> instruction: 0xffecf7fb
d0018c48:	0190f244 	orrseq	pc, r0, r4, asr #4
d0018c4c:	1310f244 	tstne	r0, #68, 4	; 0x40000004	; <UNPREDICTABLE>
d0018c50:	7f96f5b7 	svcvc	0x0096f5b7
d0018c54:	4619bf18 	sadd16mi	fp, r9, r8
d0018c58:	f1bae7d3 			; <UNDEFINED> instruction: 0xf1bae7d3
d0018c5c:	463a0f0f 	ldrtmi	r0, [sl], -pc, lsl #30
d0018c60:	0101f04f 	tsteq	r1, pc, asr #32	; <UNPREDICTABLE>
d0018c64:	d1184620 	tstle	r8, r0, lsr #12
d0018c68:	f94ef7fc 			; <UNDEFINED> instruction: 0xf94ef7fc
d0018c6c:	6108f244 	tstvs	r8, r4, asr #4	; <UNPREDICTABLE>
d0018c70:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0018c74:	212effd5 	ldrdcs	pc, [lr, -r5]!
d0018c78:	f8d7f7fa 			; <UNDEFINED> instruction: 0xf8d7f7fa
d0018c7c:	b1204605 			; <UNDEFINED> instruction: 0xb1204605
d0018c80:	4632465b 			; <UNDEFINED> instruction: 0x4632465b
d0018c84:	10cef899 	smullne	pc, lr, r9, r8	; <UNPREDICTABLE>
d0018c88:	6da3e6c2 	stcvs	6, cr14, [r3, #776]!	; 0x308
d0018c8c:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0018c90:	f8dfad03 			; <UNDEFINED> instruction: 0xf8dfad03
d0018c94:	447b3548 	ldrbtmi	r3, [fp], #-1352	; 0xfffffab8
d0018c98:	f1bae675 			; <UNDEFINED> instruction: 0xf1bae675
d0018c9c:	d1160f11 	tstle	r6, r1, lsl pc
d0018ca0:	f932f7fc 			; <UNDEFINED> instruction: 0xf932f7fc
d0018ca4:	6108f244 	tstvs	r8, r4, asr #4	; <UNPREDICTABLE>
d0018ca8:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0018cac:	6ae3ffb9 	bvs	0xcf918b98
d0018cb0:	d1042b5b 	tstle	r4, fp, asr fp
d0018cb4:	4632462b 	ldrtmi	r4, [r2], -fp, lsr #12
d0018cb8:	10cef899 	smullne	pc, lr, r9, r8	; <UNPREDICTABLE>
d0018cbc:	6da3e6cb 	stcvs	6, cr14, [r3, #812]!	; 0x32c
d0018cc0:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0018cc4:	f8dface9 			; <UNDEFINED> instruction: 0xf8dface9
d0018cc8:	447b3518 	ldrbtmi	r3, [fp], #-1304	; 0xfffffae8
d0018ccc:	f1bae65b 			; <UNDEFINED> instruction: 0xf1bae65b
d0018cd0:	d1070f08 	tstle	r7, r8, lsl #30
d0018cd4:	f918f7fc 			; <UNDEFINED> instruction: 0xf918f7fc
d0018cd8:	6108f244 	tstvs	r8, r4, asr #4	; <UNPREDICTABLE>
d0018cdc:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0018ce0:	e6dcff9f 			; <UNDEFINED> instruction: 0xe6dcff9f
d0018ce4:	f910f7fc 			; <UNDEFINED> instruction: 0xf910f7fc
d0018ce8:	0108f646 	tsteq	r8, r6, asr #12	; <UNPREDICTABLE>
d0018cec:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0018cf0:	f1baff97 			; <UNDEFINED> instruction: 0xf1baff97
d0018cf4:	e4ec0f01 	strbt	r0, [ip], #3841	; 0xf01
d0018cf8:	24e8f8df 	strbtcs	pc, [r8], #2271	; 0x8df	; <UNPREDICTABLE>
d0018cfc:	46484651 			; <UNDEFINED> instruction: 0x46484651
d0018d00:	f7f7447a 			; <UNDEFINED> instruction: 0xf7f7447a
d0018d04:	4605fdae 	strmi	pc, [r5], -lr, lsr #27
d0018d08:	4659b120 	ldrbmi	fp, [r9], -r0, lsr #2
d0018d0c:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0018d10:	e648ffe3 	strb	pc, [r8], -r3, ror #31	; <UNPREDICTABLE>
d0018d14:	2b006da3 	blcs	0xd00343a8
d0018d18:	acbef47f 	cfldrsge	mvf15, [lr], #508	; 0x1fc
d0018d1c:	34c8f8df 	strbcc	pc, [r8], #2271	; 0x8df	; <UNPREDICTABLE>
d0018d20:	e630447b 			; <UNDEFINED> instruction: 0xe630447b
d0018d24:	46202126 	strtmi	r2, [r0], -r6, lsr #2
d0018d28:	f87ff7fa 			; <UNDEFINED> instruction: 0xf87ff7fa
d0018d2c:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d0018d30:	f8df80a5 			; <UNDEFINED> instruction: 0xf8df80a5
d0018d34:	f24024b8 	vqshl.s8	d18, d24, d16
d0018d38:	46201101 	strtmi	r1, [r0], -r1, lsl #2
d0018d3c:	447a6a67 	ldrbtmi	r6, [sl], #-2663	; 0xfffff599
d0018d40:	8028f8d4 	ldrdhi	pc, [r8], -r4	; <UNPREDICTABLE>
d0018d44:	9030f894 	mlasls	r0, r4, r8, pc	; <UNPREDICTABLE>
d0018d48:	a034f8d4 	ldrsbtge	pc, [r4], -r4	; <UNPREDICTABLE>
d0018d4c:	6b06e9d4 	blvs	0xd01d34a4
d0018d50:	f879f7fa 			; <UNDEFINED> instruction: 0xf879f7fa
d0018d54:	9b09b958 	blls	0xd02872bc
d0018d58:	f8d39a09 			; <UNDEFINED> instruction: 0xf8d39a09
d0018d5c:	3b013120 	blcc	0xd00651e4
d0018d60:	3120f8c2 	smlawtcc	r0, r2, r8, pc	; <UNPREDICTABLE>
d0018d64:	ecbdb01d 	ldc	0, cr11, [sp], #116	; 0x74
d0018d68:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d0018d6c:	46318ff0 	shsub8mi	r8, r1, r0
d0018d70:	4620465a 			; <UNDEFINED> instruction: 0x4620465a
d0018d74:	fcc6f7f7 	stc2l	7, cr15, [r6], {247}	; 0xf7
d0018d78:	f2801e01 	vmull.p8	<illegal reg q0.5>, d0, d1
d0018d7c:	465a81d3 			; <UNDEFINED> instruction: 0x465a81d3
d0018d80:	46204631 			; <UNDEFINED> instruction: 0x46204631
d0018d84:	fcddf7f7 	ldc2l	7, cr15, [sp], {247}	; 0xf7
d0018d88:	db701e02 	blle	0xd1c20598
d0018d8c:	fb062638 	blx	0xd01a2676
d0018d90:	f5064602 			; <UNDEFINED> instruction: 0xf5064602
d0018d94:	f89636ba 			; <UNDEFINED> instruction: 0xf89636ba
d0018d98:	f1bbb0d0 			; <UNDEFINED> instruction: 0xf1bbb0d0
d0018d9c:	f0000f00 			; <UNDEFINED> instruction: 0xf0000f00
d0018da0:	6da381e2 	stfvsd	f0, [r3, #904]!	; 0x388
d0018da4:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0018da8:	f8dfac77 			; <UNDEFINED> instruction: 0xf8dfac77
d0018dac:	447b3444 	ldrbtmi	r3, [fp], #-1092	; 0xfffffbbc
d0018db0:	a068f8c4 	rsbge	pc, r8, r4, asr #17
d0018db4:	3716e9c4 	ldrcc	lr, [r6, -r4, asr #19]
d0018db8:	8918e9c4 	ldmdbhi	r8, {r2, r6, r7, r8, fp, sp, lr, pc}
d0018dbc:	2b0ee540 	blcs	0xd03d22c4
d0018dc0:	4620d105 	strtmi	sp, [r0], -r5, lsl #2
d0018dc4:	fff4f7fb 			; <UNDEFINED> instruction: 0xfff4f7fb
d0018dc8:	3136f896 	teqcc	r6, r6	; <illegal shifter operand>	; <UNPREDICTABLE>
d0018dcc:	b15be601 	cmplt	fp, r1, lsl #12
d0018dd0:	d0092b09 	andle	r2, r9, r9, lsl #22
d0018dd4:	d14a2b0a 	cmple	sl, sl, lsl #22
d0018dd8:	2b5b6ae3 	blcs	0xd16f396c
d0018ddc:	465ad143 	ldrbmi	sp, [sl], -r3, asr #2
d0018de0:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0018de4:	e032ffb3 	ldrht	pc, [r2], -r3	; <UNPREDICTABLE>
d0018de8:	91064620 	tstls	r6, r0, lsr #12
d0018dec:	ffe0f7fb 			; <UNDEFINED> instruction: 0xffe0f7fb
d0018df0:	99062030 	stmdbls	r6, {r4, r5, sp}
d0018df4:	fb006ae3 	blx	0xd003398a
d0018df8:	2b5b4101 	blcs	0xd16e9204
d0018dfc:	3122f501 	msrcc	CPSR_x, r1, lsl #10
d0018e00:	3135f891 	teqcc	r5, r1	; <illegal shifter operand>	; <UNPREDICTABLE>
d0018e04:	2b09d107 	blcs	0xd028d228
d0018e08:	2201d15b 	andcs	sp, r1, #-1073741802	; 0xc0000016
d0018e0c:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d0018e10:	fc50f7fd 	mrrc2	7, 15, pc, r0, cr13	; <UNPREDICTABLE>
d0018e14:	2b09e48e 	blcs	0xd0292054
d0018e18:	6da3d153 	stfvsd	f5, [r3, #332]!	; 0x14c
d0018e1c:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0018e20:	4bf4ac3b 	blmi	0xcfd43f14
d0018e24:	e7c3447b 			; <UNDEFINED> instruction: 0xe7c3447b
d0018e28:	0bf7f011 	bleq	0xcfe14e74
d0018e2c:	2101d11f 	tstcs	r1, pc, lsl r1
d0018e30:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0018e34:	f244f869 	vadd.i8	<illegal reg q15.5>, q2, <illegal reg q12.5>
d0018e38:	46206108 	strtmi	r6, [r0], -r8, lsl #2
d0018e3c:	fef0f7fb 	mrc2	7, 7, pc, cr0, cr11, {7}
d0018e40:	2b5b6ae3 	blcs	0xd16f39d4
d0018e44:	30ccf896 	smullcc	pc, ip, r6, r8	; <UNPREDICTABLE>
d0018e48:	2b08d104 	blcs	0xd024d260
d0018e4c:	2201d139 	andcs	sp, r1, #1073741838	; 0x4000000e
d0018e50:	e7dc4659 			; <UNDEFINED> instruction: 0xe7dc4659
d0018e54:	d1342b08 	teqle	r4, r8, lsl #22
d0018e58:	2b006da3 	blcs	0xd00344ec
d0018e5c:	ac1cf47f 	cfldrsge	mvf15, [ip], {127}	; 0x7f
d0018e60:	447b4be5 	ldrbtmi	r4, [fp], #-3045	; 0xfffff41b
d0018e64:	4620e7a4 	strtmi	lr, [r0], -r4, lsr #15
d0018e68:	ffa2f7fb 			; <UNDEFINED> instruction: 0xffa2f7fb
d0018e6c:	6da3e5a5 	cfstr32vs	mvfx14, [r3, #660]!	; 0x294
d0018e70:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0018e74:	4be1ac11 	blmi	0xcf883ec0
d0018e78:	e799447b 			; <UNDEFINED> instruction: 0xe799447b
d0018e7c:	4620212a 	strtmi	r2, [r0], -sl, lsr #2
d0018e80:	ffd3f7f9 			; <UNDEFINED> instruction: 0xffd3f7f9
d0018e84:	d0602800 	rsble	r2, r0, r0, lsl #16
d0018e88:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d0018e8c:	fbdcf7ff 	blx	0xcf756e92
d0018e90:	46052807 	strmi	r2, [r5], -r7, lsl #16
d0018e94:	b17ed117 	cmnlt	lr, r7, lsl r1
d0018e98:	4620213d 			; <UNDEFINED> instruction: 0x4620213d
d0018e9c:	ffc5f7f9 			; <UNDEFINED> instruction: 0xffc5f7f9
d0018ea0:	f24bb150 	vand	<illegal reg q13.5>, <illegal reg q5.5>, q0
d0018ea4:	46204103 	strtmi	r4, [r0], -r3, lsl #2
d0018ea8:	febaf7fb 	mrc2	7, 5, pc, cr10, cr11, {7}
d0018eac:	21012204 	tstcs	r1, r4, lsl #4
d0018eb0:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0018eb4:	e019f9a7 	ands	pc, r9, r7, lsr #19
d0018eb8:	41d0f44f 	bicsmi	pc, r0, pc, asr #8
d0018ebc:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0018ec0:	2504feaf 	strcs	pc, [r4, #-3759]	; 0xfffff151
d0018ec4:	2805e4bc 	stmdacs	r5, {r2, r3, r4, r5, r7, sl, sp, lr, pc}
d0018ec8:	9b09d121 	blls	0xd028d354
d0018ecc:	5124f8d3 	ldrdpl	pc, [r4, -r3]!
d0018ed0:	213db1a6 	teqcs	sp, r6, lsr #3
d0018ed4:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d0018ed8:	b178ffa8 	cmnlt	r8, r8, lsr #31	; <UNPREDICTABLE>
d0018edc:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d0018ee0:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0018ee4:	4629fe9d 			; <UNDEFINED> instruction: 0x4629fe9d
d0018ee8:	fdaef7fe 	stc2	7, cr15, [lr, #1016]!	; 0x3f8
d0018eec:	4106f64b 	tstmi	r6, fp, asr #12	; <UNPREDICTABLE>
d0018ef0:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0018ef4:	f246fe95 			; <UNDEFINED> instruction: 0xf246fe95
d0018ef8:	e68c0108 	str	r0, [ip], r8, lsl #2
d0018efc:	41d0f44f 	bicsmi	pc, r0, pc, asr #8
d0018f00:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0018f04:	9b09fe8d 	blls	0xd0298940
d0018f08:	5124f8c3 	smlawtpl	r4, r3, r8, pc	; <UNPREDICTABLE>
d0018f0c:	2804e54b 	stmdacs	r4, {r0, r1, r3, r6, r8, sl, sp, lr, pc}
d0018f10:	6da3d006 	stcvs	0, cr13, [r3, #24]!
d0018f14:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0018f18:	4bb9ac93 	blmi	0xcee8416c
d0018f1c:	e532447b 	ldr	r4, [r2, #-1147]!	; 0xfffffb85
d0018f20:	213db166 	teqcs	sp, r6, ror #2
d0018f24:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d0018f28:	b138ff80 	teqlt	r8, r0, lsl #31	; <UNPREDICTABLE>
d0018f2c:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d0018f30:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0018f34:	2201fe75 	andcs	pc, r1, #1872	; 0x750
d0018f38:	e7b94611 			; <UNDEFINED> instruction: 0xe7b94611
d0018f3c:	41d0f44f 	bicsmi	pc, r0, pc, asr #8
d0018f40:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0018f44:	f7fffe6d 			; <UNDEFINED> instruction: 0xf7fffe6d
d0018f48:	2128bba7 			; <UNDEFINED> instruction: 0x2128bba7
d0018f4c:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d0018f50:	2800ff6c 	stmdacs	r0, {r2, r3, r5, r6, r8, r9, sl, fp, ip, sp, lr, pc}
d0018f54:	6ae3d052 	bvs	0xcf90d0a4
d0018f58:	d1322b2a 	teqle	r2, sl, lsr #22
d0018f5c:	f2406ce2 	sha1c.32	q11, q8, q9
d0018f60:	429a1301 	addsmi	r1, sl, #67108864	; 0x4000000
d0018f64:	6be2d12d 	blvs	0xcf8cd420
d0018f68:	6ba14620 	blvs	0xce86a7f0
d0018f6c:	fbcaf7f7 	blx	0xcf2d6f52
d0018f70:	db261e05 	blle	0xd09a078c
d0018f74:	fb032330 	blx	0xd00e1c3e
d0018f78:	f5034305 			; <UNDEFINED> instruction: 0xf5034305
d0018f7c:	f8933322 			; <UNDEFINED> instruction: 0xf8933322
d0018f80:	2b0c3135 	blcs	0xd032545c
d0018f84:	4620d11d 			; <UNDEFINED> instruction: 0x4620d11d
d0018f88:	ff34f7f9 			; <UNDEFINED> instruction: 0xff34f7f9
d0018f8c:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d0018f90:	4a9cff31 	bmi	0xce758c5c
d0018f94:	46202129 	strtmi	r2, [r0], -r9, lsr #2
d0018f98:	f7f9447a 			; <UNDEFINED> instruction: 0xf7f9447a
d0018f9c:	2800ff54 	stmdacs	r0, {r2, r4, r6, r8, r9, sl, fp, ip, sp, lr, pc}
d0018fa0:	ab7af43f 	blge	0xd1ed60a4
d0018fa4:	21284a98 			; <UNDEFINED> instruction: 0x21284a98
d0018fa8:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d0018fac:	ff4bf7f9 			; <UNDEFINED> instruction: 0xff4bf7f9
d0018fb0:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0018fb4:	4629ab71 			; <UNDEFINED> instruction: 0x4629ab71
d0018fb8:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0018fbc:	f7ffff81 			; <UNDEFINED> instruction: 0xf7ffff81
d0018fc0:	2200bbb9 	andcs	fp, r0, #189440	; 0x2e400
d0018fc4:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d0018fc8:	f91cf7fd 			; <UNDEFINED> instruction: 0xf91cf7fd
d0018fcc:	46054a8f 	strmi	r4, [r5], -pc, lsl #21
d0018fd0:	447a2129 	ldrbtmi	r2, [sl], #-297	; 0xfffffed7
d0018fd4:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d0018fd8:	2d03ff36 	stccs	15, cr15, [r3, #-216]	; 0xffffff28
d0018fdc:	ac83f47f 	cfstrsge	mvf15, [r3], {127}	; 0x7f
d0018fe0:	7191f44f 	orrsvc	pc, r1, pc, asr #8
d0018fe4:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d0018fe8:	2800ff20 	stmdacs	r0, {r5, r8, r9, sl, fp, ip, sp, lr, pc}
d0018fec:	acdbf43f 	cfldrdge	mvd15, [fp], {63}	; 0x3f
d0018ff0:	23009909 	movwcs	r9, #2313	; 0x909
d0018ff4:	f8d14632 			; <UNDEFINED> instruction: 0xf8d14632
d0018ff8:	e5091124 	str	r1, [r9, #-292]	; 0xfffffedc
d0018ffc:	4620212b 	strtmi	r2, [r0], -fp, lsr #2
d0019000:	ff13f7f9 			; <UNDEFINED> instruction: 0xff13f7f9
d0019004:	2100b168 	tstcs	r0, r8, ror #2
d0019008:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d001900c:	2802fb1d 	stmdacs	r2, {r0, r2, r3, r4, r8, r9, fp, ip, sp, lr, pc}
d0019010:	d1204605 			; <UNDEFINED> instruction: 0xd1204605
d0019014:	2b006da3 	blcs	0xd00346a8
d0019018:	ac12f47f 	cfldrsge	mvf15, [r2], {127}	; 0x7f
d001901c:	447b4b7c 	ldrbtmi	r4, [fp], #-2940	; 0xfffff484
d0019020:	212de4b1 			; <UNDEFINED> instruction: 0x212de4b1
d0019024:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d0019028:	2800ff00 	stmdacs	r0, {r8, r9, sl, fp, ip, sp, lr, pc}
d001902c:	2121d1eb 			; <UNDEFINED> instruction: 0x2121d1eb
d0019030:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d0019034:	2800fefa 	stmdacs	r0, {r1, r3, r4, r5, r6, r7, r9, sl, fp, ip, sp, lr, pc}
d0019038:	217ed1e5 	cmncs	lr, r5, ror #3
d001903c:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d0019040:	4605fef4 			; <UNDEFINED> instruction: 0x4605fef4
d0019044:	d1de2800 	bicsle	r2, lr, r0, lsl #16
d0019048:	46204972 			; <UNDEFINED> instruction: 0x46204972
d001904c:	f7f74479 			; <UNDEFINED> instruction: 0xf7f74479
d0019050:	f7fff8ab 			; <UNDEFINED> instruction: 0xf7fff8ab
d0019054:	2803bbf5 	stmdacs	r3, {r0, r2, r4, r5, r6, r7, r8, r9, fp, ip, sp, pc}
d0019058:	2f21d108 	svccs	0x0021d108
d001905c:	6da3d013 	stcvs	0, cr13, [r3, #76]!	; 0x4c
d0019060:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0019064:	4b6caca0 	blmi	0xd1b442ec
d0019068:	e48c447b 	str	r4, [ip], #1147	; 0x47b
d001906c:	d1022f2d 	tstle	r2, sp, lsr #30
d0019070:	2140f244 	cmpcs	r0, r4, asr #4	; <UNPREDICTABLE>
d0019074:	2f7ee5bf 	svccs	0x007ee5bf
d0019078:	f244d102 	vrhadd.s8	d29, d4, d2
d001907c:	e5ba31c0 	ldr	r3, [sl, #448]!	; 0x1c0
d0019080:	f47f2f21 			; <UNDEFINED> instruction: 0xf47f2f21
d0019084:	f44fabdd 			; <UNDEFINED> instruction: 0xf44fabdd
d0019088:	46205120 	strtmi	r5, [r0], -r0, lsr #2
d001908c:	fdc8f7fb 	stc2l	7, cr15, [r8, #1004]	; 0x3ec
d0019090:	f7fc2100 			; <UNDEFINED> instruction: 0xf7fc2100
d0019094:	f7fffa32 			; <UNDEFINED> instruction: 0xf7fffa32
d0019098:	2000baff 	strdcs	fp, [r0], -pc	; <UNPREDICTABLE>
d001909c:	2e00e662 	cfmadd32cs	mvax3, mvfx14, mvfx0, mvfx2
d00190a0:	ada7f43f 	cfstrsge	mvf15, [r7, #252]!	; 0xfc
d00190a4:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d00190a8:	f641fea5 			; <UNDEFINED> instruction: 0xf641fea5
d00190ac:	46200108 	strtmi	r0, [r0], -r8, lsl #2
d00190b0:	fdb6f7fb 	ldc2	7, cr15, [r6, #1004]!	; 0x3ec
d00190b4:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d00190b8:	fdb2f7fb 	ldc2	7, cr15, [r2, #1004]!	; 0x3ec
d00190bc:	d0072f3d 	andle	r2, r7, sp, lsr pc
d00190c0:	41f0f44f 	mvnsmi	pc, pc, asr #8
d00190c4:	fdacf7fb 	stc2	7, cr15, [ip, #1004]!	; 0x3ec
d00190c8:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d00190cc:	fda8f7fb 	stc2	7, cr15, [r8, #1004]!	; 0x3ec
d00190d0:	46202201 	strtmi	r2, [r0], -r1, lsl #4
d00190d4:	f7fd4611 			; <UNDEFINED> instruction: 0xf7fd4611
d00190d8:	2f3df895 	svccs	0x003df895
d00190dc:	ad94f43f 	cfldrsge	mvf15, [r4, #252]	; 0xfc
d00190e0:	4106f64b 	tstmi	r6, fp, asr #12	; <UNPREDICTABLE>
d00190e4:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d00190e8:	f46ffd9b 			; <UNDEFINED> instruction: 0xf46ffd9b
d00190ec:	18fb7392 	ldmne	fp!, {r1, r4, r7, r8, r9, ip, sp, lr}^
d00190f0:	f63f2b08 			; <UNDEFINED> instruction: 0xf63f2b08
d00190f4:	a202ad89 	andge	sl, r2, #8768	; 0x2240
d00190f8:	3023f852 	eorcc	pc, r3, r2, asr r8	; <UNPREDICTABLE>
d00190fc:	4710441a 			; <UNDEFINED> instruction: 0x4710441a
d0019100:	fffffaff 			; <UNDEFINED> instruction: 0xfffffaff
d0019104:	fffffb21 			; <UNDEFINED> instruction: 0xfffffb21
d0019108:	fffffb09 			; <UNDEFINED> instruction: 0xfffffb09
d001910c:	fffffb09 			; <UNDEFINED> instruction: 0xfffffb09
d0019110:	fffffb27 			; <UNDEFINED> instruction: 0xfffffb27
d0019114:	fffffb2d 			; <UNDEFINED> instruction: 0xfffffb2d
d0019118:	fffffb33 			; <UNDEFINED> instruction: 0xfffffb33
d001911c:	fffffb39 			; <UNDEFINED> instruction: 0xfffffb39
d0019120:	fffffb39 			; <UNDEFINED> instruction: 0xfffffb39
d0019124:	fb062630 	blx	0xd01a29ee
d0019128:	f5064601 			; <UNDEFINED> instruction: 0xf5064601
d001912c:	f8963622 			; <UNDEFINED> instruction: 0xf8963622
d0019130:	f1bbb140 			; <UNDEFINED> instruction: 0xf1bbb140
d0019134:	f47f0f00 			; <UNDEFINED> instruction: 0xf47f0f00
d0019138:	f896ae34 			; <UNDEFINED> instruction: 0xf896ae34
d001913c:	2b0d3135 	blcs	0xd0365618
d0019140:	ae3df47f 	mrcge	4, 1, APSR_nzcv, cr13, cr15, {3}
d0019144:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0019148:	4a34fe33 	bmi	0xd0d58a1c
d001914c:	4620212e 	strtmi	r2, [r0], -lr, lsr #2
d0019150:	f7f9447a 			; <UNDEFINED> instruction: 0xf7f9447a
d0019154:	2800fe78 	stmdacs	r0, {r3, r4, r5, r6, r9, sl, fp, ip, sp, lr, pc}
d0019158:	aa9ef43f 	bge	0xce7d625c
d001915c:	465a2301 	ldrbmi	r2, [sl], -r1, lsl #6
d0019160:	1136f896 	teqne	r6, r6	; <illegal shifter operand>	; <UNPREDICTABLE>
d0019164:	f896e454 			; <UNDEFINED> instruction: 0xf896e454
d0019168:	290f10cc 	stmdbcs	pc, {r2, r3, r6, r7, ip}	; <UNPREDICTABLE>
d001916c:	ae5cf47f 	mrcge	4, 2, APSR_nzcv, cr12, cr15, {3}
d0019170:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d0019174:	fec8f7fb 	mcr2	7, 6, pc, cr8, cr11, {7}	; <UNPREDICTABLE>
d0019178:	6108f244 	tstvs	r8, r4, asr #4	; <UNPREDICTABLE>
d001917c:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0019180:	4a27fd4f 	bmi	0xd0a186c4
d0019184:	447a212e 	ldrbtmi	r2, [sl], #-302	; 0xfffffed2
d0019188:	fe5df7f9 	mrc2	7, 2, pc, cr13, cr9, {7}
d001918c:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0019190:	2301aa83 	movwcs	sl, #6787	; 0x1a83
d0019194:	f896465a 			; <UNDEFINED> instruction: 0xf896465a
d0019198:	e43910ce 	ldrt	r1, [r9], #-206	; 0xffffff32
d001919c:	ffffda30 			; <UNDEFINED> instruction: 0xffffda30
d00191a0:	fffffbdc 			; <UNDEFINED> instruction: 0xfffffbdc
d00191a4:	fffffb9b 			; <UNDEFINED> instruction: 0xfffffb9b
d00191a8:	fffffb7f 			; <UNDEFINED> instruction: 0xfffffb7f
d00191ac:	fffffb77 			; <UNDEFINED> instruction: 0xfffffb77
d00191b0:	fffffb39 			; <UNDEFINED> instruction: 0xfffffb39
d00191b4:	fffffb44 			; <UNDEFINED> instruction: 0xfffffb44
d00191b8:	fffffad3 			; <UNDEFINED> instruction: 0xfffffad3
d00191bc:	fffffa02 			; <UNDEFINED> instruction: 0xfffffa02
d00191c0:	fffff99b 			; <UNDEFINED> instruction: 0xfffff99b
d00191c4:	fffff951 			; <UNDEFINED> instruction: 0xfffff951
d00191c8:	fffff92c 			; <UNDEFINED> instruction: 0xfffff92c
d00191cc:	000081b2 			; <UNDEFINED> instruction: 0x000081b2
d00191d0:	fffff8d7 			; <UNDEFINED> instruction: 0xfffff8d7
d00191d4:	fffff8a6 			; <UNDEFINED> instruction: 0xfffff8a6
d00191d8:	fffff8b4 			; <UNDEFINED> instruction: 0xfffff8b4
d00191dc:	fffff729 			; <UNDEFINED> instruction: 0xfffff729
d00191e0:	fffff713 			; <UNDEFINED> instruction: 0xfffff713
d00191e4:	ffffbfdc 			; <UNDEFINED> instruction: 0xffffbfdc
d00191e8:	fffff774 			; <UNDEFINED> instruction: 0xfffff774
d00191ec:	fffff777 			; <UNDEFINED> instruction: 0xfffff777
d00191f0:	fffff723 			; <UNDEFINED> instruction: 0xfffff723
d00191f4:	fffff70e 			; <UNDEFINED> instruction: 0xfffff70e
d00191f8:	fffff6d0 			; <UNDEFINED> instruction: 0xfffff6d0
d00191fc:	fffff6e9 			; <UNDEFINED> instruction: 0xfffff6e9
d0019200:	fffff67b 			; <UNDEFINED> instruction: 0xfffff67b
d0019204:	fffff632 			; <UNDEFINED> instruction: 0xfffff632
d0019208:	fffff647 			; <UNDEFINED> instruction: 0xfffff647
d001920c:	fffff646 			; <UNDEFINED> instruction: 0xfffff646
d0019210:	ffffd0cc 			; <UNDEFINED> instruction: 0xffffd0cc
d0019214:	fffff5d9 			; <UNDEFINED> instruction: 0xfffff5d9
d0019218:	ffffd0a8 			; <UNDEFINED> instruction: 0xffffd0a8
d001921c:	fffff3b7 			; <UNDEFINED> instruction: 0xfffff3b7
d0019220:	fffff381 			; <UNDEFINED> instruction: 0xfffff381

Disassembly of section .text.condition.constprop.0:

d0019260 <.text.condition.constprop.0>:
d0019260:	4c0ab510 	cfstr32mi	mvfx11, [sl], {16}
d0019264:	4a0a2128 	bmi	0xd02a170c
d0019268:	447a447c 	ldrbtmi	r4, [sl], #-1148	; 0xfffffb84
d001926c:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d0019270:	2202fdea 	andcs	pc, r2, #14976	; 0x3a80
d0019274:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d0019278:	ffc4f7fc 			; <UNDEFINED> instruction: 0xffc4f7fc
d001927c:	46204a05 	strtmi	r4, [r0], -r5, lsl #20
d0019280:	447a2129 	ldrbtmi	r2, [sl], #-297	; 0xfffffed7
d0019284:	4010e8bd 			; <UNDEFINED> instruction: 0x4010e8bd
d0019288:	bdddf7f9 	ldcllt	7, cr15, [sp, #996]	; 0x3e4
d001928c:	0000a1b4 			; <UNDEFINED> instruction: 0x0000a1b4
d0019290:	ffffffb6 			; <UNDEFINED> instruction: 0xffffffb6
d0019294:	ffffffbc 			; <UNDEFINED> instruction: 0xffffffbc

Disassembly of section .text.simple_expression.constprop.0:

d0019438 <.text.simple_expression.constprop.0>:
d0019438:	342cf8df 	strtcc	pc, [ip], #-2271	; 0xfffff721
d001943c:	6cdb447b 	cfldrdvs	mvd4, [fp], {123}	; 0x7b
d0019440:	e92d2b3d 	push	{r0, r2, r3, r4, r5, r8, r9, fp, sp}
d0019444:	b0854ff0 	strdlt	r4, [r5], r0
d0019448:	f46fd01f 	vld4.8	{d29-d32}, [pc :64]
d001944c:	191a7492 	ldmdbne	sl, {r1, r4, r7, sl, ip, sp, lr}
d0019450:	d91a2a01 	ldmdble	sl, {r0, r9, fp, sp}
d0019454:	7094f46f 	addsvc	pc, r4, pc, ror #8
d0019458:	2b044403 	blcs	0xd012a46c
d001945c:	2300bf8c 	movwcs	fp, #3980	; 0xf8c
d0019460:	f8df2301 			; <UNDEFINED> instruction: 0xf8df2301
d0019464:	93004408 	movwls	r4, #1032	; 0x408
d0019468:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d001946c:	6ae2447c 	bvs	0xcf8aa664
d0019470:	d101429a 			; <UNDEFINED> instruction: 0xd101429a
d0019474:	b9539b00 	ldmdblt	r3, {r8, r9, fp, ip, pc}^
d0019478:	220348fd 	andcs	r4, r3, #16580608	; 0xfd0000
d001947c:	44782101 	ldrbtmi	r2, [r8], #-257	; 0xfffffeff
d0019480:	e8bdb005 	pop	{r0, r2, ip, sp, pc}
d0019484:	f7fc4ff0 			; <UNDEFINED> instruction: 0xf7fc4ff0
d0019488:	2301bebd 	movwcs	fp, #7869	; 0x1ebd
d001948c:	e9d4e7e9 	ldmib	r4, {r0, r3, r5, r6, r7, r8, r9, sl, sp, lr, pc}^
d0019490:	6b631206 	blvs	0xd18ddcb0
d0019494:	92024620 	andls	r4, r2, #32, 12	; 0x2000000
d0019498:	91019303 	tstls	r1, r3, lsl #6
d001949c:	f8d46a67 			; <UNDEFINED> instruction: 0xf8d46a67
d00194a0:	f8948028 			; <UNDEFINED> instruction: 0xf8948028
d00194a4:	f7f79030 			; <UNDEFINED> instruction: 0xf7f79030
d00194a8:	a901f92d 	stmdbge	r1, {r0, r2, r3, r5, r8, fp, ip, sp, lr, pc}
d00194ac:	c90e1e05 	stmdbgt	lr, {r0, r2, r9, sl, fp, ip}
d00194b0:	81caf280 	bichi	pc, sl, r0, lsl #5
d00194b4:	93014620 	movwls	r4, #5664	; 0x1620
d00194b8:	f943f7f7 			; <UNDEFINED> instruction: 0xf943f7f7
d00194bc:	0a00f1b0 	beq	0xd0055b84
d00194c0:	db159b01 	blle	0xd05800cc
d00194c4:	fb022238 	blx	0xd00a1dae
d00194c8:	f504440a 			; <UNDEFINED> instruction: 0xf504440a
d00194cc:	f89434ba 			; <UNDEFINED> instruction: 0xf89434ba
d00194d0:	b1ba20d0 	ldrsblt	r2, [sl, r0]!
d00194d4:	447a4ae7 	ldrbtmi	r4, [sl], #-2791	; 0xfffff519
d00194d8:	b9316d91 	ldmdblt	r1!, {r0, r4, r7, r8, sl, fp, sp, lr}
d00194dc:	447949e6 	ldrbtmi	r4, [r9], #-2534	; 0xfffff61a
d00194e0:	e9c26693 	stmib	r2, {r0, r1, r4, r7, r9, sl, sp, lr}^
d00194e4:	e9c21716 	stmib	r2, {r1, r2, r4, r8, r9, sl, ip}^
d00194e8:	b0058918 	andlt	r8, r5, r8, lsl r9
d00194ec:	8ff0e8bd 	svchi	0x00f0e8bd
d00194f0:	2a006da2 	bcs	0xd0034b80
d00194f4:	4ae1d1f9 	bmi	0xcf88dce0
d00194f8:	e9c4447a 	stmib	r4, {r1, r3, r4, r5, r6, sl, lr}^
d00194fc:	e9c42716 	stmib	r4, {r1, r2, r4, r8, r9, sl, sp}^
d0019500:	e01a8918 	ands	r8, sl, r8, lsl r9
d0019504:	60ccf894 	smullvs	pc, ip, r4, r8	; <UNPREDICTABLE>
d0019508:	0202f026 	andeq	pc, r2, #38	; 0x26
d001950c:	d15b2a0d 	cmple	fp, sp, lsl #20
d0019510:	93004cdb 	movwls	r4, #3291	; 0xcdb
d0019514:	4620447c 			; <UNDEFINED> instruction: 0x4620447c
d0019518:	fc6cf7f9 	stc2l	7, cr15, [ip], #-996	; 0xfffffc1c
d001951c:	4620213d 			; <UNDEFINED> instruction: 0x4620213d
d0019520:	fc83f7f9 	stc2	7, cr15, [r3], {249}	; 0xf9
d0019524:	6da2b958 			; <UNDEFINED> instruction: 0x6da2b958
d0019528:	d1de2a00 	bicsle	r2, lr, r0, lsl #20
d001952c:	9b004ad5 	blls	0xd002c088
d0019530:	e9c4447a 	stmib	r4, {r1, r3, r4, r5, r6, sl, lr}^
d0019534:	e9c48918 	stmib	r4, {r3, r4, r8, fp, pc}^
d0019538:	66a32716 	ssatvs	r2, #4, r6, lsl #14
d001953c:	2d00e7d5 	stccs	7, cr14, [r0, #-852]	; 0xfffffcac
d0019540:	bfac48d1 	svclt	0x00ac48d1
d0019544:	23382330 	teqcs	r8, #48, 6	; 0xc0000000
d0019548:	bfaa4478 	svclt	0x00aa4478
d001954c:	4405fb03 	strmi	pc, [r5], #-2819	; 0xfffff4fd
d0019550:	440afb03 	strmi	pc, [sl], #-2819	; 0xfffff4fd
d0019554:	3422f504 	strtcc	pc, [r2], #-1284	; 0xfffffafc
d0019558:	bfb69000 	svclt	0x00b69000
d001955c:	34baf504 	ldrtcc	pc, [sl], #1284	; 0x504	; <UNPREDICTABLE>
d0019560:	4136f894 	teqmi	r6, r4	; <illegal shifter operand>	; <UNPREDICTABLE>
d0019564:	40cef894 	smullmi	pc, lr, r4, r8	; <UNPREDICTABLE>
d0019568:	f7fd4621 			; <UNDEFINED> instruction: 0xf7fd4621
d001956c:	9800fe17 	stmdals	r0, {r0, r1, r2, r4, r9, sl, fp, ip, sp, lr, pc}
d0019570:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d0019574:	fb54f7fb 	blx	0xd155756a
d0019578:	98002d00 	stmdals	r0, {r8, sl, fp, sp}
d001957c:	4629db19 			; <UNDEFINED> instruction: 0x4629db19
d0019580:	fc16f7fb 	ldc2	7, cr15, [r6], {251}	; 0xfb
d0019584:	f24448c1 	vadd.i8	q10, q10, <illegal reg q0.5>
d0019588:	44786101 	ldrbtmi	r6, [r8], #-257	; 0xfffffeff
d001958c:	fb48f7fb 	blx	0xd1257582
d0019590:	4105f64b 	tstmi	r5, fp, asr #12	; <UNPREDICTABLE>
d0019594:	fb44f7fb 	blx	0xd115758a
d0019598:	731af44f 	tstvc	sl, #1325400064	; 0x4f000000	; <UNPREDICTABLE>
d001959c:	0004fb03 	andeq	pc, r4, r3, lsl #22
d00195a0:	30c9f500 	sbccc	pc, r9, r0, lsl #10
d00195a4:	0108f8b0 			; <UNDEFINED> instruction: 0x0108f8b0
d00195a8:	e8bdb005 	pop	{r0, r2, ip, sp, pc}
d00195ac:	f7fc4ff0 			; <UNDEFINED> instruction: 0xf7fc4ff0
d00195b0:	4652bd2b 	ldrbmi	fp, [r2], -fp, lsr #26
d00195b4:	90002101 	andls	r2, r0, r1, lsl #2
d00195b8:	fca6f7fb 	stc2	7, cr15, [r6], #1004	; 0x3ec
d00195bc:	6108f244 	tstvs	r8, r4, asr #4	; <UNPREDICTABLE>
d00195c0:	f7fb9800 			; <UNDEFINED> instruction: 0xf7fb9800
d00195c4:	e7ddfb2d 	ldrb	pc, [sp, sp, lsr #22]	; <UNPREDICTABLE>
d00195c8:	2a021ff2 	bcs	0xd00a1598
d00195cc:	f1a6d903 			; <UNDEFINED> instruction: 0xf1a6d903
d00195d0:	2a010210 	bcs	0xd0059e18
d00195d4:	4aaed807 	bmi	0xcebcf5f8
d00195d8:	6d91447a 	cfldrsvs	mvf4, [r1, #488]	; 0x1e8
d00195dc:	d1842900 	orrle	r2, r4, r0, lsl #18
d00195e0:	447949ac 	ldrbtmi	r4, [r9], #-2476	; 0xfffff654
d00195e4:	1eb1e77c 	mrcne	7, 5, lr, cr1, cr12, {3}
d00195e8:	d80d2909 	stmdale	sp, {r0, r3, r8, fp, sp}
d00195ec:	2215f240 	andscs	pc, r5, #64, 4
d00195f0:	07d140ca 	ldrbeq	r4, [r1, sl, asr #1]
d00195f4:	4aa8d508 	bmi	0xcea4ea1c
d00195f8:	6d91447a 	cfldrsvs	mvf4, [r1, #488]	; 0x1e8
d00195fc:	f47f2900 			; <UNDEFINED> instruction: 0xf47f2900
d0019600:	49a6af74 	stmibmi	r6!, {r2, r4, r5, r6, r8, r9, sl, fp, sp, pc}
d0019604:	e76b4479 			; <UNDEFINED> instruction: 0xe76b4479
d0019608:	93014ca5 	movwls	r4, #7333	; 0x1ca5
d001960c:	4620447c 			; <UNDEFINED> instruction: 0x4620447c
d0019610:	fbf0f7f9 	blx	0xcfc575fe
d0019614:	f8d44620 			; <UNDEFINED> instruction: 0xf8d44620
d0019618:	f7f9b02c 			; <UNDEFINED> instruction: 0xf7f9b02c
d001961c:	2e0cfbeb 	vmlscs.f64	d15, d28, d27
d0019620:	d11a9b01 	tstle	sl, r1, lsl #22
d0019624:	0f3df1bb 	svceq	0x003df1bb
d0019628:	6da2d006 	stcvs	0, cr13, [r2, #24]!
d001962c:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0019630:	4a9caf5c 	bmi	0xce7453a8
d0019634:	e760447a 			; <UNDEFINED> instruction: 0xe760447a
d0019638:	fb002030 	blx	0xd0021702
d001963c:	f5004005 			; <UNDEFINED> instruction: 0xf5004005
d0019640:	f2003022 	vhadd.s8	d3, d0, d18
d0019644:	f7fb1037 			; <UNDEFINED> instruction: 0xf7fb1037
d0019648:	2200fce3 	andcs	pc, r0, #58112	; 0xe300
d001964c:	46204629 	strtmi	r4, [r0], -r9, lsr #12
d0019650:	e8bdb005 	pop	{r0, r2, ip, sp, pc}
d0019654:	f7fb4ff0 			; <UNDEFINED> instruction: 0xf7fb4ff0
d0019658:	2e13bb92 	vmovcs.32	fp, d19[0]
d001965c:	f1bbd10d 			; <UNDEFINED> instruction: 0xf1bbd10d
d0019660:	d0060f3d 	andle	r0, r6, sp, lsr pc
d0019664:	2a006da2 	bcs	0xd0034cf4
d0019668:	af3ff47f 	svcge	0x003ff47f
d001966c:	447a4a8e 	ldrbtmi	r4, [sl], #-2702	; 0xfffff572
d0019670:	4620e743 	strtmi	lr, [r0], -r3, asr #14
d0019674:	fbe2f7fb 	blx	0xcf8d766a
d0019678:	2e12e7e7 	cdpcs	7, 1, cr14, cr2, cr7, {7}
d001967c:	f1bbd114 			; <UNDEFINED> instruction: 0xf1bbd114
d0019680:	d0060f3d 	andle	r0, r6, sp, lsr pc
d0019684:	2a006da2 	bcs	0xd0034d14
d0019688:	af2ff47f 	svcge	0x002ff47f
d001968c:	447a4a87 	ldrbtmi	r4, [sl], #-2695	; 0xfffff579
d0019690:	2330e733 	teqcs	r0, #13369344	; 0xcc0000
d0019694:	fb034620 	blx	0xd00eaf1e
d0019698:	f5034305 			; <UNDEFINED> instruction: 0xf5034305
d001969c:	f8933322 			; <UNDEFINED> instruction: 0xf8933322
d00196a0:	f7fc1136 			; <UNDEFINED> instruction: 0xf7fc1136
d00196a4:	e7d0fc21 	ldrb	pc, [r0, r1, lsr #24]	; <UNPREDICTABLE>
d00196a8:	d1142e0e 	tstle	r4, lr, lsl #28
d00196ac:	0f3df1bb 	svceq	0x003df1bb
d00196b0:	6da2d006 	stcvs	0, cr13, [r2, #24]!
d00196b4:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d00196b8:	4a7daf18 	bmi	0xd1f85320
d00196bc:	e71c447a 			; <UNDEFINED> instruction: 0xe71c447a
d00196c0:	46202330 			; <UNDEFINED> instruction: 0x46202330
d00196c4:	4305fb03 	movwmi	pc, #23299	; 0x5b03	; <UNPREDICTABLE>
d00196c8:	3322f503 	msrcc	CPSR_x, #12582912	; 0xc00000
d00196cc:	1136f893 	teqne	r6, r3	; <illegal shifter operand>	; <UNPREDICTABLE>
d00196d0:	f9baf7fe 			; <UNDEFINED> instruction: 0xf9baf7fe
d00196d4:	f1bbe7b9 			; <UNDEFINED> instruction: 0xf1bbe7b9
d00196d8:	f0000f3d 			; <UNDEFINED> instruction: 0xf0000f3d
d00196dc:	2e0a80af 	cdpcs	0, 0, cr8, cr10, cr15, {5}
d00196e0:	f46fd10b 	vld4.8	{d29,d31,d33,d35}, [pc], fp
d00196e4:	445a7292 	ldrbmi	r7, [sl], #-658	; 0xfffffd6e
d00196e8:	d9062a01 	stmdble	r6, {r0, r9, fp, sp}
d00196ec:	2a006da2 	bcs	0xd0034d7c
d00196f0:	aefbf47f 	mrcge	4, 7, APSR_nzcv, cr11, cr15, {3}
d00196f4:	447a4a6f 	ldrbtmi	r4, [sl], #-2671	; 0xfffff591
d00196f8:	2d00e6ff 	stccs	6, cr14, [r0, #-1020]	; 0xfffffc04
d00196fc:	486edb2c 	stmdami	lr!, {r2, r3, r5, r8, r9, fp, ip, lr, pc}^
d0019700:	46292200 	strtmi	r2, [r9], -r0, lsl #4
d0019704:	f7fb4478 			; <UNDEFINED> instruction: 0xf7fb4478
d0019708:	486cfb21 	stmdami	ip!, {r0, r5, r8, r9, fp, ip, sp, lr, pc}^
d001970c:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d0019710:	f7fb4478 			; <UNDEFINED> instruction: 0xf7fb4478
d0019714:	4f6afa85 	svcmi	0x006afa85
d0019718:	9a002101 	bls	0xd0021b24
d001971c:	4638447f 			; <UNDEFINED> instruction: 0x4638447f
d0019720:	fd70f7fc 	ldc2l	7, cr15, [r0, #-1008]!	; 0xfffffc10
d0019724:	0f3df1bb 	svceq	0x003df1bb
d0019728:	f64bd029 			; <UNDEFINED> instruction: 0xf64bd029
d001972c:	46384106 	ldrtmi	r4, [r8], -r6, lsl #2
d0019730:	fa76f7fb 	blx	0xd1dd7724
d0019734:	7392f46f 	orrsvc	pc, r2, #1862270976	; 0x6f000000
d0019738:	eb0b2e0a 	bl	0xd02e4f68
d001973c:	d12d0403 			; <UNDEFINED> instruction: 0xd12d0403
d0019740:	f7fb2180 			; <UNDEFINED> instruction: 0xf7fb2180
d0019744:	2c08fa6d 			; <UNDEFINED> instruction: 0x2c08fa6d
d0019748:	e8dfd821 	ldm	pc, {r0, r5, fp, ip, lr, pc}^	; <UNPREDICTABLE>
d001974c:	4112f004 	tstmi	r2, r4	; <UNPREDICTABLE>
d0019750:	4b462020 	blmi	0xd11a17d8
d0019754:	00555550 	subseq	r5, r5, r0, asr r5
d0019758:	4652485a 			; <UNDEFINED> instruction: 0x4652485a
d001975c:	44782101 	ldrbtmi	r2, [r8], #-257	; 0xfffffeff
d0019760:	f7fb9001 			; <UNDEFINED> instruction: 0xf7fb9001
d0019764:	f646fbd1 			; <UNDEFINED> instruction: 0xf646fbd1
d0019768:	98010108 	stmdals	r1, {r3, r8}
d001976c:	fa58f7fb 	blx	0xd1657760
d0019770:	4855e7cb 	ldmdami	r5, {r0, r1, r3, r6, r7, r8, r9, sl, sp, lr, pc}^
d0019774:	0108f641 	tsteq	r8, r1, asr #12	; <UNPREDICTABLE>
d0019778:	f7fb4478 			; <UNDEFINED> instruction: 0xf7fb4478
d001977c:	2e05fa51 			; <UNDEFINED> instruction: 0x2e05fa51
d0019780:	4852d105 	ldmdami	r2, {r0, r2, r8, ip, lr, pc}^
d0019784:	21c0f24b 	biccs	pc, r0, fp, asr #4
d0019788:	f7fb4478 			; <UNDEFINED> instruction: 0xf7fb4478
d001978c:	2d00fa49 	vstrcs	s30, [r0, #-292]	; 0xfffffedc
d0019790:	484fdb45 	stmdami	pc, {r0, r2, r6, r8, r9, fp, ip, lr, pc}^	; <UNPREDICTABLE>
d0019794:	46292200 	strtmi	r2, [r9], -r0, lsl #4
d0019798:	e7594478 			; <UNDEFINED> instruction: 0xe7594478
d001979c:	d8ee2c08 	stmiale	lr!, {r3, sl, fp, sp}^
d00197a0:	f853a302 			; <UNDEFINED> instruction: 0xf853a302
d00197a4:	44132024 	ldrmi	r2, [r3], #-36	; 0xffffffdc
d00197a8:	bf004718 	svclt	0x00004718
d00197ac:	ffffffc7 			; <UNDEFINED> instruction: 0xffffffc7
d00197b0:	00000025 	andeq	r0, r0, r5, lsr #32
d00197b4:	ffffffd3 			; <UNDEFINED> instruction: 0xffffffd3
d00197b8:	ffffffd3 			; <UNDEFINED> instruction: 0xffffffd3
d00197bc:	0000002f 	andeq	r0, r0, pc, lsr #32
d00197c0:	00000039 	andeq	r0, r0, r9, lsr r0
d00197c4:	00000043 	andeq	r0, r0, r3, asr #32
d00197c8:	0000004d 	andeq	r0, r0, sp, asr #32
d00197cc:	0000004d 	andeq	r0, r0, sp, asr #32
d00197d0:	f6414840 			; <UNDEFINED> instruction: 0xf6414840
d00197d4:	44782108 	ldrbtmi	r2, [r8], #-264	; 0xfffffef8
d00197d8:	483fe7cf 	ldmdami	pc!, {r0, r1, r2, r3, r6, r7, r8, r9, sl, sp, lr, pc}	; <UNPREDICTABLE>
d00197dc:	0108f244 	tsteq	r8, r4, asr #4	; <UNPREDICTABLE>
d00197e0:	e7ca4478 			; <UNDEFINED> instruction: 0xe7ca4478
d00197e4:	f244483d 	vtst.8	d20, d4, d29
d00197e8:	44783108 	ldrbtmi	r3, [r8], #-264	; 0xfffffef8
d00197ec:	483ce7c5 	ldmdami	ip!, {r0, r2, r6, r7, r8, r9, sl, sp, lr, pc}
d00197f0:	0148f244 	cmpeq	r8, r4, asr #4	; <UNPREDICTABLE>
d00197f4:	e7c04478 			; <UNDEFINED> instruction: 0xe7c04478
d00197f8:	f244483a 	vtst.8	d20, d4, d26
d00197fc:	44786102 	ldrbtmi	r6, [r8], #-258	; 0xfffffefe
d0019800:	fa0ef7fb 	blx	0xd03d77f4
d0019804:	6108f244 	tstvs	r8, r4, asr #4	; <UNPREDICTABLE>
d0019808:	fa0af7fb 	blx	0xd02d77fc
d001980c:	0190f244 	orrseq	pc, r0, r4, asr #4
d0019810:	1310f244 	tstne	r0, #68, 4	; 0x40000004	; <UNPREDICTABLE>
d0019814:	7f96f5bb 	svcvc	0x0096f5bb
d0019818:	4619bf18 	sadd16mi	fp, r9, r8
d001981c:	4832e7ad 	ldmdami	r2!, {r0, r2, r3, r5, r7, r8, r9, sl, sp, lr, pc}
d0019820:	21014652 	tstcs	r1, r2, asr r6
d0019824:	90004478 	andls	r4, r0, r8, ror r4
d0019828:	fb6ef7fb 	blx	0xd1bd781e
d001982c:	0108f246 	tsteq	r8, r6, asr #4	; <UNPREDICTABLE>
d0019830:	b0059800 	andlt	r9, r5, r0, lsl #16
d0019834:	4ff0e8bd 	svcmi	0x00f0e8bd
d0019838:	b9f2f7fb 	ldmiblt	r2!, {r0, r1, r3, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}^
d001983c:	9b002e0a 	blls	0xd002506c
d0019840:	2304bf08 	movwcs	fp, #20232	; 0x4f08
d0019844:	e7669300 	strb	r9, [r6, -r0, lsl #6]!
d0019848:	fb022230 	blx	0xd00a2112
d001984c:	f5044405 			; <UNDEFINED> instruction: 0xf5044405
d0019850:	f8943422 			; <UNDEFINED> instruction: 0xf8943422
d0019854:	2a002140 	bcs	0xd0021d5c
d0019858:	ae3cf47f 	mrcge	4, 1, APSR_nzcv, cr12, cr15, {3}
d001985c:	6135f894 	teqvs	r5, r4	; <illegal shifter operand>	; <UNPREDICTABLE>
d0019860:	3afff04f 	bcc	0xd00159a4
d0019864:	bf00e650 	svclt	0x0000e650
d0019868:	00009fe0 	andeq	r9, r0, r0, ror #31
d001986c:	00009fb0 			; <UNDEFINED> instruction: 0x00009fb0
d0019870:	00009f9e 	muleq	r0, lr, pc	; <UNPREDICTABLE>
d0019874:	00009f46 	andeq	r9, r0, r6, asr #30
d0019878:	fffffddb 			; <UNDEFINED> instruction: 0xfffffddb
d001987c:	fffffd9c 			; <UNDEFINED> instruction: 0xfffffd9c
d0019880:	00009f08 	andeq	r9, r0, r8, lsl #30
d0019884:	fffffda9 			; <UNDEFINED> instruction: 0xfffffda9
d0019888:	00009ed4 	ldrdeq	r9, [r0], -r4
d001988c:	00009e92 	muleq	r0, r2, lr
d0019890:	00009e44 	andeq	r9, r0, r4, asr #28
d0019894:	fffffd19 			; <UNDEFINED> instruction: 0xfffffd19
d0019898:	00009e24 	andeq	r9, r0, r4, lsr #28
d001989c:	fffffd1d 			; <UNDEFINED> instruction: 0xfffffd1d
d00198a0:	00009e10 	andeq	r9, r0, r0, lsl lr
d00198a4:	fffffd19 			; <UNDEFINED> instruction: 0xfffffd19
d00198a8:	fffffd10 			; <UNDEFINED> instruction: 0xfffffd10
d00198ac:	fffffd17 			; <UNDEFINED> instruction: 0xfffffd17
d00198b0:	fffffd13 			; <UNDEFINED> instruction: 0xfffffd13
d00198b4:	fffffd08 			; <UNDEFINED> instruction: 0xfffffd08
d00198b8:	00009d18 	andeq	r9, r0, r8, lsl sp
d00198bc:	00009d0c 	andeq	r9, r0, ip, lsl #26
d00198c0:	00009d00 	andeq	r9, r0, r0, lsl #26
d00198c4:	00009cbe 			; <UNDEFINED> instruction: 0x00009cbe
d00198c8:	00009ca4 	andeq	r9, r0, r4, lsr #25
d00198cc:	00009c94 	muleq	r0, r4, ip
d00198d0:	00009c84 	andeq	r9, r0, r4, lsl #25
d00198d4:	00009c46 	andeq	r9, r0, r6, asr #24
d00198d8:	00009c3c 	andeq	r9, r0, ip, lsr ip
d00198dc:	00009c32 	andeq	r9, r0, r2, lsr ip
d00198e0:	00009c28 	andeq	r9, r0, r8, lsr #24
d00198e4:	00009c1e 	andeq	r9, r0, lr, lsl ip
d00198e8:	00009bf8 	strdeq	r9, [r0], -r8

Disassembly of section .text.initialize_scalar.constprop.0:

d001994c <.text.initialize_scalar.constprop.0>:
d001994c:	4ff0e92d 	svcmi	0x00f0e92d
d0019950:	4607b087 	strmi	fp, [r7], -r7, lsl #1
d0019954:	9203460e 	andls	r4, r3, #14680064	; 0xe00000
d0019958:	4c31b971 			; <UNDEFINED> instruction: 0x4c31b971
d001995c:	447c2201 	ldrbtmi	r2, [ip], #-513	; 0xfffffdff
d0019960:	46204611 			; <UNDEFINED> instruction: 0x46204611
d0019964:	fc4ef7fc 	mcrr2	7, 15, pc, lr, cr12	; <UNPREDICTABLE>
d0019968:	46394632 			; <UNDEFINED> instruction: 0x46394632
d001996c:	b0074620 	andlt	r4, r7, r0, lsr #12
d0019970:	4ff0e8bd 	svcmi	0x00f0e8bd
d0019974:	ba03f7fb 	blt	0xd0117968
d0019978:	212d4c2a 			; <UNDEFINED> instruction: 0x212d4c2a
d001997c:	4620447c 			; <UNDEFINED> instruction: 0x4620447c
d0019980:	fa53f7f9 	blx	0xd151796c
d0019984:	69e269a3 	stmibvs	r2!, {r0, r1, r5, r7, r8, fp, sp, lr}^
d0019988:	718df44f 	orrvc	pc, sp, pc, asr #8
d001998c:	6b639305 	blvs	0xd18fe5a8
d0019990:	46209002 	strtmi	r9, [r0], -r2
d0019994:	93019204 	movwls	r9, #4612	; 0x1204
d0019998:	9030f894 	mlasls	r0, r4, r8, pc	; <UNPREDICTABLE>
d001999c:	5b08e9d4 	blpl	0xd02540f4
d00199a0:	a80ae9d4 	stmdage	sl, {r2, r4, r6, r7, r8, fp, sp, lr, pc}
d00199a4:	fa41f7f9 	blx	0xd1097990
d00199a8:	9b059a04 	blls	0xd01801c0
d00199ac:	4620b188 	strtmi	fp, [r0], -r8, lsl #3
d00199b0:	ffd8f7f9 			; <UNDEFINED> instruction: 0xffd8f7f9
d00199b4:	9b024605 	blls	0xd00ab1d0
d00199b8:	426db103 	rsbmi	fp, sp, #-1073741824	; 0xc0000000
d00199bc:	b3639b03 	cmnlt	r3, #3072	; 0xc00
d00199c0:	d92a2dff 	stmdble	sl!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, sl, fp, sp}
d00199c4:	447b4b18 	ldrbtmi	r4, [fp], #-2840	; 0xfffff4e8
d00199c8:	b9ba6d9a 	ldmiblt	sl!, {r1, r3, r4, r7, r8, sl, fp, sp, lr}
d00199cc:	447a4a17 	ldrbtmi	r4, [sl], #-2583	; 0xfffff5e9
d00199d0:	f240e00e 	vhadd.s8	d30, d0, d14
d00199d4:	45881101 	strmi	r1, [r8, #257]	; 0x101
d00199d8:	4619d113 			; <UNDEFINED> instruction: 0x4619d113
d00199dc:	f7f64620 			; <UNDEFINED> instruction: 0xf7f64620
d00199e0:	b9c0ff73 	stmiblt	r0, {r0, r1, r4, r5, r6, r8, r9, sl, fp, ip, sp, lr, pc}^
d00199e4:	447b4b12 	ldrbtmi	r4, [fp], #-2834	; 0xfffff4ee
d00199e8:	b93a6d9a 	ldmdblt	sl!, {r1, r3, r4, r7, r8, sl, fp, sp, lr}
d00199ec:	447a4a11 	ldrbtmi	r4, [sl], #-2577	; 0xfffff5ef
d00199f0:	2b16e9c3 	blcs	0xd05d4104
d00199f4:	e9c39a01 	stmib	r3, {r0, r9, fp, ip, pc}^
d00199f8:	669aa918 			; <UNDEFINED> instruction: 0x669aa918
d00199fc:	e8bdb007 	pop	{r0, r1, r2, ip, sp, pc}
d0019a00:	f5a88ff0 			; <UNDEFINED> instruction: 0xf5a88ff0
d0019a04:	f1b87881 			; <UNDEFINED> instruction: 0xf1b87881
d0019a08:	d8eb0f01 	stmiale	fp!, {r0, r8, r9, sl, fp}^
d0019a0c:	4478480a 	ldrbtmi	r4, [r8], #-2058	; 0xfffff7f6
d0019a10:	f9f0f7f9 			; <UNDEFINED> instruction: 0xf9f0f7f9
d0019a14:	6a05e7cf 	bvs	0xd0193958
d0019a18:	f846e7f8 			; <UNDEFINED> instruction: 0xf846e7f8
d0019a1c:	e7ed5027 	strb	r5, [sp, r7, lsr #32]!
d0019a20:	00009abe 			; <UNDEFINED> instruction: 0x00009abe
d0019a24:	00009aa0 	andeq	r9, r0, r0, lsr #21
d0019a28:	00009a56 	andeq	r9, r0, r6, asr sl
d0019a2c:	ffffff51 			; <UNDEFINED> instruction: 0xffffff51
d0019a30:	00009a36 	andeq	r9, r0, r6, lsr sl
d0019a34:	fffffefa 			; <UNDEFINED> instruction: 0xfffffefa
d0019a38:	00009a0e 	andeq	r9, r0, lr, lsl #20

Disassembly of section .text.initialize_record.constprop.0:

d0019b3c <.text.initialize_record.constprop.0>:
d0019b3c:	e92d2b21 	push	{r0, r5, r8, r9, fp, sp}
d0019b40:	46804ff7 			; <UNDEFINED> instruction: 0x46804ff7
d0019b44:	4615468b 	ldrmi	r4, [r5], -fp, lsl #13
d0019b48:	d108469a 			; <UNDEFINED> instruction: 0xd108469a
d0019b4c:	485c495b 	ldmdami	ip, {r0, r1, r3, r4, r6, r8, fp, lr}^
d0019b50:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d0019b54:	e8bdb003 	pop	{r0, r1, ip, sp, pc}
d0019b58:	f7f64ff0 			; <UNDEFINED> instruction: 0xf7f64ff0
d0019b5c:	4e59bb25 	vnmlsmi.f64	d27, d9, d21
d0019b60:	4a59217b 	bmi	0xd1662154
d0019b64:	447a447e 	ldrbtmi	r4, [sl], #-1150	; 0xfffffb82
d0019b68:	f7f94630 			; <UNDEFINED> instruction: 0xf7f94630
d0019b6c:	2800f96c 	stmdacs	r0, {r2, r3, r5, r6, r8, fp, ip, sp, lr, pc}
d0019b70:	80a0f000 	adchi	pc, r0, r0
d0019b74:	731af44f 	tstvc	sl, #1325400064	; 0x4f000000	; <UNPREDICTABLE>
d0019b78:	0900f04f 	stmdbeq	r0, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d0019b7c:	f808fb03 			; <UNDEFINED> instruction: 0xf808fb03
d0019b80:	34c8f508 	strbcc	pc, [r8], #1288	; 0x508	; <UNPREDICTABLE>
d0019b84:	443434c8 	ldrtmi	r3, [r4], #-1224	; 0xfffffb38
d0019b88:	2b006db3 	blcs	0xd003525c
d0019b8c:	6af3d13d 	bvs	0xcfd0e088
d0019b90:	d03a2b7d 	eorsle	r2, sl, sp, ror fp
d0019b94:	7f80f5b3 	svcvc	0x0080f5b3
d0019b98:	eb06d037 	bl	0xd01cdc7c
d0019b9c:	f5020208 			; <UNDEFINED> instruction: 0xf5020208
d0019ba0:	f89232c9 			; <UNDEFINED> instruction: 0xf89232c9
d0019ba4:	4549110a 	strbmi	r1, [r9, #-266]	; 0xfffffef6
d0019ba8:	f892d905 			; <UNDEFINED> instruction: 0xf892d905
d0019bac:	b13a210b 	teqlt	sl, fp, lsl #2
d0019bb0:	0f00f1b9 	svceq	0x0000f1b9
d0019bb4:	4945d004 	stmdbmi	r5, {r2, ip, lr, pc}^
d0019bb8:	44794845 	ldrbtmi	r4, [r9], #-2117	; 0xfffff7bb
d0019bbc:	e7c94478 			; <UNDEFINED> instruction: 0xe7c94478
d0019bc0:	f8948c67 			; <UNDEFINED> instruction: 0xf8948c67
d0019bc4:	f8942021 			; <UNDEFINED> instruction: 0xf8942021
d0019bc8:	445f0020 	ldrbmi	r0, [pc], #-32	; 0xd0019bd0
d0019bcc:	d0512a00 	subsle	r2, r1, r0, lsl #20
d0019bd0:	d03a2d00 	eorsle	r2, sl, r0, lsl #26
d0019bd4:	4a404b3f 	bmi	0xd102c8d8
d0019bd8:	447a447b 	ldrbtmi	r4, [sl], #-1147	; 0xfffffb85
d0019bdc:	e9d39301 	ldmib	r3, {r0, r8, r9, ip, pc}^
d0019be0:	f7f60106 			; <UNDEFINED> instruction: 0xf7f60106
d0019be4:	9b01fe3e 	blls	0xd00994e4
d0019be8:	4618b1c8 	ldrmi	fp, [r8], -r8, asr #3
d0019bec:	f902f7f9 			; <UNDEFINED> instruction: 0xf902f7f9
d0019bf0:	f8452300 			; <UNDEFINED> instruction: 0xf8452300
d0019bf4:	48393027 	ldmdami	r9!, {r0, r1, r2, r5, ip, sp}
d0019bf8:	f109212c 			; <UNDEFINED> instruction: 0xf109212c
d0019bfc:	34240901 	strtcc	r0, [r4], #-2305	; 0xfffff6ff
d0019c00:	f7f94478 			; <UNDEFINED> instruction: 0xf7f94478
d0019c04:	2800f912 	stmdacs	r0, {r1, r4, r8, fp, ip, sp, lr, pc}
d0019c08:	4a35d1be 	bmi	0xd0d8e308
d0019c0c:	4835217d 	ldmdami	r5!, {r0, r2, r3, r4, r5, r6, r8, sp}
d0019c10:	4478447a 	ldrbtmi	r4, [r8], #-1146	; 0xfffffb86
d0019c14:	e8bdb003 	pop	{r0, r1, ip, sp, pc}
d0019c18:	f7f94ff0 			; <UNDEFINED> instruction: 0xf7f94ff0
d0019c1c:	6adab914 	bvs	0xcf6c8074
d0019c20:	7281f5a2 	addvc	pc, r1, #679477248	; 0x28800000
d0019c24:	d8092a01 	stmdale	r9, {r0, r9, fp, sp}
d0019c28:	b93a6a1a 	ldmdblt	sl!, {r1, r3, r4, r9, fp, sp, lr}
d0019c2c:	92014618 	andls	r4, r1, #24, 12	; 0x1800000
d0019c30:	f8e0f7f9 			; <UNDEFINED> instruction: 0xf8e0f7f9
d0019c34:	f8459a01 			; <UNDEFINED> instruction: 0xf8459a01
d0019c38:	e7dc2027 	ldrb	r2, [ip, r7, lsr #32]
d0019c3c:	482b492a 	stmdami	fp!, {r1, r3, r5, r8, fp, lr}
d0019c40:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d0019c44:	fab0f7f6 	blx	0xcec57c24
d0019c48:	28ffe7d5 	ldmcs	pc!, {r0, r2, r4, r6, r7, r8, r9, sl, sp, lr, pc}^	; <UNPREDICTABLE>
d0019c4c:	4828d10c 	stmdami	r8!, {r2, r3, r8, ip, lr, pc}
d0019c50:	21012204 	tstcs	r1, r4, lsl #4
d0019c54:	f7fc4478 			; <UNDEFINED> instruction: 0xf7fc4478
d0019c58:	4826fad5 	stmdami	r6!, {r0, r2, r4, r6, r7, r9, fp, ip, sp, lr, pc}
d0019c5c:	46392200 	ldrtmi	r2, [r9], -r0, lsl #4
d0019c60:	f7fb4478 			; <UNDEFINED> instruction: 0xf7fb4478
d0019c64:	e7c6f88c 	strb	pc, [r6, ip, lsl #17]	; <UNPREDICTABLE>
d0019c68:	48234601 	stmdami	r3!, {r0, r9, sl, lr}
d0019c6c:	f7fd4478 			; <UNDEFINED> instruction: 0xf7fd4478
d0019c70:	e7f2feeb 	ldrb	pc, [r2, fp, ror #29]!	; <UNPREDICTABLE>
d0019c74:	d10428ff 	strdle	r2, [r4, -pc]
d0019c78:	46384629 	ldrtmi	r4, [r8], -r9, lsr #12
d0019c7c:	fe66f7ff 	mcr2	7, 3, pc, cr6, cr15, {7}	; <UNPREDICTABLE>
d0019c80:	2b7be7b9 	blcs	0xd1f13b6c
d0019c84:	f10ad106 			; <UNDEFINED> instruction: 0xf10ad106
d0019c88:	462a0301 	strtmi	r0, [sl], -r1, lsl #6
d0019c8c:	f7ff4639 			; <UNDEFINED> instruction: 0xf7ff4639
d0019c90:	e7b0ff55 	sbfx	pc, r5, #30, #17
d0019c94:	7381f5a3 	orrvc	pc, r1, #683671552	; 0x28c00000
d0019c98:	d8062b01 	stmdale	r6, {r0, r8, r9, fp, sp}
d0019c9c:	44784817 	ldrbtmi	r4, [r8], #-2071	; 0xfffff7e9
d0019ca0:	b9136a03 	ldmdblt	r3, {r0, r1, r9, fp, sp, lr}
d0019ca4:	f8a6f7f9 			; <UNDEFINED> instruction: 0xf8a6f7f9
d0019ca8:	4915e7a5 	ldmdbmi	r5, {r0, r2, r5, r7, r8, r9, sl, sp, lr, pc}
d0019cac:	44794815 	ldrbtmi	r4, [r9], #-2069	; 0xfffff7eb
d0019cb0:	e74f4478 	smlsldx	r4, pc, r8, r4	; <UNPREDICTABLE>
d0019cb4:	e8bdb003 	pop	{r0, r1, ip, sp, pc}
d0019cb8:	bf008ff0 	svclt	0x00008ff0
d0019cbc:	fffffee8 			; <UNDEFINED> instruction: 0xfffffee8
d0019cc0:	000098ca 	andeq	r9, r0, sl, asr #17
d0019cc4:	000098b8 			; <UNDEFINED> instruction: 0x000098b8
d0019cc8:	fffffef2 			; <UNDEFINED> instruction: 0xfffffef2
d0019ccc:	fffffec2 			; <UNDEFINED> instruction: 0xfffffec2
d0019cd0:	00009860 	andeq	r9, r0, r0, ror #16
d0019cd4:	00009844 	andeq	r9, r0, r4, asr #16
d0019cd8:	ffffb102 			; <UNDEFINED> instruction: 0xffffb102
d0019cdc:	0000981c 	andeq	r9, r0, ip, lsl r8
d0019ce0:	ffffff00 			; <UNDEFINED> instruction: 0xffffff00
d0019ce4:	0000980a 	andeq	r9, r0, sl, lsl #16
d0019ce8:	fffffe66 			; <UNDEFINED> instruction: 0xfffffe66
d0019cec:	000097da 	ldrdeq	r9, [r0], -sl
d0019cf0:	000097c8 	andeq	r9, r0, r8, asr #15
d0019cf4:	000097bc 			; <UNDEFINED> instruction: 0x000097bc
d0019cf8:	000097b0 			; <UNDEFINED> instruction: 0x000097b0
d0019cfc:	0000977e 	andeq	r9, r0, lr, ror r7
d0019d00:	fffffe31 			; <UNDEFINED> instruction: 0xfffffe31
d0019d04:	0000976c 	andeq	r9, r0, ip, ror #14

Disassembly of section .text.initialize_array.constprop.0:

d0019da0 <.text.initialize_array.constprop.0>:
d0019da0:	4ff7e92d 	svcmi	0x00f7e92d
d0019da4:	46154e36 			; <UNDEFINED> instruction: 0x46154e36
d0019da8:	460c4a36 			; <UNDEFINED> instruction: 0x460c4a36
d0019dac:	9001447e 	andls	r4, r1, lr, ror r4
d0019db0:	217b447a 	cmncs	fp, sl, ror r4
d0019db4:	461f4630 			; <UNDEFINED> instruction: 0x461f4630
d0019db8:	a030f8dd 	ldrsbtge	pc, [r0], -sp	; <UNPREDICTABLE>
d0019dbc:	f843f7f9 			; <UNDEFINED> instruction: 0xf843f7f9
d0019dc0:	d05a2800 	subsle	r2, sl, r0, lsl #16
d0019dc4:	f8df2cff 			; <UNDEFINED> instruction: 0xf8df2cff
d0019dc8:	f04fb0c0 			; <UNDEFINED> instruction: 0xf04fb0c0
d0019dcc:	bf140800 	svclt	0x00140800
d0019dd0:	701af44f 	andsvc	pc, sl, pc, asr #8
d0019dd4:	0901f04f 	stmdbeq	r1, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d0019dd8:	bf1844fb 	svclt	0x001844fb
d0019ddc:	6004fb00 	andvs	pc, r4, r0, lsl #22
d0019de0:	bf184e2a 	svclt	0x00184e2a
d0019de4:	30c9f500 	sbccc	pc, r9, r0, lsl #10
d0019de8:	bf18447e 	svclt	0x0018447e
d0019dec:	9108f8b0 			; <UNDEFINED> instruction: 0x9108f8b0
d0019df0:	bb036db3 	bllt	0xd00f54c4
d0019df4:	2b7d6af3 	blcs	0xd1f749c8
d0019df8:	f5b3d01d 			; <UNDEFINED> instruction: 0xf5b3d01d
d0019dfc:	d01a7f80 	andsle	r7, sl, r0, lsl #31
d0019e00:	45429a01 	strbmi	r9, [r2, #-2561]	; 0xfffff5ff
d0019e04:	4922d107 	stmdbmi	r2!, {r0, r1, r2, r8, ip, lr, pc}
d0019e08:	44794630 	ldrbtmi	r4, [r9], #-1584	; 0xfffff9d0
d0019e0c:	e8bdb003 	pop	{r0, r1, ip, sp, pc}
d0019e10:	f7f64ff0 			; <UNDEFINED> instruction: 0xf7f64ff0
d0019e14:	2cffb9c9 			; <UNDEFINED> instruction: 0x2cffb9c9
d0019e18:	4652d117 			; <UNDEFINED> instruction: 0x4652d117
d0019e1c:	46284639 			; <UNDEFINED> instruction: 0x46284639
d0019e20:	fd94f7ff 	ldc2	7, cr15, [r4, #1020]	; 0x3fc
d0019e24:	4658212c 	ldrbmi	r2, [r8], -ip, lsr #2
d0019e28:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d0019e2c:	f7f8444d 			; <UNDEFINED> instruction: 0xf7f8444d
d0019e30:	2800fffc 	stmdacs	r0, {r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0019e34:	4a17d1dc 	bmi	0xd060e5ac
d0019e38:	4817217d 	ldmdami	r7, {r0, r2, r3, r4, r5, r6, r8, sp}
d0019e3c:	4478447a 	ldrbtmi	r4, [r8], #-1146	; 0xfffffb86
d0019e40:	e8bdb003 	pop	{r0, r1, ip, sp, pc}
d0019e44:	f7f84ff0 			; <UNDEFINED> instruction: 0xf7f84ff0
d0019e48:	2b7bbffe 	blcs	0xd1f09e48
d0019e4c:	2301d106 	movwcs	sp, #4358	; 0x1106
d0019e50:	4629463a 			; <UNDEFINED> instruction: 0x4629463a
d0019e54:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0019e58:	e7e3fe71 			; <UNDEFINED> instruction: 0xe7e3fe71
d0019e5c:	7381f5a3 	orrvc	pc, r1, #683671552	; 0x28c00000
d0019e60:	d8052b01 	stmdale	r5, {r0, r8, r9, fp, sp}
d0019e64:	b91b6a33 	ldmdblt	fp, {r0, r1, r4, r5, r9, fp, sp, lr}
d0019e68:	f7f84630 			; <UNDEFINED> instruction: 0xf7f84630
d0019e6c:	e7d9ffc3 	ldrb	pc, [r9, r3, asr #31]	; <UNPREDICTABLE>
d0019e70:	480b490a 	stmdami	fp, {r1, r3, r8, fp, lr}
d0019e74:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d0019e78:	b003e7c8 	andlt	lr, r3, r8, asr #15
d0019e7c:	8ff0e8bd 	svchi	0x00f0e8bd
d0019e80:	00009670 	andeq	r9, r0, r0, ror r6
d0019e84:	ffffff54 			; <UNDEFINED> instruction: 0xffffff54
d0019e88:	00009644 	andeq	r9, r0, r4, asr #12
d0019e8c:	00009634 	andeq	r9, r0, r4, lsr r6
d0019e90:	ffffff1d 			; <UNDEFINED> instruction: 0xffffff1d
d0019e94:	ffffff39 			; <UNDEFINED> instruction: 0xffffff39
d0019e98:	000095de 	ldrdeq	r9, [r0], -lr
d0019e9c:	fffffed7 			; <UNDEFINED> instruction: 0xfffffed7
d0019ea0:	000095a6 	andeq	r9, r0, r6, lsr #11

Disassembly of section .text.local_declaration.constprop.0:

d001a138 <.text.local_declaration.constprop.0>:
d001a138:	4ff0e92d 	svcmi	0x00f0e92d
d001a13c:	4694f8df 			; <UNDEFINED> instruction: 0x4694f8df
d001a140:	f44fb097 	vst4.32	{d27-d30}, [pc :64], r7
d001a144:	447c7185 	ldrbtmi	r7, [ip], #-389	; 0xfffffe7b
d001a148:	f7f84620 			; <UNDEFINED> instruction: 0xf7f84620
d001a14c:	6ae2fe6e 	bvs	0xcf8d9b0c
d001a150:	131bf240 	tstne	fp, #64, 4	; <UNPREDICTABLE>
d001a154:	429a4605 	addsmi	r4, sl, #5242880	; 0x500000
d001a158:	4620d109 	strtmi	sp, [r0], -r9, lsl #2
d001a15c:	f966f7f9 			; <UNDEFINED> instruction: 0xf966f7f9
d001a160:	d1472800 	cmple	r7, r0, lsl #16
d001a164:	46282501 	strtmi	r2, [r8], -r1, lsl #10
d001a168:	e8bdb017 	pop	{r0, r1, r2, r4, ip, sp, pc}
d001a16c:	f2408ff0 	vrecps.f32	q12, q8, q8
d001a170:	46201107 	strtmi	r1, [r0], -r7, lsl #2
d001a174:	fe59f7f8 	mrc2	7, 2, pc, cr9, cr8, {7}
d001a178:	6ae3b1f8 	bvs	0xcf906960
d001a17c:	d1062b28 	tstle	r6, r8, lsr #22
d001a180:	2b2a6ce3 	blcs	0xd0ab5514
d001a184:	2000d103 	andcs	sp, r0, r3, lsl #2
d001a188:	f8b8f7fb 			; <UNDEFINED> instruction: 0xf8b8f7fb
d001a18c:	f8dfe7ea 			; <UNDEFINED> instruction: 0xf8dfe7ea
d001a190:	212a4648 			; <UNDEFINED> instruction: 0x212a4648
d001a194:	4620447c 			; <UNDEFINED> instruction: 0x4620447c
d001a198:	fe47f7f8 	mcr2	7, 2, pc, cr7, cr8, {7}	; <UNPREDICTABLE>
d001a19c:	212ab350 			; <UNDEFINED> instruction: 0x212ab350
d001a1a0:	f7f84620 			; <UNDEFINED> instruction: 0xf7f84620
d001a1a4:	2800fe42 	stmdacs	r0, {r1, r6, r9, sl, fp, ip, sp, lr, pc}
d001a1a8:	f04fbf0c 			; <UNDEFINED> instruction: 0xf04fbf0c
d001a1ac:	f04f0a0a 			; <UNDEFINED> instruction: 0xf04f0a0a
d001a1b0:	2d000a13 	vstrcs	s0, [r0, #-76]	; 0xffffffb4
d001a1b4:	81f7f040 	mvnshi	pc, r0, asr #32
d001a1b8:	6ae2e01e 	bvs	0xcf8d2238
d001a1bc:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d001a1c0:	d14d429a 			; <UNDEFINED> instruction: 0xd14d429a
d001a1c4:	e9d44620 	ldmib	r4, {r5, r9, sl, lr}^
d001a1c8:	f7f61206 			; <UNDEFINED> instruction: 0xf7f61206
d001a1cc:	2800fade 	stmdacs	r0, {r1, r2, r3, r4, r6, r7, r9, fp, ip, sp, lr, pc}
d001a1d0:	4620db46 	strtmi	sp, [r0], -r6, asr #22
d001a1d4:	1206e9d4 	andne	lr, r6, #212, 18	; 0x350000
d001a1d8:	fad7f7f6 	blx	0xcf6181b8
d001a1dc:	fb032324 	blx	0xd00e2e76
d001a1e0:	f5004000 			; <UNDEFINED> instruction: 0xf5004000
d001a1e4:	f89030e5 			; <UNDEFINED> instruction: 0xf89030e5
d001a1e8:	2bff308c 	blcs	0xcffe6420
d001a1ec:	4620d138 			; <UNDEFINED> instruction: 0x4620d138
d001a1f0:	fe00f7f8 	mcr2	7, 0, pc, cr0, cr8, {7}	; <UNPREDICTABLE>
d001a1f4:	0a00f04f 	beq	0xd0056338
d001a1f8:	45e0f8df 	strbmi	pc, [r0, #2271]!	; 0x8df	; <UNPREDICTABLE>
d001a1fc:	447cae0e 	ldrbtmi	sl, [ip], #-3598	; 0xfffff1f2
d001a200:	0718f104 	ldreq	pc, [r8, -r4, lsl #2]
d001a204:	b024f8d4 	ldrdlt	pc, [r4], -r4	; <UNPREDICTABLE>
d001a208:	9028f8d4 	ldrdls	pc, [r8], -r4	; <UNPREDICTABLE>
d001a20c:	8030f894 	mlashi	r0, r4, r8, pc	; <UNPREDICTABLE>
d001a210:	c60fcf0f 	strgt	ip, [pc], -pc, lsl #30
d001a214:	000fe897 	muleq	pc, r7, r8	; <UNPREDICTABLE>
d001a218:	000fe886 	andeq	lr, pc, r6, lsl #17
d001a21c:	25c0f8df 	strbcs	pc, [r0, #2271]	; 0x8df	; <UNPREDICTABLE>
d001a220:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d001a224:	6b674620 	blvs	0xd19ebaac
d001a228:	ae0e447a 	mcrge	4, 0, r4, cr14, cr10, {3}
d001a22c:	fe0bf7f8 	mcr2	7, 0, pc, cr11, cr8, {7}	; <UNPREDICTABLE>
d001a230:	d0972800 	addsle	r2, r7, r0, lsl #16
d001a234:	4620215b 			; <UNDEFINED> instruction: 0x4620215b
d001a238:	fdf7f7f8 	ldc2l	7, cr15, [r7, #992]!	; 0x3e0
d001a23c:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d001a240:	2d008271 	sfmcs	f0, 1, [r0, #-452]	; 0xfffffe3c
d001a244:	81d1f000 	bicshi	pc, r1, r0
d001a248:	2b006da3 	blcs	0xd00358dc
d001a24c:	f8dfd18a 			; <UNDEFINED> instruction: 0xf8dfd18a
d001a250:	447b3594 	ldrbtmi	r3, [fp], #-1428	; 0xfffffa6c
d001a254:	e9c466a7 	stmib	r4, {r0, r1, r2, r5, r7, r9, sl, sp, lr}^
d001a258:	e9c43b16 	stmib	r4, {r1, r2, r4, r8, r9, fp, ip, sp}^
d001a25c:	e7819818 	usada8	r1, r8, r8, r9
d001a260:	6584f8df 	strvs	pc, [r4, #2271]	; 0x8df
d001a264:	7184f44f 	orrvc	pc, r4, pc, asr #8
d001a268:	4630447e 			; <UNDEFINED> instruction: 0x4630447e
d001a26c:	fdddf7f8 	ldc2l	7, cr15, [sp, #992]	; 0x3e0
d001a270:	b1804604 	orrlt	r4, r0, r4, lsl #12
d001a274:	2b286af3 	blcs	0xd0a34e48
d001a278:	6cf3d104 	ldfvsp	f5, [r3], #16
d001a27c:	d1012b2a 	tstle	r1, sl, lsr #22
d001a280:	e7812001 	str	r2, [r1, r1]
d001a284:	1564f8df 	strbne	pc, [r4, #-2271]!	; 0xfffff721	; <UNPREDICTABLE>
d001a288:	0564f8df 	strbeq	pc, [r4, #-2271]!	; 0xfffff721	; <UNPREDICTABLE>
d001a28c:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d001a290:	ff8af7f5 			; <UNDEFINED> instruction: 0xff8af7f5
d001a294:	4630e766 	ldrtmi	lr, [r0], -r6, ror #14
d001a298:	fa9bf7f6 	blx	0xce718278
d001a29c:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d001a2a0:	a90d817a 	stmdbge	sp, {r1, r3, r4, r5, r6, r8, pc}
d001a2a4:	940d4630 	strls	r4, [sp], #-1584	; 0xfffff9d0
d001a2a8:	ffcaf7f8 			; <UNDEFINED> instruction: 0xffcaf7f8
d001a2ac:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001a2b0:	212aaf59 			; <UNDEFINED> instruction: 0x212aaf59
d001a2b4:	f7f84630 			; <UNDEFINED> instruction: 0xf7f84630
d001a2b8:	4605fdb8 			; <UNDEFINED> instruction: 0x4605fdb8
d001a2bc:	d06d2800 	rsble	r2, sp, r0, lsl #16
d001a2c0:	4630212a 	ldrtmi	r2, [r0], -sl, lsr #2
d001a2c4:	fdb1f7f8 	ldc2	7, cr15, [r1, #992]!	; 0x3e0
d001a2c8:	bf181e03 	svclt	0x00181e03
d001a2cc:	93092301 	movwls	r2, #37633	; 0x9301
d001a2d0:	6520f8df 	strvs	pc, [r0, #-2271]!	; 0xfffff721
d001a2d4:	447eaf0e 	ldrbtmi	sl, [lr], #-3854	; 0xfffff0f2
d001a2d8:	0c18f106 	ldfeqd	f7, [r8], {6}
d001a2dc:	b024f8d6 	ldrdlt	pc, [r4], -r6	; <UNPREDICTABLE>
d001a2e0:	a028f8d6 	ldrdge	pc, [r8], -r6	; <UNPREDICTABLE>
d001a2e4:	9030f896 	mlasls	r0, r6, r8, pc	; <UNPREDICTABLE>
d001a2e8:	8034f8d6 	ldrsbthi	pc, [r4], -r6	; <UNPREDICTABLE>
d001a2ec:	000fe8bc 			; <UNDEFINED> instruction: 0x000fe8bc
d001a2f0:	e89cc70f 	ldm	ip, {r0, r1, r2, r3, r8, r9, sl, lr, pc}
d001a2f4:	e887000f 	stm	r7, {r0, r1, r2, r3}
d001a2f8:	f8df000f 			; <UNDEFINED> instruction: 0xf8df000f
d001a2fc:	f24024fc 	vqshl.s8	q9, q14, q8
d001a300:	46301101 	ldrtmi	r1, [r0], -r1, lsl #2
d001a304:	447aaf0e 	ldrbtmi	sl, [sl], #-3854	; 0xfffff0f2
d001a308:	fd9df7f8 	ldc2	7, cr15, [sp, #992]	; 0x3e0
d001a30c:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001a310:	b935af29 	ldmdblt	r5!, {r0, r3, r5, r8, r9, sl, fp, sp, pc}
d001a314:	4630215b 			; <UNDEFINED> instruction: 0x4630215b
d001a318:	fd87f7f8 	stc2	7, cr15, [r7, #992]	; 0x3e0
d001a31c:	bf181e04 	svclt	0x00181e04
d001a320:	f8df2401 			; <UNDEFINED> instruction: 0xf8df2401
d001a324:	f44f04d8 	vst3.<illegal width 64>	{d16-d18}, [pc :64], r8
d001a328:	9b0d721a 	blls	0xd0376b98
d001a32c:	fb024478 	blx	0xd00ab516
d001a330:	f5020203 			; <UNDEFINED> instruction: 0xf5020203
d001a334:	f8b232c9 			; <UNDEFINED> instruction: 0xf8b232c9
d001a338:	92082108 	andls	r2, r8, #8, 2
d001a33c:	d05e2c00 	subsle	r2, lr, r0, lsl #24
d001a340:	f5a26ac2 			; <UNDEFINED> instruction: 0xf5a26ac2
d001a344:	2a017281 	bcs	0xd0076d50
d001a348:	6a06d807 	bvs	0xd01d036c
d001a34c:	2240b12e 	subcs	fp, r0, #-2147483637	; 0x8000000b
d001a350:	fbb29908 	blx	0xcecc077a
d001a354:	4296f2f1 	addsmi	pc, r6, #268435471	; 0x1000000f
d001a358:	f8dfd926 			; <UNDEFINED> instruction: 0xf8dfd926
d001a35c:	f44f24a4 	vst3.32	{d18-d20}, [pc :128], r4
d001a360:	447a711a 	ldrbtmi	r7, [sl], #-282	; 0xfffffee6
d001a364:	2303fb01 	movwcs	pc, #15105	; 0x3b01	; <UNPREDICTABLE>
d001a368:	33c9f503 	biccc	pc, r9, #12582912	; 0xc00000
d001a36c:	310bf893 			; <UNDEFINED> instruction: 0x310bf893
d001a370:	f8dfb9b3 			; <UNDEFINED> instruction: 0xf8dfb9b3
d001a374:	447a2490 	ldrbtmi	r2, [sl], #-1168	; 0xfffffb70
d001a378:	348cf8df 	strcc	pc, [ip], #2271	; 0x8df
d001a37c:	6d99447b 	cfldrsvs	mvf4, [r9, #492]	; 0x1ec
d001a380:	f47f2900 			; <UNDEFINED> instruction: 0xf47f2900
d001a384:	6a5daeef 	bvs	0xd1785f48
d001a388:	6b596a9c 	blvs	0xd1674e00
d001a38c:	0030f893 	mlaseq	r0, r3, r8, pc	; <UNPREDICTABLE>
d001a390:	e9c36699 	stmib	r3, {r0, r3, r4, r7, r9, sl, sp, lr}^
d001a394:	e9c32516 	stmib	r3, {r1, r2, r4, r8, sl, sp}^
d001a398:	e6e34018 	usat	r4, #3, r8
d001a39c:	e7979009 	ldr	r9, [r7, r9]
d001a3a0:	2468f8df 	strbtcs	pc, [r8], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d001a3a4:	e7e7447a 			; <UNDEFINED> instruction: 0xe7e7447a
d001a3a8:	f7f89007 			; <UNDEFINED> instruction: 0xf7f89007
d001a3ac:	f8dffd23 			; <UNDEFINED> instruction: 0xf8dffd23
d001a3b0:	215d2460 	cmpcs	sp, r0, ror #8
d001a3b4:	447a9807 	ldrbtmi	r9, [sl], #-2055	; 0xfffff7f9
d001a3b8:	fd45f7f8 	stc2l	7, cr15, [r5, #-992]	; 0xfffffc20
d001a3bc:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001a3c0:	b9f5aed1 	ldmiblt	r5!, {r0, r4, r6, r7, r9, sl, fp, sp, pc}^
d001a3c4:	43739b08 	cmnmi	r3, #8, 22	; 0x2000
d001a3c8:	f8df9307 			; <UNDEFINED> instruction: 0xf8df9307
d001a3cc:	99073448 	stmdbls	r7, {r3, r6, sl, ip, sp}
d001a3d0:	f503447b 			; <UNDEFINED> instruction: 0xf503447b
d001a3d4:	f8d23225 			; <UNDEFINED> instruction: 0xf8d23225
d001a3d8:	f1c22114 			; <UNDEFINED> instruction: 0xf1c22114
d001a3dc:	428a0240 	addmi	r0, sl, #64, 4
d001a3e0:	6d9ad211 	lfmvs	f5, 1, [sl, #68]	; 0x44
d001a3e4:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d001a3e8:	f8dfaebd 			; <UNDEFINED> instruction: 0xf8dfaebd
d001a3ec:	f8c3242c 			; <UNDEFINED> instruction: 0xf8c3242c
d001a3f0:	447a8068 	ldrbtmi	r8, [sl], #-104	; 0xffffff98
d001a3f4:	a918e9c3 	ldmdbge	r8, {r0, r1, r6, r7, r8, fp, sp, lr, pc}
d001a3f8:	2b16e9c3 	blcs	0xd05d4b0c
d001a3fc:	2601e6b2 			; <UNDEFINED> instruction: 0x2601e6b2
d001a400:	2301e7df 	movwcs	lr, #6111	; 0x17df
d001a404:	9b09e7e0 	blls	0xd029438c
d001a408:	d1582b00 	cmple	r8, r0, lsl #22
d001a40c:	d1582d00 	cmple	r8, r0, lsl #26
d001a410:	bf142c00 	svclt	0x00142c00
d001a414:	230d2310 	movwcs	r2, #54032	; 0xd310
d001a418:	ab169304 	blge	0xd05bf030
d001a41c:	b044f8cd 	sublt	pc, r4, sp, asr #17
d001a420:	b3f8f8df 	mvnslt	pc, #14614528	; 0xdf0000
d001a424:	8054f8cd 	subshi	pc, r4, sp, asr #17
d001a428:	a048f8cd 	subge	pc, r8, sp, asr #17
d001a42c:	f88d44fb 			; <UNDEFINED> instruction: 0xf88d44fb
d001a430:	e9139050 	ldmdb	r3, {r4, r6, ip, pc}
d001a434:	e88d000f 	stm	sp, {r0, r1, r2, r3}
d001a438:	e897000f 	ldm	r7, {r0, r1, r2, r3}
d001a43c:	f7f9000f 			; <UNDEFINED> instruction: 0xf7f9000f
d001a440:	f8dbfdc1 			; <UNDEFINED> instruction: 0xf8dbfdc1
d001a444:	46803058 	pkhtbmi	r3, r0, r8, asr #32
d001a448:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001a44c:	2230ae8b 	eorscs	sl, r0, #2224	; 0x8b0
d001a450:	f04f990d 			; <UNDEFINED> instruction: 0xf04f990d
d001a454:	f50b0a01 			; <UNDEFINED> instruction: 0xf50b0a01
d001a458:	fb023925 	blx	0xd00a88f6
d001a45c:	920ab300 	andls	fp, sl, #0, 6
d001a460:	3322f503 	msrcc	CPSR_x, #12582912	; 0xc00000
d001a464:	1136f883 	teqne	r6, r3, lsl #17	; <UNPREDICTABLE>
d001a468:	613ef8a3 	teqvs	lr, r3, lsr #17	; <UNPREDICTABLE>
d001a46c:	f8d99b07 			; <UNDEFINED> instruction: 0xf8d99b07
d001a470:	45537114 	ldrbmi	r7, [r3, #-276]	; 0xfffffeec
d001a474:	f8d9d827 			; <UNDEFINED> instruction: 0xf8d9d827
d001a478:	42bb3118 	adcsmi	r3, fp, #24, 2
d001a47c:	f8c9bf38 			; <UNDEFINED> instruction: 0xf8c9bf38
d001a480:	2d007118 	stfcss	f7, [r0, #-96]	; 0xffffffa0
d001a484:	4ce6d040 	stclmi	0, cr13, [r6], #256	; 0x100
d001a488:	447c213d 	ldrbtmi	r2, [ip], #-317	; 0xfffffec3
d001a48c:	f7f84620 			; <UNDEFINED> instruction: 0xf7f84620
d001a490:	4601fccc 	strmi	pc, [r1], -ip, asr #25
d001a494:	9b09b3a0 	blls	0xd028731c
d001a498:	990d4620 	stmdbls	sp, {r5, r9, sl, lr}
d001a49c:	f7fbb36b 			; <UNDEFINED> instruction: 0xf7fbb36b
d001a4a0:	48e0fd23 	stmiami	r0!, {r0, r1, r5, r8, sl, fp, ip, sp, lr, pc}^
d001a4a4:	46412200 	strbmi	r2, [r1], -r0, lsl #4
d001a4a8:	f7fa4478 			; <UNDEFINED> instruction: 0xf7fa4478
d001a4ac:	4adefc68 	bmi	0xcf7d9654
d001a4b0:	48de213b 	ldmmi	lr, {r0, r1, r3, r4, r5, r8, sp}^
d001a4b4:	4478447a 	ldrbtmi	r4, [r8], #-1146	; 0xfffffb86
d001a4b8:	fcc5f7f8 	stc2l	7, cr15, [r5], {248}	; 0xf8
d001a4bc:	2312e652 	tstcs	r2, #85983232	; 0x5200000
d001a4c0:	230ee7aa 	movwcs	lr, #59306	; 0xe7aa
d001a4c4:	1c7be7a8 	ldclne	7, cr14, [fp], #-672	; 0xfffffd60
d001a4c8:	21002230 	tstcs	r0, r0, lsr r2
d001a4cc:	0a01f10a 	beq	0xd00968fc
d001a4d0:	3114f8c9 	tstcc	r4, r9, asr #17	; <UNPREDICTABLE>
d001a4d4:	311cf899 			; <UNDEFINED> instruction: 0x311cf899
d001a4d8:	9b0a930b 	blls	0xd02bf10c
d001a4dc:	b707fb03 	strlt	pc, [r7, -r3, lsl #22]
d001a4e0:	3722f507 	strcc	pc, [r2, -r7, lsl #10]!
d001a4e4:	708af507 	addvc	pc, sl, r7, lsl #10
d001a4e8:	ff7cf004 			; <UNDEFINED> instruction: 0xff7cf004
d001a4ec:	f8879b0b 			; <UNDEFINED> instruction: 0xf8879b0b
d001a4f0:	230b3134 	movwcs	r3, #45364	; 0xb134
d001a4f4:	3135f887 	teqcc	r5, r7, lsl #17	; <UNPREDICTABLE>
d001a4f8:	f7fde7b8 			; <UNDEFINED> instruction: 0xf7fde7b8
d001a4fc:	e7d0faa5 	ldrb	pc, [r0, r5, lsr #21]	; <UNPREDICTABLE>
d001a500:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d001a504:	e7ccfbe9 	strb	pc, [ip, r9, ror #23]	; <UNPREDICTABLE>
d001a508:	213d4dc9 	teqcs	sp, r9, asr #27
d001a50c:	4628447d 			; <UNDEFINED> instruction: 0x4628447d
d001a510:	fc8bf7f8 	stc2	7, cr15, [fp], {248}	; 0xf8
d001a514:	d0ca2800 	sbcle	r2, sl, r0, lsl #16
d001a518:	6aebb9dc 	bvs	0xcfb08c90
d001a51c:	d0182b7b 	andsle	r2, r8, fp, ror fp
d001a520:	4628990d 	strtmi	r9, [r8], -sp, lsl #18
d001a524:	fe3af7fc 	mrc2	7, 1, pc, cr10, cr12, {7}
d001a528:	f24b4628 	vmax.s8	d20, d11, d24
d001a52c:	f7fa4103 			; <UNDEFINED> instruction: 0xf7fa4103
d001a530:	4641fb77 			; <UNDEFINED> instruction: 0x4641fb77
d001a534:	fc3cf7fa 	ldc2	7, cr15, [ip], #-1000	; 0xfffffc18
d001a538:	f2444628 	vmax.s8	d20, d4, d24
d001a53c:	f7fa6101 			; <UNDEFINED> instruction: 0xf7fa6101
d001a540:	f64bfb6f 			; <UNDEFINED> instruction: 0xf64bfb6f
d001a544:	f7fa4105 			; <UNDEFINED> instruction: 0xf7fa4105
d001a548:	9808fb6b 	stmdals	r8, {r0, r1, r3, r5, r6, r8, r9, fp, ip, sp, lr, pc}
d001a54c:	fd5cf7fb 	ldc2l	7, cr15, [ip, #-1004]	; 0xfffffc14
d001a550:	48b8e7ad 	ldmmi	r8!, {r0, r2, r3, r5, r7, r8, r9, sl, sp, lr, pc}
d001a554:	25002100 	strcs	r2, [r0, #-256]	; 0xffffff00
d001a558:	f7fa4478 			; <UNDEFINED> instruction: 0xf7fa4478
d001a55c:	48b6fbbd 	ldmmi	r6!, {r0, r2, r3, r4, r5, r7, r8, r9, fp, ip, sp, lr, pc}
d001a560:	9b074478 	blls	0xd01eb748
d001a564:	d10942ab 	smlatble	r9, fp, r2, r4
d001a568:	b174980d 	cmnlt	r4, sp, lsl #16
d001a56c:	46012300 	strmi	r2, [r1], -r0, lsl #6
d001a570:	46304642 	ldrtmi	r4, [r0], -r2, asr #12
d001a574:	f7ff9300 			; <UNDEFINED> instruction: 0xf7ff9300
d001a578:	e798fc13 			; <UNDEFINED> instruction: 0xe798fc13
d001a57c:	0105eb08 	tsteq	r5, r8, lsl #22
d001a580:	35012200 	strcc	r2, [r1, #-512]	; 0xfffffe00
d001a584:	fbfbf7fa 	blx	0xcff18576
d001a588:	2301e7eb 	movwcs	lr, #6123	; 0x17eb
d001a58c:	46414622 	strbmi	r4, [r1], -r2, lsr #12
d001a590:	fad4f7ff 	blx	0xcf558594
d001a594:	6af2e78b 	bvs	0xcfcd43c8
d001a598:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d001a59c:	d007429a 	mulle	r7, sl, r2
d001a5a0:	f43f2d00 			; <UNDEFINED> instruction: 0xf43f2d00
d001a5a4:	49a5ade0 	stmibmi	r5!, {r5, r6, r7, r8, sl, fp, sp, pc}
d001a5a8:	447948a5 	ldrbtmi	r4, [r9], #-2213	; 0xfffff75b
d001a5ac:	e66f4478 			; <UNDEFINED> instruction: 0xe66f4478
d001a5b0:	1206e9d6 	andne	lr, r6, #3506176	; 0x358000
d001a5b4:	f7f64630 			; <UNDEFINED> instruction: 0xf7f64630
d001a5b8:	2800f8a5 	stmdacs	r0, {r0, r2, r5, r7, fp, ip, sp, lr, pc}
d001a5bc:	48a1daf0 	stmiami	r1!, {r4, r5, r6, r7, r9, fp, ip, lr, pc}
d001a5c0:	f7fa4478 			; <UNDEFINED> instruction: 0xf7fa4478
d001a5c4:	2800fae1 	stmdacs	r0, {r0, r5, r6, r7, r9, fp, ip, sp, lr, pc}
d001a5c8:	8101f040 	tsthi	r1, r0, asr #32	; <UNPREDICTABLE>
d001a5cc:	4478489e 	ldrbtmi	r4, [r8], #-2206	; 0xfffff762
d001a5d0:	fadaf7fa 	blx	0xcf6d85c0
d001a5d4:	f04fb110 			; <UNDEFINED> instruction: 0xf04fb110
d001a5d8:	e5ea0a05 	strb	r0, [sl, #2565]!	; 0xa05
d001a5dc:	4478489b 	ldrbtmi	r4, [r8], #-2203	; 0xfffff765
d001a5e0:	fad2f7fa 	blx	0xcf4d85d0
d001a5e4:	d1f62800 	mvnsle	r2, r0, lsl #16
d001a5e8:	f1bae7da 			; <UNDEFINED> instruction: 0xf1bae7da
d001a5ec:	d0060f00 	andle	r0, r6, r0, lsl #30
d001a5f0:	2b006da3 	blcs	0xd0035c84
d001a5f4:	adb6f47f 	cfldrsge	mvf15, [r6, #508]!	; 0x1fc
d001a5f8:	447b4b95 	ldrbtmi	r4, [fp], #-2965	; 0xfffff46b
d001a5fc:	6ae3e62a 	bvs	0xcf913eac
d001a600:	7381f5a3 	orrvc	pc, r1, #683671552	; 0x28c00000
d001a604:	d80c2b01 	stmdale	ip, {r0, r8, r9, fp, sp}
d001a608:	a020f8d4 	ldrdge	pc, [r0], -r4	; <UNPREDICTABLE>
d001a60c:	0f00f1ba 	svceq	0x0000f1ba
d001a610:	f504d007 			; <UNDEFINED> instruction: 0xf504d007
d001a614:	f8d53525 			; <UNDEFINED> instruction: 0xf8d53525
d001a618:	f1c33114 			; <UNDEFINED> instruction: 0xf1c33114
d001a61c:	459a0340 	ldrmi	r0, [sl, #832]	; 0x340
d001a620:	4b8cd912 	blmi	0xce350a70
d001a624:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d001a628:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d001a62c:	4d8aad9b 	stcmi	13, cr10, [sl, #620]	; 0x26c
d001a630:	6a986a5c 	bvs	0xce634fa8
d001a634:	6b5a447d 	blvs	0xd16ab830
d001a638:	1030f893 	mlasne	r0, r3, r8, pc	; <UNPREDICTABLE>
d001a63c:	e9c3669a 	stmib	r3, {r1, r3, r4, r7, r9, sl, sp, lr}^
d001a640:	e9c35416 	stmib	r3, {r1, r2, r4, sl, ip, lr}^
d001a644:	e58d0118 	str	r0, [sp, #280]	; 0x118
d001a648:	f7f84620 			; <UNDEFINED> instruction: 0xf7f84620
d001a64c:	4a83fbd3 	bmi	0xce1195a0
d001a650:	4620215d 			; <UNDEFINED> instruction: 0x4620215d
d001a654:	f7f8447a 			; <UNDEFINED> instruction: 0xf7f8447a
d001a658:	2800fbf6 	stmdacs	r0, {r1, r2, r4, r5, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d001a65c:	ad82f43f 	cfstrsge	mvf15, [r2, #252]	; 0xfc
d001a660:	97152309 	ldrls	r2, [r5, -r9, lsl #6]
d001a664:	9048f8cd 	subls	pc, r8, sp, asr #17
d001a668:	ab169304 	blge	0xd05bf280
d001a66c:	8050f88d 	subshi	pc, r0, sp, lsl #17
d001a670:	b044f8cd 	sublt	pc, r4, sp, asr #17
d001a674:	000fe913 	andeq	lr, pc, r3, lsl r9	; <UNPREDICTABLE>
d001a678:	000fe88d 	andeq	lr, pc, sp, lsl #17
d001a67c:	000fe896 	muleq	pc, r6, r8	; <UNPREDICTABLE>
d001a680:	fca0f7f9 	stc2	7, cr15, [r0], #996	; 0x3e4
d001a684:	46076da3 	strmi	r6, [r7], -r3, lsr #27
d001a688:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001a68c:	f04fad6b 			; <UNDEFINED> instruction: 0xf04fad6b
d001a690:	26010930 			; <UNDEFINED> instruction: 0x26010930
d001a694:	fb0946a8 	blx	0xd026c13e
d001a698:	f5034300 			; <UNDEFINED> instruction: 0xf5034300
d001a69c:	f8a33322 			; <UNDEFINED> instruction: 0xf8a33322
d001a6a0:	45b2a13e 	ldrmi	sl, [r2, #318]!	; 0x13e
d001a6a4:	3114f8d8 			; <UNDEFINED> instruction: 0x3114f8d8
d001a6a8:	4c6dd126 	stfmip	f5, [sp], #-152	; 0xffffff68
d001a6ac:	f8d8213d 			; <UNDEFINED> instruction: 0xf8d8213d
d001a6b0:	447c2118 	ldrbtmi	r2, [ip], #-280	; 0xfffffee8
d001a6b4:	4620429a 			; <UNDEFINED> instruction: 0x4620429a
d001a6b8:	f8c8bf38 			; <UNDEFINED> instruction: 0xf8c8bf38
d001a6bc:	f7f83118 			; <UNDEFINED> instruction: 0xf7f83118
d001a6c0:	b198fbb4 			; <UNDEFINED> instruction: 0xb198fbb4
d001a6c4:	21004620 	tstcs	r0, r0, lsr #12
d001a6c8:	fb06f7fa 	blx	0xd01d86ba
d001a6cc:	46202500 	strtmi	r2, [r0], -r0, lsl #10
d001a6d0:	350119e9 	strcc	r1, [r1, #-2537]	; 0xfffff617
d001a6d4:	f7fa2200 			; <UNDEFINED> instruction: 0xf7fa2200
d001a6d8:	42aefb52 	adcmi	pc, lr, #83968	; 0x14800
d001a6dc:	2300d1f8 	movwcs	sp, #504	; 0x1f8
d001a6e0:	21ff463a 	mvnscs	r4, sl, lsr r6
d001a6e4:	93004630 	movwls	r4, #1584	; 0x630
d001a6e8:	fb5af7ff 	blx	0xd16d86ee
d001a6ec:	213b4a5d 	teqcs	fp, sp, asr sl
d001a6f0:	447a485d 	ldrbtmi	r4, [sl], #-2141	; 0xfffff7a3
d001a6f4:	e6df4478 			; <UNDEFINED> instruction: 0xe6df4478
d001a6f8:	fb091c5a 	blx	0xd026186a
d001a6fc:	21004303 	tstcs	r0, r3, lsl #6
d001a700:	b11cf898 			; <UNDEFINED> instruction: 0xb11cf898
d001a704:	3522f503 	strcc	pc, [r2, #-1283]!	; 0xfffffafd
d001a708:	2114f8c8 	tstcs	r4, r8, asr #17	; <UNPREDICTABLE>
d001a70c:	36012230 			; <UNDEFINED> instruction: 0x36012230
d001a710:	708af505 	addvc	pc, sl, r5, lsl #10
d001a714:	fe66f004 	cdp2	0, 6, cr15, cr6, cr4, {0}
d001a718:	f885230b 			; <UNDEFINED> instruction: 0xf885230b
d001a71c:	f885b134 			; <UNDEFINED> instruction: 0xf885b134
d001a720:	e7be3135 			; <UNDEFINED> instruction: 0xe7be3135
d001a724:	f8cdab16 			; <UNDEFINED> instruction: 0xf8cdab16
d001a728:	f88d9048 			; <UNDEFINED> instruction: 0xf88d9048
d001a72c:	97158050 			; <UNDEFINED> instruction: 0x97158050
d001a730:	a010f8cd 	andsge	pc, r0, sp, asr #17
d001a734:	b044f8cd 	sublt	pc, r4, sp, asr #17
d001a738:	000fe913 	andeq	lr, pc, r3, lsl r9	; <UNPREDICTABLE>
d001a73c:	000fe88d 	andeq	lr, pc, sp, lsl #17
d001a740:	000fe896 	muleq	pc, r6, r8	; <UNPREDICTABLE>
d001a744:	fc3ef7f9 	ldc2	7, cr15, [lr], #-996	; 0xfffffc1c
d001a748:	46066da3 	strmi	r6, [r6], -r3, lsr #27
d001a74c:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001a750:	2330ad09 	teqcs	r0, #576	; 0x240
d001a754:	fb03213d 	blx	0xd00e2c52
d001a758:	46204300 	strtmi	r4, [r0], -r0, lsl #6
d001a75c:	3322f503 	msrcc	CPSR_x, #12582912	; 0xc00000
d001a760:	5140f883 	smlalbbpl	pc, r0, r3, r8	; <UNPREDICTABLE>
d001a764:	fb61f7f8 	blx	0xd189874e
d001a768:	f1bab320 			; <UNDEFINED> instruction: 0xf1bab320
d001a76c:	d10e0f13 	tstle	lr, r3, lsl pc
d001a770:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d001a774:	483dfb63 	ldmdami	sp!, {r0, r1, r5, r6, r8, r9, fp, ip, sp, lr, pc}
d001a778:	46312200 	ldrtmi	r2, [r1], -r0, lsl #4
d001a77c:	f7fa4478 			; <UNDEFINED> instruction: 0xf7fa4478
d001a780:	4a3bfafe 	bmi	0xd0f19380
d001a784:	483b213b 	ldmdami	fp!, {r0, r1, r3, r4, r5, r8, sp}
d001a788:	4478447a 	ldrbtmi	r4, [r8], #-1146	; 0xfffffb86
d001a78c:	f1bae694 			; <UNDEFINED> instruction: 0xf1bae694
d001a790:	f04f0f0a 			; <UNDEFINED> instruction: 0xf04f0f0a
d001a794:	46200101 	strtmi	r0, [r0], -r1, lsl #2
d001a798:	2204bf0c 	andcs	fp, r4, #12, 30	; 0x30
d001a79c:	f7fb2201 			; <UNDEFINED> instruction: 0xf7fb2201
d001a7a0:	f1bafd31 			; <UNDEFINED> instruction: 0xf1bafd31
d001a7a4:	d1e60f05 	mvnle	r0, r5, lsl #30
d001a7a8:	21c0f24b 	biccs	pc, r0, fp, asr #4
d001a7ac:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d001a7b0:	e7e0fa37 			; <UNDEFINED> instruction: 0xe7e0fa37
d001a7b4:	d0e42d00 	rscle	r2, r4, r0, lsl #26
d001a7b8:	2b006da3 	blcs	0xd0035e4c
d001a7bc:	4b2ed1e1 	blmi	0xd0bcef48
d001a7c0:	447b66a7 	ldrbtmi	r6, [fp], #-1703	; 0xfffff959
d001a7c4:	9818e9c4 	ldmdals	r8, {r2, r6, r7, r8, fp, sp, lr, pc}
d001a7c8:	3b16e9c4 	blcc	0xd05d4ee0
d001a7cc:	f04fe7d9 			; <UNDEFINED> instruction: 0xf04fe7d9
d001a7d0:	e4ee0a01 	strbt	r0, [lr], #2561	; 0xa01
d001a7d4:	000092d6 	ldrdeq	r9, [r0], -r6
d001a7d8:	00009288 	andeq	r9, r0, r8, lsl #5
d001a7dc:	0000921e 	andeq	r9, r0, lr, lsl r2
d001a7e0:	fffffde4 			; <UNDEFINED> instruction: 0xfffffde4
d001a7e4:	fffffdd9 			; <UNDEFINED> instruction: 0xfffffdd9
d001a7e8:	000091b4 			; <UNDEFINED> instruction: 0x000091b4
d001a7ec:	fffffc67 			; <UNDEFINED> instruction: 0xfffffc67
d001a7f0:	0000918e 	andeq	r9, r0, lr, lsl #3
d001a7f4:	00009146 	andeq	r9, r0, r6, asr #2
d001a7f8:	fffffc26 			; <UNDEFINED> instruction: 0xfffffc26
d001a7fc:	000090f0 	strdeq	r9, [r0], -r0
d001a800:	000090ba 	strheq	r9, [r0], -sl
d001a804:	fffffb53 			; <UNDEFINED> instruction: 0xfffffb53
d001a808:	000090a0 	andeq	r9, r0, r0, lsr #1
d001a80c:	fffffafc 			; <UNDEFINED> instruction: 0xfffffafc
d001a810:	fffffb94 			; <UNDEFINED> instruction: 0xfffffb94
d001a814:	0000904c 	andeq	r9, r0, ip, asr #32
d001a818:	fffffb7d 			; <UNDEFINED> instruction: 0xfffffb7d
d001a81c:	00008ff0 	strdeq	r8, [r0], -r0
d001a820:	00008f92 	muleq	r0, r2, pc	; <UNPREDICTABLE>
d001a824:	00008f74 	andeq	r8, r0, r4, ror pc
d001a828:	fffffae9 			; <UNDEFINED> instruction: 0xfffffae9
d001a82c:	00008f66 	andeq	r8, r0, r6, ror #30
d001a830:	00008f10 	andeq	r8, r0, r0, lsl pc
d001a834:	00008ec4 	andeq	r8, r0, r4, asr #29
d001a838:	00008ebc 			; <UNDEFINED> instruction: 0x00008ebc
d001a83c:	fffffa28 			; <UNDEFINED> instruction: 0xfffffa28
d001a840:	00008e70 	andeq	r8, r0, r0, ror lr
d001a844:	fffffa00 			; <UNDEFINED> instruction: 0xfffffa00
d001a848:	fffff9fb 			; <UNDEFINED> instruction: 0xfffff9fb
d001a84c:	ffff91a8 			; <UNDEFINED> instruction: 0xffff91a8
d001a850:	fffffa54 			; <UNDEFINED> instruction: 0xfffffa54
d001a854:	00008df8 	strdeq	r8, [r0], -r8	; <UNPREDICTABLE>
d001a858:	fffffa3e 			; <UNDEFINED> instruction: 0xfffffa3e
d001a85c:	fffffa4f 			; <UNDEFINED> instruction: 0xfffffa4f
d001a860:	00008d6a 	andeq	r8, r0, sl, ror #26
d001a864:	fffff9d5 			; <UNDEFINED> instruction: 0xfffff9d5
d001a868:	00008d28 	andeq	r8, r0, r8, lsr #26
d001a86c:	00008ca0 	andeq	r8, r0, r0, lsr #25
d001a870:	fffff98a 			; <UNDEFINED> instruction: 0xfffff98a
d001a874:	00008c92 	muleq	r0, r2, ip
d001a878:	fffff930 			; <UNDEFINED> instruction: 0xfffff930

Disassembly of section .text.statement.constprop.0:

d001abd8 <.text.statement.constprop.0>:
d001abd8:	4ff0e92d 	svcmi	0x00f0e92d
d001abdc:	49acf8df 	stmibmi	ip!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d001abe0:	6da3447c 	cfstrsvs	mvf4, [r3, #496]!	; 0x1f0
d001abe4:	8b02ed2d 	blhi	0xd00d60a0
d001abe8:	bb6bb089 	bllt	0xd1b06e14
d001abec:	3525f504 	strcc	pc, [r5, #-1284]!	; 0xfffffafc
d001abf0:	3120f8d5 	ldrdcc	pc, [r0, -r5]!
d001abf4:	2b203301 	blcs	0xd0827800
d001abf8:	3120f8c5 	smlawtcc	r0, r5, r8, pc	; <UNPREDICTABLE>
d001abfc:	f8dfd904 			; <UNDEFINED> instruction: 0xf8dfd904
d001ac00:	44791990 	ldrbtmi	r1, [r9], #-2448	; 0xfffff670
d001ac04:	e0644620 	rsb	r4, r4, r0, lsr #12
d001ac08:	4620217b 			; <UNDEFINED> instruction: 0x4620217b
d001ac0c:	f90df7f8 			; <UNDEFINED> instruction: 0xf90df7f8
d001ac10:	b1f04606 	mvnslt	r4, r6, lsl #12
d001ac14:	311cf8d5 			; <UNDEFINED> instruction: 0x311cf8d5
d001ac18:	4114f8d5 			; <UNDEFINED> instruction: 0x4114f8d5
d001ac1c:	f8c53301 			; <UNDEFINED> instruction: 0xf8c53301
d001ac20:	f000311c 			; <UNDEFINED> instruction: 0xf000311c
d001ac24:	f8d5fd47 			; <UNDEFINED> instruction: 0xf8d5fd47
d001ac28:	f8c5311c 			; <UNDEFINED> instruction: 0xf8c5311c
d001ac2c:	3b014114 	blcc	0xd006b084
d001ac30:	311cf8c5 	tstcc	ip, r5, asr #17	; <UNPREDICTABLE>
d001ac34:	395cf8df 	ldmdbcc	ip, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d001ac38:	f503447b 			; <UNDEFINED> instruction: 0xf503447b
d001ac3c:	f8d33325 			; <UNDEFINED> instruction: 0xf8d33325
d001ac40:	3a012120 	bcc	0xd00630c8
d001ac44:	2120f8c3 	smlawtcs	r0, r3, r8, pc	; <UNPREDICTABLE>
d001ac48:	ecbdb009 	ldc	0, cr11, [sp], #36	; 0x24
d001ac4c:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d001ac50:	f44f8ff0 			; <UNDEFINED> instruction: 0xf44f8ff0
d001ac54:	46207186 	strtmi	r7, [r0], -r6, lsl #3
d001ac58:	f8e7f7f8 			; <UNDEFINED> instruction: 0xf8e7f7f8
d001ac5c:	b3384680 	teqlt	r8, #128, 12	; 0x8000000
d001ac60:	fafef7fe 	blx	0xcffd8c60
d001ac64:	46204631 			; <UNDEFINED> instruction: 0x46204631
d001ac68:	4798f24f 	ldrmi	pc, [r8, pc, asr #4]
d001ac6c:	fc32f7fa 	ldc2	7, cr15, [r2], #-1000	; 0xfffffc18
d001ac70:	f7ff4605 			; <UNDEFINED> instruction: 0xf7ff4605
d001ac74:	f240ffb1 	vrecps.f32	d31, d16, d17
d001ac78:	4620110d 	strtmi	r1, [r0], -sp, lsl #2
d001ac7c:	f8d5f7f8 			; <UNDEFINED> instruction: 0xf8d5f7f8
d001ac80:	b1904603 	orrslt	r4, r0, r3, lsl #12
d001ac84:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d001ac88:	4680fc19 	pkhbtmi	pc, r0, r9, lsl #24	; <UNPREDICTABLE>
d001ac8c:	59e24633 	stmibpl	r2!, {r0, r1, r4, r5, r9, sl, lr}^
d001ac90:	6da04629 	stcvs	6, cr4, [r0, #164]!	; 0xa4
d001ac94:	fa0af7fb 	blx	0xd02d8c88
d001ac98:	ff9ef7ff 			; <UNDEFINED> instruction: 0xff9ef7ff
d001ac9c:	59e24633 	stmibpl	r2!, {r0, r1, r4, r5, r9, sl, lr}^
d001aca0:	6da04641 	stcvs	6, cr4, [r0, #260]!	; 0x104
d001aca4:	fa02f7fb 	blx	0xd00d8c98
d001aca8:	59e2e7c4 	stmibpl	r2!, {r2, r6, r7, r8, r9, sl, sp, lr, pc}^
d001acac:	e7f84629 	ldrb	r4, [r8, r9, lsr #12]!
d001acb0:	7187f44f 	orrvc	pc, r7, pc, asr #8
d001acb4:	f7f84620 			; <UNDEFINED> instruction: 0xf7f84620
d001acb8:	2800f8b8 	stmdacs	r0, {r3, r4, r5, r7, fp, ip, sp, lr, pc}
d001acbc:	f8d5d07c 			; <UNDEFINED> instruction: 0xf8d5d07c
d001acc0:	2b203128 	blcs	0xd0827168
d001acc4:	f8dfd108 			; <UNDEFINED> instruction: 0xf8dfd108
d001acc8:	f8df18d0 			; <UNDEFINED> instruction: 0xf8df18d0
d001accc:	447908d0 	ldrbtmi	r0, [r9], #-2256	; 0xfffff730
d001acd0:	f7f54478 			; <UNDEFINED> instruction: 0xf7f54478
d001acd4:	e7adfa69 	str	pc, [sp, r9, ror #20]!
d001acd8:	4398f24f 	orrsmi	pc, r8, #-268435452	; 0xf0000004
d001acdc:	612cf8d5 	ldrdvs	pc, [ip, -r5]!
d001ace0:	f7fe58e7 			; <UNDEFINED> instruction: 0xf7fe58e7
d001ace4:	4641fabd 			; <UNDEFINED> instruction: 0x4641fabd
d001ace8:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d001acec:	f8d5fbf3 			; <UNDEFINED> instruction: 0xf8d5fbf3
d001acf0:	46803128 	strmi	r3, [r0], r8, lsr #2
d001acf4:	f8c53301 			; <UNDEFINED> instruction: 0xf8c53301
d001acf8:	f5043128 			; <UNDEFINED> instruction: 0xf5043128
d001acfc:	f8d53529 			; <UNDEFINED> instruction: 0xf8d53529
d001ad00:	2b403130 	blcs	0xd10271c8
d001ad04:	f8dfd137 			; <UNDEFINED> instruction: 0xf8dfd137
d001ad08:	46201898 			; <UNDEFINED> instruction: 0x46201898
d001ad0c:	f7f54479 			; <UNDEFINED> instruction: 0xf7f54479
d001ad10:	f8dffa4b 			; <UNDEFINED> instruction: 0xf8dffa4b
d001ad14:	f5064890 			; <UNDEFINED> instruction: 0xf5064890
d001ad18:	f8df45a5 			; <UNDEFINED> instruction: 0xf8df45a5
d001ad1c:	447ca88c 	ldrbtmi	sl, [ip], #-2188	; 0xfffff774
d001ad20:	44fa3526 	ldrbtmi	r3, [sl], #1318	; 0x526
d001ad24:	3225f504 	eorcc	pc, r5, #4, 10	; 0x1000000
d001ad28:	f5044620 			; <UNDEFINED> instruction: 0xf5044620
d001ad2c:	eb044974 	bl	0xd012d304
d001ad30:	f8d205c5 			; <UNDEFINED> instruction: 0xf8d205c5
d001ad34:	f1093128 			; <UNDEFINED> instruction: 0xf1093128
d001ad38:	3b010998 	blcc	0xd005d3a0
d001ad3c:	3128f8c2 	smlawtcc	r8, r2, r8, pc	; <UNPREDICTABLE>
d001ad40:	fbbcf7fa 	blx	0xcef58d32
d001ad44:	46012300 	strmi	r2, [r1], -r0, lsl #6
d001ad48:	6da0463a 	stcvs	6, cr4, [r0, #232]!	; 0xe8
d001ad4c:	f9aef7fb 			; <UNDEFINED> instruction: 0xf9aef7fb
d001ad50:	4298f24f 	addsmi	pc, r8, #-268435452	; 0xf0000004
d001ad54:	46b04641 	ldrtmi	r4, [r0], r1, asr #12
d001ad58:	58a22300 	stmiapl	r2!, {r8, r9, sp}
d001ad5c:	f7fb6da0 			; <UNDEFINED> instruction: 0xf7fb6da0
d001ad60:	f504f9a5 			; <UNDEFINED> instruction: 0xf504f9a5
d001ad64:	f5033325 			; <UNDEFINED> instruction: 0xf5033325
d001ad68:	f8d37296 			; <UNDEFINED> instruction: 0xf8d37296
d001ad6c:	4598312c 	ldrmi	r3, [r8, #300]	; 0x12c
d001ad70:	6016d312 	andsvs	sp, r6, r2, lsl r3
d001ad74:	441ce75e 	ldrmi	lr, [ip], #-1886	; 0xfffff8a2
d001ad78:	23011c5a 	movwcs	r1, #7258	; 0x1c5a
d001ad7c:	3429f504 	strtcc	pc, [r9], #-1284	; 0xfffffafc
d001ad80:	2130f8c5 	teqcs	r0, r5, asr #17	; <UNPREDICTABLE>
d001ad84:	3134f884 	teqcc	r4, r4, lsl #17	; <UNPREDICTABLE>
d001ad88:	ff26f7ff 			; <UNDEFINED> instruction: 0xff26f7ff
d001ad8c:	3130f8d5 	teqcc	r0, r5	; <illegal shifter operand>	; <UNPREDICTABLE>
d001ad90:	f8c53b01 			; <UNDEFINED> instruction: 0xf8c53b01
d001ad94:	e7bc3130 			; <UNDEFINED> instruction: 0xe7bc3130
d001ad98:	6829792b 	stmdavs	r9!, {r0, r1, r3, r5, r8, fp, ip, sp, lr}
d001ad9c:	f8d9b153 			; <UNDEFINED> instruction: 0xf8d9b153
d001ada0:	23002000 	movwcs	r2, #0
d001ada4:	0058f8da 	ldrsbeq	pc, [r8], #-138	; 0xffffff76	; <UNPREDICTABLE>
d001ada8:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d001adac:	f7fb3508 			; <UNDEFINED> instruction: 0xf7fb3508
d001adb0:	e7d6f97d 			; <UNDEFINED> instruction: 0xe7d6f97d
d001adb4:	e7f4463a 			; <UNDEFINED> instruction: 0xe7f4463a
d001adb8:	1113f240 	tstne	r3, r0, asr #4	; <UNPREDICTABLE>
d001adbc:	f7f84620 			; <UNDEFINED> instruction: 0xf7f84620
d001adc0:	2800f834 	stmdacs	r0, {r2, r4, r5, fp, ip, sp, lr, pc}
d001adc4:	80e4f000 	rschi	pc, r4, r0
d001adc8:	3128f8d5 	ldrdcc	pc, [r8, -r5]!
d001adcc:	f43f2b20 			; <UNDEFINED> instruction: 0xf43f2b20
d001add0:	f8dfaf7a 			; <UNDEFINED> instruction: 0xf8dfaf7a
d001add4:	212827d8 	ldrdcs	r2, [r8, -r8]!
d001add8:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d001addc:	f833f7f8 			; <UNDEFINED> instruction: 0xf833f7f8
d001ade0:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001ade4:	f8d5af27 			; <UNDEFINED> instruction: 0xf8d5af27
d001ade8:	f8d5311c 			; <UNDEFINED> instruction: 0xf8d5311c
d001adec:	33017114 	movwcc	r7, #4372	; 0x1114
d001adf0:	612cf8d5 	ldrdvs	pc, [ip, -r5]!
d001adf4:	311cf8c5 	tstcc	ip, r5, asr #17	; <UNPREDICTABLE>
d001adf8:	f99ef7ff 			; <UNDEFINED> instruction: 0xf99ef7ff
d001adfc:	213bb978 	teqcs	fp, r8, ror r9
d001ae00:	f7f84620 			; <UNDEFINED> instruction: 0xf7f84620
d001ae04:	b950f812 	ldmdblt	r0, {r1, r4, fp, ip, sp, lr, pc}^
d001ae08:	fb16f7fe 	blx	0xd05d8e0a
d001ae0c:	27a0f8df 	sbfxcs	pc, pc, #17, #1
d001ae10:	07a0f8df 	sbfxeq	pc, pc, #17, #1
d001ae14:	447a213b 	ldrbtmi	r2, [sl], #-315	; 0xfffffec5
d001ae18:	f7f84478 			; <UNDEFINED> instruction: 0xf7f84478
d001ae1c:	f8dff814 			; <UNDEFINED> instruction: 0xf8dff814
d001ae20:	f24f4798 	vaba.s8	d20, d31, d8
d001ae24:	447c4398 	ldrbtmi	r4, [ip], #-920	; 0xfffffc68
d001ae28:	9003f854 	andls	pc, r3, r4, asr r8	; <UNPREDICTABLE>
d001ae2c:	2b3b6ae3 	blcs	0xd0ef59c0
d001ae30:	808bf000 	addhi	pc, fp, r0
d001ae34:	21012202 	tstcs	r1, r2, lsl #4
d001ae38:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d001ae3c:	2100f9e3 	smlattcs	r0, r3, r9, pc	; <UNPREDICTABLE>
d001ae40:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d001ae44:	4605fb47 	strmi	pc, [r5], -r7, asr #22
d001ae48:	4770f8df 			; <UNDEFINED> instruction: 0x4770f8df
d001ae4c:	f8df213b 			; <UNDEFINED> instruction: 0xf8df213b
d001ae50:	447c2770 	ldrbtmi	r2, [ip], #-1904	; 0xfffff890
d001ae54:	4620447a 			; <UNDEFINED> instruction: 0x4620447a
d001ae58:	fff5f7f7 			; <UNDEFINED> instruction: 0xfff5f7f7
d001ae5c:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d001ae60:	f24ffb2d 	vqdmulh.s<illegal width 8>	d31, d15, d29
d001ae64:	46824398 	pkhbtmi	r4, r2, r8, lsl #7
d001ae68:	8003f854 	andhi	pc, r3, r4, asr r8	; <UNPREDICTABLE>
d001ae6c:	2b296ae3 	blcs	0xd0a75a00
d001ae70:	f7fed001 			; <UNDEFINED> instruction: 0xf7fed001
d001ae74:	f8dffae1 			; <UNDEFINED> instruction: 0xf8dffae1
d001ae78:	2129474c 			; <UNDEFINED> instruction: 0x2129474c
d001ae7c:	2748f8df 			; <UNDEFINED> instruction: 0x2748f8df
d001ae80:	447a447c 	ldrbtmi	r4, [sl], #-1148	; 0xfffffb84
d001ae84:	f7f74620 			; <UNDEFINED> instruction: 0xf7f74620
d001ae88:	4620ffde 			; <UNDEFINED> instruction: 0x4620ffde
d001ae8c:	fb16f7fa 	blx	0xd05d8e7e
d001ae90:	4601464a 	strmi	r4, [r1], -sl, asr #12
d001ae94:	6da02300 	stcvs	3, cr2, [r0]
d001ae98:	3929f504 	stmdbcc	r9!, {r2, r8, sl, ip, sp, lr, pc}
d001ae9c:	f906f7fb 			; <UNDEFINED> instruction: 0xf906f7fb
d001aea0:	4298f24f 	addsmi	pc, r8, #-268435452	; 0xf0000004
d001aea4:	46512300 	ldrbmi	r2, [r1], -r0, lsl #6
d001aea8:	6da058a2 	stcvs	8, cr5, [r0, #648]!	; 0x288
d001aeac:	f8fef7fb 			; <UNDEFINED> instruction: 0xf8fef7fb
d001aeb0:	3225f504 	eorcc	pc, r5, #4, 10	; 0x1000000
d001aeb4:	3128f8d2 	ldrdcc	pc, [r8, -r2]!
d001aeb8:	f8c23301 			; <UNDEFINED> instruction: 0xf8c23301
d001aebc:	f8d93128 			; <UNDEFINED> instruction: 0xf8d93128
d001aec0:	2b403130 	blcs	0xd1027388
d001aec4:	f8dfd143 			; <UNDEFINED> instruction: 0xf8dfd143
d001aec8:	46201704 	strtmi	r1, [r0], -r4, lsl #14
d001aecc:	f7f54479 			; <UNDEFINED> instruction: 0xf7f54479
d001aed0:	f8dff96b 			; <UNDEFINED> instruction: 0xf8dff96b
d001aed4:	447c46fc 	ldrbtmi	r4, [ip], #-1788	; 0xfffff904
d001aed8:	3225f504 	eorcc	pc, r5, #4, 10	; 0x1000000
d001aedc:	f8d24620 			; <UNDEFINED> instruction: 0xf8d24620
d001aee0:	3b013128 	blcc	0xd0067388
d001aee4:	3128f8c2 	smlawtcc	r8, r2, r8, pc	; <UNPREDICTABLE>
d001aee8:	fae8f7fa 	blx	0xcfa58ed8
d001aeec:	46012300 	strmi	r2, [r1], -r0, lsl #6
d001aef0:	6da04642 	stcvs	6, cr4, [r0, #264]!	; 0x108
d001aef4:	f8daf7fb 			; <UNDEFINED> instruction: 0xf8daf7fb
d001aef8:	f24fb13d 	vand	d27, d15, d29
d001aefc:	23004298 	movwcs	r4, #664	; 0x298
d001af00:	6da04629 	stcvs	6, cr4, [r0, #164]!	; 0xa4
d001af04:	f7fb58a2 			; <UNDEFINED> instruction: 0xf7fb58a2
d001af08:	f8dff8d1 			; <UNDEFINED> instruction: 0xf8dff8d1
d001af0c:	f50656c8 			; <UNDEFINED> instruction: 0xf50656c8
d001af10:	f8df44a5 			; <UNDEFINED> instruction: 0xf8df44a5
d001af14:	46b1b6c4 	ldrtmi	fp, [r1], r4, asr #13
d001af18:	3426447d 	strtcc	r4, [r6], #-1149	; 0xfffffb83
d001af1c:	f50544fb 			; <UNDEFINED> instruction: 0xf50544fb
d001af20:	eb054a74 	bl	0xd016d8f8
d001af24:	f10a04c4 			; <UNDEFINED> instruction: 0xf10a04c4
d001af28:	f5050a98 			; <UNDEFINED> instruction: 0xf5050a98
d001af2c:	f8d33325 			; <UNDEFINED> instruction: 0xf8d33325
d001af30:	4589112c 	strmi	r1, [r9, #300]	; 0x12c
d001af34:	f8d3d31c 			; <UNDEFINED> instruction: 0xf8d3d31c
d001af38:	f8c3211c 			; <UNDEFINED> instruction: 0xf8c3211c
d001af3c:	3a01612c 	bcc	0xd00733f4
d001af40:	7114f8c3 	tstvc	r4, r3, asr #17	; <UNPREDICTABLE>
d001af44:	211cf8c3 	tstcs	ip, r3, asr #17	; <UNPREDICTABLE>
d001af48:	2500e674 	strcs	lr, [r0, #-1652]	; 0xfffff98c
d001af4c:	441ce77c 	ldrmi	lr, [ip], #-1916	; 0xfffff884
d001af50:	23011c5a 	movwcs	r1, #7258	; 0x1c5a
d001af54:	3429f504 	strtcc	pc, [r9], #-1284	; 0xfffffafc
d001af58:	2130f8c9 	teqcs	r0, r9, asr #17	; <UNPREDICTABLE>
d001af5c:	3134f884 	teqcc	r4, r4, lsl #17	; <UNPREDICTABLE>
d001af60:	fe3af7ff 	mrc2	7, 1, pc, cr10, cr15, {7}
d001af64:	3130f8d9 	teqcc	r0, r9	; <illegal shifter operand>	; <UNPREDICTABLE>
d001af68:	f8c93b01 			; <UNDEFINED> instruction: 0xf8c93b01
d001af6c:	e7b03130 			; <UNDEFINED> instruction: 0xe7b03130
d001af70:	68217923 	stmdavs	r1!, {r0, r1, r5, r8, fp, ip, sp, lr}
d001af74:	f8dab153 			; <UNDEFINED> instruction: 0xf8dab153
d001af78:	23002000 	movwcs	r2, #0
d001af7c:	0058f8db 	ldrsbeq	pc, [r8], #-139	; 0xffffff75	; <UNPREDICTABLE>
d001af80:	0901f109 	stmdbeq	r1, {r0, r3, r8, ip, sp, lr, pc}
d001af84:	f7fb3408 			; <UNDEFINED> instruction: 0xf7fb3408
d001af88:	e7cef891 	bfi	pc, r1, (invalid: 17:14)	; <UNPREDICTABLE>
d001af8c:	e7f44642 	ldrb	r4, [r4, r2, asr #12]!
d001af90:	718af44f 	orrvc	pc, sl, pc, asr #8
d001af94:	f7f74620 			; <UNDEFINED> instruction: 0xf7f74620
d001af98:	4607ff48 	strmi	pc, [r7], -r8, asr #30
d001af9c:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d001afa0:	f50481fd 			; <UNDEFINED> instruction: 0xf50481fd
d001afa4:	f8d33329 			; <UNDEFINED> instruction: 0xf8d33329
d001afa8:	2b403130 	blcs	0xd1027470
d001afac:	f8dfd103 			; <UNDEFINED> instruction: 0xf8dfd103
d001afb0:	4479162c 	ldrbtmi	r1, [r9], #-1580	; 0xfffff9d4
d001afb4:	f504e626 			; <UNDEFINED> instruction: 0xf504e626
d001afb8:	f8d3332d 			; <UNDEFINED> instruction: 0xf8d3332d
d001afbc:	f5b33178 			; <UNDEFINED> instruction: 0xf5b33178
d001afc0:	93007f80 	movwls	r7, #3968	; 0xf80
d001afc4:	f8dfd103 			; <UNDEFINED> instruction: 0xf8dfd103
d001afc8:	44791618 	ldrbtmi	r1, [r9], #-1560	; 0xfffff9e8
d001afcc:	f8d5e61a 			; <UNDEFINED> instruction: 0xf8d5e61a
d001afd0:	2b403114 	blcs	0xd1027428
d001afd4:	d1109301 	tstle	r0, r1, lsl #6
d001afd8:	1608f8df 			; <UNDEFINED> instruction: 0x1608f8df
d001afdc:	0608f8df 			; <UNDEFINED> instruction: 0x0608f8df
d001afe0:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d001afe4:	f8e0f7f5 			; <UNDEFINED> instruction: 0xf8e0f7f5
d001afe8:	3600f8df 			; <UNDEFINED> instruction: 0x3600f8df
d001afec:	447b9a01 	ldrbtmi	r9, [fp], #-2561	; 0xfffff5ff
d001aff0:	3325f503 	msrcc	CPSR_sc, #12582912	; 0xc00000
d001aff4:	2114f8c3 	tstcs	r4, r3, asr #17	; <UNPREDICTABLE>
d001aff8:	f8dfe61c 			; <UNDEFINED> instruction: 0xf8dfe61c
d001affc:	212845f4 	strdcs	r4, [r8, -r4]!	; <UNPREDICTABLE>
d001b000:	25f0f8df 	ldrbcs	pc, [r0, #2271]!	; 0x8df	; <UNPREDICTABLE>
d001b004:	447a447c 	ldrbtmi	r4, [sl], #-1148	; 0xfffffb84
d001b008:	3329f504 	msrcc	CPSR_fc, #4, 10	; 0x1000000
d001b00c:	f8d34620 			; <UNDEFINED> instruction: 0xf8d34620
d001b010:	93023174 	movwls	r3, #8564	; 0x2174
d001b014:	ff17f7f7 			; <UNDEFINED> instruction: 0xff17f7f7
d001b018:	d0e52800 	rscle	r2, r5, r0, lsl #16
d001b01c:	46202201 	strtmi	r2, [r0], -r1, lsl #4
d001b020:	f7fb4611 			; <UNDEFINED> instruction: 0xf7fb4611
d001b024:	f8dff8ef 			; <UNDEFINED> instruction: 0xf8dff8ef
d001b028:	212925d0 	ldrdcs	r2, [r9, -r0]!
d001b02c:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d001b030:	ff09f7f7 			; <UNDEFINED> instruction: 0xff09f7f7
d001b034:	d0d72800 	sbcsle	r2, r7, r0, lsl #16
d001b038:	25c0f8df 	strbcs	pc, [r0, #2271]	; 0x8df	; <UNPREDICTABLE>
d001b03c:	4620217b 			; <UNDEFINED> instruction: 0x4620217b
d001b040:	f7f7447a 			; <UNDEFINED> instruction: 0xf7f7447a
d001b044:	2800ff00 	stmdacs	r0, {r8, r9, sl, fp, ip, sp, lr, pc}
d001b048:	f504d0ce 			; <UNDEFINED> instruction: 0xf504d0ce
d001b04c:	21003425 	tstcs	r0, r5, lsr #8
d001b050:	8114f8d4 			; <UNDEFINED> instruction: 0x8114f8d4
d001b054:	2118f8d4 			; <UNDEFINED> instruction: 0x2118f8d4
d001b058:	0301f108 	movweq	pc, #4360	; 0x1108	; <UNPREDICTABLE>
d001b05c:	f8c44293 			; <UNDEFINED> instruction: 0xf8c44293
d001b060:	f04f3114 			; <UNDEFINED> instruction: 0xf04f3114
d001b064:	bf880230 	svclt	0x00880230
d001b068:	3118f8c4 	tstcc	r8, r4, asr #17	; <UNPREDICTABLE>
d001b06c:	4590f8df 	ldrmi	pc, [r0, #2271]	; 0x8df
d001b070:	fb02447c 	blx	0xd00ac26a
d001b074:	f5044508 			; <UNDEFINED> instruction: 0xf5044508
d001b078:	f5053625 			; <UNDEFINED> instruction: 0xf5053625
d001b07c:	f8963522 			; <UNDEFINED> instruction: 0xf8963522
d001b080:	f505711c 			; <UNDEFINED> instruction: 0xf505711c
d001b084:	f004708a 			; <UNDEFINED> instruction: 0xf004708a
d001b088:	230bf9ad 	movwcs	pc, #47533	; 0xb9ad	; <UNPREDICTABLE>
d001b08c:	46412200 	strbmi	r2, [r1], -r0, lsl #4
d001b090:	3135f885 	teqcc	r5, r5, lsl #17	; <UNPREDICTABLE>
d001b094:	f8854620 			; <UNDEFINED> instruction: 0xf8854620
d001b098:	f7f97134 			; <UNDEFINED> instruction: 0xf7f97134
d001b09c:	f7fafe70 			; <UNDEFINED> instruction: 0xf7fafe70
d001b0a0:	f8d6fa0d 			; <UNDEFINED> instruction: 0xf8d6fa0d
d001b0a4:	f504311c 			; <UNDEFINED> instruction: 0xf504311c
d001b0a8:	ee083229 	cdp	2, 0, cr3, cr8, cr9, {1}
d001b0ac:	33010a10 	movwcc	r0, #6672	; 0x1a10
d001b0b0:	311cf8c6 	tstcc	ip, r6, asr #17	; <UNPREDICTABLE>
d001b0b4:	f8d22600 			; <UNDEFINED> instruction: 0xf8d22600
d001b0b8:	46373130 			; <UNDEFINED> instruction: 0x46373130
d001b0bc:	1c59441c 	cfldrdne	mvd4, [r9], {28}
d001b0c0:	f5042302 			; <UNDEFINED> instruction: 0xf5042302
d001b0c4:	f8c23429 			; <UNDEFINED> instruction: 0xf8c23429
d001b0c8:	f8841130 			; <UNDEFINED> instruction: 0xf8841130
d001b0cc:	f8df3134 			; <UNDEFINED> instruction: 0xf8df3134
d001b0d0:	447b3534 	ldrbtmi	r3, [fp], #-1332	; 0xfffffacc
d001b0d4:	352bf503 	strcc	pc, [fp, #-1283]!	; 0xfffffafd
d001b0d8:	75bef505 	ldrvc	pc, [lr, #1285]!	; 0x505
d001b0dc:	4528f8df 	strmi	pc, [r8, #-2271]!	; 0xfffff721
d001b0e0:	6da3447c 	cfstrsvs	mvf4, [r3, #496]!	; 0x1f0
d001b0e4:	6ae3bb23 	bvs	0xcf909d78
d001b0e8:	d0212b7d 	eorle	r2, r1, sp, ror fp
d001b0ec:	7f80f5b3 	svcvc	0x0080f5b3
d001b0f0:	f240d01e 	vqadd.s8	d29, d0, d14
d001b0f4:	42931215 	addsmi	r1, r3, #1342177281	; 0x50000001
d001b0f8:	80f2f040 	rscshi	pc, r2, r0, asr #32
d001b0fc:	f7f74620 			; <UNDEFINED> instruction: 0xf7f74620
d001b100:	6a63fe79 	bvs	0xd191aaec
d001b104:	4620212d 	strtmi	r2, [r0], -sp, lsr #2
d001b108:	6aa39303 	bvs	0xce8ffd1c
d001b10c:	a030f894 	mlasge	r0, r4, r8, pc	; <UNPREDICTABLE>
d001b110:	6b639304 	blvs	0xd18ffd28
d001b114:	f7f79305 			; <UNDEFINED> instruction: 0xf7f79305
d001b118:	6ae3fe88 	bvs	0xcf91ab40
d001b11c:	7381f5a3 	orrvc	pc, r1, #683671552	; 0x28c00000
d001b120:	d9772b01 	ldmdble	r7!, {r0, r8, r9, fp, sp}^
d001b124:	14e4f8df 	strbtne	pc, [r4], #2271	; 0x8df	; <UNPREDICTABLE>
d001b128:	44794620 	ldrbtmi	r4, [r9], #-1568	; 0xfffff9e0
d001b12c:	f83cf7f5 			; <UNDEFINED> instruction: 0xf83cf7f5
d001b130:	44dcf8df 	ldrbmi	pc, [ip], #2271	; 0x8df	; <UNPREDICTABLE>
d001b134:	f8df217d 			; <UNDEFINED> instruction: 0xf8df217d
d001b138:	447c24dc 	ldrbtmi	r2, [ip], #-1244	; 0xfffffb24
d001b13c:	4620447a 			; <UNDEFINED> instruction: 0x4620447a
d001b140:	3b2df504 	blcc	0xd0b98558
d001b144:	fe7ff7f7 	mrc2	7, 3, pc, cr15, cr7, {7}
d001b148:	3229f504 	eorcc	pc, r9, #4, 10	; 0x1000000
d001b14c:	f8d24620 			; <UNDEFINED> instruction: 0xf8d24620
d001b150:	3b013130 	blcc	0xd0067618
d001b154:	3130f8c2 	teqcc	r0, r2, asr #17	; <UNPREDICTABLE>
d001b158:	3225f504 	eorcc	pc, r5, #4, 10	; 0x1000000
d001b15c:	311cf8d2 			; <UNDEFINED> instruction: 0x311cf8d2
d001b160:	f8c23b01 			; <UNDEFINED> instruction: 0xf8c23b01
d001b164:	f7fa311c 			; <UNDEFINED> instruction: 0xf7fa311c
d001b168:	f24ff9a9 	vmla.i8	d31, d31, d25
d001b16c:	23004298 	movwcs	r4, #664	; 0x298
d001b170:	ee184681 	cfmsub32	mvax4, mvfx4, mvfx8, mvfx1
d001b174:	58a21a10 	stmiapl	r2!, {r4, r9, fp, ip}
d001b178:	f7fa6da0 			; <UNDEFINED> instruction: 0xf7fa6da0
d001b17c:	9b00ff97 	blls	0xd005afe0
d001b180:	45abf503 	strmi	pc, [fp, #1283]!	; 0x503
d001b184:	352f469a 	strcc	r4, [pc, #-1690]!	; 0xd001aaf2
d001b188:	05c5eb04 	strbeq	lr, [r5, #2820]	; 0xb04
d001b18c:	3178f8db 	ldrsbcc	pc, [r8, #-139]!	; 0xffffff75	; <UNPREDICTABLE>
d001b190:	459a3508 	ldrmi	r3, [sl, #1288]	; 0x508
d001b194:	80d6f0c0 	sbcshi	pc, r6, r0, asr #1
d001b198:	2f004620 	svccs	0x00004620
d001b19c:	80f1f000 	rscshi	pc, r1, r0
d001b1a0:	f98cf7fa 			; <UNDEFINED> instruction: 0xf98cf7fa
d001b1a4:	6da04601 	stcvs	6, cr4, [r0, #4]!
d001b1a8:	23002400 	movwcs	r2, #1024	; 0x400
d001b1ac:	f7fa463a 			; <UNDEFINED> instruction: 0xf7fa463a
d001b1b0:	f8dfff7d 			; <UNDEFINED> instruction: 0xf8dfff7d
d001b1b4:	f24f5464 	vshl.s8	<illegal reg q10.5>, q10, <illegal reg q7.5>
d001b1b8:	46494398 			; <UNDEFINED> instruction: 0x46494398
d001b1bc:	f855447d 			; <UNDEFINED> instruction: 0xf855447d
d001b1c0:	2300a003 	movwcs	sl, #3
d001b1c4:	46526da8 	ldrbmi	r6, [r2], -r8, lsr #27
d001b1c8:	ff70f7fa 			; <UNDEFINED> instruction: 0xff70f7fa
d001b1cc:	2300b12c 	movwcs	fp, #300	; 0x12c
d001b1d0:	46214652 			; <UNDEFINED> instruction: 0x46214652
d001b1d4:	f7fa6da8 			; <UNDEFINED> instruction: 0xf7fa6da8
d001b1d8:	f8dfff69 			; <UNDEFINED> instruction: 0xf8dfff69
d001b1dc:	9d024440 	cfstrsls	mvf4, [r2, #-256]	; 0xffffff00
d001b1e0:	f504447c 			; <UNDEFINED> instruction: 0xf504447c
d001b1e4:	f5083829 			; <UNDEFINED> instruction: 0xf5083829
d001b1e8:	f8d877bc 			; <UNDEFINED> instruction: 0xf8d877bc
d001b1ec:	42952174 	addsmi	r2, r5, #116, 2
d001b1f0:	80cbf0c0 	sbchi	pc, fp, r0, asr #1
d001b1f4:	f5049a02 			; <UNDEFINED> instruction: 0xf5049a02
d001b1f8:	f8c8332d 			; <UNDEFINED> instruction: 0xf8c8332d
d001b1fc:	9a002174 	bls	0xd00237d4
d001b200:	2178f8c3 	cmncs	r8, r3, asr #17	; <UNPREDICTABLE>
d001b204:	f47f2e00 			; <UNDEFINED> instruction: 0xf47f2e00
d001b208:	f8dfaeef 			; <UNDEFINED> instruction: 0xf8dfaeef
d001b20c:	46201414 			; <UNDEFINED> instruction: 0x46201414
d001b210:	e6e74479 	uxtab	r4, r7, r9, ror #8
d001b214:	9020f8d4 	ldrdls	pc, [r0], -r4	; <UNPREDICTABLE>
d001b218:	f1c9b108 			; <UNDEFINED> instruction: 0xf1c9b108
d001b21c:	f8df0900 			; <UNDEFINED> instruction: 0xf8df0900
d001b220:	447c4404 	ldrbtmi	r4, [ip], #-1028	; 0xfffffbfc
d001b224:	f7f74620 			; <UNDEFINED> instruction: 0xf7f74620
d001b228:	4afffde5 	bmi	0xd001a9c4
d001b22c:	4620213a 			; <UNDEFINED> instruction: 0x4620213a
d001b230:	f7f7447a 			; <UNDEFINED> instruction: 0xf7f7447a
d001b234:	2800fe08 	stmdacs	r0, {r3, r9, sl, fp, ip, sp, lr, pc}
d001b238:	af7af43f 	svcge	0x007af43f
d001b23c:	f5046ea2 			; <UNDEFINED> instruction: 0xf5046ea2
d001b240:	49fa332d 	ldmibmi	sl!, {r0, r2, r3, r5, r8, r9, ip, sp}^
d001b244:	44799206 	ldrbtmi	r9, [r9], #-518	; 0xfffffdfa
d001b248:	3178f8d3 	ldrsbcc	pc, [r8, #-131]!	; 0xffffff7d	; <UNPREDICTABLE>
d001b24c:	91079a00 	tstls	r7, r0, lsl #20
d001b250:	0e16e9d4 			; <UNDEFINED> instruction: 0x0e16e9d4
d001b254:	cb18e9d4 	blgt	0xd06559ac
d001b258:	429a2400 	addsmi	r2, sl, #0, 8
d001b25c:	b13cd31b 	teqlt	ip, fp, lsl r3
d001b260:	99064af3 	stmdbls	r6, {r0, r1, r4, r5, r6, r7, r9, fp, lr}
d001b264:	e9c2447a 	stmib	r2, {r1, r3, r4, r5, r6, sl, lr}^
d001b268:	e9c20e16 	stmib	r2, {r1, r2, r4, r9, sl, fp}^
d001b26c:	6691cb18 			; <UNDEFINED> instruction: 0x6691cb18
d001b270:	7f80f5b3 	svcvc	0x0080f5b3
d001b274:	4befd11f 	blmi	0xcfc0f6f8
d001b278:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d001b27c:	4aeeb94a 	bmi	0xcfbc97ac
d001b280:	659a447a 	ldrvs	r4, [sl, #1146]	; 0x47a
d001b284:	65da9a03 	ldrbvs	r9, [sl, #2563]	; 0xa03
d001b288:	e9c39a04 	stmib	r3, {r2, r9, fp, ip, pc}^
d001b28c:	9a052a18 	bls	0xd0165af4
d001b290:	3601669a 			; <UNDEFINED> instruction: 0x3601669a
d001b294:	f855e722 			; <UNDEFINED> instruction: 0xf855e722
d001b298:	45491032 	strbmi	r1, [r9, #-50]	; 0xffffffce
d001b29c:	b940d109 	stmdblt	r0, {r0, r3, r8, ip, lr, pc}^
d001b2a0:	46d39905 	ldrbmi	r9, [r3], r5, lsl #18
d001b2a4:	c010f8dd 			; <UNDEFINED> instruction: 0xc010f8dd
d001b2a8:	f8dd2401 			; <UNDEFINED> instruction: 0xf8dd2401
d001b2ac:	9807e00c 	stmdals	r7, {r2, r3, sp, lr, pc}
d001b2b0:	32019106 	andcc	r9, r1, #-2147483647	; 0x80000001
d001b2b4:	4ae1e7d1 	bmi	0xcf895200
d001b2b8:	f5031c58 			; <UNDEFINED> instruction: 0xf5031c58
d001b2bc:	447a43ab 	ldrbtmi	r4, [sl], #-939	; 0xfffffc55
d001b2c0:	f502332f 			; <UNDEFINED> instruction: 0xf502332f
d001b2c4:	f8c1312d 			; <UNDEFINED> instruction: 0xf8c1312d
d001b2c8:	f5020178 			; <UNDEFINED> instruction: 0xf5020178
d001b2cc:	31984174 	orrscc	r4, r8, r4, ror r1
d001b2d0:	f8426809 			; <UNDEFINED> instruction: 0xf8426809
d001b2d4:	eb021033 	bl	0xd009f3a8
d001b2d8:	f8c303c3 			; <UNDEFINED> instruction: 0xf8c303c3
d001b2dc:	e7d89004 	ldrb	r9, [r8, r4]
d001b2e0:	718bf44f 	orrvc	pc, fp, pc, asr #8
d001b2e4:	f7f74620 			; <UNDEFINED> instruction: 0xf7f74620
d001b2e8:	b318fda0 	tstlt	r8, #160, 26	; 0x2800	; <UNPREDICTABLE>
d001b2ec:	213a4ad4 	teqcs	sl, r4	; <illegal shifter operand>
d001b2f0:	46206a63 	strtmi	r6, [r0], -r3, ror #20
d001b2f4:	f8d4447a 			; <UNDEFINED> instruction: 0xf8d4447a
d001b2f8:	f894b028 			; <UNDEFINED> instruction: 0xf894b028
d001b2fc:	f8d4a030 			; <UNDEFINED> instruction: 0xf8d4a030
d001b300:	93039034 	movwls	r9, #12340	; 0x3034
d001b304:	fd9ff7f7 	ldc2	7, cr15, [pc, #988]	; 0xd001b6e8
d001b308:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001b30c:	b167af11 	cmnlt	r7, r1, lsl pc
d001b310:	2a006da2 	bcs	0xd00369a0
d001b314:	4acbd1bd 	bmi	0xcf30fa10
d001b318:	447a9b03 	ldrbtmi	r9, [sl], #-2819	; 0xfffff4fd
d001b31c:	9068f8c4 	rsbls	pc, r8, r4, asr #17
d001b320:	65a265e3 	strvs	r6, [r2, #1507]!	; 0x5e3
d001b324:	ba18e9c4 	blt	0xd0655a3c
d001b328:	f504e7b3 			; <UNDEFINED> instruction: 0xf504e7b3
d001b32c:	f8d44474 			; <UNDEFINED> instruction: 0xf8d44474
d001b330:	e7ae7098 			; <UNDEFINED> instruction: 0xe7ae7098
d001b334:	ff00f7fe 			; <UNDEFINED> instruction: 0xff00f7fe
d001b338:	f47f2800 			; <UNDEFINED> instruction: 0xf47f2800
d001b33c:	f7ffaecf 			; <UNDEFINED> instruction: 0xf7ffaecf
d001b340:	e6cbfc4b 	strb	pc, [fp], fp, asr #24	; <UNPREDICTABLE>
d001b344:	22004620 	andcs	r4, r0, #32, 12	; 0x2000000
d001b348:	f10a4641 			; <UNDEFINED> instruction: 0xf10a4641
d001b34c:	f7f90a01 			; <UNDEFINED> instruction: 0xf7f90a01
d001b350:	f855fcfd 			; <UNDEFINED> instruction: 0xf855fcfd
d001b354:	21012c04 	tstcs	r1, r4, lsl #24
d001b358:	fc80f7f9 	stc2	7, cr15, [r0], {249}	; 0xf9
d001b35c:	f2444620 	vmax.s8	d20, d4, d16
d001b360:	f7f92188 			; <UNDEFINED> instruction: 0xf7f92188
d001b364:	f24dfc5d 	vfma.f32	<illegal reg q15.5>, <illegal reg q6.5>, <illegal reg q6.5>
d001b368:	f7f91101 			; <UNDEFINED> instruction: 0xf7f91101
d001b36c:	f7fafc59 			; <UNDEFINED> instruction: 0xf7fafc59
d001b370:	2300f8a5 	movwcs	pc, #2213	; 0x8a5	; <UNPREDICTABLE>
d001b374:	f8554601 			; <UNDEFINED> instruction: 0xf8554601
d001b378:	6da02c08 	stcvs	12, cr2, [r0, #32]!
d001b37c:	fe96f7fa 	mrc2	7, 4, pc, cr6, cr10, {7}
d001b380:	f7fae704 			; <UNDEFINED> instruction: 0xf7fae704
d001b384:	4604f89b 			; <UNDEFINED> instruction: 0x4604f89b
d001b388:	f857e713 			; <UNDEFINED> instruction: 0xf857e713
d001b38c:	23001025 	movwcs	r1, #37	; 0x25
d001b390:	6da04652 	stcvs	6, cr4, [r0, #328]!	; 0x148
d001b394:	f7fa3501 			; <UNDEFINED> instruction: 0xf7fa3501
d001b398:	e726fe89 	str	pc, [r6, -r9, lsl #29]!
d001b39c:	f46f6ae6 	vld1.64	{d22-d23}, [pc :128], r6
d001b3a0:	18b37288 	ldmne	r3!, {r3, r7, r9, ip, sp, lr}
d001b3a4:	d8662b01 	stmdale	r6!, {r0, r8, r9, fp, sp}^
d001b3a8:	1311f240 	tstne	r1, #64, 4	; <UNPREDICTABLE>
d001b3ac:	d00e429e 	mulle	lr, lr, r2
d001b3b0:	3128f8d5 	ldrdcc	pc, [r8, -r5]!
d001b3b4:	48a4b1ab 	stmiami	r4!, {r0, r1, r3, r5, r7, r8, ip, sp, pc}
d001b3b8:	f5004478 			; <UNDEFINED> instruction: 0xf5004478
d001b3bc:	f8d33325 			; <UNDEFINED> instruction: 0xf8d33325
d001b3c0:	f5b3312c 			; <UNDEFINED> instruction: 0xf5b3312c
d001b3c4:	d1237f00 			; <UNDEFINED> instruction: 0xd1237f00
d001b3c8:	447949a0 	ldrbtmi	r4, [r9], #-2464	; 0xfffff660
d001b3cc:	f504e481 			; <UNDEFINED> instruction: 0xf504e481
d001b3d0:	f8d43429 			; <UNDEFINED> instruction: 0xf8d43429
d001b3d4:	b93b3130 	ldmdblt	fp!, {r4, r5, r8, ip, sp}
d001b3d8:	4479499d 	ldrbtmi	r4, [r9], #-2461	; 0xfffff663
d001b3dc:	4478489d 	ldrbtmi	r4, [r8], #-2205	; 0xfffff763
d001b3e0:	499de477 	ldmibmi	sp, {r0, r1, r2, r4, r5, r6, sl, sp, lr, pc}
d001b3e4:	e7f94479 			; <UNDEFINED> instruction: 0xe7f94479
d001b3e8:	4478489c 	ldrbtmi	r4, [r8], #-2204	; 0xfffff764
d001b3ec:	f5034403 			; <UNDEFINED> instruction: 0xf5034403
d001b3f0:	f8933329 			; <UNDEFINED> instruction: 0xf8933329
d001b3f4:	2b023133 	blcs	0xd00a78c8
d001b3f8:	f500d1dd 			; <UNDEFINED> instruction: 0xf500d1dd
d001b3fc:	f8d33329 			; <UNDEFINED> instruction: 0xf8d33329
d001b400:	f5b33174 			; <UNDEFINED> instruction: 0xf5b33174
d001b404:	d1027f00 	tstle	r2, r0, lsl #30
d001b408:	44794995 	ldrbtmi	r4, [r9], #-2453	; 0xfffff66b
d001b40c:	2701e461 	strcs	lr, [r1, -r1, ror #8]
d001b410:	447c4c94 	ldrbtmi	r4, [ip], #-3220	; 0xfffff36c
d001b414:	f7f74620 			; <UNDEFINED> instruction: 0xf7f74620
d001b418:	4a93fced 	bmi	0xce51a7d4
d001b41c:	4620213b 			; <UNDEFINED> instruction: 0x4620213b
d001b420:	f7f7447a 			; <UNDEFINED> instruction: 0xf7f7447a
d001b424:	4620fd10 			; <UNDEFINED> instruction: 0x4620fd10
d001b428:	f848f7fa 			; <UNDEFINED> instruction: 0xf848f7fa
d001b42c:	f504b16f 			; <UNDEFINED> instruction: 0xf504b16f
d001b430:	f8d23229 			; <UNDEFINED> instruction: 0xf8d23229
d001b434:	1c593174 	ldfnee	f3, [r9], {116}	; 0x74
d001b438:	4329f503 	msrmi	CPSR_fc, #12582912	; 0xc00000
d001b43c:	f8c2335e 			; <UNDEFINED> instruction: 0xf8c2335e
d001b440:	f8441174 			; <UNDEFINED> instruction: 0xf8441174
d001b444:	f7ff0023 			; <UNDEFINED> instruction: 0xf7ff0023
d001b448:	f504bbf5 			; <UNDEFINED> instruction: 0xf504bbf5
d001b44c:	f8d23225 			; <UNDEFINED> instruction: 0xf8d23225
d001b450:	1c59312c 	ldfnee	f3, [r9], {44}	; 0x2c
d001b454:	43a5f503 			; <UNDEFINED> instruction: 0x43a5f503
d001b458:	f8c23326 			; <UNDEFINED> instruction: 0xf8c23326
d001b45c:	f844112c 			; <UNDEFINED> instruction: 0xf844112c
d001b460:	eb040033 	bl	0xd011b534
d001b464:	f24004c3 	vshl.s8	q8, <illegal reg q1.5>, q8
d001b468:	1af31311 	bne	0xcfce00b4
d001b46c:	415e425e 	cmpmi	lr, lr, asr r2
d001b470:	f7ff7126 			; <UNDEFINED> instruction: 0xf7ff7126
d001b474:	f240bbdf 	vpadd.i8	<illegal reg q13.5>, q8, <illegal reg q7.5>
d001b478:	4620110f 	strtmi	r1, [r0], -pc, lsl #2
d001b47c:	fcd5f7f7 	ldc2l	7, cr15, [r5], {247}	; 0xf7
d001b480:	d0712800 	rsbsle	r2, r1, r0, lsl #16
d001b484:	3422f504 	strtcc	pc, [r2], #-1284	; 0xfffffafc
d001b488:	3110f894 			; <UNDEFINED> instruction: 0x3110f894
d001b48c:	d1202b04 			; <UNDEFINED> instruction: 0xd1202b04
d001b490:	447c4c76 	ldrbtmi	r4, [ip], #-3190	; 0xfffff38a
d001b494:	3522f504 	strcc	pc, [r2, #-1284]!	; 0xfffffafc
d001b498:	f8954620 			; <UNDEFINED> instruction: 0xf8954620
d001b49c:	f7fb1111 			; <UNDEFINED> instruction: 0xf7fb1111
d001b4a0:	f895fe7d 			; <UNDEFINED> instruction: 0xf895fe7d
d001b4a4:	22011112 	andcs	r1, r1, #-2147483644	; 0x80000004
d001b4a8:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d001b4ac:	f895fc4f 			; <UNDEFINED> instruction: 0xf895fc4f
d001b4b0:	f44f3111 	vst4.8	{d19,d21,d23,d25}, [pc :64], r1
d001b4b4:	fb02721a 	blx	0xd00b7d26
d001b4b8:	f5034303 			; <UNDEFINED> instruction: 0xf5034303
d001b4bc:	f8b333c9 			; <UNDEFINED> instruction: 0xf8b333c9
d001b4c0:	f7fa0108 			; <UNDEFINED> instruction: 0xf7fa0108
d001b4c4:	f244fda1 	vadd.f32	d31, d20, d17
d001b4c8:	46206108 	strtmi	r6, [r0], -r8, lsl #2
d001b4cc:	fba8f7f9 	blx	0xcea594ba
d001b4d0:	2b05e009 	blcs	0xd01934fc
d001b4d4:	4866d11a 	stmdami	r6!, {r1, r3, r4, r8, ip, lr, pc}^
d001b4d8:	f5004478 			; <UNDEFINED> instruction: 0xf5004478
d001b4dc:	f8933322 			; <UNDEFINED> instruction: 0xf8933322
d001b4e0:	f7fc1111 			; <UNDEFINED> instruction: 0xf7fc1111
d001b4e4:	4c63fab1 			; <UNDEFINED> instruction: 0x4c63fab1
d001b4e8:	4a63213b 	bmi	0xd18e39dc
d001b4ec:	447a447c 	ldrbtmi	r4, [sl], #-1148	; 0xfffffb84
d001b4f0:	f7f74620 			; <UNDEFINED> instruction: 0xf7f74620
d001b4f4:	f504fca8 			; <UNDEFINED> instruction: 0xf504fca8
d001b4f8:	f8d33322 			; <UNDEFINED> instruction: 0xf8d33322
d001b4fc:	f5b5510c 			; <UNDEFINED> instruction: 0xf5b5510c
d001b500:	d1236f80 	smlawble	r3, r0, pc, r6	; <UNPREDICTABLE>
d001b504:	4479495d 	ldrbtmi	r4, [r9], #-2397	; 0xfffff6a3
d001b508:	bb7cf7ff 	bllt	0xd1f5950c
d001b50c:	d0132b01 	andsle	r2, r3, r1, lsl #22
d001b510:	2b034c5b 	blcs	0xd00ee684
d001b514:	0101f04f 	tsteq	r1, pc, asr #32	; <UNPREDICTABLE>
d001b518:	bf0c447c 	svclt	0x000c447c
d001b51c:	22012204 	andcs	r2, r1, #4, 4	; 0x40000000
d001b520:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d001b524:	f504fe6f 			; <UNDEFINED> instruction: 0xf504fe6f
d001b528:	f8933322 			; <UNDEFINED> instruction: 0xf8933322
d001b52c:	2b023110 	blcs	0xd00a7974
d001b530:	f24bd1d9 	vand	<illegal reg q14.5>, <illegal reg q13.5>, <illegal reg q4.5>
d001b534:	e7c821c0 	strb	r2, [r8, r0, asr #3]
d001b538:	44784852 	ldrbtmi	r4, [r8], #-2130	; 0xfffff7ae
d001b53c:	2b3b6ac3 	blcs	0xd0ef6050
d001b540:	4951d0d1 	ldmdbmi	r1, {r0, r4, r6, r7, ip, lr, pc}^
d001b544:	f7f44479 			; <UNDEFINED> instruction: 0xf7f44479
d001b548:	e7ccfe2f 	strb	pc, [ip, pc, lsr #28]	; <UNPREDICTABLE>
d001b54c:	f5051c6a 			; <UNDEFINED> instruction: 0xf5051c6a
d001b550:	4620451e 			; <UNDEFINED> instruction: 0x4620451e
d001b554:	f8c33542 			; <UNDEFINED> instruction: 0xf8c33542
d001b558:	f7f9210c 			; <UNDEFINED> instruction: 0xf7f9210c
d001b55c:	eb04ffaf 	bl	0xd015b420
d001b560:	60600485 	rsbvs	r0, r0, r5, lsl #9
d001b564:	bb66f7ff 	bllt	0xd19d9568
d001b568:	4620213b 			; <UNDEFINED> instruction: 0x4620213b
d001b56c:	fc5df7f7 	mrrc2	7, 15, pc, sp, cr7	; <UNPREDICTABLE>
d001b570:	f47f2800 			; <UNDEFINED> instruction: 0xf47f2800
d001b574:	f7fdab5f 			; <UNDEFINED> instruction: 0xf7fdab5f
d001b578:	4a44ff5f 	bmi	0xd115b2fc
d001b57c:	213b4844 	teqcs	fp, r4, asr #16
d001b580:	4478447a 	ldrbtmi	r4, [r8], #-1146	; 0xfffffb86
d001b584:	fc5ff7f7 	mrrc2	7, 15, pc, pc, cr7	; <UNPREDICTABLE>
d001b588:	bb54f7ff 	bllt	0xd155958c
d001b58c:	0000883c 	andeq	r8, r0, ip, lsr r8
d001b590:	ffffb4c0 			; <UNDEFINED> instruction: 0xffffb4c0
d001b594:	000087e4 	andeq	r8, r0, r4, ror #15
d001b598:	fffffbfd 			; <UNDEFINED> instruction: 0xfffffbfd
d001b59c:	0000874c 	andeq	r8, r0, ip, asr #14
d001b5a0:	fffffbd5 			; <UNDEFINED> instruction: 0xfffffbd5
d001b5a4:	000086fe 	strdeq	r8, [r0], -lr
d001b5a8:	000086fa 	strdeq	r8, [r0], -sl
d001b5ac:	fffffb2c 			; <UNDEFINED> instruction: 0xfffffb2c
d001b5b0:	fffffb07 			; <UNDEFINED> instruction: 0xfffffb07
d001b5b4:	00008604 	andeq	r8, r0, r4, lsl #12
d001b5b8:	000085f6 	strdeq	r8, [r0], -r6
d001b5bc:	000085ca 	andeq	r8, r0, sl, asr #11
d001b5c0:	fffffaec 			; <UNDEFINED> instruction: 0xfffffaec
d001b5c4:	0000859c 	muleq	r0, ip, r5
d001b5c8:	fffffadf 			; <UNDEFINED> instruction: 0xfffffadf
d001b5cc:	fffffa15 			; <UNDEFINED> instruction: 0xfffffa15
d001b5d0:	00008546 	andeq	r8, r0, r6, asr #10
d001b5d4:	00008504 	andeq	r8, r0, r4, lsl #10
d001b5d8:	00008500 	andeq	r8, r0, r0, lsl #10
d001b5dc:	fffff92f 			; <UNDEFINED> instruction: 0xfffff92f
d001b5e0:	fffff9b3 			; <UNDEFINED> instruction: 0xfffff9b3
d001b5e4:	fffff9b9 			; <UNDEFINED> instruction: 0xfffff9b9
d001b5e8:	0000843a 	andeq	r8, r0, sl, lsr r4
d001b5ec:	0000842e 	andeq	r8, r0, lr, lsr #8
d001b5f0:	00008418 	andeq	r8, r0, r8, lsl r4
d001b5f4:	fffff9c1 			; <UNDEFINED> instruction: 0xfffff9c1
d001b5f8:	fffff9b3 			; <UNDEFINED> instruction: 0xfffff9b3
d001b5fc:	fffff9c6 			; <UNDEFINED> instruction: 0xfffff9c6
d001b600:	000083ac 	andeq	r8, r0, ip, lsr #7
d001b604:	0000834a 	andeq	r8, r0, sl, asr #6
d001b608:	0000833c 	andeq	r8, r0, ip, lsr r3
d001b60c:	fffff900 			; <UNDEFINED> instruction: 0xfffff900
d001b610:	000082e2 	andeq	r8, r0, r2, ror #5
d001b614:	fffff96b 			; <UNDEFINED> instruction: 0xfffff96b
d001b618:	00008260 	andeq	r8, r0, r0, ror #4
d001b61c:	0000823c 	andeq	r8, r0, ip, lsr r2
d001b620:	fffff8b6 			; <UNDEFINED> instruction: 0xfffff8b6
d001b624:	000081fa 	strdeq	r8, [r0], -sl
d001b628:	fffff81f 			; <UNDEFINED> instruction: 0xfffff81f
d001b62c:	fffff632 			; <UNDEFINED> instruction: 0xfffff632
d001b630:	000081b8 			; <UNDEFINED> instruction: 0x000081b8
d001b634:	000081a4 	andeq	r8, r0, r4, lsr #3
d001b638:	fffff6fd 			; <UNDEFINED> instruction: 0xfffff6fd
d001b63c:	0000815e 	andeq	r8, r0, lr, asr r1
d001b640:	fffff779 			; <UNDEFINED> instruction: 0xfffff779
d001b644:	fffff76e 			; <UNDEFINED> instruction: 0xfffff76e
d001b648:	00008064 	andeq	r8, r0, r4, rrx
d001b64c:	fffff73d 			; <UNDEFINED> instruction: 0xfffff73d
d001b650:	fffff4d2 			; <UNDEFINED> instruction: 0xfffff4d2
d001b654:	0000803e 	andeq	r8, r0, lr, lsr r0
d001b658:	fffff4b0 			; <UNDEFINED> instruction: 0xfffff4b0
d001b65c:	00008032 	andeq	r8, r0, r2, lsr r0
d001b660:	fffff6e6 			; <UNDEFINED> instruction: 0xfffff6e6
d001b664:	0000800a 	andeq	r8, r0, sl
d001b668:	fffff709 			; <UNDEFINED> instruction: 0xfffff709
d001b66c:	00007f8a 	andeq	r7, r0, sl, lsl #31
d001b670:	00007f44 	andeq	r7, r0, r4, asr #30
d001b674:	00007f30 	andeq	r7, r0, r0, lsr pc
d001b678:	fffff68c 			; <UNDEFINED> instruction: 0xfffff68c
d001b67c:	fffff68e 			; <UNDEFINED> instruction: 0xfffff68e
d001b680:	00007f04 	andeq	r7, r0, r4, lsl #30
d001b684:	00007ee2 	andeq	r7, r0, r2, ror #29
d001b688:	fffff60a 			; <UNDEFINED> instruction: 0xfffff60a
d001b68c:	fffff635 			; <UNDEFINED> instruction: 0xfffff635
d001b690:	00007e9a 	muleq	r0, sl, lr

Disassembly of section .text.block.constprop.0:

d001b6b4 <.text.block.constprop.0>:
d001b6b4:	4c0db510 	cfstr32mi	mvfx11, [sp], {16}
d001b6b8:	6da3447c 	cfstrsvs	mvf4, [r3, #496]!	; 0x1f0
d001b6bc:	6ae3b92b 	bvs	0xcf909b70
d001b6c0:	d0022b7d 	andle	r2, r2, sp, ror fp
d001b6c4:	7f80f5b3 	svcvc	0x0080f5b3
d001b6c8:	4a09d108 	bmi	0xd028faf0
d001b6cc:	4809217d 	stmdami	r9, {r0, r2, r3, r4, r5, r6, r8, sp}
d001b6d0:	4478447a 	ldrbtmi	r4, [r8], #-1146	; 0xfffffb86
d001b6d4:	4010e8bd 			; <UNDEFINED> instruction: 0x4010e8bd
d001b6d8:	bbb5f7f7 	bllt	0xced996bc
d001b6dc:	fd2cf7fe 	stc2	7, cr15, [ip, #-1016]!	; 0xfffffc08
d001b6e0:	d1ea2800 	mvnle	r2, r0, lsl #16
d001b6e4:	fa78f7ff 	blx	0xd1e596e8
d001b6e8:	bf00e7e7 	svclt	0x0000e7e7
d001b6ec:	00007d64 	andeq	r7, r0, r4, ror #26
d001b6f0:	ffffffc0 			; <UNDEFINED> instruction: 0xffffffc0
d001b6f4:	00007d4a 	andeq	r7, r0, sl, asr #26

Disassembly of section .text.global_declaration.constprop.0:

d001b87c <.text.global_declaration.constprop.0>:
d001b87c:	e92db084 	push	{r2, r7, ip, sp, pc}
d001b880:	b08b4ff0 	strdlt	r4, [fp], r0
d001b884:	a454f8df 	ldrbge	pc, [r4], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d001b888:	44faac14 	ldrbtmi	sl, [sl], #3092	; 0xc14
d001b88c:	f89d9004 			; <UNDEFINED> instruction: 0xf89d9004
d001b890:	9d1db070 	ldcls	0, cr11, [sp, #-448]	; 0xfffffe40
d001b894:	000fe884 	andeq	lr, pc, r4, lsl #17
d001b898:	46019a15 			; <UNDEFINED> instruction: 0x46019a15
d001b89c:	f8dd4650 			; <UNDEFINED> instruction: 0xf8dd4650
d001b8a0:	9205905c 	andls	r9, r5, #92	; 0x5c
d001b8a4:	8060f8dd 	ldrdhi	pc, [r0], #-141	; 0xffffff73	; <UNPREDICTABLE>
d001b8a8:	7068f89d 	mlsvc	r8, sp, r8, pc	; <UNPREDICTABLE>
d001b8ac:	f7f49e1b 			; <UNDEFINED> instruction: 0xf7f49e1b
d001b8b0:	9a05ffaf 	bls	0xd019b774
d001b8b4:	99044604 	stmdbls	r4, {r2, r9, sl, lr}
d001b8b8:	f7f44650 			; <UNDEFINED> instruction: 0xf7f44650
d001b8bc:	2800ff66 	stmdacs	r0, {r1, r2, r5, r6, r8, r9, sl, fp, ip, sp, lr, pc}
d001b8c0:	9a059904 	bls	0xd0181cd8
d001b8c4:	f8dfdb11 			; <UNDEFINED> instruction: 0xf8dfdb11
d001b8c8:	447b3418 	ldrbtmi	r3, [fp], #-1048	; 0xfffffbe8
d001b8cc:	b93a6d9a 	ldmdblt	sl!, {r1, r3, r4, r7, r8, sl, fp, sp, lr}
d001b8d0:	2410f8df 	ldrcs	pc, [r0], #-2271	; 0xfffff721
d001b8d4:	447a669e 	ldrbtmi	r6, [sl], #-1694	; 0xfffff962
d001b8d8:	8718e9c3 	ldrhi	lr, [r8, -r3, asr #19]
d001b8dc:	2916e9c3 	ldmdbcs	r6, {r0, r1, r6, r7, r8, fp, sp, lr, pc}
d001b8e0:	e8bdb00b 	pop	{r0, r1, r3, ip, sp, pc}
d001b8e4:	b0044ff0 	strdlt	r4, [r4], -r0
d001b8e8:	46504770 			; <UNDEFINED> instruction: 0x46504770
d001b8ec:	91049205 	tstls	r4, r5, lsl #4
d001b8f0:	ff27f7f4 			; <UNDEFINED> instruction: 0xff27f7f4
d001b8f4:	dae62800 	ble	0xcf9a58fc
d001b8f8:	99042c00 	stmdbls	r4, {sl, fp, sp}
d001b8fc:	db0a9a05 	blle	0xd02c2118
d001b900:	f89a2038 			; <UNDEFINED> instruction: 0xf89a2038
d001b904:	fb003008 	blx	0xd002792e
d001b908:	f504a404 			; <UNDEFINED> instruction: 0xf504a404
d001b90c:	f8943400 			; <UNDEFINED> instruction: 0xf8943400
d001b910:	4298012d 	addsmi	r0, r8, #1073741835	; 0x4000000b
d001b914:	4cf4d0d7 	ldclmi	0, cr13, [r4], #860	; 0x35c
d001b918:	447c9205 	ldrbtmi	r9, [ip], #-517	; 0xfffffdfb
d001b91c:	46209104 	strtmi	r9, [r0], -r4, lsl #2
d001b920:	ffd2f7f4 			; <UNDEFINED> instruction: 0xffd2f7f4
d001b924:	9a059904 	bls	0xd0181d3c
d001b928:	d1cc2800 	bicle	r2, ip, r0, lsl #16
d001b92c:	f7f44620 			; <UNDEFINED> instruction: 0xf7f44620
d001b930:	2800ffad 	stmdacs	r0, {r0, r2, r3, r5, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d001b934:	f504d1c7 			; <UNDEFINED> instruction: 0xf504d1c7
d001b938:	f8d333c8 			; <UNDEFINED> instruction: 0xf8d333c8
d001b93c:	2b8030a4 	blcs	0xce027bd4
d001b940:	6da3d10a 	stfvsd	f5, [r3, #40]!	; 0x28
d001b944:	d1cb2b00 	bicle	r2, fp, r0, lsl #22
d001b948:	447b4be8 	ldrbtmi	r4, [fp], #-3048	; 0xfffff418
d001b94c:	e9c466a6 	stmib	r4, {r1, r2, r5, r7, r9, sl, sp, lr}^
d001b950:	e9c43916 	stmib	r4, {r1, r2, r4, r8, fp, ip, sp}^
d001b954:	e7c38718 	bfi	r8, r8, (invalid: 14:3)
d001b958:	4620215b 			; <UNDEFINED> instruction: 0x4620215b
d001b95c:	fa65f7f7 	blx	0xd1999940
d001b960:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d001b964:	b12d808d 	smlawblt	sp, sp, r0, r8
d001b968:	2b006da3 	blcs	0xd0036ffc
d001b96c:	4be0d1b8 	blmi	0xcf850054
d001b970:	e7eb447b 			; <UNDEFINED> instruction: 0xe7eb447b
d001b974:	0f05f1bb 	svceq	0x0005f1bb
d001b978:	f1bbd008 			; <UNDEFINED> instruction: 0xf1bbd008
d001b97c:	d0050f00 	andle	r0, r5, r0, lsl #30
d001b980:	2b006da3 	blcs	0xd0037014
d001b984:	4bdbd1ac 	blmi	0xcf71003c
d001b988:	e7df447b 			; <UNDEFINED> instruction: 0xe7df447b
d001b98c:	447b4bda 	ldrbtmi	r4, [fp], #-3034	; 0xfffff426
d001b990:	6a5e6ad8 	bvs	0xd17b64f8
d001b994:	7081f5a0 	addvc	pc, r1, r0, lsr #11
d001b998:	f8936a9c 			; <UNDEFINED> instruction: 0xf8936a9c
d001b99c:	28011030 	stmdacs	r1, {r4, r5, ip}
d001b9a0:	d8016b5a 	stmdale	r1, {r1, r3, r4, r6, r8, r9, fp, sp, lr}
d001b9a4:	b9606a18 	stmdblt	r0!, {r3, r4, r9, fp, sp, lr}^
d001b9a8:	447b4bd4 	ldrbtmi	r4, [fp], #-3028	; 0xfffff42c
d001b9ac:	28006d98 	stmdacs	r0, {r3, r4, r7, r8, sl, fp, sp, lr}
d001b9b0:	48d3d196 	ldmmi	r3, {r1, r2, r4, r7, r8, ip, lr, pc}^
d001b9b4:	669a4478 			; <UNDEFINED> instruction: 0x669a4478
d001b9b8:	0616e9c3 	ldreq	lr, [r6], -r3, asr #19
d001b9bc:	4118e9c3 	tstmi	r8, r3, asr #19
d001b9c0:	f1bbe78e 			; <UNDEFINED> instruction: 0xf1bbe78e
d001b9c4:	d1080f00 	tstle	r8, r0, lsl #30
d001b9c8:	3f80f5b0 	svccc	0x0080f5b0
d001b9cc:	6d98d924 	vldrvs.16	s26, [r8, #72]	; 0x48	; <UNPREDICTABLE>
d001b9d0:	d1852800 	orrle	r2, r5, r0, lsl #16
d001b9d4:	447848cb 	ldrbtmi	r4, [r8], #-2251	; 0xfffff735
d001b9d8:	2701e7ed 	strcs	lr, [r1, -sp, ror #15]
d001b9dc:	447b4bca 	ldrbtmi	r4, [fp], #-3018	; 0xfffff436
d001b9e0:	33f8f503 	mvnscc	pc, #12582912	; 0xc00000
d001b9e4:	30fcf8d3 	ldrsbtcc	pc, [ip], #131	; 0x83	; <UNPREDICTABLE>
d001b9e8:	0f00f1bb 	svceq	0x0000f1bb
d001b9ec:	3303d102 	movwcc	sp, #12546	; 0x3102
d001b9f0:	0303f023 	movweq	pc, #12323	; 0x3023	; <UNPREDICTABLE>
d001b9f4:	2f80f5b3 	svccs	0x0080f5b3
d001b9f8:	fb07d805 	blx	0xd0211a16
d001b9fc:	f5c3f900 			; <UNDEFINED> instruction: 0xf5c3f900
d001ba00:	45992380 	ldrmi	r2, [r9, #896]	; 0x380
d001ba04:	4bc1d90a 	blmi	0xcf091e34
d001ba08:	6d98447b 	cfldrsvs	mvf4, [r8, #492]	; 0x1ec
d001ba0c:	f47f2800 			; <UNDEFINED> instruction: 0xf47f2800
d001ba10:	48bfaf67 	ldmmi	pc!, {r0, r1, r2, r5, r6, r8, r9, sl, fp, sp, pc}	; <UNPREDICTABLE>
d001ba14:	e7ce4478 			; <UNDEFINED> instruction: 0xe7ce4478
d001ba18:	e7df2704 	ldrb	r2, [pc, r4, lsl #14]
d001ba1c:	447848bd 	ldrbtmi	r4, [r8], #-2237	; 0xfffff743
d001ba20:	f7f79004 			; <UNDEFINED> instruction: 0xf7f79004
d001ba24:	4abcf9e7 	bmi	0xcef5a1c8
d001ba28:	9804215d 	stmdals	r4, {r0, r2, r3, r4, r6, r8, sp}
d001ba2c:	f7f7447a 			; <UNDEFINED> instruction: 0xf7f7447a
d001ba30:	2800fa0a 	stmdacs	r0, {r1, r3, r9, fp, ip, sp, lr, pc}
d001ba34:	af54f43f 	svcge	0x0054f43f
d001ba38:	0f00f1bb 	svceq	0x0000f1bb
d001ba3c:	ea4fd123 	b	0xd140fed0
d001ba40:	f04f0699 			; <UNDEFINED> instruction: 0xf04f0699
d001ba44:	4fb50b08 	svcmi	0x00b50b08
d001ba48:	447f213d 	ldrbtmi	r2, [pc], #-317	; 0xd001ba50
d001ba4c:	3800f507 	stmdacc	r0, {r0, r1, r2, r8, sl, ip, sp, lr, pc}
d001ba50:	f8d84638 			; <UNDEFINED> instruction: 0xf8d84638
d001ba54:	93043100 	movwls	r3, #16640	; 0x4100
d001ba58:	f9e7f7f7 			; <UNDEFINED> instruction: 0xf9e7f7f7
d001ba5c:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d001ba60:	f1ab80cd 			; <UNDEFINED> instruction: 0xf1ab80cd
d001ba64:	2b010307 	blcs	0xd005c688
d001ba68:	f8d8d837 			; <UNDEFINED> instruction: 0xf8d8d837
d001ba6c:	f5c33100 			; <UNDEFINED> instruction: 0xf5c33100
d001ba70:	42b36380 	adcsmi	r6, r3, #128, 6
d001ba74:	f7f8d20b 			; <UNDEFINED> instruction: 0xf7f8d20b
d001ba78:	2300fa51 	movwcs	pc, #2641	; 0xa51	; <UNPREDICTABLE>
d001ba7c:	e0622400 	rsb	r2, r2, r0, lsl #8
d001ba80:	46064681 	strmi	r4, [r6], -r1, lsl #13
d001ba84:	464ee7df 			; <UNDEFINED> instruction: 0x464ee7df
d001ba88:	0b07f04f 	bleq	0xd0217bcc
d001ba8c:	4630e7db 			; <UNDEFINED> instruction: 0x4630e7db
d001ba90:	fa0cf7f8 	blx	0xd0359a78
d001ba94:	28004604 	stmdacs	r0, {r2, r9, sl, lr}
d001ba98:	af22f43f 	svcge	0x0022f43f
d001ba9c:	0207f1ab 	andeq	pc, r7, #-1073741782	; 0xc000002a
d001baa0:	425321ff 	subsmi	r2, r3, #-1073741761	; 0xc000003f
d001baa4:	22004153 	andcs	r4, r0, #-1073741804	; 0xc0000014
d001baa8:	46039300 	strmi	r9, [r3], -r0, lsl #6
d001baac:	f7fe4630 			; <UNDEFINED> instruction: 0xf7fe4630
d001bab0:	4620f977 			; <UNDEFINED> instruction: 0x4620f977
d001bab4:	0386eb04 	orreq	lr, r6, #4, 22	; 0x1000
d001bab8:	d0de4283 	sbcsle	r4, lr, r3, lsl #5
d001babc:	2b04f850 	blcs	0xd0159c04
d001bac0:	d0f92a00 	rscsle	r2, r9, r0, lsl #20
d001bac4:	447b4b96 	ldrbtmi	r4, [fp], #-2966	; 0xfffff46a
d001bac8:	3300f503 	movwcc	pc, #1283	; 0x503	; <UNPREDICTABLE>
d001bacc:	2100f8d3 	ldrdcs	pc, [r0, -r3]
d001bad0:	f8c34432 			; <UNDEFINED> instruction: 0xf8c34432
d001bad4:	23012100 	movwcs	r2, #4352	; 0x1100
d001bad8:	212de7d0 	ldrdcs	lr, [sp, -r0]!
d001badc:	f7f74638 			; <UNDEFINED> instruction: 0xf7f74638
d001bae0:	6a7bf9a4 	bvs	0xd1f1a178
d001bae4:	f44f4680 	vst1.32	{d20-d22}, [pc], r0
d001bae8:	9305718d 	movwls	r7, #20877	; 0x518d
d001baec:	6abb4638 	bvs	0xceeed3d4
d001baf0:	93066afc 	movwls	r6, #27388	; 0x6afc
d001baf4:	3030f897 	mlascc	r0, r7, r8, pc	; <UNPREDICTABLE>
d001baf8:	a206e9d7 	andge	lr, r6, #3522560	; 0x35c000
d001bafc:	6b7b9307 	blvs	0xd1f00720
d001bb00:	93089209 	movwls	r9, #33289	; 0x8209
d001bb04:	f991f7f7 			; <UNDEFINED> instruction: 0xf991f7f7
d001bb08:	b1209a09 			; <UNDEFINED> instruction: 0xb1209a09
d001bb0c:	f7f74638 			; <UNDEFINED> instruction: 0xf7f74638
d001bb10:	4604ff29 	strmi	pc, [r4], -r9, lsr #30
d001bb14:	f240e00d 	vhadd.s8	d30, d0, d13
d001bb18:	429c1301 	addsmi	r1, ip, #67108864	; 0x4000000
d001bb1c:	4651d13e 			; <UNDEFINED> instruction: 0x4651d13e
d001bb20:	f7f44638 			; <UNDEFINED> instruction: 0xf7f44638
d001bb24:	2800fed1 	stmdacs	r0, {r0, r4, r6, r7, r9, sl, fp, ip, sp, lr, pc}
d001bb28:	6a04d05e 	bvs	0xd014fca8
d001bb2c:	f7f74638 			; <UNDEFINED> instruction: 0xf7f74638
d001bb30:	f1b8f961 			; <UNDEFINED> instruction: 0xf1b8f961
d001bb34:	d0000f00 	andle	r0, r0, r0, lsl #30
d001bb38:	f1bb4264 			; <UNDEFINED> instruction: 0xf1bb4264
d001bb3c:	f04f0f05 			; <UNDEFINED> instruction: 0xf04f0f05
d001bb40:	bf080300 	svclt	0x00080300
d001bb44:	4f77b2e4 	svcmi	0x0077b2e4
d001bb48:	4a77213b 	bmi	0xd1de403c
d001bb4c:	9302447f 	movwls	r4, #9343	; 0x247f
d001bb50:	4638447a 			; <UNDEFINED> instruction: 0x4638447a
d001bb54:	f977f7f7 			; <UNDEFINED> instruction: 0xf977f7f7
d001bb58:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001bb5c:	f1abaec1 			; <UNDEFINED> instruction: 0xf1abaec1
d001bb60:	9b020207 	blls	0xd009c384
d001bb64:	f2002a01 	vpmax.s8	d2, d0, d1
d001bb68:	2b0080aa 	blcs	0xd003be18
d001bb6c:	f1bbd048 			; <UNDEFINED> instruction: 0xf1bbd048
d001bb70:	d1080f08 	tstle	r8, r8, lsl #30
d001bb74:	37f8f507 	ldrbcc	pc, [r8, r7, lsl #10]!	; <UNPREDICTABLE>
d001bb78:	20f8f8d7 	ldrsbtcs	pc, [r8], #135	; 0x87	; <UNPREDICTABLE>
d001bb7c:	f0223203 			; <UNDEFINED> instruction: 0xf0223203
d001bb80:	f8c70203 			; <UNDEFINED> instruction: 0xf8c70203
d001bb84:	4a6920f8 	bmi	0xd1a63f6c
d001bb88:	f502447a 			; <UNDEFINED> instruction: 0xf502447a
d001bb8c:	f8d232f8 			; <UNDEFINED> instruction: 0xf8d232f8
d001bb90:	eb0770f8 	bl	0xd01f7f78
d001bb94:	f8c20109 			; <UNDEFINED> instruction: 0xf8c20109
d001bb98:	e04710f8 	strd	r1, [r7], #-8
d001bb9c:	7481f5a4 	strvc	pc, [r1], #1444	; 0x5a4
d001bba0:	d8212c01 	stmdale	r1!, {r0, sl, fp, sp}
d001bba4:	21014602 	tstcs	r1, r2, lsl #12
d001bba8:	f7f74638 			; <UNDEFINED> instruction: 0xf7f74638
d001bbac:	6dbbf9d7 			; <UNDEFINED> instruction: 0x6dbbf9d7
d001bbb0:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001bbb4:	f110ae95 			; <UNDEFINED> instruction: 0xf110ae95
d001bbb8:	93024300 	movwls	r4, #8960	; 0x2300
d001bbbc:	0300f141 	movweq	pc, #321	; 0x141	; <UNPREDICTABLE>
d001bbc0:	e9dd9303 	ldmib	sp, {r0, r1, r8, r9, ip, pc}^
d001bbc4:	2c013402 	cfstrscs	mvf3, [r1], {2}
d001bbc8:	f1b3bf08 			; <UNDEFINED> instruction: 0xf1b3bf08
d001bbcc:	d3a04f00 	movle	r4, #0, 30
d001bbd0:	447b4b57 	ldrbtmi	r4, [fp], #-2903	; 0xfffff4a9
d001bbd4:	9b0565bb 	blls	0xd01752c8
d001bbd8:	9b0665fb 	blls	0xd01b53cc
d001bbdc:	9b07663b 	blls	0xd01f54d0
d001bbe0:	9b08667b 	blls	0xd02355d4
d001bbe4:	e67b66bb 			; <UNDEFINED> instruction: 0xe67b66bb
d001bbe8:	48534952 	ldmdami	r3, {r1, r4, r6, r8, fp, lr}^
d001bbec:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d001bbf0:	e8bdb00b 	pop	{r0, r1, r3, ip, sp, pc}
d001bbf4:	b0044ff0 	strdlt	r4, [r4], -r0
d001bbf8:	bad6f7f4 	blt	0xcf5d9bd0
d001bbfc:	e79c4604 	ldr	r4, [ip, r4, lsl #12]
d001bc00:	0f08f1bb 	svceq	0x0008f1bb
d001bc04:	f507d108 			; <UNDEFINED> instruction: 0xf507d108
d001bc08:	f8d737f8 			; <UNDEFINED> instruction: 0xf8d737f8
d001bc0c:	320320fc 	andcc	r2, r3, #252	; 0xfc
d001bc10:	0203f022 	andeq	pc, r3, #34	; 0x22
d001bc14:	20fcf8c7 	rscscs	pc, ip, r7, asr #17
d001bc18:	447a4a48 	ldrbtmi	r4, [sl], #-2632	; 0xfffff5b8
d001bc1c:	32f8f502 	rscscc	pc, r8, #8388608	; 0x800000
d001bc20:	70fcf8d2 	ldrsbtvc	pc, [ip], #130	; 0x82	; <UNPREDICTABLE>
d001bc24:	0109eb07 	tsteq	r9, r7, lsl #22
d001bc28:	10fcf8c2 	rscsne	pc, ip, r2, asr #17
d001bc2c:	2b004a44 	blcs	0xd002e544
d001bc30:	fa83fa5f 	blx	0xce11a5b4
d001bc34:	bf08447a 	svclt	0x0008447a
d001bc38:	f1bb2600 			; <UNDEFINED> instruction: 0xf1bb2600
d001bc3c:	fa5f0f08 	blx	0xd17df864
d001bc40:	f502f885 			; <UNDEFINED> instruction: 0xf502f885
d001bc44:	7a1231c8 	bvc	0xd04a836c
d001bc48:	f8d1b2b6 			; <UNDEFINED> instruction: 0xf8d1b2b6
d001bc4c:	920200a4 	andls	r0, r2, #164	; 0xa4
d001bc50:	0c01f100 	stfeqd	f7, [r1], {-0}
d001bc54:	2010f8bd 			; <UNDEFINED> instruction: 0x2010f8bd
d001bc58:	c0a4f8c1 	adcgt	pc, r4, r1, asr #17
d001bc5c:	d1379204 	teqle	r7, r4, lsl #4
d001bc60:	0999ea4f 	ldmibeq	r9, {r0, r1, r2, r3, r6, r9, fp, sp, lr, pc}
d001bc64:	22384d37 	eorscs	r4, r8, #3520	; 0xdc0
d001bc68:	447d2100 	ldrbtmi	r2, [sp], #-256	; 0xffffff00
d001bc6c:	5500fb02 	strpl	pc, [r0, #-2818]	; 0xfffff4fe
d001bc70:	35baf505 	ldrcc	pc, [sl, #1285]!	; 0x505
d001bc74:	03a4f105 			; <UNDEFINED> instruction: 0x03a4f105
d001bc78:	f0034618 			; <UNDEFINED> instruction: 0xf0034618
d001bc7c:	f10dfbb3 			; <UNDEFINED> instruction: 0xf10dfbb3
d001bc80:	46840e50 	pkhtbmi	r0, r4, r0, asr #28
d001bc84:	40c4f8c5 	sbcmi	pc, r4, r5, asr #17
d001bc88:	70c8f8c5 	sbcvc	pc, r8, r5, asr #17
d001bc8c:	b0ccf885 	sbclt	pc, ip, r5, lsl #17
d001bc90:	a0cff885 	sbcge	pc, pc, r5, lsl #17
d001bc94:	80d0f885 	sbcshi	pc, r0, r5, lsl #17
d001bc98:	60d4f8a5 	sbcsvs	pc, r4, r5, lsr #17
d001bc9c:	90d8f8c5 	sbcsls	pc, r8, r5, asr #17
d001bca0:	000fe8be 			; <UNDEFINED> instruction: 0x000fe8be
d001bca4:	000fe8ac 	andeq	lr, pc, ip, lsr #17
d001bca8:	000fe89e 	muleq	pc, lr, r8	; <UNPREDICTABLE>
d001bcac:	000fe88c 	andeq	lr, pc, ip, lsl #17
d001bcb0:	f8859b02 			; <UNDEFINED> instruction: 0xf8859b02
d001bcb4:	9b0430cd 	blls	0xd0127ff0
d001bcb8:	30d2f8a5 	sbcscc	pc, r2, r5, lsr #17
d001bcbc:	f507e610 			; <UNDEFINED> instruction: 0xf507e610
d001bcc0:	f8d232f8 			; <UNDEFINED> instruction: 0xf8d232f8
d001bcc4:	370370f8 			; <UNDEFINED> instruction: 0x370370f8
d001bcc8:	0703f027 	streq	pc, [r3, -r7, lsr #32]
d001bccc:	e7621d39 			; <UNDEFINED> instruction: 0xe7621d39
d001bcd0:	0f07f1bb 	svceq	0x0007f1bb
d001bcd4:	f04fbf18 			; <UNDEFINED> instruction: 0xf04fbf18
d001bcd8:	e7c30900 	strb	r0, [r3, r0, lsl #18]
d001bcdc:	00007b92 	muleq	r0, r2, fp
d001bce0:	00007b52 	andeq	r7, r0, r2, asr fp
d001bce4:	fffffe1e 			; <UNDEFINED> instruction: 0xfffffe1e
d001bce8:	00007b02 	andeq	r7, r0, r2, lsl #22
d001bcec:	fffffdc4 			; <UNDEFINED> instruction: 0xfffffdc4
d001bcf0:	fffffdc3 			; <UNDEFINED> instruction: 0xfffffdc3
d001bcf4:	fffffdd5 			; <UNDEFINED> instruction: 0xfffffdd5
d001bcf8:	00007a8e 	andeq	r7, r0, lr, lsl #21
d001bcfc:	00007a72 	andeq	r7, r0, r2, ror sl
d001bd00:	fffffdda 			; <UNDEFINED> instruction: 0xfffffdda
d001bd04:	fffffde9 			; <UNDEFINED> instruction: 0xfffffde9
d001bd08:	00007a3e 	andeq	r7, r0, lr, lsr sl
d001bd0c:	00007a14 	andeq	r7, r0, r4, lsl sl
d001bd10:	fffffdcc 			; <UNDEFINED> instruction: 0xfffffdcc
d001bd14:	000079fe 	strdeq	r7, [r0], -lr
d001bd18:	fffffdd6 			; <UNDEFINED> instruction: 0xfffffdd6
d001bd1c:	000079d2 	ldrdeq	r7, [r0], -r2
d001bd20:	00007956 	andeq	r7, r0, r6, asr r9
d001bd24:	000078d0 	ldrdeq	r7, [r0], -r0
d001bd28:	fffffd01 			; <UNDEFINED> instruction: 0xfffffd01
d001bd2c:	00007894 	muleq	r0, r4, r8
d001bd30:	fffffc57 			; <UNDEFINED> instruction: 0xfffffc57
d001bd34:	ffffdcfc 			; <UNDEFINED> instruction: 0xffffdcfc
d001bd38:	0000782e 	andeq	r7, r0, lr, lsr #16
d001bd3c:	00007802 	andeq	r7, r0, r2, lsl #16
d001bd40:	000077e8 	andeq	r7, r0, r8, ror #15
d001bd44:	000077b2 			; <UNDEFINED> instruction: 0x000077b2

Disassembly of section .text.sidc_compile_project.part.0:

d001c510 <.text.sidc_compile_project.part.0>:
d001c510:	4ff0e92d 	svcmi	0x00f0e92d
d001c514:	8b02ed2d 	blhi	0xd00d79d0
d001c518:	931db0e5 	tstls	sp, #229	; 0xe5
d001c51c:	90172300 	andsls	r2, r7, r0, lsl #6
d001c520:	921a3004 	andsls	r3, sl, #4
d001c524:	9119461a 	tstls	r9, sl, lsl r6
d001c528:	428b991a 	addmi	r9, fp, #425984	; 0x68000
d001c52c:	80a7f040 	adchi	pc, r7, r0, asr #32
d001c530:	21004ca7 	smlatbcs	r0, r7, ip, r4
d001c534:	447c4aa5 	ldrbtmi	r4, [ip], #-2725	; 0xfffff55b
d001c538:	f0024620 			; <UNDEFINED> instruction: 0xf0024620
d001c53c:	9b70ff53 	blls	0xd1c5c290
d001c540:	22bc48a4 	adcscs	r4, ip, #164, 16	; 0xa40000
d001c544:	9b1d66e3 	blls	0xd07760d8
d001c548:	49a34478 	stmibmi	r3!, {r3, r4, r5, r6, sl, lr}
d001c54c:	f04f6723 			; <UNDEFINED> instruction: 0xf04f6723
d001c550:	447933ff 	ldrbtmi	r3, [r9], #-1023	; 0xfffffc01
d001c554:	67a33040 	strvs	r3, [r3, r0, asr #32]!
d001c558:	ff52f002 			; <UNDEFINED> instruction: 0xff52f002
d001c55c:	4398f24f 	orrsmi	pc, r8, #-268435452	; 0xf0000004
d001c560:	50e222bc 	strhtpl	r2, [r2], #44	; 0x2c
d001c564:	93152300 	tstls	r5, #0, 6
d001c568:	447b4b9c 	ldrbtmi	r4, [fp], #-2972	; 0xfffff464
d001c56c:	3a10ee08 	bcc	0xd0457d94
d001c570:	4374f503 	cmnmi	r4, #12582912	; 0xc00000	; <UNPREDICTABLE>
d001c574:	931b3398 	tstls	fp, #152, 6	; 0x60000002
d001c578:	9a1a4c99 	bls	0xd06af7e4
d001c57c:	447c9915 	ldrbtmi	r9, [ip], #-2325	; 0xfffff6eb
d001c580:	6da3428a 	sfmvs	f4, 4, [r3, #552]!	; 0x228
d001c584:	833cf001 	teqhi	ip, #1	; <UNPREDICTABLE>
d001c588:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d001c58c:	4895809b 	ldmmi	r5, {r0, r1, r3, r4, r7, pc}
d001c590:	f5004478 			; <UNDEFINED> instruction: 0xf5004478
d001c594:	f893332d 			; <UNDEFINED> instruction: 0xf893332d
d001c598:	2d00517e 	stfcss	f5, [r0, #-504]	; 0xfffffe08
d001c59c:	8367f001 	msrhi	SPSR_sxc, #1
d001c5a0:	2c006d84 	stccs	13, cr6, [r0], {132}	; 0x84
d001c5a4:	8362f041 	msrhi	SPSR_x, #65	; 0x41
d001c5a8:	4398f24f 	orrsmi	pc, r8, #-268435452	; 0xf0000004
d001c5ac:	58c74d8e 	stmiapl	r7, {r1, r2, r3, r7, r8, sl, fp, lr}^
d001c5b0:	7869447d 	stmdavc	r9!, {r0, r2, r3, r4, r5, r6, sl, lr}^
d001c5b4:	f8153402 			; <UNDEFINED> instruction: 0xf8153402
d001c5b8:	ea433b02 	b	0xd10eb1c8
d001c5bc:	f7f82101 			; <UNDEFINED> instruction: 0xf7f82101
d001c5c0:	2ccefb2f 	fstmiaxcs	lr, {d31-d53}	;@ Deprecated
d001c5c4:	f24fd1f5 	vand	<illegal reg q14.5>, <illegal reg q15.5>, <illegal reg q10.5>
d001c5c8:	4e884398 	mcrmi	3, 4, r4, cr8, cr8, {4}
d001c5cc:	58c52400 	stmiapl	r5, {sl, sp}^
d001c5d0:	7871447e 	ldmdavc	r1!, {r1, r2, r3, r4, r5, r6, sl, lr}^
d001c5d4:	f8163402 			; <UNDEFINED> instruction: 0xf8163402
d001c5d8:	ea433b02 	b	0xd10eb1e8
d001c5dc:	f7f82101 			; <UNDEFINED> instruction: 0xf7f82101
d001c5e0:	2cf2fb1f 	fldmiaxcs	r2!, {d31-d45}	;@ Deprecated
d001c5e4:	4c82d1f5 	stfmid	f5, [r2], {245}	; 0xf5
d001c5e8:	0a00f04f 	beq	0xd005872c
d001c5ec:	9204f8df 	andls	pc, r4, #14614528	; 0xdf0000
d001c5f0:	44f9447c 	ldrbtmi	r4, [r9], #1148	; 0x47c
d001c5f4:	360ef504 	strcc	pc, [lr], -r4, lsl #10
d001c5f8:	381ef504 	ldmdacc	lr, {r2, r8, sl, ip, sp, lr, pc}
d001c5fc:	7684f506 	strvc	pc, [r4], r6, lsl #10
d001c600:	3108f8d8 	ldrdcc	pc, [r8, -r8]
d001c604:	d203459a 	andle	r4, r3, #645922816	; 0x26800000
d001c608:	2b006da3 	blcs	0xd0037c9c
d001c60c:	8332f001 	teqhi	r2, #1	; <UNPREDICTABLE>
d001c610:	f24f4b79 	vpadd.i8	q10, <illegal reg q7.5>, <illegal reg q12.5>
d001c614:	447b4298 	ldrbtmi	r4, [fp], #-664	; 0xfffffd68
d001c618:	f24f5899 	vtst.8	d21, d31, d9
d001c61c:	589a429c 	ldmpl	sl, {r2, r3, r4, r7, r9, lr}
d001c620:	33f8f503 	mvnscc	pc, #12582912	; 0xc00000
d001c624:	0a02eb01 	beq	0xd00d7230
d001c628:	60f8f8d3 	ldrsbtvs	pc, [r8], #131	; 0x83	; <UNPREDICTABLE>
d001c62c:	0703f10a 	streq	pc, [r3, -sl, lsl #2]
d001c630:	0703f027 	streq	pc, [r3, -r7, lsr #32]
d001c634:	f0012e00 			; <UNDEFINED> instruction: 0xf0012e00
d001c638:	443e834d 	ldrtmi	r8, [lr], #-845	; 0xfffffcb3
d001c63c:	031ff106 	tsteq	pc, #-2147483647	; 0x80000001	; <UNPREDICTABLE>
d001c640:	3f80f5b6 	svccc	0x0080f5b6
d001c644:	031ff023 	tsteq	pc, #35	; 0x23	; <UNPREDICTABLE>
d001c648:	d9059310 	stmdble	r5, {r4, r8, r9, ip, pc}
d001c64c:	486c496b 	stmdami	ip!, {r0, r1, r3, r5, r6, r8, fp, lr}^
d001c650:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d001c654:	fda8f7f3 	stc2	7, cr15, [r8, #972]!	; 0x3cc
d001c658:	f04f4c6a 			; <UNDEFINED> instruction: 0xf04f4c6a
d001c65c:	4b6a0900 	blmi	0xd1a9ea64
d001c660:	f8cd447c 			; <UNDEFINED> instruction: 0xf8cd447c
d001c664:	447b903c 	ldrbtmi	r9, [fp], #-60	; 0xffffffc4
d001c668:	389af504 	ldmcc	sl, {r2, r8, sl, ip, sp, lr, pc}
d001c66c:	4b74f504 	blmi	0xd1d59a84
d001c670:	f1089311 			; <UNDEFINED> instruction: 0xf1089311
d001c674:	f10b08a0 			; <UNDEFINED> instruction: 0xf10b08a0
d001c678:	f0010b98 			; <UNDEFINED> instruction: 0xf0010b98
d001c67c:	9917bb57 	ldmdbls	r7, {r0, r1, r2, r4, r6, r8, r9, fp, ip, sp, pc}
d001c680:	1033f851 	eorsne	pc, r3, r1, asr r8	; <UNPREDICTABLE>
d001c684:	f850b129 			; <UNDEFINED> instruction: 0xf850b129
d001c688:	f5c21033 			; <UNDEFINED> instruction: 0xf5c21033
d001c68c:	42a13400 	adcmi	r3, r1, #0, 8
d001c690:	9a1ad915 	bls	0xd06d2aec
d001c694:	d00f2a01 	andle	r2, pc, r1, lsl #20
d001c698:	447a4a5c 	ldrbtmi	r4, [sl], #-2652	; 0xfffff5a4
d001c69c:	24009972 	strcs	r9, [r0], #-2418	; 0xfffff68e
d001c6a0:	2201600a 	andcs	r6, r1, #10
d001c6a4:	604a60cb 	subvs	r6, sl, fp, asr #1
d001c6a8:	610c608a 	smlabbvs	ip, sl, r0, r6
d001c6ac:	b0654620 	rsblt	r4, r5, r0, lsr #12
d001c6b0:	8b02ecbd 	blhi	0xd00d79ac
d001c6b4:	8ff0e8bd 	svchi	0x00f0e8bd
d001c6b8:	447a4a55 	ldrbtmi	r4, [sl], #-2645	; 0xfffff5ab
d001c6bc:	440ae7ee 	strmi	lr, [sl], #-2030	; 0xfffff812
d001c6c0:	e7313301 	ldr	r3, [r1, -r1, lsl #6]!
d001c6c4:	9a159b15 	bls	0xd0583320
d001c6c8:	9b177223 	blls	0xd05f8f5c
d001c6cc:	3032f853 	eorscc	pc, r2, r3, asr r8	; <UNPREDICTABLE>
d001c6d0:	9b196023 	blls	0xd0674764
d001c6d4:	f853b383 			; <UNDEFINED> instruction: 0xf853b383
d001c6d8:	4d4e3022 	stclmi	0, cr3, [lr, #-136]	; 0xffffff78
d001c6dc:	447d9915 	ldrbtmi	r9, [sp], #-2325	; 0xfffff6eb
d001c6e0:	676b4c4d 	strbvs	r4, [fp, -sp, asr #24]!
d001c6e4:	33fff04f 	mvnscc	pc, #79	; 0x4f
d001c6e8:	4250f505 	subsmi	pc, r0, #20971520	; 0x1400000
d001c6ec:	4650f505 	ldrbmi	pc, [r0], -r5, lsl #10	; <UNPREDICTABLE>
d001c6f0:	230067ab 	movwcs	r6, #1963	; 0x7ab
d001c6f4:	361c4628 	ldrcc	r4, [ip], -r8, lsr #12
d001c6f8:	f50560d3 			; <UNDEFINED> instruction: 0xf50560d3
d001c6fc:	f8c5424f 			; <UNDEFINED> instruction: 0xf8c5424f
d001c700:	447c31fc 	ldrbtmi	r3, [ip], #-508	; 0xfffffe04
d001c704:	3088f8c2 	addcc	pc, r8, r2, asr #17
d001c708:	32049a17 	andcc	r9, r4, #94208	; 0x17000
d001c70c:	2031f852 	eorscs	pc, r1, r2, asr r8	; <UNPREDICTABLE>
d001c710:	230160eb 	movwcs	r6, #4331	; 0x10eb
d001c714:	e9c5606a 	stmib	r5, {r1, r3, r5, r6, sp, lr}^
d001c718:	f7f63304 			; <UNDEFINED> instruction: 0xf7f63304
d001c71c:	4628fb6b 	strtmi	pc, [r8], -fp, ror #22
d001c720:	fb68f7f6 	blx	0xd1a5a702
d001c724:	6dab6aea 			; <UNDEFINED> instruction: 0x6dab6aea
d001c728:	7f83f5b2 	svcvc	0x0083f5b2
d001c72c:	b12bd111 			; <UNDEFINED> instruction: 0xb12bd111
d001c730:	33019b15 	movwcc	r9, #6933	; 0x1b15
d001c734:	e71f9315 			; <UNDEFINED> instruction: 0xe71f9315
d001c738:	e7ce9b19 	bfi	r9, r9, (invalid: 22:14)
d001c73c:	b11b6833 	tstlt	fp, r3, lsr r8
d001c740:	f7f64620 			; <UNDEFINED> instruction: 0xf7f64620
d001c744:	e7edfb57 	ubfx	pc, r7, #22, #14
d001c748:	f7f8981d 			; <UNDEFINED> instruction: 0xf7f8981d
d001c74c:	2800f8f5 	stmdacs	r0, {r0, r2, r4, r5, r6, r7, fp, ip, sp, lr, pc}
d001c750:	4c32d1f6 	ldfmid	f5, [r2], #-984	; 0xfffffc28
d001c754:	6da6447c 	cfstrsvs	mvf4, [r6, #496]!	; 0x1f0
d001c758:	d1e92e00 	mvnle	r2, r0, lsl #28
d001c75c:	f5b36ae3 			; <UNDEFINED> instruction: 0xf5b36ae3
d001c760:	d0e57f80 	rscle	r7, r5, r0, lsl #31
d001c764:	1119f240 	tstne	r9, r0, asr #4	; <UNPREDICTABLE>
d001c768:	f7f64620 			; <UNDEFINED> instruction: 0xf7f64620
d001c76c:	4607fb5e 			; <UNDEFINED> instruction: 0x4607fb5e
d001c770:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d001c774:	f104819c 			; <UNDEFINED> instruction: 0xf104819c
d001c778:	ad2c0718 	stcge	7, cr0, [ip, #-96]!	; 0xffffffa0
d001c77c:	802cf8d4 	ldrdhi	pc, [ip], -r4	; <UNPREDICTABLE>
d001c780:	9030f894 	mlasls	r0, r4, r8, pc	; <UNPREDICTABLE>
d001c784:	c50fcf0f 	strgt	ip, [pc, #-3855]	; 0xd001b87d
d001c788:	000fe897 	muleq	pc, r7, r8	; <UNPREDICTABLE>
d001c78c:	000fe885 	andeq	lr, pc, r5, lsl #17
d001c790:	f2406a63 	vpmax.s8	q11, q0, <illegal reg q9.5>
d001c794:	46201107 	strtmi	r1, [r0], -r7, lsl #2
d001c798:	6aa3930f 	bvs	0xce9013dc
d001c79c:	6b639310 	blvs	0xd19013e4
d001c7a0:	ba06e9d4 	blt	0xd01d6ef8
d001c7a4:	f7f69311 			; <UNDEFINED> instruction: 0xf7f69311
d001c7a8:	4607fb40 	strmi	pc, [r7], -r0, asr #22
d001c7ac:	f0402800 			; <UNDEFINED> instruction: 0xf0402800
d001c7b0:	6ae68126 	bvs	0xcf9bcc50
d001c7b4:	131bf240 	tstne	fp, #64, 4	; <UNPREDICTABLE>
d001c7b8:	d131429e 	teqle	r1, lr	; <illegal shifter operand>
d001c7bc:	f7f64620 			; <UNDEFINED> instruction: 0xf7f64620
d001c7c0:	2800fe35 	stmdacs	r0, {r0, r2, r4, r5, r9, sl, fp, ip, sp, lr, pc}
d001c7c4:	463ed0c5 	ldrtmi	sp, [lr], -r5, asr #1
d001c7c8:	bf00e073 	svclt	0x0000e073
d001c7cc:	0002b580 	andeq	fp, r2, r0, lsl #11
d001c7d0:	00006ee6 	andeq	r6, r0, r6, ror #29
d001c7d4:	00032454 	andeq	r2, r3, r4, asr r4
d001c7d8:	00001dac 	andeq	r1, r0, ip, lsr #27
d001c7dc:	00006eb2 			; <UNDEFINED> instruction: 0x00006eb2
d001c7e0:	00006e9e 	muleq	r0, lr, lr
d001c7e4:	00006e8c 	andeq	r6, r0, ip, lsl #29
d001c7e8:	00001b8e 	andeq	r1, r0, lr, lsl #23
d001c7ec:	00001c3c 	andeq	r1, r0, ip, lsr ip
d001c7f0:	00006e2c 	andeq	r6, r0, ip, lsr #28
d001c7f4:	fffffead 			; <UNDEFINED> instruction: 0xfffffead
d001c7f8:	00006e06 	andeq	r6, r0, r6, lsl #28
d001c7fc:	fffffe71 			; <UNDEFINED> instruction: 0xfffffe71
d001c800:	00006dca 	andeq	r6, r0, sl, asr #27
d001c804:	00006dbc 			; <UNDEFINED> instruction: 0x00006dbc
d001c808:	00006db6 			; <UNDEFINED> instruction: 0x00006db6
d001c80c:	fffff6c1 			; <UNDEFINED> instruction: 0xfffff6c1
d001c810:	fffff68a 			; <UNDEFINED> instruction: 0xfffff68a
d001c814:	00006d3e 	andeq	r6, r0, lr, lsr sp
d001c818:	00006d1a 	andeq	r6, r0, sl, lsl sp
d001c81c:	00006cc8 	andeq	r6, r0, r8, asr #25
d001c820:	758bf46f 	strvc	pc, [fp, #1135]	; 0x46f
d001c824:	2b011973 	blcs	0xd0062df8
d001c828:	f5a6d84c 			; <UNDEFINED> instruction: 0xf5a6d84c
d001c82c:	ad2c708c 	stcge	0, cr7, [ip, #-560]!	; 0xfffffdd0
d001c830:	41464246 	cmpmi	r6, r6, asr #4
d001c834:	f7f64620 			; <UNDEFINED> instruction: 0xf7f64620
d001c838:	f104fadd 			; <UNDEFINED> instruction: 0xf104fadd
d001c83c:	f8d40c18 			; <UNDEFINED> instruction: 0xf8d40c18
d001c840:	f894802c 			; <UNDEFINED> instruction: 0xf894802c
d001c844:	e8bc9030 	ldm	ip!, {r4, r5, ip, pc}
d001c848:	c50f000f 	strgt	r0, [pc, #-15]	; 0xd001c841
d001c84c:	000fe89c 	muleq	pc, ip, r8	; <UNPREDICTABLE>
d001c850:	000fe885 	andeq	lr, pc, r5, lsl #17
d001c854:	930f6a63 	movwls	r6, #64099	; 0xfa63
d001c858:	93106aa3 	tstls	r0, #667648	; 0xa3000
d001c85c:	93116b63 	tstls	r1, #101376	; 0x18c00
d001c860:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d001c864:	e9d44598 	ldmib	r4, {r3, r4, r7, r8, sl, lr}^
d001c868:	d102ba06 	tstle	r2, r6, lsl #20
d001c86c:	f7f64620 			; <UNDEFINED> instruction: 0xf7f64620
d001c870:	f8dffac1 			; <UNDEFINED> instruction: 0xf8dffac1
d001c874:	447c4c20 	ldrbtmi	r4, [ip], #-3104	; 0xfffff3e0
d001c878:	2b7b6ae3 	blcs	0xd1ef740c
d001c87c:	80c1f000 	sbchi	pc, r1, r0
d001c880:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d001c884:	d1164598 			; <UNDEFINED> instruction: 0xd1164598
d001c888:	46524633 			; <UNDEFINED> instruction: 0x46524633
d001c88c:	46204659 			; <UNDEFINED> instruction: 0x46204659
d001c890:	fed2f7f3 	mrc2	7, 6, pc, cr2, cr3, {7}
d001c894:	da331e05 	ble	0xd0ce40b0
d001c898:	b9536da3 	ldmdblt	r3, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d001c89c:	3bf8f8df 	blcc	0xcfe5ac20
d001c8a0:	65a3447b 	strvs	r4, [r3, #1147]!	; 0x47b
d001c8a4:	65e39b0f 	strbvs	r9, [r3, #2831]!	; 0xb0f
d001c8a8:	e9c49b10 	stmib	r4, {r4, r8, r9, fp, ip, pc}^
d001c8ac:	9b113918 	blls	0xd046ad14
d001c8b0:	25ff66a3 	ldrbcs	r6, [pc, #1699]!	; 0xd001cf5b
d001c8b4:	f8dfe024 			; <UNDEFINED> instruction: 0xf8dfe024
d001c8b8:	46201be4 	strtmi	r1, [r0], -r4, ror #23
d001c8bc:	f7f34479 			; <UNDEFINED> instruction: 0xf7f34479
d001c8c0:	e7f6fc73 			; <UNDEFINED> instruction: 0xe7f6fc73
d001c8c4:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d001c8c8:	f040429e 			; <UNDEFINED> instruction: 0xf040429e
d001c8cc:	46208094 			; <UNDEFINED> instruction: 0x46208094
d001c8d0:	1206e9d4 	andne	lr, r6, #212, 18	; 0x350000
d001c8d4:	ff59f7f3 			; <UNDEFINED> instruction: 0xff59f7f3
d001c8d8:	da062800 	ble	0xd01a68e0
d001c8dc:	1bc0f8df 	blne	0xcf05ac60
d001c8e0:	46204479 			; <UNDEFINED> instruction: 0x46204479
d001c8e4:	fc60f7f3 	stc2l	7, cr15, [r0], #-972	; 0xfffffc34
d001c8e8:	2324e76d 			; <UNDEFINED> instruction: 0x2324e76d
d001c8ec:	fb03463e 	blx	0xd00ee1ee
d001c8f0:	f5004000 			; <UNDEFINED> instruction: 0xf5004000
d001c8f4:	f89030e5 			; <UNDEFINED> instruction: 0xf89030e5
d001c8f8:	4620508c 	strtmi	r5, [r0], -ip, lsl #1
d001c8fc:	fa7af7f6 	blx	0xd1eda8dc
d001c900:	4ba0f8df 	blmi	0xce85ac84
d001c904:	6da3447c 	cfstrsvs	mvf4, [r3, #496]!	; 0x1f0
d001c908:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001c90c:	b34faf22 	movtlt	sl, #65314	; 0xff22
d001c910:	af2c9b0f 	svcge	0x002c9b0f
d001c914:	90c8f88d 	sbcls	pc, r8, sp, lsl #17
d001c918:	932fad06 			; <UNDEFINED> instruction: 0x932fad06
d001c91c:	e9cd9b10 	stmib	sp, {r4, r8, r9, fp, ip, pc}^
d001c920:	9b113830 	blls	0xd046a9e8
d001c924:	ba2ce9cd 	blt	0xd0b57060
d001c928:	cf0f9333 	svcgt	0x000f9333
d001c92c:	e897c50f 	ldm	r7, {r0, r1, r2, r3, r8, sl, lr, pc}
d001c930:	e885000f 	stm	r5, {r0, r1, r2, r3}
d001c934:	f240000f 	vhadd.s8	d16, d0, d15
d001c938:	96041301 	strls	r1, [r4], -r1, lsl #6
d001c93c:	0303ebb8 	movweq	lr, #15288	; 0x3bb8
d001c940:	2301bf18 	movwcs	fp, #7960	; 0x1f18
d001c944:	ab309305 	blge	0xd0c41560
d001c948:	e88dcb0f 	stm	sp, {r0, r1, r2, r3, r8, r9, fp, lr, pc}
d001c94c:	ab2c000f 	blge	0xd0b1c990
d001c950:	f7f7cb0f 			; <UNDEFINED> instruction: 0xf7f7cb0f
d001c954:	1e05fce5 	cdpne	12, 0, cr15, cr5, cr5, {7}
d001c958:	aefbf6ff 	mrcge	6, 7, APSR_nzcv, cr11, cr15, {7}
d001c95c:	2b006da3 	blcs	0xd0037ff0
d001c960:	aef7f47f 	mrcge	4, 7, APSR_nzcv, cr7, cr15, {3}
d001c964:	4b40f8df 	blmi	0xd105ace8
d001c968:	447cae34 	ldrbtmi	sl, [ip], #-3636	; 0xfffff1cc
d001c96c:	0718f104 	ldreq	pc, [r8, -r4, lsl #2]
d001c970:	c60fcf0f 	strgt	ip, [pc], -pc, lsl #30
d001c974:	000fe897 	muleq	pc, r7, r8	; <UNPREDICTABLE>
d001c978:	000fe886 	andeq	lr, pc, r6, lsl #17
d001c97c:	2b2cf8df 	blcs	0xd0b5ad00
d001c980:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d001c984:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d001c988:	fa5df7f6 	blx	0xd179a968
d001c98c:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001c990:	f8dfaee0 			; <UNDEFINED> instruction: 0xf8dfaee0
d001c994:	213b2b1c 	teqcs	fp, ip, lsl fp
d001c998:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d001c99c:	fa53f7f6 	blx	0xd151a97c
d001c9a0:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001c9a4:	af34aed6 	svcge	0x0034aed6
d001c9a8:	f8ddae3c 			; <UNDEFINED> instruction: 0xf8ddae3c
d001c9ac:	f8dd90dc 			; <UNDEFINED> instruction: 0xf8dd90dc
d001c9b0:	cf0f80e0 	svcgt	0x000f80e0
d001c9b4:	ba34e9dd 	blt	0xd0d57130
d001c9b8:	e897c60f 	ldm	r7, {r0, r1, r2, r3, r9, sl, lr, pc}
d001c9bc:	e886000f 	stm	r6, {r0, r1, r2, r3}
d001c9c0:	4652000f 	ldrbmi	r0, [r2], -pc
d001c9c4:	46204659 			; <UNDEFINED> instruction: 0x46204659
d001c9c8:	70e8f89d 	smlalvc	pc, r8, sp, r8	; <UNPREDICTABLE>
d001c9cc:	f7f39e3b 			; <UNDEFINED> instruction: 0xf7f39e3b
d001c9d0:	2800feb8 	stmdacs	r0, {r3, r4, r5, r7, r9, sl, fp, ip, sp, lr, pc}
d001c9d4:	f8dfdb17 			; <UNDEFINED> instruction: 0xf8dfdb17
d001c9d8:	447b3adc 	ldrbtmi	r3, [fp], #-2780	; 0xfffff524
d001c9dc:	2a006d9a 	bcs	0xd003804c
d001c9e0:	aeb7f47f 	mrcge	4, 5, APSR_nzcv, cr7, cr15, {3}
d001c9e4:	2ad0f8df 	bcs	0xcf45ad68
d001c9e8:	447a669e 	ldrbtmi	r6, [sl], #-1694	; 0xfffff962
d001c9ec:	8718e9c3 	ldrhi	lr, [r8, -r3, asr #19]
d001c9f0:	2916e9c3 	ldmdbcs	r6, {r0, r1, r6, r7, r8, fp, sp, lr, pc}
d001c9f4:	f8dfe6ad 			; <UNDEFINED> instruction: 0xf8dfe6ad
d001c9f8:	44791ac4 	ldrbtmi	r1, [r9], #-2756	; 0xfffff53c
d001c9fc:	4637e771 			; <UNDEFINED> instruction: 0x4637e771
d001ca00:	2701e757 	smlsdcs	r1, r7, r7, lr
d001ca04:	4652e755 			; <UNDEFINED> instruction: 0x4652e755
d001ca08:	46204659 			; <UNDEFINED> instruction: 0x46204659
d001ca0c:	ff00f7f3 			; <UNDEFINED> instruction: 0xff00f7f3
d001ca10:	dae02800 	ble	0xcf826a18
d001ca14:	46594652 			; <UNDEFINED> instruction: 0x46594652
d001ca18:	f7f34620 			; <UNDEFINED> instruction: 0xf7f34620
d001ca1c:	2800feb6 	stmdacs	r0, {r1, r2, r4, r5, r7, r9, sl, fp, ip, sp, lr, pc}
d001ca20:	2324db16 			; <UNDEFINED> instruction: 0x2324db16
d001ca24:	4000fb03 	andmi	pc, r0, r3, lsl #22
d001ca28:	30e5f500 	rsccc	pc, r5, r0, lsl #10
d001ca2c:	308cf890 	umullcc	pc, ip, r0, r8	; <UNPREDICTABLE>
d001ca30:	f43f429d 			; <UNDEFINED> instruction: 0xf43f429d
d001ca34:	6da3ae8e 	stcvs	14, cr10, [r3, #568]!	; 0x238
d001ca38:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001ca3c:	f8dfae8a 			; <UNDEFINED> instruction: 0xf8dfae8a
d001ca40:	447b3a80 	ldrbtmi	r3, [fp], #-2688	; 0xfffff580
d001ca44:	3916e9c4 	ldmdbcc	r6, {r2, r6, r7, r8, fp, sp, lr, pc}
d001ca48:	8718e9c4 	ldrhi	lr, [r8, -r4, asr #19]
d001ca4c:	e68066a6 	str	r6, [r0], r6, lsr #13
d001ca50:	32e9f504 	rsccc	pc, r9, #4, 10	; 0x1000000
d001ca54:	316cf8d2 	ldrdcc	pc, [ip, #-130]!	; 0xffffff7e
d001ca58:	d1072b40 	tstle	r7, r0, asr #22
d001ca5c:	2b006da3 	blcs	0xd00380f0
d001ca60:	ae77f47f 	mrcge	4, 3, APSR_nzcv, cr7, cr15, {3}
d001ca64:	3a5cf8df 	bcc	0xd175ade8
d001ca68:	e7eb447b 			; <UNDEFINED> instruction: 0xe7eb447b
d001ca6c:	f8941c59 			; <UNDEFINED> instruction: 0xf8941c59
d001ca70:	f88dc008 			; <UNDEFINED> instruction: 0xf88dc008
d001ca74:	af3c7108 	svcge	0x003c7108
d001ca78:	116cf8c2 	msrne	SPSR_fs, r2, asr #17
d001ca7c:	96432224 	strbls	r2, [r3], -r4, lsr #4
d001ca80:	4403fb02 	strmi	pc, [r3], #-2818	; 0xfffff4fe
d001ca84:	8100f8cd 	smlabthi	r0, sp, r8, pc	; <UNPREDICTABLE>
d001ca88:	34e5f504 	strbtcc	pc, [r5], #1284	; 0x504	; <UNPREDICTABLE>
d001ca8c:	90fcf8cd 	rscsls	pc, ip, sp, asr #17
d001ca90:	066cf104 	strbteq	pc, [ip], -r4, lsl #2	; <UNPREDICTABLE>
d001ca94:	508cf884 	addpl	pc, ip, r4, lsl #17
d001ca98:	c08df884 	addgt	pc, sp, r4, lsl #17
d001ca9c:	ba3ce9cd 	blt	0xd0f571d8
d001caa0:	c60fcf0f 	strgt	ip, [pc], -pc, lsl #30
d001caa4:	000fe897 	muleq	pc, r7, r8	; <UNPREDICTABLE>
d001caa8:	000fe886 	andeq	lr, pc, r6, lsl #17
d001caac:	6ae5e651 	bvs	0xcf9963f8
d001cab0:	718bf46f 	orrvc	pc, fp, pc, ror #8
d001cab4:	2b01186b 	blcs	0xd0062c68
d001cab8:	f8d4d85d 			; <UNDEFINED> instruction: 0xf8d4d85d
d001cabc:	f240a04c 	vhadd.s8	q13, q0, q6
d001cac0:	459a1301 	ldrmi	r1, [sl, #769]	; 0x301
d001cac4:	4620d157 			; <UNDEFINED> instruction: 0x4620d157
d001cac8:	f7f6ae3c 			; <UNDEFINED> instruction: 0xf7f6ae3c
d001cacc:	f104f993 			; <UNDEFINED> instruction: 0xf104f993
d001cad0:	f8d40c18 			; <UNDEFINED> instruction: 0xf8d40c18
d001cad4:	f8d4b024 			; <UNDEFINED> instruction: 0xf8d4b024
d001cad8:	f8949028 			; <UNDEFINED> instruction: 0xf8949028
d001cadc:	e8bc8030 	ldm	ip!, {r4, r5, pc}
d001cae0:	c60f000f 	strgt	r0, [pc], -pc
d001cae4:	000fe89c 	muleq	pc, ip, r8	; <UNPREDICTABLE>
d001cae8:	000fe886 	andeq	lr, pc, r6, lsl #17
d001caec:	29d8f8df 	ldmibcs	r8, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d001caf0:	46204651 			; <UNDEFINED> instruction: 0x46204651
d001caf4:	447a6b66 	ldrbtmi	r6, [sl], #-2918	; 0xfffff49a
d001caf8:	f9a5f7f6 			; <UNDEFINED> instruction: 0xf9a5f7f6
d001cafc:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001cb00:	6ae3ae28 	bvs	0xcf9083a8
d001cb04:	d12a2b7b 			; <UNDEFINED> instruction: 0xd12a2b7b
d001cb08:	0cf0f10d 	ldfeqp	f7, [r0], #52	; 0x34
d001cb0c:	f8cd9643 			; <UNDEFINED> instruction: 0xf8cd9643
d001cb10:	ae069100 	mvfges	f1, f0
d001cb14:	8108f88d 	smlabbhi	r8, sp, r8, pc	; <UNPREDICTABLE>
d001cb18:	b0fcf8cd 	rscslt	pc, ip, sp, asr #17
d001cb1c:	000fe8bc 			; <UNDEFINED> instruction: 0x000fe8bc
d001cb20:	e89cc60f 	ldm	ip, {r0, r1, r2, r3, r9, sl, lr, pc}
d001cb24:	e886000f 	stm	r6, {r0, r1, r2, r3}
d001cb28:	f5a5000f 			; <UNDEFINED> instruction: 0xf5a5000f
d001cb2c:	ab40728c 	blge	0xd1039564
d001cb30:	42559705 	subsmi	r9, r5, #1310720	; 0x140000
d001cb34:	95044155 	strls	r4, [r4, #-341]	; 0xfffffeab
d001cb38:	e88dcb0f 	stm	sp, {r0, r1, r2, r3, r8, r9, fp, lr, pc}
d001cb3c:	ab3c000f 	blge	0xd0f1cb80
d001cb40:	f7f7cb0f 			; <UNDEFINED> instruction: 0xf7f7cb0f
d001cb44:	6da3fbed 			; <UNDEFINED> instruction: 0x6da3fbed
d001cb48:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001cb4c:	f8dfae02 			; <UNDEFINED> instruction: 0xf8dfae02
d001cb50:	213b297c 	teqcs	fp, ip, ror r9
d001cb54:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d001cb58:	f975f7f6 			; <UNDEFINED> instruction: 0xf975f7f6
d001cb5c:	6da3e5f9 	cfstr32vs	mvfx14, [r3, #996]!	; 0x3e4
d001cb60:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001cb64:	f8dfadf6 			; <UNDEFINED> instruction: 0xf8dfadf6
d001cb68:	447b3968 	ldrbtmi	r3, [fp], #-2408	; 0xfffff698
d001cb6c:	9818e9c4 	ldmdals	r8, {r2, r6, r7, r8, fp, sp, lr, pc}
d001cb70:	3b16e9c4 	blcc	0xd05d7288
d001cb74:	f8dfe76a 			; <UNDEFINED> instruction: 0xf8dfe76a
d001cb78:	f44f595c 	vst2.16	{d21,d23}, [pc :64], ip
d001cb7c:	447d7183 	ldrbtmi	r7, [sp], #-387	; 0xfffffe7d
d001cb80:	f7f64628 			; <UNDEFINED> instruction: 0xf7f64628
d001cb84:	b150f952 	cmplt	r0, r2, asr r9	; <UNPREDICTABLE>
d001cb88:	4350f505 	cmpmi	r0, #20971520	; 0x1400000	; <UNPREDICTABLE>
d001cb8c:	681b331c 	ldmdavs	fp, {r2, r3, r4, r8, r9, ip, sp}
d001cb90:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001cb94:	6f28adde 	svcvs	0x0028adde
d001cb98:	fecef7f7 	mcr2	7, 6, pc, cr14, cr7, {7}	; <UNPREDICTABLE>
d001cb9c:	f44fe5d9 	vst3.<illegal width 64>	{d30,d32,d34}, [pc :64], r9
d001cba0:	46287188 	strtmi	r7, [r8], -r8, lsl #3
d001cba4:	f941f7f6 			; <UNDEFINED> instruction: 0xf941f7f6
d001cba8:	7185f44f 	orrvc	pc, r5, pc, asr #8
d001cbac:	46289013 			; <UNDEFINED> instruction: 0x46289013
d001cbb0:	f93bf7f6 			; <UNDEFINED> instruction: 0xf93bf7f6
d001cbb4:	f2406aea 	vpmax.s8	q11, q8, q13
d001cbb8:	4604131b 			; <UNDEFINED> instruction: 0x4604131b
d001cbbc:	429a4628 	addsmi	r4, sl, #40, 12	; 0x2800000
d001cbc0:	f7f6d14c 			; <UNDEFINED> instruction: 0xf7f6d14c
d001cbc4:	2800fc33 	stmdacs	r0, {r0, r1, r4, r5, sl, fp, ip, sp, lr, pc}
d001cbc8:	adc3f43f 	cfstrdge	mvd15, [r3, #252]	; 0xfc
d001cbcc:	4628213b 			; <UNDEFINED> instruction: 0x4628213b
d001cbd0:	f92bf7f6 			; <UNDEFINED> instruction: 0xf92bf7f6
d001cbd4:	28004606 	stmdacs	r0, {r1, r2, r9, sl, lr}
d001cbd8:	adbbf47f 	cfldrsge	mvf15, [fp, #508]!	; 0x1fc
d001cbdc:	0c18f105 	ldfeqd	f7, [r8], {5}
d001cbe0:	f8d5af3c 			; <UNDEFINED> instruction: 0xf8d5af3c
d001cbe4:	f8d5a024 			; <UNDEFINED> instruction: 0xf8d5a024
d001cbe8:	f8959028 			; <UNDEFINED> instruction: 0xf8959028
d001cbec:	e8bc8030 	ldm	ip!, {r4, r5, pc}
d001cbf0:	c70f000f 	strgt	r0, [pc, -pc]
d001cbf4:	000fe89c 	muleq	pc, ip, r8	; <UNPREDICTABLE>
d001cbf8:	000fe887 	andeq	lr, pc, r7, lsl #17
d001cbfc:	28d8f8df 	ldmcs	r8, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d001cc00:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d001cc04:	6b6f4628 	blvs	0xd1bee4ac
d001cc08:	f7f6447a 			; <UNDEFINED> instruction: 0xf7f6447a
d001cc0c:	f10df91c 			; <UNDEFINED> instruction: 0xf10df91c
d001cc10:	28000cf0 	stmdacs	r0, {r4, r5, r6, r7, sl, fp}
d001cc14:	ad9df43f 	cfldrsge	mvf15, [sp, #252]	; 0xfc
d001cc18:	43239b13 			; <UNDEFINED> instruction: 0x43239b13
d001cc1c:	6dabd10c 	stfvsd	f5, [fp, #48]!	; 0x30
d001cc20:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001cc24:	f8dfad96 			; <UNDEFINED> instruction: 0xf8dfad96
d001cc28:	66af38b4 			; <UNDEFINED> instruction: 0x66af38b4
d001cc2c:	e9c5447b 	stmib	r5, {r0, r1, r3, r4, r5, r6, sl, lr}^
d001cc30:	e9c59818 	stmib	r5, {r3, r4, fp, ip, pc}^
d001cc34:	e58c3a16 	str	r3, [ip, #2582]	; 0xa16
d001cc38:	f8cdab40 			; <UNDEFINED> instruction: 0xf8cdab40
d001cc3c:	f88d9100 			; <UNDEFINED> instruction: 0xf88d9100
d001cc40:	97438108 	strbls	r8, [r3, -r8, lsl #2]
d001cc44:	96049405 	strls	r9, [r4], -r5, lsl #8
d001cc48:	a0fcf8cd 	rscsge	pc, ip, sp, asr #17
d001cc4c:	e88dcb0f 	stm	sp, {r0, r1, r2, r3, r8, r9, fp, lr, pc}
d001cc50:	e89c000f 	ldm	ip, {r0, r1, r2, r3}
d001cc54:	f7fe000f 			; <UNDEFINED> instruction: 0xf7fe000f
d001cc58:	e57afe11 	ldrb	pc, [sl, #-3601]!	; 0xfffff1ef	; <UNPREDICTABLE>
d001cc5c:	fdb9f7f3 	ldc2	7, cr15, [r9, #972]!	; 0x3cc
d001cc60:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d001cc64:	b12481d9 	ldrdlt	r8, [r4, -r9]!
d001cc68:	1874f8df 	ldmdane	r4!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d001cc6c:	46284479 			; <UNDEFINED> instruction: 0x46284479
d001cc70:	a934e269 	ldmdbge	r4!, {r0, r3, r5, r6, r9, sp, lr, pc}
d001cc74:	94344628 	ldrtls	r4, [r4], #-1576	; 0xfffff9d8
d001cc78:	fae2f7f6 	blx	0xcf8dac58
d001cc7c:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001cc80:	f105ad68 			; <UNDEFINED> instruction: 0xf105ad68
d001cc84:	212a0718 			; <UNDEFINED> instruction: 0x212a0718
d001cc88:	ae3c4628 	cfmsuba32ge	mvax1, mvax4, mvfx12, mvfx8
d001cc8c:	f8cdf7f6 			; <UNDEFINED> instruction: 0xf8cdf7f6
d001cc90:	f8954604 			; <UNDEFINED> instruction: 0xf8954604
d001cc94:	cf0f8030 	svcgt	0x000f8030
d001cc98:	e897c60f 	ldm	r7, {r0, r1, r2, r3, r9, sl, lr, pc}
d001cc9c:	e886000f 	stm	r6, {r0, r1, r2, r3}
d001cca0:	6a6b000f 	bvs	0xd1adcce4
d001cca4:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d001cca8:	2838f8df 	ldmdacs	r8!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d001ccac:	93114628 	tstls	r1, #40, 12	; 0x2800000
d001ccb0:	447a6aab 	ldrbtmi	r6, [sl], #-2731	; 0xfffff555
d001ccb4:	6b6b9310 	blvs	0xd1b018fc
d001ccb8:	9a06e9d5 	bls	0xd01d7414
d001ccbc:	f7f6930f 			; <UNDEFINED> instruction: 0xf7f6930f
d001ccc0:	2800f8c2 	stmdacs	r0, {r1, r6, r7, fp, ip, sp, lr, pc}
d001ccc4:	ad45f43f 	cfstrdge	mvd15, [r5, #-252]	; 0xffffff04
d001ccc8:	2b286aeb 	blcs	0xd0a3787c
d001cccc:	9b34d14a 	blls	0xd0d511fc
d001ccd0:	ae3c2c00 	cdpge	12, 3, cr2, cr12, cr0, {0}
d001ccd4:	9316ac24 	tstls	r6, #36, 24	; 0x2400
d001ccd8:	2305bf14 	movwcs	fp, #24340	; 0x5f14
d001ccdc:	f88d2304 			; <UNDEFINED> instruction: 0xf88d2304
d001cce0:	46258108 	strtmi	r8, [r5], -r8, lsl #2
d001cce4:	9b119312 	blls	0xd0481934
d001cce8:	9b10933f 	blls	0xd04419ec
d001ccec:	9b0f9340 	blls	0xd04019f4
d001ccf0:	9a3ce9cd 	bls	0xd0f5742c
d001ccf4:	ce0f9343 	cdpgt	3, 0, cr9, cr15, cr3, {2}
d001ccf8:	e896c50f 	ldm	r6, {r0, r1, r2, r3, r8, sl, lr, pc}
d001ccfc:	e885000f 	stm	r5, {r0, r1, r2, r3}
d001cd00:	9b11000f 	blls	0xd045cd44
d001cd04:	f8cdae2c 			; <UNDEFINED> instruction: 0xf8cdae2c
d001cd08:	9327a094 			; <UNDEFINED> instruction: 0x9327a094
d001cd0c:	93289b10 			; <UNDEFINED> instruction: 0x93289b10
d001cd10:	f88d9b0f 			; <UNDEFINED> instruction: 0xf88d9b0f
d001cd14:	932b80a8 			; <UNDEFINED> instruction: 0x932b80a8
d001cd18:	c60fcc0f 	strgt	ip, [pc], -pc, lsl #24
d001cd1c:	000fe895 	muleq	pc, r5, r8	; <UNPREDICTABLE>
d001cd20:	000fe886 	andeq	lr, pc, r6, lsl #17
d001cd24:	47c0f8df 			; <UNDEFINED> instruction: 0x47c0f8df
d001cd28:	f8df2128 			; <UNDEFINED> instruction: 0xf8df2128
d001cd2c:	447c27c0 	ldrbtmi	r2, [ip], #-1984	; 0xfffff840
d001cd30:	4620447a 			; <UNDEFINED> instruction: 0x4620447a
d001cd34:	f887f7f6 			; <UNDEFINED> instruction: 0xf887f7f6
d001cd38:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001cd3c:	4652ad0a 	ldrbmi	sl, [r2], -sl, lsl #26
d001cd40:	46204649 	strtmi	r4, [r0], -r9, asr #12
d001cd44:	fd21f7f3 	stc2	7, cr15, [r1, #-972]!	; 0xfffffc34
d001cd48:	f2c02800 	vmlal.s8	q9, d0, d0
d001cd4c:	f8df8234 			; <UNDEFINED> instruction: 0xf8df8234
d001cd50:	447b37a0 	ldrbtmi	r3, [fp], #-1952	; 0xfffff860
d001cd54:	2a006d9a 	bcs	0xd00383c4
d001cd58:	acfbf47f 	cfldrdge	mvd15, [fp], #508	; 0x1fc
d001cd5c:	2794f8df 			; <UNDEFINED> instruction: 0x2794f8df
d001cd60:	e01c447a 	ands	r4, ip, sl, ror r4
d001cd64:	6dabb17c 	stfvsd	f3, [fp, #496]!	; 0x1f0
d001cd68:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001cd6c:	f8dfacf2 			; <UNDEFINED> instruction: 0xf8dfacf2
d001cd70:	447b3788 	ldrbtmi	r3, [fp], #-1928	; 0xfffff878
d001cd74:	9b1165ab 	blls	0xd0476428
d001cd78:	9b1065eb 	blls	0xd043652c
d001cd7c:	3818e9c5 	ldmdacc	r8, {r0, r2, r6, r7, r8, fp, sp, lr, pc}
d001cd80:	66ab9b0f 	strtvs	r9, [fp], pc, lsl #22
d001cd84:	9b13e4e5 	blls	0xd0516120
d001cd88:	6dabb98b 			; <UNDEFINED> instruction: 0x6dabb98b
d001cd8c:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001cd90:	f8dface0 			; <UNDEFINED> instruction: 0xf8dface0
d001cd94:	f8df3768 			; <UNDEFINED> instruction: 0xf8df3768
d001cd98:	447b2768 	ldrbtmi	r2, [fp], #-1896	; 0xfffff898
d001cd9c:	659a447a 	ldrvs	r4, [sl, #1146]	; 0x47a
d001cda0:	65da9a11 	ldrbvs	r9, [sl, #2577]	; 0xa11
d001cda4:	e9c39a10 	stmib	r3, {r4, r9, fp, ip, pc}^
d001cda8:	9a0f2818 	bls	0xd03e6e10
d001cdac:	4628e041 	strtmi	lr, [r8], -r1, asr #32
d001cdb0:	f7f6215b 			; <UNDEFINED> instruction: 0xf7f6215b
d001cdb4:	9b34f83a 	blls	0xd0d5aea4
d001cdb8:	721af44f 	andsvc	pc, sl, #1325400064	; 0x4f000000
d001cdbc:	fb024607 	blx	0xd00ae5e2
d001cdc0:	f5055503 			; <UNDEFINED> instruction: 0xf5055503
d001cdc4:	f8b535c9 			; <UNDEFINED> instruction: 0xf8b535c9
d001cdc8:	28006108 	stmdacs	r0, {r3, r8, sp, lr}
d001cdcc:	f8dfd079 			; <UNDEFINED> instruction: 0xf8dfd079
d001cdd0:	447d5734 	ldrbtmi	r5, [sp], #-1844	; 0xfffff8cc
d001cdd4:	f5a26aea 			; <UNDEFINED> instruction: 0xf5a26aea
d001cdd8:	2a017281 	bcs	0xd00797e4
d001cddc:	6a2ad80a 	bvs	0xd0ad2e0c
d001cde0:	b13a9212 	teqlt	sl, r2, lsl r2
d001cde4:	f44f00b1 	vst4.32	{d16-d19}, [pc :256], r1
d001cde8:	fbb22280 	blx	0xceca57f2
d001cdec:	9912f2f1 	ldmdbls	r2, {r0, r4, r5, r6, r7, r9, ip, sp, lr, pc}
d001cdf0:	d9244291 	stmdble	r4!, {r0, r4, r7, r9, lr}
d001cdf4:	2710f8df 			; <UNDEFINED> instruction: 0x2710f8df
d001cdf8:	711af44f 	tstvc	sl, pc, asr #8	; <UNPREDICTABLE>
d001cdfc:	fb01447a 	blx	0xd006dfee
d001ce00:	f5032303 			; <UNDEFINED> instruction: 0xf5032303
d001ce04:	f89333c9 			; <UNDEFINED> instruction: 0xf89333c9
d001ce08:	b9a3310b 	stmiblt	r3!, {r0, r1, r3, r8, ip, sp}
d001ce0c:	46fcf8df 	usatmi	pc, #28, pc, asr #17	; <UNPREDICTABLE>
d001ce10:	f8df447c 			; <UNDEFINED> instruction: 0xf8df447c
d001ce14:	447b36fc 	ldrbtmi	r3, [fp], #-1788	; 0xfffff904
d001ce18:	2a006d9a 	bcs	0xd0038488
d001ce1c:	ac99f47f 	cfldrsge	mvf15, [r9], {127}	; 0x7f
d001ce20:	6a996a58 	bvs	0xce677788
d001ce24:	5030f893 	mlaspl	r0, r3, r8, pc	; <UNPREDICTABLE>
d001ce28:	e9c36b5a 	stmib	r3, {r1, r3, r4, r6, r8, r9, fp, sp, lr}^
d001ce2c:	e9c34016 	stmib	r3, {r1, r2, r4, lr}^
d001ce30:	669a1518 			; <UNDEFINED> instruction: 0x669a1518
d001ce34:	f8dfe48d 			; <UNDEFINED> instruction: 0xf8dfe48d
d001ce38:	447c46dc 	ldrbtmi	r4, [ip], #-1756	; 0xfffff924
d001ce3c:	4628e7e9 	strtmi	lr, [r8], -r9, ror #15
d001ce40:	ffd8f7f5 			; <UNDEFINED> instruction: 0xffd8f7f5
d001ce44:	26d0f8df 			; <UNDEFINED> instruction: 0x26d0f8df
d001ce48:	4628215d 			; <UNDEFINED> instruction: 0x4628215d
d001ce4c:	f7f5447a 			; <UNDEFINED> instruction: 0xf7f5447a
d001ce50:	2800fffa 	stmdacs	r0, {r1, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d001ce54:	ac7df43f 	cfldrdge	mvd15, [sp], #-252	; 0xffffff04
d001ce58:	06c0f8df 			; <UNDEFINED> instruction: 0x06c0f8df
d001ce5c:	9b12213d 	blls	0xd04a5358
d001ce60:	435e4478 	cmpmi	lr, #120, 8	; 0x78000000
d001ce64:	3500f500 	strcc	pc, [r0, #-1280]	; 0xfffffb00
d001ce68:	3100f8d5 	ldrdcc	pc, [r0, -r5]
d001ce6c:	f7f59313 			; <UNDEFINED> instruction: 0xf7f59313
d001ce70:	b138ffdc 	teqlt	r8, ip	; <illegal shifter operand>	; <UNPREDICTABLE>
d001ce74:	3100f8d5 	ldrdcc	pc, [r0, -r5]
d001ce78:	6380f5c3 	orrvs	pc, r0, #817889280	; 0x30c00000
d001ce7c:	d923429e 	stmdble	r3!, {r1, r2, r3, r4, r7, r9, lr}
d001ce80:	f84cf7f7 			; <UNDEFINED> instruction: 0xf84cf7f7
d001ce84:	5698f8df 			; <UNDEFINED> instruction: 0x5698f8df
d001ce88:	f8df213b 			; <UNDEFINED> instruction: 0xf8df213b
d001ce8c:	447d2698 	ldrbtmi	r2, [sp], #-1688	; 0xfffff968
d001ce90:	4628447a 			; <UNDEFINED> instruction: 0x4628447a
d001ce94:	ffd7f7f5 			; <UNDEFINED> instruction: 0xffd7f7f5
d001ce98:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001ce9c:	4652ac5a 			; <UNDEFINED> instruction: 0x4652ac5a
d001cea0:	46284649 	strtmi	r4, [r8], -r9, asr #12
d001cea4:	fc71f7f3 	ldc2l	7, cr15, [r1], #-972	; 0xfffffc34
d001cea8:	db2d2800 	blle	0xd0b66eb0
d001ceac:	3678f8df 			; <UNDEFINED> instruction: 0x3678f8df
d001ceb0:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d001ceb4:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d001ceb8:	f8dfac4c 			; <UNDEFINED> instruction: 0xf8dfac4c
d001cebc:	447a2670 	ldrbtmi	r2, [sl], #-1648	; 0xfffff990
d001cec0:	2301e76d 	movwcs	lr, #5997	; 0x176d
d001cec4:	e7c79312 	bfi	r9, r2, #6, #2
d001cec8:	f7f64630 			; <UNDEFINED> instruction: 0xf7f64630
d001cecc:	4605ffef 	strmi	pc, [r5], -pc, ror #31
d001ced0:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001ced4:	9834ac3e 	ldmdals	r4!, {r1, r2, r3, r4, r5, sl, fp, sp, pc}
d001ced8:	2200b187 	andcs	fp, r0, #-1073741791	; 0xc0000021
d001cedc:	462b4601 	strtmi	r4, [fp], -r1, lsl #12
d001cee0:	92009812 	andls	r9, r0, #1179648	; 0x120000
d001cee4:	ff5cf7fc 			; <UNDEFINED> instruction: 0xff5cf7fc
d001cee8:	429e2300 	addsmi	r2, lr, #0, 6
d001ceec:	f855d0ca 			; <UNDEFINED> instruction: 0xf855d0ca
d001cef0:	2a002023 	bcs	0xd0024f84
d001cef4:	8065f041 	rsbhi	pc, r5, r1, asr #32
d001cef8:	e7f63301 	ldrb	r3, [r6, r1, lsl #6]!
d001cefc:	462a2301 	strtmi	r2, [sl], -r1, lsl #6
d001cf00:	f7fc4639 			; <UNDEFINED> instruction: 0xf7fc4639
d001cf04:	e7effe1b 			; <UNDEFINED> instruction: 0xe7effe1b
d001cf08:	46494652 			; <UNDEFINED> instruction: 0x46494652
d001cf0c:	f7f34628 			; <UNDEFINED> instruction: 0xf7f34628
d001cf10:	2800fc18 	stmdacs	r0, {r3, r4, sl, fp, ip, sp, lr, pc}
d001cf14:	4652daca 	ldrbmi	sp, [r2], -sl, asr #21
d001cf18:	46284649 	strtmi	r4, [r8], -r9, asr #12
d001cf1c:	fc78f7f3 	ldc2l	7, cr15, [r8], #-972	; 0xfffffc34
d001cf20:	dac32800 	ble	0xcf0e6f28
d001cf24:	32c8f505 	sbccc	pc, r8, #20971520	; 0x1400000
d001cf28:	f8d200b3 			; <UNDEFINED> instruction: 0xf8d200b3
d001cf2c:	298010a4 	stmibcs	r0, {r2, r5, r7, ip}
d001cf30:	f505d008 			; <UNDEFINED> instruction: 0xf505d008
d001cf34:	b98432f8 	stmiblt	r4, {r3, r4, r5, r6, r7, r9, ip, sp}
d001cf38:	50fcf8d2 	ldrsbtpl	pc, [ip], #130	; 0x82	; <UNPREDICTABLE>
d001cf3c:	2080f5c3 	addcs	pc, r0, r3, asr #11
d001cf40:	d9624285 	stmdble	r2!, {r0, r2, r7, r9, lr}^
d001cf44:	35e8f8df 	strbcc	pc, [r8, #2271]!	; 0x8df	; <UNPREDICTABLE>
d001cf48:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d001cf4c:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d001cf50:	f8dfac00 			; <UNDEFINED> instruction: 0xf8dfac00
d001cf54:	447a25e0 	ldrbtmi	r2, [sl], #-1504	; 0xfffffa20
d001cf58:	f8d2e721 			; <UNDEFINED> instruction: 0xf8d2e721
d001cf5c:	350350f8 	strcc	r5, [r3, #-248]	; 0xffffff08
d001cf60:	0503f025 	streq	pc, [r3, #-37]	; 0xffffffdb
d001cf64:	f8c2442b 			; <UNDEFINED> instruction: 0xf8c2442b
d001cf68:	f8df30f8 			; <UNDEFINED> instruction: 0xf8df30f8
d001cf6c:	2f0035cc 	svccs	0x000035cc
d001cf70:	0001f101 	andeq	pc, r1, r1, lsl #2
d001cf74:	fb84fa5f 	blx	0xce15b8fa
d001cf78:	f8bd447b 			; <UNDEFINED> instruction: 0xf8bd447b
d001cf7c:	f503704c 			; <UNDEFINED> instruction: 0xf503704c
d001cf80:	f8c232c8 			; <UNDEFINED> instruction: 0xf8c232c8
d001cf84:	bf1400a4 	svclt	0x001400a4
d001cf88:	220f2211 	andcs	r2, pc, #268435457	; 0x10000001
d001cf8c:	92182c00 	andsls	r2, r8, #0, 24
d001cf90:	2600bf08 	strcs	fp, [r0], -r8, lsl #30
d001cf94:	92147a1a 	andsls	r7, r4, #106496	; 0x1a000
d001cf98:	20d0f89d 	smullscs	pc, r0, sp, r8	; <UNPREDICTABLE>
d001cf9c:	22389216 	eorscs	r9, r8, #1610612737	; 0x60000001
d001cfa0:	3401fb02 	strcc	pc, [r1], #-2818	; 0xfffff4fe
d001cfa4:	f5042100 			; <UNDEFINED> instruction: 0xf5042100
d001cfa8:	f10434ba 			; <UNDEFINED> instruction: 0xf10434ba
d001cfac:	461803a4 	ldrmi	r0, [r8], -r4, lsr #7
d001cfb0:	fa18f002 	blx	0xd0658fc0
d001cfb4:	f10d9a11 			; <UNDEFINED> instruction: 0xf10d9a11
d001cfb8:	f88d0ef0 			; <UNDEFINED> instruction: 0xf88d0ef0
d001cfbc:	923f8108 	eorsls	r8, pc, #8, 2
d001cfc0:	9a104684 	bls	0xd042e9d8
d001cfc4:	50c8f8c4 	sbcpl	pc, r8, r4, asr #17
d001cfc8:	9a0f9240 	bls	0xd04018d0
d001cfcc:	9a3ce9cd 	bls	0xd0f57708
d001cfd0:	e8be9243 	ldm	lr!, {r0, r1, r6, r9, ip, pc}
d001cfd4:	e8ac000f 	stmia	ip!, {r0, r1, r2, r3}
d001cfd8:	e89e000f 	ldm	lr, {r0, r1, r2, r3}
d001cfdc:	e88c000f 	stm	ip, {r0, r1, r2, r3}
d001cfe0:	9b18000f 	blls	0xd061d024
d001cfe4:	30ccf884 	sbccc	pc, ip, r4, lsl #17
d001cfe8:	f8849b14 			; <UNDEFINED> instruction: 0xf8849b14
d001cfec:	9b1630cd 	blls	0xd05a9328
d001cff0:	30cef884 	sbccc	pc, lr, r4, lsl #17
d001cff4:	b0cff884 	sbclt	pc, pc, r4, lsl #17
d001cff8:	f8a49b12 			; <UNDEFINED> instruction: 0xf8a49b12
d001cffc:	f8a470d2 			; <UNDEFINED> instruction: 0xf8a470d2
d001d000:	f8c460d4 			; <UNDEFINED> instruction: 0xf8c460d4
d001d004:	f7ff30d8 			; <UNDEFINED> instruction: 0xf7ff30d8
d001d008:	3503bba4 	strcc	fp, [r3, #-2980]	; 0xfffff45c
d001d00c:	0503f025 	streq	pc, [r3, #-37]	; 0xffffffdb
d001d010:	f8c2442b 			; <UNDEFINED> instruction: 0xf8c2442b
d001d014:	e7a830fc 			; <UNDEFINED> instruction: 0xe7a830fc
d001d018:	b9239b13 	stmdblt	r3!, {r0, r1, r4, r8, r9, fp, ip, pc}
d001d01c:	1109f240 	tstne	r9, r0, asr #4	; <UNPREDICTABLE>
d001d020:	f7f54628 			; <UNDEFINED> instruction: 0xf7f54628
d001d024:	f8dfff02 			; <UNDEFINED> instruction: 0xf8dfff02
d001d028:	f44f0514 	vst3.8	{d16,d18,d20}, [pc :64], r4
d001d02c:	44787184 	ldrbtmi	r7, [r8], #-388	; 0xfffffe7c
d001d030:	fefbf7f5 	mrc2	7, 7, pc, cr11, cr5, {7}
d001d034:	28004605 	stmdacs	r0, {r0, r2, r9, sl, lr}
d001d038:	8089f040 	addhi	pc, r9, r0, asr #32
d001d03c:	0500f8df 	streq	pc, [r0, #-2271]	; 0xfffff721
d001d040:	f7f74478 			; <UNDEFINED> instruction: 0xf7f74478
d001d044:	4682fda1 	strmi	pc, [r2], r1, lsr #27
d001d048:	f0402800 			; <UNDEFINED> instruction: 0xf0402800
d001d04c:	9b138083 	blls	0xd04fd260
d001d050:	f8dfb9a3 			; <UNDEFINED> instruction: 0xf8dfb9a3
d001d054:	f24054f0 	vqshl.s8	<illegal reg q10.5>, q8, q8
d001d058:	447d1107 	ldrbtmi	r1, [sp], #-263	; 0xfffffef9
d001d05c:	f7f54628 			; <UNDEFINED> instruction: 0xf7f54628
d001d060:	2800fee4 	stmdacs	r0, {r2, r5, r6, r7, r9, sl, fp, ip, sp, lr, pc}
d001d064:	f8dfd04b 			; <UNDEFINED> instruction: 0xf8dfd04b
d001d068:	212a04e0 	smulwtcs	sl, r0, r4
d001d06c:	f7f54478 			; <UNDEFINED> instruction: 0xf7f54478
d001d070:	2800fedc 	stmdacs	r0, {r2, r3, r4, r6, r7, r9, sl, fp, ip, sp, lr, pc}
d001d074:	2500d074 	strcs	sp, [r0, #-116]	; 0xffffff8c
d001d078:	e0152303 	ands	r2, r5, r3, lsl #6
d001d07c:	04ccf8df 	strbeq	pc, [ip], #2271	; 0x8df	; <UNPREDICTABLE>
d001d080:	f7f74478 			; <UNDEFINED> instruction: 0xf7f74478
d001d084:	2800fd81 	stmdacs	r0, {r0, r7, r8, sl, fp, ip, sp, lr, pc}
d001d088:	f8dfd166 			; <UNDEFINED> instruction: 0xf8dfd166
d001d08c:	447804c4 	ldrbtmi	r0, [r8], #-1220	; 0xfffffb3c
d001d090:	fd7af7f7 	ldc2l	7, cr15, [sl, #-988]!	; 0xfffffc24
d001d094:	f8dfb930 			; <UNDEFINED> instruction: 0xf8dfb930
d001d098:	447804bc 	ldrbtmi	r0, [r8], #-1212	; 0xfffffb44
d001d09c:	fd74f7f7 	ldc2l	7, cr15, [r4, #-988]!	; 0xfffffc24
d001d0a0:	d0d62800 	sbcsle	r2, r6, r0, lsl #16
d001d0a4:	23002505 	movwcs	r2, #1285	; 0x505
d001d0a8:	f8df9312 			; <UNDEFINED> instruction: 0xf8df9312
d001d0ac:	af2c64ac 	svcge	0x002c64ac
d001d0b0:	f106447e 			; <UNDEFINED> instruction: 0xf106447e
d001d0b4:	f8960c18 			; <UNDEFINED> instruction: 0xf8960c18
d001d0b8:	e8bc8030 	ldm	ip!, {r4, r5, pc}
d001d0bc:	c70f000f 	strgt	r0, [pc, -pc]
d001d0c0:	000fe89c 	muleq	pc, ip, r8	; <UNPREDICTABLE>
d001d0c4:	000fe887 	andeq	lr, pc, r7, lsl #17
d001d0c8:	f2406a73 	vpmin.s8	q11, q0, <illegal reg q9.5>
d001d0cc:	f8df1101 			; <UNDEFINED> instruction: 0xf8df1101
d001d0d0:	4630248c 	ldrtmi	r2, [r0], -ip, lsl #9
d001d0d4:	6ab39311 	bvs	0xced01d20
d001d0d8:	9310447a 	tstls	r0, #2046820352	; 0x7a000000
d001d0dc:	e9d66b73 	ldmib	r6, {r0, r1, r4, r5, r6, r8, r9, fp, sp, lr}^
d001d0e0:	930f9a06 	movwls	r9, #64006	; 0xfa06
d001d0e4:	feaff7f5 	mcr2	7, 5, pc, cr15, cr5, {7}	; <UNPREDICTABLE>
d001d0e8:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001d0ec:	9b13ab32 	blls	0xd0507dbc
d001d0f0:	2c00bbcb 			; <UNDEFINED> instruction: 0x2c00bbcb
d001d0f4:	8771f040 	ldrbhi	pc, [r1, -r0, asr #32]!	; <UNPREDICTABLE>
d001d0f8:	931623ff 	tstls	r6, #-67108861	; 0xfc000003
d001d0fc:	6aeae612 	bvs	0xcfad694c
d001d100:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d001d104:	d118429a 			; <UNDEFINED> instruction: 0xd118429a
d001d108:	e9d54628 	ldmib	r5, {r3, r5, r9, sl, lr}^
d001d10c:	f7f31206 			; <UNDEFINED> instruction: 0xf7f31206
d001d110:	2800fb3c 	stmdacs	r0, {r2, r3, r4, r5, r8, r9, fp, ip, sp, lr, pc}
d001d114:	4628db11 			; <UNDEFINED> instruction: 0x4628db11
d001d118:	1206e9d5 	andne	lr, r6, #3489792	; 0x354000
d001d11c:	fb35f7f3 	blx	0xd0d9b0f2
d001d120:	fb032324 	blx	0xd00e5dba
d001d124:	f5005000 			; <UNDEFINED> instruction: 0xf5005000
d001d128:	f89030e5 			; <UNDEFINED> instruction: 0xf89030e5
d001d12c:	2bff308c 	blcs	0xcffe9364
d001d130:	4628d103 	strtmi	sp, [r8], -r3, lsl #2
d001d134:	fe5ef7f5 	mrc2	7, 2, pc, cr14, cr5, {7}
d001d138:	f8dfe795 			; <UNDEFINED> instruction: 0xf8dfe795
d001d13c:	f8df1424 			; <UNDEFINED> instruction: 0xf8df1424
d001d140:	44790424 	ldrbtmi	r0, [r9], #-1060	; 0xfffffbdc
d001d144:	f7f34478 			; <UNDEFINED> instruction: 0xf7f34478
d001d148:	f7fff82f 			; <UNDEFINED> instruction: 0xf7fff82f
d001d14c:	2500bb02 	strcs	fp, [r0, #-2818]	; 0xfffff4fe
d001d150:	e7a92301 	str	r2, [r9, r1, lsl #6]!
d001d154:	e7a72302 	str	r2, [r7, r2, lsl #6]!
d001d158:	f8cd2501 			; <UNDEFINED> instruction: 0xf8cd2501
d001d15c:	e7a4a048 	str	sl, [r4, r8, asr #32]!
d001d160:	90124605 	andsls	r4, r2, r5, lsl #12
d001d164:	9b12e7a1 	blls	0xd04d6ff0
d001d168:	2d00b93b 	vstrcs.16	s22, [r0, #-118]	; 0xffffff8a	; <UNPREDICTABLE>
d001d16c:	86eff040 	strbthi	pc, [pc], r0, asr #32	; <UNPREDICTABLE>
d001d170:	447b4bfd 	ldrbtmi	r4, [fp], #-3069	; 0xfffff403
d001d174:	2b286adb 	blcs	0xd0a37ce8
d001d178:	2c00d10a 	stfcsd	f5, [r0], {10}
d001d17c:	4bfbd0bc 	blmi	0xcff11474
d001d180:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d001d184:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d001d188:	4af9aae4 	bmi	0xcfe87d20
d001d18c:	e606447a 			; <UNDEFINED> instruction: 0xe606447a
d001d190:	f88d9b11 			; <UNDEFINED> instruction: 0xf88d9b11
d001d194:	932f80c8 			; <UNDEFINED> instruction: 0x932f80c8
d001d198:	94059b10 	strls	r9, [r5], #-2832	; 0xfffff4f0
d001d19c:	9b0f9330 	blls	0xd0401e64
d001d1a0:	93339504 	teqls	r3, #4, 10	; 0x1000000
d001d1a4:	cb0fab30 	blgt	0xd0407e6c
d001d1a8:	000fe88d 	andeq	lr, pc, sp, lsl #17
d001d1ac:	e9cdab2c 	stmib	sp, {r2, r3, r5, r8, r9, fp, sp, pc}^
d001d1b0:	cb0f9a2c 	blgt	0xd0403a68
d001d1b4:	4652e54f 	ldrbmi	lr, [r2], -pc, asr #10
d001d1b8:	46204649 	strtmi	r4, [r0], -r9, asr #12
d001d1bc:	fac1f7f3 	blx	0xcf09b190
d001d1c0:	f6bf2800 			; <UNDEFINED> instruction: 0xf6bf2800
d001d1c4:	4aebadc4 	bmi	0xcfb088dc
d001d1c8:	46484651 			; <UNDEFINED> instruction: 0x46484651
d001d1cc:	f7f3447a 			; <UNDEFINED> instruction: 0xf7f3447a
d001d1d0:	bb40fb48 	bllt	0xd105bef8
d001d1d4:	46514ae8 	ldrbmi	r4, [r1], -r8, ror #21
d001d1d8:	447a4648 	ldrbtmi	r4, [sl], #-1608	; 0xfffff9b8
d001d1dc:	fb41f7f3 	blx	0xd109b1b2
d001d1e0:	4ae6bb18 	bmi	0xcf9cbe48
d001d1e4:	46484651 			; <UNDEFINED> instruction: 0x46484651
d001d1e8:	f7f3447a 			; <UNDEFINED> instruction: 0xf7f3447a
d001d1ec:	2800fb3a 	stmdacs	r0, {r1, r3, r4, r5, r8, r9, fp, ip, sp, lr, pc}
d001d1f0:	2300bf0c 	movwcs	fp, #3852	; 0xf0c
d001d1f4:	4ae2230c 	bmi	0xcf8a5e2c
d001d1f8:	46484651 			; <UNDEFINED> instruction: 0x46484651
d001d1fc:	447a9314 	ldrbtmi	r9, [sl], #-788	; 0xfffffcec
d001d200:	fb2ff7f3 	blx	0xd0c1b1d6
d001d204:	901c9b14 	andsls	r9, ip, r4, lsl fp
d001d208:	d0104303 	andsle	r4, r0, r3, lsl #6
d001d20c:	9a129b13 	bls	0xd04c3e60
d001d210:	d00c4313 	andle	r4, ip, r3, lsl r3
d001d214:	447b4bdb 	ldrbtmi	r4, [fp], #-3035	; 0xfffff425
d001d218:	2a006d9a 	bcs	0xd0038888
d001d21c:	aa99f47f 	bge	0xce69a420
d001d220:	447a4ad9 	ldrbtmi	r4, [sl], #-2777	; 0xfffff527
d001d224:	2304e5bb 	movwcs	lr, #17851	; 0x45bb
d001d228:	2308e7e5 	movwcs	lr, #34789	; 0x87e5
d001d22c:	9b14e7e3 	blls	0xd05571c0
d001d230:	ac202500 	cfstr32ge	mvfx2, [r0], #-0
d001d234:	95202b04 	strls	r2, [r0, #-2820]!	; 0xfffff4fc
d001d238:	5084f88d 	addpl	pc, r4, sp, lsl #17
d001d23c:	f88d9522 			; <UNDEFINED> instruction: 0xf88d9522
d001d240:	d149508c 	smlalbble	r5, r9, ip, r0
d001d244:	f44f4dd1 			; <UNDEFINED> instruction: 0xf44f4dd1
d001d248:	4ad17185 	bmi	0xcf479864
d001d24c:	447a447d 	ldrbtmi	r4, [sl], #-1149	; 0xfffffb83
d001d250:	92184628 	andsls	r4, r8, #40, 12	; 0x2800000
d001d254:	fdf7f7f5 	ldc2l	7, cr15, [r7, #980]!	; 0x3d4
d001d258:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001d25c:	9a18aa7a 	bls	0xd0647c4c
d001d260:	110bf240 	tstne	fp, r0, asr #4	; <UNPREDICTABLE>
d001d264:	f7f54628 			; <UNDEFINED> instruction: 0xf7f54628
d001d268:	2800fdee 	stmdacs	r0, {r1, r2, r3, r5, r6, r7, r8, sl, fp, ip, sp, lr, pc}
d001d26c:	aa71f43f 	bge	0xd1c9a370
d001d270:	212a9a18 			; <UNDEFINED> instruction: 0x212a9a18
d001d274:	f7f54628 			; <UNDEFINED> instruction: 0xf7f54628
d001d278:	2800fde6 	stmdacs	r0, {r1, r2, r5, r6, r7, r8, sl, fp, ip, sp, lr, pc}
d001d27c:	aa69f43f 	bge	0xd1a9a380
d001d280:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d001d284:	f7f54628 			; <UNDEFINED> instruction: 0xf7f54628
d001d288:	f04ffdd0 			; <UNDEFINED> instruction: 0xf04ffdd0
d001d28c:	23020b01 	movwcs	r0, #11009	; 0x2b01
d001d290:	4cc07023 	stclmi	0, cr7, [r0], {35}	; 0x23
d001d294:	4ac02129 	bmi	0xcf025740
d001d298:	447a447c 	ldrbtmi	r4, [sl], #-1148	; 0xfffffb84
d001d29c:	f7f54620 			; <UNDEFINED> instruction: 0xf7f54620
d001d2a0:	2800fdd2 	stmdacs	r0, {r1, r4, r6, r7, r8, sl, fp, ip, sp, lr, pc}
d001d2a4:	aa55f43f 	bge	0xd159a3a8
d001d2a8:	2b049b12 	blcs	0xd0143ef8
d001d2ac:	81e5f040 	mvnhi	pc, r0, asr #32
d001d2b0:	0f05f1bb 	svceq	0x0005f1bb
d001d2b4:	81e1f040 	mvnhi	pc, r0, asr #32
d001d2b8:	2b006da3 	blcs	0xd003894c
d001d2bc:	aa49f47f 	bge	0xd129a4c0
d001d2c0:	447b4bb6 	ldrbtmi	r4, [fp], #-2998	; 0xfffff44a
d001d2c4:	9b1165a3 	blls	0xd0476958
d001d2c8:	9b1065e3 	blls	0xd0436a5c
d001d2cc:	3818e9c4 	ldmdacc	r8, {r2, r6, r7, r8, fp, sp, lr, pc}
d001d2d0:	66a39b0f 	strtvs	r9, [r3], pc, lsl #22
d001d2d4:	ba3df7ff 	blt	0xd0f9b2d8
d001d2d8:	447848b1 	ldrbtmi	r4, [r8], #-2225	; 0xfffff74f
d001d2dc:	f5b36ac3 			; <UNDEFINED> instruction: 0xf5b36ac3
d001d2e0:	d1067f84 	smlabble	r6, r4, pc, r7	; <UNPREDICTABLE>
d001d2e4:	2b296cc3 	blcs	0xd0a785f8
d001d2e8:	46abd103 	strtmi	sp, [fp], r3, lsl #2
d001d2ec:	fd82f7f5 	stc2	7, cr15, [r2, #980]	; 0x3d4
d001d2f0:	4dace7cf 	stcmi	7, cr14, [ip, #828]!	; 0x33c
d001d2f4:	4eacac20 	cdpmi	12, 10, cr10, cr12, cr0, {1}
d001d2f8:	0b00f04f 	bleq	0xd005943c
d001d2fc:	447e447d 	ldrbtmi	r4, [lr], #-1149	; 0xfffffb83
d001d300:	4350f505 	cmpmi	r0, #20971520	; 0x1400000	; <UNPREDICTABLE>
d001d304:	9318331c 	tstls	r8, #28, 6	; 0x70000000
d001d308:	0f01f1bb 	svceq	0x0001f1bb
d001d30c:	9b1cd14e 	blls	0xd075184c
d001d310:	d04b2b00 	suble	r2, fp, r0, lsl #22
d001d314:	931eab20 	tstls	lr, #32, 22	; 0x8000
d001d318:	2b00781b 	blcs	0xd003b38c
d001d31c:	4fa3d146 	svcmi	0x00a3d146
d001d320:	110bf240 	tstne	fp, r0, asr #4	; <UNPREDICTABLE>
d001d324:	4638447f 			; <UNDEFINED> instruction: 0x4638447f
d001d328:	fd7ff7f5 	ldc2l	7, cr15, [pc, #-980]!	; 0xd001cf5c
d001d32c:	d03d2800 	eorsle	r2, sp, r0, lsl #16
d001d330:	212a4a9f 			; <UNDEFINED> instruction: 0x212a4a9f
d001d334:	447a4638 	ldrbtmi	r4, [sl], #-1592	; 0xfffff9c8
d001d338:	f7f5921f 			; <UNDEFINED> instruction: 0xf7f5921f
d001d33c:	2800fd84 	stmdacs	r0, {r2, r7, r8, sl, fp, ip, sp, lr, pc}
d001d340:	aa07f43f 	bge	0xd021a444
d001d344:	212a9a1f 			; <UNDEFINED> instruction: 0x212a9a1f
d001d348:	f7f54638 			; <UNDEFINED> instruction: 0xf7f54638
d001d34c:	2800fd7c 	stmdacs	r0, {r2, r3, r4, r5, r6, r8, sl, fp, ip, sp, lr, pc}
d001d350:	a9fff43f 	ldmibge	pc!, {r0, r1, r2, r3, r4, r5, sl, ip, sp, lr, pc}^	; <UNPREDICTABLE>
d001d354:	9a1e2304 	bls	0xd07a5f6c
d001d358:	4f967053 	svcmi	0x00967053
d001d35c:	0cf0f10d 	ldfeqp	f7, [r0], #52	; 0x34
d001d360:	eb0c447f 	bl	0xd032e564
d001d364:	f10b1c4b 			; <UNDEFINED> instruction: 0xf10b1c4b
d001d368:	f1070b01 			; <UNDEFINED> instruction: 0xf1070b01
d001d36c:	e8be0e18 	ldm	lr!, {r3, r4, r9, sl, fp}
d001d370:	e8ac000f 	stmia	ip!, {r0, r1, r2, r3}
d001d374:	e89e000f 	ldm	lr, {r0, r1, r2, r3}
d001d378:	e88c000f 	stm	ip, {r0, r1, r2, r3}
d001d37c:	f240000f 	vhadd.s8	d16, d0, d15
d001d380:	46381101 	ldrtmi	r1, [r8], -r1, lsl #2
d001d384:	fd51f7f5 	ldc2l	7, cr15, [r1, #-980]	; 0xfffffc2c
d001d388:	3b01f814 	blcc	0xd009b3e0
d001d38c:	d0802b04 	addle	r2, r0, r4, lsl #22
d001d390:	4638212c 	ldrtmi	r2, [r8], -ip, lsr #2
d001d394:	fd49f7f5 	stc2l	7, cr15, [r9, #-980]	; 0xfffffc2c
d001d398:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001d39c:	f1bbaf7a 			; <UNDEFINED> instruction: 0xf1bbaf7a
d001d3a0:	d1b10f05 			; <UNDEFINED> instruction: 0xd1b10f05
d001d3a4:	46384984 	ldrtmi	r4, [r8], -r4, lsl #19
d001d3a8:	e6cc4479 	uxtab16	r4, ip, r9, ror #8
d001d3ac:	f7f34630 			; <UNDEFINED> instruction: 0xf7f34630
d001d3b0:	b1e8fa10 	mvnlt	pc, r0, lsl sl	; <UNPREDICTABLE>
d001d3b4:	a9342300 	ldmdbge	r4!, {r8, r9, sp}
d001d3b8:	93344630 	teqls	r4, #48, 12	; 0x3000000
d001d3bc:	ff40f7f5 			; <UNDEFINED> instruction: 0xff40f7f5
d001d3c0:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001d3c4:	212aa9c6 	smlawtcs	sl, r6, r9, sl
d001d3c8:	f7f54630 			; <UNDEFINED> instruction: 0xf7f54630
d001d3cc:	b168fd2e 	msrlt	SPSR_f, lr, lsr #26
d001d3d0:	4630212a 	ldrtmi	r2, [r0], -sl, lsr #2
d001d3d4:	fd29f7f5 	stc2	7, cr15, [r9, #-980]!	; 0xfffffc2c
d001d3d8:	bf142800 	svclt	0x00142800
d001d3dc:	230e2312 	movwcs	r2, #58130	; 0xe312
d001d3e0:	ab227023 	blge	0xd08b9474
d001d3e4:	f80b9a34 			; <UNDEFINED> instruction: 0xf80b9a34
d001d3e8:	e7b62003 	ldr	r2, [r6, r3]!
d001d3ec:	e7f7230d 	ldrb	r2, [r7, sp, lsl #6]!
d001d3f0:	f2406af2 	vpmin.s8	q11, q8, q9
d001d3f4:	429a131b 	addsmi	r1, sl, #1811939328	; 0x6c000000
d001d3f8:	4f70d025 	svcmi	0x0070d025
d001d3fc:	1107f240 	tstne	r7, r0, asr #4	; <UNPREDICTABLE>
d001d400:	4638447f 			; <UNDEFINED> instruction: 0x4638447f
d001d404:	fd11f7f5 	ldc2	7, cr15, [r1, #-980]	; 0xfffffc2c
d001d408:	6afabb10 	bvs	0xcfecc050
d001d40c:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d001d410:	d12e429a 			; <UNDEFINED> instruction: 0xd12e429a
d001d414:	e9d74638 	ldmib	r7, {r3, r4, r5, r9, sl, lr}^
d001d418:	f7f31206 			; <UNDEFINED> instruction: 0xf7f31206
d001d41c:	2800f9b6 	stmdacs	r0, {r1, r2, r4, r5, r7, r8, fp, ip, sp, lr, pc}
d001d420:	4638db27 	ldrtmi	sp, [r8], -r7, lsr #22
d001d424:	1206e9d7 	andne	lr, r6, #3522560	; 0x35c000
d001d428:	f9aff7f3 			; <UNDEFINED> instruction: 0xf9aff7f3
d001d42c:	fb032324 	blx	0xd00e60c6
d001d430:	f5007000 			; <UNDEFINED> instruction: 0xf5007000
d001d434:	f89030e5 			; <UNDEFINED> instruction: 0xf89030e5
d001d438:	2bff308c 	blcs	0xcffe9670
d001d43c:	4638d119 			; <UNDEFINED> instruction: 0x4638d119
d001d440:	fcd8f7f5 	ldc2l	7, cr15, [r8], {245}	; 0xf5
d001d444:	4630e004 	ldrtmi	lr, [r0], -r4
d001d448:	fff0f7f5 			; <UNDEFINED> instruction: 0xfff0f7f5
d001d44c:	d0d42800 	sbcsle	r2, r4, r0, lsl #16
d001d450:	212a4f5b 			; <UNDEFINED> instruction: 0x212a4f5b
d001d454:	4638447f 			; <UNDEFINED> instruction: 0x4638447f
d001d458:	fce7f7f5 	stc2l	7, cr15, [r7], #980	; 0x3d4
d001d45c:	212ab138 			; <UNDEFINED> instruction: 0x212ab138
d001d460:	f7f54638 			; <UNDEFINED> instruction: 0xf7f54638
d001d464:	2800fce2 	stmdacs	r0, {r1, r5, r6, r7, sl, fp, ip, sp, lr, pc}
d001d468:	2013bf14 	andscs	fp, r3, r4, lsl pc
d001d46c:	7020200a 	eorvc	r2, r0, sl
d001d470:	4854e773 	ldmdami	r4, {r0, r1, r4, r5, r6, r8, r9, sl, sp, lr, pc}^
d001d474:	f7f74478 			; <UNDEFINED> instruction: 0xf7f74478
d001d478:	b110fb87 	tstlt	r0, r7, lsl #23	; <UNPREDICTABLE>
d001d47c:	70232303 	eorvc	r2, r3, r3, lsl #6
d001d480:	4851e76b 	ldmdami	r1, {r0, r1, r3, r5, r6, r8, r9, sl, sp, lr, pc}^
d001d484:	f7f74478 			; <UNDEFINED> instruction: 0xf7f74478
d001d488:	2800fb7f 	stmdacs	r0, {r0, r1, r2, r3, r4, r5, r6, r8, r9, fp, ip, sp, lr, pc}
d001d48c:	809ef000 	addshi	pc, lr, r0
d001d490:	e7f42301 	ldrb	r2, [r4, r1, lsl #6]!
d001d494:	00006ba6 	andeq	r6, r0, r6, lsr #23
d001d498:	fffff51c 			; <UNDEFINED> instruction: 0xfffff51c
d001d49c:	fffff51a 			; <UNDEFINED> instruction: 0xfffff51a
d001d4a0:	fffff51e 			; <UNDEFINED> instruction: 0xfffff51e
d001d4a4:	00006b18 	andeq	r6, r0, r8, lsl fp
d001d4a8:	00006ab2 			; <UNDEFINED> instruction: 0x00006ab2
d001d4ac:	fffff4ac 			; <UNDEFINED> instruction: 0xfffff4ac
d001d4b0:	fffff4af 			; <UNDEFINED> instruction: 0xfffff4af
d001d4b4:	00006a42 	andeq	r6, r0, r2, asr #20
d001d4b8:	fffff47a 			; <UNDEFINED> instruction: 0xfffff47a
d001d4bc:	fffff41c 			; <UNDEFINED> instruction: 0xfffff41c
d001d4c0:	fffff452 			; <UNDEFINED> instruction: 0xfffff452
d001d4c4:	fffff44c 			; <UNDEFINED> instruction: 0xfffff44c
d001d4c8:	ffff6727 			; <UNDEFINED> instruction: 0xffff6727
d001d4cc:	fffff37c 			; <UNDEFINED> instruction: 0xfffff37c
d001d4d0:	fffff38d 			; <UNDEFINED> instruction: 0xfffff38d
d001d4d4:	0000689e 	muleq	r0, lr, r8
d001d4d8:	fffff311 			; <UNDEFINED> instruction: 0xfffff311
d001d4dc:	fffff309 			; <UNDEFINED> instruction: 0xfffff309
d001d4e0:	fffff2f2 			; <UNDEFINED> instruction: 0xfffff2f2
d001d4e4:	fffff2dc 			; <UNDEFINED> instruction: 0xfffff2dc
d001d4e8:	000066ee 	andeq	r6, r0, lr, ror #13
d001d4ec:	ffffac34 			; <UNDEFINED> instruction: 0xffffac34
d001d4f0:	000066ca 	andeq	r6, r0, sl, asr #13
d001d4f4:	ffffe994 			; <UNDEFINED> instruction: 0xffffe994
d001d4f8:	fffff23d 			; <UNDEFINED> instruction: 0xfffff23d
d001d4fc:	00006682 	andeq	r6, r0, r2, lsl #13
d001d500:	fffff246 			; <UNDEFINED> instruction: 0xfffff246
d001d504:	0000664a 	andeq	r6, r0, sl, asr #12
d001d508:	00006620 	andeq	r6, r0, r0, lsr #12
d001d50c:	ffffef8b 			; <UNDEFINED> instruction: 0xffffef8b
d001d510:	00006606 	andeq	r6, r0, r6, lsl #12
d001d514:	ffffef41 			; <UNDEFINED> instruction: 0xffffef41
d001d518:	ffffd0fe 			; <UNDEFINED> instruction: 0xffffd0fe
d001d51c:	000065bc 			; <UNDEFINED> instruction: 0x000065bc
d001d520:	0000658e 	andeq	r6, r0, lr, lsl #11
d001d524:	fffff17d 			; <UNDEFINED> instruction: 0xfffff17d
d001d528:	0000656c 	andeq	r6, r0, ip, ror #10
d001d52c:	ffffe836 			; <UNDEFINED> instruction: 0xffffe836
d001d530:	000064d4 	ldrdeq	r6, [r0], -r4
d001d534:	fffff0e4 			; <UNDEFINED> instruction: 0xfffff0e4
d001d538:	000064a4 	andeq	r6, r0, r4, lsr #9
d001d53c:	000063ee 	andeq	r6, r0, lr, ror #7
d001d540:	fffff023 			; <UNDEFINED> instruction: 0xfffff023
d001d544:	000063c2 	andeq	r6, r0, r2, asr #7
d001d548:	000063b0 			; <UNDEFINED> instruction: 0x000063b0
d001d54c:	ffffcf40 			; <UNDEFINED> instruction: 0xffffcf40
d001d550:	ffffcf3b 			; <UNDEFINED> instruction: 0xffffcf3b
d001d554:	ffff66ec 			; <UNDEFINED> instruction: 0xffff66ec
d001d558:	0000636c 	andeq	r6, r0, ip, ror #6
d001d55c:	ffffefd1 			; <UNDEFINED> instruction: 0xffffefd1
d001d560:	ffffef31 			; <UNDEFINED> instruction: 0xffffef31
d001d564:	000062d8 	ldrdeq	r6, [r0], -r8
d001d568:	000062aa 	andeq	r6, r0, sl, lsr #5
d001d56c:	0000629c 	muleq	r0, ip, r2
d001d570:	ffffef5d 			; <UNDEFINED> instruction: 0xffffef5d
d001d574:	ffffef3f 			; <UNDEFINED> instruction: 0xffffef3f
d001d578:	ffffef40 			; <UNDEFINED> instruction: 0xffffef40
d001d57c:	ffffef3f 			; <UNDEFINED> instruction: 0xffffef3f
d001d580:	ffffef38 			; <UNDEFINED> instruction: 0xffffef38
d001d584:	00006206 	andeq	r6, r0, r6, lsl #4
d001d588:	ffffef19 			; <UNDEFINED> instruction: 0xffffef19
d001d58c:	000061d0 	ldrdeq	r6, [r0], -r0
d001d590:	ffffef2d 			; <UNDEFINED> instruction: 0xffffef2d
d001d594:	00006184 	andeq	r6, r0, r4, lsl #3
d001d598:	fffff025 			; <UNDEFINED> instruction: 0xfffff025
d001d59c:	fffff01f 			; <UNDEFINED> instruction: 0xfffff01f
d001d5a0:	00006142 	andeq	r6, r0, r2, asr #2
d001d5a4:	00006120 	andeq	r6, r0, r0, lsr #2
d001d5a8:	0000611e 	andeq	r6, r0, lr, lsl r1
d001d5ac:	000060f8 	strdeq	r6, [r0], -r8
d001d5b0:	ffffee9a 			; <UNDEFINED> instruction: 0xffffee9a
d001d5b4:	000060bc 	strheq	r6, [r0], -ip
d001d5b8:	ffffedfe 			; <UNDEFINED> instruction: 0xffffedfe
d001d5bc:	0000601c 	andeq	r6, r0, ip, lsl r0
d001d5c0:	00005fc8 	andeq	r5, r0, r8, asr #31
d001d5c4:	ffff631a 			; <UNDEFINED> instruction: 0xffff631a
d001d5c8:	ffffcb3c 			; <UNDEFINED> instruction: 0xffffcb3c
d001d5cc:	0a20f8df 	beq	0xd085b950
d001d5d0:	f7f74478 			; <UNDEFINED> instruction: 0xf7f74478
d001d5d4:	b108fad9 	ldrdlt	pc, [r8, -r9]
d001d5d8:	e7502305 	ldrb	r2, [r0, -r5, lsl #6]
d001d5dc:	0a14f8df 	beq	0xd055b960
d001d5e0:	f7f74478 			; <UNDEFINED> instruction: 0xf7f74478
d001d5e4:	2800fad1 	stmdacs	r0, {r0, r4, r6, r7, r9, fp, ip, sp, lr, pc}
d001d5e8:	9b18d1f6 	blls	0xd0651dc8
d001d5ec:	2b00681b 	blcs	0xd0037660
d001d5f0:	f44fd03c 	vst4.8	{d29-d32}, [pc :256], ip
d001d5f4:	46287185 	strtmi	r7, [r8], -r5, lsl #3
d001d5f8:	fc17f7f5 	ldc2	7, cr15, [r7], {245}	; 0xf5
d001d5fc:	f8dfb308 			; <UNDEFINED> instruction: 0xf8dfb308
d001d600:	447809f8 	ldrbtmi	r0, [r8], #-2552	; 0xfffff608
d001d604:	fac0f7f7 	blx	0xcf05b5e8
d001d608:	f8dfb930 			; <UNDEFINED> instruction: 0xf8dfb930
d001d60c:	f8df19f0 			; <UNDEFINED> instruction: 0xf8df19f0
d001d610:	447909f0 	ldrbtmi	r0, [r9], #-2544	; 0xfffff610
d001d614:	e5964478 	ldr	r4, [r6, #1144]	; 0x478
d001d618:	29e8f8df 	stmibcs	r8!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d001d61c:	4628212a 	strtmi	r2, [r8], -sl, lsr #2
d001d620:	f7f5447a 			; <UNDEFINED> instruction: 0xf7f5447a
d001d624:	2800fc10 	stmdacs	r0, {r4, sl, fp, ip, sp, lr, pc}
d001d628:	f505d0ef 			; <UNDEFINED> instruction: 0xf505d0ef
d001d62c:	33944374 	orrscc	r4, r4, #116, 6	; 0xd0000001
d001d630:	b923881b 	stmdblt	r3!, {r0, r1, r3, r4, fp, pc}
d001d634:	19d0f8df 	ldmibne	r0, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d001d638:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d001d63c:	2306bb18 	movwcs	fp, #27416	; 0x6b18
d001d640:	9b18e71d 	blls	0xd06572bc
d001d644:	b18b681b 	orrlt	r6, fp, fp, lsl r8
d001d648:	7184f44f 	orrvc	pc, r4, pc, asr #8
d001d64c:	f7f54628 			; <UNDEFINED> instruction: 0xf7f54628
d001d650:	b158fbec 	cmplt	r8, ip, ror #23	; <UNPREDICTABLE>
d001d654:	29b4f8df 	ldmibcs	r4!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d001d658:	4628212a 	strtmi	r2, [r8], -sl, lsr #2
d001d65c:	f7f5447a 			; <UNDEFINED> instruction: 0xf7f5447a
d001d660:	2800fbf2 	stmdacs	r0, {r1, r4, r5, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d001d664:	a875f43f 	ldmdage	r5!, {r0, r1, r2, r3, r4, r5, sl, ip, sp, lr, pc}^
d001d668:	e7082302 	str	r2, [r8, -r2, lsl #6]
d001d66c:	19a0f8df 	stmibne	r0!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d001d670:	09a0f8df 	stmibeq	r0!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d001d674:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d001d678:	9b14e565 	blls	0xd0556c14
d001d67c:	d502071b 	strle	r0, [r2, #-1819]	; 0xfffff8e5
d001d680:	0f00f1bb 	svceq	0x0000f1bb
d001d684:	f8dfd14b 			; <UNDEFINED> instruction: 0xf8dfd14b
d001d688:	24007990 	strcs	r7, [r0], #-2448	; 0xfffff670
d001d68c:	f507447f 			; <UNDEFINED> instruction: 0xf507447f
d001d690:	f5073500 			; <UNDEFINED> instruction: 0xf5073500
d001d694:	f505360e 			; <UNDEFINED> instruction: 0xf505360e
d001d698:	f8d67582 			; <UNDEFINED> instruction: 0xf8d67582
d001d69c:	429c3104 	addsmi	r3, ip, #4, 2
d001d6a0:	2338d21a 	teqcs	r8, #-1610612735	; 0xa0000001
d001d6a4:	4363464a 	cmnmi	r3, #77594624	; 0x4a00000
d001d6a8:	0100e9d5 	ldrdeq	lr, [r0, -r5]
d001d6ac:	46539318 			; <UNDEFINED> instruction: 0x46539318
d001d6b0:	ffb4f7f2 			; <UNDEFINED> instruction: 0xffb4f7f2
d001d6b4:	d03e2800 	eorsle	r2, lr, r0, lsl #16
d001d6b8:	2028f895 	mlacs	r8, r5, r8, pc	; <UNPREDICTABLE>
d001d6bc:	304cf89d 	umaalcc	pc, ip, sp, r8	; <UNPREDICTABLE>
d001d6c0:	d138429a 	teqle	r8, sl	; <illegal shifter operand>
d001d6c4:	b1239b13 			; <UNDEFINED> instruction: 0xb1239b13
d001d6c8:	2029f895 	mlacs	r9, r5, r8, pc	; <UNPREDICTABLE>
d001d6cc:	429a7a3b 	addsmi	r7, sl, #241664	; 0x3b000
d001d6d0:	2c00d131 	stfcsd	f5, [r0], {49}	; 0x31
d001d6d4:	8448f280 	strbhi	pc, [r8], #-640	; 0xfffffd80	; <UNPREDICTABLE>
d001d6d8:	4940f8df 	stmdbmi	r0, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d001d6dc:	46494652 			; <UNDEFINED> instruction: 0x46494652
d001d6e0:	4620447c 			; <UNDEFINED> instruction: 0x4620447c
d001d6e4:	f894f7f3 			; <UNDEFINED> instruction: 0xf894f7f3
d001d6e8:	f2c02800 	vmlal.s8	q9, d0, d0
d001d6ec:	46528458 			; <UNDEFINED> instruction: 0x46528458
d001d6f0:	46204649 	strtmi	r4, [r0], -r9, asr #12
d001d6f4:	f88cf7f3 			; <UNDEFINED> instruction: 0xf88cf7f3
d001d6f8:	fb032338 	blx	0xd00e63e2
d001d6fc:	7a234000 	bvc	0xd08ed704
d001d700:	3000f500 	andcc	pc, r0, r0, lsl #10
d001d704:	212df890 	msrcs	CPSR_fsc, r0	; <illegal shifter operand>
d001d708:	f040429a 			; <UNDEFINED> instruction: 0xf040429a
d001d70c:	6da38448 	cfstrsvs	mvf8, [r3, #288]!	; 0x120
d001d710:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001d714:	f8dfa81e 			; <UNDEFINED> instruction: 0xf8dfa81e
d001d718:	447b3908 	ldrbtmi	r3, [fp], #-2312	; 0xfffff6f8
d001d71c:	f8dfe5d2 			; <UNDEFINED> instruction: 0xf8dfe5d2
d001d720:	447b3904 	ldrbtmi	r3, [fp], #-2308	; 0xfffff6fc
d001d724:	2a006d9a 	bcs	0xd0038d94
d001d728:	a813f47f 	ldmdage	r3, {r0, r1, r2, r3, r4, r5, r6, sl, ip, sp, lr, pc}
d001d72c:	28f8f8df 	ldmcs	r8!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d001d730:	f7ff447a 			; <UNDEFINED> instruction: 0xf7ff447a
d001d734:	3401bb34 	strcc	fp, [r1], #-2868	; 0xfffff4cc
d001d738:	e7ae3538 			; <UNDEFINED> instruction: 0xe7ae3538
d001d73c:	21001c62 	tstcs	r0, r2, ror #24
d001d740:	2104f8c3 	smlabtcs	r4, r3, r8, pc	; <UNPREDICTABLE>
d001d744:	7a2b2238 	bvc	0xd0ae602c
d001d748:	f704fb02 			; <UNDEFINED> instruction: 0xf704fb02
d001d74c:	19ee9318 	stmibne	lr!, {r3, r4, r8, r9, ip, pc}^
d001d750:	3700f507 	strcc	pc, [r0, -r7, lsl #10]
d001d754:	3600f506 	strcc	pc, [r0], -r6, lsl #10
d001d758:	7382f506 	orrvc	pc, r2, #25165824	; 0x1800000
d001d75c:	f0014618 			; <UNDEFINED> instruction: 0xf0014618
d001d760:	9a11fe41 	bls	0xd049d06c
d001d764:	0eb0f10d 	asneqs	f7, #5.0
d001d768:	80c8f88d 	sbchi	pc, r8, sp, lsl #17
d001d76c:	4684922f 	strmi	r9, [r4], pc, lsr #4
d001d770:	f8869a10 			; <UNDEFINED> instruction: 0xf8869a10
d001d774:	9230b128 	eorsls	fp, r0, #40, 2
d001d778:	e9cd9a0f 	stmib	sp, {r0, r1, r2, r3, r9, fp, ip, pc}^
d001d77c:	92339a2c 	eorsls	r9, r3, #44, 20	; 0x2c000
d001d780:	000fe8be 			; <UNDEFINED> instruction: 0x000fe8be
d001d784:	000fe8ac 	andeq	lr, pc, ip, lsr #17
d001d788:	000fe89e 	muleq	pc, lr, r8	; <UNPREDICTABLE>
d001d78c:	000fe88c 	andeq	lr, pc, ip, lsl #17
d001d790:	f2079b14 	vpadd.i8	d9, d7, d4
d001d794:	f507102f 			; <UNDEFINED> instruction: 0xf507102f
d001d798:	465a779a 			; <UNDEFINED> instruction: 0x465a779a
d001d79c:	3124f8c6 	smlawtcc	r4, r6, r8, pc	; <UNPREDICTABLE>
d001d7a0:	f886a920 			; <UNDEFINED> instruction: 0xf886a920
d001d7a4:	3b003129 	blcc	0xd0029c50
d001d7a8:	bf184428 	svclt	0x00184428
d001d7ac:	f8862301 			; <UNDEFINED> instruction: 0xf8862301
d001d7b0:	9b12312a 	blls	0xd04a9c60
d001d7b4:	312bf886 	smlawbcc	fp, r6, r8, pc	; <UNPREDICTABLE>
d001d7b8:	f8869b13 			; <UNDEFINED> instruction: 0xf8869b13
d001d7bc:	9b18312c 	blls	0xd0629c74
d001d7c0:	312df886 	smlawbcc	sp, r6, r8, pc	; <UNPREDICTABLE>
d001d7c4:	f8869b16 			; <UNDEFINED> instruction: 0xf8869b16
d001d7c8:	f001312e 			; <UNDEFINED> instruction: 0xf001312e
d001d7cc:	465afe19 			; <UNDEFINED> instruction: 0x465afe19
d001d7d0:	19e8a922 	stmibne	r8!, {r1, r5, r8, fp, sp, pc}^
d001d7d4:	fe14f001 	cdp2	0, 1, cr15, cr4, cr1, {0}
d001d7d8:	5850f8df 	ldmdapl	r0, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d001d7dc:	447d213b 	ldrbtmi	r2, [sp], #-315	; 0xfffffec5
d001d7e0:	f7f54628 			; <UNDEFINED> instruction: 0xf7f54628
d001d7e4:	2800fb22 	stmdacs	r0, {r1, r5, r8, r9, fp, ip, sp, lr, pc}
d001d7e8:	afb3f47e 	svcge	0x00b3f47e
d001d7ec:	fb032338 	blx	0xd00e64d6
d001d7f0:	f5045404 			; <UNDEFINED> instruction: 0xf5045404
d001d7f4:	f8943400 			; <UNDEFINED> instruction: 0xf8943400
d001d7f8:	b32e612a 			; <UNDEFINED> instruction: 0xb32e612a
d001d7fc:	2b006dab 	blcs	0xd0038eb0
d001d800:	afa7f47e 	svcge	0x00a7f47e
d001d804:	3828f8df 	stmdacc	r8!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d001d808:	f7ff447b 			; <UNDEFINED> instruction: 0xf7ff447b
d001d80c:	f893bab3 			; <UNDEFINED> instruction: 0xf893bab3
d001d810:	9a16312e 	bls	0xd05a9cd0
d001d814:	f0404293 			; <UNDEFINED> instruction: 0xf0404293
d001d818:	9b1883b8 	blls	0xd063e700
d001d81c:	a920465a 	stmdbge	r0!, {r1, r3, r4, r6, r9, sl, lr}
d001d820:	3600f503 	strcc	pc, [r0], -r3, lsl #10
d001d824:	102ff206 	eorne	pc, pc, r6, lsl #4
d001d828:	f0014428 			; <UNDEFINED> instruction: 0xf0014428
d001d82c:	2800fdf9 	stmdacs	r0, {r0, r3, r4, r5, r6, r7, r8, sl, fp, ip, sp, lr, pc}
d001d830:	83abf040 			; <UNDEFINED> instruction: 0x83abf040
d001d834:	769af506 	ldrvc	pc, [sl], r6, lsl #10
d001d838:	a922465a 	stmdbge	r2!, {r1, r3, r4, r6, r9, sl, lr}
d001d83c:	f00119a8 			; <UNDEFINED> instruction: 0xf00119a8
d001d840:	2800fdef 	stmdacs	r0, {r0, r1, r2, r3, r5, r6, r7, r8, sl, fp, ip, sp, lr, pc}
d001d844:	e3a0d0c8 	mov	sp, #200	; 0xc8
d001d848:	27e8f8df 	ubfxcs	pc, pc, #17, #9
d001d84c:	4628217b 			; <UNDEFINED> instruction: 0x4628217b
d001d850:	f7f5447a 			; <UNDEFINED> instruction: 0xf7f5447a
d001d854:	2800faf8 	stmdacs	r0, {r3, r4, r5, r6, r7, r9, fp, ip, sp, lr, pc}
d001d858:	af7bf43e 	svcge	0x007bf43e
d001d85c:	4974f505 	ldmdbmi	r4!, {r0, r2, r8, sl, ip, sp, lr, pc}^
d001d860:	3722f505 	strcc	pc, [r2, -r5, lsl #10]!
d001d864:	0801f04f 	stmdaeq	r1, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d001d868:	f8d94628 			; <UNDEFINED> instruction: 0xf8d94628
d001d86c:	f24b3098 	vqadd.s8	d19, d27, d8
d001d870:	f8845180 			; <UNDEFINED> instruction: 0xf8845180
d001d874:	f8c4812a 			; <UNDEFINED> instruction: 0xf8c4812a
d001d878:	f5053124 			; <UNDEFINED> instruction: 0xf5053124
d001d87c:	f8c73325 			; <UNDEFINED> instruction: 0xf8c73325
d001d880:	f8c3610c 			; <UNDEFINED> instruction: 0xf8c3610c
d001d884:	f8c3611c 			; <UNDEFINED> instruction: 0xf8c3611c
d001d888:	f8c36118 			; <UNDEFINED> instruction: 0xf8c36118
d001d88c:	f8876114 			; <UNDEFINED> instruction: 0xf8876114
d001d890:	e9c36112 	stmib	r3, {r1, r4, r8, sp, lr}^
d001d894:	f505664a 			; <UNDEFINED> instruction: 0xf505664a
d001d898:	f8c3332d 			; <UNDEFINED> instruction: 0xf8c3332d
d001d89c:	f5056178 			; <UNDEFINED> instruction: 0xf5056178
d001d8a0:	f8c33329 			; <UNDEFINED> instruction: 0xf8c33329
d001d8a4:	f8c36174 			; <UNDEFINED> instruction: 0xf8c36174
d001d8a8:	f8946130 			; <UNDEFINED> instruction: 0xf8946130
d001d8ac:	f887312b 			; <UNDEFINED> instruction: 0xf887312b
d001d8b0:	f8943110 			; <UNDEFINED> instruction: 0xf8943110
d001d8b4:	f887312e 			; <UNDEFINED> instruction: 0xf887312e
d001d8b8:	f7f73111 			; <UNDEFINED> instruction: 0xf7f73111
d001d8bc:	f8d9f9b1 			; <UNDEFINED> instruction: 0xf8d9f9b1
d001d8c0:	46313098 			; <UNDEFINED> instruction: 0x46313098
d001d8c4:	f7f79316 			; <UNDEFINED> instruction: 0xf7f79316
d001d8c8:	f44ff9ab 	vst2.32	{d31,d33}, [pc :128], fp
d001d8cc:	f7f7412f 			; <UNDEFINED> instruction: 0xf7f7412f
d001d8d0:	9b12f9a7 	blls	0xd04dbf74
d001d8d4:	f0402b04 			; <UNDEFINED> instruction: 0xf0402b04
d001d8d8:	2218808b 	andscs	r8, r8, #139	; 0x8b
d001d8dc:	a8364631 	ldmdage	r6!, {r0, r4, r5, r9, sl, lr}
d001d8e0:	fd80f001 	stc2	0, cr15, [r0, #4]
d001d8e4:	3750f8df 	smmlscc	r0, pc, r8, pc	; <UNPREDICTABLE>
d001d8e8:	9334447b 	teqls	r4, #2063597568	; 0x7b000000
d001d8ec:	93352314 	teqls	r5, #20, 6	; 0x50000000
d001d8f0:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d001d8f4:	230b9339 	movwcs	r9, #45881	; 0xb339
d001d8f8:	ab389304 	blge	0xd0e42510
d001d8fc:	e88dcb0f 	stm	sp, {r0, r1, r2, r3, r8, r9, fp, lr, pc}
d001d900:	ab34000f 	blge	0xd0d1d944
d001d904:	f7f6cb0f 			; <UNDEFINED> instruction: 0xf7f6cb0f
d001d908:	4632fb5d 			; <UNDEFINED> instruction: 0x4632fb5d
d001d90c:	f887b2c1 			; <UNDEFINED> instruction: 0xf887b2c1
d001d910:	46280112 			; <UNDEFINED> instruction: 0x46280112
d001d914:	fa33f7f7 	blx	0xd0d1b8f8
d001d918:	8048f8cd 	subhi	pc, r8, sp, asr #17
d001d91c:	21002214 	tstcs	r0, r4, lsl r2
d001d920:	2400a834 	strcs	sl, [r0], #-2100	; 0xfffff7cc
d001d924:	fd5ef001 	ldc2l	0, cr15, [lr, #-4]
d001d928:	af22ab20 	svcge	0x0022ab20
d001d92c:	0af0f10d 	beq	0xcfc59d68
d001d930:	930f461e 	movwls	r4, #63006	; 0xf61e
d001d934:	3704f8df 			; <UNDEFINED> instruction: 0x3704f8df
d001d938:	447b9411 	ldrbtmi	r9, [fp], #-1041	; 0xfffffbef
d001d93c:	45a39318 	strmi	r9, [r3, #792]!	; 0x318
d001d940:	f8dfd158 			; <UNDEFINED> instruction: 0xf8dfd158
d001d944:	240066fc 	strcs	r6, [r0], #-1788	; 0xfffff904
d001d948:	56f8f8df 	usatpl	pc, #24, pc, asr #17	; <UNPREDICTABLE>
d001d94c:	447d447e 	ldrbtmi	r4, [sp], #-1150	; 0xfffffb82
d001d950:	f04045a3 			; <UNDEFINED> instruction: 0xf04045a3
d001d954:	f7fd8117 			; <UNDEFINED> instruction: 0xf7fd8117
d001d958:	f8dffead 			; <UNDEFINED> instruction: 0xf8dffead
d001d95c:	447806ec 	ldrbtmi	r0, [r8], #-1772	; 0xfffff914
d001d960:	3322f500 	msrcc	CPSR_x, #0, 10
d001d964:	3110f893 			; <UNDEFINED> instruction: 0x3110f893
d001d968:	d0022b01 	andle	r2, r2, r1, lsl #22
d001d96c:	f7f72100 			; <UNDEFINED> instruction: 0xf7f72100
d001d970:	f8dff9b3 			; <UNDEFINED> instruction: 0xf8dff9b3
d001d974:	447806d8 	ldrbtmi	r0, [r8], #-1752	; 0xfffff928
d001d978:	4374f500 	cmnmi	r4, #0, 10	; <UNPREDICTABLE>
d001d97c:	8098f8d3 			; <UNDEFINED> instruction: 0x8098f8d3
d001d980:	3325f500 	msrcc	CPSR_sc, #0, 10
d001d984:	4118f8d3 			; <UNDEFINED> instruction: 0x4118f8d3
d001d988:	f0243401 			; <UNDEFINED> instruction: 0xf0243401
d001d98c:	b2a50401 	adclt	r0, r5, #16777216	; 0x1000000
d001d990:	4130f445 	teqmi	r0, r5, asr #8	; <UNPREDICTABLE>
d001d994:	f944f7f7 			; <UNDEFINED> instruction: 0xf944f7f7
d001d998:	5180f64b 	orrpl	pc, r0, fp, asr #12
d001d99c:	f940f7f7 			; <UNDEFINED> instruction: 0xf940f7f7
d001d9a0:	2b006d83 	blcs	0xd0038fb4
d001d9a4:	aed5f47e 	mrcge	4, 6, APSR_nzcv, cr5, cr14, {3}
d001d9a8:	36a4f8df 	ssatcc	pc, #5, pc, asr #17	; <UNPREDICTABLE>
d001d9ac:	4530f445 	ldrmi	pc, [r0, #-1093]!	; 0xfffffbbb
d001d9b0:	447b9a16 	ldrbtmi	r9, [fp], #-2582	; 0xfffff5ea
d001d9b4:	0580f045 	streq	pc, [r0, #69]	; 0x45
d001d9b8:	f882441a 			; <UNDEFINED> instruction: 0xf882441a
d001d9bc:	0a2d5040 	beq	0xd0b71ac4
d001d9c0:	5041f882 	subpl	pc, r1, r2, lsl #17
d001d9c4:	b1429a11 	cmplt	r2, r1, lsl sl
d001d9c8:	44133402 	ldrmi	r3, [r3], #-1026	; 0xfffffbfe
d001d9cc:	b2a400a4 	adclt	r0, r4, #164	; 0xa4
d001d9d0:	4040f883 	submi	pc, r0, r3, lsl #17
d001d9d4:	f8830a24 			; <UNDEFINED> instruction: 0xf8830a24
d001d9d8:	f8df4041 			; <UNDEFINED> instruction: 0xf8df4041
d001d9dc:	26004678 			; <UNDEFINED> instruction: 0x26004678
d001d9e0:	f504447c 			; <UNDEFINED> instruction: 0xf504447c
d001d9e4:	f504351e 			; <UNDEFINED> instruction: 0xf504351e
d001d9e8:	f5053722 			; <UNDEFINED> instruction: 0xf5053722
d001d9ec:	e1007586 	smlabb	r0, r6, r5, r7
d001d9f0:	e7939612 			; <UNDEFINED> instruction: 0xe7939612
d001d9f4:	2014f8da 			; <UNDEFINED> instruction: 0x2014f8da
d001d9f8:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d001d9fc:	d016429a 	mulsle	r6, sl, r2
d001da00:	3654f8df 			; <UNDEFINED> instruction: 0x3654f8df
d001da04:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d001da08:	f47e2a00 			; <UNDEFINED> instruction: 0xf47e2a00
d001da0c:	aa3caea2 	bge	0xd0f4949c
d001da10:	1444eb02 	strbne	lr, [r4], #-2818	; 0xfffff4fe
d001da14:	692068e5 	stmdbvs	r0!, {r0, r2, r5, r6, r7, fp, sp, lr}
d001da18:	7e2169e2 	vnmulvc.f16	s12, s3, s5	; <UNPREDICTABLE>
d001da1c:	463cf8df 			; <UNDEFINED> instruction: 0x463cf8df
d001da20:	e9c3447c 	stmib	r3, {r2, r3, r4, r5, r6, sl, lr}^
d001da24:	e9c34516 	stmib	r3, {r1, r2, r4, r8, sl, lr}^
d001da28:	f7ff0118 			; <UNDEFINED> instruction: 0xf7ff0118
d001da2c:	7832ba02 	ldmdavc	r2!, {r1, r9, fp, ip, sp, pc}
d001da30:	2a0d9614 	bcs	0xd0383288
d001da34:	783bd11e 	ldmdavc	fp!, {r1, r2, r3, r4, r8, ip, lr, pc}
d001da38:	711af44f 	tstvc	sl, pc, asr #8	; <UNPREDICTABLE>
d001da3c:	fb019818 	blx	0xd0083aa6
d001da40:	f5030303 			; <UNDEFINED> instruction: 0xf5030303
d001da44:	f8b333c9 			; <UNDEFINED> instruction: 0xf8b333c9
d001da48:	f1b99108 			; <UNDEFINED> instruction: 0xf1b99108
d001da4c:	d1130f00 	tstle	r3, r0, lsl #30
d001da50:	360cf8df 			; <UNDEFINED> instruction: 0x360cf8df
d001da54:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d001da58:	f47e2a00 			; <UNDEFINED> instruction: 0xf47e2a00
d001da5c:	aa3cae7a 	bge	0xd0f4944c
d001da60:	1444eb02 	strbne	lr, [r4], #-2818	; 0xfffff4fe
d001da64:	692068e5 	stmdbvs	r0!, {r0, r2, r5, r6, r7, fp, sp, lr}
d001da68:	7e2169e2 	vnmulvc.f16	s12, s3, s5	; <UNPREDICTABLE>
d001da6c:	45f4f8df 	ldrbmi	pc, [r4, #2271]!	; 0x8df	; <UNPREDICTABLE>
d001da70:	e7d6447c 			; <UNDEFINED> instruction: 0xe7d6447c
d001da74:	0901f04f 	stmdbeq	r1, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d001da78:	35ecf8df 	strbcc	pc, [ip, #2271]!	; 0x8df	; <UNPREDICTABLE>
d001da7c:	f503447b 			; <UNDEFINED> instruction: 0xf503447b
d001da80:	f8d33325 			; <UNDEFINED> instruction: 0xf8d33325
d001da84:	f1c33114 			; <UNDEFINED> instruction: 0xf1c33114
d001da88:	454b0340 	strbmi	r0, [fp, #-832]	; 0xfffffcc0
d001da8c:	ab64d3e0 	blge	0xd1952a14
d001da90:	eb039204 	bl	0xd01022a8
d001da94:	f1a31344 			; <UNDEFINED> instruction: 0xf1a31344
d001da98:	3b9005a0 	blcc	0xce41f120
d001da9c:	e88dcb0f 	stm	sp, {r0, r1, r2, r3, r8, r9, fp, lr, pc}
d001daa0:	e895000f 	ldm	r5, {r0, r1, r2, r3}
d001daa4:	f7f6000f 			; <UNDEFINED> instruction: 0xf7f6000f
d001daa8:	ab34fa8d 	blge	0xd0d5c4e4
d001daac:	f8439010 			; <UNDEFINED> instruction: 0xf8439010
d001dab0:	78330024 	ldmdavc	r3!, {r2, r5}
d001dab4:	020df1a3 	andeq	pc, sp, #-1073741784	; 0xc0000028
d001dab8:	d9012a01 	stmdble	r1, {r0, r9, fp, sp}
d001dabc:	d10b2b12 	tstle	fp, r2, lsl fp
d001dac0:	35a8f8df 	strcc	pc, [r8, #2271]!	; 0x8df
d001dac4:	99102230 	ldmdbls	r0, {r4, r5, r9, sp}
d001dac8:	fb02447b 	blx	0xd00aecbe
d001dacc:	783a3301 	ldmdavc	sl!, {r0, r8, r9, ip, sp}
d001dad0:	3322f503 	msrcc	CPSR_x, #12582912	; 0xc00000
d001dad4:	2136f883 	teqcs	r6, r3, lsl #17	; <UNPREDICTABLE>
d001dad8:	2594f8df 	ldrcs	pc, [r4, #2271]	; 0x8df
d001dadc:	447a2301 	ldrbtmi	r2, [sl], #-769	; 0xfffffcff
d001dae0:	3825f502 	stmdacc	r5!, {r1, r8, sl, ip, sp, lr, pc}
d001dae4:	e0139213 	ands	r9, r3, r3, lsl r2
d001dae8:	931c1c6a 	tstls	ip, #27136	; 0x6a00
d001daec:	21009b13 	tstcs	r0, r3, lsl fp
d001daf0:	2114f8c8 	tstcs	r4, r8, asr #17	; <UNPREDICTABLE>
d001daf4:	fb022230 	blx	0xd00a63be
d001daf8:	f5053505 			; <UNDEFINED> instruction: 0xf5053505
d001dafc:	f5053522 			; <UNDEFINED> instruction: 0xf5053522
d001db00:	f001708a 			; <UNDEFINED> instruction: 0xf001708a
d001db04:	9b1cfc6f 	blls	0xd075ccc8
d001db08:	3301220b 	movwcc	r2, #4619	; 0x120b
d001db0c:	2135f885 	teqcs	r5, r5, lsl #17	; <UNPREDICTABLE>
d001db10:	f8d84599 			; <UNDEFINED> instruction: 0xf8d84599
d001db14:	d1e75114 	mvnle	r5, r4, lsl r1
d001db18:	3118f8d8 			; <UNDEFINED> instruction: 0x3118f8d8
d001db1c:	9b1242ab 	blls	0xd04ae5d0
d001db20:	f8c8bf38 			; <UNDEFINED> instruction: 0xf8c8bf38
d001db24:	2c045118 	stfcss	f5, [r4], {24}
d001db28:	0503eb04 	streq	lr, [r3, #-2820]	; 0xfffff4fc
d001db2c:	f64fd10c 			; <UNDEFINED> instruction: 0xf64fd10c
d001db30:	ee1801d7 	mrc	1, 0, r0, cr8, cr7, {6}
d001db34:	f7f70a10 			; <UNDEFINED> instruction: 0xf7f70a10
d001db38:	9b1bf873 	blls	0xd071bd0c
d001db3c:	21002500 	tstcs	r0, r0, lsl #10
d001db40:	9311681b 	tstls	r1, #1769472	; 0x1b0000
d001db44:	f86cf7f7 			; <UNDEFINED> instruction: 0xf86cf7f7
d001db48:	36019b14 			; <UNDEFINED> instruction: 0x36019b14
d001db4c:	2b05781b 	blcs	0xd017bbc0
d001db50:	b2a9d10c 	adclt	sp, r9, #12, 2
d001db54:	051cf8df 	ldreq	pc, [ip, #-2271]	; 0xfffff721
d001db58:	01c1ea41 	biceq	lr, r1, r1, asr #20
d001db5c:	f4414478 	vst3.16	{d20-d22}, [r1 :256], r8
d001db60:	f0414132 			; <UNDEFINED> instruction: 0xf0414132
d001db64:	b28901c0 	addlt	r0, r9, #192, 2	; 0x30
d001db68:	f85af7f7 			; <UNDEFINED> instruction: 0xf85af7f7
d001db6c:	0508f8df 	streq	pc, [r8, #-2271]	; 0xfffff721
d001db70:	9910462a 	ldmdbls	r0, {r1, r3, r5, r9, sl, lr}
d001db74:	44783401 	ldrbtmi	r3, [r8], #-1025	; 0xfffffbff
d001db78:	f10a3701 			; <UNDEFINED> instruction: 0xf10a3701
d001db7c:	f7f70a20 			; <UNDEFINED> instruction: 0xf7f70a20
d001db80:	e6dcf8fe 			; <UNDEFINED> instruction: 0xe6dcf8fe
d001db84:	f8129a0f 			; <UNDEFINED> instruction: 0xf8129a0f
d001db88:	2b0d3b01 	blcs	0xd036c794
d001db8c:	d001920f 	andle	r9, r1, pc, lsl #4
d001db90:	e6dd3401 	ldrb	r3, [sp], r1, lsl #8
d001db94:	f44fab34 			; <UNDEFINED> instruction: 0xf44fab34
d001db98:	f04f721a 			; <UNDEFINED> instruction: 0xf04f721a
d001db9c:	46300900 	ldrtmi	r0, [r0], -r0, lsl #18
d001dba0:	7024f853 	eorvc	pc, r4, r3, asr r8	; <UNPREDICTABLE>
d001dba4:	5ce3ab22 	vstmiapl	r3!, {d26-<overflow reg d42>}
d001dba8:	fb024639 	blx	0xd00af496
d001dbac:	22016303 	andcs	r6, r1, #201326592	; 0xc000000
d001dbb0:	33c9f503 	biccc	pc, r9, #12582912	; 0xc00000
d001dbb4:	8108f8b3 			; <UNDEFINED> instruction: 0x8108f8b3
d001dbb8:	f8c8f7f7 			; <UNDEFINED> instruction: 0xf8c8f7f7
d001dbbc:	d9e745c8 	stmible	r7!, {r3, r6, r7, r8, sl, lr}^
d001dbc0:	f64f4628 			; <UNDEFINED> instruction: 0xf64f4628
d001dbc4:	f7f701d1 			; <UNDEFINED> instruction: 0xf7f701d1
d001dbc8:	ea4ff82b 	b	0xd141bc7c
d001dbcc:	b2890189 	addlt	r0, r9, #1073741858	; 0x40000022
d001dbd0:	f826f7f7 			; <UNDEFINED> instruction: 0xf826f7f7
d001dbd4:	0109eb07 	tsteq	r9, r7, lsl #22
d001dbd8:	f1092200 			; <UNDEFINED> instruction: 0xf1092200
d001dbdc:	f7f70901 			; <UNDEFINED> instruction: 0xf7f70901
d001dbe0:	e7ebf8ce 	strb	pc, [fp, lr, asr #17]!	; <UNPREDICTABLE>
d001dbe4:	23003601 	movwcs	r3, #1537	; 0x601
d001dbe8:	f8554642 			; <UNDEFINED> instruction: 0xf8554642
d001dbec:	f7f81b04 			; <UNDEFINED> instruction: 0xf7f81b04
d001dbf0:	f8d7fa5d 			; <UNDEFINED> instruction: 0xf8d7fa5d
d001dbf4:	6da0310c 	stfvss	f3, [r0, #48]!	; 0x30
d001dbf8:	d3f3429e 	mvnsle	r4, #-536870903	; 0xe0000009
d001dbfc:	bda9f7fe 	stclt	7, cr15, [r9, #1016]!	; 0x3f8
d001dc00:	f47e2b00 			; <UNDEFINED> instruction: 0xf47e2b00
d001dc04:	f8dfacc4 			; <UNDEFINED> instruction: 0xf8dfacc4
d001dc08:	22041474 	andcs	r1, r4, #116, 8	; 0x74000000
d001dc0c:	44794620 	ldrbtmi	r4, [r9], #-1568	; 0xfffff9e0
d001dc10:	fdfef7f2 	ldc2l	7, cr15, [lr, #968]!	; 0x3c8
d001dc14:	db0e2800 	blle	0xd03a7c1c
d001dc18:	fb032338 	blx	0xd00e6902
d001dc1c:	f5044400 			; <UNDEFINED> instruction: 0xf5044400
d001dc20:	f8943400 			; <UNDEFINED> instruction: 0xf8943400
d001dc24:	b133312a 	teqlt	r3, sl, lsr #2
d001dc28:	3128f894 	msrcc	CPSR_f, r4	; <illegal shifter operand>
d001dc2c:	f894b16b 			; <UNDEFINED> instruction: 0xf894b16b
d001dc30:	2b043130 	blcs	0xd012a0f8
d001dc34:	f8dfd009 			; <UNDEFINED> instruction: 0xf8dfd009
d001dc38:	f8df1448 			; <UNDEFINED> instruction: 0xf8df1448
d001dc3c:	44790448 	ldrbtmi	r0, [r9], #-1096	; 0xfffffbb8
d001dc40:	f7f24478 			; <UNDEFINED> instruction: 0xf7f24478
d001dc44:	f7fefab1 			; <UNDEFINED> instruction: 0xf7fefab1
d001dc48:	f8dfbca2 			; <UNDEFINED> instruction: 0xf8dfbca2
d001dc4c:	2338443c 	teqcs	r8, #60, 8	; 0x3c000000
d001dc50:	fb03447c 	blx	0xd00eee4a
d001dc54:	23004000 	movwcs	r4, #0
d001dc58:	3000f500 	andcc	pc, r0, r0, lsl #10
d001dc5c:	f8d04619 			; <UNDEFINED> instruction: 0xf8d04619
d001dc60:	6da02124 	stfvss	f2, [r0, #144]!	; 0x90
d001dc64:	fa22f7f8 	blx	0xd08dbc4c
d001dc68:	bc91f7fe 	ldclt	7, cr15, [r1], {254}	; 0xfe
d001dc6c:	462f2500 	strtmi	r2, [pc], -r0, lsl #10
d001dc70:	bcb9f7fe 	ldclt	7, cr15, [r9], #1016	; 0x3f8
d001dc74:	683088b3 	ldmdavs	r0!, {r0, r1, r4, r5, r7, fp, pc}
d001dc78:	b2921cda 	addslt	r1, r2, #55808	; 0xda00
d001dc7c:	d8092a01 	stmdale	r9, {r0, r9, fp, sp}
d001dc80:	71fef64f 	mvnsvc	pc, pc, asr #12
d001dc84:	428b2201 	addmi	r2, fp, #268435456	; 0x10000000
d001dc88:	4639bf0c 	ldrtmi	fp, [r9], -ip, lsl #30
d001dc8c:	f7f84629 			; <UNDEFINED> instruction: 0xf7f84629
d001dc90:	e016f9d9 			; <UNDEFINED> instruction: 0xe016f9d9
d001dc94:	43592138 	cmpmi	r9, #56, 2
d001dc98:	f5031863 			; <UNDEFINED> instruction: 0xf5031863
d001dc9c:	f8933300 			; <UNDEFINED> instruction: 0xf8933300
d001dca0:	b99a212a 	ldmiblt	sl, {r1, r3, r5, r8, sp}
d001dca4:	3100f501 	tstcc	r0, r1, lsl #10	; <UNPREDICTABLE>
d001dca8:	7182f501 	orrvc	pc, r2, r1, lsl #10
d001dcac:	f8d14421 			; <UNDEFINED> instruction: 0xf8d14421
d001dcb0:	6908c00c 	stmdbvs	r8, {r2, r3, lr, pc}
d001dcb4:	7e0a69cb 	vmlsvc.f16	s12, s21, s22	; <UNPREDICTABLE>
d001dcb8:	e9c466a3 	stmib	r4, {r0, r1, r5, r7, r9, sl, sp, lr}^
d001dcbc:	e9c49c16 	stmib	r4, {r1, r2, r4, sl, fp, ip, pc}^
d001dcc0:	f10a0218 			; <UNDEFINED> instruction: 0xf10a0218
d001dcc4:	36080a01 	strcc	r0, [r8], -r1, lsl #20
d001dcc8:	bc9af7fe 	ldclt	7, cr15, [sl], {254}	; 0xfe
d001dccc:	f8d32201 			; <UNDEFINED> instruction: 0xf8d32201
d001dcd0:	e7dc1124 	ldrb	r1, [ip, r4, lsr #2]
d001dcd4:	f7fe4656 			; <UNDEFINED> instruction: 0xf7fe4656
d001dcd8:	f898bcb1 			; <UNDEFINED> instruction: 0xf898bcb1
d001dcdc:	f8d82006 			; <UNDEFINED> instruction: 0xf8d82006
d001dce0:	f8b80000 			; <UNDEFINED> instruction: 0xf8b80000
d001dce4:	bb5ac004 	bllt	0xd16cdcfc
d001dce8:	3000f8db 	ldrdcc	pc, [r0], -fp
d001dcec:	f1004463 			; <UNDEFINED> instruction: 0xf1004463
d001dcf0:	f102050c 			; <UNDEFINED> instruction: 0xf102050c
d001dcf4:	f24f3cff 	vfma.f32	<illegal reg q9.5>, <illegal reg q15.5>, <illegal reg q15.5>
d001dcf8:	90122140 	andsls	r2, r2, r0, asr #2
d001dcfc:	0503f025 	streq	pc, [r3, #-37]	; 0xffffffdb
d001dd00:	0200f1dc 	andeq	pc, r0, #220, 2	; 0x37
d001dd04:	0901f109 	stmdbeq	r1, {r0, r3, r8, ip, sp, lr, pc}
d001dd08:	0808f108 	stmdaeq	r8, {r3, r8, ip, sp, lr, pc}
d001dd0c:	0505eba3 	streq	lr, [r5, #-2979]	; 0xfffff45d
d001dd10:	020ceb42 	andeq	lr, ip, #67584	; 0x10800
d001dd14:	9213b2ab 	andsls	fp, r3, #-1342177270	; 0xb000000a
d001dd18:	ff52f7f6 			; <UNDEFINED> instruction: 0xff52f7f6
d001dd1c:	0c2b9812 	stceq	8, cr9, [fp], #-72	; 0xffffffb8
d001dd20:	f24f9a13 	vpmin.s8	d25, d15, d3
d001dd24:	300421c0 	andcc	r2, r4, r0, asr #3
d001dd28:	ff4af7f6 			; <UNDEFINED> instruction: 0xff4af7f6
d001dd2c:	35baf504 	ldrcc	pc, [sl, #1284]!	; 0x504
d001dd30:	f8d56da3 			; <UNDEFINED> instruction: 0xf8d56da3
d001dd34:	459120a0 	ldrmi	r2, [r1, #160]	; 0xa0
d001dd38:	2b00d254 	blcs	0xd0052690
d001dd3c:	e03ed0cd 	eors	sp, lr, sp, asr #1
d001dd40:	f04f2a01 			; <UNDEFINED> instruction: 0xf04f2a01
d001dd44:	d1220338 			; <UNDEFINED> instruction: 0xd1220338
d001dd48:	430cfb03 	movwmi	pc, #51971	; 0xcb03	; <UNPREDICTABLE>
d001dd4c:	31baf503 			; <UNDEFINED> instruction: 0x31baf503
d001dd50:	30cff891 	smullcc	pc, pc, r1, r8	; <UNPREDICTABLE>
d001dd54:	f891b9cb 			; <UNDEFINED> instruction: 0xf891b9cb
d001dd58:	3b0730cc 	blcc	0xd01ea090
d001dd5c:	2b0ab2db 	blcs	0xd02ca8d0
d001dd60:	f240d813 	vtst.8	d29, d0, d3
d001dd64:	fa215103 	blx	0xd0872178
d001dd68:	f013f303 			; <UNDEFINED> instruction: 0xf013f303
d001dd6c:	9b100f01 	blls	0xd0421978
d001dd70:	463dbf0c 	ldrtmi	fp, [sp], -ip, lsl #30
d001dd74:	2338461d 	teqcs	r8, #30408704	; 0x1d00000
d001dd78:	fb039911 	blx	0xd01041c6
d001dd7c:	f503130c 			; <UNDEFINED> instruction: 0xf503130c
d001dd80:	f8d333ba 			; <UNDEFINED> instruction: 0xf8d333ba
d001dd84:	442b30c8 	strtmi	r3, [fp], #-200	; 0xffffff38
d001dd88:	463de7b1 			; <UNDEFINED> instruction: 0x463de7b1
d001dd8c:	fb03e7f3 	blx	0xd0117d62
d001dd90:	18e1f30c 	stmiane	r1!, {r2, r3, r8, r9, ip, sp, lr, pc}^
d001dd94:	3100f501 	tstcc	r0, r1, lsl #10	; <UNPREDICTABLE>
d001dd98:	512af891 	msrpl	CPSR_fx, r1	; <illegal shifter operand>
d001dd9c:	f503b9d5 			; <UNDEFINED> instruction: 0xf503b9d5
d001dda0:	4dba3300 	ldcmi	3, cr3, [sl]
d001dda4:	7382f503 	orrvc	pc, r2, #12582912	; 0xc00000
d001dda8:	4423447d 	strtmi	r4, [r3], #-1149	; 0xfffffb83
d001ddac:	691968d8 	ldmdbvs	r9, {r3, r4, r6, r7, fp, sp, lr}
d001ddb0:	7e1b69da 			; <UNDEFINED> instruction: 0x7e1b69da
d001ddb4:	e9c466a2 	stmib	r4, {r1, r5, r7, r9, sl, sp, lr}^
d001ddb8:	e9c45016 	stmib	r4, {r1, r2, r4, ip, lr}^
d001ddbc:	4cb41318 	ldcmi	3, cr1, [r4], #96	; 0x60
d001ddc0:	447c9d72 	ldrbtmi	r9, [ip], #-3442	; 0xfffff28e
d001ddc4:	cc0f3458 	cfstrsgt	mvf3, [pc], {88}	; 0x58
d001ddc8:	6823c50f 	stmdavs	r3!, {r0, r1, r2, r3, r8, sl, lr, pc}
d001ddcc:	602b2400 	eorvs	r2, fp, r0, lsl #8
d001ddd0:	bc6cf7fe 	stcllt	7, cr15, [ip], #-1016	; 0xfffffc08
d001ddd4:	3124f8d1 	ldrdcc	pc, [r4, -r1]!
d001ddd8:	5100f44f 	tstpl	r0, pc, asr #8	; <UNPREDICTABLE>
d001dddc:	0301f043 	movweq	pc, #4163	; 0x1043	; <UNPREDICTABLE>
d001dde0:	e784910f 	str	r9, [r4, pc, lsl #2]
d001dde4:	2b009311 	blcs	0xd0042a30
d001dde8:	f8dfd1e9 			; <UNDEFINED> instruction: 0xf8dfd1e9
d001ddec:	f24f82a8 	vhsub.s8	d24, d31, d24
d001ddf0:	f5044298 			; <UNDEFINED> instruction: 0xf5044298
d001ddf4:	f8df4174 			; <UNDEFINED> instruction: 0xf8df4174
d001ddf8:	44f8b2a0 	ldrbtmi	fp, [r8], #672	; 0x2a0
d001ddfc:	f24f58a0 	vadd.i8	d21, d31, d16
d001de00:	31a0429c 	lslcc	r4, ip	; <illegal shifter operand>
d001de04:	0840f108 	stmdaeq	r0, {r3, r8, ip, sp, lr, pc}^
d001de08:	58a244fb 	stmiapl	r2!, {r0, r1, r3, r4, r5, r6, r7, sl, lr}
d001de0c:	44401cf4 	strbmi	r1, [r0], #-3316	; 0xfffff30c
d001de10:	f00135c4 			; <UNDEFINED> instruction: 0xf00135c4
d001de14:	f024faf5 			; <UNDEFINED> instruction: 0xf024faf5
d001de18:	9b110403 	blls	0xd045ee2c
d001de1c:	000aeb08 	andeq	lr, sl, r8, lsl #22
d001de20:	020aeba4 	andeq	lr, sl, #164, 22	; 0x29000
d001de24:	0b40f10b 	bleq	0xd105a258
d001de28:	f0014619 			; <UNDEFINED> instruction: 0xf0014619
d001de2c:	9b11fadb 	blls	0xd049c9a0
d001de30:	f8df4698 			; <UNDEFINED> instruction: 0xf8df4698
d001de34:	44faa268 	ldrbtmi	sl, [sl], #616	; 0x268
d001de38:	33c8f50a 	biccc	pc, r8, #41943040	; 0x2800000
d001de3c:	30a4f8d3 	ldrdcc	pc, [r4], r3	; <UNPREDICTABLE>
d001de40:	d3414598 	movtle	r4, #5528	; 0x1598
d001de44:	ad3c2740 	ldcge	7, cr2, [ip, #-256]!	; 0xffffff00
d001de48:	f50a2100 			; <UNDEFINED> instruction: 0xf50a2100
d001de4c:	463a3af8 			; <UNDEFINED> instruction: 0x463a3af8
d001de50:	f0014628 			; <UNDEFINED> instruction: 0xf0014628
d001de54:	4992fac7 	ldmibmi	r2, {r0, r1, r2, r6, r7, r9, fp, ip, sp, lr, pc}
d001de58:	46282208 	strtmi	r2, [r8], -r8, lsl #4
d001de5c:	443c4479 	ldrtmi	r4, [ip], #-1145	; 0xfffffb87
d001de60:	facef001 	blx	0xcf3d9e6c
d001de64:	9a102302 	bls	0xd0426a74
d001de68:	e9cd4631 	stmib	sp, {r0, r4, r5, r9, sl, lr}^
d001de6c:	f8da373e 			; <UNDEFINED> instruction: 0xf8da373e
d001de70:	4f8c30fc 	svcmi	0x008c30fc
d001de74:	447f331f 	ldrbtmi	r3, [pc], #-799	; 0xd001de7c
d001de78:	9a0f4413 	bls	0xd03eeecc
d001de7c:	0040f107 	subeq	pc, r0, r7, lsl #2
d001de80:	031ff023 	tsteq	pc, #35	; 0x23	; <UNPREDICTABLE>
d001de84:	44139249 	ldrmi	r9, [r3], #-585	; 0xfffffdb7
d001de88:	23019342 	movwcs	r9, #4930	; 0x1342
d001de8c:	4b579343 	blmi	0xd1602ba0
d001de90:	3444e9cd 	strbcc	lr, [r4], #-2509	; 0xfffff633
d001de94:	93472320 	movtls	r2, #29472	; 0x7320
d001de98:	bf181e13 	svclt	0x00181e13
d001de9c:	e9cd2301 	stmib	sp, {r0, r8, r9, sp}^
d001dea0:	934a4640 	movtls	r4, #42560	; 0xa640
d001dea4:	f7f2463e 			; <UNDEFINED> instruction: 0xf7f2463e
d001dea8:	904bf967 	subls	pc, fp, r7, ror #18
d001deac:	c60fcd0f 	strgt	ip, [pc], -pc, lsl #26
d001deb0:	c60fcd0f 	strgt	ip, [pc], -pc, lsl #26
d001deb4:	c60fcd0f 	strgt	ip, [pc], -pc, lsl #26
d001deb8:	000fe895 	muleq	pc, r5, r8	; <UNPREDICTABLE>
d001debc:	000fe886 	andeq	lr, pc, r6, lsl #17
d001dec0:	601f9b71 	andsvs	r9, pc, r1, ror fp	; <UNPREDICTABLE>
d001dec4:	bbf2f7fe 	bllt	0xcfcdbec4
d001dec8:	b3537aeb 	cmplt	r3, #962560	; 0xeb000
d001decc:	f04f4b76 			; <UNDEFINED> instruction: 0xf04f4b76
d001ded0:	447b0a00 	ldrbtmi	r0, [fp], #-2560	; 0xfffff600
d001ded4:	89eae014 	stmibhi	sl!, {r2, r4, sp, lr, pc}^
d001ded8:	44526868 	ldrbmi	r6, [r2], #-2152	; 0xfffff798
d001dedc:	f5024438 			; <UNDEFINED> instruction: 0xf5024438
d001dee0:	324042f8 	subcc	r4, r0, #248, 4	; 0x8000000f
d001dee4:	1022f853 	eorne	pc, r2, r3, asr r8	; <UNPREDICTABLE>
d001dee8:	913c7a2a 	teqls	ip, sl, lsr #20
d001deec:	d10e2a07 	tstle	lr, r7, lsl #20
d001def0:	447a4a6e 	ldrbtmi	r4, [sl], #-2670	; 0xfffff592
d001def4:	44104452 	ldrmi	r4, [r0], #-1106	; 0xfffffbae
d001def8:	1040f880 	subne	pc, r0, r0, lsl #17
d001defc:	0a01f10a 	beq	0xd009a32c
d001df00:	45928a2a 	ldrmi	r8, [r2, #2602]	; 0xa2a
d001df04:	f108d3e7 			; <UNDEFINED> instruction: 0xf108d3e7
d001df08:	35380801 	ldrcc	r0, [r8, #-2049]!	; 0xfffff7ff
d001df0c:	eb00e791 	bl	0xd0057d58
d001df10:	2204008a 	andcs	r0, r4, #138	; 0x8a
d001df14:	9311a93c 	tstls	r1, #60, 18	; 0xf0000
d001df18:	f0014458 			; <UNDEFINED> instruction: 0xf0014458
d001df1c:	9b11fa71 	blls	0xd049c8e8
d001df20:	7a2be7ec 	bvc	0xd0b17ed8
d001df24:	b2db3b07 	sbcslt	r3, fp, #7168	; 0x1c00
d001df28:	d8052b0a 	stmdale	r5, {r1, r3, r8, r9, fp, sp}
d001df2c:	5203f240 	andpl	pc, r3, #64, 4
d001df30:	f303fa22 	vpmax.u8	d15, d3, d18
d001df34:	d4e607d8 	strbtle	r0, [r6], #2008	; 0x7d8
d001df38:	22044b5d 	andcs	r4, r4, #95232	; 0x17400
d001df3c:	46296868 	strtmi	r6, [r9], -r8, ror #16
d001df40:	4438447b 	ldrtmi	r4, [r8], #-1147	; 0xfffffb85
d001df44:	44183340 	ldrmi	r3, [r8], #-832	; 0xfffffcc0
d001df48:	fa5af001 	blx	0xd16d9f54
d001df4c:	2c00e7db 	stccs	7, cr14, [r0], {219}	; 0xdb
d001df50:	a91ef43f 	ldmdbge	lr, {r0, r1, r2, r3, r4, r5, sl, ip, sp, lr, pc}
d001df54:	447b4b57 	ldrbtmi	r4, [fp], #-2903	; 0xfffff4a9
d001df58:	2a006d9a 	bcs	0xd00395c8
d001df5c:	abf9f47e 	blge	0xcfe9b15c
d001df60:	447a4a55 	ldrbtmi	r4, [sl], #-2645	; 0xfffff5ab
d001df64:	bf1bf7fe 	svclt	0x001bf7fe
d001df68:	23384d54 	teqcs	r8, #84, 26	; 0x1500
d001df6c:	fb03447d 	blx	0xd00ef16a
d001df70:	f5035304 			; <UNDEFINED> instruction: 0xf5035304
d001df74:	f8933300 			; <UNDEFINED> instruction: 0xf8933300
d001df78:	45932128 	ldrmi	r2, [r3, #296]	; 0x128
d001df7c:	f893d105 			; <UNDEFINED> instruction: 0xf893d105
d001df80:	9912212b 	ldmdbls	r2, {r0, r1, r3, r5, r8, sp}
d001df84:	f43f428a 			; <UNDEFINED> instruction: 0xf43f428a
d001df88:	4b4dac42 	blmi	0xd1389098
d001df8c:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d001df90:	f47e2a00 			; <UNDEFINED> instruction: 0xf47e2a00
d001df94:	4a4babde 	bmi	0xd1308f14
d001df98:	f7fe447a 			; <UNDEFINED> instruction: 0xf7fe447a
d001df9c:	4d4abf00 	stclmi	15, cr11, [sl, #-0]
d001dfa0:	f505447d 			; <UNDEFINED> instruction: 0xf505447d
d001dfa4:	f8d3330e 			; <UNDEFINED> instruction: 0xf8d3330e
d001dfa8:	f5b44104 			; <UNDEFINED> instruction: 0xf5b44104
d001dfac:	f47f7f80 			; <UNDEFINED> instruction: 0xf47f7f80
d001dfb0:	6dababc5 			; <UNDEFINED> instruction: 0x6dababc5
d001dfb4:	f47e2b00 			; <UNDEFINED> instruction: 0xf47e2b00
d001dfb8:	4b44abcc 	blmi	0xd1148ef0
d001dfbc:	f7fe447b 			; <UNDEFINED> instruction: 0xf7fe447b
d001dfc0:	4b43bed9 	blmi	0xd110db2c
d001dfc4:	447b2401 	ldrbtmi	r2, [fp], #-1025	; 0xfffffbff
d001dfc8:	3300f503 	movwcc	pc, #1283	; 0x503	; <UNPREDICTABLE>
d001dfcc:	2100f8d3 	ldrdcs	pc, [r0, -r3]
d001dfd0:	f8c34432 			; <UNDEFINED> instruction: 0xf8c34432
d001dfd4:	f7fe2100 			; <UNDEFINED> instruction: 0xf7fe2100
d001dfd8:	9b12bf55 	blls	0xd04cdd34
d001dfdc:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001dfe0:	2d00a8ce 	stccs	8, cr10, [r0, #-824]	; 0xfffffcc8
d001dfe4:	f7ffd1b6 			; <UNDEFINED> instruction: 0xf7ffd1b6
d001dfe8:	bf00b8c3 	svclt	0x0000b8c3
d001dfec:	d0010000 	andle	r0, r1, r0
d001dff0:	ffffc9f9 			; <UNDEFINED> instruction: 0xffffc9f9
d001dff4:	ffff61a6 			; <UNDEFINED> instruction: 0xffff61a6
d001dff8:	ffffebfb 			; <UNDEFINED> instruction: 0xffffebfb
d001dffc:	ffffebf7 			; <UNDEFINED> instruction: 0xffffebf7
d001e000:	00005e08 	andeq	r5, r0, r8, lsl #28
d001e004:	ffffec10 			; <UNDEFINED> instruction: 0xffffec10
d001e008:	ffffec1d 			; <UNDEFINED> instruction: 0xffffec1d
d001e00c:	ffffec1d 			; <UNDEFINED> instruction: 0xffffec1d
d001e010:	ffffec27 			; <UNDEFINED> instruction: 0xffffec27
d001e014:	00005da6 	andeq	r5, r0, r6, lsr #27
d001e018:	00005d90 	muleq	r0, r0, sp
d001e01c:	00005d3c 	andeq	r5, r0, ip, lsr sp
d001e020:	ffffec2c 			; <UNDEFINED> instruction: 0xffffec2c
d001e024:	00005cfa 	strdeq	r5, [r0], -sl
d001e028:	ffffebf3 			; <UNDEFINED> instruction: 0xffffebf3
d001e02c:	00005c3e 	andeq	r5, r0, lr, lsr ip
d001e030:	ffffebb3 			; <UNDEFINED> instruction: 0xffffebb3
d001e034:	ffffeb84 			; <UNDEFINED> instruction: 0xffffeb84
d001e038:	ffffeb0c 			; <UNDEFINED> instruction: 0xffffeb0c
d001e03c:	00005ae2 	andeq	r5, r0, r2, ror #21
d001e040:	00005ad0 	ldrdeq	r5, [r0], -r0
d001e044:	00005ace 	andeq	r5, r0, lr, asr #21
d001e048:	00005abe 			; <UNDEFINED> instruction: 0x00005abe
d001e04c:	00005aa6 	andeq	r5, r0, r6, lsr #21
d001e050:	00030fea 	andeq	r0, r3, sl, ror #31
d001e054:	00005a3c 	andeq	r5, r0, ip, lsr sl
d001e058:	00005a18 	andeq	r5, r0, r8, lsl sl
d001e05c:	ffffe9e9 			; <UNDEFINED> instruction: 0xffffe9e9
d001e060:	000059c8 	andeq	r5, r0, r8, asr #19
d001e064:	ffffe9c5 			; <UNDEFINED> instruction: 0xffffe9c5
d001e068:	000059a0 	andeq	r5, r0, r0, lsr #19
d001e06c:	00005954 	andeq	r5, r0, r4, asr r9
d001e070:	0000593e 	andeq	r5, r0, lr, lsr r9
d001e074:	000058c0 	andeq	r5, r0, r0, asr #17
d001e078:	000058a6 	andeq	r5, r0, r6, lsr #17
d001e07c:	ffffe528 			; <UNDEFINED> instruction: 0xffffe528
d001e080:	ffffe828 			; <UNDEFINED> instruction: 0xffffe828
d001e084:	000057dc 	ldrdeq	r5, [r0], -ip
d001e088:	000057cc 	andeq	r5, r0, ip, asr #15
d001e08c:	ffffe73d 			; <UNDEFINED> instruction: 0xffffe73d
d001e090:	0000565a 	andeq	r5, r0, sl, asr r6
d001e094:	00030ba2 	andeq	r0, r3, r2, lsr #23
d001e098:	00030b94 	muleq	r3, r4, fp
d001e09c:	000055e6 	andeq	r5, r0, r6, ror #11
d001e0a0:	000002d4 	ldrdeq	r0, [r0], -r4
d001e0a4:	00030b26 	andeq	r0, r3, r6, lsr #22
d001e0a8:	0000554a 	andeq	r5, r0, sl, asr #10
d001e0ac:	00030aaa 	andeq	r0, r3, sl, lsr #21
d001e0b0:	00030a5c 	andeq	r0, r3, ip, asr sl
d001e0b4:	000054c6 	andeq	r5, r0, r6, asr #9
d001e0b8:	ffffe163 			; <UNDEFINED> instruction: 0xffffe163
d001e0bc:	000054b0 			; <UNDEFINED> instruction: 0x000054b0
d001e0c0:	00005490 	muleq	r0, r0, r4
d001e0c4:	ffffe3f3 			; <UNDEFINED> instruction: 0xffffe3f3
d001e0c8:	0000547c 	andeq	r5, r0, ip, ror r4
d001e0cc:	ffffe3bc 			; <UNDEFINED> instruction: 0xffffe3bc
d001e0d0:	00005456 	andeq	r5, r0, r6, asr r4

Disassembly of section .text.sidc_compile_project:

d001e0d4 <.text.sidc_compile_project>:
d001e0d4:	43f7e92d 	mvnsmi	lr, #737280	; 0xb4000
d001e0d8:	802cf8dd 	ldrdhi	pc, [ip], -sp	; <UNPREDICTABLE>
d001e0dc:	9c0c460f 	stcls	6, cr4, [ip], {15}
d001e0e0:	46052100 	strmi	r2, [r5], -r0, lsl #2
d001e0e4:	46204616 			; <UNDEFINED> instruction: 0x46204616
d001e0e8:	f8c82214 			; <UNDEFINED> instruction: 0xf8c82214
d001e0ec:	f8dd1000 			; <UNDEFINED> instruction: 0xf8dd1000
d001e0f0:	93019028 	movwls	r9, #4136	; 0x1028
d001e0f4:	f976f001 			; <UNDEFINED> instruction: 0xf976f001
d001e0f8:	1e72b185 	expned	f3, f5
d001e0fc:	2a0f9b01 	bcs	0xd0404d08
d001e100:	4632d80c 	ldrtmi	sp, [r2], -ip, lsl #16
d001e104:	46284639 			; <UNDEFINED> instruction: 0x46284639
d001e108:	f8cd940c 			; <UNDEFINED> instruction: 0xf8cd940c
d001e10c:	f8cd802c 			; <UNDEFINED> instruction: 0xf8cd802c
d001e110:	b0039028 	andlt	r9, r3, r8, lsr #32
d001e114:	43f0e8bd 	mvnsmi	lr, #12386304	; 0xbd0000
d001e118:	b9faf7fe 	ldmiblt	sl!, {r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}^
d001e11c:	447d4d04 	ldrbtmi	r4, [sp], #-3332	; 0xfffff2fc
d001e120:	c40fcd0f 	strgt	ip, [pc], #-3343	; 0xd001e128
d001e124:	2000682b 	andcs	r6, r0, fp, lsr #16
d001e128:	b0036023 	andlt	r6, r3, r3, lsr #32
d001e12c:	83f0e8bd 	mvnshi	lr, #12386304	; 0xbd0000
d001e130:	00002b7a 	andeq	r2, r0, sl, ror fp

Disassembly of section .text.memset:

d001f3e4 <.text.memset>:
d001f3e4:	b2c9b15a 	sbclt	fp, r9, #-2147483626	; 0x80000016
d001f3e8:	b4104603 	ldrlt	r4, [r0], #-1539	; 0xfffff9fd
d001f3ec:	461a1884 	ldrmi	r1, [sl], -r4, lsl #17
d001f3f0:	42a33301 	adcmi	r3, r3, #67108864	; 0x4000000
d001f3f4:	d1fa7011 	mvnsle	r7, r1, lsl r0
d001f3f8:	4b04f85d 	blmi	0xd015d574
d001f3fc:	47704770 			; <UNDEFINED> instruction: 0x47704770

Disassembly of section .text.memcpy:

d001f400 <.text.memcpy>:
d001f400:	4603b162 	strmi	fp, [r3], -r2, ror #2
d001f404:	1885b430 	stmne	r5, {r4, r5, sl, ip, sp, pc}
d001f408:	461c780a 	ldrmi	r7, [ip], -sl, lsl #16
d001f40c:	31013301 	tstcc	r1, r1, lsl #6
d001f410:	42abb2d2 	adcmi	fp, fp, #536870925	; 0x2000000d
d001f414:	d1f77022 	mvnsle	r7, r2, lsr #32
d001f418:	4770bc30 			; <UNDEFINED> instruction: 0x4770bc30
d001f41c:	bf004770 	svclt	0x00004770

Disassembly of section .text.memcmp:

d001f420 <.text.memcmp>:
d001f420:	46034402 	strmi	r4, [r3], -r2, lsl #8
d001f424:	d0134290 	mulsle	r3, r0, r2
d001f428:	e002b470 	and	fp, r2, r0, ror r4
d001f42c:	46034290 			; <UNDEFINED> instruction: 0x46034290
d001f430:	f813d00b 			; <UNDEFINED> instruction: 0xf813d00b
d001f434:	f8115b01 			; <UNDEFINED> instruction: 0xf8115b01
d001f438:	46184b01 	ldrmi	r4, [r8], -r1, lsl #22
d001f43c:	42a5b2ee 	adcmi	fp, r5, #-536870898	; 0xe000000e
d001f440:	d0f3b2e3 	rscsle	fp, r3, r3, ror #5
d001f444:	bc701af0 			; <UNDEFINED> instruction: 0xbc701af0
d001f448:	20004770 	andcs	r4, r0, r0, ror r7
d001f44c:	4770bc70 			; <UNDEFINED> instruction: 0x4770bc70
d001f450:	47702000 	ldrbmi	r2, [r0, -r0]!

Disassembly of section .text.sb_f_fixed:

d001f458 <.text.sb_f_fixed>:
d001f458:	0b40eeb5 	bleq	0xd105af34
d001f45c:	4ff0e92d 	svcmi	0x00f0e92d
d001f460:	fa10eef1 	blx	0xd045b02c
d001f464:	d0354606 	eorsle	r4, r5, r6, lsl #12
d001f468:	6b04eeb2 	blvs	0xd015af38
d001f46c:	eeb02400 	cdp	4, 11, cr2, cr0, cr0, {0}
d001f470:	eeb47b40 	vcmp.f64	d7, d0
d001f474:	eef10bc6 	vsqrt.f64	d16, d6
d001f478:	da22fa10 	ble	0xd08ddcc0
d001f47c:	6b00eeb7 	blvs	0xd005af60
d001f480:	7bc6eeb4 	blvc	0xcf1daf58
d001f484:	fa10eef1 	blx	0xd045b050
d001f488:	80a6f140 	adchi	pc, r6, r0, asr #2
d001f48c:	5b04eeb2 	blpl	0xd015af5c
d001f490:	73a1f46f 			; <UNDEFINED> instruction: 0x73a1f46f
d001f494:	eeb4e004 	cdp	0, 11, cr14, cr4, cr4, {0}
d001f498:	eef17bc6 	vsqrt.f64	d23, d6
d001f49c:	d504fa10 	strle	pc, [r4, #-2576]	; 0xfffff5f0
d001f4a0:	ee273c01 	cdp	12, 2, cr3, cr7, cr1, {0}
d001f4a4:	429c7b05 	addsmi	r7, ip, #5120	; 0x1400
d001f4a8:	ea24daf5 	b	0xd0956084
d001f4ac:	ea6f73e4 	b	0xd1bfc444
d001f4b0:	459c0c01 	ldrmi	r0, [ip, #3073]	; 0xc01
d001f4b4:	2000dd16 	andcs	sp, r0, r6, lsl sp
d001f4b8:	8ff0e8bd 	svchi	0x00f0e8bd
d001f4bc:	7f9af5b4 	svcvc	0x009af5b4
d001f4c0:	ee87d0dc 	mcr	0, 4, sp, cr7, cr12, {6}
d001f4c4:	34017b06 	strcc	r7, [r1], #-2822	; 0xfffff4fa
d001f4c8:	7bc6eeb4 	blvc	0xcf1dafa0
d001f4cc:	fa10eef1 	blx	0xd045b098
d001f4d0:	e7d3daf4 			; <UNDEFINED> instruction: 0xe7d3daf4
d001f4d4:	eeb02300 	cdp	3, 11, cr2, cr0, cr0, {0}
d001f4d8:	461c7b40 	ldrmi	r7, [ip], -r0, asr #22
d001f4dc:	0c01ea6f 			; <UNDEFINED> instruction: 0x0c01ea6f
d001f4e0:	dce8459c 	cfstr64le	mvdx4, [r8], #624	; 0x270
d001f4e4:	0b00f04f 	bleq	0xd005b628
d001f4e8:	5b04eeb2 	blpl	0xd015afb8
d001f4ec:	0902ea41 	stmdbeq	r2, {r0, r6, r9, fp, sp, lr, pc}
d001f4f0:	38fff10c 	ldmcc	pc!, {r2, r3, r8, ip, sp, lr, pc}^	; <UNPREDICTABLE>
d001f4f4:	43f74658 	mvnsmi	r4, #88, 12	; 0x5800000
d001f4f8:	0a30f04f 	beq	0xd0c5b63c
d001f4fc:	4b38ed9f 	blmi	0xd0e5ab80
d001f500:	0b40eeb5 	bleq	0xd105afdc
d001f504:	fa10eef1 	blx	0xd045b0d0
d001f508:	42a3d030 	adcmi	sp, r3, #48	; 0x30
d001f50c:	eefddc2e 	cdp	12, 15, cr13, cr13, cr14, {1}
d001f510:	f10b6bc7 			; <UNDEFINED> instruction: 0xf10b6bc7
d001f514:	ee160b01 	vnmls.f64	d0, d6, d1
d001f518:	ee161a90 	vmov	r1, s13
d001f51c:	29092a90 	stmdbcs	r9, {r4, r7, r9, fp, sp}
d001f520:	2209bfa8 	andcs	fp, r9, #168, 30	; 0x2a0
d001f524:	0f11f1bb 	svceq	0x0011f1bb
d001f528:	72e2ea22 	rscvc	lr, r2, #139264	; 0x22000
d001f52c:	2a90ee06 	bcs	0xce45ad4c
d001f530:	6be6eeb8 	blvs	0xcf9db018
d001f534:	7b46ee37 	blvc	0xd11dae18
d001f538:	7b05ee27 	blvc	0xd019addc
d001f53c:	459cdc16 	ldrmi	sp, [ip, #3094]	; 0xc16
d001f540:	3230d018 	eorscc	sp, r0, #24
d001f544:	5432b2d2 	ldrtpl	fp, [r2], #-722	; 0xfffffd2e
d001f548:	3b013001 	blcc	0xd006b554
d001f54c:	d0b34543 	adcsle	r4, r3, r3, asr #10
d001f550:	d1d51c59 	bicsle	r1, r5, r9, asr ip
d001f554:	0f00f1b9 	svceq	0x0000f1b9
d001f558:	eeb5d0d2 	mrc	0, 5, sp, cr5, cr2, {6}
d001f55c:	f04f0b40 			; <UNDEFINED> instruction: 0xf04f0b40
d001f560:	5432022e 	ldrtpl	r0, [r2], #-558	; 0xfffffdd2
d001f564:	eef13001 	cdp	0, 15, cr3, cr1, cr1, {0}
d001f568:	d1cefa10 	bicle	pc, lr, r0, lsl sl	; <UNPREDICTABLE>
d001f56c:	d0ec459c 	smlalle	r4, ip, ip, r5
d001f570:	e7e82230 			; <UNDEFINED> instruction: 0xe7e82230
d001f574:	dd1e2905 	vldrle.16	s4, [lr, #-10]	; <UNPREDICTABLE>
d001f578:	dd172800 	ldcle	8, cr2, [r7, #-0]
d001f57c:	0e00eb06 	vmlaeq.f64	d14, d0, d6
d001f580:	f8124672 			; <UNDEFINED> instruction: 0xf8124672
d001f584:	292e1d01 	stmdbcs	lr!, {r0, r8, sl, fp, ip}
d001f588:	0502eb07 	streq	lr, [r2, #-2823]	; 0xfffff4f9
d001f58c:	2938d003 	ldmdbcs	r8!, {r0, r1, ip, lr, pc}
d001f590:	f882d91f 			; <UNDEFINED> instruction: 0xf882d91f
d001f594:	3501a000 	strcc	sl, [r1, #-0]
d001f598:	2800d1f3 	stmdacs	r0, {r0, r1, r4, r5, r6, r7, r8, ip, lr, pc}
d001f59c:	4672dd06 	ldrbtmi	sp, [r2], -r6, lsl #26
d001f5a0:	1c01f812 	stcne	8, cr15, [r1], {18}
d001f5a4:	1901f802 	stmdbne	r1, {r1, fp, ip, sp, lr, pc}
d001f5a8:	d1f94296 			; <UNDEFINED> instruction: 0xd1f94296
d001f5ac:	0231f04f 	eorseq	pc, r1, #79	; 0x4f
d001f5b0:	70323001 	eorsvc	r3, r2, r1
d001f5b4:	d1c8e7c9 	bicle	lr, r8, r9, asr #15
d001f5b8:	7bc4eeb4 	blvc	0xcf15b090
d001f5bc:	fa10eef1 	blx	0xd045b188
d001f5c0:	2800dcda 	stmdacs	r0, {r1, r3, r4, r6, r7, sl, fp, ip, lr, pc}
d001f5c4:	1832d0c1 	ldmdane	r2!, {r0, r6, r7, ip, lr, pc}
d001f5c8:	2c01f812 	stccs	8, cr15, [r1], {18}
d001f5cc:	d5bc07d2 	ldrle	r0, [ip, #2002]!	; 0x7d2
d001f5d0:	3101e7d2 	ldrdcc	lr, [r1, -r2]
d001f5d4:	e7b87011 			; <UNDEFINED> instruction: 0xe7b87011
d001f5d8:	e77f4623 	ldrb	r4, [pc, -r3, lsr #12]!
d001f5dc:	8000f3af 	andhi	pc, r0, pc, lsr #7
d001f5e0:	812dea11 			; <UNDEFINED> instruction: 0x812dea11
d001f5e4:	3d719799 	ldclcc	7, cr9, [r1, #-612]!	; 0xfffffd9c

Disassembly of section .text.sb_f_exponent:

d001f5e8 <.text.sb_f_exponent>:
d001f5e8:	0b40eeb5 	bleq	0xd105b0c4
d001f5ec:	4ff0e92d 	svcmi	0x00f0e92d
d001f5f0:	fa10eef1 	blx	0xd045b1bc
d001f5f4:	d0344607 	eorsle	r4, r4, r7, lsl #12
d001f5f8:	6b04eeb2 	blvs	0xd015b0c8
d001f5fc:	0bc6eeb4 	bleq	0xcf1db0d4
d001f600:	fa10eef1 	blx	0xd045b1cc
d001f604:	80cef2c0 	sbchi	pc, lr, r0, asr #5
d001f608:	7b40eeb0 	blvc	0xd105b0d0
d001f60c:	e0022400 	and	r2, r2, r0, lsl #8
d001f610:	7f9af5b4 	svcvc	0x009af5b4
d001f614:	ee87d007 	cdp	0, 8, cr13, cr7, cr7, {0}
d001f618:	34017b06 	strcc	r7, [r1], #-2822	; 0xfffff4fa
d001f61c:	7bc6eeb4 	blvc	0xcf1db0f4
d001f620:	fa10eef1 	blx	0xd045b1ec
d001f624:	eeb7daf4 			; <UNDEFINED> instruction: 0xeeb7daf4
d001f628:	eeb46b00 	vmov.f64	d6, #64	; 0x3e000000  0.125
d001f62c:	eef17bc6 	vsqrt.f64	d23, d6
d001f630:	d519fa10 	ldrle	pc, [r9, #-2576]	; 0xfffff5f0
d001f634:	5b04eeb2 	blpl	0xd015b104
d001f638:	70a1f46f 	adcvc	pc, r1, pc, ror #8
d001f63c:	eeb4e004 	cdp	0, 11, cr14, cr4, cr4, {0}
d001f640:	eef17bc6 	vsqrt.f64	d23, d6
d001f644:	d50ffa10 	strle	pc, [pc, #-2576]	; 0xd001ec3c
d001f648:	ee273c01 	cdp	12, 2, cr3, cr7, cr1, {0}
d001f64c:	42847b05 	addmi	r7, r4, #5120	; 0x1400
d001f650:	f111daf5 			; <UNDEFINED> instruction: 0xf111daf5
d001f654:	d50a0e01 	strle	r0, [sl, #-3585]	; 0xfffff1ff
d001f658:	2102463e 	tstcs	r2, lr, lsr r6
d001f65c:	22002501 	andcs	r2, r0, #4194304	; 0x400000
d001f660:	eeb0e062 	cdp	0, 11, cr14, cr0, cr2, {3}
d001f664:	24007b40 	strcs	r7, [r0], #-2880	; 0xfffff4c0
d001f668:	0e01f111 	mcreq	1, 0, pc, cr1, cr1, {0}	; <UNPREDICTABLE>
d001f66c:	2500d4f4 	strcs	sp, [r0, #-1268]	; 0xfffffb0c
d001f670:	5b04eeb2 	blpl	0xd015b140
d001f674:	0902ea41 	stmdbeq	r2, {r0, r6, r9, fp, sp, lr, pc}
d001f678:	462a1c88 	strtmi	r1, [sl], -r8, lsl #25
d001f67c:	0807ea6f 	stmdaeq	r7, {r0, r1, r2, r3, r5, r6, r9, fp, sp, lr, pc}
d001f680:	0a30f04f 	beq	0xd0c5b7c4
d001f684:	0b2ef04f 	bleq	0xd0bdb7c8
d001f688:	4b49ed9f 	blmi	0xd129ad0c
d001f68c:	0b40eeb5 	bleq	0xd105b168
d001f690:	fa10eef1 	blx	0xd045b25c
d001f694:	4575d114 	ldrbmi	sp, [r5, #-276]!	; 0xfffffeec
d001f698:	2130d002 	teqcs	r0, r2
d001f69c:	320154b9 	andcc	r5, r1, #-1191182336	; 0xb9000000
d001f6a0:	42853501 	addmi	r3, r5, #4194304	; 0x400000
d001f6a4:	2d01d03d 	stccs	0, cr13, [r1, #-244]	; 0xffffff0c
d001f6a8:	f1b9d1f0 			; <UNDEFINED> instruction: 0xf1b9d1f0
d001f6ac:	d0ed0f00 	rscle	r0, sp, r0, lsl #30
d001f6b0:	0b40eeb5 	bleq	0xd105b18c
d001f6b4:	b002f807 	andlt	pc, r2, r7, lsl #16
d001f6b8:	eef13201 	cdp	2, 15, cr3, cr1, cr1, {0}
d001f6bc:	d0eafa10 	rscle	pc, sl, r0, lsl sl	; <UNPREDICTABLE>
d001f6c0:	6bc7eefd 	blvs	0xcf21b2bc
d001f6c4:	6a90ee16 	bvs	0xce45af24
d001f6c8:	1a90ee16 	bne	0xce45af28
d001f6cc:	bfa82e09 	svclt	0x00a82e09
d001f6d0:	45752109 	ldrbmi	r2, [r5, #-265]!	; 0xfffffef7
d001f6d4:	71e1ea21 	mvnvc	lr, r1, lsr #20
d001f6d8:	1a90ee06 	bne	0xce45aef8
d001f6dc:	6be6eeb8 	blvs	0xcf9db1c4
d001f6e0:	7b46ee37 	blvc	0xd11dafc4
d001f6e4:	7b05ee27 	blvc	0xd019af88
d001f6e8:	3130d002 	teqcc	r0, r2
d001f6ec:	e7d5b2c9 	ldrb	fp, [r5, r9, asr #5]
d001f6f0:	dd462e05 	stclle	14, cr2, [r6, #-20]	; 0xffffffec
d001f6f4:	dd0d2a00 	vstrle	s4, [sp, #-0]
d001f6f8:	f81118b9 			; <UNDEFINED> instruction: 0xf81118b9
d001f6fc:	2e2e6d01 	cdpcs	13, 2, cr6, cr14, cr1, {0}
d001f700:	0c01eb08 			; <UNDEFINED> instruction: 0x0c01eb08
d001f704:	2e38d003 	cdpcs	0, 3, cr13, cr8, cr3, {0}
d001f708:	f881d949 			; <UNDEFINED> instruction: 0xf881d949
d001f70c:	f1bca000 			; <UNDEFINED> instruction: 0xf1bca000
d001f710:	d1f23fff 	ldrshle	r3, [r2, #255]!	; 0xff
d001f714:	f04f3501 			; <UNDEFINED> instruction: 0xf04f3501
d001f718:	34010131 	strcc	r0, [r1], #-305	; 0xfffffecf
d001f71c:	70394285 	eorsvc	r4, r9, r5, lsl #5
d001f720:	18bed1c1 	ldmne	lr!, {r0, r6, r7, r8, ip, lr, pc}
d001f724:	1c911c55 	ldcne	12, cr1, [r1], {85}	; 0x55
d001f728:	bf142b00 	svclt	0x00142b00
d001f72c:	20652045 	rsbcs	r2, r5, r5, asr #32
d001f730:	70302c00 	eorsvc	r2, r0, r0, lsl #24
d001f734:	232dbfb4 			; <UNDEFINED> instruction: 0x232dbfb4
d001f738:	2c00232b 	stccs	3, cr2, [r0], {43}	; 0x2b
d001f73c:	bfb8557b 	svclt	0x00b8557b
d001f740:	2c634264 	sfmcs	f4, 2, [r3], #-400	; 0xfffffe70
d001f744:	4b1cdd06 	blmi	0xd0756b64
d001f748:	0304fba3 	movweq	pc, #19363	; 0x4ba3	; <UNPREDICTABLE>
d001f74c:	3330095b 	teqcc	r0, #1490944	; 0x16c000
d001f750:	1cd1547b 	cfldrdne	mvd5, [r1], {123}	; 0x7b
d001f754:	187d4a19 	ldmdane	sp!, {r0, r3, r4, r9, fp, lr}^
d001f758:	0304fba2 	movweq	pc, #19362	; 0x4ba2	; <UNPREDICTABLE>
d001f75c:	08db1c88 	ldmeq	fp, {r3, r7, sl, fp, ip}^
d001f760:	6203fba2 	andvs	pc, r3, #165888	; 0x28800
d001f764:	0683eb03 	streq	lr, [r3], r3, lsl #22
d001f768:	eba408d2 	bl	0xce921ab8
d001f76c:	eb020446 	bl	0xd00a088c
d001f770:	34300282 	ldrtcc	r0, [r0], #-642	; 0xfffffd7e
d001f774:	0342eba3 	movteq	lr, #11171	; 0x2ba3
d001f778:	547b3330 	ldrbtpl	r3, [fp], #-816	; 0xfffffcd0
d001f77c:	e8bd706c 	pop	{r2, r3, r5, r6, ip, sp, lr}
d001f780:	d18d8ff0 	strdle	r8, [sp, r0]
d001f784:	7bc4eeb4 	blvc	0xcf15b25c
d001f788:	fa10eef1 	blx	0xd045b354
d001f78c:	2a00dcb2 	bcs	0xd0056a5c
d001f790:	18b9d086 	ldmne	r9!, {r1, r2, r7, ip, lr, pc}
d001f794:	1c01f811 	stcne	8, cr15, [r1], {17}
d001f798:	d58107c9 	strle	r0, [r1, #1993]	; 0x7c9
d001f79c:	3601e7aa 	strcc	lr, [r1], -sl, lsr #15
d001f7a0:	e77d700e 	ldrb	r7, [sp, -lr]!
d001f7a4:	7b40eeb0 	blvc	0xd105b26c
d001f7a8:	e73c2400 	ldr	r2, [ip, -r0, lsl #8]!
d001f7ac:	8000f3af 	andhi	pc, r0, pc, lsr #7
d001f7b0:	812dea11 			; <UNDEFINED> instruction: 0x812dea11
d001f7b4:	3d719799 	ldclcc	7, cr9, [r1, #-612]!	; 0xfffffd9c
d001f7b8:	51eb851f 	mvnpl	r8, pc, lsl r5
d001f7bc:	cccccccd 	stclgt	12, cr12, [ip], {205}	; 0xcd

Disassembly of section .text.sb_flush.part.0:

d001f7c0 <.text.sb_flush.part.0>:
d001f7c0:	2090f8d0 			; <UNDEFINED> instruction: 0x2090f8d0
d001f7c4:	4b07b16a 	blmi	0xd020bd74
d001f7c8:	0110f100 	tsteq	r0, r0, lsl #2	; <UNPREDICTABLE>
d001f7cc:	681b689b 	ldmdavs	fp, {r0, r1, r3, r4, r7, fp, sp, lr}
d001f7d0:	685bb510 	ldmdavs	fp, {r4, r8, sl, ip, sp, pc}^
d001f7d4:	20004604 	andcs	r4, r0, r4, lsl #12
d001f7d8:	23004798 	movwcs	r4, #1944	; 0x798
d001f7dc:	3090f8c4 	addscc	pc, r0, r4, asr #17
d001f7e0:	4770bd10 			; <UNDEFINED> instruction: 0x4770bd10
d001f7e4:	2001f000 	andcs	pc, r1, r0

Disassembly of section .text.sb_char:

d001f7e8 <.text.sb_char>:
d001f7e8:	b51068c3 	ldrlt	r6, [r0, #-2243]	; 0xfffff73d
d001f7ec:	b1834604 	orrlt	r4, r3, r4, lsl #12
d001f7f0:	3090f8d0 			; <UNDEFINED> instruction: 0x3090f8d0
d001f7f4:	44031c5a 	strmi	r1, [r3], #-3162	; 0xfffff3a6
d001f7f8:	f8c02a80 			; <UNDEFINED> instruction: 0xf8c02a80
d001f7fc:	74192090 	ldrvc	r2, [r9], #-144	; 0xffffff70
d001f800:	68a3d013 	stmiavs	r3!, {r0, r1, r4, ip, lr, pc}
d001f804:	4200f06f 	andmi	pc, r0, #111	; 0x6f
d001f808:	d2014293 	andle	r4, r1, #805306377	; 0x30000009
d001f80c:	60a33301 	adcvs	r3, r3, r1, lsl #6
d001f810:	6800bd10 	stmdavs	r0, {r4, r8, sl, fp, ip, sp, pc}
d001f814:	d0f42800 	rscsle	r2, r4, r0, lsl #16
d001f818:	68a36862 	stmiavs	r3!, {r1, r5, r6, fp, sp, lr}
d001f81c:	bf182a00 	svclt	0x00182a00
d001f820:	42933a01 	addsmi	r3, r3, #4096	; 0x1000
d001f824:	54c1d2ee 	strbpl	sp, [r1], #750	; 0x2ee
d001f828:	f7ffe7eb 			; <UNDEFINED> instruction: 0xf7ffe7eb
d001f82c:	68a3ffc9 	stmiavs	r3!, {r0, r3, r6, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d001f830:	bf00e7e8 	svclt	0x0000e7e8

Disassembly of section .text.sb_number:

d001f848 <.text.sb_number>:
d001f848:	4ff0e92d 	svcmi	0x00f0e92d
d001f84c:	8b02ed2d 	blhi	0xd00dad08
d001f850:	ee08b09b 	mcr	0, 0, fp, cr8, cr11, {4}
d001f854:	93070a10 	movwls	r0, #31248	; 0x7a10
d001f858:	92069b2b 	andls	r9, r6, #44032	; 0xac00
d001f85c:	d13e2b00 	teqle	lr, r0, lsl #22
d001f860:	e9dd4bbf 	ldmib	sp, {r0, r1, r2, r3, r4, r5, r7, r8, r9, fp, lr}^
d001f864:	447b1206 	ldrbtmi	r1, [fp], #-518	; 0xfffffdfa
d001f868:	460b9305 	strmi	r9, [fp], -r5, lsl #6
d001f86c:	d13e4313 	teqle	lr, r3, lsl r3
d001f870:	9a2a9b2a 	bls	0xd0ac6520
d001f874:	bf183b00 	svclt	0x00183b00
d001f878:	2a002301 	bcs	0xd0028484
d001f87c:	9303d137 	movwls	sp, #12599	; 0x3137
d001f880:	2b009b27 	blcs	0xd0046524
d001f884:	9b28d179 	blls	0xd0a53e70
d001f888:	f1000759 			; <UNDEFINED> instruction: 0xf1000759
d001f88c:	ea4f8101 	b	0xd13ffc98
d001f890:	9a2c0983 	bls	0xd0b21ea4
d001f894:	1a40f3c9 	bne	0xd105c7c0
d001f898:	0920f009 	stmdbeq	r0!, {r0, r3, ip, sp, lr, pc}
d001f89c:	2a004653 	bcs	0xd00311f0
d001f8a0:	9a26d072 	bls	0xd09d3a70
d001f8a4:	f0002a10 			; <UNDEFINED> instruction: 0xf0002a10
d001f8a8:	9a2680f8 	bls	0xd09bfc90
d001f8ac:	f0002a02 			; <UNDEFINED> instruction: 0xf0002a02
d001f8b0:	9a268144 	bls	0xd09bfdc8
d001f8b4:	9a032a08 	bls	0xd00ea0dc
d001f8b8:	8122f000 	msrhi	CPSR_x, r0
d001f8bc:	2600992a 	strcs	r9, [r0], -sl, lsr #18
d001f8c0:	82a0f8df 	adchi	pc, r0, #14614528	; 0xdf0000
d001f8c4:	44f84291 	ldrbtmi	r4, [r8], #657	; 0x291
d001f8c8:	9a03dc69 	bls	0xd0116a74
d001f8cc:	19942700 	ldmibne	r4, {r8, r9, sl, sp}
d001f8d0:	44239a29 	strtmi	r9, [r3], #-2601	; 0xfffff5d7
d001f8d4:	f0c04293 			; <UNDEFINED> instruction: 0xf0c04293
d001f8d8:	463c80e8 	ldrtmi	r8, [ip], -r8, ror #1
d001f8dc:	4ba2e0e7 	blmi	0xce8d7c80
d001f8e0:	1206e9dd 	andne	lr, r6, #3620864	; 0x374000
d001f8e4:	9305447b 	movwls	r4, #21627	; 0x547b
d001f8e8:	4313460b 	tstmi	r3, #11534336	; 0xb00000
d001f8ec:	ab09d0c0 	blge	0xd0293bf4
d001f8f0:	26012200 	strcs	r2, [r1], -r0, lsl #4
d001f8f4:	e9dd9304 	ldmib	sp, {r2, r8, r9, ip, pc}^
d001f8f8:	469b3406 	ldrmi	r3, [fp], r6, lsl #8
d001f8fc:	46272300 	strtmi	r2, [r7], -r0, lsl #6
d001f900:	9b269303 	blls	0xd09c4514
d001f904:	e9cd4619 	stmib	sp, {r0, r3, r4, r9, sl, lr}^
d001f908:	23001200 	movwcs	r1, #512	; 0x200
d001f90c:	0ffa203f 	svceq	0x00fa203f
d001f910:	b008f8cd 	andlt	pc, r8, sp, asr #17
d001f914:	469a4699 			; <UNDEFINED> instruction: 0x469a4699
d001f918:	99023801 	stmdbls	r2, {r0, fp, ip, sp}
d001f91c:	0420f1c0 	strteq	pc, [r0], #-448	; 0xfffffe40
d001f920:	0520f1a0 	streq	pc, [r0, #-416]!	; 0xfffffe60
d001f924:	f1b040c1 			; <UNDEFINED> instruction: 0xf1b040c1
d001f928:	fa073fff 	blx	0xd01ef92c
d001f92c:	fa27fe04 	blx	0xd0a1f144
d001f930:	fa26fc05 	blx	0xd09de94c
d001f934:	fa06f404 	blx	0xd01dc94c
d001f938:	ea41f505 	b	0xd109cd54
d001f93c:	fa06010e 	blx	0xd019fd7c
d001f940:	ea44f800 	b	0xd115d948
d001f944:	ea410405 	b	0xd1060960
d001f948:	d072010c 	rsbsle	r0, r2, ip, lsl #2
d001f94c:	f0011895 			; <UNDEFINED> instruction: 0xf0011895
d001f950:	eb430101 	bl	0xd10dfd5c
d001f954:	ea410c03 	b	0xd1062968
d001f958:	46630205 	strbtmi	r0, [r3], -r5, lsl #4
d001f95c:	bc00e9dd 			; <UNDEFINED> instruction: 0xbc00e9dd
d001f960:	bf084563 	svclt	0x00084563
d001f964:	d3d7455a 	bicsle	r4, r7, #377487360	; 0x16800000
d001f968:	020bebb2 	andeq	lr, fp, #182272	; 0x2c800
d001f96c:	0909ea48 	stmdbeq	r9, {r3, r6, r9, fp, sp, lr, pc}
d001f970:	0a0aea44 	beq	0xd02da288
d001f974:	030ceb63 	movweq	lr, #52067	; 0xcb63
d001f978:	2301e7ce 	movwcs	lr, #6094	; 0x17ce
d001f97c:	092df04f 	pusheq	{r0, r1, r2, r3, r6, ip, sp, lr, pc}
d001f980:	9a2c469a 	bls	0xd0b313f0
d001f984:	d18c2a00 	orrle	r2, ip, r0, lsl #20
d001f988:	f0129a28 			; <UNDEFINED> instruction: 0xf0129a28
d001f98c:	d16a0610 	cmnle	sl, r0, lsl r6
d001f990:	81d8f8df 	ldrsbhi	pc, [r8, #143]	; 0x8f	; <UNPREDICTABLE>
d001f994:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d001f998:	4291992a 	addsmi	r9, r1, #688128	; 0xa8000
d001f99c:	9903dd95 	stmdbls	r3, {r0, r2, r4, r7, r8, sl, fp, ip, lr, pc}
d001f9a0:	198a982a 	stmibne	sl, {r1, r3, r5, fp, ip, pc}
d001f9a4:	44131a47 	ldrmi	r1, [r3], #-2631	; 0xfffff5b9
d001f9a8:	443b9a29 	ldrtmi	r9, [fp], #-2601	; 0xfffff5d7
d001f9ac:	d87c429a 	ldmdale	ip!, {r1, r3, r4, r7, r9, lr}^
d001f9b0:	24009b28 	strcs	r9, [r0], #-2856	; 0xfffff4d8
d001f9b4:	0501f003 	streq	pc, [r1, #-3]
d001f9b8:	0f00f1ba 	svceq	0x0000f1ba
d001f9bc:	b16ed14d 	cmnlt	lr, sp, asr #2
d001f9c0:	1000f898 	mulne	r0, r8, r8
d001f9c4:	0a10ee18 	beq	0xd045b22c
d001f9c8:	ff0ef7ff 			; <UNDEFINED> instruction: 0xff0ef7ff
d001f9cc:	d1052e02 	tstle	r5, r2, lsl #28
d001f9d0:	1001f898 	mulne	r1, r8, r8
d001f9d4:	0a10ee18 	beq	0xd045b23c
d001f9d8:	ff06f7ff 			; <UNDEFINED> instruction: 0xff06f7ff
d001f9dc:	b1471e7e 	hvclt	29166	; 0x71ee
d001f9e0:	7a10ee18 	bvc	0xd045b248
d001f9e4:	21303e01 	teqcs	r0, r1, lsl #28
d001f9e8:	f7ff4638 			; <UNDEFINED> instruction: 0xf7ff4638
d001f9ec:	1c72fefd 	ldclne	14, cr15, [r2], #-1012	; 0xfffffc0c
d001f9f0:	9b03d1f8 	blls	0xd01141d8
d001f9f4:	af09b163 	svcge	0x0009b163
d001f9f8:	ee189b03 	vnmls.f64	d9, d8, d3
d001f9fc:	443b8a10 	ldrtmi	r8, [fp], #-2576	; 0xfffff5f0
d001fa00:	f816461e 			; <UNDEFINED> instruction: 0xf816461e
d001fa04:	46401d01 	strbmi	r1, [r0], -r1, lsl #26
d001fa08:	feeef7ff 	mcr2	7, 7, pc, cr14, cr15, {7}	; <UNPREDICTABLE>
d001fa0c:	d1f842b7 	ldrhle	r4, [r8, #39]!	; 0x27
d001fa10:	1e65b155 	mcrne	1, 3, fp, cr5, cr5, {2}
d001fa14:	ee18b144 	mnfem	f3, f4
d001fa18:	3d014a10 	vstrcc	s8, [r1, #-64]	; 0xffffffc0
d001fa1c:	46202120 	strtmi	r2, [r0], -r0, lsr #2
d001fa20:	fee2f7ff 	mcr2	7, 7, pc, cr2, cr15, {7}	; <UNPREDICTABLE>
d001fa24:	d1f81c6b 	mvnsle	r1, fp, ror #24
d001fa28:	ecbdb01b 	ldc	0, cr11, [sp], #108	; 0x6c
d001fa2c:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d001fa30:	99058ff0 	stmdbls	r5, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
d001fa34:	9903440a 	stmdbls	r3, {r1, r3, sl, lr}
d001fa38:	31017813 	tstcc	r1, r3, lsl r8
d001fa3c:	91039a04 	tstls	r3, r4, lsl #20
d001fa40:	3b01f802 	blcc	0xd009da50
d001fa44:	030aea59 	movweq	lr, #43609	; 0xaa59
d001fa48:	f43f9204 			; <UNDEFINED> instruction: 0xf43f9204
d001fa4c:	2940af19 	stmdbcs	r0, {r0, r3, r4, r8, r9, sl, fp, sp, pc}^
d001fa50:	af16f63f 	svcge	0x0016f63f
d001fa54:	465746cb 	ldrbmi	r4, [r7], -fp, asr #13
d001fa58:	4649e757 			; <UNDEFINED> instruction: 0x4649e757
d001fa5c:	0a10ee18 	beq	0xd045b2c4
d001fa60:	fec2f7ff 	mcr2	7, 6, pc, cr2, cr15, {7}	; <UNPREDICTABLE>
d001fa64:	e9dde7ab 	ldmib	sp, {r0, r1, r3, r5, r7, r8, r9, sl, sp, lr, pc}^
d001fa68:	430a1206 	movwmi	r1, #41478	; 0xa206
d001fa6c:	af19f47f 	svcge	0x0019f47f
d001fa70:	2a089a26 	bcs	0xd0246310
d001fa74:	9a03d167 	bls	0xd0114018
d001fa78:	d1642a00 	cmnle	r4, r0, lsl #20
d001fa7c:	21302201 	teqcs	r0, r1, lsl #4
d001fa80:	80ecf8df 	ldrdhi	pc, [ip], #143	; 0x8f	; <UNPREDICTABLE>
d001fa84:	44f89e2c 	ldrbtmi	r9, [r8], #3628	; 0xe2c
d001fa88:	f88d9203 			; <UNDEFINED> instruction: 0xf88d9203
d001fa8c:	e7831024 	str	r1, [r3, r4, lsr #32]
d001fa90:	f04f2301 			; <UNDEFINED> instruction: 0xf04f2301
d001fa94:	469a092b 	ldrmi	r0, [sl], fp, lsr #18
d001fa98:	9a2be773 	bls	0xd0b1986c
d001fa9c:	f8dfb352 			; <UNDEFINED> instruction: 0xf8dfb352
d001faa0:	260280d4 			; <UNDEFINED> instruction: 0x260280d4
d001faa4:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d001faa8:	9a29e776 	bls	0xd0a99888
d001faac:	9b281ad4 	blls	0xd0a26604
d001fab0:	0303f003 	movweq	pc, #12291	; 0x3003	; <UNPREDICTABLE>
d001fab4:	d1022b02 	tstle	r2, r2, lsl #22
d001fab8:	2b009b2a 	blcs	0xd0046768
d001fabc:	9b28db33 	blls	0xd0a56790
d001fac0:	0501f013 	streq	pc, [r1, #-19]	; 0xffffffed
d001fac4:	af78f47f 	svcge	0x0078f47f
d001fac8:	3bfff104 	blcc	0xd001bee0
d001facc:	d0402c00 	suble	r2, r0, r0, lsl #24
d001fad0:	ee189402 	cfmuls	mvf9, mvf8, mvf2
d001fad4:	f10b4a10 			; <UNDEFINED> instruction: 0xf10b4a10
d001fad8:	21203bff 	strdcs	r3, [r0, -pc]!
d001fadc:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d001fae0:	f1bbfe83 			; <UNDEFINED> instruction: 0xf1bbfe83
d001fae4:	d1f63fff 	ldrshle	r3, [r6, #255]!	; 0xff
d001fae8:	f1ba9c02 			; <UNDEFINED> instruction: 0xf1ba9c02
d001faec:	f43f0f00 			; <UNDEFINED> instruction: 0xf43f0f00
d001faf0:	e7b2af66 	ldr	sl, [r2, r6, ror #30]!
d001faf4:	8080f8df 	ldrdhi	pc, [r0], pc	; <UNPREDICTABLE>
d001faf8:	9a032602 	bls	0xd00e9308
d001fafc:	e74b44f8 			; <UNDEFINED> instruction: 0xe74b44f8
d001fb00:	a91ab15a 	ldmdbge	sl, {r1, r3, r4, r6, r8, ip, sp, pc}
d001fb04:	f812188a 			; <UNDEFINED> instruction: 0xf812188a
d001fb08:	2a302c45 	bcs	0xd0c2ac24
d001fb0c:	f8dfd105 			; <UNDEFINED> instruction: 0xf8dfd105
d001fb10:	2600806c 	strcs	r8, [r0], -ip, rrx
d001fb14:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d001fb18:	f8dfe73e 			; <UNDEFINED> instruction: 0xf8dfe73e
d001fb1c:	26018064 	strcs	r8, [r1], -r4, rrx
d001fb20:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d001fb24:	9b28e738 	blls	0xd0a5980c
d001fb28:	24004427 	strcs	r4, [r0], #-1063	; 0xfffffbd9
d001fb2c:	0501f003 	streq	pc, [r1, #-3]
d001fb30:	0f00f1ba 	svceq	0x0000f1ba
d001fb34:	af43f43f 	svcge	0x0043f43f
d001fb38:	f8dfe78f 			; <UNDEFINED> instruction: 0xf8dfe78f
d001fb3c:	46168048 	ldrmi	r8, [r6], -r8, asr #32
d001fb40:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d001fb44:	f8dfe728 			; <UNDEFINED> instruction: 0xf8dfe728
d001fb48:	26008040 	strcs	r8, [r0], -r0, asr #32
d001fb4c:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d001fb50:	4625e722 	strtmi	lr, [r5], -r2, lsr #14
d001fb54:	0f00f1ba 	svceq	0x0000f1ba
d001fb58:	af31f43f 	svcge	0x0031f43f
d001fb5c:	bf00e77d 	svclt	0x0000e77d
d001fb60:	0000136a 	andeq	r1, r0, sl, ror #6
d001fb64:	ffffff6e 			; <UNDEFINED> instruction: 0xffffff6e
d001fb68:	000012d8 	ldrdeq	r1, [r0], -r8
d001fb6c:	fffffe9e 			; <UNDEFINED> instruction: 0xfffffe9e
d001fb70:	fffffdae 			; <UNDEFINED> instruction: 0xfffffdae
d001fb74:	fffffd8a 			; <UNDEFINED> instruction: 0xfffffd8a
d001fb78:	fffffd3c 			; <UNDEFINED> instruction: 0xfffffd3c
d001fb7c:	fffffd1e 			; <UNDEFINED> instruction: 0xfffffd1e
d001fb80:	fffffd1a 			; <UNDEFINED> instruction: 0xfffffd1a
d001fb84:	fffffcfe 			; <UNDEFINED> instruction: 0xfffffcfe
d001fb88:	fffffce6 			; <UNDEFINED> instruction: 0xfffffce6

Disassembly of section .text.sb_float:

d001fba4 <.text.sb_float>:
d001fba4:	4ff0e92d 	svcmi	0x00f0e92d
d001fba8:	bb10ec5c 	bllt	0xd045ad20
d001fbac:	461eb0df 			; <UNDEFINED> instruction: 0x461eb0df
d001fbb0:	73dcea5f 	bicsvc	lr, ip, #389120	; 0x5f000
d001fbb4:	460446e0 	strmi	r4, [r4], -r0, ror #13
d001fbb8:	4615468a 	ldrmi	r4, [r5], -sl, lsl #13
d001fbbc:	9a10ee10 	bls	0xd045b404
d001fbc0:	ed8d9304 	stc	3, cr9, [sp, #16]
d001fbc4:	d10a0b00 	tstle	sl, r0, lsl #22
d001fbc8:	f1000750 			; <UNDEFINED> instruction: 0xf1000750
d001fbcc:	009380cb 	addseq	r8, r3, fp, asr #1
d001fbd0:	1740f3c3 	strbne	pc, [r0, -r3, asr #7]	; <UNPREDICTABLE>
d001fbd4:	0320f003 	wfieq
d001fbd8:	930346bb 	movwls	r4, #14011	; 0x36bb
d001fbdc:	2701e003 	strcs	lr, [r1, -r3]
d001fbe0:	46bb232d 	ldrtmi	r2, [fp], sp, lsr #6
d001fbe4:	f04f9303 			; <UNDEFINED> instruction: 0xf04f9303
d001fbe8:	21000c00 	tstcs	r0, r0, lsl #24
d001fbec:	70fff240 	rscsvc	pc, pc, r0, asr #4
d001fbf0:	520af3c8 	andpl	pc, sl, #200, 6	; 0x20000003
d001fbf4:	f1aa458c 			; <UNDEFINED> instruction: 0xf1aa458c
d001fbf8:	bf080e41 	svclt	0x00080e41
d001fbfc:	fa5f4282 	blx	0xd17f060c
d001fc00:	d03efe8e 	eorsle	pc, lr, lr, lsl #29
d001fc04:	2b099b68 	blcs	0xd02869ac
d001fc08:	4afcdd4b 	bmi	0xcff5713c
d001fc0c:	0918f10d 	ldmdbeq	r8, {r0, r2, r3, r8, ip, sp, lr, pc}
d001fc10:	237046e0 	cmncs	r0, #224, 12	; 0xe000000
d001fc14:	4649447a 			; <UNDEFINED> instruction: 0x4649447a
d001fc18:	3201203c 	andcc	r2, r1, #60	; 0x3c
d001fc1c:	4618e002 	ldrmi	lr, [r8], -r2
d001fc20:	3f01f812 	svccc	0x0001f812
d001fc24:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d001fc28:	0b01f801 	bleq	0xd009dc34
d001fc2c:	d1f62b00 	mvnsle	r2, r0, lsl #22
d001fc30:	020beb08 	andeq	lr, fp, #8, 22	; 0x2000
d001fc34:	42b22301 	adcsmi	r2, r2, #67108864	; 0x4000000
d001fc38:	8099f0c0 	addshi	pc, r9, r0, asr #1
d001fc3c:	f0052600 			; <UNDEFINED> instruction: 0xf0052600
d001fc40:	2a020203 	bcs	0xd00a0454
d001fc44:	2b00d102 	blcs	0xd0054054
d001fc48:	8093f040 	addshi	pc, r3, r0, asr #32
d001fc4c:	0501f015 	streq	pc, [r1, #-21]	; 0xffffffeb
d001fc50:	80bcf040 	adcshi	pc, ip, r0, asr #32
d001fc54:	b1361e75 	teqlt	r6, r5, ror lr
d001fc58:	21203d01 			; <UNDEFINED> instruction: 0x21203d01
d001fc5c:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d001fc60:	1c69fdc3 	stclne	13, cr15, [r9], #-780	; 0xfffffcf4
d001fc64:	2f00d1f8 	svccs	0x0000d1f8
d001fc68:	8091f000 	addshi	pc, r1, r0
d001fc6c:	46209903 	strtmi	r9, [r0], -r3, lsl #18
d001fc70:	fdbaf7ff 	ldc2	7, cr15, [sl, #1020]!	; 0x3fc
d001fc74:	0f00f1b8 	svceq	0x0000f1b8
d001fc78:	808df040 	addhi	pc, sp, r0, asr #32
d001fc7c:	e8bdb05f 	pop	{r0, r1, r2, r3, r4, r6, ip, sp, pc}
d001fc80:	464a8ff0 			; <UNDEFINED> instruction: 0x464a8ff0
d001fc84:	0313f3c8 	tsteq	r3, #200, 6	; 0x20000003	; <UNPREDICTABLE>
d001fc88:	f0404313 			; <UNDEFINED> instruction: 0xf0404313
d001fc8c:	f1be80ae 			; <UNDEFINED> instruction: 0xf1be80ae
d001fc90:	f2000f19 	vrecps.f32	d0, d0, d9
d001fc94:	f8df80d4 			; <UNDEFINED> instruction: 0xf8df80d4
d001fc98:	234ec368 	movtcs	ip, #58216	; 0xe368
d001fc9c:	44fc2149 	ldrbtmi	r2, [ip], #329	; 0x149
d001fca0:	9b04e0ab 	blls	0xd0157f54
d001fca4:	ed9db12b 	ldfd	f3, [sp, #172]	; 0xac
d001fca8:	eeb17b00 	vmov.f64	d7, #16	; 0x40800000  4.0
d001fcac:	ed8d7b47 	vstr	d7, [sp, #284]	; 0x11c
d001fcb0:	f1be7b00 			; <UNDEFINED> instruction: 0xf1be7b00
d001fcb4:	f00a0f19 			; <UNDEFINED> instruction: 0xf00a0f19
d001fcb8:	bf8c0adf 	svclt	0x008c0adf
d001fcbc:	23012300 	movwcs	r2, #4864	; 0x1300
d001fcc0:	9b689304 	blls	0xd1a448d8
d001fcc4:	f2c02b00 	vqdmlsl.s<illegal width 8>	q9, d0, d0
d001fcc8:	f1ba80c5 			; <UNDEFINED> instruction: 0xf1ba80c5
d001fccc:	f0400f47 			; <UNDEFINED> instruction: 0xf0400f47
d001fcd0:	9b6880c7 	blls	0xd1a3fff4
d001fcd4:	bf082b00 	svclt	0x00082b00
d001fcd8:	93682301 	cmnls	r8, #67108864	; 0x4000000
d001fcdc:	7b00ed9d 	blvc	0xd005b358
d001fce0:	7b40eeb5 	blvc	0xd105b7bc
d001fce4:	fa10eef1 	blx	0xd045b8b0
d001fce8:	80d0f000 	sbcshi	pc, r0, r0
d001fcec:	6b04eeb2 	blvs	0xd015b7bc
d001fcf0:	7bc6eeb4 	blvc	0xcf1db7c8
d001fcf4:	fa10eef1 	blx	0xd045b8c0
d001fcf8:	8170f2c0 	cmnhi	r0, r0, asr #5	; <UNPREDICTABLE>
d001fcfc:	0a00f04f 	beq	0xd005be40
d001fd00:	f5bae003 			; <UNDEFINED> instruction: 0xf5bae003
d001fd04:	f0007f9a 			; <UNDEFINED> instruction: 0xf0007f9a
d001fd08:	ee87810f 	sins	f0, #10.0
d001fd0c:	f10a7b06 			; <UNDEFINED> instruction: 0xf10a7b06
d001fd10:	eeb40a01 	vmov.f32	s0, #65	; 0x3e080000  0.1328125
d001fd14:	eef17bc6 	vsqrt.f64	d23, d6
d001fd18:	daf2fa10 	ble	0xcfcde560
d001fd1c:	6b00eeb7 	blvs	0xd005b800
d001fd20:	7bc6eeb4 	blvc	0xcf1db7f8
d001fd24:	fa10eef1 	blx	0xd045b8f0
d001fd28:	eeb2d511 	mrc	5, 5, sp, cr2, cr1, {0}
d001fd2c:	eeb75b04 	vmov.f64	d5, #116	; 0x3fa00000  1.250
d001fd30:	e0036b00 	and	r6, r3, r0, lsl #22
d001fd34:	7fa2f51a 	svcvc	0x00a2f51a
d001fd38:	80fef000 	rscshi	pc, lr, r0
d001fd3c:	7b05ee27 	blvc	0xd019b5e0
d001fd40:	3afff10a 	bcc	0xd001c170
d001fd44:	7bc6eeb4 	blvc	0xcf1db81c
d001fd48:	fa10eef1 	blx	0xd045b914
d001fd4c:	9b68d4f2 	blls	0xd1a5511c
d001fd50:	f3404553 	vqrshl.u8	q10, <illegal reg q1.5>, q0
d001fd54:	f11a80f1 			; <UNDEFINED> instruction: 0xf11a80f1
d001fd58:	f2c00f04 			; <UNDEFINED> instruction: 0xf2c00f04
d001fd5c:	f10a80ed 			; <UNDEFINED> instruction: 0xf10a80ed
d001fd60:	e0960101 	adds	r0, r6, r1, lsl #2
d001fd64:	232b2701 			; <UNDEFINED> instruction: 0x232b2701
d001fd68:	930346bb 	movwls	r4, #14011	; 0x36bb
d001fd6c:	1ab6e73b 	bne	0xcedd9a60
d001fd70:	f005e765 			; <UNDEFINED> instruction: 0xf005e765
d001fd74:	2f000501 	svccs	0x00000501
d001fd78:	bb8dd167 	bllt	0xce39431c
d001fd7c:	b1361e75 	teqlt	r6, r5, ror lr
d001fd80:	21303d01 	teqcs	r0, r1, lsl #26
d001fd84:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d001fd88:	1c6afd2f 	stclne	13, cr15, [sl], #-188	; 0xffffff44
d001fd8c:	f1b8d1f8 			; <UNDEFINED> instruction: 0xf1b8d1f8
d001fd90:	f43f0f00 			; <UNDEFINED> instruction: 0xf43f0f00
d001fd94:	2500af73 	strcs	sl, [r0, #-3955]	; 0xfffff08d
d001fd98:	37012700 	strcc	r2, [r1, -r0, lsl #14]
d001fd9c:	1b01f819 	blne	0xd009de08
d001fda0:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d001fda4:	4547fd21 	strbmi	pc, [r7, #-3361]	; 0xfffff2df	; <UNPREDICTABLE>
d001fda8:	2d00d3f7 	stccs	3, cr13, [r0, #-988]	; 0xfffffc24
d001fdac:	af66f43f 	svcge	0x0066f43f
d001fdb0:	2e001e75 	mcrcs	14, 0, r1, cr0, cr5, {3}
d001fdb4:	af62f43f 	svcge	0x0062f43f
d001fdb8:	21203d01 			; <UNDEFINED> instruction: 0x21203d01
d001fdbc:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d001fdc0:	1c6bfd13 	stclne	13, cr15, [fp], #-76	; 0xffffffb4
d001fdc4:	b05fd1f8 	ldrshlt	sp, [pc], #-24	; <UNPREDICTABLE>
d001fdc8:	8ff0e8bd 	svchi	0x00f0e8bd
d001fdcc:	f1b8b927 			; <UNDEFINED> instruction: 0xf1b8b927
d001fdd0:	d1e10f00 	mvnle	r0, r0, lsl #30
d001fdd4:	461ee7ec 	ldrmi	lr, [lr], -ip, ror #15
d001fdd8:	46209903 	strtmi	r9, [r0], -r3, lsl #18
d001fddc:	fd04f7ff 	stc2	7, cr15, [r4, #-1020]	; 0xfffffc04
d001fde0:	0f00f1b8 	svceq	0x0000f1b8
d001fde4:	2501d0e4 	strcs	sp, [r1, #-228]	; 0xffffff1c
d001fde8:	f1bee7d6 			; <UNDEFINED> instruction: 0xf1bee7d6
d001fdec:	d9470f19 	stmdble	r7, {r0, r3, r4, r8, r9, sl, fp}^
d001fdf0:	c210f8df 	andsgt	pc, r0, #14614528	; 0xdf0000
d001fdf4:	216e2361 	cmncs	lr, r1, ror #6
d001fdf8:	f10d44fc 			; <UNDEFINED> instruction: 0xf10d44fc
d001fdfc:	f10c0918 			; <UNDEFINED> instruction: 0xf10c0918
d001fe00:	ea6f0202 	b	0xd1be0610
d001fe04:	46480c0c 	strbmi	r0, [r8], -ip, lsl #24
d001fe08:	f812e001 			; <UNDEFINED> instruction: 0xf812e001
d001fe0c:	f8003b01 			; <UNDEFINED> instruction: 0xf8003b01
d001fe10:	eb0c1b01 	bl	0xd0326a1c
d001fe14:	46190802 	ldrmi	r0, [r9], -r2, lsl #16
d001fe18:	d1f62b00 	mvnsle	r2, r0, lsl #22
d001fe1c:	020beb08 	andeq	lr, fp, #8, 22	; 0x2000
d001fe20:	d8a44296 	stmiale	r4!, {r1, r2, r4, r7, r9, lr}
d001fe24:	0601f015 			; <UNDEFINED> instruction: 0x0601f015
d001fe28:	af1df43f 	svcge	0x001df43f
d001fe2c:	d1d22f00 	bicsle	r2, r2, r0, lsl #30
d001fe30:	0f00f1b8 	svceq	0x0000f1b8
d001fe34:	af22f43f 	svcge	0x0022f43f
d001fe38:	463e4635 			; <UNDEFINED> instruction: 0x463e4635
d001fe3c:	f8dfe7ac 			; <UNDEFINED> instruction: 0xf8dfe7ac
d001fe40:	236ec1c8 	cmncs	lr, #200, 2	; 0x32
d001fe44:	44fc2169 	ldrbtmi	r2, [ip], #361	; 0x169
d001fe48:	9903e7d7 	stmdbls	r3, {r0, r1, r2, r4, r6, r7, r8, r9, sl, sp, lr, pc}
d001fe4c:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d001fe50:	e792fccb 	ldr	pc, [r2, fp, asr #25]
d001fe54:	f1ba2306 			; <UNDEFINED> instruction: 0xf1ba2306
d001fe58:	93680f47 	cmnls	r8, #284	; 0x11c
d001fe5c:	af3ef43f 	svcge	0x003ef43f
d001fe60:	0f45f1ba 	svceq	0x0045f1ba
d001fe64:	0918f10d 	ldmdbeq	r8, {r0, r2, r3, r8, ip, sp, lr, pc}
d001fe68:	9b04d154 	blls	0xd01543c0
d001fe6c:	0210f005 	andseq	pc, r0, #5
d001fe70:	46489968 	strbmi	r9, [r8], -r8, ror #18
d001fe74:	0b00ed9d 	bleq	0xd005b4f0
d001fe78:	fbb6f7ff 	blx	0xceddde7e
d001fe7c:	e6d74680 	ldrb	r4, [r7], r0, lsl #13
d001fe80:	c188f8df 	ldrdgt	pc, [r8, pc]
d001fe84:	214e2341 	cmpcs	lr, r1, asr #6
d001fe88:	e7b644fc 			; <UNDEFINED> instruction: 0xe7b644fc
d001fe8c:	f04f2101 			; <UNDEFINED> instruction: 0xf04f2101
d001fe90:	9b680a00 	blls	0xd1a22698
d001fe94:	0918f10d 	ldmdbeq	r8, {r0, r2, r3, r8, ip, sp, lr, pc}
d001fe98:	0210f005 	andseq	pc, r0, #5
d001fe9c:	46481a59 			; <UNDEFINED> instruction: 0x46481a59
d001fea0:	ed9d9205 	lfm	f1, 1, [sp, #20]
d001fea4:	f7ff0b00 			; <UNDEFINED> instruction: 0xf7ff0b00
d001fea8:	4680fad7 	pkhtbmi	pc, r0, r7, asr #21	; <UNPREDICTABLE>
d001feac:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001feb0:	4649aebf 			; <UNDEFINED> instruction: 0x4649aebf
d001feb4:	9a052300 	bls	0xd0168abc
d001feb8:	3301e003 	movwcc	lr, #4099	; 0x1003
d001febc:	f0004598 			; <UNDEFINED> instruction: 0xf0004598
d001fec0:	f8118086 			; <UNDEFINED> instruction: 0xf8118086
d001fec4:	282e0b01 	stmdacs	lr!, {r0, r8, r9, fp}
d001fec8:	f1bad1f7 			; <UNDEFINED> instruction: 0xf1bad1f7
d001fecc:	db020f00 	blle	0xd00a3ad4
d001fed0:	42999968 	addsmi	r9, r9, #104, 18	; 0x1a0000
d001fed4:	2a00d334 	bcs	0xd0054bac
d001fed8:	aeaaf47f 	mcrge	4, 5, pc, cr10, cr15, {3}	; <UNPREDICTABLE>
d001fedc:	e002464b 	and	r4, r2, fp, asr #12
d001fee0:	f43f4590 			; <UNDEFINED> instruction: 0xf43f4590
d001fee4:	f813aea5 			; <UNDEFINED> instruction: 0xf813aea5
d001fee8:	32011b01 	andcc	r1, r1, #1024	; 0x400
d001feec:	d1f7292e 	mvnsle	r2, lr, lsr #18
d001fef0:	0308eb09 	movweq	lr, #35593	; 0x8b09
d001fef4:	f813e005 			; <UNDEFINED> instruction: 0xf813e005
d001fef8:	29301d01 	ldmdbcs	r0!, {r0, r8, sl, fp, ip}
d001fefc:	ae98f47f 	mrcge	4, 4, APSR_nzcv, cr8, cr15, {3}
d001ff00:	45904680 	ldrmi	r4, [r0, #1664]	; 0x680
d001ff04:	30fff108 	rscscc	pc, pc, r8, lsl #2
d001ff08:	f47fd8f5 			; <UNDEFINED> instruction: 0xf47fd8f5
d001ff0c:	f108ae91 			; <UNDEFINED> instruction: 0xf108ae91
d001ff10:	e68d38ff 			; <UNDEFINED> instruction: 0xe68d38ff
d001ff14:	0b00ed9d 	bleq	0xd005b590
d001ff18:	f0059968 			; <UNDEFINED> instruction: 0xf0059968
d001ff1c:	46480210 			; <UNDEFINED> instruction: 0x46480210
d001ff20:	fa9af7ff 	blx	0xce6ddf24
d001ff24:	e6834680 	str	r4, [r3], r0, lsl #13
d001ff28:	6b00eeb7 	blvs	0xd005ba0c
d001ff2c:	7bc6eeb4 	blvc	0xcf1dba04
d001ff30:	fa10eef1 	blx	0xd045bafc
d001ff34:	aef9f53f 	mrcge	5, 7, APSR_nzcv, cr9, cr15, {1}
d001ff38:	0210f005 	andseq	pc, r0, #5
d001ff3c:	0918f10d 	ldmdbeq	r8, {r0, r2, r3, r8, ip, sp, lr, pc}
d001ff40:	46489968 	strbmi	r9, [r8], -r8, ror #18
d001ff44:	39019b04 	stmdbcc	r1, {r2, r8, r9, fp, ip, pc}
d001ff48:	ed9d9204 	lfm	f1, 1, [sp, #16]
d001ff4c:	f7ff0b00 			; <UNDEFINED> instruction: 0xf7ff0b00
d001ff50:	9a04fb4b 	bls	0xd015ec84
d001ff54:	2a004680 	bcs	0xd003195c
d001ff58:	ae6af47f 	mcrge	4, 3, pc, cr10, cr15, {3}	; <UNPREDICTABLE>
d001ff5c:	46424448 	strbmi	r4, [r2], -r8, asr #8
d001ff60:	461ae000 	ldrmi	lr, [sl], -r0
d001ff64:	2a001e53 	bcs	0xd00278b8
d001ff68:	ae62f43f 	mcrge	4, 3, pc, cr2, cr15, {1}	; <UNPREDICTABLE>
d001ff6c:	1d01f810 	stcne	8, cr15, [r1, #-64]	; 0xffffffc0
d001ff70:	0cdff001 	ldcleq	0, cr15, [pc], {1}
d001ff74:	0f45f1bc 	svceq	0x0045f1bc
d001ff78:	eb09d1f3 	bl	0xd029474c
d001ff7c:	46180c03 	ldrmi	r0, [r8], -r3, lsl #24
d001ff80:	f81ce005 			; <UNDEFINED> instruction: 0xf81ce005
d001ff84:	f1baad01 			; <UNDEFINED> instruction: 0xf1baad01
d001ff88:	d1220f30 			; <UNDEFINED> instruction: 0xd1220f30
d001ff8c:	f1004670 			; <UNDEFINED> instruction: 0xf1004670
d001ff90:	28003eff 	stmdacs	r0, {r0, r1, r2, r3, r4, r5, r6, r7, r9, sl, fp, ip, sp}
d001ff94:	4543d1f5 	strbmi	sp, [r3, #-501]	; 0xfffffe0b
d001ff98:	f1c2d212 			; <UNDEFINED> instruction: 0xf1c2d212
d001ff9c:	eb090a01 	bl	0xd02627a8
d001ffa0:	f10d0c03 			; <UNDEFINED> instruction: 0xf10d0c03
d001ffa4:	44820e17 	strmi	r0, [r2], #3607	; 0xe17
d001ffa8:	445344c6 	ldrbmi	r4, [r3], #-1222	; 0xfffffb3a
d001ffac:	3b0144d6 	blcc	0xd007130c
d001ffb0:	e001444b 	and	r4, r1, fp, asr #8
d001ffb4:	1f01f81c 	svcne	0x0001f81c
d001ffb8:	1f01f803 	svcne	0x0001f803
d001ffbc:	d1f94573 	mvnsle	r4, r3, ror r5
d001ffc0:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d001ffc4:	0202eba8 	andeq	lr, r2, #168, 22	; 0x2a000
d001ffc8:	0802eb00 	stmdaeq	r2, {r8, r9, fp, sp, lr, pc}
d001ffcc:	4643e630 			; <UNDEFINED> instruction: 0x4643e630
d001ffd0:	f1bae77b 			; <UNDEFINED> instruction: 0xf1bae77b
d001ffd4:	bf080f2e 	svclt	0x00080f2e
d001ffd8:	e7dc4670 			; <UNDEFINED> instruction: 0xe7dc4670
d001ffdc:	7b00eeb7 	blvc	0xd005bac0
d001ffe0:	6b00ed9d 	blvs	0xd005b65c
d001ffe4:	6bc7eeb4 	blvs	0xcf21babc
d001ffe8:	fa10eef1 	blx	0xd045bbb4
d001ffec:	af4ef57f 	svcge	0x004ef57f
d001fff0:	0a00f04f 	beq	0xd005c134
d001fff4:	7b00ed9d 	blvc	0xd005b670
d001fff8:	bf00e697 	svclt	0x0000e697
d001fffc:	ffffff84 			; <UNDEFINED> instruction: 0xffffff84
d0020000:	fffffeee 			; <UNDEFINED> instruction: 0xfffffeee
d0020004:	fffffd90 			; <UNDEFINED> instruction: 0xfffffd90
d0020008:	fffffd4e 			; <UNDEFINED> instruction: 0xfffffd4e
d002000c:	fffffd08 			; <UNDEFINED> instruction: 0xfffffd08

Disassembly of section .text.sb_format.part.0:

d0020040 <.text.sb_format.part.0>:
d0020040:	4ff0e92d 	svcmi	0x00f0e92d
d0020044:	78094688 	stmdavc	r9, {r3, r7, r9, sl, lr}
d0020048:	4683b0a7 	strmi	fp, [r3], r7, lsr #1
d002004c:	f0002900 			; <UNDEFINED> instruction: 0xf0002900
d0020050:	4bfa80b3 	blmi	0xcfec0324
d0020054:	f8df4691 			; <UNDEFINED> instruction: 0xf8df4691
d0020058:	447ba3e8 	ldrbtmi	sl, [fp], #-1000	; 0xfffffc18
d002005c:	4bf99308 	blmi	0xcfe84c84
d0020060:	9309447b 	movwls	r4, #38011	; 0x947b
d0020064:	f0402925 			; <UNDEFINED> instruction: 0xf0402925
d0020068:	f89880fd 			; <UNDEFINED> instruction: 0xf89880fd
d002006c:	2c254001 	stccs	0, cr4, [r5], #-4
d0020070:	80fef000 	rscshi	pc, lr, r0
d0020074:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d0020078:	f1a42600 			; <UNDEFINED> instruction: 0xf1a42600
d002007c:	2b100320 	blcs	0xd0420d04
d0020080:	e8dfd80a 	ldm	pc, {r1, r3, fp, ip, lr, pc}^	; <UNPREDICTABLE>
d0020084:	0978f003 	ldmdbeq	r8!, {r0, r1, ip, sp, lr, pc}^
d0020088:	09097509 	stmdbeq	r9, {r0, r3, r8, sl, ip, sp, lr}
d002008c:	09090909 	stmdbeq	r9, {r0, r3, r8, fp}
d0020090:	6f097209 	svcvs	0x00097209
d0020094:	006a0909 	rsbeq	r0, sl, r9, lsl #18
d0020098:	f0402c2a 			; <UNDEFINED> instruction: 0xf0402c2a
d002009c:	f8d980ef 			; <UNDEFINED> instruction: 0xf8d980ef
d00200a0:	f1083000 			; <UNDEFINED> instruction: 0xf1083000
d00200a4:	681d0101 	ldmdavs	sp, {r0, r8}
d00200a8:	2d001d1a 	stccs	13, cr1, [r0, #-104]	; 0xffffff98
d00200ac:	2000f8c9 	andcs	pc, r0, r9, asr #17
d00200b0:	8122f2c0 	smlawthi	r2, r0, r2, pc	; <UNPREDICTABLE>
d00200b4:	5f00f5b5 	svcpl	0x0000f5b5
d00200b8:	4001f898 	mulmi	r1, r8, r8
d00200bc:	f44fbf28 			; <UNDEFINED> instruction: 0xf44fbf28
d00200c0:	2c2e5500 	cfstr32cs	mvfx5, [lr], #-0
d00200c4:	80fbf000 	rscshi	pc, fp, r0
d00200c8:	37fff04f 	ldrbcc	pc, [pc, pc, asr #32]!	; <UNPREDICTABLE>
d00200cc:	f0002c68 			; <UNDEFINED> instruction: 0xf0002c68
d00200d0:	2c6c810d 	stfcsp	f0, [ip], #-52	; 0xffffffcc
d00200d4:	811ef000 	tsthi	lr, r0	; <UNPREDICTABLE>
d00200d8:	f0002c7a 			; <UNDEFINED> instruction: 0xf0002c7a
d00200dc:	2c748122 	ldfcsp	f0, [r4], #-136	; 0xffffff78
d00200e0:	8161f000 	msrhi	SPSR_c, r0
d00200e4:	f0002c6a 			; <UNDEFINED> instruction: 0xf0002c6a
d00200e8:	230081b3 	movwcs	r8, #435	; 0x1b3
d00200ec:	d0632c00 	rsble	r2, r3, r0, lsl #24
d00200f0:	f1012c64 			; <UNDEFINED> instruction: 0xf1012c64
d00200f4:	d07d0801 	rsbsle	r0, sp, r1, lsl #16
d00200f8:	d07b2c69 	rsbsle	r2, fp, r9, ror #24
d00200fc:	0262f1a4 	rsbeq	pc, r2, #164, 2	; 0x29
d0020100:	01dff004 	bicseq	pc, pc, r4
d0020104:	f1a1b2d2 			; <UNDEFINED> instruction: 0xf1a1b2d2
d0020108:	2a130c58 	bcs	0xd04e3270
d002010c:	fc8cfabc 	stc2	10, cr15, [ip], {188}	; 0xbc	; <UNPREDICTABLE>
d0020110:	1c5cea4f 	mrrcne	10, 4, lr, ip, cr15
d0020114:	48c8d806 	stmiami	r8, {r1, r2, fp, ip, lr, pc}^
d0020118:	f202fa20 	vpmax.s8	d15, d2, d16
d002011c:	0201f002 	andeq	pc, r1, #2
d0020120:	0c02ea4c 			; <UNDEFINED> instruction: 0x0c02ea4c
d0020124:	0f00f1bc 	svceq	0x0000f1bc
d0020128:	816cf000 	msrhi	SPSR_fs, r0
d002012c:	f0002c6f 			; <UNDEFINED> instruction: 0xf0002c6f
d0020130:	2958811b 	ldmdbcs	r8, {r0, r1, r3, r4, r8, pc}^
d0020134:	811af000 	tsthi	sl, r0	; <UNPREDICTABLE>
d0020138:	bf0c2c62 	svclt	0x000c2c62
d002013c:	210a2102 	tstcs	sl, r2, lsl #2
d0020140:	2b063b01 	blcs	0xd01aed4c
d0020144:	84fdf200 	ldrbthi	pc, [sp], #512	; 0x200	; <UNPREDICTABLE>
d0020148:	f013e8df 			; <UNDEFINED> instruction: 0xf013e8df
d002014c:	0143014b 	cmpeq	r3, fp, asr #2
d0020150:	00480018 	subeq	r0, r8, r8, lsl r0
d0020154:	00180018 	andseq	r0, r8, r8, lsl r0
d0020158:	f0460048 			; <UNDEFINED> instruction: 0xf0460048
d002015c:	f8180602 			; <UNDEFINED> instruction: 0xf8180602
d0020160:	e78a4f01 	str	r4, [sl, r1, lsl #30]
d0020164:	0601f046 	streq	pc, [r1], -r6, asr #32
d0020168:	f046e7f9 			; <UNDEFINED> instruction: 0xf046e7f9
d002016c:	e7f60604 	ldrb	r0, [r6, r4, lsl #12]!
d0020170:	0610f046 	ldreq	pc, [r0], -r6, asr #32
d0020174:	f046e7f3 			; <UNDEFINED> instruction: 0xf046e7f3
d0020178:	e7f00608 	ldrb	r0, [r0, r8, lsl #12]!
d002017c:	3000f8d9 	ldrdcc	pc, [r0], -r9
d0020180:	681a1d18 	ldmdavs	sl, {r3, r4, r8, sl, fp, ip}
d0020184:	f8c92300 			; <UNDEFINED> instruction: 0xf8c92300
d0020188:	f1a40000 			; <UNDEFINED> instruction: 0xf1a40000
d002018c:	f0260058 			; <UNDEFINED> instruction: 0xf0260058
d0020190:	2400060c 	strcs	r0, [r0], #-1548	; 0xfffff9f4
d0020194:	fab09704 	blx	0xcec45dac
d0020198:	9602f080 	strls	pc, [r2], -r0, lsl #1
d002019c:	09409503 	stmdbeq	r0, {r0, r1, r8, sl, ip, pc}^
d00201a0:	94069100 	strls	r9, [r6], #-256	; 0xffffff00
d00201a4:	46589005 	ldrbmi	r9, [r8], -r5
d00201a8:	f7ff9401 			; <UNDEFINED> instruction: 0xf7ff9401
d00201ac:	f898fb4d 			; <UNDEFINED> instruction: 0xf898fb4d
d00201b0:	29001000 	stmdbcs	r0, {ip}
d00201b4:	af56f47f 	svcge	0x0056f47f
d00201b8:	300cf8db 	ldrdcc	pc, [ip], -fp
d00201bc:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d00201c0:	465880db 			; <UNDEFINED> instruction: 0x465880db
d00201c4:	fafcf7ff 	blx	0xcff5e1c8
d00201c8:	300cf8db 	ldrdcc	pc, [ip], -fp
d00201cc:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d00201d0:	f8db80d3 			; <UNDEFINED> instruction: 0xf8db80d3
d00201d4:	b0270008 	eorlt	r0, r7, r8
d00201d8:	8ff0e8bd 	svchi	0x00f0e8bd
d00201dc:	3000f8d9 	ldrdcc	pc, [r0], -r9
d00201e0:	f0233307 			; <UNDEFINED> instruction: 0xf0233307
d00201e4:	f1030307 			; <UNDEFINED> instruction: 0xf1030307
d00201e8:	f8c90208 			; <UNDEFINED> instruction: 0xf8c90208
d00201ec:	e9d32000 	ldmib	r3, {sp}^
d00201f0:	e7ca2300 	strb	r2, [sl, r0, lsl #6]
d00201f4:	2b063b01 	blcs	0xd01aee00
d00201f8:	84acf200 	strthi	pc, [ip], #512	; 0x200
d00201fc:	f003e8df 			; <UNDEFINED> instruction: 0xf003e8df
d0020200:	1f04d7e0 	svcne	0x0004d7e0
d0020204:	001f0404 	andseq	r0, pc, r4, lsl #8
d0020208:	3000f8d9 	ldrdcc	pc, [r0], -r9
d002020c:	1d1a6818 	ldcne	8, cr6, [sl, #-96]	; 0xffffffa0
d0020210:	f8c917c1 			; <UNDEFINED> instruction: 0xf8c917c1
d0020214:	28002000 	stmdacs	r0, {sp}
d0020218:	0300f171 	movweq	pc, #369	; 0x171	; <UNPREDICTABLE>
d002021c:	4602db1e 			; <UNDEFINED> instruction: 0x4602db1e
d0020220:	0fc8460b 	svceq	0x00c8460b
d0020224:	2100240a 	tstcs	r0, sl, lsl #8
d0020228:	90019704 	andls	r9, r1, r4, lsl #14
d002022c:	95034658 	strls	r4, [r3, #-1624]	; 0xfffff9a8
d0020230:	91069602 	tstls	r6, r2, lsl #12
d0020234:	94009105 	strls	r9, [r0], #-261	; 0xfffffefb
d0020238:	fb06f7ff 	blx	0xd01de23e
d002023c:	f8d9e7b7 			; <UNDEFINED> instruction: 0xf8d9e7b7
d0020240:	33073000 	movwcc	r3, #28672	; 0x7000
d0020244:	0307f023 	movweq	pc, #28707	; 0x7023	; <UNPREDICTABLE>
d0020248:	0100e9d3 	ldrdeq	lr, [r0, -r3]
d002024c:	0208f103 	andeq	pc, r8, #-1073741824	; 0xc0000000
d0020250:	f8c92800 			; <UNDEFINED> instruction: 0xf8c92800
d0020254:	f1712000 			; <UNDEFINED> instruction: 0xf1712000
d0020258:	dae00300 	ble	0xcf820e60
d002025c:	eb614242 	bl	0xd1870b6c
d0020260:	e7de0341 	ldrb	r0, [lr, r1, asr #6]
d0020264:	f1084658 			; <UNDEFINED> instruction: 0xf1084658
d0020268:	f7ff0801 			; <UNDEFINED> instruction: 0xf7ff0801
d002026c:	e79efabd 			; <UNDEFINED> instruction: 0xe79efabd
d0020270:	f1084658 			; <UNDEFINED> instruction: 0xf1084658
d0020274:	f7ff0802 			; <UNDEFINED> instruction: 0xf7ff0802
d0020278:	e798fab7 			; <UNDEFINED> instruction: 0xe798fab7
d002027c:	0230f1a4 	eorseq	pc, r0, #164, 2	; 0x29
d0020280:	2b09b2d3 	blcs	0xd028cdd4
d0020284:	80e8f200 	rschi	pc, r8, r0, lsl #4
d0020288:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d002028c:	f5c22500 			; <UNDEFINED> instruction: 0xf5c22500
d0020290:	46415300 	strbmi	r5, [r1], -r0, lsl #6
d0020294:	0085eb05 	addeq	lr, r5, r5, lsl #22
d0020298:	4303fbaa 	movwmi	pc, #15274	; 0x3baa	; <UNPREDICTABLE>
d002029c:	4b01f818 	blmi	0xd009e304
d00202a0:	0fd3ebb5 	svceq	0x00d3ebb5
d00202a4:	0540eb02 	strbeq	lr, [r0, #-2818]	; 0xfffff4fe
d00202a8:	0230f1a4 	eorseq	pc, r0, #164, 2	; 0x29
d00202ac:	f44fbf88 			; <UNDEFINED> instruction: 0xf44fbf88
d00202b0:	b2d35500 	sbcslt	r5, r3, #0, 10
d00202b4:	d9ea2b09 	stmible	sl!, {r0, r3, r8, r9, fp, sp}^
d00202b8:	f47f2c2e 			; <UNDEFINED> instruction: 0xf47f2c2e
d00202bc:	784caf05 	stmdavc	ip, {r0, r2, r8, r9, sl, fp, sp, pc}^
d00202c0:	d1322c2a 	teqle	r2, sl, lsr #24
d00202c4:	3000f8d9 	ldrdcc	pc, [r0], -r9
d00202c8:	681f1c88 	ldmdavs	pc, {r3, r7, sl, fp, ip}	; <UNPREDICTABLE>
d00202cc:	2f001d1a 	svccs	0x00001d1a
d00202d0:	2000f8c9 	andcs	pc, r0, r9, asr #17
d00202d4:	f2c0788c 	vmlal.s8	<illegal reg q11.5>, d16, d12
d00202d8:	f5b78091 			; <UNDEFINED> instruction: 0xf5b78091
d00202dc:	46015f00 	strmi	r5, [r1], -r0, lsl #30
d00202e0:	f44fbf28 			; <UNDEFINED> instruction: 0xf44fbf28
d00202e4:	2c685700 	stclcs	7, cr5, [r8], #-0
d00202e8:	aef3f47f 	mrcge	4, 7, APSR_nzcv, cr3, cr15, {3}
d00202ec:	2c68784c 	stclcs	8, cr7, [r8], #-304	; 0xfffffed0
d00202f0:	3101d03e 	tstcc	r1, lr, lsr r0
d00202f4:	e6f92302 	ldrbt	r2, [r9], r2, lsl #6
d00202f8:	4f00f1b5 	svcmi	0x0000f1b5
d00202fc:	0601f046 	streq	pc, [r1], -r6, asr #32
d0020300:	426dd077 	rsbmi	sp, sp, #119	; 0x77
d0020304:	4001f898 	mulmi	r1, r8, r8
d0020308:	5f00f5b5 	svcpl	0x0000f5b5
d002030c:	f44fbf28 			; <UNDEFINED> instruction: 0xf44fbf28
d0020310:	e6d65500 	ldrb	r5, [r6], r0, lsl #10
d0020314:	2c6c784c 	stclcs	8, cr7, [ip], #-304	; 0xfffffed0
d0020318:	8096f000 	addshi	pc, r6, r0
d002031c:	23033101 	movwcs	r3, #12545	; 0x3101
d0020320:	784ce6e4 	stmdavc	ip, {r2, r5, r6, r7, r9, sl, sp, lr, pc}^
d0020324:	31012305 	tstcc	r1, r5, lsl #6
d0020328:	f1a4e6e0 			; <UNDEFINED> instruction: 0xf1a4e6e0
d002032c:	1c480230 	sfmne	f0, 2, [r8], {48}	; 0x30
d0020330:	2b09b2d3 	blcs	0xd028ce84
d0020334:	80daf200 	sbcshi	pc, sl, r0, lsl #4
d0020338:	27001c88 	strcs	r1, [r0, -r8, lsl #25]
d002033c:	5300f5c2 	movwpl	pc, #1474	; 0x5c2	; <UNPREDICTABLE>
d0020340:	0487eb07 	streq	lr, [r7], #2823	; 0xb07
d0020344:	fbaa4601 	blx	0xceab1b52
d0020348:	ebb7c303 	bl	0xcee10f5c
d002034c:	eb020fd3 	bl	0xd00a42a0
d0020350:	f8100744 			; <UNDEFINED> instruction: 0xf8100744
d0020354:	bf884b01 	svclt	0x00884b01
d0020358:	5700f44f 	strpl	pc, [r0, -pc, asr #8]
d002035c:	0230f1a4 	eorseq	pc, r0, #164, 2	; 0x29
d0020360:	2b09b2d3 	blcs	0xd028ceb4
d0020364:	e6b1d9ea 	ldrt	sp, [r1], sl, ror #19
d0020368:	e6e92108 	strbt	r2, [r9], r8, lsl #2
d002036c:	e6e72110 	usat	r2, #7, r0, lsl #2
d0020370:	2301788c 	movwcs	r7, #6284	; 0x188c
d0020374:	e6b93102 	ldrt	r3, [r9], r2, lsl #2
d0020378:	3000f8db 	ldrdcc	pc, [r0], -fp
d002037c:	f43f2b00 			; <UNDEFINED> instruction: 0xf43f2b00
d0020380:	f8dbaf28 			; <UNDEFINED> instruction: 0xf8dbaf28
d0020384:	2a002004 	bcs	0xd002839c
d0020388:	af23f43f 	svcge	0x0023f43f
d002038c:	1008f8db 	ldrdne	pc, [r8], -fp
d0020390:	bf98428a 	svclt	0x0098428a
d0020394:	31fff102 	mvnscc	pc, r2, lsl #2
d0020398:	545a2200 	ldrbpl	r2, [sl], #-512	; 0xfffffe00
d002039c:	0008f8db 	ldrdeq	pc, [r8], -fp
d00203a0:	e8bdb027 	pop	{r0, r1, r2, r5, ip, sp, pc}
d00203a4:	784c8ff0 	stmdavc	ip, {r4, r5, r6, r7, r8, r9, sl, fp, pc}^
d00203a8:	31012306 	tstcc	r1, r6, lsl #6
d00203ac:	f8d9e69e 			; <UNDEFINED> instruction: 0xf8d9e69e
d00203b0:	f9b33000 			; <UNDEFINED> instruction: 0xf9b33000
d00203b4:	1d1a0000 	ldcne	0, cr0, [sl, #-0]
d00203b8:	f8c917c1 			; <UNDEFINED> instruction: 0xf8c917c1
d00203bc:	e72a2000 	str	r2, [sl, -r0]!
d00203c0:	3000f8d9 	ldrdcc	pc, [r0], -r9
d00203c4:	0000f993 	muleq	r0, r3, r9
d00203c8:	17c11d1a 	bfine	r1, sl, (invalid: 26:1)
d00203cc:	2000f8c9 	andcs	pc, r0, r9, asr #17
d00203d0:	f8d9e721 			; <UNDEFINED> instruction: 0xf8d9e721
d00203d4:	1d183000 	ldcne	0, cr3, [r8, #-0]
d00203d8:	2300881a 	movwcs	r8, #2074	; 0x81a
d00203dc:	0000f8c9 	andeq	pc, r0, r9, asr #17
d00203e0:	f8d9e6d3 			; <UNDEFINED> instruction: 0xf8d9e6d3
d00203e4:	1d183000 	ldcne	0, cr3, [r8, #-0]
d00203e8:	2300781a 	movwcs	r7, #2074	; 0x81a
d00203ec:	0000f8c9 	andeq	pc, r0, r9, asr #17
d00203f0:	f898e6cb 			; <UNDEFINED> instruction: 0xf898e6cb
d00203f4:	f44f4001 	vst4.8	{d20-d23}, [pc], r1
d00203f8:	e6625500 	strbt	r5, [r2], -r0, lsl #10
d00203fc:	37fff04f 	ldrbcc	pc, [pc, pc, asr #32]!	; <UNPREDICTABLE>
d0020400:	e6634601 	strbt	r4, [r3], -r1, lsl #12
d0020404:	d0592c70 	subsle	r2, r9, r0, ror ip
d0020408:	d0722c73 	rsbsle	r2, r2, r3, ror ip
d002040c:	d0262c63 	eorle	r2, r6, r3, ror #24
d0020410:	0245f1a1 	subeq	pc, r5, #1073741864	; 0x40000028
d0020414:	d93f2a02 	ldmdble	pc!, {r1, r9, fp, sp}	; <UNPREDICTABLE>
d0020418:	f0002941 			; <UNDEFINED> instruction: 0xf0002941
d002041c:	2c6e80af 	stclcs	0, cr8, [lr], #-700	; 0xfffffd44
d0020420:	8216f000 	andshi	pc, r6, #0
d0020424:	21254658 			; <UNDEFINED> instruction: 0x21254658
d0020428:	f9def7ff 			; <UNDEFINED> instruction: 0xf9def7ff
d002042c:	46584621 	ldrbmi	r4, [r8], -r1, lsr #12
d0020430:	f9daf7ff 			; <UNDEFINED> instruction: 0xf9daf7ff
d0020434:	bf00e6bb 	svclt	0x0000e6bb
d0020438:	00082001 	andeq	r2, r8, r1
d002043c:	ffffffce 			; <UNDEFINED> instruction: 0xffffffce
d0020440:	cccccccd 	stclgt	12, cr12, [ip], {205}	; 0xcd
d0020444:	ffffffb4 			; <UNDEFINED> instruction: 0xffffffb4
d0020448:	2304788c 	movwcs	r7, #18572	; 0x488c
d002044c:	e64d3102 	strb	r3, [sp], -r2, lsl #2
d0020450:	2307784c 	movwcs	r7, #30796	; 0x784c
d0020454:	e6493101 	strb	r3, [r9], -r1, lsl #2
d0020458:	25004641 	strcs	r4, [r0, #-1601]	; 0xfffff9bf
d002045c:	2d01e631 	stccs	6, cr14, [r1, #-196]	; 0xffffff3c
d0020460:	2501bf38 	strcs	fp, [r1, #-3896]	; 0xfffff0c8
d0020464:	f10507f6 			; <UNDEFINED> instruction: 0xf10507f6
d0020468:	f14037ff 			; <UNDEFINED> instruction: 0xf14037ff
d002046c:	f8d9818b 			; <UNDEFINED> instruction: 0xf8d9818b
d0020470:	46583000 	ldrbmi	r3, [r8], -r0
d0020474:	1d1a3d02 	ldcne	13, cr3, [sl, #-8]
d0020478:	f8c97819 			; <UNDEFINED> instruction: 0xf8c97819
d002047c:	f7ff2000 			; <UNDEFINED> instruction: 0xf7ff2000
d0020480:	2f00f9b3 	svccs	0x0000f9b3
d0020484:	ae93f43f 	mrcge	4, 4, APSR_nzcv, cr3, cr15, {1}
d0020488:	46583d01 	ldrbmi	r3, [r8], -r1, lsl #26
d002048c:	f7ff2120 			; <UNDEFINED> instruction: 0xf7ff2120
d0020490:	1c68f9ab 			; <UNDEFINED> instruction: 0x1c68f9ab
d0020494:	e68ad1f8 			; <UNDEFINED> instruction: 0xe68ad1f8
d0020498:	0000f8d9 	ldrdeq	pc, [r0], -r9
d002049c:	462b4621 	strtmi	r4, [fp], -r1, lsr #12
d00204a0:	1dc44632 	stclne	6, cr4, [r4, #200]	; 0xc8
d00204a4:	f0244658 			; <UNDEFINED> instruction: 0xf0244658
d00204a8:	ed940407 	cfldrs	mvf0, [r4, #28]
d00204ac:	34080b00 	strcc	r0, [r8], #-2816	; 0xfffff500
d00204b0:	f8c99700 			; <UNDEFINED> instruction: 0xf8c99700
d00204b4:	f7ff4000 			; <UNDEFINED> instruction: 0xf7ff4000
d00204b8:	e678fb75 			; <UNDEFINED> instruction: 0xe678fb75
d00204bc:	3000f8d9 	ldrdcc	pc, [r0], -r9
d00204c0:	060cf026 	streq	pc, [ip], -r6, lsr #32
d00204c4:	21102401 	tstcs	r0, r1, lsl #8
d00204c8:	46581d1a 			; <UNDEFINED> instruction: 0x46581d1a
d00204cc:	2000f8c9 	andcs	pc, r0, r9, asr #17
d00204d0:	4663681a 			; <UNDEFINED> instruction: 0x4663681a
d00204d4:	f8cd9602 			; <UNDEFINED> instruction: 0xf8cd9602
d00204d8:	9704c014 	smladls	r4, r4, r0, ip
d00204dc:	f8cd9503 			; <UNDEFINED> instruction: 0xf8cd9503
d00204e0:	9406c004 	strls	ip, [r6], #-4
d00204e4:	f7ff9100 			; <UNDEFINED> instruction: 0xf7ff9100
d00204e8:	e660f9af 	strbt	pc, [r0], -pc, lsr #19	; <UNPREDICTABLE>
d00204ec:	27004601 	strcs	r4, [r0, -r1, lsl #12]
d00204f0:	f8d9e5ec 			; <UNDEFINED> instruction: 0xf8d9e5ec
d00204f4:	1d1a3000 	ldcne	0, cr3, [sl, #-0]
d00204f8:	2000f8c9 	andcs	pc, r0, r9, asr #17
d00204fc:	9314681b 	tstls	r4, #1769472	; 0x1b0000
d0020500:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d0020504:	781b813b 	ldmdavc	fp, {r0, r1, r3, r4, r5, r8, pc}
d0020508:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d002050c:	0ff88197 	svceq	0x00f88197
d0020510:	f0002f00 			; <UNDEFINED> instruction: 0xf0002f00
d0020514:	9a148193 	bls	0xd0540b68
d0020518:	f8122400 			; <UNDEFINED> instruction: 0xf8122400
d002051c:	34013f01 	strcc	r3, [r1], #-3841	; 0xfffff0ff
d0020520:	42bcb11b 	adcsmi	fp, ip, #-1073741818	; 0xc0000006
d0020524:	2800d3f9 	stmdacs	r0, {r0, r3, r4, r5, r6, r7, r8, r9, ip, lr, pc}
d0020528:	42a5d1f7 	adcmi	sp, r5, #-1073741763	; 0xc000003d
d002052c:	813df200 	teqhi	sp, r0, lsl #4	; <UNPREDICTABLE>
d0020530:	0301f016 	movweq	pc, #4118	; 0x1016	; <UNPREDICTABLE>
d0020534:	f0009312 			; <UNDEFINED> instruction: 0xf0009312
d0020538:	25008189 	strcs	r8, [r0, #-393]	; 0xfffffe77
d002053c:	95149b14 	ldrls	r9, [r4, #-2836]	; 0xfffff4ec
d0020540:	1e5e4625 	cdpne	6, 5, cr4, cr14, cr5, {1}
d0020544:	4637461c 			; <UNDEFINED> instruction: 0x4637461c
d0020548:	f8164658 			; <UNDEFINED> instruction: 0xf8164658
d002054c:	f7ff1f01 			; <UNDEFINED> instruction: 0xf7ff1f01
d0020550:	1cbbf94b 			; <UNDEFINED> instruction: 0x1cbbf94b
d0020554:	429d1b1b 	addsmi	r1, sp, #27648	; 0x6c00
d0020558:	9b12d8f5 	blls	0xd04d6934
d002055c:	2b009d14 	blcs	0xd00479b4
d0020560:	ae25f43f 	mcrge	4, 1, pc, cr5, cr15, {1}	; <UNPREDICTABLE>
d0020564:	2d001e6c 	stccs	14, cr1, [r0, #-432]	; 0xfffffe50
d0020568:	ae21f43f 	mcrge	4, 1, pc, cr1, cr15, {1}	; <UNPREDICTABLE>
d002056c:	21203c01 			; <UNDEFINED> instruction: 0x21203c01
d0020570:	f7ff4658 			; <UNDEFINED> instruction: 0xf7ff4658
d0020574:	1c67f939 			; <UNDEFINED> instruction: 0x1c67f939
d0020578:	e618d1f8 			; <UNDEFINED> instruction: 0xe618d1f8
d002057c:	3000f8d9 	ldrdcc	pc, [r0], -r9
d0020580:	f0233307 			; <UNDEFINED> instruction: 0xf0233307
d0020584:	ed930307 	ldc	3, cr0, [r3, #28]
d0020588:	33087b00 	movwcc	r7, #35584	; 0x8b00
d002058c:	0b17ec51 	bleq	0xd061b6d8
d0020590:	3000f8c9 	andcc	pc, r0, r9, asr #17
d0020594:	ee17460b 	cfmsub32	mvax0, mvfx4, mvfx7, mvfx11
d0020598:	2b002a10 	blcs	0xd002ade0
d002059c:	7b12ed8d 	blvc	0xd04dbbd8
d00205a0:	8176f2c0 	cmnhi	r6, r0, asr #5	; <UNPREDICTABLE>
d00205a4:	f1000771 			; <UNDEFINED> instruction: 0xf1000771
d00205a8:	00b18176 	adcseq	r8, r1, r6, ror r1
d00205ac:	0120f001 	msreq	CPSR_, r1
d00205b0:	f3c39114 	vorr.i32	d25, #180	; 0x000000b4
d00205b4:	920c510a 	andls	r5, ip, #-2147483646	; 0x80000002
d00205b8:	72fff240 	rscsvc	pc, pc, #64, 4
d00205bc:	0313f3c3 	tsteq	r3, #201326595	; 0xc000003	; <UNPREDICTABLE>
d00205c0:	42919116 	addsmi	r9, r1, #-2147483643	; 0x80000005
d00205c4:	f000930d 			; <UNDEFINED> instruction: 0xf000930d
d00205c8:	9b16817c 	blls	0xd05c0bc0
d00205cc:	bf142b00 	svclt	0x00142b00
d00205d0:	22002201 	andcs	r2, r0, #268435456	; 0x10000000
d00205d4:	f0009217 			; <UNDEFINED> instruction: 0xf0009217
d00205d8:	f2a38161 	vmla.f32	d8, d3, d1[1]
d00205dc:	2b0033ff 	blcs	0xd002d5e0
d00205e0:	bfb8931a 	svclt	0x00b8931a
d00205e4:	9312425b 	tstls	r2, #-1342177275	; 0xb0000005
d00205e8:	f0001c78 			; <UNDEFINED> instruction: 0xf0001c78
d00205ec:	f5b7818a 			; <UNDEFINED> instruction: 0xf5b7818a
d00205f0:	f3405f00 	vpmax.f32	d21, d0, d0
d00205f4:	f44f817d 	vst4.16	{d24,d26,d28,d30}, [pc :256]!
d00205f8:	e9dd5700 	ldmib	sp, {r8, r9, sl, ip, lr}^
d00205fc:	9715230c 	ldrls	r2, [r5, -ip, lsl #6]
d0020600:	230ae9cd 	movwcs	lr, #43469	; 0xa9cd
d0020604:	2100ab22 	tstcs	r0, r2, lsr #22
d0020608:	ee079a12 			; <UNDEFINED> instruction: 0xee079a12
d002060c:	4618ba90 			; <UNDEFINED> instruction: 0x4618ba90
d0020610:	fbaa9321 	blx	0xceac529e
d0020614:	4694c302 	ldrmi	ip, [r4], r2, lsl #6
d0020618:	3101468e 	smlabbcc	r1, lr, r6, r4
d002061c:	0bd3ea4f 	bleq	0xcf51af60
d0020620:	0f09f1bc 	svceq	0x0009f1bc
d0020624:	038beb0b 	orreq	lr, fp, #11264	; 0x2c00
d0020628:	0343eba2 	movteq	lr, #15266	; 0x3ba2
d002062c:	f103465a 			; <UNDEFINED> instruction: 0xf103465a
d0020630:	b2db0330 	sbcslt	r0, fp, #48, 6	; 0xc0000000
d0020634:	3b01f800 	blcc	0xd009e63c
d0020638:	ee17d8eb 	cdp	8, 1, cr13, cr7, cr11, {7}
d002063c:	931fba90 	tstls	pc, #144, 20	; 0x90000
d0020640:	e080f8cd 	add	pc, r0, sp, asr #17
d0020644:	f0002f00 			; <UNDEFINED> instruction: 0xf0002f00
d0020648:	f00681bd 			; <UNDEFINED> instruction: 0xf00681bd
d002064c:	22040310 	andcs	r0, r4, #16, 6	; 0x40000000
d0020650:	9b14931b 	blls	0xd05452c4
d0020654:	3b009815 	blcc	0xd00466b0
d0020658:	2301bf18 	movwcs	fp, #7960	; 0x1f18
d002065c:	44033302 	strmi	r3, [r3], #-770	; 0xfffffcfe
d0020660:	4413440b 	ldrmi	r4, [r3], #-1035	; 0xfffffbf5
d0020664:	f240429d 	vqsub.s8	d20, d16, d13
d0020668:	f00681b9 			; <UNDEFINED> instruction: 0xf00681b9
d002066c:	f0060101 			; <UNDEFINED> instruction: 0xf0060101
d0020670:	1aea0003 	bne	0xcfaa0684
d0020674:	0301f081 	movweq	pc, #4225	; 0x1081	; <UNPREDICTABLE>
d0020678:	901e9116 	andsls	r9, lr, r6, lsl r1
d002067c:	bf0c2802 	svclt	0x000c2802
d0020680:	f0032600 			; <UNDEFINED> instruction: 0xf0032600
d0020684:	92120601 	andsls	r0, r2, #1048576	; 0x100000
d0020688:	f0002e00 			; <UNDEFINED> instruction: 0xf0002e00
d002068c:	1e5581a5 	lognedp	f0, f5
d0020690:	f0002a00 			; <UNDEFINED> instruction: 0xf0002a00
d0020694:	3d0181b0 	stfccd	f0, [r1, #-704]	; 0xfffffd40
d0020698:	46582120 	ldrbmi	r2, [r8], -r0, lsr #2
d002069c:	f8a4f7ff 			; <UNDEFINED> instruction: 0xf8a4f7ff
d00206a0:	d1f81c69 	mvnsle	r1, r9, ror #24
d00206a4:	93162300 	tstls	r6, #0, 6
d00206a8:	2b009b14 	blcs	0xd0047300
d00206ac:	8185f040 	orrhi	pc, r5, r0, asr #32
d00206b0:	46582130 			; <UNDEFINED> instruction: 0x46582130
d00206b4:	f898f7ff 			; <UNDEFINED> instruction: 0xf898f7ff
d00206b8:	46582c41 	ldrbmi	r2, [r8], -r1, asr #24
d00206bc:	2158bf0c 	cmpcs	r8, ip, lsl #30
d00206c0:	f7ff2178 			; <UNDEFINED> instruction: 0xf7ff2178
d00206c4:	9b1ef891 	blls	0xd07de910
d00206c8:	d1022b02 	tstle	r2, r2, lsl #22
d00206cc:	f0402e00 			; <UNDEFINED> instruction: 0xf0402e00
d00206d0:	99178195 	ldmdbls	r7, {r0, r2, r4, r7, r8, pc}
d00206d4:	31304658 	teqcc	r0, r8, asr r6
d00206d8:	f7ffb2c9 			; <UNDEFINED> instruction: 0xf7ffb2c9
d00206dc:	9b15f885 	blls	0xd059e8f8
d00206e0:	43139a1b 	tstmi	r3, #110592	; 0x1b000
d00206e4:	212ed003 			; <UNDEFINED> instruction: 0x212ed003
d00206e8:	f7ff4658 			; <UNDEFINED> instruction: 0xf7ff4658
d00206ec:	2c41f87d 	mcrrcs	8, 7, pc, r1, cr13	; <UNPREDICTABLE>
d00206f0:	816ff000 	msrhi	SPSR_fsxc, r0
d00206f4:	f0002f00 			; <UNDEFINED> instruction: 0xf0002f00
d00206f8:	9e08821f 	mcrls	2, 0, r8, cr8, cr15, {0}
d00206fc:	250000bb 	strcs	r0, [r0, #-187]	; 0xffffff45
d0020700:	3b049415 	blcc	0xd014575c
d0020704:	e0069314 	and	r9, r6, r4, lsl r3
d0020708:	78193501 	ldmdavc	r9, {r0, r8, sl, ip, sp}
d002070c:	f7ff4658 			; <UNDEFINED> instruction: 0xf7ff4658
d0020710:	42aff86b 	adcmi	pc, pc, #7012352	; 0x6b0000
d0020714:	2d0cd064 	stccs	0, cr13, [ip, #-400]	; 0xfffffe70
d0020718:	dcf54633 	ldclle	6, cr4, [r5], #204	; 0xcc
d002071c:	7185ebc5 	orrvc	lr, r5, r5, asr #23
d0020720:	9c0a9b14 			; <UNDEFINED> instruction: 0x9c0a9b14
d0020724:	460a2f0c 	strmi	r2, [sl], -ip, lsl #30
d0020728:	0181ea4f 	orreq	lr, r1, pc, asr #20
d002072c:	0282eb03 	addeq	lr, r2, #3072	; 0xc00
d0020730:	0330f101 	teqeq	r0, #1073741824	; 0x40000000	; <UNPREDICTABLE>
d0020734:	0110f101 	tsteq	r0, r1, lsl #2	; <UNPREDICTABLE>
d0020738:	0020f1c2 	eoreq	pc, r0, r2, asr #3
d002073c:	0c20f1a2 	stfeqd	f7, [r0], #-648	; 0xfffffd78
d0020740:	f202fa24 	vpmax.s8	d15, d2, d20
d0020744:	f1c39c0b 			; <UNDEFINED> instruction: 0xf1c39c0b
d0020748:	fa040e20 	blx	0xd0123fd0
d002074c:	9c0cf000 	stcls	0, cr15, [ip], {-0}
d0020750:	f303fa24 	vpmax.u8	d15, d3, d20
d0020754:	ea429c0d 	b	0xd10c7790
d0020758:	980d0200 	stmdals	sp, {r9}
d002075c:	fe0efa04 	vseleq.f32	s30, s28, s8
d0020760:	fa209c0b 	blx	0xd0847794
d0020764:	fa24f101 	blx	0xd095cb70
d0020768:	ea43fc0c 	b	0xd111f7a0
d002076c:	dc32030e 	ldcle	3, cr0, [r2], #-56	; 0xffffffc8
d0020770:	020cea42 	andeq	lr, ip, #270336	; 0x42000
d0020774:	030ff002 	movweq	pc, #61442	; 0xf002	; <UNPREDICTABLE>
d0020778:	e7c54433 			; <UNDEFINED> instruction: 0xe7c54433
d002077c:	447b4bfb 	ldrbtmi	r4, [fp], #-3067	; 0xfffff405
d0020780:	e6c49314 			; <UNDEFINED> instruction: 0xe6c49314
d0020784:	b1373d02 	teqlt	r7, r2, lsl #26
d0020788:	21203d01 			; <UNDEFINED> instruction: 0x21203d01
d002078c:	f7ff4658 			; <UNDEFINED> instruction: 0xf7ff4658
d0020790:	1c6cf82b 	stclne	8, cr15, [ip], #-172	; 0xffffff54
d0020794:	f8d9d1f8 			; <UNDEFINED> instruction: 0xf8d9d1f8
d0020798:	46583000 	ldrbmi	r3, [r8], -r0
d002079c:	78191d1a 	ldmdavc	r9, {r1, r3, r4, r8, sl, fp, ip}
d00207a0:	2000f8c9 	andcs	pc, r0, r9, asr #17
d00207a4:	f820f7ff 			; <UNDEFINED> instruction: 0xf820f7ff
d00207a8:	f016e501 			; <UNDEFINED> instruction: 0xf016e501
d00207ac:	eba50301 	bl	0xce9613b8
d00207b0:	93120504 	tstls	r2, #4, 10	; 0x1000000
d00207b4:	aec2f47f 	mcrge	4, 6, pc, cr2, cr15, {3}	; <UNPREDICTABLE>
d00207b8:	b1351e6e 	teqlt	r5, lr, ror #28
d00207bc:	21203e01 			; <UNDEFINED> instruction: 0x21203e01
d00207c0:	f7ff4658 			; <UNDEFINED> instruction: 0xf7ff4658
d00207c4:	1c73f811 	ldclne	8, cr15, [r3], #-68	; 0xffffffbc
d00207c8:	2c00d1f8 	stfcsd	f5, [r0], {248}	; 0xf8
d00207cc:	aceff43f 	cfstrdge	mvd15, [pc], #252	; 0xd00208d0
d00207d0:	93122300 	tstls	r2, #0, 6
d00207d4:	430be6b2 	movwmi	lr, #46770	; 0xb6b2
d00207d8:	030ff003 	movweq	pc, #61443	; 0xf003	; <UNPREDICTABLE>
d00207dc:	e7934433 			; <UNDEFINED> instruction: 0xe7934433
d00207e0:	2c419c15 	mcrrcs	12, 1, r9, r1, cr5
d00207e4:	2150bf0c 	cmpcs	r0, ip, lsl #30
d00207e8:	46582170 			; <UNDEFINED> instruction: 0x46582170
d00207ec:	fffcf7fe 			; <UNDEFINED> instruction: 0xfffcf7fe
d00207f0:	9d219b1a 	vstmdbls	r1!, {d9-d21}
d00207f4:	2b004658 	blcs	0xd003215c
d00207f8:	461c9b20 	ldrmi	r9, [ip], -r0, lsr #22
d00207fc:	212dbfb4 			; <UNDEFINED> instruction: 0x212dbfb4
d0020800:	f7fe212b 			; <UNDEFINED> instruction: 0xf7fe212b
d0020804:	442cfff1 	strtmi	pc, [ip], #-4081	; 0xfffff00f
d0020808:	e001991f 	and	r9, r1, pc, lsl r9
d002080c:	1d01f814 	stcne	8, cr15, [r1, #-80]	; 0xffffffb0
d0020810:	f7fe4658 			; <UNDEFINED> instruction: 0xf7fe4658
d0020814:	42a5ffe9 	adcmi	pc, r5, #932	; 0x3a4
d0020818:	9b16d1f8 	blls	0xd05d5000
d002081c:	f43f2b00 			; <UNDEFINED> instruction: 0xf43f2b00
d0020820:	9b12acc6 	blls	0xd04cbb40
d0020824:	2b001e5c 	blcs	0xd002819c
d0020828:	acc1f43f 	cfstrdge	mvd15, [r1], {63}	; 0x3f
d002082c:	21203c01 			; <UNDEFINED> instruction: 0x21203c01
d0020830:	f7fe4658 			; <UNDEFINED> instruction: 0xf7fe4658
d0020834:	1c63ffd9 	stclne	15, cr15, [r3], #-868	; 0xfffffc9c
d0020838:	e4b8d1f8 	ldrt	sp, [r8], #504	; 0x1f8
d002083c:	f43f2d00 			; <UNDEFINED> instruction: 0xf43f2d00
d0020840:	07f2acb6 			; <UNDEFINED> instruction: 0x07f2acb6
d0020844:	817af140 	cmnhi	sl, r0, asr #2	; <UNPREDICTABLE>
d0020848:	e68f1e6c 	str	r1, [pc], ip, ror #28
d002084c:	e7bc9d12 			; <UNDEFINED> instruction: 0xe7bc9d12
d0020850:	f8db3b01 			; <UNDEFINED> instruction: 0xf8db3b01
d0020854:	2b062008 	blcs	0xd01a887c
d0020858:	e8dfd812 	ldm	pc, {r1, r4, fp, ip, lr, pc}^	; <UNPREDICTABLE>
d002085c:	014bf013 	cmpeq	fp, r3, lsl r0	; <UNPREDICTABLE>
d0020860:	00110142 	andseq	r0, r1, r2, asr #2
d0020864:	00110007 	andseq	r0, r1, r7
d0020868:	00070011 	andeq	r0, r7, r1, lsl r0
d002086c:	3000f8d9 	ldrdcc	pc, [r0], -r9
d0020870:	1d182100 	ldfnes	f2, [r8, #-0]
d0020874:	0000f8c9 	andeq	pc, r0, r9, asr #17
d0020878:	e9c3681b 	stmib	r3, {r0, r1, r3, r4, fp, sp, lr}^
d002087c:	e4962100 	ldr	r2, [r6], #256	; 0x100
d0020880:	3000f8d9 	ldrdcc	pc, [r0], -r9
d0020884:	f8c91d19 			; <UNDEFINED> instruction: 0xf8c91d19
d0020888:	681b1000 	ldmdavs	fp, {ip}
d002088c:	e48e601a 	str	r6, [lr], #26
d0020890:	9114212d 	tstls	r4, sp, lsr #2
d0020894:	212be68d 	smlawbcs	fp, sp, r6, lr
d0020898:	e68a9114 	pkhbt	r9, sl, r4, lsl #2
d002089c:	010ce9dd 	ldrdeq	lr, [ip, -sp]
d00208a0:	32fef240 	rscscc	pc, lr, #64, 4
d00208a4:	0301ea50 	movweq	lr, #6736	; 0x1a50
d00208a8:	48af9916 	stmiami	pc!, {r1, r2, r4, r8, fp, ip, pc}	; <UNPREDICTABLE>
d00208ac:	460bbf0c 	strmi	fp, [fp], -ip, lsl #30
d00208b0:	93124613 	tstls	r2, #19922944	; 0x1300000
d00208b4:	230ce9dd 	movwcs	lr, #51677	; 0xc9dd
d00208b8:	460bbf0c 	strmi	fp, [fp], -ip, lsl #30
d00208bc:	931a4603 	tstls	sl, #3145728	; 0x300000
d00208c0:	2c41e692 	mcrrcs	6, 9, lr, r1, cr2
d00208c4:	4632462b 	ldrtmi	r4, [r2], -fp, lsr #12
d00208c8:	bf0c4658 	svclt	0x000c4658
d00208cc:	21662146 	cmncs	r6, r6, asr #2
d00208d0:	ed9d9700 	ldc	7, cr9, [sp]
d00208d4:	f7ff0b12 			; <UNDEFINED> instruction: 0xf7ff0b12
d00208d8:	e468f965 	strbt	pc, [r8], #-2405	; 0xfffff69b	; <UNPREDICTABLE>
d00208dc:	463b4631 			; <UNDEFINED> instruction: 0x463b4631
d00208e0:	f8cd462c 			; <UNDEFINED> instruction: 0xf8cd462c
d00208e4:	9e158048 	cdpls	0, 1, cr8, cr5, cr8, {2}
d00208e8:	461746c8 	ldrmi	r4, [r7], -r8, asr #13
d00208ec:	460d4699 			; <UNDEFINED> instruction: 0x460d4699
d00208f0:	f3402f0c 	vpmax.f32	d18, d0, d12
d00208f4:	97158090 			; <UNDEFINED> instruction: 0x97158090
d00208f8:	230ce9dd 	movwcs	lr, #51677	; 0xc9dd
d00208fc:	230ae9cd 	movwcs	lr, #43469	; 0xa9cd
d0020900:	270de680 	strcs	lr, [sp, -r0, lsl #13]
d0020904:	46494628 	strbmi	r4, [r9], -r8, lsr #12
d0020908:	46c12300 	strbmi	r2, [r1], r0, lsl #6
d002090c:	9615463a 			; <UNDEFINED> instruction: 0x9615463a
d0020910:	4625469e 			; <UNDEFINED> instruction: 0x4625469e
d0020914:	8048f8dd 	ldrdhi	pc, [r8], #-141	; 0xffffff73
d0020918:	4606460f 	strmi	r4, [r6], -pc, lsl #12
d002091c:	0c20f1c3 	stfeqd	f7, [r0], #-780	; 0xfffffcf4
d0020920:	990c980d 	stmdbls	ip, {r0, r2, r3, fp, ip, pc}
d0020924:	0420f1a3 	strteq	pc, [r0], #-419	; 0xfffffe5d
d0020928:	fc0cfa00 	stc2	10, cr15, [ip], {-0}	; <UNPREDICTABLE>
d002092c:	40e040d9 	ldrdmi	r4, [r0], #9	; <UNPREDICTABLE>
d0020930:	ea413304 	b	0xd106d548
d0020934:	4301010c 	movwmi	r0, #4364	; 0x110c
d0020938:	010ff001 	tsteq	pc, r1	; <UNPREDICTABLE>
d002093c:	1e0ae9cd 	vmlsne.f16	s28, s21, s26	; <UNPREDICTABLE>
d0020940:	010ae9dd 	ldrdeq	lr, [sl, -sp]
d0020944:	d1c94301 	bicle	r4, r9, r1, lsl #6
d0020948:	d1e73a01 	mvnle	r3, r1, lsl #20
d002094c:	f8cd463b 			; <UNDEFINED> instruction: 0xf8cd463b
d0020950:	46178048 	ldrmi	r8, [r7], -r8, asr #32
d0020954:	469946c8 	ldrmi	r4, [r9], r8, asr #13
d0020958:	462c4631 			; <UNDEFINED> instruction: 0x462c4631
d002095c:	460d9e15 			; <UNDEFINED> instruction: 0x460d9e15
d0020960:	e9dd9715 	ldmib	sp, {r0, r2, r4, r8, r9, sl, ip, pc}^
d0020964:	e9cd230c 	stmib	sp, {r2, r3, r8, r9, sp}^
d0020968:	22012318 	andcs	r2, r1, #24, 6	; 0x60000000
d002096c:	e9cd2300 	stmib	sp, {r8, r9, sp}^
d0020970:	22002310 	andcs	r2, r0, #16, 6	; 0x40000000
d0020974:	2300f44f 	movwcs	pc, #1103	; 0x44f	; <UNPREDICTABLE>
d0020978:	230ee9cd 	movwcs	lr, #59853	; 0xe9cd
d002097c:	230ee9dd 	movwcs	lr, #59869	; 0xe9dd
d0020980:	0118e9dd 			; <UNDEFINED> instruction: 0x0118e9dd
d0020984:	bf08428b 	svclt	0x0008428b
d0020988:	f0c04282 			; <UNDEFINED> instruction: 0xf0c04282
d002098c:	429980c1 	addsmi	r8, r9, #193	; 0xc1
d0020990:	4290bf08 	addsmi	fp, r0, #8, 30
d0020994:	80b7f000 	adcshi	pc, r7, r0
d0020998:	230ae9dd 	movwcs	lr, #43485	; 0xa9dd
d002099c:	0110e9dd 			; <UNDEFINED> instruction: 0x0110e9dd
d00209a0:	bf08428b 	svclt	0x0008428b
d00209a4:	f47f4282 			; <UNDEFINED> instruction: 0xf47f4282
d00209a8:	9b17ae2d 	blls	0xd060c264
d00209ac:	33012200 	movwcc	r2, #4608	; 0x1200
d00209b0:	23009317 	movwcs	r9, #791	; 0x317
d00209b4:	230ae9cd 	movwcs	lr, #43469	; 0xa9cd
d00209b8:	4619e624 	ldrmi	lr, [r9], -r4, lsr #12
d00209bc:	f7fe4658 			; <UNDEFINED> instruction: 0xf7fe4658
d00209c0:	e675ff13 	uhadd16	pc, r5, r3	; <UNPREDICTABLE>
d00209c4:	0310f016 	tsteq	r0, #22	; <UNPREDICTABLE>
d00209c8:	2204bf14 	andcs	fp, r4, #20, 30	; 0x50
d00209cc:	931b2203 	tstls	fp, #805306368	; 0x30000000
d00209d0:	b177e63f 	cmnlt	r7, pc, lsr r6
d00209d4:	e6919e09 	ldr	r9, [r1], r9, lsl #28
d00209d8:	e665461e 			; <UNDEFINED> instruction: 0xe665461e
d00209dc:	0203f006 	andeq	pc, r3, #6
d00209e0:	0301f006 	movweq	pc, #4102	; 0x1006	; <UNPREDICTABLE>
d00209e4:	2200921e 	andcs	r9, r0, #-536870911	; 0xe0000001
d00209e8:	0601f083 	streq	pc, [r1], -r3, lsl #1
d00209ec:	92129316 	andsls	r9, r2, #1476395008	; 0x58000000
d00209f0:	2150e65a 	cmpcs	r0, sl, asr r6
d00209f4:	9b12e6f9 	blls	0xd04da5e0
d00209f8:	e6559316 			; <UNDEFINED> instruction: 0xe6559316
d00209fc:	1e5d9b12 	vmovne.s8	r9, d13[0]
d0020a00:	f43f2b00 			; <UNDEFINED> instruction: 0xf43f2b00
d0020a04:	3d01ae66 	stccc	14, cr10, [r1, #-408]	; 0xfffffe68
d0020a08:	46582130 			; <UNDEFINED> instruction: 0x46582130
d0020a0c:	feecf7fe 	mcr2	7, 7, pc, cr12, cr14, {7}	; <UNPREDICTABLE>
d0020a10:	d1f81c6a 	mvnsle	r1, sl, ror #24
d0020a14:	f1c7e65d 			; <UNDEFINED> instruction: 0xf1c7e65d
d0020a18:	e9dd030d 	ldmib	sp, {r0, r2, r3, r8, r9}^
d0020a1c:	009b120c 	addseq	r1, fp, ip, lsl #4
d0020a20:	f1c34618 			; <UNDEFINED> instruction: 0xf1c34618
d0020a24:	f1a30c20 			; <UNDEFINED> instruction: 0xf1a30c20
d0020a28:	460b0e20 	strmi	r0, [fp], -r0, lsr #28
d0020a2c:	fc0cfa02 	stc2	10, cr15, [ip], {2}	; <UNPREDICTABLE>
d0020a30:	32fff04f 	rscscc	pc, pc, #79	; 0x4f
d0020a34:	f1a040c3 			; <UNDEFINED> instruction: 0xf1a040c3
d0020a38:	930a0120 	movwls	r0, #41248	; 0xa120
d0020a3c:	33fff04f 	mvnscc	pc, #79	; 0x4f
d0020a40:	fe0efa03 	vseleq.f32	s30, s28, s6
d0020a44:	f300fa02 	vpmax.u8	d15, d0, d2
d0020a48:	ea429a0a 	b	0xd10c7278
d0020a4c:	f1c0020c 			; <UNDEFINED> instruction: 0xf1c0020c
d0020a50:	920a0c20 	andls	r0, sl, #32, 24	; 0x2000
d0020a54:	fa229a0d 	blx	0xd08c7290
d0020a58:	ea43f101 	b	0xd111ce64
d0020a5c:	f04f020e 			; <UNDEFINED> instruction: 0xf04f020e
d0020a60:	fa2333ff 	blx	0xd08eda64
d0020a64:	4603fc0c 	strmi	pc, [r3], -ip, lsl #24
d0020a68:	30fff04f 	rscscc	pc, pc, pc, asr #32
d0020a6c:	0e21f1a3 	abseqdp	f7, f3
d0020a70:	40989315 	addsmi	r9, r8, r5, lsl r3
d0020a74:	ea429b0a 	b	0xd10c76a4
d0020a78:	430b020c 	movwmi	r0, #45580	; 0xb20c
d0020a7c:	921b2101 	andsls	r2, fp, #1073741824	; 0x40000000
d0020a80:	9b0c930a 	blls	0xd03456b0
d0020a84:	ea239a15 	b	0xd09072e0
d0020a88:	00b80300 	adcseq	r0, r8, r0, lsl #6
d0020a8c:	0c21f1c2 	stfeqd	f7, [r1], #-776	; 0xfffffcf8
d0020a90:	93189715 	tstls	r8, #5505024	; 0x540000
d0020a94:	f30efa01 	vpmax.u8	d15, d14, d1
d0020a98:	0e20f1a0 	abseqdp	f7, f0
d0020a9c:	fc0cfa21 	stc2	10, cr15, [ip], {33}	; 0x21	; <UNPREDICTABLE>
d0020aa0:	9b0d930f 	blls	0xd03856e4
d0020aa4:	930b40d3 	movwls	r4, #45267	; 0xb0d3
d0020aa8:	f30efa01 	vpmax.u8	d15, d14, d1
d0020aac:	0e20f1c0 	abseqdm	f7, f0
d0020ab0:	9b0f9311 	blls	0xd04056fc
d0020ab4:	fe0efa21 	vseleq.f32	s30, s28, s3
d0020ab8:	030cea43 	movweq	lr, #51779	; 0xca43
d0020abc:	3cfff102 	ldfccp	f7, [pc], #8	; 0xd0020acc
d0020ac0:	930f9a1b 	movwls	r9, #64027	; 0xfa1b
d0020ac4:	ea239b0d 	b	0xd0907700
d0020ac8:	fa010202 	blx	0xd00612d8
d0020acc:	930ef30c 	movwls	pc, #58124	; 0xe30c	; <UNPREDICTABLE>
d0020ad0:	92199b11 	andsls	r9, r9, #17408	; 0x4400
d0020ad4:	030eea43 	movweq	lr, #59971	; 0xea43
d0020ad8:	fa019311 	blx	0xd0085724
d0020adc:	9310f300 	tstls	r0, #0, 6	; <UNPREDICTABLE>
d0020ae0:	f8d9e74c 			; <UNDEFINED> instruction: 0xf8d9e74c
d0020ae4:	1d193000 	ldcne	0, cr3, [r9, #-0]
d0020ae8:	1000f8c9 	andne	pc, r0, r9, asr #17
d0020aec:	801a681b 	andshi	r6, sl, fp, lsl r8
d0020af0:	bb5df7ff 	bllt	0xd179eaf4
d0020af4:	3000f8d9 	ldrdcc	pc, [r0], -r9
d0020af8:	f8c91d19 			; <UNDEFINED> instruction: 0xf8c91d19
d0020afc:	681b1000 	ldmdavs	fp, {ip}
d0020b00:	f7ff701a 			; <UNDEFINED> instruction: 0xf7ff701a
d0020b04:	b95fbb54 	ldmdblt	pc, {r2, r4, r6, r8, r9, fp, ip, sp, pc}^	; <UNPREDICTABLE>
d0020b08:	2b009b16 	blcs	0xd0047768
d0020b0c:	af44f43f 	svcge	0x0044f43f
d0020b10:	33019b0a 	movwcc	r9, #6922	; 0x1b0a
d0020b14:	9b0b930a 	blls	0xd0305744
d0020b18:	0300f143 	movweq	pc, #323	; 0x143	; <UNPREDICTABLE>
d0020b1c:	e73b930b 	ldr	r9, [fp, -fp, lsl #6]!
d0020b20:	f0039b0a 			; <UNDEFINED> instruction: 0xf0039b0a
d0020b24:	931c0301 	tstls	ip, #67108864	; 0x4000000
d0020b28:	931d2300 	tstls	sp, #0, 6
d0020b2c:	231ce9dd 	tstcs	ip, #3620864	; 0x374000
d0020b30:	f43f4313 			; <UNDEFINED> instruction: 0xf43f4313
d0020b34:	e7ebaf31 			; <UNDEFINED> instruction: 0xe7ebaf31
d0020b38:	e6562170 			; <UNDEFINED> instruction: 0xe6562170
d0020b3c:	24001e6e 	strcs	r1, [r0], #-3694	; 0xfffff192
d0020b40:	f8d9e63c 			; <UNDEFINED> instruction: 0xf8d9e63c
d0020b44:	23000000 	movwcs	r0, #0
d0020b48:	30046802 	andcc	r6, r4, r2, lsl #16
d0020b4c:	0000f8c9 	andeq	pc, r0, r9, asr #17
d0020b50:	bb1bf7ff 	bllt	0xd071eb54
d0020b54:	3000f8d9 	ldrdcc	pc, [r0], -r9
d0020b58:	33046818 	movwcc	r6, #18456	; 0x4818
d0020b5c:	f8c917c1 			; <UNDEFINED> instruction: 0xf8c917c1
d0020b60:	f7ff3000 			; <UNDEFINED> instruction: 0xf7ff3000
d0020b64:	bf00bb58 	svclt	0x0000bb58
d0020b68:	fffffc02 			; <UNDEFINED> instruction: 0xfffffc02
d0020b6c:	fffff88e 			; <UNDEFINED> instruction: 0xfffff88e

Disassembly of section .text.vsnprintf:

d0020b70 <.text.vsnprintf>:
d0020b70:	b0a7b5f0 	strdlt	fp, [r7], r0	; <UNPREDICTABLE>
d0020b74:	460e4607 	strmi	r4, [lr], -r7, lsl #12
d0020b78:	4614461d 			; <UNDEFINED> instruction: 0x4614461d
d0020b7c:	228c2100 	addcs	r2, ip, #0, 2
d0020b80:	f7fea803 			; <UNDEFINED> instruction: 0xf7fea803
d0020b84:	9701fc2f 	strls	pc, [r1, -pc, lsr #24]
d0020b88:	95009602 	strls	r9, [r0, #-1538]	; 0xfffff9fe
d0020b8c:	4621b134 			; <UNDEFINED> instruction: 0x4621b134
d0020b90:	a801466a 	stmdage	r1, {r1, r3, r5, r6, r9, sl, lr}
d0020b94:	fa54f7ff 	blx	0xd155eb98
d0020b98:	bdf0b027 	ldcllt	0, cr11, [r0, #156]!	; 0x9c
d0020b9c:	30fff04f 	rscscc	pc, pc, pc, asr #32
d0020ba0:	bf00e7fa 	svclt	0x0000e7fa

Disassembly of section .text.snprintf:

d0020ba4 <.text.snprintf>:
d0020ba4:	b500b40c 	strlt	fp, [r0, #-1036]	; 0xfffffbf4
d0020ba8:	ab04b083 	blge	0xd014cdbc
d0020bac:	2b04f853 	blcs	0xd015ed00
d0020bb0:	f7ff9301 			; <UNDEFINED> instruction: 0xf7ff9301
d0020bb4:	b003ffdd 	ldrdlt	pc, [r3], -sp
d0020bb8:	eb04f85d 	bl	0xd015ed34
d0020bbc:	4770b002 	ldrbmi	fp, [r0, -r2]!

Disassembly of section .text.memchr:

d0020be8 <.text.memchr>:
d0020be8:	4603b192 			; <UNDEFINED> instruction: 0x4603b192
d0020bec:	b410b2c9 	ldrlt	fp, [r0], #-713	; 0xfffffd37
d0020bf0:	e0011884 	and	r1, r1, r4, lsl #17
d0020bf4:	d00742a3 	andle	r4, r7, r3, lsr #5
d0020bf8:	f8134618 			; <UNDEFINED> instruction: 0xf8134618
d0020bfc:	428a2b01 	addmi	r2, sl, #1024	; 0x400
d0020c00:	f85dd1f8 			; <UNDEFINED> instruction: 0xf85dd1f8
d0020c04:	47704b04 	ldrbmi	r4, [r0, -r4, lsl #22]!
d0020c08:	f85d2000 			; <UNDEFINED> instruction: 0xf85d2000
d0020c0c:	47704b04 	ldrbmi	r4, [r0, -r4, lsl #22]!
d0020c10:	47704610 			; <UNDEFINED> instruction: 0x47704610

Disassembly of section .text.strlen:

d0020c14 <.text.strlen>:
d0020c14:	b1327802 	teqlt	r2, r2, lsl #16
d0020c18:	f8134603 			; <UNDEFINED> instruction: 0xf8134603
d0020c1c:	29001f01 	stmdbcs	r0, {r0, r8, r9, sl, fp, ip}
d0020c20:	1a18d1fb 	bne	0xd0655414
d0020c24:	46104770 			; <UNDEFINED> instruction: 0x46104770
d0020c28:	bf004770 	svclt	0x00004770

Disassembly of section .text.strcmp:

d0020c2c <.text.strcmp>:
d0020c2c:	b1937803 	orrslt	r7, r3, r3, lsl #16
d0020c30:	e002b410 	and	fp, r2, r0, lsl r4
d0020c34:	3f01f810 	svccc	0x0001f810
d0020c38:	460cb143 	strmi	fp, [ip], -r3, asr #2
d0020c3c:	2b01f811 	blcs	0xd009ec88
d0020c40:	d0f7429a 	smlalsle	r4, r7, sl, r2
d0020c44:	f85d1a98 			; <UNDEFINED> instruction: 0xf85d1a98
d0020c48:	47704b04 	ldrbmi	r4, [r0, -r4, lsl #22]!
d0020c4c:	f85d7862 			; <UNDEFINED> instruction: 0xf85d7862
d0020c50:	1a984b04 	bne	0xce633868
d0020c54:	780a4770 	stmdavc	sl, {r4, r5, r6, r8, r9, sl, lr}
d0020c58:	47701a98 			; <UNDEFINED> instruction: 0x47701a98

Disassembly of section .text.strchr:

d0020c5c <.text.strchr>:
d0020c5c:	7803b2c9 	stmdavc	r3, {r0, r3, r6, r7, r9, ip, sp, pc}
d0020c60:	d0064299 	mulle	r6, r9, r2
d0020c64:	f810b123 			; <UNDEFINED> instruction: 0xf810b123
d0020c68:	428b3f01 	addmi	r3, fp, #1, 30
d0020c6c:	4770d1fa 			; <UNDEFINED> instruction: 0x4770d1fa
d0020c70:	47704618 			; <UNDEFINED> instruction: 0x47704618

Disassembly of section .text.strrchr:

d0020c74 <.text.strrchr>:
d0020c74:	b2c92200 	sbclt	r2, r9, #0, 4
d0020c78:	4604b410 			; <UNDEFINED> instruction: 0x4604b410
d0020c7c:	3b01f810 	blcc	0xd009ecc4
d0020c80:	bf08428b 	svclt	0x0008428b
d0020c84:	2b004622 	blcs	0xd0032514
d0020c88:	4610d1f7 			; <UNDEFINED> instruction: 0x4610d1f7
d0020c8c:	4b04f85d 	blmi	0xd015ee08
d0020c90:	bf004770 	svclt	0x00004770
