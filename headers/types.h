// TYPES - header

#ifndef TYPES
#define TYPES

// PRIMITIVE TYPES
typedef const unsigned int c_size_t;

// STRUCTURES
#pragma pack(1) // forcing struct size
typedef struct Header
{
  unsigned int size;   // 4B
  struct Header *next; // 8B
} Header_t;            // 12B

#pragma pack(1)
typedef struct Footer
{
  unsigned int size; // 4B
} Footer_t;          // 4B

#endif
