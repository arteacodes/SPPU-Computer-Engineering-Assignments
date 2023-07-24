%macro print 2
	mov rax,01
	mov rdi,01
	mov rsi,%1
	mov rdx,%2
	syscall
%endmacro

section .data
	msg1 db 10,'Processor is in Real Mode'
	len1:equ $-msg1

	msg2 db 10,'Processor is in Protected Mode'
	len2:equ $-msg2
	
	mswmsg db 10,'Machine Status Word:'
	mmsg_len:equ $-mswmsg

	gdtmsg db 10,'GDT Contents are:'
	gmsg_len:equ $-gdtmsg

	ldtmsg db 10,'LDT Contents are:'
	lmsg_len:equ $-ldtmsg

	idtmsg db 10,'IDT Contents are:'
	imsg_len:equ $-idtmsg

	newline db 10


section .bss
    cr0_data resb 4  ; 32-bit 
    gdtr_data resb 6  ; 48-bit
    ldtr_data resb 2  ; 16-bit
    idtr_data resb 6  ; 48-bit

	result resb 04  ; to store hex to ascii result


section .text
global _start

_start:	
	smsw eax		; read cr0 - 32-bit 
	mov [cr0_data], eax
	bt eax, 0		; check PE bit, if 1=protected mode, else real mode
	jc label1
	print msg1, len1
	jmp label2

label1:
    print msg2, len2

label2:
    ; display msw
    print mswmsg, mmsg_len
	mov bx, [cr0_data+2]
	call print_num
	mov bx, [cr0_data]
	call print_num
	
	; store the contents 
    sgdt [gdtr_data]
	sldt [ldtr_data]
	sidt [idtr_data]
	
	; display gdtr contents
	print gdtmsg, gmsg_len
	mov bx, [gdtr_data+4]
	call print_num
	mov bx, [gdtr_data+2]
	call print_num
	mov bx, [gdtr_data]
	call print_num

    ; display ldtr contents
	print ldtmsg, lmsg_len
	mov bx, [ldtr_data]
	call print_num
    
    ; display idtr contents
	print idtmsg, imsg_len
	mov bx,[idtr_data+4]
	call print_num
	mov bx,[idtr_data+2]
	call print_num
	mov bx,[idtr_data]
	call print_num

	print newline, 1


exit:
    mov rax, 60
	mov rdi, 00
	syscall


print_num:
	mov rsi, result	;point esi to buffer
	mov rcx,04		;load number of digits to printlay 

up1:
	rol bx,4		;rotate number left by four bits
	mov dl,bl		;move lower byte in dl
	and dl,0fh		;mask upper digit of byte in dl
	add dl,30h		;add 30h to calculate ASCII code
	cmp dl,39h		;compare with 39h
	jbe skip1		;if less than 39h skip adding 07 more 
	add dl,07h		;else add 07
skip1:
	mov [rsi],dl	;store ASCII code in buffer
	inc rsi			;point to next byte
	loop up1		;decrement the count of digits to printlay
				    ;if not zero jump to repeat
	print result,4	;printlay the number from buffer
	
	ret
