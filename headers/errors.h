// ERRORS - header

#ifndef ERRORS
#define ERRORS

#include "types.h"
#include "variables.h"

void handle_error(Error_e error)
{
  switch (error)
  {
  case NO_SPACE:
    printf(RED BOLD ITALIC BLINK "\nERROR: Not Enough Space ! \n\n" RESET);
    break;
  case MEMORY_FULL:
    printf(RED BOLD ITALIC BLINK "\nERROR: Memory Full ! \n\n" RESET);
    break;
  default:
    return;
  }
}

#endif