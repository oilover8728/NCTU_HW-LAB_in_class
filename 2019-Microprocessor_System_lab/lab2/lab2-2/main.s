	.syntax unified
	.cpu cortex-m4
	.thumb
.data
	result: .word  0
	max_size:  .word  0
.text
	m: .word  0x50
	n: .word  0x30
	.global main

step1:		//a==0 return b:
	add r12,r12,r1
	b GCDend

step2:		//b==0 return a:
	add r12,r12,r0
	b GCDend

step3:		//a%2==0 && b%2==0 return 2 * GCD(a>>1,b>>1):
	push {r2}
	lsr r0, r0, #1
	lsr r1, r1, #1
	b GCD

step4:		//a%2==0 return GCD(a>>1,b)
	lsr r0, r0, #1
	b GCD

step5:		//b%2==0 return GCD(a,b>>1)
	lsr r1, r1, #1
	b GCD

ab:
	sub r0,r0,r1
	b GCD

step6:		//else return GCD(abs(a-b),min(a,b)):
	cmp r0,r1
	bgt ab
	ba:	//r7 is temp	temp=a; a=b-a; b=temp
	mov r7, #0
	add r7,r7,r0
	sub r0,r1,r0
	add r1,r7,#0
	b GCD

GCD:     //TODO: Implement your GCD function
	add r11,r11,#1
	cmp r0, #0
	beq step1		//a==0 return b

	cmp r1, #0
	beq step2		//b==0 return a

	and r4,r0,#1	//(a%2)
	and r5,r1,#1	//(b%2)
	orr r6,r4,r5		//check if (a%2) or (b%2) !=0
	cmp	r6, #0
	beq step3		//a%2==0 && b%2==0 return 2 * GCD(a>>1,b>>1)

	cmp r4, #0		//if(a%2==0)
	beq	step4		//a%2==0 return GCD(a,b>>1)

	cmp r5, #0
	beq step5		//b%2==0 return GCD(a>>1,b)

	//else
	b step6			//return GCD(abs(a-b),min(a,b))

	GCDend:
	BX LR

main:
	ldr r9, =m
	ldr r0, [r9]
	ldr r9, =n
	ldr r1, [r9]
	ldr r8, =result
	ldr r10, =max_size
	mov r2,#2
	mov r3,#1
	mov r11, #0	//r11=maxsize
	mov r12, #0	//result
	// r0 = m, r1 = n
	BL GCD
	next:
	ldr	r4,	[sp]
	cmp r4, #2
	bne store
	mul r12, r12, r4;
	pop {r4}
	b next
	// get return val and store into result
store:
	str r12, [r8]
	str r11, [r10]
end:
	b end
