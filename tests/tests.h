// TESTS - header

#ifndef TESTS
#define TESTS

#include "../headers/memory.h"
#include "helpers.h"

#include <stdlib.h>
#include <time.h>

/*
 * Testing memory_allocation - test 1 - equal blocks
*/
void test(c_size_t *memory_size, c_size_t memory_idx, c_size_t block_size)
{
  char region[memory_size[memory_idx]];
  memory_init(region, memory_size[memory_idx]);
  char *ptr;

  printf("\n-----------------------------------------------------------------------\n");
  printf(RED BOLD "\nREQUIRED BLOCK SIZE: %dB / %dB\n" RESET, block_size, memory_size[memory_idx]);

  int32_t ideal = (memory_size[memory_idx] / block_size) * block_size;
  int32_t success = 0;

  while ((ptr = (char *)memory_alloc(block_size)) != NULL)
  {
    success += block_size;

    memset(ptr, FULL_BYTE, block_size);
    display_block((void *)ptr - FULL_HEADER_SIZE, "FULL BLOCK");
  }

  print_memory(region, memory_size[memory_idx]);

  print_free_list();

  printf(RED ITALIC "\nSUCCESSFULY ALLOCATED: %dB (%.2lf%%) of %dB\n" RESET, success, GET_PERCENT(success, ideal), ideal);

  FREEZE
}

void test_equal_blocks_allocation(c_size_t *memory_size, c_size_t n, c_size_t from, c_size_t to)
{
  printf(YELLOW BOLD "#################### Test equal blocks allocation #####################\n" RESET);

  for (int32_t memory_idx = 0; memory_idx < n; ++memory_idx)
    for (int32_t block_size = from; block_size <= to; ++block_size)
      test(memory_size, memory_idx, block_size);

  printf(YELLOW BOLD "\n######################################################################\n" RESET);
}

/*
 * Testing memory_allocation - test 2, 3, 4 - random blocks
*/
void test_random_blocks_allocation(c_size_t *memory_size, c_size_t n, c_size_t from, c_size_t to)
{
  srand(time(0));

  printf(YELLOW BOLD "#################### Test random blocks allocation ####################\n" RESET);

  for (int32_t memory_idx = 0; memory_idx < n; ++memory_idx)
  {
    char region[memory_size[memory_idx]];
    memory_init(region, memory_size[memory_idx]);
    char *ptr;

    printf("\n-----------------------------------------------------------------------\n");
    printf(RED BOLD "MEMORY SIZE: %dB\n" RESET, memory_size[memory_idx]);

    int32_t block_size = 0;
    while ((ptr = (char *)memory_alloc(block_size = GET_RANDOM(from, to))) != NULL)
    {
      memset(ptr, FULL_BYTE, block_size);
      display_block((void *)ptr - FULL_HEADER_SIZE, "FULL BLOCK");
    }

    print_memory(region, memory_size[memory_idx]);

    print_free_list();

    FREEZE
  }

  printf(YELLOW BOLD "\n######################################################################\n" RESET);
}

/*
 * Interactive allocation testing
*/
void test_custom_blocks_allocation(c_size_t memory_size)
{
  printf(YELLOW BOLD "#################### Test custom blocks allocation ####################\n" RESET);

  char region[memory_size];
  memory_init(region, memory_size);
  char *ptr;

  int32_t block_size = 0;
  while (scanf("%d", &block_size) == 1)
  {
    if ((ptr = (char *)memory_alloc(block_size)) == NULL)
      continue;

    printf("\n-----------------------------------------------------------------------\n");
    printf(RED BOLD "\nBLOCK SIZE: %dB, MEMORY SIZE: %dB\n" RESET, block_size, memory_size);

    memset(ptr, FULL_BYTE, block_size);

    print_memory(region, memory_size);

    print_free_list();
  }

  printf(YELLOW BOLD "\n######################################################################\n" RESET);
}

/*
 * Testing memory_init function
*/
void test_memory_init()
{
  printf(YELLOW BOLD "########################### Test memory_init ##########################\n" RESET);

  c_size_t memory_size = 256;
  char region[memory_size];

  printf("\n* Small region *\n");
  memory_init(region, 25);
  PRINT_TEST_RESULT(!heap_g);

  printf("\n* Zero region size *\n");
  memory_init(region, 0);
  PRINT_TEST_RESULT(!heap_g);

  printf("\n* Negative region size *\n");
  memory_init(region, -256);
  PRINT_TEST_RESULT(!heap_g);

  printf("\n* Wrong pointer to region *\n");
  memory_init(NULL, memory_size);
  PRINT_TEST_RESULT(!heap_g);

  printf("\n* Correct arguments *\n");
  memory_init(region, memory_size);
  PRINT_TEST_RESULT(heap_g);

  printf("\n* Rewriting existing memory *\n");
  memory_init(region, memory_size);
  PRINT_TEST_RESULT(heap_g);

  printf("\n* Smallest possible size of region *\n");
  memory_init(region, MIN_MEMORY_SIZE);
  PRINT_TEST_RESULT(heap_g);

  printf(YELLOW BOLD "\n######################################################################\n" RESET);

  FREEZE
}

