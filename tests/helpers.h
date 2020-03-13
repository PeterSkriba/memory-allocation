// HELPERS - header

#ifndef HELPERS
#define HELPERS

#include <time.h>

#define GET_PERCENT(x, y) (((double)(x) / (y)) * 100)

#define GET_RANDOM(from, to) ((int)((rand() % ((to) - (from) + 1)) + (from)))

#define PRINT_TEST_RESULT(result) printf((result) ? (GREEN "  - OK\n" RESET) : (RED "  - FAIL\n" RESET))

#define FREEZE                                           \
  if (printf("\nPress ENTER to continue..."), getchar()) \
  {                                                      \
    /* void */                                           \
  }

void display_block(const Header_t *block, const char name[10])
{
  if (!block)
    return;

  printf(BOLD "╔════════════╦═══════════════════╦╦════════╦════════════════╦╦════════╗\n");
  printf("║ %10s ║ [%14p]: ║║ %5dB ║ %14p ║║ %5dB ║\n",
         name,
         block,
         ABS(block->size) + (IS_FREE(block) ? POINTER_SIZE : 0),
         IS_FREE(block) ? block->next : NULL,
         GET_BLOCK_SIZE(block->size));
  printf("╚════════════╩═══════════════════╩╩════════╩════════════════╩╩════════╝\n" RESET);
}

void print_memory(char region[], c_size_t size)
{
#ifdef CLEAR
  putchar('\n');
  for (int32_t byte = 0; byte < size; ++byte)
  {
    switch (region[byte])
    {
    case FULL_BYTE:
      printf(RED SQUARE RESET);
      break;
    case FREE_BYTE:
      printf(GREEN SQUARE RESET);
      break;
    case FRAGMENT_BYTE:
      printf(YELLOW SQUARE RESET);
      break;
    default:
      printf(BLUE SQUARE RESET);
    }

    if (!((byte + 1) % 32))
      putchar('\n');
  }
  putchar('\n');
#endif // CLEAR
}

void print_free_list()
{
  putchar('\n');
  for (Header_t *current = ((Header_t *)heap_g)->next; current != NULL; current = current->next)
    display_block(current, "FREE BLOCK");
}

void print_memory_text(char region[], c_size_t size)
{
  putchar('\n');
  for (int32_t byte = 0; byte < size; ++byte)
    printf(YELLOW BOLD "[%3d]: %-15d\t <- %p\n" RESET, byte, region[byte], &region[byte]);
}

#endif