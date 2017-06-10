//__asm__(".code16gcc\n");

extern void print_string(char *str);//ÉêÃ÷»ã±àº¯Êý
extern void print_char(char chr);
extern char key_detect_simple();

/*
 * echo : ¼ì²âµ½µÄ°´¼üÊÇ·ñ»ØÏÔ;
 * block: µ÷ÓÃÊÇ·ñ×èÈû
 * extern char key_detect(int echo, int block);
 *
 */




//Ê¹ÓÃprint_charº¯ÊýÊµÏÖ
void print_str(char *str)
{
    print_string("Success\r\n");
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
    while(1){
        //do something
        chr = key_detect_simple();
        if( chr != 'q')
            print_char(chr);
        else
            print_string("will quit.\r\n");
    };
}
