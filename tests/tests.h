// TESTS - header

#ifndef TESTS
#define TESTS

#include "../headers/memory.h"
#include "helpers.h"

#include <stdlib.h>
#include <time.h>

void test(c_size_t *memory_size, c_size_t memory_idx, c_size_t block_size)
{
  char region[memory_size[memory_idx]];

  memory_init(region, memory_size[memory_idx]);
  char *pointer;

  printf("\n-----------------------------------------------------------------------\n");
  printf(RED BOLD "\nREQUIRED BLOCK SIZE: %dB / %dB\n" RESET, block_size, memory_size[memory_idx]);

  int32_t ideal = (memory_size[memory_idx] / block_size) * block_size;
  int32_t success = 0;

  while ((pointer = (char *)memory_alloc(block_size)))
  {
    success += block_size;

    memset(pointer, FULL_BYTE, block_size);
    display_block(TO_FULL_HEADER(pointer), "FULL BLOCK");
  }

  print_memory(region, memory_size[memory_idx]);

  // ! print_memory_text(region, memory_size[memory_idx]);

  print_free_list();

  printf(RED ITALIC "\nSUCCESSFULY ALLOCATED: %dB (%.2lf%%) of %dB\n" RESET, success, GET_PERCENT(success, ideal), ideal);
}

void test_equal_blocks(c_size_t *memory_size, c_size_t n, c_size_t from, c_size_t to)
{
  for (int32_t memory_idx = 0; memory_idx < n; ++memory_idx)
    for (int32_t block_size = from; block_size <= to; ++block_size)
      test(memory_size, memory_idx, block_size);
}

void test_random_blocks(c_size_t *memory_size, c_size_t n, c_size_t from, c_size_t to)
{
  srand(time(0));

  for (int32_t memory_idx = 0; memory_idx < n; ++memory_idx)
  {
    char region[memory_size[memory_idx]];

    memory_init(region, memory_size[memory_idx]);
    char *pointer;

    printf("\n-----------------------------------------------------------------------\n");
    printf(RED BOLD "MEMORY SIZE: %dB\n" RESET, memory_size[memory_idx]);

    int32_t block_size = 0;
    while ((pointer = (char *)memory_alloc((block_size = GET_RANDOM(from, to)))))
    {
      memset(pointer, FULL_BYTE, block_size);
      display_block(TO_FULL_HEADER(pointer), "FULL BLOCK");
    }

    print_memory(region, memory_size[memory_idx]);

    print_free_list();

    FREEZE
  }
}

void test_custom_blocks(c_size_t memory_size)
{
  char region[memory_size];

  memory_init(region, memory_size);
  char *pointer;

  int32_t block_size = 0;
  while (scanf("%d", &block_size) == 1)
  {
    if (!(pointer = (char *)memory_alloc(block_size)))
      continue;

    printf("\n-----------------------------------------------------------------------\n");
    printf(RED BOLD "\nBLOCK SIZE: %dB, MEMORY SIZE: %dB\n" RESET, block_size, memory_size);

    memset(pointer, FULL_BYTE, block_size);

    print_memory(region, memory_size);

    print_free_list();
  }
}

void test_basic(c_size_t memory_size)
{
  char region[memory_size];

  memory_init(region, memory_size);
  printf(RED BOLD "\nMEMORY SIZE: %dB\n" RESET, memory_size);

  char *pointer1 = (char *)memory_alloc(50);
  if (pointer1)
    memset(pointer1, FULL_BYTE, 50);

  char *pointer2 = (char *)memory_alloc(80);
  if (pointer2)
    memset(pointer2, FULL_BYTE, 80);

  char *pointer3 = (char *)memory_alloc(30);
  if (pointer3)
    memset(pointer3, FULL_BYTE, 30);

  printf("%p - %s\n", pointer1, memory_check(pointer1) ? "VALID" : "INVALID");
  printf("%p - %s\n", pointer2, memory_check(pointer2) ? "VALID" : "INVALID");

  FREEZE

  memory_free(pointer2);
  memory_free(pointer1);
  memory_free(pointer3);

  printf("%p - %s\n", pointer2, memory_check(pointer2) ? "VALID" : "INVALID");
  printf("%p - %s\n", (void *)0, memory_check(0) ? "VALID" : "INVALID");
  printf("%p - %s\n", heap_g + 14, memory_check(heap_g + 14) ? "VALID" : "INVALID");
  printf("%p - %s\n", heap_g - 14, memory_check(heap_g - 14) ? "VALID" : "INVALID");

  print_memory(region, memory_size);

  print_free_list();
}

void test_valid_pointers(c_size_t size)
{
  char region[size];
  memory_init(region, size);

  print_memory_text(region, size);

  putchar('\n');
  for (int offset = -20; offset < size + 20; ++offset)
  {
    if (heap_g + offset == heap_g)
      printf(YELLOW "MEMORY START\n" RESET);

    if (heap_g + offset == heap_g + HEADER_SIZE)
      printf(YELLOW "AVAILABLE MEMORY\n" RESET);

    if (heap_g + offset == GET_END_OF_MEMORY())
      printf(YELLOW "MEMORY END\n" RESET);

    printf("%p --> ", heap_g + offset);
    printf(IS_VALID_POINTER(heap_g + offset) ? (GREEN "VALID\n" RESET) : (RED "INVALID\n" RESET));
  }
}

#endif