#ifndef TESTS_TEST_LINKED_LIST_H
#define TESTS_TEST_LINKED_LIST_H

#include "linked_list.h"

CREATE_LINKED_LIST_NODE_STRUCT(ll_info_t, ll_node_t, int)

FORWARD_DECLARE_LINKED_LIST_FUNCS(temp_ll, ll_info_t, int)

int test_linked_list_w_funcs();
int test_linked_list_w_macros();

#endif