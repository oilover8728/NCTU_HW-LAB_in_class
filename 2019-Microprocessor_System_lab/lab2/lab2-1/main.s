	.syntax unified
	.cpu cortex-m4
	.thumb

.data
	user_stack: .zero 128
	expr_result: .word 0

.text
	.global main
	postfix_expr:	.asciz	"1 -1 +"//-100 10 20 + - 10 +
	.align
//r0=&postfix_expr, r1=&user_stack, r5=&expr_result
//r2=char, r3=tmp_r0, r6=10, r9=r8+-r7, r10=answer, r11=char, r12=integer
main:
	ldr r0, =postfix_expr
	ldr r1, =user_stack
	ldr r5, =expr_result
	mov r6, #10
	start:
	ldrb r2, [r0]

	cmp r2, #0
	beq	end

	cmp r2, ' '
	itt eq
	addeq r0,r0,#1
	beq start

	cmp r2, '-'
	itte eq
	addeq r3,r0,#1
	ldrbeq r2, [r3]
	bne next
		cmp r2, ' '
		beq pminus

		add r0,r0,#1
		b atoi_neg
		go_back_neg:
		neg r12,r12
		push {r12}
		b start

	next:
	cmp r2,'+'
	beq ppostive

	b atoi_pos
	go_back_pos:
	push {r12}
	b start

	end:
		ldr r10, [sp]
		str r10, [r5]

	program_end:
		B   program_end



atoi_neg:
mov r12,#0
start_loop_atoi:
	ldrb r2, [r0]
	cmp r2, ' '
	beq end_loop_atoi
	mul r12,r12,r6
	sub r11,r2,'0'
	add r12,r12,r11
	add r0,r0,#1
	b start_loop_atoi

end_loop_atoi:
	b go_back_neg


atoi_pos:
// make r12 the reault
// make r11 a tmp val
mov r12,#0
start_loop_atoi_p:
	ldrb r2, [r0]
	cmp r2, ' '
	beq end_loop_atoi_p
	mul r12,r12,r6
	sub r11,r2,'0'
	add r12,r12,r11
	add r0,r0,#1
	b start_loop_atoi_p

end_loop_atoi_p:
	b go_back_pos

pminus:
	ldr r7, [sp]
	ldr r8, [sp,#4]
	sub r9, r8, r7
	pop {r7, r8}
	push {r9}
	add r0,r0,#1
b start

ppostive:
	ldr r7, [sp]
	ldr r8, [sp,#4]
	add r9, r7, r8
	pop {r7,r8}
	push {r9}
	add r0,r0,#1
b start
