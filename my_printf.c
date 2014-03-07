/* File:	my_printf.c
 * Name:	Tianyou Luo
 * Date:	03/17/14
 * Purpose: same function of printf() in standard I/O libary
 */

#include "itoa.c"
#include <stdio.h>

void my_printf(const char *, ...);

void
my_printf(const char * format, ...)
{
    /*
    char * ptr = format;
    
    while ((*ptr) != 0)
    {
        printf("%x\n", ptr);
        printf("%s\n", ptr++);
        
    }
    printf("%s\n", *++ptr);
    while (*ptr == 0)
    {
        printf("%x\n", ptr);
        printf("%d\n", *ptr++);
    }
    */
    /* get the first ar */
    /*
    //ptr++;
    while((*ptr) != 0)
    {
        printf("%x\n", ptr);
        printf("%d\n", *ptr);
        printf("%c\n", *ptr++);
    }*/
}

int 
main(int argc, char * argv[])
{
    my_printf("asdf", "jkl;", 123);
    return 0;
}
