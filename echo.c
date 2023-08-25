#include "echo.h"
#include "headers.h"

void echo(char **argc)
{
    int i = 1;
    while (argc[i] != NULL)
    {
        printf("%s ", argc[i]);
        i++;
    }
    printf("\n");
}