#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
 * Generic dynamic array
 */

/*
 * @brief Create dynamic array information
 * @param DA_STRUCT_NAME Wanted structure name for the dynamic array information
 * @param DA_TYPE        Wanted value type
 * @example CREATE_DYNAMIC_ARRAY_INFO(vector_info_t, int)
 */
#define CREATE_DYNAMIC_ARRAY_INFO(DA_STRUCT_NAME, DA_TYPE)                     \
  typedef struct {                                                             \
    size_t element_size;                                                       \
    size_t total_capacity;                                                     \
    unsigned int increment_size;                                               \
    DA_TYPE *array;                                                            \
  } DA_STRUCT_NAME;

/*
 * @brief Print the informations about the dynamic array
 * @param DA_NAME        Given name for the dynamic array variable
 * @example PRINT_DYNAMIC_ARRAY_INFO(vector)
 */
#define PRINT_DYNAMIC_ARRAY_INFO(DA_NAME)                                      \
  printf("-------------------------------------------- \n\r");                 \
  printf("  DA Element Size        : %zu \n\r", (DA_NAME).element_size);       \
  printf("  DA Total Capacity Size : %zu \n\r", (DA_NAME).total_capacity);     \
  printf("  DA Increament Size     : %d bytes \n\r",                           \
         (DA_NAME).increment_size);                                            \
  printf("-------------------------------------------- \n\r");

/*
 * @brief Create dynamic array variable and initialize it
 * @param DA_NAME        Wanted name for the dynamic array variable
 * @param DA_STRUCT_NAME Given structure name for the dynamic array information
 * @param DA_TYPE        Given value type
 * @param DA_INIT_SIZE   Wanted size for the new initialized dynamic array
 * @example INIT_DYNAMIC_ARRAY(vector, vector_info_t, int, 5)
 */
#define INIT_DYNAMIC_ARRAY(DA_NAME, DA_STRUCT_NAME, DA_TYPE, DA_INIT_SIZE)     \
  DA_STRUCT_NAME DA_NAME;                                                      \
  memset(&(DA_NAME), 0, sizeof(DA_STRUCT_NAME));                               \
  (DA_NAME).array = malloc((DA_INIT_SIZE) * sizeof(DA_TYPE));                  \
  (DA_NAME).increment_size = sizeof(DA_TYPE) * 5;                              \
  (DA_NAME).total_capacity = DA_INIT_SIZE;

/*
 * @brief Add value to the dynamic array variable
 * @param DA_NAME        Given name for the dynamic array variable
 * @param DA_VALUE       Wanted value to be added to the dynamic array
 * @example ADD_DYNAMIC_ARRAY(vector, 1)
 */
#define ADD_DYNAMIC_ARRAY(DA_NAME, DA_VALUE)                                   \
  if ((DA_NAME).element_size == (DA_NAME).total_capacity) {                    \
    int type_size = sizeof((DA_NAME).array[0]);                                \
    int current_size = (DA_NAME).element_size * type_size;                     \
                                                                               \
    (DA_NAME).array =                                                          \
        realloc((DA_NAME).array, current_size + (DA_NAME).increment_size);     \
    (DA_NAME).total_capacity += (DA_NAME).increment_size / type_size;          \
  }                                                                            \
                                                                               \
  (DA_NAME).array[(DA_NAME).element_size++] = DA_VALUE;

/*
 * @brief Shrink the dynamic array to the element size
 * @param DA_NAME        Given name for the dynamic array variable
 * @example SHRINK_DYNAMIC_ARRAY(vector)
 */
#define SHRINK_DYNAMIC_ARRAY(DA_NAME)                                          \
  if ((DA_NAME).element_size != (DA_NAME).total_capacity) {                    \
    int type_size = sizeof((DA_NAME).array[0]);                                \
    int current_size = (DA_NAME).element_size * type_size;                     \
                                                                               \
    (DA_NAME).array = realloc((DA_NAME).array, current_size);                  \
    (DA_NAME).total_capacity = (DA_NAME).element_size;                         \
  }

/*
 * @brief Free the reserved memory of the dynamic array
 * @param DA_NAME        Given name for the dynamic array variable
 * @example FREE_DYNAMIC_ARRAY(vector)
 */
#define FREE_DYNAMIC_ARRAY(DA_NAME) free((DA_NAME).array);

#endif