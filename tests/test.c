//* OK

#include "../headers/memory.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
  static char region[16384];

  memory_init(region, 16384);

  int size;
  int lsize;
  int curr;
  void *ptr[10];
  int i;

  /*
	 * try mallocing four pieces, each 1/4 of total size
	 */
  size = 16384 / 4;

  ptr[0] = memory_alloc(size);
  if (ptr[0] == NULL)
  {
    printf("malloc of ptr[0] failed for size %d\n",
           size);
    exit(1);
  }

  ptr[1] = memory_alloc(size);
  if (ptr[1] == NULL)
  {
    printf("malloc of ptr[1] failed for size %d\n",
           size);
    exit(1);
  }

  ptr[2] = memory_alloc(size);
  if (ptr[2] == NULL)
  {
    printf("malloc of ptr[2] failed for size %d\n",
           size);
    exit(1);
  }

  /*
	 * this one should fail due to rounding
	 */
  ptr[3] = memory_alloc(size);
  if (ptr[3] == NULL)
  {
    printf("malloc of ptr[3] fails correctly for size %d\n",
           size);
  }

  /*
	 * free the first block
	 */
  memory_free(ptr[0]);

  /*
	 * free the third block
	 */
  memory_free(ptr[2]);

  /*
	 * now free secoond block
	 */
  memory_free(ptr[1]);

  /*
	 * re-malloc first pointer
\	 */
  ptr[0] = memory_alloc(size);
  if (ptr[0] == NULL)
  {
    printf("re-malloc of ptr[0] failed for size %d\n",
           size);
    exit(1);
  }

  /*
	 * try splitting the second block
	 */
  ptr[1] = memory_alloc(size / 2);
  if (ptr[1] == NULL)
  {
    printf("split second block ptr[1] failed for size %d\n",
           size / 2);
    exit(1);
  }

  /*
	 * free first block and split of second
	 */
  memory_free(ptr[0]);
  memory_free(ptr[1]);

  /*
	 * try mallocing a little less to make sure no split occurs
	 * first block from previous print should not be split
	 */
  ptr[0] = memory_alloc(size - 1);
  if (ptr[0] == NULL)
  {
    printf("slightly smaller malloc of ptr[0] failed for size %d\n",
           size);
    exit(1);
  }

  /*
	 * free it and make sure it comes back as the correct size
	 */
  memory_free(ptr[0]);

  /*
	 * okay -- malloc up all but the last available blocks
	 */
  ptr[0] = memory_alloc(size);
  if (ptr[0] == NULL)
  {
    printf("run-up malloc of ptr[0] failed for size %d\n",
           size);
    exit(1);
  }
  ptr[1] = memory_alloc(size / 2);
  if (ptr[1] == NULL)
  {
    printf("run-up malloc of ptr[1] failed for size %d\n",
           size / 2);
    exit(1);
  }
  ptr[2] = memory_alloc(size / 2);
  if (ptr[2] == NULL)
  {
    printf("run-up malloc of ptr[2] failed for size %d\n",
           size / 2);
    exit(1);
  }
  ptr[3] = memory_alloc(size / 2);
  if (ptr[3] == NULL)
  {
    printf("run-up malloc of ptr[3] failed for size %d\n",
           size / 2);
    exit(1);
  }

  /*
	 * this one should fail by a smidge
	 */
  ptr[4] = memory_alloc(size / 2);
  if (ptr[4] == NULL)
  {
    printf("run-up malloc of ptr[4] failed for size %d\n",
           size / 2);
  }

  /*
	 * at this point, we should start walking back from size/2 until we
	 * find a size we can malloc
	 */
  lsize = size;
  while ((ptr[4] = memory_alloc(lsize)) == NULL)
  {
    lsize -= 1;
    if (lsize == 0)
    {
      printf("run back to zero\n");
      exit(1);
    }
  }
  printf("first size found: %d\n", lsize);

  /*
	 * lsize is now small enough to malloc
	 */
  curr = 5;

  while (curr < 10)
  {
    ptr[curr] = memory_alloc(lsize);
    if (ptr[curr] == NULL)
    {
      break;
    }
    curr++;
  }

  if (curr == 10)
  {
    printf("total pointer count exceeded\n");
    exit(1);
  }

  curr = 6;

  /*
	 * now free them all -- the list should look coherent
	 */
  for (i = 0; i < curr; i++)
  {
    memory_free(ptr[i]);
  }

  printf("made it -- passed test\n");

  return 0;
}
