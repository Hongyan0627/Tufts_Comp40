	.file	"phases.c"
	.section	.rodata
	.align 8
.LC0:
	.string	"This is actually not an entirely terrible idea."
	.data
	.align 8
	.type	TARGET_1, @object
	.size	TARGET_1, 8
TARGET_1:
	.quad	.LC0
	.section	.rodata
.LC1:
	.string	"giants"
	.data
	.align 8
	.type	TARGET_5, @object
	.size	TARGET_5, 8
TARGET_5:
	.quad	.LC1
	.section	.rodata
.LC2:
	.string	"isrveawhobpnutfg"
	.data
	.align 8
	.type	PARSE_5, @object
	.size	PARSE_5, 8
PARSE_5:
	.quad	.LC2
	.globl	node_9
	.align 16
	.type	node_9, @object
	.size	node_9, 16
node_9:
	.quad	158
	.quad	0
	.globl	node_8
	.align 16
	.type	node_8, @object
	.size	node_8, 16
node_8:
	.quad	862
	.quad	node_9
	.globl	node_7
	.align 16
	.type	node_7, @object
	.size	node_7, 16
node_7:
	.quad	599
	.quad	node_8
	.globl	node_6
	.align 16
	.type	node_6, @object
	.size	node_6, 16
node_6:
	.quad	246
	.quad	node_7
	.globl	node_5
	.align 16
	.type	node_5, @object
	.size	node_5, 16
node_5:
	.quad	480
	.quad	node_6
	.globl	node_4
	.align 16
	.type	node_4, @object
	.size	node_4, 16
node_4:
	.quad	781
	.quad	node_5
	.globl	node_3
	.align 16
	.type	node_3, @object
	.size	node_3, 16
node_3:
	.quad	888
	.quad	node_4
	.globl	node_2
	.align 16
	.type	node_2, @object
	.size	node_2, 16
node_2:
	.quad	655
	.quad	node_3
	.globl	node_1
	.align 16
	.type	node_1, @object
	.size	node_1, 16
node_1:
	.quad	722
	.quad	node_2
	.text
	.globl	phase_1
	.type	phase_1, @function
phase_1:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	TARGET_1(%rip), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strings_not_equal
	movl	%eax, -4(%rbp)
	cmpl	$1, -4(%rbp)
	jne	.L2
	movl	$0, %eax
	call	explode_bomb
.L2:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	phase_1, .-phase_1
	.section	.rodata
.LC3:
	.string	"%d %d %d %d %d %d"
	.text
	.globl	phase_2
	.type	phase_2, @function
phase_2:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -40(%rbp)
	leaq	-32(%rbp), %rax
	leaq	12(%rax), %r8
	leaq	-32(%rbp), %rax
	leaq	8(%rax), %rdi
	leaq	-32(%rbp), %rax
	leaq	4(%rax), %rcx
	leaq	-32(%rbp), %rdx
	movq	-40(%rbp), %rax
	leaq	-32(%rbp), %rsi
	addq	$20, %rsi
	movq	%rsi, 8(%rsp)
	leaq	-32(%rbp), %rsi
	addq	$16, %rsi
	movq	%rsi, (%rsp)
	movq	%r8, %r9
	movq	%rdi, %r8
	movl	$.LC3, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_sscanf
	movl	%eax, -8(%rbp)
	cmpl	$5, -8(%rbp)
	jg	.L5
	movl	$0, %eax
	call	explode_bomb
.L5:
	movl	$1, -4(%rbp)
	jmp	.L6
.L8:
	movl	-4(%rbp), %eax
	cltq
	movl	-32(%rbp,%rax,4), %edx
	movl	-4(%rbp), %eax
	subl	$1, %eax
	cltq
	movl	-32(%rbp,%rax,4), %eax
	addl	$5, %eax
	cmpl	%eax, %edx
	je	.L7
	movl	$0, %eax
	call	explode_bomb
.L7:
	addl	$1, -4(%rbp)
.L6:
	cmpl	$5, -4(%rbp)
	jle	.L8
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	phase_2, .-phase_2
	.section	.rodata
.LC4:
	.string	"%d %d"
	.text
	.globl	phase_3
	.type	phase_3, @function
phase_3:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	leaq	-16(%rbp), %rcx
	leaq	-12(%rbp), %rdx
	movq	-24(%rbp), %rax
	movl	$.LC4, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_sscanf
	movl	%eax, -8(%rbp)
	cmpl	$1, -8(%rbp)
	jg	.L11
	movl	$0, %eax
	call	explode_bomb
.L11:
	movl	-12(%rbp), %eax
	cmpl	$7, %eax
	jle	.L12
	movl	$0, %eax
	call	explode_bomb
	movl	$0, -4(%rbp)
	jmp	.L13
.L12:
	movl	-12(%rbp), %eax
	cmpl	$7, %eax
	ja	.L14
	movl	%eax, %eax
	movq	.L16(,%rax,8), %rax
	jmp	*%rax
	.section	.rodata
	.align 8
	.align 4
.L16:
	.quad	.L15
	.quad	.L14
	.quad	.L17
	.quad	.L18
	.quad	.L19
	.quad	.L20
	.quad	.L21
	.quad	.L22
	.text
.L15:
	movl	$424, -4(%rbp)
	jmp	.L13
.L17:
	movl	$518, -4(%rbp)
	jmp	.L13
.L18:
	movl	$486, -4(%rbp)
	jmp	.L13
.L19:
	movl	$381, -4(%rbp)
	jmp	.L13
.L20:
	movl	$426, -4(%rbp)
	jmp	.L13
