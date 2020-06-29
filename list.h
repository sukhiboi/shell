#ifndef __LIST_H_
#define __LIST_H_

typedef struct element
{
    char *value;
    struct element *next;
} Element;

typedef struct list
{
    Element *first;
    int length;
} List;

List *create_list(void);
void push(List *list, char *element);
List *split(char character, char *string);
char **convert_to_array(List *list);
int includes(List *list, char character);

#endif