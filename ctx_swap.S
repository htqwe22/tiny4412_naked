.global ctx_swap
.text
ctx_swap:
	stmfd sp!, {r0-r12, lr}
	mrs	r0, spsr
	push {r0}
	ldr r0, =current	@r0 = &current
	ldr r0, [r0]		@r0 = current
	str sp, [r0]		@top_stack = sp
	
	bl get_next_run_task	@now
	@now r0 = current
	mov r1, r0

	mov r0, #3
	bl show_led
	ldr r0, [r0]
	bl debug_lable
	mov r0, r1
	ldr sp, [r0]	
	mov r0, #4
	bl show_led
	pop {r0}
	msr	spsr, r0
	mov r0, #7
	bl show_led
	ldmfd sp!, {r0-r12, pc}^

.global schedule
schedule:
	swi 0
	mov pc, lr