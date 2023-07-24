; program to find positive and negative numbers from array

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

%macro convert 2                      ; Macro for Hex to ASCII Conversion
cmp byte[%1], 9
jbe next%2
add byte[%1], 07H
next%2:
add byte[%1], 30H
%endmacro

section .data
str1: db "Positive numbers are: "
len1: equ $-str1

str2: db "Negative numbers are: "
len2: equ $-str2

str3: db "  ", 0xA
len3: equ $-str3

pos: db 0h
neg: db 0h
count: db 10

; array of 16 bit positive and negative numbers
array: dq 0x8023451234121619, 0x0214532459658452, 0x1234587965423157,0x8259631478932516, 0x8452136758963250, 0x1254698736521458, 0x6547893256987452, 0x5478963215489632, 0x3256987456321548, 0x8523697412583690
;array: dq -64, -38, -66, -89, -90, -70, 29, 111

section .text
global _start

_start:

mov rsi, array

check:
mov rax, qword[rsi]

; BIT TEST ALGORITHM
BT rax, 63
JC label

; JS ALGO
;ADD rax, 0h
;JS label

; JG ALGO
;CMP rax, 0h
;JG label

inc byte[pos]
add rsi, 8
dec byte[count]
jnz check
jmp htoa

label:
inc byte[neg]
add rsi, 8
dec byte[count]
jnz check

htoa:
convert pos, 1
convert neg, 2

write str1, len1
write pos, 1
write str3, 1
write str2, len2
write neg, 2

exit:
mov rax, 60
mov rdi, 01
syscall
