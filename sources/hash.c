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

void fill_output_hash_buffer(unsigned char *value, size_t value_size,
                             uint8_t *output_buffer) {
  blake3_hasher hasher;
  blake3_hasher_init(&hasher);

  blake3_hasher_update(&hasher, value, value_size);

  blake3_hasher_finalize(&hasher, output_buffer, BLAKE3_OUT_LEN);
}

size_t hash_signed_char(signed char value) {
  char buffer[8] = {'\0'};
  int output_length = snprintf(buffer, 8, "%d", value);

  uint8_t output[BLAKE3_OUT_LEN];
  fill_output_hash_buffer(buffer, output_length, output);

  return calc_hash_number_value(output);
}

size_t hash_short(short value) {
  char buffer[8] = {'\0'};
  int output_length = snprintf(buffer, 8, "%d", value);

  uint8_t output[BLAKE3_OUT_LEN];
  fill_output_hash_buffer(buffer, output_length, output);

  return calc_hash_number_value(output);
}

size_t hash_int(int value) {
  char buffer[16] = {'\0'};
  int output_length = snprintf(buffer, 16, "%d", value);

  uint8_t output[BLAKE3_OUT_LEN];
  fill_output_hash_buffer(buffer, output_length, output);

  return calc_hash_number_value(output);
}

size_t hash_long_long(long long value) {
  char buffer[32] = {'\0'};
  int output_length = snprintf(buffer, 32, "%lld", value);

  uint8_t output[BLAKE3_OUT_LEN];
  fill_output_hash_buffer(buffer, output_length, output);

  return calc_hash_number_value(output);
}

size_t hash_unsigned_char(unsigned char value) {
  char buffer[8] = {'\0'};
  int output_length = snprintf(buffer, 8, "%u", value);

  uint8_t output[BLAKE3_OUT_LEN];
  fill_output_hash_buffer(buffer, output_length, output);

  return calc_hash_number_value(output);
}

size_t hash_unsigned_short(unsigned short value) {
  char buffer[8] = {'\0'};
  int output_length = snprintf(buffer, 8, "%u", value);

  uint8_t output[BLAKE3_OUT_LEN];
  fill_output_hash_buffer(buffer, output_length, output);

  return calc_hash_number_value(output);
}

size_t hash_size_t(size_t value) {
  char buffer[32] = {'\0'};
  int output_length = snprintf(buffer, 32, "%zd", value);

  uint8_t output[BLAKE3_OUT_LEN];
  fill_output_hash_buffer(buffer, output_length, output);

  return calc_hash_number_value(output);
}

size_t hash_unsigned_int(unsigned int value) {
  char buffer[16] = {'\0'};
  int output_length = snprintf(buffer, 16, "%u", value);

  uint8_t output[BLAKE3_OUT_LEN];
  fill_output_hash_buffer(buffer, output_length, output);

  return calc_hash_number_value(output);
}

size_t hash_float(float value) {
  char buffer[64] = {'\0'};
  int output_length = snprintf(buffer, 64, "%f", value);

  uint8_t output[BLAKE3_OUT_LEN];
  fill_output_hash_buffer(buffer, output_length, output);

  return calc_hash_number_value(output);
}

size_t hash_double(double value) {
  char buffer[512] = {'\0'};
  int output_length = snprintf(buffer, 512, "%f", value);

  uint8_t output[BLAKE3_OUT_LEN];
  fill_output_hash_buffer(buffer, output_length, output);

  return calc_hash_number_value(output);
}

size_t hash_unsigned_char_ptr(unsigned char *str, size_t str_length) {
  uint8_t output[BLAKE3_OUT_LEN];
  fill_output_hash_buffer(str, str_length, output);

  return calc_hash_number_value(output);
}
