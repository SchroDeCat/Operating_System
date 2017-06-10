

;         (32位栈每次push一个字)
;	|-----------------------|
;	|       3rd param       | <---ebp + 16 , caller push and pass it too callee
;	|-----------------------|
;	|       2nd param       | <---ebp + 12 , caller push and pass it too callee
;	|-----------------------|
;	|       1st param       | <---ebp + 8  , caller push and pass it too callee
;	|-----------------------|
;	|   return address      | <---ebp + 4  , caller using "call" will push it auto
;	|-----------------------|
;	|       old ebp         | <-----ebp, callee push to save ebp
;	|-----------------------|
;	|   local variables     |
;	|   registers saved     | <-----ebp - n, callee free to use
;	|-----------------------|
;	|       ... ...         |
;	|-----------------------|
;	|       ... ...         | <-----esp
;	|-----------------------|
;	|                       |
;	|       empty stack     |
;	|                       |

global  entry
extern  showInfo
extern  main
extern  print_str

bits 16

segment .text

entry:
        push    dword KernelInfo       ;push param on stack
        call    dword showInfo
        add     esp, 4                 ;clean params on stack

        push    dword SuccessInfo      ;push param on stack
        call    dword print_str
        add     esp, 4                 ;clean params on stack

        call    dword main
        jmp     $ ;will not return



segment .data

KernelInfo:
        db 'Loading Kernel...',0x0d,0x0a,0x00     ;0x0d means '\n', 0x0a means '\r', 0x00 means '\0'

SuccessInfo:
        db 'Success.',0x0d,0x0a,0x00

