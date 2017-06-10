

global print_string
global print_char
global key_detect_simple
global key_detect
global clr_screen


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
        push    ebp
        mov     ebp, esp
        mov     eax,    [ebp+0x08]      ;get 1st param

        ;do something here
        mov     ah, 0x0e
        mov     bl, 0x00
        int     0x10

        mov     esp, ebp
        pop     ebp
        ret     2


key_detect_simple:
        push    ebp
        mov     ebp, esp

        xor     eax, eax
        int     0x16
        ;the result will return in eax

        mov     esp, ebp
        pop     ebp
        ret     2


key_detect:
        push    ebp
        mov     ebp, esp

        ;check  echo
        mov     ebx,    [ebp+0x08]

        ;check  block
        mov     eax,    [ebp+0x10]         ; get 2end param
        cmp     eax,    0x01
        je      .check_buffer   ; block mode

        ; unblock mode
.check_unblock:
        mov     ah,  0x1        ; check keyboard buffer
        int     0x16
        jnz     .check_buffer

.end:
        cmp     ebx, 0x1
        je      .echo
        mov     esp, ebp
        pop     ebp
        ret     2

.check_buffer:
        xor     eax, eax        ; read keyboard buffer
        int     0x16
        jmp     .end            ; go to the end    
.echo:
        mov     ah, 0x0e
        mov     bl, 0x00
        int     0x10

        mov     esp, ebp
        pop     ebp
        ret     2

clr_screen:
        push    ebp
        mov     ebp, esp

        ;do something here
        mov     ax,   3h
        int     10h

        mov     esp, ebp
        pop     ebp
        ret     2



read_floppy:
        push    ebp
        mov     ebp, esp

        ;do something here
        mov esp, ebp
        pop ebp
        ret     2

