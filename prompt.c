#include "headers.h"
#include "prompt.h"

char *user;
char host[256];
char cwd[256] = "";
char initdir[256];
char prevdir[256];

void prompt()
{
    char buffer[256];
    getcwd(buffer, sizeof(buffer));

    char curdir[256] = "~";

    strcat(curdir, &buffer[strlen(initdir)]);

    printf(UGRN "%s@%s:" reset, user, host);
    printf(BBLU "%s> " reset, curdir);
}
