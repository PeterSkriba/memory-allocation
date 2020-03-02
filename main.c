/*H***********************
 * Explicit Free List
 * Author: Peter Škríba
 * Project: LS Zadanie 1
 * Subject: DSA
*H*/

/*
 * *************** BLOCK DESING ****************
 * - Total: 16B, Min 1B payload allowed
 *
 *    Header (12B)     Payload     Footer (4B)
 * ╔════════╦══════╦╦═════════════╦╦═══════════╗
 * ║║ size ║ next ║║   content   ║║   size   ║║
 * ╚═══════╩══════╩╩═════════════╩╩═══════════╝
*/

#include <stdio.h>
#include <string.h> // memset

// OPTIONS
#define MEMORY_SIZE 50000 // MAX VALUE
#define CLEAR
#define TEST

#include "headers/memory.h"
#include "tests/helpers.h"

// TODO: MEMORY AND TIME USAGE
// TODO: REFACTOR AND HEADER
// TODO: TESTS - FRAGMENTATION - random tester
// TODO: DOCUMENTATION
// TODO: chyby + obojsmerny a min velkost 8
// TODO: pointer ako offset

int main()
{
  static char region[MEMORY_SIZE];

  memory_init(region, MEMORY_SIZE);

  char *pointer = (char *)memory_alloc(5);
  if (pointer)
    memset(pointer, 1, 5);

  char *pointer2 = (char *)memory_alloc(10);
  if (pointer2)
    memset(pointer2, 2, 10);

  /*if (pointer)
    memory_free(pointer);*/

  if (pointer2)
    memory_free(pointer2);

  /*if (pointer)
    memory_free(pointer);*/

  printf((memory_check(pointer) ? GREEN "VALID %p\n" RESET : RED "INVALID %p\n" RESET), pointer);

  //*************************************** DEBUG ********************************************************
  putchar('\n');
  for (int i = 0; i < MEMORY_SIZE; ++i)
    printf(YELLOW BOLD "[%3d]: %-15d\t <- %p\n" RESET, i, region[i], &region[i]);

  printf(RED BOLD "\nFREE BLOCKS:\n" RESET);
  for (Header_t *current = ((Header_t *)heap_g)->next; current != NULL; current = current->next)
    display_block(current, "FREE"); //!
  //*******************************************************************************************************

  return 0;
}
