#include "test_dynamic_array.h"

SOURCE_DECLARE_DYNAMIC_ARRAY_FUNCS(temp_da, da_info_t, int)

int test_dynamic_array_w_funcs() {
  da_info_t da;

  init_temp_da_info(&da, 5);

  if (5 != da.total_capacity) {
    printf("Total capacity is wrong, %zu\n\r", da.total_capacity);
    return 1;
  }

  int i = 0;
  for (i = 0; i < 102; ++i) {
    add_temp_da(&da, &i);
  }

  if (102 != da.element_size) {
    printf("Element size is wrong, %zu\n\r", da.element_size);
    return 1;
  }

  shrink_temp_da(&da);

  if (da.element_size != da.total_capacity) {
    printf("Shrink is failed: %zu vs %zu\n\r", da.element_size,
           da.total_capacity);
    return 1;
  }

  free_temp_da(&da);

  printf("Passed all the func tests\n\r");

  return 0;
}

int test_dynamic_array_w_macros() {
  da_info_t da;

  INIT_DYNAMIC_ARRAY(da, da_info_t, int, 5)

  if (5 != da.total_capacity) {
    printf("Total capacity is wrong, %zu\n\r", da.total_capacity);
    return 1;
  }

  int i = 0;
  for (i = 0; i < 102; ++i) {
    ADD_DYNAMIC_ARRAY(da, i)
  }

  if (102 != da.element_size) {
    printf("Element size is wrong, %zu\n\r", da.element_size);
    return 1;
  }

  SHRINK_DYNAMIC_ARRAY(da)

  if (da.element_size != da.total_capacity) {
    printf("Shrink is failed: %zu vs %zu\n\r", da.element_size,
           da.total_capacity);
    return 1;
  }

  FREE_DYNAMIC_ARRAY(da)

  printf("Passed all the func tests\n\r");

  return 0;
}