.text

.macro DEBUG num
	stmfd sp!, {r0-r3,lr}  
	mov r0, \num   
	bl show_led    
	ldmfd sp!, {r0-r3,lr} 
.endm


.global _start
_start:
	/*
	 * set the cpu to SVC32 mode
	 */
	mrs	r0, cpsr
	bic	r0, r0, #0x1f
	/*0xd3 disable irq and fiq*/
	orr	r0, r0, #0xd3
	msr	cpsr,r0

	/* LED INPUT*/
	@ldr r0, =0x110002E0
	@mov r1, #0
	@str r1, [r0]
	
	// 设置堆栈在LB2栈的上面4K的位置，参考IROM手册
	@ldr sp, =0x02028400
	ldr sp, =0x0205fffc
	bl  close_wdt
	bl  icache_open
	@/*bl  system_clock_init */
	bl init_led
	b main

.global code_relocate
code_relocate:
	/*get the current addr of start*/	
	adr r0, _start	
	/*get the link addr of start, must use _start*/
	ldr r1, =_start
	ldr r3, = bss_start
	cmp r0, r1
	beq clean_bss
	@DEBUG #1
copy_code:
	DEBUG #6
	ldr r2, [r0], #4   @ copy from start
	str r2, [r1], #4   @ copy to linkaddr
	cmp r1, r3		   @ copy till the bss start
	bne copy_code
	@DEBUG #2
	
clean_bss:
	ldr r0, = bss_start
   	ldr r1, = bss_end
   	cmp r0, r1
    beq ret
    
	@DEBUG #3
   	mov r2, #0
set_zero:
    str r2, [r0], #4
	cmp r0, r1
   	bne set_zero
   	
	@DEBUG #4
ret:
		
	/*get the current addr of start*/	
	adr r0, _start	
	/*get the link addr of start, must use _start*/
	ldr r1, =_start
	/*basic ,the offset must be the same*/	
	mov r3, lr
	sub r3, r0
	add lr, r3, r1 @ new lr
	
	@DEBUG #8
	mov pc, lr

.global init_led
init_led:
	ldr r0, =0x110002E0
	ldr r1, [r0] 
	ldr r2, =0xffff
	bic r1, r1, r2
	ldr r2, =0x00001111
	orr r1, r1, r2
	str r1, [r0]
	mov pc, lr
	
.global show_led
show_led:
	ldr	r1, =0x110002E0
	eor r0,r0,#15
	@and r0,r0,#15
	str	r0, [r1, #0x04]
	mov pc,lr
	
.global halt_loop
halt_loop:
	b halt_loop

close_wdt:
	ldr r0, =0x10060000
	mov r1, #0
	str r1, [r0]
icache_open:
	mrc p15, 0, r0, c1, c0, 0
	orr r0, r0, #0x00001000
	@bic r0, r0, #0x00001000
	mcr p15, 0, r0, c1, c0, 0

	
