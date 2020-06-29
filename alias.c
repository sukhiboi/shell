#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "list.h"
#include "object.h"

void print_list(List *l)
{
    Element *f = l->first;
    while (f != NULL)
    {
        printf("%s ", f->value);
        f = f->next;
    }
    printf("\n");
}

// void print_object(Object *p)
// {
//     KV_pair *p_walker = p->first;
//     while (p_walker != NULL)
//     {
//         printf("%s- =", p_walker->key);
//         Element *value_p_walker = p_walker->value->first;
//         while (value_p_walker != NULL)
//         {
//             printf(" %s", value_p_walker->value);
//             value_p_walker = value_p_walker->next;
//         }
//         printf("\n");
//         p_walker = p_walker->next;
//     }
// }

List *parse_command_with_alias(Object *aliases, List *list)
{
    printf("simple parsing\n");
    List *parsed_alias_command = create_list();
    Element *p_walker = list->first;
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

List *add_new_alias(Object *aliases, List *list)
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

List *print_alias(Object *aliases, List *list)
{
    printf("printing one alias\n");
    KV_pair *p_walker = aliases->first;
    while (p_walker != NULL)
    {
        if (strcmp(list->first->next->value, p_walker->key) == 0)
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

void print_all_aliases(Object *aliases)
{
    printf("printing all alias\n");
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
}

List *resolve_alias(Object *aliases, List *list)
{
    List *parsed = parse_command_with_alias(aliases, list);
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
            print_all_aliases(aliases);
        }
    }
    return parsed;
}
