s_s segment stack "stack"
    db 20 dup (?)
s_s ends

d_s segment
    a db 10h
	b db 12h
	res db 0 ; for NOD
	count db 0
d_s ends

c_s segment
    assume ds:d_s, cs:c_s
	begin:
	mov ax, d_s
    mov ds, ax

	mov ah, a
	mov bh, b
	mov dl, count
	
	find:
	cmp bh, ah
	jnge first ; a больше b
	jmp second ; b больше a
	
	first:
	sub ah, bh
	cmp ah, bh
	je finish
	jmp find
	
	second:
	sub bh, ah
	cmp bh, ah
	je finish
	jmp find
	
	finish:
	mov res, ah
	
	mov cx, 8
	
	opr:
	and bh, 00000001b
	cmp bh, 1
	je plus
	jmp null
	plus:
	inc dl
	null:
	shr ah, 1
	mov bh, ah
	
	loop opr
	jmp results
	
	results:
	mov count, dl

	mov ah, 4ch
    int 21h
c_s ends
end begin