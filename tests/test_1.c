#include <stdio.h>
#include <string.h> // memset

// OPTIONS
#define MEMORY_SIZE 1000
#define CLEAR
#define TEST

#include "../headers/memory.h"
#include "helpers.h"

int main()
{
  for (unsigned int i = 8; i <= 24; ++i)
  {
    static char region[MEMORY_SIZE];
    memory_init(region, MEMORY_SIZE);
    char *pointer;

    long int multi = (int)(MEMORY_SIZE / i) * i;
    long int ex_fragment = multi - HEADER_SIZE;
    long int in_fragment = multi;

    printf(RED BOLD "\n- REQUIRED BLOCK SIZE: %uB - CAN FILL: %liB / %uB\n" RESET, i, multi, MEMORY_SIZE);
    while ((pointer = (char *)memory_alloc(i)))
    {
      ex_fragment = ex_fragment - i - HEADER_SIZE - FOOTER_SIZE;
      in_fragment -= i;
      display_block((void *)pointer - HEADER_SIZE, "FULL BLOCK");
      memset(pointer, -47, i);
    }

    print_memory(region);

    print_free_list();

    ex_fragment = ex_fragment + MEMORY_SIZE - multi;
    in_fragment -= ex_fragment;

    printf(RED ITALIC "EXTERNAL FRAGMENTATION: %li (%d%%) of %uB\n" RESET, ex_fragment, GET_PERCENT(ex_fragment, MEMORY_SIZE), MEMORY_SIZE);
    printf(RED ITALIC "INTERNAL FRAGMENTATION: %li (%d%%) of %uB\n" RESET, in_fragment, GET_PERCENT(in_fragment, MEMORY_SIZE), MEMORY_SIZE);

    FREEZE
  }

  return 0;
}