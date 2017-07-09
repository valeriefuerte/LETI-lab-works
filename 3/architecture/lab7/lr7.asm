AStack SEGMENT STACK
    DB 1024 DUP(?)
AStack ENDS

DATA SEGMENT
    StartStr DB "+...........","$"
    FinalStr DB "+00000000000","$"
DATA ENDS

CODE SEGMENT
    ASSUME SS:AStack, DS:DATA, CS:CODE


NumStr PROC FAR ;число из стека 4 байта, начиная с bp+8, кодирует в строку в 8ричном формате
    push bp
    mov bp, sp
    push di
    push ax
    push bx
    push cx
    push dx

    mov di, [bp+6];адрес строки
    mov dx, [bp+8] ;число, которое нужнозакодировать
    mov ax, [bp+10]

    cmp dx, 0 
    jge sign
    mov bl, '-'
    neg ax
    adc dx, 0 ;число "нормально перешло " в дополнительный код
    neg dx

    jmp aftersign

sign: ;если >=0
    mov bl, '+'

aftersign: 
    mov [di], bl ;к строке приписываем "+" или "-"

    add di, 11 ;записываем в строку с конца
    mov cx, 11
followingnumber:
    mov bl, al ;записываем начало числа (ax=al+ah)
    and bl, 0111b ;берем 3 младших бита числа
    add bl, 48 ;переходим к закодированным числовым символам
    mov [di], bl ;запишем получившуюся цифру в строку результата
    dec di ;подвинули указатель на строку
    ; shrd ax, dx, 3 - masm про такое не знает - ниже велосипед из костылей
    shr ax, 1 ;сдвигаем число вправо на 3
    shr ax, 1
    shr ax, 1
    mov bx, dx
    and bx, 0111b
    ror bx, 1
    ror bx, 1
    ror bx, 1
    shr dx, 1
    shr dx, 1
    shr dx, 1
    add ax, bx
    loop followingnumber

numend:
    pop dx
    pop cx
    pop bx
    pop ax
    pop di
    pop bp
    ret 6
NumStr ENDP


StrNum PROC FAR ;процедура декодирования строки обратно в число
    push bp
    mov bp, sp
    push si
    push ax
    push bx
    push cx
    push dx

    mov ax, 0
    mov dx, 0
    mov si, [bp+6]
    mov cx, 11 

followingchar:
    ; shld ax, dx, 3
    shl dx, 1
    shl dx, 1
    shl dx, 1
    mov bx, ax
    and bx, 01110000000000000b
    rol bx, 1
    rol bx, 1
    rol bx, 1
    shl ax, 1
    shl ax, 1
    shl ax, 1
    add dx, bx

    add si, 1
    mov bl, [si]
    sub bl, 48
    add al, bl
    loop followingchar

    sub si, 11
    mov bl, [si]
    cmp bl, '+'
    je charend
    neg ax
    adc dx, 0
    neg dx

charend:
    mov [bp+8], dx
    mov [bp+10], ax
    pop dx
    pop cx
    pop bx
    pop ax
    pop si
    pop bp
    ret 2
StrNum ENDP


Main PROC FAR
    push ds
    sub ax, ax
    push ax
    mov ax, data
    mov ds, ax

    push ax ;кодируем число из ax,dx в строку
    push dx
    mov bx, OFFSET StartStr
    push bx
    call NumStr

    sub sp, 4 ;выделяем 4 байта из стека
    mov bx, OFFSET FinalStr
    push bx
    call StrNum
    pop dx
    pop ax

    mov dx, OFFSET StartStr
    mov ah, 9
    int 21h

    ret
Main ENDP
CODE ENDS
END Main
