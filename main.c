#include "headers.h"
pid_t background_processes[MAX_BACKGROUND_PROCESSES];
// handler function
void signal_handler(int signum)
{
    if (signum == SIGINT)
    {
        printf("Received SIGINT (Ctrl+C)\n");
        addtoHistory("exit\n");
        exit(0);
        // Handle Ctrl+C signal here
    }
    else if (signum == SIGTERM)
    {
        printf("Received SIGTERM\n");
    }
    else
    {
        printf("Received an unknown signal (%d)\n", signum);
    }
}

int main()
{

    signal(SIGINT, signal_handler);  // Ctrl+C
    signal(SIGTERM, signal_handler); // Termination signal
    setlocale(LC_ALL, "C");

    int proc_no = 0;
    pid_t background_processes[MAX_BACKGROUND_PROCESSES];

    // Keep accepting commands
    //  *user = (char *)calloc(256, sizeof(char));
    // if (user == NULL)
    // {
    //     perror(BRED "calloc" reset);
    //     return 1; // Exit with an error code
    // }
    user = getenv("USER");
    // if (username != NULL)
    // {
    //     snprintf(user, 256, "%s", username);
    // }
    // else
    // {
    //     printf("USER environment variable is not set.\n");
    // }
    gethostname(host, sizeof(host));
    getcwd(initdir, sizeof(initdir));
    strcpy(prevdir, initdir);

    initialiseHistory();

    while (1)
    {

        // Print appropriate prompt with username, systemname and directory before accepting input
        prompt();

        char *input = (char *)calloc(4096, sizeof(char));
        char *input2 = (char *)calloc(4096, sizeof(char));

        if (input == NULL || input2 == NULL)
        {
            perror(BRED "Memory allocation failed" reset);
            return 1;
        }
        char *k = fgets(input, 4096, stdin);
        if (k == NULL)
        {
            perror(BRED "Input error" reset);
            return 1;
        }
        strcpy(input2, input);

        if (input == NULL)
        {
            continue;
        }
        addtoHistory(input);
        input = strtok(input, "\n");
        char *each_command = strtok(input, ";");
        char *tokenpointer;
        char **all_commands = (char **)calloc(256, sizeof(char *));
        if (each_command == NULL)
        {
            continue;
        }
        int num_commands = 0;
        while (each_command != NULL)
        {
            all_commands[num_commands] = (char *)calloc(256, sizeof(char));
            strcpy(all_commands[num_commands], each_command);
            num_commands++;
            each_command = strtok(NULL, ";");
        }

        for (int l = 0; l < num_commands; l++)
        {

            // tokenize the input using strtok
            char *token = strtok(all_commands[l], " \t\r\n\a");
            if (token == NULL)
            {
                all_commands[l] = strtok(NULL, ";");
                continue;
            }
            char *token2 = (char *)calloc(256, sizeof(char));
            strcpy(token2, token);
            char **args = (char **)calloc(256, sizeof(char *));

            int i = 0;
            while (token != NULL)
            {
                args[i] = (char *)calloc(256, sizeof(char));
                if (args[i] == NULL)
                {
                    perror("Memory allocation failed");
                    return 1;
                }
                strcpy(args[i], token);
                i++;
                token = strtok(NULL, " \t\r\n\a");
            }
            int background_flag = 0; // for background process
            args[i] = NULL;
            // seperate by ; and run each command using strok

            if (i == 0 && args[i - 1][strlen(args[i - 1]) - 1] == '&')
            {
                background_flag = 1;
                token2[strlen(token2) - 1] = '\0';
            }
            else if (i != 0 && args[i - 1][strlen(args[i - 1]) - 1] == '&')
            {
                background_flag = 1;
                token2[strlen(token2) - 1] = '\0';
                if (strcmp(args[i - 1], "&") == 0)
                {
                    args[i - 1] = NULL;
                }
            }
            if (background_flag)
            {
                // execute_process(token2, i, args, 1);
                // each_command = strtok_r(NULL, ";", &commandpointer);
                execute_process(i, args, 1, &proc_no, background_processes);
                // free(args);
                // free(token2);
                // free(token);
                // for (int j = 0; j < i; j++)
                // {
                //     free(args[j]);
                // }
                continue;
            }
            if (strcmp(args[0], "pastevents") == 0)
            {
                if (args[1] != NULL && strlen(args[1]) > 0)
                {
                    if (strcmp(args[1], "purge") == 0)
                    {
                        purge();
                    }
                }
                displayHistory(args);
            }
            if (strcmp(args[0], "warp") == 0)
            {
                warp(args);
            }
            else if (strcmp(args[0], "peek") == 0)
            {
                peek(args);
            }
            else if (strcmp(args[0], "proclore") == 0)
            {
                // convert next argument to pid and pass it to proclore,if n argument then pass pid of shell
                pid_t pid;
                if (args[1] == NULL)
                {
                    pid = getpid();
                }
                else
                {
                    pid = atoi(args[1]);
                }
                proclore(pid);
            }
            else if (strcmp("seek", args[0]) == 0)
            {
                int flag_e = 0;
                int flag_f = 0;
                int flag_d = 0;

                char *target = calloc(1000, sizeof(char));
                char *tofind = calloc(1000, sizeof(char));
                bool flag_tofind = false;

                for (int x = 1; x < i; x++)
                {
                    if (args[x][0] == '-')
                    {
                        if (args[x][1] == 'd')
                        {
                            flag_d = 1;
                        }
                        else if (args[x][1] == 'f')
                        {
                            flag_f = 1;
                        }
                        else if (args[x][1] == 'e')
                        {
                            flag_e = 1;
                        }
                        else
                        {
                            printf("Invalid flag\n");
                            return;
                        }
                    }
                    else
                    {
                        if (flag_tofind == false)
                        {
                            strcpy(tofind, args[x]);
                            flag_tofind = true;
                        }
                        else
                        {
                            strcpy(target, args[x]);
                        }
                    }
                }
                if (strlen(target) == 0)
                {
                    strcpy(target, ".");
                }
                // puts(tofind);
                // puts(target);
                if (flag_d == 0 && flag_f == 0)
                {

                    seek(i, target, 1, flag_e, 1, tofind);
                }
                else if (flag_d==1 && flag_f==1)
                {
                    perror("Invalid flags");
                }
                else
                {

                    seek(i, target, flag_f, flag_e, flag_d, tofind);
                }
            }
            else if (strcmp(args[0], "exit") == 0)
            {
                exit(0);
            }
            else
            {
                execute_process(i, args, 0, &proc_no, background_processes);
            }

            for (int j = 0; j < i; j++)
            {
                free(args[j]);
            }
            free(args);
            free(token2);
            free(token);
            check_background_processes(&proc_no, background_processes);
        }
        free(input);
        free(input2);
    }
}
