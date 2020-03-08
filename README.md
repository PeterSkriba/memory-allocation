# Memory Allocation - Explicit free list

This project was designed for the purpose of the assignment of the subject **Data Structures and Algorithms**.\
This program is a simulation of memory allocation similar to the functionality found int the stdlib.h library.

## Memory block design

- Total size of free block: 16B
- Total size of full block: 9B

### Free block design

| Header (12B) | Payload | Footer (4B) |
| :----------: | :-----: | :---------: |
| size \| next | content |    size     |

### Full block design

| Header (4B) | Payload | Footer (4B) |
| :---------: | :-----: | :---------: |
|    size     | content |    size     |

_Minimum 1B payload allowed._

## Compile and Run

_Windows and Linux compatible._

```console
gcc main.c -o main
```

```console
./main
```

## Interface

```C++
void memory_init(void *ptr, c_size_t size);
void *memory_alloc(c_size_t size);
int memory_check(const void *ptr);
int memory_free(void *valid_ptr);
```

## Project structure

- **[**main.c**](main.c)**: Main file with examples and tests.
- **[**headers**](headers)**: Header files containing memory allocation algorithm.
- **[**tests**](tests)**: Folder with tests and header file containing helper functions for tests.

## Options

_Situated in [**main.c**](main.c)._

```C++
#define CLEAR
#define TEST
#define ERROR
```

- **CLEAR**: Clear payload after memory_free.
- **TEST**: Memory visualization.
- **ERROR**: Error messages.

**_Comment out to turn off._**

## Usage

1. At first you need to call **memory_init** with parameters: pointer to the start of the region and size of the region.

2. Then you can use other functions like **memory_alloc** (malloc), **memory_free** (free) and **memory_check**.

## Description of functions

### memory_init

- _Time complexity_: O(1)
- _Space complexity_: O(1)

### memory_alloc

- _Time complexity_: O(n), n = linked list nodes
- _Space complexity_: O(1)

### memory_free

- _Time complexity_: O(n), n = linked list nodes
- _Space complexity_: O(1)

### memory_check

- _Time complexity_: O(n), n = memory blocks
- _Space complexity_: O(1)

By [@PeterSkriba](https://github.com/PeterSkriba), FIIT STU BA :+1:
