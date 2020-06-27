#ifndef __ALIAS_H_
#define __ALIAS_H_

#include "parser.h"
#include "object.h"

int show_all_aliases(Object *aliases);
int show_alias(Object *aliases, char *command);
int save_alias(Object *aliases, Array_P query);
int process_alias(Object *aliases, Array_P query);


#endif