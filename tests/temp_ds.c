#include "temp_ds.h"

SOURCE_DECLARE_HASH_MAP_FUNCS(temp_hash_map, hash_map_ll_info_t,
                              hash_map_info_t, int, int)

SOURCE_DECLARE_RING_BUFFER_FUNCS(temp_ring_buffer, ring_buffer_t, int)