#ifndef TEST_TEST_RING_BUFFER_H
#define TEST_TEST_RING_BUFFER_H

#include "ring_buffer.h"

CREATE_RING_BUFFER_INFO(ring_buffer_t, int)

FORWARD_DECLARE_RING_BUFFER_FUNCS(temp_ring_buffer, ring_buffer_t, int)

int test_ring_buffer_w_funcs();
int test_ring_buffer_w_macros();

#endif