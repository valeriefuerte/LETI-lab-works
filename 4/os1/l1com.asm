title       Программа типа .COM

codesg      segment   para   'code'
            assume cs:codesg,ds:codesg,ss:codesg
            org     100h
begin:      jmp    main

;-------------------------------------------------
mes 		db 'Start com ',10,13,'$'
strFF 		db 'PC type: PS',10,13,'$'
strFEorFB 	db 'PC type: PS/XT',10,13,'$'
strFA 		db 'PC type: PS2 model 30',10,13,'$'
strFC 		db 'PC type: PS2 model 50 or 60',10,13,'$'
strF8 		db 'PC type: PS2 model 80',10,13,'$'
strFD 		db 'PC type: PCjr',10,13,'$'
strF9 		db 'PC type: PC Convertible',10,13,'$'
default 	db 'PC type: $'
meslen 	equ $-mes
;--- Хранение версии MS DOS
NumberVersion   db ?
NumberModif     db ?
NumberBL        db ?
NumberBH        db ?
NumberCX        dw ?
OS 		db 'OS version: $'
MODIF		db 'Modification number: $'
OEM		db 'Original Equipment Manufacturer (OEM): $'
SER		db 'Serial number user: $'
strNumber	db 2 dup(' '),10,13,'$' ; Номер версии
strNumberModif	db 2 dup(' '),10,13,'$' ; Номер модификации
strNumberBH	db 3 dup(' '),10,13,'$' ; Серийный номер OEM
strNumberBL	db 2 dup(' '),'$' ; Номер пользователя
strNumberCX	db 4 dup(' '),'$' 
strNumberType	db 4 dup(' '),10,13,'$'
;-------------------------------------------------
main        proc   near

            ;push    ax
            ;mov     ax,codesg
            ;mov     ds,ax
            
; Выведем строку текста
		mov AH,09h
		mov DX,offset mes
		mov CX,meslen
		int 21h

;--- Определение типа компьютера:

   MOV  AX,0F000H           ;указывает ES на ПЗУ
   MOV  ES,AX               ;
   MOV  AL,ES:[0FFFEH]      ;получаем байт

   CMP  AL,0FFH             ;это PS
   JE   INITIALIZE_FF       ;переходим на инициализацию
   CMP  AL,0FEH             
   JE   INITIALIZE_FEorFB       
   CMP  AL,0FBH             
   JE   INITIALIZE_FEorFB
   CMP  AL,0FAH             
   JE   INITIALIZE_FA
   CMP  AL,0FCH             
   JE   INITIALIZE_FC
   CMP  AL,0F8H              
   JE   INITIALIZE_F8
   CMP  AL,0FDH             
   JE   INITIALIZE_FD
   CMP  AL,0F9H              
   JE   INITIALIZE_F9
; Если код не определен, вывод кода       
	LEA DI, strNumberType+3
   	XOR AH,AH 	
   	CALL WRD_TO_HEX
	mov DX,offset default
	mov AH,09h
   	int 21h
   LEA DX,strNumberType
   jmp print

INITIALIZE_FF:	mov DX,offset strFF
		jmp print
INITIALIZE_FEorFB:mov DX,offset strFEorFB
		jmp print
INITIALIZE_FA:	mov DX,offset strFA
		jmp print
INITIALIZE_FC:	mov DX,offset strFC
		jmp print
INITIALIZE_F8:	mov DX,offset strF8
		jmp print
INITIALIZE_FD:  mov DX,offset strFD
		jmp print
INITIALIZE_F9:	mov DX,offset strF9
		
print:
; Выведем строку текста - тип IBM PC
	mov AH,09h
	int 21h

;--- Определение версии MS DOS:
   MOV   AH,30H            ;номер функции получения версии
   INT   21H               ;получить номер версии
   MOV 	 NumberVersion,AL
   MOV   NumberModif,AH
   MOV   NumberBH,BH
   MOV   NumberBL,BL
   MOV   NumberCX,CX

;--- Вывод версии MS DOS
	mov AH,09h
	lea DX,OS
	int 21h
	MOV AL,NumberVersion
	LEA SI, strNumber	
	CALL BYTE_TO_DEC
   	LEA DX,strNumber
   	mov AH,09h
   	int 21h

;--- Вывод номера модификации MS DOS
   	mov AH,09h
	lea DX,MODIF
	int 21h
   LEA SI, strNumberModif
   MOV AL,NumberModif	
   CALL BYTE_TO_DEC
   LEA DX,strNumberModif
   mov AH,09h
   int 21h

;--- Вывод номера OEM
   	mov AH,09h
	lea DX,OEM
	int 21h
   LEA SI, strNumberBH+2
   MOV AL,NumberBH	
   CALL BYTE_TO_DEC
   LEA DX,strNumberBH
   mov AH,09h
   int 21h
;--- Вывод номера пользователя
   	mov AH,09h
	lea DX,SER
	int 21h
   
   LEA DI, strNumberBL+1
   XOR AH,AH 	
   MOV AL,NumberBL
   CALL WRD_TO_HEX
   LEA DX,strNumberBL
   mov AH,09h
   int 21h
   
   LEA DI, strNumberCX+3
   MOV AX,NumberCX	
   CALL WRD_TO_HEX
   LEA DX,strNumberCX
   mov AH,09h
   int 21h

;Завершим программу
		mov AX,4C00h
		int 21h
            	
main        endp

TETR_TO_HEX PROC near
and AL,0Fh
cmp AL,09
jbe NEXT
add AL,07
NEXT: add AL,30h
ret
TETR_TO_HEX ENDP
;-------------------------------
BYTE_TO_HEX PROC near
; байт в AL переводится в шестнадцатеричное число AX
push CX
mov AH,AL
call TETR_TO_HEX
xchg AL,AH
mov CL,4
shr AL,CL
call TETR_TO_HEX ;? AL ????&?? ?????
pop CX ;? AH ????&??
ret
BYTE_TO_HEX ENDP
;-------------------------------
WRD_TO_HEX PROC near
;  AX - , DI - 
push BX
mov BH,AH
call BYTE_TO_HEX
mov [DI],AH
dec DI
mov [DI],AL
dec DI
mov AL,BH
call BYTE_TO_HEX
mov [DI],AH
dec DI
mov [DI],AL
pop BX
ret
WRD_TO_HEX ENDP
;--------------------------------------------------
BYTE_TO_DEC PROC near
; AL , SI - 
push CX
push DX
xor AH,AH
xor DX,DX
mov CX,10
loop_bd: div CX
or DL,30h
mov [SI],DL
dec SI
xor DX,DX
cmp AX,10
jae loop_bd
cmp AL,00h
je end_l
or AL,30h
mov [SI],AL
end_l: pop DX
pop CX
ret
BYTE_TO_DEC ENDP
;-------------------------------
; 


codesg      ends
            end    begin
