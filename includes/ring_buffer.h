#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdlib.h>
#include <string.h>

/*
 * Generic ring buffer
 */

#define CREATE_RING_BUFFER_INFO(RB_STRUCT_NAME, RB_TYPE)                       \
  typedef struct {                                                             \
    RB_TYPE *buffer;                                                           \
    size_t capacity;                                                           \
    unsigned write_index;                                                      \
    unsigned read_index;                                                       \
  } RB_STRUCT_NAME;

#define INIT_RING_BUFFER(RB_NAME, RB_STRUCT_NAME, RB_TYPE, RB_INIT_SIZE)       \
  RB_STRUCT_NAME RB_NAME;                                                      \
  memset(&RB_NAME, 0, sizeof(RB_STRUCT_NAME));                                 \
  (RB_NAME).buffer = malloc(sizeof(RB_TYPE) * (RB_INIT_SIZE));                 \
  (RB_NAME).capacity = RB_INIT_SIZE;

#define ADD_VAL_RING_BUFFER(RB_NAME, RB_VALUE)                                 \
  {                                                                            \
    int calc_write_index = ((RB_NAME).write_index + 1) % (RB_NAME).capacity;   \
    if (calc_write_index != (RB_NAME).read_index) {                            \
      (RB_NAME).buffer[(RB_NAME).write_index] = RB_VALUE;                      \
      (RB_NAME).write_index = calc_write_index;                                \
    }                                                                          \
  }

#define GET_VAL_RING_BUFFER(RB_NAME, RB_VAL_NAME)                              \
  if ((RB_NAME).read_index != (RB_NAME).write_index) {                         \
    RB_VAL_NAME = (RB_NAME).buffer[(RB_NAME).read_index];                      \
    (RB_NAME).read_index = ((RB_NAME).read_index + 1) % (RB_NAME).capacity;    \
  }

#define FREE_RING_BUFFER(RB_NAME)                                              \
  free((RB_NAME).buffer);                                                      \
  (RB_NAME).buffer = NULL;

#endif RING_BUFFER_H