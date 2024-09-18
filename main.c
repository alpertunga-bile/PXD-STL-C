#include <stdio.h>

#include "includes/linked_list.h"

CREATE_LINKED_LIST(const char *, llnode_t)

int main() {
  llnode_t *head_node = NULL;
  llnode_t *end_node = NULL;

  ADD_BACKWARD_LINKED_LIST(head_node, end_node, "asdasd", llnode_t)
  ADD_BACKWARD_LINKED_LIST(head_node, end_node, "asdzxcwewq", llnode_t)

  llnode_t *iter = head_node;

  while (NULL != iter) {
    printf("%s \n\r", iter->value);
    iter = iter->next;
  }

  FREE_LINKED_LIST(head_node, llnode_t)

  return 0;
}