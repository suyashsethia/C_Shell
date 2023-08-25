#include "headers.h"
#include "peek.h"
void printFileDetails(const char *path, const char *filename)
{
    struct stat fileStat;
    stat(path, &fileStat);

    // printing permissions
    printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");

    printf(" %ld", fileStat.st_nlink); // printing hard links

    struct passwd *pw = getpwuid(fileStat.st_uid);
    struct group *gr = getgrgid(fileStat.st_gid);

    printf(" %s %s", pw->pw_name, gr->gr_name);

    printf(" %ld", fileStat.st_size); // printing size of file

    char time[50];
    strftime(time, 50, "%Y-%m-%d %H:%M:%S", localtime(&fileStat.st_mtime));
    printf(" %s ", time); // printing last modified time

    if (S_ISDIR(fileStat.st_mode))
        printf("\033[1;34m%s\n\033[0m", filename);
    else if ((fileStat.st_mode & S_IXUSR))
        printf("\033[1;32m%s\n\033[0m", filename);
    else
        printf("%s\n", filename);

    return;
}
void listDirectory(char *destination, int showAttributes, int showLongFormat)
{
    struct dirent *entry;
    DIR *dir = opendir(destination);

    if (dir == NULL)
    {
        perror(BRED "Error opendir()" reset);
        exit(1);
    }
    while ((entry = readdir(dir)) != NULL)
    {
        struct stat fileStat;
        char filePath[1000];
        snprintf(filePath, sizeof(filePath), "%s/%s", destination, entry->d_name); // Construct the full path

        if (showAttributes == 1 && showLongFormat == 0)
        {
            stat(filePath, &fileStat);
            if (S_ISDIR(fileStat.st_mode))
                printf(BBLU "%s\n" reset, entry->d_name);
            else if ((fileStat.st_mode & S_IXUSR))
                printf(BGRN "%s\n" reset, entry->d_name);
            else
                printf(BWHT "%s\n" reset, entry->d_name);
        }
        else if (showAttributes == 0 && showLongFormat == 1)
        {
            // Case 2: showAttributes = 0, showLongFormat = 1
            printFileDetails(filePath, entry->d_name);
        }
        else if (showAttributes == 1 && showLongFormat == 1)
        {
            // Case 3: showAttributes = 1, showLongFormat = 1
            printFileDetails(filePath, entry->d_name);
        }
        else
        {
            // Case 4: showAttributes = 0, showLongFormat = 0
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            {
                stat(filePath, &fileStat);
                if (S_ISDIR(fileStat.st_mode))
                    printf(BBLU "%s\n" reset, entry->d_name);
                else if ((fileStat.st_mode & S_IXUSR))
                    printf(BGRN "%s\n" reset, entry->d_name);
                else
                    printf(BWHT "%s\n" reset, entry->d_name);
            }
        }
    }
    closedir(dir);
}

void peek(char **argc)
{
    // printf("%s\n", argc[1]);
    int i = 1;
    int showattributes = 0, longattributes = 0;
    char *destination = (char *)malloc(256 * sizeof(char));

    if (destination == NULL)
    {
        perror("Error allocating memory");
        exit(1);
    }
    destination[0] = '\0';

    getcwd(destination, 256);
    int j = 0;
    while (argc[i] != NULL && strlen(argc[i]) > 0)
    {
        if (strcmp(argc[i], "-") == 0)
        {
            strcpy(destination, prevdir);
        }
        else if ((argc[i][0] == '-'))
        {
            if (strcmp(argc[i], "-a") == 0)
            {
                showattributes = 1;
            }
            else if (strcmp(argc[i], "-l") == 0)
            {
                longattributes = 1;
            }
            else if (strcmp(argc[i], "-al") == 0)
            {
                longattributes = 1;
                showattributes = 1;
            }
            else if (strcmp(argc[i], "-la") == 0)
            {
                longattributes = 1;
                showattributes = 1;
            }
        }
        else if (strcmp(argc[i], "~") == 0)
        {
            strcpy(destination, initdir);
        }

        else if (strcmp(argc[i], "..") == 0)
        {
            //get .. directory
            char temp[256];
            strcpy(temp, destination);
            int len = strlen(temp);
            int k = len - 1;
            while (temp[k] != '/')
            {
                temp[k] = '\0';
                k--;
            }
            temp[k] = '\0';
            strcpy(destination, temp);
            // getcwd(destination, 256);
        }
        else if (argc[i][0] == '~')
        {
            char temp[256];
            strcpy(temp, initdir);
            strcat(temp, &argc[i][1]);
            strcpy(destination, temp);
        }
        else if (argc[i] != NULL)
        {
            strcpy(destination, argc[i]);
        }
        i++;
    }

    listDirectory(destination, showattributes, longattributes);
    free(destination);
}
