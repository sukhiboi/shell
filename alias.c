#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "list.h"
#include "object.h"

List *parse_command_with_alias(Object *aliases, List *command)
{
    List *parsed_alias_command = create_list();
    Element *p_walker = command->first;
    while (p_walker != NULL)
    {
        KV_pair *pair = get_kv_pair(aliases, p_walker->value);
        if (pair == NULL)
        {
            push(parsed_alias_command, p_walker->value);
        }
        else
        {
            Element *pair_p_walker = pair->value->first;
            while (pair_p_walker != NULL)
            {
                push(parsed_alias_command, pair_p_walker->value);
                pair_p_walker = pair_p_walker->next;
            }
        }
        p_walker = p_walker->next;
    }
    return parsed_alias_command;
}

List *add_new_alias(Object *aliases, List *command)
{
    List *splitted_command = split('=', command->first->next->value);
    char *key = splitted_command->first->value;

    List *alias_value = create_list();
    push(alias_value, splitted_command->first->next->value);
    Element *p_walker = command->first->next->next;
    while (p_walker != NULL)
    {
        push(alias_value, p_walker->value);
        p_walker = p_walker->next;
    }
    add_kv_pair(aliases, key, alias_value);
    return NULL;
}

List *print_alias(Object *aliases, List *command)
{
    KV_pair *p_walker = aliases->first;
    while (p_walker != NULL)
    {
        if (strcmp(command->first->next->value, p_walker->key) == 0)
        {
            printf("%s =", p_walker->key);
            Element *value_p_walker = p_walker->value->first;
            while (value_p_walker != NULL)
            {
                printf(" %s", value_p_walker->value);
                value_p_walker = value_p_walker->next;
            }
            return NULL;
        }
        p_walker = p_walker->next;
    }
    return NULL;
}

List *print_all_aliases(Object *aliases)
{
    KV_pair *p_walker = aliases->first;
    while (p_walker != NULL)
    {
        printf("%s =", p_walker->key);
        Element *value_p_walker = p_walker->value->first;
        while (value_p_walker != NULL)
        {
            printf(" %s", value_p_walker->value);
            value_p_walker = value_p_walker->next;
        }
        p_walker = p_walker->next;
    }
    return NULL;
}

List *resolve_alias(Object *aliases, List *command)
{
    List *parsed = parse_command_with_alias(aliases, command);
    if (strcmp(parsed->first->value, "alias") == 0)
    {
        if (parsed->first->next != NULL)
        {
            if (includes(parsed, '=') == 1)
            {
                return add_new_alias(aliases, parsed);
            }
            else
            {
                return print_alias(aliases, parsed);
            }
        }
        else
        {
            return print_all_aliases(aliases);
        }
    }
    return parsed;
}