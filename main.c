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
 *   Header (12B)     Payload     Footer (4B)
 * ╔══════╦══════╦╦═════════════╦╦══════════╗
 * ║ size ║ next ║║   content   ║║   size   ║
 * ╚══════╩══════╩╩═════════════╩╩══════════╝
*/

#include <stdio.h>

// OPTIONS
#define CLEAR
#define TEST
#define ERROR

#include "tests/tests.h"

// TODO: MEMORY AND TIME USAGE
// TODO: REFACTOR AND HEADER
// TODO: TESTS - FRAGMENTATION - random tester
// TODO: DOCUMENTATION
// TODO: chyby
// TODO: pointer ako offset + header switcher by size

int main()
{
  /*int memory_size[] = {50, 100, 200};

  test_equal_blocks(memory_size, 3, 8, 24);*/

  // test_custom_blocks(256);

  test_basic(256);

  return 0;
}
