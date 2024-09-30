#include "test_linked_list.h"

SOURCE_DECLARE_LINKED_LIST_FUNCS(temp_ll, ll_info_t, ll_node_t, int)

int test_linked_list_w_funcs() {
  ll_info_t ll;

  init_temp_ll_info(&ll);

  int i = 0;
  for (i = 0; i < 100; ++i) {
    add_last_temp_ll(&ll, &i);
  }

  int first_value = ll.head->value;
  int last_value = ll.end->value;

  if (0 != first_value && 99 != last_value) {
    printf("First value is %4d and last value is %4d, which are wrong\n\r",
           first_value, last_value);
    return 1;
  }

  remove_head_temp_ll(&ll);

  first_value = ll.head->value;

  if (1 != first_value) {
    printf("First value is %4d, which is wrong\n\r", first_value);
    return 1;
  }

  int next_value = ((ll_node_t *)ll.head->next)->value;

  remove_value_temp_ll(&ll, &next_value);

  next_value = ((ll_node_t *)ll.head->next)->value;

  if (3 != next_value) {
    printf("Next value is %4d, which is wrong\n\r", next_value);
    return 1;
  }

  free_temp_ll(&ll);

  printf("All func tests are passed\n\r");

  return 0;
}

int test_linked_list_w_macros() {
  ll_info_t ll;

  INIT_LINKED_LIST_STRUCT(ll, ll_info_t)

  int i = 0;
  for (i = 0; i < 100; ++i) {
    ADD_LAST_LINKED_LIST(ll, ll_node_t, i)
  }

  int first_value = ll.head->value;
  int last_value = ll.end->value;

  if (0 != first_value && 99 != last_value) {
    printf("First value is %4d and last value is %4d, which are wrong\n\r",
           first_value, last_value);
    return 1;
  }

  REMOVE_HEAD_LINKED_LIST(ll, ll_node_t)

  first_value = ll.head->value;

  if (1 != first_value) {
    printf("First value is %4d, which is wrong\n\r", first_value);
    return 1;
  }

  int next_value = ((ll_node_t *)ll.head->next)->value;

  REMOVE_VALUE_LINKED_LIST(ll, ll_node_t, next_value)

  next_value = ((ll_node_t *)ll.head->next)->value;

  if (3 != next_value) {
    printf("Next value is %4d, which is wrong\n\r", next_value);
    return 1;
  }

  FREE_LINKED_LIST(ll, ll_node_t)

  printf("All macro tests are passed\n\r");

  return 0;
}