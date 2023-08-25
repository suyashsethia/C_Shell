#include "headers.h"
#include "process.h"

void execute_process(int num_args, char **args, int background_flag , int *proc_no , pid_t *background_processes)
{
    pid_t pid = fork(); // Fork a child process

    if (pid < 0)
    {
        perror("Fork failed");
        return;
    }

    if (pid == 0)
    {
        // Child process
        execvp(args[0], args);
        // perror("execvp");
        // exit(1); // Exit the child process
    }
    else
    {
        // Parent process
        if (background_flag)
        {
            if ((*proc_no) < MAX_BACKGROUND_PROCESSES)
            {
                background_processes[(*proc_no)] = pid;
                (*proc_no)++;
                printf("%d\n", pid);
            }
            else
            {
                printf("Too many background processes, cannot add another.\n");
            }
        }
        else
        {
            int status;
            waitpid(pid, &status, 0);
        }
    }
}
void check_background_processes(int *proc_no , pid_t *background_processes) 
{
    int status;
    pid_t pid;

    for (int i = 0; i < (*proc_no); i++)
    {
        pid = waitpid(background_processes[i], &status, WNOHANG);
        if (pid > 0)
        {
            // A background process has finished
            if (WIFEXITED(status))
            {
                printf(BBLU"Process with PID %d exited normally (%d)\n"reset,pid, WEXITSTATUS(status));
               
                
            }
            else
            {
                printf("Background process with PID %d has ended.\n", pid);
            }

            // Remove the finished process from the bg_jobs array
            for (int j = i; j < (*proc_no) - 1; j++)
            {
                background_processes[j] = background_processes[j + 1];
            }
            (*proc_no)--;
            i--; // Decrement i because elements shifted left
        }
    }
}