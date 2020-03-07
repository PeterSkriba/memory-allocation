# Memory Allocation - Explicit free list

This project was designed for the purpose of the assignment of the subject **Data Structures and Algorithms**.\
This program is a simulation of memory allocation similar to the functionality found int the stdlib.h library.

## Memory block design

- Total size of free block: 16B
- Total size of full block: 9B
  _Minimum 1B payload allowed._

**Free block design**\
Header (12B) | Payload | Footer (4B)\
╔═══╦════╦╦═════╦╦═══╗\
║ size ║ next ║║ content ║║ size ║\
╚═══╩════╩╩═════╩╩═══╝

**Full block design**\
Header (4B) | Payload | Footer (4B)\
╔═══╦╦══════╦╦═══╗\
║ size ║║ content ║║ size ║\
╚═══╩╩══════╩╩═══╝

## Installation

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

## Options

_Situated in [**main.c**](main.c)._

```C++
#define CLEAR
#define TEST
#define ERROR
```

**_Comment out to turn off._**

## Usage

1. At first you need to call **memory_init** with parameters: pointer to the start of the region and size of the region.

2. Then you can use other functions like **memory_alloc** (malloc), **memory_free** (free) and **memory_check**.

## Description of functions

- **memory_init**
- **memory_alloc**
- **memory_free**
- **memory_check**

By [@PeterSkriba](https://github.com/PeterSkriba), FIIT STU BA :+1:
