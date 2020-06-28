#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "parser.h"
#include "object.h"
#include "alias.h"

int change_dir(char *newPath)
{
    return chdir(newPath);
}

int run_if_built_in_command(Object *aliases, Array_P query)
{
    char *command = query->elements[0];
    if (strcmp(command, "cd") == 0)
        return change_dir(query->elements[1]);
    if (strcmp(command, "alias") == 0)
        return process_alias(aliases, query);
    int exit_code_of_alias_command = run_if_alias(aliases, query);
    if (exit_code_of_alias_command != 1001)
        return exit_code_of_alias_command;
    return 1000;
}

int execute(Object *aliases, char *query)
{
    Array_P splitted_query = split(query, ' ');
    int exit_status = run_if_built_in_command(aliases, splitted_query);
    if (exit_status != 1000)
        return exit_status;
    else
        return execvp(splitted_query->elements[0], splitted_query->elements);
}