#include <stdio.h>

#include "hash.h"

#include "tests/temp_ds.h"

int main() {
  hash_map_info_t hash_map;

  size_t capacity = 10;
  int key = 321;
  int value = 321;

  init_temp_hash_map_info(&hash_map, capacity, &hash_int);

  add_value_temp_hash_map(&hash_map, key, value);
  add_value_temp_hash_map(&hash_map, key, value);

  int found = contains_value_temp_hash_map(&hash_map, key, value);
  int total_elems = hash_map.total_elems;

  free_temp_hash_map(&hash_map);

  return 0;
}
