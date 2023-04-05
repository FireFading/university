s_s segment stack "stack"
    db 20 dup (?)
s_s ends

d_s1 segment
    a db 00010101b
d_s1 ends

d_s2 segment
    b dd c_s1:met3 ; адрес перехода в первый сегмент кода
d_s2 ends

d_s3 segment
    c db 00010001b
d_s3 ends

c_s1 segment
    assume cs: c_s1, ds: d_s1
    
    met3:
    mov ax, d_s1
    mov ds, ax
    
    lea si, a
    mov bl, [si]
    ror bl, 3 ; циклический сдвиг вправо на 3 бита (искомый 3 бит теперь на 0 месте)
    and bl, 00000001b ; применяем маску, и на нулевом месте теперь 3 бит
    jmp far ptr c_s2:met2 ; переход в другой сегмент кода
    
c_s1 ends

c_s2 segment
    assume cs: c_s2, ds: d_s3
    
    met2:
    mov ax, d_s3
    mov ds, ax
    
    lea si, с
    mov bh, [si]
    ror bh, 5 ; ??????????? ????? ?? ??????
    and bh, 00000001b
    jmp far ptr c_s3:met ; переход в другой сегмент кода к корректному завершению работы
    
c_s2 ends

c_s3 segment ; главный сегмент кода
    assume ss: s_s, ds: d_s1, cs: c_s3
    begin:
        mov ax, d_s1
        mov ds, ax
        
        mov ah, a
        shl ah, 1 ; умножение на 2 (сдвиг влево)
        
        assume cs: c_s3, ds:d_s3 ; загрузка нового сегмента данных
        mov ax, d_s3
        mov ds, ax

        mov bh, c
        shr bh, 2 ; деление на 2 (сдвиг вправо)

        assume cs: c_s3, ds:d_s2 ; загрузка нового сегмента данных
        mov ax, d_s2
        mov ds, ax
       
        jmp b ; переход в другой сегмент кода

        met:
        mov ah, 4ch
        int 21h
        
c_s3 ends
end begin
    