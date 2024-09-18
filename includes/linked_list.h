#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include <string.h>

/*
 * creating dynamic typed linked list
 */

#define CREATE_LINKED_LIST_NODE_STRUCT(TYPE, NODE_NAME)                        \
  typedef struct {                                                             \
    TYPE value;                                                                \
    void *next;                                                                \
  }##NODE_NAME;

#define CREATE_LINKED_LIST_NODE(VARIABLE, VALUE, NODE_NAME)                    \
  VARIABLE = malloc(sizeof(NODE_NAME));                                        \
  memset(VARIABLE, 0, sizeof(NODE_NAME));                                      \
  (VARIABLE)->value = VALUE;

#define ADD_LAST_LINKED_LIST(HEAD_NODE, END_NODE, VALUE, NODE_NAME)            \
  {                                                                            \
    NODE_NAME *temp_node = NULL;                                               \
    CREATE_LINKED_LIST_NODE(temp_node, VALUE, NODE_NAME)                       \
    if (NULL == (HEAD_NODE)) {                                                 \
      (HEAD_NODE) = temp_node;                                                 \
      (END_NODE) = HEAD_NODE;                                                  \
    } else {                                                                   \
      (END_NODE)->next = (NODE_NAME *)temp_node;                               \
      (END_NODE) = temp_node;                                                  \
    }                                                                          \
  }

#define ADD_BEGIN_LINKED_LIST(HEAD_NODE, END_NODE, VALUE, NODE_NAME)           \
  {                                                                            \
    NODE_NAME *temp_node = NULL;                                               \
    CREATE_LINKED_LIST_NODE(temp_node, VALUE, NODE_NAME)                       \
    if (NULL == (HEAD_NODE)) {                                                 \
      (HEAD_NODE) = temp_node;                                                 \
      (END_NODE) = HEAD_NODE;                                                  \
    } else {                                                                   \
      temp_node->next = HEAD_NODE;                                             \
      (HEAD_NODE) = temp_node;                                                 \
    }                                                                          \
  }

#define FREE_LINKED_LIST(HEAD_NODE, NODE_NAME)                                 \
  {                                                                            \
    while (NULL != (HEAD_NODE)) {                                              \
      NODE_NAME *temp = HEAD_NODE;                                             \
      (HEAD_NODE) = (HEAD_NODE)->next;                                         \
      free(temp);                                                              \
    }                                                                          \
    (HEAD_NODE) = NULL;                                                        \
  }

#endif