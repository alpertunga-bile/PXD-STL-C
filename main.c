#include <stdio.h>

#include "hash.h"

int main() {
  unsigned char *buffer = "zxcaszxcasdc";
  size_t hash_value = hash_unsigned_char_ptr(buffer, 16);

  int val = 12312;
  hash_value = hash_int(val);

  printf("%zu", hash_value);
}