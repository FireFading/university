s_s segment stack "stack"
    dw 5 dup (?)
s_s ends

d_s segment
    mas dw 8, 12, 7, 165, 325, 1, 75, 4
	res dw 8 dup (0)
d_s ends

c_s segment
	assume ds:d_s, cs:c_s
    begin:
	mov ax, d_s
    mov ds, ax
	
	call input
	
	call sort_one
	
	mov ah, 4ch
    int 21h
	
	input proc near
		mov cx, 8
		mov si, 0
		write:
		mov dx, mas[si]
		mov res[si], dx
		add si, 2
		loop write
		ret
	input endp
	
	sort_one proc near
	mov cx, 8
	sort:
		push cx
		mov si, 0
		mov cx, 7
		
		f:
		mov ax, res[si] ; загрузка первого числа
		add si, 2 ; вычисление адреса следующего элемента
		mov bx, res[si] ; загрузка следующего числа
		cmp ax, bx; сравниваем
		jg change
		jmp pass
		
		change:
		mov res[si], ax
		sub si, 2
		mov res[si], bx
		add si, 2
		
		pass:
		
		loop f
	pop cx
	loop sort
	ret
	sort_one endp
	
c_s ends
end begin
