/* File:	my_printf.c
 * Name:	Tianyou Luo
 * Date:	03/17/14
 * Purpose: same function of printf() in standard I/O libary;
 			  support the following format codes: %s, %c, %d, %u and %x.
 * Note:	my_printf cannot hold the situation with only one string as parameter,
 *          i.e. my_printf("...") is not allowed yet.
 *          but you still can use it this way my_printf("%s", "...").
 */

#include "itoa.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define my_printf(fmt, ...) if (check_args(fmt, #__VA_ARGS__)){ __my_printf(fmt, __VA_ARGS__);}

int check_args(char *, char *);
void __my_printf(char *, ...);

int
check_args(char * fmt, char *args)
{
	
    printf("check:\n");
    printf("fmt: %s\n", fmt);
    printf("args = %s\n", args);
    
    int num1 = 0;   // %
    int num2 = 0;   // ,
    char * ptr = fmt;
    while (*ptr != 0)
    {
        char c = *(ptr+1);
        if (*ptr == '%' && (c == 's' || c == 'd' || c == 'u' || c == 'x' || c == 'c'))
            num1++;
        ptr++;
    }

    ptr = args;    
    while (*ptr != 0)
    {
        char c = *(ptr+1);
        if (*ptr == ',')
            num2++;
        ptr++;
    }    

    
    //printf("%s\n", args);
    return num2 == (num1-1);
}

void __my_printf(char * fmt, ...)
{
    char * ptr = fmt;
    char c;
    void * arg = &fmt + 1;
    int d = 1;
    char * buf[1024];
    while ((c = *ptr++) != 0)
    {   
        //printf("%c\n", c);
        // %s, %c, %d, %u and %x
        if (c == '%')
        {

            if (*ptr == 's')
            {
                write(1, *((&fmt)+d), strlen(*((&fmt)+d)));
                d++;
                ptr++;
            } 
            else if (*ptr == 'c') 
            {
                write(1, ((&fmt)+d), 1);
                d++;
                ptr++;
            } 
            else if (*ptr == 'd')
            {
                itoa(buf, 10, *((&fmt)+d));
                write(1, buf, strlen(buf));
                d++;    
                ptr++;
            }
            else if (*ptr == 'u')
            {
                itoa(buf, 10, *((&fmt)+d));
                write(1, buf, strlen(buf));
                d++;    
                ptr++;
            }
            else if (*ptr == 'x')
            {
                itoa(buf, 16, *((&fmt)+d));
                write(1, buf, strlen(buf));
                d++;   
                ptr++; 
            }
            else 
            {
                write(1, "%", 1);  
            }
        }
        else
        {
            buf[0] = c;
            buf[1] = 0;
            write(1, buf, 1);
        }
    }
}

int 
main(int argc, char * argv[])
{
    // func(12, 13, 14, 15, 16);
    my_printf("asdf%%s%d%s%d%c\n", "c" ,123,"werwerwrwerwer",233,'b');
    //my_printf("asdfasd");
    return 0;
}
