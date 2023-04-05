d_s segment
	min dw 0
	max dw 0
    mas dw 18 dup (?)
d_s ends

c_s segment
    assume ds:d_s, cs:c_s
    begin:
	mov ax, d_s
    mov ds, ax
	
	mov cx, 17
	mov ax, 1 ; первое число
	mov bx, 1 
	mov si, 0
	mov mas[si], ax
	
	f:
	add si, 2 ; следующий элемент массива
	mov mas[si], ax
	mov dx, ax
	add ax, bx
	mov bx, dx
	
	loop f
	
	mov si, 12
	mov cx, 6
	
	find_min:
	mov ax, mas[si]
	add si, 2
	mov bx, ax
	and bx, 0000000000000001b
	cmp bx, 1
	je finish_min
	jmp null_min
	finish_min:
	mov min, ax
	mov cx, 1
	null_min:
	
	loop find_min
	
	mov si, 30
	
	find_max:
	mov ax, mas[si]
	sub si, 12
	mov bx, ax
	and bx, 0000000000000001b
	cmp bx, 1
	je finish_max
	jmp null_max
	finish_max:
	mov max, ax
	mov cx, 1
	null_max:
	
	loop find_max
	
	mov ah, 4ch
    int 21h
c_s ends
end begin
