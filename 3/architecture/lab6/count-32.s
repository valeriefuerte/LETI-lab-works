.intel_syntax noprefix

.global _first
# void first(int NumRanDat, int* RanDat, int Xmin, int* fInt);
_first:
	push ebp
	mov ebp, esp
	push eax
	push ebx
	push ecx
	push esi
	push edi

	mov ecx, [ebp+8]  	#NumRanDat
	mov esi, [ebp+12]	#Randat
	mov edi, [ebp+20]	#Xmin

	cycle:
	cmp ecx, 0
	je exit
	dec ecx 		
	mov eax, [esi+ecx*4]	#от RanDat-1 до 0. БЫЛА ОШИБКА *2. ПРОГРАММА НЕКОРРЕКТНО ЗАВЕРШИЛА РАБОТУ
	sub eax, [ebp+16]
	inc dword ptr [edi+eax*4]
	jmp cycle

	exit:
	pop edi
	pop esi
	pop ecx
	pop ebx
	pop eax
	pop ebp
	ret

.global _second
#void second(int* LGrInt, int NInt, int* fInt, int fIntSize, int Xmax, int* Freqs);
_second:
	push ebp
	mov ebp, esp
	sub esp, 8
	push eax
	push ebx
	push ecx
	push edx
	push esi
	push edi

	mov eax, [ebp+24]	#Xmax
	mov [ebp-4], eax	#local varuable (текущее число, которое мы проверяем на принадлежность интервалу)

	mov esi, [ebp+16] # fInt
	mov edi, [ebp+8]  # LgrInt
	mov ebx, [ebp+12] # Nint
	mov edx, [ebp+20] # fIntSize
	dec edx

	checklgrint:
	dec ebx
	cmp ebx, 0
	jl exits
	mov eax, [edi+ebx*4]	
	mov [ebp-8], eax 	#local varuable2

	addint:
	mov eax, [ebp-4] 
	cmp eax, [ebp-8] #сравниваем единичный интервал с текущей левой границей
	je checklgrint #если левее, то берем следующую левую границу

	mov ecx, [esi+edx*4] #кол-во чисел на единичном интервале
	mov eax, [ebp+28] 
	add [eax+ebx*4], ecx #к результату на промежутке прибавляем кол-во на каждом единичном интервале

	dec dword ptr [ebp-4] #переход к следующему числу
	dec edx
	jmp addint

	exits:

	pop edi
	pop esi
	pop edx
	pop ecx
	pop ebx
	pop eax
	add esp, 8
	pop ebp
	ret

.global _numCatch
_numCatch:
	# int32_t  NumRanDat	[ebp+8]
	# int32_t* RanDat 		[ebp+12]
	# int32_t  NInt			[ebp+16]
	# int32_t* LGrInt		[ebp+20]
	# int32_t* Freqs		[ebp+24]
	push ebp
	mov ebp, esp
	push eax
	push ebx
	push ecx
	push edx

	mov ecx, [ebp+8]
	dec ecx
	numloop:
		cmp ecx, 0
		jl numloopend
		#   eax: i(NInt)
		mov eax, [ebp+16]
	    dec eax
		#   edx: RanDat[NumRanDat]
		mov edx, [ebp+12]
		mov edx, [edx+4*ecx]
		grloop:
			#        LGrInt[i]
			mov ebx, [ebp+20]
			mov ebx, [ebx+4*eax]
			cmp edx, ebx
			jl nextgr
			#         Freqs[i]
			mov ebx, [ebp+24]
			inc dword ptr [ebx+4*eax]
			jmp grloopend
			nextgr:
			dec eax
			jmp grloop
		grloopend:
		dec ecx
		jmp numloop
	numloopend:

	pop edx
	pop ecx
	pop ebx
	pop eax
	pop ebp
	ret
