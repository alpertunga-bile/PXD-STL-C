#ifndef INCLUDES_TEMP_DS_H
#define INCLUDES_TEMP_DS_H

/*
 * This is a test header for the data structure's functions
 * Testing with the macro defined functions
 */

#include "hash_map.h"

CREATE_HASH_MAP_INFO(hash_map_ll_info_t, hash_map_info_t, int, int, 10)

FORWARD_DECLARE_HASH_MAP_FUNCS(temp_hash_map, hash_map_ll_info_t,
                               hash_map_info_t, int, int)

#include "ring_buffer.h"

CREATE_RING_BUFFER_INFO(ring_buffer_t, int)

FORWARD_DECLARE_RING_BUFFER_FUNCS(temp_ring_buffer, ring_buffer_t, int)

#endif