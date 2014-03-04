/* File:	finds.c
 * Name:	Tianyou Luo
 * Date:	03/17/14
 * Purpose: 	CS410 Assignment 2
 *		  search all files with a given type and 
 *		  print out the lines included string s in certain pattern
 * Usage:	$finds -p pathname [-f c|h|S] [-l] -s s
 */

#include <stdio.h>
#include <unistd.h>
#include <stdio.h>

#define REGULAR_F   0   /* regular files */
#define C_F         1   /* c files */
#define H_F         2   /* h files */
#define S_F         4   /* S files */

static int ftw()

int
main (int argc, char * argv[])
{
    char * pathname, * s;
    int type_flag, sym_link;
    
    pathname = NULL;        /* init w/ NULL */
    s = NULL;               /* init w/ NULL */
    type_flag = REGULAR_F;  /* type of files which need to open */
    sym_link = 0;           /* default not search symbolic links */
    
    int c;
    while ((c = getopt(argc, argv, "p:f:ls:")) != -1)
    {
        switch (c)
        {
            case 'p':
                pathname = optarg;
                break;
            case 'f':
                switch (*optarg)
                {
                    case 'c':
                        type_flag = 1;
                        break;
                    case 'h':
                        type_flag = 2;
                        break;
                    case 'S':
                        type_flag = 4;
                        break;
                    default:
                        printf("%s", "Unknown file type.\n");
                        return 1;
                }
                break;
            case 'l':
                sym_link = 1;
                break;
            case 's':
                s = optarg;
                break;
            case '?':
                if (optopt == 'p')
                {
                    printf("%s", "Option -p requires an argument.\n");
                } 
                else if (optopt == 'f')
                {
                    printf("%s", "Option -f requires an argument.\n");
                }
                else if (optopt == 's')
                {
                    printf("%s", "Option -s requires an argument.\n");
                }
                else
                {
                    printf("%s", "Unknown option.\n");
                }
                return 1;
            default:
                printf("%s", "Error on getopt!\n");
                return 1;
        }
    }
    
    if (pathname == NULL || s == NULL)
    {
        printf("%s", "Require pathname and s!");
        return 1;
    }

    
    /* already get all info, start processing */
    printf("pathname: %s\ntype_flag: %d\nsym_link: %d\ns: %s\n", pathname, type_flag, sym_link, s);
}
