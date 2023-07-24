;===========================================
section .data
;===========================================

msg1: db 0x0A,"Your numnber is  ",0x0A
len1: equ $- msg1


msg2: db 0x0A,"Factorial is  ",0x0A
len2: equ $- msg2

onee:   db 0x0A,"Factorial is 00000001",0x0A
onelen: equ $- onee

count: db 0

enter: db 0x0A




;===========================================
section .bss
;===========================================

num: resb 1
fact: resb 8
temp: resb 1


%macro scall 4
mov rax,%1
mov rdi,%2
mov rsi,%3
mov rdx,%4
syscall
%endmacro







;===========================================
section .text
;===========================================

global _start;
_start:

pop rbx ;POP UNWANTED COMMAND LINE ARGS
pop rbx
pop rbx

mov al,byte[rbx] ;REQUIRED ARGUMENT
mov [num],al

scall 1,1,msg1,len1
scall 1,1,num,1

cmp byte[num],31h
je one
cmp byte[num],30h
je one

mov dl,byte[num]
call A2H


xor rax,rax
xor rbx,rbx
mov al,byte[num]

up1:

push rax ;PREPARING STACK
inc byte[count]
dec rax
cmp rax,1
jne up1

push rax
xor rax,rax

pop rax

facto: ;RECURRSIVE MULTIPLICATION

pop rbx
mul rbx
dec byte[count]
jnz facto

mov qword[fact],rax

scall 1,1,msg2,len2
call H2A

jmp exit

one: ;IF INPUT IS ONE or ZERO

scall 1,1,onee,onelen

jmp exit


A2H: ;ASCII TO HEX

cmp dl,39h
jbe down
sub dl,7h
down:
sub dl,30h
mov [num],dl

ret

H2A: ;HEX TO ASCII

mov rax,[fact]
mov byte[count],8

up:
rol eax,4
mov dl,al
and dl,0Fh
cmp dl,09h
jbe d1
add dl,07h
d1:
add dl,30h
mov [temp],dl
push rax
scall 1,1,temp,1
pop rax
dec byte[count]
jnz up

scall 1,1,enter,1
ret

exit:

mov rax,60
mov rdi,0
syscall

