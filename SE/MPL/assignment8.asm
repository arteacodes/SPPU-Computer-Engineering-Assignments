%macro print 2
mov rax,1
mov rdi,1
mov rsi, %1
mov rdx, %2
syscall
%endmacro


section .data
str1: db 'Before overlapping',0xA
len1 equ $-str1
str2: db 'After overlapping',0xA
len2 equ $-str2

colon: db ':'
count: db 5h
newline: db 0xA
array: dq 000000000000001Ah,000000000000002Bh,000000000000003Ch,000000000000004Dh,0000000000000005Eh,0h,0h,0h,0h,0h
section .bss
ans: resb 16
cnt: resb 2

section .text
global _start
_start:
print str1,len1

mov r9,array
call Display

print newline,1
print str2,len2
br01:
mov rsi,array+32
mov rdi,array+56
mov rcx,05h
STD
REP movsq

mov r9,array+24
call Display


exit:
mov rax,60
mov rdi,00
syscall

HtoA:
mov r8,ans
mov byte[cnt], 16
up:
rol rax,4
mov bl,al
and bl,0Fh

cmp bl,09H
JBE l1
add bl,07H
l1:
add bl,30H
mov byte[r8],bl
inc r8
dec byte[cnt]
JNZ up
print ans,16
RET

Display:
mov   rax   ,   05h
mov  byte[count] , al
label1:
mov rax,r9
call HtoA
print colon,1
mov rax,qword[r9]
call HtoA
print newline,1
add r9,8
dec byte[count]
JNZ label1
RET
