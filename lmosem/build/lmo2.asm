
lmosemkrnl.elf:     file format elf32-littlearm


Disassembly of section .head.text:

30010000 <_start>:
30010000:	ea000006 	b	30010020 <reset>
30010004:	e59ff078 	ldr	pc, [pc, #120]	; 30010084 <tstw+0x4>
30010008:	e59ff078 	ldr	pc, [pc, #120]	; 30010088 <tstw+0x8>
3001000c:	e59ff078 	ldr	pc, [pc, #120]	; 3001008c <tstw+0xc>
30010010:	e59ff078 	ldr	pc, [pc, #120]	; 30010090 <tstw+0x10>
30010014:	e59ff078 	ldr	pc, [pc, #120]	; 30010094 <tstw+0x14>
30010018:	e59ff078 	ldr	pc, [pc, #120]	; 30010098 <tstw+0x18>
3001001c:	e59ff078 	ldr	pc, [pc, #120]	; 3001009c <tstw+0x1c>

30010020 <reset>:
30010020:	e329f0d3 	msr	CPSR_fc, #211	; 0xd3
30010024:	e3a00453 	mov	r0, #1392508928	; 0x53000000
30010028:	e3a01000 	mov	r1, #0	; 0x0
3001002c:	e5801000 	str	r1, [r0]
30010030:	e59f0068 	ldr	r0, [pc, #104]	; 300100a0 <tstw+0x20>
30010034:	e3e01000 	mvn	r1, #0	; 0x0
30010038:	e5801000 	str	r1, [r0]
3001003c:	e59f0060 	ldr	r0, [pc, #96]	; 300100a4 <tstw+0x24>
30010040:	e59f1060 	ldr	r1, [pc, #96]	; 300100a8 <tstw+0x28>
30010044:	e5801000 	str	r1, [r0]
30010048:	e59f0030 	ldr	r0, [pc, #48]	; 30010080 <tstw>
3001004c:	e3a0d30d 	mov	sp, #872415232	; 0x34000000
30010050:	eb00047f 	bl	30011254 <hal_undefins_distr>

30010054 <lmde>:
30010054:	eafffffe 	b	30010054 <lmde>
	...

30010060 <_undefined_struction>:
30010060:	e321f0d3 	msr	CPSR_c, #211	; 0xd3
30010064:	eb00047a 	bl	30011254 <hal_undefins_distr>

30010068 <_software_struction>:
30010068:	eafffffe 	b	30010068 <_software_struction>

3001006c <_prefetch_abort>:
3001006c:	eafffffe 	b	3001006c <_prefetch_abort>

30010070 <_data_abort>:
30010070:	eafffffe 	b	30010070 <_data_abort>

30010074 <_not_used>:
30010074:	eafffffe 	b	30010074 <_not_used>

30010078 <_irq>:
30010078:	eafffffe 	b	30010078 <_irq>

3001007c <_fiq>:
3001007c:	eafffffe 	b	3001007c <_fiq>

30010080 <tstw>:
30010080:	30010420 	.word	0x30010420
30010084:	30010060 	.word	0x30010060
30010088:	30010068 	.word	0x30010068
3001008c:	3001006c 	.word	0x3001006c
30010090:	30010070 	.word	0x30010070
30010094:	30010074 	.word	0x30010074
30010098:	30010078 	.word	0x30010078
3001009c:	3001007c 	.word	0x3001007c
300100a0:	4a000008 	.word	0x4a000008
300100a4:	4a00001c 	.word	0x4a00001c
300100a8:	00007fff 	.word	0x00007fff
300100ac:	00000000 	.word	0x00000000

300100b0 <raise>:
300100b0:	e24dd008 	sub	sp, sp, #8	; 0x8
300100b4:	e58d0004 	str	r0, [sp, #4]
300100b8:	e28dd008 	add	sp, sp, #8	; 0x8
300100bc:	e12fff1e 	bx	lr

300100c0 <init_hal>:
300100c0:	e92d4010 	push	{r4, lr}
300100c4:	eb0000d5 	bl	30010420 <__begin_lmosem_hal_intvect>
300100c8:	e8bd4010 	pop	{r4, lr}
300100cc:	e12fff1e 	bx	lr

300100d0 <s3c2440mmu_init>:
300100d0:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
300100d4:	e24dd014 	sub	sp, sp, #20	; 0x14
300100d8:	e3a03000 	mov	r3, #0	; 0x0
300100dc:	e58d3000 	str	r3, [sp]
300100e0:	e3a03000 	mov	r3, #0	; 0x0
300100e4:	e58d3004 	str	r3, [sp, #4]
300100e8:	e3a03203 	mov	r3, #805306368	; 0x30000000
300100ec:	e2833901 	add	r3, r3, #16384	; 0x4000
300100f0:	e58d3008 	str	r3, [sp, #8]
300100f4:	e3a03000 	mov	r3, #0	; 0x0
300100f8:	e58d300c 	str	r3, [sp, #12]
300100fc:	ea00000f 	b	30010140 <s3c2440mmu_init+0x70>
30010100:	e59d3000 	ldr	r3, [sp]
30010104:	e3833b03 	orr	r3, r3, #3072	; 0xc00
30010108:	e3833002 	orr	r3, r3, #2	; 0x2
3001010c:	e58d3004 	str	r3, [sp, #4]
30010110:	e59d300c 	ldr	r3, [sp, #12]
30010114:	e1a02103 	lsl	r2, r3, #2
30010118:	e59d3008 	ldr	r3, [sp, #8]
3001011c:	e0832002 	add	r2, r3, r2
30010120:	e59d3004 	ldr	r3, [sp, #4]
30010124:	e5823000 	str	r3, [r2]
30010128:	e59d3000 	ldr	r3, [sp]
3001012c:	e2833601 	add	r3, r3, #1048576	; 0x100000
30010130:	e58d3000 	str	r3, [sp]
30010134:	e59d300c 	ldr	r3, [sp, #12]
30010138:	e2833001 	add	r3, r3, #1	; 0x1
3001013c:	e58d300c 	str	r3, [sp, #12]
30010140:	e59d200c 	ldr	r2, [sp, #12]
30010144:	e3a03eff 	mov	r3, #4080	; 0xff0
30010148:	e283300f 	add	r3, r3, #15	; 0xf
3001014c:	e1520003 	cmp	r2, r3
30010150:	9affffea 	bls	30010100 <s3c2440mmu_init+0x30>
30010154:	e59d2008 	ldr	r2, [sp, #8]
30010158:	e3a03b03 	mov	r3, #3072	; 0xc00
3001015c:	e2833223 	add	r3, r3, #805306370	; 0x30000002
30010160:	e5823000 	str	r3, [r2]
30010164:	e3a00203 	mov	r0, #805306368	; 0x30000000
30010168:	e2800901 	add	r0, r0, #16384	; 0x4000
3001016c:	eb000012 	bl	300101bc <s3c2440mmu_set_tblbass>
30010170:	e3e00000 	mvn	r0, #0	; 0x0
30010174:	eb00000a 	bl	300101a4 <s3c2440mmu_set_domain>
30010178:	eb000004 	bl	30010190 <s3c2440mmu_invalid_dicache>
3001017c:	eb000380 	bl	30010f84 <hal_disable_cache>
30010180:	eb000013 	bl	300101d4 <s3c2440mmu_enable>
30010184:	e28dd014 	add	sp, sp, #20	; 0x14
30010188:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
3001018c:	e12fff1e 	bx	lr

30010190 <s3c2440mmu_invalid_dicache>:
30010190:	e3a00000 	mov	r0, #0	; 0x0
30010194:	ee070f17 	mcr	15, 0, r0, cr7, cr7, {0}
30010198:	ee070f9a 	mcr	15, 0, r0, cr7, cr10, {4}
3001019c:	ee080f17 	mcr	15, 0, r0, cr8, cr7, {0}
300101a0:	e12fff1e 	bx	lr

300101a4 <s3c2440mmu_set_domain>:
300101a4:	e24dd008 	sub	sp, sp, #8	; 0x8
300101a8:	e58d0004 	str	r0, [sp, #4]
300101ac:	e59d3004 	ldr	r3, [sp, #4]
300101b0:	ee033f10 	mcr	15, 0, r3, cr3, cr0, {0}
300101b4:	e28dd008 	add	sp, sp, #8	; 0x8
300101b8:	e12fff1e 	bx	lr

300101bc <s3c2440mmu_set_tblbass>:
300101bc:	e24dd008 	sub	sp, sp, #8	; 0x8
300101c0:	e58d0004 	str	r0, [sp, #4]
300101c4:	e59d3004 	ldr	r3, [sp, #4]
300101c8:	ee023f10 	mcr	15, 0, r3, cr2, cr0, {0}
300101cc:	e28dd008 	add	sp, sp, #8	; 0x8
300101d0:	e12fff1e 	bx	lr

300101d4 <s3c2440mmu_enable>:
300101d4:	ee010f10 	mcr	15, 0, r0, cr1, cr0, {0}
300101d8:	e3800001 	orr	r0, r0, #1	; 0x1
300101dc:	ee010f10 	mcr	15, 0, r0, cr1, cr0, {0}
300101e0:	e1a00000 	nop			(mov r0,r0)
300101e4:	e1a00000 	nop			(mov r0,r0)
300101e8:	e1a00000 	nop			(mov r0,r0)
300101ec:	e1a00000 	nop			(mov r0,r0)
300101f0:	e1a00000 	nop			(mov r0,r0)
300101f4:	e1a00000 	nop			(mov r0,r0)
300101f8:	e1a00000 	nop			(mov r0,r0)
300101fc:	e12fff1e 	bx	lr

30010200 <s3c2440vector_init>:
30010200:	e92d4010 	push	{r4, lr}
30010204:	eb000001 	bl	30010210 <s3c2440vector_copy>
30010208:	e8bd4010 	pop	{r4, lr}
3001020c:	e12fff1e 	bx	lr

30010210 <s3c2440vector_copy>:
30010210:	e24dd010 	sub	sp, sp, #16	; 0x10
30010214:	e59f3098 	ldr	r3, [pc, #152]	; 300102b4 <s3c2440vector_copy+0xa4>
30010218:	e58d3000 	str	r3, [sp]
3001021c:	e59f3094 	ldr	r3, [pc, #148]	; 300102b8 <s3c2440vector_copy+0xa8>
30010220:	e58d3004 	str	r3, [sp, #4]
30010224:	e3a03000 	mov	r3, #0	; 0x0
30010228:	e58d3008 	str	r3, [sp, #8]
3001022c:	e3a03000 	mov	r3, #0	; 0x0
30010230:	e58d300c 	str	r3, [sp, #12]
30010234:	ea000008 	b	3001025c <s3c2440vector_copy+0x4c>
30010238:	e59d300c 	ldr	r3, [sp, #12]
3001023c:	e1a02103 	lsl	r2, r3, #2
30010240:	e59d3008 	ldr	r3, [sp, #8]
30010244:	e0832002 	add	r2, r3, r2
30010248:	e3a03000 	mov	r3, #0	; 0x0
3001024c:	e5823000 	str	r3, [r2]
30010250:	e59d300c 	ldr	r3, [sp, #12]
30010254:	e2833001 	add	r3, r3, #1	; 0x1
30010258:	e58d300c 	str	r3, [sp, #12]
3001025c:	e59d200c 	ldr	r2, [sp, #12]
30010260:	e3a03eff 	mov	r3, #4080	; 0xff0
30010264:	e283300f 	add	r3, r3, #15	; 0xf
30010268:	e1520003 	cmp	r2, r3
3001026c:	9afffff1 	bls	30010238 <s3c2440vector_copy+0x28>
30010270:	ea000009 	b	3001029c <s3c2440vector_copy+0x8c>
30010274:	e59d3004 	ldr	r3, [sp, #4]
30010278:	e5932000 	ldr	r2, [r3]
3001027c:	e59d3008 	ldr	r3, [sp, #8]
30010280:	e5832000 	str	r2, [r3]
30010284:	e59d3004 	ldr	r3, [sp, #4]
30010288:	e2833004 	add	r3, r3, #4	; 0x4
3001028c:	e58d3004 	str	r3, [sp, #4]
30010290:	e59d3008 	ldr	r3, [sp, #8]
30010294:	e2833004 	add	r3, r3, #4	; 0x4
30010298:	e58d3008 	str	r3, [sp, #8]
3001029c:	e59d2004 	ldr	r2, [sp, #4]
300102a0:	e59d3000 	ldr	r3, [sp]
300102a4:	e1520003 	cmp	r2, r3
300102a8:	3afffff1 	bcc	30010274 <s3c2440vector_copy+0x64>
300102ac:	e28dd010 	add	sp, sp, #16	; 0x10
300102b0:	e12fff1e 	bx	lr
300102b4:	30010420 	.word	0x30010420
300102b8:	30011940 	.word	0x30011940

Disassembly of section .lmosem_hal.intvect:

300102bc <hal_undefins-0x4>:
300102bc:	00000000 	andeq	r0, r0, r0

300102c0 <hal_undefins>:
300102c0:	e321f0d3 	msr	CPSR_c, #211	; 0xd3
300102c4:	e24dd040 	sub	sp, sp, #64	; 0x40
300102c8:	e8cd7fff 	stmia	sp, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr}^
300102cc:	e321f0db 	msr	CPSR_c, #219	; 0xdb
300102d0:	e24e1000 	sub	r1, lr, #0	; 0x0
300102d4:	e14f0000 	mrs	r0, SPSR
300102d8:	e321f0d3 	msr	CPSR_c, #211	; 0xd3
300102dc:	e58d103c 	str	r1, [sp, #60]
300102e0:	e92d4001 	push	{r0, lr}
300102e4:	e1a0000d 	mov	r0, sp
300102e8:	e8bd4001 	pop	{r0, lr}
300102ec:	e169f000 	msr	SPSR_fc, r0
300102f0:	e8dd7fff 	ldm	sp, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr}^
300102f4:	e28dd03c 	add	sp, sp, #60	; 0x3c
300102f8:	e8fd8000 	ldm	sp!, {pc}^

300102fc <hal_swi>:
300102fc:	e2499040 	sub	r9, r9, #64	; 0x40
30010300:	e8cd7ffe 	stmia	sp, {r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr}^
30010304:	e14f1000 	mrs	r1, SPSR
30010308:	e58de03c 	str	lr, [sp, #60]
3001030c:	e92d4002 	push	{r1, lr}
30010310:	e1a0100d 	mov	r1, sp
30010314:	e8bd4002 	pop	{r1, lr}
30010318:	e169f001 	msr	SPSR_fc, r1
3001031c:	e8dd7ffe 	ldm	sp, {r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr}^
30010320:	e28dd03c 	add	sp, sp, #60	; 0x3c
30010324:	e8fd8000 	ldm	sp!, {pc}^

30010328 <hal_prefabt>:
30010328:	e321f0d3 	msr	CPSR_c, #211	; 0xd3
3001032c:	e24dd040 	sub	sp, sp, #64	; 0x40
30010330:	e8cd7fff 	stmia	sp, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr}^
30010334:	e321f0d7 	msr	CPSR_c, #215	; 0xd7
30010338:	e24e1004 	sub	r1, lr, #4	; 0x4
3001033c:	e14f0000 	mrs	r0, SPSR
30010340:	e58d103c 	str	r1, [sp, #60]
30010344:	e92d4001 	push	{r0, lr}
30010348:	e1a0000d 	mov	r0, sp
3001034c:	e8bd4001 	pop	{r0, lr}
30010350:	e169f000 	msr	SPSR_fc, r0
30010354:	e8dd7fff 	ldm	sp, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr}^
30010358:	e28dd03c 	add	sp, sp, #60	; 0x3c
3001035c:	e8fd8000 	ldm	sp!, {pc}^

30010360 <hal_dataabt>:
30010360:	e321f0d3 	msr	CPSR_c, #211	; 0xd3
30010364:	e24dd040 	sub	sp, sp, #64	; 0x40
30010368:	e8cd7fff 	stmia	sp, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr}^
3001036c:	e321f0d7 	msr	CPSR_c, #215	; 0xd7
30010370:	e24e1008 	sub	r1, lr, #8	; 0x8
30010374:	e14f0000 	mrs	r0, SPSR
30010378:	e321f0d3 	msr	CPSR_c, #211	; 0xd3
3001037c:	e58d103c 	str	r1, [sp, #60]
30010380:	e92d4001 	push	{r0, lr}
30010384:	e1a0000d 	mov	r0, sp
30010388:	e8bd4001 	pop	{r0, lr}
3001038c:	e169f000 	msr	SPSR_fc, r0
30010390:	e8dd7fff 	ldm	sp, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr}^
30010394:	e28dd03c 	add	sp, sp, #60	; 0x3c
30010398:	e8fd8000 	ldm	sp!, {pc}^

3001039c <hal_bugdie>:
3001039c:	eafffffe 	b	3001039c <hal_bugdie>

300103a0 <hal_irq>:
300103a0:	e321f0d3 	msr	CPSR_c, #211	; 0xd3
300103a4:	e24dd040 	sub	sp, sp, #64	; 0x40
300103a8:	e8cd7fff 	stmia	sp, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr}^
300103ac:	e321f0d2 	msr	CPSR_c, #210	; 0xd2
300103b0:	e24e1004 	sub	r1, lr, #4	; 0x4
300103b4:	e14f0000 	mrs	r0, SPSR
300103b8:	e321f0d3 	msr	CPSR_c, #211	; 0xd3
300103bc:	e58d103c 	str	r1, [sp, #60]
300103c0:	e92d4001 	push	{r0, lr}
300103c4:	e1a0000d 	mov	r0, sp
300103c8:	e8bd4001 	pop	{r0, lr}
300103cc:	e169f000 	msr	SPSR_fc, r0
300103d0:	e8dd7fff 	ldm	sp, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr}^
300103d4:	e28dd03c 	add	sp, sp, #60	; 0x3c
300103d8:	e8fd8000 	ldm	sp!, {pc}^

300103dc <hal_frq>:
300103dc:	e321f0d3 	msr	CPSR_c, #211	; 0xd3
300103e0:	e24dd040 	sub	sp, sp, #64	; 0x40
300103e4:	e8cd7fff 	stmia	sp, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr}^
300103e8:	e321f0d1 	msr	CPSR_c, #209	; 0xd1
300103ec:	e24e1004 	sub	r1, lr, #4	; 0x4
300103f0:	e14f0000 	mrs	r0, SPSR
300103f4:	e321f0d3 	msr	CPSR_c, #211	; 0xd3
300103f8:	e58d103c 	str	r1, [sp, #60]
300103fc:	e92d4001 	push	{r0, lr}
30010400:	e1a0000d 	mov	r0, sp
30010404:	e8bd4001 	pop	{r0, lr}
30010408:	e169f000 	msr	SPSR_fc, r0
3001040c:	e8dd7fff 	ldm	sp, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr}^
30010410:	e28dd03c 	add	sp, sp, #60	; 0x3c
30010414:	e8fd8000 	ldm	sp!, {pc}^
30010418:	e1a00000 	nop			(mov r0,r0)
3001041c:	e1a00000 	nop			(mov r0,r0)

Disassembly of section .text:

30010420 <init_haluart>:
30010420:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
30010424:	e24dd00c 	sub	sp, sp, #12	; 0xc
30010428:	e3a03061 	mov	r3, #97	; 0x61
3001042c:	e5cd3007 	strb	r3, [sp, #7]
30010430:	e5dd3007 	ldrb	r3, [sp, #7]
30010434:	e1a00003 	mov	r0, r3
30010438:	eb000013 	bl	3001048c <hal_uart0_putc>
3001043c:	eafffffe 	b	3001043c <init_haluart+0x1c>

30010440 <init_uart0>:
30010440:	e92d4010 	push	{r4, lr}
30010444:	e3a00205 	mov	r0, #1342177280	; 0x50000000
30010448:	e3a01003 	mov	r1, #3	; 0x3
3001044c:	eb000244 	bl	30010d64 <hal_io32_write>
30010450:	e3a00245 	mov	r0, #1342177284	; 0x50000004
30010454:	e3a01005 	mov	r1, #5	; 0x5
30010458:	eb000241 	bl	30010d64 <hal_io32_write>
3001045c:	e3a00285 	mov	r0, #1342177288	; 0x50000008
30010460:	e3a01000 	mov	r1, #0	; 0x0
30010464:	eb00023e 	bl	30010d64 <hal_io32_write>
30010468:	e3a002c5 	mov	r0, #1342177292	; 0x5000000c
3001046c:	e3a01000 	mov	r1, #0	; 0x0
30010470:	eb00023b 	bl	30010d64 <hal_io32_write>
30010474:	e3a00205 	mov	r0, #1342177280	; 0x50000000
30010478:	e2800028 	add	r0, r0, #40	; 0x28
3001047c:	e3a0101a 	mov	r1, #26	; 0x1a
30010480:	eb000237 	bl	30010d64 <hal_io32_write>
30010484:	e8bd4010 	pop	{r4, lr}
30010488:	e12fff1e 	bx	lr

3001048c <hal_uart0_putc>:
3001048c:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
30010490:	e24dd00c 	sub	sp, sp, #12	; 0xc
30010494:	e1a03000 	mov	r3, r0
30010498:	e5cd3007 	strb	r3, [sp, #7]
3001049c:	e3a00205 	mov	r0, #1342177280	; 0x50000000
300104a0:	e2800901 	add	r0, r0, #16384	; 0x4000
300104a4:	e2800010 	add	r0, r0, #16	; 0x10
300104a8:	eb000212 	bl	30010cf8 <hal_io32_read>
300104ac:	e1a03000 	mov	r3, r0
300104b0:	e2033004 	and	r3, r3, #4	; 0x4
300104b4:	e3530000 	cmp	r3, #0	; 0x0
300104b8:	0afffff7 	beq	3001049c <hal_uart0_putc+0x10>
300104bc:	e5dd3007 	ldrb	r3, [sp, #7]
300104c0:	e3a00205 	mov	r0, #1342177280	; 0x50000000
300104c4:	e2800901 	add	r0, r0, #16384	; 0x4000
300104c8:	e2800024 	add	r0, r0, #36	; 0x24
300104cc:	e1a01003 	mov	r1, r3
300104d0:	eb000223 	bl	30010d64 <hal_io32_write>
300104d4:	e28dd00c 	add	sp, sp, #12	; 0xc
300104d8:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
300104dc:	e12fff1e 	bx	lr

300104e0 <hal_uart_write>:
300104e0:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
300104e4:	e24dd01c 	sub	sp, sp, #28	; 0x1c
300104e8:	e58d000c 	str	r0, [sp, #12]
300104ec:	e58d1008 	str	r1, [sp, #8]
300104f0:	e58d2004 	str	r2, [sp, #4]
300104f4:	e59d3008 	ldr	r3, [sp, #8]
300104f8:	e58d3014 	str	r3, [sp, #20]
300104fc:	e28d3010 	add	r3, sp, #16	; 0x10
30010500:	e1a00003 	mov	r0, r3
30010504:	eb00016e 	bl	30010ac4 <hal_disableirq_savecpuflg>
30010508:	ea00000f 	b	3001054c <hal_uart_write+0x6c>
3001050c:	e59d3014 	ldr	r3, [sp, #20]
30010510:	e5d33000 	ldrb	r3, [r3]
30010514:	e59d000c 	ldr	r0, [sp, #12]
30010518:	e1a01003 	mov	r1, r3
3001051c:	eb000029 	bl	300105c8 <uart_send_char>
30010520:	e1a03000 	mov	r3, r0
30010524:	e3730001 	cmn	r3, #1	; 0x1
30010528:	1a000004 	bne	30010540 <hal_uart_write+0x60>
3001052c:	e59f0050 	ldr	r0, [pc, #80]	; 30010584 <hal_uart_write+0xa4>
30010530:	eb00027f 	bl	30010f34 <hal_sysdie>
30010534:	e3e03000 	mvn	r3, #0	; 0x0
30010538:	e58d3000 	str	r3, [sp]
3001053c:	ea00000b 	b	30010570 <hal_uart_write+0x90>
30010540:	e59d3014 	ldr	r3, [sp, #20]
30010544:	e2833001 	add	r3, r3, #1	; 0x1
30010548:	e58d3014 	str	r3, [sp, #20]
3001054c:	e59d3014 	ldr	r3, [sp, #20]
30010550:	e5d33000 	ldrb	r3, [r3]
30010554:	e3530000 	cmp	r3, #0	; 0x0
30010558:	1affffeb 	bne	3001050c <hal_uart_write+0x2c>
3001055c:	e28d3010 	add	r3, sp, #16	; 0x10
30010560:	e1a00003 	mov	r0, r3
30010564:	eb000164 	bl	30010afc <hal_enableirq_restcpuflg>
30010568:	e3a03000 	mov	r3, #0	; 0x0
3001056c:	e58d3000 	str	r3, [sp]
30010570:	e59d3000 	ldr	r3, [sp]
30010574:	e1a00003 	mov	r0, r3
30010578:	e28dd01c 	add	sp, sp, #28	; 0x1c
3001057c:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
30010580:	e12fff1e 	bx	lr
30010584:	30012868 	.word	0x30012868

30010588 <hal_uart_read>:
30010588:	e24dd010 	sub	sp, sp, #16	; 0x10
3001058c:	e58d000c 	str	r0, [sp, #12]
30010590:	e58d1008 	str	r1, [sp, #8]
30010594:	e58d2004 	str	r2, [sp, #4]
30010598:	e3a03000 	mov	r3, #0	; 0x0
3001059c:	e1a00003 	mov	r0, r3
300105a0:	e28dd010 	add	sp, sp, #16	; 0x10
300105a4:	e12fff1e 	bx	lr

300105a8 <hal_uart_ioctrl>:
300105a8:	e24dd010 	sub	sp, sp, #16	; 0x10
300105ac:	e58d000c 	str	r0, [sp, #12]
300105b0:	e58d1008 	str	r1, [sp, #8]
300105b4:	e58d2004 	str	r2, [sp, #4]
300105b8:	e3a03000 	mov	r3, #0	; 0x0
300105bc:	e1a00003 	mov	r0, r3
300105c0:	e28dd010 	add	sp, sp, #16	; 0x10
300105c4:	e12fff1e 	bx	lr

300105c8 <uart_send_char>:
300105c8:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
300105cc:	e24dd01c 	sub	sp, sp, #28	; 0x1c
300105d0:	e58d000c 	str	r0, [sp, #12]
300105d4:	e1a03001 	mov	r3, r1
300105d8:	e5cd300b 	strb	r3, [sp, #11]
300105dc:	e3a03000 	mov	r3, #0	; 0x0
300105e0:	e58d3014 	str	r3, [sp, #20]
300105e4:	e59d300c 	ldr	r3, [sp, #12]
300105e8:	e3530000 	cmp	r3, #0	; 0x0
300105ec:	0a00000b 	beq	30010620 <uart_send_char+0x58>
300105f0:	e3e03000 	mvn	r3, #0	; 0x0
300105f4:	e58d3004 	str	r3, [sp, #4]
300105f8:	ea000016 	b	30010658 <uart_send_char+0x90>
300105fc:	e59d3014 	ldr	r3, [sp, #20]
30010600:	e3530601 	cmp	r3, #1048576	; 0x100000
30010604:	9a000002 	bls	30010614 <uart_send_char+0x4c>
30010608:	e3e03000 	mvn	r3, #0	; 0x0
3001060c:	e58d3004 	str	r3, [sp, #4]
30010610:	ea000010 	b	30010658 <uart_send_char+0x90>
30010614:	e59d3014 	ldr	r3, [sp, #20]
30010618:	e2833001 	add	r3, r3, #1	; 0x1
3001061c:	e58d3014 	str	r3, [sp, #20]
30010620:	e3a00205 	mov	r0, #1342177280	; 0x50000000
30010624:	e2800010 	add	r0, r0, #16	; 0x10
30010628:	eb0001b2 	bl	30010cf8 <hal_io32_read>
3001062c:	e1a03000 	mov	r3, r0
30010630:	e2033004 	and	r3, r3, #4	; 0x4
30010634:	e3530000 	cmp	r3, #0	; 0x0
30010638:	0affffef 	beq	300105fc <uart_send_char+0x34>
3001063c:	e5dd300b 	ldrb	r3, [sp, #11]
30010640:	e3a00205 	mov	r0, #1342177280	; 0x50000000
30010644:	e2800020 	add	r0, r0, #32	; 0x20
30010648:	e1a01003 	mov	r1, r3
3001064c:	eb0001c4 	bl	30010d64 <hal_io32_write>
30010650:	e3a03000 	mov	r3, #0	; 0x0
30010654:	e58d3004 	str	r3, [sp, #4]
30010658:	e59d3004 	ldr	r3, [sp, #4]
3001065c:	e1a00003 	mov	r0, r3
30010660:	e28dd01c 	add	sp, sp, #28	; 0x1c
30010664:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
30010668:	e12fff1e 	bx	lr

3001066c <uart_receive_char>:
3001066c:	e24dd008 	sub	sp, sp, #8	; 0x8
30010670:	e58d0004 	str	r0, [sp, #4]
30010674:	e58d1000 	str	r1, [sp]
30010678:	e3a03000 	mov	r3, #0	; 0x0
3001067c:	e1a00003 	mov	r0, r3
30010680:	e28dd008 	add	sp, sp, #8	; 0x8
30010684:	e12fff1e 	bx	lr

30010688 <printfk>:
30010688:	e92d000f 	push	{r0, r1, r2, r3}
3001068c:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
30010690:	e24ddf83 	sub	sp, sp, #524	; 0x20c
30010694:	e28d3f85 	add	r3, sp, #532	; 0x214
30010698:	e58d3000 	str	r3, [sp]
3001069c:	e28d3004 	add	r3, sp, #4	; 0x4
300106a0:	e1a00003 	mov	r0, r3
300106a4:	eb00011b 	bl	30010b18 <hal_disableirqfiq_savecpuflg>
300106a8:	e28d3008 	add	r3, sp, #8	; 0x8
300106ac:	e1a00003 	mov	r0, r3
300106b0:	e59d1210 	ldr	r1, [sp, #528]
300106b4:	e59d2000 	ldr	r2, [sp]
300106b8:	eb000021 	bl	30010744 <vsprintfk>
300106bc:	e28d3008 	add	r3, sp, #8	; 0x8
300106c0:	e3a00000 	mov	r0, #0	; 0x0
300106c4:	e1a01003 	mov	r1, r3
300106c8:	e3a02000 	mov	r2, #0	; 0x0
300106cc:	ebffff83 	bl	300104e0 <hal_uart_write>
300106d0:	e28d3004 	add	r3, sp, #4	; 0x4
300106d4:	e1a00003 	mov	r0, r3
300106d8:	eb000119 	bl	30010b44 <hal_enableirqfiq_restcpuflg>
300106dc:	e28ddf83 	add	sp, sp, #524	; 0x20c
300106e0:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
300106e4:	e28dd010 	add	sp, sp, #16	; 0x10
300106e8:	e12fff1e 	bx	lr

300106ec <strcopyk>:
300106ec:	e24dd008 	sub	sp, sp, #8	; 0x8
300106f0:	e58d0004 	str	r0, [sp, #4]
300106f4:	e58d1000 	str	r1, [sp]
300106f8:	ea000009 	b	30010724 <strcopyk+0x38>
300106fc:	e59d3000 	ldr	r3, [sp]
30010700:	e5d33000 	ldrb	r3, [r3]
30010704:	e59d2004 	ldr	r2, [sp, #4]
30010708:	e5c23000 	strb	r3, [r2]
3001070c:	e59d3004 	ldr	r3, [sp, #4]
30010710:	e2833001 	add	r3, r3, #1	; 0x1
30010714:	e58d3004 	str	r3, [sp, #4]
30010718:	e59d3000 	ldr	r3, [sp]
3001071c:	e2833001 	add	r3, r3, #1	; 0x1
30010720:	e58d3000 	str	r3, [sp]
30010724:	e59d3000 	ldr	r3, [sp]
30010728:	e5d33000 	ldrb	r3, [r3]
3001072c:	e3530000 	cmp	r3, #0	; 0x0
30010730:	1afffff1 	bne	300106fc <strcopyk+0x10>
30010734:	e59d3004 	ldr	r3, [sp, #4]
30010738:	e1a00003 	mov	r0, r3
3001073c:	e28dd008 	add	sp, sp, #8	; 0x8
30010740:	e12fff1e 	bx	lr

30010744 <vsprintfk>:
30010744:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
30010748:	e24dd01c 	sub	sp, sp, #28	; 0x1c
3001074c:	e58d000c 	str	r0, [sp, #12]
30010750:	e58d1008 	str	r1, [sp, #8]
30010754:	e58d2004 	str	r2, [sp, #4]
30010758:	e59d300c 	ldr	r3, [sp, #12]
3001075c:	e58d3014 	str	r3, [sp, #20]
30010760:	e59d3004 	ldr	r3, [sp, #4]
30010764:	e58d3010 	str	r3, [sp, #16]
30010768:	ea000049 	b	30010894 <vsprintfk+0x150>
3001076c:	e59d3008 	ldr	r3, [sp, #8]
30010770:	e5d33000 	ldrb	r3, [r3]
30010774:	e3530025 	cmp	r3, #37	; 0x25
30010778:	0a00000a 	beq	300107a8 <vsprintfk+0x64>
3001077c:	e59d3008 	ldr	r3, [sp, #8]
30010780:	e5d33000 	ldrb	r3, [r3]
30010784:	e59d2014 	ldr	r2, [sp, #20]
30010788:	e5c23000 	strb	r3, [r2]
3001078c:	e59d3014 	ldr	r3, [sp, #20]
30010790:	e2833001 	add	r3, r3, #1	; 0x1
30010794:	e58d3014 	str	r3, [sp, #20]
30010798:	e59d3008 	ldr	r3, [sp, #8]
3001079c:	e2833001 	add	r3, r3, #1	; 0x1
300107a0:	e58d3008 	str	r3, [sp, #8]
300107a4:	ea00003a 	b	30010894 <vsprintfk+0x150>
300107a8:	e59d3008 	ldr	r3, [sp, #8]
300107ac:	e2833001 	add	r3, r3, #1	; 0x1
300107b0:	e58d3008 	str	r3, [sp, #8]
300107b4:	e59d3008 	ldr	r3, [sp, #8]
300107b8:	e5d33000 	ldrb	r3, [r3]
300107bc:	e58d3000 	str	r3, [sp]
300107c0:	e59d3000 	ldr	r3, [sp]
300107c4:	e3530073 	cmp	r3, #115	; 0x73
300107c8:	0a000024 	beq	30010860 <vsprintfk+0x11c>
300107cc:	e59d3000 	ldr	r3, [sp]
300107d0:	e3530078 	cmp	r3, #120	; 0x78
300107d4:	0a000003 	beq	300107e8 <vsprintfk+0xa4>
300107d8:	e59d3000 	ldr	r3, [sp]
300107dc:	e3530064 	cmp	r3, #100	; 0x64
300107e0:	0a00000f 	beq	30010824 <vsprintfk+0xe0>
300107e4:	ea00002a 	b	30010894 <vsprintfk+0x150>
300107e8:	e59d2010 	ldr	r2, [sp, #16]
300107ec:	e2823004 	add	r3, r2, #4	; 0x4
300107f0:	e58d3010 	str	r3, [sp, #16]
300107f4:	e1a03002 	mov	r3, r2
300107f8:	e5933000 	ldr	r3, [r3]
300107fc:	e59d0014 	ldr	r0, [sp, #20]
30010800:	e1a01003 	mov	r1, r3
30010804:	e3a02010 	mov	r2, #16	; 0x10
30010808:	eb00002b 	bl	300108bc <numberk>
3001080c:	e1a03000 	mov	r3, r0
30010810:	e58d3014 	str	r3, [sp, #20]
30010814:	e59d3008 	ldr	r3, [sp, #8]
30010818:	e2833001 	add	r3, r3, #1	; 0x1
3001081c:	e58d3008 	str	r3, [sp, #8]
30010820:	ea00001b 	b	30010894 <vsprintfk+0x150>
30010824:	e59d2010 	ldr	r2, [sp, #16]
30010828:	e2823004 	add	r3, r2, #4	; 0x4
3001082c:	e58d3010 	str	r3, [sp, #16]
30010830:	e1a03002 	mov	r3, r2
30010834:	e5933000 	ldr	r3, [r3]
30010838:	e59d0014 	ldr	r0, [sp, #20]
3001083c:	e1a01003 	mov	r1, r3
30010840:	e3a0200a 	mov	r2, #10	; 0xa
30010844:	eb00001c 	bl	300108bc <numberk>
30010848:	e1a03000 	mov	r3, r0
3001084c:	e58d3014 	str	r3, [sp, #20]
30010850:	e59d3008 	ldr	r3, [sp, #8]
30010854:	e2833001 	add	r3, r3, #1	; 0x1
30010858:	e58d3008 	str	r3, [sp, #8]
3001085c:	ea00000c 	b	30010894 <vsprintfk+0x150>
30010860:	e59d2010 	ldr	r2, [sp, #16]
30010864:	e2823004 	add	r3, r2, #4	; 0x4
30010868:	e58d3010 	str	r3, [sp, #16]
3001086c:	e1a03002 	mov	r3, r2
30010870:	e5933000 	ldr	r3, [r3]
30010874:	e59d0014 	ldr	r0, [sp, #20]
30010878:	e1a01003 	mov	r1, r3
3001087c:	ebffff9a 	bl	300106ec <strcopyk>
30010880:	e1a03000 	mov	r3, r0
30010884:	e58d3014 	str	r3, [sp, #20]
30010888:	e59d3008 	ldr	r3, [sp, #8]
3001088c:	e2833001 	add	r3, r3, #1	; 0x1
30010890:	e58d3008 	str	r3, [sp, #8]
30010894:	e59d3008 	ldr	r3, [sp, #8]
30010898:	e5d33000 	ldrb	r3, [r3]
3001089c:	e3530000 	cmp	r3, #0	; 0x0
300108a0:	1affffb1 	bne	3001076c <vsprintfk+0x28>
300108a4:	e59d3014 	ldr	r3, [sp, #20]
300108a8:	e3a02000 	mov	r2, #0	; 0x0
300108ac:	e5c32000 	strb	r2, [r3]
300108b0:	e28dd01c 	add	sp, sp, #28	; 0x1c
300108b4:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
300108b8:	e12fff1e 	bx	lr

300108bc <numberk>:
300108bc:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
300108c0:	e24dd03c 	sub	sp, sp, #60	; 0x3c
300108c4:	e58d000c 	str	r0, [sp, #12]
300108c8:	e58d1008 	str	r1, [sp, #8]
300108cc:	e58d2004 	str	r2, [sp, #4]
300108d0:	e28d2014 	add	r2, sp, #20	; 0x14
300108d4:	e58d2000 	str	r2, [sp]
300108d8:	e59d3000 	ldr	r3, [sp]
300108dc:	e2833024 	add	r3, r3, #36	; 0x24
300108e0:	e58d3000 	str	r3, [sp]
300108e4:	e59d2000 	ldr	r2, [sp]
300108e8:	e2422001 	sub	r2, r2, #1	; 0x1
300108ec:	e58d2000 	str	r2, [sp]
300108f0:	e3a03000 	mov	r3, #0	; 0x0
300108f4:	e59d2000 	ldr	r2, [sp]
300108f8:	e5c23000 	strb	r3, [r2]
300108fc:	e59d3008 	ldr	r3, [sp, #8]
30010900:	e3530000 	cmp	r3, #0	; 0x0
30010904:	1a000006 	bne	30010924 <numberk+0x68>
30010908:	e59d3000 	ldr	r3, [sp]
3001090c:	e2433001 	sub	r3, r3, #1	; 0x1
30010910:	e58d3000 	str	r3, [sp]
30010914:	e3a03030 	mov	r3, #48	; 0x30
30010918:	e59d2000 	ldr	r2, [sp]
3001091c:	e5c23000 	strb	r3, [r2]
30010920:	ea000022 	b	300109b0 <numberk+0xf4>
30010924:	e59d3000 	ldr	r3, [sp]
30010928:	e2433001 	sub	r3, r3, #1	; 0x1
3001092c:	e58d3000 	str	r3, [sp]
30010930:	e59d2004 	ldr	r2, [sp, #4]
30010934:	e59d3008 	ldr	r3, [sp, #8]
30010938:	e1a00003 	mov	r0, r3
3001093c:	e1a01002 	mov	r1, r2
30010940:	eb0003f1 	bl	3001190c <__aeabi_uidivmod>
30010944:	e1a03001 	mov	r3, r1
30010948:	e1a02003 	mov	r2, r3
3001094c:	e59f3080 	ldr	r3, [pc, #128]	; 300109d4 <numberk+0x118>
30010950:	e7d33002 	ldrb	r3, [r3, r2]
30010954:	e59d2000 	ldr	r2, [sp]
30010958:	e5c23000 	strb	r3, [r2]
3001095c:	e59d2004 	ldr	r2, [sp, #4]
30010960:	e59d3008 	ldr	r3, [sp, #8]
30010964:	e1a00003 	mov	r0, r3
30010968:	e1a01002 	mov	r1, r2
3001096c:	eb00036b 	bl	30011720 <__aeabi_uidiv>
30010970:	e1a03000 	mov	r3, r0
30010974:	e58d3008 	str	r3, [sp, #8]
30010978:	e59d3008 	ldr	r3, [sp, #8]
3001097c:	e3530000 	cmp	r3, #0	; 0x0
30010980:	1affffe7 	bne	30010924 <numberk+0x68>
30010984:	ea000009 	b	300109b0 <numberk+0xf4>
30010988:	e59d2000 	ldr	r2, [sp]
3001098c:	e5d23000 	ldrb	r3, [r2]
30010990:	e59d200c 	ldr	r2, [sp, #12]
30010994:	e5c23000 	strb	r3, [r2]
30010998:	e59d300c 	ldr	r3, [sp, #12]
3001099c:	e2833001 	add	r3, r3, #1	; 0x1
300109a0:	e58d300c 	str	r3, [sp, #12]
300109a4:	e59d3000 	ldr	r3, [sp]
300109a8:	e2833001 	add	r3, r3, #1	; 0x1
300109ac:	e58d3000 	str	r3, [sp]
300109b0:	e59d2000 	ldr	r2, [sp]
300109b4:	e5d23000 	ldrb	r3, [r2]
300109b8:	e3530000 	cmp	r3, #0	; 0x0
300109bc:	1afffff1 	bne	30010988 <numberk+0xcc>
300109c0:	e59d300c 	ldr	r3, [sp, #12]
300109c4:	e1a00003 	mov	r0, r3
300109c8:	e28dd03c 	add	sp, sp, #60	; 0x3c
300109cc:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
300109d0:	e12fff1e 	bx	lr
300109d4:	30012874 	.word	0x30012874

300109d8 <char_write_uart>:
300109d8:	e24dd010 	sub	sp, sp, #16	; 0x10
300109dc:	e58d0004 	str	r0, [sp, #4]
300109e0:	e59d3004 	ldr	r3, [sp, #4]
300109e4:	e58d300c 	str	r3, [sp, #12]
300109e8:	ea000002 	b	300109f8 <char_write_uart+0x20>
300109ec:	e59d300c 	ldr	r3, [sp, #12]
300109f0:	e2833001 	add	r3, r3, #1	; 0x1
300109f4:	e58d300c 	str	r3, [sp, #12]
300109f8:	e59d300c 	ldr	r3, [sp, #12]
300109fc:	e5d33000 	ldrb	r3, [r3]
30010a00:	e3530000 	cmp	r3, #0	; 0x0
30010a04:	1afffff8 	bne	300109ec <char_write_uart+0x14>
30010a08:	e28dd010 	add	sp, sp, #16	; 0x10
30010a0c:	e12fff1e 	bx	lr

30010a10 <hal_disable_fiq>:
30010a10:	e10f0000 	mrs	r0, CPSR
30010a14:	e3800040 	orr	r0, r0, #64	; 0x40
30010a18:	e129f000 	msr	CPSR_fc, r0
30010a1c:	e12fff1e 	bx	lr

30010a20 <hal_enable_fiq>:
30010a20:	e10f0000 	mrs	r0, CPSR
30010a24:	e3c00040 	bic	r0, r0, #64	; 0x40
30010a28:	e129f000 	msr	CPSR_fc, r0
30010a2c:	e12fff1e 	bx	lr

30010a30 <hal_disable_irq>:
30010a30:	e10f0000 	mrs	r0, CPSR
30010a34:	e3800080 	orr	r0, r0, #128	; 0x80
30010a38:	e129f000 	msr	CPSR_fc, r0
30010a3c:	e12fff1e 	bx	lr

30010a40 <hal_enable_irq>:
30010a40:	e10f0000 	mrs	r0, CPSR
30010a44:	e3c00080 	bic	r0, r0, #128	; 0x80
30010a48:	e129f000 	msr	CPSR_fc, r0
30010a4c:	e12fff1e 	bx	lr

30010a50 <hal_disable_irqfiq>:
30010a50:	e10f0000 	mrs	r0, CPSR
30010a54:	e38000c0 	orr	r0, r0, #192	; 0xc0
30010a58:	e129f000 	msr	CPSR_fc, r0
30010a5c:	e12fff1e 	bx	lr

30010a60 <hal_enable_irqfiq>:
30010a60:	e10f0000 	mrs	r0, CPSR
30010a64:	e3c000c0 	bic	r0, r0, #192	; 0xc0
30010a68:	e129f000 	msr	CPSR_fc, r0
30010a6c:	e12fff1e 	bx	lr

30010a70 <hal_disablefiq_savecpuflg>:
30010a70:	e52d7004 	push	{r7}		; (str r7, [sp, #-4]!)
30010a74:	e24dd014 	sub	sp, sp, #20	; 0x14
30010a78:	e58d0004 	str	r0, [sp, #4]
30010a7c:	e10f7000 	mrs	r7, CPSR
30010a80:	e1a03007 	mov	r3, r7
30010a84:	e3877040 	orr	r7, r7, #64	; 0x40
30010a88:	e129f007 	msr	CPSR_fc, r7
30010a8c:	e58d300c 	str	r3, [sp, #12]
30010a90:	e59d2004 	ldr	r2, [sp, #4]
30010a94:	e59d300c 	ldr	r3, [sp, #12]
30010a98:	e5823000 	str	r3, [r2]
30010a9c:	e28dd014 	add	sp, sp, #20	; 0x14
30010aa0:	e8bd0080 	pop	{r7}
30010aa4:	e12fff1e 	bx	lr

30010aa8 <hal_enablefiq_restcpuflg>:
30010aa8:	e24dd008 	sub	sp, sp, #8	; 0x8
30010aac:	e58d0004 	str	r0, [sp, #4]
30010ab0:	e59d3004 	ldr	r3, [sp, #4]
30010ab4:	e5933000 	ldr	r3, [r3]
30010ab8:	e129f003 	msr	CPSR_fc, r3
30010abc:	e28dd008 	add	sp, sp, #8	; 0x8
30010ac0:	e12fff1e 	bx	lr

30010ac4 <hal_disableirq_savecpuflg>:
30010ac4:	e52d7004 	push	{r7}		; (str r7, [sp, #-4]!)
30010ac8:	e24dd014 	sub	sp, sp, #20	; 0x14
30010acc:	e58d0004 	str	r0, [sp, #4]
30010ad0:	e10f7000 	mrs	r7, CPSR
30010ad4:	e1a03007 	mov	r3, r7
30010ad8:	e3877080 	orr	r7, r7, #128	; 0x80
30010adc:	e129f007 	msr	CPSR_fc, r7
30010ae0:	e58d300c 	str	r3, [sp, #12]
30010ae4:	e59d2004 	ldr	r2, [sp, #4]
30010ae8:	e59d300c 	ldr	r3, [sp, #12]
30010aec:	e5823000 	str	r3, [r2]
30010af0:	e28dd014 	add	sp, sp, #20	; 0x14
30010af4:	e8bd0080 	pop	{r7}
30010af8:	e12fff1e 	bx	lr

30010afc <hal_enableirq_restcpuflg>:
30010afc:	e24dd008 	sub	sp, sp, #8	; 0x8
30010b00:	e58d0004 	str	r0, [sp, #4]
30010b04:	e59d3004 	ldr	r3, [sp, #4]
30010b08:	e5933000 	ldr	r3, [r3]
30010b0c:	e129f003 	msr	CPSR_fc, r3
30010b10:	e28dd008 	add	sp, sp, #8	; 0x8
30010b14:	e12fff1e 	bx	lr

30010b18 <hal_disableirqfiq_savecpuflg>:
30010b18:	e24dd010 	sub	sp, sp, #16	; 0x10
30010b1c:	e58d0004 	str	r0, [sp, #4]
30010b20:	e10f7000 	mrs	r7, CPSR
30010b24:	e1a03007 	mov	r3, r7
30010b28:	e38770c0 	orr	r7, r7, #192	; 0xc0
30010b2c:	e58d300c 	str	r3, [sp, #12]
30010b30:	e59d2004 	ldr	r2, [sp, #4]
30010b34:	e59d300c 	ldr	r3, [sp, #12]
30010b38:	e5823000 	str	r3, [r2]
30010b3c:	e28dd010 	add	sp, sp, #16	; 0x10
30010b40:	e12fff1e 	bx	lr

30010b44 <hal_enableirqfiq_restcpuflg>:
30010b44:	e24dd008 	sub	sp, sp, #8	; 0x8
30010b48:	e58d0004 	str	r0, [sp, #4]
30010b4c:	e59d3004 	ldr	r3, [sp, #4]
30010b50:	e5933000 	ldr	r3, [r3]
30010b54:	e129f003 	msr	CPSR_fc, r3
30010b58:	e28dd008 	add	sp, sp, #8	; 0x8
30010b5c:	e12fff1e 	bx	lr

30010b60 <hal_read_currmodesp>:
30010b60:	e24dd008 	sub	sp, sp, #8	; 0x8
30010b64:	e3a03000 	mov	r3, #0	; 0x0
30010b68:	e58d3004 	str	r3, [sp, #4]
30010b6c:	e1a0300d 	mov	r3, sp
30010b70:	e58d3004 	str	r3, [sp, #4]
30010b74:	e59d3004 	ldr	r3, [sp, #4]
30010b78:	e1a00003 	mov	r0, r3
30010b7c:	e28dd008 	add	sp, sp, #8	; 0x8
30010b80:	e12fff1e 	bx	lr

30010b84 <hal_read_cpuflg>:
30010b84:	e24dd008 	sub	sp, sp, #8	; 0x8
30010b88:	e10f3000 	mrs	r3, CPSR
30010b8c:	e58d3004 	str	r3, [sp, #4]
30010b90:	e59d3004 	ldr	r3, [sp, #4]
30010b94:	e1a00003 	mov	r0, r3
30010b98:	e28dd008 	add	sp, sp, #8	; 0x8
30010b9c:	e12fff1e 	bx	lr

30010ba0 <hal_write_cpuflg>:
30010ba0:	e24dd008 	sub	sp, sp, #8	; 0x8
30010ba4:	e58d0004 	str	r0, [sp, #4]
30010ba8:	e59d3004 	ldr	r3, [sp, #4]
30010bac:	e129f003 	msr	CPSR_fc, r3
30010bb0:	e28dd008 	add	sp, sp, #8	; 0x8
30010bb4:	e12fff1e 	bx	lr

30010bb8 <hal_swhmodset_sp_rscurmod>:
30010bb8:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
30010bbc:	e24dd014 	sub	sp, sp, #20	; 0x14
30010bc0:	e58d0004 	str	r0, [sp, #4]
30010bc4:	e58d1000 	str	r1, [sp]
30010bc8:	ebffffed 	bl	30010b84 <hal_read_cpuflg>
30010bcc:	e1a03000 	mov	r3, r0
30010bd0:	e58d300c 	str	r3, [sp, #12]
30010bd4:	e59d300c 	ldr	r3, [sp, #12]
30010bd8:	e58d3008 	str	r3, [sp, #8]
30010bdc:	e59d300c 	ldr	r3, [sp, #12]
30010be0:	e3c3301f 	bic	r3, r3, #31	; 0x1f
30010be4:	e58d300c 	str	r3, [sp, #12]
30010be8:	e59d200c 	ldr	r2, [sp, #12]
30010bec:	e59d3004 	ldr	r3, [sp, #4]
30010bf0:	e1823003 	orr	r3, r2, r3
30010bf4:	e58d300c 	str	r3, [sp, #12]
30010bf8:	e59d100c 	ldr	r1, [sp, #12]
30010bfc:	e59d2000 	ldr	r2, [sp]
30010c00:	e59d3008 	ldr	r3, [sp, #8]
30010c04:	e121f001 	msr	CPSR_c, r1
30010c08:	e1a0d002 	mov	sp, r2
30010c0c:	e129f003 	msr	CPSR_fc, r3
30010c10:	e28dd014 	add	sp, sp, #20	; 0x14
30010c14:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
30010c18:	e12fff1e 	bx	lr

30010c1c <hal_read_scpuflg>:
30010c1c:	e24dd008 	sub	sp, sp, #8	; 0x8
30010c20:	e14f3000 	mrs	r3, SPSR
30010c24:	e58d3004 	str	r3, [sp, #4]
30010c28:	e59d3004 	ldr	r3, [sp, #4]
30010c2c:	e1a00003 	mov	r0, r3
30010c30:	e28dd008 	add	sp, sp, #8	; 0x8
30010c34:	e12fff1e 	bx	lr

30010c38 <hal_write_scpuflg>:
30010c38:	e24dd008 	sub	sp, sp, #8	; 0x8
30010c3c:	e58d0004 	str	r0, [sp, #4]
30010c40:	e59d3004 	ldr	r3, [sp, #4]
30010c44:	e129f003 	msr	CPSR_fc, r3
30010c48:	e28dd008 	add	sp, sp, #8	; 0x8
30010c4c:	e12fff1e 	bx	lr

30010c50 <hal_cpumode_switch>:
30010c50:	e52d7004 	push	{r7}		; (str r7, [sp, #-4]!)
30010c54:	e24dd00c 	sub	sp, sp, #12	; 0xc
30010c58:	e58d0004 	str	r0, [sp, #4]
30010c5c:	e59d3004 	ldr	r3, [sp, #4]
30010c60:	e10f7000 	mrs	r7, CPSR
30010c64:	e1877003 	orr	r7, r7, r3
30010c68:	e129f007 	msr	CPSR_fc, r7
30010c6c:	e28dd00c 	add	sp, sp, #12	; 0xc
30010c70:	e8bd0080 	pop	{r7}
30010c74:	e12fff1e 	bx	lr

30010c78 <hal_cpumodeswitch_retoldmode>:
30010c78:	e52d7004 	push	{r7}		; (str r7, [sp, #-4]!)
30010c7c:	e24dd014 	sub	sp, sp, #20	; 0x14
30010c80:	e58d0004 	str	r0, [sp, #4]
30010c84:	e59d3004 	ldr	r3, [sp, #4]
30010c88:	e10f7000 	mrs	r7, CPSR
30010c8c:	e1a03007 	mov	r3, r7
30010c90:	e1877003 	orr	r7, r7, r3
30010c94:	e129f007 	msr	CPSR_fc, r7
30010c98:	e58d300c 	str	r3, [sp, #12]
30010c9c:	e59d300c 	ldr	r3, [sp, #12]
30010ca0:	e1a00003 	mov	r0, r3
30010ca4:	e28dd014 	add	sp, sp, #20	; 0x14
30010ca8:	e8bd0080 	pop	{r7}
30010cac:	e12fff1e 	bx	lr

30010cb0 <hal_io8_read>:
30010cb0:	e24dd010 	sub	sp, sp, #16	; 0x10
30010cb4:	e58d0004 	str	r0, [sp, #4]
30010cb8:	e59d3004 	ldr	r3, [sp, #4]
30010cbc:	e5d33000 	ldrb	r3, [r3]
30010cc0:	e5cd300f 	strb	r3, [sp, #15]
30010cc4:	e5dd300f 	ldrb	r3, [sp, #15]
30010cc8:	e1a00003 	mov	r0, r3
30010ccc:	e28dd010 	add	sp, sp, #16	; 0x10
30010cd0:	e12fff1e 	bx	lr

30010cd4 <hal_io16_read>:
30010cd4:	e24dd010 	sub	sp, sp, #16	; 0x10
30010cd8:	e58d0004 	str	r0, [sp, #4]
30010cdc:	e59d3004 	ldr	r3, [sp, #4]
30010ce0:	e1d330b0 	ldrh	r3, [r3]
30010ce4:	e1cd30be 	strh	r3, [sp, #14]
30010ce8:	e1dd30be 	ldrh	r3, [sp, #14]
30010cec:	e1a00003 	mov	r0, r3
30010cf0:	e28dd010 	add	sp, sp, #16	; 0x10
30010cf4:	e12fff1e 	bx	lr

30010cf8 <hal_io32_read>:
30010cf8:	e24dd010 	sub	sp, sp, #16	; 0x10
30010cfc:	e58d0004 	str	r0, [sp, #4]
30010d00:	e59d3004 	ldr	r3, [sp, #4]
30010d04:	e5933000 	ldr	r3, [r3]
30010d08:	e58d300c 	str	r3, [sp, #12]
30010d0c:	e59d300c 	ldr	r3, [sp, #12]
30010d10:	e1a00003 	mov	r0, r3
30010d14:	e28dd010 	add	sp, sp, #16	; 0x10
30010d18:	e12fff1e 	bx	lr

30010d1c <hal_io8_write>:
30010d1c:	e24dd008 	sub	sp, sp, #8	; 0x8
30010d20:	e58d0004 	str	r0, [sp, #4]
30010d24:	e1a03001 	mov	r3, r1
30010d28:	e5cd3003 	strb	r3, [sp, #3]
30010d2c:	e5dd2003 	ldrb	r2, [sp, #3]
30010d30:	e59d3004 	ldr	r3, [sp, #4]
30010d34:	e5c32000 	strb	r2, [r3]
30010d38:	e28dd008 	add	sp, sp, #8	; 0x8
30010d3c:	e12fff1e 	bx	lr

30010d40 <hal_io16_write>:
30010d40:	e24dd008 	sub	sp, sp, #8	; 0x8
30010d44:	e58d0004 	str	r0, [sp, #4]
30010d48:	e1a03001 	mov	r3, r1
30010d4c:	e1cd30b2 	strh	r3, [sp, #2]
30010d50:	e1dd20b2 	ldrh	r2, [sp, #2]
30010d54:	e59d3004 	ldr	r3, [sp, #4]
30010d58:	e1c320b0 	strh	r2, [r3]
30010d5c:	e28dd008 	add	sp, sp, #8	; 0x8
30010d60:	e12fff1e 	bx	lr

30010d64 <hal_io32_write>:
30010d64:	e24dd008 	sub	sp, sp, #8	; 0x8
30010d68:	e58d0004 	str	r0, [sp, #4]
30010d6c:	e58d1000 	str	r1, [sp]
30010d70:	e59d2000 	ldr	r2, [sp]
30010d74:	e59d3004 	ldr	r3, [sp, #4]
30010d78:	e5832000 	str	r2, [r3]
30010d7c:	e28dd008 	add	sp, sp, #8	; 0x8
30010d80:	e12fff1e 	bx	lr

30010d84 <hal_spinlock_init>:
30010d84:	e24dd008 	sub	sp, sp, #8	; 0x8
30010d88:	e58d0004 	str	r0, [sp, #4]
30010d8c:	e59d2004 	ldr	r2, [sp, #4]
30010d90:	e3a03000 	mov	r3, #0	; 0x0
30010d94:	e1023093 	swp	r3, r3, [r2]
30010d98:	e28dd008 	add	sp, sp, #8	; 0x8
30010d9c:	e12fff1e 	bx	lr

30010da0 <hal_spinlock_lock>:
30010da0:	e92d0180 	push	{r7, r8}
30010da4:	e24dd008 	sub	sp, sp, #8	; 0x8
30010da8:	e58d0004 	str	r0, [sp, #4]
30010dac:	e59d3004 	ldr	r3, [sp, #4]
30010db0:	e3a08001 	mov	r8, #1	; 0x1
30010db4:	e1037098 	swp	r7, r8, [r3]
30010db8:	e3570000 	cmp	r7, #0	; 0x0
30010dbc:	1afffffc 	bne	30010db4 <hal_spinlock_lock+0x14>
30010dc0:	e28dd008 	add	sp, sp, #8	; 0x8
30010dc4:	e8bd0180 	pop	{r7, r8}
30010dc8:	e12fff1e 	bx	lr

30010dcc <hal_spinlock_unlock>:
30010dcc:	e24dd008 	sub	sp, sp, #8	; 0x8
30010dd0:	e58d0004 	str	r0, [sp, #4]
30010dd4:	e59d2004 	ldr	r2, [sp, #4]
30010dd8:	e3a03000 	mov	r3, #0	; 0x0
30010ddc:	e1023093 	swp	r3, r3, [r2]
30010de0:	e28dd008 	add	sp, sp, #8	; 0x8
30010de4:	e12fff1e 	bx	lr

30010de8 <hal_spinlock_saveflg_cli>:
30010de8:	e92d0180 	push	{r7, r8}
30010dec:	e24dd010 	sub	sp, sp, #16	; 0x10
30010df0:	e58d0004 	str	r0, [sp, #4]
30010df4:	e58d1000 	str	r1, [sp]
30010df8:	e10f7000 	mrs	r7, CPSR
30010dfc:	e1a03007 	mov	r3, r7
30010e00:	e38770c0 	orr	r7, r7, #192	; 0xc0
30010e04:	e129f007 	msr	CPSR_fc, r7
30010e08:	e58d300c 	str	r3, [sp, #12]
30010e0c:	e59d2000 	ldr	r2, [sp]
30010e10:	e59d300c 	ldr	r3, [sp, #12]
30010e14:	e5823000 	str	r3, [r2]
30010e18:	e59d3004 	ldr	r3, [sp, #4]
30010e1c:	e3a08001 	mov	r8, #1	; 0x1
30010e20:	e1037098 	swp	r7, r8, [r3]
30010e24:	e3570000 	cmp	r7, #0	; 0x0
30010e28:	1afffffc 	bne	30010e20 <hal_spinlock_saveflg_cli+0x38>
30010e2c:	e28dd010 	add	sp, sp, #16	; 0x10
30010e30:	e8bd0180 	pop	{r7, r8}
30010e34:	e12fff1e 	bx	lr

30010e38 <hal_spinunlock_restflg_sti>:
30010e38:	e24dd008 	sub	sp, sp, #8	; 0x8
30010e3c:	e58d0004 	str	r0, [sp, #4]
30010e40:	e58d1000 	str	r1, [sp]
30010e44:	e59d2004 	ldr	r2, [sp, #4]
30010e48:	e3a03000 	mov	r3, #0	; 0x0
30010e4c:	e1023093 	swp	r3, r3, [r2]
30010e50:	e59d3000 	ldr	r3, [sp]
30010e54:	e5933000 	ldr	r3, [r3]
30010e58:	e129f003 	msr	CPSR_fc, r3
30010e5c:	e28dd008 	add	sp, sp, #8	; 0x8
30010e60:	e12fff1e 	bx	lr

30010e64 <hal_memset>:
30010e64:	e24dd018 	sub	sp, sp, #24	; 0x18
30010e68:	e58d000c 	str	r0, [sp, #12]
30010e6c:	e58d1008 	str	r1, [sp, #8]
30010e70:	e1a03002 	mov	r3, r2
30010e74:	e5cd3007 	strb	r3, [sp, #7]
30010e78:	e59d300c 	ldr	r3, [sp, #12]
30010e7c:	e58d3010 	str	r3, [sp, #16]
30010e80:	e3a03000 	mov	r3, #0	; 0x0
30010e84:	e58d3014 	str	r3, [sp, #20]
30010e88:	ea000007 	b	30010eac <hal_memset+0x48>
30010e8c:	e59d2010 	ldr	r2, [sp, #16]
30010e90:	e59d3014 	ldr	r3, [sp, #20]
30010e94:	e0822003 	add	r2, r2, r3
30010e98:	e5dd3007 	ldrb	r3, [sp, #7]
30010e9c:	e5c23000 	strb	r3, [r2]
30010ea0:	e59d3014 	ldr	r3, [sp, #20]
30010ea4:	e2833001 	add	r3, r3, #1	; 0x1
30010ea8:	e58d3014 	str	r3, [sp, #20]
30010eac:	e59d2014 	ldr	r2, [sp, #20]
30010eb0:	e59d3008 	ldr	r3, [sp, #8]
30010eb4:	e1520003 	cmp	r2, r3
30010eb8:	3afffff3 	bcc	30010e8c <hal_memset+0x28>
30010ebc:	e28dd018 	add	sp, sp, #24	; 0x18
30010ec0:	e12fff1e 	bx	lr

30010ec4 <hal_memcpy>:
30010ec4:	e24dd020 	sub	sp, sp, #32	; 0x20
30010ec8:	e58d000c 	str	r0, [sp, #12]
30010ecc:	e58d1008 	str	r1, [sp, #8]
30010ed0:	e58d2004 	str	r2, [sp, #4]
30010ed4:	e59d300c 	ldr	r3, [sp, #12]
30010ed8:	e58d3014 	str	r3, [sp, #20]
30010edc:	e59d3008 	ldr	r3, [sp, #8]
30010ee0:	e58d3018 	str	r3, [sp, #24]
30010ee4:	e3a03000 	mov	r3, #0	; 0x0
30010ee8:	e58d301c 	str	r3, [sp, #28]
30010eec:	ea00000a 	b	30010f1c <hal_memcpy+0x58>
30010ef0:	e59d2018 	ldr	r2, [sp, #24]
30010ef4:	e59d301c 	ldr	r3, [sp, #28]
30010ef8:	e0821003 	add	r1, r2, r3
30010efc:	e59d2014 	ldr	r2, [sp, #20]
30010f00:	e59d301c 	ldr	r3, [sp, #28]
30010f04:	e0823003 	add	r3, r2, r3
30010f08:	e5d33000 	ldrb	r3, [r3]
30010f0c:	e5c13000 	strb	r3, [r1]
30010f10:	e59d301c 	ldr	r3, [sp, #28]
30010f14:	e2833001 	add	r3, r3, #1	; 0x1
30010f18:	e58d301c 	str	r3, [sp, #28]
30010f1c:	e59d201c 	ldr	r2, [sp, #28]
30010f20:	e59d3004 	ldr	r3, [sp, #4]
30010f24:	e1520003 	cmp	r2, r3
30010f28:	3afffff0 	bcc	30010ef0 <hal_memcpy+0x2c>
30010f2c:	e28dd020 	add	sp, sp, #32	; 0x20
30010f30:	e12fff1e 	bx	lr

30010f34 <hal_sysdie>:
30010f34:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
30010f38:	e24dd00c 	sub	sp, sp, #12	; 0xc
30010f3c:	e58d0004 	str	r0, [sp, #4]
30010f40:	ebfffd3e 	bl	30010440 <init_uart0>
30010f44:	e59f0010 	ldr	r0, [pc, #16]	; 30010f5c <hal_sysdie+0x28>
30010f48:	e59d1004 	ldr	r1, [sp, #4]
30010f4c:	ebfffdcd 	bl	30010688 <printfk>
30010f50:	e28dd00c 	add	sp, sp, #12	; 0xc
30010f54:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
30010f58:	e12fff1e 	bx	lr
30010f5c:	30012888 	.word	0x30012888

30010f60 <hal_retn_cpuid>:
30010f60:	e3a03000 	mov	r3, #0	; 0x0
30010f64:	e1a00003 	mov	r0, r3
30010f68:	e12fff1e 	bx	lr

30010f6c <lmosemhal_start>:
30010f6c:	e92d4010 	push	{r4, lr}
30010f70:	e59f0008 	ldr	r0, [pc, #8]	; 30010f80 <lmosemhal_start+0x14>
30010f74:	ebffffee 	bl	30010f34 <hal_sysdie>
30010f78:	e8bd4010 	pop	{r4, lr}
30010f7c:	e12fff1e 	bx	lr
30010f80:	300128a0 	.word	0x300128a0

30010f84 <hal_disable_cache>:
30010f84:	e3a03a01 	mov	r3, #4096	; 0x1000
30010f88:	e2833004 	add	r3, r3, #4	; 0x4
30010f8c:	ee010f10 	mcr	15, 0, r0, cr1, cr0, {0}
30010f90:	e1800003 	orr	r0, r0, r3
30010f94:	ee010f10 	mcr	15, 0, r0, cr1, cr0, {0}
30010f98:	e12fff1e 	bx	lr

30010f9c <cp15_read_c5>:
30010f9c:	e24dd008 	sub	sp, sp, #8	; 0x8
30010fa0:	ee053f10 	mcr	15, 0, r3, cr5, cr0, {0}
30010fa4:	e58d3004 	str	r3, [sp, #4]
30010fa8:	e59d3004 	ldr	r3, [sp, #4]
30010fac:	e1a00003 	mov	r0, r3
30010fb0:	e28dd008 	add	sp, sp, #8	; 0x8
30010fb4:	e12fff1e 	bx	lr

30010fb8 <cp15_read_c6>:
30010fb8:	e24dd008 	sub	sp, sp, #8	; 0x8
30010fbc:	ee063f10 	mcr	15, 0, r3, cr6, cr0, {0}
30010fc0:	e58d3004 	str	r3, [sp, #4]
30010fc4:	e59d3004 	ldr	r3, [sp, #4]
30010fc8:	e1a00003 	mov	r0, r3
30010fcc:	e28dd008 	add	sp, sp, #8	; 0x8
30010fd0:	e12fff1e 	bx	lr

30010fd4 <hal_read_cp15regs>:
30010fd4:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
30010fd8:	e24dd014 	sub	sp, sp, #20	; 0x14
30010fdc:	e58d000c 	str	r0, [sp, #12]
30010fe0:	e59d300c 	ldr	r3, [sp, #12]
30010fe4:	e58d3004 	str	r3, [sp, #4]
30010fe8:	e59d3004 	ldr	r3, [sp, #4]
30010fec:	e3530005 	cmp	r3, #5	; 0x5
30010ff0:	0a000003 	beq	30011004 <hal_read_cp15regs+0x30>
30010ff4:	e59d3004 	ldr	r3, [sp, #4]
30010ff8:	e3530006 	cmp	r3, #6	; 0x6
30010ffc:	0a000004 	beq	30011014 <hal_read_cp15regs+0x40>
30011000:	ea000007 	b	30011024 <hal_read_cp15regs+0x50>
30011004:	ebffffe4 	bl	30010f9c <cp15_read_c5>
30011008:	e1a03000 	mov	r3, r0
3001100c:	e58d3008 	str	r3, [sp, #8]
30011010:	ea000005 	b	3001102c <hal_read_cp15regs+0x58>
30011014:	ebffffe7 	bl	30010fb8 <cp15_read_c6>
30011018:	e1a03000 	mov	r3, r0
3001101c:	e58d3008 	str	r3, [sp, #8]
30011020:	ea000001 	b	3001102c <hal_read_cp15regs+0x58>
30011024:	e3a03000 	mov	r3, #0	; 0x0
30011028:	e58d3008 	str	r3, [sp, #8]
3001102c:	e59d3008 	ldr	r3, [sp, #8]
30011030:	e1a00003 	mov	r0, r3
30011034:	e28dd014 	add	sp, sp, #20	; 0x14
30011038:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
3001103c:	e12fff1e 	bx	lr

30011040 <init_platform>:
30011040:	e92d4010 	push	{r4, lr}
30011044:	ebfffc21 	bl	300100d0 <s3c2440mmu_init>
30011048:	ebfffc6c 	bl	30010200 <s3c2440vector_init>
3001104c:	e8bd4010 	pop	{r4, lr}
30011050:	e12fff1e 	bx	lr

30011054 <hal_dbug_print_reg>:
30011054:	e92d4010 	push	{r4, lr}
30011058:	e24dd008 	sub	sp, sp, #8	; 0x8
3001105c:	e58d0004 	str	r0, [sp, #4]
30011060:	e59d3004 	ldr	r3, [sp, #4]
30011064:	e5933008 	ldr	r3, [r3, #8]
30011068:	e59f0198 	ldr	r0, [pc, #408]	; 30011208 <hal_dbug_print_reg+0x1b4>
3001106c:	e1a01003 	mov	r1, r3
30011070:	ebfffd84 	bl	30010688 <printfk>
30011074:	e59d3004 	ldr	r3, [sp, #4]
30011078:	e593300c 	ldr	r3, [r3, #12]
3001107c:	e59f0188 	ldr	r0, [pc, #392]	; 3001120c <hal_dbug_print_reg+0x1b8>
30011080:	e1a01003 	mov	r1, r3
30011084:	ebfffd7f 	bl	30010688 <printfk>
30011088:	e59d3004 	ldr	r3, [sp, #4]
3001108c:	e5933010 	ldr	r3, [r3, #16]
30011090:	e59f0178 	ldr	r0, [pc, #376]	; 30011210 <hal_dbug_print_reg+0x1bc>
30011094:	e1a01003 	mov	r1, r3
30011098:	ebfffd7a 	bl	30010688 <printfk>
3001109c:	e59d3004 	ldr	r3, [sp, #4]
300110a0:	e5933014 	ldr	r3, [r3, #20]
300110a4:	e59f0168 	ldr	r0, [pc, #360]	; 30011214 <hal_dbug_print_reg+0x1c0>
300110a8:	e1a01003 	mov	r1, r3
300110ac:	ebfffd75 	bl	30010688 <printfk>
300110b0:	e59d3004 	ldr	r3, [sp, #4]
300110b4:	e5933018 	ldr	r3, [r3, #24]
300110b8:	e59f0158 	ldr	r0, [pc, #344]	; 30011218 <hal_dbug_print_reg+0x1c4>
300110bc:	e1a01003 	mov	r1, r3
300110c0:	ebfffd70 	bl	30010688 <printfk>
300110c4:	e59d3004 	ldr	r3, [sp, #4]
300110c8:	e593301c 	ldr	r3, [r3, #28]
300110cc:	e59f0148 	ldr	r0, [pc, #328]	; 3001121c <hal_dbug_print_reg+0x1c8>
300110d0:	e1a01003 	mov	r1, r3
300110d4:	ebfffd6b 	bl	30010688 <printfk>
300110d8:	e59d3004 	ldr	r3, [sp, #4]
300110dc:	e5933020 	ldr	r3, [r3, #32]
300110e0:	e59f0138 	ldr	r0, [pc, #312]	; 30011220 <hal_dbug_print_reg+0x1cc>
300110e4:	e1a01003 	mov	r1, r3
300110e8:	ebfffd66 	bl	30010688 <printfk>
300110ec:	e59d3004 	ldr	r3, [sp, #4]
300110f0:	e5933024 	ldr	r3, [r3, #36]
300110f4:	e59f0128 	ldr	r0, [pc, #296]	; 30011224 <hal_dbug_print_reg+0x1d0>
300110f8:	e1a01003 	mov	r1, r3
300110fc:	ebfffd61 	bl	30010688 <printfk>
30011100:	e59d3004 	ldr	r3, [sp, #4]
30011104:	e5933028 	ldr	r3, [r3, #40]
30011108:	e59f0118 	ldr	r0, [pc, #280]	; 30011228 <hal_dbug_print_reg+0x1d4>
3001110c:	e1a01003 	mov	r1, r3
30011110:	ebfffd5c 	bl	30010688 <printfk>
30011114:	e59d3004 	ldr	r3, [sp, #4]
30011118:	e593302c 	ldr	r3, [r3, #44]
3001111c:	e59f0108 	ldr	r0, [pc, #264]	; 3001122c <hal_dbug_print_reg+0x1d8>
30011120:	e1a01003 	mov	r1, r3
30011124:	ebfffd57 	bl	30010688 <printfk>
30011128:	e59d3004 	ldr	r3, [sp, #4]
3001112c:	e5933030 	ldr	r3, [r3, #48]
30011130:	e59f00f8 	ldr	r0, [pc, #248]	; 30011230 <hal_dbug_print_reg+0x1dc>
30011134:	e1a01003 	mov	r1, r3
30011138:	ebfffd52 	bl	30010688 <printfk>
3001113c:	e59d3004 	ldr	r3, [sp, #4]
30011140:	e5933034 	ldr	r3, [r3, #52]
30011144:	e59f00e8 	ldr	r0, [pc, #232]	; 30011234 <hal_dbug_print_reg+0x1e0>
30011148:	e1a01003 	mov	r1, r3
3001114c:	ebfffd4d 	bl	30010688 <printfk>
30011150:	e59d3004 	ldr	r3, [sp, #4]
30011154:	e5933038 	ldr	r3, [r3, #56]
30011158:	e59f00d8 	ldr	r0, [pc, #216]	; 30011238 <hal_dbug_print_reg+0x1e4>
3001115c:	e1a01003 	mov	r1, r3
30011160:	ebfffd48 	bl	30010688 <printfk>
30011164:	e59d3004 	ldr	r3, [sp, #4]
30011168:	e593303c 	ldr	r3, [r3, #60]
3001116c:	e59f00c8 	ldr	r0, [pc, #200]	; 3001123c <hal_dbug_print_reg+0x1e8>
30011170:	e1a01003 	mov	r1, r3
30011174:	ebfffd43 	bl	30010688 <printfk>
30011178:	e59d3004 	ldr	r3, [sp, #4]
3001117c:	e5933040 	ldr	r3, [r3, #64]
30011180:	e59f00b8 	ldr	r0, [pc, #184]	; 30011240 <hal_dbug_print_reg+0x1ec>
30011184:	e1a01003 	mov	r1, r3
30011188:	ebfffd3e 	bl	30010688 <printfk>
3001118c:	e59d3004 	ldr	r3, [sp, #4]
30011190:	e5933044 	ldr	r3, [r3, #68]
30011194:	e59f00a8 	ldr	r0, [pc, #168]	; 30011244 <hal_dbug_print_reg+0x1f0>
30011198:	e1a01003 	mov	r1, r3
3001119c:	ebfffd39 	bl	30010688 <printfk>
300111a0:	e59d3004 	ldr	r3, [sp, #4]
300111a4:	e5933000 	ldr	r3, [r3]
300111a8:	e59f0098 	ldr	r0, [pc, #152]	; 30011248 <hal_dbug_print_reg+0x1f4>
300111ac:	e1a01003 	mov	r1, r3
300111b0:	ebfffd34 	bl	30010688 <printfk>
300111b4:	ebfffe69 	bl	30010b60 <hal_read_currmodesp>
300111b8:	e1a04000 	mov	r4, r0
300111bc:	e3a0044a 	mov	r0, #1241513984	; 0x4a000000
300111c0:	e2800010 	add	r0, r0, #16	; 0x10
300111c4:	ebfffecb 	bl	30010cf8 <hal_io32_read>
300111c8:	e1a03000 	mov	r3, r0
300111cc:	e59f0078 	ldr	r0, [pc, #120]	; 3001124c <hal_dbug_print_reg+0x1f8>
300111d0:	e1a01004 	mov	r1, r4
300111d4:	e1a02003 	mov	r2, r3
300111d8:	ebfffd2a 	bl	30010688 <printfk>
300111dc:	ebfffe68 	bl	30010b84 <hal_read_cpuflg>
300111e0:	e1a04000 	mov	r4, r0
300111e4:	ebffff5d 	bl	30010f60 <hal_retn_cpuid>
300111e8:	e1a03000 	mov	r3, r0
300111ec:	e59f005c 	ldr	r0, [pc, #92]	; 30011250 <hal_dbug_print_reg+0x1fc>
300111f0:	e1a01004 	mov	r1, r4
300111f4:	e1a02003 	mov	r2, r3
300111f8:	ebfffd22 	bl	30010688 <printfk>
300111fc:	e28dd008 	add	sp, sp, #8	; 0x8
30011200:	e8bd4010 	pop	{r4, lr}
30011204:	e12fff1e 	bx	lr
30011208:	300128b4 	.word	0x300128b4
3001120c:	300128c4 	.word	0x300128c4
30011210:	300128d4 	.word	0x300128d4
30011214:	300128e4 	.word	0x300128e4
30011218:	300128f4 	.word	0x300128f4
3001121c:	30012904 	.word	0x30012904
30011220:	30012914 	.word	0x30012914
30011224:	30012924 	.word	0x30012924
30011228:	30012934 	.word	0x30012934
3001122c:	30012944 	.word	0x30012944
30011230:	30012954 	.word	0x30012954
30011234:	30012968 	.word	0x30012968
30011238:	3001297c 	.word	0x3001297c
3001123c:	30012990 	.word	0x30012990
30011240:	300129a4 	.word	0x300129a4
30011244:	300129b8 	.word	0x300129b8
30011248:	300129c8 	.word	0x300129c8
3001124c:	300129dc 	.word	0x300129dc
30011250:	300129f8 	.word	0x300129f8

30011254 <hal_undefins_distr>:
30011254:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
30011258:	e24dd00c 	sub	sp, sp, #12	; 0xc
3001125c:	e58d0004 	str	r0, [sp, #4]
30011260:	e59f000c 	ldr	r0, [pc, #12]	; 30011274 <hal_undefins_distr+0x20>
30011264:	ebffff32 	bl	30010f34 <hal_sysdie>
30011268:	e28dd00c 	add	sp, sp, #12	; 0xc
3001126c:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
30011270:	e12fff1e 	bx	lr
30011274:	30012a18 	.word	0x30012a18

30011278 <hal_swi_distr>:
30011278:	e24dd010 	sub	sp, sp, #16	; 0x10
3001127c:	e58d0004 	str	r0, [sp, #4]
30011280:	e58d1000 	str	r1, [sp]
30011284:	e3a03000 	mov	r3, #0	; 0x0
30011288:	e58d300c 	str	r3, [sp, #12]
3001128c:	e59d300c 	ldr	r3, [sp, #12]
30011290:	e1a00003 	mov	r0, r3
30011294:	e28dd010 	add	sp, sp, #16	; 0x10
30011298:	e12fff1e 	bx	lr

3001129c <hal_prefabt_distr>:
3001129c:	e92d4010 	push	{r4, lr}
300112a0:	e24dd008 	sub	sp, sp, #8	; 0x8
300112a4:	e58d0004 	str	r0, [sp, #4]
300112a8:	e3a00005 	mov	r0, #5	; 0x5
300112ac:	ebffff48 	bl	30010fd4 <hal_read_cp15regs>
300112b0:	e1a04000 	mov	r4, r0
300112b4:	e3a00006 	mov	r0, #6	; 0x6
300112b8:	ebffff45 	bl	30010fd4 <hal_read_cp15regs>
300112bc:	e1a03000 	mov	r3, r0
300112c0:	e59f0028 	ldr	r0, [pc, #40]	; 300112f0 <hal_prefabt_distr+0x54>
300112c4:	e1a01004 	mov	r1, r4
300112c8:	e1a02003 	mov	r2, r3
300112cc:	ebfffced 	bl	30010688 <printfk>
300112d0:	e59d3004 	ldr	r3, [sp, #4]
300112d4:	e1a00003 	mov	r0, r3
300112d8:	ebffff5d 	bl	30011054 <hal_dbug_print_reg>
300112dc:	e59f0010 	ldr	r0, [pc, #16]	; 300112f4 <hal_prefabt_distr+0x58>
300112e0:	ebffff13 	bl	30010f34 <hal_sysdie>
300112e4:	e28dd008 	add	sp, sp, #8	; 0x8
300112e8:	e8bd4010 	pop	{r4, lr}
300112ec:	e12fff1e 	bx	lr
300112f0:	30012a2c 	.word	0x30012a2c
300112f4:	30012a40 	.word	0x30012a40

300112f8 <hal_dataabt_distr>:
300112f8:	e92d4010 	push	{r4, lr}
300112fc:	e24dd008 	sub	sp, sp, #8	; 0x8
30011300:	e58d0004 	str	r0, [sp, #4]
30011304:	e3a00005 	mov	r0, #5	; 0x5
30011308:	ebffff31 	bl	30010fd4 <hal_read_cp15regs>
3001130c:	e1a04000 	mov	r4, r0
30011310:	e3a00006 	mov	r0, #6	; 0x6
30011314:	ebffff2e 	bl	30010fd4 <hal_read_cp15regs>
30011318:	e1a03000 	mov	r3, r0
3001131c:	e59f0028 	ldr	r0, [pc, #40]	; 3001134c <hal_dataabt_distr+0x54>
30011320:	e1a01004 	mov	r1, r4
30011324:	e1a02003 	mov	r2, r3
30011328:	ebfffcd6 	bl	30010688 <printfk>
3001132c:	e59d3004 	ldr	r3, [sp, #4]
30011330:	e1a00003 	mov	r0, r3
30011334:	ebffff46 	bl	30011054 <hal_dbug_print_reg>
30011338:	e59f0010 	ldr	r0, [pc, #16]	; 30011350 <hal_dataabt_distr+0x58>
3001133c:	ebfffefc 	bl	30010f34 <hal_sysdie>
30011340:	e28dd008 	add	sp, sp, #8	; 0x8
30011344:	e8bd4010 	pop	{r4, lr}
30011348:	e12fff1e 	bx	lr
3001134c:	30012a2c 	.word	0x30012a2c
30011350:	30012a50 	.word	0x30012a50

30011354 <hal_bugdie_distr>:
30011354:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
30011358:	e24dd00c 	sub	sp, sp, #12	; 0xc
3001135c:	e58d0004 	str	r0, [sp, #4]
30011360:	e59f000c 	ldr	r0, [pc, #12]	; 30011374 <hal_bugdie_distr+0x20>
30011364:	ebfffef2 	bl	30010f34 <hal_sysdie>
30011368:	e28dd00c 	add	sp, sp, #12	; 0xc
3001136c:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
30011370:	e12fff1e 	bx	lr
30011374:	30012a60 	.word	0x30012a60

30011378 <hal_dbugint>:
30011378:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
3001137c:	e24dd00c 	sub	sp, sp, #12	; 0xc
30011380:	e58d0004 	str	r0, [sp, #4]
30011384:	e59f001c 	ldr	r0, [pc, #28]	; 300113a8 <hal_dbugint+0x30>
30011388:	e59d1004 	ldr	r1, [sp, #4]
3001138c:	ebfffcbd 	bl	30010688 <printfk>
30011390:	e59f0010 	ldr	r0, [pc, #16]	; 300113a8 <hal_dbugint+0x30>
30011394:	e59d1004 	ldr	r1, [sp, #4]
30011398:	ebfffcba 	bl	30010688 <printfk>
3001139c:	e28dd00c 	add	sp, sp, #12	; 0xc
300113a0:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
300113a4:	e12fff1e 	bx	lr
300113a8:	30012a70 	.word	0x30012a70

300113ac <hal_dbugint2>:
300113ac:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
300113b0:	e24dd00c 	sub	sp, sp, #12	; 0xc
300113b4:	e58d0004 	str	r0, [sp, #4]
300113b8:	e59f001c 	ldr	r0, [pc, #28]	; 300113dc <hal_dbugint2+0x30>
300113bc:	e59d1004 	ldr	r1, [sp, #4]
300113c0:	ebfffcb0 	bl	30010688 <printfk>
300113c4:	e59f0010 	ldr	r0, [pc, #16]	; 300113dc <hal_dbugint2+0x30>
300113c8:	e59d1004 	ldr	r1, [sp, #4]
300113cc:	ebfffcad 	bl	30010688 <printfk>
300113d0:	e28dd00c 	add	sp, sp, #12	; 0xc
300113d4:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
300113d8:	e12fff1e 	bx	lr
300113dc:	30012a84 	.word	0x30012a84

300113e0 <hal_irq_distr>:
300113e0:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
300113e4:	e24dd014 	sub	sp, sp, #20	; 0x14
300113e8:	e58d0004 	str	r0, [sp, #4]
300113ec:	e3a03000 	mov	r3, #0	; 0x0
300113f0:	e58d300c 	str	r3, [sp, #12]
300113f4:	e59d300c 	ldr	r3, [sp, #12]
300113f8:	e58d3000 	str	r3, [sp]
300113fc:	e59d3000 	ldr	r3, [sp]
30011400:	e3530004 	cmp	r3, #4	; 0x4
30011404:	0a000003 	beq	30011418 <hal_irq_distr+0x38>
30011408:	e59d3000 	ldr	r3, [sp]
3001140c:	e3530005 	cmp	r3, #5	; 0x5
30011410:	0a000006 	beq	30011430 <hal_irq_distr+0x50>
30011414:	ea00000b 	b	30011448 <hal_irq_distr+0x68>
30011418:	e59d0004 	ldr	r0, [sp, #4]
3001141c:	e59d100c 	ldr	r1, [sp, #12]
30011420:	e3a02004 	mov	r2, #4	; 0x4
30011424:	e3a03008 	mov	r3, #8	; 0x8
30011428:	eb000015 	bl	30011484 <hal_eint_distr>
3001142c:	ea000008 	b	30011454 <hal_irq_distr+0x74>
30011430:	e59d0004 	ldr	r0, [sp, #4]
30011434:	e59d100c 	ldr	r1, [sp, #12]
30011438:	e3a02008 	mov	r2, #8	; 0x8
3001143c:	e3a03018 	mov	r3, #24	; 0x18
30011440:	eb00000f 	bl	30011484 <hal_eint_distr>
30011444:	ea000002 	b	30011454 <hal_irq_distr+0x74>
30011448:	e59d0004 	ldr	r0, [sp, #4]
3001144c:	e59d100c 	ldr	r1, [sp, #12]
30011450:	eb000081 	bl	3001165c <hal_int_distr>
30011454:	e28dd014 	add	sp, sp, #20	; 0x14
30011458:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
3001145c:	e12fff1e 	bx	lr

30011460 <hal_frq_distr>:
30011460:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
30011464:	e24dd00c 	sub	sp, sp, #12	; 0xc
30011468:	e58d0004 	str	r0, [sp, #4]
3001146c:	e59f000c 	ldr	r0, [pc, #12]	; 30011480 <hal_frq_distr+0x20>
30011470:	ebfffeaf 	bl	30010f34 <hal_sysdie>
30011474:	e28dd00c 	add	sp, sp, #12	; 0xc
30011478:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
3001147c:	e12fff1e 	bx	lr
30011480:	30012a98 	.word	0x30012a98

30011484 <hal_eint_distr>:
30011484:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
30011488:	e24dd01c 	sub	sp, sp, #28	; 0x1c
3001148c:	e58d000c 	str	r0, [sp, #12]
30011490:	e58d1008 	str	r1, [sp, #8]
30011494:	e58d2004 	str	r2, [sp, #4]
30011498:	e58d3000 	str	r3, [sp]
3001149c:	e3a00456 	mov	r0, #1442840576	; 0x56000000
300114a0:	e28000a8 	add	r0, r0, #168	; 0xa8
300114a4:	ebfffe13 	bl	30010cf8 <hal_io32_read>
300114a8:	e1a03000 	mov	r3, r0
300114ac:	e58d3010 	str	r3, [sp, #16]
300114b0:	e59d3010 	ldr	r3, [sp, #16]
300114b4:	e3c334ff 	bic	r3, r3, #-16777216	; 0xff000000
300114b8:	e58d3010 	str	r3, [sp, #16]
300114bc:	e59d3004 	ldr	r3, [sp, #4]
300114c0:	e58d3014 	str	r3, [sp, #20]
300114c4:	ea00000e 	b	30011504 <hal_eint_distr+0x80>
300114c8:	e59d2014 	ldr	r2, [sp, #20]
300114cc:	e59d3010 	ldr	r3, [sp, #16]
300114d0:	e1a03233 	lsr	r3, r3, r2
300114d4:	e2033001 	and	r3, r3, #1	; 0x1
300114d8:	e20330ff 	and	r3, r3, #255	; 0xff
300114dc:	e3530000 	cmp	r3, #0	; 0x0
300114e0:	0a000004 	beq	300114f8 <hal_eint_distr+0x74>
300114e4:	e59d3014 	ldr	r3, [sp, #20]
300114e8:	e283302f 	add	r3, r3, #47	; 0x2f
300114ec:	e1a00003 	mov	r0, r3
300114f0:	e59d100c 	ldr	r1, [sp, #12]
300114f4:	eb000062 	bl	30011684 <hal_run_intflthandle>
300114f8:	e59d3014 	ldr	r3, [sp, #20]
300114fc:	e2833001 	add	r3, r3, #1	; 0x1
30011500:	e58d3014 	str	r3, [sp, #20]
30011504:	e59d2014 	ldr	r2, [sp, #20]
30011508:	e59d3000 	ldr	r3, [sp]
3001150c:	e1520003 	cmp	r2, r3
30011510:	3affffec 	bcc	300114c8 <hal_eint_distr+0x44>
30011514:	e28dd01c 	add	sp, sp, #28	; 0x1c
30011518:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
3001151c:	e12fff1e 	bx	lr

30011520 <hal_sint_distr>:
30011520:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
30011524:	e24dd01c 	sub	sp, sp, #28	; 0x1c
30011528:	e58d000c 	str	r0, [sp, #12]
3001152c:	e58d1008 	str	r1, [sp, #8]
30011530:	e58d2004 	str	r2, [sp, #4]
30011534:	e58d3000 	str	r3, [sp]
30011538:	e3a0044a 	mov	r0, #1241513984	; 0x4a000000
3001153c:	e2800018 	add	r0, r0, #24	; 0x18
30011540:	ebfffdec 	bl	30010cf8 <hal_io32_read>
30011544:	e1a03000 	mov	r3, r0
30011548:	e58d3010 	str	r3, [sp, #16]
3001154c:	e59d3010 	ldr	r3, [sp, #16]
30011550:	e1a03883 	lsl	r3, r3, #17
30011554:	e1a038a3 	lsr	r3, r3, #17
30011558:	e58d3010 	str	r3, [sp, #16]
3001155c:	e59d3004 	ldr	r3, [sp, #4]
30011560:	e58d3014 	str	r3, [sp, #20]
30011564:	ea00000e 	b	300115a4 <hal_sint_distr+0x84>
30011568:	e59d2014 	ldr	r2, [sp, #20]
3001156c:	e59d3010 	ldr	r3, [sp, #16]
30011570:	e1a03233 	lsr	r3, r3, r2
30011574:	e2033001 	and	r3, r3, #1	; 0x1
30011578:	e20330ff 	and	r3, r3, #255	; 0xff
3001157c:	e3530000 	cmp	r3, #0	; 0x0
30011580:	0a000004 	beq	30011598 <hal_sint_distr+0x78>
30011584:	e59d3014 	ldr	r3, [sp, #20]
30011588:	e283302f 	add	r3, r3, #47	; 0x2f
3001158c:	e1a00003 	mov	r0, r3
30011590:	e59d100c 	ldr	r1, [sp, #12]
30011594:	eb00003a 	bl	30011684 <hal_run_intflthandle>
30011598:	e59d3014 	ldr	r3, [sp, #20]
3001159c:	e2833001 	add	r3, r3, #1	; 0x1
300115a0:	e58d3014 	str	r3, [sp, #20]
300115a4:	e59d2014 	ldr	r2, [sp, #20]
300115a8:	e59d3000 	ldr	r3, [sp]
300115ac:	e1520003 	cmp	r2, r3
300115b0:	3affffec 	bcc	30011568 <hal_sint_distr+0x48>
300115b4:	e28dd01c 	add	sp, sp, #28	; 0x1c
300115b8:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
300115bc:	e12fff1e 	bx	lr

300115c0 <hal_lcdint_distr>:
300115c0:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
300115c4:	e24dd01c 	sub	sp, sp, #28	; 0x1c
300115c8:	e58d000c 	str	r0, [sp, #12]
300115cc:	e58d1008 	str	r1, [sp, #8]
300115d0:	e58d2004 	str	r2, [sp, #4]
300115d4:	e58d3000 	str	r3, [sp]
300115d8:	e3a0044d 	mov	r0, #1291845632	; 0x4d000000
300115dc:	e2800054 	add	r0, r0, #84	; 0x54
300115e0:	ebfffdc4 	bl	30010cf8 <hal_io32_read>
300115e4:	e1a03000 	mov	r3, r0
300115e8:	e58d3010 	str	r3, [sp, #16]
300115ec:	e59d3010 	ldr	r3, [sp, #16]
300115f0:	e2033003 	and	r3, r3, #3	; 0x3
300115f4:	e58d3010 	str	r3, [sp, #16]
300115f8:	e59d3004 	ldr	r3, [sp, #4]
300115fc:	e58d3014 	str	r3, [sp, #20]
30011600:	ea00000e 	b	30011640 <hal_lcdint_distr+0x80>
30011604:	e59d2014 	ldr	r2, [sp, #20]
30011608:	e59d3010 	ldr	r3, [sp, #16]
3001160c:	e1a03233 	lsr	r3, r3, r2
30011610:	e2033001 	and	r3, r3, #1	; 0x1
30011614:	e20330ff 	and	r3, r3, #255	; 0xff
30011618:	e3530000 	cmp	r3, #0	; 0x0
3001161c:	0a000004 	beq	30011634 <hal_lcdint_distr+0x74>
30011620:	e59d3014 	ldr	r3, [sp, #20]
30011624:	e283302f 	add	r3, r3, #47	; 0x2f
30011628:	e1a00003 	mov	r0, r3
3001162c:	e59d100c 	ldr	r1, [sp, #12]
30011630:	eb000013 	bl	30011684 <hal_run_intflthandle>
30011634:	e59d3014 	ldr	r3, [sp, #20]
30011638:	e2833001 	add	r3, r3, #1	; 0x1
3001163c:	e58d3014 	str	r3, [sp, #20]
30011640:	e59d2014 	ldr	r2, [sp, #20]
30011644:	e59d3000 	ldr	r3, [sp]
30011648:	e1520003 	cmp	r2, r3
3001164c:	3affffec 	bcc	30011604 <hal_lcdint_distr+0x44>
30011650:	e28dd01c 	add	sp, sp, #28	; 0x1c
30011654:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
30011658:	e12fff1e 	bx	lr

3001165c <hal_int_distr>:
3001165c:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
30011660:	e24dd00c 	sub	sp, sp, #12	; 0xc
30011664:	e58d0004 	str	r0, [sp, #4]
30011668:	e58d1000 	str	r1, [sp]
3001166c:	e59d0000 	ldr	r0, [sp]
30011670:	e59d1004 	ldr	r1, [sp, #4]
30011674:	eb000002 	bl	30011684 <hal_run_intflthandle>
30011678:	e28dd00c 	add	sp, sp, #12	; 0xc
3001167c:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
30011680:	e12fff1e 	bx	lr

30011684 <hal_run_intflthandle>:
30011684:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
30011688:	e24dd01c 	sub	sp, sp, #28	; 0x1c
3001168c:	e58d0004 	str	r0, [sp, #4]
30011690:	e58d1000 	str	r1, [sp]
30011694:	e3a03000 	mov	r3, #0	; 0x0
30011698:	e58d3014 	str	r3, [sp, #20]
3001169c:	e59d3014 	ldr	r3, [sp, #20]
300116a0:	e3530000 	cmp	r3, #0	; 0x0
300116a4:	1a000002 	bne	300116b4 <hal_run_intflthandle+0x30>
300116a8:	e59f006c 	ldr	r0, [pc, #108]	; 3001171c <hal_run_intflthandle+0x98>
300116ac:	ebfffe20 	bl	30010f34 <hal_sysdie>
300116b0:	ea000016 	b	30011710 <hal_run_intflthandle+0x8c>
300116b4:	e59d3014 	ldr	r3, [sp, #20]
300116b8:	e5933008 	ldr	r3, [r3, #8]
300116bc:	e58d3010 	str	r3, [sp, #16]
300116c0:	ea00000d 	b	300116fc <hal_run_intflthandle+0x78>
300116c4:	e59d3010 	ldr	r3, [sp, #16]
300116c8:	e58d300c 	str	r3, [sp, #12]
300116cc:	e59d300c 	ldr	r3, [sp, #12]
300116d0:	e593c020 	ldr	ip, [r3, #32]
300116d4:	e59d300c 	ldr	r3, [sp, #12]
300116d8:	e5933018 	ldr	r3, [r3, #24]
300116dc:	e59d0004 	ldr	r0, [sp, #4]
300116e0:	e1a01003 	mov	r1, r3
300116e4:	e59d2000 	ldr	r2, [sp]
300116e8:	e1a0e00f 	mov	lr, pc
300116ec:	e12fff1c 	bx	ip
300116f0:	e59d3010 	ldr	r3, [sp, #16]
300116f4:	e5933004 	ldr	r3, [r3, #4]
300116f8:	e58d3010 	str	r3, [sp, #16]
300116fc:	e59d3014 	ldr	r3, [sp, #20]
30011700:	e2832004 	add	r2, r3, #4	; 0x4
30011704:	e59d3010 	ldr	r3, [sp, #16]
30011708:	e1520003 	cmp	r2, r3
3001170c:	1affffec 	bne	300116c4 <hal_run_intflthandle+0x40>
30011710:	e28dd01c 	add	sp, sp, #28	; 0x1c
30011714:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
30011718:	e12fff1e 	bx	lr
3001171c:	30012aa8 	.word	0x30012aa8

30011720 <__aeabi_uidiv>:
30011720:	e2512001 	subs	r2, r1, #1	; 0x1
30011724:	012fff1e 	bxeq	lr
30011728:	3a000074 	bcc	30011900 <__aeabi_uidiv+0x1e0>
3001172c:	e1500001 	cmp	r0, r1
30011730:	9a00006b 	bls	300118e4 <__aeabi_uidiv+0x1c4>
30011734:	e1110002 	tst	r1, r2
30011738:	0a00006c 	beq	300118f0 <__aeabi_uidiv+0x1d0>
3001173c:	e16f3f10 	clz	r3, r0
30011740:	e16f2f11 	clz	r2, r1
30011744:	e0423003 	sub	r3, r2, r3
30011748:	e273301f 	rsbs	r3, r3, #31	; 0x1f
3001174c:	10833083 	addne	r3, r3, r3, lsl #1
30011750:	e3a02000 	mov	r2, #0	; 0x0
30011754:	108ff103 	addne	pc, pc, r3, lsl #2
30011758:	e1a00000 	nop			(mov r0,r0)
3001175c:	e1500f81 	cmp	r0, r1, lsl #31
30011760:	e0a22002 	adc	r2, r2, r2
30011764:	20400f81 	subcs	r0, r0, r1, lsl #31
30011768:	e1500f01 	cmp	r0, r1, lsl #30
3001176c:	e0a22002 	adc	r2, r2, r2
30011770:	20400f01 	subcs	r0, r0, r1, lsl #30
30011774:	e1500e81 	cmp	r0, r1, lsl #29
30011778:	e0a22002 	adc	r2, r2, r2
3001177c:	20400e81 	subcs	r0, r0, r1, lsl #29
30011780:	e1500e01 	cmp	r0, r1, lsl #28
30011784:	e0a22002 	adc	r2, r2, r2
30011788:	20400e01 	subcs	r0, r0, r1, lsl #28
3001178c:	e1500d81 	cmp	r0, r1, lsl #27
30011790:	e0a22002 	adc	r2, r2, r2
30011794:	20400d81 	subcs	r0, r0, r1, lsl #27
30011798:	e1500d01 	cmp	r0, r1, lsl #26
3001179c:	e0a22002 	adc	r2, r2, r2
300117a0:	20400d01 	subcs	r0, r0, r1, lsl #26
300117a4:	e1500c81 	cmp	r0, r1, lsl #25
300117a8:	e0a22002 	adc	r2, r2, r2
300117ac:	20400c81 	subcs	r0, r0, r1, lsl #25
300117b0:	e1500c01 	cmp	r0, r1, lsl #24
300117b4:	e0a22002 	adc	r2, r2, r2
300117b8:	20400c01 	subcs	r0, r0, r1, lsl #24
300117bc:	e1500b81 	cmp	r0, r1, lsl #23
300117c0:	e0a22002 	adc	r2, r2, r2
300117c4:	20400b81 	subcs	r0, r0, r1, lsl #23
300117c8:	e1500b01 	cmp	r0, r1, lsl #22
300117cc:	e0a22002 	adc	r2, r2, r2
300117d0:	20400b01 	subcs	r0, r0, r1, lsl #22
300117d4:	e1500a81 	cmp	r0, r1, lsl #21
300117d8:	e0a22002 	adc	r2, r2, r2
300117dc:	20400a81 	subcs	r0, r0, r1, lsl #21
300117e0:	e1500a01 	cmp	r0, r1, lsl #20
300117e4:	e0a22002 	adc	r2, r2, r2
300117e8:	20400a01 	subcs	r0, r0, r1, lsl #20
300117ec:	e1500981 	cmp	r0, r1, lsl #19
300117f0:	e0a22002 	adc	r2, r2, r2
300117f4:	20400981 	subcs	r0, r0, r1, lsl #19
300117f8:	e1500901 	cmp	r0, r1, lsl #18
300117fc:	e0a22002 	adc	r2, r2, r2
30011800:	20400901 	subcs	r0, r0, r1, lsl #18
30011804:	e1500881 	cmp	r0, r1, lsl #17
30011808:	e0a22002 	adc	r2, r2, r2
3001180c:	20400881 	subcs	r0, r0, r1, lsl #17
30011810:	e1500801 	cmp	r0, r1, lsl #16
30011814:	e0a22002 	adc	r2, r2, r2
30011818:	20400801 	subcs	r0, r0, r1, lsl #16
3001181c:	e1500781 	cmp	r0, r1, lsl #15
30011820:	e0a22002 	adc	r2, r2, r2
30011824:	20400781 	subcs	r0, r0, r1, lsl #15
30011828:	e1500701 	cmp	r0, r1, lsl #14
3001182c:	e0a22002 	adc	r2, r2, r2
30011830:	20400701 	subcs	r0, r0, r1, lsl #14
30011834:	e1500681 	cmp	r0, r1, lsl #13
30011838:	e0a22002 	adc	r2, r2, r2
3001183c:	20400681 	subcs	r0, r0, r1, lsl #13
30011840:	e1500601 	cmp	r0, r1, lsl #12
30011844:	e0a22002 	adc	r2, r2, r2
30011848:	20400601 	subcs	r0, r0, r1, lsl #12
3001184c:	e1500581 	cmp	r0, r1, lsl #11
30011850:	e0a22002 	adc	r2, r2, r2
30011854:	20400581 	subcs	r0, r0, r1, lsl #11
30011858:	e1500501 	cmp	r0, r1, lsl #10
3001185c:	e0a22002 	adc	r2, r2, r2
30011860:	20400501 	subcs	r0, r0, r1, lsl #10
30011864:	e1500481 	cmp	r0, r1, lsl #9
30011868:	e0a22002 	adc	r2, r2, r2
3001186c:	20400481 	subcs	r0, r0, r1, lsl #9
30011870:	e1500401 	cmp	r0, r1, lsl #8
30011874:	e0a22002 	adc	r2, r2, r2
30011878:	20400401 	subcs	r0, r0, r1, lsl #8
3001187c:	e1500381 	cmp	r0, r1, lsl #7
30011880:	e0a22002 	adc	r2, r2, r2
30011884:	20400381 	subcs	r0, r0, r1, lsl #7
30011888:	e1500301 	cmp	r0, r1, lsl #6
3001188c:	e0a22002 	adc	r2, r2, r2
30011890:	20400301 	subcs	r0, r0, r1, lsl #6
30011894:	e1500281 	cmp	r0, r1, lsl #5
30011898:	e0a22002 	adc	r2, r2, r2
3001189c:	20400281 	subcs	r0, r0, r1, lsl #5
300118a0:	e1500201 	cmp	r0, r1, lsl #4
300118a4:	e0a22002 	adc	r2, r2, r2
300118a8:	20400201 	subcs	r0, r0, r1, lsl #4
300118ac:	e1500181 	cmp	r0, r1, lsl #3
300118b0:	e0a22002 	adc	r2, r2, r2
300118b4:	20400181 	subcs	r0, r0, r1, lsl #3
300118b8:	e1500101 	cmp	r0, r1, lsl #2
300118bc:	e0a22002 	adc	r2, r2, r2
300118c0:	20400101 	subcs	r0, r0, r1, lsl #2
300118c4:	e1500081 	cmp	r0, r1, lsl #1
300118c8:	e0a22002 	adc	r2, r2, r2
300118cc:	20400081 	subcs	r0, r0, r1, lsl #1
300118d0:	e1500001 	cmp	r0, r1
300118d4:	e0a22002 	adc	r2, r2, r2
300118d8:	20400001 	subcs	r0, r0, r1
300118dc:	e1a00002 	mov	r0, r2
300118e0:	e12fff1e 	bx	lr
300118e4:	03a00001 	moveq	r0, #1	; 0x1
300118e8:	13a00000 	movne	r0, #0	; 0x0
300118ec:	e12fff1e 	bx	lr
300118f0:	e16f2f11 	clz	r2, r1
300118f4:	e262201f 	rsb	r2, r2, #31	; 0x1f
300118f8:	e1a00230 	lsr	r0, r0, r2
300118fc:	e12fff1e 	bx	lr
30011900:	e3500000 	cmp	r0, #0	; 0x0
30011904:	13e00000 	mvnne	r0, #0	; 0x0
30011908:	ea000007 	b	3001192c <__aeabi_idiv0>

3001190c <__aeabi_uidivmod>:
3001190c:	e3510000 	cmp	r1, #0	; 0x0
30011910:	0afffffa 	beq	30011900 <__aeabi_uidiv+0x1e0>
30011914:	e92d4003 	push	{r0, r1, lr}
30011918:	ebffff80 	bl	30011720 <__aeabi_uidiv>
3001191c:	e8bd4006 	pop	{r1, r2, lr}
30011920:	e0030092 	mul	r3, r2, r0
30011924:	e0411003 	sub	r1, r1, r3
30011928:	e12fff1e 	bx	lr

3001192c <__aeabi_idiv0>:
3001192c:	e92d4002 	push	{r1, lr}
30011930:	e3a00008 	mov	r0, #8	; 0x8
30011934:	ebfff9dd 	bl	300100b0 <raise>
30011938:	e8bd8002 	pop	{r1, pc}

Disassembly of section .lmosem_hal.vector:

30011940 <vector>:
30011940:	e59ff038 	ldr	pc, [pc, #56]	; 30011980 <lmosem_restart_l>
30011944:	e59ff038 	ldr	pc, [pc, #56]	; 30011984 <lmosem_undefins_l>
30011948:	e59ff038 	ldr	pc, [pc, #56]	; 30011988 <lmosem_swi_l>
3001194c:	e59ff038 	ldr	pc, [pc, #56]	; 3001198c <lmosem_prefabt_l>
30011950:	e59ff038 	ldr	pc, [pc, #56]	; 30011990 <lmosem_dataabt_l>
30011954:	e59ff038 	ldr	pc, [pc, #56]	; 30011994 <lmosem_bugdie_l>
30011958:	e59ff038 	ldr	pc, [pc, #56]	; 30011998 <lmosem_irq_l>
3001195c:	e59ff038 	ldr	pc, [pc, #56]	; 3001199c <lmosem_frq_l>
30011960:	e1a00000 	nop			(mov r0,r0)
30011964:	e1a00000 	nop			(mov r0,r0)
30011968:	e1a00000 	nop			(mov r0,r0)
3001196c:	e1a00000 	nop			(mov r0,r0)

30011970 <_err>:
30011970:	eafff9a2 	b	30010000 <__begin_kernel>
30011974:	e1a00000 	nop			(mov r0,r0)
30011978:	e1a00000 	nop			(mov r0,r0)
3001197c:	e1a00000 	nop			(mov r0,r0)

30011980 <lmosem_restart_l>:
30011980:	30010000 	.word	0x30010000

30011984 <lmosem_undefins_l>:
30011984:	300102c0 	.word	0x300102c0

30011988 <lmosem_swi_l>:
30011988:	300102fc 	.word	0x300102fc

3001198c <lmosem_prefabt_l>:
3001198c:	30010328 	.word	0x30010328

30011990 <lmosem_dataabt_l>:
30011990:	30010360 	.word	0x30010360

30011994 <lmosem_bugdie_l>:
30011994:	3001039c 	.word	0x3001039c

30011998 <lmosem_irq_l>:
30011998:	300103a0 	.word	0x300103a0

3001199c <lmosem_frq_l>:
3001199c:	300103dc 	.word	0x300103dc

Disassembly of section .data:

300119a0 <machadrspce>:
300119a0:	00000005 	.word	0x00000005
	...
300119ac:	001fffff 	.word	0x001fffff
300119b0:	00000001 	.word	0x00000001
300119b4:	00000000 	.word	0x00000000
300119b8:	08000000 	.word	0x08000000
300119bc:	0800000f 	.word	0x0800000f
300119c0:	00000001 	.word	0x00000001
300119c4:	00000000 	.word	0x00000000
300119c8:	10000000 	.word	0x10000000
300119cc:	1000000f 	.word	0x1000000f
300119d0:	00000001 	.word	0x00000001
300119d4:	00000000 	.word	0x00000000
300119d8:	19000000 	.word	0x19000000
300119dc:	190fffff 	.word	0x190fffff
300119e0:	00000001 	.word	0x00000001
300119e4:	00000000 	.word	0x00000000
300119e8:	20000000 	.word	0x20000000
300119ec:	2000000f 	.word	0x2000000f
300119f0:	00000001 	.word	0x00000001
300119f4:	00000000 	.word	0x00000000
300119f8:	28000000 	.word	0x28000000
300119fc:	28000007 	.word	0x28000007
30011a00:	00000001 	.word	0x00000001
30011a04:	00000000 	.word	0x00000000
30011a08:	29000000 	.word	0x29000000
30011a0c:	29000007 	.word	0x29000007
30011a10:	00000002 	.word	0x00000002
30011a14:	00000000 	.word	0x00000000
30011a18:	30000000 	.word	0x30000000
30011a1c:	33ffffff 	.word	0x33ffffff
30011a20:	00000001 	.word	0x00000001
30011a24:	00000000 	.word	0x00000000
30011a28:	48000000 	.word	0x48000000
30011a2c:	48000030 	.word	0x48000030
30011a30:	00000001 	.word	0x00000001
30011a34:	00000000 	.word	0x00000000
30011a38:	49000000 	.word	0x49000000
30011a3c:	49000058 	.word	0x49000058
30011a40:	00000001 	.word	0x00000001
30011a44:	00000000 	.word	0x00000000
30011a48:	4a000000 	.word	0x4a000000
30011a4c:	4a00001c 	.word	0x4a00001c
30011a50:	00000001 	.word	0x00000001
30011a54:	00000000 	.word	0x00000000
30011a58:	4b000000 	.word	0x4b000000
30011a5c:	4b0000e0 	.word	0x4b0000e0
30011a60:	00000001 	.word	0x00000001
30011a64:	00000000 	.word	0x00000000
30011a68:	4c000000 	.word	0x4c000000
30011a6c:	4c000018 	.word	0x4c000018
30011a70:	00000001 	.word	0x00000001
30011a74:	00000000 	.word	0x00000000
30011a78:	4d000000 	.word	0x4d000000
30011a7c:	4d000060 	.word	0x4d000060
30011a80:	00000001 	.word	0x00000001
30011a84:	00000000 	.word	0x00000000
30011a88:	4e000000 	.word	0x4e000000
30011a8c:	4e00003c 	.word	0x4e00003c
30011a90:	00000001 	.word	0x00000001
30011a94:	00000000 	.word	0x00000000
30011a98:	4f000000 	.word	0x4f000000
30011a9c:	4f0000a0 	.word	0x4f0000a0
30011aa0:	00000001 	.word	0x00000001
30011aa4:	00000000 	.word	0x00000000
30011aa8:	50000000 	.word	0x50000000
30011aac:	50008028 	.word	0x50008028
30011ab0:	00000001 	.word	0x00000001
30011ab4:	00000000 	.word	0x00000000
30011ab8:	51000000 	.word	0x51000000
30011abc:	51000040 	.word	0x51000040
30011ac0:	00000001 	.word	0x00000001
30011ac4:	00000000 	.word	0x00000000
30011ac8:	52000000 	.word	0x52000000
30011acc:	5200026f 	.word	0x5200026f
30011ad0:	00000001 	.word	0x00000001
30011ad4:	00000000 	.word	0x00000000
30011ad8:	53000000 	.word	0x53000000
30011adc:	53000008 	.word	0x53000008
30011ae0:	00000001 	.word	0x00000001
30011ae4:	00000000 	.word	0x00000000
30011ae8:	54000000 	.word	0x54000000
30011aec:	54000010 	.word	0x54000010
30011af0:	00000001 	.word	0x00000001
30011af4:	00000000 	.word	0x00000000
30011af8:	55000000 	.word	0x55000000
30011afc:	55000012 	.word	0x55000012
30011b00:	00000001 	.word	0x00000001
30011b04:	00000000 	.word	0x00000000
30011b08:	56000000 	.word	0x56000000
30011b0c:	560000cc 	.word	0x560000cc
30011b10:	00000001 	.word	0x00000001
30011b14:	00000000 	.word	0x00000000
30011b18:	57000040 	.word	0x57000040
30011b1c:	5700008b 	.word	0x5700008b
30011b20:	00000001 	.word	0x00000001
30011b24:	00000000 	.word	0x00000000
30011b28:	58000000 	.word	0x58000000
30011b2c:	58000014 	.word	0x58000014
30011b30:	00000001 	.word	0x00000001
30011b34:	00000000 	.word	0x00000000
30011b38:	59000000 	.word	0x59000000
30011b3c:	59000034 	.word	0x59000034
30011b40:	00000001 	.word	0x00000001
30011b44:	00000000 	.word	0x00000000
30011b48:	5a000000 	.word	0x5a000000
30011b4c:	5a000043 	.word	0x5a000043
30011b50:	00000001 	.word	0x00000001
30011b54:	00000000 	.word	0x00000000
30011b58:	5b000000 	.word	0x5b000000
30011b5c:	5b00001c 	.word	0x5b00001c
30011b60:	00000000 	.word	0x00000000
30011b64:	0fffffff 	.word	0x0fffffff
	...

30011b70 <osmach>:
	...

30011ba4 <osphymen>:
	...

30011c78 <machintflt>:
	...

30012790 <osphymem>:
	...

30012864 <gint_indx>:
30012864:	00000000 	.word	0x00000000

Disassembly of section .rodata:

30012868 <.rodata>:
30012868:	74726175 	.word	0x74726175
3001286c:	72726520 	.word	0x72726520
30012870:	00000000 	.word	0x00000000
30012874:	33323130 	.word	0x33323130
30012878:	37363534 	.word	0x37363534
3001287c:	62613938 	.word	0x62613938
30012880:	66656463 	.word	0x66656463
30012884:	00000000 	.word	0x00000000
30012888:	534f4d4c 	.word	0x534f4d4c
3001288c:	53204d45 	.word	0x53204d45
30012890:	45545359 	.word	0x45545359
30012894:	5349204d 	.word	0x5349204d
30012898:	45494420 	.word	0x45494420
3001289c:	00732520 	.word	0x00732520
300128a0:	65646e75 	.word	0x65646e75
300128a4:	736e6966 	.word	0x736e6966
300128a8:	6e757220 	.word	0x6e757220
300128ac:	21676e69 	.word	0x21676e69
300128b0:	00000021 	.word	0x00000021
300128b4:	5f525355 	.word	0x5f525355
300128b8:	20474552 	.word	0x20474552
300128bc:	253a3072 	.word	0x253a3072
300128c0:	000d0a78 	.word	0x000d0a78
300128c4:	5f525355 	.word	0x5f525355
300128c8:	20474552 	.word	0x20474552
300128cc:	253a3172 	.word	0x253a3172
300128d0:	000d0a78 	.word	0x000d0a78
300128d4:	5f525355 	.word	0x5f525355
300128d8:	20474552 	.word	0x20474552
300128dc:	253a3272 	.word	0x253a3272
300128e0:	000d0a78 	.word	0x000d0a78
300128e4:	5f525355 	.word	0x5f525355
300128e8:	20474552 	.word	0x20474552
300128ec:	253a3372 	.word	0x253a3372
300128f0:	000d0a78 	.word	0x000d0a78
300128f4:	5f525355 	.word	0x5f525355
300128f8:	20474552 	.word	0x20474552
300128fc:	253a3472 	.word	0x253a3472
30012900:	000d0a78 	.word	0x000d0a78
30012904:	5f525355 	.word	0x5f525355
30012908:	20474552 	.word	0x20474552
3001290c:	253a3572 	.word	0x253a3572
30012910:	000d0a78 	.word	0x000d0a78
30012914:	5f525355 	.word	0x5f525355
30012918:	20474552 	.word	0x20474552
3001291c:	253a3672 	.word	0x253a3672
30012920:	000d0a78 	.word	0x000d0a78
30012924:	5f525355 	.word	0x5f525355
30012928:	20474552 	.word	0x20474552
3001292c:	253a3772 	.word	0x253a3772
30012930:	000d0a78 	.word	0x000d0a78
30012934:	5f525355 	.word	0x5f525355
30012938:	20474552 	.word	0x20474552
3001293c:	253a3872 	.word	0x253a3872
30012940:	000d0a78 	.word	0x000d0a78
30012944:	5f525355 	.word	0x5f525355
30012948:	20474552 	.word	0x20474552
3001294c:	253a3972 	.word	0x253a3972
30012950:	000d0a78 	.word	0x000d0a78
30012954:	5f525355 	.word	0x5f525355
30012958:	20474552 	.word	0x20474552
3001295c:	3a303172 	.word	0x3a303172
30012960:	0d0a7825 	.word	0x0d0a7825
30012964:	00000000 	.word	0x00000000
30012968:	5f525355 	.word	0x5f525355
3001296c:	20474552 	.word	0x20474552
30012970:	3a313172 	.word	0x3a313172
30012974:	0d0a7825 	.word	0x0d0a7825
30012978:	00000000 	.word	0x00000000
3001297c:	5f525355 	.word	0x5f525355
30012980:	20474552 	.word	0x20474552
30012984:	3a323172 	.word	0x3a323172
30012988:	0d0a7825 	.word	0x0d0a7825
3001298c:	00000000 	.word	0x00000000
30012990:	5f525355 	.word	0x5f525355
30012994:	20474552 	.word	0x20474552
30012998:	3a333172 	.word	0x3a333172
3001299c:	0d0a7825 	.word	0x0d0a7825
300129a0:	00000000 	.word	0x00000000
300129a4:	5f525355 	.word	0x5f525355
300129a8:	20474552 	.word	0x20474552
300129ac:	3a343172 	.word	0x3a343172
300129b0:	0d0a7825 	.word	0x0d0a7825
300129b4:	00000000 	.word	0x00000000
300129b8:	5f455653 	.word	0x5f455653
300129bc:	20474552 	.word	0x20474552
300129c0:	253a726c 	.word	0x253a726c
300129c4:	000d0a78 	.word	0x000d0a78
300129c8:	5f455653 	.word	0x5f455653
300129cc:	20474552 	.word	0x20474552
300129d0:	72737073 	.word	0x72737073
300129d4:	0a78253a 	.word	0x0a78253a
300129d8:	0000000d 	.word	0x0000000d
300129dc:	5f505343 	.word	0x5f505343
300129e0:	20474552 	.word	0x20474552
300129e4:	253a7073 	.word	0x253a7073
300129e8:	4e492078 	.word	0x4e492078
300129ec:	444e5054 	.word	0x444e5054
300129f0:	0a78253a 	.word	0x0a78253a
300129f4:	0000000d 	.word	0x0000000d
300129f8:	5f524343 	.word	0x5f524343
300129fc:	20474552 	.word	0x20474552
30012a00:	72737063 	.word	0x72737063
30012a04:	2078253a 	.word	0x2078253a
30012a08:	4f544e49 	.word	0x4f544e49
30012a0c:	3a545346 	.word	0x3a545346
30012a10:	0d0a7825 	.word	0x0d0a7825
30012a14:	00000000 	.word	0x00000000
30012a18:	65646e75 	.word	0x65646e75
30012a1c:	736e6966 	.word	0x736e6966
30012a20:	6e757220 	.word	0x6e757220
30012a24:	21676e69 	.word	0x21676e69
30012a28:	00000021 	.word	0x00000021
30012a2c:	35315043 	.word	0x35315043
30012a30:	3a356320 	.word	0x3a356320
30012a34:	63207825 	.word	0x63207825
30012a38:	78252036 	.word	0x78252036
30012a3c:	00000d0a 	.word	0x00000d0a
30012a40:	66657270 	.word	0x66657270
30012a44:	74626120 	.word	0x74626120
30012a48:	6e757220 	.word	0x6e757220
30012a4c:	00676e69 	.word	0x00676e69
30012a50:	61746164 	.word	0x61746164
30012a54:	74626120 	.word	0x74626120
30012a58:	6e757220 	.word	0x6e757220
30012a5c:	00676e69 	.word	0x00676e69
30012a60:	20677562 	.word	0x20677562
30012a64:	20656964 	.word	0x20656964
30012a68:	696e7572 	.word	0x696e7572
30012a6c:	0000676e 	.word	0x0000676e
30012a70:	75626469 	.word	0x75626469
30012a74:	6e652067 	.word	0x6e652067
30012a78:	2e726574 	.word	0x2e726574
30012a7c:	2078252e 	.word	0x2078252e
30012a80:	00000d0a 	.word	0x00000d0a
30012a84:	75626469 	.word	0x75626469
30012a88:	78652067 	.word	0x78652067
30012a8c:	2e2e7469 	.word	0x2e2e7469
30012a90:	0a207825 	.word	0x0a207825
30012a94:	0000000d 	.word	0x0000000d
30012a98:	20717266 	.word	0x20717266
30012a9c:	696e7572 	.word	0x696e7572
30012aa0:	2121676e 	.word	0x2121676e
30012aa4:	00000000 	.word	0x00000000
30012aa8:	5f6c6168 	.word	0x5f6c6168
30012aac:	5f6e7572 	.word	0x5f6e7572
30012ab0:	66746e69 	.word	0x66746e69
30012ab4:	7364746c 	.word	0x7364746c
30012ab8:	72652063 	.word	0x72652063
30012abc:	00000072 	.word	0x00000072

Disassembly of section .ARM.attributes:

00000000 <.ARM.attributes>:
   0:	00002c41 	andeq	r2, r0, r1, asr #24
   4:	61656100 	cmnvs	r5, r0, lsl #2
   8:	01006962 	tsteq	r0, r2, ror #18
   c:	00000022 	andeq	r0, r0, r2, lsr #32
  10:	4d524105 	ldfmie	f4, [r2, #-20]
  14:	54357620 	ldrtpl	r7, [r5], #-1568
  18:	08030600 	stmdaeq	r3, {r9, sl}
  1c:	12010901 	andne	r0, r1, #16384	; 0x4000
  20:	15011404 	strne	r1, [r1, #-1028]
  24:	18031701 	stmdane	r3, {r0, r8, r9, sl, ip}
  28:	1e021a01 	vmlane.f32	s2, s4, s2
  2c:	Address 0x0000002c is out of bounds.


Disassembly of section .debug_frame:

00000000 <.debug_frame>:
   0:	0000000c 	.word	0x0000000c
   4:	ffffffff 	.word	0xffffffff
   8:	7c010001 	.word	0x7c010001
   c:	000d0c0e 	.word	0x000d0c0e
  10:	000c      	.short	0x000c
  12:	00          	.byte	0x00
  13:	00          	.byte	0x00
  14:	00000000 	.word	0x00000000
  18:	30011720 	.word	0x30011720
  1c:	01ec      	.short	0x01ec
	...
