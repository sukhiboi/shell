#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"

Object *create_object(void)
{
    Object *obj = malloc(sizeof(Object));
    obj->first = NULL;
    return obj;
}

KV_pair *create_kv_pair(char *key, Array_P value)
{
    KV_pair *pair = malloc(sizeof(KV_pair));
    pair->key = key;
    pair->value = value;
    pair->next = NULL;
    return pair;
}

void add_kv_pair(Object *obj, char *key, Array_P value)
{
    KV_pair *new_pair = create_kv_pair(key, value);
    KV_pair *p_walker = obj->first;
    if (p_walker == NULL)
    {
        obj->first = new_pair;
        return;
    }
    while (p_walker->next != NULL)
    {
        p_walker = p_walker->next;
    }
    p_walker->next = new_pair;
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