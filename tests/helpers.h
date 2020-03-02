// HELPERS - header

#ifdef MEMORY

#ifndef HELPERS
#define HELPERS

#define FREEZE                                           \
  if (printf("\nPress ENTER to continue..."), getchar()) \
  {                                                      \
    /* void */                                           \
  }

#define GET_PERCENT(x, y) ((int)(((double)(x) / (y)) * 100))

void display_block(const Header_t *block, const char name[10])
{
  if (!block)
    return;

  printf(BOLD "╔════════════╦═══════════════════╦╦════════╦════════════════╦╦════════╗\n");
  printf("║ %10s ║ [%14p]: ║║ %5uB ║ %14p ║║ %5uB ║\n", name, block, block->size, block->next, GET_BLOCK_SIZE(block->size));
  printf("╚════════════╩═══════════════════╩╩════════╩════════════════╩╩════════╝\n" RESET);
}

void print_memory(const char memory[MEMORY_SIZE])
{
#if defined(TEST) && defined(CLEAR)
  for (unsigned int i = 0; i < MEMORY_SIZE; ++i)
  {
    switch (memory[i])
    {
    case -47:
      printf(RED SQUARE RESET);
      break;
    case -1:
      printf(GREEN SQUARE RESET);
      break;
    case -2:
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

void print_memory_text(const char region[MEMORY_SIZE])
{
  printf("---------------------------------------------------------------------------\n");
  for (int i = 0; i < MEMORY_SIZE; ++i)
    printf(YELLOW BOLD "[%3d]: %-15d\t <- %p\n" RESET, i, region[i], &region[i]);
}

#endif

#endif