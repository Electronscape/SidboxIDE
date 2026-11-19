
/mnt/LinuxDatas/work/SidboxIDE/SidboxIDE/development/Sidbox-C-Compiler-SDK-F5/compiler/build/cgarm/compiler-cgarm/compiler.elf:     file format elf32-littlearm


Disassembly of section .text.read_file:

d0018528 <.text.read_file>:
d0018528:	41ffe92d 	mvnsmi	lr, sp, lsr #18
d001852c:	4b1a461e 	blmi	0xd06a9dac
d0018530:	4690460f 	ldrmi	r4, [r0], pc, lsl #12
d0018534:	aa01685b 	bge	0xd00726a8
d0018538:	681d2101 	ldmdavs	sp, {r0, r8, sp}
d001853c:	47986bab 	ldrmi	r6, [r8, fp, lsr #23]
d0018540:	4604b120 	strmi	fp, [r4], -r0, lsr #2
d0018544:	b0044620 	andlt	r4, r4, r0, lsr #12
d0018548:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d001854c:	0002e9cd 	andeq	lr, r2, sp, asr #19
d0018550:	a9026ceb 	stmdbge	r2, {r0, r1, r3, r5, r6, r7, sl, fp, sp, lr}
d0018554:	47989801 	ldrmi	r9, [r8, r1, lsl #16]
d0018558:	b9784604 	ldmdblt	r8!, {r2, r9, sl, lr}^
d001855c:	45429a02 	strbmi	r9, [r2, #-2562]	; 0xfffff5fe
d0018560:	b15ad817 	cmplt	sl, r7, lsl r8
d0018564:	ab036bec 	blge	0xd00f351c
d0018568:	98014639 	stmdals	r1, {r0, r3, r4, r5, r9, sl, lr}
d001856c:	460447a0 	strmi	r4, [r4], -r0, lsr #15
d0018570:	e9ddb920 	ldmib	sp, {r5, r8, fp, ip, sp, pc}^
d0018574:	1a240402 	bne	0xd0919584
d0018578:	2401bf18 	strcs	fp, [r1], #-3864	; 0xfffff0e8
d001857c:	98016d6b 	stmdals	r1, {r0, r1, r3, r5, r6, r8, sl, fp, sp, lr}
d0018580:	2c004798 	stccs	7, cr4, [r0], {152}	; 0x98
d0018584:	4604d1de 			; <UNDEFINED> instruction: 0x4604d1de
d0018588:	d1db2800 	bicsle	r2, fp, r0, lsl #16
d001858c:	60339b02 	eorsvs	r9, r3, r2, lsl #22
d0018590:	f06fe7d8 			; <UNDEFINED> instruction: 0xf06fe7d8
d0018594:	e7f10402 	ldrb	r0, [r1, r2, lsl #8]!
d0018598:	2001f000 	andcs	pc, r1, r0

Disassembly of section .text.read_apicore:

d00185bc <.text.read_apicore>:
d00185bc:	460ab507 	strmi	fp, [sl], -r7, lsl #10
d00185c0:	48064601 	stmdami	r6, {r0, r9, sl, lr}
d00185c4:	4478ab01 	ldrbtmi	sl, [r8], #-2817	; 0xfffff4ff
d00185c8:	ffaef7ff 			; <UNDEFINED> instruction: 0xffaef7ff
d00185cc:	9801b918 	stmdals	r1, {r3, r4, r8, fp, ip, sp, pc}
d00185d0:	f85db003 			; <UNDEFINED> instruction: 0xf85db003
d00185d4:	2000fb04 	andcs	pc, r0, r4, lsl #22
d00185d8:	bf00e7fa 	svclt	0x0000e7fa
d00185dc:	ffffffd2 			; <UNDEFINED> instruction: 0xffffffd2

Disassembly of section .text.write_file:

d00185f4 <.text.write_file>:
d00185f4:	47ffe92d 	ldrbmi	lr, [pc, sp, lsr #18]!
d00185f8:	46074b4a 	strmi	r4, [r7], -sl, asr #22
d00185fc:	46154688 	ldrmi	r4, [r5], -r8, lsl #13
d0018600:	681e685b 	ldmdavs	lr, {r0, r1, r3, r4, r6, fp, sp, lr}
d0018604:	fbb6f002 	blx	0xcedd4616
d0018608:	03f7f1a0 	mvnseq	pc, #160, 2	; 0x28
d001860c:	f5134604 			; <UNDEFINED> instruction: 0xf5134604
d0018610:	f2407f81 	vmax.f32	d23, d16, d1
d0018614:	f8df8084 			; <UNDEFINED> instruction: 0xf8df8084
d0018618:	46029110 			; <UNDEFINED> instruction: 0x46029110
d001861c:	f8df4639 			; <UNDEFINED> instruction: 0xf8df4639
d0018620:	44f9a10c 	ldrbtmi	sl, [r9], #268	; 0x10c
d0018624:	464844fa 			; <UNDEFINED> instruction: 0x464844fa
d0018628:	ff9cf000 			; <UNDEFINED> instruction: 0xff9cf000
d001862c:	220a4940 	andcs	r4, sl, #64, 18	; 0x100000
d0018630:	0004eb09 	andeq	lr, r4, r9, lsl #22
d0018634:	f0004479 			; <UNDEFINED> instruction: 0xf0004479
d0018638:	4622ff95 	qadd8mi	pc, r2, r5	; <UNPREDICTABLE>
d001863c:	46504639 			; <UNDEFINED> instruction: 0x46504639
d0018640:	ff90f000 			; <UNDEFINED> instruction: 0xff90f000
d0018644:	220a493b 	andcs	r4, sl, #966656	; 0xec000
d0018648:	0004eb0a 	andeq	lr, r4, sl, lsl #22
d001864c:	f0004479 			; <UNDEFINED> instruction: 0xf0004479
d0018650:	6bb3ff89 	blvs	0xced1847c
d0018654:	2106aa01 	tstcs	r6, r1, lsl #20
d0018658:	47984648 	ldrmi	r4, [r8, r8, asr #12]
d001865c:	4604b120 	strmi	fp, [r4], -r0, lsr #2
d0018660:	b0044620 	andlt	r4, r4, r0, lsr #12
d0018664:	87f0e8bd 			; <UNDEFINED> instruction: 0x87f0e8bd
d0018668:	b9759002 	ldmdblt	r5!, {r1, ip, pc}^
d001866c:	98016d33 	stmdals	r1, {r0, r1, r4, r5, r8, sl, fp, sp, lr}
d0018670:	46044798 			; <UNDEFINED> instruction: 0x46044798
d0018674:	98016d73 	stmdals	r1, {r0, r1, r4, r5, r6, r8, sl, fp, sp, lr}
d0018678:	b90c4798 	stmdblt	ip, {r3, r4, r7, r8, r9, sl, lr}
d001867c:	4604b198 			; <UNDEFINED> instruction: 0x4604b198
d0018680:	6db3482d 	ldcvs	8, cr4, [r3, #180]!	; 0xb4
d0018684:	47984478 			; <UNDEFINED> instruction: 0x47984478
d0018688:	6c34e7ea 	ldcvs	7, cr14, [r4], #-936	; 0xfffffc58
d001868c:	462aab02 	strtmi	sl, [sl], -r2, lsl #22
d0018690:	98014641 	stmdals	r1, {r0, r6, r9, sl, lr}
d0018694:	460447a0 	strmi	r4, [r4], -r0, lsr #15
d0018698:	d1eb2800 	mvnle	r2, r0, lsl #16
d001869c:	42ab9b02 	adcmi	r9, fp, #2048	; 0x800
d00186a0:	2401d0e4 	strcs	sp, [r1], #-228	; 0xffffff1c
d00186a4:	6ab3e7e6 	bvs	0xced12644
d00186a8:	a9034622 	stmdbge	r3, {r1, r5, r9, sl, lr}
d00186ac:	94034638 	strls	r4, [r3], #-1592	; 0xfffff9c8
d00186b0:	46054798 			; <UNDEFINED> instruction: 0x46054798
d00186b4:	9b03b980 	blls	0xd0106cbc
d00186b8:	d42407db 	strtle	r0, [r4], #-2011	; 0xfffff825
d00186bc:	4638491f 			; <UNDEFINED> instruction: 0x4638491f
d00186c0:	44796df3 	ldrbtmi	r6, [r9], #-3571	; 0xfffff20d
d00186c4:	46054798 			; <UNDEFINED> instruction: 0x46054798
d00186c8:	481db1d8 	ldmdami	sp, {r3, r4, r6, r7, r8, ip, sp, pc}
d00186cc:	44786db3 	ldrbtmi	r6, [r8], #-3507	; 0xfffff24d
d00186d0:	b9d44798 	ldmiblt	r4, {r3, r4, r7, r8, r9, sl, lr}^
d00186d4:	e7c3462c 	strb	r4, [r3, ip, lsr #12]
d00186d8:	d1f62804 	mvnsle	r2, r4, lsl #16
d00186dc:	46394819 			; <UNDEFINED> instruction: 0x46394819
d00186e0:	44786df3 	ldrbtmi	r6, [r8], #-3571	; 0xfffff20d
d00186e4:	46054798 			; <UNDEFINED> instruction: 0x46054798
d00186e8:	d1ee2800 	mvnle	r2, r0, lsl #16
d00186ec:	d0b72c00 	adcsle	r2, r7, r0, lsl #24
d00186f0:	6db34815 	ldcvs	8, cr4, [r3, #84]!	; 0x54
d00186f4:	47984478 			; <UNDEFINED> instruction: 0x47984478
d00186f8:	bf183800 	svclt	0x00183800
d00186fc:	42442001 	submi	r2, r4, #1
d0018700:	2401e7ae 	strcs	lr, [r1], #-1966	; 0xfffff852
d0018704:	2507e7ea 	strcs	lr, [r7, #-2026]	; 0xfffff816
d0018708:	4810e7df 	ldmdami	r0, {r0, r1, r2, r3, r4, r6, r7, r8, r9, sl, sp, lr, pc}
d001870c:	6df34639 	ldclvs	6, cr4, [r3, #228]!	; 0xe4
d0018710:	47984478 			; <UNDEFINED> instruction: 0x47984478
d0018714:	d0dd2800 	sbcsle	r2, sp, r0, lsl #16
d0018718:	0401f06f 	streq	pc, [r1], #-111	; 0xffffff91
d001871c:	2407e7a0 	strcs	lr, [r7], #-1952	; 0xfffff860
d0018720:	bf00e79e 	svclt	0x0000e79e
d0018724:	2001f000 	andcs	pc, r1, r0
d0018728:	00056c22 	andeq	r6, r5, r2, lsr #24
d001872c:	00035980 	andeq	r5, r3, r0, lsl #19
d0018730:	ffffffa8 			; <UNDEFINED> instruction: 0xffffffa8
d0018734:	ffffff9a 			; <UNDEFINED> instruction: 0xffffff9a
d0018738:	00056bc0 	andeq	r6, r5, r0, asr #23
d001873c:	000358e2 	andeq	r5, r3, r2, ror #17
d0018740:	00056b76 	andeq	r6, r5, r6, ror fp
d0018744:	00056b62 	andeq	r6, r5, r2, ror #22
d0018748:	000358b0 			; <UNDEFINED> instruction: 0x000358b0
d001874c:	00035894 	muleq	r3, r4, r8

Disassembly of section .text.show_status:

d0018754 <.text.show_status>:
d0018754:	46024b09 	strmi	r4, [r2], -r9, lsl #22
d0018758:	6818447b 	ldmdavs	r8, {r0, r1, r3, r4, r5, r6, sl, lr}
d001875c:	689b4b06 	ldmvs	fp, {r1, r2, r8, r9, fp, lr}
d0018760:	68dbb120 	ldmvs	fp, {r5, r8, ip, sp, pc}^
d0018764:	f8d34611 			; <UNDEFINED> instruction: 0xf8d34611
d0018768:	471830c4 	ldrmi	r3, [r8, -r4, asr #1]
d001876c:	4904681b 	stmdbmi	r4, {r0, r1, r3, r4, fp, sp, lr}
d0018770:	4479681b 	ldrbtmi	r6, [r9], #-2075	; 0xfffff7e5
d0018774:	bf004718 	svclt	0x00004718
d0018778:	2001f000 	andcs	pc, r1, r0
d001877c:	00056d6c 	andeq	r6, r5, ip, ror #26
d0018780:	ffffffda 			; <UNDEFINED> instruction: 0xffffffda

Disassembly of section .text.open_editor:

d00187fc <.text.open_editor>:
d00187fc:	47ffe92d 	ldrbmi	lr, [pc, sp, lsr #18]!
d0018800:	f2404c5d 	vfma.f32	q10, q0, <illegal reg q6.5>
d0018804:	4607324d 	strmi	r3, [r7], -sp, asr #4
d0018808:	68a3210c 	stmiavs	r3!, {r2, r3, r8, sp}
d001880c:	685b2000 	ldmdavs	fp, {sp}^
d0018810:	4a5a9202 	bmi	0xd16bd020
d0018814:	9201447a 	andls	r4, r1, #2046820352	; 0x7a000000
d0018818:	728ef44f 	addvc	pc, lr, #1325400064	; 0x4f000000
d001881c:	22119200 	andscs	r9, r1, #0, 4
d0018820:	f44f681d 	vst2.8	{d22-d23}, [pc :64]!
d0018824:	47a873e4 	strmi	r7, [r8, r4, ror #7]!
d0018828:	46051e43 	strmi	r1, [r5], -r3, asr #28
d001882c:	2bfdb2db 	blcs	0xcff853a0
d0018830:	4853d907 	ldmdami	r3, {r0, r1, r2, r8, fp, ip, lr, pc}^
d0018834:	f7ff4478 			; <UNDEFINED> instruction: 0xf7ff4478
d0018838:	2001ff8d 	andcs	pc, r1, sp, lsl #31
d001883c:	e8bdb004 	pop	{r2, ip, sp, pc}
d0018840:	4e5087f0 	mrcmi	7, 2, r8, cr0, cr0, {7}
d0018844:	447e212f 	ldrbtmi	r2, [lr], #-303	; 0xfffffed1
d0018848:	f0024630 			; <UNDEFINED> instruction: 0xf0024630
d001884c:	68a2fac3 	stmiavs	r2!, {r0, r1, r6, r7, r9, fp, ip, sp, lr, pc}
d0018850:	68d24603 	ldmvs	r2, {r0, r1, r9, sl, lr}^
d0018854:	8018f8d2 			; <UNDEFINED> instruction: 0x8018f8d2
d0018858:	d07a2800 	rsbsle	r2, sl, r0, lsl #16
d001885c:	26013301 	strcs	r3, [r1], -r1, lsl #6
d0018860:	23109301 	tstcs	r0, #67108864	; 0x4000000
d0018864:	21082209 	tstcs	r8, r9, lsl #4
d0018868:	93004628 	movwls	r4, #1576	; 0x628
d001886c:	7387f44f 	orrvc	pc, r7, #1325400064	; 0x4f000000
d0018870:	f04f9602 			; <UNDEFINED> instruction: 0xf04f9602
d0018874:	47c00918 	bfimi	r0, r8, (invalid: 18:0)
d0018878:	4a4368a3 	bmi	0xd10f2b0c
d001887c:	718ff44f 	orrvc	pc, pc, pc, asr #8
d0018880:	468068db 	pkhtbmi	r6, r0, fp, asr #17
d0018884:	f8cd447a 			; <UNDEFINED> instruction: 0xf8cd447a
d0018888:	96029000 	strls	r9, [r2], -r0
d001888c:	92014628 	andls	r4, r1, #40, 12	; 0x2800000
d0018890:	f8d32204 			; <UNDEFINED> instruction: 0xf8d32204
d0018894:	2344a008 	movtcs	sl, #16392	; 0x4008
d0018898:	4b3c47d0 	blmi	0xd0f2a7e0
d001889c:	f44f4a3c 	vst1.8	{d20-d21}, [pc :256], ip
d00188a0:	447b71b4 	ldrbtmi	r7, [fp], #-436	; 0xfffffe4c
d00188a4:	6018447a 	andsvs	r4, r8, sl, ror r4
d00188a8:	68a34628 	stmiavs	r3!, {r3, r5, r9, sl, lr}
d00188ac:	920168db 	andls	r6, r1, #14352384	; 0xdb0000
d00188b0:	96022204 	strls	r2, [r2], -r4, lsl #4
d00188b4:	9000f8cd 	andls	pc, r0, sp, asr #17
d00188b8:	9008f8d3 	ldrdls	pc, [r8], -r3
d00188bc:	47c8234e 	strbmi	r2, [r8, lr, asr #6]
d00188c0:	22004b34 	andcs	r4, r0, #52, 22	; 0xd000
d00188c4:	447b2108 	ldrbtmi	r2, [fp], #-264	; 0xfffffef8
d00188c8:	46286018 			; <UNDEFINED> instruction: 0x46286018
d00188cc:	68db68a3 	ldmvs	fp, {r0, r1, r5, r7, fp, sp, lr}^
d00188d0:	4a319202 	bmi	0xd0c7d0e0
d00188d4:	447a9603 	ldrbtmi	r9, [sl], #-1539	; 0xfffff9fd
d00188d8:	22c19201 	sbccs	r9, r1, #268435456	; 0x10000000
d00188dc:	22229200 	eorcs	r9, r2, #0, 4
d00188e0:	9034f8d3 	ldrsbtls	pc, [r4], -r3	; <UNPREDICTABLE>
d00188e4:	73d7f44f 	bicsvc	pc, r7, #1325400064	; 0x4f000000
d00188e8:	4b2c47c8 	blmi	0xd0b2a810
d00188ec:	6018447b 	andsvs	r4, r8, fp, ror r4
d00188f0:	68db68a3 	ldmvs	fp, {r0, r1, r5, r7, fp, sp, lr}^
d00188f4:	9018f8d3 			; <UNDEFINED> instruction: 0x9018f8d3
d00188f8:	d12c2f00 			; <UNDEFINED> instruction: 0xd12c2f00
d00188fc:	447b4b28 	ldrbtmi	r4, [fp], #-2856	; 0xfffff4d8
d0018900:	23129301 	tstcs	r2, #67108864	; 0x4000000
d0018904:	210822eb 	smlattcs	r8, fp, r2, r2
d0018908:	46289300 	strtmi	r9, [r8], -r0, lsl #6
d001890c:	73d7f44f 	bicsvc	pc, r7, #1325400064	; 0x4f000000
d0018910:	47c89602 	strbmi	r9, [r8, r2, lsl #12]
d0018914:	447b4b23 	ldrbtmi	r4, [fp], #-2851	; 0xfffff4dd
d0018918:	f1b86018 			; <UNDEFINED> instruction: 0xf1b86018
d001891c:	d00c0f00 	andle	r0, ip, r0, lsl #30
d0018920:	447b4b21 	ldrbtmi	r4, [fp], #-2849	; 0xfffff4df
d0018924:	b143681b 	cmplt	r3, fp, lsl r8
d0018928:	447b4b20 	ldrbtmi	r4, [fp], #-2848	; 0xfffff4e0
d001892c:	b123681b 			; <UNDEFINED> instruction: 0xb123681b
d0018930:	447e4e1f 	ldrbtmi	r4, [lr], #-3615	; 0xfffff1e1
d0018934:	b1036833 	tstlt	r3, r3, lsr r8
d0018938:	68a3b980 	stmiavs	r3!, {r7, r8, fp, ip, sp, pc}
d001893c:	685b4628 	ldmdavs	fp, {r3, r5, r9, sl, lr}^
d0018940:	4798685b 			; <UNDEFINED> instruction: 0x4798685b
d0018944:	22004b1b 	andcs	r4, r0, #27648	; 0x6c00
d0018948:	447b481b 	ldrbtmi	r4, [fp], #-2075	; 0xfffff7e5
d001894c:	601a4478 	andsvs	r4, sl, r8, ror r4
d0018950:	4633e771 			; <UNDEFINED> instruction: 0x4633e771
d0018954:	4b19e783 	blmi	0xd0692768
d0018958:	e7d1447b 			; <UNDEFINED> instruction: 0xe7d1447b
d001895c:	462868a3 	strtmi	r6, [r8], -r3, lsr #17
d0018960:	685b4917 	ldmdavs	fp, {r0, r1, r2, r4, r8, fp, lr}^
d0018964:	689b4479 	ldmvs	fp, {r0, r3, r4, r5, r6, sl, lr}
d0018968:	68a34798 	stmiavs	r3!, {r3, r4, r7, r8, r9, sl, lr}
d001896c:	68db6830 	ldmvs	fp, {r4, r5, fp, sp, lr}^
d0018970:	47986ddb 			; <UNDEFINED> instruction: 0x47986ddb
d0018974:	e7612000 	strb	r2, [r1, -r0]!
d0018978:	2001f000 	andcs	pc, r1, r0
d001897c:	ffffff8a 			; <UNDEFINED> instruction: 0xffffff8a
d0018980:	ffffff73 			; <UNDEFINED> instruction: 0xffffff73
d0018984:	000568fe 	strdeq	r6, [r5], -lr
d0018988:	ffffff3f 			; <UNDEFINED> instruction: 0xffffff3f
d001898c:	0003688e 	andeq	r6, r3, lr, lsl #17
d0018990:	ffffff24 			; <UNDEFINED> instruction: 0xffffff24
d0018994:	000357de 	ldrdeq	r5, [r3], -lr
d0018998:	0003685e 	andeq	r6, r3, lr, asr r8
d001899c:	000357bc 			; <UNDEFINED> instruction: 0x000357bc
d00189a0:	fffffe92 			; <UNDEFINED> instruction: 0xfffffe92
d00189a4:	00056bae 	andeq	r6, r5, lr, lsr #23
d00189a8:	0003680e 	andeq	r6, r3, lr, lsl #16
d00189ac:	0003577a 	andeq	r5, r3, sl, ror r7
d00189b0:	00035776 	andeq	r5, r3, r6, ror r7
d00189b4:	00056b7a 	andeq	r6, r5, sl, ror fp
d00189b8:	fffffe82 			; <UNDEFINED> instruction: 0xfffffe82
d00189bc:	fffffe28 			; <UNDEFINED> instruction: 0xfffffe28
d00189c0:	00000521 	andeq	r0, r0, r1, lsr #10

Disassembly of section .text.report_file.part.0:

d0018a6c <.text.report_file.part.0>:
d0018a6c:	1cc5b537 	cfstr64ne	mvdx11, [r5], {55}	; 0x37
d0018a70:	460b4604 	strmi	r4, [fp], -r4, lsl #12
d0018a74:	4812d108 	ldmdami	r2, {r3, r8, ip, lr, pc}
d0018a78:	f7ff4478 			; <UNDEFINED> instruction: 0xf7ff4478
d0018a7c:	1c63fe6b 	stclne	14, cr15, [r3], #-428	; 0xfffffe54
d0018a80:	41584258 	cmpmi	r8, r8, asr r2
d0018a84:	bd30b003 	ldclt	0, cr11, [r0, #-12]!
d0018a88:	d1021d20 	tstle	r2, r0, lsr #26
d0018a8c:	4478480d 	ldrbtmi	r4, [r8], #-2061	; 0xfffff7f3
d0018a90:	1ca1e7f3 	stcne	7, cr14, [r1], #972	; 0x3cc
d0018a94:	480cd102 	stmdami	ip, {r1, r8, ip, lr, pc}
d0018a98:	e7ee4478 			; <UNDEFINED> instruction: 0xe7ee4478
d0018a9c:	d1021c62 	tstle	r2, r2, ror #24
d0018aa0:	4478480a 	ldrbtmi	r4, [r8], #-2058	; 0xfffff7f6
d0018aa4:	4d0ae7e9 	stcmi	7, cr14, [sl, #-932]	; 0xfffffc5c
d0018aa8:	71c0f44f 	bicvc	pc, r0, pc, asr #8
d0018aac:	447d4a09 	ldrbtmi	r4, [sp], #-2569	; 0xfffff5f7
d0018ab0:	447a9400 	ldrbtmi	r9, [sl], #-1024	; 0xfffffc00
d0018ab4:	f0024628 			; <UNDEFINED> instruction: 0xf0024628
d0018ab8:	4628f925 	strtmi	pc, [r8], -r5, lsr #18
d0018abc:	bf00e7dd 	svclt	0x0000e7dd
d0018ac0:	ffffff48 			; <UNDEFINED> instruction: 0xffffff48
d0018ac4:	ffffff49 			; <UNDEFINED> instruction: 0xffffff49
d0018ac8:	ffffff5a 			; <UNDEFINED> instruction: 0xffffff5a
d0018acc:	ffffff7c 			; <UNDEFINED> instruction: 0xffffff7c
d0018ad0:	00056896 	muleq	r5, r6, r8
d0018ad4:	ffffff9b 			; <UNDEFINED> instruction: 0xffffff9b

Disassembly of section .text.read_header:

d0018ad8 <.text.read_header>:
d0018ad8:	47f0e92d 	ldrbmi	lr, [r0, sp, lsr #18]!
d0018adc:	460d9f09 	strmi	r9, [sp], -r9, lsl #30
d0018ae0:	46984616 			; <UNDEFINED> instruction: 0x46984616
d0018ae4:	b9104681 	ldmdblt	r0, {r0, r7, r9, sl, lr}
d0018ae8:	e8bd2000 	ldmfd	sp!, {sp}
d0018aec:	290087f0 	stmdbcs	r0, {r4, r5, r6, r7, r8, r9, sl, pc}
d0018af0:	780bd0fa 	stmdavc	fp, {r1, r3, r4, r5, r6, r7, ip, lr, pc}
d0018af4:	d0f72b00 	rscsle	r2, r7, r0, lsl #22
d0018af8:	d0f52b2f 	rscsle	r2, r5, pc, lsr #22
d0018afc:	4628213a 			; <UNDEFINED> instruction: 0x4628213a
d0018b00:	f95cf002 			; <UNDEFINED> instruction: 0xf95cf002
d0018b04:	d1ef2800 	mvnle	r2, r0, lsl #16
d0018b08:	4648212f 	strbmi	r2, [r8], -pc, lsr #2
d0018b0c:	f962f002 			; <UNDEFINED> instruction: 0xf962f002
d0018b10:	d0e92800 	rscle	r2, r9, r0, lsl #16
d0018b14:	0409eba0 	streq	lr, [r9], #-2976	; 0xfffff460
d0018b18:	f0024628 			; <UNDEFINED> instruction: 0xf0024628
d0018b1c:	9a0af92b 	bls	0xd02d6fd0
d0018b20:	46823401 	strmi	r3, [r2], r1, lsl #8
d0018b24:	429a1823 	addsmi	r1, sl, #2293760	; 0x230000
d0018b28:	4622d9de 			; <UNDEFINED> instruction: 0x4622d9de
d0018b2c:	46384649 	ldrtmi	r4, [r8], -r9, asr #12
d0018b30:	fd18f000 	ldc2	0, cr15, [r8, #-0]
d0018b34:	0201f10a 	andeq	pc, r1, #-2147483646	; 0x80000002
d0018b38:	19384629 	ldmdbne	r8!, {r0, r3, r5, r9, sl, lr}
d0018b3c:	fd12f000 	ldc2	0, cr15, [r2, #-0]
d0018b40:	9b08b14e 	blls	0xd0245080
d0018b44:	46314642 	ldrtmi	r4, [r1], -r2, asr #12
d0018b48:	f7ff4638 			; <UNDEFINED> instruction: 0xf7ff4638
d0018b4c:	fab0fced 	blx	0xcec57f08
d0018b50:	0940f080 	stmdbeq	r0, {r7, ip, sp, lr, pc}^
d0018b54:	2001e7c9 	andcs	lr, r1, r9, asr #15
d0018b58:	Address 0x00000000d0018b58 is out of bounds.


Disassembly of section .text.resolve_path.constprop.0:

d0018b68 <.text.resolve_path.constprop.0>:
d0018b68:	460fb5f7 			; <UNDEFINED> instruction: 0x460fb5f7
d0018b6c:	46044616 			; <UNDEFINED> instruction: 0x46044616
d0018b70:	2000b910 	andcs	fp, r0, r0, lsl r9
d0018b74:	bdf0b003 	ldcllt	0, cr11, [r0, #12]!
d0018b78:	2b007803 	blcs	0xd0036b8c
d0018b7c:	f002d0f9 			; <UNDEFINED> instruction: 0xf002d0f9
d0018b80:	4605f8f9 			; <UNDEFINED> instruction: 0x4605f8f9
d0018b84:	f0024638 			; <UNDEFINED> instruction: 0xf0024638
d0018b88:	4285f8f5 	addmi	pc, r5, #16056320	; 0xf50000
d0018b8c:	1a2bd9f1 	bne	0xd0b0f358
d0018b90:	44253f01 	strtmi	r3, [r5], #-3841	; 0xfffff0ff
d0018b94:	42ab4423 	adcmi	r4, fp, #587202560	; 0x23000000
d0018b98:	213ad118 	teqcs	sl, r8, lsl r1
d0018b9c:	f0024620 			; <UNDEFINED> instruction: 0xf0024620
d0018ba0:	7823f90d 	stmdavc	r3!, {r0, r2, r3, r8, fp, ip, sp, lr, pc}
d0018ba4:	d0032b2f 	andle	r2, r3, pc, lsr #22
d0018ba8:	7843b1d8 	stmdavc	r3, {r3, r4, r6, r7, r8, ip, sp, pc}^
d0018bac:	d1e02b2f 	mvnle	r2, pc, lsr #22
d0018bb0:	46234a21 	strtmi	r4, [r3], -r1, lsr #20
d0018bb4:	7180f44f 	orrvc	pc, r0, pc, asr #8
d0018bb8:	447a4630 	ldrbtmi	r4, [sl], #-1584	; 0xfffff9d0
d0018bbc:	f8a2f002 			; <UNDEFINED> instruction: 0xf8a2f002
d0018bc0:	28fe3801 	ldmcs	lr!, {r0, fp, ip, sp}^
d0018bc4:	2000bf8c 	andcs	fp, r0, ip, lsl #31
d0018bc8:	e7d32001 	ldrb	r2, [r3, r1]
d0018bcc:	1b01f813 	blne	0xd0096c20
d0018bd0:	2f01f817 	svccs	0x0001f817
d0018bd4:	0120f041 	msreq	CPSR_, r1, asr #32
d0018bd8:	0220f042 	eoreq	pc, r0, #66	; 0x42
d0018bdc:	d0da4291 	smullsle	r4, sl, r1, r2
d0018be0:	4b14e7c7 	blmi	0xd0552b04
d0018be4:	7180f44f 	orrvc	pc, r0, pc, asr #8
d0018be8:	685b4d14 	ldmdavs	fp, {r2, r4, r8, sl, fp, lr}^
d0018bec:	681b447d 	ldmdavs	fp, {r0, r2, r3, r4, r5, r6, sl, lr}
d0018bf0:	69db4628 	ldmibvs	fp, {r3, r5, r9, sl, lr}^
d0018bf4:	28004798 	stmdacs	r0, {r3, r4, r7, r8, r9, sl, lr}
d0018bf8:	782bd1bb 	stmdavc	fp!, {r0, r1, r3, r4, r5, r7, r8, ip, lr, pc}
d0018bfc:	d0b82b00 	adcsle	r2, r8, r0, lsl #22
d0018c00:	f0024628 			; <UNDEFINED> instruction: 0xf0024628
d0018c04:	4428f8b7 	strtmi	pc, [r8], #-2231	; 0xfffff749
d0018c08:	3c01f810 	stccc	8, cr15, [r1], {16}
d0018c0c:	d00d2b2f 	andle	r2, sp, pc, lsr #22
d0018c10:	447b4b0b 	ldrbtmi	r4, [fp], #-2827	; 0xfffff4f5
d0018c14:	f44f4a0b 	vst1.8	{d20-d21}, [pc], fp
d0018c18:	46307180 	ldrtmi	r7, [r0], -r0, lsl #3
d0018c1c:	e9cd447a 	stmib	sp, {r1, r3, r4, r5, r6, sl, lr}^
d0018c20:	4b093400 	blmi	0xd0265c28
d0018c24:	f002447b 			; <UNDEFINED> instruction: 0xf002447b
d0018c28:	e7c9f86d 	strb	pc, [r9, sp, ror #16]	; <UNPREDICTABLE>
d0018c2c:	447b4b07 	ldrbtmi	r4, [fp], #-2823	; 0xfffff4f9
d0018c30:	bf00e7f0 	svclt	0x0000e7f0
d0018c34:	2001f000 	andcs	pc, r1, r0
d0018c38:	ffffff9f 			; <UNDEFINED> instruction: 0xffffff9f
d0018c3c:	00056658 	andeq	r6, r5, r8, asr r6
d0018c40:	ffffff45 			; <UNDEFINED> instruction: 0xffffff45
d0018c44:	ffffff40 			; <UNDEFINED> instruction: 0xffffff40
d0018c48:	00056620 	andeq	r6, r5, r0, lsr #12
d0018c4c:	ffffff28 			; <UNDEFINED> instruction: 0xffffff28

Disassembly of section .text.build:

d0018ca4 <.text.build>:
d0018ca4:	22004b5b 	andcs	r4, r0, #93184	; 0x16c00
d0018ca8:	447bb570 	ldrbtmi	fp, [fp], #-1392	; 0xfffffa90
d0018cac:	9307b09e 	movwls	fp, #28830	; 0x709e
d0018cb0:	4b59a90e 	blmi	0xd16830f0
d0018cb4:	447b9008 	ldrbtmi	r9, [fp], #-8
d0018cb8:	681b4858 	ldmdavs	fp, {r3, r4, r6, fp, lr}
d0018cbc:	42934478 	addsmi	r4, r3, #120, 8	; 0x78000000
d0018cc0:	4b57d159 	blmi	0xd160d22c
d0018cc4:	9306447b 	movwls	r4, #25723	; 0x647b
d0018cc8:	d15a2a00 	cmple	sl, r0, lsl #20
d0018ccc:	a906a807 	stmdbge	r6, {r0, r1, r2, fp, sp, pc}
d0018cd0:	2a01ab09 	bcs	0xd00838fc
d0018cd4:	ab059302 	blge	0xd017d8e4
d0018cd8:	2201bf38 	andcs	fp, r1, #56, 30	; 0xe0
d0018cdc:	4b519301 	blmi	0xd147d8e8
d0018ce0:	9300447b 	movwls	r4, #1147	; 0x47b
d0018ce4:	447b4b50 	ldrbtmi	r4, [fp], #-2896	; 0xfffff4b0
d0018ce8:	fb86f7ff 	blx	0xce1d6cee
d0018cec:	28004604 	stmdacs	r0, {r2, r9, sl, lr}
d0018cf0:	9c0dd14e 	stflsd	f5, [sp], {78}	; 0x4e
d0018cf4:	4a4db94c 	bmi	0xd138722c
d0018cf8:	447a9b0c 	ldrbtmi	r9, [sl], #-2828	; 0xfffff4f4
d0018cfc:	42936812 	addsmi	r6, r3, #1179648	; 0x120000
d0018d00:	4c4bd243 	sfmmi	f5, 3, [fp], {67}	; 0x43
d0018d04:	eb04447c 	bl	0xd0129efc
d0018d08:	212f2403 			; <UNDEFINED> instruction: 0x212f2403
d0018d0c:	f0024620 			; <UNDEFINED> instruction: 0xf0024620
d0018d10:	b100f861 	tstlt	r0, r1, ror #16	; <UNPREDICTABLE>
d0018d14:	9b091c44 	blls	0xd025fe2c
d0018d18:	990b9a0a 	stmdbls	fp, {r1, r3, r9, fp, ip, pc}
d0018d1c:	4b45b90b 	blmi	0xd1187150
d0018d20:	4845447b 	stmdami	r5, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0018d24:	44789200 	ldrbtmi	r9, [r8], #-512	; 0xfffffe00
d0018d28:	4d454a44 	vstrmi	s9, [r5, #-272]	; 0xfffffef0
d0018d2c:	46239302 	strtmi	r9, [r3], -r2, lsl #6
d0018d30:	447a4604 	ldrbtmi	r4, [sl], #-1540	; 0xfffff9fc
d0018d34:	447d9101 	ldrbtmi	r9, [sp], #-257	; 0xfffffeff
d0018d38:	71c0f44f 	bicvc	pc, r0, pc, asr #8
d0018d3c:	ffe2f001 			; <UNDEFINED> instruction: 0xffe2f001
d0018d40:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0018d44:	6828fd07 	stmdavs	r8!, {r0, r1, r2, r8, sl, fp, ip, sp, lr, pc}
d0018d48:	d0482800 	suble	r2, r8, r0, lsl #16
d0018d4c:	b9849c0d 	stmiblt	r4, {r0, r2, r3, sl, fp, ip, pc}
d0018d50:	b171990a 	cmnlt	r1, sl, lsl #18
d0018d54:	b1629a0b 	cmnlt	r2, fp, lsl #20
d0018d58:	3a014e2d 	bcc	0xd006c614
d0018d5c:	68b33901 	ldmvs	r3!, {r0, r8, fp, ip, sp}
d0018d60:	f8d368db 			; <UNDEFINED> instruction: 0xf8d368db
d0018d64:	479830b8 			; <UNDEFINED> instruction: 0x479830b8
d0018d68:	682868b3 	stmdavs	r8!, {r0, r1, r4, r5, r7, fp, sp, lr}
d0018d6c:	6ddb68db 	ldclvs	8, cr6, [fp, #876]	; 0x36c
d0018d70:	20004798 	mulcs	r0, r8, r7
d0018d74:	eb00e033 	bl	0xd0050e48
d0018d78:	f8412402 			; <UNDEFINED> instruction: 0xf8412402
d0018d7c:	32014022 	andcc	r4, r1, #34	; 0x22
d0018d80:	4830e79d 	ldmdami	r0!, {r0, r2, r3, r4, r7, r8, r9, sl, sp, lr, pc}
d0018d84:	4478a90e 	ldrbtmi	sl, [r8], #-2318	; 0xfffff6f2
d0018d88:	4c2fe7a2 	stcmi	7, cr14, [pc], #-648	; 0xd0018b08
d0018d8c:	e7bc447c 			; <UNDEFINED> instruction: 0xe7bc447c
d0018d90:	46024d2e 	strmi	r4, [r2], -lr, lsr #26
d0018d94:	447d9905 	ldrbtmi	r9, [sp], #-2309	; 0xfffff6fb
d0018d98:	f7ff4628 			; <UNDEFINED> instruction: 0xf7ff4628
d0018d9c:	2800fc2b 	stmdacs	r0, {r0, r1, r3, r5, sl, fp, ip, sp, lr, pc}
d0018da0:	4b2bd131 	blmi	0xd0b0d26c
d0018da4:	6818447b 	ldmdavs	r8, {r0, r1, r3, r4, r5, r6, sl, lr}
d0018da8:	212fb118 			; <UNDEFINED> instruction: 0x212fb118
d0018dac:	f0024628 			; <UNDEFINED> instruction: 0xf0024628
d0018db0:	4b28f811 	blmi	0xd0a56dfc
d0018db4:	681a447b 	ldmdavs	sl, {r0, r1, r3, r4, r5, r6, sl, lr}
d0018db8:	d9152a01 	ldmdble	r5, {r0, r9, fp, sp}
d0018dbc:	1c43b188 	stfnep	f3, [r3], {136}	; 0x88
d0018dc0:	f44f4825 	vst2.8	{d20-d21}, [pc :128], r5
d0018dc4:	920171c0 	andls	r7, r1, #192, 2	; 0x30
d0018dc8:	44784a24 	ldrbtmi	r4, [r8], #-2596	; 0xfffff5dc
d0018dcc:	447a9400 	ldrbtmi	r9, [sl], #-1024	; 0xfffffc00
d0018dd0:	ff98f001 			; <UNDEFINED> instruction: 0xff98f001
d0018dd4:	44784822 	ldrbtmi	r4, [r8], #-2082	; 0xfffff7de
d0018dd8:	fcbcf7ff 	ldc2	7, cr15, [ip], #1020	; 0x3fc
d0018ddc:	b01e2001 	andslt	r2, lr, r1
d0018de0:	4b20bd70 	blmi	0xd08483a8
d0018de4:	e7eb447b 			; <UNDEFINED> instruction: 0xe7eb447b
d0018de8:	1c43b150 	stfnep	f3, [r3], {80}	; 0x50
d0018dec:	f44f4a1e 	vst1.8	{d20-d21}, [pc :64], lr
d0018df0:	481e71c0 	ldmdami	lr, {r6, r7, r8, ip, sp, lr}
d0018df4:	9400447a 	strls	r4, [r0], #-1146	; 0xfffffb86
d0018df8:	f0014478 			; <UNDEFINED> instruction: 0xf0014478
d0018dfc:	e7e9ff83 	strb	pc, [r9, r3, lsl #31]!	; <UNPREDICTABLE>
d0018e00:	447b4b1b 	ldrbtmi	r4, [fp], #-2843	; 0xfffff4e5
d0018e04:	491be7f2 	ldmdbmi	fp, {r1, r4, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d0018e08:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d0018e0c:	e7e6fe2f 	strb	pc, [r6, pc, lsr #28]!	; <UNPREDICTABLE>
d0018e10:	2001f000 	andcs	pc, r1, r0
d0018e14:	0003648a 	andeq	r6, r3, sl, lsl #9
d0018e18:	000353f6 	strdeq	r5, [r3], -r6
d0018e1c:	000353f4 	strdeq	r5, [r3], -r4
d0018e20:	00056480 	andeq	r6, r5, r0, lsl #9
d0018e24:	fffffdf5 			; <UNDEFINED> instruction: 0xfffffdf5
d0018e28:	fffff8d3 			; <UNDEFINED> instruction: 0xfffff8d3
d0018e2c:	000353b2 			; <UNDEFINED> instruction: 0x000353b2
d0018e30:	000353ac 	andeq	r5, r3, ip, lsr #7
d0018e34:	ffffff2c 			; <UNDEFINED> instruction: 0xffffff2c
d0018e38:	0005661e 	andeq	r6, r5, lr, lsl r6
d0018e3c:	ffffff2d 			; <UNDEFINED> instruction: 0xffffff2d
d0018e40:	00035372 	andeq	r5, r3, r2, ror r3
d0018e44:	0003632a 	andeq	r6, r3, sl, lsr #6
d0018e48:	000563b8 			; <UNDEFINED> instruction: 0x000563b8
d0018e4c:	0003510e 	andeq	r5, r3, lr, lsl #2
d0018e50:	00056720 	andeq	r6, r5, r0, lsr #14
d0018e54:	000352f8 	strdeq	r5, [r3], -r8
d0018e58:	0005657a 	andeq	r6, r5, sl, ror r5
d0018e5c:	fffffe9d 			; <UNDEFINED> instruction: 0xfffffe9d
d0018e60:	0005656e 	andeq	r6, r5, lr, ror #10
d0018e64:	000350c0 	andeq	r5, r3, r0, asr #1
d0018e68:	fffffe97 			; <UNDEFINED> instruction: 0xfffffe97
d0018e6c:	0005654c 	andeq	r6, r5, ip, asr #10
d0018e70:	000350a2 	andeq	r5, r3, r2, lsr #1
d0018e74:	fffff9c0 			; <UNDEFINED> instruction: 0xfffff9c0

Disassembly of section .text.editor_proc:

d0018e88 <.text.editor_proc>:
d0018e88:	460cb513 			; <UNDEFINED> instruction: 0x460cb513
d0018e8c:	d0412900 	suble	r2, r1, r0, lsl #18
d0018e90:	2b10680b 	blcs	0xd0432ec4
d0018e94:	68cad13e 	stmiavs	sl, {r1, r2, r3, r4, r5, r8, ip, lr, pc}^
d0018e98:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d0018e9c:	d139429a 	teqle	r9, sl	; <illegal shifter operand>
d0018ea0:	688b4a1f 	stmvs	fp, {r0, r1, r2, r3, r4, r9, fp, lr}
d0018ea4:	6812447a 	ldmdavs	r2, {r1, r3, r4, r5, r6, sl, lr}
d0018ea8:	d0044293 	mulle	r4, r3, r2
d0018eac:	447a4a1d 	ldrbtmi	r4, [sl], #-2589	; 0xfffff5e3
d0018eb0:	42936812 	addsmi	r6, r3, #1179648	; 0x120000
d0018eb4:	4b18d12e 	blmi	0xd064d374
d0018eb8:	689b481b 	ldmvs	fp, {r0, r1, r3, r4, fp, lr}
d0018ebc:	4478491b 	ldrbtmi	r4, [r8], #-2331	; 0xfffff6e5
d0018ec0:	447968db 	ldrbtmi	r6, [r9], #-2267	; 0xfffff725
d0018ec4:	6f1b4a15 	svcvs	0x001b4a15
d0018ec8:	91016800 	tstls	r1, r0, lsl #16
d0018ecc:	38014798 	stmdacc	r1, {r3, r4, r7, r8, r9, sl, lr}
d0018ed0:	f5b09901 			; <UNDEFINED> instruction: 0xf5b09901
d0018ed4:	d9043f00 	stmdble	r4, {r8, r9, sl, fp, ip, sp}
d0018ed8:	44784815 	ldrbtmi	r4, [r8], #-2069	; 0xfffff7eb
d0018edc:	fc3af7ff 	ldc2	7, cr15, [sl], #-1020	; 0xfffffc04
d0018ee0:	4b14e007 	blmi	0xd0550f04
d0018ee4:	447b68a2 	ldrbtmi	r6, [fp], #-2210	; 0xfffff75e
d0018ee8:	429a681b 	addsmi	r6, sl, #1769472	; 0x1b0000
d0018eec:	f7ffd104 			; <UNDEFINED> instruction: 0xf7ffd104
d0018ef0:	20f0fed9 	ldrsbtcs	pc, [r0], #233	; 0xe9	; <UNPREDICTABLE>
d0018ef4:	bd10b002 	ldclt	0, cr11, [r0, #-8]
d0018ef8:	480f4602 	stmdami	pc, {r1, r9, sl, lr}	; <UNPREDICTABLE>
d0018efc:	f7ff4478 			; <UNDEFINED> instruction: 0xf7ff4478
d0018f00:	b910fb79 	ldmdblt	r0, {r0, r3, r4, r5, r6, r8, r9, fp, ip, sp, lr, pc}
d0018f04:	4478480d 	ldrbtmi	r4, [r8], #-2061	; 0xfffff7f3
d0018f08:	490de7e8 	stmdbmi	sp, {r3, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d0018f0c:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d0018f10:	e7eefdad 	strb	pc, [lr, sp, lsr #27]!	; <UNPREDICTABLE>
d0018f14:	e7ed2000 	strb	r2, [sp, r0]!
d0018f18:	2001f000 	andcs	pc, r1, r0
d0018f1c:	00020001 	andeq	r0, r2, r1
d0018f20:	0003628c 	andeq	r6, r3, ip, lsl #5
d0018f24:	000351f6 	strdeq	r5, [r3], -r6
d0018f28:	000351ea 	andeq	r5, r3, sl, ror #3
d0018f2c:	00036272 	andeq	r6, r3, r2, ror r2
d0018f30:	fffffae6 			; <UNDEFINED> instruction: 0xfffffae6
d0018f34:	000351be 			; <UNDEFINED> instruction: 0x000351be
d0018f38:	00056248 	andeq	r6, r5, r8, asr #4
d0018f3c:	ffffff6e 			; <UNDEFINED> instruction: 0xffffff6e
d0018f40:	fffff8b7 			; <UNDEFINED> instruction: 0xfffff8b7

Disassembly of section .text.startup.main:

d0019124 <.text.startup.main>:
d0019124:	e92d2801 	push	{r0, fp, sp}
d0019128:	46044ff0 			; <UNDEFINED> instruction: 0x46044ff0
d001912c:	ed2d460f 	stc	6, cr4, [sp, #-60]!	; 0xffffffc4
d0019130:	b0978b02 	addslt	r8, r7, r2, lsl #22
d0019134:	808cf000 	addhi	pc, ip, r0
d0019138:	f0402803 			; <UNDEFINED> instruction: 0xf0402803
d001913c:	49af8159 	stmibmi	pc!, {r0, r3, r4, r6, r8, pc}	; <UNPREDICTABLE>
d0019140:	44796878 	ldrbtmi	r6, [r9], #-2168	; 0xfffff788
d0019144:	fe22f001 	cdp2	0, 2, cr15, cr2, cr1, {0}
d0019148:	f680fab0 			; <UNDEFINED> instruction: 0xf680fab0
d001914c:	49ac0976 	stmibmi	ip!, {r1, r2, r4, r5, r6, r8, fp}
d0019150:	44796878 	ldrbtmi	r6, [r9], #-2168	; 0xfffff788
d0019154:	fe1af001 	cdp2	0, 1, cr15, cr10, cr1, {0}
d0019158:	b966b958 	stmdblt	r6!, {r3, r4, r6, r8, fp, ip, sp, pc}^
d001915c:	447848a9 	ldrbtmi	r4, [r8], #-2217	; 0xfffff757
d0019160:	f7ff2401 			; <UNDEFINED> instruction: 0xf7ff2401
d0019164:	4620faf7 			; <UNDEFINED> instruction: 0x4620faf7
d0019168:	ecbdb017 	ldc	0, cr11, [sp], #92	; 0x5c
d001916c:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d0019170:	2e008ff0 	mcrcs	15, 0, r8, cr0, cr0, {7}
d0019174:	f104d05d 			; <UNDEFINED> instruction: 0xf104d05d
d0019178:	25004480 	strcs	r4, [r0, #-1152]	; 0xfffffb80
d001917c:	46ab3c01 	strtmi	r3, [fp], r1, lsl #24
d0019180:	0024f857 	eoreq	pc, r4, r7, asr r8	; <UNPREDICTABLE>
d0019184:	f8df2401 			; <UNDEFINED> instruction: 0xf8df2401
d0019188:	49a08280 	stmibmi	r0!, {r7, r9, pc}
d001918c:	447944f8 	ldrbtmi	r4, [r9], #-1272	; 0xfffffb08
d0019190:	f7ff4642 			; <UNDEFINED> instruction: 0xf7ff4642
d0019194:	2800fce9 	stmdacs	r0, {r0, r3, r5, r6, r7, sl, fp, ip, sp, lr, pc}
d0019198:	489dd15f 	ldmmi	sp, {r0, r1, r2, r3, r4, r6, r8, ip, lr, pc}
d001919c:	e7df4478 			; <UNDEFINED> instruction: 0xe7df4478
d00191a0:	0389ea4f 	orreq	lr, r9, #323584	; 0x4f000
d00191a4:	1a10ee18 	bne	0xd0454a0c
d00191a8:	0029f857 	eoreq	pc, r9, r7, asr r8	; <UNPREDICTABLE>
d00191ac:	0889eb07 	stmeq	r9, {r0, r1, r2, r8, r9, fp, sp, lr, pc}
d00191b0:	f0019302 			; <UNDEFINED> instruction: 0xf0019302
d00191b4:	b960fdeb 	stmdblt	r0!, {r0, r1, r3, r5, r6, r7, r8, sl, fp, ip, sp, lr, pc}^
d00191b8:	f109b946 			; <UNDEFINED> instruction: 0xf109b946
d00191bc:	42a10101 	adcmi	r0, r1, #1073741824	; 0x40000000
d00191c0:	f8d8da04 			; <UNDEFINED> instruction: 0xf8d8da04
d00191c4:	78091004 	stmdavc	r9, {r2, ip}
d00191c8:	d130292d 	teqle	r0, sp, lsr #18
d00191cc:	44784891 	ldrbtmi	r4, [r8], #-2193	; 0xfffff76f
d00191d0:	4651e7c6 	ldrbmi	lr, [r1], -r6, asr #15
d00191d4:	0029f857 	eoreq	pc, r9, r7, asr r8	; <UNPREDICTABLE>
d00191d8:	fdd8f001 	ldc2l	0, cr15, [r8, #4]
d00191dc:	f1bbb978 			; <UNDEFINED> instruction: 0xf1bbb978
d00191e0:	d1090f00 	tstle	r9, r0, lsl #30
d00191e4:	0901f109 	stmdbeq	r1, {r0, r3, r8, ip, sp, lr, pc}
d00191e8:	da0545a1 	ble	0xd016a874
d00191ec:	b004f8d8 	ldrdlt	pc, [r4], -r8
d00191f0:	1000f89b 	mulne	r0, fp, r8
d00191f4:	d112292d 	tstle	r2, sp, lsr #18
d00191f8:	44784887 	ldrbtmi	r4, [r8], #-2183	; 0xfffff779
d00191fc:	9b02e7b0 	blls	0xd00d30c4
d0019200:	780858f9 	stmdavc	r8, {r0, r3, r4, r5, r6, r7, fp, ip, lr}
d0019204:	d001282d 	andle	r2, r1, sp, lsr #16
d0019208:	d9022d0f 	stmdble	r2, {r0, r1, r2, r3, r8, sl, fp, sp}
d001920c:	44784883 	ldrbtmi	r4, [r8], #-2179	; 0xfffff77d
d0019210:	ab16e7a6 	blge	0xd05d30b0
d0019214:	0085eb03 	addeq	lr, r5, r3, lsl #22
d0019218:	f8403501 			; <UNDEFINED> instruction: 0xf8403501
d001921c:	f1091c40 			; <UNDEFINED> instruction: 0xf1091c40
d0019220:	45a10901 	strmi	r0, [r1, #2305]!	; 0x901
d0019224:	b985dbbc 	stmiblt	r5, {r2, r3, r4, r5, r7, r8, r9, fp, ip, lr, pc}
d0019228:	4478487d 	ldrbtmi	r4, [r8], #-2173	; 0xfffff783
d001922c:	2601e798 			; <UNDEFINED> instruction: 0x2601e798
d0019230:	4b7ce7f5 	blmi	0xd1f5320c
d0019234:	0901f04f 	stmdbeq	r1, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d0019238:	a1ecf8df 	ldrdge	pc, [ip, #143]!	; 0x8f
d001923c:	447b4635 	ldrbtmi	r4, [fp], #-1589	; 0xfffff9cb
d0019240:	44fa46b3 	ldrbtmi	r4, [sl], #1715	; 0x6b3
d0019244:	3a10ee08 	bcc	0xd0454a6c
d0019248:	9806e7eb 	stmdals	r6, {r0, r1, r3, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d001924c:	e79a2400 	ldr	r2, [sl, r0, lsl #8]
d0019250:	48762500 	ldmdami	r6!, {r8, sl, sp}^
d0019254:	447846ab 	ldrbtmi	r4, [r8], #-1707	; 0xfffff955
d0019258:	f1bbe795 			; <UNDEFINED> instruction: 0xf1bbe795
d001925c:	d0290f00 	eorle	r0, r9, r0, lsl #30
d0019260:	46584a73 			; <UNDEFINED> instruction: 0x46584a73
d0019264:	447a4973 	ldrbtmi	r4, [sl], #-2419	; 0xfffff68d
d0019268:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d001926c:	2800fc7d 	stmdacs	r0, {r0, r2, r3, r4, r5, r6, sl, fp, ip, sp, lr, pc}
d0019270:	4871d093 	ldmdami	r1!, {r0, r1, r4, r7, ip, lr, pc}^
d0019274:	f0014478 			; <UNDEFINED> instruction: 0xf0014478
d0019278:	38f7fd7d 	ldmcc	r7!, {r0, r2, r3, r4, r5, r6, r8, sl, fp, ip, sp, lr, pc}^
d001927c:	7f81f510 	svcvc	0x0081f510
d0019280:	2c00d98b 			; <UNDEFINED> instruction: 0x2c00d98b
d0019284:	8086f040 	addhi	pc, r6, r0, asr #32
d0019288:	46274b6c 	strtmi	r4, [r7], -ip, ror #22
d001928c:	a1b0f8df 	asrsge	pc, pc	; <illegal shifter operand>	; <UNPREDICTABLE>
d0019290:	f8df447b 			; <UNDEFINED> instruction: 0xf8df447b
d0019294:	44fab1b0 	ldrbtmi	fp, [sl], #432	; 0x1b0
d0019298:	44fb601c 	ldrbtmi	r6, [fp], #28
d001929c:	447b4b6a 	ldrbtmi	r4, [fp], #-2922	; 0xfffff496
d00192a0:	42ac9302 	adcmi	r9, ip, #134217728	; 0x8000000
d00192a4:	2000d11d 	andcs	sp, r0, sp, lsl r1
d00192a8:	fcfcf7ff 	ldc2l	7, cr15, [ip], #1020	; 0x3fc
d00192ac:	f480fab0 	vst3.32			; <UNDEFINED> instruction: 0xf480fab0
d00192b0:	e7580964 	ldrb	r0, [r8, -r4, ror #18]
d00192b4:	f0014640 			; <UNDEFINED> instruction: 0xf0014640
d00192b8:	1cc3fd5d 	stclne	13, cr15, [r3], {93}	; 0x5d
d00192bc:	7f80f5b3 	svcvc	0x0080f5b3
d00192c0:	af6bf63f 	svcge	0x006bf63f
d00192c4:	1e464f61 	cdpne	15, 4, cr4, cr6, cr1, {3}
d00192c8:	447f4641 	ldrbtmi	r4, [pc], #-1601	; 0xd00192d0
d00192cc:	46384632 			; <UNDEFINED> instruction: 0x46384632
d00192d0:	f948f000 			; <UNDEFINED> instruction: 0xf948f000
d00192d4:	2204495e 	andcs	r4, r4, #1540096	; 0x178000
d00192d8:	447919b8 	ldrbtmi	r1, [r9], #-2488	; 0xfffff648
d00192dc:	f942f000 			; <UNDEFINED> instruction: 0xf942f000
d00192e0:	9a02e7c7 	bls	0xd00d3204
d00192e4:	f8daab06 			; <UNDEFINED> instruction: 0xf8daab06
d00192e8:	46598000 	ldrbmi	r8, [r9], -r0
d00192ec:	3024f853 	eorcc	pc, r4, r3, asr r8	; <UNPREDICTABLE>
d00192f0:	2908eb02 	stmdbcs	r8, {r1, r8, r9, fp, sp, lr, pc}
d00192f4:	93034618 	movwls	r4, #13848	; 0x3618
d00192f8:	f7ff464a 			; <UNDEFINED> instruction: 0xf7ff464a
d00192fc:	9b03fc35 	blls	0xd01183d8
d0019300:	4c54b948 	mrrcmi	9, 4, fp, r4, cr8	; <UNPREDICTABLE>
d0019304:	447c4a54 	ldrbtmi	r4, [ip], #-2644	; 0xfffff5ac
d0019308:	f44f447a 	vst3.16	{d20-d22}, [pc :256], sl
d001930c:	462071c0 	strtmi	r7, [r0], -r0, asr #3
d0019310:	fcf8f001 	ldc2l	0, cr15, [r8], #4
d0019314:	2300e01f 	movwcs	lr, #31
d0019318:	0607eb08 	streq	lr, [r7], -r8, lsl #22
d001931c:	3200f5c7 	andcc	pc, r0, #834666496	; 0x31c00000
d0019320:	93054648 	movwls	r4, #22088	; 0x5648
d0019324:	447b4b4d 	ldrbtmi	r4, [fp], #-2893	; 0xfffff4b3
d0019328:	ab05441e 	blge	0xd016a3a8
d001932c:	f7ff4631 			; <UNDEFINED> instruction: 0xf7ff4631
d0019330:	4601f8fb 			; <UNDEFINED> instruction: 0x4601f8fb
d0019334:	1cc3b188 	stfnep	f3, [r3], {136}	; 0x88
d0019338:	4849d102 	stmdami	r9, {r1, r8, ip, lr, pc}^
d001933c:	e70f4478 	smlsdx	pc, r8, r4, r4	; <UNPREDICTABLE>
d0019340:	464b4c48 	strbmi	r4, [fp], -r8, asr #24
d0019344:	f44f4a48 	vst1.16	{d20-d21}, [pc], r8
d0019348:	447c71c0 	ldrbtmi	r7, [ip], #-448	; 0xfffffe40
d001934c:	447a9000 	ldrbtmi	r9, [sl], #-0
d0019350:	f0014620 			; <UNDEFINED> instruction: 0xf0014620
d0019354:	4620fcd7 			; <UNDEFINED> instruction: 0x4620fcd7
d0019358:	9a05e702 	bls	0xd0192f68
d001935c:	f0014630 			; <UNDEFINED> instruction: 0xf0014630
d0019360:	b128fcf3 	strdlt	pc, [r8, -r3]!
d0019364:	464b4c41 	strbmi	r4, [fp], -r1, asr #24
d0019368:	447c4a41 	ldrbtmi	r4, [ip], #-2625	; 0xfffff5bf
d001936c:	e7cc447a 			; <UNDEFINED> instruction: 0xe7cc447a
d0019370:	34014b40 	strcc	r4, [r1], #-2880	; 0xfffff4c0
d0019374:	447b9a05 	ldrbtmi	r9, [fp], #-2565	; 0xfffff5fb
d0019378:	54b04417 	ldrtpl	r4, [r0], #1047	; 0x417
d001937c:	6038f843 	eorsvs	pc, r8, r3, asr #16
d0019380:	08c8eb03 	stmiaeq	r8, {r0, r1, r8, r9, fp, sp, lr, pc}^
d0019384:	3000f8da 	ldrdcc	pc, [r0], -sl
d0019388:	2004f8c8 	andcs	pc, r4, r8, asr #17
d001938c:	f8ca3301 			; <UNDEFINED> instruction: 0xf8ca3301
d0019390:	e7863000 	str	r3, [r6, r0]
d0019394:	23004d38 	movwcs	r4, #3384	; 0xd38
d0019398:	f44f4838 	vst2.8	{d20-d21}, [pc :256], r8
d001939c:	447d3200 	ldrbtmi	r3, [sp], #-512	; 0xfffffe00
d00193a0:	44789305 	ldrbtmi	r9, [r8], #-773	; 0xfffffcfb
d00193a4:	4629ab05 	strtmi	sl, [r9], -r5, lsl #22
d00193a8:	f8bef7ff 			; <UNDEFINED> instruction: 0xf8bef7ff
d00193ac:	4601b948 	strmi	fp, [r1], -r8, asr #18
d00193b0:	46289a05 	strtmi	r9, [r8], -r5, lsl #20
d00193b4:	fcc8f001 	stc2l	0, cr15, [r8], {1}
d00193b8:	9b05b980 	blls	0xd01879c0
d00193bc:	200054e8 	andcs	r5, r0, r8, ror #9
d00193c0:	2804e008 	stmdacs	r4, {r3, sp, lr, pc}
d00193c4:	492ed10c 	stmdbmi	lr!, {r2, r3, r8, ip, lr, pc}
d00193c8:	4628227d 			; <UNDEFINED> instruction: 0x4628227d
d00193cc:	f0004479 			; <UNDEFINED> instruction: 0xf0004479
d00193d0:	2001f8c9 	andcs	pc, r1, r9, asr #17
d00193d4:	fa12f7ff 	blx	0xd04d73d8
d00193d8:	e6c44604 	strb	r4, [r4], r4, lsl #12
d00193dc:	0003f06f 	andeq	pc, r3, pc, rrx
d00193e0:	44794928 	ldrbtmi	r4, [r9], #-2344	; 0xfffff6d8
d00193e4:	fb42f7ff 	blx	0xd10d73ea
d00193e8:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d00193ec:	e7e6aebc 			; <UNDEFINED> instruction: 0xe7e6aebc
d00193f0:	f77f2800 			; <UNDEFINED> instruction: 0xf77f2800
d00193f4:	2600aeb3 			; <UNDEFINED> instruction: 0x2600aeb3
d00193f8:	bf00e6a9 	svclt	0x0000e6a9
d00193fc:	fffffe06 			; <UNDEFINED> instruction: 0xfffffe06
d0019400:	fffffdf6 			; <UNDEFINED> instruction: 0xfffffdf6
d0019404:	fffffded 			; <UNDEFINED> instruction: 0xfffffded
d0019408:	00055fb8 			; <UNDEFINED> instruction: 0x00055fb8
d001940c:	fffffed9 			; <UNDEFINED> instruction: 0xfffffed9
d0019410:	fffffece 			; <UNDEFINED> instruction: 0xfffffece
d0019414:	fffffdc5 			; <UNDEFINED> instruction: 0xfffffdc5
d0019418:	fffffdd1 			; <UNDEFINED> instruction: 0xfffffdd1
d001941c:	fffffdf2 			; <UNDEFINED> instruction: 0xfffffdf2
d0019420:	fffffe06 			; <UNDEFINED> instruction: 0xfffffe06
d0019424:	fffffd52 			; <UNDEFINED> instruction: 0xfffffd52
d0019428:	fffffd86 			; <UNDEFINED> instruction: 0xfffffd86
d001942c:	fffffcea 			; <UNDEFINED> instruction: 0xfffffcea
d0019430:	00034c3e 	andeq	r4, r3, lr, lsr ip
d0019434:	fffffe36 			; <UNDEFINED> instruction: 0xfffffe36
d0019438:	00034c30 	andeq	r4, r3, r0, lsr ip
d001943c:	00034e1c 	andeq	r4, r3, ip, lsl lr
d0019440:	00034e16 	andeq	r4, r3, r6, lsl lr
d0019444:	fffffdcd 			; <UNDEFINED> instruction: 0xfffffdcd
d0019448:	00034e12 	andeq	r4, r3, r2, lsl lr
d001944c:	00034bda 	ldrdeq	r4, [r3], -sl
d0019450:	fffffdc9 			; <UNDEFINED> instruction: 0xfffffdc9
d0019454:	0005603e 	andeq	r6, r5, lr, lsr r0
d0019458:	fffffd9f 			; <UNDEFINED> instruction: 0xfffffd9f
d001945c:	00035e0e 	andeq	r5, r3, lr, lsl #28
d0019460:	fffffd86 			; <UNDEFINED> instruction: 0xfffffd86
d0019464:	00055ffa 	strdeq	r5, [r5], -sl
d0019468:	fffffd94 			; <UNDEFINED> instruction: 0xfffffd94
d001946c:	00055fda 	ldrdeq	r5, [r5], -sl
d0019470:	fffffd8d 			; <UNDEFINED> instruction: 0xfffffd8d
d0019474:	00035d3a 	andeq	r5, r3, sl, lsr sp
d0019478:	00035d96 	muleq	r3, r6, sp
d001947c:	00055da2 	andeq	r5, r5, r2, lsr #27
d0019480:	000000b8 	strheq	r0, [r0], -r8
d0019484:	fffffd2f 			; <UNDEFINED> instruction: 0xfffffd2f

Disassembly of section .text.initMalloc:

d0019508 <.text.initMalloc>:
d0019508:	f44f4b06 			; <UNDEFINED> instruction: 0xf44f4b06
d001950c:	4a064180 	bmi	0xd01a9b14
d0019510:	589a447b 	ldmpl	sl, {r0, r1, r3, r4, r5, r6, sl, lr}
d0019514:	4a056011 	bmi	0xd0171560
d0019518:	4b05589a 	blmi	0xd016f788
d001951c:	601a447b 	andsvs	r4, sl, fp, ror r4
d0019520:	bf004770 	svclt	0x00004770
d0019524:	000018e0 	andeq	r1, r0, r0, ror #17
d0019528:	00000004 	andeq	r0, r0, r4
d001952c:	00000000 	andeq	r0, r0, r0
d0019530:	00055fac 	andeq	r5, r5, ip, lsr #31

Disassembly of section .text.applet_entry:

d0019534 <.text.applet_entry>:
d0019534:	9101b507 	tstls	r1, r7, lsl #10
d0019538:	ffe6f7ff 			; <UNDEFINED> instruction: 0xffe6f7ff
d001953c:	b0039901 	andlt	r9, r3, r1, lsl #18
d0019540:	eb04f85d 	bl	0xd01576bc
d0019544:	bdeef7ff 	stcllt	7, cr15, [lr, #1020]!	; 0x3fc

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

Disassembly of section .text.pp_space:

d00101a8 <.text.pp_space>:
d00101a8:	6a436a81 	bvs	0xd10eabb4
d00101ac:	d204428b 	andle	r4, r4, #-1342177272	; 0xb0000008
d00101b0:	2a20781a 	bcs	0xd082e220
d00101b4:	2a09d002 	bcs	0xd02841c4
d00101b8:	4770d000 	ldrbmi	sp, [r0, -r0]!
d00101bc:	62433301 	subvs	r3, r3, #67108864	; 0x4000000
d00101c0:	Address 0x00000000d00101c0 is out of bounds.


Disassembly of section .text.pp_take:

d00101c2 <.text.pp_take>:
d00101c2:	460eb570 			; <UNDEFINED> instruction: 0x460eb570
d00101c6:	f7ff4604 			; <UNDEFINED> instruction: 0xf7ff4604
d00101ca:	4630ffee 	ldrtmi	pc, [r0], -lr, ror #31	; <UNPREDICTABLE>
d00101ce:	fdd1f00a 	ldc2l	0, cr15, [r1, #40]	; 0x28
d00101d2:	46056aa3 	strmi	r6, [r5], -r3, lsr #21
d00101d6:	1a1b6a60 	bne	0xd06eab5e
d00101da:	d20142ab 	andle	r4, r1, #-1342177270	; 0xb000000a
d00101de:	bd702000 	ldcllt	0, cr2, [r0, #-0]
d00101e2:	4631462a 	ldrtmi	r4, [r1], -sl, lsr #12
d00101e6:	f9cdf009 			; <UNDEFINED> instruction: 0xf9cdf009
d00101ea:	d1f72800 	mvnsle	r2, r0, lsl #16
d00101ee:	44286a60 	strtmi	r6, [r8], #-2656	; 0xfffff5a0
d00101f2:	20016260 	andcs	r6, r1, r0, ror #4
d00101f6:	Address 0x00000000d00101f6 is out of bounds.


Disassembly of section .text.macro_index:

d00101f8 <.text.macro_index>:
d00101f8:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d00101fc:	462bf500 	strtmi	pc, [fp], -r0, lsl #10
d0010200:	444ff500 	strbmi	pc, [pc], #-1280	; 0xd0010208	; <UNPREDICTABLE>
d0010204:	46174688 	ldrmi	r4, [r7], -r8, lsl #13
d0010208:	25003688 	strcs	r3, [r0, #-1672]	; 0xfffff978
d001020c:	68233488 	stmdavs	r3!, {r3, r7, sl, ip, sp}
d0010210:	d80242ab 	stmdale	r2, {r0, r1, r3, r5, r7, r9, lr}
d0010214:	30fff04f 	rscscc	pc, pc, pc, asr #32
d0010218:	4630e00b 	ldrtmi	lr, [r0], -fp
d001021c:	fdaaf00a 	stc2	0, cr15, [sl, #40]!	; 0x28
d0010220:	d10842b8 			; <UNDEFINED> instruction: 0xd10842b8
d0010224:	4641463a 			; <UNDEFINED> instruction: 0x4641463a
d0010228:	f0094630 			; <UNDEFINED> instruction: 0xf0094630
d001022c:	b910f9ab 	ldmdblt	r0, {r0, r1, r3, r5, r7, r8, fp, ip, sp, lr, pc}
d0010230:	e8bd4628 	pop	{r3, r5, r9, sl, lr}
d0010234:	350181f0 	strcc	r8, [r1, #-496]	; 0xfffffe10
d0010238:	e7e83648 	strb	r3, [r8, r8, asr #12]!

Disassembly of section .text.letter:

d001023c <.text.letter>:
d001023c:	0320f020 	nopeq	{32}
d0010240:	2b193b41 	blcs	0xd065ef4c
d0010244:	f1a0d904 			; <UNDEFINED> instruction: 0xf1a0d904
d0010248:	4258035f 	subsmi	r0, r8, #2080374785	; 0x7c000001
d001024c:	47704158 			; <UNDEFINED> instruction: 0x47704158
d0010250:	47702001 	ldrbmi	r2, [r0, -r1]!

Disassembly of section .text.hex_digit:

d0010254 <.text.hex_digit>:
d0010254:	38304603 	ldmdacc	r0!, {r0, r1, r9, sl, lr}
d0010258:	d9082809 	stmdble	r8, {r0, r3, fp, sp}
d001025c:	0020f043 	eoreq	pc, r0, r3, asr #32
d0010260:	0361f1a0 	msreq	SPSR_c, #160, 2	; 0x28
d0010264:	d8012b05 	stmdale	r1, {r0, r2, r8, r9, fp, sp}
d0010268:	47703857 			; <UNDEFINED> instruction: 0x47703857
d001026c:	47702010 			; <UNDEFINED> instruction: 0x47702010

Disassembly of section .text.valid_api_name:

d0010270 <.text.valid_api_name>:
d0010270:	4602b510 			; <UNDEFINED> instruction: 0x4602b510
d0010274:	f7ff7800 			; <UNDEFINED> instruction: 0xf7ff7800
d0010278:	b170ffe1 	cmnlt	r0, r1, ror #31	; <UNPREDICTABLE>
d001027c:	041ff102 	ldreq	pc, [pc], #-258	; 0xd0010284
d0010280:	1f01f812 	svcne	0x0001f812
d0010284:	4608b151 			; <UNDEFINED> instruction: 0x4608b151
d0010288:	ffd8f7ff 			; <UNDEFINED> instruction: 0xffd8f7ff
d001028c:	3930b910 	ldmdbcc	r0!, {r4, r8, fp, ip, sp, pc}
d0010290:	d8022909 	stmdale	r2, {r0, r3, r8, fp, sp}
d0010294:	d1f342a2 	mvnsle	r4, r2, lsr #5
d0010298:	bd102000 	ldclt	0, cr2, [r0, #-0]
d001029c:	e7fc2001 	ldrb	r2, [ip, r1]!

Disassembly of section .text.name_is.isra.0:

d00102a0 <.text.name_is.isra.0>:
d00102a0:	460db537 			; <UNDEFINED> instruction: 0x460db537
d00102a4:	46104604 	ldrmi	r4, [r0], -r4, lsl #12
d00102a8:	f00a9201 			; <UNDEFINED> instruction: 0xf00a9201
d00102ac:	42a8fd63 	adcmi	pc, r8, #6336	; 0x18c0
d00102b0:	99014602 	stmdbls	r1, {r1, r9, sl, lr}
d00102b4:	4620d107 	strtmi	sp, [r0], -r7, lsl #2
d00102b8:	f964f009 			; <UNDEFINED> instruction: 0xf964f009
d00102bc:	f080fab0 			; <UNDEFINED> instruction: 0xf080fab0
d00102c0:	b0030940 	andlt	r0, r3, r0, asr #18
d00102c4:	2000bd30 	andcs	fp, r0, r0, lsr sp
d00102c8:	Address 0x00000000d00102c8 is out of bounds.


Disassembly of section .text.pp_unary:

d00102e0 <.text.pp_unary>:
d00102e0:	e92d6ac3 	push	{r0, r1, r6, r7, r9, fp, sp, lr}
d00102e4:	1c5a43f7 	mrrcne	3, 15, r4, sl, cr7
d00102e8:	2a204604 	bcs	0xd0821b00
d00102ec:	d90962c2 	stmdble	r9, {r1, r6, r7, r9, sp, lr}
d00102f0:	26002201 	strcs	r2, [r0], -r1, lsl #4
d00102f4:	62c32700 	sbcvs	r2, r3, #0, 14
d00102f8:	46306302 	ldrtmi	r6, [r0], -r2, lsl #6
d00102fc:	b0034639 	andlt	r4, r3, r9, lsr r6
d0010300:	83f0e8bd 	mvnshi	lr, #12386304	; 0xbd0000
d0010304:	44794986 	ldrbtmi	r4, [r9], #-2438	; 0xfffff67a
d0010308:	ff5bf7ff 			; <UNDEFINED> instruction: 0xff5bf7ff
d001030c:	4620b148 	strtmi	fp, [r0], -r8, asr #2
d0010310:	ffe6f7ff 			; <UNDEFINED> instruction: 0xffe6f7ff
d0010314:	0301ea50 	movweq	lr, #6736	; 0x1a50
d0010318:	2601bf0c 	strcs	fp, [r1], -ip, lsl #30
d001031c:	27002600 	strcs	r2, [r0, -r0, lsl #12]
d0010320:	4980e00a 	stmibmi	r0, {r1, r3, sp, lr, pc}
d0010324:	44794620 	ldrbtmi	r4, [r9], #-1568	; 0xfffff9e0
d0010328:	ff4bf7ff 			; <UNDEFINED> instruction: 0xff4bf7ff
d001032c:	4620b140 	strtmi	fp, [r0], -r0, asr #2
d0010330:	ffd6f7ff 			; <UNDEFINED> instruction: 0xffd6f7ff
d0010334:	43cf43c6 	bicmi	r4, pc, #402653187	; 0x18000003
d0010338:	3b016ae3 	blcc	0xd006aecc
d001033c:	e7dc62e3 	ldrb	r6, [ip, r3, ror #5]
d0010340:	46204979 			; <UNDEFINED> instruction: 0x46204979
d0010344:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d0010348:	b128ff3c 	msrlt	(UNDEF: 56), ip
d001034c:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010350:	4606ffc7 	strmi	pc, [r6], -r7, asr #31
d0010354:	e7ef460f 	strb	r4, [pc, pc, lsl #12]!
d0010358:	46204974 			; <UNDEFINED> instruction: 0x46204974
d001035c:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d0010360:	b130ff30 	teqlt	r0, r0, lsr pc	; <UNPREDICTABLE>
d0010364:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010368:	4246ffbb 	submi	pc, r6, #748	; 0x2ec
d001036c:	0741eb61 	strbeq	lr, [r1, -r1, ror #22]
d0010370:	4620e7e2 	strtmi	lr, [r0], -r2, ror #15
d0010374:	ff18f7ff 			; <UNDEFINED> instruction: 0xff18f7ff
d0010378:	1c5a6ae3 	mrrcne	10, 14, r6, sl, cr3
d001037c:	62e22a20 	rscvs	r2, r2, #32, 20	; 0x20000
d0010380:	2201d904 	andcs	sp, r1, #4, 18	; 0x10000
d0010384:	62e32600 	rscvs	r2, r3, #0, 12
d0010388:	e7c86322 	strb	r6, [r8, r2, lsr #6]
d001038c:	44794968 	ldrbtmi	r4, [r9], #-2408	; 0xfffff698
d0010390:	ff17f7ff 			; <UNDEFINED> instruction: 0xff17f7ff
d0010394:	4620b168 	strtmi	fp, [r0], -r8, ror #2
d0010398:	fb3cf000 	blx	0xd0f4c3a2
d001039c:	4965460f 	stmdbmi	r5!, {r0, r1, r2, r3, r9, sl, lr}^
d00103a0:	44794606 	ldrbtmi	r4, [r9], #-1542	; 0xfffff9fa
d00103a4:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d00103a8:	bba0ff0c 	bllt	0xce84ffe0
d00103ac:	63232301 			; <UNDEFINED> instruction: 0x63232301
d00103b0:	6a65e031 	bvs	0xd198847c
d00103b4:	8028f8d4 	ldrdhi	pc, [r8], -r4	; <UNPREDICTABLE>
d00103b8:	d2514545 	subsle	r4, r1, #289406976	; 0x11400000
d00103bc:	f1a07828 			; <UNDEFINED> instruction: 0xf1a07828
d00103c0:	2b090330 	blcs	0xd0251088
d00103c4:	eba8d849 	bl	0xcea464f0
d00103c8:	2b020305 	blcs	0xd0090fe4
d00103cc:	2830dd27 	ldmdacs	r0!, {r0, r1, r2, r5, r8, sl, fp, ip, lr, pc}
d00103d0:	786bd12a 	stmdavc	fp!, {r1, r3, r5, r8, ip, lr, pc}^
d00103d4:	03dff003 	bicseq	pc, pc, #3
d00103d8:	d1272b58 			; <UNDEFINED> instruction: 0xd1272b58
d00103dc:	21103502 	tstcs	r0, r2, lsl #10
d00103e0:	25006265 	strcs	r6, [r0, #-613]	; 0xfffffd9b
d00103e4:	27002600 	strcs	r2, [r0, -r0, lsl #12]
d00103e8:	0901f04f 	stmdbeq	r1, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d00103ec:	45906a62 	ldrmi	r6, [r0, #2658]	; 0xa62
d00103f0:	8092f240 	addshi	pc, r2, r0, asr #4
d00103f4:	f7ff7810 			; <UNDEFINED> instruction: 0xf7ff7810
d00103f8:	4281ff2d 	addmi	pc, r1, #45, 30	; 0xb4
d00103fc:	b91dd818 	ldmdblt	sp, {r3, r4, fp, ip, lr, pc}
d0010400:	45902301 	ldrmi	r2, [r0, #769]	; 0x301
d0010404:	d9066323 	stmdble	r6, {r0, r1, r5, r8, r9, sp, lr}
d0010408:	f0037813 			; <UNDEFINED> instruction: 0xf0037813
d001040c:	2b5503df 	blcs	0xd1551390
d0010410:	3201d101 	andcc	sp, r1, #1073741824	; 0x40000000
d0010414:	6ae36262 	bvs	0xcf8e8da4
d0010418:	62e33b01 	rscvs	r3, r3, #1024	; 0x400
d001041c:	2830e78c 	ldmdacs	r0!, {r2, r3, r7, r8, r9, sl, sp, lr, pc}
d0010420:	210abf14 	tstcs	sl, r4, lsl pc
d0010424:	e7dc2108 	ldrb	r2, [ip, r8, lsl #2]
d0010428:	e7da210a 	ldrb	r2, [sl, sl, lsl #2]
d001042c:	e7d82108 	ldrb	r2, [r8, r8, lsl #2]
d0010430:	35011c53 	strcc	r1, [r1, #-3155]	; 0xfffff3ad
d0010434:	78106263 	ldmdavc	r0, {r0, r1, r5, r6, r9, sp, lr}
d0010438:	ff0cf7ff 			; <UNDEFINED> instruction: 0xff0cf7ff
d001043c:	fbb343c3 	blx	0xcece1352
d0010440:	42b3f3f1 	adcsmi	pc, r3, #-1006632957	; 0xc4000003
d0010444:	2306fba1 	movwcs	pc, #27553	; 0x6ba1	; <UNPREDICTABLE>
d0010448:	f8c4bf38 			; <UNDEFINED> instruction: 0xf8c4bf38
d001044c:	18169030 	ldmdane	r6, {r4, r5, ip, pc}
d0010450:	3307fb01 	movwcc	pc, #31489	; 0x7b01	; <UNPREDICTABLE>
d0010454:	0700f143 	streq	pc, [r0, -r3, asr #2]
d0010458:	f7ffe7c8 			; <UNDEFINED> instruction: 0xf7ffe7c8
d001045c:	b930feef 	ldmdblt	r0!, {r0, r1, r2, r3, r5, r6, r7, r9, sl, fp, ip, sp, lr, pc}
d0010460:	63232301 			; <UNDEFINED> instruction: 0x63232301
d0010464:	27002600 	strcs	r2, [r0, -r0, lsl #12]
d0010468:	3201e7d5 	andcc	lr, r1, #55836672	; 0x3540000
d001046c:	6a626262 	bvs	0xd18a8dfc
d0010470:	d9084590 	stmdble	r8, {r4, r7, r8, sl, lr}
d0010474:	46087811 			; <UNDEFINED> instruction: 0x46087811
d0010478:	fee0f7ff 	mcr2	7, 7, pc, cr0, cr15, {7}	; <UNPREDICTABLE>
d001047c:	d1f42800 	mvnsle	r2, r0, lsl #16
d0010480:	29093930 	stmdbcs	r9, {r4, r5, r8, fp, ip, sp}
d0010484:	1b52d9f1 	blne	0xd14c6c50
d0010488:	d1362a07 	teqle	r6, r7, lsl #20
d001048c:	4628492a 	strtmi	r4, [r8], -sl, lsr #18
d0010490:	44799201 	ldrbtmi	r9, [r9], #-513	; 0xfffffdff
d0010494:	f876f009 			; <UNDEFINED> instruction: 0xf876f009
d0010498:	bb709a01 	bllt	0xd1c36ca4
d001049c:	46204927 	strtmi	r4, [r0], -r7, lsr #18
d00104a0:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d00104a4:	4680fe8e 	strmi	pc, [r0], lr, lsl #29
d00104a8:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d00104ac:	6a61fe7d 	bvs	0xd188fea8
d00104b0:	42b16aa6 	adcsmi	r6, r1, #679936	; 0xa6000
d00104b4:	7808d003 	stmdavc	r8, {r0, r1, ip, lr, pc}
d00104b8:	fec0f7ff 	mcr2	7, 6, pc, cr0, cr15, {7}	; <UNPREDICTABLE>
d00104bc:	2301b908 	movwcs	fp, #6408	; 0x1908
d00104c0:	6a626323 	bvs	0xd18a9154
d00104c4:	d9074296 	stmdble	r7, {r1, r2, r4, r7, r9, lr}
d00104c8:	46287815 			; <UNDEFINED> instruction: 0x46287815
d00104cc:	feb6f7ff 	mrc2	7, 5, pc, cr6, cr15, {7}
d00104d0:	3d30b980 			; <UNDEFINED> instruction: 0x3d30b980
d00104d4:	d90d2d09 	stmdble	sp, {r0, r3, r8, sl, fp, sp}
d00104d8:	68201a52 	stmdavs	r0!, {r1, r4, r6, r9, fp, ip}
d00104dc:	fe8cf7ff 	mcr2	7, 4, pc, cr12, cr15, {7}	; <UNPREDICTABLE>
d00104e0:	17c12700 	strbne	r2, [r1, r0, lsl #14]
d00104e4:	0ff643ce 	svceq	0x00f643ce
d00104e8:	0f00f1b8 	svceq	0x0000f1b8
d00104ec:	4914d093 	ldmdbmi	r4, {r0, r1, r4, r7, ip, lr, pc}
d00104f0:	e7574479 			; <UNDEFINED> instruction: 0xe7574479
d00104f4:	62623201 	rsbvs	r3, r2, #268435456	; 0x10000000
d00104f8:	4629e7e3 	strtmi	lr, [r9], -r3, ror #15
d00104fc:	f7ff6820 			; <UNDEFINED> instruction: 0xf7ff6820
d0010500:	2800fe7b 	stmdacs	r0, {r0, r1, r3, r4, r5, r6, r9, sl, fp, ip, sp, lr, pc}
d0010504:	6823dbae 	stmdavs	r3!, {r1, r2, r3, r5, r7, r8, r9, fp, ip, lr, pc}
d0010508:	fb022248 	blx	0xd0098e32
d001050c:	f5003000 			; <UNDEFINED> instruction: 0xf5003000
d0010510:	e9d0402b 	ldmib	r0, {r0, r1, r3, r5, lr}^
d0010514:	e77e6732 			; <UNDEFINED> instruction: 0xe77e6732
d0010518:	f47f2d00 			; <UNDEFINED> instruction: 0xf47f2d00
d001051c:	e76faf7c 			; <UNDEFINED> instruction: 0xe76faf7c
d0010520:	ffffffc0 			; <UNDEFINED> instruction: 0xffffffc0
d0010524:	ffffffa2 			; <UNDEFINED> instruction: 0xffffffa2
d0010528:	ffffff86 			; <UNDEFINED> instruction: 0xffffff86
d001052c:	ffffff70 			; <UNDEFINED> instruction: 0xffffff70
d0010530:	ffffff40 			; <UNDEFINED> instruction: 0xffffff40
d0010534:	ffffff2e 			; <UNDEFINED> instruction: 0xffffff2e
d0010538:	fffffe40 			; <UNDEFINED> instruction: 0xfffffe40
d001053c:	fffffe2e 			; <UNDEFINED> instruction: 0xfffffe2e
d0010540:	fffffde0 			; <UNDEFINED> instruction: 0xfffffde0

Disassembly of section .text.pp_mul:

d001054c <.text.pp_mul>:
d001054c:	4ff0e92d 	svcmi	0x00f0e92d
d0010550:	8b02ed2d 	blhi	0xd00cba0c
d0010554:	4606b089 	strmi	fp, [r6], -r9, lsl #1
d0010558:	fec2f7ff 	mcr2	7, 6, pc, cr2, cr15, {7}	; <UNPREDICTABLE>
d001055c:	46044b67 	strmi	r4, [r4], -r7, ror #22
d0010560:	447b460d 	ldrbtmi	r4, [fp], #-1549	; 0xfffff9f3
d0010564:	3a10ee08 	bcc	0xd044bd8c
d0010568:	447b4b65 	ldrbtmi	r4, [fp], #-2917	; 0xfffff49b
d001056c:	3a90ee08 	bcc	0xce44bd94
d0010570:	1a10ee18 	bne	0xd044bdd8
d0010574:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0010578:	b178fe24 	cmnlt	r8, r4, lsr #28	; <UNPREDICTABLE>
d001057c:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0010580:	4361feaf 	msrmi	SPSR_c, #2800	; 0xaf0
d0010584:	3400fba4 	strcc	pc, [r0], #-2980	; 0xfffff45c
d0010588:	1105fb00 	tstne	r5, r0, lsl #22	; <UNPREDICTABLE>
d001058c:	3400e9cd 	strcc	lr, [r0], #-2509	; 0xfffff633
d0010590:	440b9b01 	strmi	r9, [fp], #-2817	; 0xfffff4ff
d0010594:	e9dd9301 	ldmib	sp, {r0, r8, r9, ip, pc}^
d0010598:	e7e94500 	strb	r4, [r9, r0, lsl #10]!
d001059c:	1a90ee18 	bne	0xce44be04
d00105a0:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d00105a4:	9006fe0e 	andls	pc, r6, lr, lsl #28
d00105a8:	4956b938 	ldmdbmi	r6, {r3, r4, r5, r8, fp, ip, sp, pc}^
d00105ac:	44794630 	ldrbtmi	r4, [r9], #-1584	; 0xfffff9d0
d00105b0:	fe07f7ff 	mcr2	7, 0, pc, cr7, cr15, {7}	; <UNPREDICTABLE>
d00105b4:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d00105b8:	46308099 			; <UNDEFINED> instruction: 0x46308099
d00105bc:	fe90f7ff 	mrc2	7, 4, pc, cr0, cr15, {7}
d00105c0:	0100e9cd 	smlabteq	r0, sp, r9, lr
d00105c4:	2300e9dd 	movwcs	lr, #2525	; 0x9dd
d00105c8:	d1094313 	tstle	r9, r3, lsl r3
d00105cc:	29006b71 	stmdbcs	r0, {r0, r4, r5, r6, r8, r9, fp, sp, lr}
d00105d0:	2301d0e1 	movwcs	sp, #4321	; 0x10e1
d00105d4:	63332400 	teqvs	r3, #0, 8
d00105d8:	e9cd2300 	stmib	sp, {r8, r9, sp}^
d00105dc:	e7da3400 	ldrb	r3, [sl, r0, lsl #8]
d00105e0:	f1752c00 			; <UNDEFINED> instruction: 0xf1752c00
d00105e4:	e9cd0300 	stmib	sp, {r8, r9}^
d00105e8:	da044502 	ble	0xd01219f8
d00105ec:	eb654262 	bl	0xd1960f7c
d00105f0:	e9cd0345 	stmib	sp, {r0, r2, r6, r8, r9}^
d00105f4:	e9dd2302 	ldmib	sp, {r1, r8, r9, sp}^
d00105f8:	2a002300 	bcs	0xd0019200
d00105fc:	2304e9cd 	movwcs	lr, #18893	; 0x49cd
d0010600:	0300f173 	movweq	pc, #371	; 0x173	; <UNPREDICTABLE>
d0010604:	e9ddda06 	ldmib	sp, {r1, r2, r9, fp, ip, lr, pc}^
d0010608:	42522300 	subsmi	r2, r2, #0, 6
d001060c:	0343eb63 	movteq	lr, #15203	; 0x3b63
d0010610:	2304e9cd 	movwcs	lr, #18893	; 0x49cd
d0010614:	0a00f04f 	beq	0xd004c758
d0010618:	0b00f04f 	bleq	0xd004c75c
d001061c:	f04f213f 			; <UNDEFINED> instruction: 0xf04f213f
d0010620:	46570c01 	ldrbmi	r0, [r7], -r1, lsl #24
d0010624:	eb1a46d8 	bl	0xd06a218c
d0010628:	f1c1030a 			; <UNDEFINED> instruction: 0xf1c1030a
d001062c:	f1a10920 			; <UNDEFINED> instruction: 0xf1a10920
d0010630:	461a0e20 	ldrmi	r0, [sl], -r0, lsr #28
d0010634:	030beb4b 	movweq	lr, #47947	; 0xbb4b
d0010638:	9b029307 	blls	0xd00b525c
d001063c:	b01cf8dd 			; <UNDEFINED> instruction: 0xb01cf8dd
d0010640:	f001fa23 			; <UNDEFINED> instruction: 0xf001fa23
d0010644:	fa039b03 	blx	0xd00f7258
d0010648:	fa23f909 	blx	0xd090ea74
d001064c:	ea40fe0e 	b	0xd104fe8c
d0010650:	ea400009 	b	0xd101067c
d0010654:	f1a1000e 			; <UNDEFINED> instruction: 0xf1a1000e
d0010658:	f0000e20 			; <UNDEFINED> instruction: 0xf0000e20
d001065c:	ea400001 	b	0xd1010668
d0010660:	f1c10a02 			; <UNDEFINED> instruction: 0xf1c10a02
d0010664:	e9dd0020 	ldmib	sp, {r5}^
d0010668:	459b2304 	ldrmi	r2, [fp, #772]	; 0x304
d001066c:	4592bf08 	ldrmi	fp, [r2, #3848]	; 0xf08
d0010670:	fa0cd313 	blx	0xd03452c4
d0010674:	fa2cfe0e 	blx	0xd0b4feb4
d0010678:	9b04f000 	blls	0xd014c680
d001067c:	0000ea4e 	andeq	lr, r0, lr, asr #20
d0010680:	fe01fa0c 	vseleq.f32	s30, s2, s24
d0010684:	0a03ebba 	beq	0xd010b574
d0010688:	ea4e9b05 	b	0xd13b72a4
d001068c:	ea400e07 	b	0xd1013eb0
d0010690:	eb6b0008 	bl	0xd1ad06b8
d0010694:	46770b03 	ldrbtmi	r0, [r7], -r3, lsl #22
d0010698:	39014680 	stmdbcc	r1, {r7, r9, sl, lr}
d001069c:	9b06d2c3 	blls	0xd01c51b0
d00106a0:	9b01b1c3 	blls	0xd007cdb4
d00106a4:	0fdb0fea 	svceq	0x00db0fea
d00106a8:	7fd5ebb3 	svcvc	0x00d5ebb3
d00106ac:	f04fbf15 			; <UNDEFINED> instruction: 0xf04fbf15
d00106b0:	f06f4100 			; <UNDEFINED> instruction: 0xf06f4100
d00106b4:	20004100 	andcs	r4, r0, r0, lsl #2
d00106b8:	30fff04f 	rscscc	pc, pc, pc, asr #32
d00106bc:	bf084541 	svclt	0x00084541
d00106c0:	d38642b8 	orrle	r4, r6, #184, 4	; 0x8000000b
d00106c4:	d002429a 	mulle	r2, sl, r2
d00106c8:	eb68427f 	bl	0xd1a210cc
d00106cc:	e9cd0848 	stmib	sp, {r3, r6, fp}^
d00106d0:	e7607800 	strb	r7, [r0, -r0, lsl #16]!
d00106d4:	f1752c00 			; <UNDEFINED> instruction: 0xf1752c00
d00106d8:	e9cd0300 	stmib	sp, {r8, r9}^
d00106dc:	f6bfab00 			; <UNDEFINED> instruction: 0xf6bfab00
d00106e0:	f1daaf5a 			; <UNDEFINED> instruction: 0xf1daaf5a
d00106e4:	eb6b0300 	bl	0xd1ad12ec
d00106e8:	e776044b 	ldrb	r0, [r6, -fp, asr #8]!
d00106ec:	46294620 	strtmi	r4, [r9], -r0, lsr #12
d00106f0:	ecbdb009 	ldc	0, cr11, [sp], #36	; 0x24
d00106f4:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d00106f8:	bf008ff0 	svclt	0x00008ff0
d00106fc:	ffffffde 			; <UNDEFINED> instruction: 0xffffffde
d0010700:	ffffffd8 			; <UNDEFINED> instruction: 0xffffffd8
d0010704:	ffffff96 			; <UNDEFINED> instruction: 0xffffff96

Disassembly of section .text.pp_add:

d0010708 <.text.pp_add>:
d0010708:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d001070c:	46064f12 			; <UNDEFINED> instruction: 0x46064f12
d0010710:	8048f8df 	ldrdhi	pc, [r8], #-143	; 0xffffff71
d0010714:	ff1af7ff 			; <UNDEFINED> instruction: 0xff1af7ff
d0010718:	4604447f 			; <UNDEFINED> instruction: 0x4604447f
d001071c:	44f8460d 	ldrbtmi	r4, [r8], #1549	; 0x60d
d0010720:	46304639 			; <UNDEFINED> instruction: 0x46304639
d0010724:	fd4df7ff 	stc2l	7, cr15, [sp, #-1020]	; 0xfffffc04
d0010728:	4630b130 			; <UNDEFINED> instruction: 0x4630b130
d001072c:	ff0ef7ff 			; <UNDEFINED> instruction: 0xff0ef7ff
d0010730:	eb411824 	bl	0xd10567c8
d0010734:	e7f30505 	ldrb	r0, [r3, r5, lsl #10]!
d0010738:	46304641 	ldrtmi	r4, [r0], -r1, asr #12
d001073c:	fd41f7ff 	stc2l	7, cr15, [r1, #-1020]	; 0xfffffc04
d0010740:	4630b130 			; <UNDEFINED> instruction: 0x4630b130
d0010744:	ff02f7ff 			; <UNDEFINED> instruction: 0xff02f7ff
d0010748:	eb651a24 	bl	0xd1956fe0
d001074c:	e7e70501 	strb	r0, [r7, r1, lsl #10]!
d0010750:	46294620 	strtmi	r4, [r9], -r0, lsr #12
d0010754:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d0010758:	fffffbb2 			; <UNDEFINED> instruction: 0xfffffbb2
d001075c:	fffffbae 			; <UNDEFINED> instruction: 0xfffffbae

Disassembly of section .text.pp_shift:

d0010768 <.text.pp_shift>:
d0010768:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d001076c:	805cf8df 	ldrsbhi	pc, [ip], #-143	; 0xffffff71	; <UNPREDICTABLE>
d0010770:	f8df4604 			; <UNDEFINED> instruction: 0xf8df4604
d0010774:	f7ff905c 			; <UNDEFINED> instruction: 0xf7ff905c
d0010778:	44f8ffc7 	ldrbtmi	pc, [r8], #4039	; 0xfc7	; <UNPREDICTABLE>
d001077c:	460e4605 	strmi	r4, [lr], -r5, lsl #12
d0010780:	464144f9 			; <UNDEFINED> instruction: 0x464144f9
d0010784:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010788:	b160fd1c 	msrlt	SPSR_, ip, lsl sp
d001078c:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010790:	2900ffbb 	stmdbcs	r0, {r0, r1, r3, r4, r5, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0010794:	2820bf08 	stmdacs	r0!, {r3, r8, r9, sl, fp, ip, sp, pc}
d0010798:	2301d302 	movwcs	sp, #4866	; 0x1302
d001079c:	e7f06323 	ldrb	r6, [r0, r3, lsr #6]!
d00107a0:	26004085 	strcs	r4, [r0], -r5, lsl #1
d00107a4:	4649e7ed 	strbmi	lr, [r9], -sp, ror #15
d00107a8:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d00107ac:	b140fd0a 	cmplt	r0, sl, lsl #26	; <UNPREDICTABLE>
d00107b0:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d00107b4:	2900ffa9 	stmdbcs	r0, {r0, r3, r5, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d00107b8:	2820bf08 	stmdacs	r0!, {r3, r8, r9, sl, fp, ip, sp, pc}
d00107bc:	40c5d2ed 	sbcmi	sp, r5, sp, ror #5
d00107c0:	4628e7ef 	strtmi	lr, [r8], -pc, ror #15
d00107c4:	e8bd4631 	pop	{r0, r4, r5, r9, sl, lr}
d00107c8:	bf0083f8 	svclt	0x000083f8
d00107cc:	ffffffe2 			; <UNDEFINED> instruction: 0xffffffe2
d00107d0:	ffffffdf 			; <UNDEFINED> instruction: 0xffffffdf

Disassembly of section .text.pp_rel:

d00107e0 <.text.pp_rel>:
d00107e0:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d00107e4:	46064f24 	strmi	r4, [r6], -r4, lsr #30
d00107e8:	8090f8df 			; <UNDEFINED> instruction: 0x8090f8df
d00107ec:	ffbcf7ff 			; <UNDEFINED> instruction: 0xffbcf7ff
d00107f0:	908cf8df 	ldrdls	pc, [ip], pc	; <UNPREDICTABLE>
d00107f4:	460d4604 	strmi	r4, [sp], -r4, lsl #12
d00107f8:	44f8447f 	ldrbtmi	r4, [r8], #1151	; 0x47f
d00107fc:	463944f9 			; <UNDEFINED> instruction: 0x463944f9
d0010800:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0010804:	b158fcde 	ldrsblt	pc, [r8, #-206]	; 0xffffff32	; <UNPREDICTABLE>
d0010808:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d001080c:	42a0ffad 	adcmi	pc, r0, #692	; 0x2b4
d0010810:	0305eb71 	movweq	lr, #23409	; 0x5b71
d0010814:	2401bfac 	strcs	fp, [r1], #-4012	; 0xfffff054
d0010818:	b2e42400 	rsclt	r2, r4, #0, 8
d001081c:	e7ee2500 	strb	r2, [lr, r0, lsl #10]!
d0010820:	46304641 	ldrtmi	r4, [r0], -r1, asr #12
d0010824:	fccdf7ff 	stc2l	7, cr15, [sp], {255}	; 0xff
d0010828:	4630b130 			; <UNDEFINED> instruction: 0x4630b130
d001082c:	ff9cf7ff 			; <UNDEFINED> instruction: 0xff9cf7ff
d0010830:	eb754284 	bl	0xd1d61248
d0010834:	e7ed0301 	strb	r0, [sp, r1, lsl #6]!
d0010838:	46304649 	ldrtmi	r4, [r0], -r9, asr #12
d001083c:	fcc1f7ff 	stc2l	7, cr15, [r1], {255}	; 0xff
d0010840:	4630b148 	ldrtmi	fp, [r0], -r8, asr #2
d0010844:	ff90f7ff 			; <UNDEFINED> instruction: 0xff90f7ff
d0010848:	eb754284 	bl	0xd1d61260
d001084c:	bfb40301 	svclt	0x00b40301
d0010850:	24002401 	strcs	r2, [r0], #-1025	; 0xfffffbff
d0010854:	490be7e1 	stmdbmi	fp, {r0, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d0010858:	44794630 	ldrbtmi	r4, [r9], #-1584	; 0xfffff9d0
d001085c:	fcb1f7ff 	ldc2	7, cr15, [r1], #1020	; 0x3fc
d0010860:	4630b130 			; <UNDEFINED> instruction: 0x4630b130
d0010864:	ff80f7ff 			; <UNDEFINED> instruction: 0xff80f7ff
d0010868:	eb7142a0 	bl	0xd1c612f0
d001086c:	e7ee0305 	strb	r0, [lr, r5, lsl #6]!
d0010870:	46294620 	strtmi	r4, [r9], -r0, lsr #12
d0010874:	83f8e8bd 	mvnshi	lr, #12386304	; 0xbd0000
d0010878:	ffffffd8 			; <UNDEFINED> instruction: 0xffffffd8
d001087c:	ffffffd9 			; <UNDEFINED> instruction: 0xffffffd9
d0010880:	ffffffda 			; <UNDEFINED> instruction: 0xffffffda
d0010884:	ffffff7e 			; <UNDEFINED> instruction: 0xffffff7e

Disassembly of section .text.pp_eq:

d0010890 <.text.pp_eq>:
d0010890:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d0010894:	46064f15 			; <UNDEFINED> instruction: 0x46064f15
d0010898:	8054f8df 	ldrsbhi	pc, [r4], #-143	; 0xffffff71	; <UNPREDICTABLE>
d001089c:	ffa0f7ff 			; <UNDEFINED> instruction: 0xffa0f7ff
d00108a0:	4604447f 			; <UNDEFINED> instruction: 0x4604447f
d00108a4:	44f8460d 	ldrbtmi	r4, [r8], #1549	; 0x60d
d00108a8:	46304639 			; <UNDEFINED> instruction: 0x46304639
d00108ac:	fc89f7ff 	stc2	7, cr15, [r9], {255}	; 0xff
d00108b0:	4630b150 			; <UNDEFINED> instruction: 0x4630b150
d00108b4:	ff94f7ff 			; <UNDEFINED> instruction: 0xff94f7ff
d00108b8:	bf0642a9 	svclt	0x000642a9
d00108bc:	240142a0 	strcs	r4, [r1], #-672	; 0xfffffd60
d00108c0:	b2e42400 	rsclt	r2, r4, #0, 8
d00108c4:	e7ef2500 	strb	r2, [pc, r0, lsl #10]!
d00108c8:	46304641 	ldrtmi	r4, [r0], -r1, asr #12
d00108cc:	fc79f7ff 	ldc2l	7, cr15, [r9], #-1020	; 0xfffffc04
d00108d0:	4630b140 	ldrtmi	fp, [r0], -r0, asr #2
d00108d4:	ff84f7ff 			; <UNDEFINED> instruction: 0xff84f7ff
d00108d8:	bf0a42a9 	svclt	0x000a42a9
d00108dc:	240142a0 	strcs	r4, [r1], #-672	; 0xfffffd60
d00108e0:	e7ee2400 	strb	r2, [lr, r0, lsl #8]!
d00108e4:	46294620 	strtmi	r4, [r9], -r0, lsr #12
d00108e8:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d00108ec:	ffffffe4 			; <UNDEFINED> instruction: 0xffffffe4
d00108f0:	ffffffe1 			; <UNDEFINED> instruction: 0xffffffe1

Disassembly of section .text.pp_band:

d00108f4 <.text.pp_band>:
d00108f4:	4604b570 			; <UNDEFINED> instruction: 0x4604b570
d00108f8:	ffcaf7ff 			; <UNDEFINED> instruction: 0xffcaf7ff
d00108fc:	460d4606 	strmi	r4, [sp], -r6, lsl #12
d0010900:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010904:	6a63fc51 	bvs	0xd190fa50
d0010908:	428b6aa1 	addmi	r6, fp, #659456	; 0xa1000
d001090c:	781ad20f 	ldmdavc	sl, {r0, r1, r2, r3, r9, ip, lr, pc}
d0010910:	d10c2a26 	tstle	ip, r6, lsr #20
d0010914:	42911c5a 	addsmi	r1, r1, #23040	; 0x5a00
d0010918:	785bd902 	ldmdavc	fp, {r1, r8, fp, ip, lr, pc}^
d001091c:	d0062b26 	andle	r2, r6, r6, lsr #22
d0010920:	62624620 	rsbvs	r4, r2, #32, 12	; 0x2000000
d0010924:	ffb4f7ff 			; <UNDEFINED> instruction: 0xffb4f7ff
d0010928:	400d4006 	andmi	r4, sp, r6
d001092c:	4630e7e8 	ldrtmi	lr, [r0], -r8, ror #15
d0010930:	bd704629 	ldcllt	6, cr4, [r0, #-164]!	; 0xffffff5c

Disassembly of section .text.pp_xor:

d0010938 <.text.pp_xor>:
d0010938:	4f0ab5f8 	svcmi	0x000ab5f8
d001093c:	f7ff4606 			; <UNDEFINED> instruction: 0xf7ff4606
d0010940:	4605ffd9 			; <UNDEFINED> instruction: 0x4605ffd9
d0010944:	447f460c 	ldrbtmi	r4, [pc], #-1548	; 0xd001094c
d0010948:	46304639 			; <UNDEFINED> instruction: 0x46304639
d001094c:	fc39f7ff 	ldc2	7, cr15, [r9], #-1020	; 0xfffffc04
d0010950:	4628b910 			; <UNDEFINED> instruction: 0x4628b910
d0010954:	bdf84621 	ldcllt	6, cr4, [r8, #132]!	; 0x84
d0010958:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d001095c:	4045ffcb 	submi	pc, r5, fp, asr #31
d0010960:	e7f1404c 	ldrb	r4, [r1, ip, asr #32]!
d0010964:	ffffffea 			; <UNDEFINED> instruction: 0xffffffea

Disassembly of section .text.pp_bor:

d0010968 <.text.pp_bor>:
d0010968:	4604b570 			; <UNDEFINED> instruction: 0x4604b570
d001096c:	ffe4f7ff 			; <UNDEFINED> instruction: 0xffe4f7ff
d0010970:	460d4606 	strmi	r4, [sp], -r6, lsl #12
d0010974:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010978:	6a63fc17 	bvs	0xd190f9dc
d001097c:	428b6aa1 	addmi	r6, fp, #659456	; 0xa1000
d0010980:	781ad20f 	ldmdavc	sl, {r0, r1, r2, r3, r9, ip, lr, pc}
d0010984:	d10c2a7c 	tstle	ip, ip, ror sl
d0010988:	42911c5a 	addsmi	r1, r1, #23040	; 0x5a00
d001098c:	785bd902 	ldmdavc	fp, {r1, r8, fp, ip, lr, pc}^
d0010990:	d0062b7c 	andle	r2, r6, ip, ror fp
d0010994:	62624620 	rsbvs	r4, r2, #32, 12	; 0x2000000
d0010998:	ffcef7ff 			; <UNDEFINED> instruction: 0xffcef7ff
d001099c:	430d4306 	movwmi	r4, #54022	; 0xd306
d00109a0:	4630e7e8 	ldrtmi	lr, [r0], -r8, ror #15
d00109a4:	bd704629 	ldcllt	6, cr4, [r0, #-164]!	; 0xffffff5c

Disassembly of section .text.pp_and:

d00109ac <.text.pp_and>:
d00109ac:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d00109b0:	46064f16 			; <UNDEFINED> instruction: 0x46064f16
d00109b4:	ffd8f7ff 			; <UNDEFINED> instruction: 0xffd8f7ff
d00109b8:	460d4604 	strmi	r4, [sp], -r4, lsl #12
d00109bc:	4639447f 			; <UNDEFINED> instruction: 0x4639447f
d00109c0:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d00109c4:	b918fbfe 	ldmdblt	r8, {r1, r2, r3, r4, r5, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d00109c8:	46294620 	strtmi	r4, [r9], -r0, lsr #12
d00109cc:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d00109d0:	8034f8d6 	ldrsbthi	pc, [r4], -r6	; <UNPREDICTABLE>
d00109d4:	0f00f1b8 	svceq	0x0000f1b8
d00109d8:	ea54d014 	b	0xd1544a30
d00109dc:	bf140305 	svclt	0x00140305
d00109e0:	23002301 	movwcs	r2, #769	; 0x301
d00109e4:	46306373 			; <UNDEFINED> instruction: 0x46306373
d00109e8:	ffbef7ff 			; <UNDEFINED> instruction: 0xffbef7ff
d00109ec:	0305ea54 	movweq	lr, #23124	; 0x5a54
d00109f0:	8034f8c6 	eorshi	pc, r4, r6, asr #17
d00109f4:	ea50d008 	b	0xd1444a1c
d00109f8:	bf140301 	svclt	0x00140301
d00109fc:	24002401 	strcs	r2, [r0], #-1025	; 0xfffffbff
d0010a00:	e7dc17e5 	ldrb	r1, [ip, r5, ror #15]
d0010a04:	e7ed4643 	strb	r4, [sp, r3, asr #12]!
d0010a08:	e7f92400 	ldrb	r2, [r9, r0, lsl #8]!
d0010a0c:	ffffffe8 			; <UNDEFINED> instruction: 0xffffffe8

Disassembly of section .text.pp_or:

d0010a14 <.text.pp_or>:
d0010a14:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d0010a18:	46064f15 			; <UNDEFINED> instruction: 0x46064f15
d0010a1c:	ffc6f7ff 			; <UNDEFINED> instruction: 0xffc6f7ff
d0010a20:	460d4604 	strmi	r4, [sp], -r4, lsl #12
d0010a24:	4639447f 			; <UNDEFINED> instruction: 0x4639447f
d0010a28:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0010a2c:	b918fbca 	ldmdblt	r8, {r1, r3, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d0010a30:	46294620 	strtmi	r4, [r9], -r0, lsr #12
d0010a34:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d0010a38:	8034f8d6 	ldrsbthi	pc, [r4], -r6	; <UNPREDICTABLE>
d0010a3c:	0f00f1b8 	svceq	0x0000f1b8
d0010a40:	ea54d014 	b	0xd1544a98
d0010a44:	bf0c0305 	svclt	0x000c0305
d0010a48:	23002301 	movwcs	r2, #769	; 0x301
d0010a4c:	46306373 			; <UNDEFINED> instruction: 0x46306373
d0010a50:	ffacf7ff 			; <UNDEFINED> instruction: 0xffacf7ff
d0010a54:	43294320 			; <UNDEFINED> instruction: 0x43294320
d0010a58:	8034f8c6 	eorshi	pc, r4, r6, asr #17
d0010a5c:	ea502500 	b	0xd1419e64
d0010a60:	bf140301 	svclt	0x00140301
d0010a64:	24002401 	strcs	r2, [r0], #-1025	; 0xfffffbff
d0010a68:	e7dcb2e4 	ldrb	fp, [ip, r4, ror #5]
d0010a6c:	e7ed4643 	strb	r4, [sp, r3, asr #12]!
d0010a70:	ffffffe8 			; <UNDEFINED> instruction: 0xffffffe8

Disassembly of section .text.find_api_constant.isra.0.constprop.0:

d0010a74 <.text.find_api_constant.isra.0.constprop.0>:
d0010a74:	47f0e92d 	ldrbmi	lr, [r0, sp, lsr #18]!
d0010a78:	46804c0e 	strmi	r4, [r0], lr, lsl #24
d0010a7c:	2600468a 	strcs	r4, [r0], -sl, lsl #13
d0010a80:	f64d447c 			; <UNDEFINED> instruction: 0xf64d447c
d0010a84:	f5040944 			; <UNDEFINED> instruction: 0xf5040944
d0010a88:	37204750 			; <UNDEFINED> instruction: 0x37204750
d0010a8c:	429e683b 	addsmi	r6, lr, #3866624	; 0x3b0000
d0010a90:	2500d303 	strcs	sp, [r0, #-771]	; 0xfffffcfd
d0010a94:	e8bd4628 	pop	{r3, r5, r9, sl, lr}
d0010a98:	eb0487f0 	bl	0xd0132a60
d0010a9c:	46510509 	ldrbmi	r0, [r1], -r9, lsl #10
d0010aa0:	34244640 	strtcc	r4, [r4], #-1600	; 0xfffff9c0
d0010aa4:	f7ff462a 			; <UNDEFINED> instruction: 0xf7ff462a
d0010aa8:	2800fbfb 	stmdacs	r0, {r0, r1, r3, r4, r5, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d0010aac:	3601d1f2 			; <UNDEFINED> instruction: 0x3601d1f2
d0010ab0:	bf00e7ec 	svclt	0x0000e7ec
d0010ab4:	0000b45c 	andeq	fp, r0, ip, asr r4

Disassembly of section .text.find_global.isra.0.constprop.0:

d0010ab8 <.text.find_global.isra.0.constprop.0>:
d0010ab8:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d0010abc:	46804e12 	pkhbtmi	r4, r0, r2, lsl #28
d0010ac0:	2400460f 	strcs	r4, [r0], #-1551	; 0xfffff9f1
d0010ac4:	f506447e 			; <UNDEFINED> instruction: 0xf506447e
d0010ac8:	f50635af 			; <UNDEFINED> instruction: 0xf50635af
d0010acc:	350439ba 	strcc	r3, [r4, #-2490]	; 0xfffff646
d0010ad0:	3004f8d9 	ldrdcc	pc, [r4], -r9
d0010ad4:	d302429c 	movwle	r4, #8860	; 0x229c
d0010ad8:	30fff04f 	rscscc	pc, pc, pc, asr #32
d0010adc:	f895e00e 			; <UNDEFINED> instruction: 0xf895e00e
d0010ae0:	7a332029 	bvc	0xd0cd8b8c
d0010ae4:	d10b429a 			; <UNDEFINED> instruction: 0xd10b429a
d0010ae8:	42bb686b 	adcsmi	r6, fp, #7012352	; 0x6b0000
d0010aec:	463ad108 	ldrtmi	sp, [sl], -r8, lsl #2
d0010af0:	68284641 	stmdavs	r8!, {r0, r6, r9, sl, lr}
d0010af4:	fd46f008 	stc2l	0, cr15, [r6, #-32]	; 0xffffffe0
d0010af8:	4620b910 			; <UNDEFINED> instruction: 0x4620b910
d0010afc:	83f8e8bd 	mvnshi	lr, #12386304	; 0xbd0000
d0010b00:	352c3401 	strcc	r3, [ip, #-1025]!	; 0xfffffbff
d0010b04:	bf00e7e4 	svclt	0x0000e7e4
d0010b08:	0000b418 	andeq	fp, r0, r8, lsl r4

Disassembly of section .text.enter_header.isra.0.constprop.0:

d0010cac <.text.enter_header.isra.0.constprop.0>:
d0010cac:	4ff0e92d 	svcmi	0x00f0e92d
d0010cb0:	6480f8df 	strvs	pc, [r0], #2271	; 0x8df
d0010cb4:	447e4698 	ldrbtmi	r4, [lr], #-1688	; 0xfffff968
d0010cb8:	8b02ed2d 	blhi	0xd00cc174
d0010cbc:	f5ad6ef3 			; <UNDEFINED> instruction: 0xf5ad6ef3
d0010cc0:	9c9b7d0f 	ldcls	13, cr7, [fp], {15}
d0010cc4:	91069005 	tstls	r6, r5
d0010cc8:	b9b39207 	ldmiblt	r3!, {r0, r1, r2, r9, ip, pc}
d0010ccc:	b13c6db4 	teqlt	ip, r4	; <illegal shifter operand>
d0010cd0:	46202400 	strtmi	r2, [r0], -r0, lsl #8
d0010cd4:	7d0ff50d 	cfstr32vc	mvfx15, [pc, #-52]	; 0xd0010ca8
d0010cd8:	8b02ecbd 	blhi	0xd00cbfd4
d0010cdc:	8ff0e8bd 	svchi	0x00f0e8bd
d0010ce0:	3454f8df 	ldrbcc	pc, [r4], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d0010ce4:	65b3447b 	ldrvs	r4, [r3, #1147]!	; 0x47b
d0010ce8:	f8c69b05 			; <UNDEFINED> instruction: 0xf8c69b05
d0010cec:	65f38068 	ldrbvs	r8, [r3, #104]!	; 0x68
d0010cf0:	66339b06 	ldrtvs	r9, [r3], -r6, lsl #22
d0010cf4:	66739b07 	ldrbtvs	r9, [r3], -r7, lsl #22
d0010cf8:	1e63e7eb 	cdpne	7, 6, cr14, cr3, cr11, {7}
d0010cfc:	d9062bfe 	stmdble	r6, {r1, r2, r3, r4, r5, r6, r7, r8, r9, fp, sp}
d0010d00:	2c006db4 	stccs	13, cr6, [r0], {180}	; 0xb4
d0010d04:	f8dfd1e4 			; <UNDEFINED> instruction: 0xf8dfd1e4
d0010d08:	447b3434 	ldrbtmi	r3, [fp], #-1076	; 0xfffffbcc
d0010d0c:	f10de7eb 			; <UNDEFINED> instruction: 0xf10de7eb
d0010d10:	46220a38 			; <UNDEFINED> instruction: 0x46220a38
d0010d14:	4650999a 			; <UNDEFINED> instruction: 0x4650999a
d0010d18:	fc24f008 	stc2	0, cr15, [r4], #-32	; 0xffffffe0
d0010d1c:	46502300 	ldrbmi	r2, [r0], -r0, lsl #6
d0010d20:	3004f80a 	andcc	pc, r4, sl, lsl #16
d0010d24:	f826f00a 			; <UNDEFINED> instruction: 0xf826f00a
d0010d28:	d8122802 	ldmdale	r2, {r1, fp, sp}
d0010d2c:	3410f8df 	ldrcc	pc, [r0], #-2271	; 0xfffff721
d0010d30:	6d9c447b 	cfldrsvs	mvf4, [ip, #492]	; 0x1ec
d0010d34:	d1cb2c00 	bicle	r2, fp, r0, lsl #24
d0010d38:	2408f8df 	strcs	pc, [r8], #-2271	; 0xfffff721
d0010d3c:	659a447a 	ldrvs	r4, [sl, #1146]	; 0x47a
d0010d40:	f8c39a05 			; <UNDEFINED> instruction: 0xf8c39a05
d0010d44:	65da8068 	ldrbvs	r8, [sl, #104]	; 0x68
d0010d48:	661a9a06 	ldrvs	r9, [sl], -r6, lsl #20
d0010d4c:	665a9a07 	ldrbvs	r9, [sl], -r7, lsl #20
d0010d50:	3802e7bf 	stmdacc	r2, {r0, r1, r2, r3, r4, r5, r7, r8, r9, sl, sp, lr, pc}
d0010d54:	445049fc 	ldrbmi	r4, [r0], #-2556	; 0xfffff604
d0010d58:	f00a4479 			; <UNDEFINED> instruction: 0xf00a4479
d0010d5c:	4604f817 			; <UNDEFINED> instruction: 0x4604f817
d0010d60:	d1e32800 	mvnle	r2, r0, lsl #16
d0010d64:	f44fab0d 			; <UNDEFINED> instruction: 0xf44fab0d
d0010d68:	af4e7280 	svcge	0x004e7280
d0010d6c:	9202900d 	andls	r9, r2, #13
d0010d70:	46024651 			; <UNDEFINED> instruction: 0x46024651
d0010d74:	3700e9cd 	strcc	lr, [r0, -sp, asr #19]
d0010d78:	6ef54603 	cdpvs	6, 15, cr4, cr5, cr3, {0}
d0010d7c:	47a86f70 			; <UNDEFINED> instruction: 0x47a86f70
d0010d80:	4635b358 			; <UNDEFINED> instruction: 0x4635b358
d0010d84:	f50646a1 			; <UNDEFINED> instruction: 0xf50646a1
d0010d88:	96095b2e 	strls	r5, [r9], -lr, lsr #22
d0010d8c:	3000f8db 	ldrdcc	pc, [r0], -fp
d0010d90:	d2074599 	andle	r4, r7, #641728512	; 0x26400000
d0010d94:	7000f505 	andvc	pc, r0, r5, lsl #10
d0010d98:	f5054639 			; <UNDEFINED> instruction: 0xf5054639
d0010d9c:	f00975a6 			; <UNDEFINED> instruction: 0xf00975a6
d0010da0:	bb08fff5 	bllt	0xd0250d7c
d0010da4:	447d4de9 	ldrbtmi	r4, [sp], #-3561	; 0xfffff217
d0010da8:	532ef505 	msrpl	CPSR_fsx, #20971520	; 0x1400000
d0010dac:	681b930a 	ldmdavs	fp, {r1, r3, r8, r9, ip, pc}
d0010db0:	f0404599 			; <UNDEFINED> instruction: 0xf0404599
d0010db4:	f1b98111 			; <UNDEFINED> instruction: 0xf1b98111
d0010db8:	d1180f20 	tstle	r8, r0, lsr #30
d0010dbc:	2b006dab 	blcs	0xd002c470
d0010dc0:	4be3d186 	blmi	0xcf9053e0
d0010dc4:	65ab447b 	strvs	r4, [fp, #1147]!	; 0x47b
d0010dc8:	f8c59b05 			; <UNDEFINED> instruction: 0xf8c59b05
d0010dcc:	65eb8068 	strbvs	r8, [fp, #104]!	; 0x68
d0010dd0:	662b9b06 	strtvs	r9, [fp], -r6, lsl #22
d0010dd4:	666b9b07 	strbtvs	r9, [fp], -r7, lsl #22
d0010dd8:	6db3e77b 	ldcvs	7, cr14, [r3, #492]!	; 0x1ec
d0010ddc:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0010de0:	4bdcaf77 	blmi	0xcf73cbc4
d0010de4:	e77e447b 			; <UNDEFINED> instruction: 0xe77e447b
d0010de8:	0901f109 	stmdbeq	r1, {r0, r3, r8, ip, sp, lr, pc}
d0010dec:	f642e7ce 			; <UNDEFINED> instruction: 0xf642e7ce
d0010df0:	58ea3384 	stmiapl	sl!, {r2, r7, r8, r9, ip, sp}^
d0010df4:	4300f5d2 	movwmi	pc, #1490	; 0x5d2	; <UNPREDICTABLE>
d0010df8:	6dabd106 	stfvsd	f5, [fp, #24]!
d0010dfc:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0010e00:	4bd5af67 	blmi	0xcf57cba4
d0010e04:	e7de447b 			; <UNDEFINED> instruction: 0xe7de447b
d0010e08:	7180f44f 	orrvc	pc, r0, pc, asr #8
d0010e0c:	5b2ef505 	blpl	0xd0bce228
d0010e10:	91029308 	tstls	r2, r8, lsl #6
d0010e14:	f10ba94e 			; <UNDEFINED> instruction: 0xf10ba94e
d0010e18:	91010b08 	tstls	r1, r8, lsl #22
d0010e1c:	1a10ee08 	bne	0xd044c644
d0010e20:	445aa90d 	ldrbmi	sl, [sl], #-2317	; 0xfffff6f3
d0010e24:	910b9100 	mrsls	r9, (UNDEF: 27)
d0010e28:	6f684651 	svcvs	0x00684651
d0010e2c:	47b86eef 	ldrmi	r6, [r8, pc, ror #29]!
d0010e30:	b9309b08 	ldmdblt	r0!, {r3, r8, r9, fp, ip, pc}
d0010e34:	2c006dac 	stccs	13, cr6, [r0], {172}	; 0xac
d0010e38:	af4af47f 	svcge	0x004af47f
d0010e3c:	447b4bc7 	ldrbtmi	r4, [fp], #-3015	; 0xfffff439
d0010e40:	9a0be7c1 	bls	0xd030ad4c
d0010e44:	42936812 	addsmi	r6, r3, #1179648	; 0x120000
d0010e48:	4bc5d208 	blmi	0xcf185670
d0010e4c:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d0010e50:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0010e54:	4ac3af3d 	bmi	0xcf0fcb50
d0010e58:	e770447a 			; <UNDEFINED> instruction: 0xe770447a
d0010e5c:	3384f642 	orrcc	pc, r4, #69206016	; 0x4200000
d0010e60:	58e82100 	stmiapl	r8!, {r8, sp}^
d0010e64:	f0094458 			; <UNDEFINED> instruction: 0xf0094458
d0010e68:	4682ff6f 	strmi	pc, [r2], pc, ror #30
d0010e6c:	d1ec2800 	mvnle	r2, r0, lsl #16
d0010e70:	f44f9b0a 			; <UNDEFINED> instruction: 0xf44f9b0a
d0010e74:	9a0a77a6 	bls	0xd02aed14
d0010e78:	0a10ee18 	beq	0xd044c6e0
d0010e7c:	9308681b 	movwls	r6, #34843	; 0x881b
d0010e80:	60133301 	andsvs	r3, r3, r1, lsl #6
d0010e84:	435f9b08 	cmpmi	pc, #8, 22	; 0x2000
d0010e88:	ff74f009 			; <UNDEFINED> instruction: 0xff74f009
d0010e8c:	1a10ee18 	bne	0xd044c6f4
d0010e90:	f5071c42 			; <UNDEFINED> instruction: 0xf5071c42
d0010e94:	18e87300 	stmiane	r8!, {r8, r9, ip, sp, lr}^
d0010e98:	fb64f008 	blx	0xd194cec2
d0010e9c:	3384f642 	orrcc	pc, r4, #69206016	; 0x4200000
d0010ea0:	58ea19e9 	stmiapl	sl!, {r0, r3, r5, r6, r7, r8, fp, ip}^
d0010ea4:	7542f505 	strbvc	pc, [r2, #-1285]	; 0xfffffafb	; <UNPREDICTABLE>
d0010ea8:	44939b0b 	ldrmi	r9, [r3], #2827	; 0xb0b
d0010eac:	2300f8c1 	movwcs	pc, #2241	; 0x8c1	; <UNPREDICTABLE>
d0010eb0:	4a9f681b 	bmi	0xce7eaf24
d0010eb4:	3304f8c1 	movwcc	pc, #18625	; 0x48c1	; <UNPREDICTABLE>
d0010eb8:	a005f847 	andge	pc, r5, r7, asr #16
d0010ebc:	0a03eb0b 	beq	0xd010baf0
d0010ec0:	d90945da 	stmdble	r9, {r1, r3, r4, r6, r7, r8, sl, lr}
d0010ec4:	3000f89b 	mulcc	r0, fp, r8
d0010ec8:	b2db3b09 	sbcslt	r3, fp, #9216	; 0x2400
d0010ecc:	d8032b17 	stmdale	r3, {r0, r1, r2, r4, r8, r9, fp, sp}
d0010ed0:	f303fa22 	vpmax.u8	d15, d3, d18
d0010ed4:	d41607db 	ldrle	r0, [r6], #-2011	; 0xfffff825
d0010ed8:	030bebaa 	movweq	lr, #48042	; 0xbbaa
d0010edc:	dd292b01 	fstmdbxle	r9!, {d2-d1}	;@ Deprecated
d0010ee0:	3000f89b 	mulcc	r0, fp, r8
d0010ee4:	d1252b2f 			; <UNDEFINED> instruction: 0xd1252b2f
d0010ee8:	3001f89b 	mulcc	r1, fp, r8
d0010eec:	d10d2b2f 	tstle	sp, pc, lsr #22
d0010ef0:	0302f10b 	movweq	pc, #8459	; 0x210b	; <UNPREDICTABLE>
d0010ef4:	469b459a 			; <UNDEFINED> instruction: 0x469b459a
d0010ef8:	f89bd9ee 			; <UNDEFINED> instruction: 0xf89bd9ee
d0010efc:	33011000 	movwcc	r1, #4096	; 0x1000
d0010f00:	d1f7290a 	mvnsle	r2, sl, lsl #18
d0010f04:	f10be7dc 			; <UNDEFINED> instruction: 0xf10be7dc
d0010f08:	e7d90b01 	ldrb	r0, [r9, r1, lsl #22]
d0010f0c:	d1112b2a 	tstle	r1, sl, lsr #22
d0010f10:	0b02f10b 	bleq	0xd00cd344
d0010f14:	0301f10b 	movweq	pc, #4363	; 0x110b	; <UNPREDICTABLE>
d0010f18:	d90b459a 	stmdble	fp, {r1, r3, r4, r7, r8, sl, lr}
d0010f1c:	1c01f813 	stcne	8, cr15, [r1], {19}
d0010f20:	d105292a 	tstle	r5, sl, lsr #18
d0010f24:	292f7819 	stmdbcs	pc!, {r0, r3, r4, fp, ip, sp, lr}	; <UNPREDICTABLE>
d0010f28:	f10bd102 			; <UNDEFINED> instruction: 0xf10bd102
d0010f2c:	e7c70b02 	strb	r0, [r7, r2, lsl #22]
d0010f30:	e7ef469b 			; <UNDEFINED> instruction: 0xe7ef469b
d0010f34:	030bebaa 	movweq	lr, #48042	; 0xbbaa
d0010f38:	dd452b06 	vstrle	d18, [r5, #-24]	; 0xffffffe8
d0010f3c:	2207498a 	andcs	r4, r7, #2260992	; 0x228000
d0010f40:	44794658 	ldrbtmi	r4, [r9], #-1624	; 0xfffff9a8
d0010f44:	fb1ef008 	blx	0xd07ccf6e
d0010f48:	d13d2800 	teqle	sp, r0, lsl #16
d0010f4c:	0507f10b 	streq	pc, [r7, #-267]	; 0xfffffef5
d0010f50:	d00545aa 	andle	r4, r5, sl, lsr #11
d0010f54:	3007f89b 	mulcc	r7, fp, r8
d0010f58:	d0012b20 	andle	r2, r1, r0, lsr #22
d0010f5c:	d1332b09 	teqle	r3, r9, lsl #22
d0010f60:	462945aa 	strtmi	r4, [r9], -sl, lsr #11
d0010f64:	462bd94d 	strtmi	sp, [fp], -sp, asr #18
d0010f68:	2b01f813 	blcs	0xd008efbc
d0010f6c:	d0462a20 	suble	r2, r6, r0, lsr #20
d0010f70:	d0442a09 	suble	r2, r4, r9, lsl #20
d0010f74:	3501462a 	strcc	r4, [r1, #-1578]	; 0xfffff9d6
d0010f78:	b000f892 	mullt	r0, r2, r8
d0010f7c:	f7ff4658 			; <UNDEFINED> instruction: 0xf7ff4658
d0010f80:	b920f95d 	stmdblt	r0!, {r0, r2, r3, r4, r6, r8, fp, ip, sp, lr, pc}
d0010f84:	0b30f1ab 	bleq	0xd0c4d638
d0010f88:	0f09f1bb 	svceq	0x0009f1bb
d0010f8c:	45aad802 	strmi	sp, [sl, #2050]!	; 0x802
d0010f90:	d8ef462a 	stmiale	pc!, {r1, r3, r5, r9, sl, lr}^	; <UNPREDICTABLE>
d0010f94:	d0171a55 	andsle	r1, r7, r5, asr sl
d0010f98:	f7ff7808 			; <UNDEFINED> instruction: 0xf7ff7808
d0010f9c:	b198f94f 	orrslt	pc, r8, pc, asr #18
d0010fa0:	d8112d3f 	ldmdale	r1, {r0, r1, r2, r3, r4, r5, r8, sl, fp, sp}
d0010fa4:	a1c4f8df 	ldrdge	pc, [r4, #143]	; 0x8f
d0010fa8:	300bf207 	andcc	pc, fp, r7, lsl #4
d0010fac:	44fa462a 	ldrbtmi	r4, [sl], #1578	; 0x62a
d0010fb0:	f0084450 			; <UNDEFINED> instruction: 0xf0084450
d0010fb4:	9b08fad7 	blls	0xd024fb18
d0010fb8:	72a6f44f 	adcvc	pc, r6, #1325400064	; 0x4f000000
d0010fbc:	aa03fb02 	bge	0xd010fbcc
d0010fc0:	44aa2300 	strtmi	r2, [sl], #768	; 0x300
d0010fc4:	330bf88a 	movwcc	pc, #47242	; 0xb88a	; <UNPREDICTABLE>
d0010fc8:	f6424969 			; <UNDEFINED> instruction: 0xf6424969
d0010fcc:	980d3284 	stmdals	sp, {r2, r7, r9, ip, sp}
d0010fd0:	588b4479 	stmpl	fp, {r0, r3, r4, r5, r6, sl, lr}
d0010fd4:	508b4403 	addpl	r4, fp, r3, lsl #8
d0010fd8:	27014a66 	strcs	r4, [r1, -r6, ror #20]
d0010fdc:	7a13447a 	bvc	0xd04e21cc
d0010fe0:	f44f409f 	vst4.32	{d20-d23}, [pc :64]
d0010fe4:	fb0373a6 	blx	0xd00ede86
d0010fe8:	b2bf2309 	adcslt	r2, pc, #603979776	; 0x24000000
d0010fec:	230af893 	movwcs	pc, #43155	; 0xa893	; <UNPREDICTABLE>
d0010ff0:	f8b3b14a 			; <UNDEFINED> instruction: 0xf8b3b14a
d0010ff4:	421f3308 	andsmi	r3, pc, #8, 6	; 0x20000000
d0010ff8:	2401d005 	strcs	sp, [r1], #-5
d0010ffc:	461de669 	ldrmi	lr, [sp], -r9, ror #12
d0011000:	462ae7ae 	strtmi	lr, [sl], -lr, lsr #15
d0011004:	4d5ce7c6 	ldclmi	7, cr14, [ip, #-792]	; 0xfffffce8
d0011008:	f8d5447d 			; <UNDEFINED> instruction: 0xf8d5447d
d001100c:	2b0c31fc 	blcs	0xd031d804
d0011010:	6dabd106 	stfvsd	f5, [fp, #24]!
d0011014:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0011018:	4b58ae5b 	blmi	0xd163c98c
d001101c:	e6d2447b 			; <UNDEFINED> instruction: 0xe6d2447b
d0011020:	71a6f44f 			; <UNDEFINED> instruction: 0x71a6f44f
d0011024:	f109fb01 			; <UNDEFINED> instruction: 0xf109fb01
d0011028:	f893186b 			; <UNDEFINED> instruction: 0xf893186b
d001102c:	b96b330b 	stmdblt	fp!, {r0, r1, r3, r8, r9, ip, sp}^
d0011030:	447b4b53 	ldrbtmi	r4, [fp], #-2899	; 0xfffff4ad
d0011034:	454a6f9a 	strbmi	r6, [sl, #-3994]	; 0xfffff066
d0011038:	4b52d121 	blmi	0xd14c54c4
d001103c:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d0011040:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0011044:	4a50ae45 	bmi	0xd143c960
d0011048:	e678447a 			; <UNDEFINED> instruction: 0xe678447a
d001104c:	310bf201 	tstcc	fp, r1, lsl #4	; <UNPREDICTABLE>
d0011050:	0a00f04f 	beq	0xd004d194
d0011054:	3b88f64a 	blcc	0xce24e984
d0011058:	f5054429 			; <UNDEFINED> instruction: 0xf5054429
d001105c:	3588454f 	strcc	r4, [r8, #1359]	; 0x54f
d0011060:	459a682b 	ldrmi	r6, [sl, #2091]	; 0x82b
d0011064:	eb06d2e4 	bl	0xd01c5bfc
d0011068:	9108000b 	tstls	r8, fp
d001106c:	f0093648 			; <UNDEFINED> instruction: 0xf0093648
d0011070:	2800fe8d 	stmdacs	r0, {r0, r2, r3, r7, r9, sl, fp, ip, sp, lr, pc}
d0011074:	f10ad0c1 			; <UNDEFINED> instruction: 0xf10ad0c1
d0011078:	99080a01 	stmdbls	r8, {r0, r9, fp}
d001107c:	f8d3e7f0 			; <UNDEFINED> instruction: 0xf8d3e7f0
d0011080:	230001fc 	movwcs	r0, #508	; 0x1fc
d0011084:	d14b4283 	smlalbble	r4, fp, r3, r2
d0011088:	c100f8df 	ldrdgt	pc, [r0, -pc]
d001108c:	f24d1c59 	vfma.f32	<illegal reg q8.5>, <illegal reg q6.5>, <illegal reg q4.5>
d0011090:	44fc050c 	ldrbtmi	r0, [ip], #1292	; 0x50c
d0011094:	1e43eb0c 	vmlane.f64	d30, d3, d12
d0011098:	f8dc3304 			; <UNDEFINED> instruction: 0xf8dc3304
d001109c:	eb0c0004 	bl	0xd03110b4
d00110a0:	f8cc1343 			; <UNDEFINED> instruction: 0xf8cc1343
d00110a4:	f85c11fc 			; <UNDEFINED> instruction: 0xf85c11fc
d00110a8:	60581005 	subsvs	r1, r8, r5
d00110ac:	000cf8dc 	ldrdeq	pc, [ip], -ip
d00110b0:	1098f8ce 	addsne	pc, r8, lr, asr #17
d00110b4:	f50c6098 			; <UNDEFINED> instruction: 0xf50c6098
d00110b8:	f8dc502e 			; <UNDEFINED> instruction: 0xf8dc502e
d00110bc:	f8dc3014 			; <UNDEFINED> instruction: 0xf8dc3014
d00110c0:	30084074 	andcc	r4, r8, r4, ror r0
d00110c4:	6010f8dc 			; <UNDEFINED> instruction: 0x6010f8dc
d00110c8:	5000f8dc 	ldrdpl	pc, [r0], -ip
d00110cc:	4080f8ce 	addmi	pc, r0, lr, asr #17
d00110d0:	f8ce2401 			; <UNDEFINED> instruction: 0xf8ce2401
d00110d4:	f8ce507c 			; <UNDEFINED> instruction: 0xf8ce507c
d00110d8:	f8cc608c 			; <UNDEFINED> instruction: 0xf8cc608c
d00110dc:	e9ce9078 	stmib	lr, {r3, r4, r5, r6, ip, pc}^
d00110e0:	f44f3224 	vst1.8	{d19-d22}, [pc :128], r4
d00110e4:	fb0373a6 	blx	0xd00edf86
d00110e8:	eb0cf309 	bl	0xd034dd14
d00110ec:	f5030203 			; <UNDEFINED> instruction: 0xf5030203
d00110f0:	f8b27300 			; <UNDEFINED> instruction: 0xf8b27300
d00110f4:	44631308 	strbtmi	r1, [r3], #-776	; 0xfffffcf8
d00110f8:	f8d2430f 			; <UNDEFINED> instruction: 0xf8d2430f
d00110fc:	f8cc1300 			; <UNDEFINED> instruction: 0xf8cc1300
d0011100:	f8a23074 			; <UNDEFINED> instruction: 0xf8a23074
d0011104:	44017308 	strmi	r7, [r1], #-776	; 0xfffffcf8
d0011108:	2304f8d2 	movwcs	pc, #18642	; 0x48d2	; <UNPREDICTABLE>
d001110c:	1000f8cc 	andne	pc, r0, ip, asr #17
d0011110:	2004f8cc 	andcs	pc, r4, ip, asr #17
d0011114:	e9cc2200 	stmib	ip, {r9, sp}^
d0011118:	f8cc4404 			; <UNDEFINED> instruction: 0xf8cc4404
d001111c:	e5d8200c 	ldrb	r2, [r8, #12]
d0011120:	31209909 			; <UNDEFINED> instruction: 0x31209909
d0011124:	6f499109 	svcvs	0x00499109
d0011128:	d0864589 	addle	r4, r6, r9, lsl #11
d001112c:	e7a93301 	str	r3, [r9, r1, lsl #6]!
d0011130:	00800013 	addeq	r0, r0, r3, lsl r0
d0011134:	0000b226 	andeq	fp, r0, r6, lsr #4
d0011138:	fffffe24 			; <UNDEFINED> instruction: 0xfffffe24
d001113c:	fffffe2b 			; <UNDEFINED> instruction: 0xfffffe2b
d0011140:	0000b1ac 	andeq	fp, r0, ip, lsr #3
d0011144:	fffffe19 			; <UNDEFINED> instruction: 0xfffffe19
d0011148:	fffffdfa 			; <UNDEFINED> instruction: 0xfffffdfa
d001114c:	0000b136 	andeq	fp, r0, r6, lsr r1
d0011150:	fffffde5 			; <UNDEFINED> instruction: 0xfffffde5
d0011154:	fffffd9e 			; <UNDEFINED> instruction: 0xfffffd9e
d0011158:	fffffdc5 			; <UNDEFINED> instruction: 0xfffffdc5
d001115c:	fffffdaf 			; <UNDEFINED> instruction: 0xfffffdaf
d0011160:	0000b090 	muleq	r0, r0, r0
d0011164:	fffffdc4 			; <UNDEFINED> instruction: 0xfffffdc4
d0011168:	fffffd07 			; <UNDEFINED> instruction: 0xfffffd07
d001116c:	0000af2e 	andeq	sl, r0, lr, lsr #30
d0011170:	0000af0c 	andeq	sl, r0, ip, lsl #30
d0011174:	0000af00 	andeq	sl, r0, r0, lsl #30
d0011178:	0000aed4 	ldrdeq	sl, [r0], -r4
d001117c:	fffffc35 			; <UNDEFINED> instruction: 0xfffffc35
d0011180:	0000aeaa 	andeq	sl, r0, sl, lsr #29
d0011184:	0000aea0 	andeq	sl, r0, r0, lsr #29
d0011188:	fffffc29 			; <UNDEFINED> instruction: 0xfffffc29
d001118c:	0000ae4a 	andeq	sl, r0, sl, asr #28

Disassembly of section .text.escape_byte.isra.0.constprop.0:

d00111c8 <.text.escape_byte.isra.0.constprop.0>:
d00111c8:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d00111cc:	461f9e08 	ldrmi	r9, [pc], -r8, lsl #28
d00111d0:	f8dd4680 			; <UNDEFINED> instruction: 0xf8dd4680
d00111d4:	68359024 	ldmdavs	r5!, {r2, r5, ip, pc}
d00111d8:	60331c6b 	eorsvs	r1, r3, fp, ror #24
d00111dc:	2c78782c 	ldclcs	8, cr7, [r8], #-176	; 0xffffff50
d00111e0:	2c6dd811 	stclcs	8, cr13, [sp], #-68	; 0xffffffbc
d00111e4:	2c3fd825 	ldccs	8, cr13, [pc], #-148	; 0xd0011158
d00111e8:	2c21d84a 	stccs	8, cr13, [r1], #-296	; 0xfffffed8
d00111ec:	f1a4d90b 			; <UNDEFINED> instruction: 0xf1a4d90b
d00111f0:	fa5f0022 	blx	0xd17d1280
d00111f4:	2001fc80 	andcs	pc, r1, r0, lsl #25
d00111f8:	f00cfa00 			; <UNDEFINED> instruction: 0xf00cfa00
d00111fc:	c154f8df 	ldrsbgt	pc, [r4, #-143]	; 0xffffff71	; <UNPREDICTABLE>
d0011200:	0f0cea10 	svceq	0x000cea10
d0011204:	3c30d137 	ldfccd	f5, [r0], #-220	; 0xffffff24
d0011208:	d8672c07 	stmdale	r7!, {r0, r1, r2, sl, fp, sp}^
d001120c:	d032454b 	eorsle	r4, r2, fp, asr #10
d0011210:	3b30786b 	blcc	0xd0c2f3c4
d0011214:	d82e2b07 	stmdale	lr!, {r0, r1, r2, r8, r9, fp, sp}
d0011218:	60301ca8 	eorsvs	r1, r0, r8, lsr #25
d001121c:	786b4581 	stmdavc	fp!, {r0, r7, r8, sl, lr}^
d0011220:	0330f1a3 	teqeq	r0, #-1073741784	; 0xc0000028	; <UNPREDICTABLE>
d0011224:	04c4eb03 	strbeq	lr, [r4], #2819	; 0xb03
d0011228:	8084f040 	addhi	pc, r4, r0, asr #32
d001122c:	d8552cff 	ldmdale	r5, {r0, r1, r2, r3, r4, r5, r6, r7, sl, fp, sp}^
d0011230:	f1a4e021 			; <UNDEFINED> instruction: 0xf1a4e021
d0011234:	280a006e 	stmdacs	sl, {r1, r2, r3, r5, r6}
d0011238:	f20fd8e5 	vadd.i8	<illegal reg q6.5>, <illegal reg q15.5>, <illegal reg q10.5>
d001123c:	f85c0c0c 			; <UNDEFINED> instruction: 0xf85c0c0c
d0011240:	44840020 	strmi	r0, [r4], #32
d0011244:	bf004760 	svclt	0x00004760
d0011248:	00000105 	andeq	r0, r0, r5, lsl #2
d001124c:	ffffffbf 			; <UNDEFINED> instruction: 0xffffffbf
d0011250:	ffffffbf 			; <UNDEFINED> instruction: 0xffffffbf
d0011254:	ffffffbf 			; <UNDEFINED> instruction: 0xffffffbf
d0011258:	0000002d 	andeq	r0, r0, sp, lsr #32
d001125c:	ffffffbf 			; <UNDEFINED> instruction: 0xffffffbf
d0011260:	00000089 	andeq	r0, r0, r9, lsl #1
d0011264:	ffffffbf 			; <UNDEFINED> instruction: 0xffffffbf
d0011268:	0000008d 	andeq	r0, r0, sp, lsl #1
d001126c:	ffffffbf 			; <UNDEFINED> instruction: 0xffffffbf
d0011270:	00000091 	muleq	r0, r1, r0
d0011274:	4620240d 	strtmi	r2, [r0], -sp, lsl #8
d0011278:	83f8e8bd 	mvnshi	lr, #12386304	; 0xbd0000
d001127c:	e7fa2408 	ldrb	r2, [sl, r8, lsl #8]!
d0011280:	005cf1a4 	subseq	pc, ip, r4, lsr #3
d0011284:	fc80fa5f 	stc2	10, cr15, [r0], {95}	; 0x5f	; <UNPREDICTABLE>
d0011288:	0f0af1bc 	svceq	0x000af1bc
d001128c:	280ad8bb 	stmdacs	sl, {r0, r1, r3, r4, r5, r7, fp, ip, lr, pc}
d0011290:	f20fd8b9 	vtst.8	d13, d31, d25
d0011294:	f85c0c0c 			; <UNDEFINED> instruction: 0xf85c0c0c
d0011298:	44840020 	strmi	r0, [r4], #32
d001129c:	bf004760 	svclt	0x00004760
d00112a0:	ffffffd7 			; <UNDEFINED> instruction: 0xffffffd7
d00112a4:	ffffff67 			; <UNDEFINED> instruction: 0xffffff67
d00112a8:	ffffff67 			; <UNDEFINED> instruction: 0xffffff67
d00112ac:	ffffff67 			; <UNDEFINED> instruction: 0xffffff67
d00112b0:	ffffff67 			; <UNDEFINED> instruction: 0xffffff67
d00112b4:	000000b1 	strheq	r0, [r0], -r1
d00112b8:	ffffffdd 			; <UNDEFINED> instruction: 0xffffffdd
d00112bc:	ffffff67 			; <UNDEFINED> instruction: 0xffffff67
d00112c0:	ffffff67 			; <UNDEFINED> instruction: 0xffffff67
d00112c4:	ffffff67 			; <UNDEFINED> instruction: 0xffffff67
d00112c8:	0000002d 	andeq	r0, r0, sp, lsr #32
d00112cc:	e7d2240c 	ldrb	r2, [r2, ip, lsl #8]
d00112d0:	e7d02409 	ldrb	r2, [r0, r9, lsl #8]
d00112d4:	e7ce240b 	strb	r2, [lr, fp, lsl #8]
d00112d8:	d106454b 	tstle	r6, fp, asr #10
d00112dc:	447d4d1e 	ldrbtmi	r4, [sp], #-3358	; 0xfffff2e2
d00112e0:	b9ec6dac 	stmiblt	ip!, {r2, r3, r5, r7, r8, sl, fp, sp, lr}^
d00112e4:	447b4b1d 	ldrbtmi	r4, [fp], #-2845	; 0xfffff4e3
d00112e8:	7868e01e 	stmdavc	r8!, {r1, r2, r3, r4, sp, lr, pc}^
d00112ec:	ffb2f7fe 			; <UNDEFINED> instruction: 0xffb2f7fe
d00112f0:	d0f32810 	rscsle	r2, r3, r0, lsl r8
d00112f4:	68352400 	ldmdavs	r5!, {sl, sp}
d00112f8:	d0bc45a9 	adcsle	r4, ip, r9, lsr #11
d00112fc:	f7fe7828 			; <UNDEFINED> instruction: 0xf7fe7828
d0011300:	2810ffa9 	ldmdacs	r0, {r0, r3, r5, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0011304:	1c6bd0b7 	stclne	0, cr13, [fp], #-732	; 0xfffffd24
d0011308:	60330124 	eorsvs	r0, r3, r4, lsr #2
d001130c:	f7fe7828 			; <UNDEFINED> instruction: 0xf7fe7828
d0011310:	4404ffa1 	strmi	pc, [r4], #-4001	; 0xfffff05f
d0011314:	d9ee2cff 	stmible	lr!, {r0, r1, r2, r3, r4, r5, r6, r7, sl, fp, sp}^
d0011318:	447d4d11 	ldrbtmi	r4, [sp], #-3345	; 0xfffff2ef
d001131c:	b10c6dac 	smlatblt	ip, ip, sp, r6
d0011320:	e7a82400 	str	r2, [r8, r0, lsl #8]!
d0011324:	447b4b0f 	ldrbtmi	r4, [fp], #-2831	; 0xfffff4f1
d0011328:	e9c566af 	stmib	r5, {r0, r1, r2, r3, r5, r7, r9, sl, sp, lr}^
d001132c:	e9c53816 	stmib	r5, {r1, r2, r4, fp, ip, sp}^
d0011330:	e7a01218 			; <UNDEFINED> instruction: 0xe7a01218
d0011334:	3b3078ab 	blcc	0xd0c2f5e8
d0011338:	f63f2b07 			; <UNDEFINED> instruction: 0xf63f2b07
d001133c:	1cebaf77 	stclne	15, cr10, [fp], #476	; 0x1dc
d0011340:	78ab6033 	stmiavc	fp!, {r0, r1, r4, r5, sp, lr}
d0011344:	eb033b30 	bl	0xd00e000c
d0011348:	e76f04c4 	strb	r0, [pc, -r4, asr #9]!
d001134c:	e792240a 	ldr	r2, [r2, sl, lsl #8]
d0011350:	e7902407 	ldr	r2, [r0, r7, lsl #8]
d0011354:	20000021 	andcs	r0, r0, r1, lsr #32
d0011358:	0000abfe 	strdeq	sl, [r0], -lr
d001135c:	fffffebe 			; <UNDEFINED> instruction: 0xfffffebe
d0011360:	0000abc2 	andeq	sl, r0, r2, asr #23
d0011364:	fffffe66 			; <UNDEFINED> instruction: 0xfffffe66

Disassembly of section .text.pp_value.constprop.0:

d0011398 <.text.pp_value.constprop.0>:
d0011398:	b570b084 	ldrblt	fp, [r0, #-132]!	; 0xffffff7c
d001139c:	ac12b08e 	ldcge	0, cr11, [r2], {142}	; 0x8e
d00113a0:	9e1bad12 	mrcls	13, 0, sl, cr11, cr2, {0}
d00113a4:	000fe884 	andeq	lr, pc, r4, lsl #17
d00113a8:	ac014b1c 			; <UNDEFINED> instruction: 0xac014b1c
d00113ac:	447b960a 	ldrbtmi	r9, [fp], #-1546	; 0xfffff9f6
d00113b0:	cd0f9300 	stcgt	3, cr9, [pc, #-0]	; 0xd00113b8
d00113b4:	e895c40f 	ldm	r5, {r0, r1, r2, r3, sl, lr, pc}
d00113b8:	e884000f 	stm	r4, {r0, r1, r2, r3}
d00113bc:	9b1a000f 	blls	0xd0691400
d00113c0:	2401466d 	strcs	r4, [r1], #-1645	; 0xfffff993
d00113c4:	23009309 	movwcs	r9, #777	; 0x309
d00113c8:	940d4628 	strls	r4, [sp], #-1576	; 0xfffff9d8
d00113cc:	930c930b 	movwls	r9, #49931	; 0xc30b
d00113d0:	fb20f7ff 	blx	0xd084f3d6
d00113d4:	e9c39b1c 	stmib	r3, {r2, r3, r4, r8, r9, fp, ip, pc}^
d00113d8:	46280100 	strtmi	r0, [r8], -r0, lsl #2
d00113dc:	fee4f7fe 	mcr2	7, 7, pc, cr4, cr14, {7}	; <UNPREDICTABLE>
d00113e0:	b9139b0c 	ldmdblt	r3, {r2, r3, r8, r9, fp, ip, pc}
d00113e4:	429e9b09 	addsmi	r9, lr, #9216	; 0x2400
d00113e8:	4b0dd014 	blmi	0xd0385440
d00113ec:	6d98447b 	cfldrsvs	mvf4, [r8, #492]	; 0x1ec
d00113f0:	490cb990 	stmdbmi	ip, {r4, r7, r8, fp, ip, sp, pc}
d00113f4:	2060f89d 	mlscs	r0, sp, r8, pc	; <UNPREDICTABLE>
d00113f8:	65994479 	ldrvs	r4, [r9, #1145]	; 0x479
d00113fc:	65d99915 	ldrbvs	r9, [r9, #2325]	; 0x915
d0011400:	e9c39916 	stmib	r3, {r1, r2, r4, r8, fp, ip, pc}^
d0011404:	9a191218 	bls	0xd0655c6c
d0011408:	b00e669a 	mullt	lr, sl, r6
d001140c:	4070e8bd 	ldrhtmi	lr, [r0], #-141	; 0xffffff73
d0011410:	4770b004 	ldrbmi	fp, [r0, -r4]!
d0011414:	e7f84620 	ldrb	r4, [r8, r0, lsr #12]!
d0011418:	e7f62000 	ldrb	r2, [r6, r0]!
d001141c:	0000ab2e 	andeq	sl, r0, lr, lsr #22
d0011420:	0000aaf0 	strdeq	sl, [r0], -r0
d0011424:	ffffff6c 			; <UNDEFINED> instruction: 0xffffff6c

Disassembly of section .text.preproc_active.constprop.0:

d0011428 <.text.preproc_active.constprop.0>:
d0011428:	f24d4a08 	vpmax.s8	d20, d13, d8
d001142c:	447a030c 	ldrbtmi	r0, [sl], #-780	; 0xfffffcf4
d0011430:	b14b58d3 	ldrdlt	r5, [fp, #-131]	; 0xffffff7d
d0011434:	534ff503 	movtpl	pc, #62723	; 0xf503	; <UNPREDICTABLE>
d0011438:	eb023321 	bl	0xd009e0c4
d001143c:	79580383 	ldmdbvc	r8, {r0, r1, r7, r8, r9}^
d0011440:	bf183800 	svclt	0x00183800
d0011444:	47702001 	ldrbmi	r2, [r0, -r1]!
d0011448:	47702001 	ldrbmi	r2, [r0, -r1]!
d001144c:	0000aaae 	andeq	sl, r0, lr, lsr #21

Disassembly of section .text.here.constprop.0:

d0011450 <.text.here.constprop.0>:
d0011450:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d0011454:	46044b10 			; <UNDEFINED> instruction: 0x46044b10
d0011458:	30042100 	andcc	r2, r4, r0, lsl #2
d001145c:	681a447b 	ldmdavs	sl, {r0, r1, r3, r4, r5, r6, sl, lr}
d0011460:	7a1f68dd 	bvc	0xd07eb7dc
d0011464:	6f9a4415 	svcvs	0x009a4415
d0011468:	f04f2a00 			; <UNDEFINED> instruction: 0xf04f2a00
d001146c:	e9d30218 	ldmib	r3, {r3, r4, r9}^
d0011470:	bfac9804 	svclt	0x00ac9804
d0011474:	26006f5e 			; <UNDEFINED> instruction: 0x26006f5e
d0011478:	f866f008 			; <UNDEFINED> instruction: 0xf866f008
d001147c:	7380f44f 	orrvc	pc, r0, #1325400064	; 0x4f000000
d0011480:	60254620 	eorvs	r4, r5, r0, lsr #12
d0011484:	900cf8c4 	andls	pc, ip, r4, asr #17
d0011488:	8010f8c4 	andshi	pc, r0, r4, asr #17
d001148c:	76276163 	strtvc	r6, [r7], -r3, ror #2
d0011490:	e8bd61e6 	pop	{r1, r2, r5, r6, r7, r8, sp, lr}
d0011494:	bf0083f8 	svclt	0x000083f8
d0011498:	0000aa80 	andeq	sl, r0, r0, lsl #21

Disassembly of section .text.peek.constprop.0:

d001149c <.text.peek.constprop.0>:
d001149c:	447b4b05 	ldrbtmi	r4, [fp], #-2821	; 0xfffff4fb
d00114a0:	441068da 	ldrmi	r6, [r0], #-2266	; 0xfffff726
d00114a4:	4290685a 	addsmi	r6, r0, #5898240	; 0x5a0000
d00114a8:	681bbf3a 	ldmdavs	fp, {r1, r3, r4, r5, r8, r9, sl, fp, ip, sp, pc}
d00114ac:	20005c18 	andcs	r5, r0, r8, lsl ip
d00114b0:	bf004770 	svclt	0x00004770
d00114b4:	0000aa3e 	andeq	sl, r0, lr, lsr sl

Disassembly of section .text.read_char.constprop.0:

d00114b8 <.text.read_char.constprop.0>:
d00114b8:	4b12b508 	blmi	0xd04be8e0
d00114bc:	68da447b 	ldmvs	sl, {r0, r1, r3, r4, r5, r6, sl, lr}^
d00114c0:	428a6859 	addmi	r6, sl, #5832704	; 0x590000
d00114c4:	6819d01b 	ldmdavs	r9, {r0, r1, r3, r4, ip, lr, pc}
d00114c8:	60d81c50 	sbcsvs	r1, r8, r0, asr ip
d00114cc:	290a5c89 	stmdbcs	sl, {r0, r3, r7, sl, fp, ip, lr}
d00114d0:	290dd006 	stmdbcs	sp, {r1, r2, ip, lr, pc}
d00114d4:	2000d10d 	andcs	sp, r0, sp, lsl #2
d00114d8:	ffe0f7ff 			; <UNDEFINED> instruction: 0xffe0f7ff
d00114dc:	d008280a 	andle	r2, r8, sl, lsl #16
d00114e0:	447b4b09 	ldrbtmi	r4, [fp], #-2825	; 0xfffff4f7
d00114e4:	3201691a 	andcc	r6, r1, #425984	; 0x68000
d00114e8:	2201611a 	andcs	r6, r1, #-2147483642	; 0x80000006
d00114ec:	4608615a 			; <UNDEFINED> instruction: 0x4608615a
d00114f0:	4a06bd08 	bmi	0xd01c0918
d00114f4:	6953447a 	ldmdbvs	r3, {r1, r3, r4, r5, r6, sl, lr}^
d00114f8:	61533301 	cmpvs	r3, r1, lsl #6
d00114fc:	2100e7f7 	strdcs	lr, [r0, -r7]
d0011500:	bf00e7f5 	svclt	0x0000e7f5
d0011504:	0000aa20 	andeq	sl, r0, r0, lsr #20
d0011508:	0000a9fa 	strdeq	sl, [r0], -sl	; <UNPREDICTABLE>
d001150c:	0000a9e8 	andeq	sl, r0, r8, ror #19

Disassembly of section .text.pp_line_end.constprop.0:

d0011510 <.text.pp_line_end.constprop.0>:
d0011510:	4c08b510 	cfstr32mi	mvfx11, [r8], {16}
d0011514:	68e2447c 	stmiavs	r2!, {r2, r3, r4, r5, r6, sl, lr}^
d0011518:	429a6863 	addsmi	r6, sl, #6488064	; 0x630000
d001151c:	2000d206 	andcs	sp, r0, r6, lsl #4
d0011520:	ffbcf7ff 			; <UNDEFINED> instruction: 0xffbcf7ff
d0011524:	d001280d 	andle	r2, r1, sp, lsl #16
d0011528:	d100280a 	tstle	r0, sl, lsl #16
d001152c:	f7ffbd10 			; <UNDEFINED> instruction: 0xf7ffbd10
d0011530:	e7f0ffc3 	ldrb	pc, [r0, r3, asr #31]!	; <UNPREDICTABLE>
d0011534:	0000a9c8 	andeq	sl, r0, r8, asr #19

Disassembly of section .text.error.constprop.0:

d0011538 <.text.error.constprop.0>:
d0011538:	447b4b07 	ldrbtmi	r4, [fp], #-2823	; 0xfffff4f9
d001153c:	b5306d9a 	ldrlt	r6, [r0, #-3482]!	; 0xfffff266
d0011540:	6a5db94a 	bvs	0xd177fa70
d0011544:	6b5a6a9c 	blvs	0xd16abfbc
d0011548:	1030f893 	mlasne	r0, r3, r8, pc	; <UNPREDICTABLE>
d001154c:	e9c3669a 	stmib	r3, {r1, r3, r4, r7, r9, sl, sp, lr}^
d0011550:	e9c30516 	stmib	r3, {r1, r2, r4, r8, sl}^
d0011554:	bd304118 	ldflts	f4, [r0, #-96]!	; 0xffffffa0
d0011558:	0000a9a2 	andeq	sl, r0, r2, lsr #19

Disassembly of section .text.scan.constprop.0:

d00116fc <.text.scan.constprop.0>:
d00116fc:	36b4f8df 	ssatcc	pc, #21, pc, asr #17	; <UNPREDICTABLE>
d0011700:	6d9b447b 	cfldrsvs	mvf4, [fp, #492]	; 0x1ec
d0011704:	4ff0e92d 	svcmi	0x00f0e92d
d0011708:	b09f4604 	addslt	r4, pc, r4, lsl #12
d001170c:	f0402b00 			; <UNDEFINED> instruction: 0xf0402b00
d0011710:	f8df830a 			; <UNDEFINED> instruction: 0xf8df830a
d0011714:	f8dfa6a4 			; <UNDEFINED> instruction: 0xf8dfa6a4
d0011718:	44fa76a4 	ldrbtmi	r7, [sl], #1700	; 0x6a4
d001171c:	f50a447f 			; <UNDEFINED> instruction: 0xf50a447f
d0011720:	330c4350 	movwcc	r4, #50000	; 0xc350
d0011724:	f7ff930c 			; <UNDEFINED> instruction: 0xf7ff930c
d0011728:	2800fe7f 	stmdacs	r0, {r0, r1, r2, r3, r4, r5, r6, r9, sl, fp, ip, sp, lr, pc}
d001172c:	2000d148 	andcs	sp, r0, r8, asr #2
d0011730:	feb4f7ff 	mrc2	7, 5, pc, cr4, cr15, {7}
d0011734:	d0352820 	eorsle	r2, r5, r0, lsr #16
d0011738:	d0332809 	eorsle	r2, r3, r9, lsl #16
d001173c:	6680f8df 	pkhtbvs	pc, r0, pc, asr #17	; <UNPREDICTABLE>
d0011740:	447e2823 	ldrbtmi	r2, [lr], #-2083	; 0xfffff7dd
d0011744:	687268f3 	ldmdavs	r2!, {r0, r1, r4, r5, r6, r7, fp, sp, lr}^
d0011748:	429ad12f 	addsmi	sp, sl, #-1073741813	; 0xc000000b
d001174c:	f10dd938 			; <UNDEFINED> instruction: 0xf10dd938
d0011750:	ad160838 	ldcge	8, cr0, [r6, #-224]	; 0xffffff20
d0011754:	f7ff4640 			; <UNDEFINED> instruction: 0xf7ff4640
d0011758:	f7fffe7b 			; <UNDEFINED> instruction: 0xf7fffe7b
d001175c:	f10dfead 			; <UNDEFINED> instruction: 0xf10dfead
d0011760:	46ec0e44 	strbtmi	r0, [ip], r4, asr #28
d0011764:	000fe8be 			; <UNDEFINED> instruction: 0x000fe8be
d0011768:	000fe8ac 	andeq	lr, pc, ip, lsr #17
d001176c:	3000f8de 	ldrdcc	pc, [r0], -lr
d0011770:	f8cc4628 			; <UNDEFINED> instruction: 0xf8cc4628
d0011774:	e8983000 	ldm	r8, {ip, sp}
d0011778:	f000000e 			; <UNDEFINED> instruction: 0xf000000e
d001177c:	6db3fcfd 	ldcvs	12, cr15, [r3, #1012]!	; 0x3f4
d0011780:	f0402b00 			; <UNDEFINED> instruction: 0xf0402b00
d0011784:	9b1b82cf 	blls	0xd06f22c8
d0011788:	7f91f5b3 	svcvc	0x0091f5b3
d001178c:	4626d0cb 	strtmi	sp, [r6], -fp, asr #1
d0011790:	c60fcd0f 	strgt	ip, [pc], -pc, lsl #26
d0011794:	000fe895 	muleq	pc, r5, r8	; <UNPREDICTABLE>
d0011798:	000fe886 	andeq	lr, pc, r6, lsl #17
d001179c:	b01f4620 	andslt	r4, pc, r0, lsr #12
d00117a0:	8ff0e8bd 	svchi	0x00f0e8bd
d00117a4:	fe88f7ff 	mcr2	7, 4, pc, cr8, cr15, {7}	; <UNPREDICTABLE>
d00117a8:	429ae7c1 	addsmi	lr, sl, #50593792	; 0x3040000
d00117ac:	f7ffd908 			; <UNDEFINED> instruction: 0xf7ffd908
d00117b0:	68f2feaf 	ldmvs	r2!, {r0, r1, r2, r3, r5, r7, r9, sl, fp, ip, sp, lr, pc}^
d00117b4:	429a6873 	addsmi	r6, sl, #7536640	; 0x730000
d00117b8:	f7ffd2b5 			; <UNDEFINED> instruction: 0xf7ffd2b5
d00117bc:	e7b2fe7d 			; <UNDEFINED> instruction: 0xe7b2fe7d
d00117c0:	f7ff2000 			; <UNDEFINED> instruction: 0xf7ff2000
d00117c4:	2820fe6b 	stmdacs	r0!, {r0, r1, r3, r5, r6, r9, sl, fp, ip, sp, lr, pc}
d00117c8:	f1a0d0f7 			; <UNDEFINED> instruction: 0xf1a0d0f7
d00117cc:	2b040309 	blcs	0xd01123f8
d00117d0:	282fd9f3 	stmdacs	pc!, {r0, r1, r4, r5, r6, r7, r8, fp, ip, lr, pc}	; <UNPREDICTABLE>
d00117d4:	2001d16e 	andcs	sp, r1, lr, ror #2
d00117d8:	fe60f7ff 	mcr2	7, 3, pc, cr0, cr15, {7}	; <UNPREDICTABLE>
d00117dc:	d110282f 	tstle	r0, pc, lsr #16
d00117e0:	55e0f8df 	strbpl	pc, [r0, #2271]!	; 0x8df	; <UNPREDICTABLE>
d00117e4:	6869447d 	stmdavs	r9!, {r0, r2, r3, r4, r5, r6, sl, lr}^
d00117e8:	68ee2000 	stmiavs	lr!, {sp}^
d00117ec:	fe56f7ff 	mrc2	7, 2, pc, cr6, cr15, {7}
d00117f0:	d098428e 	addsle	r4, r8, lr, lsl #5
d00117f4:	d096280a 	addsle	r2, r6, sl, lsl #16
d00117f8:	d094280d 	addsle	r2, r4, sp, lsl #16
d00117fc:	fe5cf7ff 	mrc2	7, 2, pc, cr12, cr15, {7}
d0011800:	282ae7f1 	stmdacs	sl!, {r0, r4, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d0011804:	f8dfd156 			; <UNDEFINED> instruction: 0xf8dfd156
d0011808:	a81655c0 	ldmdage	r6, {r6, r7, r8, sl, ip, lr}
d001180c:	fe20f7ff 	mcr2	7, 1, pc, cr0, cr15, {7}	; <UNPREDICTABLE>
d0011810:	f7ff447d 			; <UNDEFINED> instruction: 0xf7ff447d
d0011814:	f7fffe51 			; <UNDEFINED> instruction: 0xf7fffe51
d0011818:	68eafe4f 	stmiavs	sl!, {r0, r1, r2, r3, r6, r9, sl, fp, ip, sp, lr, pc}^
d001181c:	429a686b 	addsmi	r6, sl, #7012352	; 0x6b0000
d0011820:	8272f000 	rsbshi	pc, r2, #0
d0011824:	f7ff2000 			; <UNDEFINED> instruction: 0xf7ff2000
d0011828:	282afe39 	stmdacs	sl!, {r0, r3, r4, r5, r9, sl, fp, ip, sp, lr, pc}
d001182c:	2001d107 	andcs	sp, r1, r7, lsl #2
d0011830:	fe34f7ff 	mrc2	7, 1, pc, cr4, cr15, {7}
d0011834:	d102282f 	tstle	r2, pc, lsr #16
d0011838:	fe3ef7ff 	mrc2	7, 1, pc, cr14, cr15, {7}
d001183c:	f7ffe7bd 			; <UNDEFINED> instruction: 0xf7ffe7bd
d0011840:	e7eafe3b 			; <UNDEFINED> instruction: 0xe7eafe3b
d0011844:	eb073b01 	bl	0xd01e0450
d0011848:	015a1043 	cmpeq	sl, r3, asr #32
d001184c:	0098f8d0 			; <UNDEFINED> instruction: 0x0098f8d0
d0011850:	d0054281 	andle	r4, r5, r1, lsl #5
d0011854:	0574f8df 	ldrbeq	pc, [r4, #-2271]!	; 0xfffff721	; <UNPREDICTABLE>
d0011858:	f7ff4478 			; <UNDEFINED> instruction: 0xf7ff4478
d001185c:	e261fe6d 	rsb	pc, r1, #1744	; 0x6d0
d0011860:	f8c7327c 			; <UNDEFINED> instruction: 0xf8c7327c
d0011864:	19d331fc 	ldmibne	r3, {r2, r3, r4, r5, r6, r7, r8, ip, sp}^
d0011868:	e007f852 	and	pc, r7, r2, asr r8	; <UNPREDICTABLE>
d001186c:	0010f103 	andseq	pc, r0, r3, lsl #2
d0011870:	c004f8d3 	ldrdgt	pc, [r4], -r3
d0011874:	68dd689e 	ldmvs	sp, {r1, r2, r3, r4, r7, fp, sp, lr}^
d0011878:	e000f8c7 	and	pc, r0, r7, asr #17
d001187c:	60fd607e 	rscsvs	r6, sp, lr, ror r0
d0011880:	e9c7c80d 	stmib	r7, {r0, r2, r3, fp, lr, pc}^
d0011884:	22010204 	andcs	r0, r1, #4, 4	; 0x40000000
d0011888:	c074f8c7 	rsbsgt	pc, r4, r7, asr #17
d001188c:	68f867bb 	ldmvs	r8!, {r0, r1, r3, r4, r5, r7, r8, r9, sl, sp, lr}^
d0011890:	4298687b 	addsmi	r6, r8, #8060928	; 0x7b0000
d0011894:	824af040 	subhi	pc, sl, #64	; 0x40
d0011898:	31fcf8d7 	ldrsbcc	pc, [ip, #135]!	; 0x87	; <UNPREDICTABLE>
d001189c:	d1d12b00 	bicsle	r2, r1, r0, lsl #22
d00118a0:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d00118a4:	2900af40 	stmdbcs	r0, {r6, r8, r9, sl, fp, sp, pc}
d00118a8:	8243f000 	subhi	pc, r3, #0
d00118ac:	0520f8df 	streq	pc, [r0, #-2271]!	; 0xfffff721
d00118b0:	e7d24478 			; <UNDEFINED> instruction: 0xe7d24478
d00118b4:	22009b0c 	andcs	r9, r0, #12, 22	; 0x3000
d00118b8:	e7e86819 			; <UNDEFINED> instruction: 0xe7e86819
d00118bc:	fdfcf7ff 	ldc2l	7, cr15, [ip, #1020]!	; 0x3fc
d00118c0:	46822823 	strmi	r2, [r2], r3, lsr #16
d00118c4:	f10dd111 			; <UNDEFINED> instruction: 0xf10dd111
d00118c8:	466e0c44 	strbtmi	r0, [lr], -r4, asr #24
d00118cc:	e8bcad16 	ldm	ip!, {r1, r2, r4, r8, sl, fp, sp, pc}
d00118d0:	c60f000f 	strgt	r0, [pc], -pc
d00118d4:	3000f8dc 	ldrdcc	pc, [r0], -ip
d00118d8:	60334628 	eorsvs	r4, r3, r8, lsr #12
d00118dc:	000ee89b 	muleq	lr, fp, r8
d00118e0:	fc4af000 	mcrr2	0, 0, pc, sl, cr0	; <UNPREDICTABLE>
d00118e4:	3058f8d8 	ldrsbcc	pc, [r8], #-136	; 0xffffff78	; <UNPREDICTABLE>
d00118e8:	f7fee74a 			; <UNDEFINED> instruction: 0xf7fee74a
d00118ec:	4607fca7 	strmi	pc, [r7], -r7, lsr #25
d00118f0:	d13f2800 	teqle	pc, r0, lsl #16
d00118f4:	0930f1aa 	ldmdbeq	r0!, {r1, r3, r5, r7, r8, ip, sp, lr, pc}
d00118f8:	0f09f1b9 	svceq	0x0009f1b9
d00118fc:	810bf200 	mrshi	pc, R11_fiq	; <UNPREDICTABLE>
d0011900:	0f30f1ba 	svceq	0x0030f1ba
d0011904:	8238f000 	eorshi	pc, r8, #0
d0011908:	2000270a 	andcs	r2, r0, sl, lsl #14
d001190c:	fdc6f7ff 	stc2l	7, cr15, [r6, #1020]	; 0x3fc
d0011910:	f7fe4680 			; <UNDEFINED> instruction: 0xf7fe4680
d0011914:	4287fc9f 	addmi	pc, r7, #40704	; 0x9f00
d0011918:	80d5f200 	sbcshi	pc, r5, r0, lsl #4
d001191c:	0820f048 	stmdaeq	r0!, {r3, r6, ip, sp, lr, pc}
d0011920:	0f75f1b8 	svceq	0x0075f1b8
d0011924:	f7ffd101 			; <UNDEFINED> instruction: 0xf7ffd101
d0011928:	2000fdc7 	andcs	pc, r0, r7, asr #27
d001192c:	fdb6f7ff 	ldc2	7, cr15, [r6, #1020]!	; 0x3fc
d0011930:	0330f1a0 	teqeq	r0, #160, 2	; 0x28	; <UNPREDICTABLE>
d0011934:	2b094602 	blcs	0xd0263144
d0011938:	f7fed90f 			; <UNDEFINED> instruction: 0xf7fed90f
d001193c:	b960fc7f 	stmdblt	r0!, {r0, r1, r2, r3, r4, r5, r6, sl, fp, ip, sp, lr, pc}^
d0011940:	d00a2a2e 	andle	r2, sl, lr, lsr #20
d0011944:	0f75f1b8 	svceq	0x0075f1b8
d0011948:	80dff000 	sbcshi	pc, pc, r0
d001194c:	f0402f0a 			; <UNDEFINED> instruction: 0xf0402f0a
d0011950:	f1b980d1 			; <UNDEFINED> instruction: 0xf1b980d1
d0011954:	f2800f00 			; <UNDEFINED> instruction: 0xf2800f00
d0011958:	f8df80db 			; <UNDEFINED> instruction: 0xf8df80db
d001195c:	447b3478 	ldrbtmi	r3, [fp], #-1144	; 0xfffffb88
d0011960:	2a006d9a 	bcs	0xd002cfd0
d0011964:	81def040 	bicshi	pc, lr, r0, asr #32
d0011968:	246cf8df 	strbtcs	pc, [ip], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d001196c:	e03e447a 	eors	r4, lr, sl, ror r4
d0011970:	fda2f7ff 	stc2	7, cr15, [r2, #1020]!	; 0x3fc
d0011974:	f7ff2000 			; <UNDEFINED> instruction: 0xf7ff2000
d0011978:	4602fd91 			; <UNDEFINED> instruction: 0x4602fd91
d001197c:	fc5ef7fe 	mrrc2	7, 15, pc, lr, cr14	; <UNPREDICTABLE>
d0011980:	d1f52800 	mvnsle	r2, r0, lsl #16
d0011984:	2a093a30 	bcs	0xd026024c
d0011988:	f8dfd9f2 			; <UNDEFINED> instruction: 0xf8dfd9f2
d001198c:	46803450 	pkhtbmi	r3, r0, r0, asr #8
d0011990:	a44cf8df 	strbge	pc, [ip], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d0011994:	44fa447b 	ldrbtmi	r4, [sl], #1147	; 0x47b
d0011998:	68db681f 	ldmvs	fp, {r0, r1, r2, r3, r4, fp, sp, lr}^
d001199c:	eba7441f 	bl	0xce9e2a20
d00119a0:	f85a0709 			; <UNDEFINED> instruction: 0xf85a0709
d00119a4:	46392b04 	ldrtmi	r2, [r9], -r4, lsl #22
d00119a8:	f7fe4648 			; <UNDEFINED> instruction: 0xf7fe4648
d00119ac:	b120fc79 	msrlt	CPSR_, r9, ror ip
d00119b0:	1007f208 	andne	pc, r7, r8, lsl #4
d00119b4:	9013970f 	andsls	r9, r3, pc, lsl #14
d00119b8:	f108e1d5 			; <UNDEFINED> instruction: 0xf108e1d5
d00119bc:	f1b80801 			; <UNDEFINED> instruction: 0xf1b80801
d00119c0:	d1ee0f10 	mvnle	r0, r0, lsl pc
d00119c4:	a41cf8df 	ldrge	pc, [ip], #-2271	; 0xfffff721
d00119c8:	44fa4680 	ldrbtmi	r4, [sl], #1664	; 0x680
d00119cc:	2b04f85a 	blcs	0xd014fb3c
d00119d0:	46484639 			; <UNDEFINED> instruction: 0x46484639
d00119d4:	fc64f7fe 	stc2l	7, cr15, [r4], #-1016	; 0xfffffc08
d00119d8:	f8dfb188 			; <UNDEFINED> instruction: 0xf8dfb188
d00119dc:	447b340c 	ldrbtmi	r3, [fp], #-1036	; 0xfffffbf4
d00119e0:	2a006d9a 	bcs	0xd002d050
d00119e4:	819ef040 	orrshi	pc, lr, r0, asr #32
d00119e8:	2400f8df 	strcs	pc, [r0], #-2271	; 0xfffff721
d00119ec:	659a447a 	ldrvs	r4, [sl, #1146]	; 0x47a
d00119f0:	669e9a07 	ldrvs	r9, [lr], r7, lsl #20
d00119f4:	9a0865da 	bls	0xd022b164
d00119f8:	2518e9c3 	ldrcs	lr, [r8, #-2499]	; 0xfffff63d
d00119fc:	f108e192 			; <UNDEFINED> instruction: 0xf108e192
d0011a00:	f1b80801 			; <UNDEFINED> instruction: 0xf1b80801
d0011a04:	d1e10f1c 	mvnle	r0, ip, lsl pc
d0011a08:	83e4f8df 	mvnhi	pc, #14614528	; 0xdf0000
d0011a0c:	4649463a 			; <UNDEFINED> instruction: 0x4649463a
d0011a10:	464044f8 			; <UNDEFINED> instruction: 0x464044f8
d0011a14:	fbf0f7fe 	blx	0xcfc4fa16
d0011a18:	db352800 	blle	0xd0d5ba20
d0011a1c:	fb032348 	blx	0xd00da746
d0011a20:	f5008000 			; <UNDEFINED> instruction: 0xf5008000
d0011a24:	30c8402b 	sbccc	r4, r8, fp, lsr #32
d0011a28:	0100e9d0 	ldrdeq	lr, [r0, -r0]
d0011a2c:	4300f110 	movwmi	pc, #272	; 0x110	; <UNPREDICTABLE>
d0011a30:	f141930a 			; <UNDEFINED> instruction: 0xf141930a
d0011a34:	930b0300 	movwls	r0, #45824	; 0xb300
d0011a38:	230ae9dd 	movwcs	lr, #43485	; 0xa9dd
d0011a3c:	bf082b01 	svclt	0x00082b01
d0011a40:	4f00f1b2 	svcmi	0x0000f1b2
d0011a44:	f8d8d311 			; <UNDEFINED> instruction: 0xf8d8d311
d0011a48:	2b003058 	blcs	0xd001dbb0
d0011a4c:	816af040 	msrhi	SPSR_fx, r0, asr #32
d0011a50:	f8c84be8 			; <UNDEFINED> instruction: 0xf8c84be8
d0011a54:	447b6068 	ldrbtmi	r6, [fp], #-104	; 0xffffff98
d0011a58:	3058f8c8 	subscc	pc, r8, r8, asr #17
d0011a5c:	f8c89b07 			; <UNDEFINED> instruction: 0xf8c89b07
d0011a60:	9b08305c 	blls	0xd021dbd8
d0011a64:	3518e9c8 	ldrcc	lr, [r8, #-2504]	; 0xfffff638
d0011a68:	f06fe15c 			; <UNDEFINED> instruction: 0xf06fe15c
d0011a6c:	23004200 	movwcs	r4, #512	; 0x200
d0011a70:	42829009 	addmi	r9, r2, #9
d0011a74:	f240418b 	vrhadd.s8	d20, d16, d11
d0011a78:	bfa81303 	svclt	0x00a81303
d0011a7c:	7381f44f 	orrvc	pc, r1, #1325400064	; 0x4f000000
d0011a80:	970f9a09 	strls	r9, [pc, -r9, lsl #20]
d0011a84:	e03e9210 	eors	r9, lr, r0, lsl r2
d0011a88:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d0011a8c:	f7ffe7f8 			; <UNDEFINED> instruction: 0xf7ffe7f8
d0011a90:	4638fd13 			; <UNDEFINED> instruction: 0x4638fd13
d0011a94:	fd02f7ff 	stc2	7, cr15, [r2, #-1020]	; 0xfffffc04
d0011a98:	fbdcf7fe 	blx	0xcf74fa9a
d0011a9c:	46072810 			; <UNDEFINED> instruction: 0x46072810
d0011aa0:	f8d8d126 			; <UNDEFINED> instruction: 0xf8d8d126
d0011aa4:	2b003058 	blcs	0xd001dc0c
d0011aa8:	af2ff47f 	svcge	0x002ff47f
d0011aac:	f8c84bd2 			; <UNDEFINED> instruction: 0xf8c84bd2
d0011ab0:	447b6068 	ldrbtmi	r6, [fp], #-104	; 0xffffff98
d0011ab4:	3058f8c8 	subscc	pc, r8, r8, asr #17
d0011ab8:	f8c89b07 			; <UNDEFINED> instruction: 0xf8c89b07
d0011abc:	9b08305c 	blls	0xd021dc34
d0011ac0:	3518e9c8 	ldrcc	lr, [r8, #-2504]	; 0xfffff638
d0011ac4:	f7ffe721 			; <UNDEFINED> instruction: 0xf7ffe721
d0011ac8:	f7fefcf7 			; <UNDEFINED> instruction: 0xf7fefcf7
d0011acc:	43c3fbc3 	bicmi	pc, r3, #199680	; 0x30c00
d0011ad0:	f3f7fbb3 			; <UNDEFINED> instruction: 0xf3f7fbb3
d0011ad4:	d208454b 	andle	r4, r8, #314572800	; 0x12c00000
d0011ad8:	447b4bc8 	ldrbtmi	r4, [fp], #-3016	; 0xfffff438
d0011adc:	2a006d9a 	bcs	0xd002d14c
d0011ae0:	8120f040 	msrhi	CPSR_, r0, asr #32
d0011ae4:	447a4ac6 	ldrbtmi	r4, [sl], #-2758	; 0xfffff53a
d0011ae8:	fb09e781 	blx	0xd028b8f6
d0011aec:	e70c0907 	str	r0, [ip, -r7, lsl #18]
d0011af0:	e70a2710 	smlad	sl, r0, r7, r2
d0011af4:	0f00f1b9 	svceq	0x0000f1b9
d0011af8:	1303f240 	movwne	pc, #12864	; 0x3240	; <UNPREDICTABLE>
d0011afc:	f44fbfa8 			; <UNDEFINED> instruction: 0xf44fbfa8
d0011b00:	f8cd7381 			; <UNDEFINED> instruction: 0xf8cd7381
d0011b04:	93139040 	tstls	r3, #64	; 0x40
d0011b08:	f240e12d 	vrhadd.s8	d30, d0, d29
d0011b0c:	e7f81303 	ldrb	r1, [r8, r3, lsl #6]!
d0011b10:	7381f44f 	orrvc	pc, r1, #1325400064	; 0x4f000000
d0011b14:	f1bae7f5 			; <UNDEFINED> instruction: 0xf1bae7f5
d0011b18:	d0020f22 	andle	r0, r2, r2, lsr #30
d0011b1c:	0f27f1ba 	svceq	0x0027f1ba
d0011b20:	4bb8d175 	blmi	0xcee460fc
d0011b24:	4701f242 	strmi	pc, [r1, -r2, asr #4]
d0011b28:	681a447b 	ldmdavs	sl, {r0, r1, r3, r4, r5, r6, sl, lr}
d0011b2c:	68da920c 	ldmvs	sl, {r2, r3, r9, ip, pc}^
d0011b30:	68d8920a 	ldmvs	r8, {r1, r3, r9, ip, pc}^
d0011b34:	4290685a 	addsmi	r6, r0, #5898240	; 0x5a0000
d0011b38:	930dd05a 	movwls	sp, #53338	; 0xd05a
d0011b3c:	fcbcf7ff 	ldc2	7, cr15, [ip], #1020	; 0x3fc
d0011b40:	9b0d4582 	blls	0xd0363150
d0011b44:	9a0cd148 	bls	0xd034606c
d0011b48:	0f22f1ba 	svceq	0x0022f1ba
d0011b4c:	990a68df 	stmdbls	sl, {r0, r1, r2, r3, r4, r6, r7, fp, sp, lr}
d0011b50:	0801eb02 	stmdaeq	r1, {r1, r8, r9, fp, sp, lr, pc}
d0011b54:	32fff107 	rscscc	pc, pc, #-1073741823	; 0xc0000001
d0011b58:	4417681f 	ldrmi	r6, [r7], #-2079	; 0xfffff7e1
d0011b5c:	0708eba7 	streq	lr, [r8, -r7, lsr #23]
d0011b60:	eb08d037 	bl	0xd0245c44
d0011b64:	f8cd0907 			; <UNDEFINED> instruction: 0xf8cd0907
d0011b68:	45c88058 	strbmi	r8, [r8, #88]	; 0x58
d0011b6c:	6d9ad106 	ldfvsd	f5, [sl, #24]
d0011b70:	f0402a00 			; <UNDEFINED> instruction: 0xf0402a00
d0011b74:	4aa480d7 	bmi	0xce931ed8
d0011b78:	e738447a 			; <UNDEFINED> instruction: 0xe738447a
d0011b7c:	0301f108 	movweq	pc, #4360	; 0x1108	; <UNPREDICTABLE>
d0011b80:	990a9a0c 	stmdbls	sl, {r2, r3, r9, fp, ip, pc}
d0011b84:	5c529316 	mrrcpl	3, 1, r9, r2, cr6
d0011b88:	92092a5c 	andls	r2, r9, #92, 20	; 0x5c000
d0011b8c:	4599d10c 	ldrmi	sp, [r9, #268]	; 0x10c
d0011b90:	ab16d00a 	blge	0xd05c5bc0
d0011b94:	9908462a 	stmdbls	r8, {r1, r3, r5, r9, sl, lr}
d0011b98:	46339300 	ldrtmi	r9, [r3], -r0, lsl #6
d0011b9c:	f8cd9807 			; <UNDEFINED> instruction: 0xf8cd9807
d0011ba0:	f7ff9004 			; <UNDEFINED> instruction: 0xf7ff9004
d0011ba4:	9009fb11 	andls	pc, r9, r1, lsl fp	; <UNPREDICTABLE>
d0011ba8:	45999b16 	ldrmi	r9, [r9, #2838]	; 0xb16
d0011bac:	4b97d00c 	blmi	0xce605be4
d0011bb0:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d0011bb4:	4a96b942 	bmi	0xce5c00c4
d0011bb8:	447a669e 	ldrbtmi	r6, [sl], #-1694	; 0xfffff962
d0011bbc:	9a07659a 	bls	0xd01eb22c
d0011bc0:	9a0865da 	bls	0xd022b330
d0011bc4:	2518e9c3 	ldrcs	lr, [r8, #-2499]	; 0xfffff63d
d0011bc8:	7381f44f 	orrvc	pc, r1, #1325400064	; 0x4f000000
d0011bcc:	8038f8cd 	eorshi	pc, r8, sp, asr #17
d0011bd0:	f44fe756 	vst1.16	{d30}, [pc :64], r6
d0011bd4:	e7f97382 	ldrb	r7, [r9, r2, lsl #7]!
d0011bd8:	d103285c 	tstle	r3, ip, asr r8
d0011bdc:	f7ff930d 			; <UNDEFINED> instruction: 0xf7ff930d
d0011be0:	9b0dfc6b 	blls	0xd0390d94
d0011be4:	d8a4280d 	stmiale	r4!, {r0, r2, r3, fp, sp}
d0011be8:	f000fa27 			; <UNDEFINED> instruction: 0xf000fa27
d0011bec:	d5a007c2 	strle	r0, [r0, #1986]!	; 0x7c2
d0011bf0:	0f22f1ba 	svceq	0x0022f1ba
d0011bf4:	4a87d102 	bmi	0xce206004
d0011bf8:	e001447a 	and	r4, r1, sl, ror r4
d0011bfc:	447a4a86 	ldrbtmi	r4, [sl], #-2694	; 0xfffff57a
d0011c00:	447b4b86 	ldrbtmi	r4, [fp], #-2950	; 0xfffff47a
d0011c04:	29006d99 	stmdbcs	r0, {r0, r3, r4, r7, r8, sl, fp, sp, lr}
d0011c08:	808cf040 	addhi	pc, ip, r0, asr #32
d0011c0c:	f7ffe6ef 			; <UNDEFINED> instruction: 0xf7ffe6ef
d0011c10:	283dfc45 	ldmdacs	sp!, {r0, r2, r6, sl, fp, ip, sp, lr, pc}
d0011c14:	f0404680 			; <UNDEFINED> instruction: 0xf0404680
d0011c18:	f1ba80b8 			; <UNDEFINED> instruction: 0xf1ba80b8
d0011c1c:	d0020f2b 	andle	r0, r2, fp, lsr #30
d0011c20:	0f2df1ba 	svceq	0x002df1ba
d0011c24:	f7ffd10b 			; <UNDEFINED> instruction: 0xf7ffd10b
d0011c28:	f1bafc47 			; <UNDEFINED> instruction: 0xf1bafc47
d0011c2c:	f2400f2b 	vmax.f32	d16, d0, d27
d0011c30:	bf0c1121 	svclt	0x000c1121
d0011c34:	7790f44f 	ldrvc	pc, [r0, pc, asr #8]
d0011c38:	9713460f 	ldrls	r4, [r3, -pc, lsl #12]
d0011c3c:	f1bae093 			; <UNDEFINED> instruction: 0xf1bae093
d0011c40:	d1110f3d 	tstle	r1, sp, lsr pc
d0011c44:	033cf1aa 	teqeq	ip, #-2147483606	; 0x8000002a	; <UNPREDICTABLE>
d0011c48:	d9102b02 	ldmdble	r0, {r1, r8, r9, fp, sp}
d0011c4c:	0f2df1ba 	svceq	0x002df1ba
d0011c50:	f1b8d12f 			; <UNDEFINED> instruction: 0xf1b8d12f
d0011c54:	d1450f3e 	cmple	r5, lr, lsr pc
d0011c58:	171df240 	ldrne	pc, [sp, -r0, asr #4]
d0011c5c:	fc2cf7ff 	stc2	7, cr15, [ip], #-1020	; 0xfffffc04
d0011c60:	f1b8e7eb 			; <UNDEFINED> instruction: 0xf1b8e7eb
d0011c64:	d1140f3d 	tstle	r4, sp, lsr pc
d0011c68:	0f21f1ba 	svceq	0x0021f1ba
d0011c6c:	f7ffd1ea 			; <UNDEFINED> instruction: 0xf7ffd1ea
d0011c70:	f1bafc23 			; <UNDEFINED> instruction: 0xf1bafc23
d0011c74:	d0410f3d 	suble	r0, r1, sp, lsr pc
d0011c78:	0f21f1ba 	svceq	0x0021f1ba
d0011c7c:	f1bad041 			; <UNDEFINED> instruction: 0xf1bad041
d0011c80:	f2400f3c 	vrecps.f32	d16, d0, d28
d0011c84:	bf181119 	svclt	0x00181119
d0011c88:	778df44f 	strvc	pc, [sp, pc, asr #8]
d0011c8c:	460fbf08 	strmi	fp, [pc], -r8, lsl #30
d0011c90:	f1b8e7d3 			; <UNDEFINED> instruction: 0xf1b8e7d3
d0011c94:	d0020f26 	andle	r0, r2, r6, lsr #30
d0011c98:	0f7cf1b8 	svceq	0x007cf1b8
d0011c9c:	f7ffd109 			; <UNDEFINED> instruction: 0xf7ffd109
d0011ca0:	f1b8fc0b 			; <UNDEFINED> instruction: 0xf1b8fc0b
d0011ca4:	f2400f26 	vmax.f32	d16, d0, d22
d0011ca8:	bf18111b 	svclt	0x0018111b
d0011cac:	778ef44f 	strvc	pc, [lr, pc, asr #8]
d0011cb0:	f1bae7ec 			; <UNDEFINED> instruction: 0xf1bae7ec
d0011cb4:	d10f0f00 	tstle	pc, r0, lsl #30
d0011cb8:	447b4b59 	ldrbtmi	r4, [fp], #-2905	; 0xfffff4a7
d0011cbc:	b9426d9a 	stmdblt	r2, {r1, r3, r4, r7, r8, sl, fp, sp, lr}^
d0011cc0:	669e4a58 			; <UNDEFINED> instruction: 0x669e4a58
d0011cc4:	659a447a 	ldrvs	r4, [sl, #1146]	; 0x47a
d0011cc8:	65da9a07 	ldrbvs	r9, [sl, #2567]	; 0xa07
d0011ccc:	e9c39a08 	stmib	r3, {r3, r9, fp, ip, pc}^
d0011cd0:	f2402518 	vqrshl.s8	d18, d8, d0
d0011cd4:	e7b01705 	ldr	r1, [r0, r5, lsl #14]!
d0011cd8:	d10345c2 	smlabtle	r3, r2, r5, r4
d0011cdc:	0302f02a 	movweq	pc, #8234	; 0x202a	; <UNPREDICTABLE>
d0011ce0:	d0e92b3c 	rscle	r2, r9, ip, lsr fp
d0011ce4:	0f3df1b8 	svceq	0x003df1b8
d0011ce8:	d1a64657 			; <UNDEFINED> instruction: 0xd1a64657
d0011cec:	4651484e 	ldrbmi	r4, [r1], -lr, asr #16
d0011cf0:	f0094478 			; <UNDEFINED> instruction: 0xf0094478
d0011cf4:	2800f863 	stmdacs	r0, {r0, r1, r5, r6, fp, ip, sp, lr, pc}
d0011cf8:	e79ed1de 			; <UNDEFINED> instruction: 0xe79ed1de
d0011cfc:	1717f240 	ldrne	pc, [r7, -r0, asr #4]
d0011d00:	f44fe79b 	vst1.32	{d30}, [pc :64], fp
d0011d04:	e798778c 	ldr	r7, [r8, ip, lsl #15]
d0011d08:	b95b6dab 	ldmdblt	fp, {r0, r1, r3, r5, r7, r8, sl, fp, sp, lr}^
d0011d0c:	f89d4a47 			; <UNDEFINED> instruction: 0xf89d4a47
d0011d10:	447a3070 	ldrbtmi	r3, [sl], #-112	; 0xffffff90
d0011d14:	9a1965aa 	bls	0xd066b3c4
d0011d18:	9a1a65ea 	bls	0xd06ab4c8
d0011d1c:	2318e9c5 	tstcs	r8, #3227648	; 0x314000
d0011d20:	66ab9b1d 	ssatvs	r9, #12, sp, lsl #22
d0011d24:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0011d28:	e537fb93 	ldr	pc, [r7, #-2963]!	; 0xfffff46d
d0011d2c:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0011d30:	f10dacfa 			; <UNDEFINED> instruction: 0xf10dacfa
d0011d34:	f8df0b38 			; <UNDEFINED> instruction: 0xf8df0b38
d0011d38:	465880f8 			; <UNDEFINED> instruction: 0x465880f8
d0011d3c:	f7ff44f8 			; <UNDEFINED> instruction: 0xf7ff44f8
d0011d40:	9b10fb87 	blls	0xd0450b64
d0011d44:	200cf8d8 	ldrdcs	pc, [ip], -r8
d0011d48:	9b119309 	blls	0xd0476974
d0011d4c:	9038f8dd 	ldrsbtls	pc, [r8], -sp	; <UNPREDICTABLE>
d0011d50:	9b129307 	blls	0xd04b6974
d0011d54:	5050f89d 			; <UNDEFINED> instruction: 0x5050f89d
d0011d58:	f8d89308 			; <UNDEFINED> instruction: 0xf8d89308
d0011d5c:	9e153004 	cdpls	0, 1, cr3, cr5, cr4, {0}
d0011d60:	f47f429a 			; <UNDEFINED> instruction: 0xf47f429a
d0011d64:	465eadab 	ldrbmi	sl, [lr], -fp, lsr #27
d0011d68:	ce0f4625 	cfmadd32gt	mvax1, mvfx4, mvfx15, mvfx5
d0011d6c:	e896c50f 	ldm	r6, {r0, r1, r2, r3, r8, sl, lr, pc}
d0011d70:	e885000f 	stm	r5, {r0, r1, r2, r3}
d0011d74:	e511000f 	ldr	r0, [r1, #-15]
d0011d78:	fb90f7ff 	blx	0xce44fd7e
d0011d7c:	0020f040 	eoreq	pc, r0, r0, asr #32
d0011d80:	f43f2878 			; <UNDEFINED> instruction: 0xf43f2878
d0011d84:	2708ae84 	strcs	sl, [r8, -r4, lsl #29]
d0011d88:	4582e5bf 	strmi	lr, [r2, #1471]	; 0x5bf
d0011d8c:	af5ef47f 	svcge	0x005ef47f
d0011d90:	0f2bf1ba 	svceq	0x002bf1ba
d0011d94:	f1bad003 			; <UNDEFINED> instruction: 0xf1bad003
d0011d98:	f47f0f2d 			; <UNDEFINED> instruction: 0xf47f0f2d
d0011d9c:	f7ffaf62 			; <UNDEFINED> instruction: 0xf7ffaf62
d0011da0:	f1b8fb8b 			; <UNDEFINED> instruction: 0xf1b8fb8b
d0011da4:	f2400f2b 	vmax.f32	d16, d0, d27
d0011da8:	bf0c111f 	svclt	0x000c111f
d0011dac:	778ff44f 	strvc	pc, [pc, pc, asr #8]
d0011db0:	e742460f 	strb	r4, [r2, -pc, lsl #12]
d0011db4:	0000a7dc 	ldrdeq	sl, [r0], -ip
d0011db8:	0000a7c2 	andeq	sl, r0, r2, asr #15
d0011dbc:	0000a7c0 	andeq	sl, r0, r0, asr #15
d0011dc0:	0000a79a 	muleq	r0, sl, r7
d0011dc4:	0000a6f8 	strdeq	sl, [r0], -r8
d0011dc8:	0000a6cc 	andeq	sl, r0, ip, asr #13
d0011dcc:	fffffd4b 			; <UNDEFINED> instruction: 0xfffffd4b
d0011dd0:	fffffd17 			; <UNDEFINED> instruction: 0xfffffd17
d0011dd4:	0000a57e 	andeq	sl, r0, lr, ror r5
d0011dd8:	fffffd09 			; <UNDEFINED> instruction: 0xfffffd09
d0011ddc:	0000a548 	andeq	sl, r0, r8, asr #10
d0011de0:	00009496 	muleq	r0, r6, r4
d0011de4:	000094a2 	andeq	r9, r0, r2, lsr #9
d0011de8:	0000a4fe 	strdeq	sl, [r0], -lr
d0011dec:	fffffbfb 			; <UNDEFINED> instruction: 0xfffffbfb
d0011df0:	0000a4cc 	andeq	sl, r0, ip, asr #9
d0011df4:	fffffbb8 			; <UNDEFINED> instruction: 0xfffffbb8
d0011df8:	fffffb85 			; <UNDEFINED> instruction: 0xfffffb85
d0011dfc:	0000a402 	andeq	sl, r0, r2, lsl #8
d0011e00:	fffffb6a 			; <UNDEFINED> instruction: 0xfffffb6a
d0011e04:	0000a3b4 			; <UNDEFINED> instruction: 0x0000a3b4
d0011e08:	fffffb2b 			; <UNDEFINED> instruction: 0xfffffb2b
d0011e0c:	0000a32c 	andeq	sl, r0, ip, lsr #6
d0011e10:	fffffae9 			; <UNDEFINED> instruction: 0xfffffae9
d0011e14:	fffff960 			; <UNDEFINED> instruction: 0xfffff960
d0011e18:	fffff972 			; <UNDEFINED> instruction: 0xfffff972
d0011e1c:	0000a2da 	ldrdeq	sl, [r0], -sl	; <UNPREDICTABLE>
d0011e20:	0000a222 	andeq	sl, r0, r2, lsr #4
d0011e24:	fffffa0e 			; <UNDEFINED> instruction: 0xfffffa0e
d0011e28:	fffff9db 			; <UNDEFINED> instruction: 0xfffff9db
d0011e2c:	fffff87a 			; <UNDEFINED> instruction: 0xfffff87a
d0011e30:	0000a1a0 	andeq	sl, r0, r0, lsr #3

Disassembly of section .text.scan_directive.constprop.0:

d0012178 <.text.scan_directive.constprop.0>:
d0012178:	e92db084 	push	{r2, r7, ip, sp, pc}
d001217c:	ed2d4ff0 	vstr	FPSCR_nzcvqc, [sp, #-448]!	; 0xfffffe40
d0012180:	b09b8b02 	addslt	r8, fp, r2, lsl #22
d0012184:	0a10ee08 	beq	0xd044d9ac
d0012188:	e880a827 	stm	r0, {r0, r1, r2, r5, fp, sp, pc}
d001218c:	9b2a000e 	blls	0xd0a921cc
d0012190:	90b4f89d 	umlalsls	pc, r4, sp, r8	; <UNPREDICTABLE>
d0012194:	9b2b930a 	blls	0xd0af6dc4
d0012198:	93099c2e 	movwls	r9, #39982	; 0x9c2e
d001219c:	39e8f8df 	stmibcc	r8!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d00121a0:	68da447b 	ldmvs	sl, {r0, r1, r3, r4, r5, r6, sl, lr}^
d00121a4:	9210695b 	andsls	r6, r0, #1490944	; 0x16c000
d00121a8:	20009311 	andcs	r9, r0, r1, lsl r3
d00121ac:	f976f7ff 			; <UNDEFINED> instruction: 0xf976f7ff
d00121b0:	d02f2820 	eorle	r2, pc, r0, lsr #16
d00121b4:	d02d2809 	eorle	r2, sp, r9, lsl #16
d00121b8:	39d0f8df 	ldmibcc	r0, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d00121bc:	681e447b 	ldmdavs	lr, {r0, r1, r3, r4, r5, r6, sl, lr}
d00121c0:	441e68db 	ldrmi	r6, [lr], #-2267	; 0xfffff725
d00121c4:	f7ff2000 			; <UNDEFINED> instruction: 0xf7ff2000
d00121c8:	f7fef969 			; <UNDEFINED> instruction: 0xf7fef969
d00121cc:	4680f837 			; <UNDEFINED> instruction: 0x4680f837
d00121d0:	f8dfbb18 			; <UNDEFINED> instruction: 0xf8dfbb18
d00121d4:	447b39bc 	ldrbtmi	r3, [fp], #-2492	; 0xfffff644
d00121d8:	68db681a 	ldmvs	fp, {r1, r3, r4, fp, sp, lr}^
d00121dc:	1b92441a 	blne	0xce4a324c
d00121e0:	d11d2a07 	tstle	sp, r7, lsl #20
d00121e4:	19acf8df 	stmibne	ip!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d00121e8:	920b4630 	andls	r4, fp, #48, 12	; 0x3000000
d00121ec:	f0074479 			; <UNDEFINED> instruction: 0xf0074479
d00121f0:	fab0f9c9 	blx	0xcec5091c
d00121f4:	9a0bf580 	bls	0xd030f7fc
d00121f8:	f04f096d 			; <UNDEFINED> instruction: 0xf04f096d
d00121fc:	2a050a00 	bcs	0xd0154a04
d0012200:	f8cd4657 			; <UNDEFINED> instruction: 0xf8cd4657
d0012204:	f8cda034 			; <UNDEFINED> instruction: 0xf8cda034
d0012208:	f8cda02c 			; <UNDEFINED> instruction: 0xf8cda02c
d001220c:	d12fa030 			; <UNDEFINED> instruction: 0xd12fa030
d0012210:	bca7f000 	stclt	0, cr15, [r7]
d0012214:	f950f7ff 			; <UNDEFINED> instruction: 0xf950f7ff
d0012218:	f7ffe7c7 			; <UNDEFINED> instruction: 0xf7ffe7c7
d001221c:	e7d1f94d 	ldrb	pc, [r1, sp, asr #18]	; <UNPREDICTABLE>
d0012220:	f0402a06 			; <UNDEFINED> instruction: 0xf0402a06
d0012224:	f8df8482 			; <UNDEFINED> instruction: 0xf8df8482
d0012228:	46301970 			; <UNDEFINED> instruction: 0x46301970
d001222c:	4645920b 	strbmi	r9, [r5], -fp, lsl #4
d0012230:	f0074479 			; <UNDEFINED> instruction: 0xf0074479
d0012234:	f8dff9a7 			; <UNDEFINED> instruction: 0xf8dff9a7
d0012238:	fab01964 	blx	0xcec187d0
d001223c:	9a0bf780 	bls	0xd0310044
d0012240:	46304479 			; <UNDEFINED> instruction: 0x46304479
d0012244:	f99ef007 			; <UNDEFINED> instruction: 0xf99ef007
d0012248:	f380fab0 			; <UNDEFINED> instruction: 0xf380fab0
d001224c:	1950f8df 	ldmdbne	r0, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d0012250:	095b4630 	ldmdbeq	fp, {r4, r5, r9, sl, lr}^
d0012254:	44799a0b 	ldrbtmi	r9, [r9], #-2571	; 0xfffff5f5
d0012258:	930c097f 	movwls	r0, #51583	; 0xc97f
d001225c:	f992f007 			; <UNDEFINED> instruction: 0xf992f007
d0012260:	fa80fab0 	blx	0xce050d28
d0012264:	8034f8cd 	eorshi	pc, r4, sp, asr #17
d0012268:	802cf8cd 	eorhi	pc, ip, sp, asr #17
d001226c:	1a5aea4f 	bne	0xd16ccbb0
d0012270:	0b00f04f 	bleq	0xd004e3b4
d0012274:	b03cf8cd 	eorslt	pc, ip, sp, asr #17
d0012278:	b038f8cd 	eorslt	pc, r8, sp, asr #17
d001227c:	2a02e03b 	bcs	0xd00ca370
d0012280:	2a04d023 	bcs	0xd0146314
d0012284:	d1b84645 			; <UNDEFINED> instruction: 0xd1b84645
d0012288:	1918f8df 	ldmdbne	r8, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d001228c:	920b4630 	andls	r4, fp, #48, 12	; 0x3000000
d0012290:	447946c2 	ldrbtmi	r4, [r9], #-1730	; 0xfffff93e
d0012294:	f0074647 			; <UNDEFINED> instruction: 0xf0074647
d0012298:	fab0f975 	blx	0xcec50874
d001229c:	f8dff380 			; <UNDEFINED> instruction: 0xf8dff380
d00122a0:	46301908 	ldrtmi	r1, [r0], -r8, lsl #18
d00122a4:	9a0b095b 	bls	0xd02d4818
d00122a8:	930f4479 	movwls	r4, #62585	; 0xf479
d00122ac:	f96af007 			; <UNDEFINED> instruction: 0xf96af007
d00122b0:	fb80fab0 	blx	0xce050d7a
d00122b4:	8038f8cd 	eorshi	pc, r8, sp, asr #17
d00122b8:	8034f8cd 	eorshi	pc, r4, sp, asr #17
d00122bc:	1b5bea4f 	blne	0xd170cc00
d00122c0:	802cf8cd 	eorhi	pc, ip, sp, asr #17
d00122c4:	8030f8cd 	eorshi	pc, r0, sp, asr #17
d00122c8:	f8dfe015 			; <UNDEFINED> instruction: 0xf8dfe015
d00122cc:	463018e0 	ldrtmi	r1, [r0], -r0, ror #17
d00122d0:	46c246c3 	strbmi	r4, [r2], r3, asr #13
d00122d4:	46474479 			; <UNDEFINED> instruction: 0x46474479
d00122d8:	f954f007 			; <UNDEFINED> instruction: 0xf954f007
d00122dc:	f380fab0 			; <UNDEFINED> instruction: 0xf380fab0
d00122e0:	f8cd4645 			; <UNDEFINED> instruction: 0xf8cd4645
d00122e4:	095b803c 	ldmdbeq	fp, {r2, r3, r4, r5, pc}^
d00122e8:	8034f8cd 	eorshi	pc, r4, sp, asr #17
d00122ec:	802cf8cd 	eorhi	pc, ip, sp, asr #17
d00122f0:	f8cd930e 			; <UNDEFINED> instruction: 0xf8cd930e
d00122f4:	ea558030 	b	0xd15723bc
d00122f8:	f0000607 			; <UNDEFINED> instruction: 0xf0000607
d00122fc:	f7ff8174 			; <UNDEFINED> instruction: 0xf7ff8174
d0012300:	2800f893 	stmdacs	r0, {r0, r1, r4, r7, fp, ip, sp, lr, pc}
d0012304:	816ff000 	msrhi	SPSR_fsxc, r0
d0012308:	38a4f8df 	stmiacc	r4!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d001230c:	9a10af27 	bls	0xd043dfb0
d0012310:	447bad12 	ldrbtmi	sl, [fp], #-3346	; 0xfffff2ee
d0012314:	9a1160da 	bls	0xd046a684
d0012318:	cf0f615a 	svcgt	0x000f615a
d001231c:	e897c50f 	ldm	r7, {r0, r1, r2, r3, r8, sl, lr, pc}
d0012320:	e885000f 	stm	r5, {r0, r1, r2, r3}
d0012324:	2000000f 	andcs	r0, r0, pc
d0012328:	f8b8f7ff 			; <UNDEFINED> instruction: 0xf8b8f7ff
d001232c:	d03a2820 	eorsle	r2, sl, r0, lsr #16
d0012330:	d0382809 	eorsle	r2, r8, r9, lsl #16
d0012334:	387cf8df 	ldmdacc	ip!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d0012338:	681d447b 	ldmdavs	sp, {r0, r1, r3, r4, r5, r6, sl, lr}
d001233c:	441d68db 	ldrmi	r6, [sp], #-2267	; 0xfffff725
d0012340:	f7ff2000 			; <UNDEFINED> instruction: 0xf7ff2000
d0012344:	f7fdf8ab 			; <UNDEFINED> instruction: 0xf7fdf8ab
d0012348:	bb78ff79 	bllt	0xd1e52134
d001234c:	3868f8df 	stmdacc	r8!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d0012350:	681a447b 	ldmdavs	sl, {r0, r1, r3, r4, r5, r6, sl, lr}
d0012354:	441a68db 	ldrmi	r6, [sl], #-2267	; 0xfffff725
d0012358:	2a071b52 	bcs	0xd01d90a8
d001235c:	f8dfd129 			; <UNDEFINED> instruction: 0xf8dfd129
d0012360:	4628185c 			; <UNDEFINED> instruction: 0x4628185c
d0012364:	f0074479 			; <UNDEFINED> instruction: 0xf0074479
d0012368:	4606f90d 	strmi	pc, [r6], -sp, lsl #18
d001236c:	f8dfb358 			; <UNDEFINED> instruction: 0xf8dfb358
d0012370:	447b3850 	ldrbtmi	r3, [fp], #-2128	; 0xfffff7b0
d0012374:	b94a6d9a 	stmdblt	sl, {r1, r3, r4, r7, r8, sl, fp, sp, lr}^
d0012378:	2848f8df 	stmdacs	r8, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d001237c:	659a447a 	ldrvs	r4, [sl, #1146]	; 0x47a
d0012380:	669c9a0a 	ldrvs	r9, [ip], sl, lsl #20
d0012384:	9a0965da 	bls	0xd026baf4
d0012388:	2918e9c3 	ldmdbcs	r8, {r0, r1, r6, r7, r8, fp, sp, lr, pc}
d001238c:	0a10ee18 	beq	0xd044dbf4
d0012390:	f85ef7ff 			; <UNDEFINED> instruction: 0xf85ef7ff
d0012394:	0a10ee18 	beq	0xd044dbfc
d0012398:	ecbdb01b 	ldc	0, cr11, [sp], #108	; 0x6c
d001239c:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d00123a0:	b0044ff0 	strdlt	r4, [r4], -r0
d00123a4:	f7ff4770 			; <UNDEFINED> instruction: 0xf7ff4770
d00123a8:	e7bcf887 	ldr	pc, [ip, r7, lsl #17]!
d00123ac:	f884f7ff 			; <UNDEFINED> instruction: 0xf884f7ff
d00123b0:	2a06e7c6 	bcs	0xd01cc2d0
d00123b4:	f8dfd1db 			; <UNDEFINED> instruction: 0xf8dfd1db
d00123b8:	46281810 			; <UNDEFINED> instruction: 0x46281810
d00123bc:	f0074479 			; <UNDEFINED> instruction: 0xf0074479
d00123c0:	2800f8e1 	stmdacs	r0, {r0, r5, r6, r7, fp, ip, sp, lr, pc}
d00123c4:	2000d1d3 	ldrdcs	sp, [r0], -r3
d00123c8:	f868f7ff 			; <UNDEFINED> instruction: 0xf868f7ff
d00123cc:	d01e2820 	andsle	r2, lr, r0, lsr #16
d00123d0:	d01c2809 	andsle	r2, ip, r9, lsl #16
d00123d4:	d0602e00 	rsble	r2, r0, r0, lsl #28
d00123d8:	37f0f8df 	ubfxcc	pc, pc, #17, #17
d00123dc:	681e447b 	ldmdavs	lr, {r0, r1, r3, r4, r5, r6, sl, lr}
d00123e0:	200068df 	ldrdcs	r6, [r0], -pc	; <UNPREDICTABLE>
d00123e4:	f85af7ff 			; <UNDEFINED> instruction: 0xf85af7ff
d00123e8:	ff28f7fd 			; <UNDEFINED> instruction: 0xff28f7fd
d00123ec:	f8dfb990 			; <UNDEFINED> instruction: 0xf8dfb990
d00123f0:	447d57e0 	ldrbtmi	r5, [sp], #-2016	; 0xfffff820
d00123f4:	2b006fab 	blcs	0xd002e2a8
d00123f8:	f8dfda0f 			; <UNDEFINED> instruction: 0xf8dfda0f
d00123fc:	447b37d8 	ldrbtmi	r3, [fp], #-2008	; 0xfffff828
d0012400:	2a006d9a 	bcs	0xd002da70
d0012404:	f8dfd1c2 			; <UNDEFINED> instruction: 0xf8dfd1c2
d0012408:	447a27d0 	ldrbtmi	r2, [sl], #-2000	; 0xfffff830
d001240c:	f7ffe7b7 			; <UNDEFINED> instruction: 0xf7ffe7b7
d0012410:	e7d8f853 			; <UNDEFINED> instruction: 0xe7d8f853
d0012414:	f850f7ff 			; <UNDEFINED> instruction: 0xf850f7ff
d0012418:	682ae7e3 	stmdavs	sl!, {r0, r1, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d001241c:	68eb19f0 	stmiavs	fp!, {r4, r5, r6, r7, r8, fp, ip}^
d0012420:	1a12441a 	bne	0xd04a3490
d0012424:	d1e82a04 	mvnle	r2, r4, lsl #20
d0012428:	17b0f8df 	sbfxne	pc, pc, #17, #17
d001242c:	f0074479 			; <UNDEFINED> instruction: 0xf0074479
d0012430:	2800f8a9 	stmdacs	r0, {r0, r3, r5, r7, fp, ip, sp, lr, pc}
d0012434:	6fabd1e1 	svcvs	0x00abd1e1
d0012438:	72a6f44f 	adcvc	pc, r6, #1325400064	; 0x4f000000
d001243c:	5503fb02 	strpl	pc, [r3, #-2818]	; 0xfffff4fe
d0012440:	f8852301 			; <UNDEFINED> instruction: 0xf8852301
d0012444:	2000330a 	andcs	r3, r0, sl, lsl #6
d0012448:	f828f7ff 			; <UNDEFINED> instruction: 0xf828f7ff
d001244c:	f0002820 			; <UNDEFINED> instruction: 0xf0002820
d0012450:	280980c7 	stmdacs	r9, {r0, r1, r2, r6, r7, pc}
d0012454:	80c4f000 	sbchi	pc, r4, r0
d0012458:	3784f8df 			; <UNDEFINED> instruction: 0x3784f8df
d001245c:	68da447b 	ldmvs	sl, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0012460:	429a685b 	addsmi	r6, sl, #5963776	; 0x5b0000
d0012464:	80b7f000 	adcshi	pc, r7, r0
d0012468:	f000280d 			; <UNDEFINED> instruction: 0xf000280d
d001246c:	280a80b4 	stmdacs	sl, {r2, r4, r5, r7, pc}
d0012470:	80b1f000 	adcshi	pc, r1, r0
d0012474:	d105282f 	tstle	r5, pc, lsr #16
d0012478:	f7ff2001 			; <UNDEFINED> instruction: 0xf7ff2001
d001247c:	282ff80f 	stmdacs	pc!, {r0, r1, r2, r3, fp, ip, sp, lr, pc}	; <UNPREDICTABLE>
d0012480:	80a9f000 	adchi	pc, r9, r0
d0012484:	375cf8df 	smmlscc	ip, pc, r8, pc	; <UNPREDICTABLE>
d0012488:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d001248c:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0012490:	f8dfaf7d 			; <UNDEFINED> instruction: 0xf8dfaf7d
d0012494:	447a2754 	ldrbtmi	r2, [sl], #-1876	; 0xfffff8ac
d0012498:	f7ffe771 			; <UNDEFINED> instruction: 0xf7ffe771
d001249c:	2822f80d 	stmdacs	r2!, {r0, r2, r3, fp, ip, sp, lr, pc}
d00124a0:	d00c4606 	andle	r4, ip, r6, lsl #12
d00124a4:	d026283c 	eorle	r2, r6, ip, lsr r8
d00124a8:	3740f8df 			; <UNDEFINED> instruction: 0x3740f8df
d00124ac:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d00124b0:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d00124b4:	f8dfaf6b 			; <UNDEFINED> instruction: 0xf8dfaf6b
d00124b8:	447a2738 	ldrbtmi	r2, [sl], #-1848	; 0xfffff8c8
d00124bc:	4682e75f 	pkhtbmi	lr, r2, pc, asr #14	; <UNPREDICTABLE>
d00124c0:	7730f8df 			; <UNDEFINED> instruction: 0x7730f8df
d00124c4:	f8d7447f 			; <UNDEFINED> instruction: 0xf8d7447f
d00124c8:	68fd8000 	ldmvs	sp!, {pc}^
d00124cc:	200068f9 	strdcs	r6, [r0], -r9
d00124d0:	b004f8d7 	ldrdlt	pc, [r4], -r7
d00124d4:	ffe2f7fe 			; <UNDEFINED> instruction: 0xffe2f7fe
d00124d8:	d30f4559 	movwle	r4, #62809	; 0xf559
d00124dc:	d0164582 	andsle	r4, r6, r2, lsl #11
d00124e0:	3714f8df 			; <UNDEFINED> instruction: 0x3714f8df
d00124e4:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d00124e8:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d00124ec:	f8dfaf4f 			; <UNDEFINED> instruction: 0xf8dfaf4f
d00124f0:	447a270c 	ldrbtmi	r2, [sl], #-1804	; 0xfffff8f4
d00124f4:	f04fe743 			; <UNDEFINED> instruction: 0xf04fe743
d00124f8:	e7e10a3e 			; <UNDEFINED> instruction: 0xe7e10a3e
d00124fc:	d0064582 	andle	r4, r6, r2, lsl #11
d0012500:	d0ed280d 	rscle	r2, sp, sp, lsl #16
d0012504:	d0eb280a 	rscle	r2, fp, sl, lsl #16
d0012508:	ffd6f7fe 			; <UNDEFINED> instruction: 0xffd6f7fe
d001250c:	f8dfe7de 			; <UNDEFINED> instruction: 0xf8dfe7de
d0012510:	444536f0 	strbmi	r3, [r5], #-1776	; 0xfffff910
d0012514:	681f447b 	ldmdavs	pc, {r0, r1, r3, r4, r5, r6, sl, lr}	; <UNPREDICTABLE>
d0012518:	1b7f440f 	blne	0xd1fe355c
d001251c:	f7fed0e0 			; <UNDEFINED> instruction: 0xf7fed0e0
d0012520:	2000ffcb 	andcs	pc, r0, fp, asr #31
d0012524:	ffbaf7fe 			; <UNDEFINED> instruction: 0xffbaf7fe
d0012528:	d0f82820 	rscsle	r2, r8, r0, lsr #16
d001252c:	d0f62809 	rscsle	r2, r6, r9, lsl #16
d0012530:	36d0f8df 			; <UNDEFINED> instruction: 0x36d0f8df
d0012534:	68da447b 	ldmvs	sl, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0012538:	429a685b 	addsmi	r6, sl, #5963776	; 0x5b0000
d001253c:	280dd015 	stmdacs	sp, {r0, r2, r4, ip, lr, pc}
d0012540:	280ad013 	stmdacs	sl, {r0, r1, r4, ip, lr, pc}
d0012544:	282fd011 	stmdacs	pc!, {r0, r4, ip, lr, pc}	; <UNPREDICTABLE>
d0012548:	2001d104 	andcs	sp, r1, r4, lsl #2
d001254c:	ffa6f7fe 			; <UNDEFINED> instruction: 0xffa6f7fe
d0012550:	d00a282f 	andle	r2, sl, pc, lsr #16
d0012554:	36b0f8df 	ssatcc	pc, #17, pc, asr #17	; <UNPREDICTABLE>
d0012558:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d001255c:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0012560:	f8dfaf15 			; <UNDEFINED> instruction: 0xf8dfaf15
d0012564:	447a26a8 	ldrbtmi	r2, [sl], #-1704	; 0xfffff958
d0012568:	2f06e709 	svccs	0x0006e709
d001256c:	f8dfd11b 			; <UNDEFINED> instruction: 0xf8dfd11b
d0012570:	463a16a0 	ldrtmi	r1, [sl], -r0, lsr #13
d0012574:	44794628 	ldrbtmi	r4, [r9], #-1576	; 0xfffff9d8
d0012578:	f804f007 			; <UNDEFINED> instruction: 0xf804f007
d001257c:	9b0ab998 	blls	0xd02c0be4
d0012580:	9419ad12 	ldrls	sl, [r9], #-3346	; 0xfffff2ee
d0012584:	4a10ee18 	bmi	0xd044ddec
d0012588:	9b099315 	blls	0xd02771e4
d001258c:	9060f88d 	rsbls	pc, r0, sp, lsl #17
d0012590:	f44f9316 	vst2.8	{d25-d28}, [pc :64], r6
d0012594:	93177383 	tstls	r7, #201326594	; 0xc000002
d0012598:	c40fcd0f 	strgt	ip, [pc], #-3343	; 0xd00125a0
d001259c:	000fe895 	muleq	pc, r5, r8	; <UNPREDICTABLE>
d00125a0:	000fe884 	andeq	lr, pc, r4, lsl #17
d00125a4:	2e22e6f6 	mcrcs	6, 1, lr, cr2, cr6, {7}
d00125a8:	f8dfd00a 			; <UNDEFINED> instruction: 0xf8dfd00a
d00125ac:	447b3668 	ldrbtmi	r3, [fp], #-1640	; 0xfffff998
d00125b0:	2a006d9a 	bcs	0xd002dc20
d00125b4:	aeeaf47f 	mcrge	4, 7, pc, cr10, cr15, {3}	; <UNPREDICTABLE>
d00125b8:	265cf8df 			; <UNDEFINED> instruction: 0x265cf8df
d00125bc:	e6de447a 			; <UNDEFINED> instruction: 0xe6de447a
d00125c0:	464a4623 	strbmi	r4, [sl], -r3, lsr #12
d00125c4:	980a9909 	stmdals	sl, {r0, r3, r8, fp, ip, pc}
d00125c8:	5700e9cd 	strpl	lr, [r0, -sp, asr #19]
d00125cc:	fb6ef7fe 	blx	0xd1bd05ce
d00125d0:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d00125d4:	ee18aedb 	mrc	14, 0, sl, cr8, cr11, {6}
d00125d8:	f7ff0a10 			; <UNDEFINED> instruction: 0xf7ff0a10
d00125dc:	e6d9f88f 	ldrb	pc, [r9], pc, lsl #17	; <UNPREDICTABLE>
d00125e0:	ff6af7fe 			; <UNDEFINED> instruction: 0xff6af7fe
d00125e4:	ea48e72f 	b	0xd124c2a8
d00125e8:	9a0c0305 	bls	0xd0313204
d00125ec:	4313433b 	tstmi	r3, #-335544320	; 0xec000000
d00125f0:	43139a0b 	tstmi	r3, #45056	; 0xb000
d00125f4:	43139a0d 	tstmi	r3, #53248	; 0xd000
d00125f8:	ea439a0e 	b	0xd10f8e38
d00125fc:	4313030a 	tstmi	r3, #671088640	; 0x28000000
d0012600:	43139a0f 	tstmi	r3, #61440	; 0xf000
d0012604:	030bea53 	movweq	lr, #47699	; 0xba53
d0012608:	f7fed121 			; <UNDEFINED> instruction: 0xf7fed121
d001260c:	b170ff0d 	cmnlt	r0, sp, lsl #30	; <UNPREDICTABLE>
d0012610:	3608f8df 			; <UNDEFINED> instruction: 0x3608f8df
d0012614:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d0012618:	f8dfb94a 			; <UNDEFINED> instruction: 0xf8dfb94a
d001261c:	669c2604 	ldrvs	r2, [ip], r4, lsl #12
d0012620:	659a447a 	ldrvs	r4, [sl, #1146]	; 0x47a
d0012624:	65da9a0a 	ldrbvs	r9, [sl, #2570]	; 0xa0a
d0012628:	e9c39a09 	stmib	r3, {r0, r3, r9, fp, ip, pc}^
d001262c:	f7fe2918 			; <UNDEFINED> instruction: 0xf7fe2918
d0012630:	2220ff6f 	eorcs	pc, r0, #444	; 0x1bc
d0012634:	ee182100 	mufe	f2, f0, f0
d0012638:	f0060a10 			; <UNDEFINED> instruction: 0xf0060a10
d001263c:	f44fff85 			; <UNDEFINED> instruction: 0xf44fff85
d0012640:	ee187391 	mrc	3, 0, r7, cr8, cr1, {4}
d0012644:	61532a10 	cmpvs	r3, r0, lsl sl
d0012648:	f7fee6a4 			; <UNDEFINED> instruction: 0xf7fee6a4
d001264c:	2000ff35 	andcs	pc, r0, r5, lsr pc	; <UNPREDICTABLE>
d0012650:	ff24f7fe 			; <UNDEFINED> instruction: 0xff24f7fe
d0012654:	d0f82820 	rscsle	r2, r8, r0, lsr #16
d0012658:	d0f62809 	rscsle	r2, r6, r9, lsl #16
d001265c:	55c4f8df 	strbpl	pc, [r4, #2271]	; 0x8df	; <UNPREDICTABLE>
d0012660:	682b447d 	stmdavs	fp!, {r0, r2, r3, r4, r5, r6, sl, lr}
d0012664:	68eb9310 	stmiavs	fp!, {r4, r8, r9, ip, pc}^
d0012668:	9a119311 	bls	0xd04772b4
d001266c:	189e9b10 	ldmne	lr, {r4, r8, r9, fp, ip, pc}
d0012670:	ff4ef7fe 			; <UNDEFINED> instruction: 0xff4ef7fe
d0012674:	68eb682a 	stmiavs	fp!, {r1, r3, r5, fp, sp, lr}^
d0012678:	441a4635 	ldrmi	r4, [sl], #-1589	; 0xfffff9cb
d001267c:	429a1c6b 	addsmi	r1, sl, #27392	; 0x6b00
d0012680:	4615d801 	ldrmi	sp, [r5], -r1, lsl #16
d0012684:	f813e038 			; <UNDEFINED> instruction: 0xf813e038
d0012688:	292f1c01 	stmdbcs	pc!, {r0, sl, fp, ip}	; <UNPREDICTABLE>
d001268c:	7819d15e 	ldmdavc	r9, {r1, r2, r3, r4, r6, r8, ip, lr, pc}
d0012690:	d031292f 	eorsle	r2, r1, pc, lsr #18
d0012694:	d159292a 	cmple	r9, sl, lsr #18
d0012698:	1c591cab 	mrrcne	12, 10, r1, r9, cr11
d001269c:	d91a428a 	ldmdble	sl, {r1, r3, r7, r9, lr}
d00126a0:	0c01f811 	stceq	8, cr15, [r1], {17}
d00126a4:	d114282a 	tstle	r4, sl, lsr #16
d00126a8:	282f7808 	stmdacs	pc!, {r3, fp, ip, sp, lr}	; <UNPREDICTABLE>
d00126ac:	3302d111 	movwcc	sp, #8465	; 0x2111
d00126b0:	d920429a 	stmdble	r0!, {r1, r3, r4, r7, r9, lr}
d00126b4:	1b01f813 	blne	0xd0090708
d00126b8:	d0f92920 	rscsle	r2, r9, r0, lsr #18
d00126bc:	d0f72909 	rscsle	r2, r7, r9, lsl #18
d00126c0:	2564f8df 	strbcs	pc, [r4, #-2271]!	; 0xfffff721	; <UNPREDICTABLE>
d00126c4:	6d93447a 	cfldrsvs	mvf4, [r3, #488]	; 0x1e8
d00126c8:	f8dfb9b3 			; <UNDEFINED> instruction: 0xf8dfb9b3
d00126cc:	447b3560 	ldrbtmi	r3, [fp], #-1376	; 0xfffffaa0
d00126d0:	460be009 	strmi	lr, [fp], -r9
d00126d4:	f8dfe7e1 			; <UNDEFINED> instruction: 0xf8dfe7e1
d00126d8:	447a2558 	ldrbtmi	r2, [sl], #-1368	; 0xfffffaa8
d00126dc:	b95b6d93 	ldmdblt	fp, {r0, r1, r4, r7, r8, sl, fp, sp, lr}^
d00126e0:	3550f8df 	ldrbcc	pc, [r0, #-2271]	; 0xfffff721	; <UNPREDICTABLE>
d00126e4:	6593447b 	ldrvs	r4, [r3, #1147]	; 0x47b
d00126e8:	66949b0a 	ldrvs	r9, [r4], sl, lsl #22
d00126ec:	9b0965d3 	blls	0xd026be40
d00126f0:	3918e9c2 	ldmdbcc	r8, {r1, r6, r7, r8, fp, sp, lr, pc}
d00126f4:	d1e3e000 	mvnle	lr, r0
d00126f8:	d20642ae 	andle	r4, r6, #-536870902	; 0xe000000a
d00126fc:	3c01f815 	stccc	8, cr15, [r1], {21}
d0012700:	2b201e6a 	blcs	0xd081a0b0
d0012704:	2b09d0bd 	blcs	0xd0286a00
d0012708:	f7fed0bb 			; <UNDEFINED> instruction: 0xf7fed0bb
d001270c:	9b0dfe8d 	blls	0xd0392148
d0012710:	ea434607 	b	0xd10e3f34
d0012714:	9b0e000a 	blls	0xd0392744
d0012718:	f0004303 			; <UNDEFINED> instruction: 0xf0004303
d001271c:	f8df8091 			; <UNDEFINED> instruction: 0xf8df8091
d0012720:	f24d3518 	vqrshl.s8	d19, d8, d13
d0012724:	447b020c 	ldrbtmi	r0, [fp], #-524	; 0xfffffdf4
d0012728:	2a20589a 	bcs	0xd0828998
d001272c:	6d9ad110 	ldfvsd	f5, [sl, #64]	; 0x40
d0012730:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0012734:	f8dfaf7e 			; <UNDEFINED> instruction: 0xf8dfaf7e
d0012738:	447a2504 	ldrbtmi	r2, [sl], #-1284	; 0xfffffafc
d001273c:	9a0a659a 	bls	0xd02abdac
d0012740:	65da669c 	ldrbvs	r6, [sl, #1692]	; 0x69c
d0012744:	e9c39a09 	stmib	r3, {r0, r3, r9, fp, ip, pc}^
d0012748:	e7722918 			; <UNDEFINED> instruction: 0xe7722918
d001274c:	e795461d 			; <UNDEFINED> instruction: 0xe795461d
d0012750:	d0732f00 	rsbsle	r2, r3, r0, lsl #30
d0012754:	d0582800 	subsle	r2, r8, r0, lsl #16
d0012758:	d00542ae 	andle	r4, r5, lr, lsr #5
d001275c:	9a119b10 	bls	0xd04793a4
d0012760:	f7fd5c98 			; <UNDEFINED> instruction: 0xf7fd5c98
d0012764:	b970fd6b 	ldmdblt	r0!, {r0, r1, r3, r5, r6, r8, sl, fp, ip, sp, lr, pc}^
d0012768:	34d4f8df 	ldrbcc	pc, [r4], #2271	; 0x8df	; <UNPREDICTABLE>
d001276c:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d0012770:	f8dfb94a 			; <UNDEFINED> instruction: 0xf8dfb94a
d0012774:	669c24d0 			; <UNDEFINED> instruction: 0x669c24d0
d0012778:	659a447a 	ldrvs	r4, [sl, #1146]	; 0x47a
d001277c:	65da9a0a 	ldrbvs	r9, [sl, #2570]	; 0xa0a
d0012780:	e9c39a09 	stmib	r3, {r0, r3, r9, fp, ip, pc}^
d0012784:	46b02918 	ssatmi	r2, #17, r8, lsl #18
d0012788:	46424545 	strbmi	r4, [r2], -r5, asr #10
d001278c:	7811d91a 	ldmdavc	r1, {r1, r3, r4, r8, fp, ip, lr, pc}
d0012790:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d0012794:	f7fd4608 			; <UNDEFINED> instruction: 0xf7fd4608
d0012798:	2800fd51 	stmdacs	r0, {r0, r4, r6, r8, sl, fp, ip, sp, lr, pc}
d001279c:	3930d1f4 	ldmdbcc	r0!, {r2, r4, r5, r6, r7, r8, ip, lr, pc}
d00127a0:	d9f12909 	ldmible	r1!, {r0, r3, r8, fp, sp}^
d00127a4:	34a0f8df 	strtcc	pc, [r0], #2271	; 0x8df
d00127a8:	6d99447b 	cfldrsvs	mvf4, [r9, #492]	; 0x1ec
d00127ac:	f8dfb959 			; <UNDEFINED> instruction: 0xf8dfb959
d00127b0:	669c149c 			; <UNDEFINED> instruction: 0x669c149c
d00127b4:	65994479 	ldrvs	r4, [r9, #1145]	; 0x479
d00127b8:	65d9990a 	ldrbvs	r9, [r9, #2314]	; 0x90a
d00127bc:	e9c39909 	stmib	r3, {r0, r3, r8, fp, ip, pc}^
d00127c0:	e0001918 	and	r1, r0, r8, lsl r9
d00127c4:	f8dfd1ee 			; <UNDEFINED> instruction: 0xf8dfd1ee
d00127c8:	1b920488 	blne	0xce4939f0
d00127cc:	44784631 	ldrbtmi	r4, [r8], #-1585	; 0xfffff9cf
d00127d0:	fd12f7fd 	ldc2	7, cr15, [r2, #-1012]	; 0xfffffc0c
d00127d4:	0f00f1ba 	svceq	0x0000f1ba
d00127d8:	43c0d100 	bicmi	sp, r0, #0, 2
d00127dc:	f8df0fc0 			; <UNDEFINED> instruction: 0xf8df0fc0
d00127e0:	f24d3474 	vqshl.s8	<illegal reg q9.5>, q10, <illegal reg q6.5>
d00127e4:	2f00010c 	svccs	0x0000010c
d00127e8:	bf08447b 	svclt	0x0008447b
d00127ec:	585a2000 	ldmdapl	sl, {sp}^
d00127f0:	f5021c54 			; <UNDEFINED> instruction: 0xf5021c54
d00127f4:	3222524f 	eorcc	r5, r2, #-268435452	; 0xf0000004
d00127f8:	eb03505c 	bl	0xd00e6970
d00127fc:	22000382 	andcs	r0, r0, #134217730	; 0x8000002
d0012800:	7158711f 	cmpvc	r8, pc, lsl r1
d0012804:	71da7198 			; <UNDEFINED> instruction: 0x71da7198
d0012808:	2200e713 	andcs	lr, r0, #4980736	; 0x4c0000
d001280c:	95052300 	strls	r2, [r5, #-768]	; 0xfffffd00
d0012810:	e9cd9604 	stmib	sp, {r2, r9, sl, ip, pc}^
d0012814:	ab122312 	blge	0xd049b464
d0012818:	ab2b9306 	blge	0xd0af7438
d001281c:	e88dcb0f 	stm	sp, {r0, r1, r2, r3, r8, r9, fp, lr, pc}
d0012820:	ab27000f 	blge	0xd09d2864
d0012824:	f7fecb0f 			; <UNDEFINED> instruction: 0xf7fecb0f
d0012828:	2800fdb7 	stmdacs	r0, {r0, r1, r2, r4, r5, r7, r8, sl, fp, ip, sp, lr, pc}
d001282c:	e9ddd0d7 	ldmib	sp, {r0, r1, r2, r4, r6, r7, ip, lr, pc}^
d0012830:	43132312 	tstmi	r3, #1207959552	; 0x48000000
d0012834:	2001bf14 	andcs	fp, r1, r4, lsl pc
d0012838:	e7d02000 	ldrb	r2, [r0, r0]
d001283c:	e7ce4638 			; <UNDEFINED> instruction: 0xe7ce4638
d0012840:	ea489b0f 	b	0xd1239484
d0012844:	ea500003 	b	0xd1412858
d0012848:	f000030b 			; <UNDEFINED> instruction: 0xf000030b
d001284c:	f8df8096 			; <UNDEFINED> instruction: 0xf8df8096
d0012850:	447b3408 	ldrbtmi	r3, [fp], #-1032	; 0xfffffbf8
d0012854:	11fcf8d3 	ldrsbne	pc, [ip, #131]!	; 0x83	; <UNPREDICTABLE>
d0012858:	eb03b111 	bl	0xd00feca4
d001285c:	6f891141 	svcvs	0x00891141
d0012860:	f24d4bfe 	vpadd.i8	q10, <illegal reg q14.5>, q15
d0012864:	447b020c 	ldrbtmi	r0, [fp], #-524	; 0xfffffdf4
d0012868:	428a589a 	addmi	r5, sl, #10092544	; 0x9a0000
d001286c:	6d9ad806 	ldcvs	8, cr13, [sl, #24]
d0012870:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0012874:	4afaaede 	bmi	0xcfebe3f4
d0012878:	e75f447a 			; <UNDEFINED> instruction: 0xe75f447a
d001287c:	f1b81e51 			; <UNDEFINED> instruction: 0xf1b81e51
d0012880:	d0120f00 	andsle	r0, r2, r0, lsl #30
d0012884:	d00a42ae 	andle	r4, sl, lr, lsr #5
d0012888:	b9426d9a 	stmdblt	r2, {r1, r3, r4, r7, r8, sl, fp, sp, lr}^
d001288c:	669c4af5 			; <UNDEFINED> instruction: 0x669c4af5
d0012890:	659a447a 	ldrvs	r4, [sl, #1146]	; 0x47a
d0012894:	65da9a0a 	ldrbvs	r9, [sl, #2570]	; 0xa0a
d0012898:	e9c39a09 	stmib	r3, {r0, r3, r9, fp, ip, pc}^
d001289c:	4bf22918 	blmi	0xcfc9cd04
d00128a0:	020cf24d 	andeq	pc, ip, #-805306364	; 0xd0000004
d00128a4:	5099447b 	addspl	r4, r9, fp, ror r4
d00128a8:	f502e6c3 			; <UNDEFINED> instruction: 0xf502e6c3
d00128ac:	3221524f 	eorcc	r5, r1, #-268435452	; 0xf0000004
d00128b0:	0f00f1bb 	svceq	0x0000f1bb
d00128b4:	42aed028 	adcmi	sp, lr, #40	; 0x28
d00128b8:	eb03d103 	bl	0xd0106ccc
d00128bc:	79db0382 	ldmibvc	fp, {r1, r7, r8, r9}^
d00128c0:	4beab163 	blmi	0xcfabee54
d00128c4:	6d99447b 	cfldrsvs	mvf4, [r9, #492]	; 0x1ec
d00128c8:	49e9b941 	stmibmi	r9!, {r0, r6, r8, fp, ip, sp, pc}^
d00128cc:	4479669c 	ldrbtmi	r6, [r9], #-1692	; 0xfffff964
d00128d0:	990a6599 	stmdbls	sl, {r0, r3, r4, r7, r8, sl, sp, lr}
d00128d4:	990965d9 	stmdbls	r9, {r0, r3, r4, r6, r7, r8, sl, sp, lr}
d00128d8:	1918e9c3 	ldmdbne	r8, {r0, r1, r6, r7, r8, fp, sp, lr, pc}
d00128dc:	447b4be5 	ldrbtmi	r4, [fp], #-3045	; 0xfffff41b
d00128e0:	0382eb03 	orreq	lr, r2, #3072	; 0xc00
d00128e4:	b1297919 			; <UNDEFINED> instruction: 0xb1297919
d00128e8:	8006f893 	mulhi	r6, r3, r8
d00128ec:	f888fab8 			; <UNDEFINED> instruction: 0xf888fab8
d00128f0:	1858ea4f 	ldmdane	r8, {r0, r1, r2, r3, r6, r9, fp, sp, lr, pc}^
d00128f4:	447b4be0 	ldrbtmi	r4, [fp], #-3040	; 0xfffff420
d00128f8:	0282eb03 	addeq	lr, r2, #3072	; 0xc00
d00128fc:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d0012900:	8005f882 	andhi	pc, r5, r2, lsl #17
d0012904:	e69480d3 			; <UNDEFINED> instruction: 0xe69480d3
d0012908:	0182eb03 	orreq	lr, r2, r3, lsl #22
d001290c:	b15179c9 	cmplt	r1, r9, asr #19
d0012910:	b9416d99 	stmdblt	r1, {r0, r3, r4, r7, r8, sl, fp, sp, lr}^
d0012914:	669c49d9 			; <UNDEFINED> instruction: 0x669c49d9
d0012918:	65994479 	ldrvs	r4, [r9, #1145]	; 0x479
d001291c:	65d9990a 	ldrbvs	r9, [r9, #2314]	; 0x90a
d0012920:	e9c39909 	stmib	r3, {r0, r3, r8, fp, ip, pc}^
d0012924:	4cd61918 			; <UNDEFINED> instruction: 0x4cd61918
d0012928:	21002000 	mrscs	r2, (UNDEF: 0)
d001292c:	eb04447c 	bl	0xd0123b24
d0012930:	79230482 	stmdbvc	r3!, {r1, r7, sl}
d0012934:	0112e9cd 	tsteq	r2, sp, asr #19
d0012938:	7163b90b 	cmnvc	r3, fp, lsl #18
d001293c:	79a3e679 	stmibvc	r3!, {r0, r3, r4, r5, r6, r9, sl, sp, lr, pc}
d0012940:	2300b10b 	movwcs	fp, #267	; 0x10b
d0012944:	ab12e7f9 	blge	0xd04cc930
d0012948:	96049505 	strls	r9, [r4], -r5, lsl #10
d001294c:	ab2b9306 	blge	0xd0af756c
d0012950:	e88dcb0f 	stm	sp, {r0, r1, r2, r3, r8, r9, fp, lr, pc}
d0012954:	ab27000f 	blge	0xd09d2998
d0012958:	f7fecb0f 			; <UNDEFINED> instruction: 0xf7fecb0f
d001295c:	e9ddfd1d 	ldmib	sp, {r0, r2, r3, r4, r8, sl, fp, ip, sp, lr, pc}^
d0012960:	ea522312 	b	0xd149b5b0
d0012964:	bf140103 	svclt	0x00140103
d0012968:	21002101 	tstcs	r0, r1, lsl #2
d001296c:	71614313 	cmnvc	r1, r3, lsl r3
d0012970:	ae5ff43f 	mrcge	4, 2, APSR_nzcv, cr15, cr15, {1}
d0012974:	71a32301 			; <UNDEFINED> instruction: 0x71a32301
d0012978:	2f00e65b 	svccs	0x0000e65b
d001297c:	ae59f43f 	mrcge	4, 2, APSR_nzcv, cr9, cr15, {1}
d0012980:	9a0b9b0c 	bls	0xd02f95b8
d0012984:	f43f4313 			; <UNDEFINED> instruction: 0xf43f4313
d0012988:	42aeae54 	adcmi	sl, lr, #84, 28	; 0x540
d001298c:	9b10d024 	blls	0xd0446a24
d0012990:	5c989a11 	vldmiapl	r8, {s18-s34}
d0012994:	fc52f7fd 	mrrc2	7, 15, pc, r2, cr13	; <UNPREDICTABLE>
d0012998:	4637b1f0 			; <UNDEFINED> instruction: 0x4637b1f0
d001299c:	463b42bd 			; <UNDEFINED> instruction: 0x463b42bd
d00129a0:	463ad90c 	ldrtmi	sp, [sl], -ip, lsl #18
d00129a4:	f812970c 			; <UNDEFINED> instruction: 0xf812970c
d00129a8:	46081b01 	strmi	r1, [r8], -r1, lsl #22
d00129ac:	fc46f7fd 	mcrr2	7, 15, pc, r6, cr13	; <UNPREDICTABLE>
d00129b0:	f1a1b9d8 			; <UNDEFINED> instruction: 0xf1a1b9d8
d00129b4:	9b0c0030 	blls	0xd0312a7c
d00129b8:	d9162809 	ldmdble	r6, {r0, r3, fp, sp}
d00129bc:	0b06eba7 	bleq	0xd01cd860
d00129c0:	0f3ff1bb 	svceq	0x003ff1bb
d00129c4:	4bafd913 	blmi	0xcec08e18
d00129c8:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d00129cc:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d00129d0:	4aadae30 	bmi	0xceb7e298
d00129d4:	e6b1447a 	sxtah	r4, r1, sl, ror #8
d00129d8:	447b4bac 	ldrbtmi	r4, [fp], #-2988	; 0xfffff454
d00129dc:	2a006d9a 	bcs	0xd002e04c
d00129e0:	ae27f47f 	mcrge	4, 1, pc, cr7, cr15, {3}	; <UNPREDICTABLE>
d00129e4:	447a4aaa 	ldrbtmi	r4, [sl], #-2730	; 0xfffff556
d00129e8:	4617e6a8 	ldrmi	lr, [r7], -r8, lsr #13
d00129ec:	f8dfe7d6 			; <UNDEFINED> instruction: 0xf8dfe7d6
d00129f0:	465aa2a4 	ldrbmi	sl, [sl], -r4, lsr #5
d00129f4:	930c4631 	movwls	r4, #50737	; 0xc631
d00129f8:	465044fa 			; <UNDEFINED> instruction: 0x465044fa
d00129fc:	fbfcf7fd 	blx	0xcff509fa
d0012a00:	46809a0b 	strmi	r9, [r0], fp, lsl #20
d0012a04:	b36a9b0c 	cmnlt	sl, #12, 22	; 0x3000
d0012a08:	d91342bd 	ldmdble	r3, {r0, r2, r3, r4, r5, r7, r9, lr}
d0012a0c:	3b01f817 	blcc	0xd0090a70
d0012a10:	d0f92b20 	rscsle	r2, r9, r0, lsr #22
d0012a14:	d0f72b09 	rscsle	r2, r7, r9, lsl #22
d0012a18:	447b4b9f 	ldrbtmi	r4, [fp], #-2975	; 0xfffff461
d0012a1c:	b9526d9a 	ldmdblt	r2, {r1, r3, r4, r7, r8, sl, fp, sp, lr}^
d0012a20:	669c4a9e 			; <UNDEFINED> instruction: 0x669c4a9e
d0012a24:	659a447a 	ldrvs	r4, [sl, #1146]	; 0x47a
d0012a28:	65da9a0a 	ldrbvs	r9, [sl, #2570]	; 0xa0a
d0012a2c:	e9c39a09 	stmib	r3, {r0, r3, r9, fp, ip, pc}^
d0012a30:	e0002918 	and	r2, r0, r8, lsl r9
d0012a34:	f1b8d1f0 			; <UNDEFINED> instruction: 0xf1b8d1f0
d0012a38:	f6ff0f00 			; <UNDEFINED> instruction: 0xf6ff0f00
d0012a3c:	4b98adfa 	blmi	0xce63e22c
d0012a40:	7288f64c 	addvc	pc, r8, #76, 12	; 0x4c00000
d0012a44:	3488f64a 	strcc	pc, [r8], #1610	; 0x64a
d0012a48:	5899447b 	ldmpl	r9, {r0, r1, r3, r4, r5, r6, sl, lr}
d0012a4c:	50993901 	addspl	r3, r9, r1, lsl #18
d0012a50:	fb022248 	blx	0xd009b37a
d0012a54:	fb023008 	blx	0xd009ea7e
d0012a58:	44203101 	strtmi	r3, [r0], #-257	; 0xfffffeff
d0012a5c:	f0064421 			; <UNDEFINED> instruction: 0xf0064421
d0012a60:	e5e6fd81 	strb	pc, [r6, #3457]!	; 0xd81	; <UNPREDICTABLE>
d0012a64:	d91d42bd 	ldmdble	sp, {r0, r2, r3, r4, r5, r7, r9, lr}
d0012a68:	2b28783b 	blcs	0xd0a30b5c
d0012a6c:	f8dad111 			; <UNDEFINED> instruction: 0xf8dad111
d0012a70:	2b003058 	blcs	0xd001ebd8
d0012a74:	adddf47f 	cfldrdge	mvd15, [sp, #508]	; 0x1fc
d0012a78:	f8ca4b8a 			; <UNDEFINED> instruction: 0xf8ca4b8a
d0012a7c:	447b4068 	ldrbtmi	r4, [fp], #-104	; 0xffffff98
d0012a80:	3058f8ca 	subscc	pc, r8, sl, asr #17
d0012a84:	f8ca9b0a 			; <UNDEFINED> instruction: 0xf8ca9b0a
d0012a88:	9b09305c 	blls	0xd025ec00
d0012a8c:	3918e9ca 	ldmdbcc	r8, {r1, r3, r6, r7, r8, fp, sp, lr, pc}
d0012a90:	42bde5cf 	adcsmi	lr, sp, #868220928	; 0x33c00000
d0012a94:	d005463b 	andle	r4, r5, fp, lsr r6
d0012a98:	2b01f817 	blcs	0xd0090afc
d0012a9c:	d0f82a20 	rscsle	r2, r8, r0, lsr #20
d0012aa0:	d0f62a09 	rscsle	r2, r6, r9, lsl #20
d0012aa4:	21002001 	tstcs	r0, r1
d0012aa8:	e9cd429d 	stmib	sp, {r0, r2, r3, r4, r7, r9, lr}^
d0012aac:	d00e0112 	andle	r0, lr, r2, lsl r1
d0012ab0:	aa129304 	bge	0xd04b76c8
d0012ab4:	9505ab2b 	strls	sl, [r5, #-2859]	; 0xfffff4d5
d0012ab8:	cb0f9206 	blgt	0xd03f72d8
d0012abc:	000fe88d 	andeq	lr, pc, sp, lsl #17
d0012ac0:	cb0fab27 	blgt	0xd03fd764
d0012ac4:	fc68f7fe 	stc2l	7, cr15, [r8], #-1016	; 0xfffffc08
d0012ac8:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0012acc:	f1b8adb2 			; <UNDEFINED> instruction: 0xf1b8adb2
d0012ad0:	da100f00 	ble	0xd04166d8
d0012ad4:	f64c4b74 			; <UNDEFINED> instruction: 0xf64c4b74
d0012ad8:	447b7288 	ldrbtmi	r7, [fp], #-648	; 0xfffffd78
d0012adc:	28805898 	stmcs	r0, {r3, r4, r7, fp, ip, lr}
d0012ae0:	6d9ad106 	ldfvsd	f5, [sl, #24]
d0012ae4:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0012ae8:	4a70ada4 	bmi	0xd1c3e180
d0012aec:	e625447a 			; <UNDEFINED> instruction: 0xe625447a
d0012af0:	46801c41 	strmi	r1, [r0], r1, asr #24
d0012af4:	24485099 	strbcs	r5, [r8], #-153	; 0xffffff67
d0012af8:	3588f64a 	strcc	pc, [r8, #1610]	; 0x64a
d0012afc:	4631465a 			; <UNDEFINED> instruction: 0x4631465a
d0012b00:	f408fb04 			; <UNDEFINED> instruction: 0xf408fb04
d0012b04:	81a8f8df 	ldrdhi	pc, [r8, pc]!	; <UNPREDICTABLE>
d0012b08:	44f81960 	ldrbtmi	r1, [r8], #2400	; 0x960
d0012b0c:	44a04440 	strtmi	r4, [r0], #1088	; 0x440
d0012b10:	fd28f006 	stc2	0, cr15, [r8, #-24]!	; 0xffffffe8
d0012b14:	44c32300 	strbmi	r2, [r3], #768	; 0x300
d0012b18:	482bf508 	stmdami	fp!, {r3, r8, sl, ip, sp, lr, pc}
d0012b1c:	3005f80b 	andcc	pc, r5, fp, lsl #16
d0012b20:	2312e9dd 	tstcs	r2, #3620864	; 0x374000
d0012b24:	2332e9c8 	teqcs	r2, #200, 18	; 0x320000
d0012b28:	2a05e583 	bcs	0xd018c13c
d0012b2c:	aba7f47f 	blge	0xcea0fd30
d0012b30:	46304960 	ldrtmi	r4, [r0], -r0, ror #18
d0012b34:	46c2920c 	strbmi	r9, [r2], ip, lsl #4
d0012b38:	46474479 			; <UNDEFINED> instruction: 0x46474479
d0012b3c:	fd22f006 	stc2	0, cr15, [r2, #-24]!	; 0xffffffe8
d0012b40:	f380fab0 			; <UNDEFINED> instruction: 0xf380fab0
d0012b44:	4630495c 			; <UNDEFINED> instruction: 0x4630495c
d0012b48:	9a0c095b 	bls	0xd03150bc
d0012b4c:	46454479 			; <UNDEFINED> instruction: 0x46454479
d0012b50:	f006930b 			; <UNDEFINED> instruction: 0xf006930b
d0012b54:	fab0fd17 	blx	0xcec51fb8
d0012b58:	f8cdf380 			; <UNDEFINED> instruction: 0xf8cdf380
d0012b5c:	095b8030 	ldmdbeq	fp, {r4, r5, pc}^
d0012b60:	4956930d 	ldmdbmi	r6, {r0, r2, r3, r8, r9, ip, pc}^
d0012b64:	46302205 	ldrtmi	r2, [r0], -r5, lsl #4
d0012b68:	0b00f04f 	bleq	0xd004ecac
d0012b6c:	f0064479 			; <UNDEFINED> instruction: 0xf0064479
d0012b70:	fab0fd09 	blx	0xcec51f9c
d0012b74:	f8cdf880 			; <UNDEFINED> instruction: 0xf8cdf880
d0012b78:	ea4fb03c 	b	0xd13fec70
d0012b7c:	f8cd1858 			; <UNDEFINED> instruction: 0xf8cd1858
d0012b80:	f7ffb038 			; <UNDEFINED> instruction: 0xf7ffb038
d0012b84:	bf00bbb8 	svclt	0x0000bbb8
d0012b88:	00009d3c 	andeq	r9, r0, ip, lsr sp
d0012b8c:	00009d20 	andeq	r9, r0, r0, lsr #26
d0012b90:	00009d06 	andeq	r9, r0, r6, lsl #26
d0012b94:	fffffc44 			; <UNDEFINED> instruction: 0xfffffc44
d0012b98:	fffffc08 			; <UNDEFINED> instruction: 0xfffffc08
d0012b9c:	fffffbff 			; <UNDEFINED> instruction: 0xfffffbff
d0012ba0:	fffffbf0 			; <UNDEFINED> instruction: 0xfffffbf0
d0012ba4:	fffffbca 			; <UNDEFINED> instruction: 0xfffffbca
d0012ba8:	fffffbb9 			; <UNDEFINED> instruction: 0xfffffbb9
d0012bac:	fffffb85 			; <UNDEFINED> instruction: 0xfffffb85
d0012bb0:	00009bca 	andeq	r9, r0, sl, asr #23
d0012bb4:	00009ba4 	andeq	r9, r0, r4, lsr #23
d0012bb8:	00009b8c 	andeq	r9, r0, ip, lsl #23
d0012bbc:	fffffacc 			; <UNDEFINED> instruction: 0xfffffacc
d0012bc0:	00009b6a 	andeq	r9, r0, sl, ror #22
d0012bc4:	fffffaf0 			; <UNDEFINED> instruction: 0xfffffaf0
d0012bc8:	fffffa7c 			; <UNDEFINED> instruction: 0xfffffa7c
d0012bcc:	00009b00 	andeq	r9, r0, r0, lsl #22
d0012bd0:	00009aea 	andeq	r9, r0, sl, ror #21
d0012bd4:	00009ade 	ldrdeq	r9, [r0], -lr
d0012bd8:	fffffa8a 			; <UNDEFINED> instruction: 0xfffffa8a
d0012bdc:	fffffa63 			; <UNDEFINED> instruction: 0xfffffa63
d0012be0:	00009a80 	andeq	r9, r0, r0, lsl #21
d0012be4:	00009a54 	andeq	r9, r0, r4, asr sl
d0012be8:	fffffad6 			; <UNDEFINED> instruction: 0xfffffad6
d0012bec:	00009a30 	andeq	r9, r0, r0, lsr sl
d0012bf0:	fffffa0c 			; <UNDEFINED> instruction: 0xfffffa0c
d0012bf4:	00009a18 	andeq	r9, r0, r8, lsl sl
d0012bf8:	000099f8 	strdeq	r9, [r0], -r8
d0012bfc:	fffff9f1 			; <UNDEFINED> instruction: 0xfffff9f1
d0012c00:	000099c8 	andeq	r9, r0, r8, asr #19
d0012c04:	000099a8 	andeq	r9, r0, r8, lsr #19
d0012c08:	00009984 	andeq	r9, r0, r4, lsl #19
d0012c0c:	fffff9a4 			; <UNDEFINED> instruction: 0xfffff9a4
d0012c10:	fffff9bf 			; <UNDEFINED> instruction: 0xfffff9bf
d0012c14:	0000992e 	andeq	r9, r0, lr, lsr #18
d0012c18:	fffff980 			; <UNDEFINED> instruction: 0xfffff980
d0012c1c:	000098c8 	andeq	r9, r0, r8, asr #17
d0012c20:	fffff84c 			; <UNDEFINED> instruction: 0xfffff84c
d0012c24:	0000987c 	andeq	r9, r0, ip, ror r8
d0012c28:	00009818 	andeq	r9, r0, r8, lsl r8
d0012c2c:	fffff8ef 			; <UNDEFINED> instruction: 0xfffff8ef
d0012c30:	00009802 	andeq	r9, r0, r2, lsl #16
d0012c34:	fffff8ae 			; <UNDEFINED> instruction: 0xfffff8ae
d0012c38:	000097b6 			; <UNDEFINED> instruction: 0x000097b6
d0012c3c:	fffff8ab 			; <UNDEFINED> instruction: 0xfffff8ab
d0012c40:	00009770 	andeq	r9, r0, r0, ror r7
d0012c44:	fffff88c 			; <UNDEFINED> instruction: 0xfffff88c
d0012c48:	00009734 	andeq	r9, r0, r4, lsr r7
d0012c4c:	fffff879 			; <UNDEFINED> instruction: 0xfffff879
d0012c50:	0000970e 	andeq	r9, r0, lr, lsl #14
d0012c54:	000096f4 	strdeq	r9, [r0], -r4
d0012c58:	0000968a 	andeq	r9, r0, sl, lsl #13
d0012c5c:	00009676 	andeq	r9, r0, r6, ror r6
d0012c60:	fffff7dd 			; <UNDEFINED> instruction: 0xfffff7dd
d0012c64:	fffff7ed 			; <UNDEFINED> instruction: 0xfffff7ed
d0012c68:	00009638 	andeq	r9, r0, r8, lsr r6
d0012c6c:	00009618 	andeq	r9, r0, r8, lsl r6
d0012c70:	fffff7cc 			; <UNDEFINED> instruction: 0xfffff7cc
d0012c74:	000095fe 	strdeq	r9, [r0], -lr
d0012c78:	000095e6 	andeq	r9, r0, r6, ror #11
d0012c7c:	fffff79d 			; <UNDEFINED> instruction: 0xfffff79d
d0012c80:	000095b0 			; <UNDEFINED> instruction: 0x000095b0
d0012c84:	00009514 	andeq	r9, r0, r4, lsl r5
d0012c88:	fffff718 			; <UNDEFINED> instruction: 0xfffff718
d0012c8c:	00009502 	andeq	r9, r0, r2, lsl #10
d0012c90:	fffff6e1 			; <UNDEFINED> instruction: 0xfffff6e1
d0012c94:	000094e4 	andeq	r9, r0, r4, ror #9
d0012c98:	000094c2 	andeq	r9, r0, r2, asr #9
d0012c9c:	fffff6e9 			; <UNDEFINED> instruction: 0xfffff6e9
d0012ca0:	00009494 	muleq	r0, r4, r4
d0012ca4:	fffff6ac 			; <UNDEFINED> instruction: 0xfffff6ac
d0012ca8:	00009402 	andeq	r9, r0, r2, lsl #8
d0012cac:	fffff66d 			; <UNDEFINED> instruction: 0xfffff66d
d0012cb0:	000093d2 	ldrdeq	r9, [r0], -r2
d0012cb4:	fffff315 			; <UNDEFINED> instruction: 0xfffff315
d0012cb8:	fffff307 			; <UNDEFINED> instruction: 0xfffff307
d0012cbc:	fffff2fa 			; <UNDEFINED> instruction: 0xfffff2fa

Disassembly of section .text.advance.constprop.0:

d0012cc0 <.text.advance.constprop.0>:
d0012cc0:	4c0db570 	cfstr32mi	mvfx11, [sp], {112}	; 0x70
d0012cc4:	447cb088 	ldrbtmi	fp, [ip], #-136	; 0xffffff78
d0012cc8:	0638f104 	ldrteq	pc, [r8], -r4, lsl #2	; <UNPREDICTABLE>
d0012ccc:	0518f104 	ldreq	pc, [r8, #-260]	; 0xfffffefc
d0012cd0:	ce0f3438 	cfmvdhrgt	mvd15, r3
d0012cd4:	e896c50f 	ldm	r6, {r0, r1, r2, r3, r8, sl, lr, pc}
d0012cd8:	e885000f 	stm	r5, {r0, r1, r2, r3}
d0012cdc:	466d000f 	strbtmi	r0, [sp], -pc
d0012ce0:	f7fe4628 			; <UNDEFINED> instruction: 0xf7fe4628
d0012ce4:	cd0ffd0b 	stcgt	13, cr15, [pc, #-44]	; 0xd0012cc0
d0012ce8:	e895c40f 	ldm	r5, {r0, r1, r2, r3, sl, lr, pc}
d0012cec:	e884000f 	stm	r4, {r0, r1, r2, r3}
d0012cf0:	b008000f 	andlt	r0, r8, pc
d0012cf4:	bf00bd70 	svclt	0x0000bd70
d0012cf8:	00009216 	andeq	r9, r0, r6, lsl r2

Disassembly of section .text.accept.constprop.0:

d0012cfc <.text.accept.constprop.0>:
d0012cfc:	447a4a07 	ldrbtmi	r4, [sl], #-2567	; 0xfffff5f9
d0012d00:	6d93b508 	cfldr32vs	mvfx11, [r3, #32]
d0012d04:	6ad2b933 	bvs	0xcf4c11d8
d0012d08:	d1054282 	smlabble	r5, r2, r2, r4
d0012d0c:	ffd8f7ff 			; <UNDEFINED> instruction: 0xffd8f7ff
d0012d10:	bd082001 	stclt	0, cr2, [r8, #-4]
d0012d14:	e7fc2000 	ldrb	r2, [ip, r0]!
d0012d18:	e7fa4618 			; <UNDEFINED> instruction: 0xe7fa4618
d0012d1c:	000091de 	ldrdeq	r9, [r0], -lr

Disassembly of section .text.accept_sdk_type.constprop.0:

d0012d20 <.text.accept_sdk_type.constprop.0>:
d0012d20:	f24d4b0c 	vqdmulh.s<illegal width 8>	d20, d13, d12
d0012d24:	4602011c 			; <UNDEFINED> instruction: 0x4602011c
d0012d28:	5859447b 	ldmdapl	r9, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0012d2c:	b171b510 	cmnlt	r1, r0, lsl r5
d0012d30:	f2406adc 	vpmin.s8	q11, q8, q6
d0012d34:	428c1101 	addmi	r1, ip, #1073741824	; 0x40000000
d0012d38:	e9d3d109 	ldmib	r3, {r0, r3, r8, ip, lr, pc}^
d0012d3c:	f7fd0106 			; <UNDEFINED> instruction: 0xf7fd0106
d0012d40:	b120faaf 	msrlt	R8_usr, pc
d0012d44:	e8bd4620 	pop	{r5, r9, sl, lr}
d0012d48:	f7ff4010 			; <UNDEFINED> instruction: 0xf7ff4010
d0012d4c:	2000bfd7 	ldrdcs	fp, [r0], -r7
d0012d50:	bf00bd10 	svclt	0x0000bd10
d0012d54:	000091b4 			; <UNDEFINED> instruction: 0x000091b4

Disassembly of section .text.expect.constprop.0:

d0012d58 <.text.expect.constprop.0>:
d0012d58:	460db538 			; <UNDEFINED> instruction: 0x460db538
d0012d5c:	ffcef7ff 			; <UNDEFINED> instruction: 0xffcef7ff
d0012d60:	b9204604 	stmdblt	r0!, {r2, r9, sl, lr}
d0012d64:	f7fe4628 			; <UNDEFINED> instruction: 0xf7fe4628
d0012d68:	4620fbe7 	strtmi	pc, [r0], -r7, ror #23
d0012d6c:	2401bd38 	strcs	fp, [r1], #-3384	; 0xfffff2c8
d0012d70:	Address 0x00000000d0012d70 is out of bounds.


Disassembly of section .text.load_apicore.constprop.0:

d0012dd0 <.text.load_apicore.constprop.0>:
d0012dd0:	4ff0e92d 	svcmi	0x00f0e92d
d0012dd4:	b0894603 	addlt	r4, r9, r3, lsl #12
d0012dd8:	4891b928 	ldmmi	r1, {r3, r5, r8, fp, ip, sp, pc}
d0012ddc:	f7fe4478 			; <UNDEFINED> instruction: 0xf7fe4478
d0012de0:	2000fbab 	andcs	pc, r0, fp, lsr #23
d0012de4:	4d8fe081 	stcmi	0, cr14, [pc, #516]	; 0xd0012ff0
d0012de8:	51ecf640 	mvnpl	pc, r0, asr #12
d0012dec:	4628447d 			; <UNDEFINED> instruction: 0x4628447d
d0012df0:	28004798 	stmdacs	r0, {r3, r4, r7, r8, r9, sl, lr}
d0012df4:	f1a0d0f1 			; <UNDEFINED> instruction: 0xf1a0d0f1
d0012df8:	f6400218 			; <UNDEFINED> instruction: 0xf6400218
d0012dfc:	429a53d4 	addsmi	r5, sl, #212, 6	; 0x50000003
d0012e00:	8087f200 	addhi	pc, r7, r0, lsl #4
d0012e04:	22041f07 	andcs	r1, r4, #7, 30
d0012e08:	19e9a802 	stmibne	r9!, {r1, fp, sp, pc}^
d0012e0c:	fbaaf006 	blx	0xceacee2e
d0012e10:	46284639 			; <UNDEFINED> instruction: 0x46284639
d0012e14:	f9b0f7fd 			; <UNDEFINED> instruction: 0xf9b0f7fd
d0012e18:	42989b02 	addsmi	r9, r8, #2048	; 0x800
d0012e1c:	ac03d179 	stfged	f5, [r3], {121}	; 0x79
d0012e20:	22144629 	andscs	r4, r4, #42991616	; 0x2900000
d0012e24:	f0064620 			; <UNDEFINED> instruction: 0xf0064620
d0012e28:	497ffb9d 	ldmdbmi	pc!, {r0, r2, r3, r4, r7, r8, r9, fp, ip, sp, lr, pc}^	; <UNPREDICTABLE>
d0012e2c:	46202208 	strtmi	r2, [r0], -r8, lsl #4
d0012e30:	f0064479 			; <UNDEFINED> instruction: 0xf0064479
d0012e34:	4605fba7 	strmi	pc, [r5], -r7, lsr #23
d0012e38:	d1592800 	cmple	r9, r0, lsl #16
d0012e3c:	4b772601 	blmi	0xd1ddc648
d0012e40:	429a9a05 	addsmi	r9, sl, #20480	; 0x5000
d0012e44:	9906d165 	stmdbls	r6, {r0, r2, r5, r6, r8, ip, lr, pc}
d0012e48:	2b271e4b 	blcs	0xd09da77c
d0012e4c:	9a07d861 	bls	0xd0208fd8
d0012e50:	d85e2a28 	ldmdale	lr, {r3, r5, r9, fp, sp}^
d0012e54:	f04f2d00 			; <UNDEFINED> instruction: 0xf04f2d00
d0012e58:	bf0c0324 	svclt	0x000c0324
d0012e5c:	0a0cf04f 	beq	0xd034efa0
d0012e60:	0a08f04f 	beq	0xd024efa4
d0012e64:	2e00435a 	mcrcs	3, 0, r4, cr0, cr10, {2}
d0012e68:	0828f10a 	stmdaeq	r8!, {r1, r3, r8, ip, sp, lr, pc}
d0012e6c:	0b14f102 	bleq	0xd054f27c
d0012e70:	2314bf18 	tstcs	r4, #24, 30	; 0x60
d0012e74:	f101fb08 			; <UNDEFINED> instruction: 0xf101fb08
d0012e78:	2300bf08 	movwcs	fp, #3848	; 0xf08
d0012e7c:	445b448b 	ldrbmi	r4, [fp], #-1163	; 0xfffffb75
d0012e80:	d146429f 			; <UNDEFINED> instruction: 0xd146429f
d0012e84:	91a4f8df 	ldrdls	pc, [r4, pc]!	; <UNPREDICTABLE>
d0012e88:	4b693114 	blmi	0xd1a5f2e0
d0012e8c:	447b44f9 	ldrbtmi	r4, [fp], #-1273	; 0xfffffb07
d0012e90:	4058f509 	subsmi	pc, r8, r9, lsl #10
d0012e94:	93014419 	movwls	r4, #5145	; 0x1419
d0012e98:	f0063044 			; <UNDEFINED> instruction: 0xf0063044
d0012e9c:	9b01fb63 	blls	0xd0091c30
d0012ea0:	d1392e00 	teqle	r9, r0, lsl #28
d0012ea4:	d1642d00 	cmnle	r4, r0, lsl #26
d0012ea8:	0b0ef04f 	bleq	0xd03cefec
d0012eac:	27004d61 	strcs	r4, [r0, -r1, ror #26]
d0012eb0:	9184f8df 	ldrdls	pc, [r4, pc]
d0012eb4:	44f9447d 	ldrbtmi	r4, [r9], #1149	; 0x47d
d0012eb8:	4550f505 	ldrbmi	pc, [r0, #-1285]	; 0xfffffafb	; <UNPREDICTABLE>
d0012ebc:	9a06354c 	bls	0xd01a03f4
d0012ec0:	d35d4297 	cmple	sp, #1879048201	; 0x70000009
d0012ec4:	25004e5d 	strcs	r4, [r0, #-3677]	; 0xfffff1a3
d0012ec8:	f64d9f07 			; <UNDEFINED> instruction: 0xf64d9f07
d0012ecc:	447e0844 	ldrbtmi	r0, [lr], #-2116	; 0xfffff7bc
d0012ed0:	f04042bd 			; <UNDEFINED> instruction: 0xf04042bd
d0012ed4:	4d5a8099 	ldclmi	0, cr8, [sl, #-612]	; 0xfffffd9c
d0012ed8:	f505447d 			; <UNDEFINED> instruction: 0xf505447d
d0012edc:	cc0f4550 	cfstr32gt	mvfx4, [pc], {80}	; 0x50
d0012ee0:	c50f3510 	strgt	r3, [pc, #-1296]	; 0xd00129d8
d0012ee4:	20016823 	andcs	r6, r1, r3, lsr #16
d0012ee8:	b009602b 	andlt	r6, r9, fp, lsr #32
d0012eec:	8ff0e8bd 	svchi	0x00f0e8bd
d0012ef0:	22084954 	andcs	r4, r8, #84, 18	; 0x150000
d0012ef4:	44794620 	ldrbtmi	r4, [r9], #-1568	; 0xfffff9e0
d0012ef8:	fb44f006 	blx	0xd114ef1a
d0012efc:	d09d2800 	addsle	r2, sp, r0, lsl #16
d0012f00:	22084951 	andcs	r4, r8, #1327104	; 0x144000
d0012f04:	44794620 	ldrbtmi	r4, [r9], #-1568	; 0xfffff9e0
d0012f08:	fb3cf006 	blx	0xd0f4ef2a
d0012f0c:	28004606 	stmdacs	r0, {r1, r2, r9, sl, lr}
d0012f10:	484ed095 	stmdami	lr, {r0, r2, r4, r7, ip, lr, pc}^
d0012f14:	e7624478 			; <UNDEFINED> instruction: 0xe7624478
d0012f18:	475df509 	ldrbmi	pc, [sp, -r9, lsl #10]	; <UNPREDICTABLE>
d0012f1c:	010beb03 	tsteq	fp, r3, lsl #22
d0012f20:	37e42214 			; <UNDEFINED> instruction: 0x37e42214
d0012f24:	f0064638 			; <UNDEFINED> instruction: 0xf0064638
d0012f28:	f64dfb1d 			; <UNDEFINED> instruction: 0xf64dfb1d
d0012f2c:	f83953f4 			; <UNDEFINED> instruction: 0xf83953f4
d0012f30:	f6401003 			; <UNDEFINED> instruction: 0xf6401003
d0012f34:	1f0a73fc 	svcne	0x000a73fc
d0012f38:	d8ea429a 	stmiale	sl!, {r1, r3, r4, r7, r9, lr}^
d0012f3c:	52f6f64d 	rscspl	pc, r6, #80740352	; 0x4d00000
d0012f40:	0303f001 	movweq	pc, #12289	; 0x3001	; <UNPREDICTABLE>
d0012f44:	2002f839 	andcs	pc, r2, r9, lsr r8	; <UNPREDICTABLE>
d0012f48:	d1e24313 	mvnle	r4, r3, lsl r3
d0012f4c:	f8372204 			; <UNDEFINED> instruction: 0xf8372204
d0012f50:	f1020b02 			; <UNDEFINED> instruction: 0xf1020b02
d0012f54:	ea1c3cff 	b	0xd0722358
d0012f58:	d1da0f00 	bicsle	r0, sl, r0, lsl #30
d0012f5c:	42901a8a 	addsmi	r1, r0, #565248	; 0x8a000
d0012f60:	3301d8d7 	movwcc	sp, #6359	; 0x18d7
d0012f64:	d09d2b08 	addsle	r2, sp, r8, lsl #22
d0012f68:	bf0c2b01 	svclt	0x000c2b01
d0012f6c:	22042201 	andcs	r2, r4, #268435456	; 0x10000000
d0012f70:	2e00e7ed 	cdpcs	7, 0, cr14, cr0, cr13, {7}
d0012f74:	f04fbf14 			; <UNDEFINED> instruction: 0xf04fbf14
d0012f78:	f04f0b0d 			; <UNDEFINED> instruction: 0xf04f0b0d
d0012f7c:	e7950b0a 	ldr	r0, [r5, sl, lsl #22]
d0012f80:	0628f1a5 	strteq	pc, [r8], -r5, lsr #3
d0012f84:	f1094642 			; <UNDEFINED> instruction: 0xf1094642
d0012f88:	46300114 			; <UNDEFINED> instruction: 0x46300114
d0012f8c:	faeaf006 	blx	0xcfacefac
d0012f90:	f7fd4630 			; <UNDEFINED> instruction: 0xf7fd4630
d0012f94:	2800f96d 	stmdacs	r0, {r0, r2, r3, r5, r6, r8, fp, ip, sp, lr, pc}
d0012f98:	f815d0bb 			; <UNDEFINED> instruction: 0xf815d0bb
d0012f9c:	458a1c02 	strmi	r1, [sl, #3074]	; 0xc02
d0012fa0:	f815d3b7 			; <UNDEFINED> instruction: 0xf815d3b7
d0012fa4:	f6402c01 			; <UNDEFINED> instruction: 0xf6402c01
d0012fa8:	1f500381 	svcne	0x00500381
d0012fac:	d9012803 	stmdble	r1, {r0, r1, fp, sp}
d0012fb0:	d1ae2a0b 			; <UNDEFINED> instruction: 0xd1ae2a0b
d0012fb4:	0608f1a5 	streq	pc, [r8], -r5, lsr #3
d0012fb8:	f8362000 			; <UNDEFINED> instruction: 0xf8362000
d0012fbc:	f6402b02 			; <UNDEFINED> instruction: 0xf6402b02
d0012fc0:	45627cfc 	strbmi	r7, [r2, #-3324]!	; 0xfffff304
d0012fc4:	f012d8a5 			; <UNDEFINED> instruction: 0xf012d8a5
d0012fc8:	d1a20203 			; <UNDEFINED> instruction: 0xd1a20203
d0012fcc:	28033001 	stmdacs	r3, {r0, ip, sp}
d0012fd0:	462ed1f3 			; <UNDEFINED> instruction: 0x462ed1f3
d0012fd4:	d8054291 	stmdale	r5, {r0, r4, r7, r9, lr}
d0012fd8:	d910290b 	ldmdble	r0, {r0, r1, r3, r8, fp, sp}
d0012fdc:	35343701 	ldrcc	r3, [r4, #-1793]!	; 0xfffff8ff
d0012fe0:	e76c44c1 	strb	r4, [ip, -r1, asr #9]!
d0012fe4:	0b01f816 	bleq	0xd0091044
d0012fe8:	d804280b 	stmdale	r4, {r0, r1, r3, fp, sp}
d0012fec:	fc00fa23 	stc2	10, cr15, [r0], {35}	; 0x23	; <UNPREDICTABLE>
d0012ff0:	0f01f01c 	svceq	0x0001f01c
d0012ff4:	4558d18d 	ldrbmi	sp, [r8, #-397]	; 0xfffffe73
d0012ff8:	3201d88b 	andcc	sp, r1, #9109504	; 0x8b0000
d0012ffc:	5c6ae7ea 	stclpl	7, cr14, [sl], #-936	; 0xfffffc58
d0013000:	d1862a00 	orrle	r2, r6, r0, lsl #20
d0013004:	e7e73101 	strb	r3, [r7, r1, lsl #2]!
d0013008:	0008eb06 	andeq	lr, r8, r6, lsl #22
d001300c:	f7fd3624 			; <UNDEFINED> instruction: 0xf7fd3624
d0013010:	2800f92f 	stmdacs	r0, {r0, r1, r2, r3, r5, r8, fp, ip, sp, lr, pc}
d0013014:	af7df43f 	svcge	0x007df43f
d0013018:	e7593501 	ldrb	r3, [r9, -r1, lsl #10]
d001301c:	2001f000 	andcs	pc, r1, r0
d0013020:	ffffff92 			; <UNDEFINED> instruction: 0xffffff92
d0013024:	00008300 	andeq	r8, r0, r0, lsl #6
d0013028:	ffffff67 			; <UNDEFINED> instruction: 0xffffff67
d001302c:	00009050 	andeq	r9, r0, r0, asr r0
d0013030:	0000825e 	andeq	r8, r0, lr, asr r2
d0013034:	00009028 	andeq	r9, r0, r8, lsr #32
d0013038:	00008236 	andeq	r8, r0, r6, lsr r2
d001303c:	0000900e 	andeq	r9, r0, lr
d0013040:	00009004 	andeq	r9, r0, r4
d0013044:	fffffea9 			; <UNDEFINED> instruction: 0xfffffea9
d0013048:	fffffea1 			; <UNDEFINED> instruction: 0xfffffea1
d001304c:	fffffe9b 			; <UNDEFINED> instruction: 0xfffffe9b

Disassembly of section .text.find_function.isra.0.constprop.0:

d0013050 <.text.find_function.isra.0.constprop.0>:
d0013050:	47f0e92d 	ldrbmi	lr, [r0, sp, lsr #18]!
d0013054:	46814e14 	pkhbtmi	r4, r1, r4, lsl #28
d0013058:	2500460f 	strcs	r4, [r0, #-1551]	; 0xfffff9f1
d001305c:	f04f447e 			; <UNDEFINED> instruction: 0xf04f447e
d0013060:	f50638ff 			; <UNDEFINED> instruction: 0xf50638ff
d0013064:	f50634ba 			; <UNDEFINED> instruction: 0xf50634ba
d0013068:	34103ad2 	ldrcc	r3, [r0], #-2770	; 0xfffff52e
d001306c:	3010f8da 			; <UNDEFINED> instruction: 0x3010f8da
d0013070:	d211429d 	andsle	r4, r1, #-805306359	; 0xd0000009
d0013074:	42bb6863 	adcsmi	r6, fp, #6488064	; 0x630000
d0013078:	463ad112 			; <UNDEFINED> instruction: 0x463ad112
d001307c:	68204649 	stmdavs	r0!, {r0, r3, r6, r9, sl, lr}
d0013080:	fa80f006 	blx	0xce04f0a0
d0013084:	f894b960 			; <UNDEFINED> instruction: 0xf894b960
d0013088:	b1433028 	cmplt	r3, r8, lsr #32
d001308c:	2029f894 	mlacs	r9, r4, r8, pc	; <UNPREDICTABLE>
d0013090:	429a7a33 	addsmi	r7, sl, #208896	; 0x33000
d0013094:	46a8d104 	strtmi	sp, [r8], r4, lsl #2
d0013098:	e8bd4640 	pop	{r6, r9, sl, lr}
d001309c:	46a887f0 			; <UNDEFINED> instruction: 0x46a887f0
d00130a0:	34303501 	ldrtcc	r3, [r0], #-1281	; 0xfffffaff
d00130a4:	bf00e7e2 	svclt	0x0000e7e2
d00130a8:	00008e80 	andeq	r8, r0, r0, lsl #29

Disassembly of section .text.find_local.isra.0.constprop.0:

d00130ac <.text.find_local.isra.0.constprop.0>:
d00130ac:	4b10b5f8 	blmi	0xd0440894
d00130b0:	4607242c 	strmi	r2, [r7], -ip, lsr #8
d00130b4:	447b460e 	ldrbtmi	r4, [fp], #-1550	; 0xfffff9f2
d00130b8:	32fff503 	rscscc	pc, pc, #12582912	; 0xc00000
d00130bc:	5120f8d2 	ldrdpl	pc, [r0, -r2]!
d00130c0:	3405fb04 	strcc	pc, [r5], #-2820	; 0xfffff4fc
d00130c4:	34f9f504 	ldrbtcc	pc, [r9], #1284	; 0x504	; <UNPREDICTABLE>
d00130c8:	74faf504 	ldrbtvc	pc, [sl], #1284	; 0x504	; <UNPREDICTABLE>
d00130cc:	f04fb915 			; <UNDEFINED> instruction: 0xf04fb915
d00130d0:	e00a30ff 	strd	r3, [sl], -pc	; <UNPREDICTABLE>
d00130d4:	3d016863 	stccc	8, cr6, [r1, #-396]	; 0xfffffe74
d00130d8:	d10742b3 			; <UNDEFINED> instruction: 0xd10742b3
d00130dc:	46394632 			; <UNDEFINED> instruction: 0x46394632
d00130e0:	f0066820 			; <UNDEFINED> instruction: 0xf0066820
d00130e4:	b908fa4f 	stmdblt	r8, {r0, r1, r2, r3, r6, r9, fp, ip, sp, lr, pc}
d00130e8:	bdf84628 	ldcllt	6, cr4, [r8, #160]!	; 0xa0
d00130ec:	e7ed3c2c 	strb	r3, [sp, ip, lsr #24]!
d00130f0:	00008e26 	andeq	r8, r0, r6, lsr #28

Disassembly of section .text.add_local.constprop.0:

d0013130 <.text.add_local.constprop.0>:
d0013130:	e92db084 	push	{r2, r7, ip, sp, pc}
d0013134:	ac0847f0 	stcge	7, cr4, [r8], {240}	; 0xf0
d0013138:	000fe884 	andeq	lr, pc, r4, lsl #17
d001313c:	f8dd9909 			; <UNDEFINED> instruction: 0xf8dd9909
d0013140:	f8dd902c 			; <UNDEFINED> instruction: 0xf8dd902c
d0013144:	f89d8030 			; <UNDEFINED> instruction: 0xf89d8030
d0013148:	9d0f6038 	stcls	0, cr6, [pc, #-224]	; 0xd0013070
d001314c:	ffaef7ff 			; <UNDEFINED> instruction: 0xffaef7ff
d0013150:	db1d2800 	blle	0xd075d158
d0013154:	222c4b28 	eorcs	r4, ip, #40, 22	; 0xa000
d0013158:	fb02447b 	blx	0xd00a434e
d001315c:	f5033000 			; <UNDEFINED> instruction: 0xf5033000
d0013160:	f50032ff 			; <UNDEFINED> instruction: 0xf50032ff
d0013164:	f8d230fa 			; <UNDEFINED> instruction: 0xf8d230fa
d0013168:	f8902128 			; <UNDEFINED> instruction: 0xf8902128
d001316c:	42911040 	addsmi	r1, r1, #64	; 0x40
d0013170:	6d9cd10e 	ldfvsd	f5, [ip, #56]	; 0x38
d0013174:	d13d2c00 	teqle	sp, r0, lsl #24
d0013178:	447a4a20 	ldrbtmi	r4, [sl], #-2592	; 0xfffff5e0
d001317c:	e9c3669d 	stmib	r3, {r0, r2, r3, r4, r7, r9, sl, sp, lr}^
d0013180:	e9c32916 	stmib	r3, {r1, r2, r4, r8, fp, sp}^
d0013184:	46208618 			; <UNDEFINED> instruction: 0x46208618
d0013188:	47f0e8bd 			; <UNDEFINED> instruction: 0x47f0e8bd
d001318c:	4770b004 	ldrbmi	fp, [r0, -r4]!
d0013190:	447b4b1b 	ldrbtmi	r4, [fp], #-2843	; 0xfffff4e5
d0013194:	37fff503 	ldrbcc	pc, [pc, r3, lsl #10]!	; <UNPREDICTABLE>
d0013198:	4120f8d7 	ldrdmi	pc, [r0, -r7]!
d001319c:	d1042c40 	tstle	r4, r0, asr #24
d00131a0:	bb3c6d9c 	bllt	0xd0f2e818
d00131a4:	447a4a17 	ldrbtmi	r4, [sl], #-2583	; 0xfffff5e9
d00131a8:	222ce7e8 	eorcs	lr, ip, #232, 14	; 0x3a00000
d00131ac:	0801f104 	stmdaeq	r1, {r2, r8, ip, sp, lr, pc}
d00131b0:	2100ae08 	tstcs	r0, r8, lsl #28
d00131b4:	3304fb02 	movwcc	pc, #19202	; 0x4b02	; <UNPREDICTABLE>
d00131b8:	9128f897 	msrls	CPSR_f, r7	; <illegal shifter operand>
d00131bc:	8120f8c7 	smlawthi	r0, r7, r8, pc	; <UNPREDICTABLE>
d00131c0:	3afaf503 	bcc	0xcfed05d4
d00131c4:	0520f10a 	streq	pc, [r0, #-266]!	; 0xfffffef6
d00131c8:	f0064628 			; <UNDEFINED> instruction: 0xf0064628
d00131cc:	f88af9bd 			; <UNDEFINED> instruction: 0xf88af9bd
d00131d0:	ce0f9040 	cdpgt	0, 0, cr9, cr15, cr0, {2}
d00131d4:	e896c50f 	ldm	r6, {r0, r1, r2, r3, r8, sl, lr, pc}
d00131d8:	e885000f 	stm	r5, {r0, r1, r2, r3}
d00131dc:	f89d000f 			; <UNDEFINED> instruction: 0xf89d000f
d00131e0:	f88a3040 			; <UNDEFINED> instruction: 0xf88a3040
d00131e4:	f8d73041 			; <UNDEFINED> instruction: 0xf8d73041
d00131e8:	45983124 	ldrmi	r3, [r8, #292]	; 0x124
d00131ec:	f8c7d9cb 			; <UNDEFINED> instruction: 0xf8c7d9cb
d00131f0:	e7c88124 	strb	r8, [r8, r4, lsr #2]
d00131f4:	e7c62400 	strb	r2, [r6, r0, lsl #8]
d00131f8:	00008d84 	andeq	r8, r0, r4, lsl #27
d00131fc:	ffffff76 			; <UNDEFINED> instruction: 0xffffff76
d0013200:	00008d4a 	andeq	r8, r0, sl, asr #26
d0013204:	ffffff66 			; <UNDEFINED> instruction: 0xffffff66

Disassembly of section .text.wide_immediate:

d0013208 <.text.wide_immediate>:
d0013208:	085db530 	ldmdaeq	sp, {r4, r5, r8, sl, ip, sp, pc}^
d001320c:	3413ea41 	ldrcc	lr, [r3], #-2625	; 0xfffff5bf
d0013210:	6580f405 	strvs	pc, [r0, #1029]	; 0x405
d0013214:	011bb2d9 			; <UNDEFINED> instruction: 0x011bb2d9
d0013218:	ea41432c 	b	0xd1063ed0
d001321c:	4d0a2202 	sfmmi	f2, 4, [sl, #-8]
d0013220:	41e0f403 	mvnmi	pc, r3, lsl #8
d0013224:	447db224 	ldrbtmi	fp, [sp], #-548	; 0xfffffddc
d0013228:	4428430a 	strtmi	r4, [r8], #-778	; 0xfffffcf6
d001322c:	f880b292 			; <UNDEFINED> instruction: 0xf880b292
d0013230:	f3c44040 	vmla.i<illegal width 8>	q10, q2, d0[0]
d0013234:	f8802407 			; <UNDEFINED> instruction: 0xf8802407
d0013238:	0a122042 	beq	0xd049b348
d001323c:	4041f880 	submi	pc, r1, r0, lsl #17
d0013240:	2043f880 	subcs	pc, r3, r0, lsl #17
d0013244:	bf00bd30 	svclt	0x0000bd30
d0013248:	0002ac3e 	andeq	sl, r2, lr, lsr ip

Disassembly of section .text.emit.constprop.0:

d0013268 <.text.emit.constprop.0>:
d0013268:	447a4a0d 	ldrbtmi	r4, [sl], #-2573	; 0xfffff5f3
d001326c:	b4306d93 	ldrtlt	r6, [r0], #-3475	; 0xfffff26d
d0013270:	f64db9a3 			; <UNDEFINED> instruction: 0xf64db9a3
d0013274:	585551f8 	ldmdapl	r5, {r3, r4, r5, r6, r7, r8, ip, lr}^
d0013278:	f5b41cac 			; <UNDEFINED> instruction: 0xf5b41cac
d001327c:	d9043f80 	stmdble	r4, {r7, r8, r9, sl, fp, ip, sp}
d0013280:	bc304808 	ldclt	8, cr4, [r0], #-32	; 0xffffffe0
d0013284:	f7fe4478 			; <UNDEFINED> instruction: 0xf7fe4478
d0013288:	4b07b957 	blmi	0xd02017ec
d001328c:	447b5054 	ldrbtmi	r5, [fp], #-84	; 0xffffffac
d0013290:	f883442b 			; <UNDEFINED> instruction: 0xf883442b
d0013294:	0a000040 	beq	0xd001339c
d0013298:	0041f883 	subeq	pc, r1, r3, lsl #17
d001329c:	4770bc30 			; <UNDEFINED> instruction: 0x4770bc30
d00132a0:	00008c72 	andeq	r8, r0, r2, ror ip
d00132a4:	ffffffc4 			; <UNDEFINED> instruction: 0xffffffc4
d00132a8:	0002abd6 	ldrdeq	sl, [r2], -r6

Disassembly of section .text.load_constant.constprop.0:

d00132ac <.text.load_constant.constprop.0>:
d00132ac:	e92d29ff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, fp, sp}
d00132b0:	460541f0 			; <UNDEFINED> instruction: 0x460541f0
d00132b4:	d80a460c 	stmdale	sl, {r2, r3, r9, sl, lr}
d00132b8:	d8082807 	stmdale	r8, {r0, r1, r2, fp, sp}
d00132bc:	2000ea41 	andcs	lr, r0, r1, asr #20
d00132c0:	5000f440 	andpl	pc, r0, r0, asr #8
d00132c4:	41f0e8bd 	ldrhmi	lr, [r0, #141]!	; 0x8d
d00132c8:	f7ffb280 			; <UNDEFINED> instruction: 0xf7ffb280
d00132cc:	4a17bfcd 	bmi	0xd0603208
d00132d0:	53f8f64d 	mvnspl	pc, #80740352	; 0x4d00000
d00132d4:	447a2000 	ldrbtmi	r2, [sl], #-0
d00132d8:	f7ff58d6 			; <UNDEFINED> instruction: 0xf7ff58d6
d00132dc:	2000ffc5 	andcs	pc, r0, r5, asr #31
d00132e0:	ffc2f7ff 			; <UNDEFINED> instruction: 0xffc2f7ff
d00132e4:	3f80f5b4 	svccc	0x0080f5b4
d00132e8:	2000d305 	andcs	sp, r0, r5, lsl #6
d00132ec:	ffbcf7ff 			; <UNDEFINED> instruction: 0xffbcf7ff
d00132f0:	f7ff2000 			; <UNDEFINED> instruction: 0xf7ff2000
d00132f4:	4f0effb9 	svcmi	0x000effb9
d00132f8:	6dbb447f 	cfldrsvs	mvf4, [fp, #508]!	; 0x1fc
d00132fc:	b2a3b9a3 	adclt	fp, r3, #2670592	; 0x28c000
d0013300:	f24f462a 	vmax.s8	d20, d15, d26
d0013304:	46302140 	ldrtmi	r2, [r0], -r0, asr #2
d0013308:	ff7ef7ff 			; <UNDEFINED> instruction: 0xff7ef7ff
d001330c:	3f80f5b4 	svccc	0x0080f5b4
d0013310:	6dbbd30a 	ldcvs	3, cr13, [fp, #40]!	; 0x28
d0013314:	0c23b943 			; <UNDEFINED> instruction: 0x0c23b943
d0013318:	1d30462a 	ldcne	6, cr4, [r0, #-168]!	; 0xffffff58
d001331c:	21c0f24f 	biccs	pc, r0, pc, asr #4
d0013320:	41f0e8bd 	ldrhmi	lr, [r0, #141]!	; 0x8d
d0013324:	bf70f7ff 	svclt	0x0070f7ff
d0013328:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d001332c:	00008c06 	andeq	r8, r0, r6, lsl #24
d0013330:	00008be4 	andeq	r8, r0, r4, ror #23

Disassembly of section .text.constant.constprop.0:

d0013334 <.text.constant.constprop.0>:
d0013334:	20004601 	andcs	r4, r0, r1, lsl #12
d0013338:	bfb8f7ff 	svclt	0x00b8f7ff

Disassembly of section .text.null_argument.constprop.0:

d0013344 <.text.null_argument.constprop.0>:
d0013344:	447b4b16 	ldrbtmi	r4, [fp], #-2838	; 0xfffff4ea
d0013348:	b5136ada 	ldrlt	r6, [r3, #-2778]	; 0xfffff526
d001334c:	7181f5a2 	orrvc	pc, r1, r2, lsr #11
d0013350:	d8042901 	stmdale	r4, {r0, r8, fp, sp}
d0013354:	b1e36a1b 	mvnlt	r6, fp, lsl sl
d0013358:	b0022000 	andlt	r2, r2, r0
d001335c:	f240bd10 	vmla.f32	d27, d0, d0
d0013360:	428a1101 	addmi	r1, sl, #1073741824	; 0x40000000
d0013364:	4a0fd1f8 	bmi	0xd0407b4c
d0013368:	4106e9d3 	ldrdmi	lr, [r6, -r3]
d001336c:	4620447a 			; <UNDEFINED> instruction: 0x4620447a
d0013370:	f7fc9101 			; <UNDEFINED> instruction: 0xf7fc9101
d0013374:	9901ff95 	stmdbls	r1, {r0, r2, r4, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0013378:	d0ed2800 	rscle	r2, sp, r0, lsl #16
d001337c:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0013380:	2800fe95 	stmdacs	r0, {r0, r2, r4, r7, r9, sl, fp, ip, sp, lr, pc}
d0013384:	dae79901 	ble	0xcf9f9790
d0013388:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d001338c:	2800fb95 	stmdacs	r0, {r0, r2, r4, r7, r8, r9, fp, ip, sp, lr, pc}
d0013390:	f7ffdae2 			; <UNDEFINED> instruction: 0xf7ffdae2
d0013394:	2000fc95 	mulcs	r0, r5, ip
d0013398:	ffccf7ff 			; <UNDEFINED> instruction: 0xffccf7ff
d001339c:	e7dc2001 	ldrb	r2, [ip, r1]
d00133a0:	00008b96 	muleq	r0, r6, fp
d00133a4:	ffffffcc 			; <UNDEFINED> instruction: 0xffffffcc

Disassembly of section .text.load_local.constprop.0:

d00133a8 <.text.load_local.constprop.0>:
d00133a8:	b510281f 	ldrlt	r2, [r0, #-2079]	; 0xfffff7e1
d00133ac:	d808b284 	stmdale	r8, {r2, r7, r9, ip, sp, pc}
d00133b0:	0038f646 	eorseq	pc, r8, r6, asr #12
d00133b4:	1084ea40 	addne	lr, r4, r0, asr #20
d00133b8:	e8bdb280 	pop	{r7, r9, ip, sp, pc}
d00133bc:	f7ff4010 			; <UNDEFINED> instruction: 0xf7ff4010
d00133c0:	f64fbf53 			; <UNDEFINED> instruction: 0xf64fbf53
d00133c4:	f7ff00d7 			; <UNDEFINED> instruction: 0xf7ff00d7
d00133c8:	00a0ff4f 	adceq	pc, r0, pc, asr #30
d00133cc:	Address 0x00000000d00133cc is out of bounds.


Disassembly of section .text.store_local.constprop.0:

d00133ce <.text.store_local.constprop.0>:
d00133ce:	b538281f 	ldrlt	r2, [r8, #-2079]!	; 0xfffff7e1
d00133d2:	b285b28c 	addlt	fp, r5, #140, 4	; 0xc0000008
d00133d6:	ea44d80a 	b	0xd1149406
d00133da:	f4401085 	vst4.32	{d17-d20}, [r0], r5
d00133de:	f04040c0 			; <UNDEFINED> instruction: 0xf04040c0
d00133e2:	b2800038 	addlt	r0, r0, #56	; 0x38
d00133e6:	4038e8bd 	ldrhtmi	lr, [r8], -sp
d00133ea:	bf3df7ff 	svclt	0x003df7ff
d00133ee:	00c7f64f 	sbceq	pc, r7, pc, asr #12
d00133f2:	ff39f7ff 			; <UNDEFINED> instruction: 0xff39f7ff
d00133f6:	ea4000a8 	b	0xd101369e
d00133fa:	e7f23004 	ldrb	r3, [r2, r4]!

Disassembly of section .text.emit_address.constprop.0:

d0013424 <.text.emit_address.constprop.0>:
d0013424:	4b1cb538 	blmi	0xd074090c
d0013428:	447b4604 	ldrbtmi	r4, [fp], #-1540	; 0xfffff9fc
d001342c:	30aff503 	adccc	pc, pc, r3, lsl #10
d0013430:	f5b26802 			; <UNDEFINED> instruction: 0xf5b26802
d0013434:	d1056f00 	tstle	r5, r0, lsl #30
d0013438:	e8bd4818 	pop	{r3, r4, fp, lr}
d001343c:	44784038 	ldrbtmi	r4, [r8], #-56	; 0xffffffc8
d0013440:	b87af7fe 	ldmdalt	sl!, {r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}^
d0013444:	f5021c55 			; <UNDEFINED> instruction: 0xf5021c55
d0013448:	6005520f 	andvs	r5, r5, pc, lsl #4
d001344c:	50f8f64d 	rscspl	pc, r8, sp, asr #12
d0013450:	f8435818 			; <UNDEFINED> instruction: 0xf8435818
d0013454:	eb030032 	bl	0xd00d3524
d0013458:	200003c2 	andcs	r0, r0, r2, asr #7
d001345c:	719c8099 			; <UNDEFINED> instruction: 0x719c8099
d0013460:	ff02f7ff 			; <UNDEFINED> instruction: 0xff02f7ff
d0013464:	f7ff2000 			; <UNDEFINED> instruction: 0xf7ff2000
d0013468:	2000feff 	strdcs	pc, [r0], -pc	; <UNPREDICTABLE>
d001346c:	fefcf7ff 	mrc2	7, 7, pc, cr12, cr15, {7}
d0013470:	f7ff2000 			; <UNDEFINED> instruction: 0xf7ff2000
d0013474:	f44ffef9 			; <UNDEFINED> instruction: 0xf44ffef9
d0013478:	f7ff4022 			; <UNDEFINED> instruction: 0xf7ff4022
d001347c:	2c01fef5 	stccs	14, cr15, [r1], {245}	; 0xf5
d0013480:	2041bf0c 	subcs	fp, r1, ip, lsl #30
d0013484:	f4402000 	vst4.8	{d18-d21}, [r0], r0
d0013488:	e8bd50c0 	pop	{r6, r7, ip, lr}
d001348c:	f0404038 			; <UNDEFINED> instruction: 0xf0404038
d0013490:	f7ff0010 			; <UNDEFINED> instruction: 0xf7ff0010
d0013494:	bf00bee9 	svclt	0x0000bee9
d0013498:	00008ab2 			; <UNDEFINED> instruction: 0x00008ab2
d001349c:	ffffffbc 			; <UNDEFINED> instruction: 0xffffffbc

Disassembly of section .text.string_argument.constprop.0:

d00134e0 <.text.string_argument.constprop.0>:
d00134e0:	47ffe92d 	ldrbmi	lr, [pc, sp, lsr #18]!
d00134e4:	447b4b3a 	ldrbtmi	r4, [fp], #-2874	; 0xfffff4c6
d00134e8:	f5b26ada 			; <UNDEFINED> instruction: 0xf5b26ada
d00134ec:	d0067f82 	andle	r7, r6, r2, lsl #31
d00134f0:	44784838 	ldrbtmi	r4, [r8], #-2104	; 0xfffff7c8
d00134f4:	f820f7fe 			; <UNDEFINED> instruction: 0xf820f7fe
d00134f8:	e8bdb004 	pop	{r2, ip, sp, pc}
d00134fc:	f64d87f0 			; <UNDEFINED> instruction: 0xf64d87f0
d0013500:	f85352fc 			; <UNDEFINED> instruction: 0xf85352fc
d0013504:	f5b88002 			; <UNDEFINED> instruction: 0xf5b88002
d0013508:	d0314f80 	eorsle	r4, r1, r0, lsl #31
d001350c:	447c4c32 	ldrbtmi	r4, [ip], #-3122	; 0xfffff3ce
d0013510:	465df504 	ldrbmi	pc, [sp], -r4, lsl #10	; <UNPREDICTABLE>
d0013514:	4b3136fc 	blmi	0xd0c6110c
d0013518:	447b4f31 	ldrbtmi	r4, [fp], #-3889	; 0xfffff0cf
d001351c:	f8d3447f 			; <UNDEFINED> instruction: 0xf8d3447f
d0013520:	6a999024 	bvs	0xce6775b8
d0013524:	2030f893 	mlascs	r0, r3, r8, pc	; <UNPREDICTABLE>
d0013528:	a034f8d3 	ldrsbtge	pc, [r4], -r3	; <UNPREDICTABLE>
d001352c:	5006e9d3 	ldrdpl	lr, [r6], -r3
d0013530:	44059503 	strmi	r9, [r5], #-1283	; 0xfffffafd
d0013534:	42859803 	addmi	r9, r5, #196608	; 0x30000
d0013538:	f7ffd11d 			; <UNDEFINED> instruction: 0xf7ffd11d
d001353c:	4b29fbc1 	blmi	0xd0a92448
d0013540:	6ada447b 	bvs	0xcf6a4734
d0013544:	7f82f5b2 	svcvc	0x0082f5b2
d0013548:	6d9bd102 	ldfvsd	f5, [fp, #8]
d001354c:	d0e22b00 	rscle	r2, r2, r0, lsl #22
d0013550:	f64d4b25 			; <UNDEFINED> instruction: 0xf64d4b25
d0013554:	447b51fc 	ldrbtmi	r5, [fp], #-508	; 0xfffffe04
d0013558:	1c50585a 	mrrcne	8, 5, r5, r0, cr10
d001355c:	44135058 	ldrmi	r5, [r3], #-88	; 0xffffffa8
d0013560:	46412000 	strbmi	r2, [r1], -r0
d0013564:	435ef503 	cmpmi	lr, #12582912	; 0xc00000	; <UNPREDICTABLE>
d0013568:	f7ff7018 			; <UNDEFINED> instruction: 0xf7ff7018
d001356c:	e7c3ff5b 			; <UNDEFINED> instruction: 0xe7c3ff5b
d0013570:	4478481e 	ldrbtmi	r4, [r8], #-2078	; 0xfffff7e2
d0013574:	6833e7be 	ldmdavs	r3!, {r1, r2, r3, r4, r5, r7, r8, r9, sl, sp, lr, pc}
d0013578:	f5b33301 			; <UNDEFINED> instruction: 0xf5b33301
d001357c:	d30b4f80 	movwle	r4, #49024	; 0xbf80
d0013580:	2b006da3 	blcs	0xd002ec14
d0013584:	4b1ad1b8 	blmi	0xd06c7c6c
d0013588:	a068f8c4 	rsbge	pc, r8, r4, asr #17
d001358c:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0013590:	e9c41218 	stmib	r4, {r3, r4, r9, ip}^
d0013594:	e7af3916 			; <UNDEFINED> instruction: 0xe7af3916
d0013598:	93031c43 	movwls	r1, #15427	; 0x3c43
d001359c:	285c7800 	ldmdacs	ip, {fp, ip, sp, lr}^
d00135a0:	ab03d106 	blge	0xd01079c0
d00135a4:	95014648 	strls	r4, [r1, #-1608]	; 0xfffff9b8
d00135a8:	46539300 	ldrbmi	r9, [r3], -r0, lsl #6
d00135ac:	fe0cf7fd 	mcr2	7, 0, pc, cr12, cr13, {7}	; <UNPREDICTABLE>
d00135b0:	2b006dbb 	blcs	0xd002eca4
d00135b4:	f507d1a0 			; <UNDEFINED> instruction: 0xf507d1a0
d00135b8:	f8dc4c5d 			; <UNDEFINED> instruction: 0xf8dc4c5d
d00135bc:	f10330fc 			; <UNDEFINED> instruction: 0xf10330fc
d00135c0:	443b0e01 	ldrtmi	r0, [fp], #-3585	; 0xfffff1ff
d00135c4:	435ef503 	cmpmi	lr, #12582912	; 0xc00000	; <UNPREDICTABLE>
d00135c8:	e0fcf8cc 	rscs	pc, ip, ip, asr #17
d00135cc:	e7b17018 			; <UNDEFINED> instruction: 0xe7b17018
d00135d0:	000089f6 	strdeq	r8, [r0], -r6
d00135d4:	ffffffaa 			; <UNDEFINED> instruction: 0xffffffaa
d00135d8:	000089ce 	andeq	r8, r0, lr, asr #19
d00135dc:	000089c2 	andeq	r8, r0, r2, asr #19
d00135e0:	000089c0 	andeq	r8, r0, r0, asr #19
d00135e4:	0000899c 	muleq	r0, ip, r9
d00135e8:	00008986 	andeq	r8, r0, r6, lsl #19
d00135ec:	ffffff4d 			; <UNDEFINED> instruction: 0xffffff4d
d00135f0:	ffffff33 			; <UNDEFINED> instruction: 0xffffff33

Disassembly of section .text.function_pointer_value.constprop.0:

d0013688 <.text.function_pointer_value.constprop.0>:
d0013688:	4ff7e92d 	svcmi	0x00f7e92d
d001368c:	f7ff4605 			; <UNDEFINED> instruction: 0xf7ff4605
d0013690:	bb90fe59 	bllt	0xce452ffc
d0013694:	20264c42 	eorcs	r4, r6, r2, asr #24
d0013698:	fb30f7ff 	blx	0xd0c5169e
d001369c:	447c4941 	ldrbtmi	r4, [ip], #-2369	; 0xfffff6bf
d00136a0:	1001f240 	andne	pc, r1, r0, asr #4
d00136a4:	6b634479 	blvs	0xd18e4890
d00136a8:	9024f8d4 	ldrdls	pc, [r4], -r4	; <UNPREDICTABLE>
d00136ac:	8028f8d4 	ldrdhi	pc, [r8], -r4	; <UNPREDICTABLE>
d00136b0:	7030f894 	mlasvc	r0, r4, r8, pc	; <UNPREDICTABLE>
d00136b4:	e9d49301 	ldmib	r4, {r0, r8, r9, ip, pc}^
d00136b8:	f7ffb606 			; <UNDEFINED> instruction: 0xf7ffb606
d00136bc:	b1e0fb4d 	mvnlt	pc, sp, asr #22
d00136c0:	46584631 			; <UNDEFINED> instruction: 0x46584631
d00136c4:	fcf2f7ff 	ldc2l	7, cr15, [r2], #1020	; 0x3fc
d00136c8:	0a00f1b0 	beq	0xd004fd90
d00136cc:	232cdb31 			; <UNDEFINED> instruction: 0x232cdb31
d00136d0:	f30afb03 	vqrdmulh.s<illegal width 8>	d15, d10, d3
d00136d4:	f50118e1 			; <UNDEFINED> instruction: 0xf50118e1
d00136d8:	f89131fa 			; <UNDEFINED> instruction: 0xf89131fa
d00136dc:	2a0c2041 	bcs	0xd031b7e8
d00136e0:	4b31d00e 	blmi	0xd0c87720
d00136e4:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d00136e8:	4a30b93a 	bmi	0xd0c41bd8
d00136ec:	e9c3447a 	stmib	r3, {r1, r3, r4, r5, r6, sl, lr}^
d00136f0:	9a012916 	bls	0xd005db50
d00136f4:	8718e9c3 	ldrhi	lr, [r8, -r3, asr #19]
d00136f8:	b003669a 	mullt	r3, sl, r6
d00136fc:	8ff0e8bd 	svchi	0x00f0e8bd
d0013700:	f8917828 			; <UNDEFINED> instruction: 0xf8917828
d0013704:	42822042 	addmi	r2, r2, #66	; 0x42
d0013708:	f891d1eb 			; <UNDEFINED> instruction: 0xf891d1eb
d001370c:	78690043 	stmdavc	r9!, {r0, r1, r6}^
d0013710:	d1e64288 	mvnle	r4, r8, lsl #5
d0013714:	33faf503 	mvnscc	pc, #12582912	; 0xc00000
d0013718:	33441ca9 	movtcc	r1, #19625	; 0x4ca9
d001371c:	f00518e0 			; <UNDEFINED> instruction: 0xf00518e0
d0013720:	2800ff31 	stmdacs	r0, {r0, r4, r5, r8, r9, sl, fp, ip, sp, lr, pc}
d0013724:	4650d1dd 			; <UNDEFINED> instruction: 0x4650d1dd
d0013728:	e8bdb003 	pop	{r0, r1, ip, sp, pc}
d001372c:	f7ff4ff0 			; <UNDEFINED> instruction: 0xf7ff4ff0
d0013730:	4631be3b 			; <UNDEFINED> instruction: 0x4631be3b
d0013734:	f7ff4658 			; <UNDEFINED> instruction: 0xf7ff4658
d0013738:	f1b0fc8b 			; <UNDEFINED> instruction: 0xf1b0fc8b
d001373c:	db270a00 	blle	0xd09d5f44
d0013740:	46584631 			; <UNDEFINED> instruction: 0x46584631
d0013744:	f9b8f7fd 			; <UNDEFINED> instruction: 0xf9b8f7fd
d0013748:	da212800 	ble	0xd085d750
d001374c:	fb032330 	blx	0xd00dc416
d0013750:	18e1f30a 	stmiane	r1!, {r1, r3, r8, r9, ip, sp, lr, pc}^
d0013754:	31baf501 			; <UNDEFINED> instruction: 0x31baf501
d0013758:	2035f891 	mlascs	r5, r1, r8, pc	; <UNPREDICTABLE>
d001375c:	7828b9c2 	stmdavc	r8!, {r1, r6, r7, r8, fp, ip, sp, pc}
d0013760:	2034f891 	mlascs	r4, r1, r8, pc	; <UNPREDICTABLE>
d0013764:	d1134282 	tstle	r3, r2, lsl #5
d0013768:	0037f891 	mlaseq	r7, r1, r8, pc	; <UNPREDICTABLE>
d001376c:	42887869 	addmi	r7, r8, #6881280	; 0x690000
d0013770:	f503d10e 			; <UNDEFINED> instruction: 0xf503d10e
d0013774:	1ca933ba 	stcne	3, cr3, [r9], #744	; 0x2e8
d0013778:	18e0333a 	stmiane	r0!, {r1, r3, r4, r5, r8, r9, ip, sp}^
d001377c:	ff02f005 			; <UNDEFINED> instruction: 0xff02f005
d0013780:	4651b930 			; <UNDEFINED> instruction: 0x4651b930
d0013784:	b0032002 	andlt	r2, r3, r2
d0013788:	4ff0e8bd 	svcmi	0x00f0e8bd
d001378c:	be4af7ff 	mcrlt	7, 2, pc, cr10, cr15, {7}	; <UNPREDICTABLE>
d0013790:	447b4b07 	ldrbtmi	r4, [fp], #-2823	; 0xfffff4f9
d0013794:	2a006d9a 	bcs	0xd002ee04
d0013798:	4a06d1af 	bmi	0xd01c7e5c
d001379c:	e7a6447a 			; <UNDEFINED> instruction: 0xe7a6447a
d00137a0:	0000883e 	andeq	r8, r0, lr, lsr r8
d00137a4:	ffffff4c 			; <UNDEFINED> instruction: 0xffffff4c
d00137a8:	000087f8 	strdeq	r8, [r0], -r8	; <UNPREDICTABLE>
d00137ac:	ffffff3c 			; <UNDEFINED> instruction: 0xffffff3c
d00137b0:	0000874a 	andeq	r8, r0, sl, asr #14
d00137b4:	fffffeb4 			; <UNDEFINED> instruction: 0xfffffeb4

Disassembly of section .text.local_callback_declaration.constprop.0:

d001395c <.text.local_callback_declaration.constprop.0>:
d001395c:	e92d4959 	push	{r0, r3, r4, r6, r8, fp, lr}
d0013960:	447947f0 	ldrbtmi	r4, [r9], #-2032	; 0xfffff810
d0013964:	4607b090 			; <UNDEFINED> instruction: 0x4607b090
d0013968:	f7ff2028 			; <UNDEFINED> instruction: 0xf7ff2028
d001396c:	2800f9f5 	stmdacs	r0, {r0, r2, r4, r5, r6, r7, r8, fp, ip, sp, lr, pc}
d0013970:	80a4f000 	adchi	pc, r4, r0
d0013974:	202a4954 	eorcs	r4, sl, r4, asr r9
d0013978:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d001397c:	2800f9ed 	stmdacs	r0, {r0, r2, r3, r5, r6, r7, r8, fp, ip, sp, lr, pc}
d0013980:	809cf000 	addshi	pc, ip, r0
d0013984:	8144f8df 	ldrdhi	pc, [r4, #-143]	; 0xffffff71
d0013988:	44f8ac08 	ldrbtmi	sl, [r8], #3080	; 0xc08
d001398c:	0518f108 	ldreq	pc, [r8, #-264]	; 0xfffffef8
d0013990:	c40fcd0f 	strgt	ip, [pc], #-3343	; 0xd0013998
d0013994:	000fe895 	muleq	pc, r5, r8	; <UNPREDICTABLE>
d0013998:	000fe884 	andeq	lr, pc, r4, lsl #17
d001399c:	f240494c 	vmla.i8	q10, q0, q6
d00139a0:	ad081001 	stcge	0, cr1, [r8, #-4]
d00139a4:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d00139a8:	2800f9d7 	stmdacs	r0, {r0, r1, r2, r4, r6, r7, r8, fp, ip, sp, lr, pc}
d00139ac:	8086f000 	addhi	pc, r6, r0
d00139b0:	20294948 	eorcs	r4, r9, r8, asr #18
d00139b4:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d00139b8:	2800f9cf 	stmdacs	r0, {r0, r1, r2, r3, r6, r7, r8, fp, ip, sp, lr, pc}
d00139bc:	4946d07e 	stmdbmi	r6, {r1, r2, r3, r4, r5, r6, ip, lr, pc}^
d00139c0:	44792028 	ldrbtmi	r2, [r9], #-40	; 0xffffffd8
d00139c4:	f9c8f7ff 			; <UNDEFINED> instruction: 0xf9c8f7ff
d00139c8:	d0772800 	rsbsle	r2, r7, r0, lsl #16
d00139cc:	302cf8d8 	ldrdcc	pc, [ip], -r8	; <UNPREDICTABLE>
d00139d0:	ae062400 	cfcpysge	mvf2, mvf6
d00139d4:	7f84f5b3 	svcvc	0x0084f5b3
d00139d8:	80b49406 	adcshi	r9, r4, r6, lsl #8
d00139dc:	d14571b4 	strhle	r7, [r5, #-20]	; 0xffffffec
d00139e0:	304cf8d8 	ldrdcc	pc, [ip], #-136	; 0xffffff78
d00139e4:	d1432b29 	cmple	r3, r9, lsr #22
d00139e8:	f96af7ff 			; <UNDEFINED> instruction: 0xf96af7ff
d00139ec:	2029493b 	eorcs	r4, r9, fp, lsr r9
d00139f0:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d00139f4:	2800f9b1 	stmdacs	r0, {r0, r4, r5, r7, r8, fp, ip, sp, lr, pc}
d00139f8:	230cd060 	movwcs	sp, #49248	; 0xc060
d00139fc:	80e0f8df 	ldrdhi	pc, [r0], #143	; 0x8f	; <UNPREDICTABLE>
d0013a00:	ab109304 	blge	0xd0438618
d0013a04:	e91344f8 	ldmdb	r3, {r3, r4, r5, r6, r7, sl, lr}
d0013a08:	e88d000f 	stm	sp, {r0, r1, r2, r3}
d0013a0c:	e895000f 	ldm	r5, {r0, r1, r2, r3}
d0013a10:	f7ff000f 			; <UNDEFINED> instruction: 0xf7ff000f
d0013a14:	f8d8fb8d 			; <UNDEFINED> instruction: 0xf8d8fb8d
d0013a18:	46053058 			; <UNDEFINED> instruction: 0x46053058
d0013a1c:	d14d2b00 	cmple	sp, r0, lsl #22
d0013a20:	f88d232c 			; <UNDEFINED> instruction: 0xf88d232c
d0013a24:	22074018 	andcs	r4, r7, #24
d0013a28:	fb034631 	blx	0xd00e52f6
d0013a2c:	f88df400 			; <UNDEFINED> instruction: 0xf88df400
d0013a30:	eb087019 	bl	0xd022fa9c
d0013a34:	f5000004 			; <UNDEFINED> instruction: 0xf5000004
d0013a38:	304230fa 	strdcc	r3, [r2], #-10
d0013a3c:	fd92f005 	ldc2	0, cr15, [r2, #20]
d0013a40:	f7ff203d 			; <UNDEFINED> instruction: 0xf7ff203d
d0013a44:	b3b0f95b 	movslt	pc, #1490944	; 0x16c000
d0013a48:	30faf504 	rscscc	pc, sl, r4, lsl #10
d0013a4c:	44403042 	strbmi	r3, [r0], #-66	; 0xffffffbe
d0013a50:	fe1af7ff 	mrc2	7, 0, pc, cr10, cr15, {7}
d0013a54:	21004628 	tstcs	r0, r8, lsr #12
d0013a58:	fcb9f7ff 	ldc2	7, cr15, [r9], #1020	; 0x3fc
d0013a5c:	203b4921 	eorscs	r4, fp, r1, lsr #18
d0013a60:	b0104479 	andslt	r4, r0, r9, ror r4
d0013a64:	47f0e8bd 			; <UNDEFINED> instruction: 0x47f0e8bd
d0013a68:	b976f7ff 	ldmdblt	r6!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}^
d0013a6c:	d0bd2b29 	adcsle	r2, sp, r9, lsr #22
d0013a70:	f8df2400 			; <UNDEFINED> instruction: 0xf8df2400
d0013a74:	f10da074 			; <UNDEFINED> instruction: 0xf10da074
d0013a78:	44fa081a 	ldrbtmi	r0, [sl], #2074	; 0x81a
d0013a7c:	465146a1 	ldrbmi	r4, [r1], -r1, lsr #13
d0013a80:	1007f240 	andne	pc, r7, r0, asr #4
d0013a84:	f968f7ff 			; <UNDEFINED> instruction: 0xf968f7ff
d0013a88:	3401b1c0 	strcc	fp, [r1], #-448	; 0xfffffe40
d0013a8c:	1001f240 	andne	pc, r1, r0, asr #4
d0013a90:	9b01f808 	blls	0xd0091ab8
d0013a94:	f932f7ff 			; <UNDEFINED> instruction: 0xf932f7ff
d0013a98:	b2e4202c 	rsclt	r2, r4, #44	; 0x2c
d0013a9c:	f92ef7ff 			; <UNDEFINED> instruction: 0xf92ef7ff
d0013aa0:	d0a32800 	adcle	r2, r3, r0, lsl #16
d0013aa4:	d1ea2c05 	mvnle	r2, r5, lsl #24
d0013aa8:	44784810 	ldrbtmi	r4, [r8], #-2064	; 0xfffff7f0
d0013aac:	e8bdb010 	pop	{r4, ip, sp, pc}
d0013ab0:	f7fd47f0 			; <UNDEFINED> instruction: 0xf7fd47f0
d0013ab4:	f7ffbd41 			; <UNDEFINED> instruction: 0xf7ffbd41
d0013ab8:	e7cbfc3d 			; <UNDEFINED> instruction: 0xe7cbfc3d
d0013abc:	e8bdb010 	pop	{r4, ip, sp, pc}
d0013ac0:	bf0087f0 	svclt	0x000087f0
d0013ac4:	fffffe52 			; <UNDEFINED> instruction: 0xfffffe52
d0013ac8:	fffffe69 			; <UNDEFINED> instruction: 0xfffffe69
d0013acc:	00008552 	andeq	r8, r0, r2, asr r5
d0013ad0:	fffffe6a 			; <UNDEFINED> instruction: 0xfffffe6a
d0013ad4:	fffffe82 			; <UNDEFINED> instruction: 0xfffffe82
d0013ad8:	fffffea1 			; <UNDEFINED> instruction: 0xfffffea1
d0013adc:	ffffff06 			; <UNDEFINED> instruction: 0xffffff06
d0013ae0:	000084d8 	ldrdeq	r8, [r0], -r8	; <UNPREDICTABLE>
d0013ae4:	fffffec5 			; <UNDEFINED> instruction: 0xfffffec5
d0013ae8:	fffffe4d 			; <UNDEFINED> instruction: 0xfffffe4d
d0013aec:	fffffdee 			; <UNDEFINED> instruction: 0xfffffdee

Disassembly of section .text.branch.constprop.0:

d0013af0 <.text.branch.constprop.0>:
d0013af0:	f64d4b06 			; <UNDEFINED> instruction: 0xf64d4b06
d0013af4:	200052f8 	strdcs	r5, [r0], -r8
d0013af8:	b510447b 	ldrlt	r4, [r0, #-1147]	; 0xfffffb85
d0013afc:	f7ff589c 			; <UNDEFINED> instruction: 0xf7ff589c
d0013b00:	2000fbb3 			; <UNDEFINED> instruction: 0x2000fbb3
d0013b04:	fbb0f7ff 	blx	0xcec51b0a
d0013b08:	bd104620 	ldclt	6, cr4, [r0, #-128]	; 0xffffff80
d0013b0c:	000083e4 	andeq	r8, r0, r4, ror #7

Disassembly of section .text.branch_on_value.constprop.0:

d0013b10 <.text.branch_on_value.constprop.0>:
d0013b10:	4604b510 			; <UNDEFINED> instruction: 0x4604b510
d0013b14:	5020f44f 	eorpl	pc, r0, pc, asr #8
d0013b18:	fba6f7ff 	blx	0xce9d1b1e
d0013b1c:	1301f24d 	movwne	pc, #4685	; 0x124d	; <UNPREDICTABLE>
d0013b20:	0001f24d 	andeq	pc, r1, sp, asr #4
d0013b24:	bf082c00 	svclt	0x00082c00
d0013b28:	f7ff4618 			; <UNDEFINED> instruction: 0xf7ff4618
d0013b2c:	e8bdfb9d 	pop	{r0, r2, r3, r4, r7, r8, r9, fp, ip, sp, lr, pc}
d0013b30:	f7ff4010 			; <UNDEFINED> instruction: 0xf7ff4010
d0013b34:	Address 0x00000000d0013b34 is out of bounds.


Disassembly of section .text.boolean.constprop.0:

d0013b36 <.text.boolean.constprop.0>:
d0013b36:	f24db508 	vrshl.s8	d27, d8, d13
d0013b3a:	ea430301 	b	0xd10d4746
d0013b3e:	b2802000 	addlt	r2, r0, #0
d0013b42:	fb91f7ff 	blx	0xce491b48
d0013b46:	5000f44f 	andpl	pc, r0, pc, asr #8
d0013b4a:	fb8df7ff 	blx	0xce391b50
d0013b4e:	4060f44f 	rsbmi	pc, r0, pc, asr #8
d0013b52:	fb89f7ff 	blx	0xce291b58
d0013b56:	0001f242 	andeq	pc, r1, r2, asr #4
d0013b5a:	4008e8bd 			; <UNDEFINED> instruction: 0x4008e8bd
d0013b5e:	bb83f7ff 	bllt	0xce111b62

Disassembly of section .text.prepare_call.constprop.0:

d0013b62 <.text.prepare_call.constprop.0>:
d0013b62:	e92d2804 	push	{r2, fp, sp}
d0013b66:	460541f0 			; <UNDEFINED> instruction: 0x460541f0
d0013b6a:	2504bf38 	strcs	fp, [r4, #-3896]	; 0xfffff0c8
d0013b6e:	3d034604 	stccc	6, cr4, [r3, #-16]
d0013b72:	0501f035 	streq	pc, [r1, #-53]	; 0xffffffcb
d0013b76:	f445d006 	vst4.8	{d29-d32}, [r5], r6
d0013b7a:	f0404030 			; <UNDEFINED> instruction: 0xf0404030
d0013b7e:	b2800080 	addlt	r0, r0, #128	; 0x80
d0013b82:	fb71f7ff 	blx	0xd1c91b88
d0013b86:	f04f1f66 			; <UNDEFINED> instruction: 0xf04f1f66
d0013b8a:	00770804 	rsbseq	r0, r7, r4, lsl #16
d0013b8e:	0646eb05 	strbeq	lr, [r6], -r5, lsl #22
d0013b92:	4544b2b6 	strbmi	fp, [r4, #-694]	; 0xfffffd4a
d0013b96:	f107d80a 			; <UNDEFINED> instruction: 0xf107d80a
d0013b9a:	27000608 	strcs	r0, [r0, -r8, lsl #12]
d0013b9e:	b2b6442e 	adcslt	r4, r6, #771751936	; 0x2e000000
d0013ba2:	d02142bc 	strhtle	r4, [r1], -ip
d0013ba6:	d1112f04 	tstle	r1, r4, lsl #30
d0013baa:	e025b9fd 	strd	fp, [r5], -sp	; <UNPREDICTABLE>
d0013bae:	4018f446 	andsmi	pc, r8, r6, asr #8
d0013bb2:	f7ff3e02 			; <UNDEFINED> instruction: 0xf7ff3e02
d0013bb6:	f1a8fb58 			; <UNDEFINED> instruction: 0xf1a8fb58
d0013bba:	b2b60004 	adcslt	r0, r6, #4
d0013bbe:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d0013bc2:	4010f440 	andsmi	pc, r0, r0, asr #8
d0013bc6:	f7ffb280 			; <UNDEFINED> instruction: 0xf7ffb280
d0013bca:	e7e2fb4e 	strb	pc, [r2, lr, asr #22]!	; <UNPREDICTABLE>
d0013bce:	3701b2bb 			; <UNDEFINED> instruction: 0x3701b2bb
d0013bd2:	30c3ebc3 	sbccc	lr, r3, r3, asr #23
d0013bd6:	0040eb06 	subeq	lr, r0, r6, lsl #22
d0013bda:	2003ea40 	andcs	lr, r3, r0, asr #20
d0013bde:	4018f440 	andsmi	pc, r8, r0, asr #8
d0013be2:	f7ffb280 			; <UNDEFINED> instruction: 0xf7ffb280
d0013be6:	e7dbfb40 	ldrb	pc, [fp, r0, asr #22]	; <UNPREDICTABLE>
d0013bea:	eb05b125 	bl	0xd0180086
d0013bee:	46200444 	strtmi	r0, [r0], -r4, asr #8
d0013bf2:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d0013bf6:	d0fa2c00 	rscsle	r2, sl, r0, lsl #24
d0013bfa:	24000060 	strcs	r0, [r0], #-96	; 0xffffffa0
d0013bfe:	4030f440 	eorsmi	pc, r0, r0, asr #8
d0013c02:	f7ffb280 			; <UNDEFINED> instruction: 0xf7ffb280
d0013c06:	e7f2fb30 			; <UNDEFINED> instruction: 0xe7f2fb30

Disassembly of section .text.binary.constprop.0:

d0013c0a <.text.binary.constprop.0>:
d0013c0a:	b538282f 	ldrlt	r2, [r8, #-2095]!	; 0xfffff7d1
d0013c0e:	460c4605 	strmi	r4, [ip], -r5, lsl #12
d0013c12:	2824dc0d 	stmdacs	r4!, {r0, r2, r3, sl, fp, ip, lr, pc}
d0013c16:	f1a0dd0f 			; <UNDEFINED> instruction: 0xf1a0dd0f
d0013c1a:	2b0a0325 	blcs	0xd02948b6
d0013c1e:	e8dfd80b 	ldm	pc, {r0, r1, r3, fp, ip, lr, pc}^	; <UNPREDICTABLE>
d0013c22:	2338f003 	teqcs	r8, #3	; <UNPREDICTABLE>
d0013c26:	200a0a0a 	andcs	r0, sl, sl, lsl #20
d0013c2a:	0a490a1a 	beq	0xd125649a
d0013c2e:	285e002c 	ldmdacs	lr, {r2, r3, r5}^
d0013c32:	287cd020 	ldmdacs	ip!, {r5, ip, lr, pc}^
d0013c36:	f244d01b 	vqadd.s8	d29, d4, d11
d0013c3a:	f7ff2081 			; <UNDEFINED> instruction: 0xf7ff2081
d0013c3e:	f5b5fb14 			; <UNDEFINED> instruction: 0xf5b5fb14
d0013c42:	dc067f8d 	stcle	15, cr7, [r6], {141}	; 0x8d
d0013c46:	7f8bf5b5 	svcvc	0x008bf5b5
d0013c4a:	2d3cdc37 	ldccs	12, cr13, [ip, #-220]!	; 0xffffff24
d0013c4e:	2d3ed048 	ldccs	0, cr13, [lr, #-288]!	; 0xfffffee0
d0013c52:	2400d04b 	strcs	sp, [r0], #-75	; 0xffffffb5
d0013c56:	f641e003 			; <UNDEFINED> instruction: 0xf641e003
d0013c5a:	f7ff0008 			; <UNDEFINED> instruction: 0xf7ff0008
d0013c5e:	4620fb04 	strtmi	pc, [r0], -r4, lsl #22
d0013c62:	f244bd38 	vmla.f32	d27, d4, d24
d0013c66:	e7f83048 	ldrb	r3, [r8, r8, asr #32]!
d0013c6a:	0008f244 	andeq	pc, r8, r4, asr #4
d0013c6e:	f244e7f5 	vaba.s8	q15, q10, <illegal reg q10.5>
d0013c72:	e7f23008 	ldrb	r3, [r2, r8]!
d0013c76:	0048f244 	subeq	pc, r8, r4, asr #4
d0013c7a:	f64fe7ef 			; <UNDEFINED> instruction: 0xf64fe7ef
d0013c7e:	f64f3391 			; <UNDEFINED> instruction: 0xf64f3391
d0013c82:	290030b1 	stmdbcs	r0, {r0, r4, r5, r7, ip, sp}
d0013c86:	4618bf08 	ldrmi	fp, [r8], -r8, lsl #30
d0013c8a:	faedf7ff 	blx	0xcfb91c8e
d0013c8e:	00f0f24f 	rscseq	pc, r0, pc, asr #4
d0013c92:	f64fe7e3 			; <UNDEFINED> instruction: 0xf64fe7e3
d0013c96:	f64f3391 			; <UNDEFINED> instruction: 0xf64f3391
d0013c9a:	290030b1 	stmdbcs	r0, {r0, r4, r5, r7, ip, sp}
d0013c9e:	4618bf08 	ldrmi	fp, [r8], -r8, lsl #30
d0013ca2:	fae1f7ff 	blx	0xcf891ca6
d0013ca6:	20f0f24f 	rscscs	pc, r0, pc, asr #4
d0013caa:	faddf7ff 	blx	0xcf791cae
d0013cae:	3050f244 	subscc	pc, r0, r4, asr #4
d0013cb2:	fad9f7ff 	blx	0xcf691cb6
d0013cb6:	2008f641 	andcs	pc, r8, r1, asr #12
d0013cba:	f5a5e7cf 			; <UNDEFINED> instruction: 0xf5a5e7cf
d0013cbe:	2d02758c 	cfstr32cs	mvfx7, [r2, #-560]	; 0xfffffdd0
d0013cc2:	e8dfd803 	ldm	pc, {r0, r1, fp, ip, lr, pc}^	; <UNPREDICTABLE>
d0013cc6:	1706f005 	strne	pc, [r6, -r5]
d0013cca:	20000008 	andcs	r0, r0, r8
d0013cce:	ff32f7ff 			; <UNDEFINED> instruction: 0xff32f7ff
d0013cd2:	2001e7bf 			; <UNDEFINED> instruction: 0x2001e7bf
d0013cd6:	2c00e7fa 	stccs	7, cr14, [r0], {250}	; 0xfa
d0013cda:	2002bf14 	andcs	fp, r2, r4, lsl pc
d0013cde:	e7f5200a 	ldrb	r2, [r5, sl]!
d0013ce2:	bf142c00 	svclt	0x00142c00
d0013ce6:	200b2003 	andcs	r2, fp, r3
d0013cea:	2c00e7f0 	stccs	7, cr14, [r0], {240}	; 0xf0
d0013cee:	2008bf14 	andcs	fp, r8, r4, lsl pc
d0013cf2:	e7eb200c 	strb	r2, [fp, ip]!
d0013cf6:	bf142c00 	svclt	0x00142c00
d0013cfa:	200d2009 	andcs	r2, sp, r9
d0013cfe:	Address 0x00000000d0013cfe is out of bounds.


Disassembly of section .text.increment_scalar.isra.0.constprop.0:

d0013d2c <.text.increment_scalar.isra.0.constprop.0>:
d0013d2c:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d0013d30:	802cf8dd 	ldrdhi	pc, [ip], -sp	; <UNPREDICTABLE>
d0013d34:	460e4604 	strmi	r4, [lr], -r4, lsl #12
d0013d38:	46994617 			; <UNDEFINED> instruction: 0x46994617
d0013d3c:	f9b6f7ff 			; <UNDEFINED> instruction: 0xf9b6f7ff
d0013d40:	da741e05 	ble	0xd1d1b55c
d0013d44:	46204631 			; <UNDEFINED> instruction: 0x46204631
d0013d48:	feb6f7fc 	mrc2	7, 5, pc, cr6, cr12, {7}
d0013d4c:	db1b1e06 	blle	0xd06db56c
d0013d50:	222c4b3d 	eorcs	r4, ip, #62464	; 0xf400
d0013d54:	fb02447b 	blx	0xd00a4f4a
d0013d58:	f5033306 			; <UNDEFINED> instruction: 0xf5033306
d0013d5c:	f89333af 			; <UNDEFINED> instruction: 0xf89333af
d0013d60:	1ea2402c 	cdpne	0, 10, cr4, cr2, cr12, {1}
d0013d64:	d8042a0a 	stmdale	r4, {r1, r3, r9, fp, sp}
d0013d68:	63f5f240 	mvnsvs	pc, #64, 4
d0013d6c:	07da40d3 			; <UNDEFINED> instruction: 0x07da40d3
d0013d70:	2d00d40a 	cfstrscs	mvf13, [r0, #-40]	; 0xffffffd8
d0013d74:	4631da1a 			; <UNDEFINED> instruction: 0x4631da1a
d0013d78:	f7ff2001 			; <UNDEFINED> instruction: 0xf7ff2001
d0013d7c:	f646fb53 			; <UNDEFINED> instruction: 0xf646fb53
d0013d80:	f7ff0008 			; <UNDEFINED> instruction: 0xf7ff0008
d0013d84:	e014fa71 	ands	pc, r4, r1, ror sl	; <UNPREDICTABLE>
d0013d88:	44794930 	ldrbtmi	r4, [r9], #-2352	; 0xfffff6d0
d0013d8c:	28006d88 	stmdacs	r0, {r3, r7, r8, sl, fp, sp, lr}
d0013d90:	4b2fd149 	blmi	0xd0c082bc
d0013d94:	9060f8c1 	rsbls	pc, r0, r1, asr #17
d0013d98:	e9c1447b 	stmib	r1, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0013d9c:	f89d3716 			; <UNDEFINED> instruction: 0xf89d3716
d0013da0:	664b3020 	strbvs	r3, [fp], -r0, lsr #32
d0013da4:	668b9b09 	strvs	r9, [fp], r9, lsl #22
d0013da8:	83f8e8bd 	mvnshi	lr, #12386304	; 0xbd0000
d0013dac:	f7ff4628 			; <UNDEFINED> instruction: 0xf7ff4628
d0013db0:	f1b8fafb 			; <UNDEFINED> instruction: 0xf1b8fafb
d0013db4:	d0030f00 	andle	r0, r3, r0, lsl #30
d0013db8:	4001f24b 	andmi	pc, r1, fp, asr #4
d0013dbc:	fa54f7ff 	blx	0xd1551dc0
d0013dc0:	f5b39b0a 			; <UNDEFINED> instruction: 0xf5b39b0a
d0013dc4:	bf077f8f 	svclt	0x00077f8f
d0013dc8:	0004f243 	andeq	pc, r4, r3, asr #4
d0013dcc:	0301f243 	movweq	pc, #4675	; 0x1243	; <UNPREDICTABLE>
d0013dd0:	0004f643 	andeq	pc, r4, r3, asr #12
d0013dd4:	0301f643 	movweq	pc, #5699	; 0x1643	; <UNPREDICTABLE>
d0013dd8:	bf182c0a 	svclt	0x00182c0a
d0013ddc:	f7ff4618 			; <UNDEFINED> instruction: 0xf7ff4618
d0013de0:	2c05fa43 			; <UNDEFINED> instruction: 0x2c05fa43
d0013de4:	f24bd103 	vrhadd.s8	d29, d11, d3
d0013de8:	f7ff20c0 			; <UNDEFINED> instruction: 0xf7ff20c0
d0013dec:	2d00fa3d 	vstrcs	s30, [r0, #-244]	; 0xffffff0c
d0013df0:	2100db10 	tstcs	r0, r0, lsl fp
d0013df4:	f7ff4628 			; <UNDEFINED> instruction: 0xf7ff4628
d0013df8:	f1b8faea 			; <UNDEFINED> instruction: 0xf1b8faea
d0013dfc:	d0030f00 	andle	r0, r3, r0, lsl #30
d0013e00:	4001f64b 	andmi	pc, r1, fp, asr #12
d0013e04:	fa30f7ff 	blx	0xd0c51e08
d0013e08:	d00e2c0a 	andle	r2, lr, sl, lsl #24
d0013e0c:	42581e63 	subsmi	r1, r8, #1584	; 0x630
d0013e10:	e7c94158 			; <UNDEFINED> instruction: 0xe7c94158
d0013e14:	20014631 	andcs	r4, r1, r1, lsr r6
d0013e18:	fb04f7ff 	blx	0xd0151e1e
d0013e1c:	0008f246 	andeq	pc, r8, r6, asr #4
d0013e20:	fa22f7ff 	blx	0xd08d1e24
d0013e24:	2000e7e9 	andcs	lr, r0, r9, ror #15
d0013e28:	2004e7be 			; <UNDEFINED> instruction: 0x2004e7be
d0013e2c:	4b09e7bc 	blmi	0xd028dd24
d0013e30:	f04f222c 			; <UNDEFINED> instruction: 0xf04f222c
d0013e34:	447b36ff 	ldrbtmi	r3, [fp], #-1791	; 0xfffff901
d0013e38:	3305fb02 	movwcc	pc, #23298	; 0x5b02	; <UNPREDICTABLE>
d0013e3c:	33faf503 	mvnscc	pc, #12582912	; 0xc00000
d0013e40:	4041f893 	umaalmi	pc, r1, r3, r8	; <UNPREDICTABLE>
d0013e44:	bf00e78d 	svclt	0x0000e78d
d0013e48:	00008188 	andeq	r8, r0, r8, lsl #3
d0013e4c:	00008152 	andeq	r8, r0, r2, asr r1
d0013e50:	ffffff64 			; <UNDEFINED> instruction: 0xffffff64
d0013e54:	000080a6 	andeq	r8, r0, r6, lsr #1

Disassembly of section .text.patch_branch.isra.0.part.0:

d0013e58 <.text.patch_branch.isra.0.part.0>:
d0013e58:	2a001a09 	bcs	0xd001a684
d0013e5c:	0104f1a1 	smlatbeq	r4, r1, r1, pc	; <UNPREDICTABLE>
d0013e60:	f44fbf14 			; <UNDEFINED> instruction: 0xf44fbf14
d0013e64:	f44f4250 	vst1.16	{d20-d23}, [pc :64], r0
d0013e68:	b5f04210 	ldrblt	r4, [r0, #528]!	; 0x210
d0013e6c:	6600f3c1 	strvs	pc, [r0], -r1, asr #7
d0013e70:	3409f3c1 	strcc	pc, [r9], #-961	; 0xfffffc3f
d0013e74:	ea864f11 	b	0xce1a7ac0
d0013e78:	ea4453d1 	b	0xd1128dc4
d0013e7c:	447f2486 	ldrbtmi	r2, [pc], #-1158	; 0xd0013e84
d0013e80:	f44443db 	vst2.<illegal width 64>	{d20-d23}, [r4 :64], fp
d0013e84:	f0034470 			; <UNDEFINED> instruction: 0xf0034470
d0013e88:	ea860501 	b	0xce195294
d0013e8c:	f3c15391 	vrsra.u64	d21, d1, #63
d0013e90:	183e014a 	ldmdane	lr!, {r1, r3, r6, r8}
d0013e94:	f88643db 			; <UNDEFINED> instruction: 0xf88643db
d0013e98:	0a244040 	beq	0xd0923fa0
d0013e9c:	0301f003 	movweq	pc, #4099	; 0x1003	; <UNPREDICTABLE>
d0013ea0:	4041f886 	submi	pc, r1, r6, lsl #17
d0013ea4:	ea4302db 	b	0xd10d4a18
d0013ea8:	430b3345 	movwmi	r3, #45893	; 0xb345
d0013eac:	f8864313 			; <UNDEFINED> instruction: 0xf8864313
d0013eb0:	0a1b3042 	beq	0xd06dffc0
d0013eb4:	3043f886 	subcc	pc, r3, r6, lsl #17
d0013eb8:	bf00bdf0 	svclt	0x0000bdf0
d0013ebc:	00029fe6 	andeq	r9, r2, r6, ror #31

Disassembly of section .text.patch_branch.isra.0:

d0013ec0 <.text.patch_branch.isra.0>:
d0013ec0:	4604b410 			; <UNDEFINED> instruction: 0x4604b410
d0013ec4:	46114608 	ldrmi	r4, [r1], -r8, lsl #12
d0013ec8:	b91c461a 	ldmdblt	ip, {r1, r3, r4, r9, sl, lr}
d0013ecc:	4b04f85d 	blmi	0xd0152048
d0013ed0:	bfc2f7ff 	svclt	0x00c2f7ff
d0013ed4:	4b04f85d 	blmi	0xd0152050
d0013ed8:	Address 0x00000000d0013ed8 is out of bounds.


Disassembly of section .text.unary.constprop.0:

d0014434 <.text.unary.constprop.0>:
d0014434:	4ff0e92d 	svcmi	0x00f0e92d
d0014438:	ac94f8df 	ldcge	8, cr15, [r4], {223}	; 0xdf
d001443c:	44fa4681 	ldrbtmi	r4, [sl], #1665	; 0x681
d0014440:	8b02ed2d 	blhi	0xd00cf8fc
d0014444:	2058f8da 	ldrsbcs	pc, [r8], #-138	; 0xffffff76	; <UNPREDICTABLE>
d0014448:	9207b08d 	andls	fp, r7, #141	; 0x8d
d001444c:	f0402a00 			; <UNDEFINED> instruction: 0xf0402a00
d0014450:	f8da85fc 			; <UNDEFINED> instruction: 0xf8da85fc
d0014454:	f89a3034 			; <UNDEFINED> instruction: 0xf89a3034
d0014458:	93058030 	movwls	r8, #20528	; 0x5030
d001445c:	33fff50a 	mvnscc	pc, #41943040	; 0x2800000
d0014460:	012cf8d3 	ldrdeq	pc, [ip, -r3]!
d0014464:	30019306 	andcc	r9, r1, r6, lsl #6
d0014468:	f8c32820 			; <UNDEFINED> instruction: 0xf8c32820
d001446c:	e9da012c 	ldmib	sl, {r2, r3, r5, r8}^
d0014470:	e9da5106 	ldmib	sl, {r1, r2, r8, ip, lr}^
d0014474:	e9dab608 	ldmib	sl, {r3, r9, sl, ip, sp, pc}^
d0014478:	d907740a 	stmdble	r7, {r1, r3, sl, ip, sp, lr}
d001447c:	0c54f8df 	mrrceq	8, 13, pc, r4, cr15	; <UNPREDICTABLE>
d0014480:	f7fd4478 			; <UNDEFINED> instruction: 0xf7fd4478
d0014484:	f04ff859 			; <UNDEFINED> instruction: 0xf04ff859
d0014488:	e0110b00 	ands	r0, r1, r0, lsl #22
d001448c:	7081f44f 	addvc	pc, r1, pc, asr #8
d0014490:	f7fe9107 			; <UNDEFINED> instruction: 0xf7fe9107
d0014494:	9907fc33 	stmdbls	r7, {r0, r1, r4, r5, sl, fp, ip, sp, lr, pc}
d0014498:	4658b1b0 			; <UNDEFINED> instruction: 0x4658b1b0
d001449c:	ff4af7fe 			; <UNDEFINED> instruction: 0xff4af7fe
d00144a0:	1003f240 	andne	pc, r3, r0, asr #4
d00144a4:	bf144284 	svclt	0x00144284
d00144a8:	0b00f04f 	bleq	0xd00505ec
d00144ac:	0b01f04f 	bleq	0xd00905f0
d00144b0:	3c24f8df 	stccc	8, cr15, [r4], #-892	; 0xfffffc84
d00144b4:	447b4658 	ldrbtmi	r4, [fp], #-1624	; 0xfffff9a8
d00144b8:	33fff503 	mvnscc	pc, #12582912	; 0xc00000
d00144bc:	212cf8d3 	ldrdcs	pc, [ip, -r3]!
d00144c0:	f8c33a01 			; <UNDEFINED> instruction: 0xf8c33a01
d00144c4:	e091212c 	adds	r2, r1, ip, lsr #2
d00144c8:	1003f240 	andne	pc, r3, r0, asr #4
d00144cc:	f7fe9107 			; <UNDEFINED> instruction: 0xf7fe9107
d00144d0:	2800fc15 	stmdacs	r0, {r0, r2, r4, sl, fp, ip, sp, lr, pc}
d00144d4:	f44fd1e1 	vst4.<illegal width 64>	{d29,d31,d33,d35}, [pc :128], r1
d00144d8:	f7fe708f 			; <UNDEFINED> instruction: 0xf7fe708f
d00144dc:	9907fc0f 	stmdbls	r7, {r0, r1, r2, r3, sl, fp, ip, sp, lr, pc}
d00144e0:	f8dfb308 			; <UNDEFINED> instruction: 0xf8dfb308
d00144e4:	f2405bf8 	vpadd.i8	<illegal reg q10.5>, q8, q12
d00144e8:	f8df1001 			; <UNDEFINED> instruction: 0xf8df1001
d00144ec:	447d1bf4 	ldrbtmi	r1, [sp], #-3060	; 0xfffff40c
d00144f0:	6a6a4479 	bvs	0xd1aa56dc
d00144f4:	f8956aab 			; <UNDEFINED> instruction: 0xf8956aab
d00144f8:	f8d58030 			; <UNDEFINED> instruction: 0xf8d58030
d00144fc:	92069034 	andls	r9, r6, #52	; 0x34
d0014500:	e9d59305 	ldmib	r5, {r0, r2, r8, r9, ip, pc}^
d0014504:	f7fe6706 			; <UNDEFINED> instruction: 0xf7fe6706
d0014508:	2800fc27 	stmdacs	r0, {r0, r1, r2, r5, sl, fp, ip, sp, lr, pc}
d001450c:	2100d067 	tstcs	r0, r7, rrx
d0014510:	9a069b05 	bls	0xd01bb12c
d0014514:	91034630 	tstls	r3, r0, lsr r6
d0014518:	94024639 	strls	r4, [r2], #-1593	; 0xfffff9c7
d001451c:	8900e9cd 	stmdbhi	r0, {r0, r2, r3, r6, r7, r8, fp, sp, lr, pc}
d0014520:	fc04f7ff 	stc2	7, cr15, [r4], {255}	; 0xff
d0014524:	f240e059 	vqadd.s8	q15, q0, <illegal reg q4.5>
d0014528:	9107101f 	tstls	r7, pc, lsl r0
d001452c:	fbe6f7fe 	blx	0xcf9d252e
d0014530:	28009907 	stmdacs	r0, {r0, r1, r2, r8, fp, ip, pc}
d0014534:	f240d1d5 	vand	<illegal reg q14.5>, q8, <illegal reg q2.5>
d0014538:	91071001 	tstls	r7, r1
d001453c:	fbdef7fe 	blx	0xcf7d253e
d0014540:	28004683 	stmdacs	r0, {r0, r1, r7, r9, sl, lr}
d0014544:	8435f000 	ldrthi	pc, [r5], #-0	; <UNPREDICTABLE>
d0014548:	f7fe2028 			; <UNDEFINED> instruction: 0xf7fe2028
d001454c:	9907fbd7 	stmdbls	r7, {r0, r1, r2, r4, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d0014550:	28004683 	stmdacs	r0, {r0, r1, r7, r9, sl, lr}
d0014554:	82fcf000 	rscshi	pc, ip, #0
d0014558:	91064628 	tstls	r6, r8, lsr #12
d001455c:	fda6f7fe 	stc2	7, cr15, [r6, #1016]!	; 0x3f8
d0014560:	99062800 	stmdbls	r6, {fp, sp}
d0014564:	222cdb08 	eorcs	sp, ip, #8, 22	; 0x2000
d0014568:	a300fb02 	movwge	pc, #2818	; 0xb02	; <UNPREDICTABLE>
d001456c:	33faf503 	mvnscc	pc, #12582912	; 0xc00000
d0014570:	3041f893 	umaalcc	pc, r1, r3, r8	; <UNPREDICTABLE>
d0014574:	d03e2b0c 	eorsle	r2, lr, ip, lsl #22
d0014578:	3b68f8df 	blcc	0xd1a528fc
d001457c:	0a00f04f 	beq	0xd00506c0
d0014580:	f503447b 			; <UNDEFINED> instruction: 0xf503447b
d0014584:	461c4b50 			; <UNDEFINED> instruction: 0x461c4b50
d0014588:	f24d9307 	vcgt.s8	d25, d13, d7
d001458c:	f10b0324 			; <UNDEFINED> instruction: 0xf10b0324
d0014590:	f8db0b1c 			; <UNDEFINED> instruction: 0xf8db0b1c
d0014594:	45922000 	ldrmi	r2, [r2]
d0014598:	4628d33f 			; <UNDEFINED> instruction: 0x4628d33f
d001459c:	f7fe9106 			; <UNDEFINED> instruction: 0xf7fe9106
d00145a0:	f1b0fd57 			; <UNDEFINED> instruction: 0xf1b0fd57
d00145a4:	99060a00 	stmdbls	r6, {r9, fp}
d00145a8:	4628db07 	strtmi	sp, [r8], -r7, lsl #22
d00145ac:	f7fe9106 			; <UNDEFINED> instruction: 0xf7fe9106
d00145b0:	2800fd7d 	stmdacs	r0, {r0, r2, r3, r4, r5, r6, r8, sl, fp, ip, sp, lr, pc}
d00145b4:	f2c09906 	vqdmlal.s<illegal width 8>	<illegal reg q12.5>, d0, d6
d00145b8:	f8df81fd 			; <UNDEFINED> instruction: 0xf8df81fd
d00145bc:	447b3b2c 	ldrbtmi	r3, [fp], #-2860	; 0xfffff4d4
d00145c0:	28006d98 	stmdacs	r0, {r3, r4, r7, r8, sl, fp, sp, lr}
d00145c4:	af5ff47f 	svcge	0x005ff47f
d00145c8:	2b20f8df 	blcs	0xd085294c
d00145cc:	e9c3447a 	stmib	r3, {r1, r3, r4, r5, r6, sl, lr}^
d00145d0:	9a052616 	bls	0xd015de30
d00145d4:	7818e9c3 	ldmdavc	r8, {r0, r1, r6, r7, r8, fp, sp, lr, pc}
d00145d8:	4683669a 	pkhbtmi	r6, r3, sl, lsl #13
d00145dc:	f505e768 			; <UNDEFINED> instruction: 0xf505e768
d00145e0:	f8d535ff 			; <UNDEFINED> instruction: 0xf8d535ff
d00145e4:	3b01312c 	blcc	0xd0060a9c
d00145e8:	312cf8c5 	smlawtcc	ip, r5, r8, pc	; <UNPREDICTABLE>
d00145ec:	ecbdb00d 	ldc	0, cr11, [sp], #52	; 0x34
d00145f0:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d00145f4:	f0028ff0 			; <UNDEFINED> instruction: 0xf0028ff0
d00145f8:	2804fafd 	stmdacs	r4, {r0, r2, r3, r4, r5, r6, r7, r9, fp, ip, sp, lr, pc}
d00145fc:	f47f4683 			; <UNDEFINED> instruction: 0xf47f4683
d0014600:	f8dfaf57 			; <UNDEFINED> instruction: 0xf8dfaf57
d0014604:	447b3aec 	ldrbtmi	r3, [fp], #-2796	; 0xfffff514
d0014608:	2b5b6adb 	blcs	0xd16ef17c
d001460c:	829df040 	addshi	pc, sp, #64	; 0x40
d0014610:	46482100 	strbmi	r2, [r8], -r0, lsl #2
d0014614:	fb70f002 	blx	0xd1c50626
d0014618:	9a07e7df 	bls	0xd020e59c
d001461c:	91084628 	tstls	r8, r8, lsr #12
d0014620:	9206441a 	andls	r4, r6, #436207616	; 0x1a000000
d0014624:	fe3cf7fb 	mrc2	7, 1, pc, cr12, cr11, {7}
d0014628:	f1039b07 			; <UNDEFINED> instruction: 0xf1039b07
d001462c:	28000234 	stmdacs	r0, {r2, r4, r5, r9}
d0014630:	850ef040 	strhi	pc, [lr, #-64]	; 0xffffffc0
d0014634:	0a01f10a 	beq	0xd0090a64
d0014638:	0324f24d 	msreq	CPSR_s, #-805306364	; 0xd0000004
d001463c:	92079908 	andls	r9, r7, #8, 18	; 0x20000
d0014640:	f1bbe7a7 			; <UNDEFINED> instruction: 0xf1bbe7a7
d0014644:	d0040f00 	andle	r0, r4, r0, lsl #30
d0014648:	1a10ee18 	bne	0xd044feb0
d001464c:	f7fe202c 			; <UNDEFINED> instruction: 0xf7fe202c
d0014650:	f89afb83 			; <UNDEFINED> instruction: 0xf89afb83
d0014654:	1e736000 	cdpne	0, 7, cr6, cr3, cr0, {0}
d0014658:	f2002b0d 	vqdmulh.s<illegal width 8>	d2, d0, d13
d001465c:	e8df817b 	ldm	pc, {r0, r1, r3, r4, r5, r6, r8, pc}^	; <UNPREDICTABLE>
d0014660:	0063f013 	rsbeq	pc, r3, r3, lsl r0	; <UNPREDICTABLE>
d0014664:	0179000e 	cmneq	r9, lr
d0014668:	01790179 	cmneq	r9, r9, ror r1
d001466c:	01790179 	cmneq	r9, r9, ror r1
d0014670:	006d0179 	rsbeq	r0, sp, r9, ror r1
d0014674:	0179006d 	cmneq	r9, sp, rrx
d0014678:	00ea006d 	rsceq	r0, sl, sp, rrx
d001467c:	f7fe013f 			; <UNDEFINED> instruction: 0xf7fe013f
d0014680:	f10bff2f 			; <UNDEFINED> instruction: 0xf10bff2f
d0014684:	f10a0b01 			; <UNDEFINED> instruction: 0xf10a0b01
d0014688:	f24b0a01 	vpmax.s8	d16, d11, d1
d001468c:	f7fe4003 			; <UNDEFINED> instruction: 0xf7fe4003
d0014690:	9b05fdeb 	blls	0xd0193e44
d0014694:	d903455b 	stmdble	r3, {r0, r1, r3, r4, r6, r8, sl, lr}
d0014698:	6d9b9b0a 	vldrvs	d9, [fp, #40]	; 0x28
d001469c:	d0d02b00 	sbcsle	r2, r0, r0, lsl #22
d00146a0:	1a50f8df 	bne	0xd1452a24
d00146a4:	44792029 	ldrbtmi	r2, [r9], #-41	; 0xffffffd7
d00146a8:	fb56f7fe 	blx	0xd15d26aa
d00146ac:	9805b398 	stmdals	r5, {r3, r4, r7, r8, r9, ip, sp, pc}
d00146b0:	fa57f7ff 	blx	0xd16126b4
d00146b4:	2a40f8df 	bcs	0xd1052a38
d00146b8:	0318f24d 	tsteq	r8, #-805306364	; 0xd0000004	; <UNPREDICTABLE>
d00146bc:	447a4604 	ldrbtmi	r4, [sl], #-1540	; 0xfffff9fc
d00146c0:	58d1200c 	ldmpl	r1, {r2, r3, sp}^
d00146c4:	fdf2f7fe 	ldc2l	7, cr15, [r2, #1016]!	; 0x3f8
d00146c8:	f1039b06 			; <UNDEFINED> instruction: 0xf1039b06
d00146cc:	9b070520 	blls	0xd01d5b54
d00146d0:	4650f503 	ldrbmi	pc, [r0], -r3, lsl #10	; <UNPREDICTABLE>
d00146d4:	f64f364a 			; <UNDEFINED> instruction: 0xf64f364a
d00146d8:	f7fe00dc 			; <UNDEFINED> instruction: 0xf7fe00dc
d00146dc:	f835fdc5 			; <UNDEFINED> instruction: 0xf835fdc5
d00146e0:	f4400b02 			; <UNDEFINED> instruction: 0xf4400b02
d00146e4:	f7fe4040 			; <UNDEFINED> instruction: 0xf7fe4040
d00146e8:	42aefdbf 	adcmi	pc, lr, #12224	; 0x2fc0
d00146ec:	f244d1f3 	vand	<illegal reg q14.5>, q10, <illegal reg q9.5>
d00146f0:	f7fe70e0 			; <UNDEFINED> instruction: 0xf7fe70e0
d00146f4:	b124fdb9 	msrlt	CPSR_s, r9	; <illegal shifter operand>
d00146f8:	4030f444 	eorsmi	pc, r0, r4, asr #8
d00146fc:	f7feb280 			; <UNDEFINED> instruction: 0xf7feb280
d0014700:	9b06fdb3 	blls	0xd01d3dd4
d0014704:	3027f893 	mlacc	r7, r3, r8, pc	; <UNPREDICTABLE>
d0014708:	f0402b06 			; <UNDEFINED> instruction: 0xf0402b06
d001470c:	f24b814b 	vrhadd.s8	q12, <illegal reg q5.5>, <illegal reg q5.5>
d0014710:	f7fe20c0 			; <UNDEFINED> instruction: 0xf7fe20c0
d0014714:	9b06fda9 	blls	0xd01d3dc0
d0014718:	0027f893 	mlaeq	r7, r3, r8, pc	; <UNPREDICTABLE>
d001471c:	f0402807 			; <UNDEFINED> instruction: 0xf0402807
d0014720:	f04f8147 			; <UNDEFINED> instruction: 0xf04f8147
d0014724:	e6c30b02 	strb	r0, [r3], r2, lsl #22
d0014728:	fe0cf7fe 	mcr2	7, 0, pc, cr12, cr14, {7}	; <UNPREDICTABLE>
d001472c:	d1a82800 			; <UNDEFINED> instruction: 0xd1a82800
d0014730:	09c8f8df 	stmibeq	r8, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d0014734:	f7fc4478 			; <UNDEFINED> instruction: 0xf7fc4478
d0014738:	e7a2feff 			; <UNDEFINED> instruction: 0xe7a2feff
d001473c:	fe02f7fe 	mcr2	7, 0, pc, cr2, cr14, {7}	; <UNPREDICTABLE>
d0014740:	d19e2800 	orrsle	r2, lr, r0, lsl #16
d0014744:	f7fe2026 			; <UNDEFINED> instruction: 0xf7fe2026
d0014748:	f8dffad9 			; <UNDEFINED> instruction: 0xf8dffad9
d001474c:	447b39b4 	ldrbtmi	r3, [fp], #-2484	; 0xfffff64c
d0014750:	6ad96a5a 	bvs	0xcf66f0c0
d0014754:	6b5a9208 	blvs	0xd16b8f7c
d0014758:	9028f8d3 	ldrdls	pc, [r8], -r3	; <UNPREDICTABLE>
d001475c:	f2409209 	vhsub.s8	d25, d0, d9
d0014760:	f8931201 			; <UNDEFINED> instruction: 0xf8931201
d0014764:	42918030 	addsmi	r8, r1, #48	; 0x30
d0014768:	f8dfd010 			; <UNDEFINED> instruction: 0xf8dfd010
d001476c:	447b3998 	ldrbtmi	r3, [fp], #-2456	; 0xfffff668
d0014770:	2a006d9a 	bcs	0xd002fde0
d0014774:	f8dfd185 			; <UNDEFINED> instruction: 0xf8dfd185
d0014778:	447a2990 	ldrbtmi	r2, [sl], #-2448	; 0xfffff670
d001477c:	9a08659a 	bls	0xd022ddec
d0014780:	9a0965da 	bls	0xd026def0
d0014784:	9818e9c3 	ldmdals	r8, {r0, r1, r6, r7, r8, fp, sp, lr, pc}
d0014788:	e77a669a 			; <UNDEFINED> instruction: 0xe77a669a
d001478c:	7106e9d3 	ldrdvc	lr, [r6, -r3]
d0014790:	910b4638 	tstls	fp, r8, lsr r6
d0014794:	fc5cf7fe 	mrrc2	7, 15, pc, ip, cr14	; <UNPREDICTABLE>
d0014798:	dbe61e05 	blle	0xcf99bfb4
d001479c:	4638990b 	ldrtmi	r9, [r8], -fp, lsl #18
d00147a0:	fc84f7fe 	stc2	7, cr15, [r4], {254}	; 0xfe
d00147a4:	dae02800 	ble	0xcf81e7ac
d00147a8:	d01f2e09 	andsle	r2, pc, r9, lsl #28
d00147ac:	d1262e0c 			; <UNDEFINED> instruction: 0xd1262e0c
d00147b0:	7958f8df 	ldmdbvc	r8, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d00147b4:	f8df2602 			; <UNDEFINED> instruction: 0xf8df2602
d00147b8:	447f1958 	ldrbtmi	r1, [pc], #-2392	; 0xd00147c0
d00147bc:	44794632 	ldrbtmi	r4, [r9], #-1586	; 0xfffff9ce
d00147c0:	e950f8df 	ldmdb	r0, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d00147c4:	44fe2330 	ldrbtmi	r2, [lr], #816	; 0x330
d00147c8:	eb0e436b 	bl	0xd03a557c
d00147cc:	f50c0c03 			; <UNDEFINED> instruction: 0xf50c0c03
d00147d0:	f89c3cba 			; <UNDEFINED> instruction: 0xf89c3cba
d00147d4:	42b00037 	adcsmi	r0, r0, #55	; 0x37
d00147d8:	f8dfd01a 			; <UNDEFINED> instruction: 0xf8dfd01a
d00147dc:	447b393c 	ldrbtmi	r3, [fp], #-2364	; 0xfffff6c4
d00147e0:	2a006d9a 	bcs	0xd002fe50
d00147e4:	af4df47f 	svcge	0x004df47f
d00147e8:	e7c8659f 	bfc	r6, (invalid: 11:8)
d00147ec:	792cf8df 	stmdbvc	ip!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d00147f0:	f8df2601 			; <UNDEFINED> instruction: 0xf8df2601
d00147f4:	2205192c 	andcs	r1, r5, #44, 18	; 0xb0000
d00147f8:	4479447f 	ldrbtmi	r4, [r9], #-1151	; 0xfffffb81
d00147fc:	f8dfe7e0 			; <UNDEFINED> instruction: 0xf8dfe7e0
d0014800:	26017924 	strcs	r7, [r1], -r4, lsr #18
d0014804:	1920f8df 	stmdbne	r0!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d0014808:	4632447f 			; <UNDEFINED> instruction: 0x4632447f
d001480c:	e7d74479 			; <UNDEFINED> instruction: 0xe7d74479
d0014810:	0034f89c 	mlaseq	r4, ip, r8, pc	; <UNPREDICTABLE>
d0014814:	d1e04290 			; <UNDEFINED> instruction: 0xd1e04290
d0014818:	30baf503 	adcscc	pc, sl, r3, lsl #10
d001481c:	4470303a 	ldrbtmi	r3, [r0], #-58	; 0xffffffc6
d0014820:	feb0f004 	cdp2	0, 11, cr15, cr0, cr4, {0}
d0014824:	d1d82800 	bicsle	r2, r8, r0, lsl #16
d0014828:	fa4af7fe 	blx	0xd12d2828
d001482c:	20024629 	andcs	r4, r2, r9, lsr #12
d0014830:	fdf8f7fe 	ldc2l	7, cr15, [r8, #1016]!	; 0x3f8
d0014834:	f7fee725 			; <UNDEFINED> instruction: 0xf7fee725
d0014838:	2800fd85 	stmdacs	r0, {r0, r2, r7, r8, sl, fp, ip, sp, lr, pc}
d001483c:	af21f47f 	svcge	0x0021f47f
d0014840:	18e8f8df 	stmiane	r8!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d0014844:	44792026 	ldrbtmi	r2, [r9], #-38	; 0xffffffda
d0014848:	fa86f7fe 	blx	0xce1d2848
d001484c:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0014850:	f8dfaf18 			; <UNDEFINED> instruction: 0xf8dfaf18
d0014854:	f24088dc 	vtst.8	q12, q8, q6
d0014858:	44f81201 	ldrbtmi	r1, [r8], #513	; 0x201
d001485c:	102cf8d8 	ldrdne	pc, [ip], -r8	; <UNPREDICTABLE>
d0014860:	3028f8d8 	ldrdcc	pc, [r8], -r8	; <UNPREDICTABLE>
d0014864:	f8d84291 			; <UNDEFINED> instruction: 0xf8d84291
d0014868:	f8989024 			; <UNDEFINED> instruction: 0xf8989024
d001486c:	f8d87030 			; <UNDEFINED> instruction: 0xf8d87030
d0014870:	93086034 	movwls	r6, #32820	; 0x8034
d0014874:	f8dfd010 			; <UNDEFINED> instruction: 0xf8dfd010
d0014878:	447b38bc 	ldrbtmi	r3, [fp], #-2236	; 0xfffff744
d001487c:	2a006d9a 	bcs	0xd002feec
d0014880:	aefff47f 	mrcge	4, 7, APSR_nzcv, cr15, cr15, {3}
d0014884:	28b0f8df 	ldmcs	r0!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d0014888:	e9c3447a 	stmib	r3, {r1, r3, r4, r5, r6, sl, lr}^
d001488c:	9a082916 	bls	0xd021ecec
d0014890:	665f661a 			; <UNDEFINED> instruction: 0x665f661a
d0014894:	e6f4669e 	usat	r6, #20, lr, lsl #13
d0014898:	2106e9d8 	ldrdcs	lr, [r6, -r8]
d001489c:	910b4610 	tstls	fp, r0, lsl r6
d00148a0:	f7fc9209 			; <UNDEFINED> instruction: 0xf7fc9209
d00148a4:	1e05f909 	vmlane.f16	s30, s10, s18	; <UNPREDICTABLE>
d00148a8:	9a09dbe5 	bls	0xd028b844
d00148ac:	4610990b 	ldrmi	r9, [r0], -fp, lsl #18
d00148b0:	fbfcf7fe 	blx	0xcff528b2
d00148b4:	dade2800 	ble	0xcf79e8bc
d00148b8:	fb02222c 	blx	0xd009d172
d00148bc:	f5038305 			; <UNDEFINED> instruction: 0xf5038305
d00148c0:	f89333af 			; <UNDEFINED> instruction: 0xf89333af
d00148c4:	2b05302c 	blcs	0xd016097c
d00148c8:	f7fed1d5 			; <UNDEFINED> instruction: 0xf7fed1d5
d00148cc:	2001f9f9 	strdcs	pc, [r1], -r9
d00148d0:	f7fe4629 			; <UNDEFINED> instruction: 0xf7fe4629
d00148d4:	f244fda7 	vadd.f32	d31, d20, d23
d00148d8:	f7fe6008 			; <UNDEFINED> instruction: 0xf7fe6008
d00148dc:	e6d0fcc5 	ldrb	pc, [r0], r5, asr #25	; <UNPREDICTABLE>
d00148e0:	fd30f7fe 	ldc2	7, cr15, [r0, #-1016]!	; 0xfffffc08
d00148e4:	f47f2800 			; <UNDEFINED> instruction: 0xf47f2800
d00148e8:	6ae2aecc 	bvs	0xcf8c0420
d00148ec:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d00148f0:	9024f8d4 	ldrdls	pc, [r4], -r4	; <UNPREDICTABLE>
d00148f4:	f8d4429a 			; <UNDEFINED> instruction: 0xf8d4429a
d00148f8:	f8948028 			; <UNDEFINED> instruction: 0xf8948028
d00148fc:	6b667030 	blvs	0xd19b09c4
d0014900:	f8dfd00e 			; <UNDEFINED> instruction: 0xf8dfd00e
d0014904:	447b3838 	ldrbtmi	r3, [fp], #-2104	; 0xfffff7c8
d0014908:	2a006d9a 	bcs	0xd002ff78
d001490c:	aeb9f47f 	mrcge	4, 5, APSR_nzcv, cr9, cr15, {3}
d0014910:	282cf8df 	stmdacs	ip!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d0014914:	8060f8c3 	rsbhi	pc, r0, r3, asr #17
d0014918:	e9c3447a 	stmib	r3, {r1, r3, r4, r5, r6, sl, lr}^
d001491c:	e7b82916 			; <UNDEFINED> instruction: 0xe7b82916
d0014920:	3106e9d4 	ldrdcc	lr, [r6, -r4]
d0014924:	91094618 	tstls	r9, r8, lsl r6
d0014928:	f7fc9308 			; <UNDEFINED> instruction: 0xf7fc9308
d001492c:	1e05f8c5 	cdpne	8, 0, cr15, cr5, cr5, {6}
d0014930:	9b08dbe7 	blls	0xd024b8d4
d0014934:	46189909 	ldrmi	r9, [r8], -r9, lsl #18
d0014938:	fbb8f7fe 	blx	0xcee5293a
d001493c:	dae02800 	ble	0xcf81e944
d0014940:	fb03232c 	blx	0xd00dd5fa
d0014944:	f5034305 			; <UNDEFINED> instruction: 0xf5034305
d0014948:	f89333af 			; <UNDEFINED> instruction: 0xf89333af
d001494c:	2b07302c 	blcs	0xd01e0a04
d0014950:	e7bad1d7 	sbfx	sp, r7, #3, #27
d0014954:	46082101 	strmi	r2, [r8], -r1, lsl #2
d0014958:	fcb2f000 	ldc2	0, cr15, [r2]
d001495c:	3000f89a 	mulcc	r0, sl, r8
d0014960:	2b053b03 	blcs	0xd0163574
d0014964:	ae8df63f 	mcrge	6, 4, pc, cr13, cr15, {1}	; <UNPREDICTABLE>
d0014968:	f852a202 			; <UNDEFINED> instruction: 0xf852a202
d001496c:	441a3023 	ldrmi	r3, [sl], #-35	; 0xffffffdd
d0014970:	bf004710 	svclt	0x00004710
d0014974:	00000019 	andeq	r0, r0, r9, lsl r0
d0014978:	0000001f 	andeq	r0, r0, pc, lsl r0
d001497c:	fffffd0f 			; <UNDEFINED> instruction: 0xfffffd0f
d0014980:	0000002b 	andeq	r0, r0, fp, lsr #32
d0014984:	fffffd0f 			; <UNDEFINED> instruction: 0xfffffd0f
d0014988:	00000025 	andeq	r0, r0, r5, lsr #32
d001498c:	4032f44f 	eorsmi	pc, r2, pc, asr #8
d0014990:	f24be7a3 	vabd.s8	d30, d27, d19
d0014994:	e7a02080 	str	r2, [r0, r0, lsl #1]!
d0014998:	2040f24b 	subcs	pc, r0, fp, asr #4
d001499c:	f24be79d 	vaba.s8	d30, d27, d13
d00149a0:	e79a20c0 	ldr	r2, [sl, r0, asr #1]
d00149a4:	f47f2b08 			; <UNDEFINED> instruction: 0xf47f2b08
d00149a8:	f24baeb6 			; <UNDEFINED> instruction: 0xf24baeb6
d00149ac:	e6b02040 	ldrt	r2, [r0], r0, asr #32
d00149b0:	e5782805 	ldrb	r2, [r8, #-2053]!	; 0xfffff7fb
d00149b4:	f7fc4628 			; <UNDEFINED> instruction: 0xf7fc4628
d00149b8:	2800f87f 	stmdacs	r0, {r0, r1, r2, r3, r4, r5, r6, fp, ip, sp, lr, pc}
d00149bc:	adfdf6bf 	ldclge	6, cr15, [sp, #764]!	; 0x2fc
d00149c0:	fb032330 	blx	0xd00dd68a
d00149c4:	18e2f30a 	stmiane	r2!, {r1, r3, r8, r9, ip, sp, lr, pc}^
d00149c8:	32baf502 	adcscc	pc, sl, #8388608	; 0x800000
d00149cc:	103bf892 	mlasne	fp, r2, r8, pc	; <UNPREDICTABLE>
d00149d0:	d10d2904 	tstle	sp, r4, lsl #18
d00149d4:	28006da0 	stmdacs	r0, {r5, r7, r8, sl, fp, sp, lr}
d00149d8:	ad55f47f 	cfldrdge	mvd15, [r5, #-508]	; 0xfffffe04
d00149dc:	3764f8df 			; <UNDEFINED> instruction: 0x3764f8df
d00149e0:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d00149e4:	9b053616 	blls	0xd0162244
d00149e8:	7818e9c4 	ldmdavc	r8, {r2, r6, r7, r8, fp, sp, lr, pc}
d00149ec:	e5f466a3 	ldrb	r6, [r4, #1699]!	; 0x6a3
d00149f0:	2035f892 	mlascs	r5, r2, r8, pc	; <UNPREDICTABLE>
d00149f4:	d01e2a04 	andsle	r2, lr, r4, lsl #20
d00149f8:	574cf8df 			; <UNDEFINED> instruction: 0x574cf8df
d00149fc:	3bbaf503 	blcc	0xceed1e10
d0014a00:	f10b447d 			; <UNDEFINED> instruction: 0xf10b447d
d0014a04:	442b0b3a 	strtmi	r0, [fp], #-2874	; 0xfffff4c6
d0014a08:	0204eb0b 	andeq	lr, r4, #11264	; 0x2c00
d0014a0c:	f5032400 			; <UNDEFINED> instruction: 0xf5032400
d0014a10:	920633ba 	andls	r3, r6, #-402653182	; 0xe8000002
d0014a14:	f8df9307 			; <UNDEFINED> instruction: 0xf8df9307
d0014a18:	447b3734 	ldrbtmi	r3, [fp], #-1844	; 0xfffff8cc
d0014a1c:	3a10ee08 	bcc	0xd0450244
d0014a20:	f8939b07 			; <UNDEFINED> instruction: 0xf8939b07
d0014a24:	42840034 	addmi	r0, r4, #52	; 0x34
d0014a28:	6dabd201 	sfmvs	f5, 1, [fp, #4]!
d0014a2c:	f7ffb30b 			; <UNDEFINED> instruction: 0xf7ffb30b
d0014a30:	4605f898 			; <UNDEFINED> instruction: 0x4605f898
d0014a34:	2500e002 	strcs	lr, [r0, #-2]
d0014a38:	fd52f7fe 	ldc2l	7, cr15, [r2, #-1016]	; 0xfffffc08
d0014a3c:	1710f8df 			; <UNDEFINED> instruction: 0x1710f8df
d0014a40:	44792029 	ldrbtmi	r2, [r9], #-41	; 0xffffffd7
d0014a44:	f988f7fe 			; <UNDEFINED> instruction: 0xf988f7fe
d0014a48:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0014a4c:	f8dfad1c 			; <UNDEFINED> instruction: 0xf8dfad1c
d0014a50:	447c4704 	ldrbtmi	r4, [ip], #-1796	; 0xfffff8fc
d0014a54:	33f2f504 	mvnscc	pc, #4, 10	; 0x1000000
d0014a58:	b014f8d3 			; <UNDEFINED> instruction: 0xb014f8d3
d0014a5c:	6f00f5bb 	svcvs	0x0000f5bb
d0014a60:	6da0d14e 	stfvsd	f5, [r0, #312]!	; 0x138
d0014a64:	f47f2800 			; <UNDEFINED> instruction: 0xf47f2800
d0014a68:	f8dfad0e 			; <UNDEFINED> instruction: 0xf8dfad0e
d0014a6c:	447b36ec 	ldrbtmi	r3, [fp], #-1772	; 0xfffff914
d0014a70:	b124e7b7 			; <UNDEFINED> instruction: 0xb124e7b7
d0014a74:	1a10ee18 	bne	0xd04502dc
d0014a78:	f7fe202c 			; <UNDEFINED> instruction: 0xf7fe202c
d0014a7c:	9b06f96d 	blls	0xd01d3038
d0014a80:	bb01f813 	bllt	0xd0092ad4
d0014a84:	0f0af1bb 	svceq	0x000af1bb
d0014a88:	d1049306 	tstle	r4, r6, lsl #6
d0014a8c:	20012104 	andcs	r2, r1, r4, lsl #2
d0014a90:	fc16f000 	ldc2	0, cr15, [r6], {-0}
d0014a94:	f00be02b 			; <UNDEFINED> instruction: 0xf00be02b
d0014a98:	2b0203fb 	blcs	0xd0095a8c
d0014a9c:	f7fed12d 			; <UNDEFINED> instruction: 0xf7fed12d
d0014aa0:	bb20fc51 	bllt	0xd0853bec
d0014aa4:	36b4f8df 	ssatcc	pc, #21, pc, asr #17	; <UNPREDICTABLE>
d0014aa8:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d0014aac:	6ad8447b 	bvs	0xcf625ca0
d0014ab0:	d0054288 	andle	r4, r5, r8, lsl #5
d0014ab4:	06a8f8df 	ssateq	pc, #9, pc, asr #17	; <UNPREDICTABLE>
d0014ab8:	f7fc4478 			; <UNDEFINED> instruction: 0xf7fc4478
d0014abc:	e630fd3d 			; <UNDEFINED> instruction: 0xe630fd3d
d0014ac0:	0106e9d3 	ldrdeq	lr, [r6, -r3]
d0014ac4:	f7fe9308 			; <UNDEFINED> instruction: 0xf7fe9308
d0014ac8:	2800faf1 	stmdacs	r0, {r0, r4, r5, r6, r7, r9, fp, ip, sp, lr, pc}
d0014acc:	9b08dbf2 	blls	0xd024ba9c
d0014ad0:	9008212c 	andls	r2, r8, ip, lsr #2
d0014ad4:	3300fb01 	movwcc	pc, #2817	; 0xb01	; <UNPREDICTABLE>
d0014ad8:	33faf503 	mvnscc	pc, #12582912	; 0xc00000
d0014adc:	3041f893 	umaalcc	pc, r1, r3, r8	; <UNPREDICTABLE>
d0014ae0:	d1e7455b 	mvnle	r4, fp, asr r5
d0014ae4:	f8ecf7fe 			; <UNDEFINED> instruction: 0xf8ecf7fe
d0014ae8:	f7fe9808 			; <UNDEFINED> instruction: 0xf7fe9808
d0014aec:	f24bfc5d 	vfma.f32	<illegal reg q15.5>, <illegal reg q5.5>, <illegal reg q6.5>
d0014af0:	34014003 	strcc	r4, [r1], #-3
d0014af4:	fbb8f7fe 	blx	0xcee52af6
d0014af8:	2101e792 			; <UNDEFINED> instruction: 0x2101e792
d0014afc:	e7c74608 	strb	r4, [r7, r8, lsl #12]
d0014b00:	0201f10b 	andeq	pc, r1, #-1073741822	; 0xc0000002
d0014b04:	5b52f50b 	blpl	0xd14d1f38
d0014b08:	0b02f10b 	bleq	0xd00d0f3c
d0014b0c:	f7fe615a 			; <UNDEFINED> instruction: 0xf7fe615a
d0014b10:	eb04ffef 	bl	0xd0154ad4
d0014b14:	606004cb 	rsbvs	r0, r0, fp, asr #9
d0014b18:	a008f8a4 	andge	pc, r8, r4, lsr #17
d0014b1c:	f445b125 	vst4.8	{d27,d29,d31,d33}, [r5 :128], r5
d0014b20:	b2804030 	addlt	r4, r0, #48	; 0x30
d0014b24:	fba0f7fe 	blx	0xce852b26
d0014b28:	0638f8df 			; <UNDEFINED> instruction: 0x0638f8df
d0014b2c:	44782330 	ldrbtmi	r2, [r8], #-816	; 0xfffffcd0
d0014b30:	0a0afb03 	beq	0xd02d3744
d0014b34:	3abaf50a 	bcc	0xceed1f64
d0014b38:	3037f89a 	mlascc	r7, sl, r8, pc	; <UNPREDICTABLE>
d0014b3c:	f43f2b01 			; <UNDEFINED> instruction: 0xf43f2b01
d0014b40:	2b03adf0 	blcs	0xd0100308
d0014b44:	ac9ff47f 	cfldrsge	mvf15, [pc], {127}	; 0x7f
d0014b48:	f04fe55b 			; <UNDEFINED> instruction: 0xf04fe55b
d0014b4c:	e4af0b04 	strt	r0, [pc], #2820	; 0xd0014b54
d0014b50:	402cf8da 	ldrdmi	pc, [ip], -sl	; <UNPREDICTABLE>
d0014b54:	f5a49106 			; <UNDEFINED> instruction: 0xf5a49106
d0014b58:	2b01738f 	blcs	0xd007199c
d0014b5c:	f7fed80d 			; <UNDEFINED> instruction: 0xf7fed80d
d0014b60:	2301f8af 	movwcs	pc, #6319	; 0x18af	; <UNPREDICTABLE>
d0014b64:	99064632 	stmdbls	r6, {r1, r4, r5, r9, sl, lr}
d0014b68:	46289303 	strtmi	r9, [r8], -r3, lsl #6
d0014b6c:	94029b05 	strls	r9, [r2], #-2821	; 0xfffff4fb
d0014b70:	463b9301 	ldrtmi	r9, [fp], -r1, lsl #6
d0014b74:	8000f8cd 	andhi	pc, r0, sp, asr #17
d0014b78:	4628e4d2 			; <UNDEFINED> instruction: 0x4628e4d2
d0014b7c:	fa96f7fe 	blx	0xce5d2b7c
d0014b80:	46829906 	strmi	r9, [r2], r6, lsl #18
d0014b84:	f7fb4628 			; <UNDEFINED> instruction: 0xf7fb4628
d0014b88:	9906ff75 	stmdbls	r6, {r0, r2, r4, r5, r6, r8, r9, sl, fp, ip, sp, lr, pc}
d0014b8c:	6a00b118 	bvs	0xd0040ff4
d0014b90:	fbd0f7fe 	blx	0xcf452b92
d0014b94:	f1bae48c 			; <UNDEFINED> instruction: 0xf1bae48c
d0014b98:	f2c00f00 			; <UNDEFINED> instruction: 0xf2c00f00
d0014b9c:	f8df8091 			; <UNDEFINED> instruction: 0xf8df8091
d0014ba0:	232c45c8 			; <UNDEFINED> instruction: 0x232c45c8
d0014ba4:	fb03447c 	blx	0xd00e5d9e
d0014ba8:	f503430a 			; <UNDEFINED> instruction: 0xf503430a
d0014bac:	f89333fa 			; <UNDEFINED> instruction: 0xf89333fa
d0014bb0:	2d025041 	stccs	0, cr5, [r2, #-260]	; 0xfffffefc
d0014bb4:	2d04d001 	stccs	0, cr13, [r4, #-4]
d0014bb8:	f8dfd10e 			; <UNDEFINED> instruction: 0xf8dfd10e
d0014bbc:	447b35b0 	ldrbtmi	r3, [fp], #-1456	; 0xfffffa50
d0014bc0:	2a006d9a 	bcs	0xd0030230
d0014bc4:	ac5ff47f 	cfldrdge	mvd15, [pc], {127}	; 0x7f
d0014bc8:	25a4f8df 	strcs	pc, [r4, #2271]!	; 0x8df
d0014bcc:	e9c3447a 	stmib	r3, {r1, r3, r4, r5, r6, sl, lr}^
d0014bd0:	e9c32616 	stmib	r3, {r1, r2, r4, r9, sl, sp}^
d0014bd4:	e06a7818 	rsb	r7, sl, r8, lsl r8
d0014bd8:	d1052d0c 	tstle	r5, ip, lsl #26
d0014bdc:	f7fe4650 			; <UNDEFINED> instruction: 0xf7fe4650
d0014be0:	f04ffbe3 			; <UNDEFINED> instruction: 0xf04ffbe3
d0014be4:	e4630b03 	strbt	r0, [r3], #-2819	; 0xfffff4fd
d0014be8:	d10a2d09 	tstle	sl, r9, lsl #26
d0014bec:	ea4f2000 	b	0xd13dcbf4
d0014bf0:	f7fe018a 			; <UNDEFINED> instruction: 0xf7fe018a
d0014bf4:	f641fb5b 			; <UNDEFINED> instruction: 0xf641fb5b
d0014bf8:	f7fe0038 			; <UNDEFINED> instruction: 0xf7fe0038
d0014bfc:	6ae3fb35 	bvs	0xcf9138d8
d0014c00:	4650e503 	ldrbmi	lr, [r0], -r3, lsl #10
d0014c04:	fbd0f7fe 	blx	0xcf452c06
d0014c08:	d1542d06 	cmple	r4, r6, lsl #26
d0014c0c:	101df240 	andsne	pc, sp, r0, asr #4
d0014c10:	f874f7fe 			; <UNDEFINED> instruction: 0xf874f7fe
d0014c14:	d0e42800 	rscle	r2, r4, r0, lsl #16
d0014c18:	1558f8df 	ldrbne	pc, [r8, #-2271]	; 0xfffff721	; <UNPREDICTABLE>
d0014c1c:	1001f240 	andne	pc, r1, r0, asr #4
d0014c20:	44796b63 	ldrbtmi	r6, [r9], #-2915	; 0xfffff49d
d0014c24:	6aa66a67 	bvs	0xce9af5c8
d0014c28:	5030f894 	mlaspl	r0, r4, r8, pc	; <UNPREDICTABLE>
d0014c2c:	e9d49305 	ldmib	r4, {r0, r2, r8, r9, ip, pc}^
d0014c30:	f7fe8906 			; <UNDEFINED> instruction: 0xf7fe8906
d0014c34:	2800f891 	stmdacs	r0, {r0, r4, r7, fp, ip, sp, lr, pc}
d0014c38:	ac25f43f 	cfstrsge	mvf15, [r5], #-252	; 0xffffff04
d0014c3c:	a538f8df 	ldrge	pc, [r8, #-2271]!	; 0xfffff721
d0014c40:	44fa2400 	ldrbtmi	r2, [sl], #1024	; 0x400
d0014c44:	2b04f85a 	blcs	0xd0152db4
d0014c48:	46404649 	strbmi	r4, [r0], -r9, asr #12
d0014c4c:	fb28f7fb 	blx	0xd0a52c42
d0014c50:	b1d84683 	bicslt	r4, r8, r3, lsl #13
d0014c54:	03d0f64f 	bicseq	pc, r0, #82837504	; 0x4f00000
d0014c58:	0090f64f 	addseq	pc, r0, pc, asr #12
d0014c5c:	bf182c01 	svclt	0x00182c01
d0014c60:	f7fe4618 			; <UNDEFINED> instruction: 0xf7fe4618
d0014c64:	f504fb01 			; <UNDEFINED> instruction: 0xf504fb01
d0014c68:	f8df42dd 			; <UNDEFINED> instruction: 0xf8df42dd
d0014c6c:	32703510 	rsbscc	r3, r0, #16, 10	; 0x4000000
d0014c70:	eb03447b 	bl	0xd00e5e64
d0014c74:	88980342 	ldmhi	r8, {r1, r6, r8, r9}
d0014c78:	faf6f7fe 	blx	0xcfdd2c78
d0014c7c:	3c02b11c 	stfccd	f3, [r2], {28}
d0014c80:	f63f2c01 			; <UNDEFINED> instruction: 0xf63f2c01
d0014c84:	f04fac00 			; <UNDEFINED> instruction: 0xf04fac00
d0014c88:	e4110b01 	ldr	r0, [r1], #-2817	; 0xfffff4ff
d0014c8c:	2c083401 	cfstrscs	mvf3, [r8], {1}
d0014c90:	f8dfd1d8 			; <UNDEFINED> instruction: 0xf8dfd1d8
d0014c94:	447b34ec 	ldrbtmi	r3, [fp], #-1260	; 0xfffffb14
d0014c98:	2a006d9a 	bcs	0xd0030308
d0014c9c:	abf3f47f 	blge	0xcfd11ea0
d0014ca0:	24e0f8df 	strbtcs	pc, [r0], #2271	; 0x8df	; <UNPREDICTABLE>
d0014ca4:	e9c3447a 	stmib	r3, {r1, r3, r4, r5, r6, sl, lr}^
d0014ca8:	e9c36518 	stmib	r3, {r3, r4, r8, sl, sp, lr}^
d0014cac:	9a052716 	bls	0xd015e90c
d0014cb0:	f7ff669a 			; <UNDEFINED> instruction: 0xf7ff669a
d0014cb4:	2d0abbfd 	vstrcs	d11, [sl, #-1012]	; 0xfffffc0c
d0014cb8:	2d01d0a1 	stccs	0, cr13, [r1, #-644]	; 0xfffffd7c
d0014cbc:	bbf3f7ff 	bllt	0xcfd12cc0
d0014cc0:	91064628 	tstls	r6, r8, lsr #12
d0014cc4:	fef8f7fb 	mrc2	7, 7, pc, cr8, cr11, {7}
d0014cc8:	99061e04 	stmdbls	r6, {r2, r9, sl, fp, ip}
d0014ccc:	f8dfdb5c 			; <UNDEFINED> instruction: 0xf8dfdb5c
d0014cd0:	232c64b8 			; <UNDEFINED> instruction: 0x232c64b8
d0014cd4:	fb03447e 	blx	0xd00e5ed6
d0014cd8:	f5036304 			; <UNDEFINED> instruction: 0xf5036304
d0014cdc:	f89333af 			; <UNDEFINED> instruction: 0xf89333af
d0014ce0:	2d07502c 	stccs	0, cr5, [r7, #-176]	; 0xffffff50
d0014ce4:	f8dfd13c 			; <UNDEFINED> instruction: 0xf8dfd13c
d0014ce8:	205b14a4 	subscs	r1, fp, r4, lsr #9
d0014cec:	f7fe4479 			; <UNDEFINED> instruction: 0xf7fe4479
d0014cf0:	2800f833 	stmdacs	r0, {r0, r1, r4, r5, fp, ip, sp, lr, pc}
d0014cf4:	abc7f43f 	blge	0xcf211df8
d0014cf8:	46082101 	strmi	r2, [r8], -r1, lsl #2
d0014cfc:	fae0f000 	blx	0xcf850d04
d0014d00:	148cf8df 	strne	pc, [ip], #2271	; 0x8df
d0014d04:	4479205d 	ldrbtmi	r2, [r9], #-93	; 0xffffffa3
d0014d08:	f826f7fe 			; <UNDEFINED> instruction: 0xf826f7fe
d0014d0c:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0014d10:	4621abba 			; <UNDEFINED> instruction: 0x4621abba
d0014d14:	f7fe2001 			; <UNDEFINED> instruction: 0xf7fe2001
d0014d18:	f1b9fb85 			; <UNDEFINED> instruction: 0xf1b9fb85
d0014d1c:	d1050f00 	tstle	r5, r0, lsl #30
d0014d20:	4008f645 	andmi	pc, r8, r5, asr #12
d0014d24:	faa0f7fe 	blx	0xce852d24
d0014d28:	bbc2f7ff 	bllt	0xcf0d2d2c
d0014d2c:	f7fd203d 			; <UNDEFINED> instruction: 0xf7fd203d
d0014d30:	2800ffe5 	stmdacs	r0, {r0, r2, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0014d34:	f641d0f4 			; <UNDEFINED> instruction: 0xf641d0f4
d0014d38:	f7fe0008 			; <UNDEFINED> instruction: 0xf7fe0008
d0014d3c:	f24bfa95 	vpmin.s8	d31, d27, d5
d0014d40:	f7fe4003 			; <UNDEFINED> instruction: 0xf7fe4003
d0014d44:	2101fa91 			; <UNDEFINED> instruction: 0x2101fa91
d0014d48:	f0004608 			; <UNDEFINED> instruction: 0xf0004608
d0014d4c:	f64bfab9 			; <UNDEFINED> instruction: 0xf64bfab9
d0014d50:	f7fe4006 			; <UNDEFINED> instruction: 0xf7fe4006
d0014d54:	f247fa89 	vpmax.s8	d31, d23, d9
d0014d58:	f7fe0008 			; <UNDEFINED> instruction: 0xf7fe0008
d0014d5c:	e4e0fa85 	strbt	pc, [r0], #2693	; 0xa85	; <UNPREDICTABLE>
d0014d60:	46212d08 	strtmi	r2, [r1], -r8, lsl #26
d0014d64:	0001f04f 	andeq	pc, r1, pc, asr #32
d0014d68:	f7fed107 			; <UNDEFINED> instruction: 0xf7fed107
d0014d6c:	f244fb5b 	vpadd.i8	<illegal reg q15.5>, q2, <illegal reg q5.5>
d0014d70:	f7fe6008 			; <UNDEFINED> instruction: 0xf7fe6008
d0014d74:	6af3fa79 	bvs	0xcfd13760
d0014d78:	f7fee447 			; <UNDEFINED> instruction: 0xf7fee447
d0014d7c:	f646fb53 			; <UNDEFINED> instruction: 0xf646fb53
d0014d80:	f7fe0008 			; <UNDEFINED> instruction: 0xf7fe0008
d0014d84:	e798fa71 			; <UNDEFINED> instruction: 0xe798fa71
d0014d88:	2408f8df 	strcs	pc, [r8], #-2271	; 0xfffff721
d0014d8c:	447a4628 	ldrbtmi	r4, [sl], #-1576	; 0xfffff9d8
d0014d90:	fa86f7fb 	blx	0xce1d2d84
d0014d94:	b1184683 	tstlt	r8, r3, lsl #13
d0014d98:	f7fe2000 			; <UNDEFINED> instruction: 0xf7fe2000
d0014d9c:	e720facb 	str	pc, [r0, -fp, asr #21]!
d0014da0:	447b4bfd 	ldrbtmi	r4, [fp], #-3069	; 0xfffff403
d0014da4:	2a006d9a 	bcs	0xd0030414
d0014da8:	ab6df47f 	blge	0xd1b91fac
d0014dac:	447a4afb 	ldrbtmi	r4, [sl], #-2811	; 0xfffff505
d0014db0:	2026e70d 	eorcs	lr, r6, sp, lsl #14
d0014db4:	ffa2f7fd 			; <UNDEFINED> instruction: 0xffa2f7fd
d0014db8:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d0014dbc:	49f88088 	ldmibmi	r8!, {r3, r7, pc}^
d0014dc0:	1001f240 	andne	pc, r1, r0, asr #4
d0014dc4:	4024f8da 	ldrdmi	pc, [r4], -sl	; <UNPREDICTABLE>
d0014dc8:	f8da4479 			; <UNDEFINED> instruction: 0xf8da4479
d0014dcc:	f89a5028 			; <UNDEFINED> instruction: 0xf89a5028
d0014dd0:	f8da6030 			; <UNDEFINED> instruction: 0xf8da6030
d0014dd4:	e9da7034 	ldmib	sl, {r2, r4, r5, ip, sp, lr}^
d0014dd8:	f7fd8906 			; <UNDEFINED> instruction: 0xf7fd8906
d0014ddc:	b940ffbd 	stmdblt	r0, {r0, r2, r3, r4, r5, r7, r8, r9, sl, fp, ip, sp, lr, pc}^
d0014de0:	9a069b06 	bls	0xd01bba00
d0014de4:	312cf8d3 	ldrdcc	pc, [ip, -r3]!
d0014de8:	f8c23b01 			; <UNDEFINED> instruction: 0xf8c23b01
d0014dec:	f7ff312c 			; <UNDEFINED> instruction: 0xf7ff312c
d0014df0:	4649bbfd 			; <UNDEFINED> instruction: 0x4649bbfd
d0014df4:	f7fe4640 			; <UNDEFINED> instruction: 0xf7fe4640
d0014df8:	f1b0f959 			; <UNDEFINED> instruction: 0xf1b0f959
d0014dfc:	f2800a00 	vmlsl.s8	q0, d0, d0
d0014e00:	4649813b 			; <UNDEFINED> instruction: 0x4649813b
d0014e04:	f7fb4640 			; <UNDEFINED> instruction: 0xf7fb4640
d0014e08:	1e01fe57 	mcrne	14, 0, pc, cr1, cr7, {2}	; <UNPREDICTABLE>
d0014e0c:	4be5da1e 	blmi	0xcf98b68c
d0014e10:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d0014e14:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0014e18:	4ae3ab36 	bmi	0xcf8ffaf8
d0014e1c:	447a669f 	ldrbtmi	r6, [sl], #-1695	; 0xfffff961
d0014e20:	5618e9c3 	ldrpl	lr, [r8], -r3, asr #19
d0014e24:	2416e9c3 	ldrcs	lr, [r6], #-2499	; 0xfffff63d
d0014e28:	bb42f7ff 	bllt	0xd10d2e2c
d0014e2c:	f47f2b09 			; <UNDEFINED> instruction: 0xf47f2b09
d0014e30:	6d93ae8c 	ldcvs	14, cr10, [r3, #560]	; 0x230
d0014e34:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0014e38:	4bdcab26 	blmi	0xcf73fad8
d0014e3c:	447b6697 	ldrbtmi	r6, [fp], #-1687	; 0xfffff969
d0014e40:	5618e9c2 	ldrpl	lr, [r8], -r2, asr #19
d0014e44:	3416e9c2 	ldrcc	lr, [r6], #-2498	; 0xfffff63e
d0014e48:	bb32f7ff 	bllt	0xd0cd2e4c
d0014e4c:	8360f8df 	msrhi	SPSR_, #14614528	; 0xdf0000
d0014e50:	092cf04f 	stmdbeq	ip!, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d0014e54:	fb0944f8 	blx	0xd026623e
d0014e58:	f5098901 			; <UNDEFINED> instruction: 0xf5098901
d0014e5c:	f89939af 			; <UNDEFINED> instruction: 0xf89939af
d0014e60:	f010002c 			; <UNDEFINED> instruction: 0xf010002c
d0014e64:	d1d20af7 	ldrshle	r0, [r2, #167]	; 0xa7
d0014e68:	f7fe2001 			; <UNDEFINED> instruction: 0xf7fe2001
d0014e6c:	f244fadb 	vpmin.s8	<illegal reg q15.5>, q10, <illegal reg q5.5>
d0014e70:	f7fe6008 			; <UNDEFINED> instruction: 0xf7fe6008
d0014e74:	f8d8f9f9 			; <UNDEFINED> instruction: 0xf8d8f9f9
d0014e78:	2b5b302c 	blcs	0xd16e0f30
d0014e7c:	302cf899 	mlacc	ip, r9, r8, pc	; <UNPREDICTABLE>
d0014e80:	2b08d101 	blcs	0xd024928c
d0014e84:	2b08e11e 	blcs	0xd024d304
d0014e88:	ae5ff47f 	mrcge	4, 2, APSR_nzcv, cr15, cr15, {3}
d0014e8c:	3058f8d8 	ldrsbcc	pc, [r8], #-136	; 0xffffff78	; <UNPREDICTABLE>
d0014e90:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0014e94:	4bc7aaf8 	blmi	0xcf1ffa7c
d0014e98:	f8c8447b 			; <UNDEFINED> instruction: 0xf8c8447b
d0014e9c:	e9c87068 	stmib	r8, {r3, r5, r6, ip, sp, lr}^
d0014ea0:	e9c83416 	stmib	r8, {r1, r2, r4, sl, ip, sp}^
d0014ea4:	f7ff5618 			; <UNDEFINED> instruction: 0xf7ff5618
d0014ea8:	2b0abb03 	blcs	0xd02c3abc
d0014eac:	4650d1af 	ldrbmi	sp, [r0], -pc, lsr #3
d0014eb0:	fa7af7fe 	blx	0xd1ed2eb0
d0014eb4:	302cf8d8 	ldrdcc	pc, [ip], -r8	; <UNPREDICTABLE>
d0014eb8:	f0002b5b 			; <UNDEFINED> instruction: 0xf0002b5b
d0014ebc:	f8d88105 			; <UNDEFINED> instruction: 0xf8d88105
d0014ec0:	2b003058 	blcs	0xd0021028
d0014ec4:	aadff47f 	bge	0xcf8120c8
d0014ec8:	447b4bbb 	ldrbtmi	r4, [fp], #-3003	; 0xfffff445
d0014ecc:	202ae7e5 	eorcs	lr, sl, r5, ror #15
d0014ed0:	ff14f7fd 			; <UNDEFINED> instruction: 0xff14f7fd
d0014ed4:	4658b350 			; <UNDEFINED> instruction: 0x4658b350
d0014ed8:	faacf7ff 	blx	0xceb52edc
d0014edc:	46832804 	strmi	r2, [r3], r4, lsl #16
d0014ee0:	4bb6d008 	blmi	0xcedc8f08
d0014ee4:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d0014ee8:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0014eec:	4ab4aae1 	bmi	0xced3fa78
d0014ef0:	e66c447a 			; <UNDEFINED> instruction: 0xe66c447a
d0014ef4:	0f00f1b9 	svceq	0x0000f1b9
d0014ef8:	203dd012 	eorscs	sp, sp, r2, lsl r0
d0014efc:	fefef7fd 	mrc2	7, 7, pc, cr14, cr13, {7}
d0014f00:	f24bb170 	vand	<illegal reg q13.5>, <illegal reg q5.5>, q8
d0014f04:	f7fe4003 			; <UNDEFINED> instruction: 0xf7fe4003
d0014f08:	2101f9af 	smlatbcs	r1, pc, r9, pc	; <UNPREDICTABLE>
d0014f0c:	f0004608 			; <UNDEFINED> instruction: 0xf0004608
d0014f10:	f64bf9d7 			; <UNDEFINED> instruction: 0xf64bf9d7
d0014f14:	f7fe4006 			; <UNDEFINED> instruction: 0xf7fe4006
d0014f18:	f246f9a7 	vmla.i8	d31, d22, d23
d0014f1c:	e71c0008 	ldr	r0, [ip, -r8]
d0014f20:	40d0f44f 	sbcsmi	pc, r0, pc, asr #8
d0014f24:	f9a0f7fe 			; <UNDEFINED> instruction: 0xf9a0f7fe
d0014f28:	baadf7ff 	blt	0xceb92f2c
d0014f2c:	f7fd2028 			; <UNDEFINED> instruction: 0xf7fd2028
d0014f30:	2800fee5 	stmdacs	r0, {r0, r2, r5, r6, r7, r9, sl, fp, ip, sp, lr, pc}
d0014f34:	4da3d03d 	stcmi	0, cr13, [r3, #244]!	; 0xf4
d0014f38:	6aeb447d 	bvs	0xcfae6134
d0014f3c:	d12c2b2a 			; <UNDEFINED> instruction: 0xd12c2b2a
d0014f40:	f2406cea 	sha1c.32	q11, q8, q13
d0014f44:	429a1301 	addsmi	r1, sl, #67108864	; 0x4000000
d0014f48:	e9d5d127 	ldmib	r5, {r0, r1, r2, r5, r8, ip, lr, pc}^
d0014f4c:	f7fe010e 			; <UNDEFINED> instruction: 0xf7fe010e
d0014f50:	1e04f8ad 	cdpne	8, 0, cr15, cr4, cr13, {5}
d0014f54:	232cdb21 			; <UNDEFINED> instruction: 0x232cdb21
d0014f58:	5304fb03 	movwpl	pc, #19203	; 0x4b03	; <UNPREDICTABLE>
d0014f5c:	33faf503 	mvnscc	pc, #12582912	; 0xc00000
d0014f60:	3041f893 	umaalcc	pc, r1, r3, r8	; <UNPREDICTABLE>
d0014f64:	d1182b0c 	tstle	r8, ip, lsl #22
d0014f68:	feaaf7fd 	mcr2	7, 5, pc, cr10, cr13, {7}	; <UNPREDICTABLE>
d0014f6c:	fea8f7fd 	mcr2	7, 5, pc, cr8, cr13, {7}	; <UNPREDICTABLE>
d0014f70:	20294995 	mlacs	r9, r5, r9, r4
d0014f74:	f7fd4479 			; <UNDEFINED> instruction: 0xf7fd4479
d0014f78:	2800feef 	stmdacs	r0, {r0, r1, r2, r3, r5, r6, r7, r9, sl, fp, ip, sp, lr, pc}
d0014f7c:	aa83f43f 	bge	0xce112080
d0014f80:	20284992 	mlacs	r8, r2, r9, r4
d0014f84:	f7fd4479 			; <UNDEFINED> instruction: 0xf7fd4479
d0014f88:	2800fee7 	stmdacs	r0, {r0, r1, r2, r5, r6, r7, r9, sl, fp, ip, sp, lr, pc}
d0014f8c:	aa7bf43f 	bge	0xd1f12090
d0014f90:	f0014620 			; <UNDEFINED> instruction: 0xf0014620
d0014f94:	f7fffe2f 			; <UNDEFINED> instruction: 0xf7fffe2f
d0014f98:	2100bb20 	tstcs	r0, r0, lsr #22
d0014f9c:	f0002001 			; <UNDEFINED> instruction: 0xf0002001
d0014fa0:	498bf98f 	stmibmi	fp, {r0, r1, r2, r3, r7, r8, fp, ip, sp, lr, pc}
d0014fa4:	20294683 	eorcs	r4, r9, r3, lsl #13
d0014fa8:	f7fd4479 			; <UNDEFINED> instruction: 0xf7fd4479
d0014fac:	f7fffed5 			; <UNDEFINED> instruction: 0xf7fffed5
d0014fb0:	202bba7f 	eorcs	fp, fp, pc, ror sl
d0014fb4:	fea2f7fd 	mcr2	7, 5, pc, cr2, cr13, {7}	; <UNPREDICTABLE>
d0014fb8:	2000b170 	andcs	fp, r0, r0, ror r1
d0014fbc:	fa3af7ff 	blx	0xd0ed2fc0
d0014fc0:	46832802 	strmi	r2, [r3], r2, lsl #16
d0014fc4:	4b83d11e 	blmi	0xce109444
d0014fc8:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d0014fcc:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0014fd0:	4a81aa6f 	bmi	0xce07f994
d0014fd4:	e5fa447a 	ldrb	r4, [sl, #1146]!	; 0x47a
d0014fd8:	f7fd202d 			; <UNDEFINED> instruction: 0xf7fd202d
d0014fdc:	2800fe8f 	stmdacs	r0, {r0, r1, r2, r3, r7, r9, sl, fp, ip, sp, lr, pc}
d0014fe0:	2021d1eb 	eorcs	sp, r1, fp, ror #3
d0014fe4:	fe8af7fd 	mcr2	7, 4, pc, cr10, cr13, {7}	; <UNPREDICTABLE>
d0014fe8:	d1e62800 	mvnle	r2, r0, lsl #16
d0014fec:	f7fd207e 			; <UNDEFINED> instruction: 0xf7fd207e
d0014ff0:	4683fe85 	strmi	pc, [r3], r5, lsl #29
d0014ff4:	d1e02800 	mvnle	r2, r0, lsl #16
d0014ff8:	44784878 	ldrbtmi	r4, [r8], #-2168	; 0xfffff788
d0014ffc:	fa9cf7fc 	blx	0xce752ff4
d0015000:	ba56f7ff 	blt	0xd15d3004
d0015004:	d10a2803 	tstle	sl, r3, lsl #16
d0015008:	d0152c21 	andsle	r2, r5, r1, lsr #24
d001500c:	447b4b74 	ldrbtmi	r4, [fp], #-2932	; 0xfffff48c
d0015010:	2a006d9a 	bcs	0xd0030680
d0015014:	aa4cf47f 	bge	0xd1352218
d0015018:	447a4a72 	ldrbtmi	r4, [sl], #-2674	; 0xfffff58e
d001501c:	2c2de5d7 	cfstr32cs	mvfx14, [sp], #-860	; 0xfffffca4
d0015020:	f244d102 	vrhadd.s8	d29, d4, d2
d0015024:	e67d2040 	ldrbt	r2, [sp], -r0, asr #32
d0015028:	d1022c7e 	tstle	r2, lr, ror ip
d001502c:	30c0f244 	sbccc	pc, r0, r4, asr #4
d0015030:	2c21e678 	stccs	6, cr14, [r1], #-480	; 0xfffffe20
d0015034:	aa3cf47f 	bge	0xd0f52238
d0015038:	5020f44f 	eorpl	pc, r0, pc, asr #8
d001503c:	f914f7fe 			; <UNDEFINED> instruction: 0xf914f7fe
d0015040:	f7fe2000 			; <UNDEFINED> instruction: 0xf7fe2000
d0015044:	f7fffd78 			; <UNDEFINED> instruction: 0xf7fffd78
d0015048:	2000ba1e 	andcs	fp, r0, lr, lsl sl
d001504c:	bacef7ff 	blt	0xcf3d3050
d0015050:	f04f9b06 			; <UNDEFINED> instruction: 0xf04f9b06
d0015054:	4c640b00 			; <UNDEFINED> instruction: 0x4c640b00
d0015058:	3026f893 	mlacc	r6, r3, r8, pc	; <UNPREDICTABLE>
d001505c:	9305447c 	movwls	r4, #21628	; 0x547c
d0015060:	f1039b06 			; <UNDEFINED> instruction: 0xf1039b06
d0015064:	4b610a28 	blmi	0xd185790c
d0015068:	930a447b 	movwls	r4, #42107	; 0xa47b
d001506c:	447b4b60 	ldrbtmi	r4, [fp], #-2912	; 0xfffff4a0
d0015070:	3a10ee08 	bcc	0xd0450898
d0015074:	bb0df7ff 	bllt	0xd0393078
d0015078:	8178f8df 	ldrsbhi	pc, [r8, #-143]!	; 0xffffff71	; <UNPREDICTABLE>
d001507c:	44f8232c 	ldrbtmi	r2, [r8], #812	; 0x32c
d0015080:	830afb03 	movwhi	pc, #43779	; 0xab03	; <UNPREDICTABLE>
d0015084:	33faf503 	mvnscc	pc, #12582912	; 0xc00000
d0015088:	3041f893 	umaalcc	pc, r1, r3, r8	; <UNPREDICTABLE>
d001508c:	2b09b113 	blcs	0xd02814e0
d0015090:	af0bf47f 	svcge	0x000bf47f
d0015094:	018aea4f 	orreq	lr, sl, pc, asr #20
d0015098:	f7fe2000 			; <UNDEFINED> instruction: 0xf7fe2000
d001509c:	f641f907 			; <UNDEFINED> instruction: 0xf641f907
d00150a0:	f7fe0038 			; <UNDEFINED> instruction: 0xf7fe0038
d00150a4:	4a54f8e1 	bmi	0xd1553430
d00150a8:	6ad3447a 	bvs	0xcf4e6298
d00150ac:	f04f2b5b 			; <UNDEFINED> instruction: 0xf04f2b5b
d00150b0:	fb03032c 	blx	0xd00d5d6a
d00150b4:	f503230a 			; <UNDEFINED> instruction: 0xf503230a
d00150b8:	f89333fa 			; <UNDEFINED> instruction: 0xf89333fa
d00150bc:	f47f3041 			; <UNDEFINED> instruction: 0xf47f3041
d00150c0:	2b09aeb5 	blcs	0xd0280b9c
d00150c4:	ad41f47f 	cfstrdge	mvd15, [r1, #-508]	; 0xfffffe04
d00150c8:	20002101 	andcs	r2, r0, r1, lsl #2
d00150cc:	baa2f7ff 	blt	0xce8d30d0
d00150d0:	00007a9e 	muleq	r0, lr, sl
d00150d4:	fffffb07 			; <UNDEFINED> instruction: 0xfffffb07
d00150d8:	00007a26 	andeq	r7, r0, r6, lsr #20
d00150dc:	000079ee 	andeq	r7, r0, lr, ror #19
d00150e0:	fffffabf 			; <UNDEFINED> instruction: 0xfffffabf
d00150e4:	0000795c 	andeq	r7, r0, ip, asr r9
d00150e8:	0000791e 	andeq	r7, r0, lr, lsl r9
d00150ec:	fffffb09 			; <UNDEFINED> instruction: 0xfffffb09
d00150f0:	000078d6 	ldrdeq	r7, [r0], -r6
d00150f4:	fffffa07 			; <UNDEFINED> instruction: 0xfffffa07
d00150f8:	0000781e 	andeq	r7, r0, lr, lsl r8
d00150fc:	fffff8bf 			; <UNDEFINED> instruction: 0xfffff8bf
d0015100:	0000778e 	andeq	r7, r0, lr, lsl #15
d0015104:	0000776e 	andeq	r7, r0, lr, ror #14
d0015108:	fffff89d 			; <UNDEFINED> instruction: 0xfffff89d
d001510c:	fffff787 			; <UNDEFINED> instruction: 0xfffff787
d0015110:	00003d61 	andeq	r3, r0, r1, ror #26
d0015114:	00007716 	andeq	r7, r0, r6, lsl r7
d0015118:	000076fe 	strdeq	r7, [r0], -lr
d001511c:	fffff701 			; <UNDEFINED> instruction: 0xfffff701
d0015120:	00003c63 	andeq	r3, r0, r3, ror #24
d0015124:	fffff6ce 			; <UNDEFINED> instruction: 0xfffff6ce
d0015128:	00003d12 	andeq	r3, r0, r2, lsl sp
d001512c:	fffff7ff 			; <UNDEFINED> instruction: 0xfffff7ff
d0015130:	00007682 	andeq	r7, r0, r2, lsl #13
d0015134:	00007662 	andeq	r7, r0, r2, ror #12
d0015138:	fffff7bd 			; <UNDEFINED> instruction: 0xfffff7bd
d001513c:	000075d6 	ldrdeq	r7, [r0], -r6
d0015140:	fffff766 			; <UNDEFINED> instruction: 0xfffff766
d0015144:	fffff71f 			; <UNDEFINED> instruction: 0xfffff71f
d0015148:	000074dc 	ldrdeq	r7, [r0], -ip
d001514c:	fffff711 			; <UNDEFINED> instruction: 0xfffff711
d0015150:	fffff736 			; <UNDEFINED> instruction: 0xfffff736
d0015154:	0000748a 	andeq	r7, r0, sl, lsl #9
d0015158:	fffff72e 			; <UNDEFINED> instruction: 0xfffff72e
d001515c:	00007430 	andeq	r7, r0, r0, lsr r4
d0015160:	fffff692 			; <UNDEFINED> instruction: 0xfffff692
d0015164:	000073ae 	andeq	r7, r0, lr, lsr #7
d0015168:	00007338 	andeq	r7, r0, r8, lsr r3
d001516c:	0000731e 	andeq	r7, r0, lr, lsl r3
d0015170:	fffff5e8 			; <UNDEFINED> instruction: 0xfffff5e8
d0015174:	fffff5cb 			; <UNDEFINED> instruction: 0xfffff5cb
d0015178:	000061ca 	andeq	r6, r0, sl, asr #3
d001517c:	0000726c 	andeq	r7, r0, ip, ror #4
d0015180:	00007246 	andeq	r7, r0, r6, asr #4
d0015184:	fffff56c 			; <UNDEFINED> instruction: 0xfffff56c
d0015188:	00007208 	andeq	r7, r0, r8, lsl #4
d001518c:	fffff53f 			; <UNDEFINED> instruction: 0xfffff53f
d0015190:	fffff551 			; <UNDEFINED> instruction: 0xfffff551
d0015194:	ffffe5aa 			; <UNDEFINED> instruction: 0xffffe5aa
d0015198:	0000713a 	andeq	r7, r0, sl, lsr r1
d001519c:	fffff4cd 			; <UNDEFINED> instruction: 0xfffff4cd
d00151a0:	fffff4d4 			; <UNDEFINED> instruction: 0xfffff4d4
d00151a4:	000070cc 	andeq	r7, r0, ip, asr #1
d00151a8:	fffff4f4 			; <UNDEFINED> instruction: 0xfffff4f4
d00151ac:	fffff47a 			; <UNDEFINED> instruction: 0xfffff47a
d00151b0:	00007088 	andeq	r7, r0, r8, lsl #1
d00151b4:	fffff420 			; <UNDEFINED> instruction: 0xfffff420
d00151b8:	fffff41d 			; <UNDEFINED> instruction: 0xfffff41d
d00151bc:	00006ff8 	strdeq	r6, [r0], -r8
d00151c0:	fffff458 			; <UNDEFINED> instruction: 0xfffff458
d00151c4:	00006fa4 	andeq	r6, r0, r4, lsr #31
d00151c8:	fffff3f1 			; <UNDEFINED> instruction: 0xfffff3f1
d00151cc:	fffff408 			; <UNDEFINED> instruction: 0xfffff408
d00151d0:	fffff40b 			; <UNDEFINED> instruction: 0xfffff40b
d00151d4:	00006f14 	andeq	r6, r0, r4, lsl pc
d00151d8:	fffff3ec 			; <UNDEFINED> instruction: 0xfffff3ec
d00151dc:	fffff417 			; <UNDEFINED> instruction: 0xfffff417
d00151e0:	00006ece 	andeq	r6, r0, lr, asr #29
d00151e4:	fffff3cc 			; <UNDEFINED> instruction: 0xfffff3cc
d00151e8:	00006e80 	andeq	r6, r0, r0, lsl #29
d00151ec:	00006e74 	andeq	r6, r0, r4, ror lr
d00151f0:	ffffef62 			; <UNDEFINED> instruction: 0xffffef62
d00151f4:	00006e5e 	andeq	r6, r0, lr, asr lr
d00151f8:	00006e34 	andeq	r6, r0, r4, lsr lr

Disassembly of section .text.expression.constprop.0:

d00152c0 <.text.expression.constprop.0>:
d00152c0:	447b4bed 	ldrbtmi	r4, [fp], #-3053	; 0xfffff413
d00152c4:	4ff0e92d 	svcmi	0x00f0e92d
d00152c8:	b08b6a1a 	addlt	r6, fp, sl, lsl sl
d00152cc:	460e6a5f 			; <UNDEFINED> instruction: 0x460e6a5f
d00152d0:	9030f893 	mlasls	r0, r3, r8, pc	; <UNPREDICTABLE>
d00152d4:	a034f8d3 	ldrsbtge	pc, [r4], -r3	; <UNPREDICTABLE>
d00152d8:	90079203 	andls	r9, r7, r3, lsl #4
d00152dc:	820ae9d3 	andhi	lr, sl, #3457024	; 0x34c000
d00152e0:	33fff503 	mvnscc	pc, #12582912	; 0xc00000
d00152e4:	f8d39204 			; <UNDEFINED> instruction: 0xf8d39204
d00152e8:	3201212c 	andcc	r2, r1, #44, 2
d00152ec:	f8c32a20 			; <UNDEFINED> instruction: 0xf8c32a20
d00152f0:	d903212c 	stmdble	r3, {r2, r3, r5, r8, sp}
d00152f4:	447848e1 	ldrbtmi	r4, [r8], #-2273	; 0xfffff71f
d00152f8:	f91ef7fc 			; <UNDEFINED> instruction: 0xf91ef7fc
d00152fc:	0e03f1a6 	mvfeqdp	f7, f6
d0015300:	0000f1de 	ldrdeq	pc, [r0], -lr
d0015304:	000eeb40 	andeq	lr, lr, r0, asr #22
d0015308:	f894f7ff 			; <UNDEFINED> instruction: 0xf894f7ff
d001530c:	46054bdc 			; <UNDEFINED> instruction: 0x46054bdc
d0015310:	9306447b 	movwls	r4, #25723	; 0x647b
d0015314:	447b4bdb 	ldrbtmi	r4, [fp], #-3035	; 0xfffff425
d0015318:	f5039302 			; <UNDEFINED> instruction: 0xf5039302
d001531c:	33f8435d 	mvnscc	r4, #1946157057	; 0x74000001
d0015320:	9b069301 	blls	0xd01b9f2c
d0015324:	b9c46d9c 	stmiblt	r4, {r2, r3, r4, r7, r8, sl, fp, sp, lr}^
d0015328:	b02cf8d3 	ldrdlt	pc, [ip], -r3	; <UNPREDICTABLE>
d001532c:	0f5ef1bb 	svceq	0x005ef1bb
d0015330:	8122f000 	msrhi	CPSR_x, r0
d0015334:	80fef300 	rscshi	pc, lr, r0, lsl #6
d0015338:	0f2ff1bb 	svceq	0x002ff1bb
d001533c:	80f3f300 	rscshi	pc, r3, r0, lsl #6
d0015340:	0f24f1bb 	svceq	0x0024f1bb
d0015344:	80dff300 	sbcshi	pc, pc, r0, lsl #6
d0015348:	42a39b07 	adcmi	r9, r3, #7168	; 0x1c00
d001534c:	2d02dc05 	stccs	12, cr13, [r2, #-20]	; 0xffffffec
d0015350:	48cdd119 	stmiami	sp, {r0, r3, r4, r8, ip, lr, pc}^
d0015354:	f7fc4478 			; <UNDEFINED> instruction: 0xf7fc4478
d0015358:	1e73f8ef 	cdpne	8, 7, cr15, cr3, cr15, {7}
d001535c:	f2002b01 	vqdmulh.s<illegal width 8>	d2, d0, d1
d0015360:	2d028113 	stfcsd	f0, [r2, #-76]	; 0xffffffb4
d0015364:	4bc9d10b 	blmi	0xcf289798
d0015368:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d001536c:	4ac8b93a 	bmi	0xcf24385c
d0015370:	a068f8c3 	rsbge	pc, r8, r3, asr #17
d0015374:	e9c3447a 	stmib	r3, {r1, r3, r4, r5, r6, sl, lr}^
d0015378:	e9c38918 	stmib	r3, {r3, r4, r8, fp, pc}^
d001537c:	2e012716 	mcrcs	7, 0, r2, cr1, cr6, {0}
d0015380:	8113f040 	tsthi	r3, r0, asr #32	; <UNPREDICTABLE>
d0015384:	f7fde102 			; <UNDEFINED> instruction: 0xf7fde102
d0015388:	f46ffc9b 			; <UNDEFINED> instruction: 0xf46ffc9b
d001538c:	34017c8d 	strcc	r7, [r1], #-3213	; 0xfffff373
d0015390:	030ceb0b 	movweq	lr, #51979	; 0xcb0b
d0015394:	d82a2b01 	stmdale	sl!, {r0, r8, r9, fp, sp}
d0015398:	708ef5ab 	addvc	pc, lr, fp, lsr #11
d001539c:	41454245 	cmpmi	r5, r5, asr #4
d00153a0:	f7fe4628 			; <UNDEFINED> instruction: 0xf7fe4628
d00153a4:	2102fbb5 			; <UNDEFINED> instruction: 0x2102fbb5
d00153a8:	46204683 	strtmi	r4, [r0], -r3, lsl #13
d00153ac:	ff88f7ff 			; <UNDEFINED> instruction: 0xff88f7ff
d00153b0:	5020f44f 	eorpl	pc, r0, pc, asr #8
d00153b4:	ff58f7fd 			; <UNDEFINED> instruction: 0xff58f7fd
d00153b8:	f7fe2001 			; <UNDEFINED> instruction: 0xf7fe2001
d00153bc:	f7fefbbc 			; <UNDEFINED> instruction: 0xf7fefbbc
d00153c0:	9a01fb97 	bls	0xd0094224
d00153c4:	98024604 	stmdals	r2, {r2, r9, sl, lr}
d00153c8:	68122300 	ldmdavs	r2, {r8, r9, sp}
d00153cc:	6d804659 	stcvs	6, cr4, [r0, #356]	; 0x164
d00153d0:	fd76f7fe 	ldc2l	7, cr15, [r6, #-1016]!	; 0xfffffc08
d00153d4:	f7fd4628 			; <UNDEFINED> instruction: 0xf7fd4628
d00153d8:	9a01ffad 	bls	0xd0095294
d00153dc:	23009802 	movwcs	r9, #2050	; 0x802
d00153e0:	46216812 			; <UNDEFINED> instruction: 0x46216812
d00153e4:	f7fe6d80 			; <UNDEFINED> instruction: 0xf7fe6d80
d00153e8:	2500fd6b 	strcs	pc, [r0, #-3435]	; 0xfffff295
d00153ec:	f46fe799 	vld1.32	{d30}, [pc :64], r9
d00153f0:	2d03718b 	stfcss	f7, [r3, #-556]	; 0xfffffdd4
d00153f4:	0301eb0b 	movweq	lr, #6923	; 0x1b0b
d00153f8:	d10f9305 	tstle	pc, r5, lsl #6
d00153fc:	d90d2b01 	stmdble	sp, {r0, r8, r9, fp, sp}
d0015400:	447b4ba4 	ldrbtmi	r4, [fp], #-2980	; 0xfffff45c
d0015404:	2a006d9a 	bcs	0xd0030a74
d0015408:	4aa3d1a7 	bmi	0xce909aac
d001540c:	a068f8c3 	rsbge	pc, r8, r3, asr #17
d0015410:	e9c3447a 	stmib	r3, {r1, r3, r4, r5, r6, sl, lr}^
d0015414:	e9c38918 	stmib	r3, {r3, r4, r8, fp, pc}^
d0015418:	e79e2716 			; <UNDEFINED> instruction: 0xe79e2716
d001541c:	4003f24b 	andmi	pc, r3, fp, asr #4
d0015420:	ff22f7fd 			; <UNDEFINED> instruction: 0xff22f7fd
d0015424:	21024b9d 			; <UNDEFINED> instruction: 0x21024b9d
d0015428:	447b4620 	ldrbtmi	r4, [fp], #-1568	; 0xfffff9e0
d001542c:	6adb6a1a 	bvs	0xcf6efc9c
d0015430:	93089209 	movwls	r9, #33289	; 0x8209
d0015434:	ff44f7ff 			; <UNDEFINED> instruction: 0xff44f7ff
d0015438:	f64b4604 			; <UNDEFINED> instruction: 0xf64b4604
d001543c:	f7fd4006 			; <UNDEFINED> instruction: 0xf7fd4006
d0015440:	2d04ff13 	stccs	15, cr15, [r4, #-76]	; 0xffffffb4
d0015444:	9a099b08 	bls	0xd027c06c
d0015448:	80d5f000 	sbcshi	pc, r5, r0
d001544c:	d1102c04 	tstle	r0, r4, lsl #24
d0015450:	0f2bf1bb 	svceq	0x002bf1bb
d0015454:	80eef040 	rschi	pc, lr, r0, asr #32
d0015458:	2b011eeb 	blcs	0xd005d00c
d001545c:	80eef240 	rschi	pc, lr, r0, asr #4
d0015460:	25042089 	strcs	r2, [r4, #-137]	; 0xffffff77
d0015464:	ff00f7fd 			; <UNDEFINED> instruction: 0xff00f7fd
d0015468:	0008f641 	andeq	pc, r8, r1, asr #12
d001546c:	fefcf7fd 	mrc2	7, 7, pc, cr12, cr13, {7}
d0015470:	2d03e757 	stccs	7, cr14, [r3, #-348]	; 0xfffffea4
d0015474:	2c03d001 	stccs	0, cr13, [r3], {1}
d0015478:	9904d136 	stmdbls	r4, {r1, r2, r4, r5, r8, ip, lr, pc}
d001547c:	7381f5a3 	orrvc	pc, r1, #683671552	; 0x28c00000
d0015480:	7181f5a1 	orrvc	pc, r1, r1, lsr #11
d0015484:	bf972901 	svclt	0x00972901
d0015488:	21009903 	tstcs	r0, r3, lsl #18
d001548c:	f181fab1 			; <UNDEFINED> instruction: 0xf181fab1
d0015490:	2b010949 	blcs	0xd00579bc
d0015494:	fab2bf96 	blx	0xcecc52f4
d0015498:	2200f282 	andcs	pc, r0, #536870920	; 0x20000008
d001549c:	2d040952 	vstrcs.16	s0, [r4, #-164]	; 0xffffff5c	; <UNPREDICTABLE>
d00154a0:	2d03d009 	stccs	0, cr13, [r3, #-36]	; 0xffffffdc
d00154a4:	80bdf040 	adcshi	pc, sp, r0, asr #32
d00154a8:	2c013c03 	stccs	12, cr3, [r1], {3}
d00154ac:	9b05d80b 	blls	0xd018b4e0
d00154b0:	d8082b01 	stmdale	r8, {r0, r8, r9, fp, sp}
d00154b4:	1ee3e013 	mcrne	0, 7, lr, cr3, cr3, {0}
d00154b8:	d9f82b01 	ldmible	r8!, {r0, r8, r9, fp, sp}^
d00154bc:	d0022c04 	andle	r2, r2, r4, lsl #24
d00154c0:	2a00b90c 	bcs	0xd00438f8
d00154c4:	4b76d1f3 	blmi	0xd1dc9c98
d00154c8:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d00154cc:	4a75b93a 	bmi	0xd1d839bc
d00154d0:	a068f8c3 	rsbge	pc, r8, r3, asr #17
d00154d4:	e9c3447a 	stmib	r3, {r1, r3, r4, r5, r6, sl, lr}^
d00154d8:	e9c38918 	stmib	r3, {r3, r4, r8, fp, pc}^
d00154dc:	21012716 	tstcs	r1, r6, lsl r7
d00154e0:	f7fe4658 			; <UNDEFINED> instruction: 0xf7fe4658
d00154e4:	e780fb92 			; <UNDEFINED> instruction: 0xe780fb92
d00154e8:	d0022d01 	andle	r2, r2, r1, lsl #26
d00154ec:	42551e62 	subsmi	r1, r5, #1568	; 0x620
d00154f0:	46294155 			; <UNDEFINED> instruction: 0x46294155
d00154f4:	f7fe4658 			; <UNDEFINED> instruction: 0xf7fe4658
d00154f8:	1e05fb88 	vmlane.f64	d15, d21, d8
d00154fc:	2501bf18 	strcs	fp, [r1, #-3864]	; 0xfffff0e8
d0015500:	2402e70f 	strcs	lr, [r2], #-1807	; 0xfffff8f1
d0015504:	f1abe720 			; <UNDEFINED> instruction: 0xf1abe720
d0015508:	2b0a0325 	blcs	0xd02961a4
d001550c:	e8dfd809 	ldm	pc, {r0, r3, fp, ip, lr, pc}^	; <UNPREDICTABLE>
d0015510:	3731f003 	ldrcc	pc, [r1, -r3]!
d0015514:	31080808 	tstcc	r8, r8, lsl #16
d0015518:	08060806 	stmdaeq	r6, {r1, r2, fp}
d001551c:	24080031 	strcs	r0, [r8], #-49	; 0xffffffcf
d0015520:	2400e712 	strcs	lr, [r0], #-1810	; 0xfffff8ee
d0015524:	f02be710 			; <UNDEFINED> instruction: 0xf02be710
d0015528:	2b3c0302 	blcs	0xd0f16138
d001552c:	2400bf14 	strcs	fp, [r0], #-3860	; 0xfffff0ec
d0015530:	e7092407 	str	r2, [r9, -r7, lsl #8]
d0015534:	0f7cf1bb 	svceq	0x007cf1bb
d0015538:	f46fd024 	vld4.8	{d29-d32}, [pc :128], r4
d001553c:	445b738b 	ldrbmi	r7, [fp], #-907	; 0xfffffc75
d0015540:	f63f2b05 			; <UNDEFINED> instruction: 0xf63f2b05
d0015544:	2b05af01 	blcs	0xd0181150
d0015548:	a202d8eb 	andge	sp, r2, #15400960	; 0xeb0000
d001554c:	3023f852 	eorcc	pc, r3, r2, asr r8	; <UNPREDICTABLE>
d0015550:	4710441a 			; <UNDEFINED> instruction: 0x4710441a
d0015554:	00000019 	andeq	r0, r0, r9, lsl r0
d0015558:	00000019 	andeq	r0, r0, r9, lsl r0
d001555c:	0000001d 	andeq	r0, r0, sp, lsl r0
d0015560:	0000001d 	andeq	r0, r0, sp, lsl r0
d0015564:	ffffffaf 			; <UNDEFINED> instruction: 0xffffffaf
d0015568:	00000029 	andeq	r0, r0, r9, lsr #32
d001556c:	e6eb2406 	strbt	r2, [fp], r6, lsl #8
d0015570:	e6e92407 	strbt	r2, [r9], r7, lsl #8
d0015574:	e6e72409 	strbt	r2, [r7], r9, lsl #8
d0015578:	e6e52404 	strbt	r2, [r5], r4, lsl #8
d001557c:	e6e32401 	strbt	r2, [r3], r1, lsl #8
d0015580:	e6e12405 	strbt	r2, [r1], r5, lsl #8
d0015584:	e6df2403 	ldrb	r2, [pc], r3, lsl #8
d0015588:	d11b2e01 	tstle	fp, r1, lsl #28
d001558c:	2b011eeb 	blcs	0xd005d140
d0015590:	4b45d80b 	blmi	0xd118b5c4
d0015594:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d0015598:	4a44b93a 	bmi	0xd1143a88
d001559c:	f8c3447a 			; <UNDEFINED> instruction: 0xf8c3447a
d00155a0:	e9c3a068 	stmib	r3, {r3, r5, r6, sp, pc}^
d00155a4:	e9c32716 	stmib	r3, {r1, r2, r4, r8, r9, sl, sp}^
d00155a8:	4b418918 	blmi	0xd1077a10
d00155ac:	447b4628 	ldrbtmi	r4, [fp], #-1576	; 0xfffff9d8
d00155b0:	33fff503 	mvnscc	pc, #12582912	; 0xc00000
d00155b4:	212cf8d3 	ldrdcs	pc, [ip, -r3]!
d00155b8:	f8c33a01 			; <UNDEFINED> instruction: 0xf8c33a01
d00155bc:	b00b212c 	andlt	r2, fp, ip, lsr #2
d00155c0:	8ff0e8bd 	svchi	0x00f0e8bd
d00155c4:	d1f02e04 	mvnsle	r2, r4, lsl #28
d00155c8:	2b011eeb 	blcs	0xd005d17c
d00155cc:	9b04d9ed 	blls	0xd014bd88
d00155d0:	7381f5a3 	orrvc	pc, r1, #683671552	; 0x28c00000
d00155d4:	d8022b01 	stmdale	r2, {r0, r8, r9, fp, sp}
d00155d8:	2b009b03 	blcs	0xd003c1ec
d00155dc:	4b35d0e5 	blmi	0xd0d89978
d00155e0:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d00155e4:	d1e02a00 	mvnle	r2, r0, lsl #20
d00155e8:	447a4a33 	ldrbtmi	r4, [sl], #-2611	; 0xfffff5cd
d00155ec:	2d04e7d7 	stccs	7, cr14, [r4, #-860]	; 0xfffffca4
d00155f0:	af66f43f 	svcge	0x0066f43f
d00155f4:	f1bbe767 			; <UNDEFINED> instruction: 0xf1bbe767
d00155f8:	d12e0f2b 			; <UNDEFINED> instruction: 0xd12e0f2b
d00155fc:	f43f2c04 			; <UNDEFINED> instruction: 0xf43f2c04
d0015600:	2c03af2b 	stccs	15, cr10, [r3], {43}	; 0x2b
d0015604:	2080d01a 	addcs	sp, r0, sl, lsl r0
d0015608:	fe2ef7fd 	mcr2	7, 1, pc, cr14, cr13, {7}	; <UNPREDICTABLE>
d001560c:	2308f641 	movwcs	pc, #34369	; 0x8641	; <UNPREDICTABLE>
d0015610:	0008f641 	andeq	pc, r8, r1, asr #12
d0015614:	0f2bf1bb 	svceq	0x002bf1bb
d0015618:	4618bf18 	sadd16mi	fp, r8, r8
d001561c:	fe24f7fd 	mcr2	7, 1, pc, cr4, cr13, {7}	; <UNPREDICTABLE>
d0015620:	2c04e67f 	stccs	6, cr14, [r4], {127}	; 0x7f
d0015624:	2d00d1e3 	stfcsd	f5, [r0, #-908]	; 0xfffffc74
d0015628:	af4df47f 	svcge	0x004df47f
d001562c:	f47f2900 			; <UNDEFINED> instruction: 0xf47f2900
d0015630:	e748af3e 	smlaldx	sl, r8, lr, pc	; <UNPREDICTABLE>
d0015634:	0f2df1bb 	svceq	0x002df1bb
d0015638:	af1ff47f 	svcge	0x001ff47f
d001563c:	447b4b1f 	ldrbtmi	r4, [fp], #-2847	; 0xfffff4e1
d0015640:	2a006d9a 	bcs	0xd0030cb0
d0015644:	ae6df47f 	mcrge	4, 3, pc, cr13, cr15, {3}	; <UNPREDICTABLE>
d0015648:	f8c34a1d 			; <UNDEFINED> instruction: 0xf8c34a1d
d001564c:	447aa068 	ldrbtmi	sl, [sl], #-104	; 0xffffff98
d0015650:	8918e9c3 	ldmdbhi	r8, {r0, r1, r6, r7, r8, fp, sp, lr, pc}
d0015654:	2716e9c3 	ldrcs	lr, [r6, -r3, asr #19]
d0015658:	f1bbe663 			; <UNDEFINED> instruction: 0xf1bbe663
d001565c:	f47f0f2d 			; <UNDEFINED> instruction: 0xf47f0f2d
d0015660:	2c04af0c 	stccs	15, cr10, [r4], {12}
d0015664:	f641d1cd 			; <UNDEFINED> instruction: 0xf641d1cd
d0015668:	f7fd2008 			; <UNDEFINED> instruction: 0xf7fd2008
d001566c:	f44ffdfd 			; <UNDEFINED> instruction: 0xf44ffdfd
d0015670:	f7fd5084 			; <UNDEFINED> instruction: 0xf7fd5084
d0015674:	e6b8fdf9 			; <UNDEFINED> instruction: 0xe6b8fdf9
d0015678:	00006c1a 	andeq	r6, r0, sl, lsl ip
d001567c:	ffffec91 			; <UNDEFINED> instruction: 0xffffec91
d0015680:	00006bcc 	andeq	r6, r0, ip, asr #23
d0015684:	00006bc6 	andeq	r6, r0, r6, asr #23
d0015688:	fffff06c 			; <UNDEFINED> instruction: 0xfffff06c
d001568c:	00006b74 	andeq	r6, r0, r4, ror fp
d0015690:	fffffed5 			; <UNDEFINED> instruction: 0xfffffed5
d0015694:	00006ada 	ldrdeq	r6, [r0], -sl
d0015698:	ffffefd6 			; <UNDEFINED> instruction: 0xffffefd6
d001569c:	00006ab2 			; <UNDEFINED> instruction: 0x00006ab2
d00156a0:	00006a14 	andeq	r6, r0, r4, lsl sl
d00156a4:	fffffd3f 			; <UNDEFINED> instruction: 0xfffffd3f
d00156a8:	00006948 	andeq	r6, r0, r8, asr #18
d00156ac:	fffffcd1 			; <UNDEFINED> instruction: 0xfffffcd1
d00156b0:	0000692e 	andeq	r6, r0, lr, lsr #18
d00156b4:	000068fc 	strdeq	r6, [r0], -ip
d00156b8:	fffffcac 			; <UNDEFINED> instruction: 0xfffffcac
d00156bc:	0000689e 	muleq	r0, lr, r8
d00156c0:	fffffbaa 			; <UNDEFINED> instruction: 0xfffffbaa

Disassembly of section .text.local_declaration.constprop.0:

d0015824 <.text.local_declaration.constprop.0>:
d0015824:	4ff0e92d 	svcmi	0x00f0e92d
d0015828:	1007f240 	andne	pc, r7, r0, asr #4
d001582c:	f7fdb091 			; <UNDEFINED> instruction: 0xf7fdb091
d0015830:	2800fa65 	stmdacs	r0, {r0, r2, r5, r6, r9, fp, ip, sp, lr, pc}
d0015834:	4ba5d040 	blmi	0xce98993c
d0015838:	6ada447b 	bvs	0xcf6a6a2c
d001583c:	d1072a28 	tstle	r7, r8, lsr #20
d0015840:	2b2a6cdb 	blcs	0xd0ab0bb4
d0015844:	2000d104 	andcs	sp, r0, r4, lsl #2
d0015848:	f888f7fe 			; <UNDEFINED> instruction: 0xf888f7fe
d001584c:	e0672401 	rsb	r2, r7, r1, lsl #8
d0015850:	f7fd202a 			; <UNDEFINED> instruction: 0xf7fd202a
d0015854:	1e05fa53 			; <UNDEFINED> instruction: 0x1e05fa53
d0015858:	250abf18 	strcs	fp, [sl, #-3864]	; 0xfffff0e8
d001585c:	ae084c9c 	mcrge	12, 0, r4, cr8, cr12, {4}
d0015860:	f104447c 			; <UNDEFINED> instruction: 0xf104447c
d0015864:	f8d40718 			; <UNDEFINED> instruction: 0xf8d40718
d0015868:	f8d4b024 			; <UNDEFINED> instruction: 0xf8d4b024
d001586c:	f894a028 			; <UNDEFINED> instruction: 0xf894a028
d0015870:	cf0f8030 	svcgt	0x000f8030
d0015874:	e897c60f 	ldm	r7, {r0, r1, r2, r3, r9, sl, lr, pc}
d0015878:	e886000f 	stm	r6, {r0, r1, r2, r3}
d001587c:	4995000f 	ldmibmi	r5, {r0, r1, r2, r3}
d0015880:	1001f240 	andne	pc, r1, r0, asr #4
d0015884:	ae086b67 	vmlsge.f64	d6, d8, d23
d0015888:	f7fd4479 			; <UNDEFINED> instruction: 0xf7fd4479
d001588c:	2800fa65 	stmdacs	r0, {r0, r2, r5, r6, r9, fp, ip, sp, lr, pc}
d0015890:	205bd0dc 	ldrsbcs	sp, [fp], #-12
d0015894:	fa32f7fd 	blx	0xd0cd3890
d0015898:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d001589c:	2d0080ea 	stccs	0, cr8, [r0, #-936]	; 0xfffffc58
d00158a0:	6da3d044 	stcvs	0, cr13, [r3, #272]!	; 0x110
d00158a4:	d1d12b00 	bicsle	r2, r1, r0, lsl #22
d00158a8:	66a74b8b 	strtvs	r4, [r7], fp, lsl #23
d00158ac:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d00158b0:	e9c4a818 	stmib	r4, {r3, r4, fp, sp, pc}^
d00158b4:	e7c93b16 	bfi	r3, r6, (invalid: 22:9)
d00158b8:	7084f44f 	addvc	pc, r4, pc, asr #8
d00158bc:	fa1ef7fd 	blx	0xd07d38b8
d00158c0:	b1704604 	cmnlt	r0, r4, lsl #12
d00158c4:	447b4b85 	ldrbtmi	r4, [fp], #-2949	; 0xfffff47b
d00158c8:	2a286ada 	bcs	0xd0a30438
d00158cc:	6cdbd104 	ldfvsp	f5, [fp], {4}
d00158d0:	d1012b2a 	tstle	r1, sl, lsr #22
d00158d4:	e7b72001 	ldr	r2, [r7, r1]!
d00158d8:	44784881 	ldrbtmi	r4, [r8], #-2177	; 0xfffff77f
d00158dc:	fe2cf7fb 	mcr2	7, 1, pc, cr12, cr11, {7}	; <UNPREDICTABLE>
d00158e0:	4b80e7b4 	blmi	0xce04f7b8
d00158e4:	1201f240 	andne	pc, r1, #64, 4
d00158e8:	6ad9447b 	bvs	0xcf666adc
d00158ec:	d1174291 			; <UNDEFINED> instruction: 0xd1174291
d00158f0:	0106e9d3 	ldrdeq	lr, [r6, -r3]
d00158f4:	fbdaf7fd 	blx	0xcf6d38f2
d00158f8:	da112800 	ble	0xd045f900
d00158fc:	4478487a 	ldrbtmi	r4, [r8], #-2170	; 0xfffff786
d0015900:	fa0ef7fd 	blx	0xd03d38fc
d0015904:	4879b980 	ldmdami	r9!, {r7, r8, fp, ip, sp, pc}^
d0015908:	f7fd4478 			; <UNDEFINED> instruction: 0xf7fd4478
d001590c:	b108fa09 	tstlt	r8, r9, lsl #20	; <UNPREDICTABLE>
d0015910:	e7a32505 	str	r2, [r3, r5, lsl #10]!
d0015914:	44784876 	ldrbtmi	r4, [r8], #-2166	; 0xfffff78a
d0015918:	fa02f7fd 	blx	0xd00d3914
d001591c:	d1f72800 	mvnsle	r2, r0, lsl #16
d0015920:	b0114620 	andslt	r4, r1, r0, lsr #12
d0015924:	8ff0e8bd 	svchi	0x00f0e8bd
d0015928:	e7972501 	ldr	r2, [r7, r1, lsl #10]
d001592c:	f5a36ae3 			; <UNDEFINED> instruction: 0xf5a36ae3
d0015930:	2b017381 	blcs	0xd007273c
d0015934:	f8d4d80c 			; <UNDEFINED> instruction: 0xf8d4d80c
d0015938:	f1b99020 			; <UNDEFINED> instruction: 0xf1b99020
d001593c:	d0070f00 	andle	r0, r7, r0, lsl #30
d0015940:	35fff504 	ldrbcc	pc, [pc, #1284]!	; 0xd0015e4c	; <UNPREDICTABLE>
d0015944:	3120f8d5 	ldrdcc	pc, [r0, -r5]!
d0015948:	0340f1c3 	movteq	pc, #451	; 0x1c3	; <UNPREDICTABLE>
d001594c:	d9124599 	ldmdble	r2, {r0, r3, r4, r7, r8, sl, lr}
d0015950:	447b4b68 	ldrbtmi	r4, [fp], #-2920	; 0xfffff498
d0015954:	2a006d9a 	bcs	0xd0030fc4
d0015958:	af78f47f 	svcge	0x0078f47f
d001595c:	6a5c4d66 	bvs	0xd1728efc
d0015960:	447d6a98 	ldrbtmi	r6, [sp], #-2712	; 0xfffff568
d0015964:	f8936b5a 			; <UNDEFINED> instruction: 0xf8936b5a
d0015968:	669a1030 			; <UNDEFINED> instruction: 0x669a1030
d001596c:	5416e9c3 	ldrpl	lr, [r6], #-2499	; 0xfffff63d
d0015970:	0118e9c3 	tsteq	r8, r3, asr #19
d0015974:	f7fde76a 			; <UNDEFINED> instruction: 0xf7fde76a
d0015978:	4960f9a3 	stmdbmi	r0!, {r0, r1, r5, r7, r8, fp, ip, sp, lr, pc}^
d001597c:	4479205d 	ldrbtmi	r2, [r9], #-93	; 0xffffffa3
d0015980:	f9eaf7fd 			; <UNDEFINED> instruction: 0xf9eaf7fd
d0015984:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0015988:	2309af61 	movwcs	sl, #40801	; 0x9f61
d001598c:	8038f88d 	eorshi	pc, r8, sp, lsl #17
d0015990:	a030f8cd 	eorsge	pc, r0, sp, asr #17
d0015994:	ab109304 	blge	0xd043a5ac
d0015998:	f8cd970f 			; <UNDEFINED> instruction: 0xf8cd970f
d001599c:	e913b02c 	ldmdb	r3, {r2, r3, r5, ip, sp, pc}
d00159a0:	e88d000f 	stm	sp, {r0, r1, r2, r3}
d00159a4:	e896000f 	ldm	r6, {r0, r1, r2, r3}
d00159a8:	f7fd000f 			; <UNDEFINED> instruction: 0xf7fd000f
d00159ac:	6da3fbc1 			; <UNDEFINED> instruction: 0x6da3fbc1
d00159b0:	2b004680 	blcs	0xd00273b8
d00159b4:	af4af47f 	svcge	0x004af47f
d00159b8:	462e2701 	strtmi	r2, [lr], -r1, lsl #14
d00159bc:	0a2cf04f 	beq	0xd0b51b00
d00159c0:	f8d645b9 			; <UNDEFINED> instruction: 0xf8d645b9
d00159c4:	d10f3120 	tstle	pc, r0, lsr #2
d00159c8:	2124f8d6 	ldrdcs	pc, [r4, -r6]!
d00159cc:	429a203d 	addsmi	r2, sl, #61	; 0x3d
d00159d0:	f8c6bf38 			; <UNDEFINED> instruction: 0xf8c6bf38
d00159d4:	f7fd3124 			; <UNDEFINED> instruction: 0xf7fd3124
d00159d8:	b9d8f991 	ldmiblt	r8, {r0, r4, r7, r8, fp, ip, sp, lr, pc}^
d00159dc:	44794948 	ldrbtmi	r4, [r9], #-2376	; 0xfffff6b8
d00159e0:	f7fd203b 			; <UNDEFINED> instruction: 0xf7fd203b
d00159e4:	e731f9b9 			; <UNDEFINED> instruction: 0xe731f9b9
d00159e8:	fb0a1c5a 	blx	0xd029cb5a
d00159ec:	21004303 	tstcs	r0, r3, lsl #6
d00159f0:	b128f896 	msrlt	CPSR_f, r6	; <illegal shifter operand>
d00159f4:	35faf503 	ldrbcc	pc, [sl, #1283]!	; 0x503	; <UNPREDICTABLE>
d00159f8:	2120f8c6 	smlawtcs	r0, r6, r8, pc	; <UNPREDICTABLE>
d00159fc:	3701222c 	strcc	r2, [r1, -ip, lsr #4]
d0015a00:	0020f105 	eoreq	pc, r0, r5, lsl #2
d0015a04:	fda0f003 	stc2	0, cr15, [r0, #12]!
d0015a08:	f885230b 			; <UNDEFINED> instruction: 0xf885230b
d0015a0c:	f885b040 			; <UNDEFINED> instruction: 0xf885b040
d0015a10:	e7d53041 	ldrb	r3, [r5, r1, asr #32]
d0015a14:	207b493b 	rsbscs	r4, fp, fp, lsr r9
d0015a18:	91074479 	tstls	r7, r9, ror r4
d0015a1c:	f99cf7fd 			; <UNDEFINED> instruction: 0xf99cf7fd
d0015a20:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0015a24:	4a38af13 	bmi	0xd0e41678
d0015a28:	6ad3447a 	bvs	0xcf4e6c18
d0015a2c:	7381f5a3 	orrvc	pc, r1, #683671552	; 0x28c00000
d0015a30:	d8022b01 	stmdale	r2, {r0, r8, r9, fp, sp}
d0015a34:	99076a14 	stmdbls	r7, {r2, r4, r9, fp, sp, lr}
d0015a38:	4834b114 	ldmdami	r4!, {r2, r4, r8, ip, sp, pc}
d0015a3c:	e74d4478 	smlsldx	r4, sp, r8, r4
d0015a40:	f7fd9107 			; <UNDEFINED> instruction: 0xf7fd9107
d0015a44:	202cf93d 	eorcs	pc, ip, sp, lsr r9	; <UNPREDICTABLE>
d0015a48:	f958f7fd 			; <UNDEFINED> instruction: 0xf958f7fd
d0015a4c:	207d9907 	rsbscs	r9, sp, r7, lsl #18
d0015a50:	f982f7fd 			; <UNDEFINED> instruction: 0xf982f7fd
d0015a54:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0015a58:	4620aef9 			; <UNDEFINED> instruction: 0x4620aef9
d0015a5c:	fc6af7fd 	stc2l	7, cr15, [sl], #-1012	; 0xfffffc0c
d0015a60:	0004eb08 	andeq	lr, r4, r8, lsl #22
d0015a64:	21003401 	tstcs	r0, r1, lsl #8
d0015a68:	fcb1f7fd 	ldc2	7, cr15, [r1], #1012	; 0x3f4
d0015a6c:	d8f742a7 	ldmle	r7!, {r0, r1, r2, r5, r7, r9, lr}^
d0015a70:	b2ebe7b4 	rsclt	lr, fp, #180, 14	; 0x2d00000
d0015a74:	a030f8cd 	eorsge	pc, r0, sp, asr #17
d0015a78:	8038f88d 	eorshi	pc, r8, sp, lsl #17
d0015a7c:	ab109304 	blge	0xd043a694
d0015a80:	f8cd970f 			; <UNDEFINED> instruction: 0xf8cd970f
d0015a84:	e913b02c 	ldmdb	r3, {r2, r3, r5, ip, sp, pc}
d0015a88:	e88d000f 	stm	sp, {r0, r1, r2, r3}
d0015a8c:	e896000f 	ldm	r6, {r0, r1, r2, r3}
d0015a90:	f7fd000f 			; <UNDEFINED> instruction: 0xf7fd000f
d0015a94:	4604fb4d 	strmi	pc, [r4], -sp, asr #22
d0015a98:	f7fd203d 			; <UNDEFINED> instruction: 0xf7fd203d
d0015a9c:	b188f92f 	orrlt	pc, r8, pc, lsr #18
d0015aa0:	f04f2d0a 			; <UNDEFINED> instruction: 0xf04f2d0a
d0015aa4:	bf0c0001 	svclt	0x000c0001
d0015aa8:	21012104 	tstcs	r1, r4, lsl #2
d0015aac:	fc08f7ff 	stc2	7, cr15, [r8], {255}	; 0xff
d0015ab0:	d1032d05 	tstle	r3, r5, lsl #26
d0015ab4:	20c0f24b 	sbccs	pc, r0, fp, asr #4
d0015ab8:	fbd6f7fd 	blx	0xcf5d3ab6
d0015abc:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d0015ac0:	fc85f7fd 	stc2	7, cr15, [r5], {253}	; 0xfd
d0015ac4:	44794912 	ldrbtmi	r4, [r9], #-2322	; 0xfffff6ee
d0015ac8:	bf00e78a 	svclt	0x0000e78a
d0015acc:	000066a4 	andeq	r6, r0, r4, lsr #13
d0015ad0:	0000667c 	andeq	r6, r0, ip, ror r6
d0015ad4:	fffffe8b 			; <UNDEFINED> instruction: 0xfffffe8b
d0015ad8:	fffffe86 			; <UNDEFINED> instruction: 0xfffffe86
d0015adc:	00006616 	andeq	r6, r0, r6, lsl r6
d0015ae0:	fffffde6 			; <UNDEFINED> instruction: 0xfffffde6
d0015ae4:	000065f4 	strdeq	r6, [r0], -r4
d0015ae8:	fffffdfb 			; <UNDEFINED> instruction: 0xfffffdfb
d0015aec:	fffffdfa 			; <UNDEFINED> instruction: 0xfffffdfa
d0015af0:	fffffdf5 			; <UNDEFINED> instruction: 0xfffffdf5
d0015af4:	0000658a 	andeq	r6, r0, sl, lsl #11
d0015af8:	fffffdf4 			; <UNDEFINED> instruction: 0xfffffdf4
d0015afc:	fffffe09 			; <UNDEFINED> instruction: 0xfffffe09
d0015b00:	fffffdcd 			; <UNDEFINED> instruction: 0xfffffdcd
d0015b04:	fffffdbe 			; <UNDEFINED> instruction: 0xfffffdbe
d0015b08:	000064b4 			; <UNDEFINED> instruction: 0x000064b4
d0015b0c:	fffffd9a 			; <UNDEFINED> instruction: 0xfffffd9a
d0015b10:	fffffd3a 			; <UNDEFINED> instruction: 0xfffffd3a

Disassembly of section .text.simple_expression.constprop.0:

d0015bbc <.text.simple_expression.constprop.0>:
d0015bbc:	447b4b74 	ldrbtmi	r4, [fp], #-2932	; 0xfffff48c
d0015bc0:	4ff7e92d 	svcmi	0x00f7e92d
d0015bc4:	2d3d6cdd 	ldccs	12, cr6, [sp, #-884]!	; 0xfffffc8c
d0015bc8:	f5a5d014 			; <UNDEFINED> instruction: 0xf5a5d014
d0015bcc:	2d017590 	cfstr32cs	mvfx7, [r1, #-576]	; 0xfffffdc0
d0015bd0:	2500bf8c 	strcs	fp, [r0, #-3980]	; 0xfffff074
d0015bd4:	4f6f2501 	svcmi	0x006f2501
d0015bd8:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d0015bdc:	6afa447f 	bvs	0xcfea6de0
d0015be0:	d100429a 			; <UNDEFINED> instruction: 0xd100429a
d0015be4:	2103b945 	tstcs	r3, r5, asr #18
d0015be8:	b0032001 	andlt	r2, r3, r1
d0015bec:	4ff0e8bd 	svcmi	0x00f0e8bd
d0015bf0:	bb66f7ff 	bllt	0xd19d3bf4
d0015bf4:	e7ee2501 	strb	r2, [lr, r1, lsl #10]!
d0015bf8:	6106e9d7 	ldrdvs	lr, [r6, -r7]
d0015bfc:	46306a7b 			; <UNDEFINED> instruction: 0x46306a7b
d0015c00:	f8d79101 			; <UNDEFINED> instruction: 0xf8d79101
d0015c04:	f8978028 			; <UNDEFINED> instruction: 0xf8978028
d0015c08:	f8d79030 			; <UNDEFINED> instruction: 0xf8d79030
d0015c0c:	9300a034 	movwls	sl, #52	; 0x34
d0015c10:	fa4cf7fd 	blx	0xd1353c0c
d0015c14:	99011e04 	stmdbls	r1, {r2, r9, sl, fp, ip}
d0015c18:	80b0f280 	adcshi	pc, r0, r0, lsl #5
d0015c1c:	f7fa4630 			; <UNDEFINED> instruction: 0xf7fa4630
d0015c20:	1e06ff4b 	cdpne	15, 0, cr15, cr6, cr11, {2}
d0015c24:	232cdb17 			; <UNDEFINED> instruction: 0x232cdb17
d0015c28:	7706fb03 	strvc	pc, [r6, -r3, lsl #22]
d0015c2c:	37aff507 	strcc	pc, [pc, r7, lsl #10]!
d0015c30:	702cf897 	mlavc	ip, r7, r8, pc	; <UNPREDICTABLE>
d0015c34:	2b021ffb 	blcs	0xd009dc28
d0015c38:	4b57d81b 	blmi	0xd160bcac
d0015c3c:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d0015c40:	4a56b9a2 	bmi	0xd15c42d0
d0015c44:	659a447a 	ldrvs	r4, [sl, #1146]	; 0x47a
d0015c48:	f8c39a00 			; <UNDEFINED> instruction: 0xf8c39a00
d0015c4c:	65daa068 	ldrbvs	sl, [sl, #104]	; 0x68
d0015c50:	8918e9c3 	ldmdbhi	r8, {r0, r1, r6, r7, r8, fp, sp, lr, pc}
d0015c54:	6dbbe00a 	ldcvs	0, cr14, [fp, #40]!	; 0x28
d0015c58:	4b51b943 	blmi	0xd148416c
d0015c5c:	a068f8c7 	rsbge	pc, r8, r7, asr #17
d0015c60:	65bb447b 	ldrvs	r4, [fp, #1147]!	; 0x47b
d0015c64:	e9c79b00 	stmib	r7, {r8, r9, fp, ip, pc}^
d0015c68:	65fb8918 	ldrbvs	r8, [fp, #2328]!	; 0x918
d0015c6c:	e8bdb003 	pop	{r0, r1, ip, sp, pc}
d0015c70:	1eba8ff0 	mrcne	15, 5, r8, cr10, cr0, {7}
d0015c74:	d80c2a09 	stmdale	ip, {r0, r3, r9, fp, sp}
d0015c78:	2315f240 	tstcs	r5, #64, 4	; <UNPREDICTABLE>
d0015c7c:	07db40d3 			; <UNDEFINED> instruction: 0x07db40d3
d0015c80:	4b48d507 	blmi	0xd124b0a4
d0015c84:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d0015c88:	d1ef2a00 	mvnle	r2, r0, lsl #20
d0015c8c:	447a4a46 	ldrbtmi	r4, [sl], #-2630	; 0xfffff5ba
d0015c90:	f7fde7d9 			; <UNDEFINED> instruction: 0xf7fde7d9
d0015c94:	4845f815 	stmdami	r5, {r0, r2, r4, fp, ip, sp, lr, pc}^
d0015c98:	f8d04478 			; <UNDEFINED> instruction: 0xf8d04478
d0015c9c:	9001b02c 	andls	fp, r1, ip, lsr #32
d0015ca0:	f80ef7fd 			; <UNDEFINED> instruction: 0xf80ef7fd
d0015ca4:	98012f0c 	stmdals	r1, {r2, r3, r8, r9, sl, fp, sp}
d0015ca8:	f1bbd11e 			; <UNDEFINED> instruction: 0xf1bbd11e
d0015cac:	d00c0f3d 	andle	r0, ip, sp, lsr pc
d0015cb0:	2b006d83 	blcs	0xd00312c4
d0015cb4:	4b3ed1da 	blmi	0xd0fca424
d0015cb8:	a068f8c0 	rsbge	pc, r8, r0, asr #17
d0015cbc:	6583447b 	strvs	r4, [r3, #1147]	; 0x47b
d0015cc0:	e9c09b00 	stmib	r0, {r8, r9, fp, ip, pc}^
d0015cc4:	65c38918 	strbvs	r8, [r3, #2328]	; 0x918
d0015cc8:	232ce7d0 			; <UNDEFINED> instruction: 0x232ce7d0
d0015ccc:	0004fb03 	andeq	pc, r4, r3, lsl #22
d0015cd0:	30faf500 	rscscc	pc, sl, r0, lsl #10
d0015cd4:	f7fd3042 			; <UNDEFINED> instruction: 0xf7fd3042
d0015cd8:	2100fcd7 	ldrdcs	pc, [r0, -r7]
d0015cdc:	b0034620 	andlt	r4, r3, r0, lsr #12
d0015ce0:	4ff0e8bd 	svcmi	0x00f0e8bd
d0015ce4:	bb73f7fd 	bllt	0xd1d13ce0
d0015ce8:	7890f5ab 	ldmvc	r0, {r0, r1, r3, r5, r7, r8, sl, ip, sp, lr, pc}
d0015cec:	0f01f1b8 	svceq	0x0001f1b8
d0015cf0:	2c00d808 	stccs	8, cr13, [r0], {8}
d0015cf4:	4620db39 			; <UNDEFINED> instruction: 0x4620db39
d0015cf8:	fb56f7fd 	blx	0xd15d3cf6
d0015cfc:	4003f24b 	andmi	pc, r3, fp, asr #4
d0015d00:	fab2f7fd 	blx	0xcecd3cfc
d0015d04:	d1032f0a 	tstle	r3, sl, lsl #30
d0015d08:	0f3df1bb 	svceq	0x003df1bb
d0015d0c:	2504bf08 	strcs	fp, [r4, #-3848]	; 0xfffff0f8
d0015d10:	20014629 	andcs	r4, r1, r9, lsr #12
d0015d14:	fad4f7ff 	blx	0xcf553d18
d0015d18:	0f01f1b8 	svceq	0x0001f1b8
d0015d1c:	f64bd812 			; <UNDEFINED> instruction: 0xf64bd812
d0015d20:	f7fd4006 			; <UNDEFINED> instruction: 0xf7fd4006
d0015d24:	2f0afaa1 	svccs	0x000afaa1
d0015d28:	2080d102 	addcs	sp, r0, r2, lsl #2
d0015d2c:	fa9cf7fd 	blx	0xce753d28
d0015d30:	0008f641 	andeq	pc, r8, r1, asr #12
d0015d34:	2308f641 	movwcs	pc, #34369	; 0x8641	; <UNPREDICTABLE>
d0015d38:	7f90f5bb 	svcvc	0x0090f5bb
d0015d3c:	4618bf18 	sadd16mi	fp, r8, r8
d0015d40:	fa92f7fd 	blx	0xce4d3d3c
d0015d44:	d1032f05 	tstle	r3, r5, lsl #30
d0015d48:	20c0f24b 	sbccs	pc, r0, fp, asr #4
d0015d4c:	fa8cf7fd 	blx	0xce353d48
d0015d50:	dac22c00 	ble	0xcf0a0d58
d0015d54:	20014631 	andcs	r4, r1, r1, lsr r6
d0015d58:	fb64f7fd 	blx	0xd1953d56
d0015d5c:	0008f246 	andeq	pc, r8, r6, asr #4
d0015d60:	e8bdb003 	pop	{r0, r1, ip, sp, pc}
d0015d64:	f7fd4ff0 			; <UNDEFINED> instruction: 0xf7fd4ff0
d0015d68:	4631ba7f 			; <UNDEFINED> instruction: 0x4631ba7f
d0015d6c:	f7fd2001 			; <UNDEFINED> instruction: 0xf7fd2001
d0015d70:	f646fb59 			; <UNDEFINED> instruction: 0xf646fb59
d0015d74:	f7fd0008 			; <UNDEFINED> instruction: 0xf7fd0008
d0015d78:	e7bffa77 			; <UNDEFINED> instruction: 0xe7bffa77
d0015d7c:	f04f232c 			; <UNDEFINED> instruction: 0xf04f232c
d0015d80:	fb0336ff 	blx	0xd00e3986
d0015d84:	f5077704 			; <UNDEFINED> instruction: 0xf5077704
d0015d88:	f89737fa 			; <UNDEFINED> instruction: 0xf89737fa
d0015d8c:	e7517041 	ldrb	r7, [r1, -r1, asr #32]
d0015d90:	0000631e 	andeq	r6, r0, lr, lsl r3
d0015d94:	00006300 	andeq	r6, r0, r0, lsl #6
d0015d98:	000062a0 	andeq	r6, r0, r0, lsr #5
d0015d9c:	fffffef1 			; <UNDEFINED> instruction: 0xfffffef1
d0015da0:	fffffeb0 			; <UNDEFINED> instruction: 0xfffffeb0
d0015da4:	00006258 	andeq	r6, r0, r8, asr r2
d0015da8:	fffffecd 			; <UNDEFINED> instruction: 0xfffffecd
d0015dac:	00006244 	andeq	r6, r0, r4, asr #4
d0015db0:	fffffecb 			; <UNDEFINED> instruction: 0xfffffecb

Disassembly of section .text.condition.constprop.0:

d0015df0 <.text.condition.constprop.0>:
d0015df0:	20284908 	eorcs	r4, r8, r8, lsl #18
d0015df4:	4479b508 	ldrbtmi	fp, [r9], #-1288	; 0xfffffaf8
d0015df8:	ffaef7fc 			; <UNDEFINED> instruction: 0xffaef7fc
d0015dfc:	20012102 	andcs	r2, r1, r2, lsl #2
d0015e00:	fa5ef7ff 	blx	0xd17d3e04
d0015e04:	20294904 	eorcs	r4, r9, r4, lsl #18
d0015e08:	e8bd4479 	pop	{r0, r3, r4, r5, r6, sl, lr}
d0015e0c:	f7fc4008 			; <UNDEFINED> instruction: 0xf7fc4008
d0015e10:	bf00bfa3 	svclt	0x0000bfa3
d0015e14:	ffffffba 			; <UNDEFINED> instruction: 0xffffffba
d0015e18:	ffffffc6 			; <UNDEFINED> instruction: 0xffffffc6

Disassembly of section .text.statement.constprop.0:

d0016178 <.text.statement.constprop.0>:
d0016178:	4ff0e92d 	svcmi	0x00f0e92d
d001617c:	48c4f8df 	stmiami	r4, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d0016180:	6da3447c 	cfstrsvs	mvf4, [r3, #496]!	; 0x1f0
d0016184:	8b02ed2d 	blhi	0xd00d1640
d0016188:	bb6bb089 	bllt	0xd1b023b4
d001618c:	35fff504 	ldrbcc	pc, [pc, #1284]!	; 0xd0016698	; <UNPREDICTABLE>
d0016190:	312cf8d5 	ldrdcc	pc, [ip, -r5]!
d0016194:	2b203301 	blcs	0xd0822da0
d0016198:	312cf8c5 	smlawtcc	ip, r5, r8, pc	; <UNPREDICTABLE>
d001619c:	f8dfd905 			; <UNDEFINED> instruction: 0xf8dfd905
d00161a0:	447808a8 	ldrbtmi	r0, [r8], #-2216	; 0xfffff758
d00161a4:	f9c8f7fb 			; <UNDEFINED> instruction: 0xf9c8f7fb
d00161a8:	207be014 	rsbscs	lr, fp, r4, lsl r0
d00161ac:	fda6f7fc 	stc2	7, cr15, [r6, #1008]!	; 0x3f0
d00161b0:	b1f04606 	mvnslt	r4, r6, lsl #12
d00161b4:	3128f8d5 	ldrdcc	pc, [r8, -r5]!
d00161b8:	4120f8d5 	ldrdmi	pc, [r0, -r5]!
d00161bc:	f8c53301 			; <UNDEFINED> instruction: 0xf8c53301
d00161c0:	f0003128 			; <UNDEFINED> instruction: 0xf0003128
d00161c4:	f8d5fcc7 			; <UNDEFINED> instruction: 0xf8d5fcc7
d00161c8:	f8c53128 			; <UNDEFINED> instruction: 0xf8c53128
d00161cc:	3b014120 	blcc	0xd0066654
d00161d0:	3128f8c5 	smlawtcc	r8, r5, r8, pc	; <UNPREDICTABLE>
d00161d4:	3874f8df 	ldmdacc	r4!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d00161d8:	f503447b 			; <UNDEFINED> instruction: 0xf503447b
d00161dc:	f8d333ff 			; <UNDEFINED> instruction: 0xf8d333ff
d00161e0:	3a01212c 	bcc	0xd005e698
d00161e4:	212cf8c3 	smlawtcs	ip, r3, r8, pc	; <UNPREDICTABLE>
d00161e8:	ecbdb009 	ldc	0, cr11, [sp], #36	; 0x24
d00161ec:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d00161f0:	f44f8ff0 			; <UNDEFINED> instruction: 0xf44f8ff0
d00161f4:	f7fc7086 			; <UNDEFINED> instruction: 0xf7fc7086
d00161f8:	4680fd81 	strmi	pc, [r0], r1, lsl #27
d00161fc:	f7ffb320 			; <UNDEFINED> instruction: 0xf7ffb320
d0016200:	4630fdf7 			; <UNDEFINED> instruction: 0x4630fdf7
d0016204:	fc84f7fd 	stc2	7, cr15, [r4], {253}	; 0xfd
d0016208:	f7ff9000 			; <UNDEFINED> instruction: 0xf7ff9000
d001620c:	f240ffb5 	vrecps.f32	d31, d16, d21
d0016210:	f7fc100d 			; <UNDEFINED> instruction: 0xf7fc100d
d0016214:	f64dfd73 			; <UNDEFINED> instruction: 0xf64dfd73
d0016218:	460355f8 			; <UNDEFINED> instruction: 0x460355f8
d001621c:	b1889900 	orrlt	r9, r8, r0, lsl #18
d0016220:	fc66f7fd 	stc2l	7, cr15, [r6], #-1012	; 0xfffffc0c
d0016224:	46334607 	ldrtmi	r4, [r3], -r7, lsl #12
d0016228:	99005962 	stmdbls	r0, {r1, r5, r6, r8, fp, ip, lr}
d001622c:	f7fd6da0 			; <UNDEFINED> instruction: 0xf7fd6da0
d0016230:	f7fffe47 			; <UNDEFINED> instruction: 0xf7fffe47
d0016234:	4633ffa1 	ldrtmi	pc, [r3], -r1, lsr #31	; <UNPREDICTABLE>
d0016238:	46395962 	ldrtmi	r5, [r9], -r2, ror #18
d001623c:	f7fd6da0 			; <UNDEFINED> instruction: 0xf7fd6da0
d0016240:	e7c7fe3f 			; <UNDEFINED> instruction: 0xe7c7fe3f
d0016244:	e7f95962 	ldrb	r5, [r9, r2, ror #18]!
d0016248:	7087f44f 	addvc	pc, r7, pc, asr #8
d001624c:	fd56f7fc 	ldc2l	7, cr15, [r6, #-1008]	; 0xfffffc10
d0016250:	d0742800 	rsbsle	r2, r4, r0, lsl #16
d0016254:	3130f8d5 	teqcc	r0, r5	; <illegal shifter operand>	; <UNPREDICTABLE>
d0016258:	d1032b20 	tstle	r3, r0, lsr #22
d001625c:	07f0f8df 	ubfxeq	pc, pc, #17, #17
d0016260:	e79f4478 			; <UNDEFINED> instruction: 0xe79f4478
d0016264:	53f8f64d 	mvnspl	pc, #80740352	; 0x4d00000
d0016268:	6134f8d5 	teqvs	r4, r5	; <illegal shifter operand>	; <UNPREDICTABLE>
d001626c:	f7ff58e7 			; <UNDEFINED> instruction: 0xf7ff58e7
d0016270:	4640fdbf 			; <UNDEFINED> instruction: 0x4640fdbf
d0016274:	fc4cf7fd 	mcrr2	7, 15, pc, ip, cr13	; <UNPREDICTABLE>
d0016278:	3130f8d5 	teqcc	r0, r5	; <illegal shifter operand>	; <UNPREDICTABLE>
d001627c:	33014680 	movwcc	r4, #5760	; 0x1680
d0016280:	3130f8c5 	teqcc	r0, r5, asr #17	; <UNPREDICTABLE>
d0016284:	3503f504 	strcc	pc, [r3, #-1284]	; 0xfffffafc
d0016288:	3338f8d5 	teqcc	r8, #13959168	; 0xd50000	; <UNPREDICTABLE>
d001628c:	d1352b40 	teqle	r5, r0, asr #22
d0016290:	07c0f8df 			; <UNDEFINED> instruction: 0x07c0f8df
d0016294:	f7fb4478 			; <UNDEFINED> instruction: 0xf7fb4478
d0016298:	f8dff94f 			; <UNDEFINED> instruction: 0xf8dff94f
d001629c:	f50647bc 			; <UNDEFINED> instruction: 0xf50647bc
d00162a0:	f8df557f 			; <UNDEFINED> instruction: 0xf8df557f
d00162a4:	447ca7b8 	ldrbtmi	sl, [ip], #-1976	; 0xfffff848
d00162a8:	44fa3527 	ldrbtmi	r3, [sl], #1319	; 0x527
d00162ac:	32fff504 	rscscc	pc, pc, #4, 10	; 0x1000000
d00162b0:	495df504 	ldmdbmi	sp, {r2, r8, sl, ip, sp, lr, pc}^
d00162b4:	05c5eb04 	strbeq	lr, [r5, #2820]	; 0xb04
d00162b8:	3130f8d2 	teqcc	r0, r2	; <illegal shifter operand>	; <UNPREDICTABLE>
d00162bc:	09f8f109 	ldmibeq	r8!, {r0, r3, r8, ip, sp, lr, pc}^
d00162c0:	f8c23b01 			; <UNDEFINED> instruction: 0xf8c23b01
d00162c4:	f7fd3130 			; <UNDEFINED> instruction: 0xf7fd3130
d00162c8:	2300fc13 	movwcs	pc, #3091	; 0xc13	; <UNPREDICTABLE>
d00162cc:	463a4601 	ldrtmi	r4, [sl], -r1, lsl #12
d00162d0:	f7fd6da0 			; <UNDEFINED> instruction: 0xf7fd6da0
d00162d4:	f64dfdf5 			; <UNDEFINED> instruction: 0xf64dfdf5
d00162d8:	464152f8 			; <UNDEFINED> instruction: 0x464152f8
d00162dc:	230046b0 	movwcs	r4, #1712	; 0x6b0
d00162e0:	6da058a2 	stcvs	8, cr5, [r0, #648]!	; 0x288
d00162e4:	fdecf7fd 	stc2l	7, cr15, [ip, #1012]!	; 0x3f4
d00162e8:	33fff504 	mvnscc	pc, #4, 10	; 0x1000000
d00162ec:	729af503 	addsvc	pc, sl, #12582912	; 0xc00000
d00162f0:	3134f8d3 	teqcc	r4, r3	; <illegal shifter operand>	; <UNPREDICTABLE>
d00162f4:	d3124598 	tstle	r2, #152, 10	; 0x26000000
d00162f8:	e76b6016 			; <UNDEFINED> instruction: 0xe76b6016
d00162fc:	1c5a441c 	cfldrdne	mvd4, [sl], {28}
d0016300:	f5042301 			; <UNDEFINED> instruction: 0xf5042301
d0016304:	f8c53403 			; <UNDEFINED> instruction: 0xf8c53403
d0016308:	f8842338 			; <UNDEFINED> instruction: 0xf8842338
d001630c:	f7ff333c 			; <UNDEFINED> instruction: 0xf7ff333c
d0016310:	f8d5ff33 			; <UNDEFINED> instruction: 0xf8d5ff33
d0016314:	3b013338 	blcc	0xd0062ffc
d0016318:	3338f8c5 	teqcc	r8, #12910592	; 0xc50000	; <UNPREDICTABLE>
d001631c:	792be7bd 	stmdbvc	fp!, {r0, r2, r3, r4, r5, r7, r8, r9, sl, sp, lr, pc}
d0016320:	b1536829 	cmplt	r3, r9, lsr #16
d0016324:	2000f8d9 	ldrdcs	pc, [r0], -r9
d0016328:	f8da2300 			; <UNDEFINED> instruction: 0xf8da2300
d001632c:	f1080058 	cps	#24
d0016330:	35080801 	strcc	r0, [r8, #-2049]	; 0xfffff7ff
d0016334:	fdc4f7fd 	stc2l	7, cr15, [r4, #1012]	; 0x3f4
d0016338:	463ae7d6 			; <UNDEFINED> instruction: 0x463ae7d6
d001633c:	f240e7f4 	vaba.s8	q15, q8, q10
d0016340:	f7fc1013 			; <UNDEFINED> instruction: 0xf7fc1013
d0016344:	2800fcdb 	stmdacs	r0, {r0, r1, r3, r4, r6, r7, sl, fp, ip, sp, lr, pc}
d0016348:	80d6f000 	sbcshi	pc, r6, r0
d001634c:	3130f8d5 	teqcc	r0, r5	; <illegal shifter operand>	; <UNPREDICTABLE>
d0016350:	d0832b20 	addle	r2, r3, r0, lsr #22
d0016354:	1708f8df 			; <UNDEFINED> instruction: 0x1708f8df
d0016358:	44792028 	ldrbtmi	r2, [r9], #-40	; 0xffffffd8
d001635c:	fcfcf7fc 	ldc2l	7, cr15, [ip], #1008	; 0x3f0
d0016360:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0016364:	f8d5af37 			; <UNDEFINED> instruction: 0xf8d5af37
d0016368:	f8d53128 			; <UNDEFINED> instruction: 0xf8d53128
d001636c:	33017120 	movwcc	r7, #4384	; 0x1120
d0016370:	6134f8d5 	teqvs	r4, r5	; <illegal shifter operand>	; <UNPREDICTABLE>
d0016374:	3128f8c5 	smlawtcc	r8, r5, r8, pc	; <UNPREDICTABLE>
d0016378:	fa54f7ff 	blx	0xd155437c
d001637c:	203bb958 	eorscs	fp, fp, r8, asr r9
d0016380:	fcbcf7fc 	ldc2	7, cr15, [ip], #1008	; 0x3f0
d0016384:	f7ffb938 			; <UNDEFINED> instruction: 0xf7ffb938
d0016388:	f8dffc19 			; <UNDEFINED> instruction: 0xf8dffc19
d001638c:	203b16d8 	ldrsbtcs	r1, [fp], -r8
d0016390:	f7fc4479 			; <UNDEFINED> instruction: 0xf7fc4479
d0016394:	f8dffce1 			; <UNDEFINED> instruction: 0xf8dffce1
d0016398:	f64d36d0 			; <UNDEFINED> instruction: 0xf64d36d0
d001639c:	447b52f8 	ldrbtmi	r5, [fp], #-760	; 0xfffffd08
d00163a0:	a002f853 	andge	pc, r2, r3, asr r8	; <UNPREDICTABLE>
d00163a4:	2b3b6adb 	blcs	0xd0ef0f18
d00163a8:	8083f000 	addhi	pc, r3, r0
d00163ac:	20012102 	andcs	r2, r1, r2, lsl #2
d00163b0:	ff86f7fe 			; <UNDEFINED> instruction: 0xff86f7fe
d00163b4:	f7fd2000 			; <UNDEFINED> instruction: 0xf7fd2000
d00163b8:	4605fbab 	strmi	pc, [r5], -fp, lsr #23
d00163bc:	16acf8df 	ssatne	pc, #13, pc, asr #17	; <UNPREDICTABLE>
d00163c0:	4479203b 	ldrbtmi	r2, [r9], #-59	; 0xffffffc5
d00163c4:	fcc8f7fc 	stc2l	7, cr15, [r8], {252}	; 0xfc
d00163c8:	fb92f7fd 	blx	0xce4d43c6
d00163cc:	36a0f8df 	ssatcc	pc, #1, pc, asr #17	; <UNPREDICTABLE>
d00163d0:	52f8f64d 	rscspl	pc, r8, #80740352	; 0x4d00000
d00163d4:	447b4681 	ldrbtmi	r4, [fp], #-1665	; 0xfffff97f
d00163d8:	8002f853 	andhi	pc, r2, r3, asr r8	; <UNPREDICTABLE>
d00163dc:	2b296adb 	blcs	0xd0a70f50
d00163e0:	f7ffd001 			; <UNDEFINED> instruction: 0xf7ffd001
d00163e4:	f8dffbeb 			; <UNDEFINED> instruction: 0xf8dffbeb
d00163e8:	2029468c 	eorcs	r4, r9, ip, lsl #13
d00163ec:	1688f8df 	pkhtbne	pc, r8, pc, asr #17	; <UNPREDICTABLE>
d00163f0:	4479447c 	ldrbtmi	r4, [r9], #-1148	; 0xfffffb84
d00163f4:	fcb0f7fc 	ldc2	7, cr15, [r0], #1008	; 0x3f0
d00163f8:	fb7af7fd 	blx	0xd1ed43f6
d00163fc:	46012300 	strmi	r2, [r1], -r0, lsl #6
d0016400:	6da04652 	stcvs	6, cr4, [r0, #328]!	; 0x148
d0016404:	fd5cf7fd 	ldc2l	7, cr15, [ip, #-1012]	; 0xfffffc0c
d0016408:	52f8f64d 	rscspl	pc, r8, #80740352	; 0x4d00000
d001640c:	46492300 	strbmi	r2, [r9], -r0, lsl #6
d0016410:	f50458a2 			; <UNDEFINED> instruction: 0xf50458a2
d0016414:	6da03903 			; <UNDEFINED> instruction: 0x6da03903
d0016418:	fd52f7fd 	ldc2l	7, cr15, [r2, #-1012]	; 0xfffffc0c
d001641c:	32fff504 	rscscc	pc, pc, #4, 10	; 0x1000000
d0016420:	3130f8d2 	teqcc	r0, r2	; <illegal shifter operand>	; <UNPREDICTABLE>
d0016424:	f8c23301 			; <UNDEFINED> instruction: 0xf8c23301
d0016428:	f8d93130 			; <UNDEFINED> instruction: 0xf8d93130
d001642c:	2b403338 	blcs	0xd1023114
d0016430:	f8dfd141 			; <UNDEFINED> instruction: 0xf8dfd141
d0016434:	44780648 	ldrbtmi	r0, [r8], #-1608	; 0xfffff9b8
d0016438:	f87ef7fb 			; <UNDEFINED> instruction: 0xf87ef7fb
d001643c:	4640f8df 			; <UNDEFINED> instruction: 0x4640f8df
d0016440:	f504447c 			; <UNDEFINED> instruction: 0xf504447c
d0016444:	f8d232ff 			; <UNDEFINED> instruction: 0xf8d232ff
d0016448:	3b013130 	blcc	0xd0062910
d001644c:	3130f8c2 	teqcc	r0, r2, asr #17	; <UNPREDICTABLE>
d0016450:	fb4ef7fd 	blx	0xd13d444e
d0016454:	46012300 	strmi	r2, [r1], -r0, lsl #6
d0016458:	6da04642 	stcvs	6, cr4, [r0, #264]!	; 0x108
d001645c:	fd30f7fd 	ldc2	7, cr15, [r0, #-1012]!	; 0xfffffc0c
d0016460:	f64db13d 			; <UNDEFINED> instruction: 0xf64db13d
d0016464:	230052f8 	movwcs	r5, #760	; 0x2f8
d0016468:	6da04629 	stcvs	6, cr4, [r0, #164]!	; 0xa4
d001646c:	f7fd58a2 			; <UNDEFINED> instruction: 0xf7fd58a2
d0016470:	f8dffd27 			; <UNDEFINED> instruction: 0xf8dffd27
d0016474:	f5065610 			; <UNDEFINED> instruction: 0xf5065610
d0016478:	f8df547f 			; <UNDEFINED> instruction: 0xf8df547f
d001647c:	46b1b60c 	ldrtmi	fp, [r1], ip, lsl #12
d0016480:	3427447d 	strtcc	r4, [r7], #-1149	; 0xfffffb83
d0016484:	f50544fb 			; <UNDEFINED> instruction: 0xf50544fb
d0016488:	eb054a5d 	bl	0xd0168e04
d001648c:	f10a04c4 			; <UNDEFINED> instruction: 0xf10a04c4
d0016490:	f5050af8 			; <UNDEFINED> instruction: 0xf5050af8
d0016494:	f8d333ff 			; <UNDEFINED> instruction: 0xf8d333ff
d0016498:	45891134 	strmi	r1, [r9, #308]	; 0x134
d001649c:	f8d3d31c 			; <UNDEFINED> instruction: 0xf8d3d31c
d00164a0:	f8c32128 			; <UNDEFINED> instruction: 0xf8c32128
d00164a4:	3a016134 	bcc	0xd006e97c
d00164a8:	7120f8c3 	smlawtvc	r0, r3, r8, pc	; <UNPREDICTABLE>
d00164ac:	2128f8c3 	smlawtcs	r8, r3, r8, pc	; <UNPREDICTABLE>
d00164b0:	2500e690 	strcs	lr, [r0, #-1680]	; 0xfffff970
d00164b4:	441ce782 	ldrmi	lr, [ip], #-1922	; 0xfffff87e
d00164b8:	23011c5a 	movwcs	r1, #7258	; 0x1c5a
d00164bc:	3403f504 	strcc	pc, [r3], #-1284	; 0xfffffafc
d00164c0:	2338f8c9 	teqcs	r8, #13172736	; 0xc90000	; <UNPREDICTABLE>
d00164c4:	333cf884 	teqcc	ip, #132, 16	; 0x840000	; <UNPREDICTABLE>
d00164c8:	fe56f7ff 	mrc2	7, 2, pc, cr6, cr15, {7}
d00164cc:	3338f8d9 	teqcc	r8, #14221312	; 0xd90000	; <UNPREDICTABLE>
d00164d0:	f8c93b01 			; <UNDEFINED> instruction: 0xf8c93b01
d00164d4:	e7b13338 			; <UNDEFINED> instruction: 0xe7b13338
d00164d8:	68217923 	stmdavs	r1!, {r0, r1, r5, r8, fp, ip, sp, lr}
d00164dc:	f8dab153 			; <UNDEFINED> instruction: 0xf8dab153
d00164e0:	23002000 	movwcs	r2, #0
d00164e4:	0058f8db 	ldrsbeq	pc, [r8], #-139	; 0xffffff75	; <UNPREDICTABLE>
d00164e8:	0901f109 	stmdbeq	r1, {r0, r3, r8, ip, sp, lr, pc}
d00164ec:	f7fd3408 			; <UNDEFINED> instruction: 0xf7fd3408
d00164f0:	e7cefce7 	strb	pc, [lr, r7, ror #25]	; <UNPREDICTABLE>
d00164f4:	e7f44642 	ldrb	r4, [r4, r2, asr #12]!
d00164f8:	708af44f 	addvc	pc, sl, pc, asr #8
d00164fc:	fbfef7fc 	blx	0xcffd44f6
d0016500:	28004607 	stmdacs	r0, {r0, r1, r2, r9, sl, lr}
d0016504:	81e3f000 	mvnhi	pc, r0
d0016508:	3303f504 	movwcc	pc, #13572	; 0x3504	; <UNPREDICTABLE>
d001650c:	3338f8d3 	teqcc	r8, #13828096	; 0xd30000	; <UNPREDICTABLE>
d0016510:	d1032b40 	tstle	r3, r0, asr #22
d0016514:	0574f8df 	ldrbeq	pc, [r4, #-2271]!	; 0xfffff721	; <UNPREDICTABLE>
d0016518:	e6434478 			; <UNDEFINED> instruction: 0xe6434478
d001651c:	3407f504 	strcc	pc, [r7], #-1284	; 0xfffffafc
d0016520:	3380f8d4 	orrcc	pc, r0, #212, 16	; 0xd40000
d0016524:	7f80f5b3 	svcvc	0x0080f5b3
d0016528:	d1039300 	mrsle	r9, SP_svc
d001652c:	0560f8df 	strbeq	pc, [r0, #-2271]!	; 0xfffff721	; <UNPREDICTABLE>
d0016530:	e6374478 			; <UNDEFINED> instruction: 0xe6374478
d0016534:	3120f8d5 	ldrdcc	pc, [r0, -r5]!
d0016538:	93012b40 	movwls	r2, #6976	; 0x1b40
d001653c:	f8dfd10d 			; <UNDEFINED> instruction: 0xf8dfd10d
d0016540:	44780554 	ldrbtmi	r0, [r8], #-1364	; 0xfffffaac
d0016544:	fff8f7fa 			; <UNDEFINED> instruction: 0xfff8f7fa
d0016548:	354cf8df 	strbcc	pc, [ip, #-2271]	; 0xfffff721	; <UNPREDICTABLE>
d001654c:	447b9a01 	ldrbtmi	r9, [fp], #-2561	; 0xfffff5ff
d0016550:	33fff503 	mvnscc	pc, #12582912	; 0xc00000
d0016554:	2120f8c3 	smlawtcs	r0, r3, r8, pc	; <UNPREDICTABLE>
d0016558:	f8dfe63c 			; <UNDEFINED> instruction: 0xf8dfe63c
d001655c:	20284540 	eorcs	r4, r8, r0, asr #10
d0016560:	153cf8df 	ldrne	pc, [ip, #-2271]!	; 0xfffff721
d0016564:	4479447c 	ldrbtmi	r4, [r9], #-1148	; 0xfffffb84
d0016568:	3303f504 	movwcc	pc, #13572	; 0x3504	; <UNPREDICTABLE>
d001656c:	337cf8d3 	cmncc	ip, #13828096	; 0xd30000	; <UNPREDICTABLE>
d0016570:	f7fc9302 			; <UNDEFINED> instruction: 0xf7fc9302
d0016574:	2800fbf1 	stmdacs	r0, {r0, r4, r5, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d0016578:	2101d0e6 	smlattcs	r1, r6, r0, sp
d001657c:	f7fe4608 			; <UNDEFINED> instruction: 0xf7fe4608
d0016580:	f8dffe9f 			; <UNDEFINED> instruction: 0xf8dffe9f
d0016584:	20291520 	eorcs	r1, r9, r0, lsr #10
d0016588:	f7fc4479 			; <UNDEFINED> instruction: 0xf7fc4479
d001658c:	2800fbe5 	stmdacs	r0, {r0, r2, r5, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d0016590:	f8dfd0da 			; <UNDEFINED> instruction: 0xf8dfd0da
d0016594:	207b1514 	rsbscs	r1, fp, r4, lsl r5
d0016598:	f7fc4479 			; <UNDEFINED> instruction: 0xf7fc4479
d001659c:	2800fbdd 	stmdacs	r0, {r0, r2, r3, r4, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d00165a0:	f504d0d2 			; <UNDEFINED> instruction: 0xf504d0d2
d00165a4:	f8df33ff 			; <UNDEFINED> instruction: 0xf8df33ff
d00165a8:	f8d34504 			; <UNDEFINED> instruction: 0xf8d34504
d00165ac:	447c8120 	ldrbtmi	r8, [ip], #-288	; 0xfffffee0
d00165b0:	1124f8d3 	ldrdne	pc, [r4, -r3]!
d00165b4:	0201f108 	andeq	pc, r1, #8, 2
d00165b8:	36fff504 	ldrbtcc	pc, [pc], r4, lsl #10	; <UNPREDICTABLE>
d00165bc:	f8c3428a 			; <UNDEFINED> instruction: 0xf8c3428a
d00165c0:	f04f2120 			; <UNDEFINED> instruction: 0xf04f2120
d00165c4:	f8960100 			; <UNDEFINED> instruction: 0xf8960100
d00165c8:	bf887128 	svclt	0x00887128
d00165cc:	2124f8c3 	smlawtcs	r4, r3, r8, pc	; <UNPREDICTABLE>
d00165d0:	fb02222c 	blx	0xd009ee8a
d00165d4:	f5054508 			; <UNDEFINED> instruction: 0xf5054508
d00165d8:	f10535fa 			; <UNDEFINED> instruction: 0xf10535fa
d00165dc:	f0020020 			; <UNDEFINED> instruction: 0xf0020020
d00165e0:	230bffb3 	movwcs	pc, #49075	; 0xbfb3	; <UNPREDICTABLE>
d00165e4:	f8852100 			; <UNDEFINED> instruction: 0xf8852100
d00165e8:	f8857040 			; <UNDEFINED> instruction: 0xf8857040
d00165ec:	46403041 	strbmi	r3, [r0], -r1, asr #32
d00165f0:	feedf7fc 	mcr2	7, 7, pc, cr13, cr12, {7}	; <UNPREDICTABLE>
d00165f4:	fa7cf7fd 	blx	0xd1f545f0
d00165f8:	3128f8d6 	ldrdcc	pc, [r8, -r6]!
d00165fc:	3203f504 	andcc	pc, r3, #4, 10	; 0x1000000
d0016600:	0a10ee08 	beq	0xd0451e28
d0016604:	f8c63301 			; <UNDEFINED> instruction: 0xf8c63301
d0016608:	26003128 	strcs	r3, [r0], -r8, lsr #2
d001660c:	3338f8d2 	teqcc	r8, #13762560	; 0xd20000	; <UNPREDICTABLE>
d0016610:	441c4637 	ldrmi	r4, [ip], #-1591	; 0xfffff9c9
d0016614:	23021c59 	movwcs	r1, #11353	; 0x2c59
d0016618:	3403f504 	strcc	pc, [r3], #-1284	; 0xfffffafc
d001661c:	1338f8c2 	teqne	r8, #12713984	; 0xc20000	; <UNPREDICTABLE>
d0016620:	333cf884 	teqcc	ip, #132, 16	; 0x840000	; <UNPREDICTABLE>
d0016624:	3488f8df 	strcc	pc, [r8], #2271	; 0x8df
d0016628:	f503447b 			; <UNDEFINED> instruction: 0xf503447b
d001662c:	f5053505 			; <UNDEFINED> instruction: 0xf5053505
d0016630:	f8df7561 			; <UNDEFINED> instruction: 0xf8df7561
d0016634:	447c4480 	ldrbtmi	r4, [ip], #-1152	; 0xfffffb80
d0016638:	bb0b6da3 	bllt	0xd02f1ccc
d001663c:	2b7d6ae3 	blcs	0xd1f711d0
d0016640:	f5b3d01e 			; <UNDEFINED> instruction: 0xf5b3d01e
d0016644:	d01b7f80 	andsle	r7, fp, r0, lsl #31
d0016648:	1215f240 	andsne	pc, r5, #64, 4
d001664c:	f0404293 			; <UNDEFINED> instruction: 0xf0404293
d0016650:	f7fc80e5 			; <UNDEFINED> instruction: 0xf7fc80e5
d0016654:	6a63fb35 	bvs	0xd1915330
d0016658:	f894202d 			; <UNDEFINED> instruction: 0xf894202d
d001665c:	93039030 	movwls	r9, #12336	; 0x3030
d0016660:	93046aa3 	movwls	r6, #19107	; 0x4aa3
d0016664:	93056b63 	movwls	r6, #23395	; 0x5b63
d0016668:	fb48f7fc 	blx	0xd1254662
d001666c:	f5a36ae3 			; <UNDEFINED> instruction: 0xf5a36ae3
d0016670:	2b017381 	blcs	0xd007347c
d0016674:	f8dfd96f 			; <UNDEFINED> instruction: 0xf8dfd96f
d0016678:	44780440 	ldrbtmi	r0, [r8], #-1088	; 0xfffffbc0
d001667c:	ff5cf7fa 			; <UNDEFINED> instruction: 0xff5cf7fa
d0016680:	4438f8df 	ldrtmi	pc, [r8], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d0016684:	f8df207d 			; <UNDEFINED> instruction: 0xf8df207d
d0016688:	447c1438 	ldrbtmi	r1, [ip], #-1080	; 0xfffffbc8
d001668c:	f7fc4479 			; <UNDEFINED> instruction: 0xf7fc4479
d0016690:	f504fb63 			; <UNDEFINED> instruction: 0xf504fb63
d0016694:	f5043203 			; <UNDEFINED> instruction: 0xf5043203
d0016698:	f8d23b07 			; <UNDEFINED> instruction: 0xf8d23b07
d001669c:	3b013338 	blcc	0xd0063384
d00166a0:	3338f8c2 	teqcc	r8, #12713984	; 0xc20000	; <UNPREDICTABLE>
d00166a4:	32fff504 	rscscc	pc, pc, #4, 10	; 0x1000000
d00166a8:	3128f8d2 	ldrdcc	pc, [r8, -r2]!
d00166ac:	f8c23b01 			; <UNDEFINED> instruction: 0xf8c23b01
d00166b0:	f7fd3128 			; <UNDEFINED> instruction: 0xf7fd3128
d00166b4:	f64dfa1d 			; <UNDEFINED> instruction: 0xf64dfa1d
d00166b8:	230052f8 	movwcs	r5, #760	; 0x2f8
d00166bc:	ee184681 	cfmsub32	mvax4, mvfx4, mvfx8, mvfx1
d00166c0:	58a21a10 	stmiapl	r2!, {r4, r9, fp, ip}
d00166c4:	f7fd6da0 			; <UNDEFINED> instruction: 0xf7fd6da0
d00166c8:	9b00fbfb 	blls	0xd00556bc
d00166cc:	4585f503 	strmi	pc, [r5, #1283]	; 0x503
d00166d0:	3570469a 	ldrbcc	r4, [r0, #-1690]!	; 0xfffff966
d00166d4:	05c5eb04 	strbeq	lr, [r5, #2820]	; 0xb04
d00166d8:	3380f8db 	orrcc	pc, r0, #14352384	; 0xdb0000
d00166dc:	459a3508 	ldrmi	r3, [sl, #1288]	; 0x508
d00166e0:	80ccf0c0 	sbchi	pc, ip, r0, asr #1
d00166e4:	f0002f00 			; <UNDEFINED> instruction: 0xf0002f00
d00166e8:	f7fd80e5 			; <UNDEFINED> instruction: 0xf7fd80e5
d00166ec:	4601fa01 	strmi	pc, [r1], -r1, lsl #20
d00166f0:	24006da0 	strcs	r6, [r0], #-3488	; 0xfffff260
d00166f4:	463a2300 	ldrtmi	r2, [sl], -r0, lsl #6
d00166f8:	fbe2f7fd 	blx	0xcf8d46f6
d00166fc:	f64d4df1 			; <UNDEFINED> instruction: 0xf64d4df1
d0016700:	464953f8 			; <UNDEFINED> instruction: 0x464953f8
d0016704:	f855447d 			; <UNDEFINED> instruction: 0xf855447d
d0016708:	2300a003 	movwcs	sl, #3
d001670c:	46526da8 	ldrbmi	r6, [r2], -r8, lsr #27
d0016710:	fbd6f7fd 	blx	0xcf5d470e
d0016714:	2300b12c 	movwcs	fp, #300	; 0x12c
d0016718:	46214652 			; <UNDEFINED> instruction: 0x46214652
d001671c:	f7fd6da8 			; <UNDEFINED> instruction: 0xf7fd6da8
d0016720:	4ce9fbcf 	fstmiaxmi	r9!, {d31-d133}	;@ Deprecated
d0016724:	447c9d02 	ldrbtmi	r9, [ip], #-3330	; 0xfffff2fe
d0016728:	3803f504 	stmdacc	r3, {r2, r8, sl, ip, sp, lr, pc}
d001672c:	7760f508 	strbvc	pc, [r0, -r8, lsl #10]!	; <UNPREDICTABLE>
d0016730:	237cf8d8 	cmncs	ip, #216, 16	; 0xd80000	; <UNPREDICTABLE>
d0016734:	f0c04295 			; <UNDEFINED> instruction: 0xf0c04295
d0016738:	9a0280c1 	bls	0xd00b6a44
d001673c:	3407f504 	strcc	pc, [r7], #-1284	; 0xfffffafc
d0016740:	f8c89b00 			; <UNDEFINED> instruction: 0xf8c89b00
d0016744:	f8c4237c 			; <UNDEFINED> instruction: 0xf8c4237c
d0016748:	2e003380 	cdpcs	3, 0, cr3, cr0, cr0, {4}
d001674c:	aefcf47f 	mrcge	4, 7, APSR_nzcv, cr12, cr15, {3}
d0016750:	447848de 	ldrbtmi	r4, [r8], #-2270	; 0xfffff722
d0016754:	6a24e6f6 	bvs	0xd0950334
d0016758:	4264b100 	rsbmi	fp, r4, #0, 2
d001675c:	fab0f7fc 	blx	0xcec54754
d0016760:	203a49db 	ldrsbtcs	r4, [sl], -fp
d0016764:	f7fc4479 			; <UNDEFINED> instruction: 0xf7fc4479
d0016768:	2800faf7 	stmdacs	r0, {r0, r1, r2, r4, r5, r6, r7, r9, fp, ip, sp, lr, pc}
d001676c:	4ad9d088 	bmi	0xcf68a994
d0016770:	0e00f04f 	cdpeq	0, 0, cr15, cr0, cr15, {2}
d0016774:	447a49d8 	ldrbtmi	r4, [sl], #-2520	; 0xfffff628
d0016778:	f5024479 			; <UNDEFINED> instruction: 0xf5024479
d001677c:	91073307 	tstls	r7, r7, lsl #6
d0016780:	3380f8d3 	orrcc	pc, r0, #13828096	; 0xd30000
d0016784:	0c16e9d2 			; <UNDEFINED> instruction: 0x0c16e9d2
d0016788:	ab18e9d2 	blge	0xd0650ed8
d001678c:	92066e92 	andls	r6, r6, #2336	; 0x920
d0016790:	429a9a00 	addsmi	r9, sl, #0, 20
d0016794:	f1bed31d 			; <UNDEFINED> instruction: 0xf1bed31d
d0016798:	d0070f00 	andle	r0, r7, r0, lsl #30
d001679c:	99064acf 	stmdbls	r6, {r0, r1, r2, r3, r6, r7, r9, fp, lr}
d00167a0:	e9c2447a 	stmib	r2, {r1, r3, r4, r5, r6, sl, lr}^
d00167a4:	e9c20c16 	stmib	r2, {r1, r2, r4, sl, fp}^
d00167a8:	6691ab18 			; <UNDEFINED> instruction: 0x6691ab18
d00167ac:	7f80f5b3 	svcvc	0x0080f5b3
d00167b0:	4bcbd120 	blmi	0xcf30ac38
d00167b4:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d00167b8:	4acab94a 	bmi	0xcf2c4ce8
d00167bc:	659a447a 	ldrvs	r4, [sl, #1146]	; 0x47a
d00167c0:	65da9a03 	ldrbvs	r9, [sl, #2563]	; 0xa03
d00167c4:	e9c39a04 	stmib	r3, {r2, r9, fp, ip, pc}^
d00167c8:	9a052918 	bls	0xd0160c30
d00167cc:	3601669a 			; <UNDEFINED> instruction: 0x3601669a
d00167d0:	f855e72f 			; <UNDEFINED> instruction: 0xf855e72f
d00167d4:	42a11032 	adcmi	r1, r1, #50	; 0x32
d00167d8:	b948d10a 	stmdblt	r8, {r1, r3, r8, ip, lr, pc}^
d00167dc:	46cb9905 	strbmi	r9, [fp], r5, lsl #18
d00167e0:	a010f8dd 			; <UNDEFINED> instruction: 0xa010f8dd
d00167e4:	0e01f04f 	cdpeq	0, 0, cr15, cr1, cr15, {2}
d00167e8:	c00cf8dd 	ldrdgt	pc, [ip], -sp
d00167ec:	91069807 	tstls	r6, r7, lsl #16
d00167f0:	e7ce3201 	strb	r3, [lr, r1, lsl #4]
d00167f4:	1c584abc 	mrrcne	10, 11, r4, r8, cr12
d00167f8:	4385f503 	orrmi	pc, r5, #12582912	; 0xc00000
d00167fc:	3370447a 	cmncc	r0, #2046820352	; 0x7a000000
d0016800:	3107f502 	tstcc	r7, r2, lsl #10	; <UNPREDICTABLE>
d0016804:	0380f8c1 	orreq	pc, r0, #12648448	; 0xc10000
d0016808:	415df502 	cmpmi	sp, r2, lsl #10	; <UNPREDICTABLE>
d001680c:	680931f8 	stmdavs	r9, {r3, r4, r5, r6, r7, r8, ip, sp}
d0016810:	1033f842 	eorsne	pc, r3, r2, asr #16
d0016814:	03c3eb02 	biceq	lr, r3, #2048	; 0x800
d0016818:	e7d8605c 			; <UNDEFINED> instruction: 0xe7d8605c
d001681c:	708bf44f 	addvc	pc, fp, pc, asr #8
d0016820:	fa6cf7fc 	blx	0xd1b54818
d0016824:	49b1b310 	ldmibmi	r1!, {r4, r8, r9, ip, sp, pc}
d0016828:	6a63203a 	bvs	0xd18de918
d001682c:	f8d44479 			; <UNDEFINED> instruction: 0xf8d44479
d0016830:	f894b028 			; <UNDEFINED> instruction: 0xf894b028
d0016834:	f8d4a030 			; <UNDEFINED> instruction: 0xf8d4a030
d0016838:	93039034 	movwls	r9, #12340	; 0x3034
d001683c:	fa8cf7fc 	blx	0xce354834
d0016840:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0016844:	b167af1d 	cmnlt	r7, sp, lsl pc
d0016848:	2a006da2 	bcs	0xd0031ed8
d001684c:	4aa8d1bf 	bmi	0xcea4af50
d0016850:	447a9b03 	ldrbtmi	r9, [sl], #-2819	; 0xfffff4fd
d0016854:	9068f8c4 	rsbls	pc, r8, r4, asr #17
d0016858:	65a265e3 	strvs	r6, [r2, #1507]!	; 0x5e3
d001685c:	ba18e9c4 	blt	0xd0650f74
d0016860:	f504e7b5 			; <UNDEFINED> instruction: 0xf504e7b5
d0016864:	f8d4445d 			; <UNDEFINED> instruction: 0xf8d4445d
d0016868:	e7b070f8 			; <UNDEFINED> instruction: 0xe7b070f8
d001686c:	ffdaf7fe 			; <UNDEFINED> instruction: 0xffdaf7fe
d0016870:	f47f2800 			; <UNDEFINED> instruction: 0xf47f2800
d0016874:	f7ffaede 			; <UNDEFINED> instruction: 0xf7ffaede
d0016878:	e6dafc7f 			; <UNDEFINED> instruction: 0xe6dafc7f
d001687c:	f10a4640 			; <UNDEFINED> instruction: 0xf10a4640
d0016880:	f7fc0a01 			; <UNDEFINED> instruction: 0xf7fc0a01
d0016884:	f855fd91 			; <UNDEFINED> instruction: 0xf855fd91
d0016888:	20011c04 	andcs	r1, r1, r4, lsl #24
d001688c:	fd0ef7fc 	stc2	7, cr15, [lr, #-1008]	; 0xfffffc10
d0016890:	2088f244 	addcs	pc, r8, r4, asr #4
d0016894:	fce8f7fc 	stc2l	7, cr15, [r8], #1008	; 0x3f0
d0016898:	1001f24d 	andne	pc, r1, sp, asr #4
d001689c:	fce4f7fc 	stc2l	7, cr15, [r4], #1008	; 0x3f0
d00168a0:	f926f7fd 			; <UNDEFINED> instruction: 0xf926f7fd
d00168a4:	46012300 	strmi	r2, [r1], -r0, lsl #6
d00168a8:	2c08f855 	stccs	8, cr15, [r8], {85}	; 0x55
d00168ac:	f7fd6da0 			; <UNDEFINED> instruction: 0xf7fd6da0
d00168b0:	e711fb07 	ldr	pc, [r1, -r7, lsl #22]
d00168b4:	f91cf7fd 			; <UNDEFINED> instruction: 0xf91cf7fd
d00168b8:	e71f4604 	ldr	r4, [pc, -r4, lsl #12]
d00168bc:	1025f857 	eorne	pc, r5, r7, asr r8	; <UNPREDICTABLE>
d00168c0:	46522300 	ldrbmi	r2, [r2], -r0, lsl #6
d00168c4:	35016da0 	strcc	r6, [r1, #-3488]	; 0xfffff260
d00168c8:	fafaf7fd 	blx	0xcfed48c4
d00168cc:	6ae6e730 	bvs	0xcf9d0594
d00168d0:	7188f46f 	orrvc	pc, r8, pc, ror #8
d00168d4:	2b011873 	blcs	0xd005caa8
d00168d8:	f240d861 	vadd.i8	<illegal reg q14.5>, q0, <illegal reg q8.5>
d00168dc:	429e1311 	addsmi	r1, lr, #1140850688	; 0x44000000
d00168e0:	f8d5d00e 			; <UNDEFINED> instruction: 0xf8d5d00e
d00168e4:	b19b3130 	orrslt	r3, fp, r0, lsr r1
d00168e8:	447b4b82 	ldrbtmi	r4, [fp], #-2946	; 0xfffff47e
d00168ec:	33fff503 	mvnscc	pc, #12582912	; 0xc00000
d00168f0:	3134f8d3 	teqcc	r4, r3	; <illegal shifter operand>	; <UNPREDICTABLE>
d00168f4:	7f00f5b3 	svcvc	0x0000f5b3
d00168f8:	487fd121 	ldmdami	pc!, {r0, r5, r8, ip, lr, pc}^	; <UNPREDICTABLE>
d00168fc:	e4514478 	ldrb	r4, [r1], #-1144	; 0xfffffb88
d0016900:	3403f504 	strcc	pc, [r3], #-1284	; 0xfffffafc
d0016904:	3338f8d4 	teqcc	r8, #212, 16	; 0xd40000	; <UNPREDICTABLE>
d0016908:	487cb92b 	ldmdami	ip!, {r0, r1, r3, r5, r8, fp, ip, sp, pc}^
d001690c:	e4494478 	strb	r4, [r9], #-1144	; 0xfffffb88
d0016910:	4478487b 	ldrbtmi	r4, [r8], #-2171	; 0xfffff785
d0016914:	4a7be446 	bmi	0xd1f0fa34
d0016918:	4413447a 	ldrmi	r4, [r3], #-1146	; 0xfffffb86
d001691c:	3303f503 	movwcc	pc, #13571	; 0x3503	; <UNPREDICTABLE>
d0016920:	333bf893 	teqcc	fp, #9633792	; 0x930000	; <UNPREDICTABLE>
d0016924:	d1df2b02 	bicsle	r2, pc, r2, lsl #22
d0016928:	3203f502 	andcc	pc, r3, #8388608	; 0x800000
d001692c:	337cf8d2 	cmncc	ip, #13762560	; 0xd20000	; <UNPREDICTABLE>
d0016930:	7f00f5b3 	svcvc	0x0000f5b3
d0016934:	4874d102 	ldmdami	r4!, {r1, r8, ip, lr, pc}^
d0016938:	e4334478 	ldrt	r4, [r3], #-1144	; 0xfffffb88
d001693c:	f7fc2701 			; <UNDEFINED> instruction: 0xf7fc2701
d0016940:	4972f9bf 	ldmdbmi	r2!, {r0, r1, r2, r3, r4, r5, r7, r8, fp, ip, sp, lr, pc}^
d0016944:	4479203b 	ldrbtmi	r2, [r9], #-59	; 0xffffffc5
d0016948:	fa06f7fc 	blx	0xd01d4940
d001694c:	f8d0f7fd 			; <UNDEFINED> instruction: 0xf8d0f7fd
d0016950:	4a6fb177 	bmi	0xd1c02f34
d0016954:	f502447a 			; <UNDEFINED> instruction: 0xf502447a
d0016958:	f8d13103 			; <UNDEFINED> instruction: 0xf8d13103
d001695c:	1c5c337c 	mrrcne	3, 7, r3, ip, cr12
d0016960:	4303f503 	movwmi	pc, #13571	; 0x3503	; <UNPREDICTABLE>
d0016964:	f8c133e0 			; <UNDEFINED> instruction: 0xf8c133e0
d0016968:	f842437c 			; <UNDEFINED> instruction: 0xf842437c
d001696c:	e4310023 	ldrt	r0, [r1], #-35	; 0xffffffdd
d0016970:	447a4a68 	ldrbtmi	r4, [sl], #-2664	; 0xfffff598
d0016974:	31fff502 	mvnscc	pc, r2, lsl #10
d0016978:	3134f8d1 	teqcc	r4, r1	; <illegal shifter operand>	; <UNPREDICTABLE>
d001697c:	f5031c5c 			; <UNDEFINED> instruction: 0xf5031c5c
d0016980:	3327537f 			; <UNDEFINED> instruction: 0x3327537f
d0016984:	4134f8c1 	teqmi	r4, r1, asr #17	; <UNPREDICTABLE>
d0016988:	0033f842 	eorseq	pc, r3, r2, asr #16
d001698c:	03c3eb02 	biceq	lr, r3, #2048	; 0x800
d0016990:	1211f240 	andsne	pc, r1, #64, 4
d0016994:	42561ab2 	subsmi	r1, r6, #729088	; 0xb2000
d0016998:	711e4156 	tstvc	lr, r6, asr r1
d001699c:	f240e41a 	vqshl.s8	d30, d10, d0
d00169a0:	f7fc100f 			; <UNDEFINED> instruction: 0xf7fc100f
d00169a4:	2800f9ab 	stmdacs	r0, {r0, r1, r3, r5, r7, r8, fp, ip, sp, lr, pc}
d00169a8:	f504d03d 			; <UNDEFINED> instruction: 0xf504d03d
d00169ac:	7f2334fa 	svcvc	0x002334fa
d00169b0:	d0232b01 	eorle	r2, r3, r1, lsl #22
d00169b4:	f04f2b03 			; <UNDEFINED> instruction: 0xf04f2b03
d00169b8:	bf0c0001 	svclt	0x000c0001
d00169bc:	21012104 	tstcs	r1, r4, lsl #2
d00169c0:	fc7ef7fe 	ldc2l	7, cr15, [lr], #-1016	; 0xfffffc08
d00169c4:	447b4b54 	ldrbtmi	r4, [fp], #-2900	; 0xfffff4ac
d00169c8:	33faf503 	mvnscc	pc, #12582912	; 0xc00000
d00169cc:	2b027f1b 	blcs	0xd00b6640
d00169d0:	f24bd103 	vrhadd.s8	d29, d11, d3
d00169d4:	f7fc20c0 			; <UNDEFINED> instruction: 0xf7fc20c0
d00169d8:	4d50fc47 	ldclmi	12, cr15, [r0, #-284]	; 0xfffffee4
d00169dc:	4950203b 	ldmdbmi	r0, {r0, r1, r3, r4, r5, sp}^
d00169e0:	4479447d 	ldrbtmi	r4, [r9], #-1149	; 0xfffffb83
d00169e4:	f9b8f7fc 			; <UNDEFINED> instruction: 0xf9b8f7fc
d00169e8:	33faf505 	mvnscc	pc, #20971520	; 0x1400000
d00169ec:	f5b4699c 			; <UNDEFINED> instruction: 0xf5b4699c
d00169f0:	d10d6f80 	smlabble	sp, r0, pc, r6	; <UNPREDICTABLE>
d00169f4:	4478484b 	ldrbtmi	r4, [r8], #-2123	; 0xfffff7b5
d00169f8:	bbd4f7ff 	bllt	0xcf5549fc
d00169fc:	447b4b4a 	ldrbtmi	r4, [fp], #-2890	; 0xfffff4b6
d0016a00:	2b3b6adb 	blcs	0xd0ef1574
d0016a04:	4849d0e9 	stmdami	r9, {r0, r3, r5, r6, r7, ip, lr, pc}^
d0016a08:	f7fa4478 			; <UNDEFINED> instruction: 0xf7fa4478
d0016a0c:	e7e4fd95 			; <UNDEFINED> instruction: 0xe7e4fd95
d0016a10:	f5041c62 			; <UNDEFINED> instruction: 0xf5041c62
d0016a14:	340644f2 	strcc	r4, [r6], #-1266	; 0xfffffb0e
d0016a18:	f7fd619a 			; <UNDEFINED> instruction: 0xf7fd619a
d0016a1c:	f845f869 			; <UNDEFINED> instruction: 0xf845f869
d0016a20:	f7ff0024 			; <UNDEFINED> instruction: 0xf7ff0024
d0016a24:	203bbbd7 	ldrsbtcs	fp, [fp], -r7
d0016a28:	f968f7fc 			; <UNDEFINED> instruction: 0xf968f7fc
d0016a2c:	f47f2800 			; <UNDEFINED> instruction: 0xf47f2800
d0016a30:	f7ffabd1 			; <UNDEFINED> instruction: 0xf7ffabd1
d0016a34:	493ef8c3 	ldmdbmi	lr!, {r0, r1, r6, r7, fp, ip, sp, lr, pc}
d0016a38:	4479203b 	ldrbtmi	r2, [r9], #-59	; 0xffffffc5
d0016a3c:	f98cf7fc 			; <UNDEFINED> instruction: 0xf98cf7fc
d0016a40:	bbc8f7ff 	bllt	0xcf254a44
d0016a44:	00005d5c 	andeq	r5, r0, ip, asr sp
d0016a48:	ffffdde5 			; <UNDEFINED> instruction: 0xffffdde5
d0016a4c:	00005d04 	andeq	r5, r0, r4, lsl #26
d0016a50:	fffffc0b 			; <UNDEFINED> instruction: 0xfffffc0b
d0016a54:	fffffbed 			; <UNDEFINED> instruction: 0xfffffbed
d0016a58:	00005c36 	andeq	r5, r0, r6, lsr ip
d0016a5c:	00005c32 	andeq	r5, r0, r2, lsr ip
d0016a60:	fffffb4c 			; <UNDEFINED> instruction: 0xfffffb4c
d0016a64:	fffffb2d 			; <UNDEFINED> instruction: 0xfffffb2d
d0016a68:	00005b3e 	andeq	r5, r0, lr, lsr fp
d0016a6c:	fffffb1e 			; <UNDEFINED> instruction: 0xfffffb1e
d0016a70:	00005b06 	andeq	r5, r0, r6, lsl #22
d0016a74:	00005aec 	andeq	r5, r0, ip, ror #21
d0016a78:	fffffb0f 			; <UNDEFINED> instruction: 0xfffffb0f
d0016a7c:	fffffa4b 			; <UNDEFINED> instruction: 0xfffffa4b
d0016a80:	00005a9c 	muleq	r0, ip, sl
d0016a84:	00005a5c 	andeq	r5, r0, ip, asr sl
d0016a88:	00005a58 	andeq	r5, r0, r8, asr sl
d0016a8c:	fffff969 			; <UNDEFINED> instruction: 0xfffff969
d0016a90:	fffff9ed 			; <UNDEFINED> instruction: 0xfffff9ed
d0016a94:	fffff9f7 			; <UNDEFINED> instruction: 0xfffff9f7
d0016a98:	0000598e 	andeq	r5, r0, lr, lsl #19
d0016a9c:	00005978 	andeq	r5, r0, r8, ror r9
d0016aa0:	fffffa01 			; <UNDEFINED> instruction: 0xfffffa01
d0016aa4:	fffff9f9 			; <UNDEFINED> instruction: 0xfffff9f9
d0016aa8:	fffffa0e 			; <UNDEFINED> instruction: 0xfffffa0e
d0016aac:	0000592e 	andeq	r5, r0, lr, lsr #18
d0016ab0:	000058b4 			; <UNDEFINED> instruction: 0x000058b4
d0016ab4:	000058a6 	andeq	r5, r0, r6, lsr #17
d0016ab8:	fffff950 			; <UNDEFINED> instruction: 0xfffff950
d0016abc:	00005852 	andeq	r5, r0, r2, asr r8
d0016ac0:	fffff9bb 			; <UNDEFINED> instruction: 0xfffff9bb
d0016ac4:	000057d8 	ldrdeq	r5, [r0], -r8
d0016ac8:	000057b6 			; <UNDEFINED> instruction: 0x000057b6
d0016acc:	fffff914 			; <UNDEFINED> instruction: 0xfffff914
d0016ad0:	fffff88b 			; <UNDEFINED> instruction: 0xfffff88b
d0016ad4:	00005766 	andeq	r5, r0, r6, ror #14
d0016ad8:	fffff6a0 			; <UNDEFINED> instruction: 0xfffff6a0
d0016adc:	0000573c 	andeq	r5, r0, ip, lsr r7
d0016ae0:	00005728 	andeq	r5, r0, r8, lsr #14
d0016ae4:	fffff761 			; <UNDEFINED> instruction: 0xfffff761
d0016ae8:	000056e0 	andeq	r5, r0, r0, ror #13
d0016aec:	fffff7e1 			; <UNDEFINED> instruction: 0xfffff7e1
d0016af0:	fffff7d6 			; <UNDEFINED> instruction: 0xfffff7d6
d0016af4:	000055f2 	strdeq	r5, [r0], -r2
d0016af8:	fffff7ab 			; <UNDEFINED> instruction: 0xfffff7ab
d0016afc:	fffff540 			; <UNDEFINED> instruction: 0xfffff540
d0016b00:	fffff522 			; <UNDEFINED> instruction: 0xfffff522
d0016b04:	000055c4 	andeq	r5, r0, r4, asr #11
d0016b08:	fffff758 			; <UNDEFINED> instruction: 0xfffff758
d0016b0c:	fffff783 			; <UNDEFINED> instruction: 0xfffff783
d0016b10:	00005588 	andeq	r5, r0, r8, lsl #11
d0016b14:	0000556a 	andeq	r5, r0, sl, ror #10
d0016b18:	00005516 	andeq	r5, r0, r6, lsl r5
d0016b1c:	000054fc 	strdeq	r5, [r0], -ip
d0016b20:	fffff738 			; <UNDEFINED> instruction: 0xfffff738
d0016b24:	fffff73e 			; <UNDEFINED> instruction: 0xfffff73e
d0016b28:	000054de 	ldrdeq	r5, [r0], -lr
d0016b2c:	fffff6e6 			; <UNDEFINED> instruction: 0xfffff6e6
d0016b30:	fffff71b 			; <UNDEFINED> instruction: 0xfffff71b

Disassembly of section .text.block.constprop.0:

d0016b54 <.text.block.constprop.0>:
d0016b54:	4c0cb510 	cfstr32mi	mvfx11, [ip], {16}
d0016b58:	6da3447c 	cfstrsvs	mvf4, [r3, #496]!	; 0x1f0
d0016b5c:	6ae3b92b 	bvs	0xcf905010
d0016b60:	d0022b7d 	andle	r2, r2, sp, ror fp
d0016b64:	7f80f5b3 	svcvc	0x0080f5b3
d0016b68:	4908d106 	stmdbmi	r8, {r1, r2, r8, ip, lr, pc}
d0016b6c:	4479207d 	ldrbtmi	r2, [r9], #-125	; 0xffffff83
d0016b70:	4010e8bd 			; <UNDEFINED> instruction: 0x4010e8bd
d0016b74:	b8f0f7fc 	ldmlt	r0!, {r2, r3, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}^
d0016b78:	fe54f7fe 	mrc2	7, 2, pc, cr4, cr14, {7}
d0016b7c:	d1ec2800 	mvnle	r2, r0, lsl #16
d0016b80:	fafaf7ff 	blx	0xcfed4b84
d0016b84:	bf00e7e9 	svclt	0x0000e7e9
d0016b88:	00005384 	andeq	r5, r0, r4, lsl #7
d0016b8c:	ffffffc2 			; <UNDEFINED> instruction: 0xffffffc2

Disassembly of section .text.indirect_call.constprop.0:

d0016bf4 <.text.indirect_call.constprop.0>:
d0016bf4:	222c4b2a 	eorcs	r4, ip, #43008	; 0xa800
d0016bf8:	fb02447b 	blx	0xd00a7dee
d0016bfc:	e92d3300 	push	{r8, r9, ip, sp}
d0016c00:	f50341f0 			; <UNDEFINED> instruction: 0xf50341f0
d0016c04:	4f2733fa 	svcmi	0x002733fa
d0016c08:	809cf8df 			; <UNDEFINED> instruction: 0x809cf8df
d0016c0c:	f8934604 			; <UNDEFINED> instruction: 0xf8934604
d0016c10:	25006042 	strcs	r6, [r0, #-66]	; 0xffffffbe
d0016c14:	44f8447f 	ldrbtmi	r4, [r8], #1151	; 0x47f
d0016c18:	d90142ae 	stmdble	r1, {r1, r2, r3, r5, r7, r9, lr}
d0016c1c:	b35b6dbb 	cmplt	fp, #11968	; 0x2ec0
d0016c20:	f7fc4630 			; <UNDEFINED> instruction: 0xf7fc4630
d0016c24:	4921ff9e 	stmdbmi	r1!, {r1, r2, r3, r4, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0016c28:	20294605 	eorcs	r4, r9, r5, lsl #12
d0016c2c:	f7fc4479 			; <UNDEFINED> instruction: 0xf7fc4479
d0016c30:	b1f0f893 			; <UNDEFINED> instruction: 0xb1f0f893
d0016c34:	00d7f64f 	sbcseq	pc, r7, pc, asr #12
d0016c38:	fb16f7fc 	blx	0xd05d4c32
d0016c3c:	ea404817 	b	0xd1028ca0
d0016c40:	b2800084 	addlt	r0, r0, #132	; 0x84
d0016c44:	fb10f7fc 	blx	0xd0454c3e
d0016c48:	70e0f244 	rscvc	pc, r0, r4, asr #4
d0016c4c:	fb0cf7fc 	blx	0xd0354c46
d0016c50:	f445b125 	vst4.8	{d27,d29,d31,d33}, [r5 :128], r5
d0016c54:	b2804030 	addlt	r4, r0, #48	; 0x30
d0016c58:	fb06f7fc 	blx	0xd01d4c52
d0016c5c:	232c4814 			; <UNDEFINED> instruction: 0x232c4814
d0016c60:	fb034478 	blx	0xd00e7e4a
d0016c64:	f5040404 			; <UNDEFINED> instruction: 0xf5040404
d0016c68:	f89434fa 			; <UNDEFINED> instruction: 0xf89434fa
d0016c6c:	2b013043 	blcs	0xd0062d80
d0016c70:	2000d011 	andcs	sp, r0, r1, lsl r0
d0016c74:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d0016c78:	4641b11d 			; <UNDEFINED> instruction: 0x4641b11d
d0016c7c:	f7fc202c 			; <UNDEFINED> instruction: 0xf7fc202c
d0016c80:	2101f86b 	tstcs	r1, fp, ror #16	; <UNPREDICTABLE>
d0016c84:	46083501 	strmi	r3, [r8], -r1, lsl #10
d0016c88:	fb1af7fe 	blx	0xd06d4c8a
d0016c8c:	4003f24b 	andmi	pc, r3, fp, asr #4
d0016c90:	faeaf7fc 	blx	0xcfad4c88
d0016c94:	2002e7c0 	andcs	lr, r2, r0, asr #15
d0016c98:	bf00e7ec 	svclt	0x0000e7ec
d0016c9c:	ffffc000 			; <UNDEFINED> instruction: 0xffffc000
d0016ca0:	000052e4 	andeq	r5, r0, r4, ror #5
d0016ca4:	000052c8 	andeq	r5, r0, r8, asr #5
d0016ca8:	ffffff76 			; <UNDEFINED> instruction: 0xffffff76
d0016cac:	ffffff90 			; <UNDEFINED> instruction: 0xffffff90
d0016cb0:	0000527c 	andeq	r5, r0, ip, ror r2

Disassembly of section .text.int_pointer_element.constprop.0:

d0016cf8 <.text.int_pointer_element.constprop.0>:
d0016cf8:	460cb538 			; <UNDEFINED> instruction: 0x460cb538
d0016cfc:	46054921 	strmi	r4, [r5], -r1, lsr #18
d0016d00:	4479205b 	ldrbtmi	r2, [r9], #-91	; 0xffffffa5
d0016d04:	f828f7fc 			; <UNDEFINED> instruction: 0xf828f7fc
d0016d08:	2400b910 	strcs	fp, [r0], #-2320	; 0xfffff6f0
d0016d0c:	bd384620 	ldclt	6, cr4, [r8, #-128]!	; 0xffffff80
d0016d10:	4003f24b 	andmi	pc, r3, fp, asr #4
d0016d14:	faa8f7fc 	blx	0xcea54d0c
d0016d18:	46082101 	strmi	r2, [r8], -r1, lsl #2
d0016d1c:	fad0f7fe 	blx	0xcf454d1c
d0016d20:	205d4919 	subscs	r4, sp, r9, lsl r9
d0016d24:	f7fc4479 			; <UNDEFINED> instruction: 0xf7fc4479
d0016d28:	2800f817 	stmdacs	r0, {r0, r1, r2, r4, fp, ip, sp, lr, pc}
d0016d2c:	f64bd0ed 			; <UNDEFINED> instruction: 0xf64bd0ed
d0016d30:	f7fc4006 			; <UNDEFINED> instruction: 0xf7fc4006
d0016d34:	2080fa99 	umullcs	pc, r0, r9, sl	; <UNPREDICTABLE>
d0016d38:	fa96f7fc 	blx	0xce5d4d30
d0016d3c:	0008f641 	andeq	pc, r8, r1, asr #12
d0016d40:	fa92f7fc 	blx	0xce4d4d38
d0016d44:	b1adb9dc 	ldrdlt	fp, [sp, ip]!
d0016d48:	f7fb203d 			; <UNDEFINED> instruction: 0xf7fb203d
d0016d4c:	b188ffd7 	ldrdlt	pc, [r8, r7]
d0016d50:	4003f24b 	andmi	pc, r3, fp, asr #4
d0016d54:	f7fc2402 			; <UNDEFINED> instruction: 0xf7fc2402
d0016d58:	2101fa87 	smlabbcs	r1, r7, sl, pc	; <UNPREDICTABLE>
d0016d5c:	f7fe4608 			; <UNDEFINED> instruction: 0xf7fe4608
d0016d60:	f64bfaaf 			; <UNDEFINED> instruction: 0xf64bfaaf
d0016d64:	f7fc4006 			; <UNDEFINED> instruction: 0xf7fc4006
d0016d68:	f246fa7f 	vpmin.s8	<illegal reg q15.5>, q3, <illegal reg q15.5>
d0016d6c:	f7fc0008 			; <UNDEFINED> instruction: 0xf7fc0008
d0016d70:	e7cbfa7b 			; <UNDEFINED> instruction: 0xe7cbfa7b
d0016d74:	40d0f44f 	sbcsmi	pc, r0, pc, asr #8
d0016d78:	fa76f7fc 	blx	0xd1dd4d70
d0016d7c:	2404e7c6 	strcs	lr, [r4], #-1990	; 0xfffff83a
d0016d80:	bf00e7c4 	svclt	0x0000e7c4
d0016d84:	ffffffae 			; <UNDEFINED> instruction: 0xffffffae
d0016d88:	ffffffb0 			; <UNDEFINED> instruction: 0xffffffb0

Disassembly of section .text.sidc_compile_project.part.0:

d0017358 <.text.sidc_compile_project.part.0>:
d0017358:	4ff0e92d 	svcmi	0x00f0e92d
d001735c:	8b02ed2d 	blhi	0xd00d2818
d0017360:	9312b0c7 	tstls	r2, #199	; 0xc7
d0017364:	900c2300 	andls	r2, ip, r0, lsl #6
d0017368:	920e3004 	andls	r3, lr, #4
d001736c:	910d461a 	tstls	sp, sl, lsl r6
d0017370:	428b990e 	addmi	r9, fp, #229376	; 0x38000
d0017374:	4c6fd138 	stfmip	f5, [pc], #-224	; 0xd001729c
d0017378:	4a6d2100 	bmi	0xd1b5f780
d001737c:	4620447c 			; <UNDEFINED> instruction: 0x4620447c
d0017380:	f8e2f002 			; <UNDEFINED> instruction: 0xf8e2f002
d0017384:	486c9b52 	stmdami	ip!, {r1, r4, r6, r8, r9, fp, ip, pc}^
d0017388:	66e322bc 			; <UNDEFINED> instruction: 0x66e322bc
d001738c:	44789b12 	ldrbtmi	r9, [r8], #-2834	; 0xfffff4ee
d0017390:	6723496a 	strvs	r4, [r3, -sl, ror #18]!
d0017394:	33fff04f 	mvnscc	pc, #79	; 0x4f
d0017398:	30404479 	subcc	r4, r0, r9, ror r4
d001739c:	f00267a3 			; <UNDEFINED> instruction: 0xf00267a3
d00173a0:	f64df8e1 			; <UNDEFINED> instruction: 0xf64df8e1
d00173a4:	22bc53f8 	adcscs	r5, ip, #248, 6	; 0xe0000003
d00173a8:	230050e2 	movwcs	r5, #226	; 0xe2
d00173ac:	4b64930a 	blmi	0xd193bfdc
d00173b0:	930f447b 	movwls	r4, #62587	; 0xf47b
d00173b4:	33f2f503 	mvnscc	pc, #12582912	; 0xc00000
d00173b8:	93103318 	tstls	r0, #24, 6	; 0x60000000
d00173bc:	9a0e4c61 	bls	0xd03aa548
d00173c0:	447c990a 	ldrbtmi	r9, [ip], #-2314	; 0xfffff6f6
d00173c4:	6da3428a 	sfmvs	f4, 4, [r3, #552]!	; 0x228
d00173c8:	85c9f000 	strbhi	pc, [r9]	; <UNPREDICTABLE>
d00173cc:	4c5eb37b 	mrrcmi	3, 7, fp, lr, cr11
d00173d0:	f8df2600 			; <UNDEFINED> instruction: 0xf8df2600
d00173d4:	447c8178 	ldrbtmi	r8, [ip], #-376	; 0xfffffe88
d00173d8:	f50444f8 			; <UNDEFINED> instruction: 0xf50444f8
d00173dc:	f50435d2 			; <UNDEFINED> instruction: 0xf50435d2
d00173e0:	351437f2 	ldrcc	r3, [r4, #-2034]	; 0xfffff80e
d00173e4:	be02f000 	cdplt	0, 0, cr15, cr2, cr0, {0}
d00173e8:	f851990c 			; <UNDEFINED> instruction: 0xf851990c
d00173ec:	b1291033 			; <UNDEFINED> instruction: 0xb1291033
d00173f0:	1033f850 	eorsne	pc, r3, r0, asr r8	; <UNPREDICTABLE>
d00173f4:	3400f5c2 	strcc	pc, [r0], #-1474	; 0xfffffa3e
d00173f8:	d91542a1 	ldmdble	r5, {r0, r5, r7, r9, lr}
d00173fc:	2a019a0e 	bcs	0xd007dc3c
d0017400:	4a53d00f 	bmi	0xd150b444
d0017404:	9954447a 	ldmdbls	r4, {r1, r3, r4, r5, r6, sl, lr}^
d0017408:	600a2400 	andvs	r2, sl, r0, lsl #8
d001740c:	60cb2201 	sbcvs	r2, fp, r1, lsl #4
d0017410:	608a604a 	addvs	r6, sl, sl, asr #32
d0017414:	4620610c 	strtmi	r6, [r0], -ip, lsl #2
d0017418:	ecbdb047 	ldc	0, cr11, [sp], #284	; 0x11c
d001741c:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d0017420:	4a4c8ff0 	bmi	0xd133b3e8
d0017424:	e7ee447a 			; <UNDEFINED> instruction: 0xe7ee447a
d0017428:	3301440a 	movwcc	r4, #5130	; 0x140a
d001742c:	9b0ae7a0 	blls	0xd02d12b4
d0017430:	72239a0a 	eorvc	r9, r3, #40960	; 0xa000
d0017434:	f8539b0c 			; <UNDEFINED> instruction: 0xf8539b0c
d0017438:	60233032 	eorvs	r3, r3, r2, lsr r0
d001743c:	b3639b0d 	cmnlt	r3, #13312	; 0x3400
d0017440:	3022f853 	eorcc	pc, r2, r3, asr r8	; <UNPREDICTABLE>
d0017444:	990a4c44 	stmdbls	sl, {r2, r6, sl, fp, lr}
d0017448:	6763447c 			; <UNDEFINED> instruction: 0x6763447c
d001744c:	33fff04f 	mvnscc	pc, #79	; 0x4f
d0017450:	4250f504 	subsmi	pc, r0, #4, 10	; 0x1000000
d0017454:	4550f504 	ldrbmi	pc, [r0, #-1284]	; 0xfffffafc	; <UNPREDICTABLE>
d0017458:	230067a3 	movwcs	r6, #1955	; 0x7a3
d001745c:	60d3351c 	sbcsvs	r3, r3, ip, lsl r5
d0017460:	424ff504 	submi	pc, pc, #4, 10	; 0x1000000
d0017464:	31fcf8c4 	mvnscc	pc, r4, asr #17
d0017468:	3088f8c2 	addcc	pc, r8, r2, asr #17
d001746c:	32049a0c 	andcc	r9, r4, #12, 20	; 0xc000
d0017470:	2031f852 	eorscs	pc, r1, r2, asr r8	; <UNPREDICTABLE>
d0017474:	230160e3 	movwcs	r6, #4323	; 0x10e3
d0017478:	e9c46062 	stmib	r4, {r1, r5, r6, sp, lr}^
d001747c:	f7fb3304 			; <UNDEFINED> instruction: 0xf7fb3304
d0017480:	f7fbfc1f 			; <UNDEFINED> instruction: 0xf7fbfc1f
d0017484:	6ae2fc1d 	bvs	0xcf8d6500
d0017488:	f5b26da3 			; <UNDEFINED> instruction: 0xf5b26da3
d001748c:	d1107f83 	tstle	r0, r3, lsl #31
d0017490:	9b0ab12b 	blls	0xd02c3944
d0017494:	930a3301 	movwls	r3, #41729	; 0xa301
d0017498:	9b0de790 	blls	0xd03912e0
d001749c:	682be7d2 	stmdavs	fp!, {r1, r4, r6, r7, r8, r9, sl, sp, lr, pc}
d00174a0:	f7fbb113 			; <UNDEFINED> instruction: 0xf7fbb113
d00174a4:	e7eefc0d 	strb	pc, [lr, sp, lsl #24]!	; <UNPREDICTABLE>
d00174a8:	f7fb9812 			; <UNDEFINED> instruction: 0xf7fb9812
d00174ac:	2800fc91 	stmdacs	r0, {r0, r4, r7, sl, fp, ip, sp, lr, pc}
d00174b0:	4c2ad1f7 	stfmid	f5, [sl], #-988	; 0xfffffc24
d00174b4:	6da3447c 	cfstrsvs	mvf4, [r3, #496]!	; 0x1f0
d00174b8:	d1ea2b00 	mvnle	r2, r0, lsl #22
d00174bc:	f5b36ae3 			; <UNDEFINED> instruction: 0xf5b36ae3
d00174c0:	d0e67f80 	rscle	r7, r6, r0, lsl #31
d00174c4:	7083f44f 	addvc	pc, r3, pc, asr #8
d00174c8:	fc18f7fb 	ldc2	7, cr15, [r8], {251}	; 0xfb
d00174cc:	f504b148 			; <UNDEFINED> instruction: 0xf504b148
d00174d0:	331c4350 	tstcc	ip, #80, 6	; 0x40000001
d00174d4:	2b00681b 	blcs	0xd0031548
d00174d8:	6f20d1eb 	svcvs	0x0020d1eb
d00174dc:	fc78f7fb 	ldc2l	7, cr15, [r8], #-1004	; 0xfffffc14
d00174e0:	f44fe7e7 	vst1.64	{d30}, [pc :128], r7
d00174e4:	f7fb7088 			; <UNDEFINED> instruction: 0xf7fb7088
d00174e8:	900bfc09 	andls	pc, fp, r9, lsl #24
d00174ec:	f240b918 	vmul.i8	d27, d0, d8
d00174f0:	f7fb1009 			; <UNDEFINED> instruction: 0xf7fb1009
d00174f4:	f44ffc03 			; <UNDEFINED> instruction: 0xf44ffc03
d00174f8:	f7fb7084 			; <UNDEFINED> instruction: 0xf7fb7084
d00174fc:	4604fbff 			; <UNDEFINED> instruction: 0x4604fbff
d0017500:	f0402800 			; <UNDEFINED> instruction: 0xf0402800
d0017504:	481680d5 	ldmdami	r6, {r0, r2, r4, r6, r7, pc}
d0017508:	f7fb4478 			; <UNDEFINED> instruction: 0xf7fb4478
d001750c:	2800fc09 	stmdacs	r0, {r0, r3, sl, fp, ip, sp, lr, pc}
d0017510:	80d2f040 	sbcshi	pc, r2, r0, asr #32
d0017514:	bb3b9b0b 	bllt	0xd0efe148
d0017518:	1007f240 	andne	pc, r7, r0, asr #4
d001751c:	fbeef7fb 	blx	0xcfbd5512
d0017520:	f0402800 			; <UNDEFINED> instruction: 0xf0402800
d0017524:	480f80bd 	stmdami	pc, {r0, r2, r3, r4, r5, r7, pc}	; <UNPREDICTABLE>
d0017528:	f7fa4478 			; <UNDEFINED> instruction: 0xf7fa4478
d001752c:	e7c0f805 	strb	pc, [r0, r5, lsl #16]	; <UNPREDICTABLE>
d0017530:	00021f88 	andeq	r1, r2, r8, lsl #31
d0017534:	00004b60 	andeq	r4, r0, r0, ror #22
d0017538:	00026ad6 	ldrdeq	r6, [r2], -r6	; <UNPREDICTABLE>
d001753c:	000010ca 	andeq	r1, r0, sl, asr #1
d0017540:	00004b2c 	andeq	r4, r0, ip, lsr #22
d0017544:	00004b1a 	andeq	r4, r0, sl, lsl fp
d0017548:	00004b06 	andeq	r4, r0, r6, lsl #22
d001754c:	ffffff10 			; <UNDEFINED> instruction: 0xffffff10
d0017550:	fffff99b 			; <UNDEFINED> instruction: 0xfffff99b
d0017554:	fffff964 			; <UNDEFINED> instruction: 0xfffff964
d0017558:	00004a94 	muleq	r0, r4, sl
d001755c:	00004a28 	andeq	r4, r0, r8, lsr #20
d0017560:	fffff8b7 			; <UNDEFINED> instruction: 0xfffff8b7
d0017564:	fffff8a7 			; <UNDEFINED> instruction: 0xfffff8a7
d0017568:	0bd8f8df 	bleq	0xcf6558ec
d001756c:	f7fb4478 			; <UNDEFINED> instruction: 0xf7fb4478
d0017570:	2800fbd7 	stmdacs	r0, {r0, r1, r2, r4, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d0017574:	80a3f040 	adchi	pc, r3, r0, asr #32
d0017578:	0bccf8df 	bleq	0xcf3558fc
d001757c:	f7fb4478 			; <UNDEFINED> instruction: 0xf7fb4478
d0017580:	b930fbcf 	ldmdblt	r0!, {r0, r1, r2, r3, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d0017584:	0bc4f8df 	bleq	0xcf155908
d0017588:	f7fb4478 			; <UNDEFINED> instruction: 0xf7fb4478
d001758c:	2800fbc9 	stmdacs	r0, {r0, r3, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d0017590:	2405d0c2 	strcs	sp, [r5], #-194	; 0xffffff3e
d0017594:	0b00f04f 	bleq	0xd00536d8
d0017598:	6bb4f8df 	blvs	0xced5591c
d001759c:	447ead16 	ldrbtmi	sl, [lr], #-3350	; 0xfffff2ea
d00175a0:	0718f106 	ldreq	pc, [r8, -r6, lsl #2]
d00175a4:	c50fcf0f 	strgt	ip, [pc, #-3855]	; 0xd001669d
d00175a8:	000fe897 	muleq	pc, r7, r8	; <UNPREDICTABLE>
d00175ac:	000fe885 	andeq	lr, pc, r5, lsl #17
d00175b0:	f2406a73 	vpmin.s8	q11, q0, <illegal reg q9.5>
d00175b4:	f8df1001 			; <UNDEFINED> instruction: 0xf8df1001
d00175b8:	93061b9c 	movwls	r1, #27548	; 0x6b9c
d00175bc:	44796ab3 	ldrbtmi	r6, [r9], #-2739	; 0xfffff54d
d00175c0:	f8969307 			; <UNDEFINED> instruction: 0xf8969307
d00175c4:	93083030 	movwls	r3, #32816	; 0x8030
d00175c8:	e9d66b73 	ldmib	r6, {r0, r1, r4, r5, r6, r8, r9, fp, sp, lr}^
d00175cc:	93099506 	movwls	r9, #38150	; 0x9506
d00175d0:	fbc2f7fb 	blx	0xcf0d55c6
d00175d4:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d00175d8:	9b0baf6c 	blls	0xd0303390
d00175dc:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d00175e0:	f1bb81b6 			; <UNDEFINED> instruction: 0xf1bb81b6
d00175e4:	f0400f00 			; <UNDEFINED> instruction: 0xf0400f00
d00175e8:	b91c81b2 	ldmdblt	ip, {r1, r4, r5, r7, r8, pc}
d00175ec:	2b286af3 	blcs	0xd0a321c0
d00175f0:	81adf000 			; <UNDEFINED> instruction: 0x81adf000
d00175f4:	af169b06 	svcge	0x00169b06
d00175f8:	9319ae1e 	tstls	r9, #480	; 0x1e0
d00175fc:	931a9b07 	tstls	sl, #7168	; 0x1c00
d0017600:	f88d9b08 			; <UNDEFINED> instruction: 0xf88d9b08
d0017604:	9b093070 	blls	0xd02637cc
d0017608:	9516e9cd 	ldrls	lr, [r6, #-2509]	; 0xfffff633
d001760c:	cf0f931d 	svcgt	0x000f931d
d0017610:	e897c60f 	ldm	r7, {r0, r1, r2, r3, r9, sl, lr, pc}
d0017614:	e886000f 	stm	r6, {r0, r1, r2, r3}
d0017618:	4629000f 	strtmi	r0, [r9], -pc
d001761c:	f7fb4648 			; <UNDEFINED> instruction: 0xf7fb4648
d0017620:	4629fd17 			; <UNDEFINED> instruction: 0x4629fd17
d0017624:	46484606 	strbmi	r4, [r8], -r6, lsl #12
d0017628:	fa46f7f9 	blx	0xd11d5614
d001762c:	da572800 	ble	0xd15e1634
d0017630:	db0c2e00 	blle	0xd0322e38
d0017634:	3b20f8df 	blcc	0xd08559b8
d0017638:	447b2030 	ldrbtmi	r2, [fp], #-48	; 0xffffffd0
d001763c:	3606fb00 	strcc	pc, [r6], -r0, lsl #22
d0017640:	f5067a1b 			; <UNDEFINED> instruction: 0xf5067a1b
d0017644:	f89636ba 			; <UNDEFINED> instruction: 0xf89636ba
d0017648:	429a2039 	addsmi	r2, sl, #57	; 0x39
d001764c:	4629d048 	strtmi	sp, [r9], -r8, asr #32
d0017650:	f7f94648 			; <UNDEFINED> instruction: 0xf7f94648
d0017654:	2800fa0f 	stmdacs	r0, {r0, r1, r2, r3, r9, fp, ip, sp, lr, pc}
d0017658:	f8dfd142 			; <UNDEFINED> instruction: 0xf8dfd142
d001765c:	46078b00 	strmi	r8, [r7], -r0, lsl #22
d0017660:	f50844f8 			; <UNDEFINED> instruction: 0xf50844f8
d0017664:	46464a50 			; <UNDEFINED> instruction: 0x46464a50
d0017668:	0a1cf10a 	beq	0xd0753a98
d001766c:	3000f8da 	ldrdcc	pc, [r0], -sl
d0017670:	d329429f 			; <UNDEFINED> instruction: 0xd329429f
d0017674:	33baf506 			; <UNDEFINED> instruction: 0x33baf506
d0017678:	2b80685b 	blcs	0xce0317ec
d001767c:	6db3d144 	ldfvsd	f5, [r3, #272]!	; 0x110
d0017680:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0017684:	f8dfaf16 			; <UNDEFINED> instruction: 0xf8dfaf16
d0017688:	447b3ad8 	ldrbtmi	r3, [fp], #-2776	; 0xfffff528
d001768c:	9b0665b3 	blls	0xd01b0d60
d0017690:	9b0765f3 	blls	0xd01f0e64
d0017694:	9b086633 	blls	0xd0230f68
d0017698:	9b096673 	blls	0xd027106c
d001769c:	e70866b3 			; <UNDEFINED> instruction: 0xe70866b3
d00176a0:	f7fb202a 			; <UNDEFINED> instruction: 0xf7fb202a
d00176a4:	b160fb2b 	msrlt	SPSR_irq, fp
d00176a8:	f04f2400 			; <UNDEFINED> instruction: 0xf04f2400
d00176ac:	e7730b03 	ldrb	r0, [r3, -r3, lsl #22]!
d00176b0:	f04f2400 			; <UNDEFINED> instruction: 0xf04f2400
d00176b4:	e76f0b01 	strb	r0, [pc, -r1, lsl #22]!
d00176b8:	0b02f04f 	bleq	0xd00d37fc
d00176bc:	2401e76c 	strcs	lr, [r1], #-1900	; 0xfffff894
d00176c0:	4604e768 	strmi	lr, [r4], -r8, ror #14
d00176c4:	e7674683 	strb	r4, [r7, -r3, lsl #13]!
d00176c8:	4250f508 	subsmi	pc, r0, #8, 10	; 0x2000000
d00176cc:	46484629 	strbmi	r4, [r8], -r9, lsr #12
d00176d0:	0834f108 	ldmdaeq	r4!, {r3, r8, ip, sp, lr, pc}
d00176d4:	f7f83224 			; <UNDEFINED> instruction: 0xf7f83224
d00176d8:	b908fde3 	stmdblt	r8, {r0, r1, r5, r6, r7, r8, sl, fp, ip, sp, lr, pc}
d00176dc:	e7c53701 	strb	r3, [r5, r1, lsl #14]
d00176e0:	3a80f8df 	bcc	0xce055a64
d00176e4:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d00176e8:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d00176ec:	f8dfaee2 			; <UNDEFINED> instruction: 0xf8dfaee2
d00176f0:	447a2a78 	ldrbtmi	r2, [sl], #-2680	; 0xfffff588
d00176f4:	9a06659a 	bls	0xd01b0d64
d00176f8:	9a0765da 	bls	0xd01f0e68
d00176fc:	9a08661a 	bls	0xd0230f6c
d0017700:	9a09665a 	bls	0xd0271070
d0017704:	e6d4669a 			; <UNDEFINED> instruction: 0xe6d4669a
d0017708:	b2e7205b 	rsclt	r2, r7, #91	; 0x5b
d001770c:	faf6f7fb 	blx	0xcfdd5700
d0017710:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d0017714:	2c05808f 	stccs	0, cr8, [r5], {143}	; 0x8f
d0017718:	b13cd008 	teqlt	ip, r8
d001771c:	2b006db3 	blcs	0xd0032df0
d0017720:	aec7f47f 	mcrge	4, 6, pc, cr7, cr15, {3}	; <UNPREDICTABLE>
d0017724:	3a44f8df 	bcc	0xd1155aa8
d0017728:	e7af447b 			; <UNDEFINED> instruction: 0xe7af447b
d001772c:	3a40f8df 	bcc	0xd1055ab0
d0017730:	6ad8447b 	bvs	0xcf628924
d0017734:	c024f8d3 	ldrdgt	pc, [r4], -r3	; <UNPREDICTABLE>
d0017738:	7081f5a0 	addvc	pc, r1, r0, lsr #11
d001773c:	f8936a9f 			; <UNDEFINED> instruction: 0xf8936a9f
d0017740:	28011030 	stmdacs	r1, {r4, r5, ip}
d0017744:	d8016b5a 	stmdale	r1, {r1, r3, r4, r6, r8, r9, fp, sp, lr}
d0017748:	b9786a18 	ldmdblt	r8!, {r3, r4, r9, fp, sp, lr}^
d001774c:	0a24f8df 	beq	0xd0955ad0
d0017750:	6d834478 	cfstrsvs	mvf4, [r3, #480]	; 0x1e0
d0017754:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0017758:	f8dfaeac 			; <UNDEFINED> instruction: 0xf8dfaeac
d001775c:	447b3a1c 	ldrbtmi	r3, [fp], #-2588	; 0xfffff5e4
d0017760:	e9c06682 	stmib	r0, {r1, r7, r9, sl, sp, lr}^
d0017764:	e9c03c16 	stmib	r0, {r1, r2, r4, sl, fp, ip, sp}^
d0017768:	e6a27118 	ssat	r7, #3, r8, lsl #2
d001776c:	f5b0b974 			; <UNDEFINED> instruction: 0xf5b0b974
d0017770:	d9293f80 	stmdble	r9!, {r7, r8, r9, sl, fp, ip, sp}
d0017774:	28006d98 	stmdacs	r0, {r3, r4, r7, r8, sl, fp, sp, lr}
d0017778:	ae9bf47f 	mrcge	4, 4, APSR_nzcv, cr11, cr15, {3}
d001777c:	09fcf8df 	ldmibeq	ip!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d0017780:	4478661f 	ldrbtmi	r6, [r8], #-1567	; 0xfffff9e1
d0017784:	0c16e9c3 			; <UNDEFINED> instruction: 0x0c16e9c3
d0017788:	e7bb6659 	sbfx	r6, r9, #12, #28
d001778c:	f8df2601 			; <UNDEFINED> instruction: 0xf8df2601
d0017790:	447b39f0 	ldrbtmi	r3, [fp], #-2544	; 0xfffff610
d0017794:	33baf503 			; <UNDEFINED> instruction: 0x33baf503
d0017798:	b91468db 	ldmdblt	r4, {r0, r1, r3, r4, r6, r7, fp, sp, lr}
d001779c:	f0233303 			; <UNDEFINED> instruction: 0xf0233303
d00177a0:	f5b30303 			; <UNDEFINED> instruction: 0xf5b30303
d00177a4:	d8042f80 	stmdale	r4, {r7, r8, r9, sl, fp, sp}
d00177a8:	f5c34346 			; <UNDEFINED> instruction: 0xf5c34346
d00177ac:	429e2380 	addsmi	r2, lr, #128, 6
d00177b0:	f8dfd90c 			; <UNDEFINED> instruction: 0xf8dfd90c
d00177b4:	447809d0 	ldrbtmi	r0, [r8], #-2512	; 0xfffff630
d00177b8:	2b006d83 	blcs	0xd0032dcc
d00177bc:	ae79f47f 	mrcge	4, 3, APSR_nzcv, cr9, cr15, {3}
d00177c0:	39c4f8df 	stmibcc	r4, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d00177c4:	e7cb447b 			; <UNDEFINED> instruction: 0xe7cb447b
d00177c8:	e7e02604 	strb	r2, [r0, r4, lsl #12]!
d00177cc:	fa78f7fb 	blx	0xd1e557c0
d00177d0:	19b8f8df 	ldmibne	r8!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d00177d4:	4479205d 	ldrbtmi	r2, [r9], #-93	; 0xffffffa3
d00177d8:	fabef7fb 	blx	0xcefd57cc
d00177dc:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d00177e0:	2c00ae68 	stccs	14, cr10, [r0], {104}	; 0x68
d00177e4:	2708bf0c 	strcs	fp, [r8, -ip, lsl #30]
d00177e8:	203d2707 	eorscs	r2, sp, r7, lsl #14
d00177ec:	fa86f7fb 	blx	0xce1d57e0
d00177f0:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d00177f4:	1ffb8097 	svcne	0x00fb8097
d00177f8:	d8772b01 	ldmdale	r7!, {r0, r8, r9, fp, sp}^
d00177fc:	1990f8df 	ldmibne	r0, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d0017800:	4479207b 	ldrbtmi	r2, [r9], #-123	; 0xffffff85
d0017804:	f7fb910b 			; <UNDEFINED> instruction: 0xf7fb910b
d0017808:	2800faa7 	stmdacs	r0, {r0, r1, r2, r5, r7, r9, fp, ip, sp, lr, pc}
d001780c:	ae51f43f 	mrcge	4, 2, APSR_nzcv, cr1, cr15, {1}
d0017810:	2980f8df 	stmibcs	r0, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d0017814:	6ad3447a 	bvs	0xcf4e8a04
d0017818:	7381f5a3 	orrvc	pc, r1, #683671552	; 0x28c00000
d001781c:	d8052b01 	stmdale	r5, {r0, r8, r9, fp, sp}
d0017820:	b020f8d2 	ldrdlt	pc, [r0], -r2	; <UNPREDICTABLE>
d0017824:	f1bb990b 			; <UNDEFINED> instruction: 0xf1bb990b
d0017828:	d0050f00 	andle	r0, r5, r0, lsl #30
d001782c:	0968f8df 	stmdbeq	r8!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d0017830:	e67a4478 			; <UNDEFINED> instruction: 0xe67a4478
d0017834:	e7d84606 	ldrb	r4, [r8, r6, lsl #12]
d0017838:	f7fb910b 			; <UNDEFINED> instruction: 0xf7fb910b
d001783c:	202cfa41 	eorcs	pc, ip, r1, asr #20
d0017840:	fa5cf7fb 	blx	0xd1755834
d0017844:	207d990b 	rsbscs	r9, sp, fp, lsl #18
d0017848:	fa86f7fb 	blx	0xce1d583c
d001784c:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0017850:	f8dfae30 			; <UNDEFINED> instruction: 0xf8dfae30
d0017854:	203b1948 	eorscs	r1, fp, r8, asr #18
d0017858:	f7fb4479 			; <UNDEFINED> instruction: 0xf7fb4479
d001785c:	2800fa7d 	stmdacs	r0, {r0, r2, r3, r4, r5, r6, r9, fp, ip, sp, lr, pc}
d0017860:	ae27f43f 	mcrge	4, 1, pc, cr7, cr15, {1}	; <UNPREDICTABLE>
d0017864:	2b011ffb 	blcs	0xd005f858
d0017868:	2f08d868 	svccs	0x0008d868
d001786c:	f8dfd109 			; <UNDEFINED> instruction: 0xf8dfd109
d0017870:	447a2930 	ldrbtmi	r2, [sl], #-2352	; 0xfffff6d0
d0017874:	32baf502 	adcscc	pc, sl, #8388608	; 0x800000
d0017878:	330368d3 	movwcc	r6, #14547	; 0x38d3
d001787c:	0303f023 	movweq	pc, #12323	; 0x3023	; <UNPREDICTABLE>
d0017880:	f8df60d3 			; <UNDEFINED> instruction: 0xf8df60d3
d0017884:	447b3920 	ldrbtmi	r3, [fp], #-2336	; 0xfffff6e0
d0017888:	33baf503 			; <UNDEFINED> instruction: 0x33baf503
d001788c:	442668dc 	strtmi	r6, [r6], #-2268	; 0xfffff724
d0017890:	f8df60de 			; <UNDEFINED> instruction: 0xf8df60de
d0017894:	f10d2914 			; <UNDEFINED> instruction: 0xf10d2914
d0017898:	447a0e78 	ldrbtmi	r0, [sl], #-3704	; 0xfffff188
d001789c:	31baf502 			; <UNDEFINED> instruction: 0x31baf502
d00178a0:	684b7a16 	stmdavs	fp, {r1, r2, r4, r9, fp, ip, sp, lr}^
d00178a4:	60481c58 	subvs	r1, r8, r8, asr ip
d00178a8:	e9cd9906 	stmib	sp, {r1, r2, r8, fp, ip, pc}^
d00178ac:	9121951e 			; <UNDEFINED> instruction: 0x9121951e
d00178b0:	9907252c 	stmdbls	r7, {r2, r3, r5, r8, sl, sp}
d00178b4:	2503fb05 	strcs	pc, [r3, #-2821]	; 0xfffff4fb
d00178b8:	99089122 	stmdbls	r8, {r1, r5, r8, ip, pc}
d00178bc:	35aff505 	strcc	pc, [pc, #1285]!	; 0xd0017dc9
d00178c0:	1090f88d 	addsne	pc, r0, sp, lsl #17
d00178c4:	0c04f105 	stfeqd	f7, [r4], {5}
d00178c8:	f8c59909 			; <UNDEFINED> instruction: 0xf8c59909
d00178cc:	9125b024 			; <UNDEFINED> instruction: 0x9125b024
d00178d0:	f88562ac 			; <UNDEFINED> instruction: 0xf88562ac
d00178d4:	e8be702c 	ldm	lr!, {r2, r3, r5, ip, sp, lr}
d00178d8:	e8ac000f 	stmia	ip!, {r0, r1, r2, r3}
d00178dc:	e89e000f 	ldm	lr, {r0, r1, r2, r3}
d00178e0:	e88c000f 	stm	ip, {r0, r1, r2, r3}
d00178e4:	f885000f 			; <UNDEFINED> instruction: 0xf885000f
d00178e8:	e5e2602d 	strb	r6, [r2, #45]!	; 0x2d
d00178ec:	f7fb202d 			; <UNDEFINED> instruction: 0xf7fb202d
d00178f0:	f8dffa05 			; <UNDEFINED> instruction: 0xf8dffa05
d00178f4:	f24038b8 	vtst.8	d19, d16, d24
d00178f8:	46041101 	strmi	r1, [r4], -r1, lsl #2
d00178fc:	6ada447b 	bvs	0xcf6a8af0
d0017900:	d114428a 	tstle	r4, sl, lsl #5
d0017904:	0106e9d3 	ldrdeq	lr, [r6, -r3]
d0017908:	f8b4f7f9 			; <UNDEFINED> instruction: 0xf8b4f7f9
d001790c:	f8dfb918 			; <UNDEFINED> instruction: 0xf8dfb918
d0017910:	447808a0 	ldrbtmi	r0, [r8], #-2208	; 0xfffff760
d0017914:	f8d0e609 			; <UNDEFINED> instruction: 0xf8d0e609
d0017918:	f7fbb020 			; <UNDEFINED> instruction: 0xf7fbb020
d001791c:	b10cf9d1 	ldrdlt	pc, [ip, -r1]
d0017920:	0b00f1cb 	bleq	0xd0054054
d0017924:	bf082f05 	svclt	0x00082f05
d0017928:	fb8bfa5f 	blx	0xce3162ae
d001792c:	f5a2e791 			; <UNDEFINED> instruction: 0xf5a2e791
d0017930:	2a017281 	bcs	0xd007433c
d0017934:	f8d3d8eb 			; <UNDEFINED> instruction: 0xf8d3d8eb
d0017938:	e7eeb020 	strb	fp, [lr, r0, lsr #32]!
d001793c:	3874f8df 	ldmdacc	r4!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d0017940:	f503447b 			; <UNDEFINED> instruction: 0xf503447b
d0017944:	689c33ba 	ldmvs	ip, {r1, r3, r4, r5, r7, r8, r9, ip, sp}
d0017948:	609a1d22 	addsvs	r1, sl, r2, lsr #26
d001794c:	f8dfe7a1 			; <UNDEFINED> instruction: 0xf8dfe7a1
d0017950:	20281868 	eorcs	r1, r8, r8, ror #16
d0017954:	f7fb4479 			; <UNDEFINED> instruction: 0xf7fb4479
d0017958:	2800f9ff 	stmdacs	r0, {r0, r1, r2, r3, r4, r5, r6, r7, r8, fp, ip, sp, lr, pc}
d001795c:	ada9f43f 	cfstrsge	mvf15, [r9, #252]!	; 0xfc
d0017960:	46484629 	strbmi	r4, [r8], -r9, lsr #12
d0017964:	f8a8f7f9 			; <UNDEFINED> instruction: 0xf8a8f7f9
d0017968:	db0a2800 	blle	0xd02a1970
d001796c:	384cf8df 	stmdacc	ip, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d0017970:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d0017974:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0017978:	f8dfad9c 			; <UNDEFINED> instruction: 0xf8dfad9c
d001797c:	447a2844 	ldrbtmi	r2, [sl], #-2116	; 0xfffff7bc
d0017980:	f8dfe6b8 			; <UNDEFINED> instruction: 0xf8dfe6b8
d0017984:	46292840 	strtmi	r2, [r9], -r0, asr #16
d0017988:	447a4648 	ldrbtmi	r4, [sl], #-1608	; 0xfffff9b8
d001798c:	fc88f7f8 	stc2	7, cr15, [r8], {248}	; 0xf8
d0017990:	f8dfbb78 			; <UNDEFINED> instruction: 0xf8dfbb78
d0017994:	46292834 			; <UNDEFINED> instruction: 0x46292834
d0017998:	447a4648 	ldrbtmi	r4, [sl], #-1608	; 0xfffff9b8
d001799c:	fc80f7f8 	stc2	7, cr15, [r0], {248}	; 0xf8
d00179a0:	f8dfbb50 			; <UNDEFINED> instruction: 0xf8dfbb50
d00179a4:	46292828 	strtmi	r2, [r9], -r8, lsr #16
d00179a8:	447a4648 	ldrbtmi	r4, [sl], #-1608	; 0xfffff9b8
d00179ac:	fc78f7f8 	ldc2l	7, cr15, [r8], #-992	; 0xfffffc20
d00179b0:	bf0c2800 	svclt	0x000c2800
d00179b4:	0800f04f 	stmdaeq	r0, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d00179b8:	080cf04f 	stmdaeq	ip, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d00179bc:	2810f8df 	ldmdacs	r0, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d00179c0:	46484629 	strbmi	r4, [r8], -r9, lsr #12
d00179c4:	f7f8447a 			; <UNDEFINED> instruction: 0xf7f8447a
d00179c8:	4603fc6b 	strmi	pc, [r3], -fp, ror #24
d00179cc:	ea589011 	b	0xd163ba18
d00179d0:	d0140303 	andsle	r0, r4, r3, lsl #6
d00179d4:	ea539b0b 	b	0xd14fe608
d00179d8:	d010030b 	andsle	r0, r0, fp, lsl #6
d00179dc:	37f4f8df 	ubfxcc	pc, pc, #17, #21
d00179e0:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d00179e4:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d00179e8:	f8dfad64 			; <UNDEFINED> instruction: 0xf8dfad64
d00179ec:	447a27ec 	ldrbtmi	r2, [sl], #-2028	; 0xfffff814
d00179f0:	f04fe680 			; <UNDEFINED> instruction: 0xf04fe680
d00179f4:	e7e10804 	strb	r0, [r1, r4, lsl #16]!
d00179f8:	0808f04f 	stmdaeq	r8, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d00179fc:	2400e7de 	strcs	lr, [r0], #-2014	; 0xfffff822
d0017a00:	0f04f1b8 	svceq	0x0004f1b8
d0017a04:	f88d9414 			; <UNDEFINED> instruction: 0xf88d9414
d0017a08:	f0404054 			; <UNDEFINED> instruction: 0xf0404054
d0017a0c:	f8df8083 			; <UNDEFINED> instruction: 0xf8df8083
d0017a10:	f44f17cc 	vst1.64	{d17}, [pc], ip
d0017a14:	44797085 	ldrbtmi	r7, [r9], #-133	; 0xffffff7b
d0017a18:	f7fb9111 			; <UNDEFINED> instruction: 0xf7fb9111
d0017a1c:	2800f99d 	stmdacs	r0, {r0, r2, r3, r4, r7, r8, fp, ip, sp, lr, pc}
d0017a20:	ad47f43f 	cfstrdge	mvd15, [r7, #-252]	; 0xffffff04
d0017a24:	f2409911 	vmul.i8	d25, d0, d1
d0017a28:	f7fb100b 			; <UNDEFINED> instruction: 0xf7fb100b
d0017a2c:	2800f995 	stmdacs	r0, {r0, r2, r4, r7, r8, fp, ip, sp, lr, pc}
d0017a30:	ad3ff43f 	cfldrsge	mvf15, [pc, #-252]!	; 0xd001793c
d0017a34:	202a9911 	eorcs	r9, sl, r1, lsl r9
d0017a38:	f98ef7fb 			; <UNDEFINED> instruction: 0xf98ef7fb
d0017a3c:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0017a40:	f240ad38 	vmla.f32	d26, d0, d24
d0017a44:	24011001 	strcs	r1, [r1], #-1
d0017a48:	f958f7fb 			; <UNDEFINED> instruction: 0xf958f7fb
d0017a4c:	f88d2302 			; <UNDEFINED> instruction: 0xf88d2302
d0017a50:	f8df3050 			; <UNDEFINED> instruction: 0xf8df3050
d0017a54:	2029178c 	eorcs	r1, r9, ip, lsl #15
d0017a58:	f7fb4479 			; <UNDEFINED> instruction: 0xf7fb4479
d0017a5c:	2800f97d 	stmdacs	r0, {r0, r2, r3, r4, r5, r6, r8, fp, ip, sp, lr, pc}
d0017a60:	ad27f43f 	cfstrsge	mvf15, [r7, #-252]!	; 0xffffff04
d0017a64:	0f08f018 	svceq	0x0008f018
d0017a68:	2c00d002 	stccs	0, cr13, [r0], {2}
d0017a6c:	811bf040 	tsthi	fp, r0, asr #32	; <UNPREDICTABLE>
d0017a70:	a770f8df 			; <UNDEFINED> instruction: 0xa770f8df
d0017a74:	44fa2700 	ldrbtmi	r2, [sl], #1792	; 0x700
d0017a78:	36baf50a 	ldrtcc	pc, [sl], sl, lsl #10	; <UNPREDICTABLE>
d0017a7c:	33d2f50a 	bicscc	pc, r2, #41943040	; 0x2800000
d0017a80:	691a3610 	ldmdbvs	sl, {r4, r9, sl, ip, sp}
d0017a84:	d2244297 	eorle	r4, r4, #1879048201	; 0x70000009
d0017a88:	437a2230 	cmnmi	sl, #48, 4
d0017a8c:	68729211 	ldmdavs	r2!, {r0, r4, r9, ip, pc}^
d0017a90:	f04042aa 			; <UNDEFINED> instruction: 0xf04042aa
d0017a94:	462a8113 			; <UNDEFINED> instruction: 0x462a8113
d0017a98:	68304649 	ldmdavs	r0!, {r0, r3, r6, r9, sl, lr}
d0017a9c:	f0019313 			; <UNDEFINED> instruction: 0xf0019313
d0017aa0:	9b13fd71 	blls	0xd051706c
d0017aa4:	f0402800 			; <UNDEFINED> instruction: 0xf0402800
d0017aa8:	f8968109 			; <UNDEFINED> instruction: 0xf8968109
d0017aac:	f89d1028 			; <UNDEFINED> instruction: 0xf89d1028
d0017ab0:	4291202c 	addsmi	r2, r1, #44	; 0x2c
d0017ab4:	8102f040 	tsthi	r2, r0, asr #32	; <UNPREDICTABLE>
d0017ab8:	b1329a0b 	teqlt	r2, fp, lsl #20
d0017abc:	1029f896 	mlane	r9, r6, r8, pc	; <UNPREDICTABLE>
d0017ac0:	2008f89a 	mulcs	r8, sl, r8
d0017ac4:	f0404291 			; <UNDEFINED> instruction: 0xf0404291
d0017ac8:	f1b780f9 			; <UNDEFINED> instruction: 0xf1b780f9
d0017acc:	f2800a00 	vmlsl.s8	q0, d0, d0
d0017ad0:	46298464 	strtmi	r8, [r9], -r4, ror #8
d0017ad4:	f7fb4648 			; <UNDEFINED> instruction: 0xf7fb4648
d0017ad8:	2800fabb 	stmdacs	r0, {r0, r1, r3, r4, r5, r7, r9, fp, ip, sp, lr, pc}
d0017adc:	844cf2c0 	strbhi	pc, [ip], #-704	; 0xfffffd40	; <UNPREDICTABLE>
d0017ae0:	46484629 	strbmi	r4, [r8], -r9, lsr #12
d0017ae4:	fab4f7fb 	blx	0xced55ad8
d0017ae8:	36fcf8df 	usatcc	pc, #28, pc, asr #17	; <UNPREDICTABLE>
d0017aec:	447b2230 	ldrbtmi	r2, [fp], #-560	; 0xfffffdd0
d0017af0:	3000fb02 	andcc	pc, r0, r2, lsl #22
d0017af4:	f5007a1a 			; <UNDEFINED> instruction: 0xf5007a1a
d0017af8:	f89030ba 			; <UNDEFINED> instruction: 0xf89030ba
d0017afc:	42911039 	addsmi	r1, r1, #57	; 0x39
d0017b00:	843af040 	ldrthi	pc, [sl], #-64	; 0xffffffc0	; <UNPREDICTABLE>
d0017b04:	2a006d9a 	bcs	0xd0033174
d0017b08:	acd3f47f 	cfldrdge	mvd15, [r3], {127}	; 0x7f
d0017b0c:	26dcf8df 			; <UNDEFINED> instruction: 0x26dcf8df
d0017b10:	e5ef447a 	strb	r4, [pc, #1146]!	; 0xd0017f92
d0017b14:	36d8f8df 			; <UNDEFINED> instruction: 0x36d8f8df
d0017b18:	6ada447b 	bvs	0xcf6a8d0c
d0017b1c:	7f84f5b2 	svcvc	0x0084f5b2
d0017b20:	6cdbd105 	ldfvsp	f5, [fp], {5}
d0017b24:	d1022b29 	tstle	r2, r9, lsr #22
d0017b28:	f8caf7fb 			; <UNDEFINED> instruction: 0xf8caf7fb
d0017b2c:	f8dfe791 			; <UNDEFINED> instruction: 0xf8dfe791
d0017b30:	ae14a6c4 	cfmsub32ge	mvax6, mvfx10, mvfx4, mvfx4
d0017b34:	36c0f8df 			; <UNDEFINED> instruction: 0x36c0f8df
d0017b38:	44fa2400 	ldrbtmi	r2, [sl], #1024	; 0x400
d0017b3c:	f50a447b 			; <UNDEFINED> instruction: 0xf50a447b
d0017b40:	ee084750 	mcr	7, 0, r4, cr8, cr0, {2}
d0017b44:	371c3a10 			; <UNDEFINED> instruction: 0x371c3a10
d0017b48:	d1462c01 	cmple	r6, r1, lsl #24
d0017b4c:	2b009b11 	blcs	0xd003e798
d0017b50:	f89dd043 			; <UNDEFINED> instruction: 0xf89dd043
d0017b54:	2b003050 	blcs	0xd0023c9c
d0017b58:	f240d13f 	vand	d29, d0, d31
d0017b5c:	f7fb100b 			; <UNDEFINED> instruction: 0xf7fb100b
d0017b60:	b3d0f8cd 	bicslt	pc, r0, #13434880	; 0xcd0000
d0017b64:	1694f8df 			; <UNDEFINED> instruction: 0x1694f8df
d0017b68:	4479202a 	ldrbtmi	r2, [r9], #-42	; 0xffffffd6
d0017b6c:	f7fb9113 			; <UNDEFINED> instruction: 0xf7fb9113
d0017b70:	2800f8f3 	stmdacs	r0, {r0, r1, r4, r5, r6, r7, fp, ip, sp, lr, pc}
d0017b74:	ac9df43f 	cfldrsge	mvf15, [sp], {63}	; 0x3f
d0017b78:	202a9913 	eorcs	r9, sl, r3, lsl r9
d0017b7c:	f8ecf7fb 			; <UNDEFINED> instruction: 0xf8ecf7fb
d0017b80:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0017b84:	2304ac96 	movwcs	sl, #19606	; 0x4c96
d0017b88:	3051f88d 	subscc	pc, r1, sp, lsl #17
d0017b8c:	e670f8df 			; <UNDEFINED> instruction: 0xe670f8df
d0017b90:	0c78f10d 	ldfeqp	f7, [r8], #-52	; 0xffffffcc
d0017b94:	eb0c44fe 	bl	0xd0328f94
d0017b98:	34011c44 	strcc	r1, [r1], #-3140	; 0xfffff3bc
d0017b9c:	0e18f10e 	mnfeqe	f7, #0.5
d0017ba0:	000fe8be 			; <UNDEFINED> instruction: 0x000fe8be
d0017ba4:	000fe8ac 	andeq	lr, pc, ip, lsr #17
d0017ba8:	000fe89e 	muleq	pc, lr, r8	; <UNPREDICTABLE>
d0017bac:	000fe88c 	andeq	lr, pc, ip, lsl #17
d0017bb0:	1001f240 	andne	pc, r1, r0, asr #4
d0017bb4:	f8a2f7fb 			; <UNDEFINED> instruction: 0xf8a2f7fb
d0017bb8:	3b01f816 	blcc	0xd0095c18
d0017bbc:	f43f2b04 			; <UNDEFINED> instruction: 0xf43f2b04
d0017bc0:	202caf48 	eorcs	sl, ip, r8, asr #30
d0017bc4:	f89af7fb 			; <UNDEFINED> instruction: 0xf89af7fb
d0017bc8:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0017bcc:	2c05af42 	stccs	15, cr10, [r5], {66}	; 0x42
d0017bd0:	f8dfd1ba 			; <UNDEFINED> instruction: 0xf8dfd1ba
d0017bd4:	44780630 	ldrbtmi	r0, [r8], #-1584	; 0xfffff9d0
d0017bd8:	f240e4a7 	vshl.s8	d30, d23, d16
d0017bdc:	f7fb1007 			; <UNDEFINED> instruction: 0xf7fb1007
d0017be0:	b140f88d 	smlalbblt	pc, r0, sp, r8	; <UNPREDICTABLE>
d0017be4:	f7fb202a 			; <UNDEFINED> instruction: 0xf7fb202a
d0017be8:	2800f889 	stmdacs	r0, {r0, r3, r7, fp, ip, sp, lr, pc}
d0017bec:	230abf14 	movwcs	fp, #44820	; 0xaf14
d0017bf0:	70332300 	eorsvc	r2, r3, r0, lsl #6
d0017bf4:	ee18e7ca 	cdp	7, 1, cr14, cr8, cr10, {6}
d0017bf8:	f7fb0a10 			; <UNDEFINED> instruction: 0xf7fb0a10
d0017bfc:	b108f891 			; <UNDEFINED> instruction: 0xb108f891
d0017c00:	e7f62303 	ldrb	r2, [r6, r3, lsl #6]!
d0017c04:	0600f8df 			; <UNDEFINED> instruction: 0x0600f8df
d0017c08:	f7fb4478 			; <UNDEFINED> instruction: 0xf7fb4478
d0017c0c:	b108f889 	smlabblt	r8, r9, r8, pc	; <UNPREDICTABLE>
d0017c10:	e7ee2301 	strb	r2, [lr, r1, lsl #6]!
d0017c14:	05f4f8df 	ldrbeq	pc, [r4, #2271]!	; 0x8df	; <UNPREDICTABLE>
d0017c18:	f7fb4478 			; <UNDEFINED> instruction: 0xf7fb4478
d0017c1c:	b108f881 	smlabblt	r8, r1, r8, pc	; <UNPREDICTABLE>
d0017c20:	e7e62305 	strb	r2, [r6, r5, lsl #6]!
d0017c24:	05e8f8df 	strbeq	pc, [r8, #2271]!	; 0x8df	; <UNPREDICTABLE>
d0017c28:	f7fb4478 			; <UNDEFINED> instruction: 0xf7fb4478
d0017c2c:	2800f879 	stmdacs	r0, {r0, r3, r4, r5, r6, fp, ip, sp, lr, pc}
d0017c30:	683bd1f6 	ldmdavs	fp!, {r1, r2, r4, r5, r6, r7, r8, ip, lr, pc}
d0017c34:	f44fb39b 	vst2.32	{d27-d30}, [pc :64], fp
d0017c38:	f7fb7085 			; <UNDEFINED> instruction: 0xf7fb7085
d0017c3c:	b1e0f85f 	mvnlt	pc, pc, asr r8	; <UNPREDICTABLE>
d0017c40:	05d0f8df 	ldrbeq	pc, [r0, #2271]	; 0x8df	; <UNPREDICTABLE>
d0017c44:	f7fb4478 			; <UNDEFINED> instruction: 0xf7fb4478
d0017c48:	b918f86b 	ldmdblt	r8, {r0, r1, r3, r5, r6, fp, ip, sp, lr, pc}
d0017c4c:	05c8f8df 	strbeq	pc, [r8, #2271]	; 0x8df	; <UNPREDICTABLE>
d0017c50:	e46a4478 	strbt	r4, [sl], #-1144	; 0xfffffb88
d0017c54:	15c4f8df 	strbne	pc, [r4, #2271]	; 0x8df	; <UNPREDICTABLE>
d0017c58:	4479202a 	ldrbtmi	r2, [r9], #-42	; 0xffffffd6
d0017c5c:	f87cf7fb 			; <UNDEFINED> instruction: 0xf87cf7fb
d0017c60:	d0f32800 	rscsle	r2, r3, r0, lsl #16
d0017c64:	435df50a 	cmpmi	sp, #41943040	; 0x2800000	; <UNPREDICTABLE>
d0017c68:	881b33f4 	ldmdahi	fp, {r2, r4, r5, r6, r7, r8, r9, ip, sp}
d0017c6c:	f8dfb91b 			; <UNDEFINED> instruction: 0xf8dfb91b
d0017c70:	447805b0 	ldrbtmi	r0, [r8], #-1456	; 0xfffffa50
d0017c74:	2306e459 	movwcs	lr, #25689	; 0x6459
d0017c78:	683be7bb 	ldmdavs	fp!, {r0, r1, r3, r4, r5, r7, r8, r9, sl, sp, lr, pc}
d0017c7c:	f44fb17b 	vst4.16	{d27,d29,d31,d33}, [pc :256], fp
d0017c80:	f7fb7084 			; <UNDEFINED> instruction: 0xf7fb7084
d0017c84:	b150f83b 	cmplt	r0, fp, lsr r8	; <UNPREDICTABLE>
d0017c88:	1598f8df 	ldrne	pc, [r8, #2271]	; 0x8df
d0017c8c:	4479202a 	ldrbtmi	r2, [r9], #-42	; 0xffffffd6
d0017c90:	f862f7fb 			; <UNDEFINED> instruction: 0xf862f7fb
d0017c94:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0017c98:	2302ac0c 	movwcs	sl, #11276	; 0x2c0c
d0017c9c:	f8dfe7a9 			; <UNDEFINED> instruction: 0xf8dfe7a9
d0017ca0:	44780588 	ldrbtmi	r0, [r8], #-1416	; 0xfffffa78
d0017ca4:	f8dfe441 			; <UNDEFINED> instruction: 0xf8dfe441
d0017ca8:	447b3584 	ldrbtmi	r3, [fp], #-1412	; 0xfffffa7c
d0017cac:	2a006d9a 	bcs	0xd003331c
d0017cb0:	abfff47f 	blge	0xd0014eb4
d0017cb4:	2578f8df 	ldrbcs	pc, [r8, #-2271]!	; 0xfffff721	; <UNPREDICTABLE>
d0017cb8:	e51b447a 	ldr	r4, [fp, #-1146]	; 0xfffffb86
d0017cbc:	36303701 	ldrtcc	r3, [r0], -r1, lsl #14
d0017cc0:	1c7ae6df 	ldclne	6, cr14, [sl], #-892	; 0xfffffc84
d0017cc4:	210046ba 			; <UNDEFINED> instruction: 0x210046ba
d0017cc8:	2230611a 	eorscs	r6, r0, #-2147483642	; 0x80000006
d0017ccc:	93137a33 	tstls	r3, #208896	; 0x33000
d0017cd0:	f307fb02 	vqrdmulh.s<illegal width 8>	d15, d7, d2
d0017cd4:	931118f7 	tstls	r1, #16187392	; 0xf70000
d0017cd8:	37baf507 	ldrcc	pc, [sl, r7, lsl #10]!
d0017cdc:	0310f107 	tsteq	r0, #-1073741823	; 0xc0000001	; <UNPREDICTABLE>
d0017ce0:	f0014618 			; <UNDEFINED> instruction: 0xf0014618
d0017ce4:	9a06fc31 	bls	0xd01d6db0
d0017ce8:	0c58f10d 	ldfeqp	f7, [r8], {13}
d0017cec:	8030f8c7 	eorshi	pc, r0, r7, asr #17
d0017cf0:	9a079219 	bls	0xd01fc55c
d0017cf4:	4034f887 	eorsmi	pc, r4, r7, lsl #17
d0017cf8:	9a08921a 	bls	0xd023c568
d0017cfc:	8035f887 	eorshi	pc, r5, r7, lsl #17
d0017d00:	2070f88d 	rsbscs	pc, r0, sp, lsl #17
d0017d04:	f8879a09 			; <UNDEFINED> instruction: 0xf8879a09
d0017d08:	921db037 	andsls	fp, sp, #55	; 0x37
d0017d0c:	9516e9cd 	ldrls	lr, [r6, #-2509]	; 0xfffff633
d0017d10:	e8bc4605 	ldm	ip!, {r0, r2, r9, sl, lr}
d0017d14:	c50f000f 	strgt	r0, [pc, #-15]	; 0xd0017d0d
d0017d18:	000fe89c 	muleq	pc, ip, r8	; <UNPREDICTABLE>
d0017d1c:	000fe885 	andeq	lr, pc, r5, lsl #17
d0017d20:	0300f1b8 	movweq	pc, #440	; 0x1b8	; <UNPREDICTABLE>
d0017d24:	a9144622 	ldmdbge	r4, {r1, r5, r9, sl, lr}
d0017d28:	2301bf18 	movwcs	fp, #7960	; 0x1f18
d0017d2c:	3036f887 	eorscc	pc, r6, r7, lsl #17
d0017d30:	f8879b0b 			; <UNDEFINED> instruction: 0xf8879b0b
d0017d34:	9b133038 	blls	0xd04e3e1c
d0017d38:	3039f887 	eorscc	pc, r9, r7, lsl #17
d0017d3c:	f5039b11 			; <UNDEFINED> instruction: 0xf5039b11
d0017d40:	303a30ba 	ldrhtcc	r3, [sl], -sl
d0017d44:	f0014430 			; <UNDEFINED> instruction: 0xf0014430
d0017d48:	203bfc0d 	eorscs	pc, fp, sp, lsl #24
d0017d4c:	ffd6f7fa 			; <UNDEFINED> instruction: 0xffd6f7fa
d0017d50:	f47f2800 			; <UNDEFINED> instruction: 0xf47f2800
d0017d54:	f8dfabae 			; <UNDEFINED> instruction: 0xf8dfabae
d0017d58:	273064dc 			; <UNDEFINED> instruction: 0x273064dc
d0017d5c:	fb07447e 	blx	0xd01e8f5e
d0017d60:	f507670a 			; <UNDEFINED> instruction: 0xf507670a
d0017d64:	f89737ba 			; <UNDEFINED> instruction: 0xf89737ba
d0017d68:	b19d5036 	orrslt	r5, sp, r6, lsr r0
d0017d6c:	2b006db3 	blcs	0xd0033440
d0017d70:	ab9ff47f 	blge	0xce814f74
d0017d74:	34c0f8df 	strbcc	pc, [r0], #2271	; 0x8df	; <UNPREDICTABLE>
d0017d78:	e487447b 	str	r4, [r7], #1147	; 0x47b
d0017d7c:	46229b11 			; <UNDEFINED> instruction: 0x46229b11
d0017d80:	f503a914 			; <UNDEFINED> instruction: 0xf503a914
d0017d84:	303a30ba 	ldrhtcc	r3, [sl], -sl
d0017d88:	f0014428 			; <UNDEFINED> instruction: 0xf0014428
d0017d8c:	2800fbfb 	stmdacs	r0, {r0, r1, r3, r4, r5, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d0017d90:	e312d0db 	tst	r2, #219	; 0xdb
d0017d94:	14a4f8df 	strtne	pc, [r4], #2271	; 0x8df
d0017d98:	4479207b 	ldrbtmi	r2, [r9], #-123	; 0xffffff85
d0017d9c:	ffdcf7fa 			; <UNDEFINED> instruction: 0xffdcf7fa
d0017da0:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0017da4:	f506ab86 			; <UNDEFINED> instruction: 0xf506ab86
d0017da8:	f506485d 			; <UNDEFINED> instruction: 0xf506485d
d0017dac:	f24b32fa 	vqsub.s8	<illegal reg q9.5>, <illegal reg q13.5>, q13
d0017db0:	f10d5080 			; <UNDEFINED> instruction: 0xf10d5080
d0017db4:	f8d80978 			; <UNDEFINED> instruction: 0xf8d80978
d0017db8:	f24030f8 	vqadd.s8	<illegal reg q9.5>, q8, q12
d0017dbc:	61951b01 	orrsvs	r1, r5, r1, lsl #22
d0017dc0:	2301633b 	movwcs	r6, #4923	; 0x133b
d0017dc4:	3036f887 	eorscc	pc, r6, r7, lsl #17
d0017dc8:	33fff506 	mvnscc	pc, #25165824	; 0x1800000
d0017dcc:	5128f8c3 	smlawtpl	r8, r3, r8, pc	; <UNPREDICTABLE>
d0017dd0:	5548e9c3 	strbpl	lr, [r8, #-2499]	; 0xfffff63d
d0017dd4:	554ce9c3 	strbpl	lr, [ip, #-2499]	; 0xfffff63d
d0017dd8:	3307f506 	movwcc	pc, #29958	; 0x7506	; <UNPREDICTABLE>
d0017ddc:	3603f506 	strcc	pc, [r3], -r6, lsl #10
d0017de0:	537cf8c6 	cmnpl	ip, #12976128	; 0xc60000	; <UNPREDICTABLE>
d0017de4:	5338f8c6 	teqpl	r8, #12976128	; 0xc60000	; <UNPREDICTABLE>
d0017de8:	6454f8df 	ldrbvs	pc, [r4], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d0017dec:	5380f8c3 	orrpl	pc, r0, #12779520	; 0xc30000
d0017df0:	f897447e 			; <UNDEFINED> instruction: 0xf897447e
d0017df4:	f5063037 			; <UNDEFINED> instruction: 0xf5063037
d0017df8:	7713465d 			; <UNDEFINED> instruction: 0x7713465d
d0017dfc:	fa34f7fb 	blx	0xd0d55df0
d0017e00:	70f8f8d8 	ldrsbtvc	pc, [r8], #136	; 0x88	; <UNPREDICTABLE>
d0017e04:	46a84628 	strtmi	r4, [r8], r8, lsr #12
d0017e08:	f7fb36f8 			; <UNDEFINED> instruction: 0xf7fb36f8
d0017e0c:	f44ffa2d 	vst1.8	{d31-d32}, [pc :128]!
d0017e10:	f7fb402f 			; <UNDEFINED> instruction: 0xf7fb402f
d0017e14:	42acfa29 	adcmi	pc, ip, #167936	; 0x29000
d0017e18:	f7fed145 			; <UNDEFINED> instruction: 0xf7fed145
d0017e1c:	f8dffe9b 			; <UNDEFINED> instruction: 0xf8dffe9b
d0017e20:	447b3424 	ldrbtmi	r3, [fp], #-1060	; 0xfffffbdc
d0017e24:	33faf503 	mvnscc	pc, #12582912	; 0xc00000
d0017e28:	2b017f1b 	blcs	0xd0077a9c
d0017e2c:	2000d002 	andcs	sp, r0, r2
d0017e30:	fa80f7fb 	blx	0xce055e24
d0017e34:	9410f8df 	ldrls	pc, [r0], #-2271	; 0xfffff721
d0017e38:	f50944f9 			; <UNDEFINED> instruction: 0xf50944f9
d0017e3c:	f8d3435d 			; <UNDEFINED> instruction: 0xf8d3435d
d0017e40:	f50950f8 			; <UNDEFINED> instruction: 0xf50950f8
d0017e44:	f8d333ff 			; <UNDEFINED> instruction: 0xf8d333ff
d0017e48:	34014124 	strcc	r4, [r1], #-292	; 0xfffffedc
d0017e4c:	0401f024 	streq	pc, [r1], #-36	; 0xffffffdc
d0017e50:	f446b2a6 	vst1.32	{d27-d30}, [r6 :128], r6
d0017e54:	f7fb4030 			; <UNDEFINED> instruction: 0xf7fb4030
d0017e58:	f64bfa07 			; <UNDEFINED> instruction: 0xf64bfa07
d0017e5c:	f7fb5080 			; <UNDEFINED> instruction: 0xf7fb5080
d0017e60:	f8d9fa03 			; <UNDEFINED> instruction: 0xf8d9fa03
d0017e64:	2b003058 	blcs	0xd0023fcc
d0017e68:	ab23f47f 	blge	0xd091506c
d0017e6c:	f4464bf7 			; <UNDEFINED> instruction: 0xf4464bf7
d0017e70:	447b4630 	ldrbtmi	r4, [fp], #-1584	; 0xfffff9d0
d0017e74:	0680f046 	streq	pc, [r0], r6, asr #32
d0017e78:	f887441f 			; <UNDEFINED> instruction: 0xf887441f
d0017e7c:	0a366040 	beq	0xd0daff84
d0017e80:	6041f887 	subvs	pc, r1, r7, lsl #17
d0017e84:	0f00f1b8 	svceq	0x0000f1b8
d0017e88:	3402d008 	strcc	sp, [r2], #-8
d0017e8c:	00a44498 	umlaleq	r4, r4, r8, r4	; <UNPREDICTABLE>
d0017e90:	f888b2a4 			; <UNDEFINED> instruction: 0xf888b2a4
d0017e94:	0a244040 	beq	0xd0927f9c
d0017e98:	4041f888 	submi	pc, r1, r8, lsl #17
d0017e9c:	24009b0f 	strcs	r9, [r0], #-2831	; 0xfffff4f1
d0017ea0:	36faf503 	ldrbtcc	pc, [sl], r3, lsl #10	; <UNPREDICTABLE>
d0017ea4:	f8d9e054 			; <UNDEFINED> instruction: 0xf8d9e054
d0017ea8:	455b3014 	ldrbmi	r3, [fp, #-20]	; 0xffffffec
d0017eac:	4be8d012 	blmi	0xcfa4befc
d0017eb0:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d0017eb4:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0017eb8:	aa1eaafc 	bge	0xd07c2ab0
d0017ebc:	1545eb02 	strbne	lr, [r5, #-2818]	; 0xfffff4fe
d0017ec0:	692868ec 	stmdbvs	r8!, {r2, r3, r5, r6, r7, fp, sp, lr}
d0017ec4:	7e2969ea 	vnmulvc.f16	s12, s19, s21	; <UNPREDICTABLE>
d0017ec8:	66184de2 	ldrvs	r4, [r8], -r2, ror #27
d0017ecc:	e9c3447d 	stmib	r3, {r0, r2, r3, r4, r5, r6, sl, lr}^
d0017ed0:	e4595416 	ldrb	r5, [r9], #-1046	; 0xfffffbea
d0017ed4:	aa14ab46 	bge	0xd0542bf4
d0017ed8:	1345eb03 	movtne	lr, #23299	; 0x5b03
d0017edc:	f1a35caa 			; <UNDEFINED> instruction: 0xf1a35caa
d0017ee0:	3b900ca0 	blcc	0xce41b168
d0017ee4:	cb0f9204 	blgt	0xd03fc6fc
d0017ee8:	000fe88d 	andeq	lr, pc, sp, lsl #17
d0017eec:	000fe89c 	muleq	pc, ip, r8	; <UNPREDICTABLE>
d0017ef0:	f91ef7fb 			; <UNDEFINED> instruction: 0xf91ef7fb
d0017ef4:	46822d04 	strmi	r2, [r2], r4, lsl #26
d0017ef8:	f64fd120 			; <UNDEFINED> instruction: 0xf64fd120
d0017efc:	f7fb00d7 			; <UNDEFINED> instruction: 0xf7fb00d7
d0017f00:	2000f9b3 			; <UNDEFINED> instruction: 0x2000f9b3
d0017f04:	8000f8d6 	ldrdhi	pc, [r0], -r6
d0017f08:	f9aef7fb 			; <UNDEFINED> instruction: 0xf9aef7fb
d0017f0c:	ab142100 	blge	0xd0520314
d0017f10:	2b055ceb 	blcs	0xd016f2c4
d0017f14:	b288d10b 	addlt	sp, r8, #-1073741822	; 0xc0000002
d0017f18:	ea409106 	b	0xd103c338
d0017f1c:	f44000c0 	vst4.<illegal width 64>	{d16-d19}, [r0], r0
d0017f20:	f0404032 			; <UNDEFINED> instruction: 0xf0404032
d0017f24:	b28000c0 	addlt	r0, r0, #192	; 0xc0
d0017f28:	f99ef7fb 			; <UNDEFINED> instruction: 0xf99ef7fb
d0017f2c:	46509906 	ldrbmi	r9, [r0], -r6, lsl #18
d0017f30:	f1093501 			; <UNDEFINED> instruction: 0xf1093501
d0017f34:	f7fb0920 			; <UNDEFINED> instruction: 0xf7fb0920
d0017f38:	e76cfa4a 	strb	pc, [ip, -sl, asr #20]!	; <UNPREDICTABLE>
d0017f3c:	e7e64629 	strb	r4, [r6, r9, lsr #12]!
d0017f40:	23009910 	movwcs	r9, #2320	; 0x910
d0017f44:	f851462a 			; <UNDEFINED> instruction: 0xf851462a
d0017f48:	34011024 	strcc	r1, [r1], #-36	; 0xffffffdc
d0017f4c:	ffb8f7fb 			; <UNDEFINED> instruction: 0xffb8f7fb
d0017f50:	6d989b0f 	vldrvs	d9, [r8, #60]	; 0x3c
d0017f54:	429c69b3 	addsmi	r6, ip, #2932736	; 0x2cc000
d0017f58:	f7ffd3f2 			; <UNDEFINED> instruction: 0xf7ffd3f2
d0017f5c:	2b00baaa 	blcs	0xd0046a0c
d0017f60:	aa35f47f 	bge	0xd0d95164
d0017f64:	210448bc 			; <UNDEFINED> instruction: 0x210448bc
d0017f68:	f7fb4478 			; <UNDEFINED> instruction: 0xf7fb4478
d0017f6c:	2800f871 	stmdacs	r0, {r0, r4, r5, r6, fp, ip, sp, lr, pc}
d0017f70:	2330db0e 	teqcs	r0, #14336	; 0x3800
d0017f74:	4400fb03 	strmi	pc, [r0], #-2819	; 0xfffff4fd
d0017f78:	34baf504 	ldrtcc	pc, [sl], #1284	; 0x504	; <UNPREDICTABLE>
d0017f7c:	3036f894 	mlascc	r6, r4, r8, pc	; <UNPREDICTABLE>
d0017f80:	f894b133 			; <UNDEFINED> instruction: 0xf894b133
d0017f84:	b14b3034 	cmplt	fp, r4, lsr r0
d0017f88:	303bf894 	mlascc	fp, r4, r8, pc	; <UNPREDICTABLE>
d0017f8c:	d0052b04 	andle	r2, r5, r4, lsl #22
d0017f90:	447848b2 	ldrbtmi	r4, [r8], #-2226	; 0xfffff74e
d0017f94:	fad0f7f9 	blx	0xcf455f80
d0017f98:	ba19f7ff 	blt	0xd0695f9c
d0017f9c:	23304cb0 	teqcs	r0, #176, 24	; 0xb000
d0017fa0:	fb03447c 	blx	0xd00e919a
d0017fa4:	23004000 	movwcs	r4, #0
d0017fa8:	30baf500 	adcscc	pc, sl, r0, lsl #10
d0017fac:	6b024619 	blvs	0xd00a9818
d0017fb0:	f7fb6da0 			; <UNDEFINED> instruction: 0xf7fb6da0
d0017fb4:	f7ffff85 			; <UNDEFINED> instruction: 0xf7ffff85
d0017fb8:	88aaba0a 	stmiahi	sl!, {r1, r3, r9, fp, ip, sp, pc}
d0017fbc:	43532330 	cmpmi	r3, #48, 6	; 0xc0000000
d0017fc0:	f50118e1 			; <UNDEFINED> instruction: 0xf50118e1
d0017fc4:	f89131ba 			; <UNDEFINED> instruction: 0xf89131ba
d0017fc8:	2a002036 	bcs	0xd00200a8
d0017fcc:	f503d143 			; <UNDEFINED> instruction: 0xf503d143
d0017fd0:	331033ba 	tstcc	r0, #-402653182	; 0xe8000002
d0017fd4:	68d84423 	ldmvs	r8, {r0, r1, r5, sl, lr}^
d0017fd8:	69da6919 	ldmibvs	sl, {r0, r3, r4, r8, fp, sp, lr}^
d0017fdc:	66a27e1b 	ssatvs	r7, #3, fp, lsl #28
d0017fe0:	8016e9c4 	andshi	lr, r6, r4, asr #19
d0017fe4:	1318e9c4 	tstne	r8, #196, 18	; 0x310000
d0017fe8:	35083601 	strcc	r3, [r8, #-1537]	; 0xfffff9ff
d0017fec:	429e697b 	addsmi	r6, lr, #2015232	; 0x1ec000
d0017ff0:	6da3d202 	sfmvs	f5, 1, [r3, #8]!
d0017ff4:	d0e02b00 	rscle	r2, r0, r0, lsl #22
d0017ff8:	f64d4b9a 			; <UNDEFINED> instruction: 0xf64d4b9a
d0017ffc:	447b52f8 	ldrbtmi	r5, [fp], #-760	; 0xfffffd08
d0018000:	f64d5899 			; <UNDEFINED> instruction: 0xf64d5899
d0018004:	589a52fc 	ldmpl	sl, {r2, r3, r4, r5, r6, r7, r9, ip, lr}
d0018008:	33baf503 			; <UNDEFINED> instruction: 0x33baf503
d001800c:	0802eb01 	stmdaeq	r2, {r0, r8, r9, fp, sp, lr, pc}
d0018010:	f108689e 			; <UNDEFINED> instruction: 0xf108689e
d0018014:	f0220203 			; <UNDEFINED> instruction: 0xf0220203
d0018018:	92060203 	andls	r0, r6, #805306368	; 0x30000000
d001801c:	4416b30e 	ldrmi	fp, [r6], #-782	; 0xfffffcf2
d0018020:	031ff106 	tsteq	pc, #-2147483647	; 0x80000001	; <UNPREDICTABLE>
d0018024:	3f80f5b6 	svccc	0x0080f5b6
d0018028:	031ff023 	tsteq	pc, #35	; 0x23	; <UNPREDICTABLE>
d001802c:	d9039307 	stmdble	r3, {r0, r1, r2, r8, r9, ip, pc}
d0018030:	4478488d 	ldrbtmi	r4, [r8], #-2189	; 0xfffff773
d0018034:	fa80f7f9 	blx	0xce056020
d0018038:	f04f4c8c 			; <UNDEFINED> instruction: 0xf04f4c8c
d001803c:	4b8c0a00 	blmi	0xce31a844
d0018040:	4657447c 			; <UNDEFINED> instruction: 0x4657447c
d0018044:	f504447b 			; <UNDEFINED> instruction: 0xf504447b
d0018048:	f5044b5d 			; <UNDEFINED> instruction: 0xf5044b5d
d001804c:	9308398f 	movwls	r3, #35215	; 0x898f
d0018050:	0bf8f10b 	bleq	0xcfe54484
d0018054:	2201e02d 	andcs	lr, r1, #45	; 0x2d
d0018058:	68286b09 	stmdavs	r8!, {r0, r3, r8, r9, fp, sp, lr}
d001805c:	fefcf7fb 	mrc2	7, 7, pc, cr12, cr11, {7}
d0018060:	4646e7c2 	strbmi	lr, [r6], -r2, asr #15
d0018064:	f899e7dc 			; <UNDEFINED> instruction: 0xf899e7dc
d0018068:	f8d92006 			; <UNDEFINED> instruction: 0xf8d92006
d001806c:	f8b90000 			; <UNDEFINED> instruction: 0xf8b90000
d0018070:	bb425004 	bllt	0xd10ac088
d0018074:	3000f8db 	ldrdcc	pc, [r0], -fp
d0018078:	f100442b 			; <UNDEFINED> instruction: 0xf100442b
d001807c:	1e51050c 	cdpne	5, 5, cr0, cr1, cr12, {0}
d0018080:	f10a9009 			; <UNDEFINED> instruction: 0xf10a9009
d0018084:	f0250a01 			; <UNDEFINED> instruction: 0xf0250a01
d0018088:	424a0503 	submi	r0, sl, #12582912	; 0xc00000
d001808c:	0908f109 	stmdbeq	r8, {r0, r3, r8, ip, sp, lr, pc}
d0018090:	0505eba3 	streq	lr, [r5, #-2979]	; 0xfffff45d
d0018094:	f24f414a 	vrhadd.s8	q10, <illegal reg q7.5>, q5
d0018098:	b2ab2140 	adclt	r2, fp, #64, 2
d001809c:	f7fb920a 			; <UNDEFINED> instruction: 0xf7fb920a
d00180a0:	9809f8b3 	stmdals	r9, {r0, r1, r4, r5, r7, fp, ip, sp, lr, pc}
d00180a4:	9a0a0c2b 	bls	0xd029b158
d00180a8:	21c0f24f 	biccs	pc, r0, pc, asr #4
d00180ac:	f7fb3004 			; <UNDEFINED> instruction: 0xf7fb3004
d00180b0:	f504f8ab 			; <UNDEFINED> instruction: 0xf504f8ab
d00180b4:	6da533af 	stcvs	3, cr3, [r5, #700]!	; 0x2bc
d00180b8:	4592681a 	ldrmi	r6, [r2, #2074]	; 0x81a
d00180bc:	80def080 	sbcshi	pc, lr, r0, lsl #1
d00180c0:	d0d02d00 	sbcsle	r2, r0, r0, lsl #26
d00180c4:	2a01e02d 	bcs	0xd0090180
d00180c8:	212cd114 			; <UNDEFINED> instruction: 0x212cd114
d00180cc:	18634369 	stmdane	r3!, {r0, r3, r5, r6, r8, r9, lr}^
d00180d0:	33aff503 			; <UNDEFINED> instruction: 0x33aff503
d00180d4:	502cf893 	mlapl	ip, r3, r8, pc	; <UNPREDICTABLE>
d00180d8:	3d079b07 	vstrcc	d9, [r7, #-28]	; 0xffffffe4
d00180dc:	9b06469c 	blls	0xd01a9b54
d00180e0:	bf882d01 	svclt	0x00882d01
d00180e4:	9b08469c 	blls	0xd0229b5c
d00180e8:	46654419 			; <UNDEFINED> instruction: 0x46654419
d00180ec:	31aff501 			; <UNDEFINED> instruction: 0x31aff501
d00180f0:	e7c16a8b 	strb	r6, [r1, fp, lsl #21]
d00180f4:	436b2330 	cmnmi	fp, #48, 6	; 0xc0000000
d00180f8:	f50118e1 			; <UNDEFINED> instruction: 0xf50118e1
d00180fc:	f89131ba 			; <UNDEFINED> instruction: 0xf89131ba
d0018100:	b9cd5036 	stmiblt	sp, {r1, r2, r4, r5, ip, lr}^
d0018104:	33baf503 			; <UNDEFINED> instruction: 0x33baf503
d0018108:	33104d5a 	tstcc	r0, #5760	; 0x1680
d001810c:	4423447d 	strtmi	r4, [r3], #-1149	; 0xfffffb83
d0018110:	691968d8 	ldmdbvs	r9, {r3, r4, r6, r7, fp, sp, lr}
d0018114:	7e1b69da 			; <UNDEFINED> instruction: 0x7e1b69da
d0018118:	e9c466a2 	stmib	r4, {r1, r5, r7, r9, sl, sp, lr}^
d001811c:	e9c45016 	stmib	r4, {r1, r2, r4, ip, lr}^
d0018120:	4d551318 	ldclmi	3, cr1, [r5, #-96]	; 0xffffffa0
d0018124:	447d9c54 	ldrbtmi	r9, [sp], #-3156	; 0xfffff3ac
d0018128:	cd0f3558 	cfstr32gt	mvfx3, [pc, #-352]	; 0xd0017fd0
d001812c:	682bc40f 	stmdavs	fp!, {r0, r1, r2, r3, sl, lr, pc}
d0018130:	24006023 	strcs	r6, [r0], #-35	; 0xffffffdd
d0018134:	b96ff7ff 	stmdblt	pc!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}^	; <UNPREDICTABLE>
d0018138:	f44f6b0b 			; <UNDEFINED> instruction: 0xf44f6b0b
d001813c:	f0435700 			; <UNDEFINED> instruction: 0xf0435700
d0018140:	e79a0301 	ldr	r0, [sl, r1, lsl #6]
d0018144:	ffffe18d 			; <UNDEFINED> instruction: 0xffffe18d
d0018148:	ffffe186 			; <UNDEFINED> instruction: 0xffffe186
d001814c:	ffffe183 			; <UNDEFINED> instruction: 0xffffe183
d0018150:	0000493e 	andeq	r4, r0, lr, lsr r9
d0018154:	fffff847 			; <UNDEFINED> instruction: 0xfffff847
d0018158:	000048a2 	andeq	r4, r0, r2, lsr #17
d001815c:	0000487c 	andeq	r4, r0, ip, ror r8
d0018160:	fffff7b1 			; <UNDEFINED> instruction: 0xfffff7b1
d0018164:	000047f8 	strdeq	r4, [r0], -r8
d0018168:	fffff72f 			; <UNDEFINED> instruction: 0xfffff72f
d001816c:	fffff738 			; <UNDEFINED> instruction: 0xfffff738
d0018170:	000047ac 	andeq	r4, r0, ip, lsr #15
d0018174:	0000478c 	andeq	r4, r0, ip, lsl #15
d0018178:	fffff733 			; <UNDEFINED> instruction: 0xfffff733
d001817c:	fffff740 			; <UNDEFINED> instruction: 0xfffff740
d0018180:	0000474a 	andeq	r4, r0, sl, asr #14
d0018184:	00004726 	andeq	r4, r0, r6, lsr #14
d0018188:	fffff71f 			; <UNDEFINED> instruction: 0xfffff71f
d001818c:	fffff72f 			; <UNDEFINED> instruction: 0xfffff72f
d0018190:	fffff72a 			; <UNDEFINED> instruction: 0xfffff72a
d0018194:	000046c8 	andeq	r4, r0, r8, asr #13
d0018198:	fffff6fc 			; <UNDEFINED> instruction: 0xfffff6fc
d001819c:	fffff735 			; <UNDEFINED> instruction: 0xfffff735
d00181a0:	0000466a 	andeq	r4, r0, sl, ror #12
d00181a4:	00004656 	andeq	r4, r0, r6, asr r6
d00181a8:	00004642 	andeq	r4, r0, r2, asr #12
d00181ac:	000045e0 	andeq	r4, r0, r0, ror #11
d00181b0:	fffff63f 			; <UNDEFINED> instruction: 0xfffff63f
d00181b4:	0000459c 	muleq	r0, ip, r5
d00181b8:	fffff65f 			; <UNDEFINED> instruction: 0xfffff65f
d00181bc:	0000456c 	andeq	r4, r0, ip, ror #10
d00181c0:	fffff4a3 			; <UNDEFINED> instruction: 0xfffff4a3
d00181c4:	fffff64a 			; <UNDEFINED> instruction: 0xfffff64a
d00181c8:	fffff649 			; <UNDEFINED> instruction: 0xfffff649
d00181cc:	fffff646 			; <UNDEFINED> instruction: 0xfffff646
d00181d0:	fffff63b 			; <UNDEFINED> instruction: 0xfffff63b
d00181d4:	000044fc 	strdeq	r4, [r0], -ip
d00181d8:	fffff616 			; <UNDEFINED> instruction: 0xfffff616
d00181dc:	fffff62e 			; <UNDEFINED> instruction: 0xfffff62e
d00181e0:	fffff738 			; <UNDEFINED> instruction: 0xfffff738
d00181e4:	00004466 	andeq	r4, r0, r6, ror #8
d00181e8:	000043ee 	andeq	r4, r0, lr, ror #7
d00181ec:	fffff6c5 			; <UNDEFINED> instruction: 0xfffff6c5
d00181f0:	000043c4 	andeq	r4, r0, r4, asr #7
d00181f4:	000043a2 	andeq	r4, r0, r2, lsr #7
d00181f8:	fffff58a 			; <UNDEFINED> instruction: 0xfffff58a
d00181fc:	fffff52f 			; <UNDEFINED> instruction: 0xfffff52f
d0018200:	00004348 	andeq	r4, r0, r8, asr #6
d0018204:	fffff499 			; <UNDEFINED> instruction: 0xfffff499
d0018208:	ffffdaf1 			; <UNDEFINED> instruction: 0xffffdaf1
d001820c:	ffffdaea 			; <UNDEFINED> instruction: 0xffffdaea
d0018210:	ffffdae3 			; <UNDEFINED> instruction: 0xffffdae3
d0018214:	fffff48a 			; <UNDEFINED> instruction: 0xfffff48a
d0018218:	fffff48a 			; <UNDEFINED> instruction: 0xfffff48a
d001821c:	fffff4a7 			; <UNDEFINED> instruction: 0xfffff4a7
d0018220:	fffff4b4 			; <UNDEFINED> instruction: 0xfffff4b4
d0018224:	fffff4bc 			; <UNDEFINED> instruction: 0xfffff4bc
d0018228:	fffff4ca 			; <UNDEFINED> instruction: 0xfffff4ca
d001822c:	00004232 	andeq	r4, r0, r2, lsr r2
d0018230:	fffff4fa 			; <UNDEFINED> instruction: 0xfffff4fa
d0018234:	00004180 	andeq	r4, r0, r0, lsl #3
d0018238:	fffff4d2 			; <UNDEFINED> instruction: 0xfffff4d2
d001823c:	fffff4c9 			; <UNDEFINED> instruction: 0xfffff4c9
d0018240:	000040ec 	andeq	r4, r0, ip, ror #1
d0018244:	000040ba 	strheq	r4, [r0], -sl
d0018248:	000040a4 	andeq	r4, r0, r4, lsr #1
d001824c:	00025ff2 	strdeq	r5, [r2], -r2
d0018250:	0000402c 	andeq	r4, r0, ip, lsr #32
d0018254:	fffff3b7 			; <UNDEFINED> instruction: 0xfffff3b7
d0018258:	fffff097 			; <UNDEFINED> instruction: 0xfffff097
d001825c:	fffff31d 			; <UNDEFINED> instruction: 0xfffff31d
d0018260:	00003f3c 	andeq	r3, r0, ip, lsr pc
d0018264:	00003ede 	ldrdeq	r3, [r0], -lr
d0018268:	fffff2d8 			; <UNDEFINED> instruction: 0xfffff2d8
d001826c:	00003e9c 	muleq	r0, ip, lr
d0018270:	00003e98 	muleq	r0, r8, lr
d0018274:	fffff222 			; <UNDEFINED> instruction: 0xfffff222
d0018278:	00003db6 			; <UNDEFINED> instruction: 0x00003db6
d001827c:	2d009308 	stccs	3, cr9, [r0, #-32]	; 0xffffffe0
d0018280:	af4ff47f 	svcge	0x004ff47f
d0018284:	52f8f64d 	rscspl	pc, r8, #80740352	; 0x4d00000
d0018288:	9148f8df 	ldrdls	pc, [r8, #-143]	; 0xffffff71
d001828c:	415ef504 	cmpmi	lr, r4, lsl #10	; <UNPREDICTABLE>
d0018290:	a144f8df 	ldrdge	pc, [r4, #-143]	; 0xffffff71
d0018294:	f64d58a0 			; <UNDEFINED> instruction: 0xf64d58a0
d0018298:	44f952fc 	ldrbtmi	r5, [r9], #764	; 0x2fc
d001829c:	58a244fa 	stmiapl	r2!, {r1, r3, r4, r5, r6, r7, sl, lr}
d00182a0:	f1091cf4 			; <UNDEFINED> instruction: 0xf1091cf4
d00182a4:	f10a0940 			; <UNDEFINED> instruction: 0xf10a0940
d00182a8:	f0240a40 			; <UNDEFINED> instruction: 0xf0240a40
d00182ac:	44480403 	strbmi	r0, [r8], #-1027	; 0xfffffbfd
d00182b0:	f958f001 			; <UNDEFINED> instruction: 0xf958f001
d00182b4:	0008eb09 	andeq	lr, r8, r9, lsl #22
d00182b8:	0208eba4 	andeq	lr, r8, #164, 22	; 0x29000
d00182bc:	f0014629 			; <UNDEFINED> instruction: 0xf0014629
d00182c0:	9b08f943 	blls	0xd02567d4
d00182c4:	0824f103 	stmdaeq	r4!, {r0, r1, r8, ip, sp, lr, pc}
d00182c8:	59b0f503 	ldmibpl	r0!, {r0, r1, r8, sl, ip, sp, lr, pc}
d00182cc:	3004f8d9 	ldrdcc	pc, [r4], -r9
d00182d0:	d33f429d 	teqle	pc, #-805306359	; 0xd0000009
d00182d4:	0840f04f 	stmdaeq	r0, {r0, r1, r2, r3, r6, ip, sp, lr, pc}^
d00182d8:	2100ad1e 	tstcs	r0, lr, lsl sp
d00182dc:	46284642 	strtmi	r4, [r8], -r2, asr #12
d00182e0:	f932f001 			; <UNDEFINED> instruction: 0xf932f001
d00182e4:	2208493d 	andcs	r4, r8, #999424	; 0xf4000
d00182e8:	44794628 	ldrbtmi	r4, [r9], #-1576	; 0xfffff9d8
d00182ec:	f0014444 			; <UNDEFINED> instruction: 0xf0014444
d00182f0:	2302f939 	movwcs	pc, #10553	; 0x2939	; <UNPREDICTABLE>
d00182f4:	46319a07 	ldrtmi	r9, [r1], -r7, lsl #20
d00182f8:	e9cd972b 	stmib	sp, {r0, r1, r3, r5, r8, r9, sl, ip, pc}^
d00182fc:	f8d93820 			; <UNDEFINED> instruction: 0xf8d93820
d0018300:	331f300c 	tstcc	pc, #12
d0018304:	f0234413 			; <UNDEFINED> instruction: 0xf0234413
d0018308:	443b031f 	ldrtmi	r0, [fp], #-799	; 0xfffffce1
d001830c:	bf183f00 	svclt	0x00183f00
d0018310:	93242701 			; <UNDEFINED> instruction: 0x93242701
d0018314:	972c2301 	strls	r2, [ip, -r1, lsl #6]!
d0018318:	93254f31 			; <UNDEFINED> instruction: 0x93254f31
d001831c:	447f4b2c 	ldrbtmi	r4, [pc], #-2860	; 0xd0018324
d0018320:	3426e9cd 	strtcc	lr, [r6], #-2509	; 0xfffff633
d0018324:	eb072320 	bl	0xd01e0fac
d0018328:	e9cd0008 	stmib	sp, {r3}^
d001832c:	93294622 			; <UNDEFINED> instruction: 0x93294622
d0018330:	f7f7463e 			; <UNDEFINED> instruction: 0xf7f7463e
d0018334:	902dff21 	eorls	pc, sp, r1, lsr #30
d0018338:	c60fcd0f 	strgt	ip, [pc], -pc, lsl #26
d001833c:	c60fcd0f 	strgt	ip, [pc], -pc, lsl #26
d0018340:	c60fcd0f 	strgt	ip, [pc], -pc, lsl #26
d0018344:	000fe895 	muleq	pc, r5, r8	; <UNPREDICTABLE>
d0018348:	000fe886 	andeq	lr, pc, r6, lsl #17
d001834c:	601f9b53 	andsvs	r9, pc, r3, asr fp	; <UNPREDICTABLE>
d0018350:	b861f7ff 	stmdalt	r1!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}^
d0018354:	3008f898 	mulcc	r8, r8, r8
d0018358:	2b013b07 	blcs	0xd0066f7c
d001835c:	f8d8d908 			; <UNDEFINED> instruction: 0xf8d8d908
d0018360:	22040004 	andcs	r0, r4, #4
d0018364:	46419b06 	strbmi	r9, [r1], -r6, lsl #22
d0018368:	44504418 	ldrbmi	r4, [r0], #-1048	; 0xfffffbe8
d001836c:	f8faf001 			; <UNDEFINED> instruction: 0xf8faf001
d0018370:	f1083501 			; <UNDEFINED> instruction: 0xf1083501
d0018374:	e7a9082c 	str	r0, [r9, ip, lsr #16]!
d0018378:	447e4e1a 	ldrbtmi	r4, [lr], #-3610	; 0xfffff1e6
d001837c:	33d2f506 	bicscc	pc, r2, #25165824	; 0x1800000
d0018380:	f5b7691f 			; <UNDEFINED> instruction: 0xf5b7691f
d0018384:	f47f7f80 			; <UNDEFINED> instruction: 0xf47f7f80
d0018388:	6db3ac9c 	ldcvs	12, cr10, [r3, #624]!	; 0x270
d001838c:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0018390:	4b15a890 	blmi	0xd05825d8
d0018394:	f7ff447b 			; <UNDEFINED> instruction: 0xf7ff447b
d0018398:	4d14b979 	vldrmi.16	s22, [r4, #-242]	; 0xffffff0e	; <UNPREDICTABLE>
d001839c:	447d2330 	ldrbtmi	r2, [sp], #-816	; 0xfffffcd0
d00183a0:	530afb03 	movwpl	pc, #43779	; 0xab03	; <UNPREDICTABLE>
d00183a4:	33baf503 			; <UNDEFINED> instruction: 0x33baf503
d00183a8:	2034f893 	mlascs	r4, r3, r8, pc	; <UNPREDICTABLE>
d00183ac:	d1044294 			; <UNDEFINED> instruction: 0xd1044294
d00183b0:	3037f893 	mlascc	r7, r3, r8, pc	; <UNPREDICTABLE>
d00183b4:	f43f459b 			; <UNDEFINED> instruction: 0xf43f459b
d00183b8:	4b0dace1 	blmi	0xd0383744
d00183bc:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d00183c0:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d00183c4:	4a0ba876 	bmi	0xd03025a4
d00183c8:	f7ff447a 			; <UNDEFINED> instruction: 0xf7ff447a
d00183cc:	bf00b993 	svclt	0x0000b993
d00183d0:	d0010000 	andle	r0, r1, r0
d00183d4:	00025bca 	andeq	r5, r2, sl, asr #23
d00183d8:	00025bc8 	andeq	r5, r2, r8, asr #23
d00183dc:	0000016a 	andeq	r0, r0, sl, ror #2
d00183e0:	00025b46 	andeq	r5, r2, r6, asr #22
d00183e4:	00003b62 	andeq	r3, r0, r2, ror #22
d00183e8:	ffffee73 			; <UNDEFINED> instruction: 0xffffee73
d00183ec:	00003b3e 	andeq	r3, r0, lr, lsr fp
d00183f0:	00003b20 	andeq	r3, r0, r0, lsr #22
d00183f4:	ffffee52 			; <UNDEFINED> instruction: 0xffffee52

Disassembly of section .text.sidc_compile_project:

d00183f8 <.text.sidc_compile_project>:
d00183f8:	43f7e92d 	mvnsmi	lr, #737280	; 0xb4000
d00183fc:	802cf8dd 	ldrdhi	pc, [ip], -sp	; <UNPREDICTABLE>
d0018400:	9c0c460f 	stcls	6, cr4, [ip], {15}
d0018404:	46052100 	strmi	r2, [r5], -r0, lsl #2
d0018408:	46204616 			; <UNDEFINED> instruction: 0x46204616
d001840c:	f8c82214 			; <UNDEFINED> instruction: 0xf8c82214
d0018410:	f8dd1000 			; <UNDEFINED> instruction: 0xf8dd1000
d0018414:	93019028 	movwls	r9, #4136	; 0x1028
d0018418:	f896f001 			; <UNDEFINED> instruction: 0xf896f001
d001841c:	1e72b185 	expned	f3, f5
d0018420:	2a0f9b01 	bcs	0xd03ff02c
d0018424:	4632d80c 	ldrtmi	sp, [r2], -ip, lsl #16
d0018428:	46284639 			; <UNDEFINED> instruction: 0x46284639
d001842c:	f8cd940c 			; <UNDEFINED> instruction: 0xf8cd940c
d0018430:	f8cd802c 			; <UNDEFINED> instruction: 0xf8cd802c
d0018434:	b0039028 	andlt	r9, r3, r8, lsr #32
d0018438:	43f0e8bd 	mvnsmi	lr, #12386304	; 0xbd0000
d001843c:	bf8cf7fe 	svclt	0x008cf7fe
d0018440:	447d4d04 	ldrbtmi	r4, [sp], #-3332	; 0xfffff2fc
d0018444:	c40fcd0f 	strgt	ip, [pc], #-3343	; 0xd001844c
d0018448:	2000682b 	andcs	r6, r0, fp, lsr #16
d001844c:	b0036023 	andlt	r6, r3, r3, lsr #32
d0018450:	83f0e8bd 	mvnshi	lr, #12386304	; 0xbd0000
d0018454:	000029b6 			; <UNDEFINED> instruction: 0x000029b6

Disassembly of section .text.memset:

d0019548 <.text.memset>:
d0019548:	b2c9b15a 	sbclt	fp, r9, #-2147483626	; 0x80000016
d001954c:	b4104603 	ldrlt	r4, [r0], #-1539	; 0xfffff9fd
d0019550:	461a1884 	ldrmi	r1, [sl], -r4, lsl #17
d0019554:	42a33301 	adcmi	r3, r3, #67108864	; 0x4000000
d0019558:	d1fa7011 	mvnsle	r7, r1, lsl r0
d001955c:	4b04f85d 	blmi	0xd01576d8
d0019560:	47704770 			; <UNDEFINED> instruction: 0x47704770

Disassembly of section .text.memcpy:

d0019564 <.text.memcpy>:
d0019564:	4603b162 	strmi	fp, [r3], -r2, ror #2
d0019568:	1885b430 	stmne	r5, {r4, r5, sl, ip, sp, pc}
d001956c:	461c780a 	ldrmi	r7, [ip], -sl, lsl #16
d0019570:	31013301 	tstcc	r1, r1, lsl #6
d0019574:	42abb2d2 	adcmi	fp, fp, #536870925	; 0x2000000d
d0019578:	d1f77022 	mvnsle	r7, r2, lsr #32
d001957c:	4770bc30 			; <UNDEFINED> instruction: 0x4770bc30
d0019580:	bf004770 	svclt	0x00004770

Disassembly of section .text.memcmp:

d0019584 <.text.memcmp>:
d0019584:	46034402 	strmi	r4, [r3], -r2, lsl #8
d0019588:	d0134290 	mulsle	r3, r0, r2
d001958c:	e002b470 	and	fp, r2, r0, ror r4
d0019590:	46034290 			; <UNDEFINED> instruction: 0x46034290
d0019594:	f813d00b 			; <UNDEFINED> instruction: 0xf813d00b
d0019598:	f8115b01 			; <UNDEFINED> instruction: 0xf8115b01
d001959c:	46184b01 	ldrmi	r4, [r8], -r1, lsl #22
d00195a0:	42a5b2ee 	adcmi	fp, r5, #-536870898	; 0xe000000e
d00195a4:	d0f3b2e3 	rscsle	fp, r3, r3, ror #5
d00195a8:	bc701af0 			; <UNDEFINED> instruction: 0xbc701af0
d00195ac:	20004770 	andcs	r4, r0, r0, ror r7
d00195b0:	4770bc70 			; <UNDEFINED> instruction: 0x4770bc70
d00195b4:	47702000 	ldrbmi	r2, [r0, -r0]!

Disassembly of section .text.sb_f_fixed:

d00195b8 <.text.sb_f_fixed>:
d00195b8:	0b40eeb5 	bleq	0xd1055094
d00195bc:	4ff0e92d 	svcmi	0x00f0e92d
d00195c0:	fa10eef1 	blx	0xd045518c
d00195c4:	d0354606 	eorsle	r4, r5, r6, lsl #12
d00195c8:	6b04eeb2 	blvs	0xd0155098
d00195cc:	eeb02400 	cdp	4, 11, cr2, cr0, cr0, {0}
d00195d0:	eeb47b40 	vcmp.f64	d7, d0
d00195d4:	eef10bc6 	vsqrt.f64	d16, d6
d00195d8:	da22fa10 	ble	0xd08d7e20
d00195dc:	6b00eeb7 	blvs	0xd00550c0
d00195e0:	7bc6eeb4 	blvc	0xcf1d50b8
d00195e4:	fa10eef1 	blx	0xd04551b0
d00195e8:	80a6f140 	adchi	pc, r6, r0, asr #2
d00195ec:	5b04eeb2 	blpl	0xd01550bc
d00195f0:	73a1f46f 			; <UNDEFINED> instruction: 0x73a1f46f
d00195f4:	eeb4e004 	cdp	0, 11, cr14, cr4, cr4, {0}
d00195f8:	eef17bc6 	vsqrt.f64	d23, d6
d00195fc:	d504fa10 	strle	pc, [r4, #-2576]	; 0xfffff5f0
d0019600:	ee273c01 	cdp	12, 2, cr3, cr7, cr1, {0}
d0019604:	429c7b05 	addsmi	r7, ip, #5120	; 0x1400
d0019608:	ea24daf5 	b	0xd09501e4
d001960c:	ea6f73e4 	b	0xd1bf65a4
d0019610:	459c0c01 	ldrmi	r0, [ip, #3073]	; 0xc01
d0019614:	2000dd16 	andcs	sp, r0, r6, lsl sp
d0019618:	8ff0e8bd 	svchi	0x00f0e8bd
d001961c:	7f9af5b4 	svcvc	0x009af5b4
d0019620:	ee87d0dc 	mcr	0, 4, sp, cr7, cr12, {6}
d0019624:	34017b06 	strcc	r7, [r1], #-2822	; 0xfffff4fa
d0019628:	7bc6eeb4 	blvc	0xcf1d5100
d001962c:	fa10eef1 	blx	0xd04551f8
d0019630:	e7d3daf4 			; <UNDEFINED> instruction: 0xe7d3daf4
d0019634:	eeb02300 	cdp	3, 11, cr2, cr0, cr0, {0}
d0019638:	461c7b40 	ldrmi	r7, [ip], -r0, asr #22
d001963c:	0c01ea6f 			; <UNDEFINED> instruction: 0x0c01ea6f
d0019640:	dce8459c 	cfstr64le	mvdx4, [r8], #624	; 0x270
d0019644:	0b00f04f 	bleq	0xd0055788
d0019648:	5b04eeb2 	blpl	0xd0155118
d001964c:	0902ea41 	stmdbeq	r2, {r0, r6, r9, fp, sp, lr, pc}
d0019650:	38fff10c 	ldmcc	pc!, {r2, r3, r8, ip, sp, lr, pc}^	; <UNPREDICTABLE>
d0019654:	43f74658 	mvnsmi	r4, #88, 12	; 0x5800000
d0019658:	0a30f04f 	beq	0xd0c5579c
d001965c:	4b38ed9f 	blmi	0xd0e54ce0
d0019660:	0b40eeb5 	bleq	0xd105513c
d0019664:	fa10eef1 	blx	0xd0455230
d0019668:	42a3d030 	adcmi	sp, r3, #48	; 0x30
d001966c:	eefddc2e 	cdp	12, 15, cr13, cr13, cr14, {1}
d0019670:	f10b6bc7 			; <UNDEFINED> instruction: 0xf10b6bc7
d0019674:	ee160b01 	vnmls.f64	d0, d6, d1
d0019678:	ee161a90 	vmov	r1, s13
d001967c:	29092a90 	stmdbcs	r9, {r4, r7, r9, fp, sp}
d0019680:	2209bfa8 	andcs	fp, r9, #168, 30	; 0x2a0
d0019684:	0f11f1bb 	svceq	0x0011f1bb
d0019688:	72e2ea22 	rscvc	lr, r2, #139264	; 0x22000
d001968c:	2a90ee06 	bcs	0xce454eac
d0019690:	6be6eeb8 	blvs	0xcf9d5178
d0019694:	7b46ee37 	blvc	0xd11d4f78
d0019698:	7b05ee27 	blvc	0xd0194f3c
d001969c:	459cdc16 	ldrmi	sp, [ip, #3094]	; 0xc16
d00196a0:	3230d018 	eorscc	sp, r0, #24
d00196a4:	5432b2d2 	ldrtpl	fp, [r2], #-722	; 0xfffffd2e
d00196a8:	3b013001 	blcc	0xd00656b4
d00196ac:	d0b34543 	adcsle	r4, r3, r3, asr #10
d00196b0:	d1d51c59 	bicsle	r1, r5, r9, asr ip
d00196b4:	0f00f1b9 	svceq	0x0000f1b9
d00196b8:	eeb5d0d2 	mrc	0, 5, sp, cr5, cr2, {6}
d00196bc:	f04f0b40 			; <UNDEFINED> instruction: 0xf04f0b40
d00196c0:	5432022e 	ldrtpl	r0, [r2], #-558	; 0xfffffdd2
d00196c4:	eef13001 	cdp	0, 15, cr3, cr1, cr1, {0}
d00196c8:	d1cefa10 	bicle	pc, lr, r0, lsl sl	; <UNPREDICTABLE>
d00196cc:	d0ec459c 	smlalle	r4, ip, ip, r5
d00196d0:	e7e82230 			; <UNDEFINED> instruction: 0xe7e82230
d00196d4:	dd1e2905 	vldrle.16	s4, [lr, #-10]	; <UNPREDICTABLE>
d00196d8:	dd172800 	ldcle	8, cr2, [r7, #-0]
d00196dc:	0e00eb06 	vmlaeq.f64	d14, d0, d6
d00196e0:	f8124672 			; <UNDEFINED> instruction: 0xf8124672
d00196e4:	292e1d01 	stmdbcs	lr!, {r0, r8, sl, fp, ip}
d00196e8:	0502eb07 	streq	lr, [r2, #-2823]	; 0xfffff4f9
d00196ec:	2938d003 	ldmdbcs	r8!, {r0, r1, ip, lr, pc}
d00196f0:	f882d91f 			; <UNDEFINED> instruction: 0xf882d91f
d00196f4:	3501a000 	strcc	sl, [r1, #-0]
d00196f8:	2800d1f3 	stmdacs	r0, {r0, r1, r4, r5, r6, r7, r8, ip, lr, pc}
d00196fc:	4672dd06 	ldrbtmi	sp, [r2], -r6, lsl #26
d0019700:	1c01f812 	stcne	8, cr15, [r1], {18}
d0019704:	1901f802 	stmdbne	r1, {r1, fp, ip, sp, lr, pc}
d0019708:	d1f94296 			; <UNDEFINED> instruction: 0xd1f94296
d001970c:	0231f04f 	eorseq	pc, r1, #79	; 0x4f
d0019710:	70323001 	eorsvc	r3, r2, r1
d0019714:	d1c8e7c9 	bicle	lr, r8, r9, asr #15
d0019718:	7bc4eeb4 	blvc	0xcf1551f0
d001971c:	fa10eef1 	blx	0xd04552e8
d0019720:	2800dcda 	stmdacs	r0, {r1, r3, r4, r6, r7, sl, fp, ip, lr, pc}
d0019724:	1832d0c1 	ldmdane	r2!, {r0, r6, r7, ip, lr, pc}
d0019728:	2c01f812 	stccs	8, cr15, [r1], {18}
d001972c:	d5bc07d2 	ldrle	r0, [ip, #2002]!	; 0x7d2
d0019730:	3101e7d2 	ldrdcc	lr, [r1, -r2]
d0019734:	e7b87011 			; <UNDEFINED> instruction: 0xe7b87011
d0019738:	e77f4623 	ldrb	r4, [pc, -r3, lsr #12]!
d001973c:	8000f3af 	andhi	pc, r0, pc, lsr #7
d0019740:	812dea11 			; <UNDEFINED> instruction: 0x812dea11
d0019744:	3d719799 	ldclcc	7, cr9, [r1, #-612]!	; 0xfffffd9c

Disassembly of section .text.sb_f_exponent:

d0019748 <.text.sb_f_exponent>:
d0019748:	0b40eeb5 	bleq	0xd1055224
d001974c:	4ff0e92d 	svcmi	0x00f0e92d
d0019750:	fa10eef1 	blx	0xd045531c
d0019754:	d0344607 	eorsle	r4, r4, r7, lsl #12
d0019758:	6b04eeb2 	blvs	0xd0155228
d001975c:	0bc6eeb4 	bleq	0xcf1d5234
d0019760:	fa10eef1 	blx	0xd045532c
d0019764:	80cef2c0 	sbchi	pc, lr, r0, asr #5
d0019768:	7b40eeb0 	blvc	0xd1055230
d001976c:	e0022400 	and	r2, r2, r0, lsl #8
d0019770:	7f9af5b4 	svcvc	0x009af5b4
d0019774:	ee87d007 	cdp	0, 8, cr13, cr7, cr7, {0}
d0019778:	34017b06 	strcc	r7, [r1], #-2822	; 0xfffff4fa
d001977c:	7bc6eeb4 	blvc	0xcf1d5254
d0019780:	fa10eef1 	blx	0xd045534c
d0019784:	eeb7daf4 			; <UNDEFINED> instruction: 0xeeb7daf4
d0019788:	eeb46b00 	vmov.f64	d6, #64	; 0x3e000000  0.125
d001978c:	eef17bc6 	vsqrt.f64	d23, d6
d0019790:	d519fa10 	ldrle	pc, [r9, #-2576]	; 0xfffff5f0
d0019794:	5b04eeb2 	blpl	0xd0155264
d0019798:	70a1f46f 	adcvc	pc, r1, pc, ror #8
d001979c:	eeb4e004 	cdp	0, 11, cr14, cr4, cr4, {0}
d00197a0:	eef17bc6 	vsqrt.f64	d23, d6
d00197a4:	d50ffa10 	strle	pc, [pc, #-2576]	; 0xd0018d9c
d00197a8:	ee273c01 	cdp	12, 2, cr3, cr7, cr1, {0}
d00197ac:	42847b05 	addmi	r7, r4, #5120	; 0x1400
d00197b0:	f111daf5 			; <UNDEFINED> instruction: 0xf111daf5
d00197b4:	d50a0e01 	strle	r0, [sl, #-3585]	; 0xfffff1ff
d00197b8:	2102463e 	tstcs	r2, lr, lsr r6
d00197bc:	22002501 	andcs	r2, r0, #4194304	; 0x400000
d00197c0:	eeb0e062 	cdp	0, 11, cr14, cr0, cr2, {3}
d00197c4:	24007b40 	strcs	r7, [r0], #-2880	; 0xfffff4c0
d00197c8:	0e01f111 	mcreq	1, 0, pc, cr1, cr1, {0}	; <UNPREDICTABLE>
d00197cc:	2500d4f4 	strcs	sp, [r0, #-1268]	; 0xfffffb0c
d00197d0:	5b04eeb2 	blpl	0xd01552a0
d00197d4:	0902ea41 	stmdbeq	r2, {r0, r6, r9, fp, sp, lr, pc}
d00197d8:	462a1c88 	strtmi	r1, [sl], -r8, lsl #25
d00197dc:	0807ea6f 	stmdaeq	r7, {r0, r1, r2, r3, r5, r6, r9, fp, sp, lr, pc}
d00197e0:	0a30f04f 	beq	0xd0c55924
d00197e4:	0b2ef04f 	bleq	0xd0bd5928
d00197e8:	4b49ed9f 	blmi	0xd1294e6c
d00197ec:	0b40eeb5 	bleq	0xd10552c8
d00197f0:	fa10eef1 	blx	0xd04553bc
d00197f4:	4575d114 	ldrbmi	sp, [r5, #-276]!	; 0xfffffeec
d00197f8:	2130d002 	teqcs	r0, r2
d00197fc:	320154b9 	andcc	r5, r1, #-1191182336	; 0xb9000000
d0019800:	42853501 	addmi	r3, r5, #4194304	; 0x400000
d0019804:	2d01d03d 	stccs	0, cr13, [r1, #-244]	; 0xffffff0c
d0019808:	f1b9d1f0 			; <UNDEFINED> instruction: 0xf1b9d1f0
d001980c:	d0ed0f00 	rscle	r0, sp, r0, lsl #30
d0019810:	0b40eeb5 	bleq	0xd10552ec
d0019814:	b002f807 	andlt	pc, r2, r7, lsl #16
d0019818:	eef13201 	cdp	2, 15, cr3, cr1, cr1, {0}
d001981c:	d0eafa10 	rscle	pc, sl, r0, lsl sl	; <UNPREDICTABLE>
d0019820:	6bc7eefd 	blvs	0xcf21541c
d0019824:	6a90ee16 	bvs	0xce455084
d0019828:	1a90ee16 	bne	0xce455088
d001982c:	bfa82e09 	svclt	0x00a82e09
d0019830:	45752109 	ldrbmi	r2, [r5, #-265]!	; 0xfffffef7
d0019834:	71e1ea21 	mvnvc	lr, r1, lsr #20
d0019838:	1a90ee06 	bne	0xce455058
d001983c:	6be6eeb8 	blvs	0xcf9d5324
d0019840:	7b46ee37 	blvc	0xd11d5124
d0019844:	7b05ee27 	blvc	0xd01950e8
d0019848:	3130d002 	teqcc	r0, r2
d001984c:	e7d5b2c9 	ldrb	fp, [r5, r9, asr #5]
d0019850:	dd462e05 	stclle	14, cr2, [r6, #-20]	; 0xffffffec
d0019854:	dd0d2a00 	vstrle	s4, [sp, #-0]
d0019858:	f81118b9 			; <UNDEFINED> instruction: 0xf81118b9
d001985c:	2e2e6d01 	cdpcs	13, 2, cr6, cr14, cr1, {0}
d0019860:	0c01eb08 			; <UNDEFINED> instruction: 0x0c01eb08
d0019864:	2e38d003 	cdpcs	0, 3, cr13, cr8, cr3, {0}
d0019868:	f881d949 			; <UNDEFINED> instruction: 0xf881d949
d001986c:	f1bca000 			; <UNDEFINED> instruction: 0xf1bca000
d0019870:	d1f23fff 	ldrshle	r3, [r2, #255]!	; 0xff
d0019874:	f04f3501 			; <UNDEFINED> instruction: 0xf04f3501
d0019878:	34010131 	strcc	r0, [r1], #-305	; 0xfffffecf
d001987c:	70394285 	eorsvc	r4, r9, r5, lsl #5
d0019880:	18bed1c1 	ldmne	lr!, {r0, r6, r7, r8, ip, lr, pc}
d0019884:	1c911c55 	ldcne	12, cr1, [r1], {85}	; 0x55
d0019888:	bf142b00 	svclt	0x00142b00
d001988c:	20652045 	rsbcs	r2, r5, r5, asr #32
d0019890:	70302c00 	eorsvc	r2, r0, r0, lsl #24
d0019894:	232dbfb4 			; <UNDEFINED> instruction: 0x232dbfb4
d0019898:	2c00232b 	stccs	3, cr2, [r0], {43}	; 0x2b
d001989c:	bfb8557b 	svclt	0x00b8557b
d00198a0:	2c634264 	sfmcs	f4, 2, [r3], #-400	; 0xfffffe70
d00198a4:	4b1cdd06 	blmi	0xd0750cc4
d00198a8:	0304fba3 	movweq	pc, #19363	; 0x4ba3	; <UNPREDICTABLE>
d00198ac:	3330095b 	teqcc	r0, #1490944	; 0x16c000
d00198b0:	1cd1547b 	cfldrdne	mvd5, [r1], {123}	; 0x7b
d00198b4:	187d4a19 	ldmdane	sp!, {r0, r3, r4, r9, fp, lr}^
d00198b8:	0304fba2 	movweq	pc, #19362	; 0x4ba2	; <UNPREDICTABLE>
d00198bc:	08db1c88 	ldmeq	fp, {r3, r7, sl, fp, ip}^
d00198c0:	6203fba2 	andvs	pc, r3, #165888	; 0x28800
d00198c4:	0683eb03 	streq	lr, [r3], r3, lsl #22
d00198c8:	eba408d2 	bl	0xce91bc18
d00198cc:	eb020446 	bl	0xd009a9ec
d00198d0:	34300282 	ldrtcc	r0, [r0], #-642	; 0xfffffd7e
d00198d4:	0342eba3 	movteq	lr, #11171	; 0x2ba3
d00198d8:	547b3330 	ldrbtpl	r3, [fp], #-816	; 0xfffffcd0
d00198dc:	e8bd706c 	pop	{r2, r3, r5, r6, ip, sp, lr}
d00198e0:	d18d8ff0 	strdle	r8, [sp, r0]
d00198e4:	7bc4eeb4 	blvc	0xcf1553bc
d00198e8:	fa10eef1 	blx	0xd04554b4
d00198ec:	2a00dcb2 	bcs	0xd0050bbc
d00198f0:	18b9d086 	ldmne	r9!, {r1, r2, r7, ip, lr, pc}
d00198f4:	1c01f811 	stcne	8, cr15, [r1], {17}
d00198f8:	d58107c9 	strle	r0, [r1, #1993]	; 0x7c9
d00198fc:	3601e7aa 	strcc	lr, [r1], -sl, lsr #15
d0019900:	e77d700e 	ldrb	r7, [sp, -lr]!
d0019904:	7b40eeb0 	blvc	0xd10553cc
d0019908:	e73c2400 	ldr	r2, [ip, -r0, lsl #8]!
d001990c:	8000f3af 	andhi	pc, r0, pc, lsr #7
d0019910:	812dea11 			; <UNDEFINED> instruction: 0x812dea11
d0019914:	3d719799 	ldclcc	7, cr9, [r1, #-612]!	; 0xfffffd9c
d0019918:	51eb851f 	mvnpl	r8, pc, lsl r5
d001991c:	cccccccd 	stclgt	12, cr12, [ip], {205}	; 0xcd

Disassembly of section .text.sb_flush.part.0:

d0019920 <.text.sb_flush.part.0>:
d0019920:	2090f8d0 			; <UNDEFINED> instruction: 0x2090f8d0
d0019924:	4b07b16a 	blmi	0xd0205ed4
d0019928:	0110f100 	tsteq	r0, r0, lsl #2	; <UNPREDICTABLE>
d001992c:	681b689b 	ldmdavs	fp, {r0, r1, r3, r4, r7, fp, sp, lr}
d0019930:	685bb510 	ldmdavs	fp, {r4, r8, sl, ip, sp, pc}^
d0019934:	20004604 	andcs	r4, r0, r4, lsl #12
d0019938:	23004798 	movwcs	r4, #1944	; 0x798
d001993c:	3090f8c4 	addscc	pc, r0, r4, asr #17
d0019940:	4770bd10 			; <UNDEFINED> instruction: 0x4770bd10
d0019944:	2001f000 	andcs	pc, r1, r0

Disassembly of section .text.sb_char:

d0019948 <.text.sb_char>:
d0019948:	b51068c3 	ldrlt	r6, [r0, #-2243]	; 0xfffff73d
d001994c:	b1834604 	orrlt	r4, r3, r4, lsl #12
d0019950:	3090f8d0 			; <UNDEFINED> instruction: 0x3090f8d0
d0019954:	44031c5a 	strmi	r1, [r3], #-3162	; 0xfffff3a6
d0019958:	f8c02a80 			; <UNDEFINED> instruction: 0xf8c02a80
d001995c:	74192090 	ldrvc	r2, [r9], #-144	; 0xffffff70
d0019960:	68a3d013 	stmiavs	r3!, {r0, r1, r4, ip, lr, pc}
d0019964:	4200f06f 	andmi	pc, r0, #111	; 0x6f
d0019968:	d2014293 	andle	r4, r1, #805306377	; 0x30000009
d001996c:	60a33301 	adcvs	r3, r3, r1, lsl #6
d0019970:	6800bd10 	stmdavs	r0, {r4, r8, sl, fp, ip, sp, pc}
d0019974:	d0f42800 	rscsle	r2, r4, r0, lsl #16
d0019978:	68a36862 	stmiavs	r3!, {r1, r5, r6, fp, sp, lr}
d001997c:	bf182a00 	svclt	0x00182a00
d0019980:	42933a01 	addsmi	r3, r3, #4096	; 0x1000
d0019984:	54c1d2ee 	strbpl	sp, [r1], #750	; 0x2ee
d0019988:	f7ffe7eb 			; <UNDEFINED> instruction: 0xf7ffe7eb
d001998c:	68a3ffc9 	stmiavs	r3!, {r0, r3, r6, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0019990:	bf00e7e8 	svclt	0x0000e7e8

Disassembly of section .text.sb_number:

d00199a8 <.text.sb_number>:
d00199a8:	4ff0e92d 	svcmi	0x00f0e92d
d00199ac:	8b02ed2d 	blhi	0xd00d4e68
d00199b0:	ee08b09b 	mcr	0, 0, fp, cr8, cr11, {4}
d00199b4:	93070a10 	movwls	r0, #31248	; 0x7a10
d00199b8:	92069b2b 	andls	r9, r6, #44032	; 0xac00
d00199bc:	d13e2b00 	teqle	lr, r0, lsl #22
d00199c0:	e9dd4bbf 	ldmib	sp, {r0, r1, r2, r3, r4, r5, r7, r8, r9, fp, lr}^
d00199c4:	447b1206 	ldrbtmi	r1, [fp], #-518	; 0xfffffdfa
d00199c8:	460b9305 	strmi	r9, [fp], -r5, lsl #6
d00199cc:	d13e4313 	teqle	lr, r3, lsl r3
d00199d0:	9a2a9b2a 	bls	0xd0ac0680
d00199d4:	bf183b00 	svclt	0x00183b00
d00199d8:	2a002301 	bcs	0xd00225e4
d00199dc:	9303d137 	movwls	sp, #12599	; 0x3137
d00199e0:	2b009b27 	blcs	0xd0040684
d00199e4:	9b28d179 	blls	0xd0a4dfd0
d00199e8:	f1000759 			; <UNDEFINED> instruction: 0xf1000759
d00199ec:	ea4f8101 	b	0xd13f9df8
d00199f0:	9a2c0983 	bls	0xd0b1c004
d00199f4:	1a40f3c9 	bne	0xd1056920
d00199f8:	0920f009 	stmdbeq	r0!, {r0, r3, ip, sp, lr, pc}
d00199fc:	2a004653 	bcs	0xd002b350
d0019a00:	9a26d072 	bls	0xd09cdbd0
d0019a04:	f0002a10 			; <UNDEFINED> instruction: 0xf0002a10
d0019a08:	9a2680f8 	bls	0xd09b9df0
d0019a0c:	f0002a02 			; <UNDEFINED> instruction: 0xf0002a02
d0019a10:	9a268144 	bls	0xd09b9f28
d0019a14:	9a032a08 	bls	0xd00e423c
d0019a18:	8122f000 	msrhi	CPSR_x, r0
d0019a1c:	2600992a 	strcs	r9, [r0], -sl, lsr #18
d0019a20:	82a0f8df 	adchi	pc, r0, #14614528	; 0xdf0000
d0019a24:	44f84291 	ldrbtmi	r4, [r8], #657	; 0x291
d0019a28:	9a03dc69 	bls	0xd0110bd4
d0019a2c:	19942700 	ldmibne	r4, {r8, r9, sl, sp}
d0019a30:	44239a29 	strtmi	r9, [r3], #-2601	; 0xfffff5d7
d0019a34:	f0c04293 			; <UNDEFINED> instruction: 0xf0c04293
d0019a38:	463c80e8 	ldrtmi	r8, [ip], -r8, ror #1
d0019a3c:	4ba2e0e7 	blmi	0xce8d1de0
d0019a40:	1206e9dd 	andne	lr, r6, #3620864	; 0x374000
d0019a44:	9305447b 	movwls	r4, #21627	; 0x547b
d0019a48:	4313460b 	tstmi	r3, #11534336	; 0xb00000
d0019a4c:	ab09d0c0 	blge	0xd028dd54
d0019a50:	26012200 	strcs	r2, [r1], -r0, lsl #4
d0019a54:	e9dd9304 	ldmib	sp, {r2, r8, r9, ip, pc}^
d0019a58:	469b3406 	ldrmi	r3, [fp], r6, lsl #8
d0019a5c:	46272300 	strtmi	r2, [r7], -r0, lsl #6
d0019a60:	9b269303 	blls	0xd09be674
d0019a64:	e9cd4619 	stmib	sp, {r0, r3, r4, r9, sl, lr}^
d0019a68:	23001200 	movwcs	r1, #512	; 0x200
d0019a6c:	0ffa203f 	svceq	0x00fa203f
d0019a70:	b008f8cd 	andlt	pc, r8, sp, asr #17
d0019a74:	469a4699 			; <UNDEFINED> instruction: 0x469a4699
d0019a78:	99023801 	stmdbls	r2, {r0, fp, ip, sp}
d0019a7c:	0420f1c0 	strteq	pc, [r0], #-448	; 0xfffffe40
d0019a80:	0520f1a0 	streq	pc, [r0, #-416]!	; 0xfffffe60
d0019a84:	f1b040c1 			; <UNDEFINED> instruction: 0xf1b040c1
d0019a88:	fa073fff 	blx	0xd01e9a8c
d0019a8c:	fa27fe04 	blx	0xd0a192a4
d0019a90:	fa26fc05 	blx	0xd09d8aac
d0019a94:	fa06f404 	blx	0xd01d6aac
d0019a98:	ea41f505 	b	0xd1096eb4
d0019a9c:	fa06010e 	blx	0xd0199edc
d0019aa0:	ea44f800 	b	0xd1157aa8
d0019aa4:	ea410405 	b	0xd105aac0
d0019aa8:	d072010c 	rsbsle	r0, r2, ip, lsl #2
d0019aac:	f0011895 			; <UNDEFINED> instruction: 0xf0011895
d0019ab0:	eb430101 	bl	0xd10d9ebc
d0019ab4:	ea410c03 	b	0xd105cac8
d0019ab8:	46630205 	strbtmi	r0, [r3], -r5, lsl #4
d0019abc:	bc00e9dd 			; <UNDEFINED> instruction: 0xbc00e9dd
d0019ac0:	bf084563 	svclt	0x00084563
d0019ac4:	d3d7455a 	bicsle	r4, r7, #377487360	; 0x16800000
d0019ac8:	020bebb2 	andeq	lr, fp, #182272	; 0x2c800
d0019acc:	0909ea48 	stmdbeq	r9, {r3, r6, r9, fp, sp, lr, pc}
d0019ad0:	0a0aea44 	beq	0xd02d43e8
d0019ad4:	030ceb63 	movweq	lr, #52067	; 0xcb63
d0019ad8:	2301e7ce 	movwcs	lr, #6094	; 0x17ce
d0019adc:	092df04f 	pusheq	{r0, r1, r2, r3, r6, ip, sp, lr, pc}
d0019ae0:	9a2c469a 	bls	0xd0b2b550
d0019ae4:	d18c2a00 	orrle	r2, ip, r0, lsl #20
d0019ae8:	f0129a28 			; <UNDEFINED> instruction: 0xf0129a28
d0019aec:	d16a0610 	cmnle	sl, r0, lsl r6
d0019af0:	81d8f8df 	ldrsbhi	pc, [r8, #143]	; 0x8f	; <UNPREDICTABLE>
d0019af4:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d0019af8:	4291992a 	addsmi	r9, r1, #688128	; 0xa8000
d0019afc:	9903dd95 	stmdbls	r3, {r0, r2, r4, r7, r8, sl, fp, ip, lr, pc}
d0019b00:	198a982a 	stmibne	sl, {r1, r3, r5, fp, ip, pc}
d0019b04:	44131a47 	ldrmi	r1, [r3], #-2631	; 0xfffff5b9
d0019b08:	443b9a29 	ldrtmi	r9, [fp], #-2601	; 0xfffff5d7
d0019b0c:	d87c429a 	ldmdale	ip!, {r1, r3, r4, r7, r9, lr}^
d0019b10:	24009b28 	strcs	r9, [r0], #-2856	; 0xfffff4d8
d0019b14:	0501f003 	streq	pc, [r1, #-3]
d0019b18:	0f00f1ba 	svceq	0x0000f1ba
d0019b1c:	b16ed14d 	cmnlt	lr, sp, asr #2
d0019b20:	1000f898 	mulne	r0, r8, r8
d0019b24:	0a10ee18 	beq	0xd045538c
d0019b28:	ff0ef7ff 			; <UNDEFINED> instruction: 0xff0ef7ff
d0019b2c:	d1052e02 	tstle	r5, r2, lsl #28
d0019b30:	1001f898 	mulne	r1, r8, r8
d0019b34:	0a10ee18 	beq	0xd045539c
d0019b38:	ff06f7ff 			; <UNDEFINED> instruction: 0xff06f7ff
d0019b3c:	b1471e7e 	hvclt	29166	; 0x71ee
d0019b40:	7a10ee18 	bvc	0xd04553a8
d0019b44:	21303e01 	teqcs	r0, r1, lsl #28
d0019b48:	f7ff4638 			; <UNDEFINED> instruction: 0xf7ff4638
d0019b4c:	1c72fefd 	ldclne	14, cr15, [r2], #-1012	; 0xfffffc0c
d0019b50:	9b03d1f8 	blls	0xd010e338
d0019b54:	af09b163 	svcge	0x0009b163
d0019b58:	ee189b03 	vnmls.f64	d9, d8, d3
d0019b5c:	443b8a10 	ldrtmi	r8, [fp], #-2576	; 0xfffff5f0
d0019b60:	f816461e 			; <UNDEFINED> instruction: 0xf816461e
d0019b64:	46401d01 	strbmi	r1, [r0], -r1, lsl #26
d0019b68:	feeef7ff 	mcr2	7, 7, pc, cr14, cr15, {7}	; <UNPREDICTABLE>
d0019b6c:	d1f842b7 	ldrhle	r4, [r8, #39]!	; 0x27
d0019b70:	1e65b155 	mcrne	1, 3, fp, cr5, cr5, {2}
d0019b74:	ee18b144 	mnfem	f3, f4
d0019b78:	3d014a10 	vstrcc	s8, [r1, #-64]	; 0xffffffc0
d0019b7c:	46202120 	strtmi	r2, [r0], -r0, lsr #2
d0019b80:	fee2f7ff 	mcr2	7, 7, pc, cr2, cr15, {7}	; <UNPREDICTABLE>
d0019b84:	d1f81c6b 	mvnsle	r1, fp, ror #24
d0019b88:	ecbdb01b 	ldc	0, cr11, [sp], #108	; 0x6c
d0019b8c:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d0019b90:	99058ff0 	stmdbls	r5, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
d0019b94:	9903440a 	stmdbls	r3, {r1, r3, sl, lr}
d0019b98:	31017813 	tstcc	r1, r3, lsl r8
d0019b9c:	91039a04 	tstls	r3, r4, lsl #20
d0019ba0:	3b01f802 	blcc	0xd0097bb0
d0019ba4:	030aea59 	movweq	lr, #43609	; 0xaa59
d0019ba8:	f43f9204 			; <UNDEFINED> instruction: 0xf43f9204
d0019bac:	2940af19 	stmdbcs	r0, {r0, r3, r4, r8, r9, sl, fp, sp, pc}^
d0019bb0:	af16f63f 	svcge	0x0016f63f
d0019bb4:	465746cb 	ldrbmi	r4, [r7], -fp, asr #13
d0019bb8:	4649e757 			; <UNDEFINED> instruction: 0x4649e757
d0019bbc:	0a10ee18 	beq	0xd0455424
d0019bc0:	fec2f7ff 	mcr2	7, 6, pc, cr2, cr15, {7}	; <UNPREDICTABLE>
d0019bc4:	e9dde7ab 	ldmib	sp, {r0, r1, r3, r5, r7, r8, r9, sl, sp, lr, pc}^
d0019bc8:	430a1206 	movwmi	r1, #41478	; 0xa206
d0019bcc:	af19f47f 	svcge	0x0019f47f
d0019bd0:	2a089a26 	bcs	0xd0240470
d0019bd4:	9a03d167 	bls	0xd010e178
d0019bd8:	d1642a00 	cmnle	r4, r0, lsl #20
d0019bdc:	21302201 	teqcs	r0, r1, lsl #4
d0019be0:	80ecf8df 	ldrdhi	pc, [ip], #143	; 0x8f	; <UNPREDICTABLE>
d0019be4:	44f89e2c 	ldrbtmi	r9, [r8], #3628	; 0xe2c
d0019be8:	f88d9203 			; <UNDEFINED> instruction: 0xf88d9203
d0019bec:	e7831024 	str	r1, [r3, r4, lsr #32]
d0019bf0:	f04f2301 			; <UNDEFINED> instruction: 0xf04f2301
d0019bf4:	469a092b 	ldrmi	r0, [sl], fp, lsr #18
d0019bf8:	9a2be773 	bls	0xd0b139cc
d0019bfc:	f8dfb352 			; <UNDEFINED> instruction: 0xf8dfb352
d0019c00:	260280d4 			; <UNDEFINED> instruction: 0x260280d4
d0019c04:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d0019c08:	9a29e776 	bls	0xd0a939e8
d0019c0c:	9b281ad4 	blls	0xd0a20764
d0019c10:	0303f003 	movweq	pc, #12291	; 0x3003	; <UNPREDICTABLE>
d0019c14:	d1022b02 	tstle	r2, r2, lsl #22
d0019c18:	2b009b2a 	blcs	0xd00408c8
d0019c1c:	9b28db33 	blls	0xd0a508f0
d0019c20:	0501f013 	streq	pc, [r1, #-19]	; 0xffffffed
d0019c24:	af78f47f 	svcge	0x0078f47f
d0019c28:	3bfff104 	blcc	0xd0016040
d0019c2c:	d0402c00 	suble	r2, r0, r0, lsl #24
d0019c30:	ee189402 	cfmuls	mvf9, mvf8, mvf2
d0019c34:	f10b4a10 			; <UNDEFINED> instruction: 0xf10b4a10
d0019c38:	21203bff 	strdcs	r3, [r0, -pc]!
d0019c3c:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0019c40:	f1bbfe83 			; <UNDEFINED> instruction: 0xf1bbfe83
d0019c44:	d1f63fff 	ldrshle	r3, [r6, #255]!	; 0xff
d0019c48:	f1ba9c02 			; <UNDEFINED> instruction: 0xf1ba9c02
d0019c4c:	f43f0f00 			; <UNDEFINED> instruction: 0xf43f0f00
d0019c50:	e7b2af66 	ldr	sl, [r2, r6, ror #30]!
d0019c54:	8080f8df 	ldrdhi	pc, [r0], pc	; <UNPREDICTABLE>
d0019c58:	9a032602 	bls	0xd00e3468
d0019c5c:	e74b44f8 			; <UNDEFINED> instruction: 0xe74b44f8
d0019c60:	a91ab15a 	ldmdbge	sl, {r1, r3, r4, r6, r8, ip, sp, pc}
d0019c64:	f812188a 			; <UNDEFINED> instruction: 0xf812188a
d0019c68:	2a302c45 	bcs	0xd0c24d84
d0019c6c:	f8dfd105 			; <UNDEFINED> instruction: 0xf8dfd105
d0019c70:	2600806c 	strcs	r8, [r0], -ip, rrx
d0019c74:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d0019c78:	f8dfe73e 			; <UNDEFINED> instruction: 0xf8dfe73e
d0019c7c:	26018064 	strcs	r8, [r1], -r4, rrx
d0019c80:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d0019c84:	9b28e738 	blls	0xd0a5396c
d0019c88:	24004427 	strcs	r4, [r0], #-1063	; 0xfffffbd9
d0019c8c:	0501f003 	streq	pc, [r1, #-3]
d0019c90:	0f00f1ba 	svceq	0x0000f1ba
d0019c94:	af43f43f 	svcge	0x0043f43f
d0019c98:	f8dfe78f 			; <UNDEFINED> instruction: 0xf8dfe78f
d0019c9c:	46168048 	ldrmi	r8, [r6], -r8, asr #32
d0019ca0:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d0019ca4:	f8dfe728 			; <UNDEFINED> instruction: 0xf8dfe728
d0019ca8:	26008040 	strcs	r8, [r0], -r0, asr #32
d0019cac:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d0019cb0:	4625e722 	strtmi	lr, [r5], -r2, lsr #14
d0019cb4:	0f00f1ba 	svceq	0x0000f1ba
d0019cb8:	af31f43f 	svcge	0x0031f43f
d0019cbc:	bf00e77d 	svclt	0x0000e77d
d0019cc0:	0000136a 	andeq	r1, r0, sl, ror #6
d0019cc4:	ffffff6e 			; <UNDEFINED> instruction: 0xffffff6e
d0019cc8:	000012d8 	ldrdeq	r1, [r0], -r8
d0019ccc:	fffffe9e 			; <UNDEFINED> instruction: 0xfffffe9e
d0019cd0:	fffffdae 			; <UNDEFINED> instruction: 0xfffffdae
d0019cd4:	fffffd8a 			; <UNDEFINED> instruction: 0xfffffd8a
d0019cd8:	fffffd3c 			; <UNDEFINED> instruction: 0xfffffd3c
d0019cdc:	fffffd1e 			; <UNDEFINED> instruction: 0xfffffd1e
d0019ce0:	fffffd1a 			; <UNDEFINED> instruction: 0xfffffd1a
d0019ce4:	fffffcfe 			; <UNDEFINED> instruction: 0xfffffcfe
d0019ce8:	fffffce6 			; <UNDEFINED> instruction: 0xfffffce6

Disassembly of section .text.sb_float:

d0019d04 <.text.sb_float>:
d0019d04:	4ff0e92d 	svcmi	0x00f0e92d
d0019d08:	bb10ec5c 	bllt	0xd0454e80
d0019d0c:	461eb0df 			; <UNDEFINED> instruction: 0x461eb0df
d0019d10:	73dcea5f 	bicsvc	lr, ip, #389120	; 0x5f000
d0019d14:	460446e0 	strmi	r4, [r4], -r0, ror #13
d0019d18:	4615468a 	ldrmi	r4, [r5], -sl, lsl #13
d0019d1c:	9a10ee10 	bls	0xd0455564
d0019d20:	ed8d9304 	stc	3, cr9, [sp, #16]
d0019d24:	d10a0b00 	tstle	sl, r0, lsl #22
d0019d28:	f1000750 			; <UNDEFINED> instruction: 0xf1000750
d0019d2c:	009380cb 	addseq	r8, r3, fp, asr #1
d0019d30:	1740f3c3 	strbne	pc, [r0, -r3, asr #7]	; <UNPREDICTABLE>
d0019d34:	0320f003 	wfieq
d0019d38:	930346bb 	movwls	r4, #14011	; 0x36bb
d0019d3c:	2701e003 	strcs	lr, [r1, -r3]
d0019d40:	46bb232d 	ldrtmi	r2, [fp], sp, lsr #6
d0019d44:	f04f9303 			; <UNDEFINED> instruction: 0xf04f9303
d0019d48:	21000c00 	tstcs	r0, r0, lsl #24
d0019d4c:	70fff240 	rscsvc	pc, pc, r0, asr #4
d0019d50:	520af3c8 	andpl	pc, sl, #200, 6	; 0x20000003
d0019d54:	f1aa458c 			; <UNDEFINED> instruction: 0xf1aa458c
d0019d58:	bf080e41 	svclt	0x00080e41
d0019d5c:	fa5f4282 	blx	0xd17ea76c
d0019d60:	d03efe8e 	eorsle	pc, lr, lr, lsl #29
d0019d64:	2b099b68 	blcs	0xd0280b0c
d0019d68:	4afcdd4b 	bmi	0xcff5129c
d0019d6c:	0918f10d 	ldmdbeq	r8, {r0, r2, r3, r8, ip, sp, lr, pc}
d0019d70:	237046e0 	cmncs	r0, #224, 12	; 0xe000000
d0019d74:	4649447a 			; <UNDEFINED> instruction: 0x4649447a
d0019d78:	3201203c 	andcc	r2, r1, #60	; 0x3c
d0019d7c:	4618e002 	ldrmi	lr, [r8], -r2
d0019d80:	3f01f812 	svccc	0x0001f812
d0019d84:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d0019d88:	0b01f801 	bleq	0xd0097d94
d0019d8c:	d1f62b00 	mvnsle	r2, r0, lsl #22
d0019d90:	020beb08 	andeq	lr, fp, #8, 22	; 0x2000
d0019d94:	42b22301 	adcsmi	r2, r2, #67108864	; 0x4000000
d0019d98:	8099f0c0 	addshi	pc, r9, r0, asr #1
d0019d9c:	f0052600 			; <UNDEFINED> instruction: 0xf0052600
d0019da0:	2a020203 	bcs	0xd009a5b4
d0019da4:	2b00d102 	blcs	0xd004e1b4
d0019da8:	8093f040 	addshi	pc, r3, r0, asr #32
d0019dac:	0501f015 	streq	pc, [r1, #-21]	; 0xffffffeb
d0019db0:	80bcf040 	adcshi	pc, ip, r0, asr #32
d0019db4:	b1361e75 	teqlt	r6, r5, ror lr
d0019db8:	21203d01 			; <UNDEFINED> instruction: 0x21203d01
d0019dbc:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0019dc0:	1c69fdc3 	stclne	13, cr15, [r9], #-780	; 0xfffffcf4
d0019dc4:	2f00d1f8 	svccs	0x0000d1f8
d0019dc8:	8091f000 	addshi	pc, r1, r0
d0019dcc:	46209903 	strtmi	r9, [r0], -r3, lsl #18
d0019dd0:	fdbaf7ff 	ldc2	7, cr15, [sl, #1020]!	; 0x3fc
d0019dd4:	0f00f1b8 	svceq	0x0000f1b8
d0019dd8:	808df040 	addhi	pc, sp, r0, asr #32
d0019ddc:	e8bdb05f 	pop	{r0, r1, r2, r3, r4, r6, ip, sp, pc}
d0019de0:	464a8ff0 			; <UNDEFINED> instruction: 0x464a8ff0
d0019de4:	0313f3c8 	tsteq	r3, #200, 6	; 0x20000003	; <UNPREDICTABLE>
d0019de8:	f0404313 			; <UNDEFINED> instruction: 0xf0404313
d0019dec:	f1be80ae 			; <UNDEFINED> instruction: 0xf1be80ae
d0019df0:	f2000f19 	vrecps.f32	d0, d0, d9
d0019df4:	f8df80d4 			; <UNDEFINED> instruction: 0xf8df80d4
d0019df8:	234ec368 	movtcs	ip, #58216	; 0xe368
d0019dfc:	44fc2149 	ldrbtmi	r2, [ip], #329	; 0x149
d0019e00:	9b04e0ab 	blls	0xd01520b4
d0019e04:	ed9db12b 	ldfd	f3, [sp, #172]	; 0xac
d0019e08:	eeb17b00 	vmov.f64	d7, #16	; 0x40800000  4.0
d0019e0c:	ed8d7b47 	vstr	d7, [sp, #284]	; 0x11c
d0019e10:	f1be7b00 			; <UNDEFINED> instruction: 0xf1be7b00
d0019e14:	f00a0f19 			; <UNDEFINED> instruction: 0xf00a0f19
d0019e18:	bf8c0adf 	svclt	0x008c0adf
d0019e1c:	23012300 	movwcs	r2, #4864	; 0x1300
d0019e20:	9b689304 	blls	0xd1a3ea38
d0019e24:	f2c02b00 	vqdmlsl.s<illegal width 8>	q9, d0, d0
d0019e28:	f1ba80c5 			; <UNDEFINED> instruction: 0xf1ba80c5
d0019e2c:	f0400f47 			; <UNDEFINED> instruction: 0xf0400f47
d0019e30:	9b6880c7 	blls	0xd1a3a154
d0019e34:	bf082b00 	svclt	0x00082b00
d0019e38:	93682301 	cmnls	r8, #67108864	; 0x4000000
d0019e3c:	7b00ed9d 	blvc	0xd00554b8
d0019e40:	7b40eeb5 	blvc	0xd105591c
d0019e44:	fa10eef1 	blx	0xd0455a10
d0019e48:	80d0f000 	sbcshi	pc, r0, r0
d0019e4c:	6b04eeb2 	blvs	0xd015591c
d0019e50:	7bc6eeb4 	blvc	0xcf1d5928
d0019e54:	fa10eef1 	blx	0xd0455a20
d0019e58:	8170f2c0 	cmnhi	r0, r0, asr #5	; <UNPREDICTABLE>
d0019e5c:	0a00f04f 	beq	0xd0055fa0
d0019e60:	f5bae003 			; <UNDEFINED> instruction: 0xf5bae003
d0019e64:	f0007f9a 			; <UNDEFINED> instruction: 0xf0007f9a
d0019e68:	ee87810f 	sins	f0, #10.0
d0019e6c:	f10a7b06 			; <UNDEFINED> instruction: 0xf10a7b06
d0019e70:	eeb40a01 	vmov.f32	s0, #65	; 0x3e080000  0.1328125
d0019e74:	eef17bc6 	vsqrt.f64	d23, d6
d0019e78:	daf2fa10 	ble	0xcfcd86c0
d0019e7c:	6b00eeb7 	blvs	0xd0055960
d0019e80:	7bc6eeb4 	blvc	0xcf1d5958
d0019e84:	fa10eef1 	blx	0xd0455a50
d0019e88:	eeb2d511 	mrc	5, 5, sp, cr2, cr1, {0}
d0019e8c:	eeb75b04 	vmov.f64	d5, #116	; 0x3fa00000  1.250
d0019e90:	e0036b00 	and	r6, r3, r0, lsl #22
d0019e94:	7fa2f51a 	svcvc	0x00a2f51a
d0019e98:	80fef000 	rscshi	pc, lr, r0
d0019e9c:	7b05ee27 	blvc	0xd0195740
d0019ea0:	3afff10a 	bcc	0xd00162d0
d0019ea4:	7bc6eeb4 	blvc	0xcf1d597c
d0019ea8:	fa10eef1 	blx	0xd0455a74
d0019eac:	9b68d4f2 	blls	0xd1a4f27c
d0019eb0:	f3404553 	vqrshl.u8	q10, <illegal reg q1.5>, q0
d0019eb4:	f11a80f1 			; <UNDEFINED> instruction: 0xf11a80f1
d0019eb8:	f2c00f04 			; <UNDEFINED> instruction: 0xf2c00f04
d0019ebc:	f10a80ed 			; <UNDEFINED> instruction: 0xf10a80ed
d0019ec0:	e0960101 	adds	r0, r6, r1, lsl #2
d0019ec4:	232b2701 			; <UNDEFINED> instruction: 0x232b2701
d0019ec8:	930346bb 	movwls	r4, #14011	; 0x36bb
d0019ecc:	1ab6e73b 	bne	0xcedd3bc0
d0019ed0:	f005e765 			; <UNDEFINED> instruction: 0xf005e765
d0019ed4:	2f000501 	svccs	0x00000501
d0019ed8:	bb8dd167 	bllt	0xce38e47c
d0019edc:	b1361e75 	teqlt	r6, r5, ror lr
d0019ee0:	21303d01 	teqcs	r0, r1, lsl #26
d0019ee4:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0019ee8:	1c6afd2f 	stclne	13, cr15, [sl], #-188	; 0xffffff44
d0019eec:	f1b8d1f8 			; <UNDEFINED> instruction: 0xf1b8d1f8
d0019ef0:	f43f0f00 			; <UNDEFINED> instruction: 0xf43f0f00
d0019ef4:	2500af73 	strcs	sl, [r0, #-3955]	; 0xfffff08d
d0019ef8:	37012700 	strcc	r2, [r1, -r0, lsl #14]
d0019efc:	1b01f819 	blne	0xd0097f68
d0019f00:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0019f04:	4547fd21 	strbmi	pc, [r7, #-3361]	; 0xfffff2df	; <UNPREDICTABLE>
d0019f08:	2d00d3f7 	stccs	3, cr13, [r0, #-988]	; 0xfffffc24
d0019f0c:	af66f43f 	svcge	0x0066f43f
d0019f10:	2e001e75 	mcrcs	14, 0, r1, cr0, cr5, {3}
d0019f14:	af62f43f 	svcge	0x0062f43f
d0019f18:	21203d01 			; <UNDEFINED> instruction: 0x21203d01
d0019f1c:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0019f20:	1c6bfd13 	stclne	13, cr15, [fp], #-76	; 0xffffffb4
d0019f24:	b05fd1f8 	ldrshlt	sp, [pc], #-24	; <UNPREDICTABLE>
d0019f28:	8ff0e8bd 	svchi	0x00f0e8bd
d0019f2c:	f1b8b927 			; <UNDEFINED> instruction: 0xf1b8b927
d0019f30:	d1e10f00 	mvnle	r0, r0, lsl #30
d0019f34:	461ee7ec 	ldrmi	lr, [lr], -ip, ror #15
d0019f38:	46209903 	strtmi	r9, [r0], -r3, lsl #18
d0019f3c:	fd04f7ff 	stc2	7, cr15, [r4, #-1020]	; 0xfffffc04
d0019f40:	0f00f1b8 	svceq	0x0000f1b8
d0019f44:	2501d0e4 	strcs	sp, [r1, #-228]	; 0xffffff1c
d0019f48:	f1bee7d6 			; <UNDEFINED> instruction: 0xf1bee7d6
d0019f4c:	d9470f19 	stmdble	r7, {r0, r3, r4, r8, r9, sl, fp}^
d0019f50:	c210f8df 	andsgt	pc, r0, #14614528	; 0xdf0000
d0019f54:	216e2361 	cmncs	lr, r1, ror #6
d0019f58:	f10d44fc 			; <UNDEFINED> instruction: 0xf10d44fc
d0019f5c:	f10c0918 			; <UNDEFINED> instruction: 0xf10c0918
d0019f60:	ea6f0202 	b	0xd1bda770
d0019f64:	46480c0c 	strbmi	r0, [r8], -ip, lsl #24
d0019f68:	f812e001 			; <UNDEFINED> instruction: 0xf812e001
d0019f6c:	f8003b01 			; <UNDEFINED> instruction: 0xf8003b01
d0019f70:	eb0c1b01 	bl	0xd0320b7c
d0019f74:	46190802 	ldrmi	r0, [r9], -r2, lsl #16
d0019f78:	d1f62b00 	mvnsle	r2, r0, lsl #22
d0019f7c:	020beb08 	andeq	lr, fp, #8, 22	; 0x2000
d0019f80:	d8a44296 	stmiale	r4!, {r1, r2, r4, r7, r9, lr}
d0019f84:	0601f015 			; <UNDEFINED> instruction: 0x0601f015
d0019f88:	af1df43f 	svcge	0x001df43f
d0019f8c:	d1d22f00 	bicsle	r2, r2, r0, lsl #30
d0019f90:	0f00f1b8 	svceq	0x0000f1b8
d0019f94:	af22f43f 	svcge	0x0022f43f
d0019f98:	463e4635 			; <UNDEFINED> instruction: 0x463e4635
d0019f9c:	f8dfe7ac 			; <UNDEFINED> instruction: 0xf8dfe7ac
d0019fa0:	236ec1c8 	cmncs	lr, #200, 2	; 0x32
d0019fa4:	44fc2169 	ldrbtmi	r2, [ip], #361	; 0x169
d0019fa8:	9903e7d7 	stmdbls	r3, {r0, r1, r2, r4, r6, r7, r8, r9, sl, sp, lr, pc}
d0019fac:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0019fb0:	e792fccb 	ldr	pc, [r2, fp, asr #25]
d0019fb4:	f1ba2306 			; <UNDEFINED> instruction: 0xf1ba2306
d0019fb8:	93680f47 	cmnls	r8, #284	; 0x11c
d0019fbc:	af3ef43f 	svcge	0x003ef43f
d0019fc0:	0f45f1ba 	svceq	0x0045f1ba
d0019fc4:	0918f10d 	ldmdbeq	r8, {r0, r2, r3, r8, ip, sp, lr, pc}
d0019fc8:	9b04d154 	blls	0xd014e520
d0019fcc:	0210f005 	andseq	pc, r0, #5
d0019fd0:	46489968 	strbmi	r9, [r8], -r8, ror #18
d0019fd4:	0b00ed9d 	bleq	0xd0055650
d0019fd8:	fbb6f7ff 	blx	0xcedd7fde
d0019fdc:	e6d74680 	ldrb	r4, [r7], r0, lsl #13
d0019fe0:	c188f8df 	ldrdgt	pc, [r8, pc]
d0019fe4:	214e2341 	cmpcs	lr, r1, asr #6
d0019fe8:	e7b644fc 			; <UNDEFINED> instruction: 0xe7b644fc
d0019fec:	f04f2101 			; <UNDEFINED> instruction: 0xf04f2101
d0019ff0:	9b680a00 	blls	0xd1a1c7f8
d0019ff4:	0918f10d 	ldmdbeq	r8, {r0, r2, r3, r8, ip, sp, lr, pc}
d0019ff8:	0210f005 	andseq	pc, r0, #5
d0019ffc:	46481a59 			; <UNDEFINED> instruction: 0x46481a59
d001a000:	ed9d9205 	lfm	f1, 1, [sp, #20]
d001a004:	f7ff0b00 			; <UNDEFINED> instruction: 0xf7ff0b00
d001a008:	4680fad7 	pkhtbmi	pc, r0, r7, asr #21	; <UNPREDICTABLE>
d001a00c:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001a010:	4649aebf 			; <UNDEFINED> instruction: 0x4649aebf
d001a014:	9a052300 	bls	0xd0162c1c
d001a018:	3301e003 	movwcc	lr, #4099	; 0x1003
d001a01c:	f0004598 			; <UNDEFINED> instruction: 0xf0004598
d001a020:	f8118086 			; <UNDEFINED> instruction: 0xf8118086
d001a024:	282e0b01 	stmdacs	lr!, {r0, r8, r9, fp}
d001a028:	f1bad1f7 			; <UNDEFINED> instruction: 0xf1bad1f7
d001a02c:	db020f00 	blle	0xd009dc34
d001a030:	42999968 	addsmi	r9, r9, #104, 18	; 0x1a0000
d001a034:	2a00d334 	bcs	0xd004ed0c
d001a038:	aeaaf47f 	mcrge	4, 5, pc, cr10, cr15, {3}	; <UNPREDICTABLE>
d001a03c:	e002464b 	and	r4, r2, fp, asr #12
d001a040:	f43f4590 			; <UNDEFINED> instruction: 0xf43f4590
d001a044:	f813aea5 			; <UNDEFINED> instruction: 0xf813aea5
d001a048:	32011b01 	andcc	r1, r1, #1024	; 0x400
d001a04c:	d1f7292e 	mvnsle	r2, lr, lsr #18
d001a050:	0308eb09 	movweq	lr, #35593	; 0x8b09
d001a054:	f813e005 			; <UNDEFINED> instruction: 0xf813e005
d001a058:	29301d01 	ldmdbcs	r0!, {r0, r8, sl, fp, ip}
d001a05c:	ae98f47f 	mrcge	4, 4, APSR_nzcv, cr8, cr15, {3}
d001a060:	45904680 	ldrmi	r4, [r0, #1664]	; 0x680
d001a064:	30fff108 	rscscc	pc, pc, r8, lsl #2
d001a068:	f47fd8f5 			; <UNDEFINED> instruction: 0xf47fd8f5
d001a06c:	f108ae91 			; <UNDEFINED> instruction: 0xf108ae91
d001a070:	e68d38ff 			; <UNDEFINED> instruction: 0xe68d38ff
d001a074:	0b00ed9d 	bleq	0xd00556f0
d001a078:	f0059968 			; <UNDEFINED> instruction: 0xf0059968
d001a07c:	46480210 			; <UNDEFINED> instruction: 0x46480210
d001a080:	fa9af7ff 	blx	0xce6d8084
d001a084:	e6834680 	str	r4, [r3], r0, lsl #13
d001a088:	6b00eeb7 	blvs	0xd0055b6c
d001a08c:	7bc6eeb4 	blvc	0xcf1d5b64
d001a090:	fa10eef1 	blx	0xd0455c5c
d001a094:	aef9f53f 	mrcge	5, 7, APSR_nzcv, cr9, cr15, {1}
d001a098:	0210f005 	andseq	pc, r0, #5
d001a09c:	0918f10d 	ldmdbeq	r8, {r0, r2, r3, r8, ip, sp, lr, pc}
d001a0a0:	46489968 	strbmi	r9, [r8], -r8, ror #18
d001a0a4:	39019b04 	stmdbcc	r1, {r2, r8, r9, fp, ip, pc}
d001a0a8:	ed9d9204 	lfm	f1, 1, [sp, #16]
d001a0ac:	f7ff0b00 			; <UNDEFINED> instruction: 0xf7ff0b00
d001a0b0:	9a04fb4b 	bls	0xd0158de4
d001a0b4:	2a004680 	bcs	0xd002babc
d001a0b8:	ae6af47f 	mcrge	4, 3, pc, cr10, cr15, {3}	; <UNPREDICTABLE>
d001a0bc:	46424448 	strbmi	r4, [r2], -r8, asr #8
d001a0c0:	461ae000 	ldrmi	lr, [sl], -r0
d001a0c4:	2a001e53 	bcs	0xd0021a18
d001a0c8:	ae62f43f 	mcrge	4, 3, pc, cr2, cr15, {1}	; <UNPREDICTABLE>
d001a0cc:	1d01f810 	stcne	8, cr15, [r1, #-64]	; 0xffffffc0
d001a0d0:	0cdff001 	ldcleq	0, cr15, [pc], {1}
d001a0d4:	0f45f1bc 	svceq	0x0045f1bc
d001a0d8:	eb09d1f3 	bl	0xd028e8ac
d001a0dc:	46180c03 	ldrmi	r0, [r8], -r3, lsl #24
d001a0e0:	f81ce005 			; <UNDEFINED> instruction: 0xf81ce005
d001a0e4:	f1baad01 			; <UNDEFINED> instruction: 0xf1baad01
d001a0e8:	d1220f30 			; <UNDEFINED> instruction: 0xd1220f30
d001a0ec:	f1004670 			; <UNDEFINED> instruction: 0xf1004670
d001a0f0:	28003eff 	stmdacs	r0, {r0, r1, r2, r3, r4, r5, r6, r7, r9, sl, fp, ip, sp}
d001a0f4:	4543d1f5 	strbmi	sp, [r3, #-501]	; 0xfffffe0b
d001a0f8:	f1c2d212 			; <UNDEFINED> instruction: 0xf1c2d212
d001a0fc:	eb090a01 	bl	0xd025c908
d001a100:	f10d0c03 			; <UNDEFINED> instruction: 0xf10d0c03
d001a104:	44820e17 	strmi	r0, [r2], #3607	; 0xe17
d001a108:	445344c6 	ldrbmi	r4, [r3], #-1222	; 0xfffffb3a
d001a10c:	3b0144d6 	blcc	0xd006b46c
d001a110:	e001444b 	and	r4, r1, fp, asr #8
d001a114:	1f01f81c 	svcne	0x0001f81c
d001a118:	1f01f803 	svcne	0x0001f803
d001a11c:	d1f94573 	mvnsle	r4, r3, ror r5
d001a120:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d001a124:	0202eba8 	andeq	lr, r2, #168, 22	; 0x2a000
d001a128:	0802eb00 	stmdaeq	r2, {r8, r9, fp, sp, lr, pc}
d001a12c:	4643e630 			; <UNDEFINED> instruction: 0x4643e630
d001a130:	f1bae77b 			; <UNDEFINED> instruction: 0xf1bae77b
d001a134:	bf080f2e 	svclt	0x00080f2e
d001a138:	e7dc4670 			; <UNDEFINED> instruction: 0xe7dc4670
d001a13c:	7b00eeb7 	blvc	0xd0055c20
d001a140:	6b00ed9d 	blvs	0xd00557bc
d001a144:	6bc7eeb4 	blvs	0xcf215c1c
d001a148:	fa10eef1 	blx	0xd0455d14
d001a14c:	af4ef57f 	svcge	0x004ef57f
d001a150:	0a00f04f 	beq	0xd0056294
d001a154:	7b00ed9d 	blvc	0xd00557d0
d001a158:	bf00e697 	svclt	0x0000e697
d001a15c:	ffffff84 			; <UNDEFINED> instruction: 0xffffff84
d001a160:	fffffeee 			; <UNDEFINED> instruction: 0xfffffeee
d001a164:	fffffd90 			; <UNDEFINED> instruction: 0xfffffd90
d001a168:	fffffd4e 			; <UNDEFINED> instruction: 0xfffffd4e
d001a16c:	fffffd08 			; <UNDEFINED> instruction: 0xfffffd08

Disassembly of section .text.sb_format.part.0:

d001a1a0 <.text.sb_format.part.0>:
d001a1a0:	4ff0e92d 	svcmi	0x00f0e92d
d001a1a4:	78094688 	stmdavc	r9, {r3, r7, r9, sl, lr}
d001a1a8:	4683b0a7 	strmi	fp, [r3], r7, lsr #1
d001a1ac:	f0002900 			; <UNDEFINED> instruction: 0xf0002900
d001a1b0:	4bfa80b3 	blmi	0xcfeba484
d001a1b4:	f8df4691 			; <UNDEFINED> instruction: 0xf8df4691
d001a1b8:	447ba3e8 	ldrbtmi	sl, [fp], #-1000	; 0xfffffc18
d001a1bc:	4bf99308 	blmi	0xcfe7ede4
d001a1c0:	9309447b 	movwls	r4, #38011	; 0x947b
d001a1c4:	f0402925 			; <UNDEFINED> instruction: 0xf0402925
d001a1c8:	f89880fd 			; <UNDEFINED> instruction: 0xf89880fd
d001a1cc:	2c254001 	stccs	0, cr4, [r5], #-4
d001a1d0:	80fef000 	rscshi	pc, lr, r0
d001a1d4:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d001a1d8:	f1a42600 			; <UNDEFINED> instruction: 0xf1a42600
d001a1dc:	2b100320 	blcs	0xd041ae64
d001a1e0:	e8dfd80a 	ldm	pc, {r1, r3, fp, ip, lr, pc}^	; <UNPREDICTABLE>
d001a1e4:	0978f003 	ldmdbeq	r8!, {r0, r1, ip, sp, lr, pc}^
d001a1e8:	09097509 	stmdbeq	r9, {r0, r3, r8, sl, ip, sp, lr}
d001a1ec:	09090909 	stmdbeq	r9, {r0, r3, r8, fp}
d001a1f0:	6f097209 	svcvs	0x00097209
d001a1f4:	006a0909 	rsbeq	r0, sl, r9, lsl #18
d001a1f8:	f0402c2a 			; <UNDEFINED> instruction: 0xf0402c2a
d001a1fc:	f8d980ef 			; <UNDEFINED> instruction: 0xf8d980ef
d001a200:	f1083000 			; <UNDEFINED> instruction: 0xf1083000
d001a204:	681d0101 	ldmdavs	sp, {r0, r8}
d001a208:	2d001d1a 	stccs	13, cr1, [r0, #-104]	; 0xffffff98
d001a20c:	2000f8c9 	andcs	pc, r0, r9, asr #17
d001a210:	8122f2c0 	smlawthi	r2, r0, r2, pc	; <UNPREDICTABLE>
d001a214:	5f00f5b5 	svcpl	0x0000f5b5
d001a218:	4001f898 	mulmi	r1, r8, r8
d001a21c:	f44fbf28 			; <UNDEFINED> instruction: 0xf44fbf28
d001a220:	2c2e5500 	cfstr32cs	mvfx5, [lr], #-0
d001a224:	80fbf000 	rscshi	pc, fp, r0
d001a228:	37fff04f 	ldrbcc	pc, [pc, pc, asr #32]!	; <UNPREDICTABLE>
d001a22c:	f0002c68 			; <UNDEFINED> instruction: 0xf0002c68
d001a230:	2c6c810d 	stfcsp	f0, [ip], #-52	; 0xffffffcc
d001a234:	811ef000 	tsthi	lr, r0	; <UNPREDICTABLE>
d001a238:	f0002c7a 			; <UNDEFINED> instruction: 0xf0002c7a
d001a23c:	2c748122 	ldfcsp	f0, [r4], #-136	; 0xffffff78
d001a240:	8161f000 	msrhi	SPSR_c, r0
d001a244:	f0002c6a 			; <UNDEFINED> instruction: 0xf0002c6a
d001a248:	230081b3 	movwcs	r8, #435	; 0x1b3
d001a24c:	d0632c00 	rsble	r2, r3, r0, lsl #24
d001a250:	f1012c64 			; <UNDEFINED> instruction: 0xf1012c64
d001a254:	d07d0801 	rsbsle	r0, sp, r1, lsl #16
d001a258:	d07b2c69 	rsbsle	r2, fp, r9, ror #24
d001a25c:	0262f1a4 	rsbeq	pc, r2, #164, 2	; 0x29
d001a260:	01dff004 	bicseq	pc, pc, r4
d001a264:	f1a1b2d2 			; <UNDEFINED> instruction: 0xf1a1b2d2
d001a268:	2a130c58 	bcs	0xd04dd3d0
d001a26c:	fc8cfabc 	stc2	10, cr15, [ip], {188}	; 0xbc	; <UNPREDICTABLE>
d001a270:	1c5cea4f 	mrrcne	10, 4, lr, ip, cr15
d001a274:	48c8d806 	stmiami	r8, {r1, r2, fp, ip, lr, pc}^
d001a278:	f202fa20 	vpmax.s8	d15, d2, d16
d001a27c:	0201f002 	andeq	pc, r1, #2
d001a280:	0c02ea4c 			; <UNDEFINED> instruction: 0x0c02ea4c
d001a284:	0f00f1bc 	svceq	0x0000f1bc
d001a288:	816cf000 	msrhi	SPSR_fs, r0
d001a28c:	f0002c6f 			; <UNDEFINED> instruction: 0xf0002c6f
d001a290:	2958811b 	ldmdbcs	r8, {r0, r1, r3, r4, r8, pc}^
d001a294:	811af000 	tsthi	sl, r0	; <UNPREDICTABLE>
d001a298:	bf0c2c62 	svclt	0x000c2c62
d001a29c:	210a2102 	tstcs	sl, r2, lsl #2
d001a2a0:	2b063b01 	blcs	0xd01a8eac
d001a2a4:	84fdf200 	ldrbthi	pc, [sp], #512	; 0x200	; <UNPREDICTABLE>
d001a2a8:	f013e8df 			; <UNDEFINED> instruction: 0xf013e8df
d001a2ac:	0143014b 	cmpeq	r3, fp, asr #2
d001a2b0:	00480018 	subeq	r0, r8, r8, lsl r0
d001a2b4:	00180018 	andseq	r0, r8, r8, lsl r0
d001a2b8:	f0460048 			; <UNDEFINED> instruction: 0xf0460048
d001a2bc:	f8180602 			; <UNDEFINED> instruction: 0xf8180602
d001a2c0:	e78a4f01 	str	r4, [sl, r1, lsl #30]
d001a2c4:	0601f046 	streq	pc, [r1], -r6, asr #32
d001a2c8:	f046e7f9 			; <UNDEFINED> instruction: 0xf046e7f9
d001a2cc:	e7f60604 	ldrb	r0, [r6, r4, lsl #12]!
d001a2d0:	0610f046 	ldreq	pc, [r0], -r6, asr #32
d001a2d4:	f046e7f3 			; <UNDEFINED> instruction: 0xf046e7f3
d001a2d8:	e7f00608 	ldrb	r0, [r0, r8, lsl #12]!
d001a2dc:	3000f8d9 	ldrdcc	pc, [r0], -r9
d001a2e0:	681a1d18 	ldmdavs	sl, {r3, r4, r8, sl, fp, ip}
d001a2e4:	f8c92300 			; <UNDEFINED> instruction: 0xf8c92300
d001a2e8:	f1a40000 			; <UNDEFINED> instruction: 0xf1a40000
d001a2ec:	f0260058 			; <UNDEFINED> instruction: 0xf0260058
d001a2f0:	2400060c 	strcs	r0, [r0], #-1548	; 0xfffff9f4
d001a2f4:	fab09704 	blx	0xcec3ff0c
d001a2f8:	9602f080 	strls	pc, [r2], -r0, lsl #1
d001a2fc:	09409503 	stmdbeq	r0, {r0, r1, r8, sl, ip, pc}^
d001a300:	94069100 	strls	r9, [r6], #-256	; 0xffffff00
d001a304:	46589005 	ldrbmi	r9, [r8], -r5
d001a308:	f7ff9401 			; <UNDEFINED> instruction: 0xf7ff9401
d001a30c:	f898fb4d 			; <UNDEFINED> instruction: 0xf898fb4d
d001a310:	29001000 	stmdbcs	r0, {ip}
d001a314:	af56f47f 	svcge	0x0056f47f
d001a318:	300cf8db 	ldrdcc	pc, [ip], -fp
d001a31c:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d001a320:	465880db 			; <UNDEFINED> instruction: 0x465880db
d001a324:	fafcf7ff 	blx	0xcff58328
d001a328:	300cf8db 	ldrdcc	pc, [ip], -fp
d001a32c:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d001a330:	f8db80d3 			; <UNDEFINED> instruction: 0xf8db80d3
d001a334:	b0270008 	eorlt	r0, r7, r8
d001a338:	8ff0e8bd 	svchi	0x00f0e8bd
d001a33c:	3000f8d9 	ldrdcc	pc, [r0], -r9
d001a340:	f0233307 			; <UNDEFINED> instruction: 0xf0233307
d001a344:	f1030307 			; <UNDEFINED> instruction: 0xf1030307
d001a348:	f8c90208 			; <UNDEFINED> instruction: 0xf8c90208
d001a34c:	e9d32000 	ldmib	r3, {sp}^
d001a350:	e7ca2300 	strb	r2, [sl, r0, lsl #6]
d001a354:	2b063b01 	blcs	0xd01a8f60
d001a358:	84acf200 	strthi	pc, [ip], #512	; 0x200
d001a35c:	f003e8df 			; <UNDEFINED> instruction: 0xf003e8df
d001a360:	1f04d7e0 	svcne	0x0004d7e0
d001a364:	001f0404 	andseq	r0, pc, r4, lsl #8
d001a368:	3000f8d9 	ldrdcc	pc, [r0], -r9
d001a36c:	1d1a6818 	ldcne	8, cr6, [sl, #-96]	; 0xffffffa0
d001a370:	f8c917c1 			; <UNDEFINED> instruction: 0xf8c917c1
d001a374:	28002000 	stmdacs	r0, {sp}
d001a378:	0300f171 	movweq	pc, #369	; 0x171	; <UNPREDICTABLE>
d001a37c:	4602db1e 			; <UNDEFINED> instruction: 0x4602db1e
d001a380:	0fc8460b 	svceq	0x00c8460b
d001a384:	2100240a 	tstcs	r0, sl, lsl #8
d001a388:	90019704 	andls	r9, r1, r4, lsl #14
d001a38c:	95034658 	strls	r4, [r3, #-1624]	; 0xfffff9a8
d001a390:	91069602 	tstls	r6, r2, lsl #12
d001a394:	94009105 	strls	r9, [r0], #-261	; 0xfffffefb
d001a398:	fb06f7ff 	blx	0xd01d839e
d001a39c:	f8d9e7b7 			; <UNDEFINED> instruction: 0xf8d9e7b7
d001a3a0:	33073000 	movwcc	r3, #28672	; 0x7000
d001a3a4:	0307f023 	movweq	pc, #28707	; 0x7023	; <UNPREDICTABLE>
d001a3a8:	0100e9d3 	ldrdeq	lr, [r0, -r3]
d001a3ac:	0208f103 	andeq	pc, r8, #-1073741824	; 0xc0000000
d001a3b0:	f8c92800 			; <UNDEFINED> instruction: 0xf8c92800
d001a3b4:	f1712000 			; <UNDEFINED> instruction: 0xf1712000
d001a3b8:	dae00300 	ble	0xcf81afc0
d001a3bc:	eb614242 	bl	0xd186accc
d001a3c0:	e7de0341 	ldrb	r0, [lr, r1, asr #6]
d001a3c4:	f1084658 			; <UNDEFINED> instruction: 0xf1084658
d001a3c8:	f7ff0801 			; <UNDEFINED> instruction: 0xf7ff0801
d001a3cc:	e79efabd 			; <UNDEFINED> instruction: 0xe79efabd
d001a3d0:	f1084658 			; <UNDEFINED> instruction: 0xf1084658
d001a3d4:	f7ff0802 			; <UNDEFINED> instruction: 0xf7ff0802
d001a3d8:	e798fab7 			; <UNDEFINED> instruction: 0xe798fab7
d001a3dc:	0230f1a4 	eorseq	pc, r0, #164, 2	; 0x29
d001a3e0:	2b09b2d3 	blcs	0xd0286f34
d001a3e4:	80e8f200 	rschi	pc, r8, r0, lsl #4
d001a3e8:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d001a3ec:	f5c22500 			; <UNDEFINED> instruction: 0xf5c22500
d001a3f0:	46415300 	strbmi	r5, [r1], -r0, lsl #6
d001a3f4:	0085eb05 	addeq	lr, r5, r5, lsl #22
d001a3f8:	4303fbaa 	movwmi	pc, #15274	; 0x3baa	; <UNPREDICTABLE>
d001a3fc:	4b01f818 	blmi	0xd0098464
d001a400:	0fd3ebb5 	svceq	0x00d3ebb5
d001a404:	0540eb02 	strbeq	lr, [r0, #-2818]	; 0xfffff4fe
d001a408:	0230f1a4 	eorseq	pc, r0, #164, 2	; 0x29
d001a40c:	f44fbf88 			; <UNDEFINED> instruction: 0xf44fbf88
d001a410:	b2d35500 	sbcslt	r5, r3, #0, 10
d001a414:	d9ea2b09 	stmible	sl!, {r0, r3, r8, r9, fp, sp}^
d001a418:	f47f2c2e 			; <UNDEFINED> instruction: 0xf47f2c2e
d001a41c:	784caf05 	stmdavc	ip, {r0, r2, r8, r9, sl, fp, sp, pc}^
d001a420:	d1322c2a 	teqle	r2, sl, lsr #24
d001a424:	3000f8d9 	ldrdcc	pc, [r0], -r9
d001a428:	681f1c88 	ldmdavs	pc, {r3, r7, sl, fp, ip}	; <UNPREDICTABLE>
d001a42c:	2f001d1a 	svccs	0x00001d1a
d001a430:	2000f8c9 	andcs	pc, r0, r9, asr #17
d001a434:	f2c0788c 	vmlal.s8	<illegal reg q11.5>, d16, d12
d001a438:	f5b78091 			; <UNDEFINED> instruction: 0xf5b78091
d001a43c:	46015f00 	strmi	r5, [r1], -r0, lsl #30
d001a440:	f44fbf28 			; <UNDEFINED> instruction: 0xf44fbf28
d001a444:	2c685700 	stclcs	7, cr5, [r8], #-0
d001a448:	aef3f47f 	mrcge	4, 7, APSR_nzcv, cr3, cr15, {3}
d001a44c:	2c68784c 	stclcs	8, cr7, [r8], #-304	; 0xfffffed0
d001a450:	3101d03e 	tstcc	r1, lr, lsr r0
d001a454:	e6f92302 	ldrbt	r2, [r9], r2, lsl #6
d001a458:	4f00f1b5 	svcmi	0x0000f1b5
d001a45c:	0601f046 	streq	pc, [r1], -r6, asr #32
d001a460:	426dd077 	rsbmi	sp, sp, #119	; 0x77
d001a464:	4001f898 	mulmi	r1, r8, r8
d001a468:	5f00f5b5 	svcpl	0x0000f5b5
d001a46c:	f44fbf28 			; <UNDEFINED> instruction: 0xf44fbf28
d001a470:	e6d65500 	ldrb	r5, [r6], r0, lsl #10
d001a474:	2c6c784c 	stclcs	8, cr7, [ip], #-304	; 0xfffffed0
d001a478:	8096f000 	addshi	pc, r6, r0
d001a47c:	23033101 	movwcs	r3, #12545	; 0x3101
d001a480:	784ce6e4 	stmdavc	ip, {r2, r5, r6, r7, r9, sl, sp, lr, pc}^
d001a484:	31012305 	tstcc	r1, r5, lsl #6
d001a488:	f1a4e6e0 			; <UNDEFINED> instruction: 0xf1a4e6e0
d001a48c:	1c480230 	sfmne	f0, 2, [r8], {48}	; 0x30
d001a490:	2b09b2d3 	blcs	0xd0286fe4
d001a494:	80daf200 	sbcshi	pc, sl, r0, lsl #4
d001a498:	27001c88 	strcs	r1, [r0, -r8, lsl #25]
d001a49c:	5300f5c2 	movwpl	pc, #1474	; 0x5c2	; <UNPREDICTABLE>
d001a4a0:	0487eb07 	streq	lr, [r7], #2823	; 0xb07
d001a4a4:	fbaa4601 	blx	0xceaabcb2
d001a4a8:	ebb7c303 	bl	0xcee0b0bc
d001a4ac:	eb020fd3 	bl	0xd009e400
d001a4b0:	f8100744 			; <UNDEFINED> instruction: 0xf8100744
d001a4b4:	bf884b01 	svclt	0x00884b01
d001a4b8:	5700f44f 	strpl	pc, [r0, -pc, asr #8]
d001a4bc:	0230f1a4 	eorseq	pc, r0, #164, 2	; 0x29
d001a4c0:	2b09b2d3 	blcs	0xd0287014
d001a4c4:	e6b1d9ea 	ldrt	sp, [r1], sl, ror #19
d001a4c8:	e6e92108 	strbt	r2, [r9], r8, lsl #2
d001a4cc:	e6e72110 	usat	r2, #7, r0, lsl #2
d001a4d0:	2301788c 	movwcs	r7, #6284	; 0x188c
d001a4d4:	e6b93102 	ldrt	r3, [r9], r2, lsl #2
d001a4d8:	3000f8db 	ldrdcc	pc, [r0], -fp
d001a4dc:	f43f2b00 			; <UNDEFINED> instruction: 0xf43f2b00
d001a4e0:	f8dbaf28 			; <UNDEFINED> instruction: 0xf8dbaf28
d001a4e4:	2a002004 	bcs	0xd00224fc
d001a4e8:	af23f43f 	svcge	0x0023f43f
d001a4ec:	1008f8db 	ldrdne	pc, [r8], -fp
d001a4f0:	bf98428a 	svclt	0x0098428a
d001a4f4:	31fff102 	mvnscc	pc, r2, lsl #2
d001a4f8:	545a2200 	ldrbpl	r2, [sl], #-512	; 0xfffffe00
d001a4fc:	0008f8db 	ldrdeq	pc, [r8], -fp
d001a500:	e8bdb027 	pop	{r0, r1, r2, r5, ip, sp, pc}
d001a504:	784c8ff0 	stmdavc	ip, {r4, r5, r6, r7, r8, r9, sl, fp, pc}^
d001a508:	31012306 	tstcc	r1, r6, lsl #6
d001a50c:	f8d9e69e 			; <UNDEFINED> instruction: 0xf8d9e69e
d001a510:	f9b33000 			; <UNDEFINED> instruction: 0xf9b33000
d001a514:	1d1a0000 	ldcne	0, cr0, [sl, #-0]
d001a518:	f8c917c1 			; <UNDEFINED> instruction: 0xf8c917c1
d001a51c:	e72a2000 	str	r2, [sl, -r0]!
d001a520:	3000f8d9 	ldrdcc	pc, [r0], -r9
d001a524:	0000f993 	muleq	r0, r3, r9
d001a528:	17c11d1a 	bfine	r1, sl, (invalid: 26:1)
d001a52c:	2000f8c9 	andcs	pc, r0, r9, asr #17
d001a530:	f8d9e721 			; <UNDEFINED> instruction: 0xf8d9e721
d001a534:	1d183000 	ldcne	0, cr3, [r8, #-0]
d001a538:	2300881a 	movwcs	r8, #2074	; 0x81a
d001a53c:	0000f8c9 	andeq	pc, r0, r9, asr #17
d001a540:	f8d9e6d3 			; <UNDEFINED> instruction: 0xf8d9e6d3
d001a544:	1d183000 	ldcne	0, cr3, [r8, #-0]
d001a548:	2300781a 	movwcs	r7, #2074	; 0x81a
d001a54c:	0000f8c9 	andeq	pc, r0, r9, asr #17
d001a550:	f898e6cb 			; <UNDEFINED> instruction: 0xf898e6cb
d001a554:	f44f4001 	vst4.8	{d20-d23}, [pc], r1
d001a558:	e6625500 	strbt	r5, [r2], -r0, lsl #10
d001a55c:	37fff04f 	ldrbcc	pc, [pc, pc, asr #32]!	; <UNPREDICTABLE>
d001a560:	e6634601 	strbt	r4, [r3], -r1, lsl #12
d001a564:	d0592c70 	subsle	r2, r9, r0, ror ip
d001a568:	d0722c73 	rsbsle	r2, r2, r3, ror ip
d001a56c:	d0262c63 	eorle	r2, r6, r3, ror #24
d001a570:	0245f1a1 	subeq	pc, r5, #1073741864	; 0x40000028
d001a574:	d93f2a02 	ldmdble	pc!, {r1, r9, fp, sp}	; <UNPREDICTABLE>
d001a578:	f0002941 			; <UNDEFINED> instruction: 0xf0002941
d001a57c:	2c6e80af 	stclcs	0, cr8, [lr], #-700	; 0xfffffd44
d001a580:	8216f000 	andshi	pc, r6, #0
d001a584:	21254658 			; <UNDEFINED> instruction: 0x21254658
d001a588:	f9def7ff 			; <UNDEFINED> instruction: 0xf9def7ff
d001a58c:	46584621 	ldrbmi	r4, [r8], -r1, lsr #12
d001a590:	f9daf7ff 			; <UNDEFINED> instruction: 0xf9daf7ff
d001a594:	bf00e6bb 	svclt	0x0000e6bb
d001a598:	00082001 	andeq	r2, r8, r1
d001a59c:	ffffffce 			; <UNDEFINED> instruction: 0xffffffce
d001a5a0:	cccccccd 	stclgt	12, cr12, [ip], {205}	; 0xcd
d001a5a4:	ffffffb4 			; <UNDEFINED> instruction: 0xffffffb4
d001a5a8:	2304788c 	movwcs	r7, #18572	; 0x488c
d001a5ac:	e64d3102 	strb	r3, [sp], -r2, lsl #2
d001a5b0:	2307784c 	movwcs	r7, #30796	; 0x784c
d001a5b4:	e6493101 	strb	r3, [r9], -r1, lsl #2
d001a5b8:	25004641 	strcs	r4, [r0, #-1601]	; 0xfffff9bf
d001a5bc:	2d01e631 	stccs	6, cr14, [r1, #-196]	; 0xffffff3c
d001a5c0:	2501bf38 	strcs	fp, [r1, #-3896]	; 0xfffff0c8
d001a5c4:	f10507f6 			; <UNDEFINED> instruction: 0xf10507f6
d001a5c8:	f14037ff 			; <UNDEFINED> instruction: 0xf14037ff
d001a5cc:	f8d9818b 			; <UNDEFINED> instruction: 0xf8d9818b
d001a5d0:	46583000 	ldrbmi	r3, [r8], -r0
d001a5d4:	1d1a3d02 	ldcne	13, cr3, [sl, #-8]
d001a5d8:	f8c97819 			; <UNDEFINED> instruction: 0xf8c97819
d001a5dc:	f7ff2000 			; <UNDEFINED> instruction: 0xf7ff2000
d001a5e0:	2f00f9b3 	svccs	0x0000f9b3
d001a5e4:	ae93f43f 	mrcge	4, 4, APSR_nzcv, cr3, cr15, {1}
d001a5e8:	46583d01 	ldrbmi	r3, [r8], -r1, lsl #26
d001a5ec:	f7ff2120 			; <UNDEFINED> instruction: 0xf7ff2120
d001a5f0:	1c68f9ab 			; <UNDEFINED> instruction: 0x1c68f9ab
d001a5f4:	e68ad1f8 			; <UNDEFINED> instruction: 0xe68ad1f8
d001a5f8:	0000f8d9 	ldrdeq	pc, [r0], -r9
d001a5fc:	462b4621 	strtmi	r4, [fp], -r1, lsr #12
d001a600:	1dc44632 	stclne	6, cr4, [r4, #200]	; 0xc8
d001a604:	f0244658 			; <UNDEFINED> instruction: 0xf0244658
d001a608:	ed940407 	cfldrs	mvf0, [r4, #28]
d001a60c:	34080b00 	strcc	r0, [r8], #-2816	; 0xfffff500
d001a610:	f8c99700 			; <UNDEFINED> instruction: 0xf8c99700
d001a614:	f7ff4000 			; <UNDEFINED> instruction: 0xf7ff4000
d001a618:	e678fb75 			; <UNDEFINED> instruction: 0xe678fb75
d001a61c:	3000f8d9 	ldrdcc	pc, [r0], -r9
d001a620:	060cf026 	streq	pc, [ip], -r6, lsr #32
d001a624:	21102401 	tstcs	r0, r1, lsl #8
d001a628:	46581d1a 			; <UNDEFINED> instruction: 0x46581d1a
d001a62c:	2000f8c9 	andcs	pc, r0, r9, asr #17
d001a630:	4663681a 			; <UNDEFINED> instruction: 0x4663681a
d001a634:	f8cd9602 			; <UNDEFINED> instruction: 0xf8cd9602
d001a638:	9704c014 	smladls	r4, r4, r0, ip
d001a63c:	f8cd9503 			; <UNDEFINED> instruction: 0xf8cd9503
d001a640:	9406c004 	strls	ip, [r6], #-4
d001a644:	f7ff9100 			; <UNDEFINED> instruction: 0xf7ff9100
d001a648:	e660f9af 	strbt	pc, [r0], -pc, lsr #19	; <UNPREDICTABLE>
d001a64c:	27004601 	strcs	r4, [r0, -r1, lsl #12]
d001a650:	f8d9e5ec 			; <UNDEFINED> instruction: 0xf8d9e5ec
d001a654:	1d1a3000 	ldcne	0, cr3, [sl, #-0]
d001a658:	2000f8c9 	andcs	pc, r0, r9, asr #17
d001a65c:	9314681b 	tstls	r4, #1769472	; 0x1b0000
d001a660:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d001a664:	781b813b 	ldmdavc	fp, {r0, r1, r3, r4, r5, r8, pc}
d001a668:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d001a66c:	0ff88197 	svceq	0x00f88197
d001a670:	f0002f00 			; <UNDEFINED> instruction: 0xf0002f00
d001a674:	9a148193 	bls	0xd053acc8
d001a678:	f8122400 			; <UNDEFINED> instruction: 0xf8122400
d001a67c:	34013f01 	strcc	r3, [r1], #-3841	; 0xfffff0ff
d001a680:	42bcb11b 	adcsmi	fp, ip, #-1073741818	; 0xc0000006
d001a684:	2800d3f9 	stmdacs	r0, {r0, r3, r4, r5, r6, r7, r8, r9, ip, lr, pc}
d001a688:	42a5d1f7 	adcmi	sp, r5, #-1073741763	; 0xc000003d
d001a68c:	813df200 	teqhi	sp, r0, lsl #4	; <UNPREDICTABLE>
d001a690:	0301f016 	movweq	pc, #4118	; 0x1016	; <UNPREDICTABLE>
d001a694:	f0009312 			; <UNDEFINED> instruction: 0xf0009312
d001a698:	25008189 	strcs	r8, [r0, #-393]	; 0xfffffe77
d001a69c:	95149b14 	ldrls	r9, [r4, #-2836]	; 0xfffff4ec
d001a6a0:	1e5e4625 	cdpne	6, 5, cr4, cr14, cr5, {1}
d001a6a4:	4637461c 			; <UNDEFINED> instruction: 0x4637461c
d001a6a8:	f8164658 			; <UNDEFINED> instruction: 0xf8164658
d001a6ac:	f7ff1f01 			; <UNDEFINED> instruction: 0xf7ff1f01
d001a6b0:	1cbbf94b 			; <UNDEFINED> instruction: 0x1cbbf94b
d001a6b4:	429d1b1b 	addsmi	r1, sp, #27648	; 0x6c00
d001a6b8:	9b12d8f5 	blls	0xd04d0a94
d001a6bc:	2b009d14 	blcs	0xd0041b14
d001a6c0:	ae25f43f 	mcrge	4, 1, pc, cr5, cr15, {1}	; <UNPREDICTABLE>
d001a6c4:	2d001e6c 	stccs	14, cr1, [r0, #-432]	; 0xfffffe50
d001a6c8:	ae21f43f 	mcrge	4, 1, pc, cr1, cr15, {1}	; <UNPREDICTABLE>
d001a6cc:	21203c01 			; <UNDEFINED> instruction: 0x21203c01
d001a6d0:	f7ff4658 			; <UNDEFINED> instruction: 0xf7ff4658
d001a6d4:	1c67f939 			; <UNDEFINED> instruction: 0x1c67f939
d001a6d8:	e618d1f8 			; <UNDEFINED> instruction: 0xe618d1f8
d001a6dc:	3000f8d9 	ldrdcc	pc, [r0], -r9
d001a6e0:	f0233307 			; <UNDEFINED> instruction: 0xf0233307
d001a6e4:	ed930307 	ldc	3, cr0, [r3, #28]
d001a6e8:	33087b00 	movwcc	r7, #35584	; 0x8b00
d001a6ec:	0b17ec51 	bleq	0xd0615838
d001a6f0:	3000f8c9 	andcc	pc, r0, r9, asr #17
d001a6f4:	ee17460b 	cfmsub32	mvax0, mvfx4, mvfx7, mvfx11
d001a6f8:	2b002a10 	blcs	0xd0024f40
d001a6fc:	7b12ed8d 	blvc	0xd04d5d38
d001a700:	8176f2c0 	cmnhi	r6, r0, asr #5	; <UNPREDICTABLE>
d001a704:	f1000771 			; <UNDEFINED> instruction: 0xf1000771
d001a708:	00b18176 	adcseq	r8, r1, r6, ror r1
d001a70c:	0120f001 	msreq	CPSR_, r1
d001a710:	f3c39114 	vorr.i32	d25, #180	; 0x000000b4
d001a714:	920c510a 	andls	r5, ip, #-2147483646	; 0x80000002
d001a718:	72fff240 	rscsvc	pc, pc, #64, 4
d001a71c:	0313f3c3 	tsteq	r3, #201326595	; 0xc000003	; <UNPREDICTABLE>
d001a720:	42919116 	addsmi	r9, r1, #-2147483643	; 0x80000005
d001a724:	f000930d 			; <UNDEFINED> instruction: 0xf000930d
d001a728:	9b16817c 	blls	0xd05bad20
d001a72c:	bf142b00 	svclt	0x00142b00
d001a730:	22002201 	andcs	r2, r0, #268435456	; 0x10000000
d001a734:	f0009217 			; <UNDEFINED> instruction: 0xf0009217
d001a738:	f2a38161 	vmla.f32	d8, d3, d1[1]
d001a73c:	2b0033ff 	blcs	0xd0027740
d001a740:	bfb8931a 	svclt	0x00b8931a
d001a744:	9312425b 	tstls	r2, #-1342177275	; 0xb0000005
d001a748:	f0001c78 			; <UNDEFINED> instruction: 0xf0001c78
d001a74c:	f5b7818a 			; <UNDEFINED> instruction: 0xf5b7818a
d001a750:	f3405f00 	vpmax.f32	d21, d0, d0
d001a754:	f44f817d 	vst4.16	{d24,d26,d28,d30}, [pc :256]!
d001a758:	e9dd5700 	ldmib	sp, {r8, r9, sl, ip, lr}^
d001a75c:	9715230c 	ldrls	r2, [r5, -ip, lsl #6]
d001a760:	230ae9cd 	movwcs	lr, #43469	; 0xa9cd
d001a764:	2100ab22 	tstcs	r0, r2, lsr #22
d001a768:	ee079a12 			; <UNDEFINED> instruction: 0xee079a12
d001a76c:	4618ba90 			; <UNDEFINED> instruction: 0x4618ba90
d001a770:	fbaa9321 	blx	0xceabf3fe
d001a774:	4694c302 	ldrmi	ip, [r4], r2, lsl #6
d001a778:	3101468e 	smlabbcc	r1, lr, r6, r4
d001a77c:	0bd3ea4f 	bleq	0xcf5150c0
d001a780:	0f09f1bc 	svceq	0x0009f1bc
d001a784:	038beb0b 	orreq	lr, fp, #11264	; 0x2c00
d001a788:	0343eba2 	movteq	lr, #15266	; 0x3ba2
d001a78c:	f103465a 			; <UNDEFINED> instruction: 0xf103465a
d001a790:	b2db0330 	sbcslt	r0, fp, #48, 6	; 0xc0000000
d001a794:	3b01f800 	blcc	0xd009879c
d001a798:	ee17d8eb 	cdp	8, 1, cr13, cr7, cr11, {7}
d001a79c:	931fba90 	tstls	pc, #144, 20	; 0x90000
d001a7a0:	e080f8cd 	add	pc, r0, sp, asr #17
d001a7a4:	f0002f00 			; <UNDEFINED> instruction: 0xf0002f00
d001a7a8:	f00681bd 			; <UNDEFINED> instruction: 0xf00681bd
d001a7ac:	22040310 	andcs	r0, r4, #16, 6	; 0x40000000
d001a7b0:	9b14931b 	blls	0xd053f424
d001a7b4:	3b009815 	blcc	0xd0040810
d001a7b8:	2301bf18 	movwcs	fp, #7960	; 0x1f18
d001a7bc:	44033302 	strmi	r3, [r3], #-770	; 0xfffffcfe
d001a7c0:	4413440b 	ldrmi	r4, [r3], #-1035	; 0xfffffbf5
d001a7c4:	f240429d 	vqsub.s8	d20, d16, d13
d001a7c8:	f00681b9 			; <UNDEFINED> instruction: 0xf00681b9
d001a7cc:	f0060101 			; <UNDEFINED> instruction: 0xf0060101
d001a7d0:	1aea0003 	bne	0xcfa9a7e4
d001a7d4:	0301f081 	movweq	pc, #4225	; 0x1081	; <UNPREDICTABLE>
d001a7d8:	901e9116 	andsls	r9, lr, r6, lsl r1
d001a7dc:	bf0c2802 	svclt	0x000c2802
d001a7e0:	f0032600 			; <UNDEFINED> instruction: 0xf0032600
d001a7e4:	92120601 	andsls	r0, r2, #1048576	; 0x100000
d001a7e8:	f0002e00 			; <UNDEFINED> instruction: 0xf0002e00
d001a7ec:	1e5581a5 	lognedp	f0, f5
d001a7f0:	f0002a00 			; <UNDEFINED> instruction: 0xf0002a00
d001a7f4:	3d0181b0 	stfccd	f0, [r1, #-704]	; 0xfffffd40
d001a7f8:	46582120 	ldrbmi	r2, [r8], -r0, lsr #2
d001a7fc:	f8a4f7ff 			; <UNDEFINED> instruction: 0xf8a4f7ff
d001a800:	d1f81c69 	mvnsle	r1, r9, ror #24
d001a804:	93162300 	tstls	r6, #0, 6
d001a808:	2b009b14 	blcs	0xd0041460
d001a80c:	8185f040 	orrhi	pc, r5, r0, asr #32
d001a810:	46582130 			; <UNDEFINED> instruction: 0x46582130
d001a814:	f898f7ff 			; <UNDEFINED> instruction: 0xf898f7ff
d001a818:	46582c41 	ldrbmi	r2, [r8], -r1, asr #24
d001a81c:	2158bf0c 	cmpcs	r8, ip, lsl #30
d001a820:	f7ff2178 			; <UNDEFINED> instruction: 0xf7ff2178
d001a824:	9b1ef891 	blls	0xd07d8a70
d001a828:	d1022b02 	tstle	r2, r2, lsl #22
d001a82c:	f0402e00 			; <UNDEFINED> instruction: 0xf0402e00
d001a830:	99178195 	ldmdbls	r7, {r0, r2, r4, r7, r8, pc}
d001a834:	31304658 	teqcc	r0, r8, asr r6
d001a838:	f7ffb2c9 			; <UNDEFINED> instruction: 0xf7ffb2c9
d001a83c:	9b15f885 	blls	0xd0598a58
d001a840:	43139a1b 	tstmi	r3, #110592	; 0x1b000
d001a844:	212ed003 			; <UNDEFINED> instruction: 0x212ed003
d001a848:	f7ff4658 			; <UNDEFINED> instruction: 0xf7ff4658
d001a84c:	2c41f87d 	mcrrcs	8, 7, pc, r1, cr13	; <UNPREDICTABLE>
d001a850:	816ff000 	msrhi	SPSR_fsxc, r0
d001a854:	f0002f00 			; <UNDEFINED> instruction: 0xf0002f00
d001a858:	9e08821f 	mcrls	2, 0, r8, cr8, cr15, {0}
d001a85c:	250000bb 	strcs	r0, [r0, #-187]	; 0xffffff45
d001a860:	3b049415 	blcc	0xd013f8bc
d001a864:	e0069314 	and	r9, r6, r4, lsl r3
d001a868:	78193501 	ldmdavc	r9, {r0, r8, sl, ip, sp}
d001a86c:	f7ff4658 			; <UNDEFINED> instruction: 0xf7ff4658
d001a870:	42aff86b 	adcmi	pc, pc, #7012352	; 0x6b0000
d001a874:	2d0cd064 	stccs	0, cr13, [ip, #-400]	; 0xfffffe70
d001a878:	dcf54633 	ldclle	6, cr4, [r5], #204	; 0xcc
d001a87c:	7185ebc5 	orrvc	lr, r5, r5, asr #23
d001a880:	9c0a9b14 			; <UNDEFINED> instruction: 0x9c0a9b14
d001a884:	460a2f0c 	strmi	r2, [sl], -ip, lsl #30
d001a888:	0181ea4f 	orreq	lr, r1, pc, asr #20
d001a88c:	0282eb03 	addeq	lr, r2, #3072	; 0xc00
d001a890:	0330f101 	teqeq	r0, #1073741824	; 0x40000000	; <UNPREDICTABLE>
d001a894:	0110f101 	tsteq	r0, r1, lsl #2	; <UNPREDICTABLE>
d001a898:	0020f1c2 	eoreq	pc, r0, r2, asr #3
d001a89c:	0c20f1a2 	stfeqd	f7, [r0], #-648	; 0xfffffd78
d001a8a0:	f202fa24 	vpmax.s8	d15, d2, d20
d001a8a4:	f1c39c0b 			; <UNDEFINED> instruction: 0xf1c39c0b
d001a8a8:	fa040e20 	blx	0xd011e130
d001a8ac:	9c0cf000 	stcls	0, cr15, [ip], {-0}
d001a8b0:	f303fa24 	vpmax.u8	d15, d3, d20
d001a8b4:	ea429c0d 	b	0xd10c18f0
d001a8b8:	980d0200 	stmdals	sp, {r9}
d001a8bc:	fe0efa04 	vseleq.f32	s30, s28, s8
d001a8c0:	fa209c0b 	blx	0xd08418f4
d001a8c4:	fa24f101 	blx	0xd0956cd0
d001a8c8:	ea43fc0c 	b	0xd1119900
d001a8cc:	dc32030e 	ldcle	3, cr0, [r2], #-56	; 0xffffffc8
d001a8d0:	020cea42 	andeq	lr, ip, #270336	; 0x42000
d001a8d4:	030ff002 	movweq	pc, #61442	; 0xf002	; <UNPREDICTABLE>
d001a8d8:	e7c54433 			; <UNDEFINED> instruction: 0xe7c54433
d001a8dc:	447b4bfb 	ldrbtmi	r4, [fp], #-3067	; 0xfffff405
d001a8e0:	e6c49314 			; <UNDEFINED> instruction: 0xe6c49314
d001a8e4:	b1373d02 	teqlt	r7, r2, lsl #26
d001a8e8:	21203d01 			; <UNDEFINED> instruction: 0x21203d01
d001a8ec:	f7ff4658 			; <UNDEFINED> instruction: 0xf7ff4658
d001a8f0:	1c6cf82b 	stclne	8, cr15, [ip], #-172	; 0xffffff54
d001a8f4:	f8d9d1f8 			; <UNDEFINED> instruction: 0xf8d9d1f8
d001a8f8:	46583000 	ldrbmi	r3, [r8], -r0
d001a8fc:	78191d1a 	ldmdavc	r9, {r1, r3, r4, r8, sl, fp, ip}
d001a900:	2000f8c9 	andcs	pc, r0, r9, asr #17
d001a904:	f820f7ff 			; <UNDEFINED> instruction: 0xf820f7ff
d001a908:	f016e501 			; <UNDEFINED> instruction: 0xf016e501
d001a90c:	eba50301 	bl	0xce95b518
d001a910:	93120504 	tstls	r2, #4, 10	; 0x1000000
d001a914:	aec2f47f 	mcrge	4, 6, pc, cr2, cr15, {3}	; <UNPREDICTABLE>
d001a918:	b1351e6e 	teqlt	r5, lr, ror #28
d001a91c:	21203e01 			; <UNDEFINED> instruction: 0x21203e01
d001a920:	f7ff4658 			; <UNDEFINED> instruction: 0xf7ff4658
d001a924:	1c73f811 	ldclne	8, cr15, [r3], #-68	; 0xffffffbc
d001a928:	2c00d1f8 	stfcsd	f5, [r0], {248}	; 0xf8
d001a92c:	aceff43f 	cfstrdge	mvd15, [pc], #252	; 0xd001aa30
d001a930:	93122300 	tstls	r2, #0, 6
d001a934:	430be6b2 	movwmi	lr, #46770	; 0xb6b2
d001a938:	030ff003 	movweq	pc, #61443	; 0xf003	; <UNPREDICTABLE>
d001a93c:	e7934433 			; <UNDEFINED> instruction: 0xe7934433
d001a940:	2c419c15 	mcrrcs	12, 1, r9, r1, cr5
d001a944:	2150bf0c 	cmpcs	r0, ip, lsl #30
d001a948:	46582170 			; <UNDEFINED> instruction: 0x46582170
d001a94c:	fffcf7fe 			; <UNDEFINED> instruction: 0xfffcf7fe
d001a950:	9d219b1a 	vstmdbls	r1!, {d9-d21}
d001a954:	2b004658 	blcs	0xd002c2bc
d001a958:	461c9b20 	ldrmi	r9, [ip], -r0, lsr #22
d001a95c:	212dbfb4 			; <UNDEFINED> instruction: 0x212dbfb4
d001a960:	f7fe212b 			; <UNDEFINED> instruction: 0xf7fe212b
d001a964:	442cfff1 	strtmi	pc, [ip], #-4081	; 0xfffff00f
d001a968:	e001991f 	and	r9, r1, pc, lsl r9
d001a96c:	1d01f814 	stcne	8, cr15, [r1, #-80]	; 0xffffffb0
d001a970:	f7fe4658 			; <UNDEFINED> instruction: 0xf7fe4658
d001a974:	42a5ffe9 	adcmi	pc, r5, #932	; 0x3a4
d001a978:	9b16d1f8 	blls	0xd05cf160
d001a97c:	f43f2b00 			; <UNDEFINED> instruction: 0xf43f2b00
d001a980:	9b12acc6 	blls	0xd04c5ca0
d001a984:	2b001e5c 	blcs	0xd00222fc
d001a988:	acc1f43f 	cfstrdge	mvd15, [r1], {63}	; 0x3f
d001a98c:	21203c01 			; <UNDEFINED> instruction: 0x21203c01
d001a990:	f7fe4658 			; <UNDEFINED> instruction: 0xf7fe4658
d001a994:	1c63ffd9 	stclne	15, cr15, [r3], #-868	; 0xfffffc9c
d001a998:	e4b8d1f8 	ldrt	sp, [r8], #504	; 0x1f8
d001a99c:	f43f2d00 			; <UNDEFINED> instruction: 0xf43f2d00
d001a9a0:	07f2acb6 			; <UNDEFINED> instruction: 0x07f2acb6
d001a9a4:	817af140 	cmnhi	sl, r0, asr #2	; <UNPREDICTABLE>
d001a9a8:	e68f1e6c 	str	r1, [pc], ip, ror #28
d001a9ac:	e7bc9d12 			; <UNDEFINED> instruction: 0xe7bc9d12
d001a9b0:	f8db3b01 			; <UNDEFINED> instruction: 0xf8db3b01
d001a9b4:	2b062008 	blcs	0xd01a29dc
d001a9b8:	e8dfd812 	ldm	pc, {r1, r4, fp, ip, lr, pc}^	; <UNPREDICTABLE>
d001a9bc:	014bf013 	cmpeq	fp, r3, lsl r0	; <UNPREDICTABLE>
d001a9c0:	00110142 	andseq	r0, r1, r2, asr #2
d001a9c4:	00110007 	andseq	r0, r1, r7
d001a9c8:	00070011 	andeq	r0, r7, r1, lsl r0
d001a9cc:	3000f8d9 	ldrdcc	pc, [r0], -r9
d001a9d0:	1d182100 	ldfnes	f2, [r8, #-0]
d001a9d4:	0000f8c9 	andeq	pc, r0, r9, asr #17
d001a9d8:	e9c3681b 	stmib	r3, {r0, r1, r3, r4, fp, sp, lr}^
d001a9dc:	e4962100 	ldr	r2, [r6], #256	; 0x100
d001a9e0:	3000f8d9 	ldrdcc	pc, [r0], -r9
d001a9e4:	f8c91d19 			; <UNDEFINED> instruction: 0xf8c91d19
d001a9e8:	681b1000 	ldmdavs	fp, {ip}
d001a9ec:	e48e601a 	str	r6, [lr], #26
d001a9f0:	9114212d 	tstls	r4, sp, lsr #2
d001a9f4:	212be68d 	smlawbcs	fp, sp, r6, lr
d001a9f8:	e68a9114 	pkhbt	r9, sl, r4, lsl #2
d001a9fc:	010ce9dd 	ldrdeq	lr, [ip, -sp]
d001aa00:	32fef240 	rscscc	pc, lr, #64, 4
d001aa04:	0301ea50 	movweq	lr, #6736	; 0x1a50
d001aa08:	48af9916 	stmiami	pc!, {r1, r2, r4, r8, fp, ip, pc}	; <UNPREDICTABLE>
d001aa0c:	460bbf0c 	strmi	fp, [fp], -ip, lsl #30
d001aa10:	93124613 	tstls	r2, #19922944	; 0x1300000
d001aa14:	230ce9dd 	movwcs	lr, #51677	; 0xc9dd
d001aa18:	460bbf0c 	strmi	fp, [fp], -ip, lsl #30
d001aa1c:	931a4603 	tstls	sl, #3145728	; 0x300000
d001aa20:	2c41e692 	mcrrcs	6, 9, lr, r1, cr2
d001aa24:	4632462b 	ldrtmi	r4, [r2], -fp, lsr #12
d001aa28:	bf0c4658 	svclt	0x000c4658
d001aa2c:	21662146 	cmncs	r6, r6, asr #2
d001aa30:	ed9d9700 	ldc	7, cr9, [sp]
d001aa34:	f7ff0b12 			; <UNDEFINED> instruction: 0xf7ff0b12
d001aa38:	e468f965 	strbt	pc, [r8], #-2405	; 0xfffff69b	; <UNPREDICTABLE>
d001aa3c:	463b4631 			; <UNDEFINED> instruction: 0x463b4631
d001aa40:	f8cd462c 			; <UNDEFINED> instruction: 0xf8cd462c
d001aa44:	9e158048 	cdpls	0, 1, cr8, cr5, cr8, {2}
d001aa48:	461746c8 	ldrmi	r4, [r7], -r8, asr #13
d001aa4c:	460d4699 			; <UNDEFINED> instruction: 0x460d4699
d001aa50:	f3402f0c 	vpmax.f32	d18, d0, d12
d001aa54:	97158090 			; <UNDEFINED> instruction: 0x97158090
d001aa58:	230ce9dd 	movwcs	lr, #51677	; 0xc9dd
d001aa5c:	230ae9cd 	movwcs	lr, #43469	; 0xa9cd
d001aa60:	270de680 	strcs	lr, [sp, -r0, lsl #13]
d001aa64:	46494628 	strbmi	r4, [r9], -r8, lsr #12
d001aa68:	46c12300 	strbmi	r2, [r1], r0, lsl #6
d001aa6c:	9615463a 			; <UNDEFINED> instruction: 0x9615463a
d001aa70:	4625469e 			; <UNDEFINED> instruction: 0x4625469e
d001aa74:	8048f8dd 	ldrdhi	pc, [r8], #-141	; 0xffffff73
d001aa78:	4606460f 	strmi	r4, [r6], -pc, lsl #12
d001aa7c:	0c20f1c3 	stfeqd	f7, [r0], #-780	; 0xfffffcf4
d001aa80:	990c980d 	stmdbls	ip, {r0, r2, r3, fp, ip, pc}
d001aa84:	0420f1a3 	strteq	pc, [r0], #-419	; 0xfffffe5d
d001aa88:	fc0cfa00 	stc2	10, cr15, [ip], {-0}	; <UNPREDICTABLE>
d001aa8c:	40e040d9 	ldrdmi	r4, [r0], #9	; <UNPREDICTABLE>
d001aa90:	ea413304 	b	0xd10676a8
d001aa94:	4301010c 	movwmi	r0, #4364	; 0x110c
d001aa98:	010ff001 	tsteq	pc, r1	; <UNPREDICTABLE>
d001aa9c:	1e0ae9cd 	vmlsne.f16	s28, s21, s26	; <UNPREDICTABLE>
d001aaa0:	010ae9dd 	ldrdeq	lr, [sl, -sp]
d001aaa4:	d1c94301 	bicle	r4, r9, r1, lsl #6
d001aaa8:	d1e73a01 	mvnle	r3, r1, lsl #20
d001aaac:	f8cd463b 			; <UNDEFINED> instruction: 0xf8cd463b
d001aab0:	46178048 	ldrmi	r8, [r7], -r8, asr #32
d001aab4:	469946c8 	ldrmi	r4, [r9], r8, asr #13
d001aab8:	462c4631 			; <UNDEFINED> instruction: 0x462c4631
d001aabc:	460d9e15 			; <UNDEFINED> instruction: 0x460d9e15
d001aac0:	e9dd9715 	ldmib	sp, {r0, r2, r4, r8, r9, sl, ip, pc}^
d001aac4:	e9cd230c 	stmib	sp, {r2, r3, r8, r9, sp}^
d001aac8:	22012318 	andcs	r2, r1, #24, 6	; 0x60000000
d001aacc:	e9cd2300 	stmib	sp, {r8, r9, sp}^
d001aad0:	22002310 	andcs	r2, r0, #16, 6	; 0x40000000
d001aad4:	2300f44f 	movwcs	pc, #1103	; 0x44f	; <UNPREDICTABLE>
d001aad8:	230ee9cd 	movwcs	lr, #59853	; 0xe9cd
d001aadc:	230ee9dd 	movwcs	lr, #59869	; 0xe9dd
d001aae0:	0118e9dd 			; <UNDEFINED> instruction: 0x0118e9dd
d001aae4:	bf08428b 	svclt	0x0008428b
d001aae8:	f0c04282 			; <UNDEFINED> instruction: 0xf0c04282
d001aaec:	429980c1 	addsmi	r8, r9, #193	; 0xc1
d001aaf0:	4290bf08 	addsmi	fp, r0, #8, 30
d001aaf4:	80b7f000 	adcshi	pc, r7, r0
d001aaf8:	230ae9dd 	movwcs	lr, #43485	; 0xa9dd
d001aafc:	0110e9dd 			; <UNDEFINED> instruction: 0x0110e9dd
d001ab00:	bf08428b 	svclt	0x0008428b
d001ab04:	f47f4282 			; <UNDEFINED> instruction: 0xf47f4282
d001ab08:	9b17ae2d 	blls	0xd06063c4
d001ab0c:	33012200 	movwcc	r2, #4608	; 0x1200
d001ab10:	23009317 	movwcs	r9, #791	; 0x317
d001ab14:	230ae9cd 	movwcs	lr, #43469	; 0xa9cd
d001ab18:	4619e624 	ldrmi	lr, [r9], -r4, lsr #12
d001ab1c:	f7fe4658 			; <UNDEFINED> instruction: 0xf7fe4658
d001ab20:	e675ff13 	uhadd16	pc, r5, r3	; <UNPREDICTABLE>
d001ab24:	0310f016 	tsteq	r0, #22	; <UNPREDICTABLE>
d001ab28:	2204bf14 	andcs	fp, r4, #20, 30	; 0x50
d001ab2c:	931b2203 	tstls	fp, #805306368	; 0x30000000
d001ab30:	b177e63f 	cmnlt	r7, pc, lsr r6
d001ab34:	e6919e09 	ldr	r9, [r1], r9, lsl #28
d001ab38:	e665461e 			; <UNDEFINED> instruction: 0xe665461e
d001ab3c:	0203f006 	andeq	pc, r3, #6
d001ab40:	0301f006 	movweq	pc, #4102	; 0x1006	; <UNPREDICTABLE>
d001ab44:	2200921e 	andcs	r9, r0, #-536870911	; 0xe0000001
d001ab48:	0601f083 	streq	pc, [r1], -r3, lsl #1
d001ab4c:	92129316 	andsls	r9, r2, #1476395008	; 0x58000000
d001ab50:	2150e65a 	cmpcs	r0, sl, asr r6
d001ab54:	9b12e6f9 	blls	0xd04d4740
d001ab58:	e6559316 			; <UNDEFINED> instruction: 0xe6559316
d001ab5c:	1e5d9b12 	vmovne.s8	r9, d13[0]
d001ab60:	f43f2b00 			; <UNDEFINED> instruction: 0xf43f2b00
d001ab64:	3d01ae66 	stccc	14, cr10, [r1, #-408]	; 0xfffffe68
d001ab68:	46582130 			; <UNDEFINED> instruction: 0x46582130
d001ab6c:	feecf7fe 	mcr2	7, 7, pc, cr12, cr14, {7}	; <UNPREDICTABLE>
d001ab70:	d1f81c6a 	mvnsle	r1, sl, ror #24
d001ab74:	f1c7e65d 			; <UNDEFINED> instruction: 0xf1c7e65d
d001ab78:	e9dd030d 	ldmib	sp, {r0, r2, r3, r8, r9}^
d001ab7c:	009b120c 	addseq	r1, fp, ip, lsl #4
d001ab80:	f1c34618 			; <UNDEFINED> instruction: 0xf1c34618
d001ab84:	f1a30c20 			; <UNDEFINED> instruction: 0xf1a30c20
d001ab88:	460b0e20 	strmi	r0, [fp], -r0, lsr #28
d001ab8c:	fc0cfa02 	stc2	10, cr15, [ip], {2}	; <UNPREDICTABLE>
d001ab90:	32fff04f 	rscscc	pc, pc, #79	; 0x4f
d001ab94:	f1a040c3 			; <UNDEFINED> instruction: 0xf1a040c3
d001ab98:	930a0120 	movwls	r0, #41248	; 0xa120
d001ab9c:	33fff04f 	mvnscc	pc, #79	; 0x4f
d001aba0:	fe0efa03 	vseleq.f32	s30, s28, s6
d001aba4:	f300fa02 	vpmax.u8	d15, d0, d2
d001aba8:	ea429a0a 	b	0xd10c13d8
d001abac:	f1c0020c 			; <UNDEFINED> instruction: 0xf1c0020c
d001abb0:	920a0c20 	andls	r0, sl, #32, 24	; 0x2000
d001abb4:	fa229a0d 	blx	0xd08c13f0
d001abb8:	ea43f101 	b	0xd1116fc4
d001abbc:	f04f020e 			; <UNDEFINED> instruction: 0xf04f020e
d001abc0:	fa2333ff 	blx	0xd08e7bc4
d001abc4:	4603fc0c 	strmi	pc, [r3], -ip, lsl #24
d001abc8:	30fff04f 	rscscc	pc, pc, pc, asr #32
d001abcc:	0e21f1a3 	abseqdp	f7, f3
d001abd0:	40989315 	addsmi	r9, r8, r5, lsl r3
d001abd4:	ea429b0a 	b	0xd10c1804
d001abd8:	430b020c 	movwmi	r0, #45580	; 0xb20c
d001abdc:	921b2101 	andsls	r2, fp, #1073741824	; 0x40000000
d001abe0:	9b0c930a 	blls	0xd033f810
d001abe4:	ea239a15 	b	0xd0901440
d001abe8:	00b80300 	adcseq	r0, r8, r0, lsl #6
d001abec:	0c21f1c2 	stfeqd	f7, [r1], #-776	; 0xfffffcf8
d001abf0:	93189715 	tstls	r8, #5505024	; 0x540000
d001abf4:	f30efa01 	vpmax.u8	d15, d14, d1
d001abf8:	0e20f1a0 	abseqdp	f7, f0
d001abfc:	fc0cfa21 	stc2	10, cr15, [ip], {33}	; 0x21	; <UNPREDICTABLE>
d001ac00:	9b0d930f 	blls	0xd037f844
d001ac04:	930b40d3 	movwls	r4, #45267	; 0xb0d3
d001ac08:	f30efa01 	vpmax.u8	d15, d14, d1
d001ac0c:	0e20f1c0 	abseqdm	f7, f0
d001ac10:	9b0f9311 	blls	0xd03ff85c
d001ac14:	fe0efa21 	vseleq.f32	s30, s28, s3
d001ac18:	030cea43 	movweq	lr, #51779	; 0xca43
d001ac1c:	3cfff102 	ldfccp	f7, [pc], #8	; 0xd001ac2c
d001ac20:	930f9a1b 	movwls	r9, #64027	; 0xfa1b
d001ac24:	ea239b0d 	b	0xd0901860
d001ac28:	fa010202 	blx	0xd005b438
d001ac2c:	930ef30c 	movwls	pc, #58124	; 0xe30c	; <UNPREDICTABLE>
d001ac30:	92199b11 	andsls	r9, r9, #17408	; 0x4400
d001ac34:	030eea43 	movweq	lr, #59971	; 0xea43
d001ac38:	fa019311 	blx	0xd007f884
d001ac3c:	9310f300 	tstls	r0, #0, 6	; <UNPREDICTABLE>
d001ac40:	f8d9e74c 			; <UNDEFINED> instruction: 0xf8d9e74c
d001ac44:	1d193000 	ldcne	0, cr3, [r9, #-0]
d001ac48:	1000f8c9 	andne	pc, r0, r9, asr #17
d001ac4c:	801a681b 	andshi	r6, sl, fp, lsl r8
d001ac50:	bb5df7ff 	bllt	0xd1798c54
d001ac54:	3000f8d9 	ldrdcc	pc, [r0], -r9
d001ac58:	f8c91d19 			; <UNDEFINED> instruction: 0xf8c91d19
d001ac5c:	681b1000 	ldmdavs	fp, {ip}
d001ac60:	f7ff701a 			; <UNDEFINED> instruction: 0xf7ff701a
d001ac64:	b95fbb54 	ldmdblt	pc, {r2, r4, r6, r8, r9, fp, ip, sp, pc}^	; <UNPREDICTABLE>
d001ac68:	2b009b16 	blcs	0xd00418c8
d001ac6c:	af44f43f 	svcge	0x0044f43f
d001ac70:	33019b0a 	movwcc	r9, #6922	; 0x1b0a
d001ac74:	9b0b930a 	blls	0xd02ff8a4
d001ac78:	0300f143 	movweq	pc, #323	; 0x143	; <UNPREDICTABLE>
d001ac7c:	e73b930b 	ldr	r9, [fp, -fp, lsl #6]!
d001ac80:	f0039b0a 			; <UNDEFINED> instruction: 0xf0039b0a
d001ac84:	931c0301 	tstls	ip, #67108864	; 0x4000000
d001ac88:	931d2300 	tstls	sp, #0, 6
d001ac8c:	231ce9dd 	tstcs	ip, #3620864	; 0x374000
d001ac90:	f43f4313 			; <UNDEFINED> instruction: 0xf43f4313
d001ac94:	e7ebaf31 			; <UNDEFINED> instruction: 0xe7ebaf31
d001ac98:	e6562170 			; <UNDEFINED> instruction: 0xe6562170
d001ac9c:	24001e6e 	strcs	r1, [r0], #-3694	; 0xfffff192
d001aca0:	f8d9e63c 			; <UNDEFINED> instruction: 0xf8d9e63c
d001aca4:	23000000 	movwcs	r0, #0
d001aca8:	30046802 	andcc	r6, r4, r2, lsl #16
d001acac:	0000f8c9 	andeq	pc, r0, r9, asr #17
d001acb0:	bb1bf7ff 	bllt	0xd0718cb4
d001acb4:	3000f8d9 	ldrdcc	pc, [r0], -r9
d001acb8:	33046818 	movwcc	r6, #18456	; 0x4818
d001acbc:	f8c917c1 			; <UNDEFINED> instruction: 0xf8c917c1
d001acc0:	f7ff3000 			; <UNDEFINED> instruction: 0xf7ff3000
d001acc4:	bf00bb58 	svclt	0x0000bb58
d001acc8:	fffffc02 			; <UNDEFINED> instruction: 0xfffffc02
d001accc:	fffff88e 			; <UNDEFINED> instruction: 0xfffff88e

Disassembly of section .text.vsnprintf:

d001acd0 <.text.vsnprintf>:
d001acd0:	b0a7b5f0 	strdlt	fp, [r7], r0	; <UNPREDICTABLE>
d001acd4:	460e4607 	strmi	r4, [lr], -r7, lsl #12
d001acd8:	4614461d 			; <UNDEFINED> instruction: 0x4614461d
d001acdc:	228c2100 	addcs	r2, ip, #0, 2
d001ace0:	f7fea803 			; <UNDEFINED> instruction: 0xf7fea803
d001ace4:	9701fc31 	smuadxls	r1, r1, ip
d001ace8:	95009602 	strls	r9, [r0, #-1538]	; 0xfffff9fe
d001acec:	4621b134 			; <UNDEFINED> instruction: 0x4621b134
d001acf0:	a801466a 	stmdage	r1, {r1, r3, r5, r6, r9, sl, lr}
d001acf4:	fa54f7ff 	blx	0xd1558cf8
d001acf8:	bdf0b027 	ldcllt	0, cr11, [r0, #156]!	; 0x9c
d001acfc:	30fff04f 	rscscc	pc, pc, pc, asr #32
d001ad00:	bf00e7fa 	svclt	0x0000e7fa

Disassembly of section .text.snprintf:

d001ad04 <.text.snprintf>:
d001ad04:	b500b40c 	strlt	fp, [r0, #-1036]	; 0xfffffbf4
d001ad08:	ab04b083 	blge	0xd0146f1c
d001ad0c:	2b04f853 	blcs	0xd0158e60
d001ad10:	f7ff9301 			; <UNDEFINED> instruction: 0xf7ff9301
d001ad14:	b003ffdd 	ldrdlt	pc, [r3], -sp
d001ad18:	eb04f85d 	bl	0xd0158e94
d001ad1c:	4770b002 	ldrbmi	fp, [r0, -r2]!

Disassembly of section .text.memchr:

d001ad48 <.text.memchr>:
d001ad48:	4603b192 			; <UNDEFINED> instruction: 0x4603b192
d001ad4c:	b410b2c9 	ldrlt	fp, [r0], #-713	; 0xfffffd37
d001ad50:	e0011884 	and	r1, r1, r4, lsl #17
d001ad54:	d00742a3 	andle	r4, r7, r3, lsr #5
d001ad58:	f8134618 			; <UNDEFINED> instruction: 0xf8134618
d001ad5c:	428a2b01 	addmi	r2, sl, #1024	; 0x400
d001ad60:	f85dd1f8 			; <UNDEFINED> instruction: 0xf85dd1f8
d001ad64:	47704b04 	ldrbmi	r4, [r0, -r4, lsl #22]!
d001ad68:	f85d2000 			; <UNDEFINED> instruction: 0xf85d2000
d001ad6c:	47704b04 	ldrbmi	r4, [r0, -r4, lsl #22]!
d001ad70:	47704610 			; <UNDEFINED> instruction: 0x47704610

Disassembly of section .text.strlen:

d001ad74 <.text.strlen>:
d001ad74:	b1327802 	teqlt	r2, r2, lsl #16
d001ad78:	f8134603 			; <UNDEFINED> instruction: 0xf8134603
d001ad7c:	29001f01 	stmdbcs	r0, {r0, r8, r9, sl, fp, ip}
d001ad80:	1a18d1fb 	bne	0xd064f574
d001ad84:	46104770 			; <UNDEFINED> instruction: 0x46104770
d001ad88:	bf004770 	svclt	0x00004770

Disassembly of section .text.strcmp:

d001ad8c <.text.strcmp>:
d001ad8c:	b1937803 	orrslt	r7, r3, r3, lsl #16
d001ad90:	e002b410 	and	fp, r2, r0, lsl r4
d001ad94:	3f01f810 	svccc	0x0001f810
d001ad98:	460cb143 	strmi	fp, [ip], -r3, asr #2
d001ad9c:	2b01f811 	blcs	0xd0098de8
d001ada0:	d0f7429a 	smlalsle	r4, r7, sl, r2
d001ada4:	f85d1a98 			; <UNDEFINED> instruction: 0xf85d1a98
d001ada8:	47704b04 	ldrbmi	r4, [r0, -r4, lsl #22]!
d001adac:	f85d7862 			; <UNDEFINED> instruction: 0xf85d7862
d001adb0:	1a984b04 	bne	0xce62d9c8
d001adb4:	780a4770 	stmdavc	sl, {r4, r5, r6, r8, r9, sl, lr}
d001adb8:	47701a98 			; <UNDEFINED> instruction: 0x47701a98

Disassembly of section .text.strchr:

d001adbc <.text.strchr>:
d001adbc:	7803b2c9 	stmdavc	r3, {r0, r3, r6, r7, r9, ip, sp, pc}
d001adc0:	d0064299 	mulle	r6, r9, r2
d001adc4:	f810b123 			; <UNDEFINED> instruction: 0xf810b123
d001adc8:	428b3f01 	addmi	r3, fp, #1, 30
d001adcc:	4770d1fa 			; <UNDEFINED> instruction: 0x4770d1fa
d001add0:	47704618 			; <UNDEFINED> instruction: 0x47704618

Disassembly of section .text.strrchr:

d001add4 <.text.strrchr>:
d001add4:	b2c92200 	sbclt	r2, r9, #0, 4
d001add8:	4604b410 			; <UNDEFINED> instruction: 0x4604b410
d001addc:	3b01f810 	blcc	0xd0098e24
d001ade0:	bf08428b 	svclt	0x0008428b
d001ade4:	2b004622 	blcs	0xd002c674
d001ade8:	4610d1f7 			; <UNDEFINED> instruction: 0x4610d1f7
d001adec:	4b04f85d 	blmi	0xd0158f68
d001adf0:	bf004770 	svclt	0x00004770
