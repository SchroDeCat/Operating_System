;	+--------+
;	|        |
;	|        |
;	|        |
;	|        |
;	|--------|
;	|BOOT SEC|
;	|ORIGIN  | 07C0:0000
;	|--------|
;	|        |
;	|        |
;	|        |
;	|--------|
;	|KERNEL  |
;	|LOADED  |
;	|--------| 0060:0000
;	|        |
;	+--------+


bits 16

segment .text

%define     BASE        0x7c00
%define     LOADSEG     0x0060
%define     KERSIZE     1
%define     KERSTART    2

        org  BASE
entry:
        cld
        sub     ax, ax
        mov     ds, ax
        mov     ss, ax          ; initialize stack
        mov     bp, 0x7c00
        mov     sp, 0x7c00
        call    print
        db      "Loading Boot...",13,10,0

read_floppy:
        mov     ax, LOADSEG           ;段地址 ; 存放数据的内存基地址
        mov     es, ax                ;设置段地址（不能直接mov es,段地址）
        mov     bx, 0                 ;偏移地址; 存放数据的内存偏移地址
        mov     ah, 2                 ; 功能号
        mov     al, KERSIZE           ;扇区数
        mov     dl, 0                 ;驱动器号 ; 软盘为0，硬盘和U盘为80H
        mov     dh, 0                 ;磁头号 ; 起始编号为0
        mov     ch, 0                 ;柱面号 ; 起始编号为0
        mov     cl, KERSTART          ;起始扇区号 ; 起始编号为1
        int     13H                   ;调用读磁盘BIOS的13h功能
        cmp     ah, 0;
        jmp     word LOADSEG:0x0000
        jmp     $



print_char:
        xor     bx, bx                   ; video page 0
        mov     ah, 0x0E                 ; else print it
        int     0x10                     ; via TTY mode
print:
        pop     si                       ; this is the first character
        lodsb                          ; get token
        push    si                       ; stack up potential return address
        cmp     al, 0                    ; end of string?
        jne     print_char              ; until done
        ret                            ; and jump to it


        times   0x01fe-$+$$ db 0

sign            dw      0xAA55
