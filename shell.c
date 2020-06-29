#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
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
    char **command_array = convert_to_array(splitted_query);
    char **parsed_command = built_in_handler(aliases, variables, splitted_query);
    if (parsed_command != NULL)
        command_array = parsed_command;
    return execvp(command_array[0], command_array);
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
            handle_output(execute(aliases, variables, command));
        }
        else
            wait(&pid);
    }
}