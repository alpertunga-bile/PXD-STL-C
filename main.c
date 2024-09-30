#include <stdio.h>

#include "tests/test_hash_map.h"

int main() {
  int ret_val = test_hash_map_w_funcs();
  ret_val = test_hash_map_w_macros();

  return 0;
}
