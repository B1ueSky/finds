/* File:	my_printf.c
 * Name:	Tianyou Luo
 * Date:	03/17/14
 * Purpose: same function of printf() in standard I/O libary;
 			    support the following format codes: %s, %c, %d, %u and %x.
 * Note:	my_printf cannot hold the situation with only one string as parameter,
 *              i.e. my_printf("...") is not allowed yet.
 *              but you still can use it this way my_printf("%s", "...").
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
	/*
    printf("check:\n");
    printf("fmt: %s\n", fmt);
    printf("args = %s\n", args);
    */
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
    int max_length = 1024;
    char * ptr_fmt = fmt;
    void ** arg = (void **)(&fmt + 1);
    char buf[max_length], tmp[max_length], c;
    char * ptr_buf = buf;
    int i = 0;

    while ((c = *ptr_fmt++) != 0 && i++ < max_length)
    {
        //printf("%c\n", c);
        //printf("%s\n", buf);
        // %s, %c, %d, %u and %x
        if (c == '%')
        {
            if (*ptr_fmt == 's')
            {
                ptr_buf += strlen(strcpy(ptr_buf, (char *)(*arg++)));
                ptr_fmt++;
            } 
            else if (*ptr_fmt == 'c') 
            {
                *ptr_buf++ = (char)(*arg++);
                ptr_fmt++;
            } 
            else if (*ptr_fmt == 'd' || *ptr_fmt == 'u')
            {
                itoa(tmp, 'd', (int)(*arg++));
                strcpy(ptr_buf, tmp);
                ptr_buf += strlen(tmp);
                ptr_fmt++;
            }
            else if (*ptr_fmt == 'x')
            {
                itoa(tmp, 'x', (int)(*arg++));
                strcpy(ptr_buf, tmp);
                ptr_buf += strlen(tmp);
                ptr_fmt++; 
            }
            else    /* alone '%' T T */
            {
                *ptr_buf++ = '%';
            }
        }
        else
        {
            *ptr_buf++ = c;
        }
    }
    *ptr_buf = 0;
    
    write(1, buf, strlen(buf));
}

/*
int 
main(int argc, char * argv[])
{
    // func(12, 13, 14, 15, 16);
    my_printf("asdf%%s%d%s%d%c\n", "c" ,123,"werwerwrwerwer",233,'b');
    my_printf("%s%d\n","asdf");
    my_printf("%s\n", "zxcv");
    return 0;
}
*/