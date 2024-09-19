#include <stdio.h>

#include "includes/dynamic_array.h"

int main() {
  INIT_DYNAMIC_ARRAY(vector, vector_info_t, int, 5)

  FREE_DYNAMIC_ARRAY(vector)

  return 0;
}