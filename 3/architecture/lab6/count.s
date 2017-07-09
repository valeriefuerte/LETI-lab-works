.intel_syntax noprefix
.global _count

_count:
	mov r10, [rsp+40]
	# rcx: int64_t  NumRanDat
	# rdx: int64_t* RanDat
	# r8:  int64_t  NInt
	# r9:  int64_t* LGrInt
	# r10: int64_t* Freqs

	sub rcx, 1
	numloop:
		cmp rcx, 0
		jl numloopend
		#   rax: i(NInt)
		mov rax, r8
		sub rax, 1
		#   r11: RanDat[NumRanDat]
		mov r11, [rdx+8*rcx]
		grloop:
			#        LGrInt[i]
			cmp r11, [r9+8*rax]
			jl nextgr
			#         Freqs[i]
			add qword ptr [r10+8*rax], 1
			jmp grloopend
			nextgr:
			sub rax, 1
			jmp grloop
		grloopend:
		sub rcx, 1
		jmp numloop
	numloopend:
	ret
