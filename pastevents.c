#include "headers.h"
#include "pastevents.h"

char historypath[1000];
int historySize = 0;
char history[20][256];


void initialiseHistory()
{
    historySize = 0;
    strcpy(historypath, initdir);
    strcat(historypath, "/past_events.txt");
    FILE *historyfile = fopen(historypath, "r");
    char line[MAX_COMMAND_LENGTH];

    while (fgets(line, sizeof(line), historyfile) != NULL)
    {
        if (line[0] != '\n')
        {
            strcpy(history[historySize], line);
            historySize++;
        }
    }
    fclose(historyfile);
}

void displayHistory()
{
   
    if (historySize == 0)
    {
        printf(BRED "No commands in history\n" reset);
        return;
    }
    for (int i = 0; i < historySize; i++)
    {
        printf("%s", history[i]);
    }
}

void addtoHistory(char *argc)
{
    // if the argc contains a substrinh pastevents, do not add it to history
    if (historySize > 0 && strcmp(argc, history[historySize - 1]) == 0 )
    {
        return;
    }
    if (strstr(argc, "pastevents") != NULL)
    {
        return;
    }
    if (historySize == 15)
    {
        strcpy(history[historySize], argc);

        // remove the first element of array
        for (int i = 0; i < historySize - 1; i++)
        {
            strcpy(history[i], history[i + 1]);
        }
    }
    else
    {
        strcpy(history[historySize], argc);
        historySize++;
    }
    // empty the past_events.txt file and write the array to it
    FILE *historyfile = fopen(historypath, "w");
    fclose(historyfile);
    historyfile = fopen(historypath, "a");
    for (int i = 0; i < historySize; i++)
    {
        fprintf(historyfile, "%s", history[i]);
    }
    fclose(historyfile);
}
void purge()
{
    //reset the history array
    for (int i = 0; i < historySize; i++)
    {
        strcpy(history[i], "");
    }
    historySize = 0;
    // empty the past_events.txt file
    FILE *historyfile = fopen(historypath, "w");
    fclose(historyfile);

    

}