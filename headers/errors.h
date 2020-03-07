// ERRORS - header

#ifndef ERRORS
#define ERRORS

#include "types.h"
#include "variables.h"

#define PRINT_MESSAGE(message) printf(RED BOLD ITALIC BLINK "\n%s\n" RESET, message)

void handle_error(Error_e error)
{
  switch (error)
  {
  case NO_SPACE:
    PRINT_MESSAGE("> Not Enough Space !");
    break;
  case MEMORY_FULL:
    PRINT_MESSAGE("> Memory Full !");
    break;
  default:
    return;
  }
}

#endif