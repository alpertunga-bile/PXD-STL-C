#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include <string.h>

/*
 * creating generic linked list
 */

#define CREATE_LINKED_LIST_NODE_STRUCT(LL_STRUCT_NAME, LL_NODE_NAME, LL_TYPE)  \
  typedef struct {                                                             \
    LL_TYPE value;                                                             \
    void *next;                                                                \
  } LL_NODE_NAME;                                                              \
                                                                               \
  typedef struct {                                                             \
    LL_NODE_NAME *head;                                                        \
    LL_NODE_NAME *end;                                                         \
    size_t total_elems;                                                        \
    int (*eq_func)(LL_TYPE, LL_TYPE);                                          \
  } LL_STRUCT_NAME;

#define INIT_LINKED_LIST_STRUCT(LL_NAME, LL_STRUCT_NAME, LL_EQ_FUNC)           \
  memset(&LL_NAME, 0, sizeof(LL_STRUCT_NAME));                                 \
  (LL_NAME).eq_func = LL_EQ_FUNC;

#define ADD_LAST_LINKED_LIST(LL_NAME, LL_NODE_NAME, LL_VALUE)                  \
  {                                                                            \
    LL_NODE_NAME *temp_node = NULL;                                            \
                                                                               \
    temp_node = malloc(sizeof(LL_NODE_NAME));                                  \
    memset(temp_node, 0, sizeof(LL_NODE_NAME));                                \
    temp_node->value = LL_VALUE;                                               \
                                                                               \
    if (NULL == (LL_NAME).head) {                                              \
      (LL_NAME).head = temp_node;                                              \
      (LL_NAME).end = (LL_NAME).head;                                          \
    } else {                                                                   \
      (LL_NAME).end->next = (LL_NODE_NAME *)temp_node;                         \
      (LL_NAME).end = temp_node;                                               \
    }                                                                          \
                                                                               \
    (LL_NAME).total_elems++;                                                   \
  }

#define ADD_BEGIN_LINKED_LIST(LL_NAME, LL_NODE_NAME, LL_VALUE)                 \
  {                                                                            \
    LL_NODE_NAME *temp_node = NULL;                                            \
                                                                               \
    temp_node = malloc(sizeof(LL_NODE_NAME));                                  \
    memset(temp_node, 0, sizeof(LL_NODE_NAME));                                \
    temp_node->value = LL_VALUE;                                               \
                                                                               \
    if (NULL == (LL_NAME).head) {                                              \
      (LL_NAME).head = temp_node;                                              \
      (LL_NAME).end = (LL_NAME).head;                                          \
    } else {                                                                   \
      temp_node->next = (LL_NAME).head;                                        \
      (LL_NAME).head = temp_node;                                              \
    }                                                                          \
                                                                               \
    (LL_NAME).total_elems++;                                                   \
  }

#define FREE_LINKED_LIST(LL_NAME, LL_NODE_NAME)                                \
  {                                                                            \
    LL_NODE_NAME *temp_node = (LL_NAME).head;                                  \
                                                                               \
    while (NULL != temp_node) {                                                \
      LL_NODE_NAME *prev_node = temp_node;                                     \
      temp_node = temp_node->next;                                             \
      free(prev_node);                                                         \
    }                                                                          \
                                                                               \
    (LL_NAME).head = NULL;                                                     \
    (LL_NAME).end = NULL;                                                      \
    (LL_NAME).total_elems = 0;                                                 \
  }

#define REMOVE_HEAD_LINKED_LIST(LL_NAME, LL_NODE_NAME)                         \
  {                                                                            \
    if (NULL != (LL_NAME).head) {                                              \
      LL_NODE_NAME *holder = (LL_NAME).head;                                   \
      (LL_NAME).head = (LL_NAME).head->next;                                   \
      free(holder);                                                            \
      (LL_NAME).total_elems--;                                                 \
    }                                                                          \
  }

