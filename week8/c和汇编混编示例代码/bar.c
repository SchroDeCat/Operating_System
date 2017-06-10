void myprint(char* msg, int len); // 外部函数

int choose(int a, int b) // 函数定义体
{
    if (a >= b) myprint("the 1st one\n", 13); // 调用外部函数
    else myprint("the 2nd one\n", 13); // 调用外部函数

    return 0; // 函数返回
}
