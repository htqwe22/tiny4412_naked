
/**********************************************************************************
 * FILE : kv_string.c
 * Description:
 * Author: Kevin He
 * Created On: 2018-12-01 , At 11:33:09
 * Modifiled On : 
 * Version : 0.0.1
 * Information :
 **********************************************************************************/

.text

.global kv_strlen
kv_strlen:
	MOV r1, #0
strlen_start:		
	LDRB r2, [r0], #1
	ADD	r1, r1, #1
	cmp r2, #0
	bne	 strlen_start
	sub r0, r1, #1
	mov pc, lr

	
	.global kv_strcpy
kv_strcpy:
	mov r2, r0
strcpy_start:		
	ldrb r3, [r1], #1
	strb r3, [r2], #1
	cmp r3, #0
	bne strcpy_start
	mov pc, lr


	.global kv_strcat
kv_strcat:
	stmfd sp!, {r0-r5, lr}
	mov r4, r0
	mov r5, r1
	bl	kv_strlen
	add r0, r4, r0	;@new start
	mov r1, r5
	bl	kv_strcpy
	ldmfd sp!, {r0-r5, pc}

	
	.global kv_memcpy
kv_memcpy:
	push {r4}
	mov r4, r0
memcpy_start:	
	cmp r2, #0
	beq memcpy_ret
	ldrb r3, [r1], #1
	strb r3, [r4], #1
	sub	r2, r2, #1
	b memcpy_start
memcpy_ret:
	pop {r4}
	mov pc, lr
	




	.global	kv_memset
kv_memset:
	mov r3, r0
memset_start:
	cmp r2, #0
	beq memset_ret
	strb r1, [r3], #1
	sub r2, r2, #1
	b memset_start
memset_ret:
	mov pc, lr

	
.global kv_memcmp
kv_memcmp:
	stmfd sp!, {r4, r5}
	mov r3, r0
	mov r0, #0
memcmp_start:
	cmp r2, #0
	beq memcmp_ret
	ldrb r4, [r3], #1
	ldrb r5, [r1], #1
	sub	r2, r2, #1
	subs r0, r4, r5
	beq	memcmp_start
memcmp_ret:
	ldmfd sp!, {r4, r5}
	mov pc, lr
	
.global kv_strcmp
kv_strcmp:
	stmfd sp!, {r4, r5}
	mov r2, r0
	mov r3, #1
	mov r0, #0
strcmp_start:
	cmp r3, #0
	beq strcmp_ret	
	ldrb r0, [r2], #1
	ldrb r3, [r1], #1
	subs r0, r0, r3
	beq strcmp_start
strcmp_ret:
	ldmfd sp!, {r4, r5}
	mov pc, lr
	
	.global kv_strchr
kv_strchr:
	ldrb r2, [r0], #1
	cmp r2, r1
	beq strchr_ok
	cmp r2, #0
	bne kv_strchr
strchr_err:
	mov r0,#1
strchr_ok:
	sub r0,r0,#1
	mov pc, lr



