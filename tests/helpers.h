// HELPERS - header

#ifdef MEMORY

#ifndef HELPERS
#define HELPERS

#include <time.h>

#define FREEZE                                           \
  if (printf("\nPress ENTER to continue..."), getchar()) \
  {                                                      \
    /* void */                                           \
  }

#define GET_PERCENT(x, y) (((double)(x) / (y)) * 100)

#define GET_RANDOM(from, to) ((rand() % ((to) - (from) + 1)) + (from))

void display_block(const Header_t *block, const char name[10])
{
  if (!block)
    return;

  printf(BOLD "╔════════════╦═══════════════════╦╦════════╦════════════════╦╦════════╗\n");
  printf("║ %10s ║ [%14p]: ║║ %5dB ║ %14p ║║ %5dB ║\n", name, block, ABS(block->size), block->next, GET_BLOCK_SIZE(block->size));
  printf("╚════════════╩═══════════════════╩╩════════╩════════════════╩╩════════╝\n" RESET);
}

void print_memory(char region[], unsigned int size)
{
#if defined(TEST) && defined(CLEAR)
  for (unsigned int i = 0; i < size; ++i)
  {
    switch (region[i])
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

    if (!((i + 1) % 32))
      putchar('\n');
  }
  putchar('\n');
#endif // TEST && CLEAR
}

void print_free_list()
{
  for (Header_t *current = ((Header_t *)heap_g)->next; current != NULL; current = current->next)
    display_block(current, "FREE BLOCK");
}

void print_memory_text(char region[], unsigned int size)
{
  for (unsigned int i = 0; i < size; ++i)
    printf(YELLOW BOLD "[%3d]: %-15d\t <- %p\n" RESET, i, region[i], &region[i]);
}

#endif

#endif