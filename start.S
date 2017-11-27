.text

.macro LED_DEBUG num
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
	
	// 设置堆栈在LB2栈的上面4K的位置，参考IROM手册
	mov fp, sp
	@ldr sp, =0x02028400
	//设置堆栈在最顶
	ldr sp, =0x02060000
	bl  close_wdt
	bl  icache_open
	bl init_led
	adr r0, _start	
	mov r1, fp
	@ldr pc, =_main
	b _main
	
.global get_start
get_start:
	adr r0, _start
	mov pc, lr
.global code_relocate

.global get_code_size
get_code_size:
	ldr r1, =_start
	ldr r0, =bss_start
	sub r0, r0, r1
	mov pc,lr

code_relocate:
	/*get the current addr of start*/	
	adr r0, _start	
	/*get the link addr of start, must use _start*/
	ldr r1, =_start
	ldr r3, = bss_start
	cmp r0, r1
	beq clean_bss
	@LED_DEBUG #1
copy_code:
	LED_DEBUG #6
	ldr r2, [r0], #4   @ copy from start
	str r2, [r1], #4   @ copy to linkaddr
	cmp r1, r3		   @ copy till the bss start
	bne copy_code
	@DEBUG #2
	
clean_bss:
	ldr r0, =bss_start
   	ldr r1, =bss_end
   	cmp r0, r1
    beq ret
    
	@LED_DEBUG #3
   	mov r2, #0
set_zero:
    str r2, [r0], #4
	cmp r0, r1
   	bne set_zero
   	
	@LED_DEBUG #4
ret:
		
	/*get the current addr of start*/	
	adr r0, _start	
	/*get the link addr of start, must use _start*/
	ldr r1, =_start
	/*basic ,the offset must be the same*/	
	mov r3, lr
	sub r3, r0
	add lr, r3, r1 @ new lr
	
	@LED_DEBUG #8
	mov pc, lr

.global init_led
init_led:
	ldr r0, =0x110002e0	 	
	ldr r1, [r0] 
	lsr r1, r1, #16
	lsl r1, r1, #16
	ldr r2, =0x1111
	orr r1, r1, r2
	str r1, [r0]	
	mov pc, lr
	
.global show_led
show_led:
	ldr	r1, =0x110002E4
	eor r0,r0,#15
	@and r0,r0,#15
	str	r0, [r1]
	mov pc,lr
	
.global halt_loop
halt_loop:
	b halt_loop

close_wdt:
	ldr r0, =0x10060000
	mov r1, #0
	str r1, [r0]
	mov pc, lr
icache_open:
	mrc p15, 0, r0, c1, c0, 0
	orr r0, r0, #0x00001000
	@bic r0, r0, #0x00001000
	mcr p15, 0, r0, c1, c0, 0
	mov pc, lr
	
