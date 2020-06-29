#ifndef __ALIAS_H_
#define __ALIAS_H_

#include "list.h"
#include "object.h"

List *parse_command_with_alias(Object *aliases, List *list);
List *resolve_alias(Object *aliases, List *list);

#endif