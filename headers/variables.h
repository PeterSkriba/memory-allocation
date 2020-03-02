// VARIABLES - header

#ifndef VARIABLES
#define VARIABLES

// GLOBALS
void *heap_g = 0x0;

// CONSTANTS
#define MEMORY_SIZE 128                              // custom
#define HEADER_SIZE 0xC                              // 12B
#define FOOTER_SIZE 0x4                              // 4B
#define MIN_BLOCK_SIZE 0x11                          // 17B
#define MIN_MEMORY_SIZE HEADER_SIZE + MIN_BLOCK_SIZE // 29B
#define FULL_SIGN 1                                  // full == header size + 1

// MACROS
#define GET_FOOTER_SIZE(footer) (((Footer_t *)footer)->size)
#define GET_HEADER_SIZE(header) (((Header_t *)header)->size)
#define GET_BLOCK_SIZE(payload) (HEADER_SIZE + payload + FOOTER_SIZE)
// move pointer to payload from header
#define TO_PAYLOAD(header) ((void *)header + HEADER_SIZE)
// move pointer to footer from header
#define TO_FOOTER(header) (TO_PAYLOAD(header) + GET_HEADER_SIZE(header))
// get size of payload without header and footer size
#define GET_PAYLOAD_SIZE(size) (size - HEADER_SIZE - FOOTER_SIZE)
// move pointer from payload to next and previous blocks
#define TO_PREV_NEIGHBOR(header) ((void *)header - FOOTER_SIZE - GET_FOOTER_SIZE(((void *)header - FOOTER_SIZE)) - HEADER_SIZE)
#define TO_NEXT_NEIGHBOR(header) (TO_FOOTER(header) + FOOTER_SIZE)
// check if pointer is in memory range
#define IS_VALID_POINTER(ptr) (((void *)ptr >= heap_g + HEADER_SIZE && (void *)ptr < TO_PAYLOAD(heap_g) + GET_HEADER_SIZE(heap_g)))
// check if block is not allocated
#define IS_FREE(header) (GET_HEADER_SIZE(header) == GET_FOOTER_SIZE(TO_FOOTER(header)))

// OS BASED CONSTANTS
#ifdef __unix__
#define SQUARE "■ "
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define BLUE "\033[0;34m"
#define YELLOW "\033[0;33m"
#define BOLD "\033[1m"
#define ITALIC "\033[3m"
#define RESET "\033[0m"
#else // windows
#define SQUARE "# "
#define RED
#define GREEN
#define BLUE
#define YELLOW
#define BOLD
#define ITALIC
#define RESET
#endif

#endif