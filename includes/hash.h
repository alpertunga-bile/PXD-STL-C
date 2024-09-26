#ifndef INCLUDES_HASH_H
#define INCLUDES_HASH_H

#include <stdint.h>

size_t hash_signed_char(signed char value);
size_t hash_short(short value);
size_t hash_int(int value);
size_t hash_long_long(long long value);

size_t hash_unsigned_char(unsigned char value);
size_t hash_unsigned_short(unsigned short value);
size_t hash_unsigned_int(unsigned int value);
size_t hash_size_t(size_t value);

size_t hash_float(float value);
size_t hash_double(double value);
size_t hash_unsigned_char_ptr(unsigned char *str, size_t str_length);

#endif