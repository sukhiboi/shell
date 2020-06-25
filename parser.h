#ifndef __PARSER_H_
#define __PARSER_H_

typedef char* Char_P ;

typedef struct
{
    Char_P  *elements;
    int length;
} Array;

typedef Array *Array_P ;

int string_length(Char_P  string);
int get_number_of_splits(Char_P  string, char seperator, int length);
Array_P  create_array(int length);
Array_P  split(Char_P  actual_string, char seperator);
void print_split_string(Array_P  split_string);

#endif