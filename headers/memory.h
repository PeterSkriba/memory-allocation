// MEMORY - header

#ifndef MEMORY
#define MEMORY

#include <string.h> // memset

// HEADERS
#include "errors.h"
#include "types.h"
#include "variables.h"

void free_list_insert(Header_t *block)
{
  Header_t *current = heap_g;

  // find best place for free block
  while (current != NULL && current->size < block->size)
    current = current->next;

  // connect block to free list
  block->next = current->next;
  current->next = block;
}

void free_list_delete(Header_t *block)
{
  Header_t *current = heap_g;

  // find block pointing to free block
  while (current->next != NULL && current->next != block)
    current = current->next;

  // disconnect block from free list
  current->next = block->next;
  block->next = NULL;
}

/*
 * Time complexity: O(n), n = memory blocks
 * Space complexity: O(1)
*/
int memory_check(const void *ptr)
{
  if (heap_g == NULL || !ptr)
    return 0;

  if (!IS_VALID_POINTER(ptr))
  {
#ifdef ERROR
    handle_error(NOT_VALID_POINTER);
#endif // ERROR
    return 0;
  }

  Header_t *current = ((Header_t *)heap_g)->next;

  // forward seaching greater pointer in free list
  while (current != NULL && (void *)current <= ptr)
    current = current->next;

  // move to the end of the memory if memory is full
  if (current == NULL)
    current = GET_END_OF_MEMORY();

  // backward searching smaller pointer in memory
  while ((void *)current >= ptr && TO_PAYLOAD(current) != ptr && !IS_PREV_FOOTER_FREE(current))
    current = TO_PREV_NEIGHBOR_FULL(current);

  // returning true when pointer is valid and allocated
  return IS_VALID_POINTER(current) &&
         TO_PAYLOAD(current) == ptr &&
         !IS_FREE(current);
}

/*
 * Time complexity: O(n), n = linked list nodes
 * Space complexity: O(1)
*/
int memory_free(void *valid_ptr)
{
  if (heap_g == NULL || !valid_ptr || !memory_check(valid_ptr))
    return 1;

  // header and footer for new free block
  Header_t *block_header = valid_ptr - FULL_HEADER_SIZE;
  // making block size free
  block_header->size = TOGGLE_FULL_FREE(block_header->size) - POINTER_SIZE;

  Footer_t *block_footer = TO_FOOTER(block_header);
  block_footer->size = block_header->size;

  // blocks for merging
  Header_t *left_neighbor = TO_PREV_NEIGHBOR(block_header);
  Header_t *right_neighbor = TO_NEXT_NEIGHBOR(block_header);

  // checking left neighbor and merging header
  if (IS_VALID_POINTER(left_neighbor) && IS_FREE(left_neighbor))
  {
    free_list_delete(left_neighbor);

    block_header = left_neighbor;
    block_header->size += GET_BLOCK_SIZE(block_footer->size);
    block_footer->size = block_header->size; // coppying size to footer
  }

  // checking right neighbor and merging footer
  if (IS_VALID_POINTER(right_neighbor) && IS_FREE(right_neighbor))
  {
    free_list_delete(right_neighbor);

    block_header->size += GET_BLOCK_SIZE(right_neighbor->size);
    block_footer = TO_FOOTER(right_neighbor);
    block_footer->size = block_header->size; // coppying size to footer
  }

  free_list_insert(block_header);

#if defined(CLEAR) || defined(TEST)
  memset(TO_PAYLOAD(block_header), FREE_BYTE, block_header->size);
#endif // CLEAR || TEST

  return 0;
}

void *get_required_block(Header_t *header, c_size_t size)
{
  header->size += POINTER_SIZE;
  c_size_t new_block_size = header->size - size;

  // split block and insert free block to list
  if (new_block_size >= MIN_BLOCK_SIZE)
  {
    header->size = size;

    // header for free block
    Header_t *free_header = TO_NEXT_HEADER(header);
    free_header->size = GET_PAYLOAD_SIZE(new_block_size);

    // footer for free block
    Footer_t *free_footer = TO_FOOTER(free_header);
    free_footer->size = free_header->size;

    // inserting free block into right spot in linked list
    free_list_insert(free_header);
  }

  // new footer for allocated block
  Footer_t *footer = TO_FULL_FOOTER(header);
  footer->size = header->size;

#ifdef TEST
  memset(TO_FULL_PAYLOAD(header), FRAGMENT_BYTE, header->size);
#endif // TEST

  // full block flag
  header->size = footer->size = TOGGLE_FULL_FREE(header->size);

  return header;
}

void *get_free_block(c_size_t size)
{
  Header_t *current = ((Header_t *)heap_g)->next;
  Header_t *before = heap_g;

  // first and best block of required size
  while (current != NULL && current->size < size - POINTER_SIZE)
    before = current, current = current->next;

  // free block not found
  if (current == NULL)
    return NULL;

  // disconnect block from free list
  before->next = current->next;
  current->next = NULL;

  return current;
}

/*
 * Time complexity: O(n), n = linked list nodes
 * Space complexity: O(1)
*/
void *memory_alloc(c_size_t size)
{
  if (heap_g == NULL || size <= 0)
    return NULL;

  Header_t *free_block = get_free_block(size);

  // memory full
  if (free_block == NULL)
  {
#ifdef ERROR
    if (((Header_t *)heap_g)->next == NULL)
      handle_error(MEMORY_FULL);
    else
      handle_error(NO_SPACE);
#endif // ERROR
    return NULL;
  }

  // split block and insert free block to list
  Header_t *user_block = get_required_block(free_block, size);

#ifdef TEST
  memset(TO_PAYLOAD(user_block), FULL_BYTE, size);
#endif // TEST

  // returning payload of block
  return TO_PAYLOAD(user_block);
}

/*
 * Time complexity: O(1)
 * Space complexity: O(1)
*/
void memory_init(void *ptr, c_size_t size)
{
  heap_g = NULL;

  if (ptr == NULL || size <= 0)
    return;

  if (size < MIN_MEMORY_SIZE)
  {
#ifdef ERROR
    handle_error(MIN_MEMORY);
#endif // ERROR
    return;
  }

  heap_g = ptr;

  // main memory header
  Header_t *memory_header = heap_g;
  memory_header->size = size - HEADER_SIZE;

  // header of first empty block
  Header_t *block_header = memory_header + 1;
  block_header->size = GET_PAYLOAD_SIZE(memory_header->size);
  block_header->next = NULL;

  // footer of first empty block
  Footer_t *block_footer = TO_FOOTER(block_header);
  block_footer->size = block_header->size;

  // link to first empty block from main memory header
  memory_header->next = block_header;

#ifdef TEST
  memset(TO_PAYLOAD(block_header), FREE_BYTE, block_header->size);
#endif // TEST
}

#endif