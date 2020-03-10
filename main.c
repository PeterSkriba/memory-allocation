/*H***********************
 * Explicit Free List
 * Author: Peter Škríba
 * Project: LS Zadanie 1
 * Subject: DSA
*H*/

/*
 * *************** BLOCK DESING ****************
 * - Total: 16B (free) / 9B (full)
 * - Minimum 1B payload allowed
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
#define TEST
#define ERROR

#include "tests/tests.h"

// TODO: TESTS - FRAGMENTATION
// TODO: DOCUMENTATION
// TODO: pointer ako offset + header switcher by size

int main()
{
  int32_t memory_size_small[] = {50, 100, 200};
  int32_t memory_size_big[] = {1000, 15000, 25000, 40000, 50000};

  // test_custom_blocks(256);

  // test_basic(256);

  test_basic_2(256);

  //? Test 1
  // test_equal_blocks(memory_size_small, 3, 8, 24);

  //? Test 2
  // test_random_blocks(memory_size_small, 3, 8, 24);

  //? Test 3
  // test_random_blocks(memory_size_big, 5, 500, 5000);

  //? Test 4
  // test_random_blocks(memory_size_big, 5, 8, 50000);

  return 0;
}
