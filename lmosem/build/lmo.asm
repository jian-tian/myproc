
lmosemkrnl.elf:     file format elf32-littlearm


Disassembly of section .head.text:

30010000 <_start>:
30010000:	ea000006 	b	30010020 <reset>
30010004:	e59ff088 	ldr	pc, [pc, #136]	; 30010094 <tstw+0x4>
30010008:	e59ff088 	ldr	pc, [pc, #136]	; 30010098 <tstw+0x8>
3001000c:	e59ff088 	ldr	pc, [pc, #136]	; 3001009c <tstw+0xc>
30010010:	e59ff088 	ldr	pc, [pc, #136]	; 300100a0 <tstw+0x10>
30010014:	e59ff088 	ldr	pc, [pc, #136]	; 300100a4 <tstw+0x14>
30010018:	e59ff088 	ldr	pc, [pc, #136]	; 300100a8 <tstw+0x18>
3001001c:	e59ff088 	ldr	pc, [pc, #136]	; 300100ac <tstw+0x1c>

30010020 <reset>:
30010020:	e329f0d3 	msr	CPSR_fc, #211	; 0xd3
30010024:	e3a00453 	mov	r0, #1392508928	; 0x53000000
30010028:	e3a01000 	mov	r1, #0	; 0x0
3001002c:	e5801000 	str	r1, [r0]
30010030:	e59f0078 	ldr	r0, [pc, #120]	; 300100b0 <tstw+0x20>
30010034:	e3e01000 	mvn	r1, #0	; 0x0
30010038:	e5801000 	str	r1, [r0]
3001003c:	e59f0070 	ldr	r0, [pc, #112]	; 300100b4 <tstw+0x24>
30010040:	e59f1070 	ldr	r1, [pc, #112]	; 300100b8 <tstw+0x28>
30010044:	e5801000 	str	r1, [r0]
30010048:	e59f0040 	ldr	r0, [pc, #64]	; 30010090 <tstw>
3001004c:	e3a0d30d 	mov	sp, #872415232	; 0x34000000
30010050:	e1a00000 	nop			(mov r0,r0)
30010054:	e1a00000 	nop			(mov r0,r0)
30010058:	eb0000f4 	bl	30010430 <__begin_lmosem_hal_intvect>
3001005c:	eb000175 	bl	30010638 <hal_undefins_distr>

30010060 <lmde>:
30010060:	eafffffe 	b	30010060 <lmde>
	...

30010070 <_undefined_struction>:
30010070:	e321f0d3 	msr	CPSR_c, #211	; 0xd3
30010074:	eb00016f 	bl	30010638 <hal_undefins_distr>

30010078 <_software_struction>:
30010078:	eafffffe 	b	30010078 <_software_struction>

3001007c <_prefetch_abort>:
3001007c:	eafffffe 	b	3001007c <_prefetch_abort>

30010080 <_data_abort>:
30010080:	eafffffe 	b	30010080 <_data_abort>

30010084 <_not_used>:
30010084:	eafffffe 	b	30010084 <_not_used>

30010088 <_irq>:
30010088:	eafffffe 	b	30010088 <_irq>

3001008c <_fiq>:
3001008c:	eafffffe 	b	3001008c <_fiq>

30010090 <tstw>:
30010090:	30010430 	.word	0x30010430
30010094:	30010070 	.word	0x30010070
30010098:	30010078 	.word	0x30010078
3001009c:	3001007c 	.word	0x3001007c
300100a0:	30010080 	.word	0x30010080
300100a4:	30010084 	.word	0x30010084
300100a8:	30010088 	.word	0x30010088
300100ac:	3001008c 	.word	0x3001008c
300100b0:	4a000008 	.word	0x4a000008
300100b4:	4a00001c 	.word	0x4a00001c
300100b8:	00007fff 	.word	0x00007fff
300100bc:	00000000 	.word	0x00000000

300100c0 <raise>:
300100c0:	e24dd008 	sub	sp, sp, #8	; 0x8
300100c4:	e58d0004 	str	r0, [sp, #4]
300100c8:	e28dd008 	add	sp, sp, #8	; 0x8
300100cc:	e12fff1e 	bx	lr

300100d0 <init_hal>:
300100d0:	e92d4010 	push	{r4, lr}
300100d4:	eb00028a 	bl	30010b04 <init_platform>
300100d8:	eb0004f6 	bl	300114b8 <init_haluart>
300100dc:	e8bd4010 	pop	{r4, lr}
300100e0:	e12fff1e 	bx	lr

300100e4 <s3c2440mmu_init>:
300100e4:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
300100e8:	e24dd014 	sub	sp, sp, #20	; 0x14
300100ec:	e3a03000 	mov	r3, #0	; 0x0
300100f0:	e58d3000 	str	r3, [sp]
300100f4:	e3a03000 	mov	r3, #0	; 0x0
300100f8:	e58d3004 	str	r3, [sp, #4]
300100fc:	e3a03203 	mov	r3, #805306368	; 0x30000000
30010100:	e2833901 	add	r3, r3, #16384	; 0x4000
30010104:	e58d3008 	str	r3, [sp, #8]
30010108:	e3a03000 	mov	r3, #0	; 0x0
3001010c:	e58d300c 	str	r3, [sp, #12]
30010110:	ea00000f 	b	30010154 <s3c2440mmu_init+0x70>
30010114:	e59d3000 	ldr	r3, [sp]
30010118:	e3833b03 	orr	r3, r3, #3072	; 0xc00
3001011c:	e3833002 	orr	r3, r3, #2	; 0x2
30010120:	e58d3004 	str	r3, [sp, #4]
30010124:	e59d300c 	ldr	r3, [sp, #12]
30010128:	e1a02103 	lsl	r2, r3, #2
3001012c:	e59d3008 	ldr	r3, [sp, #8]
30010130:	e0832002 	add	r2, r3, r2
30010134:	e59d3004 	ldr	r3, [sp, #4]
30010138:	e5823000 	str	r3, [r2]
3001013c:	e59d3000 	ldr	r3, [sp]
30010140:	e2833601 	add	r3, r3, #1048576	; 0x100000
30010144:	e58d3000 	str	r3, [sp]
30010148:	e59d300c 	ldr	r3, [sp, #12]
3001014c:	e2833001 	add	r3, r3, #1	; 0x1
30010150:	e58d300c 	str	r3, [sp, #12]
30010154:	e59d200c 	ldr	r2, [sp, #12]
30010158:	e3a03eff 	mov	r3, #4080	; 0xff0
3001015c:	e283300f 	add	r3, r3, #15	; 0xf
30010160:	e1520003 	cmp	r2, r3
30010164:	9affffea 	bls	30010114 <s3c2440mmu_init+0x30>
30010168:	e59d2008 	ldr	r2, [sp, #8]
3001016c:	e3a03b03 	mov	r3, #3072	; 0xc00
30010170:	e2833223 	add	r3, r3, #805306370	; 0x30000002
30010174:	e5823000 	str	r3, [r2]
30010178:	e3a00203 	mov	r0, #805306368	; 0x30000000
3001017c:	e2800901 	add	r0, r0, #16384	; 0x4000
30010180:	eb000012 	bl	300101d0 <s3c2440mmu_set_tblbass>
30010184:	e3e00000 	mvn	r0, #0	; 0x0
30010188:	eb00000a 	bl	300101b8 <s3c2440mmu_set_domain>
3001018c:	eb000004 	bl	300101a4 <s3c2440mmu_invalid_dicache>
30010190:	eb000499 	bl	300113fc <hal_disable_cache>
30010194:	eb000013 	bl	300101e8 <s3c2440mmu_enable>
30010198:	e28dd014 	add	sp, sp, #20	; 0x14
3001019c:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
300101a0:	e12fff1e 	bx	lr

300101a4 <s3c2440mmu_invalid_dicache>:
300101a4:	e3a00000 	mov	r0, #0	; 0x0
300101a8:	ee070f17 	mcr	15, 0, r0, cr7, cr7, {0}
300101ac:	ee070f9a 	mcr	15, 0, r0, cr7, cr10, {4}
300101b0:	ee080f17 	mcr	15, 0, r0, cr8, cr7, {0}
300101b4:	e12fff1e 	bx	lr

300101b8 <s3c2440mmu_set_domain>:
300101b8:	e24dd008 	sub	sp, sp, #8	; 0x8
300101bc:	e58d0004 	str	r0, [sp, #4]
300101c0:	e59d3004 	ldr	r3, [sp, #4]
300101c4:	ee033f10 	mcr	15, 0, r3, cr3, cr0, {0}
300101c8:	e28dd008 	add	sp, sp, #8	; 0x8
300101cc:	e12fff1e 	bx	lr

300101d0 <s3c2440mmu_set_tblbass>:
300101d0:	e24dd008 	sub	sp, sp, #8	; 0x8
300101d4:	e58d0004 	str	r0, [sp, #4]
300101d8:	e59d3004 	ldr	r3, [sp, #4]
300101dc:	ee023f10 	mcr	15, 0, r3, cr2, cr0, {0}
300101e0:	e28dd008 	add	sp, sp, #8	; 0x8
300101e4:	e12fff1e 	bx	lr

300101e8 <s3c2440mmu_enable>:
300101e8:	ee010f10 	mcr	15, 0, r0, cr1, cr0, {0}
300101ec:	e3800001 	orr	r0, r0, #1	; 0x1
300101f0:	ee010f10 	mcr	15, 0, r0, cr1, cr0, {0}
300101f4:	e1a00000 	nop			(mov r0,r0)
300101f8:	e1a00000 	nop			(mov r0,r0)
300101fc:	e1a00000 	nop			(mov r0,r0)
30010200:	e1a00000 	nop			(mov r0,r0)
30010204:	e1a00000 	nop			(mov r0,r0)
30010208:	e1a00000 	nop			(mov r0,r0)
3001020c:	e1a00000 	nop			(mov r0,r0)
30010210:	e12fff1e 	bx	lr

30010214 <s3c2440vector_init>:
30010214:	e92d4010 	push	{r4, lr}
30010218:	eb000001 	bl	30010224 <s3c2440vector_copy>
3001021c:	e8bd4010 	pop	{r4, lr}
30010220:	e12fff1e 	bx	lr

30010224 <s3c2440vector_copy>:
30010224:	e24dd010 	sub	sp, sp, #16	; 0x10
30010228:	e59f3098 	ldr	r3, [pc, #152]	; 300102c8 <s3c2440vector_copy+0xa4>
3001022c:	e58d3000 	str	r3, [sp]
30010230:	e59f3094 	ldr	r3, [pc, #148]	; 300102cc <s3c2440vector_copy+0xa8>
30010234:	e58d3004 	str	r3, [sp, #4]
30010238:	e3a03000 	mov	r3, #0	; 0x0
3001023c:	e58d3008 	str	r3, [sp, #8]
30010240:	e3a03000 	mov	r3, #0	; 0x0
30010244:	e58d300c 	str	r3, [sp, #12]
30010248:	ea000008 	b	30010270 <s3c2440vector_copy+0x4c>
3001024c:	e59d300c 	ldr	r3, [sp, #12]
30010250:	e1a02103 	lsl	r2, r3, #2
30010254:	e59d3008 	ldr	r3, [sp, #8]
30010258:	e0832002 	add	r2, r3, r2
3001025c:	e3a03000 	mov	r3, #0	; 0x0
30010260:	e5823000 	str	r3, [r2]
30010264:	e59d300c 	ldr	r3, [sp, #12]
30010268:	e2833001 	add	r3, r3, #1	; 0x1
3001026c:	e58d300c 	str	r3, [sp, #12]
30010270:	e59d200c 	ldr	r2, [sp, #12]
30010274:	e3a03eff 	mov	r3, #4080	; 0xff0
30010278:	e283300f 	add	r3, r3, #15	; 0xf
3001027c:	e1520003 	cmp	r2, r3
30010280:	9afffff1 	bls	3001024c <s3c2440vector_copy+0x28>
30010284:	ea000009 	b	300102b0 <s3c2440vector_copy+0x8c>
30010288:	e59d3004 	ldr	r3, [sp, #4]
3001028c:	e5932000 	ldr	r2, [r3]
30010290:	e59d3008 	ldr	r3, [sp, #8]
30010294:	e5832000 	str	r2, [r3]
30010298:	e59d3004 	ldr	r3, [sp, #4]
3001029c:	e2833004 	add	r3, r3, #4	; 0x4
300102a0:	e58d3004 	str	r3, [sp, #4]
300102a4:	e59d3008 	ldr	r3, [sp, #8]
300102a8:	e2833004 	add	r3, r3, #4	; 0x4
300102ac:	e58d3008 	str	r3, [sp, #8]
300102b0:	e59d2004 	ldr	r2, [sp, #4]
300102b4:	e59d3000 	ldr	r3, [sp]
300102b8:	e1520003 	cmp	r2, r3
300102bc:	3afffff1 	bcc	30010288 <s3c2440vector_copy+0x64>
300102c0:	e28dd010 	add	sp, sp, #16	; 0x10
300102c4:	e12fff1e 	bx	lr
300102c8:	30010430 	.word	0x30010430
300102cc:	30011940 	.word	0x30011940

Disassembly of section .lmosem_hal.intvect:

300102d0 <hal_undefins>:
300102d0:	e321f0d3 	msr	CPSR_c, #211	; 0xd3
300102d4:	e24dd040 	sub	sp, sp, #64	; 0x40
300102d8:	e8cd7fff 	stmia	sp, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr}^
300102dc:	e321f0db 	msr	CPSR_c, #219	; 0xdb
300102e0:	e24e1000 	sub	r1, lr, #0	; 0x0
300102e4:	e14f0000 	mrs	r0, SPSR
300102e8:	e321f0d3 	msr	CPSR_c, #211	; 0xd3
300102ec:	e58d103c 	str	r1, [sp, #60]
300102f0:	e92d4001 	push	{r0, lr}
300102f4:	e1a0000d 	mov	r0, sp
300102f8:	e8bd4001 	pop	{r0, lr}
300102fc:	e169f000 	msr	SPSR_fc, r0
30010300:	e8dd7fff 	ldm	sp, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr}^
30010304:	e28dd03c 	add	sp, sp, #60	; 0x3c
30010308:	e8fd8000 	ldm	sp!, {pc}^

3001030c <hal_swi>:
3001030c:	e2499040 	sub	r9, r9, #64	; 0x40
30010310:	e8cd7ffe 	stmia	sp, {r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr}^
30010314:	e14f1000 	mrs	r1, SPSR
30010318:	e58de03c 	str	lr, [sp, #60]
3001031c:	e92d4002 	push	{r1, lr}
30010320:	e1a0100d 	mov	r1, sp
30010324:	e8bd4002 	pop	{r1, lr}
30010328:	e169f001 	msr	SPSR_fc, r1
3001032c:	e8dd7ffe 	ldm	sp, {r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr}^
30010330:	e28dd03c 	add	sp, sp, #60	; 0x3c
30010334:	e8fd8000 	ldm	sp!, {pc}^

30010338 <hal_prefabt>:
30010338:	e321f0d3 	msr	CPSR_c, #211	; 0xd3
3001033c:	e24dd040 	sub	sp, sp, #64	; 0x40
30010340:	e8cd7fff 	stmia	sp, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr}^
30010344:	e321f0d7 	msr	CPSR_c, #215	; 0xd7
30010348:	e24e1004 	sub	r1, lr, #4	; 0x4
3001034c:	e14f0000 	mrs	r0, SPSR
30010350:	e58d103c 	str	r1, [sp, #60]
30010354:	e92d4001 	push	{r0, lr}
30010358:	e1a0000d 	mov	r0, sp
3001035c:	e8bd4001 	pop	{r0, lr}
30010360:	e169f000 	msr	SPSR_fc, r0
30010364:	e8dd7fff 	ldm	sp, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr}^
30010368:	e28dd03c 	add	sp, sp, #60	; 0x3c
3001036c:	e8fd8000 	ldm	sp!, {pc}^

30010370 <hal_dataabt>:
30010370:	e321f0d3 	msr	CPSR_c, #211	; 0xd3
30010374:	e24dd040 	sub	sp, sp, #64	; 0x40
30010378:	e8cd7fff 	stmia	sp, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr}^
3001037c:	e321f0d7 	msr	CPSR_c, #215	; 0xd7
30010380:	e24e1008 	sub	r1, lr, #8	; 0x8
30010384:	e14f0000 	mrs	r0, SPSR
30010388:	e321f0d3 	msr	CPSR_c, #211	; 0xd3
3001038c:	e58d103c 	str	r1, [sp, #60]
30010390:	e92d4001 	push	{r0, lr}
30010394:	e1a0000d 	mov	r0, sp
30010398:	e8bd4001 	pop	{r0, lr}
3001039c:	e169f000 	msr	SPSR_fc, r0
300103a0:	e8dd7fff 	ldm	sp, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr}^
300103a4:	e28dd03c 	add	sp, sp, #60	; 0x3c
300103a8:	e8fd8000 	ldm	sp!, {pc}^

300103ac <hal_bugdie>:
300103ac:	eafffffe 	b	300103ac <hal_bugdie>

300103b0 <hal_irq>:
300103b0:	e321f0d3 	msr	CPSR_c, #211	; 0xd3
300103b4:	e24dd040 	sub	sp, sp, #64	; 0x40
300103b8:	e8cd7fff 	stmia	sp, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr}^
300103bc:	e321f0d2 	msr	CPSR_c, #210	; 0xd2
300103c0:	e24e1004 	sub	r1, lr, #4	; 0x4
300103c4:	e14f0000 	mrs	r0, SPSR
300103c8:	e321f0d3 	msr	CPSR_c, #211	; 0xd3
300103cc:	e58d103c 	str	r1, [sp, #60]
300103d0:	e92d4001 	push	{r0, lr}
300103d4:	e1a0000d 	mov	r0, sp
300103d8:	e8bd4001 	pop	{r0, lr}
300103dc:	e169f000 	msr	SPSR_fc, r0
300103e0:	e8dd7fff 	ldm	sp, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr}^
300103e4:	e28dd03c 	add	sp, sp, #60	; 0x3c
300103e8:	e8fd8000 	ldm	sp!, {pc}^

300103ec <hal_frq>:
300103ec:	e321f0d3 	msr	CPSR_c, #211	; 0xd3
300103f0:	e24dd040 	sub	sp, sp, #64	; 0x40
300103f4:	e8cd7fff 	stmia	sp, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr}^
300103f8:	e321f0d1 	msr	CPSR_c, #209	; 0xd1
300103fc:	e24e1004 	sub	r1, lr, #4	; 0x4
30010400:	e14f0000 	mrs	r0, SPSR
30010404:	e321f0d3 	msr	CPSR_c, #211	; 0xd3
30010408:	e58d103c 	str	r1, [sp, #60]
3001040c:	e92d4001 	push	{r0, lr}
30010410:	e1a0000d 	mov	r0, sp
30010414:	e8bd4001 	pop	{r0, lr}
30010418:	e169f000 	msr	SPSR_fc, r0
3001041c:	e8dd7fff 	ldm	sp, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr}^
30010420:	e28dd03c 	add	sp, sp, #60	; 0x3c
30010424:	e8fd8000 	ldm	sp!, {pc}^
30010428:	e1a00000 	nop			(mov r0,r0)
3001042c:	e1a00000 	nop			(mov r0,r0)

Disassembly of section .text:

30010430 <lmosemhal_start>:
30010430:	eafffffe 	b	30010430 <lmosemhal_start>
30010434:	e12fff1e 	bx	lr

30010438 <hal_dbug_print_reg>:
30010438:	e92d4010 	push	{r4, lr}
3001043c:	e24dd008 	sub	sp, sp, #8	; 0x8
30010440:	e58d0004 	str	r0, [sp, #4]
30010444:	e59d3004 	ldr	r3, [sp, #4]
30010448:	e5933008 	ldr	r3, [r3, #8]
3001044c:	e59f0198 	ldr	r0, [pc, #408]	; 300105ec <hal_dbug_print_reg+0x1b4>
30010450:	e1a01003 	mov	r1, r3
30010454:	eb0001af 	bl	30010b18 <printfk>
30010458:	e59d3004 	ldr	r3, [sp, #4]
3001045c:	e593300c 	ldr	r3, [r3, #12]
30010460:	e59f0188 	ldr	r0, [pc, #392]	; 300105f0 <hal_dbug_print_reg+0x1b8>
30010464:	e1a01003 	mov	r1, r3
30010468:	eb0001aa 	bl	30010b18 <printfk>
3001046c:	e59d3004 	ldr	r3, [sp, #4]
30010470:	e5933010 	ldr	r3, [r3, #16]
30010474:	e59f0178 	ldr	r0, [pc, #376]	; 300105f4 <hal_dbug_print_reg+0x1bc>
30010478:	e1a01003 	mov	r1, r3
3001047c:	eb0001a5 	bl	30010b18 <printfk>
30010480:	e59d3004 	ldr	r3, [sp, #4]
30010484:	e5933014 	ldr	r3, [r3, #20]
30010488:	e59f0168 	ldr	r0, [pc, #360]	; 300105f8 <hal_dbug_print_reg+0x1c0>
3001048c:	e1a01003 	mov	r1, r3
30010490:	eb0001a0 	bl	30010b18 <printfk>
30010494:	e59d3004 	ldr	r3, [sp, #4]
30010498:	e5933018 	ldr	r3, [r3, #24]
3001049c:	e59f0158 	ldr	r0, [pc, #344]	; 300105fc <hal_dbug_print_reg+0x1c4>
300104a0:	e1a01003 	mov	r1, r3
300104a4:	eb00019b 	bl	30010b18 <printfk>
300104a8:	e59d3004 	ldr	r3, [sp, #4]
300104ac:	e593301c 	ldr	r3, [r3, #28]
300104b0:	e59f0148 	ldr	r0, [pc, #328]	; 30010600 <hal_dbug_print_reg+0x1c8>
300104b4:	e1a01003 	mov	r1, r3
300104b8:	eb000196 	bl	30010b18 <printfk>
300104bc:	e59d3004 	ldr	r3, [sp, #4]
300104c0:	e5933020 	ldr	r3, [r3, #32]
300104c4:	e59f0138 	ldr	r0, [pc, #312]	; 30010604 <hal_dbug_print_reg+0x1cc>
300104c8:	e1a01003 	mov	r1, r3
300104cc:	eb000191 	bl	30010b18 <printfk>
300104d0:	e59d3004 	ldr	r3, [sp, #4]
300104d4:	e5933024 	ldr	r3, [r3, #36]
300104d8:	e59f0128 	ldr	r0, [pc, #296]	; 30010608 <hal_dbug_print_reg+0x1d0>
300104dc:	e1a01003 	mov	r1, r3
300104e0:	eb00018c 	bl	30010b18 <printfk>
300104e4:	e59d3004 	ldr	r3, [sp, #4]
300104e8:	e5933028 	ldr	r3, [r3, #40]
300104ec:	e59f0118 	ldr	r0, [pc, #280]	; 3001060c <hal_dbug_print_reg+0x1d4>
300104f0:	e1a01003 	mov	r1, r3
300104f4:	eb000187 	bl	30010b18 <printfk>
300104f8:	e59d3004 	ldr	r3, [sp, #4]
300104fc:	e593302c 	ldr	r3, [r3, #44]
30010500:	e59f0108 	ldr	r0, [pc, #264]	; 30010610 <hal_dbug_print_reg+0x1d8>
30010504:	e1a01003 	mov	r1, r3
30010508:	eb000182 	bl	30010b18 <printfk>
3001050c:	e59d3004 	ldr	r3, [sp, #4]
30010510:	e5933030 	ldr	r3, [r3, #48]
30010514:	e59f00f8 	ldr	r0, [pc, #248]	; 30010614 <hal_dbug_print_reg+0x1dc>
30010518:	e1a01003 	mov	r1, r3
3001051c:	eb00017d 	bl	30010b18 <printfk>
30010520:	e59d3004 	ldr	r3, [sp, #4]
30010524:	e5933034 	ldr	r3, [r3, #52]
30010528:	e59f00e8 	ldr	r0, [pc, #232]	; 30010618 <hal_dbug_print_reg+0x1e0>
3001052c:	e1a01003 	mov	r1, r3
30010530:	eb000178 	bl	30010b18 <printfk>
30010534:	e59d3004 	ldr	r3, [sp, #4]
30010538:	e5933038 	ldr	r3, [r3, #56]
3001053c:	e59f00d8 	ldr	r0, [pc, #216]	; 3001061c <hal_dbug_print_reg+0x1e4>
30010540:	e1a01003 	mov	r1, r3
30010544:	eb000173 	bl	30010b18 <printfk>
30010548:	e59d3004 	ldr	r3, [sp, #4]
3001054c:	e593303c 	ldr	r3, [r3, #60]
30010550:	e59f00c8 	ldr	r0, [pc, #200]	; 30010620 <hal_dbug_print_reg+0x1e8>
30010554:	e1a01003 	mov	r1, r3
30010558:	eb00016e 	bl	30010b18 <printfk>
3001055c:	e59d3004 	ldr	r3, [sp, #4]
30010560:	e5933040 	ldr	r3, [r3, #64]
30010564:	e59f00b8 	ldr	r0, [pc, #184]	; 30010624 <hal_dbug_print_reg+0x1ec>
30010568:	e1a01003 	mov	r1, r3
3001056c:	eb000169 	bl	30010b18 <printfk>
30010570:	e59d3004 	ldr	r3, [sp, #4]
30010574:	e5933044 	ldr	r3, [r3, #68]
30010578:	e59f00a8 	ldr	r0, [pc, #168]	; 30010628 <hal_dbug_print_reg+0x1f0>
3001057c:	e1a01003 	mov	r1, r3
30010580:	eb000164 	bl	30010b18 <printfk>
30010584:	e59d3004 	ldr	r3, [sp, #4]
30010588:	e5933000 	ldr	r3, [r3]
3001058c:	e59f0098 	ldr	r0, [pc, #152]	; 3001062c <hal_dbug_print_reg+0x1f4>
30010590:	e1a01003 	mov	r1, r3
30010594:	eb00015f 	bl	30010b18 <printfk>
30010598:	eb000294 	bl	30010ff0 <hal_read_currmodesp>
3001059c:	e1a04000 	mov	r4, r0
300105a0:	e3a0044a 	mov	r0, #1241513984	; 0x4a000000
300105a4:	e2800010 	add	r0, r0, #16	; 0x10
300105a8:	eb0002f6 	bl	30011188 <hal_io32_read>
300105ac:	e1a03000 	mov	r3, r0
300105b0:	e59f0078 	ldr	r0, [pc, #120]	; 30010630 <hal_dbug_print_reg+0x1f8>
300105b4:	e1a01004 	mov	r1, r4
300105b8:	e1a02003 	mov	r2, r3
300105bc:	eb000155 	bl	30010b18 <printfk>
300105c0:	eb000293 	bl	30011014 <hal_read_cpuflg>
300105c4:	e1a04000 	mov	r4, r0
300105c8:	eb000388 	bl	300113f0 <hal_retn_cpuid>
300105cc:	e1a03000 	mov	r3, r0
300105d0:	e59f005c 	ldr	r0, [pc, #92]	; 30010634 <hal_dbug_print_reg+0x1fc>
300105d4:	e1a01004 	mov	r1, r4
300105d8:	e1a02003 	mov	r2, r3
300105dc:	eb00014d 	bl	30010b18 <printfk>
300105e0:	e28dd008 	add	sp, sp, #8	; 0x8
300105e4:	e8bd4010 	pop	{r4, lr}
300105e8:	e12fff1e 	bx	lr
300105ec:	30012868 	.word	0x30012868
300105f0:	30012878 	.word	0x30012878
300105f4:	30012888 	.word	0x30012888
300105f8:	30012898 	.word	0x30012898
300105fc:	300128a8 	.word	0x300128a8
30010600:	300128b8 	.word	0x300128b8
30010604:	300128c8 	.word	0x300128c8
30010608:	300128d8 	.word	0x300128d8
3001060c:	300128e8 	.word	0x300128e8
30010610:	300128f8 	.word	0x300128f8
30010614:	30012908 	.word	0x30012908
30010618:	3001291c 	.word	0x3001291c
3001061c:	30012930 	.word	0x30012930
30010620:	30012944 	.word	0x30012944
30010624:	30012958 	.word	0x30012958
30010628:	3001296c 	.word	0x3001296c
3001062c:	3001297c 	.word	0x3001297c
30010630:	30012990 	.word	0x30012990
30010634:	300129ac 	.word	0x300129ac

30010638 <hal_undefins_distr>:
30010638:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
3001063c:	e24dd00c 	sub	sp, sp, #12	; 0xc
30010640:	e58d0004 	str	r0, [sp, #4]
30010644:	e59f000c 	ldr	r0, [pc, #12]	; 30010658 <hal_undefins_distr+0x20>
30010648:	eb00035d 	bl	300113c4 <hal_sysdie>
3001064c:	e28dd00c 	add	sp, sp, #12	; 0xc
30010650:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
30010654:	e12fff1e 	bx	lr
30010658:	300129cc 	.word	0x300129cc

3001065c <hal_swi_distr>:
3001065c:	e24dd010 	sub	sp, sp, #16	; 0x10
30010660:	e58d0004 	str	r0, [sp, #4]
30010664:	e58d1000 	str	r1, [sp]
30010668:	e3a03000 	mov	r3, #0	; 0x0
3001066c:	e58d300c 	str	r3, [sp, #12]
30010670:	e59d300c 	ldr	r3, [sp, #12]
30010674:	e1a00003 	mov	r0, r3
30010678:	e28dd010 	add	sp, sp, #16	; 0x10
3001067c:	e12fff1e 	bx	lr

30010680 <hal_prefabt_distr>:
30010680:	e92d4010 	push	{r4, lr}
30010684:	e24dd008 	sub	sp, sp, #8	; 0x8
30010688:	e58d0004 	str	r0, [sp, #4]
3001068c:	e3a00005 	mov	r0, #5	; 0x5
30010690:	eb00036d 	bl	3001144c <hal_read_cp15regs>
30010694:	e1a04000 	mov	r4, r0
30010698:	e3a00006 	mov	r0, #6	; 0x6
3001069c:	eb00036a 	bl	3001144c <hal_read_cp15regs>
300106a0:	e1a03000 	mov	r3, r0
300106a4:	e59f0028 	ldr	r0, [pc, #40]	; 300106d4 <hal_prefabt_distr+0x54>
300106a8:	e1a01004 	mov	r1, r4
300106ac:	e1a02003 	mov	r2, r3
300106b0:	eb000118 	bl	30010b18 <printfk>
300106b4:	e59d3004 	ldr	r3, [sp, #4]
300106b8:	e1a00003 	mov	r0, r3
300106bc:	ebffff5d 	bl	30010438 <hal_dbug_print_reg>
300106c0:	e59f0010 	ldr	r0, [pc, #16]	; 300106d8 <hal_prefabt_distr+0x58>
300106c4:	eb00033e 	bl	300113c4 <hal_sysdie>
300106c8:	e28dd008 	add	sp, sp, #8	; 0x8
300106cc:	e8bd4010 	pop	{r4, lr}
300106d0:	e12fff1e 	bx	lr
300106d4:	300129e0 	.word	0x300129e0
300106d8:	300129f4 	.word	0x300129f4

300106dc <hal_dataabt_distr>:
300106dc:	e92d4010 	push	{r4, lr}
300106e0:	e24dd008 	sub	sp, sp, #8	; 0x8
300106e4:	e58d0004 	str	r0, [sp, #4]
300106e8:	e3a00005 	mov	r0, #5	; 0x5
300106ec:	eb000356 	bl	3001144c <hal_read_cp15regs>
300106f0:	e1a04000 	mov	r4, r0
300106f4:	e3a00006 	mov	r0, #6	; 0x6
300106f8:	eb000353 	bl	3001144c <hal_read_cp15regs>
300106fc:	e1a03000 	mov	r3, r0
30010700:	e59f0028 	ldr	r0, [pc, #40]	; 30010730 <hal_dataabt_distr+0x54>
30010704:	e1a01004 	mov	r1, r4
30010708:	e1a02003 	mov	r2, r3
3001070c:	eb000101 	bl	30010b18 <printfk>
30010710:	e59d3004 	ldr	r3, [sp, #4]
30010714:	e1a00003 	mov	r0, r3
30010718:	ebffff46 	bl	30010438 <hal_dbug_print_reg>
3001071c:	e59f0010 	ldr	r0, [pc, #16]	; 30010734 <hal_dataabt_distr+0x58>
30010720:	eb000327 	bl	300113c4 <hal_sysdie>
30010724:	e28dd008 	add	sp, sp, #8	; 0x8
30010728:	e8bd4010 	pop	{r4, lr}
3001072c:	e12fff1e 	bx	lr
30010730:	300129e0 	.word	0x300129e0
30010734:	30012a04 	.word	0x30012a04

30010738 <hal_bugdie_distr>:
30010738:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
3001073c:	e24dd00c 	sub	sp, sp, #12	; 0xc
30010740:	e58d0004 	str	r0, [sp, #4]
30010744:	e59f000c 	ldr	r0, [pc, #12]	; 30010758 <hal_bugdie_distr+0x20>
30010748:	eb00031d 	bl	300113c4 <hal_sysdie>
3001074c:	e28dd00c 	add	sp, sp, #12	; 0xc
30010750:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
30010754:	e12fff1e 	bx	lr
30010758:	30012a14 	.word	0x30012a14

3001075c <hal_dbugint>:
3001075c:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
30010760:	e24dd00c 	sub	sp, sp, #12	; 0xc
30010764:	e58d0004 	str	r0, [sp, #4]
30010768:	e59f001c 	ldr	r0, [pc, #28]	; 3001078c <hal_dbugint+0x30>
3001076c:	e59d1004 	ldr	r1, [sp, #4]
30010770:	eb0000e8 	bl	30010b18 <printfk>
30010774:	e59f0010 	ldr	r0, [pc, #16]	; 3001078c <hal_dbugint+0x30>
30010778:	e59d1004 	ldr	r1, [sp, #4]
3001077c:	eb0000e5 	bl	30010b18 <printfk>
30010780:	e28dd00c 	add	sp, sp, #12	; 0xc
30010784:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
30010788:	e12fff1e 	bx	lr
3001078c:	30012a24 	.word	0x30012a24

30010790 <hal_dbugint2>:
30010790:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
30010794:	e24dd00c 	sub	sp, sp, #12	; 0xc
30010798:	e58d0004 	str	r0, [sp, #4]
3001079c:	e59f001c 	ldr	r0, [pc, #28]	; 300107c0 <hal_dbugint2+0x30>
300107a0:	e59d1004 	ldr	r1, [sp, #4]
300107a4:	eb0000db 	bl	30010b18 <printfk>
300107a8:	e59f0010 	ldr	r0, [pc, #16]	; 300107c0 <hal_dbugint2+0x30>
300107ac:	e59d1004 	ldr	r1, [sp, #4]
300107b0:	eb0000d8 	bl	30010b18 <printfk>
300107b4:	e28dd00c 	add	sp, sp, #12	; 0xc
300107b8:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
300107bc:	e12fff1e 	bx	lr
300107c0:	30012a38 	.word	0x30012a38

300107c4 <hal_irq_distr>:
300107c4:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
300107c8:	e24dd014 	sub	sp, sp, #20	; 0x14
300107cc:	e58d0004 	str	r0, [sp, #4]
300107d0:	e3a03000 	mov	r3, #0	; 0x0
300107d4:	e58d300c 	str	r3, [sp, #12]
300107d8:	e59d300c 	ldr	r3, [sp, #12]
300107dc:	e58d3000 	str	r3, [sp]
300107e0:	e59d3000 	ldr	r3, [sp]
300107e4:	e3530004 	cmp	r3, #4	; 0x4
300107e8:	0a000003 	beq	300107fc <hal_irq_distr+0x38>
300107ec:	e59d3000 	ldr	r3, [sp]
300107f0:	e3530005 	cmp	r3, #5	; 0x5
300107f4:	0a000006 	beq	30010814 <hal_irq_distr+0x50>
300107f8:	ea00000b 	b	3001082c <hal_irq_distr+0x68>
300107fc:	e59d0004 	ldr	r0, [sp, #4]
30010800:	e59d100c 	ldr	r1, [sp, #12]
30010804:	e3a02004 	mov	r2, #4	; 0x4
30010808:	e3a03008 	mov	r3, #8	; 0x8
3001080c:	eb000015 	bl	30010868 <hal_eint_distr>
30010810:	ea000008 	b	30010838 <hal_irq_distr+0x74>
30010814:	e59d0004 	ldr	r0, [sp, #4]
30010818:	e59d100c 	ldr	r1, [sp, #12]
3001081c:	e3a02008 	mov	r2, #8	; 0x8
30010820:	e3a03018 	mov	r3, #24	; 0x18
30010824:	eb00000f 	bl	30010868 <hal_eint_distr>
30010828:	ea000002 	b	30010838 <hal_irq_distr+0x74>
3001082c:	e59d0004 	ldr	r0, [sp, #4]
30010830:	e59d100c 	ldr	r1, [sp, #12]
30010834:	eb000081 	bl	30010a40 <hal_int_distr>
30010838:	e28dd014 	add	sp, sp, #20	; 0x14
3001083c:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
30010840:	e12fff1e 	bx	lr

30010844 <hal_frq_distr>:
30010844:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
30010848:	e24dd00c 	sub	sp, sp, #12	; 0xc
3001084c:	e58d0004 	str	r0, [sp, #4]
30010850:	e59f000c 	ldr	r0, [pc, #12]	; 30010864 <hal_frq_distr+0x20>
30010854:	eb0002da 	bl	300113c4 <hal_sysdie>
30010858:	e28dd00c 	add	sp, sp, #12	; 0xc
3001085c:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
30010860:	e12fff1e 	bx	lr
30010864:	30012a4c 	.word	0x30012a4c

30010868 <hal_eint_distr>:
30010868:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
3001086c:	e24dd01c 	sub	sp, sp, #28	; 0x1c
30010870:	e58d000c 	str	r0, [sp, #12]
30010874:	e58d1008 	str	r1, [sp, #8]
30010878:	e58d2004 	str	r2, [sp, #4]
3001087c:	e58d3000 	str	r3, [sp]
30010880:	e3a00456 	mov	r0, #1442840576	; 0x56000000
30010884:	e28000a8 	add	r0, r0, #168	; 0xa8
30010888:	eb00023e 	bl	30011188 <hal_io32_read>
3001088c:	e1a03000 	mov	r3, r0
30010890:	e58d3010 	str	r3, [sp, #16]
30010894:	e59d3010 	ldr	r3, [sp, #16]
30010898:	e3c334ff 	bic	r3, r3, #-16777216	; 0xff000000
3001089c:	e58d3010 	str	r3, [sp, #16]
300108a0:	e59d3004 	ldr	r3, [sp, #4]
300108a4:	e58d3014 	str	r3, [sp, #20]
300108a8:	ea00000e 	b	300108e8 <hal_eint_distr+0x80>
300108ac:	e59d2014 	ldr	r2, [sp, #20]
300108b0:	e59d3010 	ldr	r3, [sp, #16]
300108b4:	e1a03233 	lsr	r3, r3, r2
300108b8:	e2033001 	and	r3, r3, #1	; 0x1
300108bc:	e20330ff 	and	r3, r3, #255	; 0xff
300108c0:	e3530000 	cmp	r3, #0	; 0x0
300108c4:	0a000004 	beq	300108dc <hal_eint_distr+0x74>
300108c8:	e59d3014 	ldr	r3, [sp, #20]
300108cc:	e283302f 	add	r3, r3, #47	; 0x2f
300108d0:	e1a00003 	mov	r0, r3
300108d4:	e59d100c 	ldr	r1, [sp, #12]
300108d8:	eb000062 	bl	30010a68 <hal_run_intflthandle>
300108dc:	e59d3014 	ldr	r3, [sp, #20]
300108e0:	e2833001 	add	r3, r3, #1	; 0x1
300108e4:	e58d3014 	str	r3, [sp, #20]
300108e8:	e59d2014 	ldr	r2, [sp, #20]
300108ec:	e59d3000 	ldr	r3, [sp]
300108f0:	e1520003 	cmp	r2, r3
300108f4:	3affffec 	bcc	300108ac <hal_eint_distr+0x44>
300108f8:	e28dd01c 	add	sp, sp, #28	; 0x1c
300108fc:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
30010900:	e12fff1e 	bx	lr

30010904 <hal_sint_distr>:
30010904:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
30010908:	e24dd01c 	sub	sp, sp, #28	; 0x1c
3001090c:	e58d000c 	str	r0, [sp, #12]
30010910:	e58d1008 	str	r1, [sp, #8]
30010914:	e58d2004 	str	r2, [sp, #4]
30010918:	e58d3000 	str	r3, [sp]
3001091c:	e3a0044a 	mov	r0, #1241513984	; 0x4a000000
30010920:	e2800018 	add	r0, r0, #24	; 0x18
30010924:	eb000217 	bl	30011188 <hal_io32_read>
30010928:	e1a03000 	mov	r3, r0
3001092c:	e58d3010 	str	r3, [sp, #16]
30010930:	e59d3010 	ldr	r3, [sp, #16]
30010934:	e1a03883 	lsl	r3, r3, #17
30010938:	e1a038a3 	lsr	r3, r3, #17
3001093c:	e58d3010 	str	r3, [sp, #16]
30010940:	e59d3004 	ldr	r3, [sp, #4]
30010944:	e58d3014 	str	r3, [sp, #20]
30010948:	ea00000e 	b	30010988 <hal_sint_distr+0x84>
3001094c:	e59d2014 	ldr	r2, [sp, #20]
30010950:	e59d3010 	ldr	r3, [sp, #16]
30010954:	e1a03233 	lsr	r3, r3, r2
30010958:	e2033001 	and	r3, r3, #1	; 0x1
3001095c:	e20330ff 	and	r3, r3, #255	; 0xff
30010960:	e3530000 	cmp	r3, #0	; 0x0
30010964:	0a000004 	beq	3001097c <hal_sint_distr+0x78>
30010968:	e59d3014 	ldr	r3, [sp, #20]
3001096c:	e283302f 	add	r3, r3, #47	; 0x2f
30010970:	e1a00003 	mov	r0, r3
30010974:	e59d100c 	ldr	r1, [sp, #12]
30010978:	eb00003a 	bl	30010a68 <hal_run_intflthandle>
3001097c:	e59d3014 	ldr	r3, [sp, #20]
30010980:	e2833001 	add	r3, r3, #1	; 0x1
30010984:	e58d3014 	str	r3, [sp, #20]
30010988:	e59d2014 	ldr	r2, [sp, #20]
3001098c:	e59d3000 	ldr	r3, [sp]
30010990:	e1520003 	cmp	r2, r3
30010994:	3affffec 	bcc	3001094c <hal_sint_distr+0x48>
30010998:	e28dd01c 	add	sp, sp, #28	; 0x1c
3001099c:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
300109a0:	e12fff1e 	bx	lr

300109a4 <hal_lcdint_distr>:
300109a4:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
300109a8:	e24dd01c 	sub	sp, sp, #28	; 0x1c
300109ac:	e58d000c 	str	r0, [sp, #12]
300109b0:	e58d1008 	str	r1, [sp, #8]
300109b4:	e58d2004 	str	r2, [sp, #4]
300109b8:	e58d3000 	str	r3, [sp]
300109bc:	e3a0044d 	mov	r0, #1291845632	; 0x4d000000
300109c0:	e2800054 	add	r0, r0, #84	; 0x54
300109c4:	eb0001ef 	bl	30011188 <hal_io32_read>
300109c8:	e1a03000 	mov	r3, r0
300109cc:	e58d3010 	str	r3, [sp, #16]
300109d0:	e59d3010 	ldr	r3, [sp, #16]
300109d4:	e2033003 	and	r3, r3, #3	; 0x3
300109d8:	e58d3010 	str	r3, [sp, #16]
300109dc:	e59d3004 	ldr	r3, [sp, #4]
300109e0:	e58d3014 	str	r3, [sp, #20]
300109e4:	ea00000e 	b	30010a24 <hal_lcdint_distr+0x80>
300109e8:	e59d2014 	ldr	r2, [sp, #20]
300109ec:	e59d3010 	ldr	r3, [sp, #16]
300109f0:	e1a03233 	lsr	r3, r3, r2
300109f4:	e2033001 	and	r3, r3, #1	; 0x1
300109f8:	e20330ff 	and	r3, r3, #255	; 0xff
300109fc:	e3530000 	cmp	r3, #0	; 0x0
30010a00:	0a000004 	beq	30010a18 <hal_lcdint_distr+0x74>
30010a04:	e59d3014 	ldr	r3, [sp, #20]
30010a08:	e283302f 	add	r3, r3, #47	; 0x2f
30010a0c:	e1a00003 	mov	r0, r3
30010a10:	e59d100c 	ldr	r1, [sp, #12]
30010a14:	eb000013 	bl	30010a68 <hal_run_intflthandle>
30010a18:	e59d3014 	ldr	r3, [sp, #20]
30010a1c:	e2833001 	add	r3, r3, #1	; 0x1
30010a20:	e58d3014 	str	r3, [sp, #20]
30010a24:	e59d2014 	ldr	r2, [sp, #20]
30010a28:	e59d3000 	ldr	r3, [sp]
30010a2c:	e1520003 	cmp	r2, r3
30010a30:	3affffec 	bcc	300109e8 <hal_lcdint_distr+0x44>
30010a34:	e28dd01c 	add	sp, sp, #28	; 0x1c
30010a38:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
30010a3c:	e12fff1e 	bx	lr

30010a40 <hal_int_distr>:
30010a40:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
30010a44:	e24dd00c 	sub	sp, sp, #12	; 0xc
30010a48:	e58d0004 	str	r0, [sp, #4]
30010a4c:	e58d1000 	str	r1, [sp]
30010a50:	e59d0000 	ldr	r0, [sp]
30010a54:	e59d1004 	ldr	r1, [sp, #4]
30010a58:	eb000002 	bl	30010a68 <hal_run_intflthandle>
30010a5c:	e28dd00c 	add	sp, sp, #12	; 0xc
30010a60:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
30010a64:	e12fff1e 	bx	lr

30010a68 <hal_run_intflthandle>:
30010a68:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
30010a6c:	e24dd01c 	sub	sp, sp, #28	; 0x1c
30010a70:	e58d0004 	str	r0, [sp, #4]
30010a74:	e58d1000 	str	r1, [sp]
30010a78:	e3a03000 	mov	r3, #0	; 0x0
30010a7c:	e58d3014 	str	r3, [sp, #20]
30010a80:	e59d3014 	ldr	r3, [sp, #20]
30010a84:	e3530000 	cmp	r3, #0	; 0x0
30010a88:	1a000002 	bne	30010a98 <hal_run_intflthandle+0x30>
30010a8c:	e59f006c 	ldr	r0, [pc, #108]	; 30010b00 <hal_run_intflthandle+0x98>
30010a90:	eb00024b 	bl	300113c4 <hal_sysdie>
30010a94:	ea000016 	b	30010af4 <hal_run_intflthandle+0x8c>
30010a98:	e59d3014 	ldr	r3, [sp, #20]
30010a9c:	e5933008 	ldr	r3, [r3, #8]
30010aa0:	e58d3010 	str	r3, [sp, #16]
30010aa4:	ea00000d 	b	30010ae0 <hal_run_intflthandle+0x78>
30010aa8:	e59d3010 	ldr	r3, [sp, #16]
30010aac:	e58d300c 	str	r3, [sp, #12]
30010ab0:	e59d300c 	ldr	r3, [sp, #12]
30010ab4:	e593c020 	ldr	ip, [r3, #32]
30010ab8:	e59d300c 	ldr	r3, [sp, #12]
30010abc:	e5933018 	ldr	r3, [r3, #24]
30010ac0:	e59d0004 	ldr	r0, [sp, #4]
30010ac4:	e1a01003 	mov	r1, r3
30010ac8:	e59d2000 	ldr	r2, [sp]
30010acc:	e1a0e00f 	mov	lr, pc
30010ad0:	e12fff1c 	bx	ip
30010ad4:	e59d3010 	ldr	r3, [sp, #16]
30010ad8:	e5933004 	ldr	r3, [r3, #4]
30010adc:	e58d3010 	str	r3, [sp, #16]
30010ae0:	e59d3014 	ldr	r3, [sp, #20]
30010ae4:	e2832004 	add	r2, r3, #4	; 0x4
30010ae8:	e59d3010 	ldr	r3, [sp, #16]
30010aec:	e1520003 	cmp	r2, r3
30010af0:	1affffec 	bne	30010aa8 <hal_run_intflthandle+0x40>
30010af4:	e28dd01c 	add	sp, sp, #28	; 0x1c
30010af8:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
30010afc:	e12fff1e 	bx	lr
30010b00:	30012a5c 	.word	0x30012a5c

30010b04 <init_platform>:
30010b04:	e92d4010 	push	{r4, lr}
30010b08:	ebfffd75 	bl	300100e4 <s3c2440mmu_init>
30010b0c:	ebfffdc0 	bl	30010214 <s3c2440vector_init>
30010b10:	e8bd4010 	pop	{r4, lr}
30010b14:	e12fff1e 	bx	lr

30010b18 <printfk>:
30010b18:	e92d000f 	push	{r0, r1, r2, r3}
30010b1c:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
30010b20:	e24ddf83 	sub	sp, sp, #524	; 0x20c
30010b24:	e28d3f85 	add	r3, sp, #532	; 0x214
30010b28:	e58d3000 	str	r3, [sp]
30010b2c:	e28d3004 	add	r3, sp, #4	; 0x4
30010b30:	e1a00003 	mov	r0, r3
30010b34:	eb00011b 	bl	30010fa8 <hal_disableirqfiq_savecpuflg>
30010b38:	e28d3008 	add	r3, sp, #8	; 0x8
30010b3c:	e1a00003 	mov	r0, r3
30010b40:	e59d1210 	ldr	r1, [sp, #528]
30010b44:	e59d2000 	ldr	r2, [sp]
30010b48:	eb000021 	bl	30010bd4 <vsprintfk>
30010b4c:	e28d3008 	add	r3, sp, #8	; 0x8
30010b50:	e3a00000 	mov	r0, #0	; 0x0
30010b54:	e1a01003 	mov	r1, r3
30010b58:	e3a02000 	mov	r2, #0	; 0x0
30010b5c:	eb000285 	bl	30011578 <hal_uart_write>
30010b60:	e28d3004 	add	r3, sp, #4	; 0x4
30010b64:	e1a00003 	mov	r0, r3
30010b68:	eb000119 	bl	30010fd4 <hal_enableirqfiq_restcpuflg>
30010b6c:	e28ddf83 	add	sp, sp, #524	; 0x20c
30010b70:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
30010b74:	e28dd010 	add	sp, sp, #16	; 0x10
30010b78:	e12fff1e 	bx	lr

30010b7c <strcopyk>:
30010b7c:	e24dd008 	sub	sp, sp, #8	; 0x8
30010b80:	e58d0004 	str	r0, [sp, #4]
30010b84:	e58d1000 	str	r1, [sp]
30010b88:	ea000009 	b	30010bb4 <strcopyk+0x38>
30010b8c:	e59d3000 	ldr	r3, [sp]
30010b90:	e5d33000 	ldrb	r3, [r3]
30010b94:	e59d2004 	ldr	r2, [sp, #4]
30010b98:	e5c23000 	strb	r3, [r2]
30010b9c:	e59d3004 	ldr	r3, [sp, #4]
30010ba0:	e2833001 	add	r3, r3, #1	; 0x1
30010ba4:	e58d3004 	str	r3, [sp, #4]
30010ba8:	e59d3000 	ldr	r3, [sp]
30010bac:	e2833001 	add	r3, r3, #1	; 0x1
30010bb0:	e58d3000 	str	r3, [sp]
30010bb4:	e59d3000 	ldr	r3, [sp]
30010bb8:	e5d33000 	ldrb	r3, [r3]
30010bbc:	e3530000 	cmp	r3, #0	; 0x0
30010bc0:	1afffff1 	bne	30010b8c <strcopyk+0x10>
30010bc4:	e59d3004 	ldr	r3, [sp, #4]
30010bc8:	e1a00003 	mov	r0, r3
30010bcc:	e28dd008 	add	sp, sp, #8	; 0x8
30010bd0:	e12fff1e 	bx	lr

30010bd4 <vsprintfk>:
30010bd4:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
30010bd8:	e24dd01c 	sub	sp, sp, #28	; 0x1c
30010bdc:	e58d000c 	str	r0, [sp, #12]
30010be0:	e58d1008 	str	r1, [sp, #8]
30010be4:	e58d2004 	str	r2, [sp, #4]
30010be8:	e59d300c 	ldr	r3, [sp, #12]
30010bec:	e58d3014 	str	r3, [sp, #20]
30010bf0:	e59d3004 	ldr	r3, [sp, #4]
30010bf4:	e58d3010 	str	r3, [sp, #16]
30010bf8:	ea000049 	b	30010d24 <vsprintfk+0x150>
30010bfc:	e59d3008 	ldr	r3, [sp, #8]
30010c00:	e5d33000 	ldrb	r3, [r3]
30010c04:	e3530025 	cmp	r3, #37	; 0x25
30010c08:	0a00000a 	beq	30010c38 <vsprintfk+0x64>
30010c0c:	e59d3008 	ldr	r3, [sp, #8]
30010c10:	e5d33000 	ldrb	r3, [r3]
30010c14:	e59d2014 	ldr	r2, [sp, #20]
30010c18:	e5c23000 	strb	r3, [r2]
30010c1c:	e59d3014 	ldr	r3, [sp, #20]
30010c20:	e2833001 	add	r3, r3, #1	; 0x1
30010c24:	e58d3014 	str	r3, [sp, #20]
30010c28:	e59d3008 	ldr	r3, [sp, #8]
30010c2c:	e2833001 	add	r3, r3, #1	; 0x1
30010c30:	e58d3008 	str	r3, [sp, #8]
30010c34:	ea00003a 	b	30010d24 <vsprintfk+0x150>
30010c38:	e59d3008 	ldr	r3, [sp, #8]
30010c3c:	e2833001 	add	r3, r3, #1	; 0x1
30010c40:	e58d3008 	str	r3, [sp, #8]
30010c44:	e59d3008 	ldr	r3, [sp, #8]
30010c48:	e5d33000 	ldrb	r3, [r3]
30010c4c:	e58d3000 	str	r3, [sp]
30010c50:	e59d3000 	ldr	r3, [sp]
30010c54:	e3530073 	cmp	r3, #115	; 0x73
30010c58:	0a000024 	beq	30010cf0 <vsprintfk+0x11c>
30010c5c:	e59d3000 	ldr	r3, [sp]
30010c60:	e3530078 	cmp	r3, #120	; 0x78
30010c64:	0a000003 	beq	30010c78 <vsprintfk+0xa4>
30010c68:	e59d3000 	ldr	r3, [sp]
30010c6c:	e3530064 	cmp	r3, #100	; 0x64
30010c70:	0a00000f 	beq	30010cb4 <vsprintfk+0xe0>
30010c74:	ea00002a 	b	30010d24 <vsprintfk+0x150>
30010c78:	e59d2010 	ldr	r2, [sp, #16]
30010c7c:	e2823004 	add	r3, r2, #4	; 0x4
30010c80:	e58d3010 	str	r3, [sp, #16]
30010c84:	e1a03002 	mov	r3, r2
30010c88:	e5933000 	ldr	r3, [r3]
30010c8c:	e59d0014 	ldr	r0, [sp, #20]
30010c90:	e1a01003 	mov	r1, r3
30010c94:	e3a02010 	mov	r2, #16	; 0x10
30010c98:	eb00002b 	bl	30010d4c <numberk>
30010c9c:	e1a03000 	mov	r3, r0
30010ca0:	e58d3014 	str	r3, [sp, #20]
30010ca4:	e59d3008 	ldr	r3, [sp, #8]
30010ca8:	e2833001 	add	r3, r3, #1	; 0x1
30010cac:	e58d3008 	str	r3, [sp, #8]
30010cb0:	ea00001b 	b	30010d24 <vsprintfk+0x150>
30010cb4:	e59d2010 	ldr	r2, [sp, #16]
30010cb8:	e2823004 	add	r3, r2, #4	; 0x4
30010cbc:	e58d3010 	str	r3, [sp, #16]
30010cc0:	e1a03002 	mov	r3, r2
30010cc4:	e5933000 	ldr	r3, [r3]
30010cc8:	e59d0014 	ldr	r0, [sp, #20]
30010ccc:	e1a01003 	mov	r1, r3
30010cd0:	e3a0200a 	mov	r2, #10	; 0xa
30010cd4:	eb00001c 	bl	30010d4c <numberk>
30010cd8:	e1a03000 	mov	r3, r0
30010cdc:	e58d3014 	str	r3, [sp, #20]
30010ce0:	e59d3008 	ldr	r3, [sp, #8]
30010ce4:	e2833001 	add	r3, r3, #1	; 0x1
30010ce8:	e58d3008 	str	r3, [sp, #8]
30010cec:	ea00000c 	b	30010d24 <vsprintfk+0x150>
30010cf0:	e59d2010 	ldr	r2, [sp, #16]
30010cf4:	e2823004 	add	r3, r2, #4	; 0x4
30010cf8:	e58d3010 	str	r3, [sp, #16]
30010cfc:	e1a03002 	mov	r3, r2
30010d00:	e5933000 	ldr	r3, [r3]
30010d04:	e59d0014 	ldr	r0, [sp, #20]
30010d08:	e1a01003 	mov	r1, r3
30010d0c:	ebffff9a 	bl	30010b7c <strcopyk>
30010d10:	e1a03000 	mov	r3, r0
30010d14:	e58d3014 	str	r3, [sp, #20]
30010d18:	e59d3008 	ldr	r3, [sp, #8]
30010d1c:	e2833001 	add	r3, r3, #1	; 0x1
30010d20:	e58d3008 	str	r3, [sp, #8]
30010d24:	e59d3008 	ldr	r3, [sp, #8]
30010d28:	e5d33000 	ldrb	r3, [r3]
30010d2c:	e3530000 	cmp	r3, #0	; 0x0
30010d30:	1affffb1 	bne	30010bfc <vsprintfk+0x28>
30010d34:	e59d3014 	ldr	r3, [sp, #20]
30010d38:	e3a02000 	mov	r2, #0	; 0x0
30010d3c:	e5c32000 	strb	r2, [r3]
30010d40:	e28dd01c 	add	sp, sp, #28	; 0x1c
30010d44:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
30010d48:	e12fff1e 	bx	lr

30010d4c <numberk>:
30010d4c:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
30010d50:	e24dd03c 	sub	sp, sp, #60	; 0x3c
30010d54:	e58d000c 	str	r0, [sp, #12]
30010d58:	e58d1008 	str	r1, [sp, #8]
30010d5c:	e58d2004 	str	r2, [sp, #4]
30010d60:	e28d2014 	add	r2, sp, #20	; 0x14
30010d64:	e58d2000 	str	r2, [sp]
30010d68:	e59d3000 	ldr	r3, [sp]
30010d6c:	e2833024 	add	r3, r3, #36	; 0x24
30010d70:	e58d3000 	str	r3, [sp]
30010d74:	e59d2000 	ldr	r2, [sp]
30010d78:	e2422001 	sub	r2, r2, #1	; 0x1
30010d7c:	e58d2000 	str	r2, [sp]
30010d80:	e3a03000 	mov	r3, #0	; 0x0
30010d84:	e59d2000 	ldr	r2, [sp]
30010d88:	e5c23000 	strb	r3, [r2]
30010d8c:	e59d3008 	ldr	r3, [sp, #8]
30010d90:	e3530000 	cmp	r3, #0	; 0x0
30010d94:	1a000006 	bne	30010db4 <numberk+0x68>
30010d98:	e59d3000 	ldr	r3, [sp]
30010d9c:	e2433001 	sub	r3, r3, #1	; 0x1
30010da0:	e58d3000 	str	r3, [sp]
30010da4:	e3a03030 	mov	r3, #48	; 0x30
30010da8:	e59d2000 	ldr	r2, [sp]
30010dac:	e5c23000 	strb	r3, [r2]
30010db0:	ea000022 	b	30010e40 <numberk+0xf4>
30010db4:	e59d3000 	ldr	r3, [sp]
30010db8:	e2433001 	sub	r3, r3, #1	; 0x1
30010dbc:	e58d3000 	str	r3, [sp]
30010dc0:	e59d2004 	ldr	r2, [sp, #4]
30010dc4:	e59d3008 	ldr	r3, [sp, #8]
30010dc8:	e1a00003 	mov	r0, r3
30010dcc:	e1a01002 	mov	r1, r2
30010dd0:	eb0002cd 	bl	3001190c <__aeabi_uidivmod>
30010dd4:	e1a03001 	mov	r3, r1
30010dd8:	e1a02003 	mov	r2, r3
30010ddc:	e59f3080 	ldr	r3, [pc, #128]	; 30010e64 <numberk+0x118>
30010de0:	e7d33002 	ldrb	r3, [r3, r2]
30010de4:	e59d2000 	ldr	r2, [sp]
30010de8:	e5c23000 	strb	r3, [r2]
30010dec:	e59d2004 	ldr	r2, [sp, #4]
30010df0:	e59d3008 	ldr	r3, [sp, #8]
30010df4:	e1a00003 	mov	r0, r3
30010df8:	e1a01002 	mov	r1, r2
30010dfc:	eb000247 	bl	30011720 <__aeabi_uidiv>
30010e00:	e1a03000 	mov	r3, r0
30010e04:	e58d3008 	str	r3, [sp, #8]
30010e08:	e59d3008 	ldr	r3, [sp, #8]
30010e0c:	e3530000 	cmp	r3, #0	; 0x0
30010e10:	1affffe7 	bne	30010db4 <numberk+0x68>
30010e14:	ea000009 	b	30010e40 <numberk+0xf4>
30010e18:	e59d2000 	ldr	r2, [sp]
30010e1c:	e5d23000 	ldrb	r3, [r2]
30010e20:	e59d200c 	ldr	r2, [sp, #12]
30010e24:	e5c23000 	strb	r3, [r2]
30010e28:	e59d300c 	ldr	r3, [sp, #12]
30010e2c:	e2833001 	add	r3, r3, #1	; 0x1
30010e30:	e58d300c 	str	r3, [sp, #12]
30010e34:	e59d3000 	ldr	r3, [sp]
30010e38:	e2833001 	add	r3, r3, #1	; 0x1
30010e3c:	e58d3000 	str	r3, [sp]
30010e40:	e59d2000 	ldr	r2, [sp]
30010e44:	e5d23000 	ldrb	r3, [r2]
30010e48:	e3530000 	cmp	r3, #0	; 0x0
30010e4c:	1afffff1 	bne	30010e18 <numberk+0xcc>
30010e50:	e59d300c 	ldr	r3, [sp, #12]
30010e54:	e1a00003 	mov	r0, r3
30010e58:	e28dd03c 	add	sp, sp, #60	; 0x3c
30010e5c:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
30010e60:	e12fff1e 	bx	lr
30010e64:	30012a74 	.word	0x30012a74

30010e68 <char_write_uart>:
30010e68:	e24dd010 	sub	sp, sp, #16	; 0x10
30010e6c:	e58d0004 	str	r0, [sp, #4]
30010e70:	e59d3004 	ldr	r3, [sp, #4]
30010e74:	e58d300c 	str	r3, [sp, #12]
30010e78:	ea000002 	b	30010e88 <char_write_uart+0x20>
30010e7c:	e59d300c 	ldr	r3, [sp, #12]
30010e80:	e2833001 	add	r3, r3, #1	; 0x1
30010e84:	e58d300c 	str	r3, [sp, #12]
30010e88:	e59d300c 	ldr	r3, [sp, #12]
30010e8c:	e5d33000 	ldrb	r3, [r3]
30010e90:	e3530000 	cmp	r3, #0	; 0x0
30010e94:	1afffff8 	bne	30010e7c <char_write_uart+0x14>
30010e98:	e28dd010 	add	sp, sp, #16	; 0x10
30010e9c:	e12fff1e 	bx	lr

30010ea0 <hal_disable_fiq>:
30010ea0:	e10f0000 	mrs	r0, CPSR
30010ea4:	e3800040 	orr	r0, r0, #64	; 0x40
30010ea8:	e129f000 	msr	CPSR_fc, r0
30010eac:	e12fff1e 	bx	lr

30010eb0 <hal_enable_fiq>:
30010eb0:	e10f0000 	mrs	r0, CPSR
30010eb4:	e3c00040 	bic	r0, r0, #64	; 0x40
30010eb8:	e129f000 	msr	CPSR_fc, r0
30010ebc:	e12fff1e 	bx	lr

30010ec0 <hal_disable_irq>:
30010ec0:	e10f0000 	mrs	r0, CPSR
30010ec4:	e3800080 	orr	r0, r0, #128	; 0x80
30010ec8:	e129f000 	msr	CPSR_fc, r0
30010ecc:	e12fff1e 	bx	lr

30010ed0 <hal_enable_irq>:
30010ed0:	e10f0000 	mrs	r0, CPSR
30010ed4:	e3c00080 	bic	r0, r0, #128	; 0x80
30010ed8:	e129f000 	msr	CPSR_fc, r0
30010edc:	e12fff1e 	bx	lr

30010ee0 <hal_disable_irqfiq>:
30010ee0:	e10f0000 	mrs	r0, CPSR
30010ee4:	e38000c0 	orr	r0, r0, #192	; 0xc0
30010ee8:	e129f000 	msr	CPSR_fc, r0
30010eec:	e12fff1e 	bx	lr

30010ef0 <hal_enable_irqfiq>:
30010ef0:	e10f0000 	mrs	r0, CPSR
30010ef4:	e3c000c0 	bic	r0, r0, #192	; 0xc0
30010ef8:	e129f000 	msr	CPSR_fc, r0
30010efc:	e12fff1e 	bx	lr

30010f00 <hal_disablefiq_savecpuflg>:
30010f00:	e52d7004 	push	{r7}		; (str r7, [sp, #-4]!)
30010f04:	e24dd014 	sub	sp, sp, #20	; 0x14
30010f08:	e58d0004 	str	r0, [sp, #4]
30010f0c:	e10f7000 	mrs	r7, CPSR
30010f10:	e1a03007 	mov	r3, r7
30010f14:	e3877040 	orr	r7, r7, #64	; 0x40
30010f18:	e129f007 	msr	CPSR_fc, r7
30010f1c:	e58d300c 	str	r3, [sp, #12]
30010f20:	e59d2004 	ldr	r2, [sp, #4]
30010f24:	e59d300c 	ldr	r3, [sp, #12]
30010f28:	e5823000 	str	r3, [r2]
30010f2c:	e28dd014 	add	sp, sp, #20	; 0x14
30010f30:	e8bd0080 	pop	{r7}
30010f34:	e12fff1e 	bx	lr

30010f38 <hal_enablefiq_restcpuflg>:
30010f38:	e24dd008 	sub	sp, sp, #8	; 0x8
30010f3c:	e58d0004 	str	r0, [sp, #4]
30010f40:	e59d3004 	ldr	r3, [sp, #4]
30010f44:	e5933000 	ldr	r3, [r3]
30010f48:	e129f003 	msr	CPSR_fc, r3
30010f4c:	e28dd008 	add	sp, sp, #8	; 0x8
30010f50:	e12fff1e 	bx	lr

30010f54 <hal_disableirq_savecpuflg>:
30010f54:	e52d7004 	push	{r7}		; (str r7, [sp, #-4]!)
30010f58:	e24dd014 	sub	sp, sp, #20	; 0x14
30010f5c:	e58d0004 	str	r0, [sp, #4]
30010f60:	e10f7000 	mrs	r7, CPSR
30010f64:	e1a03007 	mov	r3, r7
30010f68:	e3877080 	orr	r7, r7, #128	; 0x80
30010f6c:	e129f007 	msr	CPSR_fc, r7
30010f70:	e58d300c 	str	r3, [sp, #12]
30010f74:	e59d2004 	ldr	r2, [sp, #4]
30010f78:	e59d300c 	ldr	r3, [sp, #12]
30010f7c:	e5823000 	str	r3, [r2]
30010f80:	e28dd014 	add	sp, sp, #20	; 0x14
30010f84:	e8bd0080 	pop	{r7}
30010f88:	e12fff1e 	bx	lr

30010f8c <hal_enableirq_restcpuflg>:
30010f8c:	e24dd008 	sub	sp, sp, #8	; 0x8
30010f90:	e58d0004 	str	r0, [sp, #4]
30010f94:	e59d3004 	ldr	r3, [sp, #4]
30010f98:	e5933000 	ldr	r3, [r3]
30010f9c:	e129f003 	msr	CPSR_fc, r3
30010fa0:	e28dd008 	add	sp, sp, #8	; 0x8
30010fa4:	e12fff1e 	bx	lr

30010fa8 <hal_disableirqfiq_savecpuflg>:
30010fa8:	e24dd010 	sub	sp, sp, #16	; 0x10
30010fac:	e58d0004 	str	r0, [sp, #4]
30010fb0:	e10f7000 	mrs	r7, CPSR
30010fb4:	e1a03007 	mov	r3, r7
30010fb8:	e38770c0 	orr	r7, r7, #192	; 0xc0
30010fbc:	e58d300c 	str	r3, [sp, #12]
30010fc0:	e59d2004 	ldr	r2, [sp, #4]
30010fc4:	e59d300c 	ldr	r3, [sp, #12]
30010fc8:	e5823000 	str	r3, [r2]
30010fcc:	e28dd010 	add	sp, sp, #16	; 0x10
30010fd0:	e12fff1e 	bx	lr

30010fd4 <hal_enableirqfiq_restcpuflg>:
30010fd4:	e24dd008 	sub	sp, sp, #8	; 0x8
30010fd8:	e58d0004 	str	r0, [sp, #4]
30010fdc:	e59d3004 	ldr	r3, [sp, #4]
30010fe0:	e5933000 	ldr	r3, [r3]
30010fe4:	e129f003 	msr	CPSR_fc, r3
30010fe8:	e28dd008 	add	sp, sp, #8	; 0x8
30010fec:	e12fff1e 	bx	lr

30010ff0 <hal_read_currmodesp>:
30010ff0:	e24dd008 	sub	sp, sp, #8	; 0x8
30010ff4:	e3a03000 	mov	r3, #0	; 0x0
30010ff8:	e58d3004 	str	r3, [sp, #4]
30010ffc:	e1a0300d 	mov	r3, sp
30011000:	e58d3004 	str	r3, [sp, #4]
30011004:	e59d3004 	ldr	r3, [sp, #4]
30011008:	e1a00003 	mov	r0, r3
3001100c:	e28dd008 	add	sp, sp, #8	; 0x8
30011010:	e12fff1e 	bx	lr

30011014 <hal_read_cpuflg>:
30011014:	e24dd008 	sub	sp, sp, #8	; 0x8
30011018:	e10f3000 	mrs	r3, CPSR
3001101c:	e58d3004 	str	r3, [sp, #4]
30011020:	e59d3004 	ldr	r3, [sp, #4]
30011024:	e1a00003 	mov	r0, r3
30011028:	e28dd008 	add	sp, sp, #8	; 0x8
3001102c:	e12fff1e 	bx	lr

30011030 <hal_write_cpuflg>:
30011030:	e24dd008 	sub	sp, sp, #8	; 0x8
30011034:	e58d0004 	str	r0, [sp, #4]
30011038:	e59d3004 	ldr	r3, [sp, #4]
3001103c:	e129f003 	msr	CPSR_fc, r3
30011040:	e28dd008 	add	sp, sp, #8	; 0x8
30011044:	e12fff1e 	bx	lr

30011048 <hal_swhmodset_sp_rscurmod>:
30011048:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
3001104c:	e24dd014 	sub	sp, sp, #20	; 0x14
30011050:	e58d0004 	str	r0, [sp, #4]
30011054:	e58d1000 	str	r1, [sp]
30011058:	ebffffed 	bl	30011014 <hal_read_cpuflg>
3001105c:	e1a03000 	mov	r3, r0
30011060:	e58d300c 	str	r3, [sp, #12]
30011064:	e59d300c 	ldr	r3, [sp, #12]
30011068:	e58d3008 	str	r3, [sp, #8]
3001106c:	e59d300c 	ldr	r3, [sp, #12]
30011070:	e3c3301f 	bic	r3, r3, #31	; 0x1f
30011074:	e58d300c 	str	r3, [sp, #12]
30011078:	e59d200c 	ldr	r2, [sp, #12]
3001107c:	e59d3004 	ldr	r3, [sp, #4]
30011080:	e1823003 	orr	r3, r2, r3
30011084:	e58d300c 	str	r3, [sp, #12]
30011088:	e59d100c 	ldr	r1, [sp, #12]
3001108c:	e59d2000 	ldr	r2, [sp]
30011090:	e59d3008 	ldr	r3, [sp, #8]
30011094:	e121f001 	msr	CPSR_c, r1
30011098:	e1a0d002 	mov	sp, r2
3001109c:	e129f003 	msr	CPSR_fc, r3
300110a0:	e28dd014 	add	sp, sp, #20	; 0x14
300110a4:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
300110a8:	e12fff1e 	bx	lr

300110ac <hal_read_scpuflg>:
300110ac:	e24dd008 	sub	sp, sp, #8	; 0x8
300110b0:	e14f3000 	mrs	r3, SPSR
300110b4:	e58d3004 	str	r3, [sp, #4]
300110b8:	e59d3004 	ldr	r3, [sp, #4]
300110bc:	e1a00003 	mov	r0, r3
300110c0:	e28dd008 	add	sp, sp, #8	; 0x8
300110c4:	e12fff1e 	bx	lr

300110c8 <hal_write_scpuflg>:
300110c8:	e24dd008 	sub	sp, sp, #8	; 0x8
300110cc:	e58d0004 	str	r0, [sp, #4]
300110d0:	e59d3004 	ldr	r3, [sp, #4]
300110d4:	e129f003 	msr	CPSR_fc, r3
300110d8:	e28dd008 	add	sp, sp, #8	; 0x8
300110dc:	e12fff1e 	bx	lr

300110e0 <hal_cpumode_switch>:
300110e0:	e52d7004 	push	{r7}		; (str r7, [sp, #-4]!)
300110e4:	e24dd00c 	sub	sp, sp, #12	; 0xc
300110e8:	e58d0004 	str	r0, [sp, #4]
300110ec:	e59d3004 	ldr	r3, [sp, #4]
300110f0:	e10f7000 	mrs	r7, CPSR
300110f4:	e1877003 	orr	r7, r7, r3
300110f8:	e129f007 	msr	CPSR_fc, r7
300110fc:	e28dd00c 	add	sp, sp, #12	; 0xc
30011100:	e8bd0080 	pop	{r7}
30011104:	e12fff1e 	bx	lr

30011108 <hal_cpumodeswitch_retoldmode>:
30011108:	e52d7004 	push	{r7}		; (str r7, [sp, #-4]!)
3001110c:	e24dd014 	sub	sp, sp, #20	; 0x14
30011110:	e58d0004 	str	r0, [sp, #4]
30011114:	e59d3004 	ldr	r3, [sp, #4]
30011118:	e10f7000 	mrs	r7, CPSR
3001111c:	e1a03007 	mov	r3, r7
30011120:	e1877003 	orr	r7, r7, r3
30011124:	e129f007 	msr	CPSR_fc, r7
30011128:	e58d300c 	str	r3, [sp, #12]
3001112c:	e59d300c 	ldr	r3, [sp, #12]
30011130:	e1a00003 	mov	r0, r3
30011134:	e28dd014 	add	sp, sp, #20	; 0x14
30011138:	e8bd0080 	pop	{r7}
3001113c:	e12fff1e 	bx	lr

30011140 <hal_io8_read>:
30011140:	e24dd010 	sub	sp, sp, #16	; 0x10
30011144:	e58d0004 	str	r0, [sp, #4]
30011148:	e59d3004 	ldr	r3, [sp, #4]
3001114c:	e5d33000 	ldrb	r3, [r3]
30011150:	e5cd300f 	strb	r3, [sp, #15]
30011154:	e5dd300f 	ldrb	r3, [sp, #15]
30011158:	e1a00003 	mov	r0, r3
3001115c:	e28dd010 	add	sp, sp, #16	; 0x10
30011160:	e12fff1e 	bx	lr

30011164 <hal_io16_read>:
30011164:	e24dd010 	sub	sp, sp, #16	; 0x10
30011168:	e58d0004 	str	r0, [sp, #4]
3001116c:	e59d3004 	ldr	r3, [sp, #4]
30011170:	e1d330b0 	ldrh	r3, [r3]
30011174:	e1cd30be 	strh	r3, [sp, #14]
30011178:	e1dd30be 	ldrh	r3, [sp, #14]
3001117c:	e1a00003 	mov	r0, r3
30011180:	e28dd010 	add	sp, sp, #16	; 0x10
30011184:	e12fff1e 	bx	lr

30011188 <hal_io32_read>:
30011188:	e24dd010 	sub	sp, sp, #16	; 0x10
3001118c:	e58d0004 	str	r0, [sp, #4]
30011190:	e59d3004 	ldr	r3, [sp, #4]
30011194:	e5933000 	ldr	r3, [r3]
30011198:	e58d300c 	str	r3, [sp, #12]
3001119c:	e59d300c 	ldr	r3, [sp, #12]
300111a0:	e1a00003 	mov	r0, r3
300111a4:	e28dd010 	add	sp, sp, #16	; 0x10
300111a8:	e12fff1e 	bx	lr

300111ac <hal_io8_write>:
300111ac:	e24dd008 	sub	sp, sp, #8	; 0x8
300111b0:	e58d0004 	str	r0, [sp, #4]
300111b4:	e1a03001 	mov	r3, r1
300111b8:	e5cd3003 	strb	r3, [sp, #3]
300111bc:	e5dd2003 	ldrb	r2, [sp, #3]
300111c0:	e59d3004 	ldr	r3, [sp, #4]
300111c4:	e5c32000 	strb	r2, [r3]
300111c8:	e28dd008 	add	sp, sp, #8	; 0x8
300111cc:	e12fff1e 	bx	lr

300111d0 <hal_io16_write>:
300111d0:	e24dd008 	sub	sp, sp, #8	; 0x8
300111d4:	e58d0004 	str	r0, [sp, #4]
300111d8:	e1a03001 	mov	r3, r1
300111dc:	e1cd30b2 	strh	r3, [sp, #2]
300111e0:	e1dd20b2 	ldrh	r2, [sp, #2]
300111e4:	e59d3004 	ldr	r3, [sp, #4]
300111e8:	e1c320b0 	strh	r2, [r3]
300111ec:	e28dd008 	add	sp, sp, #8	; 0x8
300111f0:	e12fff1e 	bx	lr

300111f4 <hal_io32_write>:
300111f4:	e24dd008 	sub	sp, sp, #8	; 0x8
300111f8:	e58d0004 	str	r0, [sp, #4]
300111fc:	e58d1000 	str	r1, [sp]
30011200:	e59d2000 	ldr	r2, [sp]
30011204:	e59d3004 	ldr	r3, [sp, #4]
30011208:	e5832000 	str	r2, [r3]
3001120c:	e28dd008 	add	sp, sp, #8	; 0x8
30011210:	e12fff1e 	bx	lr

30011214 <hal_spinlock_init>:
30011214:	e24dd008 	sub	sp, sp, #8	; 0x8
30011218:	e58d0004 	str	r0, [sp, #4]
3001121c:	e59d2004 	ldr	r2, [sp, #4]
30011220:	e3a03000 	mov	r3, #0	; 0x0
30011224:	e1023093 	swp	r3, r3, [r2]
30011228:	e28dd008 	add	sp, sp, #8	; 0x8
3001122c:	e12fff1e 	bx	lr

30011230 <hal_spinlock_lock>:
30011230:	e92d0180 	push	{r7, r8}
30011234:	e24dd008 	sub	sp, sp, #8	; 0x8
30011238:	e58d0004 	str	r0, [sp, #4]
3001123c:	e59d3004 	ldr	r3, [sp, #4]
30011240:	e3a08001 	mov	r8, #1	; 0x1
30011244:	e1037098 	swp	r7, r8, [r3]
30011248:	e3570000 	cmp	r7, #0	; 0x0
3001124c:	1afffffc 	bne	30011244 <hal_spinlock_lock+0x14>
30011250:	e28dd008 	add	sp, sp, #8	; 0x8
30011254:	e8bd0180 	pop	{r7, r8}
30011258:	e12fff1e 	bx	lr

3001125c <hal_spinlock_unlock>:
3001125c:	e24dd008 	sub	sp, sp, #8	; 0x8
30011260:	e58d0004 	str	r0, [sp, #4]
30011264:	e59d2004 	ldr	r2, [sp, #4]
30011268:	e3a03000 	mov	r3, #0	; 0x0
3001126c:	e1023093 	swp	r3, r3, [r2]
30011270:	e28dd008 	add	sp, sp, #8	; 0x8
30011274:	e12fff1e 	bx	lr

30011278 <hal_spinlock_saveflg_cli>:
30011278:	e92d0180 	push	{r7, r8}
3001127c:	e24dd010 	sub	sp, sp, #16	; 0x10
30011280:	e58d0004 	str	r0, [sp, #4]
30011284:	e58d1000 	str	r1, [sp]
30011288:	e10f7000 	mrs	r7, CPSR
3001128c:	e1a03007 	mov	r3, r7
30011290:	e38770c0 	orr	r7, r7, #192	; 0xc0
30011294:	e129f007 	msr	CPSR_fc, r7
30011298:	e58d300c 	str	r3, [sp, #12]
3001129c:	e59d2000 	ldr	r2, [sp]
300112a0:	e59d300c 	ldr	r3, [sp, #12]
300112a4:	e5823000 	str	r3, [r2]
300112a8:	e59d3004 	ldr	r3, [sp, #4]
300112ac:	e3a08001 	mov	r8, #1	; 0x1
300112b0:	e1037098 	swp	r7, r8, [r3]
300112b4:	e3570000 	cmp	r7, #0	; 0x0
300112b8:	1afffffc 	bne	300112b0 <hal_spinlock_saveflg_cli+0x38>
300112bc:	e28dd010 	add	sp, sp, #16	; 0x10
300112c0:	e8bd0180 	pop	{r7, r8}
300112c4:	e12fff1e 	bx	lr

300112c8 <hal_spinunlock_restflg_sti>:
300112c8:	e24dd008 	sub	sp, sp, #8	; 0x8
300112cc:	e58d0004 	str	r0, [sp, #4]
300112d0:	e58d1000 	str	r1, [sp]
300112d4:	e59d2004 	ldr	r2, [sp, #4]
300112d8:	e3a03000 	mov	r3, #0	; 0x0
300112dc:	e1023093 	swp	r3, r3, [r2]
300112e0:	e59d3000 	ldr	r3, [sp]
300112e4:	e5933000 	ldr	r3, [r3]
300112e8:	e129f003 	msr	CPSR_fc, r3
300112ec:	e28dd008 	add	sp, sp, #8	; 0x8
300112f0:	e12fff1e 	bx	lr

300112f4 <hal_memset>:
300112f4:	e24dd018 	sub	sp, sp, #24	; 0x18
300112f8:	e58d000c 	str	r0, [sp, #12]
300112fc:	e58d1008 	str	r1, [sp, #8]
30011300:	e1a03002 	mov	r3, r2
30011304:	e5cd3007 	strb	r3, [sp, #7]
30011308:	e59d300c 	ldr	r3, [sp, #12]
3001130c:	e58d3010 	str	r3, [sp, #16]
30011310:	e3a03000 	mov	r3, #0	; 0x0
30011314:	e58d3014 	str	r3, [sp, #20]
30011318:	ea000007 	b	3001133c <hal_memset+0x48>
3001131c:	e59d2010 	ldr	r2, [sp, #16]
30011320:	e59d3014 	ldr	r3, [sp, #20]
30011324:	e0822003 	add	r2, r2, r3
30011328:	e5dd3007 	ldrb	r3, [sp, #7]
3001132c:	e5c23000 	strb	r3, [r2]
30011330:	e59d3014 	ldr	r3, [sp, #20]
30011334:	e2833001 	add	r3, r3, #1	; 0x1
30011338:	e58d3014 	str	r3, [sp, #20]
3001133c:	e59d2014 	ldr	r2, [sp, #20]
30011340:	e59d3008 	ldr	r3, [sp, #8]
30011344:	e1520003 	cmp	r2, r3
30011348:	3afffff3 	bcc	3001131c <hal_memset+0x28>
3001134c:	e28dd018 	add	sp, sp, #24	; 0x18
30011350:	e12fff1e 	bx	lr

30011354 <hal_memcpy>:
30011354:	e24dd020 	sub	sp, sp, #32	; 0x20
30011358:	e58d000c 	str	r0, [sp, #12]
3001135c:	e58d1008 	str	r1, [sp, #8]
30011360:	e58d2004 	str	r2, [sp, #4]
30011364:	e59d300c 	ldr	r3, [sp, #12]
30011368:	e58d3014 	str	r3, [sp, #20]
3001136c:	e59d3008 	ldr	r3, [sp, #8]
30011370:	e58d3018 	str	r3, [sp, #24]
30011374:	e3a03000 	mov	r3, #0	; 0x0
30011378:	e58d301c 	str	r3, [sp, #28]
3001137c:	ea00000a 	b	300113ac <hal_memcpy+0x58>
30011380:	e59d2018 	ldr	r2, [sp, #24]
30011384:	e59d301c 	ldr	r3, [sp, #28]
30011388:	e0821003 	add	r1, r2, r3
3001138c:	e59d2014 	ldr	r2, [sp, #20]
30011390:	e59d301c 	ldr	r3, [sp, #28]
30011394:	e0823003 	add	r3, r2, r3
30011398:	e5d33000 	ldrb	r3, [r3]
3001139c:	e5c13000 	strb	r3, [r1]
300113a0:	e59d301c 	ldr	r3, [sp, #28]
300113a4:	e2833001 	add	r3, r3, #1	; 0x1
300113a8:	e58d301c 	str	r3, [sp, #28]
300113ac:	e59d201c 	ldr	r2, [sp, #28]
300113b0:	e59d3004 	ldr	r3, [sp, #4]
300113b4:	e1520003 	cmp	r2, r3
300113b8:	3afffff0 	bcc	30011380 <hal_memcpy+0x2c>
300113bc:	e28dd020 	add	sp, sp, #32	; 0x20
300113c0:	e12fff1e 	bx	lr

300113c4 <hal_sysdie>:
300113c4:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
300113c8:	e24dd00c 	sub	sp, sp, #12	; 0xc
300113cc:	e58d0004 	str	r0, [sp, #4]
300113d0:	eb000040 	bl	300114d8 <init_uart0>
300113d4:	e59f0010 	ldr	r0, [pc, #16]	; 300113ec <hal_sysdie+0x28>
300113d8:	e59d1004 	ldr	r1, [sp, #4]
300113dc:	ebfffdcd 	bl	30010b18 <printfk>
300113e0:	e28dd00c 	add	sp, sp, #12	; 0xc
300113e4:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
300113e8:	e12fff1e 	bx	lr
300113ec:	30012a88 	.word	0x30012a88

300113f0 <hal_retn_cpuid>:
300113f0:	e3a03000 	mov	r3, #0	; 0x0
300113f4:	e1a00003 	mov	r0, r3
300113f8:	e12fff1e 	bx	lr

300113fc <hal_disable_cache>:
300113fc:	e3a03a01 	mov	r3, #4096	; 0x1000
30011400:	e2833004 	add	r3, r3, #4	; 0x4
30011404:	ee010f10 	mcr	15, 0, r0, cr1, cr0, {0}
30011408:	e1800003 	orr	r0, r0, r3
3001140c:	ee010f10 	mcr	15, 0, r0, cr1, cr0, {0}
30011410:	e12fff1e 	bx	lr

30011414 <cp15_read_c5>:
30011414:	e24dd008 	sub	sp, sp, #8	; 0x8
30011418:	ee053f10 	mcr	15, 0, r3, cr5, cr0, {0}
3001141c:	e58d3004 	str	r3, [sp, #4]
30011420:	e59d3004 	ldr	r3, [sp, #4]
30011424:	e1a00003 	mov	r0, r3
30011428:	e28dd008 	add	sp, sp, #8	; 0x8
3001142c:	e12fff1e 	bx	lr

30011430 <cp15_read_c6>:
30011430:	e24dd008 	sub	sp, sp, #8	; 0x8
30011434:	ee063f10 	mcr	15, 0, r3, cr6, cr0, {0}
30011438:	e58d3004 	str	r3, [sp, #4]
3001143c:	e59d3004 	ldr	r3, [sp, #4]
30011440:	e1a00003 	mov	r0, r3
30011444:	e28dd008 	add	sp, sp, #8	; 0x8
30011448:	e12fff1e 	bx	lr

3001144c <hal_read_cp15regs>:
3001144c:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
30011450:	e24dd014 	sub	sp, sp, #20	; 0x14
30011454:	e58d000c 	str	r0, [sp, #12]
30011458:	e59d300c 	ldr	r3, [sp, #12]
3001145c:	e58d3004 	str	r3, [sp, #4]
30011460:	e59d3004 	ldr	r3, [sp, #4]
30011464:	e3530005 	cmp	r3, #5	; 0x5
30011468:	0a000003 	beq	3001147c <hal_read_cp15regs+0x30>
3001146c:	e59d3004 	ldr	r3, [sp, #4]
30011470:	e3530006 	cmp	r3, #6	; 0x6
30011474:	0a000004 	beq	3001148c <hal_read_cp15regs+0x40>
30011478:	ea000007 	b	3001149c <hal_read_cp15regs+0x50>
3001147c:	ebffffe4 	bl	30011414 <cp15_read_c5>
30011480:	e1a03000 	mov	r3, r0
30011484:	e58d3008 	str	r3, [sp, #8]
30011488:	ea000005 	b	300114a4 <hal_read_cp15regs+0x58>
3001148c:	ebffffe7 	bl	30011430 <cp15_read_c6>
30011490:	e1a03000 	mov	r3, r0
30011494:	e58d3008 	str	r3, [sp, #8]
30011498:	ea000001 	b	300114a4 <hal_read_cp15regs+0x58>
3001149c:	e3a03000 	mov	r3, #0	; 0x0
300114a0:	e58d3008 	str	r3, [sp, #8]
300114a4:	e59d3008 	ldr	r3, [sp, #8]
300114a8:	e1a00003 	mov	r0, r3
300114ac:	e28dd014 	add	sp, sp, #20	; 0x14
300114b0:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
300114b4:	e12fff1e 	bx	lr

300114b8 <init_haluart>:
300114b8:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
300114bc:	e24dd00c 	sub	sp, sp, #12	; 0xc
300114c0:	e3a03061 	mov	r3, #97	; 0x61
300114c4:	e5cd3007 	strb	r3, [sp, #7]
300114c8:	e5dd3007 	ldrb	r3, [sp, #7]
300114cc:	e1a00003 	mov	r0, r3
300114d0:	eb000013 	bl	30011524 <hal_uart0_putc>
300114d4:	eafffffe 	b	300114d4 <init_haluart+0x1c>

300114d8 <init_uart0>:
300114d8:	e92d4010 	push	{r4, lr}
300114dc:	e3a00205 	mov	r0, #1342177280	; 0x50000000
300114e0:	e3a01003 	mov	r1, #3	; 0x3
300114e4:	ebffff42 	bl	300111f4 <hal_io32_write>
300114e8:	e3a00245 	mov	r0, #1342177284	; 0x50000004
300114ec:	e3a01005 	mov	r1, #5	; 0x5
300114f0:	ebffff3f 	bl	300111f4 <hal_io32_write>
300114f4:	e3a00285 	mov	r0, #1342177288	; 0x50000008
300114f8:	e3a01000 	mov	r1, #0	; 0x0
300114fc:	ebffff3c 	bl	300111f4 <hal_io32_write>
30011500:	e3a002c5 	mov	r0, #1342177292	; 0x5000000c
30011504:	e3a01000 	mov	r1, #0	; 0x0
30011508:	ebffff39 	bl	300111f4 <hal_io32_write>
3001150c:	e3a00205 	mov	r0, #1342177280	; 0x50000000
30011510:	e2800028 	add	r0, r0, #40	; 0x28
30011514:	e3a0101a 	mov	r1, #26	; 0x1a
30011518:	ebffff35 	bl	300111f4 <hal_io32_write>
3001151c:	e8bd4010 	pop	{r4, lr}
30011520:	e12fff1e 	bx	lr

30011524 <hal_uart0_putc>:
30011524:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
30011528:	e24dd00c 	sub	sp, sp, #12	; 0xc
3001152c:	e1a03000 	mov	r3, r0
30011530:	e5cd3007 	strb	r3, [sp, #7]
30011534:	e3a00205 	mov	r0, #1342177280	; 0x50000000
30011538:	e2800901 	add	r0, r0, #16384	; 0x4000
3001153c:	e2800010 	add	r0, r0, #16	; 0x10
30011540:	ebffff10 	bl	30011188 <hal_io32_read>
30011544:	e1a03000 	mov	r3, r0
30011548:	e2033004 	and	r3, r3, #4	; 0x4
3001154c:	e3530000 	cmp	r3, #0	; 0x0
30011550:	0afffff7 	beq	30011534 <hal_uart0_putc+0x10>
30011554:	e5dd3007 	ldrb	r3, [sp, #7]
30011558:	e3a00205 	mov	r0, #1342177280	; 0x50000000
3001155c:	e2800901 	add	r0, r0, #16384	; 0x4000
30011560:	e2800024 	add	r0, r0, #36	; 0x24
30011564:	e1a01003 	mov	r1, r3
30011568:	ebffff21 	bl	300111f4 <hal_io32_write>
3001156c:	e28dd00c 	add	sp, sp, #12	; 0xc
30011570:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
30011574:	e12fff1e 	bx	lr

30011578 <hal_uart_write>:
30011578:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
3001157c:	e24dd01c 	sub	sp, sp, #28	; 0x1c
30011580:	e58d000c 	str	r0, [sp, #12]
30011584:	e58d1008 	str	r1, [sp, #8]
30011588:	e58d2004 	str	r2, [sp, #4]
3001158c:	e59d3008 	ldr	r3, [sp, #8]
30011590:	e58d3014 	str	r3, [sp, #20]
30011594:	e28d3010 	add	r3, sp, #16	; 0x10
30011598:	e1a00003 	mov	r0, r3
3001159c:	ebfffe6c 	bl	30010f54 <hal_disableirq_savecpuflg>
300115a0:	ea00000f 	b	300115e4 <hal_uart_write+0x6c>
300115a4:	e59d3014 	ldr	r3, [sp, #20]
300115a8:	e5d33000 	ldrb	r3, [r3]
300115ac:	e59d000c 	ldr	r0, [sp, #12]
300115b0:	e1a01003 	mov	r1, r3
300115b4:	eb000029 	bl	30011660 <uart_send_char>
300115b8:	e1a03000 	mov	r3, r0
300115bc:	e3730001 	cmn	r3, #1	; 0x1
300115c0:	1a000004 	bne	300115d8 <hal_uart_write+0x60>
300115c4:	e59f0050 	ldr	r0, [pc, #80]	; 3001161c <hal_uart_write+0xa4>
300115c8:	ebffff7d 	bl	300113c4 <hal_sysdie>
300115cc:	e3e03000 	mvn	r3, #0	; 0x0
300115d0:	e58d3000 	str	r3, [sp]
300115d4:	ea00000b 	b	30011608 <hal_uart_write+0x90>
300115d8:	e59d3014 	ldr	r3, [sp, #20]
300115dc:	e2833001 	add	r3, r3, #1	; 0x1
300115e0:	e58d3014 	str	r3, [sp, #20]
300115e4:	e59d3014 	ldr	r3, [sp, #20]
300115e8:	e5d33000 	ldrb	r3, [r3]
300115ec:	e3530000 	cmp	r3, #0	; 0x0
300115f0:	1affffeb 	bne	300115a4 <hal_uart_write+0x2c>
300115f4:	e28d3010 	add	r3, sp, #16	; 0x10
300115f8:	e1a00003 	mov	r0, r3
300115fc:	ebfffe62 	bl	30010f8c <hal_enableirq_restcpuflg>
30011600:	e3a03000 	mov	r3, #0	; 0x0
30011604:	e58d3000 	str	r3, [sp]
30011608:	e59d3000 	ldr	r3, [sp]
3001160c:	e1a00003 	mov	r0, r3
30011610:	e28dd01c 	add	sp, sp, #28	; 0x1c
30011614:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
30011618:	e12fff1e 	bx	lr
3001161c:	30012aa0 	.word	0x30012aa0

30011620 <hal_uart_read>:
30011620:	e24dd010 	sub	sp, sp, #16	; 0x10
30011624:	e58d000c 	str	r0, [sp, #12]
30011628:	e58d1008 	str	r1, [sp, #8]
3001162c:	e58d2004 	str	r2, [sp, #4]
30011630:	e3a03000 	mov	r3, #0	; 0x0
30011634:	e1a00003 	mov	r0, r3
30011638:	e28dd010 	add	sp, sp, #16	; 0x10
3001163c:	e12fff1e 	bx	lr

30011640 <hal_uart_ioctrl>:
30011640:	e24dd010 	sub	sp, sp, #16	; 0x10
30011644:	e58d000c 	str	r0, [sp, #12]
30011648:	e58d1008 	str	r1, [sp, #8]
3001164c:	e58d2004 	str	r2, [sp, #4]
30011650:	e3a03000 	mov	r3, #0	; 0x0
30011654:	e1a00003 	mov	r0, r3
30011658:	e28dd010 	add	sp, sp, #16	; 0x10
3001165c:	e12fff1e 	bx	lr

30011660 <uart_send_char>:
30011660:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
30011664:	e24dd01c 	sub	sp, sp, #28	; 0x1c
30011668:	e58d000c 	str	r0, [sp, #12]
3001166c:	e1a03001 	mov	r3, r1
30011670:	e5cd300b 	strb	r3, [sp, #11]
30011674:	e3a03000 	mov	r3, #0	; 0x0
30011678:	e58d3014 	str	r3, [sp, #20]
3001167c:	e59d300c 	ldr	r3, [sp, #12]
30011680:	e3530000 	cmp	r3, #0	; 0x0
30011684:	0a00000b 	beq	300116b8 <uart_send_char+0x58>
30011688:	e3e03000 	mvn	r3, #0	; 0x0
3001168c:	e58d3004 	str	r3, [sp, #4]
30011690:	ea000016 	b	300116f0 <uart_send_char+0x90>
30011694:	e59d3014 	ldr	r3, [sp, #20]
30011698:	e3530601 	cmp	r3, #1048576	; 0x100000
3001169c:	9a000002 	bls	300116ac <uart_send_char+0x4c>
300116a0:	e3e03000 	mvn	r3, #0	; 0x0
300116a4:	e58d3004 	str	r3, [sp, #4]
300116a8:	ea000010 	b	300116f0 <uart_send_char+0x90>
300116ac:	e59d3014 	ldr	r3, [sp, #20]
300116b0:	e2833001 	add	r3, r3, #1	; 0x1
300116b4:	e58d3014 	str	r3, [sp, #20]
300116b8:	e3a00205 	mov	r0, #1342177280	; 0x50000000
300116bc:	e2800010 	add	r0, r0, #16	; 0x10
300116c0:	ebfffeb0 	bl	30011188 <hal_io32_read>
300116c4:	e1a03000 	mov	r3, r0
300116c8:	e2033004 	and	r3, r3, #4	; 0x4
300116cc:	e3530000 	cmp	r3, #0	; 0x0
300116d0:	0affffef 	beq	30011694 <uart_send_char+0x34>
300116d4:	e5dd300b 	ldrb	r3, [sp, #11]
300116d8:	e3a00205 	mov	r0, #1342177280	; 0x50000000
300116dc:	e2800020 	add	r0, r0, #32	; 0x20
300116e0:	e1a01003 	mov	r1, r3
300116e4:	ebfffec2 	bl	300111f4 <hal_io32_write>
300116e8:	e3a03000 	mov	r3, #0	; 0x0
300116ec:	e58d3004 	str	r3, [sp, #4]
300116f0:	e59d3004 	ldr	r3, [sp, #4]
300116f4:	e1a00003 	mov	r0, r3
300116f8:	e28dd01c 	add	sp, sp, #28	; 0x1c
300116fc:	e49de004 	pop	{lr}		; (ldr lr, [sp], #4)
30011700:	e12fff1e 	bx	lr

30011704 <uart_receive_char>:
30011704:	e24dd008 	sub	sp, sp, #8	; 0x8
30011708:	e58d0004 	str	r0, [sp, #4]
3001170c:	e58d1000 	str	r1, [sp]
30011710:	e3a03000 	mov	r3, #0	; 0x0
30011714:	e1a00003 	mov	r0, r3
30011718:	e28dd008 	add	sp, sp, #8	; 0x8
3001171c:	e12fff1e 	bx	lr

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
30011934:	ebfff9e1 	bl	300100c0 <raise>
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
30011984:	300102d0 	.word	0x300102d0

30011988 <lmosem_swi_l>:
30011988:	3001030c 	.word	0x3001030c

3001198c <lmosem_prefabt_l>:
3001198c:	30010338 	.word	0x30010338

30011990 <lmosem_dataabt_l>:
30011990:	30010370 	.word	0x30010370

30011994 <lmosem_bugdie_l>:
30011994:	300103ac 	.word	0x300103ac

30011998 <lmosem_irq_l>:
30011998:	300103b0 	.word	0x300103b0

3001199c <lmosem_frq_l>:
3001199c:	300103ec 	.word	0x300103ec

Disassembly of section .data:

300119a0 <gint_indx>:
300119a0:	00000000 	.word	0x00000000

300119a4 <machadrspce>:
300119a4:	00000005 	.word	0x00000005
	...
300119b0:	001fffff 	.word	0x001fffff
300119b4:	00000001 	.word	0x00000001
300119b8:	00000000 	.word	0x00000000
300119bc:	08000000 	.word	0x08000000
300119c0:	0800000f 	.word	0x0800000f
300119c4:	00000001 	.word	0x00000001
300119c8:	00000000 	.word	0x00000000
300119cc:	10000000 	.word	0x10000000
300119d0:	1000000f 	.word	0x1000000f
300119d4:	00000001 	.word	0x00000001
300119d8:	00000000 	.word	0x00000000
300119dc:	19000000 	.word	0x19000000
300119e0:	190fffff 	.word	0x190fffff
300119e4:	00000001 	.word	0x00000001
300119e8:	00000000 	.word	0x00000000
300119ec:	20000000 	.word	0x20000000
300119f0:	2000000f 	.word	0x2000000f
300119f4:	00000001 	.word	0x00000001
300119f8:	00000000 	.word	0x00000000
300119fc:	28000000 	.word	0x28000000
30011a00:	28000007 	.word	0x28000007
30011a04:	00000001 	.word	0x00000001
30011a08:	00000000 	.word	0x00000000
30011a0c:	29000000 	.word	0x29000000
30011a10:	29000007 	.word	0x29000007
30011a14:	00000002 	.word	0x00000002
30011a18:	00000000 	.word	0x00000000
30011a1c:	30000000 	.word	0x30000000
30011a20:	33ffffff 	.word	0x33ffffff
30011a24:	00000001 	.word	0x00000001
30011a28:	00000000 	.word	0x00000000
30011a2c:	48000000 	.word	0x48000000
30011a30:	48000030 	.word	0x48000030
30011a34:	00000001 	.word	0x00000001
30011a38:	00000000 	.word	0x00000000
30011a3c:	49000000 	.word	0x49000000
30011a40:	49000058 	.word	0x49000058
30011a44:	00000001 	.word	0x00000001
30011a48:	00000000 	.word	0x00000000
30011a4c:	4a000000 	.word	0x4a000000
30011a50:	4a00001c 	.word	0x4a00001c
30011a54:	00000001 	.word	0x00000001
30011a58:	00000000 	.word	0x00000000
30011a5c:	4b000000 	.word	0x4b000000
30011a60:	4b0000e0 	.word	0x4b0000e0
30011a64:	00000001 	.word	0x00000001
30011a68:	00000000 	.word	0x00000000
30011a6c:	4c000000 	.word	0x4c000000
30011a70:	4c000018 	.word	0x4c000018
30011a74:	00000001 	.word	0x00000001
30011a78:	00000000 	.word	0x00000000
30011a7c:	4d000000 	.word	0x4d000000
30011a80:	4d000060 	.word	0x4d000060
30011a84:	00000001 	.word	0x00000001
30011a88:	00000000 	.word	0x00000000
30011a8c:	4e000000 	.word	0x4e000000
30011a90:	4e00003c 	.word	0x4e00003c
30011a94:	00000001 	.word	0x00000001
30011a98:	00000000 	.word	0x00000000
30011a9c:	4f000000 	.word	0x4f000000
30011aa0:	4f0000a0 	.word	0x4f0000a0
30011aa4:	00000001 	.word	0x00000001
30011aa8:	00000000 	.word	0x00000000
30011aac:	50000000 	.word	0x50000000
30011ab0:	50008028 	.word	0x50008028
30011ab4:	00000001 	.word	0x00000001
30011ab8:	00000000 	.word	0x00000000
30011abc:	51000000 	.word	0x51000000
30011ac0:	51000040 	.word	0x51000040
30011ac4:	00000001 	.word	0x00000001
30011ac8:	00000000 	.word	0x00000000
30011acc:	52000000 	.word	0x52000000
30011ad0:	5200026f 	.word	0x5200026f
30011ad4:	00000001 	.word	0x00000001
30011ad8:	00000000 	.word	0x00000000
30011adc:	53000000 	.word	0x53000000
30011ae0:	53000008 	.word	0x53000008
30011ae4:	00000001 	.word	0x00000001
30011ae8:	00000000 	.word	0x00000000
30011aec:	54000000 	.word	0x54000000
30011af0:	54000010 	.word	0x54000010
30011af4:	00000001 	.word	0x00000001
30011af8:	00000000 	.word	0x00000000
30011afc:	55000000 	.word	0x55000000
30011b00:	55000012 	.word	0x55000012
30011b04:	00000001 	.word	0x00000001
30011b08:	00000000 	.word	0x00000000
30011b0c:	56000000 	.word	0x56000000
30011b10:	560000cc 	.word	0x560000cc
30011b14:	00000001 	.word	0x00000001
30011b18:	00000000 	.word	0x00000000
30011b1c:	57000040 	.word	0x57000040
30011b20:	5700008b 	.word	0x5700008b
30011b24:	00000001 	.word	0x00000001
30011b28:	00000000 	.word	0x00000000
30011b2c:	58000000 	.word	0x58000000
30011b30:	58000014 	.word	0x58000014
30011b34:	00000001 	.word	0x00000001
30011b38:	00000000 	.word	0x00000000
30011b3c:	59000000 	.word	0x59000000
30011b40:	59000034 	.word	0x59000034
30011b44:	00000001 	.word	0x00000001
30011b48:	00000000 	.word	0x00000000
30011b4c:	5a000000 	.word	0x5a000000
30011b50:	5a000043 	.word	0x5a000043
30011b54:	00000001 	.word	0x00000001
30011b58:	00000000 	.word	0x00000000
30011b5c:	5b000000 	.word	0x5b000000
30011b60:	5b00001c 	.word	0x5b00001c
30011b64:	00000000 	.word	0x00000000
30011b68:	0fffffff 	.word	0x0fffffff
	...

30011b74 <osmach>:
	...

30011ba8 <osphymen>:
	...

30011c7c <machintflt>:
	...

30012794 <osphymem>:
	...

Disassembly of section .rodata:

30012868 <.rodata>:
30012868:	5f525355 	.word	0x5f525355
3001286c:	20474552 	.word	0x20474552
30012870:	253a3072 	.word	0x253a3072
30012874:	000d0a78 	.word	0x000d0a78
30012878:	5f525355 	.word	0x5f525355
3001287c:	20474552 	.word	0x20474552
30012880:	253a3172 	.word	0x253a3172
30012884:	000d0a78 	.word	0x000d0a78
30012888:	5f525355 	.word	0x5f525355
3001288c:	20474552 	.word	0x20474552
30012890:	253a3272 	.word	0x253a3272
30012894:	000d0a78 	.word	0x000d0a78
30012898:	5f525355 	.word	0x5f525355
3001289c:	20474552 	.word	0x20474552
300128a0:	253a3372 	.word	0x253a3372
300128a4:	000d0a78 	.word	0x000d0a78
300128a8:	5f525355 	.word	0x5f525355
300128ac:	20474552 	.word	0x20474552
300128b0:	253a3472 	.word	0x253a3472
300128b4:	000d0a78 	.word	0x000d0a78
300128b8:	5f525355 	.word	0x5f525355
300128bc:	20474552 	.word	0x20474552
300128c0:	253a3572 	.word	0x253a3572
300128c4:	000d0a78 	.word	0x000d0a78
300128c8:	5f525355 	.word	0x5f525355
300128cc:	20474552 	.word	0x20474552
300128d0:	253a3672 	.word	0x253a3672
300128d4:	000d0a78 	.word	0x000d0a78
300128d8:	5f525355 	.word	0x5f525355
300128dc:	20474552 	.word	0x20474552
300128e0:	253a3772 	.word	0x253a3772
300128e4:	000d0a78 	.word	0x000d0a78
300128e8:	5f525355 	.word	0x5f525355
300128ec:	20474552 	.word	0x20474552
300128f0:	253a3872 	.word	0x253a3872
300128f4:	000d0a78 	.word	0x000d0a78
300128f8:	5f525355 	.word	0x5f525355
300128fc:	20474552 	.word	0x20474552
30012900:	253a3972 	.word	0x253a3972
30012904:	000d0a78 	.word	0x000d0a78
30012908:	5f525355 	.word	0x5f525355
3001290c:	20474552 	.word	0x20474552
30012910:	3a303172 	.word	0x3a303172
30012914:	0d0a7825 	.word	0x0d0a7825
30012918:	00000000 	.word	0x00000000
3001291c:	5f525355 	.word	0x5f525355
30012920:	20474552 	.word	0x20474552
30012924:	3a313172 	.word	0x3a313172
30012928:	0d0a7825 	.word	0x0d0a7825
3001292c:	00000000 	.word	0x00000000
30012930:	5f525355 	.word	0x5f525355
30012934:	20474552 	.word	0x20474552
30012938:	3a323172 	.word	0x3a323172
3001293c:	0d0a7825 	.word	0x0d0a7825
30012940:	00000000 	.word	0x00000000
30012944:	5f525355 	.word	0x5f525355
30012948:	20474552 	.word	0x20474552
3001294c:	3a333172 	.word	0x3a333172
30012950:	0d0a7825 	.word	0x0d0a7825
30012954:	00000000 	.word	0x00000000
30012958:	5f525355 	.word	0x5f525355
3001295c:	20474552 	.word	0x20474552
30012960:	3a343172 	.word	0x3a343172
30012964:	0d0a7825 	.word	0x0d0a7825
30012968:	00000000 	.word	0x00000000
3001296c:	5f455653 	.word	0x5f455653
30012970:	20474552 	.word	0x20474552
30012974:	253a726c 	.word	0x253a726c
30012978:	000d0a78 	.word	0x000d0a78
3001297c:	5f455653 	.word	0x5f455653
30012980:	20474552 	.word	0x20474552
30012984:	72737073 	.word	0x72737073
30012988:	0a78253a 	.word	0x0a78253a
3001298c:	0000000d 	.word	0x0000000d
30012990:	5f505343 	.word	0x5f505343
30012994:	20474552 	.word	0x20474552
30012998:	253a7073 	.word	0x253a7073
3001299c:	4e492078 	.word	0x4e492078
300129a0:	444e5054 	.word	0x444e5054
300129a4:	0a78253a 	.word	0x0a78253a
300129a8:	0000000d 	.word	0x0000000d
300129ac:	5f524343 	.word	0x5f524343
300129b0:	20474552 	.word	0x20474552
300129b4:	72737063 	.word	0x72737063
300129b8:	2078253a 	.word	0x2078253a
300129bc:	4f544e49 	.word	0x4f544e49
300129c0:	3a545346 	.word	0x3a545346
300129c4:	0d0a7825 	.word	0x0d0a7825
300129c8:	00000000 	.word	0x00000000
300129cc:	65646e75 	.word	0x65646e75
300129d0:	736e6966 	.word	0x736e6966
300129d4:	6e757220 	.word	0x6e757220
300129d8:	21676e69 	.word	0x21676e69
300129dc:	00000021 	.word	0x00000021
300129e0:	35315043 	.word	0x35315043
300129e4:	3a356320 	.word	0x3a356320
300129e8:	63207825 	.word	0x63207825
300129ec:	78252036 	.word	0x78252036
300129f0:	00000d0a 	.word	0x00000d0a
300129f4:	66657270 	.word	0x66657270
300129f8:	74626120 	.word	0x74626120
300129fc:	6e757220 	.word	0x6e757220
30012a00:	00676e69 	.word	0x00676e69
30012a04:	61746164 	.word	0x61746164
30012a08:	74626120 	.word	0x74626120
30012a0c:	6e757220 	.word	0x6e757220
30012a10:	00676e69 	.word	0x00676e69
30012a14:	20677562 	.word	0x20677562
30012a18:	20656964 	.word	0x20656964
30012a1c:	696e7572 	.word	0x696e7572
30012a20:	0000676e 	.word	0x0000676e
30012a24:	75626469 	.word	0x75626469
30012a28:	6e652067 	.word	0x6e652067
30012a2c:	2e726574 	.word	0x2e726574
30012a30:	2078252e 	.word	0x2078252e
30012a34:	00000d0a 	.word	0x00000d0a
30012a38:	75626469 	.word	0x75626469
30012a3c:	78652067 	.word	0x78652067
30012a40:	2e2e7469 	.word	0x2e2e7469
30012a44:	0a207825 	.word	0x0a207825
30012a48:	0000000d 	.word	0x0000000d
30012a4c:	20717266 	.word	0x20717266
30012a50:	696e7572 	.word	0x696e7572
30012a54:	2121676e 	.word	0x2121676e
30012a58:	00000000 	.word	0x00000000
30012a5c:	5f6c6168 	.word	0x5f6c6168
30012a60:	5f6e7572 	.word	0x5f6e7572
30012a64:	66746e69 	.word	0x66746e69
30012a68:	7364746c 	.word	0x7364746c
30012a6c:	72652063 	.word	0x72652063
30012a70:	00000072 	.word	0x00000072
30012a74:	33323130 	.word	0x33323130
30012a78:	37363534 	.word	0x37363534
30012a7c:	62613938 	.word	0x62613938
30012a80:	66656463 	.word	0x66656463
30012a84:	00000000 	.word	0x00000000
30012a88:	534f4d4c 	.word	0x534f4d4c
30012a8c:	53204d45 	.word	0x53204d45
30012a90:	45545359 	.word	0x45545359
30012a94:	5349204d 	.word	0x5349204d
30012a98:	45494420 	.word	0x45494420
30012a9c:	00732520 	.word	0x00732520
30012aa0:	74726175 	.word	0x74726175
30012aa4:	72726520 	.word	0x72726520
30012aa8:	00000000 	.word	0x00000000

Disassembly of section .ARM.attributes:

00000000 <.ARM.attributes>:
   0:	00002a41 	andeq	r2, r0, r1, asr #20
   4:	61656100 	cmnvs	r5, r0, lsl #2
   8:	01006962 	tsteq	r0, r2, ror #18
   c:	00000020 	andeq	r0, r0, r0, lsr #32
  10:	4d524105 	ldfmie	f4, [r2, #-20]
  14:	54357620 	ldrtpl	r7, [r5], #-1568
  18:	08030600 	stmdaeq	r3, {r9, sl}
  1c:	12010901 	andne	r0, r1, #16384	; 0x4000
  20:	15011404 	strne	r1, [r1, #-1028]
  24:	18031701 	stmdane	r3, {r0, r8, r9, sl, ip}
  28:	Address 0x00000028 is out of bounds.


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
