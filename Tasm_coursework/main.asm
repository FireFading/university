s_s segment stack "stack"
	dw 128 dup(?)
s_s ends

d_s segment
    mas dw 9 dup(0)
    res dw 0
    n dw 0
    message db 'Input number: ', '$'
    message_n db 'Input n: ', '$'
	message_res db 'Result: ', '$'
d_s ends

c_s segment
    assume ds:d_s, cs:c_s, ss:s_s
    begin:
    mov ax, d_s
    mov ds, ax
	
	xor ax, ax
	mov ah, 06h ; очистка экрана перед показом результата
	int 10h

	mov cx, 9 ; количество вводов чисел
	mov si, 0 ; начальное смещение
	
	main: ; загрузка данных в массив
    xor ax, ax  
    mov ah, 09h
    mov dx,OFFSET message ; подсказка для пользователя 
	;Оператор получения смещения выражения offset позволяет получить значение смещения выражения в байтах относительно начала того сегмента,
	;в котором выражение определено.
    int 21h
	
	push cx ; сохранение номера текущей итерации
	xor cx, cx
	xor ax, ax
	xor dx, dx
	call user_input ; вызов фунции считывания и обработки числа
	
	pop cx
	
	mov mas[si], bx ; загрузка введенного числа в память
	add si, 2 ; смещение следующего числа
	
	loop main
    
	xor ax, ax
    mov ah, 09h
    mov dx,OFFSET message_n
    int 21h
	
	xor ax, ax
	xor dx, dx
	
	call user_input ; ввод пользователем дополнительного числа n
	mov n, bx ; загрузка введенного числа в память
	
	mov cx, 9 ; количество проверок на делимость
	
	xor bx, bx
	xor dx, dx
	mov bl, 1
	
	xor ax, ax
	xor si, si
	
	math:
	mov ax, n
	idiv bl ; делим введенное число на позицию, остаток от деления в ah
	cmp ah, 0 ; сравниваем остаток от деления с 0
	jne follow ; если не равно, то переходим к следующей позиции
	
	xor ax, ax
	mov ax, mas[si]
	add res, ax
	
	follow:
	add si, 2 ; вычисление элемента, стоящего на следующей позиции
	inc bl ; вычисление позиции

	loop math
	
	xor cx, cx
	
	xor ax, ax
    mov ah, 09h
    mov dx,OFFSET message_res
    int 21h
	
	call result
	
	; результат будет оставаться на экране, пока пользователь не нажмет клавишу
	xor ax, ax
	mov  ah, 0ch ;выбираем функцию DOS 0CH
	mov al, 1 ;выбираем функцию ввода символа
	int 21h ;чистим буфер, ждем ввода
	
	xor ax, ax
    mov ah, 4ch
    int 21h
	
    
	user_input proc near; процедура ввода числа, число помещается в bx
	push ax ; сохранение регистров в стеке
	push cx
	push dx
	push si
	
	xor bx, bx ; введенное число
	xor cx, cx ; количество помещений в стек
	mov dx, 1 ; множитель
	
	met:
	
	mov ah, 01 ; считывание символа с клавиатуры
	int 21h
	cmp al, 0dh ; проверка не закончилось ли число (нажата клавиша Enter)
	je check_sign ; если да, то начинаем обработку числа
	cmp al, '-' ; проверка является ли введенный символ минусом
	je sign ; если это минус, то пропускаем вычисление аски-кода
	sub al, 30h ; получаем из аски-кода символа цифру при условии что введена цифра
	
	sign:
	mov ah, 0
	push ax ; помещаем символ в стек 
	inc cx ; увеличиваем счетчик на 1
	jmp met ; переход на ввод нового символа
	
	check_sign:
	pop ax ; достаем символ из стека
	cmp al, '-'
	jne redaction ; если не минус, то обрабатываем число
	neg bx ; если минус, то меняем знак
	jmp exit ; число обработано, переход к выходу
	
	redaction:
	xor ah, ah
	
	push dx ; сохраняем текущее положение множителя в стеке
	imul dx ; умножаем цифру на множитель
	add bx, ax ; добавляем произведение к результату
	
	pop dx
	mov ax, dx 
	mov dx, 0ah 
	imul dx ; вычисление нового множителя
	mov dx, ax
	
	loop check_sign ; повтор пока не будут обработаны все символы
	
	exit: ; завершение
	pop si
	pop dx
	pop cx
	pop ax
	ret
	user_input endp
	
	
	result proc near ; процедура вывода результата на экран
	mov bx, 0 ; количество цифр в результате (количество загрузок в стек)
	xor cx, cx
	mov cx, 0ah ; делитель (основание системы счисления)
	mov ax, res ; загрузка получившейся суммы в регистр
	cmp ax, 0
	jns put ; проверка является ли результат отрицательным, если нет то переход к показу цифр получившегося числа
	neg ax ; если результат отрицательный, то меняем знак
	
	put: ; обработка всех разрядов числа
	xor dx, dx	
	idiv cx ; целая часть в ax, остаток в dx
	push dx ; загружаем остаток от деления в стек
	add bx, 1
	cmp ax, 0
	jne put

	mov ax, res ; загрузка получившейся суммы в регистр
	cmp ax, 0
	jns show ; проверка нужно ли выводить минус
	mov dl, '-'
	xor ax, ax
	mov ah, 02h
	int 21h
	
	show: ; показ символов на экране
	pop dx ; загружаем значение из стека
	add dl, 30h ; вычисление аски-кода для цифры
	mov ah, 02h ; показ символа на экране
	int 21h
	sub bx, 1
	cmp bx, 0 ; если все цифры из стека выведены на экран, то конец
	jne show
	
	ret
	result endp
c_s ends
end begin