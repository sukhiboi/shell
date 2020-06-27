#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include "execute.h"
#include "object.h"

void prompt()
{
    char cwd[255];
    printf("\n%s $ ", getcwd(cwd, sizeof(cwd)));
}

void handle_output(int exit_status)
{
    if (exit_status == -1)
        printf("command not found\n");
}

int main()
{
    Object *aliases = create_object();
    while (1)
    {
        signal(SIGINT, SIG_IGN);
        prompt();
        char command[255];
        gets(command);
        int pid = fork();
        if (pid == 0)
        {
            signal(SIGINT, NULL);
            handle_output(execute(aliases, command));
        }
        else
            wait(&pid);
    }
}