#include "headers.h"

void warp(char **args)
{

    char current[256];
    int i = 1;
    if (args[1] == NULL)
    {
        chdir(initdir);
        printf("%s\n", initdir);
    }
    else
    {
        while (args[i] != NULL)
        {
            warp_internal(args[i]);
            i++;
        }
    }
}

void warp_internal(char *args)
{
    char buff[256];
    getcwd(buff, sizeof(buff));
    int retchdir = -1;
    if (strcmp(args, "-") == 0) // Going to old working directory
        retchdir = chdir(prevdir);

    else if (strcmp(args, "~") == 0) // go to home directory
        retchdir = chdir(initdir);
    else if (args[0] == '~')
    {
        char temp[256];
        strcpy(temp, initdir);
        strcat(temp, &args[1]);
        retchdir = chdir(temp);
    }
    else if (strcmp(args, ".") == 0) // do nothing
        ;

    else if (strcmp("..", args) == 0)
        retchdir = chdir("..");

    else // go to some other directory , " .. " is already implemented here
        retchdir = chdir(args);

    if (retchdir == 0) // on successful completion of chdir
        strcpy(prevdir, buff);

    getcwd(buff, sizeof(buff));
    printf("%s\n", buff);
}