#include "test_hash_map.h"

SOURCE_DECLARE_HASH_MAP_FUNCS(temp_hash_map, hash_map_ll_info_t,
                              hash_map_info_t, int, int)

#include "hash.h"

int test_hash_map_w_funcs() {
  hash_map_info_t hash_map;
  int key = 16;
  int value = 16;
  int new_value = 32;
  /* it has to be same with the CREATE_ macro HM_SIZE variable */
  int capacity = 128;

  init_temp_hash_map_info(&hash_map, capacity, &hash_int);

  int i = 0;
  for (i = 0; i < 100; ++i) {
    add_value_temp_hash_map(&hash_map, i, i);
  }

  int ret_val = contains_key_temp_hash_map(&hash_map, key);

  if (1 == ret_val) {
    printf("Key map didn't contain %d key value\n\r", key);
    return ret_val;
  }

  ret_val = get_value_temp_hash_map(&hash_map, key, &value);

  if (1 == ret_val) {
    printf("Can't get the value of the key %d from the hash map\n\r", key);
    return ret_val;
  }

  printf("Key : %4d | Value: %4d\n\r", key, value);

  update_value_temp_hash_map(&hash_map, key, new_value);

  ret_val = get_value_temp_hash_map(&hash_map, key, &value);

  if (1 == ret_val) {
    printf("Can't get the value of the key %d from the hash map\n\r", key);
    return ret_val;
  }

  printf("Key : %4d | Value: %4d\n\r", key, value);

  remove_value_temp_hash_map(&hash_map, key);

  ret_val = contains_key_temp_hash_map(&hash_map, key);

  if (0 == ret_val) {
    printf("After the remove of key %d, hash map contains the key\n\r", key);
    return 1;
  }

  free_temp_hash_map(&hash_map);
}