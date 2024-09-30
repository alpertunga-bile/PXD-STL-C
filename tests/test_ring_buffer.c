#include "test_ring_buffer.h"

SOURCE_DECLARE_RING_BUFFER_FUNCS(temp_ring_buffer, ring_buffer_t, int)

#include <stdio.h>

int test_ring_buffer_w_funcs() {
  ring_buffer_t ring_buffer;
  size_t buffer_capacity = 3;

  init_temp_ring_buffer_info(&ring_buffer, buffer_capacity);

  int i = 0;
  for (i = 0; i < 10; ++i) {
    add_value_temp_ring_buffer(&ring_buffer, &i);
  }

  printf("------------------------------------------\n\r");
  for (i = 0; i < buffer_capacity; ++i) {
    printf("index %4d : %4d\n\r", i, ring_buffer.buffer[i]);
  }
  printf("------------------------------------------\n\r");

  int value = 0;
  int ret_val = get_value_temp_ring_buffer(&ring_buffer, &value);

  if (1 == ret_val) {
    printf("Cannot get the result from the ring buffer");
    return ret_val;
  }

  printf("Value : %d\n\r", value);

  free_temp_ring_buffer(&ring_buffer);

  return 0;
}

int test_ring_buffer_w_macros() {
  ring_buffer_t ring_buffer;
  size_t buffer_capacity = 3;

  INIT_RING_BUFFER(ring_buffer, ring_buffer_t, int, buffer_capacity)

  int i = 0;
  for (i = 0; i < 10; ++i) {
    ADD_VAL_RING_BUFFER(ring_buffer, i)
  }

  printf("------------------------------------------\n\r");
  for (i = 0; i < buffer_capacity; ++i) {
    printf("%4d index : %4d\n\r", i, ring_buffer.buffer[i]);
  }
  printf("------------------------------------------\n\r");

  int value = 0;
  GET_VAL_RING_BUFFER(ring_buffer, value)

  printf("Value : %d\n\r", value);

  FREE_RING_BUFFER(ring_buffer)

  return 0;
}