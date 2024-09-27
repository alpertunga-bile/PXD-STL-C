#include <stdio.h>

#include "hash.h"

#include "tests/temp_ds.h"

int main() {
  hash_map_info_t hash_map;

  size_t capacity = 10;
  int found = 0;
  int key = 23;
  int value = 23;

  INIT_HASH_MAP_INFO(hash_map, hash_map_ll_info_t, hash_map_info_t, hash_int,
                     capacity)

  int i;
  for (i = 0; i < 100; ++i) {
    ADD_VALUE_HASH_MAP(hash_map, hash_map_ll_info_t, i, i)
  }

  CONTAINS_KEY_HASH_MAP(hash_map, hash_map_ll_info_t, key, found)
  CONTAINS_VALUE_HASH_MAP(hash_map, hash_map_ll_info_t, key, value, found)

  REMOVE_HASH_MAP(hash_map, hash_map_ll_info_t, key)

  CONTAINS_KEY_HASH_MAP(hash_map, hash_map_ll_info_t, key, found)

  ADD_OR_UPDATE_VALUE_HASH_MAP(hash_map, hash_map_ll_info_t, key, 31);

  int node_value = 0;
  GET_VALUE_HASH_MAP(hash_map, hash_map_ll_info_t, key, node_value)

  int total_elems = hash_map.total_elems;

  FREE_HASH_MAP(hash_map, hash_map_ll_info_t)

  return 0;
}
