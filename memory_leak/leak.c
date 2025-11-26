#include <emscripten/emscripten.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ONE_MB 1048576
#define LEAK_MESSAGE "if your looking at the register good job"

EMSCRIPTEN_KEEPALIVE
void leak_mb(int in_mb) {
  const size_t msg_len = strlen(LEAK_MESSAGE);
  if (msg_len >= ONE_MB) {
    fprintf(stderr, "message to big from 1mb block.\n");
    return;
  }

  int i;
  printf("Starting allocation loop to leak %dMB...\n", in_mb);
  for (i = 0; i < in_mb; i++) {
    // allocate 1 MB of memory in each iteration.
    char *data = (char *)malloc(ONE_MB);

    // check for allocation failure
    if (data == NULL) {
      fprintf(stderr,
              "memory allocation failed after %d blocks (less than %dMB "
              "leaked).\n",
              i, in_mb);
      break;
    }

    // so, at first i tried to do a lazy allocation of memory, where i only
    // allocated something in the front and in the end of the block, but i
    // actually couldnt do that for some reason (maybe my macbook was too
    // smart). instead i had to actually stuff the register with real data to
    // get my program to leak memory for real.
    strncpy(data, LEAK_MESSAGE, msg_len);
    size_t current_offset = msg_len;

    while (current_offset < ONE_MB) {
      size_t bytes_to_copy = ((ONE_MB - current_offset) > msg_len)
                                 ? msg_len
                                 : (ONE_MB - current_offset);
      memcpy(data + current_offset, data, bytes_to_copy);
      current_offset += bytes_to_copy;
    }

    printf("leaking...\t");
  }

  printf("successfully allocated %d blocks of 1MB each.\n", i);
  printf("approximately %dMB of memory has been leaked (reserved by this "
         " process).\n",
         in_mb);
}

int main() {
  printf("starting to leak, better plug me up.\n\n");
  leak_mb(50000);
  printf("program has finished leaking. please check system memory now, "
         "program will exit in 10s.\n");

  // wait for a 10 seconds.
  time_t start, end;
  time(&start);
  do
    time(&end);
  while (difftime(end, start) <= 10);

  // once the program exits, it should hypothetically free the memory.
  // hypothetically....
  return 0;
}

#ifdef __cplusplus
}
#endif