#define REMOVE_VALUE_LINKED_LIST(LL_NAME, LL_NODE_NAME, LL_VALUE)              \
  {                                                                            \
    int head_eq = 1;                                                           \
    if (NULL != (LL_NAME).eq_func) {                                           \
      head_eq = (LL_NAME).eq_func((LL_VALUE), ((LL_NAME).head->value));        \
    } else {                                                                   \
      head_eq = (LL_VALUE) == ((LL_NAME).head->value);                         \
    }                                                                          \
                                                                               \
    if (0 == head_eq) {                                                        \
      REMOVE_HEAD_LINKED_LIST((LL_NAME), LL_NODE_NAME)                         \
    } else {                                                                   \
      LL_NODE_NAME *iter = (LL_NAME).head->next;                               \
      LL_NODE_NAME *iter_prev = (LL_NAME).head;                                \
                                                                               \
      while (NULL != iter) {                                                   \
        int iter_eq = 1;                                                       \
                                                                               \
        if (NULL != (LL_NAME).eq_func) {                                       \
          iter_eq = (LL_NAME).eq_func((LL_VALUE), ((LL_NAME).head->value));    \
        } else {                                                               \
          iter_eq = (LL_VALUE) == ((LL_NAME).head->value);                     \
        }                                                                      \
                                                                               \
        if (0 == iter_eq) {                                                    \
          iter_prev->next = iter->next;                                        \
          free(iter);                                                          \
          break;                                                               \
        }                                                                      \
        iter_prev = iter;                                                      \
        iter = iter->next;                                                     \
      }                                                                        \
                                                                               \
      (LL_NAME).total_elems--;                                                 \
    }                                                                          \
  }

#define FORWARD_DECLARE_LINKED_LIST_FUNCS(LL_FUNC_ID, LL_STRUCT_NAME, LL_TYPE) \
  void init_##LL_FUNC_ID##_info(LL_STRUCT_NAME *ll_info,                       \
                                int (*eq_func)(LL_TYPE, LL_TYPE));             \
                                                                               \
  void add_last_##LL_FUNC_ID##(LL_STRUCT_NAME * ll_info, LL_TYPE * value);     \
                                                                               \
  void add_begin_##LL_FUNC_ID##(LL_STRUCT_NAME * ll_info, LL_TYPE * value);    \
                                                                               \
  void remove_head_##LL_FUNC_ID##(LL_STRUCT_NAME * ll_info);                   \
                                                                               \
  void remove_value_##LL_FUNC_ID##(LL_STRUCT_NAME * ll_info, LL_TYPE * value); \
                                                                               \
  void free_##LL_FUNC_ID##(LL_STRUCT_NAME * ll_info);

