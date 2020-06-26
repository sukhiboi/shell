#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include "parser.h"

int change_dir(Array_P command)
{
    return chdir(command->elements[1]);
}

int execute(char *command)
{
    Array_P split_command = split(command, ' ');
    if (strcmp(split_command->elements[0], "cd") == 0)
        return change_dir(split_command);
    else
        return execvp(split_command->elements[0], split_command->elements);
}

void prompt()
{
    char cwd[255];
    printf("%s $ ", getcwd(cwd, sizeof(cwd)));
}

void handle_output(int exit_status)
{
    if (exit_status == -1)
        printf("command not found\n");
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
            handle_output(execute(command));
        else
            wait(&pid);
    }
}