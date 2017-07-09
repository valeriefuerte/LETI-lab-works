DOSSEG                                      
   .MODEL  SMALL                              
   .STACK  100h                               
   .DATA 
                                      
		KEEP_CS DW 0 ; для хранения сегмента
		KEEP_IP DW 0 ; и смещения прерывания

		Greeting DB 'Hello. Interruption is actuated.',13,10,'$'
   

.CODE
begin:                               
   mov  bx,@data                        
   mov  ds,bx                           
   
	MOV AH, 35H ; функция получения вектора
	MOV AL, 60H ; номер вектора
	INT 21H
	MOV KEEP_IP, BX ; запоминание смещения
	MOV KEEP_CS, ES ; и сегмента


	PUSH DS
	MOV DX, OFFSET ROUT ; смещение для процедуры в DX
	MOV AX, SEG ROUT ; сегмент процедуры
	MOV DS, AX ; помещаем в DS
	MOV AH, 25H ; функция установки вектора
	MOV AL, 60H ; номер вектора
	INT 21H ; меняем прерывание
	POP DS

	int 60h

	CLI
	PUSH DS
	MOV DX, KEEP_IP
	MOV AX, KEEP_CS
	MOV DS, AX
	MOV AH, 25H
	MOV AL, 60H
	INT 21H ; восстанавливаем вектор
	POP DS
	STI

	mov  ah,4ch                         
	int  21h                             

	ROUT proc far ;начало процедуры
  		push ax ;сохраняем все изменяемые регистры
  		push dx ;сохраняем все изменяемые регистры
 
  		mov ah,9h ;функция установки вектора
  		mov dx,offset Greeting ;в dx загружаем адрес сообщения
  		int 21h ;вывод строки на экран
  
  		pop dx ;восстанавливаем регистры
  		pop ax ;восстанавливаем регистры
  		ret
	ROUT endp

END begin