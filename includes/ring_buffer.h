#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdlib.h>
#include <string.h>

/*
 * Generic ring buffer
 */

/*
 * @brief Create the ring buffer info structure
 * @param RB_STRUCT_NAME Name of the structure
 * @param RB_TYPE        Type of the buffer's values
 * @example CREATE_RING_BUFFER_INFO(ring_buffer_info_t, int)
 */
#define CREATE_RING_BUFFER_INFO(RB_STRUCT_NAME, RB_TYPE)                       \
  typedef struct {                                                             \
    RB_TYPE *buffer;                                                           \
    size_t capacity;                                                           \
    unsigned write_index;                                                      \
    unsigned read_index;                                                       \
  } RB_STRUCT_NAME;

/*
 * @brief Create ring buffer variable and initialize it
 * @param RB_NAME        Name of the ring buffer variable
 * @param RB_STRUCT_NAME Name of the structure
 * @param RB_TYPE        Type of the buffer's values
 * @param RB_INIT_SIZE   Capacity of the ring buffer
 * @example INIT_RING_BUFFER(ring_buffer, ring_buffer_info_t, int, 7)
 */
#define INIT_RING_BUFFER(RB_NAME, RB_STRUCT_NAME, RB_TYPE, RB_INIT_SIZE)       \
  RB_STRUCT_NAME RB_NAME;                                                      \
  memset(&RB_NAME, 0, sizeof(RB_STRUCT_NAME));                                 \
  (RB_NAME).buffer = malloc(sizeof(RB_TYPE) * (RB_INIT_SIZE));                 \
  (RB_NAME).capacity = RB_INIT_SIZE;

/*
 * @brief Add value to the ring buffer
 * @if write_index is not equal to read_index
 * @param RB_NAME  Name of the ring buffer variable
 * @param RB_VALUE Value want to be inserted
 * @example ADD_VAL_RING_BUFFER(ring_buffer, 1)
 */
#define ADD_VAL_RING_BUFFER(RB_NAME, RB_VALUE)                                 \
  {                                                                            \
    int calc_write_index = ((RB_NAME).write_index + 1) % (RB_NAME).capacity;   \
    if (calc_write_index != (RB_NAME).read_index) {                            \
      (RB_NAME).buffer[(RB_NAME).write_index] = RB_VALUE;                      \
      (RB_NAME).write_index = calc_write_index;                                \
    }                                                                          \
  }

/*
 * @brief Get value from the ring buffer
 * @if read_index is not equal to write_index
 * @param RB_NAME     Name of the ring buffer variable
 * @param RB_VAL_NAME Name of the variable to be assigned
 * @example GET_VAL_RING_BUFFER(ring_buffer, val)
 */
#define GET_VAL_RING_BUFFER(RB_NAME, RB_VAL_NAME)                              \
  if ((RB_NAME).read_index != (RB_NAME).write_index) {                         \
    RB_VAL_NAME = (RB_NAME).buffer[(RB_NAME).read_index];                      \
    (RB_NAME).read_index = ((RB_NAME).read_index + 1) % (RB_NAME).capacity;    \
  }

/*
 * @brief Free the ring buffer
 * @param RB_NAME Name of the ring buffer variable
 * @example FREE_RING_BUFFER(ring_buffer)
 */
#define FREE_RING_BUFFER(RB_NAME)                                              \
  free((RB_NAME).buffer);                                                      \
  (RB_NAME).buffer = NULL;

#define FORWARD_DECLARE_RING_BUFFER_FUNCS(RB_FUNC_ID, RB_STRUCT_NAME, RB_TYPE) \
  void init_##RB_FUNC_ID##_info(RB_STRUCT_NAME *rb_info, size_t init_size);    \
                                                                               \
  int add_value_##RB_FUNC_ID##(RB_STRUCT_NAME * rb_info, RB_TYPE * value);     \
                                                                               \
  int get_value_##RB_FUNC_ID##(RB_STRUCT_NAME * rb_info, RB_TYPE * retun_val); \
                                                                               \
  void free##RB_FUNC_ID##(RB_STRUCT_NAME * rb_info);

#define SOURCE_DECLARE_RING_BUFFER_FUNCS(RB_FUNC_ID, RB_STRUCT_NAME, RB_TYPE)  \
  void init_##RB_FUNC_ID##_info(RB_STRUCT_NAME *rb_info, size_t init_size) {   \
    memset(rb_info, 0, sizeof(RB_STRUCT_NAME));                                \
    rb_info->buffer = malloc(sizeof(RB_TYPE) * init_size);                     \
    rb_info->capacity = init_size;                                             \
  }                                                                            \
                                                                               \
  int add_value_##RB_FUNC_ID##(RB_STRUCT_NAME * rb_info, RB_TYPE * value) {    \
    int calc_write_index = (rb_info->write_index + 1) % rb_info->capacity;     \
                                                                               \
    if (calc_write_index == rb_info->read_index) {                             \
      return 0;                                                                \
    }                                                                          \
                                                                               \
    rb_info->buffer[rb_info->write_index] = *value;                            \
    rb_info->write_index = calc_write_index;                                   \
                                                                               \
    return 1;                                                                  \
  }                                                                            \
                                                                               \
  int get_value_##RB_FUNC_ID##(RB_STRUCT_NAME * rb_info,                       \
                               RB_TYPE * return_val) {                         \
    if (rb_info->read_index == rb_info->write_index) {                         \
      return 0;                                                                \
    }                                                                          \
                                                                               \
    *return_val = rb_info->buffer[rb_info->read_index];                        \
    rb_info->read_index = (rb_info->read_index + 1) % rb_info->capacity;       \
                                                                               \
    return 1;                                                                  \
  }                                                                            \
                                                                               \
  void free##RB_FUNC_ID##(RB_STRUCT_NAME * rb_info) {                          \
    free(rb_info->buffer);                                                     \
    rb_info->buffer = NULL;                                                    \
  }

#endif RING_BUFFER_H