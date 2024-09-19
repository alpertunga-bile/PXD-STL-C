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

#define FREE_RING_BUFFER(RB_NAME) free((RB_NAME).buffer);

#endif RING_BUFFER_H