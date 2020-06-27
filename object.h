#ifndef __OBJECT_H_
#define __OBJECT_H_

typedef struct kv_pair
{
    char *key;
    char *value;
    struct kv_pair *next;
} KV_pair;

typedef struct object
{
    KV_pair *first;
} Object;

Object *create_object(void);
KV_pair *create_kv_pair(char *key, char *value);
void add_kv_pair(Object *obj, char *key, char *value);
KV_pair *get_kv_pair(Object *obj, char *key);

#endif