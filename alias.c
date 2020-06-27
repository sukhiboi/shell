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
        printf("%s %s\n", p_walker->key, p_walker->value);
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
            printf("%s %s\n", p_walker->key, p_walker->value);
        p_walker = p_walker->next;
    }
    return 0;
}

int save_alias(Object *aliases, Array_P query)
{
    Array_P splitted_alias = split(query->elements[1], '=');
    char *key = splitted_alias->elements[0];
    char *value = splitted_alias->elements[1];
    if (key == NULL || value == NULL)
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