#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include <string.h>

/*
 * creating dynamic typed linked list
 * LL_NODE_NAME is not literal const char*, it is struct's defined name
 * LL is for Linked List
 *
 * @usage
 * CREATE_LINKED_LIST_NODE_STRUCT(llnode_t, int)
 *
 * llnode_t *head_node = NULL;
 * llnode_t *end_node = NULL;
 *
 * ADD_LAST_LINKED_LIST(llnode_t, head_node, end_node, 10)
 * ADD_LAST_LINKED_LIST(llnode_t, head_node, end_node, 9)
 * ADD_BEGIN_LINKED_LIST(llnode_t, head_node, end_node, 8)
 *
 * REMOVE_VALUE_LINKED_LIST(llnode_t, head_node, 9)
 *
 * FREE_LINKED_LIST(llnode_t, head_node)
 */

#define CREATE_LINKED_LIST_NODE_STRUCT(LL_NODE_NAME, LL_TYPE)                  \
  typedef struct {                                                             \
    LL_TYPE value;                                                             \
    void *next;                                                                \
  } LL_NODE_NAME;

#define CREATE_LINKED_LIST_NODE(LL_NODE_NAME, LL_VARIABLE, LL_VALUE)           \
  LL_VARIABLE = malloc(sizeof(LL_NODE_NAME));                                  \
  memset(LL_VARIABLE, 0, sizeof(LL_NODE_NAME));                                \
  (LL_VARIABLE)->value = LL_VALUE;

#define ADD_LAST_LINKED_LIST(LL_NODE_NAME, LL_HEAD_NODE, LL_END_NODE,          \
                             LL_VALUE)                                         \
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

#define ADD_BEGIN_LINKED_LIST(LL_NODE_NAME, LL_HEAD_NODE, LL_END_NODE,         \
                              LL_VALUE)                                        \
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

#define FREE_LINKED_LIST(LL_NODE_NAME, LL_HEAD_NODE)                           \
  {                                                                            \
    while (NULL != (LL_HEAD_NODE)) {                                           \
      LL_NODE_NAME *temp = LL_HEAD_NODE;                                       \
      (LL_HEAD_NODE) = (LL_HEAD_NODE)->next;                                   \
      free(temp);                                                              \
    }                                                                          \
    (LL_HEAD_NODE) = NULL;                                                     \
  }

#define REMOVE_HEAD_LINKED_LIST(LL_NODE_NAME, LL_HEAD_NODE)                    \
  {                                                                            \
    LL_NODE_NAME *holder = LL_HEAD_NODE;                                       \
    (LL_HEAD_NODE) = (LL_HEAD_NODE)->next;                                     \
    free(holder);                                                              \
  }

#define REMOVE_VALUE_LINKED_LIST(LL_NODE_NAME, LL_HEAD_NODE, LL_VALUE)         \
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