#include "headers.h"

int is_valid_token(const char *token)
{
    // Check if the token contains only letters, numbers, or normal characters
    for (int i = 0; token[i] != '\0'; i++)
    {
        if (!isalnum(token[i]) && token[i] != ' ' && token[i] != '\t' && token[i] != '\r' && token[i] != '\n' && token[i] != '\a')
        {
            return 0; // Token contains invalid characters
        }
    }
    return 1; // Token is valid
}

// Signal handler function
void signal_handler(int signum)
{
    if (signum == SIGINT)
    {
        printf("Received SIGINT (Ctrl+C)\n");
        addtoHistory("exit");
        exit(0);
        // Handle Ctrl+C signal here
    }
    else if (signum == SIGTERM)
    {
        printf("Received SIGTERM\n");
        // Handle SIGTERM signal here
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
    // Keep accepting commands
    char *user = (char *)calloc(256, sizeof(char));
    if (user == NULL)
    {
        perror(BRED "calloc" reset);
        return 1; // Exit with an error code
    }
    char *username = getenv("USER");
    if (username != NULL)
    {
        snprintf(user, 256, "%s", username);
    }
    else
    {
        printf("USER environment variable is not set.\n");
    }
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

        
        // tokenize the input using strtok
        char *token = strtok(input, " \t\r\n\a");
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
        // seperate by ; and run each command using strok
        char *token2 = strtok(input2, ";");

        while (token2 != NULL)
        {

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
            else
            {
                addtoHistory(input2);
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
            else if (strcmp(args[0], "exit") == 0)
            {
                exit(0);
            }
            else if (args[0] == NULL)
            {
                exit(0);
            }
            for (int j = 0; j < i; j++)
            {
                free(args[j]);
            }
            token2 = strtok(NULL, ";");
        }
        free(args);
        free(input);
        free(input2);
    }
}
