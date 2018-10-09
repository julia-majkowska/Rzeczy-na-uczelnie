/*
 * Binary search vs. heap search.
 *
 * $ ./bsearch -n 23 -t 24 -v 0
 * Time elapsed: 8.101319 seconds.
 * $ ./bsearch -n 23 -t 24 -v 1
 * Time elapsed: 3.290986 seconds.
 */
#include "common.h"

void fill(int *arr, int n) {
  /* Yeah, gcc allows that, though it's non-standard extension ;) */
  int icmp(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
  }

  for (int i = 0; i < n; i++)
    arr[i] = rand();

  qsort(arr, n, sizeof(int), icmp);
}

void heapify(int *dst, int *src, int n) {
    int divisor = 2; 
    int i = 0; 
    n+=1;
    int addend = n/divisor * 2; 
    int cur_verse = n/divisor;
    while(divisor < n+2){
        addend = n/divisor * 2;
        cur_verse = n/divisor;
        while(cur_verse < n) {
            ///printf("%d ", n/divisor * multiplier-1);
            dst[i] = src[cur_verse-1]; 
            cur_verse += addend;
            i++;
        }
        //printf("\n");
        divisor<<=1;
    }
  /* XXX: Fill in this procedure! */
}

bool binary_search(int *arr, long size, int x) {
  do {
    size >>= 1;
    int y = arr[size];
    if (y < x)
      arr += size + 1;
    if (y == x)
      return true;
  } while (size > 0);

  return false;
}

bool heap_search(int *arr, long size, int x) {
  long i = 1;
  do {
    int y = arr[i - 1];
    long j = i * 2;
    if (y < x)
      j |= 1;
    //j|=(y < x) ;
    if (y == x)
      return true;
    i = j;
  } while (i <= size);
  return false;

  
}

int main(int argc, char **argv) {
  int opt, exp = -1, times = -1, var = -1;
  bool err = false;

  while ((opt = getopt(argc, argv, "n:t:v:")) != -1) {
    if (opt == 'n')
      exp = atoi(optarg);
    else if (opt == 't')
      times = 1 << atoi(optarg);
    else if (opt == 'v')
      var = atoi(optarg);
    else
      err = true;
  }

  if (err || exp < 0 || times < 0 || var < 0 || var >= 2) {
    fprintf(stderr,
            "Usage: %s -n log2(size) -l log2(times) -v variant\n", argv[0]);
    return 1;
  }

  int n = (1 << exp) - 1;
  int size = n * sizeof(int);
  int *arr = NULL, *tmp = NULL;
 
  posix_memalign((void **)&arr, getpagesize(), size);

  //printf("Generate array of 2^%d-1 elements (%d KiB)\n", exp, size >> 10);

  fill(arr, n);
  if (var == 1) {
    posix_memalign((void **)&tmp, getpagesize(), size);
    heapify(tmp, arr, n);
    free(arr);
    arr = tmp;
  }
  flush_cache();

  //printf("Performing %d searches.\n", times);

  _timer_t timer;
  timer_reset(&timer);
  timer_start(&timer);
  for (int i = 0; i < times; i++) {
    if (var == 0) {
      binary_search(arr, n, rand());
    } else {
      heap_search(arr, n, rand());
    }
  }
  timer_stop(&timer);
  timer_print(&timer);

  free(arr);

  return 0;
}
