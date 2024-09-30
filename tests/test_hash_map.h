#ifndef TEST_HASH_MAP_H
#define TEST_HASH_MAP_H

#include "hash_map.h"

CREATE_HASH_MAP_INFO(hash_map_ll_info_t, hash_map_info_t, int, int, 10)

FORWARD_DECLARE_HASH_MAP_FUNCS(temp_hash_map, hash_map_ll_info_t,
                               hash_map_info_t, int, int)

#endif