/* unit testing driver for hilbert.c */
/* Note complex.h header is included before fftw3.h */

/* #include "envelope.h" */
#include "hilbertf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main(void)
{

  float x[] = { 1.0, 2.0, 3.0, 4.0, 10.0, 21.0, 32.0, 43.0 };

  int nt = 4;
  int n2 = 2;
  float* y = malloc(sizeof(float) * nt * n2);

  envelope(y, x, nt, n2);

  printf("Original signal x = \n");
  for (int i = 0; i < 4; i++) {
    printf("%11.7f   %11.7f\n", x[i], x[i + 4]);
  }

  printf("It's envelope signal e =\n");
  for (int i = 0; i < 4; i++) {
    /* printf("z[%d] = %f + i%f\n",i,z[i][0],z[i][1]); */
    /* printf("z[%d] = %f + i%f\n",i,crealf(z[i]),cimagf(z[i])); */
    printf("%11.7f   %11.7f\n", y[i], y[i + 4]);
  }

  return 0;
}
