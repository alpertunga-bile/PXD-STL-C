#include <stdio.h>

#include "includes/dynamic_array.h"

CREATE_DYNAMIC_ARRAY_INFO(vector_info_t, int)

int main() {
  INIT_DYNAMIC_ARRAY(vector, vector_info_t, int, 5)

  int i;

  for (i = 0; i < 12; ++i) {
    ADD_DYNAMIC_ARRAY(vector, i)
  }

  SHRINK_DYNAMIC_ARRAY(vector)

  for (i = 0; i < vector.element_size; ++i) {
    printf("Values %d index : %d \n\r", i, vector.array[i]);
  }

  PRINT_DYNAMIC_ARRAY_INFO(vector)

  FREE_DYNAMIC_ARRAY(vector)

  return 0;
}