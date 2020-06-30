#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "list.h"
#include "object.h"
#include "alias.h"
#include "variable.h"
#include "built_in.h"

int change_dir(Element *path)
{
    if (path == NULL)
        return chdir("~");
    else
        return chdir(path->value);
}

char **built_in_handler(Object *aliases, Object *variables, List *command)
{
    if (includes(command, '$') == 1)
    {
        resolve_variable(variables, command);
    }
    List *parsed_command = resolve_alias(aliases, command);
    if (parsed_command == NULL)
    {
        return NULL;
    }
    if (strcmp(parsed_command->first->value, "cd") == 0)
    {
        change_dir(parsed_command->first->next);
    }
    return convert_to_array(parsed_command);
}