.L21:
	movl	$651, -4(%rbp)
	jmp	.L13
.L22:
	movl	$284, -4(%rbp)
	jmp	.L13
.L14:
	movl	$455, -4(%rbp)
.L13:
	movl	-16(%rbp), %eax
	cmpl	-4(%rbp), %eax
	je	.L23
	movl	$0, %eax
	call	explode_bomb
.L23:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	phase_3, .-phase_3
	.globl	func4
	.type	func4, @function
func4:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	cmpl	$1, -4(%rbp)
	jg	.L26
	movl	$1, %eax
	jmp	.L27
.L26:
	movl	-4(%rbp), %eax
	subl	$1, %eax
	movl	%eax, %edi
	call	func4
	imull	-4(%rbp), %eax
.L27:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	func4, .-func4
	.section	.rodata
.LC5:
	.string	"%d"
	.text
	.globl	phase_4
	.type	phase_4, @function
phase_4:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	leaq	-12(%rbp), %rdx
	movq	-24(%rbp), %rax
	movl	$.LC5, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_sscanf
	movl	%eax, -4(%rbp)
	cmpl	$1, -4(%rbp)
	je	.L29
	movl	$0, %eax
	call	explode_bomb
.L29:
	movl	-12(%rbp), %eax
	testl	%eax, %eax
	jg	.L30
	movl	$0, %eax
	call	explode_bomb
.L30:
	movl	-12(%rbp), %eax
	movl	%eax, %edi
	call	func4
	movl	%eax, -8(%rbp)
	cmpl	$5040, -8(%rbp)
	je	.L31
	movl	$0, %eax
	call	explode_bomb
.L31:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	phase_4, .-phase_4
	.globl	phase_5
	.type	phase_5, @function
phase_5:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	string_length
	cmpl	$6, %eax
	je	.L34
	movl	$0, %eax
	call	explode_bomb
.L34:
	movl	$0, -4(%rbp)
	jmp	.L35
.L36:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movl	%eax, %edx
	sarb	$7, %dl
	shrb	$4, %dl
	addl	%edx, %eax
	andl	$15, %eax
	subl	%edx, %eax
	movsbl	%al, %eax
	movl	%eax, -8(%rbp)
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rax, %rdx
	movq	PARSE_5(%rip), %rcx
	movl	-8(%rbp), %eax
	cltq
	addq	%rcx, %rax
	movzbl	(%rax), %eax
	movb	%al, (%rdx)
	addl	$1, -4(%rbp)
.L35:
	cmpl	$5, -4(%rbp)
	jle	.L36
	movq	TARGET_5(%rip), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strings_not_equal
	movl	%eax, -12(%rbp)
	cmpl	$0, -12(%rbp)
	je	.L37
	movl	$0, %eax
	call	explode_bomb
.L37:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	phase_5, .-phase_5
	.globl	fun_6
	.type	fun_6, @function
fun_6:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -40(%rbp)
	cmpq	$0, -40(%rbp)
	jne	.L40
	jmp	.L39
.L40:
	movq	-40(%rbp), %rax
	movq	$node_1, 8(%rax)
	movq	-40(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -16(%rbp)
	jmp	.L42
.L46:
	jmp	.L43
.L45:
	movq	-16(%rbp), %rax
	movq	(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	cmpq	%rax, %rdx
	jle	.L44
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -24(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rdx, (%rax)
.L44:
	movq	-16(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -16(%rbp)
.L43:
	cmpq	$0, -16(%rbp)
	jne	.L45
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -8(%rbp)
.L42:
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	testq	%rax, %rax
	jne	.L46
	nop
.L39:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	fun_6, .-fun_6
	.globl	phase_6
	.type	phase_6, @function
phase_6:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -56(%rbp)
	movq	-56(%rbp), %rax
	movl	$10, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	strtol
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -48(%rbp)
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	fun_6
	leaq	-48(%rbp), %rax
	movq	%rax, -16(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L48
.L49:
	movq	-16(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -16(%rbp)
	addl	$1, -4(%rbp)
.L48:
	cmpl	$4, -4(%rbp)
	jle	.L49
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	cmpq	-24(%rbp), %rax
	je	.L50
	movl	$0, %eax
	call	explode_bomb
.L50:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	phase_6, .-phase_6
	.globl	fun_7
	.type	fun_7, @function
fun_7:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	cmpq	-8(%rbp), %rax
	jg	.L53
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	cmpq	-8(%rbp), %rax
	jne	.L54
	movl	$0, %eax
	jmp	.L55
.L54:
	movq	-16(%rbp), %rax
	movq	16(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	fun_7
	addq	%rax, %rax
	addq	$1, %rax
	jmp	.L55
.L53:
	movq	-16(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	fun_7
	addq	%rax, %rax
.L55:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	fun_7, .-fun_7
	.globl	secret_phase
	.type	secret_phase, @function
secret_phase:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	read_line
	movq	-24(%rbp), %rax
	movl	$10, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	strtol
	movq	%rax, -8(%rbp)
	cmpq	$1001, -8(%rbp)
	jle	.L57
	movl	$0, %eax
	call	explode_bomb
.L57:
	movq	BST(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	fun_7
	movq	%rax, -16(%rbp)
	cmpq	$6, -16(%rbp)
	je	.L58
	movl	$0, %eax
	call	explode_bomb
.L58:
	movl	$0, %eax
	call	phase_defused
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	secret_phase, .-secret_phase
	.ident	"GCC: (GNU) 4.8.0"
	.section	.note.GNU-stack,"",@progbits
