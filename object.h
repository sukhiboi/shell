#ifndef __OBJECT_H_
#define __OBJECT_H_

#include "list.h"

typedef struct kv_pair
{
    char *key;
    List *value;
    struct kv_pair *next;
} KV_pair;

typedef struct object
{
    KV_pair *first;
} Object;

Object *create_object(void);
KV_pair *create_kv_pair(char *key, List* value);
void add_kv_pair(Object *obj, char *key, List* value);
KV_pair *get_kv_pair(Object *obj, char *key);

#endif
