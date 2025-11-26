#include <emscripten/emscripten.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

// declare NUMBER_ON_LOAD as a global variable.
int NUMBER_ON_LOAD = 0;

// export the check_number function.
EMSCRIPTEN_KEEPALIVE
int check_number(int guessed_number) {
  if (guessed_number == NUMBER_ON_LOAD) {
    return 1;
  } else {
    return 0;
  }
}

int main() {
  // seed random number generator with current time.
  srand(time(NULL));
  NUMBER_ON_LOAD = rand() % 10;
  NUMBER_ON_LOAD += 1; // this makes it so it is 1-10, instead of 0-9.
  printf("The secret number is %d\n", NUMBER_ON_LOAD);
  return 0;
}

#ifdef __cplusplus
}
#endif
