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
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

static char * s;        /* string pattern that needs to search */
static int type_flag;   /* type of files need to be open */

#define REGULAR_F   0x7   /* regular files */
#define C_F         0x1   /* c files */
#define H_F         0x2   /* h files */
#define S_F         0x4   /* S files */

static void ftw(char * pathname, void (* func)(char *));
static void search(char *); 




/* 
 * This function is modified from Program 4.7 
 * in Book Advanced Programming in the UNIX Environment, 
 * written by W. Richard Stevens
 *
 * Descend through the hierarchy, starting at "pathname".
 * If "pathname" is anything other than a directory, 
 * we lstat() it, call func(), and return.
 * For a directory, we call ourself recursively 
 * for each name in the directory.
 */
static void
ftw(char * pathname, void (* func)(char *))
{
    struct stat     statbuf;
    struct dirent   * dirp;
    DIR             * dp;
    char            * ptr;

    if (lstat(pathname, &statbuf) < 0)  /* stat error */
    {
        printf("ERROR: stat error on %s\n", pathname);
        return;
    }
    
    if (S_ISDIR(statbuf.st_mode))       /* a directory */
    {
        /*
         * It's a directory.
         * So process each filename in the directory.
         */
        ptr = pathname + strlen(pathname);  /* point to end of pathname */
        *ptr++ = '/';
        *ptr = 0;

        if ((dp = opendir(pathname)) == NULL)   /* can NOT read directory */
        {
            printf("ERROR: can NOT read directory \"%s\"\n", pathname);
            return;
        }

        /* process all files inside one by one */        
        while ((dirp = readdir(dp)) != NULL)
        {
            if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
            {
                continue;   /* ignore dot and dot dot */
            }

            strcpy(ptr, dirp->d_name);  /* append name after slash */
            
            ftw(pathname, func);    /* recursively call ftw */
        }
        
        ptr[-1] = 0;    /* erase everything from slash onwards */

        if (closedir(dp) < 0)
        {
            printf("ERROR: can NOT close directory %s\n", pathname);
            return;
        }

    }
    else if (S_ISREG(statbuf.st_mode))  /* a regular file */
    {
        func(pathname);
    }
    else if (S_ISLNK(statbuf.st_mode))  /* a symbolic link */
    {
        printf("\"%s\" is a symbolic link.\n", pathname);
    }
    
}

static void 
search(char * filename)
{
    // printf("file: %s\n", filename);
    char    * file_extension;
    int     file_type;

    file_extension = filename + strlen(filename) - 2;   /* point to the last two char in pathname */

    /* get file type */
    if (strcmp(file_extension, ".c") == 0)
    {  
        file_type = C_F;
    }
    else if (strcmp(file_extension, ".h") == 0)
    {
        file_type = H_F;
    }
    else if (strcmp(file_extension, ".S") == 0)
    {
        file_type = S_F;
    }
    else
    {
        file_type = 0x0;
    }
    
    if (file_type & type_flag)  /* decide whether the file needs to be open */
    {
        printf("%s\n", filename);
    }    
    
}

int
main (int argc, char * argv[])
{
    char * pathname;
    int sym_link;
    
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
        printf("ERROR: requires pathname and s!\n");
        printf("Usage:	$finds -p pathname [-f c|h|S] [-l] -s s\n");
        return 1;
    }

    
    /* already get all info, start processing */
    printf("pathname: %s\ntype_flag: %d\nsym_link: %d\ns: %s\n\n", pathname, type_flag, sym_link, s);
    ftw(pathname, &search);
}
