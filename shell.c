#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include "parser.h"

void execute(char *command)
{
    Array_P split_string = split(command, ' ');
    if (strcmp(split_string->elements[0], "cd") == 0)
    {
        chdir(split_string->elements[1]);
        return;
    }
    int exitStatus = execvp(split_string->elements[0], split_string->elements);
    if (exitStatus == -1)
    {
        printf("command not found\n");
    }
}

void prompt()
{
    char cwd[255];
    printf("%s $ ", getcwd(cwd, sizeof(cwd)));
}

int main()
{
    while (1)
    {
        signal(SIGINT, SIG_IGN);
        prompt();
        char command[255];
        gets(command);
        int pid = fork();
        if (pid == 0)
            execute(command);
        else
            wait(&pid);
    }
}