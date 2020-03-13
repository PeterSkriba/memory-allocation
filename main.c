/*H***********************
 * Explicit Free List
 * Author: Peter Škríba
 * Project: LS Zadanie 1
 * Subject: DSA
*H*/

/*
 * ************** BLOCK DESING **************
 *
 *               * FREE BLOCK *
 *   Header (12B)     Payload     Footer (4B)
 * ╔══════╦══════╦╦═════════════╦╦══════════╗
 * ║ size ║ next ║║   content   ║║   size   ║
 * ╚══════╩══════╩╩═════════════╩╩══════════╝
 *
 *              * FULL BLOCK *
 *  Header (4B)    Payload     Footer (4B)
 * ╔══════════╦╦═════════════╦╦══════════╗
 * ║   size   ║║   content   ║║   size   ║
 * ╚══════════╩╩═════════════╩╩══════════╝
*/

#include <stdio.h>

// OPTIONS
#define CLEAR
#define ERROR

#include "tests/tests.h"

// TODO: ONE SOURCE
// TODO: DOCUMENTATION

int main()
{
  /*
   * For better enjoyment, run the program on the Linux operating system,
   * leave all options on and do not change the content of the allocated pointer.
  */

  int32_t memory_size_small[] = {50, 100, 200};
  int32_t memory_size_big[] = {1000, 15000, 25000, 40000, 50000};

  //? Other tests
  // test_custom_blocks_allocation(256);

  //? Test 1
  // test_equal_blocks_allocation(memory_size_small, 3, 8, 24);
  // test_equal_blocks_allocation(memory_size_big, 5, 8, 24);

  //? Test 2
  // test_random_blocks_allocation(memory_size_small, 3, 8, 24);

  //? Test 3
  // test_random_blocks_allocation(memory_size_big, 5, 500, 5000);

  //? Test 4
  // test_random_blocks_allocation(memory_size_big, 5, 8, 50000);

  //? Custom tests
  // test_memory_init();
  // test_valid_pointers(128);
  // test_memory_alloc();
  // test_memory_check();
  // test_memory_free();
  // test_memory_free_cases();

  return 0;
}
