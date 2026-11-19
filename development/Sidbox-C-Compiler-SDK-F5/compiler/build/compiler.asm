
/mnt/LinuxDatas/work/SidboxIDE/SidboxIDE/development/Sidbox-C-Compiler-SDK-F5/compiler/build/cgarm/compiler-cgarm/compiler.elf:     file format elf32-littlearm


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
d0010238:	f00c2600 			; <UNDEFINED> instruction: 0xf00c2600
d001023c:	f44ff911 	vst2.8	{d31,d33}, [pc :64], r1
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


Disassembly of section .text.pp_take:

d00102b8 <.text.pp_take>:
d00102b8:	460eb570 			; <UNDEFINED> instruction: 0x460eb570
d00102bc:	f7ff4604 			; <UNDEFINED> instruction: 0xf7ff4604
d00102c0:	4630ffdb 			; <UNDEFINED> instruction: 0x4630ffdb
d00102c4:	fce2f00d 	stc2l	0, cr15, [r2], #52	; 0x34
d00102c8:	46056aa3 	strmi	r6, [r5], -r3, lsr #21
d00102cc:	1a1b6a60 	bne	0xd06eac54
d00102d0:	d20142ab 	andle	r4, r1, #-1342177270	; 0xb000000a
d00102d4:	bd702000 	ldcllt	0, cr2, [r0, #-0]
d00102d8:	4631462a 	ldrtmi	r4, [r1], -sl, lsr #12
d00102dc:	f8def00c 			; <UNDEFINED> instruction: 0xf8def00c
d00102e0:	d1f72800 	mvnsle	r2, r0, lsl #16
d00102e4:	44286a60 	strtmi	r6, [r8], #-2656	; 0xfffff5a0
d00102e8:	20016260 	andcs	r6, r1, r0, ror #4
d00102ec:	Address 0x00000000d00102ec is out of bounds.


Disassembly of section .text.macro_index:

d00102ee <.text.macro_index>:
d00102ee:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d00102f2:	462bf500 	strtmi	pc, [fp], -r0, lsl #10
d00102f6:	444ff500 	strbmi	pc, [pc], #-1280	; 0xd00102fe	; <UNPREDICTABLE>
d00102fa:	46174688 	ldrmi	r4, [r7], -r8, lsl #13
d00102fe:	25003688 	strcs	r3, [r0, #-1672]	; 0xfffff978
d0010302:	68233488 	stmdavs	r3!, {r3, r7, sl, ip, sp}
d0010306:	d80242ab 	stmdale	r2, {r0, r1, r3, r5, r7, r9, lr}
d001030a:	30fff04f 	rscscc	pc, pc, pc, asr #32
d001030e:	4630e00b 	ldrtmi	lr, [r0], -fp
d0010312:	fcbbf00d 	ldc2	0, cr15, [fp], #52	; 0x34
d0010316:	d10842b8 			; <UNDEFINED> instruction: 0xd10842b8
d001031a:	4641463a 			; <UNDEFINED> instruction: 0x4641463a
d001031e:	f00c4630 			; <UNDEFINED> instruction: 0xf00c4630
d0010322:	b910f8bc 	ldmdblt	r0, {r2, r3, r4, r5, r7, fp, ip, sp, lr, pc}
d0010326:	e8bd4628 	pop	{r3, r5, r9, sl, lr}
d001032a:	350181f0 	strcc	r8, [r1, #-496]	; 0xfffffe10
d001032e:	e7e83648 	strb	r3, [r8, r8, asr #12]!

Disassembly of section .text.letter:

d0010332 <.text.letter>:
d0010332:	0320f020 	nopeq	{32}
d0010336:	2b193b41 	blcs	0xd065f042
d001033a:	f1a0d904 			; <UNDEFINED> instruction: 0xf1a0d904
d001033e:	4258035f 	subsmi	r0, r8, #2080374785	; 0x7c000001
d0010342:	47704158 			; <UNDEFINED> instruction: 0x47704158
d0010346:	47702001 	ldrbmi	r2, [r0, -r1]!

Disassembly of section .text.hex_digit:

d001034a <.text.hex_digit>:
d001034a:	38304603 	ldmdacc	r0!, {r0, r1, r9, sl, lr}
d001034e:	d9082809 	stmdble	r8, {r0, r3, fp, sp}
d0010352:	0020f043 	eoreq	pc, r0, r3, asr #32
d0010356:	0361f1a0 	msreq	SPSR_c, #160, 2	; 0x28
d001035a:	d8012b05 	stmdale	r1, {r0, r2, r8, r9, fp, sp}
d001035e:	47703857 			; <UNDEFINED> instruction: 0x47703857
d0010362:	47702010 			; <UNDEFINED> instruction: 0x47702010

Disassembly of section .text.valid_api_name:

d0010366 <.text.valid_api_name>:
d0010366:	4602b510 			; <UNDEFINED> instruction: 0x4602b510
d001036a:	f7ff7800 			; <UNDEFINED> instruction: 0xf7ff7800
d001036e:	b170ffe1 	cmnlt	r0, r1, ror #31	; <UNPREDICTABLE>
d0010372:	041ff102 	ldreq	pc, [pc], #-258	; 0xd001037a
d0010376:	1f01f812 	svcne	0x0001f812
d001037a:	4608b151 			; <UNDEFINED> instruction: 0x4608b151
d001037e:	ffd8f7ff 			; <UNDEFINED> instruction: 0xffd8f7ff
d0010382:	3930b910 	ldmdbcc	r0!, {r4, r8, fp, ip, sp, pc}
d0010386:	d8022909 	stmdale	r2, {r0, r3, r8, fp, sp}
d001038a:	d1f342a2 	mvnsle	r4, r2, lsr #5
d001038e:	bd102000 	ldclt	0, cr2, [r0, #-0]
d0010392:	e7fc2001 	ldrb	r2, [ip, r1]!

Disassembly of section .text.escape_byte.isra.0:

d00103cc <.text.escape_byte.isra.0>:
d00103cc:	47f0e92d 	ldrbmi	lr, [r0, sp, lsr #18]!
d00103d0:	46059e09 	strmi	r9, [r5], -r9, lsl #28
d00103d4:	f8dd461f 			; <UNDEFINED> instruction: 0xf8dd461f
d00103d8:	6830a020 	ldmdavs	r0!, {r5, sp, pc}
d00103dc:	8028f8dd 	ldrdhi	pc, [r8], -sp	; <UNPREDICTABLE>
d00103e0:	60331c43 	eorsvs	r1, r3, r3, asr #24
d00103e4:	2c787804 	ldclcs	8, cr7, [r8], #-16
d00103e8:	2c6dd812 	stclcs	8, cr13, [sp], #-72	; 0xffffffb8
d00103ec:	2c3fd828 	ldccs	8, cr13, [pc], #-160	; 0xd0010354
d00103f0:	2c21d84e 	stccs	8, cr13, [r1], #-312	; 0xfffffec8
d00103f4:	f1a4d90c 			; <UNDEFINED> instruction: 0xf1a4d90c
d00103f8:	fa5f0c22 	blx	0xd17d3488
d00103fc:	f04ffe8c 			; <UNDEFINED> instruction: 0xf04ffe8c
d0010400:	fa0c0c01 	blx	0xd031340c
d0010404:	f8dffc0e 			; <UNDEFINED> instruction: 0xf8dffc0e
d0010408:	ea1ce160 	b	0xd0748990
d001040c:	d13a0f0e 	teqle	sl, lr, lsl #30
d0010410:	2c073c30 	stccs	12, cr3, [r7], {48}	; 0x30
d0010414:	4543d86a 	strbmi	sp, [r3, #-2154]	; 0xfffff796
d0010418:	7843d035 	stmdavc	r3, {r0, r2, r4, r5, ip, lr, pc}^
d001041c:	2b073b30 	blcs	0xd01df0e4
d0010420:	f100d831 			; <UNDEFINED> instruction: 0xf100d831
d0010424:	f8c60c02 			; <UNDEFINED> instruction: 0xf8c60c02
d0010428:	45e0c000 	strbmi	ip, [r0, #0]!
d001042c:	f1a37843 			; <UNDEFINED> instruction: 0xf1a37843
d0010430:	eb030330 	bl	0xd00d10f8
d0010434:	f04004c4 			; <UNDEFINED> instruction: 0xf04004c4
d0010438:	2cff8086 	ldclcs	0, cr8, [pc], #536	; 0xd0010658
d001043c:	e022d856 	eor	sp, r2, r6, asr r8
d0010440:	0c6ef1a4 	stfeqp	f7, [lr], #-656	; 0xfffffd70
d0010444:	0f0af1bc 	svceq	0x000af1bc
d0010448:	f20fd8e2 	vadd.i8	<illegal reg q6.5>, <illegal reg q15.5>, q9
d001044c:	f85e0e0c 			; <UNDEFINED> instruction: 0xf85e0e0c
d0010450:	44e6c02c 	strbtmi	ip, [r6], #44	; 0x2c
d0010454:	bf004770 	svclt	0x00004770
d0010458:	00000107 	andeq	r0, r0, r7, lsl #2
d001045c:	ffffffb9 			; <UNDEFINED> instruction: 0xffffffb9
d0010460:	ffffffb9 			; <UNDEFINED> instruction: 0xffffffb9
d0010464:	ffffffb9 			; <UNDEFINED> instruction: 0xffffffb9
d0010468:	0000002d 	andeq	r0, r0, sp, lsr #32
d001046c:	ffffffb9 			; <UNDEFINED> instruction: 0xffffffb9
d0010470:	00000089 	andeq	r0, r0, r9, lsl #1
d0010474:	ffffffb9 			; <UNDEFINED> instruction: 0xffffffb9
d0010478:	0000008d 	andeq	r0, r0, sp, lsl #1
d001047c:	ffffffb9 			; <UNDEFINED> instruction: 0xffffffb9
d0010480:	00000091 	muleq	r0, r1, r0
d0010484:	4620240d 	strtmi	r2, [r0], -sp, lsl #8
d0010488:	87f0e8bd 			; <UNDEFINED> instruction: 0x87f0e8bd
d001048c:	e7fa2408 	ldrb	r2, [sl, r8, lsl #8]!
d0010490:	0c5cf1a4 	ldfeqp	f7, [ip], {164}	; 0xa4
d0010494:	fe8cfa5f 	mcr2	10, 4, pc, cr12, cr15, {2}	; <UNPREDICTABLE>
d0010498:	0f0af1be 	svceq	0x000af1be
d001049c:	f1bcd8b8 			; <UNDEFINED> instruction: 0xf1bcd8b8
d00104a0:	d8b50f0a 	ldmle	r5!, {r1, r3, r8, r9, sl, fp}
d00104a4:	0e08f20f 	cdpeq	2, 0, cr15, cr8, cr15, {0}
d00104a8:	c02cf85e 	eorgt	pc, ip, lr, asr r8	; <UNPREDICTABLE>
d00104ac:	477044e6 	ldrbmi	r4, [r0, -r6, ror #9]!
d00104b0:	ffffffd7 			; <UNDEFINED> instruction: 0xffffffd7
d00104b4:	ffffff61 			; <UNDEFINED> instruction: 0xffffff61
d00104b8:	ffffff61 			; <UNDEFINED> instruction: 0xffffff61
d00104bc:	ffffff61 			; <UNDEFINED> instruction: 0xffffff61
d00104c0:	ffffff61 			; <UNDEFINED> instruction: 0xffffff61
d00104c4:	000000b3 	strheq	r0, [r0], -r3
d00104c8:	ffffffdd 			; <UNDEFINED> instruction: 0xffffffdd
d00104cc:	ffffff61 			; <UNDEFINED> instruction: 0xffffff61
d00104d0:	ffffff61 			; <UNDEFINED> instruction: 0xffffff61
d00104d4:	ffffff61 			; <UNDEFINED> instruction: 0xffffff61
d00104d8:	0000002d 	andeq	r0, r0, sp, lsr #32
d00104dc:	e7d2240c 	ldrb	r2, [r2, ip, lsl #8]
d00104e0:	e7d02409 	ldrb	r2, [r0, r9, lsl #8]
d00104e4:	e7ce240b 	strb	r2, [lr, fp, lsl #8]
d00104e8:	d1044543 	tstle	r4, r3, asr #10
d00104ec:	b9fc6dac 	ldmiblt	ip!, {r2, r3, r5, r7, r8, sl, fp, sp, lr}^
d00104f0:	447b4b1e 	ldrbtmi	r4, [fp], #-2846	; 0xfffff4e2
d00104f4:	7840e020 	stmdavc	r0, {r5, sp, lr, pc}^
d00104f8:	ff27f7ff 			; <UNDEFINED> instruction: 0xff27f7ff
d00104fc:	d0f52810 	rscsle	r2, r5, r0, lsl r8
d0010500:	f8d62400 			; <UNDEFINED> instruction: 0xf8d62400
d0010504:	45c89000 	strbmi	r9, [r8]
d0010508:	f899d0bd 			; <UNDEFINED> instruction: 0xf899d0bd
d001050c:	f7ff0000 			; <UNDEFINED> instruction: 0xf7ff0000
d0010510:	2810ff1c 	ldmdacs	r0, {r2, r3, r4, r8, r9, sl, fp, ip, sp, lr, pc}
d0010514:	f109d0b7 			; <UNDEFINED> instruction: 0xf109d0b7
d0010518:	01240301 			; <UNDEFINED> instruction: 0x01240301
d001051c:	f8996033 			; <UNDEFINED> instruction: 0xf8996033
d0010520:	f7ff0000 			; <UNDEFINED> instruction: 0xf7ff0000
d0010524:	4404ff12 	strmi	pc, [r4], #-3858	; 0xfffff0ee
d0010528:	d9ea2cff 	stmible	sl!, {r0, r1, r2, r3, r4, r5, r6, r7, sl, fp, sp}^
d001052c:	b10c6dac 	smlatblt	ip, ip, sp, r6
d0010530:	e7a82400 	str	r2, [r8, r0, lsl #8]!
d0010534:	447b4b0e 	ldrbtmi	r4, [fp], #-2830	; 0xfffff4f2
d0010538:	a068f8c5 	rsbge	pc, r8, r5, asr #17
d001053c:	3116e9c5 	tstcc	r6, r5, asr #19
d0010540:	2718e9c5 	ldrcs	lr, [r8, -r5, asr #19]
d0010544:	7883e79f 	stmvc	r3, {r0, r1, r2, r3, r4, r7, r8, r9, sl, sp, lr, pc}
d0010548:	2b073b30 	blcs	0xd01df210
d001054c:	af75f63f 	svcge	0x0075f63f
d0010550:	60331cc3 	eorsvs	r1, r3, r3, asr #25
d0010554:	3b307883 	blcc	0xd0c2e768
d0010558:	04c4eb03 	strbeq	lr, [r4], #2819	; 0xb03
d001055c:	240ae76d 	strcs	lr, [sl], #-1901	; 0xfffff893
d0010560:	2407e791 	strcs	lr, [r7], #-1937	; 0xfffff86f
d0010564:	bf00e78f 	svclt	0x0000e78f
d0010568:	20000021 	andcs	r0, r0, r1, lsr #32
d001056c:	fffffeb8 			; <UNDEFINED> instruction: 0xfffffeb8
d0010570:	fffffe5c 			; <UNDEFINED> instruction: 0xfffffe5c

Disassembly of section .text.same_name.isra.0:

d0010574 <.text.same_name.isra.0>:
d0010574:	460cb510 			; <UNDEFINED> instruction: 0x460cb510
d0010578:	429c4611 	addsmi	r4, ip, #17825792	; 0x1100000
d001057c:	4622d106 	strtmi	sp, [r2], -r6, lsl #2
d0010580:	ff8cf00b 			; <UNDEFINED> instruction: 0xff8cf00b
d0010584:	f080fab0 			; <UNDEFINED> instruction: 0xf080fab0
d0010588:	bd100940 	vldrlt.16	s0, [r0, #-128]	; 0xffffff80	; <UNPREDICTABLE>
d001058c:	e7fc2000 	ldrb	r2, [ip, r0]!

Disassembly of section .text.find_record.isra.0:

d0010590 <.text.find_record.isra.0>:
d0010590:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d0010594:	34bcf500 	ldrtcc	pc, [ip], #1280	; 0x500	; <UNPREDICTABLE>
d0010598:	4690460f 	ldrmi	r4, [r0], pc, lsl #12
d001059c:	34082500 	strcc	r2, [r8], #-1280	; 0xfffffb00
d00105a0:	36d8f500 	ldrbcc	pc, [r8], r0, lsl #10	; <UNPREDICTABLE>
d00105a4:	f983fa5f 			; <UNDEFINED> instruction: 0xf983fa5f
d00105a8:	31c8f8d6 	ldrdcc	pc, [r8, #134]	; 0x86
d00105ac:	d302429d 	movwle	r4, #8861	; 0x229d
d00105b0:	30fff04f 	rscscc	pc, pc, pc, asr #32
d00105b4:	f894e00e 			; <UNDEFINED> instruction: 0xf894e00e
d00105b8:	b96b3264 	stmdblt	fp!, {r2, r5, r6, r9, ip, sp}^
d00105bc:	463a4643 	ldrtmi	r4, [sl], -r3, asr #12
d00105c0:	0100e9d4 	ldrdeq	lr, [r0, -r4]
d00105c4:	ffd6f7ff 			; <UNDEFINED> instruction: 0xffd6f7ff
d00105c8:	f894b130 			; <UNDEFINED> instruction: 0xf894b130
d00105cc:	454b3263 	strbmi	r3, [fp, #-611]	; 0xfffffd9d
d00105d0:	4628d102 	strtmi	sp, [r8], -r2, lsl #2
d00105d4:	83f8e8bd 	mvnshi	lr, #12386304	; 0xbd0000
d00105d8:	f5043501 			; <UNDEFINED> instruction: 0xf5043501
d00105dc:	e7e3741a 			; <UNDEFINED> instruction: 0xe7e3741a

Disassembly of section .text.records_equal:

d00105e0 <.text.records_equal>:
d00105e0:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d00105e4:	3260f8d0 	rsbcc	pc, r0, #208, 16	; 0xd00000
d00105e8:	f0234605 			; <UNDEFINED> instruction: 0xf0234605
d00105ec:	f8d1427f 			; <UNDEFINED> instruction: 0xf8d1427f
d00105f0:	f0233260 			; <UNDEFINED> instruction: 0xf0233260
d00105f4:	429a437f 	addsmi	r4, sl, #-67108863	; 0xfc000001
d00105f8:	2000d002 	andcs	sp, r0, r2
d00105fc:	83f8e8bd 	mvnshi	lr, #12386304	; 0xbd0000
d0010600:	2263f890 	rsbcs	pc, r3, #144, 16	; 0x900000
d0010604:	3263f891 	rsbcc	pc, r3, #9502720	; 0x910000
d0010608:	d1f6429a 			; <UNDEFINED> instruction: 0xd1f6429a
d001060c:	460c4606 	strmi	r4, [ip], -r6, lsl #12
d0010610:	f8952700 			; <UNDEFINED> instruction: 0xf8952700
d0010614:	429f3262 	addsmi	r3, pc, #536870918	; 0x20000006
d0010618:	2001d301 	andcs	sp, r1, r1, lsl #6
d001061c:	6a63e7ee 	bvs	0xd190a5dc
d0010620:	6a2246b1 	bvs	0xd08a20ec
d0010624:	6a7146a0 	bvs	0xd1c620ac
d0010628:	f7ff6a30 			; <UNDEFINED> instruction: 0xf7ff6a30
d001062c:	2800ffa3 	stmdacs	r0, {r0, r1, r5, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0010630:	f896d0e3 			; <UNDEFINED> instruction: 0xf896d0e3
d0010634:	f8942040 			; <UNDEFINED> instruction: 0xf8942040
d0010638:	429a3040 	addsmi	r3, sl, #64	; 0x40
d001063c:	f8b9d1dd 			; <UNDEFINED> instruction: 0xf8b9d1dd
d0010640:	36242042 	strtcc	r2, [r4], -r2, asr #32
d0010644:	3042f8b8 	strhcc	pc, [r2], #-136	; 0xffffff78	; <UNPREDICTABLE>
d0010648:	429a3424 	addsmi	r3, sl, #36, 8	; 0x24000000
d001064c:	3701d1d5 			; <UNDEFINED> instruction: 0x3701d1d5
d0010650:	Address 0x00000000d0010650 is out of bounds.


Disassembly of section .text.find_local.isra.0:

d0010652 <.text.find_local.isra.0>:
d0010652:	3316f500 	tstcc	r6, #0, 10	; <UNPREDICTABLE>
d0010656:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d001065a:	61ecf8d3 	ldrdvs	pc, [ip, #131]!	; 0x83
d001065e:	460f252c 	strmi	r2, [pc], -ip, lsr #10
d0010662:	fb054690 	blx	0xd01620ac
d0010666:	f5000006 			; <UNDEFINED> instruction: 0xf5000006
d001066a:	f5043413 			; <UNDEFINED> instruction: 0xf5043413
d001066e:	b9167430 	ldmdblt	r6, {r4, r5, sl, ip, sp, lr}
d0010672:	30fff04f 	rscscc	pc, pc, pc, asr #32
d0010676:	6861e00a 	stmdavs	r1!, {r1, r3, sp, lr, pc}^
d001067a:	463a4643 	ldrtmi	r4, [sl], -r3, asr #12
d001067e:	092cf854 	stmdbeq	ip!, {r2, r4, r6, fp, ip, sp, lr, pc}
d0010682:	f7ff3e01 			; <UNDEFINED> instruction: 0xf7ff3e01
d0010686:	2800ff76 	stmdacs	r0, {r1, r2, r4, r5, r6, r8, r9, sl, fp, ip, sp, lr, pc}
d001068a:	4630d0f1 			; <UNDEFINED> instruction: 0x4630d0f1
d001068e:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d

Disassembly of section .text.find_global.isra.0:

d0010692 <.text.find_global.isra.0>:
d0010692:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d0010696:	35aff500 	strcc	pc, [pc, #1280]!	; 0xd0010b9e
d001069a:	460f4606 	strmi	r4, [pc], -r6, lsl #12
d001069e:	35044690 	strcc	r4, [r4, #-1680]	; 0xfffff970
d00106a2:	f5002400 			; <UNDEFINED> instruction: 0xf5002400
d00106a6:	f8d939bc 			; <UNDEFINED> instruction: 0xf8d939bc
d00106aa:	429c3004 	addsmi	r3, ip, #4
d00106ae:	f04fd302 			; <UNDEFINED> instruction: 0xf04fd302
d00106b2:	e00c30ff 	strd	r3, [ip], -pc	; <UNPREDICTABLE>
d00106b6:	2029f895 	mlacs	r9, r5, r8, pc	; <UNPREDICTABLE>
d00106ba:	429a7a33 	addsmi	r7, sl, #208896	; 0x33000
d00106be:	4643d109 	strbmi	sp, [r3], -r9, lsl #2
d00106c2:	e9d5463a 	ldmib	r5, {r1, r3, r4, r5, r9, sl, lr}^
d00106c6:	f7ff0100 			; <UNDEFINED> instruction: 0xf7ff0100
d00106ca:	b110ff54 	tstlt	r0, r4, asr pc	; <UNPREDICTABLE>
d00106ce:	e8bd4620 	pop	{r5, r9, sl, lr}
d00106d2:	340183f8 	strcc	r8, [r1], #-1016	; 0xfffffc08
d00106d6:	e7e63534 			; <UNDEFINED> instruction: 0xe7e63534

Disassembly of section .text.find_alias.isra.0:

d00106da <.text.find_alias.isra.0>:
d00106da:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d00106de:	35d8f500 	ldrbcc	pc, [r8, #1280]	; 0x500	; <UNPREDICTABLE>
d00106e2:	460f4606 	strmi	r4, [pc], -r6, lsl #12
d00106e6:	f5054690 			; <UNDEFINED> instruction: 0xf5054690
d00106ea:	240075e6 	strcs	r7, [r0], #-1510	; 0xfffffa1a
d00106ee:	39ddf500 	ldmibcc	sp, {r8, sl, ip, sp, lr, pc}^
d00106f2:	30ccf8d9 	ldrdcc	pc, [ip], #137	; 0x89
d00106f6:	d302429c 	movwle	r4, #8860	; 0x229c
d00106fa:	30fff04f 	rscscc	pc, pc, pc, asr #32
d00106fe:	f895e00c 			; <UNDEFINED> instruction: 0xf895e00c
d0010702:	7a332021 	bvc	0xd0cd878e
d0010706:	d109429a 			; <UNDEFINED> instruction: 0xd109429a
d001070a:	463a4643 	ldrtmi	r4, [sl], -r3, asr #12
d001070e:	0100e9d5 	ldrdeq	lr, [r0, -r5]
d0010712:	ff2ff7ff 			; <UNDEFINED> instruction: 0xff2ff7ff
d0010716:	4620b110 			; <UNDEFINED> instruction: 0x4620b110
d001071a:	83f8e8bd 	mvnshi	lr, #12386304	; 0xbd0000
d001071e:	35243401 	strcc	r3, [r4, #-1025]!	; 0xfffffbff
d0010722:	Address 0x00000000d0010722 is out of bounds.


Disassembly of section .text.is_record_type:

d0010724 <.text.is_record_type>:
d0010724:	f46f6ac3 	vld1.64	{d22-d23}, [pc], r3
d0010728:	189a728b 	ldmne	sl, {r0, r1, r3, r7, r9, ip, sp, lr}
d001072c:	b5102a01 	ldrlt	r2, [r0, #-2561]	; 0xfffff5ff
d0010730:	d8014604 	stmdale	r1, {r2, r9, sl, lr}
d0010734:	bd102001 	ldclt	0, cr2, [r0, #-4]
d0010738:	1201f240 	andne	pc, r1, #64, 4
d001073c:	d10e4293 			; <UNDEFINED> instruction: 0xd10e4293
d0010740:	698169c2 	stmibvs	r1, {r1, r6, r7, r8, fp, sp, lr}
d0010744:	ffc9f7ff 			; <UNDEFINED> instruction: 0xffc9f7ff
d0010748:	db081e03 	blle	0xd0217f5c
d001074c:	fb002024 	blx	0xd00187e6
d0010750:	f5004003 			; <UNDEFINED> instruction: 0xf5004003
d0010754:	f89030d8 			; <UNDEFINED> instruction: 0xf89030d8
d0010758:	2bff31ec 	blcs	0xcffdcf10
d001075c:	2000d1ea 	andcs	sp, r0, sl, ror #3
d0010760:	Address 0x00000000d0010760 is out of bounds.


Disassembly of section .text.find_function.isra.0:

d0010762 <.text.find_function.isra.0>:
d0010762:	47f0e92d 	ldrbmi	lr, [r0, sp, lsr #18]!
d0010766:	34e5f500 	strbtcc	pc, [r5], #1280	; 0x500	; <UNPREDICTABLE>
d001076a:	46884606 	strmi	r4, [r8], r6, lsl #12
d001076e:	34dc4691 	ldrbcc	r4, [ip], #1681	; 0x691
d0010772:	f04f2500 			; <UNDEFINED> instruction: 0xf04f2500
d0010776:	f50037ff 			; <UNDEFINED> instruction: 0xf50037ff
d001077a:	f8da3aff 			; <UNDEFINED> instruction: 0xf8da3aff
d001077e:	429d30dc 	addsmi	r3, sp, #220	; 0xdc
d0010782:	464bd20f 	strbmi	sp, [fp], -pc, lsl #4
d0010786:	e9d44642 	ldmib	r4, {r1, r6, r9, sl, lr}^
d001078a:	f7ff0100 			; <UNDEFINED> instruction: 0xf7ff0100
d001078e:	b160fef2 	strdlt	pc, [r0, #-226]!	; 0xffffff1e
d0010792:	3028f894 	mlacc	r8, r4, r8, pc	; <UNPREDICTABLE>
d0010796:	f894b143 			; <UNDEFINED> instruction: 0xf894b143
d001079a:	7a332029 	bvc	0xd0cd8846
d001079e:	d104429a 			; <UNDEFINED> instruction: 0xd104429a
d00107a2:	4638462f 	ldrtmi	r4, [r8], -pc, lsr #12
d00107a6:	87f0e8bd 			; <UNDEFINED> instruction: 0x87f0e8bd
d00107aa:	3501462f 	strcc	r4, [r1, #-1583]	; 0xfffff9d1
d00107ae:	e7e43434 			; <UNDEFINED> instruction: 0xe7e43434

Disassembly of section .text.name_is.isra.0:

d00107b2 <.text.name_is.isra.0>:
d00107b2:	460db537 			; <UNDEFINED> instruction: 0x460db537
d00107b6:	46104604 	ldrmi	r4, [r0], -r4, lsl #12
d00107ba:	f00d9201 			; <UNDEFINED> instruction: 0xf00d9201
d00107be:	42a8fa66 	adcmi	pc, r8, #417792	; 0x66000
d00107c2:	99014602 	stmdbls	r1, {r1, r9, sl, lr}
d00107c6:	4620d107 	strtmi	sp, [r0], -r7, lsl #2
d00107ca:	fe67f00b 	cdp2	0, 6, cr15, cr7, cr11, {0}
d00107ce:	f080fab0 			; <UNDEFINED> instruction: 0xf080fab0
d00107d2:	b0030940 	andlt	r0, r3, r0, asr #18
d00107d6:	2000bd30 	andcs	fp, r0, r0, lsr sp
d00107da:	Address 0x00000000d00107da is out of bounds.


Disassembly of section .text.find_api_constant.isra.0:

d00107dc <.text.find_api_constant.isra.0>:
d00107dc:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d00107e0:	4558f500 	ldrbmi	pc, [r8, #-1280]	; 0xfffffb00	; <UNPREDICTABLE>
d00107e4:	4450f500 	ldrbmi	pc, [r0], #-1280	; 0xfffffb00	; <UNPREDICTABLE>
d00107e8:	4690460f 	ldrmi	r4, [r0], pc, lsl #12
d00107ec:	26003544 	strcs	r3, [r0], -r4, asr #10
d00107f0:	68233420 	stmdavs	r3!, {r5, sl, ip, sp}
d00107f4:	d304429e 	movwle	r4, #17054	; 0x429e
d00107f8:	0900f04f 	stmdbeq	r0, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d00107fc:	e8bd4648 	pop	{r3, r6, r9, sl, lr}
d0010800:	462a83f8 			; <UNDEFINED> instruction: 0x462a83f8
d0010804:	46384641 	ldrtmi	r4, [r8], -r1, asr #12
d0010808:	f7ff46a9 			; <UNDEFINED> instruction: 0xf7ff46a9
d001080c:	3524ffd2 	strcc	pc, [r4, #-4050]!	; 0xfffff02e
d0010810:	d1f32800 	mvnsle	r2, r0, lsl #16
d0010814:	e7ec3601 	strb	r3, [ip, r1, lsl #12]!

Disassembly of section .text.pp_unary:

d001082c <.text.pp_unary>:
d001082c:	e92d6ac3 	push	{r0, r1, r6, r7, r9, fp, sp, lr}
d0010830:	1c5a43f7 	mrrcne	3, 15, r4, sl, cr7
d0010834:	2a204604 	bcs	0xd082204c
d0010838:	d90962c2 	stmdble	r9, {r1, r6, r7, r9, sp, lr}
d001083c:	26002201 	strcs	r2, [r0], -r1, lsl #4
d0010840:	62c32700 	sbcvs	r2, r3, #0, 14
d0010844:	46306302 	ldrtmi	r6, [r0], -r2, lsl #6
d0010848:	b0034639 	andlt	r4, r3, r9, lsr r6
d001084c:	83f0e8bd 	mvnshi	lr, #12386304	; 0xbd0000
d0010850:	44794986 	ldrbtmi	r4, [r9], #-2438	; 0xfffff67a
d0010854:	fd30f7ff 	ldc2	7, cr15, [r0, #-1020]!	; 0xfffffc04
d0010858:	4620b148 	strtmi	fp, [r0], -r8, asr #2
d001085c:	ffe6f7ff 			; <UNDEFINED> instruction: 0xffe6f7ff
d0010860:	0301ea50 	movweq	lr, #6736	; 0x1a50
d0010864:	2601bf0c 	strcs	fp, [r1], -ip, lsl #30
d0010868:	27002600 	strcs	r2, [r0, -r0, lsl #12]
d001086c:	4980e00a 	stmibmi	r0, {r1, r3, sp, lr, pc}
d0010870:	44794620 	ldrbtmi	r4, [r9], #-1568	; 0xfffff9e0
d0010874:	fd20f7ff 	stc2	7, cr15, [r0, #-1020]!	; 0xfffffc04
d0010878:	4620b140 	strtmi	fp, [r0], -r0, asr #2
d001087c:	ffd6f7ff 			; <UNDEFINED> instruction: 0xffd6f7ff
d0010880:	43cf43c6 	bicmi	r4, pc, #402653187	; 0x18000003
d0010884:	3b016ae3 	blcc	0xd006b418
d0010888:	e7dc62e3 	ldrb	r6, [ip, r3, ror #5]
d001088c:	46204979 			; <UNDEFINED> instruction: 0x46204979
d0010890:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d0010894:	b128fd11 	msrlt	CPSR_f, r1, lsl sp
d0010898:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d001089c:	4606ffc7 	strmi	pc, [r6], -r7, asr #31
d00108a0:	e7ef460f 	strb	r4, [pc, pc, lsl #12]!
d00108a4:	46204974 			; <UNDEFINED> instruction: 0x46204974
d00108a8:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d00108ac:	b130fd05 	teqlt	r0, r5, lsl #26	; <UNPREDICTABLE>
d00108b0:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d00108b4:	4246ffbb 	submi	pc, r6, #748	; 0x2ec
d00108b8:	0741eb61 	strbeq	lr, [r1, -r1, ror #22]
d00108bc:	4620e7e2 	strtmi	lr, [r0], -r2, ror #15
d00108c0:	fcdaf7ff 	ldc2l	7, cr15, [sl], {255}	; 0xff
d00108c4:	1c5a6ae3 	mrrcne	10, 14, r6, sl, cr3
d00108c8:	62e22a20 	rscvs	r2, r2, #32, 20	; 0x20000
d00108cc:	2201d904 	andcs	sp, r1, #4, 18	; 0x10000
d00108d0:	62e32600 	rscvs	r2, r3, #0, 12
d00108d4:	e7c86322 	strb	r6, [r8, r2, lsr #6]
d00108d8:	44794968 	ldrbtmi	r4, [r9], #-2408	; 0xfffff698
d00108dc:	fcecf7ff 	stc2l	7, cr15, [ip], #1020	; 0x3fc
d00108e0:	4620b168 	strtmi	fp, [r0], -r8, ror #2
d00108e4:	fb3cf000 	blx	0xd0f4c8ee
d00108e8:	4965460f 	stmdbmi	r5!, {r0, r1, r2, r3, r9, sl, lr}^
d00108ec:	44794606 	ldrbtmi	r4, [r9], #-1542	; 0xfffff9fa
d00108f0:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d00108f4:	bba0fce1 	bllt	0xce84fc80
d00108f8:	63232301 			; <UNDEFINED> instruction: 0x63232301
d00108fc:	6a65e031 	bvs	0xd19889c8
d0010900:	8028f8d4 	ldrdhi	pc, [r8], -r4	; <UNPREDICTABLE>
d0010904:	d2514545 	subsle	r4, r1, #289406976	; 0x11400000
d0010908:	f1a07828 			; <UNDEFINED> instruction: 0xf1a07828
d001090c:	2b090330 	blcs	0xd02515d4
d0010910:	eba8d849 	bl	0xcea46a3c
d0010914:	2b020305 	blcs	0xd0091530
d0010918:	2830dd27 	ldmdacs	r0!, {r0, r1, r2, r5, r8, sl, fp, ip, lr, pc}
d001091c:	786bd12a 	stmdavc	fp!, {r1, r3, r5, r8, ip, lr, pc}^
d0010920:	03dff003 	bicseq	pc, pc, #3
d0010924:	d1272b58 			; <UNDEFINED> instruction: 0xd1272b58
d0010928:	21103502 	tstcs	r0, r2, lsl #10
d001092c:	25006265 	strcs	r6, [r0, #-613]	; 0xfffffd9b
d0010930:	27002600 	strcs	r2, [r0, -r0, lsl #12]
d0010934:	0901f04f 	stmdbeq	r1, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d0010938:	45906a62 	ldrmi	r6, [r0, #2658]	; 0xa62
d001093c:	8092f240 	addshi	pc, r2, r0, asr #4
d0010940:	f7ff7810 			; <UNDEFINED> instruction: 0xf7ff7810
d0010944:	4281fd02 	addmi	pc, r1, #2, 26	; 0x80
d0010948:	b91dd818 	ldmdblt	sp, {r3, r4, fp, ip, lr, pc}
d001094c:	45902301 	ldrmi	r2, [r0, #769]	; 0x301
d0010950:	d9066323 	stmdble	r6, {r0, r1, r5, r8, r9, sp, lr}
d0010954:	f0037813 			; <UNDEFINED> instruction: 0xf0037813
d0010958:	2b5503df 	blcs	0xd15518dc
d001095c:	3201d101 	andcc	sp, r1, #1073741824	; 0x40000000
d0010960:	6ae36262 	bvs	0xcf8e92f0
d0010964:	62e33b01 	rscvs	r3, r3, #1024	; 0x400
d0010968:	2830e78c 	ldmdacs	r0!, {r2, r3, r7, r8, r9, sl, sp, lr, pc}
d001096c:	210abf14 	tstcs	sl, r4, lsl pc
d0010970:	e7dc2108 	ldrb	r2, [ip, r8, lsl #2]
d0010974:	e7da210a 	ldrb	r2, [sl, sl, lsl #2]
d0010978:	e7d82108 	ldrb	r2, [r8, r8, lsl #2]
d001097c:	35011c53 	strcc	r1, [r1, #-3155]	; 0xfffff3ad
d0010980:	78106263 	ldmdavc	r0, {r0, r1, r5, r6, r9, sp, lr}
d0010984:	fce1f7ff 	stc2l	7, cr15, [r1], #1020	; 0x3fc
d0010988:	fbb343c3 	blx	0xcece189e
d001098c:	42b3f3f1 	adcsmi	pc, r3, #-1006632957	; 0xc4000003
d0010990:	2306fba1 	movwcs	pc, #27553	; 0x6ba1	; <UNPREDICTABLE>
d0010994:	f8c4bf38 			; <UNDEFINED> instruction: 0xf8c4bf38
d0010998:	18169030 	ldmdane	r6, {r4, r5, ip, pc}
d001099c:	3307fb01 	movwcc	pc, #31489	; 0x7b01	; <UNPREDICTABLE>
d00109a0:	0700f143 	streq	pc, [r0, -r3, asr #2]
d00109a4:	f7ffe7c8 			; <UNDEFINED> instruction: 0xf7ffe7c8
d00109a8:	b930fcc4 	ldmdblt	r0!, {r2, r6, r7, sl, fp, ip, sp, lr, pc}
d00109ac:	63232301 			; <UNDEFINED> instruction: 0x63232301
d00109b0:	27002600 	strcs	r2, [r0, -r0, lsl #12]
d00109b4:	3201e7d5 	andcc	lr, r1, #55836672	; 0x3540000
d00109b8:	6a626262 	bvs	0xd18a9348
d00109bc:	d9084590 	stmdble	r8, {r4, r7, r8, sl, lr}
d00109c0:	46087811 			; <UNDEFINED> instruction: 0x46087811
d00109c4:	fcb5f7ff 	ldc2	7, cr15, [r5], #1020	; 0x3fc
d00109c8:	d1f42800 	mvnsle	r2, r0, lsl #16
d00109cc:	29093930 	stmdbcs	r9, {r4, r5, r8, fp, ip, sp}
d00109d0:	1b52d9f1 	blne	0xd14c719c
d00109d4:	d1362a07 	teqle	r6, r7, lsl #20
d00109d8:	4628492a 	strtmi	r4, [r8], -sl, lsr #18
d00109dc:	44799201 	ldrbtmi	r9, [r9], #-513	; 0xfffffdff
d00109e0:	fd5cf00b 	ldc2l	0, cr15, [ip, #-44]	; 0xffffffd4
d00109e4:	bb709a01 	bllt	0xd1c371f0
d00109e8:	46204927 	strtmi	r4, [r0], -r7, lsr #18
d00109ec:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d00109f0:	4680fc63 	strmi	pc, [r0], r3, ror #24
d00109f4:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d00109f8:	6a61fc3f 	bvs	0xd188fafc
d00109fc:	42b16aa6 	adcsmi	r6, r1, #679936	; 0xa6000
d0010a00:	7808d003 	stmdavc	r8, {r0, r1, ip, lr, pc}
d0010a04:	fc95f7ff 	ldc2	7, cr15, [r5], {255}	; 0xff
d0010a08:	2301b908 	movwcs	fp, #6408	; 0x1908
d0010a0c:	6a626323 	bvs	0xd18a96a0
d0010a10:	d9074296 	stmdble	r7, {r1, r2, r4, r7, r9, lr}
d0010a14:	46287815 			; <UNDEFINED> instruction: 0x46287815
d0010a18:	fc8bf7ff 	stc2	7, cr15, [fp], {255}	; 0xff
d0010a1c:	3d30b980 			; <UNDEFINED> instruction: 0x3d30b980
d0010a20:	d90d2d09 	stmdble	sp, {r0, r3, r8, sl, fp, sp}
d0010a24:	68201a52 	stmdavs	r0!, {r1, r4, r6, r9, fp, ip}
d0010a28:	fc61f7ff 	stc2l	7, cr15, [r1], #-1020	; 0xfffffc04
d0010a2c:	17c12700 	strbne	r2, [r1, r0, lsl #14]
d0010a30:	0ff643ce 	svceq	0x00f643ce
d0010a34:	0f00f1b8 	svceq	0x0000f1b8
d0010a38:	4914d093 	ldmdbmi	r4, {r0, r1, r4, r7, ip, lr, pc}
d0010a3c:	e7574479 			; <UNDEFINED> instruction: 0xe7574479
d0010a40:	62623201 	rsbvs	r3, r2, #268435456	; 0x10000000
d0010a44:	4629e7e3 	strtmi	lr, [r9], -r3, ror #15
d0010a48:	f7ff6820 			; <UNDEFINED> instruction: 0xf7ff6820
d0010a4c:	2800fc50 	stmdacs	r0, {r4, r6, sl, fp, ip, sp, lr, pc}
d0010a50:	6823dbae 	stmdavs	r3!, {r1, r2, r3, r5, r7, r8, r9, fp, ip, lr, pc}
d0010a54:	fb022248 	blx	0xd009937e
d0010a58:	f5003000 			; <UNDEFINED> instruction: 0xf5003000
d0010a5c:	e9d0402b 	ldmib	r0, {r0, r1, r3, r5, lr}^
d0010a60:	e77e6732 			; <UNDEFINED> instruction: 0xe77e6732
d0010a64:	f47f2d00 			; <UNDEFINED> instruction: 0xf47f2d00
d0010a68:	e76faf7c 			; <UNDEFINED> instruction: 0xe76faf7c
d0010a6c:	ffffffc2 			; <UNDEFINED> instruction: 0xffffffc2
d0010a70:	ffffffa4 			; <UNDEFINED> instruction: 0xffffffa4
d0010a74:	ffffff88 			; <UNDEFINED> instruction: 0xffffff88
d0010a78:	ffffff72 			; <UNDEFINED> instruction: 0xffffff72
d0010a7c:	ffffff42 			; <UNDEFINED> instruction: 0xffffff42
d0010a80:	ffffff30 			; <UNDEFINED> instruction: 0xffffff30
d0010a84:	fffffe42 			; <UNDEFINED> instruction: 0xfffffe42
d0010a88:	fffffe30 			; <UNDEFINED> instruction: 0xfffffe30
d0010a8c:	fffffde2 			; <UNDEFINED> instruction: 0xfffffde2

Disassembly of section .text.pp_mul:

d0010a98 <.text.pp_mul>:
d0010a98:	4ff0e92d 	svcmi	0x00f0e92d
d0010a9c:	8b02ed2d 	blhi	0xd00cbf58
d0010aa0:	4606b089 	strmi	fp, [r6], -r9, lsl #1
d0010aa4:	fec2f7ff 	mcr2	7, 6, pc, cr2, cr15, {7}	; <UNPREDICTABLE>
d0010aa8:	46044b67 	strmi	r4, [r4], -r7, ror #22
d0010aac:	447b460d 	ldrbtmi	r4, [fp], #-1549	; 0xfffff9f3
d0010ab0:	3a10ee08 	bcc	0xd044c2d8
d0010ab4:	447b4b65 	ldrbtmi	r4, [fp], #-2917	; 0xfffff49b
d0010ab8:	3a90ee08 	bcc	0xce44c2e0
d0010abc:	1a10ee18 	bne	0xd044c324
d0010ac0:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0010ac4:	b178fbf9 	ldrshlt	pc, [r8, #-185]!	; 0xffffff47	; <UNPREDICTABLE>
d0010ac8:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0010acc:	4361feaf 	msrmi	SPSR_c, #2800	; 0xaf0
d0010ad0:	3400fba4 	strcc	pc, [r0], #-2980	; 0xfffff45c
d0010ad4:	1105fb00 	tstne	r5, r0, lsl #22	; <UNPREDICTABLE>
d0010ad8:	3400e9cd 	strcc	lr, [r0], #-2509	; 0xfffff633
d0010adc:	440b9b01 	strmi	r9, [fp], #-2817	; 0xfffff4ff
d0010ae0:	e9dd9301 	ldmib	sp, {r0, r8, r9, ip, pc}^
d0010ae4:	e7e94500 	strb	r4, [r9, r0, lsl #10]!
d0010ae8:	1a90ee18 	bne	0xce44c350
d0010aec:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0010af0:	9006fbe3 	andls	pc, r6, r3, ror #23
d0010af4:	4956b938 	ldmdbmi	r6, {r3, r4, r5, r8, fp, ip, sp, pc}^
d0010af8:	44794630 	ldrbtmi	r4, [r9], #-1584	; 0xfffff9d0
d0010afc:	fbdcf7ff 	blx	0xcf74eb02
d0010b00:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d0010b04:	46308099 			; <UNDEFINED> instruction: 0x46308099
d0010b08:	fe90f7ff 	mrc2	7, 4, pc, cr0, cr15, {7}
d0010b0c:	0100e9cd 	smlabteq	r0, sp, r9, lr
d0010b10:	2300e9dd 	movwcs	lr, #2525	; 0x9dd
d0010b14:	d1094313 	tstle	r9, r3, lsl r3
d0010b18:	29006b71 	stmdbcs	r0, {r0, r4, r5, r6, r8, r9, fp, sp, lr}
d0010b1c:	2301d0e1 	movwcs	sp, #4321	; 0x10e1
d0010b20:	63332400 	teqvs	r3, #0, 8
d0010b24:	e9cd2300 	stmib	sp, {r8, r9, sp}^
d0010b28:	e7da3400 	ldrb	r3, [sl, r0, lsl #8]
d0010b2c:	f1752c00 			; <UNDEFINED> instruction: 0xf1752c00
d0010b30:	e9cd0300 	stmib	sp, {r8, r9}^
d0010b34:	da044502 	ble	0xd0121f44
d0010b38:	eb654262 	bl	0xd19614c8
d0010b3c:	e9cd0345 	stmib	sp, {r0, r2, r6, r8, r9}^
d0010b40:	e9dd2302 	ldmib	sp, {r1, r8, r9, sp}^
d0010b44:	2a002300 	bcs	0xd001974c
d0010b48:	2304e9cd 	movwcs	lr, #18893	; 0x49cd
d0010b4c:	0300f173 	movweq	pc, #371	; 0x173	; <UNPREDICTABLE>
d0010b50:	e9ddda06 	ldmib	sp, {r1, r2, r9, fp, ip, lr, pc}^
d0010b54:	42522300 	subsmi	r2, r2, #0, 6
d0010b58:	0343eb63 	movteq	lr, #15203	; 0x3b63
d0010b5c:	2304e9cd 	movwcs	lr, #18893	; 0x49cd
d0010b60:	0a00f04f 	beq	0xd004cca4
d0010b64:	0b00f04f 	bleq	0xd004cca8
d0010b68:	f04f213f 			; <UNDEFINED> instruction: 0xf04f213f
d0010b6c:	46570c01 	ldrbmi	r0, [r7], -r1, lsl #24
d0010b70:	eb1a46d8 	bl	0xd06a26d8
d0010b74:	f1c1030a 			; <UNDEFINED> instruction: 0xf1c1030a
d0010b78:	f1a10920 			; <UNDEFINED> instruction: 0xf1a10920
d0010b7c:	461a0e20 	ldrmi	r0, [sl], -r0, lsr #28
d0010b80:	030beb4b 	movweq	lr, #47947	; 0xbb4b
d0010b84:	9b029307 	blls	0xd00b57a8
d0010b88:	b01cf8dd 			; <UNDEFINED> instruction: 0xb01cf8dd
d0010b8c:	f001fa23 			; <UNDEFINED> instruction: 0xf001fa23
d0010b90:	fa039b03 	blx	0xd00f77a4
d0010b94:	fa23f909 	blx	0xd090efc0
d0010b98:	ea40fe0e 	b	0xd10503d8
d0010b9c:	ea400009 	b	0xd1010bc8
d0010ba0:	f1a1000e 			; <UNDEFINED> instruction: 0xf1a1000e
d0010ba4:	f0000e20 			; <UNDEFINED> instruction: 0xf0000e20
d0010ba8:	ea400001 	b	0xd1010bb4
d0010bac:	f1c10a02 			; <UNDEFINED> instruction: 0xf1c10a02
d0010bb0:	e9dd0020 	ldmib	sp, {r5}^
d0010bb4:	459b2304 	ldrmi	r2, [fp, #772]	; 0x304
d0010bb8:	4592bf08 	ldrmi	fp, [r2, #3848]	; 0xf08
d0010bbc:	fa0cd313 	blx	0xd0345810
d0010bc0:	fa2cfe0e 	blx	0xd0b50400
d0010bc4:	9b04f000 	blls	0xd014cbcc
d0010bc8:	0000ea4e 	andeq	lr, r0, lr, asr #20
d0010bcc:	fe01fa0c 	vseleq.f32	s30, s2, s24
d0010bd0:	0a03ebba 	beq	0xd010bac0
d0010bd4:	ea4e9b05 	b	0xd13b77f0
d0010bd8:	ea400e07 	b	0xd10143fc
d0010bdc:	eb6b0008 	bl	0xd1ad0c04
d0010be0:	46770b03 	ldrbtmi	r0, [r7], -r3, lsl #22
d0010be4:	39014680 	stmdbcc	r1, {r7, r9, sl, lr}
d0010be8:	9b06d2c3 	blls	0xd01c56fc
d0010bec:	9b01b1c3 	blls	0xd007d300
d0010bf0:	0fdb0fea 	svceq	0x00db0fea
d0010bf4:	7fd5ebb3 	svcvc	0x00d5ebb3
d0010bf8:	f04fbf15 			; <UNDEFINED> instruction: 0xf04fbf15
d0010bfc:	f06f4100 			; <UNDEFINED> instruction: 0xf06f4100
d0010c00:	20004100 	andcs	r4, r0, r0, lsl #2
d0010c04:	30fff04f 	rscscc	pc, pc, pc, asr #32
d0010c08:	bf084541 	svclt	0x00084541
d0010c0c:	d38642b8 	orrle	r4, r6, #184, 4	; 0x8000000b
d0010c10:	d002429a 	mulle	r2, sl, r2
d0010c14:	eb68427f 	bl	0xd1a21618
d0010c18:	e9cd0848 	stmib	sp, {r3, r6, fp}^
d0010c1c:	e7607800 	strb	r7, [r0, -r0, lsl #16]!
d0010c20:	f1752c00 			; <UNDEFINED> instruction: 0xf1752c00
d0010c24:	e9cd0300 	stmib	sp, {r8, r9}^
d0010c28:	f6bfab00 			; <UNDEFINED> instruction: 0xf6bfab00
d0010c2c:	f1daaf5a 			; <UNDEFINED> instruction: 0xf1daaf5a
d0010c30:	eb6b0300 	bl	0xd1ad1838
d0010c34:	e776044b 	ldrb	r0, [r6, -fp, asr #8]!
d0010c38:	46294620 	strtmi	r4, [r9], -r0, lsr #12
d0010c3c:	ecbdb009 	ldc	0, cr11, [sp], #36	; 0x24
d0010c40:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d0010c44:	bf008ff0 	svclt	0x00008ff0
d0010c48:	ffffffde 			; <UNDEFINED> instruction: 0xffffffde
d0010c4c:	ffffffd8 			; <UNDEFINED> instruction: 0xffffffd8
d0010c50:	ffffff96 			; <UNDEFINED> instruction: 0xffffff96

Disassembly of section .text.pp_add:

d0010c54 <.text.pp_add>:
d0010c54:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d0010c58:	46064f12 			; <UNDEFINED> instruction: 0x46064f12
d0010c5c:	8048f8df 	ldrdhi	pc, [r8], #-143	; 0xffffff71
d0010c60:	ff1af7ff 			; <UNDEFINED> instruction: 0xff1af7ff
d0010c64:	4604447f 			; <UNDEFINED> instruction: 0x4604447f
d0010c68:	44f8460d 	ldrbtmi	r4, [r8], #1549	; 0x60d
d0010c6c:	46304639 			; <UNDEFINED> instruction: 0x46304639
d0010c70:	fb22f7ff 	blx	0xd08cec76
d0010c74:	4630b130 			; <UNDEFINED> instruction: 0x4630b130
d0010c78:	ff0ef7ff 			; <UNDEFINED> instruction: 0xff0ef7ff
d0010c7c:	eb411824 	bl	0xd1056d14
d0010c80:	e7f30505 	ldrb	r0, [r3, r5, lsl #10]!
d0010c84:	46304641 	ldrtmi	r4, [r0], -r1, asr #12
d0010c88:	fb16f7ff 	blx	0xd05cec8e
d0010c8c:	4630b130 			; <UNDEFINED> instruction: 0x4630b130
d0010c90:	ff02f7ff 			; <UNDEFINED> instruction: 0xff02f7ff
d0010c94:	eb651a24 	bl	0xd195752c
d0010c98:	e7e70501 	strb	r0, [r7, r1, lsl #10]!
d0010c9c:	46294620 	strtmi	r4, [r9], -r0, lsr #12
d0010ca0:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d0010ca4:	fffffbb4 			; <UNDEFINED> instruction: 0xfffffbb4
d0010ca8:	fffffbb0 			; <UNDEFINED> instruction: 0xfffffbb0

Disassembly of section .text.pp_shift:

d0010cb4 <.text.pp_shift>:
d0010cb4:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d0010cb8:	805cf8df 	ldrsbhi	pc, [ip], #-143	; 0xffffff71	; <UNPREDICTABLE>
d0010cbc:	f8df4604 			; <UNDEFINED> instruction: 0xf8df4604
d0010cc0:	f7ff905c 			; <UNDEFINED> instruction: 0xf7ff905c
d0010cc4:	44f8ffc7 	ldrbtmi	pc, [r8], #4039	; 0xfc7	; <UNPREDICTABLE>
d0010cc8:	460e4605 	strmi	r4, [lr], -r5, lsl #12
d0010ccc:	464144f9 			; <UNDEFINED> instruction: 0x464144f9
d0010cd0:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010cd4:	b160faf1 	strdlt	pc, [r0, #-161]!	; 0xffffff5f
d0010cd8:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010cdc:	2900ffbb 	stmdbcs	r0, {r0, r1, r3, r4, r5, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0010ce0:	2820bf08 	stmdacs	r0!, {r3, r8, r9, sl, fp, ip, sp, pc}
d0010ce4:	2301d302 	movwcs	sp, #4866	; 0x1302
d0010ce8:	e7f06323 	ldrb	r6, [r0, r3, lsr #6]!
d0010cec:	26004085 	strcs	r4, [r0], -r5, lsl #1
d0010cf0:	4649e7ed 	strbmi	lr, [r9], -sp, ror #15
d0010cf4:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010cf8:	b140fadf 	ldrdlt	pc, [r0, #-175]	; 0xffffff51
d0010cfc:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010d00:	2900ffa9 	stmdbcs	r0, {r0, r3, r5, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0010d04:	2820bf08 	stmdacs	r0!, {r3, r8, r9, sl, fp, ip, sp, pc}
d0010d08:	40c5d2ed 	sbcmi	sp, r5, sp, ror #5
d0010d0c:	4628e7ef 	strtmi	lr, [r8], -pc, ror #15
d0010d10:	e8bd4631 	pop	{r0, r4, r5, r9, sl, lr}
d0010d14:	bf0083f8 	svclt	0x000083f8
d0010d18:	ffffffe2 			; <UNDEFINED> instruction: 0xffffffe2
d0010d1c:	ffffffdf 			; <UNDEFINED> instruction: 0xffffffdf

Disassembly of section .text.pp_rel:

d0010d2c <.text.pp_rel>:
d0010d2c:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d0010d30:	46064f24 	strmi	r4, [r6], -r4, lsr #30
d0010d34:	8090f8df 			; <UNDEFINED> instruction: 0x8090f8df
d0010d38:	ffbcf7ff 			; <UNDEFINED> instruction: 0xffbcf7ff
d0010d3c:	908cf8df 	ldrdls	pc, [ip], pc	; <UNPREDICTABLE>
d0010d40:	460d4604 	strmi	r4, [sp], -r4, lsl #12
d0010d44:	44f8447f 	ldrbtmi	r4, [r8], #1151	; 0x47f
d0010d48:	463944f9 			; <UNDEFINED> instruction: 0x463944f9
d0010d4c:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0010d50:	b158fab3 	ldrhlt	pc, [r8, #-163]	; 0xffffff5d	; <UNPREDICTABLE>
d0010d54:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0010d58:	42a0ffad 	adcmi	pc, r0, #692	; 0x2b4
d0010d5c:	0305eb71 	movweq	lr, #23409	; 0x5b71
d0010d60:	2401bfac 	strcs	fp, [r1], #-4012	; 0xfffff054
d0010d64:	b2e42400 	rsclt	r2, r4, #0, 8
d0010d68:	e7ee2500 	strb	r2, [lr, r0, lsl #10]!
d0010d6c:	46304641 	ldrtmi	r4, [r0], -r1, asr #12
d0010d70:	faa2f7ff 	blx	0xce8ced74
d0010d74:	4630b130 			; <UNDEFINED> instruction: 0x4630b130
d0010d78:	ff9cf7ff 			; <UNDEFINED> instruction: 0xff9cf7ff
d0010d7c:	eb754284 	bl	0xd1d61794
d0010d80:	e7ed0301 	strb	r0, [sp, r1, lsl #6]!
d0010d84:	46304649 	ldrtmi	r4, [r0], -r9, asr #12
d0010d88:	fa96f7ff 	blx	0xce5ced8c
d0010d8c:	4630b148 	ldrtmi	fp, [r0], -r8, asr #2
d0010d90:	ff90f7ff 			; <UNDEFINED> instruction: 0xff90f7ff
d0010d94:	eb754284 	bl	0xd1d617ac
d0010d98:	bfb40301 	svclt	0x00b40301
d0010d9c:	24002401 	strcs	r2, [r0], #-1025	; 0xfffffbff
d0010da0:	490be7e1 	stmdbmi	fp, {r0, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d0010da4:	44794630 	ldrbtmi	r4, [r9], #-1584	; 0xfffff9d0
d0010da8:	fa86f7ff 	blx	0xce1cedac
d0010dac:	4630b130 			; <UNDEFINED> instruction: 0x4630b130
d0010db0:	ff80f7ff 			; <UNDEFINED> instruction: 0xff80f7ff
d0010db4:	eb7142a0 	bl	0xd1c6183c
d0010db8:	e7ee0305 	strb	r0, [lr, r5, lsl #6]!
d0010dbc:	46294620 	strtmi	r4, [r9], -r0, lsr #12
d0010dc0:	83f8e8bd 	mvnshi	lr, #12386304	; 0xbd0000
d0010dc4:	ffffffd8 			; <UNDEFINED> instruction: 0xffffffd8
d0010dc8:	ffffffd9 			; <UNDEFINED> instruction: 0xffffffd9
d0010dcc:	ffffffda 			; <UNDEFINED> instruction: 0xffffffda
d0010dd0:	ffffff7e 			; <UNDEFINED> instruction: 0xffffff7e

Disassembly of section .text.pp_eq:

d0010ddc <.text.pp_eq>:
d0010ddc:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d0010de0:	46064f15 			; <UNDEFINED> instruction: 0x46064f15
d0010de4:	8054f8df 	ldrsbhi	pc, [r4], #-143	; 0xffffff71	; <UNPREDICTABLE>
d0010de8:	ffa0f7ff 			; <UNDEFINED> instruction: 0xffa0f7ff
d0010dec:	4604447f 			; <UNDEFINED> instruction: 0x4604447f
d0010df0:	44f8460d 	ldrbtmi	r4, [r8], #1549	; 0x60d
d0010df4:	46304639 			; <UNDEFINED> instruction: 0x46304639
d0010df8:	fa5ef7ff 	blx	0xd17cedfc
d0010dfc:	4630b150 			; <UNDEFINED> instruction: 0x4630b150
d0010e00:	ff94f7ff 			; <UNDEFINED> instruction: 0xff94f7ff
d0010e04:	bf0642a9 	svclt	0x000642a9
d0010e08:	240142a0 	strcs	r4, [r1], #-672	; 0xfffffd60
d0010e0c:	b2e42400 	rsclt	r2, r4, #0, 8
d0010e10:	e7ef2500 	strb	r2, [pc, r0, lsl #10]!
d0010e14:	46304641 	ldrtmi	r4, [r0], -r1, asr #12
d0010e18:	fa4ef7ff 	blx	0xd13cee1c
d0010e1c:	4630b140 	ldrtmi	fp, [r0], -r0, asr #2
d0010e20:	ff84f7ff 			; <UNDEFINED> instruction: 0xff84f7ff
d0010e24:	bf0a42a9 	svclt	0x000a42a9
d0010e28:	240142a0 	strcs	r4, [r1], #-672	; 0xfffffd60
d0010e2c:	e7ee2400 	strb	r2, [lr, r0, lsl #8]!
d0010e30:	46294620 	strtmi	r4, [r9], -r0, lsr #12
d0010e34:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d0010e38:	ffffffe4 			; <UNDEFINED> instruction: 0xffffffe4
d0010e3c:	ffffffe1 			; <UNDEFINED> instruction: 0xffffffe1

Disassembly of section .text.pp_band:

d0010e40 <.text.pp_band>:
d0010e40:	4604b570 			; <UNDEFINED> instruction: 0x4604b570
d0010e44:	ffcaf7ff 			; <UNDEFINED> instruction: 0xffcaf7ff
d0010e48:	460d4606 	strmi	r4, [sp], -r6, lsl #12
d0010e4c:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010e50:	6a63fa13 	bvs	0xd190f6a4
d0010e54:	428b6aa1 	addmi	r6, fp, #659456	; 0xa1000
d0010e58:	781ad20f 	ldmdavc	sl, {r0, r1, r2, r3, r9, ip, lr, pc}
d0010e5c:	d10c2a26 	tstle	ip, r6, lsr #20
d0010e60:	42911c5a 	addsmi	r1, r1, #23040	; 0x5a00
d0010e64:	785bd902 	ldmdavc	fp, {r1, r8, fp, ip, lr, pc}^
d0010e68:	d0062b26 	andle	r2, r6, r6, lsr #22
d0010e6c:	62624620 	rsbvs	r4, r2, #32, 12	; 0x2000000
d0010e70:	ffb4f7ff 			; <UNDEFINED> instruction: 0xffb4f7ff
d0010e74:	400d4006 	andmi	r4, sp, r6
d0010e78:	4630e7e8 	ldrtmi	lr, [r0], -r8, ror #15
d0010e7c:	bd704629 	ldcllt	6, cr4, [r0, #-164]!	; 0xffffff5c

Disassembly of section .text.pp_xor:

d0010e84 <.text.pp_xor>:
d0010e84:	4f0ab5f8 	svcmi	0x000ab5f8
d0010e88:	f7ff4606 			; <UNDEFINED> instruction: 0xf7ff4606
d0010e8c:	4605ffd9 			; <UNDEFINED> instruction: 0x4605ffd9
d0010e90:	447f460c 	ldrbtmi	r4, [pc], #-1548	; 0xd0010e98
d0010e94:	46304639 			; <UNDEFINED> instruction: 0x46304639
d0010e98:	fa0ef7ff 	blx	0xd03cee9c
d0010e9c:	4628b910 			; <UNDEFINED> instruction: 0x4628b910
d0010ea0:	bdf84621 	ldcllt	6, cr4, [r8, #132]!	; 0x84
d0010ea4:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0010ea8:	4045ffcb 	submi	pc, r5, fp, asr #31
d0010eac:	e7f1404c 	ldrb	r4, [r1, ip, asr #32]!
d0010eb0:	ffffffea 			; <UNDEFINED> instruction: 0xffffffea

Disassembly of section .text.pp_bor:

d0010eb4 <.text.pp_bor>:
d0010eb4:	4604b570 			; <UNDEFINED> instruction: 0x4604b570
d0010eb8:	ffe4f7ff 			; <UNDEFINED> instruction: 0xffe4f7ff
d0010ebc:	460d4606 	strmi	r4, [sp], -r6, lsl #12
d0010ec0:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0010ec4:	6a63f9d9 	bvs	0xd190f630
d0010ec8:	428b6aa1 	addmi	r6, fp, #659456	; 0xa1000
d0010ecc:	781ad20f 	ldmdavc	sl, {r0, r1, r2, r3, r9, ip, lr, pc}
d0010ed0:	d10c2a7c 	tstle	ip, ip, ror sl
d0010ed4:	42911c5a 	addsmi	r1, r1, #23040	; 0x5a00
d0010ed8:	785bd902 	ldmdavc	fp, {r1, r8, fp, ip, lr, pc}^
d0010edc:	d0062b7c 	andle	r2, r6, ip, ror fp
d0010ee0:	62624620 	rsbvs	r4, r2, #32, 12	; 0x2000000
d0010ee4:	ffcef7ff 			; <UNDEFINED> instruction: 0xffcef7ff
d0010ee8:	430d4306 	movwmi	r4, #54022	; 0xd306
d0010eec:	4630e7e8 	ldrtmi	lr, [r0], -r8, ror #15
d0010ef0:	bd704629 	ldcllt	6, cr4, [r0, #-164]!	; 0xffffff5c

Disassembly of section .text.pp_and:

d0010ef8 <.text.pp_and>:
d0010ef8:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d0010efc:	46064f16 			; <UNDEFINED> instruction: 0x46064f16
d0010f00:	ffd8f7ff 			; <UNDEFINED> instruction: 0xffd8f7ff
d0010f04:	460d4604 	strmi	r4, [sp], -r4, lsl #12
d0010f08:	4639447f 			; <UNDEFINED> instruction: 0x4639447f
d0010f0c:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0010f10:	b918f9d3 	ldmdblt	r8, {r0, r1, r4, r6, r7, r8, fp, ip, sp, lr, pc}
d0010f14:	46294620 	strtmi	r4, [r9], -r0, lsr #12
d0010f18:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d0010f1c:	8034f8d6 	ldrsbthi	pc, [r4], -r6	; <UNPREDICTABLE>
d0010f20:	0f00f1b8 	svceq	0x0000f1b8
d0010f24:	ea54d014 	b	0xd1544f7c
d0010f28:	bf140305 	svclt	0x00140305
d0010f2c:	23002301 	movwcs	r2, #769	; 0x301
d0010f30:	46306373 			; <UNDEFINED> instruction: 0x46306373
d0010f34:	ffbef7ff 			; <UNDEFINED> instruction: 0xffbef7ff
d0010f38:	0305ea54 	movweq	lr, #23124	; 0x5a54
d0010f3c:	8034f8c6 	eorshi	pc, r4, r6, asr #17
d0010f40:	ea50d008 	b	0xd1444f68
d0010f44:	bf140301 	svclt	0x00140301
d0010f48:	24002401 	strcs	r2, [r0], #-1025	; 0xfffffbff
d0010f4c:	e7dc17e5 	ldrb	r1, [ip, r5, ror #15]
d0010f50:	e7ed4643 	strb	r4, [sp, r3, asr #12]!
d0010f54:	e7f92400 	ldrb	r2, [r9, r0, lsl #8]!
d0010f58:	ffffffe8 			; <UNDEFINED> instruction: 0xffffffe8

Disassembly of section .text.pp_or:

d0010f60 <.text.pp_or>:
d0010f60:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d0010f64:	46064f15 			; <UNDEFINED> instruction: 0x46064f15
d0010f68:	ffc6f7ff 			; <UNDEFINED> instruction: 0xffc6f7ff
d0010f6c:	460d4604 	strmi	r4, [sp], -r4, lsl #12
d0010f70:	4639447f 			; <UNDEFINED> instruction: 0x4639447f
d0010f74:	f7ff4630 			; <UNDEFINED> instruction: 0xf7ff4630
d0010f78:	b918f99f 	ldmdblt	r8, {r0, r1, r2, r3, r4, r7, r8, fp, ip, sp, lr, pc}
d0010f7c:	46294620 	strtmi	r4, [r9], -r0, lsr #12
d0010f80:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d0010f84:	8034f8d6 	ldrsbthi	pc, [r4], -r6	; <UNPREDICTABLE>
d0010f88:	0f00f1b8 	svceq	0x0000f1b8
d0010f8c:	ea54d014 	b	0xd1544fe4
d0010f90:	bf0c0305 	svclt	0x000c0305
d0010f94:	23002301 	movwcs	r2, #769	; 0x301
d0010f98:	46306373 			; <UNDEFINED> instruction: 0x46306373
d0010f9c:	ffacf7ff 			; <UNDEFINED> instruction: 0xffacf7ff
d0010fa0:	43294320 			; <UNDEFINED> instruction: 0x43294320
d0010fa4:	8034f8c6 	eorshi	pc, r4, r6, asr #17
d0010fa8:	ea502500 	b	0xd141a3b0
d0010fac:	bf140301 	svclt	0x00140301
d0010fb0:	24002401 	strcs	r2, [r0], #-1025	; 0xfffffbff
d0010fb4:	e7dcb2e4 	ldrb	fp, [ip, r4, ror #5]
d0010fb8:	e7ed4643 	strb	r4, [sp, r3, asr #12]!
d0010fbc:	ffffffe8 			; <UNDEFINED> instruction: 0xffffffe8

Disassembly of section .text.pp_value:

d0010ff0 <.text.pp_value>:
d0010ff0:	b5f0b084 	ldrblt	fp, [r0, #132]!	; 0x84
d0010ff4:	4606b08f 	strmi	fp, [r6], -pc, lsl #1
d0010ff8:	9000ac15 	andls	sl, r0, r5, lsl ip
d0010ffc:	9f1ead01 	svcls	0x001ead01
d0011000:	000ee884 	andeq	lr, lr, r4, lsl #17
d0011004:	c50fcc0f 	strgt	ip, [pc, #-3087]	; 0xd00103fd
d0011008:	000fe894 	muleq	pc, r4, r8	; <UNPREDICTABLE>
d001100c:	000fe885 	andeq	lr, pc, r5, lsl #17
d0011010:	466d9b1d 			; <UNDEFINED> instruction: 0x466d9b1d
d0011014:	970a2401 	strls	r2, [sl, -r1, lsl #8]
d0011018:	23009309 	movwcs	r9, #777	; 0x309
d001101c:	940d4628 	strls	r4, [sp], #-1576	; 0xfffff9d8
d0011020:	930c930b 	movwls	r9, #49931	; 0xc30b
d0011024:	ff9cf7ff 			; <UNDEFINED> instruction: 0xff9cf7ff
d0011028:	e9c39b1f 	stmib	r3, {r0, r1, r2, r3, r4, r8, r9, fp, ip, pc}^
d001102c:	46280100 	strtmi	r0, [r8], -r0, lsl #2
d0011030:	f922f7ff 			; <UNDEFINED> instruction: 0xf922f7ff
d0011034:	b9139b0c 	ldmdblt	r3, {r2, r3, r8, r9, fp, ip, pc}
d0011038:	42bb9b09 	adcsmi	r9, fp, #9216	; 0x2400
d001103c:	6db0d012 	ldcvs	0, cr13, [r0, #72]!	; 0x48
d0011040:	490ab990 	stmdbmi	sl, {r4, r7, r8, fp, ip, sp, pc}
d0011044:	206cf89d 	mlscs	ip, sp, r8, pc	; <UNPREDICTABLE>
d0011048:	65b14479 	ldrvs	r4, [r1, #1145]!	; 0x479
d001104c:	65f19918 	ldrbvs	r9, [r1, #2328]!	; 0x918
d0011050:	e9c69919 	stmib	r6, {r0, r3, r4, r8, fp, ip, pc}^
d0011054:	9a1c1218 	bls	0xd07158bc
d0011058:	b00f66b2 			; <UNDEFINED> instruction: 0xb00f66b2
d001105c:	40f0e8bd 	ldrhtmi	lr, [r0], #141	; 0x8d
d0011060:	4770b004 	ldrbmi	fp, [r0, -r4]!
d0011064:	e7f84620 	ldrb	r4, [r8, r0, lsr #12]!
d0011068:	e7f62000 	ldrb	r2, [r6, r0]!
d001106c:	ffffff74 			; <UNDEFINED> instruction: 0xffffff74

Disassembly of section .text.enter_header.isra.0:

d0011210 <.text.enter_header.isra.0>:
d0011210:	4ff0e92d 	svcmi	0x00f0e92d
d0011214:	f5ad461e 			; <UNDEFINED> instruction: 0xf5ad461e
d0011218:	6ec37d0d 	cdpvs	13, 12, cr7, cr3, cr13, {0}
d001121c:	9d984604 	ldcls	6, cr4, [r8, #16]
d0011220:	92059104 	andls	r9, r5, #4, 2
d0011224:	6d85b993 	vstrvs.16	s22, [r5, #294]	; 0x126	; <UNPREDICTABLE>
d0011228:	2500b12d 	strcs	fp, [r0, #-301]	; 0xfffffed3
d001122c:	f50d4628 			; <UNDEFINED> instruction: 0xf50d4628
d0011230:	e8bd7d0d 	pop	{r0, r2, r3, r8, sl, fp, ip, sp, lr}
d0011234:	4bfa8ff0 	blmi	0xcfeb51fc
d0011238:	65a3447b 	strvs	r4, [r3, #1147]!	; 0x47b
d001123c:	65e39b04 	strbvs	r9, [r3, #2820]!	; 0xb04
d0011240:	e9c49b05 	stmib	r4, {r0, r2, r8, r9, fp, ip, pc}^
d0011244:	9b963618 	blls	0xce59eaac
d0011248:	e7ef66a3 	strb	r6, [pc, r3, lsr #13]!
d001124c:	2bfe1e6b 	blcs	0xcff98c00
d0011250:	6d85d905 	vstrvs.16	s26, [r5, #10]	; <UNPREDICTABLE>
d0011254:	d1e82d00 	mvnle	r2, r0, lsl #26
d0011258:	447b4bf2 	ldrbtmi	r4, [fp], #-3058	; 0xfffff40e
d001125c:	f10de7ed 			; <UNDEFINED> instruction: 0xf10de7ed
d0011260:	462a0930 			; <UNDEFINED> instruction: 0x462a0930
d0011264:	46489997 			; <UNDEFINED> instruction: 0x46489997
d0011268:	f908f00b 			; <UNDEFINED> instruction: 0xf908f00b
d001126c:	46482300 	strbmi	r2, [r8], -r0, lsl #6
d0011270:	3005f809 	andcc	pc, r5, r9, lsl #16
d0011274:	fd0af00c 	stc2	0, cr15, [sl, #-48]	; 0xffffffd0
d0011278:	d8052802 	stmdale	r5, {r1, fp, sp}
d001127c:	2d006da5 	stccs	13, cr6, [r0, #-660]	; 0xfffffd6c
d0011280:	4be9d1d3 	blmi	0xcfa859d4
d0011284:	e7d8447b 			; <UNDEFINED> instruction: 0xe7d8447b
d0011288:	49e83802 	stmibmi	r8!, {r1, fp, ip, sp}^
d001128c:	44794448 	ldrbtmi	r4, [r9], #-1096	; 0xfffffbb8
d0011290:	fd08f00c 	stc2	0, cr15, [r8, #-48]	; 0xffffffd0
d0011294:	28004605 	stmdacs	r0, {r0, r2, r9, sl, lr}
d0011298:	ab0bd1f0 	blge	0xd0305a60
d001129c:	7280f44f 	addvc	pc, r0, #1325400064	; 0x4f000000
d00112a0:	7b98f50d 	blvc	0xce64e6dc
d00112a4:	9202900b 	andls	r9, r2, #11
d00112a8:	46024649 	strmi	r4, [r2], -r9, asr #12
d00112ac:	e9cd6ee7 	stmib	sp, {r0, r1, r2, r5, r6, r7, r9, sl, fp, sp, lr}^
d00112b0:	46033b00 	strmi	r3, [r3], -r0, lsl #22
d00112b4:	47b86f60 	ldrmi	r6, [r8, r0, ror #30]!
d00112b8:	f504b1e8 			; <UNDEFINED> instruction: 0xf504b1e8
d00112bc:	46a87700 	strtmi	r7, [r8], r0, lsl #14
d00112c0:	5a2ef504 	bpl	0xd0bce6d8
d00112c4:	3000f8da 	ldrdcc	pc, [r0], -sl
d00112c8:	d2064598 	andle	r4, r6, #152, 10	; 0x26000000
d00112cc:	46594638 			; <UNDEFINED> instruction: 0x46594638
d00112d0:	77a6f507 	strvc	pc, [r6, r7, lsl #10]!
d00112d4:	fce6f00c 	stc2l	0, cr15, [r6], #48	; 0x30
d00112d8:	f8dab998 			; <UNDEFINED> instruction: 0xf8dab998
d00112dc:	45983000 	ldrmi	r3, [r8]
d00112e0:	8103f040 	tsthi	r3, r0, asr #32	; <UNPREDICTABLE>
d00112e4:	0f20f1b8 	svceq	0x0020f1b8
d00112e8:	6da3d10e 	stfvsd	f5, [r3, #56]!	; 0x38
d00112ec:	d19c2b00 	orrsle	r2, ip, r0, lsl #22
d00112f0:	447b4bcf 	ldrbtmi	r4, [fp], #-3023	; 0xfffff431
d00112f4:	6da3e7a1 	stcvs	7, cr14, [r3, #644]!	; 0x284
d00112f8:	d1962b00 	orrsle	r2, r6, r0, lsl #22
d00112fc:	447b4bcd 	ldrbtmi	r4, [fp], #-3021	; 0xfffff433
d0011300:	f108e79b 			; <UNDEFINED> instruction: 0xf108e79b
d0011304:	e7dd0801 	ldrb	r0, [sp, r1, lsl #16]
d0011308:	3384f642 	orrcc	pc, r4, #69206016	; 0x4200000
d001130c:	f5d258e2 			; <UNDEFINED> instruction: 0xf5d258e2
d0011310:	d1054300 	mrsle	r4, SP_abt
d0011314:	2b006da3 	blcs	0xd002c9a8
d0011318:	4bc7d187 	blmi	0xcf20593c
d001131c:	e78c447b 			; <UNDEFINED> instruction: 0xe78c447b
d0011320:	512ef504 	msrpl	CPSR_fsx, r4, lsl #10
d0011324:	7b98f50d 	blvc	0xce64e760
d0011328:	31086f60 	tstcc	r8, r0, ror #30
d001132c:	f8cd6ee7 			; <UNDEFINED> instruction: 0xf8cd6ee7
d0011330:	9106b004 	tstls	r6, r4
d0011334:	7180f44f 	orrvc	pc, r0, pc, asr #8
d0011338:	91029307 	tstls	r2, r7, lsl #6
d001133c:	9109a90b 	tstls	r9, fp, lsl #18
d0011340:	99069100 	stmdbls	r6, {r8, ip, pc}
d0011344:	4649440a 	strbmi	r4, [r9], -sl, lsl #8
d0011348:	9b0747b8 	blls	0xd01e3230
d001134c:	6da5b930 			; <UNDEFINED> instruction: 0x6da5b930
d0011350:	f47f2d00 			; <UNDEFINED> instruction: 0xf47f2d00
d0011354:	4bb9af6a 	blmi	0xcee7d104
d0011358:	e76e447b 			; <UNDEFINED> instruction: 0xe76e447b
d001135c:	68129a09 	ldmdavs	r2, {r0, r3, r9, fp, ip, pc}
d0011360:	d2064293 	andle	r4, r6, #805306377	; 0x30000009
d0011364:	2b006da3 	blcs	0xd002c9f8
d0011368:	af5ff47f 	svcge	0x005ff47f
d001136c:	447b4bb4 	ldrbtmi	r4, [fp], #-2996	; 0xfffff44c
d0011370:	f642e763 			; <UNDEFINED> instruction: 0xf642e763
d0011374:	21003384 	smlabbcs	r0, r4, r3, r3
d0011378:	9b0658e0 	blls	0xd01a7700
d001137c:	f00c4418 			; <UNDEFINED> instruction: 0xf00c4418
d0011380:	4681fc6f 	strmi	pc, [r1], pc, ror #24
d0011384:	d1ed2800 	mvnle	r2, r0, lsl #16
d0011388:	3000f8da 	ldrdcc	pc, [r0], -sl
d001138c:	70a6f44f 	adcvc	pc, r6, pc, asr #8
d0011390:	33019307 	movwcc	r9, #4871	; 0x1307
d0011394:	3000f8ca 	andcc	pc, r0, sl, asr #17
d0011398:	43439b07 	movtmi	r9, #15111	; 0x3b07
d001139c:	93084658 	movwls	r4, #34392	; 0x8658
d00113a0:	7300f503 	movwvc	pc, #1283	; 0x503	; <UNPREDICTABLE>
d00113a4:	0a03eb04 	beq	0xd010bfbc
d00113a8:	fc70f00c 	ldc2l	0, cr15, [r0], #-48	; 0xffffffd0
d00113ac:	1c424659 	mcrrne	6, 5, r4, r2, cr9
d00113b0:	f00b4650 			; <UNDEFINED> instruction: 0xf00b4650
d00113b4:	f642f863 			; <UNDEFINED> instruction: 0xf642f863
d00113b8:	9b083284 	blls	0xd021ddd0
d00113bc:	9a0958a1 	bls	0xd0267648
d00113c0:	681218e3 	ldmdavs	r2, {r0, r1, r5, r6, r7, fp, ip}
d00113c4:	1300f8c3 	movwne	pc, #2243	; 0x8c3	; <UNPREDICTABLE>
d00113c8:	2304f8c3 	movwcs	pc, #18627	; 0x48c3	; <UNPREDICTABLE>
d00113cc:	9308f8c3 	movwls	pc, #35011	; 0x88c3	; <UNPREDICTABLE>
d00113d0:	440b9b06 	strmi	r9, [fp], #-2822	; 0xfffff4fa
d00113d4:	0902eb03 	stmdbeq	r2, {r0, r1, r8, r9, fp, sp, lr, pc}
d00113d8:	4a90469a 	bmi	0xce422e48
d00113dc:	d90945d1 	stmdble	r9, {r0, r4, r6, r7, r8, sl, lr}
d00113e0:	3000f89a 	mulcc	r0, sl, r8
d00113e4:	b2db3b09 	sbcslt	r3, fp, #9216	; 0x2400
d00113e8:	d8032b17 	stmdale	r3, {r0, r1, r2, r4, r8, r9, fp, sp}
d00113ec:	f303fa22 	vpmax.u8	d15, d3, d18
d00113f0:	d41607db 	ldrle	r0, [r6], #-2011	; 0xfffff825
d00113f4:	030aeba9 	movweq	lr, #43945	; 0xaba9
d00113f8:	dd292b01 	fstmdbxle	r9!, {d2-d1}	;@ Deprecated
d00113fc:	3000f89a 	mulcc	r0, sl, r8
d0011400:	d1252b2f 			; <UNDEFINED> instruction: 0xd1252b2f
d0011404:	3001f89a 	mulcc	r1, sl, r8
d0011408:	d10d2b2f 	tstle	sp, pc, lsr #22
d001140c:	0302f10a 	movweq	pc, #8458	; 0x210a	; <UNPREDICTABLE>
d0011410:	469a4599 			; <UNDEFINED> instruction: 0x469a4599
d0011414:	f89ad9ee 			; <UNDEFINED> instruction: 0xf89ad9ee
d0011418:	33011000 	movwcc	r1, #4096	; 0x1000
d001141c:	d1f7290a 	mvnsle	r2, sl, lsl #18
d0011420:	f10ae7dc 			; <UNDEFINED> instruction: 0xf10ae7dc
d0011424:	e7d90a01 	ldrb	r0, [r9, r1, lsl #20]
d0011428:	d1112b2a 	tstle	r1, sl, lsr #22
d001142c:	0a02f10a 	beq	0xd00cd85c
d0011430:	0301f10a 	movweq	pc, #4362	; 0x110a	; <UNPREDICTABLE>
d0011434:	d90b4599 	stmdble	fp, {r0, r3, r4, r7, r8, sl, lr}
d0011438:	1c01f813 	stcne	8, cr15, [r1], {19}
d001143c:	d105292a 	tstle	r5, sl, lsr #18
d0011440:	292f7819 	stmdbcs	pc!, {r0, r3, r4, fp, ip, sp, lr}	; <UNPREDICTABLE>
d0011444:	f10ad102 			; <UNDEFINED> instruction: 0xf10ad102
d0011448:	e7c70a02 	strb	r0, [r7, r2, lsl #20]
d001144c:	e7ef469a 			; <UNDEFINED> instruction: 0xe7ef469a
d0011450:	030aeba9 	movweq	lr, #43945	; 0xaba9
d0011454:	dd422b06 	vstrle	d18, [r2, #-24]	; 0xffffffe8
d0011458:	2207497a 	andcs	r4, r7, #1998848	; 0x1e8000
d001145c:	44794650 	ldrbtmi	r4, [r9], #-1616	; 0xfffff9b0
d0011460:	f81cf00b 			; <UNDEFINED> instruction: 0xf81cf00b
d0011464:	f10abbd8 			; <UNDEFINED> instruction: 0xf10abbd8
d0011468:	45b90707 	ldrmi	r0, [r9, #1799]!	; 0x707
d001146c:	f89ad005 			; <UNDEFINED> instruction: 0xf89ad005
d0011470:	2b203007 	blcs	0xd081d494
d0011474:	2b09d001 	blcs	0xd0285480
d0011478:	45b9d131 	ldrmi	sp, [r9, #305]!	; 0x131
d001147c:	d9474639 	stmdble	r7, {r0, r3, r4, r5, r9, sl, lr}^
d0011480:	f813463b 			; <UNDEFINED> instruction: 0xf813463b
d0011484:	2a202b01 	bcs	0xd081c090
d0011488:	2a09d040 	bcs	0xd0285590
d001148c:	463ad03e 			; <UNDEFINED> instruction: 0x463ad03e
d0011490:	f8923701 			; <UNDEFINED> instruction: 0xf8923701
d0011494:	4650a000 	ldrbmi	sl, [r0], -r0
d0011498:	ff4bf7fe 			; <UNDEFINED> instruction: 0xff4bf7fe
d001149c:	f1aab920 			; <UNDEFINED> instruction: 0xf1aab920
d00114a0:	f1ba0a30 			; <UNDEFINED> instruction: 0xf1ba0a30
d00114a4:	d8020f09 	stmdale	r2, {r0, r3, r8, r9, sl, fp}
d00114a8:	463a45b9 			; <UNDEFINED> instruction: 0x463a45b9
d00114ac:	1a57d8ef 	bne	0xd1607870
d00114b0:	7808d015 	stmdavc	r8, {r0, r2, r4, ip, lr, pc}
d00114b4:	ff3df7fe 			; <UNDEFINED> instruction: 0xff3df7fe
d00114b8:	2f3fb188 	svccs	0x003fb188
d00114bc:	9b08d80f 	blls	0xd0247500
d00114c0:	f203463a 	vmin.s8	d4, d3, d26
d00114c4:	4420300b 	strtmi	r3, [r0], #-11
d00114c8:	ffd8f00a 			; <UNDEFINED> instruction: 0xffd8f00a
d00114cc:	f44f9b07 			; <UNDEFINED> instruction: 0xf44f9b07
d00114d0:	fb0272a6 	blx	0xd00adf72
d00114d4:	23004203 	movwcs	r4, #515	; 0x203
d00114d8:	f882443a 			; <UNDEFINED> instruction: 0xf882443a
d00114dc:	f642330b 			; <UNDEFINED> instruction: 0xf642330b
d00114e0:	990b3284 	stmdbls	fp, {r2, r7, r9, ip, sp}
d00114e4:	440b58a3 	strmi	r5, [fp], #-2211	; 0xfffff75d
d00114e8:	7a2350a3 	bvc	0xd08e577c
d00114ec:	409f2701 	addsmi	r2, pc, r1, lsl #14
d00114f0:	73a6f44f 			; <UNDEFINED> instruction: 0x73a6f44f
d00114f4:	4308fb03 	movwmi	pc, #35587	; 0x8b03	; <UNPREDICTABLE>
d00114f8:	f893b2bf 			; <UNDEFINED> instruction: 0xf893b2bf
d00114fc:	b14a230a 	cmplt	sl, sl, lsl #6
d0011500:	3308f8b3 	movwcc	pc, #34995	; 0x88b3	; <UNPREDICTABLE>
d0011504:	d005421f 	andle	r4, r5, pc, lsl r2
d0011508:	e68f2501 	str	r2, [pc], r1, lsl #10
d001150c:	e7b4461f 			; <UNDEFINED> instruction: 0xe7b4461f
d0011510:	e7cc463a 			; <UNDEFINED> instruction: 0xe7cc463a
d0011514:	31fcf8d4 	ldrsbcc	pc, [ip, #132]!	; 0x84	; <UNPREDICTABLE>
d0011518:	d1062b0c 	tstle	r6, ip, lsl #22
d001151c:	2b006da3 	blcs	0xd002cbb0
d0011520:	ae83f47f 	mcrge	4, 4, pc, cr3, cr15, {3}	; <UNPREDICTABLE>
d0011524:	447b4b48 	ldrbtmi	r4, [fp], #-2888	; 0xfffff4b8
d0011528:	f44fe687 	vst1.32	{d30-d32}, [pc], r7
d001152c:	fb0171a6 	blx	0xd006dbce
d0011530:	1863f108 	stmdane	r3!, {r3, r8, ip, sp, lr, pc}^
d0011534:	330bf893 	movwcc	pc, #47251	; 0xb893	; <UNPREDICTABLE>
d0011538:	6fa1b94b 	svcvs	0x00a1b94b
d001153c:	d1234541 			; <UNDEFINED> instruction: 0xd1234541
d0011540:	2b006da3 	blcs	0xd002cbd4
d0011544:	ae71f47f 	mrcge	4, 3, APSR_nzcv, cr1, cr15, {3}
d0011548:	447b4b40 	ldrbtmi	r4, [fp], #-2880	; 0xfffff4c0
d001154c:	f201e675 	vmin.s8	q7, <illegal reg q0.5>, <illegal reg q10.5>
d0011550:	f504310b 			; <UNDEFINED> instruction: 0xf504310b
d0011554:	f504492b 			; <UNDEFINED> instruction: 0xf504492b
d0011558:	f04f4b4f 			; <UNDEFINED> instruction: 0xf04f4b4f
d001155c:	44210a00 	strtmi	r0, [r1], #-2560	; 0xfffff600
d0011560:	0988f109 	stmibeq	r8, {r0, r3, r8, ip, sp, lr, pc}
d0011564:	0b88f10b 	bleq	0xce24d998
d0011568:	3000f8db 	ldrdcc	pc, [r0], -fp
d001156c:	d2e4459a 	rscle	r4, r4, #645922816	; 0x26800000
d0011570:	91064648 	tstls	r6, r8, asr #12
d0011574:	0948f109 	stmdbeq	r8, {r0, r3, r8, ip, sp, lr, pc}^
d0011578:	fb94f00c 	blx	0xce54d5b2
d001157c:	d0c32800 	sbcle	r2, r3, r0, lsl #16
d0011580:	0a01f10a 	beq	0xd008d9b0
d0011584:	e7ef9906 	strb	r9, [pc, r6, lsl #18]!
d0011588:	01fcf8d4 	ldrsbeq	pc, [ip, #132]!	; 0x84	; <UNPREDICTABLE>
d001158c:	f1042200 			; <UNDEFINED> instruction: 0xf1042200
d0011590:	42820c94 	addmi	r0, r2, #148, 24	; 0x9400
d0011594:	1342ea4f 	movtne	lr, #10831	; 0x2a4f
d0011598:	3201d13a 	andcc	sp, r1, #-2147483634	; 0x8000000e
d001159c:	f8d468e5 			; <UNDEFINED> instruction: 0xf8d468e5
d00115a0:	44239074 	strtmi	r9, [r3], #-116	; 0xffffff8c
d00115a4:	21fcf8c4 	mvnscs	pc, r4, asr #17
d00115a8:	020cf24d 	andeq	pc, ip, #-805306364	; 0xd0000004
d00115ac:	e004f8d4 	ldrd	pc, [r4], -r4
d00115b0:	c002f854 	andgt	pc, r2, r4, asr r8	; <UNPREDICTABLE>
d00115b4:	e9d46822 	ldmib	r4, {r1, r5, fp, sp, lr}^
d00115b8:	f8c36004 			; <UNDEFINED> instruction: 0xf8c36004
d00115bc:	25015088 	strcs	r5, [r1, #-136]	; 0xffffff78
d00115c0:	608cf8c3 	addvs	pc, ip, r3, asr #17
d00115c4:	f8c367da 			; <UNDEFINED> instruction: 0xf8c367da
d00115c8:	e9c3c098 	stmib	r3, {r3, r4, r7, lr, pc}^
d00115cc:	e9c30124 	stmib	r3, {r2, r5, r8}^
d00115d0:	f44f9e20 			; <UNDEFINED> instruction: 0xf44f9e20
d00115d4:	fb0373a6 	blx	0xd00ee476
d00115d8:	18e1f308 	stmiane	r1!, {r3, r8, r9, ip, sp, lr, pc}^
d00115dc:	7300f503 	movwvc	pc, #1283	; 0x503	; <UNPREDICTABLE>
d00115e0:	2308f8b1 	movwcs	pc, #34993	; 0x88b1	; <UNPREDICTABLE>
d00115e4:	f8d14423 			; <UNDEFINED> instruction: 0xf8d14423
d00115e8:	43170300 	tstmi	r7, #0, 6
d00115ec:	522ef504 	eorpl	pc, lr, #4, 10	; 0x1000000
d00115f0:	f8a13208 			; <UNDEFINED> instruction: 0xf8a13208
d00115f4:	44027308 	strmi	r7, [r2], #-776	; 0xfffffcf8
d00115f8:	f8d16022 			; <UNDEFINED> instruction: 0xf8d16022
d00115fc:	67632304 	strbvs	r2, [r3, -r4, lsl #6]!
d0011600:	22006062 	andcs	r6, r0, #98	; 0x62
d0011604:	8078f8c4 	rsbshi	pc, r8, r4, asr #17
d0011608:	e9c460e2 	stmib	r4, {r1, r5, r6, r7, sp, lr}^
d001160c:	e60d5504 	str	r5, [sp], -r4, lsl #10
d0011610:	3003f85c 	andcc	pc, r3, ip, asr r8	; <UNPREDICTABLE>
d0011614:	d0934598 	umullsle	r4, r3, r8, r5
d0011618:	e7ba3201 	ldr	r3, [sl, r1, lsl #4]!
d001161c:	00800013 	addeq	r0, r0, r3, lsl r0
d0011620:	fffffe34 			; <UNDEFINED> instruction: 0xfffffe34
d0011624:	fffffe3f 			; <UNDEFINED> instruction: 0xfffffe3f
d0011628:	fffffe35 			; <UNDEFINED> instruction: 0xfffffe35
d001162c:	fffffe28 			; <UNDEFINED> instruction: 0xfffffe28
d0011630:	fffffe1b 			; <UNDEFINED> instruction: 0xfffffe1b
d0011634:	fffffde8 			; <UNDEFINED> instruction: 0xfffffde8
d0011638:	fffffe11 			; <UNDEFINED> instruction: 0xfffffe11
d001163c:	fffffdf9 			; <UNDEFINED> instruction: 0xfffffdf9
d0011640:	fffffe12 			; <UNDEFINED> instruction: 0xfffffe12
d0011644:	fffffd4f 			; <UNDEFINED> instruction: 0xfffffd4f
d0011648:	fffffc8f 			; <UNDEFINED> instruction: 0xfffffc8f
d001164c:	fffffc8b 			; <UNDEFINED> instruction: 0xfffffc8b

Disassembly of section .text.scan:

d00117f0 <.text.scan>:
d00117f0:	e92d6d8b 	push	{r0, r1, r3, r7, r8, sl, fp, sp, lr}
d00117f4:	46064ff0 			; <UNDEFINED> instruction: 0x46064ff0
d00117f8:	460cb09d 			; <UNDEFINED> instruction: 0x460cb09d
d00117fc:	f501bba3 			; <UNDEFINED> instruction: 0xf501bba3
d0011800:	370c4750 	smlsdcc	ip, r0, r7, r4
d0011804:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011808:	2800fd27 	stmdacs	r0, {r0, r1, r2, r5, r8, sl, fp, ip, sp, lr, pc}
d001180c:	2100d150 	tstcs	r0, r0, asr r1
d0011810:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011814:	2820fcd7 	stmdacs	r0!, {r0, r1, r2, r4, r6, r7, sl, fp, ip, sp, lr, pc}
d0011818:	2809d029 	stmdacs	r9, {r0, r3, r5, ip, lr, pc}
d001181c:	2823d027 	stmdacs	r3!, {r0, r1, r2, r5, ip, lr, pc}
d0011820:	686268e3 	stmdavs	r2!, {r0, r1, r5, r6, r7, fp, sp, lr}^
d0011824:	429ad137 	addsmi	sp, sl, #-1073741811	; 0xc000000d
d0011828:	f10dd942 			; <UNDEFINED> instruction: 0xf10dd942
d001182c:	46210830 			; <UNDEFINED> instruction: 0x46210830
d0011830:	4640ad14 			; <UNDEFINED> instruction: 0x4640ad14
d0011834:	fceef7fe 	stc2l	7, cr15, [lr], #1016	; 0x3f8
d0011838:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d001183c:	f10dfccc 			; <UNDEFINED> instruction: 0xf10dfccc
d0011840:	46ec0e38 			; <UNDEFINED> instruction: 0x46ec0e38
d0011844:	000fe8be 			; <UNDEFINED> instruction: 0x000fe8be
d0011848:	000fe8ac 	andeq	lr, pc, ip, lsr #17
d001184c:	0003e89e 	muleq	r3, lr, r8
d0011850:	0003e88c 	andeq	lr, r3, ip, lsl #17
d0011854:	46284621 	strtmi	r4, [r8], -r1, lsr #12
d0011858:	000ce898 	muleq	ip, r8, r8
d001185c:	fce0f000 	stc2l	0, cr15, [r0]
d0011860:	b1436da3 	smlaltblt	r6, r3, r3, sp
d0011864:	46304621 	ldrtmi	r4, [r0], -r1, lsr #12
d0011868:	fcd4f7fe 	ldc2l	7, cr15, [r4], {254}	; 0xfe
d001186c:	4620e00f 	strtmi	lr, [r0], -pc
d0011870:	fcb1f7fe 	ldc2	7, cr15, [r1], #1016	; 0x3f8
d0011874:	9b19e7cb 	blls	0xd068b7a8
d0011878:	7f93f5b3 	svcvc	0x0093f5b3
d001187c:	462cd0c2 	strtmi	sp, [ip], -r2, asr #1
d0011880:	cc0f4637 	stcgt	6, cr4, [pc], {55}	; 0x37
d0011884:	e894c70f 	ldm	r4, {r0, r1, r2, r3, r8, r9, sl, lr, pc}
d0011888:	e887000f 	stm	r7, {r0, r1, r2, r3}
d001188c:	4630000f 	ldrtmi	r0, [r0], -pc
d0011890:	e8bdb01d 	pop	{r0, r2, r3, r4, ip, sp, pc}
d0011894:	429a8ff0 	addsmi	r8, sl, #240, 30	; 0x3c0
d0011898:	4620d90a 	strtmi	sp, [r0], -sl, lsl #18
d001189c:	fcf9f7fe 	ldc2l	7, cr15, [r9], #1016	; 0x3f8
d00118a0:	686368e2 	stmdavs	r3!, {r1, r5, r6, r7, fp, sp, lr}^
d00118a4:	d2ad429a 	adcle	r4, sp, #-1610612727	; 0xa0000009
d00118a8:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d00118ac:	e7a9fc94 			; <UNDEFINED> instruction: 0xe7a9fc94
d00118b0:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d00118b4:	fc86f7fe 	stc2	7, cr15, [r6], {254}	; 0xfe
d00118b8:	d0f52820 	rscsle	r2, r5, r0, lsr #16
d00118bc:	0309f1a0 	movweq	pc, #37280	; 0x91a0	; <UNPREDICTABLE>
d00118c0:	d9f12b04 	ldmible	r1!, {r2, r8, r9, fp, sp}^
d00118c4:	d170282f 	cmnle	r0, pc, lsr #16
d00118c8:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d00118cc:	fc7af7fe 	ldc2l	7, cr15, [sl], #-1016	; 0xfffffc08
d00118d0:	d10f282f 	tstle	pc, pc, lsr #16
d00118d4:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d00118d8:	fc74f7fe 	ldc2l	7, cr15, [r4], #-1016	; 0xfffffc08
d00118dc:	686368e2 	stmdavs	r3!, {r1, r5, r6, r7, fp, sp, lr}^
d00118e0:	d08f429a 	umullle	r4, pc, sl, r2	; <UNPREDICTABLE>
d00118e4:	d08d280a 	addle	r2, sp, sl, lsl #16
d00118e8:	d08b280d 	addle	r2, fp, sp, lsl #16
d00118ec:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d00118f0:	e7effc72 			; <UNDEFINED> instruction: 0xe7effc72
d00118f4:	d158282a 	cmple	r8, sl, lsr #16
d00118f8:	4621a814 			; <UNDEFINED> instruction: 0x4621a814
d00118fc:	fc8af7fe 	stc2	7, cr15, [sl], {254}	; 0xfe
d0011900:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011904:	4620fc68 	strtmi	pc, [r0], -r8, ror #24
d0011908:	fc65f7fe 	stc2l	7, cr15, [r5], #-1016	; 0xfffffc08
d001190c:	686368e2 	stmdavs	r3!, {r1, r5, r6, r7, fp, sp, lr}^
d0011910:	f000429a 			; <UNDEFINED> instruction: 0xf000429a
d0011914:	21008274 	tstcs	r0, r4, ror r2
d0011918:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d001191c:	282afc53 	stmdacs	sl!, {r0, r1, r4, r6, sl, fp, ip, sp, lr, pc}
d0011920:	2101d1f1 	strdcs	sp, [r1, -r1]
d0011924:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011928:	282ffc4d 	stmdacs	pc!, {r0, r2, r3, r6, sl, fp, ip, sp, lr, pc}	; <UNPREDICTABLE>
d001192c:	4620d1eb 	strtmi	sp, [r0], -fp, ror #3
d0011930:	fc51f7fe 	mrrc2	7, 15, pc, r1, cr14	; <UNPREDICTABLE>
d0011934:	3b01e7b8 	blcc	0xd008b81c
d0011938:	eb046838 	bl	0xd012ba20
d001193c:	015a1143 	cmpeq	sl, r3, asr #2
d0011940:	1098f8d1 			; <UNDEFINED> instruction: 0x1098f8d1
d0011944:	d0064288 	andle	r4, r6, r8, lsl #5
d0011948:	1550f8df 	ldrbne	pc, [r0, #-2271]	; 0xfffff721	; <UNPREDICTABLE>
d001194c:	46204479 			; <UNDEFINED> instruction: 0x46204479
d0011950:	fc2af7fe 	stc2	7, cr15, [sl], #-1016	; 0xfffffc08
d0011954:	327ce786 	rsbscc	lr, ip, #35127296	; 0x2180000
d0011958:	31fcf8c4 	mvnscc	pc, r4, asr #17
d001195c:	f85418a3 			; <UNDEFINED> instruction: 0xf85418a3
d0011960:	f103e002 			; <UNDEFINED> instruction: 0xf103e002
d0011964:	f8d3000c 			; <UNDEFINED> instruction: 0xf8d3000c
d0011968:	689dc004 	ldmvs	sp, {r2, lr, pc}
d001196c:	e9c4c80f 	stmib	r4, {r0, r1, r2, r3, fp, lr, pc}^
d0011970:	22011204 	andcs	r1, r1, #4, 4	; 0x40000000
d0011974:	e000f8c4 	and	pc, r0, r4, asr #17
d0011978:	c074f8c4 	rsbsgt	pc, r4, r4, asr #17
d001197c:	60e06065 	rscvs	r6, r0, r5, rrx
d0011980:	68e167a3 	stmiavs	r1!, {r0, r1, r5, r7, r8, r9, sl, sp, lr}^
d0011984:	42996863 	addsmi	r6, r9, #6488064	; 0x630000
d0011988:	824af040 	subhi	pc, sl, #64	; 0x40
d001198c:	31fcf8d4 	ldrsbcc	pc, [ip, #132]!	; 0x84	; <UNPREDICTABLE>
d0011990:	d1d02b00 	bicsle	r2, r0, r0, lsl #22
d0011994:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0011998:	683baf35 	ldmdavs	fp!, {r0, r2, r4, r5, r8, r9, sl, fp, sp, pc}
d001199c:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d00119a0:	f8df8242 			; <UNDEFINED> instruction: 0xf8df8242
d00119a4:	447914fc 	ldrbtmi	r1, [r9], #-1276	; 0xfffffb04
d00119a8:	2200e7d1 	andcs	lr, r0, #54788096	; 0x3440000
d00119ac:	4620e7e9 	strtmi	lr, [r0], -r9, ror #15
d00119b0:	fc11f7fe 	ldc2	7, cr15, [r1], {254}	; 0xfe
d00119b4:	46812823 	strmi	r2, [r1], r3, lsr #16
d00119b8:	f10dd124 			; <UNDEFINED> instruction: 0xf10dd124
d00119bc:	46ec0e38 			; <UNDEFINED> instruction: 0x46ec0e38
d00119c0:	0850f10d 	ldmdaeq	r0, {r0, r2, r3, r8, ip, sp, lr, pc}^
d00119c4:	000fe8be 			; <UNDEFINED> instruction: 0x000fe8be
d00119c8:	000fe8ac 	andeq	lr, pc, ip, lsr #17
d00119cc:	0003e89e 	muleq	r3, lr, r8
d00119d0:	0003e88c 	andeq	lr, r3, ip, lsl #17
d00119d4:	46404621 	strbmi	r4, [r0], -r1, lsr #12
d00119d8:	000ce895 	muleq	ip, r5, r8
d00119dc:	fc20f000 	stc2	0, cr15, [r0], #-0
d00119e0:	2b006da3 	blcs	0xd002d074
d00119e4:	af3ef47f 	svcge	0x003ef47f
d00119e8:	f5b39b19 			; <UNDEFINED> instruction: 0xf5b39b19
d00119ec:	f43f7f93 			; <UNDEFINED> instruction: 0xf43f7f93
d00119f0:	4644af09 	strbmi	sl, [r4], -r9, lsl #30
d00119f4:	cc0f4635 	stcgt	6, cr4, [pc], {53}	; 0x35
d00119f8:	e894c50f 	ldm	r4, {r0, r1, r2, r3, r8, sl, lr, pc}
d00119fc:	e885000f 	stm	r5, {r0, r1, r2, r3}
d0011a00:	e744000f 	strb	r0, [r4, -pc]
d0011a04:	fc95f7fe 	ldc2	7, cr15, [r5], {254}	; 0xfe
d0011a08:	28004601 	stmdacs	r0, {r0, r9, sl, lr}
d0011a0c:	f1a9d140 			; <UNDEFINED> instruction: 0xf1a9d140
d0011a10:	f1b80830 			; <UNDEFINED> instruction: 0xf1b80830
d0011a14:	f2000f09 	vmax.f32	d0, d0, d9
d0011a18:	f1b980fa 			; <UNDEFINED> instruction: 0xf1b980fa
d0011a1c:	f0000f30 			; <UNDEFINED> instruction: 0xf0000f30
d0011a20:	270a821a 	smladcs	sl, sl, r2, r8
d0011a24:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d0011a28:	fbccf7fe 	blx	0xcf34fa2a
d0011a2c:	f7fe4681 			; <UNDEFINED> instruction: 0xf7fe4681
d0011a30:	4287fc8c 	addmi	pc, r7, #140, 24	; 0x8c00
d0011a34:	80c4f200 	sbchi	pc, r4, r0, lsl #4
d0011a38:	0920f049 	stmdbeq	r0!, {r0, r3, r6, ip, sp, lr, pc}
d0011a3c:	0f75f1b9 	svceq	0x0075f1b9
d0011a40:	4620d102 	strtmi	sp, [r0], -r2, lsl #2
d0011a44:	fbc7f7fe 	blx	0xcf20fa46
d0011a48:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d0011a4c:	fbbaf7fe 	blx	0xceecfa4e
d0011a50:	0330f1a0 	teqeq	r0, #160, 2	; 0x28	; <UNPREDICTABLE>
d0011a54:	2b094602 	blcs	0xd0263264
d0011a58:	f7fed90f 			; <UNDEFINED> instruction: 0xf7fed90f
d0011a5c:	b960fc6a 	stmdblt	r0!, {r1, r3, r5, r6, sl, fp, ip, sp, lr, pc}^
d0011a60:	d00a2a2e 	andle	r2, sl, lr, lsr #20
d0011a64:	0f75f1b9 	svceq	0x0075f1b9
d0011a68:	80cbf000 	sbchi	pc, fp, r0
d0011a6c:	f0402f0a 			; <UNDEFINED> instruction: 0xf0402f0a
d0011a70:	f1b880bd 			; <UNDEFINED> instruction: 0xf1b880bd
d0011a74:	f2800f00 			; <UNDEFINED> instruction: 0xf2800f00
d0011a78:	6da380c7 	stcvs	0, cr8, [r3, #796]!	; 0x31c
d0011a7c:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0011a80:	f8dfaef1 			; <UNDEFINED> instruction: 0xf8dfaef1
d0011a84:	447b3420 	ldrbtmi	r3, [fp], #-1056	; 0xfffffbe0
d0011a88:	4620e03f 			; <UNDEFINED> instruction: 0x4620e03f
d0011a8c:	fba3f7fe 	blx	0xce90fa8e
d0011a90:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d0011a94:	fb96f7fe 	blx	0xce5cfa96
d0011a98:	f7fe4602 			; <UNDEFINED> instruction: 0xf7fe4602
d0011a9c:	2800fc4a 	stmdacs	r0, {r1, r3, r6, sl, fp, ip, sp, lr, pc}
d0011aa0:	3a30d1f3 	bcc	0xd0c46274
d0011aa4:	d9f02a09 	ldmible	r0!, {r0, r3, r9, fp, sp}^
d0011aa8:	46056827 	strmi	r6, [r5], -r7, lsr #16
d0011aac:	f8df68e3 			; <UNDEFINED> instruction: 0xf8df68e3
d0011ab0:	441f93f8 	ldrmi	r9, [pc], #-1016	; 0xd0011ab8
d0011ab4:	eba744f9 	bl	0xce9e2ea0
d0011ab8:	f8590708 			; <UNDEFINED> instruction: 0xf8590708
d0011abc:	46392b04 	ldrtmi	r2, [r9], -r4, lsl #22
d0011ac0:	f7fe4640 			; <UNDEFINED> instruction: 0xf7fe4640
d0011ac4:	b160fe76 	smclt	4070	; 0xfe6
d0011ac8:	1507f205 	strne	pc, [r7, #-517]	; 0xfffffdfb
d0011acc:	9511970d 	ldrls	r9, [r1, #-1805]	; 0xfffff8f3
d0011ad0:	ad0c4634 	stcge	6, cr4, [ip, #-208]	; 0xffffff30
d0011ad4:	c40fcd0f 	strgt	ip, [pc], #-3343	; 0xd0011adc
d0011ad8:	000fe895 	muleq	pc, r5, r8	; <UNPREDICTABLE>
d0011adc:	000fe884 	andeq	lr, pc, r4, lsl #17
d0011ae0:	3501e6d5 	strcc	lr, [r1, #-1749]	; 0xfffff92b
d0011ae4:	d1e82d14 	mvnle	r2, r4, lsl sp
d0011ae8:	93c0f8df 	bicls	pc, r0, #14614528	; 0xdf0000
d0011aec:	44f94605 	ldrbtmi	r4, [r9], #1541	; 0x605
d0011af0:	2b04f859 	blcs	0xd014fc5c
d0011af4:	46404639 			; <UNDEFINED> instruction: 0x46404639
d0011af8:	fe5bf7fe 	mrc2	7, 2, pc, cr11, cr14, {7}
d0011afc:	6da3b160 	stfvsd	f3, [r3, #384]!	; 0x180
d0011b00:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0011b04:	4beaaeaf 	blmi	0xcfabd5c8
d0011b08:	65a3447b 	strvs	r4, [r3, #1147]!	; 0x47b
d0011b0c:	e9c49b06 	stmib	r4, {r1, r2, r8, r9, fp, ip, pc}^
d0011b10:	65e3ba18 	strbvs	fp, [r3, #2584]!	; 0xa18
d0011b14:	e1819b07 	orr	r9, r1, r7, lsl #22
d0011b18:	2d183501 	cfldr32cs	mvfx3, [r8, #-4]
d0011b1c:	463ad1e8 	ldrtmi	sp, [sl], -r8, ror #3
d0011b20:	46204641 	strtmi	r4, [r0], -r1, asr #12
d0011b24:	fbe3f7fe 	blx	0xcf90fb26
d0011b28:	db2b2800 	blle	0xd0adbb30
d0011b2c:	fb032348 	blx	0xd00da856
d0011b30:	f5004000 			; <UNDEFINED> instruction: 0xf5004000
d0011b34:	30c8402b 	sbccc	r4, r8, fp, lsr #32
d0011b38:	0100e9d0 	ldrdeq	lr, [r0, -r0]
d0011b3c:	4300f110 	movwmi	pc, #272	; 0x110	; <UNPREDICTABLE>
d0011b40:	f1419308 			; <UNDEFINED> instruction: 0xf1419308
d0011b44:	93090300 	movwls	r0, #37632	; 0x9300
d0011b48:	2308e9dd 	movwcs	lr, #35293	; 0x89dd
d0011b4c:	bf082b01 	svclt	0x00082b01
d0011b50:	4f00f1b2 	svcmi	0x0000f1b2
d0011b54:	6da3d306 	stcvs	3, cr13, [r3, #24]!
d0011b58:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0011b5c:	4bd5ae83 	blmi	0xcf57d570
d0011b60:	e7d2447b 			; <UNDEFINED> instruction: 0xe7d2447b
d0011b64:	4200f06f 	andmi	pc, r0, #111	; 0x6f
d0011b68:	900a2300 	andls	r2, sl, r0, lsl #6
d0011b6c:	418b4282 	orrmi	r4, fp, r2, lsl #5
d0011b70:	1303f240 	movwne	pc, #12864	; 0x3240	; <UNPREDICTABLE>
d0011b74:	f44fbfa8 			; <UNDEFINED> instruction: 0xf44fbfa8
d0011b78:	9a0a7381 	bls	0xd02ae984
d0011b7c:	920e970d 	andls	r9, lr, #3407872	; 0x340000
d0011b80:	e7a59311 			; <UNDEFINED> instruction: 0xe7a59311
d0011b84:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d0011b88:	4620e7f7 			; <UNDEFINED> instruction: 0x4620e7f7
d0011b8c:	f7fe910a 			; <UNDEFINED> instruction: 0xf7fe910a
d0011b90:	990afb22 	stmdbls	sl, {r1, r5, r8, r9, fp, ip, sp, lr, pc}
d0011b94:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011b98:	f7fefb15 			; <UNDEFINED> instruction: 0xf7fefb15
d0011b9c:	2810fbd6 	ldmdacs	r0, {r1, r2, r4, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d0011ba0:	d1214607 			; <UNDEFINED> instruction: 0xd1214607
d0011ba4:	2b006da3 	blcs	0xd002d238
d0011ba8:	af3cf47f 	svcge	0x003cf47f
d0011bac:	447b4bc2 	ldrbtmi	r4, [fp], #-3010	; 0xfffff43e
d0011bb0:	9b0665a3 	blls	0xd01ab244
d0011bb4:	9b0765e3 	blls	0xd01eb348
d0011bb8:	ba18e9c4 	blt	0xd064c2d0
d0011bbc:	e73166a3 	ldr	r6, [r1, -r3, lsr #13]!
d0011bc0:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011bc4:	f7fefb08 			; <UNDEFINED> instruction: 0xf7fefb08
d0011bc8:	43c3fbc0 	bicmi	pc, r3, #192, 22	; 0x30000
d0011bcc:	f3f7fbb3 			; <UNDEFINED> instruction: 0xf3f7fbb3
d0011bd0:	d2064543 	andle	r4, r6, #281018368	; 0x10c00000
d0011bd4:	2b006da3 	blcs	0xd002d268
d0011bd8:	ae44f47f 	mcrge	4, 2, pc, cr4, cr15, {3}	; <UNPREDICTABLE>
d0011bdc:	447b4bb7 	ldrbtmi	r4, [fp], #-2999	; 0xfffff449
d0011be0:	fb08e793 	blx	0xd024ba36
d0011be4:	e71d0807 	ldr	r0, [sp, -r7, lsl #16]
d0011be8:	e71b2710 			; <UNDEFINED> instruction: 0xe71b2710
d0011bec:	0f00f1b8 	svceq	0x0000f1b8
d0011bf0:	1303f240 	movwne	pc, #12864	; 0x3240	; <UNPREDICTABLE>
d0011bf4:	f44fbfa8 			; <UNDEFINED> instruction: 0xf44fbfa8
d0011bf8:	f8cd7381 			; <UNDEFINED> instruction: 0xf8cd7381
d0011bfc:	93118038 	tstls	r1, #56	; 0x38
d0011c00:	f240e127 	vrhadd.s8	d30, d0, d23
d0011c04:	e7f81303 	ldrb	r1, [r8, r3, lsl #6]!
d0011c08:	7381f44f 	orrvc	pc, r1, #1325400064	; 0x4f000000
d0011c0c:	f1b9e7f5 			; <UNDEFINED> instruction: 0xf1b9e7f5
d0011c10:	d0020f22 	andle	r0, r2, r2, lsr #30
d0011c14:	0f27f1b9 	svceq	0x0027f1b9
d0011c18:	6823d171 	stmdavs	r3!, {r0, r4, r5, r6, r8, ip, lr, pc}
d0011c1c:	4701f242 	strmi	pc, [r1, -r2, asr #4]
d0011c20:	68e39308 	stmiavs	r3!, {r3, r8, r9, ip, pc}^
d0011c24:	68e2930b 	stmiavs	r2!, {r0, r1, r3, r8, r9, ip, pc}^
d0011c28:	429a6863 	addsmi	r6, sl, #6488064	; 0x630000
d0011c2c:	4620d05a 			; <UNDEFINED> instruction: 0x4620d05a
d0011c30:	fad1f7fe 	blx	0xcf48fc30
d0011c34:	d14a4581 	smlalbble	r4, sl, r1, r5
d0011c38:	f1b99b08 			; <UNDEFINED> instruction: 0xf1b99b08
d0011c3c:	68e70f22 	stmiavs	r7!, {r1, r5, r8, r9, sl, fp}^
d0011c40:	eb039a0b 	bl	0xd00f8474
d0011c44:	f1070802 			; <UNDEFINED> instruction: 0xf1070802
d0011c48:	682733ff 	stmdavs	r7!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, ip, sp}
d0011c4c:	eba7441f 	bl	0xce9e2cd0
d0011c50:	d0390708 	eorsle	r0, r9, r8, lsl #14
d0011c54:	0907eb08 	stmdbeq	r7, {r3, r8, r9, fp, sp, lr, pc}
d0011c58:	8050f8cd 	subshi	pc, r0, sp, asr #17
d0011c5c:	d10645c8 	smlabtle	r6, r8, r5, r4
d0011c60:	2b006da3 	blcs	0xd002d2f4
d0011c64:	adfef47f 	cfldrdge	mvd15, [lr, #508]!	; 0x1fc
d0011c68:	447b4b95 	ldrbtmi	r4, [fp], #-2965	; 0xfffff46b
d0011c6c:	f108e74d 			; <UNDEFINED> instruction: 0xf108e74d
d0011c70:	9a080301 	bls	0xd021287c
d0011c74:	9314990b 	tstls	r4, #180224	; 0x2c000
d0011c78:	2a5c5c52 	bcs	0xd1728dc8
d0011c7c:	d10e920a 	tstle	lr, sl, lsl #4
d0011c80:	d00c4599 	mulle	ip, r9, r5
d0011c84:	465aab14 			; <UNDEFINED> instruction: 0x465aab14
d0011c88:	46209906 	strtmi	r9, [r0], -r6, lsl #18
d0011c8c:	9b079301 	blls	0xd01f6898
d0011c90:	9008f8cd 	andls	pc, r8, sp, asr #17
d0011c94:	46539300 	ldrbmi	r9, [r3], -r0, lsl #6
d0011c98:	fb98f7fe 	blx	0xce64fc9a
d0011c9c:	9b14900a 	blls	0xd0535ccc
d0011ca0:	d00a4599 	mulle	sl, r9, r5
d0011ca4:	b9436da3 	stmdblt	r3, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0011ca8:	447b4b86 	ldrbtmi	r4, [fp], #-2950	; 0xfffff47a
d0011cac:	9b0665a3 	blls	0xd01ab340
d0011cb0:	9b0765e3 	blls	0xd01eb444
d0011cb4:	ba18e9c4 	blt	0xd064c3cc
d0011cb8:	f44f66a3 	vst1.32	{d22-d24}, [pc :128], r3
d0011cbc:	9a0a7381 	bls	0xd02aeac8
d0011cc0:	870ce9cd 	strhi	lr, [ip, -sp, asr #19]
d0011cc4:	e79a920e 	ldr	r9, [sl, lr, lsl #4]
d0011cc8:	7382f44f 	orrvc	pc, r2, #1325400064	; 0x4f000000
d0011ccc:	285ce7f7 	ldmdacs	ip, {r0, r1, r2, r4, r5, r6, r7, r8, r9, sl, sp, lr, pc}^
d0011cd0:	4620d102 	strtmi	sp, [r0], -r2, lsl #2
d0011cd4:	fa7ff7fe 	blx	0xd200fcd4
d0011cd8:	d8a4280d 	stmiale	r4!, {r0, r2, r3, fp, sp}
d0011cdc:	f000fa27 			; <UNDEFINED> instruction: 0xf000fa27
d0011ce0:	d5a007c3 	strle	r0, [r0, #1987]!	; 0x7c3
d0011ce4:	0f22f1b9 	svceq	0x0022f1b9
d0011ce8:	4b77d102 	blmi	0xd1e060f8
d0011cec:	e001447b 	and	r4, r1, fp, ror r4
d0011cf0:	447b4b76 	ldrbtmi	r4, [fp], #-2934	; 0xfffff48a
d0011cf4:	2a006da2 	bcs	0xd002d384
d0011cf8:	adb4f47f 	cfldrsge	mvf15, [r4, #508]!	; 0x1fc
d0011cfc:	4620e705 	strtmi	lr, [r0], -r5, lsl #14
d0011d00:	fa60f7fe 	blx	0xd184fd00
d0011d04:	4680283d 			; <UNDEFINED> instruction: 0x4680283d
d0011d08:	80b1f040 	adcshi	pc, r1, r0, asr #32
d0011d0c:	0f2bf1b9 	svceq	0x002bf1b9
d0011d10:	f1b9d002 			; <UNDEFINED> instruction: 0xf1b9d002
d0011d14:	d10c0f2d 	tstle	ip, sp, lsr #30
d0011d18:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011d1c:	f1b9fa5c 			; <UNDEFINED> instruction: 0xf1b9fa5c
d0011d20:	f2400f2b 	vmax.f32	d16, d0, d27
d0011d24:	bf0c1925 	svclt	0x000c1925
d0011d28:	7792f44f 	ldrvc	pc, [r2, pc, asr #8]
d0011d2c:	9711464f 	ldrls	r4, [r1, -pc, asr #12]
d0011d30:	f1b9e08f 			; <UNDEFINED> instruction: 0xf1b9e08f
d0011d34:	d1120f3d 	tstle	r2, sp, lsr pc
d0011d38:	033cf1a9 	teqeq	ip, #1073741866	; 0x4000002a	; <UNPREDICTABLE>
d0011d3c:	d9112b02 	ldmdble	r1, {r1, r8, r9, fp, sp}
d0011d40:	0f2df1b9 	svceq	0x002df1b9
d0011d44:	f1b8d132 			; <UNDEFINED> instruction: 0xf1b8d132
d0011d48:	d1460f3e 	cmple	r6, lr, lsr pc
d0011d4c:	f2404620 	vmax.s8	d20, d0, d16
d0011d50:	f7fe1721 			; <UNDEFINED> instruction: 0xf7fe1721
d0011d54:	e7eafa40 	strb	pc, [sl, r0, asr #20]!	; <UNPREDICTABLE>
d0011d58:	0f3df1b8 	svceq	0x003df1b8
d0011d5c:	f1b9d115 			; <UNDEFINED> instruction: 0xf1b9d115
d0011d60:	d1e90f21 	mvnle	r0, r1, lsr #30
d0011d64:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011d68:	f1b9fa36 			; <UNDEFINED> instruction: 0xf1b9fa36
d0011d6c:	d0400f3d 	suble	r0, r0, sp, lsr pc
d0011d70:	0f21f1b9 	svceq	0x0021f1b9
d0011d74:	f1b9d040 			; <UNDEFINED> instruction: 0xf1b9d040
d0011d78:	f2400f3c 	vrecps.f32	d16, d0, d28
d0011d7c:	bf18191d 	svclt	0x0018191d
d0011d80:	778ff44f 	strvc	pc, [pc, pc, asr #8]
d0011d84:	464fbf08 	strbmi	fp, [pc], -r8, lsl #30
d0011d88:	f1b8e7d1 			; <UNDEFINED> instruction: 0xf1b8e7d1
d0011d8c:	d0020f26 	andle	r0, r2, r6, lsr #30
d0011d90:	0f7cf1b8 	svceq	0x007cf1b8
d0011d94:	4620d10a 	strtmi	sp, [r0], -sl, lsl #2
d0011d98:	191ff240 	ldmdbne	pc, {r6, r9, ip, sp, lr, pc}	; <UNPREDICTABLE>
d0011d9c:	fa1bf7fe 	blx	0xd070fd9c
d0011da0:	0f26f1b8 	svceq	0x0026f1b8
d0011da4:	f44fbf18 			; <UNDEFINED> instruction: 0xf44fbf18
d0011da8:	e7eb7790 			; <UNDEFINED> instruction: 0xe7eb7790
d0011dac:	0f00f1b9 	svceq	0x0000f1b9
d0011db0:	6da3d10d 	stfvsd	f5, [r3, #52]!	; 0x34
d0011db4:	4b46b943 	blmi	0xd11c02c8
d0011db8:	65a3447b 	strvs	r4, [r3, #1147]!	; 0x47b
d0011dbc:	65e39b06 	strbvs	r9, [r3, #2822]!	; 0xb06
d0011dc0:	e9c49b07 	stmib	r4, {r0, r1, r2, r8, r9, fp, ip, pc}^
d0011dc4:	66a3ba18 	ssatvs	fp, #4, r8, lsl #20
d0011dc8:	1705f240 	strne	pc, [r5, -r0, asr #4]
d0011dcc:	45c1e7af 	strbmi	lr, [r1, #1967]	; 0x7af
d0011dd0:	f029d103 			; <UNDEFINED> instruction: 0xf029d103
d0011dd4:	2b3c0302 	blcs	0xd0f129e4
d0011dd8:	f1b8d0eb 			; <UNDEFINED> instruction: 0xf1b8d0eb
d0011ddc:	464f0f3d 			; <UNDEFINED> instruction: 0x464f0f3d
d0011de0:	483cd1a5 	ldmdami	ip!, {r0, r2, r5, r7, r8, ip, lr, pc}
d0011de4:	44784649 	ldrbtmi	r4, [r8], #-1609	; 0xfffff9b7
d0011de8:	ff74f00b 			; <UNDEFINED> instruction: 0xff74f00b
d0011dec:	d1e02800 	mvnle	r2, r0, lsl #16
d0011df0:	f240e79d 	vaba.s8	d30, d16, d13
d0011df4:	e79a171b 			; <UNDEFINED> instruction: 0xe79a171b
d0011df8:	778ef44f 	strvc	pc, [lr, pc, asr #8]
d0011dfc:	6da3e797 	stcvs	7, cr14, [r3, #604]!	; 0x25c
d0011e00:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0011e04:	4a34ad2f 	bmi	0xd0d3d2c8
d0011e08:	3068f89d 	mlscc	r8, sp, r8, pc	; <UNPREDICTABLE>
d0011e0c:	65a2447a 	strvs	r4, [r2, #1146]!	; 0x47a
d0011e10:	65e29a17 	strbvs	r9, [r2, #2583]!	; 0xa17
d0011e14:	e9c49a18 	stmib	r4, {r3, r4, r9, fp, ip, pc}^
d0011e18:	9b1b2318 	blls	0xd06daa80
d0011e1c:	e52166a3 	str	r6, [r1, #-1699]!	; 0xfffff95d
d0011e20:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0011e24:	ad0cacef 	stcge	12, cr10, [ip, #-956]	; 0xfffffc44
d0011e28:	46284621 	strtmi	r4, [r8], -r1, lsr #12
d0011e2c:	f9f2f7fe 			; <UNDEFINED> instruction: 0xf9f2f7fe
d0011e30:	68e29b0e 	stmiavs	r2!, {r1, r2, r3, r8, r9, fp, ip, pc}^
d0011e34:	9b0f930a 	blls	0xd03f6a64
d0011e38:	8030f8dd 	ldrsbthi	pc, [r0], -sp	; <UNPREDICTABLE>
d0011e3c:	9b139306 	blls	0xd04f6a5c
d0011e40:	b040f8dd 	ldrdlt	pc, [r0], #-141	; 0xffffff73
d0011e44:	68639307 	stmdavs	r3!, {r0, r1, r2, r8, r9, ip, pc}^
d0011e48:	a048f89d 	umaalge	pc, r8, sp, r8	; <UNPREDICTABLE>
d0011e4c:	f47f429a 			; <UNDEFINED> instruction: 0xf47f429a
d0011e50:	4634adae 	ldrtmi	sl, [r4], -lr, lsr #27
d0011e54:	900ae63e 	andls	lr, sl, lr, lsr r6
d0011e58:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0011e5c:	f040f9b3 			; <UNDEFINED> instruction: 0xf040f9b3
d0011e60:	990a0020 	stmdbls	sl, {r5}
d0011e64:	f43f2878 			; <UNDEFINED> instruction: 0xf43f2878
d0011e68:	2708ae90 			; <UNDEFINED> instruction: 0x2708ae90
d0011e6c:	4581e5da 	strmi	lr, [r1, #1498]	; 0x5da
d0011e70:	af66f47f 	svcge	0x0066f47f
d0011e74:	0f2bf1b9 	svceq	0x002bf1b9
d0011e78:	f1b9d003 			; <UNDEFINED> instruction: 0xf1b9d003
d0011e7c:	f47f0f2d 			; <UNDEFINED> instruction: 0xf47f0f2d
d0011e80:	4620af6b 	strtmi	sl, [r0], -fp, ror #30
d0011e84:	1923f240 	stmdbne	r3!, {r6, r9, ip, sp, lr, pc}
d0011e88:	f9a5f7fe 			; <UNDEFINED> instruction: 0xf9a5f7fe
d0011e8c:	0f2bf1b8 	svceq	0x002bf1b8
d0011e90:	464fbf14 			; <UNDEFINED> instruction: 0x464fbf14
d0011e94:	7791f44f 	ldrvc	pc, [r1, pc, asr #8]
d0011e98:	bf00e749 	svclt	0x0000e749
d0011e9c:	fffffd4b 			; <UNDEFINED> instruction: 0xfffffd4b
d0011ea0:	fffffd15 			; <UNDEFINED> instruction: 0xfffffd15
d0011ea4:	fffffce3 			; <UNDEFINED> instruction: 0xfffffce3
d0011ea8:	0000c290 	muleq	r0, r0, r2
d0011eac:	0000c2a6 	andeq	ip, r0, r6, lsr #5
d0011eb0:	fffffbd3 			; <UNDEFINED> instruction: 0xfffffbd3
d0011eb4:	fffffba2 			; <UNDEFINED> instruction: 0xfffffba2
d0011eb8:	fffffb7d 			; <UNDEFINED> instruction: 0xfffffb7d
d0011ebc:	fffffb66 			; <UNDEFINED> instruction: 0xfffffb66
d0011ec0:	fffffb2d 			; <UNDEFINED> instruction: 0xfffffb2d
d0011ec4:	fffffaed 			; <UNDEFINED> instruction: 0xfffffaed
d0011ec8:	fffff960 			; <UNDEFINED> instruction: 0xfffff960
d0011ecc:	fffff972 			; <UNDEFINED> instruction: 0xfffff972
d0011ed0:	fffffa0e 			; <UNDEFINED> instruction: 0xfffffa0e
d0011ed4:	fffff9d9 			; <UNDEFINED> instruction: 0xfffff9d9
d0011ed8:	fffff874 			; <UNDEFINED> instruction: 0xfffff874

Disassembly of section .text.scan_directive:

d0012220 <.text.scan_directive>:
d0012220:	e92db082 	push	{r1, r7, ip, sp, pc}
d0012224:	ed2d4ff0 	vstr	FPSCR_nzcvqc, [sp, #-448]!	; 0xfffffe40
d0012228:	b09b8b02 	addslt	r8, fp, r2, lsl #22
d001222c:	ee08460c 	cfmadd32	mvax0, mvfx4, mvfx8, mvfx12
d0012230:	a9260a10 	stmdbge	r6!, {r4, r9, fp}
d0012234:	000ce881 	andeq	lr, ip, r1, lsl #17
d0012238:	9d299b2a 	vstmdbls	r9!, {d9-d29}
d001223c:	9b2d9308 	blls	0xd0b76e64
d0012240:	a0b0f89d 	umlalsge	pc, r0, sp, r8	; <UNPREDICTABLE>
d0012244:	68e39309 	stmiavs	r3!, {r0, r3, r8, r9, ip, pc}^
d0012248:	6963930f 	stmdbvs	r3!, {r0, r1, r2, r3, r8, r9, ip, pc}^
d001224c:	21009310 	tstcs	r0, r0, lsl r3
d0012250:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0012254:	2820ffb7 	stmdacs	r0!, {r0, r1, r2, r4, r5, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0012258:	2809d02a 	stmdacs	r9, {r1, r3, r5, ip, lr, pc}
d001225c:	6827d028 	stmdavs	r7!, {r3, r5, ip, lr, pc}
d0012260:	441f68e3 	ldrmi	r6, [pc], #-2275	; 0xd0012268
d0012264:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d0012268:	ffacf7fd 			; <UNDEFINED> instruction: 0xffacf7fd
d001226c:	f861f7fe 			; <UNDEFINED> instruction: 0xf861f7fe
d0012270:	bb084681 	bllt	0xd0223c7c
d0012274:	68e36822 	stmiavs	r3!, {r1, r5, fp, sp, lr}^
d0012278:	1bd2441a 	blne	0xcf4a32e8
d001227c:	d11f2a07 	tstle	pc, r7, lsl #20
d0012280:	1964f8df 	stmdbne	r4!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d0012284:	920a4638 	andls	r4, sl, #56, 12	; 0x3800000
d0012288:	f00a4479 			; <UNDEFINED> instruction: 0xf00a4479
d001228c:	fab0f907 	blx	0xcec506b0
d0012290:	9a0af680 	bls	0xd02cfc98
d0012294:	f04f0976 			; <UNDEFINED> instruction: 0xf04f0976
d0012298:	2a050b00 	bcs	0xd0154ea0
d001229c:	f8cd46d8 			; <UNDEFINED> instruction: 0xf8cd46d8
d00122a0:	f8cdb030 			; <UNDEFINED> instruction: 0xf8cdb030
d00122a4:	f8cdb028 			; <UNDEFINED> instruction: 0xf8cdb028
d00122a8:	d132b02c 	teqle	r2, ip, lsr #32
d00122ac:	bc8cf000 	stclt	0, cr15, [ip], {0}
d00122b0:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d00122b4:	e7caff90 	bfi	pc, r0, (invalid: 31:10)	; <UNPREDICTABLE>
d00122b8:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d00122bc:	e7d1ff8c 	ldrb	pc, [r1, ip, lsl #31]	; <UNPREDICTABLE>
d00122c0:	f0402a06 			; <UNDEFINED> instruction: 0xf0402a06
d00122c4:	f8df8465 			; <UNDEFINED> instruction: 0xf8df8465
d00122c8:	46381924 	ldrtmi	r1, [r8], -r4, lsr #18
d00122cc:	464e920a 	strbmi	r9, [lr], -sl, lsl #4
d00122d0:	f00a4479 			; <UNDEFINED> instruction: 0xf00a4479
d00122d4:	f8dff8e3 			; <UNDEFINED> instruction: 0xf8dff8e3
d00122d8:	fab01918 	blx	0xcec18740
d00122dc:	9a0af880 	bls	0xd02d04e4
d00122e0:	46384479 			; <UNDEFINED> instruction: 0x46384479
d00122e4:	f8daf00a 			; <UNDEFINED> instruction: 0xf8daf00a
d00122e8:	f380fab0 			; <UNDEFINED> instruction: 0xf380fab0
d00122ec:	1904f8df 	stmdbne	r4, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d00122f0:	095b4638 	ldmdbeq	fp, {r3, r4, r5, r9, sl, lr}^
d00122f4:	44799a0a 	ldrbtmi	r9, [r9], #-2570	; 0xfffff5f6
d00122f8:	1858ea4f 	ldmdane	r8, {r0, r1, r2, r3, r6, r9, fp, sp, lr, pc}^
d00122fc:	f00a930b 			; <UNDEFINED> instruction: 0xf00a930b
d0012300:	fab0f8cd 	blx	0xcec5063c
d0012304:	f8cdfb80 			; <UNDEFINED> instruction: 0xf8cdfb80
d0012308:	f8cd9030 			; <UNDEFINED> instruction: 0xf8cd9030
d001230c:	ea4f9028 	b	0xd13f63b4
d0012310:	23001b5b 	movwcs	r1, #2907	; 0xb5b
d0012314:	930d930e 	movwls	r9, #54030	; 0xd30e
d0012318:	2a02e03a 	bcs	0xd00ca408
d001231c:	2a04d022 	bcs	0xd01463ac
d0012320:	d1b8464e 			; <UNDEFINED> instruction: 0xd1b8464e
d0012324:	18d0f8df 	ldmne	r0, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d0012328:	920a4638 	andls	r4, sl, #56, 12	; 0x3800000
d001232c:	447946cb 	ldrbtmi	r4, [r9], #-1739	; 0xfffff935
d0012330:	f00a46c8 			; <UNDEFINED> instruction: 0xf00a46c8
d0012334:	fab0f8b3 	blx	0xcec50608
d0012338:	f8dff380 			; <UNDEFINED> instruction: 0xf8dff380
d001233c:	463818c0 	ldrtmi	r1, [r8], -r0, asr #17
d0012340:	9a0a095b 	bls	0xd02948b4
d0012344:	930e4479 	movwls	r4, #58489	; 0xe479
d0012348:	f8a8f00a 			; <UNDEFINED> instruction: 0xf8a8f00a
d001234c:	f380fab0 			; <UNDEFINED> instruction: 0xf380fab0
d0012350:	9034f8cd 	eorsls	pc, r4, sp, asr #17
d0012354:	9030f8cd 	eorsls	pc, r0, sp, asr #17
d0012358:	f8cd095b 			; <UNDEFINED> instruction: 0xf8cd095b
d001235c:	f8cd9028 			; <UNDEFINED> instruction: 0xf8cd9028
d0012360:	e015902c 	ands	r9, r5, ip, lsr #32
d0012364:	1898f8df 	ldmne	r8, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d0012368:	46cb4638 			; <UNDEFINED> instruction: 0x46cb4638
d001236c:	447946c8 	ldrbtmi	r4, [r9], #-1736	; 0xfffff938
d0012370:	f00a464e 			; <UNDEFINED> instruction: 0xf00a464e
d0012374:	fab0f893 	blx	0xcec505c8
d0012378:	f8cdf380 			; <UNDEFINED> instruction: 0xf8cdf380
d001237c:	095b9038 	ldmdbeq	fp, {r3, r4, r5, ip, pc}^
d0012380:	9030f8cd 	eorsls	pc, r0, sp, asr #17
d0012384:	9028f8cd 	eorls	pc, r8, sp, asr #17
d0012388:	464b930d 	strbmi	r9, [fp], -sp, lsl #6
d001238c:	902cf8cd 	eorls	pc, ip, sp, asr #17
d0012390:	0708ea56 	smlsdeq	r8, r6, sl, lr
d0012394:	815cf000 	cmphi	ip, r0	; <UNPREDICTABLE>
d0012398:	93114620 	tstls	r1, #32, 12	; 0x2000000
d001239c:	ff5cf7fd 			; <UNDEFINED> instruction: 0xff5cf7fd
d00123a0:	28009b11 	stmdacs	r0, {r0, r4, r8, r9, fp, ip, pc}
d00123a4:	8154f000 	cmphi	r4, r0	; <UNPREDICTABLE>
d00123a8:	f10d9b0f 			; <UNDEFINED> instruction: 0xf10d9b0f
d00123ac:	ae120c98 	mrcge	12, 0, r0, cr2, cr8, {4}
d00123b0:	9b1060e3 	blls	0xd042a744
d00123b4:	e8bc6163 	ldm	ip!, {r0, r1, r5, r6, r8, sp, lr}
d00123b8:	c60f000f 	strgt	r0, [pc], -pc
d00123bc:	000fe89c 	muleq	pc, ip, r8	; <UNPREDICTABLE>
d00123c0:	000fe886 	andeq	lr, pc, r6, lsl #17
d00123c4:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d00123c8:	fefcf7fd 	mrc2	7, 7, pc, cr12, cr13, {7}
d00123cc:	d0332820 	eorsle	r2, r3, r0, lsr #16
d00123d0:	d0312809 	eorsle	r2, r1, r9, lsl #16
d00123d4:	68e36826 	stmiavs	r3!, {r1, r2, r5, fp, sp, lr}^
d00123d8:	2100441e 	tstcs	r0, lr, lsl r4
d00123dc:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d00123e0:	f7fdfef1 			; <UNDEFINED> instruction: 0xf7fdfef1
d00123e4:	bb58ffa6 	bllt	0xd1652284
d00123e8:	68e36822 	stmiavs	r3!, {r1, r5, fp, sp, lr}^
d00123ec:	1b92441a 	blne	0xce4a345c
d00123f0:	d1292a07 			; <UNDEFINED> instruction: 0xd1292a07
d00123f4:	180cf8df 	stmdane	ip, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d00123f8:	44794630 	ldrbtmi	r4, [r9], #-1584	; 0xfffff9d0
d00123fc:	f84ef00a 			; <UNDEFINED> instruction: 0xf84ef00a
d0012400:	b3584607 	cmplt	r8, #7340032	; 0x700000
d0012404:	b94b6da3 	stmdblt	fp, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0012408:	37fcf8df 	ubfxcc	pc, pc, #17, #29
d001240c:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0012410:	9b083516 	blls	0xd021f870
d0012414:	3a18e9c4 	bcc	0xd064cb2c
d0012418:	66a39b09 	strtvs	r9, [r3], r9, lsl #22
d001241c:	ee184621 	cfmsub32	mvax1, mvfx4, mvfx8, mvfx1
d0012420:	f7fd0a10 			; <UNDEFINED> instruction: 0xf7fd0a10
d0012424:	ee18fef7 	mrc	14, 0, APSR_nzcv, cr8, cr7, {7}
d0012428:	b01b0a10 	andslt	r0, fp, r0, lsl sl
d001242c:	8b02ecbd 	blhi	0xd00cd728
d0012430:	4ff0e8bd 	svcmi	0x00f0e8bd
d0012434:	4770b002 	ldrbmi	fp, [r0, -r2]!
d0012438:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d001243c:	e7c1fecc 	strb	pc, [r1, ip, asr #29]	; <UNPREDICTABLE>
d0012440:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0012444:	e7c8fec8 	strb	pc, [r8, r8, asr #29]	; <UNPREDICTABLE>
d0012448:	d1db2a06 	bicsle	r2, fp, r6, lsl #20
d001244c:	17bcf8df 	sbfxne	pc, pc, #17, #29
d0012450:	44794630 	ldrbtmi	r4, [r9], #-1584	; 0xfffff9d0
d0012454:	f822f00a 			; <UNDEFINED> instruction: 0xf822f00a
d0012458:	d1d32800 	bicsle	r2, r3, r0, lsl #16
d001245c:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d0012460:	feb0f7fd 	mrc2	7, 5, pc, cr0, cr13, {7}
d0012464:	d0162820 	andsle	r2, r6, r0, lsr #16
d0012468:	d0142809 	andsle	r2, r4, r9, lsl #16
d001246c:	d0552f00 	subsle	r2, r5, r0, lsl #30
d0012470:	68e76826 	stmiavs	r7!, {r1, r2, r5, fp, sp, lr}^
d0012474:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d0012478:	fea4f7fd 	mcr2	7, 5, pc, cr4, cr13, {7}	; <UNPREDICTABLE>
d001247c:	ff59f7fd 			; <UNDEFINED> instruction: 0xff59f7fd
d0012480:	6fa3b968 	svcvs	0x00a3b968
d0012484:	da0e2b00 	ble	0xd039d08c
d0012488:	2b006da3 	blcs	0xd002db1c
d001248c:	f8dfd1c6 			; <UNDEFINED> instruction: 0xf8dfd1c6
d0012490:	447b3780 	ldrbtmi	r3, [fp], #-1920	; 0xfffff880
d0012494:	4620e7bb 			; <UNDEFINED> instruction: 0x4620e7bb
d0012498:	fe9df7fd 	mrc2	7, 4, pc, cr13, cr13, {7}
d001249c:	4620e7de 			; <UNDEFINED> instruction: 0x4620e7de
d00124a0:	fe99f7fd 	mrc2	7, 4, pc, cr9, cr13, {7}
d00124a4:	6822e7e6 	stmdavs	r2!, {r1, r2, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d00124a8:	68e319f0 	stmiavs	r3!, {r4, r5, r6, r7, r8, fp, ip}^
d00124ac:	1a12441a 	bne	0xd04a351c
d00124b0:	d1e92a04 	mvnle	r2, r4, lsl #20
d00124b4:	175cf8df 	smmlsne	ip, pc, r8, pc	; <UNPREDICTABLE>
d00124b8:	f0094479 			; <UNDEFINED> instruction: 0xf0094479
d00124bc:	2800ffef 	stmdacs	r0, {r0, r1, r2, r3, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d00124c0:	6fa3d1e2 	svcvs	0x00a3d1e2
d00124c4:	72a6f44f 	adcvc	pc, r6, #1325400064	; 0x4f000000
d00124c8:	4303fb02 	movwmi	pc, #15106	; 0x3b02	; <UNPREDICTABLE>
d00124cc:	f8832201 			; <UNDEFINED> instruction: 0xf8832201
d00124d0:	2100230a 	tstcs	r0, sl, lsl #6
d00124d4:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d00124d8:	2820fe75 	stmdacs	r0!, {r0, r2, r4, r5, r6, r9, sl, fp, ip, sp, lr, pc}
d00124dc:	80b4f000 	adcshi	pc, r4, r0
d00124e0:	f0002809 			; <UNDEFINED> instruction: 0xf0002809
d00124e4:	68e280b1 	stmiavs	r2!, {r0, r4, r5, r7, pc}^
d00124e8:	429a6863 	addsmi	r6, sl, #6488064	; 0x630000
d00124ec:	80a6f000 	adchi	pc, r6, r0
d00124f0:	f000280d 			; <UNDEFINED> instruction: 0xf000280d
d00124f4:	280a80a3 	stmdacs	sl, {r0, r1, r5, r7, pc}
d00124f8:	80a0f000 	adchi	pc, r0, r0
d00124fc:	d106282f 	tstle	r6, pc, lsr #16
d0012500:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d0012504:	fe5ef7fd 	mrc2	7, 2, pc, cr14, cr13, {7}
d0012508:	f000282f 			; <UNDEFINED> instruction: 0xf000282f
d001250c:	6da38097 	stcvs	0, cr8, [r3, #604]!	; 0x25c
d0012510:	d1832b00 	orrle	r2, r3, r0, lsl #22
d0012514:	3700f8df 			; <UNDEFINED> instruction: 0x3700f8df
d0012518:	e778447b 			; <UNDEFINED> instruction: 0xe778447b
d001251c:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0012520:	2822fe5a 	stmdacs	r2!, {r1, r3, r4, r6, r9, sl, fp, ip, sp, lr, pc}
d0012524:	d0094680 	andle	r4, r9, r0, lsl #13
d0012528:	d01c283c 	andsle	r2, ip, ip, lsr r8
d001252c:	2b006da3 	blcs	0xd002dbc0
d0012530:	af74f47f 	svcge	0x0074f47f
d0012534:	36e4f8df 	usatcc	pc, #4, pc, asr #17	; <UNPREDICTABLE>
d0012538:	e768447b 			; <UNDEFINED> instruction: 0xe768447b
d001253c:	68264681 	stmdavs	r6!, {r0, r7, r9, sl, lr}
d0012540:	210068e7 	smlattcs	r0, r7, r8, r6
d0012544:	68e24620 	stmiavs	r2!, {r5, r9, sl, lr}^
d0012548:	fe3cf7fd 	mrc2	7, 1, pc, cr12, cr13, {7}
d001254c:	429a6863 	addsmi	r6, sl, #6488064	; 0x630000
d0012550:	4581d30c 	strmi	sp, [r1, #780]	; 0x30c
d0012554:	6da3d014 	stcvs	0, cr13, [r3, #80]!	; 0x50
d0012558:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001255c:	f8dfaf5f 			; <UNDEFINED> instruction: 0xf8dfaf5f
d0012560:	447b36c0 	ldrbtmi	r3, [fp], #-1728	; 0xfffff940
d0012564:	f04fe753 			; <UNDEFINED> instruction: 0xf04fe753
d0012568:	e7e8093e 			; <UNDEFINED> instruction: 0xe7e8093e
d001256c:	d0074581 	andle	r4, r7, r1, lsl #11
d0012570:	d0f0280d 	rscsle	r2, r0, sp, lsl #16
d0012574:	d0ee280a 	rscle	r2, lr, sl, lsl #16
d0012578:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d001257c:	e7e0fe2c 	strb	pc, [r0, ip, lsr #28]!	; <UNPREDICTABLE>
d0012580:	68264437 	stmdavs	r6!, {r0, r1, r2, r4, r5, sl, lr}
d0012584:	1bf64416 	blne	0xcfda35e4
d0012588:	4620d0e5 	strtmi	sp, [r0], -r5, ror #1
d001258c:	fe23f7fd 	mcr2	7, 1, pc, cr3, cr13, {7}	; <UNPREDICTABLE>
d0012590:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d0012594:	fe16f7fd 	mrc2	7, 0, pc, cr6, cr13, {7}
d0012598:	d0f62820 	rscsle	r2, r6, r0, lsr #16
d001259c:	d0f42809 	rscsle	r2, r4, r9, lsl #16
d00125a0:	686368e2 	stmdavs	r3!, {r1, r5, r6, r7, fp, sp, lr}^
d00125a4:	d013429a 	mulsle	r3, sl, r2
d00125a8:	d011280d 	andsle	r2, r1, sp, lsl #16
d00125ac:	d00f280a 	andle	r2, pc, sl, lsl #16
d00125b0:	d105282f 	tstle	r5, pc, lsr #16
d00125b4:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d00125b8:	fe04f7fd 	mcr2	7, 0, pc, cr4, cr13, {7}	; <UNPREDICTABLE>
d00125bc:	d007282f 	andle	r2, r7, pc, lsr #16
d00125c0:	2b006da3 	blcs	0xd002dc54
d00125c4:	af2af47f 	svcge	0x002af47f
d00125c8:	3658f8df 			; <UNDEFINED> instruction: 0x3658f8df
d00125cc:	e71e447b 			; <UNDEFINED> instruction: 0xe71e447b
d00125d0:	d11b2e06 	tstle	fp, r6, lsl #28
d00125d4:	1650f8df 			; <UNDEFINED> instruction: 0x1650f8df
d00125d8:	46384632 			; <UNDEFINED> instruction: 0x46384632
d00125dc:	f0094479 			; <UNDEFINED> instruction: 0xf0094479
d00125e0:	b998ff5d 	ldmiblt	r8, {r0, r2, r3, r4, r6, r8, r9, sl, fp, ip, sp, lr, pc}
d00125e4:	ee189b08 	vnmls.f64	d9, d8, d8
d00125e8:	95154a10 	ldrls	r4, [r5, #-2576]	; 0xfffff5f0
d00125ec:	9316ad12 	tstls	r6, #1152	; 0x480
d00125f0:	7383f44f 	orrvc	pc, r3, #1325400064	; 0x4f000000
d00125f4:	a060f88d 	rsbge	pc, r0, sp, lsl #17
d00125f8:	9b099317 	blls	0xd027725c
d00125fc:	cd0f9319 	stcgt	3, cr9, [pc, #-100]	; 0xd00125a0
d0012600:	e895c40f 	ldm	r5, {r0, r1, r2, r3, sl, lr, pc}
d0012604:	e884000f 	stm	r4, {r0, r1, r2, r3}
d0012608:	e70c000f 	str	r0, [ip, -pc]
d001260c:	0f22f1b8 	svceq	0x0022f1b8
d0012610:	6da3d007 	stcvs	0, cr13, [r3, #28]!
d0012614:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0012618:	f8dfaf01 			; <UNDEFINED> instruction: 0xf8dfaf01
d001261c:	447b3610 	ldrbtmi	r3, [fp], #-1552	; 0xfffff9f0
d0012620:	9b09e6f5 	blls	0xd028c1fc
d0012624:	9a084629 	bls	0xd0223ed0
d0012628:	93004620 	movwls	r4, #1568	; 0x620
d001262c:	96024653 			; <UNDEFINED> instruction: 0x96024653
d0012630:	f7fe9701 			; <UNDEFINED> instruction: 0xf7fe9701
d0012634:	2800fded 	stmdacs	r0, {r0, r2, r3, r5, r6, r7, r8, sl, fp, ip, sp, lr, pc}
d0012638:	aef0f43f 	mrcge	4, 7, APSR_nzcv, cr0, cr15, {1}
d001263c:	ee184621 	cfmsub32	mvax1, mvfx4, mvfx8, mvfx1
d0012640:	f7ff0a10 			; <UNDEFINED> instruction: 0xf7ff0a10
d0012644:	e6eef8d5 	usat	pc, #14, r5, asr #17	; <UNPREDICTABLE>
d0012648:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d001264c:	e740fdc4 	strb	pc, [r0, -r4, asr #27]	; <UNPREDICTABLE>
d0012650:	0206ea49 	andeq	lr, r6, #299008	; 0x49000
d0012654:	ea42990b 	b	0xd10b8a88
d0012658:	430a0208 	movwmi	r0, #41480	; 0xa208
d001265c:	430a990a 	movwmi	r9, #43274	; 0xa90a
d0012660:	430a990c 	movwmi	r9, #43276	; 0xa90c
d0012664:	ea42990d 	b	0xd10b8aa0
d0012668:	430a020b 	movwmi	r0, #41483	; 0xa20b
d001266c:	430a990e 	movwmi	r9, #43278	; 0xa90e
d0012670:	d123431a 			; <UNDEFINED> instruction: 0xd123431a
d0012674:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0012678:	b158fdef 	cmplt	r8, pc, ror #27	; <UNPREDICTABLE>
d001267c:	b94b6da3 	stmdblt	fp, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0012680:	35acf8df 	strcc	pc, [ip, #2271]!	; 0x8df
d0012684:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0012688:	9b083516 	blls	0xd021fae8
d001268c:	3a18e9c4 	bcc	0xd064cda4
d0012690:	66a39b09 	strtvs	r9, [r3], r9, lsl #22
d0012694:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0012698:	2220fdfc 	eorcs	pc, r0, #252, 26	; 0x3f00
d001269c:	ee182100 	mufe	f2, f0, f0
d00126a0:	f0090a10 			; <UNDEFINED> instruction: 0xf0090a10
d00126a4:	f44ffedd 			; <UNDEFINED> instruction: 0xf44ffedd
d00126a8:	ee187393 	mrc	3, 0, r7, cr8, cr3, {4}
d00126ac:	61532a10 	cmpvs	r3, r0, lsl sl
d00126b0:	4620e6b9 			; <UNDEFINED> instruction: 0x4620e6b9
d00126b4:	f7fd930f 			; <UNDEFINED> instruction: 0xf7fd930f
d00126b8:	9b0ffd8e 	blls	0xd0411cf8
d00126bc:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d00126c0:	f7fd930f 			; <UNDEFINED> instruction: 0xf7fd930f
d00126c4:	2820fd7f 	stmdacs	r0!, {r0, r1, r2, r3, r4, r5, r6, r8, sl, fp, ip, sp, lr, pc}
d00126c8:	d0f29b0f 	rscsle	r9, r2, pc, lsl #22
d00126cc:	d0f02809 	rscsle	r2, r0, r9, lsl #16
d00126d0:	46209311 			; <UNDEFINED> instruction: 0x46209311
d00126d4:	930f6823 	movwls	r6, #63523	; 0xf823
d00126d8:	931068e3 	tstls	r0, #14876672	; 0xe30000
d00126dc:	9b0f9a10 	blls	0xd03f8f24
d00126e0:	f7fd189f 			; <UNDEFINED> instruction: 0xf7fd189f
d00126e4:	6821fdd6 	stmdavs	r1!, {r1, r2, r4, r6, r7, r8, sl, fp, ip, sp, lr, pc}
d00126e8:	46bc68e2 	ldrtmi	r6, [ip], r2, ror #17
d00126ec:	44119b11 	ldrmi	r9, [r1], #-2833	; 0xfffff4ef
d00126f0:	0201f10c 	andeq	pc, r1, #12, 2
d00126f4:	d301428a 	movwle	r4, #4746	; 0x128a
d00126f8:	e033468c 	eors	r4, r3, ip, lsl #13
d00126fc:	0c01f812 	stceq	8, cr15, [r1], {18}
d0012700:	d15a282f 	cmple	sl, pc, lsr #16
d0012704:	282f7810 	stmdacs	pc!, {r4, fp, ip, sp, lr}	; <UNPREDICTABLE>
d0012708:	282ad02c 	stmdacs	sl!, {r2, r3, r5, ip, lr, pc}
d001270c:	f10cd155 			; <UNDEFINED> instruction: 0xf10cd155
d0012710:	1c500202 	lfmne	f0, 2, [r0], {2}
d0012714:	d2174288 	andsle	r4, r7, #136, 4	; 0x80000008
d0012718:	6c01f810 	stcvs	8, cr15, [r1], {16}
d001271c:	d1112e2a 	tstle	r1, sl, lsr #28
d0012720:	2e2f7806 	cdpcs	8, 2, cr7, cr15, cr6, {0}
d0012724:	3202d10e 	andcc	sp, r2, #-2147483645	; 0x80000003
d0012728:	d21a428a 	andsle	r4, sl, #-1610612728	; 0xa0000008
d001272c:	0b01f812 	bleq	0xd009077c
d0012730:	d0f92820 	rscsle	r2, r9, r0, lsr #16
d0012734:	d0f72809 	rscsle	r2, r7, r9, lsl #16
d0012738:	b99a6da2 	ldmiblt	sl, {r1, r5, r7, r8, sl, fp, sp, lr}
d001273c:	24f4f8df 	ldrbtcs	pc, [r4], #2271	; 0x8df	; <UNPREDICTABLE>
d0012740:	e006447a 	and	r4, r6, sl, ror r4
d0012744:	e7e44602 	strb	r4, [r4, r2, lsl #12]!
d0012748:	b95a6da2 	ldmdblt	sl, {r1, r5, r7, r8, sl, fp, sp, lr}^
d001274c:	24e8f8df 	strbtcs	pc, [r8], #2271	; 0x8df	; <UNPREDICTABLE>
d0012750:	e9c4447a 	stmib	r4, {r1, r3, r4, r5, r6, sl, lr}^
d0012754:	9a082516 	bls	0xd021bbb4
d0012758:	2a18e9c4 	bcs	0xd064ce70
d001275c:	66a29a09 	strtvs	r9, [r2], r9, lsl #20
d0012760:	d1e9e000 	mvnle	lr, r0
d0012764:	42be4666 	adcsmi	r4, lr, #106954752	; 0x6600000
d0012768:	f816d906 			; <UNDEFINED> instruction: 0xf816d906
d001276c:	1e712c01 	cdpne	12, 7, cr2, cr1, cr1, {0}
d0012770:	d0242a20 	eorle	r2, r4, r0, lsr #20
d0012774:	d0222a09 	eorle	r2, r2, r9, lsl #20
d0012778:	93114620 	tstls	r1, #32, 12	; 0x2000000
d001277c:	fd6cf7fd 	stc2l	7, cr15, [ip, #-1012]!	; 0xfffffc0c
d0012780:	46809b0c 	strmi	r9, [r0], ip, lsl #22
d0012784:	000bea43 	andeq	lr, fp, r3, asr #20
d0012788:	43039b0d 	movwmi	r9, #15117	; 0x3b0d
d001278c:	f0009b11 			; <UNDEFINED> instruction: 0xf0009b11
d0012790:	f24d8090 	vqadd.s8	d24, d29, d0
d0012794:	58e3030c 	stmiapl	r3!, {r2, r3, r8, r9}^
d0012798:	d1122b20 	tstle	r2, r0, lsr #22
d001279c:	2b006da3 	blcs	0xd002de30
d00127a0:	af7bf47f 	svcge	0x007bf47f
d00127a4:	3494f8df 	ldrcc	pc, [r4], #2271	; 0x8df
d00127a8:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d00127ac:	9b083516 	blls	0xd021fc0c
d00127b0:	3a18e9c4 	bcc	0xd064cec8
d00127b4:	66a39b09 	strtvs	r9, [r3], r9, lsl #22
d00127b8:	4694e76f 	ldrmi	lr, [r4], pc, ror #14
d00127bc:	460ee798 			; <UNDEFINED> instruction: 0x460ee798
d00127c0:	f1b8e7d1 			; <UNDEFINED> instruction: 0xf1b8e7d1
d00127c4:	d0720f00 	rsbsle	r0, r2, r0, lsl #30
d00127c8:	d0542800 	subsle	r2, r4, r0, lsl #16
d00127cc:	d00542be 			; <UNDEFINED> instruction: 0xd00542be
d00127d0:	9a109b0f 	bls	0xd0439414
d00127d4:	f7fd5c98 			; <UNDEFINED> instruction: 0xf7fd5c98
d00127d8:	b958fdac 	ldmdblt	r8, {r2, r3, r5, r7, r8, sl, fp, ip, sp, lr, pc}^
d00127dc:	b94b6da3 	stmdblt	fp, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d00127e0:	345cf8df 	ldrbcc	pc, [ip], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d00127e4:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d00127e8:	9b083516 	blls	0xd021fc48
d00127ec:	3a18e9c4 	bcc	0xd064cf04
d00127f0:	66a39b09 	strtvs	r9, [r3], r9, lsl #22
d00127f4:	454e46b9 	strbmi	r4, [lr, #-1721]	; 0xfffff947
d00127f8:	d917464a 	ldmdble	r7, {r1, r3, r6, r9, sl, lr}
d00127fc:	f1097811 			; <UNDEFINED> instruction: 0xf1097811
d0012800:	46080901 	strmi	r0, [r8], -r1, lsl #18
d0012804:	fd95f7fd 	ldc2	7, cr15, [r5, #1012]	; 0x3f4
d0012808:	d1f42800 	mvnsle	r2, r0, lsl #16
d001280c:	29093930 	stmdbcs	r9, {r4, r5, r8, fp, ip, sp}
d0012810:	6da3d9f1 			; <UNDEFINED> instruction: 0x6da3d9f1
d0012814:	f8dfb95b 			; <UNDEFINED> instruction: 0xf8dfb95b
d0012818:	447b342c 	ldrbtmi	r3, [fp], #-1068	; 0xfffffbd4
d001281c:	3516e9c4 	ldrcc	lr, [r6, #-2500]	; 0xfffff63c
d0012820:	e9c49b08 	stmib	r4, {r3, r8, r9, fp, ip, pc}^
d0012824:	9b093a18 	blls	0xd026108c
d0012828:	e00066a3 	and	r6, r0, r3, lsr #13
d001282c:	1bd2d1f1 	blne	0xcf4c6ff8
d0012830:	46204639 			; <UNDEFINED> instruction: 0x46204639
d0012834:	fd5bf7fd 	ldc2l	7, cr15, [fp, #-1012]	; 0xfffffc0c
d0012838:	0f00f1bb 	svceq	0x0000f1bb
d001283c:	43c0d100 	bicmi	sp, r0, #0, 2
d0012840:	f24d0fc0 	vmax.f32	q8, <illegal reg q14.5>, q0
d0012844:	f1b8030c 			; <UNDEFINED> instruction: 0xf1b8030c
d0012848:	58e10f00 	stmiapl	r1!, {r8, r9, sl, fp}^
d001284c:	2000bf08 	andcs	fp, r0, r8, lsl #30
d0012850:	50e21c4a 	rscpl	r1, r2, sl, asr #24
d0012854:	0481eb04 	streq	lr, [r1], #2820	; 0xb04
d0012858:	738cf64c 	orrvc	pc, ip, #76, 12	; 0x4c00000
d001285c:	f8042200 			; <UNDEFINED> instruction: 0xf8042200
d0012860:	f64c8003 			; <UNDEFINED> instruction: 0xf64c8003
d0012864:	54e0738d 	strbtpl	r7, [r0], #909	; 0x38d
d0012868:	738ef64c 	orrvc	pc, lr, #76, 12	; 0x4c00000
d001286c:	f64c54e0 			; <UNDEFINED> instruction: 0xf64c54e0
d0012870:	54e2738f 	strbtpl	r7, [r2], #911	; 0x38f
d0012874:	2200e711 	andcs	lr, r0, #4456448	; 0x440000
d0012878:	96062300 	strls	r2, [r6], -r0, lsl #6
d001287c:	9705ae29 	strls	sl, [r5, -r9, lsr #28]
d0012880:	e9cd466d 	stmib	sp, {r0, r2, r3, r5, r6, r9, sl, lr}^
d0012884:	ab122312 	blge	0xd049b4d4
d0012888:	ce0f9307 	cdpgt	3, 0, cr9, cr15, cr7, {0}
d001288c:	6833c50f 	ldmdavs	r3!, {r0, r1, r2, r3, r8, sl, lr, pc}
d0012890:	602b4620 	eorvs	r4, fp, r0, lsr #12
d0012894:	cb0eab26 	blgt	0xd03bd534
d0012898:	fbaaf7fe 	blx	0xcead089a
d001289c:	d0d02800 	sbcsle	r2, r0, r0, lsl #16
d00128a0:	2312e9dd 	tstcs	r2, #3620864	; 0x374000
d00128a4:	bf144313 	svclt	0x00144313
d00128a8:	20002001 	andcs	r2, r0, r1
d00128ac:	4640e7c9 	strbmi	lr, [r0], -r9, asr #15
d00128b0:	9a0ee7c7 	bls	0xd03cc7d4
d00128b4:	0002ea49 	andeq	lr, r2, r9, asr #20
d00128b8:	0203ea50 	andeq	lr, r3, #80, 20	; 0x50000
d00128bc:	80a2f000 	adchi	pc, r2, r0
d00128c0:	21fcf8d4 	ldrsbcs	pc, [ip, #132]!	; 0x84	; <UNPREDICTABLE>
d00128c4:	eb04b112 	bl	0xd013ed14
d00128c8:	6f921242 	svcvs	0x00921242
d00128cc:	010cf24d 	tsteq	ip, sp, asr #4	; <UNPREDICTABLE>
d00128d0:	42915861 	addsmi	r5, r1, #6356992	; 0x610000
d00128d4:	6da3d806 	stcvs	8, cr13, [r3, #24]!
d00128d8:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d00128dc:	4bdaaede 	blmi	0xcf6be45c
d00128e0:	e762447b 			; <UNDEFINED> instruction: 0xe762447b
d00128e4:	f1b91e4a 			; <UNDEFINED> instruction: 0xf1b91e4a
d00128e8:	d0100f00 	andsle	r0, r0, r0, lsl #30
d00128ec:	d00a42be 			; <UNDEFINED> instruction: 0xd00a42be
d00128f0:	b9436da3 	stmdblt	r3, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d00128f4:	447b4bd5 	ldrbtmi	r4, [fp], #-3029	; 0xfffff42b
d00128f8:	3516e9c4 	ldrcc	lr, [r6, #-2500]	; 0xfffff63c
d00128fc:	e9c49b08 	stmib	r4, {r3, r8, r9, fp, ip, pc}^
d0012900:	9b093a18 	blls	0xd0261168
d0012904:	f24d66a3 	vmax.s8	d22, d29, d19
d0012908:	50e2030c 	rscpl	r0, r2, ip, lsl #6
d001290c:	ea4fe6c5 	b	0xd140c428
d0012910:	b3630881 	cmnlt	r3, #8454144	; 0x810000
d0012914:	d10642be 			; <UNDEFINED> instruction: 0xd10642be
d0012918:	534ff502 	movtpl	pc, #62722	; 0xf502	; <UNPREDICTABLE>
d001291c:	eb043322 	bl	0xd011f5ac
d0012920:	79db0383 	ldmibvc	fp, {r0, r1, r7, r8, r9}^
d0012924:	6da3b153 	stfvsd	f3, [r3, #332]!	; 0x14c
d0012928:	4bc9b943 	blmi	0xcf280e3c
d001292c:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0012930:	9b083516 	blls	0xd021fd90
d0012934:	3a18e9c4 	bcc	0xd064d04c
d0012938:	66a39b09 	strtvs	r9, [r3], r9, lsl #22
d001293c:	f64c4444 			; <UNDEFINED> instruction: 0xf64c4444
d0012940:	5ce37388 	stclpl	3, cr7, [r3], #544	; 0x220
d0012944:	f64cb13b 			; <UNDEFINED> instruction: 0xf64cb13b
d0012948:	f814738a 			; <UNDEFINED> instruction: 0xf814738a
d001294c:	fab99003 	blx	0xcee76960
d0012950:	ea4ff989 	b	0xd1410f7c
d0012954:	f64c1959 			; <UNDEFINED> instruction: 0xf64c1959
d0012958:	f64c7389 			; <UNDEFINED> instruction: 0xf64c7389
d001295c:	f804728a 			; <UNDEFINED> instruction: 0xf804728a
d0012960:	23019003 	movwcs	r9, #4099	; 0x1003
d0012964:	f64c54a3 			; <UNDEFINED> instruction: 0xf64c54a3
d0012968:	54a3728b 	strtpl	r7, [r3], #651	; 0x28b
d001296c:	44a0e695 	strtmi	lr, [r0], #1685	; 0x695
d0012970:	738bf64c 	orrvc	pc, fp, #76, 12	; 0x4c00000
d0012974:	3003f818 	andcc	pc, r3, r8, lsl r8	; <UNPREDICTABLE>
d0012978:	6da3b153 	stfvsd	f3, [r3, #332]!	; 0x14c
d001297c:	4bb5b943 	blmi	0xced80e90
d0012980:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0012984:	9b083516 	blls	0xd021fde4
d0012988:	3a18e9c4 	bcc	0xd064d0a0
d001298c:	66a39b09 	strtvs	r9, [r3], r9, lsl #22
d0012990:	22002300 	andcs	r2, r0, #0, 6
d0012994:	2312e9cd 	tstcs	r2, #3358720	; 0x334000
d0012998:	7388f64c 	orrvc	pc, r8, #76, 12	; 0x4c00000
d001299c:	3003f818 	andcc	pc, r3, r8, lsl r8	; <UNPREDICTABLE>
d00129a0:	f64cb923 			; <UNDEFINED> instruction: 0xf64cb923
d00129a4:	f8087289 			; <UNDEFINED> instruction: 0xf8087289
d00129a8:	e6763002 	ldrbt	r3, [r6], -r2
d00129ac:	798af64c 	stmibvc	sl, {r2, r3, r6, r9, sl, ip, sp, lr, pc}
d00129b0:	3009f818 	andcc	pc, r9, r8, lsl r8	; <UNPREDICTABLE>
d00129b4:	f64cb12b 			; <UNDEFINED> instruction: 0xf64cb12b
d00129b8:	22007389 	andcs	r7, r0, #603979778	; 0x24000002
d00129bc:	2003f808 	andcs	pc, r3, r8, lsl #16
d00129c0:	9606e66b 	strls	lr, [r6], -fp, ror #12
d00129c4:	ae29ab12 	vmovge.32	d9[1], sl
d00129c8:	93079705 	movwls	r9, #30469	; 0x7705
d00129cc:	ce0f466d 	cfmadd32gt	mvax3, mvfx4, mvfx15, mvfx13
d00129d0:	6833c50f 	ldmdavs	r3!, {r0, r1, r2, r3, r8, sl, lr, pc}
d00129d4:	602b4620 	eorvs	r4, fp, r0, lsr #12
d00129d8:	cb0eab26 	blgt	0xd03bd678
d00129dc:	fb08f7fe 	blx	0xd02509de
d00129e0:	2312e9dd 	tstcs	r2, #3620864	; 0x374000
d00129e4:	0103ea52 	tsteq	r3, r2, asr sl
d00129e8:	7189f64c 	orrvc	pc, r9, ip, asr #12
d00129ec:	2001bf14 	andcs	fp, r1, r4, lsl pc
d00129f0:	43132000 	tstmi	r3, #0
d00129f4:	0001f808 	andeq	pc, r1, r8, lsl #16
d00129f8:	ae4ff43f 	mcrge	4, 2, pc, cr15, cr15, {1}	; <UNPREDICTABLE>
d00129fc:	f8082301 			; <UNDEFINED> instruction: 0xf8082301
d0012a00:	e64a3009 	strb	r3, [sl], -r9
d0012a04:	0f00f1b8 	svceq	0x0000f1b8
d0012a08:	ae47f43f 	mcrge	4, 2, pc, cr7, cr15, {1}	; <UNPREDICTABLE>
d0012a0c:	9a0a9b0b 	bls	0xd02b9640
d0012a10:	f43f4313 			; <UNDEFINED> instruction: 0xf43f4313
d0012a14:	42beae42 	adcsmi	sl, lr, #1056	; 0x420
d0012a18:	9b0fd023 	blls	0xd0406aac
d0012a1c:	5c989a10 	vldmiapl	r8, {s18-s33}
d0012a20:	fc87f7fd 	stc2	7, cr15, [r7], {253}	; 0xfd
d0012a24:	46b8b1e8 	ldrtmi	fp, [r8], r8, ror #3
d0012a28:	46434546 	strbmi	r4, [r3], -r6, asr #10
d0012a2c:	4642d90d 	strbmi	sp, [r2], -sp, lsl #18
d0012a30:	802cf8cd 	eorhi	pc, ip, sp, asr #17
d0012a34:	1b01f812 	blne	0xd0090a84
d0012a38:	f7fd4608 			; <UNDEFINED> instruction: 0xf7fd4608
d0012a3c:	b9b8fc7a 	ldmiblt	r8!, {r1, r3, r4, r5, r6, sl, fp, ip, sp, lr, pc}
d0012a40:	0030f1a1 	eorseq	pc, r0, r1, lsr #3
d0012a44:	28099b0b 	stmdacs	r9, {r0, r1, r3, r8, r9, fp, ip, pc}
d0012a48:	eba8d912 	bl	0xcea48e98
d0012a4c:	f1bb0b07 			; <UNDEFINED> instruction: 0xf1bb0b07
d0012a50:	d90f0f3f 	stmdble	pc, {r0, r1, r2, r3, r4, r5, r8, r9, sl, fp}	; <UNPREDICTABLE>
d0012a54:	2b006da3 	blcs	0xd002e0e8
d0012a58:	ae1ff47f 	mrcge	4, 0, APSR_nzcv, cr15, cr15, {3}
d0012a5c:	447b4b7e 	ldrbtmi	r4, [fp], #-2942	; 0xfffff482
d0012a60:	6da3e6a3 	stcvs	6, cr14, [r3, #652]!	; 0x28c
d0012a64:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0012a68:	4b7cae18 	blmi	0xd1f3e2d0
d0012a6c:	e69c447b 			; <UNDEFINED> instruction: 0xe69c447b
d0012a70:	e7d94690 	bfi	r4, r0, #13, #13
d0012a74:	4639465a 			; <UNDEFINED> instruction: 0x4639465a
d0012a78:	930b4620 	movwls	r4, #46624	; 0xb620
d0012a7c:	fc37f7fd 	ldc2	7, cr15, [r7], #-1012	; 0xfffffc0c
d0012a80:	46819a0a 	strmi	r9, [r1], sl, lsl #20
d0012a84:	b34a9b0b 	movtlt	r9, #43787	; 0xab0b
d0012a88:	d9114546 	ldmdble	r1, {r1, r2, r6, r8, sl, lr}
d0012a8c:	3b01f818 	blcc	0xd0090af4
d0012a90:	d0f92b20 	rscsle	r2, r9, r0, lsr #22
d0012a94:	d0f72b09 	rscsle	r2, r7, r9, lsl #22
d0012a98:	b9536da3 	ldmdblt	r3, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0012a9c:	447b4b70 	ldrbtmi	r4, [fp], #-2928	; 0xfffff490
d0012aa0:	3516e9c4 	ldrcc	lr, [r6, #-2500]	; 0xfffff63c
d0012aa4:	e9c49b08 	stmib	r4, {r3, r8, r9, fp, ip, pc}^
d0012aa8:	9b093a18 	blls	0xd0261310
d0012aac:	e00066a3 	and	r6, r0, r3, lsr #13
d0012ab0:	f1b9d1f2 			; <UNDEFINED> instruction: 0xf1b9d1f2
d0012ab4:	f6ff0f00 			; <UNDEFINED> instruction: 0xf6ff0f00
d0012ab8:	f64cadf0 			; <UNDEFINED> instruction: 0xf64cadf0
d0012abc:	22487388 	subcs	r7, r8, #136, 6	; 0x20000002
d0012ac0:	fb0258e1 	blx	0xd00a8e4e
d0012ac4:	39014009 	stmdbcc	r1, {r0, r3, lr}
d0012ac8:	f64a50e1 			; <UNDEFINED> instruction: 0xf64a50e1
d0012acc:	fb023388 	blx	0xd009f8f6
d0012ad0:	44184101 	ldrmi	r4, [r8], #-257	; 0xfffffeff
d0012ad4:	f0094419 			; <UNDEFINED> instruction: 0xf0094419
d0012ad8:	e5defcd1 	ldrb	pc, [lr, #3281]	; 0xcd1	; <UNPREDICTABLE>
d0012adc:	d9134546 	ldmdble	r3, {r1, r2, r6, r8, sl, lr}
d0012ae0:	3000f898 	mulcc	r0, r8, r8
d0012ae4:	d1062b28 	tstle	r6, r8, lsr #22
d0012ae8:	2b006da3 	blcs	0xd002e17c
d0012aec:	add5f47f 	cfldrdge	mvd15, [r5, #508]	; 0x1fc
d0012af0:	447b4b5c 	ldrbtmi	r4, [fp], #-2908	; 0xfffff4a4
d0012af4:	4546e659 	strbmi	lr, [r6, #-1625]	; 0xfffff9a7
d0012af8:	d0054643 	andle	r4, r5, r3, asr #12
d0012afc:	2b01f818 	blcs	0xd0090b64
d0012b00:	d0f82a20 	rscsle	r2, r8, r0, lsr #20
d0012b04:	d0f62a09 	rscsle	r2, r6, r9, lsl #20
d0012b08:	21002001 	tstcs	r0, r1
d0012b0c:	e9cd429e 	stmib	sp, {r1, r2, r3, r4, r7, r9, lr}^
d0012b10:	d0130112 	andsle	r0, r3, r2, lsl r1
d0012b14:	aa129606 	bge	0xd04b8334
d0012b18:	9305ae29 	movwls	sl, #24105	; 0x5e29
d0012b1c:	46ec9207 	strbtmi	r9, [ip], r7, lsl #4
d0012b20:	e8acce0f 	stmia	ip!, {r0, r1, r2, r3, r9, sl, fp, lr, pc}
d0012b24:	6833000f 	ldmdavs	r3!, {r0, r1, r2, r3}
d0012b28:	f8cc4620 			; <UNDEFINED> instruction: 0xf8cc4620
d0012b2c:	ab263000 	blge	0xd099eb34
d0012b30:	f7fecb0e 			; <UNDEFINED> instruction: 0xf7fecb0e
d0012b34:	2800fa5d 	stmdacs	r0, {r0, r2, r3, r4, r6, r9, fp, ip, sp, lr, pc}
d0012b38:	adaff43f 	cfstrsge	mvf15, [pc, #252]!	; 0xd0012c3c
d0012b3c:	0f00f1b9 	svceq	0x0000f1b9
d0012b40:	f64cda0e 			; <UNDEFINED> instruction: 0xf64cda0e
d0012b44:	58e07388 	stmiapl	r0!, {r3, r7, r8, r9, ip, sp, lr}^
d0012b48:	d1062880 	smlabble	r6, r0, r8, r2
d0012b4c:	2b006da3 	blcs	0xd002e1e0
d0012b50:	ada3f47f 	cfstrsge	mvf15, [r3, #508]!	; 0x1fc
d0012b54:	447b4b44 	ldrbtmi	r4, [fp], #-2884	; 0xfffff4bc
d0012b58:	1c42e627 	mcrrne	6, 2, lr, r2, cr7
d0012b5c:	50e24681 	rscpl	r4, r2, r1, lsl #13
d0012b60:	f64a2048 			; <UNDEFINED> instruction: 0xf64a2048
d0012b64:	465a3588 	ldrbmi	r3, [sl], -r8, lsl #11
d0012b68:	fb004639 	blx	0xd0024456
d0012b6c:	eb09f909 	bl	0xd0290f98
d0012b70:	44200005 	strtmi	r0, [r0], #-5
d0012b74:	f009444c 			; <UNDEFINED> instruction: 0xf009444c
d0012b78:	2300fc81 	movwcs	pc, #3201	; 0xc81	; <UNPREDICTABLE>
d0012b7c:	f50444a3 			; <UNDEFINED> instruction: 0xf50444a3
d0012b80:	f80b442b 			; <UNDEFINED> instruction: 0xf80b442b
d0012b84:	e9dd3005 	ldmib	sp, {r0, r2, ip, sp}^
d0012b88:	e9c42312 	stmib	r4, {r1, r4, r8, r9, sp}^
d0012b8c:	e5842332 	str	r2, [r4, #818]	; 0x332
d0012b90:	f47f2a05 			; <UNDEFINED> instruction: 0xf47f2a05
d0012b94:	4935abc2 	ldmdbmi	r5!, {r1, r6, r7, r8, r9, fp, sp, pc}
d0012b98:	920b4638 	andls	r4, fp, #56, 12	; 0x3800000
d0012b9c:	447946cb 	ldrbtmi	r4, [r9], #-1739	; 0xfffff935
d0012ba0:	f00946c8 			; <UNDEFINED> instruction: 0xf00946c8
d0012ba4:	fab0fc7b 	blx	0xcec51d98
d0012ba8:	4931f380 	ldmdbmi	r1!, {r7, r8, r9, ip, sp, lr, pc}
d0012bac:	095b4638 	ldmdbeq	fp, {r3, r4, r5, r9, sl, lr}^
d0012bb0:	44799a0b 	ldrbtmi	r9, [r9], #-2571	; 0xfffff5f5
d0012bb4:	930a464e 	movwls	r4, #42574	; 0xa64e
d0012bb8:	fc70f009 	ldc2l	0, cr15, [r0], #-36	; 0xffffffdc
d0012bbc:	f380fab0 			; <UNDEFINED> instruction: 0xf380fab0
d0012bc0:	902cf8cd 	eorls	pc, ip, sp, asr #17
d0012bc4:	930c095b 	movwls	r0, #51547	; 0xc95b
d0012bc8:	2205492a 	andcs	r4, r5, #688128	; 0xa8000
d0012bcc:	44794638 	ldrbtmi	r4, [r9], #-1592	; 0xfffff9c8
d0012bd0:	fc64f009 	stc2l	0, cr15, [r4], #-36	; 0xffffffdc
d0012bd4:	fab02300 	blx	0xcec1b7dc
d0012bd8:	930ef980 	movwls	pc, #59776	; 0xe980	; <UNPREDICTABLE>
d0012bdc:	1959ea4f 	ldmdbne	r9, {r0, r1, r2, r3, r6, r9, fp, sp, lr, pc}^
d0012be0:	f7ff930d 			; <UNDEFINED> instruction: 0xf7ff930d
d0012be4:	bf00bbd5 	svclt	0x0000bbd5
d0012be8:	fffffc50 			; <UNDEFINED> instruction: 0xfffffc50
d0012bec:	fffffc10 			; <UNDEFINED> instruction: 0xfffffc10
d0012bf0:	fffffc07 			; <UNDEFINED> instruction: 0xfffffc07
d0012bf4:	fffffbf8 			; <UNDEFINED> instruction: 0xfffffbf8
d0012bf8:	fffffbd6 			; <UNDEFINED> instruction: 0xfffffbd6
d0012bfc:	fffffbc5 			; <UNDEFINED> instruction: 0xfffffbc5
d0012c00:	fffffb93 			; <UNDEFINED> instruction: 0xfffffb93
d0012c04:	fffffade 			; <UNDEFINED> instruction: 0xfffffade
d0012c08:	fffffb08 			; <UNDEFINED> instruction: 0xfffffb08
d0012c0c:	fffffa8e 			; <UNDEFINED> instruction: 0xfffffa8e
d0012c10:	fffffaaa 			; <UNDEFINED> instruction: 0xfffffaaa
d0012c14:	fffffa7f 			; <UNDEFINED> instruction: 0xfffffa7f
d0012c18:	fffffafc 			; <UNDEFINED> instruction: 0xfffffafc
d0012c1c:	fffffa36 			; <UNDEFINED> instruction: 0xfffffa36
d0012c20:	fffffa29 			; <UNDEFINED> instruction: 0xfffffa29
d0012c24:	fffff9e6 			; <UNDEFINED> instruction: 0xfffff9e6
d0012c28:	fffffa01 			; <UNDEFINED> instruction: 0xfffffa01
d0012c2c:	fffff9c6 			; <UNDEFINED> instruction: 0xfffff9c6
d0012c30:	fffff890 			; <UNDEFINED> instruction: 0xfffff890
d0012c34:	fffff925 			; <UNDEFINED> instruction: 0xfffff925
d0012c38:	fffff8ea 			; <UNDEFINED> instruction: 0xfffff8ea
d0012c3c:	fffff8e5 			; <UNDEFINED> instruction: 0xfffff8e5
d0012c40:	fffff8c8 			; <UNDEFINED> instruction: 0xfffff8c8
d0012c44:	fffff8bb 			; <UNDEFINED> instruction: 0xfffff8bb
d0012c48:	fffff81d 			; <UNDEFINED> instruction: 0xfffff81d
d0012c4c:	fffff82f 			; <UNDEFINED> instruction: 0xfffff82f
d0012c50:	fffff816 			; <UNDEFINED> instruction: 0xfffff816
d0012c54:	fffff7dd 			; <UNDEFINED> instruction: 0xfffff7dd
d0012c58:	fffff736 			; <UNDEFINED> instruction: 0xfffff736
d0012c5c:	fffff703 			; <UNDEFINED> instruction: 0xfffff703
d0012c60:	fffff717 			; <UNDEFINED> instruction: 0xfffff717
d0012c64:	fffff6e0 			; <UNDEFINED> instruction: 0xfffff6e0
d0012c68:	fffff6ab 			; <UNDEFINED> instruction: 0xfffff6ab
d0012c6c:	fffff357 			; <UNDEFINED> instruction: 0xfffff357
d0012c70:	fffff349 			; <UNDEFINED> instruction: 0xfffff349
d0012c74:	fffff340 			; <UNDEFINED> instruction: 0xfffff340

Disassembly of section .text.advance:

d0012c78 <.text.advance>:
d0012c78:	f100b570 			; <UNDEFINED> instruction: 0xf100b570
d0012c7c:	46040638 			; <UNDEFINED> instruction: 0x46040638
d0012c80:	0518f100 	ldreq	pc, [r8, #-256]	; 0xffffff00
d0012c84:	ce0fb088 	cdpgt	0, 0, cr11, cr15, cr8, {4}
d0012c88:	e896c50f 	ldm	r6, {r0, r1, r2, r3, r8, sl, lr, pc}
d0012c8c:	e885000f 	stm	r5, {r0, r1, r2, r3}
d0012c90:	466d000f 	strbtmi	r0, [sp], -pc
d0012c94:	34384621 	ldrtcc	r4, [r8], #-1569	; 0xfffff9df
d0012c98:	f7fe4628 			; <UNDEFINED> instruction: 0xf7fe4628
d0012c9c:	cd0ffda9 	stcgt	13, cr15, [pc, #-676]	; 0xd0012a00
d0012ca0:	e895c40f 	ldm	r5, {r0, r1, r2, r3, sl, lr, pc}
d0012ca4:	e884000f 	stm	r4, {r0, r1, r2, r3}
d0012ca8:	b008000f 	andlt	r0, r8, pc
d0012cac:	Address 0x00000000d0012cac is out of bounds.


Disassembly of section .text.accept:

d0012cae <.text.accept>:
d0012cae:	6d83b508 	cfstr32vs	mvfx11, [r3, #32]
d0012cb2:	6ac2b933 	bvs	0xcf0c1186
d0012cb6:	d105428a 	smlabble	r5, sl, r2, r4
d0012cba:	ffddf7ff 			; <UNDEFINED> instruction: 0xffddf7ff
d0012cbe:	bd082001 	stclt	0, cr2, [r8, #-4]
d0012cc2:	e7fc2000 	ldrb	r2, [ip, r0]!
d0012cc6:	e7fa4618 			; <UNDEFINED> instruction: 0xe7fa4618

Disassembly of section .text.expect:

d0012cca <.text.expect>:
d0012cca:	4605b570 			; <UNDEFINED> instruction: 0x4605b570
d0012cce:	f7ff4616 			; <UNDEFINED> instruction: 0xf7ff4616
d0012cd2:	4604ffed 	strmi	pc, [r4], -sp, ror #31
d0012cd6:	4631b928 	ldrtmi	fp, [r1], -r8, lsr #18
d0012cda:	f7fd4628 			; <UNDEFINED> instruction: 0xf7fd4628
d0012cde:	4620fa64 	strtmi	pc, [r0], -r4, ror #20
d0012ce2:	2401bd70 	strcs	fp, [r1], #-3440	; 0xfffff290
d0012ce6:	Address 0x00000000d0012ce6 is out of bounds.


Disassembly of section .text.record_type:

d0012d50 <.text.record_type>:
d0012d50:	4ff7e92d 	svcmi	0x00f7e92d
d0012d54:	6ac6460d 	bvs	0xcf1a4590
d0012d58:	718bf46f 	orrvc	pc, fp, pc, ror #8
d0012d5c:	18734604 	ldmdane	r3!, {r2, r9, sl, lr}^
d0012d60:	d8362b01 	ldmdale	r6!, {r0, r8, r9, fp, sp}
d0012d64:	ff88f7ff 			; <UNDEFINED> instruction: 0xff88f7ff
d0012d68:	6b634a26 	blvs	0xd18e5608
d0012d6c:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d0012d70:	4620447a 			; <UNDEFINED> instruction: 0x4620447a
d0012d74:	9024f8d4 	ldrdls	pc, [r4], -r4	; <UNPREDICTABLE>
d0012d78:	8028f8d4 	ldrdhi	pc, [r8], -r4	; <UNPREDICTABLE>
d0012d7c:	7030f894 	mlasvc	r0, r4, r8, pc	; <UNPREDICTABLE>
d0012d80:	e9d49301 	ldmib	r4, {r0, r8, r9, ip, pc}^
d0012d84:	f7ffab06 			; <UNDEFINED> instruction: 0xf7ffab06
d0012d88:	b918ffa0 	ldmdblt	r8, {r5, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0012d8c:	b0032000 	andlt	r2, r3, r0
d0012d90:	8ff0e8bd 	svchi	0x00f0e8bd
d0012d94:	728cf5a6 	addvc	pc, ip, #696254464	; 0x29800000
d0012d98:	46204651 			; <UNDEFINED> instruction: 0x46204651
d0012d9c:	41534253 	cmpmi	r3, r3, asr r2
d0012da0:	f7fd465a 			; <UNDEFINED> instruction: 0xf7fd465a
d0012da4:	2800fbf5 	stmdacs	r0, {r0, r2, r4, r5, r6, r7, r8, r9, fp, ip, sp, lr, pc}
d0012da8:	f5b6da11 			; <UNDEFINED> instruction: 0xf5b6da11
d0012dac:	d00b7f8c 	andle	r7, fp, ip, lsl #31
d0012db0:	447b4b15 	ldrbtmi	r4, [fp], #-2837	; 0xfffff4eb
d0012db4:	b92a6da2 	stmdblt	sl!, {r1, r5, r7, r8, sl, fp, sp, lr}
d0012db8:	3916e9c4 	ldmdbcc	r6, {r2, r6, r7, r8, fp, sp, lr, pc}
d0012dbc:	e9c49b01 	stmib	r4, {r0, r8, r9, fp, ip, pc}^
d0012dc0:	66a38718 	ssatvs	r8, #4, r8, lsl #14
d0012dc4:	e7e22001 	strb	r2, [r2, r1]!
d0012dc8:	447b4b10 	ldrbtmi	r4, [fp], #-2832	; 0xfffff4f0
d0012dcc:	6028e7f2 	strdvs	lr, [r8], -r2	; <UNPREDICTABLE>
d0012dd0:	f240e7f8 	vaba.s8	q15, q8, q12
d0012dd4:	429e1301 	addsmi	r1, lr, #67108864	; 0x4000000
d0012dd8:	69c2d1d8 	stmibvs	r2, {r3, r4, r6, r7, r8, ip, lr, pc}^
d0012ddc:	f7fd6981 			; <UNDEFINED> instruction: 0xf7fd6981
d0012de0:	2800fc7c 	stmdacs	r0, {r2, r3, r4, r5, r6, sl, fp, ip, sp, lr, pc}
d0012de4:	2324dbd2 			; <UNDEFINED> instruction: 0x2324dbd2
d0012de8:	4000fb03 	andmi	pc, r0, r3, lsl #22
d0012dec:	30d8f500 	sbcscc	pc, r8, r0, lsl #10
d0012df0:	31ecf890 			; <UNDEFINED> instruction: 0x31ecf890
d0012df4:	d0c92bff 	strdle	r2, [r9], #191	; 0xbf
d0012df8:	602b4620 	eorvs	r4, fp, r0, lsr #12
d0012dfc:	ff3cf7ff 			; <UNDEFINED> instruction: 0xff3cf7ff
d0012e00:	bf00e7e0 	svclt	0x0000e7e0
d0012e04:	ffffffbd 			; <UNDEFINED> instruction: 0xffffffbd
d0012e08:	ffffff56 			; <UNDEFINED> instruction: 0xffffff56
d0012e0c:	ffffff1a 			; <UNDEFINED> instruction: 0xffffff1a

Disassembly of section .text.sizeof_operand:

d0012ff0 <.text.sizeof_operand>:
d0012ff0:	4ff0e92d 	svcmi	0x00f0e92d
d0012ff4:	21284604 			; <UNDEFINED> instruction: 0x21284604
d0012ff8:	8b02ed2d 	blhi	0xd00ce4b4
d0012ffc:	f7ffb08d 			; <UNDEFINED> instruction: 0xf7ffb08d
d0013000:	f240fe56 			; <UNDEFINED> instruction: 0xf240fe56
d0013004:	90041107 	andls	r1, r4, r7, lsl #2
d0013008:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d001300c:	b128fe50 	msrlt	R8_fiq, r0
d0013010:	4620212a 	strtmi	r2, [r0], -sl, lsr #2
d0013014:	fe4bf7ff 	mcr2	7, 2, pc, cr11, cr15, {7}	; <UNPREDICTABLE>
d0013018:	e0252704 	eor	r2, r5, r4, lsl #14
d001301c:	7184f44f 	orrvc	pc, r4, pc, asr #8
d0013020:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0013024:	b190fe44 	orrslt	pc, r0, r4, asr #28
d0013028:	4620212a 	strtmi	r2, [r0], -sl, lsr #2
d001302c:	fe3ff7ff 	mrc2	7, 1, pc, cr15, cr15, {7}
d0013030:	28004607 	stmdacs	r0, {r0, r1, r2, r9, sl, lr}
d0013034:	f8dfd1f0 			; <UNDEFINED> instruction: 0xf8dfd1f0
d0013038:	4620146c 	strtmi	r1, [r0], -ip, ror #8
d001303c:	f7fd4479 			; <UNDEFINED> instruction: 0xf7fd4479
d0013040:	4638f8b3 			; <UNDEFINED> instruction: 0x4638f8b3
d0013044:	ecbdb00d 	ldc	0, cr11, [sp], #52	; 0x34
d0013048:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d001304c:	f2408ff0 	vrecps.f32	q12, q8, q8
d0013050:	4620110b 	strtmi	r1, [r0], -fp, lsl #2
d0013054:	fe2bf7ff 	mcr2	7, 1, pc, cr11, cr15, {7}	; <UNPREDICTABLE>
d0013058:	212ab340 			; <UNDEFINED> instruction: 0x212ab340
d001305c:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0013060:	2800fe26 	stmdacs	r0, {r1, r2, r5, r9, sl, fp, ip, sp, lr, pc}
d0013064:	2701d1d8 			; <UNDEFINED> instruction: 0x2701d1d8
d0013068:	4620215b 			; <UNDEFINED> instruction: 0x4620215b
d001306c:	fe1ff7ff 	mrc2	7, 0, pc, cr15, cr15, {7}
d0013070:	d0602800 	rsble	r2, r0, r0, lsl #16
d0013074:	f5a36ae3 			; <UNDEFINED> instruction: 0xf5a36ae3
d0013078:	2b017381 	blcs	0xd006fe84
d001307c:	81e2f200 	mvnhi	pc, r0, lsl #4
d0013080:	2d006a25 	vstrcs	s12, [r0, #-148]	; 0xffffff6c
d0013084:	81def000 	bicshi	pc, lr, r0
d0013088:	2305fba7 	movwcs	pc, #23463	; 0x5ba7	; <UNPREDICTABLE>
d001308c:	f0402b00 			; <UNDEFINED> instruction: 0xf0402b00
d0013090:	462081d9 			; <UNDEFINED> instruction: 0x462081d9
d0013094:	fdf0f7ff 	ldc2l	7, cr15, [r0, #1020]!	; 0x3fc
d0013098:	240cf8df 	strcs	pc, [ip], #-2271	; 0xfffff721
d001309c:	4620215d 			; <UNDEFINED> instruction: 0x4620215d
d00130a0:	f7ff447a 			; <UNDEFINED> instruction: 0xf7ff447a
d00130a4:	b350fe12 	cmplt	r0, #288	; 0x120	; <UNPREDICTABLE>
d00130a8:	e044436f 	sub	r4, r4, pc, ror #6
d00130ac:	f2406ae5 	vpmax.s8	q11, q8, <illegal reg q10.5>
d00130b0:	429d1301 	addsmi	r1, sp, #67108864	; 0x4000000
d00130b4:	4afdd118 	bmi	0xcff8751c
d00130b8:	447a69e1 	ldrbtmi	r6, [sl], #-2529	; 0xfffff61f
d00130bc:	f7fd69a0 			; <UNDEFINED> instruction: 0xf7fd69a0
d00130c0:	b118fb78 	tstlt	r8, r8, ror fp	; <UNPREDICTABLE>
d00130c4:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d00130c8:	e7c6fdd7 			; <UNDEFINED> instruction: 0xe7c6fdd7
d00130cc:	42ab6ae3 	adcmi	r6, fp, #929792	; 0xe3000
d00130d0:	4af7d10a 	bmi	0xcfe07500
d00130d4:	447a69e1 	ldrbtmi	r6, [sl], #-2529	; 0xfffff61f
d00130d8:	f7fd69a0 			; <UNDEFINED> instruction: 0xf7fd69a0
d00130dc:	b118fb6a 	tstlt	r8, sl, ror #22	; <UNPREDICTABLE>
d00130e0:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d00130e4:	e793fdc9 	ldr	pc, [r3, r9, asr #27]
d00130e8:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d00130ec:	b1c8fb1b 	biclt	pc, r8, fp, lsl fp	; <UNPREDICTABLE>
d00130f0:	a90b2300 	stmdbge	fp, {r8, r9, sp}
d00130f4:	930b4620 	movwls	r4, #46624	; 0xb620
d00130f8:	fe2af7ff 	mcr2	7, 1, pc, cr10, cr15, {7}	; <UNPREDICTABLE>
d00130fc:	2700b908 	strcs	fp, [r0, -r8, lsl #18]
d0013100:	212ae79f 			; <UNDEFINED> instruction: 0x212ae79f
d0013104:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0013108:	2800fdd2 	stmdacs	r0, {r1, r4, r6, r7, r8, sl, fp, ip, sp, lr, pc}
d001310c:	9b0bd184 	blls	0xd0307724
d0013110:	721af44f 	andsvc	pc, sl, #1325400064	; 0x4f000000
d0013114:	4303fb02 	movwmi	pc, #15106	; 0x3b02	; <UNPREDICTABLE>
d0013118:	33bdf503 			; <UNDEFINED> instruction: 0x33bdf503
d001311c:	7068f8b3 	strhtvc	pc, [r8], #-131	; 0xffffff7d	; <UNPREDICTABLE>
d0013120:	e7a100bf 			; <UNDEFINED> instruction: 0xe7a100bf
d0013124:	f5a36ae3 			; <UNDEFINED> instruction: 0xf5a36ae3
d0013128:	2b017381 	blcs	0xd006ff34
d001312c:	2704d810 	smladcs	r4, r0, r8, sp
d0013130:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0013134:	9b04fda1 	blls	0xd01527c0
d0013138:	d0822b00 	addle	r2, r2, r0, lsl #22
d001313c:	21294add 	ldrdcs	r4, [r9, -sp]!
d0013140:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d0013144:	fdc1f7ff 	stc2l	7, cr15, [r1, #1020]	; 0x3fc
d0013148:	f47f2800 			; <UNDEFINED> instruction: 0xf47f2800
d001314c:	e7d6af7a 			; <UNDEFINED> instruction: 0xe7d6af7a
d0013150:	4620212a 	strtmi	r2, [r0], -sl, lsr #2
d0013154:	fdabf7ff 	stc2	7, cr15, [fp, #1020]!	; 0x3fc
d0013158:	4ad76a63 	bmi	0xcf5edaec
d001315c:	93014681 	movwls	r4, #5761	; 0x1681
d0013160:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d0013164:	447a6aa3 	ldrbtmi	r6, [sl], #-2723	; 0xfffff55d
d0013168:	f8944620 			; <UNDEFINED> instruction: 0xf8944620
d001316c:	9303a030 	movwls	sl, #12336	; 0x3030
d0013170:	e9d46b63 	ldmib	r4, {r0, r1, r5, r6, r8, r9, fp, sp, lr}^
d0013174:	93025606 	movwls	r5, #9734	; 0x2606
d0013178:	fda7f7ff 	stc2	7, cr15, [r7, #1020]!	; 0x3fc
d001317c:	d0be2800 	adcsle	r2, lr, r0, lsl #16
d0013180:	46294632 			; <UNDEFINED> instruction: 0x46294632
d0013184:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0013188:	2800fa64 	stmdacs	r0, {r2, r5, r6, r9, fp, ip, sp, lr, pc}
d001318c:	8172f280 	cmnhi	r2, r0, lsl #5	; <UNPREDICTABLE>
d0013190:	46294632 			; <UNDEFINED> instruction: 0x46294632
d0013194:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0013198:	2800fa7c 	stmdacs	r0, {r2, r3, r4, r5, r6, r9, fp, ip, sp, lr, pc}
d001319c:	6da7da0d 			; <UNDEFINED> instruction: 0x6da7da0d
d00131a0:	d1ac2f00 			; <UNDEFINED> instruction: 0xd1ac2f00
d00131a4:	447b4bc5 	ldrbtmi	r4, [fp], #-3013	; 0xfffff43b
d00131a8:	9b0165a3 	blls	0xd006c83c
d00131ac:	9b0365e3 	blls	0xd00ec940
d00131b0:	3a18e9c4 	bcc	0xd064d8c8
d00131b4:	66a39b02 	strtvs	r9, [r3], r2, lsl #22
d00131b8:	2334e743 	teqcs	r4, #17563648	; 0x10c0000
d00131bc:	4000fb03 	andmi	pc, r0, r3, lsl #22
d00131c0:	30aff500 	adccc	pc, pc, r0, lsl #10
d00131c4:	802cf890 	mlahi	ip, r0, r8, pc	; <UNPREDICTABLE>
d00131c8:	602ef890 	mlavs	lr, r0, r8, pc	; <UNPREDICTABLE>
d00131cc:	f1a86b41 			; <UNDEFINED> instruction: 0xf1a86b41
d00131d0:	2b04030d 	blcs	0xd0113e0c
d00131d4:	f1a8d933 			; <UNDEFINED> instruction: 0xf1a8d933
d00131d8:	25000307 	strcs	r0, [r0, #-775]	; 0xfffffcf9
d00131dc:	d9302b02 	ldmdble	r0!, {r1, r8, r9, fp, sp}
d00131e0:	0f10f1b8 	svceq	0x0010f1b8
d00131e4:	f1a8d02f 			; <UNDEFINED> instruction: 0xf1a8d02f
d00131e8:	427b0711 	rsbsmi	r0, fp, #4456448	; 0x440000
d00131ec:	f1b8417b 			; <UNDEFINED> instruction: 0xf1b8417b
d00131f0:	f0000f0a 			; <UNDEFINED> instruction: 0xf0000f0a
d00131f4:	f1b8814b 			; <UNDEFINED> instruction: 0xf1b8814b
d00131f8:	dd260f0e 	stcle	15, cr0, [r6, #-56]!	; 0xffffffc8
d00131fc:	0206f1a8 	andeq	pc, r6, #168, 2	; 0x2a
d0013200:	0b00f1d2 	bleq	0xd004f950
d0013204:	0b02eb4b 	bleq	0xd00cdf38
d0013208:	0f07f1b8 	svceq	0x0007f1b8
d001320c:	f1b8d026 			; <UNDEFINED> instruction: 0xf1b8d026
d0013210:	d0230f05 	eorle	r0, r3, r5, lsl #30
d0013214:	f1bbb385 			; <UNDEFINED> instruction: 0xf1bbb385
d0013218:	f0400f00 			; <UNDEFINED> instruction: 0xf0400f00
d001321c:	f44f8123 	vst4.8	{d24,d26,d28,d30}, [pc :128], r3
d0013220:	fb02721a 	blx	0xd00afa92
d0013224:	f5024206 			; <UNDEFINED> instruction: 0xf5024206
d0013228:	f8b232bd 			; <UNDEFINED> instruction: 0xf8b232bd
d001322c:	f1b97068 			; <UNDEFINED> instruction: 0xf1b97068
d0013230:	d11a0f00 	tstle	sl, r0, lsl #30
d0013234:	46cb00bf 			; <UNDEFINED> instruction: 0x46cb00bf
d0013238:	434fb39b 	movtmi	fp, #62363	; 0xf39b
d001323c:	2501e031 	strcs	lr, [r1, #-49]	; 0xffffffcf
d0013240:	2301e7ce 	movwcs	lr, #6094	; 0x17ce
d0013244:	2301e7d7 	movwcs	lr, #6103	; 0x17d7
d0013248:	f245e7d8 	vaba.s8	q15, <illegal reg q10.5>, q4
d001324c:	fa220214 	blx	0xd0893aa4
d0013250:	07d0f208 	ldrbeq	pc, [r0, r8, lsl #4]	; <UNPREDICTABLE>
d0013254:	f04fd5d2 			; <UNDEFINED> instruction: 0xf04fd5d2
d0013258:	e7d80b01 	ldrb	r0, [r8, r1, lsl #22]
d001325c:	f1b92701 			; <UNDEFINED> instruction: 0xf1b92701
d0013260:	d0e90f00 	rscle	r0, r9, r0, lsl #30
d0013264:	0f00f1bb 	svceq	0x0000f1bb
d0013268:	6da7d108 	stfvsd	f5, [r7, #32]!
d001326c:	f47f2f00 			; <UNDEFINED> instruction: 0xf47f2f00
d0013270:	4b93af46 	blmi	0xce4fef90
d0013274:	e797447b 			; <UNDEFINED> instruction: 0xe797447b
d0013278:	e7f02704 	ldrb	r2, [r0, r4, lsl #14]!
d001327c:	0f0ef1b8 	svceq	0x000ef1b8
d0013280:	f44fd120 	vst4.8	{d29,d31,d33,d35}, [pc :128], r0
d0013284:	fb03731a 	blx	0xd00efef6
d0013288:	f5034306 			; <UNDEFINED> instruction: 0xf5034306
d001328c:	f8b333bd 			; <UNDEFINED> instruction: 0xf8b333bd
d0013290:	00bf7068 	adcseq	r7, pc, r8, rrx
d0013294:	030ef1a8 	movweq	pc, #57768	; 0xe1a8	; <UNPREDICTABLE>
d0013298:	0b00f04f 	bleq	0xd004f3dc
d001329c:	415d425d 	cmpmi	sp, sp, asr r2
d00132a0:	215b465b 	cmpcs	fp, fp, asr r6
d00132a4:	93054620 	movwls	r4, #22048	; 0x5620
d00132a8:	fd01f7ff 	stc2	7, cr15, [r1, #-1020]	; 0xfffffc04
d00132ac:	9b05b390 	blls	0xd01800f4
d00132b0:	030bea53 	movweq	lr, #47699	; 0xba53
d00132b4:	6da7d117 	stfvsd	f5, [r7, #92]!	; 0x5c
d00132b8:	f47f2f00 			; <UNDEFINED> instruction: 0xf47f2f00
d00132bc:	4b81af20 	blmi	0xce07ef44
d00132c0:	e771447b 			; <UNDEFINED> instruction: 0xe771447b
d00132c4:	e7e52704 	strb	r2, [r5, r4, lsl #14]!
d00132c8:	d1072b5b 	tstle	r7, fp, asr fp
d00132cc:	46203701 	strtmi	r3, [r0], -r1, lsl #14
d00132d0:	fcd2f7ff 	ldc2l	7, cr15, [r2], {255}	; 0xff
d00132d4:	b9a5b947 	stmiblt	r5!, {r0, r1, r2, r6, r8, fp, ip, sp, pc}
d00132d8:	e01b2704 	ands	r2, fp, r4, lsl #14
d00132dc:	bf082b5d 	svclt	0x00082b5d
d00132e0:	37fff107 	ldrbcc	pc, [pc, r7, lsl #2]!	; <UNPREDICTABLE>
d00132e4:	2701e7f3 			; <UNDEFINED> instruction: 0x2701e7f3
d00132e8:	f5b36ae3 			; <UNDEFINED> instruction: 0xf5b36ae3
d00132ec:	d0027f80 	andle	r7, r2, r0, lsl #31
d00132f0:	2a006da2 	bcs	0xd002e980
d00132f4:	4974d0e8 	ldmdbmi	r4!, {r3, r5, r6, r7, ip, lr, pc}^
d00132f8:	44794620 	ldrbtmi	r4, [r9], #-1568	; 0xfffff9e0
d00132fc:	ff54f7fc 			; <UNDEFINED> instruction: 0xff54f7fc
d0013300:	f44fe6fd 	vst1.64	{d30-d32}, [pc :256]!
d0013304:	fb03731a 	blx	0xd00eff76
d0013308:	f5034306 			; <UNDEFINED> instruction: 0xf5034306
d001330c:	f8b333bd 			; <UNDEFINED> instruction: 0xf8b333bd
d0013310:	00bf7068 	adcseq	r7, pc, r8, rrx
d0013314:	f2406ae2 	vpmax.s8	q11, q8, q9
d0013318:	429a1321 	addsmi	r1, sl, #-2080374784	; 0x84000000
d001331c:	808ef040 	addhi	pc, lr, r0, asr #32
d0013320:	0f0ef1b8 	svceq	0x000ef1b8
d0013324:	f1b9d103 			; <UNDEFINED> instruction: 0xf1b9d103
d0013328:	f0000f00 			; <UNDEFINED> instruction: 0xf0000f00
d001332c:	6da78087 	stcvs	0, cr8, [r7, #540]!	; 0x21c
d0013330:	f47f2f00 			; <UNDEFINED> instruction: 0xf47f2f00
d0013334:	4b65aee4 	blmi	0xd197eecc
d0013338:	e735447b 			; <UNDEFINED> instruction: 0xe735447b
d001333c:	465a69a3 	ldrbmi	r6, [sl], -r3, lsr #19
d0013340:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d0013344:	ee084620 	cfmadd32	mvax1, mvfx4, mvfx8, mvfx0
d0013348:	69e33a10 	stmibvs	r3!, {r4, r9, fp, ip, sp}^
d001334c:	6a639309 	bvs	0xd18f7f78
d0013350:	6aa39305 	bvs	0xce8f7f6c
d0013354:	f8949308 			; <UNDEFINED> instruction: 0xf8949308
d0013358:	93073030 	movwls	r3, #28720	; 0x7030
d001335c:	93066b63 	movwls	r6, #27491	; 0x6b63
d0013360:	fcb3f7ff 	ldc2	7, cr15, [r3], #1020	; 0x3fc
d0013364:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0013368:	f44faeca 			; <UNDEFINED> instruction: 0xf44faeca
d001336c:	2700781a 	smladcs	r0, sl, r8, r7
d0013370:	fb089b09 	blx	0xd0239f9e
d0013374:	f508f806 			; <UNDEFINED> instruction: 0xf508f806
d0013378:	44a039bc 	strtmi	r3, [r0], #2492	; 0x9bc
d001337c:	0928f109 	stmdbeq	r8!, {r0, r3, r8, ip, sp, lr, pc}
d0013380:	38bdf508 	popcc	{r3, r8, sl, ip, sp, lr, pc}
d0013384:	f89844a1 			; <UNDEFINED> instruction: 0xf89844a1
d0013388:	42ba206a 	adcsmi	r2, sl, #106	; 0x6a
d001338c:	f44fd818 	vst2.8	{d29-d30}, [pc :64], r8
d0013390:	435e731a 	cmpmi	lr, #1744830464	; 0x68000000
d0013394:	f50219a2 			; <UNDEFINED> instruction: 0xf50219a2
d0013398:	f89232bd 			; <UNDEFINED> instruction: 0xf89232bd
d001339c:	42ba206a 	adcsmi	r2, sl, #106	; 0x6a
d00133a0:	6da7d11c 	stfvsd	f5, [r7, #112]!	; 0x70
d00133a4:	f47f2f00 			; <UNDEFINED> instruction: 0xf47f2f00
d00133a8:	4b49aeaa 	blmi	0xd127ee58
d00133ac:	65a3447b 	strvs	r4, [r3, #1147]!	; 0x47b
d00133b0:	65e39b05 	strbvs	r9, [r3, #2821]!	; 0xb05
d00133b4:	66239b08 	strtvs	r9, [r3], -r8, lsl #22
d00133b8:	66639b07 	strbtvs	r9, [r3], -r7, lsl #22
d00133bc:	e6fa9b06 	ldrbt	r9, [sl], r6, lsl #22
d00133c0:	1004f8d9 	ldrdne	pc, [r4], -r9
d00133c4:	2a10ee18 	bcs	0xd044ec2c
d00133c8:	0b24f859 	bleq	0xd0951534
d00133cc:	f7fd9309 			; <UNDEFINED> instruction: 0xf7fd9309
d00133d0:	9b09f8d1 	blls	0xd029171c
d00133d4:	d1da2800 	bicsle	r2, sl, r0, lsl #16
d00133d8:	e7d43701 	ldrb	r3, [r4, r1, lsl #14]
d00133dc:	fb022224 	blx	0xd009bc76
d00133e0:	44276707 	strtmi	r6, [r7], #-1799	; 0xfffff8f9
d00133e4:	37bcf507 	ldrcc	pc, [ip, r7, lsl #10]!
d00133e8:	6048f897 	umaalvs	pc, r8, r7, r8	; <UNPREDICTABLE>
d00133ec:	bf132eff 	svclt	0x00132eff
d00133f0:	4306fb03 	movwmi	pc, #27395	; 0x6b03	; <UNPREDICTABLE>
d00133f4:	27042500 	strcs	r2, [r4, -r0, lsl #10]
d00133f8:	33bdf503 			; <UNDEFINED> instruction: 0x33bdf503
d00133fc:	f8b3bf1c 			; <UNDEFINED> instruction: 0xf8b3bf1c
d0013400:	00bf7068 	adcseq	r7, pc, r8, rrx
d0013404:	2b2e6ae3 	blcs	0xd0badf98
d0013408:	f240d004 	vhadd.s8	d29, d0, d4
d001340c:	42931221 	addsmi	r1, r3, #268435458	; 0x10000002
d0013410:	ae91f47f 	mrcge	4, 4, APSR_nzcv, cr1, cr15, {3}
d0013414:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0013418:	2d00fc2f 	stccs	12, cr15, [r0, #-188]	; 0xffffff44
d001341c:	6da3d18e 	stfvsd	f5, [r3, #568]!	; 0x238
d0013420:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0013424:	4b2bae6c 	blmi	0xd0afeddc
d0013428:	65a3447b 	strvs	r4, [r3, #1147]!	; 0x47b
d001342c:	65e39b01 	strbvs	r9, [r3, #2817]!	; 0xb01
d0013430:	e9c49b03 	stmib	r4, {r0, r1, r8, r9, fp, ip, pc}^
d0013434:	9b023a18 	blls	0xd00a1c9c
d0013438:	e66066a3 	strbt	r6, [r0], -r3, lsr #13
d001343c:	b098f8df 			; <UNDEFINED> instruction: 0xb098f8df
d0013440:	e7df44fb 			; <UNDEFINED> instruction: 0xe7df44fb
d0013444:	2f006da7 	svccs	0x00006da7
d0013448:	ae59f47f 	mrcge	4, 2, APSR_nzcv, cr9, cr15, {3}
d001344c:	6a604d23 	bvs	0xd18268e0
d0013450:	447d6aa1 	ldrbtmi	r6, [sp], #-2721	; 0xfffff55f
d0013454:	2030f894 	mlascs	r0, r4, r8, pc	; <UNPREDICTABLE>
d0013458:	e9c46b63 	stmib	r4, {r0, r1, r5, r6, r8, r9, fp, sp, lr}^
d001345c:	e9c45016 	stmib	r4, {r1, r2, r4, ip, lr}^
d0013460:	e6a81218 	ssat	r1, #9, r8, lsl #4
d0013464:	0f00f1b9 	svceq	0x0000f1b9
d0013468:	af08f47f 	svcge	0x0008f47f
d001346c:	27042501 	strcs	r2, [r4, -r1, lsl #10]
d0013470:	e6e146ab 	strbt	r4, [r1], fp, lsr #13
d0013474:	fb03232c 	blx	0xd00dc12e
d0013478:	f5004000 			; <UNDEFINED> instruction: 0xf5004000
d001347c:	f8903013 			; <UNDEFINED> instruction: 0xf8903013
d0013480:	f890830d 			; <UNDEFINED> instruction: 0xf890830d
d0013484:	f8b0630e 			; <UNDEFINED> instruction: 0xf8b0630e
d0013488:	e6a01316 	ssat	r1, #1, r6, lsl #6
d001348c:	d1e92d00 	mvnle	r2, r0, lsl #26
d0013490:	0f00f1b9 	svceq	0x0000f1b9
d0013494:	af16f47f 	svcge	0x0016f47f
d0013498:	f04f464d 			; <UNDEFINED> instruction: 0xf04f464d
d001349c:	27040b01 	strcs	r0, [r4, -r1, lsl #22]
d00134a0:	bf00e6ca 	svclt	0x0000e6ca
d00134a4:	fffffdd0 			; <UNDEFINED> instruction: 0xfffffdd0
d00134a8:	fffffeec 			; <UNDEFINED> instruction: 0xfffffeec
d00134ac:	fffffd78 			; <UNDEFINED> instruction: 0xfffffd78
d00134b0:	fffffd64 			; <UNDEFINED> instruction: 0xfffffd64
d00134b4:	fffffe6c 			; <UNDEFINED> instruction: 0xfffffe6c
d00134b8:	fffffcdc 			; <UNDEFINED> instruction: 0xfffffcdc
d00134bc:	fffffcc5 			; <UNDEFINED> instruction: 0xfffffcc5
d00134c0:	fffffc24 			; <UNDEFINED> instruction: 0xfffffc24
d00134c4:	fffffbf1 			; <UNDEFINED> instruction: 0xfffffbf1
d00134c8:	fffffcd6 			; <UNDEFINED> instruction: 0xfffffcd6
d00134cc:	fffffba3 			; <UNDEFINED> instruction: 0xfffffba3
d00134d0:	fffffb95 			; <UNDEFINED> instruction: 0xfffffb95
d00134d4:	fffffad4 			; <UNDEFINED> instruction: 0xfffffad4
d00134d8:	fffffae2 			; <UNDEFINED> instruction: 0xfffffae2
d00134dc:	fffffb08 			; <UNDEFINED> instruction: 0xfffffb08

Disassembly of section .text.initialize_static_buffer.constprop.0:

d0013514 <.text.initialize_static_buffer.constprop.0>:
d0013514:	480e4602 	stmdami	lr, {r1, r9, sl, lr}
d0013518:	f5004478 			; <UNDEFINED> instruction: 0xf5004478
d001351c:	f8d333e5 			; <UNDEFINED> instruction: 0xf8d333e5
d0013520:	f5c330d8 			; <UNDEFINED> instruction: 0xf5c330d8
d0013524:	42916180 	addsmi	r6, r1, #128, 2
d0013528:	d206b510 	andle	fp, r6, #16, 10	; 0x4000000
d001352c:	24004909 	strcs	r4, [r0], #-2313	; 0xfffff6f7
d0013530:	f7fc4479 			; <UNDEFINED> instruction: 0xf7fc4479
d0013534:	4620fe39 			; <UNDEFINED> instruction: 0x4620fe39
d0013538:	f500bd10 			; <UNDEFINED> instruction: 0xf500bd10
d001353c:	009234dd 			; <UNDEFINED> instruction: 0x009234dd
d0013540:	34d82100 	ldrbcc	r2, [r8], #256	; 0x100
d0013544:	0483eb04 	streq	lr, [r3], #2820	; 0xb04
d0013548:	f0084620 			; <UNDEFINED> instruction: 0xf0084620
d001354c:	e7f2ff89 	ldrb	pc, [r2, r9, lsl #31]!	; <UNPREDICTABLE>
d0013550:	0000b8dc 	ldrdeq	fp, [r0], -ip
d0013554:	ffffffac 			; <UNDEFINED> instruction: 0xffffffac

Disassembly of section .text.initialize_large_zero.constprop.0:

d0013580 <.text.initialize_large_zero.constprop.0>:
d0013580:	4c16b513 	cfldr32mi	mvfx11, [r6], {19}
d0013584:	4a16217b 	bmi	0xd059bb78
d0013588:	447a447c 	ldrbtmi	r4, [sl], #-1148	; 0xfffffb84
d001358c:	92014620 	andls	r4, r1, #32, 12	; 0x2000000
d0013590:	fb9bf7ff 	blx	0xce711596
d0013594:	6ae3b300 	bvs	0xcf90019c
d0013598:	7381f5a3 	orrvc	pc, r1, #683671552	; 0x28c00000
d001359c:	d8022b01 	stmdale	r2, {r0, r8, r9, fp, sp}
d00135a0:	9a016a23 	bls	0xd006de34
d00135a4:	490fb143 	stmdbmi	pc, {r0, r1, r6, r8, ip, sp, pc}	; <UNPREDICTABLE>
d00135a8:	4479480f 	ldrbtmi	r4, [r9], #-2063	; 0xfffff7f1
d00135ac:	b0024478 	andlt	r4, r2, r8, ror r4
d00135b0:	4010e8bd 			; <UNDEFINED> instruction: 0x4010e8bd
d00135b4:	bdf8f7fc 	ldcllt	7, cr15, [r8, #1008]!	; 0x3f0
d00135b8:	92014620 	andls	r4, r1, #32, 12	; 0x2000000
d00135bc:	fb5cf7ff 	blx	0xd17515c2
d00135c0:	4620212c 	strtmi	r2, [r0], -ip, lsr #2
d00135c4:	fb73f7ff 	blx	0xd1d115ca
d00135c8:	217d9a01 	cmncs	sp, r1, lsl #20
d00135cc:	b0024620 	andlt	r4, r2, r0, lsr #12
d00135d0:	4010e8bd 			; <UNDEFINED> instruction: 0x4010e8bd
d00135d4:	bb79f7ff 	bllt	0xd1e915d8
d00135d8:	bd10b002 	ldclt	0, cr11, [r0, #-8]
d00135dc:	0000b86c 	andeq	fp, r0, ip, ror #16
d00135e0:	ffffffca 			; <UNDEFINED> instruction: 0xffffffca
d00135e4:	ffffffaa 			; <UNDEFINED> instruction: 0xffffffaa
d00135e8:	0000b848 	andeq	fp, r0, r8, asr #16

Disassembly of section .text.add_local.constprop.0:

d0013628 <.text.add_local.constprop.0>:
d0013628:	e92db084 	push	{r2, r7, ip, sp, pc}
d001362c:	4d3447f0 	ldcmi	7, cr4, [r4, #-960]!	; 0xfffffc40
d0013630:	447dac08 	ldrbtmi	sl, [sp], #-3080	; 0xfffff3f8
d0013634:	000fe884 	andeq	lr, pc, r4, lsl #17
d0013638:	9a094601 	bls	0xd0264e44
d001363c:	f8dd4628 			; <UNDEFINED> instruction: 0xf8dd4628
d0013640:	f8dda02c 			; <UNDEFINED> instruction: 0xf8dda02c
d0013644:	f89d9030 			; <UNDEFINED> instruction: 0xf89d9030
d0013648:	9e0f8038 	mcrls	0, 0, r8, cr15, cr8, {1}
d001364c:	f801f7fd 			; <UNDEFINED> instruction: 0xf801f7fd
d0013650:	db1b2800 	blle	0xd06dd658
d0013654:	fb03232c 	blx	0xd00dc30e
d0013658:	f5055000 			; <UNDEFINED> instruction: 0xf5055000
d001365c:	f5003316 			; <UNDEFINED> instruction: 0xf5003316
d0013660:	f8d33013 			; <UNDEFINED> instruction: 0xf8d33013
d0013664:	f89031f4 			; <UNDEFINED> instruction: 0xf89031f4
d0013668:	429a230c 	addsmi	r2, sl, #12, 6	; 0x30000000
d001366c:	6dacd10e 	stfvsd	f5, [ip, #56]!	; 0x38
d0013670:	d1422c00 	cmple	r2, r0, lsl #24
d0013674:	66ae4b23 	strtvs	r4, [lr], r3, lsr #22
d0013678:	e9c5447b 	stmib	r5, {r0, r1, r3, r4, r5, r6, sl, lr}^
d001367c:	e9c59818 	stmib	r5, {r3, r4, fp, ip, pc}^
d0013680:	46203a16 			; <UNDEFINED> instruction: 0x46203a16
d0013684:	47f0e8bd 			; <UNDEFINED> instruction: 0x47f0e8bd
d0013688:	4770b004 	ldrbmi	fp, [r0, -r4]!
d001368c:	447b4b1e 	ldrbtmi	r4, [fp], #-2846	; 0xfffff4e2
d0013690:	3716f503 	ldrcc	pc, [r6, -r3, lsl #10]
d0013694:	41ecf8d7 	ldrdmi	pc, [ip, #135]!	; 0x87
d0013698:	d1092c40 	tstle	r9, r0, asr #24
d001369c:	bb646d9c 	bllt	0xd192ed14
d00136a0:	669e4a1a 			; <UNDEFINED> instruction: 0x669e4a1a
d00136a4:	e9c3447a 	stmib	r3, {r1, r3, r4, r5, r6, sl, lr}^
d00136a8:	e9c39818 	stmib	r3, {r3, r4, fp, ip, pc}^
d00136ac:	e7e82a16 			; <UNDEFINED> instruction: 0xe7e82a16
d00136b0:	f104222c 			; <UNDEFINED> instruction: 0xf104222c
d00136b4:	ae080801 	cdpge	8, 0, cr0, cr8, cr1, {0}
d00136b8:	fb022100 	blx	0xd009bac2
d00136bc:	f8973304 			; <UNDEFINED> instruction: 0xf8973304
d00136c0:	f8c791f4 			; <UNDEFINED> instruction: 0xf8c791f4
d00136c4:	f50381ec 			; <UNDEFINED> instruction: 0xf50381ec
d00136c8:	f50a3a13 			; <UNDEFINED> instruction: 0xf50a3a13
d00136cc:	4628753b 			; <UNDEFINED> instruction: 0x4628753b
d00136d0:	fec6f008 	cdp2	0, 12, cr15, cr6, cr8, {0}
d00136d4:	930cf88a 	movwls	pc, #51338	; 0xc88a	; <UNPREDICTABLE>
d00136d8:	c50fce0f 	strgt	ip, [pc, #-3599]	; 0xd00128d1
d00136dc:	000fe896 	muleq	pc, r6, r8	; <UNPREDICTABLE>
d00136e0:	000fe885 	andeq	lr, pc, r5, lsl #17
d00136e4:	3040f89d 	umaalcc	pc, r0, sp, r8	; <UNPREDICTABLE>
d00136e8:	330df88a 	movwcc	pc, #55434	; 0xd88a	; <UNPREDICTABLE>
d00136ec:	31f0f8d7 	ldrsbcc	pc, [r0, #135]!	; 0x87	; <UNPREDICTABLE>
d00136f0:	d9c64598 	stmible	r6, {r3, r4, r7, r8, sl, lr}^
d00136f4:	81f0f8c7 	mvnshi	pc, r7, asr #17
d00136f8:	2400e7c3 	strcs	lr, [r0], #-1987	; 0xfffff83d
d00136fc:	bf00e7c1 	svclt	0x0000e7c1
d0013700:	0000b7c2 	andeq	fp, r0, r2, asr #15
d0013704:	ffffff70 			; <UNDEFINED> instruction: 0xffffff70
d0013708:	0000b766 	andeq	fp, r0, r6, ror #14
d001370c:	ffffff60 			; <UNDEFINED> instruction: 0xffffff60

Disassembly of section .text.record_definition.constprop.0:

d0013948 <.text.record_definition.constprop.0>:
d0013948:	e92db084 	push	{r2, r7, ip, sp, pc}
d001394c:	ed2d4ff0 	vstr	FPSCR_nzcvqc, [sp, #-448]!	; 0xfffffe40
d0013950:	f5ad8b02 			; <UNDEFINED> instruction: 0xf5ad8b02
d0013954:	46807d31 			; <UNDEFINED> instruction: 0x46807d31
d0013958:	f8ddacbc 			; <UNDEFINED> instruction: 0xf8ddacbc
d001395c:	e884b310 	stm	r4, {r4, r8, r9, ip, sp, pc}
d0013960:	9bbd000f 	blls	0xcef539a4
d0013964:	4af8217b 	bmi	0xcfe1bf58
d0013968:	3a10ee08 	bcc	0xd044f190
d001396c:	48f79bbf 	ldmmi	r7!, {r0, r1, r2, r3, r4, r5, r7, r8, r9, fp, ip, pc}^
d0013970:	9301447a 	movwls	r4, #5242	; 0x147a
d0013974:	44789bc0 	ldrbtmi	r9, [r8], #-3008	; 0xfffff440
d0013978:	f89d9302 			; <UNDEFINED> instruction: 0xf89d9302
d001397c:	93033308 	movwls	r3, #13064	; 0x3308
d0013980:	93049bc3 	movwls	r9, #19395	; 0x4bc3
d0013984:	f9a1f7ff 			; <UNDEFINED> instruction: 0xf9a1f7ff
d0013988:	f04fb950 			; <UNDEFINED> instruction: 0xf04fb950
d001398c:	462034ff 			; <UNDEFINED> instruction: 0x462034ff
d0013990:	7d31f50d 	cfldr32vc	mvfx15, [r1, #-52]!	; 0xffffffcc
d0013994:	8b02ecbd 	blhi	0xd00cec90
d0013998:	4ff0e8bd 	svcmi	0x00f0e8bd
d001399c:	4770b004 	ldrbmi	fp, [r0, -r4]!
d00139a0:	f44fac16 			; <UNDEFINED> instruction: 0xf44fac16
d00139a4:	2100721a 	tstcs	r0, sl, lsl r2
d00139a8:	46254620 	strtmi	r4, [r5], -r0, lsr #12
d00139ac:	fd58f008 	ldc2l	0, cr15, [r8, #-32]	; 0xffffffe0
d00139b0:	2b009bc5 	blcs	0xd003a8cc
d00139b4:	aec6d044 	cdpge	0, 12, cr13, cr6, cr4, {2}
d00139b8:	0934f10d 	ldmdbeq	r4!, {r0, r2, r3, r8, ip, sp, lr, pc}
d00139bc:	c50fce0f 	strgt	ip, [pc, #-3599]	; 0xd0012bb5
d00139c0:	000fe896 	muleq	pc, r6, r8	; <UNPREDICTABLE>
d00139c4:	000fe885 	andeq	lr, pc, r5, lsl #17
d00139c8:	9bc54de1 	blls	0xcf167154
d00139cc:	f884447d 			; <UNDEFINED> instruction: 0xf884447d
d00139d0:	f884b263 			; <UNDEFINED> instruction: 0xf884b263
d00139d4:	7a2b3264 	bvc	0xd0ae036c
d00139d8:	3265f884 	rsbcc	pc, r5, #132, 16	; 0x840000
d00139dc:	b92b6dab 	stmdblt	fp!, {r0, r1, r3, r5, r7, r8, sl, fp, sp, lr}
d00139e0:	2b7d6aeb 	blcs	0xd1f6e594
d00139e4:	f5b3d002 			; <UNDEFINED> instruction: 0xf5b3d002
d00139e8:	d12b7f80 	smlawble	fp, r0, pc, r7	; <UNPREDICTABLE>
d00139ec:	217d4cd9 	ldrsbcs	r4, [sp, #-201]!	; 0xffffff37
d00139f0:	447c4ad9 	ldrbtmi	r4, [ip], #-2777	; 0xfffff527
d00139f4:	4620447a 			; <UNDEFINED> instruction: 0x4620447a
d00139f8:	f967f7ff 			; <UNDEFINED> instruction: 0xf967f7ff
d00139fc:	d0c42800 	sbcle	r2, r4, r0, lsl #16
d0013a00:	ae169bc5 	vnmlage.f64	d9, d22, d5
d0013a04:	3418b13b 	ldrcc	fp, [r8], #-315	; 0xfffffec5
d0013a08:	cc0f4635 	stcgt	6, cr4, [pc], {53}	; 0x35
d0013a0c:	e894c50f 	ldm	r4, {r0, r1, r2, r3, r8, sl, lr, pc}
d0013a10:	e885000f 	stm	r5, {r0, r1, r2, r3}
d0013a14:	f896000f 			; <UNDEFINED> instruction: 0xf896000f
d0013a18:	2b003262 	blcs	0xd00203a8
d0013a1c:	8105f040 	tsthi	r5, r0, asr #32	; <UNPREDICTABLE>
d0013a20:	447b4bce 	ldrbtmi	r4, [fp], #-3022	; 0xfffff432
d0013a24:	2a006d9a 	bcs	0xd002f094
d0013a28:	4acdd1af 	bmi	0xcf3880ec
d0013a2c:	659a447a 	ldrvs	r4, [sl, #1146]	; 0x47a
d0013a30:	65da9a01 	ldrbvs	r9, [sl, #2561]	; 0xa01
d0013a34:	661a9a02 	ldrvs	r9, [sl], -r2, lsl #20
d0013a38:	665a9a03 	ldrbvs	r9, [sl], -r3, lsl #20
d0013a3c:	e0af9a04 	adc	r9, pc, r4, lsl #20
d0013a40:	e7b9aebc 			; <UNDEFINED> instruction: 0xe7b9aebc
d0013a44:	32baf89d 	adcscc	pc, sl, #10289152	; 0x9d0000
d0013a48:	d1052b10 	tstle	r5, r0, lsl fp
d0013a4c:	462849c5 	strtmi	r4, [r8], -r5, asr #19
d0013a50:	f7fc4479 			; <UNDEFINED> instruction: 0xf7fc4479
d0013a54:	e798fba9 	ldr	pc, [r8, r9, lsr #23]
d0013a58:	f24024ff 	vqshl.s8	q9, <illegal reg q15.5>, q8
d0013a5c:	46281107 	strtmi	r1, [r8], -r7, lsl #2
d0013a60:	4000f8c9 	andmi	pc, r0, r9, asr #17
d0013a64:	f923f7ff 			; <UNDEFINED> instruction: 0xf923f7ff
d0013a68:	d04e2800 	suble	r2, lr, r0, lsl #16
d0013a6c:	4000f8c9 	andmi	pc, r0, r9, asr #17
d0013a70:	ae0e4cbd 	mcrge	12, 0, r4, cr14, cr13, {5}
d0013a74:	f104447c 			; <UNDEFINED> instruction: 0xf104447c
d0013a78:	cf0f0718 	svcgt	0x000f0718
d0013a7c:	e897c60f 	ldm	r7, {r0, r1, r2, r3, r9, sl, lr, pc}
d0013a80:	e886000f 	stm	r6, {r0, r1, r2, r3}
d0013a84:	69a3000f 	stmibvs	r3!, {r0, r1, r2, r3}
d0013a88:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d0013a8c:	46204ab7 			; <UNDEFINED> instruction: 0x46204ab7
d0013a90:	69e39309 	stmibvs	r3!, {r0, r3, r8, r9, ip, pc}^
d0013a94:	6a67447a 	bvs	0xd19e4c84
d0013a98:	6aa3930a 	bvs	0xce8f86c8
d0013a9c:	f8949308 			; <UNDEFINED> instruction: 0xf8949308
d0013aa0:	93063030 	movwls	r3, #24624	; 0x6030
d0013aa4:	93076b63 	movwls	r6, #31587	; 0x7b63
d0013aa8:	f90ff7ff 			; <UNDEFINED> instruction: 0xf90ff7ff
d0013aac:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0013ab0:	4aafaf6c 	bmi	0xcebff868
d0013ab4:	4620213b 			; <UNDEFINED> instruction: 0x4620213b
d0013ab8:	f7ff447a 			; <UNDEFINED> instruction: 0xf7ff447a
d0013abc:	2800f906 	stmdacs	r0, {r1, r2, r8, fp, ip, sp, lr, pc}
d0013ac0:	af63f43f 	svcge	0x0063f43f
d0013ac4:	2600ac16 			; <UNDEFINED> instruction: 0x2600ac16
d0013ac8:	f89a46a2 			; <UNDEFINED> instruction: 0xf89a46a2
d0013acc:	42962262 	addsmi	r2, r6, #536870918	; 0x20000006
d0013ad0:	f8d9d34b 			; <UNDEFINED> instruction: 0xf8d9d34b
d0013ad4:	2bff3000 	blcs	0xcffdfadc
d0013ad8:	d0689305 	rsble	r9, r8, r5, lsl #6
d0013adc:	f44f4ba5 			; <UNDEFINED> instruction: 0xf44f4ba5
d0013ae0:	9805711a 	stmdals	r5, {r1, r3, r4, r8, ip, sp, lr}
d0013ae4:	fb01447b 	blx	0xd0064cda
d0013ae8:	f5033300 			; <UNDEFINED> instruction: 0xf5033300
d0013aec:	f8b333bd 			; <UNDEFINED> instruction: 0xf8b333bd
d0013af0:	f1bee068 			; <UNDEFINED> instruction: 0xf1bee068
d0013af4:	d15c0f00 	cmple	ip, r0, lsl #30
d0013af8:	447b4b9f 	ldrbtmi	r4, [fp], #-2975	; 0xfffff461
d0013afc:	2a006d9a 	bcs	0xd002f16c
d0013b00:	af43f47f 	svcge	0x0043f47f
d0013b04:	447a4a9d 	ldrbtmi	r4, [sl], #-2717	; 0xfffff563
d0013b08:	6aeae043 	bvs	0xcfacbc1c
d0013b0c:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d0013b10:	d118429a 			; <UNDEFINED> instruction: 0xd118429a
d0013b14:	e9d54628 	ldmib	r5, {r3, r5, r9, sl, lr}^
d0013b18:	f7fc1206 			; <UNDEFINED> instruction: 0xf7fc1206
d0013b1c:	2800fdde 	stmdacs	r0, {r1, r2, r3, r4, r6, r7, r8, sl, fp, ip, sp, lr, pc}
d0013b20:	4628db11 			; <UNDEFINED> instruction: 0x4628db11
d0013b24:	1206e9d5 	andne	lr, r6, #3489792	; 0x354000
d0013b28:	fdd7f7fc 	ldc2l	7, cr15, [r7, #1008]	; 0x3f0
d0013b2c:	fb032324 	blx	0xd00dc7c6
d0013b30:	f5005000 			; <UNDEFINED> instruction: 0xf5005000
d0013b34:	f89030d8 			; <UNDEFINED> instruction: 0xf89030d8
d0013b38:	2bff31ec 	blcs	0xcffe02f0
d0013b3c:	4628d103 	strtmi	sp, [r8], -r3, lsl #2
d0013b40:	f89af7ff 			; <UNDEFINED> instruction: 0xf89af7ff
d0013b44:	488ee794 	stmmi	lr, {r2, r4, r7, r8, r9, sl, sp, lr, pc}
d0013b48:	44784649 	ldrbtmi	r4, [r8], #-1609	; 0xfffff9b7
d0013b4c:	f900f7ff 			; <UNDEFINED> instruction: 0xf900f7ff
d0013b50:	d18d2800 	orrle	r2, sp, r0, lsl #16
d0013b54:	0f00f1bb 	svceq	0x0000f1bb
d0013b58:	498ad104 	stmibmi	sl, {r2, r8, ip, lr, pc}
d0013b5c:	488a4479 	stmmi	sl, {r0, r3, r4, r5, r6, sl, lr}
d0013b60:	e7764478 			; <UNDEFINED> instruction: 0xe7764478
d0013b64:	44794989 	ldrbtmi	r4, [r9], #-2441	; 0xfffff677
d0013b68:	6a61e7f9 	bvs	0xd188db54
d0013b6c:	f8543424 			; <UNDEFINED> instruction: 0xf8543424
d0013b70:	9b0a0c04 	blls	0xd0296b88
d0013b74:	f7fc9a09 			; <UNDEFINED> instruction: 0xf7fc9a09
d0013b78:	b1b0fcfd 	rorslt	pc, sp	; <illegal shifter operand>	; <UNPREDICTABLE>
d0013b7c:	0f00f1bb 	svceq	0x0000f1bb
d0013b80:	4a83d110 	bmi	0xce107fc8
d0013b84:	4b83447a 	blmi	0xce0e4d74
d0013b88:	6d99447b 	cfldrsvs	mvf4, [r9, #492]	; 0x1ec
d0013b8c:	f47f2900 			; <UNDEFINED> instruction: 0xf47f2900
d0013b90:	e9c3aefc 	stmib	r3, {r2, r3, r4, r5, r6, r7, r9, sl, fp, sp, pc}^
d0013b94:	9a082716 	bls	0xd021d7f4
d0013b98:	9a06661a 	bls	0xd01ad408
d0013b9c:	9a07665a 	bls	0xd01ed50c
d0013ba0:	e6f2669a 	usat	r6, #18, sl, lsl #13
d0013ba4:	447a4a7c 	ldrbtmi	r4, [sl], #-2684	; 0xfffff584
d0013ba8:	3601e7ed 	strcc	lr, [r1], -sp, ror #15
d0013bac:	f04fe78d 			; <UNDEFINED> instruction: 0xf04fe78d
d0013bb0:	f8bd0e01 			; <UNDEFINED> instruction: 0xf8bd0e01
d0013bb4:	f10dc2b8 			; <UNDEFINED> instruction: 0xf10dc2b8
d0013bb8:	f5cc0a58 			; <UNDEFINED> instruction: 0xf5cc0a58
d0013bbc:	33ff437f 	mvnscc	r4, #-67108863	; 0xfc000001
d0013bc0:	d3994573 	orrsle	r4, r9, #482344960	; 0x1cc00000
d0013bc4:	f1bb1c53 			; <UNDEFINED> instruction: 0xf1bb1c53
d0013bc8:	97110f00 	ldrls	r0, [r1, -r0, lsl #30]
d0013bcc:	0724f04f 	streq	pc, [r4, -pc, asr #32]!
d0013bd0:	3262f88a 	rsbcc	pc, r2, #9043968	; 0x8a0000
d0013bd4:	4663bf0c 	strbtmi	fp, [r3], -ip, lsl #30
d0013bd8:	fb072300 	blx	0xd01dc7e2
d0013bdc:	ac0ea702 	stcge	7, cr10, [lr], {2}
d0013be0:	f107930b 			; <UNDEFINED> instruction: 0xf107930b
d0013be4:	9b090620 	blls	0xd025546c
d0013be8:	9b0a930e 	blls	0xd02b8828
d0013bec:	9b08930f 	blls	0xd0238830
d0013bf0:	9b069312 	blls	0xd01b8840
d0013bf4:	3050f88d 	subscc	pc, r0, sp, lsl #17
d0013bf8:	93159b07 	tstls	r5, #7168	; 0x1c00
d0013bfc:	c60fcc0f 	strgt	ip, [pc], -pc, lsl #24
d0013c00:	000fe894 	muleq	pc, r4, r8	; <UNPREDICTABLE>
d0013c04:	000fe886 	andeq	lr, pc, r6, lsl #17
d0013c08:	f8879b05 			; <UNDEFINED> instruction: 0xf8879b05
d0013c0c:	9b0b3040 	blls	0xd02dfd14
d0013c10:	3042f8a7 	subcc	pc, r2, r7, lsr #17
d0013c14:	45f4d005 	ldrbmi	sp, [r4, #5]!
d0013c18:	aee0f4bf 	mcrge	4, 7, pc, cr0, cr15, {5}	; <UNPREDICTABLE>
d0013c1c:	e260f8aa 	rsb	pc, r0, #11141120	; 0xaa0000
d0013c20:	44f4e6dc 	ldrbtmi	lr, [r4], #1756	; 0x6dc
d0013c24:	c260f8aa 	rsbgt	pc, r0, #11141120	; 0xaa0000
d0013c28:	9bc5e6d8 	blls	0xcf18d790
d0013c2c:	4f5bb31b 	svcmi	0x005bb31b
d0013c30:	447f2400 	ldrbtmi	r2, [pc], #-1024	; 0xd0013c38
d0013c34:	35bcf507 	ldrcc	pc, [ip, #1287]!	; 0x507
d0013c38:	38d8f507 	ldmcc	r8, {r0, r1, r2, r8, sl, ip, sp, lr, pc}^
d0013c3c:	f8d83508 			; <UNDEFINED> instruction: 0xf8d83508
d0013c40:	429c31c8 	addsmi	r3, ip, #200, 2	; 0x32
d0013c44:	4856d333 	ldmdami	r6, {r0, r1, r4, r5, r8, r9, ip, lr, pc}^
d0013c48:	f5004478 			; <UNDEFINED> instruction: 0xf5004478
d0013c4c:	f8d333d8 			; <UNDEFINED> instruction: 0xf8d333d8
d0013c50:	2c1841c8 	ldfcss	f4, [r8], {200}	; 0xc8
d0013c54:	6d83d146 	stfvsd	f5, [r3, #280]	; 0x118
d0013c58:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0013c5c:	4b51ae96 	blmi	0xd147f6bc
d0013c60:	6583447b 	strvs	r4, [r3, #1147]	; 0x47b
d0013c64:	65c39b01 	strbvs	r9, [r3, #2817]	; 0xb01
d0013c68:	66039b02 	strvs	r9, [r3], -r2, lsl #22
d0013c6c:	66439b03 	strbvs	r9, [r3], -r3, lsl #22
d0013c70:	66839b04 	strvs	r9, [r3], r4, lsl #22
d0013c74:	4c4ce689 	mcrrmi	6, 8, lr, ip, cr9
d0013c78:	0301f08b 	movweq	pc, #4235	; 0x108b	; <UNPREDICTABLE>
d0013c7c:	2a10ee18 	bcs	0xd044f4e4
d0013c80:	447c4641 	ldrbtmi	r4, [ip], #-1601	; 0xfffff9bf
d0013c84:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0013c88:	2800fc83 	stmdacs	r0, {r0, r1, r7, sl, fp, ip, sp, lr, pc}
d0013c8c:	6da3db38 			; <UNDEFINED> instruction: 0x6da3db38
d0013c90:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0013c94:	4b45ae7a 	blmi	0xd117f684
d0013c98:	65a3447b 	strvs	r4, [r3, #1147]!	; 0x47b
d0013c9c:	65e39b01 	strbvs	r9, [r3, #2817]!	; 0xb01
d0013ca0:	66239b02 	strtvs	r9, [r3], -r2, lsl #22
d0013ca4:	66639b03 	strbtvs	r9, [r3], -r3, lsl #22
d0013ca8:	66a39b04 	strtvs	r9, [r3], r4, lsl #22
d0013cac:	f895e66d 			; <UNDEFINED> instruction: 0xf895e66d
d0013cb0:	b1833264 	orrlt	r3, r3, r4, ror #4
d0013cb4:	2265f895 	rsbcs	pc, r5, #9764864	; 0x950000
d0013cb8:	429a7a3b 	addsmi	r7, sl, #241664	; 0x3b000
d0013cbc:	e9d6d00b 	ldmib	r6, {r0, r1, r3, ip, lr, pc}^
d0013cc0:	e9d52300 	ldmib	r5, {r8, r9, sp}^
d0013cc4:	f7fc0100 			; <UNDEFINED> instruction: 0xf7fc0100
d0013cc8:	b120fc55 	msrlt	CPSR_, r5, asr ip
d0013ccc:	46304629 	ldrtmi	r4, [r0], -r9, lsr #12
d0013cd0:	fc86f7fc 	stc2	7, cr15, [r6], {252}	; 0xfc
d0013cd4:	3401b9e8 	strcc	fp, [r1], #-2536	; 0xfffff618
d0013cd8:	751af505 	ldrvc	pc, [sl, #-1285]	; 0xfffffafb
d0013cdc:	4a34e7af 	bmi	0xd0d4dba0
d0013ce0:	e02a447a 	eor	r4, sl, sl, ror r4
d0013ce4:	46311c62 	ldrtmi	r1, [r1], -r2, ror #24
d0013ce8:	21c8f8c3 	biccs	pc, r8, r3, asr #17
d0013cec:	721af44f 	andsvc	pc, sl, #1325400064	; 0x4f000000
d0013cf0:	0004fb02 	andeq	pc, r4, r2, lsl #22
d0013cf4:	30bcf500 	adcscc	pc, ip, r0, lsl #10
d0013cf8:	f0083008 			; <UNDEFINED> instruction: 0xf0083008
d0013cfc:	e646fbbf 			; <UNDEFINED> instruction: 0xe646fbbf
d0013d00:	465b4620 	ldrbmi	r4, [fp], -r0, lsr #12
d0013d04:	2a10ee18 	bcs	0xd044f56c
d0013d08:	f7fc4641 			; <UNDEFINED> instruction: 0xf7fc4641
d0013d0c:	1e04fc41 	cdpne	12, 0, cr15, cr4, cr1, {2}
d0013d10:	f44fdb99 			; <UNDEFINED> instruction: 0xf44fdb99
d0013d14:	4927731a 	stmdbmi	r7!, {r1, r3, r4, r8, r9, ip, sp, lr}
d0013d18:	43634630 	cmnmi	r3, #48, 12	; 0x3000000
d0013d1c:	f5034479 			; <UNDEFINED> instruction: 0xf5034479
d0013d20:	330833bc 	movwcc	r3, #33724	; 0x83bc
d0013d24:	f7fc4419 			; <UNDEFINED> instruction: 0xf7fc4419
d0013d28:	2800fc5b 	stmdacs	r0, {r0, r1, r3, r4, r6, sl, fp, ip, sp, lr, pc}
d0013d2c:	ae2ff47f 	mcrge	4, 1, pc, cr15, cr15, {3}	; <UNPREDICTABLE>
d0013d30:	0f00f1bb 	svceq	0x0000f1bb
d0013d34:	4a20d1d3 	bmi	0xd0848488
d0013d38:	4b20447a 	blmi	0xd0824f28
d0013d3c:	6d99447b 	cfldrsvs	mvf4, [r9, #492]	; 0x1ec
d0013d40:	f47f2900 			; <UNDEFINED> instruction: 0xf47f2900
d0013d44:	e672ae22 	ldrbt	sl, [r2], -r2, lsr #28
d0013d48:	fffffe99 			; <UNDEFINED> instruction: 0xfffffe99
d0013d4c:	0000b47e 	andeq	fp, r0, lr, ror r4
d0013d50:	0000b428 	andeq	fp, r0, r8, lsr #8
d0013d54:	0000b402 	andeq	fp, r0, r2, lsl #8
d0013d58:	fffffeb8 			; <UNDEFINED> instruction: 0xfffffeb8
d0013d5c:	0000b3d2 	ldrdeq	fp, [r0], -r2
d0013d60:	fffffea1 			; <UNDEFINED> instruction: 0xfffffea1
d0013d64:	fffffdd8 			; <UNDEFINED> instruction: 0xfffffdd8
d0013d68:	0000b380 	andeq	fp, r0, r0, lsl #7
d0013d6c:	fffffdb2 			; <UNDEFINED> instruction: 0xfffffdb2
d0013d70:	fffffda9 			; <UNDEFINED> instruction: 0xfffffda9
d0013d74:	0000b310 	andeq	fp, r0, r0, lsl r3
d0013d78:	0000b2fa 	strdeq	fp, [r0], -sl
d0013d7c:	fffffd7b 			; <UNDEFINED> instruction: 0xfffffd7b
d0013d80:	0000b2aa 	andeq	fp, r0, sl, lsr #5
d0013d84:	fffffbfa 			; <UNDEFINED> instruction: 0xfffffbfa
d0013d88:	0000b294 	muleq	r0, r4, r2
d0013d8c:	fffffba6 			; <UNDEFINED> instruction: 0xfffffba6
d0013d90:	fffffc33 			; <UNDEFINED> instruction: 0xfffffc33
d0013d94:	0000b26c 	andeq	fp, r0, ip, ror #4
d0013d98:	fffffbfb 			; <UNDEFINED> instruction: 0xfffffbfb
d0013d9c:	0000b1c2 	andeq	fp, r0, r2, asr #3
d0013da0:	0000b1ac 	andeq	fp, r0, ip, lsr #3
d0013da4:	fffffcc2 			; <UNDEFINED> instruction: 0xfffffcc2
d0013da8:	0000b172 	andeq	fp, r0, r2, ror r1
d0013dac:	fffffc5d 			; <UNDEFINED> instruction: 0xfffffc5d
d0013db0:	fffffaee 			; <UNDEFINED> instruction: 0xfffffaee
d0013db4:	0000b0d8 	ldrdeq	fp, [r0], -r8
d0013db8:	fffffab3 			; <UNDEFINED> instruction: 0xfffffab3
d0013dbc:	0000b0b8 	strheq	fp, [r0], -r8

Disassembly of section .text.load_apicore.constprop.0:

d0013e1c <.text.load_apicore.constprop.0>:
d0013e1c:	4ff0e92d 	svcmi	0x00f0e92d
d0013e20:	b0894603 	addlt	r4, r9, r3, lsl #12
d0013e24:	4993b938 	ldmibmi	r3, {r3, r4, r5, r8, fp, ip, sp, pc}
d0013e28:	44794893 	ldrbtmi	r4, [r9], #-2195	; 0xfffff76d
d0013e2c:	f7fc4478 			; <UNDEFINED> instruction: 0xf7fc4478
d0013e30:	2000f9bb 			; <UNDEFINED> instruction: 0x2000f9bb
d0013e34:	4d91e081 	ldcmi	0, cr14, [r1, #516]	; 0x204
d0013e38:	51ecf640 	mvnpl	pc, r0, asr #12
d0013e3c:	4628447d 			; <UNDEFINED> instruction: 0x4628447d
d0013e40:	28004798 	stmdacs	r0, {r3, r4, r7, r8, r9, sl, lr}
d0013e44:	f1a0d0ef 			; <UNDEFINED> instruction: 0xf1a0d0ef
d0013e48:	f6400218 			; <UNDEFINED> instruction: 0xf6400218
d0013e4c:	429a53d4 	addsmi	r5, sl, #212, 6	; 0x50000003
d0013e50:	8087f200 	addhi	pc, r7, r0, lsl #4
d0013e54:	22041f07 	andcs	r1, r4, #7, 30
d0013e58:	19e9a802 	stmibne	r9!, {r1, fp, sp, pc}^
d0013e5c:	fb0ef008 	blx	0xd03cfe86
d0013e60:	46284639 			; <UNDEFINED> instruction: 0x46284639
d0013e64:	f988f7fc 			; <UNDEFINED> instruction: 0xf988f7fc
d0013e68:	42989b02 	addsmi	r9, r8, #2048	; 0x800
d0013e6c:	ac03d179 	stfged	f5, [r3], {121}	; 0x79
d0013e70:	22144629 	andscs	r4, r4, #42991616	; 0x2900000
d0013e74:	f0084620 			; <UNDEFINED> instruction: 0xf0084620
d0013e78:	4981fb01 	stmibmi	r1, {r0, r8, r9, fp, ip, sp, lr, pc}
d0013e7c:	46202208 	strtmi	r2, [r0], -r8, lsl #4
d0013e80:	f0084479 			; <UNDEFINED> instruction: 0xf0084479
d0013e84:	4605fb0b 	strmi	pc, [r5], -fp, lsl #22
d0013e88:	d1592800 	cmple	r9, r0, lsl #16
d0013e8c:	4b782601 	blmi	0xd1e1d698
d0013e90:	429a9a05 	addsmi	r9, sl, #20480	; 0x5000
d0013e94:	9906d165 	stmdbls	r6, {r0, r2, r5, r6, r8, ip, lr, pc}
d0013e98:	2b271e4b 	blcs	0xd09db7cc
d0013e9c:	9a07d861 	bls	0xd020a028
d0013ea0:	d85e2a28 	ldmdale	lr, {r3, r5, r9, fp, sp}^
d0013ea4:	f04f2d00 			; <UNDEFINED> instruction: 0xf04f2d00
d0013ea8:	bf0c0324 	svclt	0x000c0324
d0013eac:	0a0cf04f 	beq	0xd034fff0
d0013eb0:	0a08f04f 	beq	0xd024fff4
d0013eb4:	2e00435a 	mcrcs	3, 0, r4, cr0, cr10, {2}
d0013eb8:	0828f10a 	stmdaeq	r8!, {r1, r3, r8, ip, sp, lr, pc}
d0013ebc:	0b14f102 	bleq	0xd05502cc
d0013ec0:	2314bf18 	tstcs	r4, #24, 30	; 0x60
d0013ec4:	f101fb08 			; <UNDEFINED> instruction: 0xf101fb08
d0013ec8:	2300bf08 	movwcs	fp, #3848	; 0xf08
d0013ecc:	445b448b 	ldrbmi	r4, [fp], #-1163	; 0xfffffb75
d0013ed0:	d146429f 			; <UNDEFINED> instruction: 0xd146429f
d0013ed4:	91acf8df 	ldrdls	pc, [ip, pc]!	; <UNPREDICTABLE>
d0013ed8:	4b6b3114 	blmi	0xd1ae0330
d0013edc:	447b44f9 	ldrbtmi	r4, [fp], #-1273	; 0xfffffb07
d0013ee0:	4058f509 	subsmi	pc, r8, r9, lsl #10
d0013ee4:	93014419 	movwls	r4, #5145	; 0x1419
d0013ee8:	f0083044 			; <UNDEFINED> instruction: 0xf0083044
d0013eec:	9b01fac7 	blls	0xd0092a10
d0013ef0:	d13b2e00 	teqle	fp, r0, lsl #28
d0013ef4:	d1662d00 	cmnle	r6, r0, lsl #26
d0013ef8:	0b0ef04f 	bleq	0xd03d003c
d0013efc:	27004d63 	strcs	r4, [r0, -r3, ror #26]
d0013f00:	918cf8df 	ldrdls	pc, [ip, pc]
d0013f04:	44f9447d 	ldrbtmi	r4, [r9], #1149	; 0x47d
d0013f08:	4550f505 	ldrbmi	pc, [r0, #-1285]	; 0xfffffafb	; <UNPREDICTABLE>
d0013f0c:	9a06354c 	bls	0xd01a1444
d0013f10:	d35f4297 	cmple	pc, #1879048201	; 0x70000009
d0013f14:	25004e5f 	strcs	r4, [r0, #-3679]	; 0xfffff1a1
d0013f18:	f64d9f07 			; <UNDEFINED> instruction: 0xf64d9f07
d0013f1c:	447e0844 	ldrbtmi	r0, [lr], #-2116	; 0xfffff7bc
d0013f20:	f04042bd 			; <UNDEFINED> instruction: 0xf04042bd
d0013f24:	4d5c809b 	ldclmi	0, cr8, [ip, #-620]	; 0xfffffd94
d0013f28:	f505447d 			; <UNDEFINED> instruction: 0xf505447d
d0013f2c:	cc0f4550 	cfstr32gt	mvfx4, [pc], {80}	; 0x50
d0013f30:	c50f3510 	strgt	r3, [pc, #-1296]	; 0xd0013a28
d0013f34:	20016823 	andcs	r6, r1, r3, lsr #16
d0013f38:	b009602b 	andlt	r6, r9, fp, lsr #32
d0013f3c:	8ff0e8bd 	svchi	0x00f0e8bd
d0013f40:	22084956 	andcs	r4, r8, #1409024	; 0x158000
d0013f44:	44794620 	ldrbtmi	r4, [r9], #-1568	; 0xfffff9e0
d0013f48:	faa8f008 	blx	0xcea4ff70
d0013f4c:	d09d2800 	addsle	r2, sp, r0, lsl #16
d0013f50:	22084953 	andcs	r4, r8, #1359872	; 0x14c000
d0013f54:	44794620 	ldrbtmi	r4, [r9], #-1568	; 0xfffff9e0
d0013f58:	faa0f008 	blx	0xce84ff80
d0013f5c:	28004606 	stmdacs	r0, {r1, r2, r9, sl, lr}
d0013f60:	4950d095 	ldmdbmi	r0, {r0, r2, r4, r7, ip, lr, pc}^
d0013f64:	44794850 	ldrbtmi	r4, [r9], #-2128	; 0xfffff7b0
d0013f68:	e7604478 			; <UNDEFINED> instruction: 0xe7604478
d0013f6c:	475df509 	ldrbmi	pc, [sp, -r9, lsl #10]	; <UNPREDICTABLE>
d0013f70:	010beb03 	tsteq	fp, r3, lsl #22
d0013f74:	37e42214 			; <UNDEFINED> instruction: 0x37e42214
d0013f78:	f0084638 			; <UNDEFINED> instruction: 0xf0084638
d0013f7c:	f64dfa7f 			; <UNDEFINED> instruction: 0xf64dfa7f
d0013f80:	f83953f4 			; <UNDEFINED> instruction: 0xf83953f4
d0013f84:	f6401003 			; <UNDEFINED> instruction: 0xf6401003
d0013f88:	1f0a73fc 	svcne	0x000a73fc
d0013f8c:	d8e8429a 	stmiale	r8!, {r1, r3, r4, r7, r9, lr}^
d0013f90:	52f6f64d 	rscspl	pc, r6, #80740352	; 0x4d00000
d0013f94:	0303f001 	movweq	pc, #12289	; 0x3001	; <UNPREDICTABLE>
d0013f98:	2002f839 	andcs	pc, r2, r9, lsr r8	; <UNPREDICTABLE>
d0013f9c:	d1e04313 	mvnle	r4, r3, lsl r3
d0013fa0:	f8372204 			; <UNDEFINED> instruction: 0xf8372204
d0013fa4:	f1020b02 			; <UNDEFINED> instruction: 0xf1020b02
d0013fa8:	ea1c3cff 	b	0xd07233ac
d0013fac:	d1d80f00 	bicsle	r0, r8, r0, lsl #30
d0013fb0:	42901a8a 	addsmi	r1, r0, #565248	; 0x8a000
d0013fb4:	3301d8d5 	movwcc	sp, #6357	; 0x18d5
d0013fb8:	d09b2b08 	addsle	r2, fp, r8, lsl #22
d0013fbc:	bf0c2b01 	svclt	0x000c2b01
d0013fc0:	22042201 	andcs	r2, r4, #268435456	; 0x10000000
d0013fc4:	2e00e7ed 	cdpcs	7, 0, cr14, cr0, cr13, {7}
d0013fc8:	f04fbf14 			; <UNDEFINED> instruction: 0xf04fbf14
d0013fcc:	f04f0b0d 			; <UNDEFINED> instruction: 0xf04f0b0d
d0013fd0:	e7930b0a 	ldr	r0, [r3, sl, lsl #22]
d0013fd4:	0628f1a5 	strteq	pc, [r8], -r5, lsr #3
d0013fd8:	f1094642 			; <UNDEFINED> instruction: 0xf1094642
d0013fdc:	46300114 			; <UNDEFINED> instruction: 0x46300114
d0013fe0:	fa4cf008 	blx	0xd1350008
d0013fe4:	f7fc4630 			; <UNDEFINED> instruction: 0xf7fc4630
d0013fe8:	2800f9be 	stmdacs	r0, {r1, r2, r3, r4, r5, r7, r8, fp, ip, sp, lr, pc}
d0013fec:	f815d0b9 			; <UNDEFINED> instruction: 0xf815d0b9
d0013ff0:	458a1c02 	strmi	r1, [sl, #3074]	; 0xc02
d0013ff4:	f815d3b5 			; <UNDEFINED> instruction: 0xf815d3b5
d0013ff8:	f6402c01 			; <UNDEFINED> instruction: 0xf6402c01
d0013ffc:	1f500381 	svcne	0x00500381
d0014000:	d9012803 	stmdble	r1, {r0, r1, fp, sp}
d0014004:	d1ac2a0b 			; <UNDEFINED> instruction: 0xd1ac2a0b
d0014008:	0608f1a5 	streq	pc, [r8], -r5, lsr #3
d001400c:	f8362000 			; <UNDEFINED> instruction: 0xf8362000
d0014010:	f6402b02 			; <UNDEFINED> instruction: 0xf6402b02
d0014014:	45627cfc 	strbmi	r7, [r2, #-3324]!	; 0xfffff304
d0014018:	f012d8a3 			; <UNDEFINED> instruction: 0xf012d8a3
d001401c:	d1a00203 	lslle	r0, r3, #4
d0014020:	28033001 	stmdacs	r3, {r0, ip, sp}
d0014024:	462ed1f3 			; <UNDEFINED> instruction: 0x462ed1f3
d0014028:	d8054291 	stmdale	r5, {r0, r4, r7, r9, lr}
d001402c:	d910290b 	ldmdble	r0, {r0, r1, r3, r8, fp, sp}
d0014030:	35343701 	ldrcc	r3, [r4, #-1793]!	; 0xfffff8ff
d0014034:	e76a44c1 	strb	r4, [sl, -r1, asr #9]!
d0014038:	0b01f816 	bleq	0xd0092098
d001403c:	d804280b 	stmdale	r4, {r0, r1, r3, fp, sp}
d0014040:	fc00fa23 	stc2	10, cr15, [r0], {35}	; 0x23	; <UNPREDICTABLE>
d0014044:	0f01f01c 	svceq	0x0001f01c
d0014048:	4558d18b 	ldrbmi	sp, [r8, #-395]	; 0xfffffe75
d001404c:	3201d889 	andcc	sp, r1, #8978432	; 0x890000
d0014050:	5c6ae7ea 	stclpl	7, cr14, [sl], #-936	; 0xfffffc58
d0014054:	d1842a00 	orrle	r2, r4, r0, lsl #20
d0014058:	e7e73101 	strb	r3, [r7, r1, lsl #2]!
d001405c:	0008eb06 	andeq	lr, r8, r6, lsl #22
d0014060:	f7fc3624 			; <UNDEFINED> instruction: 0xf7fc3624
d0014064:	2800f980 	stmdacs	r0, {r7, r8, fp, ip, sp, lr, pc}
d0014068:	af7bf43f 	svcge	0x007bf43f
d001406c:	e7573501 	ldrb	r3, [r7, -r1, lsl #10]
d0014070:	2001f000 	andcs	pc, r1, r0
d0014074:	ffffff92 			; <UNDEFINED> instruction: 0xffffff92
d0014078:	0000afc8 	andeq	sl, r0, r8, asr #31
d001407c:	0000a1c8 	andeq	sl, r0, r8, asr #3
d0014080:	ffffff65 			; <UNDEFINED> instruction: 0xffffff65
d0014084:	0000af18 	andeq	sl, r0, r8, lsl pc
d0014088:	0000a126 	andeq	sl, r0, r6, lsr #2
d001408c:	0000aef0 	strdeq	sl, [r0], -r0
d0014090:	0000a0fe 	strdeq	sl, [r0], -lr
d0014094:	0000aed6 	ldrdeq	sl, [r0], -r6
d0014098:	0000aecc 	andeq	sl, r0, ip, asr #29
d001409c:	fffffea7 			; <UNDEFINED> instruction: 0xfffffea7
d00140a0:	fffffe9f 			; <UNDEFINED> instruction: 0xfffffe9f
d00140a4:	fffffe97 			; <UNDEFINED> instruction: 0xfffffe97
d00140a8:	0000ae8c 	andeq	sl, r0, ip, lsl #29

Disassembly of section .text.accept_sdk_type.constprop.0:

d00140ac <.text.accept_sdk_type.constprop.0>:
d00140ac:	4c0cb538 	cfstr32mi	mvfx11, [ip], {56}	; 0x38
d00140b0:	031cf24d 	tsteq	ip, #-805306364	; 0xd0000004	; <UNPREDICTABLE>
d00140b4:	447c4602 	ldrbtmi	r4, [ip], #-1538	; 0xfffff9fe
d00140b8:	b17b58e3 	cmnlt	fp, r3, ror #17
d00140bc:	f2406ae5 	vpmax.s8	q11, q8, <illegal reg q10.5>
d00140c0:	429d1301 	addsmi	r1, sp, #67108864	; 0x4000000
d00140c4:	e9d4d10a 	ldmib	r4, {r1, r3, r8, ip, lr, pc}^
d00140c8:	f7fc0106 			; <UNDEFINED> instruction: 0xf7fc0106
d00140cc:	b128fb72 	msrlt	(UNDEF: 56), r2
d00140d0:	46204629 	strtmi	r4, [r0], -r9, lsr #12
d00140d4:	4038e8bd 	ldrhtmi	lr, [r8], -sp
d00140d8:	bde9f7fe 	stcllt	7, cr15, [r9, #1016]!	; 0x3f8
d00140dc:	bd382000 	ldclt	0, cr2, [r8, #-0]
d00140e0:	0000ad3e 	andeq	sl, r0, lr, lsr sp

Disassembly of section .text.wide_immediate:

d00140e4 <.text.wide_immediate>:
d00140e4:	085db530 	ldmdaeq	sp, {r4, r5, r8, sl, ip, sp, pc}^
d00140e8:	3413ea41 	ldrcc	lr, [r3], #-2625	; 0xfffff5bf
d00140ec:	6580f405 	strvs	pc, [r0, #1029]	; 0x405
d00140f0:	011bb2d9 			; <UNDEFINED> instruction: 0x011bb2d9
d00140f4:	ea41432c 	b	0xd1064dac
d00140f8:	4d0a2202 	sfmmi	f2, 4, [sl, #-8]
d00140fc:	41e0f403 	mvnmi	pc, r3, lsl #8
d0014100:	447db224 	ldrbtmi	fp, [sp], #-548	; 0xfffffddc
d0014104:	4428430a 	strtmi	r4, [r8], #-778	; 0xfffffcf6
d0014108:	f880b292 			; <UNDEFINED> instruction: 0xf880b292
d001410c:	f3c44040 	vmla.i<illegal width 8>	q10, q2, d0[0]
d0014110:	f8802407 			; <UNDEFINED> instruction: 0xf8802407
d0014114:	0a122042 	beq	0xd049c224
d0014118:	4041f880 	submi	pc, r1, r0, lsl #17
d001411c:	2043f880 	subcs	pc, r3, r0, lsl #17
d0014120:	bf00bd30 	svclt	0x0000bd30
d0014124:	00032742 	andeq	r2, r3, r2, asr #14

Disassembly of section .text.emit:

d0014144 <.text.emit>:
d0014144:	b4706d82 	ldrbtlt	r6, [r0], #-3458	; 0xfffff27e
d0014148:	f64db9a2 			; <UNDEFINED> instruction: 0xf64db9a2
d001414c:	590654f8 	stmdbpl	r6, {r3, r4, r5, r6, r7, sl, ip, lr}
d0014150:	f5b51cb5 			; <UNDEFINED> instruction: 0xf5b51cb5
d0014154:	d9043f80 	stmdble	r4, {r7, r8, r9, sl, fp, ip, sp}
d0014158:	bc704907 			; <UNDEFINED> instruction: 0xbc704907
d001415c:	f7fc4479 			; <UNDEFINED> instruction: 0xf7fc4479
d0014160:	4a06b823 	bmi	0xd01c21f4
d0014164:	4432447a 	ldrtmi	r4, [r2], #-1146	; 0xfffffb86
d0014168:	1040f882 	subne	pc, r0, r2, lsl #17
d001416c:	f8820a09 			; <UNDEFINED> instruction: 0xf8820a09
d0014170:	51051041 	tstpl	r5, r1, asr #32
d0014174:	4770bc70 			; <UNDEFINED> instruction: 0x4770bc70
d0014178:	ffffffc8 			; <UNDEFINED> instruction: 0xffffffc8
d001417c:	000326e0 	andeq	r2, r3, r0, ror #13

Disassembly of section .text.load_constant:

d0014180 <.text.load_constant>:
d0014180:	e92d2aff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r9, fp, sp}
d0014184:	460541f0 			; <UNDEFINED> instruction: 0x460541f0
d0014188:	4614460e 	ldrmi	r4, [r4], -lr, lsl #12
d001418c:	2907d80a 	stmdbcs	r7, {r1, r3, fp, ip, lr, pc}
d0014190:	ea42d808 	b	0xd10ca1b8
d0014194:	f4412101 	vst4.8	{d18,d20,d22,d24}, [r1], r1
d0014198:	e8bd5100 	pop	{r8, ip, lr}
d001419c:	b28941f0 	addlt	r4, r9, #240, 2	; 0x3c
d00141a0:	bfd0f7ff 	svclt	0x00d0f7ff
d00141a4:	53f8f64d 	mvnspl	pc, #80740352	; 0x4d00000
d00141a8:	46282100 	strtmi	r2, [r8], -r0, lsl #2
d00141ac:	f7ff58ef 			; <UNDEFINED> instruction: 0xf7ff58ef
d00141b0:	2100ffc9 	smlabtcs	r0, r9, pc, pc	; <UNPREDICTABLE>
d00141b4:	ffc6f7ff 			; <UNDEFINED> instruction: 0xffc6f7ff
d00141b8:	3f80f5b4 	svccc	0x0080f5b4
d00141bc:	2100d305 	tstcs	r0, r5, lsl #6
d00141c0:	ffc0f7ff 			; <UNDEFINED> instruction: 0xffc0f7ff
d00141c4:	f7ff2100 			; <UNDEFINED> instruction: 0xf7ff2100
d00141c8:	6dabffbd 	stcvs	15, cr15, [fp, #756]!	; 0x2f4
d00141cc:	b2a3b9a3 	adclt	fp, r3, #2670592	; 0x28c000
d00141d0:	f24f4632 	vmin.s8	d20, d15, d18
d00141d4:	46382140 	ldrtmi	r2, [r8], -r0, asr #2
d00141d8:	ff84f7ff 			; <UNDEFINED> instruction: 0xff84f7ff
d00141dc:	3f80f5b4 	svccc	0x0080f5b4
d00141e0:	6dabd30a 	stcvs	3, cr13, [fp, #40]!	; 0x28
d00141e4:	0c23b943 			; <UNDEFINED> instruction: 0x0c23b943
d00141e8:	1d384632 	ldcne	6, cr4, [r8, #-200]!	; 0xffffff38
d00141ec:	21c0f24f 	biccs	pc, r0, pc, asr #4
d00141f0:	41f0e8bd 	ldrhmi	lr, [r0, #141]!	; 0x8d
d00141f4:	bf76f7ff 	svclt	0x0076f7ff
d00141f8:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d

Disassembly of section .text.constant:

d00141fc <.text.constant>:
d00141fc:	2100460a 	tstcs	r0, sl, lsl #12
d0014200:	bfbef7ff 	svclt	0x00bef7ff

Disassembly of section .text.null_argument:

d001420c <.text.null_argument>:
d001420c:	f5a36ac3 			; <UNDEFINED> instruction: 0xf5a36ac3
d0014210:	2a017281 	bcs	0xd0070c1c
d0014214:	4604b570 			; <UNDEFINED> instruction: 0x4604b570
d0014218:	6a03d803 	bvs	0xd010a22c
d001421c:	2000b1eb 	andcs	fp, r0, fp, ror #3
d0014220:	f240bd70 	vmla.f32	<illegal reg q13.5>, q0, q8
d0014224:	42931201 	addsmi	r1, r3, #268435456	; 0x10000000
d0014228:	4a10d1f9 	bmi	0xd0448a14
d001422c:	5606e9d0 			; <UNDEFINED> instruction: 0x5606e9d0
d0014230:	4631447a 			; <UNDEFINED> instruction: 0x4631447a
d0014234:	f7fc4628 			; <UNDEFINED> instruction: 0xf7fc4628
d0014238:	2800fabc 	stmdacs	r0, {r2, r3, r4, r5, r7, r9, fp, ip, sp, lr, pc}
d001423c:	4632d0ef 	ldrtmi	sp, [r2], -pc, ror #1
d0014240:	46204629 	strtmi	r4, [r0], -r9, lsr #12
d0014244:	fa05f7fc 	blx	0xd019223c
d0014248:	dae82800 	ble	0xcfa1e250
d001424c:	46294632 			; <UNDEFINED> instruction: 0x46294632
d0014250:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0014254:	2800fa1e 	stmdacs	r0, {r1, r2, r3, r4, r9, fp, ip, sp, lr, pc}
d0014258:	4620dae1 	strtmi	sp, [r0], -r1, ror #21
d001425c:	fd0cf7fe 	stc2	7, cr15, [ip, #-1016]	; 0xfffffc08
d0014260:	21004620 	tstcs	r0, r0, lsr #12
d0014264:	ffcaf7ff 			; <UNDEFINED> instruction: 0xffcaf7ff
d0014268:	e7d92001 	ldrb	r2, [r9, r1]
d001426c:	ffffffd0 			; <UNDEFINED> instruction: 0xffffffd0

Disassembly of section .text.store_local:

d0014270 <.text.store_local>:
d0014270:	b570291f 	ldrblt	r2, [r0, #-2335]!	; 0xfffff6e1
d0014274:	b28db294 	addlt	fp, sp, #148, 4	; 0x40000009
d0014278:	ea44d80a 	b	0xd114a2a8
d001427c:	f4411185 	vst4.32	{d17,d19,d21,d23}, [r1], r5
d0014280:	f04141c0 			; <UNDEFINED> instruction: 0xf04141c0
d0014284:	b2890138 	addlt	r0, r9, #56, 2
d0014288:	4070e8bd 	ldrhtmi	lr, [r0], #-141	; 0xffffff73
d001428c:	bf5af7ff 	svclt	0x005af7ff
d0014290:	01c7f64f 	biceq	pc, r7, pc, asr #12
d0014294:	ff56f7ff 			; <UNDEFINED> instruction: 0xff56f7ff
d0014298:	ea4100a9 	b	0xd1054544
d001429c:	b2893104 	addlt	r3, r9, #4, 2
d00142a0:	Address 0x00000000d00142a0 is out of bounds.


Disassembly of section .text.local_address:

d00142a2 <.text.local_address>:
d00142a2:	4604b510 			; <UNDEFINED> instruction: 0x4604b510
d00142a6:	2100008a 	smlabbcs	r0, sl, r0, r0
d00142aa:	ff69f7ff 			; <UNDEFINED> instruction: 0xff69f7ff
d00142ae:	f6414620 			; <UNDEFINED> instruction: 0xf6414620
d00142b2:	e8bd0138 	pop	{r3, r4, r5, r8}
d00142b6:	f7ff4010 			; <UNDEFINED> instruction: 0xf7ff4010
d00142ba:	Address 0x00000000d00142ba is out of bounds.


Disassembly of section .text.emit_address:

d00142e4 <.text.emit_address>:
d00142e4:	460db570 			; <UNDEFINED> instruction: 0x460db570
d00142e8:	31aff500 			; <UNDEFINED> instruction: 0x31aff500
d00142ec:	680b4604 	stmdavs	fp, {r2, r9, sl, lr}
d00142f0:	6f00f5b3 	svcvs	0x0000f5b3
d00142f4:	4914d105 	ldmdbmi	r4, {r0, r2, r8, ip, lr, pc}
d00142f8:	4070e8bd 	ldrhtmi	lr, [r0], #-141	; 0xffffff73
d00142fc:	f7fb4479 			; <UNDEFINED> instruction: 0xf7fb4479
d0014300:	1c58bf53 	mrrcne	15, 5, fp, r8, cr3
d0014304:	03c3eb04 	biceq	lr, r3, #4, 22	; 0x1000
d0014308:	60082604 	andvs	r2, r8, r4, lsl #12
d001430c:	51f8f64d 	mvnspl	pc, sp, asr #12
d0014310:	338ff503 	orrcc	pc, pc, #12582912	; 0xc00000
d0014314:	809a5861 	addshi	r5, sl, r1, ror #16
d0014318:	719d6019 	orrsvc	r6, sp, r9, lsl r0
d001431c:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d0014320:	ff10f7ff 			; <UNDEFINED> instruction: 0xff10f7ff
d0014324:	d1f93e01 	mvnsle	r3, r1, lsl #28
d0014328:	4122f44f 	msrmi	CPSR_x, pc, asr #8
d001432c:	ff0af7ff 			; <UNDEFINED> instruction: 0xff0af7ff
d0014330:	bf0c2d01 	svclt	0x000c2d01
d0014334:	21002141 	tstcs	r0, r1, asr #2
d0014338:	51c0f441 	bicpl	pc, r0, r1, asr #8
d001433c:	4070e8bd 	ldrhtmi	lr, [r0], #-141	; 0xffffff73
d0014340:	0110f041 	tsteq	r0, r1, asr #32	; <UNPREDICTABLE>
d0014344:	befef7ff 	mrclt	7, 7, APSR_nzcv, cr14, cr15, {7}
d0014348:	ffffffbc 			; <UNDEFINED> instruction: 0xffffffbc

Disassembly of section .text.string_argument:

d001438c <.text.string_argument>:
d001438c:	f5b36ac3 			; <UNDEFINED> instruction: 0xf5b36ac3
d0014390:	e92d7f82 	push	{r1, r7, r8, r9, sl, fp, ip, sp, lr}
d0014394:	460447f0 			; <UNDEFINED> instruction: 0x460447f0
d0014398:	d006b086 	andle	fp, r6, r6, lsl #1
d001439c:	44794930 	ldrbtmi	r4, [r9], #-2352	; 0xfffff6d0
d00143a0:	ff02f7fb 			; <UNDEFINED> instruction: 0xff02f7fb
d00143a4:	e8bdb006 	pop	{r1, r2, ip, sp, pc}
d00143a8:	f64d87f0 			; <UNDEFINED> instruction: 0xf64d87f0
d00143ac:	f85055fc 			; <UNDEFINED> instruction: 0xf85055fc
d00143b0:	f5b88005 			; <UNDEFINED> instruction: 0xf5b88005
d00143b4:	d0264f80 	eorle	r4, r6, r0, lsl #31
d00143b8:	6a614405 	bvs	0xd18653d4
d00143bc:	f8946aa2 			; <UNDEFINED> instruction: 0xf8946aa2
d00143c0:	f8d4a030 			; <UNDEFINED> instruction: 0xf8d4a030
d00143c4:	e9d49034 	ldmib	r4, {r2, r4, r5, ip, pc}^
d00143c8:	97057306 	strls	r7, [r5, -r6, lsl #6]
d00143cc:	9805441f 	stmdals	r5, {r0, r1, r2, r3, r4, sl, lr}
d00143d0:	d11b42b8 			; <UNDEFINED> instruction: 0xd11b42b8
d00143d4:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d00143d8:	6ae3fc4f 	bvs	0xcf91351c
d00143dc:	7f82f5b3 	svcvc	0x0082f5b3
d00143e0:	6da3d102 	stfvsd	f5, [r3, #8]!
d00143e4:	d0e82b00 	rscle	r2, r8, r0, lsl #22
d00143e8:	52fcf64d 	rscspl	pc, ip, #80740352	; 0x4d00000
d00143ec:	58a34620 	stmiapl	r3!, {r5, r9, sl, lr}
d00143f0:	44231c59 	strtmi	r1, [r3], #-3161	; 0xfffff3a7
d00143f4:	f50350a1 			; <UNDEFINED> instruction: 0xf50350a1
d00143f8:	2100435e 	tstcs	r0, lr, asr r3
d00143fc:	70194642 	andsvc	r4, r9, r2, asr #12
d0014400:	ff70f7ff 			; <UNDEFINED> instruction: 0xff70f7ff
d0014404:	4917e7ce 	ldmdbmi	r7, {r1, r2, r3, r6, r7, r8, r9, sl, sp, lr, pc}
d0014408:	e7c94479 			; <UNDEFINED> instruction: 0xe7c94479
d001440c:	3301682b 	movwcc	r6, #6187	; 0x182b
d0014410:	4f80f5b3 	svcmi	0x0080f5b3
d0014414:	6da3d30b 	stcvs	3, cr13, [r3, #44]!	; 0x2c
d0014418:	d1c32b00 	bicle	r2, r3, r0, lsl #22
d001441c:	f8c44b12 			; <UNDEFINED> instruction: 0xf8c44b12
d0014420:	447b9068 	ldrbtmi	r9, [fp], #-104	; 0xffffff98
d0014424:	2a18e9c4 	bcs	0xd064eb3c
d0014428:	3116e9c4 	tstcc	r6, r4, asr #19
d001442c:	1c43e7ba 	mcrrne	7, 11, lr, r3, cr10
d0014430:	78009305 	stmdavc	r0, {r0, r2, r8, r9, ip, pc}
d0014434:	d108285c 	tstle	r8, ip, asr r8
d0014438:	4620ab05 	strtmi	sl, [r0], -r5, lsl #22
d001443c:	93019702 	movwls	r9, #5890	; 0x1702
d0014440:	f8cd4653 			; <UNDEFINED> instruction: 0xf8cd4653
d0014444:	f7fb9000 			; <UNDEFINED> instruction: 0xf7fb9000
d0014448:	6da3ffc1 	stcvs	15, cr15, [r3, #772]!	; 0x304
d001444c:	d1a92b00 			; <UNDEFINED> instruction: 0xd1a92b00
d0014450:	1c73682e 	ldclne	8, cr6, [r3], #-184	; 0xffffff48
d0014454:	f5064426 			; <UNDEFINED> instruction: 0xf5064426
d0014458:	602b465e 	eorvs	r4, fp, lr, asr r6
d001445c:	e7b67030 			; <UNDEFINED> instruction: 0xe7b67030
d0014460:	ffffffaa 			; <UNDEFINED> instruction: 0xffffffaa
d0014464:	ffffff63 			; <UNDEFINED> instruction: 0xffffff63
d0014468:	ffffff49 			; <UNDEFINED> instruction: 0xffffff49

Disassembly of section .text.branch:

d001446c <.text.branch>:
d001446c:	f64db538 			; <UNDEFINED> instruction: 0xf64db538
d0014470:	210053f8 	strdcs	r5, [r0, -r8]
d0014474:	f7ff58c5 			; <UNDEFINED> instruction: 0xf7ff58c5
d0014478:	2100fe65 	tstcs	r0, r5, ror #28	; <UNPREDICTABLE>
d001447c:	fe62f7ff 	mcr2	7, 3, pc, cr2, cr15, {7}	; <UNPREDICTABLE>
d0014480:	bd384628 	ldclt	6, cr4, [r8, #-160]!	; 0xffffff60

Disassembly of section .text.branch_on_value:

d0014484 <.text.branch_on_value>:
d0014484:	460db538 			; <UNDEFINED> instruction: 0x460db538
d0014488:	5120f44f 	msrpl	CPSR_, pc, asr #8
d001448c:	fe5af7ff 	mrc2	7, 2, pc, cr10, cr15, {7}
d0014490:	1301f24d 	movwne	pc, #4685	; 0x124d	; <UNPREDICTABLE>
d0014494:	0101f24d 	tsteq	r1, sp, asr #4	; <UNPREDICTABLE>
d0014498:	bf082d00 	svclt	0x00082d00
d001449c:	f7ff4619 			; <UNDEFINED> instruction: 0xf7ff4619
d00144a0:	e8bdfe51 	pop	{r0, r4, r6, r9, sl, fp, ip, sp, lr, pc}
d00144a4:	f7ff4038 			; <UNDEFINED> instruction: 0xf7ff4038
d00144a8:	Address 0x00000000d00144a8 is out of bounds.


Disassembly of section .text.boolean:

d00144aa <.text.boolean>:
d00144aa:	0301f24d 	movweq	pc, #4685	; 0x124d	; <UNPREDICTABLE>
d00144ae:	2101ea43 	tstcs	r1, r3, asr #20
d00144b2:	b289b510 	addlt	fp, r9, #16, 10	; 0x4000000
d00144b6:	fe45f7ff 	mcr2	7, 2, pc, cr5, cr15, {7}	; <UNPREDICTABLE>
d00144ba:	5100f44f 	tstpl	r0, pc, asr #8	; <UNPREDICTABLE>
d00144be:	fe41f7ff 	mcr2	7, 2, pc, cr1, cr15, {7}	; <UNPREDICTABLE>
d00144c2:	4160f44f 	msrmi	SPSR_, pc, asr #8
d00144c6:	fe3df7ff 	mrc2	7, 1, pc, cr13, cr15, {7}
d00144ca:	0101f242 	tsteq	r1, r2, asr #4	; <UNPREDICTABLE>
d00144ce:	4010e8bd 			; <UNDEFINED> instruction: 0x4010e8bd
d00144d2:	be37f7ff 	mrclt	7, 1, APSR_nzcv, cr7, cr15, {7}

Disassembly of section .text.prepare_call:

d00144d6 <.text.prepare_call>:
d00144d6:	e92d2904 	push	{r2, r8, fp, sp}
d00144da:	460d43f8 			; <UNDEFINED> instruction: 0x460d43f8
d00144de:	2504bf38 	strcs	fp, [r4, #-3896]	; 0xfffff0c8
d00144e2:	460c4607 	strmi	r4, [ip], -r7, lsl #12
d00144e6:	f0353d03 			; <UNDEFINED> instruction: 0xf0353d03
d00144ea:	d0060501 	andle	r0, r6, r1, lsl #10
d00144ee:	4130f445 	teqmi	r0, r5, asr #8	; <UNPREDICTABLE>
d00144f2:	0180f041 	orreq	pc, r0, r1, asr #32
d00144f6:	f7ffb289 			; <UNDEFINED> instruction: 0xf7ffb289
d00144fa:	1f66fe24 	svcne	0x0066fe24
d00144fe:	0904f04f 	stmdbeq	r4, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d0014502:	0846ea4f 	stmdaeq	r6, {r0, r1, r2, r3, r6, r9, fp, sp, lr, pc}^
d0014506:	0646eb05 	strbeq	lr, [r6], -r5, lsl #22
d001450a:	45a1b2b6 	strmi	fp, [r1, #694]!	; 0x2b6
d001450e:	f108d30c 			; <UNDEFINED> instruction: 0xf108d30c
d0014512:	f04f0608 			; <UNDEFINED> instruction: 0xf04f0608
d0014516:	442e0800 	strtmi	r0, [lr], #-2048	; 0xfffff800
d001451a:	45a0b2b6 	strmi	fp, [r0, #694]!	; 0x2b6
d001451e:	f1b8d026 			; <UNDEFINED> instruction: 0xf1b8d026
d0014522:	d1120f04 	tstle	r2, r4, lsl #30
d0014526:	e029bb1d 	eor	fp, r9, sp, lsl fp
d001452a:	4118f446 	tstmi	r8, r6, asr #8	; <UNPREDICTABLE>
d001452e:	f7ff4638 			; <UNDEFINED> instruction: 0xf7ff4638
d0014532:	f1a9fe08 			; <UNDEFINED> instruction: 0xf1a9fe08
d0014536:	3e020104 	adfccs	f0, f2, f4
d001453a:	0901f109 	stmdbeq	r1, {r0, r3, r8, ip, sp, lr, pc}
d001453e:	4110f441 	tstmi	r0, r1, asr #8	; <UNPREDICTABLE>
d0014542:	b289b2b6 	addlt	fp, r9, #1610612747	; 0x6000000b
d0014546:	fdfdf7ff 	ldc2l	7, cr15, [sp, #1020]!	; 0x3fc
d001454a:	fa1fe7df 	blx	0xd080e4ce
d001454e:	4638f388 	ldrtmi	pc, [r8], -r8, lsl #7	; <UNPREDICTABLE>
d0014552:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d0014556:	31c3ebc3 	biccc	lr, r3, r3, asr #23
d001455a:	0141eb06 	cmpeq	r1, r6, lsl #22
d001455e:	2103ea41 	tstcs	r3, r1, asr #20
d0014562:	4118f441 	tstmi	r8, r1, asr #8	; <UNPREDICTABLE>
d0014566:	f7ffb289 			; <UNDEFINED> instruction: 0xf7ffb289
d001456a:	e7d6fdec 	ldrb	pc, [r6, ip, ror #27]	; <UNPREDICTABLE>
d001456e:	eb05b125 	bl	0xd0180a0a
d0014572:	46200444 	strtmi	r0, [r0], -r4, asr #8
d0014576:	83f8e8bd 	mvnshi	lr, #12386304	; 0xbd0000
d001457a:	d0fa2c00 	rscsle	r2, sl, r0, lsl #24
d001457e:	46380061 	ldrtmi	r0, [r8], -r1, rrx
d0014582:	f4412400 	vst3.8	{d18-d20}, [r1], r0
d0014586:	b2894130 	addlt	r4, r9, #48, 2
d001458a:	fddbf7ff 	ldc2l	7, cr15, [fp, #1020]	; 0x3fc
d001458e:	Address 0x00000000d001458e is out of bounds.


Disassembly of section .text.binary:

d0014590 <.text.binary>:
d0014590:	b570292f 	ldrblt	r2, [r0, #-2351]!	; 0xfffff6d1
d0014594:	460e4604 	strmi	r4, [lr], -r4, lsl #12
d0014598:	dc0d4615 	stcle	6, cr4, [sp], {21}
d001459c:	dd0f2924 	vstrle.16	s4, [pc, #-72]	; 0xd001455c	; <UNPREDICTABLE>
d00145a0:	0325f1a1 	msreq	CPSR_sc, #1073741864	; 0x40000028
d00145a4:	d80b2b0a 	stmdale	fp, {r1, r3, r8, r9, fp, sp}
d00145a8:	f003e8df 			; <UNDEFINED> instruction: 0xf003e8df
d00145ac:	0a0a253a 	beq	0xd029da9c
d00145b0:	0a1b220a 	beq	0xd06dcde0
d00145b4:	002e0a4b 	eoreq	r0, lr, fp, asr #20
d00145b8:	d022295e 	eorle	r2, r2, lr, asr r9
d00145bc:	d01d297c 	andsle	r2, sp, ip, ror r9
d00145c0:	2181f244 	orrcs	pc, r1, r4, asr #4
d00145c4:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d00145c8:	f5b6fdbd 			; <UNDEFINED> instruction: 0xf5b6fdbd
d00145cc:	dc067f8f 	stcle	15, cr7, [r6], {143}	; 0x8f
d00145d0:	7f8df5b6 	svcvc	0x008df5b6
d00145d4:	2e3cdc38 	mrccs	12, 1, sp, cr12, cr8, {1}
d00145d8:	2e3ed04a 	cdpcs	0, 3, cr13, cr14, cr10, {2}
d00145dc:	2500d04d 	strcs	sp, [r0, #-77]	; 0xffffffb3
d00145e0:	f641e004 			; <UNDEFINED> instruction: 0xf641e004
d00145e4:	46200108 	strtmi	r0, [r0], -r8, lsl #2
d00145e8:	fdacf7ff 	stc2	7, cr15, [ip, #1020]!	; 0x3fc
d00145ec:	bd704628 	ldcllt	6, cr4, [r0, #-160]!	; 0xffffff60
d00145f0:	3148f244 	cmpcc	r8, r4, asr #4	; <UNPREDICTABLE>
d00145f4:	f244e7f7 	vaba.s8	q15, q10, <illegal reg q11.5>
d00145f8:	e7f40108 	ldrb	r0, [r4, r8, lsl #2]!
d00145fc:	3108f244 	tstcc	r8, r4, asr #4	; <UNPREDICTABLE>
d0014600:	f244e7f2 	vaba.s8	q15, q10, q9
d0014604:	e7ef0148 	strb	r0, [pc, r8, asr #2]!
d0014608:	3391f64f 	orrscc	pc, r1, #82837504	; 0x4f00000
d001460c:	31b1f64f 			; <UNDEFINED> instruction: 0x31b1f64f
d0014610:	bf082d00 	svclt	0x00082d00
d0014614:	f7ff4619 			; <UNDEFINED> instruction: 0xf7ff4619
d0014618:	f24ffd95 	vmla.f32	d31, d31, d5
d001461c:	e7e201f0 			; <UNDEFINED> instruction: 0xe7e201f0
d0014620:	3391f64f 	orrscc	pc, r1, #82837504	; 0x4f00000
d0014624:	31b1f64f 			; <UNDEFINED> instruction: 0x31b1f64f
d0014628:	bf082d00 	svclt	0x00082d00
d001462c:	f7ff4619 			; <UNDEFINED> instruction: 0xf7ff4619
d0014630:	f24ffd89 	vadd.f32	d31, d31, d9
d0014634:	f7ff21f0 			; <UNDEFINED> instruction: 0xf7ff21f0
d0014638:	f244fd85 	vadd.f32	d31, d20, d5
d001463c:	f7ff3150 			; <UNDEFINED> instruction: 0xf7ff3150
d0014640:	f641fd81 			; <UNDEFINED> instruction: 0xf641fd81
d0014644:	e7ce2108 	strb	r2, [lr, r8, lsl #2]
d0014648:	768ef5a6 	strvc	pc, [lr], r6, lsr #11
d001464c:	d8032e02 	stmdale	r3, {r1, r9, sl, fp, sp}
d0014650:	f006e8df 			; <UNDEFINED> instruction: 0xf006e8df
d0014654:	00091807 	andeq	r1, r9, r7, lsl #16
d0014658:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d001465c:	ff25f7ff 			; <UNDEFINED> instruction: 0xff25f7ff
d0014660:	2101e7bd 			; <UNDEFINED> instruction: 0x2101e7bd
d0014664:	2d00e7f9 	stccs	7, cr14, [r0, #-996]	; 0xfffffc1c
d0014668:	2102bf14 	tstcs	r2, r4, lsl pc
d001466c:	e7f4210a 	ldrb	r2, [r4, sl, lsl #2]!
d0014670:	bf142d00 	svclt	0x00142d00
d0014674:	210b2103 	tstcs	fp, r3, lsl #2
d0014678:	2d00e7ef 	stccs	7, cr14, [r0, #-956]	; 0xfffffc44
d001467c:	2108bf14 	tstcs	r8, r4, lsl pc
d0014680:	e7ea210c 	strb	r2, [sl, ip, lsl #2]!
d0014684:	bf142d00 	svclt	0x00142d00
d0014688:	210d2109 	tstcs	sp, r9, lsl #2
d001468c:	Address 0x00000000d001468c is out of bounds.


Disassembly of section .text.record_member_pointer:

d001471c <.text.record_member_pointer>:
d001471c:	447b4b42 	ldrbtmi	r4, [fp], #-2882	; 0xfffff4be
d0014720:	4ff0e92d 	svcmi	0x00f0e92d
d0014724:	460e4604 	strmi	r4, [lr], -r4, lsl #12
d0014728:	8b04ed2d 	blhi	0xd014fbe4
d001472c:	3a10ee09 	bcc	0xd044ff58
d0014730:	9203b085 	andls	fp, r3, #133	; 0x85
d0014734:	ee1969a3 	vnmls.f16	s12, s19, s7
d0014738:	f2402a10 	vpmin.s8	d18, d0, d0
d001473c:	46201101 	strtmi	r1, [r0], -r1, lsl #2
d0014740:	3a10ee08 	bcc	0xd044ff68
d0014744:	f8d469e3 			; <UNDEFINED> instruction: 0xf8d469e3
d0014748:	ee08b024 	cdp	0, 0, cr11, cr8, cr4, {1}
d001474c:	6aa33a90 	bvs	0xce8e3194
d0014750:	9030f894 	mlasls	r0, r4, r8, pc	; <UNPREDICTABLE>
d0014754:	6b639302 	blvs	0xd18f9364
d0014758:	f7fe9301 			; <UNDEFINED> instruction: 0xf7fe9301
d001475c:	b330fab6 	teqlt	r0, #745472	; 0xb6000	; <UNPREDICTABLE>
d0014760:	731af44f 	tstvc	sl, #1325400064	; 0x4f000000	; <UNPREDICTABLE>
d0014764:	fb032500 	blx	0xd00ddb6e
d0014768:	f507f706 			; <UNDEFINED> instruction: 0xf507f706
d001476c:	442738bc 	strtmi	r3, [r7], #-2236	; 0xfffff744
d0014770:	0828f108 	stmdaeq	r8!, {r3, r8, ip, sp, lr, pc}
d0014774:	37bdf507 	ldrcc	pc, [sp, r7, lsl #10]!
d0014778:	0a08eb04 	beq	0xd024f390
d001477c:	306af897 	mlscc	sl, r7, r8, pc	; <UNPREDICTABLE>
d0014780:	d81942ab 	ldmdale	r9, {r0, r1, r3, r5, r7, r9, lr}
d0014784:	731af44f 	tstvc	sl, #1325400064	; 0x4f000000	; <UNPREDICTABLE>
d0014788:	4606fb03 	strmi	pc, [r6], -r3, lsl #22
d001478c:	36bdf506 	ldrtcc	pc, [sp], r6, lsl #10	; <UNPREDICTABLE>
d0014790:	306af896 	mlscc	sl, r6, r8, pc	; <UNPREDICTABLE>
d0014794:	d11d42ab 	tstle	sp, fp, lsr #5
d0014798:	b9436da3 	stmdblt	r3, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d001479c:	447b4b23 	ldrbtmi	r4, [fp], #-2851	; 0xfffff4dd
d00147a0:	3b16e9c4 	blcc	0xd05ceeb8
d00147a4:	e9c49b02 	stmib	r4, {r1, r8, r9, fp, ip, pc}^
d00147a8:	9b013918 	blls	0xd0062c10
d00147ac:	b00566a3 	andlt	r6, r5, r3, lsr #13
d00147b0:	8b04ecbd 	blhi	0xd014faac
d00147b4:	8ff0e8bd 	svchi	0x00f0e8bd
d00147b8:	3004f8da 	ldrdcc	pc, [r4], -sl
d00147bc:	1a90ee18 	bne	0xce450024
d00147c0:	2b24f85a 	blcs	0xd0952930
d00147c4:	0a10ee18 	beq	0xd045002c
d00147c8:	fed4f7fb 	mrc2	7, 6, pc, cr4, cr11, {7}
d00147cc:	d1d92800 	bicsle	r2, r9, r0, lsl #16
d00147d0:	e7d33501 	ldrb	r3, [r3, r1, lsl #10]
d00147d4:	fb032324 	blx	0xd00dd46e
d00147d8:	44258505 	strtmi	r8, [r5], #-1285	; 0xfffffafb
d00147dc:	f8958c6a 			; <UNDEFINED> instruction: 0xf8958c6a
d00147e0:	b14a7020 	cmplt	sl, r0, lsr #32
d00147e4:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d00147e8:	f7ff0092 			; <UNDEFINED> instruction: 0xf7ff0092
d00147ec:	f44ffcc9 			; <UNDEFINED> instruction: 0xf44ffcc9
d00147f0:	462051c2 	strtmi	r5, [r0], -r2, asr #3
d00147f4:	fca6f7ff 	stc2	7, cr15, [r6], #1020	; 0x3fc
d00147f8:	d1052fff 	strdle	r2, [r5, -pc]
d00147fc:	2b006da3 	blcs	0xd002fe90
d0014800:	4b0bd1d5 	blmi	0xd0308f5c
d0014804:	e7cb447b 			; <UNDEFINED> instruction: 0xe7cb447b
d0014808:	4620212e 	strtmi	r2, [r0], -lr, lsr #2
d001480c:	f7fe463e 			; <UNDEFINED> instruction: 0xf7fe463e
d0014810:	2800fa4e 	stmdacs	r0, {r1, r2, r3, r6, r9, fp, ip, sp, lr, pc}
d0014814:	9b03d18e 	blls	0xd0108e54
d0014818:	d0c842bb 	strhle	r4, [r8], #43	; 0x2b
d001481c:	2b006da3 	blcs	0xd002feb0
d0014820:	4b04d1c5 	blmi	0xd0148f3c
d0014824:	e7bb447b 			; <UNDEFINED> instruction: 0xe7bb447b
d0014828:	ffffff6c 			; <UNDEFINED> instruction: 0xffffff6c
d001482c:	ffffff0a 			; <UNDEFINED> instruction: 0xffffff0a
d0014830:	fffffebf 			; <UNDEFINED> instruction: 0xfffffebf
d0014834:	fffffec5 			; <UNDEFINED> instruction: 0xfffffec5

Disassembly of section .text.load_local.constprop.0:

d0014838 <.text.load_local.constprop.0>:
d0014838:	b538291f 	ldrlt	r2, [r8, #-2335]!	; 0xfffff6e1
d001483c:	d808b28c 	stmdale	r8, {r2, r3, r7, r9, ip, sp, pc}
d0014840:	0138f646 	teqeq	r8, r6, asr #12	; <UNPREDICTABLE>
d0014844:	1184ea41 	orrne	lr, r4, r1, asr #20
d0014848:	e8bdb289 	pop	{r0, r3, r7, r9, ip, sp, pc}
d001484c:	f7ff4038 			; <UNDEFINED> instruction: 0xf7ff4038
d0014850:	f64fbc79 			; <UNDEFINED> instruction: 0xf64fbc79
d0014854:	f7ff01d7 			; <UNDEFINED> instruction: 0xf7ff01d7
d0014858:	00a1fc75 	adceq	pc, r1, r5, ror ip	; <UNPREDICTABLE>
d001485c:	e7f4b289 	ldrb	fp, [r4, r9, lsl #5]!

Disassembly of section .text.function_pointer_value.constprop.0:

d00148f4 <.text.function_pointer_value.constprop.0>:
d00148f4:	4ff7e92d 	svcmi	0x00f7e92d
d00148f8:	46054c4b 	strmi	r4, [r5], -fp, asr #24
d00148fc:	4620447c 			; <UNDEFINED> instruction: 0x4620447c
d0014900:	fc84f7ff 	stc2	7, cr15, [r4], {255}	; 0xff
d0014904:	2126bb98 			; <UNDEFINED> instruction: 0x2126bb98
d0014908:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d001490c:	4a47f9d0 	bmi	0xd1213054
d0014910:	f2406b63 	vqdmulh.s<illegal width 8>	q11, q0, <illegal reg q9.5>
d0014914:	447a1101 	ldrbtmi	r1, [sl], #-257	; 0xfffffeff
d0014918:	f8d44620 			; <UNDEFINED> instruction: 0xf8d44620
d001491c:	f8d49024 			; <UNDEFINED> instruction: 0xf8d49024
d0014920:	f8948028 			; <UNDEFINED> instruction: 0xf8948028
d0014924:	93017030 	movwls	r7, #4144	; 0x1030
d0014928:	b606e9d4 			; <UNDEFINED> instruction: 0xb606e9d4
d001492c:	f9cdf7fe 			; <UNDEFINED> instruction: 0xf9cdf7fe
d0014930:	4632b1e8 	ldrtmi	fp, [r2], -r8, ror #3
d0014934:	46204659 			; <UNDEFINED> instruction: 0x46204659
d0014938:	fe8bf7fb 	mcr2	7, 4, pc, cr11, cr11, {7}	; <UNPREDICTABLE>
d001493c:	0a00f1b0 	beq	0xd0051004
d0014940:	202cdb33 	eorcs	sp, ip, r3, lsr fp
d0014944:	f00afb00 			; <UNDEFINED> instruction: 0xf00afb00
d0014948:	f5031823 			; <UNDEFINED> instruction: 0xf5031823
d001494c:	f8933313 			; <UNDEFINED> instruction: 0xf8933313
d0014950:	2a0c230d 	bcs	0xd031d58c
d0014954:	4b36d00e 	blmi	0xd0dc8994
d0014958:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d001495c:	4a35b93a 	bmi	0xd0d82e4c
d0014960:	e9c3447a 	stmib	r3, {r1, r3, r4, r5, r6, sl, lr}^
d0014964:	9a012916 	bls	0xd005edc4
d0014968:	8718e9c3 	ldrhi	lr, [r8, -r3, asr #19]
d001496c:	b003669a 	mullt	r3, sl, r6
d0014970:	8ff0e8bd 	svchi	0x00f0e8bd
d0014974:	f8937829 			; <UNDEFINED> instruction: 0xf8937829
d0014978:	428a230f 	addmi	r2, sl, #1006632960	; 0x3c000000
d001497c:	f893d1eb 			; <UNDEFINED> instruction: 0xf893d1eb
d0014980:	786b1310 	stmdavc	fp!, {r4, r8, r9, ip}^
d0014984:	d1e64299 			; <UNDEFINED> instruction: 0xd1e64299
d0014988:	3013f500 	andscc	pc, r3, r0, lsl #10
d001498c:	f2001ca9 			; <UNDEFINED> instruction: 0xf2001ca9
d0014990:	44203011 	strtmi	r3, [r0], #-17	; 0xffffffef
d0014994:	fd82f007 	stc2	0, cr15, [r2, #28]
d0014998:	d1dc2800 	bicsle	r2, ip, r0, lsl #16
d001499c:	46204651 			; <UNDEFINED> instruction: 0x46204651
d00149a0:	e8bdb003 	pop	{r0, r1, ip, sp, pc}
d00149a4:	f7ff4ff0 			; <UNDEFINED> instruction: 0xf7ff4ff0
d00149a8:	4632bf47 	ldrtmi	fp, [r2], -r7, asr #30
d00149ac:	46204659 			; <UNDEFINED> instruction: 0x46204659
d00149b0:	fed7f7fb 	mrc2	7, 6, pc, cr7, cr11, {7}
d00149b4:	0a00f1b0 	beq	0xd005107c
d00149b8:	4632db2d 	ldrtmi	sp, [r2], -sp, lsr #22
d00149bc:	46204659 			; <UNDEFINED> instruction: 0x46204659
d00149c0:	fe67f7fb 	mcr2	7, 3, pc, cr7, cr11, {7}	; <UNPREDICTABLE>
d00149c4:	da262800 	ble	0xd099e9cc
d00149c8:	fb032334 	blx	0xd00dd6a2
d00149cc:	18e1f30a 	stmiane	r1!, {r1, r3, r8, r9, ip, sp, lr, pc}^
d00149d0:	1201f101 	andne	pc, r1, #1073741824	; 0x40000000
d00149d4:	424bf502 	submi	pc, fp, #8388608	; 0x800000
d00149d8:	b9e27812 	stmiblt	r2!, {r1, r4, fp, ip, sp, lr}^
d00149dc:	31e5f501 	mvncc	pc, r1, lsl #10
d00149e0:	f8917828 			; <UNDEFINED> instruction: 0xf8917828
d00149e4:	42822100 	addmi	r2, r2, #0, 2
d00149e8:	f891d115 			; <UNDEFINED> instruction: 0xf891d115
d00149ec:	78690103 	stmdavc	r9!, {r0, r1, r8}^
d00149f0:	d1104288 	tstle	r0, r8, lsl #5
d00149f4:	33e5f503 	mvncc	pc, #12582912	; 0xc00000
d00149f8:	f5031ca9 			; <UNDEFINED> instruction: 0xf5031ca9
d00149fc:	18e07383 	stmiane	r0!, {r0, r1, r7, r8, r9, ip, sp, lr}^
d0014a00:	fd4cf007 	stc2l	0, cr15, [ip, #-28]	; 0xffffffe4
d0014a04:	4652b938 			; <UNDEFINED> instruction: 0x4652b938
d0014a08:	46202102 	strtmi	r2, [r0], -r2, lsl #2
d0014a0c:	e8bdb003 	pop	{r0, r1, ip, sp, pc}
d0014a10:	f7ff4ff0 			; <UNDEFINED> instruction: 0xf7ff4ff0
d0014a14:	4b08bc67 	blmi	0xd0243bb8
d0014a18:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d0014a1c:	d1a62a00 			; <UNDEFINED> instruction: 0xd1a62a00
d0014a20:	447a4a06 	ldrbtmi	r4, [sl], #-2566	; 0xfffff5fa
d0014a24:	bf00e79d 	svclt	0x0000e79d
d0014a28:	0000a4f8 	strdeq	sl, [r0], -r8
d0014a2c:	ffffff46 			; <UNDEFINED> instruction: 0xffffff46
d0014a30:	0000a49c 	muleq	r0, ip, r4
d0014a34:	ffffff34 			; <UNDEFINED> instruction: 0xffffff34
d0014a38:	0000a3dc 	ldrdeq	sl, [r0], -ip
d0014a3c:	fffffe9a 			; <UNDEFINED> instruction: 0xfffffe9a

Disassembly of section .text.local_callback_declaration.constprop.0:

d0014be4 <.text.local_callback_declaration.constprop.0>:
d0014be4:	47f0e92d 	ldrbmi	lr, [r0, sp, lsr #18]!
d0014be8:	b0904e61 	addslt	r4, r0, r1, ror #28
d0014bec:	46804a61 	strmi	r4, [r0], r1, ror #20
d0014bf0:	2128447e 			; <UNDEFINED> instruction: 0x2128447e
d0014bf4:	4630447a 			; <UNDEFINED> instruction: 0x4630447a
d0014bf8:	f867f7fe 			; <UNDEFINED> instruction: 0xf867f7fe
d0014bfc:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d0014c00:	4a5d80b3 	bmi	0xd1774ed4
d0014c04:	4630212a 	ldrtmi	r2, [r0], -sl, lsr #2
d0014c08:	f7fe447a 			; <UNDEFINED> instruction: 0xf7fe447a
d0014c0c:	2800f85e 	stmdacs	r0, {r1, r2, r3, r4, r6, fp, ip, sp, lr, pc}
d0014c10:	80aaf000 	adchi	pc, sl, r0
d0014c14:	0518f106 	ldreq	pc, [r8, #-262]	; 0xfffffefa
d0014c18:	f10dac08 			; <UNDEFINED> instruction: 0xf10dac08
d0014c1c:	cd0f0920 	vstrgt.16	s0, [pc, #-64]	; 0xd0014be4	; <UNPREDICTABLE>
d0014c20:	e895c40f 	ldm	r5, {r0, r1, r2, r3, sl, lr, pc}
d0014c24:	e884000f 	stm	r4, {r0, r1, r2, r3}
d0014c28:	4a54000f 	bmi	0xd1514c6c
d0014c2c:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d0014c30:	447a4630 	ldrbtmi	r4, [sl], #-1584	; 0xfffff9d0
d0014c34:	f849f7fe 			; <UNDEFINED> instruction: 0xf849f7fe
d0014c38:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d0014c3c:	4a508095 	bmi	0xd1434e98
d0014c40:	46302129 	ldrtmi	r2, [r0], -r9, lsr #2
d0014c44:	f7fe447a 			; <UNDEFINED> instruction: 0xf7fe447a
d0014c48:	2800f840 	stmdacs	r0, {r6, fp, ip, sp, lr, pc}
d0014c4c:	808cf000 	addhi	pc, ip, r0
d0014c50:	21284a4c 			; <UNDEFINED> instruction: 0x21284a4c
d0014c54:	447a4630 	ldrbtmi	r4, [sl], #-1584	; 0xfffff9d0
d0014c58:	f837f7fe 			; <UNDEFINED> instruction: 0xf837f7fe
d0014c5c:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d0014c60:	6af38083 	bvs	0xcfcf4e74
d0014c64:	af062400 	svcge	0x00062400
d0014c68:	7f84f5b3 	svcvc	0x0084f5b3
d0014c6c:	80bc9406 	adcshi	r9, ip, r6, lsl #8
d0014c70:	d14a71bc 	strhle	r7, [sl, #-28]	; 0xffffffe4
d0014c74:	2b296cf3 	blcs	0xd0a70048
d0014c78:	4630d149 	ldrtmi	sp, [r0], -r9, asr #2
d0014c7c:	fffcf7fd 			; <UNDEFINED> instruction: 0xfffcf7fd
d0014c80:	21294d41 			; <UNDEFINED> instruction: 0x21294d41
d0014c84:	447d4a41 	ldrbtmi	r4, [sp], #-2625	; 0xfffff5bf
d0014c88:	4628447a 			; <UNDEFINED> instruction: 0x4628447a
d0014c8c:	f81df7fe 			; <UNDEFINED> instruction: 0xf81df7fe
d0014c90:	d0692800 	rsble	r2, r9, r0, lsl #16
d0014c94:	9304230c 	movwls	r2, #17164	; 0x430c
d0014c98:	e913ab10 	ldmdb	r3, {r4, r8, r9, fp, sp, pc}
d0014c9c:	e88d000f 	stm	sp, {r0, r1, r2, r3}
d0014ca0:	e899000f 	ldm	r9, {r0, r1, r2, r3}
d0014ca4:	f7fe000f 			; <UNDEFINED> instruction: 0xf7fe000f
d0014ca8:	6dabfcbf 	stcvs	12, cr15, [fp, #764]!	; 0x2fc
d0014cac:	2b004606 	blcs	0xd00264cc
d0014cb0:	232cd15a 			; <UNDEFINED> instruction: 0x232cd15a
d0014cb4:	4018f88d 	andsmi	pc, r8, sp, lsl #17
d0014cb8:	46392207 	ldrtmi	r2, [r9], -r7, lsl #4
d0014cbc:	f400fb03 			; <UNDEFINED> instruction: 0xf400fb03
d0014cc0:	8019f88d 	andshi	pc, r9, sp, lsl #17
d0014cc4:	f5001928 			; <UNDEFINED> instruction: 0xf5001928
d0014cc8:	f2003013 	vqadd.s8	d3, d0, d3
d0014ccc:	f007300f 			; <UNDEFINED> instruction: 0xf007300f
d0014cd0:	213dfbd5 	teqcs	sp, r5	; <illegal shifter operand>	; <UNPREDICTABLE>
d0014cd4:	f7fd4628 			; <UNDEFINED> instruction: 0xf7fd4628
d0014cd8:	4601ffea 	strmi	pc, [r1], -sl, ror #31
d0014cdc:	d03f2800 	eorsle	r2, pc, r0, lsl #16
d0014ce0:	3013f504 	andscc	pc, r3, r4, lsl #10
d0014ce4:	300ff200 	andcc	pc, pc, r0, lsl #4
d0014ce8:	f7ff4428 			; <UNDEFINED> instruction: 0xf7ff4428
d0014cec:	4828fe03 	stmdami	r8!, {r0, r1, r9, sl, fp, ip, sp, lr, pc}
d0014cf0:	22004631 	andcs	r4, r0, #51380224	; 0x3100000
d0014cf4:	f7ff4478 			; <UNDEFINED> instruction: 0xf7ff4478
d0014cf8:	4a26fabb 	bmi	0xd09d37ec
d0014cfc:	447a213b 	ldrbtmi	r2, [sl], #-315	; 0xfffffec5
d0014d00:	e8bdb010 	pop	{r4, ip, sp, pc}
d0014d04:	f7fd47f0 			; <UNDEFINED> instruction: 0xf7fd47f0
d0014d08:	2b29bfe0 	blcs	0xd0a84c90
d0014d0c:	f8dfd0b8 			; <UNDEFINED> instruction: 0xf8dfd0b8
d0014d10:	f10da088 			; <UNDEFINED> instruction: 0xf10da088
d0014d14:	4d21061a 	stcmi	6, cr0, [r1, #-104]!	; 0xffffff98
d0014d18:	44fa2400 	ldrbtmi	r2, [sl], #1024	; 0x400
d0014d1c:	4652447d 			; <UNDEFINED> instruction: 0x4652447d
d0014d20:	1107f240 	tstne	r7, r0, asr #4	; <UNPREDICTABLE>
d0014d24:	f7fd4628 			; <UNDEFINED> instruction: 0xf7fd4628
d0014d28:	b1e8ffd0 	ldrdlt	pc, [r8, #240]!	; 0xf0
d0014d2c:	f2402300 	vcgt.s8	d18, d0, d0
d0014d30:	34011101 	strcc	r1, [r1], #-257	; 0xfffffeff
d0014d34:	f8064628 			; <UNDEFINED> instruction: 0xf8064628
d0014d38:	f7fd3b01 			; <UNDEFINED> instruction: 0xf7fd3b01
d0014d3c:	212cffb8 	msrcs	LR_mon, r8
d0014d40:	b2e44628 	rsclt	r4, r4, #40, 12	; 0x2800000
d0014d44:	ffb3f7fd 			; <UNDEFINED> instruction: 0xffb3f7fd
d0014d48:	d0992800 	addsle	r2, r9, r0, lsl #16
d0014d4c:	d1e62c05 	mvnle	r2, r5, lsl #24
d0014d50:	46284913 			; <UNDEFINED> instruction: 0x46284913
d0014d54:	b0104479 	andslt	r4, r0, r9, ror r4
d0014d58:	47f0e8bd 			; <UNDEFINED> instruction: 0x47f0e8bd
d0014d5c:	ba24f7fb 	blt	0xd0952d50
d0014d60:	f7ff4628 			; <UNDEFINED> instruction: 0xf7ff4628
d0014d64:	e7c2fa4b 	strb	pc, [r2, fp, asr #20]	; <UNPREDICTABLE>
d0014d68:	e8bdb010 	pop	{r4, ip, sp, pc}
d0014d6c:	bf0087f0 	svclt	0x000087f0
d0014d70:	0000a204 	andeq	sl, r0, r4, lsl #4
d0014d74:	fffffe48 			; <UNDEFINED> instruction: 0xfffffe48
d0014d78:	fffffe61 			; <UNDEFINED> instruction: 0xfffffe61
d0014d7c:	fffffe64 			; <UNDEFINED> instruction: 0xfffffe64
d0014d80:	fffffe7a 			; <UNDEFINED> instruction: 0xfffffe7a
d0014d84:	fffffe95 			; <UNDEFINED> instruction: 0xfffffe95
d0014d88:	0000a16e 	andeq	sl, r0, lr, ror #2
d0014d8c:	fffffef6 			; <UNDEFINED> instruction: 0xfffffef6
d0014d90:	0000a100 	andeq	sl, r0, r0, lsl #2
d0014d94:	fffffeaf 			; <UNDEFINED> instruction: 0xfffffeaf
d0014d98:	fffffe35 			; <UNDEFINED> instruction: 0xfffffe35
d0014d9c:	0000a0d8 	ldrdeq	sl, [r0], -r8
d0014da0:	fffffdcc 			; <UNDEFINED> instruction: 0xfffffdcc

Disassembly of section .text.increment_scalar.isra.0:

d0014dd0 <.text.increment_scalar.isra.0>:
d0014dd0:	43f8e92d 	mvnsmi	lr, #737280	; 0xb4000
d0014dd4:	8030f8dd 	ldrsbthi	pc, [r0], -sp	; <UNPREDICTABLE>
d0014dd8:	460d4604 	strmi	r4, [sp], -r4, lsl #12
d0014ddc:	46994617 			; <UNDEFINED> instruction: 0x46994617
d0014de0:	fc37f7fb 	ldc2	7, cr15, [r7], #-1004	; 0xfffffc14
d0014de4:	da7a1e06 	ble	0xd1e9c604
d0014de8:	4629463a 			; <UNDEFINED> instruction: 0x4629463a
d0014dec:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0014df0:	1e07fc50 	mcrne	12, 0, pc, cr7, cr0, {2}	; <UNPREDICTABLE>
d0014df4:	2334db1b 	teqcs	r4, #27648	; 0x6c00
d0014df8:	4307fb03 	movwmi	pc, #31491	; 0x7b03	; <UNPREDICTABLE>
d0014dfc:	33aff503 			; <UNDEFINED> instruction: 0x33aff503
d0014e00:	502cf893 	mlapl	ip, r3, r8, pc	; <UNPREDICTABLE>
d0014e04:	2a0f1eaa 	bcs	0xd03dc8b4
d0014e08:	f64fd804 			; <UNDEFINED> instruction: 0xf64fd804
d0014e0c:	40d363f5 	ldrshmi	r6, [r3], #53	; 0x35
d0014e10:	d40c07da 	strle	r0, [ip], #-2010	; 0xfffff826
d0014e14:	da1a2e00 	ble	0xd06a061c
d0014e18:	463a4620 	ldrtmi	r4, [sl], -r0, lsr #12
d0014e1c:	f7ff2101 			; <UNDEFINED> instruction: 0xf7ff2101
d0014e20:	f646fa61 			; <UNDEFINED> instruction: 0xf646fa61
d0014e24:	46200108 	strtmi	r0, [r0], -r8, lsl #2
d0014e28:	f98cf7ff 			; <UNDEFINED> instruction: 0xf98cf7ff
d0014e2c:	6da0e013 	stcvs	0, cr14, [r0, #76]!	; 0x4c
d0014e30:	d1502800 	cmple	r0, r0, lsl #16
d0014e34:	447b4b2f 	ldrbtmi	r4, [fp], #-2863	; 0xfffff4d1
d0014e38:	3916e9c4 	ldmdbcc	r6, {r2, r6, r7, r8, fp, sp, lr, pc}
d0014e3c:	66239b08 	strtvs	r9, [r3], -r8, lsl #22
d0014e40:	3024f89d 	mlacc	r4, sp, r8, pc	; <UNPREDICTABLE>
d0014e44:	9b0a6663 	blls	0xd02ae7d8
d0014e48:	e8bd66a3 	pop	{r0, r1, r5, r7, r9, sl, sp, lr}
d0014e4c:	463183f8 			; <UNDEFINED> instruction: 0x463183f8
d0014e50:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0014e54:	f1b8fcf1 			; <UNDEFINED> instruction: 0xf1b8fcf1
d0014e58:	d0040f00 	andle	r0, r4, r0, lsl #30
d0014e5c:	4101f24b 	tstmi	r1, fp, asr #4	; <UNPREDICTABLE>
d0014e60:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0014e64:	9b0bf96f 	blls	0xd0313428
d0014e68:	f5b34620 			; <UNDEFINED> instruction: 0xf5b34620
d0014e6c:	bf077f91 	svclt	0x00077f91
d0014e70:	0104f243 	tsteq	r4, r3, asr #4	; <UNPREDICTABLE>
d0014e74:	0301f243 	movweq	pc, #4675	; 0x1243	; <UNPREDICTABLE>
d0014e78:	0104f643 	tsteq	r4, r3, asr #12	; <UNPREDICTABLE>
d0014e7c:	0301f643 	movweq	pc, #5699	; 0x1643	; <UNPREDICTABLE>
d0014e80:	bf182d0a 	svclt	0x00182d0a
d0014e84:	f7ff4619 			; <UNDEFINED> instruction: 0xf7ff4619
d0014e88:	2d05f95d 	vstrcs.16	s30, [r5, #-186]	; 0xffffff46	; <UNPREDICTABLE>
d0014e8c:	f24bd103 	vrhadd.s8	d29, d11, d3
d0014e90:	f7ff21c0 			; <UNDEFINED> instruction: 0xf7ff21c0
d0014e94:	2e00f957 			; <UNDEFINED> instruction: 0x2e00f957
d0014e98:	2200db12 	andcs	sp, r0, #18432	; 0x4800
d0014e9c:	46204631 			; <UNDEFINED> instruction: 0x46204631
d0014ea0:	f9e6f7ff 			; <UNDEFINED> instruction: 0xf9e6f7ff
d0014ea4:	0f00f1b8 	svceq	0x0000f1b8
d0014ea8:	f64bd004 			; <UNDEFINED> instruction: 0xf64bd004
d0014eac:	46204101 	strtmi	r4, [r0], -r1, lsl #2
d0014eb0:	f948f7ff 			; <UNDEFINED> instruction: 0xf948f7ff
d0014eb4:	d0102d0a 	andsle	r2, r0, sl, lsl #26
d0014eb8:	42581e6b 	subsmi	r1, r8, #1712	; 0x6b0
d0014ebc:	e7c44158 			; <UNDEFINED> instruction: 0xe7c44158
d0014ec0:	463a4620 	ldrtmi	r4, [sl], -r0, lsr #12
d0014ec4:	f7ff2101 			; <UNDEFINED> instruction: 0xf7ff2101
d0014ec8:	f246fa0d 	vpmax.s8	d31, d6, d13
d0014ecc:	46200108 	strtmi	r0, [r0], -r8, lsl #2
d0014ed0:	f938f7ff 			; <UNDEFINED> instruction: 0xf938f7ff
d0014ed4:	2000e7e6 	andcs	lr, r0, r6, ror #15
d0014ed8:	2004e7b7 			; <UNDEFINED> instruction: 0x2004e7b7
d0014edc:	222ce7b5 	eorcs	lr, ip, #47448064	; 0x2d40000
d0014ee0:	37fff04f 	ldrbcc	pc, [pc, pc, asr #32]!	; <UNPREDICTABLE>
d0014ee4:	4206fb02 	andmi	pc, r6, #2048	; 0x800
d0014ee8:	3213f502 	andscc	pc, r3, #8388608	; 0x800000
d0014eec:	530df892 	movwpl	pc, #55442	; 0xd892	; <UNPREDICTABLE>
d0014ef0:	bf00e788 	svclt	0x0000e788
d0014ef4:	ffffff6a 			; <UNDEFINED> instruction: 0xffffff6a

Disassembly of section .text.patch_branch.isra.0.part.0:

d0014ef8 <.text.patch_branch.isra.0.part.0>:
d0014ef8:	2a001a09 	bcs	0xd001b724
d0014efc:	0104f1a1 	smlatbeq	r4, r1, r1, pc	; <UNPREDICTABLE>
d0014f00:	f44fbf14 			; <UNDEFINED> instruction: 0xf44fbf14
d0014f04:	f44f4250 	vst1.16	{d20-d23}, [pc :64], r0
d0014f08:	b5f04210 	ldrblt	r4, [r0, #528]!	; 0x210
d0014f0c:	6600f3c1 	strvs	pc, [r0], -r1, asr #7
d0014f10:	3409f3c1 	strcc	pc, [r9], #-961	; 0xfffffc3f
d0014f14:	ea864f11 	b	0xce1a8b60
d0014f18:	ea4453d1 	b	0xd1129e64
d0014f1c:	447f2486 	ldrbtmi	r2, [pc], #-1158	; 0xd0014f24
d0014f20:	f44443db 	vst2.<illegal width 64>	{d20-d23}, [r4 :64], fp
d0014f24:	f0034470 			; <UNDEFINED> instruction: 0xf0034470
d0014f28:	ea860501 	b	0xce196334
d0014f2c:	f3c15391 	vrsra.u64	d21, d1, #63
d0014f30:	183e014a 	ldmdane	lr!, {r1, r3, r6, r8}
d0014f34:	f88643db 			; <UNDEFINED> instruction: 0xf88643db
d0014f38:	0a244040 	beq	0xd0925040
d0014f3c:	0301f003 	movweq	pc, #4099	; 0x1003	; <UNPREDICTABLE>
d0014f40:	4041f886 	submi	pc, r1, r6, lsl #17
d0014f44:	ea4302db 	b	0xd10d5ab8
d0014f48:	430b3345 	movwmi	r3, #45893	; 0xb345
d0014f4c:	f8864313 			; <UNDEFINED> instruction: 0xf8864313
d0014f50:	0a1b3042 	beq	0xd06e1060
d0014f54:	3043f886 	subcc	pc, r3, r6, lsl #17
d0014f58:	bf00bdf0 	svclt	0x0000bdf0
d0014f5c:	00031926 	andeq	r1, r3, r6, lsr #18

Disassembly of section .text.patch_branch.isra.0:

d0014f60 <.text.patch_branch.isra.0>:
d0014f60:	4604b410 			; <UNDEFINED> instruction: 0x4604b410
d0014f64:	46114608 	ldrmi	r4, [r1], -r8, lsl #12
d0014f68:	b91c461a 	ldmdblt	ip, {r1, r3, r4, r9, sl, lr}
d0014f6c:	4b04f85d 	blmi	0xd01530e8
d0014f70:	bfc2f7ff 	svclt	0x00c2f7ff
d0014f74:	4b04f85d 	blmi	0xd01530f0
d0014f78:	Address 0x00000000d0014f78 is out of bounds.


Disassembly of section .text.unary:

d0015548 <.text.unary>:
d0015548:	4ff0e92d 	svcmi	0x00f0e92d
d001554c:	46046d82 	strmi	r6, [r4], -r2, lsl #27
d0015550:	ed2d460e 	stc	6, cr4, [sp, #-56]!	; 0xffffffc8
d0015554:	b08d8b02 	addlt	r8, sp, r2, lsl #22
d0015558:	2a009209 	bcs	0xd0039d84
d001555c:	86dcf040 	ldrbhi	pc, [ip], r0, asr #32	; <UNPREDICTABLE>
d0015560:	f5006a83 			; <UNDEFINED> instruction: 0xf5006a83
d0015564:	f8d03b16 			; <UNDEFINED> instruction: 0xf8d03b16
d0015568:	9307a02c 	movwls	sl, #28716	; 0x702c
d001556c:	3030f890 	mlascc	r0, r0, r8, pc	; <UNPREDICTABLE>
d0015570:	6b439308 	blvs	0xd10fa198
d0015574:	f8db9306 			; <UNDEFINED> instruction: 0xf8db9306
d0015578:	330131f8 	movwcc	r3, #4600	; 0x11f8
d001557c:	e9d02b20 	ldmib	r0, {r5, r8, r9, fp, sp}^
d0015580:	e9d08906 	ldmib	r0, {r1, r2, r8, fp, pc}^
d0015584:	f8cb5708 			; <UNDEFINED> instruction: 0xf8cb5708
d0015588:	d90631f8 	stmdble	r6, {r3, r4, r5, r6, r7, r8, ip, sp}
d001558c:	1cdcf8df 	ldclne	8, cr15, [ip], {223}	; 0xdf
d0015590:	f7fa4479 			; <UNDEFINED> instruction: 0xf7fa4479
d0015594:	2500fe09 	strcs	pc, [r0, #-3593]	; 0xfffff1f7
d0015598:	f44fe01d 	vst4.8	{d30-d33}, [pc :64]!
d001559c:	f7fd718d 			; <UNDEFINED> instruction: 0xf7fd718d
d00155a0:	b140fb86 	smlalbblt	pc, r0, r6, fp	; <UNPREDICTABLE>
d00155a4:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d00155a8:	4601fd23 	strmi	pc, [r1], -r3, lsr #26
d00155ac:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d00155b0:	2501fe25 	strcs	pc, [r1, #-3621]	; 0xfffff1db
d00155b4:	f44fe00f 	vst4.8	{d30-d33}, [pc]
d00155b8:	46207181 	strtmi	r7, [r0], -r1, lsl #3
d00155bc:	fb77f7fd 	blx	0xd1e135ba
d00155c0:	4620b198 			; <UNDEFINED> instruction: 0x4620b198
d00155c4:	f7fe4629 			; <UNDEFINED> instruction: 0xf7fe4629
d00155c8:	f240fe19 			; <UNDEFINED> instruction: 0xf240fe19
d00155cc:	45821003 	strmi	r1, [r2, #3]
d00155d0:	2500bf14 	strcs	fp, [r0, #-3860]	; 0xfffff0ec
d00155d4:	f5042501 			; <UNDEFINED> instruction: 0xf5042501
d00155d8:	46283416 			; <UNDEFINED> instruction: 0x46283416
d00155dc:	31f8f8d4 	ldrsbcc	pc, [r8, #132]!	; 0x84	; <UNPREDICTABLE>
d00155e0:	f8c43b01 			; <UNDEFINED> instruction: 0xf8c43b01
d00155e4:	f00031f8 			; <UNDEFINED> instruction: 0xf00031f8
d00155e8:	f240bcec 	sha1c.32	<illegal reg q13.5>, q8, q14
d00155ec:	46201103 	strtmi	r1, [r0], -r3, lsl #2
d00155f0:	fb5df7fd 	blx	0xd17935ee
d00155f4:	d1e42800 	mvnle	r2, r0, lsl #16
d00155f8:	7191f44f 	orrsvc	pc, r1, pc, asr #8
d00155fc:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0015600:	b1f8fb56 	mvnslt	pc, r6, asr fp	; <UNPREDICTABLE>
d0015604:	2c68f8df 	stclcs	8, cr15, [r8], #-892	; 0xfffffc84
d0015608:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d001560c:	46206a63 	strtmi	r6, [r0], -r3, ror #20
d0015610:	6aa7447a 	bvs	0xce9e6800
d0015614:	8030f894 	mlashi	r0, r4, r8, pc	; <UNPREDICTABLE>
d0015618:	9034f8d4 	ldrsbtls	pc, [r4], -r4	; <UNPREDICTABLE>
d001561c:	e9d49306 	ldmib	r4, {r1, r2, r8, r9, ip, pc}^
d0015620:	f7fd5606 			; <UNDEFINED> instruction: 0xf7fd5606
d0015624:	2800fb52 	stmdacs	r0, {r1, r4, r6, r8, r9, fp, ip, sp, lr, pc}
d0015628:	84c6f000 	strbhi	pc, [r6], #0	; <UNPREDICTABLE>
d001562c:	9b062200 	blls	0xd019de34
d0015630:	92044629 	andls	r4, r4, #42991616	; 0x2900000
d0015634:	e88d4632 	stm	sp, {r1, r4, r5, r9, sl, lr}
d0015638:	46200780 	strtmi	r0, [r0], -r0, lsl #15
d001563c:	fbc8f7ff 	blx	0xcf253642
d0015640:	e7c84605 	strb	r4, [r8, r5, lsl #12]
d0015644:	1123f240 	msrne	R11_usr, r0
d0015648:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d001564c:	2800fb30 	stmdacs	r0, {r4, r5, r8, r9, fp, ip, sp, lr, pc}
d0015650:	f240d1d8 	vand	<illegal reg q14.5>, q8, q4
d0015654:	46201101 	strtmi	r1, [r0], -r1, lsl #2
d0015658:	fb29f7fd 	blx	0xd0a93656
d001565c:	28004605 	stmdacs	r0, {r0, r2, r9, sl, lr}
d0015660:	8491f000 	ldrhi	pc, [r1], #0
d0015664:	46202128 	strtmi	r2, [r0], -r8, lsr #2
d0015668:	fb21f7fd 	blx	0xd0893666
d001566c:	28004605 	stmdacs	r0, {r0, r2, r9, sl, lr}
d0015670:	82d4f000 	sbcshi	pc, r4, #0
d0015674:	464a4641 	strbmi	r4, [sl], -r1, asr #12
d0015678:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d001567c:	1e01ffea 	cdpne	15, 0, cr15, cr1, cr10, {7}
d0015680:	232cdb08 			; <UNDEFINED> instruction: 0x232cdb08
d0015684:	4301fb03 	movwmi	pc, #6915	; 0x1b03	; <UNPREDICTABLE>
d0015688:	3313f503 	tstcc	r3, #12582912	; 0xc00000	; <UNPREDICTABLE>
d001568c:	330df893 	movwcc	pc, #55443	; 0xd893	; <UNPREDICTABLE>
d0015690:	d02b2b0c 	eorle	r2, fp, ip, lsl #22
d0015694:	4b50f504 	blmi	0xd1452aac
d0015698:	4a50f504 	bmi	0xd1452ab0
d001569c:	f10b2500 			; <UNDEFINED> instruction: 0xf10b2500
d00156a0:	f10a0b24 			; <UNDEFINED> instruction: 0xf10a0b24
d00156a4:	f8da0a1c 			; <UNDEFINED> instruction: 0xf8da0a1c
d00156a8:	429d3000 	addsmi	r3, sp, #0
d00156ac:	464ad32f 	strbmi	sp, [sl], -pc, lsr #6
d00156b0:	46204641 	strtmi	r4, [r0], -r1, asr #12
d00156b4:	f855f7fb 			; <UNDEFINED> instruction: 0xf855f7fb
d00156b8:	0a00f1b0 	beq	0xd0051d80
d00156bc:	464adb07 	strbmi	sp, [sl], -r7, lsl #22
d00156c0:	46204641 	strtmi	r4, [r0], -r1, asr #12
d00156c4:	ffc5f7fa 			; <UNDEFINED> instruction: 0xffc5f7fa
d00156c8:	f2c02800 	vmlal.s8	q9, d0, d0
d00156cc:	6da581d7 	stfvsd	f0, [r5, #860]!	; 0x35c
d00156d0:	f47f2d00 			; <UNDEFINED> instruction: 0xf47f2d00
d00156d4:	f8dfaf60 			; <UNDEFINED> instruction: 0xf8dfaf60
d00156d8:	447b3b9c 	ldrbtmi	r3, [fp], #-2972	; 0xfffff464
d00156dc:	3716e9c4 	ldrcc	lr, [r6, -r4, asr #19]
d00156e0:	66239b07 	strtvs	r9, [r3], -r7, lsl #22
d00156e4:	66639b08 	strbtvs	r9, [r3], -r8, lsl #22
d00156e8:	e3869b06 	orr	r9, r6, #6144	; 0x1800
d00156ec:	f0014620 			; <UNDEFINED> instruction: 0xf0014620
d00156f0:	2804fcbb 	stmdacs	r4, {r0, r1, r3, r4, r5, r7, sl, fp, ip, sp, lr, pc}
d00156f4:	f47f4605 			; <UNDEFINED> instruction: 0xf47f4605
d00156f8:	6ae3af6e 	bvs	0xcf9014b8
d00156fc:	f0402b5b 			; <UNDEFINED> instruction: 0xf0402b5b
d0015700:	2200828b 	andcs	r8, r0, #-1342177272	; 0xb0000008
d0015704:	46204631 			; <UNDEFINED> instruction: 0x46204631
d0015708:	fc2cf001 	stc2	0, cr15, [ip], #-4
d001570c:	465ae798 			; <UNDEFINED> instruction: 0x465ae798
d0015710:	46404649 	strbmi	r4, [r0], -r9, asr #12
d0015714:	f84df7fb 			; <UNDEFINED> instruction: 0xf84df7fb
d0015718:	0334f10b 	teqeq	r4, #-1073741822	; 0xc0000002	; <UNPREDICTABLE>
d001571c:	f0402800 			; <UNDEFINED> instruction: 0xf0402800
d0015720:	350185fd 	strcc	r8, [r1, #-1533]	; 0xfffffa03
d0015724:	e7be469b 			; <UNDEFINED> instruction: 0xe7be469b
d0015728:	b12b9b06 			; <UNDEFINED> instruction: 0xb12b9b06
d001572c:	2a10ee18 	bcs	0xd0450f94
d0015730:	4620212c 	strtmi	r2, [r0], -ip, lsr #2
d0015734:	fac9f7fd 	blx	0xcf293730
d0015738:	9000f896 	mulls	r0, r6, r8
d001573c:	33fff109 	mvnscc	pc, #1073741826	; 0x40000002
d0015740:	f2002b0d 	vqdmulh.s<illegal width 8>	d2, d0, d13
d0015744:	e8df816c 	ldm	pc, {r2, r3, r5, r6, r8, pc}^	; <UNPREDICTABLE>
d0015748:	0061f013 	rsbeq	pc, r1, r3, lsl r0	; <UNPREDICTABLE>
d001574c:	016a000e 	cmneq	sl, lr
d0015750:	016a016a 	cmneq	sl, sl, ror #2
d0015754:	016a016a 	cmneq	sl, sl, ror #2
d0015758:	006d016a 	rsbeq	r0, sp, sl, ror #2
d001575c:	016a006d 	cmneq	sl, sp, rrx
d0015760:	00e9006d 	rsceq	r0, r9, sp, rrx
d0015764:	46200138 			; <UNDEFINED> instruction: 0x46200138
d0015768:	fe10f7fe 	mrc2	7, 0, pc, cr0, cr14, {7}
d001576c:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d0015770:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0015774:	9b06fce7 	blls	0xd01d4b18
d0015778:	33013601 	movwcc	r3, #5633	; 0x1601
d001577c:	9b079306 	blls	0xd01fa39c
d0015780:	42939a06 	addsmi	r9, r3, #24576	; 0x6000
d0015784:	6da3d902 			; <UNDEFINED> instruction: 0x6da3d902
d0015788:	d0cd2b00 	sbcle	r2, sp, r0, lsl #22
d001578c:	2ae8f8df 	bcs	0xcfa53b10
d0015790:	46202129 	strtmi	r2, [r0], -r9, lsr #2
d0015794:	f7fd447a 			; <UNDEFINED> instruction: 0xf7fd447a
d0015798:	b380fa98 	orrlt	pc, r0, #152, 20	; 0x98000
d001579c:	46209907 	strtmi	r9, [r0], -r7, lsl #18
d00157a0:	fe99f7fe 	mrc2	7, 4, pc, cr9, cr14, {7}
d00157a4:	0318f24d 	tsteq	r8, #-805306364	; 0xd0000004	; <UNPREDICTABLE>
d00157a8:	0620f10b 	strteq	pc, [r0], -fp, lsl #2
d00157ac:	0726f10b 	streq	pc, [r6, -fp, lsl #2]!
d00157b0:	58e24605 	stmiapl	r2!, {r0, r2, r9, sl, lr}^
d00157b4:	4620210c 	strtmi	r2, [r0], -ip, lsl #2
d00157b8:	fce2f7fe 	stc2l	7, cr15, [r2], #1016	; 0x3f8
d00157bc:	01dcf64f 	bicseq	pc, ip, pc, asr #12
d00157c0:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d00157c4:	f836fcbf 			; <UNDEFINED> instruction: 0xf836fcbf
d00157c8:	f4411b02 			; <UNDEFINED> instruction: 0xf4411b02
d00157cc:	f7fe4140 			; <UNDEFINED> instruction: 0xf7fe4140
d00157d0:	42b7fcb9 	adcsmi	pc, r7, #47360	; 0xb900
d00157d4:	f244d1f2 	vand	<illegal reg q14.5>, q10, q9
d00157d8:	f7fe71e0 			; <UNDEFINED> instruction: 0xf7fe71e0
d00157dc:	b125fcb3 	msrlt	CPSR_sc, r3	; <illegal shifter operand>
d00157e0:	4130f445 	teqmi	r0, r5, asr #8	; <UNPREDICTABLE>
d00157e4:	f7feb289 			; <UNDEFINED> instruction: 0xf7feb289
d00157e8:	f89bfcad 			; <UNDEFINED> instruction: 0xf89bfcad
d00157ec:	2b063027 	blcs	0xd01a1890
d00157f0:	813cf040 	teqhi	ip, r0, asr #32	; <UNPREDICTABLE>
d00157f4:	21c0f24b 	biccs	pc, r0, fp, asr #4
d00157f8:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d00157fc:	f89bfca3 			; <UNDEFINED> instruction: 0xf89bfca3
d0015800:	28070027 	stmdacs	r7, {r0, r1, r2, r5}
d0015804:	8138f040 	teqhi	r8, r0, asr #32	; <UNPREDICTABLE>
d0015808:	e6e42502 	strbt	r2, [r4], r2, lsl #10
d001580c:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0015810:	2800fcfd 	stmdacs	r0, {r0, r2, r3, r4, r5, r6, r7, sl, fp, ip, sp, lr, pc}
d0015814:	f8dfd1aa 			; <UNDEFINED> instruction: 0xf8dfd1aa
d0015818:	46201a64 	strtmi	r1, [r0], -r4, ror #20
d001581c:	f7fa4479 			; <UNDEFINED> instruction: 0xf7fa4479
d0015820:	e7a3fcc3 	str	pc, [r3, r3, asr #25]!
d0015824:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0015828:	2800fcf1 	stmdacs	r0, {r0, r4, r5, r6, r7, sl, fp, ip, sp, lr, pc}
d001582c:	2126d19e 			; <UNDEFINED> instruction: 0x2126d19e
d0015830:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0015834:	6b63fa3c 	blvs	0xd191412c
d0015838:	93086ae2 	movwls	r6, #35554	; 0x8ae2
d001583c:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d0015840:	8024f8d4 	ldrdhi	pc, [r4], -r4	; <UNPREDICTABLE>
d0015844:	6aa7429a 	bvs	0xce9e62b4
d0015848:	a030f894 	mlasge	r0, r4, r8, pc	; <UNPREDICTABLE>
d001584c:	6da3d00d 	stcvs	0, cr13, [r3, #52]!	; 0x34
d0015850:	d18b2b00 	orrle	r2, fp, r0, lsl #22
d0015854:	3a28f8df 	bcc	0xd0a53bd8
d0015858:	65a3447b 	strvs	r4, [r3, #1147]!	; 0x47b
d001585c:	f8c49b08 			; <UNDEFINED> instruction: 0xf8c49b08
d0015860:	66a3805c 	ssatvs	r8, #4, ip, asr #0
d0015864:	7a18e9c4 	bvc	0xd064ff7c
d0015868:	e9d4e780 	ldmib	r4, {r7, r8, r9, sl, sp, lr, pc}^
d001586c:	46201206 	strtmi	r1, [r0], -r6, lsl #4
d0015870:	910a920b 	tstls	sl, fp, lsl #4
d0015874:	ff75f7fa 			; <UNDEFINED> instruction: 0xff75f7fa
d0015878:	dbe81e05 	blle	0xcfa1d094
d001587c:	46209a0b 	strtmi	r9, [r0], -fp, lsl #20
d0015880:	f7fa990a 			; <UNDEFINED> instruction: 0xf7fa990a
d0015884:	2800fee6 	stmdacs	r0, {r1, r2, r5, r6, r7, r9, sl, fp, ip, sp, lr, pc}
d0015888:	f1b9dae1 			; <UNDEFINED> instruction: 0xf1b9dae1
d001588c:	d01b0f09 	andsle	r0, fp, r9, lsl #30
d0015890:	0f0cf1b9 	svceq	0x000cf1b9
d0015894:	f8dfd122 			; <UNDEFINED> instruction: 0xf8dfd122
d0015898:	f04f99ec 			; <UNDEFINED> instruction: 0xf04f99ec
d001589c:	f8df0c02 			; <UNDEFINED> instruction: 0xf8df0c02
d00158a0:	44f919e8 	ldrbtmi	r1, [r9], #2536	; 0x9e8
d00158a4:	44794662 	ldrbtmi	r4, [r9], #-1634	; 0xfffff99e
d00158a8:	436b2334 	cmnmi	fp, #52, 6	; 0xd0000000
d00158ac:	f50018e0 			; <UNDEFINED> instruction: 0xf50018e0
d00158b0:	f89030e5 			; <UNDEFINED> instruction: 0xf89030e5
d00158b4:	45e6e103 	strbmi	lr, [r6, #259]!	; 0x103
d00158b8:	6da3d01a 	stcvs	0, cr13, [r3, #104]!	; 0x68
d00158bc:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d00158c0:	f8c4af55 			; <UNDEFINED> instruction: 0xf8c4af55
d00158c4:	e7c99058 			; <UNDEFINED> instruction: 0xe7c99058
d00158c8:	99c0f8df 	stmibls	r0, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d00158cc:	0c01f04f 	stceq	0, cr15, [r1], {79}	; 0x4f
d00158d0:	19bcf8df 	ldmibne	ip!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d00158d4:	44f92205 	ldrbtmi	r2, [r9], #517	; 0x205
d00158d8:	e7e54479 			; <UNDEFINED> instruction: 0xe7e54479
d00158dc:	99b4f8df 	ldmibls	r4!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d00158e0:	0c01f04f 	stceq	0, cr15, [r1], {79}	; 0x4f
d00158e4:	19b0f8df 	ldmibne	r0!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d00158e8:	466244f9 			; <UNDEFINED> instruction: 0x466244f9
d00158ec:	e7db4479 			; <UNDEFINED> instruction: 0xe7db4479
d00158f0:	0100f890 			; <UNDEFINED> instruction: 0x0100f890
d00158f4:	d1e04290 			; <UNDEFINED> instruction: 0xd1e04290
d00158f8:	30e5f503 	rsccc	pc, r5, r3, lsl #10
d00158fc:	7083f500 	addvc	pc, r3, r0, lsl #10
d0015900:	f0064420 			; <UNDEFINED> instruction: 0xf0064420
d0015904:	2800fdcb 	stmdacs	r0, {r0, r1, r3, r6, r7, r8, sl, fp, ip, sp, lr, pc}
d0015908:	4620d1d7 			; <UNDEFINED> instruction: 0x4620d1d7
d001590c:	f9b4f7fd 			; <UNDEFINED> instruction: 0xf9b4f7fd
d0015910:	2102462a 	tstcs	r2, sl, lsr #12
d0015914:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0015918:	e727fce5 	str	pc, [r7, -r5, ror #25]!
d001591c:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0015920:	2800fc75 	stmdacs	r0, {r0, r2, r4, r5, r6, sl, fp, ip, sp, lr, pc}
d0015924:	af22f47f 	svcge	0x0022f47f
d0015928:	2a90ee18 	bcs	0xce451190
d001592c:	46202126 	strtmi	r2, [r0], -r6, lsr #2
d0015930:	f9cbf7fd 			; <UNDEFINED> instruction: 0xf9cbf7fd
d0015934:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0015938:	6ae2af19 	bvs	0xcf8c15a4
d001593c:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d0015940:	a024f8d4 	ldrdge	pc, [r4], -r4	; <UNPREDICTABLE>
d0015944:	f8d4429a 			; <UNDEFINED> instruction: 0xf8d4429a
d0015948:	f8949028 			; <UNDEFINED> instruction: 0xf8949028
d001594c:	6b678030 	blvs	0xd19f5a14
d0015950:	6da3d00c 	stcvs	0, cr13, [r3, #48]!	; 0x30
d0015954:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0015958:	f8dfaf09 			; <UNDEFINED> instruction: 0xf8dfaf09
d001595c:	447b3940 	ldrbtmi	r3, [fp], #-2368	; 0xfffff6c0
d0015960:	e9c466a7 	stmib	r4, {r0, r1, r2, r5, r7, r9, sl, sp, lr}^
d0015964:	e9c43a16 	stmib	r4, {r1, r2, r4, r9, fp, ip, sp}^
d0015968:	e6ff9818 	usat	r9, #31, r8, lsl #16
d001596c:	1206e9d4 	andne	lr, r6, #212, 18	; 0x350000
d0015970:	920a4620 	andls	r4, sl, #32, 12	; 0x2000000
d0015974:	f7fa9108 			; <UNDEFINED> instruction: 0xf7fa9108
d0015978:	1e05fe8c 	cdpne	14, 0, cr15, cr5, cr12, {4}
d001597c:	9a0adbe9 	bls	0xd02cc928
d0015980:	99084620 	stmdbls	r8, {r5, r9, sl, lr}
d0015984:	fe65f7fa 	mcr2	7, 3, pc, cr5, cr10, {7}	; <UNPREDICTABLE>
d0015988:	dae22800 	ble	0xcf89f990
d001598c:	fb032334 	blx	0xd00de666
d0015990:	f5034305 			; <UNDEFINED> instruction: 0xf5034305
d0015994:	f89333af 			; <UNDEFINED> instruction: 0xf89333af
d0015998:	2b05302c 	blcs	0xd0161a50
d001599c:	4620d1d9 			; <UNDEFINED> instruction: 0x4620d1d9
d00159a0:	f96af7fd 			; <UNDEFINED> instruction: 0xf96af7fd
d00159a4:	462a2101 	strtmi	r2, [sl], -r1, lsl #2
d00159a8:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d00159ac:	f244fc9b 	vfma.f32	d31, d20, d11
d00159b0:	46206108 	strtmi	r6, [r0], -r8, lsl #2
d00159b4:	fbc6f7fe 	blx	0xcf1d39b6
d00159b8:	4620e6d8 			; <UNDEFINED> instruction: 0x4620e6d8
d00159bc:	fc26f7fe 	stc2	7, cr15, [r6], #-1016	; 0xfffffc08
d00159c0:	f47f2800 			; <UNDEFINED> instruction: 0xf47f2800
d00159c4:	6ae2aed3 	bvs	0xcf8c1518
d00159c8:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d00159cc:	a024f8d4 	ldrdge	pc, [r4], -r4	; <UNPREDICTABLE>
d00159d0:	f8d4429a 			; <UNDEFINED> instruction: 0xf8d4429a
d00159d4:	f8949028 			; <UNDEFINED> instruction: 0xf8949028
d00159d8:	6b678030 	blvs	0xd19f5aa0
d00159dc:	6da3d005 	stcvs	0, cr13, [r3, #20]!
d00159e0:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d00159e4:	9b09aec3 	blls	0xd02814f8
d00159e8:	e9d4e7ba 	ldmib	r4, {r1, r3, r4, r5, r7, r8, r9, sl, sp, lr, pc}^
d00159ec:	46201206 	strtmi	r1, [r0], -r6, lsl #4
d00159f0:	9108920a 	tstls	r8, sl, lsl #4
d00159f4:	fe4df7fa 	mcr2	7, 2, pc, cr13, cr10, {7}	; <UNPREDICTABLE>
d00159f8:	dbf01e05 	blle	0xcfc1d214
d00159fc:	46209a0a 	strtmi	r9, [r0], -sl, lsl #20
d0015a00:	f7fa9908 			; <UNDEFINED> instruction: 0xf7fa9908
d0015a04:	2800fe26 	stmdacs	r0, {r1, r2, r5, r9, sl, fp, ip, sp, lr, pc}
d0015a08:	2334dae9 	teqcs	r4, #954368	; 0xe9000
d0015a0c:	4305fb03 	movwmi	pc, #23299	; 0x5b03	; <UNPREDICTABLE>
d0015a10:	33aff503 			; <UNDEFINED> instruction: 0x33aff503
d0015a14:	302cf893 	mlacc	ip, r3, r8, pc	; <UNPREDICTABLE>
d0015a18:	d1e02b07 	mvnle	r2, r7, lsl #22
d0015a1c:	2201e7bf 	andcs	lr, r1, #50069504	; 0x2fc0000
d0015a20:	46114620 	ldrmi	r4, [r1], -r0, lsr #12
d0015a24:	fd2af000 	stc2	0, cr15, [sl, #-0]
d0015a28:	3b037833 	blcc	0xd00f3afc
d0015a2c:	f63f2b05 			; <UNDEFINED> instruction: 0xf63f2b05
d0015a30:	a202ae9d 	andge	sl, r2, #2512	; 0x9d0
d0015a34:	3023f852 	eorcc	pc, r3, r2, asr r8	; <UNPREDICTABLE>
d0015a38:	4710441a 			; <UNDEFINED> instruction: 0x4710441a
d0015a3c:	00000019 	andeq	r0, r0, r9, lsl r0
d0015a40:	0000001f 	andeq	r0, r0, pc, lsl r0
d0015a44:	fffffd31 			; <UNDEFINED> instruction: 0xfffffd31
d0015a48:	0000002b 	andeq	r0, r0, fp, lsr #32
d0015a4c:	fffffd31 			; <UNDEFINED> instruction: 0xfffffd31
d0015a50:	00000025 	andeq	r0, r0, r5, lsr #32
d0015a54:	4132f44f 	teqmi	r2, pc, asr #8	; <UNPREDICTABLE>
d0015a58:	f24be7ab 	vabd.s8	d30, d27, d27
d0015a5c:	e7a82180 	str	r2, [r8, r0, lsl #3]!
d0015a60:	2140f24b 	cmpcs	r0, fp, asr #4	; <UNPREDICTABLE>
d0015a64:	f24be7a5 	vabd.s8	d30, d27, d21
d0015a68:	e7a221c0 	str	r2, [r2, r0, asr #3]!
d0015a6c:	f47f2b08 			; <UNDEFINED> instruction: 0xf47f2b08
d0015a70:	f24baec6 	vceq.f32	q13, <illegal reg q13.5>, q3
d0015a74:	e6bf2140 	ldrt	r2, [pc], r0, asr #2
d0015a78:	e5a92805 	str	r2, [r9, #2053]!	; 0x805
d0015a7c:	4641464a 	strbmi	r4, [r1], -sl, asr #12
d0015a80:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0015a84:	2800fe06 	stmdacs	r0, {r1, r2, r9, sl, fp, ip, sp, lr, pc}
d0015a88:	ae21f6bf 	mcrge	6, 1, pc, cr1, cr15, {5}	; <UNPREDICTABLE>
d0015a8c:	fb052534 	blx	0xd015ef66
d0015a90:	1963f50a 	stmdbne	r3!, {r1, r3, r8, sl, ip, sp, lr, pc}^
d0015a94:	32e5f503 	rsccc	pc, r5, #12582912	; 0xc00000
d0015a98:	1107f892 			; <UNDEFINED> instruction: 0x1107f892
d0015a9c:	d1072904 	tstle	r7, r4, lsl #18
d0015aa0:	2d006da5 	stccs	13, cr6, [r0, #-660]	; 0xfffffd6c
d0015aa4:	ad77f47f 	cfldrdge	mvd15, [r7, #-508]!	; 0xfffffe04
d0015aa8:	37f4f8df 	ubfxcc	pc, pc, #17, #21
d0015aac:	e615447b 			; <UNDEFINED> instruction: 0xe615447b
d0015ab0:	1301f103 	movwne	pc, #4355	; 0x1103	; <UNPREDICTABLE>
d0015ab4:	434bf503 	movtmi	pc, #46339	; 0xb503	; <UNPREDICTABLE>
d0015ab8:	2b04781b 	blcs	0xd0133b2c
d0015abc:	f505d016 			; <UNDEFINED> instruction: 0xf505d016
d0015ac0:	f8df35e5 			; <UNDEFINED> instruction: 0xf8df35e5
d0015ac4:	f04f97e0 			; <UNDEFINED> instruction: 0xf04f97e0
d0015ac8:	92090800 	andls	r0, r9, #0, 16
d0015acc:	7583f505 	strvc	pc, [r3, #1285]	; 0x505
d0015ad0:	442544f9 	strtmi	r4, [r5], #-1273	; 0xfffffb07
d0015ad4:	f8939b09 			; <UNDEFINED> instruction: 0xf8939b09
d0015ad8:	45881100 	strmi	r1, [r8, #256]	; 0x100
d0015adc:	6da3d201 	sfmvs	f5, 1, [r3, #4]!
d0015ae0:	4620b313 			; <UNDEFINED> instruction: 0x4620b313
d0015ae4:	fcf7f7fe 	ldc2l	7, cr15, [r7], #1016	; 0x3f8
d0015ae8:	e0044680 	and	r4, r4, r0, lsl #13
d0015aec:	0800f04f 	stmdaeq	r0, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d0015af0:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0015af4:	f8dffc4b 			; <UNDEFINED> instruction: 0xf8dffc4b
d0015af8:	212927b0 			; <UNDEFINED> instruction: 0x212927b0
d0015afc:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d0015b00:	f8e3f7fd 			; <UNDEFINED> instruction: 0xf8e3f7fd
d0015b04:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0015b08:	f504ad46 			; <UNDEFINED> instruction: 0xf504ad46
d0015b0c:	f8d3330f 			; <UNDEFINED> instruction: 0xf8d3330f
d0015b10:	f5b552e0 			; <UNDEFINED> instruction: 0xf5b552e0
d0015b14:	d15a6f00 	cmple	sl, r0, lsl #30
d0015b18:	2d006da5 	stccs	13, cr6, [r0, #-660]	; 0xfffffd6c
d0015b1c:	ad3bf47f 	cfldrsge	mvf15, [fp, #-508]!	; 0xfffffe04
d0015b20:	3788f8df 			; <UNDEFINED> instruction: 0x3788f8df
d0015b24:	e5d9447b 	ldrb	r4, [r9, #1147]	; 0x47b
d0015b28:	0f00f1b8 	svceq	0x0000f1b8
d0015b2c:	464ad004 	strbmi	sp, [sl], -r4
d0015b30:	4620212c 	strtmi	r2, [r0], -ip, lsr #2
d0015b34:	f8c9f7fd 			; <UNDEFINED> instruction: 0xf8c9f7fd
d0015b38:	bb01f815 	bllt	0xd0093b94
d0015b3c:	0f0ef1bb 	svceq	0x000ef1bb
d0015b40:	7929d10b 	stmdbvc	r9!, {r0, r1, r3, r8, ip, lr, pc}
d0015b44:	f0014620 			; <UNDEFINED> instruction: 0xf0014620
d0015b48:	f24bf8c3 	vadd.i8	<illegal reg q15.5>, <illegal reg q13.5>, <illegal reg q1.5>
d0015b4c:	46204103 	strtmi	r4, [r0], -r3, lsl #2
d0015b50:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d0015b54:	faf6f7fe 	blx	0xcfdd3b54
d0015b58:	f1bbe7bc 			; <UNDEFINED> instruction: 0xf1bbe7bc
d0015b5c:	d1050f0a 	tstle	r5, sl, lsl #30
d0015b60:	21012204 	tstcs	r1, r4, lsl #4
d0015b64:	f0004620 			; <UNDEFINED> instruction: 0xf0004620
d0015b68:	e7eefc89 	strb	pc, [lr, r9, lsl #25]!	; <UNPREDICTABLE>
d0015b6c:	02fbf00b 	rscseq	pc, fp, #11
d0015b70:	d1292a02 			; <UNDEFINED> instruction: 0xd1292a02
d0015b74:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0015b78:	2800fb49 	stmdacs	r0, {r0, r3, r6, r8, r9, fp, ip, sp, lr, pc}
d0015b7c:	6ae1d1e5 	bvs	0xcf88a318
d0015b80:	1201f240 	andne	pc, r1, #64, 4
d0015b84:	d0064291 	mulle	r6, r1, r2
d0015b88:	1724f8df 			; <UNDEFINED> instruction: 0x1724f8df
d0015b8c:	44794620 	ldrbtmi	r4, [r9], #-1568	; 0xfffff9e0
d0015b90:	fb0af7fa 	blx	0xd02d3b82
d0015b94:	69a1e638 	stmibvs	r1!, {r3, r4, r5, r9, sl, sp, lr, pc}
d0015b98:	69e24620 	stmibvs	r2!, {r5, r9, sl, lr}^
d0015b9c:	fd59f7fa 	ldc2l	7, cr15, [r9, #-1000]	; 0xfffffc18
d0015ba0:	dbf11e01 	blle	0xcfc5d3ac
d0015ba4:	910a232c 	tstls	sl, ip, lsr #6
d0015ba8:	4201fb03 	andmi	pc, r1, #3072	; 0xc00
d0015bac:	3213f502 	andscc	pc, r3, #8388608	; 0x800000
d0015bb0:	230df892 	movwcs	pc, #55442	; 0xd892	; <UNPREDICTABLE>
d0015bb4:	d1e7455a 	mvnle	r4, sl, asr r5
d0015bb8:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0015bbc:	990af85d 	stmdbls	sl, {r0, r2, r3, r4, r6, fp, ip, sp, lr, pc}
d0015bc0:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0015bc4:	e7c0fe39 			; <UNDEFINED> instruction: 0xe7c0fe39
d0015bc8:	46112201 	ldrmi	r2, [r1], -r1, lsl #4
d0015bcc:	1c6ae7ca 	stclne	7, cr14, [sl], #-808	; 0xfffffcd8
d0015bd0:	05c5eb04 	strbeq	lr, [r5, #2820]	; 0xb04
d0015bd4:	f5054620 			; <UNDEFINED> instruction: 0xf5054620
d0015bd8:	f8c335ff 			; <UNDEFINED> instruction: 0xf8c335ff
d0015bdc:	f7fe22e0 			; <UNDEFINED> instruction: 0xf7fe22e0
d0015be0:	f8a5fc45 			; <UNDEFINED> instruction: 0xf8a5fc45
d0015be4:	f8c5a0e4 			; <UNDEFINED> instruction: 0xf8c5a0e4
d0015be8:	f1b800e0 			; <UNDEFINED> instruction: 0xf1b800e0
d0015bec:	d0050f00 	andle	r0, r5, r0, lsl #30
d0015bf0:	4130f448 	teqmi	r0, r8, asr #8	; <UNPREDICTABLE>
d0015bf4:	b2894620 	addlt	r4, r9, #32, 12	; 0x2000000
d0015bf8:	faa4f7fe 	blx	0xce953bf8
d0015bfc:	fb002034 	blx	0xd001dcd6
d0015c00:	f50a4a0a 			; <UNDEFINED> instruction: 0xf50a4a0a
d0015c04:	f89a3ae5 			; <UNDEFINED> instruction: 0xf89a3ae5
d0015c08:	2b013103 	blcs	0xd006201c
d0015c0c:	adfcf43f 	cfldrdge	mvd15, [ip, #252]!	; 0xfc
d0015c10:	f47f2b03 			; <UNDEFINED> instruction: 0xf47f2b03
d0015c14:	e570acc0 	ldrb	sl, [r0, #-3264]!	; 0xfffff340
d0015c18:	e4dc2504 	ldrb	r2, [ip], #1284	; 0x504
d0015c1c:	a02cf8d4 	ldrdge	pc, [ip], -r4	; <UNPREDICTABLE>
d0015c20:	7391f5aa 	orrsvc	pc, r1, #713031680	; 0x2a800000
d0015c24:	d8102b01 	ldmdale	r0, {r0, r8, r9, fp, sp}
d0015c28:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0015c2c:	2301f825 	movwcs	pc, #6181	; 0x1825	; <UNPREDICTABLE>
d0015c30:	4641464a 	strbmi	r4, [r1], -sl, asr #12
d0015c34:	9b069304 	blls	0xd01ba84c
d0015c38:	a00cf8cd 	andge	pc, ip, sp, asr #17
d0015c3c:	9b089302 	blls	0xd023a84c
d0015c40:	9b079301 	blls	0xd01fa84c
d0015c44:	463b9300 	ldrtmi	r9, [fp], -r0, lsl #6
d0015c48:	464ae4f7 			; <UNDEFINED> instruction: 0x464ae4f7
d0015c4c:	46204641 	strtmi	r4, [r0], -r1, asr #12
d0015c50:	fcfff7fa 	ldc2l	7, cr15, [pc], #1000	; 0xd0016040
d0015c54:	4683464a 	strmi	r4, [r3], sl, asr #12
d0015c58:	46204641 	strtmi	r4, [r0], -r1, asr #12
d0015c5c:	fdbef7fa 	ldc2	7, cr15, [lr, #1000]!	; 0x3e8
d0015c60:	b1204682 	smlawblt	r0, r2, r6, r4
d0015c64:	46206a01 	strtmi	r6, [r0], -r1, lsl #20
d0015c68:	fac8f7fe 	blx	0xcf253c68
d0015c6c:	f1bbe4b3 			; <UNDEFINED> instruction: 0xf1bbe4b3
d0015c70:	f2c00f00 			; <UNDEFINED> instruction: 0xf2c00f00
d0015c74:	f04f80cd 			; <UNDEFINED> instruction: 0xf04f80cd
d0015c78:	fb08082c 	blx	0xd0217d32
d0015c7c:	f508480b 			; <UNDEFINED> instruction: 0xf508480b
d0015c80:	f8983813 			; <UNDEFINED> instruction: 0xf8983813
d0015c84:	f1b9930d 			; <UNDEFINED> instruction: 0xf1b9930d
d0015c88:	d0020f02 	andle	r0, r2, r2, lsl #30
d0015c8c:	0f04f1b9 	svceq	0x0004f1b9
d0015c90:	6da3d107 	stfvsd	f5, [r3, #28]!
d0015c94:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0015c98:	f8dfac7e 			; <UNDEFINED> instruction: 0xf8dfac7e
d0015c9c:	447b3618 	ldrbtmi	r3, [fp], #-1560	; 0xfffff9e8
d0015ca0:	f1b9e51c 			; <UNDEFINED> instruction: 0xf1b9e51c
d0015ca4:	d1050f0c 	tstle	r5, ip, lsl #30
d0015ca8:	46204659 			; <UNDEFINED> instruction: 0x46204659
d0015cac:	fdc4f7fe 	stc2l	7, cr15, [r4, #1016]	; 0x3f8
d0015cb0:	e4902503 	ldr	r2, [r0], #1283	; 0x503
d0015cb4:	030df1a9 	movweq	pc, #53673	; 0xd1a9	; <UNPREDICTABLE>
d0015cb8:	46204659 			; <UNDEFINED> instruction: 0x46204659
d0015cbc:	d82d2b01 	stmdale	sp!, {r0, r8, r9, fp, sp}
d0015cc0:	0f0df1b9 	svceq	0x000df1b9
d0015cc4:	f7fed117 			; <UNDEFINED> instruction: 0xf7fed117
d0015cc8:	212efaec 	msrcs	LR_fiq, ip
d0015ccc:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0015cd0:	4605ffee 	strmi	pc, [r5], -lr, ror #31
d0015cd4:	4653b138 			; <UNDEFINED> instruction: 0x4653b138
d0015cd8:	f8984632 			; <UNDEFINED> instruction: 0xf8984632
d0015cdc:	4620130e 	strtmi	r1, [r0], -lr, lsl #6
d0015ce0:	fe24f000 	cdp2	0, 2, cr15, cr4, cr0, {0}
d0015ce4:	6da3e4ac 	cfstrsvs	mvf14, [r3, #688]!	; 0x2b0
d0015ce8:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0015cec:	f8dfac54 			; <UNDEFINED> instruction: 0xf8dfac54
d0015cf0:	447b35c8 	ldrbtmi	r3, [fp], #-1480	; 0xfffffa38
d0015cf4:	f7fee4f2 			; <UNDEFINED> instruction: 0xf7fee4f2
d0015cf8:	f240fd9f 	vmla.f32	d31, d16, d15
d0015cfc:	f7fc1121 			; <UNDEFINED> instruction: 0xf7fc1121
d0015d00:	4603ffd6 			; <UNDEFINED> instruction: 0x4603ffd6
d0015d04:	d1e62800 	mvnle	r2, r0, lsl #16
d0015d08:	2a5b6ae2 	bcs	0xd16f0898
d0015d0c:	4632d1d0 			; <UNDEFINED> instruction: 0x4632d1d0
d0015d10:	130ef898 	movwne	pc, #59544	; 0xe898	; <UNPREDICTABLE>
d0015d14:	f0004620 			; <UNDEFINED> instruction: 0xf0004620
d0015d18:	e491ff2f 	ldr	pc, [r1], #3887	; 0xf2f
d0015d1c:	0f10f1b9 	svceq	0x0010f1b9
d0015d20:	f7fed10e 			; <UNDEFINED> instruction: 0xf7fed10e
d0015d24:	6ae3fabe 	bvs	0xcf914824
d0015d28:	d1012b5b 	tstle	r1, fp, asr fp
d0015d2c:	e7ee4653 	ubfx	r4, r3, #12, #15
d0015d30:	2b006da3 	blcs	0xd00313c4
d0015d34:	ac2ff47f 	cfstrsge	mvf15, [pc], #-508	; 0xd0015b40
d0015d38:	3580f8df 	strcc	pc, [r0, #2271]	; 0x8df
d0015d3c:	e4cd447b 	strb	r4, [sp], #1147	; 0x47b
d0015d40:	0f09f1b9 	svceq	0x0009f1b9
d0015d44:	f7fed102 			; <UNDEFINED> instruction: 0xf7fed102
d0015d48:	e4d6faac 	ldrb	pc, [r6], #2732	; 0xaac	; <UNPREDICTABLE>
d0015d4c:	fd74f7fe 	ldc2l	7, cr15, [r4, #-1016]!	; 0xfffffc08
d0015d50:	0f06f1b9 	svceq	0x0006f1b9
d0015d54:	f240d154 	vand	<illegal reg q14.5>, q0, q2
d0015d58:	f7fc1121 			; <UNDEFINED> instruction: 0xf7fc1121
d0015d5c:	2800ffa8 	stmdacs	r0, {r3, r5, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0015d60:	6aa3d0a6 	bvs	0xce90a000
d0015d64:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d0015d68:	2554f8df 	ldrbcs	pc, [r4, #-2271]	; 0xfffff721	; <UNPREDICTABLE>
d0015d6c:	93064620 	movwls	r4, #26144	; 0x6620
d0015d70:	447a6b63 	ldrbtmi	r6, [sl], #-2915	; 0xfffff49d
d0015d74:	9024f8d4 	ldrdls	pc, [r4], -r4	; <UNPREDICTABLE>
d0015d78:	7030f894 	mlasvc	r0, r4, r8, pc	; <UNPREDICTABLE>
d0015d7c:	e9d49307 	ldmib	r4, {r0, r1, r2, r8, r9, ip, pc}^
d0015d80:	f7fcab06 			; <UNDEFINED> instruction: 0xf7fcab06
d0015d84:	2800ffa2 	stmdacs	r0, {r1, r5, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d0015d88:	ac05f43f 	cfstrsge	mvf15, [r5], {63}	; 0x3f
d0015d8c:	8534f8df 	ldrhi	pc, [r4, #-2271]!	; 0xfffff721
d0015d90:	44f82600 	ldrbtmi	r2, [r8], #1536	; 0x600
d0015d94:	2b04f858 	blcs	0xd0153efc
d0015d98:	46504659 			; <UNDEFINED> instruction: 0x46504659
d0015d9c:	fd09f7fa 	stc2	7, cr15, [r9, #-1000]	; 0xfffffc18
d0015da0:	b1d04605 	bicslt	r4, r0, r5, lsl #12
d0015da4:	03d0f64f 	bicseq	pc, r0, #82837504	; 0x4f00000
d0015da8:	0190f64f 	orrseq	pc, r0, pc, asr #12
d0015dac:	2e014620 	cfmadd32cs	mvax1, mvfx4, mvfx1, mvfx0
d0015db0:	4619bf18 	sadd16mi	fp, r9, r8
d0015db4:	f9c6f7fe 			; <UNDEFINED> instruction: 0xf9c6f7fe
d0015db8:	43ddf506 	bicsmi	pc, sp, #25165824	; 0x1800000
d0015dbc:	eb043370 	bl	0xd0122b84
d0015dc0:	88990343 	ldmhi	r9, {r0, r1, r6, r8, r9}
d0015dc4:	f9bef7fe 			; <UNDEFINED> instruction: 0xf9bef7fe
d0015dc8:	f43f2e00 			; <UNDEFINED> instruction: 0xf43f2e00
d0015dcc:	3e02abf2 	vmovcc.16	d18[1], sl
d0015dd0:	f63f2e01 			; <UNDEFINED> instruction: 0xf63f2e01
d0015dd4:	f7ffabe0 			; <UNDEFINED> instruction: 0xf7ffabe0
d0015dd8:	3601bbec 	strcc	fp, [r1], -ip, ror #23
d0015ddc:	d1d92e08 	bicsle	r2, r9, r8, lsl #28
d0015de0:	2b006da3 	blcs	0xd0031474
d0015de4:	abd7f47f 	blge	0xcf612fe8
d0015de8:	34dcf8df 	ldrbcc	pc, [ip], #2271	; 0x8df	; <UNPREDICTABLE>
d0015dec:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0015df0:	9b063916 	blls	0xd01a4250
d0015df4:	3718e9c4 	ldrcc	lr, [r8, -r4, asr #19]
d0015df8:	66a39b07 	strtvs	r9, [r3], r7, lsl #22
d0015dfc:	bbebf7ff 	bllt	0xcfb13e00
d0015e00:	0f0af1b9 	svceq	0x000af1b9
d0015e04:	ac79f43f 	cfldrdge	mvd15, [r9], #-252	; 0xffffff04
d0015e08:	0f01f1b9 	svceq	0x0001f1b9
d0015e0c:	bbe0f7ff 	bllt	0xcf853e10
d0015e10:	4641464a 	strbmi	r4, [r1], -sl, asr #12
d0015e14:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0015e18:	f1b0fc3c 			; <UNDEFINED> instruction: 0xf1b0fc3c
d0015e1c:	f2c00b00 	vqdmlsl.s<illegal width 8>	q8, d0, d0
d0015e20:	f04f809d 			; <UNDEFINED> instruction: 0xf04f809d
d0015e24:	fb080834 	blx	0xd0217efe
d0015e28:	f508480b 			; <UNDEFINED> instruction: 0xf508480b
d0015e2c:	f89838af 			; <UNDEFINED> instruction: 0xf89838af
d0015e30:	f1b9902c 			; <UNDEFINED> instruction: 0xf1b9902c
d0015e34:	d1430f07 	cmple	r3, r7, lsl #30
d0015e38:	2490f8df 	ldrcs	pc, [r0], #2271	; 0x8df
d0015e3c:	4620215b 			; <UNDEFINED> instruction: 0x4620215b
d0015e40:	f7fc447a 			; <UNDEFINED> instruction: 0xf7fc447a
d0015e44:	2800ff42 	stmdacs	r0, {r1, r6, r8, r9, sl, fp, ip, sp, lr, pc}
d0015e48:	aba5f43f 	blge	0xce992f4c
d0015e4c:	46202201 	strtmi	r2, [r0], -r1, lsl #4
d0015e50:	f0004611 			; <UNDEFINED> instruction: 0xf0004611
d0015e54:	f8dffb13 			; <UNDEFINED> instruction: 0xf8dffb13
d0015e58:	215d2478 	cmpcs	sp, r8, ror r4
d0015e5c:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d0015e60:	ff33f7fc 			; <UNDEFINED> instruction: 0xff33f7fc
d0015e64:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0015e68:	465aab96 			; <UNDEFINED> instruction: 0x465aab96
d0015e6c:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d0015e70:	fa38f7fe 	blx	0xd0e53e70
d0015e74:	f645b936 			; <UNDEFINED> instruction: 0xf645b936
d0015e78:	46204108 	strtmi	r4, [r0], -r8, lsl #2
d0015e7c:	f962f7fe 			; <UNDEFINED> instruction: 0xf962f7fe
d0015e80:	bba9f7ff 	bllt	0xcea93e84
d0015e84:	4620213d 			; <UNDEFINED> instruction: 0x4620213d
d0015e88:	ff11f7fc 			; <UNDEFINED> instruction: 0xff11f7fc
d0015e8c:	d0f22800 	rscsle	r2, r2, r0, lsl #16
d0015e90:	f6414620 			; <UNDEFINED> instruction: 0xf6414620
d0015e94:	f7fe0108 			; <UNDEFINED> instruction: 0xf7fe0108
d0015e98:	f24bf955 	vmul.i8	<illegal reg q15.5>, <illegal reg q5.5>, <illegal reg q2.5>
d0015e9c:	f7fe4103 			; <UNDEFINED> instruction: 0xf7fe4103
d0015ea0:	2201f951 	andcs	pc, r1, #1327104	; 0x144000
d0015ea4:	f0004611 			; <UNDEFINED> instruction: 0xf0004611
d0015ea8:	f64bfae9 			; <UNDEFINED> instruction: 0xf64bfae9
d0015eac:	46204106 	strtmi	r4, [r0], -r6, lsl #2
d0015eb0:	f948f7fe 			; <UNDEFINED> instruction: 0xf948f7fe
d0015eb4:	0108f247 	tsteq	r8, r7, asr #4	; <UNPREDICTABLE>
d0015eb8:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0015ebc:	e4a3f943 	strt	pc, [r3], #2371	; 0x943
d0015ec0:	0f0ff1b9 	svceq	0x000ff1b9
d0015ec4:	f04f465a 			; <UNDEFINED> instruction: 0xf04f465a
d0015ec8:	46200101 	strtmi	r0, [r0], -r1, lsl #2
d0015ecc:	f7fed118 			; <UNDEFINED> instruction: 0xf7fed118
d0015ed0:	f244fa09 	vpmax.s8	d31, d4, d9
d0015ed4:	46206108 	strtmi	r6, [r0], -r8, lsl #2
d0015ed8:	f934f7fe 			; <UNDEFINED> instruction: 0xf934f7fe
d0015edc:	f7fc212e 			; <UNDEFINED> instruction: 0xf7fc212e
d0015ee0:	4605fee6 	strmi	pc, [r5], -r6, ror #29
d0015ee4:	4653b120 	ldrbmi	fp, [r3], -r0, lsr #2
d0015ee8:	f8984632 			; <UNDEFINED> instruction: 0xf8984632
d0015eec:	e6f6102e 	ldrbt	r1, [r6], lr, lsr #32
d0015ef0:	2b006da3 	blcs	0xd0031584
d0015ef4:	ab4ff47f 	blge	0xd14130f8
d0015ef8:	447b4bf6 	ldrbtmi	r4, [fp], #-3062	; 0xfffff40a
d0015efc:	bbeef7ff 	bllt	0xcfbd3f00
d0015f00:	0f11f1b9 	svceq	0x0011f1b9
d0015f04:	f7fed116 			; <UNDEFINED> instruction: 0xf7fed116
d0015f08:	f244f9ed 	vmla.i8	<illegal reg q15.5>, q10, <illegal reg q14.5>
d0015f0c:	46206108 	strtmi	r6, [r0], -r8, lsl #2
d0015f10:	f918f7fe 			; <UNDEFINED> instruction: 0xf918f7fe
d0015f14:	2b5b6ae3 	blcs	0xd16f0aa8
d0015f18:	4653d104 	ldrbmi	sp, [r3], -r4, lsl #2
d0015f1c:	f8984632 			; <UNDEFINED> instruction: 0xf8984632
d0015f20:	e6f7102e 	ldrbt	r1, [r7], lr, lsr #32
d0015f24:	2b006da3 	blcs	0xd00315b8
d0015f28:	ab35f47f 	blge	0xd0d9312c
d0015f2c:	447b4bea 	ldrbtmi	r4, [fp], #-3050	; 0xfffff416
d0015f30:	bbd4f7ff 	bllt	0xcf553f34
d0015f34:	0f08f1b9 	svceq	0x0008f1b9
d0015f38:	f7fed108 			; <UNDEFINED> instruction: 0xf7fed108
d0015f3c:	f244f9d3 	vmul.i8	<illegal reg q15.5>, q10, <illegal reg q1.5>
d0015f40:	46206108 	strtmi	r6, [r0], -r8, lsl #2
d0015f44:	f8fef7fe 			; <UNDEFINED> instruction: 0xf8fef7fe
d0015f48:	bbd7f7ff 	bllt	0xcf613f4c
d0015f4c:	f9caf7fe 			; <UNDEFINED> instruction: 0xf9caf7fe
d0015f50:	0108f646 	tsteq	r8, r6, asr #12	; <UNPREDICTABLE>
d0015f54:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0015f58:	e755f8f5 	smmlsr	r5, r5, r8, pc	; <UNPREDICTABLE>
d0015f5c:	46494adf 			; <UNDEFINED> instruction: 0x46494adf
d0015f60:	447a4640 	ldrbtmi	r4, [sl], #-1600	; 0xfffff9c0
d0015f64:	fc25f7fa 	stc2	7, cr15, [r5], #-1000	; 0xfffffc18
d0015f68:	b1204605 			; <UNDEFINED> instruction: 0xb1204605
d0015f6c:	46204651 			; <UNDEFINED> instruction: 0x46204651
d0015f70:	f944f7fe 			; <UNDEFINED> instruction: 0xf944f7fe
d0015f74:	6da3e69c 	stcvs	6, cr14, [r3, #624]!	; 0x270
d0015f78:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0015f7c:	4bd8ab0c 	blmi	0xcf640bb4
d0015f80:	f7ff447b 			; <UNDEFINED> instruction: 0xf7ff447b
d0015f84:	2126bbab 			; <UNDEFINED> instruction: 0x2126bbab
d0015f88:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0015f8c:	2800fe90 	stmdacs	r0, {r4, r7, r9, sl, fp, ip, sp, lr, pc}
d0015f90:	809af000 	addshi	pc, sl, r0
d0015f94:	f2404ad3 	vpmin.s8	q10, q8, <illegal reg q1.5>
d0015f98:	46201101 	strtmi	r1, [r0], -r1, lsl #2
d0015f9c:	447a6a66 	ldrbtmi	r6, [sl], #-2662	; 0xfffff59a
d0015fa0:	f8946aa7 			; <UNDEFINED> instruction: 0xf8946aa7
d0015fa4:	f8d48030 			; <UNDEFINED> instruction: 0xf8d48030
d0015fa8:	e9d49034 	ldmib	r4, {r2, r4, r5, ip, pc}^
d0015fac:	9306a306 	movwls	sl, #25350	; 0x6306
d0015fb0:	fe8bf7fc 	mcr2	7, 4, pc, cr11, cr12, {7}	; <UNPREDICTABLE>
d0015fb4:	b9489b06 	stmdblt	r8, {r1, r2, r8, r9, fp, ip, pc}^
d0015fb8:	31f8f8db 	ldrsbcc	pc, [r8, #139]!	; 0x8b	; <UNPREDICTABLE>
d0015fbc:	f8cb3b01 			; <UNDEFINED> instruction: 0xf8cb3b01
d0015fc0:	b00d31f8 	strdlt	r3, [sp], -r8
d0015fc4:	8b02ecbd 	blhi	0xd00d12c0
d0015fc8:	8ff0e8bd 	svchi	0x00f0e8bd
d0015fcc:	4651461a 			; <UNDEFINED> instruction: 0x4651461a
d0015fd0:	93064620 	movwls	r4, #26144	; 0x6620
d0015fd4:	fb3df7fa 	blx	0xd0f93fc6
d0015fd8:	0b00f1b0 	bleq	0xd00526a0
d0015fdc:	f2809b06 	vqdmlsl.s<illegal width 8>	<illegal reg q4.5>, d0, d6
d0015fe0:	461a81b1 			; <UNDEFINED> instruction: 0x461a81b1
d0015fe4:	46204651 			; <UNDEFINED> instruction: 0x46204651
d0015fe8:	fb53f7fa 	blx	0xd1513fda
d0015fec:	da1d1e02 	ble	0xd075d7fc
d0015ff0:	2b006da3 	blcs	0xd0031684
d0015ff4:	aacff47f 	bge	0xcf4131f8
d0015ff8:	447b4bbb 	ldrbtmi	r4, [fp], #-3003	; 0xfffff445
d0015ffc:	bbb3e052 	bllt	0xced0e14c
d0016000:	46204659 			; <UNDEFINED> instruction: 0x46204659
d0016004:	f94df7fe 			; <UNDEFINED> instruction: 0xf94df7fe
d0016008:	2b5b6ae3 	blcs	0xd16f0b9c
d001600c:	032cf04f 	msreq	CPSR_fs, #79	; 0x4f
d0016010:	430bfb03 	movwmi	pc, #47875	; 0xbb03	; <UNPREDICTABLE>
d0016014:	3313f503 	tstcc	r3, #12582912	; 0xc00000	; <UNPREDICTABLE>
d0016018:	330df893 	movwcc	pc, #55443	; 0xd893	; <UNPREDICTABLE>
d001601c:	2b09d139 	blcs	0xd028a508
d0016020:	adfaf47f 	cfldrdge	mvd15, [sl, #508]!	; 0x1fc
d0016024:	21002201 	tstcs	r0, r1, lsl #4
d0016028:	bb6df7ff 	bllt	0xd1b9402c
d001602c:	0a34f04f 	beq	0xd0d52170
d0016030:	4a02fb0a 	bmi	0xd00d4c60
d0016034:	3aaff50a 	bcc	0xcec13464
d0016038:	102cf89a 	mlane	ip, sl, r8, pc	; <UNPREDICTABLE>
d001603c:	f040290f 			; <UNDEFINED> instruction: 0xf040290f
d0016040:	2101819e 			; <UNDEFINED> instruction: 0x2101819e
d0016044:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0016048:	f244f94d 	vmla.i8	<illegal reg q15.5>, q2, <illegal reg q6.5>
d001604c:	46206108 	strtmi	r6, [r0], -r8, lsl #2
d0016050:	f878f7fe 			; <UNDEFINED> instruction: 0xf878f7fe
d0016054:	212e4aa5 			; <UNDEFINED> instruction: 0x212e4aa5
d0016058:	f7fc447a 			; <UNDEFINED> instruction: 0xf7fc447a
d001605c:	2800fe36 	stmdacs	r0, {r1, r2, r4, r5, r9, sl, fp, ip, sp, lr, pc}
d0016060:	aa99f43f 	bge	0xce693164
d0016064:	22002301 	andcs	r2, r0, #67108864	; 0x4000000
d0016068:	102ef89a 	mlane	lr, sl, r8, pc	; <UNPREDICTABLE>
d001606c:	2b09e637 	blcs	0xd028f950
d0016070:	2b0ad0c6 	blcs	0xd02ca390
d0016074:	4659d1bc 			; <UNDEFINED> instruction: 0x4659d1bc
d0016078:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d001607c:	6ae3fbdd 	bvs	0xcf914ff8
d0016080:	d0cf2b5b 	sbcle	r2, pc, fp, asr fp	; <UNPREDICTABLE>
d0016084:	2b006da3 	blcs	0xd0031718
d0016088:	aa85f47f 	bge	0xce19328c
d001608c:	447b4b98 	ldrbtmi	r4, [fp], #-2968	; 0xfffff468
d0016090:	2b09e008 	blcs	0xd028e0b8
d0016094:	adc0f47f 	cfstrdge	mvd15, [r0, #508]	; 0x1fc
d0016098:	2b006da3 	blcs	0xd003172c
d001609c:	aa7bf47f 	bge	0xd1f132a0
d00160a0:	447b4b94 	ldrbtmi	r4, [fp], #-2964	; 0xfffff46c
d00160a4:	9068f8c4 	rsbls	pc, r8, r4, asr #17
d00160a8:	3616e9c4 	ldrcc	lr, [r6], -r4, asr #19
d00160ac:	7818e9c4 	ldmdavc	r8, {r2, r6, r7, r8, fp, sp, lr, pc}
d00160b0:	ba91f7ff 	blt	0xce4940b4
d00160b4:	f47f2b08 			; <UNDEFINED> instruction: 0xf47f2b08
d00160b8:	6da3adaf 	stcvs	13, cr10, [r3, #700]!	; 0x2bc
d00160bc:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d00160c0:	4b8daa6a 	blmi	0xce380a70
d00160c4:	e7ed447b 			; <UNDEFINED> instruction: 0xe7ed447b
d00160c8:	4620212a 	strtmi	r2, [r0], -sl, lsr #2
d00160cc:	fdeff7fc 	stc2l	7, cr15, [pc, #1008]!	; 0xd00164c4
d00160d0:	2100b360 	tstcs	r0, r0, ror #6
d00160d4:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d00160d8:	2804fa37 	stmdacs	r4, {r0, r1, r2, r4, r5, r9, fp, ip, sp, lr, pc}
d00160dc:	d0074605 	andle	r4, r7, r5, lsl #12
d00160e0:	2b006da3 	blcs	0xd0031774
d00160e4:	aa77f47f 	bge	0xd1e132e8
d00160e8:	447b4b84 	ldrbtmi	r4, [fp], #-2948	; 0xfffff47c
d00160ec:	baf6f7ff 	blt	0xcfdd40f0
d00160f0:	213db1ae 	teqcs	sp, lr, lsr #3
d00160f4:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d00160f8:	b180fdda 	ldrdlt	pc, [r0, sl]
d00160fc:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d0016100:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0016104:	2201f81f 	andcs	pc, r1, #2031616	; 0x1f0000
d0016108:	f0004611 			; <UNDEFINED> instruction: 0xf0004611
d001610c:	f64bf9b7 			; <UNDEFINED> instruction: 0xf64bf9b7
d0016110:	46204106 	strtmi	r4, [r0], -r6, lsl #2
d0016114:	f816f7fe 			; <UNDEFINED> instruction: 0xf816f7fe
d0016118:	0108f246 	tsteq	r8, r6, asr #4	; <UNPREDICTABLE>
d001611c:	f44fe6cc 	vst1.64	{d30-d32}, [pc], ip
d0016120:	462041d0 			; <UNDEFINED> instruction: 0x462041d0
d0016124:	f80ef7fe 			; <UNDEFINED> instruction: 0xf80ef7fe
d0016128:	ba35f7ff 	blt	0xd0d9412c
d001612c:	46202128 	strtmi	r2, [r0], -r8, lsr #2
d0016130:	fdbdf7fc 	ldc2	7, cr15, [sp, #1008]!	; 0x3f0
d0016134:	d0432800 	suble	r2, r3, r0, lsl #16
d0016138:	2b2a6ae3 	blcs	0xd0ab0ccc
d001613c:	6ce2d132 	stfvsp	f5, [r2], #200	; 0xc8
d0016140:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d0016144:	d12d429a 			; <UNDEFINED> instruction: 0xd12d429a
d0016148:	46206be2 	strtmi	r6, [r0], -r2, ror #23
d001614c:	f7fa6ba1 			; <UNDEFINED> instruction: 0xf7fa6ba1
d0016150:	1e05fa80 	vmlane.f32	s30, s11, s0
d0016154:	232cdb26 			; <UNDEFINED> instruction: 0x232cdb26
d0016158:	4305fb03 	movwmi	pc, #23299	; 0x5b03	; <UNPREDICTABLE>
d001615c:	3313f503 	tstcc	r3, #12582912	; 0xc00000	; <UNPREDICTABLE>
d0016160:	330df893 	movwcc	pc, #55443	; 0xd893	; <UNPREDICTABLE>
d0016164:	d11d2b0c 	tstle	sp, ip, lsl #22
d0016168:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d001616c:	4620fd85 	strtmi	pc, [r0], -r5, lsl #27
d0016170:	fd82f7fc 	stc2	7, cr15, [r2, #1008]	; 0x3f0
d0016174:	21294a62 			; <UNDEFINED> instruction: 0x21294a62
d0016178:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d001617c:	fda5f7fc 	stc2	7, cr15, [r5, #1008]!	; 0x3f0
d0016180:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0016184:	4a5faa08 	bmi	0xd18009ac
d0016188:	46202128 	strtmi	r2, [r0], -r8, lsr #2
d001618c:	f7fc447a 			; <UNDEFINED> instruction: 0xf7fc447a
d0016190:	2800fd9c 	stmdacs	r0, {r2, r3, r4, r7, r8, sl, fp, ip, sp, lr, pc}
d0016194:	a9fff43f 	ldmibge	pc!, {r0, r1, r2, r3, r4, r5, sl, ip, sp, lr, pc}^	; <UNPREDICTABLE>
d0016198:	46204629 	strtmi	r4, [r0], -r9, lsr #12
d001619c:	ff64f000 			; <UNDEFINED> instruction: 0xff64f000
d00161a0:	ba4ef7ff 	blt	0xd13d41a4
d00161a4:	21012200 	mrscs	r2, R9_usr
d00161a8:	f0004620 			; <UNDEFINED> instruction: 0xf0004620
d00161ac:	4a56f967 	bmi	0xd15d4750
d00161b0:	21294605 			; <UNDEFINED> instruction: 0x21294605
d00161b4:	4620447a 			; <UNDEFINED> instruction: 0x4620447a
d00161b8:	fd87f7fc 	stc2	7, cr15, [r7, #1008]	; 0x3f0
d00161bc:	ba0bf7ff 	blt	0xd03141c0
d00161c0:	4620212b 	strtmi	r2, [r0], -fp, lsr #2
d00161c4:	fd73f7fc 	ldc2l	7, cr15, [r3, #-1008]!	; 0xfffffc10
d00161c8:	2100b170 	tstcs	r0, r0, ror r1
d00161cc:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d00161d0:	2802f9bb 	stmdacs	r2, {r0, r1, r3, r4, r5, r7, r8, fp, ip, sp, lr, pc}
d00161d4:	d1214605 			; <UNDEFINED> instruction: 0xd1214605
d00161d8:	2b006da3 	blcs	0xd003186c
d00161dc:	a9fbf47f 	ldmibge	fp!, {r0, r1, r2, r3, r4, r5, r6, sl, ip, sp, lr, pc}^
d00161e0:	447b4b4a 	ldrbtmi	r4, [fp], #-2890	; 0xfffff4b6
d00161e4:	ba7af7ff 	blt	0xd1ed41e8
d00161e8:	4620212d 	strtmi	r2, [r0], -sp, lsr #2
d00161ec:	fd5ff7fc 	ldc2l	7, cr15, [pc, #-1008]	; 0xd0015e04
d00161f0:	d1ea2800 	mvnle	r2, r0, lsl #16
d00161f4:	46202121 	strtmi	r2, [r0], -r1, lsr #2
d00161f8:	fd59f7fc 	ldc2l	7, cr15, [r9, #-1008]	; 0xfffffc10
d00161fc:	d1e42800 	mvnle	r2, r0, lsl #16
d0016200:	4620217e 			; <UNDEFINED> instruction: 0x4620217e
d0016204:	fd53f7fc 	ldc2l	7, cr15, [r3, #-1008]	; 0xfffffc10
d0016208:	28004605 	stmdacs	r0, {r0, r2, r9, sl, lr}
d001620c:	4940d1dd 	stmdbmi	r0, {r0, r2, r3, r4, r6, r7, r8, ip, lr, pc}^
d0016210:	44794620 	ldrbtmi	r4, [r9], #-1568	; 0xfffff9e0
d0016214:	ffc8f7f9 			; <UNDEFINED> instruction: 0xffc8f7f9
d0016218:	b9ddf7ff 	ldmiblt	sp, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}^
d001621c:	d10a2803 	tstle	sl, r3, lsl #16
d0016220:	0f21f1ba 	svceq	0x0021f1ba
d0016224:	6da3d017 	stcvs	0, cr13, [r3, #92]!	; 0x5c
d0016228:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001622c:	4b39a9d4 	blmi	0xd0e80984
d0016230:	f7ff447b 			; <UNDEFINED> instruction: 0xf7ff447b
d0016234:	f1baba53 			; <UNDEFINED> instruction: 0xf1baba53
d0016238:	d1020f2d 	tstle	r2, sp, lsr #30
d001623c:	2140f244 	cmpcs	r0, r4, asr #4	; <UNPREDICTABLE>
d0016240:	f1bae61b 			; <UNDEFINED> instruction: 0xf1bae61b
d0016244:	d1020f7e 	tstle	r2, lr, ror pc
d0016248:	31c0f244 	biccc	pc, r0, r4, asr #4
d001624c:	f1bae615 			; <UNDEFINED> instruction: 0xf1bae615
d0016250:	f47f0f21 			; <UNDEFINED> instruction: 0xf47f0f21
d0016254:	f44fa9c0 	vst2.<illegal width 64>	{d26,d28}, [pc], r0
d0016258:	46205120 	strtmi	r5, [r0], -r0, lsr #2
d001625c:	ff72f7fd 			; <UNDEFINED> instruction: 0xff72f7fd
d0016260:	f7fe2100 			; <UNDEFINED> instruction: 0xf7fe2100
d0016264:	f7fff922 			; <UNDEFINED> instruction: 0xf7fff922
d0016268:	bf00b996 	svclt	0x0000b996
d001626c:	fffffa97 			; <UNDEFINED> instruction: 0xfffffa97
d0016270:	fffffa3f 			; <UNDEFINED> instruction: 0xfffffa3f
d0016274:	fffffa9b 			; <UNDEFINED> instruction: 0xfffffa9b
d0016278:	fffff9b9 			; <UNDEFINED> instruction: 0xfffff9b9
d001627c:	fffff877 			; <UNDEFINED> instruction: 0xfffff877
d0016280:	fffff85f 			; <UNDEFINED> instruction: 0xfffff85f
d0016284:	fffff73f 			; <UNDEFINED> instruction: 0xfffff73f
d0016288:	00005b91 	muleq	r0, r1, fp
d001628c:	fffff6c3 			; <UNDEFINED> instruction: 0xfffff6c3
d0016290:	00005a9d 	muleq	r0, sp, sl
d0016294:	fffff68e 			; <UNDEFINED> instruction: 0xfffff68e
d0016298:	00005b4a 	andeq	r5, r0, sl, asr #22
d001629c:	fffff787 			; <UNDEFINED> instruction: 0xfffff787
d00162a0:	fffff6f3 			; <UNDEFINED> instruction: 0xfffff6f3
d00162a4:	fffff6fb 			; <UNDEFINED> instruction: 0xfffff6fb
d00162a8:	fffff71a 			; <UNDEFINED> instruction: 0xfffff71a
d00162ac:	fffff718 			; <UNDEFINED> instruction: 0xfffff718
d00162b0:	fffff65c 			; <UNDEFINED> instruction: 0xfffff65c
d00162b4:	fffff5b6 			; <UNDEFINED> instruction: 0xfffff5b6
d00162b8:	fffff59b 			; <UNDEFINED> instruction: 0xfffff59b
d00162bc:	fffff56f 			; <UNDEFINED> instruction: 0xfffff56f
d00162c0:	fffff562 			; <UNDEFINED> instruction: 0xfffff562
d00162c4:	00007f92 	muleq	r0, r2, pc	; <UNPREDICTABLE>
d00162c8:	fffff50b 			; <UNDEFINED> instruction: 0xfffff50b
d00162cc:	fffff4d2 			; <UNDEFINED> instruction: 0xfffff4d2
d00162d0:	fffff4e0 			; <UNDEFINED> instruction: 0xfffff4e0
d00162d4:	fffff393 			; <UNDEFINED> instruction: 0xfffff393
d00162d8:	fffff37d 			; <UNDEFINED> instruction: 0xfffff37d
d00162dc:	ffffe29e 			; <UNDEFINED> instruction: 0xffffe29e
d00162e0:	fffff3e2 			; <UNDEFINED> instruction: 0xfffff3e2
d00162e4:	fffff3e5 			; <UNDEFINED> instruction: 0xfffff3e5
d00162e8:	fffff42a 			; <UNDEFINED> instruction: 0xfffff42a
d00162ec:	fffff347 			; <UNDEFINED> instruction: 0xfffff347
d00162f0:	fffff36b 			; <UNDEFINED> instruction: 0xfffff36b
d00162f4:	fffff328 			; <UNDEFINED> instruction: 0xfffff328
d00162f8:	fffff306 			; <UNDEFINED> instruction: 0xfffff306
d00162fc:	fffff370 			; <UNDEFINED> instruction: 0xfffff370
d0016300:	fffff2fd 			; <UNDEFINED> instruction: 0xfffff2fd
d0016304:	fffff312 			; <UNDEFINED> instruction: 0xfffff312
d0016308:	fffff311 			; <UNDEFINED> instruction: 0xfffff311
d001630c:	fffff2f0 			; <UNDEFINED> instruction: 0xfffff2f0
d0016310:	fffff311 			; <UNDEFINED> instruction: 0xfffff311
d0016314:	fffff2c8 			; <UNDEFINED> instruction: 0xfffff2c8
d0016318:	e6522000 	ldrb	r2, [r2], -r0
d001631c:	3026f89b 	mlacc	r6, fp, r8, pc	; <UNPREDICTABLE>
d0016320:	0628f10b 	strteq	pc, [r8], -fp, lsl #2
d0016324:	23009307 	movwcs	r9, #775	; 0x307
d0016328:	4b1f9306 	blmi	0xd07faf48
d001632c:	ee08447b 	mcr	4, 0, r4, cr8, cr11, {3}
d0016330:	4b1e3a10 	blmi	0xd07a4b78
d0016334:	9309447b 	movwls	r4, #38011	; 0x947b
d0016338:	447b4b1d 	ldrbtmi	r4, [fp], #-2845	; 0xfffff4e3
d001633c:	3a90ee08 	bcc	0xce451b64
d0016340:	ba1df7ff 	blt	0xd0794344
d0016344:	0a2cf04f 	beq	0xd0b52488
d0016348:	4a0bfb0a 	bmi	0xd0314f78
d001634c:	3a13f50a 	bcc	0xd051377c
d0016350:	330df89a 	movwcc	pc, #55450	; 0xd89a	; <UNPREDICTABLE>
d0016354:	f47f2b0d 			; <UNDEFINED> instruction: 0xf47f2b0d
d0016358:	4659ae52 			; <UNDEFINED> instruction: 0x4659ae52
d001635c:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0016360:	4a14ffa0 	bmi	0xd05561e8
d0016364:	4620212e 	strtmi	r2, [r0], -lr, lsr #2
d0016368:	f7fc447a 			; <UNDEFINED> instruction: 0xf7fc447a
d001636c:	2800fcae 	stmdacs	r0, {r1, r2, r3, r5, r7, sl, fp, ip, sp, lr, pc}
d0016370:	a911f43f 	ldmdbge	r1, {r0, r1, r2, r3, r4, r5, sl, ip, sp, lr, pc}
d0016374:	22002301 	andcs	r2, r0, #67108864	; 0x4000000
d0016378:	130ef89a 	movwne	pc, #59546	; 0xe89a	; <UNPREDICTABLE>
d001637c:	f011e4af 			; <UNDEFINED> instruction: 0xf011e4af
d0016380:	f47f0bf7 			; <UNDEFINED> instruction: 0xf47f0bf7
d0016384:	2101ae35 	tstcs	r1, r5, lsr lr
d0016388:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d001638c:	f244ffab 	vmax.f32	d31, d20, d27
d0016390:	46206108 	strtmi	r6, [r0], -r8, lsl #2
d0016394:	fed6f7fd 	mrc2	7, 6, pc, cr6, cr13, {7}
d0016398:	2b5b6ae3 	blcs	0xd16f0f2c
d001639c:	302cf89a 	mlacc	ip, sl, r8, pc	; <UNPREDICTABLE>
d00163a0:	ae88f47f 	mcrge	4, 4, pc, cr8, cr15, {3}	; <UNPREDICTABLE>
d00163a4:	e63b2b08 	ldrt	r2, [fp], -r8, lsl #22
d00163a8:	ffffed44 			; <UNDEFINED> instruction: 0xffffed44
d00163ac:	ffffedea 			; <UNDEFINED> instruction: 0xffffedea
d00163b0:	ffffedab 			; <UNDEFINED> instruction: 0xffffedab
d00163b4:	fffff037 			; <UNDEFINED> instruction: 0xfffff037

Disassembly of section .text.expression:

d001647c <.text.expression>:
d001647c:	4ff0e92d 	svcmi	0x00f0e92d
d0016480:	b08b6a03 	addlt	r6, fp, r3, lsl #20
d0016484:	f5004690 			; <UNDEFINED> instruction: 0xf5004690
d0016488:	93043216 	movwls	r3, #16918	; 0x4216
d001648c:	6a434604 	bvs	0xd10e7ca4
d0016490:	7030f890 	mlasvc	r0, r0, r8, pc	; <UNPREDICTABLE>
d0016494:	91069301 	tstls	r6, r1, lsl #6
d0016498:	630ae9d0 	movwvs	lr, #43472	; 0xa9d0
d001649c:	6b439305 	blvs	0xd10fb0b8
d00164a0:	f8d29302 			; <UNDEFINED> instruction: 0xf8d29302
d00164a4:	330131f8 	movwcc	r3, #4600	; 0x11f8
d00164a8:	f8c22b20 			; <UNDEFINED> instruction: 0xf8c22b20
d00164ac:	d90331f8 	stmdble	r3, {r3, r4, r5, r6, r7, r8, ip, sp}
d00164b0:	447949ef 	ldrbtmi	r4, [r9], #-2543	; 0xfffff611
d00164b4:	fe78f7f9 	mrc2	7, 3, pc, cr8, cr9, {7}
d00164b8:	0e03f1a8 	mvfeqdp	f7, #0.0
d00164bc:	f1de4620 			; <UNDEFINED> instruction: 0xf1de4620
d00164c0:	eb410100 	bl	0xd10568c8
d00164c4:	f7ff010e 			; <UNDEFINED> instruction: 0xf7ff010e
d00164c8:	4beaf83f 	blmi	0xcfad45cc
d00164cc:	447b4605 	ldrbtmi	r4, [fp], #-1541	; 0xfffff9fb
d00164d0:	4be99307 	blmi	0xcfa7b0f4
d00164d4:	9308447b 	movwls	r4, #33915	; 0x847b
d00164d8:	9058f8d4 	ldrsbls	pc, [r8], #-132	; 0xffffff7c	; <UNPREDICTABLE>
d00164dc:	0f00f1b9 	svceq	0x0000f1b9
d00164e0:	f8d4d119 			; <UNDEFINED> instruction: 0xf8d4d119
d00164e4:	f1baa02c 			; <UNDEFINED> instruction: 0xf1baa02c
d00164e8:	f0000f5e 			; <UNDEFINED> instruction: 0xf0000f5e
d00164ec:	f300813c 	veor	d8, d0, d28
d00164f0:	f1ba8114 			; <UNDEFINED> instruction: 0xf1ba8114
d00164f4:	f3000f2f 	vpmax.f32	d0, d0, d31
d00164f8:	f1ba8107 			; <UNDEFINED> instruction: 0xf1ba8107
d00164fc:	f3000f24 	vpmax.f32	d0, d0, d20
d0016500:	9b0680f1 	blls	0xd01b68cc
d0016504:	dc06454b 	cfstr32le	mvfx4, [r6], {75}	; 0x4b
d0016508:	d11b2d02 	tstle	fp, r2, lsl #26
d001650c:	462049db 			; <UNDEFINED> instruction: 0x462049db
d0016510:	f7f94479 			; <UNDEFINED> instruction: 0xf7f94479
d0016514:	f108fe49 			; <UNDEFINED> instruction: 0xf108fe49
d0016518:	2b0133ff 	blcs	0xd006351c
d001651c:	812ff200 	msrhi	(UNDEF: 47), r0
d0016520:	d10a2d02 	tstle	sl, r2, lsl #26
d0016524:	b9436da3 	stmdblt	r3, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0016528:	447b4bd5 	ldrbtmi	r4, [fp], #-3029	; 0xfffff42b
d001652c:	9b0165a3 	blls	0xd006fbc0
d0016530:	9b0265e3 	blls	0xd00afcc4
d0016534:	6718e9c4 	ldrvs	lr, [r8, -r4, asr #19]
d0016538:	f1b866a3 			; <UNDEFINED> instruction: 0xf1b866a3
d001653c:	f0400f01 			; <UNDEFINED> instruction: 0xf0400f01
d0016540:	e11f812f 	tst	pc, pc, lsr #2
d0016544:	f1094620 			; <UNDEFINED> instruction: 0xf1094620
d0016548:	f7fc0901 			; <UNDEFINED> instruction: 0xf7fc0901
d001654c:	f46ffb95 			; <UNDEFINED> instruction: 0xf46ffb95
d0016550:	eb0a7c8f 	bl	0xd02b5794
d0016554:	2b01030c 	blcs	0xd005718c
d0016558:	f5aad82e 			; <UNDEFINED> instruction: 0xf5aad82e
d001655c:	f64d7090 			; <UNDEFINED> instruction: 0xf64d7090
d0016560:	42455bf8 	submi	r5, r5, #248, 22	; 0x3e000
d0016564:	46204145 	strtmi	r4, [r0], -r5, asr #2
d0016568:	f7fd4629 			; <UNDEFINED> instruction: 0xf7fd4629
d001656c:	2202ff8b 	andcs	pc, r2, #556	; 0x22c
d0016570:	46824649 	strmi	r4, [r2], r9, asr #12
d0016574:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0016578:	4620ff81 	strtmi	pc, [r0], -r1, lsl #31
d001657c:	5120f44f 	msrpl	CPSR_, pc, asr #8
d0016580:	fde0f7fd 	stc2l	7, cr15, [r0, #1012]!	; 0x3f4
d0016584:	f7fd2101 			; <UNDEFINED> instruction: 0xf7fd2101
d0016588:	f7fdff90 			; <UNDEFINED> instruction: 0xf7fdff90
d001658c:	2300ff6f 	movwcs	pc, #3951	; 0xf6f	; <UNPREDICTABLE>
d0016590:	200bf854 	andcs	pc, fp, r4, asr r8	; <UNPREDICTABLE>
d0016594:	46514681 	ldrbmi	r4, [r1], -r1, lsl #13
d0016598:	f7fe6da0 			; <UNDEFINED> instruction: 0xf7fe6da0
d001659c:	4629fce1 	strtmi	pc, [r9], -r1, ror #25
d00165a0:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d00165a4:	2300fe2b 	movwcs	pc, #3627	; 0xe2b	; <UNPREDICTABLE>
d00165a8:	200bf854 	andcs	pc, fp, r4, asr r8	; <UNPREDICTABLE>
d00165ac:	6da04649 	stcvs	6, cr4, [r0, #292]!	; 0x124
d00165b0:	fcd6f7fe 	ldc2l	7, cr15, [r6], {254}	; 0xfe
d00165b4:	e78f2500 	str	r2, [pc, r0, lsl #10]
d00165b8:	718df46f 	orrvc	pc, sp, pc, ror #8
d00165bc:	eb0a2d03 	bl	0xd02a19d0
d00165c0:	93030301 	movwls	r0, #13057	; 0x3301
d00165c4:	2b01d10e 	blcs	0xd008aa04
d00165c8:	6da3d90c 			; <UNDEFINED> instruction: 0x6da3d90c
d00165cc:	d1a22b00 			; <UNDEFINED> instruction: 0xd1a22b00
d00165d0:	447b4bac 	ldrbtmi	r4, [fp], #-2988	; 0xfffff454
d00165d4:	9b0165a3 	blls	0xd006fc68
d00165d8:	9b0265e3 	blls	0xd00afd6c
d00165dc:	6718e9c4 	ldrvs	lr, [r8, -r4, asr #19]
d00165e0:	e79866a3 	ldr	r6, [r8, r3, lsr #13]
d00165e4:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d00165e8:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d00165ec:	6a23fdab 	bvs	0xd0915ca0
d00165f0:	22024649 	andcs	r4, r2, #76546048	; 0x4900000
d00165f4:	f8d49309 			; <UNDEFINED> instruction: 0xf8d49309
d00165f8:	f7ffb02c 			; <UNDEFINED> instruction: 0xf7ffb02c
d00165fc:	f64bff3f 			; <UNDEFINED> instruction: 0xf64bff3f
d0016600:	46814106 	strmi	r4, [r1], r6, lsl #2
d0016604:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0016608:	2d04fd9d 	stccs	13, cr15, [r4, #-628]	; 0xfffffd8c
d001660c:	f0009b09 			; <UNDEFINED> instruction: 0xf0009b09
d0016610:	f1b980ea 			; <UNDEFINED> instruction: 0xf1b980ea
d0016614:	d1110f04 	tstle	r1, r4, lsl #30
d0016618:	0f2bf1ba 	svceq	0x002bf1ba
d001661c:	8106f040 	tsthi	r6, r0, asr #32	; <UNPREDICTABLE>
d0016620:	2b011eeb 	blcs	0xd005e1d4
d0016624:	8106f240 	tsthi	r6, r0, asr #4	; <UNPREDICTABLE>
d0016628:	46202189 	strtmi	r2, [r0], -r9, lsl #3
d001662c:	fd8af7fd 	stc2	7, cr15, [sl, #1012]	; 0x3f4
d0016630:	0108f641 	tsteq	r8, r1, asr #12	; <UNPREDICTABLE>
d0016634:	f7fd2504 			; <UNDEFINED> instruction: 0xf7fd2504
d0016638:	e74dfd85 	strb	pc, [sp, -r5, lsl #27]	; <UNPREDICTABLE>
d001663c:	d0022d03 	andle	r2, r2, r3, lsl #26
d0016640:	0f03f1b9 	svceq	0x0003f1b9
d0016644:	9a05d13c 	bls	0xd018ab3c
d0016648:	7b81f5ab 	blvc	0xce093cfc
d001664c:	7281f5a2 	addvc	pc, r1, #679477248	; 0x28800000
d0016650:	bf972a01 	svclt	0x00972a01
d0016654:	22009a04 	andcs	r9, r0, #4, 20	; 0x4000
d0016658:	f282fab2 			; <UNDEFINED> instruction: 0xf282fab2
d001665c:	f1bb0952 			; <UNDEFINED> instruction: 0xf1bb0952
d0016660:	bf960f01 	svclt	0x00960f01
d0016664:	f383fab3 			; <UNDEFINED> instruction: 0xf383fab3
d0016668:	095b2300 	ldmdbeq	fp, {r8, r9, sp}^
d001666c:	d00b2d04 	andle	r2, fp, r4, lsl #26
d0016670:	f0402d03 			; <UNDEFINED> instruction: 0xf0402d03
d0016674:	f1a980d1 			; <UNDEFINED> instruction: 0xf1a980d1
d0016678:	f1b90903 			; <UNDEFINED> instruction: 0xf1b90903
d001667c:	d80f0f01 	stmdale	pc, {r0, r8, r9, sl, fp}	; <UNPREDICTABLE>
d0016680:	2b019b03 	blcs	0xd007d294
d0016684:	e015d80c 	ands	sp, r5, ip, lsl #16
d0016688:	0203f1a9 	andeq	pc, r3, #1073741866	; 0x4000002a
d001668c:	d9f72a01 	ldmible	r7!, {r0, r9, fp, sp}^
d0016690:	0f04f1b9 	svceq	0x0004f1b9
d0016694:	f1b9d004 			; <UNDEFINED> instruction: 0xf1b9d004
d0016698:	d1010f00 	tstle	r1, r0, lsl #30
d001669c:	d1ef2b00 	mvnle	r2, r0, lsl #22
d00166a0:	b93b6da3 	ldmdblt	fp!, {r0, r1, r5, r7, r8, sl, fp, sp, lr}
d00166a4:	65a39b07 	strvs	r9, [r3, #2823]!	; 0xb07
d00166a8:	65e39b01 	strbvs	r9, [r3, #2817]!	; 0xb01
d00166ac:	e9c49b02 	stmib	r4, {r1, r8, r9, fp, ip, pc}^
d00166b0:	66a36718 	ssatvs	r6, #4, r8, lsl #14
d00166b4:	46512201 	ldrbmi	r2, [r1], -r1, lsl #4
d00166b8:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d00166bc:	e779ff69 	ldrb	pc, [r9, -r9, ror #30]!	; <UNPREDICTABLE>
d00166c0:	d0032d01 	andle	r2, r3, r1, lsl #26
d00166c4:	32fff109 	rscscc	pc, pc, #1073741826	; 0x40000002
d00166c8:	41554255 	cmpmi	r5, r5, asr r2
d00166cc:	4651462a 	ldrbmi	r4, [r1], -sl, lsr #12
d00166d0:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d00166d4:	1e05ff5d 	mcrne	15, 0, pc, cr5, cr13, {2}	; <UNPREDICTABLE>
d00166d8:	2501bf18 	strcs	fp, [r1, #-3864]	; 0xfffff0e8
d00166dc:	f04fe6fc 			; <UNDEFINED> instruction: 0xf04fe6fc
d00166e0:	e70e0902 	str	r0, [lr, -r2, lsl #18]
d00166e4:	0325f1aa 	msreq	CPSR_sc, #-2147483606	; 0x8000002a
d00166e8:	d80a2b0a 	stmdale	sl, {r1, r3, r8, r9, fp, sp}
d00166ec:	f003e8df 			; <UNDEFINED> instruction: 0xf003e8df
d00166f0:	09094138 	stmdbeq	r9, {r3, r4, r5, r8, lr}
d00166f4:	09063809 	stmdbeq	r6, {r0, r3, fp, ip, sp}
d00166f8:	00380906 	eorseq	r0, r8, r6, lsl #18
d00166fc:	0908f04f 	stmdbeq	r8, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d0016700:	f04fe6ff 			; <UNDEFINED> instruction: 0xf04fe6ff
d0016704:	e6fc0900 	ldrbt	r0, [ip], r0, lsl #18
d0016708:	0302f02a 	movweq	pc, #8234	; 0x202a	; <UNPREDICTABLE>
d001670c:	bf142b3c 	svclt	0x00142b3c
d0016710:	0900f04f 	stmdbeq	r0, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d0016714:	0907f04f 	stmdbeq	r7, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d0016718:	f1bae6f3 			; <UNDEFINED> instruction: 0xf1bae6f3
d001671c:	d02b0f7c 	eorle	r0, fp, ip, ror pc
d0016720:	738df46f 	orrvc	pc, sp, #1862270976	; 0x6f000000
d0016724:	2b054453 	blcs	0xd0167878
d0016728:	aeebf63f 	mcrge	6, 7, pc, cr11, cr15, {1}	; <UNPREDICTABLE>
d001672c:	d8e82b05 	stmiale	r8!, {r0, r2, r8, r9, fp, sp}^
d0016730:	f852a202 			; <UNDEFINED> instruction: 0xf852a202
d0016734:	441a3023 	ldrmi	r3, [sl], #-35	; 0xffffffdd
d0016738:	bf004710 	svclt	0x00004710
d001673c:	00000019 	andeq	r0, r0, r9, lsl r0
d0016740:	00000019 	andeq	r0, r0, r9, lsl r0
d0016744:	0000001f 	andeq	r0, r0, pc, lsl r0
d0016748:	0000001f 	andeq	r0, r0, pc, lsl r0
d001674c:	ffffffa3 			; <UNDEFINED> instruction: 0xffffffa3
d0016750:	00000031 	andeq	r0, r0, r1, lsr r0
d0016754:	0906f04f 	stmdbeq	r6, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d0016758:	f04fe6d3 			; <UNDEFINED> instruction: 0xf04fe6d3
d001675c:	e6d00907 	ldrb	r0, [r0], r7, lsl #18
d0016760:	0909f04f 	stmdbeq	r9, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d0016764:	f04fe6cd 			; <UNDEFINED> instruction: 0xf04fe6cd
d0016768:	e6ca0904 	strb	r0, [sl], r4, lsl #18
d001676c:	0901f04f 	stmdbeq	r1, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d0016770:	f04fe6c7 			; <UNDEFINED> instruction: 0xf04fe6c7
d0016774:	e6c40905 	strb	r0, [r4], r5, lsl #18
d0016778:	0903f04f 	stmdbeq	r3, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d001677c:	f1b8e6c1 			; <UNDEFINED> instruction: 0xf1b8e6c1
d0016780:	d1180f01 	tstle	r8, r1, lsl #30
d0016784:	2b011eeb 	blcs	0xd005e338
d0016788:	6da3d80a 	stcvs	8, cr13, [r3, #40]!	; 0x28
d001678c:	4b3eb943 	blmi	0xd0fc4ca0
d0016790:	65a3447b 	strvs	r4, [r3, #1147]!	; 0x47b
d0016794:	65e39b01 	strbvs	r9, [r3, #2817]!	; 0xb01
d0016798:	e9c49b02 	stmib	r4, {r1, r8, r9, fp, ip, pc}^
d001679c:	66a36718 	ssatvs	r6, #4, r8, lsl #14
d00167a0:	3416f504 	ldrcc	pc, [r6], #-1284	; 0xfffffafc
d00167a4:	f8d44628 			; <UNDEFINED> instruction: 0xf8d44628
d00167a8:	3b0131f8 	blcc	0xd0062f90
d00167ac:	31f8f8c4 	mvnscc	pc, r4, asr #17
d00167b0:	e8bdb00b 	pop	{r0, r1, r3, ip, sp, pc}
d00167b4:	f1b88ff0 			; <UNDEFINED> instruction: 0xf1b88ff0
d00167b8:	d1f10f04 	mvnsle	r0, r4, lsl #30
d00167bc:	2b011eeb 	blcs	0xd005e370
d00167c0:	9b05d9ee 	blls	0xd018cf80
d00167c4:	7381f5a3 	orrvc	pc, r1, #683671552	; 0x28c00000
d00167c8:	d8022b01 	stmdale	r2, {r0, r8, r9, fp, sp}
d00167cc:	2b009b04 	blcs	0xd003d3e4
d00167d0:	6da3d0e6 	stcvs	0, cr13, [r3, #920]!	; 0x398
d00167d4:	d1e32b00 	mvnle	r2, r0, lsl #22
d00167d8:	447b4b2c 	ldrbtmi	r4, [fp], #-2860	; 0xfffff4d4
d00167dc:	2d04e7d9 	stccs	7, cr14, [r4, #-868]	; 0xfffffc9c
d00167e0:	af59f43f 	svcge	0x0059f43f
d00167e4:	f1bae75c 			; <UNDEFINED> instruction: 0xf1bae75c
d00167e8:	d1300f2b 	teqle	r0, fp, lsr #30
d00167ec:	0f04f1b9 	svceq	0x0004f1b9
d00167f0:	af16f43f 	svcge	0x0016f43f
d00167f4:	0f03f1b9 	svceq	0x0003f1b9
d00167f8:	2180d01c 	orrcs	sp, r0, ip, lsl r0
d00167fc:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0016800:	f641fca1 			; <UNDEFINED> instruction: 0xf641fca1
d0016804:	f6412308 			; <UNDEFINED> instruction: 0xf6412308
d0016808:	f1ba0108 			; <UNDEFINED> instruction: 0xf1ba0108
d001680c:	bf180f2b 	svclt	0x00180f2b
d0016810:	f7fd4619 			; <UNDEFINED> instruction: 0xf7fd4619
d0016814:	e65ffc97 			; <UNDEFINED> instruction: 0xe65ffc97
d0016818:	0f04f1b9 	svceq	0x0004f1b9
d001681c:	2d00d1df 	stfcsd	f5, [r0, #-892]	; 0xfffffc84
d0016820:	af3ef47f 	svcge	0x003ef47f
d0016824:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0016828:	e739af2b 	ldr	sl, [r9, -fp, lsr #30]!
d001682c:	0f2df1ba 	svceq	0x002df1ba
d0016830:	af09f47f 	svcge	0x0009f47f
d0016834:	2b006da3 	blcs	0xd0031ec8
d0016838:	ae4ef47f 	mcrge	4, 2, pc, cr14, cr15, {3}	; <UNPREDICTABLE>
d001683c:	65a39b08 	strvs	r9, [r3, #2824]!	; 0xb08
d0016840:	65e39b01 	strbvs	r9, [r3, #2817]!	; 0xb01
d0016844:	e9c49b02 	stmib	r4, {r1, r8, r9, fp, ip, pc}^
d0016848:	66a36718 	ssatvs	r6, #4, r8, lsl #14
d001684c:	f1bae644 			; <UNDEFINED> instruction: 0xf1bae644
d0016850:	f47f0f2d 			; <UNDEFINED> instruction: 0xf47f0f2d
d0016854:	f1b9aef8 			; <UNDEFINED> instruction: 0xf1b9aef8
d0016858:	d1cb0f04 	bicle	r0, fp, r4, lsl #30
d001685c:	2108f641 	tstcs	r8, r1, asr #12	; <UNPREDICTABLE>
d0016860:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0016864:	f44ffc6f 			; <UNDEFINED> instruction: 0xf44ffc6f
d0016868:	f7fd5184 			; <UNDEFINED> instruction: 0xf7fd5184
d001686c:	e6a1fc6b 	strt	pc, [r1], fp, ror #24
d0016870:	ffffeb75 			; <UNDEFINED> instruction: 0xffffeb75
d0016874:	ffffff01 			; <UNDEFINED> instruction: 0xffffff01
d0016878:	fffffee0 			; <UNDEFINED> instruction: 0xfffffee0
d001687c:	ffffefc2 			; <UNDEFINED> instruction: 0xffffefc2
d0016880:	fffffedb 			; <UNDEFINED> instruction: 0xfffffedb
d0016884:	ffffef26 			; <UNDEFINED> instruction: 0xffffef26
d0016888:	fffffc99 			; <UNDEFINED> instruction: 0xfffffc99
d001688c:	fffffc78 			; <UNDEFINED> instruction: 0xfffffc78

Disassembly of section .text.struct_member:

d001692c <.text.struct_member>:
d001692c:	4ff0e92d 	svcmi	0x00f0e92d
d0016930:	4b6e461d 	blmi	0xd1ba81ac
d0016934:	460e4604 	strmi	r4, [lr], -r4, lsl #12
d0016938:	f44f447b 	vst3.16	{d20-d22}, [pc :256], fp
d001693c:	ed2d7b1a 	vpush	{d7-d19}
d0016940:	ee088b02 	vmla.f64	d8, d8, d2
d0016944:	b0873a90 	umulllt	r3, r7, r0, sl
d0016948:	69a39204 	stmibvs	r3!, {r2, r9, ip, pc}
d001694c:	2a90ee18 	bcs	0xce4521b4
d0016950:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d0016954:	ee084620 	cfmadd32	mvax1, mvfx4, mvfx8, mvfx0
d0016958:	69e33a10 	stmibvs	r3!, {r4, r9, fp, ip, sp}^
d001695c:	6a639305 	bvs	0xd18fb578
d0016960:	6aa39300 	bvs	0xce8fb568
d0016964:	f8949301 			; <UNDEFINED> instruction: 0xf8949301
d0016968:	93023030 	movwls	r3, #8240	; 0x2030
d001696c:	93036b63 	movwls	r6, #15203	; 0x3b63
d0016970:	f9abf7fc 			; <UNDEFINED> instruction: 0xf9abf7fc
d0016974:	b9089b05 	stmdblt	r8, {r0, r2, r8, r9, fp, ip, pc}
d0016978:	e0282500 	eor	r2, r8, r0, lsl #10
d001697c:	f806fb0b 			; <UNDEFINED> instruction: 0xf806fb0b
d0016980:	f5082700 			; <UNDEFINED> instruction: 0xf5082700
d0016984:	44a039bc 	strtmi	r3, [r0], #2492	; 0x9bc
d0016988:	0928f109 	stmdbeq	r8!, {r0, r3, r8, ip, sp, lr, pc}
d001698c:	38bdf508 	popcc	{r3, r8, sl, ip, sp, lr, pc}
d0016990:	0a09eb04 	beq	0xd02915a8
d0016994:	206af898 	mlscs	sl, r8, r8, pc	; <UNPREDICTABLE>
d0016998:	d81e42ba 	ldmdale	lr, {r1, r3, r4, r5, r7, r9, lr}
d001699c:	4606fb0b 	strmi	pc, [r6], -fp, lsl #22
d00169a0:	36bdf506 	ldrtcc	pc, [sp], r6, lsl #10	; <UNPREDICTABLE>
d00169a4:	306af896 	mlscc	sl, r6, r8, pc	; <UNPREDICTABLE>
d00169a8:	d12742bb 			; <UNDEFINED> instruction: 0xd12742bb
d00169ac:	306bf896 	mlscc	fp, r6, r8, pc	; <UNPREDICTABLE>
d00169b0:	4b4fbb0b 	blmi	0xd14055e4
d00169b4:	6da5447b 	cfstrsvs	mvf4, [r5, #492]!	; 0x1ec
d00169b8:	d1dd2d00 	bicsle	r2, sp, r0, lsl #26
d00169bc:	9b0065a3 	blls	0xd0030050
d00169c0:	9b0165e3 	blls	0xd0070154
d00169c4:	9b026623 	blls	0xd00b0258
d00169c8:	9b036663 	blls	0xd00f035c
d00169cc:	462866a3 	strtmi	r6, [r8], -r3, lsr #13
d00169d0:	ecbdb007 	ldc	0, cr11, [sp], #28
d00169d4:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d00169d8:	f8da8ff0 			; <UNDEFINED> instruction: 0xf8da8ff0
d00169dc:	ee181004 	cdp	0, 1, cr1, cr8, cr4, {0}
d00169e0:	f85a2a10 			; <UNDEFINED> instruction: 0xf85a2a10
d00169e4:	93050b24 	movwls	r0, #23332	; 0x5b24
d00169e8:	fdc4f7f9 	stc2l	7, cr15, [r4, #996]	; 0x3e4
d00169ec:	28009b05 	stmdacs	r0, {r0, r2, r8, r9, fp, ip, pc}
d00169f0:	3701d1d4 			; <UNDEFINED> instruction: 0x3701d1d4
d00169f4:	4b3fe7ce 	blmi	0xd1010934
d00169f8:	e7dc447b 			; <UNDEFINED> instruction: 0xe7dc447b
d00169fc:	fb032324 	blx	0xd00df696
d0016a00:	44279707 	strtmi	r9, [r7], #-1799	; 0xfffff8f9
d0016a04:	f8978c7a 			; <UNDEFINED> instruction: 0xf8978c7a
d0016a08:	b14a6020 	cmplt	sl, r0, lsr #32
d0016a0c:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d0016a10:	f7fd0092 			; <UNDEFINED> instruction: 0xf7fd0092
d0016a14:	f44ffbb5 			; <UNDEFINED> instruction: 0xf44ffbb5
d0016a18:	462051c2 	strtmi	r5, [r0], -r2, asr #3
d0016a1c:	fb92f7fd 	blx	0xce4d4a1a
d0016a20:	d0152eff 			; <UNDEFINED> instruction: 0xd0152eff
d0016a24:	4620212e 	strtmi	r2, [r0], -lr, lsr #2
d0016a28:	f941f7fc 			; <UNDEFINED> instruction: 0xf941f7fc
d0016a2c:	d18c2800 	orrle	r2, ip, r0, lsl #16
d0016a30:	6da3b965 			; <UNDEFINED> instruction: 0x6da3b965
d0016a34:	4b30b953 	blmi	0xd0c44f88
d0016a38:	65a3447b 	strvs	r4, [r3, #1147]!	; 0x47b
d0016a3c:	65e39b00 	strbvs	r9, [r3, #2816]!	; 0xb00
d0016a40:	66239b01 	strtvs	r9, [r3], -r1, lsl #22
d0016a44:	66639b02 	strbtvs	r9, [r3], -r2, lsl #22
d0016a48:	66a39b03 	strtvs	r9, [r3], r3, lsl #22
d0016a4c:	e7be2503 	ldr	r2, [lr, r3, lsl #10]!
d0016a50:	2e2e6ae6 	vnmulcs.f32	s12, s29, s13
d0016a54:	4929d105 	stmdbmi	r9!, {r0, r2, r8, ip, lr, pc}
d0016a58:	44794620 	ldrbtmi	r4, [r9], #-1568	; 0xfffff9e0
d0016a5c:	fba4f7f9 	blx	0xce954a4a
d0016a60:	2d00e78a 	stccs	7, cr14, [r0, #-552]	; 0xfffffdd8
d0016a64:	9b04d140 	blls	0xd014af6c
d0016a68:	2e3db3c3 	cdpcs	3, 3, cr11, cr13, cr3, {6}
d0016a6c:	f5a6d003 			; <UNDEFINED> instruction: 0xf5a6d003
d0016a70:	2b017392 	blcs	0xd00738c0
d0016a74:	4620d832 			; <UNDEFINED> instruction: 0x4620d832
d0016a78:	f8fef7fc 			; <UNDEFINED> instruction: 0xf8fef7fc
d0016a7c:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d0016a80:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0016a84:	2e3dfb5f 	mrccs	11, 1, APSR_nzcv, cr13, cr15, {2}
d0016a88:	f44fd007 	vst4.8	{d29-d32}, [pc], r7
d0016a8c:	f7fd41d0 			; <UNDEFINED> instruction: 0xf7fd41d0
d0016a90:	f24bfb59 	vpadd.i8	<illegal reg q15.5>, <illegal reg q5.5>, <illegal reg q4.5>
d0016a94:	f7fd4103 			; <UNDEFINED> instruction: 0xf7fd4103
d0016a98:	2201fb55 	andcs	pc, r1, #87040	; 0x15400
d0016a9c:	46114620 	ldrmi	r4, [r1], -r0, lsr #12
d0016aa0:	fcecf7ff 	stc2l	7, cr15, [ip], #1020	; 0x3fc
d0016aa4:	d00e2e3d 	andle	r2, lr, sp, lsr lr
d0016aa8:	4106f64b 	tstmi	r6, fp, asr #12	; <UNPREDICTABLE>
d0016aac:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0016ab0:	f641fb49 			; <UNDEFINED> instruction: 0xf641fb49
d0016ab4:	f6410108 			; <UNDEFINED> instruction: 0xf6410108
d0016ab8:	f5b62308 			; <UNDEFINED> instruction: 0xf5b62308
d0016abc:	bf187f92 	svclt	0x00187f92
d0016ac0:	f7fd4619 			; <UNDEFINED> instruction: 0xf7fd4619
d0016ac4:	f64bfb3f 			; <UNDEFINED> instruction: 0xf64bfb3f
d0016ac8:	46204106 	strtmi	r4, [r0], -r6, lsl #2
d0016acc:	fb3af7fd 	blx	0xd0ed4aca
d0016ad0:	0108f246 	tsteq	r8, r6, asr #4	; <UNPREDICTABLE>
d0016ad4:	f7fd2502 			; <UNDEFINED> instruction: 0xf7fd2502
d0016ad8:	e778fb35 			; <UNDEFINED> instruction: 0xe778fb35
d0016adc:	41d0f44f 	bicsmi	pc, r0, pc, asr #8
d0016ae0:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0016ae4:	e772fb2f 	ldrb	pc, [r2, -pc, lsr #22]!	; <UNPREDICTABLE>
d0016ae8:	e7702504 	ldrb	r2, [r0, -r4, lsl #10]!
d0016aec:	ffffff7d 			; <UNDEFINED> instruction: 0xffffff7d
d0016af0:	fffffeec 			; <UNDEFINED> instruction: 0xfffffeec
d0016af4:	fffffe94 			; <UNDEFINED> instruction: 0xfffffe94
d0016af8:	fffffe99 			; <UNDEFINED> instruction: 0xfffffe99
d0016afc:	fffffe9f 			; <UNDEFINED> instruction: 0xfffffe9f

Disassembly of section .text.struct_array_element:

d0016b78 <.text.struct_array_element>:
d0016b78:	41f0e92d 	mvnsmi	lr, sp, lsr #18
d0016b7c:	4a244617 	bmi	0xd09283e0
d0016b80:	215b460d 	cmpcs	fp, sp, lsl #12
d0016b84:	4604447a 			; <UNDEFINED> instruction: 0x4604447a
d0016b88:	f7fc461e 			; <UNDEFINED> instruction: 0xf7fc461e
d0016b8c:	b3e0f89e 	mvnlt	pc, #10354688	; 0x9e0000
d0016b90:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d0016b94:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0016b98:	2201fad5 	andcs	pc, r1, #872448	; 0xd5000
d0016b9c:	f7ff4611 			; <UNDEFINED> instruction: 0xf7ff4611
d0016ba0:	4a1cfc6d 	bmi	0xd0755d5c
d0016ba4:	4620215d 			; <UNDEFINED> instruction: 0x4620215d
d0016ba8:	f7fc447a 			; <UNDEFINED> instruction: 0xf7fc447a
d0016bac:	b360f88e 	msrlt	SPSR_, #9306112	; 0x8e0000
d0016bb0:	4106f64b 	tstmi	r6, fp, asr #12	; <UNPREDICTABLE>
d0016bb4:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0016bb8:	f44ffac5 	vst1.64	{d31-d32}, [pc], r5
d0016bbc:	2102701a 	tstcs	r2, sl, lsl r0
d0016bc0:	4005fb00 	andmi	pc, r5, r0, lsl #22
d0016bc4:	30bdf500 	adcscc	pc, sp, r0, lsl #10
d0016bc8:	2068f8b0 	strhtcs	pc, [r8], #-128	; 0xffffff80	; <UNPREDICTABLE>
d0016bcc:	00924620 	addseq	r4, r2, r0, lsr #12
d0016bd0:	fad6f7fd 	blx	0xcf5d4bcc
d0016bd4:	3150f244 	cmpcc	r0, r4, asr #4	; <UNPREDICTABLE>
d0016bd8:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0016bdc:	f44ffab3 	vst1.32	{d31-d32}, [pc :256], r3
d0016be0:	f7fd51c2 			; <UNDEFINED> instruction: 0xf7fd51c2
d0016be4:	b986faaf 	stmiblt	r6, {r0, r1, r2, r3, r5, r7, r9, fp, ip, sp, lr, pc}
d0016be8:	f7fc212e 			; <UNDEFINED> instruction: 0xf7fc212e
d0016bec:	b138f860 	teqlt	r8, r0, ror #16	; <UNPREDICTABLE>
d0016bf0:	463a4633 			; <UNDEFINED> instruction: 0x463a4633
d0016bf4:	46204629 	strtmi	r4, [r0], -r9, lsr #12
d0016bf8:	41f0e8bd 	ldrhmi	lr, [r0, #141]!	; 0x8d
d0016bfc:	be96f7ff 	mrclt	7, 4, APSR_nzcv, cr6, cr15, {7}
d0016c00:	46204905 	strtmi	r4, [r0], -r5, lsl #18
d0016c04:	f7f94479 			; <UNDEFINED> instruction: 0xf7f94479
d0016c08:	2003facf 	andcs	pc, r3, pc, asr #21
d0016c0c:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d0016c10:	ffffff78 			; <UNDEFINED> instruction: 0xffffff78
d0016c14:	ffffff74 			; <UNDEFINED> instruction: 0xffffff74
d0016c18:	ffffff3e 			; <UNDEFINED> instruction: 0xffffff3e

Disassembly of section .text.struct_pointer_value:

d0016cd0 <.text.struct_pointer_value>:
d0016cd0:	4ff0e92d 	svcmi	0x00f0e92d
d0016cd4:	b0854604 	addlt	r4, r5, r4, lsl #12
d0016cd8:	2126460f 			; <UNDEFINED> instruction: 0x2126460f
d0016cdc:	ffe7f7fb 			; <UNDEFINED> instruction: 0xffe7f7fb
d0016ce0:	f2406ae3 	vpmax.s8	q11, q8, <illegal reg q9.5>
d0016ce4:	90021201 	andls	r1, r2, r1, lsl #4
d0016ce8:	f0404293 			; <UNDEFINED> instruction: 0xf0404293
d0016cec:	6a6280ef 	bvs	0xd18b70b0
d0016cf0:	f8d44620 			; <UNDEFINED> instruction: 0xf8d44620
d0016cf4:	92018028 	andls	r8, r1, #40	; 0x28
d0016cf8:	9030f894 	mlasls	r0, r4, r8, pc	; <UNPREDICTABLE>
d0016cfc:	a034f8d4 	ldrsbtge	pc, [r4], -r4	; <UNPREDICTABLE>
d0016d00:	6306e9d4 	movwvs	lr, #27092	; 0x69d4
d0016d04:	4631461a 			; <UNDEFINED> instruction: 0x4631461a
d0016d08:	f7f99303 			; <UNDEFINED> instruction: 0xf7f99303
d0016d0c:	1e05fca2 	cdpne	12, 0, cr15, cr5, cr2, {5}
d0016d10:	da1e9b03 	ble	0xd07bd924
d0016d14:	4631461a 			; <UNDEFINED> instruction: 0x4631461a
d0016d18:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d0016d1c:	9b03fcba 	blls	0xd011600c
d0016d20:	9a024683 	bls	0xd00a8734
d0016d24:	4a74b9c2 	bmi	0xd1d45434
d0016d28:	46304619 			; <UNDEFINED> instruction: 0x46304619
d0016d2c:	f7f9447a 			; <UNDEFINED> instruction: 0xf7f9447a
d0016d30:	b188fd40 	orrlt	pc, r8, r0, asr #26
d0016d34:	da0f2d00 	ble	0xd03e213c
d0016d38:	0f00f1bb 	svceq	0x0000f1bb
d0016d3c:	4620da0c 	strtmi	sp, [r0], -ip, lsl #20
d0016d40:	ff9af7fb 			; <UNDEFINED> instruction: 0xff9af7fb
d0016d44:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d0016d48:	e8bdb005 	pop	{r0, r2, ip, sp, pc}
d0016d4c:	f7fd4ff0 			; <UNDEFINED> instruction: 0xf7fd4ff0
d0016d50:	f04fba55 			; <UNDEFINED> instruction: 0xf04fba55
d0016d54:	e7e43bff 			; <UNDEFINED> instruction: 0xe7e43bff
d0016d58:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0016d5c:	2d00ff8d 	stccs	15, cr15, [r0, #-564]	; 0xfffffdcc
d0016d60:	232cdb1c 			; <UNDEFINED> instruction: 0x232cdb1c
d0016d64:	4305fb03 	movwmi	pc, #23299	; 0x5b03	; <UNPREDICTABLE>
d0016d68:	3313f503 	tstcc	r3, #12582912	; 0xc00000	; <UNPREDICTABLE>
d0016d6c:	230df893 	movwcs	pc, #55443	; 0xd893	; <UNPREDICTABLE>
d0016d70:	630ef893 	movwvs	pc, #59539	; 0xe893	; <UNPREDICTABLE>
d0016d74:	03fdf002 	mvnseq	pc, #2
d0016d78:	d1452b0d 	cmple	r5, sp, lsl #22
d0016d7c:	b9eb9b02 	stmiblt	fp!, {r1, r8, r9, fp, ip, pc}^
d0016d80:	b9436da3 	stmdblt	r3, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d0016d84:	447b4b5d 	ldrbtmi	r4, [fp], #-2909	; 0xfffff4a3
d0016d88:	9b0165a3 	blls	0xd007041c
d0016d8c:	a068f8c4 	rsbge	pc, r8, r4, asr #17
d0016d90:	e9c465e3 	stmib	r4, {r0, r1, r5, r6, r7, r8, sl, sp, lr}^
d0016d94:	b0058918 	andlt	r8, r5, r8, lsl r9
d0016d98:	8ff0e8bd 	svchi	0x00f0e8bd
d0016d9c:	0f00f1bb 	svceq	0x0000f1bb
d0016da0:	2334bfad 	teqcs	r4, #692	; 0x2b4
d0016da4:	26ff220b 	ldrbtcs	r2, [pc], fp, lsl #4
d0016da8:	430bfb03 	movwmi	pc, #47875	; 0xbb03	; <UNPREDICTABLE>
d0016dac:	f503bfa2 			; <UNDEFINED> instruction: 0xf503bfa2
d0016db0:	f89333af 			; <UNDEFINED> instruction: 0xf89333af
d0016db4:	f893202c 			; <UNDEFINED> instruction: 0xf893202c
d0016db8:	e7db602e 	ldrb	r6, [fp, lr, lsr #32]
d0016dbc:	db102d00 	blle	0xd04221c4
d0016dc0:	46204629 	strtmi	r4, [r0], -r9, lsr #12
d0016dc4:	fa6df7fd 	blx	0xd1b94dc0
d0016dc8:	4620212e 	strtmi	r2, [r0], -lr, lsr #2
d0016dcc:	ff6ff7fb 			; <UNDEFINED> instruction: 0xff6ff7fb
d0016dd0:	463ab190 			; <UNDEFINED> instruction: 0x463ab190
d0016dd4:	46204631 			; <UNDEFINED> instruction: 0x46204631
d0016dd8:	e8bdb005 	pop	{r0, r2, ip, sp, pc}
d0016ddc:	f7fd4ff0 			; <UNDEFINED> instruction: 0xf7fd4ff0
d0016de0:	4620bc9d 			; <UNDEFINED> instruction: 0x4620bc9d
d0016de4:	2101465a 	tstcs	r1, sl, asr r6
d0016de8:	fa7cf7fd 	blx	0xd1f54de4
d0016dec:	6108f244 	tstvs	r8, r4, asr #4	; <UNPREDICTABLE>
d0016df0:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0016df4:	e7e7f9a7 	strb	pc, [r7, r7, lsr #19]!	; <UNPREDICTABLE>
d0016df8:	d0cc42be 	strhle	r4, [ip], #46	; 0x2e
d0016dfc:	2b006da3 	blcs	0xd0032490
d0016e00:	4b3fd1c9 	blmi	0xd100b52c
d0016e04:	e7bf447b 			; <UNDEFINED> instruction: 0xe7bf447b
d0016e08:	0310f1a2 	tsteq	r0, #-2147483608	; 0x80000028	; <UNPREDICTABLE>
d0016e0c:	d83f2b01 	ldmdale	pc!, {r0, r8, r9, fp, sp}	; <UNPREDICTABLE>
d0016e10:	db0e2d00 	blle	0xd03a2218
d0016e14:	46204629 	strtmi	r4, [r0], -r9, lsr #12
d0016e18:	fa43f7fd 	blx	0xd1114e14
d0016e1c:	6ae39a02 	bvs	0xcf8fd62c
d0016e20:	2b5bb332 	blcs	0xd1703af0
d0016e24:	6da3d010 	stcvs	0, cr13, [r3, #64]!	; 0x40
d0016e28:	d1b42b00 			; <UNDEFINED> instruction: 0xd1b42b00
d0016e2c:	447b4b35 	ldrbtmi	r4, [fp], #-2869	; 0xfffff4cb
d0016e30:	4620e7aa 	strtmi	lr, [r0], -sl, lsr #15
d0016e34:	2101465a 	tstcs	r1, sl, asr r6
d0016e38:	fa54f7fd 	blx	0xd1554e34
d0016e3c:	6108f244 	tstvs	r8, r4, asr #4	; <UNPREDICTABLE>
d0016e40:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0016e44:	e7e9f97f 			; <UNDEFINED> instruction: 0xe7e9f97f
d0016e48:	23014631 	movwcs	r4, #5681	; 0x1631
d0016e4c:	46202200 	strtmi	r2, [r0], -r0, lsl #4
d0016e50:	fe92f7ff 	mrc2	7, 4, pc, cr2, cr15, {7}
d0016e54:	4620212e 	strtmi	r2, [r0], -lr, lsr #2
d0016e58:	ff29f7fb 			; <UNDEFINED> instruction: 0xff29f7fb
d0016e5c:	d1b82800 			; <UNDEFINED> instruction: 0xd1b82800
d0016e60:	d09842be 			; <UNDEFINED> instruction: 0xd09842be
d0016e64:	2b006da3 	blcs	0xd00324f8
d0016e68:	4b27d195 	blmi	0xd0a0b4c4
d0016e6c:	e78b447b 			; <UNDEFINED> instruction: 0xe78b447b
d0016e70:	d1052b5b 	tstle	r5, fp, asr fp
d0016e74:	2b006da3 	blcs	0xd0032508
d0016e78:	4b24d18d 	blmi	0xd094b4b4
d0016e7c:	e783447b 			; <UNDEFINED> instruction: 0xe783447b
d0016e80:	d08842be 			; <UNDEFINED> instruction: 0xd08842be
d0016e84:	2b006da3 	blcs	0xd0032518
d0016e88:	4b21d185 	blmi	0xd088b4a4
d0016e8c:	e77b447b 			; <UNDEFINED> instruction: 0xe77b447b
d0016e90:	d1142a0e 	tstle	r4, lr, lsl #20
d0016e94:	db122d00 	blle	0xd04a229c
d0016e98:	46204629 	strtmi	r4, [r0], -r9, lsr #12
d0016e9c:	fcccf7fd 	stc2l	7, cr15, [ip], {253}	; 0xfd
d0016ea0:	b32b9b02 			; <UNDEFINED> instruction: 0xb32b9b02
d0016ea4:	1121f240 	msrne	R9_usr, r0
d0016ea8:	ff01f7fb 			; <UNDEFINED> instruction: 0xff01f7fb
d0016eac:	d1902800 	orrsle	r2, r0, r0, lsl #16
d0016eb0:	2b006da3 	blcs	0xd0032544
d0016eb4:	af6ff47f 	svcge	0x006ff47f
d0016eb8:	447b4b16 	ldrbtmi	r4, [fp], #-2838	; 0xfffff4ea
d0016ebc:	6da3e764 	stcvs	7, cr14, [r3, #400]!	; 0x190
d0016ec0:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0016ec4:	4b14af68 	blmi	0xd0542c6c
d0016ec8:	e75d447b 			; <UNDEFINED> instruction: 0xe75d447b
d0016ecc:	b93a9a02 	ldmdblt	sl!, {r1, r9, fp, ip, pc}
d0016ed0:	7381f5a3 	orrvc	pc, r1, #683671552	; 0x28c00000
d0016ed4:	d8032b01 	stmdale	r3, {r0, r8, r9, fp, sp}
d0016ed8:	2b006a23 	blcs	0xd003176c
d0016edc:	af2ff43f 	svcge	0x002ff43f
d0016ee0:	4620490e 	strtmi	r4, [r0], -lr, lsl #18
d0016ee4:	b0054479 	andlt	r4, r5, r9, ror r4
d0016ee8:	4ff0e8bd 	svcmi	0x00f0e8bd
d0016eec:	b95cf7f9 	ldmdblt	ip, {r0, r3, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}^
d0016ef0:	d1dd42be 	ldrhle	r4, [sp, #46]	; 0x2e
d0016ef4:	bf00e74f 	svclt	0x0000e74f
d0016ef8:	ffffd4d4 			; <UNDEFINED> instruction: 0xffffd4d4
d0016efc:	fffffe92 			; <UNDEFINED> instruction: 0xfffffe92
d0016f00:	ffffd8e5 			; <UNDEFINED> instruction: 0xffffd8e5
d0016f04:	fffffe0f 			; <UNDEFINED> instruction: 0xfffffe0f
d0016f08:	ffffd87d 			; <UNDEFINED> instruction: 0xffffd87d
d0016f0c:	fffffdeb 			; <UNDEFINED> instruction: 0xfffffdeb
d0016f10:	ffffd85d 			; <UNDEFINED> instruction: 0xffffd85d
d0016f14:	ffffd82f 			; <UNDEFINED> instruction: 0xffffd82f
d0016f18:	ffffd821 			; <UNDEFINED> instruction: 0xffffd821
d0016f1c:	fffffdad 			; <UNDEFINED> instruction: 0xfffffdad

Disassembly of section .text.int_pointer_element:

d0016f64 <.text.int_pointer_element>:
d0016f64:	4615b570 			; <UNDEFINED> instruction: 0x4615b570
d0016f68:	460e4a24 	strmi	r4, [lr], -r4, lsr #20
d0016f6c:	447a215b 	ldrbtmi	r2, [sl], #-347	; 0xfffffea5
d0016f70:	f7fb4604 			; <UNDEFINED> instruction: 0xf7fb4604
d0016f74:	b910feaa 	ldmdblt	r0, {r1, r3, r5, r7, r9, sl, fp, ip, sp, lr, pc}
d0016f78:	46282500 	strtmi	r2, [r8], -r0, lsl #10
d0016f7c:	f24bbd70 	vmla.f32	<illegal reg q13.5>, <illegal reg q5.5>, q8
d0016f80:	46204103 	strtmi	r4, [r0], -r3, lsl #2
d0016f84:	f8def7fd 			; <UNDEFINED> instruction: 0xf8def7fd
d0016f88:	46112201 	ldrmi	r2, [r1], -r1, lsl #4
d0016f8c:	fa76f7ff 	blx	0xd1dd4f90
d0016f90:	215d4a1b 	cmpcs	sp, fp, lsl sl
d0016f94:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d0016f98:	fe97f7fb 	mrc2	7, 4, pc, cr7, cr11, {7}
d0016f9c:	d0eb2800 	rscle	r2, fp, r0, lsl #16
d0016fa0:	4106f64b 	tstmi	r6, fp, asr #12	; <UNPREDICTABLE>
d0016fa4:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0016fa8:	2180f8cd 	orrcs	pc, r0, sp, asr #17
d0016fac:	f8caf7fd 			; <UNDEFINED> instruction: 0xf8caf7fd
d0016fb0:	0108f641 	tsteq	r8, r1, asr #12	; <UNPREDICTABLE>
d0016fb4:	f8c6f7fd 			; <UNDEFINED> instruction: 0xf8c6f7fd
d0016fb8:	b1beb9f5 			; <UNDEFINED> instruction: 0xb1beb9f5
d0016fbc:	f7fb213d 			; <UNDEFINED> instruction: 0xf7fb213d
d0016fc0:	b198fe76 	orrslt	pc, r8, r6, ror lr	; <UNPREDICTABLE>
d0016fc4:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d0016fc8:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0016fcc:	2201f8bb 	andcs	pc, r1, #12255232	; 0xbb0000
d0016fd0:	46112502 	ldrmi	r2, [r1], -r2, lsl #10
d0016fd4:	fa52f7ff 	blx	0xd14d4fd8
d0016fd8:	4106f64b 	tstmi	r6, fp, asr #12	; <UNPREDICTABLE>
d0016fdc:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0016fe0:	f246f8b1 	vtst.8	d31, d22, d17
d0016fe4:	f7fd0108 			; <UNDEFINED> instruction: 0xf7fd0108
d0016fe8:	e7c6f8ad 	strb	pc, [r6, sp, lsr #17]	; <UNPREDICTABLE>
d0016fec:	41d0f44f 	bicsmi	pc, r0, pc, asr #8
d0016ff0:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0016ff4:	e7c0f8a7 	strb	pc, [r0, r7, lsr #17]	; <UNPREDICTABLE>
d0016ff8:	e7be2504 	ldr	r2, [lr, r4, lsl #10]!
d0016ffc:	ffffffae 			; <UNDEFINED> instruction: 0xffffffae
d0017000:	ffffffaa 			; <UNDEFINED> instruction: 0xffffffaa

Disassembly of section .text.indirect_call:

d0017068 <.text.indirect_call>:
d0017068:	fb03232c 	blx	0xd00dfd22
d001706c:	e92d0301 	push	{r0, r8, r9}
d0017070:	f50341f0 			; <UNDEFINED> instruction: 0xf50341f0
d0017074:	f8df3313 			; <UNDEFINED> instruction: 0xf8df3313
d0017078:	4604809c 			; <UNDEFINED> instruction: 0x4604809c
d001707c:	f893460d 			; <UNDEFINED> instruction: 0xf893460d
d0017080:	2600730f 	strcs	r7, [r0], -pc, lsl #6
d0017084:	42be44f8 	adcsmi	r4, lr, #248, 8	; 0xf8000000
d0017088:	6da3d201 	sfmvs	f5, 1, [r3, #4]!
d001708c:	4639b363 	ldrtmi	fp, [r9], -r3, ror #6
d0017090:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0017094:	4a20fa20 	bmi	0xd085591c
d0017098:	21294606 			; <UNDEFINED> instruction: 0x21294606
d001709c:	4620447a 			; <UNDEFINED> instruction: 0x4620447a
d00170a0:	fe13f7fb 	mrc2	7, 0, pc, cr3, cr11, {7}
d00170a4:	f64fb1e8 			; <UNDEFINED> instruction: 0xf64fb1e8
d00170a8:	462001d7 			; <UNDEFINED> instruction: 0x462001d7
d00170ac:	f84af7fd 			; <UNDEFINED> instruction: 0xf84af7fd
d00170b0:	ea414917 	b	0xd1069514
d00170b4:	b2890185 	addlt	r0, r9, #1073741857	; 0x40000021
d00170b8:	f844f7fd 			; <UNDEFINED> instruction: 0xf844f7fd
d00170bc:	71e0f244 	mvnvc	pc, r4, asr #4
d00170c0:	f840f7fd 			; <UNDEFINED> instruction: 0xf840f7fd
d00170c4:	f446b126 	vst4.8	{d27,d29,d31,d33}, [r6 :128], r6
d00170c8:	b2894130 	addlt	r4, r9, #48, 2
d00170cc:	f83af7fd 			; <UNDEFINED> instruction: 0xf83af7fd
d00170d0:	fb00202c 	blx	0xd001f18a
d00170d4:	f5044405 			; <UNDEFINED> instruction: 0xf5044405
d00170d8:	f8943413 			; <UNDEFINED> instruction: 0xf8943413
d00170dc:	2b013310 	blcs	0xd0063d24
d00170e0:	2000d014 	andcs	sp, r0, r4, lsl r0
d00170e4:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d00170e8:	4642b126 	strbmi	fp, [r2], -r6, lsr #2
d00170ec:	4620212c 	strtmi	r2, [r0], -ip, lsr #2
d00170f0:	fdebf7fb 	stc2l	7, cr15, [fp, #1004]!	; 0x3ec
d00170f4:	46202201 	strtmi	r2, [r0], -r1, lsl #4
d00170f8:	46113601 	ldrmi	r3, [r1], -r1, lsl #12
d00170fc:	f9bef7ff 			; <UNDEFINED> instruction: 0xf9bef7ff
d0017100:	4103f24b 	tstmi	r3, fp, asr #4	; <UNPREDICTABLE>
d0017104:	f7fd4620 			; <UNDEFINED> instruction: 0xf7fd4620
d0017108:	e7bcf81d 			; <UNDEFINED> instruction: 0xe7bcf81d
d001710c:	e7e92002 	strb	r2, [r9, r2]!
d0017110:	ffffc000 			; <UNDEFINED> instruction: 0xffffc000
d0017114:	ffffff7c 			; <UNDEFINED> instruction: 0xffffff7c
d0017118:	ffffff94 			; <UNDEFINED> instruction: 0xffffff94

Disassembly of section .text.condition.constprop.0:

d0017158 <.text.condition.constprop.0>:
d0017158:	4c0ab510 	cfstr32mi	mvfx11, [sl], {16}
d001715c:	4a0a2128 	bmi	0xd029f604
d0017160:	447a447c 	ldrbtmi	r4, [sl], #-1148	; 0xfffffb84
d0017164:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0017168:	2202fdb0 	andcs	pc, r2, #176, 26	; 0x2c00
d001716c:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d0017170:	f984f7ff 			; <UNDEFINED> instruction: 0xf984f7ff
d0017174:	46204a05 	strtmi	r4, [r0], -r5, lsl #20
d0017178:	447a2129 	ldrbtmi	r2, [sl], #-297	; 0xfffffed7
d001717c:	4010e8bd 			; <UNDEFINED> instruction: 0x4010e8bd
d0017180:	bda3f7fb 	stclt	7, cr15, [r3, #1004]!	; 0x3ec
d0017184:	00007c94 	muleq	r0, r4, ip
d0017188:	ffffffb6 			; <UNDEFINED> instruction: 0xffffffb6
d001718c:	ffffffbc 			; <UNDEFINED> instruction: 0xffffffbc

Disassembly of section .text.simple_expression.constprop.0:

d0017268 <.text.simple_expression.constprop.0>:
d0017268:	447b4b8e 	ldrbtmi	r4, [fp], #-2958	; 0xfffff472
d001726c:	4ff0e92d 	svcmi	0x00f0e92d
d0017270:	b0856cde 	ldrdlt	r6, [r5], lr
d0017274:	d0162e3d 	andsle	r2, r6, sp, lsr lr
d0017278:	7692f5a6 	ldrvc	pc, [r2], r6, lsr #11
d001727c:	bf8c2e01 	svclt	0x008c2e01
d0017280:	26012600 	strcs	r2, [r1], -r0, lsl #12
d0017284:	f2404c88 			; <UNDEFINED> instruction: 0xf2404c88
d0017288:	447c1301 	ldrbtmi	r1, [ip], #-769	; 0xfffffcff
d001728c:	429a6ae2 	addsmi	r6, sl, #925696	; 0xe2000
d0017290:	b956d100 	ldmdblt	r6, {r8, ip, lr, pc}^
d0017294:	22034885 	andcs	r4, r3, #8716288	; 0x850000
d0017298:	44782101 	ldrbtmi	r2, [r8], #-257	; 0xfffffeff
d001729c:	e8bdb005 	pop	{r0, r2, ip, sp, pc}
d00172a0:	f7ff4ff0 			; <UNDEFINED> instruction: 0xf7ff4ff0
d00172a4:	2601b8eb 	strcs	fp, [r1], -fp, ror #17
d00172a8:	6a63e7ec 	bvs	0xd1911260
d00172ac:	f8d44620 			; <UNDEFINED> instruction: 0xf8d44620
d00172b0:	93009028 	movwls	r9, #40	; 0x28
d00172b4:	f8946b63 			; <UNDEFINED> instruction: 0xf8946b63
d00172b8:	9303a030 	movwls	sl, #12336	; 0x3030
d00172bc:	1206e9d4 	andne	lr, r6, #212, 18	; 0x350000
d00172c0:	91019202 	tstls	r1, r2, lsl #4
d00172c4:	f9c5f7f9 			; <UNDEFINED> instruction: 0xf9c5f7f9
d00172c8:	1e05a901 	vmlane.f16	s20, s10, s2	; <UNPREDICTABLE>
d00172cc:	f280c90e 	vqdmlal.s<illegal width 8>	q6, d0, d14
d00172d0:	462080de 			; <UNDEFINED> instruction: 0x462080de
d00172d4:	f7f99301 			; <UNDEFINED> instruction: 0xf7f99301
d00172d8:	f1b0f9dc 			; <UNDEFINED> instruction: 0xf1b0f9dc
d00172dc:	9b010800 	blls	0xd00592e4
d00172e0:	2234db1d 	eorscs	sp, r4, #29696	; 0x7400
d00172e4:	4408fb02 	strmi	pc, [r8], #-2818	; 0xfffff4fe
d00172e8:	34aff504 	strtcc	pc, [pc], #1284	; 0xd00172f0
d00172ec:	702cf894 	mlavc	ip, r4, r8, pc	; <UNPREDICTABLE>
d00172f0:	290a1ff9 	stmdbcs	sl, {r0, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
d00172f4:	f240d804 	vadd.i8	d29, d0, d4
d00172f8:	40ca7247 	sbcmi	r7, sl, r7, asr #4
d00172fc:	d41907d1 	ldrle	r0, [r9], #-2001	; 0xfffff82f
d0017300:	29091eb9 	stmdbcs	r9, {r0, r3, r4, r5, r7, r9, sl, fp, ip}
d0017304:	f240d825 	vadd.i8	d29, d0, d21
d0017308:	40ca2215 	sbcmi	r2, sl, r5, lsl r2
d001730c:	d52007d2 	strle	r0, [r0, #-2002]!	; 0xfffff82e
d0017310:	447a4a67 	ldrbtmi	r4, [sl], #-2663	; 0xfffff599
d0017314:	b9c96d91 	stmiblt	r9, {r0, r4, r7, r8, sl, fp, sp, lr}^
d0017318:	44794966 	ldrbtmi	r4, [r9], #-2406	; 0xfffff69a
d001731c:	6da2e010 	stcvs	0, cr14, [r2, #64]!	; 0x40
d0017320:	4a65b9a2 	bmi	0xd19859b0
d0017324:	65a2447a 	strvs	r4, [r2, #1146]!	; 0x47a
d0017328:	66a39a00 	strtvs	r9, [r3], r0, lsl #20
d001732c:	e9c465e2 	stmib	r4, {r1, r5, r6, r7, r8, sl, sp, lr}^
d0017330:	e00b9a18 	and	r9, fp, r8, lsl sl
d0017334:	447a4a61 	ldrbtmi	r4, [sl], #-2657	; 0xfffff59f
d0017338:	b9396d91 	ldmdblt	r9!, {r0, r4, r7, r8, sl, fp, sp, lr}
d001733c:	44794960 	ldrbtmi	r4, [r9], #-2400	; 0xfffff6a0
d0017340:	99006591 	stmdbls	r0, {r0, r4, r7, r8, sl, sp, lr}
d0017344:	65d16693 	ldrbvs	r6, [r1, #1683]	; 0x693
d0017348:	9a18e9c2 	bls	0xd0651a58
d001734c:	e8bdb005 	pop	{r0, r2, ip, sp, pc}
d0017350:	4c5c8ff0 	mrrcmi	15, 15, r8, ip, cr0
d0017354:	447c9301 	ldrbtmi	r9, [ip], #-769	; 0xfffffcff
d0017358:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d001735c:	4620fc8d 	strtmi	pc, [r0], -sp, lsl #25
d0017360:	b02cf8d4 	ldrdlt	pc, [ip], -r4	; <UNPREDICTABLE>
d0017364:	fc88f7fb 	stc2	7, cr15, [r8], {251}	; 0xfb
d0017368:	9b012f0c 	blls	0xd0062fa0
d001736c:	f1bbd119 			; <UNDEFINED> instruction: 0xf1bbd119
d0017370:	d0050f3d 	andle	r0, r5, sp, lsr pc
d0017374:	2a006da2 	bcs	0xd0032a04
d0017378:	4a53d1e8 	bmi	0xd150bb20
d001737c:	e7d2447a 			; <UNDEFINED> instruction: 0xe7d2447a
d0017380:	fb00202c 	blx	0xd001f43a
d0017384:	f5004005 			; <UNDEFINED> instruction: 0xf5004005
d0017388:	f2003013 	vqadd.s8	d3, d0, d3
d001738c:	f7fd300f 			; <UNDEFINED> instruction: 0xf7fd300f
d0017390:	2200fab1 	andcs	pc, r0, #724992	; 0xb1000
d0017394:	46204629 	strtmi	r4, [r0], -r9, lsr #12
d0017398:	e8bdb005 	pop	{r0, r2, ip, sp, pc}
d001739c:	f7fc4ff0 			; <UNDEFINED> instruction: 0xf7fc4ff0
d00173a0:	2f0ebf67 	svccs	0x000ebf67
d00173a4:	f1bbd113 			; <UNDEFINED> instruction: 0xf1bbd113
d00173a8:	d0050f3d 	andle	r0, r5, sp, lsr pc
d00173ac:	2a006da2 	bcs	0xd0032a3c
d00173b0:	4a46d1cc 	bmi	0xd11cbae8
d00173b4:	e7b6447a 			; <UNDEFINED> instruction: 0xe7b6447a
d00173b8:	4620232c 	strtmi	r2, [r0], -ip, lsr #6
d00173bc:	4305fb03 	movwmi	pc, #23299	; 0x5b03	; <UNPREDICTABLE>
d00173c0:	3313f503 	tstcc	r3, #12582912	; 0xc00000	; <UNPREDICTABLE>
d00173c4:	130ef893 	movwne	pc, #59539	; 0xe893	; <UNPREDICTABLE>
d00173c8:	fc82f7ff 	stc2	7, cr15, [r2], {255}	; 0xff
d00173cc:	f5abe7e1 			; <UNDEFINED> instruction: 0xf5abe7e1
d00173d0:	f1b97992 			; <UNDEFINED> instruction: 0xf1b97992
d00173d4:	d80b0f01 	stmdale	fp, {r0, r8, r9, sl, fp}
d00173d8:	db3e2d00 	blle	0xd0fa27e0
d00173dc:	46204629 	strtmi	r4, [r0], -r9, lsr #12
d00173e0:	fa2af7fd 	blx	0xd0ad53dc
d00173e4:	f24b483a 	vtst.8	d20, d11, d26
d00173e8:	44784103 	ldrbtmi	r4, [r8], #-259	; 0xfffffefd
d00173ec:	feaaf7fc 	mcr2	7, 5, pc, cr10, cr12, {7}	; <UNPREDICTABLE>
d00173f0:	d1032f0a 	tstle	r3, sl, lsl #30
d00173f4:	0f3df1bb 	svceq	0x003df1bb
d00173f8:	2604bf08 	strcs	fp, [r4], -r8, lsl #30
d00173fc:	46324c35 			; <UNDEFINED> instruction: 0x46324c35
d0017400:	447c2101 	ldrbtmi	r2, [ip], #-257	; 0xfffffeff
d0017404:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d0017408:	f1b9f839 			; <UNDEFINED> instruction: 0xf1b9f839
d001740c:	d8150f01 	ldmdale	r5, {r0, r8, r9, sl, fp}
d0017410:	4106f64b 	tstmi	r6, fp, asr #12	; <UNPREDICTABLE>
d0017414:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0017418:	2f0afe95 	svccs	0x000afe95
d001741c:	2180d102 	orrcs	sp, r0, r2, lsl #2
d0017420:	fe90f7fc 	mrc2	7, 4, pc, cr0, cr12, {7}
d0017424:	0108f641 	tsteq	r8, r1, asr #12	; <UNPREDICTABLE>
d0017428:	2308f641 	movwcs	pc, #34369	; 0x8641	; <UNPREDICTABLE>
d001742c:	f5bb482a 			; <UNDEFINED> instruction: 0xf5bb482a
d0017430:	bf187f92 	svclt	0x00187f92
d0017434:	44784619 	ldrbtmi	r4, [r8], #-1561	; 0xfffff9e7
d0017438:	fe84f7fc 	mcr2	7, 4, pc, cr4, cr12, {7}	; <UNPREDICTABLE>
d001743c:	d1052f05 	tstle	r5, r5, lsl #30
d0017440:	f24b4826 	vadd.i8	d20, d11, d22
d0017444:	447821c0 	ldrbtmi	r2, [r8], #-448	; 0xfffffe40
d0017448:	fe7cf7fc 	mrc2	7, 3, pc, cr12, cr12, {7}
d001744c:	db0f2d00 	blle	0xd03e2854
d0017450:	22004823 	andcs	r4, r0, #2293760	; 0x230000
d0017454:	44784629 	ldrbtmi	r4, [r8], #-1577	; 0xfffff9d7
d0017458:	4620e79e 			; <UNDEFINED> instruction: 0x4620e79e
d001745c:	21014642 	tstcs	r1, r2, asr #12
d0017460:	ff40f7fc 			; <UNDEFINED> instruction: 0xff40f7fc
d0017464:	0108f646 	tsteq	r8, r6, asr #12	; <UNPREDICTABLE>
d0017468:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d001746c:	e7b9fe6b 	ldr	pc, [r9, fp, ror #28]!
d0017470:	4642481c 			; <UNDEFINED> instruction: 0x4642481c
d0017474:	44782101 	ldrbtmi	r2, [r8], #-257	; 0xfffffeff
d0017478:	f7fc9000 			; <UNDEFINED> instruction: 0xf7fc9000
d001747c:	f246ff33 	vrecps.f32	d31, d6, d19
d0017480:	98000108 	stmdals	r0, {r3, r8}
d0017484:	e8bdb005 	pop	{r0, r2, ip, sp, pc}
d0017488:	f7fc4ff0 			; <UNDEFINED> instruction: 0xf7fc4ff0
d001748c:	222cbe5b 	eorcs	fp, ip, #1456	; 0x5b0
d0017490:	38fff04f 	ldmcc	pc!, {r0, r1, r2, r3, r6, ip, sp, lr, pc}^	; <UNPREDICTABLE>
d0017494:	4405fb02 	strmi	pc, [r5], #-2818	; 0xfffff4fe
d0017498:	3413f504 	ldrcc	pc, [r3], #-1284	; 0xfffffafc
d001749c:	730df894 	movwvc	pc, #55444	; 0xd894	; <UNPREDICTABLE>
d00174a0:	bf00e726 	svclt	0x0000e726
d00174a4:	00007b8a 	andeq	r7, r0, sl, lsl #23
d00174a8:	00007b6a 	andeq	r7, r0, sl, ror #22
d00174ac:	00007b5a 	andeq	r7, r0, sl, asr fp
d00174b0:	00007ae2 	andeq	r7, r0, r2, ror #21
d00174b4:	fffffebd 			; <UNDEFINED> instruction: 0xfffffebd
d00174b8:	fffffe68 			; <UNDEFINED> instruction: 0xfffffe68
d00174bc:	00007abe 			; <UNDEFINED> instruction: 0x00007abe
d00174c0:	fffffe73 			; <UNDEFINED> instruction: 0xfffffe73
d00174c4:	00007a9e 	muleq	r0, lr, sl
d00174c8:	fffffe87 			; <UNDEFINED> instruction: 0xfffffe87
d00174cc:	fffffe80 			; <UNDEFINED> instruction: 0xfffffe80
d00174d0:	00007a0a 	andeq	r7, r0, sl, lsl #20
d00174d4:	000079f2 	strdeq	r7, [r0], -r2
d00174d8:	000079be 			; <UNDEFINED> instruction: 0x000079be
d00174dc:	000079ae 	andeq	r7, r0, lr, lsr #19
d00174e0:	0000799e 	muleq	r0, lr, r9
d00174e4:	0000797e 	andeq	r7, r0, lr, ror r9

Disassembly of section .text.initialize_scalar.constprop.0:

d0017548 <.text.initialize_scalar.constprop.0>:
d0017548:	4ff0e92d 	svcmi	0x00f0e92d
d001754c:	4607b087 	strmi	fp, [r7], -r7, lsl #1
d0017550:	9203460e 	andls	r4, r3, #14680064	; 0xe00000
d0017554:	4c31b971 			; <UNDEFINED> instruction: 0x4c31b971
d0017558:	447c2201 	ldrbtmi	r2, [ip], #-513	; 0xfffffdff
d001755c:	46204611 			; <UNDEFINED> instruction: 0x46204611
d0017560:	ff8cf7fe 			; <UNDEFINED> instruction: 0xff8cf7fe
d0017564:	46394632 			; <UNDEFINED> instruction: 0x46394632
d0017568:	b0074620 	andlt	r4, r7, r0, lsr #12
d001756c:	4ff0e8bd 	svcmi	0x00f0e8bd
d0017570:	be7ef7fc 	mrclt	7, 3, APSR_nzcv, cr14, cr12, {7}
d0017574:	212d4c2a 			; <UNDEFINED> instruction: 0x212d4c2a
d0017578:	4620447c 			; <UNDEFINED> instruction: 0x4620447c
d001757c:	fb97f7fb 	blx	0xce615572
d0017580:	69e269a3 	stmibvs	r2!, {r0, r1, r5, r7, r8, fp, sp, lr}^
d0017584:	718df44f 	orrvc	pc, sp, pc, asr #8
d0017588:	6b639305 	blvs	0xd18fc1a4
d001758c:	46209002 	strtmi	r9, [r0], -r2
d0017590:	93019204 	movwls	r9, #4612	; 0x1204
d0017594:	9030f894 	mlasls	r0, r4, r8, pc	; <UNPREDICTABLE>
d0017598:	5b08e9d4 	blpl	0xd0251cf0
d001759c:	a80ae9d4 	stmdage	sl, {r2, r4, r6, r7, r8, fp, sp, lr, pc}
d00175a0:	fb85f7fb 	blx	0xce195596
d00175a4:	9b059a04 	blls	0xd017ddbc
d00175a8:	4620b188 	strtmi	fp, [r0], -r8, lsl #3
d00175ac:	fd20f7fb 	stc2	7, cr15, [r0, #-1004]!	; 0xfffffc14
d00175b0:	9b024605 	blls	0xd00a8dcc
d00175b4:	426db103 	rsbmi	fp, sp, #-1073741824	; 0xc0000000
d00175b8:	b3639b03 	cmnlt	r3, #3072	; 0xc00
d00175bc:	d92a2dff 	stmdble	sl!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, sl, fp, sp}
d00175c0:	447b4b18 	ldrbtmi	r4, [fp], #-2840	; 0xfffff4e8
d00175c4:	b9ba6d9a 	ldmiblt	sl!, {r1, r3, r4, r7, r8, sl, fp, sp, lr}
d00175c8:	447a4a17 	ldrbtmi	r4, [sl], #-2583	; 0xfffff5e9
d00175cc:	f240e00e 	vhadd.s8	d30, d0, d14
d00175d0:	45881101 	strmi	r1, [r8, #257]	; 0x101
d00175d4:	4619d113 			; <UNDEFINED> instruction: 0x4619d113
d00175d8:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d00175dc:	b9c0f8ff 	stmiblt	r0, {r0, r1, r2, r3, r4, r5, r6, r7, fp, ip, sp, lr, pc}^
d00175e0:	447b4b12 	ldrbtmi	r4, [fp], #-2834	; 0xfffff4ee
d00175e4:	b93a6d9a 	ldmdblt	sl!, {r1, r3, r4, r7, r8, sl, fp, sp, lr}
d00175e8:	447a4a11 	ldrbtmi	r4, [sl], #-2577	; 0xfffff5ef
d00175ec:	2b16e9c3 	blcs	0xd05d1d00
d00175f0:	e9c39a01 	stmib	r3, {r0, r9, fp, ip, pc}^
d00175f4:	669aa918 			; <UNDEFINED> instruction: 0x669aa918
d00175f8:	e8bdb007 	pop	{r0, r1, r2, ip, sp, pc}
d00175fc:	f5a88ff0 			; <UNDEFINED> instruction: 0xf5a88ff0
d0017600:	f1b87881 			; <UNDEFINED> instruction: 0xf1b87881
d0017604:	d8eb0f01 	stmiale	fp!, {r0, r8, r9, sl, fp}^
d0017608:	4478480a 	ldrbtmi	r4, [r8], #-2058	; 0xfffff7f6
d001760c:	fb34f7fb 	blx	0xd0d55602
d0017610:	6a05e7cf 	bvs	0xd0191554
d0017614:	f846e7f8 			; <UNDEFINED> instruction: 0xf846e7f8
d0017618:	e7ed5027 	strb	r5, [sp, r7, lsr #32]!
d001761c:	0000789a 	muleq	r0, sl, r8
d0017620:	0000787c 	andeq	r7, r0, ip, ror r8
d0017624:	00007832 	andeq	r7, r0, r2, lsr r8
d0017628:	ffffff51 			; <UNDEFINED> instruction: 0xffffff51
d001762c:	00007812 	andeq	r7, r0, r2, lsl r8
d0017630:	fffffefa 			; <UNDEFINED> instruction: 0xfffffefa
d0017634:	000077ea 	andeq	r7, r0, sl, ror #15

Disassembly of section .text.initialize_record.constprop.0:

d0017700 <.text.initialize_record.constprop.0>:
d0017700:	e92d2b21 	push	{r0, r5, r8, r9, fp, sp}
d0017704:	46064ff8 			; <UNDEFINED> instruction: 0x46064ff8
d0017708:	4690468b 	ldrmi	r4, [r0], fp, lsl #13
d001770c:	d1074699 			; <UNDEFINED> instruction: 0xd1074699
d0017710:	48374936 	ldmdami	r7!, {r1, r2, r4, r5, r8, fp, lr}
d0017714:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d0017718:	4ff8e8bd 	svcmi	0x00f8e8bd
d001771c:	bd44f7f8 	stcllt	7, cr15, [r4, #-992]	; 0xfffffc20
d0017720:	217b4c34 	cmncs	fp, r4, lsr ip
d0017724:	447c4a34 	ldrbtmi	r4, [ip], #-2612	; 0xfffff5cc
d0017728:	4620447a 			; <UNDEFINED> instruction: 0x4620447a
d001772c:	facdf7fb 	blx	0xcf395720
d0017730:	d0592800 	subsle	r2, r9, r0, lsl #16
d0017734:	731af44f 	tstvc	sl, #1325400064	; 0x4f000000	; <UNPREDICTABLE>
d0017738:	435e2700 	cmpmi	lr, #0, 14
d001773c:	0a04eb06 	beq	0xd015235c
d0017740:	bb736da3 	bllt	0xd1cf2dd4
d0017744:	2d7d6ae5 	vldmdbcs	sp!, {s13-s241}
d0017748:	f5b5d02b 			; <UNDEFINED> instruction: 0xf5b5d02b
d001774c:	d0287f80 	eorle	r7, r8, r0, lsl #31
d0017750:	f50319a3 			; <UNDEFINED> instruction: 0xf50319a3
d0017754:	f89333bd 			; <UNDEFINED> instruction: 0xf89333bd
d0017758:	42ba206a 	adcsmi	r2, sl, #106	; 0x6a
d001775c:	f893d903 			; <UNDEFINED> instruction: 0xf893d903
d0017760:	b12b306b 			; <UNDEFINED> instruction: 0xb12b306b
d0017764:	4925b127 	stmdbmi	r5!, {r0, r1, r2, r5, r8, ip, sp, pc}
d0017768:	44794825 	ldrbtmi	r4, [r9], #-2085	; 0xfffff7db
d001776c:	e7d34478 			; <UNDEFINED> instruction: 0xe7d34478
d0017770:	33bcf50a 			; <UNDEFINED> instruction: 0x33bcf50a
d0017774:	c048f893 	umaalgt	pc, r8, r3, r8	; <UNPREDICTABLE>
d0017778:	f1bc3328 			; <UNDEFINED> instruction: 0xf1bc3328
d001777c:	8c5b0fff 	mrrchi	15, 15, r0, fp, cr15
d0017780:	000beb03 	andeq	lr, fp, r3, lsl #22
d0017784:	2200d116 	andcs	sp, r0, #-2147483643	; 0x80000005
d0017788:	f7ff4641 			; <UNDEFINED> instruction: 0xf7ff4641
d001778c:	481dfedd 	ldmdami	sp, {r0, r2, r3, r4, r6, r7, r9, sl, fp, ip, sp, lr, pc}
d0017790:	3701212c 	strcc	r2, [r1, -ip, lsr #2]
d0017794:	0a24f10a 	beq	0xd0953bc4
d0017798:	f7fb4478 			; <UNDEFINED> instruction: 0xf7fb4478
d001779c:	2800fa88 	stmdacs	r0, {r3, r7, r9, fp, ip, sp, lr, pc}
d00177a0:	4a19d1ce 	bmi	0xd068bee0
d00177a4:	4819217d 	ldmdami	r9, {r0, r2, r3, r4, r5, r6, r8, sp}
d00177a8:	4478447a 	ldrbtmi	r4, [r8], #-1146	; 0xfffffb86
d00177ac:	4ff8e8bd 	svcmi	0x00f8e8bd
d00177b0:	ba8bf7fb 	blt	0xce3157a4
d00177b4:	d1072d7b 	tstle	r7, fp, ror sp
d00177b8:	f1094601 			; <UNDEFINED> instruction: 0xf1094601
d00177bc:	46420301 	strbmi	r0, [r2], -r1, lsl #6
d00177c0:	f7ff4660 			; <UNDEFINED> instruction: 0xf7ff4660
d00177c4:	e7e2ff9d 			; <UNDEFINED> instruction: 0xe7e2ff9d
d00177c8:	7581f5a5 	strvc	pc, [r1, #1445]	; 0x5a5
d00177cc:	d8062d01 	stmdale	r6, {r0, r8, sl, fp, sp}
d00177d0:	4478480f 	ldrbtmi	r4, [r8], #-2063	; 0xfffff7f1
d00177d4:	b9136a03 	ldmdblt	r3, {r0, r1, r9, fp, sp, lr}
d00177d8:	fa4ef7fb 	blx	0xd13d57cc
d00177dc:	490de7d7 	stmdbmi	sp, {r0, r1, r2, r4, r6, r7, r8, r9, sl, sp, lr, pc}
d00177e0:	4479480d 	ldrbtmi	r4, [r9], #-2061	; 0xfffff7f3
d00177e4:	e7974478 			; <UNDEFINED> instruction: 0xe7974478
d00177e8:	8ff8e8bd 	svchi	0x00f8e8bd
d00177ec:	ffffff20 			; <UNDEFINED> instruction: 0xffffff20
d00177f0:	000076de 	ldrdeq	r7, [r0], -lr
d00177f4:	000076ce 	andeq	r7, r0, lr, asr #13
d00177f8:	ffffff2c 			; <UNDEFINED> instruction: 0xffffff2c
d00177fc:	ffffff0e 			; <UNDEFINED> instruction: 0xffffff0e
d0017800:	00007688 	andeq	r7, r0, r8, lsl #13
d0017804:	0000765c 	andeq	r7, r0, ip, asr r6
d0017808:	ffffff2b 			; <UNDEFINED> instruction: 0xffffff2b
d001780c:	0000764a 	andeq	r7, r0, sl, asr #12
d0017810:	00007622 	andeq	r7, r0, r2, lsr #12
d0017814:	fffffec0 			; <UNDEFINED> instruction: 0xfffffec0
d0017818:	00007610 	andeq	r7, r0, r0, lsl r6

Disassembly of section .text.initialize_array.constprop.0:

d00178b4 <.text.initialize_array.constprop.0>:
d00178b4:	4ff7e92d 	svcmi	0x00f7e92d
d00178b8:	46154e36 			; <UNDEFINED> instruction: 0x46154e36
d00178bc:	460c4a36 			; <UNDEFINED> instruction: 0x460c4a36
d00178c0:	9001447e 	andls	r4, r1, lr, ror r4
d00178c4:	217b447a 	cmncs	fp, sl, ror r4
d00178c8:	461f4630 			; <UNDEFINED> instruction: 0x461f4630
d00178cc:	a030f8dd 	ldrsbtge	pc, [r0], -sp	; <UNPREDICTABLE>
d00178d0:	f9fbf7fb 			; <UNDEFINED> instruction: 0xf9fbf7fb
d00178d4:	d05a2800 	subsle	r2, sl, r0, lsl #16
d00178d8:	f8df2cff 			; <UNDEFINED> instruction: 0xf8df2cff
d00178dc:	f04fb0c0 			; <UNDEFINED> instruction: 0xf04fb0c0
d00178e0:	bf140800 	svclt	0x00140800
d00178e4:	701af44f 	andsvc	pc, sl, pc, asr #8
d00178e8:	0901f04f 	stmdbeq	r1, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d00178ec:	bf1844fb 	svclt	0x001844fb
d00178f0:	6004fb00 	andvs	pc, r4, r0, lsl #22
d00178f4:	bf184e2a 	svclt	0x00184e2a
d00178f8:	30bdf500 	adcscc	pc, sp, r0, lsl #10
d00178fc:	bf18447e 	svclt	0x0018447e
d0017900:	9068f8b0 	strhtls	pc, [r8], #-128	; 0xffffff80	; <UNPREDICTABLE>
d0017904:	bb036db3 	bllt	0xd00f2fd8
d0017908:	2b7d6af3 	blcs	0xd1f724dc
d001790c:	f5b3d01d 			; <UNDEFINED> instruction: 0xf5b3d01d
d0017910:	d01a7f80 	andsle	r7, sl, r0, lsl #31
d0017914:	45429a01 	strbmi	r9, [r2, #-2561]	; 0xfffff5ff
d0017918:	4922d107 	stmdbmi	r2!, {r0, r1, r2, r8, ip, lr, pc}
d001791c:	44794630 	ldrbtmi	r4, [r9], #-1584	; 0xfffff9d0
d0017920:	e8bdb003 	pop	{r0, r1, ip, sp, pc}
d0017924:	f7f84ff0 			; <UNDEFINED> instruction: 0xf7f84ff0
d0017928:	2cffbc3f 	ldclcs	12, cr11, [pc], #252	; 0xd0017a2c
d001792c:	4652d117 			; <UNDEFINED> instruction: 0x4652d117
d0017930:	46284639 			; <UNDEFINED> instruction: 0x46284639
d0017934:	fe08f7ff 	mcr2	7, 0, pc, cr8, cr15, {7}	; <UNPREDICTABLE>
d0017938:	4658212c 	ldrbmi	r2, [r8], -ip, lsr #2
d001793c:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d0017940:	f7fb444d 			; <UNDEFINED> instruction: 0xf7fb444d
d0017944:	2800f9b4 	stmdacs	r0, {r2, r4, r5, r7, r8, fp, ip, sp, lr, pc}
d0017948:	4a17d1dc 	bmi	0xd060c0c0
d001794c:	4817217d 	ldmdami	r7, {r0, r2, r3, r4, r5, r6, r8, sp}
d0017950:	4478447a 	ldrbtmi	r4, [r8], #-1146	; 0xfffffb86
d0017954:	e8bdb003 	pop	{r0, r1, ip, sp, pc}
d0017958:	f7fb4ff0 			; <UNDEFINED> instruction: 0xf7fb4ff0
d001795c:	2b7bb9b6 	blcs	0xd1f0603c
d0017960:	2301d106 	movwcs	sp, #4358	; 0x1106
d0017964:	4629463a 			; <UNDEFINED> instruction: 0x4629463a
d0017968:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d001796c:	e7e3fec9 	strb	pc, [r3, r9, asr #29]!	; <UNPREDICTABLE>
d0017970:	7381f5a3 	orrvc	pc, r1, #683671552	; 0x28c00000
d0017974:	d8052b01 	stmdale	r5, {r0, r8, r9, fp, sp}
d0017978:	b91b6a33 	ldmdblt	fp, {r0, r1, r4, r5, r9, fp, sp, lr}
d001797c:	f7fb4630 			; <UNDEFINED> instruction: 0xf7fb4630
d0017980:	e7d9f97b 			; <UNDEFINED> instruction: 0xe7d9f97b
d0017984:	480b490a 	stmdami	fp, {r1, r3, r8, fp, lr}
d0017988:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d001798c:	b003e7c8 	andlt	lr, r3, r8, asr #15
d0017990:	8ff0e8bd 	svchi	0x00f0e8bd
d0017994:	00007534 	andeq	r7, r0, r4, lsr r5
d0017998:	ffffff54 			; <UNDEFINED> instruction: 0xffffff54
d001799c:	00007508 	andeq	r7, r0, r8, lsl #10
d00179a0:	000074f8 	strdeq	r7, [r0], -r8
d00179a4:	ffffff1d 			; <UNDEFINED> instruction: 0xffffff1d
d00179a8:	ffffff39 			; <UNDEFINED> instruction: 0xffffff39
d00179ac:	000074a2 	andeq	r7, r0, r2, lsr #9
d00179b0:	fffffed7 			; <UNDEFINED> instruction: 0xfffffed7
d00179b4:	0000746a 	andeq	r7, r0, sl, ror #8

Disassembly of section .text.local_declaration.constprop.0:

d0017bcc <.text.local_declaration.constprop.0>:
d0017bcc:	4ff0e92d 	svcmi	0x00f0e92d
d0017bd0:	6524f8df 	strvs	pc, [r4, #-2271]!	; 0xfffff721
d0017bd4:	f240b095 	vqadd.s8	d27, d16, d5
d0017bd8:	447e1107 	ldrbtmi	r1, [lr], #-263	; 0xfffffef9
d0017bdc:	f7fb4630 			; <UNDEFINED> instruction: 0xf7fb4630
d0017be0:	2800f866 	stmdacs	r0, {r1, r2, r5, r6, fp, ip, sp, lr, pc}
d0017be4:	6af3d049 	bvs	0xcfd0bd10
d0017be8:	d1072b28 	tstle	r7, r8, lsr #22
d0017bec:	2b2a6cf3 	blcs	0xd0ab2fc0
d0017bf0:	2000d104 	andcs	sp, r0, r4, lsl #2
d0017bf4:	fff6f7fc 			; <UNDEFINED> instruction: 0xfff6f7fc
d0017bf8:	e1af2401 			; <UNDEFINED> instruction: 0xe1af2401
d0017bfc:	04fcf8df 	ldrbteq	pc, [ip], #2271	; 0x8df	; <UNPREDICTABLE>
d0017c00:	4478212a 	ldrbtmi	r2, [r8], #-298	; 0xfffffed6
d0017c04:	f853f7fb 			; <UNDEFINED> instruction: 0xf853f7fb
d0017c08:	bf181e05 	svclt	0x00181e05
d0017c0c:	f8df250a 			; <UNDEFINED> instruction: 0xf8df250a
d0017c10:	ae0c44f0 	mcrge	4, 0, r4, cr12, cr0, {7}
d0017c14:	f104447c 			; <UNDEFINED> instruction: 0xf104447c
d0017c18:	f8d40718 			; <UNDEFINED> instruction: 0xf8d40718
d0017c1c:	f8d4b024 			; <UNDEFINED> instruction: 0xf8d4b024
d0017c20:	f894a028 			; <UNDEFINED> instruction: 0xf894a028
d0017c24:	f8d49030 			; <UNDEFINED> instruction: 0xf8d49030
d0017c28:	cf0f8034 	svcgt	0x000f8034
d0017c2c:	e897c60f 	ldm	r7, {r0, r1, r2, r3, r9, sl, lr, pc}
d0017c30:	e886000f 	stm	r6, {r0, r1, r2, r3}
d0017c34:	f8df000f 			; <UNDEFINED> instruction: 0xf8df000f
d0017c38:	f24024cc 	vshl.s8	q9, q6, q8
d0017c3c:	46201101 	strtmi	r1, [r0], -r1, lsl #2
d0017c40:	447aae0c 	ldrbtmi	sl, [sl], #-3596	; 0xfffff1f4
d0017c44:	f841f7fb 			; <UNDEFINED> instruction: 0xf841f7fb
d0017c48:	d0d52800 	sbcsle	r2, r5, r0, lsl #16
d0017c4c:	4620215b 			; <UNDEFINED> instruction: 0x4620215b
d0017c50:	f82df7fb 			; <UNDEFINED> instruction: 0xf82df7fb
d0017c54:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d0017c58:	2d008219 	sfmcs	f0, 1, [r0, #-100]	; 0xffffff9c
d0017c5c:	8184f000 	orrhi	pc, r4, r0
d0017c60:	2b006da3 	blcs	0xd00332f4
d0017c64:	f8dfd1c8 			; <UNDEFINED> instruction: 0xf8dfd1c8
d0017c68:	f8c434a0 			; <UNDEFINED> instruction: 0xf8c434a0
d0017c6c:	447b8068 	ldrbtmi	r8, [fp], #-104	; 0xffffff98
d0017c70:	a918e9c4 	ldmdbge	r8, {r2, r6, r7, r8, fp, sp, lr, pc}
d0017c74:	3b16e9c4 	blcc	0xd05d238c
d0017c78:	f44fe7be 	vst1.32	{d30}, [pc :256], lr
d0017c7c:	46307184 	ldrtmi	r7, [r0], -r4, lsl #3
d0017c80:	f815f7fb 			; <UNDEFINED> instruction: 0xf815f7fb
d0017c84:	b1804605 	orrlt	r4, r0, r5, lsl #12
d0017c88:	2b286af3 	blcs	0xd0a3285c
d0017c8c:	6cf3d104 	ldfvsp	f5, [r3], #16
d0017c90:	d1012b2a 	tstle	r1, sl, lsr #22
d0017c94:	e7ad2001 	str	r2, [sp, r1]!
d0017c98:	1470f8df 	ldrbtne	pc, [r0], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d0017c9c:	0470f8df 	ldrbteq	pc, [r0], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d0017ca0:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d0017ca4:	fa80f7f8 	blx	0xce055c8c
d0017ca8:	4630e7a6 	ldrtmi	lr, [r0], -r6, lsr #15
d0017cac:	fd3af7f8 	ldc2	7, cr15, [sl, #-992]!	; 0xfffffc20
d0017cb0:	28004604 	stmdacs	r0, {r2, r9, sl, lr}
d0017cb4:	8134f000 	teqhi	r4, r0	; <UNPREDICTABLE>
d0017cb8:	4630a90b 	ldrtmi	sl, [r0], -fp, lsl #18
d0017cbc:	f7fb950b 			; <UNDEFINED> instruction: 0xf7fb950b
d0017cc0:	2800f847 	stmdacs	r0, {r0, r1, r2, r6, fp, ip, sp, lr, pc}
d0017cc4:	212ad098 			; <UNDEFINED> instruction: 0x212ad098
d0017cc8:	f7fa4630 			; <UNDEFINED> instruction: 0xf7fa4630
d0017ccc:	f106fff0 			; <UNDEFINED> instruction: 0xf106fff0
d0017cd0:	46040c18 			; <UNDEFINED> instruction: 0x46040c18
d0017cd4:	f8d6af0c 			; <UNDEFINED> instruction: 0xf8d6af0c
d0017cd8:	f8d6b024 			; <UNDEFINED> instruction: 0xf8d6b024
d0017cdc:	f896a028 			; <UNDEFINED> instruction: 0xf896a028
d0017ce0:	f8d69030 			; <UNDEFINED> instruction: 0xf8d69030
d0017ce4:	e8bc8034 	ldm	ip!, {r2, r4, r5, pc}
d0017ce8:	c70f000f 	strgt	r0, [pc, -pc]
d0017cec:	000fe89c 	muleq	pc, ip, r8	; <UNPREDICTABLE>
d0017cf0:	000fe887 	andeq	lr, pc, r7, lsl #17
d0017cf4:	241cf8df 	ldrcs	pc, [ip], #-2271	; 0xfffff721
d0017cf8:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d0017cfc:	447a4630 	ldrbtmi	r4, [sl], #-1584	; 0xfffff9d0
d0017d00:	ffe3f7fa 			; <UNDEFINED> instruction: 0xffe3f7fa
d0017d04:	9307ab0c 	movwls	sl, #31500	; 0x7b0c
d0017d08:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0017d0c:	b934af75 	ldmdblt	r4!, {r0, r2, r4, r5, r6, r8, r9, sl, fp, sp, pc}
d0017d10:	4630215b 			; <UNDEFINED> instruction: 0x4630215b
d0017d14:	ffcbf7fa 			; <UNDEFINED> instruction: 0xffcbf7fa
d0017d18:	bf181e05 	svclt	0x00181e05
d0017d1c:	48fe2501 	ldmmi	lr!, {r0, r8, sl, sp}^
d0017d20:	721af44f 	andsvc	pc, sl, #1325400064	; 0x4f000000
d0017d24:	44789b0b 	ldrbtmi	r9, [r8], #-2827	; 0xfffff4f5
d0017d28:	0203fb02 	andeq	pc, r3, #2048	; 0x800
d0017d2c:	32bdf502 	adcscc	pc, sp, #8388608	; 0x800000
d0017d30:	6068f8b2 	strhtvs	pc, [r8], #-130	; 0xffffff7e	; <UNPREDICTABLE>
d0017d34:	d0512d00 	subsle	r2, r1, r0, lsl #26
d0017d38:	f5a26ac2 			; <UNDEFINED> instruction: 0xf5a26ac2
d0017d3c:	2a017281 	bcs	0xd0074748
d0017d40:	6a07d806 	bvs	0xd020dd60
d0017d44:	2240b127 	subcs	fp, r0, #-1073741815	; 0xc0000009
d0017d48:	f2f6fbb2 			; <UNDEFINED> instruction: 0xf2f6fbb2
d0017d4c:	d9204297 	stmdble	r0!, {r0, r1, r2, r4, r7, r9, lr}
d0017d50:	f44f4af2 	vst1.64	{d20-d21}, [pc :256], r2
d0017d54:	447a711a 	ldrbtmi	r7, [sl], #-282	; 0xfffffee6
d0017d58:	2303fb01 	movwcs	pc, #15105	; 0x3b01	; <UNPREDICTABLE>
d0017d5c:	33bdf503 			; <UNDEFINED> instruction: 0x33bdf503
d0017d60:	306bf893 	mlscc	fp, r3, r8, pc	; <UNPREDICTABLE>
d0017d64:	4aeeb993 	bmi	0xcfbc63b8
d0017d68:	4bee447a 	blmi	0xcfba8f58
d0017d6c:	6d99447b 	cfldrsvs	mvf4, [r9, #492]	; 0x1ec
d0017d70:	f47f2900 			; <UNDEFINED> instruction: 0xf47f2900
d0017d74:	6a5daf41 	bvs	0xd1783a80
d0017d78:	6b596a9c 	blvs	0xd16727f0
d0017d7c:	0030f893 	mlaseq	r0, r3, r8, pc	; <UNPREDICTABLE>
d0017d80:	e9c36699 	stmib	r3, {r0, r3, r4, r7, r9, sl, sp, lr}^
d0017d84:	e9c32516 	stmib	r3, {r1, r2, r4, r8, sl, sp}^
d0017d88:	e7354018 			; <UNDEFINED> instruction: 0xe7354018
d0017d8c:	447a4ae6 	ldrbtmi	r4, [sl], #-2790	; 0xfffff51a
d0017d90:	9008e7eb 	andls	lr, r8, fp, ror #15
d0017d94:	ff70f7fa 			; <UNDEFINED> instruction: 0xff70f7fa
d0017d98:	215d4ae4 	cmpcs	sp, r4, ror #21
d0017d9c:	447a9808 	ldrbtmi	r9, [sl], #-2056	; 0xfffff7f8
d0017da0:	ff93f7fa 			; <UNDEFINED> instruction: 0xff93f7fa
d0017da4:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0017da8:	b9ccaf27 	stmiblt	ip, {r0, r1, r2, r5, r8, r9, sl, fp, sp, pc}^
d0017dac:	4be0437e 	blmi	0xcf828bac
d0017db0:	f503447b 			; <UNDEFINED> instruction: 0xf503447b
d0017db4:	f8d23216 			; <UNDEFINED> instruction: 0xf8d23216
d0017db8:	f1c221ec 			; <UNDEFINED> instruction: 0xf1c221ec
d0017dbc:	42b20240 	adcsmi	r0, r2, #64, 4
d0017dc0:	6d9ad210 	lfmvs	f5, 1, [sl, #64]	; 0x40
d0017dc4:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0017dc8:	4adaaf17 	bmi	0xcf6c3a2c
d0017dcc:	8068f8c3 	rsbhi	pc, r8, r3, asr #17
d0017dd0:	e9c3447a 	stmib	r3, {r1, r3, r4, r5, r6, sl, lr}^
d0017dd4:	e9c3a918 	stmib	r3, {r3, r4, r8, fp, sp, pc}^
d0017dd8:	e70d2b16 	smlad	sp, r6, fp, r2
d0017ddc:	e7e42701 	strb	r2, [r4, r1, lsl #14]!
d0017de0:	e7e42601 	strb	r2, [r4, r1, lsl #12]!
d0017de4:	d1522c00 	cmple	r2, r0, lsl #24
d0017de8:	bf142d00 	svclt	0x00142d00
d0017dec:	230d2310 	movwcs	r2, #54032	; 0xd310
d0017df0:	ab149304 	blge	0xd053ca08
d0017df4:	a040f8cd 	subge	pc, r0, sp, asr #17
d0017df8:	9048f88d 	subls	pc, r8, sp, lsl #17
d0017dfc:	804cf8cd 	subhi	pc, ip, sp, asr #17
d0017e00:	a334f8df 	teqge	r4, #14614528	; 0xdf0000	; <UNPREDICTABLE>
d0017e04:	b03cf8cd 	eorslt	pc, ip, sp, asr #17
d0017e08:	e91344fa 	ldmdb	r3, {r1, r3, r4, r5, r6, r7, sl, lr}
d0017e0c:	e88d000f 	stm	sp, {r0, r1, r2, r3}
d0017e10:	9b07000f 	blls	0xd01d7e54
d0017e14:	f7fbcb0f 			; <UNDEFINED> instruction: 0xf7fbcb0f
d0017e18:	f8dafc07 			; <UNDEFINED> instruction: 0xf8dafc07
d0017e1c:	46813058 	pkhtbmi	r3, r1, r8, asr #32
d0017e20:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0017e24:	222caee9 	eorcs	sl, ip, #3728	; 0xe90
d0017e28:	f50a990b 			; <UNDEFINED> instruction: 0xf50a990b
d0017e2c:	fb023b16 	blx	0xd00a6a8e
d0017e30:	9208a300 	andls	sl, r8, #0, 6
d0017e34:	3313f503 	tstcc	r3, #12582912	; 0xc00000	; <UNPREDICTABLE>
d0017e38:	130ef883 	movwne	pc, #59523	; 0xe883	; <UNPREDICTABLE>
d0017e3c:	7316f8a3 	tstvc	r6, #10682368	; 0xa30000	; <UNPREDICTABLE>
d0017e40:	429e2301 	addsmi	r2, lr, #67108864	; 0x4000000
d0017e44:	21ecf8db 	ldrdcs	pc, [ip, #139]!	; 0x8b
d0017e48:	f8dbd823 			; <UNDEFINED> instruction: 0xf8dbd823
d0017e4c:	429331f0 	addsmi	r3, r3, #240, 2	; 0x3c
d0017e50:	f8cbbf38 			; <UNDEFINED> instruction: 0xf8cbbf38
d0017e54:	2c0021f0 	stfcss	f2, [r0], {240}	; 0xf0
d0017e58:	4cb8d03a 	ldcmi	0, cr13, [r8], #232	; 0xe8
d0017e5c:	447c213d 	ldrbtmi	r2, [ip], #-317	; 0xfffffec3
d0017e60:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0017e64:	4601ff24 	strmi	pc, [r1], -r4, lsr #30
d0017e68:	990bb370 	stmdbls	fp, {r4, r5, r6, r8, r9, ip, sp, pc}
d0017e6c:	f7fe4620 			; <UNDEFINED> instruction: 0xf7fe4620
d0017e70:	48b3ff2f 	ldmmi	r3!, {r0, r1, r2, r3, r5, r8, r9, sl, fp, ip, sp, lr, pc}
d0017e74:	46492200 	strbmi	r2, [r9], -r0, lsl #4
d0017e78:	f7fc4478 			; <UNDEFINED> instruction: 0xf7fc4478
d0017e7c:	4ab1f9f9 	bmi	0xcec96668
d0017e80:	48b1213b 	ldmmi	r1!, {r0, r1, r3, r4, r5, r8, sp}
d0017e84:	4478447a 	ldrbtmi	r4, [r8], #-1146	; 0xfffffb86
d0017e88:	ff1ff7fa 			; <UNDEFINED> instruction: 0xff1ff7fa
d0017e8c:	230ee6b4 	movwcs	lr, #59060	; 0xe6b4
d0017e90:	9309e7ae 	movwls	lr, #38830	; 0x97ae
d0017e94:	f89b1c51 			; <UNDEFINED> instruction: 0xf89b1c51
d0017e98:	f8cb31f4 			; <UNDEFINED> instruction: 0xf8cb31f4
d0017e9c:	210011ec 	smlattcs	r0, ip, r1, r1
d0017ea0:	9b089307 	blls	0xd023cac4
d0017ea4:	a802fb03 	stmdage	r2, {r0, r1, r8, r9, fp, ip, sp, lr, pc}
d0017ea8:	f508222c 			; <UNDEFINED> instruction: 0xf508222c
d0017eac:	f5083813 			; <UNDEFINED> instruction: 0xf5083813
d0017eb0:	f004703b 			; <UNDEFINED> instruction: 0xf004703b
d0017eb4:	9b07fad5 	blls	0xd0216a10
d0017eb8:	f888220b 			; <UNDEFINED> instruction: 0xf888220b
d0017ebc:	9b09330c 	blls	0xd0264af4
d0017ec0:	230df888 	movwcs	pc, #55432	; 0xd888	; <UNPREDICTABLE>
d0017ec4:	e7bc3301 	ldr	r3, [ip, r1, lsl #6]!
d0017ec8:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d0017ecc:	e7d0f997 	bfi	pc, r7, (invalid: 19:16)	; <UNPREDICTABLE>
d0017ed0:	8278f8df 	rsbshi	pc, r8, #14614528	; 0xdf0000
d0017ed4:	44f8213d 	ldrbtmi	r2, [r8], #317	; 0x13d
d0017ed8:	f7fa4640 			; <UNDEFINED> instruction: 0xf7fa4640
d0017edc:	2800fee8 	stmdacs	r0, {r3, r5, r6, r7, r9, sl, fp, ip, sp, lr, pc}
d0017ee0:	4640d0cd 	strbmi	sp, [r0], -sp, asr #1
d0017ee4:	f7fc4621 			; <UNDEFINED> instruction: 0xf7fc4621
d0017ee8:	4899f989 	ldmmi	r9, {r0, r3, r7, r8, fp, ip, sp, lr, pc}
d0017eec:	42a64478 	adcmi	r4, r6, #120, 8	; 0x78000000
d0017ef0:	980bd109 	stmdals	fp, {r0, r3, r8, ip, lr, pc}
d0017ef4:	2300b175 	movwcs	fp, #373	; 0x175
d0017ef8:	464a4601 	strbmi	r4, [sl], -r1, lsl #12
d0017efc:	93004638 	movwls	r4, #1592	; 0x638
d0017f00:	fcd8f7ff 	ldc2l	7, cr15, [r8], {255}	; 0xff
d0017f04:	eb09e7bb 	bl	0xd0291df8
d0017f08:	22000104 	andcs	r0, r0, #4, 2
d0017f0c:	f7fc3401 			; <UNDEFINED> instruction: 0xf7fc3401
d0017f10:	e7ecf9af 	strb	pc, [ip, pc, lsr #19]!	; <UNPREDICTABLE>
d0017f14:	462a2301 	strtmi	r2, [sl], -r1, lsl #6
d0017f18:	f7ff4649 			; <UNDEFINED> instruction: 0xf7ff4649
d0017f1c:	e7aefbf1 			; <UNDEFINED> instruction: 0xe7aefbf1
d0017f20:	f2406af2 	vpmin.s8	q11, q8, q9
d0017f24:	429a1301 	addsmi	r1, sl, #67108864	; 0x4000000
d0017f28:	4630d118 			; <UNDEFINED> instruction: 0x4630d118
d0017f2c:	1206e9d6 	andne	lr, r6, #3506176	; 0x358000
d0017f30:	fb8ff7f8 	blx	0xce415f1a
d0017f34:	da112800 	ble	0xd0461f3c
d0017f38:	44784886 	ldrbtmi	r4, [r8], #-2182	; 0xfffff77a
d0017f3c:	f8b6f7fc 			; <UNDEFINED> instruction: 0xf8b6f7fc
d0017f40:	4885b980 	stmmi	r5, {r7, r8, fp, ip, sp, pc}
d0017f44:	f7fc4478 			; <UNDEFINED> instruction: 0xf7fc4478
d0017f48:	b108f8b1 			; <UNDEFINED> instruction: 0xb108f8b1
d0017f4c:	e65e2505 	ldrb	r2, [lr], -r5, lsl #10
d0017f50:	44784882 	ldrbtmi	r4, [r8], #-2178	; 0xfffff77e
d0017f54:	f8aaf7fc 			; <UNDEFINED> instruction: 0xf8aaf7fc
d0017f58:	d1f72800 	mvnsle	r2, r0, lsl #16
d0017f5c:	b0154620 	andslt	r4, r5, r0, lsr #12
d0017f60:	8ff0e8bd 	svchi	0x00f0e8bd
d0017f64:	e6522501 	ldrb	r2, [r2], -r1, lsl #10
d0017f68:	f5a36ae3 			; <UNDEFINED> instruction: 0xf5a36ae3
d0017f6c:	2b017381 	blcs	0xd0074d78
d0017f70:	6a27d809 	bvs	0xd0a0df9c
d0017f74:	f504b13f 			; <UNDEFINED> instruction: 0xf504b13f
d0017f78:	f8d53516 			; <UNDEFINED> instruction: 0xf8d53516
d0017f7c:	f1c331ec 			; <UNDEFINED> instruction: 0xf1c331ec
d0017f80:	429f0340 	addsmi	r0, pc, #64, 6
d0017f84:	4b76d912 	blmi	0xd1dce3d4
d0017f88:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d0017f8c:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0017f90:	4d74ae33 	ldclmi	14, cr10, [r4, #-204]!	; 0xffffff34
d0017f94:	6a986a5c 	bvs	0xce63290c
d0017f98:	6b5a447d 	blvs	0xd16a9194
d0017f9c:	1030f893 	mlasne	r0, r3, r8, pc	; <UNPREDICTABLE>
d0017fa0:	e9c3669a 	stmib	r3, {r1, r3, r4, r7, r9, sl, sp, lr}^
d0017fa4:	e9c35416 	stmib	r3, {r1, r2, r4, sl, ip, lr}^
d0017fa8:	e6250118 			; <UNDEFINED> instruction: 0xe6250118
d0017fac:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0017fb0:	4a6dfe63 	bmi	0xd1b97944
d0017fb4:	4620215d 			; <UNDEFINED> instruction: 0x4620215d
d0017fb8:	f7fa447a 			; <UNDEFINED> instruction: 0xf7fa447a
d0017fbc:	2800fe86 	stmdacs	r0, {r1, r2, r7, r9, sl, fp, ip, sp, lr, pc}
d0017fc0:	ae1af43f 	mrcge	4, 0, APSR_nzcv, cr10, cr15, {1}
d0017fc4:	f8cd2309 			; <UNDEFINED> instruction: 0xf8cd2309
d0017fc8:	f8cd804c 			; <UNDEFINED> instruction: 0xf8cd804c
d0017fcc:	9304a040 	movwls	sl, #16448	; 0x4040
d0017fd0:	f88dab14 			; <UNDEFINED> instruction: 0xf88dab14
d0017fd4:	f8cd9048 			; <UNDEFINED> instruction: 0xf8cd9048
d0017fd8:	e913b03c 	ldmdb	r3, {r2, r3, r4, r5, ip, sp, pc}
d0017fdc:	e88d000f 	stm	sp, {r0, r1, r2, r3}
d0017fe0:	e896000f 	ldm	r6, {r0, r1, r2, r3}
d0017fe4:	f7fb000f 			; <UNDEFINED> instruction: 0xf7fb000f
d0017fe8:	6da3fb1f 			; <UNDEFINED> instruction: 0x6da3fb1f
d0017fec:	2b004680 	blcs	0xd00299f4
d0017ff0:	ae02f47f 	mcrge	4, 0, pc, cr2, cr15, {3}	; <UNPREDICTABLE>
d0017ff4:	0a2cf04f 	beq	0xd0b54138
d0017ff8:	46a92601 	strtmi	r2, [r9], r1, lsl #12
d0017ffc:	4300fb0a 	movwmi	pc, #2826	; 0xb0a	; <UNPREDICTABLE>
d0018000:	3313f503 	tstcc	r3, #12582912	; 0xc00000	; <UNPREDICTABLE>
d0018004:	7316f8a3 	tstvc	r6, #10682368	; 0xa30000	; <UNPREDICTABLE>
d0018008:	f8d942b7 			; <UNDEFINED> instruction: 0xf8d942b7
d001800c:	d12731ec 			; <UNDEFINED> instruction: 0xd12731ec
d0018010:	213d4c56 	teqcs	sp, r6, asr ip
d0018014:	21f0f8d9 	ldrsbcs	pc, [r0, #137]!	; 0x89	; <UNPREDICTABLE>
d0018018:	429a447c 	addsmi	r4, sl, #124, 8	; 0x7c000000
d001801c:	bf384620 	svclt	0x00384620
d0018020:	31f0f8c9 	mvnscc	pc, r9, asr #17
d0018024:	fe43f7fa 	mcr2	7, 2, pc, cr3, cr10, {7}	; <UNPREDICTABLE>
d0018028:	4620b1a0 	strtmi	fp, [r0], -r0, lsr #3
d001802c:	f7fc2100 			; <UNDEFINED> instruction: 0xf7fc2100
d0018030:	2500f8e5 	strcs	pc, [r0, #-2277]	; 0xfffff71b
d0018034:	eb084620 	bl	0xd02298bc
d0018038:	35010105 	strcc	r0, [r1, #-261]	; 0xfffffefb
d001803c:	f7fc2200 			; <UNDEFINED> instruction: 0xf7fc2200
d0018040:	42aef917 	adcmi	pc, lr, #376832	; 0x5c000
d0018044:	2300d1f7 	movwcs	sp, #503	; 0x1f7
d0018048:	21ff4642 	mvnscs	r4, r2, asr #12
d001804c:	93004630 	movwls	r4, #1584	; 0x630
d0018050:	fc30f7ff 	ldc2	7, cr15, [r0], #-1020	; 0xfffffc04
d0018054:	213b4a46 	teqcs	fp, r6, asr #20
d0018058:	447a4846 	ldrbtmi	r4, [sl], #-2118	; 0xfffff7ba
d001805c:	e7134478 			; <UNDEFINED> instruction: 0xe7134478
d0018060:	fb0a1c5a 	blx	0xd029f1d2
d0018064:	21004303 	tstcs	r0, r3, lsl #6
d0018068:	b1f4f899 			; <UNDEFINED> instruction: 0xb1f4f899
d001806c:	3513f503 	ldrcc	pc, [r3, #-1283]	; 0xfffffafd
d0018070:	21ecf8c9 	mvncs	pc, r9, asr #17
d0018074:	3601222c 	strcc	r2, [r1], -ip, lsr #4
d0018078:	703bf505 	eorsvc	pc, fp, r5, lsl #10
d001807c:	f9f0f004 			; <UNDEFINED> instruction: 0xf9f0f004
d0018080:	f885230b 			; <UNDEFINED> instruction: 0xf885230b
d0018084:	f885b30c 			; <UNDEFINED> instruction: 0xf885b30c
d0018088:	e7bd330d 	ldr	r3, [sp, sp, lsl #6]!
d001808c:	f8cdb2eb 			; <UNDEFINED> instruction: 0xf8cdb2eb
d0018090:	f88da040 			; <UNDEFINED> instruction: 0xf88da040
d0018094:	93049048 	movwls	r9, #16456	; 0x4048
d0018098:	f8cdab14 			; <UNDEFINED> instruction: 0xf8cdab14
d001809c:	f8cd804c 			; <UNDEFINED> instruction: 0xf8cd804c
d00180a0:	e913b03c 	ldmdb	r3, {r2, r3, r4, r5, ip, sp, pc}
d00180a4:	e88d000f 	stm	sp, {r0, r1, r2, r3}
d00180a8:	e896000f 	ldm	r6, {r0, r1, r2, r3}
d00180ac:	f7fb000f 			; <UNDEFINED> instruction: 0xf7fb000f
d00180b0:	213dfabb 	teqcs	sp, fp	; <illegal shifter operand>	; <UNPREDICTABLE>
d00180b4:	46204606 	strtmi	r4, [r0], -r6, lsl #12
d00180b8:	fdf9f7fa 	ldc2l	7, cr15, [r9, #1000]!	; 0x3e8
d00180bc:	2d0ab1a8 	stfcsd	f3, [sl, #-672]	; 0xfffffd60
d00180c0:	0101f04f 	tsteq	r1, pc, asr #32	; <UNPREDICTABLE>
d00180c4:	bf0c4620 	svclt	0x000c4620
d00180c8:	22012204 	andcs	r2, r1, #4, 4	; 0x40000000
d00180cc:	f9d6f7fe 			; <UNDEFINED> instruction: 0xf9d6f7fe
d00180d0:	d1042d05 	tstle	r4, r5, lsl #26
d00180d4:	21c0f24b 	biccs	pc, r0, fp, asr #4
d00180d8:	f7fc4620 			; <UNDEFINED> instruction: 0xf7fc4620
d00180dc:	4826f833 	stmdami	r6!, {r0, r1, r4, r5, fp, ip, sp, lr, pc}
d00180e0:	46312200 	ldrtmi	r2, [r1], -r0, lsl #4
d00180e4:	f7fc4478 			; <UNDEFINED> instruction: 0xf7fc4478
d00180e8:	4a24f8c3 	bmi	0xd09563fc
d00180ec:	4824213b 	stmdami	r4!, {r0, r1, r3, r4, r5, r8, sp}
d00180f0:	4478447a 	ldrbtmi	r4, [r8], #-1146	; 0xfffffb86
d00180f4:	bf00e6c8 	svclt	0x0000e6c8
d00180f8:	0000721a 	andeq	r7, r0, sl, lsl r2
d00180fc:	000071f2 	strdeq	r7, [r0], -r2
d0018100:	000071e0 	andeq	r7, r0, r0, ror #3
d0018104:	fffffea4 			; <UNDEFINED> instruction: 0xfffffea4
d0018108:	fffffe97 			; <UNDEFINED> instruction: 0xfffffe97
d001810c:	fffffd67 			; <UNDEFINED> instruction: 0xfffffd67
d0018110:	00007152 	andeq	r7, r0, r2, asr r1
d0018114:	fffffd42 			; <UNDEFINED> instruction: 0xfffffd42
d0018118:	000070ce 	andeq	r7, r0, lr, asr #1
d001811c:	0000709e 	muleq	r0, lr, r0
d0018120:	fffffc75 			; <UNDEFINED> instruction: 0xfffffc75
d0018124:	00007088 	andeq	r7, r0, r8, lsl #1
d0018128:	fffffc26 			; <UNDEFINED> instruction: 0xfffffc26
d001812c:	fffffcc0 			; <UNDEFINED> instruction: 0xfffffcc0
d0018130:	00007044 	andeq	r7, r0, r4, asr #32
d0018134:	fffffcb3 			; <UNDEFINED> instruction: 0xfffffcb3
d0018138:	00006fec 	andeq	r6, r0, ip, ror #31
d001813c:	00006f96 	muleq	r0, r6, pc	; <UNPREDICTABLE>
d0018140:	00006f7c 	andeq	r6, r0, ip, ror pc
d0018144:	fffffc2d 			; <UNDEFINED> instruction: 0xfffffc2d
d0018148:	00006f6e 	andeq	r6, r0, lr, ror #30
d001814c:	00006f1e 	andeq	r6, r0, lr, lsl pc
d0018150:	00006f08 	andeq	r6, r0, r8, lsl #30
d0018154:	fffffb9a 			; <UNDEFINED> instruction: 0xfffffb9a
d0018158:	fffffb99 			; <UNDEFINED> instruction: 0xfffffb99
d001815c:	ffffaee0 			; <UNDEFINED> instruction: 0xffffaee0
d0018160:	00006e6c 	andeq	r6, r0, ip, ror #28
d0018164:	fffffb91 			; <UNDEFINED> instruction: 0xfffffb91
d0018168:	fffffba2 			; <UNDEFINED> instruction: 0xfffffba2
d001816c:	00006ddc 	ldrdeq	r6, [r0], -ip
d0018170:	fffffb24 			; <UNDEFINED> instruction: 0xfffffb24
d0018174:	00006d98 	muleq	r0, r8, sp
d0018178:	00006d10 	andeq	r6, r0, r0, lsl sp
d001817c:	fffffab9 			; <UNDEFINED> instruction: 0xfffffab9
d0018180:	00006d02 	andeq	r6, r0, r2, lsl #26

Disassembly of section .text.block.constprop.0:

d00181a4 <.text.block.constprop.0>:
d00181a4:	4c0db510 	cfstr32mi	mvfx11, [sp], {16}
d00181a8:	6da3447c 	cfstrsvs	mvf4, [r3, #496]!	; 0x1f0
d00181ac:	6ae3b92b 	bvs	0xcf906660
d00181b0:	d0022b7d 	andle	r2, r2, sp, ror fp
d00181b4:	7f80f5b3 	svcvc	0x0080f5b3
d00181b8:	4a09d108 	bmi	0xd028c5e0
d00181bc:	4809217d 	stmdami	r9, {r0, r2, r3, r4, r5, r6, r8, sp}
d00181c0:	4478447a 	ldrbtmi	r4, [r8], #-1146	; 0xfffffb86
d00181c4:	4010e8bd 			; <UNDEFINED> instruction: 0x4010e8bd
d00181c8:	bd7ff7fa 	ldcllt	7, cr15, [pc, #-1000]!	; 0xd0017de8
d00181cc:	fcfef7ff 	ldc2l	7, cr15, [lr], #1020	; 0x3fc
d00181d0:	d1ea2800 	mvnle	r2, r0, lsl #16
d00181d4:	f9b6f000 			; <UNDEFINED> instruction: 0xf9b6f000
d00181d8:	bf00e7e7 	svclt	0x0000e7e7
d00181dc:	00006c4c 	andeq	r6, r0, ip, asr #24
d00181e0:	ffffffc0 			; <UNDEFINED> instruction: 0xffffffc0
d00181e4:	00006c32 	andeq	r6, r0, r2, lsr ip

Disassembly of section .text.statement.constprop.0:

d0018544 <.text.statement.constprop.0>:
d0018544:	4ff0e92d 	svcmi	0x00f0e92d
d0018548:	494cf8df 	stmdbmi	ip, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d001854c:	6da3447c 	cfstrsvs	mvf4, [r3, #496]!	; 0x1f0
d0018550:	8b02ed2d 	blhi	0xd00d3a0c
d0018554:	bb6bb089 	bllt	0xd1b04780
d0018558:	3516f504 	ldrcc	pc, [r6, #-1284]	; 0xfffffafc
d001855c:	31f8f8d5 	ldrsbcc	pc, [r8, #133]!	; 0x85	; <UNPREDICTABLE>
d0018560:	2b203301 	blcs	0xd082516c
d0018564:	31f8f8c5 	mvnscc	pc, r5, asr #17
d0018568:	f8dfd904 			; <UNDEFINED> instruction: 0xf8dfd904
d001856c:	44791930 	ldrbtmi	r1, [r9], #-2352	; 0xfffff6d0
d0018570:	e0644620 	rsb	r4, r4, r0, lsr #12
d0018574:	4620217b 			; <UNDEFINED> instruction: 0x4620217b
d0018578:	fb99f7fa 	blx	0xce69656a
d001857c:	b1f04606 	mvnslt	r4, r6, lsl #12
d0018580:	31f4f8d5 	ldrsbcc	pc, [r4, #133]!	; 0x85	; <UNPREDICTABLE>
d0018584:	41ecf8d5 	ldrdmi	pc, [ip, #133]!	; 0x85
d0018588:	f8c53301 			; <UNDEFINED> instruction: 0xf8c53301
d001858c:	f7ff31f4 			; <UNDEFINED> instruction: 0xf7ff31f4
d0018590:	f8d5fe09 			; <UNDEFINED> instruction: 0xf8d5fe09
d0018594:	f8c531f4 			; <UNDEFINED> instruction: 0xf8c531f4
d0018598:	3b0141ec 	blcc	0xd0068d50
d001859c:	31f4f8c5 	mvnscc	pc, r5, asr #17
d00185a0:	38fcf8df 	ldmcc	ip!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d00185a4:	f503447b 			; <UNDEFINED> instruction: 0xf503447b
d00185a8:	f8d33316 			; <UNDEFINED> instruction: 0xf8d33316
d00185ac:	3a0121f8 	bcc	0xd0060d94
d00185b0:	21f8f8c3 	mvnscs	pc, r3, asr #17
d00185b4:	ecbdb009 	ldc	0, cr11, [sp], #36	; 0x24
d00185b8:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d00185bc:	f44f8ff0 			; <UNDEFINED> instruction: 0xf44f8ff0
d00185c0:	46207186 	strtmi	r7, [r0], -r6, lsl #3
d00185c4:	fb73f7fa 	blx	0xd1d165b6
d00185c8:	b3384680 	teqlt	r8, #128, 12	; 0x8000000
d00185cc:	fdc4f7fe 	stc2l	7, cr15, [r4, #1016]	; 0x3f8
d00185d0:	46204631 			; <UNDEFINED> instruction: 0x46204631
d00185d4:	57f8f64d 	ldrbpl	pc, [r8, sp, asr #12]!	; <UNPREDICTABLE>
d00185d8:	ff54f7fb 			; <UNDEFINED> instruction: 0xff54f7fb
d00185dc:	f7ff4605 			; <UNDEFINED> instruction: 0xf7ff4605
d00185e0:	f240ffb1 	vrecps.f32	d31, d16, d17
d00185e4:	4620110d 	strtmi	r1, [r0], -sp, lsl #2
d00185e8:	fb61f7fa 	blx	0xd18965da
d00185ec:	b1904603 	orrslt	r4, r0, r3, lsl #12
d00185f0:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d00185f4:	4680ff3b 			; <UNDEFINED> instruction: 0x4680ff3b
d00185f8:	59e24633 	stmibpl	r2!, {r0, r1, r4, r5, r9, sl, lr}^
d00185fc:	6da04629 	stcvs	6, cr4, [r0, #164]!	; 0xa4
d0018600:	fcaef7fc 	stc2	7, cr15, [lr], #1008	; 0x3f0
d0018604:	ff9ef7ff 			; <UNDEFINED> instruction: 0xff9ef7ff
d0018608:	59e24633 	stmibpl	r2!, {r0, r1, r4, r5, r9, sl, lr}^
d001860c:	6da04641 	stcvs	6, cr4, [r0, #260]!	; 0x104
d0018610:	fca6f7fc 	stc2	7, cr15, [r6], #1008	; 0x3f0
d0018614:	59e2e7c4 	stmibpl	r2!, {r2, r6, r7, r8, r9, sl, sp, lr, pc}^
d0018618:	e7f84629 	ldrb	r4, [r8, r9, lsr #12]!
d001861c:	7187f44f 	orrvc	pc, r7, pc, asr #8
d0018620:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0018624:	2800fb44 	stmdacs	r0, {r2, r6, r8, r9, fp, ip, sp, lr, pc}
d0018628:	f8d5d07d 			; <UNDEFINED> instruction: 0xf8d5d07d
d001862c:	2b2031fc 	blcs	0xd0824e24
d0018630:	f8dfd108 			; <UNDEFINED> instruction: 0xf8dfd108
d0018634:	f8df1870 			; <UNDEFINED> instruction: 0xf8df1870
d0018638:	44790870 	ldrbtmi	r0, [r9], #-2160	; 0xfffff790
d001863c:	f7f74478 			; <UNDEFINED> instruction: 0xf7f74478
d0018640:	e7adfdb3 			; <UNDEFINED> instruction: 0xe7adfdb3
d0018644:	53f8f64d 	mvnspl	pc, #80740352	; 0x4d00000
d0018648:	6200f8d5 	andvs	pc, r0, #13959168	; 0xd50000
d001864c:	f7fe58e7 			; <UNDEFINED> instruction: 0xf7fe58e7
d0018650:	4641fd83 	strbmi	pc, [r1], -r3, lsl #27	; <UNPREDICTABLE>
d0018654:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0018658:	f8d5ff15 			; <UNDEFINED> instruction: 0xf8d5ff15
d001865c:	468031fc 			; <UNDEFINED> instruction: 0x468031fc
d0018660:	f8c53301 			; <UNDEFINED> instruction: 0xf8c53301
d0018664:	f50431fc 			; <UNDEFINED> instruction: 0xf50431fc
d0018668:	f8d5351a 			; <UNDEFINED> instruction: 0xf8d5351a
d001866c:	2b403204 	blcs	0xd1024e84
d0018670:	f8dfd138 			; <UNDEFINED> instruction: 0xf8dfd138
d0018674:	46201838 			; <UNDEFINED> instruction: 0x46201838
d0018678:	f7f74479 			; <UNDEFINED> instruction: 0xf7f74479
d001867c:	f8dffd95 			; <UNDEFINED> instruction: 0xf8dffd95
d0018680:	f8df4830 			; <UNDEFINED> instruction: 0xf8df4830
d0018684:	447ca830 	ldrbtmi	sl, [ip], #-2096	; 0xfffff7d0
d0018688:	f50444fa 			; <UNDEFINED> instruction: 0xf50444fa
d001868c:	eb043216 	bl	0xd0124eec
d0018690:	462005c6 	strtmi	r0, [r0], -r6, asr #11
d0018694:	495df504 	ldmdbmi	sp, {r2, r8, sl, ip, sp, lr, pc}^
d0018698:	31fcf8d2 	ldrsbcc	pc, [ip, #130]!	; 0x82	; <UNPREDICTABLE>
d001869c:	3516f505 	ldrcc	pc, [r6, #-1285]	; 0xfffffafb
d00186a0:	09f8f109 	ldmibeq	r8!, {r0, r3, r8, ip, sp, lr, pc}^
d00186a4:	f5053b01 			; <UNDEFINED> instruction: 0xf5053b01
d00186a8:	f8c27501 			; <UNDEFINED> instruction: 0xf8c27501
d00186ac:	f7fb31fc 			; <UNDEFINED> instruction: 0xf7fb31fc
d00186b0:	2300fedd 	movwcs	pc, #3805	; 0xedd	; <UNPREDICTABLE>
d00186b4:	463a4601 	ldrtmi	r4, [sl], -r1, lsl #12
d00186b8:	f7fc6da0 			; <UNDEFINED> instruction: 0xf7fc6da0
d00186bc:	f64dfc51 			; <UNDEFINED> instruction: 0xf64dfc51
d00186c0:	464152f8 			; <UNDEFINED> instruction: 0x464152f8
d00186c4:	230046b0 	movwcs	r4, #1712	; 0x6b0
d00186c8:	6da058a2 	stcvs	8, cr5, [r0, #648]!	; 0x288
d00186cc:	fc48f7fc 	mcrr2	7, 15, pc, r8, cr12	; <UNPREDICTABLE>
d00186d0:	3316f504 	tstcc	r6, #4, 10	; 0x1000000	; <UNPREDICTABLE>
d00186d4:	7200f503 	andvc	pc, r0, #12582912	; 0xc00000
d00186d8:	3200f8d3 	andcc	pc, r0, #13828096	; 0xd30000
d00186dc:	d3124598 	tstle	r2, #152, 10	; 0x26000000
d00186e0:	e75d6016 	smmla	sp, r6, r0, r6
d00186e4:	1c5a441c 	cfldrdne	mvd4, [sl], {28}
d00186e8:	f5042301 			; <UNDEFINED> instruction: 0xf5042301
d00186ec:	f8c5341a 			; <UNDEFINED> instruction: 0xf8c5341a
d00186f0:	f8842204 			; <UNDEFINED> instruction: 0xf8842204
d00186f4:	f7ff3208 			; <UNDEFINED> instruction: 0xf7ff3208
d00186f8:	f8d5ff25 			; <UNDEFINED> instruction: 0xf8d5ff25
d00186fc:	3b013204 	blcc	0xd0064f14
d0018700:	3204f8c5 	andcc	pc, r4, #12910592	; 0xc50000
d0018704:	792be7bb 	stmdbvc	fp!, {r0, r1, r3, r4, r5, r7, r8, r9, sl, sp, lr, pc}
d0018708:	b1536829 	cmplt	r3, r9, lsr #16
d001870c:	2000f8d9 	ldrdcs	pc, [r0], -r9
d0018710:	f8da2300 			; <UNDEFINED> instruction: 0xf8da2300
d0018714:	f1080058 	cps	#24
d0018718:	35080801 	strcc	r0, [r8, #-2049]	; 0xfffff7ff
d001871c:	fc20f7fc 	stc2	7, cr15, [r0], #-1008	; 0xfffffc10
d0018720:	463ae7d6 			; <UNDEFINED> instruction: 0x463ae7d6
d0018724:	f240e7f4 	vaba.s8	q15, q8, q10
d0018728:	46201113 			; <UNDEFINED> instruction: 0x46201113
d001872c:	fabff7fa 	blx	0xcf01671c
d0018730:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d0018734:	f8d580e5 			; <UNDEFINED> instruction: 0xf8d580e5
d0018738:	2b2031fc 	blcs	0xd0824f30
d001873c:	af79f43f 	svcge	0x0079f43f
d0018740:	2774f8df 			; <UNDEFINED> instruction: 0x2774f8df
d0018744:	46202128 	strtmi	r2, [r0], -r8, lsr #2
d0018748:	f7fa447a 			; <UNDEFINED> instruction: 0xf7fa447a
d001874c:	2800fabe 	stmdacs	r0, {r1, r2, r3, r4, r5, r7, r9, fp, ip, sp, lr, pc}
d0018750:	af26f43f 	svcge	0x0026f43f
d0018754:	31f4f8d5 	ldrsbcc	pc, [r4, #133]!	; 0x85	; <UNPREDICTABLE>
d0018758:	71ecf8d5 	ldrdvc	pc, [ip, #133]!	; 0x85
d001875c:	f8d53301 			; <UNDEFINED> instruction: 0xf8d53301
d0018760:	f8c56200 			; <UNDEFINED> instruction: 0xf8c56200
d0018764:	f7ff31f4 			; <UNDEFINED> instruction: 0xf7ff31f4
d0018768:	b978fa31 	ldmdblt	r8!, {r0, r4, r5, r9, fp, ip, sp, lr, pc}^
d001876c:	4620213b 			; <UNDEFINED> instruction: 0x4620213b
d0018770:	fa9df7fa 	blx	0xce796760
d0018774:	f7feb950 			; <UNDEFINED> instruction: 0xf7feb950
d0018778:	f8dffd77 			; <UNDEFINED> instruction: 0xf8dffd77
d001877c:	f8df2740 			; <UNDEFINED> instruction: 0xf8df2740
d0018780:	213b0740 	teqcs	fp, r0, asr #14
d0018784:	4478447a 	ldrbtmi	r4, [r8], #-1146	; 0xfffffb86
d0018788:	fa9ff7fa 	blx	0xce816778
d001878c:	4734f8df 			; <UNDEFINED> instruction: 0x4734f8df
d0018790:	53f8f64d 	mvnspl	pc, #80740352	; 0x4d00000
d0018794:	f854447c 			; <UNDEFINED> instruction: 0xf854447c
d0018798:	6ae39003 	bvs	0xcf8fc7ac
d001879c:	f0002b3b 			; <UNDEFINED> instruction: 0xf0002b3b
d00187a0:	2202808c 	andcs	r8, r2, #140	; 0x8c
d00187a4:	46202101 	strtmi	r2, [r0], -r1, lsl #2
d00187a8:	fe68f7fd 	mcr2	7, 3, pc, cr8, cr13, {7}	; <UNPREDICTABLE>
d00187ac:	46202100 	strtmi	r2, [r0], -r0, lsl #2
d00187b0:	fe68f7fb 	mcr2	7, 3, pc, cr8, cr11, {7}	; <UNPREDICTABLE>
d00187b4:	f8df4605 			; <UNDEFINED> instruction: 0xf8df4605
d00187b8:	213b4710 	teqcs	fp, r0, lsl r7
d00187bc:	270cf8df 			; <UNDEFINED> instruction: 0x270cf8df
d00187c0:	447a447c 	ldrbtmi	r4, [sl], #-1148	; 0xfffffb84
d00187c4:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d00187c8:	4620fa80 	strtmi	pc, [r0], -r0, lsl #21
d00187cc:	fe4ef7fb 	mcr2	7, 2, pc, cr14, cr11, {7}	; <UNPREDICTABLE>
d00187d0:	53f8f64d 	mvnspl	pc, #80740352	; 0x4d00000
d00187d4:	f8544682 			; <UNDEFINED> instruction: 0xf8544682
d00187d8:	6ae38003 	bvs	0xcf8f87ec
d00187dc:	d0012b29 	andle	r2, r1, r9, lsr #22
d00187e0:	fd42f7fe 	stc2l	7, cr15, [r2, #-1016]	; 0xfffffc08
d00187e4:	46e8f8df 	usatmi	pc, #8, pc, asr #17	; <UNPREDICTABLE>
d00187e8:	f8df2129 			; <UNDEFINED> instruction: 0xf8df2129
d00187ec:	447c26e8 	ldrbtmi	r2, [ip], #-1768	; 0xfffff918
d00187f0:	4620447a 			; <UNDEFINED> instruction: 0x4620447a
d00187f4:	fa69f7fa 	blx	0xd1a967e4
d00187f8:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d00187fc:	464afe37 			; <UNDEFINED> instruction: 0x464afe37
d0018800:	23004601 	movwcs	r4, #1537	; 0x601
d0018804:	f5046da0 			; <UNDEFINED> instruction: 0xf5046da0
d0018808:	f7fc391a 			; <UNDEFINED> instruction: 0xf7fc391a
d001880c:	f64dfba9 			; <UNDEFINED> instruction: 0xf64dfba9
d0018810:	230052f8 	movwcs	r5, #760	; 0x2f8
d0018814:	58a24651 	stmiapl	r2!, {r0, r4, r6, r9, sl, lr}
d0018818:	f7fc6da0 			; <UNDEFINED> instruction: 0xf7fc6da0
d001881c:	f504fba1 			; <UNDEFINED> instruction: 0xf504fba1
d0018820:	f8d23216 			; <UNDEFINED> instruction: 0xf8d23216
d0018824:	330131fc 	movwcc	r3, #4604	; 0x11fc
d0018828:	31fcf8c2 	mvnscc	pc, r2, asr #17
d001882c:	3204f8d9 	andcc	pc, r4, #14221312	; 0xd90000
d0018830:	d1442b40 	cmple	r4, r0, asr #22
d0018834:	16a0f8df 	ssatne	pc, #1, pc, asr #17	; <UNPREDICTABLE>
d0018838:	44794620 	ldrbtmi	r4, [r9], #-1568	; 0xfffff9e0
d001883c:	fcb4f7f7 	ldc2	7, cr15, [r4], #988	; 0x3dc
d0018840:	4698f8df 			; <UNDEFINED> instruction: 0x4698f8df
d0018844:	f504447c 			; <UNDEFINED> instruction: 0xf504447c
d0018848:	46203216 			; <UNDEFINED> instruction: 0x46203216
d001884c:	31fcf8d2 	ldrsbcc	pc, [ip, #130]!	; 0x82	; <UNPREDICTABLE>
d0018850:	f8c23b01 			; <UNDEFINED> instruction: 0xf8c23b01
d0018854:	f7fb31fc 			; <UNDEFINED> instruction: 0xf7fb31fc
d0018858:	2300fe09 	movwcs	pc, #3593	; 0xe09	; <UNPREDICTABLE>
d001885c:	46424601 	strbmi	r4, [r2], -r1, lsl #12
d0018860:	f7fc6da0 			; <UNDEFINED> instruction: 0xf7fc6da0
d0018864:	b13dfb7d 	teqlt	sp, sp, ror fp	; <UNPREDICTABLE>
d0018868:	52f8f64d 	rscspl	pc, r8, #80740352	; 0x4d00000
d001886c:	46292300 	strtmi	r2, [r9], -r0, lsl #6
d0018870:	58a26da0 	stmiapl	r2!, {r5, r7, r8, sl, fp, sp, lr}
d0018874:	fb74f7fc 	blx	0xd1d5686e
d0018878:	f8df00f4 			; <UNDEFINED> instruction: 0xf8df00f4
d001887c:	f8df5664 			; <UNDEFINED> instruction: 0xf8df5664
d0018880:	46b1b664 	ldrtmi	fp, [r1], r4, ror #12
d0018884:	f504447d 			; <UNDEFINED> instruction: 0xf504447d
d0018888:	44fb3416 	ldrbtmi	r3, [fp], #1046	; 0x416
d001888c:	7401f504 	strvc	pc, [r1], #-1284	; 0xfffffafc
d0018890:	4a5df505 	bmi	0xd1795cac
d0018894:	f10a442c 			; <UNDEFINED> instruction: 0xf10a442c
d0018898:	f5050af8 			; <UNDEFINED> instruction: 0xf5050af8
d001889c:	f8d33316 			; <UNDEFINED> instruction: 0xf8d33316
d00188a0:	45891200 	strmi	r1, [r9, #512]	; 0x200
d00188a4:	f8d3d31c 			; <UNDEFINED> instruction: 0xf8d3d31c
d00188a8:	f8c321f4 			; <UNDEFINED> instruction: 0xf8c321f4
d00188ac:	3a016200 	bcc	0xd00710b4
d00188b0:	71ecf8c3 	mvnvc	pc, r3, asr #17
d00188b4:	21f4f8c3 	mvnscs	pc, r3, asr #17
d00188b8:	2500e672 	strcs	lr, [r0, #-1650]	; 0xfffff98e
d00188bc:	441ce77b 	ldrmi	lr, [ip], #-1915	; 0xfffff885
d00188c0:	23011c5a 	movwcs	r1, #7258	; 0x1c5a
d00188c4:	341af504 	ldrcc	pc, [sl], #-1284	; 0xfffffafc
d00188c8:	2204f8c9 	andcs	pc, r4, #13172736	; 0xc90000
d00188cc:	3208f884 	andcc	pc, r8, #132, 16	; 0x840000
d00188d0:	fe38f7ff 	mrc2	7, 1, pc, cr8, cr15, {7}
d00188d4:	3204f8d9 	andcc	pc, r4, #14221312	; 0xd90000
d00188d8:	f8c93b01 			; <UNDEFINED> instruction: 0xf8c93b01
d00188dc:	e7af3204 	str	r3, [pc, r4, lsl #4]!
d00188e0:	68217923 	stmdavs	r1!, {r0, r1, r5, r8, fp, ip, sp, lr}
d00188e4:	f8dab153 			; <UNDEFINED> instruction: 0xf8dab153
d00188e8:	23002000 	movwcs	r2, #0
d00188ec:	0058f8db 	ldrsbeq	pc, [r8], #-139	; 0xffffff75	; <UNPREDICTABLE>
d00188f0:	0901f109 	stmdbeq	r1, {r0, r3, r8, ip, sp, lr, pc}
d00188f4:	f7fc3408 			; <UNDEFINED> instruction: 0xf7fc3408
d00188f8:	e7cefb33 			; <UNDEFINED> instruction: 0xe7cefb33
d00188fc:	e7f44642 	ldrb	r4, [r4, r2, asr #12]!
d0018900:	718af44f 	orrvc	pc, sl, pc, asr #8
d0018904:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0018908:	4607f9d2 			; <UNDEFINED> instruction: 0x4607f9d2
d001890c:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d0018910:	f50481f8 			; <UNDEFINED> instruction: 0xf50481f8
d0018914:	f8d3331a 			; <UNDEFINED> instruction: 0xf8d3331a
d0018918:	2b403204 	blcs	0xd1025130
d001891c:	f8dfd103 			; <UNDEFINED> instruction: 0xf8dfd103
d0018920:	447915c8 	ldrbtmi	r1, [r9], #-1480	; 0xfffffa38
d0018924:	f504e624 			; <UNDEFINED> instruction: 0xf504e624
d0018928:	f8d3331e 			; <UNDEFINED> instruction: 0xf8d3331e
d001892c:	f5b3324c 			; <UNDEFINED> instruction: 0xf5b3324c
d0018930:	93007f80 	movwls	r7, #3968	; 0xf80
d0018934:	f8dfd103 			; <UNDEFINED> instruction: 0xf8dfd103
d0018938:	447915b4 	ldrbtmi	r1, [r9], #-1460	; 0xfffffa4c
d001893c:	f8d5e618 			; <UNDEFINED> instruction: 0xf8d5e618
d0018940:	2b4031ec 	blcs	0xd10250f8
d0018944:	d1109301 	tstle	r0, r1, lsl #6
d0018948:	15a4f8df 	strne	pc, [r4, #2271]!	; 0x8df
d001894c:	05a4f8df 	streq	pc, [r4, #2271]!	; 0x8df
d0018950:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d0018954:	fc28f7f7 	stc2	7, cr15, [r8], #-988	; 0xfffffc24
d0018958:	359cf8df 	ldrcc	pc, [ip, #2271]	; 0x8df
d001895c:	447b9a01 	ldrbtmi	r9, [fp], #-2561	; 0xfffff5ff
d0018960:	3316f503 	tstcc	r6, #12582912	; 0xc00000	; <UNPREDICTABLE>
d0018964:	21ecf8c3 	mvncs	pc, r3, asr #17
d0018968:	f8dfe61a 			; <UNDEFINED> instruction: 0xf8dfe61a
d001896c:	21284590 			; <UNDEFINED> instruction: 0x21284590
d0018970:	258cf8df 	strcs	pc, [ip, #2271]	; 0x8df
d0018974:	447a447c 	ldrbtmi	r4, [sl], #-1148	; 0xfffffb84
d0018978:	331af504 	tstcc	sl, #4, 10	; 0x1000000	; <UNPREDICTABLE>
d001897c:	f8d34620 			; <UNDEFINED> instruction: 0xf8d34620
d0018980:	93023248 	movwls	r3, #8776	; 0x2248
d0018984:	f9a1f7fa 			; <UNDEFINED> instruction: 0xf9a1f7fa
d0018988:	d0e52800 	rscle	r2, r5, r0, lsl #16
d001898c:	46202201 	strtmi	r2, [r0], -r1, lsl #4
d0018990:	f7fd4611 			; <UNDEFINED> instruction: 0xf7fd4611
d0018994:	f8dffd73 			; <UNDEFINED> instruction: 0xf8dffd73
d0018998:	2129256c 			; <UNDEFINED> instruction: 0x2129256c
d001899c:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d00189a0:	f993f7fa 			; <UNDEFINED> instruction: 0xf993f7fa
d00189a4:	d0d72800 	sbcsle	r2, r7, r0, lsl #16
d00189a8:	255cf8df 	ldrbcs	pc, [ip, #-2271]	; 0xfffff721	; <UNPREDICTABLE>
d00189ac:	4620217b 			; <UNDEFINED> instruction: 0x4620217b
d00189b0:	f7fa447a 			; <UNDEFINED> instruction: 0xf7fa447a
d00189b4:	2800f98a 	stmdacs	r0, {r1, r3, r7, r8, fp, ip, sp, lr, pc}
d00189b8:	f504d0ce 			; <UNDEFINED> instruction: 0xf504d0ce
d00189bc:	21003416 	tstcs	r0, r6, lsl r4
d00189c0:	81ecf8d4 	ldrdhi	pc, [ip, #132]!	; 0x84
d00189c4:	21f0f8d4 	ldrsbcs	pc, [r0, #132]!	; 0x84	; <UNPREDICTABLE>
d00189c8:	0301f108 	movweq	pc, #4360	; 0x1108	; <UNPREDICTABLE>
d00189cc:	f8c44293 			; <UNDEFINED> instruction: 0xf8c44293
d00189d0:	f04f31ec 			; <UNDEFINED> instruction: 0xf04f31ec
d00189d4:	bf88022c 	svclt	0x0088022c
d00189d8:	31f0f8c4 	mvnscc	pc, r4, asr #17
d00189dc:	452cf8df 	strmi	pc, [ip, #-2271]!	; 0xfffff721
d00189e0:	fb02447c 	blx	0xd00a9bda
d00189e4:	f5044508 			; <UNDEFINED> instruction: 0xf5044508
d00189e8:	f5053616 			; <UNDEFINED> instruction: 0xf5053616
d00189ec:	f8963513 			; <UNDEFINED> instruction: 0xf8963513
d00189f0:	f50571f4 			; <UNDEFINED> instruction: 0xf50571f4
d00189f4:	f003703b 			; <UNDEFINED> instruction: 0xf003703b
d00189f8:	230bfd33 	movwcs	pc, #48435	; 0xbd33	; <UNPREDICTABLE>
d00189fc:	46412200 	strbmi	r2, [r1], -r0, lsl #4
d0018a00:	330df885 	movwcc	pc, #55429	; 0xd885	; <UNPREDICTABLE>
d0018a04:	f8854620 			; <UNDEFINED> instruction: 0xf8854620
d0018a08:	f7fb730c 			; <UNDEFINED> instruction: 0xf7fb730c
d0018a0c:	f7fbfc31 			; <UNDEFINED> instruction: 0xf7fbfc31
d0018a10:	f8d6fd2d 			; <UNDEFINED> instruction: 0xf8d6fd2d
d0018a14:	f50431f4 			; <UNDEFINED> instruction: 0xf50431f4
d0018a18:	ee08321a 	mcr	2, 0, r3, cr8, cr10, {0}
d0018a1c:	33010a10 	movwcc	r0, #6672	; 0x1a10
d0018a20:	31f4f8c6 	mvnscc	pc, r6, asr #17
d0018a24:	f8d22600 			; <UNDEFINED> instruction: 0xf8d22600
d0018a28:	46373204 	ldrtmi	r3, [r7], -r4, lsl #4
d0018a2c:	1c59441c 	cfldrdne	mvd4, [r9], {28}
d0018a30:	f5042302 			; <UNDEFINED> instruction: 0xf5042302
d0018a34:	f8c2341a 			; <UNDEFINED> instruction: 0xf8c2341a
d0018a38:	f8841204 			; <UNDEFINED> instruction: 0xf8841204
d0018a3c:	f8df3208 			; <UNDEFINED> instruction: 0xf8df3208
d0018a40:	447b34d0 	ldrbtmi	r3, [fp], #-1232	; 0xfffffb30
d0018a44:	351cf503 	ldrcc	pc, [ip, #-1283]	; 0xfffffafd
d0018a48:	7514f505 	ldrvc	pc, [r4, #-1285]	; 0xfffffafb
d0018a4c:	44c4f8df 	strbmi	pc, [r4], #2271	; 0x8df	; <UNPREDICTABLE>
d0018a50:	6da3447c 	cfstrsvs	mvf4, [r3, #496]!	; 0x1f0
d0018a54:	6ae3bb23 	bvs	0xcf9076e8
d0018a58:	d0212b7d 	eorle	r2, r1, sp, ror fp
d0018a5c:	7f80f5b3 	svcvc	0x0080f5b3
d0018a60:	f240d01e 	vqadd.s8	d29, d0, d14
d0018a64:	42931215 	addsmi	r1, r3, #1342177281	; 0x50000001
d0018a68:	80eef040 	rschi	pc, lr, r0, asr #32
d0018a6c:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0018a70:	6a63f903 	bvs	0xd1916e84
d0018a74:	4620212d 	strtmi	r2, [r0], -sp, lsr #2
d0018a78:	6aa39303 	bvs	0xce8fd68c
d0018a7c:	a030f894 	mlasge	r0, r4, r8, pc	; <UNPREDICTABLE>
d0018a80:	6b639304 	blvs	0xd18fd698
d0018a84:	f7fa9305 			; <UNDEFINED> instruction: 0xf7fa9305
d0018a88:	6ae3f912 	bvs	0xcf916ed8
d0018a8c:	7381f5a3 	orrvc	pc, r1, #683671552	; 0x28c00000
d0018a90:	d9752b01 	ldmdble	r5!, {r0, r8, r9, fp, sp}^
d0018a94:	1480f8df 	strne	pc, [r0], #2271	; 0x8df
d0018a98:	44794620 	ldrbtmi	r4, [r9], #-1568	; 0xfffff9e0
d0018a9c:	fb84f7f7 	blx	0xce156a82
d0018aa0:	4478f8df 	ldrbtmi	pc, [r8], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d0018aa4:	f8df217d 			; <UNDEFINED> instruction: 0xf8df217d
d0018aa8:	447c2478 	ldrbtmi	r2, [ip], #-1144	; 0xfffffb88
d0018aac:	4620447a 			; <UNDEFINED> instruction: 0x4620447a
d0018ab0:	3b1ef504 	blcc	0xd07d5ec8
d0018ab4:	f909f7fa 			; <UNDEFINED> instruction: 0xf909f7fa
d0018ab8:	321af504 	andscc	pc, sl, #4, 10	; 0x1000000
d0018abc:	f8d24620 			; <UNDEFINED> instruction: 0xf8d24620
d0018ac0:	3b013204 	blcc	0xd00652d8
d0018ac4:	3204f8c2 	andcc	pc, r4, #12713984	; 0xc20000
d0018ac8:	3216f504 	andscc	pc, r6, #4, 10	; 0x1000000
d0018acc:	31f4f8d2 	ldrsbcc	pc, [r4, #130]!	; 0x82	; <UNPREDICTABLE>
d0018ad0:	f8c23b01 			; <UNDEFINED> instruction: 0xf8c23b01
d0018ad4:	f7fb31f4 			; <UNDEFINED> instruction: 0xf7fb31f4
d0018ad8:	f64dfcc9 			; <UNDEFINED> instruction: 0xf64dfcc9
d0018adc:	230052f8 	movwcs	r5, #760	; 0x2f8
d0018ae0:	ee184681 	cfmsub32	mvax4, mvfx4, mvfx8, mvfx1
d0018ae4:	58a21a10 	stmiapl	r2!, {r4, r9, fp, ip}
d0018ae8:	f7fc6da0 			; <UNDEFINED> instruction: 0xf7fc6da0
d0018aec:	9b00fa39 	blls	0xd00573d8
d0018af0:	05c3eb04 	strbeq	lr, [r3, #2820]	; 0xb04
d0018af4:	f505469a 			; <UNDEFINED> instruction: 0xf505469a
d0018af8:	f505351c 			; <UNDEFINED> instruction: 0xf505351c
d0018afc:	f8db7513 			; <UNDEFINED> instruction: 0xf8db7513
d0018b00:	3508324c 	strcc	r3, [r8, #-588]	; 0xfffffdb4
d0018b04:	f0c0459a 			; <UNDEFINED> instruction: 0xf0c0459a
d0018b08:	462080d1 			; <UNDEFINED> instruction: 0x462080d1
d0018b0c:	f0002f00 			; <UNDEFINED> instruction: 0xf0002f00
d0018b10:	f7fb80eb 			; <UNDEFINED> instruction: 0xf7fb80eb
d0018b14:	4601fcab 	strmi	pc, [r1], -fp, lsr #25
d0018b18:	24006da0 	strcs	r6, [r0], #-3488	; 0xfffff260
d0018b1c:	463a2300 	ldrtmi	r2, [sl], -r0, lsl #6
d0018b20:	fa1ef7fc 	blx	0xd07d6b18
d0018b24:	f64d4dff 			; <UNDEFINED> instruction: 0xf64d4dff
d0018b28:	464953f8 			; <UNDEFINED> instruction: 0x464953f8
d0018b2c:	f855447d 			; <UNDEFINED> instruction: 0xf855447d
d0018b30:	2300a003 	movwcs	sl, #3
d0018b34:	46526da8 	ldrbmi	r6, [r2], -r8, lsr #27
d0018b38:	fa12f7fc 	blx	0xd04d6b30
d0018b3c:	2300b12c 	movwcs	fp, #300	; 0x12c
d0018b40:	46214652 			; <UNDEFINED> instruction: 0x46214652
d0018b44:	f7fc6da8 			; <UNDEFINED> instruction: 0xf7fc6da8
d0018b48:	4cf7fa0b 	vldmiami	r7!, {s31-s41}
d0018b4c:	447c9d02 	ldrbtmi	r9, [ip], #-3330	; 0xfffff2fe
d0018b50:	381af504 	ldmdacc	sl, {r2, r8, sl, ip, sp, lr, pc}
d0018b54:	7713f508 	ldrvc	pc, [r3, -r8, lsl #10]
d0018b58:	2248f8d8 	subcs	pc, r8, #216, 16	; 0xd80000
d0018b5c:	f0c04295 			; <UNDEFINED> instruction: 0xf0c04295
d0018b60:	9a0280c7 	bls	0xd00b8e84
d0018b64:	331ef504 	tstcc	lr, #4, 10	; 0x1000000	; <UNPREDICTABLE>
d0018b68:	2248f8c8 	subcs	pc, r8, #200, 16	; 0xc80000
d0018b6c:	f8c39a00 			; <UNDEFINED> instruction: 0xf8c39a00
d0018b70:	2e00224c 	cdpcs	2, 0, cr2, cr0, cr12, {2}
d0018b74:	aef0f47f 	mrcge	4, 7, APSR_nzcv, cr0, cr15, {3}
d0018b78:	462049ec 	strtmi	r4, [r0], -ip, ror #19
d0018b7c:	e6e94479 	uxtab	r4, r9, r9, ror #8
d0018b80:	9020f8d4 	ldrdls	pc, [r0], -r4	; <UNPREDICTABLE>
d0018b84:	f1c9b108 			; <UNDEFINED> instruction: 0xf1c9b108
d0018b88:	4ce90900 			; <UNDEFINED> instruction: 0x4ce90900
d0018b8c:	4620447c 			; <UNDEFINED> instruction: 0x4620447c
d0018b90:	f872f7fa 			; <UNDEFINED> instruction: 0xf872f7fa
d0018b94:	213a4ae7 	teqcs	sl, r7, ror #21
d0018b98:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d0018b9c:	f895f7fa 			; <UNDEFINED> instruction: 0xf895f7fa
d0018ba0:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0018ba4:	6ea2af7d 	mcrvs	15, 5, sl, cr2, cr13, {3}
d0018ba8:	331ef504 	tstcc	lr, #4, 10	; 0x1000000	; <UNPREDICTABLE>
d0018bac:	920649e2 	andls	r4, r6, #3702784	; 0x388000
d0018bb0:	f8d34479 			; <UNDEFINED> instruction: 0xf8d34479
d0018bb4:	9a00324c 	bls	0xd00254ec
d0018bb8:	e9d49107 	ldmib	r4, {r0, r1, r2, r8, ip, pc}^
d0018bbc:	e9d40e16 	ldmib	r4, {r1, r2, r4, r9, sl, fp}^
d0018bc0:	2400cb18 	strcs	ip, [r0], #-2840	; 0xfffff4e8
d0018bc4:	d31b429a 	tstle	fp, #-1610612727	; 0xa0000009
d0018bc8:	4adcb13c 	bmi	0xcf7450c0
d0018bcc:	447a9906 	ldrbtmi	r9, [sl], #-2310	; 0xfffff6fa
d0018bd0:	0e16e9c2 	vnmlaeq.f16	s28, s13, s4	; <UNPREDICTABLE>
d0018bd4:	cb18e9c2 	blgt	0xd06532e4
d0018bd8:	f5b36691 			; <UNDEFINED> instruction: 0xf5b36691
d0018bdc:	d11f7f80 	tstle	pc, r0, lsl #31
d0018be0:	447b4bd7 	ldrbtmi	r4, [fp], #-3031	; 0xfffff429
d0018be4:	b94a6d9a 	stmdblt	sl, {r1, r3, r4, r7, r8, sl, fp, sp, lr}^
d0018be8:	447a4ad6 	ldrbtmi	r4, [sl], #-2774	; 0xfffff52a
d0018bec:	9a03659a 	bls	0xd00f225c
d0018bf0:	9a0465da 	bls	0xd0132360
d0018bf4:	2a18e9c3 	bcs	0xd0653308
d0018bf8:	669a9a05 	ldrvs	r9, [sl], r5, lsl #20
d0018bfc:	e7253601 	str	r3, [r5, -r1, lsl #12]!
d0018c00:	1032f855 	eorsne	pc, r2, r5, asr r8	; <UNPREDICTABLE>
d0018c04:	d1094549 	tstle	r9, r9, asr #10
d0018c08:	9905b940 	stmdbls	r5, {r6, r8, fp, ip, sp, pc}
d0018c0c:	f8dd46d3 			; <UNDEFINED> instruction: 0xf8dd46d3
d0018c10:	2401c010 	strcs	ip, [r1], #-16
d0018c14:	e00cf8dd 	ldrd	pc, [ip], -sp
d0018c18:	91069807 	tstls	r6, r7, lsl #16
d0018c1c:	e7d13201 	ldrb	r3, [r1, r1, lsl #4]
d0018c20:	4ac91c58 	bmi	0xcf25fd88
d0018c24:	439cf503 	orrsmi	pc, ip, #12582912	; 0xc00000
d0018c28:	3349447a 	movtcc	r4, #38010	; 0x947a
d0018c2c:	311ef502 	tstcc	lr, r2, lsl #10	; <UNPREDICTABLE>
d0018c30:	03c3eb02 	biceq	lr, r3, #2048	; 0x800
d0018c34:	425df502 	subsmi	pc, sp, #8388608	; 0x800000
d0018c38:	024cf8c1 	subeq	pc, ip, #12648448	; 0xc10000
d0018c3c:	f8c332f8 			; <UNDEFINED> instruction: 0xf8c332f8
d0018c40:	68129008 	ldmdavs	r2, {r3, ip, pc}
d0018c44:	e7d9605a 			; <UNDEFINED> instruction: 0xe7d9605a
d0018c48:	718bf44f 	orrvc	pc, fp, pc, asr #8
d0018c4c:	f7fa4620 			; <UNDEFINED> instruction: 0xf7fa4620
d0018c50:	b318f82e 	tstlt	r8, #3014656	; 0x2e0000	; <UNPREDICTABLE>
d0018c54:	213a4abd 	teqcs	sl, sp	; <illegal shifter operand>
d0018c58:	46206a63 	strtmi	r6, [r0], -r3, ror #20
d0018c5c:	f8d4447a 			; <UNDEFINED> instruction: 0xf8d4447a
d0018c60:	f894b028 			; <UNDEFINED> instruction: 0xf894b028
d0018c64:	f8d4a030 			; <UNDEFINED> instruction: 0xf8d4a030
d0018c68:	93039034 	movwls	r9, #12340	; 0x3034
d0018c6c:	f82df7fa 			; <UNDEFINED> instruction: 0xf82df7fa
d0018c70:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0018c74:	b167af15 	cmnlt	r7, r5, lsl pc
d0018c78:	2a006da2 	bcs	0xd0034308
d0018c7c:	4ab4d1be 	bmi	0xced4d37c
d0018c80:	447a9b03 	ldrbtmi	r9, [sl], #-2819	; 0xfffff4fd
d0018c84:	9068f8c4 	rsbls	pc, r8, r4, asr #17
d0018c88:	65a265e3 	strvs	r6, [r2, #1507]!	; 0x5e3
d0018c8c:	ba18e9c4 	blt	0xd06533a4
d0018c90:	f504e7b4 			; <UNDEFINED> instruction: 0xf504e7b4
d0018c94:	f8d4445d 			; <UNDEFINED> instruction: 0xf8d4445d
d0018c98:	e7af70f8 			; <UNDEFINED> instruction: 0xe7af70f8
d0018c9c:	ff96f7fe 			; <UNDEFINED> instruction: 0xff96f7fe
d0018ca0:	f47f2800 			; <UNDEFINED> instruction: 0xf47f2800
d0018ca4:	f7ffaed3 			; <UNDEFINED> instruction: 0xf7ffaed3
d0018ca8:	e6cffc4d 	strb	pc, [pc], sp, asr #24	; <UNPREDICTABLE>
d0018cac:	46414620 	strbmi	r4, [r1], -r0, lsr #12
d0018cb0:	fdc2f7fb 	stc2l	7, cr15, [r2, #1004]	; 0x3ec
d0018cb4:	2c04f855 	stccs	8, cr15, [r4], {85}	; 0x55
d0018cb8:	f10a2101 			; <UNDEFINED> instruction: 0xf10a2101
d0018cbc:	f7fb0a01 			; <UNDEFINED> instruction: 0xf7fb0a01
d0018cc0:	4620fa5f 			; <UNDEFINED> instruction: 0x4620fa5f
d0018cc4:	2188f244 	orrcs	pc, r8, r4, asr #4
d0018cc8:	fa3cf7fb 	blx	0xd0f56cbc
d0018ccc:	1101f24d 	tstne	r1, sp, asr #4	; <UNPREDICTABLE>
d0018cd0:	fa38f7fb 	blx	0xd0e56cc4
d0018cd4:	fbcaf7fb 	blx	0xcf2d6cca
d0018cd8:	46012300 	strmi	r2, [r1], -r0, lsl #6
d0018cdc:	2c08f855 	stccs	8, cr15, [r8], {85}	; 0x55
d0018ce0:	f7fc6da0 			; <UNDEFINED> instruction: 0xf7fc6da0
d0018ce4:	e70af93d 	smuadx	sl, sp, r9
d0018ce8:	fbc0f7fb 	blx	0xcf056cde
d0018cec:	e7194604 	ldr	r4, [r9, -r4, lsl #12]
d0018cf0:	1025f857 	eorne	pc, r5, r7, asr r8	; <UNPREDICTABLE>
d0018cf4:	46522300 	ldrbmi	r2, [r2], -r0, lsl #6
d0018cf8:	35016da0 	strcc	r6, [r1, #-3488]	; 0xfffff260
d0018cfc:	f930f7fc 			; <UNDEFINED> instruction: 0xf930f7fc
d0018d00:	6ae6e72a 	bvs	0xcf9d29b0
d0018d04:	7288f46f 	addvc	pc, r8, #1862270976	; 0x6f000000
d0018d08:	2b0118b3 	blcs	0xd005efdc
d0018d0c:	f240d866 	vadd.i8	<illegal reg q14.5>, q0, q11
d0018d10:	429e1311 	addsmi	r1, lr, #1140850688	; 0x44000000
d0018d14:	f8d5d00e 			; <UNDEFINED> instruction: 0xf8d5d00e
d0018d18:	b1ab31fc 	strdlt	r3, [fp, ip]!
d0018d1c:	4478488d 	ldrbtmi	r4, [r8], #-2189	; 0xfffff773
d0018d20:	3316f500 	tstcc	r6, #0, 10	; <UNPREDICTABLE>
d0018d24:	3200f8d3 	andcc	pc, r0, #13828096	; 0xd30000
d0018d28:	7f00f5b3 	svcvc	0x0000f5b3
d0018d2c:	498ad123 	stmibmi	sl, {r0, r1, r5, r8, ip, lr, pc}
d0018d30:	e4844479 	str	r4, [r4], #1145	; 0x479
d0018d34:	341af504 	ldrcc	pc, [sl], #-1284	; 0xfffffafc
d0018d38:	3204f8d4 	andcc	pc, r4, #212, 16	; 0xd40000
d0018d3c:	4987b93b 	stmibmi	r7, {r0, r1, r3, r4, r5, r8, fp, ip, sp, pc}
d0018d40:	48874479 	stmmi	r7, {r0, r3, r4, r5, r6, sl, lr}
d0018d44:	e47a4478 	ldrbt	r4, [sl], #-1144	; 0xfffffb88
d0018d48:	44794986 	ldrbtmi	r4, [r9], #-2438	; 0xfffff67a
d0018d4c:	4886e7f9 	stmmi	r6, {r0, r3, r4, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d0018d50:	44034478 	strmi	r4, [r3], #-1144	; 0xfffffb88
d0018d54:	331af503 	tstcc	sl, #12582912	; 0xc00000	; <UNPREDICTABLE>
d0018d58:	3207f893 	andcc	pc, r7, #9633792	; 0x930000
d0018d5c:	d1dd2b02 	bicsle	r2, sp, r2, lsl #22
d0018d60:	331af500 	tstcc	sl, #0, 10	; <UNPREDICTABLE>
d0018d64:	3248f8d3 	subcc	pc, r8, #13828096	; 0xd30000
d0018d68:	7f00f5b3 	svcvc	0x0000f5b3
d0018d6c:	497fd102 	ldmdbmi	pc!, {r1, r8, ip, lr, pc}^	; <UNPREDICTABLE>
d0018d70:	e4644479 	strbt	r4, [r4], #-1145	; 0xfffffb87
d0018d74:	4c7e2701 	ldclmi	7, cr2, [lr], #-4
d0018d78:	4620447c 			; <UNDEFINED> instruction: 0x4620447c
d0018d7c:	ff7cf7f9 			; <UNDEFINED> instruction: 0xff7cf7f9
d0018d80:	213b4a7c 	teqcs	fp, ip, ror sl
d0018d84:	447a4620 	ldrbtmi	r4, [sl], #-1568	; 0xfffff9e0
d0018d88:	ff9ff7f9 			; <UNDEFINED> instruction: 0xff9ff7f9
d0018d8c:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0018d90:	b177fb6d 	cmnlt	r7, sp, ror #22	; <UNPREDICTABLE>
d0018d94:	321af504 	andscc	pc, sl, #4, 10	; 0x1000000
d0018d98:	3248f8d2 	subcc	pc, r8, #13762560	; 0xd20000
d0018d9c:	f5031c59 			; <UNDEFINED> instruction: 0xf5031c59
d0018da0:	3392431a 	orrscc	r4, r2, #1744830464	; 0x68000000
d0018da4:	1248f8c2 	subne	pc, r8, #12713984	; 0xc20000
d0018da8:	0483eb04 	streq	lr, [r3], #2820	; 0xb04
d0018dac:	f7ff6060 			; <UNDEFINED> instruction: 0xf7ff6060
d0018db0:	f504bbf7 			; <UNDEFINED> instruction: 0xf504bbf7
d0018db4:	f8d23216 			; <UNDEFINED> instruction: 0xf8d23216
d0018db8:	1c593200 	lfmne	f3, 2, [r9], {-0}
d0018dbc:	4396f503 	orrsmi	pc, r6, #12582912	; 0xc00000
d0018dc0:	f8c23340 			; <UNDEFINED> instruction: 0xf8c23340
d0018dc4:	eb041200 	bl	0xd011d5cc
d0018dc8:	f24004c3 	vshl.s8	q8, <illegal reg q1.5>, q8
d0018dcc:	1af31311 	bne	0xcfcdda18
d0018dd0:	425e6060 	subsmi	r6, lr, #96	; 0x60
d0018dd4:	7226415e 	eorvc	r4, r6, #-2147483625	; 0x80000017
d0018dd8:	bbe2f7ff 	bllt	0xcf8d6ddc
d0018ddc:	110ff240 	tstne	pc, r0, asr #4	; <UNPREDICTABLE>
d0018de0:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d0018de4:	2800ff64 	stmdacs	r0, {r2, r5, r6, r8, r9, sl, fp, ip, sp, lr, pc}
d0018de8:	f504d044 			; <UNDEFINED> instruction: 0xf504d044
d0018dec:	f8943413 			; <UNDEFINED> instruction: 0xf8943413
d0018df0:	2b0132e8 	blcs	0xd0065998
d0018df4:	4c60d028 	stclmi	0, cr13, [r0], #-160	; 0xffffff60
d0018df8:	f04f2b03 			; <UNDEFINED> instruction: 0xf04f2b03
d0018dfc:	447c0101 	ldrbtmi	r0, [ip], #-257	; 0xfffffeff
d0018e00:	2204bf0c 	andcs	fp, r4, #12, 30	; 0x30
d0018e04:	46202201 	strtmi	r2, [r0], -r1, lsl #4
d0018e08:	fb38f7fd 	blx	0xd0e56e06
d0018e0c:	3313f504 	tstcc	r3, #4, 10	; 0x1000000	; <UNPREDICTABLE>
d0018e10:	32e8f893 	rsccc	pc, r8, #9633792	; 0x930000
d0018e14:	d1042b02 	tstle	r4, r2, lsl #22
d0018e18:	21c0f24b 	biccs	pc, r0, fp, asr #4
d0018e1c:	f7fb4620 			; <UNDEFINED> instruction: 0xf7fb4620
d0018e20:	4c56f991 	mrrcmi	9, 9, pc, r6, cr1	; <UNPREDICTABLE>
d0018e24:	4a56213b 	bmi	0xd15a1318
d0018e28:	447a447c 	ldrbtmi	r4, [sl], #-1148	; 0xfffffb84
d0018e2c:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d0018e30:	f504ff4c 			; <UNDEFINED> instruction: 0xf504ff4c
d0018e34:	f8d33313 			; <UNDEFINED> instruction: 0xf8d33313
d0018e38:	f5b552e4 			; <UNDEFINED> instruction: 0xf5b552e4
d0018e3c:	d10d6f80 	smlabble	sp, r0, pc, r6	; <UNPREDICTABLE>
d0018e40:	44794950 	ldrbtmi	r4, [r9], #-2384	; 0xfffff6b0
d0018e44:	bb94f7ff 	bllt	0xce556e48
d0018e48:	4478484f 	ldrbtmi	r4, [r8], #-2127	; 0xfffff7b1
d0018e4c:	2b3b6ac3 	blcs	0xd0ef3960
d0018e50:	494ed0e7 	stmdbmi	lr, {r0, r1, r2, r5, r6, r7, ip, lr, pc}^
d0018e54:	f7f74479 			; <UNDEFINED> instruction: 0xf7f74479
d0018e58:	e7e2f9a7 	strb	pc, [r2, r7, lsr #19]!	; <UNPREDICTABLE>
d0018e5c:	f5051c6a 			; <UNDEFINED> instruction: 0xf5051c6a
d0018e60:	4620450f 	strtmi	r4, [r0], -pc, lsl #10
d0018e64:	f8c335b8 			; <UNDEFINED> instruction: 0xf8c335b8
d0018e68:	f7fb22e4 			; <UNDEFINED> instruction: 0xf7fb22e4
d0018e6c:	eb04faff 	bl	0xd0157a70
d0018e70:	e79b0485 	ldr	r0, [fp, r5, lsl #9]
d0018e74:	4620213b 			; <UNDEFINED> instruction: 0x4620213b
d0018e78:	ff19f7f9 			; <UNDEFINED> instruction: 0xff19f7f9
d0018e7c:	f47f2800 			; <UNDEFINED> instruction: 0xf47f2800
d0018e80:	f7feab8f 			; <UNDEFINED> instruction: 0xf7feab8f
d0018e84:	4a42f9f1 	bmi	0xd10d7650
d0018e88:	213b4842 	teqcs	fp, r2, asr #16
d0018e8c:	4478447a 	ldrbtmi	r4, [r8], #-1146	; 0xfffffb86
d0018e90:	ff1bf7f9 			; <UNDEFINED> instruction: 0xff1bf7f9
d0018e94:	bb84f7ff 	bllt	0xce156e98
d0018e98:	000068a8 	andeq	r6, r0, r8, lsr #17
d0018e9c:	ffffcab9 			; <UNDEFINED> instruction: 0xffffcab9
d0018ea0:	00006850 	andeq	r6, r0, r0, asr r8
d0018ea4:	fffffbfd 			; <UNDEFINED> instruction: 0xfffffbfd
d0018ea8:	000067b8 			; <UNDEFINED> instruction: 0x000067b8
d0018eac:	fffffbd5 			; <UNDEFINED> instruction: 0xfffffbd5
d0018eb0:	0000676e 	andeq	r6, r0, lr, ror #14
d0018eb4:	0000676c 	andeq	r6, r0, ip, ror #14
d0018eb8:	fffffb2a 			; <UNDEFINED> instruction: 0xfffffb2a
d0018ebc:	fffffb05 			; <UNDEFINED> instruction: 0xfffffb05
d0018ec0:	0000666e 	andeq	r6, r0, lr, ror #12
d0018ec4:	00006660 	andeq	r6, r0, r0, ror #12
d0018ec8:	00006634 	andeq	r6, r0, r4, lsr r6
d0018ecc:	fffffaea 			; <UNDEFINED> instruction: 0xfffffaea
d0018ed0:	00006606 	andeq	r6, r0, r6, lsl #12
d0018ed4:	fffffadd 			; <UNDEFINED> instruction: 0xfffffadd
d0018ed8:	fffffa13 			; <UNDEFINED> instruction: 0xfffffa13
d0018edc:	000065b0 			; <UNDEFINED> instruction: 0x000065b0
d0018ee0:	00006570 	andeq	r6, r0, r0, ror r5
d0018ee4:	0000656a 	andeq	r6, r0, sl, ror #10
d0018ee8:	fffff92b 			; <UNDEFINED> instruction: 0xfffff92b
d0018eec:	fffff9af 			; <UNDEFINED> instruction: 0xfffff9af
d0018ef0:	fffff9b5 			; <UNDEFINED> instruction: 0xfffff9b5
d0018ef4:	000064a2 	andeq	r6, r0, r2, lsr #9
d0018ef8:	00006496 	muleq	r0, r6, r4
d0018efc:	00006480 	andeq	r6, r0, r0, lsl #9
d0018f00:	fffff9bd 			; <UNDEFINED> instruction: 0xfffff9bd
d0018f04:	fffff9af 			; <UNDEFINED> instruction: 0xfffff9af
d0018f08:	fffff9c2 			; <UNDEFINED> instruction: 0xfffff9c2
d0018f0c:	00006414 	andeq	r6, r0, r4, lsl r4
d0018f10:	000063b2 			; <UNDEFINED> instruction: 0x000063b2
d0018f14:	000063a4 	andeq	r6, r0, r4, lsr #7
d0018f18:	fffff8fc 			; <UNDEFINED> instruction: 0xfffff8fc
d0018f1c:	0000634a 	andeq	r6, r0, sl, asr #6
d0018f20:	fffff967 			; <UNDEFINED> instruction: 0xfffff967
d0018f24:	000062c8 	andeq	r6, r0, r8, asr #5
d0018f28:	000062a6 	andeq	r6, r0, r6, lsr #5
d0018f2c:	fffff8b6 			; <UNDEFINED> instruction: 0xfffff8b6
d0018f30:	00006268 	andeq	r6, r0, r8, ror #4
d0018f34:	fffff821 			; <UNDEFINED> instruction: 0xfffff821
d0018f38:	fffff634 			; <UNDEFINED> instruction: 0xfffff634
d0018f3c:	00006226 	andeq	r6, r0, r6, lsr #4
d0018f40:	00006212 	andeq	r6, r0, r2, lsl r2
d0018f44:	fffff6ff 			; <UNDEFINED> instruction: 0xfffff6ff
d0018f48:	000061cc 	andeq	r6, r0, ip, asr #3
d0018f4c:	fffff77d 			; <UNDEFINED> instruction: 0xfffff77d
d0018f50:	fffff772 			; <UNDEFINED> instruction: 0xfffff772
d0018f54:	000060d6 	ldrdeq	r6, [r0], -r6	; <UNPREDICTABLE>
d0018f58:	fffff743 			; <UNDEFINED> instruction: 0xfffff743
d0018f5c:	fffff4d8 			; <UNDEFINED> instruction: 0xfffff4d8
d0018f60:	000060b0 	strheq	r6, [r0], -r0
d0018f64:	fffff4b6 			; <UNDEFINED> instruction: 0xfffff4b6
d0018f68:	000060a4 	andeq	r6, r0, r4, lsr #1
d0018f6c:	fffff6ec 			; <UNDEFINED> instruction: 0xfffff6ec
d0018f70:	0000607c 	andeq	r6, r0, ip, ror r0
d0018f74:	fffff70f 			; <UNDEFINED> instruction: 0xfffff70f
d0018f78:	00005ff6 	strdeq	r5, [r0], -r6
d0018f7c:	00005fcc 	andeq	r5, r0, ip, asr #31
d0018f80:	fffff6bc 			; <UNDEFINED> instruction: 0xfffff6bc
d0018f84:	fffff6be 			; <UNDEFINED> instruction: 0xfffff6be
d0018f88:	00005faa 	andeq	r5, r0, sl, lsr #31
d0018f8c:	fffff666 			; <UNDEFINED> instruction: 0xfffff666
d0018f90:	fffff695 			; <UNDEFINED> instruction: 0xfffff695
d0018f94:	00005f66 	andeq	r5, r0, r6, ror #30

Disassembly of section .text.sidc_compile_project.part.0:

d0019764 <.text.sidc_compile_project.part.0>:
d0019764:	4ff0e92d 	svcmi	0x00f0e92d
d0019768:	8b02ed2d 	blhi	0xd00d4c24
d001976c:	931cb0db 	tstls	ip, #219	; 0xdb
d0019770:	90172300 	andsls	r2, r7, r0, lsl #6
d0019774:	92193004 	andsls	r3, r9, #4
d0019778:	9118461a 	tstls	r8, sl, lsl r6
d001977c:	428b9919 	addmi	r9, fp, #409600	; 0x64000
d0019780:	4c9dd139 	ldfmid	f5, [sp], {57}	; 0x39
d0019784:	4a9b2100 	bmi	0xce6e1b8c
d0019788:	4620447c 			; <UNDEFINED> instruction: 0x4620447c
d001978c:	fe68f002 	cdp2	0, 6, cr15, cr8, cr2, {0}
d0019790:	489a9b66 	ldmmi	sl, {r1, r2, r5, r6, r8, r9, fp, ip, pc}
d0019794:	66e322bc 			; <UNDEFINED> instruction: 0x66e322bc
d0019798:	44789b1c 	ldrbtmi	r9, [r8], #-2844	; 0xfffff4e4
d001979c:	67234998 			; <UNDEFINED> instruction: 0x67234998
d00197a0:	33fff04f 	mvnscc	pc, #79	; 0x4f
d00197a4:	30404479 	subcc	r4, r0, r9, ror r4
d00197a8:	f00267a3 			; <UNDEFINED> instruction: 0xf00267a3
d00197ac:	f64dfe67 			; <UNDEFINED> instruction: 0xf64dfe67
d00197b0:	22bc53f8 	adcscs	r5, ip, #248, 6	; 0xe0000003
d00197b4:	230050e2 	movwcs	r5, #226	; 0xe2
d00197b8:	4b929316 	blmi	0xce4be418
d00197bc:	ee08447b 	mcr	4, 0, r4, cr8, cr11, {3}
d00197c0:	f5033a10 			; <UNDEFINED> instruction: 0xf5033a10
d00197c4:	33f8435d 	mvnscc	r4, #1946157057	; 0x74000001
d00197c8:	4c8f931a 	stcmi	3, cr9, [pc], {26}
d00197cc:	99169a19 	ldmdbls	r6, {r0, r3, r4, r9, fp, ip, pc}
d00197d0:	428a447c 	addmi	r4, sl, #124, 8	; 0x7c000000
d00197d4:	f0016da3 			; <UNDEFINED> instruction: 0xf0016da3
d00197d8:	b37b8315 	cmnlt	fp, #1409286144	; 0x54000000
d00197dc:	26004c8b 	strcs	r4, [r0], -fp, lsl #25
d00197e0:	822cf8df 	eorhi	pc, ip, #14614528	; 0xdf0000
d00197e4:	44f8447c 	ldrbtmi	r4, [r8], #1148	; 0x47c
d00197e8:	35fff504 	ldrbcc	pc, [pc, #1284]!	; 0xd0019cf4	; <UNPREDICTABLE>
d00197ec:	370ff504 	strcc	pc, [pc, -r4, lsl #10]
d00197f0:	f00135e0 			; <UNDEFINED> instruction: 0xf00135e0
d00197f4:	9917bb56 	ldmdbls	r7, {r1, r2, r4, r6, r8, r9, fp, ip, sp, pc}
d00197f8:	1033f851 	eorsne	pc, r3, r1, asr r8	; <UNPREDICTABLE>
d00197fc:	f850b129 			; <UNDEFINED> instruction: 0xf850b129
d0019800:	f5c21033 			; <UNDEFINED> instruction: 0xf5c21033
d0019804:	42a13400 	adcmi	r3, r1, #0, 8
d0019808:	9a19d915 	bls	0xd068fc64
d001980c:	d00f2a01 	andle	r2, pc, r1, lsl #20
d0019810:	447a4a80 	ldrbtmi	r4, [sl], #-2688	; 0xfffff580
d0019814:	24009968 	strcs	r9, [r0], #-2408	; 0xfffff698
d0019818:	2201600a 	andcs	r6, r1, #10
d001981c:	604a60cb 	subvs	r6, sl, fp, asr #1
d0019820:	610c608a 	smlabbvs	ip, sl, r0, r6
d0019824:	b05b4620 	subslt	r4, fp, r0, lsr #12
d0019828:	8b02ecbd 	blhi	0xd00d4b24
d001982c:	8ff0e8bd 	svchi	0x00f0e8bd
d0019830:	447a4a79 	ldrbtmi	r4, [sl], #-2681	; 0xfffff587
d0019834:	440ae7ee 	strmi	lr, [sl], #-2030	; 0xfffff812
d0019838:	e79f3301 	ldr	r3, [pc, r1, lsl #6]
d001983c:	9a169b16 	bls	0xd05c049c
d0019840:	9b177223 	blls	0xd05f60d4
d0019844:	3032f853 	eorscc	pc, r2, r3, asr r8	; <UNPREDICTABLE>
d0019848:	9b186023 	blls	0xd06318dc
d001984c:	f853b383 			; <UNDEFINED> instruction: 0xf853b383
d0019850:	4d723022 	ldclmi	0, cr3, [r2, #-136]!	; 0xffffff78
d0019854:	447d9916 	ldrbtmi	r9, [sp], #-2326	; 0xfffff6ea
d0019858:	676b4c71 			; <UNDEFINED> instruction: 0x676b4c71
d001985c:	33fff04f 	mvnscc	pc, #79	; 0x4f
d0019860:	4250f505 	subsmi	pc, r0, #20971520	; 0x1400000
d0019864:	4650f505 	ldrbmi	pc, [r0], -r5, lsl #10	; <UNPREDICTABLE>
d0019868:	230067ab 	movwcs	r6, #1963	; 0x7ab
d001986c:	361c4628 	ldrcc	r4, [ip], -r8, lsr #12
d0019870:	f50560d3 			; <UNDEFINED> instruction: 0xf50560d3
d0019874:	f8c5424f 			; <UNDEFINED> instruction: 0xf8c5424f
d0019878:	447c31fc 	ldrbtmi	r3, [ip], #-508	; 0xfffffe04
d001987c:	3088f8c2 	addcc	pc, r8, r2, asr #17
d0019880:	32049a17 	andcc	r9, r4, #94208	; 0x17000
d0019884:	2031f852 	eorscs	pc, r1, r2, asr r8	; <UNPREDICTABLE>
d0019888:	230160eb 	movwcs	r6, #4331	; 0x10eb
d001988c:	e9c5606a 	stmib	r5, {r1, r3, r5, r6, sp, lr}^
d0019890:	f7f93304 			; <UNDEFINED> instruction: 0xf7f93304
d0019894:	4628f9f1 			; <UNDEFINED> instruction: 0x4628f9f1
d0019898:	f9eef7f9 			; <UNDEFINED> instruction: 0xf9eef7f9
d001989c:	6dab6aea 			; <UNDEFINED> instruction: 0x6dab6aea
d00198a0:	7f83f5b2 	svcvc	0x0083f5b2
d00198a4:	b12bd111 			; <UNDEFINED> instruction: 0xb12bd111
d00198a8:	33019b16 	movwcc	r9, #6934	; 0x1b16
d00198ac:	e78c9316 	usada8	ip, r6, r3, r9
d00198b0:	e7ce9b18 	bfi	r9, r8, (invalid: 22:14)
d00198b4:	b11b6833 	tstlt	fp, r3, lsr r8
d00198b8:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d00198bc:	e7edf9dd 	ubfx	pc, sp, #19, #14
d00198c0:	f7fa981c 			; <UNDEFINED> instruction: 0xf7fa981c
d00198c4:	2800faab 	stmdacs	r0, {r0, r1, r3, r5, r7, r9, fp, ip, sp, lr, pc}
d00198c8:	4c56d1f6 	ldfmip	f5, [r6], {246}	; 0xf6
d00198cc:	6da6447c 	cfstrsvs	mvf4, [r6, #496]!	; 0x1f0
d00198d0:	d1e92e00 	mvnle	r2, r0, lsl #28
d00198d4:	f5b36ae3 			; <UNDEFINED> instruction: 0xf5b36ae3
d00198d8:	d0e57f80 	rscle	r7, r5, r0, lsl #31
d00198dc:	1119f240 	tstne	r9, r0, asr #4	; <UNPREDICTABLE>
d00198e0:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d00198e4:	4607f9e4 	strmi	pc, [r7], -r4, ror #19
d00198e8:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d00198ec:	f1048187 			; <UNDEFINED> instruction: 0xf1048187
d00198f0:	ad220718 	stcge	7, cr0, [r2, #-96]!	; 0xffffffa0
d00198f4:	802cf8d4 	ldrdhi	pc, [ip], -r4	; <UNPREDICTABLE>
d00198f8:	9030f894 	mlasls	r0, r4, r8, pc	; <UNPREDICTABLE>
d00198fc:	c50fcf0f 	strgt	ip, [pc, #-3855]	; 0xd00189f5
d0019900:	000fe897 	muleq	pc, r7, r8	; <UNPREDICTABLE>
d0019904:	000fe885 	andeq	lr, pc, r5, lsl #17
d0019908:	f2406a63 	vpmax.s8	q11, q0, <illegal reg q9.5>
d001990c:	46201107 	strtmi	r1, [r0], -r7, lsl #2
d0019910:	6aa3930f 	bvs	0xce8fe554
d0019914:	6b639310 	blvs	0xd18fe55c
d0019918:	ba06e9d4 	blt	0xd01d4070
d001991c:	f7f99311 			; <UNDEFINED> instruction: 0xf7f99311
d0019920:	4607f9c6 	strmi	pc, [r7], -r6, asr #19
d0019924:	f0402800 			; <UNDEFINED> instruction: 0xf0402800
d0019928:	6ae68111 	bvs	0xcf9b9d74
d001992c:	7c8bf46f 	cfstrsvc	mvf15, [fp], {111}	; 0x6f
d0019930:	030ceb06 	movweq	lr, #51974	; 0xcb06
d0019934:	d8492b01 	stmdale	r9, {r0, r8, r9, fp, sp}^
d0019938:	758cf5a6 	strvc	pc, [ip, #1446]	; 0x5a6
d001993c:	426e4620 	rsbmi	r4, lr, #32, 12	; 0x2000000
d0019940:	f7f9416e 			; <UNDEFINED> instruction: 0xf7f9416e
d0019944:	f104f999 			; <UNDEFINED> instruction: 0xf104f999
d0019948:	ad220c18 	stcge	12, cr0, [r2, #-96]!	; 0xffffffa0
d001994c:	802cf8d4 	ldrdhi	pc, [ip], -r4	; <UNPREDICTABLE>
d0019950:	9030f894 	mlasls	r0, r4, r8, pc	; <UNPREDICTABLE>
d0019954:	000fe8bc 			; <UNDEFINED> instruction: 0x000fe8bc
d0019958:	e89cc50f 	ldm	ip, {r0, r1, r2, r3, r8, sl, lr, pc}
d001995c:	e885000f 	stm	r5, {r0, r1, r2, r3}
d0019960:	6a63000f 	bvs	0xd18d99a4
d0019964:	6aa3930f 	bvs	0xce8fe5a8
d0019968:	6b639310 	blvs	0xd18fe5b0
d001996c:	f2409311 	vcge.s8	d25, d0, d1
d0019970:	45981301 	ldrmi	r1, [r8, #769]	; 0x301
d0019974:	ba06e9d4 	blt	0xd01d40cc
d0019978:	4620d102 	strtmi	sp, [r0], -r2, lsl #2
d001997c:	f97cf7f9 			; <UNDEFINED> instruction: 0xf97cf7f9
d0019980:	447c4c29 	ldrbtmi	r4, [ip], #-3113	; 0xfffff3d7
d0019984:	2b7b6ae3 	blcs	0xd1ef4518
d0019988:	80e2f000 	rschi	pc, r2, r0
d001998c:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d0019990:	d1154598 			; <UNDEFINED> instruction: 0xd1154598
d0019994:	46524633 			; <UNDEFINED> instruction: 0x46524633
d0019998:	46204659 			; <UNDEFINED> instruction: 0x46204659
d001999c:	fdf8f7f6 	ldc2l	7, cr15, [r8, #984]!	; 0x3d8
d00199a0:	da541e05 	ble	0xd15211bc
d00199a4:	b94b6da3 	stmdblt	fp, {r0, r1, r5, r7, r8, sl, fp, sp, lr}^
d00199a8:	447b4b20 	ldrbtmi	r4, [fp], #-2848	; 0xfffff4e0
d00199ac:	9b0f65a3 	blls	0xd03f3040
d00199b0:	9b1065e3 	blls	0xd0433144
d00199b4:	3918e9c4 	ldmdbcc	r8, {r2, r6, r7, r8, fp, sp, lr, pc}
d00199b8:	66a39b11 	ssatvs	r9, #4, r1, lsl #22
d00199bc:	e04625ff 	strd	r2, [r6], #-95	; 0xffffffa1
d00199c0:	4620491b 			; <UNDEFINED> instruction: 0x4620491b
d00199c4:	f7f64479 			; <UNDEFINED> instruction: 0xf7f64479
d00199c8:	e7f7fbef 	ldrb	pc, [r7, pc, ror #23]!	; <UNPREDICTABLE>
d00199cc:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d00199d0:	f040429e 			; <UNDEFINED> instruction: 0xf040429e
d00199d4:	462080b7 			; <UNDEFINED> instruction: 0x462080b7
d00199d8:	1206e9d4 	andne	lr, r6, #212, 18	; 0x350000
d00199dc:	fe7df7f6 	mrc2	7, 3, pc, cr13, cr6, {7}
d00199e0:	da292800 	ble	0xd0a639e8
d00199e4:	44794913 	ldrbtmi	r4, [r9], #-2323	; 0xfffff6ed
d00199e8:	463e4620 	ldrtmi	r4, [lr], -r0, lsr #12
d00199ec:	fbdcf7f6 	blx	0xcf7579ce
d00199f0:	bf00e7e4 	svclt	0x0000e7e4
d00199f4:	00027a50 	andeq	r7, r2, r0, asr sl
d00199f8:	0000566c 	andeq	r5, r0, ip, ror #12
d00199fc:	0002d0aa 	andeq	sp, r2, sl, lsr #1
d0019a00:	00001bd6 	ldrdeq	r1, [r0], -r6
d0019a04:	00005638 	andeq	r5, r0, r8, lsr r6
d0019a08:	00005624 	andeq	r5, r0, r4, lsr #12
d0019a0c:	00005610 	andeq	r5, r0, r0, lsl r6
d0019a10:	ffffff10 			; <UNDEFINED> instruction: 0xffffff10
d0019a14:	fffff799 			; <UNDEFINED> instruction: 0xfffff799
d0019a18:	fffff762 			; <UNDEFINED> instruction: 0xfffff762
d0019a1c:	0000559e 	muleq	r0, lr, r5
d0019a20:	0000557a 	andeq	r5, r0, sl, ror r5
d0019a24:	00005528 	andeq	r5, r0, r8, lsr #10
d0019a28:	00005472 	andeq	r5, r0, r2, ror r4
d0019a2c:	fffff662 			; <UNDEFINED> instruction: 0xfffff662
d0019a30:	fffff662 			; <UNDEFINED> instruction: 0xfffff662
d0019a34:	fffff668 			; <UNDEFINED> instruction: 0xfffff668
d0019a38:	463e2324 	ldrtmi	r2, [lr], -r4, lsr #6
d0019a3c:	4000fb03 	andmi	pc, r0, r3, lsl #22
d0019a40:	30d8f500 	sbcscc	pc, r8, r0, lsl #10
d0019a44:	51ecf890 			; <UNDEFINED> instruction: 0x51ecf890
d0019a48:	f7f94620 			; <UNDEFINED> instruction: 0xf7f94620
d0019a4c:	f8dff915 			; <UNDEFINED> instruction: 0xf8dff915
d0019a50:	447c4bc0 	ldrbtmi	r4, [ip], #-3008	; 0xfffff440
d0019a54:	2b006da3 	blcs	0xd00350e8
d0019a58:	af37f47f 	svcge	0x0037f47f
d0019a5c:	9b0fb34f 	blls	0xd04067a0
d0019a60:	f88daf22 			; <UNDEFINED> instruction: 0xf88daf22
d0019a64:	ad0690a0 	stcge	0, cr9, [r6, #-640]	; 0xfffffd80
d0019a68:	9b109325 	blls	0xd043e704
d0019a6c:	3826e9cd 	stmdacc	r6!, {r0, r2, r3, r6, r7, r8, fp, sp, lr, pc}
d0019a70:	e9cd9b11 	stmib	sp, {r0, r4, r8, r9, fp, ip, pc}^
d0019a74:	9329ba22 			; <UNDEFINED> instruction: 0x9329ba22
d0019a78:	c50fcf0f 	strgt	ip, [pc, #-3855]	; 0xd0018b71
d0019a7c:	000fe897 	muleq	pc, r7, r8	; <UNPREDICTABLE>
d0019a80:	000fe885 	andeq	lr, pc, r5, lsl #17
d0019a84:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d0019a88:	ebb89604 	bl	0xcee3f2a0
d0019a8c:	bf180303 	svclt	0x00180303
d0019a90:	93052301 	movwls	r2, #21249	; 0x5301
d0019a94:	cb0fab26 	blgt	0xd0404734
d0019a98:	000fe88d 	andeq	lr, pc, sp, lsl #17
d0019a9c:	cb0fab22 	blgt	0xd040472c
d0019aa0:	ff52f7f9 			; <UNDEFINED> instruction: 0xff52f7f9
d0019aa4:	f6ff1e05 			; <UNDEFINED> instruction: 0xf6ff1e05
d0019aa8:	6da3af10 	stcvs	15, cr10, [r3, #64]!	; 0x40
d0019aac:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0019ab0:	f8dfaf0c 			; <UNDEFINED> instruction: 0xf8dfaf0c
d0019ab4:	ae2a4b60 	vnmulge.f64	d4, d10, d16
d0019ab8:	f104447c 			; <UNDEFINED> instruction: 0xf104447c
d0019abc:	cf0f0718 	svcgt	0x000f0718
d0019ac0:	e897c60f 	ldm	r7, {r0, r1, r2, r3, r9, sl, lr, pc}
d0019ac4:	e886000f 	stm	r6, {r0, r1, r2, r3}
d0019ac8:	f8df000f 			; <UNDEFINED> instruction: 0xf8df000f
d0019acc:	f2402b4c 	vqdmulh.s<illegal width 8>	q9, q0, q6
d0019ad0:	46201101 	strtmi	r1, [r0], -r1, lsl #2
d0019ad4:	f7f9447a 			; <UNDEFINED> instruction: 0xf7f9447a
d0019ad8:	2800f8f8 	stmdacs	r0, {r3, r4, r5, r6, r7, fp, ip, sp, lr, pc}
d0019adc:	aef5f43f 	mrcge	4, 7, APSR_nzcv, cr5, cr15, {1}
d0019ae0:	2b38f8df 	blcs	0xd0e57e64
d0019ae4:	4620213b 			; <UNDEFINED> instruction: 0x4620213b
d0019ae8:	f7f9447a 			; <UNDEFINED> instruction: 0xf7f9447a
d0019aec:	2800f8ee 	stmdacs	r0, {r1, r2, r3, r5, r6, r7, fp, ip, sp, lr, pc}
d0019af0:	aeebf43f 	mcrge	4, 7, pc, cr11, cr15, {1}	; <UNPREDICTABLE>
d0019af4:	ae32af2a 	cdpge	15, 3, cr10, cr2, cr10, {1}
d0019af8:	90b4f8dd 	ldrsbtls	pc, [r4], sp	; <UNPREDICTABLE>
d0019afc:	80b8f8dd 	ldrsbthi	pc, [r8], sp	; <UNPREDICTABLE>
d0019b00:	e9ddcf0f 	ldmib	sp, {r0, r1, r2, r3, r8, r9, sl, fp, lr, pc}^
d0019b04:	c60fba2a 	strgt	fp, [pc], -sl, lsr #20
d0019b08:	000fe897 	muleq	pc, r7, r8	; <UNPREDICTABLE>
d0019b0c:	000fe886 	andeq	lr, pc, r6, lsl #17
d0019b10:	46594652 			; <UNDEFINED> instruction: 0x46594652
d0019b14:	f89d4620 			; <UNDEFINED> instruction: 0xf89d4620
d0019b18:	9e3170c0 	cdpls	0, 3, cr7, cr1, cr0, {6}
d0019b1c:	fdb9f7f6 	ldc2	7, cr15, [r9, #984]!	; 0x3d8
d0019b20:	db172800 	blle	0xd05e3b28
d0019b24:	3af8f8df 	bcc	0xcfe57ea8
d0019b28:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d0019b2c:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0019b30:	f8dfaecc 			; <UNDEFINED> instruction: 0xf8dfaecc
d0019b34:	669e2af0 			; <UNDEFINED> instruction: 0x669e2af0
d0019b38:	e9c3447a 	stmib	r3, {r1, r3, r4, r5, r6, sl, lr}^
d0019b3c:	e9c38718 	stmib	r3, {r3, r4, r8, r9, sl, pc}^
d0019b40:	e6c22916 			; <UNDEFINED> instruction: 0xe6c22916
d0019b44:	1ae0f8df 	bne	0xcf857ec8
d0019b48:	e74d4479 	smlsldx	r4, sp, r9, r4
d0019b4c:	e7354637 			; <UNDEFINED> instruction: 0xe7354637
d0019b50:	e7332701 	ldr	r2, [r3, -r1, lsl #14]!
d0019b54:	46594652 			; <UNDEFINED> instruction: 0x46594652
d0019b58:	f7f64620 			; <UNDEFINED> instruction: 0xf7f64620
d0019b5c:	2800fe02 	stmdacs	r0, {r1, r9, sl, fp, ip, sp, lr, pc}
d0019b60:	4652dae0 	ldrbmi	sp, [r2], -r0, ror #21
d0019b64:	46204659 			; <UNDEFINED> instruction: 0x46204659
d0019b68:	fdb7f7f6 	ldc2	7, cr15, [r7, #984]!	; 0x3d8
d0019b6c:	db162800 	blle	0xd05a3b74
d0019b70:	fb032324 	blx	0xd00e280a
d0019b74:	f5004000 			; <UNDEFINED> instruction: 0xf5004000
d0019b78:	f89030d8 			; <UNDEFINED> instruction: 0xf89030d8
d0019b7c:	429d31ec 	addsmi	r3, sp, #236, 2	; 0x3b
d0019b80:	aea3f43f 	mcrge	4, 5, pc, cr3, cr15, {1}	; <UNPREDICTABLE>
d0019b84:	2b006da3 	blcs	0xd0035218
d0019b88:	ae9ff47f 	mrcge	4, 4, APSR_nzcv, cr15, cr15, {3}
d0019b8c:	3a9cf8df 	bcc	0xce757f10
d0019b90:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0019b94:	e9c43916 	stmib	r4, {r1, r2, r4, r8, fp, ip, sp}^
d0019b98:	66a68718 	ssatvs	r8, #7, r8, lsl #14
d0019b9c:	f504e695 			; <UNDEFINED> instruction: 0xf504e695
d0019ba0:	f8d232dd 			; <UNDEFINED> instruction: 0xf8d232dd
d0019ba4:	2b4030cc 	blcs	0xd1025edc
d0019ba8:	6da3d107 	stfvsd	f5, [r3, #28]!
d0019bac:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0019bb0:	f8dfae8c 			; <UNDEFINED> instruction: 0xf8dfae8c
d0019bb4:	447b3a7c 	ldrbtmi	r3, [fp], #-2684	; 0xfffff584
d0019bb8:	1c59e7eb 	mrrcne	7, 14, lr, r9, cr11
d0019bbc:	c008f894 	mulgt	r8, r4, r8
d0019bc0:	70e0f88d 	rscvc	pc, r0, sp, lsl #17
d0019bc4:	f8c2af32 			; <UNDEFINED> instruction: 0xf8c2af32
d0019bc8:	222410cc 	eorcs	r1, r4, #204	; 0xcc
d0019bcc:	fb029639 	blx	0xd00bf4ba
d0019bd0:	f8cd4403 			; <UNDEFINED> instruction: 0xf8cd4403
d0019bd4:	f50480d8 			; <UNDEFINED> instruction: 0xf50480d8
d0019bd8:	f8cd34d8 			; <UNDEFINED> instruction: 0xf8cd34d8
d0019bdc:	f50490d4 			; <UNDEFINED> instruction: 0xf50490d4
d0019be0:	f88476e6 			; <UNDEFINED> instruction: 0xf88476e6
d0019be4:	f88451ec 			; <UNDEFINED> instruction: 0xf88451ec
d0019be8:	e9cdc1ed 	stmib	sp, {r0, r2, r3, r5, r6, r7, r8, lr, pc}^
d0019bec:	cf0fba32 	svcgt	0x000fba32
d0019bf0:	e897c60f 	ldm	r7, {r0, r1, r2, r3, r9, sl, lr, pc}
d0019bf4:	e886000f 	stm	r6, {r0, r1, r2, r3}
d0019bf8:	e666000f 	strbt	r0, [r6], -pc
d0019bfc:	f46f6ae5 	vld1.64	{d22-d23}, [pc :128], r5
d0019c00:	182b708b 	stmdane	fp!, {r0, r1, r3, r7, ip, sp, lr}
d0019c04:	d85d2b01 	ldmdale	sp, {r0, r8, r9, fp, sp}^
d0019c08:	a04cf8d4 	ldrdge	pc, [ip], #-132	; 0xffffff7c
d0019c0c:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d0019c10:	d157459a 			; <UNDEFINED> instruction: 0xd157459a
d0019c14:	ae324620 	cfmsuba32ge	mvax1, mvax4, mvfx2, mvfx0
d0019c18:	f82ef7f9 			; <UNDEFINED> instruction: 0xf82ef7f9
d0019c1c:	0c18f104 	ldfeqd	f7, [r8], {4}
d0019c20:	b024f8d4 	ldrdlt	pc, [r4], -r4	; <UNPREDICTABLE>
d0019c24:	9028f8d4 	ldrdls	pc, [r8], -r4	; <UNPREDICTABLE>
d0019c28:	8030f894 	mlashi	r0, r4, r8, pc	; <UNPREDICTABLE>
d0019c2c:	000fe8bc 			; <UNDEFINED> instruction: 0x000fe8bc
d0019c30:	e89cc60f 	ldm	ip, {r0, r1, r2, r3, r9, sl, lr, pc}
d0019c34:	e886000f 	stm	r6, {r0, r1, r2, r3}
d0019c38:	f8df000f 			; <UNDEFINED> instruction: 0xf8df000f
d0019c3c:	465129f8 			; <UNDEFINED> instruction: 0x465129f8
d0019c40:	6b664620 	blvs	0xd19ab4c8
d0019c44:	f7f9447a 			; <UNDEFINED> instruction: 0xf7f9447a
d0019c48:	2800f840 	stmdacs	r0, {r6, fp, ip, sp, lr, pc}
d0019c4c:	ae3df43f 	mrcge	4, 1, APSR_nzcv, cr13, cr15, {1}
d0019c50:	2b7b6ae3 	blcs	0xd1ef47e4
d0019c54:	f10dd12a 			; <UNDEFINED> instruction: 0xf10dd12a
d0019c58:	96390cc8 	ldrtls	r0, [r9], -r8, asr #25
d0019c5c:	90d8f8cd 	sbcsls	pc, r8, sp, asr #17
d0019c60:	f88dae06 			; <UNDEFINED> instruction: 0xf88dae06
d0019c64:	f8cd80e0 			; <UNDEFINED> instruction: 0xf8cd80e0
d0019c68:	e8bcb0d4 	ldm	ip!, {r2, r4, r6, r7, ip, sp, pc}
d0019c6c:	c60f000f 	strgt	r0, [pc], -pc
d0019c70:	000fe89c 	muleq	pc, ip, r8	; <UNPREDICTABLE>
d0019c74:	000fe886 	andeq	lr, pc, r6, lsl #17
d0019c78:	718cf5a5 	orrvc	pc, ip, r5, lsr #11
d0019c7c:	9705ab36 	smladxls	r5, r6, fp, sl
d0019c80:	414d424d 	cmpmi	sp, sp, asr #4
d0019c84:	cb0f9504 	blgt	0xd03ff09c
d0019c88:	000fe88d 	andeq	lr, pc, sp, lsl #17
d0019c8c:	cb0fab32 	blgt	0xd040495c
d0019c90:	fe5af7f9 	mrc2	7, 2, pc, cr10, cr9, {7}
d0019c94:	2b006da3 	blcs	0xd0035328
d0019c98:	ae17f47f 	mrcge	4, 0, APSR_nzcv, cr7, cr15, {3}
d0019c9c:	2998f8df 	ldmibcs	r8, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d0019ca0:	4620213b 			; <UNDEFINED> instruction: 0x4620213b
d0019ca4:	f7f9447a 			; <UNDEFINED> instruction: 0xf7f9447a
d0019ca8:	e60ef810 			; <UNDEFINED> instruction: 0xe60ef810
d0019cac:	2b006da3 	blcs	0xd0035340
d0019cb0:	ae0bf47f 	mcrge	4, 0, pc, cr11, cr15, {3}	; <UNPREDICTABLE>
d0019cb4:	3984f8df 	stmibcc	r4, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d0019cb8:	e9c4447b 	stmib	r4, {r0, r1, r3, r4, r5, r6, sl, lr}^
d0019cbc:	e9c49818 	stmib	r4, {r3, r4, fp, ip, pc}^
d0019cc0:	e76a3b16 			; <UNDEFINED> instruction: 0xe76a3b16
d0019cc4:	5978f8df 	ldmdbpl	r8!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d0019cc8:	7183f44f 	orrvc	pc, r3, pc, asr #8
d0019ccc:	4628447d 			; <UNDEFINED> instruction: 0x4628447d
d0019cd0:	ffedf7f8 			; <UNDEFINED> instruction: 0xffedf7f8
d0019cd4:	b1504604 	cmplt	r0, r4, lsl #12
d0019cd8:	4350f505 	cmpmi	r0, #20971520	; 0x1400000	; <UNPREDICTABLE>
d0019cdc:	681b331c 	ldmdavs	fp, {r2, r3, r4, r8, r9, ip, sp}
d0019ce0:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d0019ce4:	6f28adf2 	svcvs	0x0028adf2
d0019ce8:	f898f7fa 			; <UNDEFINED> instruction: 0xf898f7fa
d0019cec:	f44fe5ed 	vst3.<illegal width 64>	{d30,d32,d34}, [pc :128]!
d0019cf0:	46287188 	strtmi	r7, [r8], -r8, lsl #3
d0019cf4:	ffdbf7f8 			; <UNDEFINED> instruction: 0xffdbf7f8
d0019cf8:	46289014 			; <UNDEFINED> instruction: 0x46289014
d0019cfc:	fd12f7f6 	ldc2	7, cr15, [r2, #-984]	; 0xfffffc28
d0019d00:	28009015 	stmdacs	r0, {r0, r2, r4, ip, pc}
d0019d04:	8162f000 	msrhi	SPSR_x, r0
d0019d08:	4628a92a 	strtmi	sl, [r8], -sl, lsr #18
d0019d0c:	f7f9942a 			; <UNDEFINED> instruction: 0xf7f9942a
d0019d10:	2800f81f 	stmdacs	r0, {r0, r1, r2, r3, r4, fp, ip, sp, lr, pc}
d0019d14:	add9f43f 	cfldrdge	mvd15, [r9, #252]	; 0xfc
d0019d18:	b9339b14 	ldmdblt	r3!, {r2, r4, r8, r9, fp, ip, pc}
d0019d1c:	1924f8df 	stmdbne	r4!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d0019d20:	44794628 	ldrbtmi	r4, [r9], #-1576	; 0xfffff9d8
d0019d24:	fa40f7f6 	blx	0xd1057d04
d0019d28:	f105e5cf 			; <UNDEFINED> instruction: 0xf105e5cf
d0019d2c:	ae320718 	mrcge	7, 1, r0, cr2, cr8, {0}
d0019d30:	a030f895 	mlasge	r0, r5, r8, pc	; <UNPREDICTABLE>
d0019d34:	c60fcf0f 	strgt	ip, [pc], -pc, lsl #30
d0019d38:	000fe897 	muleq	pc, r7, r8	; <UNPREDICTABLE>
d0019d3c:	000fe886 	andeq	lr, pc, r6, lsl #17
d0019d40:	f2406a6b 	vpmax.s8	q11, q0, <illegal reg q13.5>
d0019d44:	f8df1101 			; <UNDEFINED> instruction: 0xf8df1101
d0019d48:	46282900 	strtmi	r2, [r8], -r0, lsl #18
d0019d4c:	6aab9311 	bvs	0xceafe998
d0019d50:	9310447a 	tstls	r0, #2046820352	; 0x7a000000
d0019d54:	e9d56b6b 	ldmib	r5, {r0, r1, r3, r5, r6, r8, r9, fp, sp, lr}^
d0019d58:	930f8b06 	movwls	r8, #64262	; 0xfb06
d0019d5c:	ffb5f7f8 			; <UNDEFINED> instruction: 0xffb5f7f8
d0019d60:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0019d64:	215badb2 	ldrhcs	sl, [fp, #-210]	; 0xffffff2e
d0019d68:	f7f84628 			; <UNDEFINED> instruction: 0xf7f84628
d0019d6c:	9b2affa0 	blls	0xd0ad9bf4
d0019d70:	721af44f 	andsvc	pc, sl, #1325400064	; 0x4f000000
d0019d74:	fb024607 	blx	0xd00ab59a
d0019d78:	f5025203 			; <UNDEFINED> instruction: 0xf5025203
d0019d7c:	f8b232bd 			; <UNDEFINED> instruction: 0xf8b232bd
d0019d80:	28006068 	stmdacs	r0, {r3, r5, r6, sp, lr}
d0019d84:	6aead07e 	bvs	0xcfacdf84
d0019d88:	7281f5a2 	addvc	pc, r1, #679477248	; 0x28800000
d0019d8c:	d80b2a01 	stmdale	fp, {r0, r9, fp, sp}
d0019d90:	9020f8d5 	ldrdls	pc, [r0], -r5	; <UNPREDICTABLE>
d0019d94:	0f00f1b9 	svceq	0x0000f1b9
d0019d98:	00b1d006 	adcseq	sp, r1, r6
d0019d9c:	2280f44f 	addcs	pc, r0, #1325400064	; 0x4f000000
d0019da0:	f2f1fbb2 			; <UNDEFINED> instruction: 0xf2f1fbb2
d0019da4:	d9244591 	stmdble	r4!, {r0, r4, r7, r8, sl, lr}
d0019da8:	28a0f8df 	stmiacs	r0!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d0019dac:	711af44f 	tstvc	sl, pc, asr #8	; <UNPREDICTABLE>
d0019db0:	fb01447a 	blx	0xd006afa2
d0019db4:	f5032303 			; <UNDEFINED> instruction: 0xf5032303
d0019db8:	f89333bd 			; <UNDEFINED> instruction: 0xf89333bd
d0019dbc:	b9a3306b 	stmiblt	r3!, {r0, r1, r3, r5, r6, ip, sp}
d0019dc0:	488cf8df 	stmmi	ip, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d0019dc4:	f8df447c 			; <UNDEFINED> instruction: 0xf8df447c
d0019dc8:	447b388c 	ldrbtmi	r3, [fp], #-2188	; 0xfffff774
d0019dcc:	2a006d9a 	bcs	0xd003543c
d0019dd0:	ad7bf47f 	cfldrdge	mvd15, [fp, #-508]!	; 0xfffffe04
d0019dd4:	6a996a58 	bvs	0xce67473c
d0019dd8:	5030f893 	mlaspl	r0, r3, r8, pc	; <UNPREDICTABLE>
d0019ddc:	e9c36b5a 	stmib	r3, {r1, r3, r4, r6, r8, r9, fp, sp, lr}^
d0019de0:	e9c34016 	stmib	r3, {r1, r2, r4, lr}^
d0019de4:	669a1518 			; <UNDEFINED> instruction: 0x669a1518
d0019de8:	f8dfe56f 			; <UNDEFINED> instruction: 0xf8dfe56f
d0019dec:	447c486c 	ldrbtmi	r4, [ip], #-2156	; 0xfffff794
d0019df0:	4628e7e9 	strtmi	lr, [r8], -r9, ror #15
d0019df4:	ff40f7f8 			; <UNDEFINED> instruction: 0xff40f7f8
d0019df8:	2860f8df 	stmdacs	r0!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d0019dfc:	4628215d 			; <UNDEFINED> instruction: 0x4628215d
d0019e00:	f7f8447a 			; <UNDEFINED> instruction: 0xf7f8447a
d0019e04:	2800ff62 	stmdacs	r0, {r1, r5, r6, r8, r9, sl, fp, ip, sp, lr, pc}
d0019e08:	ad5ff43f 	cfldrdge	mvd15, [pc, #-252]	; 0xd0019d14
d0019e0c:	0850f8df 	ldmdaeq	r0, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d0019e10:	fb09213d 	blx	0xd026230e
d0019e14:	4478f606 	ldrbtmi	pc, [r8], #-1542	; 0xfffff9fa	; <UNPREDICTABLE>
d0019e18:	35e5f500 	strbcc	pc, [r5, #1280]!	; 0x500	; <UNPREDICTABLE>
d0019e1c:	30d8f8d5 	ldrsbcc	pc, [r8], #133	; 0x85	; <UNPREDICTABLE>
d0019e20:	f7f89312 			; <UNDEFINED> instruction: 0xf7f89312
d0019e24:	b138ff44 	teqlt	r8, r4, asr #30	; <UNPREDICTABLE>
d0019e28:	30d8f8d5 	ldrsbcc	pc, [r8], #133	; 0x85	; <UNPREDICTABLE>
d0019e2c:	6380f5c3 	orrvs	pc, r0, #817889280	; 0x30c00000
d0019e30:	d92a429e 	stmdble	sl!, {r1, r2, r3, r4, r7, r9, lr}
d0019e34:	fba4f7f9 	blx	0xce957e22
d0019e38:	5828f8df 	stmdapl	r8!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d0019e3c:	f8df213b 			; <UNDEFINED> instruction: 0xf8df213b
d0019e40:	447d2828 	ldrbtmi	r2, [sp], #-2088	; 0xfffff7d8
d0019e44:	4628447a 			; <UNDEFINED> instruction: 0x4628447a
d0019e48:	ff3ff7f8 			; <UNDEFINED> instruction: 0xff3ff7f8
d0019e4c:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d0019e50:	465aad3c 			; <UNDEFINED> instruction: 0x465aad3c
d0019e54:	46284641 	strtmi	r4, [r8], -r1, asr #12
d0019e58:	fc3ff7f6 	ldc2	7, cr15, [pc], #-984	; 0xd0019a88
d0019e5c:	db342800 	blle	0xd0d23e64
d0019e60:	3808f8df 	stmdacc	r8, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d0019e64:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d0019e68:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0019e6c:	f8dfad2e 			; <UNDEFINED> instruction: 0xf8dfad2e
d0019e70:	447a2800 	ldrbtmi	r2, [sl], #-2048	; 0xfffff800
d0019e74:	9a11659a 	bls	0xd04734e4
d0019e78:	9a1065da 	bls	0xd04335e8
d0019e7c:	2a18e9c3 	bcs	0xd0654590
d0019e80:	e7b09a0f 	ldr	r9, [r0, pc, lsl #20]!
d0019e84:	0901f04f 	stmdbeq	r1, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d0019e88:	4630e7c0 	ldrtmi	lr, [r0], -r0, asr #15
d0019e8c:	fb42f7f9 	blx	0xd10d7e7a
d0019e90:	28004605 	stmdacs	r0, {r0, r2, r9, sl, lr}
d0019e94:	ad19f43f 	cfldrsge	mvf15, [r9, #-252]	; 0xffffff04
d0019e98:	b187982a 	orrlt	r9, r7, sl, lsr #16
d0019e9c:	46012200 	strmi	r2, [r1], -r0, lsl #4
d0019ea0:	4648462b 	strbmi	r4, [r8], -fp, lsr #12
d0019ea4:	f7fd9200 			; <UNDEFINED> instruction: 0xf7fd9200
d0019ea8:	2300fd05 	movwcs	pc, #3333	; 0xd05	; <UNPREDICTABLE>
d0019eac:	d0c3429e 	smullle	r4, r3, lr, r2
d0019eb0:	2023f855 	eorcs	pc, r3, r5, asr r8	; <UNPREDICTABLE>
d0019eb4:	f0412a00 			; <UNDEFINED> instruction: 0xf0412a00
d0019eb8:	3301816c 	movwcc	r8, #4460	; 0x116c
d0019ebc:	2301e7f6 	movwcs	lr, #6134	; 0x17f6
d0019ec0:	4639462a 	ldrtmi	r4, [r9], -sl, lsr #12
d0019ec4:	fc1cf7fd 	ldc2	7, cr15, [ip], {253}	; 0xfd
d0019ec8:	465ae7ef 	ldrbmi	lr, [sl], -pc, ror #15
d0019ecc:	46284641 	strtmi	r4, [r8], -r1, asr #12
d0019ed0:	fbdff7f6 	blx	0xcf817eb2
d0019ed4:	dac32800 	ble	0xcf0e3edc
d0019ed8:	4641465a 			; <UNDEFINED> instruction: 0x4641465a
d0019edc:	f7f64628 			; <UNDEFINED> instruction: 0xf7f64628
d0019ee0:	2800fc40 	stmdacs	r0, {r6, sl, fp, ip, sp, lr, pc}
d0019ee4:	f505dabc 			; <UNDEFINED> instruction: 0xf505dabc
d0019ee8:	00b332bc 	ldrhteq	r3, [r3], ip
d0019eec:	29806851 	stmibcs	r0, {r0, r4, r6, fp, sp, lr}
d0019ef0:	f505d008 			; <UNDEFINED> instruction: 0xf505d008
d0019ef4:	b98432dd 	stmiblt	r4, {r0, r2, r3, r4, r6, r7, r9, ip, sp}
d0019ef8:	50d4f8d2 	ldrsbpl	pc, [r4], #130	; 0x82	; <UNPREDICTABLE>
d0019efc:	2080f5c3 	addcs	pc, r0, r3, asr #11
d0019f00:	d95c4285 	ldmdble	ip, {r0, r2, r7, r9, lr}^
d0019f04:	376cf8df 			; <UNDEFINED> instruction: 0x376cf8df
d0019f08:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d0019f0c:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d0019f10:	f8dfacdc 			; <UNDEFINED> instruction: 0xf8dfacdc
d0019f14:	447a2764 	ldrbtmi	r2, [sl], #-1892	; 0xfffff89c
d0019f18:	f8d2e7ac 			; <UNDEFINED> instruction: 0xf8d2e7ac
d0019f1c:	350350d0 	strcc	r5, [r3, #-208]	; 0xffffff30
d0019f20:	0503f025 	streq	pc, [r3, #-37]	; 0xffffffdb
d0019f24:	f8c2442b 			; <UNDEFINED> instruction: 0xf8c2442b
d0019f28:	f8df30d0 			; <UNDEFINED> instruction: 0xf8df30d0
d0019f2c:	2f003750 	svccs	0x00003750
d0019f30:	0001f101 	andeq	pc, r1, r1, lsl #2
d0019f34:	7048f8bd 	strhvc	pc, [r8], #-141	; 0xffffff73	; <UNPREDICTABLE>
d0019f38:	f503447b 			; <UNDEFINED> instruction: 0xf503447b
d0019f3c:	605032bc 	ldrhvs	r3, [r0], #-44	; 0xffffffd4
d0019f40:	2211bf14 	andscs	fp, r1, #20, 30	; 0x50
d0019f44:	2c00220f 	sfmcs	f2, 4, [r0], {15}
d0019f48:	bf08921b 	svclt	0x0008921b
d0019f4c:	7a1a2600 	bvc	0xd06a3754
d0019f50:	f89d9213 			; <UNDEFINED> instruction: 0xf89d9213
d0019f54:	921420a8 	andsls	r2, r4, #168	; 0xa8
d0019f58:	9215b2e2 	andsls	fp, r5, #536870926	; 0x2000000e
d0019f5c:	fb022234 	blx	0xd00a2836
d0019f60:	21003401 	tstcs	r0, r1, lsl #8
d0019f64:	34aff504 	strtcc	pc, [pc], #1284	; 0xd0019f6c
d0019f68:	46181d23 	ldrmi	r1, [r8], -r3, lsr #26
d0019f6c:	fa78f002 	blx	0xd1e55f7c
d0019f70:	f10d9a11 			; <UNDEFINED> instruction: 0xf10d9a11
d0019f74:	f88d0ec8 			; <UNDEFINED> instruction: 0xf88d0ec8
d0019f78:	9235a0e0 	eorsls	sl, r5, #224	; 0xe0
d0019f7c:	9a104684 	bls	0xd042b994
d0019f80:	923662a5 	eorsls	r6, r6, #1342177290	; 0x5000000a
d0019f84:	e9cd9a0f 	stmib	sp, {r0, r1, r2, r3, r9, fp, ip, pc}^
d0019f88:	92398b32 	eorsls	r8, r9, #51200	; 0xc800
d0019f8c:	000fe8be 			; <UNDEFINED> instruction: 0x000fe8be
d0019f90:	000fe8ac 	andeq	lr, pc, ip, lsr #17
d0019f94:	000fe89e 	muleq	pc, lr, r8	; <UNPREDICTABLE>
d0019f98:	000fe88c 	andeq	lr, pc, ip, lsl #17
d0019f9c:	f8849b1b 			; <UNDEFINED> instruction: 0xf8849b1b
d0019fa0:	9b13302c 	blls	0xd04e6058
d0019fa4:	302df884 	eorcc	pc, sp, r4, lsl #17
d0019fa8:	f8849b14 			; <UNDEFINED> instruction: 0xf8849b14
d0019fac:	9b15302e 	blls	0xd056606c
d0019fb0:	f8848627 			; <UNDEFINED> instruction: 0xf8848627
d0019fb4:	8666302f 	strbthi	r3, [r6], -pc, lsr #32
d0019fb8:	9034f8c4 	eorsls	pc, r4, r4, asr #17
d0019fbc:	3503e485 	strcc	lr, [r3, #-1157]	; 0xfffffb7b
d0019fc0:	0503f025 	streq	pc, [r3, #-37]	; 0xffffffdb
d0019fc4:	f8c2442b 			; <UNDEFINED> instruction: 0xf8c2442b
d0019fc8:	e7ae30d4 	sbfx	r3, r4, #1, #15
d0019fcc:	b9239b14 	stmdblt	r3!, {r2, r4, r8, r9, fp, ip, pc}
d0019fd0:	1109f240 	tstne	r9, r0, asr #4	; <UNPREDICTABLE>
d0019fd4:	f7f84628 			; <UNDEFINED> instruction: 0xf7f84628
d0019fd8:	f8dffe6a 			; <UNDEFINED> instruction: 0xf8dffe6a
d0019fdc:	f44f06a4 	vst1.32	{d16-d18}, [pc :128], r4
d0019fe0:	44787184 	ldrbtmi	r7, [r8], #-388	; 0xfffffe7c
d0019fe4:	fe63f7f8 	mcr2	7, 3, pc, cr3, cr8, {7}	; <UNPREDICTABLE>
d0019fe8:	28004605 	stmdacs	r0, {r0, r2, r9, sl, lr}
d0019fec:	80f1f040 	rscshi	pc, r1, r0, asr #32
d0019ff0:	0690f8df 			; <UNDEFINED> instruction: 0x0690f8df
d0019ff4:	f7fa4478 			; <UNDEFINED> instruction: 0xf7fa4478
d0019ff8:	4604f859 			; <UNDEFINED> instruction: 0x4604f859
d0019ffc:	f0402800 			; <UNDEFINED> instruction: 0xf0402800
d001a000:	9b1480eb 	blls	0xd053a3b4
d001a004:	f8dfb9b3 			; <UNDEFINED> instruction: 0xf8dfb9b3
d001a008:	f2404680 	vmax.s8	d20, d16, d0
d001a00c:	447c1107 	ldrbtmi	r1, [ip], #-263	; 0xfffffef9
d001a010:	f7f84620 			; <UNDEFINED> instruction: 0xf7f84620
d001a014:	2800fe4c 	stmdacs	r0, {r2, r3, r6, r9, sl, fp, ip, sp, lr, pc}
d001a018:	80b6f000 	adcshi	pc, r6, r0
d001a01c:	066cf8df 			; <UNDEFINED> instruction: 0x066cf8df
d001a020:	4478212a 	ldrbtmi	r2, [r8], #-298	; 0xfffffed6
d001a024:	fe43f7f8 	mcr2	7, 2, pc, cr3, cr8, {7}	; <UNPREDICTABLE>
d001a028:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d001a02c:	250080da 	strcs	r8, [r0, #-218]	; 0xffffff26
d001a030:	e0162303 	ands	r2, r6, r3, lsl #6
d001a034:	0658f8df 			; <UNDEFINED> instruction: 0x0658f8df
d001a038:	f7fa4478 			; <UNDEFINED> instruction: 0xf7fa4478
d001a03c:	2800f837 	stmdacs	r0, {r0, r1, r2, r4, r5, fp, ip, sp, lr, pc}
d001a040:	80ccf040 	sbchi	pc, ip, r0, asr #32
d001a044:	064cf8df 			; <UNDEFINED> instruction: 0x064cf8df
d001a048:	f7fa4478 			; <UNDEFINED> instruction: 0xf7fa4478
d001a04c:	b930f82f 	ldmdblt	r0!, {r0, r1, r2, r3, r5, fp, ip, sp, lr, pc}
d001a050:	0644f8df 			; <UNDEFINED> instruction: 0x0644f8df
d001a054:	f7fa4478 			; <UNDEFINED> instruction: 0xf7fa4478
d001a058:	2800f829 	stmdacs	r0, {r0, r3, r5, fp, ip, sp, lr, pc}
d001a05c:	2505d0d3 	strcs	sp, [r5, #-211]	; 0xffffff2d
d001a060:	93132300 	tstls	r3, #0, 6
d001a064:	4634f8df 			; <UNDEFINED> instruction: 0x4634f8df
d001a068:	447cae2a 	ldrbtmi	sl, [ip], #-3626	; 0xfffff1d6
d001a06c:	0718f104 	ldreq	pc, [r8, -r4, lsl #2]
d001a070:	c60fcf0f 	strgt	ip, [pc], -pc, lsl #30
d001a074:	000fe897 	muleq	pc, r7, r8	; <UNPREDICTABLE>
d001a078:	000fe886 	andeq	lr, pc, r6, lsl #17
d001a07c:	f2406a63 	vpmax.s8	q11, q0, <illegal reg q9.5>
d001a080:	f8df1101 			; <UNDEFINED> instruction: 0xf8df1101
d001a084:	4620261c 			; <UNDEFINED> instruction: 0x4620261c
d001a088:	6aa39311 	bvs	0xce8fecd4
d001a08c:	930f447a 	movwls	r4, #62586	; 0xf47a
d001a090:	3030f894 	mlascc	r0, r4, r8, pc	; <UNPREDICTABLE>
d001a094:	6b639312 	blvs	0xd18fece4
d001a098:	ab06e9d4 	blge	0xd01d47f0
d001a09c:	f7f89310 			; <UNDEFINED> instruction: 0xf7f89310
d001a0a0:	2800fe14 	stmdacs	r0, {r2, r4, r9, sl, fp, ip, sp, lr, pc}
d001a0a4:	ac11f43f 	cfldrsge	mvf15, [r1], {63}	; 0x3f
d001a0a8:	2b009b14 	blcs	0xd0040d00
d001a0ac:	8258f000 	subshi	pc, r8, #0
d001a0b0:	2b009b13 	blcs	0xd0040d04
d001a0b4:	8254f040 	subshi	pc, r4, #64	; 0x40
d001a0b8:	6ae3b91d 	bvs	0xcf908534
d001a0bc:	f0002b28 			; <UNDEFINED> instruction: 0xf0002b28
d001a0c0:	9b11824f 	blls	0xd047aa04
d001a0c4:	ac32ae2a 	ldcge	14, cr10, [r2], #-168	; 0xffffff58
d001a0c8:	9b0f932d 	blls	0xd03fed84
d001a0cc:	9b12932e 	blls	0xd04bed8c
d001a0d0:	30c0f88d 	sbccc	pc, r0, sp, lsl #17
d001a0d4:	e9cd9b10 	stmib	sp, {r4, r8, r9, fp, ip, pc}^
d001a0d8:	9331ab2a 	teqls	r1, #43008	; 0xa800
d001a0dc:	c40fce0f 	strgt	ip, [pc], #-3599	; 0xd001a0e4
d001a0e0:	000fe896 	muleq	pc, r6, r8	; <UNPREDICTABLE>
d001a0e4:	65bcf8df 	ldrvs	pc, [ip, #2271]!	; 0x8df
d001a0e8:	e884447e 	stm	r4, {r1, r2, r3, r4, r5, r6, sl, lr}
d001a0ec:	465a000f 	ldrbmi	r0, [sl], -pc
d001a0f0:	46304651 			; <UNDEFINED> instruction: 0x46304651
d001a0f4:	fb35f7f6 	blx	0xd0d980d6
d001a0f8:	4604465a 			; <UNDEFINED> instruction: 0x4604465a
d001a0fc:	46304651 			; <UNDEFINED> instruction: 0x46304651
d001a100:	faebf7f6 	blx	0xcfb180e0
d001a104:	da792800 	ble	0xd1e6410c
d001a108:	4651465a 			; <UNDEFINED> instruction: 0x4651465a
d001a10c:	f7f64630 			; <UNDEFINED> instruction: 0xf7f64630
d001a110:	2800fac0 	stmdacs	r0, {r6, r7, r9, fp, ip, sp, lr, pc}
d001a114:	2c00da72 			; <UNDEFINED> instruction: 0x2c00da72
d001a118:	2034db09 	eorscs	sp, r4, r9, lsl #22
d001a11c:	fb007a33 	blx	0xd00389f2
d001a120:	f5046404 			; <UNDEFINED> instruction: 0xf5046404
d001a124:	f89434e5 			; <UNDEFINED> instruction: 0xf89434e5
d001a128:	429a2105 	addsmi	r2, sl, #1073741825	; 0x40000001
d001a12c:	f8dfd066 			; <UNDEFINED> instruction: 0xf8dfd066
d001a130:	465a7578 			; <UNDEFINED> instruction: 0x465a7578
d001a134:	447f4651 	ldrbtmi	r4, [pc], #-1617	; 0xd001a13c
d001a138:	f7f64638 			; <UNDEFINED> instruction: 0xf7f64638
d001a13c:	2800fb4f 	stmdacs	r0, {r0, r1, r2, r3, r6, r8, r9, fp, ip, sp, lr, pc}
d001a140:	f507d15c 			; <UNDEFINED> instruction: 0xf507d15c
d001a144:	46044850 			; <UNDEFINED> instruction: 0x46044850
d001a148:	f24d463e 	vmin.s8	d20, d13, d30
d001a14c:	f1080924 			; <UNDEFINED> instruction: 0xf1080924
d001a150:	f8d8081c 			; <UNDEFINED> instruction: 0xf8d8081c
d001a154:	429c3000 	addsmi	r3, ip, #0
d001a158:	f506d346 			; <UNDEFINED> instruction: 0xf506d346
d001a15c:	685b33bc 	ldmdavs	fp, {r2, r3, r4, r5, r7, r8, r9, ip, sp}^
d001a160:	d15e2b80 	cmple	lr, r0, lsl #23
d001a164:	2b006db3 	blcs	0xd0035838
d001a168:	abaff47f 	blge	0xcec1736c
d001a16c:	353cf8df 	ldrcc	pc, [ip, #-2271]!	; 0xfffff721
d001a170:	65b3447b 	ldrvs	r4, [r3, #1147]!	; 0x47b
d001a174:	65f39b11 	ldrbvs	r9, [r3, #2833]!	; 0xb11
d001a178:	66339b0f 	ldrtvs	r9, [r3], -pc, lsl #22
d001a17c:	66739b12 			; <UNDEFINED> instruction: 0x66739b12
d001a180:	66b39b10 	ssatvs	r9, #20, r0, lsl #22
d001a184:	bba1f7ff 	bllt	0xce898188
d001a188:	f2406ae2 	vpmax.s8	q11, q8, q9
d001a18c:	429a1301 	addsmi	r1, sl, #67108864	; 0x4000000
d001a190:	4620d118 			; <UNDEFINED> instruction: 0x4620d118
d001a194:	1206e9d4 	andne	lr, r6, #212, 18	; 0x350000
d001a198:	fa9ff7f6 	blx	0xce818178
d001a19c:	db112800 	blle	0xd04641a4
d001a1a0:	e9d44620 	ldmib	r4, {r5, r9, sl, lr}^
d001a1a4:	f7f61206 			; <UNDEFINED> instruction: 0xf7f61206
d001a1a8:	2324fa98 	msrcs	CPSR_s, #152, 20	; 0x98000
d001a1ac:	4000fb03 	andmi	pc, r0, r3, lsl #22
d001a1b0:	30d8f500 	sbcscc	pc, r8, r0, lsl #10
d001a1b4:	31ecf890 			; <UNDEFINED> instruction: 0x31ecf890
d001a1b8:	d1032bff 	strdle	r2, [r3, -pc]
d001a1bc:	f7f84620 			; <UNDEFINED> instruction: 0xf7f84620
d001a1c0:	e72bfd5b 			; <UNDEFINED> instruction: 0xe72bfd5b
d001a1c4:	14e8f8df 	strbtne	pc, [r8], #2271	; 0x8df	; <UNPREDICTABLE>
d001a1c8:	04e8f8df 	strbteq	pc, [r8], #2271	; 0x8df	; <UNPREDICTABLE>
d001a1cc:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d001a1d0:	2500e5a8 	strcs	lr, [r0, #-1448]	; 0xfffffa58
d001a1d4:	e7442301 	strb	r2, [r4, -r1, lsl #6]
d001a1d8:	e7422302 	strb	r2, [r2, -r2, lsl #6]
d001a1dc:	94132501 	ldrls	r2, [r3], #-1281	; 0xfffffaff
d001a1e0:	4605e740 	strmi	lr, [r5], -r0, asr #14
d001a1e4:	e73d9013 			; <UNDEFINED> instruction: 0xe73d9013
d001a1e8:	0209eb07 	andeq	lr, r9, #7168	; 0x1c00
d001a1ec:	46504659 			; <UNDEFINED> instruction: 0x46504659
d001a1f0:	f7f63734 			; <UNDEFINED> instruction: 0xf7f63734
d001a1f4:	b908fade 	stmdblt	r8, {r1, r2, r3, r4, r6, r7, r9, fp, ip, sp, lr, pc}
d001a1f8:	e7aa3401 	str	r3, [sl, r1, lsl #8]!
d001a1fc:	34b8f8df 	ldrtcc	pc, [r8], #2271	; 0x8df	; <UNPREDICTABLE>
d001a200:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d001a204:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d001a208:	f8dfab60 			; <UNDEFINED> instruction: 0xf8dfab60
d001a20c:	447a24b0 	ldrbtmi	r2, [sl], #-1200	; 0xfffffb50
d001a210:	9a11659a 	bls	0xd0473880
d001a214:	9a0f65da 	bls	0xd03f3984
d001a218:	9a12661a 	bls	0xd04b3a88
d001a21c:	9a10665a 	bls	0xd0433b8c
d001a220:	215be5e1 	cmpcs	fp, r1, ror #11
d001a224:	fa5f4630 	blx	0xd17ebaec
d001a228:	f7f8f885 			; <UNDEFINED> instruction: 0xf7f8f885
d001a22c:	2800fd40 	stmdacs	r0, {r6, r8, sl, fp, ip, sp, lr, pc}
d001a230:	8101f000 	mrshi	pc, (UNDEF: 1)	; <UNPREDICTABLE>
d001a234:	d0082d05 	andle	r2, r8, r5, lsl #26
d001a238:	6db3b13d 	ldfvsd	f3, [r3, #244]!	; 0xf4
d001a23c:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001a240:	f8dfab44 			; <UNDEFINED> instruction: 0xf8dfab44
d001a244:	447b347c 	ldrbtmi	r3, [fp], #-1148	; 0xfffffb84
d001a248:	f8dfe793 			; <UNDEFINED> instruction: 0xf8dfe793
d001a24c:	447b3478 	ldrbtmi	r3, [fp], #-1144	; 0xfffffb88
d001a250:	6a5f6ad8 	bvs	0xd17f4db8
d001a254:	7081f5a0 	addvc	pc, r1, r0, lsr #11
d001a258:	f8936a9e 			; <UNDEFINED> instruction: 0xf8936a9e
d001a25c:	28011030 	stmdacs	r1, {r4, r5, ip}
d001a260:	d8016b5a 	stmdale	r1, {r1, r3, r4, r6, r8, r9, fp, sp, lr}
d001a264:	b9806a18 	stmiblt	r0, {r3, r4, r9, fp, sp, lr}
d001a268:	045cf8df 	ldrbeq	pc, [ip], #-2271	; 0xfffff721	; <UNPREDICTABLE>
d001a26c:	6d834478 	cfstrsvs	mvf4, [r3, #480]	; 0x1e0
d001a270:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001a274:	f8dfab2a 			; <UNDEFINED> instruction: 0xf8dfab2a
d001a278:	447b3454 	ldrbtmi	r3, [fp], #-1108	; 0xfffffbac
d001a27c:	e9c06682 	stmib	r0, {r1, r7, r9, sl, sp, lr}^
d001a280:	e9c03716 	stmib	r0, {r1, r2, r4, r8, r9, sl, ip, sp}^
d001a284:	f7ff6118 			; <UNDEFINED> instruction: 0xf7ff6118
d001a288:	b975bb20 	ldmdblt	r5!, {r5, r8, r9, fp, ip, sp, pc}^
d001a28c:	3f80f5b0 	svccc	0x0080f5b0
d001a290:	6d98d929 	vldrvs.16	s26, [r8, #82]	; 0x52	; <UNPREDICTABLE>
d001a294:	f47f2800 			; <UNDEFINED> instruction: 0xf47f2800
d001a298:	f8dfab18 			; <UNDEFINED> instruction: 0xf8dfab18
d001a29c:	44780434 	ldrbtmi	r0, [r8], #-1076	; 0xfffffbcc
d001a2a0:	6118e9c3 	tstvs	r8, r3, asr #19
d001a2a4:	0716e9c3 	ldreq	lr, [r6, -r3, asr #19]
d001a2a8:	2401e59d 	strcs	lr, [r1], #-1437	; 0xfffffa63
d001a2ac:	3424f8df 	strtcc	pc, [r4], #-2271	; 0xfffff721
d001a2b0:	f503447b 			; <UNDEFINED> instruction: 0xf503447b
d001a2b4:	f8d333dd 			; <UNDEFINED> instruction: 0xf8d333dd
d001a2b8:	b91530d4 	ldmdblt	r5, {r2, r4, r6, r7, ip, sp}
d001a2bc:	f0233303 			; <UNDEFINED> instruction: 0xf0233303
d001a2c0:	f5b30303 			; <UNDEFINED> instruction: 0xf5b30303
d001a2c4:	d8042f80 	stmdale	r4, {r7, r8, r9, sl, fp, sp}
d001a2c8:	f5c34344 			; <UNDEFINED> instruction: 0xf5c34344
d001a2cc:	429c2380 	addsmi	r2, ip, #128, 6
d001a2d0:	f8dfd90b 			; <UNDEFINED> instruction: 0xf8dfd90b
d001a2d4:	44780404 	ldrbtmi	r0, [r8], #-1028	; 0xfffffbfc
d001a2d8:	2b006d83 	blcs	0xd00358ec
d001a2dc:	aaf5f47f 	bge	0xcfd974e0
d001a2e0:	447b4bfe 	ldrbtmi	r4, [fp], #-3070	; 0xfffff402
d001a2e4:	2404e7ca 	strcs	lr, [r4], #-1994	; 0xfffff836
d001a2e8:	48fde7e0 	ldmmi	sp!, {r5, r6, r7, r8, r9, sl, sp, lr, pc}^
d001a2ec:	90134478 	andsls	r4, r3, r8, ror r4
d001a2f0:	fcc2f7f8 	stc2l	7, cr15, [r2], {248}	; 0xf8
d001a2f4:	215d4afb 	ldrshcs	r4, [sp, #-171]	; 0xffffff55
d001a2f8:	447a9813 	ldrbtmi	r9, [sl], #-2067	; 0xfffff7ed
d001a2fc:	fce5f7f8 	stc2l	7, cr15, [r5], #992	; 0x3e0
d001a300:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001a304:	2d00aae2 	vstrcs	s20, [r0, #-904]	; 0xfffffc78
d001a308:	8098f040 	addshi	pc, r8, r0, asr #32
d001a30c:	f04f08a7 			; <UNDEFINED> instruction: 0xf04f08a7
d001a310:	4ef50808 	cdpmi	8, 15, cr0, cr5, cr8, {0}
d001a314:	447e213d 	ldrbtmi	r2, [lr], #-317	; 0xfffffec3
d001a318:	39e5f506 	stmibcc	r5!, {r1, r2, r8, sl, ip, sp, lr, pc}^
d001a31c:	f8d94630 			; <UNDEFINED> instruction: 0xf8d94630
d001a320:	931330d8 	tstls	r3, #216	; 0xd8
d001a324:	fcc3f7f8 	stc2l	7, cr15, [r3], {248}	; 0xf8
d001a328:	f0002800 			; <UNDEFINED> instruction: 0xf0002800
d001a32c:	f1a880ef 			; <UNDEFINED> instruction: 0xf1a880ef
d001a330:	2b010307 	blcs	0xd005af54
d001a334:	80aff200 	adchi	pc, pc, r0, lsl #4
d001a338:	30d8f8d9 	ldrsbcc	pc, [r8], #137	; 0x89	; <UNPREDICTABLE>
d001a33c:	6380f5c3 	orrvs	pc, r0, #817889280	; 0x30c00000
d001a340:	d27f42bb 	rsbsle	r4, pc, #-1342177269	; 0xb000000b
d001a344:	f91cf7f9 			; <UNDEFINED> instruction: 0xf91cf7f9
d001a348:	4ee82500 	cdpmi	5, 14, cr2, cr8, cr0, {0}
d001a34c:	4ae8213b 	bmi	0xcfa22840
d001a350:	447a447e 	ldrbtmi	r4, [sl], #-1150	; 0xfffffb82
d001a354:	f7f84630 			; <UNDEFINED> instruction: 0xf7f84630
d001a358:	2800fcb8 	stmdacs	r0, {r3, r4, r5, r7, sl, fp, ip, sp, lr, pc}
d001a35c:	aab5f43f 	bge	0xced97460
d001a360:	0307f1a8 	movweq	pc, #29096	; 0x71a8	; <UNPREDICTABLE>
d001a364:	f2002b01 	vqdmulh.s<illegal width 8>	d2, d0, d1
d001a368:	9b1580ea 	blls	0xd057a718
d001a36c:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d001a370:	f1b880cf 			; <UNDEFINED> instruction: 0xf1b880cf
d001a374:	d1080f08 	tstle	r8, r8, lsl #30
d001a378:	36ddf506 	ldrbcc	pc, [sp], r6, lsl #10	; <UNPREDICTABLE>
d001a37c:	30d0f8d6 	ldrsbcc	pc, [r0], #134	; 0x86	; <UNPREDICTABLE>
d001a380:	f0233303 			; <UNDEFINED> instruction: 0xf0233303
d001a384:	f8c60303 			; <UNDEFINED> instruction: 0xf8c60303
d001a388:	4bda30d0 	blmi	0xcf6a66d0
d001a38c:	f503447b 			; <UNDEFINED> instruction: 0xf503447b
d001a390:	f8d333dd 			; <UNDEFINED> instruction: 0xf8d333dd
d001a394:	eb0990d0 	bl	0xd027e6dc
d001a398:	f8c30204 			; <UNDEFINED> instruction: 0xf8c30204
d001a39c:	4bd620d0 	blmi	0xcf5a26e4
d001a3a0:	f503447b 			; <UNDEFINED> instruction: 0xf503447b
d001a3a4:	7a1b32bc 	bvc	0xd06e6e9c
d001a3a8:	f89d9314 			; <UNDEFINED> instruction: 0xf89d9314
d001a3ac:	68563054 	ldmdavs	r6, {r2, r4, r6, ip, sp}^
d001a3b0:	f8bd931b 			; <UNDEFINED> instruction: 0xf8bd931b
d001a3b4:	1c71304c 	ldclne	0, cr3, [r1], #-304	; 0xfffffed0
d001a3b8:	9b159313 	blls	0xd057f00c
d001a3bc:	2b006051 	blcs	0xd0032508
d001a3c0:	2700bf08 	strcs	fp, [r0, -r8, lsl #30]
d001a3c4:	0f08f1b8 	svceq	0x0008f1b8
d001a3c8:	f040b2bf 			; <UNDEFINED> instruction: 0xf040b2bf
d001a3cc:	08a480c4 	stmiaeq	r4!, {r2, r6, r7, pc}
d001a3d0:	22344bca 	eorscs	r4, r4, #206848	; 0x32800
d001a3d4:	447b2100 	ldrbtmi	r2, [fp], #-256	; 0xffffff00
d001a3d8:	3606fb02 	strcc	pc, [r6], -r2, lsl #22
d001a3dc:	36aff506 	strtcc	pc, [pc], r6, lsl #10
d001a3e0:	46181d33 			; <UNDEFINED> instruction: 0x46181d33
d001a3e4:	f83cf002 			; <UNDEFINED> instruction: 0xf83cf002
d001a3e8:	f10d9a11 			; <UNDEFINED> instruction: 0xf10d9a11
d001a3ec:	46840ec8 	strmi	r0, [r4], r8, asr #29
d001a3f0:	9a0f9235 	bls	0xd03feccc
d001a3f4:	92366275 	eorsls	r6, r6, #1342177287	; 0x50000007
d001a3f8:	f8c69a12 			; <UNDEFINED> instruction: 0xf8c69a12
d001a3fc:	f88d9028 			; <UNDEFINED> instruction: 0xf88d9028
d001a400:	9a1020e0 	bls	0xd0422788
d001a404:	802cf886 	eorhi	pc, ip, r6, lsl #17
d001a408:	e9cd9239 	stmib	sp, {r0, r3, r4, r5, r9, ip, pc}^
d001a40c:	e8beab32 	ldm	lr!, {r1, r4, r5, r8, r9, fp, sp, pc}
d001a410:	e8ac000f 	stmia	ip!, {r0, r1, r2, r3}
d001a414:	e89e000f 	ldm	lr, {r0, r1, r2, r3}
d001a418:	e88c000f 	stm	ip, {r0, r1, r2, r3}
d001a41c:	9b14000f 	blls	0xd051a460
d001a420:	302df886 	eorcc	pc, sp, r6, lsl #17
d001a424:	f8869b1b 			; <UNDEFINED> instruction: 0xf8869b1b
d001a428:	9b13302f 	blls	0xd04e64ec
d001a42c:	86338677 			; <UNDEFINED> instruction: 0x86338677
d001a430:	f7ff6374 			; <UNDEFINED> instruction: 0xf7ff6374
d001a434:	4604ba4a 	strmi	fp, [r4], -sl, asr #20
d001a438:	e76a4607 	strb	r4, [sl, -r7, lsl #12]!
d001a43c:	f04f4627 			; <UNDEFINED> instruction: 0xf04f4627
d001a440:	e7660807 	strb	r0, [r6, -r7, lsl #16]!
d001a444:	f7f94638 			; <UNDEFINED> instruction: 0xf7f94638
d001a448:	4605f865 	strmi	pc, [r5], -r5, ror #16
d001a44c:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001a450:	f1a8aa3c 			; <UNDEFINED> instruction: 0xf1a8aa3c
d001a454:	21ff0207 	mvnscs	r0, r7, lsl #4
d001a458:	41534253 	cmpmi	r3, r3, asr r2
d001a45c:	93002200 	movwls	r2, #512	; 0x200
d001a460:	46384603 	ldrtmi	r4, [r8], -r3, lsl #12
d001a464:	fa26f7fd 	blx	0xd09d8460
d001a468:	eb054628 	bl	0xd016bd10
d001a46c:	42830387 	addmi	r0, r3, #469762050	; 0x1c000002
d001a470:	af6af43f 	svcge	0x006af43f
d001a474:	2b04f850 	blcs	0xd01585bc
d001a478:	d0f82a00 	rscsle	r2, r8, r0, lsl #20
d001a47c:	25004ba0 	strcs	r4, [r0, #-2976]	; 0xfffff460
d001a480:	f503447b 			; <UNDEFINED> instruction: 0xf503447b
d001a484:	f8d333e5 			; <UNDEFINED> instruction: 0xf8d333e5
d001a488:	443a20d8 	ldrtmi	r2, [sl], #-216	; 0xffffff28
d001a48c:	20d8f8c3 	sbcscs	pc, r8, r3, asr #17
d001a490:	93152301 	tstls	r5, #67108864	; 0x4000000
d001a494:	212de759 			; <UNDEFINED> instruction: 0x212de759
d001a498:	f7f84630 			; <UNDEFINED> instruction: 0xf7f84630
d001a49c:	69f2fc08 	ldmibvs	r2!, {r3, sl, fp, ip, sp, lr, pc}^
d001a4a0:	f44f69b3 	vst2.32	{d22,d24}, [pc :256], r3
d001a4a4:	9014718d 	andsls	r7, r4, sp, lsl #3
d001a4a8:	921b4630 	andsls	r4, fp, #48, 12	; 0x3000000
d001a4ac:	3a90ee08 	bcc	0xce455cd4
d001a4b0:	f8d66a35 			; <UNDEFINED> instruction: 0xf8d66a35
d001a4b4:	f7f8902c 			; <UNDEFINED> instruction: 0xf7f8902c
d001a4b8:	9a1bfbfa 	bls	0xd07194a8
d001a4bc:	4630b158 			; <UNDEFINED> instruction: 0x4630b158
d001a4c0:	fd96f7f8 	ldc2	7, cr15, [r6, #992]	; 0x3e0
d001a4c4:	9b144605 	blls	0xd052bce0
d001a4c8:	426db103 	rsbmi	fp, sp, #-1073741824	; 0xc0000000
d001a4cc:	0f05f1b8 	svceq	0x0005f1b8
d001a4d0:	b2edbf08 	rsclt	fp, sp, #8, 30
d001a4d4:	f240e739 	vaba.s8	d30, d0, d25
d001a4d8:	45991301 	ldrmi	r1, [r9, #769]	; 0x301
d001a4dc:	ee18d110 	mrc	1, 0, sp, cr8, cr0, {0}
d001a4e0:	46301a90 			; <UNDEFINED> instruction: 0x46301a90
d001a4e4:	f97af7f6 			; <UNDEFINED> instruction: 0xf97af7f6
d001a4e8:	4986b920 	stmibmi	r6, {r5, r8, fp, ip, sp, pc}
d001a4ec:	44794886 	ldrbtmi	r4, [r9], #-2182	; 0xfffff77a
d001a4f0:	e4174478 	ldr	r4, [r7], #-1144	; 0xfffffb88
d001a4f4:	48856a05 	stmmi	r5, {r0, r2, r9, fp, sp, lr}
d001a4f8:	f7f84478 			; <UNDEFINED> instruction: 0xf7f84478
d001a4fc:	e7e2fbbd 			; <UNDEFINED> instruction: 0xe7e2fbbd
d001a500:	7981f5a9 	stmibvc	r1, {r0, r3, r5, r7, r8, sl, ip, sp, lr, pc}
d001a504:	0f01f1b9 	svceq	0x0001f1b9
d001a508:	e7eed9f5 			; <UNDEFINED> instruction: 0xe7eed9f5
d001a50c:	e7dd4605 	ldrb	r4, [sp, r5, lsl #12]
d001a510:	0f08f1b8 	svceq	0x0008f1b8
d001a514:	f506d108 			; <UNDEFINED> instruction: 0xf506d108
d001a518:	f8d636dd 			; <UNDEFINED> instruction: 0xf8d636dd
d001a51c:	330330d4 	movwcc	r3, #12500	; 0x30d4
d001a520:	0303f023 	movweq	pc, #12323	; 0x3023	; <UNPREDICTABLE>
d001a524:	30d4f8c6 	sbcscc	pc, r4, r6, asr #17
d001a528:	447b4b79 	ldrbtmi	r4, [fp], #-2937	; 0xfffff487
d001a52c:	33ddf503 	bicscc	pc, sp, #12582912	; 0xc00000
d001a530:	90d4f8d3 	ldrsbls	pc, [r4], #131	; 0x83	; <UNPREDICTABLE>
d001a534:	0204eb09 	andeq	lr, r4, #9216	; 0x2400
d001a538:	20d4f8c3 	sbcscs	pc, r4, r3, asr #17
d001a53c:	f506e72f 			; <UNDEFINED> instruction: 0xf506e72f
d001a540:	f8d636dd 			; <UNDEFINED> instruction: 0xf8d636dd
d001a544:	330330d0 	movwcc	r3, #12496	; 0x30d0
d001a548:	0903f023 	stmdbeq	r3, {r0, r1, r5, ip, sp, lr, pc}
d001a54c:	0304f109 	movweq	pc, #16649	; 0x4109	; <UNPREDICTABLE>
d001a550:	30d0f8c6 	sbcscc	pc, r0, r6, asr #17
d001a554:	f1b8e723 			; <UNDEFINED> instruction: 0xf1b8e723
d001a558:	bf180f07 	svclt	0x00180f07
d001a55c:	e7372400 	ldr	r2, [r7, -r0, lsl #8]!
d001a560:	21284c6c 			; <UNDEFINED> instruction: 0x21284c6c
d001a564:	447c4a6c 	ldrbtmi	r4, [ip], #-2668	; 0xfffff594
d001a568:	4620447a 			; <UNDEFINED> instruction: 0x4620447a
d001a56c:	fbadf7f8 	blx	0xceb98556
d001a570:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001a574:	465aa9aa 	ldrbmi	sl, [sl], -sl, lsr #19
d001a578:	46204651 			; <UNDEFINED> instruction: 0x46204651
d001a57c:	f8adf7f6 			; <UNDEFINED> instruction: 0xf8adf7f6
d001a580:	db082800 	blle	0xd0224588
d001a584:	447b4b65 	ldrbtmi	r4, [fp], #-2917	; 0xfffff49b
d001a588:	2a006d9a 	bcs	0xd0035bf8
d001a58c:	a99df47f 	ldmibge	sp, {r0, r1, r2, r3, r4, r5, r6, sl, ip, sp, lr, pc}
d001a590:	447a4a63 	ldrbtmi	r4, [sl], #-2659	; 0xfffff59d
d001a594:	465ae63c 			; <UNDEFINED> instruction: 0x465ae63c
d001a598:	46204651 			; <UNDEFINED> instruction: 0x46204651
d001a59c:	f879f7f6 			; <UNDEFINED> instruction: 0xf879f7f6
d001a5a0:	daef2800 	ble	0xcfbe45a8
d001a5a4:	46594a5f 			; <UNDEFINED> instruction: 0x46594a5f
d001a5a8:	447a4650 	ldrbtmi	r4, [sl], #-1616	; 0xfffff9b0
d001a5ac:	f901f7f6 			; <UNDEFINED> instruction: 0xf901f7f6
d001a5b0:	4a5dbb50 	bmi	0xd17892f8
d001a5b4:	46504659 			; <UNDEFINED> instruction: 0x46504659
d001a5b8:	f7f6447a 			; <UNDEFINED> instruction: 0xf7f6447a
d001a5bc:	bb28f8fa 	bllt	0xd0a589ac
d001a5c0:	46594a5a 			; <UNDEFINED> instruction: 0x46594a5a
d001a5c4:	447a4650 	ldrbtmi	r4, [sl], #-1616	; 0xfffff9b0
d001a5c8:	f8f3f7f6 			; <UNDEFINED> instruction: 0xf8f3f7f6
d001a5cc:	bf0c2800 	svclt	0x000c2800
d001a5d0:	230c2300 	movwcs	r2, #49920	; 0xc300
d001a5d4:	46594a56 			; <UNDEFINED> instruction: 0x46594a56
d001a5d8:	93154650 	tstls	r5, #80, 12	; 0x5000000
d001a5dc:	f7f6447a 			; <UNDEFINED> instruction: 0xf7f6447a
d001a5e0:	9b15f8e8 	blls	0xd0598988
d001a5e4:	4303901b 	movwmi	r9, #12315	; 0x301b
d001a5e8:	80a8f000 	adchi	pc, r8, r0
d001a5ec:	9a139b14 	bls	0xd0501244
d001a5f0:	f0004313 			; <UNDEFINED> instruction: 0xf0004313
d001a5f4:	4b4f80a3 	blmi	0xd13fa888
d001a5f8:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d001a5fc:	f47f2a00 			; <UNDEFINED> instruction: 0xf47f2a00
d001a600:	4a4da964 	bmi	0xd1384b98
d001a604:	e603447a 			; <UNDEFINED> instruction: 0xe603447a
d001a608:	e7e32304 	strb	r2, [r3, r4, lsl #6]!
d001a60c:	e7e12308 	strb	r2, [r1, r8, lsl #6]!
d001a610:	000053a2 	andeq	r5, r0, r2, lsr #7
d001a614:	0000533c 	andeq	r5, r0, ip, lsr r3
d001a618:	fffff5ae 			; <UNDEFINED> instruction: 0xfffff5ae
d001a61c:	fffff5b1 			; <UNDEFINED> instruction: 0xfffff5b1
d001a620:	000052cc 	andeq	r5, r0, ip, asr #5
d001a624:	fffff57c 			; <UNDEFINED> instruction: 0xfffff57c
d001a628:	fffff51e 			; <UNDEFINED> instruction: 0xfffff51e
d001a62c:	fffff554 			; <UNDEFINED> instruction: 0xfffff554
d001a630:	fffff54e 			; <UNDEFINED> instruction: 0xfffff54e
d001a634:	ffff90e9 			; <UNDEFINED> instruction: 0xffff90e9
d001a638:	fffff47e 			; <UNDEFINED> instruction: 0xfffff47e
d001a63c:	fffff48f 			; <UNDEFINED> instruction: 0xfffff48f
d001a640:	00005128 	andeq	r5, r0, r8, lsr #2
d001a644:	fffff447 			; <UNDEFINED> instruction: 0xfffff447
d001a648:	fffff444 			; <UNDEFINED> instruction: 0xfffff444
d001a64c:	00005044 	andeq	r5, r0, r4, asr #32
d001a650:	fffff227 			; <UNDEFINED> instruction: 0xfffff227
d001a654:	0000502a 	andeq	r5, r0, sl, lsr #32
d001a658:	fffff1dd 			; <UNDEFINED> instruction: 0xfffff1dd
d001a65c:	ffffdc5e 			; <UNDEFINED> instruction: 0xffffdc5e
d001a660:	00004fde 	ldrdeq	r4, [r0], -lr
d001a664:	00004fb2 			; <UNDEFINED> instruction: 0x00004fb2
d001a668:	fffff375 			; <UNDEFINED> instruction: 0xfffff375
d001a66c:	00004f90 	muleq	r0, r0, pc	; <UNPREDICTABLE>
d001a670:	fffff374 			; <UNDEFINED> instruction: 0xfffff374
d001a674:	00004eec 	andeq	r4, r0, ip, ror #29
d001a678:	fffff2ea 			; <UNDEFINED> instruction: 0xfffff2ea
d001a67c:	00004ebc 			; <UNDEFINED> instruction: 0x00004ebc
d001a680:	00004e12 	andeq	r4, r0, r2, lsl lr
d001a684:	fffff235 			; <UNDEFINED> instruction: 0xfffff235
d001a688:	00004de6 	andeq	r4, r0, r6, ror #27
d001a68c:	00004dd2 	ldrdeq	r4, [r0], -r2
d001a690:	ffffda9c 			; <UNDEFINED> instruction: 0xffffda9c
d001a694:	ffffda95 			; <UNDEFINED> instruction: 0xffffda95
d001a698:	ffff8dde 			; <UNDEFINED> instruction: 0xffff8dde
d001a69c:	00004d8a 	andeq	r4, r0, sl, lsl #27
d001a6a0:	fffff1e3 			; <UNDEFINED> instruction: 0xfffff1e3
d001a6a4:	00004d0c 	andeq	r4, r0, ip, lsl #26
d001a6a8:	00004cbe 			; <UNDEFINED> instruction: 0x00004cbe
d001a6ac:	fffff11b 			; <UNDEFINED> instruction: 0xfffff11b
d001a6b0:	fffff06d 			; <UNDEFINED> instruction: 0xfffff06d
d001a6b4:	00004c26 	andeq	r4, r0, r6, lsr #24
d001a6b8:	00004bf4 	strdeq	r4, [r0], -r4	; <UNPREDICTABLE>
d001a6bc:	ffffefd8 			; <UNDEFINED> instruction: 0xffffefd8
d001a6c0:	fffff06a 			; <UNDEFINED> instruction: 0xfffff06a
d001a6c4:	00004ba6 	andeq	r4, r0, r6, lsr #23
d001a6c8:	00004b88 	andeq	r4, r0, r8, lsl #23
d001a6cc:	fffff067 			; <UNDEFINED> instruction: 0xfffff067
d001a6d0:	fffff074 			; <UNDEFINED> instruction: 0xfffff074
d001a6d4:	00004b44 	andeq	r4, r0, r4, asr #22
d001a6d8:	00004b1e 	andeq	r4, r0, lr, lsl fp
d001a6dc:	fffff051 			; <UNDEFINED> instruction: 0xfffff051
d001a6e0:	00004b08 	andeq	r4, r0, r8, lsl #22
d001a6e4:	fffff05b 			; <UNDEFINED> instruction: 0xfffff05b
d001a6e8:	00004ade 	ldrdeq	r4, [r0], -lr
d001a6ec:	00004aa4 	andeq	r4, r0, r4, lsr #21
d001a6f0:	fffff02a 			; <UNDEFINED> instruction: 0xfffff02a
d001a6f4:	00004a68 	andeq	r4, r0, r8, ror #20
d001a6f8:	00004a54 	andeq	r4, r0, r4, asr sl
d001a6fc:	00004a1e 	andeq	r4, r0, lr, lsl sl
d001a700:	00004974 	andeq	r4, r0, r4, ror r9
d001a704:	ffffcff6 			; <UNDEFINED> instruction: 0xffffcff6
d001a708:	00004904 	andeq	r4, r0, r4, lsl #18
d001a70c:	000048fc 	strdeq	r4, [r0], -ip
d001a710:	000048ca 	andeq	r4, r0, sl, asr #17
d001a714:	0000488e 	andeq	r4, r0, lr, lsl #17
d001a718:	ffffee3a 			; <UNDEFINED> instruction: 0xffffee3a
d001a71c:	0000486e 	andeq	r4, r0, lr, ror #16
d001a720:	ffffec54 			; <UNDEFINED> instruction: 0xffffec54
d001a724:	ffffee19 			; <UNDEFINED> instruction: 0xffffee19
d001a728:	ffffee1a 			; <UNDEFINED> instruction: 0xffffee1a
d001a72c:	ffffee19 			; <UNDEFINED> instruction: 0xffffee19
d001a730:	ffffee12 			; <UNDEFINED> instruction: 0xffffee12
d001a734:	000047fc 	strdeq	r4, [r0], -ip
d001a738:	ffffedef 			; <UNDEFINED> instruction: 0xffffedef
d001a73c:	24009b15 	strcs	r9, [r0], #-2837	; 0xfffff4eb
d001a740:	94202b04 	strtls	r2, [r0], #-2820	; 0xfffff4fc
d001a744:	4084f88d 	addmi	pc, r4, sp, lsl #17
d001a748:	f88d9422 			; <UNDEFINED> instruction: 0xf88d9422
d001a74c:	f040408c 			; <UNDEFINED> instruction: 0xf040408c
d001a750:	f8df808c 			; <UNDEFINED> instruction: 0xf8df808c
d001a754:	f44f4ab4 	vst1.32	{d20-d21}, [pc :256], r4
d001a758:	f8df7185 			; <UNDEFINED> instruction: 0xf8df7185
d001a75c:	447c2ab0 	ldrbtmi	r2, [ip], #-2736	; 0xfffff550
d001a760:	4620447a 			; <UNDEFINED> instruction: 0x4620447a
d001a764:	f7f8921b 			; <UNDEFINED> instruction: 0xf7f8921b
d001a768:	2800fab0 	stmdacs	r0, {r4, r5, r7, r9, fp, ip, sp, lr, pc}
d001a76c:	a8adf43f 	stmiage	sp!, {r0, r1, r2, r3, r4, r5, sl, ip, sp, lr, pc}
d001a770:	f2409a1b 	vpmin.s8	d25, d0, d11
d001a774:	4620110b 	strtmi	r1, [r0], -fp, lsl #2
d001a778:	faa7f7f8 	blx	0xcea18760
d001a77c:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001a780:	9a1ba8a4 	bls	0xd0704a18
d001a784:	4620212a 	strtmi	r2, [r0], -sl, lsr #2
d001a788:	fa9ff7f8 	blx	0xce818770
d001a78c:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001a790:	4620a89c 			; <UNDEFINED> instruction: 0x4620a89c
d001a794:	1101f240 	tstne	r1, r0, asr #4	; <UNPREDICTABLE>
d001a798:	fa89f7f8 	blx	0xce298780
d001a79c:	23022401 	movwcs	r2, #9217	; 0x2401
d001a7a0:	3080f88d 	addcc	pc, r0, sp, lsl #17
d001a7a4:	5a68f8df 	bpl	0xd1a58b28
d001a7a8:	f8df2129 			; <UNDEFINED> instruction: 0xf8df2129
d001a7ac:	447d2a68 	ldrbtmi	r2, [sp], #-2664	; 0xfffff598
d001a7b0:	4628447a 			; <UNDEFINED> instruction: 0x4628447a
d001a7b4:	fa89f7f8 	blx	0xce29879c
d001a7b8:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001a7bc:	9b15a886 	blls	0xd05849dc
d001a7c0:	d502071b 	strle	r0, [r2, #-1819]	; 0xfffff8e5
d001a7c4:	f0402c00 			; <UNDEFINED> instruction: 0xf0402c00
d001a7c8:	f8df8173 			; <UNDEFINED> instruction: 0xf8df8173
d001a7cc:	27008a4c 	strcs	r8, [r0, -ip, asr #20]
d001a7d0:	f50844f8 			; <UNDEFINED> instruction: 0xf50844f8
d001a7d4:	f50835e5 			; <UNDEFINED> instruction: 0xf50835e5
d001a7d8:	35dc39ff 	ldrbcc	r3, [ip, #2559]	; 0x9ff
d001a7dc:	30dcf8d9 	ldrsbcc	pc, [ip], #137	; 0x89	; <UNPREDICTABLE>
d001a7e0:	d21f429f 	andsle	r4, pc, #-268435447	; 0xf0000009
d001a7e4:	46522334 			; <UNDEFINED> instruction: 0x46522334
d001a7e8:	f607fb03 			; <UNDEFINED> instruction: 0xf607fb03
d001a7ec:	e9d5465b 	ldmib	r5, {r0, r1, r3, r4, r6, r9, sl, lr}^
d001a7f0:	f7f50100 			; <UNDEFINED> instruction: 0xf7f50100
d001a7f4:	2800febf 	stmdacs	r0, {r0, r1, r2, r3, r4, r5, r7, r9, sl, fp, ip, sp, lr, pc}
d001a7f8:	816cf000 	msrhi	SPSR_fs, r0
d001a7fc:	2028f895 	mlacs	r8, r5, r8, pc	; <UNPREDICTABLE>
d001a800:	3050f89d 			; <UNDEFINED> instruction: 0x3050f89d
d001a804:	f040429a 			; <UNDEFINED> instruction: 0xf040429a
d001a808:	9b148165 	blls	0xd053ada4
d001a80c:	f895b133 			; <UNDEFINED> instruction: 0xf895b133
d001a810:	f8982029 			; <UNDEFINED> instruction: 0xf8982029
d001a814:	429a3008 	addsmi	r3, sl, #8
d001a818:	815cf040 	cmphi	ip, r0, asr #32	; <UNPREDICTABLE>
d001a81c:	0900f1b7 	stmdbeq	r0, {r0, r1, r2, r4, r5, r7, r8, ip, sp, lr, pc}
d001a820:	84d4f280 	ldrbhi	pc, [r4], #640	; 0x280	; <UNPREDICTABLE>
d001a824:	59f4f8df 	ldmibpl	r4!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d001a828:	4651465a 			; <UNDEFINED> instruction: 0x4651465a
d001a82c:	4628447d 			; <UNDEFINED> instruction: 0x4628447d
d001a830:	ff97f7f5 			; <UNDEFINED> instruction: 0xff97f7f5
d001a834:	f2c02800 	vmlal.s8	q9, d0, d0
d001a838:	465a84b8 			; <UNDEFINED> instruction: 0x465a84b8
d001a83c:	46284651 			; <UNDEFINED> instruction: 0x46284651
d001a840:	ff8ff7f5 			; <UNDEFINED> instruction: 0xff8ff7f5
d001a844:	fb032334 	blx	0xd00e351e
d001a848:	7a2b5000 	bvc	0xd0aee850
d001a84c:	30e5f500 	rsccc	pc, r5, r0, lsl #10
d001a850:	2105f890 			; <UNDEFINED> instruction: 0x2105f890
d001a854:	f040429a 			; <UNDEFINED> instruction: 0xf040429a
d001a858:	6dab84a8 	cfstrsvs	mvf8, [fp, #672]!	; 0x2a0
d001a85c:	f47f2b00 			; <UNDEFINED> instruction: 0xf47f2b00
d001a860:	f8dfa834 			; <UNDEFINED> instruction: 0xf8dfa834
d001a864:	447b39bc 	ldrbtmi	r3, [fp], #-2492	; 0xfffff644
d001a868:	f8dfe129 			; <UNDEFINED> instruction: 0xf8dfe129
d001a86c:	447809b8 	ldrbtmi	r0, [r8], #-2488	; 0xfffff648
d001a870:	f5b36ac3 			; <UNDEFINED> instruction: 0xf5b36ac3
d001a874:	d1057f84 	smlabble	r5, r4, pc, r7	; <UNPREDICTABLE>
d001a878:	2b296cc3 	blcs	0xd0a75b8c
d001a87c:	f7f8d102 			; <UNDEFINED> instruction: 0xf7f8d102
d001a880:	e78ff9fb 			; <UNDEFINED> instruction: 0xe78ff9fb
d001a884:	79a0f8df 	stmibvc	r0!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d001a888:	f8dfae20 			; <UNDEFINED> instruction: 0xf8dfae20
d001a88c:	240059a0 	strcs	r5, [r0], #-2464	; 0xfffff660
d001a890:	447d447f 	ldrbtmi	r4, [sp], #-1151	; 0xfffffb81
d001a894:	4950f507 	ldmdbmi	r0, {r0, r1, r2, r8, sl, ip, sp, lr, pc}^
d001a898:	091cf109 	ldmdbeq	ip, {r0, r3, r8, ip, sp, lr, pc}
d001a89c:	d1512c01 	cmple	r1, r1, lsl #24
d001a8a0:	2b009b1b 	blcs	0xd0041514
d001a8a4:	f89dd04e 			; <UNDEFINED> instruction: 0xf89dd04e
d001a8a8:	2b003080 	blcs	0xd0026ab0
d001a8ac:	f8dfd14a 			; <UNDEFINED> instruction: 0xf8dfd14a
d001a8b0:	f2408980 	vmla.i8	d24, d16, d0
d001a8b4:	44f8110b 	ldrbtmi	r1, [r8], #267	; 0x10b
d001a8b8:	f7f84640 			; <UNDEFINED> instruction: 0xf7f84640
d001a8bc:	2800f9f8 	stmdacs	r0, {r3, r4, r5, r6, r7, r8, fp, ip, sp, lr, pc}
d001a8c0:	f8dfd040 			; <UNDEFINED> instruction: 0xf8dfd040
d001a8c4:	212a2970 			; <UNDEFINED> instruction: 0x212a2970
d001a8c8:	447a4640 	ldrbtmi	r4, [sl], #-1600	; 0xfffff9c0
d001a8cc:	f7f8921d 			; <UNDEFINED> instruction: 0xf7f8921d
d001a8d0:	2800f9fc 	stmdacs	r0, {r2, r3, r4, r5, r6, r7, r8, fp, ip, sp, lr, pc}
d001a8d4:	aff9f43e 	svcge	0x00f9f43e
d001a8d8:	212a9a1d 			; <UNDEFINED> instruction: 0x212a9a1d
d001a8dc:	f7f84640 			; <UNDEFINED> instruction: 0xf7f84640
d001a8e0:	2800f9f4 	stmdacs	r0, {r2, r4, r5, r6, r7, r8, fp, ip, sp, lr, pc}
d001a8e4:	aff1f43e 	svcge	0x00f1f43e
d001a8e8:	f88d2304 			; <UNDEFINED> instruction: 0xf88d2304
d001a8ec:	f8df3081 			; <UNDEFINED> instruction: 0xf8df3081
d001a8f0:	f10d8948 			; <UNDEFINED> instruction: 0xf10d8948
d001a8f4:	44f80cc8 	ldrbtmi	r0, [r8], #3272	; 0xcc8
d001a8f8:	1c44eb0c 	mcrrne	11, 0, lr, r4, cr12
d001a8fc:	f1083401 			; <UNDEFINED> instruction: 0xf1083401
d001a900:	e8be0e18 	ldm	lr!, {r3, r4, r9, sl, fp}
d001a904:	e8ac000f 	stmia	ip!, {r0, r1, r2, r3}
d001a908:	e89e000f 	ldm	lr, {r0, r1, r2, r3}
d001a90c:	e88c000f 	stm	ip, {r0, r1, r2, r3}
d001a910:	f240000f 	vhadd.s8	d16, d0, d15
d001a914:	46401101 	strbmi	r1, [r0], -r1, lsl #2
d001a918:	f9c9f7f8 			; <UNDEFINED> instruction: 0xf9c9f7f8
d001a91c:	3b01f816 	blcc	0xd009897c
d001a920:	f43f2b04 			; <UNDEFINED> instruction: 0xf43f2b04
d001a924:	212caf3f 			; <UNDEFINED> instruction: 0x212caf3f
d001a928:	f7f84640 			; <UNDEFINED> instruction: 0xf7f84640
d001a92c:	2800f9c0 	stmdacs	r0, {r6, r7, r8, fp, ip, sp, lr, pc}
d001a930:	af38f43f 	svcge	0x0038f43f
d001a934:	d1b12c05 			; <UNDEFINED> instruction: 0xd1b12c05
d001a938:	1900f8df 	stmdbne	r0, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}
d001a93c:	44794640 	ldrbtmi	r4, [r9], #-1600	; 0xfffff9c0
d001a940:	b9f0f7ff 	ldmiblt	r0!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}^
d001a944:	f7f54628 			; <UNDEFINED> instruction: 0xf7f54628
d001a948:	b1c0feed 	biclt	pc, r0, sp, ror #29
d001a94c:	a91f2300 	ldmdbge	pc, {r8, r9, sp}	; <UNPREDICTABLE>
d001a950:	931f4628 	tstls	pc, #40, 12	; 0x2800000
d001a954:	f9fcf7f8 			; <UNDEFINED> instruction: 0xf9fcf7f8
d001a958:	f43e2800 			; <UNDEFINED> instruction: 0xf43e2800
d001a95c:	f8dfafb6 			; <UNDEFINED> instruction: 0xf8dfafb6
d001a960:	212a28e0 			; <UNDEFINED> instruction: 0x212a28e0
d001a964:	447a4628 	ldrbtmi	r4, [sl], #-1576	; 0xfffff9d8
d001a968:	f9aff7f8 			; <UNDEFINED> instruction: 0xf9aff7f8
d001a96c:	f43e2800 			; <UNDEFINED> instruction: 0xf43e2800
d001a970:	230eafac 	movwcs	sl, #61356	; 0xefac
d001a974:	70339a1f 	eorsvc	r9, r3, pc, lsl sl
d001a978:	54e2ab22 	strbtpl	sl, [r2], #2850	; 0xb22
d001a97c:	f240e7b7 	vaba.s8	d30, d16, d23
d001a980:	46281107 	strtmi	r1, [r8], -r7, lsl #2
d001a984:	f993f7f8 			; <UNDEFINED> instruction: 0xf993f7f8
d001a988:	6aeab9e0 	bvs	0xcfac9110
d001a98c:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d001a990:	d123429a 			; <UNDEFINED> instruction: 0xd123429a
d001a994:	e9d54628 	ldmib	r5, {r3, r5, r9, sl, lr}^
d001a998:	f7f51206 			; <UNDEFINED> instruction: 0xf7f51206
d001a99c:	2800fe9e 	stmdacs	r0, {r1, r2, r3, r4, r7, r9, sl, fp, ip, sp, lr, pc}
d001a9a0:	4628db1c 			; <UNDEFINED> instruction: 0x4628db1c
d001a9a4:	1206e9d5 	andne	lr, r6, #3489792	; 0x354000
d001a9a8:	fe97f7f5 	mrc2	7, 4, pc, cr7, cr5, {7}
d001a9ac:	fb032324 	blx	0xd00e3646
d001a9b0:	f5005000 			; <UNDEFINED> instruction: 0xf5005000
d001a9b4:	f89030d8 			; <UNDEFINED> instruction: 0xf89030d8
d001a9b8:	2bff31ec 	blcs	0xcffe7170
d001a9bc:	4628d10e 	strtmi	sp, [r8], -lr, lsl #2
d001a9c0:	f95af7f8 			; <UNDEFINED> instruction: 0xf95af7f8
d001a9c4:	087cf8df 	ldmdaeq	ip!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d001a9c8:	4478212a 	ldrbtmi	r2, [r8], #-298	; 0xfffffed6
d001a9cc:	f96ff7f8 			; <UNDEFINED> instruction: 0xf96ff7f8
d001a9d0:	bf142800 	svclt	0x00142800
d001a9d4:	2300230a 	movwcs	r2, #778	; 0x30a
d001a9d8:	e7887033 			; <UNDEFINED> instruction: 0xe7887033
d001a9dc:	0868f8df 	stmdaeq	r8!, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d001a9e0:	f7f94478 			; <UNDEFINED> instruction: 0xf7f94478
d001a9e4:	b108fb63 	tstlt	r8, r3, ror #22	; <UNPREDICTABLE>
d001a9e8:	e7f52303 	ldrb	r2, [r5, r3, lsl #6]!
d001a9ec:	085cf8df 	ldmdaeq	ip, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d001a9f0:	f7f94478 			; <UNDEFINED> instruction: 0xf7f94478
d001a9f4:	b108fb5b 	tstlt	r8, fp, asr fp	; <UNPREDICTABLE>
d001a9f8:	e7ed2301 	strb	r2, [sp, r1, lsl #6]!
d001a9fc:	0850f8df 	ldmdaeq	r0, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d001aa00:	f7f94478 			; <UNDEFINED> instruction: 0xf7f94478
d001aa04:	b108fb53 	tstlt	r8, r3, asr fp	; <UNPREDICTABLE>
d001aa08:	e7e52305 	strb	r2, [r5, r5, lsl #6]!
d001aa0c:	0844f8df 	stmdaeq	r4, {r0, r1, r2, r3, r4, r6, r7, fp, ip, sp, lr, pc}^
d001aa10:	f7f94478 			; <UNDEFINED> instruction: 0xf7f94478
d001aa14:	2800fb4b 	stmdacs	r0, {r0, r1, r3, r6, r8, r9, fp, ip, sp, lr, pc}
d001aa18:	f8d9d1f6 			; <UNDEFINED> instruction: 0xf8d9d1f6
d001aa1c:	2b003000 	blcs	0xd0026a24
d001aa20:	f44fd03e 	vst4.8	{d29-d32}, [pc :256], lr
d001aa24:	46387185 	ldrtmi	r7, [r8], -r5, lsl #3
d001aa28:	f941f7f8 			; <UNDEFINED> instruction: 0xf941f7f8
d001aa2c:	f8dfb318 			; <UNDEFINED> instruction: 0xf8dfb318
d001aa30:	44780828 	ldrbtmi	r0, [r8], #-2088	; 0xfffff7d8
d001aa34:	fb3af7f9 	blx	0xd0ed8a22
d001aa38:	f8dfb938 			; <UNDEFINED> instruction: 0xf8dfb938
d001aa3c:	f8df1820 			; <UNDEFINED> instruction: 0xf8df1820
d001aa40:	44790820 	ldrbtmi	r0, [r9], #-2080	; 0xfffff7e0
d001aa44:	f7ff4478 			; <UNDEFINED> instruction: 0xf7ff4478
d001aa48:	f8dfb96d 			; <UNDEFINED> instruction: 0xf8dfb96d
d001aa4c:	212a2818 			; <UNDEFINED> instruction: 0x212a2818
d001aa50:	447a4638 	ldrbtmi	r4, [sl], #-1592	; 0xfffff9c8
d001aa54:	f939f7f8 			; <UNDEFINED> instruction: 0xf939f7f8
d001aa58:	d0ee2800 	rscle	r2, lr, r0, lsl #16
d001aa5c:	435df507 	cmpmi	sp, #29360128	; 0x1c00000	; <UNPREDICTABLE>
d001aa60:	881b33f4 	ldmdahi	fp, {r2, r4, r5, r6, r7, r8, r9, ip, sp}
d001aa64:	f8dfb92b 			; <UNDEFINED> instruction: 0xf8dfb92b
d001aa68:	46381800 	ldrtmi	r1, [r8], -r0, lsl #16
d001aa6c:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d001aa70:	2306b959 	movwcs	fp, #26969	; 0x6959
d001aa74:	f8d9e7b0 			; <UNDEFINED> instruction: 0xf8d9e7b0
d001aa78:	b18b3000 	orrlt	r3, fp, r0
d001aa7c:	7184f44f 	orrvc	pc, r4, pc, asr #8
d001aa80:	f7f84638 			; <UNDEFINED> instruction: 0xf7f84638
d001aa84:	b158f914 	cmplt	r8, r4, lsl r9	; <UNPREDICTABLE>
d001aa88:	27e0f8df 	ubfxcs	pc, pc, #17, #1
d001aa8c:	4638212a 	ldrtmi	r2, [r8], -sl, lsr #2
d001aa90:	f7f8447a 			; <UNDEFINED> instruction: 0xf7f8447a
d001aa94:	2800f91a 	stmdacs	r0, {r1, r3, r4, r8, fp, ip, sp, lr, pc}
d001aa98:	af17f43e 	svcge	0x0017f43e
d001aa9c:	e79b2302 	ldr	r2, [fp, r2, lsl #6]
d001aaa0:	17ccf8df 			; <UNDEFINED> instruction: 0x17ccf8df
d001aaa4:	07ccf8df 			; <UNDEFINED> instruction: 0x07ccf8df
d001aaa8:	44784479 	ldrbtmi	r4, [r8], #-1145	; 0xfffffb87
d001aaac:	b93af7ff 	ldmdblt	sl!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, ip, sp, lr, pc}
d001aab0:	2b006dab 	blcs	0xd0036164
d001aab4:	af09f47e 	svcge	0x0009f47e
d001aab8:	37bcf8df 	sbfxcc	pc, pc, #17, #29
d001aabc:	65ab447b 	strvs	r4, [fp, #1147]!	; 0x47b
d001aac0:	65eb9b11 	strbvs	r9, [fp, #2833]!	; 0xb11
d001aac4:	662b9b0f 	strtvs	r9, [fp], -pc, lsl #22
d001aac8:	666b9b12 			; <UNDEFINED> instruction: 0x666b9b12
d001aacc:	66ab9b10 	ssatvs	r9, #12, r0, lsl #22
d001aad0:	befbf7fe 	mrclt	7, 7, APSR_nzcv, cr11, cr14, {7}
d001aad4:	35343701 	ldrcc	r3, [r4, #-1793]!	; 0xfffff8ff
d001aad8:	1c7ae680 	ldclne	6, cr14, [sl], #-512	; 0xfffffe00
d001aadc:	210046b9 			; <UNDEFINED> instruction: 0x210046b9
d001aae0:	20dcf8c3 	sbcscs	pc, ip, r3, asr #17
d001aae4:	7a2b2234 	bvc	0xd0ae33bc
d001aae8:	f607fb02 			; <UNDEFINED> instruction: 0xf607fb02
d001aaec:	eb05931b 	bl	0xd017f760
d001aaf0:	f5060806 			; <UNDEFINED> instruction: 0xf5060806
d001aaf4:	f50836e5 			; <UNDEFINED> instruction: 0xf50836e5
d001aaf8:	f10837e5 			; <UNDEFINED> instruction: 0xf10837e5
d001aafc:	f1071801 			; <UNDEFINED> instruction: 0xf1071801
d001ab00:	f50803dc 			; <UNDEFINED> instruction: 0xf50803dc
d001ab04:	4618484b 	ldrmi	r4, [r8], -fp, asr #16
d001ab08:	fcaaf001 	stc2	0, cr15, [sl], #4
d001ab0c:	f10d9a11 			; <UNDEFINED> instruction: 0xf10d9a11
d001ab10:	46840ea8 	strmi	r0, [r4], r8, lsr #29
d001ab14:	9a0f922d 	bls	0xd03ff3d0
d001ab18:	4100f887 	smlabbmi	r0, r7, r8, pc	; <UNPREDICTABLE>
d001ab1c:	9a12922e 	bls	0xd04bf3dc
d001ab20:	20c0f88d 	sbccs	pc, r0, sp, lsl #17
d001ab24:	e9cd9a10 	stmib	sp, {r4, r9, fp, ip, pc}^
d001ab28:	9231ab2a 	eorsls	sl, r1, #43008	; 0xa800
d001ab2c:	000fe8be 			; <UNDEFINED> instruction: 0x000fe8be
d001ab30:	000fe8ac 	andeq	lr, pc, ip, lsr #17
d001ab34:	000fe89e 	muleq	pc, lr, r8	; <UNPREDICTABLE>
d001ab38:	000fe88c 	andeq	lr, pc, ip, lsl #17
d001ab3c:	f5069b15 			; <UNDEFINED> instruction: 0xf5069b15
d001ab40:	46227083 	strtmi	r7, [r2], -r3, lsl #1
d001ab44:	f1b3a920 			; <UNDEFINED> instruction: 0xf1b3a920
d001ab48:	f8c70b00 			; <UNDEFINED> instruction: 0xf8c70b00
d001ab4c:	f88830fc 			; <UNDEFINED> instruction: 0xf88830fc
d001ab50:	44283000 	strtmi	r3, [r8], #-0
d001ab54:	f04fbf18 			; <UNDEFINED> instruction: 0xf04fbf18
d001ab58:	9b130b01 	blls	0xd04dd764
d001ab5c:	b102f887 	smlabblt	r2, r7, r8, pc	; <UNPREDICTABLE>
d001ab60:	3103f887 	smlabbcc	r3, r7, r8, pc	; <UNPREDICTABLE>
d001ab64:	f8879b14 			; <UNDEFINED> instruction: 0xf8879b14
d001ab68:	9b1b3104 	blls	0xd06e6f80
d001ab6c:	3105f887 	smlabbcc	r5, r7, r8, pc	; <UNPREDICTABLE>
d001ab70:	fc84f001 	stc2	0, cr15, [r4], {1}
d001ab74:	100bf206 	andne	pc, fp, r6, lsl #4
d001ab78:	a9224622 	stmdbge	r2!, {r1, r5, r9, sl, lr}
d001ab7c:	f0014428 			; <UNDEFINED> instruction: 0xf0014428
d001ab80:	f8dffc7d 			; <UNDEFINED> instruction: 0xf8dffc7d
d001ab84:	213b66f8 	teqcs	fp, r8	; <illegal shifter operand>
d001ab88:	4630447e 			; <UNDEFINED> instruction: 0x4630447e
d001ab8c:	f88ff7f8 			; <UNDEFINED> instruction: 0xf88ff7f8
d001ab90:	f47e2800 			; <UNDEFINED> instruction: 0xf47e2800
d001ab94:	2734ae9a 			; <UNDEFINED> instruction: 0x2734ae9a
d001ab98:	6709fb07 	strvs	pc, [r9, -r7, lsl #22]
d001ab9c:	37e5f507 	strbcc	pc, [r5, r7, lsl #10]!	; <UNPREDICTABLE>
d001aba0:	5102f897 			; <UNDEFINED> instruction: 0x5102f897
d001aba4:	6db3b1f5 	ldfvsd	f3, [r3, #980]!	; 0x3d4
d001aba8:	f47e2b00 			; <UNDEFINED> instruction: 0xf47e2b00
d001abac:	f8dfae8e 			; <UNDEFINED> instruction: 0xf8dfae8e
d001abb0:	447b36d0 	ldrbtmi	r3, [fp], #-1744	; 0xfffff930
d001abb4:	baddf7ff 	blt	0xcf798bb8
d001abb8:	36e5f506 	strbtcc	pc, [r5], r6, lsl #10	; <UNPREDICTABLE>
d001abbc:	a9204622 	stmdbge	r0!, {r1, r5, r9, sl, lr}
d001abc0:	7083f506 	addvc	pc, r3, r6, lsl #10
d001abc4:	f0014428 			; <UNDEFINED> instruction: 0xf0014428
d001abc8:	2800fc69 	stmdacs	r0, {r0, r3, r5, r6, sl, fp, ip, sp, lr, pc}
d001abcc:	830ff040 	movwhi	pc, #61504	; 0xf040	; <UNPREDICTABLE>
d001abd0:	160bf206 	strne	pc, [fp], -r6, lsl #4
d001abd4:	a9224622 	stmdbge	r2!, {r1, r5, r9, sl, lr}
d001abd8:	f00119a8 			; <UNDEFINED> instruction: 0xf00119a8
d001abdc:	2800fc5f 	stmdacs	r0, {r0, r1, r2, r3, r4, r6, sl, fp, ip, sp, lr, pc}
d001abe0:	e304d0cf 	movw	sp, #16591	; 0x40cf
d001abe4:	269cf8df 			; <UNDEFINED> instruction: 0x269cf8df
d001abe8:	4630217b 			; <UNDEFINED> instruction: 0x4630217b
d001abec:	f7f8447a 			; <UNDEFINED> instruction: 0xf7f8447a
d001abf0:	2800f86c 	stmdacs	r0, {r2, r3, r5, r6, fp, ip, sp, lr, pc}
d001abf4:	ae69f43e 	mcrge	4, 3, pc, cr9, cr14, {1}	; <UNPREDICTABLE>
d001abf8:	485df506 	ldmdami	sp, {r1, r2, r8, sl, ip, sp, lr, pc}^
d001abfc:	3213f506 	andscc	pc, r3, #25165824	; 0x1800000
d001ac00:	b684f8df 	pkhtblt	pc, r4, pc, asr #17	; <UNPREDICTABLE>
d001ac04:	f8d84630 			; <UNDEFINED> instruction: 0xf8d84630
d001ac08:	f24b30f8 	vqadd.s8	<illegal reg q9.5>, <illegal reg q13.5>, q12
d001ac0c:	f8c25180 			; <UNDEFINED> instruction: 0xf8c25180
d001ac10:	f10d52e4 			; <UNDEFINED> instruction: 0xf10d52e4
d001ac14:	f8c70ac8 			; <UNDEFINED> instruction: 0xf8c70ac8
d001ac18:	230130fc 	movwcs	r3, #4348	; 0x10fc
d001ac1c:	44fb46a9 	ldrbtmi	r4, [fp], #1705	; 0x6a9
d001ac20:	3102f887 	smlabbcc	r2, r7, r8, pc	; <UNPREDICTABLE>
d001ac24:	3316f506 	tstcc	r6, #25165824	; 0x1800000	; <UNPREDICTABLE>
d001ac28:	51f4f8c3 	mvnspl	pc, r3, asr #17
d001ac2c:	51f0f8c3 	mvnspl	pc, r3, asr #17
d001ac30:	51ecf8c3 	mvnpl	pc, r3, asr #17
d001ac34:	5200f8c3 	andpl	pc, r0, #12779520	; 0xc30000
d001ac38:	51fcf8c3 	mvnspl	pc, r3, asr #17
d001ac3c:	331ef506 	tstcc	lr, #25165824	; 0x1800000	; <UNPREDICTABLE>
d001ac40:	524cf8c3 	subpl	pc, ip, #12779520	; 0xc30000
d001ac44:	331af506 	tstcc	sl, #25165824	; 0x1800000	; <UNPREDICTABLE>
d001ac48:	f8c3ae20 			; <UNDEFINED> instruction: 0xf8c3ae20
d001ac4c:	f8c35248 			; <UNDEFINED> instruction: 0xf8c35248
d001ac50:	f8975204 			; <UNDEFINED> instruction: 0xf8975204
d001ac54:	f8823103 			; <UNDEFINED> instruction: 0xf8823103
d001ac58:	f7f932e8 			; <UNDEFINED> instruction: 0xf7f932e8
d001ac5c:	4629fa73 			; <UNDEFINED> instruction: 0x4629fa73
d001ac60:	70f8f8d8 	ldrsbtvc	pc, [r8], #136	; 0x88	; <UNPREDICTABLE>
d001ac64:	fa6ef7f9 	blx	0xd1bd8c50
d001ac68:	412ff44f 	msrmi	CPSR_fsxc, pc, asr #8
d001ac6c:	fa6af7f9 	blx	0xd1ad8c58
d001ac70:	d14c42ac 	smlaltble	r4, ip, ip, r2
d001ac74:	fa96f7fd 	blx	0xce5d8c70
d001ac78:	0610f8df 			; <UNDEFINED> instruction: 0x0610f8df
d001ac7c:	f5004478 			; <UNDEFINED> instruction: 0xf5004478
d001ac80:	f8933313 			; <UNDEFINED> instruction: 0xf8933313
d001ac84:	2b0132e8 	blcs	0xd006782c
d001ac88:	2100d002 	tstcs	r0, r2
d001ac8c:	fab6f7f9 	blx	0xcedd8c78
d001ac90:	05fcf8df 	ldrbeq	pc, [ip, #2271]!	; 0x8df	; <UNPREDICTABLE>
d001ac94:	f5004478 			; <UNDEFINED> instruction: 0xf5004478
d001ac98:	f8d3435d 			; <UNDEFINED> instruction: 0xf8d3435d
d001ac9c:	f50080f8 			; <UNDEFINED> instruction: 0xf50080f8
d001aca0:	f8d33316 			; <UNDEFINED> instruction: 0xf8d33316
d001aca4:	340141f0 	strcc	r4, [r1], #-496	; 0xfffffe10
d001aca8:	0401f024 	streq	pc, [r1], #-36	; 0xffffffdc
d001acac:	f445b2a5 	vst1.32	{d27-d30}, [r5 :128], r5
d001acb0:	f7f94130 			; <UNDEFINED> instruction: 0xf7f94130
d001acb4:	f64bfa47 			; <UNDEFINED> instruction: 0xf64bfa47
d001acb8:	f7f95180 			; <UNDEFINED> instruction: 0xf7f95180
d001acbc:	6d83fa43 	vstrvs	s30, [r3, #268]	; 0x10c
d001acc0:	f47e2b00 			; <UNDEFINED> instruction: 0xf47e2b00
d001acc4:	f8dfae02 			; <UNDEFINED> instruction: 0xf8dfae02
d001acc8:	f44535cc 	vst3.<illegal width 64>	{d19,d21,d23}, [r5], ip
d001accc:	447b4530 	ldrbtmi	r4, [fp], #-1328	; 0xfffffad0
d001acd0:	0580f045 	streq	pc, [r0, #69]	; 0x45
d001acd4:	f887441f 			; <UNDEFINED> instruction: 0xf887441f
d001acd8:	0a2d5040 	beq	0xd0b6ede0
d001acdc:	5041f887 	subpl	pc, r1, r7, lsl #17
d001ace0:	0f00f1b9 	svceq	0x0000f1b9
d001ace4:	3402d008 	strcc	sp, [r2], #-8
d001ace8:	00a44499 	umlaleq	r4, r4, r9, r4	; <UNPREDICTABLE>
d001acec:	f889b2a4 			; <UNDEFINED> instruction: 0xf889b2a4
d001acf0:	0a244040 	beq	0xd092adf8
d001acf4:	4041f889 	submi	pc, r1, r9, lsl #17
d001acf8:	459cf8df 	ldrmi	pc, [ip, #2271]	; 0x8df
d001acfc:	447c2600 	ldrbtmi	r2, [ip], #-1536	; 0xfffffa00
d001ad00:	350ff504 	strcc	pc, [pc, #-1284]	; 0xd001a804
d001ad04:	3713f504 	ldrcc	pc, [r3, -r4, lsl #10]
d001ad08:	7539f505 	ldrvc	pc, [r9, #-1285]!	; 0xfffffafb
d001ad0c:	f8dae073 			; <UNDEFINED> instruction: 0xf8dae073
d001ad10:	f2402014 	vqadd.s8	d18, d0, d4
d001ad14:	429a1301 	addsmi	r1, sl, #67108864	; 0x4000000
d001ad18:	f8dfd017 			; <UNDEFINED> instruction: 0xf8dfd017
d001ad1c:	447a2580 	ldrbtmi	r2, [sl], #-1408	; 0xfffffa80
d001ad20:	2b006d93 	blcs	0xd0036374
d001ad24:	add1f47e 	cfldrdge	mvd15, [r1, #504]	; 0x1f8
d001ad28:	eb03ab32 	bl	0xd01059f8
d001ad2c:	68ec1545 	stmiavs	ip!, {r0, r2, r6, r8, sl, ip}^
d001ad30:	69eb6928 	stmibvs	fp!, {r3, r5, r8, fp, sp, lr}^
d001ad34:	f8df7e29 			; <UNDEFINED> instruction: 0xf8df7e29
d001ad38:	66935568 	ldrvs	r5, [r3], r8, ror #10
d001ad3c:	e9c2447d 	stmib	r2, {r0, r2, r3, r4, r5, r6, sl, lr}^
d001ad40:	e9c20118 	stmib	r2, {r3, r4, r8}^
d001ad44:	f7fe5416 			; <UNDEFINED> instruction: 0xf7fe5416
d001ad48:	ab5abdc0 	blge	0xd16ca450
d001ad4c:	eb037832 	bl	0xd00f8e1c
d001ad50:	92041345 	andls	r1, r4, #335544321	; 0x14000001
d001ad54:	0ca0f1a3 	stfeqd	f7, [r0], #652	; 0x28c
d001ad58:	cb0f3b90 	blgt	0xd03e9ba0
d001ad5c:	000fe88d 	andeq	lr, pc, sp, lsl #17
d001ad60:	000fe89c 	muleq	pc, ip, r8	; <UNPREDICTABLE>
d001ad64:	fc60f7f8 	stc2l	7, cr15, [r0], #-992	; 0xfffffc20
d001ad68:	46807833 			; <UNDEFINED> instruction: 0x46807833
d001ad6c:	d1352b0e 	teqle	r5, lr, lsl #22
d001ad70:	3530f8df 	ldrcc	pc, [r0, #-2271]!	; 0xfffff721
d001ad74:	2d04222c 	sfmcs	f2, 4, [r4, #-176]	; 0xffffff50
d001ad78:	fb02447b 	blx	0xd00abf6e
d001ad7c:	aa223300 	bge	0xd08a7984
d001ad80:	3313f503 	tstcc	r3, #12582912	; 0xc00000	; <UNPREDICTABLE>
d001ad84:	f8835caa 			; <UNDEFINED> instruction: 0xf8835caa
d001ad88:	d12b230e 			; <UNDEFINED> instruction: 0xd12b230e
d001ad8c:	01d7f64f 	bicseq	pc, r7, pc, asr #12
d001ad90:	0a10ee18 	beq	0xd04565f8
d001ad94:	f9d6f7f9 			; <UNDEFINED> instruction: 0xf9d6f7f9
d001ad98:	21009b1a 	tstcs	r0, sl, lsl fp
d001ad9c:	9000f8d3 	ldrdls	pc, [r0], -r3
d001ada0:	f9d0f7f9 			; <UNDEFINED> instruction: 0xf9d0f7f9
d001ada4:	78332200 	ldmdavc	r3!, {r9, sp}
d001ada8:	d10c2b05 	tstle	ip, r5, lsl #22
d001adac:	4658b291 			; <UNDEFINED> instruction: 0x4658b291
d001adb0:	ea41920f 	b	0xd107f5f4
d001adb4:	f44101c1 	vst4.<illegal width 64>	{d16,d18,d20,d22}, [r1], r1
d001adb8:	f0414132 			; <UNDEFINED> instruction: 0xf0414132
d001adbc:	b28901c0 	addlt	r0, r9, #192, 2	; 0x30
d001adc0:	f9c0f7f9 			; <UNDEFINED> instruction: 0xf9c0f7f9
d001adc4:	f8df9a0f 			; <UNDEFINED> instruction: 0xf8df9a0f
d001adc8:	464104e0 	strbmi	r0, [r1], -r0, ror #9
d001adcc:	36013501 	strcc	r3, [r1], -r1, lsl #10
d001add0:	f10a4478 			; <UNDEFINED> instruction: 0xf10a4478
d001add4:	f7f90a20 			; <UNDEFINED> instruction: 0xf7f90a20
d001add8:	e749fa4b 	strb	pc, [r9, -fp, asr #20]	; <UNPREDICTABLE>
d001addc:	d0d52d04 	sbcsle	r2, r5, r4, lsl #26
d001ade0:	e7e0462a 	strb	r4, [r0, sl, lsr #12]!
d001ade4:	e7ee462a 	strb	r4, [lr, sl, lsr #12]!
d001ade8:	23003601 	movwcs	r3, #1537	; 0x601
d001adec:	f8554642 			; <UNDEFINED> instruction: 0xf8554642
d001adf0:	f7fa1b04 			; <UNDEFINED> instruction: 0xf7fa1b04
d001adf4:	f8d7f8b5 			; <UNDEFINED> instruction: 0xf8d7f8b5
d001adf8:	6da032e4 	sfmvs	f3, 4, [r0, #912]!	; 0x390
d001adfc:	d3f3429e 	mvnsle	r4, #-536870903	; 0xe0000009
d001ae00:	bd63f7fe 	stcllt	7, cr15, [r3, #-1016]!	; 0xfffffc08
d001ae04:	f47e2b00 			; <UNDEFINED> instruction: 0xf47e2b00
d001ae08:	f8dface9 			; <UNDEFINED> instruction: 0xf8dface9
d001ae0c:	220414a0 	andcs	r1, r4, #160, 8	; 0xa0000000
d001ae10:	44794620 	ldrbtmi	r4, [r9], #-1568	; 0xfffff9e0
d001ae14:	fca5f7f5 	stc2	7, cr15, [r5], #980	; 0x3d4
d001ae18:	db0e2800 	blle	0xd03a4e20
d001ae1c:	fb032334 	blx	0xd00e3af6
d001ae20:	f5044400 			; <UNDEFINED> instruction: 0xf5044400
d001ae24:	f89434e5 			; <UNDEFINED> instruction: 0xf89434e5
d001ae28:	b1333102 	teqlt	r3, r2, lsl #2
d001ae2c:	3100f894 			; <UNDEFINED> instruction: 0x3100f894
d001ae30:	f894b16b 			; <UNDEFINED> instruction: 0xf894b16b
d001ae34:	2b043107 	blcs	0xd0127258
d001ae38:	f8dfd009 			; <UNDEFINED> instruction: 0xf8dfd009
d001ae3c:	f8df1474 			; <UNDEFINED> instruction: 0xf8df1474
d001ae40:	44790474 	ldrbtmi	r0, [r9], #-1140	; 0xfffffb8c
d001ae44:	f7f54478 			; <UNDEFINED> instruction: 0xf7f54478
d001ae48:	f7fef9af 			; <UNDEFINED> instruction: 0xf7fef9af
d001ae4c:	f8dfbcc7 			; <UNDEFINED> instruction: 0xf8dfbcc7
d001ae50:	23344468 	teqcs	r4, #104, 8	; 0x68000000
d001ae54:	fb03447c 	blx	0xd00ec04e
d001ae58:	23004000 	movwcs	r4, #0
d001ae5c:	30e5f500 	rsccc	pc, r5, r0, lsl #10
d001ae60:	f8d04619 			; <UNDEFINED> instruction: 0xf8d04619
d001ae64:	6da020fc 	stcvs	0, cr2, [r0, #1008]!	; 0x3f0
d001ae68:	f87af7fa 			; <UNDEFINED> instruction: 0xf87af7fa
d001ae6c:	bcb6f7fe 	ldclt	7, cr15, [r6], #1016	; 0x3f8
d001ae70:	233488aa 	teqcs	r4, #11141120	; 0xaa0000
d001ae74:	18e14353 	stmiane	r1!, {r0, r1, r4, r6, r8, r9, lr}^
d001ae78:	31e5f501 	mvncc	pc, r1, lsl #10
d001ae7c:	2102f891 			; <UNDEFINED> instruction: 0x2102f891
d001ae80:	d1482a00 	cmple	r8, r0, lsl #20
d001ae84:	33e5f503 	mvncc	pc, #12582912	; 0xc00000
d001ae88:	442333dc 	strtmi	r3, [r3], #-988	; 0xfffffc24
d001ae8c:	691968d8 	ldmdbvs	r9, {r3, r4, r6, r7, fp, sp, lr}
d001ae90:	7e1b69da 			; <UNDEFINED> instruction: 0x7e1b69da
d001ae94:	e9c466a2 	stmib	r4, {r1, r5, r7, r9, sl, sp, lr}^
d001ae98:	e9c48016 	stmib	r4, {r1, r2, r4, pc}^
d001ae9c:	36011318 			; <UNDEFINED> instruction: 0x36011318
d001aea0:	f8d73508 			; <UNDEFINED> instruction: 0xf8d73508
d001aea4:	429e32e0 	addsmi	r3, lr, #224, 4
d001aea8:	6da3d202 	sfmvs	f5, 1, [r3, #8]!
d001aeac:	d0df2b00 	sbcsle	r2, pc, r0, lsl #22
d001aeb0:	3408f8df 	strcc	pc, [r8], #-2271	; 0xfffff721
d001aeb4:	52f8f64d 	rscspl	pc, r8, #80740352	; 0x4d00000
d001aeb8:	5899447b 	ldmpl	r9, {r0, r1, r3, r4, r5, r6, sl, lr}
d001aebc:	52fcf64d 	rscspl	pc, ip, #80740352	; 0x4d00000
d001aec0:	f503589a 			; <UNDEFINED> instruction: 0xf503589a
d001aec4:	eb0133dd 	bl	0xd0067e40
d001aec8:	f8d30902 			; <UNDEFINED> instruction: 0xf8d30902
d001aecc:	f10960d0 			; <UNDEFINED> instruction: 0xf10960d0
d001aed0:	f0270703 			; <UNDEFINED> instruction: 0xf0270703
d001aed4:	b32e0703 			; <UNDEFINED> instruction: 0xb32e0703
d001aed8:	f106443e 			; <UNDEFINED> instruction: 0xf106443e
d001aedc:	f5b6031f 			; <UNDEFINED> instruction: 0xf5b6031f
d001aee0:	f0233f80 			; <UNDEFINED> instruction: 0xf0233f80
d001aee4:	9310031f 	tstls	r0, #2080374784	; 0x7c000000
d001aee8:	49f5d905 	ldmibmi	r5!, {r0, r2, r8, fp, ip, lr, pc}^
d001aeec:	447948f5 	ldrbtmi	r4, [r9], #-2293	; 0xfffff70b
d001aef0:	f7f54478 			; <UNDEFINED> instruction: 0xf7f54478
d001aef4:	4cf4f959 			; <UNDEFINED> instruction: 0x4cf4f959
d001aef8:	0800f04f 	stmdaeq	r0, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d001aefc:	447c4bf3 	ldrbtmi	r4, [ip], #-3059	; 0xfffff40d
d001af00:	803cf8cd 	eorshi	pc, ip, sp, asr #17
d001af04:	f504447b 			; <UNDEFINED> instruction: 0xf504447b
d001af08:	f5044b5d 			; <UNDEFINED> instruction: 0xf5044b5d
d001af0c:	93113a8f 	tstls	r1, #585728	; 0x8f000
d001af10:	0bf8f10b 	bleq	0xcfe57344
d001af14:	2201e031 	andcs	lr, r1, #49	; 0x31
d001af18:	10fcf8d1 	ldrsbtne	pc, [ip], #129	; 0x81	; <UNPREDICTABLE>
d001af1c:	f7f96828 			; <UNDEFINED> instruction: 0xf7f96828
d001af20:	e7bcffeb 	ldr	pc, [ip, fp, ror #31]!
d001af24:	e7d8464e 	ldrb	r4, [r8, lr, asr #12]
d001af28:	2006f89a 	mulcs	r6, sl, r8
d001af2c:	0000f8da 	ldrdeq	pc, [r0], -sl
d001af30:	c004f8ba 			; <UNDEFINED> instruction: 0xc004f8ba
d001af34:	f8dbbb52 			; <UNDEFINED> instruction: 0xf8dbbb52
d001af38:	44633000 	strbtmi	r3, [r3], #-0
d001af3c:	050cf100 	streq	pc, [ip, #-256]	; 0xffffff00
d001af40:	3cfff102 	ldfccp	f7, [pc], #8	; 0xd001af50
d001af44:	2140f24f 	cmpcs	r0, pc, asr #4	; <UNPREDICTABLE>
d001af48:	f0259012 			; <UNDEFINED> instruction: 0xf0259012
d001af4c:	f1dc0503 			; <UNDEFINED> instruction: 0xf1dc0503
d001af50:	f1080200 			; <UNDEFINED> instruction: 0xf1080200
d001af54:	f10a0801 			; <UNDEFINED> instruction: 0xf10a0801
d001af58:	eba30a08 	bl	0xce8dd780
d001af5c:	eb420505 	bl	0xd109c378
d001af60:	b2ab020c 	adclt	r0, fp, #12, 4	; 0xc0000000
d001af64:	f7f99213 			; <UNDEFINED> instruction: 0xf7f99213
d001af68:	9812f8bd 	ldmdals	r2, {r0, r2, r3, r4, r5, r7, fp, ip, sp, lr, pc}
d001af6c:	9a130c2b 	bls	0xd04de020
d001af70:	21c0f24f 	biccs	pc, r0, pc, asr #4
d001af74:	f7f93004 			; <UNDEFINED> instruction: 0xf7f93004
d001af78:	f504f8b5 			; <UNDEFINED> instruction: 0xf504f8b5
d001af7c:	6da335af 	cfstr32vs	mvfx3, [r3, #700]!	; 0x2bc
d001af80:	4590682a 	ldrmi	r6, [r0, #2090]	; 0x82a
d001af84:	2b00d252 	blcs	0xd004f8d4
d001af88:	e03cd0ce 	eors	sp, ip, lr, asr #1
d001af8c:	f04f2a01 			; <UNDEFINED> instruction: 0xf04f2a01
d001af90:	d1210334 			; <UNDEFINED> instruction: 0xd1210334
d001af94:	430cfb03 	movwmi	pc, #51971	; 0xcb03	; <UNPREDICTABLE>
d001af98:	31aff503 			; <UNDEFINED> instruction: 0x31aff503
d001af9c:	302ff891 	mlacc	pc, r1, r8, pc	; <UNPREDICTABLE>
d001afa0:	f891b9c3 			; <UNDEFINED> instruction: 0xf891b9c3
d001afa4:	3b07302c 	blcc	0xd01e705c
d001afa8:	2b0ab2db 	blcs	0xd02c7b1c
d001afac:	f240d812 	vtst.8	d29, d0, d2
d001afb0:	fa215103 	blx	0xd086f3c4
d001afb4:	f013f303 			; <UNDEFINED> instruction: 0xf013f303
d001afb8:	9b100f01 	blls	0xd041ebc4
d001afbc:	463dbf0c 	ldrtmi	fp, [sp], -ip, lsl #30
d001afc0:	2334461d 	teqcs	r4, #30408704	; 0x1d00000
d001afc4:	fb039911 	blx	0xd0101412
d001afc8:	f503130c 			; <UNDEFINED> instruction: 0xf503130c
d001afcc:	6a9b33af 	bvs	0xce6e7e90
d001afd0:	e7b3442b 	ldr	r4, [r3, fp, lsr #8]!
d001afd4:	e7f4463d 			; <UNDEFINED> instruction: 0xe7f4463d
d001afd8:	f30cfb03 	vqrdmulh.s<illegal width 8>	d15, d12, d3
d001afdc:	f50118e1 			; <UNDEFINED> instruction: 0xf50118e1
d001afe0:	f89131e5 			; <UNDEFINED> instruction: 0xf89131e5
d001afe4:	b9cd5102 	stmiblt	sp, {r1, r8, ip, lr}^
d001afe8:	33e5f503 	mvncc	pc, #12582912	; 0xc00000
d001afec:	33dc4db8 	bicscc	r4, ip, #184, 26	; 0x2e00
d001aff0:	4423447d 	strtmi	r4, [r3], #-1149	; 0xfffffb83
d001aff4:	691968d8 	ldmdbvs	r9, {r3, r4, r6, r7, fp, sp, lr}
d001aff8:	7e1b69da 			; <UNDEFINED> instruction: 0x7e1b69da
d001affc:	e9c466a2 	stmib	r4, {r1, r5, r7, r9, sl, sp, lr}^
d001b000:	e9c45016 	stmib	r4, {r1, r2, r4, ip, lr}^
d001b004:	4db31318 	ldcmi	3, cr1, [r3, #96]!	; 0x60
d001b008:	447d9c68 	ldrbtmi	r9, [sp], #-3176	; 0xfffff398
d001b00c:	cd0f3558 	cfstr32gt	mvfx3, [pc, #-352]	; 0xd001aeb4
d001b010:	682bc40f 	stmdavs	fp!, {r0, r1, r2, r3, sl, lr, pc}
d001b014:	24006023 	strcs	r6, [r0], #-35	; 0xffffffdd
d001b018:	bc04f7fe 	stclt	7, cr15, [r4], {254}	; 0xfe
d001b01c:	30fcf8d1 	ldrsbtcc	pc, [ip], #129	; 0x81	; <UNPREDICTABLE>
d001b020:	5100f44f 	tstpl	r0, pc, asr #8	; <UNPREDICTABLE>
d001b024:	0301f043 	movweq	pc, #4163	; 0x1043	; <UNPREDICTABLE>
d001b028:	e787910f 	str	r9, [r7, pc, lsl #2]
d001b02c:	2b009311 	blcs	0xd003fc78
d001b030:	f8dfd1e9 			; <UNDEFINED> instruction: 0xf8dfd1e9
d001b034:	f64da2a4 			; <UNDEFINED> instruction: 0xf64da2a4
d001b038:	f50452f8 			; <UNDEFINED> instruction: 0xf50452f8
d001b03c:	f8df415e 			; <UNDEFINED> instruction: 0xf8df415e
d001b040:	44fab29c 	ldrbtmi	fp, [sl], #668	; 0x29c
d001b044:	f64d58a0 			; <UNDEFINED> instruction: 0xf64d58a0
d001b048:	44fb52fc 	ldrbtmi	r5, [fp], #764	; 0x2fc
d001b04c:	0a40f10a 	beq	0xd105747c
d001b050:	58a23524 	stmiapl	r2!, {r2, r5, r8, sl, ip, sp}
d001b054:	44501cf4 	ldrbmi	r1, [r0], #-3316	; 0xfffff30c
d001b058:	0b40f10b 	bleq	0xd105748c
d001b05c:	fa0ef001 	blx	0xd03d7068
d001b060:	0403f024 	streq	pc, [r3], #-36	; 0xffffffdc
d001b064:	eb0a9b11 	bl	0xd02c1cb0
d001b068:	eba40009 	bl	0xce91b094
d001b06c:	46190209 	ldrmi	r0, [r9], -r9, lsl #4
d001b070:	f9f6f001 			; <UNDEFINED> instruction: 0xf9f6f001
d001b074:	46999b11 			; <UNDEFINED> instruction: 0x46999b11
d001b078:	a264f8df 	rsbge	pc, r4, #14614528	; 0xdf0000
d001b07c:	f50a44fa 			; <UNDEFINED> instruction: 0xf50a44fa
d001b080:	685b33bc 	ldmdavs	fp, {r2, r3, r4, r5, r7, r8, r9, ip, sp}^
d001b084:	d3414599 	movtle	r4, #5529	; 0x1599
d001b088:	ad322740 	ldcge	7, cr2, [r2, #-256]!	; 0xffffff00
d001b08c:	f50a2100 			; <UNDEFINED> instruction: 0xf50a2100
d001b090:	463a3add 			; <UNDEFINED> instruction: 0x463a3add
d001b094:	f0014628 			; <UNDEFINED> instruction: 0xf0014628
d001b098:	4992f9e3 	ldmibmi	r2, {r0, r1, r5, r6, r7, r8, fp, ip, sp, lr, pc}
d001b09c:	46282208 	strtmi	r2, [r8], -r8, lsl #4
d001b0a0:	443c4479 	ldrtmi	r4, [ip], #-1145	; 0xfffffb87
d001b0a4:	f9eaf001 			; <UNDEFINED> instruction: 0xf9eaf001
d001b0a8:	9a102302 	bls	0xd0423cb8
d001b0ac:	e9cd4631 	stmib	sp, {r0, r4, r5, r9, sl, lr}^
d001b0b0:	f8da3734 			; <UNDEFINED> instruction: 0xf8da3734
d001b0b4:	4f8c30d4 	svcmi	0x008c30d4
d001b0b8:	447f331f 	ldrbtmi	r3, [pc], #-799	; 0xd001b0c0
d001b0bc:	9a0f4413 	bls	0xd03ec110
d001b0c0:	0040f107 	subeq	pc, r0, r7, lsl #2
d001b0c4:	031ff023 	tsteq	pc, #35	; 0x23	; <UNPREDICTABLE>
d001b0c8:	4413923f 	ldrmi	r9, [r3], #-575	; 0xfffffdc1
d001b0cc:	23019338 	movwcs	r9, #4920	; 0x1338
d001b0d0:	4b4c9339 	blmi	0xd133fdbc
d001b0d4:	343ae9cd 	ldrtcc	lr, [sl], #-2509	; 0xfffff633
d001b0d8:	933d2320 	teqls	sp, #32, 6	; 0x80000000
d001b0dc:	bf181e13 	svclt	0x00181e13
d001b0e0:	e9cd2301 	stmib	sp, {r0, r8, r9, sp}^
d001b0e4:	93404636 	movtls	r4, #1590	; 0x636
d001b0e8:	f7f5463e 			; <UNDEFINED> instruction: 0xf7f5463e
d001b0ec:	9041f845 	subls	pc, r1, r5, asr #16
d001b0f0:	c60fcd0f 	strgt	ip, [pc], -pc, lsl #26
d001b0f4:	c60fcd0f 	strgt	ip, [pc], -pc, lsl #26
d001b0f8:	c60fcd0f 	strgt	ip, [pc], -pc, lsl #26
d001b0fc:	000fe895 	muleq	pc, r5, r8	; <UNPREDICTABLE>
d001b100:	000fe886 	andeq	lr, pc, r6, lsl #17
d001b104:	601f9b67 	andsvs	r9, pc, r7, ror #22
d001b108:	bb8cf7fe 	bllt	0xce359108
d001b10c:	b3537aeb 	cmplt	r3, #962560	; 0xeb000
d001b110:	f04f4b76 			; <UNDEFINED> instruction: 0xf04f4b76
d001b114:	447b0a00 	ldrbtmi	r0, [fp], #-2560	; 0xfffff600
d001b118:	89aae014 	stmibhi	sl!, {r2, r4, sp, lr, pc}
d001b11c:	44526868 	ldrbmi	r6, [r2], #-2152	; 0xfffff798
d001b120:	f5024438 			; <UNDEFINED> instruction: 0xf5024438
d001b124:	323642dd 	eorscc	r4, r6, #-805306355	; 0xd000000d
d001b128:	1022f853 	eorne	pc, r2, r3, asr r8	; <UNPREDICTABLE>
d001b12c:	91327a2a 	teqls	r2, sl, lsr #20
d001b130:	d10e2a07 	tstle	lr, r7, lsl #20
d001b134:	447a4a6e 	ldrbtmi	r4, [sl], #-2670	; 0xfffff592
d001b138:	44104452 	ldrmi	r4, [r0], #-1106	; 0xfffffbae
d001b13c:	1040f880 	subne	pc, r0, r0, lsl #17
d001b140:	0a01f10a 	beq	0xd0097570
d001b144:	459289ea 	ldrmi	r8, [r2, #2538]	; 0x9ea
d001b148:	f109d3e7 			; <UNDEFINED> instruction: 0xf109d3e7
d001b14c:	35340901 	ldrcc	r0, [r4, #-2305]!	; 0xfffff6ff
d001b150:	eb00e792 	bl	0xd0054fa0
d001b154:	2204008a 	andcs	r0, r4, #138	; 0x8a
d001b158:	9311a932 	tstls	r1, #819200	; 0xc8000
d001b15c:	f0014458 			; <UNDEFINED> instruction: 0xf0014458
d001b160:	9b11f98d 	blls	0xd049979c
d001b164:	7a2be7ec 	bvc	0xd0b1511c
d001b168:	b2db3b07 	sbcslt	r3, fp, #7168	; 0x1c00
d001b16c:	d8052b0a 	stmdale	r5, {r1, r3, r8, r9, fp, sp}
d001b170:	5203f240 	andpl	pc, r3, #64, 4
d001b174:	f303fa22 	vpmax.u8	d15, d3, d18
d001b178:	d4e607d8 	strbtle	r0, [r6], #2008	; 0x7d8
d001b17c:	22044b5d 	andcs	r4, r4, #95232	; 0x17400
d001b180:	46296868 	strtmi	r6, [r9], -r8, ror #16
d001b184:	4438447b 	ldrtmi	r4, [r8], #-1147	; 0xfffffb85
d001b188:	44183340 	ldrmi	r3, [r8], #-832	; 0xfffffcc0
d001b18c:	f976f001 			; <UNDEFINED> instruction: 0xf976f001
d001b190:	4b59e7db 	blmi	0xd1695104
d001b194:	447b2401 	ldrbtmi	r2, [fp], #-1025	; 0xfffffbff
d001b198:	33e5f503 	mvncc	pc, #12582912	; 0xc00000
d001b19c:	20d8f8d3 	ldrsbcs	pc, [r8], #131	; 0x83	; <UNPREDICTABLE>
d001b1a0:	f8c34432 			; <UNDEFINED> instruction: 0xf8c34432
d001b1a4:	f7fe20d8 			; <UNDEFINED> instruction: 0xf7fe20d8
d001b1a8:	4d54be47 	ldclmi	14, cr11, [r4, #-284]	; 0xfffffee4
d001b1ac:	f505447d 			; <UNDEFINED> instruction: 0xf505447d
d001b1b0:	f8d333ff 			; <UNDEFINED> instruction: 0xf8d333ff
d001b1b4:	f5b770dc 			; <UNDEFINED> instruction: 0xf5b770dc
d001b1b8:	f47f7f80 			; <UNDEFINED> instruction: 0xf47f7f80
d001b1bc:	6dabac8e 	stcvs	12, cr10, [fp, #568]!	; 0x238
d001b1c0:	f47e2b00 			; <UNDEFINED> instruction: 0xf47e2b00
d001b1c4:	4b4eab82 	blmi	0xd13c5fd4
d001b1c8:	e478447b 	ldrbt	r4, [r8], #-1147	; 0xfffffb85
d001b1cc:	23344d4d 	teqcs	r4, #4928	; 0x1340
d001b1d0:	fb03447d 	blx	0xd00ec3ce
d001b1d4:	f5035309 			; <UNDEFINED> instruction: 0xf5035309
d001b1d8:	f89333e5 			; <UNDEFINED> instruction: 0xf89333e5
d001b1dc:	42942100 	addsmi	r2, r4, #0, 2
d001b1e0:	f893d105 			; <UNDEFINED> instruction: 0xf893d105
d001b1e4:	9a133103 	bls	0xd04e75f8
d001b1e8:	f43f429a 			; <UNDEFINED> instruction: 0xf43f429a
d001b1ec:	4b46ace5 	blmi	0xd11c6588
d001b1f0:	6d9a447b 	cfldrsvs	mvf4, [sl, #492]	; 0x1ec
d001b1f4:	f47e2a00 			; <UNDEFINED> instruction: 0xf47e2a00
d001b1f8:	4a44ab68 	bmi	0xd1145fa0
d001b1fc:	f7ff447a 			; <UNDEFINED> instruction: 0xf7ff447a
d001b200:	bf00b807 	svclt	0x0000b807
d001b204:	d0010000 	andle	r0, r1, r0
d001b208:	00004696 	muleq	r0, r6, r6
d001b20c:	ffffecd3 			; <UNDEFINED> instruction: 0xffffecd3
d001b210:	00004646 	andeq	r4, r0, r6, asr #12
d001b214:	ffffedee 			; <UNDEFINED> instruction: 0xffffedee
d001b218:	00004624 	andeq	r4, r0, r4, lsr #12
d001b21c:	000045c8 	andeq	r4, r0, r8, asr #11
d001b220:	ffffed7d 			; <UNDEFINED> instruction: 0xffffed7d
d001b224:	00004586 	andeq	r4, r0, r6, lsl #11
d001b228:	00004564 	andeq	r4, r0, r4, ror #10
d001b22c:	00004562 	andeq	r4, r0, r2, ror #10
d001b230:	0000453e 	andeq	r4, r0, lr, lsr r5
d001b234:	ffffebbe 			; <UNDEFINED> instruction: 0xffffebbe
d001b238:	000044fe 	strdeq	r4, [r0], -lr
d001b23c:	ffffeb20 			; <UNDEFINED> instruction: 0xffffeb20
d001b240:	ffffeb4f 			; <UNDEFINED> instruction: 0xffffeb4f
d001b244:	0000442a 	andeq	r4, r0, sl, lsr #8
d001b248:	ffff845a 			; <UNDEFINED> instruction: 0xffff845a
d001b24c:	ffffd0e4 			; <UNDEFINED> instruction: 0xffffd0e4
d001b250:	ffffd0dd 			; <UNDEFINED> instruction: 0xffffd0dd
d001b254:	ffff8422 			; <UNDEFINED> instruction: 0xffff8422
d001b258:	ffffeaaa 			; <UNDEFINED> instruction: 0xffffeaaa
d001b25c:	ffffeaa6 			; <UNDEFINED> instruction: 0xffffeaa6
d001b260:	000043b0 			; <UNDEFINED> instruction: 0x000043b0
d001b264:	ffffeabd 			; <UNDEFINED> instruction: 0xffffeabd
d001b268:	ffffeac8 			; <UNDEFINED> instruction: 0xffffeac8
d001b26c:	ffffeac8 			; <UNDEFINED> instruction: 0xffffeac8
d001b270:	ffffead2 			; <UNDEFINED> instruction: 0xffffead2
d001b274:	0000434a 	andeq	r4, r0, sl, asr #6
d001b278:	ffffeb04 			; <UNDEFINED> instruction: 0xffffeb04
d001b27c:	0000426c 	andeq	r4, r0, ip, ror #4
d001b280:	ffffeaa6 			; <UNDEFINED> instruction: 0xffffeaa6
d001b284:	ffffea85 			; <UNDEFINED> instruction: 0xffffea85
d001b288:	000041d6 	ldrdeq	r4, [r0], -r6
d001b28c:	00004178 	andeq	r4, r0, r8, ror r1
d001b290:	00004160 	andeq	r4, r0, r0, ror #2
d001b294:	0002bb76 	andeq	fp, r2, r6, ror fp
d001b298:	000040f6 	strdeq	r4, [r0], -r6
d001b29c:	000040d6 	ldrdeq	r4, [r0], -r6
d001b2a0:	ffffe955 			; <UNDEFINED> instruction: 0xffffe955
d001b2a4:	0000407c 	andeq	r4, r0, ip, ror r0
d001b2a8:	00004024 	andeq	r4, r0, r4, lsr #32
d001b2ac:	ffffe5dc 			; <UNDEFINED> instruction: 0xffffe5dc
d001b2b0:	ffffe87b 			; <UNDEFINED> instruction: 0xffffe87b
d001b2b4:	00003fb0 			; <UNDEFINED> instruction: 0x00003fb0
d001b2b8:	00003fa0 	andeq	r3, r0, r0, lsr #31
d001b2bc:	00003f3c 	andeq	r3, r0, ip, lsr pc
d001b2c0:	ffffe82a 			; <UNDEFINED> instruction: 0xffffe82a
d001b2c4:	00003f04 	andeq	r3, r0, r4, lsl #30
d001b2c8:	00003ef6 	strdeq	r3, [r0], -r6
d001b2cc:	00003ef0 	strdeq	r3, [r0], -r0
d001b2d0:	ffffe74c 			; <UNDEFINED> instruction: 0xffffe74c
d001b2d4:	00003dea 	andeq	r3, r0, sl, ror #27
d001b2d8:	0002b802 	andeq	fp, r2, r2, lsl #16
d001b2dc:	0002b7fa 	strdeq	fp, [r2], -sl
d001b2e0:	00003d78 	andeq	r3, r0, r8, ror sp
d001b2e4:	000002cc 	andeq	r0, r0, ip, asr #5
d001b2e8:	0002b78a 	andeq	fp, r2, sl, lsl #15
d001b2ec:	00003cde 	ldrdeq	r3, [r0], -lr
d001b2f0:	0002b70e 	andeq	fp, r2, lr, lsl #14
d001b2f4:	0002b6c0 	andeq	fp, r2, r0, asr #13
d001b2f8:	00003c5e 	andeq	r3, r0, lr, asr ip
d001b2fc:	00003c48 	andeq	r3, r0, r8, asr #24
d001b300:	ffffe44d 			; <UNDEFINED> instruction: 0xffffe44d
d001b304:	00003c24 	andeq	r3, r0, r4, lsr #24
d001b308:	00003c04 	andeq	r3, r0, r4, lsl #24
d001b30c:	ffffe42c 			; <UNDEFINED> instruction: 0xffffe42c

Disassembly of section .text.sidc_compile_project:

d001b310 <.text.sidc_compile_project>:
d001b310:	43f7e92d 	mvnsmi	lr, #737280	; 0xb4000
d001b314:	802cf8dd 	ldrdhi	pc, [ip], -sp	; <UNPREDICTABLE>
d001b318:	9c0c460f 	stcls	6, cr4, [ip], {15}
d001b31c:	46052100 	strmi	r2, [r5], -r0, lsl #2
d001b320:	46204616 			; <UNDEFINED> instruction: 0x46204616
d001b324:	f8c82214 			; <UNDEFINED> instruction: 0xf8c82214
d001b328:	f8dd1000 			; <UNDEFINED> instruction: 0xf8dd1000
d001b32c:	93019028 	movwls	r9, #4136	; 0x1028
d001b330:	f896f001 			; <UNDEFINED> instruction: 0xf896f001
d001b334:	1e72b185 	expned	f3, f5
d001b338:	2a0f9b01 	bcs	0xd0401f44
d001b33c:	4632d80c 	ldrtmi	sp, [r2], -ip, lsl #16
d001b340:	46284639 			; <UNDEFINED> instruction: 0x46284639
d001b344:	f8cd940c 			; <UNDEFINED> instruction: 0xf8cd940c
d001b348:	f8cd802c 			; <UNDEFINED> instruction: 0xf8cd802c
d001b34c:	b0039028 	andlt	r9, r3, r8, lsr #32
d001b350:	43f0e8bd 	mvnsmi	lr, #12386304	; 0xbd0000
d001b354:	ba06f7fe 	blt	0xd01d9354
d001b358:	447d4d04 	ldrbtmi	r4, [sp], #-3332	; 0xfffff2fc
d001b35c:	c40fcd0f 	strgt	ip, [pc], #-3343	; 0xd001b364
d001b360:	2000682b 	andcs	r6, r0, fp, lsr #16
d001b364:	b0036023 	andlt	r6, r3, r3, lsr #32
d001b368:	83f0e8bd 	mvnshi	lr, #12386304	; 0xbd0000
d001b36c:	000029b6 			; <UNDEFINED> instruction: 0x000029b6

Disassembly of section .text.read_file:

d001b440 <.text.read_file>:
d001b440:	41ffe92d 	mvnsmi	lr, sp, lsr #18
d001b444:	4b1a461e 	blmi	0xd06accc4
d001b448:	4690460f 	ldrmi	r4, [r0], pc, lsl #12
d001b44c:	aa01685b 	bge	0xd00755c0
d001b450:	681d2101 	ldmdavs	sp, {r0, r8, sp}
d001b454:	47986bab 	ldrmi	r6, [r8, fp, lsr #23]
d001b458:	4604b120 	strmi	fp, [r4], -r0, lsr #2
d001b45c:	b0044620 	andlt	r4, r4, r0, lsr #12
d001b460:	81f0e8bd 	ldrhhi	lr, [r0, #141]!	; 0x8d
d001b464:	0002e9cd 	andeq	lr, r2, sp, asr #19
d001b468:	a9026ceb 	stmdbge	r2, {r0, r1, r3, r5, r6, r7, sl, fp, sp, lr}
d001b46c:	47989801 	ldrmi	r9, [r8, r1, lsl #16]
d001b470:	b9784604 	ldmdblt	r8!, {r2, r9, sl, lr}^
d001b474:	45429a02 	strbmi	r9, [r2, #-2562]	; 0xfffff5fe
d001b478:	b15ad817 	cmplt	sl, r7, lsl r8
d001b47c:	ab036bec 	blge	0xd00f6434
d001b480:	98014639 	stmdals	r1, {r0, r3, r4, r5, r9, sl, lr}
d001b484:	460447a0 	strmi	r4, [r4], -r0, lsr #15
d001b488:	e9ddb920 	ldmib	sp, {r5, r8, fp, ip, sp, pc}^
d001b48c:	1a240402 	bne	0xd091c49c
d001b490:	2401bf18 	strcs	fp, [r1], #-3864	; 0xfffff0e8
d001b494:	98016d6b 	stmdals	r1, {r0, r1, r3, r5, r6, r8, sl, fp, sp, lr}
d001b498:	2c004798 	stccs	7, cr4, [r0], {152}	; 0x98
d001b49c:	4604d1de 			; <UNDEFINED> instruction: 0x4604d1de
d001b4a0:	d1db2800 	bicsle	r2, fp, r0, lsl #16
d001b4a4:	60339b02 	eorsvs	r9, r3, r2, lsl #22
d001b4a8:	f06fe7d8 			; <UNDEFINED> instruction: 0xf06fe7d8
d001b4ac:	e7f10402 	ldrb	r0, [r1, r2, lsl #8]!
d001b4b0:	2001f000 	andcs	pc, r1, r0

Disassembly of section .text.read_apicore:

d001b4d4 <.text.read_apicore>:
d001b4d4:	460ab507 	strmi	fp, [sl], -r7, lsl #10
d001b4d8:	48064601 	stmdami	r6, {r0, r9, sl, lr}
d001b4dc:	4478ab01 	ldrbtmi	sl, [r8], #-2817	; 0xfffff4ff
d001b4e0:	ffaef7ff 			; <UNDEFINED> instruction: 0xffaef7ff
d001b4e4:	9801b918 	stmdals	r1, {r3, r4, r8, fp, ip, sp, pc}
d001b4e8:	f85db003 			; <UNDEFINED> instruction: 0xf85db003
d001b4ec:	2000fb04 	andcs	pc, r0, r4, lsl #22
d001b4f0:	bf00e7fa 	svclt	0x0000e7fa
d001b4f4:	ffffffd2 			; <UNDEFINED> instruction: 0xffffffd2

Disassembly of section .text.write_file:

d001b50c <.text.write_file>:
d001b50c:	47ffe92d 	ldrbmi	lr, [pc, sp, lsr #18]!
d001b510:	46074b4a 	strmi	r4, [r7], -sl, asr #22
d001b514:	46154688 	ldrmi	r4, [r5], -r8, lsl #13
d001b518:	681e685b 	ldmdavs	lr, {r0, r1, r3, r4, r6, fp, sp, lr}
d001b51c:	fbb6f002 	blx	0xcedd752e
d001b520:	03f7f1a0 	mvnseq	pc, #160, 2	; 0x28
d001b524:	f5134604 			; <UNDEFINED> instruction: 0xf5134604
d001b528:	f2407f81 	vmax.f32	d23, d16, d1
d001b52c:	f8df8084 			; <UNDEFINED> instruction: 0xf8df8084
d001b530:	46029110 			; <UNDEFINED> instruction: 0x46029110
d001b534:	f8df4639 			; <UNDEFINED> instruction: 0xf8df4639
d001b538:	44f9a10c 	ldrbtmi	sl, [r9], #268	; 0x10c
d001b53c:	464844fa 			; <UNDEFINED> instruction: 0x464844fa
d001b540:	ff9cf000 			; <UNDEFINED> instruction: 0xff9cf000
d001b544:	220a4940 	andcs	r4, sl, #64, 18	; 0x100000
d001b548:	0004eb09 	andeq	lr, r4, r9, lsl #22
d001b54c:	f0004479 			; <UNDEFINED> instruction: 0xf0004479
d001b550:	4622ff95 	qadd8mi	pc, r2, r5	; <UNPREDICTABLE>
d001b554:	46504639 			; <UNDEFINED> instruction: 0x46504639
d001b558:	ff90f000 			; <UNDEFINED> instruction: 0xff90f000
d001b55c:	220a493b 	andcs	r4, sl, #966656	; 0xec000
d001b560:	0004eb0a 	andeq	lr, r4, sl, lsl #22
d001b564:	f0004479 			; <UNDEFINED> instruction: 0xf0004479
d001b568:	6bb3ff89 	blvs	0xced1b394
d001b56c:	2106aa01 	tstcs	r6, r1, lsl #20
d001b570:	47984648 	ldrmi	r4, [r8, r8, asr #12]
d001b574:	4604b120 	strmi	fp, [r4], -r0, lsr #2
d001b578:	b0044620 	andlt	r4, r4, r0, lsr #12
d001b57c:	87f0e8bd 			; <UNDEFINED> instruction: 0x87f0e8bd
d001b580:	b9759002 	ldmdblt	r5!, {r1, ip, pc}^
d001b584:	98016d33 	stmdals	r1, {r0, r1, r4, r5, r8, sl, fp, sp, lr}
d001b588:	46044798 			; <UNDEFINED> instruction: 0x46044798
d001b58c:	98016d73 	stmdals	r1, {r0, r1, r4, r5, r6, r8, sl, fp, sp, lr}
d001b590:	b90c4798 	stmdblt	ip, {r3, r4, r7, r8, r9, sl, lr}
d001b594:	4604b198 			; <UNDEFINED> instruction: 0x4604b198
d001b598:	6db3482d 	ldcvs	8, cr4, [r3, #180]!	; 0xb4
d001b59c:	47984478 			; <UNDEFINED> instruction: 0x47984478
d001b5a0:	6c34e7ea 	ldcvs	7, cr14, [r4], #-936	; 0xfffffc58
d001b5a4:	462aab02 	strtmi	sl, [sl], -r2, lsl #22
d001b5a8:	98014641 	stmdals	r1, {r0, r6, r9, sl, lr}
d001b5ac:	460447a0 	strmi	r4, [r4], -r0, lsr #15
d001b5b0:	d1eb2800 	mvnle	r2, r0, lsl #16
d001b5b4:	42ab9b02 	adcmi	r9, fp, #2048	; 0x800
d001b5b8:	2401d0e4 	strcs	sp, [r1], #-228	; 0xffffff1c
d001b5bc:	6ab3e7e6 	bvs	0xced1555c
d001b5c0:	a9034622 	stmdbge	r3, {r1, r5, r9, sl, lr}
d001b5c4:	94034638 	strls	r4, [r3], #-1592	; 0xfffff9c8
d001b5c8:	46054798 			; <UNDEFINED> instruction: 0x46054798
d001b5cc:	9b03b980 	blls	0xd0109bd4
d001b5d0:	d42407db 	strtle	r0, [r4], #-2011	; 0xfffff825
d001b5d4:	4638491f 			; <UNDEFINED> instruction: 0x4638491f
d001b5d8:	44796df3 	ldrbtmi	r6, [r9], #-3571	; 0xfffff20d
d001b5dc:	46054798 			; <UNDEFINED> instruction: 0x46054798
d001b5e0:	481db1d8 	ldmdami	sp, {r3, r4, r6, r7, r8, ip, sp, pc}
d001b5e4:	44786db3 	ldrbtmi	r6, [r8], #-3507	; 0xfffff24d
d001b5e8:	b9d44798 	ldmiblt	r4, {r3, r4, r7, r8, r9, sl, lr}^
d001b5ec:	e7c3462c 	strb	r4, [r3, ip, lsr #12]
d001b5f0:	d1f62804 	mvnsle	r2, r4, lsl #16
d001b5f4:	46394819 			; <UNDEFINED> instruction: 0x46394819
d001b5f8:	44786df3 	ldrbtmi	r6, [r8], #-3571	; 0xfffff20d
d001b5fc:	46054798 			; <UNDEFINED> instruction: 0x46054798
d001b600:	d1ee2800 	mvnle	r2, r0, lsl #16
d001b604:	d0b72c00 	adcsle	r2, r7, r0, lsl #24
d001b608:	6db34815 	ldcvs	8, cr4, [r3, #84]!	; 0x54
d001b60c:	47984478 			; <UNDEFINED> instruction: 0x47984478
d001b610:	bf183800 	svclt	0x00183800
d001b614:	42442001 	submi	r2, r4, #1
d001b618:	2401e7ae 	strcs	lr, [r1], #-1966	; 0xfffff852
d001b61c:	2507e7ea 	strcs	lr, [r7, #-2026]	; 0xfffff816
d001b620:	4810e7df 	ldmdami	r0, {r0, r1, r2, r3, r4, r6, r7, r8, r9, sl, sp, lr, pc}
d001b624:	6df34639 	ldclvs	6, cr4, [r3, #228]!	; 0xe4
d001b628:	47984478 			; <UNDEFINED> instruction: 0x47984478
d001b62c:	d0dd2800 	sbcsle	r2, sp, r0, lsl #16
d001b630:	0401f06f 	streq	pc, [r1], #-111	; 0xffffff91
d001b634:	2407e7a0 	strcs	lr, [r7], #-1952	; 0xfffff860
d001b638:	bf00e79e 	svclt	0x0000e79e
d001b63c:	2001f000 	andcs	pc, r1, r0
d001b640:	0005c6ea 	andeq	ip, r5, sl, ror #13
d001b644:	0003b448 	andeq	fp, r3, r8, asr #8
d001b648:	ffffffa8 			; <UNDEFINED> instruction: 0xffffffa8
d001b64c:	ffffff9a 			; <UNDEFINED> instruction: 0xffffff9a
d001b650:	0005c688 	andeq	ip, r5, r8, lsl #13
d001b654:	0003b3aa 	andeq	fp, r3, sl, lsr #7
d001b658:	0005c63e 	andeq	ip, r5, lr, lsr r6
d001b65c:	0005c62a 	andeq	ip, r5, sl, lsr #12
d001b660:	0003b378 	andeq	fp, r3, r8, ror r3
d001b664:	0003b35c 	andeq	fp, r3, ip, asr r3

Disassembly of section .text.show_status:

d001b66c <.text.show_status>:
d001b66c:	46024b09 	strmi	r4, [r2], -r9, lsl #22
d001b670:	6818447b 	ldmdavs	r8, {r0, r1, r3, r4, r5, r6, sl, lr}
d001b674:	689b4b06 	ldmvs	fp, {r1, r2, r8, r9, fp, lr}
d001b678:	68dbb120 	ldmvs	fp, {r5, r8, ip, sp, pc}^
d001b67c:	f8d34611 			; <UNDEFINED> instruction: 0xf8d34611
d001b680:	471830c4 	ldrmi	r3, [r8, -r4, asr #1]
d001b684:	4904681b 	stmdbmi	r4, {r0, r1, r3, r4, fp, sp, lr}
d001b688:	4479681b 	ldrbtmi	r6, [r9], #-2075	; 0xfffff7e5
d001b68c:	bf004718 	svclt	0x00004718
d001b690:	2001f000 	andcs	pc, r1, r0
d001b694:	0005c834 	andeq	ip, r5, r4, lsr r8
d001b698:	ffffffda 			; <UNDEFINED> instruction: 0xffffffda

Disassembly of section .text.open_editor:

d001b714 <.text.open_editor>:
d001b714:	47ffe92d 	ldrbmi	lr, [pc, sp, lsr #18]!
d001b718:	f2404c5d 	vfma.f32	q10, q0, <illegal reg q6.5>
d001b71c:	4607324d 	strmi	r3, [r7], -sp, asr #4
d001b720:	68a3210c 	stmiavs	r3!, {r2, r3, r8, sp}
d001b724:	685b2000 	ldmdavs	fp, {sp}^
d001b728:	4a5a9202 	bmi	0xd16bff38
d001b72c:	9201447a 	andls	r4, r1, #2046820352	; 0x7a000000
d001b730:	728ef44f 	addvc	pc, lr, #1325400064	; 0x4f000000
d001b734:	22119200 	andscs	r9, r1, #0, 4
d001b738:	f44f681d 	vst2.8	{d22-d23}, [pc :64]!
d001b73c:	47a873e4 	strmi	r7, [r8, r4, ror #7]!
d001b740:	46051e43 	strmi	r1, [r5], -r3, asr #28
d001b744:	2bfdb2db 	blcs	0xcff882b8
d001b748:	4853d907 	ldmdami	r3, {r0, r1, r2, r8, fp, ip, lr, pc}^
d001b74c:	f7ff4478 			; <UNDEFINED> instruction: 0xf7ff4478
d001b750:	2001ff8d 	andcs	pc, r1, sp, lsl #31
d001b754:	e8bdb004 	pop	{r2, ip, sp, pc}
d001b758:	4e5087f0 	mrcmi	7, 2, r8, cr0, cr0, {7}
d001b75c:	447e212f 	ldrbtmi	r2, [lr], #-303	; 0xfffffed1
d001b760:	f0024630 			; <UNDEFINED> instruction: 0xf0024630
d001b764:	68a2fac3 	stmiavs	r2!, {r0, r1, r6, r7, r9, fp, ip, sp, lr, pc}
d001b768:	68d24603 	ldmvs	r2, {r0, r1, r9, sl, lr}^
d001b76c:	8018f8d2 			; <UNDEFINED> instruction: 0x8018f8d2
d001b770:	d07a2800 	rsbsle	r2, sl, r0, lsl #16
d001b774:	26013301 	strcs	r3, [r1], -r1, lsl #6
d001b778:	23109301 	tstcs	r0, #67108864	; 0x4000000
d001b77c:	21082209 	tstcs	r8, r9, lsl #4
d001b780:	93004628 	movwls	r4, #1576	; 0x628
d001b784:	7387f44f 	orrvc	pc, r7, #1325400064	; 0x4f000000
d001b788:	f04f9602 			; <UNDEFINED> instruction: 0xf04f9602
d001b78c:	47c00918 	bfimi	r0, r8, (invalid: 18:0)
d001b790:	4a4368a3 	bmi	0xd10f5a24
d001b794:	718ff44f 	orrvc	pc, pc, pc, asr #8
d001b798:	468068db 	pkhtbmi	r6, r0, fp, asr #17
d001b79c:	f8cd447a 			; <UNDEFINED> instruction: 0xf8cd447a
d001b7a0:	96029000 	strls	r9, [r2], -r0
d001b7a4:	92014628 	andls	r4, r1, #40, 12	; 0x2800000
d001b7a8:	f8d32204 			; <UNDEFINED> instruction: 0xf8d32204
d001b7ac:	2344a008 	movtcs	sl, #16392	; 0x4008
d001b7b0:	4b3c47d0 	blmi	0xd0f2d6f8
d001b7b4:	f44f4a3c 	vst1.8	{d20-d21}, [pc :256], ip
d001b7b8:	447b71b4 	ldrbtmi	r7, [fp], #-436	; 0xfffffe4c
d001b7bc:	6018447a 	andsvs	r4, r8, sl, ror r4
d001b7c0:	68a34628 	stmiavs	r3!, {r3, r5, r9, sl, lr}
d001b7c4:	920168db 	andls	r6, r1, #14352384	; 0xdb0000
d001b7c8:	96022204 	strls	r2, [r2], -r4, lsl #4
d001b7cc:	9000f8cd 	andls	pc, r0, sp, asr #17
d001b7d0:	9008f8d3 	ldrdls	pc, [r8], -r3
d001b7d4:	47c8234e 	strbmi	r2, [r8, lr, asr #6]
d001b7d8:	22004b34 	andcs	r4, r0, #52, 22	; 0xd000
d001b7dc:	447b2108 	ldrbtmi	r2, [fp], #-264	; 0xfffffef8
d001b7e0:	46286018 			; <UNDEFINED> instruction: 0x46286018
d001b7e4:	68db68a3 	ldmvs	fp, {r0, r1, r5, r7, fp, sp, lr}^
d001b7e8:	4a319202 	bmi	0xd0c7fff8
d001b7ec:	447a9603 	ldrbtmi	r9, [sl], #-1539	; 0xfffff9fd
d001b7f0:	22c19201 	sbccs	r9, r1, #268435456	; 0x10000000
d001b7f4:	22229200 	eorcs	r9, r2, #0, 4
d001b7f8:	9034f8d3 	ldrsbtls	pc, [r4], -r3	; <UNPREDICTABLE>
d001b7fc:	73d7f44f 	bicsvc	pc, r7, #1325400064	; 0x4f000000
d001b800:	4b2c47c8 	blmi	0xd0b2d728
d001b804:	6018447b 	andsvs	r4, r8, fp, ror r4
d001b808:	68db68a3 	ldmvs	fp, {r0, r1, r5, r7, fp, sp, lr}^
d001b80c:	9018f8d3 			; <UNDEFINED> instruction: 0x9018f8d3
d001b810:	d12c2f00 			; <UNDEFINED> instruction: 0xd12c2f00
d001b814:	447b4b28 	ldrbtmi	r4, [fp], #-2856	; 0xfffff4d8
d001b818:	23129301 	tstcs	r2, #67108864	; 0x4000000
d001b81c:	210822eb 	smlattcs	r8, fp, r2, r2
d001b820:	46289300 	strtmi	r9, [r8], -r0, lsl #6
d001b824:	73d7f44f 	bicsvc	pc, r7, #1325400064	; 0x4f000000
d001b828:	47c89602 	strbmi	r9, [r8, r2, lsl #12]
d001b82c:	447b4b23 	ldrbtmi	r4, [fp], #-2851	; 0xfffff4dd
d001b830:	f1b86018 			; <UNDEFINED> instruction: 0xf1b86018
d001b834:	d00c0f00 	andle	r0, ip, r0, lsl #30
d001b838:	447b4b21 	ldrbtmi	r4, [fp], #-2849	; 0xfffff4df
d001b83c:	b143681b 	cmplt	r3, fp, lsl r8
d001b840:	447b4b20 	ldrbtmi	r4, [fp], #-2848	; 0xfffff4e0
d001b844:	b123681b 			; <UNDEFINED> instruction: 0xb123681b
d001b848:	447e4e1f 	ldrbtmi	r4, [lr], #-3615	; 0xfffff1e1
d001b84c:	b1036833 	tstlt	r3, r3, lsr r8
d001b850:	68a3b980 	stmiavs	r3!, {r7, r8, fp, ip, sp, pc}
d001b854:	685b4628 	ldmdavs	fp, {r3, r5, r9, sl, lr}^
d001b858:	4798685b 			; <UNDEFINED> instruction: 0x4798685b
d001b85c:	22004b1b 	andcs	r4, r0, #27648	; 0x6c00
d001b860:	447b481b 	ldrbtmi	r4, [fp], #-2075	; 0xfffff7e5
d001b864:	601a4478 	andsvs	r4, sl, r8, ror r4
d001b868:	4633e771 			; <UNDEFINED> instruction: 0x4633e771
d001b86c:	4b19e783 	blmi	0xd0695680
d001b870:	e7d1447b 			; <UNDEFINED> instruction: 0xe7d1447b
d001b874:	462868a3 	strtmi	r6, [r8], -r3, lsr #17
d001b878:	685b4917 	ldmdavs	fp, {r0, r1, r2, r4, r8, fp, lr}^
d001b87c:	689b4479 	ldmvs	fp, {r0, r3, r4, r5, r6, sl, lr}
d001b880:	68a34798 	stmiavs	r3!, {r3, r4, r7, r8, r9, sl, lr}
d001b884:	68db6830 	ldmvs	fp, {r4, r5, fp, sp, lr}^
d001b888:	47986ddb 			; <UNDEFINED> instruction: 0x47986ddb
d001b88c:	e7612000 	strb	r2, [r1, -r0]!
d001b890:	2001f000 	andcs	pc, r1, r0
d001b894:	ffffff8a 			; <UNDEFINED> instruction: 0xffffff8a
d001b898:	ffffff73 			; <UNDEFINED> instruction: 0xffffff73
d001b89c:	0005c3c6 	andeq	ip, r5, r6, asr #7
d001b8a0:	ffffff3f 			; <UNDEFINED> instruction: 0xffffff3f
d001b8a4:	0003c356 	andeq	ip, r3, r6, asr r3
d001b8a8:	ffffff24 			; <UNDEFINED> instruction: 0xffffff24
d001b8ac:	0003b2a6 	andeq	fp, r3, r6, lsr #5
d001b8b0:	0003c326 	andeq	ip, r3, r6, lsr #6
d001b8b4:	0003b284 	andeq	fp, r3, r4, lsl #5
d001b8b8:	fffffe92 			; <UNDEFINED> instruction: 0xfffffe92
d001b8bc:	0005c676 	andeq	ip, r5, r6, ror r6
d001b8c0:	0003c2d6 	ldrdeq	ip, [r3], -r6
d001b8c4:	0003b242 	andeq	fp, r3, r2, asr #4
d001b8c8:	0003b23e 	andeq	fp, r3, lr, lsr r2
d001b8cc:	0005c642 	andeq	ip, r5, r2, asr #12
d001b8d0:	fffffe82 			; <UNDEFINED> instruction: 0xfffffe82
d001b8d4:	fffffe28 			; <UNDEFINED> instruction: 0xfffffe28
d001b8d8:	00000521 	andeq	r0, r0, r1, lsr #10

Disassembly of section .text.report_file.part.0:

d001b984 <.text.report_file.part.0>:
d001b984:	1cc5b537 	cfstr64ne	mvdx11, [r5], {55}	; 0x37
d001b988:	460b4604 	strmi	r4, [fp], -r4, lsl #12
d001b98c:	4812d108 	ldmdami	r2, {r3, r8, ip, lr, pc}
d001b990:	f7ff4478 			; <UNDEFINED> instruction: 0xf7ff4478
d001b994:	1c63fe6b 	stclne	14, cr15, [r3], #-428	; 0xfffffe54
d001b998:	41584258 	cmpmi	r8, r8, asr r2
d001b99c:	bd30b003 	ldclt	0, cr11, [r0, #-12]!
d001b9a0:	d1021d20 	tstle	r2, r0, lsr #26
d001b9a4:	4478480d 	ldrbtmi	r4, [r8], #-2061	; 0xfffff7f3
d001b9a8:	1ca1e7f3 	stcne	7, cr14, [r1], #972	; 0x3cc
d001b9ac:	480cd102 	stmdami	ip, {r1, r8, ip, lr, pc}
d001b9b0:	e7ee4478 			; <UNDEFINED> instruction: 0xe7ee4478
d001b9b4:	d1021c62 	tstle	r2, r2, ror #24
d001b9b8:	4478480a 	ldrbtmi	r4, [r8], #-2058	; 0xfffff7f6
d001b9bc:	4d0ae7e9 	stcmi	7, cr14, [sl, #-932]	; 0xfffffc5c
d001b9c0:	71c0f44f 	bicvc	pc, r0, pc, asr #8
d001b9c4:	447d4a09 	ldrbtmi	r4, [sp], #-2569	; 0xfffff5f7
d001b9c8:	447a9400 	ldrbtmi	r9, [sl], #-1024	; 0xfffffc00
d001b9cc:	f0024628 			; <UNDEFINED> instruction: 0xf0024628
d001b9d0:	4628f925 	strtmi	pc, [r8], -r5, lsr #18
d001b9d4:	bf00e7dd 	svclt	0x0000e7dd
d001b9d8:	ffffff48 			; <UNDEFINED> instruction: 0xffffff48
d001b9dc:	ffffff49 			; <UNDEFINED> instruction: 0xffffff49
d001b9e0:	ffffff5a 			; <UNDEFINED> instruction: 0xffffff5a
d001b9e4:	ffffff7c 			; <UNDEFINED> instruction: 0xffffff7c
d001b9e8:	0005c35e 	andeq	ip, r5, lr, asr r3
d001b9ec:	ffffff9b 			; <UNDEFINED> instruction: 0xffffff9b

Disassembly of section .text.read_header:

d001b9f0 <.text.read_header>:
d001b9f0:	47f0e92d 	ldrbmi	lr, [r0, sp, lsr #18]!
d001b9f4:	460d9f09 	strmi	r9, [sp], -r9, lsl #30
d001b9f8:	46984616 			; <UNDEFINED> instruction: 0x46984616
d001b9fc:	b9104681 	ldmdblt	r0, {r0, r7, r9, sl, lr}
d001ba00:	e8bd2000 	ldmfd	sp!, {sp}
d001ba04:	290087f0 	stmdbcs	r0, {r4, r5, r6, r7, r8, r9, sl, pc}
d001ba08:	780bd0fa 	stmdavc	fp, {r1, r3, r4, r5, r6, r7, ip, lr, pc}
d001ba0c:	d0f72b00 	rscsle	r2, r7, r0, lsl #22
d001ba10:	d0f52b2f 	rscsle	r2, r5, pc, lsr #22
d001ba14:	4628213a 			; <UNDEFINED> instruction: 0x4628213a
d001ba18:	f95cf002 			; <UNDEFINED> instruction: 0xf95cf002
d001ba1c:	d1ef2800 	mvnle	r2, r0, lsl #16
d001ba20:	4648212f 	strbmi	r2, [r8], -pc, lsr #2
d001ba24:	f962f002 			; <UNDEFINED> instruction: 0xf962f002
d001ba28:	d0e92800 	rscle	r2, r9, r0, lsl #16
d001ba2c:	0409eba0 	streq	lr, [r9], #-2976	; 0xfffff460
d001ba30:	f0024628 			; <UNDEFINED> instruction: 0xf0024628
d001ba34:	9a0af92b 	bls	0xd02d9ee8
d001ba38:	46823401 	strmi	r3, [r2], r1, lsl #8
d001ba3c:	429a1823 	addsmi	r1, sl, #2293760	; 0x230000
d001ba40:	4622d9de 			; <UNDEFINED> instruction: 0x4622d9de
d001ba44:	46384649 	ldrtmi	r4, [r8], -r9, asr #12
d001ba48:	fd18f000 	ldc2	0, cr15, [r8, #-0]
d001ba4c:	0201f10a 	andeq	pc, r1, #-2147483646	; 0x80000002
d001ba50:	19384629 	ldmdbne	r8!, {r0, r3, r5, r9, sl, lr}
d001ba54:	fd12f000 	ldc2	0, cr15, [r2, #-0]
d001ba58:	9b08b14e 	blls	0xd0247f98
d001ba5c:	46314642 	ldrtmi	r4, [r1], -r2, asr #12
d001ba60:	f7ff4638 			; <UNDEFINED> instruction: 0xf7ff4638
d001ba64:	fab0fced 	blx	0xcec5ae20
d001ba68:	0940f080 	stmdbeq	r0, {r7, ip, sp, lr, pc}^
d001ba6c:	2001e7c9 	andcs	lr, r1, r9, asr #15
d001ba70:	Address 0x00000000d001ba70 is out of bounds.


Disassembly of section .text.resolve_path.constprop.0:

d001ba80 <.text.resolve_path.constprop.0>:
d001ba80:	460fb5f7 			; <UNDEFINED> instruction: 0x460fb5f7
d001ba84:	46044616 			; <UNDEFINED> instruction: 0x46044616
d001ba88:	2000b910 	andcs	fp, r0, r0, lsl r9
d001ba8c:	bdf0b003 	ldcllt	0, cr11, [r0, #12]!
d001ba90:	2b007803 	blcs	0xd0039aa4
d001ba94:	f002d0f9 			; <UNDEFINED> instruction: 0xf002d0f9
d001ba98:	4605f8f9 			; <UNDEFINED> instruction: 0x4605f8f9
d001ba9c:	f0024638 			; <UNDEFINED> instruction: 0xf0024638
d001baa0:	4285f8f5 	addmi	pc, r5, #16056320	; 0xf50000
d001baa4:	1a2bd9f1 	bne	0xd0b12270
d001baa8:	44253f01 	strtmi	r3, [r5], #-3841	; 0xfffff0ff
d001baac:	42ab4423 	adcmi	r4, fp, #587202560	; 0x23000000
d001bab0:	213ad118 	teqcs	sl, r8, lsl r1
d001bab4:	f0024620 			; <UNDEFINED> instruction: 0xf0024620
d001bab8:	7823f90d 	stmdavc	r3!, {r0, r2, r3, r8, fp, ip, sp, lr, pc}
d001babc:	d0032b2f 	andle	r2, r3, pc, lsr #22
d001bac0:	7843b1d8 	stmdavc	r3, {r3, r4, r6, r7, r8, ip, sp, pc}^
d001bac4:	d1e02b2f 	mvnle	r2, pc, lsr #22
d001bac8:	46234a21 	strtmi	r4, [r3], -r1, lsr #20
d001bacc:	7180f44f 	orrvc	pc, r0, pc, asr #8
d001bad0:	447a4630 	ldrbtmi	r4, [sl], #-1584	; 0xfffff9d0
d001bad4:	f8a2f002 			; <UNDEFINED> instruction: 0xf8a2f002
d001bad8:	28fe3801 	ldmcs	lr!, {r0, fp, ip, sp}^
d001badc:	2000bf8c 	andcs	fp, r0, ip, lsl #31
d001bae0:	e7d32001 	ldrb	r2, [r3, r1]
d001bae4:	1b01f813 	blne	0xd0099b38
d001bae8:	2f01f817 	svccs	0x0001f817
d001baec:	0120f041 	msreq	CPSR_, r1, asr #32
d001baf0:	0220f042 	eoreq	pc, r0, #66	; 0x42
d001baf4:	d0da4291 	smullsle	r4, sl, r1, r2
d001baf8:	4b14e7c7 	blmi	0xd0555a1c
d001bafc:	7180f44f 	orrvc	pc, r0, pc, asr #8
d001bb00:	685b4d14 	ldmdavs	fp, {r2, r4, r8, sl, fp, lr}^
d001bb04:	681b447d 	ldmdavs	fp, {r0, r2, r3, r4, r5, r6, sl, lr}
d001bb08:	69db4628 	ldmibvs	fp, {r3, r5, r9, sl, lr}^
d001bb0c:	28004798 	stmdacs	r0, {r3, r4, r7, r8, r9, sl, lr}
d001bb10:	782bd1bb 	stmdavc	fp!, {r0, r1, r3, r4, r5, r7, r8, ip, lr, pc}
d001bb14:	d0b82b00 	adcsle	r2, r8, r0, lsl #22
d001bb18:	f0024628 			; <UNDEFINED> instruction: 0xf0024628
d001bb1c:	4428f8b7 	strtmi	pc, [r8], #-2231	; 0xfffff749
d001bb20:	3c01f810 	stccc	8, cr15, [r1], {16}
d001bb24:	d00d2b2f 	andle	r2, sp, pc, lsr #22
d001bb28:	447b4b0b 	ldrbtmi	r4, [fp], #-2827	; 0xfffff4f5
d001bb2c:	f44f4a0b 	vst1.8	{d20-d21}, [pc], fp
d001bb30:	46307180 	ldrtmi	r7, [r0], -r0, lsl #3
d001bb34:	e9cd447a 	stmib	sp, {r1, r3, r4, r5, r6, sl, lr}^
d001bb38:	4b093400 	blmi	0xd0268b40
d001bb3c:	f002447b 			; <UNDEFINED> instruction: 0xf002447b
d001bb40:	e7c9f86d 	strb	pc, [r9, sp, ror #16]	; <UNPREDICTABLE>
d001bb44:	447b4b07 	ldrbtmi	r4, [fp], #-2823	; 0xfffff4f9
d001bb48:	bf00e7f0 	svclt	0x0000e7f0
d001bb4c:	2001f000 	andcs	pc, r1, r0
d001bb50:	ffffff9f 			; <UNDEFINED> instruction: 0xffffff9f
d001bb54:	0005c120 	andeq	ip, r5, r0, lsr #2
d001bb58:	ffffff45 			; <UNDEFINED> instruction: 0xffffff45
d001bb5c:	ffffff40 			; <UNDEFINED> instruction: 0xffffff40
d001bb60:	0005c0e8 	andeq	ip, r5, r8, ror #1
d001bb64:	ffffff28 			; <UNDEFINED> instruction: 0xffffff28

Disassembly of section .text.build:

d001bbbc <.text.build>:
d001bbbc:	22004b5b 	andcs	r4, r0, #93184	; 0x16c00
d001bbc0:	447bb570 	ldrbtmi	fp, [fp], #-1392	; 0xfffffa90
d001bbc4:	9307b09e 	movwls	fp, #28830	; 0x709e
d001bbc8:	4b59a90e 	blmi	0xd1686008
d001bbcc:	447b9008 	ldrbtmi	r9, [fp], #-8
d001bbd0:	681b4858 	ldmdavs	fp, {r3, r4, r6, fp, lr}
d001bbd4:	42934478 	addsmi	r4, r3, #120, 8	; 0x78000000
d001bbd8:	4b57d159 	blmi	0xd1610144
d001bbdc:	9306447b 	movwls	r4, #25723	; 0x647b
d001bbe0:	d15a2a00 	cmple	sl, r0, lsl #20
d001bbe4:	a906a807 	stmdbge	r6, {r0, r1, r2, fp, sp, pc}
d001bbe8:	2a01ab09 	bcs	0xd0086814
d001bbec:	ab059302 	blge	0xd01807fc
d001bbf0:	2201bf38 	andcs	fp, r1, #56, 30	; 0xe0
d001bbf4:	4b519301 	blmi	0xd1480800
d001bbf8:	9300447b 	movwls	r4, #1147	; 0x47b
d001bbfc:	447b4b50 	ldrbtmi	r4, [fp], #-2896	; 0xfffff4b0
d001bc00:	fb86f7ff 	blx	0xce1d9c06
d001bc04:	28004604 	stmdacs	r0, {r2, r9, sl, lr}
d001bc08:	9c0dd14e 	stflsd	f5, [sp], {78}	; 0x4e
d001bc0c:	4a4db94c 	bmi	0xd138a144
d001bc10:	447a9b0c 	ldrbtmi	r9, [sl], #-2828	; 0xfffff4f4
d001bc14:	42936812 	addsmi	r6, r3, #1179648	; 0x120000
d001bc18:	4c4bd243 	sfmmi	f5, 3, [fp], {67}	; 0x43
d001bc1c:	eb04447c 	bl	0xd012ce14
d001bc20:	212f2403 			; <UNDEFINED> instruction: 0x212f2403
d001bc24:	f0024620 			; <UNDEFINED> instruction: 0xf0024620
d001bc28:	b100f861 	tstlt	r0, r1, ror #16	; <UNPREDICTABLE>
d001bc2c:	9b091c44 	blls	0xd0262d44
d001bc30:	990b9a0a 	stmdbls	fp, {r1, r3, r9, fp, ip, pc}
d001bc34:	4b45b90b 	blmi	0xd118a068
d001bc38:	4845447b 	stmdami	r5, {r0, r1, r3, r4, r5, r6, sl, lr}^
d001bc3c:	44789200 	ldrbtmi	r9, [r8], #-512	; 0xfffffe00
d001bc40:	4d454a44 	vstrmi	s9, [r5, #-272]	; 0xfffffef0
d001bc44:	46239302 	strtmi	r9, [r3], -r2, lsl #6
d001bc48:	447a4604 	ldrbtmi	r4, [sl], #-1540	; 0xfffff9fc
d001bc4c:	447d9101 	ldrbtmi	r9, [sp], #-257	; 0xfffffeff
d001bc50:	71c0f44f 	bicvc	pc, r0, pc, asr #8
d001bc54:	ffe2f001 			; <UNDEFINED> instruction: 0xffe2f001
d001bc58:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d001bc5c:	6828fd07 	stmdavs	r8!, {r0, r1, r2, r8, sl, fp, ip, sp, lr, pc}
d001bc60:	d0482800 	suble	r2, r8, r0, lsl #16
d001bc64:	b9849c0d 	stmiblt	r4, {r0, r2, r3, sl, fp, ip, pc}
d001bc68:	b171990a 	cmnlt	r1, sl, lsl #18
d001bc6c:	b1629a0b 	cmnlt	r2, fp, lsl #20
d001bc70:	3a014e2d 	bcc	0xd006f52c
d001bc74:	68b33901 	ldmvs	r3!, {r0, r8, fp, ip, sp}
d001bc78:	f8d368db 			; <UNDEFINED> instruction: 0xf8d368db
d001bc7c:	479830b8 			; <UNDEFINED> instruction: 0x479830b8
d001bc80:	682868b3 	stmdavs	r8!, {r0, r1, r4, r5, r7, fp, sp, lr}
d001bc84:	6ddb68db 	ldclvs	8, cr6, [fp, #876]	; 0x36c
d001bc88:	20004798 	mulcs	r0, r8, r7
d001bc8c:	eb00e033 	bl	0xd0053d60
d001bc90:	f8412402 			; <UNDEFINED> instruction: 0xf8412402
d001bc94:	32014022 	andcc	r4, r1, #34	; 0x22
d001bc98:	4830e79d 	ldmdami	r0!, {r0, r2, r3, r4, r7, r8, r9, sl, sp, lr, pc}
d001bc9c:	4478a90e 	ldrbtmi	sl, [r8], #-2318	; 0xfffff6f2
d001bca0:	4c2fe7a2 	stcmi	7, cr14, [pc], #-648	; 0xd001ba20
d001bca4:	e7bc447c 			; <UNDEFINED> instruction: 0xe7bc447c
d001bca8:	46024d2e 	strmi	r4, [r2], -lr, lsr #26
d001bcac:	447d9905 	ldrbtmi	r9, [sp], #-2309	; 0xfffff6fb
d001bcb0:	f7ff4628 			; <UNDEFINED> instruction: 0xf7ff4628
d001bcb4:	2800fc2b 	stmdacs	r0, {r0, r1, r3, r5, sl, fp, ip, sp, lr, pc}
d001bcb8:	4b2bd131 	blmi	0xd0b10184
d001bcbc:	6818447b 	ldmdavs	r8, {r0, r1, r3, r4, r5, r6, sl, lr}
d001bcc0:	212fb118 			; <UNDEFINED> instruction: 0x212fb118
d001bcc4:	f0024628 			; <UNDEFINED> instruction: 0xf0024628
d001bcc8:	4b28f811 	blmi	0xd0a59d14
d001bccc:	681a447b 	ldmdavs	sl, {r0, r1, r3, r4, r5, r6, sl, lr}
d001bcd0:	d9152a01 	ldmdble	r5, {r0, r9, fp, sp}
d001bcd4:	1c43b188 	stfnep	f3, [r3], {136}	; 0x88
d001bcd8:	f44f4825 	vst2.8	{d20-d21}, [pc :128], r5
d001bcdc:	920171c0 	andls	r7, r1, #192, 2	; 0x30
d001bce0:	44784a24 	ldrbtmi	r4, [r8], #-2596	; 0xfffff5dc
d001bce4:	447a9400 	ldrbtmi	r9, [sl], #-1024	; 0xfffffc00
d001bce8:	ff98f001 			; <UNDEFINED> instruction: 0xff98f001
d001bcec:	44784822 	ldrbtmi	r4, [r8], #-2082	; 0xfffff7de
d001bcf0:	fcbcf7ff 	ldc2	7, cr15, [ip], #1020	; 0x3fc
d001bcf4:	b01e2001 	andslt	r2, lr, r1
d001bcf8:	4b20bd70 	blmi	0xd084b2c0
d001bcfc:	e7eb447b 			; <UNDEFINED> instruction: 0xe7eb447b
d001bd00:	1c43b150 	stfnep	f3, [r3], {80}	; 0x50
d001bd04:	f44f4a1e 	vst1.8	{d20-d21}, [pc :64], lr
d001bd08:	481e71c0 	ldmdami	lr, {r6, r7, r8, ip, sp, lr}
d001bd0c:	9400447a 	strls	r4, [r0], #-1146	; 0xfffffb86
d001bd10:	f0014478 			; <UNDEFINED> instruction: 0xf0014478
d001bd14:	e7e9ff83 	strb	pc, [r9, r3, lsl #31]!	; <UNPREDICTABLE>
d001bd18:	447b4b1b 	ldrbtmi	r4, [fp], #-2843	; 0xfffff4e5
d001bd1c:	491be7f2 	ldmdbmi	fp, {r1, r4, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d001bd20:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d001bd24:	e7e6fe2f 	strb	pc, [r6, pc, lsr #28]!	; <UNPREDICTABLE>
d001bd28:	2001f000 	andcs	pc, r1, r0
d001bd2c:	0003bf52 	andeq	fp, r3, r2, asr pc
d001bd30:	0003aebe 			; <UNDEFINED> instruction: 0x0003aebe
d001bd34:	0003aebc 			; <UNDEFINED> instruction: 0x0003aebc
d001bd38:	0005bf48 	andeq	fp, r5, r8, asr #30
d001bd3c:	fffffdf5 			; <UNDEFINED> instruction: 0xfffffdf5
d001bd40:	fffff8d3 			; <UNDEFINED> instruction: 0xfffff8d3
d001bd44:	0003ae7a 	andeq	sl, r3, sl, ror lr
d001bd48:	0003ae74 	andeq	sl, r3, r4, ror lr
d001bd4c:	ffffff2c 			; <UNDEFINED> instruction: 0xffffff2c
d001bd50:	0005c0e6 	andeq	ip, r5, r6, ror #1
d001bd54:	ffffff2d 			; <UNDEFINED> instruction: 0xffffff2d
d001bd58:	0003ae3a 	andeq	sl, r3, sl, lsr lr
d001bd5c:	0003bdf2 	strdeq	fp, [r3], -r2
d001bd60:	0005be80 	andeq	fp, r5, r0, lsl #29
d001bd64:	0003abd6 	ldrdeq	sl, [r3], -r6
d001bd68:	0005c1e8 	andeq	ip, r5, r8, ror #3
d001bd6c:	0003adc0 	andeq	sl, r3, r0, asr #27
d001bd70:	0005c042 	andeq	ip, r5, r2, asr #32
d001bd74:	fffffe9d 			; <UNDEFINED> instruction: 0xfffffe9d
d001bd78:	0005c036 	andeq	ip, r5, r6, lsr r0
d001bd7c:	0003ab88 	andeq	sl, r3, r8, lsl #23
d001bd80:	fffffe97 			; <UNDEFINED> instruction: 0xfffffe97
d001bd84:	0005c014 	andeq	ip, r5, r4, lsl r0
d001bd88:	0003ab6a 	andeq	sl, r3, sl, ror #22
d001bd8c:	fffff9c0 			; <UNDEFINED> instruction: 0xfffff9c0

Disassembly of section .text.editor_proc:

d001bda0 <.text.editor_proc>:
d001bda0:	460cb513 			; <UNDEFINED> instruction: 0x460cb513
d001bda4:	d0412900 	suble	r2, r1, r0, lsl #18
d001bda8:	2b10680b 	blcs	0xd0435ddc
d001bdac:	68cad13e 	stmiavs	sl, {r1, r2, r3, r4, r5, r8, ip, lr, pc}^
d001bdb0:	1301f240 	movwne	pc, #4672	; 0x1240	; <UNPREDICTABLE>
d001bdb4:	d139429a 	teqle	r9, sl	; <illegal shifter operand>
d001bdb8:	688b4a1f 	stmvs	fp, {r0, r1, r2, r3, r4, r9, fp, lr}
d001bdbc:	6812447a 	ldmdavs	r2, {r1, r3, r4, r5, r6, sl, lr}
d001bdc0:	d0044293 	mulle	r4, r3, r2
d001bdc4:	447a4a1d 	ldrbtmi	r4, [sl], #-2589	; 0xfffff5e3
d001bdc8:	42936812 	addsmi	r6, r3, #1179648	; 0x120000
d001bdcc:	4b18d12e 	blmi	0xd065028c
d001bdd0:	689b481b 	ldmvs	fp, {r0, r1, r3, r4, fp, lr}
d001bdd4:	4478491b 	ldrbtmi	r4, [r8], #-2331	; 0xfffff6e5
d001bdd8:	447968db 	ldrbtmi	r6, [r9], #-2267	; 0xfffff725
d001bddc:	6f1b4a15 	svcvs	0x001b4a15
d001bde0:	91016800 	tstls	r1, r0, lsl #16
d001bde4:	38014798 	stmdacc	r1, {r3, r4, r7, r8, r9, sl, lr}
d001bde8:	f5b09901 			; <UNDEFINED> instruction: 0xf5b09901
d001bdec:	d9043f00 	stmdble	r4, {r8, r9, sl, fp, ip, sp}
d001bdf0:	44784815 	ldrbtmi	r4, [r8], #-2069	; 0xfffff7eb
d001bdf4:	fc3af7ff 	ldc2	7, cr15, [sl], #-1020	; 0xfffffc04
d001bdf8:	4b14e007 	blmi	0xd0553e1c
d001bdfc:	447b68a2 	ldrbtmi	r6, [fp], #-2210	; 0xfffff75e
d001be00:	429a681b 	addsmi	r6, sl, #1769472	; 0x1b0000
d001be04:	f7ffd104 			; <UNDEFINED> instruction: 0xf7ffd104
d001be08:	20f0fed9 	ldrsbtcs	pc, [r0], #233	; 0xe9	; <UNPREDICTABLE>
d001be0c:	bd10b002 	ldclt	0, cr11, [r0, #-8]
d001be10:	480f4602 	stmdami	pc, {r1, r9, sl, lr}	; <UNPREDICTABLE>
d001be14:	f7ff4478 			; <UNDEFINED> instruction: 0xf7ff4478
d001be18:	b910fb79 	ldmdblt	r0, {r0, r3, r4, r5, r6, r8, r9, fp, ip, sp, lr, pc}
d001be1c:	4478480d 	ldrbtmi	r4, [r8], #-2061	; 0xfffff7f3
d001be20:	490de7e8 	stmdbmi	sp, {r3, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d001be24:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d001be28:	e7eefdad 	strb	pc, [lr, sp, lsr #27]!	; <UNPREDICTABLE>
d001be2c:	e7ed2000 	strb	r2, [sp, r0]!
d001be30:	2001f000 	andcs	pc, r1, r0
d001be34:	00020001 	andeq	r0, r2, r1
d001be38:	0003bd54 	andeq	fp, r3, r4, asr sp
d001be3c:	0003acbe 			; <UNDEFINED> instruction: 0x0003acbe
d001be40:	0003acb2 			; <UNDEFINED> instruction: 0x0003acb2
d001be44:	0003bd3a 	andeq	fp, r3, sl, lsr sp
d001be48:	fffffae6 			; <UNDEFINED> instruction: 0xfffffae6
d001be4c:	0003ac86 	andeq	sl, r3, r6, lsl #25
d001be50:	0005bd10 	andeq	fp, r5, r0, lsl sp
d001be54:	ffffff6e 			; <UNDEFINED> instruction: 0xffffff6e
d001be58:	fffff8b7 			; <UNDEFINED> instruction: 0xfffff8b7

Disassembly of section .text.startup.main:

d001c03c <.text.startup.main>:
d001c03c:	e92d2801 	push	{r0, fp, sp}
d001c040:	46044ff0 			; <UNDEFINED> instruction: 0x46044ff0
d001c044:	ed2d460f 	stc	6, cr4, [sp, #-60]!	; 0xffffffc4
d001c048:	b0978b02 	addslt	r8, r7, r2, lsl #22
d001c04c:	808cf000 	addhi	pc, ip, r0
d001c050:	f0402803 			; <UNDEFINED> instruction: 0xf0402803
d001c054:	49af8159 	stmibmi	pc!, {r0, r3, r4, r6, r8, pc}	; <UNPREDICTABLE>
d001c058:	44796878 	ldrbtmi	r6, [r9], #-2168	; 0xfffff788
d001c05c:	fe22f001 	cdp2	0, 2, cr15, cr2, cr1, {0}
d001c060:	f680fab0 			; <UNDEFINED> instruction: 0xf680fab0
d001c064:	49ac0976 	stmibmi	ip!, {r1, r2, r4, r5, r6, r8, fp}
d001c068:	44796878 	ldrbtmi	r6, [r9], #-2168	; 0xfffff788
d001c06c:	fe1af001 	cdp2	0, 1, cr15, cr10, cr1, {0}
d001c070:	b966b958 	stmdblt	r6!, {r3, r4, r6, r8, fp, ip, sp, pc}^
d001c074:	447848a9 	ldrbtmi	r4, [r8], #-2217	; 0xfffff757
d001c078:	f7ff2401 			; <UNDEFINED> instruction: 0xf7ff2401
d001c07c:	4620faf7 			; <UNDEFINED> instruction: 0x4620faf7
d001c080:	ecbdb017 	ldc	0, cr11, [sp], #92	; 0x5c
d001c084:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d001c088:	2e008ff0 	mcrcs	15, 0, r8, cr0, cr0, {7}
d001c08c:	f104d05d 			; <UNDEFINED> instruction: 0xf104d05d
d001c090:	25004480 	strcs	r4, [r0, #-1152]	; 0xfffffb80
d001c094:	46ab3c01 	strtmi	r3, [fp], r1, lsl #24
d001c098:	0024f857 	eoreq	pc, r4, r7, asr r8	; <UNPREDICTABLE>
d001c09c:	f8df2401 			; <UNDEFINED> instruction: 0xf8df2401
d001c0a0:	49a08280 	stmibmi	r0!, {r7, r9, pc}
d001c0a4:	447944f8 	ldrbtmi	r4, [r9], #-1272	; 0xfffffb08
d001c0a8:	f7ff4642 			; <UNDEFINED> instruction: 0xf7ff4642
d001c0ac:	2800fce9 	stmdacs	r0, {r0, r3, r5, r6, r7, sl, fp, ip, sp, lr, pc}
d001c0b0:	489dd15f 	ldmmi	sp, {r0, r1, r2, r3, r4, r6, r8, ip, lr, pc}
d001c0b4:	e7df4478 			; <UNDEFINED> instruction: 0xe7df4478
d001c0b8:	0389ea4f 	orreq	lr, r9, #323584	; 0x4f000
d001c0bc:	1a10ee18 	bne	0xd0457924
d001c0c0:	0029f857 	eoreq	pc, r9, r7, asr r8	; <UNPREDICTABLE>
d001c0c4:	0889eb07 	stmeq	r9, {r0, r1, r2, r8, r9, fp, sp, lr, pc}
d001c0c8:	f0019302 			; <UNDEFINED> instruction: 0xf0019302
d001c0cc:	b960fdeb 	stmdblt	r0!, {r0, r1, r3, r5, r6, r7, r8, sl, fp, ip, sp, lr, pc}^
d001c0d0:	f109b946 			; <UNDEFINED> instruction: 0xf109b946
d001c0d4:	42a10101 	adcmi	r0, r1, #1073741824	; 0x40000000
d001c0d8:	f8d8da04 			; <UNDEFINED> instruction: 0xf8d8da04
d001c0dc:	78091004 	stmdavc	r9, {r2, ip}
d001c0e0:	d130292d 	teqle	r0, sp, lsr #18
d001c0e4:	44784891 	ldrbtmi	r4, [r8], #-2193	; 0xfffff76f
d001c0e8:	4651e7c6 	ldrbmi	lr, [r1], -r6, asr #15
d001c0ec:	0029f857 	eoreq	pc, r9, r7, asr r8	; <UNPREDICTABLE>
d001c0f0:	fdd8f001 	ldc2l	0, cr15, [r8, #4]
d001c0f4:	f1bbb978 			; <UNDEFINED> instruction: 0xf1bbb978
d001c0f8:	d1090f00 	tstle	r9, r0, lsl #30
d001c0fc:	0901f109 	stmdbeq	r1, {r0, r3, r8, ip, sp, lr, pc}
d001c100:	da0545a1 	ble	0xd016d78c
d001c104:	b004f8d8 	ldrdlt	pc, [r4], -r8
d001c108:	1000f89b 	mulne	r0, fp, r8
d001c10c:	d112292d 	tstle	r2, sp, lsr #18
d001c110:	44784887 	ldrbtmi	r4, [r8], #-2183	; 0xfffff779
d001c114:	9b02e7b0 	blls	0xd00d5fdc
d001c118:	780858f9 	stmdavc	r8, {r0, r3, r4, r5, r6, r7, fp, ip, lr}
d001c11c:	d001282d 	andle	r2, r1, sp, lsr #16
d001c120:	d9022d0f 	stmdble	r2, {r0, r1, r2, r3, r8, sl, fp, sp}
d001c124:	44784883 	ldrbtmi	r4, [r8], #-2179	; 0xfffff77d
d001c128:	ab16e7a6 	blge	0xd05d5fc8
d001c12c:	0085eb03 	addeq	lr, r5, r3, lsl #22
d001c130:	f8403501 			; <UNDEFINED> instruction: 0xf8403501
d001c134:	f1091c40 			; <UNDEFINED> instruction: 0xf1091c40
d001c138:	45a10901 	strmi	r0, [r1, #2305]!	; 0x901
d001c13c:	b985dbbc 	stmiblt	r5, {r2, r3, r4, r5, r7, r8, r9, fp, ip, lr, pc}
d001c140:	4478487d 	ldrbtmi	r4, [r8], #-2173	; 0xfffff783
d001c144:	2601e798 			; <UNDEFINED> instruction: 0x2601e798
d001c148:	4b7ce7f5 	blmi	0xd1f56124
d001c14c:	0901f04f 	stmdbeq	r1, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
d001c150:	a1ecf8df 	ldrdge	pc, [ip, #143]!	; 0x8f
d001c154:	447b4635 	ldrbtmi	r4, [fp], #-1589	; 0xfffff9cb
d001c158:	44fa46b3 	ldrbtmi	r4, [sl], #1715	; 0x6b3
d001c15c:	3a10ee08 	bcc	0xd0457984
d001c160:	9806e7eb 	stmdals	r6, {r0, r1, r3, r5, r6, r7, r8, r9, sl, sp, lr, pc}
d001c164:	e79a2400 	ldr	r2, [sl, r0, lsl #8]
d001c168:	48762500 	ldmdami	r6!, {r8, sl, sp}^
d001c16c:	447846ab 	ldrbtmi	r4, [r8], #-1707	; 0xfffff955
d001c170:	f1bbe795 			; <UNDEFINED> instruction: 0xf1bbe795
d001c174:	d0290f00 	eorle	r0, r9, r0, lsl #30
d001c178:	46584a73 			; <UNDEFINED> instruction: 0x46584a73
d001c17c:	447a4973 	ldrbtmi	r4, [sl], #-2419	; 0xfffff68d
d001c180:	f7ff4479 			; <UNDEFINED> instruction: 0xf7ff4479
d001c184:	2800fc7d 	stmdacs	r0, {r0, r2, r3, r4, r5, r6, sl, fp, ip, sp, lr, pc}
d001c188:	4871d093 	ldmdami	r1!, {r0, r1, r4, r7, ip, lr, pc}^
d001c18c:	f0014478 			; <UNDEFINED> instruction: 0xf0014478
d001c190:	38f7fd7d 	ldmcc	r7!, {r0, r2, r3, r4, r5, r6, r8, sl, fp, ip, sp, lr, pc}^
d001c194:	7f81f510 	svcvc	0x0081f510
d001c198:	2c00d98b 			; <UNDEFINED> instruction: 0x2c00d98b
d001c19c:	8086f040 	addhi	pc, r6, r0, asr #32
d001c1a0:	46274b6c 	strtmi	r4, [r7], -ip, ror #22
d001c1a4:	a1b0f8df 	asrsge	pc, pc	; <illegal shifter operand>	; <UNPREDICTABLE>
d001c1a8:	f8df447b 			; <UNDEFINED> instruction: 0xf8df447b
d001c1ac:	44fab1b0 	ldrbtmi	fp, [sl], #432	; 0x1b0
d001c1b0:	44fb601c 	ldrbtmi	r6, [fp], #28
d001c1b4:	447b4b6a 	ldrbtmi	r4, [fp], #-2922	; 0xfffff496
d001c1b8:	42ac9302 	adcmi	r9, ip, #134217728	; 0x8000000
d001c1bc:	2000d11d 	andcs	sp, r0, sp, lsl r1
d001c1c0:	fcfcf7ff 	ldc2l	7, cr15, [ip], #1020	; 0x3fc
d001c1c4:	f480fab0 	vst3.32			; <UNDEFINED> instruction: 0xf480fab0
d001c1c8:	e7580964 	ldrb	r0, [r8, -r4, ror #18]
d001c1cc:	f0014640 			; <UNDEFINED> instruction: 0xf0014640
d001c1d0:	1cc3fd5d 	stclne	13, cr15, [r3], {93}	; 0x5d
d001c1d4:	7f80f5b3 	svcvc	0x0080f5b3
d001c1d8:	af6bf63f 	svcge	0x006bf63f
d001c1dc:	1e464f61 	cdpne	15, 4, cr4, cr6, cr1, {3}
d001c1e0:	447f4641 	ldrbtmi	r4, [pc], #-1601	; 0xd001c1e8
d001c1e4:	46384632 			; <UNDEFINED> instruction: 0x46384632
d001c1e8:	f948f000 			; <UNDEFINED> instruction: 0xf948f000
d001c1ec:	2204495e 	andcs	r4, r4, #1540096	; 0x178000
d001c1f0:	447919b8 	ldrbtmi	r1, [r9], #-2488	; 0xfffff648
d001c1f4:	f942f000 			; <UNDEFINED> instruction: 0xf942f000
d001c1f8:	9a02e7c7 	bls	0xd00d611c
d001c1fc:	f8daab06 			; <UNDEFINED> instruction: 0xf8daab06
d001c200:	46598000 	ldrbmi	r8, [r9], -r0
d001c204:	3024f853 	eorcc	pc, r4, r3, asr r8	; <UNPREDICTABLE>
d001c208:	2908eb02 	stmdbcs	r8, {r1, r8, r9, fp, sp, lr, pc}
d001c20c:	93034618 	movwls	r4, #13848	; 0x3618
d001c210:	f7ff464a 			; <UNDEFINED> instruction: 0xf7ff464a
d001c214:	9b03fc35 	blls	0xd011b2f0
d001c218:	4c54b948 	mrrcmi	9, 4, fp, r4, cr8	; <UNPREDICTABLE>
d001c21c:	447c4a54 	ldrbtmi	r4, [ip], #-2644	; 0xfffff5ac
d001c220:	f44f447a 	vst3.16	{d20-d22}, [pc :256], sl
d001c224:	462071c0 	strtmi	r7, [r0], -r0, asr #3
d001c228:	fcf8f001 	ldc2l	0, cr15, [r8], #4
d001c22c:	2300e01f 	movwcs	lr, #31
d001c230:	0607eb08 	streq	lr, [r7], -r8, lsl #22
d001c234:	3200f5c7 	andcc	pc, r0, #834666496	; 0x31c00000
d001c238:	93054648 	movwls	r4, #22088	; 0x5648
d001c23c:	447b4b4d 	ldrbtmi	r4, [fp], #-2893	; 0xfffff4b3
d001c240:	ab05441e 	blge	0xd016d2c0
d001c244:	f7ff4631 			; <UNDEFINED> instruction: 0xf7ff4631
d001c248:	4601f8fb 			; <UNDEFINED> instruction: 0x4601f8fb
d001c24c:	1cc3b188 	stfnep	f3, [r3], {136}	; 0x88
d001c250:	4849d102 	stmdami	r9, {r1, r8, ip, lr, pc}^
d001c254:	e70f4478 	smlsdx	pc, r8, r4, r4	; <UNPREDICTABLE>
d001c258:	464b4c48 	strbmi	r4, [fp], -r8, asr #24
d001c25c:	f44f4a48 	vst1.16	{d20-d21}, [pc], r8
d001c260:	447c71c0 	ldrbtmi	r7, [ip], #-448	; 0xfffffe40
d001c264:	447a9000 	ldrbtmi	r9, [sl], #-0
d001c268:	f0014620 			; <UNDEFINED> instruction: 0xf0014620
d001c26c:	4620fcd7 			; <UNDEFINED> instruction: 0x4620fcd7
d001c270:	9a05e702 	bls	0xd0195e80
d001c274:	f0014630 			; <UNDEFINED> instruction: 0xf0014630
d001c278:	b128fcf3 	strdlt	pc, [r8, -r3]!
d001c27c:	464b4c41 	strbmi	r4, [fp], -r1, asr #24
d001c280:	447c4a41 	ldrbtmi	r4, [ip], #-2625	; 0xfffff5bf
d001c284:	e7cc447a 			; <UNDEFINED> instruction: 0xe7cc447a
d001c288:	34014b40 	strcc	r4, [r1], #-2880	; 0xfffff4c0
d001c28c:	447b9a05 	ldrbtmi	r9, [fp], #-2565	; 0xfffff5fb
d001c290:	54b04417 	ldrtpl	r4, [r0], #1047	; 0x417
d001c294:	6038f843 	eorsvs	pc, r8, r3, asr #16
d001c298:	08c8eb03 	stmiaeq	r8, {r0, r1, r8, r9, fp, sp, lr, pc}^
d001c29c:	3000f8da 	ldrdcc	pc, [r0], -sl
d001c2a0:	2004f8c8 	andcs	pc, r4, r8, asr #17
d001c2a4:	f8ca3301 			; <UNDEFINED> instruction: 0xf8ca3301
d001c2a8:	e7863000 	str	r3, [r6, r0]
d001c2ac:	23004d38 	movwcs	r4, #3384	; 0xd38
d001c2b0:	f44f4838 	vst2.8	{d20-d21}, [pc :256], r8
d001c2b4:	447d3200 	ldrbtmi	r3, [sp], #-512	; 0xfffffe00
d001c2b8:	44789305 	ldrbtmi	r9, [r8], #-773	; 0xfffffcfb
d001c2bc:	4629ab05 	strtmi	sl, [r9], -r5, lsl #22
d001c2c0:	f8bef7ff 			; <UNDEFINED> instruction: 0xf8bef7ff
d001c2c4:	4601b948 	strmi	fp, [r1], -r8, asr #18
d001c2c8:	46289a05 	strtmi	r9, [r8], -r5, lsl #20
d001c2cc:	fcc8f001 	stc2l	0, cr15, [r8], {1}
d001c2d0:	9b05b980 	blls	0xd018a8d8
d001c2d4:	200054e8 	andcs	r5, r0, r8, ror #9
d001c2d8:	2804e008 	stmdacs	r4, {r3, sp, lr, pc}
d001c2dc:	492ed10c 	stmdbmi	lr!, {r2, r3, r8, ip, lr, pc}
d001c2e0:	4628227d 			; <UNDEFINED> instruction: 0x4628227d
d001c2e4:	f0004479 			; <UNDEFINED> instruction: 0xf0004479
d001c2e8:	2001f8c9 	andcs	pc, r1, r9, asr #17
d001c2ec:	fa12f7ff 	blx	0xd04da2f0
d001c2f0:	e6c44604 	strb	r4, [r4], r4, lsl #12
d001c2f4:	0003f06f 	andeq	pc, r3, pc, rrx
d001c2f8:	44794928 	ldrbtmi	r4, [r9], #-2344	; 0xfffff6d8
d001c2fc:	fb42f7ff 	blx	0xd10da302
d001c300:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001c304:	e7e6aebc 			; <UNDEFINED> instruction: 0xe7e6aebc
d001c308:	f77f2800 			; <UNDEFINED> instruction: 0xf77f2800
d001c30c:	2600aeb3 			; <UNDEFINED> instruction: 0x2600aeb3
d001c310:	bf00e6a9 	svclt	0x0000e6a9
d001c314:	fffffe06 			; <UNDEFINED> instruction: 0xfffffe06
d001c318:	fffffdf6 			; <UNDEFINED> instruction: 0xfffffdf6
d001c31c:	fffffded 			; <UNDEFINED> instruction: 0xfffffded
d001c320:	0005ba80 	andeq	fp, r5, r0, lsl #21
d001c324:	fffffed9 			; <UNDEFINED> instruction: 0xfffffed9
d001c328:	fffffece 			; <UNDEFINED> instruction: 0xfffffece
d001c32c:	fffffdc5 			; <UNDEFINED> instruction: 0xfffffdc5
d001c330:	fffffdd1 			; <UNDEFINED> instruction: 0xfffffdd1
d001c334:	fffffdf2 			; <UNDEFINED> instruction: 0xfffffdf2
d001c338:	fffffe06 			; <UNDEFINED> instruction: 0xfffffe06
d001c33c:	fffffd52 			; <UNDEFINED> instruction: 0xfffffd52
d001c340:	fffffd86 			; <UNDEFINED> instruction: 0xfffffd86
d001c344:	fffffcea 			; <UNDEFINED> instruction: 0xfffffcea
d001c348:	0003a706 	andeq	sl, r3, r6, lsl #14
d001c34c:	fffffe36 			; <UNDEFINED> instruction: 0xfffffe36
d001c350:	0003a6f8 	strdeq	sl, [r3], -r8
d001c354:	0003a8e4 	andeq	sl, r3, r4, ror #17
d001c358:	0003a8de 	ldrdeq	sl, [r3], -lr
d001c35c:	fffffdcd 			; <UNDEFINED> instruction: 0xfffffdcd
d001c360:	0003a8da 	ldrdeq	sl, [r3], -sl	; <UNPREDICTABLE>
d001c364:	0003a6a2 	andeq	sl, r3, r2, lsr #13
d001c368:	fffffdc9 			; <UNDEFINED> instruction: 0xfffffdc9
d001c36c:	0005bb06 	andeq	fp, r5, r6, lsl #22
d001c370:	fffffd9f 			; <UNDEFINED> instruction: 0xfffffd9f
d001c374:	0003b8d6 	ldrdeq	fp, [r3], -r6
d001c378:	fffffd86 			; <UNDEFINED> instruction: 0xfffffd86
d001c37c:	0005bac2 	andeq	fp, r5, r2, asr #21
d001c380:	fffffd94 			; <UNDEFINED> instruction: 0xfffffd94
d001c384:	0005baa2 	andeq	fp, r5, r2, lsr #21
d001c388:	fffffd8d 			; <UNDEFINED> instruction: 0xfffffd8d
d001c38c:	0003b802 	andeq	fp, r3, r2, lsl #16
d001c390:	0003b85e 	andeq	fp, r3, lr, asr r8
d001c394:	0005b86a 	andeq	fp, r5, sl, ror #16
d001c398:	000000b8 	strheq	r0, [r0], -r8
d001c39c:	fffffd2f 			; <UNDEFINED> instruction: 0xfffffd2f

Disassembly of section .text.initMalloc:

d001c420 <.text.initMalloc>:
d001c420:	f44f4b06 			; <UNDEFINED> instruction: 0xf44f4b06
d001c424:	4a064180 	bmi	0xd01aca2c
d001c428:	589a447b 	ldmpl	sl, {r0, r1, r3, r4, r5, r6, sl, lr}
d001c42c:	4a056011 	bmi	0xd0174478
d001c430:	4b05589a 	blmi	0xd01726a0
d001c434:	601a447b 	andsvs	r4, sl, fp, ror r4
d001c438:	bf004770 	svclt	0x00004770
d001c43c:	000018e0 	andeq	r1, r0, r0, ror #17
d001c440:	00000004 	andeq	r0, r0, r4
d001c444:	00000000 	andeq	r0, r0, r0
d001c448:	0005ba74 	andeq	fp, r5, r4, ror sl

Disassembly of section .text.applet_entry:

d001c44c <.text.applet_entry>:
d001c44c:	9101b507 	tstls	r1, r7, lsl #10
d001c450:	ffe6f7ff 			; <UNDEFINED> instruction: 0xffe6f7ff
d001c454:	b0039901 	andlt	r9, r3, r1, lsl #18
d001c458:	eb04f85d 	bl	0xd015a5d4
d001c45c:	bdeef7ff 	stcllt	7, cr15, [lr, #1020]!	; 0x3fc

Disassembly of section .text.memset:

d001c460 <.text.memset>:
d001c460:	b2c9b15a 	sbclt	fp, r9, #-2147483626	; 0x80000016
d001c464:	b4104603 	ldrlt	r4, [r0], #-1539	; 0xfffff9fd
d001c468:	461a1884 	ldrmi	r1, [sl], -r4, lsl #17
d001c46c:	42a33301 	adcmi	r3, r3, #67108864	; 0x4000000
d001c470:	d1fa7011 	mvnsle	r7, r1, lsl r0
d001c474:	4b04f85d 	blmi	0xd015a5f0
d001c478:	47704770 			; <UNDEFINED> instruction: 0x47704770

Disassembly of section .text.memcpy:

d001c47c <.text.memcpy>:
d001c47c:	4603b162 	strmi	fp, [r3], -r2, ror #2
d001c480:	1885b430 	stmne	r5, {r4, r5, sl, ip, sp, pc}
d001c484:	461c780a 	ldrmi	r7, [ip], -sl, lsl #16
d001c488:	31013301 	tstcc	r1, r1, lsl #6
d001c48c:	42abb2d2 	adcmi	fp, fp, #536870925	; 0x2000000d
d001c490:	d1f77022 	mvnsle	r7, r2, lsr #32
d001c494:	4770bc30 			; <UNDEFINED> instruction: 0x4770bc30
d001c498:	bf004770 	svclt	0x00004770

Disassembly of section .text.memcmp:

d001c49c <.text.memcmp>:
d001c49c:	46034402 	strmi	r4, [r3], -r2, lsl #8
d001c4a0:	d0134290 	mulsle	r3, r0, r2
d001c4a4:	e002b470 	and	fp, r2, r0, ror r4
d001c4a8:	46034290 			; <UNDEFINED> instruction: 0x46034290
d001c4ac:	f813d00b 			; <UNDEFINED> instruction: 0xf813d00b
d001c4b0:	f8115b01 			; <UNDEFINED> instruction: 0xf8115b01
d001c4b4:	46184b01 	ldrmi	r4, [r8], -r1, lsl #22
d001c4b8:	42a5b2ee 	adcmi	fp, r5, #-536870898	; 0xe000000e
d001c4bc:	d0f3b2e3 	rscsle	fp, r3, r3, ror #5
d001c4c0:	bc701af0 			; <UNDEFINED> instruction: 0xbc701af0
d001c4c4:	20004770 	andcs	r4, r0, r0, ror r7
d001c4c8:	4770bc70 			; <UNDEFINED> instruction: 0x4770bc70
d001c4cc:	47702000 	ldrbmi	r2, [r0, -r0]!

Disassembly of section .text.sb_f_fixed:

d001c4d0 <.text.sb_f_fixed>:
d001c4d0:	0b40eeb5 	bleq	0xd1057fac
d001c4d4:	4ff0e92d 	svcmi	0x00f0e92d
d001c4d8:	fa10eef1 	blx	0xd04580a4
d001c4dc:	d0354606 	eorsle	r4, r5, r6, lsl #12
d001c4e0:	6b04eeb2 	blvs	0xd0157fb0
d001c4e4:	eeb02400 	cdp	4, 11, cr2, cr0, cr0, {0}
d001c4e8:	eeb47b40 	vcmp.f64	d7, d0
d001c4ec:	eef10bc6 	vsqrt.f64	d16, d6
d001c4f0:	da22fa10 	ble	0xd08dad38
d001c4f4:	6b00eeb7 	blvs	0xd0057fd8
d001c4f8:	7bc6eeb4 	blvc	0xcf1d7fd0
d001c4fc:	fa10eef1 	blx	0xd04580c8
d001c500:	80a6f140 	adchi	pc, r6, r0, asr #2
d001c504:	5b04eeb2 	blpl	0xd0157fd4
d001c508:	73a1f46f 			; <UNDEFINED> instruction: 0x73a1f46f
d001c50c:	eeb4e004 	cdp	0, 11, cr14, cr4, cr4, {0}
d001c510:	eef17bc6 	vsqrt.f64	d23, d6
d001c514:	d504fa10 	strle	pc, [r4, #-2576]	; 0xfffff5f0
d001c518:	ee273c01 	cdp	12, 2, cr3, cr7, cr1, {0}
d001c51c:	429c7b05 	addsmi	r7, ip, #5120	; 0x1400
d001c520:	ea24daf5 	b	0xd09530fc
d001c524:	ea6f73e4 	b	0xd1bf94bc
d001c528:	459c0c01 	ldrmi	r0, [ip, #3073]	; 0xc01
d001c52c:	2000dd16 	andcs	sp, r0, r6, lsl sp
d001c530:	8ff0e8bd 	svchi	0x00f0e8bd
d001c534:	7f9af5b4 	svcvc	0x009af5b4
d001c538:	ee87d0dc 	mcr	0, 4, sp, cr7, cr12, {6}
d001c53c:	34017b06 	strcc	r7, [r1], #-2822	; 0xfffff4fa
d001c540:	7bc6eeb4 	blvc	0xcf1d8018
d001c544:	fa10eef1 	blx	0xd0458110
d001c548:	e7d3daf4 			; <UNDEFINED> instruction: 0xe7d3daf4
d001c54c:	eeb02300 	cdp	3, 11, cr2, cr0, cr0, {0}
d001c550:	461c7b40 	ldrmi	r7, [ip], -r0, asr #22
d001c554:	0c01ea6f 			; <UNDEFINED> instruction: 0x0c01ea6f
d001c558:	dce8459c 	cfstr64le	mvdx4, [r8], #624	; 0x270
d001c55c:	0b00f04f 	bleq	0xd00586a0
d001c560:	5b04eeb2 	blpl	0xd0158030
d001c564:	0902ea41 	stmdbeq	r2, {r0, r6, r9, fp, sp, lr, pc}
d001c568:	38fff10c 	ldmcc	pc!, {r2, r3, r8, ip, sp, lr, pc}^	; <UNPREDICTABLE>
d001c56c:	43f74658 	mvnsmi	r4, #88, 12	; 0x5800000
d001c570:	0a30f04f 	beq	0xd0c586b4
d001c574:	4b38ed9f 	blmi	0xd0e57bf8
d001c578:	0b40eeb5 	bleq	0xd1058054
d001c57c:	fa10eef1 	blx	0xd0458148
d001c580:	42a3d030 	adcmi	sp, r3, #48	; 0x30
d001c584:	eefddc2e 	cdp	12, 15, cr13, cr13, cr14, {1}
d001c588:	f10b6bc7 			; <UNDEFINED> instruction: 0xf10b6bc7
d001c58c:	ee160b01 	vnmls.f64	d0, d6, d1
d001c590:	ee161a90 	vmov	r1, s13
d001c594:	29092a90 	stmdbcs	r9, {r4, r7, r9, fp, sp}
d001c598:	2209bfa8 	andcs	fp, r9, #168, 30	; 0x2a0
d001c59c:	0f11f1bb 	svceq	0x0011f1bb
d001c5a0:	72e2ea22 	rscvc	lr, r2, #139264	; 0x22000
d001c5a4:	2a90ee06 	bcs	0xce457dc4
d001c5a8:	6be6eeb8 	blvs	0xcf9d8090
d001c5ac:	7b46ee37 	blvc	0xd11d7e90
d001c5b0:	7b05ee27 	blvc	0xd0197e54
d001c5b4:	459cdc16 	ldrmi	sp, [ip, #3094]	; 0xc16
d001c5b8:	3230d018 	eorscc	sp, r0, #24
d001c5bc:	5432b2d2 	ldrtpl	fp, [r2], #-722	; 0xfffffd2e
d001c5c0:	3b013001 	blcc	0xd00685cc
d001c5c4:	d0b34543 	adcsle	r4, r3, r3, asr #10
d001c5c8:	d1d51c59 	bicsle	r1, r5, r9, asr ip
d001c5cc:	0f00f1b9 	svceq	0x0000f1b9
d001c5d0:	eeb5d0d2 	mrc	0, 5, sp, cr5, cr2, {6}
d001c5d4:	f04f0b40 			; <UNDEFINED> instruction: 0xf04f0b40
d001c5d8:	5432022e 	ldrtpl	r0, [r2], #-558	; 0xfffffdd2
d001c5dc:	eef13001 	cdp	0, 15, cr3, cr1, cr1, {0}
d001c5e0:	d1cefa10 	bicle	pc, lr, r0, lsl sl	; <UNPREDICTABLE>
d001c5e4:	d0ec459c 	smlalle	r4, ip, ip, r5
d001c5e8:	e7e82230 			; <UNDEFINED> instruction: 0xe7e82230
d001c5ec:	dd1e2905 	vldrle.16	s4, [lr, #-10]	; <UNPREDICTABLE>
d001c5f0:	dd172800 	ldcle	8, cr2, [r7, #-0]
d001c5f4:	0e00eb06 	vmlaeq.f64	d14, d0, d6
d001c5f8:	f8124672 			; <UNDEFINED> instruction: 0xf8124672
d001c5fc:	292e1d01 	stmdbcs	lr!, {r0, r8, sl, fp, ip}
d001c600:	0502eb07 	streq	lr, [r2, #-2823]	; 0xfffff4f9
d001c604:	2938d003 	ldmdbcs	r8!, {r0, r1, ip, lr, pc}
d001c608:	f882d91f 			; <UNDEFINED> instruction: 0xf882d91f
d001c60c:	3501a000 	strcc	sl, [r1, #-0]
d001c610:	2800d1f3 	stmdacs	r0, {r0, r1, r4, r5, r6, r7, r8, ip, lr, pc}
d001c614:	4672dd06 	ldrbtmi	sp, [r2], -r6, lsl #26
d001c618:	1c01f812 	stcne	8, cr15, [r1], {18}
d001c61c:	1901f802 	stmdbne	r1, {r1, fp, ip, sp, lr, pc}
d001c620:	d1f94296 			; <UNDEFINED> instruction: 0xd1f94296
d001c624:	0231f04f 	eorseq	pc, r1, #79	; 0x4f
d001c628:	70323001 	eorsvc	r3, r2, r1
d001c62c:	d1c8e7c9 	bicle	lr, r8, r9, asr #15
d001c630:	7bc4eeb4 	blvc	0xcf158108
d001c634:	fa10eef1 	blx	0xd0458200
d001c638:	2800dcda 	stmdacs	r0, {r1, r3, r4, r6, r7, sl, fp, ip, lr, pc}
d001c63c:	1832d0c1 	ldmdane	r2!, {r0, r6, r7, ip, lr, pc}
d001c640:	2c01f812 	stccs	8, cr15, [r1], {18}
d001c644:	d5bc07d2 	ldrle	r0, [ip, #2002]!	; 0x7d2
d001c648:	3101e7d2 	ldrdcc	lr, [r1, -r2]
d001c64c:	e7b87011 			; <UNDEFINED> instruction: 0xe7b87011
d001c650:	e77f4623 	ldrb	r4, [pc, -r3, lsr #12]!
d001c654:	8000f3af 	andhi	pc, r0, pc, lsr #7
d001c658:	812dea11 			; <UNDEFINED> instruction: 0x812dea11
d001c65c:	3d719799 	ldclcc	7, cr9, [r1, #-612]!	; 0xfffffd9c

Disassembly of section .text.sb_f_exponent:

d001c660 <.text.sb_f_exponent>:
d001c660:	0b40eeb5 	bleq	0xd105813c
d001c664:	4ff0e92d 	svcmi	0x00f0e92d
d001c668:	fa10eef1 	blx	0xd0458234
d001c66c:	d0344607 	eorsle	r4, r4, r7, lsl #12
d001c670:	6b04eeb2 	blvs	0xd0158140
d001c674:	0bc6eeb4 	bleq	0xcf1d814c
d001c678:	fa10eef1 	blx	0xd0458244
d001c67c:	80cef2c0 	sbchi	pc, lr, r0, asr #5
d001c680:	7b40eeb0 	blvc	0xd1058148
d001c684:	e0022400 	and	r2, r2, r0, lsl #8
d001c688:	7f9af5b4 	svcvc	0x009af5b4
d001c68c:	ee87d007 	cdp	0, 8, cr13, cr7, cr7, {0}
d001c690:	34017b06 	strcc	r7, [r1], #-2822	; 0xfffff4fa
d001c694:	7bc6eeb4 	blvc	0xcf1d816c
d001c698:	fa10eef1 	blx	0xd0458264
d001c69c:	eeb7daf4 			; <UNDEFINED> instruction: 0xeeb7daf4
d001c6a0:	eeb46b00 	vmov.f64	d6, #64	; 0x3e000000  0.125
d001c6a4:	eef17bc6 	vsqrt.f64	d23, d6
d001c6a8:	d519fa10 	ldrle	pc, [r9, #-2576]	; 0xfffff5f0
d001c6ac:	5b04eeb2 	blpl	0xd015817c
d001c6b0:	70a1f46f 	adcvc	pc, r1, pc, ror #8
d001c6b4:	eeb4e004 	cdp	0, 11, cr14, cr4, cr4, {0}
d001c6b8:	eef17bc6 	vsqrt.f64	d23, d6
d001c6bc:	d50ffa10 	strle	pc, [pc, #-2576]	; 0xd001bcb4
d001c6c0:	ee273c01 	cdp	12, 2, cr3, cr7, cr1, {0}
d001c6c4:	42847b05 	addmi	r7, r4, #5120	; 0x1400
d001c6c8:	f111daf5 			; <UNDEFINED> instruction: 0xf111daf5
d001c6cc:	d50a0e01 	strle	r0, [sl, #-3585]	; 0xfffff1ff
d001c6d0:	2102463e 	tstcs	r2, lr, lsr r6
d001c6d4:	22002501 	andcs	r2, r0, #4194304	; 0x400000
d001c6d8:	eeb0e062 	cdp	0, 11, cr14, cr0, cr2, {3}
d001c6dc:	24007b40 	strcs	r7, [r0], #-2880	; 0xfffff4c0
d001c6e0:	0e01f111 	mcreq	1, 0, pc, cr1, cr1, {0}	; <UNPREDICTABLE>
d001c6e4:	2500d4f4 	strcs	sp, [r0, #-1268]	; 0xfffffb0c
d001c6e8:	5b04eeb2 	blpl	0xd01581b8
d001c6ec:	0902ea41 	stmdbeq	r2, {r0, r6, r9, fp, sp, lr, pc}
d001c6f0:	462a1c88 	strtmi	r1, [sl], -r8, lsl #25
d001c6f4:	0807ea6f 	stmdaeq	r7, {r0, r1, r2, r3, r5, r6, r9, fp, sp, lr, pc}
d001c6f8:	0a30f04f 	beq	0xd0c5883c
d001c6fc:	0b2ef04f 	bleq	0xd0bd8840
d001c700:	4b49ed9f 	blmi	0xd1297d84
d001c704:	0b40eeb5 	bleq	0xd10581e0
d001c708:	fa10eef1 	blx	0xd04582d4
d001c70c:	4575d114 	ldrbmi	sp, [r5, #-276]!	; 0xfffffeec
d001c710:	2130d002 	teqcs	r0, r2
d001c714:	320154b9 	andcc	r5, r1, #-1191182336	; 0xb9000000
d001c718:	42853501 	addmi	r3, r5, #4194304	; 0x400000
d001c71c:	2d01d03d 	stccs	0, cr13, [r1, #-244]	; 0xffffff0c
d001c720:	f1b9d1f0 			; <UNDEFINED> instruction: 0xf1b9d1f0
d001c724:	d0ed0f00 	rscle	r0, sp, r0, lsl #30
d001c728:	0b40eeb5 	bleq	0xd1058204
d001c72c:	b002f807 	andlt	pc, r2, r7, lsl #16
d001c730:	eef13201 	cdp	2, 15, cr3, cr1, cr1, {0}
d001c734:	d0eafa10 	rscle	pc, sl, r0, lsl sl	; <UNPREDICTABLE>
d001c738:	6bc7eefd 	blvs	0xcf218334
d001c73c:	6a90ee16 	bvs	0xce457f9c
d001c740:	1a90ee16 	bne	0xce457fa0
d001c744:	bfa82e09 	svclt	0x00a82e09
d001c748:	45752109 	ldrbmi	r2, [r5, #-265]!	; 0xfffffef7
d001c74c:	71e1ea21 	mvnvc	lr, r1, lsr #20
d001c750:	1a90ee06 	bne	0xce457f70
d001c754:	6be6eeb8 	blvs	0xcf9d823c
d001c758:	7b46ee37 	blvc	0xd11d803c
d001c75c:	7b05ee27 	blvc	0xd0198000
d001c760:	3130d002 	teqcc	r0, r2
d001c764:	e7d5b2c9 	ldrb	fp, [r5, r9, asr #5]
d001c768:	dd462e05 	stclle	14, cr2, [r6, #-20]	; 0xffffffec
d001c76c:	dd0d2a00 	vstrle	s4, [sp, #-0]
d001c770:	f81118b9 			; <UNDEFINED> instruction: 0xf81118b9
d001c774:	2e2e6d01 	cdpcs	13, 2, cr6, cr14, cr1, {0}
d001c778:	0c01eb08 			; <UNDEFINED> instruction: 0x0c01eb08
d001c77c:	2e38d003 	cdpcs	0, 3, cr13, cr8, cr3, {0}
d001c780:	f881d949 			; <UNDEFINED> instruction: 0xf881d949
d001c784:	f1bca000 			; <UNDEFINED> instruction: 0xf1bca000
d001c788:	d1f23fff 	ldrshle	r3, [r2, #255]!	; 0xff
d001c78c:	f04f3501 			; <UNDEFINED> instruction: 0xf04f3501
d001c790:	34010131 	strcc	r0, [r1], #-305	; 0xfffffecf
d001c794:	70394285 	eorsvc	r4, r9, r5, lsl #5
d001c798:	18bed1c1 	ldmne	lr!, {r0, r6, r7, r8, ip, lr, pc}
d001c79c:	1c911c55 	ldcne	12, cr1, [r1], {85}	; 0x55
d001c7a0:	bf142b00 	svclt	0x00142b00
d001c7a4:	20652045 	rsbcs	r2, r5, r5, asr #32
d001c7a8:	70302c00 	eorsvc	r2, r0, r0, lsl #24
d001c7ac:	232dbfb4 			; <UNDEFINED> instruction: 0x232dbfb4
d001c7b0:	2c00232b 	stccs	3, cr2, [r0], {43}	; 0x2b
d001c7b4:	bfb8557b 	svclt	0x00b8557b
d001c7b8:	2c634264 	sfmcs	f4, 2, [r3], #-400	; 0xfffffe70
d001c7bc:	4b1cdd06 	blmi	0xd0753bdc
d001c7c0:	0304fba3 	movweq	pc, #19363	; 0x4ba3	; <UNPREDICTABLE>
d001c7c4:	3330095b 	teqcc	r0, #1490944	; 0x16c000
d001c7c8:	1cd1547b 	cfldrdne	mvd5, [r1], {123}	; 0x7b
d001c7cc:	187d4a19 	ldmdane	sp!, {r0, r3, r4, r9, fp, lr}^
d001c7d0:	0304fba2 	movweq	pc, #19362	; 0x4ba2	; <UNPREDICTABLE>
d001c7d4:	08db1c88 	ldmeq	fp, {r3, r7, sl, fp, ip}^
d001c7d8:	6203fba2 	andvs	pc, r3, #165888	; 0x28800
d001c7dc:	0683eb03 	streq	lr, [r3], r3, lsl #22
d001c7e0:	eba408d2 	bl	0xce91eb30
d001c7e4:	eb020446 	bl	0xd009d904
d001c7e8:	34300282 	ldrtcc	r0, [r0], #-642	; 0xfffffd7e
d001c7ec:	0342eba3 	movteq	lr, #11171	; 0x2ba3
d001c7f0:	547b3330 	ldrbtpl	r3, [fp], #-816	; 0xfffffcd0
d001c7f4:	e8bd706c 	pop	{r2, r3, r5, r6, ip, sp, lr}
d001c7f8:	d18d8ff0 	strdle	r8, [sp, r0]
d001c7fc:	7bc4eeb4 	blvc	0xcf1582d4
d001c800:	fa10eef1 	blx	0xd04583cc
d001c804:	2a00dcb2 	bcs	0xd0053ad4
d001c808:	18b9d086 	ldmne	r9!, {r1, r2, r7, ip, lr, pc}
d001c80c:	1c01f811 	stcne	8, cr15, [r1], {17}
d001c810:	d58107c9 	strle	r0, [r1, #1993]	; 0x7c9
d001c814:	3601e7aa 	strcc	lr, [r1], -sl, lsr #15
d001c818:	e77d700e 	ldrb	r7, [sp, -lr]!
d001c81c:	7b40eeb0 	blvc	0xd10582e4
d001c820:	e73c2400 	ldr	r2, [ip, -r0, lsl #8]!
d001c824:	8000f3af 	andhi	pc, r0, pc, lsr #7
d001c828:	812dea11 			; <UNDEFINED> instruction: 0x812dea11
d001c82c:	3d719799 	ldclcc	7, cr9, [r1, #-612]!	; 0xfffffd9c
d001c830:	51eb851f 	mvnpl	r8, pc, lsl r5
d001c834:	cccccccd 	stclgt	12, cr12, [ip], {205}	; 0xcd

Disassembly of section .text.sb_flush.part.0:

d001c838 <.text.sb_flush.part.0>:
d001c838:	2090f8d0 			; <UNDEFINED> instruction: 0x2090f8d0
d001c83c:	4b07b16a 	blmi	0xd0208dec
d001c840:	0110f100 	tsteq	r0, r0, lsl #2	; <UNPREDICTABLE>
d001c844:	681b689b 	ldmdavs	fp, {r0, r1, r3, r4, r7, fp, sp, lr}
d001c848:	685bb510 	ldmdavs	fp, {r4, r8, sl, ip, sp, pc}^
d001c84c:	20004604 	andcs	r4, r0, r4, lsl #12
d001c850:	23004798 	movwcs	r4, #1944	; 0x798
d001c854:	3090f8c4 	addscc	pc, r0, r4, asr #17
d001c858:	4770bd10 			; <UNDEFINED> instruction: 0x4770bd10
d001c85c:	2001f000 	andcs	pc, r1, r0

Disassembly of section .text.sb_char:

d001c860 <.text.sb_char>:
d001c860:	b51068c3 	ldrlt	r6, [r0, #-2243]	; 0xfffff73d
d001c864:	b1834604 	orrlt	r4, r3, r4, lsl #12
d001c868:	3090f8d0 			; <UNDEFINED> instruction: 0x3090f8d0
d001c86c:	44031c5a 	strmi	r1, [r3], #-3162	; 0xfffff3a6
d001c870:	f8c02a80 			; <UNDEFINED> instruction: 0xf8c02a80
d001c874:	74192090 	ldrvc	r2, [r9], #-144	; 0xffffff70
d001c878:	68a3d013 	stmiavs	r3!, {r0, r1, r4, ip, lr, pc}
d001c87c:	4200f06f 	andmi	pc, r0, #111	; 0x6f
d001c880:	d2014293 	andle	r4, r1, #805306377	; 0x30000009
d001c884:	60a33301 	adcvs	r3, r3, r1, lsl #6
d001c888:	6800bd10 	stmdavs	r0, {r4, r8, sl, fp, ip, sp, pc}
d001c88c:	d0f42800 	rscsle	r2, r4, r0, lsl #16
d001c890:	68a36862 	stmiavs	r3!, {r1, r5, r6, fp, sp, lr}
d001c894:	bf182a00 	svclt	0x00182a00
d001c898:	42933a01 	addsmi	r3, r3, #4096	; 0x1000
d001c89c:	54c1d2ee 	strbpl	sp, [r1], #750	; 0x2ee
d001c8a0:	f7ffe7eb 			; <UNDEFINED> instruction: 0xf7ffe7eb
d001c8a4:	68a3ffc9 	stmiavs	r3!, {r0, r3, r6, r7, r8, r9, sl, fp, ip, sp, lr, pc}
d001c8a8:	bf00e7e8 	svclt	0x0000e7e8

Disassembly of section .text.sb_number:

d001c8c0 <.text.sb_number>:
d001c8c0:	4ff0e92d 	svcmi	0x00f0e92d
d001c8c4:	8b02ed2d 	blhi	0xd00d7d80
d001c8c8:	ee08b09b 	mcr	0, 0, fp, cr8, cr11, {4}
d001c8cc:	93070a10 	movwls	r0, #31248	; 0x7a10
d001c8d0:	92069b2b 	andls	r9, r6, #44032	; 0xac00
d001c8d4:	d13e2b00 	teqle	lr, r0, lsl #22
d001c8d8:	e9dd4bbf 	ldmib	sp, {r0, r1, r2, r3, r4, r5, r7, r8, r9, fp, lr}^
d001c8dc:	447b1206 	ldrbtmi	r1, [fp], #-518	; 0xfffffdfa
d001c8e0:	460b9305 	strmi	r9, [fp], -r5, lsl #6
d001c8e4:	d13e4313 	teqle	lr, r3, lsl r3
d001c8e8:	9a2a9b2a 	bls	0xd0ac3598
d001c8ec:	bf183b00 	svclt	0x00183b00
d001c8f0:	2a002301 	bcs	0xd00254fc
d001c8f4:	9303d137 	movwls	sp, #12599	; 0x3137
d001c8f8:	2b009b27 	blcs	0xd004359c
d001c8fc:	9b28d179 	blls	0xd0a50ee8
d001c900:	f1000759 			; <UNDEFINED> instruction: 0xf1000759
d001c904:	ea4f8101 	b	0xd13fcd10
d001c908:	9a2c0983 	bls	0xd0b1ef1c
d001c90c:	1a40f3c9 	bne	0xd1059838
d001c910:	0920f009 	stmdbeq	r0!, {r0, r3, ip, sp, lr, pc}
d001c914:	2a004653 	bcs	0xd002e268
d001c918:	9a26d072 	bls	0xd09d0ae8
d001c91c:	f0002a10 			; <UNDEFINED> instruction: 0xf0002a10
d001c920:	9a2680f8 	bls	0xd09bcd08
d001c924:	f0002a02 			; <UNDEFINED> instruction: 0xf0002a02
d001c928:	9a268144 	bls	0xd09bce40
d001c92c:	9a032a08 	bls	0xd00e7154
d001c930:	8122f000 	msrhi	CPSR_x, r0
d001c934:	2600992a 	strcs	r9, [r0], -sl, lsr #18
d001c938:	82a0f8df 	adchi	pc, r0, #14614528	; 0xdf0000
d001c93c:	44f84291 	ldrbtmi	r4, [r8], #657	; 0x291
d001c940:	9a03dc69 	bls	0xd0113aec
d001c944:	19942700 	ldmibne	r4, {r8, r9, sl, sp}
d001c948:	44239a29 	strtmi	r9, [r3], #-2601	; 0xfffff5d7
d001c94c:	f0c04293 			; <UNDEFINED> instruction: 0xf0c04293
d001c950:	463c80e8 	ldrtmi	r8, [ip], -r8, ror #1
d001c954:	4ba2e0e7 	blmi	0xce8d4cf8
d001c958:	1206e9dd 	andne	lr, r6, #3620864	; 0x374000
d001c95c:	9305447b 	movwls	r4, #21627	; 0x547b
d001c960:	4313460b 	tstmi	r3, #11534336	; 0xb00000
d001c964:	ab09d0c0 	blge	0xd0290c6c
d001c968:	26012200 	strcs	r2, [r1], -r0, lsl #4
d001c96c:	e9dd9304 	ldmib	sp, {r2, r8, r9, ip, pc}^
d001c970:	469b3406 	ldrmi	r3, [fp], r6, lsl #8
d001c974:	46272300 	strtmi	r2, [r7], -r0, lsl #6
d001c978:	9b269303 	blls	0xd09c158c
d001c97c:	e9cd4619 	stmib	sp, {r0, r3, r4, r9, sl, lr}^
d001c980:	23001200 	movwcs	r1, #512	; 0x200
d001c984:	0ffa203f 	svceq	0x00fa203f
d001c988:	b008f8cd 	andlt	pc, r8, sp, asr #17
d001c98c:	469a4699 			; <UNDEFINED> instruction: 0x469a4699
d001c990:	99023801 	stmdbls	r2, {r0, fp, ip, sp}
d001c994:	0420f1c0 	strteq	pc, [r0], #-448	; 0xfffffe40
d001c998:	0520f1a0 	streq	pc, [r0, #-416]!	; 0xfffffe60
d001c99c:	f1b040c1 			; <UNDEFINED> instruction: 0xf1b040c1
d001c9a0:	fa073fff 	blx	0xd01ec9a4
d001c9a4:	fa27fe04 	blx	0xd0a1c1bc
d001c9a8:	fa26fc05 	blx	0xd09db9c4
d001c9ac:	fa06f404 	blx	0xd01d99c4
d001c9b0:	ea41f505 	b	0xd1099dcc
d001c9b4:	fa06010e 	blx	0xd019cdf4
d001c9b8:	ea44f800 	b	0xd115a9c0
d001c9bc:	ea410405 	b	0xd105d9d8
d001c9c0:	d072010c 	rsbsle	r0, r2, ip, lsl #2
d001c9c4:	f0011895 			; <UNDEFINED> instruction: 0xf0011895
d001c9c8:	eb430101 	bl	0xd10dcdd4
d001c9cc:	ea410c03 	b	0xd105f9e0
d001c9d0:	46630205 	strbtmi	r0, [r3], -r5, lsl #4
d001c9d4:	bc00e9dd 			; <UNDEFINED> instruction: 0xbc00e9dd
d001c9d8:	bf084563 	svclt	0x00084563
d001c9dc:	d3d7455a 	bicsle	r4, r7, #377487360	; 0x16800000
d001c9e0:	020bebb2 	andeq	lr, fp, #182272	; 0x2c800
d001c9e4:	0909ea48 	stmdbeq	r9, {r3, r6, r9, fp, sp, lr, pc}
d001c9e8:	0a0aea44 	beq	0xd02d7300
d001c9ec:	030ceb63 	movweq	lr, #52067	; 0xcb63
d001c9f0:	2301e7ce 	movwcs	lr, #6094	; 0x17ce
d001c9f4:	092df04f 	pusheq	{r0, r1, r2, r3, r6, ip, sp, lr, pc}
d001c9f8:	9a2c469a 	bls	0xd0b2e468
d001c9fc:	d18c2a00 	orrle	r2, ip, r0, lsl #20
d001ca00:	f0129a28 			; <UNDEFINED> instruction: 0xf0129a28
d001ca04:	d16a0610 	cmnle	sl, r0, lsl r6
d001ca08:	81d8f8df 	ldrsbhi	pc, [r8, #143]	; 0x8f	; <UNPREDICTABLE>
d001ca0c:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d001ca10:	4291992a 	addsmi	r9, r1, #688128	; 0xa8000
d001ca14:	9903dd95 	stmdbls	r3, {r0, r2, r4, r7, r8, sl, fp, ip, lr, pc}
d001ca18:	198a982a 	stmibne	sl, {r1, r3, r5, fp, ip, pc}
d001ca1c:	44131a47 	ldrmi	r1, [r3], #-2631	; 0xfffff5b9
d001ca20:	443b9a29 	ldrtmi	r9, [fp], #-2601	; 0xfffff5d7
d001ca24:	d87c429a 	ldmdale	ip!, {r1, r3, r4, r7, r9, lr}^
d001ca28:	24009b28 	strcs	r9, [r0], #-2856	; 0xfffff4d8
d001ca2c:	0501f003 	streq	pc, [r1, #-3]
d001ca30:	0f00f1ba 	svceq	0x0000f1ba
d001ca34:	b16ed14d 	cmnlt	lr, sp, asr #2
d001ca38:	1000f898 	mulne	r0, r8, r8
d001ca3c:	0a10ee18 	beq	0xd04582a4
d001ca40:	ff0ef7ff 			; <UNDEFINED> instruction: 0xff0ef7ff
d001ca44:	d1052e02 	tstle	r5, r2, lsl #28
d001ca48:	1001f898 	mulne	r1, r8, r8
d001ca4c:	0a10ee18 	beq	0xd04582b4
d001ca50:	ff06f7ff 			; <UNDEFINED> instruction: 0xff06f7ff
d001ca54:	b1471e7e 	hvclt	29166	; 0x71ee
d001ca58:	7a10ee18 	bvc	0xd04582c0
d001ca5c:	21303e01 	teqcs	r0, r1, lsl #28
d001ca60:	f7ff4638 			; <UNDEFINED> instruction: 0xf7ff4638
d001ca64:	1c72fefd 	ldclne	14, cr15, [r2], #-1012	; 0xfffffc0c
d001ca68:	9b03d1f8 	blls	0xd0111250
d001ca6c:	af09b163 	svcge	0x0009b163
d001ca70:	ee189b03 	vnmls.f64	d9, d8, d3
d001ca74:	443b8a10 	ldrtmi	r8, [fp], #-2576	; 0xfffff5f0
d001ca78:	f816461e 			; <UNDEFINED> instruction: 0xf816461e
d001ca7c:	46401d01 	strbmi	r1, [r0], -r1, lsl #26
d001ca80:	feeef7ff 	mcr2	7, 7, pc, cr14, cr15, {7}	; <UNPREDICTABLE>
d001ca84:	d1f842b7 	ldrhle	r4, [r8, #39]!	; 0x27
d001ca88:	1e65b155 	mcrne	1, 3, fp, cr5, cr5, {2}
d001ca8c:	ee18b144 	mnfem	f3, f4
d001ca90:	3d014a10 	vstrcc	s8, [r1, #-64]	; 0xffffffc0
d001ca94:	46202120 	strtmi	r2, [r0], -r0, lsr #2
d001ca98:	fee2f7ff 	mcr2	7, 7, pc, cr2, cr15, {7}	; <UNPREDICTABLE>
d001ca9c:	d1f81c6b 	mvnsle	r1, fp, ror #24
d001caa0:	ecbdb01b 	ldc	0, cr11, [sp], #108	; 0x6c
d001caa4:	e8bd8b02 	pop	{r1, r8, r9, fp, pc}
d001caa8:	99058ff0 	stmdbls	r5, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
d001caac:	9903440a 	stmdbls	r3, {r1, r3, sl, lr}
d001cab0:	31017813 	tstcc	r1, r3, lsl r8
d001cab4:	91039a04 	tstls	r3, r4, lsl #20
d001cab8:	3b01f802 	blcc	0xd009aac8
d001cabc:	030aea59 	movweq	lr, #43609	; 0xaa59
d001cac0:	f43f9204 			; <UNDEFINED> instruction: 0xf43f9204
d001cac4:	2940af19 	stmdbcs	r0, {r0, r3, r4, r8, r9, sl, fp, sp, pc}^
d001cac8:	af16f63f 	svcge	0x0016f63f
d001cacc:	465746cb 	ldrbmi	r4, [r7], -fp, asr #13
d001cad0:	4649e757 			; <UNDEFINED> instruction: 0x4649e757
d001cad4:	0a10ee18 	beq	0xd045833c
d001cad8:	fec2f7ff 	mcr2	7, 6, pc, cr2, cr15, {7}	; <UNPREDICTABLE>
d001cadc:	e9dde7ab 	ldmib	sp, {r0, r1, r3, r5, r7, r8, r9, sl, sp, lr, pc}^
d001cae0:	430a1206 	movwmi	r1, #41478	; 0xa206
d001cae4:	af19f47f 	svcge	0x0019f47f
d001cae8:	2a089a26 	bcs	0xd0243388
d001caec:	9a03d167 	bls	0xd0111090
d001caf0:	d1642a00 	cmnle	r4, r0, lsl #20
d001caf4:	21302201 	teqcs	r0, r1, lsl #4
d001caf8:	80ecf8df 	ldrdhi	pc, [ip], #143	; 0x8f	; <UNPREDICTABLE>
d001cafc:	44f89e2c 	ldrbtmi	r9, [r8], #3628	; 0xe2c
d001cb00:	f88d9203 			; <UNDEFINED> instruction: 0xf88d9203
d001cb04:	e7831024 	str	r1, [r3, r4, lsr #32]
d001cb08:	f04f2301 			; <UNDEFINED> instruction: 0xf04f2301
d001cb0c:	469a092b 	ldrmi	r0, [sl], fp, lsr #18
d001cb10:	9a2be773 	bls	0xd0b168e4
d001cb14:	f8dfb352 			; <UNDEFINED> instruction: 0xf8dfb352
d001cb18:	260280d4 			; <UNDEFINED> instruction: 0x260280d4
d001cb1c:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d001cb20:	9a29e776 	bls	0xd0a96900
d001cb24:	9b281ad4 	blls	0xd0a2367c
d001cb28:	0303f003 	movweq	pc, #12291	; 0x3003	; <UNPREDICTABLE>
d001cb2c:	d1022b02 	tstle	r2, r2, lsl #22
d001cb30:	2b009b2a 	blcs	0xd00437e0
d001cb34:	9b28db33 	blls	0xd0a53808
d001cb38:	0501f013 	streq	pc, [r1, #-19]	; 0xffffffed
d001cb3c:	af78f47f 	svcge	0x0078f47f
d001cb40:	3bfff104 	blcc	0xd0018f58
d001cb44:	d0402c00 	suble	r2, r0, r0, lsl #24
d001cb48:	ee189402 	cfmuls	mvf9, mvf8, mvf2
d001cb4c:	f10b4a10 			; <UNDEFINED> instruction: 0xf10b4a10
d001cb50:	21203bff 	strdcs	r3, [r0, -pc]!
d001cb54:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d001cb58:	f1bbfe83 			; <UNDEFINED> instruction: 0xf1bbfe83
d001cb5c:	d1f63fff 	ldrshle	r3, [r6, #255]!	; 0xff
d001cb60:	f1ba9c02 			; <UNDEFINED> instruction: 0xf1ba9c02
d001cb64:	f43f0f00 			; <UNDEFINED> instruction: 0xf43f0f00
d001cb68:	e7b2af66 	ldr	sl, [r2, r6, ror #30]!
d001cb6c:	8080f8df 	ldrdhi	pc, [r0], pc	; <UNPREDICTABLE>
d001cb70:	9a032602 	bls	0xd00e6380
d001cb74:	e74b44f8 			; <UNDEFINED> instruction: 0xe74b44f8
d001cb78:	a91ab15a 	ldmdbge	sl, {r1, r3, r4, r6, r8, ip, sp, pc}
d001cb7c:	f812188a 			; <UNDEFINED> instruction: 0xf812188a
d001cb80:	2a302c45 	bcs	0xd0c27c9c
d001cb84:	f8dfd105 			; <UNDEFINED> instruction: 0xf8dfd105
d001cb88:	2600806c 	strcs	r8, [r0], -ip, rrx
d001cb8c:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d001cb90:	f8dfe73e 			; <UNDEFINED> instruction: 0xf8dfe73e
d001cb94:	26018064 	strcs	r8, [r1], -r4, rrx
d001cb98:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d001cb9c:	9b28e738 	blls	0xd0a56884
d001cba0:	24004427 	strcs	r4, [r0], #-1063	; 0xfffffbd9
d001cba4:	0501f003 	streq	pc, [r1, #-3]
d001cba8:	0f00f1ba 	svceq	0x0000f1ba
d001cbac:	af43f43f 	svcge	0x0043f43f
d001cbb0:	f8dfe78f 			; <UNDEFINED> instruction: 0xf8dfe78f
d001cbb4:	46168048 	ldrmi	r8, [r6], -r8, asr #32
d001cbb8:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d001cbbc:	f8dfe728 			; <UNDEFINED> instruction: 0xf8dfe728
d001cbc0:	26008040 	strcs	r8, [r0], -r0, asr #32
d001cbc4:	44f89a03 	ldrbtmi	r9, [r8], #2563	; 0xa03
d001cbc8:	4625e722 	strtmi	lr, [r5], -r2, lsr #14
d001cbcc:	0f00f1ba 	svceq	0x0000f1ba
d001cbd0:	af31f43f 	svcge	0x0031f43f
d001cbd4:	bf00e77d 	svclt	0x0000e77d
d001cbd8:	0000136a 	andeq	r1, r0, sl, ror #6
d001cbdc:	ffffff6e 			; <UNDEFINED> instruction: 0xffffff6e
d001cbe0:	000012d8 	ldrdeq	r1, [r0], -r8
d001cbe4:	fffffe9e 			; <UNDEFINED> instruction: 0xfffffe9e
d001cbe8:	fffffdae 			; <UNDEFINED> instruction: 0xfffffdae
d001cbec:	fffffd8a 			; <UNDEFINED> instruction: 0xfffffd8a
d001cbf0:	fffffd3c 			; <UNDEFINED> instruction: 0xfffffd3c
d001cbf4:	fffffd1e 			; <UNDEFINED> instruction: 0xfffffd1e
d001cbf8:	fffffd1a 			; <UNDEFINED> instruction: 0xfffffd1a
d001cbfc:	fffffcfe 			; <UNDEFINED> instruction: 0xfffffcfe
d001cc00:	fffffce6 			; <UNDEFINED> instruction: 0xfffffce6

Disassembly of section .text.sb_float:

d001cc1c <.text.sb_float>:
d001cc1c:	4ff0e92d 	svcmi	0x00f0e92d
d001cc20:	bb10ec5c 	bllt	0xd0457d98
d001cc24:	461eb0df 			; <UNDEFINED> instruction: 0x461eb0df
d001cc28:	73dcea5f 	bicsvc	lr, ip, #389120	; 0x5f000
d001cc2c:	460446e0 	strmi	r4, [r4], -r0, ror #13
d001cc30:	4615468a 	ldrmi	r4, [r5], -sl, lsl #13
d001cc34:	9a10ee10 	bls	0xd045847c
d001cc38:	ed8d9304 	stc	3, cr9, [sp, #16]
d001cc3c:	d10a0b00 	tstle	sl, r0, lsl #22
d001cc40:	f1000750 			; <UNDEFINED> instruction: 0xf1000750
d001cc44:	009380cb 	addseq	r8, r3, fp, asr #1
d001cc48:	1740f3c3 	strbne	pc, [r0, -r3, asr #7]	; <UNPREDICTABLE>
d001cc4c:	0320f003 	wfieq
d001cc50:	930346bb 	movwls	r4, #14011	; 0x36bb
d001cc54:	2701e003 	strcs	lr, [r1, -r3]
d001cc58:	46bb232d 	ldrtmi	r2, [fp], sp, lsr #6
d001cc5c:	f04f9303 			; <UNDEFINED> instruction: 0xf04f9303
d001cc60:	21000c00 	tstcs	r0, r0, lsl #24
d001cc64:	70fff240 	rscsvc	pc, pc, r0, asr #4
d001cc68:	520af3c8 	andpl	pc, sl, #200, 6	; 0x20000003
d001cc6c:	f1aa458c 			; <UNDEFINED> instruction: 0xf1aa458c
d001cc70:	bf080e41 	svclt	0x00080e41
d001cc74:	fa5f4282 	blx	0xd17ed684
d001cc78:	d03efe8e 	eorsle	pc, lr, lr, lsl #29
d001cc7c:	2b099b68 	blcs	0xd0283a24
d001cc80:	4afcdd4b 	bmi	0xcff541b4
d001cc84:	0918f10d 	ldmdbeq	r8, {r0, r2, r3, r8, ip, sp, lr, pc}
d001cc88:	237046e0 	cmncs	r0, #224, 12	; 0xe000000
d001cc8c:	4649447a 			; <UNDEFINED> instruction: 0x4649447a
d001cc90:	3201203c 	andcc	r2, r1, #60	; 0x3c
d001cc94:	4618e002 	ldrmi	lr, [r8], -r2
d001cc98:	3f01f812 	svccc	0x0001f812
d001cc9c:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d001cca0:	0b01f801 	bleq	0xd009acac
d001cca4:	d1f62b00 	mvnsle	r2, r0, lsl #22
d001cca8:	020beb08 	andeq	lr, fp, #8, 22	; 0x2000
d001ccac:	42b22301 	adcsmi	r2, r2, #67108864	; 0x4000000
d001ccb0:	8099f0c0 	addshi	pc, r9, r0, asr #1
d001ccb4:	f0052600 			; <UNDEFINED> instruction: 0xf0052600
d001ccb8:	2a020203 	bcs	0xd009d4cc
d001ccbc:	2b00d102 	blcs	0xd00510cc
d001ccc0:	8093f040 	addshi	pc, r3, r0, asr #32
d001ccc4:	0501f015 	streq	pc, [r1, #-21]	; 0xffffffeb
d001ccc8:	80bcf040 	adcshi	pc, ip, r0, asr #32
d001cccc:	b1361e75 	teqlt	r6, r5, ror lr
d001ccd0:	21203d01 			; <UNDEFINED> instruction: 0x21203d01
d001ccd4:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d001ccd8:	1c69fdc3 	stclne	13, cr15, [r9], #-780	; 0xfffffcf4
d001ccdc:	2f00d1f8 	svccs	0x0000d1f8
d001cce0:	8091f000 	addshi	pc, r1, r0
d001cce4:	46209903 	strtmi	r9, [r0], -r3, lsl #18
d001cce8:	fdbaf7ff 	ldc2	7, cr15, [sl, #1020]!	; 0x3fc
d001ccec:	0f00f1b8 	svceq	0x0000f1b8
d001ccf0:	808df040 	addhi	pc, sp, r0, asr #32
d001ccf4:	e8bdb05f 	pop	{r0, r1, r2, r3, r4, r6, ip, sp, pc}
d001ccf8:	464a8ff0 			; <UNDEFINED> instruction: 0x464a8ff0
d001ccfc:	0313f3c8 	tsteq	r3, #200, 6	; 0x20000003	; <UNPREDICTABLE>
d001cd00:	f0404313 			; <UNDEFINED> instruction: 0xf0404313
d001cd04:	f1be80ae 			; <UNDEFINED> instruction: 0xf1be80ae
d001cd08:	f2000f19 	vrecps.f32	d0, d0, d9
d001cd0c:	f8df80d4 			; <UNDEFINED> instruction: 0xf8df80d4
d001cd10:	234ec368 	movtcs	ip, #58216	; 0xe368
d001cd14:	44fc2149 	ldrbtmi	r2, [ip], #329	; 0x149
d001cd18:	9b04e0ab 	blls	0xd0154fcc
d001cd1c:	ed9db12b 	ldfd	f3, [sp, #172]	; 0xac
d001cd20:	eeb17b00 	vmov.f64	d7, #16	; 0x40800000  4.0
d001cd24:	ed8d7b47 	vstr	d7, [sp, #284]	; 0x11c
d001cd28:	f1be7b00 			; <UNDEFINED> instruction: 0xf1be7b00
d001cd2c:	f00a0f19 			; <UNDEFINED> instruction: 0xf00a0f19
d001cd30:	bf8c0adf 	svclt	0x008c0adf
d001cd34:	23012300 	movwcs	r2, #4864	; 0x1300
d001cd38:	9b689304 	blls	0xd1a41950
d001cd3c:	f2c02b00 	vqdmlsl.s<illegal width 8>	q9, d0, d0
d001cd40:	f1ba80c5 			; <UNDEFINED> instruction: 0xf1ba80c5
d001cd44:	f0400f47 			; <UNDEFINED> instruction: 0xf0400f47
d001cd48:	9b6880c7 	blls	0xd1a3d06c
d001cd4c:	bf082b00 	svclt	0x00082b00
d001cd50:	93682301 	cmnls	r8, #67108864	; 0x4000000
d001cd54:	7b00ed9d 	blvc	0xd00583d0
d001cd58:	7b40eeb5 	blvc	0xd1058834
d001cd5c:	fa10eef1 	blx	0xd0458928
d001cd60:	80d0f000 	sbcshi	pc, r0, r0
d001cd64:	6b04eeb2 	blvs	0xd0158834
d001cd68:	7bc6eeb4 	blvc	0xcf1d8840
d001cd6c:	fa10eef1 	blx	0xd0458938
d001cd70:	8170f2c0 	cmnhi	r0, r0, asr #5	; <UNPREDICTABLE>
d001cd74:	0a00f04f 	beq	0xd0058eb8
d001cd78:	f5bae003 			; <UNDEFINED> instruction: 0xf5bae003
d001cd7c:	f0007f9a 			; <UNDEFINED> instruction: 0xf0007f9a
d001cd80:	ee87810f 	sins	f0, #10.0
d001cd84:	f10a7b06 			; <UNDEFINED> instruction: 0xf10a7b06
d001cd88:	eeb40a01 	vmov.f32	s0, #65	; 0x3e080000  0.1328125
d001cd8c:	eef17bc6 	vsqrt.f64	d23, d6
d001cd90:	daf2fa10 	ble	0xcfcdb5d8
d001cd94:	6b00eeb7 	blvs	0xd0058878
d001cd98:	7bc6eeb4 	blvc	0xcf1d8870
d001cd9c:	fa10eef1 	blx	0xd0458968
d001cda0:	eeb2d511 	mrc	5, 5, sp, cr2, cr1, {0}
d001cda4:	eeb75b04 	vmov.f64	d5, #116	; 0x3fa00000  1.250
d001cda8:	e0036b00 	and	r6, r3, r0, lsl #22
d001cdac:	7fa2f51a 	svcvc	0x00a2f51a
d001cdb0:	80fef000 	rscshi	pc, lr, r0
d001cdb4:	7b05ee27 	blvc	0xd0198658
d001cdb8:	3afff10a 	bcc	0xd00191e8
d001cdbc:	7bc6eeb4 	blvc	0xcf1d8894
d001cdc0:	fa10eef1 	blx	0xd045898c
d001cdc4:	9b68d4f2 	blls	0xd1a52194
d001cdc8:	f3404553 	vqrshl.u8	q10, <illegal reg q1.5>, q0
d001cdcc:	f11a80f1 			; <UNDEFINED> instruction: 0xf11a80f1
d001cdd0:	f2c00f04 			; <UNDEFINED> instruction: 0xf2c00f04
d001cdd4:	f10a80ed 			; <UNDEFINED> instruction: 0xf10a80ed
d001cdd8:	e0960101 	adds	r0, r6, r1, lsl #2
d001cddc:	232b2701 			; <UNDEFINED> instruction: 0x232b2701
d001cde0:	930346bb 	movwls	r4, #14011	; 0x36bb
d001cde4:	1ab6e73b 	bne	0xcedd6ad8
d001cde8:	f005e765 			; <UNDEFINED> instruction: 0xf005e765
d001cdec:	2f000501 	svccs	0x00000501
d001cdf0:	bb8dd167 	bllt	0xce391394
d001cdf4:	b1361e75 	teqlt	r6, r5, ror lr
d001cdf8:	21303d01 	teqcs	r0, r1, lsl #26
d001cdfc:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d001ce00:	1c6afd2f 	stclne	13, cr15, [sl], #-188	; 0xffffff44
d001ce04:	f1b8d1f8 			; <UNDEFINED> instruction: 0xf1b8d1f8
d001ce08:	f43f0f00 			; <UNDEFINED> instruction: 0xf43f0f00
d001ce0c:	2500af73 	strcs	sl, [r0, #-3955]	; 0xfffff08d
d001ce10:	37012700 	strcc	r2, [r1, -r0, lsl #14]
d001ce14:	1b01f819 	blne	0xd009ae80
d001ce18:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d001ce1c:	4547fd21 	strbmi	pc, [r7, #-3361]	; 0xfffff2df	; <UNPREDICTABLE>
d001ce20:	2d00d3f7 	stccs	3, cr13, [r0, #-988]	; 0xfffffc24
d001ce24:	af66f43f 	svcge	0x0066f43f
d001ce28:	2e001e75 	mcrcs	14, 0, r1, cr0, cr5, {3}
d001ce2c:	af62f43f 	svcge	0x0062f43f
d001ce30:	21203d01 			; <UNDEFINED> instruction: 0x21203d01
d001ce34:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d001ce38:	1c6bfd13 	stclne	13, cr15, [fp], #-76	; 0xffffffb4
d001ce3c:	b05fd1f8 	ldrshlt	sp, [pc], #-24	; <UNPREDICTABLE>
d001ce40:	8ff0e8bd 	svchi	0x00f0e8bd
d001ce44:	f1b8b927 			; <UNDEFINED> instruction: 0xf1b8b927
d001ce48:	d1e10f00 	mvnle	r0, r0, lsl #30
d001ce4c:	461ee7ec 	ldrmi	lr, [lr], -ip, ror #15
d001ce50:	46209903 	strtmi	r9, [r0], -r3, lsl #18
d001ce54:	fd04f7ff 	stc2	7, cr15, [r4, #-1020]	; 0xfffffc04
d001ce58:	0f00f1b8 	svceq	0x0000f1b8
d001ce5c:	2501d0e4 	strcs	sp, [r1, #-228]	; 0xffffff1c
d001ce60:	f1bee7d6 			; <UNDEFINED> instruction: 0xf1bee7d6
d001ce64:	d9470f19 	stmdble	r7, {r0, r3, r4, r8, r9, sl, fp}^
d001ce68:	c210f8df 	andsgt	pc, r0, #14614528	; 0xdf0000
d001ce6c:	216e2361 	cmncs	lr, r1, ror #6
d001ce70:	f10d44fc 			; <UNDEFINED> instruction: 0xf10d44fc
d001ce74:	f10c0918 			; <UNDEFINED> instruction: 0xf10c0918
d001ce78:	ea6f0202 	b	0xd1bdd688
d001ce7c:	46480c0c 	strbmi	r0, [r8], -ip, lsl #24
d001ce80:	f812e001 			; <UNDEFINED> instruction: 0xf812e001
d001ce84:	f8003b01 			; <UNDEFINED> instruction: 0xf8003b01
d001ce88:	eb0c1b01 	bl	0xd0323a94
d001ce8c:	46190802 	ldrmi	r0, [r9], -r2, lsl #16
d001ce90:	d1f62b00 	mvnsle	r2, r0, lsl #22
d001ce94:	020beb08 	andeq	lr, fp, #8, 22	; 0x2000
d001ce98:	d8a44296 	stmiale	r4!, {r1, r2, r4, r7, r9, lr}
d001ce9c:	0601f015 			; <UNDEFINED> instruction: 0x0601f015
d001cea0:	af1df43f 	svcge	0x001df43f
d001cea4:	d1d22f00 	bicsle	r2, r2, r0, lsl #30
d001cea8:	0f00f1b8 	svceq	0x0000f1b8
d001ceac:	af22f43f 	svcge	0x0022f43f
d001ceb0:	463e4635 			; <UNDEFINED> instruction: 0x463e4635
d001ceb4:	f8dfe7ac 			; <UNDEFINED> instruction: 0xf8dfe7ac
d001ceb8:	236ec1c8 	cmncs	lr, #200, 2	; 0x32
d001cebc:	44fc2169 	ldrbtmi	r2, [ip], #361	; 0x169
d001cec0:	9903e7d7 	stmdbls	r3, {r0, r1, r2, r4, r6, r7, r8, r9, sl, sp, lr, pc}
d001cec4:	f7ff4620 			; <UNDEFINED> instruction: 0xf7ff4620
d001cec8:	e792fccb 	ldr	pc, [r2, fp, asr #25]
d001cecc:	f1ba2306 			; <UNDEFINED> instruction: 0xf1ba2306
d001ced0:	93680f47 	cmnls	r8, #284	; 0x11c
d001ced4:	af3ef43f 	svcge	0x003ef43f
d001ced8:	0f45f1ba 	svceq	0x0045f1ba
d001cedc:	0918f10d 	ldmdbeq	r8, {r0, r2, r3, r8, ip, sp, lr, pc}
d001cee0:	9b04d154 	blls	0xd0151438
d001cee4:	0210f005 	andseq	pc, r0, #5
d001cee8:	46489968 	strbmi	r9, [r8], -r8, ror #18
d001ceec:	0b00ed9d 	bleq	0xd0058568
d001cef0:	fbb6f7ff 	blx	0xceddaef6
d001cef4:	e6d74680 	ldrb	r4, [r7], r0, lsl #13
d001cef8:	c188f8df 	ldrdgt	pc, [r8, pc]
d001cefc:	214e2341 	cmpcs	lr, r1, asr #6
d001cf00:	e7b644fc 			; <UNDEFINED> instruction: 0xe7b644fc
d001cf04:	f04f2101 			; <UNDEFINED> instruction: 0xf04f2101
d001cf08:	9b680a00 	blls	0xd1a1f710
d001cf0c:	0918f10d 	ldmdbeq	r8, {r0, r2, r3, r8, ip, sp, lr, pc}
d001cf10:	0210f005 	andseq	pc, r0, #5
d001cf14:	46481a59 			; <UNDEFINED> instruction: 0x46481a59
d001cf18:	ed9d9205 	lfm	f1, 1, [sp, #20]
d001cf1c:	f7ff0b00 			; <UNDEFINED> instruction: 0xf7ff0b00
d001cf20:	4680fad7 	pkhtbmi	pc, r0, r7, asr #21	; <UNPREDICTABLE>
d001cf24:	f43f2800 			; <UNDEFINED> instruction: 0xf43f2800
d001cf28:	4649aebf 			; <UNDEFINED> instruction: 0x4649aebf
d001cf2c:	9a052300 	bls	0xd0165b34
d001cf30:	3301e003 	movwcc	lr, #4099	; 0x1003
d001cf34:	f0004598 			; <UNDEFINED> instruction: 0xf0004598
d001cf38:	f8118086 			; <UNDEFINED> instruction: 0xf8118086
d001cf3c:	282e0b01 	stmdacs	lr!, {r0, r8, r9, fp}
d001cf40:	f1bad1f7 			; <UNDEFINED> instruction: 0xf1bad1f7
d001cf44:	db020f00 	blle	0xd00a0b4c
d001cf48:	42999968 	addsmi	r9, r9, #104, 18	; 0x1a0000
d001cf4c:	2a00d334 	bcs	0xd0051c24
d001cf50:	aeaaf47f 	mcrge	4, 5, pc, cr10, cr15, {3}	; <UNPREDICTABLE>
d001cf54:	e002464b 	and	r4, r2, fp, asr #12
d001cf58:	f43f4590 			; <UNDEFINED> instruction: 0xf43f4590
d001cf5c:	f813aea5 			; <UNDEFINED> instruction: 0xf813aea5
d001cf60:	32011b01 	andcc	r1, r1, #1024	; 0x400
d001cf64:	d1f7292e 	mvnsle	r2, lr, lsr #18
d001cf68:	0308eb09 	movweq	lr, #35593	; 0x8b09
d001cf6c:	f813e005 			; <UNDEFINED> instruction: 0xf813e005
d001cf70:	29301d01 	ldmdbcs	r0!, {r0, r8, sl, fp, ip}
d001cf74:	ae98f47f 	mrcge	4, 4, APSR_nzcv, cr8, cr15, {3}
d001cf78:	45904680 	ldrmi	r4, [r0, #1664]	; 0x680
d001cf7c:	30fff108 	rscscc	pc, pc, r8, lsl #2
d001cf80:	f47fd8f5 			; <UNDEFINED> instruction: 0xf47fd8f5
d001cf84:	f108ae91 			; <UNDEFINED> instruction: 0xf108ae91
d001cf88:	e68d38ff 			; <UNDEFINED> instruction: 0xe68d38ff
d001cf8c:	0b00ed9d 	bleq	0xd0058608
d001cf90:	f0059968 			; <UNDEFINED> instruction: 0xf0059968
d001cf94:	46480210 			; <UNDEFINED> instruction: 0x46480210
d001cf98:	fa9af7ff 	blx	0xce6daf9c
d001cf9c:	e6834680 	str	r4, [r3], r0, lsl #13
d001cfa0:	6b00eeb7 	blvs	0xd0058a84
d001cfa4:	7bc6eeb4 	blvc	0xcf1d8a7c
d001cfa8:	fa10eef1 	blx	0xd0458b74
d001cfac:	aef9f53f 	mrcge	5, 7, APSR_nzcv, cr9, cr15, {1}
d001cfb0:	0210f005 	andseq	pc, r0, #5
d001cfb4:	0918f10d 	ldmdbeq	r8, {r0, r2, r3, r8, ip, sp, lr, pc}
d001cfb8:	46489968 	strbmi	r9, [r8], -r8, ror #18
d001cfbc:	39019b04 	stmdbcc	r1, {r2, r8, r9, fp, ip, pc}
d001cfc0:	ed9d9204 	lfm	f1, 1, [sp, #16]
d001cfc4:	f7ff0b00 			; <UNDEFINED> instruction: 0xf7ff0b00
d001cfc8:	9a04fb4b 	bls	0xd015bcfc
d001cfcc:	2a004680 	bcs	0xd002e9d4
d001cfd0:	ae6af47f 	mcrge	4, 3, pc, cr10, cr15, {3}	; <UNPREDICTABLE>
d001cfd4:	46424448 	strbmi	r4, [r2], -r8, asr #8
d001cfd8:	461ae000 	ldrmi	lr, [sl], -r0
d001cfdc:	2a001e53 	bcs	0xd0024930
d001cfe0:	ae62f43f 	mcrge	4, 3, pc, cr2, cr15, {1}	; <UNPREDICTABLE>
d001cfe4:	1d01f810 	stcne	8, cr15, [r1, #-64]	; 0xffffffc0
d001cfe8:	0cdff001 	ldcleq	0, cr15, [pc], {1}
d001cfec:	0f45f1bc 	svceq	0x0045f1bc
d001cff0:	eb09d1f3 	bl	0xd02917c4
d001cff4:	46180c03 	ldrmi	r0, [r8], -r3, lsl #24
d001cff8:	f81ce005 			; <UNDEFINED> instruction: 0xf81ce005
d001cffc:	f1baad01 			; <UNDEFINED> instruction: 0xf1baad01
d001d000:	d1220f30 			; <UNDEFINED> instruction: 0xd1220f30
d001d004:	f1004670 			; <UNDEFINED> instruction: 0xf1004670
d001d008:	28003eff 	stmdacs	r0, {r0, r1, r2, r3, r4, r5, r6, r7, r9, sl, fp, ip, sp}
d001d00c:	4543d1f5 	strbmi	sp, [r3, #-501]	; 0xfffffe0b
d001d010:	f1c2d212 			; <UNDEFINED> instruction: 0xf1c2d212
d001d014:	eb090a01 	bl	0xd025f820
d001d018:	f10d0c03 			; <UNDEFINED> instruction: 0xf10d0c03
d001d01c:	44820e17 	strmi	r0, [r2], #3607	; 0xe17
d001d020:	445344c6 	ldrbmi	r4, [r3], #-1222	; 0xfffffb3a
d001d024:	3b0144d6 	blcc	0xd006e384
d001d028:	e001444b 	and	r4, r1, fp, asr #8
d001d02c:	1f01f81c 	svcne	0x0001f81c
d001d030:	1f01f803 	svcne	0x0001f803
d001d034:	d1f94573 	mvnsle	r4, r3, ror r5
d001d038:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d001d03c:	0202eba8 	andeq	lr, r2, #168, 22	; 0x2a000
d001d040:	0802eb00 	stmdaeq	r2, {r8, r9, fp, sp, lr, pc}
d001d044:	4643e630 			; <UNDEFINED> instruction: 0x4643e630
d001d048:	f1bae77b 			; <UNDEFINED> instruction: 0xf1bae77b
d001d04c:	bf080f2e 	svclt	0x00080f2e
d001d050:	e7dc4670 			; <UNDEFINED> instruction: 0xe7dc4670
d001d054:	7b00eeb7 	blvc	0xd0058b38
d001d058:	6b00ed9d 	blvs	0xd00586d4
d001d05c:	6bc7eeb4 	blvs	0xcf218b34
d001d060:	fa10eef1 	blx	0xd0458c2c
d001d064:	af4ef57f 	svcge	0x004ef57f
d001d068:	0a00f04f 	beq	0xd00591ac
d001d06c:	7b00ed9d 	blvc	0xd00586e8
d001d070:	bf00e697 	svclt	0x0000e697
d001d074:	ffffff84 			; <UNDEFINED> instruction: 0xffffff84
d001d078:	fffffeee 			; <UNDEFINED> instruction: 0xfffffeee
d001d07c:	fffffd90 			; <UNDEFINED> instruction: 0xfffffd90
d001d080:	fffffd4e 			; <UNDEFINED> instruction: 0xfffffd4e
d001d084:	fffffd08 			; <UNDEFINED> instruction: 0xfffffd08

Disassembly of section .text.sb_format.part.0:

d001d0b8 <.text.sb_format.part.0>:
d001d0b8:	4ff0e92d 	svcmi	0x00f0e92d
d001d0bc:	78094688 	stmdavc	r9, {r3, r7, r9, sl, lr}
d001d0c0:	4683b0a7 	strmi	fp, [r3], r7, lsr #1
d001d0c4:	f0002900 			; <UNDEFINED> instruction: 0xf0002900
d001d0c8:	4bfa80b3 	blmi	0xcfebd39c
d001d0cc:	f8df4691 			; <UNDEFINED> instruction: 0xf8df4691
d001d0d0:	447ba3e8 	ldrbtmi	sl, [fp], #-1000	; 0xfffffc18
d001d0d4:	4bf99308 	blmi	0xcfe81cfc
d001d0d8:	9309447b 	movwls	r4, #38011	; 0x947b
d001d0dc:	f0402925 			; <UNDEFINED> instruction: 0xf0402925
d001d0e0:	f89880fd 			; <UNDEFINED> instruction: 0xf89880fd
d001d0e4:	2c254001 	stccs	0, cr4, [r5], #-4
d001d0e8:	80fef000 	rscshi	pc, lr, r0
d001d0ec:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d001d0f0:	f1a42600 			; <UNDEFINED> instruction: 0xf1a42600
d001d0f4:	2b100320 	blcs	0xd041dd7c
d001d0f8:	e8dfd80a 	ldm	pc, {r1, r3, fp, ip, lr, pc}^	; <UNPREDICTABLE>
d001d0fc:	0978f003 	ldmdbeq	r8!, {r0, r1, ip, sp, lr, pc}^
d001d100:	09097509 	stmdbeq	r9, {r0, r3, r8, sl, ip, sp, lr}
d001d104:	09090909 	stmdbeq	r9, {r0, r3, r8, fp}
d001d108:	6f097209 	svcvs	0x00097209
d001d10c:	006a0909 	rsbeq	r0, sl, r9, lsl #18
d001d110:	f0402c2a 			; <UNDEFINED> instruction: 0xf0402c2a
d001d114:	f8d980ef 			; <UNDEFINED> instruction: 0xf8d980ef
d001d118:	f1083000 			; <UNDEFINED> instruction: 0xf1083000
d001d11c:	681d0101 	ldmdavs	sp, {r0, r8}
d001d120:	2d001d1a 	stccs	13, cr1, [r0, #-104]	; 0xffffff98
d001d124:	2000f8c9 	andcs	pc, r0, r9, asr #17
d001d128:	8122f2c0 	smlawthi	r2, r0, r2, pc	; <UNPREDICTABLE>
d001d12c:	5f00f5b5 	svcpl	0x0000f5b5
d001d130:	4001f898 	mulmi	r1, r8, r8
d001d134:	f44fbf28 			; <UNDEFINED> instruction: 0xf44fbf28
d001d138:	2c2e5500 	cfstr32cs	mvfx5, [lr], #-0
d001d13c:	80fbf000 	rscshi	pc, fp, r0
d001d140:	37fff04f 	ldrbcc	pc, [pc, pc, asr #32]!	; <UNPREDICTABLE>
d001d144:	f0002c68 			; <UNDEFINED> instruction: 0xf0002c68
d001d148:	2c6c810d 	stfcsp	f0, [ip], #-52	; 0xffffffcc
d001d14c:	811ef000 	tsthi	lr, r0	; <UNPREDICTABLE>
d001d150:	f0002c7a 			; <UNDEFINED> instruction: 0xf0002c7a
d001d154:	2c748122 	ldfcsp	f0, [r4], #-136	; 0xffffff78
d001d158:	8161f000 	msrhi	SPSR_c, r0
d001d15c:	f0002c6a 			; <UNDEFINED> instruction: 0xf0002c6a
d001d160:	230081b3 	movwcs	r8, #435	; 0x1b3
d001d164:	d0632c00 	rsble	r2, r3, r0, lsl #24
d001d168:	f1012c64 			; <UNDEFINED> instruction: 0xf1012c64
d001d16c:	d07d0801 	rsbsle	r0, sp, r1, lsl #16
d001d170:	d07b2c69 	rsbsle	r2, fp, r9, ror #24
d001d174:	0262f1a4 	rsbeq	pc, r2, #164, 2	; 0x29
d001d178:	01dff004 	bicseq	pc, pc, r4
d001d17c:	f1a1b2d2 			; <UNDEFINED> instruction: 0xf1a1b2d2
d001d180:	2a130c58 	bcs	0xd04e02e8
d001d184:	fc8cfabc 	stc2	10, cr15, [ip], {188}	; 0xbc	; <UNPREDICTABLE>
d001d188:	1c5cea4f 	mrrcne	10, 4, lr, ip, cr15
d001d18c:	48c8d806 	stmiami	r8, {r1, r2, fp, ip, lr, pc}^
d001d190:	f202fa20 	vpmax.s8	d15, d2, d16
d001d194:	0201f002 	andeq	pc, r1, #2
d001d198:	0c02ea4c 			; <UNDEFINED> instruction: 0x0c02ea4c
d001d19c:	0f00f1bc 	svceq	0x0000f1bc
d001d1a0:	816cf000 	msrhi	SPSR_fs, r0
d001d1a4:	f0002c6f 			; <UNDEFINED> instruction: 0xf0002c6f
d001d1a8:	2958811b 	ldmdbcs	r8, {r0, r1, r3, r4, r8, pc}^
d001d1ac:	811af000 	tsthi	sl, r0	; <UNPREDICTABLE>
d001d1b0:	bf0c2c62 	svclt	0x000c2c62
d001d1b4:	210a2102 	tstcs	sl, r2, lsl #2
d001d1b8:	2b063b01 	blcs	0xd01abdc4
d001d1bc:	84fdf200 	ldrbthi	pc, [sp], #512	; 0x200	; <UNPREDICTABLE>
d001d1c0:	f013e8df 			; <UNDEFINED> instruction: 0xf013e8df
d001d1c4:	0143014b 	cmpeq	r3, fp, asr #2
d001d1c8:	00480018 	subeq	r0, r8, r8, lsl r0
d001d1cc:	00180018 	andseq	r0, r8, r8, lsl r0
d001d1d0:	f0460048 			; <UNDEFINED> instruction: 0xf0460048
d001d1d4:	f8180602 			; <UNDEFINED> instruction: 0xf8180602
d001d1d8:	e78a4f01 	str	r4, [sl, r1, lsl #30]
d001d1dc:	0601f046 	streq	pc, [r1], -r6, asr #32
d001d1e0:	f046e7f9 			; <UNDEFINED> instruction: 0xf046e7f9
d001d1e4:	e7f60604 	ldrb	r0, [r6, r4, lsl #12]!
d001d1e8:	0610f046 	ldreq	pc, [r0], -r6, asr #32
d001d1ec:	f046e7f3 			; <UNDEFINED> instruction: 0xf046e7f3
d001d1f0:	e7f00608 	ldrb	r0, [r0, r8, lsl #12]!
d001d1f4:	3000f8d9 	ldrdcc	pc, [r0], -r9
d001d1f8:	681a1d18 	ldmdavs	sl, {r3, r4, r8, sl, fp, ip}
d001d1fc:	f8c92300 			; <UNDEFINED> instruction: 0xf8c92300
d001d200:	f1a40000 			; <UNDEFINED> instruction: 0xf1a40000
d001d204:	f0260058 			; <UNDEFINED> instruction: 0xf0260058
d001d208:	2400060c 	strcs	r0, [r0], #-1548	; 0xfffff9f4
d001d20c:	fab09704 	blx	0xcec42e24
d001d210:	9602f080 	strls	pc, [r2], -r0, lsl #1
d001d214:	09409503 	stmdbeq	r0, {r0, r1, r8, sl, ip, pc}^
d001d218:	94069100 	strls	r9, [r6], #-256	; 0xffffff00
d001d21c:	46589005 	ldrbmi	r9, [r8], -r5
d001d220:	f7ff9401 			; <UNDEFINED> instruction: 0xf7ff9401
d001d224:	f898fb4d 			; <UNDEFINED> instruction: 0xf898fb4d
d001d228:	29001000 	stmdbcs	r0, {ip}
d001d22c:	af56f47f 	svcge	0x0056f47f
d001d230:	300cf8db 	ldrdcc	pc, [ip], -fp
d001d234:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d001d238:	465880db 			; <UNDEFINED> instruction: 0x465880db
d001d23c:	fafcf7ff 	blx	0xcff5b240
d001d240:	300cf8db 	ldrdcc	pc, [ip], -fp
d001d244:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d001d248:	f8db80d3 			; <UNDEFINED> instruction: 0xf8db80d3
d001d24c:	b0270008 	eorlt	r0, r7, r8
d001d250:	8ff0e8bd 	svchi	0x00f0e8bd
d001d254:	3000f8d9 	ldrdcc	pc, [r0], -r9
d001d258:	f0233307 			; <UNDEFINED> instruction: 0xf0233307
d001d25c:	f1030307 			; <UNDEFINED> instruction: 0xf1030307
d001d260:	f8c90208 			; <UNDEFINED> instruction: 0xf8c90208
d001d264:	e9d32000 	ldmib	r3, {sp}^
d001d268:	e7ca2300 	strb	r2, [sl, r0, lsl #6]
d001d26c:	2b063b01 	blcs	0xd01abe78
d001d270:	84acf200 	strthi	pc, [ip], #512	; 0x200
d001d274:	f003e8df 			; <UNDEFINED> instruction: 0xf003e8df
d001d278:	1f04d7e0 	svcne	0x0004d7e0
d001d27c:	001f0404 	andseq	r0, pc, r4, lsl #8
d001d280:	3000f8d9 	ldrdcc	pc, [r0], -r9
d001d284:	1d1a6818 	ldcne	8, cr6, [sl, #-96]	; 0xffffffa0
d001d288:	f8c917c1 			; <UNDEFINED> instruction: 0xf8c917c1
d001d28c:	28002000 	stmdacs	r0, {sp}
d001d290:	0300f171 	movweq	pc, #369	; 0x171	; <UNPREDICTABLE>
d001d294:	4602db1e 			; <UNDEFINED> instruction: 0x4602db1e
d001d298:	0fc8460b 	svceq	0x00c8460b
d001d29c:	2100240a 	tstcs	r0, sl, lsl #8
d001d2a0:	90019704 	andls	r9, r1, r4, lsl #14
d001d2a4:	95034658 	strls	r4, [r3, #-1624]	; 0xfffff9a8
d001d2a8:	91069602 	tstls	r6, r2, lsl #12
d001d2ac:	94009105 	strls	r9, [r0], #-261	; 0xfffffefb
d001d2b0:	fb06f7ff 	blx	0xd01db2b6
d001d2b4:	f8d9e7b7 			; <UNDEFINED> instruction: 0xf8d9e7b7
d001d2b8:	33073000 	movwcc	r3, #28672	; 0x7000
d001d2bc:	0307f023 	movweq	pc, #28707	; 0x7023	; <UNPREDICTABLE>
d001d2c0:	0100e9d3 	ldrdeq	lr, [r0, -r3]
d001d2c4:	0208f103 	andeq	pc, r8, #-1073741824	; 0xc0000000
d001d2c8:	f8c92800 			; <UNDEFINED> instruction: 0xf8c92800
d001d2cc:	f1712000 			; <UNDEFINED> instruction: 0xf1712000
d001d2d0:	dae00300 	ble	0xcf81ded8
d001d2d4:	eb614242 	bl	0xd186dbe4
d001d2d8:	e7de0341 	ldrb	r0, [lr, r1, asr #6]
d001d2dc:	f1084658 			; <UNDEFINED> instruction: 0xf1084658
d001d2e0:	f7ff0801 			; <UNDEFINED> instruction: 0xf7ff0801
d001d2e4:	e79efabd 			; <UNDEFINED> instruction: 0xe79efabd
d001d2e8:	f1084658 			; <UNDEFINED> instruction: 0xf1084658
d001d2ec:	f7ff0802 			; <UNDEFINED> instruction: 0xf7ff0802
d001d2f0:	e798fab7 			; <UNDEFINED> instruction: 0xe798fab7
d001d2f4:	0230f1a4 	eorseq	pc, r0, #164, 2	; 0x29
d001d2f8:	2b09b2d3 	blcs	0xd0289e4c
d001d2fc:	80e8f200 	rschi	pc, r8, r0, lsl #4
d001d300:	0801f108 	stmdaeq	r1, {r3, r8, ip, sp, lr, pc}
d001d304:	f5c22500 			; <UNDEFINED> instruction: 0xf5c22500
d001d308:	46415300 	strbmi	r5, [r1], -r0, lsl #6
d001d30c:	0085eb05 	addeq	lr, r5, r5, lsl #22
d001d310:	4303fbaa 	movwmi	pc, #15274	; 0x3baa	; <UNPREDICTABLE>
d001d314:	4b01f818 	blmi	0xd009b37c
d001d318:	0fd3ebb5 	svceq	0x00d3ebb5
d001d31c:	0540eb02 	strbeq	lr, [r0, #-2818]	; 0xfffff4fe
d001d320:	0230f1a4 	eorseq	pc, r0, #164, 2	; 0x29
d001d324:	f44fbf88 			; <UNDEFINED> instruction: 0xf44fbf88
d001d328:	b2d35500 	sbcslt	r5, r3, #0, 10
d001d32c:	d9ea2b09 	stmible	sl!, {r0, r3, r8, r9, fp, sp}^
d001d330:	f47f2c2e 			; <UNDEFINED> instruction: 0xf47f2c2e
d001d334:	784caf05 	stmdavc	ip, {r0, r2, r8, r9, sl, fp, sp, pc}^
d001d338:	d1322c2a 	teqle	r2, sl, lsr #24
d001d33c:	3000f8d9 	ldrdcc	pc, [r0], -r9
d001d340:	681f1c88 	ldmdavs	pc, {r3, r7, sl, fp, ip}	; <UNPREDICTABLE>
d001d344:	2f001d1a 	svccs	0x00001d1a
d001d348:	2000f8c9 	andcs	pc, r0, r9, asr #17
d001d34c:	f2c0788c 	vmlal.s8	<illegal reg q11.5>, d16, d12
d001d350:	f5b78091 			; <UNDEFINED> instruction: 0xf5b78091
d001d354:	46015f00 	strmi	r5, [r1], -r0, lsl #30
d001d358:	f44fbf28 			; <UNDEFINED> instruction: 0xf44fbf28
d001d35c:	2c685700 	stclcs	7, cr5, [r8], #-0
d001d360:	aef3f47f 	mrcge	4, 7, APSR_nzcv, cr3, cr15, {3}
d001d364:	2c68784c 	stclcs	8, cr7, [r8], #-304	; 0xfffffed0
d001d368:	3101d03e 	tstcc	r1, lr, lsr r0
d001d36c:	e6f92302 	ldrbt	r2, [r9], r2, lsl #6
d001d370:	4f00f1b5 	svcmi	0x0000f1b5
d001d374:	0601f046 	streq	pc, [r1], -r6, asr #32
d001d378:	426dd077 	rsbmi	sp, sp, #119	; 0x77
d001d37c:	4001f898 	mulmi	r1, r8, r8
d001d380:	5f00f5b5 	svcpl	0x0000f5b5
d001d384:	f44fbf28 			; <UNDEFINED> instruction: 0xf44fbf28
d001d388:	e6d65500 	ldrb	r5, [r6], r0, lsl #10
d001d38c:	2c6c784c 	stclcs	8, cr7, [ip], #-304	; 0xfffffed0
d001d390:	8096f000 	addshi	pc, r6, r0
d001d394:	23033101 	movwcs	r3, #12545	; 0x3101
d001d398:	784ce6e4 	stmdavc	ip, {r2, r5, r6, r7, r9, sl, sp, lr, pc}^
d001d39c:	31012305 	tstcc	r1, r5, lsl #6
d001d3a0:	f1a4e6e0 			; <UNDEFINED> instruction: 0xf1a4e6e0
d001d3a4:	1c480230 	sfmne	f0, 2, [r8], {48}	; 0x30
d001d3a8:	2b09b2d3 	blcs	0xd0289efc
d001d3ac:	80daf200 	sbcshi	pc, sl, r0, lsl #4
d001d3b0:	27001c88 	strcs	r1, [r0, -r8, lsl #25]
d001d3b4:	5300f5c2 	movwpl	pc, #1474	; 0x5c2	; <UNPREDICTABLE>
d001d3b8:	0487eb07 	streq	lr, [r7], #2823	; 0xb07
d001d3bc:	fbaa4601 	blx	0xceaaebca
d001d3c0:	ebb7c303 	bl	0xcee0dfd4
d001d3c4:	eb020fd3 	bl	0xd00a1318
d001d3c8:	f8100744 			; <UNDEFINED> instruction: 0xf8100744
d001d3cc:	bf884b01 	svclt	0x00884b01
d001d3d0:	5700f44f 	strpl	pc, [r0, -pc, asr #8]
d001d3d4:	0230f1a4 	eorseq	pc, r0, #164, 2	; 0x29
d001d3d8:	2b09b2d3 	blcs	0xd0289f2c
d001d3dc:	e6b1d9ea 	ldrt	sp, [r1], sl, ror #19
d001d3e0:	e6e92108 	strbt	r2, [r9], r8, lsl #2
d001d3e4:	e6e72110 	usat	r2, #7, r0, lsl #2
d001d3e8:	2301788c 	movwcs	r7, #6284	; 0x188c
d001d3ec:	e6b93102 	ldrt	r3, [r9], r2, lsl #2
d001d3f0:	3000f8db 	ldrdcc	pc, [r0], -fp
d001d3f4:	f43f2b00 			; <UNDEFINED> instruction: 0xf43f2b00
d001d3f8:	f8dbaf28 			; <UNDEFINED> instruction: 0xf8dbaf28
d001d3fc:	2a002004 	bcs	0xd0025414
d001d400:	af23f43f 	svcge	0x0023f43f
d001d404:	1008f8db 	ldrdne	pc, [r8], -fp
d001d408:	bf98428a 	svclt	0x0098428a
d001d40c:	31fff102 	mvnscc	pc, r2, lsl #2
d001d410:	545a2200 	ldrbpl	r2, [sl], #-512	; 0xfffffe00
d001d414:	0008f8db 	ldrdeq	pc, [r8], -fp
d001d418:	e8bdb027 	pop	{r0, r1, r2, r5, ip, sp, pc}
d001d41c:	784c8ff0 	stmdavc	ip, {r4, r5, r6, r7, r8, r9, sl, fp, pc}^
d001d420:	31012306 	tstcc	r1, r6, lsl #6
d001d424:	f8d9e69e 			; <UNDEFINED> instruction: 0xf8d9e69e
d001d428:	f9b33000 			; <UNDEFINED> instruction: 0xf9b33000
d001d42c:	1d1a0000 	ldcne	0, cr0, [sl, #-0]
d001d430:	f8c917c1 			; <UNDEFINED> instruction: 0xf8c917c1
d001d434:	e72a2000 	str	r2, [sl, -r0]!
d001d438:	3000f8d9 	ldrdcc	pc, [r0], -r9
d001d43c:	0000f993 	muleq	r0, r3, r9
d001d440:	17c11d1a 	bfine	r1, sl, (invalid: 26:1)
d001d444:	2000f8c9 	andcs	pc, r0, r9, asr #17
d001d448:	f8d9e721 			; <UNDEFINED> instruction: 0xf8d9e721
d001d44c:	1d183000 	ldcne	0, cr3, [r8, #-0]
d001d450:	2300881a 	movwcs	r8, #2074	; 0x81a
d001d454:	0000f8c9 	andeq	pc, r0, r9, asr #17
d001d458:	f8d9e6d3 			; <UNDEFINED> instruction: 0xf8d9e6d3
d001d45c:	1d183000 	ldcne	0, cr3, [r8, #-0]
d001d460:	2300781a 	movwcs	r7, #2074	; 0x81a
d001d464:	0000f8c9 	andeq	pc, r0, r9, asr #17
d001d468:	f898e6cb 			; <UNDEFINED> instruction: 0xf898e6cb
d001d46c:	f44f4001 	vst4.8	{d20-d23}, [pc], r1
d001d470:	e6625500 	strbt	r5, [r2], -r0, lsl #10
d001d474:	37fff04f 	ldrbcc	pc, [pc, pc, asr #32]!	; <UNPREDICTABLE>
d001d478:	e6634601 	strbt	r4, [r3], -r1, lsl #12
d001d47c:	d0592c70 	subsle	r2, r9, r0, ror ip
d001d480:	d0722c73 	rsbsle	r2, r2, r3, ror ip
d001d484:	d0262c63 	eorle	r2, r6, r3, ror #24
d001d488:	0245f1a1 	subeq	pc, r5, #1073741864	; 0x40000028
d001d48c:	d93f2a02 	ldmdble	pc!, {r1, r9, fp, sp}	; <UNPREDICTABLE>
d001d490:	f0002941 			; <UNDEFINED> instruction: 0xf0002941
d001d494:	2c6e80af 	stclcs	0, cr8, [lr], #-700	; 0xfffffd44
d001d498:	8216f000 	andshi	pc, r6, #0
d001d49c:	21254658 			; <UNDEFINED> instruction: 0x21254658
d001d4a0:	f9def7ff 			; <UNDEFINED> instruction: 0xf9def7ff
d001d4a4:	46584621 	ldrbmi	r4, [r8], -r1, lsr #12
d001d4a8:	f9daf7ff 			; <UNDEFINED> instruction: 0xf9daf7ff
d001d4ac:	bf00e6bb 	svclt	0x0000e6bb
d001d4b0:	00082001 	andeq	r2, r8, r1
d001d4b4:	ffffffce 			; <UNDEFINED> instruction: 0xffffffce
d001d4b8:	cccccccd 	stclgt	12, cr12, [ip], {205}	; 0xcd
d001d4bc:	ffffffb4 			; <UNDEFINED> instruction: 0xffffffb4
d001d4c0:	2304788c 	movwcs	r7, #18572	; 0x488c
d001d4c4:	e64d3102 	strb	r3, [sp], -r2, lsl #2
d001d4c8:	2307784c 	movwcs	r7, #30796	; 0x784c
d001d4cc:	e6493101 	strb	r3, [r9], -r1, lsl #2
d001d4d0:	25004641 	strcs	r4, [r0, #-1601]	; 0xfffff9bf
d001d4d4:	2d01e631 	stccs	6, cr14, [r1, #-196]	; 0xffffff3c
d001d4d8:	2501bf38 	strcs	fp, [r1, #-3896]	; 0xfffff0c8
d001d4dc:	f10507f6 			; <UNDEFINED> instruction: 0xf10507f6
d001d4e0:	f14037ff 			; <UNDEFINED> instruction: 0xf14037ff
d001d4e4:	f8d9818b 			; <UNDEFINED> instruction: 0xf8d9818b
d001d4e8:	46583000 	ldrbmi	r3, [r8], -r0
d001d4ec:	1d1a3d02 	ldcne	13, cr3, [sl, #-8]
d001d4f0:	f8c97819 			; <UNDEFINED> instruction: 0xf8c97819
d001d4f4:	f7ff2000 			; <UNDEFINED> instruction: 0xf7ff2000
d001d4f8:	2f00f9b3 	svccs	0x0000f9b3
d001d4fc:	ae93f43f 	mrcge	4, 4, APSR_nzcv, cr3, cr15, {1}
d001d500:	46583d01 	ldrbmi	r3, [r8], -r1, lsl #26
d001d504:	f7ff2120 			; <UNDEFINED> instruction: 0xf7ff2120
d001d508:	1c68f9ab 			; <UNDEFINED> instruction: 0x1c68f9ab
d001d50c:	e68ad1f8 			; <UNDEFINED> instruction: 0xe68ad1f8
d001d510:	0000f8d9 	ldrdeq	pc, [r0], -r9
d001d514:	462b4621 	strtmi	r4, [fp], -r1, lsr #12
d001d518:	1dc44632 	stclne	6, cr4, [r4, #200]	; 0xc8
d001d51c:	f0244658 			; <UNDEFINED> instruction: 0xf0244658
d001d520:	ed940407 	cfldrs	mvf0, [r4, #28]
d001d524:	34080b00 	strcc	r0, [r8], #-2816	; 0xfffff500
d001d528:	f8c99700 			; <UNDEFINED> instruction: 0xf8c99700
d001d52c:	f7ff4000 			; <UNDEFINED> instruction: 0xf7ff4000
d001d530:	e678fb75 			; <UNDEFINED> instruction: 0xe678fb75
d001d534:	3000f8d9 	ldrdcc	pc, [r0], -r9
d001d538:	060cf026 	streq	pc, [ip], -r6, lsr #32
d001d53c:	21102401 	tstcs	r0, r1, lsl #8
d001d540:	46581d1a 			; <UNDEFINED> instruction: 0x46581d1a
d001d544:	2000f8c9 	andcs	pc, r0, r9, asr #17
d001d548:	4663681a 			; <UNDEFINED> instruction: 0x4663681a
d001d54c:	f8cd9602 			; <UNDEFINED> instruction: 0xf8cd9602
d001d550:	9704c014 	smladls	r4, r4, r0, ip
d001d554:	f8cd9503 			; <UNDEFINED> instruction: 0xf8cd9503
d001d558:	9406c004 	strls	ip, [r6], #-4
d001d55c:	f7ff9100 			; <UNDEFINED> instruction: 0xf7ff9100
d001d560:	e660f9af 	strbt	pc, [r0], -pc, lsr #19	; <UNPREDICTABLE>
d001d564:	27004601 	strcs	r4, [r0, -r1, lsl #12]
d001d568:	f8d9e5ec 			; <UNDEFINED> instruction: 0xf8d9e5ec
d001d56c:	1d1a3000 	ldcne	0, cr3, [sl, #-0]
d001d570:	2000f8c9 	andcs	pc, r0, r9, asr #17
d001d574:	9314681b 	tstls	r4, #1769472	; 0x1b0000
d001d578:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d001d57c:	781b813b 	ldmdavc	fp, {r0, r1, r3, r4, r5, r8, pc}
d001d580:	f0002b00 			; <UNDEFINED> instruction: 0xf0002b00
d001d584:	0ff88197 	svceq	0x00f88197
d001d588:	f0002f00 			; <UNDEFINED> instruction: 0xf0002f00
d001d58c:	9a148193 	bls	0xd053dbe0
d001d590:	f8122400 			; <UNDEFINED> instruction: 0xf8122400
d001d594:	34013f01 	strcc	r3, [r1], #-3841	; 0xfffff0ff
d001d598:	42bcb11b 	adcsmi	fp, ip, #-1073741818	; 0xc0000006
d001d59c:	2800d3f9 	stmdacs	r0, {r0, r3, r4, r5, r6, r7, r8, r9, ip, lr, pc}
d001d5a0:	42a5d1f7 	adcmi	sp, r5, #-1073741763	; 0xc000003d
d001d5a4:	813df200 	teqhi	sp, r0, lsl #4	; <UNPREDICTABLE>
d001d5a8:	0301f016 	movweq	pc, #4118	; 0x1016	; <UNPREDICTABLE>
d001d5ac:	f0009312 			; <UNDEFINED> instruction: 0xf0009312
d001d5b0:	25008189 	strcs	r8, [r0, #-393]	; 0xfffffe77
d001d5b4:	95149b14 	ldrls	r9, [r4, #-2836]	; 0xfffff4ec
d001d5b8:	1e5e4625 	cdpne	6, 5, cr4, cr14, cr5, {1}
d001d5bc:	4637461c 			; <UNDEFINED> instruction: 0x4637461c
d001d5c0:	f8164658 			; <UNDEFINED> instruction: 0xf8164658
d001d5c4:	f7ff1f01 			; <UNDEFINED> instruction: 0xf7ff1f01
d001d5c8:	1cbbf94b 			; <UNDEFINED> instruction: 0x1cbbf94b
d001d5cc:	429d1b1b 	addsmi	r1, sp, #27648	; 0x6c00
d001d5d0:	9b12d8f5 	blls	0xd04d39ac
d001d5d4:	2b009d14 	blcs	0xd0044a2c
d001d5d8:	ae25f43f 	mcrge	4, 1, pc, cr5, cr15, {1}	; <UNPREDICTABLE>
d001d5dc:	2d001e6c 	stccs	14, cr1, [r0, #-432]	; 0xfffffe50
d001d5e0:	ae21f43f 	mcrge	4, 1, pc, cr1, cr15, {1}	; <UNPREDICTABLE>
d001d5e4:	21203c01 			; <UNDEFINED> instruction: 0x21203c01
d001d5e8:	f7ff4658 			; <UNDEFINED> instruction: 0xf7ff4658
d001d5ec:	1c67f939 			; <UNDEFINED> instruction: 0x1c67f939
d001d5f0:	e618d1f8 			; <UNDEFINED> instruction: 0xe618d1f8
d001d5f4:	3000f8d9 	ldrdcc	pc, [r0], -r9
d001d5f8:	f0233307 			; <UNDEFINED> instruction: 0xf0233307
d001d5fc:	ed930307 	ldc	3, cr0, [r3, #28]
d001d600:	33087b00 	movwcc	r7, #35584	; 0x8b00
d001d604:	0b17ec51 	bleq	0xd0618750
d001d608:	3000f8c9 	andcc	pc, r0, r9, asr #17
d001d60c:	ee17460b 	cfmsub32	mvax0, mvfx4, mvfx7, mvfx11
d001d610:	2b002a10 	blcs	0xd0027e58
d001d614:	7b12ed8d 	blvc	0xd04d8c50
d001d618:	8176f2c0 	cmnhi	r6, r0, asr #5	; <UNPREDICTABLE>
d001d61c:	f1000771 			; <UNDEFINED> instruction: 0xf1000771
d001d620:	00b18176 	adcseq	r8, r1, r6, ror r1
d001d624:	0120f001 	msreq	CPSR_, r1
d001d628:	f3c39114 	vorr.i32	d25, #180	; 0x000000b4
d001d62c:	920c510a 	andls	r5, ip, #-2147483646	; 0x80000002
d001d630:	72fff240 	rscsvc	pc, pc, #64, 4
d001d634:	0313f3c3 	tsteq	r3, #201326595	; 0xc000003	; <UNPREDICTABLE>
d001d638:	42919116 	addsmi	r9, r1, #-2147483643	; 0x80000005
d001d63c:	f000930d 			; <UNDEFINED> instruction: 0xf000930d
d001d640:	9b16817c 	blls	0xd05bdc38
d001d644:	bf142b00 	svclt	0x00142b00
d001d648:	22002201 	andcs	r2, r0, #268435456	; 0x10000000
d001d64c:	f0009217 			; <UNDEFINED> instruction: 0xf0009217
d001d650:	f2a38161 	vmla.f32	d8, d3, d1[1]
d001d654:	2b0033ff 	blcs	0xd002a658
d001d658:	bfb8931a 	svclt	0x00b8931a
d001d65c:	9312425b 	tstls	r2, #-1342177275	; 0xb0000005
d001d660:	f0001c78 			; <UNDEFINED> instruction: 0xf0001c78
d001d664:	f5b7818a 			; <UNDEFINED> instruction: 0xf5b7818a
d001d668:	f3405f00 	vpmax.f32	d21, d0, d0
d001d66c:	f44f817d 	vst4.16	{d24,d26,d28,d30}, [pc :256]!
d001d670:	e9dd5700 	ldmib	sp, {r8, r9, sl, ip, lr}^
d001d674:	9715230c 	ldrls	r2, [r5, -ip, lsl #6]
d001d678:	230ae9cd 	movwcs	lr, #43469	; 0xa9cd
d001d67c:	2100ab22 	tstcs	r0, r2, lsr #22
d001d680:	ee079a12 			; <UNDEFINED> instruction: 0xee079a12
d001d684:	4618ba90 			; <UNDEFINED> instruction: 0x4618ba90
d001d688:	fbaa9321 	blx	0xceac2316
d001d68c:	4694c302 	ldrmi	ip, [r4], r2, lsl #6
d001d690:	3101468e 	smlabbcc	r1, lr, r6, r4
d001d694:	0bd3ea4f 	bleq	0xcf517fd8
d001d698:	0f09f1bc 	svceq	0x0009f1bc
d001d69c:	038beb0b 	orreq	lr, fp, #11264	; 0x2c00
d001d6a0:	0343eba2 	movteq	lr, #15266	; 0x3ba2
d001d6a4:	f103465a 			; <UNDEFINED> instruction: 0xf103465a
d001d6a8:	b2db0330 	sbcslt	r0, fp, #48, 6	; 0xc0000000
d001d6ac:	3b01f800 	blcc	0xd009b6b4
d001d6b0:	ee17d8eb 	cdp	8, 1, cr13, cr7, cr11, {7}
d001d6b4:	931fba90 	tstls	pc, #144, 20	; 0x90000
d001d6b8:	e080f8cd 	add	pc, r0, sp, asr #17
d001d6bc:	f0002f00 			; <UNDEFINED> instruction: 0xf0002f00
d001d6c0:	f00681bd 			; <UNDEFINED> instruction: 0xf00681bd
d001d6c4:	22040310 	andcs	r0, r4, #16, 6	; 0x40000000
d001d6c8:	9b14931b 	blls	0xd054233c
d001d6cc:	3b009815 	blcc	0xd0043728
d001d6d0:	2301bf18 	movwcs	fp, #7960	; 0x1f18
d001d6d4:	44033302 	strmi	r3, [r3], #-770	; 0xfffffcfe
d001d6d8:	4413440b 	ldrmi	r4, [r3], #-1035	; 0xfffffbf5
d001d6dc:	f240429d 	vqsub.s8	d20, d16, d13
d001d6e0:	f00681b9 			; <UNDEFINED> instruction: 0xf00681b9
d001d6e4:	f0060101 			; <UNDEFINED> instruction: 0xf0060101
d001d6e8:	1aea0003 	bne	0xcfa9d6fc
d001d6ec:	0301f081 	movweq	pc, #4225	; 0x1081	; <UNPREDICTABLE>
d001d6f0:	901e9116 	andsls	r9, lr, r6, lsl r1
d001d6f4:	bf0c2802 	svclt	0x000c2802
d001d6f8:	f0032600 			; <UNDEFINED> instruction: 0xf0032600
d001d6fc:	92120601 	andsls	r0, r2, #1048576	; 0x100000
d001d700:	f0002e00 			; <UNDEFINED> instruction: 0xf0002e00
d001d704:	1e5581a5 	lognedp	f0, f5
d001d708:	f0002a00 			; <UNDEFINED> instruction: 0xf0002a00
d001d70c:	3d0181b0 	stfccd	f0, [r1, #-704]	; 0xfffffd40
d001d710:	46582120 	ldrbmi	r2, [r8], -r0, lsr #2
d001d714:	f8a4f7ff 			; <UNDEFINED> instruction: 0xf8a4f7ff
d001d718:	d1f81c69 	mvnsle	r1, r9, ror #24
d001d71c:	93162300 	tstls	r6, #0, 6
d001d720:	2b009b14 	blcs	0xd0044378
d001d724:	8185f040 	orrhi	pc, r5, r0, asr #32
d001d728:	46582130 			; <UNDEFINED> instruction: 0x46582130
d001d72c:	f898f7ff 			; <UNDEFINED> instruction: 0xf898f7ff
d001d730:	46582c41 	ldrbmi	r2, [r8], -r1, asr #24
d001d734:	2158bf0c 	cmpcs	r8, ip, lsl #30
d001d738:	f7ff2178 			; <UNDEFINED> instruction: 0xf7ff2178
d001d73c:	9b1ef891 	blls	0xd07db988
d001d740:	d1022b02 	tstle	r2, r2, lsl #22
d001d744:	f0402e00 			; <UNDEFINED> instruction: 0xf0402e00
d001d748:	99178195 	ldmdbls	r7, {r0, r2, r4, r7, r8, pc}
d001d74c:	31304658 	teqcc	r0, r8, asr r6
d001d750:	f7ffb2c9 			; <UNDEFINED> instruction: 0xf7ffb2c9
d001d754:	9b15f885 	blls	0xd059b970
d001d758:	43139a1b 	tstmi	r3, #110592	; 0x1b000
d001d75c:	212ed003 			; <UNDEFINED> instruction: 0x212ed003
d001d760:	f7ff4658 			; <UNDEFINED> instruction: 0xf7ff4658
d001d764:	2c41f87d 	mcrrcs	8, 7, pc, r1, cr13	; <UNPREDICTABLE>
d001d768:	816ff000 	msrhi	SPSR_fsxc, r0
d001d76c:	f0002f00 			; <UNDEFINED> instruction: 0xf0002f00
d001d770:	9e08821f 	mcrls	2, 0, r8, cr8, cr15, {0}
d001d774:	250000bb 	strcs	r0, [r0, #-187]	; 0xffffff45
d001d778:	3b049415 	blcc	0xd01427d4
d001d77c:	e0069314 	and	r9, r6, r4, lsl r3
d001d780:	78193501 	ldmdavc	r9, {r0, r8, sl, ip, sp}
d001d784:	f7ff4658 			; <UNDEFINED> instruction: 0xf7ff4658
d001d788:	42aff86b 	adcmi	pc, pc, #7012352	; 0x6b0000
d001d78c:	2d0cd064 	stccs	0, cr13, [ip, #-400]	; 0xfffffe70
d001d790:	dcf54633 	ldclle	6, cr4, [r5], #204	; 0xcc
d001d794:	7185ebc5 	orrvc	lr, r5, r5, asr #23
d001d798:	9c0a9b14 			; <UNDEFINED> instruction: 0x9c0a9b14
d001d79c:	460a2f0c 	strmi	r2, [sl], -ip, lsl #30
d001d7a0:	0181ea4f 	orreq	lr, r1, pc, asr #20
d001d7a4:	0282eb03 	addeq	lr, r2, #3072	; 0xc00
d001d7a8:	0330f101 	teqeq	r0, #1073741824	; 0x40000000	; <UNPREDICTABLE>
d001d7ac:	0110f101 	tsteq	r0, r1, lsl #2	; <UNPREDICTABLE>
d001d7b0:	0020f1c2 	eoreq	pc, r0, r2, asr #3
d001d7b4:	0c20f1a2 	stfeqd	f7, [r0], #-648	; 0xfffffd78
d001d7b8:	f202fa24 	vpmax.s8	d15, d2, d20
d001d7bc:	f1c39c0b 			; <UNDEFINED> instruction: 0xf1c39c0b
d001d7c0:	fa040e20 	blx	0xd0121048
d001d7c4:	9c0cf000 	stcls	0, cr15, [ip], {-0}
d001d7c8:	f303fa24 	vpmax.u8	d15, d3, d20
d001d7cc:	ea429c0d 	b	0xd10c4808
d001d7d0:	980d0200 	stmdals	sp, {r9}
d001d7d4:	fe0efa04 	vseleq.f32	s30, s28, s8
d001d7d8:	fa209c0b 	blx	0xd084480c
d001d7dc:	fa24f101 	blx	0xd0959be8
d001d7e0:	ea43fc0c 	b	0xd111c818
d001d7e4:	dc32030e 	ldcle	3, cr0, [r2], #-56	; 0xffffffc8
d001d7e8:	020cea42 	andeq	lr, ip, #270336	; 0x42000
d001d7ec:	030ff002 	movweq	pc, #61442	; 0xf002	; <UNPREDICTABLE>
d001d7f0:	e7c54433 			; <UNDEFINED> instruction: 0xe7c54433
d001d7f4:	447b4bfb 	ldrbtmi	r4, [fp], #-3067	; 0xfffff405
d001d7f8:	e6c49314 			; <UNDEFINED> instruction: 0xe6c49314
d001d7fc:	b1373d02 	teqlt	r7, r2, lsl #26
d001d800:	21203d01 			; <UNDEFINED> instruction: 0x21203d01
d001d804:	f7ff4658 			; <UNDEFINED> instruction: 0xf7ff4658
d001d808:	1c6cf82b 	stclne	8, cr15, [ip], #-172	; 0xffffff54
d001d80c:	f8d9d1f8 			; <UNDEFINED> instruction: 0xf8d9d1f8
d001d810:	46583000 	ldrbmi	r3, [r8], -r0
d001d814:	78191d1a 	ldmdavc	r9, {r1, r3, r4, r8, sl, fp, ip}
d001d818:	2000f8c9 	andcs	pc, r0, r9, asr #17
d001d81c:	f820f7ff 			; <UNDEFINED> instruction: 0xf820f7ff
d001d820:	f016e501 			; <UNDEFINED> instruction: 0xf016e501
d001d824:	eba50301 	bl	0xce95e430
d001d828:	93120504 	tstls	r2, #4, 10	; 0x1000000
d001d82c:	aec2f47f 	mcrge	4, 6, pc, cr2, cr15, {3}	; <UNPREDICTABLE>
d001d830:	b1351e6e 	teqlt	r5, lr, ror #28
d001d834:	21203e01 			; <UNDEFINED> instruction: 0x21203e01
d001d838:	f7ff4658 			; <UNDEFINED> instruction: 0xf7ff4658
d001d83c:	1c73f811 	ldclne	8, cr15, [r3], #-68	; 0xffffffbc
d001d840:	2c00d1f8 	stfcsd	f5, [r0], {248}	; 0xf8
d001d844:	aceff43f 	cfstrdge	mvd15, [pc], #252	; 0xd001d948
d001d848:	93122300 	tstls	r2, #0, 6
d001d84c:	430be6b2 	movwmi	lr, #46770	; 0xb6b2
d001d850:	030ff003 	movweq	pc, #61443	; 0xf003	; <UNPREDICTABLE>
d001d854:	e7934433 			; <UNDEFINED> instruction: 0xe7934433
d001d858:	2c419c15 	mcrrcs	12, 1, r9, r1, cr5
d001d85c:	2150bf0c 	cmpcs	r0, ip, lsl #30
d001d860:	46582170 			; <UNDEFINED> instruction: 0x46582170
d001d864:	fffcf7fe 			; <UNDEFINED> instruction: 0xfffcf7fe
d001d868:	9d219b1a 	vstmdbls	r1!, {d9-d21}
d001d86c:	2b004658 	blcs	0xd002f1d4
d001d870:	461c9b20 	ldrmi	r9, [ip], -r0, lsr #22
d001d874:	212dbfb4 			; <UNDEFINED> instruction: 0x212dbfb4
d001d878:	f7fe212b 			; <UNDEFINED> instruction: 0xf7fe212b
d001d87c:	442cfff1 	strtmi	pc, [ip], #-4081	; 0xfffff00f
d001d880:	e001991f 	and	r9, r1, pc, lsl r9
d001d884:	1d01f814 	stcne	8, cr15, [r1, #-80]	; 0xffffffb0
d001d888:	f7fe4658 			; <UNDEFINED> instruction: 0xf7fe4658
d001d88c:	42a5ffe9 	adcmi	pc, r5, #932	; 0x3a4
d001d890:	9b16d1f8 	blls	0xd05d2078
d001d894:	f43f2b00 			; <UNDEFINED> instruction: 0xf43f2b00
d001d898:	9b12acc6 	blls	0xd04c8bb8
d001d89c:	2b001e5c 	blcs	0xd0025214
d001d8a0:	acc1f43f 	cfstrdge	mvd15, [r1], {63}	; 0x3f
d001d8a4:	21203c01 			; <UNDEFINED> instruction: 0x21203c01
d001d8a8:	f7fe4658 			; <UNDEFINED> instruction: 0xf7fe4658
d001d8ac:	1c63ffd9 	stclne	15, cr15, [r3], #-868	; 0xfffffc9c
d001d8b0:	e4b8d1f8 	ldrt	sp, [r8], #504	; 0x1f8
d001d8b4:	f43f2d00 			; <UNDEFINED> instruction: 0xf43f2d00
d001d8b8:	07f2acb6 			; <UNDEFINED> instruction: 0x07f2acb6
d001d8bc:	817af140 	cmnhi	sl, r0, asr #2	; <UNPREDICTABLE>
d001d8c0:	e68f1e6c 	str	r1, [pc], ip, ror #28
d001d8c4:	e7bc9d12 			; <UNDEFINED> instruction: 0xe7bc9d12
d001d8c8:	f8db3b01 			; <UNDEFINED> instruction: 0xf8db3b01
d001d8cc:	2b062008 	blcs	0xd01a58f4
d001d8d0:	e8dfd812 	ldm	pc, {r1, r4, fp, ip, lr, pc}^	; <UNPREDICTABLE>
d001d8d4:	014bf013 	cmpeq	fp, r3, lsl r0	; <UNPREDICTABLE>
d001d8d8:	00110142 	andseq	r0, r1, r2, asr #2
d001d8dc:	00110007 	andseq	r0, r1, r7
d001d8e0:	00070011 	andeq	r0, r7, r1, lsl r0
d001d8e4:	3000f8d9 	ldrdcc	pc, [r0], -r9
d001d8e8:	1d182100 	ldfnes	f2, [r8, #-0]
d001d8ec:	0000f8c9 	andeq	pc, r0, r9, asr #17
d001d8f0:	e9c3681b 	stmib	r3, {r0, r1, r3, r4, fp, sp, lr}^
d001d8f4:	e4962100 	ldr	r2, [r6], #256	; 0x100
d001d8f8:	3000f8d9 	ldrdcc	pc, [r0], -r9
d001d8fc:	f8c91d19 			; <UNDEFINED> instruction: 0xf8c91d19
d001d900:	681b1000 	ldmdavs	fp, {ip}
d001d904:	e48e601a 	str	r6, [lr], #26
d001d908:	9114212d 	tstls	r4, sp, lsr #2
d001d90c:	212be68d 	smlawbcs	fp, sp, r6, lr
d001d910:	e68a9114 	pkhbt	r9, sl, r4, lsl #2
d001d914:	010ce9dd 	ldrdeq	lr, [ip, -sp]
d001d918:	32fef240 	rscscc	pc, lr, #64, 4
d001d91c:	0301ea50 	movweq	lr, #6736	; 0x1a50
d001d920:	48af9916 	stmiami	pc!, {r1, r2, r4, r8, fp, ip, pc}	; <UNPREDICTABLE>
d001d924:	460bbf0c 	strmi	fp, [fp], -ip, lsl #30
d001d928:	93124613 	tstls	r2, #19922944	; 0x1300000
d001d92c:	230ce9dd 	movwcs	lr, #51677	; 0xc9dd
d001d930:	460bbf0c 	strmi	fp, [fp], -ip, lsl #30
d001d934:	931a4603 	tstls	sl, #3145728	; 0x300000
d001d938:	2c41e692 	mcrrcs	6, 9, lr, r1, cr2
d001d93c:	4632462b 	ldrtmi	r4, [r2], -fp, lsr #12
d001d940:	bf0c4658 	svclt	0x000c4658
d001d944:	21662146 	cmncs	r6, r6, asr #2
d001d948:	ed9d9700 	ldc	7, cr9, [sp]
d001d94c:	f7ff0b12 			; <UNDEFINED> instruction: 0xf7ff0b12
d001d950:	e468f965 	strbt	pc, [r8], #-2405	; 0xfffff69b	; <UNPREDICTABLE>
d001d954:	463b4631 			; <UNDEFINED> instruction: 0x463b4631
d001d958:	f8cd462c 			; <UNDEFINED> instruction: 0xf8cd462c
d001d95c:	9e158048 	cdpls	0, 1, cr8, cr5, cr8, {2}
d001d960:	461746c8 	ldrmi	r4, [r7], -r8, asr #13
d001d964:	460d4699 			; <UNDEFINED> instruction: 0x460d4699
d001d968:	f3402f0c 	vpmax.f32	d18, d0, d12
d001d96c:	97158090 			; <UNDEFINED> instruction: 0x97158090
d001d970:	230ce9dd 	movwcs	lr, #51677	; 0xc9dd
d001d974:	230ae9cd 	movwcs	lr, #43469	; 0xa9cd
d001d978:	270de680 	strcs	lr, [sp, -r0, lsl #13]
d001d97c:	46494628 	strbmi	r4, [r9], -r8, lsr #12
d001d980:	46c12300 	strbmi	r2, [r1], r0, lsl #6
d001d984:	9615463a 			; <UNDEFINED> instruction: 0x9615463a
d001d988:	4625469e 			; <UNDEFINED> instruction: 0x4625469e
d001d98c:	8048f8dd 	ldrdhi	pc, [r8], #-141	; 0xffffff73
d001d990:	4606460f 	strmi	r4, [r6], -pc, lsl #12
d001d994:	0c20f1c3 	stfeqd	f7, [r0], #-780	; 0xfffffcf4
d001d998:	990c980d 	stmdbls	ip, {r0, r2, r3, fp, ip, pc}
d001d99c:	0420f1a3 	strteq	pc, [r0], #-419	; 0xfffffe5d
d001d9a0:	fc0cfa00 	stc2	10, cr15, [ip], {-0}	; <UNPREDICTABLE>
d001d9a4:	40e040d9 	ldrdmi	r4, [r0], #9	; <UNPREDICTABLE>
d001d9a8:	ea413304 	b	0xd106a5c0
d001d9ac:	4301010c 	movwmi	r0, #4364	; 0x110c
d001d9b0:	010ff001 	tsteq	pc, r1	; <UNPREDICTABLE>
d001d9b4:	1e0ae9cd 	vmlsne.f16	s28, s21, s26	; <UNPREDICTABLE>
d001d9b8:	010ae9dd 	ldrdeq	lr, [sl, -sp]
d001d9bc:	d1c94301 	bicle	r4, r9, r1, lsl #6
d001d9c0:	d1e73a01 	mvnle	r3, r1, lsl #20
d001d9c4:	f8cd463b 			; <UNDEFINED> instruction: 0xf8cd463b
d001d9c8:	46178048 	ldrmi	r8, [r7], -r8, asr #32
d001d9cc:	469946c8 	ldrmi	r4, [r9], r8, asr #13
d001d9d0:	462c4631 			; <UNDEFINED> instruction: 0x462c4631
d001d9d4:	460d9e15 			; <UNDEFINED> instruction: 0x460d9e15
d001d9d8:	e9dd9715 	ldmib	sp, {r0, r2, r4, r8, r9, sl, ip, pc}^
d001d9dc:	e9cd230c 	stmib	sp, {r2, r3, r8, r9, sp}^
d001d9e0:	22012318 	andcs	r2, r1, #24, 6	; 0x60000000
d001d9e4:	e9cd2300 	stmib	sp, {r8, r9, sp}^
d001d9e8:	22002310 	andcs	r2, r0, #16, 6	; 0x40000000
d001d9ec:	2300f44f 	movwcs	pc, #1103	; 0x44f	; <UNPREDICTABLE>
d001d9f0:	230ee9cd 	movwcs	lr, #59853	; 0xe9cd
d001d9f4:	230ee9dd 	movwcs	lr, #59869	; 0xe9dd
d001d9f8:	0118e9dd 			; <UNDEFINED> instruction: 0x0118e9dd
d001d9fc:	bf08428b 	svclt	0x0008428b
d001da00:	f0c04282 			; <UNDEFINED> instruction: 0xf0c04282
d001da04:	429980c1 	addsmi	r8, r9, #193	; 0xc1
d001da08:	4290bf08 	addsmi	fp, r0, #8, 30
d001da0c:	80b7f000 	adcshi	pc, r7, r0
d001da10:	230ae9dd 	movwcs	lr, #43485	; 0xa9dd
d001da14:	0110e9dd 			; <UNDEFINED> instruction: 0x0110e9dd
d001da18:	bf08428b 	svclt	0x0008428b
d001da1c:	f47f4282 			; <UNDEFINED> instruction: 0xf47f4282
d001da20:	9b17ae2d 	blls	0xd06092dc
d001da24:	33012200 	movwcc	r2, #4608	; 0x1200
d001da28:	23009317 	movwcs	r9, #791	; 0x317
d001da2c:	230ae9cd 	movwcs	lr, #43469	; 0xa9cd
d001da30:	4619e624 	ldrmi	lr, [r9], -r4, lsr #12
d001da34:	f7fe4658 			; <UNDEFINED> instruction: 0xf7fe4658
d001da38:	e675ff13 	uhadd16	pc, r5, r3	; <UNPREDICTABLE>
d001da3c:	0310f016 	tsteq	r0, #22	; <UNPREDICTABLE>
d001da40:	2204bf14 	andcs	fp, r4, #20, 30	; 0x50
d001da44:	931b2203 	tstls	fp, #805306368	; 0x30000000
d001da48:	b177e63f 	cmnlt	r7, pc, lsr r6
d001da4c:	e6919e09 	ldr	r9, [r1], r9, lsl #28
d001da50:	e665461e 			; <UNDEFINED> instruction: 0xe665461e
d001da54:	0203f006 	andeq	pc, r3, #6
d001da58:	0301f006 	movweq	pc, #4102	; 0x1006	; <UNPREDICTABLE>
d001da5c:	2200921e 	andcs	r9, r0, #-536870911	; 0xe0000001
d001da60:	0601f083 	streq	pc, [r1], -r3, lsl #1
d001da64:	92129316 	andsls	r9, r2, #1476395008	; 0x58000000
d001da68:	2150e65a 	cmpcs	r0, sl, asr r6
d001da6c:	9b12e6f9 	blls	0xd04d7658
d001da70:	e6559316 			; <UNDEFINED> instruction: 0xe6559316
d001da74:	1e5d9b12 	vmovne.s8	r9, d13[0]
d001da78:	f43f2b00 			; <UNDEFINED> instruction: 0xf43f2b00
d001da7c:	3d01ae66 	stccc	14, cr10, [r1, #-408]	; 0xfffffe68
d001da80:	46582130 			; <UNDEFINED> instruction: 0x46582130
d001da84:	feecf7fe 	mcr2	7, 7, pc, cr12, cr14, {7}	; <UNPREDICTABLE>
d001da88:	d1f81c6a 	mvnsle	r1, sl, ror #24
d001da8c:	f1c7e65d 			; <UNDEFINED> instruction: 0xf1c7e65d
d001da90:	e9dd030d 	ldmib	sp, {r0, r2, r3, r8, r9}^
d001da94:	009b120c 	addseq	r1, fp, ip, lsl #4
d001da98:	f1c34618 			; <UNDEFINED> instruction: 0xf1c34618
d001da9c:	f1a30c20 			; <UNDEFINED> instruction: 0xf1a30c20
d001daa0:	460b0e20 	strmi	r0, [fp], -r0, lsr #28
d001daa4:	fc0cfa02 	stc2	10, cr15, [ip], {2}	; <UNPREDICTABLE>
d001daa8:	32fff04f 	rscscc	pc, pc, #79	; 0x4f
d001daac:	f1a040c3 			; <UNDEFINED> instruction: 0xf1a040c3
d001dab0:	930a0120 	movwls	r0, #41248	; 0xa120
d001dab4:	33fff04f 	mvnscc	pc, #79	; 0x4f
d001dab8:	fe0efa03 	vseleq.f32	s30, s28, s6
d001dabc:	f300fa02 	vpmax.u8	d15, d0, d2
d001dac0:	ea429a0a 	b	0xd10c42f0
d001dac4:	f1c0020c 			; <UNDEFINED> instruction: 0xf1c0020c
d001dac8:	920a0c20 	andls	r0, sl, #32, 24	; 0x2000
d001dacc:	fa229a0d 	blx	0xd08c4308
d001dad0:	ea43f101 	b	0xd1119edc
d001dad4:	f04f020e 			; <UNDEFINED> instruction: 0xf04f020e
d001dad8:	fa2333ff 	blx	0xd08eaadc
d001dadc:	4603fc0c 	strmi	pc, [r3], -ip, lsl #24
d001dae0:	30fff04f 	rscscc	pc, pc, pc, asr #32
d001dae4:	0e21f1a3 	abseqdp	f7, f3
d001dae8:	40989315 	addsmi	r9, r8, r5, lsl r3
d001daec:	ea429b0a 	b	0xd10c471c
d001daf0:	430b020c 	movwmi	r0, #45580	; 0xb20c
d001daf4:	921b2101 	andsls	r2, fp, #1073741824	; 0x40000000
d001daf8:	9b0c930a 	blls	0xd0342728
d001dafc:	ea239a15 	b	0xd0904358
d001db00:	00b80300 	adcseq	r0, r8, r0, lsl #6
d001db04:	0c21f1c2 	stfeqd	f7, [r1], #-776	; 0xfffffcf8
d001db08:	93189715 	tstls	r8, #5505024	; 0x540000
d001db0c:	f30efa01 	vpmax.u8	d15, d14, d1
d001db10:	0e20f1a0 	abseqdp	f7, f0
d001db14:	fc0cfa21 	stc2	10, cr15, [ip], {33}	; 0x21	; <UNPREDICTABLE>
d001db18:	9b0d930f 	blls	0xd038275c
d001db1c:	930b40d3 	movwls	r4, #45267	; 0xb0d3
d001db20:	f30efa01 	vpmax.u8	d15, d14, d1
d001db24:	0e20f1c0 	abseqdm	f7, f0
d001db28:	9b0f9311 	blls	0xd0402774
d001db2c:	fe0efa21 	vseleq.f32	s30, s28, s3
d001db30:	030cea43 	movweq	lr, #51779	; 0xca43
d001db34:	3cfff102 	ldfccp	f7, [pc], #8	; 0xd001db44
d001db38:	930f9a1b 	movwls	r9, #64027	; 0xfa1b
d001db3c:	ea239b0d 	b	0xd0904778
d001db40:	fa010202 	blx	0xd005e350
d001db44:	930ef30c 	movwls	pc, #58124	; 0xe30c	; <UNPREDICTABLE>
d001db48:	92199b11 	andsls	r9, r9, #17408	; 0x4400
d001db4c:	030eea43 	movweq	lr, #59971	; 0xea43
d001db50:	fa019311 	blx	0xd008279c
d001db54:	9310f300 	tstls	r0, #0, 6	; <UNPREDICTABLE>
d001db58:	f8d9e74c 			; <UNDEFINED> instruction: 0xf8d9e74c
d001db5c:	1d193000 	ldcne	0, cr3, [r9, #-0]
d001db60:	1000f8c9 	andne	pc, r0, r9, asr #17
d001db64:	801a681b 	andshi	r6, sl, fp, lsl r8
d001db68:	bb5df7ff 	bllt	0xd179bb6c
d001db6c:	3000f8d9 	ldrdcc	pc, [r0], -r9
d001db70:	f8c91d19 			; <UNDEFINED> instruction: 0xf8c91d19
d001db74:	681b1000 	ldmdavs	fp, {ip}
d001db78:	f7ff701a 			; <UNDEFINED> instruction: 0xf7ff701a
d001db7c:	b95fbb54 	ldmdblt	pc, {r2, r4, r6, r8, r9, fp, ip, sp, pc}^	; <UNPREDICTABLE>
d001db80:	2b009b16 	blcs	0xd00447e0
d001db84:	af44f43f 	svcge	0x0044f43f
d001db88:	33019b0a 	movwcc	r9, #6922	; 0x1b0a
d001db8c:	9b0b930a 	blls	0xd03027bc
d001db90:	0300f143 	movweq	pc, #323	; 0x143	; <UNPREDICTABLE>
d001db94:	e73b930b 	ldr	r9, [fp, -fp, lsl #6]!
d001db98:	f0039b0a 			; <UNDEFINED> instruction: 0xf0039b0a
d001db9c:	931c0301 	tstls	ip, #67108864	; 0x4000000
d001dba0:	931d2300 	tstls	sp, #0, 6
d001dba4:	231ce9dd 	tstcs	ip, #3620864	; 0x374000
d001dba8:	f43f4313 			; <UNDEFINED> instruction: 0xf43f4313
d001dbac:	e7ebaf31 			; <UNDEFINED> instruction: 0xe7ebaf31
d001dbb0:	e6562170 			; <UNDEFINED> instruction: 0xe6562170
d001dbb4:	24001e6e 	strcs	r1, [r0], #-3694	; 0xfffff192
d001dbb8:	f8d9e63c 			; <UNDEFINED> instruction: 0xf8d9e63c
d001dbbc:	23000000 	movwcs	r0, #0
d001dbc0:	30046802 	andcc	r6, r4, r2, lsl #16
d001dbc4:	0000f8c9 	andeq	pc, r0, r9, asr #17
d001dbc8:	bb1bf7ff 	bllt	0xd071bbcc
d001dbcc:	3000f8d9 	ldrdcc	pc, [r0], -r9
d001dbd0:	33046818 	movwcc	r6, #18456	; 0x4818
d001dbd4:	f8c917c1 			; <UNDEFINED> instruction: 0xf8c917c1
d001dbd8:	f7ff3000 			; <UNDEFINED> instruction: 0xf7ff3000
d001dbdc:	bf00bb58 	svclt	0x0000bb58
d001dbe0:	fffffc02 			; <UNDEFINED> instruction: 0xfffffc02
d001dbe4:	fffff88e 			; <UNDEFINED> instruction: 0xfffff88e

Disassembly of section .text.vsnprintf:

d001dbe8 <.text.vsnprintf>:
d001dbe8:	b0a7b5f0 	strdlt	fp, [r7], r0	; <UNPREDICTABLE>
d001dbec:	460e4607 	strmi	r4, [lr], -r7, lsl #12
d001dbf0:	4614461d 			; <UNDEFINED> instruction: 0x4614461d
d001dbf4:	228c2100 	addcs	r2, ip, #0, 2
d001dbf8:	f7fea803 			; <UNDEFINED> instruction: 0xf7fea803
d001dbfc:	9701fc31 	smuadxls	r1, r1, ip
d001dc00:	95009602 	strls	r9, [r0, #-1538]	; 0xfffff9fe
d001dc04:	4621b134 			; <UNDEFINED> instruction: 0x4621b134
d001dc08:	a801466a 	stmdage	r1, {r1, r3, r5, r6, r9, sl, lr}
d001dc0c:	fa54f7ff 	blx	0xd155bc10
d001dc10:	bdf0b027 	ldcllt	0, cr11, [r0, #156]!	; 0x9c
d001dc14:	30fff04f 	rscscc	pc, pc, pc, asr #32
d001dc18:	bf00e7fa 	svclt	0x0000e7fa

Disassembly of section .text.snprintf:

d001dc1c <.text.snprintf>:
d001dc1c:	b500b40c 	strlt	fp, [r0, #-1036]	; 0xfffffbf4
d001dc20:	ab04b083 	blge	0xd0149e34
d001dc24:	2b04f853 	blcs	0xd015bd78
d001dc28:	f7ff9301 			; <UNDEFINED> instruction: 0xf7ff9301
d001dc2c:	b003ffdd 	ldrdlt	pc, [r3], -sp
d001dc30:	eb04f85d 	bl	0xd015bdac
d001dc34:	4770b002 	ldrbmi	fp, [r0, -r2]!

Disassembly of section .text.memchr:

d001dc60 <.text.memchr>:
d001dc60:	4603b192 			; <UNDEFINED> instruction: 0x4603b192
d001dc64:	b410b2c9 	ldrlt	fp, [r0], #-713	; 0xfffffd37
d001dc68:	e0011884 	and	r1, r1, r4, lsl #17
d001dc6c:	d00742a3 	andle	r4, r7, r3, lsr #5
d001dc70:	f8134618 			; <UNDEFINED> instruction: 0xf8134618
d001dc74:	428a2b01 	addmi	r2, sl, #1024	; 0x400
d001dc78:	f85dd1f8 			; <UNDEFINED> instruction: 0xf85dd1f8
d001dc7c:	47704b04 	ldrbmi	r4, [r0, -r4, lsl #22]!
d001dc80:	f85d2000 			; <UNDEFINED> instruction: 0xf85d2000
d001dc84:	47704b04 	ldrbmi	r4, [r0, -r4, lsl #22]!
d001dc88:	47704610 			; <UNDEFINED> instruction: 0x47704610

Disassembly of section .text.strlen:

d001dc8c <.text.strlen>:
d001dc8c:	b1327802 	teqlt	r2, r2, lsl #16
d001dc90:	f8134603 			; <UNDEFINED> instruction: 0xf8134603
d001dc94:	29001f01 	stmdbcs	r0, {r0, r8, r9, sl, fp, ip}
d001dc98:	1a18d1fb 	bne	0xd065248c
d001dc9c:	46104770 			; <UNDEFINED> instruction: 0x46104770
d001dca0:	bf004770 	svclt	0x00004770

Disassembly of section .text.strcmp:

d001dca4 <.text.strcmp>:
d001dca4:	b1937803 	orrslt	r7, r3, r3, lsl #16
d001dca8:	e002b410 	and	fp, r2, r0, lsl r4
d001dcac:	3f01f810 	svccc	0x0001f810
d001dcb0:	460cb143 	strmi	fp, [ip], -r3, asr #2
d001dcb4:	2b01f811 	blcs	0xd009bd00
d001dcb8:	d0f7429a 	smlalsle	r4, r7, sl, r2
d001dcbc:	f85d1a98 			; <UNDEFINED> instruction: 0xf85d1a98
d001dcc0:	47704b04 	ldrbmi	r4, [r0, -r4, lsl #22]!
d001dcc4:	f85d7862 			; <UNDEFINED> instruction: 0xf85d7862
d001dcc8:	1a984b04 	bne	0xce6308e0
d001dccc:	780a4770 	stmdavc	sl, {r4, r5, r6, r8, r9, sl, lr}
d001dcd0:	47701a98 			; <UNDEFINED> instruction: 0x47701a98

Disassembly of section .text.strchr:

d001dcd4 <.text.strchr>:
d001dcd4:	7803b2c9 	stmdavc	r3, {r0, r3, r6, r7, r9, ip, sp, pc}
d001dcd8:	d0064299 	mulle	r6, r9, r2
d001dcdc:	f810b123 			; <UNDEFINED> instruction: 0xf810b123
d001dce0:	428b3f01 	addmi	r3, fp, #1, 30
d001dce4:	4770d1fa 			; <UNDEFINED> instruction: 0x4770d1fa
d001dce8:	47704618 			; <UNDEFINED> instruction: 0x47704618

Disassembly of section .text.strrchr:

d001dcec <.text.strrchr>:
d001dcec:	b2c92200 	sbclt	r2, r9, #0, 4
d001dcf0:	4604b410 			; <UNDEFINED> instruction: 0x4604b410
d001dcf4:	3b01f810 	blcc	0xd009bd3c
d001dcf8:	bf08428b 	svclt	0x0008428b
d001dcfc:	2b004622 	blcs	0xd002f58c
d001dd00:	4610d1f7 			; <UNDEFINED> instruction: 0x4610d1f7
d001dd04:	4b04f85d 	blmi	0xd015be80
d001dd08:	bf004770 	svclt	0x00004770
