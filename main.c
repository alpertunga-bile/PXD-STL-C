#include <stdio.h>

#include "hash_map.h"

CREATE_HASH_MAP_INFO(hash_map_ll_info_t, hash_map_info_t, int, 10)

int main() {
  hash_map_info_t hash_map;

  INIT_HASH_MAP_INFO(hash_map, hash_map_ll_info_t, hash_map_info_t, 10)

  ADD_VALUE_HASH_MAP(hash_map, hash_map_ll_info_t, int, 1)
  ADD_VALUE_HASH_MAP(hash_map, hash_map_ll_info_t, int, 1)

  FREE_HASH_MAP(hash_map, hash_map_ll_info_t)

  return 0;
}