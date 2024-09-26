#include "hash.h"

#include "blake3/c/blake3.h"

#include <math.h>
#include <stdio.h>

size_t calc_hash_number_value(uint8_t *values) {
  size_t hasher_number_value = 0;

  for (int i = 0; i < BLAKE3_OUT_LEN; ++i) {
    hasher_number_value += (size_t)(values[i]) * (size_t)(pow(2, i));
  }

  return hasher_number_value;
}

size_t get_hash_number_value(float value) {
  blake3_hasher hasher;
  blake3_hasher_init(&hasher);

  unsigned char buffer[64];

  int output_length = snprintf(buffer, 64, "%f", value);

  blake3_hasher_update(&hasher, buffer, output_length);

  uint8_t output[BLAKE3_OUT_LEN];
  blake3_hasher_finalize(&hasher, output, BLAKE3_OUT_LEN);

  return calc_hash_number_value(output);
}