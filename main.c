#include <stdio.h>

#include "tests/test_dynamic_array.h"

int main() {
  int ret_val = 0;

  ret_val = test_dynamic_array_w_funcs();
  ret_val = test_dynamic_array_w_macros();

  return 0;
}
