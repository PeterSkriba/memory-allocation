// TYPES - header

#ifndef TYPES
#define TYPES

#include <stdint.h>

// PRIMITIVE TYPES
typedef const int32_t c_size_t;

// STRUCTURES
#pragma pack(1) // forcing struct size
typedef struct Header
{
  int32_t size;        // 4B
  struct Header *next; // 8B
} Header_t;            // 12B

#pragma pack(1)
typedef struct Footer
{
  int32_t size; // 4B
} Footer_t;     // 4B

// ERROR TYPES
typedef enum Error
{
  NO_SPACE = -1,
  MEMORY_FULL = -2,
  NOT_VALID_POINTER = -3,
  MIN_MEMORY = -4
} Error_e;

#endif
