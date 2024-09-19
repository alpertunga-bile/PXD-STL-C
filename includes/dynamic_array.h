#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdlib.h>
#include <string.h>

#define INIT_DYNAMIC_ARRAY(DA_NAME, DA_STRUCT_NAME, DA_TYPE, DA_INIT_SIZE)     \
  typedef struct {                                                             \
    unsigned int element_size;                                                 \
    unsigned int total_capacity;                                               \
    DA_TYPE *array;                                                            \
  } DA_STRUCT_NAME;                                                            \
  DA_STRUCT_NAME DA_NAME;                                                      \
  memset(&DA_NAME, 0, sizeof(DA_STRUCT_NAME));

#define FREE_DYNAMIC_ARRAY(DA_NAME) free((DA_NAME).array);

#endif