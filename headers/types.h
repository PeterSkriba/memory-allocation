// TYPES - header

#ifndef TYPES
#define TYPES

// PRIMITIVE TYPES
typedef const unsigned int c_size_t;

// STRUCTURES
#pragma pack(1) // forcing struct size
typedef struct Header
{
  unsigned int size;   // 4b
  struct Header *next; // 8b
} Header_t;            // 12b

#pragma pack(1)
typedef struct Footer
{
  unsigned int size; // 4b
} Footer_t;          // 4b

#endif
