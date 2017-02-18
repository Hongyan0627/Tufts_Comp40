	.file	"calc.c"
	.text
.Ltext0:
	.type	push, @function
push:
.LFB0:
	.file 1 "calc.c"
	.loc 1 14 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	.loc 1 16 0
	movl	-12(%rbp), %eax
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	Seq_addhi
	.loc 1 17 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	push, .-push
	.type	pop, @function
pop:
.LFB1:
	.loc 1 20 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	.loc 1 21 0
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	Seq_remhi
	.loc 1 22 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	pop, .-pop
	.type	get, @function
get:
.LFB2:
	.loc 1 25 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	.loc 1 26 0
	movl	-12(%rbp), %edx
	movq	-8(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	Seq_get
	.loc 1 27 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	get, .-get
	.section	.rodata
.LC0:
	.string	"Division by zero"
.LC1:
	.string	">>> %d\n"
.LC2:
	.string	"Unknown character '%c'\n"
.LC3:
	.string	"calc.c"
	.text
	.type	run, @function
run:
.LFB3:
	.loc 1 60 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$112, %rsp
	movq	%rdi, -104(%rbp)
.L7:
	.loc 1 67 0
	call	getchar
	movl	%eax, -4(%rbp)
	jmp	.L8
.L56:
.LBB2:
	.loc 1 159 0
	nop
.L8:
.LBE2:
	.loc 1 70 0
	movl	-4(%rbp), %eax
	addl	$1, %eax
	cmpl	$127, %eax
	ja	.L9
	movl	%eax, %eax
	movq	.L11(,%rax,8), %rax
	jmp	*%rax
	.section	.rodata
	.align 8
	.align 4
.L11:
	.quad	.L54
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L12
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L13
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L14
	.quad	.L15
	.quad	.L9
	.quad	.L16
	.quad	.L9
	.quad	.L17
	.quad	.L18
	.quad	.L18
	.quad	.L18
	.quad	.L18
	.quad	.L18
	.quad	.L18
	.quad	.L18
	.quad	.L18
	.quad	.L18
	.quad	.L18
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L19
	.quad	.L20
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L21
	.quad	.L9
	.quad	.L9
	.quad	.L22
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L9
	.quad	.L55
	.quad	.L9
	.quad	.L24
	.quad	.L9
	.quad	.L25
	.text
.L18:
	.loc 1 75 0
	movl	-4(%rbp), %eax
	subl	$48, %eax
	movl	%eax, %edx
	movq	-104(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	push
	.loc 1 76 0
	jmp	.L27
.L15:
	.loc 1 78 0
	movq	-104(%rbp), %rax
	movl	$2, %esi
	movq	%rax, %rdi
	call	has
	testb	%al, %al
	je	.L28
.LBB3:
	.loc 1 78 0 is_stmt 0 discriminator 1
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	pop
	movl	%eax, -16(%rbp)
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	pop
	movl	%eax, -20(%rbp)
	movl	-16(%rbp), %eax
	movl	-20(%rbp), %edx
	addl	%eax, %edx
	movq	-104(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	push
.LBE3:
	jmp	.L7
.L28:
	.loc 1 78 0 discriminator 2
	jmp	.L7
.L16:
	.loc 1 79 0 is_stmt 1
	movq	-104(%rbp), %rax
	movl	$2, %esi
	movq	%rax, %rdi
	call	has
	testb	%al, %al
	je	.L29
.LBB4:
	.loc 1 79 0 is_stmt 0 discriminator 1
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	pop
	movl	%eax, -24(%rbp)
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	pop
	movl	%eax, -28(%rbp)
	movl	-24(%rbp), %eax
	movl	-28(%rbp), %edx
	subl	%eax, %edx
	movq	-104(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	push
.LBE4:
	jmp	.L7
.L29:
	.loc 1 79 0 discriminator 2
	jmp	.L7
.L14:
	.loc 1 80 0 is_stmt 1
	movq	-104(%rbp), %rax
	movl	$2, %esi
	movq	%rax, %rdi
	call	has
	testb	%al, %al
	je	.L30
.LBB5:
	.loc 1 80 0 is_stmt 0 discriminator 1
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	pop
	movl	%eax, -32(%rbp)
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	pop
	movl	%eax, -36(%rbp)
	movl	-36(%rbp), %eax
	imull	-32(%rbp), %eax
	movl	%eax, %edx
	movq	-104(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	push
.LBE5:
	jmp	.L7
.L30:
	.loc 1 80 0 discriminator 2
	jmp	.L7
.L13:
	.loc 1 81 0 is_stmt 1
	movq	-104(%rbp), %rax
	movl	$2, %esi
	movq	%rax, %rdi
	call	has
	testb	%al, %al
	je	.L31
.LBB6:
	.loc 1 81 0 is_stmt 0 discriminator 1
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	pop
	movl	%eax, -40(%rbp)
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	pop
	movl	%eax, -44(%rbp)
	movl	-40(%rbp), %eax
	movl	-44(%rbp), %edx
	andl	%eax, %edx
	movq	-104(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	push
.LBE6:
	jmp	.L7
.L31:
	.loc 1 81 0 discriminator 2
	jmp	.L7
.L24:
	.loc 1 82 0 is_stmt 1
	movq	-104(%rbp), %rax
	movl	$2, %esi
	movq	%rax, %rdi
	call	has
	testb	%al, %al
	je	.L32
.LBB7:
	.loc 1 82 0 is_stmt 0 discriminator 1
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	pop
	movl	%eax, -48(%rbp)
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	pop
	movl	%eax, -52(%rbp)
	movl	-48(%rbp), %eax
	movl	-52(%rbp), %edx
	orl	%eax, %edx
	movq	-104(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	push
.LBE7:
	jmp	.L7
.L32:
	.loc 1 82 0 discriminator 2
	jmp	.L7
.L25:
	.loc 1 83 0 is_stmt 1
	movq	-104(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	has
	testb	%al, %al
	je	.L33
.LBB8:
	.loc 1 83 0 is_stmt 0 discriminator 1
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	pop
	movl	%eax, -56(%rbp)
	movl	-56(%rbp), %eax
	notl	%eax
	movl	%eax, %edx
	movq	-104(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	push
.LBE8:
	jmp	.L7
.L33:
	.loc 1 83 0 discriminator 2
	jmp	.L7
.L19:
	.loc 1 84 0 is_stmt 1
	movq	-104(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	has
	testb	%al, %al
	je	.L34
.LBB9:
	.loc 1 84 0 is_stmt 0 discriminator 1
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	pop
	movl	%eax, -60(%rbp)
	movl	-60(%rbp), %eax
	negl	%eax
	movl	%eax, %edx
	movq	-104(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	push
.LBE9:
	jmp	.L7
.L34:
	.loc 1 84 0 discriminator 2
	jmp	.L7
.L17:
	.loc 1 86 0 is_stmt 1
	movq	-104(%rbp), %rax
	movl	$2, %esi
	movq	%rax, %rdi
	call	has
	testb	%al, %al
	je	.L35
.LBB10:
	.loc 1 87 0
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	pop
	movl	%eax, -64(%rbp)
	.loc 1 88 0
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	pop
	movl	%eax, -68(%rbp)
	.loc 1 89 0
	cmpl	$0, -64(%rbp)
	jne	.L36
	.loc 1 90 0
	movl	$.LC0, %edi
	call	puts
	.loc 1 91 0
	movl	-68(%rbp), %edx
	movq	-104(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	push
	.loc 1 92 0
	movl	-64(%rbp), %edx
	movq	-104(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	push
	jmp	.L35
.L36:
	.loc 1 93 0
	movl	-68(%rbp), %eax
	testl	%eax, %eax
	jns	.L37
	.loc 1 94 0
	movl	-64(%rbp), %eax
	testl	%eax, %eax
	jns	.L38
	.loc 1 95 0
	movl	-68(%rbp), %eax
	negl	%eax
	movl	%eax, -68(%rbp)
	.loc 1 96 0
	movl	-64(%rbp), %eax
	negl	%eax
	movl	%eax, -64(%rbp)
	.loc 1 97 0
	movl	-68(%rbp), %eax
	movl	$0, %edx
	divl	-64(%rbp)
	movl	%eax, %edx
	movq	-104(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	push
	jmp	.L35
.L38:
.LBB11:
	.loc 1 99 0
	movl	-68(%rbp), %eax
	negl	%eax
	movl	%eax, -68(%rbp)
	.loc 1 100 0
	movl	-68(%rbp), %eax
	movl	$0, %edx
	divl	-64(%rbp)
	movl	%eax, -72(%rbp)
	.loc 1 101 0
	movl	-72(%rbp), %eax
	negl	%eax
	movl	%eax, %edx
	movq	-104(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	push
.LBE11:
.LBE10:
	.loc 1 111 0
	jmp	.L7
.L37:
.LBB13:
	.loc 1 103 0
	movl	-64(%rbp), %eax
	testl	%eax, %eax
	jns	.L40
.LBB12:
	.loc 1 104 0
	movl	-64(%rbp), %eax
	negl	%eax
	movl	%eax, -64(%rbp)
	.loc 1 105 0
	movl	-68(%rbp), %eax
	movl	$0, %edx
	divl	-64(%rbp)
	movl	%eax, -76(%rbp)
	.loc 1 106 0
	movl	-76(%rbp), %eax
	negl	%eax
	movl	%eax, %edx
	movq	-104(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	push
.LBE12:
	jmp	.L35
.L40:
	.loc 1 108 0
	movl	-68(%rbp), %eax
	movl	$0, %edx
	divl	-64(%rbp)
	movl	%eax, %edx
	movq	-104(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	push
.LBE13:
	.loc 1 111 0
	jmp	.L7
.L35:
	jmp	.L7
.L22:
	.loc 1 114 0
	movq	-104(%rbp), %rax
	movl	$2, %esi
	movq	%rax, %rdi
	call	has
	testb	%al, %al
	je	.L41
.LBB14:
	.loc 1 115 0
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	pop
	movl	%eax, -80(%rbp)
	.loc 1 116 0
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	pop
	movl	%eax, -84(%rbp)
	.loc 1 117 0
	movl	-80(%rbp), %edx
	movq	-104(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	push
	.loc 1 118 0
	movl	-84(%rbp), %edx
	movq	-104(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	push
.LBE14:
	.loc 1 120 0
	jmp	.L7
.L41:
	jmp	.L7
.L20:
	.loc 1 122 0
	movq	-104(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	has
	testb	%al, %al
	je	.L42
.LBB15:
	.loc 1 123 0
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	pop
	movl	%eax, -88(%rbp)
	.loc 1 124 0
	movl	-88(%rbp), %edx
	movq	-104(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	push
	.loc 1 125 0
	movl	-88(%rbp), %edx
	movq	-104(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	push
.LBE15:
	.loc 1 127 0
	jmp	.L7
.L42:
	jmp	.L7
.L21:
	.loc 1 129 0
	movq	-104(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	has
	testb	%al, %al
	je	.L43
	.loc 1 130 0
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	pop
	.loc 1 131 0
	jmp	.L7
.L43:
	jmp	.L7
.L12:
.LBB16:
	.loc 1 133 0
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	Seq_length
	movl	%eax, -8(%rbp)
	jmp	.L44
.L45:
	.loc 1 134 0 discriminator 2
	movl	-8(%rbp), %eax
	leal	-1(%rax), %edx
	movq	-104(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	get
	movl	%eax, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	.loc 1 133 0 discriminator 2
	subl	$1, -8(%rbp)
.L44:
	.loc 1 133 0 is_stmt 0 discriminator 1
	cmpl	$0, -8(%rbp)
	jg	.L45
.LBE16:
	.loc 1 135 0 is_stmt 1
	jmp	.L7
.L47:
	.loc 1 138 0
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	Seq_remlo
	jmp	.L46
.L55:
	.loc 1 137 0
	nop
.L46:
	.loc 1 137 0 is_stmt 0 discriminator 1
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	Seq_length
	testl	%eax, %eax
	jg	.L47
	.loc 1 139 0 is_stmt 1
	jmp	.L7
.L9:
	.loc 1 141 0
	call	__ctype_b_loc
	movq	(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	addq	%rdx, %rdx
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	andl	$8192, %eax
	testl	%eax, %eax
	jne	.L48
	.loc 1 142 0
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	.loc 1 143 0
	jmp	.L7
.L48:
	jmp	.L7
.L27:
	.loc 1 147 0
	call	getchar
	movl	%eax, -4(%rbp)
	.loc 1 148 0
	movl	-4(%rbp), %eax
	subl	$48, %eax
	cmpl	$9, %eax
	ja	.L56
.LBB17:
	.loc 1 152 0
	movq	-104(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	has
	testb	%al, %al
	jne	.L51
	.loc 1 152 0 is_stmt 0 discriminator 2
	movl	$152, %edx
	movl	$.LC3, %esi
	movl	$Assert_Failed, %edi
	call	Except_raise
	jmp	.L53
.L51:
	.loc 1 152 0 discriminator 1
	nop
.L53:
	.loc 1 153 0 is_stmt 1
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	pop
	movl	%eax, -12(%rbp)
	.loc 1 154 0
	movl	-12(%rbp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	movl	%eax, %edx
	movl	-4(%rbp), %eax
	addl	%edx, %eax
	leal	-48(%rax), %edx
	movq	-104(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	push
	.loc 1 155 0
	jmp	.L27
.L54:
.LBE17:
	.loc 1 71 0
	nop
	.loc 1 161 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	run, .-run
	.globl	main
	.type	main, @function
main:
.LFB4:
	.loc 1 164 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	.loc 1 165 0
	movl	$10, %edi
	call	Seq_new
	movq	%rax, -8(%rbp)
	.loc 1 166 0
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	run
	.loc 1 167 0
	leaq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	Seq_free
	.loc 1 168 0
	movl	$0, %eax
	.loc 1 169 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	main, .-main
	.section	.rodata
.LC4:
	.string	""
.LC5:
	.string	"s"
	.align 8
.LC6:
	.string	"Stack underflow---expected at least %d element%s\n"
	.text
	.type	has, @function
has:
.LFB5:
	.loc 1 172 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	.loc 1 173 0
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	Seq_length
	cmpl	-12(%rbp), %eax
	jl	.L60
	.loc 1 174 0
	movl	$1, %eax
	jmp	.L61
.L60:
	.loc 1 176 0
	cmpl	$1, -12(%rbp)
	jne	.L62
	.loc 1 176 0 is_stmt 0 discriminator 1
	movl	$.LC4, %eax
	jmp	.L63
.L62:
	.loc 1 176 0 discriminator 2
	movl	$.LC5, %eax
.L63:
	.loc 1 176 0 discriminator 3
	movl	-12(%rbp), %ecx
	movq	%rax, %rdx
	movl	%ecx, %esi
	movl	$.LC6, %edi
	movl	$0, %eax
	call	printf
	.loc 1 179 0 is_stmt 1 discriminator 3
	movl	$0, %eax
.L61:
	.loc 1 181 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	has, .-has
.Letext0:
	.file 2 "/usr/sup/cii40/include/cii/except.h"
	.file 3 "/usr/include/stdint.h"
	.file 4 "/usr/sup/cii40/include/cii/seq.h"
	.file 5 "/usr/include/ctype.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x4f4
	.value	0x4
	.long	.Ldebug_abbrev0
	.byte	0x8
	.uleb128 0x1
	.long	.LASF37
	.byte	0x1
	.long	.LASF38
	.long	.LASF39
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.long	.Ldebug_line0
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF0
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.long	.LASF1
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF2
	.uleb128 0x4
	.long	.LASF21
	.byte	0x8
	.byte	0x2
	.byte	0x6
	.long	0x62
	.uleb128 0x5
	.long	.LASF40
	.byte	0x2
	.byte	0x7
	.long	0x62
	.byte	0
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x68
	.uleb128 0x7
	.long	0x6d
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF3
	.uleb128 0x8
	.long	.LASF21
	.byte	0x2
	.byte	0x8
	.long	0x49
	.uleb128 0x7
	.long	0x74
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.long	.LASF4
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.long	.LASF5
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF6
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF7
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.long	.LASF8
	.uleb128 0x9
	.byte	0x4
	.byte	0x5
	.byte	0x31
	.long	0x103
	.uleb128 0xa
	.long	.LASF9
	.sleb128 256
	.uleb128 0xa
	.long	.LASF10
	.sleb128 512
	.uleb128 0xa
	.long	.LASF11
	.sleb128 1024
	.uleb128 0xa
	.long	.LASF12
	.sleb128 2048
	.uleb128 0xa
	.long	.LASF13
	.sleb128 4096
	.uleb128 0xa
	.long	.LASF14
	.sleb128 8192
	.uleb128 0xa
	.long	.LASF15
	.sleb128 16384
	.uleb128 0xa
	.long	.LASF16
	.sleb128 32768
	.uleb128 0xa
	.long	.LASF17
	.sleb128 1
	.uleb128 0xa
	.long	.LASF18
	.sleb128 2
	.uleb128 0xa
	.long	.LASF19
	.sleb128 4
	.uleb128 0xa
	.long	.LASF20
	.sleb128 8
	.byte	0
	.uleb128 0x8
	.long	.LASF22
	.byte	0x3
	.byte	0x27
	.long	0x3b
	.uleb128 0x8
	.long	.LASF23
	.byte	0x3
	.byte	0x34
	.long	0x92
	.uleb128 0x8
	.long	.LASF24
	.byte	0x3
	.byte	0x7b
	.long	0x42
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.long	.LASF25
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF26
	.uleb128 0x8
	.long	.LASF27
	.byte	0x4
	.byte	0x5
	.long	0x13d
	.uleb128 0x6
	.byte	0x8
	.long	0x143
	.uleb128 0xb
	.long	.LASF27
	.uleb128 0x8
	.long	.LASF28
	.byte	0x1
	.byte	0xa
	.long	0x10e
	.uleb128 0xc
	.long	.LASF31
	.byte	0x1
	.byte	0xd
	.quad	.LFB0
	.quad	.LFE0-.LFB0
	.uleb128 0x1
	.byte	0x9c
	.long	0x18d
	.uleb128 0xd
	.long	.LASF29
	.byte	0x1
	.byte	0xd
	.long	0x132
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0xd
	.long	.LASF30
	.byte	0x1
	.byte	0xd
	.long	0x148
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.byte	0
	.uleb128 0xe
	.string	"pop"
	.byte	0x1
	.byte	0x13
	.long	0x148
	.quad	.LFB1
	.quad	.LFE1-.LFB1
	.uleb128 0x1
	.byte	0x9c
	.long	0x1bd
	.uleb128 0xd
	.long	.LASF29
	.byte	0x1
	.byte	0x13
	.long	0x132
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0xe
	.string	"get"
	.byte	0x1
	.byte	0x18
	.long	0x148
	.quad	.LFB2
	.quad	.LFE2-.LFB2
	.uleb128 0x1
	.byte	0x9c
	.long	0x1f9
	.uleb128 0xd
	.long	.LASF29
	.byte	0x1
	.byte	0x18
	.long	0x132
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0xf
	.string	"i"
	.byte	0x1
	.byte	0x18
	.long	0x3b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.byte	0
	.uleb128 0x10
	.string	"run"
	.byte	0x1
	.byte	0x3b
	.quad	.LFB3
	.quad	.LFE3-.LFB3
	.uleb128 0x1
	.byte	0x9c
	.long	0x479
	.uleb128 0xd
	.long	.LASF29
	.byte	0x1
	.byte	0x3b
	.long	0x132
	.uleb128 0x3
	.byte	0x91
	.sleb128 -120
	.uleb128 0x11
	.string	"c"
	.byte	0x1
	.byte	0x3d
	.long	0x3b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x12
	.long	.LASF32
	.byte	0x1
	.byte	0x3e
	.quad	.L7
	.uleb128 0x12
	.long	.LASF33
	.byte	0x1
	.byte	0x45
	.quad	.L8
	.uleb128 0x12
	.long	.LASF34
	.byte	0x1
	.byte	0x91
	.quad	.L27
	.uleb128 0x13
	.long	.Ldebug_ranges0+0
	.long	0x274
	.uleb128 0x11
	.string	"w"
	.byte	0x1
	.byte	0x99
	.long	0x148
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.byte	0
	.uleb128 0x14
	.quad	.LBB3
	.quad	.LBE3-.LBB3
	.long	0x2a2
	.uleb128 0x11
	.string	"y"
	.byte	0x1
	.byte	0x4e
	.long	0x148
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x11
	.string	"x"
	.byte	0x1
	.byte	0x4e
	.long	0x148
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.byte	0
	.uleb128 0x14
	.quad	.LBB4
	.quad	.LBE4-.LBB4
	.long	0x2d0
	.uleb128 0x11
	.string	"y"
	.byte	0x1
	.byte	0x4f
	.long	0x148
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x11
	.string	"x"
	.byte	0x1
	.byte	0x4f
	.long	0x148
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.byte	0
	.uleb128 0x14
	.quad	.LBB5
	.quad	.LBE5-.LBB5
	.long	0x2fe
	.uleb128 0x11
	.string	"y"
	.byte	0x1
	.byte	0x50
	.long	0x148
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x11
	.string	"x"
	.byte	0x1
	.byte	0x50
	.long	0x148
	.uleb128 0x2
	.byte	0x91
	.sleb128 -52
	.byte	0
	.uleb128 0x14
	.quad	.LBB6
	.quad	.LBE6-.LBB6
	.long	0x32c
	.uleb128 0x11
	.string	"y"
	.byte	0x1
	.byte	0x51
	.long	0x148
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x11
	.string	"x"
	.byte	0x1
	.byte	0x51
	.long	0x148
	.uleb128 0x2
	.byte	0x91
	.sleb128 -60
	.byte	0
	.uleb128 0x14
	.quad	.LBB7
	.quad	.LBE7-.LBB7
	.long	0x35b
	.uleb128 0x11
	.string	"y"
	.byte	0x1
	.byte	0x52
	.long	0x148
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x11
	.string	"x"
	.byte	0x1
	.byte	0x52
	.long	0x148
	.uleb128 0x3
	.byte	0x91
	.sleb128 -68
	.byte	0
	.uleb128 0x14
	.quad	.LBB8
	.quad	.LBE8-.LBB8
	.long	0x37e
	.uleb128 0x11
	.string	"x"
	.byte	0x1
	.byte	0x53
	.long	0x148
	.uleb128 0x3
	.byte	0x91
	.sleb128 -72
	.byte	0
	.uleb128 0x14
	.quad	.LBB9
	.quad	.LBE9-.LBB9
	.long	0x3a1
	.uleb128 0x11
	.string	"x"
	.byte	0x1
	.byte	0x54
	.long	0x148
	.uleb128 0x3
	.byte	0x91
	.sleb128 -76
	.byte	0
	.uleb128 0x13
	.long	.Ldebug_ranges0+0x30
	.long	0x407
	.uleb128 0x11
	.string	"y"
	.byte	0x1
	.byte	0x57
	.long	0x148
	.uleb128 0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0x11
	.string	"x"
	.byte	0x1
	.byte	0x58
	.long	0x148
	.uleb128 0x3
	.byte	0x91
	.sleb128 -84
	.uleb128 0x14
	.quad	.LBB11
	.quad	.LBE11-.LBB11
	.long	0x3e7
	.uleb128 0x11
	.string	"q"
	.byte	0x1
	.byte	0x64
	.long	0x148
	.uleb128 0x3
	.byte	0x91
	.sleb128 -88
	.byte	0
	.uleb128 0x15
	.quad	.LBB12
	.quad	.LBE12-.LBB12
	.uleb128 0x11
	.string	"q"
	.byte	0x1
	.byte	0x69
	.long	0x148
	.uleb128 0x3
	.byte	0x91
	.sleb128 -92
	.byte	0
	.byte	0
	.uleb128 0x14
	.quad	.LBB14
	.quad	.LBE14-.LBB14
	.long	0x437
	.uleb128 0x11
	.string	"y"
	.byte	0x1
	.byte	0x73
	.long	0x148
	.uleb128 0x3
	.byte	0x91
	.sleb128 -96
	.uleb128 0x11
	.string	"x"
	.byte	0x1
	.byte	0x74
	.long	0x148
	.uleb128 0x3
	.byte	0x91
	.sleb128 -100
	.byte	0
	.uleb128 0x14
	.quad	.LBB15
	.quad	.LBE15-.LBB15
	.long	0x45a
	.uleb128 0x11
	.string	"x"
	.byte	0x1
	.byte	0x7b
	.long	0x148
	.uleb128 0x3
	.byte	0x91
	.sleb128 -104
	.byte	0
	.uleb128 0x15
	.quad	.LBB16
	.quad	.LBE16-.LBB16
	.uleb128 0x11
	.string	"i"
	.byte	0x1
	.byte	0x85
	.long	0x3b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.byte	0
	.uleb128 0x16
	.long	.LASF41
	.byte	0x1
	.byte	0xa3
	.long	0x3b
	.quad	.LFB4
	.quad	.LFE4-.LFB4
	.uleb128 0x1
	.byte	0x9c
	.long	0x4a9
	.uleb128 0x17
	.long	.LASF29
	.byte	0x1
	.byte	0xa5
	.long	0x132
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0xe
	.string	"has"
	.byte	0x1
	.byte	0xab
	.long	0x4e5
	.quad	.LFB5
	.quad	.LFE5-.LFB5
	.uleb128 0x1
	.byte	0x9c
	.long	0x4e5
	.uleb128 0xd
	.long	.LASF35
	.byte	0x1
	.byte	0xab
	.long	0x132
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0xf
	.string	"n"
	.byte	0x1
	.byte	0xab
	.long	0x3b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.byte	0
	.uleb128 0x2
	.byte	0x1
	.byte	0x2
	.long	.LASF36
	.uleb128 0x18
	.long	.LASF42
	.byte	0x2
	.byte	0x14
	.long	0x7f
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x4
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x13
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0xa
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x11
	.uleb128 0x1
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.long	0x2c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x8
	.byte	0
	.value	0
	.value	0
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.quad	0
	.quad	0
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.quad	.LBB2-.Ltext0
	.quad	.LBE2-.Ltext0
	.quad	.LBB17-.Ltext0
	.quad	.LBE17-.Ltext0
	.quad	0
	.quad	0
	.quad	.LBB10-.Ltext0
	.quad	.LBE10-.Ltext0
	.quad	.LBB13-.Ltext0
	.quad	.LBE13-.Ltext0
	.quad	0
	.quad	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF30:
	.string	"word"
.LASF18:
	.string	"_IScntrl"
.LASF24:
	.string	"uintptr_t"
.LASF12:
	.string	"_ISdigit"
.LASF8:
	.string	"short int"
.LASF16:
	.string	"_ISgraph"
.LASF15:
	.string	"_ISprint"
.LASF31:
	.string	"push"
.LASF4:
	.string	"unsigned char"
.LASF33:
	.string	"waiting_with_character"
.LASF2:
	.string	"long unsigned int"
.LASF5:
	.string	"short unsigned int"
.LASF42:
	.string	"Assert_Failed"
.LASF38:
	.string	"calc.c"
.LASF11:
	.string	"_ISalpha"
.LASF28:
	.string	"Um_word"
.LASF37:
	.string	"GNU C 4.8.0 -mtune=generic -march=x86-64 -g -std=gnu99"
.LASF41:
	.string	"main"
.LASF27:
	.string	"Seq_T"
.LASF35:
	.string	"sequence"
.LASF6:
	.string	"unsigned int"
.LASF26:
	.string	"long long unsigned int"
.LASF40:
	.string	"reason"
.LASF20:
	.string	"_ISalnum"
.LASF22:
	.string	"int32_t"
.LASF0:
	.string	"sizetype"
.LASF17:
	.string	"_ISblank"
.LASF10:
	.string	"_ISlower"
.LASF25:
	.string	"long long int"
.LASF13:
	.string	"_ISxdigit"
.LASF3:
	.string	"char"
.LASF29:
	.string	"values"
.LASF21:
	.string	"Except_T"
.LASF32:
	.string	"waiting"
.LASF19:
	.string	"_ISpunct"
.LASF34:
	.string	"entering"
.LASF39:
	.string	"/h/jbarth04/Desktop/comp40/hw8"
.LASF14:
	.string	"_ISspace"
.LASF23:
	.string	"uint32_t"
.LASF1:
	.string	"long int"
.LASF7:
	.string	"signed char"
.LASF36:
	.string	"_Bool"
.LASF9:
	.string	"_ISupper"
	.ident	"GCC: (GNU) 4.8.0"
	.section	.note.GNU-stack,"",@progbits
