#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include <string.h>

/*
 * creating dynamic typed linked list
 * LL_NODE_NAME is not literal const char*, it is struct's defined name
 * LL is for Linked List
 */

#define CREATE_LINKED_LIST_NODE_STRUCT(LL_TYPE, LL_NODE_NAME)                  \
  typedef struct {                                                             \
    LL_TYPE value;                                                             \
    void *next;                                                                \
  }##LL_NODE_NAME;                                                             \
                                                                               \
  inline void create_node(LL_NODE_NAME *variable, LL_TYPE value) {             \
    variable = malloc(sizeof(LL_NODE_NAME));                                   \
    memset(variable, 0, sizeof(LL_NODE_NAME));                                 \
    variable->value = value;                                                   \
  }

#define CREATE_LINKED_LIST_NODE(LL_VARIABLE, LL_VALUE, LL_NODE_NAME)           \
  LL_VARIABLE = malloc(sizeof(LL_NODE_NAME));                                  \
  memset(LL_VARIABLE, 0, sizeof(LL_NODE_NAME));                                \
  (LL_VARIABLE)->value = LL_VALUE;

#define ADD_LAST_LINKED_LIST(LL_HEAD_NODE, LL_END_NODE, LL_VALUE,              \
                             LL_NODE_NAME)                                     \
  {                                                                            \
    LL_NODE_NAME *temp_node = NULL;                                            \
    CREATE_LINKED_LIST_NODE(temp_node, LL_VALUE, LL_NODE_NAME)                 \
    if (NULL == (LL_HEAD_NODE)) {                                              \
      (LL_HEAD_NODE) = temp_node;                                              \
      (LL_END_NODE) = LL_HEAD_NODE;                                            \
    } else {                                                                   \
      (LL_END_NODE)->next = (LL_NODE_NAME *)temp_node;                         \
      (LL_END_NODE) = temp_node;                                               \
    }                                                                          \
  }

#define ADD_BEGIN_LINKED_LIST(LL_HEAD_NODE, LL_END_NODE, LL_VALUE,             \
                              LL_NODE_NAME)                                    \
  {                                                                            \
    LL_NODE_NAME *temp_node = NULL;                                            \
    CREATE_LINKED_LIST_NODE(temp_node, LL_VALUE, LL_NODE_NAME)                 \
    if (NULL == (LL_HEAD_NODE)) {                                              \
      (LL_HEAD_NODE) = temp_node;                                              \
      (LL_END_NODE) = LL_HEAD_NODE;                                            \
    } else {                                                                   \
      temp_node->next = LL_HEAD_NODE;                                          \
      (LL_HEAD_NODE) = temp_node;                                              \
    }                                                                          \
  }

#define FREE_LINKED_LIST(LL_HEAD_NODE, LL_NODE_NAME)                           \
  {                                                                            \
    while (NULL != (LL_HEAD_NODE)) {                                           \
      LL_NODE_NAME *temp = LL_HEAD_NODE;                                       \
      (LL_HEAD_NODE) = (LL_HEAD_NODE)->next;                                   \
      free(temp);                                                              \
    }                                                                          \
    (LL_HEAD_NODE) = NULL;                                                     \
  }

#define REMOVE_HEAD_LINKED_LIST(LL_HEAD_NODE, LL_NODE_NAME)                    \
  {                                                                            \
    LL_NODE_NAME *holder = LL_HEAD_NODE;                                       \
    (LL_HEAD_NODE) = (LL_HEAD_NODE)->next;                                     \
    free(holder);                                                              \
  }

#define REMOVE_VALUE_LINKED_LIST(LL_HEAD_NODE, LL_VALUE, LL_NODE_NAME)         \
  {                                                                            \
    if ((LL_VALUE) == ((LL_HEAD_NODE)->value)) {                               \
      REMOVE_HEAD_LINKED_LIST(LL_HEAD_NODE, LL_NODE_NAME)                      \
    } else {                                                                   \
      LL_NODE_NAME *iter = (LL_HEAD_NODE)->next;                               \
      LL_NODE_NAME *iter_prev = (LL_HEAD_NODE);                                \
      while (NULL != iter) {                                                   \
        if (LL_VALUE == iter->value) {                                         \
          iter_prev->next = iter->next;                                        \
          free(iter);                                                          \
          break;                                                               \
        }                                                                      \
        iter_prev = iter;                                                      \
        iter = iter->next;                                                     \
      }                                                                        \
    }                                                                          \
  }

#endif