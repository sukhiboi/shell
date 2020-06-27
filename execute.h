#ifndef __EXECUTE_H_
#define __EXECUTE_H_

#include "parser.h"
#include "object.h"

int save_alias(Object *aliases, char *alias_statement);
int run_if_built_in_command(Object *aliases, Array_P query);
int execute(Object *aliases, char *query);

#endif