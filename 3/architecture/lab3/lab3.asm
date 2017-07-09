AStack SEGMENT STACK
    DW 12 DUP(?)
AStack ENDS


DATA SEGMENT

a DW 1
b DW 2
i DW 3
k DW 4

i1 DW 0
i2 DW 0
res DW 0

DATA ENDS


CODE SEGMENT
     ASSUME CS:CODE, DS:DATA, SS:AStack


Main PROC FAR
    push ds
    xor ax, ax
    push ax

    mov ax, DATA
    mov ds,ax

    mov ax, a


; F1
    ; si = i
    ; di = 2i
    mov si, i
    mov di, si
    shl di, 1

    cmp ax, b
    jg F3_L
    ; a <= b

    ; cx = 3i
    add di, si
    mov cx, di

    add cx, 4
    jmp F1_STO
    
F3_L:
    ; a > b

    mov cx, 15
    sub cx, di
    
F1_STO:
    ; store result
    mov i1, cx


; F5
    ; di *= 2
    sal di, 1
    ; di = -di
    neg di

    cmp ax, b
    jg F5_L
    ; a <= b
    add di, 6

    jmp F5_STO

F5_L:
    ; a > b
    add di, 20

F5_STO:
    ; store result
    mov i2, di


; F4
    ; ax = -i2 
    xor ax, ax
    sub ax, i2

    cmp k, 0
    jge F4_L
    ; k < 0
        ; ax = i1 - i2
        add ax, i1

        ; ax = |i1 - i2|
        cmp ax, 0
        jg MODULO_END
        neg ax
    MODULO_END:

        ; min

        cmp ax, 2
        ; min = ax
        jl F4_STO

        mov ax, 2
        ; min = 2
        jmp F4_STO 

F4_L:      
    ; else 
    ; k >= 0
        cmp ax, -6
        ; max = ax
        jg F4_STO
        ; max = -6
        mov ax, -6

F4_STO:
    mov res, ax

    ret 2
Main ENDP
CODE ENDS

END Main
