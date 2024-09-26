#include <stdio.h>

#include "hash.h"

int main() {
  size_t hash_value = get_hash_number_value(2.3);
  printf("%zu", hash_value);
}