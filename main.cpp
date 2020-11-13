#include "RngStream.h"
#include <stdio.h>

int main(void) {
  double x;
  int i;
  RngStream gen;

  /* get a stream */
  gen = RngStream_CreateStream("generator_1");

  /* sample from generator */
  for (i = 0; i < 10; i++) {
    x = RngStream_RandU01(gen);
    printf("%f\n", x);
  }

  return 0;
}
