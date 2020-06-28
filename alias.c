#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "parser.h"
#include "object.h"

int has_char(char *str, char character)
{
    int p_walker = 0;
    while (str[p_walker] != '\0')
    {
        if (str[p_walker] == character)
            return 1;
        p_walker++;
    }
    return 0;
}

int show_all_aliases(Object *aliases)
{
    KV_pair *p_walker = aliases->first;
    while (p_walker != NULL)
    {
        printf("%s ", p_walker->key);
        for (int i = 0; i < p_walker->value->length; i++)
            printf("%s ", p_walker->value->elements[i]);
        printf("\n");
        p_walker = p_walker->next;
    }
    return 0;
}

int show_alias(Object *aliases, char *command)
{
    KV_pair *p_walker = aliases->first;
    while (p_walker != NULL)
    {
        if (strcmp(p_walker->key, command) == 0)
        {
            for (int i = 0; i < p_walker->value->length; i++)
                printf("%s ", p_walker->value->elements[i]);
            printf("\n");
        }
        p_walker = p_walker->next;
    }
    return 0;
}

int save_alias(Object *aliases, Array_P query)
{
    Array_P splitted_alias = split(query->elements[1], '=');
    char *key = splitted_alias->elements[0];
    Array_P value = create_array(query->length - 2);
    value->elements[0] = splitted_alias->elements[1];
    for (int i = 2, value_idx = 1; i < query->length - 1; i++)
        value->elements[value_idx] = query->elements[i];
    if (key == NULL || splitted_alias->elements[1] == NULL)
        return -1;
    add_kv_pair(aliases, key, value);
    return 0;
}

int process_alias(Object *aliases, Array_P query)
{
    if (query->elements[1] == NULL)
        return show_all_aliases(aliases);
    if (has_char(query->elements[1], '='))
        return save_alias(aliases, query);
    if (query->elements[1] != NULL)
        return show_alias(aliases, query->elements[1]);
    return -1;
}

int run_if_alias(Object *aliases, Array_P alias)
{
    print_split_string(alias);
    KV_pair *alias_details = get_kv_pair(aliases, alias->elements[0]);
    if (alias_details == NULL)
        return 1001;
    Array_P final = create_array(alias_details->value->length + alias->length - 1);
    int final_command_idx = 0;
    for (int i = 0; i < alias_details->value->length; i++)
        final->elements[final_command_idx++] = alias_details->value->elements[i];
    for (int i = 1; i < alias->length; i++)
        final->elements[final_command_idx++] = alias->elements[i];
    return execvp(final->elements[0], final->elements);
}