/*
 * Test memory_check function
*/
void test_memory_check()
{
  printf(YELLOW BOLD "########################## Test memory_check ##########################\n" RESET);

  printf("\n* Checking before memory_init *\n");
  PRINT_TEST_RESULT(!memory_check(0xff));

  c_size_t memory_size = 256;
  char region[memory_size];
  memory_init(region, memory_size);

  char *ptr1 = (char *)memory_alloc(16);
  char *ptr2 = (char *)memory_alloc(32);
  char *ptr3 = (char *)memory_alloc(64);

  printf("\n* Bigger block than available memory *\n");
  char *ptr4 = (char *)memory_alloc(128);
  PRINT_TEST_RESULT(!ptr4);

  printf("\n* Freeing middle block *\n");
  PRINT_TEST_RESULT(!memory_free(ptr2));

  printf("\n* Checking null pointer *\n");
  PRINT_TEST_RESULT(!memory_check(NULL));

  printf("\n* Checking invalid pointer *\n");
  PRINT_TEST_RESULT(!memory_check(heap_g));

  printf("\n* Memory before tests *\n");
  print_memory(region, memory_size);

  printf("\n* Checking all memory *\n");
  for (int32_t offset = -20; offset < memory_size + 20; ++offset)
  {
    int32_t result = memory_check(heap_g + offset);
    printf("%p", heap_g + offset);

    if (heap_g + offset == ptr1 || heap_g + offset == ptr3)
      PRINT_TEST_RESULT(result);
    else
      PRINT_TEST_RESULT(!result);
  }

  printf("\n* Checking free pointer *\n");
  PRINT_TEST_RESULT(!memory_check(ptr2));

  printf("\n* Freeing of already free block *\n");
  PRINT_TEST_RESULT(memory_free(ptr2));

  printf("\n* Checking block in full memory *\n");
  ptr2 = (char *)memory_alloc(32);
  ptr4 = (char *)memory_alloc(100);
  PRINT_TEST_RESULT(memory_check(ptr1));

  printf(YELLOW BOLD "\n######################################################################\n" RESET);

  FREEZE
}

/*
 * Testing valid pointers from memory
*/
void test_valid_pointers(c_size_t memory_size)
{
  printf(YELLOW BOLD "######################### Test valid pointers #########################\n" RESET);

  char region[memory_size];
  memory_init(region, memory_size);

  putchar('\n');
  for (int32_t offset = -20; offset < memory_size + 20; ++offset)
  {
    if (heap_g + offset == heap_g)
      printf(YELLOW "MEMORY START\n" RESET);

    if (heap_g + offset == heap_g + HEADER_SIZE)
      printf(YELLOW "AVAILABLE MEMORY\n" RESET);

    if (heap_g + offset == GET_END_OF_MEMORY())
      printf(YELLOW "MEMORY END\n" RESET);

    printf("%p ", heap_g + offset);
    printf(IS_VALID_POINTER(heap_g + offset) ? (GREEN "- VALID\n" RESET) : (RED "- INVALID\n" RESET));
  }

  printf(YELLOW BOLD "\n######################################################################\n" RESET);
}

/*
 * Testing memory_free function and memory free cases
*/
void memory_free_case(c_size_t free_1, c_size_t free_2, c_size_t free_3)
{
  c_size_t memory_size = 256;
  char region[memory_size];
  memory_init(region, memory_size);

  char *ptr1 = (char *)memory_alloc(8);
  char *ptr2 = (char *)memory_alloc(16);
  char *ptr3 = (char *)memory_alloc(32);

  if (free_1)
    memory_free(ptr1);
  if (free_2)
    memory_free(ptr2);
  if (free_3)
    memory_free(ptr3);

  printf(YELLOW BOLD "\n* Memory before test *\n" RESET);
  print_memory(region, memory_size);

  printf(YELLOW BOLD "\n* Testing blocks: %s |", free_1 ? "free" : "full");
  printf(" %s ", free_2 ? "FREE" : "FULL");
  printf("| %s *\n" RESET, free_3 ? "free" : "full");

  printf("\n* Freeing middle block *\n");
  if (!free_2)
    PRINT_TEST_RESULT(!memory_free(ptr2));
  else
    PRINT_TEST_RESULT(memory_free(ptr2));

  print_memory(region, memory_size);
  print_free_list(region, memory_size);

  printf("\n* Test result *\n");
  if ((free_1 && free_3) || free_2)
    PRINT_TEST_RESULT(!memory_check(ptr1) && !memory_check(ptr2) && !memory_check(ptr3));
  else if (free_1)
    PRINT_TEST_RESULT(!memory_check(ptr1) && !memory_check(ptr2) && memory_check(ptr3));
  else if (free_3)
    PRINT_TEST_RESULT(memory_check(ptr1) && !memory_check(ptr2) && !memory_check(ptr3));
  else
    PRINT_TEST_RESULT(memory_check(ptr1) && !memory_check(ptr2) && memory_check(ptr3));
}

