; program to read 5 numbers from user and print them

section .data
str1: db "enter 5 numbers: "
len1 equ $-str1

str2: db "5 numbers are: ", 0xA
len2 equ $-str2


section .bss
array resq 85
count resb 1


section .text
global _start

_start:
mov r8, array
mov byte[count], 05h

mov rax, 01
mov rdi, 01
mov rsi, str1
mov rdx, len1
syscall

;read the 5 numbers
label1:
mov rax, 00
mov rdi, 00
mov rsi, r8
mov rdx, 17     ; 16 characters and +1 for ENTER key
syscall

add r8, 17      ; shift r8 pointer by 17 bytes
dec byte[count]     ; decrement counter by 1
jnz label1

mov rax, 01
mov rdi, 01
mov rsi, str2
mov rdx, len2
syscall

; reset pointer and counter
mov r8, array
mov byte[count], 05h

; display the 5 numbers
label2:
mov rax, 01
mov rdi, 01
mov rsi, r8
mov rdx, 17
syscall

add r8, 17
dec byte[count]
jnz label2

mov rax, 60
mov rdi, 00
syscall


