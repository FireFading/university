d_s segment
    x db 27
    y db 2
    z db 7
    sum db 0
    itg db 0
d_s ends
c_s segment
    assume ds:d_s,cs:c_s
    begin:
        mov ax, d_s
        mov ds, ax
        mov al, x
        sub al, 25 ; выполнение вычитания
        mov ah, al
        mul ah ; возведение в квадрат
        mov x, al ; загрузка в память результат предыдущего действия
        mov ah, y 
        mov al, z
        add ah, al
        neg ah 
        mov y, ah
        mov al, x
        xor ah, ah
        div y ; получение целой части от деления(div), расположена в al
        mov sum, al
        mov al, sum
        and al, 01010110b
        or al, 0110001b
        xor al, 7 ; сложение по модулю 2 с произвольным числом
        mov itg, al
        mov ah, 4ch
        int 21h
c_s ends
end begin