void test_memory_free_cases()
{
  printf(YELLOW BOLD "####################### Test memory_free cases ########################\n" RESET);

  // full, FULL, full
  memory_free_case(0, 0, 0);
  FREEZE

  // free, FULL, full
  memory_free_case(1, 0, 0);
  FREEZE

  // full, FULL, free
  memory_free_case(0, 0, 1);
  FREEZE

  // free, FULL, free
  memory_free_case(1, 0, 1);
  FREEZE

  // free, FREE, free
  memory_free_case(1, 1, 1);

  printf(YELLOW BOLD "\n######################################################################\n" RESET);
}

/*
 * Testing memory_free function
*/
void test_memory_free()
{
  srand(time(0));

  printf(YELLOW BOLD "########################## Test memory_free ###########################\n" RESET);

  printf("\n* Memory free before memory_init *\n");
  PRINT_TEST_RESULT(memory_free(0xff));

  c_size_t memory_size = 512;
  char region[memory_size];
  memory_init(region, memory_size);

  printf("\n* Freeing null pointer *\n");
  PRINT_TEST_RESULT(memory_free(NULL));

  void *ptr[20];
  for (int32_t idx = 0; idx < 20; ++idx)
    ptr[idx] = memory_alloc(GET_RANDOM(8, 16));
  print_memory(region, memory_size);
  FREEZE

  printf("\n* Freeing all blocks *\n");
  for (int32_t idx = 0; idx < 20; ++idx)
  {
    printf("%p", ptr[idx]);
    PRINT_TEST_RESULT(!memory_free(ptr[idx]));
  }
  print_memory(region, memory_size);
  FREEZE

  for (int32_t idx = 0; idx < 20; ++idx)
    ptr[idx] = memory_alloc(GET_RANDOM(8, 16));
  print_memory(region, memory_size);
  FREEZE

  printf("\n* Freeing even blocks *\n");
  for (int32_t idx = 1; idx < 20; idx += 2)
  {
    printf("%p", ptr[idx]);
    PRINT_TEST_RESULT(!memory_free(ptr[idx]));
  }
  print_memory(region, memory_size);
  print_free_list();
  FREEZE

  memory_init(region, memory_size);

  char *ptr_free = (char *)memory_alloc(350);

  printf("\n* Freeing block multiple times *\n");
  display_block(ptr_free - FULL_HEADER_SIZE, "FULL BLOCK");
  PRINT_TEST_RESULT(!memory_free(ptr_free));
  PRINT_TEST_RESULT(memory_free(ptr_free));

  printf(YELLOW BOLD "\n######################################################################\n" RESET);
}

/*
 * Testing memory_alloc function
*/
void test_memory_alloc()
{
  printf(YELLOW BOLD "########################## Test memory_alloc ##########################\n" RESET);

  printf("\n* Allocating zero size *\n");
  PRINT_TEST_RESULT(!memory_alloc(0));

  printf("\n* Allocating before memory_init *\n");
  PRINT_TEST_RESULT(!memory_alloc(50));

  c_size_t memory_size = 1024;
  char region[memory_size];
  memory_init(region, memory_size);
  char *ptr;

  printf("\n* Allocating bigger size than memory size *\n");
  PRINT_TEST_RESULT(!memory_alloc(2 * memory_size));
  FREEZE

  printf("\n* Allocating from size 1 until memory is full *\n");
  int32_t success = 0;
  for (int32_t block_size = 1; (ptr = (char *)memory_alloc(block_size)); success += block_size++)
    display_block(ptr - FULL_HEADER_SIZE, "FULL BLOCK");
  print_memory(region, memory_size);
  printf(RED ITALIC "\nSUCCESSFULY ALLOCATED: %dB (%.2lf%%) of %dB\n" RESET, success, GET_PERCENT(success, memory_size), memory_size);
  FREEZE

  memory_init(region, memory_size);

  printf("\n* Allocating the biggest block *\n");
  for (int32_t block_size = memory_size; !ptr; --block_size)
    ptr = (char *)memory_alloc(block_size);
  print_memory(region, memory_size);
  printf("Memory size: %d\n", memory_size);
  display_block(ptr - FULL_HEADER_SIZE, "BIGGEST");

  printf("\n* Allocating block when memory full *\n");
  PRINT_TEST_RESULT(!memory_alloc(50));
  FREEZE

  memory_init(region, memory_size);

  printf("\n* Allocating block of integer type *\n");
  PRINT_TEST_RESULT(memory_alloc(sizeof(int)));

  printf("\n* Allocating array of integer type *\n");
  PRINT_TEST_RESULT(memory_alloc(8 * sizeof(int)));

  printf("\n* Allocating array of double type *\n");
  PRINT_TEST_RESULT(memory_alloc(15 * sizeof(double)));

  print_memory(region, memory_size);

  printf(YELLOW BOLD "\n######################################################################\n" RESET);
}

#endif