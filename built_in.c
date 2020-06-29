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

char **built_in_handler(Object *aliases, Object *variables, List *list)
{
    List *command = list;
    if (strcmp(command->first->value, "cd") == 0)
        change_dir(command->first->next);
    if (includes(command, '$') == 1)
        command = resolve_variable(variables, command);
    command = resolve_alias(aliases, command);
    return convert_to_array(command);
}