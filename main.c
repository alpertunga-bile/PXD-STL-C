#include <stdio.h>

#include "hash_map.h"

CREATE_HASH_MAP_INFO(hash_map_ll_info_t, hash_map_info_t, int, int, 10)

FORWARD_DECLARE_HASH_MAP_FUNCS(hash_map_ll_info_t, hash_map_info_t, int, int)

int main() {
  hash_map_info_t hash_map;

  init_hash_map_info(&hash_map, 10, &hash_int);

  add_value_hash_map(&hash_map, 312, 312);

  int found = contains_value_hash_map(&hash_map, 312, 312);

  free_hash_map(&hash_map);

  return 0;
}

SOURCE_DECLARE_HASH_MAP_FUNCS(hash_map_ll_info_t, hash_map_info_t, int, int)