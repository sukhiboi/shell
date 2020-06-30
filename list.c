#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

List *create_list(void)
{
    List *list = malloc(sizeof(List));
    list->first = NULL;
    list->length = 0;
    return list;
}

void push(List *list, char *element)
{
    Element *e = malloc(sizeof(Element));
    e->value = element;
    e->next = NULL;
    list->length++;
    Element *p_walker = list->first;
    if (p_walker == NULL)
    {
        list->first = e;
        return;
    }
    while (p_walker->next != NULL)
        p_walker = p_walker->next;
    p_walker->next = e;
}

List *split(char character, char *string)
{
    List *split_string = create_list();
    int length = strlen(string) + 1;
    char *string_on_heap = malloc(sizeof(char) * length);
    strcpy(string_on_heap, string);
    push(split_string, &string_on_heap[0]);
    for (int i = 1; i < length; i++)
        if (string_on_heap[i] == character)
        {
            string_on_heap[i] = '\0';
            push(split_string, &string_on_heap[i + 1]);
        }
    return split_string;
}

char **convert_to_array(List *list)
{
    char **array = malloc(sizeof(char *) * (list->length + 1));
    Element *element = list->first;
    for (int i = 0; i < list->length; i++)
    {
        array[i] = element->value;
        element = element->next;
    }
    array[list->length] = NULL;
    return array;
}

int includes(List *list, char character)
{
    Element *p_walker = list->first;
    while (p_walker != NULL)
    {
        int length = strlen(p_walker->value);
        for (int i = 0; i < length; i++)
        {
            if (p_walker->value[i] == character)
                return 1;
        }
        p_walker = p_walker->next;
    }
    return 0;
}