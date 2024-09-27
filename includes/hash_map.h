#ifndef INCLUDES_HASH_MAP_H
#define INCLUDES_HASH_MAP_H

#include "hash.h"
#include <stdlib.h>
#include <string.h>

#define CREATE_HASH_MAP_INFO(HM_LINKED_LIST_STRUCT_NAME, HM_STRUCT_NAME,       \
                             HM_KEY_DATA_TYPE, HM_VALUE_DATA_TYPE, HM_SIZE)    \
  typedef struct {                                                             \
    HM_VALUE_DATA_TYPE value;                                                  \
    void *next;                                                                \
  } HM_LINKED_LIST_STRUCT_NAME;                                                \
                                                                               \
  typedef struct {                                                             \
    HM_LINKED_LIST_STRUCT_NAME map[HM_SIZE];                                   \
    size_t capacity;                                                           \
    size_t (*hash_function)(HM_KEY_DATA_TYPE);                                 \
  } HM_STRUCT_NAME;

#define INIT_HASH_MAP_INFO(HM_NAME, HM_LINKED_LIST_STRUCT_NAME,                \
                           HM_STRUCT_NAME, HM_HASH_FUNCTION, HM_SIZE)          \
  memset(&HM_NAME, 0, sizeof(HM_STRUCT_NAME));                                 \
  (HM_NAME).hash_function = &HM_HASH_FUNCTION;                                 \
  (HM_NAME).capacity = HM_SIZE;

#define CONTAINS_VALUE_HASH_MAP(HM_NAME, HM_LINKED_LIST_STRUCT_NAME, HM_KEY,   \
                                HM_VALUE, HM_BOOL_VARIABLE)                    \
  {                                                                            \
    size_t hash_value = (*(HM_NAME).hash_function)(HM_KEY);                    \
    int index = hash_value % ((HM_NAME).capacity);                             \
    HM_BOOL_VARIABLE = 0;                                                      \
                                                                               \
    HM_LINKED_LIST_STRUCT_NAME *current_node = &(HM_NAME).map[index];          \
    HM_LINKED_LIST_STRUCT_NAME *prev_node = NULL;                              \
                                                                               \
    while (NULL != current_node) {                                             \
      if ((HM_VALUE) == current_node->value) {                                 \
        HM_BOOL_VARIABLE = 1;                                                  \
        break;                                                                 \
      }                                                                        \
                                                                               \
      prev_node = current_node;                                                \
      current_node = (HM_LINKED_LIST_STRUCT_NAME *)(current_node->next);       \
    }                                                                          \
  }

#define ADD_VALUE_HASH_MAP(HM_NAME, HM_LINKED_LIST_STRUCT_NAME,                \
                           HM_KEY_DATA_TYPE, HM_KEY, HM_VALUE)                 \
  {                                                                            \
    size_t hash_value = (*(HM_NAME).hash_function)(HM_KEY);                    \
    int index = hash_value % ((HM_NAME).capacity);                             \
    int found = 0;                                                             \
                                                                               \
    HM_LINKED_LIST_STRUCT_NAME *current_node = &(HM_NAME).map[index];          \
    HM_LINKED_LIST_STRUCT_NAME *prev_node = NULL;                              \
                                                                               \
    while (NULL != current_node) {                                             \
      if ((HM_VALUE) == current_node->value) {                                 \
        found = 1;                                                             \
        break;                                                                 \
      }                                                                        \
                                                                               \
      prev_node = current_node;                                                \
      current_node = (HM_LINKED_LIST_STRUCT_NAME *)(current_node->next);       \
    }                                                                          \
                                                                               \
    if (0 == found) {                                                          \
      if (NULL == (HM_NAME).map[index].next) {                                 \
        (HM_NAME).map[index].value = HM_VALUE;                                 \
      } else {                                                                 \
        HM_LINKED_LIST_STRUCT_NAME *new_node =                                 \
            malloc(sizeof(HM_LINKED_LIST_STRUCT_NAME));                        \
        memset(new_node, 0, sizeof(HM_LINKED_LIST_STRUCT_NAME));               \
        new_node->value = HM_VALUE;                                            \
        prev_node->next = new_node;                                            \
      }                                                                        \
    }                                                                          \
  }

#define FREE_HASH_MAP(HM_NAME, HM_LINKED_LIST_STRUCT_NAME)                     \
  {                                                                            \
    int i;                                                                     \
    int capacity = (HM_NAME).capacity;                                         \
                                                                               \
    for (i = 0; i < capacity; ++i) {                                           \
      HM_LINKED_LIST_STRUCT_NAME *current_node = &(HM_NAME).map[i];            \
                                                                               \
      if (NULL == current_node->next) {                                        \
        continue;                                                              \
      }                                                                        \
                                                                               \
      current_node = (HM_LINKED_LIST_STRUCT_NAME *)current_node->next;         \
      HM_LINKED_LIST_STRUCT_NAME *prev_node = NULL;                            \
                                                                               \
      while (NULL != current_node) {                                           \
        prev_node = current_node;                                              \
        current_node = (HM_LINKED_LIST_STRUCT_NAME *)current_node->next;       \
                                                                               \
        free(prev_node);                                                       \
      }                                                                        \
    }                                                                          \
  }

#endif