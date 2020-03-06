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
#include <string.h> // memset

// OPTIONS
#define CLEAR
#define TEST
#define ERROR

#include "headers/memory.h"
#include "tests/helpers.h"

#include "tests/tests.h"

// TODO: MEMORY AND TIME USAGE
// TODO: REFACTOR AND HEADER
// TODO: TESTS - FRAGMENTATION - random tester
// TODO: DOCUMENTATION
// TODO: chyby + obojsmerny a min velkost 8
// TODO: pointer ako offset

int main()
{
  int memory_size[] = {50, 100, 200};

  test_equal_blocks(memory_size, 3, 8, 24);

  // test_custom_blocks(256);

  return 0;
}
