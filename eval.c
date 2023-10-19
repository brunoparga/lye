#include "eval.h"

static Value *evaluate_sexpr(Value *value) {
  /* Evaluate children */
  for (int index = 0; index < count(value); index++) {
    value->sexpr.cell[index] = evaluate(element_at(value, index));
    if (IS_ERROR(element_at(value, index))) {
      return take_value(value, index);
    }
  }

  /* Empty expression, () */
  if (count(value) == 0) {
    return value;
  }

  if (count(value) == 1) {
    return take_value(value, 0);
  }

  /* Ensure first element is a Symbol */
  Value *first = pop_value(value, 0);
  if (!IS_SYMBOL(first)) {
    delete_value(first);
    delete_value(value);
    return make_error("S-expression does not start with a symbol.");
  }

  /* Pass operator for calculation */
  Value *result = compute(value, &first->symbol);
  delete_value(first);
  return result;
}

Value *evaluate(Value *value) {
  /* Evaluate S-expressions */
  if (IS_SEXPR(value)) {
    return evaluate_sexpr(value);
  }

  /* All other Value types remain the same */
  return value;
}
