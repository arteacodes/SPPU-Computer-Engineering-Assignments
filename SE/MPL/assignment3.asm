; program to find max of 5 numbers in array

section .data
str1: db "maximum value is: ", 0xA
len1: equ $-str1

array: db 01h, 1Fh, 12h, 1Ah, 0xF8


section .bss
count: resb 1
result: resb 2


section .text
global _start

_start:
mov byte[count], 04h

mov r8, array  ; set pointer to 1st element of array

mov al, byte[array]  ; store 1st value in accumulator

label1:
inc r8  ; go to next byte for next value

mov bl, byte[r8]  ; store 2nd value in accumulator

cmp al, bl  ; compare values in AL and BL
ja label2  ; if AL>BL skip the move instruction (jump if above)
mov al, bl

label2:
dec byte[count]  ; decrement counter
jnz label1  ; if COUNT!=0 then loop


; max value is now stored in AL
; HEX to ASCII
mov bl, al  ; store max element in BL to manipulate
mov r8, result  ; set pointer to result variable
mov cx, 16h  ; set counter

loop:
rol bl, 4
mov al, bl
and al, 0Fh

cmp al, 09h  ; 0-9 then add 30, A-F then add 37
jbe label3
add al, 07h
label3: add al, 30h

mov byte[r8], al
inc r8
dec cx
jnz loop


; print message 1
mov rax, 1
mov rdi, 1
mov rsi, str1
mov rdx, len1
syscall

mov rax, 1
mov rdi, 1
mov rsi, result
mov rdx, 02h
syscall


; exit
mov rax, 60
mov rdi, 00
syscall
