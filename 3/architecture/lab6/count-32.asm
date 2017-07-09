global _count

_count:
	; int32_t  NumRanDat	[ebp+8]
	; int32_t* RanDat 		[ebp+12]
	; int32_t  NInt			[ebp+16]
	; int32_t* LGrInt		[ebp+20]
	; int32_t* Freqs		[ebp+24]
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
		;   eax: i(NInt)
		mov eax, [ebp+16]
		inc eax
		;   edx: RanDat[NumRanDat]
		mov edx, [ebp+12]
		mov edx, [edx+4*ecx]
		grloop:
			;        LGrInt[i]
			mov ebx, [ebp+20]
			mov ebx, [ebx+4*eax]
			cmp edx, ebx
			jl nextgr
			;         Freqs[i]
			mov ebx, [ebp+24]
			inc dword [ebx+4*eax]
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
