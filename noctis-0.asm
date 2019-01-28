	.386p
	ifndef	??version
?debug	macro
	endm
publicdll macro	name
	public	name
	endm
$comm	macro	name,dist,size,count
	comm	dist name:BYTE:count*size
	endm
	else
$comm	macro	name,dist,size,count
	comm	dist name[size]:BYTE:count
	endm
	endif
	?debug	V 301h
	?debug	S "src/noctis-0.cpp"
	?debug	C E96BAF2A4E107372632F6E6F637469732D302E637070
	?debug	C E96BAF2A4E0E5352432F6E6F637469732D642E68
	?debug	C E94020792217433A5C4243355C494E434C5544455C7374646C6962+
	?debug	C 2E68
	?debug	C E94020792216433A5C4243355C494E434C5544455C5F646566732E+
	?debug	C 68
	?debug	C E94020792216433A5C4243355C494E434C5544455C5F6E756C6C2E+
	?debug	C 68
	?debug	C E94020792216433A5C4243355C494E434C5544455C737464696F2E+
	?debug	C 68
	?debug	C E94020792217433A5C4243355C494E434C5544455C5F6E66696C65+
	?debug	C 2E68
	?debug	C E94020792216433A5C4243355C494E434C5544455C636F6E696F2E+
	?debug	C 68
	?debug	C E94020792217433A5C4243355C494E434C5544455C737472696E67+
	?debug	C 2E68
	?debug	C E94020792217433A5C4243355C494E434C5544455C737464646566+
	?debug	C 2E68
	?debug	C E94020792216433A5C4243355C494E434C5544455C616C6C6F632E+
	?debug	C 68
	?debug	C E94020792216433A5C4243355C494E434C5544455C737464696F2E+
	?debug	C 68
	?debug	C E94020792215433A5C4243355C494E434C5544455C74696D652E68
	?debug	C E94020792215433A5C4243355C494E434C5544455C6D6174682E68
	?debug	C E94020792214433A5C4243355C494E434C5544455C646F732E68
	?debug	C E94020792213433A5C4243355C494E434C5544455C696F2E68
	?debug	C E96BAF2A4E0E5352432F41534D4861636B732E68
	?debug	C E96BAF2A4E0E5352432F6E6F637469732D642E68
NOCTIS-0_TEXT	segment byte public use16 'CODE'
NOCTIS-0_TEXT	ends
DGROUP	group	_DATA,_BSS
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
_DATA	segment word public use16 'DATA'
d@	label	byte
d@w	label	word
_DATA	ends
_BSS	segment word public use16 'BSS'
b@	label	byte
b@w	label	word
_BSS	ends
NOCTIS-0_TEXT	segment byte public use16 'CODE'
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@carryAddMultiply$qll	proc	far
	push	bp
	mov	bp,sp
	sub	sp,4
	push	si
	push	di
	pusha	
	db	 066H
	mov	 dx, word ptr [bp+6]
	db	 066H
	mov	 ax, word ptr [bp+10]
	db	 066H
	imul	 dx
	db	 066H
	add	 dx, ax
	db	 066H
	mov	 word ptr [bp-4], dx
	popa	
	mov	dx,word ptr [bp-2]
	mov	ax,word ptr [bp-4]
	pop	di
	pop	si
	leave	
	ret	
@carryAddMultiply$qll	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@shiftSegment$qnuci	proc	far
	push	bp
	mov	bp,sp
	sub	sp,4
	push	si
	push	di
	mov	eax,dword ptr [bp+6]
	mov	dword ptr [bp-4],eax
	movsx	eax,word ptr [bp+10]
	shl	eax,16
	add	dword ptr [bp-4],eax
	mov	dx,word ptr [bp-2]
	mov	ax,word ptr [bp-4]
	pop	di
	pop	si
	leave	
	ret	
@shiftSegment$qnuci	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@clearOffset$qnuc	proc	far
	push	bp
	mov	bp,sp
	sub	sp,4
	push	si
	push	di
	mov	eax,dword ptr [bp+6]
	mov	dword ptr [bp-4],eax
	and	dword ptr [bp-4],large 0FFFF0000h
	mov	dx,word ptr [bp-2]
	mov	ax,word ptr [bp-4]
	pop	di
	pop	si
	leave	
	ret	
@clearOffset$qnuc	endp
NOCTIS-0_TEXT	ends
_DATA	segment word public use16 'DATA'
_QUADWORDS	label	word
	db	128
	db	62
_adaptor	label	dword
	db	0
	db	0
	db	0
	db	160
_adapted	label	dword
	db	0
	db	0
	db	0
	db	176
_DATA	ends
_BSS	segment word public use16 'BSS'
_tmppal	label	byte
	db	768 dup (?)
_return_palette	label	byte
	db	768 dup (?)
_surface_palette	label	byte
	db	768 dup (?)
_BSS	ends
NOCTIS-0_TEXT	segment byte public use16 'CODE'
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@lstri$qnc	proc	far
	push	bp
	mov	bp,sp
	push	si
	push	di
	xor	dx,dx
@4@2:
	les	bx,dword ptr [bp+6]
	add	bx,dx
	mov	ax,bx
	cmp	byte ptr es:[bx],0
	je	short @4@4
	mov	al,byte ptr es:[bx]
	mov	bx,dx
	mov	byte ptr DGROUP:_tmppal[bx],al
	jmp	short @4@6
@4@4:
	mov	bx,dx
	mov	byte ptr DGROUP:_tmppal[bx],0
	mov	ax,dx
	jmp	short @4@9
@4@6:
	inc	dx
	cmp	dx,768
	jl	short @4@2
	xor	ax,ax
@4@9:
	pop	di
	pop	si
	pop	bp
	ret	
@lstri$qnc	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@reach_your_dir$qv	proc	far
	push	bp
	mov	bp,sp
	sub	sp,16
	push	si
	push	di
	les	bx,dword ptr DGROUP:__argv
	push	dword ptr es:[bx]
	push	cs
	call	near ptr @lstri$qnc
	add	sp,4
	dec	ax
	mov	dx,ax
	jmp	short @5@3
@5@2:
	dec	dx
@5@3:
	or	dx,dx
	jl	short @5@5
	mov	bx,dx
	cmp	byte ptr DGROUP:_tmppal[bx],92
	jne	short @5@2
@5@5:
	or	dx,dx
	jl	short @5@9
	mov	bx,dx
	cmp	byte ptr DGROUP:_tmppal[bx-1],58
	je	short @5@8
	mov	byte ptr DGROUP:_tmppal[bx],0
	jmp	short @5@9
@5@8:
	mov	bx,dx
	mov	byte ptr DGROUP:_tmppal[bx+1],0
@5@9:
	les	bx,dword ptr DGROUP:__argv
	les	bx,dword ptr es:[bx]
	mov	al,byte ptr es:[bx]
	cbw	
	cmp	ax,97
	jl	short @5@12
	les	bx,dword ptr DGROUP:__argv
	les	bx,dword ptr es:[bx]
	mov	al,byte ptr es:[bx]
	cbw	
	cmp	ax,122
	jg	short @5@12
	les	bx,dword ptr DGROUP:__argv
	les	bx,dword ptr es:[bx]
	mov	dl,byte ptr es:[bx]
	add	dl,159
	jmp	short @5@13
@5@12:
	les	bx,dword ptr DGROUP:__argv
	les	bx,dword ptr es:[bx]
	mov	dl,byte ptr es:[bx]
	add	dl,191
@5@13:
	mov	byte ptr [bp-15],14
	mov	byte ptr [bp-10],dl
	push	ss
	lea	ax,word ptr [bp-16]
	push	ax
	push	ss
	push	ax
	call	far ptr _intdos
	add	sp,8
	mov	byte ptr [bp-15],59
	mov	al,byte ptr DGROUP:_tmppal
	mov	ah,0
	mov	word ptr [bp-10],ax
	push	ss
	lea	ax,word ptr [bp-16]
	push	ax
	push	ss
	push	ax
	call	far ptr _intdos
	add	sp,8
	pop	di
	pop	si
	leave	
	ret	
@reach_your_dir$qv	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@_320_200_256$qv	proc	far
	push	bp
	mov	bp,sp
	sub	sp,16
	push	si
	push	di
	mov	word ptr [bp-16],19
	push	ss
	lea	ax,word ptr [bp-16]
	push	ax
	push	ss
	push	ax
	push	16
	call	far ptr _int86
	add	sp,10
	pop	di
	pop	si
	leave	
	ret	
@_320_200_256$qv	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@_80_25_C$qv	proc	far
	push	bp
	mov	bp,sp
	sub	sp,16
	push	si
	push	di
	mov	word ptr [bp-16],3
	push	ss
	lea	ax,word ptr [bp-16]
	push	ax
	push	ss
	push	ax
	push	16
	call	far ptr _int86
	add	sp,10
	pop	di
	pop	si
	leave	
	ret	
@_80_25_C$qv	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@attendi_pressione_tasto$qv	proc	far
	push	bp
	mov	bp,sp
	sub	sp,16
	push	si
	push	di
	mov	byte ptr [bp-15],8
	push	ss
	lea	ax,word ptr [bp-16]
	push	ax
	push	ss
	push	ax
	call	far ptr _intdos
	add	sp,8
	mov	al,byte ptr [bp-16]
	mov	ah,0
	pop	di
	pop	si
	leave	
	ret	
@attendi_pressione_tasto$qv	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@tasto_premuto$qv	proc	far
	push	bp
	mov	bp,sp
	sub	sp,16
	push	si
	push	di
	mov	byte ptr [bp-15],11
	push	ss
	lea	ax,word ptr [bp-16]
	push	ax
	push	ss
	push	ax
	call	far ptr _intdos
	add	sp,8
	cmp	byte ptr [bp-16],255
	jne	short @9@3
	mov	ax,1
	jmp	short @9@4
@9@3:
	xor	ax,ax
@9@4:
	pop	di
	pop	si
	leave	
	ret	
@tasto_premuto$qv	endp
NOCTIS-0_TEXT	ends
_DATA	segment word public use16 'DATA'
_range8088	label	byte
	db	0
	db	0
	db	0
	db	1
	db	1
	db	1
	db	2
	db	2
	db	2
	db	3
	db	3
	db	3
	db	4
	db	4
	db	4
	db	5
	db	5
	db	5
	db	6
	db	6
	db	6
	db	7
	db	7
	db	7
	db	8
	db	8
	db	8
	db	9
	db	9
	db	9
	db	10
	db	10
	db	10
	db	11
	db	11
	db	11
	db	12
	db	12
	db	12
	db	13
	db	13
	db	13
	db	14
	db	14
	db	14
	db	15
	db	15
	db	15
	db	16
	db	16
	db	16
	db	17
	db	17
	db	17
	db	18
	db	18
	db	18
	db	19
	db	19
	db	19
	db	20
	db	20
	db	20
	db	21
	db	21
	db	21
	db	22
	db	22
	db	22
	db	23
	db	23
	db	23
	db	24
	db	24
	db	24
	db	25
	db	25
	db	25
	db	26
	db	26
	db	26
	db	27
	db	27
	db	27
	db	28
	db	28
	db	28
	db	29
	db	29
	db	29
	db	30
	db	30
	db	30
	db	31
	db	31
	db	31
	db	32
	db	32
	db	32
	db	33
	db	33
	db	33
	db	34
	db	34
	db	34
	db	35
	db	35
	db	35
	db	36
	db	36
	db	36
	db	37
	db	37
	db	37
	db	38
	db	38
	db	38
	db	39
	db	39
	db	39
	db	40
	db	40
	db	40
	db	41
	db	41
	db	41
	db	42
	db	42
	db	42
	db	43
	db	43
	db	43
	db	44
	db	44
	db	44
	db	45
	db	45
	db	45
	db	46
	db	46
	db	46
	db	47
	db	47
	db	47
	db	48
	db	48
	db	48
	db	49
	db	49
	db	49
	db	50
	db	50
	db	50
	db	51
	db	51
	db	51
	db	52
	db	52
	db	52
	db	53
	db	53
	db	53
	db	54
	db	54
	db	54
	db	55
	db	55
	db	55
	db	56
	db	56
	db	56
	db	57
	db	57
	db	57
	db	58
	db	58
	db	58
	db	59
	db	59
	db	59
	db	60
	db	60
	db	60
	db	61
	db	61
	db	61
	db	62
	db	62
	db	62
	db	63
	db	63
	db	63
_DATA	ends
NOCTIS-0_TEXT	segment byte public use16 'CODE'
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@tavola_colori$qnucuiuiccc	proc	far
	push	bp
	mov	bp,sp
	sub	sp,2
	push	si
	push	di
	xor	cx,cx
	mov	ax,3
	imul	word ptr [bp+12]
	mov	word ptr [bp+12],ax
	mov	ax,3
	imul	word ptr [bp+10]
	mov	word ptr [bp+10],ax
	mov	ax,word ptr [bp+10]
	mov	word ptr [bp-2],ax
	cmp	cx,word ptr [bp+12]
	jae	short @10@5
@10@3:
	les	bx,dword ptr [bp+6]
	add	bx,cx
	mov	al,byte ptr es:[bx]
	mov	bx,word ptr [bp-2]
	mov	byte ptr DGROUP:_tmppal[bx],al
	inc	cx
	inc	word ptr [bp-2]
	cmp	cx,word ptr [bp+12]
	jb	short @10@3
@10@5:
	mov	ax,word ptr [bp+10]
	mov	word ptr [bp-2],ax
	jmp	@10@13
@10@6:
	mov	bx,word ptr [bp-2]
	mov	al,byte ptr DGROUP:_tmppal[bx]
	mov	ah,0
	mov	cx,ax
	mov	al,byte ptr [bp+14]
	cbw	
	imul	cx
	mov	cx,ax
	mov	bx,63
	mov	ax,cx
	xor	dx,dx
	div	bx
	mov	cx,ax
	cmp	cx,63
	jbe	short @10@8
	mov	cx,63
@10@8:
	mov	bx,word ptr [bp-2]
	mov	byte ptr DGROUP:_tmppal[bx],cl
	inc	word ptr [bp-2]
	mov	bx,word ptr [bp-2]
	mov	al,byte ptr DGROUP:_tmppal[bx]
	mov	ah,0
	mov	cx,ax
	mov	al,byte ptr [bp+16]
	cbw	
	imul	cx
	mov	cx,ax
	mov	bx,63
	mov	ax,cx
	xor	dx,dx
	div	bx
	mov	cx,ax
	cmp	cx,63
	jbe	short @10@10
	mov	cx,63
@10@10:
	mov	bx,word ptr [bp-2]
	mov	byte ptr DGROUP:_tmppal[bx],cl
	inc	word ptr [bp-2]
	mov	bx,word ptr [bp-2]
	mov	al,byte ptr DGROUP:_tmppal[bx]
	mov	ah,0
	mov	cx,ax
	mov	al,byte ptr [bp+18]
	cbw	
	imul	cx
	mov	cx,ax
	mov	bx,63
	mov	ax,cx
	xor	dx,dx
	div	bx
	mov	cx,ax
	cmp	cx,63
	jbe	short @10@12
	mov	cx,63
@10@12:
	mov	bx,word ptr [bp-2]
	mov	byte ptr DGROUP:_tmppal[bx],cl
	inc	word ptr [bp-2]
@10@13:
	mov	ax,word ptr [bp+12]
	add	ax,word ptr [bp+10]
	cmp	ax,word ptr [bp-2]
	ja	@10@6
	mov	dx,968
	mov	al,0
	out	dx,al
	xor	cx,cx
	jmp	short @10@18
@10@16:
	mov	bx,cx
	mov	al,byte ptr DGROUP:_tmppal[bx]
	mov	dx,969
	out	dx,al
	inc	cx
@10@18:
	mov	ax,word ptr [bp+10]
	add	ax,word ptr [bp+12]
	cmp	ax,cx
	ja	short @10@16
	pop	di
	pop	si
	leave	
	ret	
@tavola_colori$qnucuiuiccc	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@pcopy$qnuct1	proc	far
	push	bp
	mov	bp,sp
	push	si
	push	di
	mov	ax,word ptr DGROUP:_QUADWORDS
	shl	ax,2
	les	di,dword ptr [bp+6]
	mov	dx,word ptr [bp+12]
	mov	si,word ptr [bp+10]
	mov	cx,ax
	shr	cx,1
	push	ds
	mov	ds,dx
	rep 	movsw	
	adc	cx,cx
	rep 	movsb	
	pop	ds
	pop	di
	pop	si
	pop	bp
	ret	
@pcopy$qnuct1	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@pclear$qnucuc	proc	far
	push	bp
	mov	bp,sp
	push	si
	push	di
	mov	al,byte ptr [bp+10]
	mov	ah,0
	mov	dx,word ptr DGROUP:_QUADWORDS
	shl	dx,2
	les	di,dword ptr [bp+6]
	mov	ah,al
	mov	cx,dx
	shr	cx,1
	rep 	stosw	
	adc	cx,cx
	rep 	stosb	
	pop	di
	pop	si
	pop	bp
	ret	
@pclear$qnucuc	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@areaclear$qnuciiiiiiuc	proc	far
	push	bp
	mov	bp,sp
	sub	sp,2
	push	si
	push	di
	cmp	word ptr [bp+18],0
	je	short @13@3
	cmp	word ptr [bp+20],0
	jne	short @13@4
@13@3:
	mov	ax,word ptr [bp+14]
	sub	ax,word ptr [bp+10]
	mov	word ptr [bp+18],ax
	mov	ax,word ptr [bp+16]
	sub	ax,word ptr [bp+12]
	mov	word ptr [bp+20],ax
@13@4:
	mov	cx,word ptr [bp+10]
	jmp	short @13@10
@13@5:
	mov	dx,word ptr [bp+12]
	jmp	short @13@8
@13@6:
	mov	ax,dx
	imul	ax,ax,320
	add	ax,cx
	mov	word ptr [bp-2],ax
	les	bx,dword ptr [bp+6]
	add	bx,word ptr [bp-2]
	mov	al,byte ptr [bp+22]
	mov	byte ptr es:[bx],al
	inc	dx
@13@8:
	mov	ax,word ptr [bp+12]
	add	ax,word ptr [bp+20]
	cmp	ax,dx
	jg	short @13@6
	inc	cx
@13@10:
	mov	ax,word ptr [bp+10]
	add	ax,word ptr [bp+18]
	cmp	ax,cx
	jg	short @13@5
	pop	di
	pop	si
	leave	
	ret	
@areaclear$qnuciiiiiiuc	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@psmooth_grays$qnuc	proc	far
	push	bp
	mov	bp,sp
	sub	sp,14
	push	si
	push	di
	mov	ax,word ptr DGROUP:_QUADWORDS
	shl	ax,2
	add	ax,-1280
	mov	word ptr [bp-2],ax
	mov	word ptr [bp-4],0
	mov	word ptr [bp-6],0
	jmp	@14@5
@14@3:
	les	bx,dword ptr [bp+6]
	add	bx,word ptr [bp-4]
	mov	al,byte ptr es:[bx]
	mov	ah,0
	mov	word ptr [bp-8],ax
	mov	bx,word ptr [bp-4]
	add	bx,word ptr [bp+6]
	mov	cx,bx
	mov	al,byte ptr es:[bx+1]
	mov	ah,0
	mov	word ptr [bp-10],ax
	mov	al,byte ptr es:[bx+3]
	mov	ah,0
	mov	dx,ax
	shl	ax,24
	mov	dx,word ptr [bp-10]
	shl	dx,8
	add	ax,dx
	add	ax,word ptr [bp-8]
	movzx	eax,ax
	mov	dword ptr [bp-14],eax
	mov	al,byte ptr es:[bx+320]
	mov	ah,0
	mov	word ptr [bp-8],ax
	mov	al,byte ptr es:[bx+321]
	mov	ah,0
	mov	word ptr [bp-10],ax
	mov	al,byte ptr es:[bx+323]
	mov	ah,0
	mov	dx,ax
	shl	ax,24
	mov	dx,word ptr [bp-10]
	shl	dx,8
	add	ax,dx
	add	ax,word ptr [bp-8]
	movzx	eax,ax
	add	dword ptr [bp-14],eax
	mov	al,byte ptr es:[bx+640]
	mov	ah,0
	mov	word ptr [bp-8],ax
	mov	al,byte ptr es:[bx+641]
	mov	ah,0
	mov	word ptr [bp-10],ax
	mov	al,byte ptr es:[bx+643]
	mov	ah,0
	mov	dx,ax
	shl	ax,24
	mov	dx,word ptr [bp-10]
	shl	dx,8
	add	ax,dx
	add	ax,word ptr [bp-8]
	movzx	eax,ax
	add	dword ptr [bp-14],eax
	mov	al,byte ptr es:[bx+960]
	mov	ah,0
	mov	word ptr [bp-8],ax
	mov	al,byte ptr es:[bx+961]
	mov	ah,0
	mov	word ptr [bp-10],ax
	mov	al,byte ptr es:[bx+963]
	mov	ah,0
	mov	dx,ax
	shl	ax,24
	mov	dx,word ptr [bp-10]
	shl	dx,8
	add	ax,dx
	add	ax,word ptr [bp-8]
	movzx	eax,ax
	add	dword ptr [bp-14],eax
	and	dword ptr [bp-14],large 0FCFCFCFCh
	mov	eax,dword ptr [bp-14]
	shr	eax,2
	mov	dword ptr [bp-14],eax
	mov	dl,byte ptr [bp-14]
	and	dl,255
	mov	al,0
	add	al,dl
	mov	dl,al
	mov	eax,dword ptr [bp-14]
	shr	eax,16
	mov	dword ptr [bp-14],eax
	mov	al,byte ptr [bp-14]
	and	al,255
	add	al,dl
	mov	dl,al
	mov	al,0
	add	al,dl
	mov	dl,al
	shr	dl,2
	mov	bx,word ptr [bp+6]
	mov	byte ptr es:[bx+320],dl
	inc	word ptr [bp-6]
	inc	word ptr [bp-4]
@14@5:
	mov	ax,word ptr [bp-6]
	cmp	ax,word ptr [bp-2]
	jb	@14@3
	pop	di
	pop	si
	leave	
	ret	
@psmooth_grays$qnuc	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@pfade$qnucuiuc	proc	far
	push	bp
	mov	bp,sp
	sub	sp,8
	push	si
	push	di
	mov	ax,word ptr DGROUP:_QUADWORDS
	add	ax,-80
	shl	ax,2
	mov	word ptr [bp-2],ax
	push	word ptr [bp+10]
	push	dword ptr [bp+6]
	push	cs
	call	near ptr @shiftSegment$qnuci
	add	sp,6
	push	dx
	push	ax
	push	cs
	call	near ptr @clearOffset$qnuc
	add	sp,4
	mov	word ptr [bp-4],dx
	mov	word ptr [bp-6],ax
	xor	cx,cx
	jmp	short @15@8
@15@3:
	les	bx,dword ptr [bp-6]
	add	bx,cx
	mov	word ptr [bp-8],bx
	mov	dl,byte ptr es:[bx]
	and	dl,63
	cmp	byte ptr [bp+12],dl
	jae	short @15@5
	sub	dl,byte ptr [bp+12]
	jmp	short @15@6
@15@5:
	mov	dl,0
@15@6:
	mov	es,word ptr [bp-4]
	mov	bx,word ptr [bp-8]
	mov	byte ptr es:[bx],dl
	inc	cx
@15@8:
	cmp	cx,word ptr [bp-2]
	jb	short @15@3
	pop	di
	pop	si
	leave	
	ret	
@pfade$qnucuiuc	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@psmooth_64$qnucui	proc	far
	push	bp
	mov	bp,sp
	sub	sp,10
	push	si
	push	di
	mov	ax,word ptr DGROUP:_QUADWORDS
	add	ax,-80
	shl	ax,2
	mov	word ptr [bp-2],ax
	push	word ptr [bp+10]
	push	dword ptr [bp+6]
	push	cs
	call	near ptr @shiftSegment$qnuci
	add	sp,6
	push	dx
	push	ax
	push	cs
	call	near ptr @clearOffset$qnuc
	add	sp,4
	mov	word ptr [bp-4],dx
	mov	word ptr [bp-6],ax
	xor	cx,cx
	jmp	@16@5
@16@3:
	mov	ax,cx
	add	ax,320
	les	bx,dword ptr [bp-6]
	add	bx,ax
	mov	dl,byte ptr es:[bx]
	and	dl,63
	mov	ax,cx
	add	ax,321
	mov	bx,word ptr [bp-6]
	add	bx,ax
	mov	al,byte ptr es:[bx]
	and	al,63
	mov	byte ptr [bp-7],al
	mov	ax,cx
	add	ax,640
	mov	bx,word ptr [bp-6]
	add	bx,ax
	mov	al,byte ptr es:[bx]
	and	al,63
	mov	byte ptr [bp-8],al
	mov	ax,cx
	add	ax,641
	mov	bx,word ptr [bp-6]
	add	bx,ax
	mov	al,byte ptr es:[bx]
	and	al,63
	mov	byte ptr [bp-9],al
	mov	ax,cx
	add	ax,320
	mov	bx,word ptr [bp-6]
	add	bx,ax
	mov	al,byte ptr es:[bx]
	and	al,192
	mov	byte ptr [bp-10],al
	mov	al,dl
	mov	ah,0
	mov	dl,byte ptr [bp-7]
	mov	dh,0
	add	ax,dx
	mov	dl,byte ptr [bp-8]
	mov	dh,0
	add	ax,dx
	mov	dl,byte ptr [bp-9]
	mov	dh,0
	add	ax,dx
	mov	bx,4
	cwd	
	idiv	bx
	mov	dl,al
	or	dl,byte ptr [bp-10]
	mov	bx,word ptr [bp-6]
	add	bx,cx
	mov	byte ptr es:[bx],dl
	inc	cx
@16@5:
	cmp	cx,word ptr [bp-2]
	jb	@16@3
	pop	di
	pop	si
	leave	
	ret	
@psmooth_64$qnucui	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@smootharound_64$qnuclllc	proc	far
	push	bp
	mov	bp,sp
	sub	sp,54
	push	si
	push	di
	mov	eax,dword ptr [bp+10]
	sub	eax,dword ptr [bp+18]
	mov	dword ptr [bp-34],eax
	mov	dword ptr [bp-4],eax
	mov	eax,dword ptr [bp+14]
	sub	eax,dword ptr [bp+18]
	mov	dword ptr [bp-8],eax
	mov	eax,dword ptr [bp+10]
	add	eax,dword ptr [bp+18]
	mov	dword ptr [bp-12],eax
	mov	eax,dword ptr [bp+14]
	add	eax,dword ptr [bp+18]
	mov	dword ptr [bp-16],eax
	mov	eax,dword ptr [bp+18]
	imul	eax,dword ptr [bp+18]
	mov	dword ptr [bp-28],eax
	cmp	dword ptr [bp+18],large 0
	jle	@17@47
	cmp	dword ptr [bp-4],large 318
	jg	@17@47
	cmp	dword ptr [bp-8],large 198
	jg	@17@47
	cmp	dword ptr [bp-12],large 0
	jl	@17@47
	cmp	dword ptr [bp-16],large 0
	jl	@17@47
	cmp	dword ptr [bp-8],large 0
	jge	short @17@8
	mov	dword ptr [bp-8],large 0
@17@8:
	cmp	dword ptr [bp-12],large 318
	jle	short @17@10
	mov	dword ptr [bp-12],large 318
@17@10:
	cmp	dword ptr [bp-16],large 198
	jle	short @17@12
	mov	dword ptr [bp-16],large 198
@17@12:
	mov	eax,dword ptr [bp+18]
	neg	eax
	mov	dword ptr [bp-38],eax
	mov	dword ptr [bp-24],eax
	jmp	@17@46
@17@13:
	mov	eax,dword ptr [bp-38]
	mov	dword ptr [bp-20],eax
	mov	eax,dword ptr [bp-34]
	mov	dword ptr [bp-4],eax
	cmp	dword ptr [bp-4],large 0
	jge	short @17@15
	sub	dword ptr [bp-20],eax
	mov	dword ptr [bp-4],large 0
@17@15:
	mov	ax,word ptr [bp-8]
	imul	ax,ax,320
	add	ax,word ptr [bp-4]
	mov	word ptr [bp-30],ax
	cmp	byte ptr [bp+22],0
	je	@17@44
	jmp	@17@34
@17@17:
	mov	eax,dword ptr [bp-20]
	imul	eax,dword ptr [bp-20]
	mov	edx,dword ptr [bp-24]
	imul	edx,dword ptr [bp-24]
	add	eax,edx
	cmp	eax,dword ptr [bp-28]
	jge	@17@33
	les	bx,dword ptr [bp+6]
	add	bx,word ptr [bp-30]
	mov	word ptr [bp-40],bx
	mov	al,byte ptr es:[bx]
	mov	byte ptr [bp-50],al
	mov	ax,word ptr [bp-30]
	inc	ax
	mov	word ptr [bp-42],ax
	mov	bx,word ptr [bp+6]
	add	bx,ax
	mov	al,byte ptr es:[bx]
	mov	byte ptr [bp-49],al
	mov	ax,word ptr [bp-30]
	add	ax,320
	mov	word ptr [bp-44],ax
	mov	bx,word ptr [bp+6]
	add	bx,ax
	mov	al,byte ptr es:[bx]
	mov	byte ptr [bp-48],al
	mov	ax,word ptr [bp-30]
	add	ax,321
	mov	word ptr [bp-46],ax
	mov	bx,word ptr [bp+6]
	add	bx,ax
	mov	al,byte ptr es:[bx]
	mov	byte ptr [bp-47],al
	push	ss
	pop	es
	lea	di,word ptr [bp-54]
	mov	ax,ss
	lea	si,word ptr [bp-50]
	mov	cx,2
	push	ds
	mov	ds,ax
	rep 	movsw	
	pop	ds
	xor	ax,ax
@17@20:
	lea	bx,word ptr [bp-54]
	add	bx,ax
	and	byte ptr ss:[bx],192
	inc	ax
	cmp	ax,4
	jb	short @17@20
	xor	ax,ax
@17@24:
	lea	bx,word ptr [bp-50]
	add	bx,ax
	and	byte ptr ss:[bx],63
	inc	ax
	cmp	ax,4
	jb	short @17@24
	mov	al,byte ptr [bp-48]
	add	byte ptr [bp-50],al
	mov	al,byte ptr [bp-47]
	add	byte ptr [bp-49],al
	mov	al,byte ptr [bp-49]
	add	byte ptr [bp-50],al
	shr	byte ptr [bp-50],2
	mov	al,byte ptr [bp-50]
	mov	byte ptr [bp-49],al
	mov	al,byte ptr [bp-50]
	mov	byte ptr [bp-48],al
	mov	al,byte ptr [bp-49]
	mov	byte ptr [bp-47],al
	xor	dx,dx
@17@29:
	lea	bx,word ptr [bp-54]
	add	bx,dx
	mov	al,byte ptr ss:[bx]
	lea	bx,word ptr [bp-50]
	add	bx,dx
	or	byte ptr ss:[bx],al
	inc	dx
	cmp	dx,4
	jb	short @17@29
	mov	es,word ptr [bp+8]
	mov	bx,word ptr [bp-40]
	mov	al,byte ptr [bp-50]
	mov	byte ptr es:[bx],al
	mov	bx,word ptr [bp+6]
	add	bx,word ptr [bp-42]
	mov	al,byte ptr [bp-49]
	mov	byte ptr es:[bx],al
	mov	bx,word ptr [bp+6]
	add	bx,word ptr [bp-44]
	mov	al,byte ptr [bp-48]
	mov	byte ptr es:[bx],al
	mov	bx,word ptr [bp+6]
	add	bx,word ptr [bp-46]
	mov	al,byte ptr [bp-47]
	mov	byte ptr es:[bx],al
@17@33:
	inc	word ptr [bp-30]
	inc	dword ptr [bp-20]
	inc	dword ptr [bp-4]
@17@34:
	mov	eax,dword ptr [bp-4]
	cmp	eax,dword ptr [bp-12]
	jle	@17@17
	jmp	@17@45
@17@36:
	mov	eax,dword ptr [bp-20]
	imul	eax,dword ptr [bp-20]
	mov	edx,dword ptr [bp-24]
	imul	edx,dword ptr [bp-24]
	add	eax,edx
	cmp	eax,dword ptr [bp-28]
	jge	@17@43
	les	bx,dword ptr [bp+6]
	add	bx,word ptr [bp-30]
	mov	word ptr [bp-40],bx
	mov	al,byte ptr es:[bx]
	mov	byte ptr [bp-50],al
	mov	ax,word ptr [bp-30]
	inc	ax
	mov	bx,word ptr [bp+6]
	add	bx,ax
	mov	al,byte ptr es:[bx]
	mov	byte ptr [bp-49],al
	mov	ax,word ptr [bp-30]
	add	ax,320
	mov	bx,word ptr [bp+6]
	add	bx,ax
	mov	al,byte ptr es:[bx]
	mov	byte ptr [bp-48],al
	mov	ax,word ptr [bp-30]
	add	ax,321
	mov	bx,word ptr [bp+6]
	add	bx,ax
	mov	al,byte ptr es:[bx]
	mov	byte ptr [bp-47],al
	mov	dl,byte ptr [bp-50]
	and	dl,192
	xor	ax,ax
@17@39:
	lea	bx,word ptr [bp-50]
	add	bx,ax
	and	byte ptr ss:[bx],63
	inc	ax
	cmp	ax,4
	jb	short @17@39
	mov	al,byte ptr [bp-48]
	add	byte ptr [bp-50],al
	mov	al,byte ptr [bp-47]
	add	byte ptr [bp-49],al
	mov	al,byte ptr [bp-49]
	add	byte ptr [bp-50],al
	shr	byte ptr [bp-50],2
	or	byte ptr [bp-50],dl
	mov	es,word ptr [bp+8]
	mov	bx,word ptr [bp-40]
	mov	al,byte ptr [bp-50]
	mov	byte ptr es:[bx],al
@17@43:
	inc	word ptr [bp-30]
	inc	dword ptr [bp-20]
	inc	dword ptr [bp-4]
@17@44:
	mov	eax,dword ptr [bp-4]
	cmp	eax,dword ptr [bp-12]
	jle	@17@36
@17@45:
	inc	dword ptr [bp-24]
	inc	dword ptr [bp-8]
@17@46:
	mov	eax,dword ptr [bp-8]
	cmp	eax,dword ptr [bp-16]
	jle	@17@13
@17@47:
	pop	di
	pop	si
	leave	
	ret	
@smootharound_64$qnuclllc	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@mask_pixels$qnucuc	proc	far
	push	bp
	mov	bp,sp
	sub	sp,6
	push	si
	push	di
	mov	byte ptr [bp-1],63
	mov	dword ptr [bp-6],large 0
	jmp	short @18@5
@18@3:
	les	bx,dword ptr [bp+6]
	add	bx,word ptr [bp-6]
	mov	cx,bx
	mov	dl,byte ptr es:[bx]
	and	dl,byte ptr [bp-1]
	add	dl,byte ptr [bp+10]
	mov	byte ptr es:[bx],dl
	inc	dword ptr [bp-6]
@18@5:
	movsx	eax,word ptr DGROUP:_QUADWORDS
	shl	eax,2
	cmp	eax,dword ptr [bp-6]
	ja	short @18@3
	pop	di
	pop	si
	leave	
	ret	
@mask_pixels$qnucuc	endp
	?debug	C E96BAF2A4E0E5352432F7464706F6C7967732E68
	?debug	C E94020792216433A5C4243355C494E434C5544455C666C6F61742E+
	?debug	C 68
	?debug	C E96BAF2A4E0E5352432F6E6F637469732D642E68
NOCTIS-0_TEXT	ends
_DATA	segment word public use16 'DATA'
_uneg	label	dword
	db	0
	db	0
	db	200
	db	66
_alfa	label	dword
	db	0
	db	0
	db	0
	db	0
_beta	label	dword
	db	0
	db	0
	db	0
	db	0
_gamma	label	dword
	db	0
	db	0
	db	0
	db	0
_cam_x	label	dword
	db	0
	db	0
	db	0
	db	0
_cam_y	label	dword
	db	0
	db	0
	db	0
	db	0
_cam_z	label	dword
	db	0
	db	0
	db	0
	db	0
_deg	label	qword
	db	57
	db	157
	db	82
	db	162
	db	70
	db	223
	db	145
	db	63
_dpp	label	dword
	db	0
	db	0
	db	72
	db	67
_inv_dpp	label	dword
	db	4 dup (0)
_EMU_K	label	dword
	db	0
	db	0
	db	128
	db	65
_H_MATRIXS	label	dword
	db	16
	db	0
	db	0
	db	0
_V_MATRIXS	label	dword
	db	16
	db	0
	db	0
	db	0
_XSIZE	label	dword
	db	4 dup (0)
_YSIZE	label	dword
	db	4 dup (0)
_XCOEFF	label	dword
	db	4 dup (0)
_YCOEFF	label	dword
	db	4 dup (0)
_DATA	ends
_BSS	segment word public use16 'BSS'
_riga	label	word
	db	400 dup (?)
_BSS	ends
NOCTIS-0_TEXT	segment byte public use16 'CODE'
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@initscanlines$qv	proc	far
	push	si
	push	di
	xor	cx,cx
	mov	dx,offset DGROUP:_riga
@19@3:
	mov	ax,cx
	imul	ax,ax,320
	mov	bx,dx
	mov	word ptr [bx],ax
	add	dx,2
	inc	cx
	cmp	dx,offset DGROUP:_riga+400
	jne	short @19@3
	push	large 0003F003Fh
	call	far ptr __control87
	add	sp,4
	pop	di
	pop	si
	ret	
@initscanlines$qv	endp
NOCTIS-0_TEXT	ends
_BSS	segment word public use16 'BSS'
_ptr	label	word
	db	2 dup (?)
_xp	label	dword
	db	4 dup (?)
_yp	label	dword
	db	4 dup (?)
_xa	label	dword
	db	4 dup (?)
_ya	label	dword
	db	4 dup (?)
_global_x	label	dword
	db	4 dup (?)
_global_y	label	dword
	db	4 dup (?)
_BSS	ends
NOCTIS-0_TEXT	segment byte public use16 'CODE'
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@Segmento$qv	proc	far
	push	bp
	mov	bp,sp
	sub	sp,16
	push	si
	push	di
	mov	eax,dword ptr DGROUP:_xp
	cmp	eax,dword ptr DGROUP:_xa
	jne	short @20@15
	mov	eax,dword ptr DGROUP:_ya
	cmp	eax,dword ptr DGROUP:_yp
	jb	short @20@4
	mov	bx,word ptr DGROUP:_yp
	add	bx,bx
	mov	ax,word ptr DGROUP:_riga[bx]
	add	ax,word ptr DGROUP:_xp
	mov	word ptr [bp-14],ax
	mov	bx,word ptr DGROUP:_ya
	add	bx,bx
	jmp	short @20@5
@20@4:
	mov	bx,word ptr DGROUP:_ya
	add	bx,bx
	mov	ax,word ptr DGROUP:_riga[bx]
	add	ax,word ptr DGROUP:_xp
	mov	word ptr [bp-14],ax
	mov	bx,word ptr DGROUP:_yp
	add	bx,bx
@20@5:
	mov	ax,word ptr DGROUP:_riga[bx+2]
	mov	word ptr [bp-16],ax
   	les	 si, dword ptr DGROUP:_adapted
	add	 [bp-14], si
	add	 [bp-16], si
	mov	 si, [bp-14] 
@20@10:
   	mov	 byte ptr es:[si], 255
	add	 si, 320
	cmp	 si, [bp-16]
	jb	short @20@10
	jmp	@20@111
@20@15:
   	db	 066H
	mov	 si, word ptr DGROUP:_xa
	db	 066H
	sub	 si, word ptr DGROUP:_xp
	jnc	short @20@38
	db	 066H
	mov	 ax, word ptr DGROUP:_xp
	db	 066H
	mov	 bx, word ptr DGROUP:_xa
	db	 066H
	mov	 cx, word ptr DGROUP:_yp
	db	 066H
	mov	 dx, word ptr DGROUP:_ya
	db	 066H
	mov	 word ptr DGROUP:_xa, ax
	db	 066H
	mov	 word ptr DGROUP:_xp, bx
	db	 066H
	mov	 word ptr DGROUP:_ya, cx
	db	 066H
	mov	 word ptr DGROUP:_yp, dx
	db	 066H
	neg	 si 
@20@38:
   	db	 066H
	mov	 word ptr [bp-4], si
	db	 066H
	mov	 word ptr [bp-12], si
	xor	 ch, ch
	db	 066H
	mov	 ax, word ptr DGROUP:_ya
	db	 066H
	sub	 ax, word ptr DGROUP:_yp
	jnc	short @20@51
	not	 ch
	db	 066H
	neg	 ax 
@20@51:
   	db	 066H
	mov	 word ptr [bp-8], ax
	db	 066H
	cmp	 ax, word ptr [bp-12]
	jb	short @20@58
	db	 066H
	mov	 word ptr [bp-12], ax 
@20@58:
   	db	 066H
	inc	 word ptr [bp-12]
	db	 066H
	shl	 word ptr DGROUP:_xa, 16
	db	 066H
	mov	 ax, word ptr DGROUP:_xp
	db	 066H
	mov	 bx, word ptr DGROUP:_yp
	db	 066H
	shl	 ax, 16
	db	 066H
	shl	 bx, 16
	db	 066H
	mov	 word ptr DGROUP:_global_x, ax
	db	 066H
	mov	 word ptr DGROUP:_global_y, bx
	db	 066H
	shl	 word ptr [bp-4], 16 
	db	 066H
	sal	 word ptr [bp-8], 16 
	mov	 dx, word ptr [bp-4][2]
	mov	 ax, word ptr [bp-4]
	div	 word ptr [bp-12]     
	mov	 word ptr [bp-4], ax
	mov	 word ptr [bp-4][2], 0
	mov	 dx, word ptr [bp-8][2]
	mov	 ax, word ptr [bp-8]
	div	 word ptr [bp-12]     
	mov	 word ptr [bp-8], ax
	mov	 word ptr [bp-8][2], 0
	test	 ch, ch
	je	short @20@92
	db	 066H
	neg	 word ptr [bp-8] 
@20@92:
 	les	 ax, dword ptr DGROUP:_adapted
   	db	 066H
	mov	 ax, word ptr [bp-4]    
	db	 066H
	mov	 dx, word ptr [bp-8]    
	db	 066H
	mov	 cx, word ptr DGROUP:_xa 
@20@99:
   	mov	 bx, word ptr DGROUP:_global_y[2]
	mov	 di, word ptr DGROUP:_global_x[2]
	add	 bx, bx
	db	 066H
	add	 word ptr DGROUP:_global_x, ax
	add	 di, word ptr DGROUP:_riga[bx]
	db	 066H
	add	 word ptr DGROUP:_global_y, dx
	mov	 byte ptr es:[di+4], 255
	db	 066H
	cmp	 word ptr DGROUP:_global_x, cx
	jb	short @20@99
@20@111:
	pop	di
	pop	si
	leave	
	ret	
@Segmento$qv	endp
NOCTIS-0_TEXT	ends
_DATA	segment word public use16 'DATA'
_flares	label	byte
	db	0
_DATA	ends
_BSS	segment word public use16 'BSS'
_mp	label	dword
	db	96 dup (?)
_max_x	label	word
	db	2 dup (?)
_max_y	label	word
	db	2 dup (?)
_min_x	label	word
	db	2 dup (?)
_min_y	label	word
	db	2 dup (?)
_doflag	label	byte
	db	1 dup (?)
	db	1 dup (?)
_pvert	label	word
	db	2 dup (?)
_nvert	label	word
	db	2 dup (?)
_vvert	label	word
	db	2 dup (?)
_vr	label	word
	db	2 dup (?)
_vr2	label	word
	db	2 dup (?)
_vr3	label	word
	db	2 dup (?)
_vr4	label	word
	db	2 dup (?)
_vr5	label	word
	db	2 dup (?)
_vr6	label	word
	db	2 dup (?)
_zk	label	dword
	db	4 dup (?)
_x2	label	dword
	db	4 dup (?)
_y2	label	dword
	db	4 dup (?)
_z2	label	dword
	db	4 dup (?)
_xx	label	dword
	db	4 dup (?)
_yy	label	dword
	db	4 dup (?)
_zz	label	dword
	db	4 dup (?)
_rwf	label	byte
	db	4 dup (?)
_rxf	label	dword
	db	16 dup (?)
_ryf	label	dword
	db	16 dup (?)
_rzf	label	dword
	db	16 dup (?)
_BSS	ends
_DATA	segment word public use16 'DATA'
	db	1 dup (0)
_lbxl	label	dword
	db	5
	db	0
	db	0
	db	0
_ubxl	label	dword
	db	55
	db	1
	db	0
	db	0
_lbyl	label	dword
	db	10
	db	0
	db	0
	db	0
_ubyl	label	dword
	db	190
	db	0
	db	0
	db	0
_lbxf	label	dword
	db	0
	db	0
	db	160
	db	64
_ubxf	label	dword
	db	0
	db	128
	db	155
	db	67
_lbyf	label	dword
	db	0
	db	0
	db	32
	db	65
_ubyf	label	dword
	db	0
	db	0
	db	62
	db	67
_x_centro_f	label	dword
	db	0
	db	0
	db	30
	db	67
_y_centro_f	label	dword
	db	0
	db	0
	db	200
	db	66
_opt_pcosbeta	label	dword
	db	4 dup (0)
_opt_psinbeta	label	dword
	db	0
	db	0
	db	0
	db	0
_opt_tcosbeta	label	dword
	db	0
	db	0
	db	128
	db	63
_opt_tsinbeta	label	dword
	db	0
	db	0
	db	0
	db	0
_opt_pcosalfa	label	dword
	db	4 dup (0)
_opt_psinalfa	label	dword
	db	0
	db	0
	db	0
	db	0
_opt_tcosalfa	label	dword
	db	0
	db	0
	db	128
	db	63
_opt_tsinalfa	label	dword
	db	0
	db	0
	db	0
	db	0
_opt_tcosgamma	label	dword
	db	0
	db	0
	db	128
	db	63
_opt_tsingamma	label	dword
	db	0
	db	0
	db	0
	db	0
_DATA	ends
NOCTIS-0_TEXT	segment byte public use16 'CODE'
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@change_angle_of_view$qv	proc	far
	push	bp
	mov	bp,sp
	push	si
	push	di
	fld	dword ptr DGROUP:_beta
	fmul	qword ptr DGROUP:_deg
	sub	sp,8
	fstp	qword ptr [bp-12]
	fwait	
	call	far ptr _cos
	add	sp,8
	fmul	dword ptr DGROUP:_dpp
	fstp	dword ptr DGROUP:_opt_pcosbeta
	fld	dword ptr DGROUP:_beta
	fmul	qword ptr DGROUP:_deg
	sub	sp,8
	fstp	qword ptr [bp-12]
	fwait	
	call	far ptr _sin
	add	sp,8
	fmul	dword ptr DGROUP:_dpp
	fstp	dword ptr DGROUP:_opt_psinbeta
	fld	dword ptr DGROUP:_beta
	fmul	qword ptr DGROUP:_deg
	sub	sp,8
	fstp	qword ptr [bp-12]
	fwait	
	call	far ptr _cos
	add	sp,8
	fstp	dword ptr DGROUP:_opt_tcosbeta
	fld	dword ptr DGROUP:_beta
	fmul	qword ptr DGROUP:_deg
	sub	sp,8
	fstp	qword ptr [bp-12]
	fwait	
	call	far ptr _sin
	add	sp,8
	fstp	dword ptr DGROUP:_opt_tsinbeta
	fld	dword ptr DGROUP:_alfa
	fmul	qword ptr DGROUP:_deg
	sub	sp,8
	fstp	qword ptr [bp-12]
	fwait	
	call	far ptr _cos
	add	sp,8
	fmul	dword ptr DGROUP:_dpp
	fstp	dword ptr DGROUP:_opt_pcosalfa
	fld	dword ptr DGROUP:_alfa
	fmul	qword ptr DGROUP:_deg
	sub	sp,8
	fstp	qword ptr [bp-12]
	fwait	
	call	far ptr _sin
	add	sp,8
	fmul	dword ptr DGROUP:_dpp
	fstp	dword ptr DGROUP:_opt_psinalfa
	fld	dword ptr DGROUP:_alfa
	fmul	qword ptr DGROUP:_deg
	sub	sp,8
	fstp	qword ptr [bp-12]
	fwait	
	call	far ptr _cos
	add	sp,8
	fstp	dword ptr DGROUP:_opt_tcosalfa
	fld	dword ptr DGROUP:_alfa
	fmul	qword ptr DGROUP:_deg
	sub	sp,8
	fstp	qword ptr [bp-12]
	fwait	
	call	far ptr _sin
	add	sp,8
	fstp	dword ptr DGROUP:_opt_tsinalfa
	fld	dword ptr DGROUP:_gamma
	fmul	qword ptr DGROUP:_deg
	sub	sp,8
	fstp	qword ptr [bp-12]
	fwait	
	call	far ptr _cos
	add	sp,8
	fstp	dword ptr DGROUP:_opt_tcosgamma
	fld	dword ptr DGROUP:_gamma
	fmul	qword ptr DGROUP:_deg
	sub	sp,8
	fstp	qword ptr [bp-12]
	fwait	
	call	far ptr _sin
	add	sp,8
	fstp	dword ptr DGROUP:_opt_tsingamma
	fwait	
	pop	di
	pop	si
	pop	bp
	ret	
@change_angle_of_view$qv	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@change_camera_lens$qv	proc	far
	push	bp
	mov	bp,sp
	sub	sp,4
	push	si
	push	di
	fld1	
	fdiv	dword ptr DGROUP:_dpp
	fstp	dword ptr DGROUP:_inv_dpp
	fld	dword ptr DGROUP:_EMU_K
	fdiv	dword ptr DGROUP:_dpp
	fst	dword ptr [bp-4]
	fstp	dword ptr DGROUP:_XCOEFF
	fld	dword ptr [bp-4]
	fstp	dword ptr DGROUP:_YCOEFF
	fwait	
	push	cs
	call	near ptr @change_angle_of_view$qv
	pop	di
	pop	si
	leave	
	ret	
@change_camera_lens$qv	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@change_txm_repeating_mode$qv	proc	far
	push	si
	push	di
	mov	eax,dword ptr DGROUP:_H_MATRIXS
	shl	eax,8
	mov	dword ptr DGROUP:_XSIZE,eax
	mov	eax,dword ptr DGROUP:_V_MATRIXS
	shl	eax,8
	mov	dword ptr DGROUP:_YSIZE,eax
	pop	di
	pop	si
	ret	
@change_txm_repeating_mode$qv	endp
NOCTIS-0_TEXT	ends
_DATA	segment word public use16 'DATA'
_uno	label	dword
	db	0
	db	0
	db	128
	db	63
_entity	label	byte
	db	1
_DATA	ends
NOCTIS-0_TEXT	segment byte public use16 'CODE'
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@poly3d$qnft1t1uiuc	proc	far
	push	bp
	mov	bp,sp
	sub	sp,588
	push	si
	push	di
	mov	al,byte ptr DGROUP:_entity
	mov	byte ptr [bp-3],al
	mov	byte ptr DGROUP:_doflag,0
   	xor	 di, di
	xor	 si, si 
@24@4:
   	les	 bx, dword ptr [bp+14]
	fld	 dword ptr es:[bx+si]
	fsub	 DGROUP:_cam_z
	fst	 DGROUP:_zz
	fmul	 DGROUP:_opt_psinbeta
	les	 bx, dword ptr [bp+6]
	fld	 dword ptr es:[bx+si]
	fsub	 DGROUP:_cam_x
	fst	 DGROUP:_xx
	fmul	 DGROUP:_opt_pcosbeta
	faddp	
	fstp	 dword ptr DGROUP:_rxf[si]
	fld	 DGROUP:_zz
	fmul	 DGROUP:_opt_tcosbeta
	fld	 DGROUP:_xx
	fmul	 DGROUP:_opt_tsinbeta
	fsubp	
	fst	 DGROUP:_z2
	fmul	 DGROUP:_opt_tcosalfa
	les	 bx, dword ptr [bp+10]
	fld	 dword ptr es:[bx+si]
	fsub	 DGROUP:_cam_y
	fst	 DGROUP:_yy
	fmul	 DGROUP:_opt_tsinalfa
	faddp	
	fst	 dword ptr DGROUP:_rzf[si]
	fcomp	 DGROUP:_uneg
	fstsw	 ax
	fld	 DGROUP:_yy
	fmul	 DGROUP:_opt_pcosalfa
	fld	 DGROUP:_z2
	fmul	 DGROUP:_opt_psinalfa
	fsubp	
	fstp	 dword ptr DGROUP:_ryf[si]
	sahf	
	jb	short @24@43
	inc	 DGROUP:_doflag
	mov	 byte ptr DGROUP:_rwf[di], 1
	jmp	short @24@44
@24@43:
   	mov	 byte ptr DGROUP:_rwf[di], 0
@24@44:
 	add	 si, 4
	inc	 di
	cmp	 di, [bp+18]
	je	short @24@49
	jmp	@24@4
@24@49:
	cmp	byte ptr DGROUP:_doflag,0
	jne	short @24@51
	jmp	@24@1355
@24@51:
	mov	al,byte ptr DGROUP:_doflag
	cbw	
	cmp	ax,word ptr [bp+18]
	jne	short @24@71
   	xor	 si, si
	mov	 cx, [bp+18]
	mov	 DGROUP:_vr2, cx 
@24@55:
   	db	 066H
	mov	 ax, word ptr DGROUP:_rxf[si]
	db	 066H
	mov	 bx, word ptr DGROUP:_ryf[si]
	db	 066H
	mov	 dx, word ptr DGROUP:_rzf[si]
	db	 066H
	mov	 word ptr [bp-44][si], ax
	db	 066H
	mov	 word ptr [bp-76][si], bx
	db	 066H
	mov	 word ptr [bp-108][si], dx
	add	 si, 4
	dec	 cx
	jne	short @24@55
	jmp	@24@277
@24@71:
   	mov	 DGROUP:_vr, 0
	xor	 di, di
	mov	 dx, [bp+18]
	dec	 dx 
@24@75:
   	mov	 si, DGROUP:_vr
	cmp	 byte ptr DGROUP:_rwf[si], 0
	je	short @24@79
	jmp	@24@253
@24@79:
   	mov	 ax, DGROUP:_vr
	sub	 ax, 1
	jnc	short @24@84
	mov	 DGROUP:_pvert, dx
	jmp	short @24@85
@24@84:
     	mov	 DGROUP:_pvert, ax
@24@85:
   	mov	 ax, DGROUP:_vr
	inc	 ax
	cmp	 ax, dx
	jbe	short @24@91
	mov	 DGROUP:_nvert, 0
	jmp	short @24@92
@24@91:
     	mov	 DGROUP:_nvert, ax
@24@92:
   	mov	 si, DGROUP:_pvert
	cmp	 byte ptr DGROUP:_rwf[si], 0
	je	short @24@96
	jmp	short @24@100
@24@96:
   	mov	 si, DGROUP:_nvert
	cmp	 byte ptr DGROUP:_rwf[si], 0
	jne	short @24@100
	jmp	@24@267
@24@100:
   	mov	 bx, DGROUP:_vr
	shl	 bx, 2
	mov	 si, DGROUP:_pvert
	mov	 al, byte ptr DGROUP:_rwf[si]
	mov	 si, DGROUP:_nvert
	add	 al, byte ptr DGROUP:_rwf[si]
	cmp	 al, 2
	je	short @24@109
	jmp	@24@199
@24@109:
   	shl	 DGROUP:_pvert, 2
	shl	 DGROUP:_nvert, 2
	mov	 si, bx
	fld	 dword ptr DGROUP:_rzf[si]
	mov	 si, DGROUP:_pvert
	fcomp	 dword ptr DGROUP:_rzf[si]
	fstsw	 ax
	sahf	
	jne	short @24@119
	jmp	@24@141
@24@119:
   	fld	 dword ptr DGROUP:_uneg
	fsub	 dword ptr DGROUP:_rzf[si]
	fld	 dword ptr DGROUP:_rzf[si]
	mov	 si, bx
	fsubr	 dword ptr DGROUP:_rzf[si]
	fdivp	
	fst	 DGROUP:_zk
	fld	 dword ptr DGROUP:_rxf[si]
	mov	 si, DGROUP:_pvert
	fsub	 dword ptr DGROUP:_rxf[si]
	fmulp	
	fadd	 dword ptr DGROUP:_rxf[si]
	fstp	 dword ptr [bp-44][di]
	fld	 DGROUP:_zk
	mov	 si, bx
	fld	 dword ptr DGROUP:_ryf[si]
	mov	 si, DGROUP:_pvert
	fsub	 dword ptr DGROUP:_ryf[si]
	fmulp	
	fadd	 dword ptr DGROUP:_ryf[si]
	fstp	 dword ptr [bp-76][di]
	jmp	short @24@150
@24@141:
   	mov	 si, bx
	db	 066H
	mov	 ax, word ptr DGROUP:_rxf[si]
	db	 066H
	mov	 word ptr [bp-44][di], ax
	db	 066H
	mov	 ax, word ptr DGROUP:_ryf[si]
	db	 066H
	mov	 word ptr [bp-76][di], ax 
@24@150:
   	db	 066H
	mov	 ax, word ptr DGROUP:_uneg
	db	 066H
	mov	 word ptr [bp-108][di], ax
	mov	 si, bx
	fld	 dword ptr DGROUP:_rzf[si]
	mov	 si, DGROUP:_nvert
	fcomp	 dword ptr DGROUP:_rzf[si]
	fstsw	 ax
	sahf	
	jne	short @24@162
	jmp	@24@184
@24@162:
   	fld	 dword ptr DGROUP:_uneg
	fsub	 dword ptr DGROUP:_rzf[si]
	fld	 dword ptr DGROUP:_rzf[si]
	mov	 si, bx
	fsubr	 dword ptr DGROUP:_rzf[si]
	fdivp	
	fst	 DGROUP:_zk
	fld	 dword ptr DGROUP:_rxf[si]
	mov	 si, DGROUP:_nvert
	fsub	 dword ptr DGROUP:_rxf[si]
	fmulp	
	fadd	 dword ptr DGROUP:_rxf[si]
	fstp	 dword ptr [bp-44][di+4]
	fld	 DGROUP:_zk
	mov	 si, bx
	fld	 dword ptr DGROUP:_ryf[si]
	mov	 si, DGROUP:_nvert
	fsub	 dword ptr DGROUP:_ryf[si]
	fmulp	
	fadd	 dword ptr DGROUP:_ryf[si]
	fstp	 dword ptr [bp-76][di+4]
	jmp	short @24@193
@24@184:
   	mov	 si, bx
	db	 066H
	mov	 ax, word ptr DGROUP:_rxf[si]
	db	 066H
	mov	 word ptr [bp-44][di+4], ax
	db	 066H
	mov	 ax, word ptr DGROUP:_ryf[si]
	db	 066H
	mov	 word ptr [bp-76][di+4], ax 
@24@193:
   	db	 066H
	mov	 ax, word ptr DGROUP:_uneg
	db	 066H
	mov	 word ptr [bp-108][di+4], ax
	add	 di, 8
	jmp	@24@267
@24@199:
   	mov	 si, DGROUP:_pvert
	cmp	 byte ptr DGROUP:_rwf[si], 0
	jne	short @24@205
	mov	 ax, DGROUP:_nvert
	mov	 DGROUP:_vvert, ax
	jmp	short @24@207
@24@205:
   	mov	 ax, DGROUP:_pvert
	mov	 DGROUP:_vvert, ax 
@24@207:
   	shl	 DGROUP:_vvert, 2
	mov	 si, bx
	fld	 dword ptr DGROUP:_rzf[si]
	mov	 si, DGROUP:_vvert
	fcomp	 dword ptr DGROUP:_rzf[si]
	fstsw	 ax
	sahf	
	jne	short @24@216
	jmp	@24@238
@24@216:
   	fld	 dword ptr DGROUP:_uneg
	fsub	 dword ptr DGROUP:_rzf[si]
	fld	 dword ptr DGROUP:_rzf[si]
	mov	 si, bx
	fsubr	 dword ptr DGROUP:_rzf[si]
	fdivp	
	fst	 DGROUP:_zk
	fld	 dword ptr DGROUP:_rxf[si]
	mov	 si, DGROUP:_vvert
	fsub	 dword ptr DGROUP:_rxf[si]
	fmulp	
	fadd	 dword ptr DGROUP:_rxf[si]
	fstp	 dword ptr [bp-44][di]
	fld	 DGROUP:_zk
	mov	 si, bx
	fld	 dword ptr DGROUP:_ryf[si]
	mov	 si, DGROUP:_vvert
	fsub	 dword ptr DGROUP:_ryf[si]
	fmulp	
	fadd	 dword ptr DGROUP:_ryf[si]
	fstp	 dword ptr [bp-76][di]
	jmp	short @24@247
@24@238:
   	mov	 si, bx
	db	 066H
	mov	 ax, word ptr DGROUP:_rxf[si]
	db	 066H
	mov	 word ptr [bp-44][di], ax
	db	 066H
	mov	 ax, word ptr DGROUP:_ryf[si]
	db	 066H
	mov	 word ptr [bp-76][di], ax 
@24@247:
   	db	 066H
	mov	 ax, word ptr DGROUP:_uneg
	db	 066H
	mov	 word ptr [bp-108][di], ax
	add	 di, 4
	jmp	short @24@267
@24@253:
   	shl	 si, 2
	db	 066H
	mov	 ax, word ptr DGROUP:_rxf[si]
	db	 066H
	mov	 word ptr [bp-44][di], ax
	db	 066H
	mov	 ax, word ptr DGROUP:_ryf[si]
	db	 066H
	mov	 word ptr [bp-76][di], ax
	db	 066H
	mov	 ax, word ptr DGROUP:_rzf[si]
	db	 066H
	mov	 word ptr [bp-108][di], ax
	add	 di, 4 
@24@267:
   	inc	 DGROUP:_vr
	mov	 ax, DGROUP:_vr
	cmp	 ax, [bp+18]
	jae	short @24@272
	jmp	@24@75
@24@272:
   	mov	 ax, di
	shr	 ax, 2
	mov	 DGROUP:_vr2, ax 
	cmp	word ptr DGROUP:_vr2,3
	jge	short @24@277
	jmp	@24@1355
@24@277:
   	db	 066H
	mov	 ax, word ptr DGROUP:_lbxl
	db	 066H
	mov	 bx, word ptr DGROUP:_lbyl
	db	 066H
	mov	 cx, word ptr DGROUP:_ubxl
	db	 066H
	mov	 dx, word ptr DGROUP:_ubyl
	mov	 si, DGROUP:_vr2
	dec	 si
	shl	 si, 2
	mov	 di, si
	add	 di, si
	mov	 [bp-2], di 
@24@291:
   	fld	 DGROUP:_uno
	fdiv	 dword ptr [bp-108][si]
	fld	 st(0)
	fmul	 dword ptr [bp-44][si]
	fadd	 dword ptr DGROUP:_x_centro_f
	fst	 dword ptr [bp-140][si]
	fistp	 dword ptr DGROUP:_mp[di]
	db	 066H
	cmp	 word ptr DGROUP:_mp[di], cx
	jge	short @24@303
	db	 066H
	mov	 cx, word ptr DGROUP:_mp[di] 
@24@303:
   	db	 066H
	cmp	 word ptr DGROUP:_mp[di], ax
	jle	short @24@308
	db	 066H
	mov	 ax, word ptr DGROUP:_mp[di] 
@24@308:
   	fmul	 dword ptr [bp-76][si]
	fadd	 dword ptr DGROUP:_y_centro_f
	fst	 dword ptr [bp-172][si]
	fistp	 dword ptr DGROUP:_mp[di+4]
	db	 066H
	cmp	 word ptr DGROUP:_mp[di+4], dx
	jge	short @24@317
	db	 066H
	mov	 dx, word ptr DGROUP:_mp[di+4] 
@24@317:
   	db	 066H
	cmp	 word ptr DGROUP:_mp[di+4], bx
	jle	short @24@322
	db	 066H
	mov	 bx, word ptr DGROUP:_mp[di+4] 
@24@322:
   	sub	 di, 8
	sub	 si, 4
	jnc	short @24@291
	mov	 DGROUP:_max_x, ax
	mov	 DGROUP:_max_y, bx
	mov	 DGROUP:_min_x, cx
	mov	 DGROUP:_min_y, dx
	xor	 si, si
	db	 066H
	cmp	 ax, word ptr DGROUP:_ubxl
	jl	short @24@335
	inc	 si
	mov	 DGROUP:_max_x, 306/2 + 158 
@24@335:
   	db	 066H
	cmp	 bx, word ptr DGROUP:_ubyl
	jl	short @24@340
	inc	 si
	mov	 DGROUP:_max_y, 180/2 + 100 
@24@340:
   	db	 066H
	cmp	 cx, word ptr DGROUP:_lbxl
	jge	short @24@345
	inc	 si
	mov	 DGROUP:_min_x, -306/2 + 158 
@24@345:
   	db	 066H
	cmp	 dx, word ptr DGROUP:_lbyl
	jge	short @24@350
	inc	 si
	mov	 DGROUP:_min_y, -180/2 + 100 
@24@350:
   	test	 si, si
	jne	short @24@353
	jmp	@24@1054
@24@353:
   	mov	 DGROUP:_vr, 0
	xor	 di, di
	mov	 dx, DGROUP:_vr2
	dec	 dx 
@24@357:
   	mov	 si, DGROUP:_vr
	shl	 si, 2
	fld	 dword ptr [bp-172][si]
	fcomp	 dword ptr DGROUP:_lbyf
	fstsw	 ax
	sahf	
	jb	short @24@365
	jmp	@24@513
@24@365:
   	mov	 bx, si
	mov	 ax, DGROUP:_vr
	sub	 ax, 1
	jnc	short @24@371
	mov	 DGROUP:_pvert, dx
	jmp	short @24@372
@24@371:
     	mov	 DGROUP:_pvert, ax
@24@372:
   	mov	 ax, DGROUP:_vr
	inc	 ax
	cmp	 ax, dx
	jbe	short @24@378
	mov	 DGROUP:_nvert, 0
	jmp	short @24@379
@24@378:
     	mov	 DGROUP:_nvert, ax
@24@379:
   	shl	 DGROUP:_pvert, 2
	shl	 DGROUP:_nvert, 2
	mov	 si, DGROUP:_pvert
	fld	 dword ptr [bp-172][si]
	fcomp	 dword ptr DGROUP:_lbyf
	fstsw	 ax
	sahf	
	jae	short @24@394
	mov	 si, DGROUP:_nvert
	fld	 dword ptr [bp-172][si]
	fcomp	 dword ptr DGROUP:_lbyf
	fstsw	 ax
	sahf	
	jae	short @24@394
	jmp	@24@522
@24@394:
   	mov	 si, DGROUP:_pvert
	fld	 dword ptr [bp-172][si]
	fcomp	 dword ptr DGROUP:_lbyf
	fstsw	 ax
	sahf	
	jae	short @24@401
	jmp	@24@470
@24@401:
   	mov	 si, DGROUP:_nvert
	fld	 dword ptr [bp-172][si]
	fcomp	 dword ptr DGROUP:_lbyf
	fstsw	 ax
	sahf	
	jae	short @24@408
	jmp	@24@470
@24@408:
   	mov	 si, bx
	fld	 dword ptr [bp-172][si]
	mov	 si, DGROUP:_pvert
	fcomp	 dword ptr [bp-172][si]
	fstsw	 ax
	sahf	
	jne	short @24@416
	jmp	short @24@429
@24@416:
   	fld	 dword ptr DGROUP:_lbyf
	fsub	 dword ptr [bp-172][si]
	fld	 dword ptr [bp-172][si]
	mov	 si, bx
	fsubr	 dword ptr [bp-172][si]
	fdivp	
	fld	 dword ptr [bp-140][si]
	mov	 si, DGROUP:_pvert
	fsub	 dword ptr [bp-140][si]
	fmulp	
	fadd	 dword ptr [bp-140][si]
	fstp	 dword ptr [bp-220][di]
	jmp	short @24@434
@24@429:
   	mov	 si, bx
	db	 066H
	mov	 ax, word ptr [bp-140][si]
	db	 066H
	mov	 word ptr [bp-220][di], ax 
@24@434:
   	db	 066H
	mov	 ax, word ptr DGROUP:_lbyf
	db	 066H
	mov	 word ptr [bp-268][di], ax
	mov	 si, bx
	fld	 dword ptr [bp-172][si]
	mov	 si, DGROUP:_nvert
	fcomp	 dword ptr [bp-172][si]
	fstsw	 ax
	sahf	
	jne	short @24@446
	jmp	short @24@459
@24@446:
   	fld	 dword ptr DGROUP:_lbyf
	fsub	 dword ptr [bp-172][si]
	fld	 dword ptr [bp-172][si]
	mov	 si, bx
	fsubr	 dword ptr [bp-172][si]
	fdivp	
	fld	 dword ptr [bp-140][si]
	mov	 si, DGROUP:_nvert
	fsub	 dword ptr [bp-140][si]
	fmulp	
	fadd	 dword ptr [bp-140][si]
	fstp	 dword ptr [bp-220][di+4]
	jmp	short @24@464
@24@459:
   	mov	 si, bx
	db	 066H
	mov	 ax, word ptr [bp-140][si]
	db	 066H
	mov	 word ptr [bp-220][di+4], ax 
@24@464:
   	db	 066H
	mov	 ax, word ptr DGROUP:_lbyf
	db	 066H
	mov	 word ptr [bp-268][di+4], ax
	add	 di, 8
	jmp	@24@522
@24@470:
   	mov	 si, DGROUP:_pvert
	fld	 dword ptr [bp-172][si]
	fcomp	 dword ptr DGROUP:_lbyf
	fstsw	 ax
	sahf	
	jb	short @24@479
	mov	 ax, DGROUP:_pvert
	mov	 DGROUP:_vvert, ax
	jmp	short @24@481
@24@479:
   	mov	 ax, DGROUP:_nvert
	mov	 DGROUP:_vvert, ax 
@24@481:
   	mov	 si, bx
	fld	 dword ptr [bp-172][si]
	mov	 si, DGROUP:_vvert
	fcomp	 dword ptr [bp-172][si]
	fstsw	 ax
	sahf	
	jne	short @24@489
	jmp	@24@681
@24@489:
   	fld	 dword ptr DGROUP:_lbyf
	fsub	 dword ptr [bp-172][si]
	fld	 dword ptr [bp-172][si]
	mov	 si, bx
	fsubr	 dword ptr [bp-172][si]
	fdivp	
	fld	 dword ptr [bp-140][si]
	mov	 si, DGROUP:_vvert
	fsub	 dword ptr [bp-140][si]
	fmulp	
	fadd	 dword ptr [bp-140][si]
	fstp	 dword ptr [bp-220][di]
	jmp	short @24@507
   	mov	 si, bx
	db	 066H
	mov	 ax, word ptr [bp-140][si]
	db	 066H
	mov	 word ptr [bp-220][di], ax 
@24@507:
   	db	 066H
	mov	 ax, word ptr DGROUP:_lbyf
	db	 066H
	mov	 word ptr [bp-268][di], ax
	add	 di, 4
	jmp	short @24@522
@24@513:
   	db	 066H
	mov	 ax, word ptr [bp-172][si]
	db	 066H
	mov	 word ptr [bp-268][di], ax
	db	 066H
	mov	 ax, word ptr [bp-140][si]
	db	 066H
	mov	 word ptr [bp-220][di], ax
	add	 di, 4 
@24@522:
   	inc	 DGROUP:_vr
	mov	 ax, DGROUP:_vr
	cmp	 ax, DGROUP:_vr2
	jae	short @24@527
	jmp	@24@357
@24@527:
   	mov	 ax, di
	shr	 ax, 2
	mov	 DGROUP:_vr3, ax 
	cmp	word ptr DGROUP:_vr3,3
	jge	short @24@532
	jmp	@24@1355
@24@532:
   	mov	 DGROUP:_vr, 0
	xor	 di, di
	mov	 dx, DGROUP:_vr3
	dec	 dx 
@24@536:
   	mov	 si, DGROUP:_vr
	shl	 si, 2
	fld	 dword ptr [bp-268][si]
	fcomp	 dword ptr DGROUP:_ubyf
	fstsw	 ax
	sahf	
	ja	short @24@544
	jmp	@24@692
@24@544:
   	mov	 bx, si
	mov	 ax, DGROUP:_vr
	sub	 ax, 1
	jnc	short @24@550
	mov	 DGROUP:_pvert, dx
	jmp	short @24@551
@24@550:
     	mov	 DGROUP:_pvert, ax
@24@551:
   	mov	 ax, DGROUP:_vr
	inc	 ax
	cmp	 ax, dx
	jbe	short @24@557
	mov	 DGROUP:_nvert, 0
	jmp	short @24@558
@24@557:
     	mov	 DGROUP:_nvert, ax
@24@558:
   	shl	 DGROUP:_pvert, 2
	shl	 DGROUP:_nvert, 2
	mov	 si, DGROUP:_pvert
	fld	 dword ptr [bp-268][si]
	fcomp	 dword ptr DGROUP:_ubyf
	fstsw	 ax
	sahf	
	jbe	short @24@573
	mov	 si, DGROUP:_nvert
	fld	 dword ptr [bp-268][si]
	fcomp	 dword ptr DGROUP:_ubyf
	fstsw	 ax
	sahf	
	jbe	short @24@573
	jmp	@24@701
@24@573:
   	mov	 si, DGROUP:_pvert
	fld	 dword ptr [bp-268][si]
	fcomp	 dword ptr DGROUP:_ubyf
	fstsw	 ax
	sahf	
	jbe	short @24@580
	jmp	@24@649
@24@580:
   	mov	 si, DGROUP:_nvert
	fld	 dword ptr [bp-268][si]
	fcomp	 dword ptr DGROUP:_ubyf
	fstsw	 ax
	sahf	
	jbe	short @24@587
	jmp	@24@649
@24@587:
   	mov	 si, bx
	fld	 dword ptr [bp-268][si]
	mov	 si, DGROUP:_pvert
	fcomp	 dword ptr [bp-268][si]
	fstsw	 ax
	sahf	
	jne	short @24@595
	jmp	short @24@608
@24@595:
   	fld	 dword ptr DGROUP:_ubyf
	fsub	 dword ptr [bp-268][si]
	fld	 dword ptr [bp-268][si]
	mov	 si, bx
	fsubr	 dword ptr [bp-268][si]
	fdivp	
	fld	 dword ptr [bp-220][si]
	mov	 si, DGROUP:_pvert
	fsub	 dword ptr [bp-220][si]
	fmulp	
	fadd	 dword ptr [bp-220][si]
	fstp	 dword ptr [bp-332][di]
	jmp	short @24@613
@24@608:
   	mov	 si, bx
	db	 066H
	mov	 ax, word ptr [bp-220][si]
	db	 066H
	mov	 word ptr [bp-332][di], ax 
@24@613:
   	db	 066H
	mov	 ax, word ptr DGROUP:_ubyf
	db	 066H
	mov	 word ptr [bp-396][di], ax
	mov	 si, bx
	fld	 dword ptr [bp-268][si]
	mov	 si, DGROUP:_nvert
	fcomp	 dword ptr [bp-268][si]
	fstsw	 ax
	sahf	
	jne	short @24@625
	jmp	short @24@638
@24@625:
   	fld	 dword ptr DGROUP:_ubyf
	fsub	 dword ptr [bp-268][si]
	fld	 dword ptr [bp-268][si]
	mov	 si, bx
	fsubr	 dword ptr [bp-268][si]
	fdivp	
	fld	 dword ptr [bp-220][si]
	mov	 si, DGROUP:_nvert
	fsub	 dword ptr [bp-220][si]
	fmulp	
	fadd	 dword ptr [bp-220][si]
	fstp	 dword ptr [bp-332][di+4]
	jmp	short @24@643
@24@638:
   	mov	 si, bx
	db	 066H
	mov	 ax, word ptr [bp-220][si]
	db	 066H
	mov	 word ptr [bp-332][di+4], ax 
@24@643:
   	db	 066H
	mov	 ax, word ptr DGROUP:_ubyf
	db	 066H
	mov	 word ptr [bp-396][di+4], ax
	add	 di, 8
	jmp	@24@701
@24@649:
   	mov	 si, DGROUP:_pvert
	fld	 dword ptr [bp-268][si]
	fcomp	 dword ptr DGROUP:_ubyf
	fstsw	 ax
	sahf	
	ja	short @24@658
	mov	 ax, DGROUP:_pvert
	mov	 DGROUP:_vvert, ax
	jmp	short @24@660
@24@658:
   	mov	 ax, DGROUP:_nvert
	mov	 DGROUP:_vvert, ax 
@24@660:
   	mov	 si, bx
	fld	 dword ptr [bp-268][si]
	mov	 si, DGROUP:_vvert
	fcomp	 dword ptr [bp-268][si]
	fstsw	 ax
	sahf	
	jne	short @24@668
	jmp	short @24@681
@24@668:
   	fld	 dword ptr DGROUP:_ubyf
	fsub	 dword ptr [bp-268][si]
	fld	 dword ptr [bp-268][si]
	mov	 si, bx
	fsubr	 dword ptr [bp-268][si]
	fdivp	
	fld	 dword ptr [bp-220][si]
	mov	 si, DGROUP:_vvert
	fsub	 dword ptr [bp-220][si]
	fmulp	
	fadd	 dword ptr [bp-220][si]
	fstp	 dword ptr [bp-332][di]
	jmp	short @24@686
@24@681:
   	mov	 si, bx
	db	 066H
	mov	 ax, word ptr [bp-220][si]
	db	 066H
	mov	 word ptr [bp-332][di], ax 
@24@686:
   	db	 066H
	mov	 ax, word ptr DGROUP:_ubyf
	db	 066H
	mov	 word ptr [bp-396][di], ax
	add	 di, 4
	jmp	short @24@701
@24@692:
   	db	 066H
	mov	 ax, word ptr [bp-268][si]
	db	 066H
	mov	 word ptr [bp-396][di], ax
	db	 066H
	mov	 ax, word ptr [bp-220][si]
	db	 066H
	mov	 word ptr [bp-332][di], ax
	add	 di, 4 
@24@701:
   	inc	 DGROUP:_vr
	mov	 ax, DGROUP:_vr
	cmp	 ax, DGROUP:_vr3
	jae	short @24@706
	jmp	@24@536
@24@706:
   	mov	 ax, di
	shr	 ax, 2
	mov	 DGROUP:_vr4, ax 
	cmp	word ptr DGROUP:_vr4,3
	jge	short @24@711
	jmp	@24@1355
@24@711:
   	mov	 DGROUP:_vr, 0
	xor	 di, di
	mov	 dx, DGROUP:_vr4
	dec	 dx 
@24@715:
   	mov	 si, DGROUP:_vr
	shl	 si, 2
	fld	 dword ptr [bp-332][si]
	fcomp	 dword ptr DGROUP:_lbxf
	fstsw	 ax
	sahf	
	jb	short @24@723
	jmp	@24@871
@24@723:
   	mov	 bx, si
	mov	 ax, DGROUP:_vr
	sub	 ax, 1
	jnc	short @24@729
	mov	 DGROUP:_pvert, dx
	jmp	short @24@730
@24@729:
     	mov	 DGROUP:_pvert, ax
@24@730:
   	mov	 ax, DGROUP:_vr
	inc	 ax
	cmp	 ax, dx
	jbe	short @24@736
	mov	 DGROUP:_nvert, 0
	jmp	short @24@737
@24@736:
     	mov	 DGROUP:_nvert, ax
@24@737:
   	shl	 DGROUP:_pvert, 2
	shl	 DGROUP:_nvert, 2
	mov	 si, DGROUP:_pvert
	fld	 dword ptr [bp-332][si]
	fcomp	 dword ptr DGROUP:_lbxf
	fstsw	 ax
	sahf	
	jae	short @24@752
	mov	 si, DGROUP:_nvert
	fld	 dword ptr [bp-332][si]
	fcomp	 dword ptr DGROUP:_lbxf
	fstsw	 ax
	sahf	
	jae	short @24@752
	jmp	@24@880
@24@752:
   	mov	 si, DGROUP:_pvert
	fld	 dword ptr [bp-332][si]
	fcomp	 dword ptr DGROUP:_lbxf
	fstsw	 ax
	sahf	
	jae	short @24@759
	jmp	@24@828
@24@759:
   	mov	 si, DGROUP:_nvert
	fld	 dword ptr [bp-332][si]
	fcomp	 dword ptr DGROUP:_lbxf
	fstsw	 ax
	sahf	
	jae	short @24@766
	jmp	@24@828
@24@766:
   	mov	 si, bx
	fld	 dword ptr [bp-332][si]
	mov	 si, DGROUP:_pvert
	fcomp	 dword ptr [bp-332][si]
	fstsw	 ax
	sahf	
	jne	short @24@774
	jmp	short @24@787
@24@774:
   	fld	 dword ptr DGROUP:_lbxf
	fsub	 dword ptr [bp-332][si]
	fld	 dword ptr [bp-332][si]
	mov	 si, bx
	fsubr	 dword ptr [bp-332][si]
	fdivp	
	fld	 dword ptr [bp-396][si]
	mov	 si, DGROUP:_pvert
	fsub	 dword ptr [bp-396][si]
	fmulp	
	fadd	 dword ptr [bp-396][si]
	fstp	 dword ptr [bp-588][di]
	jmp	short @24@792
@24@787:
   	mov	 si, bx
	db	 066H
	mov	 ax, word ptr [bp-396][si]
	db	 066H
	mov	 word ptr [bp-588][di], ax 
@24@792:
   	db	 066H
	mov	 ax, word ptr DGROUP:_lbxf
	db	 066H
	mov	 word ptr [bp-492][di], ax
	mov	 si, bx
	fld	 dword ptr [bp-332][si]
	mov	 si, DGROUP:_nvert
	fcomp	 dword ptr [bp-332][si]
	fstsw	 ax
	sahf	
	jne	short @24@804
	jmp	short @24@817
@24@804:
   	fld	 dword ptr DGROUP:_lbxf
	fsub	 dword ptr [bp-332][si]
	fld	 dword ptr [bp-332][si]
	mov	 si, bx
	fsubr	 dword ptr [bp-332][si]
	fdivp	
	fld	 dword ptr [bp-396][si]
	mov	 si, DGROUP:_nvert
	fsub	 dword ptr [bp-396][si]
	fmulp	
	fadd	 dword ptr [bp-396][si]
	fstp	 dword ptr [bp-588][di+4]
	jmp	short @24@822
@24@817:
   	mov	 si, bx
	db	 066H
	mov	 ax, word ptr [bp-396][si]
	db	 066H
	mov	 word ptr [bp-588][di+4], ax 
@24@822:
   	db	 066H
	mov	 ax, word ptr DGROUP:_lbxf
	db	 066H
	mov	 word ptr [bp-492][di+4], ax
	add	 di, 8
	jmp	@24@880
@24@828:
   	mov	 si, DGROUP:_pvert
	fld	 dword ptr [bp-332][si]
	fcomp	 dword ptr DGROUP:_lbxf
	fstsw	 ax
	sahf	
	jb	short @24@837
	mov	 ax, DGROUP:_pvert
	mov	 DGROUP:_vvert, ax
	jmp	short @24@839
@24@837:
   	mov	 ax, DGROUP:_nvert
	mov	 DGROUP:_vvert, ax 
@24@839:
   	mov	 si, bx
	fld	 dword ptr [bp-332][si]
	mov	 si, DGROUP:_vvert
	fcomp	 dword ptr [bp-332][si]
	fstsw	 ax
	sahf	
	jne	short @24@847
	jmp	short @24@860
@24@847:
   	fld	 dword ptr DGROUP:_lbxf
	fsub	 dword ptr [bp-332][si]
	fld	 dword ptr [bp-332][si]
	mov	 si, bx
	fsubr	 dword ptr [bp-332][si]
	fdivp	
	fld	 dword ptr [bp-396][si]
	mov	 si, DGROUP:_vvert
	fsub	 dword ptr [bp-396][si]
	fmulp	
	fadd	 dword ptr [bp-396][si]
	fstp	 dword ptr [bp-588][di]
	jmp	short @24@865
@24@860:
   	mov	 si, bx
	db	 066H
	mov	 ax, word ptr [bp-396][si]
	db	 066H
	mov	 word ptr [bp-588][di], ax 
@24@865:
   	db	 066H
	mov	 ax, word ptr DGROUP:_lbxf
	db	 066H
	mov	 word ptr [bp-492][di], ax
	add	 di, 4
	jmp	short @24@880
@24@871:
   	db	 066H
	mov	 ax, word ptr [bp-332][si]
	db	 066H
	mov	 word ptr [bp-492][di], ax
	db	 066H
	mov	 ax, word ptr [bp-396][si]
	db	 066H
	mov	 word ptr [bp-588][di], ax
	add	 di, 4 
@24@880:
   	inc	 DGROUP:_vr
	mov	 ax, DGROUP:_vr
	cmp	 ax, DGROUP:_vr4
	jae	short @24@885
	jmp	@24@715
@24@885:
   	mov	 ax, di
	shr	 ax, 2
	mov	 DGROUP:_vr5, ax 
	cmp	word ptr DGROUP:_vr5,3
	jge	short @24@890
	jmp	@24@1355
@24@890:
   	mov	 DGROUP:_vr, 0
	xor	 di, di 
	mov	 dx, DGROUP:_vr5
	dec	 dx 
@24@894:
   	mov	 si, DGROUP:_vr
	shl	 si, 2
	fld	 dword ptr [bp-492][si]
	fcomp	 dword ptr DGROUP:_ubxf
	fstsw	 ax
	sahf	
	ja	short @24@902
	jmp	@24@1038
@24@902:
   	mov	 bx, si 
	mov	 ax, DGROUP:_vr
	sub	 ax, 1
	jnc	short @24@908
	mov	 DGROUP:_pvert, dx
	jmp	short @24@909
@24@908:
     	mov	 DGROUP:_pvert, ax
@24@909:
   	mov	 ax, DGROUP:_vr
	inc	 ax
	cmp	 ax, dx
	jbe	short @24@915
	mov	 DGROUP:_nvert, 0
	jmp	short @24@916
@24@915:
     	mov	 DGROUP:_nvert, ax
@24@916:
   	shl	 DGROUP:_pvert, 2
	shl	 DGROUP:_nvert, 2
	mov	 si, DGROUP:_pvert
	fld	 dword ptr [bp-492][si]
	fcomp	 dword ptr DGROUP:_ubxf
	fstsw	 ax
	sahf	
	jbe	short @24@931
	mov	 si, DGROUP:_nvert
	fld	 dword ptr [bp-492][si]
	fcomp	 dword ptr DGROUP:_ubxf
	fstsw	 ax
	sahf	
	jbe	short @24@931
	jmp	@24@1043
@24@931:
   	mov	 si, DGROUP:_pvert
	fld	 dword ptr [bp-492][si]
	fcomp	 dword ptr DGROUP:_ubxf
	fstsw	 ax
	sahf	
	jbe	short @24@938
	jmp	@24@999
@24@938:
   	mov	 si, DGROUP:_nvert
	fld	 dword ptr [bp-492][si]
	fcomp	 dword ptr DGROUP:_ubxf
	fstsw	 ax
	sahf	
	jbe	short @24@945
	jmp	@24@999
@24@945:
   	mov	 si, bx
	fld	 dword ptr [bp-492][si]
	mov	 si, DGROUP:_pvert
	fcomp	 dword ptr [bp-492][si]
	fstsw	 ax
	sahf	
	jne	short @24@953
	jmp	short @24@966
@24@953:
   	fld	 dword ptr DGROUP:_ubxf
	fsub	 dword ptr [bp-492][si]
	fld	 dword ptr [bp-492][si]
	mov	 si, bx
	fsubr	 dword ptr [bp-492][si]
	fdivp	
	fld	 dword ptr [bp-588][si]
	mov	 si, DGROUP:_pvert
	fsub	 dword ptr [bp-588][si]
	fmulp	
	fadd	 dword ptr [bp-588][si]
	fistp	 dword ptr DGROUP:_mp[di+4]
	jmp	short @24@969
@24@966:
   	mov	 si, bx
	fld	 dword ptr [bp-588][si]
	fistp	 dword ptr DGROUP:_mp[di+4] 
@24@969:
   	mov	 word ptr DGROUP:_mp[di], 306/2 + 158
	mov	 word ptr DGROUP:_mp[di+2], 0
	mov	 si, bx
	fld	 dword ptr [bp-492][si]
	mov	 si, DGROUP:_nvert
	fcomp	 dword ptr [bp-492][si]
	fstsw	 ax
	sahf	
	jne	short @24@979
	jmp	short @24@992
@24@979:
   	fld	 dword ptr DGROUP:_ubxf
	fsub	 dword ptr [bp-492][si]
	fld	 dword ptr [bp-492][si]
	mov	 si, bx
	fsubr	 dword ptr [bp-492][si]
	fdivp	
	fld	 dword ptr [bp-588][si]
	mov	 si, DGROUP:_nvert
	fsub	 dword ptr [bp-588][si]
	fmulp	
	fadd	 dword ptr [bp-588][si]
	fistp	 dword ptr DGROUP:_mp[di+12]
	jmp	short @24@995
@24@992:
   	mov	 si, bx
	fld	 dword ptr [bp-588][si]
	fistp	 dword ptr DGROUP:_mp[di+12] 
@24@995:
   	mov	 word ptr DGROUP:_mp[di+8], 306/2 + 158
	mov	 word ptr DGROUP:_mp[di+10], 0
	add	 di, 16
	jmp	@24@1043
@24@999:
   	mov	 si, DGROUP:_pvert
	fld	 dword ptr [bp-492][si]
	fcomp	 dword ptr DGROUP:_ubxf
	fstsw	 ax
	sahf	
	ja	short @24@1008
	mov	 ax, DGROUP:_pvert
	mov	 DGROUP:_vvert, ax
	jmp	short @24@1010
@24@1008:
   	mov	 ax, DGROUP:_nvert
	mov	 DGROUP:_vvert, ax 
@24@1010:
   	mov	 si, bx
	fld	 dword ptr [bp-492][si]
	mov	 si, DGROUP:_vvert
	fcomp	 dword ptr [bp-492][si]
	fstsw	 ax
	sahf	
	jne	short @24@1018
	jmp	short @24@1031
@24@1018:
   	fld	 dword ptr DGROUP:_ubxf
	fsub	 dword ptr [bp-492][si]
	fld	 dword ptr [bp-492][si]
	mov	 si, bx
	fsubr	 dword ptr [bp-492][si]
	fdivp	
	fld	 dword ptr [bp-588][si]
	mov	 si, DGROUP:_vvert
	fsub	 dword ptr [bp-588][si]
	fmulp	
	fadd	 dword ptr [bp-588][si]
	fistp	 dword ptr DGROUP:_mp[di+4]
	jmp	short @24@1034
@24@1031:
   	mov	 si, bx
	fld	 dword ptr [bp-588][si]
	fistp	 dword ptr DGROUP:_mp[di+4] 
@24@1034:
   	mov	 word ptr DGROUP:_mp[di], 306/2 + 158
	mov	 word ptr DGROUP:_mp[di+2], 0
	add	 di, 8
	jmp	short @24@1043
@24@1038:
   	fld	 dword ptr [bp-492][si]
	fistp	 dword ptr DGROUP:_mp[di]
	fld	 dword ptr [bp-588][si]
	fistp	 dword ptr DGROUP:_mp[di+4]
	add	 di, 8 
@24@1043:
   	inc	 DGROUP:_vr
	mov	 ax, DGROUP:_vr
	cmp	 ax, DGROUP:_vr5
	jae	short @24@1048
	jmp	@24@894
@24@1048:
   	mov	 [bp-2], di
	sub	 [bp-2], 8
	shr	 di, 3
	mov	 DGROUP:_vr6, di 
	cmp	word ptr DGROUP:_vr6,3
	jge	short @24@1054
	jmp	@24@1355
@24@1054:
	cmp	byte ptr DGROUP:_flares,0
	jne	short @24@1062
	mov	ax,word ptr DGROUP:_min_y
	cmp	ax,word ptr DGROUP:_max_y
	jne	short @24@1062
	mov	ax,word ptr DGROUP:_min_x
	cmp	ax,word ptr DGROUP:_max_x
	jne	short @24@1058
	mov	bx,word ptr DGROUP:_min_y
	add	bx,bx
	mov	ax,word ptr DGROUP:_riga[bx]
	add	ax,word ptr DGROUP:_min_x
	les	bx,dword ptr DGROUP:_adapted
	add	bx,ax
	mov	al,byte ptr [bp+20]
	mov	byte ptr es:[bx],al
	jmp	@24@1355
@24@1058:
	mov	bx,word ptr DGROUP:_min_y
	add	bx,bx
	mov	ax,word ptr DGROUP:_riga[bx]
	add	ax,word ptr DGROUP:_max_x
	mov	word ptr DGROUP:_ptr,ax
	jmp	short @24@1060
@24@1059:
	les	bx,dword ptr DGROUP:_adapted
	add	bx,word ptr DGROUP:_ptr
	mov	al,byte ptr [bp+20]
	mov	byte ptr es:[bx],al
	dec	word ptr DGROUP:_max_x
	dec	word ptr DGROUP:_ptr
@24@1060:
	mov	ax,word ptr DGROUP:_max_x
	cmp	ax,word ptr DGROUP:_min_x
	jae	short @24@1059
	jmp	@24@1355
@24@1062:
     	xor	 si, si
@24@1063:
   	db	 066H
	mov	 ax, word ptr DGROUP:_mp[si]
	db	 066H
	mov	 word ptr DGROUP:_xp, ax
	db	 066H
	mov	 ax, word ptr DGROUP:_mp[si+4]
	db	 066H
	mov	 word ptr DGROUP:_yp, ax
	db	 066H
	mov	 ax, word ptr DGROUP:_mp[si+8]
	db	 066H
	mov	 word ptr DGROUP:_xa, ax
	db	 066H
	mov	 ax, word ptr DGROUP:_mp[si+12]
	db	 066H
	mov	 word ptr DGROUP:_ya, ax
	push	 si 
	push	cs
	call	near ptr @Segmento$qv
   	pop	 si
	add	 si, 8
	cmp	 si, [bp-2]
	jb	short @24@1063
	db	 066H
	mov	 ax, word ptr DGROUP:_mp[si]
	db	 066H
	mov	 word ptr DGROUP:_xp, ax
	db	 066H
	mov	 ax, word ptr DGROUP:_mp[si+4]
	db	 066H
	mov	 word ptr DGROUP:_yp, ax
	db	 066H
	mov	 ax, word ptr DGROUP:_mp[0]
	db	 066H
	mov	 word ptr DGROUP:_xa, ax
	db	 066H
	mov	 ax, word ptr DGROUP:_mp[4]
	db	 066H
	mov	 word ptr DGROUP:_ya, ax 
	push	cs
	call	near ptr @Segmento$qv
   	mov	 si, DGROUP:_min_y
	mov	 ax, DGROUP:_min_x
	add	 si, si
	mov	 di, DGROUP:_max_y
	add	 ax, word ptr DGROUP:_riga[si]
	mov	 bx, DGROUP:_min_x
	add	 di, di
	mov	 [bp-6], ax
	add	 bx, word ptr DGROUP:_riga[di]
	mov	 [bp-8], bx
	add	 ax, DGROUP:_max_x
	sub	 ax, DGROUP:_min_x
	mov	 [bp-10], ax
	sub	 ax, [bp-6]
	add	 ax, 2
	mov	 [bp-12], ax 
 	cld	
	mov	al,byte ptr DGROUP:_flares
	cbw	
	mov	bx,ax
	cmp	bx,4
	ja	@24@1355
	add	bx,bx
	jmp	word ptr cs:@24@C1566[bx]
@24@1122:
   	pusha	
	les	 di, dword ptr DGROUP:_adapted
	add	 [bp-8], di
	add	 di, [bp-6]
	mov	 al, [bp+20]
	mov	 ah, [bp+20]
	db	 066H 
	db	 0c1H
	db	 0e0H
	db	 010H
	mov	 ah, [bp+20] 
@24@1133:
   	push	 di
	mov	 cx, [bp-12]
	mov	 al, 255
	repne scasb	
	jne	short @24@1168
	mov	 si, di
	repe scasb	
	mov	 bx, di
	repne scasb	
	jne	short @24@1161
	repe scasb	
	dec	 di
	dec	 si
	mov	 al, [bp+20]
	mov	 dx, di
	sub	 dx, si
	mov	 di, si
	mov	 cx, dx
	shr	 cx, 2
	je	short @24@1157
@24@1153:
   	db	 026H, 066H, 089H, 005H 
	add	 di, 4
	dec	 cx
	jne	short @24@1153
@24@1157:
   	mov	 cl, dl
	and	 cl, 3
	rep stosb	
	jmp	short @24@1168
@24@1161:
   	dec	 si
	dec	 bx
	mov	 cx, bx
	mov	 al, [bp+20]
	sub	 cx, si
	mov	 di, si
	rep stosb	 
@24@1168:
   	pop	 di
	add	 di, 320
	cmp	 di, [bp-8]
	jbe	short @24@1133
	popa	 
	jmp	@24@1355
@24@1174:
   	les	 di, dword ptr DGROUP:_adapted
	add	 [bp-8], di
	add	 di, [bp-6]
	mov	 al, [bp+20]
	and	 al, 03FH
	mov	 [bp+20], al 
@24@1180:
   	push	 di
	mov	 cx, [bp-12]
	mov	 al, 255
	repne scasb	
	jne	short @24@1224
	mov	 si, di
	repe scasb	
	mov	 bx, di
	repne scasb	
	jne	short @24@1207
	repe scasb	
	dec	 di
	dec	 si
	mov	 cx, di
	sub	 cx, si
	mov	 di, si 
@24@1196:
   	mov	 al, es:[di-1]
	and	 al, 03FH
	add	 al, [bp+20]
	cmp	 al, 62
	jb	short @24@1202
	mov	 al, 62 
@24@1202:
   	mov	 es:[di], al
	inc	 di
	dec	 cx
	jne	short @24@1196
	jmp	short @24@1224
@24@1207:
   	dec	 si
	dec	 bx
	mov	 cx, bx
	sub	 cx, si
	mov	 di, si
	mov	 dl, [bp+20]
	shr	 dl, 1 
@24@1214:
   	mov	 al, es:[di-1]
	and	 al, 03FH
	add	 al, dl
	cmp	 al, 62
	jb	short @24@1220
	mov	 al, 62 
@24@1220:
   	mov	 es:[di], al
	inc	 di
	dec	 cx
	jne	short @24@1214
@24@1224:
   	pop	 di
	add	 di, 320
	cmp	 di, [bp-8]
	jbe	short @24@1180
	jmp	@24@1355
@24@1229:
   	push	 ds
	les	 ax, dword ptr DGROUP:_adapted
	lds	 di, dword ptr DGROUP:_adapted
	add	 [bp-8], di
	add	 di, [bp-6] 
@24@1234:
   	mov	 al, 0FFH
	push	 di
	mov	 cx, [bp-12]
	repne scasb	
	jne	short @24@1284
	mov	 si, di
	repe scasb	
	mov	 bx, di
	repne scasb	
	jne	short @24@1269
	repe scasb	
	dec	 di
	dec	 si
	mov	 cx, di
	sub	 cx, si
	mov	 di, si 
@24@1250:
   	cmp	 byte ptr [di], 0FFH
	jne	short @24@1257
	mov	 ah, [di-321]
	and	 ah, 03FH
	or	 ah, 040H
	mov	 [di], ah
	jmp	short @24@1265
@24@1257:
   	mov	 al, [di]
	and	 ax, 03FH
	or	  al, 040H
	add	 ax, cx
	cmp	 ax, 128
	jb	short @24@1264
	mov	 al, 127 
@24@1264:
 	mov	 [di], al
@24@1265:
   	inc	 di
	dec	 cx
	jne	short @24@1250
	jmp	short @24@1284
@24@1269:
   	dec	 si
	dec	 bx
	mov	 cx, bx
	sub	 cx, si
	mov	 di, si 
@24@1274:
   	mov	 ah, [di-321]
	cmp	 ah, 0FFH
	jne	short @24@1278
	mov	 ah, [di-642] 
@24@1278:
   	and	 ah, 03FH
	or	 ah, 040H
	mov	 [di], ah
	inc	 di
	dec	 cx
	jne	short @24@1274
@24@1284:
   	pop	 di
	add	 di, 320
	cmp	 di, [bp-8]
	ja	short @24@1289
	jmp	@24@1234
@24@1289:
 	pop	 ds
	jmp	@24@1355
@24@1291:
   	pusha	
	les	 di, dword ptr DGROUP:_adapted
	add	 [bp-8], di
	add	 di, [bp-6] 
@24@1295:
   	mov	 al, [bp+20]
	mov	 ah, [bp+20]
	db	 066H 
	db	 0c1H
	db	 0e0H
	db	 010H
	mov	 ah, [bp+20]
	push	 di
	mov	 cx, [bp-12]
	mov	 al, 255
	repne scasb	
	jne	short @24@1337
	mov	 si, di
	repe scasb	
	mov	 bx, di
	repne scasb	
	jne	short @24@1330
	repe scasb	
	dec	 di
	dec	 si
	mov	 al, [bp+20]
	mov	 dx, di
	sub	 dx, si
	mov	 di, si
	mov	 cx, dx
	shr	 cx, 2
	je	short @24@1326
@24@1322:
   	db	 026H, 066H, 089H, 005H 
	add	 di, 4
	dec	 cx
	jne	short @24@1322
@24@1326:
   	mov	 cl, dl
	and	 cl, 3
	rep stosb	
	jmp	short @24@1337
@24@1330:
   	dec	 si
	dec	 bx
	mov	 cx, bx
	mov	 al, [bp+20]
	sub	 cx, si
	mov	 di, si
	rep stosb	 
@24@1337:
   	mov	 al, [bp+20]
	mov	 ah, [bp+20]
	and	 al, 03FH
	and	 ah, 0C0H
	add	 al, [bp-3]
	cmp	 al, 03FH
	jbe	short @24@1348
	mov	 al, 03FH
	test	 [bp-3], 080H
	je	short @24@1348
	xor	 al, al 
@24@1348:
   	or	  al, ah
	mov	 [bp+20], al
	pop	 di
	add	 di, 320
	cmp	 di, [bp-8]
	jbe	short @24@1295
	popa	 
@24@1355:
	pop	di
	pop	si
	leave	
	ret	
@poly3d$qnft1t1uiuc	endp
@24@C1566	label	word
	dw	@24@1122
	dw	@24@1174
	dw	@24@1229
	dw	@24@1355
	dw	@24@1291
NOCTIS-0_TEXT	ends
_BSS	segment word public use16 'BSS'
_txtr	label	dword
	db	4 dup (?)
_BSS	ends
NOCTIS-0_TEXT	segment byte public use16 'CODE'
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@init_texture_mapping$qv	proc	far
	push	large 0003F003Fh
	call	far ptr __control87
	add	sp,4
	push	large 000010010h
	call	far ptr _farmalloc
	add	sp,4
	mov	word ptr DGROUP:_txtr+2,dx
	mov	word ptr DGROUP:_txtr,ax
	or	ax,word ptr DGROUP:_txtr+2
	je	short @25@2
	mov	al,1
	ret	
@25@2:
	mov	al,0
	ret	
@init_texture_mapping$qv	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@load_texture$qncl	proc	far
	push	bp
	mov	bp,sp
	sub	sp,4
	push	si
	push	di
	push	0
	push	dword ptr [bp+6]
	call	far ptr __rtl_open
	add	sp,6
	mov	si,ax
	cmp	si,-1
	jle	short @26@12
	cmp	dword ptr [bp+10],large 0
	jl	short @26@4
	push	0
	jmp	short @26@5
@26@4:
	push	2
@26@5:
	push	dword ptr [bp+10]
	push	si
	call	far ptr _lseek
	add	sp,8
	xor	di,di
	mov	dword ptr [bp-4],large 12
	jmp	short @26@8
@26@7:
	push	256
	mov	dx,word ptr DGROUP:_txtr+2
	mov	ax,word ptr DGROUP:_txtr
	mov	cx,word ptr [bp-2]
	mov	bx,word ptr [bp-4]
	call	far ptr F_PADD@
	push	dx
	push	ax
	push	si
	call	far ptr __rtl_read
	add	sp,8
	add	dword ptr [bp-4],large 256
	inc	di
@26@8:
	cmp	di,256
	jge	short @26@10
	push	si
	call	far ptr _eof
	add	sp,2
	or	ax,ax
	je	short @26@7
@26@10:
	push	si
	call	far ptr __rtl_close
	add	sp,2
	cmp	di,256
	jne	short @26@12
	mov	al,1
	jmp	short @26@13
@26@12:
	mov	al,0
@26@13:
	pop	di
	pop	si
	leave	
	ret	
@load_texture$qncl	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@fast_load_texture$qnc	proc	far
	push	bp
	mov	bp,sp
	sub	sp,4
	push	si
	push	0
	push	dword ptr [bp+6]
	call	far ptr __rtl_open
	add	sp,6
	mov	si,ax
	cmp	si,-1
	jle	short @27@4
	mov	dword ptr [bp-4],large 12
	push	-32768
	mov	dx,word ptr DGROUP:_txtr+2
	mov	ax,word ptr DGROUP:_txtr
	mov	cx,word ptr [bp-2]
	mov	bx,word ptr [bp-4]
	call	far ptr F_PADD@
	push	dx
	push	ax
	push	si
	call	far ptr __rtl_read
	add	sp,8
	add	dword ptr [bp-4],large 08000h
	push	-32768
	mov	dx,word ptr DGROUP:_txtr+2
	mov	ax,word ptr DGROUP:_txtr
	mov	cx,word ptr [bp-2]
	mov	bx,word ptr [bp-4]
	call	far ptr F_PADD@
	push	dx
	push	ax
	push	si
	call	far ptr __rtl_read
	add	sp,8
	push	si
	call	far ptr __rtl_close
	add	sp,2
	mov	al,1
	jmp	short @27@5
@27@4:
	mov	al,0
@27@5:
	pop	si
	leave	
	ret	
@fast_load_texture$qnc	endp
NOCTIS-0_TEXT	ends
_DATA	segment word public use16 'DATA'
	db	1 dup (0)
_xl	label	word
	db	158
	db	0
_yl	label	word
	db	100
	db	0
_aspect	label	word
	db	8
	db	0
_fallout	label	word
	db	20
	db	0
_lt_range	label	word
	db	30
	db	0
_absorption	label	word
	db	45
	db	0
_shadymask	label	byte
	db	1
	db	1 dup (0)
_shady_aux	label	word
	db	0
	db	0
_DATA	ends
_BSS	segment word public use16 'BSS'
_xsh	label	word
	db	2 dup (?)
_ysh	label	word
	db	2 dup (?)
_ksh	label	word
	db	2 dup (?)
_pnx	label	dword
	db	4 dup (?)
_pny	label	dword
	db	4 dup (?)
_pnz	label	dword
	db	4 dup (?)
_BSS	ends
NOCTIS-0_TEXT	segment byte public use16 'CODE'
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@pnorm$qnft1t1	proc	far
	push	bp
	mov	bp,sp
	sub	sp,42
	les	bx,dword ptr [bp+6]
	fld	dword ptr es:[bx+8]
	les	bx,dword ptr [bp+6]
	fsubr	dword ptr es:[bx]
	fstp	dword ptr [bp-4]
	fwait	
	les	bx,dword ptr [bp+10]
	fld	dword ptr es:[bx+8]
	les	bx,dword ptr [bp+10]
	fsubr	dword ptr es:[bx]
	fstp	dword ptr [bp-8]
	fwait	
	les	bx,dword ptr [bp+14]
	fld	dword ptr es:[bx+8]
	les	bx,dword ptr [bp+14]
	fsubr	dword ptr es:[bx]
	fstp	dword ptr [bp-12]
	fwait	
	les	bx,dword ptr [bp+6]
	fld	dword ptr es:[bx+4]
	les	bx,dword ptr [bp+6]
	fsub	dword ptr es:[bx+8]
	fstp	dword ptr [bp-16]
	fwait	
	les	bx,dword ptr [bp+10]
	fld	dword ptr es:[bx+4]
	les	bx,dword ptr [bp+10]
	fsub	dword ptr es:[bx+8]
	fstp	dword ptr [bp-20]
	fwait	
	les	bx,dword ptr [bp+14]
	fld	dword ptr es:[bx+4]
	les	bx,dword ptr [bp+14]
	fsub	dword ptr es:[bx+8]
	fstp	dword ptr [bp-24]
	fld	dword ptr [bp-8]
	fmul	dword ptr [bp-24]
	fld	dword ptr [bp-20]
	fmul	dword ptr [bp-12]
	fsub	
	fstp	dword ptr [bp-28]
	fld	dword ptr [bp-12]
	fmul	dword ptr [bp-16]
	fld	dword ptr [bp-24]
	fmul	dword ptr [bp-4]
	fsub	
	fstp	dword ptr [bp-32]
	fld	dword ptr [bp-4]
	fmul	dword ptr [bp-20]
	fld	dword ptr [bp-16]
	fmul	dword ptr [bp-8]
	fsub	
	fstp	dword ptr [bp-36]
	fld	dword ptr [bp-28]
	fmul	dword ptr [bp-28]
	fld	dword ptr [bp-32]
	fmul	dword ptr [bp-32]
	fadd	
	fld	dword ptr [bp-36]
	fmul	dword ptr [bp-36]
	fadd	
	sub	sp,8
	fstp	qword ptr [bp-50]
	fwait	
	call	far ptr _sqrt
	add	sp,8
	fstp	dword ptr [bp-40]
	fld	dword ptr [bp-40]
	fldz	
	fcompp
	fstsw	word ptr [bp-42]
	fwait	
	mov	ax,word ptr [bp-42]
	sahf	
	jae	short @28@3
	fld1	
	fdiv	dword ptr [bp-40]
	fstp	dword ptr [bp-40]
	fld	dword ptr [bp-28]
	fmul	dword ptr [bp-40]
	fstp	dword ptr DGROUP:_pnx
	fld	dword ptr [bp-32]
	fmul	dword ptr [bp-40]
	fstp	dword ptr DGROUP:_pny
	fld	dword ptr [bp-36]
	fmul	dword ptr [bp-40]
	fstp	dword ptr DGROUP:_pnz
	fwait	
	leave	
	ret	
@28@3:
	mov	dword ptr DGROUP:_pnx,large 0
	mov	dword ptr DGROUP:_pny,large 0
	mov	dword ptr DGROUP:_pnz,large 0
	leave	
	ret	
@pnorm$qnft1t1	endp
NOCTIS-0_TEXT	ends
_DATA	segment word public use16 'DATA'
__0	label	dword
	db	0
	db	0
	db	0
	db	0
__16	label	dword
	db	0
	db	0
	db	128
	db	65
_x_antialias	label	dword
	db	0
	db	0
	db	144
	db	63
_y_antialias	label	dword
	db	0
	db	0
	db	144
	db	63
_z_antialias	label	dword
	db	0
	db	0
	db	144
	db	63
_culling_needed	label	byte
	db	0
_halfscan_needed	label	byte
	db	0
_escrescenze	label	byte
	db	224
_DATA	ends
NOCTIS-0_TEXT	segment byte public use16 'CODE'
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@polymap$qnft1t1cuc	proc	far
	push	bp
	mov	bp,sp
	sub	sp,1146
	push	si
	push	di
	mov	eax,dword ptr DGROUP:_XSIZE
	mov	dword ptr [bp-8],eax
	fild	dword ptr [bp-8]
	fstp	dword ptr [bp-4]
	fwait	
	mov	eax,dword ptr DGROUP:_YSIZE
	mov	dword ptr [bp-8],eax
	fild	dword ptr [bp-8]
	fstp	dword ptr [bp-12]
	fwait	
	mov	al,byte ptr DGROUP:_flares
	mov	byte ptr [bp-13],al
	mov	dword ptr [bp-18],large 03F800000h
	mov	al,byte ptr DGROUP:_culling_needed
	mov	byte ptr [bp-19],al
	mov	al,byte ptr DGROUP:_halfscan_needed
	mov	byte ptr [bp-20],al
	mov	dword ptr [bp-34],large -10000
	mov	dword ptr [bp-38],large 10000
	mov	al,byte ptr [bp+18]
	cbw	
	cmp	ax,3
	jne	short @29@3
	les	bx,dword ptr [bp+6]
	fld	dword ptr es:[bx+8]
	les	bx,dword ptr [bp+6]
	fstp	dword ptr es:[bx+12]
	fwait	
	les	bx,dword ptr [bp+10]
	fld	dword ptr es:[bx+8]
	les	bx,dword ptr [bp+10]
	fstp	dword ptr es:[bx+12]
	fwait	
	les	bx,dword ptr [bp+14]
	fld	dword ptr es:[bx+8]
	les	bx,dword ptr [bp+14]
	fstp	dword ptr es:[bx+12]
	fwait	
@29@3:
 	mov	 DGROUP:_doflag, 0
	db	 066H
	mov	 ax, word ptr DGROUP:__0
	db	 066H
	cmp	 ax, word ptr DGROUP:_gamma
	jne	short @29@10
	jmp	@29@69
@29@10:
   	xor	 di, di
	xor	 si, si 
@29@12:
   	les	 bx, dword ptr [bp+14]
	fld	 dword ptr es:[bx+si]
	fsub	 DGROUP:_cam_z
	fst	 [bp-194]
	fmul	 DGROUP:_opt_tsinbeta
	les	 bx, dword ptr [bp+6]
	fld	 dword ptr es:[bx+si]
	fsub	 DGROUP:_cam_x
	fst	 [bp-186]
	fmul	 DGROUP:_opt_tcosbeta
	faddp	
	fstp	 dword ptr DGROUP:_rxf[si]
	fld	 [bp-194]
	fmul	 DGROUP:_opt_tcosbeta
	fld	 [bp-186]
	fmul	 DGROUP:_opt_tsinbeta
	fsubp	
	fst	 DGROUP:_z2
	fmul	 DGROUP:_opt_tcosalfa
	les	 bx, dword ptr [bp+10]
	fld	 dword ptr es:[bx+si]
	fsub	 DGROUP:_cam_y
	fst	 [bp-190]
	fmul	 DGROUP:_opt_tsinalfa
	faddp	
	fst	 dword ptr DGROUP:_rzf[si]
	fcomp	 DGROUP:_uneg
	fstsw	 ax
	fld	 [bp-190]
	fmul	 DGROUP:_opt_tcosalfa
	fld	 DGROUP:_z2
	fmul	 DGROUP:_opt_tsinalfa
	fsubp	
	fst	 [bp-166]
	fmul	 DGROUP:_opt_tcosgamma
	fld	 dword ptr DGROUP:_rxf[si]
	fmul	 DGROUP:_opt_tsingamma
	fsubp	
	fstp	 dword ptr DGROUP:_ryf[si]
	fld	 [bp-166]
	fmul	 DGROUP:_opt_tsingamma
	fld	 dword ptr DGROUP:_rxf[si]
	fmul	 DGROUP:_opt_tcosgamma
	faddp	
	fstp	 dword ptr DGROUP:_rxf[si]
	sahf	
	jb	short @29@62
	inc	 DGROUP:_doflag
	mov	 byte ptr DGROUP:_rwf[di], 1
	jmp	short @29@63
@29@62:
     	mov	 byte ptr DGROUP:_rwf[di], 0
@29@63:
   	add	 si, 4
	inc	 di
	cmp	 di, 4
	je	short @29@68
	jmp	@29@12
@29@68:
	jmp	@29@116
@29@69:
   	xor	 di, di
	xor	 si, si 
@29@71:
   	les	 bx, dword ptr [bp+14]
	fld	 dword ptr es:[bx+si]
	fsub	 DGROUP:_cam_z
	fst	 [bp-194]
	fmul	 DGROUP:_opt_tsinbeta
	les	 bx, dword ptr [bp+6]
	fld	 dword ptr es:[bx+si]
	fsub	 DGROUP:_cam_x
	fst	 [bp-186]
	fmul	 DGROUP:_opt_tcosbeta
	faddp	
	fstp	 dword ptr DGROUP:_rxf[si]
	fld	 [bp-194]
	fmul	 DGROUP:_opt_tcosbeta
	fld	 [bp-186]
	fmul	 DGROUP:_opt_tsinbeta
	fsubp	
	fst	 DGROUP:_z2
	fmul	 DGROUP:_opt_tcosalfa
	les	 bx, dword ptr [bp+10]
	fld	 dword ptr es:[bx+si]
	fsub	 DGROUP:_cam_y
	fst	 [bp-190]
	fmul	 DGROUP:_opt_tsinalfa
	faddp	
	fst	 dword ptr DGROUP:_rzf[si]
	fcomp	 DGROUP:_uneg
	fstsw	 ax
	fld	 [bp-190]
	fmul	 DGROUP:_opt_tcosalfa
	fld	 DGROUP:_z2
	fmul	 DGROUP:_opt_tsinalfa
	fsubp	
	fstp	 dword ptr DGROUP:_ryf[si]
	sahf	
	jb	short @29@110
	inc	 DGROUP:_doflag
	mov	 byte ptr DGROUP:_rwf[di], 1
	jmp	short @29@111
@29@110:
     	mov	 byte ptr DGROUP:_rwf[di], 0
@29@111:
   	add	 si, 4
	inc	 di
	cmp	 di, 4
	je	short @29@116
	jmp	@29@71
@29@116:
	cmp	 DGROUP:_doflag, 0
	jne	short @29@119
	jmp	@29@1059
@29@119:
	mov	al,byte ptr [bp+18]
	cbw	
	cmp	ax,3
	jne	@29@125
	fld	dword ptr DGROUP:_rxf
	fadd	dword ptr DGROUP:_rxf+4
	fadd	dword ptr DGROUP:_rxf+8
	fmul	qword ptr DGROUP:s@
	fstp	dword ptr [bp-198]
	fld	dword ptr DGROUP:_ryf
	fadd	dword ptr DGROUP:_ryf+4
	fadd	dword ptr DGROUP:_ryf+8
	fmul	qword ptr DGROUP:s@
	fstp	dword ptr [bp-202]
	fld	dword ptr DGROUP:_rzf
	fadd	dword ptr DGROUP:_rzf+4
	fadd	dword ptr DGROUP:_rzf+8
	fmul	qword ptr DGROUP:s@
	fstp	dword ptr [bp-206]
	fwait	
	mov	word ptr DGROUP:_vr,0
	jmp	@29@123
@29@121:
	mov	bx,word ptr DGROUP:_vr
	shl	bx,2
	lea	ax,word ptr [bp-1114]
	add	bx,ax
	mov	si,word ptr DGROUP:_vr
	shl	si,2
	fld	dword ptr DGROUP:_rxf[si]
	fsub	dword ptr [bp-198]
	fmul	dword ptr DGROUP:_x_antialias
	fadd	dword ptr [bp-198]
	fstp	dword ptr ss:[bx]
	fwait	
	mov	bx,word ptr DGROUP:_vr
	shl	bx,2
	lea	ax,word ptr [bp-1130]
	add	bx,ax
	mov	si,word ptr DGROUP:_vr
	shl	si,2
	fld	dword ptr DGROUP:_ryf[si]
	fsub	dword ptr [bp-202]
	fmul	dword ptr DGROUP:_y_antialias
	fadd	dword ptr [bp-202]
	fstp	dword ptr ss:[bx]
	fwait	
	mov	bx,word ptr DGROUP:_vr
	shl	bx,2
	lea	ax,word ptr [bp-1146]
	add	bx,ax
	mov	si,word ptr DGROUP:_vr
	shl	si,2
	fld	dword ptr DGROUP:_rzf[si]
	fsub	dword ptr [bp-206]
	fmul	dword ptr DGROUP:_z_antialias
	fadd	dword ptr [bp-206]
	fstp	dword ptr ss:[bx]
	fwait	
	inc	word ptr DGROUP:_vr
@29@123:
	cmp	word ptr DGROUP:_vr,3
	jl	@29@121
	mov	si,8
	jmp	@29@130
@29@125:
	fld	dword ptr DGROUP:_rxf
	fadd	dword ptr DGROUP:_rxf+4
	fadd	dword ptr DGROUP:_rxf+8
	fadd	dword ptr DGROUP:_rxf+12
	fmul	dword ptr DGROUP:s@+8
	fstp	dword ptr [bp-198]
	fld	dword ptr DGROUP:_ryf
	fadd	dword ptr DGROUP:_ryf+4
	fadd	dword ptr DGROUP:_ryf+8
	fadd	dword ptr DGROUP:_ryf+12
	fmul	dword ptr DGROUP:s@+8
	fstp	dword ptr [bp-202]
	fld	dword ptr DGROUP:_rzf
	fadd	dword ptr DGROUP:_rzf+4
	fadd	dword ptr DGROUP:_rzf+8
	fadd	dword ptr DGROUP:_rzf+12
	fmul	dword ptr DGROUP:s@+8
	fstp	dword ptr [bp-206]
	fwait	
	mov	word ptr DGROUP:_vr,0
	jmp	@29@128
@29@126:
	mov	bx,word ptr DGROUP:_vr
	shl	bx,2
	lea	ax,word ptr [bp-1114]
	add	bx,ax
	mov	si,word ptr DGROUP:_vr
	shl	si,2
	fld	dword ptr DGROUP:_rxf[si]
	fsub	dword ptr [bp-198]
	fmul	dword ptr DGROUP:_x_antialias
	fadd	dword ptr [bp-198]
	fstp	dword ptr ss:[bx]
	fwait	
	mov	bx,word ptr DGROUP:_vr
	shl	bx,2
	lea	ax,word ptr [bp-1130]
	add	bx,ax
	mov	si,word ptr DGROUP:_vr
	shl	si,2
	fld	dword ptr DGROUP:_ryf[si]
	fsub	dword ptr [bp-202]
	fmul	dword ptr DGROUP:_y_antialias
	fadd	dword ptr [bp-202]
	fstp	dword ptr ss:[bx]
	fwait	
	mov	bx,word ptr DGROUP:_vr
	shl	bx,2
	lea	ax,word ptr [bp-1146]
	add	bx,ax
	mov	si,word ptr DGROUP:_vr
	shl	si,2
	fld	dword ptr DGROUP:_rzf[si]
	fsub	dword ptr [bp-206]
	fmul	dword ptr DGROUP:_z_antialias
	fadd	dword ptr [bp-206]
	fstp	dword ptr ss:[bx]
	fwait	
	inc	word ptr DGROUP:_vr
@29@128:
	cmp	word ptr DGROUP:_vr,4
	jl	@29@126
	mov	si,12
@29@130:
	fld	 dword ptr [bp-1114][0]
	fstp	 [bp-150]
	fld	 dword ptr [bp-1114][4]
	fsub	 [bp-150]
	fstp	 [bp-162]
	fld	 [bp-150]
	fsub	 dword ptr [bp-1114][si]
	fstp	 [bp-174]
	fld	 dword ptr [bp-1130][0]
	fstp	 [bp-154]
	fld	 dword ptr [bp-1130][4]
	fsub	 [bp-154]
	fstp	 [bp-166]
	fld	 [bp-154]
	fsub	 dword ptr [bp-1130][si]
	fstp	 [bp-178]
	fld	 dword ptr [bp-1146][0]
	fstp	 [bp-158]
	fld	 dword ptr [bp-1146][4]
	fsub	 [bp-158]
	fstp	 [bp-170]
	fld	 [bp-158]
	fsub	 dword ptr [bp-1146][si]
	fstp	 [bp-182] 
	fld	 [bp-150]
	fmul	 [bp-170]
	fld	 [bp-158]
	fmul	 [bp-162]
	fsubp	
	fmul	 DGROUP:_YCOEFF
	fstp	 [bp-98]
	fld	 [bp-150]
	fmul	 [bp-182]
	fld	 [bp-158]
	fmul	 [bp-174]
	fsubp	
	fmul	 DGROUP:_YCOEFF
	fstp	 [bp-110]
	fld	 [bp-174]
	fmul	 [bp-170]
	fld	 [bp-182]
	fmul	 [bp-162]
	fsubp	
	fmul	 DGROUP:_inv_dpp
	fstp	 [bp-122]
	fld	 [bp-158]
	fmul	 [bp-166]
	fld	 [bp-154]
	fmul	 [bp-170]
	fsubp	
	fmul	 DGROUP:_XCOEFF
	fstp	 [bp-102]
	fld	 [bp-158]
	fmul	 [bp-178]
	fld	 [bp-154]
	fmul	 [bp-182]
	fsubp	
	fmul	 DGROUP:_XCOEFF
	fstp	 [bp-114]
	fld	 [bp-182]
	fmul	 [bp-166]
	fld	 [bp-178]
	fmul	 [bp-170]
	fsubp	
	fmul	 DGROUP:_inv_dpp
	fstp	 [bp-126]
	fld	 [bp-154]
	fmul	 [bp-162]
	fld	 [bp-150]
	fmul	 [bp-166]
	fsubp	
	fmul	 DGROUP:_EMU_K
	fstp	 [bp-106]
	fld	 [bp-154]
	fmul	 [bp-174]
	fld	 [bp-150]
	fmul	 [bp-178]
	fsubp	
	fmul	 DGROUP:_EMU_K
	fstp	 [bp-118]
	fld	 [bp-178]
	fmul	 [bp-162]
	fld	 [bp-174]
	fmul	 [bp-166]
	fsubp	
	fstp	 [bp-130] 
	cmp	 DGROUP:_doflag, 4
	jne	short @29@238
	xor	 si, si
	mov	 cx, 4
	mov	 DGROUP:_vr2, 4
	mov	 [bp-22], 8 
@29@222:
   	db	 066H
	mov	 ax, word ptr DGROUP:_rxf[si]
	db	 066H
	mov	 bx, word ptr DGROUP:_ryf[si]
	db	 066H
	mov	 dx, word ptr DGROUP:_rzf[si]
	db	 066H
	mov	 word ptr [bp-238][si], ax
	db	 066H
	mov	 word ptr [bp-270][si], bx
	db	 066H
	mov	 word ptr [bp-302][si], dx
	add	 si, 4
	dec	 cx
	jne	short @29@222
	jmp	@29@445
@29@238:
   	mov	 DGROUP:_vr, 0
	xor	 di, di
	mov	 dx, 4
	dec	 dx 
@29@242:
   	mov	 si, DGROUP:_vr
	cmp	 byte ptr DGROUP:_rwf[si], 0
	je	short @29@246
	jmp	@29@420
@29@246:
   	mov	 ax, DGROUP:_vr
	sub	 ax, 1
	jnc	short @29@251
	mov	 DGROUP:_pvert, dx
	jmp	short @29@252
@29@251:
     	mov	 DGROUP:_pvert, ax
@29@252:
   	mov	 ax, DGROUP:_vr
	inc	 ax
	cmp	 ax, dx
	jbe	short @29@258
	mov	 DGROUP:_nvert, 0
	jmp	short @29@259
@29@258:
     	mov	 DGROUP:_nvert, ax
@29@259:
   	mov	 si, DGROUP:_pvert
	cmp	 byte ptr DGROUP:_rwf[si], 0
	je	short @29@263
	jmp	short @29@267
@29@263:
   	mov	 si, DGROUP:_nvert
	cmp	 byte ptr DGROUP:_rwf[si], 0
	jne	short @29@267
	jmp	@29@434
@29@267:
   	mov	 bx, DGROUP:_vr
	shl	 bx, 2
	mov	 si, DGROUP:_pvert
	mov	 al, byte ptr DGROUP:_rwf[si]
	mov	 si, DGROUP:_nvert
	add	 al, byte ptr DGROUP:_rwf[si]
	cmp	 al, 2
	je	short @29@276
	jmp	@29@366
@29@276:
   	shl	 DGROUP:_pvert, 2
	shl	 DGROUP:_nvert, 2
	mov	 si, bx
	fld	 dword ptr DGROUP:_rzf[si]
	mov	 si, DGROUP:_pvert
	fcomp	 dword ptr DGROUP:_rzf[si]
	fstsw	 ax
	sahf	
	jne	short @29@286
	jmp	@29@308
@29@286:
   	fld	 dword ptr DGROUP:_uneg
	fsub	 dword ptr DGROUP:_rzf[si]
	fld	 dword ptr DGROUP:_rzf[si]
	mov	 si, bx
	fsubr	 dword ptr DGROUP:_rzf[si]
	fdivp	
	fst	 DGROUP:_zk
	fld	 dword ptr DGROUP:_rxf[si]
	mov	 si, DGROUP:_pvert
	fsub	 dword ptr DGROUP:_rxf[si]
	fmulp	
	fadd	 dword ptr DGROUP:_rxf[si]
	fstp	 dword ptr [bp-238][di]
	fld	 DGROUP:_zk
	mov	 si, bx
	fld	 dword ptr DGROUP:_ryf[si]
	mov	 si, DGROUP:_pvert
	fsub	 dword ptr DGROUP:_ryf[si]
	fmulp	
	fadd	 dword ptr DGROUP:_ryf[si]
	fstp	 dword ptr [bp-270][di]
	jmp	short @29@317
@29@308:
   	mov	 si, bx
	db	 066H
	mov	 ax, word ptr DGROUP:_rxf[si]
	db	 066H
	mov	 word ptr [bp-238][di], ax
	db	 066H
	mov	 ax, word ptr DGROUP:_ryf[si]
	db	 066H
	mov	 word ptr [bp-270][di], ax 
@29@317:
   	db	 066H
	mov	 ax, word ptr DGROUP:_uneg
	db	 066H
	mov	 word ptr [bp-302][di], ax
	mov	 si, bx
	fld	 dword ptr DGROUP:_rzf[si]
	mov	 si, DGROUP:_nvert
	fcomp	 dword ptr DGROUP:_rzf[si]
	fstsw	 ax
	sahf	
	jne	short @29@329
	jmp	@29@351
@29@329:
   	fld	 dword ptr DGROUP:_uneg
	fsub	 dword ptr DGROUP:_rzf[si]
	fld	 dword ptr DGROUP:_rzf[si]
	mov	 si, bx
	fsubr	 dword ptr DGROUP:_rzf[si]
	fdivp	
	fst	 DGROUP:_zk
	fld	 dword ptr DGROUP:_rxf[si]
	mov	 si, DGROUP:_nvert
	fsub	 dword ptr DGROUP:_rxf[si]
	fmulp	
	fadd	 dword ptr DGROUP:_rxf[si]
	fstp	 dword ptr [bp-238][di+4]
	fld	 DGROUP:_zk
	mov	 si, bx
	fld	 dword ptr DGROUP:_ryf[si]
	mov	 si, DGROUP:_nvert
	fsub	 dword ptr DGROUP:_ryf[si]
	fmulp	
	fadd	 dword ptr DGROUP:_ryf[si]
	fstp	 dword ptr [bp-270][di+4]
	jmp	short @29@360
@29@351:
   	mov	 si, bx
	db	 066H
	mov	 ax, word ptr DGROUP:_rxf[si]
	db	 066H
	mov	 word ptr [bp-238][di+4], ax
	db	 066H
	mov	 ax, word ptr DGROUP:_ryf[si]
	db	 066H
	mov	 word ptr [bp-270][di+4], ax 
@29@360:
   	db	 066H
	mov	 ax, word ptr DGROUP:_uneg
	db	 066H
	mov	 word ptr [bp-302][di+4], ax
	add	 di, 8
	jmp	@29@434
@29@366:
   	mov	 si, DGROUP:_pvert
	cmp	 byte ptr DGROUP:_rwf[si], 0
	jne	short @29@372
	mov	 ax, DGROUP:_nvert
	mov	 DGROUP:_vvert, ax
	jmp	short @29@374
@29@372:
   	mov	 ax, DGROUP:_pvert
	mov	 DGROUP:_vvert, ax 
@29@374:
   	shl	 DGROUP:_vvert, 2
	mov	 si, bx
	fld	 dword ptr DGROUP:_rzf[si]
	mov	 si, DGROUP:_vvert
	fcomp	 dword ptr DGROUP:_rzf[si]
	fstsw	 ax
	sahf	
	jne	short @29@383
	jmp	@29@405
@29@383:
   	fld	 dword ptr DGROUP:_uneg
	fsub	 dword ptr DGROUP:_rzf[si]
	fld	 dword ptr DGROUP:_rzf[si]
	mov	 si, bx
	fsubr	 dword ptr DGROUP:_rzf[si]
	fdivp	
	fst	 DGROUP:_zk
	fld	 dword ptr DGROUP:_rxf[si]
	mov	 si, DGROUP:_vvert
	fsub	 dword ptr DGROUP:_rxf[si]
	fmulp	
	fadd	 dword ptr DGROUP:_rxf[si]
	fstp	 dword ptr [bp-238][di]
	fld	 DGROUP:_zk
	mov	 si, bx
	fld	 dword ptr DGROUP:_ryf[si]
	mov	 si, DGROUP:_vvert
	fsub	 dword ptr DGROUP:_ryf[si]
	fmulp	
	fadd	 dword ptr DGROUP:_ryf[si]
	fstp	 dword ptr [bp-270][di]
	jmp	short @29@414
@29@405:
   	mov	 si, bx
	db	 066H
	mov	 ax, word ptr DGROUP:_rxf[si]
	db	 066H
	mov	 word ptr [bp-238][di], ax
	db	 066H
	mov	 ax, word ptr DGROUP:_ryf[si]
	db	 066H
	mov	 word ptr [bp-270][di], ax 
@29@414:
   	db	 066H
	mov	 ax, word ptr DGROUP:_uneg
	db	 066H
	mov	 word ptr [bp-302][di], ax
	add	 di, 4
	jmp	short @29@434
@29@420:
   	shl	 si, 2
	db	 066H
	mov	 ax, word ptr DGROUP:_rxf[si]
	db	 066H
	mov	 word ptr [bp-238][di], ax
	db	 066H
	mov	 ax, word ptr DGROUP:_ryf[si]
	db	 066H
	mov	 word ptr [bp-270][di], ax
	db	 066H
	mov	 ax, word ptr DGROUP:_rzf[si]
	db	 066H
	mov	 word ptr [bp-302][di], ax
	add	 di, 4 
@29@434:
   	inc	 DGROUP:_vr
	mov	 ax, DGROUP:_vr
	cmp	 ax, 4
	jae	short @29@439
	jmp	@29@242
@29@439:
   	mov	 ax, di
	shr	 ax, 1
	mov	 [bp-22], ax
	shr	 ax, 1
	mov	 DGROUP:_vr2, ax 
	cmp	word ptr DGROUP:_vr2,3
	jl	@29@1059
@29@445:
   	db	 066H
	mov	 dx, word ptr DGROUP:_ubyl
	db	 066H
	mov	 bx, word ptr DGROUP:_lbyl
	mov	 si, DGROUP:_vr2
	dec	 si
	shl	 si, 2
	mov	 di, si
	add	 di, si 
@29@454:
   	fld	 DGROUP:_dpp
	fdiv	 dword ptr [bp-302][si]
	fld	 st(0)
	fmul	 dword ptr [bp-238][si]
	fadd	 dword ptr DGROUP:_x_centro_f
	fistp	 dword ptr DGROUP:_mp[di]
	fmul	 dword ptr [bp-270][si]
	fadd	 dword ptr DGROUP:_y_centro_f
	fistp	 dword ptr DGROUP:_mp[di + 4]
	db	 066H
	cmp	 word ptr DGROUP:_mp[di + 4], dx
	jge	short @29@468
	db	 066H
	mov	 dx, word ptr DGROUP:_mp[di + 4] 
@29@468:
   	db	 066H
	cmp	 word ptr DGROUP:_mp[di+4], bx
	jle	short @29@473
	db	 066H
	mov	 bx, word ptr DGROUP:_mp[di+4] 
@29@473:
   	sub	 di, 8
	sub	 si, 4
	jnc	short @29@454
	db	 066H
	mov	 word ptr [bp-54], bx
	db	 066H
	mov	 word ptr [bp-50], dx 
	db	 066H
	mov	 ax, word ptr [bp-50]
	db	 066H
	cmp	 ax, word ptr DGROUP:_ubyl
	jle	short @29@491
	db	 066H
	mov	 ax, word ptr [bp-54]
	db	 066H
	cmp	 ax, word ptr DGROUP:_lbyl
	jge	short @29@491
	jmp	@29@1059
@29@491:
	db	 066H
	mov	 ax, word ptr [bp-50]
	db	 066H
	cmp	 ax, word ptr DGROUP:_lbyl
	jge	short @29@500
	db	 066H
	mov	 ax, word ptr DGROUP:_lbyl
	db	 066H
	mov	 word ptr [bp-50], ax 
@29@500:
	db	 066H
	mov	 ax, word ptr [bp-54]
	db	 066H
	cmp	 ax, word ptr DGROUP:_ubyl
	jle	short @29@509
	db	 066H
	mov	 ax, word ptr DGROUP:_ubyl
	db	 066H
	mov	 word ptr [bp-54], ax 
@29@509:
	db	 066H
	mov	 ax, word ptr [bp-50]
	db	 066H
	cmp	 ax, word ptr [bp-54]
	jle	short @29@515
	jmp	@29@1059
@29@515:
	fld	  [bp-102]
	fmul	 DGROUP:__16
	fstp	 [bp-82]
	fld	  [bp-114]
	fmul	 DGROUP:__16
	fstp	 [bp-86]
	fld	  [bp-126]
	fmul	 DGROUP:__16
	fstp	 [bp-90] 
	cmp	byte ptr [bp-19],0
	je	short @29@526
	fld	dword ptr DGROUP:s@+12
	fmul	dword ptr [bp-82]
	fstp	dword ptr [bp-82]
	fld	dword ptr DGROUP:s@+12
	fmul	dword ptr [bp-86]
	fstp	dword ptr [bp-86]
	fld	dword ptr DGROUP:s@+12
	fmul	dword ptr [bp-90]
	fstp	dword ptr [bp-90]
	fwait	
@29@526:
	mov	 di, word ptr [bp-50]
	mov	 cx, word ptr [bp-54]
	db	 066H
	mov	 ax, word ptr DGROUP:_lbxl
	db	 066H
	mov	 bx, word ptr DGROUP:_ubxl
	sub	 cx, di
	shl	 di, 1
	inc	 cx 
@29@535:
	mov	 word ptr [bp-700][di], ax
	mov	 word ptr [bp-1098][di], bx
	add	 di, 2
	dec	 cx
	jne	short @29@535
	mov	 di, [bp-22]
	shl	 di, 2
	db	 066H
	mov	 ax, word ptr DGROUP:_mp[0]
	db	 066H
	mov	 bx, word ptr DGROUP:_mp[4]
	db	 066H
	mov	 word ptr DGROUP:_mp[di], ax
	db	 066H
	mov	 word ptr DGROUP:_mp[di+4], bx
	xor	 si, si
	shr	 [bp-22], 1 
@29@552:
	db	 066H
	mov	 bx, word ptr DGROUP:_mp[si+4]
	db	 066H
	mov	 dx, word ptr DGROUP:_mp[si+12]
	db	 066H
	mov	 ax, word ptr DGROUP:_mp[si]
	db	 066H
	mov	 cx, word ptr DGROUP:_mp[si+8]
	db	 066H
	cmp	 dx, bx
	jge	short @29@572
	db	 066H
	mov	 word ptr [bp-58], cx
	db	 066H
	mov	 word ptr [bp-62], dx
	db	 066H
	mov	 word ptr [bp-66], ax
	db	 066H
	mov	 word ptr [bp-70], bx
	jmp	short @29@580
@29@572:
	db	 066H
	mov	 word ptr [bp-58], ax
	db	 066H
	mov	 word ptr [bp-62], bx
	db	 066H
	mov	 word ptr [bp-66], cx
	db	 066H
	mov	 word ptr [bp-70], dx 
@29@580:
	jne	short @29@582
	jmp	@29@668
@29@582:
	fild	 [bp-66]
	fisub	 [bp-58]
	fild	 [bp-70]
	fisub	 [bp-62]
	fdivp	
	fstp	 [bp-146]
	db	 066H
	mov	 ax, word ptr [bp-62]
	db	 066H
	cmp	 ax, word ptr DGROUP:_lbyl
	jge	short @29@604
	db	 066H
	mov	 ax, word ptr DGROUP:_lbyl
	db	 066H
	mov	 word ptr [bp-74], ax
	fild	 [bp-58]
	fild	 DGROUP:_lbyl
	fisub	 [bp-62]
	fmul	 [bp-146]
	faddp	
	fistp	 [bp-58]
	jmp	short @29@608
@29@604:
	db	 066H
	mov	 ax, word ptr [bp-62]
	db	 066H
	mov	 word ptr [bp-74], ax 
@29@608:
	db	 066H
	mov	 ax, word ptr [bp-70]
	db	 066H
	cmp	 ax, word ptr DGROUP:_ubyl
	jle	short @29@618
	db	 066H
	mov	 ax, word ptr DGROUP:_ubyl
	db	 066H
	mov	 word ptr [bp-78], ax
	jmp	short @29@622
@29@618:
	db	 066H
	mov	 ax, word ptr [bp-70]
	db	 066H
	mov	 word ptr [bp-78], ax 
@29@622:
	fild	 [bp-58]
	db	 066H
	mov	 di, word ptr [bp-74]
	db	 066H
	mov	 cx, word ptr [bp-78]
	db	 066H
	cmp	 di, cx
	jge	short @29@667
	db	 066H
	sub	 cx, di
	shl	 di, 1
	inc	 cx 
@29@634:
	fist	 [bp-26]
	db	 066H
	mov	 ax, word ptr [bp-26]
	db	 066H
	cmp	 ax, word ptr [bp-34]
	jge	short @29@642
	db	 066H
	mov	 ax, word ptr [bp-34] 
@29@642:
   	db	 066H
	cmp	 ax, word ptr [bp-38]
	jle	short @29@647
	db	 066H
	mov	 ax, word ptr [bp-38] 
@29@647:
	cmp	 ax, word ptr [bp-700][di]
	jle	short @29@655
	cmp	 ax, word ptr DGROUP:_ubxl
	jge	short @29@653
	mov	 word ptr [bp-700][di], ax
	jmp	short @29@655
@29@653:
	mov	 dx, word ptr DGROUP:_ubxl
	mov	 word ptr [bp-700][di], dx 
@29@655:
	cmp	 ax, word ptr [bp-1098][di]
	jge	short @29@663
	cmp	 ax, word ptr DGROUP:_lbxl
	jle	short @29@661
	mov	 word ptr [bp-1098][di], ax
	jmp	short @29@663
@29@661:
	mov	 dx, word ptr DGROUP:_lbxl
	mov	 word ptr [bp-1098][di], dx 
@29@663:
	fadd	 [bp-146]
	add	 di, 2
	dec	 cx
	jne	short @29@634
@29@667:
 	fstp	 st
@29@668:
   	add	 si, 8
	dec	 [bp-22]
	je	short @29@672
	jmp	@29@552
@29@672:
 	les	 dx, dword ptr DGROUP:_txtr  
 	mov	 ax, es          
 	shr	 dx, 4           
 	add	 ax, dx          
 	db	 08eH, 0e0H       
 	les	 ax, dword ptr DGROUP:_adapted   
 	mov	 al, [bp+20]       
 	mov	 es:[0FA00H], al     
 	mov	 al, DGROUP:_escrescenze     
 	mov	 es:[0FA01H], al     
     	mov	 ax, word ptr [bp-50]
 	mov	 [bp-28], ax
@29@684:
	mov	 si, [bp-28]
	shl	 si, 1
	fild	 word ptr [bp-1098][si]
	fsub	 DGROUP:_x_centro_f
	fadd	 DGROUP:_uno
	fld	 st(0) 
	fld	 st(0) 
	fmul	 [bp-126]
	fild	 [bp-28]
	fsub	 DGROUP:_y_centro_f
	fmul	 [bp-122]
	faddp	
	fadd	 [bp-130]
	fst	 [bp-142]
	fdivr	 DGROUP:_uno
	fstp	 [bp-94]
	fmul	 [bp-102]
	fild	 [bp-28]
	fsub	 DGROUP:_y_centro_f
	fmul	 [bp-98]
	faddp	
	fadd	 [bp-106]
	fstp	 [bp-134]
	fmul	 [bp-114]
	fild	 [bp-28]
	fsub	 DGROUP:_y_centro_f
	fmul	 [bp-110]
	faddp	
	fadd	 [bp-118]
	fstp	 [bp-138]
	fld	 [bp-138]
	fmul	 [bp-12]
	fmul	 [bp-94]
	fld	 [bp-134]
	fmul	 [bp-4]
	fmul	 [bp-94]
	fxch	
	fistp	 [bp-46]
	fistp	 [bp-42]
	mov	 dx, word ptr [bp-1098][si]
	mov	 ax, word ptr [bp-700][si]
	mov	 di, word ptr DGROUP:_riga[si]
	sub	 ax, dx
	add	 di, dx
	mov	 [bp-30], ax
	push	 ds
	push	 es
	pop	  ds
	test	 [bp-19], 1
	je	short @29@735
	jmp	@29@875
@29@735:
   	cmp	 [bp-30], 0
	jg	short @29@738
	jmp	@29@1028
@29@738:
   	cmp	 [bp-30], 16
	jg	short @29@743
	mov	 ax, [bp-30]
	mov	 cl, al
	jmp	short @29@744
@29@743:
     	mov	 cl, 16
@29@744:
   	sub	 [bp-30], 16
	cmp	 cl, 0
	je	short @29@735
	fld	   [bp-142]           
	fadd	  [bp-90]               
	fld	   [bp-134]           
	fadd	  [bp-82]               
	fxch	                   
	fst	   [bp-142]               
	fxch	                   
	fst	   [bp-134]               
	fxch	                   
	fdivr	 [bp-18]             
	db	 066H
	mov	 ax, word ptr [bp-42]     
	db	 066H
	mov	 dx, word ptr [bp-46]     
	mov	 ch, [bp-13]        
	push	 bp                
	fxch	                   
	fmul	  [bp-4]        
	fld	   [bp-138]               
	fadd	  [bp-86]           
	fst	   [bp-138]               
	fmul	  [bp-12]        
	fxch	                   
	fmul	  st, st(2)        
	fxch	                   
	fmul	  st, st(2)        
	fxch	                   
	fistp	 [bp-42]                
	fistp	 [bp-46]                
	fstp	 st
	db	 066H
	mov	 si, word ptr [bp-46]
	db	 066H
	mov	 bp, word ptr [bp-42]
	db	 066H
	sub	 si, dx
	db	 066H
	sub	 bp, ax
	db	 066H
	sar	 si, 4
	db	 066H
	sar	 bp, 4
	test	 ch, 15     
	je	short @29@798
	test	 ch, 1      
	jne	short @29@809
	test	 ch, 2      
	jne	short @29@820
	test	 ch, 4      
	jne	short @29@836
	jmp	@29@851
@29@798:
   	mov	 bh, dh      
	inc	 di          
	mov	 bl, ah      
	mov	 ch, ds:[0FA00H] 
	db	 064H, 002H, 02FH     
	add	 ax, bp      
	mov	 [di+3], ch      
	add	 dx, si      
	dec	 cl          
	jne	short @29@798
	jmp	@29@873
@29@809:
   	mov	 bh, dh      
	inc	 di          
	mov	 bl, ah      
	mov	 ch, [di+3]      
	db	 064H, 002H, 02FH     
	add	 ax, bp      
	mov	 [di+3], ch      
	add	 dx, si      
	dec	 cl          
	jne	short @29@809
	jmp	@29@873
@29@820:
   	mov	 ch, [di+4]      
	mov	 bh, dh      
	inc	 di          
	mov	 bl, ah      
	and	 ch, 03FH        
	add	 ax, bp      
	db	 064H, 002H, 02FH     
	add	 dx, si      
	cmp	 ch, 03EH        
	jbe	short @29@831
	mov	 ch, 03EH 
@29@831:
   	and	 byte ptr [di+3], 0C0H 
	or	  [di+3], ch      
	dec	 cl          
	jne	short @29@820
	jmp	@29@873
@29@836:
   	mov	 ch, [di+4]      
	mov	 bh, dh      
	inc	 di          
	mov	 bl, ah      
	and	 ch, 03FH        
	add	 ax, bp      
	db	 064H, 002H, 02FH     
	add	 ch, ds:[0FA00H]
	add	 dx, si      
	shr	 ch, 1       
	and	 byte ptr [di+3], 0C0H 
	or	  [di+3], ch      
	dec	 cl          
	jne	short @29@836
	jmp	short @29@873
@29@851:
   	mov	 bh, dh      
	inc	 di          
	mov	 bl, ah      
	mov	 ch, ds:[0FA00H] 
	db	 064H, 002H, 02FH     
	add	 ax, bp      
	mov	 [di+3], ch      
	push	 di
	push	 cx
	and	 ch, 07H 
@29@861:
   	sub	 di, 320
	dec	 ch
	jns	short @29@861
	pop	 cx
	sub	 ch, ds:[0FA00H]
	add	 ch, ds:[0FA01H] 
	db	 064H, 002H, 02FH     
	mov	 byte ptr [di+640+3], ch
	pop	 di
	add	 dx, si      
	dec	 cl          
	jne	short @29@851
@29@873:
   	pop	 bp
	jmp	@29@735
@29@875:
   	cmp	 [bp-30], 0
	jg	short @29@878
	jmp	@29@1028
@29@878:
   	cmp	 [bp-30], 32
	jg	short @29@884
	mov	 ax, [bp-30]
	add	 ax, 2
	mov	 cl, al
	jmp	short @29@885
@29@884:
     	mov	 cl, 32
@29@885:
   	sub	 [bp-30], 32
	cmp	 cl, 2
	jl	short @29@875
	fld	   [bp-142]           
	fadd	  [bp-90]               
	fld	   [bp-134]           
	fadd	  [bp-82]               
	fxch	                   
	fst	   [bp-142]               
	fxch	                   
	fst	   [bp-134]               
	fxch	                   
	fdivr	 [bp-18]             
	db	 066H
	mov	 ax, word ptr [bp-42]     
	db	 066H
	mov	 dx, word ptr [bp-46]     
	shr	 cl, 1          
	push	 bp                
	mov	 ch, [bp-13]        
	push	 di            
	fxch	                   
	fmul	  [bp-4]        
	fld	   [bp-138]               
	fadd	  [bp-86]           
	fst	   [bp-138]               
	fmul	  [bp-12]        
	fxch	                   
	fmul	  st, st(2)        
	fxch	                   
	fmul	  st, st(2)        
	fxch	                   
	fistp	 [bp-42]                
	fistp	 [bp-46]                
	fstp	 st
	db	 066H
	mov	 si, word ptr [bp-46]
	db	 066H
	mov	 bp, word ptr [bp-42]
	db	 066H
	sub	 si, dx
	db	 066H
	sub	 bp, ax
	db	 066H
	sar	 si, 4
	db	 066H
	sar	 bp, 4
	test	 ch, 15         
	je	short @29@941
	test	 ch, 1      
	jne	short @29@953
	test	 ch, 2      
	jne	short @29@965
	test	 ch, 4      
	jne	short @29@983
	jmp	@29@1000
@29@941:
   	mov	 bh, dh      
	add	 di, 2       
	mov	 bl, ah      
	mov	 ch, ds:[0FA00H] 
	db	 064H, 002H, 02FH     
	add	 ax, bp      
	mov	 [di+2], ch      
	mov	 [di+3], ch      
	add	 dx, si      
	dec	 cl          
	jne	short @29@941
	jmp	@29@1024
@29@953:
   	mov	 bh, dh      
	add	 di, 2       
	mov	 bl, ah      
	mov	 ch, [di+3]      
	db	 064H, 002H, 02FH     
	add	 ax, bp      
	mov	 [di+2], ch      
	mov	 [di+3], ch      
	add	 dx, si      
	dec	 cl          
	jne	short @29@953
	jmp	@29@1024
@29@965:
   	mov	 ch, [di+4]      
	mov	 bh, dh      
	add	 di, 2       
	mov	 bl, ah      
	and	 ch, 03FH        
	add	 ax, bp      
	db	 064H, 002H, 02FH     
	add	 dx, si      
	cmp	 ch, 03EH        
	jbe	short @29@976
	mov	 ch, 03EH 
@29@976:
   	and	 byte ptr [di+2], 0C0H 
	or	  ch, [di+2]      
	dec	 cl          
	mov	 [di+2], ch      
	mov	 [di+3], ch      
	jne	short @29@965
	jmp	@29@1024
@29@983:
   	mov	 ch, [di+4]      
	mov	 bh, dh      
	add	 di, 2       
	mov	 bl, ah      
	and	 ch, 03FH        
	add	 ax, bp      
	db	 064H, 002H, 02FH     
	add	 ch, ds:[0FA00H]
	add	 dx, si      
	shr	 ch, 1       
	and	 byte ptr [di+2], 0C0H 
	or	  ch, [di+2]      
	dec	 cl          
	mov	 [di+2], ch      
	mov	 [di+3], ch      
	jne	short @29@983
	jmp	@29@1024
@29@1000:
   	mov	 bh, dh      
	add	 di, 2       
	mov	 bl, ah      
	mov	 ch, ds:[0FA00H] 
	db	 064H, 002H, 02FH     
	add	 ax, bp      
	mov	 [di+2], ch      
	mov	 [di+3], ch      
	push	 di
	push	 cx
	and	 ch, 07H 
@29@1011:
   	sub	 di, 320
	dec	 ch
	jns	short @29@1011
	pop	 cx
	sub	 ch, ds:[0FA00H]
	add	 ch, ds:[0FA01H] 
	db	 064H, 002H, 02FH     
	mov	 byte ptr [di+640+2], ch
	mov	 byte ptr [di+640+3], ch
	pop	 di
	add	 dx, si      
	dec	 cl          
	jne	short @29@1000
@29@1024:
   	pop	 di
	pop	 bp
	add	 di, 32
	jmp	@29@875
@29@1028:
   	test	 [bp-20], 1
	je	short @29@1053
	inc	 [bp-28]
	mov	 ax, word ptr [bp-54]
	cmp	 ax, [bp-28]
	pop	 ds
	jb	short @29@1059
	mov	 si, [bp-28]
	shl	 si, 1
	mov	 dx, word ptr [bp-1098][si-2]
	mov	 ax, word ptr [bp-700][si-2]
	mov	 di, word ptr DGROUP:_riga[si]
	push	 ds
	push	 es
	pop	  ds
	sub	 ax, dx
	jc	short @29@1053
	je	short @29@1053
	add	 di, dx 
@29@1047:
   	mov	 dl, [di-316]
	mov	 [di+4], dl
	mov	 [di+324], dl
	inc	 di
	dec	 ax
	jne	short @29@1047
@29@1053:
   	inc	 [bp-28]
	mov	 ax, word ptr [bp-54]
	cmp	 ax, [bp-28]
	pop	 ds
	jb	short @29@1059
	jmp	@29@684
@29@1059:
	pop	di
	pop	si
	leave	
	ret	
@polymap$qnft1t1cuc	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@Forward$qf	proc	far
	push	bp
	mov	bp,sp
	fld	dword ptr [bp+6]
	fmul	dword ptr DGROUP:_opt_tsinbeta
	fmul	dword ptr DGROUP:_opt_tcosalfa
	fsubr	dword ptr DGROUP:_cam_x
	fstp	dword ptr DGROUP:_cam_x
	fld	dword ptr [bp+6]
	fmul	dword ptr DGROUP:_opt_tcosbeta
	fmul	dword ptr DGROUP:_opt_tcosalfa
	fadd	dword ptr DGROUP:_cam_z
	fstp	dword ptr DGROUP:_cam_z
	fld	dword ptr [bp+6]
	fmul	dword ptr DGROUP:_opt_tsinalfa
	fadd	dword ptr DGROUP:_cam_y
	fstp	dword ptr DGROUP:_cam_y
	fwait	
	pop	bp
	ret	
@Forward$qf	endp
NOCTIS-0_TEXT	ends
_BSS	segment word public use16 'BSS'
__x_	label	dword
	db	4 dup (?)
__y_	label	dword
	db	4 dup (?)
_BSS	ends
NOCTIS-0_TEXT	segment byte public use16 'CODE'
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@getcoords$qfff	proc	far
	push	bp
	mov	bp,sp
	sub	sp,16
	db	 066H
	mov	 ax, word ptr DGROUP:__0
	db	 066H
	cmp	 ax, word ptr DGROUP:_gamma
	jne	short @31@7
	jmp	@31@53
@31@7:
   	fld	 [bp+14]
	fsub	 DGROUP:_cam_z
	fst	 DGROUP:_zz
	fmul	 DGROUP:_opt_tsinbeta
	fld	 [bp+6]
	fsub	 DGROUP:_cam_x
	fst	 DGROUP:_xx
	fmul	 DGROUP:_opt_tcosbeta
	faddp	
	fstp	 [bp-4]
	fld	 DGROUP:_zz
	fmul	 DGROUP:_opt_tcosbeta
	fld	 DGROUP:_xx
	fmul	 DGROUP:_opt_tsinbeta
	fsubp	
	fst	 DGROUP:_z2
	fmul	 DGROUP:_opt_tcosalfa
	fld	 [bp+10]
	fsub	 DGROUP:_cam_y
	fst	 DGROUP:_yy
	fmul	 DGROUP:_opt_tsinalfa
	faddp	
	fst	 [bp-12]
	fcomp	 DGROUP:_uneg
	fstsw	 ax
	fld	 DGROUP:_yy
	fmul	 DGROUP:_opt_tcosalfa
	fld	 DGROUP:_z2
	fmul	 DGROUP:_opt_tsinalfa
	fsubp	
	fst	 [bp-16]
	fmul	 DGROUP:_opt_tcosgamma
	fld	 [bp-4]
	fmul	 DGROUP:_opt_tsingamma
	fsubp	
	fstp	 [bp-8]
	fld	 [bp-16]
	fmul	 DGROUP:_opt_tsingamma
	fld	 [bp-4]
	fmul	 DGROUP:_opt_tcosgamma
	faddp	
	fstp	 [bp-4]
	sahf	
	jb	short @31@52
	jmp	@31@88
@31@52:
	jmp	@31@102
@31@53:
   	fld	 [bp+14]
	fsub	 DGROUP:_cam_z
	fst	 DGROUP:_zz
	fmul	 DGROUP:_opt_tsinbeta
	fld	 [bp+6]
	fsub	 DGROUP:_cam_x
	fst	 DGROUP:_xx
	fmul	 DGROUP:_opt_tcosbeta
	faddp	
	fstp	 [bp-4]
	fld	 DGROUP:_zz
	fmul	 DGROUP:_opt_tcosbeta
	fld	 DGROUP:_xx
	fmul	 DGROUP:_opt_tsinbeta
	fsubp	
	fst	 DGROUP:_z2
	fmul	 DGROUP:_opt_tcosalfa
	fld	 [bp+10]
	fsub	 DGROUP:_cam_y
	fst	 DGROUP:_yy
	fmul	 DGROUP:_opt_tsinalfa
	faddp	
	fst	 [bp-12]
	fcomp	 DGROUP:_uneg
	fstsw	 ax
	fld	 DGROUP:_yy
	fmul	 DGROUP:_opt_tcosalfa
	fld	 DGROUP:_z2
	fmul	 DGROUP:_opt_tsinalfa
	fsubp	
	fstp	 [bp-8]
	sahf	
	jb	short @31@87
	jmp	short @31@88
@31@87:
	jmp	short @31@102
@31@88:
	fld	 DGROUP:_dpp
	fdiv	 [bp-12]
	fld	 st(0)
	fmul	 [bp-4]
	fadd	 DGROUP:_x_centro_f
	fistp	 DGROUP:__x_
	fmul	 [bp-8]
	fadd	 DGROUP:_y_centro_f
	fistp	 DGROUP:__y_
	mov	eax,dword ptr DGROUP:__x_
	cmp	eax,dword ptr DGROUP:_lbxl
	jle	short @31@102
	cmp	eax,dword ptr DGROUP:_ubxl
	jge	short @31@102
	mov	eax,dword ptr DGROUP:__y_
	cmp	eax,dword ptr DGROUP:_lbyl
	jle	short @31@102
	cmp	eax,dword ptr DGROUP:_ubyl
	jge	short @31@102
	mov	al,1
	leave	
	ret	
@31@102:
	mov	al,0
	leave	
	ret	
@getcoords$qfff	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@facing$qnft1t1	proc	far
	push	bp
	mov	bp,sp
	sub	sp,36
	push	si
	push	di
   	les	   bx, dword ptr [bp+6]
	mov	   si, word ptr  [bp+10]
	mov	   di, word ptr  [bp+14]
	fld	   dword ptr es:[bx]
	fsub	  dword ptr es:[bx+8]
	fstp	  [bp-4]
	fld	   dword ptr es:[si]
	fsub	  dword ptr es:[si+8]
	fstp	  [bp-8]
	fld	   dword ptr es:[di]
	fsub	  dword ptr es:[di+8]
	fstp	  [bp-12]
	fld	   dword ptr es:[bx+4]
	fsub	  dword ptr es:[bx+8]
	fstp	  [bp-16]
	fld	   dword ptr es:[si+4]
	fsub	  dword ptr es:[si+8]
	fstp	  [bp-20]
	fld	   dword ptr es:[di+4]
	fsub	  dword ptr es:[di+8]
	fst	   [bp-24]
	fmul	  [bp-8]
	fld	   [bp-20]
	fmul	  [bp-12]
	fsubp	
	fstp	  [bp-28]
	fld	   [bp-12]
	fmul	  [bp-16]
	fld	   [bp-24]
	fmul	  [bp-4]
	fsubp	
	fstp	  [bp-32]
	fld	   [bp-4]
	fmul	  [bp-20]
	fld	   [bp-16]
	fmul	  [bp-8]
	fsubp	
	fstp	  [bp-36]
	fld	   DGROUP:_cam_x
	fsub	  dword ptr es:[bx+8]
	fmul	  [bp-28]
	fld	   DGROUP:_cam_y
	fsub	  dword ptr es:[si+8]
	fmul	  [bp-32]
	faddp	
	fld	   DGROUP:_cam_z
	fsub	  dword ptr es:[di+8]
	fmul	  [bp-36]
	faddp	
	ftst	
	ffree	 st(0)
	fstsw	 ax
	xor	 dl, dl
	sahf	
	jb	short @32@57
	not	 dl 
@32@57:
	mov	al,dl
	pop	di
	pop	si
	leave	
	ret	
@facing$qnft1t1	endp
NOCTIS-0_TEXT	ends
_DATA	segment word public use16 'DATA'
	db	1 dup (0)
_situation_file	label	dword
	dd	DGROUP:s@+16
_starmap_file	label	dword
	dd	DGROUP:s@+33
_goesoutputfile	label	dword
	dd	DGROUP:s@+50
_surface_file	label	dword
	dd	DGROUP:s@+68
_DATA	ends
_BSS	segment word public use16 'BSS'
_sfh	label	word
	db	2 dup (?)
_BSS	ends
_DATA	segment word public use16 'DATA'
_sync	label	byte
	db	1
_anti_rad	label	byte
	db	1
_pl_search	label	byte
	db	0
_field_amplificator	label	byte
	db	0
_ilight	label	byte
	db	63
_ilightv	label	byte
	db	1
_charge	label	byte
	db	3
_revcontrols	label	byte
	db	0
_ap_targetting	label	byte
	db	0
_ap_targetted	label	byte
	db	0
_ip_targetting	label	byte
	db	0
_ip_targetted	label	byte
	db	255
_ip_reaching	label	byte
	db	0
_ip_reached	label	byte
	db	0
_ap_target_spin	label	byte
	db	0
_ap_target_r	label	byte
	db	0
_ap_target_g	label	byte
	db	0
_ap_target_b	label	byte
	db	0
_nearstar_spin	label	byte
	db	0
_nearstar_r	label	byte
	db	0
_nearstar_g	label	byte
	db	0
_nearstar_b	label	byte
	db	0
_gburst	label	byte
	db	0
_menusalwayson	label	byte
	db	1
_depolarize	label	byte
	db	0
	db	1 dup (0)
_sys	label	word
	db	4
	db	0
_pwr	label	word
	db	32
	db	78
_dev_page	label	word
	db	0
	db	0
_ap_target_class	label	word
	db	0
	db	0
_f_ray_elapsed	label	word
	db	0
	db	0
_nearstar_class	label	word
	db	0
	db	0
_nearstar_nop	label	word
	db	0
	db	0
_pos_x	label	dword
	db	0
	db	0
	db	0
	db	0
_pos_y	label	dword
	db	0
	db	0
	db	0
	db	0
_pos_z	label	dword
	db	0
	db	0
	db	250
	db	195
_user_alfa	label	dword
	db	0
	db	0
	db	0
	db	0
_user_beta	label	dword
	db	0
	db	0
	db	0
	db	0
_navigation_beta	label	dword
	db	0
	db	0
	db	0
	db	0
_ap_target_ray	label	dword
	db	0
	db	0
	db	122
	db	68
_nearstar_ray	label	dword
	db	0
	db	0
	db	122
	db	68
_dzat_x	label	qword
	db	0
	db	0
	db	0
	db	0
	db	64
	db	248
	db	76
	db	65
_dzat_y	label	qword
	db	0
	db	0
	db	0
	db	0
	db	28
	db	154
	db	80
	db	193
_dzat_z	label	qword
	db	0
	db	0
	db	0
	db	0
	db	180
	db	58
	db	44
	db	193
_ap_target_x	label	qword
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
_ap_target_y	label	qword
	db	0
	db	0
	db	0
	db	0
	db	132
	db	215
	db	151
	db	65
_ap_target_z	label	qword
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
_nearstar_x	label	qword
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
_nearstar_y	label	qword
	db	0
	db	0
	db	0
	db	0
	db	132
	db	215
	db	151
	db	65
_nearstar_z	label	qword
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
_helptime	label	qword
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
_ip_target_initial_d	label	qword
	db	0
	db	0
	db	0
	db	0
	db	132
	db	215
	db	151
	db	65
_requested_approach_coefficient	label	qword
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	240
	db	63
_current_approach_coefficient	label	qword
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	240
	db	63
_reaction_time	label	qword
	db	123
	db	20
	db	174
	db	71
	db	225
	db	122
	db	132
	db	63
_fcs_status	label	byte
	db	83
	db	84
	db	65
	db	78
	db	68
	db	66
	db	89
	db	4 dup (0)
	db	1 dup (0)
_fcs_status_delay	label	word
	db	0
	db	0
_psys	label	word
	db	4
	db	0
_ap_target_initial_d	label	qword
	db	0
	db	0
	db	0
	db	0
	db	132
	db	215
	db	151
	db	65
_requested_vimana_coefficient	label	qword
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	240
	db	63
_current_vimana_coefficient	label	qword
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	240
	db	63
_vimana_reaction_time	label	qword
	db	123
	db	20
	db	174
	db	71
	db	225
	db	122
	db	132
	db	63
_lithium_collector	label	byte
	db	0
_autoscreenoff	label	byte
	db	0
_ap_reached	label	byte
	db	0
	db	1 dup (0)
_lifter	label	word
	db	0
	db	0
_secs	label	qword
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
_data	label	byte
	db	0
_surlight	label	byte
	db	16
_land_now	label	byte
	db	0
_landing_point	label	byte
	db	0
_landing_pt_lon	label	word
	db	0
	db	0
_landing_pt_lat	label	word
	db	60
	db	0
_DATA	ends
_BSS	segment word public use16 'BSS'
_crepzone	label	word
	db	2 dup (?)
_nightzone	label	word
	db	2 dup (?)
_sun_x_factor	label	word
	db	2 dup (?)
_BSS	ends
_DATA	segment word public use16 'DATA'
_epoc	label	word
	db	123
	db	23
_DATA	ends
_BSS	segment word public use16 'BSS'
_ctb	label	byte
	db	512 dup (?)
_dec	label	byte
	db	20 dup (?)
_BSS	ends
_DATA	segment word public use16 'DATA'
__delay	label	byte
	db	12
_stspeed	label	byte
	db	0
_DATA	ends
_BSS	segment word public use16 'BSS'
_bright	label	byte
	db	1 dup (?)
_BSS	ends
_DATA	segment word public use16 'DATA'
_elight	label	byte
	db	0
	db	1 dup (0)
_gl_start	label	word
	db	0
	db	0
_DATA	ends
_BSS	segment word public use16 'BSS'
	db	1 dup (?)
_point	label	word
	db	2 dup (?)
_vptr	label	word
	db	2 dup (?)
_BSS	ends
_DATA	segment word public use16 'DATA'
_infoarea	label	word
	db	0
	db	0
_s_control	label	word
	db	1
	db	0
_s_command	label	word
	db	0
	db	0
_DATA	ends
_BSS	segment word public use16 'BSS'
_isecs	label	word
	db	2 dup (?)
_p_isecs	label	word
	db	2 dup (?)
_fsecs	label	qword
	db	8 dup (?)
_BSS	ends
_DATA	segment word public use16 'DATA'
_gl_fps	label	word
	db	1
	db	0
_fps	label	word
	db	1
	db	0
_dlt_alfa	label	dword
	db	0
	db	0
	db	0
	db	0
_dlt_beta	label	dword
	db	0
	db	0
	db	0
	db	0
_dlt_nav_beta	label	dword
	db	0
	db	0
	db	0
	db	0
_step	label	dword
	db	0
	db	0
	db	0
	db	0
_shift	label	dword
	db	0
	db	0
	db	0
	db	0
_s_m	label	qword
	db	0
	db	0
	db	0
	db	0
	db	0
	db	64
	db	143
	db	64
_DATA	ends
_BSS	segment word public use16 'BSS'
_plx	label	qword
	db	8 dup (?)
_ply	label	qword
	db	8 dup (?)
_plz	label	qword
	db	8 dup (?)
_pxx	label	qword
	db	8 dup (?)
_pyy	label	qword
	db	8 dup (?)
_delta_x	label	qword
	db	8 dup (?)
_delta_y	label	qword
	db	8 dup (?)
_nearstar_identity	label	qword
	db	8 dup (?)
_nearstar_labeled	label	word
	db	2 dup (?)
_BSS	ends
_DATA	segment word public use16 'DATA'
_nearstar_nob	label	word
	db	0
	db	0
_DATA	ends
_BSS	segment word public use16 'BSS'
_npcs	label	word
	db	2 dup (?)
_resident_map1	label	word
	db	2 dup (?)
_resident_map2	label	word
	db	2 dup (?)
_ontheroof	label	byte
	db	1 dup (?)
_BSS	ends
_DATA	segment word public use16 'DATA'
_datasheetscroll	label	word
	db	0
	db	0
_datasheetdelta	label	word
	db	0
	db	0
_ord	label	dword
	dd	DGROUP:s@+85
	dd	DGROUP:s@+92
	dd	DGROUP:s@+98
	dd	DGROUP:s@+105
	dd	DGROUP:s@+111
	dd	DGROUP:s@+118
	dd	DGROUP:s@+124
	dd	DGROUP:s@+130
	dd	DGROUP:s@+138
	dd	DGROUP:s@+144
	dd	DGROUP:s@+151
	dd	DGROUP:s@+157
	dd	DGROUP:s@+166
	dd	DGROUP:s@+175
	dd	DGROUP:s@+185
	dd	DGROUP:s@+196
	dd	DGROUP:s@+206
	dd	DGROUP:s@+216
	dd	DGROUP:s@+228
	dd	DGROUP:s@+239
	dd	DGROUP:s@+250
_star_description	label	dword
	dd	DGROUP:s@+259
	dd	DGROUP:s@+335
	dd	DGROUP:s@+395
	dd	DGROUP:s@+442
	dd	DGROUP:s@+479
	dd	DGROUP:s@+536
	dd	DGROUP:s@+586
	dd	DGROUP:s@+637
	dd	DGROUP:s@+694
	dd	DGROUP:s@+754
	dd	DGROUP:s@+805
	dd	DGROUP:s@+866
_class_rgb	label	byte
	db	63
	db	58
	db	40
	db	30
	db	50
	db	63
	db	63
	db	63
	db	63
	db	63
	db	30
	db	20
	db	63
	db	55
	db	32
	db	32
	db	16
	db	10
	db	32
	db	28
	db	24
	db	10
	db	20
	db	63
	db	63
	db	32
	db	16
	db	48
	db	32
	db	63
	db	40
	db	10
	db	10
	db	0
	db	63
	db	63
_class_ray	label	word
	db	136
	db	19
	db	152
	db	58
	db	44
	db	1
	db	32
	db	78
	db	152
	db	58
	db	232
	db	3
	db	184
	db	11
	db	208
	db	7
	db	160
	db	15
	db	220
	db	5
	db	48
	db	117
	db	250
	db	0
_class_rayvar	label	word
	db	208
	db	7
	db	16
	db	39
	db	200
	db	0
	db	152
	db	58
	db	136
	db	19
	db	232
	db	3
	db	184
	db	11
	db	244
	db	1
	db	136
	db	19
	db	16
	db	39
	db	232
	db	3
	db	10
	db	0
_class_act	label	word
	db	2
	db	0
	db	4
	db	0
	db	1
	db	0
	db	6
	db	0
	db	5
	db	0
	db	10
	db	0
	db	100
	db	0
	db	1
	db	0
	db	2
	db	0
	db	1
	db	0
	db	10
	db	0
	db	1
	db	0
_class_planets	label	byte
	db	12
	db	18
	db	8
	db	15
	db	20
	db	3
	db	0
	db	1
	db	7
	db	20
	db	2
	db	5
_DATA	ends
_BSS	segment word public use16 'BSS'
_nearstar_p_type	label	byte
	db	80 dup (?)
	db	1 dup (?)
_nearstar_p_owner	label	word
	db	160 dup (?)
_nearstar_p_moonid	label	byte
	db	80 dup (?)
_nearstar_p_ring	label	qword
	db	640 dup (?)
_nearstar_p_tilt	label	qword
	db	640 dup (?)
_nearstar_p_ray	label	qword
	db	640 dup (?)
_nearstar_p_orb_ray	label	qword
	db	640 dup (?)
_nearstar_p_orb_seed	label	qword
	db	640 dup (?)
_nearstar_p_orb_tilt	label	qword
	db	640 dup (?)
_nearstar_p_orb_orient	label	qword
	db	640 dup (?)
_nearstar_p_orb_ecc	label	qword
	db	640 dup (?)
_nearstar_p_rtperiod	label	word
	db	160 dup (?)
_nearstar_p_rotation	label	word
	db	160 dup (?)
_nearstar_p_term_start	label	word
	db	160 dup (?)
_nearstar_p_term_end	label	word
	db	160 dup (?)
_nearstar_p_qsortindex	label	word
	db	160 dup (?)
_nearstar_p_qsortdist	label	dword
	db	320 dup (?)
_BSS	ends
_DATA	segment word public use16 'DATA'
_planet_description	label	dword
	dd	DGROUP:s@+926
	dd	DGROUP:s@+988
	dd	DGROUP:s@+1036
	dd	DGROUP:s@+1099
	dd	DGROUP:s@+1164
	dd	DGROUP:s@+1208
	dd	DGROUP:s@+1239
	dd	DGROUP:s@+1289
	dd	DGROUP:s@+1331
	dd	DGROUP:s@+1396
	dd	DGROUP:s@+1443
_planet_rgb_and_var	label	byte
	db	60
	db	30
	db	15
	db	20
	db	40
	db	50
	db	40
	db	25
	db	32
	db	32
	db	32
	db	32
	db	16
	db	32
	db	48
	db	40
	db	32
	db	40
	db	32
	db	20
	db	32
	db	32
	db	32
	db	32
	db	32
	db	32
	db	32
	db	32
	db	32
	db	40
	db	48
	db	24
	db	40
	db	40
	db	40
	db	30
	db	50
	db	25
	db	10
	db	20
	db	40
	db	40
	db	40
	db	40
_planet_possiblemoons	label	word
	db	1
	db	0
	db	1
	db	0
	db	2
	db	0
	db	3
	db	0
	db	2
	db	0
	db	2
	db	0
	db	18
	db	0
	db	2
	db	0
	db	3
	db	0
	db	20
	db	0
	db	20
	db	0
_planet_orb_scaling	label	qword
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	20
	db	64
_avg_planet_sizing	label	qword
	db	51
	db	51
	db	51
	db	51
	db	51
	db	51
	db	3
	db	64
_moon_orb_scaling	label	qword
	db	154
	db	153
	db	153
	db	153
	db	153
	db	153
	db	41
	db	64
_avg_moon_sizing	label	qword
	db	205
	db	204
	db	204
	db	204
	db	204
	db	204
	db	252
	db	63
_avg_planet_ray	label	qword
	db	121
	db	233
	db	38
	db	49
	db	8
	db	172
	db	124
	db	63
	db	250
	db	126
	db	106
	db	188
	db	116
	db	147
	db	104
	db	63
	db	123
	db	20
	db	174
	db	71
	db	225
	db	122
	db	132
	db	63
	db	186
	db	73
	db	12
	db	2
	db	43
	db	135
	db	134
	db	63
	db	123
	db	20
	db	174
	db	71
	db	225
	db	122
	db	132
	db	63
	db	252
	db	169
	db	241
	db	210
	db	77
	db	98
	db	128
	db	63
	db	252
	db	169
	db	241
	db	210
	db	77
	db	98
	db	176
	db	63
	db	59
	db	223
	db	79
	db	141
	db	151
	db	110
	db	130
	db	63
	db	250
	db	126
	db	106
	db	188
	db	116
	db	147
	db	136
	db	63
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	192
	db	63
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	20
	db	64
_mindiff	label	dword
	db	10
	db	215
	db	35
	db	60
_DATA	ends
_BSS	segment word public use16 'BSS'
_s_background	label	dword
	db	4 dup (?)
_p_background	label	dword
	db	4 dup (?)
_p_surfacemap	label	dword
	db	4 dup (?)
_objectschart	label	dword
	db	4 dup (?)
_ruinschart	label	dword
	db	4 dup (?)
_pvfile	label	dword
	db	4 dup (?)
_n_offsets_map	label	dword
	db	4 dup (?)
_n_globes_map	label	dword
	db	4 dup (?)
_BSS	ends
_DATA	segment word public use16 'DATA'
_sky_red_filter	label	byte
	db	63
_sky_grn_filter	label	byte
	db	63
_sky_blu_filter	label	byte
	db	63
_gnd_red_filter	label	byte
	db	63
_gnd_grn_filter	label	byte
	db	63
_gnd_blu_filter	label	byte
	db	63
_planet_grav	label	dword
	db	0
	db	0
	db	22
	db	67
_rainy	label	dword
	db	0
	db	0
	db	0
	db	0
_albedo	label	word
	db	0
	db	0
_sky_brightness	label	byte
	db	32
_horiz_brt	label	byte
	db	20
_DATA	ends
_BSS	segment word public use16 'BSS'
_m200	label	word
	db	400 dup (?)
_BSS	ends
_DATA	segment word public use16 'DATA'
_rwp	label	dword
	db	0
	db	0
	db	112
	db	65
_iwp	label	dword
	db	0
	db	0
	db	0
	db	0
_wp	label	dword
	db	0
	db	0
	db	0
	db	0
_wdir	label	dword
	db	0
	db	0
	db	0
	db	0
_wdirsin	label	dword
	db	0
	db	0
	db	0
	db	0
_wdircos	label	dword
	db	0
	db	0
	db	128
	db	63
_DATA	ends
_BSS	segment word public use16 'BSS'
_landed	label	byte
	db	1 dup (?)
	db	1 dup (?)
_atl_x	label	dword
	db	4 dup (?)
_atl_z	label	dword
	db	4 dup (?)
_atl_x2	label	dword
	db	4 dup (?)
_atl_z2	label	dword
	db	4 dup (?)
_BSS	ends
_DATA	segment word public use16 'DATA'
_qid	label	qword
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	16
	db	63
_pvfile_datatop	label	dword
	db	0
	db	0
	db	0
	db	0
_pvfile_dataptr	label	word
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
_pvfile_datalen	label	word
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
_pvfile_npolygs	label	word
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
_DATA	ends
_BSS	segment word public use16 'BSS'
_pv_n_vtx	label	dword
	db	64 dup (?)
_pvfile_x	label	dword
	db	64 dup (?)
_pvfile_y	label	dword
	db	64 dup (?)
_pvfile_z	label	dword
	db	64 dup (?)
_pvfile_c	label	dword
	db	64 dup (?)
_pv_mid_x	label	dword
	db	64 dup (?)
_pv_mid_y	label	dword
	db	64 dup (?)
_pv_mid_z	label	dword
	db	64 dup (?)
_pv_mid_d	label	dword
	db	64 dup (?)
_pv_dep_i	label	dword
	db	64 dup (?)
_flat_rnd_seed	label	dword
	db	4 dup (?)
_BSS	ends
NOCTIS-0_TEXT	segment byte public use16 'CODE'
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@fast_srand$ql	proc	far
	push	bp
	mov	bp,sp
	mov	eax,dword ptr [bp+6]
	or	eax,large 3
	mov	dword ptr DGROUP:_flat_rnd_seed,eax
	pop	bp
	ret	
@fast_srand$ql	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@fast_random$ql	proc	far
	push	bp
	mov	bp,sp
	sub	sp,4
	db	 066H
	mov	 ax, word ptr DGROUP:_flat_rnd_seed
	db	 066H
	mov	 dx, word ptr DGROUP:_flat_rnd_seed
	db	 066H
	mul	 dx
	add	 al, dl
	db	 066H
	add	 word ptr DGROUP:_flat_rnd_seed, ax
	db	 066H
	and	 ax, word ptr [bp+6]
	db	 066H
	mov	 word ptr [bp-4], ax
	mov	dx,word ptr [bp-2]
	mov	ax,word ptr [bp-4]
	leave	
	ret	
@fast_random$ql	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@ranged_fast_random$qi	proc	far
	push	bp
	mov	bp,sp
	push	si
	mov	si,word ptr [bp+6]
	or	si,si
	jg	short @35@3
	mov	si,1
@35@3:
	push	large 32767
	push	cs
	call	near ptr @fast_random$ql
	shl	eax,16
	shrd	eax,edx,16
	add	sp,4
	movsx	ebx,si
	cdq	
	idiv	ebx
	mov	eax,edx
	pop	si
	pop	bp
	ret	
@ranged_fast_random$qi	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@flandom$qv	proc	far
	push	bp
	mov	bp,sp
	sub	sp,2
	call	far ptr _rand
	cwde	
	imul	eax,large 32767
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	mov	word ptr [bp-2],ax
	fild	word ptr [bp-2]
	fmul	qword ptr DGROUP:s@+1473
	leave	
	ret	
@flandom$qv	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@fast_flandom$qv	proc	far
	push	bp
	mov	bp,sp
	sub	sp,4
	push	large 32767
	push	cs
	call	near ptr @fast_random$ql
	shl	eax,16
	shrd	eax,edx,16
	add	sp,4
	mov	dword ptr [bp-4],eax
	fild	dword ptr [bp-4]
	fmul	qword ptr DGROUP:s@+1473
	leave	
	ret	
@fast_flandom$qv	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@sa_open$ql	proc	far
	push	bp
	mov	bp,sp
	push	si
	push	0
	push	ds
	push	offset DGROUP:s@+1481
	call	far ptr __rtl_open
	add	sp,6
	mov	si,ax
	cmp	si,-1
	je	short @38@5
	push	2
	push	dword ptr [bp+6]
	push	si
	call	far ptr _lseek
	shl	eax,16
	shrd	eax,edx,16
	add	sp,8
	cmp	eax,large -1
	jle	short @38@4
	mov	ax,si
	jmp	short @38@6
@38@4:
	push	si
	call	far ptr __rtl_close
	add	sp,2
@38@5:
	mov	ax,-1
@38@6:
	pop	si
	pop	bp
	ret	
@sa_open$ql	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@shade$qnuciiffffff	proc	far
	push	bp
	mov	bp,sp
	sub	sp,18
	push	si
	push	di
	mov	si,word ptr [bp+10]
	mov	di,word ptr [bp+12]
	mov	ax,word ptr [bp+12]
	mov	word ptr [bp-6],ax
	fild	word ptr [bp-6]
	fld1	
	fdivr	
	fstp	dword ptr [bp-4]
	fld	dword ptr [bp+26]
	fsub	dword ptr [bp+14]
	fmul	dword ptr [bp-4]
	fstp	dword ptr [bp-10]
	fld	dword ptr [bp+30]
	fsub	dword ptr [bp+18]
	fmul	dword ptr [bp-4]
	fstp	dword ptr [bp-14]
	fld	dword ptr [bp+34]
	fsub	dword ptr [bp+22]
	fmul	dword ptr [bp-4]
	fstp	dword ptr [bp-18]
	mov	ax,3
	imul	si
	mov	si,ax
	fwait	
	jmp	@39@21
@39@2:
	fld	dword ptr [bp+14]
	fldz	
	fcompp
	fstsw	word ptr [bp-6]
	fwait	
	mov	ax,word ptr [bp-6]
	sahf	
	ja	short @39@5
	fld	dword ptr [bp+14]
	fcomp	dword ptr DGROUP:s@+1498
	fstsw	word ptr [bp-6]
	fwait	
	mov	ax,word ptr [bp-6]
	sahf	
	jae	short @39@5
	les	bx,dword ptr [bp+6]
	add	bx,si
	fld	dword ptr [bp+14]
	push	es
	push	bx
	call	far ptr F_FTOL@
	pop	bx
	pop	es
	mov	byte ptr es:[bx],al
	jmp	short @39@8
@39@5:
	fld	dword ptr [bp+14]
	fldz	
	fcompp
	fstsw	word ptr [bp-6]
	fwait	
	mov	ax,word ptr [bp-6]
	sahf	
	jae	short @39@7
	les	bx,dword ptr [bp+6]
	add	bx,si
	mov	byte ptr es:[bx],63
	jmp	short @39@8
@39@7:
	les	bx,dword ptr [bp+6]
	add	bx,si
	mov	byte ptr es:[bx],0
@39@8:
	fld	dword ptr [bp+18]
	fldz	
	fcompp
	fstsw	word ptr [bp-6]
	fwait	
	mov	ax,word ptr [bp-6]
	sahf	
	ja	short @39@11
	fld	dword ptr [bp+18]
	fcomp	dword ptr DGROUP:s@+1498
	fstsw	word ptr [bp-6]
	fwait	
	mov	ax,word ptr [bp-6]
	sahf	
	jae	short @39@11
	les	bx,dword ptr [bp+6]
	fld	dword ptr [bp+18]
	push	es
	push	bx
	call	far ptr F_FTOL@
	pop	bx
	pop	es
	mov	byte ptr es:[bx+si+1],al
	jmp	short @39@14
@39@11:
	fld	dword ptr [bp+18]
	fldz	
	fcompp
	fstsw	word ptr [bp-6]
	fwait	
	mov	ax,word ptr [bp-6]
	sahf	
	jae	short @39@13
	les	bx,dword ptr [bp+6]
	mov	byte ptr es:[bx+si+1],63
	jmp	short @39@14
@39@13:
	les	bx,dword ptr [bp+6]
	mov	byte ptr es:[bx+si+1],0
@39@14:
	fld	dword ptr [bp+22]
	fldz	
	fcompp
	fstsw	word ptr [bp-6]
	fwait	
	mov	ax,word ptr [bp-6]
	sahf	
	ja	short @39@17
	fld	dword ptr [bp+22]
	fcomp	dword ptr DGROUP:s@+1498
	fstsw	word ptr [bp-6]
	fwait	
	mov	ax,word ptr [bp-6]
	sahf	
	jae	short @39@17
	les	bx,dword ptr [bp+6]
	fld	dword ptr [bp+22]
	push	es
	push	bx
	call	far ptr F_FTOL@
	pop	bx
	pop	es
	mov	byte ptr es:[bx+si+2],al
	jmp	short @39@20
@39@17:
	fld	dword ptr [bp+22]
	fldz	
	fcompp
	fstsw	word ptr [bp-6]
	fwait	
	mov	ax,word ptr [bp-6]
	sahf	
	jae	short @39@19
	les	bx,dword ptr [bp+6]
	mov	byte ptr es:[bx+si+2],63
	jmp	short @39@20
@39@19:
	les	bx,dword ptr [bp+6]
	mov	byte ptr es:[bx+si+2],0
@39@20:
	fld	dword ptr [bp-10]
	fadd	dword ptr [bp+14]
	fstp	dword ptr [bp+14]
	fld	dword ptr [bp-14]
	fadd	dword ptr [bp+18]
	fstp	dword ptr [bp+18]
	fld	dword ptr [bp-18]
	fadd	dword ptr [bp+22]
	fstp	dword ptr [bp+22]
	add	si,3
	dec	di
	fwait	
@39@21:
	or	di,di
	jne	@39@2
	pop	di
	pop	si
	leave	
	ret	
@shade$qnuciiffffff	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@from_vehicle$qv	proc	far
	push	bp
	mov	bp,sp
	sub	sp,2
	fld	qword ptr DGROUP:_dzat_x
	fstp	dword ptr DGROUP:_cam_x
	fld	qword ptr DGROUP:_dzat_y
	fstp	dword ptr DGROUP:_cam_y
	fld	qword ptr DGROUP:_dzat_z
	fstp	dword ptr DGROUP:_cam_z
	fwait	
	mov	eax,dword ptr DGROUP:_user_alfa
	mov	dword ptr DGROUP:_alfa,eax
	fld	dword ptr DGROUP:_user_beta
	fadd	dword ptr DGROUP:_navigation_beta
	fadd	dword ptr DGROUP:s@+1502
	fstp	dword ptr DGROUP:_beta
	fld	dword ptr DGROUP:_beta
	fcomp	dword ptr DGROUP:s@+1506
	fstsw	word ptr [bp-2]
	fwait	
	mov	ax,word ptr [bp-2]
	sahf	
	jb	short @40@3
	fld	dword ptr DGROUP:s@+1506
	fsubr	dword ptr DGROUP:_beta
	fstp	dword ptr DGROUP:_beta
	fwait	
@40@3:
	push	cs
	call	near ptr @change_angle_of_view$qv
	leave	
	ret	
@from_vehicle$qv	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@from_user$qv	proc	far
	mov	eax,dword ptr DGROUP:_pos_x
	mov	dword ptr DGROUP:_cam_x,eax
	mov	eax,dword ptr DGROUP:_pos_y
	mov	dword ptr DGROUP:_cam_y,eax
	mov	eax,dword ptr DGROUP:_pos_z
	mov	dword ptr DGROUP:_cam_z,eax
	mov	eax,dword ptr DGROUP:_user_alfa
	mov	dword ptr DGROUP:_alfa,eax
	mov	eax,dword ptr DGROUP:_user_beta
	mov	dword ptr DGROUP:_beta,eax
	push	cs
	call	near ptr @change_angle_of_view$qv
	ret	
@from_user$qv	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@watch$qdddddd	proc	far
	push	bp
	mov	bp,sp
	sub	sp,106
	fld	qword ptr [bp+6]
	fsub	qword ptr [bp+30]
	fstp	qword ptr [bp-8]
	fld	qword ptr [bp+14]
	fsub	qword ptr [bp+38]
	fstp	qword ptr [bp-16]
	fld	qword ptr [bp+22]
	fsub	qword ptr [bp+46]
	fstp	qword ptr [bp-24]
	fld	qword ptr [bp-8]
	fmul	qword ptr [bp-8]
	fld	qword ptr [bp-16]
	fmul	qword ptr [bp-16]
	fadd	
	fld	qword ptr [bp-24]
	fmul	qword ptr [bp-24]
	fadd	
	sub	sp,8
	fstp	qword ptr [bp-114]
	fwait	
	call	far ptr _sqrt
	add	sp,8
	fstp	qword ptr [bp-32]
	fld	qword ptr [bp+6]
	fsubr	qword ptr [bp+30]
	fstp	qword ptr [bp+30]
	fld	qword ptr [bp+14]
	fsubr	qword ptr [bp+38]
	fstp	qword ptr [bp+38]
	fld	qword ptr [bp+22]
	fsubr	qword ptr [bp+46]
	fstp	qword ptr [bp+46]
	fldz	
	fstp	qword ptr [bp-64]
	fldz	
	fstp	qword ptr [bp-72]
	fld	qword ptr DGROUP:s@+1510
	fstp	qword ptr [bp-80]
	jmp	@42@15
@42@2:
	fld	qword ptr DGROUP:s@+1526
	fstp	qword ptr [bp-56]
	fld	qword ptr [bp-80]
	fdiv	dword ptr DGROUP:s@+1534
	fstp	qword ptr [bp-40]
	fld	dword ptr DGROUP:_beta
	sub	sp,8
	fstp	qword ptr [bp-114]
	fwait	
	call	far ptr _sin
	add	sp,8
	fstp	qword ptr [bp-88]
	fld	dword ptr DGROUP:_beta
	sub	sp,8
	fstp	qword ptr [bp-114]
	fwait	
	call	far ptr _cos
	add	sp,8
	fstp	qword ptr [bp-96]
	fld	qword ptr [bp-72]
	fsub	qword ptr [bp-80]
	jmp	@42@6
@42@3:
	fld	dword ptr DGROUP:_alfa
	sub	sp,8
	fstp	qword ptr [bp-114]
	fwait	
	call	far ptr _cos
	add	sp,8
	fld	qword ptr [bp-32]
	fchs	
	fmul	qword ptr [bp-88]
	fmul	
	fsub	qword ptr [bp+30]
	fstp	qword ptr [bp-8]
	fld	dword ptr DGROUP:_alfa
	sub	sp,8
	fstp	qword ptr [bp-114]
	fwait	
	call	far ptr _sin
	add	sp,8
	fmul	qword ptr [bp-32]
	fsub	qword ptr [bp+38]
	fstp	qword ptr [bp-16]
	fld	dword ptr DGROUP:_alfa
	sub	sp,8
	fstp	qword ptr [bp-114]
	fwait	
	call	far ptr _cos
	add	sp,8
	fld	qword ptr [bp-32]
	fmul	qword ptr [bp-96]
	fmul	
	fsub	qword ptr [bp+46]
	fstp	qword ptr [bp-24]
	fld	qword ptr [bp-8]
	fmul	qword ptr [bp-8]
	fld	qword ptr [bp-16]
	fmul	qword ptr [bp-16]
	fadd	
	fld	qword ptr [bp-24]
	fmul	qword ptr [bp-24]
	fadd	
	fstp	qword ptr [bp-48]
	fld	qword ptr [bp-48]
	fcomp	qword ptr [bp-56]
	fstsw	word ptr [bp-106]
	fwait	
	mov	ax,word ptr [bp-106]
	sahf	
	jae	short @42@5
	fld	qword ptr [bp-48]
	fstp	qword ptr [bp-56]
	fld	dword ptr DGROUP:_alfa
	fstp	qword ptr [bp-72]
	fwait	
@42@5:
	fld	dword ptr DGROUP:_alfa
	fadd	qword ptr [bp-40]
@42@6:
	fstp	dword ptr DGROUP:_alfa
	fwait	
	fld	dword ptr DGROUP:_alfa
	fld	qword ptr [bp-72]
	fadd	qword ptr [bp-80]
	fcompp
	fstsw	word ptr [bp-106]
	fwait	
	mov	ax,word ptr [bp-106]
	sahf	
	ja	@42@3
	fld	qword ptr [bp-72]
	fstp	dword ptr DGROUP:_alfa
	fld	dword ptr DGROUP:_alfa
	sub	sp,8
	fstp	qword ptr [bp-114]
	fwait	
	call	far ptr _sin
	add	sp,8
	fmul	qword ptr [bp-32]
	fsub	qword ptr [bp+38]
	fstp	qword ptr [bp-16]
	fld	qword ptr [bp-16]
	fmul	qword ptr [bp-16]
	fstp	qword ptr [bp-16]
	fld	dword ptr DGROUP:_alfa
	sub	sp,8
	fstp	qword ptr [bp-114]
	fwait	
	call	far ptr _cos
	add	sp,8
	fstp	qword ptr [bp-104]
	fld	qword ptr DGROUP:s@+1526
	fstp	qword ptr [bp-56]
	fld	qword ptr [bp-80]
	fdiv	dword ptr DGROUP:s@+1534
	fstp	qword ptr [bp-40]
	fld	qword ptr [bp-64]
	fsub	qword ptr [bp-80]
	jmp	@42@12
@42@9:
	fld	dword ptr DGROUP:_beta
	sub	sp,8
	fstp	qword ptr [bp-114]
	fwait	
	call	far ptr _sin
	add	sp,8
	fld	qword ptr [bp-32]
	fchs	
	fmul	
	fmul	qword ptr [bp-104]
	fsub	qword ptr [bp+30]
	fstp	qword ptr [bp-8]
	fld	dword ptr DGROUP:_beta
	sub	sp,8
	fstp	qword ptr [bp-114]
	fwait	
	call	far ptr _cos
	add	sp,8
	fmul	qword ptr [bp-32]
	fmul	qword ptr [bp-104]
	fsub	qword ptr [bp+46]
	fstp	qword ptr [bp-24]
	fld	qword ptr [bp-8]
	fmul	qword ptr [bp-8]
	fadd	qword ptr [bp-16]
	fld	qword ptr [bp-24]
	fmul	qword ptr [bp-24]
	fadd	
	fstp	qword ptr [bp-48]
	fld	qword ptr [bp-48]
	fcomp	qword ptr [bp-56]
	fstsw	word ptr [bp-106]
	fwait	
	mov	ax,word ptr [bp-106]
	sahf	
	jae	short @42@11
	fld	qword ptr [bp-48]
	fstp	qword ptr [bp-56]
	fld	dword ptr DGROUP:_beta
	fstp	qword ptr [bp-64]
	fwait	
@42@11:
	fld	dword ptr DGROUP:_beta
	fadd	qword ptr [bp-40]
@42@12:
	fstp	dword ptr DGROUP:_beta
	fwait	
	fld	dword ptr DGROUP:_beta
	fld	qword ptr [bp-64]
	fadd	qword ptr [bp-80]
	fcompp
	fstsw	word ptr [bp-106]
	fwait	
	mov	ax,word ptr [bp-106]
	sahf	
	ja	@42@9
	fld	qword ptr [bp-64]
	fstp	dword ptr DGROUP:_beta
	fld	dword ptr DGROUP:s@+1538
	fdivr	qword ptr [bp-80]
	fstp	qword ptr [bp-80]
@42@15:
	fwait	
	fld	qword ptr [bp-80]
	fcomp	qword ptr DGROUP:s@+1518
	fstsw	word ptr [bp-106]
	fwait	
	mov	ax,word ptr [bp-106]
	sahf	
	ja	@42@2
	fld	dword ptr DGROUP:_alfa
	fdiv	qword ptr DGROUP:_deg
	fstp	dword ptr DGROUP:_alfa
	fld	dword ptr DGROUP:_beta
	fdiv	qword ptr DGROUP:_deg
	fstp	dword ptr DGROUP:_beta
	fwait	
	leave	
	ret	
@watch$qdddddd	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@xy$qdddddd	proc	far
	push	bp
	mov	bp,sp
	sub	sp,42
	fld	qword ptr [bp+30]
	fsub	qword ptr [bp+6]
	fstp	qword ptr [bp-8]
	fld	qword ptr [bp+38]
	fsub	qword ptr [bp+14]
	fstp	qword ptr [bp-16]
	fld	qword ptr [bp+46]
	fsub	qword ptr [bp+22]
	fstp	qword ptr [bp-24]
	fld	dword ptr DGROUP:_opt_pcosbeta
	fmul	qword ptr [bp-8]
	fld	dword ptr DGROUP:_opt_psinbeta
	fmul	qword ptr [bp-24]
	fadd	
	fstp	qword ptr DGROUP:_delta_x
	fld	dword ptr DGROUP:_opt_tcosbeta
	fmul	qword ptr [bp-24]
	fld	dword ptr DGROUP:_opt_tsinbeta
	fmul	qword ptr [bp-8]
	fsub	
	fstp	qword ptr [bp-32]
	fld	dword ptr DGROUP:_opt_tcosalfa
	fmul	qword ptr [bp-32]
	fld	dword ptr DGROUP:_opt_tsinalfa
	fmul	qword ptr [bp-16]
	fadd	
	fstp	qword ptr [bp-40]
	fld	dword ptr DGROUP:_opt_pcosalfa
	fmul	qword ptr [bp-16]
	fld	dword ptr DGROUP:_opt_psinalfa
	fmul	qword ptr [bp-32]
	fsub	
	fstp	qword ptr DGROUP:_delta_y
	fld	qword ptr [bp-40]
	fcomp	qword ptr DGROUP:s@+1542
	fstsw	word ptr [bp-42]
	fwait	
	mov	ax,word ptr [bp-42]
	sahf	
	jbe	short @43@4
	fld	qword ptr [bp-40]
	fdivr	qword ptr DGROUP:_delta_x
	fstp	qword ptr DGROUP:_delta_x
	fld	qword ptr [bp-40]
	fdivr	qword ptr DGROUP:_delta_y
	fstp	qword ptr DGROUP:_delta_y
	fwait	
	mov	al,1
	leave	
	ret	
@43@4:
	mov	al,0
	leave	
	ret	
@xy$qdddddd	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@p_Forward$qf	proc	far
	push	bp
	mov	bp,sp
	fld	dword ptr [bp+6]
	fmul	dword ptr DGROUP:_opt_tsinbeta
	fmul	dword ptr DGROUP:_opt_tcosalfa
	fsubr	dword ptr DGROUP:_pos_x
	fstp	dword ptr DGROUP:_pos_x
	fld	dword ptr [bp+6]
	fmul	dword ptr DGROUP:_opt_tcosbeta
	fmul	dword ptr DGROUP:_opt_tcosalfa
	fadd	dword ptr DGROUP:_pos_z
	fstp	dword ptr DGROUP:_pos_z
	fwait	
	pop	bp
	ret	
@p_Forward$qf	endp
NOCTIS-0_TEXT	ends
_BSS	segment word public use16 'BSS'
_mox	label	qword
	db	8 dup (?)
_moy	label	qword
	db	8 dup (?)
_moz	label	qword
	db	8 dup (?)
_BSS	ends
NOCTIS-0_TEXT	segment byte public use16 'CODE'
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@moonorigin$qi	proc	far
	push	bp
	mov	bp,sp
	sub	sp,50
	push	si
	mov	si,word ptr [bp+6]
	mov	bx,si
	shl	bx,3
	fld	qword ptr DGROUP:_nearstar_p_orb_ray[bx]
	mov	bx,si
	shl	bx,3
	fmul	qword ptr DGROUP:_nearstar_p_orb_ray[bx]
	fstp	qword ptr [bp-24]
	fld	qword ptr DGROUP:_s_m
	fdiv	qword ptr [bp-24]
	sub	sp,8
	fstp	qword ptr [bp-60]
	fwait	
	call	far ptr _sqrt
	add	sp,8
	fstp	qword ptr [bp-16]
	fld	qword ptr DGROUP:_secs
	fmul	qword ptr [bp-16]
	fmul	qword ptr DGROUP:s@+1550
	fdiv	dword ptr DGROUP:s@+1502
	fstp	qword ptr [bp-40]
	mov	bx,si
	shl	bx,3
	fld	qword ptr DGROUP:_nearstar_p_orb_tilt[bx]
	fmul	qword ptr DGROUP:_deg
	fstp	qword ptr [bp-32]
	fld	qword ptr [bp-40]
	sub	sp,8
	fstp	qword ptr [bp-60]
	fwait	
	call	far ptr _sin
	add	sp,8
	mov	bx,si
	shl	bx,3
	fld	qword ptr DGROUP:_nearstar_p_orb_ray[bx]
	fchs	
	fmul	
	fstp	tbyte ptr [bp-50]
	fld	qword ptr [bp-32]
	sub	sp,8
	fstp	qword ptr [bp-60]
	fwait	
	call	far ptr _cos
	add	sp,8
	fld	tbyte ptr [bp-50]
	fmul	
	fstp	qword ptr [bp-8]
	fld	qword ptr [bp-40]
	sub	sp,8
	fstp	qword ptr [bp-60]
	fwait	
	call	far ptr _cos
	add	sp,8
	mov	bx,si
	shl	bx,3
	fmul	qword ptr DGROUP:_nearstar_p_orb_ray[bx]
	fstp	tbyte ptr [bp-50]
	fld	qword ptr [bp-32]
	sub	sp,8
	fstp	qword ptr [bp-60]
	fwait	
	call	far ptr _cos
	add	sp,8
	fld	tbyte ptr [bp-50]
	fmul	
	fstp	qword ptr DGROUP:_moz
	fld	qword ptr [bp-32]
	sub	sp,8
	fstp	qword ptr [bp-60]
	fwait	
	call	far ptr _sin
	add	sp,8
	mov	bx,si
	shl	bx,3
	fmul	qword ptr DGROUP:_nearstar_p_orb_ray[bx]
	fstp	qword ptr DGROUP:_moy
	mov	bx,si
	shl	bx,3
	fld	qword ptr DGROUP:_nearstar_p_orb_ecc[bx]
	fmul	qword ptr DGROUP:_moz
	fstp	qword ptr DGROUP:_moz
	mov	bx,si
	shl	bx,3
	fld	qword ptr DGROUP:_nearstar_p_orb_orient[bx]
	fstp	qword ptr [bp-40]
	fld	qword ptr [bp-40]
	sub	sp,8
	fstp	qword ptr [bp-60]
	fwait	
	call	far ptr _cos
	add	sp,8
	fmul	qword ptr [bp-8]
	fstp	tbyte ptr [bp-50]
	fld	qword ptr [bp-40]
	sub	sp,8
	fstp	qword ptr [bp-60]
	fwait	
	call	far ptr _sin
	add	sp,8
	fmul	qword ptr DGROUP:_moz
	fld	tbyte ptr [bp-50]
	fadd	
	fstp	qword ptr DGROUP:_mox
	fld	qword ptr [bp-40]
	sub	sp,8
	fstp	qword ptr [bp-60]
	fwait	
	call	far ptr _cos
	add	sp,8
	fmul	qword ptr DGROUP:_moz
	fstp	tbyte ptr [bp-50]
	fld	qword ptr [bp-40]
	sub	sp,8
	fstp	qword ptr [bp-60]
	fwait	
	call	far ptr _sin
	add	sp,8
	fmul	qword ptr [bp-8]
	fld	tbyte ptr [bp-50]
	fsubr	
	fstp	qword ptr DGROUP:_moz
	fwait	
	pop	si
	leave	
	ret	
@moonorigin$qi	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@planet_xyz$qi	proc	far
	push	bp
	mov	bp,sp
	sub	sp,58
	push	si
	mov	si,word ptr [bp+6]
	mov	bx,si
	shl	bx,3
	fld	qword ptr DGROUP:_nearstar_p_orb_ray[bx]
	mov	bx,si
	shl	bx,3
	fmul	qword ptr DGROUP:_nearstar_p_orb_ray[bx]
	fstp	qword ptr [bp-48]
	mov	bx,si
	add	bx,bx
	fwait	
	cmp	word ptr DGROUP:_nearstar_p_owner[bx],-1
	jle	short @46@3
	mov	bx,si
	add	bx,bx
	mov	bx,word ptr DGROUP:_nearstar_p_owner[bx]
	shl	bx,3
	fld	qword ptr DGROUP:_nearstar_p_ray[bx]
	fstp	qword ptr [bp-8]
	fld	qword ptr DGROUP:s@+1558
	fmul	qword ptr [bp-8]
	fmul	qword ptr [bp-8]
	fmul	qword ptr [bp-8]
	fmul	qword ptr DGROUP:s@+1566
	fstp	qword ptr [bp-32]
	fld	qword ptr [bp-32]
	fdiv	qword ptr [bp-48]
	jmp	short @46@4
@46@3:
	fld	qword ptr DGROUP:_s_m
	fdiv	qword ptr [bp-48]
@46@4:
	sub	sp,8
	fstp	qword ptr [bp-68]
	fwait	
	call	far ptr _sqrt
	add	sp,8
	fstp	qword ptr [bp-40]
	fwait	
	fld	qword ptr DGROUP:_secs
	fmul	qword ptr [bp-40]
	fmul	qword ptr DGROUP:s@+1550
	fdiv	dword ptr DGROUP:s@+1502
	fstp	qword ptr [bp-24]
	mov	bx,si
	shl	bx,3
	fld	qword ptr DGROUP:_nearstar_p_orb_tilt[bx]
	fmul	qword ptr DGROUP:_deg
	fstp	qword ptr [bp-16]
	fld	qword ptr [bp-24]
	sub	sp,8
	fstp	qword ptr [bp-68]
	fwait	
	call	far ptr _sin
	add	sp,8
	mov	bx,si
	shl	bx,3
	fld	qword ptr DGROUP:_nearstar_p_orb_ray[bx]
	fchs	
	fmul	
	fstp	tbyte ptr [bp-58]
	fld	qword ptr [bp-16]
	sub	sp,8
	fstp	qword ptr [bp-68]
	fwait	
	call	far ptr _cos
	add	sp,8
	fld	tbyte ptr [bp-58]
	fmul	
	fstp	qword ptr [bp-8]
	fld	qword ptr [bp-24]
	sub	sp,8
	fstp	qword ptr [bp-68]
	fwait	
	call	far ptr _cos
	add	sp,8
	mov	bx,si
	shl	bx,3
	fmul	qword ptr DGROUP:_nearstar_p_orb_ray[bx]
	fstp	tbyte ptr [bp-58]
	fld	qword ptr [bp-16]
	sub	sp,8
	fstp	qword ptr [bp-68]
	fwait	
	call	far ptr _cos
	add	sp,8
	fld	tbyte ptr [bp-58]
	fmul	
	fstp	qword ptr DGROUP:_plz
	fld	qword ptr [bp-16]
	sub	sp,8
	fstp	qword ptr [bp-68]
	fwait	
	call	far ptr _sin
	add	sp,8
	mov	bx,si
	shl	bx,3
	fmul	qword ptr DGROUP:_nearstar_p_orb_ray[bx]
	fstp	qword ptr DGROUP:_ply
	mov	bx,si
	shl	bx,3
	fld	qword ptr DGROUP:_nearstar_p_orb_ecc[bx]
	fmul	qword ptr DGROUP:_plz
	fstp	qword ptr DGROUP:_plz
	mov	bx,si
	shl	bx,3
	fld	qword ptr DGROUP:_nearstar_p_orb_orient[bx]
	fstp	qword ptr [bp-24]
	fld	qword ptr [bp-24]
	sub	sp,8
	fstp	qword ptr [bp-68]
	fwait	
	call	far ptr _cos
	add	sp,8
	fmul	qword ptr [bp-8]
	fstp	tbyte ptr [bp-58]
	fld	qword ptr [bp-24]
	sub	sp,8
	fstp	qword ptr [bp-68]
	fwait	
	call	far ptr _sin
	add	sp,8
	fmul	qword ptr DGROUP:_plz
	fld	tbyte ptr [bp-58]
	fadd	
	fstp	qword ptr DGROUP:_plx
	fld	qword ptr [bp-24]
	sub	sp,8
	fstp	qword ptr [bp-68]
	fwait	
	call	far ptr _cos
	add	sp,8
	fmul	qword ptr DGROUP:_plz
	fstp	tbyte ptr [bp-58]
	fld	qword ptr [bp-24]
	sub	sp,8
	fstp	qword ptr [bp-68]
	fwait	
	call	far ptr _sin
	add	sp,8
	fmul	qword ptr [bp-8]
	fld	tbyte ptr [bp-58]
	fsubr	
	fstp	qword ptr DGROUP:_plz
	fld	qword ptr DGROUP:_nearstar_x
	fadd	qword ptr DGROUP:_plx
	fstp	qword ptr DGROUP:_plx
	fld	qword ptr DGROUP:_nearstar_y
	fadd	qword ptr DGROUP:_ply
	fstp	qword ptr DGROUP:_ply
	fld	qword ptr DGROUP:_nearstar_z
	fadd	qword ptr DGROUP:_plz
	fstp	qword ptr DGROUP:_plz
	mov	bx,si
	add	bx,bx
	fwait	
	cmp	word ptr DGROUP:_nearstar_p_owner[bx],-1
	jle	short @46@7
	mov	bx,si
	add	bx,bx
	push	word ptr DGROUP:_nearstar_p_owner[bx]
	push	cs
	call	near ptr @moonorigin$qi
	add	sp,2
	fld	qword ptr DGROUP:_mox
	fadd	qword ptr DGROUP:_plx
	fstp	qword ptr DGROUP:_plx
	fld	qword ptr DGROUP:_moy
	fadd	qword ptr DGROUP:_ply
	fstp	qword ptr DGROUP:_ply
	fld	qword ptr DGROUP:_moz
	fadd	qword ptr DGROUP:_plz
	fstp	qword ptr DGROUP:_plz
	fwait	
@46@7:
	pop	si
	leave	
	ret	
@planet_xyz$qi	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@rtp$qi	proc	far
	push	bp
	mov	bp,sp
	sub	sp,32
	push	si
	mov	si,word ptr [bp+6]
	mov	bx,si
	shl	bx,3
	fld	qword ptr DGROUP:_nearstar_p_orb_ray[bx]
	mov	bx,si
	shl	bx,3
	fmul	qword ptr DGROUP:_nearstar_p_orb_ray[bx]
	fstp	qword ptr [bp-24]
	mov	bx,si
	add	bx,bx
	fwait	
	cmp	word ptr DGROUP:_nearstar_p_owner[bx],-1
	jle	short @47@3
	mov	bx,si
	add	bx,bx
	mov	bx,word ptr DGROUP:_nearstar_p_owner[bx]
	shl	bx,3
	fld	qword ptr DGROUP:_nearstar_p_ray[bx]
	fstp	qword ptr [bp-32]
	fld	qword ptr DGROUP:s@+1558
	fmul	qword ptr [bp-32]
	fmul	qword ptr [bp-32]
	fmul	qword ptr [bp-32]
	fmul	qword ptr DGROUP:s@+1566
	fstp	qword ptr [bp-8]
	fld	qword ptr [bp-8]
	fdiv	qword ptr [bp-24]
	jmp	short @47@4
@47@3:
	fld	qword ptr DGROUP:_s_m
	fdiv	qword ptr [bp-24]
@47@4:
	sub	sp,8
	fstp	qword ptr [bp-42]
	fwait	
	call	far ptr _sqrt
	add	sp,8
	fstp	qword ptr [bp-16]
	fwait	
	fld	dword ptr DGROUP:s@+1506
	fdiv	qword ptr [bp-16]
	pop	si
	leave	
	ret	
@rtp$qi	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@planet_viewpoint$qdd	proc	far
	push	bp
	mov	bp,sp
	sub	sp,28
	push	si
	push	di
	xor	di,di
	fld	qword ptr DGROUP:s@+1574
	fstp	qword ptr [bp-24]
	xor	si,si
	fwait	
@48@2:
	mov	word ptr [bp-28],si
	mov	word ptr [bp-26],0
	fild	dword ptr [bp-28]
	fmul	qword ptr DGROUP:_deg
	sub	sp,8
	fstp	qword ptr [bp-40]
	fwait	
	call	far ptr _cos
	add	sp,8
	fadd	qword ptr DGROUP:_plx
	fsub	qword ptr [bp+6]
	fstp	qword ptr [bp-8]
	fwait	
	mov	word ptr [bp-28],si
	mov	word ptr [bp-26],0
	fild	dword ptr [bp-28]
	fmul	qword ptr DGROUP:_deg
	sub	sp,8
	fstp	qword ptr [bp-40]
	fwait	
	call	far ptr _sin
	add	sp,8
	fadd	qword ptr DGROUP:_plz
	fsub	qword ptr [bp+14]
	fstp	qword ptr [bp-16]
	fld	qword ptr [bp-8]
	fmul	qword ptr [bp-8]
	fld	qword ptr [bp-16]
	fmul	qword ptr [bp-16]
	fadd	
	fstp	qword ptr [bp-8]
	fld	qword ptr [bp-8]
	fcomp	qword ptr [bp-24]
	fstsw	word ptr [bp-28]
	fwait	
	mov	ax,word ptr [bp-28]
	sahf	
	jae	short @48@4
	mov	di,si
	fld	qword ptr [bp-8]
	fstp	qword ptr [bp-24]
	fwait	
@48@4:
	inc	si
	cmp	si,360
	jb	@48@2
	mov	ax,di
	pop	di
	pop	si
	leave	
	ret	
@planet_viewpoint$qdd	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@cplx_planet_viewpoint$qi	proc	far
	push	bp
	mov	bp,sp
	sub	sp,16
	push	si
	push	di
	mov	si,word ptr [bp+6]
	mov	bx,si
	add	bx,bx
	cmp	word ptr DGROUP:_nearstar_p_owner[bx],-1
	je	short @49@5
	mov	bx,si
	add	bx,bx
	mov	di,word ptr DGROUP:_nearstar_p_owner[bx]
	mov	al,byte ptr DGROUP:_nearstar_p_type[di]
	cbw	
	cmp	ax,10
	jne	short @49@5
	push	di
	push	cs
	call	near ptr @planet_xyz$qi
	add	sp,2
	fld	qword ptr DGROUP:_plx
	fstp	qword ptr [bp-8]
	fld	qword ptr DGROUP:_plz
	fstp	qword ptr [bp-16]
	push	si
	fwait	
	push	cs
	call	near ptr @planet_xyz$qi
	add	sp,2
	fld	qword ptr [bp-16]
	sub	sp,8
	fstp	qword ptr [bp-28]
	fld	qword ptr [bp-8]
	sub	sp,8
	fstp	qword ptr [bp-36]
	jmp	short @49@6
@49@5:
	fld	qword ptr DGROUP:_nearstar_z
	sub	sp,8
	fstp	qword ptr [bp-28]
	fld	qword ptr DGROUP:_nearstar_x
	sub	sp,8
	fstp	qword ptr [bp-36]
@49@6:
	fwait	
	push	cs
	call	near ptr @planet_viewpoint$qdd
	add	sp,16
	pop	di
	pop	si
	leave	
	ret	
@cplx_planet_viewpoint$qi	endp
NOCTIS-0_TEXT	ends
_DATA	segment word public use16 'DATA'
_previous_flares_value	label	byte
	db	0
_DATA	ends
NOCTIS-0_TEXT	segment byte public use16 'CODE'
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@setfx$qc	proc	far
	push	bp
	mov	bp,sp
	mov	al,byte ptr DGROUP:_flares
	mov	byte ptr DGROUP:_previous_flares_value,al
	mov	al,byte ptr [bp+6]
	mov	byte ptr DGROUP:_flares,al
	pop	bp
	ret	
@setfx$qc	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@chgfx$qc	proc	far
	push	bp
	mov	bp,sp
	mov	al,byte ptr [bp+6]
	mov	byte ptr DGROUP:_flares,al
	pop	bp
	ret	
@chgfx$qc	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@resetfx$qv	proc	far
	mov	al,byte ptr DGROUP:_previous_flares_value
	mov	byte ptr DGROUP:_flares,al
	ret	
@resetfx$qv	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@stick$qulululul	proc	far
	push	bp
	mov	bp,sp
	sub	sp,46
	push	si
	push	di
	mov	eax,dword ptr DGROUP:_adapted
	mov	dword ptr [bp-20],eax
	mov	cx,word ptr [bp-20]
	and	eax,large 0FFFF0000h
	shld	edx,eax,16
	mov	word ptr [bp-22],dx
	mov	word ptr [bp-24],ax
	mov	eax,dword ptr [bp+6]
	cmp	eax,dword ptr [bp+14]
	jne	@53@25
	mov	eax,dword ptr [bp+18]
	cmp	eax,dword ptr [bp+10]
	jb	short @53@4
	mov	bx,word ptr [bp+10]
	add	bx,bx
	mov	ax,word ptr DGROUP:_riga[bx]
	add	ax,word ptr [bp+6]
	mov	word ptr [bp-14],ax
	mov	bx,word ptr [bp+18]
	add	bx,bx
	jmp	short @53@5
@53@4:
	mov	bx,word ptr [bp+18]
	add	bx,bx
	mov	ax,word ptr DGROUP:_riga[bx]
	add	ax,word ptr [bp+6]
	mov	word ptr [bp-14],ax
	mov	bx,word ptr [bp+10]
	add	bx,bx
@53@5:
	mov	ax,word ptr DGROUP:_riga[bx+2]
	mov	word ptr [bp-16],ax
	add	word ptr [bp-14],cx
	add	word ptr [bp-16],cx
	mov	cx,word ptr [bp-14]
	mov	al,byte ptr DGROUP:_flares
	cbw	
	mov	bx,ax
	cmp	bx,3
	ja	@53@50
	add	bx,bx
	jmp	word ptr cs:@53@C215[bx]
@53@10:
	les	bx,dword ptr [bp-24]
	add	bx,cx
	mov	si,bx
	mov	byte ptr es:[bx],62
	mov	ax,cx
	inc	ax
	mov	bx,word ptr [bp-24]
	add	bx,ax
	mov	byte ptr es:[bx],0
	add	cx,320
@53@11:
	cmp	cx,word ptr [bp-16]
	jb	short @53@10
	jmp	@53@50
@53@13:
	les	bx,dword ptr [bp-24]
	add	bx,cx
	mov	si,bx
	mov	dl,byte ptr es:[bx]
	and	dl,63
	mov	al,dl
	add	al,8
	mov	dl,al
	and	byte ptr es:[si],192
	cmp	dl,62
	jbe	short @53@15
	mov	dl,62
@53@15:
	les	bx,dword ptr [bp-24]
	add	bx,cx
	mov	si,bx
	add	byte ptr es:[bx],dl
	add	cx,320
@53@16:
	cmp	cx,word ptr [bp-16]
	jb	short @53@13
	jmp	@53@50
@53@18:
	les	bx,dword ptr [bp-24]
	add	bx,cx
	mov	si,bx
	mov	dl,byte ptr es:[bx]
	and	dl,63
	shr	dl,1
	and	byte ptr es:[si],192
	mov	bx,word ptr [bp-24]
	add	bx,cx
	mov	si,bx
	add	byte ptr es:[bx],dl
	add	cx,320
@53@19:
	cmp	cx,word ptr [bp-16]
	jb	short @53@18
	jmp	@53@50
@53@21:
	les	bx,dword ptr [bp-24]
	add	bx,cx
	mov	si,bx
	mov	byte ptr es:[bx],46
	mov	ax,cx
	inc	ax
	mov	bx,word ptr [bp-24]
	add	bx,ax
	mov	byte ptr es:[bx],30
	mov	ax,cx
	add	ax,2
	mov	bx,word ptr [bp-24]
	add	bx,ax
	mov	byte ptr es:[bx],19
	mov	ax,cx
	add	ax,3
	mov	bx,word ptr [bp-24]
	add	bx,ax
	mov	byte ptr es:[bx],14
	add	cx,320
@53@22:
	cmp	cx,word ptr [bp-16]
	jb	short @53@21
	jmp	@53@50
	jmp	@53@50
@53@25:
	mov	eax,dword ptr [bp+14]
	sub	eax,dword ptr [bp+6]
	mov	dword ptr [bp-28],eax
	mov	eax,dword ptr [bp+14]
	cmp	eax,dword ptr [bp+6]
	jae	short @53@27
	mov	eax,dword ptr [bp+6]
	mov	dword ptr [bp-40],eax
	mov	eax,dword ptr [bp+14]
	mov	dword ptr [bp+6],eax
	mov	eax,dword ptr [bp-40]
	mov	dword ptr [bp+14],eax
	mov	eax,dword ptr [bp+10]
	mov	dword ptr [bp-40],eax
	mov	eax,dword ptr [bp+18]
	mov	dword ptr [bp+10],eax
	mov	eax,dword ptr [bp-40]
	mov	dword ptr [bp+18],eax
	mov	eax,dword ptr [bp-28]
	not	eax
	inc	eax
	mov	dword ptr [bp-28],eax
@53@27:
	mov	eax,dword ptr [bp-28]
	mov	dword ptr [bp-4],eax
	mov	dword ptr [bp-12],eax
	mov	eax,dword ptr [bp+18]
	sub	eax,dword ptr [bp+10]
	mov	dword ptr [bp-32],eax
	mov	byte ptr [bp-33],0
	mov	eax,dword ptr [bp+18]
	cmp	eax,dword ptr [bp+10]
	jae	short @53@29
	mov	byte ptr [bp-33],1
	mov	eax,dword ptr [bp-32]
	not	eax
	inc	eax
	mov	dword ptr [bp-32],eax
@53@29:
	mov	eax,dword ptr [bp-32]
	mov	dword ptr [bp-8],eax
	cmp	eax,dword ptr [bp-12]
	jbe	short @53@31
	mov	dword ptr [bp-12],eax
@53@31:
	inc	dword ptr [bp-12]
	mov	eax,dword ptr [bp+14]
	shl	eax,16
	mov	dword ptr [bp+14],eax
	mov	eax,dword ptr [bp+6]
	shl	eax,16
	mov	dword ptr DGROUP:_global_x,eax
	mov	eax,dword ptr [bp+10]
	shl	eax,16
	mov	dword ptr DGROUP:_global_y,eax
	mov	eax,dword ptr [bp-4]
	shl	eax,16
	mov	dword ptr [bp-4],eax
	cdq	
	idiv	dword ptr [bp-12]
	mov	dword ptr [bp-4],eax
	and	dword ptr [bp-4],large 0FFFFh
	mov	eax,dword ptr [bp-8]
	shl	eax,16
	mov	dword ptr [bp-8],eax
	cdq	
	idiv	dword ptr [bp-12]
	mov	dword ptr [bp-8],eax
	and	dword ptr [bp-8],large 0FFFFh
	cmp	byte ptr [bp-33],0
	je	short @53@33
	mov	eax,dword ptr [bp-8]
	neg	eax
	mov	dword ptr [bp-8],eax
@53@33:
	mov	al,byte ptr DGROUP:_flares
	cbw	
	mov	bx,ax
	cmp	bx,3
	ja	@53@50
	add	bx,bx
	jmp	word ptr cs:@53@C220[bx]
@53@36:
	mov	eax,dword ptr DGROUP:_global_y
	shr	eax,16
	add	ax,ax
	mov	dx,ax
	mov	eax,dword ptr DGROUP:_global_x
	shr	eax,16
	mov	dword ptr [bp-40],eax
	mov	eax,dword ptr [bp-4]
	add	dword ptr DGROUP:_global_x,eax
	mov	eax,dword ptr [bp-8]
	add	dword ptr DGROUP:_global_y,eax
	mov	bx,dx
	mov	al,byte ptr DGROUP:_riga[bx]
	mov	ah,0
	mov	word ptr [bp-42],ax
	mov	al,byte ptr DGROUP:_riga[bx+1]
	mov	ah,0
	mov	word ptr [bp-44],ax
	shl	ax,8
	add	ax,word ptr [bp-42]
	movzx	eax,ax
	add	dword ptr [bp-40],eax
	mov	bx,word ptr [bp-40]
	mov	es,word ptr [bp-22]
	add	bx,word ptr [bp-24]
	mov	byte ptr es:[bx+4],0
	mov	bx,word ptr [bp-40]
	add	bx,word ptr [bp-24]
	mov	byte ptr es:[bx+5],62
@53@37:
	mov	eax,dword ptr DGROUP:_global_x
	cmp	eax,dword ptr [bp+14]
	jb	short @53@36
	jmp	@53@50
@53@39:
	mov	eax,dword ptr DGROUP:_global_y
	shr	eax,16
	add	ax,ax
	mov	word ptr [bp-38],ax
	mov	eax,dword ptr DGROUP:_global_x
	shr	eax,16
	mov	dword ptr [bp-42],eax
	mov	eax,dword ptr [bp-4]
	shl	eax,1
	add	dword ptr DGROUP:_global_x,eax
	mov	eax,dword ptr [bp-8]
	shl	eax,1
	add	dword ptr DGROUP:_global_y,eax
	mov	bx,word ptr [bp-38]
	mov	al,byte ptr DGROUP:_riga[bx]
	mov	ah,0
	mov	word ptr [bp-44],ax
	mov	al,byte ptr DGROUP:_riga[bx+1]
	mov	ah,0
	mov	word ptr [bp-46],ax
	shl	ax,8
	add	ax,word ptr [bp-44]
	movzx	eax,ax
	add	dword ptr [bp-42],eax
	mov	bx,word ptr [bp-42]
	mov	es,word ptr [bp-22]
	add	bx,word ptr [bp-24]
	mov	word ptr [bp-36],bx
	mov	al,byte ptr es:[bx+4]
	mov	ah,0
	shl	ax,2
	mov	dx,ax
	and	ax,255
	cmp	ax,223
	ja	short @53@41
	add	dx,32
	jmp	short @53@42
@53@41:
	mov	ax,dx
	and	ax,-256
	add	ax,251
	mov	dx,ax
@53@42:
	mov	ax,dx
	shr	ax,2
	and	al,255
	mov	es,word ptr [bp-22]
	mov	bx,word ptr [bp-36]
	mov	byte ptr es:[bx+4],al
@53@43:
	mov	eax,dword ptr DGROUP:_global_x
	cmp	eax,dword ptr [bp+14]
	jb	@53@39
	jmp	@53@50
@53@45:
	mov	eax,dword ptr DGROUP:_global_y
	shr	eax,16
	add	ax,ax
	mov	word ptr [bp-38],ax
	mov	eax,dword ptr DGROUP:_global_x
	shr	eax,16
	mov	dword ptr [bp-42],eax
	mov	eax,dword ptr [bp-4]
	add	dword ptr DGROUP:_global_x,eax
	mov	eax,dword ptr [bp-8]
	add	dword ptr DGROUP:_global_y,eax
	mov	bx,word ptr [bp-38]
	mov	al,byte ptr DGROUP:_riga[bx]
	mov	ah,0
	mov	word ptr [bp-44],ax
	mov	al,byte ptr DGROUP:_riga[bx+1]
	mov	ah,0
	mov	word ptr [bp-46],ax
	shl	ax,8
	add	ax,word ptr [bp-44]
	movzx	eax,ax
	add	dword ptr [bp-42],eax
	mov	bx,word ptr [bp-42]
	mov	es,word ptr [bp-22]
	add	bx,word ptr [bp-24]
	mov	di,bx
	mov	al,byte ptr es:[bx+4]
	mov	ah,0
	mov	dx,ax
	and	dx,63
	and	byte ptr es:[di+4],192
	shr	dx,1
	mov	bx,word ptr [bp-42]
	add	bx,word ptr [bp-24]
	mov	di,bx
	mov	al,byte ptr es:[bx+4]
	add	al,dl
	mov	byte ptr es:[di+4],al
@53@46:
	mov	eax,dword ptr DGROUP:_global_x
	cmp	eax,dword ptr [bp+14]
	jb	@53@45
	jmp	@53@50
@53@48:
	mov	eax,dword ptr DGROUP:_global_y
	shr	eax,16
	add	ax,ax
	mov	dx,ax
	mov	eax,dword ptr DGROUP:_global_x
	shr	eax,16
	mov	dword ptr [bp-40],eax
	mov	eax,dword ptr [bp-4]
	add	dword ptr DGROUP:_global_x,eax
	mov	eax,dword ptr [bp-8]
	add	dword ptr DGROUP:_global_y,eax
	mov	bx,dx
	mov	al,byte ptr DGROUP:_riga[bx]
	mov	ah,0
	mov	word ptr [bp-42],ax
	mov	al,byte ptr DGROUP:_riga[bx+1]
	mov	ah,0
	mov	word ptr [bp-44],ax
	shl	ax,8
	add	ax,word ptr [bp-42]
	movzx	eax,ax
	add	dword ptr [bp-40],eax
	mov	bx,word ptr [bp-40]
	mov	es,word ptr [bp-22]
	add	bx,word ptr [bp-24]
	mov	byte ptr es:[bx+4],206
	mov	bx,word ptr [bp-40]
	add	bx,word ptr [bp-24]
	mov	byte ptr es:[bx+5],211
	mov	bx,word ptr [bp-40]
	add	bx,word ptr [bp-24]
	mov	byte ptr es:[bx+6],222
	mov	bx,word ptr [bp-40]
	add	bx,word ptr [bp-24]
	mov	byte ptr es:[bx+7],238
@53@49:
	mov	eax,dword ptr DGROUP:_global_x
	cmp	eax,dword ptr [bp+14]
	jb	@53@48
@53@50:
	pop	di
	pop	si
	leave	
	ret	
@stick$qulululul	endp
@53@C220	label	word
	dw	@53@37
	dw	@53@43
	dw	@53@46
	dw	@53@49
@53@C215	label	word
	dw	@53@11
	dw	@53@16
	dw	@53@19
	dw	@53@22
NOCTIS-0_TEXT	ends
_DATA	segment word public use16 'DATA'
	db	1 dup (0)
_fpx	label	dword
	db	255
	db	255
	db	255
	db	255
_DATA	ends
_BSS	segment word public use16 'BSS'
_fpy	label	dword
	db	4 dup (?)
_p_rx	label	dword
	db	4 dup (?)
_p_ry	label	dword
	db	4 dup (?)
_p_rz	label	dword
	db	4 dup (?)
_BSS	ends
_DATA	segment word public use16 'DATA'
_stick_uneg	label	dword
	db	0
	db	0
	db	72
	db	67
_DATA	ends
NOCTIS-0_TEXT	segment byte public use16 'CODE'
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@stick3d$qffffff	proc	far
	push	bp
	mov	bp,sp
	sub	sp,40
	mov	dword ptr DGROUP:_fpx,large -1
	fld	dword ptr DGROUP:_cam_x
	fsubr	dword ptr [bp+6]
	fstp	dword ptr [bp+6]
	fld	dword ptr DGROUP:_cam_y
	fsubr	dword ptr [bp+10]
	fstp	dword ptr [bp+10]
	fld	dword ptr DGROUP:_cam_z
	fsubr	dword ptr [bp+14]
	fstp	dword ptr [bp+14]
	fld	dword ptr [bp+14]
	fmul	dword ptr DGROUP:_opt_tcosbeta
	fld	dword ptr [bp+6]
	fmul	dword ptr DGROUP:_opt_tsinbeta
	fsub	
	fstp	dword ptr [bp-12]
	fld	dword ptr [bp-12]
	fmul	dword ptr DGROUP:_opt_tcosalfa
	fld	dword ptr [bp+10]
	fmul	dword ptr DGROUP:_opt_tsinalfa
	fadd	
	fstp	dword ptr DGROUP:_p_rz
	fld	dword ptr DGROUP:_cam_x
	fsubr	dword ptr [bp+18]
	fstp	dword ptr [bp+18]
	fld	dword ptr DGROUP:_cam_y
	fsubr	dword ptr [bp+22]
	fstp	dword ptr [bp+22]
	fld	dword ptr DGROUP:_cam_z
	fsubr	dword ptr [bp+26]
	fstp	dword ptr [bp+26]
	fld	dword ptr [bp+26]
	fmul	dword ptr DGROUP:_opt_tcosbeta
	fld	dword ptr [bp+18]
	fmul	dword ptr DGROUP:_opt_tsinbeta
	fsub	
	fstp	dword ptr [bp-32]
	fld	dword ptr [bp-32]
	fmul	dword ptr DGROUP:_opt_tcosalfa
	fld	dword ptr [bp+22]
	fmul	dword ptr DGROUP:_opt_tsinalfa
	fadd	
	fstp	dword ptr [bp-28]
	fld	dword ptr [bp-28]
	fcomp	dword ptr DGROUP:_stick_uneg
	fstsw	word ptr [bp-40]
	fwait	
	mov	ax,word ptr [bp-40]
	sahf	
	jae	short @54@3
	fld	dword ptr DGROUP:_p_rz
	fcomp	dword ptr DGROUP:_stick_uneg
	fstsw	word ptr [bp-40]
	fwait	
	mov	ax,word ptr [bp-40]
	sahf	
	jb	@54@56
@54@3:
	fld	dword ptr [bp+6]
	fmul	dword ptr DGROUP:_opt_pcosbeta
	fld	dword ptr [bp+14]
	fmul	dword ptr DGROUP:_opt_psinbeta
	fadd	
	fstp	dword ptr DGROUP:_p_rx
	fld	dword ptr [bp+10]
	fmul	dword ptr DGROUP:_opt_pcosalfa
	fld	dword ptr [bp-12]
	fmul	dword ptr DGROUP:_opt_psinalfa
	fsub	
	fstp	dword ptr DGROUP:_p_ry
	fld	dword ptr [bp+18]
	fmul	dword ptr DGROUP:_opt_pcosbeta
	fld	dword ptr [bp+26]
	fmul	dword ptr DGROUP:_opt_psinbeta
	fadd	
	fstp	dword ptr [bp-20]
	fld	dword ptr [bp+22]
	fmul	dword ptr DGROUP:_opt_pcosalfa
	fld	dword ptr [bp-32]
	fmul	dword ptr DGROUP:_opt_psinalfa
	fsub	
	fstp	dword ptr [bp-24]
	fld	dword ptr [bp-28]
	fcomp	dword ptr DGROUP:_stick_uneg
	fstsw	word ptr [bp-40]
	fwait	
	mov	ax,word ptr [bp-40]
	sahf	
	jae	@54@8
	fld	dword ptr [bp-28]
	fsub	dword ptr DGROUP:_p_rz
	fstp	dword ptr [bp-16]
	fld	dword ptr DGROUP:_mindiff
	fchs	
	fcomp	dword ptr [bp-16]
	fstsw	word ptr [bp-40]
	fwait	
	mov	ax,word ptr [bp-40]
	sahf	
	ja	short @54@6
	fld	dword ptr [bp-16]
	fcomp	dword ptr DGROUP:_mindiff
	fstsw	word ptr [bp-40]
	fwait	
	mov	ax,word ptr [bp-40]
	sahf	
	jbe	short @54@7
@54@6:
	fld	dword ptr DGROUP:_stick_uneg
	fsub	dword ptr DGROUP:_p_rz
	fdiv	dword ptr [bp-16]
	fstp	dword ptr [bp-36]
	fld	dword ptr [bp-20]
	fsub	dword ptr DGROUP:_p_rx
	fmul	dword ptr [bp-36]
	fadd	dword ptr DGROUP:_p_rx
	fstp	dword ptr [bp-20]
	fld	dword ptr [bp-24]
	fsub	dword ptr DGROUP:_p_ry
	fmul	dword ptr [bp-36]
	fadd	dword ptr DGROUP:_p_ry
	fstp	dword ptr [bp-24]
	fwait	
@54@7:
	mov	eax,dword ptr DGROUP:_stick_uneg
	mov	dword ptr [bp-28],eax
	jmp	@54@13
@54@8:
	fld	dword ptr DGROUP:_p_rz
	fcomp	dword ptr DGROUP:_stick_uneg
	fstsw	word ptr [bp-40]
	fwait	
	mov	ax,word ptr [bp-40]
	sahf	
	jae	@54@13
	fld	dword ptr DGROUP:_p_rz
	fsub	dword ptr [bp-28]
	fstp	dword ptr [bp-16]
	fld	dword ptr DGROUP:_mindiff
	fchs	
	fcomp	dword ptr [bp-16]
	fstsw	word ptr [bp-40]
	fwait	
	mov	ax,word ptr [bp-40]
	sahf	
	ja	short @54@11
	fld	dword ptr [bp-16]
	fcomp	dword ptr DGROUP:_mindiff
	fstsw	word ptr [bp-40]
	fwait	
	mov	ax,word ptr [bp-40]
	sahf	
	jbe	short @54@12
@54@11:
	fld	dword ptr DGROUP:_stick_uneg
	fsub	dword ptr [bp-28]
	fdiv	dword ptr [bp-16]
	fstp	dword ptr [bp-36]
	fld	dword ptr DGROUP:_p_rx
	fsub	dword ptr [bp-20]
	fmul	dword ptr [bp-36]
	fadd	dword ptr [bp-20]
	fstp	dword ptr DGROUP:_p_rx
	fld	dword ptr DGROUP:_p_ry
	fsub	dword ptr [bp-24]
	fmul	dword ptr [bp-36]
	fadd	dword ptr [bp-24]
	fstp	dword ptr DGROUP:_p_ry
	fwait	
@54@12:
	mov	eax,dword ptr DGROUP:_stick_uneg
	mov	dword ptr DGROUP:_p_rz,eax
@54@13:
	fld	dword ptr [bp-20]
	fdiv	dword ptr [bp-28]
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	dword ptr [bp-4],eax
	fld	dword ptr [bp-24]
	fdiv	dword ptr [bp-28]
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	dword ptr [bp-8],eax
	fld	dword ptr DGROUP:_p_rx
	fdiv	dword ptr DGROUP:_p_rz
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	dword ptr DGROUP:_fpx,eax
	fld	dword ptr DGROUP:_p_ry
	fdiv	dword ptr DGROUP:_p_rz
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	dword ptr DGROUP:_fpy,eax
	cmp	dword ptr DGROUP:_fpy,large -90
	jge	short @54@15
	cmp	dword ptr [bp-8],large -90
	jl	@54@56
@54@15:
	cmp	dword ptr DGROUP:_fpy,large 90
	jle	short @54@17
	cmp	dword ptr [bp-8],large 90
	jg	@54@56
@54@17:
	cmp	dword ptr DGROUP:_fpx,large -150
	jge	short @54@19
	cmp	dword ptr [bp-4],large -150
	jl	@54@56
@54@19:
	cmp	dword ptr DGROUP:_fpx,large 160
	jle	short @54@21
	cmp	dword ptr [bp-4],large 160
	jg	@54@56
@54@21:
	cmp	dword ptr DGROUP:_fpx,large -150
	jge	@54@25
	mov	eax,dword ptr DGROUP:_fpx
	sub	eax,dword ptr [bp-4]
	mov	dword ptr [bp-40],eax
	fild	dword ptr [bp-40]
	fstp	dword ptr [bp-16]
	fld	dword ptr DGROUP:_mindiff
	fchs	
	fcomp	dword ptr [bp-16]
	fstsw	word ptr [bp-40]
	fwait	
	mov	ax,word ptr [bp-40]
	sahf	
	ja	short @54@24
	fld	dword ptr [bp-16]
	fcomp	dword ptr DGROUP:_mindiff
	fstsw	word ptr [bp-40]
	fwait	
	mov	ax,word ptr [bp-40]
	sahf	
	jbe	short @54@25
@54@24:
	mov	eax,large -150
	sub	eax,dword ptr [bp-4]
	mov	dword ptr [bp-40],eax
	fild	dword ptr [bp-40]
	fdiv	dword ptr [bp-16]
	fstp	dword ptr [bp-36]
	fwait	
	mov	eax,dword ptr DGROUP:_fpy
	sub	eax,dword ptr [bp-8]
	mov	dword ptr [bp-40],eax
	fild	dword ptr [bp-40]
	fmul	dword ptr [bp-36]
	mov	eax,dword ptr [bp-8]
	mov	dword ptr [bp-40],eax
	fild	dword ptr [bp-40]
	fadd	
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	dword ptr DGROUP:_fpy,eax
	mov	dword ptr DGROUP:_fpx,large -150
@54@25:
	cmp	dword ptr [bp-4],large -150
	jge	@54@29
	mov	eax,dword ptr [bp-4]
	sub	eax,dword ptr DGROUP:_fpx
	mov	dword ptr [bp-40],eax
	fild	dword ptr [bp-40]
	fstp	dword ptr [bp-16]
	fld	dword ptr DGROUP:_mindiff
	fchs	
	fcomp	dword ptr [bp-16]
	fstsw	word ptr [bp-40]
	fwait	
	mov	ax,word ptr [bp-40]
	sahf	
	ja	short @54@28
	fld	dword ptr [bp-16]
	fcomp	dword ptr DGROUP:_mindiff
	fstsw	word ptr [bp-40]
	fwait	
	mov	ax,word ptr [bp-40]
	sahf	
	jbe	short @54@29
@54@28:
	mov	eax,large -150
	sub	eax,dword ptr DGROUP:_fpx
	mov	dword ptr [bp-40],eax
	fild	dword ptr [bp-40]
	fdiv	dword ptr [bp-16]
	fstp	dword ptr [bp-36]
	fwait	
	mov	eax,dword ptr [bp-8]
	sub	eax,dword ptr DGROUP:_fpy
	mov	dword ptr [bp-40],eax
	fild	dword ptr [bp-40]
	fmul	dword ptr [bp-36]
	mov	eax,dword ptr DGROUP:_fpy
	mov	dword ptr [bp-40],eax
	fild	dword ptr [bp-40]
	fadd	
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	dword ptr [bp-8],eax
	mov	dword ptr [bp-4],large -150
@54@29:
	cmp	dword ptr DGROUP:_fpy,large -90
	jge	@54@33
	mov	eax,dword ptr DGROUP:_fpy
	sub	eax,dword ptr [bp-8]
	mov	dword ptr [bp-40],eax
	fild	dword ptr [bp-40]
	fstp	dword ptr [bp-16]
	fld	dword ptr DGROUP:_mindiff
	fchs	
	fcomp	dword ptr [bp-16]
	fstsw	word ptr [bp-40]
	fwait	
	mov	ax,word ptr [bp-40]
	sahf	
	ja	short @54@32
	fld	dword ptr [bp-16]
	fcomp	dword ptr DGROUP:_mindiff
	fstsw	word ptr [bp-40]
	fwait	
	mov	ax,word ptr [bp-40]
	sahf	
	jbe	short @54@33
@54@32:
	mov	eax,large -90
	sub	eax,dword ptr [bp-8]
	mov	dword ptr [bp-40],eax
	fild	dword ptr [bp-40]
	fdiv	dword ptr [bp-16]
	fstp	dword ptr [bp-36]
	fwait	
	mov	eax,dword ptr DGROUP:_fpx
	sub	eax,dword ptr [bp-4]
	mov	dword ptr [bp-40],eax
	fild	dword ptr [bp-40]
	fmul	dword ptr [bp-36]
	mov	eax,dword ptr [bp-4]
	mov	dword ptr [bp-40],eax
	fild	dword ptr [bp-40]
	fadd	
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	dword ptr DGROUP:_fpx,eax
	mov	dword ptr DGROUP:_fpy,large -90
@54@33:
	cmp	dword ptr [bp-8],large -90
	jge	@54@37
	mov	eax,dword ptr [bp-8]
	sub	eax,dword ptr DGROUP:_fpy
	mov	dword ptr [bp-40],eax
	fild	dword ptr [bp-40]
	fstp	dword ptr [bp-16]
	fld	dword ptr DGROUP:_mindiff
	fchs	
	fcomp	dword ptr [bp-16]
	fstsw	word ptr [bp-40]
	fwait	
	mov	ax,word ptr [bp-40]
	sahf	
	ja	short @54@36
	fld	dword ptr [bp-16]
	fcomp	dword ptr DGROUP:_mindiff
	fstsw	word ptr [bp-40]
	fwait	
	mov	ax,word ptr [bp-40]
	sahf	
	jbe	short @54@37
@54@36:
	mov	eax,large -90
	sub	eax,dword ptr DGROUP:_fpy
	mov	dword ptr [bp-40],eax
	fild	dword ptr [bp-40]
	fdiv	dword ptr [bp-16]
	fstp	dword ptr [bp-36]
	fwait	
	mov	eax,dword ptr [bp-4]
	sub	eax,dword ptr DGROUP:_fpx
	mov	dword ptr [bp-40],eax
	fild	dword ptr [bp-40]
	fmul	dword ptr [bp-36]
	mov	eax,dword ptr DGROUP:_fpx
	mov	dword ptr [bp-40],eax
	fild	dword ptr [bp-40]
	fadd	
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	dword ptr [bp-4],eax
	mov	dword ptr [bp-8],large -90
@54@37:
	cmp	dword ptr DGROUP:_fpx,large 160
	jle	@54@41
	mov	eax,dword ptr DGROUP:_fpx
	sub	eax,dword ptr [bp-4]
	mov	dword ptr [bp-40],eax
	fild	dword ptr [bp-40]
	fstp	dword ptr [bp-16]
	fld	dword ptr DGROUP:_mindiff
	fchs	
	fcomp	dword ptr [bp-16]
	fstsw	word ptr [bp-40]
	fwait	
	mov	ax,word ptr [bp-40]
	sahf	
	ja	short @54@40
	fld	dword ptr [bp-16]
	fcomp	dword ptr DGROUP:_mindiff
	fstsw	word ptr [bp-40]
	fwait	
	mov	ax,word ptr [bp-40]
	sahf	
	jbe	short @54@41
@54@40:
	mov	eax,large 160
	sub	eax,dword ptr [bp-4]
	mov	dword ptr [bp-40],eax
	fild	dword ptr [bp-40]
	fdiv	dword ptr [bp-16]
	fstp	dword ptr [bp-36]
	fwait	
	mov	eax,dword ptr DGROUP:_fpy
	sub	eax,dword ptr [bp-8]
	mov	dword ptr [bp-40],eax
	fild	dword ptr [bp-40]
	fmul	dword ptr [bp-36]
	mov	eax,dword ptr [bp-8]
	mov	dword ptr [bp-40],eax
	fild	dword ptr [bp-40]
	fadd	
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	dword ptr DGROUP:_fpy,eax
	mov	dword ptr DGROUP:_fpx,large 160
@54@41:
	cmp	dword ptr [bp-4],large 160
	jle	@54@45
	mov	eax,dword ptr [bp-4]
	sub	eax,dword ptr DGROUP:_fpx
	mov	dword ptr [bp-40],eax
	fild	dword ptr [bp-40]
	fstp	dword ptr [bp-16]
	fld	dword ptr DGROUP:_mindiff
	fchs	
	fcomp	dword ptr [bp-16]
	fstsw	word ptr [bp-40]
	fwait	
	mov	ax,word ptr [bp-40]
	sahf	
	ja	short @54@44
	fld	dword ptr [bp-16]
	fcomp	dword ptr DGROUP:_mindiff
	fstsw	word ptr [bp-40]
	fwait	
	mov	ax,word ptr [bp-40]
	sahf	
	jbe	short @54@45
@54@44:
	mov	eax,large 160
	sub	eax,dword ptr DGROUP:_fpx
	mov	dword ptr [bp-40],eax
	fild	dword ptr [bp-40]
	fdiv	dword ptr [bp-16]
	fstp	dword ptr [bp-36]
	fwait	
	mov	eax,dword ptr [bp-8]
	sub	eax,dword ptr DGROUP:_fpy
	mov	dword ptr [bp-40],eax
	fild	dword ptr [bp-40]
	fmul	dword ptr [bp-36]
	mov	eax,dword ptr DGROUP:_fpy
	mov	dword ptr [bp-40],eax
	fild	dword ptr [bp-40]
	fadd	
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	dword ptr [bp-8],eax
	mov	dword ptr [bp-4],large 160
@54@45:
	cmp	dword ptr DGROUP:_fpy,large 90
	jle	@54@49
	mov	eax,dword ptr DGROUP:_fpy
	sub	eax,dword ptr [bp-8]
	mov	dword ptr [bp-40],eax
	fild	dword ptr [bp-40]
	fstp	dword ptr [bp-16]
	fld	dword ptr DGROUP:_mindiff
	fchs	
	fcomp	dword ptr [bp-16]
	fstsw	word ptr [bp-40]
	fwait	
	mov	ax,word ptr [bp-40]
	sahf	
	ja	short @54@48
	fld	dword ptr [bp-16]
	fcomp	dword ptr DGROUP:_mindiff
	fstsw	word ptr [bp-40]
	fwait	
	mov	ax,word ptr [bp-40]
	sahf	
	jbe	short @54@49
@54@48:
	mov	eax,large 90
	sub	eax,dword ptr [bp-8]
	mov	dword ptr [bp-40],eax
	fild	dword ptr [bp-40]
	fdiv	dword ptr [bp-16]
	fstp	dword ptr [bp-36]
	fwait	
	mov	eax,dword ptr DGROUP:_fpx
	sub	eax,dword ptr [bp-4]
	mov	dword ptr [bp-40],eax
	fild	dword ptr [bp-40]
	fmul	dword ptr [bp-36]
	mov	eax,dword ptr [bp-4]
	mov	dword ptr [bp-40],eax
	fild	dword ptr [bp-40]
	fadd	
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	dword ptr DGROUP:_fpx,eax
	mov	dword ptr DGROUP:_fpy,large 90
@54@49:
	cmp	dword ptr [bp-8],large 90
	jle	@54@53
	mov	eax,dword ptr [bp-8]
	sub	eax,dword ptr DGROUP:_fpy
	mov	dword ptr [bp-40],eax
	fild	dword ptr [bp-40]
	fstp	dword ptr [bp-16]
	fld	dword ptr DGROUP:_mindiff
	fchs	
	fcomp	dword ptr [bp-16]
	fstsw	word ptr [bp-40]
	fwait	
	mov	ax,word ptr [bp-40]
	sahf	
	ja	short @54@52
	fld	dword ptr [bp-16]
	fcomp	dword ptr DGROUP:_mindiff
	fstsw	word ptr [bp-40]
	fwait	
	mov	ax,word ptr [bp-40]
	sahf	
	jbe	short @54@53
@54@52:
	mov	eax,large 90
	sub	eax,dword ptr DGROUP:_fpy
	mov	dword ptr [bp-40],eax
	fild	dword ptr [bp-40]
	fdiv	dword ptr [bp-16]
	fstp	dword ptr [bp-36]
	fwait	
	mov	eax,dword ptr [bp-4]
	sub	eax,dword ptr DGROUP:_fpx
	mov	dword ptr [bp-40],eax
	fild	dword ptr [bp-40]
	fmul	dword ptr [bp-36]
	mov	eax,dword ptr DGROUP:_fpx
	mov	dword ptr [bp-40],eax
	fild	dword ptr [bp-40]
	fadd	
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	dword ptr [bp-4],eax
	mov	dword ptr [bp-8],large 90
@54@53:
	mov	eax,dword ptr DGROUP:_fpx
	cmp	eax,dword ptr [bp-4]
	jne	short @54@55
	mov	eax,dword ptr DGROUP:_fpy
	cmp	eax,dword ptr [bp-8]
	je	short @54@56
@54@55:
	mov	eax,dword ptr [bp-8]
	add	eax,large 100
	push	eax
	mov	eax,dword ptr [bp-4]
	add	eax,large 158
	push	eax
	mov	eax,dword ptr DGROUP:_fpy
	add	eax,large 100
	push	eax
	mov	eax,dword ptr DGROUP:_fpx
	add	eax,large 158
	push	eax
	push	cs
	call	near ptr @stick$qulululul
	add	sp,16
@54@56:
	leave	
	ret	
@stick3d$qffffff	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@link3d$qfff	proc	far
	push	bp
	mov	bp,sp
	sub	sp,26
	cmp	dword ptr DGROUP:_fpx,large -1
	je	@55@14
	cmp	dword ptr DGROUP:_fpy,large -90
	jle	@55@14
	cmp	dword ptr DGROUP:_fpy,large 90
	jge	@55@14
	cmp	dword ptr DGROUP:_fpx,large -150
	jle	@55@14
	cmp	dword ptr DGROUP:_fpx,large 160
	jge	@55@14
	fld	dword ptr DGROUP:_cam_x
	fsubr	dword ptr [bp+6]
	fstp	dword ptr [bp+6]
	fld	dword ptr DGROUP:_cam_z
	fsubr	dword ptr [bp+14]
	fstp	dword ptr [bp+14]
	fld	dword ptr DGROUP:_cam_y
	fsubr	dword ptr [bp+10]
	fstp	dword ptr [bp+10]
	fld	dword ptr [bp+14]
	fmul	dword ptr DGROUP:_opt_tcosbeta
	fld	dword ptr [bp+6]
	fmul	dword ptr DGROUP:_opt_tsinbeta
	fsub	
	fstp	dword ptr [bp-24]
	fld	dword ptr [bp+10]
	fmul	dword ptr DGROUP:_opt_tsinalfa
	fld	dword ptr [bp-24]
	fmul	dword ptr DGROUP:_opt_tcosalfa
	fadd	
	fstp	dword ptr [bp-20]
	fld	dword ptr [bp-20]
	fcomp	dword ptr DGROUP:_stick_uneg
	fstsw	word ptr [bp-26]
	fwait	
	mov	ax,word ptr [bp-26]
	sahf	
	jb	@55@14
	fld	dword ptr [bp+6]
	fmul	dword ptr DGROUP:_opt_pcosbeta
	fld	dword ptr [bp+14]
	fmul	dword ptr DGROUP:_opt_psinbeta
	fadd	
	fstp	dword ptr [bp-12]
	fld	dword ptr [bp+10]
	fmul	dword ptr DGROUP:_opt_pcosalfa
	fld	dword ptr [bp-24]
	fmul	dword ptr DGROUP:_opt_psinalfa
	fsub	
	fstp	dword ptr [bp-16]
	fld	dword ptr [bp-12]
	fdiv	dword ptr [bp-20]
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	dword ptr [bp-4],eax
	fld	dword ptr [bp-16]
	fdiv	dword ptr [bp-20]
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	dword ptr [bp-8],eax
	cmp	dword ptr [bp-8],large -90
	jle	short @55@14
	cmp	dword ptr [bp-8],large 90
	jge	short @55@14
	cmp	dword ptr [bp-4],large -150
	jle	short @55@14
	cmp	dword ptr [bp-4],large 160
	jge	short @55@14
	mov	eax,dword ptr DGROUP:_fpx
	cmp	eax,dword ptr [bp-4]
	jne	short @55@13
	mov	eax,dword ptr DGROUP:_fpy
	cmp	eax,dword ptr [bp-8]
	je	short @55@14
@55@13:
	mov	eax,dword ptr [bp-8]
	add	eax,large 100
	push	eax
	mov	eax,dword ptr [bp-4]
	add	eax,large 158
	push	eax
	mov	eax,dword ptr DGROUP:_fpy
	add	eax,large 100
	push	eax
	mov	eax,dword ptr DGROUP:_fpx
	add	eax,large 158
	push	eax
	push	cs
	call	near ptr @stick$qulululul
	add	sp,16
@55@14:
	leave	
	ret	
@link3d$qfff	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@fline$qllll	proc	far
	push	bp
	mov	bp,sp
	sub	sp,12
	cmp	dword ptr [bp+6],large -150
	jge	@56@5
	mov	eax,dword ptr [bp+6]
	sub	eax,dword ptr [bp+14]
	mov	dword ptr [bp-12],eax
	fild	dword ptr [bp-12]
	fstp	dword ptr [bp-8]
	fld	dword ptr DGROUP:_mindiff
	fchs	
	fcomp	dword ptr [bp-8]
	fstsw	word ptr [bp-12]
	fwait	
	mov	ax,word ptr [bp-12]
	sahf	
	ja	short @56@4
	fld	dword ptr [bp-8]
	fcomp	dword ptr DGROUP:_mindiff
	fstsw	word ptr [bp-12]
	fwait	
	mov	ax,word ptr [bp-12]
	sahf	
	jbe	short @56@5
@56@4:
	mov	eax,large -150
	sub	eax,dword ptr [bp+14]
	mov	dword ptr [bp-12],eax
	fild	dword ptr [bp-12]
	fdiv	dword ptr [bp-8]
	fstp	dword ptr [bp-4]
	fwait	
	mov	eax,dword ptr [bp+10]
	sub	eax,dword ptr [bp+18]
	mov	dword ptr [bp-12],eax
	fild	dword ptr [bp-12]
	fmul	dword ptr [bp-4]
	mov	eax,dword ptr [bp+18]
	mov	dword ptr [bp-12],eax
	fild	dword ptr [bp-12]
	fadd	
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	dword ptr [bp+10],eax
	mov	dword ptr [bp+6],large -150
@56@5:
	cmp	dword ptr [bp+14],large -150
	jge	@56@9
	mov	eax,dword ptr [bp+14]
	sub	eax,dword ptr [bp+6]
	mov	dword ptr [bp-12],eax
	fild	dword ptr [bp-12]
	fstp	dword ptr [bp-8]
	fld	dword ptr DGROUP:_mindiff
	fchs	
	fcomp	dword ptr [bp-8]
	fstsw	word ptr [bp-12]
	fwait	
	mov	ax,word ptr [bp-12]
	sahf	
	ja	short @56@8
	fld	dword ptr [bp-8]
	fcomp	dword ptr DGROUP:_mindiff
	fstsw	word ptr [bp-12]
	fwait	
	mov	ax,word ptr [bp-12]
	sahf	
	jbe	short @56@9
@56@8:
	mov	eax,large -150
	sub	eax,dword ptr [bp+6]
	mov	dword ptr [bp-12],eax
	fild	dword ptr [bp-12]
	fdiv	dword ptr [bp-8]
	fstp	dword ptr [bp-4]
	fwait	
	mov	eax,dword ptr [bp+18]
	sub	eax,dword ptr [bp+10]
	mov	dword ptr [bp-12],eax
	fild	dword ptr [bp-12]
	fmul	dword ptr [bp-4]
	mov	eax,dword ptr [bp+10]
	mov	dword ptr [bp-12],eax
	fild	dword ptr [bp-12]
	fadd	
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	dword ptr [bp+18],eax
	mov	dword ptr [bp+14],large -150
@56@9:
	cmp	dword ptr [bp+10],large -90
	jge	@56@13
	mov	eax,dword ptr [bp+10]
	sub	eax,dword ptr [bp+18]
	mov	dword ptr [bp-12],eax
	fild	dword ptr [bp-12]
	fstp	dword ptr [bp-8]
	fld	dword ptr DGROUP:_mindiff
	fchs	
	fcomp	dword ptr [bp-8]
	fstsw	word ptr [bp-12]
	fwait	
	mov	ax,word ptr [bp-12]
	sahf	
	ja	short @56@12
	fld	dword ptr [bp-8]
	fcomp	dword ptr DGROUP:_mindiff
	fstsw	word ptr [bp-12]
	fwait	
	mov	ax,word ptr [bp-12]
	sahf	
	jbe	short @56@13
@56@12:
	mov	eax,large -90
	sub	eax,dword ptr [bp+18]
	mov	dword ptr [bp-12],eax
	fild	dword ptr [bp-12]
	fdiv	dword ptr [bp-8]
	fstp	dword ptr [bp-4]
	fwait	
	mov	eax,dword ptr [bp+6]
	sub	eax,dword ptr [bp+14]
	mov	dword ptr [bp-12],eax
	fild	dword ptr [bp-12]
	fmul	dword ptr [bp-4]
	mov	eax,dword ptr [bp+14]
	mov	dword ptr [bp-12],eax
	fild	dword ptr [bp-12]
	fadd	
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	dword ptr [bp+6],eax
	mov	dword ptr [bp+10],large -90
@56@13:
	cmp	dword ptr [bp+18],large -90
	jge	@56@17
	mov	eax,dword ptr [bp+18]
	sub	eax,dword ptr [bp+10]
	mov	dword ptr [bp-12],eax
	fild	dword ptr [bp-12]
	fstp	dword ptr [bp-8]
	fld	dword ptr DGROUP:_mindiff
	fchs	
	fcomp	dword ptr [bp-8]
	fstsw	word ptr [bp-12]
	fwait	
	mov	ax,word ptr [bp-12]
	sahf	
	ja	short @56@16
	fld	dword ptr [bp-8]
	fcomp	dword ptr DGROUP:_mindiff
	fstsw	word ptr [bp-12]
	fwait	
	mov	ax,word ptr [bp-12]
	sahf	
	jbe	short @56@17
@56@16:
	mov	eax,large -90
	sub	eax,dword ptr [bp+10]
	mov	dword ptr [bp-12],eax
	fild	dword ptr [bp-12]
	fdiv	dword ptr [bp-8]
	fstp	dword ptr [bp-4]
	fwait	
	mov	eax,dword ptr [bp+14]
	sub	eax,dword ptr [bp+6]
	mov	dword ptr [bp-12],eax
	fild	dword ptr [bp-12]
	fmul	dword ptr [bp-4]
	mov	eax,dword ptr [bp+6]
	mov	dword ptr [bp-12],eax
	fild	dword ptr [bp-12]
	fadd	
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	dword ptr [bp+14],eax
	mov	dword ptr [bp+18],large -90
@56@17:
	cmp	dword ptr [bp+6],large 160
	jle	@56@21
	mov	eax,dword ptr [bp+6]
	sub	eax,dword ptr [bp+14]
	mov	dword ptr [bp-12],eax
	fild	dword ptr [bp-12]
	fstp	dword ptr [bp-8]
	fld	dword ptr DGROUP:_mindiff
	fchs	
	fcomp	dword ptr [bp-8]
	fstsw	word ptr [bp-12]
	fwait	
	mov	ax,word ptr [bp-12]
	sahf	
	ja	short @56@20
	fld	dword ptr [bp-8]
	fcomp	dword ptr DGROUP:_mindiff
	fstsw	word ptr [bp-12]
	fwait	
	mov	ax,word ptr [bp-12]
	sahf	
	jbe	short @56@21
@56@20:
	mov	eax,large 160
	sub	eax,dword ptr [bp+14]
	mov	dword ptr [bp-12],eax
	fild	dword ptr [bp-12]
	fdiv	dword ptr [bp-8]
	fstp	dword ptr [bp-4]
	fwait	
	mov	eax,dword ptr [bp+10]
	sub	eax,dword ptr [bp+18]
	mov	dword ptr [bp-12],eax
	fild	dword ptr [bp-12]
	fmul	dword ptr [bp-4]
	mov	eax,dword ptr [bp+18]
	mov	dword ptr [bp-12],eax
	fild	dword ptr [bp-12]
	fadd	
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	dword ptr [bp+10],eax
	mov	dword ptr [bp+6],large 160
@56@21:
	cmp	dword ptr [bp+14],large 160
	jle	@56@25
	mov	eax,dword ptr [bp+14]
	sub	eax,dword ptr [bp+6]
	mov	dword ptr [bp-12],eax
	fild	dword ptr [bp-12]
	fstp	dword ptr [bp-8]
	fld	dword ptr DGROUP:_mindiff
	fchs	
	fcomp	dword ptr [bp-8]
	fstsw	word ptr [bp-12]
	fwait	
	mov	ax,word ptr [bp-12]
	sahf	
	ja	short @56@24
	fld	dword ptr [bp-8]
	fcomp	dword ptr DGROUP:_mindiff
	fstsw	word ptr [bp-12]
	fwait	
	mov	ax,word ptr [bp-12]
	sahf	
	jbe	short @56@25
@56@24:
	mov	eax,large 160
	sub	eax,dword ptr [bp+6]
	mov	dword ptr [bp-12],eax
	fild	dword ptr [bp-12]
	fdiv	dword ptr [bp-8]
	fstp	dword ptr [bp-4]
	fwait	
	mov	eax,dword ptr [bp+18]
	sub	eax,dword ptr [bp+10]
	mov	dword ptr [bp-12],eax
	fild	dword ptr [bp-12]
	fmul	dword ptr [bp-4]
	mov	eax,dword ptr [bp+10]
	mov	dword ptr [bp-12],eax
	fild	dword ptr [bp-12]
	fadd	
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	dword ptr [bp+18],eax
	mov	dword ptr [bp+14],large 160
@56@25:
	cmp	dword ptr [bp+10],large 90
	jle	@56@29
	mov	eax,dword ptr [bp+10]
	sub	eax,dword ptr [bp+18]
	mov	dword ptr [bp-12],eax
	fild	dword ptr [bp-12]
	fstp	dword ptr [bp-8]
	fld	dword ptr DGROUP:_mindiff
	fchs	
	fcomp	dword ptr [bp-8]
	fstsw	word ptr [bp-12]
	fwait	
	mov	ax,word ptr [bp-12]
	sahf	
	ja	short @56@28
	fld	dword ptr [bp-8]
	fcomp	dword ptr DGROUP:_mindiff
	fstsw	word ptr [bp-12]
	fwait	
	mov	ax,word ptr [bp-12]
	sahf	
	jbe	short @56@29
@56@28:
	mov	eax,large 90
	sub	eax,dword ptr [bp+18]
	mov	dword ptr [bp-12],eax
	fild	dword ptr [bp-12]
	fdiv	dword ptr [bp-8]
	fstp	dword ptr [bp-4]
	fwait	
	mov	eax,dword ptr [bp+6]
	sub	eax,dword ptr [bp+14]
	mov	dword ptr [bp-12],eax
	fild	dword ptr [bp-12]
	fmul	dword ptr [bp-4]
	mov	eax,dword ptr [bp+14]
	mov	dword ptr [bp-12],eax
	fild	dword ptr [bp-12]
	fadd	
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	dword ptr [bp+6],eax
	mov	dword ptr [bp+10],large 90
@56@29:
	cmp	dword ptr [bp+18],large 90
	jle	@56@33
	mov	eax,dword ptr [bp+18]
	sub	eax,dword ptr [bp+10]
	mov	dword ptr [bp-12],eax
	fild	dword ptr [bp-12]
	fstp	dword ptr [bp-8]
	fld	dword ptr DGROUP:_mindiff
	fchs	
	fcomp	dword ptr [bp-8]
	fstsw	word ptr [bp-12]
	fwait	
	mov	ax,word ptr [bp-12]
	sahf	
	ja	short @56@32
	fld	dword ptr [bp-8]
	fcomp	dword ptr DGROUP:_mindiff
	fstsw	word ptr [bp-12]
	fwait	
	mov	ax,word ptr [bp-12]
	sahf	
	jbe	short @56@33
@56@32:
	mov	eax,large 90
	sub	eax,dword ptr [bp+10]
	mov	dword ptr [bp-12],eax
	fild	dword ptr [bp-12]
	fdiv	dword ptr [bp-8]
	fstp	dword ptr [bp-4]
	fwait	
	mov	eax,dword ptr [bp+14]
	sub	eax,dword ptr [bp+6]
	mov	dword ptr [bp-12],eax
	fild	dword ptr [bp-12]
	fmul	dword ptr [bp-4]
	mov	eax,dword ptr [bp+6]
	mov	dword ptr [bp-12],eax
	fild	dword ptr [bp-12]
	fadd	
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	dword ptr [bp+14],eax
	mov	dword ptr [bp+18],large 90
@56@33:
	mov	eax,dword ptr [bp+6]
	cmp	eax,dword ptr [bp+14]
	jne	short @56@35
	mov	eax,dword ptr [bp+10]
	cmp	eax,dword ptr [bp+18]
	je	short @56@44
@56@35:
	cmp	dword ptr [bp+10],large -90
	jl	short @56@44
	cmp	dword ptr [bp+18],large -90
	jl	short @56@44
	cmp	dword ptr [bp+10],large 90
	jg	short @56@44
	cmp	dword ptr [bp+18],large 90
	jg	short @56@44
	cmp	dword ptr [bp+6],large -150
	jl	short @56@44
	cmp	dword ptr [bp+14],large -150
	jl	short @56@44
	cmp	dword ptr [bp+6],large 160
	jg	short @56@44
	cmp	dword ptr [bp+14],large 160
	jg	short @56@44
	mov	eax,dword ptr [bp+18]
	add	eax,large 100
	push	eax
	mov	eax,dword ptr [bp+14]
	add	eax,large 158
	push	eax
	mov	eax,dword ptr [bp+10]
	add	eax,large 100
	push	eax
	mov	eax,dword ptr [bp+6]
	add	eax,large 158
	push	eax
	push	cs
	call	near ptr @stick$qulululul
	add	sp,16
@56@44:
	leave	
	ret	
@fline$qllll	endp
NOCTIS-0_TEXT	ends
_DATA	segment word public use16 'DATA'
_map_color_a	label	byte
	db	30
_map_color_b	label	byte
	db	31
_map_color_c	label	byte
	db	32
_map_color_d	label	byte
	db	33
_DATA	ends
NOCTIS-0_TEXT	segment byte public use16 'CODE'
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@randomic_mapper$qfffffffffc	proc	far
	push	bp
	mov	bp,sp
	sub	sp,72
	dec	byte ptr [bp+42]
	cmp	byte ptr [bp+42],0
	je	@57@6
	fld	dword ptr [bp+6]
	fadd	dword ptr [bp+18]
	fmul	dword ptr DGROUP:s@+1582
	fstp	dword ptr [bp-4]
	fld	dword ptr [bp+10]
	fadd	dword ptr [bp+22]
	fmul	dword ptr DGROUP:s@+1582
	fstp	dword ptr [bp-8]
	fld	dword ptr [bp+14]
	fadd	dword ptr [bp+26]
	fmul	dword ptr DGROUP:s@+1582
	fstp	dword ptr [bp-12]
	fld	dword ptr [bp+18]
	fadd	dword ptr [bp+30]
	fmul	dword ptr DGROUP:s@+1582
	fstp	dword ptr [bp-16]
	fld	dword ptr [bp+22]
	fadd	dword ptr [bp+34]
	fmul	dword ptr DGROUP:s@+1582
	fstp	dword ptr [bp-20]
	fld	dword ptr [bp+26]
	fadd	dword ptr [bp+38]
	fmul	dword ptr DGROUP:s@+1582
	fstp	dword ptr [bp-24]
	fld	dword ptr [bp+6]
	fadd	dword ptr [bp+30]
	fmul	dword ptr DGROUP:s@+1582
	fstp	dword ptr [bp-28]
	fld	dword ptr [bp+10]
	fadd	dword ptr [bp+34]
	fmul	dword ptr DGROUP:s@+1582
	fstp	dword ptr [bp-32]
	fld	dword ptr [bp+14]
	fadd	dword ptr [bp+38]
	fmul	dword ptr DGROUP:s@+1582
	fstp	dword ptr [bp-36]
	fwait	
	mov	al,byte ptr [bp+42]
	cbw	
	cmp	ax,1
	jne	@57@4
	mov	eax,dword ptr [bp+6]
	mov	dword ptr [bp-48],eax
	mov	eax,dword ptr [bp+10]
	mov	dword ptr [bp-60],eax
	mov	eax,dword ptr [bp+14]
	mov	dword ptr [bp-72],eax
	mov	eax,dword ptr [bp-4]
	mov	dword ptr [bp-44],eax
	mov	eax,dword ptr [bp-8]
	mov	dword ptr [bp-56],eax
	mov	eax,dword ptr [bp-12]
	mov	dword ptr [bp-68],eax
	mov	eax,dword ptr [bp-28]
	mov	dword ptr [bp-40],eax
	mov	eax,dword ptr [bp-32]
	mov	dword ptr [bp-52],eax
	mov	eax,dword ptr [bp-36]
	mov	dword ptr [bp-64],eax
	mov	al,byte ptr DGROUP:_map_color_a
	push	ax
	push	3
	push	ss
	lea	ax,word ptr [bp-72]
	push	ax
	push	ss
	lea	ax,word ptr [bp-60]
	push	ax
	push	ss
	lea	ax,word ptr [bp-48]
	push	ax
	push	cs
	call	near ptr @poly3d$qnft1t1uiuc
	add	sp,16
	mov	al,byte ptr [bp+42]
	push	ax
	push	dword ptr [bp-36]
	push	dword ptr [bp-32]
	push	dword ptr [bp-28]
	push	dword ptr [bp-12]
	push	dword ptr [bp-8]
	push	dword ptr [bp-4]
	push	dword ptr [bp+14]
	push	dword ptr [bp+10]
	push	dword ptr [bp+6]
	push	cs
	call	near ptr @randomic_mapper$qfffffffffc
	add	sp,38
	mov	eax,dword ptr [bp-16]
	mov	dword ptr [bp-48],eax
	mov	eax,dword ptr [bp-20]
	mov	dword ptr [bp-60],eax
	mov	eax,dword ptr [bp-24]
	mov	dword ptr [bp-72],eax
	mov	al,byte ptr DGROUP:_map_color_b
	push	ax
	push	3
	push	ss
	lea	ax,word ptr [bp-72]
	push	ax
	push	ss
	lea	ax,word ptr [bp-60]
	push	ax
	push	ss
	lea	ax,word ptr [bp-48]
	push	ax
	push	cs
	call	near ptr @poly3d$qnft1t1uiuc
	add	sp,16
	mov	al,byte ptr [bp+42]
	push	ax
	push	dword ptr [bp-36]
	push	dword ptr [bp-32]
	push	dword ptr [bp-28]
	push	dword ptr [bp-12]
	push	dword ptr [bp-8]
	push	dword ptr [bp-4]
	push	dword ptr [bp-24]
	push	dword ptr [bp-20]
	push	dword ptr [bp-16]
	push	cs
	call	near ptr @randomic_mapper$qfffffffffc
	add	sp,38
	mov	eax,dword ptr [bp+30]
	mov	dword ptr [bp-44],eax
	mov	eax,dword ptr [bp+34]
	mov	dword ptr [bp-56],eax
	mov	eax,dword ptr [bp+38]
	mov	dword ptr [bp-68],eax
	mov	al,byte ptr DGROUP:_map_color_c
	push	ax
	push	3
	push	ss
	lea	ax,word ptr [bp-72]
	push	ax
	push	ss
	lea	ax,word ptr [bp-60]
	push	ax
	push	ss
	lea	ax,word ptr [bp-48]
	push	ax
	push	cs
	call	near ptr @poly3d$qnft1t1uiuc
	add	sp,16
	mov	al,byte ptr [bp+42]
	push	ax
	push	dword ptr [bp-36]
	push	dword ptr [bp-32]
	push	dword ptr [bp-28]
	push	dword ptr [bp+38]
	push	dword ptr [bp+34]
	push	dword ptr [bp+30]
	push	dword ptr [bp-24]
	push	dword ptr [bp-20]
	push	dword ptr [bp-16]
	push	cs
	call	near ptr @randomic_mapper$qfffffffffc
	add	sp,38
	mov	eax,dword ptr [bp+18]
	mov	dword ptr [bp-40],eax
	mov	eax,dword ptr [bp+22]
	mov	dword ptr [bp-52],eax
	mov	eax,dword ptr [bp+26]
	mov	dword ptr [bp-64],eax
	mov	eax,dword ptr [bp-4]
	mov	dword ptr [bp-44],eax
	mov	eax,dword ptr [bp-8]
	mov	dword ptr [bp-56],eax
	mov	eax,dword ptr [bp-12]
	mov	dword ptr [bp-68],eax
	mov	al,byte ptr DGROUP:_map_color_d
	push	ax
	push	3
	push	ss
	lea	ax,word ptr [bp-72]
	push	ax
	push	ss
	lea	ax,word ptr [bp-60]
	push	ax
	push	ss
	lea	ax,word ptr [bp-48]
	push	ax
	push	cs
	call	near ptr @poly3d$qnft1t1uiuc
	add	sp,16
	jmp	@57@5
@57@4:
	mov	al,byte ptr [bp+42]
	push	ax
	push	dword ptr [bp-36]
	push	dword ptr [bp-32]
	push	dword ptr [bp-28]
	push	dword ptr [bp-12]
	push	dword ptr [bp-8]
	push	dword ptr [bp-4]
	push	dword ptr [bp+14]
	push	dword ptr [bp+10]
	push	dword ptr [bp+6]
	push	cs
	call	near ptr @randomic_mapper$qfffffffffc
	add	sp,38
	mov	al,byte ptr [bp+42]
	push	ax
	push	dword ptr [bp-36]
	push	dword ptr [bp-32]
	push	dword ptr [bp-28]
	push	dword ptr [bp-12]
	push	dword ptr [bp-8]
	push	dword ptr [bp-4]
	push	dword ptr [bp-24]
	push	dword ptr [bp-20]
	push	dword ptr [bp-16]
	push	cs
	call	near ptr @randomic_mapper$qfffffffffc
	add	sp,38
	mov	al,byte ptr [bp+42]
	push	ax
	push	dword ptr [bp-36]
	push	dword ptr [bp-32]
	push	dword ptr [bp-28]
	push	dword ptr [bp+38]
	push	dword ptr [bp+34]
	push	dword ptr [bp+30]
	push	dword ptr [bp-24]
	push	dword ptr [bp-20]
	push	dword ptr [bp-16]
	push	cs
	call	near ptr @randomic_mapper$qfffffffffc
	add	sp,38
@57@5:
	mov	al,byte ptr [bp+42]
	push	ax
	push	dword ptr [bp+26]
	push	dword ptr [bp+22]
	push	dword ptr [bp+18]
	push	dword ptr [bp-12]
	push	dword ptr [bp-8]
	push	dword ptr [bp-4]
	push	dword ptr [bp-24]
	push	dword ptr [bp-20]
	push	dword ptr [bp-16]
	push	cs
	call	near ptr @randomic_mapper$qfffffffffc
	add	sp,38
@57@6:
	leave	
	ret	
@randomic_mapper$qfffffffffc	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@unloadpv$qi	proc	far
	push	bp
	mov	bp,sp
	sub	sp,8
	push	si
	push	di
	mov	di,word ptr [bp+6]
	cmp	di,16
	jge	@58@16
	mov	bx,di
	add	bx,bx
	cmp	word ptr DGROUP:_pvfile_datalen[bx],0
	je	@58@16
	mov	word ptr [bp-2],0
	mov	word ptr [bp-6],offset DGROUP:_pvfile_dataptr
	mov	word ptr [bp-8],0
@58@5:
	mov	bx,word ptr [bp-6]
	mov	ax,word ptr [bx]
	mov	bx,di
	add	bx,bx
	cmp	ax,word ptr DGROUP:_pvfile_dataptr[bx]
	jbe	@58@9
	mov	bx,di
	add	bx,bx
	mov	ax,word ptr DGROUP:_pvfile_datalen[bx]
	mov	bx,word ptr [bp-8]
	sub	word ptr DGROUP:_pv_n_vtx[bx],ax
	mov	bx,di
	add	bx,bx
	mov	ax,word ptr DGROUP:_pvfile_datalen[bx]
	mov	bx,word ptr [bp-8]
	sub	word ptr DGROUP:_pvfile_x[bx],ax
	mov	bx,di
	add	bx,bx
	mov	ax,word ptr DGROUP:_pvfile_datalen[bx]
	mov	bx,word ptr [bp-8]
	sub	word ptr DGROUP:_pvfile_y[bx],ax
	mov	bx,di
	add	bx,bx
	mov	ax,word ptr DGROUP:_pvfile_datalen[bx]
	mov	bx,word ptr [bp-8]
	sub	word ptr DGROUP:_pvfile_z[bx],ax
	mov	bx,di
	add	bx,bx
	mov	ax,word ptr DGROUP:_pvfile_datalen[bx]
	mov	bx,word ptr [bp-8]
	sub	word ptr DGROUP:_pvfile_c[bx],ax
	mov	bx,word ptr [bp-8]
	mov	ax,word ptr DGROUP:_pv_mid_x[bx]
	or	ax,word ptr DGROUP:_pv_mid_x[bx+2]
	je	short @58@8
	mov	bx,di
	add	bx,bx
	mov	ax,word ptr DGROUP:_pvfile_datalen[bx]
	mov	bx,word ptr [bp-8]
	sub	word ptr DGROUP:_pv_mid_x[bx],ax
	mov	bx,di
	add	bx,bx
	mov	ax,word ptr DGROUP:_pvfile_datalen[bx]
	mov	bx,word ptr [bp-8]
	sub	word ptr DGROUP:_pv_mid_y[bx],ax
	mov	bx,di
	add	bx,bx
	mov	ax,word ptr DGROUP:_pvfile_datalen[bx]
	mov	bx,word ptr [bp-8]
	sub	word ptr DGROUP:_pv_mid_z[bx],ax
	mov	bx,di
	add	bx,bx
	mov	ax,word ptr DGROUP:_pvfile_datalen[bx]
	mov	bx,word ptr [bp-8]
	sub	word ptr DGROUP:_pv_mid_d[bx],ax
	mov	bx,di
	add	bx,bx
	mov	ax,word ptr DGROUP:_pvfile_datalen[bx]
	mov	bx,word ptr [bp-8]
	sub	word ptr DGROUP:_pv_dep_i[bx],ax
@58@8:
	mov	bx,di
	add	bx,bx
	mov	ax,word ptr DGROUP:_pvfile_datalen[bx]
	mov	bx,word ptr [bp-6]
	sub	word ptr [bx],ax
@58@9:
	add	word ptr [bp-6],2
	add	word ptr [bp-8],4
	inc	word ptr [bp-2]
	cmp	word ptr [bp-6],offset DGROUP:_pvfile_dataptr+32
	jne	@58@5
	mov	bx,di
	add	bx,bx
	mov	ax,word ptr DGROUP:_pvfile_dataptr[bx]
	mov	bx,di
	add	bx,bx
	add	ax,word ptr DGROUP:_pvfile_datalen[bx]
	mov	word ptr [bp-4],ax
	movzx	eax,word ptr [bp-4]
	cmp	eax,dword ptr DGROUP:_pvfile_datatop
	jae	short @58@15
	mov	ax,word ptr DGROUP:_pvfile_datatop
	sub	ax,word ptr [bp-4]
	push	ax
	mov	bx,di
	shl	bx,2
	mov	ax,word ptr DGROUP:_pv_n_vtx[bx]
	mov	si,di
	add	si,si
	add	ax,word ptr DGROUP:_pvfile_datalen[si]
	push	word ptr DGROUP:_pv_n_vtx[bx+2]
	push	ax
	mov	bx,di
	shl	bx,2
	push	dword ptr DGROUP:_pv_n_vtx[bx]
	call	far ptr __fmemmove
	add	sp,10
@58@15:
	mov	bx,di
	add	bx,bx
	movzx	eax,word ptr DGROUP:_pvfile_datalen[bx]
	sub	dword ptr DGROUP:_pvfile_datatop,eax
	mov	bx,di
	add	bx,bx
	mov	word ptr DGROUP:_pvfile_datalen[bx],0
@58@16:
	pop	di
	pop	si
	leave	
	ret	
@unloadpv$qi	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@unloadallpv$qv	proc	far
	push	bp
	mov	bp,sp
	sub	sp,2
	push	di
	mov	dword ptr DGROUP:_pvfile_datatop,large 0
	mov	cx,16
	mov	di,offset DGROUP:_pvfile_datalen
	push	ds
	pop	es
	xor	ax,ax
	rep 	stosw	
	mov	word ptr [bp-2],16
	pop	di
	leave	
	ret	
@unloadallpv$qv	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@loadpv$qilffffffucc	proc	far
	push	bp
	mov	bp,sp
	sub	sp,18
	push	si
	push	di
	mov	si,word ptr [bp+6]
	cmp	si,16
	jge	@60@19
	push	dword ptr [bp+8]
	push	cs
	call	near ptr @sa_open$ql
	add	sp,4
	mov	word ptr [bp-2],ax
	cmp	word ptr [bp-2],-1
	jne	short @60@4
	mov	al,255
	jmp	@60@44
@60@4:
	mov	bx,si
	add	bx,bx
	cmp	word ptr DGROUP:_pvfile_datalen[bx],0
	je	short @60@6
	push	si
	push	cs
	call	near ptr @unloadpv$qi
	add	sp,2
@60@6:
	mov	bx,si
	add	bx,bx
	mov	word ptr DGROUP:_pvfile_datalen[bx],0
	mov	bx,si
	add	bx,bx
	mov	ax,word ptr DGROUP:_pvfile_datatop
	mov	word ptr DGROUP:_pvfile_dataptr[bx],ax
	push	2
	push	ds
	mov	ax,si
	add	ax,ax
	add	ax,offset DGROUP:_pvfile_npolygs
	push	ax
	push	word ptr [bp-2]
	call	far ptr __rtl_read
	add	sp,8
	mov	ax,word ptr DGROUP:_pvfile+2
	mov	dx,word ptr DGROUP:_pvfile
	add	dx,word ptr DGROUP:_pvfile_datatop
	mov	bx,si
	shl	bx,2
	mov	word ptr DGROUP:_pv_n_vtx[bx+2],ax
	mov	word ptr DGROUP:_pv_n_vtx[bx],dx
	mov	bx,si
	add	bx,bx
	movzx	eax,word ptr DGROUP:_pvfile_npolygs[bx]
	add	dword ptr DGROUP:_pvfile_datatop,eax
	mov	ax,word ptr DGROUP:_pvfile+2
	mov	dx,word ptr DGROUP:_pvfile
	add	dx,word ptr DGROUP:_pvfile_datatop
	mov	bx,si
	shl	bx,2
	mov	word ptr DGROUP:_pvfile_x[bx+2],ax
	mov	word ptr DGROUP:_pvfile_x[bx],dx
	mov	bx,si
	add	bx,bx
	mov	ax,word ptr DGROUP:_pvfile_npolygs[bx]
	shl	ax,4
	movzx	eax,ax
	add	dword ptr DGROUP:_pvfile_datatop,eax
	mov	ax,word ptr DGROUP:_pvfile+2
	mov	dx,word ptr DGROUP:_pvfile
	add	dx,word ptr DGROUP:_pvfile_datatop
	mov	bx,si
	shl	bx,2
	mov	word ptr DGROUP:_pvfile_y[bx+2],ax
	mov	word ptr DGROUP:_pvfile_y[bx],dx
	mov	bx,si
	add	bx,bx
	mov	ax,word ptr DGROUP:_pvfile_npolygs[bx]
	shl	ax,4
	movzx	eax,ax
	add	dword ptr DGROUP:_pvfile_datatop,eax
	mov	ax,word ptr DGROUP:_pvfile+2
	mov	dx,word ptr DGROUP:_pvfile
	add	dx,word ptr DGROUP:_pvfile_datatop
	mov	bx,si
	shl	bx,2
	mov	word ptr DGROUP:_pvfile_z[bx+2],ax
	mov	word ptr DGROUP:_pvfile_z[bx],dx
	mov	bx,si
	add	bx,bx
	mov	ax,word ptr DGROUP:_pvfile_npolygs[bx]
	shl	ax,4
	movzx	eax,ax
	add	dword ptr DGROUP:_pvfile_datatop,eax
	mov	ax,word ptr DGROUP:_pvfile+2
	mov	dx,word ptr DGROUP:_pvfile
	add	dx,word ptr DGROUP:_pvfile_datatop
	mov	bx,si
	shl	bx,2
	mov	word ptr DGROUP:_pvfile_c[bx+2],ax
	mov	word ptr DGROUP:_pvfile_c[bx],dx
	mov	bx,si
	add	bx,bx
	movzx	eax,word ptr DGROUP:_pvfile_npolygs[bx]
	add	dword ptr DGROUP:_pvfile_datatop,eax
	mov	bx,si
	shl	bx,2
	mov	word ptr DGROUP:_pv_mid_x[bx+2],0
	mov	word ptr DGROUP:_pv_mid_x[bx],0
	cmp	dword ptr DGROUP:_pvfile_datatop,large 20480
	jbe	short @60@9
	mov	bx,si
	add	bx,bx
	movzx	eax,word ptr DGROUP:_pvfile_dataptr[bx]
	mov	dword ptr DGROUP:_pvfile_datatop,eax
	push	word ptr [bp-2]
	call	far ptr __rtl_close
	add	sp,2
	mov	al,0
	jmp	@60@44
@60@9:
	mov	bx,si
	add	bx,bx
	mov	ax,word ptr DGROUP:_pvfile_datatop
	sub	ax,word ptr DGROUP:_pvfile_dataptr[bx]
	push	ax
	mov	bx,si
	add	bx,bx
	mov	ax,word ptr DGROUP:_pvfile
	add	ax,word ptr DGROUP:_pvfile_dataptr[bx]
	push	word ptr DGROUP:_pvfile+2
	push	ax
	push	word ptr [bp-2]
	call	far ptr __rtl_read
	add	sp,8
	push	word ptr [bp-2]
	call	far ptr __rtl_close
	add	sp,2
	mov	word ptr [bp-6],0
	mov	word ptr [bp-10],0
	jmp	short @60@15
@60@11:
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pv_n_vtx[bx]
	add	bx,word ptr [bp-6]
	mov	al,byte ptr es:[bx]
	cbw	
	cmp	ax,3
	jne	short @60@13
	mov	ax,word ptr [bp-10]
	mov	bx,si
	shl	bx,2
	mov	es,word ptr DGROUP:_pvfile_x[bx+2]
	add	ax,word ptr DGROUP:_pvfile_x[bx]
	mov	bx,ax
	mov	dword ptr es:[bx+12],large 0
	mov	ax,word ptr [bp-10]
	mov	bx,si
	shl	bx,2
	mov	es,word ptr DGROUP:_pvfile_y[bx+2]
	add	ax,word ptr DGROUP:_pvfile_y[bx]
	mov	bx,ax
	mov	dword ptr es:[bx+12],large 0
	mov	ax,word ptr [bp-10]
	mov	bx,si
	shl	bx,2
	mov	es,word ptr DGROUP:_pvfile_z[bx+2]
	add	ax,word ptr DGROUP:_pvfile_z[bx]
	mov	bx,ax
	mov	dword ptr es:[bx+12],large 0
@60@13:
	add	word ptr [bp-10],16
	inc	word ptr [bp-6]
@60@15:
	mov	bx,si
	add	bx,bx
	mov	ax,word ptr DGROUP:_pvfile_npolygs[bx]
	cmp	ax,word ptr [bp-6]
	ja	short @60@11
	cmp	byte ptr [bp+38],0
	je	@60@20
	mov	ax,word ptr DGROUP:_pvfile+2
	mov	dx,word ptr DGROUP:_pvfile
	add	dx,word ptr DGROUP:_pvfile_datatop
	mov	bx,si
	shl	bx,2
	mov	word ptr DGROUP:_pv_mid_x[bx+2],ax
	mov	word ptr DGROUP:_pv_mid_x[bx],dx
	mov	bx,si
	add	bx,bx
	mov	ax,word ptr DGROUP:_pvfile_npolygs[bx]
	shl	ax,2
	movzx	eax,ax
	add	dword ptr DGROUP:_pvfile_datatop,eax
	mov	ax,word ptr DGROUP:_pvfile+2
	mov	dx,word ptr DGROUP:_pvfile
	add	dx,word ptr DGROUP:_pvfile_datatop
	mov	bx,si
	shl	bx,2
	mov	word ptr DGROUP:_pv_mid_y[bx+2],ax
	mov	word ptr DGROUP:_pv_mid_y[bx],dx
	mov	bx,si
	add	bx,bx
	mov	ax,word ptr DGROUP:_pvfile_npolygs[bx]
	shl	ax,2
	movzx	eax,ax
	add	dword ptr DGROUP:_pvfile_datatop,eax
	mov	ax,word ptr DGROUP:_pvfile+2
	mov	dx,word ptr DGROUP:_pvfile
	add	dx,word ptr DGROUP:_pvfile_datatop
	mov	bx,si
	shl	bx,2
	mov	word ptr DGROUP:_pv_mid_z[bx+2],ax
	mov	word ptr DGROUP:_pv_mid_z[bx],dx
	mov	bx,si
	add	bx,bx
	mov	ax,word ptr DGROUP:_pvfile_npolygs[bx]
	shl	ax,2
	movzx	eax,ax
	add	dword ptr DGROUP:_pvfile_datatop,eax
	mov	ax,word ptr DGROUP:_pvfile+2
	mov	dx,word ptr DGROUP:_pvfile
	add	dx,word ptr DGROUP:_pvfile_datatop
	mov	bx,si
	shl	bx,2
	mov	word ptr DGROUP:_pv_mid_d[bx+2],ax
	mov	word ptr DGROUP:_pv_mid_d[bx],dx
	mov	bx,si
	add	bx,bx
	mov	ax,word ptr DGROUP:_pvfile_npolygs[bx]
	shl	ax,2
	movzx	eax,ax
	add	dword ptr DGROUP:_pvfile_datatop,eax
	mov	ax,word ptr DGROUP:_pvfile+2
	mov	dx,word ptr DGROUP:_pvfile
	add	dx,word ptr DGROUP:_pvfile_datatop
	mov	bx,si
	shl	bx,2
	mov	word ptr DGROUP:_pv_dep_i[bx+2],ax
	mov	word ptr DGROUP:_pv_dep_i[bx],dx
	mov	bx,si
	add	bx,bx
	mov	ax,word ptr DGROUP:_pvfile_npolygs[bx]
	add	ax,ax
	movzx	eax,ax
	add	dword ptr DGROUP:_pvfile_datatop,eax
	cmp	dword ptr DGROUP:_pvfile_datatop,large 20480
	jbe	short @60@20
	mov	bx,si
	add	bx,bx
	movzx	eax,word ptr DGROUP:_pvfile_dataptr[bx]
	mov	dword ptr DGROUP:_pvfile_datatop,eax
@60@19:
	mov	al,0
	jmp	@60@44
@60@20:
	mov	word ptr [bp-4],0
	mov	word ptr [bp-12],0
	jmp	@60@25
@60@22:
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_x[bx]
	add	bx,word ptr [bp-12]
	fld	dword ptr es:[bx]
	fmul	dword ptr [bp+12]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_x[bx]
	add	bx,word ptr [bp-12]
	fstp	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	fwait	
	mov	bx,word ptr DGROUP:_pvfile_x[bx]
	add	bx,word ptr [bp-12]
	fld	dword ptr es:[bx]
	fadd	dword ptr [bp+24]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_x[bx]
	add	bx,word ptr [bp-12]
	fstp	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	fwait	
	les	bx,dword ptr DGROUP:_pvfile_y[bx]
	add	bx,word ptr [bp-12]
	fld	dword ptr es:[bx]
	fmul	dword ptr [bp+16]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_y[bx]
	add	bx,word ptr [bp-12]
	fstp	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	fwait	
	mov	bx,word ptr DGROUP:_pvfile_y[bx]
	add	bx,word ptr [bp-12]
	fld	dword ptr es:[bx]
	fadd	dword ptr [bp+28]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_y[bx]
	add	bx,word ptr [bp-12]
	fstp	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	fwait	
	les	bx,dword ptr DGROUP:_pvfile_z[bx]
	add	bx,word ptr [bp-12]
	fld	dword ptr es:[bx]
	fmul	dword ptr [bp+20]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_z[bx]
	add	bx,word ptr [bp-12]
	fstp	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	fwait	
	mov	bx,word ptr DGROUP:_pvfile_z[bx]
	add	bx,word ptr [bp-12]
	fld	dword ptr es:[bx]
	fadd	dword ptr [bp+32]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_z[bx]
	add	bx,word ptr [bp-12]
	fstp	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	fwait	
	les	bx,dword ptr DGROUP:_pvfile_c[bx]
	add	bx,word ptr [bp-4]
	mov	al,byte ptr es:[bx]
	add	al,byte ptr [bp+36]
	mov	bx,si
	shl	bx,2
	mov	bx,word ptr DGROUP:_pvfile_c[bx]
	add	bx,word ptr [bp-4]
	mov	byte ptr es:[bx],al
	add	word ptr [bp-12],4
	inc	word ptr [bp-4]
@60@25:
	mov	bx,si
	add	bx,bx
	mov	ax,word ptr DGROUP:_pvfile_npolygs[bx]
	shl	ax,2
	cmp	ax,word ptr [bp-4]
	ja	@60@22
	cmp	byte ptr [bp+38],0
	je	@60@42
	mov	word ptr [bp-6],0
	xor	di,di
	mov	word ptr [bp-16],0
	mov	word ptr [bp-18],0
	jmp	@60@41
@60@29:
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pv_dep_i[bx]
	add	bx,word ptr [bp-18]
	mov	ax,word ptr [bp-6]
	mov	word ptr es:[bx],ax
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pv_mid_d[bx]
	add	bx,di
	mov	dword ptr es:[bx],large 0
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pv_mid_x[bx]
	add	bx,di
	mov	dword ptr es:[bx],large 0
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pv_mid_y[bx]
	add	bx,di
	mov	dword ptr es:[bx],large 0
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pv_mid_z[bx]
	add	bx,di
	mov	dword ptr es:[bx],large 0
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pv_n_vtx[bx]
	add	bx,word ptr [bp-6]
	cmp	byte ptr es:[bx],0
	je	@60@37
	mov	word ptr [bp-4],0
	mov	ax,word ptr [bp-16]
	mov	word ptr [bp-14],ax
	jmp	@60@35
@60@32:
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_x[bx]
	add	bx,word ptr [bp-14]
	fld	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pv_mid_x[bx]
	add	bx,di
	fadd	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	mov	bx,word ptr DGROUP:_pv_mid_x[bx]
	add	bx,di
	fstp	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	fwait	
	les	bx,dword ptr DGROUP:_pvfile_y[bx]
	add	bx,word ptr [bp-14]
	fld	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pv_mid_y[bx]
	add	bx,di
	fadd	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	mov	bx,word ptr DGROUP:_pv_mid_y[bx]
	add	bx,di
	fstp	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	fwait	
	les	bx,dword ptr DGROUP:_pvfile_z[bx]
	add	bx,word ptr [bp-14]
	fld	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pv_mid_z[bx]
	add	bx,di
	fadd	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	mov	bx,word ptr DGROUP:_pv_mid_z[bx]
	add	bx,di
	fstp	dword ptr es:[bx]
	fwait	
	add	word ptr [bp-14],4
	inc	word ptr [bp-4]
@60@35:
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pv_n_vtx[bx]
	add	bx,word ptr [bp-6]
	mov	al,byte ptr es:[bx]
	cbw	
	cmp	ax,word ptr [bp-4]
	jg	@60@32
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pv_mid_x[bx]
	add	bx,di
	fld	dword ptr es:[bx]
	mov	ax,word ptr [bp-4]
	mov	word ptr [bp-8],ax
	fild	word ptr [bp-8]
	fdiv	
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pv_mid_x[bx]
	add	bx,di
	fstp	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	fwait	
	les	bx,dword ptr DGROUP:_pv_mid_y[bx]
	add	bx,di
	fld	dword ptr es:[bx]
	mov	word ptr [bp-8],ax
	fild	word ptr [bp-8]
	fdiv	
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pv_mid_y[bx]
	add	bx,di
	fstp	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	fwait	
	les	bx,dword ptr DGROUP:_pv_mid_z[bx]
	add	bx,di
	fld	dword ptr es:[bx]
	mov	word ptr [bp-8],ax
	fild	word ptr [bp-8]
	fdiv	
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pv_mid_z[bx]
	add	bx,di
	fstp	dword ptr es:[bx]
	fwait	
@60@37:
	add	di,4
	add	word ptr [bp-16],16
	add	word ptr [bp-18],2
	inc	word ptr [bp-6]
@60@41:
	mov	bx,si
	add	bx,bx
	mov	ax,word ptr DGROUP:_pvfile_npolygs[bx]
	cmp	ax,word ptr [bp-6]
	ja	@60@29
@60@42:
	mov	bx,si
	add	bx,bx
	mov	ax,word ptr DGROUP:_pvfile_datatop
	sub	ax,word ptr DGROUP:_pvfile_dataptr[bx]
	mov	bx,si
	add	bx,bx
	mov	word ptr DGROUP:_pvfile_datalen[bx],ax
	mov	al,1
@60@44:
	pop	di
	pop	si
	leave	
	ret	
@loadpv$qilffffffucc	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@QuickSort$qninfii	proc	far
	push	bp
	mov	bp,sp
	sub	sp,12
	push	si
	push	di
	mov	si,word ptr [bp+16]
	mov	di,word ptr [bp+14]
	mov	ax,word ptr [bp+14]
	add	ax,word ptr [bp+16]
	cwd	
	sub	ax,dx
	sar	ax,1
	add	ax,ax
	les	bx,dword ptr [bp+6]
	add	bx,ax
	mov	ax,word ptr es:[bx]
	shl	ax,2
	les	bx,dword ptr [bp+10]
	add	bx,ax
	fld	dword ptr es:[bx]
	fstp	dword ptr [bp-6]
	fwait	
	jmp	@61@12
@61@2:
	mov	ax,di
	add	ax,ax
	mov	word ptr [bp-10],ax
	jmp	short @61@5
@61@3:
	add	word ptr [bp-10],2
	inc	di
@61@5:
	les	bx,dword ptr [bp+6]
	add	bx,word ptr [bp-10]
	mov	ax,word ptr es:[bx]
	shl	ax,2
	les	bx,dword ptr [bp+10]
	add	bx,ax
	fld	dword ptr es:[bx]
	fcomp	dword ptr [bp-6]
	fstsw	word ptr [bp-8]
	fwait	
	mov	ax,word ptr [bp-8]
	sahf	
	ja	short @61@3
	mov	ax,si
	add	ax,ax
	mov	word ptr [bp-12],ax
	jmp	short @61@9
@61@7:
	sub	word ptr [bp-12],2
	dec	si
@61@9:
	les	bx,dword ptr [bp+6]
	add	bx,word ptr [bp-12]
	mov	ax,word ptr es:[bx]
	shl	ax,2
	les	bx,dword ptr [bp+10]
	add	bx,ax
	fld	dword ptr es:[bx]
	fcomp	dword ptr [bp-6]
	fstsw	word ptr [bp-8]
	fwait	
	mov	ax,word ptr [bp-8]
	sahf	
	jb	short @61@7
	cmp	di,si
	jg	short @61@12
	mov	ax,di
	add	ax,ax
	les	bx,dword ptr [bp+6]
	add	bx,ax
	mov	ax,word ptr es:[bx]
	mov	word ptr [bp-2],ax
	mov	ax,si
	add	ax,ax
	mov	bx,word ptr [bp+6]
	add	bx,ax
	mov	ax,word ptr es:[bx]
	mov	dx,di
	add	dx,dx
	mov	bx,word ptr [bp+6]
	add	bx,dx
	mov	word ptr es:[bx],ax
	mov	ax,si
	add	ax,ax
	mov	bx,word ptr [bp+6]
	add	bx,ax
	mov	ax,word ptr [bp-2]
	mov	word ptr es:[bx],ax
	inc	di
	dec	si
@61@12:
	cmp	di,si
	jle	@61@2
	cmp	word ptr [bp+14],si
	jge	short @61@15
	push	si
	push	word ptr [bp+14]
	push	dword ptr [bp+10]
	push	dword ptr [bp+6]
	push	cs
	call	near ptr @QuickSort$qninfii
	add	sp,12
@61@15:
	cmp	di,word ptr [bp+16]
	jge	short @61@17
	push	word ptr [bp+16]
	push	di
	push	dword ptr [bp+10]
	push	dword ptr [bp+6]
	push	cs
	call	near ptr @QuickSort$qninfii
	add	sp,12
@61@17:
	pop	di
	pop	si
	leave	
	ret	
@QuickSort$qninfii	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@drawpv$qiiifffc	proc	far
	push	bp
	mov	bp,sp
	sub	sp,36
	push	si
	push	di
	mov	si,word ptr [bp+6]
	cmp	si,16
	jge	@62@62
	mov	bx,si
	add	bx,bx
	cmp	word ptr DGROUP:_pvfile_datalen[bx],0
	je	@62@62
	fld	dword ptr [bp+12]
	fsubr	dword ptr DGROUP:_cam_x
	fstp	dword ptr DGROUP:_cam_x
	fld	dword ptr [bp+16]
	fsubr	dword ptr DGROUP:_cam_y
	fstp	dword ptr DGROUP:_cam_y
	fld	dword ptr [bp+20]
	fsubr	dword ptr DGROUP:_cam_z
	fstp	dword ptr DGROUP:_cam_z
	fwait	
	cmp	byte ptr [bp+24],0
	je	@62@35
	mov	bx,si
	shl	bx,2
	mov	ax,word ptr DGROUP:_pv_mid_x[bx]
	or	ax,word ptr DGROUP:_pv_mid_x[bx+2]
	je	@62@35
	mov	word ptr [bp-14],0
	mov	word ptr [bp-20],0
	jmp	@62@10
@62@7:
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pv_mid_x[bx]
	add	bx,word ptr [bp-20]
	fld	dword ptr es:[bx]
	fsub	dword ptr DGROUP:_cam_x
	fstp	dword ptr [bp-4]
	mov	bx,si
	shl	bx,2
	fwait	
	les	bx,dword ptr DGROUP:_pv_mid_y[bx]
	add	bx,word ptr [bp-20]
	fld	dword ptr es:[bx]
	fsub	dword ptr DGROUP:_cam_y
	fstp	dword ptr [bp-8]
	mov	bx,si
	shl	bx,2
	fwait	
	les	bx,dword ptr DGROUP:_pv_mid_z[bx]
	add	bx,word ptr [bp-20]
	fld	dword ptr es:[bx]
	fsub	dword ptr DGROUP:_cam_z
	fstp	dword ptr [bp-12]
	mov	bx,si
	shl	bx,2
	fwait	
	les	bx,dword ptr DGROUP:_pv_mid_d[bx]
	add	bx,word ptr [bp-20]
	fld	dword ptr [bp-4]
	fmul	dword ptr [bp-4]
	fld	dword ptr [bp-8]
	fmul	dword ptr [bp-8]
	fadd	
	fld	dword ptr [bp-12]
	fmul	dword ptr [bp-12]
	fadd	
	fstp	dword ptr es:[bx]
	fwait	
	add	word ptr [bp-20],4
	inc	word ptr [bp-14]
@62@10:
	mov	bx,si
	add	bx,bx
	mov	ax,word ptr DGROUP:_pvfile_npolygs[bx]
	cmp	ax,word ptr [bp-14]
	ja	@62@7
	mov	bx,si
	add	bx,bx
	dec	ax
	push	ax
	push	0
	mov	bx,si
	shl	bx,2
	push	dword ptr DGROUP:_pv_mid_d[bx]
	mov	bx,si
	shl	bx,2
	push	dword ptr DGROUP:_pv_dep_i[bx]
	push	cs
	call	near ptr @QuickSort$qninfii
	add	sp,12
	mov	word ptr [bp-14],0
	mov	word ptr [bp-22],0
	jmp	@62@33
@62@13:
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pv_dep_i[bx]
	add	bx,word ptr [bp-22]
	mov	ax,word ptr es:[bx]
	mov	word ptr [bp-16],ax
	shl	ax,2
	mov	di,ax
	mov	ax,word ptr [bp+8]
	or	ax,ax
	je	short @62@19
	cmp	ax,1
	je	short @62@20
	cmp	ax,2
	je	@62@29
	jmp	@62@31
@62@19:
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_c[bx]
	add	bx,word ptr [bp-16]
	mov	al,byte ptr es:[bx]
	push	ax
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pv_n_vtx[bx]
	add	bx,word ptr [bp-16]
	mov	al,byte ptr es:[bx]
	cbw	
	push	ax
	mov	bx,si
	shl	bx,2
	mov	ax,word ptr DGROUP:_pvfile_z[bx]
	mov	dx,di
	shl	dx,2
	add	ax,dx
	push	word ptr DGROUP:_pvfile_z[bx+2]
	push	ax
	mov	bx,si
	shl	bx,2
	mov	ax,word ptr DGROUP:_pvfile_y[bx]
	mov	dx,di
	shl	dx,2
	add	ax,dx
	push	word ptr DGROUP:_pvfile_y[bx+2]
	push	ax
	mov	bx,si
	shl	bx,2
	mov	ax,word ptr DGROUP:_pvfile_x[bx]
	mov	dx,di
	shl	dx,2
	add	ax,dx
	push	word ptr DGROUP:_pvfile_x[bx+2]
	push	ax
	push	cs
	call	near ptr @poly3d$qnft1t1uiuc
	add	sp,16
	jmp	@62@31
@62@20:
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_c[bx]
	add	bx,word ptr [bp-16]
	mov	al,byte ptr es:[bx]
	cbw	
	mov	word ptr [bp-18],ax
   	push	    ax
	mov	     ax, [bp-18]
	and	     ax, 03FH
	and	     [bp-18],  0C0H
	shr	     ax, 1
	or	  [bp-18],  ax
	pop	 ax 
	mov	al,byte ptr [bp-18]
	push	ax
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pv_n_vtx[bx]
	add	bx,word ptr [bp-16]
	mov	al,byte ptr es:[bx]
	push	ax
	mov	bx,si
	shl	bx,2
	mov	ax,word ptr DGROUP:_pvfile_z[bx]
	mov	dx,di
	shl	dx,2
	add	ax,dx
	push	word ptr DGROUP:_pvfile_z[bx+2]
	push	ax
	mov	bx,si
	shl	bx,2
	mov	ax,word ptr DGROUP:_pvfile_y[bx]
	mov	dx,di
	shl	dx,2
	add	ax,dx
	push	word ptr DGROUP:_pvfile_y[bx+2]
	push	ax
	mov	bx,si
	shl	bx,2
	mov	ax,word ptr DGROUP:_pvfile_x[bx]
	mov	dx,di
	shl	dx,2
	add	ax,dx
	push	word ptr DGROUP:_pvfile_x[bx+2]
	push	ax
	push	cs
	call	near ptr @polymap$qnft1t1cuc
	add	sp,16
	jmp	@62@31
@62@29:
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_c[bx]
	add	bx,word ptr [bp-16]
	mov	al,byte ptr es:[bx]
	mov	byte ptr DGROUP:_map_color_a,al
	add	al,254
	mov	byte ptr DGROUP:_map_color_b,al
	mov	al,byte ptr DGROUP:_map_color_a
	add	al,255
	mov	byte ptr DGROUP:_map_color_c,al
	mov	al,byte ptr DGROUP:_map_color_a
	inc	al
	mov	byte ptr DGROUP:_map_color_d,al
	mov	al,byte ptr [bp+10]
	push	ax
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_z[bx]
	lea	ax,word ptr [di+2]
	shl	ax,2
	mov	word ptr [bp-32],ax
	add	bx,ax
	push	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_y[bx]
	lea	ax,word ptr [di+2]
	shl	ax,2
	add	bx,ax
	push	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_x[bx]
	lea	ax,word ptr [di+2]
	shl	ax,2
	add	bx,ax
	push	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_z[bx]
	lea	ax,word ptr [di+1]
	shl	ax,2
	mov	word ptr [bp-34],ax
	add	bx,ax
	push	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_y[bx]
	lea	ax,word ptr [di+1]
	shl	ax,2
	add	bx,ax
	push	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_x[bx]
	lea	ax,word ptr [di+1]
	shl	ax,2
	add	bx,ax
	push	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_z[bx]
	mov	ax,di
	shl	ax,2
	add	bx,ax
	push	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_y[bx]
	mov	ax,di
	shl	ax,2
	add	bx,ax
	push	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_x[bx]
	mov	ax,di
	shl	ax,2
	add	bx,ax
	push	dword ptr es:[bx]
	push	cs
	call	near ptr @randomic_mapper$qfffffffffc
	add	sp,38
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pv_n_vtx[bx]
	add	bx,word ptr [bp-14]
	mov	al,byte ptr es:[bx]
	cbw	
	cmp	ax,4
	jne	@62@31
	mov	al,byte ptr [bp+10]
	push	ax
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_z[bx]
	mov	ax,di
	shl	ax,2
	add	bx,ax
	push	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_y[bx]
	mov	ax,di
	shl	ax,2
	add	bx,ax
	push	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_x[bx]
	mov	ax,di
	shl	ax,2
	add	bx,ax
	push	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_z[bx]
	lea	ax,word ptr [di+3]
	shl	ax,2
	mov	word ptr [bp-36],ax
	add	bx,ax
	push	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_y[bx]
	lea	ax,word ptr [di+3]
	shl	ax,2
	add	bx,ax
	push	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_x[bx]
	lea	ax,word ptr [di+3]
	shl	ax,2
	add	bx,ax
	push	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_z[bx]
	lea	ax,word ptr [di+2]
	shl	ax,2
	mov	word ptr [bp-32],ax
	add	bx,ax
	push	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_y[bx]
	lea	ax,word ptr [di+2]
	shl	ax,2
	add	bx,ax
	push	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_x[bx]
	lea	ax,word ptr [di+2]
	shl	ax,2
	add	bx,ax
	push	dword ptr es:[bx]
	push	cs
	call	near ptr @randomic_mapper$qfffffffffc
	add	sp,38
@62@31:
	add	word ptr [bp-22],2
	inc	word ptr [bp-14]
@62@33:
	mov	bx,si
	add	bx,bx
	mov	ax,word ptr DGROUP:_pvfile_npolygs[bx]
	cmp	ax,word ptr [bp-14]
	ja	@62@13
	jmp	@62@61
@62@35:
	mov	word ptr [bp-14],0
	xor	di,di
	mov	word ptr [bp-24],0
	mov	word ptr [bp-26],8
	mov	word ptr [bp-28],4
	mov	word ptr [bp-30],12
	jmp	@62@60
@62@37:
	mov	ax,word ptr [bp+8]
	or	ax,ax
	je	short @62@42
	cmp	ax,1
	je	short @62@43
	cmp	ax,2
	je	@62@52
	jmp	@62@54
@62@42:
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_c[bx]
	add	bx,word ptr [bp-14]
	mov	al,byte ptr es:[bx]
	push	ax
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pv_n_vtx[bx]
	add	bx,word ptr [bp-14]
	mov	al,byte ptr es:[bx]
	cbw	
	push	ax
	mov	bx,si
	shl	bx,2
	mov	ax,word ptr DGROUP:_pvfile_z[bx]
	add	ax,word ptr [bp-24]
	push	word ptr DGROUP:_pvfile_z[bx+2]
	push	ax
	mov	bx,si
	shl	bx,2
	mov	ax,word ptr DGROUP:_pvfile_y[bx]
	add	ax,word ptr [bp-24]
	push	word ptr DGROUP:_pvfile_y[bx+2]
	push	ax
	mov	bx,si
	shl	bx,2
	mov	ax,word ptr DGROUP:_pvfile_x[bx]
	add	ax,word ptr [bp-24]
	push	word ptr DGROUP:_pvfile_x[bx+2]
	push	ax
	push	cs
	call	near ptr @poly3d$qnft1t1uiuc
	add	sp,16
	jmp	@62@54
@62@43:
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_c[bx]
	add	bx,word ptr [bp-14]
	mov	al,byte ptr es:[bx]
	cbw	
	mov	word ptr [bp-18],ax
   	push	    ax
	mov	     ax, [bp-18]
	and	     ax, 03FH
	and	     [bp-18],  0C0H
	shr	     ax, 1
	or	  [bp-18],  ax
	pop	 ax 
	mov	al,byte ptr [bp-18]
	push	ax
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pv_n_vtx[bx]
	add	bx,word ptr [bp-14]
	mov	al,byte ptr es:[bx]
	push	ax
	mov	bx,si
	shl	bx,2
	mov	ax,word ptr DGROUP:_pvfile_z[bx]
	add	ax,word ptr [bp-24]
	push	word ptr DGROUP:_pvfile_z[bx+2]
	push	ax
	mov	bx,si
	shl	bx,2
	mov	ax,word ptr DGROUP:_pvfile_y[bx]
	add	ax,word ptr [bp-24]
	push	word ptr DGROUP:_pvfile_y[bx+2]
	push	ax
	mov	bx,si
	shl	bx,2
	mov	ax,word ptr DGROUP:_pvfile_x[bx]
	add	ax,word ptr [bp-24]
	push	word ptr DGROUP:_pvfile_x[bx+2]
	push	ax
	push	cs
	call	near ptr @polymap$qnft1t1cuc
	add	sp,16
	jmp	@62@54
@62@52:
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_c[bx]
	add	bx,word ptr [bp-14]
	mov	al,byte ptr es:[bx]
	mov	byte ptr DGROUP:_map_color_a,al
	add	al,254
	mov	byte ptr DGROUP:_map_color_b,al
	mov	al,byte ptr DGROUP:_map_color_a
	add	al,255
	mov	byte ptr DGROUP:_map_color_c,al
	mov	al,byte ptr DGROUP:_map_color_a
	inc	al
	mov	byte ptr DGROUP:_map_color_d,al
	mov	al,byte ptr [bp+10]
	push	ax
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_z[bx]
	add	bx,word ptr [bp-26]
	push	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_y[bx]
	add	bx,word ptr [bp-26]
	push	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_x[bx]
	add	bx,word ptr [bp-26]
	push	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_z[bx]
	add	bx,word ptr [bp-28]
	push	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_y[bx]
	add	bx,word ptr [bp-28]
	push	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_x[bx]
	add	bx,word ptr [bp-28]
	push	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_z[bx]
	add	bx,word ptr [bp-24]
	push	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_y[bx]
	add	bx,word ptr [bp-24]
	push	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_x[bx]
	add	bx,word ptr [bp-24]
	push	dword ptr es:[bx]
	push	cs
	call	near ptr @randomic_mapper$qfffffffffc
	add	sp,38
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pv_n_vtx[bx]
	add	bx,word ptr [bp-14]
	mov	al,byte ptr es:[bx]
	cbw	
	cmp	ax,4
	jne	@62@54
	mov	al,byte ptr [bp+10]
	push	ax
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_z[bx]
	add	bx,word ptr [bp-24]
	push	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_y[bx]
	add	bx,word ptr [bp-24]
	push	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_x[bx]
	add	bx,word ptr [bp-24]
	push	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_z[bx]
	add	bx,word ptr [bp-30]
	push	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_y[bx]
	add	bx,word ptr [bp-30]
	push	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_x[bx]
	add	bx,word ptr [bp-30]
	push	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_z[bx]
	add	bx,word ptr [bp-26]
	push	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_y[bx]
	add	bx,word ptr [bp-26]
	push	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_x[bx]
	add	bx,word ptr [bp-26]
	push	dword ptr es:[bx]
	push	cs
	call	near ptr @randomic_mapper$qfffffffffc
	add	sp,38
@62@54:
	inc	word ptr [bp-14]
	add	word ptr [bp-24],16
	add	word ptr [bp-26],16
	add	word ptr [bp-28],16
	add	word ptr [bp-30],16
	add	di,4
@62@60:
	mov	bx,si
	add	bx,bx
	mov	ax,word ptr DGROUP:_pvfile_npolygs[bx]
	cmp	ax,word ptr [bp-14]
	ja	@62@37
@62@61:
	fld	dword ptr [bp+12]
	fadd	dword ptr DGROUP:_cam_x
	fstp	dword ptr DGROUP:_cam_x
	fld	dword ptr [bp+16]
	fadd	dword ptr DGROUP:_cam_y
	fstp	dword ptr DGROUP:_cam_y
	fld	dword ptr [bp+20]
	fadd	dword ptr DGROUP:_cam_z
	fstp	dword ptr DGROUP:_cam_z
	fwait	
@62@62:
	pop	di
	pop	si
	leave	
	ret	
@drawpv$qiiifffc	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@copypv$qii	proc	far
	push	bp
	mov	bp,sp
	push	si
	push	di
	mov	di,word ptr [bp+6]
	mov	si,word ptr [bp+8]
	cmp	si,16
	jge	short @63@6
	cmp	di,16
	jge	short @63@6
	mov	bx,si
	add	bx,bx
	cmp	word ptr DGROUP:_pvfile_datalen[bx],0
	je	short @63@6
	mov	bx,di
	add	bx,bx
	mov	ax,word ptr DGROUP:_pvfile_datalen[bx]
	mov	bx,si
	add	bx,bx
	cmp	ax,word ptr DGROUP:_pvfile_datalen[bx]
	jne	short @63@6
	mov	bx,si
	add	bx,bx
	push	word ptr DGROUP:_pvfile_datalen[bx]
	mov	bx,si
	shl	bx,2
	push	dword ptr DGROUP:_pv_n_vtx[bx]
	mov	bx,di
	shl	bx,2
	push	dword ptr DGROUP:_pv_n_vtx[bx]
	call	far ptr __fmemmove
	add	sp,10
@63@6:
	pop	di
	pop	si
	pop	bp
	ret	
@copypv$qii	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@modpv$qiiiffffffn6pvlist	proc	far
	push	bp
	mov	bp,sp
	sub	sp,72
	push	si
	push	di
	mov	si,word ptr [bp+6]
	cmp	si,16
	jge	@64@56
	mov	bx,si
	add	bx,bx
	cmp	word ptr DGROUP:_pvfile_datalen[bx],0
	je	@64@56
	fld	dword ptr [bp+24]
	fmul	qword ptr DGROUP:_deg
	sub	sp,8
	fstp	qword ptr [bp-84]
	fwait	
	call	far ptr _sin
	add	sp,8
	fstp	dword ptr [bp-4]
	fld	dword ptr [bp+24]
	fmul	qword ptr DGROUP:_deg
	sub	sp,8
	fstp	qword ptr [bp-84]
	fwait	
	call	far ptr _cos
	add	sp,8
	fstp	dword ptr [bp-8]
	fld	dword ptr [bp+28]
	fmul	qword ptr DGROUP:_deg
	sub	sp,8
	fstp	qword ptr [bp-84]
	fwait	
	call	far ptr _sin
	add	sp,8
	fstp	dword ptr [bp-12]
	fld	dword ptr [bp+28]
	fmul	qword ptr DGROUP:_deg
	sub	sp,8
	fstp	qword ptr [bp-84]
	fwait	
	call	far ptr _cos
	add	sp,8
	fstp	dword ptr [bp-16]
	fld	dword ptr [bp+32]
	fmul	qword ptr DGROUP:_deg
	sub	sp,8
	fstp	qword ptr [bp-84]
	fwait	
	call	far ptr _sin
	add	sp,8
	fstp	dword ptr [bp-20]
	fld	dword ptr [bp+32]
	fmul	qword ptr DGROUP:_deg
	sub	sp,8
	fstp	qword ptr [bp-84]
	fwait	
	call	far ptr _cos
	add	sp,8
	fstp	dword ptr [bp-24]
	fwait	
	cmp	word ptr [bp+8],-1
	jle	short @64@6
	cmp	word ptr [bp+10],-1
	jle	short @64@6
	mov	ax,word ptr [bp+8]
	shl	ax,2
	add	ax,word ptr [bp+10]
	mov	word ptr [bp-30],ax
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_x[bx]
	shl	ax,2
	add	bx,ax
	fld	dword ptr es:[bx]
	fstp	dword ptr [bp-48]
	mov	bx,si
	shl	bx,2
	fwait	
	les	bx,dword ptr DGROUP:_pvfile_y[bx]
	mov	ax,word ptr [bp-30]
	shl	ax,2
	add	bx,ax
	fld	dword ptr es:[bx]
	fstp	dword ptr [bp-52]
	mov	bx,si
	shl	bx,2
	fwait	
	les	bx,dword ptr DGROUP:_pvfile_z[bx]
	mov	ax,word ptr [bp-30]
	shl	ax,2
	add	bx,ax
	fld	dword ptr es:[bx]
	fstp	dword ptr [bp-56]
	fwait	
	jmp	short @64@7
@64@6:
	mov	dword ptr [bp-48],large 0
	mov	dword ptr [bp-52],large 0
	mov	dword ptr [bp-56],large 0
@64@7:
	cmp	dword ptr [bp+36],large 0
	jne	@64@21
	mov	word ptr [bp-28],0
	mov	word ptr [bp-62],0
	jmp	@64@19
@64@10:
	mov	ax,word ptr [bp-62]
	mov	word ptr [bp-30],ax
	xor	di,di
	shl	ax,2
	mov	word ptr [bp-60],ax
	jmp	@64@16
@64@12:
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_x[bx]
	add	bx,word ptr [bp-60]
	fld	dword ptr es:[bx]
	fsub	dword ptr [bp-48]
	fmul	dword ptr [bp-16]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_z[bx]
	add	bx,word ptr [bp-60]
	fld	dword ptr es:[bx]
	fsub	dword ptr [bp-56]
	fmul	dword ptr [bp-12]
	fadd	
	fstp	dword ptr [bp-36]
	mov	bx,si
	shl	bx,2
	fwait	
	les	bx,dword ptr DGROUP:_pvfile_z[bx]
	add	bx,word ptr [bp-60]
	fld	dword ptr es:[bx]
	fsub	dword ptr [bp-56]
	fmul	dword ptr [bp-16]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_x[bx]
	add	bx,word ptr [bp-60]
	fld	dword ptr es:[bx]
	fsub	dword ptr [bp-48]
	fmul	dword ptr [bp-12]
	fsub	
	fstp	dword ptr [bp-44]
	mov	bx,si
	shl	bx,2
	fwait	
	les	bx,dword ptr DGROUP:_pvfile_y[bx]
	add	bx,word ptr [bp-60]
	fld	dword ptr es:[bx]
	fsub	dword ptr [bp-52]
	fmul	dword ptr [bp-4]
	fld	dword ptr [bp-44]
	fmul	dword ptr [bp-8]
	fadd	
	fmul	dword ptr [bp+20]
	fadd	dword ptr [bp-56]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_z[bx]
	add	bx,word ptr [bp-60]
	fstp	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	fwait	
	les	bx,dword ptr DGROUP:_pvfile_y[bx]
	add	bx,word ptr [bp-60]
	fld	dword ptr es:[bx]
	fsub	dword ptr [bp-52]
	fmul	dword ptr [bp-8]
	fld	dword ptr [bp-44]
	fmul	dword ptr [bp-4]
	fsub	
	fstp	dword ptr [bp-40]
	mov	bx,si
	shl	bx,2
	fwait	
	les	bx,dword ptr DGROUP:_pvfile_x[bx]
	add	bx,word ptr [bp-60]
	fld	dword ptr [bp-36]
	fmul	dword ptr [bp-24]
	fld	dword ptr [bp-40]
	fmul	dword ptr [bp-20]
	fadd	
	fmul	dword ptr [bp+12]
	fadd	dword ptr [bp-48]
	fstp	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	fwait	
	les	bx,dword ptr DGROUP:_pvfile_y[bx]
	add	bx,word ptr [bp-60]
	fld	dword ptr [bp-40]
	fmul	dword ptr [bp-24]
	fld	dword ptr [bp-36]
	fmul	dword ptr [bp-20]
	fsub	
	fmul	dword ptr [bp+16]
	fadd	dword ptr [bp-52]
	fstp	dword ptr es:[bx]
	fwait	
	add	word ptr [bp-60],4
	inc	word ptr [bp-30]
	inc	di
@64@16:
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pv_n_vtx[bx]
	add	bx,word ptr [bp-28]
	mov	al,byte ptr es:[bx]
	cbw	
	cmp	ax,di
	jg	@64@12
	add	word ptr [bp-62],4
	inc	word ptr [bp-28]
@64@19:
	mov	bx,si
	add	bx,bx
	mov	ax,word ptr DGROUP:_pvfile_npolygs[bx]
	cmp	ax,word ptr [bp-28]
	ja	@64@10
	jmp	@64@42
@64@21:
	mov	word ptr [bp-28],0
	mov	word ptr [bp-64],0
	jmp	@64@41
@64@23:
	mov	ax,word ptr [bp-72]
	mov	word ptr [bp-26],ax
	shl	ax,2
	mov	word ptr [bp-30],ax
	xor	di,di
@64@24:
	or	di,di
	jne	short @64@27
	mov	es,word ptr [bp+38]
	mov	bx,word ptr [bp-70]
	test	byte ptr es:[bx+1],16
	setne	al
	je	short @64@27
	mov	ax,word ptr [bp-30]
	mov	word ptr [bp-32],ax
	jmp	short @64@36
@64@27:
	cmp	di,1
	jne	short @64@30
	mov	es,word ptr [bp+38]
	mov	bx,word ptr [bp-70]
	test	byte ptr es:[bx+1],32
	setne	al
	je	short @64@30
	mov	ax,word ptr [bp-30]
	inc	ax
	mov	word ptr [bp-32],ax
	jmp	short @64@36
@64@30:
	cmp	di,2
	jne	short @64@33
	mov	es,word ptr [bp+38]
	mov	bx,word ptr [bp-70]
	test	byte ptr es:[bx+1],64
	setne	al
	je	short @64@33
	mov	ax,word ptr [bp-30]
	add	ax,2
	mov	word ptr [bp-32],ax
	jmp	short @64@36
@64@33:
	cmp	di,3
	jne	@64@37
	mov	es,word ptr [bp+38]
	mov	bx,word ptr [bp-70]
	test	byte ptr es:[bx+1],128
	setne	al
	je	@64@37
	mov	ax,word ptr [bp-30]
	add	ax,3
	mov	word ptr [bp-32],ax
@64@36:
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_x[bx]
	mov	ax,word ptr [bp-32]
	shl	ax,2
	add	bx,ax
	fld	dword ptr es:[bx]
	fsub	dword ptr [bp-48]
	fmul	dword ptr [bp-16]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_z[bx]
	mov	ax,word ptr [bp-32]
	shl	ax,2
	add	bx,ax
	fld	dword ptr es:[bx]
	fsub	dword ptr [bp-56]
	fmul	dword ptr [bp-12]
	fadd	
	fstp	dword ptr [bp-36]
	mov	bx,si
	shl	bx,2
	fwait	
	les	bx,dword ptr DGROUP:_pvfile_z[bx]
	mov	ax,word ptr [bp-32]
	shl	ax,2
	add	bx,ax
	fld	dword ptr es:[bx]
	fsub	dword ptr [bp-56]
	fmul	dword ptr [bp-16]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_x[bx]
	mov	ax,word ptr [bp-32]
	shl	ax,2
	add	bx,ax
	fld	dword ptr es:[bx]
	fsub	dword ptr [bp-48]
	fmul	dword ptr [bp-12]
	fsub	
	fstp	dword ptr [bp-44]
	mov	bx,si
	shl	bx,2
	fwait	
	les	bx,dword ptr DGROUP:_pvfile_y[bx]
	mov	ax,word ptr [bp-32]
	shl	ax,2
	add	bx,ax
	fld	dword ptr es:[bx]
	fsub	dword ptr [bp-52]
	fmul	dword ptr [bp-4]
	fld	dword ptr [bp-44]
	fmul	dword ptr [bp-8]
	fadd	
	fmul	dword ptr [bp+20]
	fadd	dword ptr [bp-56]
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_z[bx]
	mov	ax,word ptr [bp-32]
	shl	ax,2
	add	bx,ax
	fstp	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	fwait	
	les	bx,dword ptr DGROUP:_pvfile_y[bx]
	mov	ax,word ptr [bp-32]
	shl	ax,2
	add	bx,ax
	fld	dword ptr es:[bx]
	fsub	dword ptr [bp-52]
	fmul	dword ptr [bp-8]
	fld	dword ptr [bp-44]
	fmul	dword ptr [bp-4]
	fsub	
	fstp	dword ptr [bp-40]
	mov	bx,si
	shl	bx,2
	fwait	
	les	bx,dword ptr DGROUP:_pvfile_x[bx]
	mov	ax,word ptr [bp-32]
	shl	ax,2
	add	bx,ax
	fld	dword ptr [bp-36]
	fmul	dword ptr [bp-24]
	fld	dword ptr [bp-40]
	fmul	dword ptr [bp-20]
	fadd	
	fmul	dword ptr [bp+12]
	fadd	dword ptr [bp-48]
	fstp	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	fwait	
	les	bx,dword ptr DGROUP:_pvfile_y[bx]
	mov	ax,word ptr [bp-32]
	shl	ax,2
	add	bx,ax
	fld	dword ptr [bp-40]
	fmul	dword ptr [bp-24]
	fld	dword ptr [bp-36]
	fmul	dword ptr [bp-20]
	fsub	
	fmul	dword ptr [bp+16]
	fadd	dword ptr [bp-52]
	fstp	dword ptr es:[bx]
	fwait	
@64@37:
	inc	di
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pv_n_vtx[bx]
	add	bx,word ptr [bp-26]
	mov	al,byte ptr es:[bx]
	cbw	
	cmp	ax,di
	jg	@64@24
	add	word ptr [bp-64],2
	inc	word ptr [bp-28]
@64@41:
	les	bx,dword ptr [bp+36]
	add	bx,word ptr [bp-64]
	mov	word ptr [bp-70],bx
	mov	ax,word ptr es:[bx]
	and	ax,4095
	mov	word ptr [bp-72],ax
	cmp	ax,4095
	jne	@64@23
@64@42:
	mov	bx,si
	shl	bx,2
	mov	ax,word ptr DGROUP:_pv_mid_x[bx]
	or	ax,word ptr DGROUP:_pv_mid_x[bx+2]
	je	@64@56
	mov	word ptr [bp-28],0
	mov	word ptr [bp-68],0
	jmp	@64@55
@64@45:
	mov	ax,word ptr [bp-68]
	mov	word ptr [bp-30],ax
	mov	dword ptr [bp-48],large 0
	mov	dword ptr [bp-52],large 0
	mov	dword ptr [bp-56],large 0
	xor	di,di
	shl	ax,2
	mov	word ptr [bp-66],ax
	jmp	short @64@51
@64@47:
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pvfile_x[bx]
	add	bx,word ptr [bp-66]
	fld	dword ptr es:[bx]
	fadd	dword ptr [bp-48]
	fstp	dword ptr [bp-48]
	mov	bx,si
	shl	bx,2
	fwait	
	les	bx,dword ptr DGROUP:_pvfile_y[bx]
	add	bx,word ptr [bp-66]
	fld	dword ptr es:[bx]
	fadd	dword ptr [bp-52]
	fstp	dword ptr [bp-52]
	mov	bx,si
	shl	bx,2
	fwait	
	les	bx,dword ptr DGROUP:_pvfile_z[bx]
	add	bx,word ptr [bp-66]
	fld	dword ptr es:[bx]
	fadd	dword ptr [bp-56]
	fstp	dword ptr [bp-56]
	fwait	
	add	word ptr [bp-66],4
	inc	word ptr [bp-30]
	inc	di
@64@51:
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pv_n_vtx[bx]
	add	bx,word ptr [bp-28]
	mov	al,byte ptr es:[bx]
	cbw	
	cmp	ax,di
	jg	short @64@47
	mov	bx,si
	shl	bx,2
	les	bx,dword ptr DGROUP:_pv_mid_x[bx]
	add	bx,word ptr [bp-68]
	mov	word ptr [bp-58],di
	fild	word ptr [bp-58]
	fdivr	dword ptr [bp-48]
	fstp	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	fwait	
	les	bx,dword ptr DGROUP:_pv_mid_y[bx]
	add	bx,word ptr [bp-68]
	mov	word ptr [bp-58],di
	fild	word ptr [bp-58]
	fdivr	dword ptr [bp-52]
	fstp	dword ptr es:[bx]
	mov	bx,si
	shl	bx,2
	fwait	
	les	bx,dword ptr DGROUP:_pv_mid_z[bx]
	add	bx,word ptr [bp-68]
	mov	word ptr [bp-58],di
	fild	word ptr [bp-58]
	fdivr	dword ptr [bp-56]
	fstp	dword ptr es:[bx]
	fwait	
	add	word ptr [bp-68],4
	inc	word ptr [bp-28]
@64@55:
	mov	bx,si
	add	bx,bx
	mov	ax,word ptr DGROUP:_pvfile_npolygs[bx]
	cmp	ax,word ptr [bp-28]
	ja	@64@45
@64@56:
	pop	di
	pop	si
	leave	
	ret	
@modpv$qiiiffffffn6pvlist	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@alphavalue$qd	proc	far
	push	bp
	mov	bp,sp
	push	ds
	push	offset DGROUP:_dec
	push	15
	fld	qword ptr [bp+6]
	sub	sp,8
	fstp	qword ptr [bp-14]
	fwait	
	call	far ptr _gcvt
	add	sp,14
	mov	dx,ds
	mov	ax,offset DGROUP:_dec
	pop	bp
	ret	
@alphavalue$qd	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@background$quinuct2t2uiui	proc	far
	push	bp
	mov	bp,sp
	push	si
	push	di
   	pusha	
	push	 ds
	les	 ax, dword ptr [bp+8]
	add	 [bp+22], ax
	mov	 dx, [bp+22]
	mov	 ax, es
	les	 bx, dword ptr [bp+12]
	mov	 bx, es
	mov	 cx, [bp+20]
	shr	 cx, 1
	lds	 si, dword ptr [bp+16]
	mov	 bp, [bp+6]
	add	 bp, 4
	db	 08EH, 0E3H 
	mov	 es, ax 
@66@16:
   	cmp	 word ptr [si], 64000
	jae	short @66@48
	mov	 di, [si]
	add	 di, dx
	db	 064H, 08AH, 046H, 000H 
	mov	 ah, al
	db	 066H
	shl	 ax, 8
	mov	 al, ah
	db	 066H
	shl	 ax, 8
	mov	 al, ah
	db	 066H
	mov	 es:[di], ax
	mov	 es:[di+4], al
	db	 066H
	mov	 es:[di+320], ax
	mov	 es:[di+324], al
	db	 066H
	mov	 es:[di+640], ax
	mov	 es:[di+644], al
	db	 066H
	mov	 es:[di+960], ax
	mov	 es:[di+964], al
	db	 066H
	mov	 es:[di+1280], ax
	mov	 es:[di+1284], al
	add	 bp, 1
	add	 si, 2
	dec	 cx
	jne	short @66@16
	jmp	short @66@54
@66@48:
   	mov	 bx, [si]
	sub	 bx, 64000
	add	 bp, bx
	add	 si, 2
	dec	 cx
	jne	short @66@16
@66@54:
   	pop	 ds
	popa	 
	pop	di
	pop	si
	pop	bp
	ret	
@background$quinuct2t2uiui	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@sky$qui	proc	far
	push	bp
	mov	bp,sp
	sub	sp,134
	push	si
	push	di
	mov	dword ptr [bp-4],large 03B9ACA00h
	mov	byte ptr [bp-5],9
	cmp	byte ptr DGROUP:_field_amplificator,0
	je	short @67@3
	mov	byte ptr [bp-5],14
@67@3:
	cmp	byte ptr DGROUP:_ap_targetting,0
	jne	short @67@5
	mov	dword ptr [bp-36],large 0461C4000h
	jmp	short @67@6
@67@5:
	mov	dword ptr [bp-36],large 03F800000h
@67@6:
	mov	dword ptr [bp-60],large 0000186A0h
	mov	al,byte ptr [bp-5]
	cbw	
	mov	word ptr [bp-100],ax
	cwde	
	imul	eax,large 0000186A0h
	mov	dword ptr [bp-64],eax
	fld	qword ptr DGROUP:_dzat_x
	fmul	qword ptr DGROUP:_dzat_x
	fld	qword ptr DGROUP:_dzat_z
	fmul	qword ptr DGROUP:_dzat_z
	fadd	
	sub	sp,8
	fstp	qword ptr [bp-146]
	fwait	
	call	far ptr _sqrt
	add	sp,8
	fstp	qword ptr [bp-90]
	fld	qword ptr DGROUP:_dzat_y
	fabs	
	fmul	dword ptr DGROUP:s@+1586
	fadd	qword ptr [bp-90]
	fstp	qword ptr [bp-90]
	fld	qword ptr [bp-90]
	fmul	qword ptr DGROUP:s@+1590
	call	far ptr F_FTOL@
	mov	word ptr [bp-82],ax
	mov	ax,1
	mov	cl,byte ptr [bp-82]
	shl	ax,cl
	mov	word ptr [bp-82],ax
	dec	word ptr [bp-82]
	mov	al,byte ptr [bp-5]
	cbw	
	mov	word ptr [bp-100],ax
	cwde	
	imul	eax,large 0C350h
	mov	dword ptr [bp-94],eax
	fild	dword ptr [bp-94]
	fsubr	qword ptr DGROUP:_dzat_x
	fdiv	dword ptr DGROUP:s@+1598
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	dword ptr [bp-40],eax
	imul	eax,large 0000186A0h
	mov	dword ptr [bp-40],eax
	mov	al,byte ptr [bp-5]
	cbw	
	mov	word ptr [bp-100],ax
	cwde	
	imul	eax,large 0C350h
	mov	dword ptr [bp-94],eax
	fild	dword ptr [bp-94]
	fsubr	qword ptr DGROUP:_dzat_y
	fdiv	dword ptr DGROUP:s@+1598
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	dword ptr [bp-44],eax
	imul	eax,large 0000186A0h
	mov	dword ptr [bp-44],eax
	mov	al,byte ptr [bp-5]
	cbw	
	mov	word ptr [bp-100],ax
	cwde	
	imul	eax,large 0C350h
	mov	dword ptr [bp-94],eax
	fild	dword ptr [bp-94]
	fsubr	qword ptr DGROUP:_dzat_z
	fdiv	dword ptr DGROUP:s@+1598
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	dword ptr [bp-48],eax
	imul	eax,large 0000186A0h
	mov	dword ptr [bp-48],eax
	mov	dword ptr [bp-98],large 0
	mov	byte ptr [bp-6],0
	jmp	@67@37
@67@7:
	mov	byte ptr [bp-7],0
	jmp	@67@35
@67@8:
	mov	byte ptr [bp-8],0
	jmp	@67@33
@67@9:
	mov	word ptr [bp-110],-15536
	mov	eax,dword ptr [bp-40]
	add	eax,dword ptr [bp-48]
	mov	dword ptr [bp-104],eax
	and	eax,large 00001FFFFh
	add	eax,dword ptr [bp-40]
	mov	dword ptr [bp-68],eax
	movzx	eax,word ptr [bp-110]
	mov	dword ptr [bp-108],eax
	cmp	eax,dword ptr [bp-68]
	je	@67@32
	mov	eax,dword ptr [bp-108]
	sub	dword ptr [bp-68],eax
	push	dword ptr [bp-104]
	push	dword ptr [bp-68]
	push	cs
	call	near ptr @carryAddMultiply$qll
	add	sp,8
	mov	word ptr [bp-112],dx
	mov	word ptr [bp-114],ax
	mov	eax,dword ptr [bp-40]
	add	eax,dword ptr [bp-48]
	mov	dword ptr [bp-104],eax
	add	eax,dword ptr [bp-114]
	mov	dword ptr [bp-118],eax
	mov	eax,dword ptr [bp-114]
	and	eax,large 00001FFFFh
	add	eax,dword ptr [bp-44]
	mov	dword ptr [bp-72],eax
	movzx	eax,word ptr [bp-110]
	mov	dword ptr [bp-108],eax
	cmp	eax,dword ptr [bp-72]
	je	@67@32
	mov	eax,dword ptr [bp-108]
	sub	dword ptr [bp-72],eax
	push	dword ptr [bp-118]
	push	dword ptr [bp-72]
	push	cs
	call	near ptr @carryAddMultiply$qll
	add	sp,8
	mov	word ptr [bp-112],dx
	mov	word ptr [bp-114],ax
	mov	eax,dword ptr [bp-114]
	and	eax,large 00001FFFFh
	add	eax,dword ptr [bp-48]
	mov	dword ptr [bp-76],eax
	movzx	eax,word ptr [bp-110]
	mov	dword ptr [bp-108],eax
	cmp	eax,dword ptr [bp-76]
	je	@67@32
	mov	eax,dword ptr [bp-108]
	sub	dword ptr [bp-76],eax
	mov	eax,dword ptr [bp-68]
	add	eax,dword ptr [bp-72]
	add	eax,dword ptr [bp-76]
	mov	dword ptr [bp-122],eax
	cmp	word ptr [bp-82],0
	je	short @67@14
	mov	ax,1
	jmp	short @67@15
@67@14:
	xor	ax,ax
@67@15:
	cwde	
	test	eax,dword ptr [bp-122]
	jne	@67@32
	mov	eax,dword ptr [bp-76]
	mov	dword ptr [bp-94],eax
	fild	dword ptr [bp-94]
	fsub	qword ptr DGROUP:_dzat_z
	fstp	dword ptr [bp-20]
	fwait	
	mov	eax,dword ptr [bp-68]
	mov	dword ptr [bp-94],eax
	fild	dword ptr [bp-94]
	fsub	qword ptr DGROUP:_dzat_x
	fstp	dword ptr [bp-12]
	fwait	
	mov	eax,dword ptr [bp-72]
	mov	dword ptr [bp-94],eax
	fild	dword ptr [bp-94]
	fsub	qword ptr DGROUP:_dzat_y
	fstp	dword ptr [bp-16]
	fld	dword ptr [bp-20]
	fmul	dword ptr DGROUP:_opt_tcosbeta
	fld	dword ptr [bp-12]
	fmul	dword ptr DGROUP:_opt_tsinbeta
	fsub	
	fstp	dword ptr [bp-24]
	fld	dword ptr [bp-24]
	fmul	dword ptr DGROUP:_opt_tcosalfa
	fld	dword ptr [bp-16]
	fmul	dword ptr DGROUP:_opt_tsinalfa
	fadd	
	fstp	dword ptr [bp-28]
	fld	dword ptr [bp-28]
	fcomp	dword ptr [bp-36]
	fstsw	word ptr [bp-94]
	fwait	
	mov	ax,word ptr [bp-94]
	sahf	
	jb	@67@32
	fld	dword ptr DGROUP:_uno
	fdiv	dword ptr [bp-28]
	fstp	dword ptr [bp-32]
	fld	dword ptr [bp-12]
	fmul	dword ptr DGROUP:_opt_pcosbeta
	fld	dword ptr [bp-20]
	fmul	dword ptr DGROUP:_opt_psinbeta
	fadd	
	fmul	dword ptr [bp-32]
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	dword ptr [bp-52],eax
	add	eax,large 158
	mov	dword ptr [bp-98],eax
	cmp	dword ptr [bp-98],large 10
	jbe	@67@32
	cmp	dword ptr [bp-98],large 310
	jae	@67@32
	fld	dword ptr [bp-16]
	fmul	dword ptr DGROUP:_opt_pcosalfa
	fld	dword ptr [bp-24]
	fmul	dword ptr DGROUP:_opt_psinalfa
	fsub	
	fmul	dword ptr [bp-32]
	fsub	dword ptr DGROUP:s@+12
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	dword ptr [bp-56],eax
	mov	ax,word ptr [bp-56]
	add	ax,100
	mov	si,ax
	cmp	si,10
	jbe	@67@32
	cmp	si,190
	jae	@67@32
	mov	ax,2
	imul	si
	mov	si,ax
	mov	al,byte ptr DGROUP:_riga[si]
	mov	ah,0
	mov	word ptr [bp-124],ax
	mov	al,byte ptr DGROUP:_riga[si+1]
	mov	ah,0
	mov	word ptr [bp-126],ax
	shl	ax,8
	add	ax,word ptr [bp-124]
	mov	word ptr [bp-128],ax
	movzx	eax,word ptr [bp-128]
	add	dword ptr [bp-98],eax
	mov	al,byte ptr DGROUP:_ap_targetting
	cbw	
	cmp	ax,1
	je	short @67@25
	les	bx,dword ptr DGROUP:_adapted
	add	bx,word ptr [bp-98]
	mov	di,bx
	mov	al,byte ptr es:[bx]
	mov	byte ptr [bp-134],al
	cmp	byte ptr [bp-134],68
	je	@67@32
	mov	ah,0
	mov	dx,word ptr [bp+6]
	shr	dx,8
	cmp	ax,dx
	jb	@67@32
	mov	al,byte ptr [bp-134]
	mov	ah,0
	mov	dx,word ptr [bp+6]
	and	dx,255
	cmp	ax,dx
	ja	@67@32
@67@25:
	fld	dword ptr [bp-28]
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	dword ptr [bp-80],eax
	mov	cl,byte ptr DGROUP:_field_amplificator
	add	cl,13
	sar	eax,cl
	mov	dword ptr [bp-132],eax
	mov	al,63
	sub	al,byte ptr [bp-132]
	mov	byte ptr [bp-133],al
	cbw	
	or	ax,ax
	jl	short @67@29
	les	bx,dword ptr DGROUP:_adapted
	add	bx,word ptr [bp-98]
	mov	di,bx
	mov	cl,byte ptr es:[bx]
	and	byte ptr es:[di],192
	and	cl,63
	add	byte ptr [bp-133],cl
	mov	al,byte ptr [bp-133]
	cbw	
	cmp	ax,63
	jle	short @67@28
	mov	byte ptr [bp-133],63
@67@28:
	les	bx,dword ptr DGROUP:_adapted
	add	bx,word ptr [bp-98]
	mov	di,bx
	mov	al,byte ptr [bp-133]
	or	byte ptr es:[bx],al
@67@29:
	mov	al,byte ptr DGROUP:_ap_targetting
	cbw	
	cmp	ax,1
	jne	short @67@32
	mov	eax,dword ptr [bp-52]
	imul	eax,dword ptr [bp-52]
	mov	edx,dword ptr [bp-56]
	imul	edx,dword ptr [bp-56]
	add	eax,edx
	mov	dword ptr [bp-80],eax
	cmp	eax,dword ptr [bp-4]
	jge	short @67@32
	mov	dword ptr [bp-4],eax
	mov	eax,dword ptr [bp-68]
	mov	dword ptr [bp-94],eax
	fild	dword ptr [bp-94]
	fstp	qword ptr DGROUP:_ap_target_x
	fwait	
	mov	eax,dword ptr [bp-72]
	mov	dword ptr [bp-94],eax
	fild	dword ptr [bp-94]
	fstp	qword ptr DGROUP:_ap_target_y
	fwait	
	mov	eax,dword ptr [bp-76]
	mov	dword ptr [bp-94],eax
	fild	dword ptr [bp-94]
	fstp	qword ptr DGROUP:_ap_target_z
	fwait	
@67@32:
	inc	byte ptr [bp-8]
	mov	eax,dword ptr [bp-60]
	add	dword ptr [bp-48],eax
@67@33:
	mov	al,byte ptr [bp-8]
	mov	ah,0
	push	ax
	mov	al,byte ptr [bp-5]
	cbw	
	mov	word ptr [bp-100],ax
	pop	dx
	cmp	dx,ax
	jl	@67@9
	inc	byte ptr [bp-7]
	mov	eax,dword ptr [bp-60]
	add	dword ptr [bp-44],eax
	mov	eax,dword ptr [bp-64]
	sub	dword ptr [bp-48],eax
@67@35:
	mov	al,byte ptr [bp-7]
	mov	ah,0
	cmp	ax,word ptr [bp-100]
	jl	@67@8
	inc	byte ptr [bp-6]
	mov	eax,dword ptr [bp-60]
	add	dword ptr [bp-40],eax
	mov	eax,dword ptr [bp-64]
	sub	dword ptr [bp-44],eax
@67@37:
	mov	al,byte ptr [bp-6]
	mov	ah,0
	push	ax
	mov	al,byte ptr [bp-5]
	cbw	
	mov	word ptr [bp-100],ax
	pop	dx
	cmp	dx,ax
	jl	@67@7
	pop	di
	pop	si
	leave	
	ret	
@sky$qui	endp
NOCTIS-0_TEXT	ends
_DATA	segment word public use16 'DATA'
_glass_bubble	label	byte
	db	1
_DATA	ends
NOCTIS-0_TEXT	segment byte public use16 'CODE'
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@gman1x1$qv	proc	far
	push	di
 	mov	 es:[di+4], dl
	pop	di
	ret	
@gman1x1$qv	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@gman2x2$qv	proc	far
	push	di
	mov	 dh, dl
	mov	 es:[di+4], dx
	mov	 es:[di+324], dx
	pop	di
	ret	
@gman2x2$qv	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@gman3x3$qv	proc	far
	push	di
	mov	 dh, dl
	mov	 es:[di+4], dx
	mov	 es:[di+6], dl
	mov	 es:[di+324], dx
	mov	 es:[di+326], dl
	mov	 es:[di+644], dx
	mov	 es:[di+646], dl
	pop	di
	ret	
@gman3x3$qv	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@gman4x4$qv	proc	far
	push	di
	mov	 dh, dl
	mov	 es:[di+4], dx
	mov	 es:[di+6], dx
	mov	 es:[di+324], dx
	mov	 es:[di+326], dx
	mov	 es:[di+644], dx
	mov	 es:[di+646], dx
	mov	 es:[di+964], dx
	mov	 es:[di+966], dx
	pop	di
	ret	
@gman4x4$qv	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@globe$quinuct2t2uidddfcc	proc	far
	push	bp
	mov	bp,sp
	sub	sp,68
	push	si
	push	di
	fld	qword ptr [bp+22]
	fsub	qword ptr DGROUP:_dzat_x
	fstp	qword ptr [bp-18]
	fld	qword ptr [bp+30]
	fsub	qword ptr DGROUP:_dzat_y
	fstp	qword ptr [bp-26]
	fld	qword ptr [bp+38]
	fsub	qword ptr DGROUP:_dzat_z
	fstp	qword ptr [bp-34]
	fld	dword ptr DGROUP:_opt_pcosbeta
	fmul	qword ptr [bp-18]
	fld	dword ptr DGROUP:_opt_psinbeta
	fmul	qword ptr [bp-34]
	fadd	
	fstp	qword ptr [bp-50]
	fld	dword ptr DGROUP:_opt_tcosbeta
	fmul	qword ptr [bp-34]
	fld	dword ptr DGROUP:_opt_tsinbeta
	fmul	qword ptr [bp-18]
	fsub	
	fstp	qword ptr [bp-42]
	fld	dword ptr DGROUP:_opt_tcosalfa
	fmul	qword ptr [bp-42]
	fld	dword ptr DGROUP:_opt_tsinalfa
	fmul	qword ptr [bp-26]
	fadd	
	fstp	qword ptr [bp-66]
	fld	dword ptr DGROUP:_opt_pcosalfa
	fmul	qword ptr [bp-26]
	fld	dword ptr DGROUP:_opt_psinalfa
	fmul	qword ptr [bp-42]
	fsub	
	fstp	qword ptr [bp-58]
	fld	qword ptr [bp-66]
	fcomp	qword ptr DGROUP:s@+1542
	fstsw	word ptr [bp-68]
	fwait	
	mov	ax,word ptr [bp-68]
	sahf	
	jb	@72@70
	fld	dword ptr [bp+46]
	fdiv	qword ptr [bp-66]
	fstp	dword ptr [bp+46]
	fwait	
	mov	word ptr [bp-2],seg @gman1x1$qv
	mov	word ptr [bp-4],offset @gman1x1$qv
	fld	dword ptr [bp+46]
	fcomp	qword ptr DGROUP:s@+1602
	fstsw	word ptr [bp-68]
	fwait	
	mov	ax,word ptr [bp-68]
	sahf	
	jae	short @72@4
	mov	dword ptr [bp+46],large 03A83126Fh
@72@4:
	fld	dword ptr [bp+46]
	fcomp	qword ptr DGROUP:s@+1610
	fstsw	word ptr [bp-68]
	fwait	
	mov	ax,word ptr [bp-68]
	sahf	
	jbe	short @72@6
	mov	word ptr [bp-2],seg @gman2x2$qv
	mov	word ptr [bp-4],offset @gman2x2$qv
@72@6:
	fld	dword ptr [bp+46]
	fcomp	qword ptr DGROUP:s@+1618
	fstsw	word ptr [bp-68]
	fwait	
	mov	ax,word ptr [bp-68]
	sahf	
	jbe	short @72@8
	mov	word ptr [bp-2],seg @gman3x3$qv
	mov	word ptr [bp-4],offset @gman3x3$qv
@72@8:
	fld	dword ptr [bp+46]
	fcomp	qword ptr DGROUP:s@+1626
	fstsw	word ptr [bp-68]
	fwait	
	mov	ax,word ptr [bp-68]
	sahf	
	jbe	short @72@10
	mov	word ptr [bp-2],seg @gman4x4$qv
	mov	word ptr [bp-4],offset @gman4x4$qv
@72@10:
	fld	dword ptr [bp+46]
	fcomp	qword ptr DGROUP:s@+1634
	fstsw	word ptr [bp-68]
	fwait	
	mov	ax,word ptr [bp-68]
	sahf	
	jbe	short @72@12
	mov	dword ptr [bp+46],large 03FA8F5C3h
@72@12:
	fld	qword ptr [bp-66]
	fdivr	qword ptr [bp-50]
	fstp	qword ptr [bp-50]
	fld	qword ptr [bp-66]
	fdivr	qword ptr [bp-58]
	fstp	qword ptr [bp-58]
	fld	qword ptr [bp-50]
	fcomp	qword ptr DGROUP:s@+1642
	fstsw	word ptr [bp-68]
	fwait	
	mov	ax,word ptr [bp-68]
	sahf	
	jb	@72@70
	fld	qword ptr [bp-50]
	fcomp	dword ptr DGROUP:s@+1650
	fstsw	word ptr [bp-68]
	fwait	
	mov	ax,word ptr [bp-68]
	sahf	
	ja	@72@70
	fld	qword ptr [bp-58]
	fcomp	qword ptr DGROUP:s@+1654
	fstsw	word ptr [bp-68]
	fwait	
	mov	ax,word ptr [bp-68]
	sahf	
	jb	@72@70
	fld	qword ptr [bp-58]
	fcomp	dword ptr DGROUP:s@+1662
	fstsw	word ptr [bp-68]
	fwait	
	mov	ax,word ptr [bp-68]
	sahf	
	ja	@72@70
	fld	dword ptr DGROUP:_x_centro_f
	fadd	qword ptr [bp-50]
	call	far ptr F_FTOL@
	mov	word ptr [bp-6],ax
	fld	dword ptr DGROUP:_y_centro_f
	fadd	qword ptr [bp-58]
	call	far ptr F_FTOL@
	mov	word ptr [bp-8],ax
 	pusha	
 	push	 ds
 	push	 ds
 	db	 00FH, 0A9H 
	mov	cx,word ptr [bp+20]
	shr	cx,1
 	les	 ax, dword ptr [bp+12]
	add	word ptr [bp+6],ax
	mov	bx,word ptr [bp+6]
	mov	ax,es
 	db	 08EH, 0E0H 
 	les	 ax, dword ptr [bp+8]
 	lds	 si, dword ptr [bp+16]
@72@27:
 	cmp	 byte ptr [si], 100
	jne	short @72@30
	jmp	@72@60
@72@30:
 	mov	 al, [si]
 	cbw	
	mov	word ptr [bp-10],ax
	mov	ax,word ptr [bp-10]
	mov	word ptr [bp-68],ax
	fild	word ptr [bp-68]
	fmul	dword ptr [bp+46]
	call	far ptr F_FTOL@
	mov	word ptr [bp-10],ax
	mov	di,word ptr [bp-10]
	add	di,word ptr [bp-8]
 	cmp	 di, 6
	jb	short @72@58
 	cmp	 di, 191
	jae	short @72@58
 	mov	 al, [si+1]      
 	add	 di, di
 	cbw	         
 	db	 065H, 08BH, 0BDH 
 	dw	 offset DGROUP:_riga      
 	mov	 [bp-10], ax        
 	fild	 word ptr [bp-10]
 	fmul	 dword ptr [bp+46]
 	fistp	 word ptr [bp-10]
 	mov	 ax, [bp-10]
 	add	 ax, [bp-6]
 	cmp	 ax, 6
	jb	short @72@58
 	cmp	 ax, 311
	jae	short @72@58
 	add	 di, ax
 	db	 064H, 08AH, 017H 
 	cmp	 dl, [bp+52]
	jae	short @72@57
 	mov	 dl, [bp+52]
@72@57:
	or	dl,byte ptr [bp+50]
	call	dword ptr [bp-4]
@72@58:
	inc	bx
	add	si,2
	dec	cx
	or	cx,cx
	jne	@72@27
	jmp	short @72@62
@72@60:
 	mov	 al, [si+1]
	xor	ah,ah
	add	bx,ax
	add	si,2
	dec	cx
	or	cx,cx
	jne	@72@27
@72@62:
	pop	 ds
	popa	
	cmp	byte ptr DGROUP:_glass_bubble,0
	je	@72@70
	fld	dword ptr [bp+46]
	fmul	dword ptr DGROUP:s@+1666
	call	far ptr F_FTOL@
	mov	word ptr [bp-10],ax
	cmp	word ptr [bp-10],0
	je	@72@70
	fld	dword ptr [bp+46]
	fmul	dword ptr DGROUP:s@+1670
	fstp	qword ptr [bp-50]
	fld	qword ptr DGROUP:s@+1674
	fmul	qword ptr DGROUP:_deg
	fdiv	dword ptr [bp+46]
	fstp	qword ptr [bp-58]
	fld	dword ptr DGROUP:s@+1582
	fmul	qword ptr [bp-58]
	fstp	qword ptr [bp-66]
	fld	qword ptr DGROUP:s@+1682
	fmul	qword ptr [bp-50]
	fstp	qword ptr [bp-42]
	jmp	short @72@68
@72@67:
	push	1
	movsx	eax,word ptr [bp-10]
	push	eax
	fld	qword ptr [bp-66]
	sub	sp,8
	fstp	qword ptr [bp-86]
	fwait	
	call	far ptr _sin
	add	sp,8
	fmul	qword ptr [bp-42]
	mov	ax,word ptr [bp-8]
	mov	word ptr [bp-68],ax
	fild	word ptr [bp-68]
	fadd	
	call	far ptr F_FTOL@
	push	dx
	push	ax
	fld	qword ptr [bp-66]
	sub	sp,8
	fstp	qword ptr [bp-90]
	fwait	
	call	far ptr _cos
	add	sp,8
	fmul	qword ptr [bp-50]
	mov	ax,word ptr [bp-6]
	mov	word ptr [bp-68],ax
	fild	word ptr [bp-68]
	fadd	
	call	far ptr F_FTOL@
	push	dx
	push	ax
	push	dword ptr [bp+8]
	push	cs
	call	near ptr @smootharound_64$qnuclllc
	add	sp,18
	fld	qword ptr [bp-58]
	fadd	qword ptr [bp-66]
	fstp	qword ptr [bp-66]
@72@68:
	fwait	
	fld	qword ptr [bp-66]
	fcomp	qword ptr DGROUP:s@+1510
	fstsw	word ptr [bp-68]
	fwait	
	mov	ax,word ptr [bp-68]
	sahf	
	jb	@72@67
@72@70:
	pop	di
	pop	si
	leave	
	ret	
@globe$quinuct2t2uidddfcc	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@glowinglobe$qinuct2uidddfiiuc	proc	far
	push	bp
	mov	bp,sp
	sub	sp,64
	push	si
	push	di
	fld	qword ptr [bp+18]
	fsub	qword ptr DGROUP:_dzat_x
	fstp	qword ptr [bp-14]
	fld	qword ptr [bp+26]
	fsub	qword ptr DGROUP:_dzat_y
	fstp	qword ptr [bp-22]
	fld	qword ptr [bp+34]
	fsub	qword ptr DGROUP:_dzat_z
	fstp	qword ptr [bp-30]
	fld	dword ptr DGROUP:_opt_pcosbeta
	fmul	qword ptr [bp-14]
	fld	dword ptr DGROUP:_opt_psinbeta
	fmul	qword ptr [bp-30]
	fadd	
	fstp	qword ptr [bp-46]
	fld	dword ptr DGROUP:_opt_tcosbeta
	fmul	qword ptr [bp-30]
	fld	dword ptr DGROUP:_opt_tsinbeta
	fmul	qword ptr [bp-14]
	fsub	
	fstp	qword ptr [bp-38]
	fld	dword ptr DGROUP:_opt_tcosalfa
	fmul	qword ptr [bp-38]
	fld	dword ptr DGROUP:_opt_tsinalfa
	fmul	qword ptr [bp-22]
	fadd	
	fstp	qword ptr [bp-62]
	fld	dword ptr DGROUP:_opt_pcosalfa
	fmul	qword ptr [bp-22]
	fld	dword ptr DGROUP:_opt_psinalfa
	fmul	qword ptr [bp-38]
	fsub	
	fstp	qword ptr [bp-54]
	fld	qword ptr [bp-62]
	fcomp	qword ptr DGROUP:s@+1542
	fstsw	word ptr [bp-64]
	fwait	
	mov	ax,word ptr [bp-64]
	sahf	
	jb	@73@90
	fld	dword ptr [bp+42]
	fdiv	qword ptr [bp-62]
	fstp	dword ptr [bp+42]
	fld	dword ptr [bp+42]
	fcomp	qword ptr DGROUP:s@+1618
	fstsw	word ptr [bp-64]
	fwait	
	mov	ax,word ptr [bp-64]
	sahf	
	jbe	short @73@4
	mov	dword ptr [bp+42],large 03F28F5C3h
@73@4:
	fld	dword ptr [bp+42]
	fcomp	qword ptr DGROUP:s@+1602
	fstsw	word ptr [bp-64]
	fwait	
	mov	ax,word ptr [bp-64]
	sahf	
	jae	short @73@6
	mov	dword ptr [bp+42],large 03A83126Fh
@73@6:
	fld	qword ptr [bp-62]
	fdivr	qword ptr [bp-46]
	fstp	qword ptr [bp-46]
	fld	qword ptr [bp-62]
	fdivr	qword ptr [bp-54]
	fstp	qword ptr [bp-54]
	fld	qword ptr [bp-46]
	fcomp	qword ptr DGROUP:s@+1690
	fstsw	word ptr [bp-64]
	fwait	
	mov	ax,word ptr [bp-64]
	sahf	
	jb	@73@90
	fld	qword ptr [bp-46]
	fcomp	dword ptr DGROUP:s@+1698
	fstsw	word ptr [bp-64]
	fwait	
	mov	ax,word ptr [bp-64]
	sahf	
	ja	@73@90
	fld	qword ptr [bp-54]
	fcomp	qword ptr DGROUP:s@+1702
	fstsw	word ptr [bp-64]
	fwait	
	mov	ax,word ptr [bp-64]
	sahf	
	jb	@73@90
	fld	qword ptr [bp-54]
	fcomp	dword ptr DGROUP:s@+1710
	fstsw	word ptr [bp-64]
	fwait	
	mov	ax,word ptr [bp-64]
	sahf	
	ja	@73@90
	fld	dword ptr DGROUP:_x_centro_f
	fadd	qword ptr [bp-46]
	call	far ptr F_FTOL@
	mov	word ptr [bp-2],ax
	fld	dword ptr DGROUP:_y_centro_f
	fadd	qword ptr [bp-54]
	call	far ptr F_FTOL@
	mov	word ptr [bp-4],ax
	mov	ax,word ptr [bp+46]
	sub	word ptr [bp+6],ax
	jmp	short @73@12
@73@11:
	add	word ptr [bp+6],360
@73@12:
	cmp	word ptr [bp+6],0
	jl	short @73@11
   	pusha	
	push	 ds
	push	 ds
	db	 00FH, 0A9H 
	mov	 cx, [bp+16]
	shr	 cx, 1
	mov	 bl, [bp+50]
	and	 bl, 0C0H
	mov	 bh, [bp+50]
	and	 bh, 03FH
	shr	 bh, 2
	or	  bh, bl
	mov	 bl, [bp+50]
	mov	 dx, [bp+6]
	les	 ax, dword ptr [bp+8]
	lds	 si, dword ptr [bp+12] 
@73@29:
   	cmp	 byte ptr [si], 100
	jne	short @73@32
	jmp	@73@77
@73@32:
   	test	 dx, 3
	je	short @73@35
	jmp	@73@69
@73@35:
   	mov	 al, [si]
	cbw	
	mov	 [bp-6], ax
	fild	 word ptr [bp-6]
	fmul	 dword ptr [bp+42]
	fistp	 word ptr [bp-6]
	mov	 di, [bp-6]
	add	 di, [bp-4]
	cmp	 di, 10
	jae	short @73@48
	cmp	 di, 190
	jb	short @73@48
	jmp	short @73@69
@73@48:
   	mov	 al, [si+1]
	add	 di, di
	cbw	
	db	 065H, 08BH, 0BDH 
	dw	 offset DGROUP:_riga
	mov	 [bp-6], ax
	fild	 word ptr [bp-6]
	fmul	 dword ptr [bp+42]
	fistp	 word ptr [bp-6]
	mov	 ax, [bp-6]
	add	 ax, [bp-2]
	cmp	 ax, 9
	jb	short @73@69
	cmp	 ax, 310
	jae	short @73@69
	add	 di, ax
	cmp	 dx, [bp+48]
	jb	short @73@68
	mov	 es:[di+4], bl
	jmp	short @73@69
@73@68:
     	mov	 es:[di+4], bh
@73@69:
   	add	 dx, 1
	cmp	 dx, 360
	jb	short @73@73
	xor	 dx, dx 
@73@73:
   	add	 si, 2
	dec	 cx
	je	short @73@88
	jmp	@73@29
@73@77:
   	mov	 al, [si+1]
	xor	 ah, ah
	add	 dx, ax 
@73@80:
   	cmp	 dx, 360
	jb	short @73@84
	sub	 dx, 360
	jmp	short @73@80
@73@84:
   	add	 si, 2
	dec	 cx
	je	short @73@88
	jmp	@73@29
@73@88:
   	pop	 ds
	popa	 
@73@90:
	pop	di
	pop	si
	leave	
	ret	
@glowinglobe$qinuct2uidddfiiuc	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@whiteglobe$qnucdddff	proc	far
	push	bp
	mov	bp,sp
	sub	sp,158
	push	di
	fld	qword ptr [bp+10]
	fsub	qword ptr DGROUP:_dzat_x
	fstp	qword ptr [bp-56]
	fld	qword ptr [bp+18]
	fsub	qword ptr DGROUP:_dzat_y
	fstp	qword ptr [bp-64]
	fld	qword ptr [bp+26]
	fsub	qword ptr DGROUP:_dzat_z
	fstp	qword ptr [bp-72]
	fld	dword ptr DGROUP:_opt_pcosbeta
	fmul	qword ptr [bp-56]
	fld	dword ptr DGROUP:_opt_psinbeta
	fmul	qword ptr [bp-72]
	fadd	
	fstp	qword ptr [bp-88]
	fld	dword ptr DGROUP:_opt_tcosbeta
	fmul	qword ptr [bp-72]
	fld	dword ptr DGROUP:_opt_tsinbeta
	fmul	qword ptr [bp-56]
	fsub	
	fstp	qword ptr [bp-80]
	fld	dword ptr DGROUP:_opt_tcosalfa
	fmul	qword ptr [bp-80]
	fld	dword ptr DGROUP:_opt_tsinalfa
	fmul	qword ptr [bp-64]
	fadd	
	fstp	qword ptr [bp-104]
	fld	dword ptr DGROUP:_opt_pcosalfa
	fmul	qword ptr [bp-64]
	fld	dword ptr DGROUP:_opt_psinalfa
	fmul	qword ptr [bp-80]
	fsub	
	fstp	qword ptr [bp-96]
	fld	qword ptr [bp-104]
	fcomp	qword ptr DGROUP:s@+1542
	fstsw	word ptr [bp-158]
	fwait	
	mov	ax,word ptr [bp-158]
	sahf	
	jb	@74@44
	fld	dword ptr [bp+34]
	fdiv	qword ptr [bp-104]
	fstp	dword ptr [bp+34]
	fld	dword ptr [bp+34]
	fcomp	qword ptr DGROUP:s@+1714
	fstsw	word ptr [bp-158]
	fwait	
	mov	ax,word ptr [bp-158]
	sahf	
	jbe	short @74@4
	mov	dword ptr [bp+34],large 0403F5C29h
@74@4:
	fld	dword ptr [bp+34]
	fcomp	qword ptr DGROUP:s@+1602
	fstsw	word ptr [bp-158]
	fwait	
	mov	ax,word ptr [bp-158]
	sahf	
	jae	short @74@6
	mov	dword ptr [bp+34],large 03C23D70Ah
@74@6:
	fld	qword ptr [bp-104]
	fdivr	qword ptr [bp-88]
	fstp	qword ptr [bp-88]
	fld	qword ptr [bp-104]
	fdivr	qword ptr [bp-96]
	fstp	qword ptr [bp-96]
	fld	qword ptr [bp-88]
	fcomp	qword ptr DGROUP:s@+1722
	fstsw	word ptr [bp-158]
	fwait	
	mov	ax,word ptr [bp-158]
	sahf	
	jb	@74@44
	fld	qword ptr [bp-88]
	fcomp	dword ptr DGROUP:s@+1730
	fstsw	word ptr [bp-158]
	fwait	
	mov	ax,word ptr [bp-158]
	sahf	
	ja	@74@44
	fld	qword ptr [bp-96]
	fcomp	qword ptr DGROUP:s@+1734
	fstsw	word ptr [bp-158]
	fwait	
	mov	ax,word ptr [bp-158]
	sahf	
	jb	@74@44
	fld	qword ptr [bp-96]
	fcomp	dword ptr DGROUP:s@+1742
	fstsw	word ptr [bp-158]
	fwait	
	mov	ax,word ptr [bp-158]
	sahf	
	ja	@74@44
	fld	dword ptr DGROUP:_x_centro_f
	fadd	qword ptr [bp-88]
	fadd	dword ptr DGROUP:s@+1582
	fstp	qword ptr [bp-8]
	fld	dword ptr DGROUP:_y_centro_f
	fadd	qword ptr [bp-96]
	fadd	dword ptr DGROUP:s@+1582
	fstp	qword ptr [bp-16]
	fld	dword ptr [bp+34]
	fmul	dword ptr DGROUP:s@+1746
	fadd	dword ptr DGROUP:s@+1750
	fstp	qword ptr [bp-24]
	fld	dword ptr [bp+38]
	fmul	qword ptr [bp-24]
	fstp	qword ptr [bp-32]
	fld	qword ptr [bp-24]
	fsub	qword ptr [bp-32]
	fstp	qword ptr [bp-40]
	fld	qword ptr [bp-40]
	fld1	
	fcompp
	fstsw	word ptr [bp-158]
	fwait	
	mov	ax,word ptr [bp-158]
	sahf	
	jbe	short @74@12
	fld1	
	fstp	qword ptr [bp-40]
	fwait	
@74@12:
	fld	dword ptr DGROUP:s@+1754
	fdiv	qword ptr [bp-40]
	fstp	qword ptr [bp-48]
	fld	qword ptr [bp-24]
	fmul	qword ptr [bp-24]
	fstp	qword ptr [bp-144]
	fld	qword ptr [bp-32]
	fmul	qword ptr [bp-32]
	fstp	qword ptr [bp-152]
	fwait	
	les	     dx, dword ptr [bp+6]
	mov	     ax, es
	shr	     dx, 4
	add	     ax, dx
	db	      08EH, 0e0H 
	fld	qword ptr [bp-24]
	fchs	
	fmul	qword ptr DGROUP:s@+1674
	fstp	qword ptr [bp-120]
	fld	qword ptr [bp-16]
	fadd	qword ptr [bp-24]
	fstp	qword ptr [bp-136]
	fld	qword ptr [bp-16]
	fsub	qword ptr [bp-24]
	fstp	qword ptr [bp-64]
	jmp	@74@42
@74@19:
	fld	qword ptr [bp-24]
	fchs	
	fstp	qword ptr [bp-112]
	fld	qword ptr [bp-8]
	fadd	qword ptr [bp-24]
	fstp	qword ptr [bp-128]
	fld	qword ptr [bp-8]
	fsub	qword ptr [bp-24]
	fstp	qword ptr [bp-56]
	jmp	@74@39
@74@20:
	fld	qword ptr [bp-56]
	fcomp	dword ptr DGROUP:s@+1758
	fstsw	word ptr [bp-158]
	fwait	
	mov	ax,word ptr [bp-158]
	sahf	
	jbe	@74@38
	fld	qword ptr [bp-56]
	fcomp	dword ptr DGROUP:s@+1762
	fstsw	word ptr [bp-158]
	fwait	
	mov	ax,word ptr [bp-158]
	sahf	
	jae	@74@38
	fld	qword ptr [bp-64]
	fcomp	dword ptr DGROUP:s@+1758
	fstsw	word ptr [bp-158]
	fwait	
	mov	ax,word ptr [bp-158]
	sahf	
	jbe	@74@38
	fld	qword ptr [bp-64]
	fcomp	dword ptr DGROUP:s@+1766
	fstsw	word ptr [bp-158]
	fwait	
	mov	ax,word ptr [bp-158]
	sahf	
	jae	@74@38
	fld	qword ptr [bp-112]
	fmul	qword ptr [bp-112]
	fld	qword ptr [bp-120]
	fmul	qword ptr [bp-120]
	fadd	
	fstp	qword ptr [bp-72]
	fld	qword ptr [bp-72]
	fcomp	qword ptr [bp-144]
	fstsw	word ptr [bp-158]
	fwait	
	mov	ax,word ptr [bp-158]
	sahf	
	jae	@74@38
	fld	qword ptr [bp-72]
	fcomp	qword ptr [bp-152]
	fstsw	word ptr [bp-158]
	fwait	
	mov	ax,word ptr [bp-158]
	sahf	
	jbe	short @74@27
	fld	qword ptr [bp-72]
	sub	sp,8
	fstp	qword ptr [bp-168]
	fwait	
	call	far ptr _sqrt
	add	sp,8
	fsub	qword ptr [bp-32]
	fmul	qword ptr [bp-48]
	fsubr	dword ptr DGROUP:s@+1754
	call	far ptr F_FTOL@
	mov	byte ptr [bp-155],al
	jmp	short @74@28
@74@27:
	mov	byte ptr [bp-155],63
@74@28:
	fld	qword ptr [bp-64]
	call	far ptr F_FTOL@
	add	ax,ax
	mov	bx,ax
	mov	ax,word ptr DGROUP:_riga[bx]
	fld	qword ptr [bp-56]
	push	ax
	call	far ptr F_FTOL@
	pop	dx
	add	dx,ax
	mov	word ptr [bp-154],dx
	les	bx,dword ptr [bp+6]
	add	bx,word ptr [bp-154]
	mov	al,byte ptr es:[bx]
	add	al,byte ptr [bp-155]
	mov	byte ptr [bp-155],al
	cbw	
	cmp	ax,63
	jle	short @74@33
	mov	 di, [bp-154]
	db	 064H, 0C7H, 045H, 004H, 03FH, 03FH
	db	 064H, 0C7H, 085H, 044H, 001H, 03FH, 03FH
	jmp	short @74@38
@74@33:
	mov	 al, [bp-155]
	mov	 di, [bp-154]
	mov	 ah, al
	db	 064H, 089H, 045H, 004H
	db	 064H, 089H, 085H, 044H, 001H
@74@38:
	fld	dword ptr DGROUP:s@+12
	fadd	qword ptr [bp-112]
	fstp	qword ptr [bp-112]
	fld	dword ptr DGROUP:s@+12
	fadd	qword ptr [bp-56]
	fstp	qword ptr [bp-56]
@74@39:
	fwait	
	fld	qword ptr [bp-56]
	fcomp	qword ptr [bp-128]
	fstsw	word ptr [bp-158]
	fwait	
	mov	ax,word ptr [bp-158]
	sahf	
	jb	@74@20
	fld	qword ptr DGROUP:s@+1770
	fadd	qword ptr [bp-120]
	fstp	qword ptr [bp-120]
	fld	dword ptr DGROUP:s@+12
	fadd	qword ptr [bp-64]
	fstp	qword ptr [bp-64]
@74@42:
	fwait	
	fld	qword ptr [bp-64]
	fcomp	qword ptr [bp-136]
	fstsw	word ptr [bp-158]
	fwait	
	mov	ax,word ptr [bp-158]
	sahf	
	jb	@74@19
@74@44:
	pop	di
	leave	
	ret	
@whiteglobe$qnucdddff	endp
NOCTIS-0_TEXT	ends
_BSS	segment word public use16 'BSS'
_xsun_onscreen	label	qword
	db	8 dup (?)
_BSS	ends
NOCTIS-0_TEXT	segment byte public use16 'CODE'
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@whitesun$qnucdddff	proc	far
	push	bp
	mov	bp,sp
	sub	sp,164
	push	si
	push	di
	fld	qword ptr [bp+10]
	fsub	qword ptr DGROUP:_dzat_x
	fstp	qword ptr [bp-56]
	fld	qword ptr [bp+18]
	fsub	qword ptr DGROUP:_dzat_y
	fstp	qword ptr [bp-64]
	fld	qword ptr [bp+26]
	fsub	qword ptr DGROUP:_dzat_z
	fstp	qword ptr [bp-72]
	fld	dword ptr DGROUP:_opt_pcosbeta
	fmul	qword ptr [bp-56]
	fld	dword ptr DGROUP:_opt_psinbeta
	fmul	qword ptr [bp-72]
	fadd	
	fstp	qword ptr [bp-88]
	fld	dword ptr DGROUP:_opt_tcosbeta
	fmul	qword ptr [bp-72]
	fld	dword ptr DGROUP:_opt_tsinbeta
	fmul	qword ptr [bp-56]
	fsub	
	fstp	qword ptr [bp-80]
	fld	dword ptr DGROUP:_opt_tcosalfa
	fmul	qword ptr [bp-80]
	fld	dword ptr DGROUP:_opt_tsinalfa
	fmul	qword ptr [bp-64]
	fadd	
	fstp	qword ptr [bp-104]
	fld	dword ptr DGROUP:_opt_pcosalfa
	fmul	qword ptr [bp-64]
	fld	dword ptr DGROUP:_opt_psinalfa
	fmul	qword ptr [bp-80]
	fsub	
	fstp	qword ptr [bp-96]
	fld	qword ptr [bp-104]
	fcomp	qword ptr DGROUP:s@+1542
	fstsw	word ptr [bp-156]
	fwait	
	mov	ax,word ptr [bp-156]
	sahf	
	jb	@75@31
	fld	dword ptr [bp+34]
	fdiv	qword ptr [bp-104]
	fstp	dword ptr [bp+34]
	fld	dword ptr [bp+34]
	fcomp	qword ptr DGROUP:s@+1714
	fstsw	word ptr [bp-156]
	fwait	
	mov	ax,word ptr [bp-156]
	sahf	
	jbe	short @75@4
	mov	dword ptr [bp+34],large 0403F5C29h
@75@4:
	fld	dword ptr [bp+34]
	fcomp	qword ptr DGROUP:s@+1602
	fstsw	word ptr [bp-156]
	fwait	
	mov	ax,word ptr [bp-156]
	sahf	
	jae	short @75@6
	mov	dword ptr [bp+34],large 03C23D70Ah
@75@6:
	fld	qword ptr [bp-104]
	fdivr	qword ptr [bp-88]
	fstp	qword ptr [bp-88]
	fld	qword ptr [bp-104]
	fdivr	qword ptr [bp-96]
	fstp	qword ptr [bp-96]
	fld	dword ptr DGROUP:_x_centro_f
	fadd	qword ptr [bp-88]
	fst	qword ptr [bp-164]
	fstp	qword ptr DGROUP:_xsun_onscreen
	fld	qword ptr [bp-88]
	fcomp	qword ptr DGROUP:s@+1722
	fstsw	word ptr [bp-156]
	fwait	
	mov	ax,word ptr [bp-156]
	sahf	
	jb	@75@31
	fld	qword ptr [bp-88]
	fcomp	dword ptr DGROUP:s@+1730
	fstsw	word ptr [bp-156]
	fwait	
	mov	ax,word ptr [bp-156]
	sahf	
	ja	@75@31
	fld	qword ptr [bp-96]
	fcomp	qword ptr DGROUP:s@+1734
	fstsw	word ptr [bp-156]
	fwait	
	mov	ax,word ptr [bp-156]
	sahf	
	jb	@75@31
	fld	qword ptr [bp-96]
	fcomp	dword ptr DGROUP:s@+1742
	fstsw	word ptr [bp-156]
	fwait	
	mov	ax,word ptr [bp-156]
	sahf	
	ja	@75@31
	fld	qword ptr [bp-164]
	fadd	dword ptr DGROUP:s@+1582
	fstp	qword ptr [bp-8]
	fld	dword ptr DGROUP:_y_centro_f
	fadd	qword ptr [bp-96]
	fadd	dword ptr DGROUP:s@+1582
	fstp	qword ptr [bp-16]
	fld	dword ptr [bp+34]
	fmul	dword ptr DGROUP:s@+1746
	fadd	dword ptr DGROUP:s@+1750
	fstp	qword ptr [bp-24]
	fld	dword ptr [bp+38]
	fmul	qword ptr [bp-24]
	fstp	qword ptr [bp-32]
	fld	qword ptr [bp-24]
	fsub	qword ptr [bp-32]
	fstp	qword ptr [bp-40]
	fld	qword ptr [bp-40]
	fld1	
	fcompp
	fstsw	word ptr [bp-156]
	fwait	
	mov	ax,word ptr [bp-156]
	sahf	
	jbe	short @75@12
	fld1	
	fstp	qword ptr [bp-40]
	fwait	
@75@12:
	fld	dword ptr DGROUP:s@+1754
	fdiv	qword ptr [bp-40]
	fstp	qword ptr [bp-48]
	fld	qword ptr [bp-24]
	fmul	qword ptr [bp-24]
	fstp	qword ptr [bp-144]
	fld	qword ptr [bp-32]
	fmul	qword ptr [bp-32]
	fstp	qword ptr [bp-152]
	fld	qword ptr [bp-24]
	fchs	
	fmul	qword ptr DGROUP:s@+1674
	fstp	qword ptr [bp-120]
	fld	qword ptr [bp-16]
	fadd	qword ptr [bp-24]
	fstp	qword ptr [bp-136]
	fld	qword ptr [bp-16]
	fsub	qword ptr [bp-24]
	fstp	qword ptr [bp-64]
	jmp	@75@29
@75@13:
	fld	qword ptr [bp-24]
	fchs	
	fstp	qword ptr [bp-112]
	fld	qword ptr [bp-8]
	fadd	qword ptr [bp-24]
	fstp	qword ptr [bp-128]
	fld	qword ptr [bp-8]
	fsub	qword ptr [bp-24]
	fstp	qword ptr [bp-56]
	jmp	@75@26
@75@14:
	fld	qword ptr [bp-56]
	fcomp	dword ptr DGROUP:s@+1758
	fstsw	word ptr [bp-156]
	fwait	
	mov	ax,word ptr [bp-156]
	sahf	
	jbe	@75@25
	fld	qword ptr [bp-56]
	fcomp	dword ptr DGROUP:s@+1762
	fstsw	word ptr [bp-156]
	fwait	
	mov	ax,word ptr [bp-156]
	sahf	
	jae	@75@25
	fld	qword ptr [bp-64]
	fcomp	dword ptr DGROUP:s@+1758
	fstsw	word ptr [bp-156]
	fwait	
	mov	ax,word ptr [bp-156]
	sahf	
	jbe	@75@25
	fld	qword ptr [bp-64]
	fcomp	dword ptr DGROUP:s@+1766
	fstsw	word ptr [bp-156]
	fwait	
	mov	ax,word ptr [bp-156]
	sahf	
	jae	@75@25
	fld	qword ptr [bp-112]
	fmul	qword ptr [bp-112]
	fld	qword ptr [bp-120]
	fmul	qword ptr [bp-120]
	fadd	
	fstp	qword ptr [bp-72]
	fld	qword ptr [bp-72]
	fcomp	qword ptr [bp-144]
	fstsw	word ptr [bp-156]
	fwait	
	mov	ax,word ptr [bp-156]
	sahf	
	jae	@75@25
	fld	qword ptr [bp-72]
	fcomp	qword ptr [bp-152]
	fstsw	word ptr [bp-156]
	fwait	
	mov	ax,word ptr [bp-156]
	sahf	
	jbe	short @75@21
	fld	qword ptr [bp-72]
	sub	sp,8
	fstp	qword ptr [bp-176]
	fwait	
	call	far ptr _sqrt
	add	sp,8
	fsub	qword ptr [bp-32]
	fmul	qword ptr [bp-48]
	fsubr	dword ptr DGROUP:s@+1754
	call	far ptr F_FTOL@
	mov	byte ptr [bp-153],al
	jmp	short @75@22
@75@21:
	mov	byte ptr [bp-153],63
@75@22:
	fld	qword ptr [bp-64]
	call	far ptr F_FTOL@
	add	ax,ax
	mov	bx,ax
	mov	ax,word ptr DGROUP:_riga[bx]
	fld	qword ptr [bp-56]
	push	ax
	call	far ptr F_FTOL@
	pop	dx
	add	dx,ax
	mov	di,dx
	les	bx,dword ptr [bp+6]
	add	bx,di
	mov	si,bx
	mov	al,byte ptr es:[bx]
	add	al,byte ptr [bp-153]
	mov	byte ptr [bp-153],al
	cbw	
	cmp	ax,63
	jle	short @75@24
	mov	byte ptr es:[si],63
	jmp	short @75@25
@75@24:
	mov	es,word ptr [bp+8]
	mov	al,byte ptr [bp-153]
	mov	byte ptr es:[si],al
@75@25:
	fld1	
	fadd	qword ptr [bp-112]
	fstp	qword ptr [bp-112]
	fld1	
	fadd	qword ptr [bp-56]
	fstp	qword ptr [bp-56]
@75@26:
	fwait	
	fld	qword ptr [bp-56]
	fcomp	qword ptr [bp-128]
	fstsw	word ptr [bp-156]
	fwait	
	mov	ax,word ptr [bp-156]
	sahf	
	jb	@75@14
	fld	qword ptr DGROUP:s@+1674
	fadd	qword ptr [bp-120]
	fstp	qword ptr [bp-120]
	fld1	
	fadd	qword ptr [bp-64]
	fstp	qword ptr [bp-64]
@75@29:
	fwait	
	fld	qword ptr [bp-64]
	fcomp	qword ptr [bp-136]
	fstsw	word ptr [bp-156]
	fwait	
	mov	ax,word ptr [bp-156]
	sahf	
	jb	@75@13
@75@31:
	pop	di
	pop	si
	leave	
	ret	
@whitesun$qnucdddff	endp
NOCTIS-0_TEXT	ends
NOCTIS-05_DATA	segment para public use16 'FAR_DATA'
_lft_sin	label	dword
	db	1444 dup (?)
_lft_cos	label	dword
	db	1444 dup (?)
NOCTIS-05_DATA	ends
NOCTIS-0_TEXT	segment byte public use16 'CODE'
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@lens_flares_init$qv	proc	far
	push	bp
	mov	bp,sp
	sub	sp,16
	push	si
	push	di
	fldz	
	fstp	qword ptr [bp-8]
	fld	qword ptr DGROUP:s@+1778
	fstp	qword ptr [bp-16]
	mov	ax,offset _lft_sin
	or	ax,seg _lft_sin
	fwait	
	je	short @76@3
	mov	ax,offset _lft_cos
	or	ax,seg _lft_cos
	jne	short @76@4
@76@3:
	mov	al,0
	jmp	short @76@11
@76@4:
	xor	di,di
	xor	si,si
@76@6:
	fld	qword ptr [bp-8]
	sub	sp,8
	fstp	qword ptr [bp-28]
	fwait	
	call	far ptr _cos
	add	sp,8
	mov	ax,seg _lft_cos
	mov	es,ax
	fstp	dword ptr es:_lft_cos[si]
	fld	qword ptr [bp-8]
	sub	sp,8
	fstp	qword ptr [bp-28]
	fwait	
	call	far ptr _sin
	add	sp,8
	mov	ax,seg _lft_sin
	mov	es,ax
	fstp	dword ptr es:_lft_sin[si]
	fld	qword ptr [bp-16]
	fadd	qword ptr [bp-8]
	fstp	qword ptr [bp-8]
	fwait	
	add	si,4
	inc	di
	cmp	si,1444
	jne	short @76@6
	mov	al,1
@76@11:
	pop	di
	pop	si
	leave	
	ret	
@lens_flares_init$qv	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@lens_flares_for$qdddddddiccii	proc	far
	push	bp
	mov	bp,sp
	sub	sp,114
	push	si
	push	di
	fld	dword ptr DGROUP:s@+1534
	fdiv	qword ptr [bp+54]
	fstp	qword ptr [bp-8]
	fld1	
	fstp	qword ptr [bp-16]
	fld	dword ptr DGROUP:s@+1750
	fstp	qword ptr [bp-24]
	push	1
	fwait	
	push	cs
	call	near ptr @setfx$qc
	add	sp,2
	fld	qword ptr [bp+30]
	fsub	qword ptr [bp+6]
	fstp	qword ptr [bp-32]
	fld	qword ptr [bp+38]
	fsub	qword ptr [bp+14]
	fstp	qword ptr [bp-40]
	fld	qword ptr [bp+46]
	fsub	qword ptr [bp+22]
	fstp	qword ptr [bp-48]
	fld	dword ptr DGROUP:_opt_pcosbeta
	fmul	qword ptr [bp-32]
	fld	dword ptr DGROUP:_opt_psinbeta
	fmul	qword ptr [bp-48]
	fadd	
	fstp	qword ptr [bp-64]
	fld	dword ptr DGROUP:_opt_tcosbeta
	fmul	qword ptr [bp-48]
	fld	dword ptr DGROUP:_opt_tsinbeta
	fmul	qword ptr [bp-32]
	fsub	
	fstp	qword ptr [bp-56]
	fld	dword ptr DGROUP:_opt_tcosalfa
	fmul	qword ptr [bp-56]
	fld	dword ptr DGROUP:_opt_tsinalfa
	fmul	qword ptr [bp-40]
	fadd	
	fstp	qword ptr [bp-80]
	fld	dword ptr DGROUP:_opt_pcosalfa
	fmul	qword ptr [bp-40]
	fld	dword ptr DGROUP:_opt_psinalfa
	fmul	qword ptr [bp-56]
	fsub	
	fstp	qword ptr [bp-72]
	fld	qword ptr [bp-80]
	fld1	
	fcompp
	fstsw	word ptr [bp-112]
	fwait	
	mov	ax,word ptr [bp-112]
	sahf	
	jae	@77@33
	fld	qword ptr [bp+54]
	fldz	
	fcompp
	fstsw	word ptr [bp-112]
	fwait	
	mov	ax,word ptr [bp-112]
	sahf	
	jbe	short @77@4
	fld	qword ptr [bp+54]
	fchs	
	fdiv	qword ptr [bp-80]
	jmp	short @77@5
@77@4:
	fld	dword ptr DGROUP:s@+1534
	fdiv	qword ptr [bp+54]
@77@5:
	fstp	qword ptr [bp-8]
	fwait	
	fld	qword ptr [bp-64]
	fdiv	qword ptr [bp-80]
	mov	ax,word ptr [bp+68]
	mov	word ptr [bp-112],ax
	fild	word ptr [bp-112]
	fadd	
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	dword ptr [bp-84],eax
	fld	qword ptr [bp-72]
	fdiv	qword ptr [bp-80]
	mov	ax,word ptr [bp+70]
	mov	word ptr [bp-112],ax
	fild	word ptr [bp-112]
	fadd	
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	dword ptr [bp-88],eax
	cmp	dword ptr [bp-84],large -150
	jle	@77@33
	cmp	dword ptr [bp-88],large -90
	jle	@77@33
	cmp	dword ptr [bp-84],large 160
	jge	@77@33
	cmp	dword ptr [bp-88],large 90
	jge	@77@33
	mov	al,byte ptr [bp+66]
	cbw	
	cmp	ax,1
	je	short @77@14
	cmp	ax,2
	je	short @77@16
	jmp	short @77@18
@77@14:
	mov	bx,word ptr [bp-88]
	add	bx,bx
	mov	bx,word ptr DGROUP:_riga[bx+200]
	add	bx,word ptr [bp-84]
	mov	es,word ptr DGROUP:_adapted+2
	add	bx,word ptr DGROUP:_adapted
	mov	al,byte ptr es:[bx+158]
	mov	byte ptr [bp-105],al
	cmp	byte ptr [bp-105],64
	jae	short @77@18
	jmp	@77@33
@77@16:
	mov	bx,word ptr [bp-88]
	add	bx,bx
	mov	bx,word ptr DGROUP:_riga[bx+200]
	add	bx,word ptr [bp-84]
	mov	es,word ptr DGROUP:_adapted+2
	add	bx,word ptr DGROUP:_adapted
	mov	al,byte ptr es:[bx+158]
	mov	byte ptr [bp-105],al
	cmp	byte ptr [bp-105],64
	jb	@77@33
	cmp	byte ptr [bp-105],127
	ja	@77@33
@77@18:
	mov	word ptr [bp-108],0
	xor	di,di
	mov	ax,word ptr [bp+62]
	mov	dx,4
	imul	dx
	mov	word ptr [bp-114],ax
@77@21:
	mov	ax,seg _lft_cos
	mov	es,ax
	fld	dword ptr es:_lft_cos[di]
	fmul	qword ptr [bp-8]
	fmul	qword ptr [bp-16]
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	dword ptr [bp-92],eax
	mov	ax,seg _lft_sin
	mov	es,ax
	fld	dword ptr es:_lft_sin[di]
	fmul	qword ptr [bp-8]
	fmul	qword ptr [bp-16]
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	dword ptr [bp-96],eax
	mov	eax,dword ptr [bp-88]
	add	eax,dword ptr [bp-96]
	push	eax
	mov	eax,dword ptr [bp-84]
	add	eax,dword ptr [bp-92]
	push	eax
	mov	eax,dword ptr [bp-88]
	sub	eax,dword ptr [bp-96]
	push	eax
	mov	eax,dword ptr [bp-84]
	sub	eax,dword ptr [bp-92]
	push	eax
	push	cs
	call	near ptr @fline$qllll
	add	sp,16
	cmp	byte ptr [bp+64],0
	je	@77@27
	mov	ax,word ptr [bp-108]
	mov	bx,8
	cwd	
	idiv	bx
	or	dx,dx
	jne	@77@27
	mov	ebx,large 10
	mov	eax,dword ptr [bp-92]
	cdq	
	idiv	ebx
	mov	dword ptr [bp-92],eax
	mov	eax,dword ptr [bp-96]
	cdq	
	idiv	ebx
	mov	dword ptr [bp-96],eax
	mov	eax,dword ptr [bp-84]
	mov	dword ptr [bp-112],eax
	fild	dword ptr [bp-112]
	fmul	qword ptr DGROUP:s@+1786
	fstp	dword ptr [bp-100]
	fwait	
	mov	eax,dword ptr [bp-88]
	mov	dword ptr [bp-112],eax
	fild	dword ptr [bp-112]
	fmul	qword ptr DGROUP:s@+1786
	fstp	dword ptr [bp-104]
	xor	si,si
	fwait	
@77@24:
	mov	eax,dword ptr [bp-96]
	mov	dword ptr [bp-112],eax
	fild	dword ptr [bp-112]
	fadd	dword ptr [bp-104]
	call	far ptr F_FTOL@
	push	dx
	push	ax
	mov	eax,dword ptr [bp-92]
	mov	dword ptr [bp-112],eax
	fild	dword ptr [bp-112]
	fadd	dword ptr [bp-100]
	call	far ptr F_FTOL@
	push	dx
	push	ax
	mov	eax,dword ptr [bp-96]
	mov	dword ptr [bp-112],eax
	fild	dword ptr [bp-112]
	fsubr	dword ptr [bp-104]
	call	far ptr F_FTOL@
	push	dx
	push	ax
	mov	eax,dword ptr [bp-92]
	mov	dword ptr [bp-112],eax
	fild	dword ptr [bp-112]
	fsubr	dword ptr [bp-100]
	call	far ptr F_FTOL@
	push	dx
	push	ax
	push	cs
	call	near ptr @fline$qllll
	add	sp,16
	mov	eax,dword ptr [bp-92]
	imul	eax,large 4
	mov	dword ptr [bp-92],eax
	mov	eax,dword ptr [bp-96]
	imul	eax,large 4
	mov	dword ptr [bp-96],eax
	fld	dword ptr DGROUP:s@+1794
	fmul	dword ptr [bp-100]
	fstp	dword ptr [bp-100]
	fld	dword ptr DGROUP:s@+1794
	fmul	dword ptr [bp-104]
	fstp	dword ptr [bp-104]
	fwait	
	inc	si
	cmp	si,3
	jl	@77@24
@77@27:
	fld	qword ptr [bp-24]
	fmul	qword ptr [bp-16]
	fstp	qword ptr [bp-16]
	fld	qword ptr [bp-16]
	fcomp	dword ptr DGROUP:s@+1794
	fstsw	word ptr [bp-112]
	fwait	
	mov	ax,word ptr [bp-112]
	sahf	
	ja	short @77@29
	fld	qword ptr [bp-16]
	fld1	
	fcompp
	fstsw	word ptr [bp-112]
	fwait	
	mov	ax,word ptr [bp-112]
	sahf	
	jbe	short @77@30
@77@29:
	fld1	
	fdiv	qword ptr [bp-24]
	fstp	qword ptr [bp-24]
	fwait	
@77@30:
	add	di,word ptr [bp-114]
	mov	ax,word ptr [bp+62]
	add	word ptr [bp-108],ax
	cmp	word ptr [bp-108],180
	jl	@77@21
@77@33:
	push	cs
	call	near ptr @resetfx$qv
	pop	di
	pop	si
	leave	
	ret	
@lens_flares_for$qdddddddiccii	endp
NOCTIS-0_TEXT	ends
_DATA	segment word public use16 'DATA'
	db	1 dup (0)
_pix_dst_scale	label	qword
	db	250
	db	126
	db	106
	db	188
	db	116
	db	147
	db	216
	db	63
_pix_rad_scale	label	qword
	db	51
	db	51
	db	51
	db	51
	db	51
	db	51
	db	147
	db	64
_pixilating_effect	label	byte
	db	0
_pixel_spreads	label	byte
	db	1
_multicolourmask	label	byte
	db	192
_DATA	ends
NOCTIS-0_TEXT	segment byte public use16 'CODE'
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@single_pixel_at_ptr$quiuc	proc	far
	push	bp
	mov	bp,sp
	sub	sp,6
	mov	ax,word ptr DGROUP:_adapted+2
	mov	dx,word ptr DGROUP:_adapted
	add	dx,word ptr [bp+6]
	mov	word ptr [bp-2],ax
	mov	word ptr [bp-4],dx
	les	bx,dword ptr [bp-4]
	mov	al,byte ptr es:[bx]
	mov	byte ptr [bp-6],al
	mov	cl,al
	and	cl,63
	add	cl,byte ptr [bp+8]
	mov	al,byte ptr DGROUP:_pixilating_effect
	cbw	
	or	ax,ax
	je	short @78@7
	cmp	ax,1
	je	short @78@11
	cmp	ax,2
	je	short @78@14
	leave	
	ret	
@78@7:
	les	bx,dword ptr [bp-4]
	cmp	byte ptr es:[bx],63
	jbe	short @78@16
	mov	al,byte ptr [bp-6]
	mov	byte ptr [bp-5],al
	and	byte ptr [bp-5],192
	cmp	cl,62
	jbe	short @78@10
	mov	cl,62
@78@10:
	or	cl,byte ptr [bp-5]
	les	bx,dword ptr [bp-4]
	mov	byte ptr es:[bx],cl
	leave	
	ret	
@78@11:
	les	bx,dword ptr [bp-4]
	cmp	byte ptr es:[bx],63
	jbe	short @78@16
	mov	al,byte ptr [bp-6]
	mov	byte ptr [bp-5],al
@78@13:
	and	byte ptr [bp-5],192
	shr	cl,1
	or	cl,byte ptr [bp-5]
	les	bx,dword ptr [bp-4]
	mov	byte ptr es:[bx],cl
	leave	
	ret	
@78@14:
	les	bx,dword ptr [bp-4]
	cmp	byte ptr es:[bx],63
	jbe	short @78@16
	mov	al,byte ptr DGROUP:_multicolourmask
	mov	byte ptr [bp-5],al
	jmp	short @78@13
@78@16:
	leave	
	ret	
@single_pixel_at_ptr$quiuc	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@far_pixel_at$qdddduc	proc	far
	push	bp
	mov	bp,sp
	sub	sp,50
	fld	qword ptr [bp+6]
	fsub	qword ptr DGROUP:_dzat_x
	fstp	qword ptr [bp-8]
	fld	qword ptr [bp+14]
	fsub	qword ptr DGROUP:_dzat_y
	fstp	qword ptr [bp-16]
	fld	qword ptr [bp+22]
	fsub	qword ptr DGROUP:_dzat_z
	fstp	qword ptr [bp-24]
	fld	dword ptr DGROUP:_opt_pcosbeta
	fmul	qword ptr [bp-8]
	fld	dword ptr DGROUP:_opt_psinbeta
	fmul	qword ptr [bp-24]
	fadd	
	fstp	qword ptr DGROUP:_pxx
	fld	dword ptr DGROUP:_opt_tcosbeta
	fmul	qword ptr [bp-24]
	fld	dword ptr DGROUP:_opt_tsinbeta
	fmul	qword ptr [bp-8]
	fsub	
	fstp	qword ptr [bp-32]
	fld	dword ptr DGROUP:_opt_tcosalfa
	fmul	qword ptr [bp-32]
	fld	dword ptr DGROUP:_opt_tsinalfa
	fmul	qword ptr [bp-16]
	fadd	
	fstp	qword ptr [bp-40]
	fld	dword ptr DGROUP:_opt_pcosalfa
	fmul	qword ptr [bp-16]
	fld	dword ptr DGROUP:_opt_psinalfa
	fmul	qword ptr [bp-32]
	fsub	
	fstp	qword ptr DGROUP:_pyy
	fld	qword ptr [bp-40]
	fcomp	qword ptr DGROUP:s@+1542
	fstsw	word ptr [bp-50]
	fwait	
	mov	ax,word ptr [bp-50]
	sahf	
	jbe	@79@26
	cmp	byte ptr [bp+38],0
	jne	short @79@7
	fld	qword ptr [bp-40]
	fmul	qword ptr DGROUP:_pix_dst_scale
	fsubr	dword ptr DGROUP:s@+1498
	fld	qword ptr [bp+30]
	fmul	qword ptr DGROUP:_pix_rad_scale
	fadd	
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	dword ptr [bp-44],eax
	cmp	dword ptr [bp-44],large 63
	jle	short @79@5
	mov	dword ptr [bp-44],large 63
@79@5:
	cmp	dword ptr [bp-44],large 0
	jge	short @79@8
	mov	dword ptr [bp-44],large 0
	jmp	short @79@8
@79@7:
	movzx	eax,byte ptr [bp+38]
	mov	dword ptr [bp-44],eax
@79@8:
	fld	qword ptr [bp-40]
	fdivr	qword ptr DGROUP:_pxx
	fstp	qword ptr DGROUP:_pxx
	fld	dword ptr DGROUP:s@+1798
	fadd	qword ptr DGROUP:_pxx
	fstp	qword ptr DGROUP:_pxx
	fld	qword ptr [bp-40]
	fdivr	qword ptr DGROUP:_pyy
	fstp	qword ptr DGROUP:_pyy
	fld	dword ptr DGROUP:s@+1746
	fadd	qword ptr DGROUP:_pyy
	fstp	qword ptr DGROUP:_pyy
	fld	qword ptr DGROUP:_pxx
	fcomp	dword ptr DGROUP:s@+1534
	fstsw	word ptr [bp-50]
	fwait	
	mov	ax,word ptr [bp-50]
	sahf	
	jbe	@79@26
	fld	qword ptr DGROUP:_pyy
	fcomp	dword ptr DGROUP:s@+1534
	fstsw	word ptr [bp-50]
	fwait	
	mov	ax,word ptr [bp-50]
	sahf	
	jbe	@79@26
	fld	qword ptr DGROUP:_pxx
	fcomp	dword ptr DGROUP:s@+1802
	fstsw	word ptr [bp-50]
	fwait	
	mov	ax,word ptr [bp-50]
	sahf	
	jae	@79@26
	fld	qword ptr DGROUP:_pyy
	fcomp	dword ptr DGROUP:s@+1766
	fstsw	word ptr [bp-50]
	fwait	
	mov	ax,word ptr [bp-50]
	sahf	
	jae	@79@26
	fld	qword ptr DGROUP:_pyy
	call	far ptr F_FTOL@
	imul	ax,ax,320
	mov	word ptr [bp-50],ax
	fild	word ptr [bp-50]
	fadd	qword ptr DGROUP:_pxx
	call	far ptr F_FTOL@
	mov	word ptr DGROUP:_vptr,ax
	cmp	byte ptr DGROUP:_pixel_spreads,0
	je	@79@23
	mov	ax,word ptr [bp-44]
	sar	ax,1
	mov	byte ptr [bp-45],al
	mov	ax,word ptr [bp-44]
	sar	ax,2
	mov	byte ptr [bp-46],al
	mov	ax,word ptr [bp-44]
	sar	ax,3
	mov	byte ptr [bp-47],al
	mov	ax,word ptr [bp-44]
	sar	ax,4
	mov	byte ptr [bp-48],al
	cmp	byte ptr [bp-45],7
	jbe	short @79@15
	mov	al,byte ptr [bp-45]
	push	ax
	mov	ax,word ptr DGROUP:_vptr
	sub	ax,320
	push	ax
	push	cs
	call	near ptr @single_pixel_at_ptr$quiuc
	add	sp,4
	mov	al,byte ptr [bp-45]
	push	ax
	mov	ax,word ptr DGROUP:_vptr
	add	ax,320
	push	ax
	push	cs
	call	near ptr @single_pixel_at_ptr$quiuc
	add	sp,4
	mov	al,byte ptr [bp-45]
	push	ax
	mov	ax,word ptr DGROUP:_vptr
	dec	ax
	push	ax
	push	cs
	call	near ptr @single_pixel_at_ptr$quiuc
	add	sp,4
	mov	al,byte ptr [bp-45]
	push	ax
	mov	ax,word ptr DGROUP:_vptr
	inc	ax
	push	ax
	push	cs
	call	near ptr @single_pixel_at_ptr$quiuc
	add	sp,4
@79@15:
	cmp	byte ptr [bp-46],7
	jbe	short @79@17
	mov	al,byte ptr [bp-46]
	push	ax
	mov	ax,word ptr DGROUP:_vptr
	sub	ax,321
	push	ax
	push	cs
	call	near ptr @single_pixel_at_ptr$quiuc
	add	sp,4
	mov	al,byte ptr [bp-46]
	push	ax
	mov	ax,word ptr DGROUP:_vptr
	sub	ax,319
	push	ax
	push	cs
	call	near ptr @single_pixel_at_ptr$quiuc
	add	sp,4
	mov	al,byte ptr [bp-46]
	push	ax
	mov	ax,word ptr DGROUP:_vptr
	add	ax,321
	push	ax
	push	cs
	call	near ptr @single_pixel_at_ptr$quiuc
	add	sp,4
	mov	al,byte ptr [bp-46]
	push	ax
	mov	ax,word ptr DGROUP:_vptr
	add	ax,319
	push	ax
	push	cs
	call	near ptr @single_pixel_at_ptr$quiuc
	add	sp,4
@79@17:
	cmp	byte ptr [bp-47],7
	jbe	short @79@19
	mov	al,byte ptr [bp-47]
	push	ax
	mov	ax,word ptr DGROUP:_vptr
	sub	ax,640
	push	ax
	push	cs
	call	near ptr @single_pixel_at_ptr$quiuc
	add	sp,4
	mov	al,byte ptr [bp-47]
	push	ax
	mov	ax,word ptr DGROUP:_vptr
	add	ax,640
	push	ax
	push	cs
	call	near ptr @single_pixel_at_ptr$quiuc
	add	sp,4
	mov	al,byte ptr [bp-47]
	push	ax
	mov	ax,word ptr DGROUP:_vptr
	sub	ax,2
	push	ax
	push	cs
	call	near ptr @single_pixel_at_ptr$quiuc
	add	sp,4
	mov	al,byte ptr [bp-47]
	push	ax
	mov	ax,word ptr DGROUP:_vptr
	add	ax,2
	push	ax
	push	cs
	call	near ptr @single_pixel_at_ptr$quiuc
	add	sp,4
@79@19:
	cmp	byte ptr [bp-48],7
	jbe	@79@21
	mov	al,byte ptr [bp-48]
	push	ax
	mov	ax,word ptr DGROUP:_vptr
	sub	ax,641
	push	ax
	push	cs
	call	near ptr @single_pixel_at_ptr$quiuc
	add	sp,4
	mov	al,byte ptr [bp-48]
	push	ax
	mov	ax,word ptr DGROUP:_vptr
	sub	ax,639
	push	ax
	push	cs
	call	near ptr @single_pixel_at_ptr$quiuc
	add	sp,4
	mov	al,byte ptr [bp-48]
	push	ax
	mov	ax,word ptr DGROUP:_vptr
	add	ax,641
	push	ax
	push	cs
	call	near ptr @single_pixel_at_ptr$quiuc
	add	sp,4
	mov	al,byte ptr [bp-48]
	push	ax
	mov	ax,word ptr DGROUP:_vptr
	add	ax,639
	push	ax
	push	cs
	call	near ptr @single_pixel_at_ptr$quiuc
	add	sp,4
	mov	al,byte ptr [bp-48]
	push	ax
	mov	ax,word ptr DGROUP:_vptr
	sub	ax,322
	push	ax
	push	cs
	call	near ptr @single_pixel_at_ptr$quiuc
	add	sp,4
	mov	al,byte ptr [bp-48]
	push	ax
	mov	ax,word ptr DGROUP:_vptr
	sub	ax,318
	push	ax
	push	cs
	call	near ptr @single_pixel_at_ptr$quiuc
	add	sp,4
	mov	al,byte ptr [bp-48]
	push	ax
	mov	ax,word ptr DGROUP:_vptr
	add	ax,322
	push	ax
	push	cs
	call	near ptr @single_pixel_at_ptr$quiuc
	add	sp,4
	mov	al,byte ptr [bp-48]
	push	ax
	mov	ax,word ptr DGROUP:_vptr
	add	ax,318
	push	ax
	push	cs
	call	near ptr @single_pixel_at_ptr$quiuc
	add	sp,4
@79@21:
	cmp	dword ptr [bp-44],large 7
	jle	short @79@25
	jmp	short @79@24
@79@23:
	cmp	dword ptr [bp-44],large 0
	je	short @79@25
@79@24:
	mov	al,byte ptr [bp-44]
	push	ax
	push	word ptr DGROUP:_vptr
	push	cs
	call	near ptr @single_pixel_at_ptr$quiuc
	add	sp,4
@79@25:
	mov	al,1
	leave	
	ret	
@79@26:
	mov	al,0
	leave	
	ret	
@far_pixel_at$qdddduc	endp
NOCTIS-0_TEXT	ends
_DATA	segment word public use16 'DATA'
$iipcfaia	label	word
	db	0
	db	0
	db	16 dup (0)
_DATA	ends
NOCTIS-0_TEXT	segment byte public use16 'CODE'
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@getsecs$qv	proc	far
	push	bp
	mov	bp,sp
	sub	sp,30
	push	si
	push	di
	mov	si,offset DGROUP:$iipcfaia
	lea	di,word ptr [bp-30]
	push	ss
	pop	es
	mov	cx,9
	rep 	movsw	
	mov	word ptr [bp-30],0
	mov	word ptr [bp-28],0
	mov	word ptr [bp-26],0
	mov	word ptr [bp-24],1
	mov	word ptr [bp-22],0
	mov	word ptr [bp-20],84
	push	ss
	lea	ax,word ptr [bp-4]
	push	ax
	call	far ptr _time
	add	sp,4
	push	ss
	lea	ax,word ptr [bp-4]
	push	ax
	call	far ptr _localtime
	add	sp,4
	mov	word ptr [bp-6],dx
	mov	word ptr [bp-8],ax
	les	bx,dword ptr [bp-8]
	mov	al,byte ptr es:[bx]
	mov	byte ptr [bp-9],al
	push	ss
	lea	ax,word ptr [bp-30]
	push	ax
	call	far ptr _mktime
	add	sp,4
	push	dx
	push	ax
	push	dword ptr [bp-4]
	call	far ptr _difftime
	add	sp,8
	fstp	qword ptr DGROUP:_secs
	fld	dword ptr DGROUP:s@+1806
	fsubr	qword ptr DGROUP:_secs
	fstp	qword ptr DGROUP:_secs
	fwait	
	mov	al,byte ptr [bp-9]
	mov	ah,0
	mov	word ptr DGROUP:_isecs,ax
	mov	ax,word ptr DGROUP:_p_isecs
	cmp	ax,word ptr DGROUP:_isecs
	je	short @80@5
	mov	al,byte ptr DGROUP:__delay
	cbw	
	cmp	ax,10
	jl	short @80@4
	dec	byte ptr DGROUP:__delay
@80@4:
	mov	ax,word ptr DGROUP:_isecs
	mov	word ptr DGROUP:_p_isecs,ax
	mov	ax,word ptr DGROUP:_fps
	mov	word ptr DGROUP:_gl_fps,ax
	mov	word ptr DGROUP:_fps,1
	jmp	short @80@8
@80@5:
	cmp	word ptr DGROUP:_gl_fps,0
	je	short @80@7
	mov	ax,word ptr DGROUP:_fps
	mov	word ptr [bp-12],ax
	fild	word ptr [bp-12]
	mov	ax,word ptr DGROUP:_gl_fps
	mov	word ptr [bp-12],ax
	fild	word ptr [bp-12]
	fdiv	
	fadd	qword ptr DGROUP:_secs
	fstp	qword ptr DGROUP:_secs
	fwait	
@80@7:
	mov	ax,word ptr DGROUP:_fps
	mov	word ptr [bp-12],ax
	fild	word ptr [bp-12]
	mov	ax,word ptr DGROUP:_gl_fps
	mov	word ptr [bp-12],ax
	fild	word ptr [bp-12]
	fdiv	
	fstp	qword ptr DGROUP:_fsecs
	fwait	
	inc	word ptr DGROUP:_fps
@80@8:
	fld	qword ptr DGROUP:_secs
	fdiv	dword ptr DGROUP:s@+1810
	fadd	dword ptr DGROUP:s@+1814
	call	far ptr F_FTOL@
	mov	word ptr DGROUP:_epoc,ax
	pop	di
	pop	si
	leave	
	ret	
@getsecs$qv	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@extract_ap_target_infos$qv	proc	far
	push	bp
	mov	bp,sp
	sub	sp,4
	fld	qword ptr DGROUP:_ap_target_x
	fdiv	dword ptr DGROUP:s@+1598
	fmul	qword ptr DGROUP:_ap_target_y
	fdiv	dword ptr DGROUP:s@+1598
	fmul	qword ptr DGROUP:_ap_target_z
	fdiv	dword ptr DGROUP:s@+1598
	call	far ptr F_FTOL@
	push	ax
	call	far ptr _srand
	add	sp,2
	call	far ptr _rand
	cwde	
	imul	eax,large 12
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	mov	word ptr DGROUP:_ap_target_class,ax
	mov	bx,word ptr DGROUP:_ap_target_class
	add	bx,bx
	mov	ax,word ptr DGROUP:_class_rayvar[bx]
	mov	word ptr [bp-2],ax
	call	far ptr _rand
	cwde	
	movsx	edx,word ptr [bp-2]
	imul	eax,edx
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	mov	word ptr [bp-4],ax
	fild	word ptr [bp-4]
	mov	bx,word ptr DGROUP:_ap_target_class
	add	bx,bx
	mov	ax,word ptr DGROUP:_class_ray[bx]
	mov	word ptr [bp-4],ax
	fild	word ptr [bp-4]
	fadd	
	fmul	qword ptr DGROUP:s@+1542
	fstp	dword ptr DGROUP:_ap_target_ray
	fwait	
	mov	bx,word ptr DGROUP:_ap_target_class
	add	bx,bx
	add	bx,word ptr DGROUP:_ap_target_class
	mov	al,byte ptr DGROUP:_class_rgb[bx]
	mov	byte ptr DGROUP:_ap_target_r,al
	mov	bx,word ptr DGROUP:_ap_target_class
	add	bx,bx
	add	bx,word ptr DGROUP:_ap_target_class
	mov	al,byte ptr DGROUP:_class_rgb[bx+1]
	mov	byte ptr DGROUP:_ap_target_g,al
	mov	bx,word ptr DGROUP:_ap_target_class
	add	bx,bx
	add	bx,word ptr DGROUP:_ap_target_class
	mov	al,byte ptr DGROUP:_class_rgb[bx+2]
	mov	byte ptr DGROUP:_ap_target_b,al
	mov	byte ptr DGROUP:_ap_target_spin,0
	cmp	word ptr DGROUP:_ap_target_class,11
	jne	short @81@3
	call	far ptr _rand
	cwde	
	imul	eax,large 30
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	inc	al
	mov	byte ptr DGROUP:_ap_target_spin,al
@81@3:
	cmp	word ptr DGROUP:_ap_target_class,7
	jne	short @81@5
	call	far ptr _rand
	cwde	
	imul	eax,large 12
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	inc	al
	mov	byte ptr DGROUP:_ap_target_spin,al
@81@5:
	cmp	word ptr DGROUP:_ap_target_class,2
	jne	short @81@7
	call	far ptr _rand
	cwde	
	shl	eax,2
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	inc	al
	mov	byte ptr DGROUP:_ap_target_spin,al
@81@7:
	leave	
	ret	
@extract_ap_target_infos$qv	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@zrandom$qi	proc	far
	push	bp
	mov	bp,sp
	sub	sp,6
	push	si
	mov	si,word ptr [bp+6]
	mov	word ptr [bp-2],si
	call	far ptr _rand
	cwde	
	movsx	edx,word ptr [bp-2]
	imul	eax,edx
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	mov	word ptr [bp-4],si
	push	eax
	call	far ptr _rand
	cwde	
	movsx	edx,word ptr [bp-4]
	imul	eax,edx
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	pop	edx
	sub	dx,ax
	mov	word ptr [bp-6],dx
	fild	word ptr [bp-6]
	pop	si
	leave	
	ret	
@zrandom$qi	endp
NOCTIS-0_TEXT	ends
_BSS	segment word public use16 'BSS'
_smh	label	word
	db	2 dup (?)
_BSS	ends
_DATA	segment word public use16 'DATA'
	db	1 dup (0)
_idscale	label	qword
	db	241
	db	104
	db	227
	db	136
	db	181
	db	248
	db	228
	db	62
_DATA	ends
NOCTIS-0_TEXT	segment byte public use16 'CODE'
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@search_id_code$qdc	proc	far
	push	bp
	mov	bp,sp
	sub	sp,36
	push	si
	push	di
	mov	dword ptr [bp-4],large 4
	mov	byte ptr [bp-5],0
	mov	eax,dword ptr DGROUP:_p_surfacemap
	mov	dword ptr [bp-14],eax
	mov	dword ptr [bp-18],eax
	fld	qword ptr [bp+6]
	fsub	qword ptr DGROUP:_idscale
	fstp	qword ptr [bp-26]
	fld	qword ptr [bp+6]
	fadd	qword ptr DGROUP:_idscale
	fstp	qword ptr [bp-34]
	push	0
	fwait	
	push	dword ptr DGROUP:_starmap_file
	call	far ptr __rtl_open
	add	sp,6
	mov	word ptr DGROUP:_smh,ax
	cmp	word ptr DGROUP:_smh,-1
	jle	@83@15
	push	0
	push	large 4
	push	ax
	call	far ptr _lseek
	add	sp,8
	jmp	short @83@13
@83@3:
	xor	di,di
	mov	word ptr [bp-10],0
	xor	si,si
	jmp	short @83@12
@83@5:
	lea	ax,word ptr [di+29]
	les	bx,dword ptr [bp-14]
	add	bx,ax
	mov	al,byte ptr es:[bx]
	cmp	al,byte ptr [bp+14]
	jne	short @83@9
	les	bx,dword ptr [bp-18]
	add	bx,si
	fld	qword ptr es:[bx]
	fcomp	qword ptr [bp-26]
	fstsw	word ptr [bp-36]
	fwait	
	mov	ax,word ptr [bp-36]
	sahf	
	jbe	short @83@9
	les	bx,dword ptr [bp-18]
	add	bx,si
	fld	qword ptr es:[bx]
	fcomp	qword ptr [bp-34]
	fstsw	word ptr [bp-36]
	fwait	
	mov	ax,word ptr [bp-36]
	sahf	
	jae	short @83@9
	mov	byte ptr [bp-5],1
	jmp	short @83@14
@83@9:
	add	dword ptr [bp-4],large 32
	add	di,32
	add	si,32
	add	word ptr [bp-10],4
@83@12:
	cmp	di,word ptr [bp-8]
	jb	short @83@5
@83@13:
	push	-25536
	push	dword ptr [bp-14]
	push	word ptr DGROUP:_smh
	call	far ptr __rtl_read
	add	sp,8
	mov	word ptr [bp-8],ax
	or	ax,ax
	ja	@83@3
@83@14:
	push	word ptr DGROUP:_smh
	call	far ptr __rtl_close
	add	sp,2
@83@15:
	cmp	byte ptr [bp-5],0
	je	short @83@17
	mov	dx,word ptr [bp-2]
	mov	ax,word ptr [bp-4]
	jmp	short @83@18
@83@17:
	mov	dx,-1
	mov	ax,0FFFFh
@83@18:
	pop	di
	pop	si
	leave	
	ret	
@search_id_code$qdc	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@starnop$qddd	proc	far
	push	bp
	mov	bp,sp
	sub	sp,2
	push	si
	fld	qword ptr [bp+6]
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	ebx,large 10000
	cdq	
	idiv	ebx
	fld	qword ptr [bp+14]
	push	edx
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	edx,eax
	pop	eax
	imul	eax,edx
	mov	ebx,large 10000
	cdq	
	idiv	ebx
	fld	qword ptr [bp+22]
	push	edx
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	edx,eax
	pop	eax
	imul	eax,edx
	mov	ebx,large 10000
	cdq	
	idiv	ebx
	push	dx
	call	far ptr _srand
	add	sp,2
	mov	bx,word ptr DGROUP:_ap_target_class
	mov	al,byte ptr DGROUP:_class_planets[bx]
	cbw	
	inc	ax
	mov	word ptr [bp-2],ax
	call	far ptr _rand
	cwde	
	movsx	edx,word ptr [bp-2]
	imul	eax,edx
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	mov	si,ax
	call	far ptr _rand
	cwde	
	shl	eax,1
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	add	si,ax
	call	far ptr _rand
	cwde	
	shl	eax,1
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	sub	si,ax
	or	si,si
	jge	short @84@3
	xor	si,si
@84@3:
	mov	ax,si
	pop	si
	leave	
	ret	
@starnop$qddd	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@prepare_nearstar$qv	proc	far
	push	bp
	mov	bp,sp
	sub	sp,86
	push	si
	push	di
	cmp	byte ptr DGROUP:__delay,0
	jne	short @85@3
	mov	ax,word ptr DGROUP:_ap_target_class
	mov	word ptr DGROUP:_nearstar_class,ax
	fld	qword ptr DGROUP:_ap_target_x
	fstp	qword ptr DGROUP:_nearstar_x
	fld	qword ptr DGROUP:_ap_target_y
	fstp	qword ptr DGROUP:_nearstar_y
	fld	qword ptr DGROUP:_ap_target_z
	fstp	qword ptr DGROUP:_nearstar_z
	fwait	
	mov	eax,dword ptr DGROUP:_ap_target_ray
	mov	dword ptr DGROUP:_nearstar_ray,eax
	mov	al,byte ptr DGROUP:_ap_target_spin
	mov	byte ptr DGROUP:_nearstar_spin,al
	mov	al,byte ptr DGROUP:_ap_target_r
	mov	byte ptr DGROUP:_nearstar_r,al
	mov	al,byte ptr DGROUP:_ap_target_g
	mov	byte ptr DGROUP:_nearstar_g,al
	mov	al,byte ptr DGROUP:_ap_target_b
	mov	byte ptr DGROUP:_nearstar_b,al
@85@3:
	fld	dword ptr DGROUP:_nearstar_ray
	fmul	qword ptr DGROUP:s@+1558
	fmul	dword ptr DGROUP:_nearstar_ray
	fmul	dword ptr DGROUP:_nearstar_ray
	fmul	qword ptr DGROUP:s@+1818
	fstp	qword ptr DGROUP:_s_m
	fld	qword ptr DGROUP:_nearstar_x
	fdiv	dword ptr DGROUP:s@+1598
	fmul	qword ptr DGROUP:_nearstar_y
	fdiv	dword ptr DGROUP:s@+1598
	fmul	qword ptr DGROUP:_nearstar_z
	fdiv	dword ptr DGROUP:s@+1598
	fstp	qword ptr DGROUP:_nearstar_identity
	fld	qword ptr DGROUP:_nearstar_x
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	ebx,large 10000
	cdq	
	idiv	ebx
	fld	qword ptr DGROUP:_nearstar_y
	push	edx
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	edx,eax
	pop	eax
	imul	eax,edx
	mov	ebx,large 10000
	cdq	
	idiv	ebx
	fld	qword ptr DGROUP:_nearstar_z
	push	edx
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	edx,eax
	pop	eax
	imul	eax,edx
	mov	ebx,large 10000
	cdq	
	idiv	ebx
	push	dx
	call	far ptr _srand
	add	sp,2
	mov	bx,word ptr DGROUP:_nearstar_class
	mov	al,byte ptr DGROUP:_class_planets[bx]
	cbw	
	inc	ax
	mov	word ptr [bp-18],ax
	call	far ptr _rand
	cwde	
	movsx	edx,word ptr [bp-18]
	imul	eax,edx
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	mov	word ptr DGROUP:_nearstar_nop,ax
	xor	si,si
	mov	word ptr [bp-40],offset DGROUP:_nearstar_p_owner
	mov	word ptr [bp-42],0
	mov	word ptr [bp-44],offset DGROUP:_nearstar_p_orb_seed
	mov	word ptr [bp-46],offset DGROUP:_nearstar_p_orb_tilt
	mov	word ptr [bp-48],offset DGROUP:_nearstar_p_type
	jmp	@85@20
@85@5:
	mov	bx,word ptr [bp-40]
	mov	word ptr [bx],-1
	call	far ptr _rand
	cwde	
	imul	eax,large 360
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	mov	word ptr [bp-20],ax
	fild	word ptr [bp-20]
	fmul	qword ptr DGROUP:_deg
	mov	bx,word ptr [bp-42]
	fstp	qword ptr DGROUP:_nearstar_p_orb_orient[bx]
	fld	dword ptr DGROUP:s@+1826
	fmul	dword ptr DGROUP:_nearstar_ray
	call	far ptr F_FTOL@
	mov	word ptr [bp-22],ax
	call	far ptr _rand
	cwde	
	movsx	edx,word ptr [bp-22]
	imul	eax,edx
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	mov	word ptr [bp-20],ax
	fild	word ptr [bp-20]
	fdiv	dword ptr DGROUP:s@+1746
	mov	ax,si
	imul	si
	mov	dx,ax
	add	dx,dx
	add	dx,ax
	add	dx,3
	mov	word ptr [bp-20],dx
	fild	word ptr [bp-20]
	fmul	dword ptr DGROUP:_nearstar_ray
	fadd	
	mov	bx,word ptr [bp-44]
	fstp	qword ptr [bx]
	fld	qword ptr [bx]
	fmul	dword ptr DGROUP:s@+1534
	call	far ptr F_FTOL@
	push	ax
	push	cs
	call	near ptr @zrandom$qi
	add	sp,2
	fdiv	dword ptr DGROUP:s@+1830
	mov	bx,word ptr [bp-42]
	fstp	qword ptr DGROUP:_nearstar_p_tilt[bx]
	fwait	
	mov	bx,word ptr [bp-44]
	fld	qword ptr [bx]
	fmul	dword ptr DGROUP:s@+1534
	call	far ptr F_FTOL@
	push	ax
	push	cs
	call	near ptr @zrandom$qi
	add	sp,2
	fdiv	dword ptr DGROUP:s@+1834
	mov	bx,word ptr [bp-46]
	fstp	qword ptr [bx]
	fld	qword ptr [bx]
	fabs	
	fmul	dword ptr DGROUP:s@+1534
	mov	bx,word ptr [bp-44]
	fadd	qword ptr [bx]
	call	far ptr F_FTOL@
	mov	word ptr [bp-24],ax
	call	far ptr _rand
	cwde	
	movsx	edx,word ptr [bp-24]
	imul	eax,edx
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	mov	word ptr [bp-20],ax
	fild	word ptr [bp-20]
	fdiv	dword ptr DGROUP:s@+1838
	fld1	
	fsubr	
	mov	bx,word ptr [bp-42]
	fstp	qword ptr DGROUP:_nearstar_p_orb_ecc[bx]
	fwait	
	mov	bx,word ptr [bp-44]
	fld	qword ptr [bx]
	call	far ptr F_FTOL@
	mov	word ptr [bp-26],ax
	call	far ptr _rand
	cwde	
	movsx	edx,word ptr [bp-26]
	imul	eax,edx
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	mov	word ptr [bp-20],ax
	fild	word ptr [bp-20]
	fmul	qword ptr DGROUP:s@+1542
	fadd	qword ptr DGROUP:s@+1602
	mov	bx,word ptr [bp-42]
	fstp	qword ptr DGROUP:_nearstar_p_ray[bx]
	fld	qword ptr DGROUP:_nearstar_p_ray[bx]
	call	far ptr F_FTOL@
	push	ax
	push	cs
	call	near ptr @zrandom$qi
	add	sp,2
	fstp	tbyte ptr [bp-86]
	call	far ptr _rand
	cwde	
	imul	eax,large 1000
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	mov	word ptr [bp-20],ax
	fild	word ptr [bp-20]
	fdiv	dword ptr DGROUP:s@+1746
	fld1	
	fadd	
	fld	tbyte ptr [bp-86]
	fmul	
	mov	bx,word ptr [bp-42]
	fstp	qword ptr DGROUP:_nearstar_p_ring[bx]
	fwait	
	cmp	word ptr DGROUP:_nearstar_class,8
	je	short @85@7
	jmp	short @85@9
@85@7:
	call	far ptr _rand
	cwde	
	shl	eax,1
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	or	ax,ax
	je	short @85@9
	mov	bx,word ptr [bp-48]
	mov	byte ptr [bx],10
	mov	bx,word ptr [bp-46]
	fld	qword ptr [bx]
	fmul	dword ptr DGROUP:s@+1746
	mov	bx,word ptr [bp-46]
	fstp	qword ptr [bx]
	fwait	
	jmp	short @85@10
@85@9:
	call	far ptr _rand
	cwde	
	imul	eax,large 10
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	mov	bx,word ptr [bp-48]
	mov	byte ptr [bx],al
@85@10:
	cmp	word ptr DGROUP:_nearstar_class,2
	je	short @85@13
	cmp	word ptr DGROUP:_nearstar_class,7
	je	short @85@13
	cmp	word ptr DGROUP:_nearstar_class,15
	jne	short @85@14
@85@13:
	mov	bx,word ptr [bp-44]
	fld	qword ptr [bx]
	fmul	dword ptr DGROUP:s@+1534
	mov	bx,word ptr [bp-44]
	fstp	qword ptr [bx]
	fwait	
@85@14:
	add	word ptr [bp-40],2
	add	word ptr [bp-42],8
	add	word ptr [bp-44],8
	add	word ptr [bp-46],8
	inc	word ptr [bp-48]
	inc	si
@85@20:
	cmp	si,word ptr DGROUP:_nearstar_nop
	jl	@85@5
	cmp	word ptr DGROUP:_nearstar_class,0
	jne	short @85@28
	call	far ptr _rand
	cwde	
	shl	eax,2
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	cmp	ax,2
	jne	short @85@24
	mov	byte ptr DGROUP:_nearstar_p_type+2,3
@85@24:
	call	far ptr _rand
	cwde	
	shl	eax,2
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	cmp	ax,2
	jne	short @85@26
	mov	byte ptr DGROUP:_nearstar_p_type+3,3
@85@26:
	call	far ptr _rand
	cwde	
	shl	eax,2
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	cmp	ax,2
	jne	short @85@28
	mov	byte ptr DGROUP:_nearstar_p_type+4,3
@85@28:
	xor	si,si
	jmp	@85@49
@85@29:
	mov	bx,word ptr DGROUP:_nearstar_class
	sub	bx,2
	cmp	bx,9
	ja	@85@48
	add	bx,bx
	jmp	word ptr cs:@85@C375[bx]
@85@32:
	call	far ptr _rand
	cwde	
	imul	eax,large 10
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	mov	byte ptr DGROUP:_nearstar_p_type[si],al
@85@33:
	mov	al,byte ptr DGROUP:_nearstar_p_type[si]
	cbw	
	cmp	ax,3
	je	short @85@32
	jmp	@85@48
@85@35:
	call	far ptr _rand
	cwde	
	imul	eax,large 10
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	mov	byte ptr DGROUP:_nearstar_p_type[si],al
@85@36:
	mov	al,byte ptr DGROUP:_nearstar_p_type[si]
	cbw	
	cmp	ax,6
	je	short @85@35
	mov	al,byte ptr DGROUP:_nearstar_p_type[si]
	cbw	
	cmp	ax,9
	je	short @85@35
	jmp	short @85@48
@85@39:
	mov	byte ptr DGROUP:_nearstar_p_type[si],9
	jmp	short @85@48
@85@40:
	call	far ptr _rand
	cwde	
	imul	eax,large 10
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	mov	byte ptr DGROUP:_nearstar_p_type[si],al
@85@41:
	cmp	byte ptr DGROUP:_nearstar_p_type[si],0
	je	short @85@48
	mov	al,byte ptr DGROUP:_nearstar_p_type[si]
	cbw	
	cmp	ax,6
	je	short @85@48
	mov	al,byte ptr DGROUP:_nearstar_p_type[si]
	cbw	
	cmp	ax,9
	jne	short @85@40
	jmp	short @85@48
@85@45:
	call	far ptr _rand
	cwde	
	imul	eax,large 10
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	mov	byte ptr DGROUP:_nearstar_p_type[si],al
@85@46:
	mov	al,byte ptr DGROUP:_nearstar_p_type[si]
	cbw	
	cmp	ax,1
	je	short @85@48
	mov	al,byte ptr DGROUP:_nearstar_p_type[si]
	cbw	
	cmp	ax,7
	jne	short @85@45
@85@48:
	inc	si
@85@49:
	cmp	si,word ptr DGROUP:_nearstar_nop
	jl	@85@29
	xor	si,si
	mov	word ptr [bp-50],offset DGROUP:_nearstar_p_type
	jmp	@85@71
@85@52:
	mov	bx,word ptr [bp-50]
	mov	al,byte ptr [bx]
	cbw	
	or	ax,ax
	je	short @85@57
	cmp	ax,3
	je	short @85@59
	cmp	ax,7
	je	short @85@65
	jmp	@85@69
@85@57:
	call	far ptr _rand
	cwde	
	shl	eax,3
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	or	ax,ax
	je	short @85@69
	jmp	short @85@64
@85@59:
	cmp	si,2
	jl	short @85@63
	cmp	si,6
	jg	short @85@63
	cmp	word ptr DGROUP:_nearstar_class,0
	je	short @85@69
	call	far ptr _rand
	cwde	
	shl	eax,2
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	or	ax,ax
	je	short @85@69
@85@63:
	call	far ptr _rand
	cwde	
	shl	eax,1
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	or	ax,ax
	je	short @85@67
@85@64:
	mov	bx,word ptr [bp-50]
	inc	byte ptr [bx]
	jmp	short @85@69
@85@65:
	cmp	si,7
	jge	short @85@69
	call	far ptr _rand
	cwde	
	shl	eax,1
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	or	ax,ax
	je	short @85@68
@85@67:
	mov	bx,word ptr [bp-50]
	dec	byte ptr [bx]
	jmp	short @85@69
@85@68:
	mov	bx,word ptr [bp-50]
	mov	al,byte ptr [bx]
	add	al,254
	mov	byte ptr [bx],al
@85@69:
	inc	word ptr [bp-50]
	inc	si
@85@71:
	cmp	si,word ptr DGROUP:_nearstar_nop
	jl	@85@52
	mov	ax,word ptr DGROUP:_nearstar_nop
	mov	word ptr DGROUP:_nearstar_nob,ax
	cmp	word ptr DGROUP:_nearstar_class,2
	je	@85@132
	cmp	word ptr DGROUP:_nearstar_class,7
	je	@85@132
	cmp	word ptr DGROUP:_nearstar_class,15
	jne	short @85@76
	jmp	@85@132
@85@76:
	xor	si,si
	mov	word ptr [bp-52],0
	jmp	@85@131
@85@78:
	mov	al,byte ptr DGROUP:_nearstar_p_type[si]
	cbw	
	mov	word ptr [bp-6],ax
	cmp	si,2
	jge	short @85@81
	mov	word ptr [bp-8],0
	cmp	word ptr [bp-6],10
	jne	short @85@83
	call	far ptr _rand
	cwde	
	imul	eax,large 3
	jmp	short @85@82
@85@81:
	mov	bx,word ptr [bp-6]
	add	bx,bx
	mov	ax,word ptr DGROUP:_planet_possiblemoons[bx]
	inc	ax
	mov	word ptr [bp-28],ax
	call	far ptr _rand
	cwde	
	movsx	edx,word ptr [bp-28]
	imul	eax,edx
@85@82:
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	mov	word ptr [bp-8],ax
@85@83:
	mov	ax,word ptr DGROUP:_nearstar_nob
	add	ax,word ptr [bp-8]
	cmp	ax,80
	jle	short @85@85
	mov	ax,80
	sub	ax,word ptr DGROUP:_nearstar_nob
	mov	word ptr [bp-8],ax
@85@85:
	mov	word ptr [bp-2],0
	jmp	@85@127
@85@86:
	mov	ax,word ptr DGROUP:_nearstar_nob
	add	ax,word ptr [bp-2]
	mov	di,ax
	mov	bx,di
	add	bx,bx
	mov	word ptr DGROUP:_nearstar_p_owner[bx],si
	mov	al,byte ptr [bp-2]
	mov	byte ptr DGROUP:_nearstar_p_moonid[di],al
	call	far ptr _rand
	cwde	
	imul	eax,large 360
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	mov	word ptr [bp-20],ax
	fild	word ptr [bp-20]
	fmul	qword ptr DGROUP:_deg
	mov	bx,di
	shl	bx,3
	fstp	qword ptr DGROUP:_nearstar_p_orb_orient[bx]
	fwait	
	mov	bx,word ptr [bp-52]
	fld	qword ptr DGROUP:_nearstar_p_ray[bx]
	fmul	dword ptr DGROUP:s@+1826
	call	far ptr F_FTOL@
	push	ax
	push	cs
	call	near ptr @zrandom$qi
	add	sp,2
	fdiv	dword ptr DGROUP:s@+1746
	mov	ax,word ptr [bp-2]
	imul	word ptr [bp-2]
	add	ax,4
	mov	word ptr [bp-20],ax
	fild	word ptr [bp-20]
	mov	bx,word ptr [bp-52]
	fmul	qword ptr DGROUP:_nearstar_p_ray[bx]
	fadd	
	mov	bx,di
	shl	bx,3
	fstp	qword ptr DGROUP:_nearstar_p_orb_seed[bx]
	mov	bx,di
	shl	bx,3
	fld	qword ptr DGROUP:_nearstar_p_orb_seed[bx]
	fmul	dword ptr DGROUP:s@+1534
	call	far ptr F_FTOL@
	push	ax
	push	cs
	call	near ptr @zrandom$qi
	add	sp,2
	fdiv	dword ptr DGROUP:s@+1842
	mov	bx,di
	shl	bx,3
	fstp	qword ptr DGROUP:_nearstar_p_tilt[bx]
	mov	bx,di
	shl	bx,3
	fld	qword ptr DGROUP:_nearstar_p_orb_seed[bx]
	fmul	dword ptr DGROUP:s@+1534
	call	far ptr F_FTOL@
	push	ax
	push	cs
	call	near ptr @zrandom$qi
	add	sp,2
	fdiv	dword ptr DGROUP:s@+1830
	mov	bx,di
	shl	bx,3
	fstp	qword ptr DGROUP:_nearstar_p_orb_tilt[bx]
	mov	bx,di
	shl	bx,3
	fld	qword ptr DGROUP:_nearstar_p_orb_tilt[bx]
	fabs	
	fmul	dword ptr DGROUP:s@+1534
	mov	bx,di
	shl	bx,3
	fadd	qword ptr DGROUP:_nearstar_p_orb_seed[bx]
	call	far ptr F_FTOL@
	mov	word ptr [bp-30],ax
	call	far ptr _rand
	cwde	
	movsx	edx,word ptr [bp-30]
	imul	eax,edx
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	mov	word ptr [bp-20],ax
	fild	word ptr [bp-20]
	fdiv	dword ptr DGROUP:s@+1838
	fld1	
	fsubr	
	mov	bx,di
	shl	bx,3
	fstp	qword ptr DGROUP:_nearstar_p_orb_ecc[bx]
	fwait	
	mov	bx,word ptr [bp-52]
	fld	qword ptr DGROUP:_nearstar_p_orb_seed[bx]
	call	far ptr F_FTOL@
	mov	word ptr [bp-32],ax
	call	far ptr _rand
	cwde	
	movsx	edx,word ptr [bp-32]
	imul	eax,edx
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	mov	word ptr [bp-20],ax
	fild	word ptr [bp-20]
	fmul	qword ptr DGROUP:s@+1846
	fadd	qword ptr DGROUP:s@+1854
	mov	bx,di
	shl	bx,3
	fstp	qword ptr DGROUP:_nearstar_p_ray[bx]
	mov	bx,di
	shl	bx,3
	fldz	
	fstp	qword ptr DGROUP:_nearstar_p_ring[bx]
	fwait	
	call	far ptr _rand
	cwde	
	imul	eax,large 10
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	mov	byte ptr DGROUP:_nearstar_p_type[di],al
	mov	al,byte ptr DGROUP:_nearstar_p_type[di]
	cbw	
	mov	word ptr [bp-4],ax
	cmp	word ptr [bp-4],9
	jne	short @85@89
	cmp	word ptr [bp-6],10
	je	short @85@89
	mov	word ptr [bp-4],2
@85@89:
	cmp	word ptr [bp-4],6
	jne	short @85@92
	cmp	word ptr [bp-6],9
	jge	short @85@92
	mov	word ptr [bp-4],5
@85@92:
	cmp	si,7
	jle	short @85@95
	mov	ax,word ptr [bp-2]
	mov	word ptr [bp-34],ax
	call	far ptr _rand
	cwde	
	movsx	edx,word ptr [bp-34]
	imul	eax,edx
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	or	ax,ax
	je	short @85@95
	mov	word ptr [bp-4],7
@85@95:
	cmp	si,9
	jle	short @85@98
	mov	ax,word ptr [bp-2]
	mov	word ptr [bp-36],ax
	call	far ptr _rand
	cwde	
	movsx	edx,word ptr [bp-36]
	imul	eax,edx
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	or	ax,ax
	je	short @85@98
	mov	word ptr [bp-4],7
@85@98:
	cmp	word ptr [bp-4],2
	je	short @85@102
	cmp	word ptr [bp-4],3
	je	short @85@102
	cmp	word ptr [bp-4],4
	je	short @85@102
	cmp	word ptr [bp-4],8
	jne	short @85@105
@85@102:
	cmp	word ptr [bp-6],6
	je	short @85@105
	cmp	word ptr [bp-6],9
	jge	short @85@105
	mov	word ptr [bp-4],1
@85@105:
	cmp	word ptr [bp-4],3
	jne	short @85@116
	cmp	word ptr [bp-6],9
	jge	short @85@116
	cmp	si,7
	jle	short @85@109
	mov	word ptr [bp-4],7
@85@109:
	cmp	word ptr DGROUP:_nearstar_class,0
	je	short @85@112
	call	far ptr _rand
	cwde	
	shl	eax,2
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	or	ax,ax
	je	short @85@112
	mov	word ptr [bp-4],5
@85@112:
	cmp	word ptr DGROUP:_nearstar_class,2
	je	short @85@115
	cmp	word ptr DGROUP:_nearstar_class,7
	je	short @85@115
	cmp	word ptr DGROUP:_nearstar_class,11
	jne	short @85@116
@85@115:
	mov	word ptr [bp-4],8
@85@116:
	cmp	word ptr [bp-4],7
	jne	short @85@119
	cmp	si,5
	jg	short @85@119
	mov	word ptr [bp-4],1
@85@119:
	cmp	word ptr DGROUP:_nearstar_class,2
	je	short @85@123
	cmp	word ptr DGROUP:_nearstar_class,5
	je	short @85@123
	cmp	word ptr DGROUP:_nearstar_class,7
	je	short @85@123
	cmp	word ptr DGROUP:_nearstar_class,11
	jne	short @85@125
@85@123:
	mov	word ptr [bp-38],si
	call	far ptr _rand
	cwde	
	movsx	edx,word ptr [bp-38]
	imul	eax,edx
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	or	ax,ax
	je	short @85@125
	mov	word ptr [bp-4],7
@85@125:
	mov	al,byte ptr [bp-4]
	mov	byte ptr DGROUP:_nearstar_p_type[di],al
	inc	word ptr [bp-2]
@85@127:
	mov	ax,word ptr [bp-2]
	cmp	ax,word ptr [bp-8]
	jl	@85@86
	mov	ax,word ptr [bp-8]
	add	word ptr DGROUP:_nearstar_nob,ax
	add	word ptr [bp-52],8
	inc	si
@85@131:
	cmp	si,word ptr DGROUP:_nearstar_nop
	jl	@85@78
@85@132:
	fld	dword ptr DGROUP:_nearstar_ray
	fmul	qword ptr DGROUP:_planet_orb_scaling
	fstp	qword ptr [bp-16]
	fwait	
	cmp	word ptr DGROUP:_nearstar_class,8
	jne	short @85@134
	fld	dword ptr DGROUP:s@+12
	fmul	qword ptr [bp-16]
	fstp	qword ptr [bp-16]
	fwait	
@85@134:
	cmp	word ptr DGROUP:_nearstar_class,2
	jne	short @85@136
	fld	dword ptr DGROUP:s@+1862
	fmul	qword ptr [bp-16]
	fstp	qword ptr [bp-16]
	fwait	
@85@136:
	cmp	word ptr DGROUP:_nearstar_class,7
	jne	short @85@138
	fld	dword ptr DGROUP:s@+1866
	fmul	qword ptr [bp-16]
	fstp	qword ptr [bp-16]
	fwait	
@85@138:
	cmp	word ptr DGROUP:_nearstar_class,11
	jne	short @85@140
	fld	dword ptr DGROUP:s@+1870
	fmul	qword ptr [bp-16]
	fstp	qword ptr [bp-16]
	fwait	
@85@140:
	xor	si,si
	mov	word ptr [bp-54],offset DGROUP:_nearstar_p_type
	mov	word ptr [bp-56],offset DGROUP:_nearstar_p_ray
	mov	word ptr [bp-58],offset DGROUP:_nearstar_p_orb_ray
	jmp	@85@150
@85@142:
	push	100
	push	cs
	call	near ptr @zrandom$qi
	add	sp,2
	mov	bx,word ptr [bp-54]
	mov	al,byte ptr [bx]
	cbw	
	shl	ax,3
	mov	bx,ax
	fmul	qword ptr DGROUP:_avg_planet_ray[bx]
	fdiv	dword ptr DGROUP:s@+1874
	mov	bx,word ptr [bp-54]
	mov	al,byte ptr [bx]
	cbw	
	shl	ax,3
	mov	bx,ax
	fadd	qword ptr DGROUP:_avg_planet_ray[bx]
	mov	bx,word ptr [bp-56]
	fstp	qword ptr [bx]
	fld	qword ptr [bx]
	fmul	qword ptr DGROUP:_avg_planet_sizing
	mov	bx,word ptr [bp-56]
	fstp	qword ptr [bx]
	push	100
	fwait	
	push	cs
	call	near ptr @zrandom$qi
	add	sp,2
	fmul	qword ptr [bp-16]
	fdiv	dword ptr DGROUP:s@+1830
	fadd	qword ptr [bp-16]
	mov	bx,word ptr [bp-58]
	fstp	qword ptr [bx]
	fwait	
	mov	bx,word ptr [bp-54]
	mov	al,byte ptr [bx]
	cbw	
	shl	ax,3
	mov	bx,ax
	fld	qword ptr DGROUP:_avg_planet_ray[bx]
	fmul	qword ptr [bp-16]
	mov	bx,word ptr [bp-58]
	fadd	qword ptr [bx]
	fstp	qword ptr [bx]
	cmp	si,8
	fwait	
	jge	short @85@144
	fld	qword ptr [bx]
	jmp	short @85@145
@85@144:
	mov	bx,word ptr [bp-58]
	fld	qword ptr [bx]
	fmul	qword ptr DGROUP:s@+1878
@85@145:
	fadd	qword ptr [bp-16]
	fstp	qword ptr [bp-16]
	fwait	
	inc	word ptr [bp-54]
	add	word ptr [bp-56],8
	add	word ptr [bp-58],8
	inc	si
@85@150:
	cmp	si,word ptr DGROUP:_nearstar_nop
	jl	@85@142
	mov	si,word ptr DGROUP:_nearstar_nop
	mov	ax,si
	shl	ax,3
	mov	word ptr [bp-68],ax
	mov	ax,si
	add	ax,ax
	add	ax,offset DGROUP:_nearstar_p_owner
	mov	word ptr [bp-70],ax
	jmp	@85@172
@85@153:
	xor	di,di
	mov	bx,word ptr [bp-70]
	mov	ax,word ptr [bx]
	mov	word ptr [bp-2],ax
	mov	bx,word ptr [bp-2]
	shl	bx,3
	fld	qword ptr DGROUP:_nearstar_p_ray[bx]
	fmul	qword ptr DGROUP:_moon_orb_scaling
	fstp	qword ptr [bp-16]
	fwait	
	mov	ax,si
	add	ax,offset DGROUP:_nearstar_p_type
	mov	word ptr [bp-60],ax
	mov	ax,word ptr [bp-68]
	add	ax,offset DGROUP:_nearstar_p_ray
	mov	word ptr [bp-62],ax
	mov	ax,word ptr [bp-68]
	add	ax,offset DGROUP:_nearstar_p_orb_ray
	mov	word ptr [bp-64],ax
	mov	ax,word ptr [bp-70]
	mov	word ptr [bp-66],ax
	jmp	@85@170
@85@155:
	push	100
	push	cs
	call	near ptr @zrandom$qi
	add	sp,2
	mov	bx,word ptr [bp-60]
	mov	al,byte ptr [bx]
	cbw	
	shl	ax,3
	mov	bx,ax
	fmul	qword ptr DGROUP:_avg_planet_ray[bx]
	fdiv	dword ptr DGROUP:s@+1874
	mov	bx,word ptr [bp-60]
	mov	al,byte ptr [bx]
	cbw	
	shl	ax,3
	mov	bx,ax
	fadd	qword ptr DGROUP:_avg_planet_ray[bx]
	mov	bx,word ptr [bp-62]
	fstp	qword ptr [bx]
	fld	qword ptr [bx]
	fmul	qword ptr DGROUP:_avg_moon_sizing
	mov	bx,word ptr [bp-62]
	fstp	qword ptr [bx]
	push	100
	fwait	
	push	cs
	call	near ptr @zrandom$qi
	add	sp,2
	fmul	qword ptr [bp-16]
	fdiv	dword ptr DGROUP:s@+1886
	fadd	qword ptr [bp-16]
	mov	bx,word ptr [bp-64]
	fstp	qword ptr [bx]
	fwait	
	mov	bx,word ptr [bp-60]
	mov	al,byte ptr [bx]
	cbw	
	shl	ax,3
	mov	bx,ax
	fld	qword ptr DGROUP:_avg_planet_ray[bx]
	fmul	qword ptr [bp-16]
	mov	bx,word ptr [bp-64]
	fadd	qword ptr [bx]
	fstp	qword ptr [bx]
	cmp	di,2
	fwait	
	jge	short @85@157
	fld	qword ptr [bx]
	fadd	qword ptr [bp-16]
	fstp	qword ptr [bp-16]
	fwait	
@85@157:
	cmp	di,2
	jl	short @85@160
	cmp	di,8
	jge	short @85@160
	mov	bx,word ptr [bp-64]
	fld	qword ptr [bx]
	fmul	qword ptr DGROUP:s@+1890
	fadd	qword ptr [bp-16]
	fstp	qword ptr [bp-16]
	fwait	
@85@160:
	cmp	di,8
	jl	short @85@162
	mov	bx,word ptr [bp-64]
	fld	qword ptr [bx]
	fmul	qword ptr DGROUP:s@+1898
	fadd	qword ptr [bp-16]
	fstp	qword ptr [bp-16]
	fwait	
@85@162:
	inc	di
	inc	word ptr [bp-60]
	add	word ptr [bp-62],8
	add	word ptr [bp-64],8
	add	word ptr [bp-66],2
	add	word ptr [bp-68],8
	add	word ptr [bp-70],2
	inc	si
@85@170:
	cmp	si,word ptr DGROUP:_nearstar_nob
	jge	short @85@172
	mov	bx,word ptr [bp-66]
	mov	ax,word ptr [bx]
	cmp	ax,word ptr [bp-2]
	je	@85@155
@85@172:
	cmp	si,word ptr DGROUP:_nearstar_nob
	jl	@85@153
	xor	si,si
	mov	word ptr [bp-72],0
	mov	word ptr [bp-74],offset DGROUP:_nearstar_p_ring
	jmp	@85@184
@85@175:
	call	far ptr _rand
	cwde	
	imul	eax,large 3
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	add	ax,2
	mov	word ptr [bp-20],ax
	fild	word ptr [bp-20]
	mov	bx,word ptr [bp-72]
	fld	qword ptr DGROUP:_nearstar_p_ray[bx]
	fmul	dword ptr DGROUP:s@+1906
	fmul	
	mov	bx,word ptr [bp-74]
	fstp	qword ptr [bx]
	fwait	
	mov	al,byte ptr DGROUP:_nearstar_p_type[si]
	cbw	
	mov	word ptr [bp-6],ax
	cmp	word ptr [bp-6],6
	je	short @85@179
	cmp	word ptr [bp-6],9
	je	short @85@179
	call	far ptr _rand
	cwde	
	imul	eax,large 5
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	or	ax,ax
	je	short @85@181
	jmp	short @85@180
@85@179:
	call	far ptr _rand
	cwde	
	shl	eax,1
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	or	ax,ax
	je	short @85@181
@85@180:
	mov	bx,word ptr [bp-74]
	fldz	
	fstp	qword ptr [bx]
	fwait	
@85@181:
	add	word ptr [bp-72],8
	add	word ptr [bp-74],8
	inc	si
@85@184:
	cmp	si,word ptr DGROUP:_nearstar_nop
	jl	@85@175
	mov	word ptr DGROUP:_nearstar_labeled,0
	mov	si,1
	jmp	short @85@189
@85@186:
	push	80
	mov	word ptr [bp-20],si
	fild	word ptr [bp-20]
	fadd	qword ptr DGROUP:_nearstar_identity
	sub	sp,8
	fstp	qword ptr [bp-100]
	fwait	
	push	cs
	call	near ptr @search_id_code$qdc
	shl	eax,16
	shrd	eax,edx,16
	add	sp,10
	cmp	eax,large -1
	je	short @85@188
	inc	word ptr DGROUP:_nearstar_labeled
@85@188:
	inc	si
@85@189:
	cmp	si,word ptr DGROUP:_nearstar_nob
	jle	short @85@186
	xor	si,si
	mov	word ptr [bp-76],offset DGROUP:_nearstar_p_rtperiod
	jmp	short @85@195
@85@192:
	mov	bx,word ptr [bp-76]
	mov	word ptr [bx],0
	add	word ptr [bp-76],2
	inc	si
@85@195:
	cmp	si,word ptr DGROUP:_nearstar_nob
	jl	short @85@192
	pop	di
	pop	si
	leave	
	ret	
@prepare_nearstar$qv	endp
@85@C375	label	word
	dw	@85@33
	dw	@85@48
	dw	@85@48
	dw	@85@36
	dw	@85@48
	dw	@85@39
	dw	@85@48
	dw	@85@41
	dw	@85@48
	dw	@85@46
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@ssmooth$qnuc	proc	far
	push	bp
	mov	bp,sp
	sub	sp,12
	push	si
	movsx	eax,word ptr DGROUP:_QUADWORDS
	shl	eax,2
	sub	eax,large 1440
	mov	dword ptr [bp-4],eax
	mov	dword ptr [bp-8],large 0
	jmp	@86@5
@86@3:
	les	bx,dword ptr [bp+6]
	add	bx,word ptr [bp-8]
	mov	al,byte ptr es:[bx]
	mov	bx,word ptr [bp-8]
	add	bx,word ptr [bp+6]
	mov	si,bx
	add	al,byte ptr es:[bx+360]
	add	al,byte ptr es:[si+720]
	add	al,byte ptr es:[si+1080]
	mov	cl,al
	mov	al,byte ptr es:[si+1]
	add	al,byte ptr es:[si+361]
	add	al,byte ptr es:[si+721]
	add	al,byte ptr es:[si+1081]
	mov	byte ptr [bp-9],al
	mov	al,byte ptr es:[si+2]
	add	al,byte ptr es:[si+362]
	add	al,byte ptr es:[si+722]
	add	al,byte ptr es:[si+1082]
	mov	byte ptr [bp-10],al
	mov	al,byte ptr es:[si+3]
	add	al,byte ptr es:[si+363]
	add	al,byte ptr es:[si+723]
	add	al,byte ptr es:[si+1083]
	mov	byte ptr [bp-11],al
	mov	al,cl
	mov	ah,0
	and	ax,252
	mov	bx,4
	cwd	
	idiv	bx
	mov	cl,al
	mov	al,byte ptr [bp-9]
	mov	ah,0
	and	ax,252
	cwd	
	idiv	bx
	mov	byte ptr [bp-9],al
	mov	al,byte ptr [bp-10]
	mov	ah,0
	and	ax,252
	cwd	
	idiv	bx
	mov	byte ptr [bp-10],al
	mov	al,byte ptr [bp-11]
	mov	ah,0
	and	ax,252
	cwd	
	idiv	bx
	mov	byte ptr [bp-11],al
	mov	al,cl
	add	al,byte ptr [bp-9]
	add	al,byte ptr [bp-10]
	add	al,byte ptr [bp-11]
	mov	byte ptr [bp-12],al
	mov	ah,0
	cwd	
	idiv	bx
	mov	byte ptr [bp-12],al
	mov	byte ptr es:[si+360],al
	inc	dword ptr [bp-8]
@86@5:
	mov	eax,dword ptr [bp-8]
	cmp	eax,dword ptr [bp-4]
	jb	@86@3
	pop	si
	leave	
	ret	
@ssmooth$qnuc	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@lssmooth$qnuc	proc	far
	push	bp
	mov	bp,sp
	sub	sp,2
	push	di
	mov	ax,word ptr DGROUP:_QUADWORDS
	add	ax,-80
	shl	ax,2
	mov	word ptr [bp-2],ax
	pusha	
	push	 es
	mov	 cx, [bp-2]
	les	 di, dword ptr [bp+6]
@87@6:
	mov	 dx, es:[di]
	mov	 al, dl
	and	dx,16191
	mov	 bx, es:[di+360]
	add	 dl, dh
	and	bx,16191
	add	 dl, bl
	and	 al, 11000000b
	add	 dl, bh
	shr	 dl, 2
	or	 al, dl
	mov	 es:[di], al
	inc	 di
	dec	 cx
	jne	short @87@6
	pop	 es
	popa	
	pop	di
	leave	
	ret	
@lssmooth$qnuc	endp
NOCTIS-0_TEXT	ends
_BSS	segment word public use16 'BSS'
_c	label	word
	db	2 dup (?)
_gr	label	word
	db	2 dup (?)
_r	label	word
	db	2 dup (?)
_g	label	word
	db	2 dup (?)
_b	label	word
	db	2 dup (?)
_cr	label	word
	db	2 dup (?)
_cx	label	word
	db	2 dup (?)
_cy	label	word
	db	2 dup (?)
_a	label	dword
	db	4 dup (?)
_BSS	ends
_DATA	segment word public use16 'DATA'
_kfract	label	dword
	db	0
	db	0
	db	0
	db	64
_DATA	ends
_BSS	segment word public use16 'BSS'
_lave	label	byte
	db	1 dup (?)
_crays	label	byte
	db	1 dup (?)
_px	label	word
	db	2 dup (?)
_py	label	word
	db	2 dup (?)
_BSS	ends
NOCTIS-0_TEXT	segment byte public use16 'CODE'
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@spot$qv	proc	far
	push	di
   	les	 di, dword ptr DGROUP:_p_background
	add	 di, DGROUP:_py
	add	 di, DGROUP:_px
	mov	 al, es:[di]
	add	 al, byte ptr DGROUP:_gr
	cmp	 al, 03EH
	jb	short @88@9
	mov	 al, 03EH 
@88@9:
     	mov	 es:[di], al
	pop	di
	ret	
@spot$qv	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@permanent_storm$qv	proc	far
	push	bp
	mov	bp,sp
	sub	sp,2
	mov	word ptr DGROUP:_g,1
	jmp	@89@7
@89@2:
	mov	dword ptr DGROUP:_a,large 0
	jmp	@89@5
@89@3:
	fld	dword ptr DGROUP:_a
	sub	sp,8
	fstp	qword ptr [bp-10]
	fwait	
	call	far ptr _cos
	add	sp,8
	mov	ax,word ptr DGROUP:_g
	mov	word ptr [bp-2],ax
	fild	word ptr [bp-2]
	fmul	
	mov	ax,word ptr DGROUP:_cx
	mov	word ptr [bp-2],ax
	fild	word ptr [bp-2]
	fadd	
	call	far ptr F_FTOL@
	mov	word ptr DGROUP:_px,ax
	fld	dword ptr DGROUP:_a
	sub	sp,8
	fstp	qword ptr [bp-10]
	fwait	
	call	far ptr _sin
	add	sp,8
	mov	ax,word ptr DGROUP:_g
	mov	word ptr [bp-2],ax
	fild	word ptr [bp-2]
	fmul	
	mov	ax,word ptr DGROUP:_cy
	mov	word ptr [bp-2],ax
	fild	word ptr [bp-2]
	fadd	
	call	far ptr F_FTOL@
	mov	word ptr DGROUP:_py,ax
	mov	ax,360
	imul	word ptr DGROUP:_py
	mov	word ptr DGROUP:_py,ax
	push	cs
	call	near ptr @spot$qv
	fld	dword ptr DGROUP:_a
	fld	dword ptr DGROUP:s@+1910
	fmul	qword ptr DGROUP:_deg
	fadd	
	fstp	dword ptr DGROUP:_a
	fwait	
@89@5:
	fld	dword ptr DGROUP:_a
	fcomp	qword ptr DGROUP:s@+1510
	fstsw	word ptr [bp-2]
	fwait	
	mov	ax,word ptr [bp-2]
	sahf	
	jb	@89@3
	inc	word ptr DGROUP:_g
@89@7:
	mov	ax,word ptr DGROUP:_g
	cmp	ax,word ptr DGROUP:_cr
	jl	@89@2
	leave	
	ret	
@permanent_storm$qv	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@crater$qv	proc	far
	push	bp
	mov	bp,sp
	sub	sp,2
	push	si
	push	di
	mov	dword ptr DGROUP:_a,large 0
	jmp	@90@38
@90@2:
	mov	word ptr DGROUP:_gr,0
	jmp	@90@15
@90@3:
	fld	dword ptr DGROUP:_a
	sub	sp,8
	fstp	qword ptr [bp-14]
	fwait	
	call	far ptr _cos
	add	sp,8
	mov	ax,word ptr DGROUP:_gr
	mov	word ptr [bp-2],ax
	fild	word ptr [bp-2]
	fmul	
	mov	ax,word ptr DGROUP:_cx
	mov	word ptr [bp-2],ax
	fild	word ptr [bp-2]
	fadd	
	call	far ptr F_FTOL@
	mov	word ptr DGROUP:_px,ax
	fld	dword ptr DGROUP:_a
	sub	sp,8
	fstp	qword ptr [bp-14]
	fwait	
	call	far ptr _sin
	add	sp,8
	mov	ax,word ptr DGROUP:_gr
	mov	word ptr [bp-2],ax
	fild	word ptr [bp-2]
	fmul	
	mov	ax,word ptr DGROUP:_cy
	mov	word ptr [bp-2],ax
	fild	word ptr [bp-2]
	fadd	
	call	far ptr F_FTOL@
	mov	word ptr DGROUP:_py,ax
	imul	ax,ax,360
	add	ax,word ptr DGROUP:_px
	mov	word ptr DGROUP:_vptr,ax
   	les	 di, dword ptr DGROUP:_p_background
	add	 di, DGROUP:_vptr
	mov	 al, es:[di]
	mov	 ah, byte ptr DGROUP:_gr
	mov	 cl, DGROUP:_lave
	shr	 ah, cl
	sub	 al, ah
	jnc	short @90@13
	xor	 al, al 
@90@13:
     	mov	 es:[di], al
	inc	word ptr DGROUP:_gr
@90@15:
	mov	ax,word ptr DGROUP:_gr
	cmp	ax,word ptr DGROUP:_cr
	jl	@90@3
   	les	 di, dword ptr DGROUP:_p_background
	add	 di, DGROUP:_vptr
	mov	 ax, 0013EH
	mov	 es:[di], ax 
	cmp	byte ptr DGROUP:_crays,0
	je	@90@37
	mov	al,byte ptr DGROUP:_crays
	cbw	
	mov	si,ax
	call	far ptr _rand
	cwde	
	movsx	edx,si
	imul	eax,edx
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	or	ax,ax
	jne	@90@37
	call	far ptr _rand
	cwde	
	shl	eax,1
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	add	ax,2
	imul	word ptr DGROUP:_cr
	mov	word ptr DGROUP:_b,ax
	mov	ax,word ptr DGROUP:_cy
	sub	ax,word ptr DGROUP:_b
	jle	@90@37
	mov	ax,word ptr DGROUP:_cy
	add	ax,word ptr DGROUP:_b
	cmp	ax,179
	jge	@90@37
	mov	ax,word ptr DGROUP:_cr
	inc	ax
	mov	word ptr DGROUP:_gr,ax
	jmp	@90@36
@90@25:
	fld	dword ptr DGROUP:_a
	sub	sp,8
	fstp	qword ptr [bp-14]
	fwait	
	call	far ptr _cos
	add	sp,8
	mov	ax,word ptr DGROUP:_gr
	mov	word ptr [bp-2],ax
	fild	word ptr [bp-2]
	fmul	
	mov	ax,word ptr DGROUP:_cx
	mov	word ptr [bp-2],ax
	fild	word ptr [bp-2]
	fadd	
	call	far ptr F_FTOL@
	mov	word ptr DGROUP:_px,ax
	fld	dword ptr DGROUP:_a
	sub	sp,8
	fstp	qword ptr [bp-14]
	fwait	
	call	far ptr _sin
	add	sp,8
	mov	ax,word ptr DGROUP:_gr
	mov	word ptr [bp-2],ax
	fild	word ptr [bp-2]
	fmul	
	mov	ax,word ptr DGROUP:_cy
	mov	word ptr [bp-2],ax
	fild	word ptr [bp-2]
	fadd	
	call	far ptr F_FTOL@
	mov	word ptr DGROUP:_py,ax
	imul	ax,ax,360
	add	ax,word ptr DGROUP:_px
	mov	word ptr DGROUP:_vptr,ax
   	les	 di, dword ptr DGROUP:_p_background
	add	 di, DGROUP:_vptr
	mov	 al, es:[di]
	mov	 ah, byte ptr DGROUP:_cr
	add	 al, ah
	cmp	 al, 03EH
	jb	short @90@34
	mov	 al, 03EH 
@90@34:
     	mov	 es:[di], al
	inc	word ptr DGROUP:_gr
@90@36:
	mov	ax,word ptr DGROUP:_gr
	cmp	ax,word ptr DGROUP:_b
	jl	@90@25
@90@37:
	fld	dword ptr DGROUP:_a
	fld	dword ptr DGROUP:s@+1910
	fmul	qword ptr DGROUP:_deg
	fadd	
	fstp	dword ptr DGROUP:_a
	fwait	
@90@38:
	fld	dword ptr DGROUP:_a
	fcomp	qword ptr DGROUP:s@+1510
	fstsw	word ptr [bp-2]
	fwait	
	mov	ax,word ptr [bp-2]
	sahf	
	jb	@90@2
	pop	di
	pop	si
	leave	
	ret	
@crater$qv	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@band$qv	proc	far
	push	di
   	les	 di, dword ptr DGROUP:_p_background
	add	 di, DGROUP:_py
	mov	 cx, DGROUP:_cr
	mov	 ah, byte ptr DGROUP:_g 
@91@5:
   	mov	 al, es:[di]
	sub	 al, ah
	jnc	short @91@9
	xor	 al, al 
@91@9:
   	mov	 es:[di], al
	inc	 di
	dec	 cx
	jne	short @91@5
	pop	di
	ret	
@band$qv	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@wave$qv	proc	far
	push	di
   	les	 di, dword ptr DGROUP:_p_background
	mov	 DGROUP:_px, 360
	mov	 bx, DGROUP:_cy 
@92@4:
   	fild	 DGROUP:_px
	fmul	 DGROUP:_a
	db	 0d9H, 0feH 
	fild	 DGROUP:_cr
	fmulp	
	fistp	 DGROUP:_py
	add	 DGROUP:_py, bx
	mov	 ax, DGROUP:_py
	mov	 dx, 360
	mul	 dx
	add	 ax, 4
	mov	 di, ax
	add	 di, DGROUP:_px
	mov	 byte ptr es:[di], 0
	dec	 DGROUP:_px
	jne	short @92@4
	pop	di
	ret	
@wave$qv	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@fracture$qnucf	proc	far
	push	bp
	mov	bp,sp
	sub	sp,12
	push	si
	push	di
	call	far ptr _rand
	cwde	
	imul	eax,large 360
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	mov	word ptr [bp-4],ax
	fild	word ptr [bp-4]
	fmul	qword ptr DGROUP:_deg
	fstp	dword ptr DGROUP:_a
	fwait	
	inc	word ptr DGROUP:_gr
	mov	ax,word ptr DGROUP:_cx
	mov	word ptr [bp-4],ax
	fild	word ptr [bp-4]
	fstp	dword ptr [bp-8]
	fwait	
	mov	ax,word ptr DGROUP:_cy
	mov	word ptr [bp-4],ax
	fild	word ptr [bp-4]
	fstp	dword ptr [bp-12]
	fwait	
@93@2:
	mov	si,word ptr DGROUP:_g
	call	far ptr _rand
	cwde	
	movsx	edx,si
	imul	eax,edx
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	mov	di,word ptr DGROUP:_g
	push	eax
	call	far ptr _rand
	cwde	
	movsx	edx,di
	imul	eax,edx
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	pop	edx
	sub	dx,ax
	mov	word ptr [bp-4],dx
	fild	word ptr [bp-4]
	fmul	qword ptr DGROUP:_deg
	fadd	dword ptr DGROUP:_a
	fstp	dword ptr DGROUP:_a
	fld	dword ptr DGROUP:_a
	sub	sp,8
	fstp	qword ptr [bp-24]
	fwait	
	call	far ptr _cos
	add	sp,8
	fmul	dword ptr DGROUP:_kfract
	fadd	dword ptr [bp-8]
	fstp	dword ptr [bp-8]
	fld	dword ptr [bp-8]
	fcomp	dword ptr DGROUP:s@+1914
	fstsw	word ptr [bp-4]
	fwait	
	mov	ax,word ptr [bp-4]
	sahf	
	jbe	short @93@4
	fld	dword ptr DGROUP:s@+1506
	fsubr	dword ptr [bp-8]
	fstp	dword ptr [bp-8]
	fwait	
@93@4:
	fld	dword ptr [bp-8]
	fldz	
	fcompp
	fstsw	word ptr [bp-4]
	fwait	
	mov	ax,word ptr [bp-4]
	sahf	
	jbe	short @93@6
	fld	dword ptr DGROUP:s@+1506
	fadd	dword ptr [bp-8]
	fstp	dword ptr [bp-8]
	fwait	
@93@6:
	fld	dword ptr DGROUP:_a
	sub	sp,8
	fstp	qword ptr [bp-24]
	fwait	
	call	far ptr _sin
	add	sp,8
	fmul	dword ptr DGROUP:_kfract
	fadd	dword ptr [bp-12]
	fstp	dword ptr [bp-12]
	fld	dword ptr [bp+10]
	fld1	
	fsub	
	fcomp	dword ptr [bp-12]
	fstsw	word ptr [bp-4]
	fwait	
	mov	ax,word ptr [bp-4]
	sahf	
	jae	short @93@8
	fld	dword ptr [bp+10]
	fsubr	dword ptr [bp-12]
	fstp	dword ptr [bp-12]
	fwait	
@93@8:
	fld	dword ptr [bp-12]
	fldz	
	fcompp
	fstsw	word ptr [bp-4]
	fwait	
	mov	ax,word ptr [bp-4]
	sahf	
	jbe	short @93@10
	fld	dword ptr [bp+10]
	fadd	dword ptr [bp-12]
	fstp	dword ptr [bp-12]
	fwait	
@93@10:
	fld	dword ptr [bp-12]
	call	far ptr F_FTOL@
	imul	ax,ax,360
	mov	word ptr [bp-4],ax
	mov	word ptr [bp-2],0
	fild	dword ptr [bp-4]
	fadd	dword ptr [bp-8]
	call	far ptr F_FTOL@
	mov	word ptr DGROUP:_vptr,ax
	les	bx,dword ptr [bp+6]
	add	bx,word ptr DGROUP:_vptr
	mov	cl,byte ptr DGROUP:_b
	shr	byte ptr es:[bx],cl
	dec	word ptr DGROUP:_gr
	cmp	word ptr DGROUP:_gr,0
	jne	@93@2
	pop	di
	pop	si
	leave	
	ret	
@fracture$qnucf	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@volcano$qv	proc	far
	push	bp
	mov	bp,sp
	sub	sp,2
	mov	dword ptr DGROUP:_a,large 0
	jmp	@94@9
@94@2:
	mov	ax,word ptr DGROUP:_gr
	mov	word ptr DGROUP:_b,ax
	mov	ax,word ptr DGROUP:_cr
	cwd	
	sub	ax,dx
	sar	ax,1
	mov	word ptr DGROUP:_g,ax
	jmp	@94@6
@94@3:
	fld	dword ptr DGROUP:_a
	sub	sp,8
	fstp	qword ptr [bp-10]
	fwait	
	call	far ptr _cos
	add	sp,8
	mov	ax,word ptr DGROUP:_g
	mov	word ptr [bp-2],ax
	fild	word ptr [bp-2]
	fmul	
	mov	ax,word ptr DGROUP:_cx
	mov	word ptr [bp-2],ax
	fild	word ptr [bp-2]
	fadd	
	call	far ptr F_FTOL@
	mov	word ptr DGROUP:_px,ax
	fld	dword ptr DGROUP:_a
	sub	sp,8
	fstp	qword ptr [bp-10]
	fwait	
	call	far ptr _sin
	add	sp,8
	mov	ax,word ptr DGROUP:_g
	mov	word ptr [bp-2],ax
	fild	word ptr [bp-2]
	fmul	
	mov	ax,word ptr DGROUP:_cy
	mov	word ptr [bp-2],ax
	fild	word ptr [bp-2]
	fadd	
	call	far ptr F_FTOL@
	mov	word ptr DGROUP:_py,ax
	mov	ax,360
	imul	word ptr DGROUP:_py
	mov	word ptr DGROUP:_py,ax
	push	cs
	call	near ptr @spot$qv
	dec	word ptr DGROUP:_gr
	cmp	word ptr DGROUP:_gr,0
	jge	short @94@5
	mov	word ptr DGROUP:_gr,0
@94@5:
	inc	word ptr DGROUP:_g
@94@6:
	mov	ax,word ptr DGROUP:_g
	cmp	ax,word ptr DGROUP:_cr
	jl	@94@3
	mov	ax,word ptr DGROUP:_b
	mov	word ptr DGROUP:_gr,ax
	fld	dword ptr DGROUP:_a
	fld	dword ptr DGROUP:s@+1910
	fmul	qword ptr DGROUP:_deg
	fadd	
	fstp	dword ptr DGROUP:_a
	fwait	
@94@9:
	fld	dword ptr DGROUP:_a
	fcomp	qword ptr DGROUP:s@+1510
	fstsw	word ptr [bp-2]
	fwait	
	mov	ax,word ptr [bp-2]
	sahf	
	jb	@94@2
	leave	
	ret	
@volcano$qv	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@contrast$qfff	proc	far
	push	bp
	mov	bp,sp
	sub	sp,2
	push	si
	push	di
	xor	si,si
	jmp	@95@12
@95@2:
	les	bx,dword ptr DGROUP:_p_background
	add	bx,si
	mov	di,bx
	mov	al,byte ptr es:[bx]
	mov	ah,0
	mov	word ptr [bp-2],ax
	fild	word ptr [bp-2]
	fstp	dword ptr DGROUP:_a
	fld	dword ptr [bp+14]
	fsubr	dword ptr DGROUP:_a
	fstp	dword ptr DGROUP:_a
	fld	dword ptr DGROUP:_a
	fldz	
	fcompp
	fstsw	word ptr [bp-2]
	fwait	
	mov	ax,word ptr [bp-2]
	sahf	
	jae	short @95@4
	fld	dword ptr [bp+6]
	fmul	dword ptr DGROUP:_a
	fstp	dword ptr DGROUP:_a
	jmp	short @95@5
@95@4:
	fld	dword ptr [bp+10]
	fmul	dword ptr DGROUP:_a
	fstp	dword ptr DGROUP:_a
@95@5:
	fwait	
	fld	dword ptr [bp+14]
	fadd	dword ptr DGROUP:_a
	fstp	dword ptr DGROUP:_a
	fld	dword ptr DGROUP:_a
	fldz	
	fcompp
	fstsw	word ptr [bp-2]
	fwait	
	mov	ax,word ptr [bp-2]
	sahf	
	jbe	short @95@8
	mov	dword ptr DGROUP:_a,large 0
@95@8:
	fld	dword ptr DGROUP:_a
	fcomp	dword ptr DGROUP:s@+1754
	fstsw	word ptr [bp-2]
	fwait	
	mov	ax,word ptr [bp-2]
	sahf	
	jbe	short @95@10
	mov	dword ptr DGROUP:_a,large 0427C0000h
@95@10:
	mov	es,word ptr DGROUP:_p_background+2
	fld	dword ptr DGROUP:_a
	push	es
	call	far ptr F_FTOL@
	pop	es
	mov	byte ptr es:[di],al
	inc	si
@95@12:
	cmp	si,-736
	jb	@95@2
	pop	di
	pop	si
	leave	
	ret	
@contrast$qfff	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@randoface$qii	proc	far
	push	bp
	mov	bp,sp
	sub	sp,4
	push	si
	push	di
	mov	di,word ptr [bp+8]
	xor	si,si
	jmp	@96@12
@96@2:
	les	bx,dword ptr DGROUP:_p_background
	add	bx,si
	mov	al,byte ptr es:[bx]
	mov	ah,0
	mov	word ptr DGROUP:_gr,ax
	or	di,di
	jle	short @96@4
	cmp	word ptr DGROUP:_gr,di
	jge	short @96@6
@96@4:
	or	di,di
	jge	short @96@11
	mov	ax,di
	neg	ax
	cmp	ax,word ptr DGROUP:_gr
	jl	short @96@11
@96@6:
	mov	ax,word ptr [bp+6]
	mov	word ptr [bp-2],ax
	call	far ptr _rand
	cwde	
	movsx	edx,word ptr [bp-2]
	imul	eax,edx
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	add	word ptr DGROUP:_gr,ax
	mov	ax,word ptr [bp+6]
	mov	word ptr [bp-4],ax
	call	far ptr _rand
	cwde	
	movsx	edx,word ptr [bp-4]
	imul	eax,edx
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	sub	word ptr DGROUP:_gr,ax
	cmp	word ptr DGROUP:_gr,63
	jle	short @96@8
	mov	word ptr DGROUP:_gr,63
@96@8:
	cmp	word ptr DGROUP:_gr,0
	jge	short @96@10
	mov	word ptr DGROUP:_gr,0
@96@10:
	les	bx,dword ptr DGROUP:_p_background
	add	bx,si
	mov	al,byte ptr DGROUP:_gr
	mov	byte ptr es:[bx],al
@96@11:
	inc	si
@96@12:
	cmp	si,-736
	jb	@96@2
	pop	di
	pop	si
	leave	
	ret	
@randoface$qii	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@negate$qv	proc	far
	push	di
   	les	 di, DGROUP:_p_background
	mov	 cx, 64800 
@97@3:
   	mov	 al, 03EH
	sub	 al, es:[di]
	mov	 es:[di], al
	inc	 di
	dec	 cx
	jne	short @97@3
	pop	di
	ret	
@negate$qv	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@crater_juice$qv	proc	far
	push	si
	push	di
	call	far ptr _rand
	cwde	
	imul	eax,large 3
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	mov	byte ptr DGROUP:_lave,al
	call	far ptr _rand
	cwde	
	imul	eax,large 3
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	add	al,al
	mov	byte ptr DGROUP:_crays,al
	mov	word ptr DGROUP:_c,0
	jmp	@98@8
@98@2:
	call	far ptr _rand
	cwde	
	imul	eax,large 360
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	mov	word ptr DGROUP:_cx,ax
	mov	ax,word ptr DGROUP:_r
	inc	ax
	sub	ax,word ptr DGROUP:_c
	mov	si,ax
	call	far ptr _rand
	cwde	
	movsx	edx,si
	imul	eax,edx
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	add	ax,2
	mov	word ptr DGROUP:_cr,ax
	jmp	short @98@4
@98@3:
	sub	word ptr DGROUP:_cr,10
@98@4:
	cmp	word ptr DGROUP:_cr,20
	jg	short @98@3
	mov	ax,word ptr DGROUP:_cr
	add	ax,ax
	mov	dx,178
	sub	dx,ax
	mov	di,dx
	call	far ptr _rand
	cwde	
	movsx	edx,di
	imul	eax,edx
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	add	ax,word ptr DGROUP:_cr
	mov	word ptr DGROUP:_cy,ax
	push	cs
	call	near ptr @crater$qv
	cmp	word ptr DGROUP:_cr,15
	jle	short @98@7
	push	dword ptr DGROUP:_p_background
	push	cs
	call	near ptr @lssmooth$qnuc
	add	sp,4
@98@7:
	inc	word ptr DGROUP:_c
@98@8:
	mov	ax,word ptr DGROUP:_c
	cmp	ax,word ptr DGROUP:_r
	jl	@98@2
	pop	di
	pop	si
	ret	
@crater_juice$qv	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@cirrus$qv	proc	far
	push	di
   	les	 di, dword ptr DGROUP:_objectschart
	mov	 bx, DGROUP:_py
	add	 bx, DGROUP:_px
	shr	 bx, 1
	mov	 al, es:[bx+di]
	add	 al, byte ptr DGROUP:_gr
	cmp	 al, 01FH
	jb	short @99@10
	mov	 al, 01FH 
@99@10:
     	mov	 es:[bx+di], al
	pop	di
	ret	
@cirrus$qv	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@atm_cyclon$qv	proc	far
	push	bp
	mov	bp,sp
	sub	sp,2
	mov	word ptr DGROUP:_b,0
	jmp	@100@5
@100@2:
	fld	dword ptr DGROUP:_a
	sub	sp,8
	fstp	qword ptr [bp-10]
	fwait	
	call	far ptr _cos
	add	sp,8
	mov	ax,word ptr DGROUP:_cr
	mov	word ptr [bp-2],ax
	fild	word ptr [bp-2]
	fmul	
	mov	ax,word ptr DGROUP:_cx
	mov	word ptr [bp-2],ax
	fild	word ptr [bp-2]
	fadd	
	call	far ptr F_FTOL@
	mov	word ptr DGROUP:_px,ax
	fld	dword ptr DGROUP:_a
	sub	sp,8
	fstp	qword ptr [bp-10]
	fwait	
	call	far ptr _sin
	add	sp,8
	mov	ax,word ptr DGROUP:_cr
	mov	word ptr [bp-2],ax
	fild	word ptr [bp-2]
	fmul	
	mov	ax,word ptr DGROUP:_cy
	mov	word ptr [bp-2],ax
	fild	word ptr [bp-2]
	fadd	
	call	far ptr F_FTOL@
	mov	word ptr DGROUP:_py,ax
	mov	ax,360
	imul	word ptr DGROUP:_py
	mov	word ptr DGROUP:_py,ax
	push	cs
	call	near ptr @cirrus$qv
	call	far ptr _rand
	cwde	
	shl	eax,2
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	add	word ptr DGROUP:_px,ax
	push	cs
	call	near ptr @cirrus$qv
	add	word ptr DGROUP:_py,359
	push	cs
	call	near ptr @cirrus$qv
	call	far ptr _rand
	cwde	
	shl	eax,2
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	sub	word ptr DGROUP:_px,ax
	push	cs
	call	near ptr @cirrus$qv
	add	word ptr DGROUP:_py,361
	push	cs
	call	near ptr @cirrus$qv
	call	far ptr _rand
	cwde	
	shl	eax,2
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	add	word ptr DGROUP:_px,ax
	push	cs
	call	near ptr @cirrus$qv
	inc	word ptr DGROUP:_b
	mov	ax,word ptr DGROUP:_b
	cwd	
	idiv	word ptr DGROUP:_g
	mov	word ptr DGROUP:_b,dx
	cmp	word ptr DGROUP:_b,0
	jne	short @100@4
	dec	word ptr DGROUP:_cr
@100@4:
	fld	dword ptr DGROUP:_a
	fld	dword ptr DGROUP:s@+1918
	fmul	qword ptr DGROUP:_deg
	fadd	
	fstp	dword ptr DGROUP:_a
	fwait	
@100@5:
	cmp	word ptr DGROUP:_cr,0
	jg	@100@2
	leave	
	ret	
@atm_cyclon$qv	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@storm$qv	proc	far
	push	bp
	mov	bp,sp
	sub	sp,2
	mov	word ptr DGROUP:_g,1
	jmp	@101@7
@101@2:
	mov	dword ptr DGROUP:_a,large 0
	jmp	@101@5
@101@3:
	fld	dword ptr DGROUP:_a
	sub	sp,8
	fstp	qword ptr [bp-10]
	fwait	
	call	far ptr _cos
	add	sp,8
	mov	ax,word ptr DGROUP:_g
	mov	word ptr [bp-2],ax
	fild	word ptr [bp-2]
	fmul	
	mov	ax,word ptr DGROUP:_cx
	mov	word ptr [bp-2],ax
	fild	word ptr [bp-2]
	fadd	
	call	far ptr F_FTOL@
	mov	word ptr DGROUP:_px,ax
	fld	dword ptr DGROUP:_a
	sub	sp,8
	fstp	qword ptr [bp-10]
	fwait	
	call	far ptr _sin
	add	sp,8
	mov	ax,word ptr DGROUP:_g
	mov	word ptr [bp-2],ax
	fild	word ptr [bp-2]
	fmul	
	mov	ax,word ptr DGROUP:_cy
	mov	word ptr [bp-2],ax
	fild	word ptr [bp-2]
	fadd	
	call	far ptr F_FTOL@
	mov	word ptr DGROUP:_py,ax
	mov	ax,360
	imul	word ptr DGROUP:_py
	mov	word ptr DGROUP:_py,ax
	push	cs
	call	near ptr @cirrus$qv
	fld	dword ptr DGROUP:_a
	fld	dword ptr DGROUP:s@+1910
	fmul	qword ptr DGROUP:_deg
	fadd	
	fstp	dword ptr DGROUP:_a
	fwait	
@101@5:
	fld	dword ptr DGROUP:_a
	fcomp	qword ptr DGROUP:s@+1510
	fstsw	word ptr [bp-2]
	fwait	
	mov	ax,word ptr [bp-2]
	sahf	
	jb	@101@3
	inc	word ptr DGROUP:_g
@101@7:
	mov	ax,word ptr DGROUP:_g
	cmp	ax,word ptr DGROUP:_cr
	jl	@101@2
	leave	
	ret	
@storm$qv	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@surface$qiiduc	proc	far
	push	bp
	mov	bp,sp
	sub	sp,92
	push	si
	push	di
	mov	si,word ptr [bp+8]
	mov	byte ptr [bp-5],0
	mov	ax,word ptr DGROUP:_QUADWORDS
	mov	word ptr [bp-8],ax
	mov	eax,dword ptr DGROUP:_objectschart
	mov	dword ptr [bp-48],eax
	cmp	si,10
	jne	short @102@3
	jmp	@102@243
@102@3:
	fld	qword ptr [bp+10]
	fadd	dword ptr DGROUP:s@+1922
	call	far ptr F_FTOL@
	push	dx
	push	ax
	push	cs
	call	near ptr @fast_srand$ql
	add	sp,4
	push	50
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	imul	ax,ax,10
	push	ax
	push	25
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	imul	ax,ax,10
	pop	dx
	add	dx,ax
	push	dx
	push	250
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	pop	dx
	add	dx,ax
	add	dx,51
	mov	bx,word ptr [bp+6]
	add	bx,bx
	mov	word ptr DGROUP:_nearstar_p_rtperiod[bx],dx
	mov	bx,word ptr [bp+6]
	add	bx,bx
	mov	ax,word ptr DGROUP:_nearstar_p_rtperiod[bx]
	mov	word ptr [bp-50],ax
	fild	word ptr [bp-50]
	fdivr	qword ptr DGROUP:_secs
	call	far ptr F_FTOL@
	mov	bx,word ptr [bp+6]
	add	bx,bx
	mov	word ptr DGROUP:_nearstar_p_rotation[bx],ax
	mov	bx,word ptr [bp+6]
	add	bx,bx
	mov	ax,word ptr DGROUP:_nearstar_p_rotation[bx]
	mov	bx,360
	cwd	
	idiv	bx
	mov	bx,word ptr [bp+6]
	add	bx,bx
	mov	word ptr DGROUP:_nearstar_p_rotation[bx],dx
	push	word ptr [bp+6]
	push	cs
	call	near ptr @cplx_planet_viewpoint$qi
	add	sp,2
	mov	dx,89
	sub	dx,ax
	mov	word ptr [bp-2],dx
	mov	bx,word ptr [bp+6]
	add	bx,bx
	mov	ax,word ptr DGROUP:_nearstar_p_rotation[bx]
	add	word ptr [bp-2],ax
	mov	bx,360
	mov	ax,word ptr [bp-2]
	cwd	
	idiv	bx
	mov	word ptr [bp-2],dx
	cmp	word ptr [bp-2],0
	jge	short @102@5
	add	word ptr [bp-2],360
@102@5:
	fld	qword ptr [bp+10]
	fmul	dword ptr DGROUP:s@+1534
	call	far ptr F_FTOL@
	push	dx
	push	ax
	push	cs
	call	near ptr @fast_srand$ql
	add	sp,4
	push	large 0FFFFh
	push	cs
	call	near ptr @fast_random$ql
	add	sp,4
	mov	word ptr [bp-4],ax
	push	ax
	call	far ptr _srand
	add	sp,2
   	les	 di, dword ptr DGROUP:_p_background
	mov	 cx, 64800
	mov	 ax, [bp-4] 
@102@9:
   	add	 ax, cx
	xor	 dx, dx
	imul	 ax
	add	 ax, dx
	mov	 bl, al
	and	 bl, 03EH
	mov	 es:[di], bl
	inc	 di
	dec	 cx
	jne	short @102@9
	push	large 07E900000h
	push	dword ptr [bp-48]
	call	far ptr __fmemset
	add	sp,8
	push	word ptr [bp-4]
	call	far ptr _srand
	add	sp,2
	mov	word ptr DGROUP:_QUADWORDS,16200
	mov	bx,si
	cmp	bx,9
	ja	@102@178
	add	bx,bx
	jmp	word ptr cs:@102@C611[bx]
@102@23:
	push	3
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,5
	mov	word ptr DGROUP:_r,ax
	mov	word ptr DGROUP:_c,0
	jmp	short @102@26
@102@24:
	push	dword ptr DGROUP:_p_background
	push	cs
	call	near ptr @ssmooth$qnuc
	add	sp,4
	inc	word ptr DGROUP:_c
@102@26:
	mov	ax,word ptr DGROUP:_c
	cmp	ax,word ptr DGROUP:_r
	jl	short @102@24
   	les	 di, dword ptr DGROUP:_p_background
	mov	 cx, 64800 
@102@29:
   	cmp	 byte ptr es:[di], 28
	jb	short @102@32
	mov	 byte ptr es:[di], 62 
@102@32:
   	inc	 di
	dec	 cx
	jne	short @102@29
	push	5
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,5
	mov	word ptr DGROUP:_r,ax
	mov	word ptr DGROUP:_c,0
	jmp	short @102@38
@102@36:
	push	dword ptr DGROUP:_p_background
	push	cs
	call	near ptr @ssmooth$qnuc
	add	sp,4
	inc	word ptr DGROUP:_c
@102@38:
	mov	ax,word ptr DGROUP:_c
	cmp	ax,word ptr DGROUP:_r
	jl	short @102@36
	push	26
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,5
	mov	word ptr DGROUP:_r,ax
	mov	word ptr DGROUP:_c,0
	jmp	short @102@42
@102@40:
	push	20
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,5
	mov	word ptr DGROUP:_cr,ax
	push	360
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	mov	word ptr DGROUP:_cx,ax
	push	130
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,25
	mov	word ptr DGROUP:_cy,ax
	mov	ax,word ptr DGROUP:_cr
	cwd	
	sub	ax,dx
	sar	ax,1
	push	ax
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	push	ax
	mov	ax,word ptr DGROUP:_cr
	cwd	
	sub	ax,dx
	sar	ax,1
	pop	dx
	add	dx,ax
	add	dx,2
	mov	word ptr DGROUP:_gr,dx
	push	cs
	call	near ptr @volcano$qv
	inc	word ptr DGROUP:_c
@102@42:
	mov	ax,word ptr DGROUP:_c
	cmp	ax,word ptr DGROUP:_r
	jl	short @102@40
	push	100
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,100
	mov	word ptr DGROUP:_r,ax
	push	3
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	inc	ax
	mov	word ptr DGROUP:_b,ax
	mov	word ptr DGROUP:_g,360
	mov	word ptr DGROUP:_c,0
	jmp	short @102@46
@102@44:
	push	360
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	mov	word ptr DGROUP:_cx,ax
	push	180
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	mov	word ptr DGROUP:_cy,ax
	push	100
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	mov	word ptr DGROUP:_gr,ax
	push	large 043340000h
	push	dword ptr DGROUP:_p_background
	push	cs
	call	near ptr @fracture$qnucf
	add	sp,8
	inc	word ptr DGROUP:_c
@102@46:
	mov	ax,word ptr DGROUP:_c
	cmp	ax,word ptr DGROUP:_r
	jl	short @102@44
@102@47:
	push	dword ptr DGROUP:_p_background
	push	cs
	call	near ptr @lssmooth$qnuc
	add	sp,4
	jmp	@102@178
@102@48:
	push	2
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	or	ax,ax
	je	short @102@50
	push	dword ptr DGROUP:_p_background
	push	cs
	call	near ptr @ssmooth$qnuc
	add	sp,4
@102@50:
	push	41
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,10
	mov	word ptr DGROUP:_r,ax
	push	cs
	call	near ptr @crater_juice$qv
	push	dword ptr DGROUP:_p_background
	push	cs
	call	near ptr @lssmooth$qnuc
	add	sp,4
	push	5
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	or	ax,ax
	jne	@102@178
	push	cs
	call	near ptr @negate$qv
	jmp	@102@178
@102@52:
	push	25
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,5
	mov	word ptr DGROUP:_r,ax
	mov	word ptr DGROUP:_c,0
	jmp	@102@61
@102@53:
	push	20
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	inc	ax
	mov	word ptr DGROUP:_cr,ax
	add	ax,ax
	mov	dx,178
	sub	dx,ax
	push	dx
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,word ptr DGROUP:_cr
	mov	word ptr DGROUP:_cy,ax
	call	far ptr _rand
	cwde	
	shl	eax,1
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	or	ax,ax
	je	short @102@58
	cmp	ax,1
	je	short @102@59
	jmp	@102@60
@102@58:
	fld	dword ptr DGROUP:s@+1534
	fmul	qword ptr DGROUP:_secs
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	push	eax
	push	3600
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,180
	movsx	ebx,ax
	pop	eax
	cdq	
	idiv	ebx
	mov	ebx,large 360
	cdq	
	idiv	ebx
	mov	word ptr DGROUP:_cx,dx
	push	12
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,2
	mov	word ptr DGROUP:_gr,ax
	push	cs
	call	near ptr @storm$qv
	jmp	short @102@60
@102@59:
	push	15
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,3
	mov	word ptr DGROUP:_gr,ax
	mov	ax,word ptr DGROUP:_cy
	imul	ax,ax,360
	mov	word ptr DGROUP:_py,ax
	mov	ax,360
	imul	word ptr DGROUP:_cr
	mov	word ptr DGROUP:_cr,ax
	push	word ptr DGROUP:_gr
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	inc	ax
	mov	word ptr DGROUP:_g,ax
	push	cs
	call	near ptr @band$qv
@102@60:
	inc	word ptr DGROUP:_c
@102@61:
	mov	ax,word ptr DGROUP:_c
	cmp	ax,word ptr DGROUP:_r
	jl	@102@53
	push	3
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	or	ax,ax
	jne	@102@178
	push	cs
	call	near ptr @negate$qv
	jmp	@102@178
@102@64:
	push	3
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,4
	mov	word ptr DGROUP:_r,ax
	push	3
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,26
	push	ax
	push	5
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	pop	dx
	sub	dx,ax
	mov	word ptr DGROUP:_g,dx
	mov	word ptr DGROUP:_c,0
	jmp	short @102@67
@102@65:
	push	dword ptr DGROUP:_p_background
	push	cs
	call	near ptr @ssmooth$qnuc
	add	sp,4
	inc	word ptr DGROUP:_c
@102@67:
	mov	ax,word ptr DGROUP:_c
	cmp	ax,word ptr DGROUP:_r
	jl	short @102@65
   	les	 di, dword ptr DGROUP:_p_background
	mov	 cx, 64000
	mov	 ax, [bp-4] 
@102@71:
   	mov	 dl, byte ptr DGROUP:_g
	cmp	 es:[di], dl
	jae	short @102@76
	mov	 byte ptr es:[di], 16
	jmp	short @102@85
@102@76:
   	add	 ax, cx
	imul	 ax
	add	 ax, dx
	mov	 bl, al
	and	 bl, 03EH
	add	 es:[di], bl
	cmp	 byte ptr es:[di], 03EH
	jb	short @102@85
	mov	 word ptr es:[di], 03EH 
@102@85:
   	inc	 di
	dec	 cx
	jne	short @102@71
	push	40
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,20
	mov	word ptr DGROUP:_r,ax
	mov	word ptr DGROUP:_c,0
	jmp	@102@94
@102@89:
	push	5
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	inc	ax
	mov	word ptr DGROUP:_gr,ax
	push	10
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,10
	mov	word ptr DGROUP:_cr,ax
	push	3
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	or	ax,ax
	je	short @102@91
	mov	ax,word ptr DGROUP:_cr
	add	ax,ax
	mov	dx,172
	sub	dx,ax
	push	dx
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,word ptr DGROUP:_cr
	add	ax,2
	mov	word ptr DGROUP:_cy,ax
	jmp	short @102@92
@102@91:
	push	10
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,60
	push	ax
	push	10
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	pop	dx
	sub	dx,ax
	mov	word ptr DGROUP:_cy,dx
@102@92:
	fld	qword ptr DGROUP:_secs
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	push	eax
	push	360
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,180
	movsx	ebx,ax
	pop	eax
	cdq	
	idiv	ebx
	mov	ebx,large 360
	cdq	
	idiv	ebx
	mov	word ptr DGROUP:_cx,dx
	push	5
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,7
	mov	word ptr DGROUP:_g,ax
	push	360
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	mov	word ptr [bp-50],ax
	fild	word ptr [bp-50]
	fmul	qword ptr DGROUP:_deg
	fstp	dword ptr DGROUP:_a
	fwait	
	push	cs
	call	near ptr @atm_cyclon$qv
	inc	word ptr DGROUP:_c
@102@94:
	mov	ax,word ptr DGROUP:_c
	cmp	ax,word ptr DGROUP:_r
	jl	@102@89
	jmp	@102@178
@102@96:
	push	dword ptr DGROUP:_p_background
	push	cs
	call	near ptr @ssmooth$qnuc
	add	sp,4
	push	2
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	or	ax,ax
	je	short @102@98
	push	dword ptr DGROUP:_p_background
	push	cs
	call	near ptr @ssmooth$qnuc
	add	sp,4
@102@98:
   	les	 di, dword ptr DGROUP:_p_background
	mov	 cx, 64000 
@102@100:
   	cmp	 byte ptr es:[di], 32
	jne	short @102@104
	mov	 word ptr es:[di], 03E01H
	mov	 byte ptr es:[di+360], 001H 
@102@104:
   	inc	 di
	dec	 cx
	jne	short @102@100
	push	30
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	mov	word ptr DGROUP:_r,ax
	cmp	word ptr DGROUP:_r,20
	jle	short @102@109
	mov	ax,10
	imul	word ptr DGROUP:_r
	mov	word ptr DGROUP:_r,ax
@102@109:
	push	3
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	inc	ax
	mov	word ptr DGROUP:_b,ax
	push	300
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,200
	mov	word ptr DGROUP:_g,ax
	mov	word ptr DGROUP:_c,0
	jmp	short @102@112
@102@110:
	push	360
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	mov	word ptr DGROUP:_cx,ax
	push	180
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	mov	word ptr DGROUP:_cy,ax
	push	100
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,50
	mov	word ptr DGROUP:_gr,ax
	push	large 043340000h
	push	dword ptr DGROUP:_p_background
	push	cs
	call	near ptr @fracture$qnucf
	add	sp,8
	inc	word ptr DGROUP:_c
@102@112:
	mov	ax,word ptr DGROUP:_c
	cmp	ax,word ptr DGROUP:_r
	jl	short @102@110
	push	25
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	inc	ax
	mov	word ptr DGROUP:_r,ax
	push	cs
	call	near ptr @crater_juice$qv
	push	dword ptr DGROUP:_p_background
	push	cs
	call	near ptr @lssmooth$qnuc
	add	sp,4
	push	2
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	or	ax,ax
	je	@102@178
	jmp	@102@47
@102@115:
	push	3
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,4
	mov	word ptr DGROUP:_r,ax
	mov	word ptr DGROUP:_c,0
	jmp	short @102@118
@102@116:
	push	dword ptr DGROUP:_p_background
	push	cs
	call	near ptr @ssmooth$qnuc
	add	sp,4
	inc	word ptr DGROUP:_c
@102@118:
	mov	ax,word ptr DGROUP:_c
	cmp	ax,word ptr DGROUP:_r
	jl	short @102@116
	push	3
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,25
	mov	word ptr [bp-50],ax
	fild	word ptr [bp-50]
	sub	sp,4
	fstp	dword ptr [bp-100]
	push	350
	fwait	
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	mov	word ptr [bp-50],ax
	fild	word ptr [bp-50]
	fdiv	dword ptr DGROUP:s@+1746
	fadd	dword ptr DGROUP:s@+1910
	sub	sp,4
	fstp	dword ptr [bp-104]
	push	200
	fwait	
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	mov	word ptr [bp-50],ax
	fild	word ptr [bp-50]
	fdiv	dword ptr DGROUP:s@+1926
	fadd	qword ptr DGROUP:s@+1930
	sub	sp,4
	fstp	dword ptr [bp-108]
	fwait	
	push	cs
	call	near ptr @contrast$qfff
	add	sp,12
	push	3
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	imul	ax,ax,-20
	add	ax,-20
	push	ax
	push	3
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,5
	push	ax
	push	cs
	call	near ptr @randoface$qii
	add	sp,4
	push	5
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,5
	mov	word ptr DGROUP:_r,ax
	mov	word ptr DGROUP:_c,0
	jmp	short @102@122
@102@120:
	push	10
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,5
	mov	word ptr DGROUP:_cr,ax
	push	360
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	mov	word ptr DGROUP:_cx,ax
	push	145
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,15
	mov	word ptr DGROUP:_cy,ax
	mov	ax,word ptr DGROUP:_cr
	cwd	
	sub	ax,dx
	sar	ax,1
	push	ax
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,2
	mov	word ptr DGROUP:_gr,ax
	push	cs
	call	near ptr @volcano$qv
	inc	word ptr DGROUP:_c
@102@122:
	mov	ax,word ptr DGROUP:_c
	cmp	ax,word ptr DGROUP:_r
	jl	short @102@120
	push	5
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,5
	mov	word ptr DGROUP:_r,ax
	mov	word ptr DGROUP:_c,0
	jmp	@102@126
@102@124:
	push	30
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	inc	ax
	mov	word ptr DGROUP:_cr,ax
	add	ax,ax
	mov	dx,178
	sub	dx,ax
	push	dx
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,word ptr DGROUP:_cr
	mov	word ptr DGROUP:_cy,ax
	fld	dword ptr DGROUP:s@+1938
	fmul	qword ptr DGROUP:_secs
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	push	eax
	push	3600
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,360
	movsx	ebx,ax
	pop	eax
	cdq	
	idiv	ebx
	mov	ebx,large 360
	cdq	
	idiv	ebx
	mov	word ptr DGROUP:_cx,dx
	push	2
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	inc	ax
	mov	word ptr DGROUP:_gr,ax
	push	cs
	call	near ptr @permanent_storm$qv
	inc	word ptr DGROUP:_c
@102@126:
	mov	ax,word ptr DGROUP:_c
	cmp	ax,word ptr DGROUP:_r
	jl	@102@124
	mov	word ptr DGROUP:_c,0
@102@128:
	push	10
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,10
	mov	word ptr DGROUP:_gr,ax
	push	360
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	mov	word ptr DGROUP:_px,ax
	push	10
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	mov	word ptr DGROUP:_py,ax
	mov	ax,360
	imul	word ptr DGROUP:_py
	mov	word ptr DGROUP:_py,ax
	push	cs
	call	near ptr @spot$qv
	push	360
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	mov	word ptr DGROUP:_px,ax
	push	10
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	mov	dx,125
	sub	dx,ax
	mov	word ptr DGROUP:_py,dx
	mov	ax,360
	imul	word ptr DGROUP:_py
	mov	word ptr DGROUP:_py,ax
	push	cs
	call	near ptr @spot$qv
	inc	word ptr DGROUP:_c
	cmp	word ptr DGROUP:_c,10000
	jl	short @102@128
	push	2
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	or	ax,ax
	je	@102@47
	push	dword ptr DGROUP:_p_background
	push	cs
	call	near ptr @ssmooth$qnuc
	add	sp,4
	jmp	@102@178
@102@133:
	push	5
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,3
	mov	word ptr DGROUP:_r,ax
	mov	word ptr DGROUP:_c,0
	jmp	short @102@136
@102@134:
	push	dword ptr DGROUP:_p_background
	push	cs
	call	near ptr @ssmooth$qnuc
	add	sp,4
	inc	word ptr DGROUP:_c
@102@136:
	mov	ax,word ptr DGROUP:_c
	cmp	ax,word ptr DGROUP:_r
	jl	short @102@134
	push	100
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,50
	mov	word ptr DGROUP:_r,ax
	mov	word ptr DGROUP:_c,0
	jmp	@102@142
@102@138:
	push	10
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	inc	ax
	mov	word ptr DGROUP:_cr,ax
	add	ax,ax
	mov	dx,178
	sub	dx,ax
	push	dx
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,word ptr DGROUP:_cr
	mov	word ptr DGROUP:_cy,ax
	push	8
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	or	ax,ax
	je	short @102@140
	push	5
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,2
	mov	word ptr DGROUP:_gr,ax
	push	ax
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	inc	ax
	mov	word ptr DGROUP:_g,ax
	mov	ax,word ptr DGROUP:_cy
	imul	ax,ax,360
	mov	word ptr DGROUP:_py,ax
	mov	ax,360
	imul	word ptr DGROUP:_cr
	mov	word ptr DGROUP:_cr,ax
	push	cs
	call	near ptr @band$qv
	jmp	short @102@141
@102@140:
	push	10
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,5
	mov	word ptr [bp-50],ax
	fild	word ptr [bp-50]
	fdiv	dword ptr DGROUP:s@+1586
	fstp	dword ptr DGROUP:_a
	fwait	
	mov	ax,word ptr DGROUP:_cr
	mov	bx,4
	cwd	
	idiv	bx
	inc	ax
	mov	word ptr DGROUP:_cr,ax
	push	cs
	call	near ptr @wave$qv
@102@141:
	inc	word ptr DGROUP:_c
@102@142:
	mov	ax,word ptr DGROUP:_c
	cmp	ax,word ptr DGROUP:_r
	jl	@102@138
	push	100
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,50
	mov	word ptr DGROUP:_r,ax
	mov	word ptr DGROUP:_c,0
	jmp	@102@149
@102@144:
	push	15
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	inc	ax
	mov	word ptr DGROUP:_cr,ax
	add	ax,ax
	mov	dx,178
	sub	dx,ax
	push	dx
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,word ptr DGROUP:_cr
	mov	word ptr DGROUP:_cy,ax
	fld	dword ptr DGROUP:s@+1938
	fmul	qword ptr DGROUP:_secs
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	push	eax
	push	8000
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,360
	movsx	ebx,ax
	pop	eax
	cdq	
	idiv	ebx
	mov	ebx,large 360
	cdq	
	idiv	ebx
	mov	word ptr DGROUP:_cx,dx
	push	2
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	inc	ax
	mov	word ptr DGROUP:_gr,ax
	push	10
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	or	ax,ax
	je	short @102@146
	mov	ax,word ptr DGROUP:_cr
	cwd	
	sub	ax,dx
	sar	ax,1
	inc	ax
	mov	word ptr DGROUP:_cr,ax
	jmp	short @102@147
@102@146:
	mov	ax,3
	imul	word ptr DGROUP:_gr
	mov	word ptr DGROUP:_gr,ax
@102@147:
	push	cs
	call	near ptr @storm$qv
	inc	word ptr DGROUP:_c
@102@149:
	mov	ax,word ptr DGROUP:_c
	cmp	ax,word ptr DGROUP:_r
	jl	@102@144
	push	dword ptr DGROUP:_p_background
	push	cs
	call	near ptr @lssmooth$qnuc
	add	sp,4
	push	3
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	or	ax,ax
	jne	@102@178
	push	cs
	call	near ptr @negate$qv
	jmp	@102@178
@102@152:
	push	5
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,5
	mov	word ptr DGROUP:_r,ax
	mov	word ptr DGROUP:_c,0
	jmp	short @102@155
@102@153:
	push	dword ptr DGROUP:_p_background
	push	cs
	call	near ptr @ssmooth$qnuc
	add	sp,4
	inc	word ptr DGROUP:_c
@102@155:
	mov	ax,word ptr DGROUP:_c
	cmp	ax,word ptr DGROUP:_r
	jl	short @102@153
	push	50
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,10
	mov	word ptr DGROUP:_r,ax
	push	20
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,5
	mov	word ptr DGROUP:_g,ax
	push	2
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	inc	ax
	mov	word ptr DGROUP:_b,ax
	mov	word ptr DGROUP:_c,0
	jmp	short @102@159
@102@157:
	push	360
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	mov	word ptr DGROUP:_cx,ax
	push	180
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	mov	word ptr DGROUP:_cy,ax
	push	300
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	mov	word ptr DGROUP:_gr,ax
	push	large 043340000h
	push	dword ptr DGROUP:_p_background
	push	cs
	call	near ptr @fracture$qnucf
	add	sp,8
	inc	word ptr DGROUP:_c
@102@159:
	mov	ax,word ptr DGROUP:_c
	cmp	ax,word ptr DGROUP:_r
	jl	short @102@157
	push	2
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	or	ax,ax
	je	short @102@162
	push	dword ptr DGROUP:_p_background
	push	cs
	call	near ptr @lssmooth$qnuc
	add	sp,4
@102@162:
	push	large 00001000Ah
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	inc	ax
	push	ax
	push	cs
	call	near ptr @randoface$qii
	add	sp,4
	push	2
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	or	ax,ax
	je	@102@178
	push	cs
	call	near ptr @negate$qv
	jmp	@102@178
@102@164:
	push	10
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	inc	ax
	mov	word ptr DGROUP:_r,ax
	mov	word ptr DGROUP:_c,0
	jmp	short @102@167
@102@165:
	push	dword ptr DGROUP:_p_background
	push	cs
	call	near ptr @lssmooth$qnuc
	add	sp,4
	inc	word ptr DGROUP:_c
@102@167:
	mov	ax,word ptr DGROUP:_c
	cmp	ax,word ptr DGROUP:_r
	jl	short @102@165
	push	50
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,100
	mov	word ptr DGROUP:_r,ax
	mov	word ptr DGROUP:_c,0
	jmp	short @102@171
@102@169:
	push	5
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	inc	ax
	mov	word ptr DGROUP:_cr,ax
	push	5
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	inc	ax
	mov	word ptr DGROUP:_gr,ax
	push	360
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	mov	word ptr DGROUP:_cx,ax
	mov	ax,word ptr DGROUP:_cr
	add	ax,ax
	mov	dx,178
	sub	dx,ax
	push	dx
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,word ptr DGROUP:_cr
	mov	word ptr DGROUP:_cy,ax
	push	cs
	call	near ptr @permanent_storm$qv
	inc	word ptr DGROUP:_c
@102@171:
	mov	ax,word ptr DGROUP:_c
	cmp	ax,word ptr DGROUP:_r
	jl	short @102@169
	push	2
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	or	ax,ax
	je	short @102@178
	push	cs
	call	near ptr @negate$qv
	jmp	short @102@178
@102@174:
	push	31
	push	dword ptr DGROUP:_p_background
	push	cs
	call	near ptr @pclear$qnucuc
	add	sp,6
	mov	cx,16200
	mov	di,word ptr [bp-48]
	mov	es,word ptr [bp-46]
	mov	ax,7967
	rep 	stosw	
	mov	word ptr DGROUP:_px,32400
@102@178:
	cmp	si,3
	je	short @102@180
	cmp	si,5
	jne	short @102@184
@102@180:
	mov	word ptr DGROUP:_px,0
	jmp	short @102@183
@102@181:
	les	bx,dword ptr DGROUP:_p_background
	add	bx,word ptr DGROUP:_px
	shr	byte ptr es:[bx],1
	inc	word ptr DGROUP:_px
@102@183:
	cmp	word ptr DGROUP:_px,-736
	jb	short @102@181
@102@184:
	cmp	si,3
	jne	short @102@189
	push	2
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	or	ax,ax
	je	short @102@187
	push	dword ptr DGROUP:_p_background
	push	cs
	call	near ptr @lssmooth$qnuc
	jmp	short @102@188
@102@187:
	push	dword ptr DGROUP:_p_background
	push	cs
	call	near ptr @ssmooth$qnuc
@102@188:
	add	sp,4
@102@189:
	mov	word ptr DGROUP:_px,0
	mov	word ptr DGROUP:_py,0
	jmp	short @102@195
@102@190:
	les	bx,dword ptr [bp-48]
	add	bx,word ptr DGROUP:_px
	mov	al,byte ptr es:[bx]
	les	bx,dword ptr DGROUP:_p_background
	add	bx,word ptr DGROUP:_py
	mov	word ptr [bp-88],bx
	add	byte ptr es:[bx],al
	mov	bx,word ptr DGROUP:_p_background
	add	bx,word ptr DGROUP:_py
	mov	word ptr [bp-88],bx
	cmp	byte ptr es:[bx],62
	jbe	short @102@192
	mov	byte ptr es:[bx],62
@102@192:
	les	bx,dword ptr [bp-48]
	add	bx,word ptr DGROUP:_px
	mov	al,byte ptr es:[bx]
	mov	dx,word ptr DGROUP:_py
	inc	dx
	les	bx,dword ptr DGROUP:_p_background
	add	bx,dx
	mov	word ptr [bp-90],bx
	add	byte ptr es:[bx],al
	mov	ax,word ptr DGROUP:_py
	inc	ax
	mov	bx,word ptr DGROUP:_p_background
	add	bx,ax
	mov	word ptr [bp-90],bx
	cmp	byte ptr es:[bx],62
	jbe	short @102@194
	mov	ax,word ptr DGROUP:_py
	inc	ax
	mov	bx,word ptr DGROUP:_p_background
	add	bx,ax
	mov	byte ptr es:[bx],62
@102@194:
	add	word ptr DGROUP:_py,2
	inc	word ptr DGROUP:_px
@102@195:
	cmp	word ptr DGROUP:_px,32400
	jb	short @102@190
	cmp	si,2
	jne	short @102@199
	call	far ptr _rand
	cwde	
	imul	eax,large 3
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	or	ax,ax
	jne	short @102@199
	push	dword ptr DGROUP:_p_background
	push	cs
	call	near ptr @psmooth_grays$qnuc
	add	sp,4
	mov	byte ptr [bp-5],1
@102@199:
	mov	bx,word ptr [bp+6]
	add	bx,bx
	mov	ax,word ptr [bp-2]
	add	ax,35
	mov	word ptr DGROUP:_nearstar_p_term_start[bx],ax
	mov	bx,word ptr [bp+6]
	add	bx,bx
	cmp	word ptr DGROUP:_nearstar_p_term_start[bx],360
	jl	short @102@201
	mov	bx,word ptr [bp+6]
	add	bx,bx
	sub	word ptr DGROUP:_nearstar_p_term_start[bx],360
@102@201:
	mov	bx,word ptr [bp+6]
	add	bx,bx
	mov	ax,word ptr DGROUP:_nearstar_p_term_start[bx]
	add	ax,130
	mov	bx,word ptr [bp+6]
	add	bx,bx
	mov	word ptr DGROUP:_nearstar_p_term_end[bx],ax
	mov	bx,word ptr [bp+6]
	add	bx,bx
	cmp	word ptr DGROUP:_nearstar_p_term_end[bx],360
	jl	short @102@203
	mov	bx,word ptr [bp+6]
	add	bx,bx
	sub	word ptr DGROUP:_nearstar_p_term_end[bx],360
@102@203:
   	les	 di, dword ptr DGROUP:_p_background
	add	 di, [bp-2]
	add	 di, 35
	mov	 cx, 179 
@102@207:
   	push	 cx
	mov	 cx, 130 
@102@209:
   	shr	 byte ptr es:[di], 2
	inc	 di
	dec	 cx
	jne	short @102@209
	pop	 cx
	add	 di, 230
	dec	 cx
	jne	short @102@207
	cmp	si,2
	jne	short @102@224
	cmp	byte ptr [bp-5],0
	je	short @102@220
	push	dword ptr DGROUP:_p_background
	push	cs
	call	near ptr @ssmooth$qnuc
	add	sp,4
	jmp	short @102@224
@102@220:
	push	5
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	add	ax,3
	mov	word ptr DGROUP:_r,ax
	mov	word ptr DGROUP:_c,0
	jmp	short @102@223
@102@221:
	push	dword ptr DGROUP:_p_background
	push	cs
	call	near ptr @ssmooth$qnuc
	add	sp,4
	inc	word ptr DGROUP:_c
@102@223:
	mov	ax,word ptr DGROUP:_c
	cmp	ax,word ptr DGROUP:_r
	jl	short @102@221
@102@224:
	cmp	si,6
	jne	short @102@230
	mov	word ptr DGROUP:_c,0
@102@226:
	push	2
	push	cs
	call	near ptr @ranged_fast_random$qi
	add	sp,2
	or	ax,ax
	je	short @102@228
	push	dword ptr DGROUP:_p_background
	push	cs
	call	near ptr @ssmooth$qnuc
	add	sp,4
@102@228:
	inc	word ptr DGROUP:_c
	cmp	word ptr DGROUP:_c,3
	jl	short @102@226
@102@230:
	cmp	si,9
	jne	short @102@235
	mov	word ptr DGROUP:_c,0
@102@232:
	push	dword ptr DGROUP:_p_background
	push	cs
	call	near ptr @ssmooth$qnuc
	add	sp,4
	inc	word ptr DGROUP:_c
	cmp	word ptr DGROUP:_c,6
	jl	short @102@232
@102@235:
	cmp	byte ptr [bp+18],255
	jne	short @102@237
	mov	ax,word ptr [bp-8]
	mov	word ptr DGROUP:_QUADWORDS,ax
	jmp	@102@243
@102@237:
	shl	si,2
	mov	al,byte ptr DGROUP:_planet_rgb_and_var[si]
	mov	ah,0
	mov	word ptr DGROUP:_r,ax
	mov	al,byte ptr DGROUP:_planet_rgb_and_var[si+1]
	mov	ah,0
	mov	word ptr DGROUP:_g,ax
	mov	al,byte ptr DGROUP:_planet_rgb_and_var[si+2]
	mov	ah,0
	mov	word ptr DGROUP:_b,ax
	mov	al,byte ptr DGROUP:_planet_rgb_and_var[si+3]
	mov	ah,0
	mov	word ptr DGROUP:_c,ax
	shl	word ptr DGROUP:_r,1
	mov	al,byte ptr DGROUP:_nearstar_r
	cbw	
	add	word ptr DGROUP:_r,ax
	sar	word ptr DGROUP:_r,1
	shl	word ptr DGROUP:_g,1
	mov	al,byte ptr DGROUP:_nearstar_g
	cbw	
	add	word ptr DGROUP:_g,ax
	sar	word ptr DGROUP:_g,1
	shl	word ptr DGROUP:_b,1
	mov	al,byte ptr DGROUP:_nearstar_b
	cbw	
	add	word ptr DGROUP:_b,ax
	sar	word ptr DGROUP:_b,1
	mov	ax,word ptr DGROUP:_c
	mov	word ptr [bp-52],ax
	call	far ptr _rand
	cwde	
	movsx	edx,word ptr [bp-52]
	imul	eax,edx
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	add	ax,word ptr DGROUP:_r
	mov	dx,word ptr DGROUP:_c
	mov	word ptr [bp-54],dx
	push	ax
	call	far ptr _rand
	cwde	
	movsx	edx,word ptr [bp-54]
	imul	eax,edx
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	pop	dx
	sub	dx,ax
	mov	word ptr [bp-50],dx
	fild	word ptr [bp-50]
	fstp	dword ptr [bp-12]
	fwait	
	mov	ax,word ptr DGROUP:_c
	mov	word ptr [bp-56],ax
	call	far ptr _rand
	cwde	
	movsx	edx,word ptr [bp-56]
	imul	eax,edx
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	add	ax,word ptr DGROUP:_g
	mov	dx,word ptr DGROUP:_c
	mov	word ptr [bp-58],dx
	push	ax
	call	far ptr _rand
	cwde	
	movsx	edx,word ptr [bp-58]
	imul	eax,edx
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	pop	dx
	sub	dx,ax
	mov	word ptr [bp-50],dx
	fild	word ptr [bp-50]
	fstp	dword ptr [bp-24]
	fwait	
	mov	ax,word ptr DGROUP:_c
	mov	word ptr [bp-60],ax
	call	far ptr _rand
	cwde	
	movsx	edx,word ptr [bp-60]
	imul	eax,edx
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	add	ax,word ptr DGROUP:_b
	mov	dx,word ptr DGROUP:_c
	mov	word ptr [bp-62],dx
	push	ax
	call	far ptr _rand
	cwde	
	movsx	edx,word ptr [bp-62]
	imul	eax,edx
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	pop	dx
	sub	dx,ax
	mov	word ptr [bp-50],dx
	fild	word ptr [bp-50]
	fstp	dword ptr [bp-36]
	fwait	
	mov	ax,word ptr DGROUP:_c
	mov	word ptr [bp-64],ax
	call	far ptr _rand
	cwde	
	movsx	edx,word ptr [bp-64]
	imul	eax,edx
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	add	ax,word ptr DGROUP:_r
	mov	dx,word ptr DGROUP:_c
	mov	word ptr [bp-66],dx
	push	ax
	call	far ptr _rand
	cwde	
	movsx	edx,word ptr [bp-66]
	imul	eax,edx
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	pop	dx
	sub	dx,ax
	mov	word ptr [bp-50],dx
	fild	word ptr [bp-50]
	fstp	dword ptr [bp-16]
	fwait	
	mov	ax,word ptr DGROUP:_c
	mov	word ptr [bp-68],ax
	call	far ptr _rand
	cwde	
	movsx	edx,word ptr [bp-68]
	imul	eax,edx
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	add	ax,word ptr DGROUP:_g
	mov	dx,word ptr DGROUP:_c
	mov	word ptr [bp-70],dx
	push	ax
	call	far ptr _rand
	cwde	
	movsx	edx,word ptr [bp-70]
	imul	eax,edx
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	pop	dx
	sub	dx,ax
	mov	word ptr [bp-50],dx
	fild	word ptr [bp-50]
	fstp	dword ptr [bp-28]
	fwait	
	mov	ax,word ptr DGROUP:_c
	mov	word ptr [bp-72],ax
	call	far ptr _rand
	cwde	
	movsx	edx,word ptr [bp-72]
	imul	eax,edx
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	add	ax,word ptr DGROUP:_b
	mov	dx,word ptr DGROUP:_c
	mov	word ptr [bp-74],dx
	push	ax
	call	far ptr _rand
	cwde	
	movsx	edx,word ptr [bp-74]
	imul	eax,edx
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	pop	dx
	sub	dx,ax
	mov	word ptr [bp-50],dx
	fild	word ptr [bp-50]
	fstp	dword ptr [bp-40]
	fwait	
	mov	ax,word ptr DGROUP:_c
	mov	word ptr [bp-76],ax
	call	far ptr _rand
	cwde	
	movsx	edx,word ptr [bp-76]
	imul	eax,edx
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	add	ax,word ptr DGROUP:_r
	mov	dx,word ptr DGROUP:_c
	mov	word ptr [bp-78],dx
	push	ax
	call	far ptr _rand
	cwde	
	movsx	edx,word ptr [bp-78]
	imul	eax,edx
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	pop	dx
	sub	dx,ax
	mov	word ptr [bp-50],dx
	fild	word ptr [bp-50]
	fstp	dword ptr [bp-20]
	fwait	
	mov	ax,word ptr DGROUP:_c
	mov	word ptr [bp-80],ax
	call	far ptr _rand
	cwde	
	movsx	edx,word ptr [bp-80]
	imul	eax,edx
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	add	ax,word ptr DGROUP:_g
	mov	dx,word ptr DGROUP:_c
	mov	word ptr [bp-82],dx
	push	ax
	call	far ptr _rand
	cwde	
	movsx	edx,word ptr [bp-82]
	imul	eax,edx
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	pop	dx
	sub	dx,ax
	mov	word ptr [bp-50],dx
	fild	word ptr [bp-50]
	fstp	dword ptr [bp-32]
	fwait	
	mov	ax,word ptr DGROUP:_c
	mov	word ptr [bp-84],ax
	call	far ptr _rand
	cwde	
	movsx	edx,word ptr [bp-84]
	imul	eax,edx
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	add	ax,word ptr DGROUP:_b
	mov	dx,word ptr DGROUP:_c
	mov	word ptr [bp-86],dx
	push	ax
	call	far ptr _rand
	cwde	
	movsx	edx,word ptr [bp-86]
	imul	eax,edx
	mov	ebx,large 08000h
	cdq	
	idiv	ebx
	pop	dx
	sub	dx,ax
	mov	word ptr [bp-50],dx
	fild	word ptr [bp-50]
	fstp	dword ptr [bp-44]
	fld	dword ptr [bp-12]
	fmul	dword ptr DGROUP:s@+8
	fstp	dword ptr [bp-12]
	fld	dword ptr [bp-24]
	fmul	dword ptr DGROUP:s@+8
	fstp	dword ptr [bp-24]
	fld	dword ptr [bp-36]
	fmul	dword ptr DGROUP:s@+8
	fstp	dword ptr [bp-36]
	fld	dword ptr [bp-16]
	fmul	dword ptr DGROUP:s@+1906
	fstp	dword ptr [bp-16]
	fld	dword ptr [bp-28]
	fmul	dword ptr DGROUP:s@+1906
	fstp	dword ptr [bp-28]
	fld	dword ptr [bp-40]
	fmul	dword ptr DGROUP:s@+1906
	fstp	dword ptr [bp-40]
	fld	dword ptr [bp-20]
	fmul	dword ptr DGROUP:s@+1942
	fstp	dword ptr [bp-20]
	fld	dword ptr [bp-32]
	fmul	dword ptr DGROUP:s@+1942
	fstp	dword ptr [bp-32]
	fld	dword ptr [bp-44]
	fmul	dword ptr DGROUP:s@+1942
	fstp	dword ptr [bp-44]
	sar	si,2
	fwait	
	push	dword ptr [bp-36]
	push	dword ptr [bp-24]
	push	dword ptr [bp-12]
	push	large 0
	push	large 0
	push	large 0
	push	16
	mov	al,byte ptr [bp+18]
	mov	ah,0
	mov	word ptr [bp-92],ax
	push	ax
	push	ds
	push	offset DGROUP:_tmppal
	push	cs
	call	near ptr @shade$qnuciiffffff
	add	sp,32
	push	dword ptr [bp-40]
	push	dword ptr [bp-28]
	push	dword ptr [bp-16]
	push	dword ptr [bp-36]
	push	dword ptr [bp-24]
	push	dword ptr [bp-12]
	push	16
	mov	al,byte ptr [bp+18]
	mov	ah,0
	mov	word ptr [bp-92],ax
	add	ax,16
	push	ax
	push	ds
	push	offset DGROUP:_tmppal
	push	cs
	call	near ptr @shade$qnuciiffffff
	add	sp,32
	push	dword ptr [bp-44]
	push	dword ptr [bp-32]
	push	dword ptr [bp-20]
	push	dword ptr [bp-40]
	push	dword ptr [bp-28]
	push	dword ptr [bp-16]
	push	16
	mov	al,byte ptr [bp+18]
	mov	ah,0
	mov	word ptr [bp-92],ax
	add	ax,32
	push	ax
	push	ds
	push	offset DGROUP:_tmppal
	push	cs
	call	near ptr @shade$qnuciiffffff
	add	sp,32
	push	large 042800000h
	push	large 042800000h
	push	large 042800000h
	push	dword ptr [bp-44]
	push	dword ptr [bp-32]
	push	dword ptr [bp-20]
	push	16
	mov	al,byte ptr [bp+18]
	mov	ah,0
	mov	word ptr [bp-92],ax
	add	ax,48
	push	ax
	push	ds
	push	offset DGROUP:_tmppal
	push	cs
	call	near ptr @shade$qnuciiffffff
	add	sp,32
	mov	bx,word ptr [bp+6]
	add	bx,bx
	mov	al,byte ptr DGROUP:_nearstar_p_owner[bx]
	mov	byte ptr [bp-6],al
	cbw	
	cmp	ax,-1
	jne	short @102@239
	mov	al,byte ptr [bp+6]
	mov	byte ptr [bp-6],al
@102@239:
	mov	al,byte ptr [bp-6]
	cbw	
	cmp	ax,4
	jg	short @102@241
	mov	byte ptr [bp-6],64
	jmp	short @102@242
@102@241:
	mov	al,byte ptr [bp-6]
	shl	al,2
	add	al,240
	mov	dl,64
	sub	dl,al
	mov	byte ptr [bp-6],dl
@102@242:
	mov	al,byte ptr [bp-6]
	push	ax
	push	ax
	push	ax
	push	64
	mov	al,byte ptr [bp+18]
	mov	ah,0
	mov	word ptr [bp-92],ax
	push	ax
	add	ax,ax
	add	ax,word ptr [bp-92]
	add	ax,offset DGROUP:_tmppal
	push	ds
	push	ax
	push	cs
	call	near ptr @tavola_colori$qnucuiuiccc
	add	sp,14
	mov	ax,word ptr [bp-8]
	mov	word ptr DGROUP:_QUADWORDS,ax
@102@243:
	pop	di
	pop	si
	leave	
	ret	
@surface$qiiduc	endp
@102@C611	label	word
	dw	@102@23
	dw	@102@48
	dw	@102@52
	dw	@102@64
	dw	@102@96
	dw	@102@115
	dw	@102@133
	dw	@102@152
	dw	@102@164
	dw	@102@174
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@ring$qidddii	proc	far
	push	bp
	mov	bp,sp
	sub	sp,60
	push	si
	push	di
	mov	bx,word ptr [bp+6]
	shl	bx,3
	fld	qword ptr DGROUP:_nearstar_p_ring[bx]
	fstp	qword ptr [bp-42]
	fwait	
	mov	bx,word ptr [bp+6]
	shl	bx,3
	fld	qword ptr DGROUP:_nearstar_p_tilt[bx]
	fld	qword ptr DGROUP:s@+1854
	fmul	qword ptr [bp-42]
	fmul	
	fstp	qword ptr [bp-50]
	fld	qword ptr DGROUP:s@+1946
	fmul	qword ptr [bp-42]
	fstp	qword ptr [bp-58]
	fld	dword ptr DGROUP:s@+1954
	fmul	qword ptr [bp-42]
	mov	ax,word ptr [bp+6]
	mov	word ptr [bp-60],ax
	fild	word ptr [bp-60]
	fadd	
	call	far ptr F_FTOL@
	push	dx
	push	ax
	push	cs
	call	near ptr @fast_srand$ql
	add	sp,4
	push	large 31
	push	cs
	call	near ptr @fast_random$ql
	add	sp,4
	inc	ax
	sub	ax,word ptr [bp+34]
	mov	word ptr [bp-2],ax
	push	large 3
	push	cs
	call	near ptr @fast_random$ql
	add	sp,4
	inc	ax
	mov	word ptr [bp-10],ax
	jmp	@103@17
@103@2:
	push	large 7
	push	cs
	call	near ptr @fast_random$ql
	add	sp,4
	or	ax,dx
	jne	short @103@4
	push	large 3
	push	cs
	call	near ptr @fast_random$ql
	add	sp,4
	inc	ax
	mov	word ptr [bp-4],ax
	mov	byte ptr DGROUP:_pixel_spreads,0
	jmp	short @103@5
@103@4:
	push	large 7
	push	cs
	call	near ptr @fast_random$ql
	add	sp,4
	inc	ax
	mov	word ptr [bp-4],ax
	mov	byte ptr DGROUP:_pixel_spreads,1
@103@5:
	mov	ax,word ptr [bp+32]
	cwd	
	idiv	word ptr [bp-4]
	mov	ax,word ptr [bp+32]
	sub	ax,dx
	mov	si,ax
	push	large 1
	push	cs
	call	near ptr @fast_random$ql
	add	sp,4
	push	ax
	push	large 1
	push	cs
	call	near ptr @fast_random$ql
	add	sp,4
	pop	dx
	add	dl,al
	mov	byte ptr DGROUP:_pixilating_effect,dl
	or	si,si
	jge	short @103@7
	add	si,360
@103@7:
	mov	ax,word ptr [bp-4]
	mov	word ptr [bp-6],ax
	jmp	@103@13
@103@8:
	push	large 1
	push	cs
	call	near ptr @fast_random$ql
	add	sp,4
	add	ax,word ptr [bp-4]
	mov	word ptr [bp-8],ax
	add	word ptr [bp-6],ax
	add	si,word ptr [bp-8]
	cmp	si,360
	jle	short @103@10
	sub	si,360
@103@10:
	mov	bx,si
	shl	bx,2
	mov	ax,seg _lft_sin
	mov	es,ax
	fld	dword ptr es:_lft_sin[bx]
	fmul	qword ptr [bp-50]
	fsubr	qword ptr [bp+16]
	fstp	qword ptr [bp-26]
	mov	bx,si
	shl	bx,2
	mov	ax,seg _lft_sin
	mov	es,ax
	fld	dword ptr es:_lft_sin[bx]
	fmul	qword ptr [bp-42]
	fadd	qword ptr [bp+8]
	fstp	qword ptr [bp-18]
	mov	bx,si
	shl	bx,2
	mov	ax,seg _lft_cos
	mov	es,ax
	fld	dword ptr es:_lft_cos[bx]
	fmul	qword ptr [bp-42]
	fadd	qword ptr [bp+24]
	fstp	qword ptr [bp-34]
	fwait	
	mov	di,word ptr [bp-10]
	jmp	short @103@12
@103@11:
	push	cs
	call	near ptr @fast_flandom$qv
	fmul	qword ptr [bp-58]
	fsubr	qword ptr [bp-58]
	fadd	qword ptr [bp-34]
	fstp	qword ptr [bp-34]
	fwait	
	push	cs
	call	near ptr @fast_flandom$qv
	fmul	qword ptr [bp-58]
	fsubr	qword ptr [bp-58]
	fadd	qword ptr [bp-18]
	fstp	qword ptr [bp-18]
	push	0
	fld	qword ptr DGROUP:s@+1958
	sub	sp,8
	fstp	qword ptr [bp-74]
	fld	qword ptr [bp-34]
	sub	sp,8
	fstp	qword ptr [bp-82]
	fld	qword ptr [bp-26]
	sub	sp,8
	fstp	qword ptr [bp-90]
	fld	qword ptr [bp-18]
	sub	sp,8
	fstp	qword ptr [bp-98]
	fwait	
	push	cs
	call	near ptr @far_pixel_at$qdddduc
	add	sp,34
	dec	di
@103@12:
	or	di,di
	jne	short @103@11
@103@13:
	mov	ax,word ptr [bp-6]
	add	ax,word ptr [bp-4]
	cmp	ax,180
	jl	@103@8
	fld	qword ptr [bp-58]
	fadd	qword ptr [bp-42]
	fstp	qword ptr [bp-42]
	push	large 7
	fwait	
	push	cs
	call	near ptr @fast_random$ql
	add	sp,4
	or	ax,dx
	jne	short @103@16
	fld	dword ptr DGROUP:s@+1538
	fmul	qword ptr [bp-58]
	fadd	qword ptr [bp-42]
	fstp	qword ptr [bp-42]
	fwait	
@103@16:
	mov	bx,word ptr [bp+6]
	shl	bx,3
	fld	qword ptr DGROUP:_nearstar_p_tilt[bx]
	fld	qword ptr DGROUP:s@+1854
	fmul	qword ptr [bp-42]
	fmul	
	fstp	qword ptr [bp-50]
	fwait	
	dec	word ptr [bp-2]
@103@17:
	cmp	word ptr [bp-2],0
	jg	@103@2
	mov	byte ptr DGROUP:_pixilating_effect,0
	mov	byte ptr DGROUP:_pixel_spreads,1
	pop	di
	pop	si
	leave	
	ret	
@ring$qidddii	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@planets$qv	proc	far
	push	bp
	mov	bp,sp
	sub	sp,126
	push	si
	push	di
	mov	eax,dword ptr DGROUP:_objectschart
	mov	dword ptr [bp-4],eax
	mov	eax,dword ptr DGROUP:_p_background
	mov	dword ptr [bp-8],eax
	fld	dword ptr DGROUP:s@+1810
	fstp	qword ptr [bp-106]
	fwait	
	cmp	byte ptr DGROUP:_ip_targetting,0
	je	short @104@3
	mov	byte ptr DGROUP:_ip_targetted,255
@104@3:
	cmp	word ptr DGROUP:_nearstar_nop,0
	je	@104@168
	mov	word ptr [bp-36],0
	mov	word ptr [bp-118],offset DGROUP:_nearstar_p_qsortindex
	mov	word ptr [bp-120],offset DGROUP:_nearstar_p_qsortdist
	jmp	@104@10
@104@6:
	push	word ptr [bp-36]
	push	cs
	call	near ptr @planet_xyz$qi
	add	sp,2
	fld	qword ptr DGROUP:_plx
	fsub	qword ptr DGROUP:_dzat_x
	fstp	qword ptr [bp-66]
	fld	qword ptr DGROUP:_ply
	fsub	qword ptr DGROUP:_dzat_y
	fstp	qword ptr [bp-74]
	fld	qword ptr DGROUP:_plz
	fsub	qword ptr DGROUP:_dzat_z
	fstp	qword ptr [bp-82]
	fwait	
	mov	bx,word ptr [bp-118]
	mov	ax,word ptr [bp-36]
	mov	word ptr [bx],ax
	fld	qword ptr [bp-66]
	fmul	qword ptr [bp-66]
	fld	qword ptr [bp-74]
	fmul	qword ptr [bp-74]
	fadd	
	fld	qword ptr [bp-82]
	fmul	qword ptr [bp-82]
	fadd	
	sub	sp,8
	fstp	qword ptr [bp-138]
	fwait	
	call	far ptr _sqrt
	add	sp,8
	mov	bx,word ptr [bp-120]
	fstp	dword ptr [bx]
	fwait	
	add	word ptr [bp-118],2
	add	word ptr [bp-120],4
	inc	word ptr [bp-36]
@104@10:
	mov	ax,word ptr [bp-36]
	cmp	ax,word ptr DGROUP:_nearstar_nob
	jl	@104@6
	mov	ax,word ptr DGROUP:_nearstar_nob
	dec	ax
	push	ax
	push	0
	push	ds
	push	offset DGROUP:_nearstar_p_qsortdist
	push	ds
	push	offset DGROUP:_nearstar_p_qsortindex
	push	cs
	call	near ptr @QuickSort$qninfii
	add	sp,12
	cmp	word ptr DGROUP:_nearstar_nob,1
	jne	short @104@14
	mov	ax,word ptr DGROUP:_npcs
	mov	word ptr [bp-32],ax
	mov	word ptr DGROUP:_npcs,0
	mov	ax,word ptr DGROUP:_npcs
	cmp	ax,word ptr [bp-32]
	je	@104@21
	mov	word ptr DGROUP:_resident_map1,0
	mov	word ptr DGROUP:_resident_map2,-1
	jmp	@104@21
@104@14:
	mov	ax,word ptr DGROUP:_npcs
	mov	word ptr [bp-32],ax
	mov	ax,word ptr DGROUP:_nearstar_nob
	dec	ax
	mov	word ptr [bp-24],ax
	mov	bx,word ptr [bp-24]
	add	bx,bx
	mov	ax,word ptr DGROUP:_nearstar_p_qsortindex[bx]
	mov	word ptr [bp-20],ax
	mov	bx,word ptr [bp-20]
	add	bx,bx
	mov	ax,word ptr DGROUP:_nearstar_p_owner[bx]
	mov	word ptr [bp-28],ax
	mov	ax,word ptr DGROUP:_nearstar_nob
	add	ax,-2
	mov	word ptr [bp-26],ax
	mov	bx,word ptr [bp-26]
	add	bx,bx
	mov	ax,word ptr DGROUP:_nearstar_p_qsortindex[bx]
	mov	word ptr [bp-22],ax
	mov	bx,word ptr [bp-22]
	add	bx,bx
	mov	ax,word ptr DGROUP:_nearstar_p_owner[bx]
	mov	word ptr [bp-30],ax
	cmp	word ptr [bp-28],-1
	jle	short @104@19
	mov	ax,word ptr [bp-26]
	add	ax,ax
	add	ax,offset DGROUP:_nearstar_p_qsortindex
	mov	word ptr [bp-122],ax
	jmp	short @104@18
@104@16:
	sub	word ptr [bp-122],2
	dec	word ptr [bp-26]
	mov	bx,word ptr [bp-122]
	mov	ax,word ptr [bx]
	mov	word ptr [bp-22],ax
	mov	bx,word ptr [bp-22]
	add	bx,bx
	mov	ax,word ptr DGROUP:_nearstar_p_owner[bx]
	mov	word ptr [bp-30],ax
@104@18:
	cmp	word ptr [bp-30],-1
	jg	short @104@16
@104@19:
	mov	ax,word ptr [bp-20]
	imul	ax,ax,80
	sub	ax,word ptr [bp-22]
	mov	word ptr DGROUP:_npcs,ax
	cmp	ax,word ptr [bp-32]
	je	short @104@21
	mov	ax,word ptr [bp-20]
	mov	word ptr DGROUP:_resident_map1,ax
	mov	ax,word ptr [bp-22]
	mov	word ptr DGROUP:_resident_map2,ax
@104@21:
	mov	word ptr [bp-34],0
	mov	word ptr [bp-124],offset DGROUP:_nearstar_p_qsortindex
	jmp	@104@166
@104@23:
	mov	bx,word ptr [bp-124]
	mov	ax,word ptr [bx]
	mov	word ptr [bp-36],ax
	mov	bx,word ptr [bp-36]
	shl	bx,2
	fld	dword ptr DGROUP:_nearstar_p_qsortdist[bx]
	fstp	qword ptr [bp-90]
	push	ax
	fwait	
	push	cs
	call	near ptr @planet_xyz$qi
	add	sp,2
	mov	bx,word ptr [bp-36]
	add	bx,bx
	cmp	word ptr DGROUP:_nearstar_p_owner[bx],-1
	jle	short @104@25
	mov	eax,dword ptr DGROUP:_s_background
	mov	dword ptr DGROUP:_p_background,eax
	mov	byte ptr [bp-107],128
	mov	byte ptr [bp-9],1
	jmp	short @104@26
@104@25:
	mov	eax,dword ptr [bp-8]
	mov	dword ptr DGROUP:_p_background,eax
	mov	byte ptr [bp-107],192
	mov	byte ptr [bp-9],0
@104@26:
	mov	byte ptr [bp-108],0
	mov	byte ptr [bp-109],0
	mov	byte ptr [bp-110],0
	mov	bx,word ptr [bp-36]
	shl	bx,3
	fld	qword ptr DGROUP:_nearstar_p_ray[bx]
	fmul	dword ptr DGROUP:s@+1886
	fcomp	qword ptr [bp-90]
	fstsw	word ptr [bp-116]
	fwait	
	mov	ax,word ptr [bp-116]
	sahf	
	jbe	short @104@30
	mov	byte ptr [bp-109],1
	mov	bx,word ptr [bp-36]
	shl	bx,3
	fld	qword ptr DGROUP:_nearstar_p_ray[bx]
	fdivr	qword ptr [bp-90]
	fmul	qword ptr DGROUP:s@+1846
	call	far ptr F_FTOL@
	mov	word ptr [bp-112],ax
	mov	bx,word ptr [bp-36]
	shl	bx,3
	fld	qword ptr DGROUP:_nearstar_p_ray[bx]
	fmul	dword ptr DGROUP:s@+1746
	fcomp	qword ptr [bp-90]
	fstsw	word ptr [bp-116]
	fwait	
	mov	ax,word ptr [bp-116]
	sahf	
	jbe	short @104@30
	mov	byte ptr [bp-108],1
	mov	bx,word ptr [bp-36]
	shl	bx,3
	fld	qword ptr DGROUP:_nearstar_p_ray[bx]
	fmul	dword ptr DGROUP:s@+1966
	fcomp	qword ptr [bp-90]
	fstsw	word ptr [bp-116]
	fwait	
	mov	ax,word ptr [bp-116]
	sahf	
	jbe	short @104@30
	mov	byte ptr [bp-110],1
@104@30:
	cmp	byte ptr DGROUP:_ip_targetting,0
	jne	short @104@32
	cmp	byte ptr [bp-108],0
	jne	@104@35
@104@32:
	push	0
	mov	bx,word ptr [bp-36]
	shl	bx,3
	fld	qword ptr DGROUP:_nearstar_p_ray[bx]
	sub	sp,8
	fstp	qword ptr [bp-140]
	fld	qword ptr DGROUP:_plz
	sub	sp,8
	fstp	qword ptr [bp-148]
	fld	qword ptr DGROUP:_ply
	sub	sp,8
	fstp	qword ptr [bp-156]
	fld	qword ptr DGROUP:_plx
	sub	sp,8
	fstp	qword ptr [bp-164]
	fwait	
	push	cs
	call	near ptr @far_pixel_at$qdddduc
	add	sp,34
	cmp	byte ptr DGROUP:_ip_targetting,0
	je	short @104@35
	fld	dword ptr DGROUP:s@+1798
	fsubr	qword ptr DGROUP:_pxx
	fstp	qword ptr DGROUP:_pxx
	fld	dword ptr DGROUP:s@+1746
	fsubr	qword ptr DGROUP:_pyy
	fstp	qword ptr DGROUP:_pyy
	fld	qword ptr DGROUP:_pxx
	fmul	qword ptr DGROUP:_pxx
	fld	qword ptr DGROUP:_pyy
	fmul	qword ptr DGROUP:_pyy
	fadd	
	fstp	qword ptr [bp-98]
	fld	qword ptr [bp-98]
	fcomp	qword ptr [bp-106]
	fstsw	word ptr [bp-116]
	fwait	
	mov	ax,word ptr [bp-116]
	sahf	
	jae	short @104@35
	fld	qword ptr [bp-98]
	fstp	qword ptr [bp-106]
	fwait	
	mov	al,byte ptr [bp-36]
	mov	byte ptr DGROUP:_ip_targetted,al
@104@35:
	mov	bx,word ptr [bp-36]
	mov	al,byte ptr DGROUP:_nearstar_p_type[bx]
	cbw	
	cmp	ax,10
	je	@104@164
	cmp	byte ptr [bp-109],0
	je	@104@44
	cmp	byte ptr [bp-110],0
	je	short @104@39
	mov	byte ptr DGROUP:_multicolourmask,192
	jmp	short @104@40
@104@39:
	mov	byte ptr DGROUP:_multicolourmask,64
@104@40:
	fld	qword ptr DGROUP:_dzat_z
	sub	sp,8
	fstp	qword ptr [bp-138]
	fld	qword ptr DGROUP:_dzat_x
	sub	sp,8
	fstp	qword ptr [bp-146]
	fwait	
	push	cs
	call	near ptr @planet_viewpoint$qdd
	add	sp,16
	mov	dx,359
	sub	dx,ax
	mov	word ptr [bp-44],dx
	mov	bx,word ptr [bp-36]
	shl	bx,3
	fld	qword ptr DGROUP:_nearstar_p_ring[bx]
	fldz	
	fcompp
	fstsw	word ptr [bp-116]
	fwait	
	mov	ax,word ptr [bp-116]
	sahf	
	je	short @104@44
	mov	ax,word ptr [bp-44]
	add	ax,180
	mov	word ptr [bp-46],ax
	cmp	word ptr [bp-46],359
	jle	short @104@43
	sub	word ptr [bp-46],360
@104@43:
	push	word ptr [bp-112]
	push	word ptr [bp-46]
	fld	qword ptr DGROUP:_plz
	sub	sp,8
	fstp	qword ptr [bp-142]
	fld	qword ptr DGROUP:_ply
	sub	sp,8
	fstp	qword ptr [bp-150]
	fld	qword ptr DGROUP:_plx
	sub	sp,8
	fstp	qword ptr [bp-158]
	fwait	
	push	word ptr [bp-36]
	push	cs
	call	near ptr @ring$qidddii
	add	sp,30
@104@44:
	cmp	byte ptr [bp-108],0
	je	@104@160
	cmp	byte ptr [bp-110],0
	je	@104@155
	mov	ax,word ptr [bp-36]
	cmp	ax,word ptr DGROUP:_resident_map1
	je	short @104@48
	cmp	ax,word ptr DGROUP:_resident_map2
	jne	@104@61
@104@48:
	cmp	byte ptr [bp-9],0
	je	short @104@52
	mov	bx,word ptr [bp-36]
	cmp	byte ptr DGROUP:_nearstar_p_type[bx],0
	je	short @104@51
	push	128
	mov	al,byte ptr DGROUP:_nearstar_p_type[bx]
	cbw	
	mov	word ptr [bp-116],ax
	fild	word ptr [bp-116]
	fld	dword ptr DGROUP:s@+1970
	fmul	dword ptr DGROUP:_nearstar_ray
	fmul	
	jmp	short @104@56
@104@51:
	push	128
	movsx	eax,word ptr [bp-36]
	imul	eax,large 0001E8480h
	mov	dword ptr [bp-116],eax
	fild	dword ptr [bp-116]
	fmul	dword ptr DGROUP:_nearstar_ray
	jmp	short @104@56
@104@52:
	mov	bx,word ptr [bp-36]
	cmp	byte ptr DGROUP:_nearstar_p_type[bx],0
	je	short @104@54
	push	192
	mov	al,byte ptr DGROUP:_nearstar_p_type[bx]
	cbw	
	cwde	
	imul	eax,large 0000F4240h
	jmp	short @104@55
@104@54:
	push	192
	movsx	eax,word ptr [bp-36]
	imul	eax,large 0001E8480h
@104@55:
	mov	dword ptr [bp-116],eax
	fild	dword ptr [bp-116]
	mov	bx,word ptr [bp-36]
	shl	bx,3
	fmul	qword ptr DGROUP:_nearstar_p_orb_seed[bx]
	mov	bx,word ptr [bp-36]
	shl	bx,3
	fmul	qword ptr DGROUP:_nearstar_p_orb_tilt[bx]
	mov	bx,word ptr [bp-36]
	shl	bx,3
	fmul	qword ptr DGROUP:_nearstar_p_orb_ecc[bx]
@104@56:
	mov	bx,word ptr [bp-36]
	shl	bx,3
	fmul	qword ptr DGROUP:_nearstar_p_orb_orient[bx]
	sub	sp,8
	fstp	qword ptr [bp-140]
	fwait	
	mov	bx,word ptr [bp-36]
	mov	al,byte ptr DGROUP:_nearstar_p_type[bx]
	cbw	
	push	ax
	push	bx
	push	cs
	call	near ptr @surface$qiiduc
	add	sp,14
	mov	ax,word ptr [bp-36]
	cmp	ax,word ptr DGROUP:_resident_map1
	jne	short @104@59
	mov	word ptr DGROUP:_resident_map1,-1
@104@59:
	mov	ax,word ptr [bp-36]
	cmp	ax,word ptr DGROUP:_resident_map2
	jne	short @104@61
	mov	word ptr DGROUP:_resident_map2,-1
@104@61:
	mov	al,byte ptr DGROUP:_ip_targetted
	cbw	
	cmp	ax,word ptr [bp-36]
	jne	@104@132
	cmp	byte ptr DGROUP:_landing_point,0
	je	@104@132
	mov	word ptr DGROUP:_nightzone,0
	mov	bx,word ptr [bp-36]
	add	bx,bx
	mov	ax,word ptr DGROUP:_nearstar_p_term_start[bx]
	mov	word ptr [bp-40],ax
	mov	bx,word ptr [bp-36]
	add	bx,bx
	mov	ax,word ptr DGROUP:_nearstar_p_term_end[bx]
	mov	word ptr [bp-42],ax
	mov	si,word ptr DGROUP:_landing_pt_lon
	mov	ax,word ptr [bp-40]
	cmp	ax,word ptr [bp-42]
	jle	short @104@67
	cmp	si,word ptr [bp-40]
	jge	short @104@69
	cmp	si,word ptr [bp-42]
	jge	short @104@70
	jmp	short @104@69
@104@67:
	cmp	si,word ptr [bp-40]
	jl	short @104@70
	cmp	si,word ptr [bp-42]
	jge	short @104@70
@104@69:
	mov	word ptr DGROUP:_nightzone,1
@104@70:
	mov	word ptr [bp-50],0
	mov	si,word ptr DGROUP:_landing_pt_lon
	jmp	short @104@73
@104@71:
	inc	word ptr [bp-50]
	inc	si
	cmp	si,360
	jl	short @104@73
	xor	si,si
@104@73:
	cmp	si,word ptr [bp-42]
	jne	short @104@71
	mov	word ptr [bp-52],0
	mov	si,word ptr DGROUP:_landing_pt_lon
	jmp	short @104@77
@104@75:
	inc	word ptr [bp-52]
	dec	si
	cmp	si,-1
	jg	short @104@77
	mov	si,359
@104@77:
	cmp	si,word ptr [bp-42]
	jne	short @104@75
	mov	ax,word ptr [bp-50]
	cmp	ax,word ptr [bp-52]
	jge	short @104@80
	mov	word ptr [bp-48],ax
	jmp	short @104@81
@104@80:
	mov	ax,word ptr [bp-52]
	mov	word ptr [bp-48],ax
@104@81:
	mov	word ptr [bp-56],0
	mov	si,word ptr DGROUP:_landing_pt_lon
	jmp	short @104@84
@104@82:
	inc	word ptr [bp-56]
	inc	si
	cmp	si,360
	jl	short @104@84
	xor	si,si
@104@84:
	cmp	si,word ptr [bp-40]
	jne	short @104@82
	mov	word ptr [bp-58],0
	mov	si,word ptr DGROUP:_landing_pt_lon
	jmp	short @104@88
@104@86:
	inc	word ptr [bp-58]
	dec	si
	cmp	si,-1
	jg	short @104@88
	mov	si,359
@104@88:
	cmp	si,word ptr [bp-40]
	jne	short @104@86
	mov	ax,word ptr [bp-56]
	cmp	ax,word ptr [bp-58]
	jge	short @104@91
	mov	word ptr [bp-54],ax
	jmp	short @104@92
@104@91:
	mov	ax,word ptr [bp-58]
	mov	word ptr [bp-54],ax
@104@92:
	mov	ax,word ptr [bp-54]
	cmp	ax,word ptr [bp-48]
	jg	short @104@94
	mov	word ptr DGROUP:_sun_x_factor,1
	mov	word ptr DGROUP:_crepzone,ax
	jmp	short @104@95
@104@94:
	mov	word ptr DGROUP:_sun_x_factor,-1
	mov	ax,word ptr [bp-48]
	mov	word ptr DGROUP:_crepzone,ax
@104@95:
	mov	bx,word ptr [bp-36]
	shl	bx,3
	fld	qword ptr DGROUP:_nearstar_p_orb_seed[bx]
	mov	bx,word ptr [bp-36]
	shl	bx,3
	fmul	qword ptr DGROUP:_nearstar_p_orb_ecc[bx]
	fmul	dword ptr DGROUP:s@+1974
	call	far ptr F_FTOL@
	push	dx
	push	ax
	push	cs
	call	near ptr @fast_srand$ql
	add	sp,4
	mov	ax,word ptr DGROUP:_landing_pt_lat
	imul	ax,ax,360
	add	ax,word ptr DGROUP:_landing_pt_lon
	mov	word ptr DGROUP:_ptr,ax
	push	large 31
	push	cs
	call	near ptr @fast_random$ql
	add	sp,4
	add	al,32
	mov	byte ptr DGROUP:_sky_red_filter,al
	push	large 15
	push	cs
	call	near ptr @fast_random$ql
	add	sp,4
	add	al,48
	mov	byte ptr DGROUP:_sky_grn_filter,al
	push	large 15
	push	cs
	call	near ptr @fast_random$ql
	add	sp,4
	add	al,48
	mov	byte ptr DGROUP:_sky_blu_filter,al
	cmp	byte ptr [bp-9],0
	je	short @104@97
	les	bx,dword ptr DGROUP:_p_background
	add	bx,word ptr DGROUP:_ptr
	mov	word ptr [bp-126],bx
	mov	al,byte ptr es:[bx]
	mov	ah,0
	mov	bx,ax
	add	bx,bx
	add	bx,ax
	mov	al,byte ptr DGROUP:_tmppal[bx+384]
	mov	byte ptr DGROUP:_gnd_red_filter,al
	mov	bx,word ptr [bp-126]
	mov	al,byte ptr es:[bx]
	mov	ah,0
	mov	bx,ax
	add	bx,bx
	add	bx,ax
	mov	al,byte ptr DGROUP:_tmppal[bx+385]
	mov	byte ptr DGROUP:_gnd_grn_filter,al
	mov	bx,word ptr [bp-126]
	mov	al,byte ptr es:[bx]
	mov	ah,0
	mov	bx,ax
	add	bx,bx
	add	bx,ax
	mov	al,byte ptr DGROUP:_tmppal[bx+386]
	jmp	short @104@98
@104@97:
	les	bx,dword ptr DGROUP:_p_background
	add	bx,word ptr DGROUP:_ptr
	mov	word ptr [bp-126],bx
	mov	al,byte ptr es:[bx]
	mov	ah,0
	mov	bx,ax
	add	bx,bx
	add	bx,ax
	mov	al,byte ptr DGROUP:_tmppal[bx+576]
	mov	byte ptr DGROUP:_gnd_red_filter,al
	mov	bx,word ptr [bp-126]
	mov	al,byte ptr es:[bx]
	mov	ah,0
	mov	bx,ax
	add	bx,bx
	add	bx,ax
	mov	al,byte ptr DGROUP:_tmppal[bx+577]
	mov	byte ptr DGROUP:_gnd_grn_filter,al
	mov	bx,word ptr [bp-126]
	mov	al,byte ptr es:[bx]
	mov	ah,0
	mov	bx,ax
	add	bx,bx
	add	bx,ax
	mov	al,byte ptr DGROUP:_tmppal[bx+578]
@104@98:
	mov	byte ptr DGROUP:_gnd_blu_filter,al
	push	large 15
	push	cs
	call	near ptr @fast_random$ql
	add	sp,4
	add	al,byte ptr DGROUP:_gnd_red_filter
	mov	byte ptr DGROUP:_gnd_red_filter,al
	push	large 15
	push	cs
	call	near ptr @fast_random$ql
	add	sp,4
	add	al,byte ptr DGROUP:_gnd_grn_filter
	mov	byte ptr DGROUP:_gnd_grn_filter,al
	push	large 15
	push	cs
	call	near ptr @fast_random$ql
	add	sp,4
	add	al,byte ptr DGROUP:_gnd_blu_filter
	mov	byte ptr DGROUP:_gnd_blu_filter,al
	mov	bx,word ptr [bp-36]
	movsx	eax,byte ptr DGROUP:_nearstar_p_type[bx]
	mov	dword ptr [bp-18],eax
	cmp	word ptr DGROUP:_nightzone,0
	je	short @104@103
	les	bx,dword ptr DGROUP:_p_background
	add	bx,word ptr DGROUP:_ptr
	mov	word ptr [bp-126],bx
	mov	al,byte ptr es:[bx]
	mov	ah,0
	mov	word ptr DGROUP:_albedo,ax
	shl	word ptr DGROUP:_albedo,2
	cmp	dword ptr [bp-18],large 3
	je	short @104@102
	cmp	dword ptr [bp-18],large 5
	jne	short @104@106
@104@102:
	mov	ax,word ptr DGROUP:_ptr
	shr	ax,1
	les	bx,dword ptr [bp-4]
	add	bx,ax
	mov	al,byte ptr es:[bx]
	cbw	
	sub	word ptr DGROUP:_albedo,ax
	jmp	short @104@106
@104@103:
	les	bx,dword ptr DGROUP:_p_background
	add	bx,word ptr DGROUP:_ptr
	mov	word ptr [bp-126],bx
	mov	al,byte ptr es:[bx]
	mov	ah,0
	mov	word ptr DGROUP:_albedo,ax
	cmp	dword ptr [bp-18],large 3
	je	short @104@105
	cmp	dword ptr [bp-18],large 5
	jne	short @104@106
@104@105:
	mov	ax,word ptr DGROUP:_ptr
	shr	ax,1
	les	bx,dword ptr [bp-4]
	add	bx,ax
	mov	al,byte ptr es:[bx]
	cbw	
	sub	word ptr DGROUP:_albedo,ax
@104@106:
	sar	word ptr DGROUP:_albedo,2
	shl	word ptr DGROUP:_albedo,2
	cmp	dword ptr [bp-18],large 3
	je	short @104@109
	cmp	dword ptr [bp-18],large 5
	jne	short @104@110
@104@109:
	mov	ax,2
	imul	word ptr DGROUP:_albedo
	mov	word ptr DGROUP:_albedo,ax
@104@110:
	mov	ax,word ptr DGROUP:_ptr
	shr	ax,1
	les	bx,dword ptr [bp-4]
	add	bx,ax
	mov	al,byte ptr es:[bx]
	cbw	
	mov	word ptr [bp-116],ax
	fild	word ptr [bp-116]
	fmul	dword ptr DGROUP:s@+8
	fstp	dword ptr DGROUP:_rainy
	fld	dword ptr DGROUP:_rainy
	fcomp	dword ptr DGROUP:s@+1538
	fstsw	word ptr [bp-116]
	fwait	
	mov	ax,word ptr [bp-116]
	sahf	
	jbe	short @104@112
	mov	dword ptr DGROUP:_rainy,large 040A00000h
@104@112:
	cmp	word ptr DGROUP:_nightzone,0
	je	short @104@116
	mov	al,byte ptr DGROUP:_sky_grn_filter
	cbw	
	cwd	
	sub	ax,dx
	sar	ax,1
	mov	byte ptr DGROUP:_sky_grn_filter,al
	mov	al,byte ptr DGROUP:_sky_blu_filter
	cbw	
	cwd	
	sub	ax,dx
	sar	ax,1
	mov	byte ptr DGROUP:_sky_blu_filter,al
	cmp	word ptr DGROUP:_crepzone,5
	jle	short @104@115
	mov	al,byte ptr DGROUP:_sky_red_filter
	cbw	
	cwd	
	sub	ax,dx
	sar	ax,1
	mov	byte ptr DGROUP:_sky_red_filter,al
	mov	byte ptr DGROUP:_sky_brightness,8
	mov	byte ptr DGROUP:_horiz_brt,10
	jmp	short @104@119
@104@115:
	mov	byte ptr DGROUP:_sky_brightness,32
	mov	byte ptr DGROUP:_horiz_brt,16
	jmp	short @104@119
@104@116:
	cmp	word ptr DGROUP:_crepzone,5
	jle	short @104@118
	mov	byte ptr DGROUP:_sky_brightness,48
	mov	byte ptr DGROUP:_horiz_brt,20
	jmp	short @104@119
@104@118:
	mov	al,byte ptr DGROUP:_sky_grn_filter
	cbw	
	cwd	
	sub	ax,dx
	sar	ax,1
	mov	byte ptr DGROUP:_sky_grn_filter,al
	mov	al,byte ptr DGROUP:_sky_blu_filter
	cbw	
	mov	bx,3
	cwd	
	idiv	bx
	mov	byte ptr DGROUP:_sky_blu_filter,al
	mov	byte ptr DGROUP:_sky_brightness,40
	mov	byte ptr DGROUP:_horiz_brt,13
@104@119:
	mov	dword ptr [bp-14],large -180
	jmp	short @104@124
@104@120:
	movzx	eax,word ptr DGROUP:_ptr
	add	eax,dword ptr [bp-14]
	mov	dword ptr [bp-18],eax
	cmp	dword ptr [bp-18],large 0
	jle	short @104@123
	cmp	dword ptr [bp-18],large 0FD20h
	jge	short @104@123
	les	bx,dword ptr DGROUP:_p_background
	add	bx,word ptr [bp-18]
	mov	di,bx
	mov	al,byte ptr es:[bx]
	xor	al,30
	mov	byte ptr es:[di],al
@104@123:
	inc	dword ptr [bp-14]
@104@124:
	cmp	dword ptr [bp-14],large 180
	jl	short @104@120
	mov	dword ptr [bp-14],large -60
	jmp	short @104@131
@104@126:
	cmp	dword ptr [bp-14],large 0
	je	short @104@130
	mov	eax,dword ptr [bp-14]
	imul	eax,large 360
	movzx	edx,word ptr DGROUP:_ptr
	add	eax,edx
	mov	dword ptr [bp-18],eax
	cmp	dword ptr [bp-18],large 0
	jle	short @104@130
	cmp	dword ptr [bp-18],large 0FD20h
	jge	short @104@130
	les	bx,dword ptr DGROUP:_p_background
	add	bx,word ptr [bp-18]
	mov	di,bx
	mov	al,byte ptr es:[bx]
	xor	al,30
	mov	byte ptr es:[di],al
@104@130:
	inc	dword ptr [bp-14]
@104@131:
	cmp	dword ptr [bp-14],large 60
	jl	short @104@126
@104@132:
	mov	bx,word ptr [bp-36]
	mov	al,byte ptr DGROUP:_nearstar_p_type[bx]
	cbw	
	mov	word ptr [bp-38],ax
	cmp	word ptr [bp-38],2
	je	short @104@137
	cmp	word ptr [bp-38],3
	je	short @104@137
	cmp	word ptr [bp-38],6
	je	short @104@137
	cmp	word ptr [bp-38],8
	je	short @104@137
	cmp	word ptr [bp-38],9
	jne	short @104@138
@104@137:
	mov	byte ptr DGROUP:_glass_bubble,1
	jmp	short @104@139
@104@138:
	mov	byte ptr DGROUP:_glass_bubble,0
@104@139:
	push	0
	mov	al,byte ptr [bp-107]
	push	ax
	mov	bx,word ptr [bp-36]
	shl	bx,3
	fld	qword ptr DGROUP:_nearstar_p_ray[bx]
	sub	sp,4
	fstp	dword ptr [bp-138]
	fld	qword ptr DGROUP:_plz
	sub	sp,8
	fstp	qword ptr [bp-146]
	fld	qword ptr DGROUP:_ply
	sub	sp,8
	fstp	qword ptr [bp-154]
	fld	qword ptr DGROUP:_plx
	sub	sp,8
	fstp	qword ptr [bp-162]
	push	22586
	fwait	
	push	dword ptr DGROUP:_n_globes_map
	push	dword ptr DGROUP:_p_background
	push	dword ptr DGROUP:_adapted
	mov	bx,word ptr [bp-36]
	add	bx,bx
	mov	ax,word ptr DGROUP:_nearstar_p_rotation[bx]
	add	ax,word ptr [bp-44]
	push	ax
	push	cs
	call	near ptr @globe$quinuct2t2uidddfcc
	add	sp,48
	mov	al,byte ptr DGROUP:_ip_targetted
	cbw	
	cmp	ax,word ptr [bp-36]
	jne	@104@160
	cmp	byte ptr DGROUP:_landing_point,0
	je	@104@160
	mov	dword ptr [bp-14],large -180
	jmp	short @104@146
@104@142:
	movzx	eax,word ptr DGROUP:_ptr
	add	eax,dword ptr [bp-14]
	mov	dword ptr [bp-18],eax
	cmp	dword ptr [bp-18],large 0
	jle	short @104@145
	cmp	dword ptr [bp-18],large 0FD20h
	jge	short @104@145
	les	bx,dword ptr DGROUP:_p_background
	add	bx,word ptr [bp-18]
	mov	di,bx
	mov	al,byte ptr es:[bx]
	xor	al,30
	mov	byte ptr es:[di],al
@104@145:
	inc	dword ptr [bp-14]
@104@146:
	cmp	dword ptr [bp-14],large 180
	jl	short @104@142
	mov	dword ptr [bp-14],large -60
	jmp	short @104@153
@104@148:
	cmp	dword ptr [bp-14],large 0
	je	short @104@152
	mov	eax,dword ptr [bp-14]
	imul	eax,large 360
	movzx	edx,word ptr DGROUP:_ptr
	add	eax,edx
	mov	dword ptr [bp-18],eax
	cmp	dword ptr [bp-18],large 0
	jle	short @104@152
	cmp	dword ptr [bp-18],large 0FD20h
	jge	short @104@152
	les	bx,dword ptr DGROUP:_p_background
	add	bx,word ptr [bp-18]
	mov	di,bx
	mov	al,byte ptr es:[bx]
	xor	al,30
	mov	byte ptr es:[di],al
@104@152:
	inc	dword ptr [bp-14]
@104@153:
	cmp	dword ptr [bp-14],large 60
	jl	short @104@148
	jmp	@104@160
@104@155:
	push	word ptr [bp-36]
	push	cs
	call	near ptr @cplx_planet_viewpoint$qi
	add	sp,2
	mov	dx,124
	sub	dx,ax
	mov	word ptr [bp-40],dx
	cmp	word ptr [bp-40],0
	jge	short @104@157
	add	word ptr [bp-40],360
@104@157:
	cmp	word ptr [bp-40],359
	jle	short @104@159
	sub	word ptr [bp-40],360
@104@159:
	push	127
	push	130
	push	word ptr [bp-40]
	mov	bx,word ptr [bp-36]
	shl	bx,3
	fld	qword ptr DGROUP:_nearstar_p_ray[bx]
	sub	sp,4
	fstp	dword ptr [bp-140]
	fld	qword ptr DGROUP:_plz
	sub	sp,8
	fstp	qword ptr [bp-148]
	fld	qword ptr DGROUP:_ply
	sub	sp,8
	fstp	qword ptr [bp-156]
	fld	qword ptr DGROUP:_plx
	sub	sp,8
	fstp	qword ptr [bp-164]
	push	22586
	fwait	
	push	dword ptr DGROUP:_n_globes_map
	push	dword ptr DGROUP:_adapted
	push	word ptr [bp-44]
	push	cs
	call	near ptr @glowinglobe$qinuct2uidddfiiuc
	add	sp,46
@104@160:
	cmp	byte ptr [bp-109],0
	je	@104@164
	mov	bx,word ptr [bp-36]
	shl	bx,3
	fld	qword ptr DGROUP:_nearstar_p_ring[bx]
	fldz	
	fcompp
	fstsw	word ptr [bp-116]
	fwait	
	mov	ax,word ptr [bp-116]
	sahf	
	je	@104@164
	push	word ptr [bp-112]
	push	word ptr [bp-44]
	fld	qword ptr DGROUP:_plz
	sub	sp,8
	fstp	qword ptr [bp-142]
	fld	qword ptr DGROUP:_ply
	sub	sp,8
	fstp	qword ptr [bp-150]
	fld	qword ptr DGROUP:_plx
	sub	sp,8
	fstp	qword ptr [bp-158]
	fwait	
	push	word ptr [bp-36]
	push	cs
	call	near ptr @ring$qidddii
	add	sp,30
	cmp	byte ptr [bp-108],0
	jne	short @104@164
	push	0
	mov	bx,word ptr [bp-36]
	shl	bx,3
	fld	qword ptr DGROUP:_nearstar_p_ray[bx]
	sub	sp,8
	fstp	qword ptr [bp-140]
	fld	qword ptr DGROUP:_plz
	sub	sp,8
	fstp	qword ptr [bp-148]
	fld	qword ptr DGROUP:_ply
	sub	sp,8
	fstp	qword ptr [bp-156]
	fld	qword ptr DGROUP:_plx
	sub	sp,8
	fstp	qword ptr [bp-164]
	fwait	
	push	cs
	call	near ptr @far_pixel_at$qdddduc
	add	sp,34
@104@164:
	add	word ptr [bp-124],2
	inc	word ptr [bp-34]
@104@166:
	mov	ax,word ptr [bp-34]
	cmp	ax,word ptr DGROUP:_nearstar_nob
	jl	@104@23
	mov	eax,dword ptr [bp-8]
	mov	dword ptr DGROUP:_p_background,eax
@104@168:
	pop	di
	pop	si
	leave	
	ret	
@planets$qv	endp
NOCTIS-0_TEXT	ends
_BSS	segment word public use16 'BSS'
_laststar_x	label	qword
	db	8 dup (?)
_laststar_y	label	qword
	db	8 dup (?)
_laststar_z	label	qword
	db	8 dup (?)
_BSS	ends
NOCTIS-0_TEXT	segment byte public use16 'CODE'
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@isthere$qd	proc	far
	push	bp
	mov	bp,sp
	sub	sp,54
	mov	byte ptr [bp-1],9
	mov	dword ptr [bp-22],large 0000186A0h
	fld	qword ptr [bp+6]
	fsub	qword ptr DGROUP:_idscale
	fstp	qword ptr [bp-30]
	fld	qword ptr [bp+6]
	fadd	qword ptr DGROUP:_idscale
	fstp	qword ptr [bp-38]
	fwait	
	mov	al,byte ptr [bp-1]
	cbw	
	cwde	
	imul	eax,large 0C350h
	mov	dword ptr [bp-54],eax
	fild	dword ptr [bp-54]
	fsubr	qword ptr DGROUP:_dzat_x
	fdiv	dword ptr DGROUP:s@+1598
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	dword ptr [bp-6],eax
	imul	eax,large 0000186A0h
	mov	dword ptr [bp-6],eax
	mov	al,byte ptr [bp-1]
	cbw	
	cwde	
	imul	eax,large 0C350h
	mov	dword ptr [bp-54],eax
	fild	dword ptr [bp-54]
	fsubr	qword ptr DGROUP:_dzat_y
	fdiv	dword ptr DGROUP:s@+1598
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	dword ptr [bp-10],eax
	imul	eax,large 0000186A0h
	mov	dword ptr [bp-10],eax
	mov	al,byte ptr [bp-1]
	cbw	
	cwde	
	imul	eax,large 0C350h
	mov	dword ptr [bp-54],eax
	fild	dword ptr [bp-54]
	fsubr	qword ptr DGROUP:_dzat_z
	fdiv	dword ptr DGROUP:s@+1598
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	dword ptr [bp-14],eax
	imul	eax,large 0000186A0h
	mov	dword ptr [bp-14],eax
	cmp	byte ptr DGROUP:_field_amplificator,0
	je	short @105@3
	mov	byte ptr [bp-1],14
@105@3:
	mov	al,byte ptr [bp-1]
	cbw	
	cwde	
	imul	eax,large 0000186A0h
	mov	dword ptr [bp-18],eax
   	les	 ax, dword ptr DGROUP:_adapted
	mov	 al, [bp-1]
	mov	 [bp-39], al 
@105@7:
   	mov	 al, [bp-1]
	mov	 [bp-40], al 
@105@9:
   	mov	 al, [bp-1]
	mov	 [bp-41], al 
@105@11:
   	db	 066H, 0BBH, 050H, 0C3H, 000H, 000H 
	db	 066H
	mov	 ax, word ptr [bp-6]
	db	 066H
	mov	 dx, word ptr [bp-14]
	db	 066H
	add	 ax, dx
	db	 066H
	mov	 cx, ax
	db	 066H
	mov	 dx, ax
	db	 066H, 081H, 0E2H, 0FFH, 0FFH, 001H, 000H 
	db	 066H
	add	 dx, word ptr [bp-6]
	db	 066H
	sub	 dx, bx
	db	 066H
	mov	 word ptr DGROUP:_laststar_x, dx
	db	 066H
	imul	 dx
	db	 066H
	add	 dx, ax
	db	 066H
	add	 cx, dx
	db	 066H, 081H, 0E2H, 0FFH, 0FFH, 001H, 000H 
	db	 066H
	add	 dx, word ptr [bp-10]
	db	 066H
	sub	 dx, bx
	db	 066H
	mov	 word ptr DGROUP:_laststar_y, dx
	db	 066H
	mov	 ax, cx
	db	 066H
	imul	 dx
	db	 066H
	add	 dx, ax
	db	 066H, 081H, 0E2H, 0FFH, 0FFH, 001H, 000H 
	db	 066H
	add	 dx, word ptr [bp-14]
	db	 066H
	sub	 dx, bx
	db	 066H
	mov	 word ptr DGROUP:_laststar_z, dx
	fild	 dword ptr DGROUP:_laststar_x
	fst	  DGROUP:_laststar_x
	fmul	 DGROUP:_idscale
	fild	 dword ptr DGROUP:_laststar_y
	fst	  DGROUP:_laststar_y
	fmul	 DGROUP:_idscale
	fild	 dword ptr DGROUP:_laststar_z
	fst	  DGROUP:_laststar_z
	fmul	 DGROUP:_idscale
	fmulp	
	fmulp	
	fst	 [bp-50]
	fcomp	 [bp-30]
	fstsw	 ax
	sahf	
	jb	short @105@76
	fld	 [bp-50]
	fcomp	 [bp-38]
	fstsw	 ax
	sahf	
	jb	short @105@100
@105@76:
   	db	 066H
	mov	 ax, word ptr [bp-22]
	db	 066H
	add	 word ptr [bp-14], ax
	dec	 [bp-41]
	je	short @105@83
	jmp	@105@11
@105@83:
 	db	 066H
	mov	 dx, word ptr [bp-18]
	db	 066H
	sub	 word ptr [bp-14], dx
	db	 066H
	add	 word ptr [bp-10], ax
	dec	 [bp-40]
	je	short @105@92
	jmp	@105@9
@105@92:
 	db	 066H
	sub	 word ptr [bp-10], dx
	db	 066H
	add	 word ptr [bp-6], ax
	dec	 [bp-39]
	je	short @105@99
	jmp	@105@7
@105@99:
	mov	al,0
	leave	
	ret	
@105@100:
	mov	al,1
	leave	
	ret	
@isthere$qd	endp
NOCTIS-0_TEXT	ends
_DATA	segment word public use16 'DATA'
_tgt_collect_lastpos	label	dword
	db	0
	db	0
	db	0
	db	0
_targets	label	word
	db	0
	db	0
_topmost_target	label	word
	db	0
	db	0
_target_line	label	word
	db	0
	db	0
_update_targets	label	byte
	db	0
_collecting_targets	label	byte
	db	0
_DATA	ends
_BSS	segment word public use16 'BSS'
_targets_table_id	label	qword
	db	400 dup (?)
_targets_table_px	label	qword
	db	400 dup (?)
_targets_table_py	label	qword
	db	400 dup (?)
_targets_table_pz	label	qword
	db	400 dup (?)
_BSS	ends
NOCTIS-0_TEXT	segment byte public use16 'CODE'
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@collect_targets$qv	proc	far
	push	bp
	mov	bp,sp
	sub	sp,16
	push	si
	push	di
	mov	eax,dword ptr DGROUP:_p_surfacemap
	mov	dword ptr [bp-12],eax
	mov	dword ptr [bp-16],eax
	push	0
	push	dword ptr DGROUP:_starmap_file
	call	far ptr __rtl_open
	add	sp,6
	mov	word ptr [bp-2],ax
	cmp	word ptr [bp-2],-1
	jle	@106@23
	mov	word ptr [bp-8],160
	jmp	@106@21
@106@3:
	push	0
	push	dword ptr DGROUP:_tgt_collect_lastpos
	push	word ptr [bp-2]
	call	far ptr _lseek
	add	sp,8
	push	word ptr [bp-8]
	push	dword ptr [bp-12]
	push	word ptr [bp-2]
	call	far ptr __rtl_read
	add	sp,8
	mov	word ptr [bp-4],ax
	cmp	word ptr [bp-4],0
	jne	short @106@5
	mov	byte ptr DGROUP:_collecting_targets,0
	jmp	@106@22
@106@5:
	xor	di,di
	mov	word ptr [bp-6],0
	mov	word ptr [bp-8],0
	xor	si,si
	jmp	@106@20
@106@7:
	lea	ax,word ptr [di+29]
	les	bx,dword ptr [bp-12]
	add	bx,ax
	mov	al,byte ptr es:[bx]
	cbw	
	cmp	ax,83
	jne	@106@16
	les	bx,dword ptr [bp-16]
	add	bx,si
	fld	qword ptr es:[bx]
	sub	sp,8
	fstp	qword ptr [bp-28]
	fwait	
	push	cs
	call	near ptr @isthere$qd
	add	sp,8
	or	al,al
	je	@106@17
	les	bx,dword ptr [bp-16]
	add	bx,si
	fld	qword ptr es:[bx]
	mov	bx,word ptr DGROUP:_targets
	shl	bx,3
	fstp	qword ptr DGROUP:_targets_table_id[bx]
	fwait	
	mov	bx,word ptr DGROUP:_targets
	shl	bx,3
	fld	qword ptr DGROUP:_laststar_x
	fstp	qword ptr DGROUP:_targets_table_px[bx]
	fwait	
	mov	bx,word ptr DGROUP:_targets
	shl	bx,3
	fld	qword ptr DGROUP:_laststar_y
	fstp	qword ptr DGROUP:_targets_table_py[bx]
	fwait	
	mov	bx,word ptr DGROUP:_targets
	shl	bx,3
	fld	qword ptr DGROUP:_laststar_z
	fstp	qword ptr DGROUP:_targets_table_pz[bx]
	fwait	
	cmp	word ptr DGROUP:_targets,3
	jge	short @106@11
	mov	ax,word ptr DGROUP:_targets
	mov	word ptr DGROUP:_target_line,ax
	jmp	short @106@12
@106@11:
	mov	word ptr DGROUP:_target_line,2
@106@12:
	cmp	word ptr DGROUP:_targets,2
	jle	short @106@14
	mov	ax,word ptr DGROUP:_targets
	add	ax,-2
	mov	word ptr DGROUP:_topmost_target,ax
@106@14:
	mov	byte ptr DGROUP:_update_targets,1
	inc	word ptr DGROUP:_targets
	cmp	word ptr DGROUP:_targets,50
	jne	short @106@17
	mov	byte ptr DGROUP:_collecting_targets,0
	jmp	short @106@22
@106@16:
	add	word ptr [bp-8],32
@106@17:
	add	di,32
	add	si,32
	add	word ptr [bp-6],4
	add	dword ptr DGROUP:_tgt_collect_lastpos,large 32
@106@20:
	cmp	di,word ptr [bp-4]
	jb	@106@7
@106@21:
	cmp	word ptr [bp-8],0
	jne	@106@3
@106@22:
	push	word ptr [bp-2]
	call	far ptr __rtl_close
	add	sp,2
@106@23:
	pop	di
	pop	si
	leave	
	ret	
@collect_targets$qv	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@status$qnci	proc	far
	push	bp
	mov	bp,sp
	push	si
	push	di
	mov	dx,word ptr [bp+10]
	cmp	dx,word ptr DGROUP:_fcs_status_delay
	jl	short @107@3
	push	ds
	pop	es
	mov	di,offset DGROUP:_fcs_status
	push	es
	mov	es,word ptr [bp+8]
	push	di
	mov	di,word ptr [bp+6]
	xor	ax,ax
	mov	cx,0FFFFh
	repnz 	scasb	
	not	cx
	sub	di,cx
	shr	cx,1
	mov	ax,word ptr [bp+8]
	mov	si,word ptr [bp+6]
	pop	di
	pop	es
	push	ds
	mov	ds,ax
	rep 	movsw	
	adc	cx,cx
	rep 	movsb	
	pop	ds
	mov	word ptr DGROUP:_fcs_status_delay,dx
@107@3:
	pop	di
	pop	si
	pop	bp
	ret	
@status$qnci	endp
NOCTIS-0_TEXT	ends
_DATA	segment word public use16 'DATA'
_digimap	label	byte
	db	0
	db	0
	db	0
	db	0
	db	0
	db	2
	db	2
	db	2
	db	0
	db	2
	db	5
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	3
	db	5
	db	5
	db	2
	db	2
	db	6
	db	2
	db	2
	db	1
	db	4
	db	2
	db	1
	db	4
	db	0
	db	0
	db	2
	db	0
	db	0
	db	0
	db	2
	db	2
	db	0
	db	0
	db	4
	db	2
	db	2
	db	2
	db	4
	db	1
	db	2
	db	2
	db	2
	db	1
	db	0
	db	0
	db	7
	db	2
	db	2
	db	0
	db	2
	db	7
	db	2
	db	0
	db	0
	db	0
	db	0
	db	2
	db	1
	db	0
	db	0
	db	7
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	2
	db	0
	db	4
	db	2
	db	1
	db	0
	db	7
	db	5
	db	5
	db	5
	db	7
	db	3
	db	2
	db	2
	db	2
	db	7
	db	7
	db	4
	db	7
	db	1
	db	7
	db	7
	db	4
	db	6
	db	4
	db	7
	db	4
	db	6
	db	5
	db	7
	db	4
	db	7
	db	1
	db	7
	db	4
	db	7
	db	7
	db	1
	db	7
	db	5
	db	7
	db	7
	db	4
	db	4
	db	4
	db	4
	db	7
	db	5
	db	7
	db	5
	db	7
	db	7
	db	5
	db	7
	db	4
	db	4
	db	0
	db	2
	db	0
	db	2
	db	0
	db	0
	db	2
	db	0
	db	2
	db	1
	db	4
	db	2
	db	1
	db	2
	db	4
	db	0
	db	7
	db	0
	db	7
	db	0
	db	1
	db	2
	db	4
	db	2
	db	1
	db	7
	db	4
	db	6
	db	0
	db	2
	db	0
	db	2
	db	0
	db	0
	db	0
	db	7
	db	5
	db	7
	db	5
	db	5
	db	7
	db	5
	db	3
	db	5
	db	7
	db	7
	db	1
	db	1
	db	1
	db	7
	db	3
	db	5
	db	5
	db	5
	db	3
	db	7
	db	1
	db	3
	db	1
	db	7
	db	7
	db	1
	db	3
	db	1
	db	1
	db	7
	db	1
	db	5
	db	5
	db	7
	db	5
	db	5
	db	7
	db	5
	db	5
	db	2
	db	2
	db	2
	db	2
	db	2
	db	4
	db	4
	db	4
	db	5
	db	7
	db	5
	db	5
	db	3
	db	5
	db	5
	db	1
	db	1
	db	1
	db	1
	db	7
	db	7
	db	7
	db	5
	db	5
	db	5
	db	5
	db	7
	db	7
	db	5
	db	5
	db	7
	db	5
	db	5
	db	5
	db	7
	db	7
	db	5
	db	7
	db	1
	db	1
	db	7
	db	5
	db	5
	db	1
	db	5
	db	7
	db	5
	db	3
	db	5
	db	5
	db	7
	db	1
	db	7
	db	4
	db	7
	db	7
	db	2
	db	2
	db	2
	db	2
	db	5
	db	5
	db	5
	db	5
	db	7
	db	5
	db	5
	db	5
	db	5
	db	2
	db	5
	db	5
	db	7
	db	7
	db	5
	db	5
	db	5
	db	2
	db	5
	db	5
	db	5
	db	5
	db	7
	db	2
	db	2
	db	7
	db	4
	db	2
	db	1
	db	7
	db	0
	db	0
	db	6
	db	2
	db	2
	db	1
	db	3
	db	7
	db	3
	db	1
	db	2
	db	2
	db	6
	db	0
	db	0
	db	2
	db	2
	db	2
	db	2
	db	2
	db	0
	db	0
	db	0
	db	0
	db	7
	db	1
	db	2
	db	0
	db	0
	db	0
_DATA	ends
_BSS	segment word public use16 'BSS'
_digimap2	label	dword
	db	4 dup (?)
_BSS	ends
_DATA	segment word public use16 'DATA'
	db	1 dup (0)
_cupsize	label	dword
	db	0
	db	0
	db	225
	db	68
_cupheight	label	dword
	db	0
	db	96
	db	208
	db	68
_DATA	ends
NOCTIS-0_TEXT	segment byte public use16 'CODE'
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@cupola$qff	proc	far
	push	bp
	mov	bp,sp
	sub	sp,54
	mov	dword ptr [bp-24],large 03E20D97Ch
	mov	dword ptr [bp-28],large 03EA0D97Ch
	fld	dword ptr [bp-28]
	fdiv	dword ptr DGROUP:s@+12
	fstp	dword ptr [bp-32]
	fwait	
	mov	dword ptr [bp-20],large 0
	jmp	@108@9
@108@2:
	fld	dword ptr [bp-20]
	fadd	dword ptr [bp-28]
	fstp	dword ptr [bp-36]
	fld	dword ptr [bp-36]
	sub	sp,8
	fstp	qword ptr [bp-62]
	fwait	
	call	far ptr _cos
	add	sp,8
	fstp	dword ptr [bp-48]
	fld	dword ptr [bp-36]
	sub	sp,8
	fstp	qword ptr [bp-62]
	fwait	
	call	far ptr _sin
	add	sp,8
	fstp	dword ptr [bp-52]
	fld	dword ptr [bp-20]
	sub	sp,8
	fstp	qword ptr [bp-62]
	fwait	
	call	far ptr _cos
	add	sp,8
	fstp	dword ptr [bp-40]
	fld	dword ptr [bp-20]
	sub	sp,8
	fstp	qword ptr [bp-62]
	fwait	
	call	far ptr _sin
	add	sp,8
	fstp	dword ptr [bp-44]
	fwait	
	mov	eax,dword ptr [bp-24]
	mov	dword ptr [bp-16],eax
	jmp	@108@5
@108@3:
	fld	dword ptr [bp-16]
	fadd	dword ptr [bp-24]
	sub	sp,8
	fstp	qword ptr [bp-62]
	fwait	
	call	far ptr _sin
	add	sp,8
	fmul	dword ptr DGROUP:_cupsize
	fstp	dword ptr [bp-4]
	fld	dword ptr [bp-16]
	sub	sp,8
	fstp	qword ptr [bp-62]
	fwait	
	call	far ptr _cos
	add	sp,8
	fld	dword ptr DGROUP:_cupheight
	fchs	
	fmul	
	fmul	dword ptr [bp+6]
	fstp	dword ptr [bp-8]
	fld	dword ptr [bp-16]
	sub	sp,8
	fstp	qword ptr [bp-62]
	fwait	
	call	far ptr _sin
	add	sp,8
	fmul	dword ptr DGROUP:_cupsize
	fstp	dword ptr [bp-12]
	fld	dword ptr [bp-4]
	fmul	dword ptr [bp-44]
	sub	sp,4
	fstp	dword ptr [bp-58]
	fld	dword ptr [bp-16]
	fadd	dword ptr [bp-24]
	sub	sp,8
	fstp	qword ptr [bp-66]
	fwait	
	call	far ptr _cos
	add	sp,8
	fld	dword ptr DGROUP:_cupheight
	fchs	
	fmul	
	fmul	dword ptr [bp+6]
	sub	sp,4
	fstp	dword ptr [bp-62]
	fld	dword ptr [bp-4]
	fmul	dword ptr [bp-40]
	sub	sp,4
	fstp	dword ptr [bp-66]
	fld	dword ptr [bp-12]
	fmul	dword ptr [bp-44]
	sub	sp,4
	fstp	dword ptr [bp-70]
	fwait	
	push	dword ptr [bp-8]
	fld	dword ptr [bp-12]
	fmul	dword ptr [bp-40]
	sub	sp,4
	fstp	dword ptr [bp-78]
	fwait	
	push	cs
	call	near ptr @stick3d$qffffff
	add	sp,24
	fld	dword ptr [bp-12]
	fmul	dword ptr [bp-52]
	sub	sp,4
	fstp	dword ptr [bp-58]
	fwait	
	push	dword ptr [bp-8]
	fld	dword ptr [bp-12]
	fmul	dword ptr [bp-48]
	sub	sp,4
	fstp	dword ptr [bp-66]
	fld	dword ptr [bp-12]
	fmul	dword ptr [bp-44]
	sub	sp,4
	fstp	dword ptr [bp-70]
	fwait	
	push	dword ptr [bp-8]
	fld	dword ptr [bp-12]
	fmul	dword ptr [bp-40]
	sub	sp,4
	fstp	dword ptr [bp-78]
	fwait	
	push	cs
	call	near ptr @stick3d$qffffff
	add	sp,24
	fld	dword ptr [bp-24]
	fadd	dword ptr [bp-16]
	fstp	dword ptr [bp-16]
	fwait	
@108@5:
	fld	dword ptr [bp+10]
	fmul	dword ptr [bp-24]
	fcomp	dword ptr [bp-16]
	fstsw	word ptr [bp-54]
	fwait	
	mov	ax,word ptr [bp-54]
	sahf	
	ja	@108@3
	mov	al,byte ptr DGROUP:_gburst
	cbw	
	cmp	ax,1
	jle	@108@8
	mov	al,byte ptr DGROUP:_gburst
	cbw	
	mov	word ptr [bp-54],ax
	fild	word ptr [bp-54]
	fdiv	dword ptr DGROUP:s@+1754
	fmul	qword ptr DGROUP:s@+1978
	fstp	dword ptr [bp-16]
	push	large 000010001h
	push	0
	push	1
	push	10
	fld	qword ptr DGROUP:s@+1986
	sub	sp,8
	fstp	qword ptr [bp-72]
	fld	dword ptr [bp-16]
	sub	sp,8
	fstp	qword ptr [bp-80]
	fwait	
	call	far ptr _sin
	add	sp,8
	fld	dword ptr DGROUP:_cupsize
	fmul	dword ptr [bp-44]
	fmul	
	sub	sp,8
	fstp	qword ptr [bp-80]
	fld	dword ptr [bp-16]
	sub	sp,8
	fstp	qword ptr [bp-88]
	fwait	
	call	far ptr _cos
	add	sp,8
	fld	dword ptr DGROUP:_cupheight
	fchs	
	fmul	
	sub	sp,8
	fstp	qword ptr [bp-88]
	fld	dword ptr [bp-16]
	sub	sp,8
	fstp	qword ptr [bp-96]
	fwait	
	call	far ptr _sin
	add	sp,8
	fld	dword ptr DGROUP:_cupsize
	fmul	dword ptr [bp-40]
	fmul	
	sub	sp,8
	fstp	qword ptr [bp-96]
	fld	dword ptr DGROUP:_cam_z
	sub	sp,8
	fstp	qword ptr [bp-104]
	fld	dword ptr DGROUP:_cam_y
	sub	sp,8
	fstp	qword ptr [bp-112]
	fld	dword ptr DGROUP:_cam_x
	sub	sp,8
	fstp	qword ptr [bp-120]
	fwait	
	push	cs
	call	near ptr @lens_flares_for$qdddddddiccii
	add	sp,66
	mov	byte ptr DGROUP:_flares,0
@108@8:
	fld	dword ptr [bp-28]
	fadd	dword ptr [bp-20]
	fstp	dword ptr [bp-20]
	fwait	
@108@9:
	fld	dword ptr [bp-20]
	fld	dword ptr [bp-32]
	fsubr	qword ptr DGROUP:s@+1510
	fcompp
	fstsw	word ptr [bp-54]
	fwait	
	mov	ax,word ptr [bp-54]
	sahf	
	ja	@108@2
	leave	
	ret	
@cupola$qff	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@polycupola$qfc	proc	far
	push	bp
	mov	bp,sp
	sub	sp,106
	mov	dword ptr [bp-28],large 03E20D97Ch
	mov	dword ptr [bp-32],large 03EA0D97Ch
	fld	dword ptr [bp-32]
	fdiv	dword ptr DGROUP:s@+12
	fstp	dword ptr [bp-36]
	fwait	
	cmp	byte ptr [bp+10],0
	je	short @109@3
	push	4
	jmp	short @109@4
@109@3:
	push	2
@109@4:
	push	cs
	call	near ptr @setfx$qc
	add	sp,2
	mov	dword ptr [bp-24],large 0
	jmp	@109@24
@109@6:
	fld	dword ptr [bp-24]
	fadd	dword ptr [bp-32]
	fstp	dword ptr [bp-40]
	fld	dword ptr [bp-40]
	sub	sp,8
	fstp	qword ptr [bp-114]
	fwait	
	call	far ptr _cos
	add	sp,8
	fstp	dword ptr [bp-52]
	fld	dword ptr [bp-40]
	sub	sp,8
	fstp	qword ptr [bp-114]
	fwait	
	call	far ptr _sin
	add	sp,8
	fstp	dword ptr [bp-56]
	fld	dword ptr [bp-24]
	sub	sp,8
	fstp	qword ptr [bp-114]
	fwait	
	call	far ptr _cos
	add	sp,8
	fstp	dword ptr [bp-44]
	fld	dword ptr [bp-24]
	sub	sp,8
	fstp	qword ptr [bp-114]
	fwait	
	call	far ptr _sin
	add	sp,8
	fstp	dword ptr [bp-48]
	fwait	
	mov	eax,dword ptr [bp-28]
	mov	dword ptr [bp-20],eax
	jmp	@109@22
@109@7:
	fld	dword ptr [bp-20]
	fadd	dword ptr [bp-28]
	sub	sp,8
	fstp	qword ptr [bp-114]
	fwait	
	call	far ptr _sin
	add	sp,8
	fmul	dword ptr DGROUP:_cupsize
	fstp	dword ptr DGROUP:_xx
	fld	dword ptr [bp-20]
	sub	sp,8
	fstp	qword ptr [bp-114]
	fwait	
	call	far ptr _cos
	add	sp,8
	fld	dword ptr DGROUP:_cupheight
	fchs	
	fmul	
	fmul	dword ptr [bp+6]
	fstp	dword ptr DGROUP:_yy
	fld	dword ptr [bp-20]
	sub	sp,8
	fstp	qword ptr [bp-114]
	fwait	
	call	far ptr _sin
	add	sp,8
	fmul	dword ptr DGROUP:_cupsize
	fstp	dword ptr DGROUP:_zz
	fld	dword ptr DGROUP:_zz
	fmul	dword ptr [bp-44]
	fstp	dword ptr [bp-74]
	fwait	
	mov	eax,dword ptr DGROUP:_yy
	mov	dword ptr [bp-90],eax
	fld	dword ptr DGROUP:_zz
	fmul	dword ptr [bp-48]
	fstp	dword ptr [bp-106]
	fld	dword ptr DGROUP:_zz
	fmul	dword ptr [bp-52]
	fstp	dword ptr [bp-70]
	fwait	
	mov	dword ptr [bp-86],eax
	fld	dword ptr DGROUP:_zz
	fmul	dword ptr [bp-56]
	fstp	dword ptr [bp-102]
	fld	dword ptr DGROUP:_xx
	fmul	dword ptr [bp-52]
	fstp	dword ptr [bp-66]
	fld	dword ptr [bp-20]
	fadd	dword ptr [bp-28]
	sub	sp,8
	fstp	qword ptr [bp-114]
	fwait	
	call	far ptr _cos
	add	sp,8
	fld	dword ptr DGROUP:_cupheight
	fchs	
	fmul	
	fmul	dword ptr [bp+6]
	fstp	dword ptr [bp-82]
	fld	dword ptr DGROUP:_xx
	fmul	dword ptr [bp-56]
	fstp	dword ptr [bp-98]
	fld	dword ptr DGROUP:_xx
	fmul	dword ptr [bp-44]
	fstp	dword ptr [bp-62]
	fld	dword ptr [bp-20]
	fadd	dword ptr [bp-28]
	sub	sp,8
	fstp	qword ptr [bp-114]
	fwait	
	call	far ptr _cos
	add	sp,8
	fld	dword ptr DGROUP:_cupheight
	fchs	
	fmul	
	fmul	dword ptr [bp+6]
	fstp	dword ptr [bp-78]
	fld	dword ptr DGROUP:_xx
	fmul	dword ptr [bp-48]
	fstp	dword ptr [bp-94]
	fwait	
	cmp	byte ptr DGROUP:_ontheroof,0
	je	@109@14
	fld	dword ptr [bp+6]
	fld1	
	fcompp
	fstsw	word ptr [bp-58]
	fwait	
	mov	ax,word ptr [bp-58]
	sahf	
	jne	@109@14
	fld	dword ptr [bp-74]
	fadd	dword ptr [bp-70]
	fmul	dword ptr DGROUP:s@+1582
	fsub	dword ptr DGROUP:_cam_x
	fstp	dword ptr [bp-4]
	fld	dword ptr [bp-106]
	fadd	dword ptr [bp-102]
	fmul	dword ptr DGROUP:s@+1582
	fsub	dword ptr DGROUP:_cam_z
	fstp	dword ptr [bp-8]
	fld	dword ptr [bp-4]
	fmul	dword ptr [bp-4]
	fld	dword ptr [bp-8]
	fmul	dword ptr [bp-8]
	fadd	
	sub	sp,8
	fstp	qword ptr [bp-114]
	fwait	
	call	far ptr _sqrt
	add	sp,8
	fsubr	dword ptr DGROUP:s@+1998
	fstp	dword ptr [bp-16]
	fld	dword ptr [bp-16]
	fcomp	dword ptr DGROUP:s@+2002
	fstsw	word ptr [bp-58]
	fwait	
	mov	ax,word ptr [bp-58]
	sahf	
	jbe	short @109@11
	mov	dword ptr [bp-16],large 044160000h
@109@11:
	fld	dword ptr [bp-16]
	fldz	
	fcompp
	fstsw	word ptr [bp-58]
	fwait	
	mov	ax,word ptr [bp-58]
	sahf	
	jbe	short @109@13
	mov	dword ptr [bp-16],large 0
@109@13:
	fld	dword ptr [bp-16]
	fadd	dword ptr DGROUP:_cam_y
	fstp	dword ptr DGROUP:_cam_y
	push	64
	push	4
	push	ss
	fwait	
	lea	ax,word ptr [bp-106]
	push	ax
	push	ss
	lea	ax,word ptr [bp-90]
	push	ax
	push	ss
	lea	ax,word ptr [bp-74]
	push	ax
	push	cs
	call	near ptr @poly3d$qnft1t1uiuc
	add	sp,16
	fld	dword ptr [bp-16]
	fsubr	dword ptr DGROUP:_cam_y
	fstp	dword ptr DGROUP:_cam_y
	fwait	
	jmp	@109@21
@109@14:
	cmp	byte ptr [bp+10],0
	je	@109@20
	fld	dword ptr [bp-74]
	fadd	dword ptr [bp-70]
	fmul	dword ptr DGROUP:s@+1582
	fsub	dword ptr DGROUP:_cam_x
	fstp	dword ptr [bp-4]
	fld	dword ptr [bp-90]
	fadd	dword ptr [bp-82]
	fmul	dword ptr DGROUP:s@+1582
	fsub	dword ptr DGROUP:_cam_y
	fstp	dword ptr [bp-8]
	fld	dword ptr [bp-106]
	fadd	dword ptr [bp-102]
	fmul	dword ptr DGROUP:s@+1582
	fsub	dword ptr DGROUP:_cam_z
	fstp	dword ptr [bp-12]
	fld	dword ptr [bp-4]
	fmul	dword ptr [bp-4]
	fld	dword ptr [bp-8]
	fmul	dword ptr [bp-8]
	fadd	
	fld	dword ptr [bp-12]
	fmul	dword ptr [bp-12]
	fadd	
	sub	sp,8
	fstp	qword ptr [bp-114]
	fwait	
	call	far ptr _sqrt
	add	sp,8
	fsubr	dword ptr DGROUP:s@+1830
	fstp	dword ptr [bp-16]
	fld	dword ptr [bp-16]
	fcomp	dword ptr DGROUP:s@+1830
	fstsw	word ptr [bp-58]
	fwait	
	mov	ax,word ptr [bp-58]
	sahf	
	jbe	short @109@17
	mov	dword ptr [bp-16],large 043FA0000h
@109@17:
	fld	dword ptr [bp-16]
	fldz	
	fcompp
	fstsw	word ptr [bp-58]
	fwait	
	mov	ax,word ptr [bp-58]
	sahf	
	jbe	short @109@19
	mov	dword ptr [bp-16],large 0
@109@19:
	fld	dword ptr DGROUP:s@+1910
	fmul	dword ptr [bp-16]
	fmul	dword ptr [bp+6]
	fadd	dword ptr DGROUP:_cam_y
	fstp	dword ptr DGROUP:_cam_y
	fwait	
	mov	eax,dword ptr [bp-62]
	mov	dword ptr DGROUP:_xx,eax
	mov	eax,dword ptr [bp-78]
	mov	dword ptr DGROUP:_yy,eax
	mov	eax,dword ptr [bp-94]
	mov	dword ptr DGROUP:_zz,eax
	mov	eax,dword ptr [bp-66]
	mov	dword ptr [bp-62],eax
	mov	eax,dword ptr [bp-82]
	mov	dword ptr [bp-78],eax
	mov	eax,dword ptr [bp-98]
	mov	dword ptr [bp-94],eax
	mov	eax,dword ptr [bp-70]
	mov	dword ptr [bp-66],eax
	mov	eax,dword ptr [bp-86]
	mov	dword ptr [bp-82],eax
	mov	eax,dword ptr [bp-102]
	mov	dword ptr [bp-98],eax
	mov	eax,dword ptr [bp-74]
	mov	dword ptr [bp-70],eax
	mov	eax,dword ptr [bp-90]
	mov	dword ptr [bp-86],eax
	mov	eax,dword ptr [bp-106]
	mov	dword ptr [bp-102],eax
	mov	eax,dword ptr DGROUP:_xx
	mov	dword ptr [bp-74],eax
	mov	eax,dword ptr DGROUP:_yy
	mov	dword ptr [bp-90],eax
	mov	eax,dword ptr DGROUP:_zz
	mov	dword ptr [bp-106],eax
	push	0
	push	4
	push	ss
	lea	ax,word ptr [bp-106]
	push	ax
	push	ss
	lea	ax,word ptr [bp-90]
	push	ax
	push	ss
	lea	ax,word ptr [bp-74]
	push	ax
	push	cs
	call	near ptr @polymap$qnft1t1cuc
	add	sp,16
	fld	dword ptr DGROUP:s@+1910
	fmul	dword ptr [bp-16]
	fmul	dword ptr [bp+6]
	fsubr	dword ptr DGROUP:_cam_y
	fstp	dword ptr DGROUP:_cam_y
	fwait	
	jmp	short @109@21
@109@20:
	push	64
	push	4
	push	ss
	lea	ax,word ptr [bp-106]
	push	ax
	push	ss
	lea	ax,word ptr [bp-90]
	push	ax
	push	ss
	lea	ax,word ptr [bp-74]
	push	ax
	push	cs
	call	near ptr @poly3d$qnft1t1uiuc
	add	sp,16
@109@21:
	fld	dword ptr [bp-28]
	fadd	dword ptr [bp-20]
	fstp	dword ptr [bp-20]
	fwait	
@109@22:
	fld	dword ptr DGROUP:s@+1994
	fmul	dword ptr [bp-28]
	fcomp	dword ptr [bp-20]
	fstsw	word ptr [bp-58]
	fwait	
	mov	ax,word ptr [bp-58]
	sahf	
	ja	@109@7
	fld	dword ptr [bp-32]
	fadd	dword ptr [bp-24]
	fstp	dword ptr [bp-24]
	fwait	
@109@24:
	fld	dword ptr [bp-24]
	fld	dword ptr [bp-36]
	fsubr	qword ptr DGROUP:s@+1510
	fcompp
	fstsw	word ptr [bp-58]
	fwait	
	mov	ax,word ptr [bp-58]
	sahf	
	ja	@109@6
	push	cs
	call	near ptr @resetfx$qv
	leave	
	ret	
@polycupola$qfc	endp
NOCTIS-0_TEXT	ends
_BSS	segment word public use16 'BSS'
_gtime	label	dword
	db	4 dup (?)
_BSS	ends
NOCTIS-0_TEXT	segment byte public use16 'CODE'
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@sync_start$qv	proc	far
	call	far ptr _clock
	mov	word ptr DGROUP:_gtime+2,dx
	mov	word ptr DGROUP:_gtime,ax
	ret	
@sync_start$qv	endp
@111@0:
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@sync_stop$qv	proc	far
	call	far ptr _clock
	shl	eax,16
	shrd	eax,edx,16
	cmp	eax,dword ptr DGROUP:_gtime
	je	short @111@0
	ret	
@sync_stop$qv	endp
NOCTIS-0_TEXT	ends
_BSS	segment word public use16 'BSS'
_global_surface_seed	label	dword
	db	4 dup (?)
_ppos_x	label	dword
	db	4 dup (?)
_ppos_y	label	dword
	db	4 dup (?)
_ppos_z	label	dword
	db	4 dup (?)
_dsd	label	qword
	db	8 dup (?)
_BSS	ends
NOCTIS-0_TEXT	segment byte public use16 'CODE'
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@load_starface$qv	proc	far
	push	bp
	mov	bp,sp
	sub	sp,2
	push	si
	push	di
	fld	qword ptr DGROUP:_nearstar_identity
	fmul	dword ptr DGROUP:s@+1974
	call	far ptr F_FTOL@
	mov	word ptr [bp-2],ax
   	les	 di, dword ptr DGROUP:_s_background
	mov	 cx, 64800
	mov	 ax, [bp-2] 
@112@5:
   	add	 ax, cx
	xor	 dx, dx
	imul	 ax
	add	 ax, dx
	mov	 bl, al
	and	 bl, 03EH
	mov	 es:[di], bl
	inc	 di
	dec	 cx
	jne	short @112@5
	movzx	eax,word ptr [bp-2]
	push	eax
	push	cs
	call	near ptr @fast_srand$ql
	add	sp,4
	push	large 3
	push	cs
	call	near ptr @fast_random$ql
	add	sp,4
	mov	si,ax
	cmp	word ptr DGROUP:_nearstar_class,11
	je	short @112@18
	cmp	word ptr DGROUP:_nearstar_class,7
	je	short @112@18
	cmp	word ptr DGROUP:_nearstar_class,2
	jne	short @112@20
@112@18:
	push	large 3
	push	cs
	call	near ptr @fast_random$ql
	add	sp,4
	add	ax,si
	add	ax,2
	mov	si,ax
	jmp	short @112@20
@112@19:
	push	dword ptr DGROUP:_s_background
	push	cs
	call	near ptr @ssmooth$qnuc
	add	sp,4
	dec	si
@112@20:
	or	si,si
	jne	short @112@19
	pop	di
	pop	si
	leave	
	ret	
@load_starface$qv	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@load_QVRmaps$qv	proc	far
	push	si
	push	large -29926
	push	cs
	call	near ptr @sa_open$ql
	add	sp,4
	mov	si,ax
	cmp	si,-1
	jle	short @113@3
	push	7340
	push	dword ptr DGROUP:_n_offsets_map
	push	ax
	call	far ptr __rtl_read
	add	sp,8
	push	si
	call	far ptr __rtl_close
	add	sp,2
@113@3:
	push	large -22586
	push	cs
	call	near ptr @sa_open$ql
	add	sp,4
	mov	si,ax
	cmp	si,-1
	jle	short @113@5
	push	22586
	push	dword ptr DGROUP:_n_globes_map
	push	ax
	call	far ptr __rtl_read
	add	sp,8
	push	si
	call	far ptr __rtl_close
	add	sp,2
@113@5:
	pop	si
	ret	
@load_QVRmaps$qv	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@load_digimap2$qv	proc	far
	push	si
	push	large 0FFFF1298h
	push	cs
	call	near ptr @sa_open$ql
	add	sp,4
	mov	si,ax
	cmp	si,-1
	jle	short @114@3
	push	9360
	push	dword ptr DGROUP:_digimap2
	push	ax
	call	far ptr __rtl_read
	add	sp,8
	push	si
	call	far ptr __rtl_close
	add	sp,2
@114@3:
	pop	si
	ret	
@load_digimap2$qv	endp
NOCTIS-0_TEXT	ends
_BSS	segment word public use16 'BSS'
_outhudbuffer	label	byte
	db	81 dup (?)
_BSS	ends
_DATA	segment word public use16 'DATA'
_compass	label	dword
	dd	DGROUP:s@+2006
_tp_gravity	label	dword
	db	0
	db	0
	db	128
	db	63
_pp_gravity	label	dword
	db	0
	db	0
	db	128
	db	63
_tp_temp	label	dword
	db	0
	db	0
	db	176
	db	65
_pp_temp	label	dword
	db	0
	db	0
	db	176
	db	65
_tp_pressure	label	dword
	db	0
	db	0
	db	128
	db	63
_pp_pressure	label	dword
	db	0
	db	0
	db	128
	db	63
_tp_pulse	label	dword
	db	0
	db	0
	db	236
	db	66
_pp_pulse	label	dword
	db	0
	db	0
	db	236
	db	66
_DATA	ends
NOCTIS-0_TEXT	segment byte public use16 'CODE'
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@wrouthud$quiuiuinc	proc	far
	push	bp
	mov	bp,sp
	sub	sp,12
	push	si
	push	di
	mov	word ptr [bp-4],0
	cmp	word ptr [bp+10],0
	jne	short @115@3
	mov	word ptr [bp+10],32767
@115@3:
	mov	ax,word ptr [bp+8]
	imul	ax,ax,320
	add	ax,word ptr [bp+6]
	mov	cx,ax
	jmp	@115@17
@115@4:
	mov	es,word ptr [bp+14]
	mov	bx,word ptr [bp-12]
	mov	al,byte ptr es:[bx]
	cbw	
	imul	ax,ax,5
	add	ax,-160
	mov	word ptr [bp-2],ax
	xor	di,di
	add	ax,offset DGROUP:_digimap
	mov	si,ax
@115@6:
	test	byte ptr [si],1
	je	short @115@8
	les	bx,dword ptr DGROUP:_adapted
	add	bx,cx
	mov	word ptr [bp-6],bx
	mov	al,191
	sub	al,byte ptr es:[bx]
	mov	byte ptr es:[bx],al
@115@8:
	test	byte ptr [si],2
	je	short @115@10
	mov	ax,cx
	inc	ax
	les	bx,dword ptr DGROUP:_adapted
	add	bx,ax
	mov	word ptr [bp-8],bx
	mov	al,191
	sub	al,byte ptr es:[bx]
	mov	dx,cx
	inc	dx
	mov	bx,word ptr DGROUP:_adapted
	add	bx,dx
	mov	byte ptr es:[bx],al
@115@10:
	test	byte ptr [si],4
	je	short @115@12
	mov	ax,cx
	add	ax,2
	les	bx,dword ptr DGROUP:_adapted
	add	bx,ax
	mov	word ptr [bp-10],bx
	mov	al,191
	sub	al,byte ptr es:[bx]
	mov	dx,cx
	add	dx,2
	mov	bx,word ptr DGROUP:_adapted
	add	bx,dx
	mov	byte ptr es:[bx],al
@115@12:
	add	cx,320
	inc	si
	inc	di
	cmp	di,5
	jl	short @115@6
	sub	cx,1600
	add	cx,4
	inc	word ptr [bp-4]
@115@17:
	les	bx,dword ptr [bp+12]
	add	bx,word ptr [bp-4]
	mov	word ptr [bp-12],bx
	cmp	byte ptr es:[bx],0
	je	short @115@19
	mov	ax,word ptr [bp-4]
	cmp	ax,word ptr [bp+10]
	jb	@115@4
@115@19:
	pop	di
	pop	si
	leave	
	ret	
@wrouthud$quiuiuinc	endp
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@surrounding$qci	proc	far
	push	bp
	mov	bp,sp
	sub	sp,26
	push	si
	push	di
	mov	dword ptr [bp-8],large 0
	jmp	short @116@4
@116@2:
	mov	al,byte ptr [bp-8]
	mov	dl,3
	mov	ah,0
	imul	dl
	add	al,byte ptr DGROUP:_surlight
	add	al,54
	push	ax
	push	large 00001012Ch
	push	large 0
	mov	ax,word ptr [bp+8]
	add	ax,9
	sub	ax,word ptr [bp-8]
	push	ax
	push	10
	push	dword ptr DGROUP:_adapted
	push	cs
	call	near ptr @areaclear$qnuciiiiiiuc
	add	sp,18
	inc	dword ptr [bp-8]
@116@4:
	cmp	dword ptr [bp-8],large 4
	jl	short @116@2
	mov	dword ptr [bp-8],large 0
	jmp	short @116@8
@116@6:
	mov	al,byte ptr DGROUP:_surlight
	add	al,64
	sub	al,byte ptr [bp-8]
	push	ax
	push	large 000010140h
	push	large 0
	mov	ax,9
	sub	ax,word ptr [bp-8]
	push	ax
	push	0
	push	dword ptr DGROUP:_adapted
	push	cs
	call	near ptr @areaclear$qnuciiiiiiuc
	add	sp,18
	inc	dword ptr [bp-8]
@116@8:
	cmp	dword ptr [bp-8],large 10
	jl	short @116@6
	mov	dword ptr [bp-8],large 0
	jmp	short @116@12
@116@10:
	mov	al,byte ptr DGROUP:_surlight
	add	al,64
	sub	al,byte ptr [bp-8]
	push	ax
	push	large 000010140h
	push	large 0
	mov	ax,word ptr [bp-8]
	add	ax,190
	push	ax
	push	0
	push	dword ptr DGROUP:_adapted
	push	cs
	call	near ptr @areaclear$qnuciiiiiiuc
	add	sp,18
	inc	dword ptr [bp-8]
@116@12:
	cmp	dword ptr [bp-8],large 10
	jl	short @116@10
	mov	dword ptr [bp-8],large 0
	jmp	short @116@16
@116@14:
	mov	al,byte ptr DGROUP:_surlight
	add	al,64
	sub	al,byte ptr [bp-8]
	push	ax
	push	large 000B40001h
	push	large 0
	push	10
	mov	ax,9
	sub	ax,word ptr [bp-8]
	push	ax
	push	dword ptr DGROUP:_adapted
	push	cs
	call	near ptr @areaclear$qnuciiiiiiuc
	add	sp,18
	inc	dword ptr [bp-8]
@116@16:
	cmp	dword ptr [bp-8],large 10
	jl	short @116@14
	mov	dword ptr [bp-8],large 0
	jmp	short @116@20
@116@18:
	mov	al,byte ptr DGROUP:_surlight
	add	al,64
	sub	al,byte ptr [bp-8]
	push	ax
	push	large 000B40001h
	push	large 0
	push	10
	mov	ax,word ptr [bp-8]
	add	ax,310
	push	ax
	push	dword ptr DGROUP:_adapted
	push	cs
	call	near ptr @areaclear$qnuciiiiiiuc
	add	sp,18
	inc	dword ptr [bp-8]
@116@20:
	cmp	dword ptr [bp-8],large 10
	jl	short @116@18
	mov	al,byte ptr DGROUP:_surlight
	cbw	
	mov	dx,ax
	add	dx,dx
	add	dx,ax
	add	dx,64
	movsx	eax,dx
	mov	dword ptr [bp-8],eax
	cmp	dword ptr [bp-8],large 127
	jle	short @116@23
	mov	dword ptr [bp-8],large 127
@116@23:
	mov	al,byte ptr [bp-8]
	push	ax
	push	large 000040004h
	push	large 0
	push	large 000090009h
	push	dword ptr DGROUP:_adapted
	push	cs
	call	near ptr @areaclear$qnuciiiiiiuc
	add	sp,18
	push	1
	push	large 5
	push	large 9
	push	large 9
	push	dword ptr DGROUP:_adapted
	push	cs
	call	near ptr @smootharound_64$qnuclllc
	add	sp,18
	mov	al,byte ptr [bp-8]
	push	ax
	push	large 000040004h
	push	large 0
	push	large 000090134h
	push	dword ptr DGROUP:_adapted
	push	cs
	call	near ptr @areaclear$qnuciiiiiiuc
	add	sp,18
	push	1
	push	large 5
	push	large 9
	push	large 308
	push	dword ptr DGROUP:_adapted
	push	cs
	call	near ptr @smootharound_64$qnuclllc
	add	sp,18
	mov	al,byte ptr [bp-8]
	push	ax
	push	large 000040004h
	push	large 0
	push	large 000BC0009h
	push	dword ptr DGROUP:_adapted
	push	cs
	call	near ptr @areaclear$qnuciiiiiiuc
	add	sp,18
	push	1
	push	large 5
	push	large 188
	push	large 9
	push	dword ptr DGROUP:_adapted
	push	cs
	call	near ptr @smootharound_64$qnuclllc
	add	sp,18
	mov	al,byte ptr [bp-8]
	push	ax
	push	large 000040004h
	push	large 0
	push	large 000BC0134h
	push	dword ptr DGROUP:_adapted
	push	cs
	call	near ptr @areaclear$qnuciiiiiiuc
	add	sp,18
	push	1
	push	large 5
	push	large 188
	push	large 308
	push	dword ptr DGROUP:_adapted
	push	cs
	call	near ptr @smootharound_64$qnuclllc
	add	sp,18
	push	word ptr DGROUP:_epoc
	push	ds
	push	offset DGROUP:s@+2075
	push	ds
	push	offset DGROUP:_outhudbuffer
	call	far ptr _sprintf
	add	sp,10
	fld	dword ptr DGROUP:s@+1810
	sub	sp,8
	fstp	qword ptr [bp-38]
	fld	qword ptr DGROUP:_secs
	sub	sp,8
	fstp	qword ptr [bp-46]
	fwait	
	call	far ptr _fmod
	add	sp,16
	fdiv	dword ptr DGROUP:s@+1970
	call	far ptr F_FTOL@
	mov	word ptr [bp-18],ax
	cmp	word ptr [bp-18],100
	jae	short @116@25
	push	ds
	pop	es
	mov	di,offset DGROUP:_outhudbuffer
	mov	si,offset DGROUP:s@+2086
	mov	cx,0FFFFh
	xor	ax,ax
	repnz 	scasb	
	dec	di
	mov	cx,2
	rep 	movsb	
@116@25:
	mov	ax,word ptr [bp-18]
	mov	word ptr [bp-22],ax
	mov	word ptr [bp-20],0
	fild	dword ptr [bp-22]
	sub	sp,8
	fstp	qword ptr [bp-38]
	fwait	
	push	cs
	call	near ptr @alphavalue$qd
	add	sp,8
	mov	bx,ds
	mov	si,offset DGROUP:_outhudbuffer
	mov	di,ax
	mov	es,dx
	xor	ax,ax
	mov	cx,0FFFFh
	repnz 	scasb	
	not	cx
	sub	di,cx
	push	ds
	mov	ds,bx
	xchg	si,di
	mov	ax,ds
	mov	bx,ax
	mov	ax,es
	mov	ds,ax
	mov	es,bx
	push	cx
	mov	cx,0FFFFh
	xor	ax,ax
	repnz 	scasb	
	dec	di
	pop	cx
	rep 	movsb	
	pop	ds
	push	ds
	pop	es
	mov	di,offset DGROUP:_outhudbuffer
	mov	si,offset DGROUP:s@+2088
	mov	cx,0FFFFh
	xor	ax,ax
	repnz 	scasb	
	dec	di
	mov	cx,2
	rep 	movsb	
	fld	dword ptr DGROUP:s@+1970
	sub	sp,8
	fstp	qword ptr [bp-38]
	fld	qword ptr DGROUP:_secs
	sub	sp,8
	fstp	qword ptr [bp-46]
	fwait	
	call	far ptr _fmod
	add	sp,16
	fdiv	dword ptr DGROUP:s@+1998
	call	far ptr F_FTOL@
	mov	word ptr [bp-24],ax
	cmp	word ptr [bp-24],100
	jae	short @116@27
	push	ds
	pop	es
	mov	di,offset DGROUP:_outhudbuffer
	mov	si,offset DGROUP:s@+2090
	mov	cx,0FFFFh
	xor	ax,ax
	repnz 	scasb	
	dec	di
	mov	cx,2
	rep 	movsb	
@116@27:
	mov	ax,word ptr [bp-24]
	mov	word ptr [bp-22],ax
	mov	word ptr [bp-20],0
	fild	dword ptr [bp-22]
	sub	sp,8
	fstp	qword ptr [bp-38]
	fwait	
	push	cs
	call	near ptr @alphavalue$qd
	add	sp,8
	mov	bx,ds
	mov	si,offset DGROUP:_outhudbuffer
	mov	di,ax
	mov	es,dx
	xor	ax,ax
	mov	cx,0FFFFh
	repnz 	scasb	
	not	cx
	sub	di,cx
	push	ds
	mov	ds,bx
	xchg	si,di
	mov	ax,ds
	mov	bx,ax
	mov	ax,es
	mov	ds,ax
	mov	es,bx
	push	cx
	mov	cx,0FFFFh
	xor	ax,ax
	repnz 	scasb	
	dec	di
	pop	cx
	rep 	movsb	
	pop	ds
	push	ds
	pop	es
	mov	di,offset DGROUP:_outhudbuffer
	mov	si,offset DGROUP:s@+2092
	mov	cx,0FFFFh
	xor	ax,ax
	repnz 	scasb	
	dec	di
	mov	cx,2
	rep 	movsb	
	fld	dword ptr DGROUP:s@+1998
	sub	sp,8
	fstp	qword ptr [bp-38]
	fld	qword ptr DGROUP:_secs
	sub	sp,8
	fstp	qword ptr [bp-46]
	fwait	
	call	far ptr _fmod
	add	sp,16
	call	far ptr F_FTOL@
	mov	word ptr [bp-26],ax
	cmp	word ptr [bp-26],100
	jae	short @116@29
	push	ds
	pop	es
	mov	di,offset DGROUP:_outhudbuffer
	mov	si,offset DGROUP:s@+2094
	mov	cx,0FFFFh
	xor	ax,ax
	repnz 	scasb	
	dec	di
	mov	cx,2
	rep 	movsb	
@116@29:
	mov	ax,word ptr [bp-26]
	mov	word ptr [bp-22],ax
	mov	word ptr [bp-20],0
	fild	dword ptr [bp-22]
	sub	sp,8
	fstp	qword ptr [bp-38]
	fwait	
	push	cs
	call	near ptr @alphavalue$qd
	add	sp,8
	mov	bx,ds
	mov	si,offset DGROUP:_outhudbuffer
	mov	di,ax
	mov	es,dx
	xor	ax,ax
	mov	cx,0FFFFh
	repnz 	scasb	
	not	cx
	sub	di,cx
	push	ds
	mov	ds,bx
	xchg	si,di
	mov	ax,ds
	mov	bx,ax
	mov	ax,es
	mov	ds,ax
	mov	es,bx
	push	cx
	mov	cx,0FFFFh
	xor	ax,ax
	repnz 	scasb	
	dec	di
	pop	cx
	rep 	movsb	
	pop	ds
	cmp	byte ptr [bp+6],0
	je	@116@33
	push	ds
	pop	es
	mov	di,offset DGROUP:_outhudbuffer
	mov	si,offset DGROUP:s@+2096
	mov	cx,0FFFFh
	xor	ax,ax
	repnz 	scasb	
	dec	di
	mov	cx,8
	rep 	movsb	
	mov	ax,word ptr DGROUP:_landing_pt_lon
	mov	word ptr [bp-22],ax
	fild	word ptr [bp-22]
	sub	sp,8
	fstp	qword ptr [bp-38]
	fwait	
	push	cs
	call	near ptr @alphavalue$qd
	add	sp,8
	mov	bx,ds
	mov	si,offset DGROUP:_outhudbuffer
	mov	di,ax
	mov	es,dx
	xor	ax,ax
	mov	cx,0FFFFh
	repnz 	scasb	
	not	cx
	sub	di,cx
	push	ds
	mov	ds,bx
	xchg	si,di
	mov	ax,ds
	mov	bx,ax
	mov	ax,es
	mov	ds,ax
	mov	es,bx
	push	cx
	mov	cx,0FFFFh
	xor	ax,ax
	repnz 	scasb	
	dec	di
	pop	cx
	rep 	movsb	
	pop	ds
	push	ds
	pop	es
	mov	di,offset DGROUP:_outhudbuffer
	mov	si,offset DGROUP:s@+2104
	mov	cx,0FFFFh
	xor	ax,ax
	repnz 	scasb	
	dec	di
	mov	cx,2
	rep 	movsb	
	mov	ax,word ptr DGROUP:_landing_pt_lat
	mov	word ptr [bp-22],ax
	fild	word ptr [bp-22]
	sub	sp,8
	fstp	qword ptr [bp-38]
	fwait	
	push	cs
	call	near ptr @alphavalue$qd
	add	sp,8
	mov	bx,ds
	mov	si,offset DGROUP:_outhudbuffer
	mov	di,ax
	mov	es,dx
	xor	ax,ax
	mov	cx,0FFFFh
	repnz 	scasb	
	not	cx
	sub	di,cx
	push	ds
	mov	ds,bx
	xchg	si,di
	mov	ax,ds
	mov	bx,ax
	mov	ax,es
	mov	ds,ax
	mov	es,bx
	push	cx
	mov	cx,0FFFFh
	xor	ax,ax
	repnz 	scasb	
	dec	di
	pop	cx
	rep 	movsb	
	pop	ds
	push	ds
	pop	es
	mov	di,offset DGROUP:_outhudbuffer
	mov	si,offset DGROUP:s@+2106
	mov	cx,0FFFFh
	xor	ax,ax
	repnz 	scasb	
	dec	di
	mov	cx,2
	rep 	movsb	
	fld	dword ptr DGROUP:_pos_x
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	sar	eax,14
	add	eax,large -100
	mov	dword ptr [bp-22],eax
	fild	dword ptr [bp-22]
	sub	sp,8
	fstp	qword ptr [bp-38]
	fwait	
	push	cs
	call	near ptr @alphavalue$qd
	add	sp,8
	mov	bx,ds
	mov	si,offset DGROUP:_outhudbuffer
	mov	di,ax
	mov	es,dx
	xor	ax,ax
	mov	cx,0FFFFh
	repnz 	scasb	
	not	cx
	sub	di,cx
	push	ds
	mov	ds,bx
	xchg	si,di
	mov	ax,ds
	mov	bx,ax
	mov	ax,es
	mov	ds,ax
	mov	es,bx
	push	cx
	mov	cx,0FFFFh
	xor	ax,ax
	repnz 	scasb	
	dec	di
	pop	cx
	rep 	movsb	
	pop	ds
	push	ds
	pop	es
	mov	di,offset DGROUP:_outhudbuffer
	mov	si,offset DGROUP:s@+2108
	mov	cx,0FFFFh
	xor	ax,ax
	repnz 	scasb	
	dec	di
	mov	cx,2
	rep 	movsb	
	fld	dword ptr DGROUP:_pos_z
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	sar	eax,14
	add	eax,large -100
	mov	dword ptr [bp-22],eax
	fild	dword ptr [bp-22]
	sub	sp,8
	fstp	qword ptr [bp-38]
	fwait	
	push	cs
	call	near ptr @alphavalue$qd
	add	sp,8
	mov	bx,ds
	mov	si,offset DGROUP:_outhudbuffer
	mov	di,ax
	mov	es,dx
	xor	ax,ax
	mov	cx,0FFFFh
	repnz 	scasb	
	not	cx
	sub	di,cx
	push	ds
	mov	ds,bx
	xchg	si,di
	mov	ax,ds
	mov	bx,ax
	mov	ax,es
	mov	ds,ax
	mov	es,bx
	push	cx
	mov	cx,0FFFFh
	xor	ax,ax
	repnz 	scasb	
	dec	di
	pop	cx
	rep 	movsb	
	pop	ds
	push	64
	push	large 000070005h
	push	large 0
	push	large 0000100FEh
	push	dword ptr DGROUP:_adapted
	push	cs
	call	near ptr @areaclear$qnuciiiiiiuc
	add	sp,18
	push	127
	push	large 000010001h
	push	large 0
	push	large 000080100h
	push	dword ptr DGROUP:_adapted
	push	cs
	call	near ptr @areaclear$qnuciiiiiiuc
	add	sp,18
	fld	dword ptr DGROUP:s@+1506
	fsub	dword ptr DGROUP:_user_beta
	fstp	dword ptr [bp-16]
	fld	dword ptr [bp-16]
	fcomp	dword ptr DGROUP:s@+1914
	fstsw	word ptr [bp-22]
	fwait	
	mov	ax,word ptr [bp-22]
	sahf	
	jbe	short @116@32
	fld	dword ptr DGROUP:s@+1506
	fsubr	dword ptr [bp-16]
	fstp	dword ptr [bp-16]
	fwait	
@116@32:
	fld	dword ptr [bp-16]
	fdiv	dword ptr DGROUP:s@+1758
	call	far ptr F_FTOL@
	mov	word ptr [bp-2],ax
	fld	dword ptr [bp-16]
	fmul	qword ptr DGROUP:s@+2110
	call	far ptr F_FTOL@
	mov	word ptr [bp-4],ax
	mov	ax,word ptr DGROUP:_compass
	add	ax,word ptr [bp-2]
	push	word ptr DGROUP:_compass+2
	push	ax
	push	large 0001C0002h
	mov	ax,word ptr [bp-4]
	mov	bx,4
	cwd	
	idiv	bx
	mov	ax,200
	sub	ax,dx
	push	ax
	push	cs
	call	near ptr @wrouthud$quiuiuinc
	add	sp,10
	jmp	@116@37
@116@33:
	cmp	byte ptr DGROUP:_ontheroof,0
	jne	@116@37
	push	ds
	pop	es
	mov	di,offset DGROUP:_outhudbuffer
	mov	si,offset DGROUP:s@+2118
	mov	cx,0FFFFh
	xor	ax,ax
	repnz 	scasb	
	dec	di
	mov	cx,4
	rep 	movsb	
	cmp	word ptr DGROUP:_sys,4
	jne	short @116@36
	mov	di,offset DGROUP:_outhudbuffer
	mov	si,offset DGROUP:s@+2122
	mov	cx,0FFFFh
	repnz 	scasb	
	dec	di
	mov	cx,51
	rep 	movsb	
	jmp	@116@37
@116@36:
	push	ds
	pop	es
	mov	di,offset DGROUP:_outhudbuffer
	xor	ax,ax
	mov	cx,0FFFFh
	repnz 	scasb	
	not	cx
	dec	cx
	mov	word ptr [bp-2],cx
	mov	bx,word ptr [bp-2]
	mov	byte ptr DGROUP:_outhudbuffer[bx],54
	mov	byte ptr DGROUP:_outhudbuffer[bx+1],92
	mov	di,word ptr [bp-2]
	add	di,offset DGROUP:_outhudbuffer+2
	mov	si,offset DGROUP:_ctb+20
	mov	cx,5
	rep 	movsw	
	mov	byte ptr DGROUP:_outhudbuffer[bx+12],32
	mov	byte ptr DGROUP:_outhudbuffer[bx+13],55
	mov	byte ptr DGROUP:_outhudbuffer[bx+14],92
	mov	di,word ptr [bp-2]
	add	di,offset DGROUP:_outhudbuffer+15
	mov	si,offset DGROUP:_ctb+47
	mov	cx,5
	rep 	movsw	
	mov	byte ptr DGROUP:_outhudbuffer[bx+25],32
	mov	byte ptr DGROUP:_outhudbuffer[bx+26],56
	mov	byte ptr DGROUP:_outhudbuffer[bx+27],92
	mov	di,word ptr [bp-2]
	add	di,offset DGROUP:_outhudbuffer+28
	mov	si,offset DGROUP:_ctb+74
	mov	cx,5
	rep 	movsw	
	mov	byte ptr DGROUP:_outhudbuffer[bx+38],32
	mov	byte ptr DGROUP:_outhudbuffer[bx+39],57
	mov	byte ptr DGROUP:_outhudbuffer[bx+40],92
	mov	di,word ptr [bp-2]
	add	di,offset DGROUP:_outhudbuffer+41
	mov	si,offset DGROUP:_ctb+101
	mov	cx,5
	rep 	movsw	
	mov	byte ptr DGROUP:_outhudbuffer[bx+51],0
	push	ds
	push	offset DGROUP:_outhudbuffer
	call	far ptr _strupr
	add	sp,4
@116@37:
	push	ds
	push	offset DGROUP:_outhudbuffer
	push	large 2
	push	2
	push	cs
	call	near ptr @wrouthud$quiuiuinc
	add	sp,10
	fld	dword ptr DGROUP:_pp_gravity
	fsub	dword ptr DGROUP:_tp_gravity
	fmul	dword ptr DGROUP:s@+8
	fstp	dword ptr [bp-12]
	fld	dword ptr [bp-12]
	fadd	dword ptr DGROUP:_tp_gravity
	fstp	dword ptr DGROUP:_tp_gravity
	fld	dword ptr DGROUP:_pp_temp
	fsub	dword ptr DGROUP:_tp_temp
	fmul	qword ptr DGROUP:s@+1846
	fstp	dword ptr [bp-12]
	fld	dword ptr [bp-12]
	fadd	dword ptr DGROUP:_tp_temp
	fstp	dword ptr DGROUP:_tp_temp
	fld	dword ptr DGROUP:_pp_pressure
	fsub	dword ptr DGROUP:_tp_pressure
	fmul	qword ptr DGROUP:s@+1518
	fstp	dword ptr [bp-12]
	fld	dword ptr [bp-12]
	fadd	dword ptr DGROUP:_tp_pressure
	fstp	dword ptr DGROUP:_tp_pressure
	fld	dword ptr DGROUP:_pp_pulse
	fsub	dword ptr DGROUP:_tp_pulse
	fmul	qword ptr DGROUP:s@+1602
	fstp	dword ptr [bp-12]
	fld	dword ptr [bp-12]
	fadd	dword ptr DGROUP:_tp_pulse
	fstp	dword ptr DGROUP:_tp_pulse
	fld	dword ptr DGROUP:_tp_pulse
	sub	sp,8
	fstp	qword ptr [bp-38]
	fld	dword ptr DGROUP:_tp_pressure
	sub	sp,8
	fstp	qword ptr [bp-46]
	fld	dword ptr DGROUP:_tp_temp
	sub	sp,8
	fstp	qword ptr [bp-54]
	fld	dword ptr DGROUP:_tp_gravity
	sub	sp,8
	fstp	qword ptr [bp-62]
	push	ds
	push	offset DGROUP:s@+2173
	push	ds
	push	offset DGROUP:_outhudbuffer
	fwait	
	call	far ptr _sprintf
	add	sp,40
	push	ds
	push	offset DGROUP:_outhudbuffer
	push	large 192
	push	2
	push	cs
	call	near ptr @wrouthud$quiuiuinc
	add	sp,10
	pop	di
	pop	si
	leave	
	ret	
@surrounding$qci	endp
NOCTIS-0_TEXT	ends
_BSS	segment word public use16 'BSS'
_snapfilename	label	byte
	db	24 dup (?)
_BSS	ends
NOCTIS-0_TEXT	segment byte public use16 'CODE'
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@snapshot$qic	proc	far
	push	bp
	mov	bp,sp
	sub	sp,98
	push	si
	push	di
	push	large -29980
	push	cs
	call	near ptr @sa_open$ql
	add	sp,4
	mov	word ptr [bp-36],ax
	cmp	word ptr [bp-36],-1
	je	@117@45
	push	54
	push	ss
	lea	ax,word ptr [bp-98]
	push	ax
	push	word ptr [bp-36]
	call	far ptr __rtl_read
	add	sp,8
	push	word ptr [bp-36]
	call	far ptr __rtl_close
	add	sp,2
	mov	ax,word ptr DGROUP:_QUADWORDS
	mov	word ptr [bp-4],ax
	mov	word ptr DGROUP:_QUADWORDS,16000
	push	0
	push	dword ptr DGROUP:_adaptor
	push	cs
	call	near ptr @pclear$qnucuc
	add	sp,6
	mov	ax,word ptr [bp-4]
	mov	word ptr DGROUP:_QUADWORDS,ax
	cmp	word ptr [bp+6],0
	jne	short @117@9
	mov	word ptr [bp-2],-1
@117@4:
	inc	word ptr [bp-2]
	cmp	word ptr [bp-2],9999
	je	@117@45
	push	word ptr [bp-2]
	push	ds
	push	offset DGROUP:s@+2252
	push	ds
	push	offset DGROUP:_snapfilename
	call	far ptr _sprintf
	add	sp,10
	push	0
	push	ds
	push	offset DGROUP:_snapfilename
	call	far ptr __rtl_open
	add	sp,6
	mov	word ptr [bp-36],ax
	cmp	word ptr [bp-36],-1
	je	short @117@7
	push	ax
	call	far ptr __rtl_close
	add	sp,2
@117@7:
	cmp	word ptr [bp-36],-1
	jne	short @117@4
	jmp	short @117@10
@117@9:
	push	word ptr [bp+6]
	push	ds
	push	offset DGROUP:s@+2276
	push	ds
	push	offset DGROUP:_snapfilename
	call	far ptr _sprintf
	add	sp,10
@117@10:
	cmp	byte ptr [bp+8],0
	je	@117@32
	push	127
	push	large 00007013Ch
	push	large 0
	push	large 000BF0002h
	push	dword ptr DGROUP:_adapted
	push	cs
	call	near ptr @areaclear$qnuciiiiiiuc
	add	sp,18
   	fld	 DGROUP:_dzat_x
	frndint	
	fstp	 [bp-12]
	fld	 DGROUP:_dzat_y
	frndint	
	fstp	 [bp-20]
	fld	 DGROUP:_dzat_z
	frndint	
	fstp	 [bp-28] 
	push	ds
	pop	es
	mov	di,offset DGROUP:_outhudbuffer
	mov	si,offset DGROUP:s@+2300
	mov	cx,9
	rep 	movsw	
	fld	qword ptr [bp-12]
	sub	sp,8
	fstp	qword ptr [bp-110]
	fwait	
	push	cs
	call	near ptr @alphavalue$qd
	add	sp,8
	mov	bx,ds
	mov	si,offset DGROUP:_outhudbuffer
	mov	di,ax
	mov	es,dx
	xor	ax,ax
	mov	cx,0FFFFh
	repnz 	scasb	
	not	cx
	sub	di,cx
	push	ds
	mov	ds,bx
	xchg	si,di
	mov	ax,ds
	mov	bx,ax
	mov	ax,es
	mov	ds,ax
	mov	es,bx
	push	cx
	mov	cx,0FFFFh
	xor	ax,ax
	repnz 	scasb	
	dec	di
	pop	cx
	rep 	movsb	
	pop	ds
	push	ds
	pop	es
	mov	di,offset DGROUP:_outhudbuffer
	mov	si,offset DGROUP:s@+2318
	mov	cx,0FFFFh
	xor	ax,ax
	repnz 	scasb	
	dec	di
	mov	cx,2
	rep 	movsb	
	fld	qword ptr [bp-20]
	fchs	
	sub	sp,8
	fstp	qword ptr [bp-110]
	fwait	
	push	cs
	call	near ptr @alphavalue$qd
	add	sp,8
	mov	bx,ds
	mov	si,offset DGROUP:_outhudbuffer
	mov	di,ax
	mov	es,dx
	xor	ax,ax
	mov	cx,0FFFFh
	repnz 	scasb	
	not	cx
	sub	di,cx
	push	ds
	mov	ds,bx
	xchg	si,di
	mov	ax,ds
	mov	bx,ax
	mov	ax,es
	mov	ds,ax
	mov	es,bx
	push	cx
	mov	cx,0FFFFh
	xor	ax,ax
	repnz 	scasb	
	dec	di
	pop	cx
	rep 	movsb	
	pop	ds
	push	ds
	pop	es
	mov	di,offset DGROUP:_outhudbuffer
	mov	si,offset DGROUP:s@+2320
	mov	cx,0FFFFh
	xor	ax,ax
	repnz 	scasb	
	dec	di
	mov	cx,2
	rep 	movsb	
	fld	qword ptr [bp-28]
	sub	sp,8
	fstp	qword ptr [bp-110]
	fwait	
	push	cs
	call	near ptr @alphavalue$qd
	add	sp,8
	mov	bx,ds
	mov	si,offset DGROUP:_outhudbuffer
	mov	di,ax
	mov	es,dx
	xor	ax,ax
	mov	cx,0FFFFh
	repnz 	scasb	
	not	cx
	sub	di,cx
	push	ds
	mov	ds,bx
	xchg	si,di
	mov	ax,ds
	mov	bx,ax
	mov	ax,es
	mov	ds,ax
	mov	es,bx
	push	cx
	mov	cx,0FFFFh
	xor	ax,ax
	repnz 	scasb	
	dec	di
	pop	cx
	rep 	movsb	
	pop	ds
	mov	al,byte ptr DGROUP:_ip_targetted
	cbw	
	mov	word ptr [bp-44],ax
	cmp	ax,-1
	jle	@117@26
	mov	bx,word ptr [bp-44]
	add	bx,bx
	cmp	word ptr DGROUP:_nearstar_p_owner[bx],-1
	jle	@117@24
	push	ds
	pop	es
	mov	di,offset DGROUP:_outhudbuffer
	mov	si,offset DGROUP:s@+2322
	mov	cx,0FFFFh
	xor	ax,ax
	repnz 	scasb	
	dec	di
	mov	cx,16
	rep 	movsb	
	mov	al,byte ptr DGROUP:_ip_targetted
	cbw	
	mov	word ptr [bp-44],ax
	mov	bx,ax
	mov	al,byte ptr DGROUP:_nearstar_p_moonid[bx]
	cbw	
	inc	ax
	mov	word ptr [bp-38],ax
	fild	word ptr [bp-38]
	sub	sp,8
	fstp	qword ptr [bp-110]
	fwait	
	push	cs
	call	near ptr @alphavalue$qd
	add	sp,8
	mov	bx,ds
	mov	si,offset DGROUP:_outhudbuffer
	mov	di,ax
	mov	es,dx
	xor	ax,ax
	mov	cx,0FFFFh
	repnz 	scasb	
	not	cx
	sub	di,cx
	push	ds
	mov	ds,bx
	xchg	si,di
	mov	ax,ds
	mov	bx,ax
	mov	ax,es
	mov	ds,ax
	mov	es,bx
	push	cx
	mov	cx,0FFFFh
	xor	ax,ax
	repnz 	scasb	
	dec	di
	pop	cx
	rep 	movsb	
	pop	ds
	push	ds
	pop	es
	mov	di,offset DGROUP:_outhudbuffer
	mov	si,offset DGROUP:s@+2338
	mov	cx,0FFFFh
	xor	ax,ax
	repnz 	scasb	
	dec	di
	mov	cx,14
	rep 	movsb	
	mov	al,byte ptr DGROUP:_ip_targetted
	cbw	
	mov	word ptr [bp-44],ax
	add	ax,ax
	mov	bx,ax
	mov	ax,word ptr DGROUP:_nearstar_p_owner[bx]
	jmp	short @117@25
@117@24:
	push	ds
	pop	es
	mov	di,offset DGROUP:_outhudbuffer
	mov	si,offset DGROUP:s@+2352
	mov	cx,0FFFFh
	xor	ax,ax
	repnz 	scasb	
	dec	di
	mov	cx,18
	rep 	movsb	
	mov	al,byte ptr DGROUP:_ip_targetted
	cbw	
	mov	word ptr [bp-44],ax
@117@25:
	inc	ax
	mov	word ptr [bp-38],ax
	fild	word ptr [bp-38]
	sub	sp,8
	fstp	qword ptr [bp-110]
	fwait	
	push	cs
	call	near ptr @alphavalue$qd
	add	sp,8
	mov	bx,ds
	mov	si,offset DGROUP:_outhudbuffer
	mov	di,ax
	mov	es,dx
	xor	ax,ax
	mov	cx,0FFFFh
	repnz 	scasb	
	not	cx
	sub	di,cx
	push	ds
	mov	ds,bx
	xchg	si,di
	mov	ax,ds
	mov	bx,ax
	mov	ax,es
	mov	ds,ax
	mov	es,bx
	push	cx
	mov	cx,0FFFFh
	xor	ax,ax
	repnz 	scasb	
	dec	di
	pop	cx
	rep 	movsb	
	pop	ds
@117@26:
	push	ds
	push	offset DGROUP:_outhudbuffer
	push	large 192
	push	3
	push	cs
	call	near ptr @wrouthud$quiuiuinc
	add	sp,10
	mov	al,byte ptr DGROUP:_ap_targetted
	cbw	
	cmp	ax,1
	jne	short @117@29
	cmp	dword ptr DGROUP:_star_label_pos,large -1
	je	short @117@29
	push	127
	push	large 000070066h
	push	large 0
	push	large 0000E000Eh
	push	dword ptr DGROUP:_adapted
	push	cs
	call	near ptr @areaclear$qnuciiiiiiuc
	add	sp,18
	push	ds
	push	offset DGROUP:_star_label
	push	large 00014000Fh
	push	15
	push	cs
	call	near ptr @wrouthud$quiuiuinc
	add	sp,10
@117@29:
	mov	al,byte ptr DGROUP:_ip_targetted
	cbw	
	mov	word ptr [bp-44],ax
	cmp	ax,-1
	je	short @117@32
	cmp	dword ptr DGROUP:_planet_label_pos,large -1
	je	short @117@32
	push	127
	push	large 000070066h
	push	large 0
	push	large 00017000Eh
	push	dword ptr DGROUP:_adapted
	push	cs
	call	near ptr @areaclear$qnuciiiiiiuc
	add	sp,18
	push	ds
	push	offset DGROUP:_planet_label
	push	large 000140018h
	push	15
	push	cs
	call	near ptr @wrouthud$quiuiuinc
	add	sp,10
@117@32:
	push	0
	push	ds
	push	offset DGROUP:_snapfilename
	call	far ptr __rtl_creat
	add	sp,6
	mov	word ptr [bp-36],ax
	cmp	word ptr [bp-36],-1
	jle	@117@45
	mov	byte ptr [bp-33],0
	push	54
	push	ss
	lea	ax,word ptr [bp-98]
	push	ax
	push	word ptr [bp-36]
	call	far ptr __rtl_write
	add	sp,8
	mov	word ptr [bp-32],0
	mov	word ptr [bp-40],offset DGROUP:_tmppal+2
	mov	word ptr [bp-42],offset DGROUP:_tmppal+1
@117@35:
	mov	bx,word ptr [bp-40]
	mov	al,byte ptr [bx]
	shl	al,2
	mov	byte ptr [bp-34],al
	push	1
	push	ss
	lea	ax,word ptr [bp-34]
	push	ax
	push	word ptr [bp-36]
	call	far ptr __rtl_write
	add	sp,8
	mov	bx,word ptr [bp-42]
	mov	al,byte ptr [bx]
	shl	al,2
	mov	byte ptr [bp-34],al
	push	1
	push	ss
	lea	ax,word ptr [bp-34]
	push	ax
	push	word ptr [bp-36]
	call	far ptr __rtl_write
	add	sp,8
	mov	bx,word ptr [bp-32]
	mov	al,byte ptr DGROUP:_tmppal[bx]
	shl	al,2
	mov	byte ptr [bp-34],al
	push	1
	push	ss
	lea	ax,word ptr [bp-34]
	push	ax
	push	word ptr [bp-36]
	call	far ptr __rtl_write
	add	sp,8
	push	1
	push	ss
	lea	ax,word ptr [bp-33]
	push	ax
	push	word ptr [bp-36]
	call	far ptr __rtl_write
	add	sp,8
	add	word ptr [bp-40],3
	add	word ptr [bp-42],3
	add	word ptr [bp-32],3
	cmp	word ptr [bp-32],768
	jb	@117@35
	mov	word ptr [bp-30],-1856
	jmp	short @117@43
@117@41:
	push	320
	mov	ax,word ptr DGROUP:_adapted
	add	ax,word ptr [bp-30]
	push	word ptr DGROUP:_adapted+2
	push	ax
	push	word ptr [bp-36]
	call	far ptr __rtl_write
	add	sp,8
	sub	word ptr [bp-30],320
@117@43:
	cmp	word ptr [bp-30],-1536
	jb	short @117@41
	push	word ptr [bp-36]
	call	far ptr __rtl_close
	add	sp,2
@117@45:
	pop	di
	pop	si
	leave	
	ret	
@snapshot$qic	endp
NOCTIS-0_TEXT	ends
_DATA	segment word public use16 'DATA'
_iqsecs	label	dword
	db	0
	db	0
	db	0
	db	0
_DATA	ends
NOCTIS-0_TEXT	segment byte public use16 'CODE'
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@additional_consumes$qv	proc	far
	push	si
	fld	qword ptr DGROUP:_secs
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	cmp	eax,dword ptr DGROUP:_iqsecs
	jle	short @118@3
	fld	qword ptr DGROUP:_secs
	call	far ptr F_FTOL@
	shl	eax,16
	shrd	eax,edx,16
	mov	dword ptr DGROUP:_iqsecs,eax
@118@3:
	mov	al,byte ptr DGROUP:_ip_targetted
	cbw	
	cmp	ax,-1
	jle	@118@22
	cmp	word ptr DGROUP:_pwr,15000
	jle	@118@22
	cmp	byte ptr DGROUP:_ip_reached,0
	je	@118@22
	cmp	byte ptr DGROUP:_sync,0
	je	@118@22
	mov	al,byte ptr DGROUP:_sync
	cbw	
	mov	si,ax
	cmp	ax,1
	jne	short @118@10
	mov	eax,dword ptr DGROUP:_iqsecs
	mov	ebx,large 29
	cdq	
	idiv	ebx
	cmp	edx,large 0
	jne	short @118@10
	dec	word ptr DGROUP:_pwr
	inc	dword ptr DGROUP:_iqsecs
@118@10:
	mov	al,byte ptr DGROUP:_sync
	cbw	
	mov	si,ax
	cmp	ax,2
	jne	short @118@13
	mov	eax,dword ptr DGROUP:_iqsecs
	mov	ebx,large 18
	cdq	
	idiv	ebx
	cmp	edx,large 0
	jne	short @118@13
	dec	word ptr DGROUP:_pwr
	inc	dword ptr DGROUP:_iqsecs
@118@13:
	cmp	si,3
	jne	short @118@16
	mov	eax,dword ptr DGROUP:_iqsecs
	mov	ebx,large 58
	cdq	
	idiv	ebx
	cmp	edx,large 0
	jne	short @118@16
	dec	word ptr DGROUP:_pwr
	inc	dword ptr DGROUP:_iqsecs
@118@16:
	cmp	si,4
	jne	short @118@19
	mov	eax,dword ptr DGROUP:_iqsecs
	mov	ebx,large 7
	cdq	
	idiv	ebx
	cmp	edx,large 0
	jne	short @118@19
	dec	word ptr DGROUP:_pwr
	inc	dword ptr DGROUP:_iqsecs
@118@19:
	cmp	si,5
	jne	short @118@22
	mov	eax,dword ptr DGROUP:_iqsecs
	mov	ebx,large 33
	cdq	
	idiv	ebx
	cmp	edx,large 0
	jne	short @118@22
	dec	word ptr DGROUP:_pwr
	inc	dword ptr DGROUP:_iqsecs
@118@22:
	cmp	byte ptr DGROUP:_pl_search,0
	je	short @118@25
	mov	eax,dword ptr DGROUP:_iqsecs
	mov	ebx,large 155
	cdq	
	idiv	ebx
	cmp	edx,large 0
	jne	short @118@25
	dec	word ptr DGROUP:_pwr
	inc	dword ptr DGROUP:_iqsecs
@118@25:
	mov	al,byte ptr DGROUP:_ilightv
	cbw	
	cmp	ax,1
	jne	short @118@28
	mov	eax,dword ptr DGROUP:_iqsecs
	mov	ebx,large 84
	cdq	
	idiv	ebx
	cmp	edx,large 0
	jne	short @118@28
	dec	word ptr DGROUP:_pwr
	inc	dword ptr DGROUP:_iqsecs
@118@28:
	cmp	byte ptr DGROUP:_field_amplificator,0
	je	short @118@31
	mov	eax,dword ptr DGROUP:_iqsecs
	mov	ebx,large 41
	cdq	
	idiv	ebx
	cmp	edx,large 0
	jne	short @118@31
	dec	word ptr DGROUP:_pwr
	inc	dword ptr DGROUP:_iqsecs
@118@31:
	cmp	word ptr DGROUP:_pwr,15000
	jg	short @118@36
	cmp	byte ptr DGROUP:_charge,0
	je	short @118@34
	dec	byte ptr DGROUP:_charge
	mov	word ptr DGROUP:_pwr,20000
	push	100
	push	ds
	push	offset DGROUP:s@+2370
	push	cs
	call	near ptr @status$qnci
	add	sp,6
	jmp	short @118@36
@118@34:
	mov	byte ptr DGROUP:_stspeed,0
	mov	byte ptr DGROUP:_ip_reaching,0
	mov	byte ptr DGROUP:_ip_reached,1
	mov	byte ptr DGROUP:_ip_targetted,255
	cmp	word ptr DGROUP:_pwr,15000
	je	short @118@36
	push	100
	push	ds
	push	offset DGROUP:s@+2381
	push	cs
	call	near ptr @status$qnci
	add	sp,6
	mov	word ptr DGROUP:_pwr,15000
@118@36:
	pop	si
	ret	
@additional_consumes$qv	endp
NOCTIS-0_TEXT	ends
_INIT_	segment word public use16 'INITDATA'
	db	1
	db	32
	dd	@_STCON0_$qv
_INIT_	ends
NOCTIS-0_TEXT	segment byte public use16 'CODE'
	assume	cs:NOCTIS-0_TEXT,ds:DGROUP
@_STCON0_$qv	proc	far
	push	bp
	mov	bp,sp
	sub	sp,4
	fld1	
	fdiv	dword ptr DGROUP:_dpp
	fstp	dword ptr DGROUP:_inv_dpp
	fwait	
	mov	eax,dword ptr DGROUP:_H_MATRIXS
	shl	eax,8
	mov	dword ptr DGROUP:_XSIZE,eax
	mov	eax,dword ptr DGROUP:_V_MATRIXS
	shl	eax,8
	mov	dword ptr DGROUP:_YSIZE,eax
	fld	dword ptr DGROUP:_EMU_K
	fdiv	dword ptr DGROUP:_dpp
	fst	dword ptr [bp-4]
	fstp	dword ptr DGROUP:_XCOEFF
	fld	dword ptr [bp-4]
	fstp	dword ptr DGROUP:_YCOEFF
	fwait	
	mov	eax,dword ptr DGROUP:_dpp
	mov	dword ptr DGROUP:_opt_pcosbeta,eax
	mov	dword ptr DGROUP:_opt_pcosalfa,eax
	leave	
	ret	
@_STCON0_$qv	endp
	?debug	C E9
	?debug	C FAD5010000
NOCTIS-0_TEXT	ends
_DATA	segment word public use16 'DATA'
s@	label	byte
	db	-121
	db	-68
	db	-118
	db	'1UU'
	db	-43
	db	'?'
	db	0
	db	0
	db	-128
	db	'>'
	db	0
	db	0
	db	0
	db	'@data\Current.BIN'
	db	0
	db	'data\StarMap.BIN'
	db	0
	db	'data\GOESfile.TXT'
	db	0
	db	'data\Surface.BIN'
	db	0
	db	'zeroth'
	db	0
	db	'first'
	db	0
	db	'second'
	db	0
	db	'third'
	db	0
	db	'fourth'
	db	0
	db	'fifth'
	db	0
	db	'sixth'
	db	0
	db	'seventh'
	db	0
	db	'eight'
	db	0
	db	'nineth'
	db	0
	db	'tenth'
	db	0
	db	'eleventh'
	db	0
	db	'twelveth'
	db	0
	db	'thiteenth'
	db	0
	db	'fourteenth'
	db	0
	db	'fifteenth'
	db	0
	db	'sixteenth'
	db	0
	db	'seventeenth'
	db	0
	db	'eighteenth'
	db	0
	db	'nineteenth'
	db	0
	db	'twentyth'
	db	0
	db	'medium size, yellow star, suitable for planets having indigen'
	db	'ous lifeforms.'
	db	0
	db	'very large, blue giant star, high energy radiations around.'
	db	0
	db	'white dwarf star, possible harmful radiations.'
	db	0
	db	'very large, ancient, red giant star.'
	db	0
	db	'large and glowing, orange giant star, high nuclear mass.'
	db	0
	db	'small, weak, cold, brown dwarf substellar object.'
	db	0
	db	'large, very weak, very cold, gray giant dead star.'
	db	0
	db	'very small, blue dwarf star, strong gravity well around.'
	db	0
	db	'possible MULTIPLE system - planets spread over wide ranges.'
	db	0
	db	'medium size, surrounded by gas clouds, young star.'
	db	0
	db	'very large and ancient runaway star, unsuitable for planets.'
	db	0
	db	'tiny pulsar object, unsafe, high radiation, strong gravity.'
	db	0
	db	'medium size, internally hot, unstable surface, no atmosphere.'
	db	0
	db	'small, solid, dusty, craterized, no atmosphere.'
	db	0
	db	'medium size, solid, thick atmosphere, fully covered by clouds'
	db	'.'
	db	0
	db	'medium size, felisian, breathable atmosphere, suitable for li'
	db	'fe.'
	db	0
	db	'medium size, rocky, creased, no atmosphere.'
	db	0
	db	'small, solid, thin atmosphere.'
	db	0
	db	'large, not consistent, covered with dense clouds.'
	db	0
	db	'small, solid, icy surface, no atmosphere.'
	db	0
	db	'medium size, surface is mainly native quartz, oxygen atmosphe'
	db	're.'
	db	0
	db	'very large, substellar object, not consistent.'
	db	0
	db	'companion star - not a planet'
	db	0
	db	-31
	db	11
	db	-38
	db	'~'
	db	14
	db	0
	db	0
	db	'?res/supports.nct'
	db	0
	db	0
	db	0
	db	-128
	db	'B'
	db	0
	db	0
	db	'4C'
	db	0
	db	0
	db	-76
	db	'C'
	db	24
	db	'-DT'
	db	-5
	db	'!'
	db	25
	db	'@{'
	db	20
	db	-82
	db	'G'
	db	-31
	db	'z'
	db	-108
	db	'?=:'
	db	-72
	db	'Y'
	db	-68
	db	-100
	db	-6
	db	'V'
	db	0
	db	0
	db	' A'
	db	0
	db	0
	db	-96
	db	'@'
	db	-4
	db	-87
	db	-15
	db	-46
	db	'MbP?'
	db	24
	db	'-DT'
	db	-5
	db	'!'
	db	9
	db	'@es-8R'
	db	-63
	db	16
	db	'@'
	db	-94
	db	'&'
	db	-6
	db	'|'
	db	-108
	db	17
	db	7
	db	'?.'
	db	-97
	db	-121
	db	-94
	db	-82
	db	'B}T'
	db	0
	db	0
	db	0
	db	'?'
	db	0
	db	0
	db	-16
	db	'A:'
	db	-116
	db	'0'
	db	-30
	db	-114
	db	'y%>'
	db	0
	db	'P'
	db	-61
	db	'G{'
	db	20
	db	-82
	db	'G'
	db	-31
	db	'z'
	db	-124
	db	'?'
	db	31
	db	-123
	db	-21
	db	'Q'
	db	-72
	db	30
	db	-43
	db	'?'
	db	31
	db	-123
	db	-21
	db	'Q'
	db	-72
	db	30
	db	-27
	db	'?'
	db	-82
	db	'G'
	db	-31
	db	'z'
	db	20
	db	-82
	db	-17
	db	'?'
	db	31
	db	-123
	db	-21
	db	'Q'
	db	-72
	db	30
	db	-11
	db	'?'
	db	0
	db	0
	db	0
	db	0
	db	0
	db	'@r'
	db	-64
	db	0
	db	0
	db	-110
	db	'C'
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	'm'
	db	-64
	db	0
	db	0
	db	'hC'
	db	0
	db	0
	db	-24
	db	'@'
	db	0
	db	0
	db	-36
	db	'B333333'
	db	-13
	db	'?'
	db	14
	db	'-'
	db	-78
	db	-99
	db	-17
	db	-89
	db	-22
	db	'?'
	db	0
	db	0
	db	0
	db	0
	db	0
	db	'@l'
	db	-64
	db	0
	db	0
	db	'bC'
	db	0
	db	0
	db	0
	db	0
	db	0
	db	-64
	db	'd'
	db	-64
	db	0
	db	0
	db	'&C'
	db	-20
	db	'Q'
	db	-72
	db	30
	db	-123
	db	-21
	db	7
	db	'@'
	db	0
	db	0
	db	0
	db	0
	db	0
	db	-64
	db	'|'
	db	-64
	db	0
	db	0
	db	-26
	db	'C'
	db	0
	db	0
	db	0
	db	0
	db	0
	db	0
	db	'y'
	db	-64
	db	0
	db	0
	db	-56
	db	'C'
	db	0
	db	0
	db	-56
	db	'B'
	db	0
	db	0
	db	-64
	db	'?'
	db	0
	db	0
	db	'|B'
	db	0
	db	0
	db	16
	db	'A'
	db	0
	db	-128
	db	-100
	db	'C'
	db	0
	db	0
	db	'>C333333'
	db	3
	db	'@9'
	db	-99
	db	'R'
	db	-94
	db	'F'
	db	-33
	db	-111
	db	'?'
	db	-102
	db	-103
	db	-103
	db	-103
	db	-103
	db	-103
	db	-71
	db	-65
	db	0
	db	0
	db	'@@'
	db	0
	db	0
	db	30
	db	'C'
	db	0
	db	0
	db	-101
	db	'C'
	db	-128
	db	-72
	db	-95
	db	'G(knN'
	db	0
	db	-40
	db	-69
	db	'E'
	db	-107
	db	-42
	db	'&'
	db	-24
	db	11
	db	'.'
	db	17
	db	'>'
	db	0
	db	0
	db	-106
	db	'C'
	db	0
	db	0
	db	-6
	db	'C'
	db	0
	db	'@'
	db	-100
	db	'E'
	db	0
	db	0
	db	-6
	db	'D'
	db	0
	db	0
	db	'HB'
	db	-102
	db	-103
	db	-103
	db	-103
	db	-103
	db	-103
	db	-87
	db	'?'
	db	-102
	db	-103
	db	-103
	db	-103
	db	-103
	db	-103
	db	-71
	db	'?'
	db	0
	db	0
	db	-128
	db	'A'
	db	0
	db	0
	db	-112
	db	'A'
	db	0
	db	0
	db	-96
	db	'A'
	db	0
	db	0
	db	'HC)\'
	db	-113
	db	-62
	db	-11
	db	'('
	db	-52
	db	'?'
	db	0
	db	0
	db	'zC'
	db	-72
	db	30
	db	-123
	db	-21
	db	'Q'
	db	-72
	db	-66
	db	'?'
	db	-102
	db	-103
	db	-103
	db	-103
	db	-103
	db	-103
	db	-103
	db	'?'
	db	0
	db	0
	db	'@?'
	db	0
	db	0
	db	-128
	db	'@'
	db	0
	db	-128
	db	-77
	db	'C'
	db	0
	db	0
	db	-64
	db	'@'
	db	0
	db	-128
	db	-128
	db	'E'
	db	0
	db	0
	db	'aD333333'
	db	-29
	db	'?'
	db	0
	db	0
	db	'pB'
	db	0
	db	0
	db	-96
	db	'?'
	db	-72
	db	30
	db	-123
	db	-21
	db	'Q'
	db	-72
	db	'~?'
	db	0
	db	'@'
	db	28
	db	'F'
	db	27
	db	'/'
	db	-35
	db	'$'
	db	6
	db	-127
	db	-91
	db	-65
	db	0
	db	0
	db	-56
	db	'A'
	db	0
	db	'$tI'
	db	0
	db	-28
	db	'@F'
	db	-32
	db	-16
	db	-100
	db	'v/'
	db	27
	db	-12
	db	'?'
	db	0
	db	0
	db	0
	db	0
	db	0
	db	'j'
	db	-24
	db	-64
	db	0
	db	0
	db	0
	db	'A'
	db	0
	db	0
	db	'zD'
	db	0
	db	0
	db	22
	db	'DN.........E.........S.........W.........N.........E.........'
	db	'S.......'
	db	0
	db	'EPOC %d & '
	db	0
	db	'0'
	db	0
	db	'.'
	db	0
	db	'0'
	db	0
	db	'.'
	db	0
	db	'0'
	db	0
	db	' & SQC '
	db	0
	db	'.'
	db	0
	db	':'
	db	0
	db	'.'
	db	0
	db	-3
	db	'0Bx'
	db	-76
	db	'q'
	db	-36
	db	'? & '
	db	0
	db	'5\FLIGHTCTR R\DEVICES    D\PREFS      X\SCREEN OFF'
	db	0
	db	'GRAVITY %2.3f FG & TEMPERATURE %+3.1f@C & PRESSURE %2.3f ATM '
	db	'& PULSE %3.0f PPS'
	db	0
	db	'..\GALLERY\SNAP%04d.BMP'
	db	0
	db	'..\GALLERY\SNAP%04d.BMP'
	db	0
	db	'LOCATION PARSIS: '
	db	0
	db	';'
	db	0
	db	';'
	db	0
	db	' & TGT: MOON N@'
	db	0
	db	' OF PLANET N@'
	db	0
	db	' & TGT: PLANET N@'
	db	0
	db	'FCS: READY'
	db	0
	db	'POWER LOSS'
	db	0
_DATA	ends
NOCTIS-0_TEXT	segment byte public use16 'CODE'
NOCTIS-0_TEXT	ends
	extrn	_rand:far
	extrn	_srand:far
	extrn	_gcvt:far
	extrn	_time:far
	extrn	_sprintf:far
	extrn	_strupr:far
	extrn	__fmemmove:far
	extrn	__fmemset:far
	extrn	_farmalloc:far
	extrn	_difftime:far
	extrn	_localtime:far
	extrn	_mktime:far
	extrn	_clock:far
	extrn	_cos:far
	extrn	_fmod:far
	extrn	_sin:far
	extrn	_sqrt:far
	extrn	_int86:far
	extrn	_intdos:far
	extrn	__argv:dword
	extrn	__rtl_close:far
	extrn	__rtl_creat:far
	extrn	_eof:far
	extrn	_lseek:far
	extrn	__rtl_open:far
	extrn	__rtl_read:far
	extrn	__rtl_write:far
	public	@carryAddMultiply$qll
	public	@shiftSegment$qnuci
	public	@clearOffset$qnuc
	public	_QUADWORDS
	public	_adaptor
	public	_adapted
	public	_tmppal
	public	_return_palette
	public	_surface_palette
	public	@lstri$qnc
	public	@reach_your_dir$qv
	public	@_320_200_256$qv
	public	@_80_25_C$qv
	public	@attendi_pressione_tasto$qv
	public	@tasto_premuto$qv
	public	_range8088
	public	@tavola_colori$qnucuiuiccc
	public	@pcopy$qnuct1
	public	@pclear$qnucuc
	public	@areaclear$qnuciiiiiiuc
	public	@psmooth_grays$qnuc
	public	@pfade$qnucuiuc
	public	@psmooth_64$qnucui
	public	@smootharound_64$qnuclllc
	public	@mask_pixels$qnucuc
	extrn	__control87:far
	public	_uneg
	public	_alfa
	public	_beta
	public	_gamma
	public	_cam_x
	public	_cam_y
	public	_cam_z
	public	_dpp
	public	_inv_dpp
	public	_EMU_K
	public	_H_MATRIXS
	public	_V_MATRIXS
	public	_XSIZE
	public	_YSIZE
	public	_XCOEFF
	public	_YCOEFF
	public	_riga
	public	@initscanlines$qv
	public	_ptr
	public	_xp
	public	_yp
	public	_xa
	public	_ya
	public	_global_x
	public	_global_y
	public	@Segmento$qv
	public	_flares
	public	_mp
	public	_max_x
	public	_max_y
	public	_min_x
	public	_min_y
	public	_doflag
	public	_pvert
	public	_nvert
	public	_vvert
	public	_vr
	public	_vr2
	public	_vr3
	public	_vr4
	public	_vr5
	public	_vr6
	public	_zk
	public	_x2
	public	_y2
	public	_z2
	public	_xx
	public	_yy
	public	_zz
	public	_rwf
	public	_rxf
	public	_ryf
	public	_rzf
	public	_lbxl
	public	_ubxl
	public	_lbyl
	public	_ubyl
	public	_lbxf
	public	_ubxf
	public	_lbyf
	public	_ubyf
	public	_x_centro_f
	public	_y_centro_f
	public	_opt_pcosbeta
	public	_opt_psinbeta
	public	_opt_tcosbeta
	public	_opt_tsinbeta
	public	_opt_pcosalfa
	public	_opt_psinalfa
	public	_opt_tcosalfa
	public	_opt_tsinalfa
	public	_opt_tcosgamma
	public	_opt_tsingamma
	public	@change_angle_of_view$qv
	public	@change_camera_lens$qv
	public	@change_txm_repeating_mode$qv
	public	_uno
	public	_entity
	public	@poly3d$qnft1t1uiuc
	public	_txtr
	public	@init_texture_mapping$qv
	public	@load_texture$qncl
	extrn	F_PADD@:far
	public	@fast_load_texture$qnc
	public	_xl
	public	_yl
	public	_aspect
	public	_fallout
	public	_lt_range
	public	_absorption
	public	_shadymask
	public	_shady_aux
	public	_xsh
	public	_ysh
	public	_ksh
	public	_pnx
	public	_pny
	public	_pnz
	public	@pnorm$qnft1t1
	public	__0
	public	__16
	public	_x_antialias
	public	_y_antialias
	public	_z_antialias
	public	_culling_needed
	public	_halfscan_needed
	public	_escrescenze
	public	@polymap$qnft1t1cuc
	public	@Forward$qf
	public	__x_
	public	__y_
	public	@getcoords$qfff
	public	@facing$qnft1t1
	public	_situation_file
	public	_starmap_file
	public	_goesoutputfile
	public	_surface_file
	public	_sfh
	public	_sync
	public	_anti_rad
	public	_pl_search
	public	_field_amplificator
	public	_ilight
	public	_ilightv
	public	_charge
	public	_revcontrols
	public	_ap_targetting
	public	_ap_targetted
	public	_ip_targetting
	public	_ip_targetted
	public	_ip_reaching
	public	_ip_reached
	public	_ap_target_spin
	public	_ap_target_r
	public	_ap_target_g
	public	_ap_target_b
	public	_nearstar_spin
	public	_nearstar_r
	public	_nearstar_g
	public	_nearstar_b
	public	_gburst
	public	_menusalwayson
	public	_depolarize
	public	_sys
	public	_pwr
	public	_dev_page
	public	_ap_target_class
	public	_f_ray_elapsed
	public	_nearstar_class
	public	_nearstar_nop
	public	_pos_x
	public	_pos_y
	public	_pos_z
	public	_user_alfa
	public	_user_beta
	public	_navigation_beta
	public	_ap_target_ray
	public	_nearstar_ray
	public	_dzat_x
	public	_dzat_y
	public	_dzat_z
	public	_ap_target_x
	public	_ap_target_y
	public	_ap_target_z
	public	_nearstar_x
	public	_nearstar_y
	public	_nearstar_z
	public	_helptime
	public	_ip_target_initial_d
	public	_requested_approach_coefficient
	public	_current_approach_coefficient
	public	_reaction_time
	public	_fcs_status
	public	_fcs_status_delay
	public	_psys
	public	_ap_target_initial_d
	public	_requested_vimana_coefficient
	public	_current_vimana_coefficient
	public	_vimana_reaction_time
	public	_lithium_collector
	public	_autoscreenoff
	public	_ap_reached
	public	_lifter
	public	_secs
	public	_data
	public	_surlight
	public	_land_now
	public	_landing_point
	public	_landing_pt_lon
	public	_landing_pt_lat
	public	_crepzone
	public	_nightzone
	public	_sun_x_factor
	public	_epoc
	public	_ctb
	public	_dec
	public	__delay
	public	_stspeed
	public	_bright
	public	_elight
	public	_gl_start
	public	_point
	public	_vptr
	public	_infoarea
	public	_s_control
	public	_s_command
	public	_isecs
	public	_p_isecs
	public	_fsecs
	public	_gl_fps
	public	_fps
	public	_dlt_alfa
	public	_dlt_beta
	public	_dlt_nav_beta
	public	_step
	public	_shift
	public	_s_m
	public	_plx
	public	_ply
	public	_plz
	public	_pxx
	public	_pyy
	public	_delta_x
	public	_delta_y
	public	_nearstar_identity
	public	_nearstar_labeled
	public	_nearstar_nob
	public	_npcs
	public	_resident_map1
	public	_resident_map2
	public	_ontheroof
	public	_datasheetscroll
	public	_datasheetdelta
	public	_ord
	public	_star_description
	public	_class_rgb
	public	_class_ray
	public	_class_rayvar
	public	_class_act
	public	_class_planets
	public	_nearstar_p_type
	public	_nearstar_p_owner
	public	_nearstar_p_moonid
	public	_nearstar_p_ring
	public	_nearstar_p_tilt
	public	_nearstar_p_ray
	public	_nearstar_p_orb_ray
	public	_nearstar_p_orb_seed
	public	_nearstar_p_orb_tilt
	public	_nearstar_p_orb_orient
	public	_nearstar_p_orb_ecc
	public	_nearstar_p_rtperiod
	public	_nearstar_p_rotation
	public	_nearstar_p_term_start
	public	_nearstar_p_term_end
	public	_nearstar_p_qsortindex
	public	_nearstar_p_qsortdist
	public	_planet_description
	public	_planet_rgb_and_var
	public	_planet_possiblemoons
	public	_avg_planet_ray
	public	_mindiff
	public	_s_background
	public	_p_background
	public	_p_surfacemap
	public	_objectschart
	public	_ruinschart
	public	_pvfile
	public	_n_offsets_map
	public	_n_globes_map
	public	_sky_red_filter
	public	_sky_grn_filter
	public	_sky_blu_filter
	public	_gnd_red_filter
	public	_gnd_grn_filter
	public	_gnd_blu_filter
	public	_planet_grav
	public	_rainy
	public	_albedo
	public	_sky_brightness
	public	_horiz_brt
	public	_m200
	public	_rwp
	public	_iwp
	public	_wp
	public	_wdir
	public	_wdirsin
	public	_wdircos
	public	_landed
	public	_atl_x
	public	_atl_z
	public	_atl_x2
	public	_atl_z2
	public	_qid
	public	_pvfile_datatop
	public	_pvfile_dataptr
	public	_pvfile_datalen
	public	_pvfile_npolygs
	public	_pv_n_vtx
	public	_pvfile_x
	public	_pvfile_y
	public	_pvfile_z
	public	_pvfile_c
	public	_pv_mid_x
	public	_pv_mid_y
	public	_pv_mid_z
	public	_pv_mid_d
	public	_pv_dep_i
	public	_flat_rnd_seed
	public	@fast_srand$ql
	public	@fast_random$ql
	public	@ranged_fast_random$qi
	public	@flandom$qv
	public	@fast_flandom$qv
	public	@sa_open$ql
	public	@shade$qnuciiffffff
	extrn	F_FTOL@:far
	public	@from_vehicle$qv
	public	@from_user$qv
	public	@watch$qdddddd
	public	@xy$qdddddd
	public	@p_Forward$qf
	public	_mox
	public	_moy
	public	_moz
	public	@moonorigin$qi
	public	@planet_xyz$qi
	public	@rtp$qi
	public	@planet_viewpoint$qdd
	public	@cplx_planet_viewpoint$qi
	public	_previous_flares_value
	public	@setfx$qc
	public	@chgfx$qc
	public	@resetfx$qv
	public	@stick$qulululul
	public	_fpx
	public	_fpy
	public	_p_rx
	public	_p_ry
	public	_p_rz
	public	_stick_uneg
	public	@stick3d$qffffff
	public	@link3d$qfff
	public	@fline$qllll
	public	_map_color_a
	public	_map_color_b
	public	_map_color_c
	public	_map_color_d
	public	@randomic_mapper$qfffffffffc
	public	@unloadpv$qi
	public	@unloadallpv$qv
	public	@loadpv$qilffffffucc
	public	@QuickSort$qninfii
	public	@drawpv$qiiifffc
	public	@copypv$qii
	public	@modpv$qiiiffffffn6pvlist
	public	@alphavalue$qd
	public	@background$quinuct2t2uiui
	public	@sky$qui
	public	_glass_bubble
	public	@gman1x1$qv
	public	@gman2x2$qv
	public	@gman3x3$qv
	public	@gman4x4$qv
	public	@globe$quinuct2t2uidddfcc
	public	@glowinglobe$qinuct2uidddfiiuc
	public	@whiteglobe$qnucdddff
	public	_xsun_onscreen
	public	@whitesun$qnucdddff
	public	_lft_sin
	public	_lft_cos
	public	@lens_flares_init$qv
	public	@lens_flares_for$qdddddddiccii
	public	_pixilating_effect
	public	_pixel_spreads
	public	_multicolourmask
	public	@single_pixel_at_ptr$quiuc
	public	@far_pixel_at$qdddduc
	public	@getsecs$qv
	public	@extract_ap_target_infos$qv
	public	@zrandom$qi
	public	_smh
	public	_idscale
	public	@search_id_code$qdc
	public	@starnop$qddd
	public	@prepare_nearstar$qv
	public	@ssmooth$qnuc
	public	@lssmooth$qnuc
	public	_c
	public	_gr
	public	_r
	public	_g
	public	_b
	public	_cr
	public	_cx
	public	_cy
	public	_a
	public	_kfract
	public	_lave
	public	_crays
	public	_px
	public	_py
	public	@spot$qv
	public	@permanent_storm$qv
	public	@crater$qv
	public	@band$qv
	public	@wave$qv
	public	@fracture$qnucf
	public	@volcano$qv
	public	@contrast$qfff
	public	@randoface$qii
	public	@negate$qv
	public	@crater_juice$qv
	public	@cirrus$qv
	public	@atm_cyclon$qv
	public	@storm$qv
	public	@surface$qiiduc
	public	@ring$qidddii
	public	@planets$qv
	public	_laststar_x
	public	_laststar_y
	public	_laststar_z
	public	@isthere$qd
	public	_tgt_collect_lastpos
	public	_targets
	public	_topmost_target
	public	_target_line
	public	_update_targets
	public	_collecting_targets
	public	_targets_table_id
	public	_targets_table_px
	public	_targets_table_py
	public	_targets_table_pz
	public	@collect_targets$qv
	public	@status$qnci
	public	_digimap
	public	_digimap2
	public	@cupola$qff
	public	@polycupola$qfc
	public	_gtime
	public	@sync_start$qv
	public	@sync_stop$qv
	public	_global_surface_seed
	public	_ppos_x
	public	_ppos_y
	public	_ppos_z
	public	_dsd
	public	@load_starface$qv
	public	@load_QVRmaps$qv
	public	@load_digimap2$qv
	public	_outhudbuffer
	public	_compass
	public	_tp_gravity
	public	_pp_gravity
	public	_tp_temp
	public	_pp_temp
	public	_tp_pressure
	public	_pp_pressure
	public	_tp_pulse
	public	_pp_pulse
	public	@wrouthud$quiuiuinc
	public	@surrounding$qci
	extrn	_star_label_pos:dword
	extrn	_star_label:byte
	extrn	_planet_label_pos:dword
	extrn	_planet_label:byte
	public	_snapfilename
	public	@snapshot$qic
	public	_iqsecs
	public	@additional_consumes$qv
	extrn	__turboFloat:word
	end