#define SOURCE_DECLARE_LINKED_LIST_FUNCS(LL_FUNC_ID, LL_STRUCT_NAME,           \
                                         LL_NODE_NAME, LL_TYPE)                \
  void init_##LL_FUNC_ID##_info(LL_STRUCT_NAME *ll_info,                       \
                                int (*eq_func)(LL_TYPE, LL_TYPE)) {            \
    memset(ll_info, 0, sizeof(LL_STRUCT_NAME));                                \
    ll_info->eq_func = eq_func;                                                \
  }                                                                            \
                                                                               \
  void add_last_##LL_FUNC_ID##(LL_STRUCT_NAME * ll_info, LL_TYPE * value) {    \
    LL_NODE_NAME *temp_node = NULL;                                            \
                                                                               \
    temp_node = malloc(sizeof(LL_STRUCT_NAME));                                \
    memset(temp_node, 0, sizeof(LL_STRUCT_NAME));                              \
    temp_node->value = *value;                                                 \
                                                                               \
    if (NULL == ll_info->head) {                                               \
      ll_info->head = temp_node;                                               \
      ll_info->end = ll_info->head;                                            \
    } else {                                                                   \
      ll_info->end->next = (LL_NODE_NAME *)temp_node;                          \
      ll_info->end = temp_node;                                                \
    }                                                                          \
                                                                               \
    ll_info->total_elems++;                                                    \
  }                                                                            \
                                                                               \
  void add_begin_##LL_FUNC_ID##(LL_STRUCT_NAME * ll_info, LL_TYPE * value) {   \
    LL_NODE_NAME *temp_node = NULL;                                            \
                                                                               \
    temp_node = malloc(sizeof(LL_STRUCT_NAME));                                \
    memset(temp_node, 0, sizeof(LL_STRUCT_NAME));                              \
    temp_node->value = *value;                                                 \
                                                                               \
    if (NULL == ll_info->head) {                                               \
      ll_info->head = temp_node;                                               \
      ll_info->end = ll_info->head;                                            \
    } else {                                                                   \
      temp_node->next = ll_info->head;                                         \
      ll_info->head = temp_node;                                               \
    }                                                                          \
                                                                               \
    ll_info->total_elems++;                                                    \
  }                                                                            \
                                                                               \
  void remove_head_##LL_FUNC_ID##(LL_STRUCT_NAME * ll_info) {                  \
    if (NULL == ll_info->head) {                                               \
      return;                                                                  \
    }                                                                          \
                                                                               \
    LL_NODE_NAME *holder = ll_info->head;                                      \
    ll_info->head = ll_info->head->next;                                       \
    free(holder);                                                              \
    holder = NULL;                                                             \
                                                                               \
    ll_info->total_elems--;                                                    \
  }                                                                            \
                                                                               \
  void remove_value_##LL_FUNC_ID##(LL_STRUCT_NAME * ll_info,                   \
                                   LL_TYPE * value) {                          \
    if (NULL == ll_info->head) {                                               \
      return;                                                                  \
    }                                                                          \
                                                                               \
    int head_eq = 1;                                                           \
    if (NULL != ll_info->eq_func) {                                            \
      head_eq = ll_info->eq_func(*value, ll_info->head->value);                \
    } else {                                                                   \
      head_eq = (*value) == ll_info->head->value;                              \
    }                                                                          \
                                                                               \
    if (head_eq) {                                                             \
      remove_head_##LL_FUNC_ID##(ll_info);                                     \
      return;                                                                  \
    }                                                                          \
                                                                               \
    LL_NODE_NAME *iter = ll_info->head->next;                                  \
    LL_NODE_NAME *prev_iter = ll_info->head;                                   \
                                                                               \
    while (NULL != iter) {                                                     \
      int iter_eq = 1;                                                         \
                                                                               \
      if (NULL != ll_info->eq_func) {                                          \
        iter_eq = ll_info->eq_func(*value, iter->value);                       \
      } else {                                                                 \
        iter_eq = (*value) == iter->value;                                     \
      }                                                                        \
                                                                               \
      if (iter_eq) {                                                           \
        prev_iter->next = iter->next;                                          \
        free(iter);                                                            \
        iter = NULL;                                                           \
        break;                                                                 \
      }                                                                        \
                                                                               \
      prev_iter = iter;                                                        \
      iter = iter->next;                                                       \
    }                                                                          \
                                                                               \
    ll_info->total_elems--;                                                    \
  }                                                                            \
                                                                               \
  void free_##LL_FUNC_ID##(LL_STRUCT_NAME * ll_info) {                         \
    LL_NODE_NAME *temp_node = ll_info->head;                                   \
                                                                               \
    while (NULL != temp_node) {                                                \
      LL_NODE_NAME *prev_node = temp_node;                                     \
      temp_node = temp_node->next;                                             \
                                                                               \
      free(prev_node);                                                         \
    }                                                                          \
                                                                               \
    ll_info->head = NULL;                                                      \
    ll_info->end = NULL;                                                       \
    ll_info->total_elems = 0;                                                  \
  }

#endif