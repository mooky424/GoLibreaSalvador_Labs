	.file	"Lab5_GoLibreaSalvador.cpp"
	.text
	.globl	_Z12calcDistanceP7Point3DS0_
	.def	_Z12calcDistanceP7Point3DS0_;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z12calcDistanceP7Point3DS0_
_Z12calcDistanceP7Point3DS0_:
.LFB2214:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	%rdx, 24(%rbp)
	movq	16(%rbp), %rax
	movl	(%rax), %ecx
	movq	24(%rbp), %rax
	movl	(%rax), %edx
	movl	%ecx, %eax
	subl	%edx, %eax
	movl	%eax, %edx
	negl	%edx
	cmovns	%edx, %eax
	movl	%eax, %ecx
	movq	16(%rbp), %rax
	movl	4(%rax), %r8d
	movq	24(%rbp), %rax
	movl	4(%rax), %edx
	movl	%r8d, %eax
	subl	%edx, %eax
	movl	%eax, %edx
	negl	%edx
	cmovns	%edx, %eax
	leal	(%rcx,%rax), %r8d
	movq	16(%rbp), %rax
	movl	8(%rax), %ecx
	movq	24(%rbp), %rax
	movl	8(%rax), %edx
	movl	%ecx, %eax
	subl	%edx, %eax
	movl	%eax, %edx
	negl	%edx
	cmovns	%edx, %eax
	addl	%r8d, %eax
	popq	%rbp
	ret
	.seh_endproc
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
.LFB2215:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$72, %rsp
	.seh_stackalloc	72
	leaq	64(%rsp), %rbp
	.seh_setframe	%rbp, 64
	.seh_endprologue
	call	__main
	leaq	-28(%rbp), %rax
	movq	%rax, %rdx
	movq	.refptr._ZSt3cin(%rip), %rax
	movq	%rax, %rcx
	call	_ZNSirsERi
	movl	-28(%rbp), %eax
	testl	%eax, %eax
	jns	.L6
	movl	$-1, %eax
	jmp	.L13
.L12:
	movq	%rsp, %rax
	movq	%rax, %rbx
	leaq	-32(%rbp), %rax
	movq	%rax, %rdx
	movq	.refptr._ZSt3cin(%rip), %rax
	movq	%rax, %rcx
	call	_ZNSirsERi
	movl	-32(%rbp), %eax
	cmpl	$1, %eax
	jg	.L7
	movl	$-2, %eax
	movq	%rbx, %rsp
	jmp	.L13
.L7:
	movl	-32(%rbp), %ecx
	movslq	%ecx, %rax
	subq	$1, %rax
	movq	%rax, -16(%rbp)
	movslq	%ecx, %rax
	movq	%rax, %r8
	movl	$0, %r9d
	movq	%r8, %rax
	movq	%r9, %rdx
	addq	%rax, %rax
	adcq	%rdx, %rdx
	addq	%r8, %rax
	adcq	%r9, %rdx
	shldq	$5, %rax, %rdx
	salq	$5, %rax
	movslq	%ecx, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movslq	%ecx, %rax
	movq	%rax, %r8
	movl	$0, %r9d
	movq	%r8, %rax
	movq	%r9, %rdx
	addq	%rax, %rax
	adcq	%rdx, %rdx
	addq	%r8, %rax
	adcq	%r9, %rdx
	shldq	$5, %rax, %rdx
	salq	$5, %rax
	movslq	%ecx, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	$15, %rax
	shrq	$4, %rax
	salq	$4, %rax
	call	___chkstk_ms
	subq	%rax, %rsp
	leaq	32(%rsp), %rax
	addq	$3, %rax
	shrq	$2, %rax
	salq	$2, %rax
	movq	%rax, -24(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L8
.L9:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	-24(%rbp), %rdx
	addq	%rdx, %rax
	movq	%rax, %rdx
	movq	.refptr._ZSt3cin(%rip), %rax
	movq	%rax, %rcx
	call	_ZNSirsERi
	movq	%rax, %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	-24(%rbp), %rdx
	addq	%rdx, %rax
	addq	$4, %rax
	movq	%rax, %rdx
	call	_ZNSirsERi
	movq	%rax, %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	-24(%rbp), %rdx
	addq	%rdx, %rax
	addq	$8, %rax
	movq	%rax, %rdx
	call	_ZNSirsERi
	addl	$1, -4(%rbp)
.L8:
	movl	-32(%rbp), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L9
	movl	$0, -8(%rbp)
	jmp	.L10
.L11:
	movl	-8(%rbp), %eax
	addl	$1, %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	-24(%rbp), %rdx
	leaq	(%rax,%rdx), %rcx
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	-24(%rbp), %rdx
	addq	%rdx, %rax
	movq	%rcx, %rdx
	movq	%rax, %rcx
	call	_Z12calcDistanceP7Point3DS0_
	movl	%eax, %edx
	movq	.refptr._ZSt4cout(%rip), %rax
	movq	%rax, %rcx
	call	_ZNSolsEi
	movq	%rax, %rcx
	movq	.refptr._ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_(%rip), %rax
	movq	%rax, %rdx
	call	_ZNSolsEPFRSoS_E
	addl	$1, -8(%rbp)
.L10:
	movl	-32(%rbp), %eax
	subl	$1, %eax
	cmpl	%eax, -8(%rbp)
	jl	.L11
	movq	%rbx, %rsp
.L6:
	movl	-28(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, -28(%rbp)
	testl	%eax, %eax
	setne	%al
	testb	%al, %al
	jne	.L12
	movl	$0, %eax
.L13:
	leaq	8(%rbp), %rsp
	popq	%rbx
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
_ZNSt8__detail30__integer_to_chars_is_unsignedIjEE:
	.byte	1
_ZNSt8__detail30__integer_to_chars_is_unsignedImEE:
	.byte	1
_ZNSt8__detail30__integer_to_chars_is_unsignedIyEE:
	.byte	1
	.def	__main;	.scl	2;	.type	32;	.endef
	.ident	"GCC: (Rev2, Built by MSYS2 project) 14.2.0"
	.def	_ZNSirsERi;	.scl	2;	.type	32;	.endef
	.def	_ZNSolsEi;	.scl	2;	.type	32;	.endef
	.def	_ZNSolsEPFRSoS_E;	.scl	2;	.type	32;	.endef
	.section	.rdata$.refptr._ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, "dr"
	.globl	.refptr._ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	.linkonce	discard
.refptr._ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_:
	.quad	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	.section	.rdata$.refptr._ZSt4cout, "dr"
	.globl	.refptr._ZSt4cout
	.linkonce	discard
.refptr._ZSt4cout:
	.quad	_ZSt4cout
	.section	.rdata$.refptr._ZSt3cin, "dr"
	.globl	.refptr._ZSt3cin
	.linkonce	discard
.refptr._ZSt3cin:
	.quad	_ZSt3cin
