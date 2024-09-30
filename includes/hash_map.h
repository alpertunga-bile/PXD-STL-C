#ifndef INCLUDES_HASH_MAP_H
#define INCLUDES_HASH_MAP_H

#include <stdlib.h>
#include <string.h>

#define CREATE_HASH_MAP_INFO(HM_LINKED_LIST_STRUCT_NAME, HM_STRUCT_NAME,       \
                             HM_KEY_DATA_TYPE, HM_VALUE_DATA_TYPE, HM_SIZE)    \
  typedef struct {                                                             \
    HM_KEY_DATA_TYPE key;                                                      \
    HM_VALUE_DATA_TYPE value;                                                  \
    void *next;                                                                \
  } HM_LINKED_LIST_STRUCT_NAME;                                                \
                                                                               \
  typedef struct {                                                             \
    HM_LINKED_LIST_STRUCT_NAME *map[HM_SIZE];                                  \
    size_t capacity;                                                           \
    size_t total_elems;                                                        \
    size_t (*hash_function)(HM_KEY_DATA_TYPE);                                 \
  } HM_STRUCT_NAME;

#define INIT_HASH_MAP_INFO(HM_NAME, HM_LINKED_LIST_STRUCT_NAME,                \
                           HM_STRUCT_NAME, HM_HASH_FUNCTION, HM_SIZE)          \
  memset(&HM_NAME, 0, sizeof(HM_STRUCT_NAME));                                 \
  (HM_NAME).hash_function = &HM_HASH_FUNCTION;                                 \
  (HM_NAME).capacity = HM_SIZE;

#define CONTAINS_KEY_HASH_MAP(HM_NAME, HM_LINKED_LIST_STRUCT_NAME, HM_KEY,     \
                              HM_BOOL_VARIABLE)                                \
  {                                                                            \
    size_t hash_value = (*(HM_NAME).hash_function)(HM_KEY);                    \
    int index = hash_value % ((HM_NAME).capacity);                             \
    HM_BOOL_VARIABLE = 1;                                                      \
                                                                               \
    HM_LINKED_LIST_STRUCT_NAME *node = (HM_NAME).map[index];                   \
                                                                               \
    while (NULL != node) {                                                     \
      if ((HM_KEY) == node->key) {                                             \
        HM_BOOL_VARIABLE = 0;                                                  \
        break;                                                                 \
      }                                                                        \
                                                                               \
      node = (HM_LINKED_LIST_STRUCT_NAME *)node->next;                         \
    }                                                                          \
  }

#define CONTAINS_VALUE_HASH_MAP(HM_NAME, HM_LINKED_LIST_STRUCT_NAME, HM_KEY,   \
                                HM_VALUE, HM_BOOL_VARIABLE)                    \
  {                                                                            \
    size_t hash_value = (*(HM_NAME).hash_function)(HM_KEY);                    \
    int index = hash_value % ((HM_NAME).capacity);                             \
    HM_BOOL_VARIABLE = 1;                                                      \
                                                                               \
    HM_LINKED_LIST_STRUCT_NAME *current_node = (HM_NAME).map[index];           \
                                                                               \
    while (NULL != current_node) {                                             \
      if ((HM_KEY) == current_node->key &&                                     \
          (HM_VALUE) == current_node->value) {                                 \
        HM_BOOL_VARIABLE = 0;                                                  \
        break;                                                                 \
      }                                                                        \
                                                                               \
      current_node = (HM_LINKED_LIST_STRUCT_NAME *)(current_node->next);       \
    }                                                                          \
  }

#define GET_VALUE_HASH_MAP(HM_NAME, HM_LINKED_LIST_STRUCT_NAME, HM_KEY,        \
                           HM_VARIABLE)                                        \
  {                                                                            \
    size_t hash_value = (*(HM_NAME).hash_function)(HM_KEY);                    \
    int index = hash_value % ((HM_NAME).capacity);                             \
                                                                               \
    HM_LINKED_LIST_STRUCT_NAME *current_node = (HM_NAME).map[index];           \
                                                                               \
    while (NULL != current_node) {                                             \
      if ((HM_KEY) == current_node->key) {                                     \
        HM_VARIABLE = current_node->value;                                     \
        break;                                                                 \
      }                                                                        \
                                                                               \
      current_node = (HM_LINKED_LIST_STRUCT_NAME *)current_node->next;         \
    }                                                                          \
  }

