// TESTS - header

#include "../headers/memory.h"
#include "helpers.h"

void test(c_size_t *memory_size, const unsigned int memory_idx, const unsigned int block_size)
{
  char region[memory_size[memory_idx]];

  memory_init(region, memory_size[memory_idx]);
  char *pointer;

  int can_allocate = (memory_size[memory_idx] / block_size) * block_size; // TODO: check
  int fragmentation = memory_size[memory_idx];
  int success = 0;

  printf(RED BOLD "\nREQUIRED BLOCK SIZE: %uB / %uB\n" RESET, block_size, memory_size[memory_idx]);
  while ((pointer = (char *)memory_alloc(block_size)))
  {
    fragmentation -= block_size;
    success += block_size;

    display_block((void *)pointer - HEADER_SIZE, "FULL BLOCK");

    memset(pointer, FULL_BYTE, block_size);
  }

  putchar('\n');
  print_memory(region, memory_size[memory_idx]);

  putchar('\n');
  print_free_list();

  putchar('\n');
  printf(YELLOW ITALIC "FRAGMENTATION: " RESET);
  printf(BLUE ITALIC "%dB (%.2lf%%) of %dB\n" RESET, fragmentation, GET_PERCENT(fragmentation, memory_size[memory_idx]), memory_size[memory_idx]);
  printf(RED ITALIC "SUCCESSFULY ALLOCATED: %dB (%.2lf%%) of %dB\n" RESET, success, GET_PERCENT(success, can_allocate), can_allocate);

  FREEZE
}

void test_equal_blocks(c_size_t *memory_size, const unsigned int n, const unsigned int from, const unsigned int to)
{
  for (unsigned int memory_idx = 0; memory_idx < n; ++memory_idx)
    for (unsigned int block_size = from; block_size <= to; ++block_size)
      test(memory_size, memory_idx, block_size);
}

void test_custom_blocks(c_size_t memory_size)
{
  char region[memory_size];

  memory_init(region, memory_size);
  char *pointer;

  unsigned int block_size = 0;
  while ((scanf("%u", &block_size) == 1))
  {
    if (!(pointer = (char *)memory_alloc(block_size)))
      continue;

    printf(RED BOLD "\nBLOCK SIZE: %uB, MEMORY SIZE: %uB\n" RESET, block_size, memory_size);
    memset(pointer, FULL_BYTE, block_size);

    putchar('\n');
    print_memory(region, memory_size);

    putchar('\n');
    print_free_list();
  }
}

// TODO: test random blocks