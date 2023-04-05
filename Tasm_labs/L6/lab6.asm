s_s segment stack "stack"
	dw 10 dup(?)
s_s ends

hospital struc
	number dw 0
	gender db 'f'
	birthday dw 0
	date_in db '  /  /    '
	date_out db '  /  /    '
hospital ends

d_s segment
	count_persons db 0
	number_female db 0
	date_birthday dw 0
	number_male db 0
	persons hospital <1, 'f', 2000, '07/10/2020', '08/12/2021'>, <2, 'm', 2004, '09/11/2021', '20/11/2021'>, <3, 'f', 1996, '08/12/2020', '01/10/2020'>
	date_n db '08/12/2021'
	female db 'f'
	male db 'm'
	number_find dw 2
	year dw 2004
d_s ends

c_s segment
	assume ds:d_s, cs:c_s
    begin:
    mov ax, d_s
    mov ds, ax
	
	xor si, si ; смещение массива (первый человек)
	lea bx, persons ; загрузка базового адреса массива
	mov cx, 3 ; количество итераций (людей в массиве структур)
	xor dx, dx
	add si, 5 ; начало поля дата поступления
	xor di, di
	xor ax, ax
	
	p: ; поиск количества пациентов, поступивших на определенную дату
	push cx
	mov cx, 10 ; количество символов в записи даты
	check: ; посимвольное сравнение необходимой даты и даты в поле структуры
	mov ah, [bx][si] ; загрузка символа из массива
	mov dh, date_n[di] ; загрузка соответствующего символа по порядку из необходимой даты
	cmp dh, ah
	jne pass ; если символы не совпадают, то цикл обрывается
	inc si ; вычисление смещения следующего символа в дате в массиве
	inc di
	loop check
	add dl, 1 ; если не произошло обрыва цикла, значит даты совпадают, прибавляем значение счетчика
	pass:
	xor di, di ; обнуляем смещение искомой даты
	add si, cx
	add si, type hospital ; переходим к следующему человеку
	sub si, 10 ; переходим на начало поля даты поступления в массиве
	pop cx
	loop p
	mov count_persons, dl
	
	xor si, si ; смещение массива (первый человек)
	lea bx, persons ; загрузка базового адреса массива
	mov cx, 3 ; количество итераций (людей в массиве структур)
	xor dx, dx
	add si, 15 ; начало поля дата выписки
	xor di, di
	xor ax, ax
	
	p2: ; подсчет количества женщин, выписанных на определенную дату
	mov ah, [bx][di].gender
	add di, type hospital ; следующий элемент массива
	cmp ah, 'f' ; если пациент не женщина, то пропускаем проверку даты
	jne pass_2
	push di
	push cx
	mov cx, 10 ; количество символов в записи даты
	xor di, di ; обнуляем смещение искомой даты
	check_2: ; посимвольное сравнение необходимой даты и даты в поле структуры
	mov ah, [bx][si] ; загрузка символа из массива
	mov dh, date_n[di] ; загрузка соответствующего символа по порядку из необходимой даты
	cmp dh, ah
	jne pass_3 ; если символы не совпадают, то цикл обрывается
	inc si ; вычисление смещения следующего символа в дате в массиве
	inc di
	loop check_2
	add dl, 1 ; если не произошло обрыва цикла, значит даты совпадают, прибавляем значение счетчика
	pass_3:
	add si, cx
	sub si, 10 ; переходим на начало поля даты выписки в массиве
	pop cx
	pop di
	pass_2:
	add si, type hospital
	loop p2
	mov number_female, dl
	
	xor si, si ; смещение массива (первый человек)
	lea bx, persons ; загрузка базового адреса массива
	mov cx, 3 ; количество итераций (людей в массиве структур)
	xor dx, dx
	xor si, si
	xor ax, ax
	mov dx, number_find
	
	p3: ; поиск года рождения человека по номеру карты
	mov ax, [bx][si].number
	cmp ax, dx ; сравниваем значение из поля структуры и искомое значение
	jne not_find
	xor ax, ax
	mov ax, [bx][si].birthday
	mov date_birthday, ax
	not_find:
	add si, type hospital ; следующий элемент массива
	loop p3
	
	xor si, si ; смещение массива (первый человек)
	lea bx, persons ; загрузка базового адреса массива
	mov cx, 3 ; количество итераций (людей в массиве структур)
	xor dx, dx
	xor di, di
	xor ax, ax
	
	p4: ; поиск количества мужчин по заданному году рождения
	mov ah, [bx][di].gender
	cmp ah, 'm' ; если пациент не мужчина, то пропускаем проверку года рождения
	jne pass_4
	push ax
	mov ax, [bx][di].birthday
	cmp ax, year
	jne pass_4
	inc dl
	pass_4:
	add di, type hospital ; следующий элемент массива
	loop p4
	mov number_male, dl
	
	xor ax, ax	
	mov ah, 4ch
    int 21h
c_s ends
end begin