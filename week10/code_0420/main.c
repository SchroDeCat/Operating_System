extern void print_string(char *str);//申明汇编函数
extern void print_char(char chr);
extern char key_detect_simple();
extern void print_str(char *str);
extern void clr_screen();

/*
 * echo : 检测到的按键是否回显;
 * block: 调用是否阻塞
 */
 extern char key_detect(int echo, int block);
 


//use print_char
void print_str(char *str)
{
    print_char('S');
    print_char('u');
    print_char('c');
    print_char('c');
    print_char('e');
    print_char('s');
    print_char('s');
    print_char('\r');
    print_char('\n');
}



void showInfo(char *message)
{
     print_string(message);
}


void main()
{
    int chr;
    print_char('o');
    print_char('s');
    print_char('t');
    while(1){
        //do something
        //chr = key_detect_simple();
        chr = key_detect(0,1);
        if( chr == 'c')
        {
            clr_screen();
        }
        else if( chr != 'q'){

            print_char(chr);
        }
        else {
            print_string("will quit.\r\n");
            //clr_screen();
        }
    }
}
