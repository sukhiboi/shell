    #include <stdio.h>
    #include <stdlib.h>
#include "parser.h"

int string_length(Char_P string)
{
    int length = 0;
    while (string[length] != '\0')
        length++;
    return length + 1;
}

int get_number_of_splits(Char_P string, char seperator, int length)
{
    int number_of_splits = 1;
    for (int i = 0; i < length; i++)
    {
        if (string[i] == seperator)
            number_of_splits++;
    }
    return number_of_splits;
}

void print_split_string(Array_P split_string)
{
    for (int i = 0; i < split_string->length; i++)
    {
        printf("%s ", split_string->elements[i]);
    }
}

Array_P create_array(int length)
{
    Array_P array = malloc(sizeof(Array));
    array->length = length;
    array->elements = malloc(sizeof(Char_P) * array->length);
    return array;
}

Array_P split(Char_P actual_string, char seperator)
{
    int length = string_length(actual_string);
    int number_of_splits = get_number_of_splits(actual_string, seperator, length);
    Array_P array = create_array(number_of_splits);
    Char_P string = malloc(sizeof(char) * length);
    array->elements[0] = &string[0];
    int pos = 1;
    for (int i = 0; i < length; i++)
    {
        string[i] = actual_string[i];
        if (actual_string[i] == seperator)
        {
            array->elements[pos] = &string[i + 1];
            string[i] = '\0';
            pos++;
        }
    }
    return array;
}