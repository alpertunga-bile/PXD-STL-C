#include <stdio.h>

#include "hash_map.h"

CREATE_HASH_MAP_INFO(hash_map_ll_info_t, hash_map_info_t, int, int, 10)

int main() {
  hash_map_info_t hash_map;

  INIT_HASH_MAP_INFO(hash_map, hash_map_ll_info_t, hash_map_info_t, hash_int,
                     10)

  ADD_VALUE_HASH_MAP(hash_map, hash_map_ll_info_t, int, 321, 342)

  int found = 0;
  CONTAINS_VALUE_HASH_MAP(hash_map, hash_map_ll_info_t, 321, 342, found)

  FREE_HASH_MAP(hash_map, hash_map_ll_info_t)

  return 0;
}