// MEMORY - header

#ifndef MEMORY
#define MEMORY

#include <stdio.h>
#include <string.h> // memset

// HEADERS
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

int memory_check(const void *ptr)
{
  if (heap_g == NULL || !ptr || !IS_VALID_POINTER(ptr))
    return 0;

  Header_t *current = ((Header_t *)heap_g)->next;

  // forward seaching greater pointer in free list
  while (current != NULL && (void *)current <= ptr)
    current = current->next;

  // backward searching smaller pointer in memory
  while (current != heap_g && (void *)current >= ptr && TO_PAYLOAD(current) != ptr)
    current = TO_PREV_NEIGHBOR(current);

  // returning true when pointer is valid and allocated
  return IS_VALID_POINTER(current) &&
         TO_PAYLOAD(current) == ptr &&
         !IS_FREE(current);
}

int memory_free(void *valid_ptr)
{
  if (heap_g == NULL || !valid_ptr)
    return 1;

  // header and footer for new free block
  Header_t *block_header = valid_ptr - HEADER_SIZE;
  block_header->size -= FULL_SIGN; // making block size free
  Footer_t *block_footer = TO_FOOTER(block_header);

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

#ifdef CLEAR
  memset(TO_PAYLOAD(block_header), -1, block_header->size);
#endif // CLEAR

  return 0;
}

void *get_required_block(Header_t *block, c_size_t size)
{
  c_size_t remaining_block_size = block->size - size;

  // split block and insert free block to list
  if (remaining_block_size >= MIN_BLOCK_SIZE)
  {
    block->size = size;

    // header for free block
    Header_t *free_header = TO_NEXT_NEIGHBOR(block);
    free_header->size = GET_PAYLOAD_SIZE(remaining_block_size);

    // footer for free block
    Footer_t *free_footer = TO_FOOTER(free_header);
    free_footer->size = free_header->size;

    // inserting free block into right spot in linked list
    free_list_insert(free_header);
  }

  // new footer for allocated block
  Footer_t *footer = TO_FOOTER(block);
  footer->size = block->size;

#ifdef TEST
  memset(TO_PAYLOAD(block), -2, block->size);
#endif // TEST

  block->size += FULL_SIGN; // full block flag: 1

  return block;
}

void *get_free_block(c_size_t size)
{
  Header_t *current = ((Header_t *)heap_g)->next;
  Header_t *before = heap_g;

  // first and best block of required size
  while (current != NULL && current->size < size)
    before = current, current = current->next;

  // free block not found
  if (current == NULL)
    return NULL;

  // disconnect block from free list
  before->next = current->next;
  current->next = NULL;

  return current;
}

void *memory_alloc(c_size_t size)
{
  if (heap_g == NULL || !size)
    return NULL;

  Header_t *free_block = get_free_block(size);
  if (free_block == NULL)
    return NULL;

  // split block and insert free block to list
  Header_t *user_block = get_required_block(free_block, size);

  // returning payload of block
  return TO_PAYLOAD(user_block);
}

void memory_init(void *ptr, c_size_t size)
{
  if (ptr == NULL || !size || size < MIN_MEMORY_SIZE)
    return;

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
  memset(TO_PAYLOAD(block_header), -1, block_header->size);
#endif // TEST
}

#endif