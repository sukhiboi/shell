#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include "list.h"
#include "object.h"
#include "alias.h"
#include "built_in.h"

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

int execute(Object *aliases, Object *variables, char *query)
{
    List *splitted_query = split(' ', query);
    char **parsed_command = built_in_handler(aliases, variables, splitted_query);
    if (parsed_command == NULL)
    {
        return -1;
    }
    return execvp(parsed_command[0], parsed_command);
}

int main()
{
    Object *aliases = create_object();
    Object *variables = create_object();
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
            int exit_status = execute(aliases, variables, command);
            handle_output(exit_status);
        }
        else
            wait(&pid);
    }
}