/* File:	my_printf.c
 * Name:	Tianyou Luo
 * Date:	03/17/14
 * Purpose: same function of printf() in standard I/O libary
 */

#include "itoa.c"
#include <stdio.h>
#include <stdlib.h>
void my_printf(const char *, ...);

int getesp() {
__asm__("movl %esp,%eax");
}

int getebp()
{
__asm__("movl %ebp,%eax");
}

void
my_printf(const char * format, ...)
{
    int i = 0;

    printf("%s\n", *(&format+1));
    void ** arg_ptr;
    arg_ptr  = &format +1;
    
    printf("%x\n", arg_ptr);
    printf("%s\n", (char*)(arg_ptr));
}

int 
main(int argc, char * argv[])
{
    my_printf("asdfasdfasdf", "jkl",123,"werwerwrwerwer",233);
    return 0;
}
