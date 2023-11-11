#ifndef lye_env_h
#define lye_env_h

#include <stdlib.h>
#include <string.h>

#include "calc.h"
#include "list.h"
#include "value.h"

typedef struct Env {
  int count;
  Symbol *keys;
  Value **values;
} Env;

/* Environment constructor and destructor */
Env *make_env();
void delete_env(Env *env);

/* Store and retrieve */
Value *get_value(Env *env, Value *key);
void put_value(Env *env, Value *key, Value *value);

/* Register language built-ins */
void register_builtin(Env *env, Symbol name, Builtin function);
void register_builtins(Env *env);

#endif