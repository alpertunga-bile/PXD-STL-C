#ifndef TESTS_TEST_DYNAMIC_ARRAY_H
#define TESTS_TEST_DYNAMIC_ARRAY_H

#include "dynamic_array.h"

CREATE_DYNAMIC_ARRAY_INFO(da_info_t, int)

FORWARD_DECLARE_DYNAMIC_ARRAY_FUNCS(temp_da, da_info_t, int)

int test_dynamic_array_w_funcs();
int test_dynamic_array_w_macros();

#endif