#define ADD_VALUE_HASH_MAP(HM_NAME, HM_LINKED_LIST_STRUCT_NAME, HM_KEY,        \
                           HM_VALUE)                                           \
  {                                                                            \
    size_t hash_value = (*(HM_NAME).hash_function)(HM_KEY);                    \
    int index = hash_value % ((HM_NAME).capacity);                             \
    int found = 1;                                                             \
                                                                               \
    HM_LINKED_LIST_STRUCT_NAME *current_node = (HM_NAME).map[index];           \
    HM_LINKED_LIST_STRUCT_NAME *prev_node = NULL;                              \
                                                                               \
    while (NULL != current_node) {                                             \
      prev_node = current_node;                                                \
                                                                               \
      if ((HM_KEY) == current_node->key) {                                     \
        found = 0;                                                             \
        break;                                                                 \
      }                                                                        \
                                                                               \
      current_node = (HM_LINKED_LIST_STRUCT_NAME *)(current_node->next);       \
    }                                                                          \
                                                                               \
    if (1 == found) {                                                          \
      HM_LINKED_LIST_STRUCT_NAME *new_node =                                   \
          malloc(sizeof(HM_LINKED_LIST_STRUCT_NAME));                          \
      memset(new_node, 0, sizeof(HM_LINKED_LIST_STRUCT_NAME));                 \
      new_node->key = HM_KEY;                                                  \
      new_node->value = HM_VALUE;                                              \
                                                                               \
      if (NULL == (HM_NAME).map[index]) {                                      \
        (HM_NAME).map[index] = new_node;                                       \
      } else {                                                                 \
        prev_node->next = new_node;                                            \
      }                                                                        \
                                                                               \
      (HM_NAME).total_elems++;                                                 \
    }                                                                          \
  }

#define UPDATE_VALUE_HASH_MAP(HM_NAME, HM_LINKED_LIST_STRUCT_NAME, HM_KEY,     \
                              HM_VALUE)                                        \
  {                                                                            \
    size_t hash_value = (*(HM_NAME).hash_function)(HM_KEY);                    \
    int index = hash_value % ((HM_NAME).capacity);                             \
                                                                               \
    HM_LINKED_LIST_STRUCT_NAME *current_node = (HM_NAME).map[index];           \
                                                                               \
    while (NULL != current_node) {                                             \
      if ((HM_KEY) == current_node->key) {                                     \
        current_node->value = HM_VALUE;                                        \
        break;                                                                 \
      }                                                                        \
                                                                               \
      current_node = (HM_LINKED_LIST_STRUCT_NAME *)current_node->next;         \
    }                                                                          \
  }

#define ADD_OR_UPDATE_VALUE_HASH_MAP(HM_NAME, HM_LINKED_LIST_STRUCT_NAME,      \
                                     HM_KEY, HM_VALUE)                         \
  {                                                                            \
    size_t hash_value = (*(HM_NAME).hash_function)(HM_KEY);                    \
    int index = hash_value % ((HM_NAME).capacity);                             \
    int found = 1;                                                             \
                                                                               \
    HM_LINKED_LIST_STRUCT_NAME *current_node = (HM_NAME).map[index];           \
    HM_LINKED_LIST_STRUCT_NAME *prev_node = NULL;                              \
                                                                               \
    while (NULL != current_node) {                                             \
      prev_node = current_node;                                                \
                                                                               \
      if ((HM_KEY) == current_node->key) {                                     \
        current_node->value = HM_VALUE;                                        \
        found = 0;                                                             \
        break;                                                                 \
      }                                                                        \
                                                                               \
      current_node = (HM_LINKED_LIST_STRUCT_NAME *)(current_node->next);       \
    }                                                                          \
                                                                               \
    if (1 == found) {                                                          \
      HM_LINKED_LIST_STRUCT_NAME *new_node =                                   \
          malloc(sizeof(HM_LINKED_LIST_STRUCT_NAME));                          \
      memset(new_node, 0, sizeof(HM_LINKED_LIST_STRUCT_NAME));                 \
      new_node->key = HM_KEY;                                                  \
      new_node->value = HM_VALUE;                                              \
                                                                               \
      if (NULL == (HM_NAME).map[index]) {                                      \
        (HM_NAME).map[index] = new_node;                                       \
      } else {                                                                 \
        prev_node->next = new_node;                                            \
      }                                                                        \
                                                                               \
      (HM_NAME).total_elems++;                                                 \
    }                                                                          \
  }

