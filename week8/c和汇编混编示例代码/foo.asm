extern choose               ; 外部C函数：int choose(int a, int b);

[section .data]             ; 数据段
num1st  dd  3           ; 调用参数a
num2nd  dd  4           ; 调用参数b

[section .text]             ; 代码段
global _start               ; 导出程序入口_start
global myprint          ; 导出函数myprint

_start:                 ; 程序入口
; 调用C函数choose(a, b);
push dword [num2nd] ; b入栈
push dword [num1st] ; a入栈
call choose         ; 调用choose
add esp, 8          ; = a、b出栈

; 系统调用：退出
mov ebx, 0          ; 退出状态码
mov eax, 1          ; sys_exit功能号
int 0x80                ; 系统中断

myprint:                    ; 显示字符串函数：void myprint(char *msg, int len);
mov ecx, [esp + 4]      ; 串地址
mov edx, [esp + 8]      ; 串长
mov ebx, 1          ; 文件描述符1=标准输出（默认为屏幕）
mov eax, 4          ; sys_write功能号
int 0x80                ; 系统中断

ret                 ; 程序返回
