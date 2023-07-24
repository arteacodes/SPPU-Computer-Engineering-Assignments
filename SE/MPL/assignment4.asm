; program to perform basic arithmetic operations using switch case

; read system call
%macro read 2
mov rax, 00
mov rdi, 00
mov rsi, %1
mov rdx, %2
syscall
%endmacro

; write system call
%macro write 2
mov rax, 01
mov rdi, 01
mov rsi, %1
mov rdx, %2
syscall
%endmacro

section .data
menu db "| 1. Add | 2. Subtract | 3. Multiply | 4. Divide |", 0xA
mlen equ $-menu

str1 db "Enter choice: "
len1 equ $-str1

newline db 0xA
nlen equ $-newline

n1 dq 9h
n2 dq 9h


section .bss
choice resb 1  ; stores the choice
result resb 16


section .text
global _start

_start:

write menu, mlen
write str1, len1
read choice, 1

; switch case
cmp byte[choice], 31h
je l1
cmp byte[choice], 32h
je l2
cmp byte[choice], 33h
je l3
cmp byte[choice], 34h
je l4


l1:
mov rax, qword[n1]
mov rbx, qword[n2]
adc rax, rbx  ; add with carry
call HexToAscii
jmp exit

l2:
mov rax, qword[n1]
mov rbx, qword[n2]
sbb rax, rbx  ; subtract with borrow
call HexToAscii
jmp exit

l3:
xor rdx, rdx  ; clear rdx
mov rax, qword[n1]
mov rbx, qword[n2]
imul rbx  ; rbx gets multiplied with accumulator value
; result stored in 2 registers rdx:rax
push rax
mov rax, rdx
call HexToAscii
pop rax
call HexToAscii
jmp exit

l4:
xor rdx, rdx
mov rax, qword[n1]
mov ebx, dword[n2]
idiv ebx
push rax
mov rax, rdx
call HexToAscii
pop rax
call HexToAscii
jmp exit


exit:
mov rax, 60
mov rdi, 00
syscall

; procedure for hex to ascii conversion 
HexToAscii:
mov r8, result  
mov rcx, 16h

loop:
rol rax, 4
mov rbx, rax
and rbx, 0Fh
cmp rbx, 09h
jbe label
add rbx, 07h

label: add rbx, 30h
mov qword[r8], rbx
inc r8
dec rcx
jnz loop

write result, 16
write newline, nlen
ret  ; procedure ends here