#define REMOVE_HASH_MAP(HM_NAME, HM_LINKED_LIST_STRUCT_NAME, HM_KEY)           \
  {                                                                            \
    size_t hash_value = (*(HM_NAME).hash_function)(HM_KEY);                    \
    int index = hash_value % ((HM_NAME).capacity);                             \
                                                                               \
    HM_LINKED_LIST_STRUCT_NAME *current_node = (HM_NAME).map[index];           \
    HM_LINKED_LIST_STRUCT_NAME *prev_node = NULL;                              \
                                                                               \
    while (NULL != current_node) {                                             \
      if ((HM_KEY) == current_node->key) {                                     \
        break;                                                                 \
      }                                                                        \
                                                                               \
      prev_node = current_node;                                                \
      current_node = (HM_LINKED_LIST_STRUCT_NAME *)current_node->next;         \
    }                                                                          \
                                                                               \
    if (NULL != current_node) {                                                \
      if (NULL == prev_node) {                                                 \
        (HM_NAME).map[index] = current_node->next;                             \
      } else {                                                                 \
        prev_node->next = current_node->next;                                  \
      }                                                                        \
                                                                               \
      (HM_NAME).total_elems--;                                                 \
    }                                                                          \
  }

#define FREE_HASH_MAP(HM_NAME, HM_LINKED_LIST_STRUCT_NAME)                     \
  {                                                                            \
    int i;                                                                     \
    int capacity = (HM_NAME).capacity;                                         \
                                                                               \
    for (i = 0; i < capacity; ++i) {                                           \
      HM_LINKED_LIST_STRUCT_NAME *current_node = (HM_NAME).map[i];             \
                                                                               \
      if (NULL == current_node) {                                              \
        continue;                                                              \
      }                                                                        \
                                                                               \
      HM_LINKED_LIST_STRUCT_NAME *prev_node = NULL;                            \
                                                                               \
      while (NULL != current_node) {                                           \
        prev_node = current_node;                                              \
        current_node = (HM_LINKED_LIST_STRUCT_NAME *)current_node->next;       \
                                                                               \
        free(prev_node);                                                       \
      }                                                                        \
                                                                               \
      (HM_NAME).map[i] = NULL;                                                 \
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
  int get_value_##HM_FUNC_ID##(HM_STRUCT_NAME * hash_map_info,                 \
                               HM_KEY_DATA_TYPE key,                           \
                               HM_VALUE_DATA_TYPE * value);                    \
                                                                               \
  int contains_key_##HM_FUNC_ID##(HM_STRUCT_NAME * hash_map_info,              \
                                  HM_KEY_DATA_TYPE key);                       \
                                                                               \
  int contains_value_##HM_FUNC_ID##(HM_STRUCT_NAME * hash_map_info,            \
                                    HM_KEY_DATA_TYPE key,                      \
                                    HM_VALUE_DATA_TYPE value);                 \
                                                                               \
  void add_value_##HM_FUNC_ID##(HM_STRUCT_NAME * hash_map_info,                \
                                HM_KEY_DATA_TYPE key,                          \
                                HM_VALUE_DATA_TYPE value);                     \
                                                                               \
  void add_or_update_value_##HM_FUNC_ID##(HM_STRUCT_NAME * hash_map_info,      \
                                          HM_KEY_DATA_TYPE key,                \
                                          HM_VALUE_DATA_TYPE value);           \
                                                                               \
  void update_value_##HM_FUNC_ID##(HM_STRUCT_NAME * hash_map_info,             \
                                   HM_KEY_DATA_TYPE key,                       \
                                   HM_VALUE_DATA_TYPE new_value);              \
                                                                               \
  void remove_value_##HM_FUNC_ID##(HM_STRUCT_NAME * hash_map_info,             \
                                   HM_KEY_DATA_TYPE key);                      \
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
  int get_value_##HM_FUNC_ID##(HM_STRUCT_NAME * hash_map_info,                 \
                               HM_KEY_DATA_TYPE key,                           \
                               HM_VALUE_DATA_TYPE * value) {                   \
    int index = get_index_from_hash_##HM_FUNC_ID##(hash_map_info, key);        \
                                                                               \
    HM_LINKED_LIST_STRUCT_NAME *node = hash_map_info->map[index];              \
                                                                               \
    while (NULL != node) {                                                     \
      if (key == node->key) {                                                  \
        *value = node->value;                                                  \
        return 0;                                                              \
      }                                                                        \
    }                                                                          \
                                                                               \
    return 1;                                                                  \
  }                                                                            \
                                                                               \
  int contains_value_##HM_FUNC_ID##(HM_STRUCT_NAME * hash_map_info,            \
                                    HM_KEY_DATA_TYPE key,                      \
                                    HM_VALUE_DATA_TYPE value) {                \
    int index = get_index_from_hash_##HM_FUNC_ID##(hash_map_info, key);        \
                                                                               \
    HM_LINKED_LIST_STRUCT_NAME *node = hash_map_info->map[index];              \
                                                                               \
    while (NULL != node) {                                                     \
      if (key == node->key && value == node->value) {                          \
        return 0;                                                              \
      }                                                                        \
                                                                               \
      node = (HM_LINKED_LIST_STRUCT_NAME *)node->next;                         \
    }                                                                          \
                                                                               \
    return 1;                                                                  \
  }                                                                            \
                                                                               \
  int contains_key_##HM_FUNC_ID##(HM_STRUCT_NAME * hash_map_info,              \
                                  HM_KEY_DATA_TYPE key) {                      \
    int index = get_index_from_hash_##HM_FUNC_ID##(hash_map_info, key);        \
                                                                               \
    HM_LINKED_LIST_STRUCT_NAME *node = hash_map_info->map[index];              \
                                                                               \
    while (NULL != node) {                                                     \
      if (key == node->key) {                                                  \
        return 0;                                                              \
      }                                                                        \
                                                                               \
      node = (HM_LINKED_LIST_STRUCT_NAME *)node->next;                         \
    }                                                                          \
                                                                               \
    return 1;                                                                  \
  }                                                                            \
                                                                               \
  void add_value_##HM_FUNC_ID##(HM_STRUCT_NAME * hash_map_info,                \
                                HM_KEY_DATA_TYPE key,                          \
                                HM_VALUE_DATA_TYPE value) {                    \
    int index = get_index_from_hash_##HM_FUNC_ID##(hash_map_info, key);        \
                                                                               \
    HM_LINKED_LIST_STRUCT_NAME *current_node = hash_map_info->map[index];      \
    HM_LINKED_LIST_STRUCT_NAME *prev_node = NULL;                              \
                                                                               \
    while (NULL != current_node) {                                             \
      prev_node = current_node;                                                \
                                                                               \
      if (key == current_node->key) {                                          \
        return;                                                                \
      }                                                                        \
                                                                               \
      current_node = (HM_LINKED_LIST_STRUCT_NAME *)current_node->next;         \
    }                                                                          \
                                                                               \
    HM_LINKED_LIST_STRUCT_NAME *new_node =                                     \
        malloc(sizeof(HM_LINKED_LIST_STRUCT_NAME));                            \
    memset(new_node, 0, sizeof(HM_LINKED_LIST_STRUCT_NAME));                   \
    new_node->key = key;                                                       \
    new_node->value = value;                                                   \
                                                                               \
    if (NULL == hash_map_info->map[index]) {                                   \
      hash_map_info->map[index] = new_node;                                    \
    } else {                                                                   \
      prev_node->next = new_node;                                              \
    }                                                                          \
                                                                               \
    hash_map_info->total_elems++;                                              \
  }                                                                            \
                                                                               \
  void add_or_update_value_##HM_FUNC_ID##(HM_STRUCT_NAME * hash_map_info,      \
                                          HM_KEY_DATA_TYPE key,                \
                                          HM_VALUE_DATA_TYPE value) {          \
    int index = get_index_from_hash_##HM_FUNC_ID##(hash_map_info, key);        \
                                                                               \
    HM_LINKED_LIST_STRUCT_NAME *current_node = hash_map_info->map[index];      \
    HM_LINKED_LIST_STRUCT_NAME *prev_node = NULL;                              \
                                                                               \
    while (NULL != current_node) {                                             \
      prev_node = current_node;                                                \
                                                                               \
      if (key == current_node->key) {                                          \
        current_node->value = value;                                           \
        return;                                                                \
      }                                                                        \
                                                                               \
      current_node = (HM_LINKED_LIST_STRUCT_NAME *)current_node->next;         \
    }                                                                          \
                                                                               \
    HM_LINKED_LIST_STRUCT_NAME *new_node =                                     \
        malloc(sizeof(HM_LINKED_LIST_STRUCT_NAME));                            \
    memset(new_node, 0, sizeof(HM_LINKED_LIST_STRUCT_NAME));                   \
    new_node->key = key;                                                       \
    new_node->value = value;                                                   \
                                                                               \
    if (NULL == hash_map_info->map[index]) {                                   \
      hash_map_info->map[index] = new_node;                                    \
    } else {                                                                   \
      prev_node->next = new_node;                                              \
    }                                                                          \
                                                                               \
    hash_map_info->total_elems++;                                              \
  }                                                                            \
                                                                               \
  void update_value_##HM_FUNC_ID##(HM_STRUCT_NAME * hash_map_info,             \
                                   HM_KEY_DATA_TYPE key,                       \
                                   HM_VALUE_DATA_TYPE new_value) {             \
    int index = get_index_from_hash_##HM_FUNC_ID##(hash_map_info, key);        \
                                                                               \
    HM_LINKED_LIST_STRUCT_NAME *node = hash_map_info->map[index];              \
                                                                               \
    while (NULL != node) {                                                     \
      if (key == node->key) {                                                  \
        node->value = new_value;                                               \
        return;                                                                \
      }                                                                        \
                                                                               \
      node = (HM_LINKED_LIST_STRUCT_NAME *)node->next;                         \
    }                                                                          \
  }                                                                            \
                                                                               \
  void remove_value_##HM_FUNC_ID##(HM_STRUCT_NAME * hash_map_info,             \
                                   HM_KEY_DATA_TYPE key) {                     \
    int index = get_index_from_hash_##HM_FUNC_ID##(hash_map_info, key);        \
                                                                               \
    HM_LINKED_LIST_STRUCT_NAME *current_node = hash_map_info->map[index];      \
    HM_LINKED_LIST_STRUCT_NAME *prev_node = NULL;                              \
                                                                               \
    while (NULL != current_node) {                                             \
      if (key == current_node->key) {                                          \
        break;                                                                 \
      }                                                                        \
                                                                               \
      prev_node = current_node;                                                \
      current_node = (HM_LINKED_LIST_STRUCT_NAME *)current_node->next;         \
    }                                                                          \
                                                                               \
    if (NULL == current_node) {                                                \
      return;                                                                  \
    }                                                                          \
                                                                               \
    if (NULL == prev_node) {                                                   \
      hash_map_info->map[index] = current_node->next;                          \
    } else {                                                                   \
      prev_node->next = current_node->next;                                    \
    }                                                                          \
  }                                                                            \
                                                                               \
  void free_##HM_FUNC_ID##(HM_STRUCT_NAME * hash_map_info) {                   \
    int i;                                                                     \
    int capacity = hash_map_info->capacity;                                    \
                                                                               \
    for (i = 0; i < capacity; ++i) {                                           \
      HM_LINKED_LIST_STRUCT_NAME *current_node = hash_map_info->map[i];        \
                                                                               \
      if (NULL == current_node) {                                              \
        continue;                                                              \
      }                                                                        \
                                                                               \
      HM_LINKED_LIST_STRUCT_NAME *prev_node = NULL;                            \
                                                                               \
      while (NULL != current_node) {                                           \
        prev_node = current_node;                                              \
        current_node = (HM_LINKED_LIST_STRUCT_NAME *)current_node->next;       \
                                                                               \
        free(prev_node);                                                       \
      }                                                                        \
                                                                               \
      hash_map_info->map[i] = NULL;                                            \
    }                                                                          \
                                                                               \
    hash_map_info->total_elems = 0;                                            \
  }

#endif