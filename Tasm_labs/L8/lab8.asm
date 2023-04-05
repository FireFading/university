s_s segment stack "stack"
	dw 10 dup(?)
s_s ends

d_s segment
    a dw 4h
    b dw 3h
    x dw 1
    y dw 1
d_s ends

c_s segment
    assume ds:d_s, cs:c_s
    begin:
    mov ax, d_s
    mov ds, ax

    xor cx, cx

    mov cx, a
    push cx
    mov ax, 1
    call factorial
    mov x, ax

    xor cx, cx
    xor ax, ax

    lea si, [b]
    push si
    mov ax, 1
    call factorial_2
    mov y, ax

    xor ax, ax	
	mov ah, 4ch
    int 21h

    factorial proc near ; процедура подсчета факториала с передачей аргумента по значению
    push bp ; запоминаем адрес вершины стека для адресации относительно вершины стека
    mov bp,sp
    cmp cx, 1 ; проверка на окончание ввода аргументов в стек
    je done ; проверка флага знака (окончание рекурсии, выход из процедуры, если флаг поднят)
    dec cx
    push cx ; запоминаем число в стеке
    call factorial ; рекурсивный вызов процедуры
    done:
    mov cx,[bp+4] ; загружаем аргумент из стека
    mul cx
    mov sp, bp
    pop bp
    ret 2 ; удаляем одну ячейку из стека
    factorial endp

    factorial_2 proc near ; процедура подсчета факториала с передачей аргумента по ссылке
    push bp ; запоминаем адрес вершины стека для адресации относительно вершины стека
    mov bp, sp
    mov si, [bp+4] ; загрузка адреса расположения аргумента
    mov cx, [si]
    cmp cx, 1
    je all ; проверка флага знака (окончание рекурсии, выход из процедуры, если флаг поднят)
    dec cx
    mov [si], cx
    push si
    call factorial_2 ; вызов
    all:
    mul cx
    mov sp, bp
    pop bp
    ret 2
    factorial_2 endp
c_s ends
end begin