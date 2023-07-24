; program to find length of input string

section .data
str1: db "enter a string: "
len1 equ $-str1

str2: db "length of string is: "
len2 equ $-str2


section .bss
instr: resb 30
result: resb 16


section .text
global _start

_start:

; print enter message
mov rax, 1
mov rdi, 1
mov rsi, str1
mov rdx, len1
syscall

; read user string
mov rax, 0
mov rdi, 0
mov rsi, instr
mov rdx, 30
syscall

; rax stores length of value read right after the read call
dec rax    ; remove null character i.e. ENTER.
mov rbx, rax
mov rdi, result  ; set pointer to result variable (initially empty)
mov cx, 16h  ; set counter to 16

loop:
rol rbx, 4  ; swap the digits by rotating bits
mov al, bl  ; move lower 8 bits to AL
and al, 0fh  ; get LSB
cmp al, 09h  ; compare LSB with 9
jg l1  ; check if greater
add al, 30h  ; add 30 if false
jmp l2  ; skip 'ADD 37'

l1:
add al, 37h  ; add 37 if true

l2:
mov [rdi], al  ; store the value in result
inc rdi  ; set pointer to next byte
dec cx  ; decrease counter by 1
jnz loop  ; loop until counter=0

; print length message
mov rax, 1
mov rdi, 1
mov rsi, str2
mov rdx, len2
syscall

; print length of string
mov rax, 1
mov rdi, 1
mov rsi, result
mov rdx, 16
syscall

; exit
mov rax, 60
mov rdi, 00
syscall
