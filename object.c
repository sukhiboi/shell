#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"

Object *create_object(void)
{
    Object *obj = malloc(sizeof(Object));
    obj->first = NULL;
    obj->count = 0;
    return obj;
}

KV_pair *create_kv_pair(char *key, List *value)
{
    KV_pair *pair = malloc(sizeof(KV_pair));
    pair->key = key;
    pair->value = value;
    pair->next = NULL;
    return pair;
}

void add_kv_pair(Object *obj, char *key, List *value)
{
    KV_pair *new_pair = create_kv_pair(key, value);
    obj->count++;
    if (obj->first == NULL)
    {
        obj->first = new_pair;
    }
    else
    {
        KV_pair *p_walker = obj->first;
        while (p_walker->next != NULL)
        {
            p_walker = p_walker->next;
        }
        p_walker->next = new_pair;
    }
}

KV_pair *get_kv_pair(Object *obj, char *key)
{
    KV_pair *p_walker = obj->first;
    while (p_walker != NULL)
    {
        if (strcmp(p_walker->key, key) == 0)
        {
            return p_walker;
        }
        p_walker = p_walker->next;
    }
    return NULL;
}