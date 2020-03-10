// ERRORS - header

#ifndef ERRORS
#define ERRORS

#include <stdio.h>

#include "types.h"
#include "variables.h"

#define PRINT_MESSAGE(message) printf(RED BOLD ITALIC BLINK "\n%s\n" RESET, message)

void handle_error(Error_e error)
{
  switch (error)
  {
  case NO_SPACE:
    PRINT_MESSAGE("> Not Enough SPACE !");
    break;
  case MEMORY_FULL:
    PRINT_MESSAGE("> Memory FULL !");
    break;
  case NOT_VALID_POINTER:
    PRINT_MESSAGE("> Pointer is NOT VALID !");
    break;
  case MIN_MEMORY:
    PRINT_MESSAGE("> Small memory SIZE !");
    break;
  default:
    return;
  }
}

#endif