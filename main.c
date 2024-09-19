#include <stdio.h>

#include "includes/ring_buffer.h"

CREATE_RING_BUFFER_INFO(ring_buffer_info_t, int)

int main() {
  INIT_RING_BUFFER(ring_buffer, ring_buffer_info_t, int, 7)

  int i = 0;

  const int N_WRITE_TIMES = 4;

  for (i = 0; i < N_WRITE_TIMES; ++i) {
    ADD_VAL_RING_BUFFER(ring_buffer, i)
  }

  for (i = 0; i < N_WRITE_TIMES - 1; ++i) {
    int val = -1;
    GET_VAL_RING_BUFFER(ring_buffer, val)

    printf("read_index: %d | val: %d \n\r", ring_buffer.read_index, val);
  }

  for (i = 0; i < N_WRITE_TIMES; ++i) {
    ADD_VAL_RING_BUFFER(ring_buffer, i + 7)
  }

  for (i = 0; i < N_WRITE_TIMES - 1; ++i) {
    int val = -1;
    GET_VAL_RING_BUFFER(ring_buffer, val)

    printf("read_index: %d | val: %d \n\r", ring_buffer.read_index, val);
  }

  FREE_RING_BUFFER(ring_buffer)

  return 0;
}