#ifndef lispy_list_h
#define lispy_list_h

#include "value.h"

Value *builtin_list(Value *value);
Value *builtin_head(Value *value);
Value *builtin_tail(Value *value);
Value *builtin_join(Value *value);
Value *builtin_eval(Value *value);

#endif
