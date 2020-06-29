#include <stdio.h>
#include <stdlib.h>
#include "object.h"
#include "list.h"

List *add_variable(Object *variables, List *list)
{
    List *splitted_command = split('=', list->first->value);
    char *key = splitted_command->first->value;
    List *variable_value = create_list();
    Element *p_walker = splitted_command->first->next;
    while (p_walker != NULL)
    {
        push(variable_value, p_walker->value);
        p_walker = p_walker->next;
    }
    add_kv_pair(variables, key, variable_value);
    return list;
}

List *resolve_variable(Object *variables, List *list)
{
    if (includes(list, '='))
        return add_variable(variables, list);
    Element *p_walker = list->first;
    while (p_walker != NULL)
    {
        KV_pair *pair = get_kv_pair(variables, p_walker->value);
        if (pair != NULL)
            p_walker->value = pair->value->first->value;
        p_walker = p_walker->next;
    }
    if (list->length == 1)
        printf("%s\n", list->first->value);
    return list;
}