#include "headers.h"
#include "proclore.h"

void proclore(pid_t pid)
{
    char path[256];
    char status[256];
    char *processStatus;
    char exePath[256];
    char memPath[256];

    long vmSize = 0;

    snprintf(path, sizeof(path), "/proc/%d/status", pid);
    FILE *statusFile = fopen(path, "r");

    if (statusFile == NULL)
    {
        perror(BRED "Error opening status file" reset);
        exit(EXIT_FAILURE);
    }
    while (fgets(status, sizeof(status), statusFile) != NULL)
    {
        if (strstr(status, "State:") == status)
        {
            processStatus = status + 7;
            break;
        }
    }
    fclose(statusFile);
    char *statusSymbol = processStatus;
    if (processStatus[1] == '+')
    {
        processStatus[1] = '\0'; // Remove '+' for printing
    }
    else
    {
        statusSymbol = NULL;
    }
   
    printf(BMAG "pid : %d\n" reset, pid);
    printf(BCYN "Process Status : %c%s\n" reset, processStatus[0], (statusSymbol ? "+" : ""));
    printf(BYEL "Process Group : %d\n" reset, getpgid(pid));
    snprintf(memPath, sizeof(memPath), "/proc/%d/status", pid);
    FILE *memFile = fopen(memPath, "r");

    if (memFile == NULL)
    {
        perror("Error opening memory file");
        exit(EXIT_FAILURE);
    }

    while (fgets(status, sizeof(status), memFile))
    {
        if (strstr(status, "VmSize:") == status)
        {
            sscanf(status, "VmSize:\t%ld", &vmSize);
            break;
        }
    }

    fclose(memFile);

    // Obtain executable path

    ssize_t exePathSize = readlink("/proc/self/exe", exePath, sizeof(exePath) - 1);
    if (exePathSize != -1)
    {
        exePath[exePathSize] = '\0';
    }
    else
    {
        perror(BRED "Error reading executable path" reset);
        exit(EXIT_FAILURE);
    }
    // convert excecutable path to relative path and use ~ for initial directory
    
    if (strstr(exePath, initdir) == exePath)
    {
        char *temp = exePath + strlen(initdir);
        exePath[0] = '~';
        exePath[1] = '\0';
        strcat(exePath, temp);
    }
    
    printf(BBLU "Virtual memory : %ld\n" reset, vmSize);
    printf(BWHT "Executable path : %s\n" reset, exePath);
}
