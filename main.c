#include <stdio.h>

#include "includes/ring_buffer.h"

CREATE_RING_BUFFER_INFO(ring_buffer_info_t, int)

int main() {
  INIT_RING_BUFFER(ring_buffer, ring_buffer_info_t, int, 7)

  int i = 0;

  for (i = 0; i < 7; ++i) {
    ADD_VAL_RING_BUFFER(ring_buffer, i)
  }

  for (i = 0; i < 7; ++i) {
    int val = -1;
    GET_VAL_RING_BUFFER(ring_buffer, val)

    printf("val: %d \n\r", val);
  }

  FREE_RING_BUFFER(ring_buffer)

  return 0;
}