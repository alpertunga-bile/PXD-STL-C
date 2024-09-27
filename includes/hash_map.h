#ifndef INCLUDES_HASH_MAP_H
#define INCLUDES_HASH_MAP_H

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
    size_t total_elems;                                                        \
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
                                                                               \
      (HM_NAME).total_elems++;                                                 \
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
                                                                               \
    (HM_NAME).total_elems = 0;                                                 \
  }

#define FORWARD_DECLARE_HASH_MAP_FUNCS(HM_FUNC_ID, HM_LINKED_LIST_STRUCT_NAME, \
                                       HM_STRUCT_NAME, HM_KEY_DATA_TYPE,       \
                                       HM_VALUE_DATA_TYPE)                     \
                                                                               \
  void init_##HM_FUNC_ID##_info(HM_STRUCT_NAME *hash_map_info,                 \
                                size_t map_capacity,                           \
                                size_t (*func)(HM_KEY_DATA_TYPE));             \
                                                                               \
  int contains_value_##HM_FUNC_ID##(HM_STRUCT_NAME * hash_map_info,            \
                                    HM_KEY_DATA_TYPE key,                      \
                                    HM_VALUE_DATA_TYPE value);                 \
                                                                               \
  void add_value_##HM_FUNC_ID##(HM_STRUCT_NAME * hash_map_info,                \
                                HM_KEY_DATA_TYPE key,                          \
                                HM_VALUE_DATA_TYPE value);                     \
                                                                               \
  void free_##HM_FUNC_ID##(HM_STRUCT_NAME * hash_map_info);

#define SOURCE_DECLARE_HASH_MAP_FUNCS(HM_FUNC_ID, HM_LINKED_LIST_STRUCT_NAME,  \
                                      HM_STRUCT_NAME, HM_KEY_DATA_TYPE,        \
                                      HM_VALUE_DATA_TYPE)                      \
                                                                               \
  void init_##HM_FUNC_ID##_info(HM_STRUCT_NAME *hash_map_info,                 \
                                size_t map_capacity,                           \
                                size_t (*func)(HM_KEY_DATA_TYPE)) {            \
    memset(hash_map_info, 0, sizeof(HM_STRUCT_NAME));                          \
    hash_map_info->capacity = map_capacity;                                    \
    hash_map_info->hash_function = func;                                       \
  }                                                                            \
                                                                               \
  size_t get_index_from_hash_##HM_FUNC_ID##(HM_STRUCT_NAME * hash_map_info,    \
                                            HM_KEY_DATA_TYPE key) {            \
    size_t hash_value = (*(hash_map_info->hash_function))(key);                \
    size_t index = hash_value % (hash_map_info->capacity);                     \
                                                                               \
    return index;                                                              \
  }                                                                            \
                                                                               \
  int find_set_prev_current_node_##HM_FUNC_ID##(                               \
      HM_STRUCT_NAME * hash_map_info, size_t index, HM_VALUE_DATA_TYPE value,  \
      HM_LINKED_LIST_STRUCT_NAME * prev_node,                                  \
      HM_LINKED_LIST_STRUCT_NAME * current_node) {                             \
    int found = 0;                                                             \
                                                                               \
    current_node = &(hash_map_info->map[index]);                               \
    prev_node = NULL;                                                          \
                                                                               \
    while (NULL != current_node) {                                             \
      if (value == current_node->value) {                                      \
        found = 1;                                                             \
        break;                                                                 \
      }                                                                        \
                                                                               \
      prev_node = current_node;                                                \
      current_node = (HM_LINKED_LIST_STRUCT_NAME *)(current_node->next);       \
    }                                                                          \
                                                                               \
    return found;                                                              \
  }                                                                            \
                                                                               \
  int contains_value_##HM_FUNC_ID##(HM_STRUCT_NAME * hash_map_info,            \
                                    HM_KEY_DATA_TYPE key,                      \
                                    HM_VALUE_DATA_TYPE value) {                \
    int index = get_index_from_hash_##HM_FUNC_ID##(hash_map_info, key);        \
                                                                               \
    HM_LINKED_LIST_STRUCT_NAME *current_node = NULL;                           \
    HM_LINKED_LIST_STRUCT_NAME *prev_node = NULL;                              \
                                                                               \
    return find_set_prev_current_node_##HM_FUNC_ID##(                          \
        hash_map_info, index, value, prev_node, current_node);                 \
  }                                                                            \
                                                                               \
  void add_value_##HM_FUNC_ID##(HM_STRUCT_NAME * hash_map_info,                \
                                HM_KEY_DATA_TYPE key,                          \
                                HM_VALUE_DATA_TYPE value) {                    \
    int index = get_index_from_hash_##HM_FUNC_ID##(hash_map_info, key);        \
                                                                               \
    HM_LINKED_LIST_STRUCT_NAME *current_node = NULL;                           \
    HM_LINKED_LIST_STRUCT_NAME *prev_node = NULL;                              \
                                                                               \
    int found = find_set_prev_current_node_##HM_FUNC_ID##(                     \
        hash_map_info, index, value, prev_node, current_node);                 \
                                                                               \
    if (1 == found) {                                                          \
      return;                                                                  \
    }                                                                          \
                                                                               \
    if (NULL == hash_map_info->map[index].next) {                              \
      hash_map_info->map[index].value = value;                                 \
    } else {                                                                   \
      HM_LINKED_LIST_STRUCT_NAME *new_node =                                   \
          malloc(sizeof(HM_LINKED_LIST_STRUCT_NAME));                          \
      memset(new_node, 0, sizeof(HM_LINKED_LIST_STRUCT_NAME));                 \
      new_node->value = value;                                                 \
      prev_node->next = new_node;                                              \
    }                                                                          \
                                                                               \
    hash_map_info->total_elems++;                                              \
  }                                                                            \
                                                                               \
  void free_##HM_FUNC_ID##(HM_STRUCT_NAME * hash_map_info) {                   \
    int i;                                                                     \
    int capacity = hash_map_info->capacity;                                    \
                                                                               \
    for (i = 0; i < capacity; ++i) {                                           \
      HM_LINKED_LIST_STRUCT_NAME *current_node = &(hash_map_info->map[i]);     \
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
        prev_node = NULL;                                                      \
      }                                                                        \
    }                                                                          \
                                                                               \
    hash_map_info->total_elems = 0;                                            \
  }

#endif