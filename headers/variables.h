// VARIABLES - header

#ifndef VARIABLES
#define VARIABLES

// ON / OFF
#define REWRITE_POINTER

// GLOBALS
void *heap_g = 0x0;

// CONSTANTS
#define MIN_PAYLOAD_SIZE 0x1                                        // 1B || 8B
#define HEADER_SIZE 0xC                                             // 12B
#define FOOTER_SIZE 0x4                                             // 4B
#define MIN_BLOCK_SIZE HEADER_SIZE + MIN_PAYLOAD_SIZE + FOOTER_SIZE // 17B
#define MIN_MEMORY_SIZE HEADER_SIZE + MIN_BLOCK_SIZE                // 29B
#define FULL_SIGN -1

#ifdef REWRITE_POINTER
#define FULL_HEADER_SIZE 0x4 // 4B
#define POINTER_SIZE 0x8     // 8B
#else
#define FULL_HEADER_SIZE 0xC // 12B
#define POINTER_SIZE 0x0     // 0B
#endif

// TEST CONSTANTS
#define FREE_BYTE -5
#define FULL_BYTE -6
#define FRAGMENT_BYTE -7

// MACROS
#define ABS(x) (((x) < 0) ? -(x) : (x))
// block segment sizes
#define GET_HEADER_SIZE(header) (((Header_t *)(header))->size)
#define GET_FOOTER_SIZE(footer) (((Footer_t *)(footer))->size)
#define GET_BLOCK_SIZE(payload) (HEADER_SIZE + ABS(payload) + FOOTER_SIZE)
#define GET_PAYLOAD_SIZE(size) (ABS(size) - HEADER_SIZE - FOOTER_SIZE)
// check if block is not allocated
#define IS_FREE(header) (GET_HEADER_SIZE(header) > 0)
#define IS_PREV_FOOTER_FREE(header) (GET_FOOTER_SIZE((void *)header - FOOTER_SIZE) > 0)
// move pointer to payload from header
#define TO_PAYLOAD(header) ((void *)(header) + (IS_FREE(header) ? HEADER_SIZE : FULL_HEADER_SIZE))
#define TO_FULL_PAYLOAD(header) ((void *)header + FULL_HEADER_SIZE)
// move pointer to footer from header
#define TO_FOOTER(header) (TO_PAYLOAD(header) + ABS(GET_HEADER_SIZE(header)))
#define TO_FULL_FOOTER(header) (TO_FULL_PAYLOAD(header) + ABS(GET_HEADER_SIZE(header)));
// move pointer from payload to header
#define TO_FULL_HEADER(payload) ((void *)payload - FULL_HEADER_SIZE)
// move pointer to next header from full block
#define TO_NEXT_HEADER(header) (TO_FULL_PAYLOAD(header) + ABS(GET_HEADER_SIZE(header)) + FOOTER_SIZE)
// move pointer from payload to next and previous blocks
#define TO_PREV_NEIGHBOR(header) ((void *)header - FOOTER_SIZE - ABS(GET_FOOTER_SIZE(((void *)header - FOOTER_SIZE))) - HEADER_SIZE)
#define TO_PREV_NEIGHBOR_FULL(header) ((void *)header - FOOTER_SIZE - ABS(GET_FOOTER_SIZE(((void *)header - FOOTER_SIZE))) - FULL_HEADER_SIZE)
#define TO_NEXT_NEIGHBOR(header) (TO_FOOTER(header) + FOOTER_SIZE)
// check if pointer is in memory range
#define IS_VALID_POINTER(ptr) (((void *)(ptr) >= heap_g + HEADER_SIZE && (void *)(ptr) < heap_g + HEADER_SIZE + GET_HEADER_SIZE(heap_g)))
// return end of memory pointer
#define GET_END_OF_MEMORY() (heap_g + HEADER_SIZE + GET_HEADER_SIZE(heap_g))
// making block full by changing size to negative
#define TOGGLE_FULL_FREE(size) (size * FULL_SIGN)

// OS BASED CONSTANTS
#ifdef __unix__
#define SQUARE "■ "
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define BLUE "\033[0;34m"
#define YELLOW "\033[0;33m"
#define BOLD "\033[1m"
#define ITALIC "\033[3m"
#define BLINK "\033[5m"
#define RESET "\033[0m"
#else // windows
#define SQUARE "# "
#define RED
#define GREEN
#define BLUE
#define YELLOW
#define BOLD
#define ITALIC
#define BLINK
#define RESET
#endif

#endif