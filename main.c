#include <stdio.h>

#include "hash.h"

#include "tests/temp_ds.h"

int main() {
  hash_map_info_t hash_map;

  size_t capacity = 10;
  int found = 0;
  int key = 16;
  int value = 16;

  init_temp_hash_map_info(&hash_map, capacity, &hash_int);

  int i;
  for (i = 0; i < 100; ++i) {
    add_value_temp_hash_map(&hash_map, i, i);
  }

  found = contains_key_temp_hash_map(&hash_map, key);
  found = contains_value_temp_hash_map(&hash_map, key, value);
  int total_elems = hash_map.total_elems;

  free_temp_hash_map(&hash_map);

  return 0;
}
