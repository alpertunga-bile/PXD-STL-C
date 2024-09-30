#include <stdio.h>

#include "tests/test_linked_list.h"

int main() {
  int ret_val = 0;

  ret_val = test_linked_list_w_funcs();
  ret_val = test_linked_list_w_macros();

  return 0;
}
