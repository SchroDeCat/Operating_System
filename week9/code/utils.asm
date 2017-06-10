

global print_string
global print_char
global key_detect_simple


bits 16

segment .text


print_string:
        push    ebp
        mov     ebp, esp
        mov     esi,    [ebp+0x08]      ;get 1st param
.print_loop:
        lodsb
        or      al, al
        jz      .print_leave
        mov     ah, 0x0e
        mov     bl, 0x00
        int     0x10
        jmp     .print_loop
.print_leave:
        mov     esp, ebp
        pop     ebp
        ret


print_char:
        push    esp
        mov     ebp, esp
        mov     eax, [ebp+0x08]

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
        mov     ah, 0x0e
        mov     bl, 0x00
        int     0x10
        mov     esp, ebp
        pop ebp
        ret


key_detect_simple:
        push    ebp
        mov     ebp, esp

        xor     eax, eax
        int     0x16
        ;the result will return in eax

        mov     esp, ebp
        pop ebp
        ret




key_detect:
        push    esp
        mov     ebp, esp

        ;do something here
        mov     esp, ebp
        pop     ebp
        ret


clr_screen:
        push    esp
        mov     ebp, esp

        ;do something here

        mov     esp, ebp
        pop     ebp
        ret


read_floppy:
        push    esp
        mov     ebp, esp

        ;do something here

        mov     esp, ebp
        pop     ebp
        ret

