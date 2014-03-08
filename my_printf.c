/* File:	my_printf.c
 * Name:	Tianyou Luo
 * Date:	03/17/14
 * Purpose: same function of printf() in standard I/O libary;
 			  support the following format codes: %s, %c, %d, %u and %x.
 * Note:	my_printf does NOT check the number of parameters temporary.
 *			  So make sure pass arguments correctly when using my_printf
 */

#include "itoa.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void my_printf(const char *, ...);

/*
int getesp() {
__asm__("movl %esp,%eax");
}

int getebp()
{
__asm__("movl %ebp,%eax");
}
*/

void
my_printf(const char * format, ...)
{
    int i = 0;			/* count the number of %* in format */
    char * ptr;			/* point to a char in format */
    char * result;		/* final str to print out */
    char * num;
	int c;

    printf("%s\n", *(&format+1));
    
    ptr = format;

    while ((c = *ptr++) != 0)
    {
    	if (c == '%')
    	{
    		switch (*ptr)
    		{
    			case 's':
    				i++;
    				write(1, *(char *)(&format+i), strlen(*(char *)(&format+i)));
    				ptr++;
    				break;
    			case 'c':
    				i++;
    				write(1, *(char *)(&format+i), 1);
    				ptr++;
    				break;
    			case 'd':
    				i++;
    				itoa(num, 'd', *(char *)(&format+i));
    				write(1, num, strlen(num));
    				ptr++;
    				break;
    			case 'u':
    				i++;
    				itoa(num, 'd', *(char *)(&format+i));
    				write(1, num, strlen(num));
    				ptr++;
    				break;
    			case 'x':
    				i++;
    				itoa(num,'x', *(char *)(&format+i));
    				write(1, num, strlen(num));
    				ptr++;
    				break;
    			case  0 :
    				break;
    			default :
    				write(1, c, 1);

    		}
    	}
    	else if (c == '\\')
    	{
    		if (*ptr == 'n')
    		{
    			write(1,"\n",1);
    		}
    	}
    	else
    	{
    		write(1,c,1);
    	}
    }
}

int 
main(int argc, char * argv[])
{
    my_printf("asdfasdfasdf%s%d%s%d\n", "jkl",123,"werwerwrwerwer",233);
    return 0;
}
