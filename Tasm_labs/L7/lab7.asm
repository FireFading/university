s_s segment stack "stack"
	dw 20 dup('$')
s_s ends

d_s segment
	string db '()'
    res db 0
d_s ends

c_s segment
	assume ds:d_s, cs:c_s
    begin:
    mov ax, d_s
    mov ds, ax
	
    xor cx, cx
    mov cx, 2 ; количество символов в последовательности
    mov si, 0 ; смещение первого символа
    xor dx, dx
    xor bx, bx ; флаг типа открывающей скобки

    check: ; проверка, является ли текущая скобка открывающей, определение ее вида
    xor ax, ax
    mov ah, string[si] ; загрузка текущего символа
    cmp ah, '(' ; сравниваем текущую скобку с первым видом открывающих скобок
    je first
    cmp ah, '[' ; сравниваем со вторым
    je second
    cmp ah, '{' ; сравниваем с третьим
    je third
 ; скобки закрывающие

    cmp sp, 40 ; узнаем не пустой ли стек
    jne good ; стек не пустой, есть еще не закрытые скобки
    mov res, 3 ; лишние закрывающие скобки
    jmp itog ; выход

    good: ; проверка соответствия закрывающих скобок
    cmp ah, ')'
    je first_close
    cmp ah, ']'
    je second_close
    cmp ah, '}'
    je third_close

    first:
	mov bh, 1
    push bx ; сохраняем текущую открытую скобку в стек
    jmp next

    second:
    mov bh, 2
    push bx ; сохраняем текущую открытую скобку в стек
    jmp next

    third:
    mov bh, 3
    push bx ; сохраняем текущую открытую скобку в стек
    jmp next

    first_close:
    pop bx
    cmp bh, 1
    je next ; скобки закрыты верно переход к следующему символу
    jmp error

    second_close:
    pop bx
    cmp bh, 2
    je next ; скобки закрыты верно переход к следующему символу
    jmp error

    third_close:
    pop bx
    cmp bh, 3
    je next ; скобки закрыты верно переход к следующему символу
    jmp error

    next:
    inc si ; вычисление следующего смещения
    loop check

    cmp sp, 40 ; проверяем пустой ли стек, если нет, то не все скобки закрыты
    je itog
    mov res, 2 ; лишние открывающие скобки
    jmp itog

    error:
    mov dl, bh ; скобки закрыты неверно, сохранение скобки, которая ожидается
    mov res, 1
    
    itog:

	xor ax, ax	
	mov ah, 4ch
    int 21h
c_s ends
end begin