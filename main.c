#include <stdio.h>

#include "includes/linked_list.h"

CREATE_LINKED_LIST_NODE_STRUCT(int, llnode_t)

int main() {
  llnode_t *head_node = NULL;
  llnode_t *end_node = NULL;

  ADD_LAST_LINKED_LIST(head_node, end_node, 10, llnode_t)
  ADD_LAST_LINKED_LIST(head_node, end_node, 9, llnode_t)
  ADD_BEGIN_LINKED_LIST(head_node, end_node, 8, llnode_t)

  REMOVE_VALUE_LINKED_LIST(head_node, 8, llnode_t)

  llnode_t *iter = head_node;

  while (NULL != iter) {
    printf("%d \n\r", iter->value);
    iter = iter->next;
  }

  FREE_LINKED_LIST(head_node, llnode_t)

  return 0;
}