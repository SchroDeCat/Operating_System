extern choose               ; �ⲿC������int choose(int a, int b);

[section .data]             ; ���ݶ�
num1st  dd  3           ; ���ò���a
num2nd  dd  4           ; ���ò���b

[section .text]             ; �����
global _start               ; �����������_start
global myprint          ; ��������myprint

_start:                 ; �������
; ����C����choose(a, b);
push dword [num2nd] ; b��ջ
push dword [num1st] ; a��ջ
call choose         ; ����choose
add esp, 8          ; = a��b��ջ

; ϵͳ���ã��˳�
mov ebx, 0          ; �˳�״̬��
mov eax, 1          ; sys_exit���ܺ�
int 0x80                ; ϵͳ�ж�

myprint:                    ; ��ʾ�ַ���������void myprint(char *msg, int len);
mov ecx, [esp + 4]      ; ����ַ
mov edx, [esp + 8]      ; ����
mov ebx, 1          ; �ļ�������1=��׼�����Ĭ��Ϊ��Ļ��
mov eax, 4          ; sys_write���ܺ�
int 0x80                ; ϵͳ�ж�

ret                 ; ���򷵻�
