/* unit testing driver for analytic.c */
/* Note complex.h header is included before fftw3.h */

/* #include "analytic.h" */
#include "hilbertf.h"
#include <fftw3.h>
#include <stdio.h>
#include <math.h>

int
main(void)
{

  float x[] = { 1.0, 2.0, 3.0, 4.0, 10.0, 21.0, 32.0, 43.0 };
  analytic_init(4, 2);

  fftwf_complex* z = analytic_execute(x);

  printf("Original signal x = \n");
  for (int i = 0; i < 4; i++) {
    printf("%11.7f   %11.7f\n", x[i], x[i + 4]);
  }

  printf("Analytic signal z = \n");
  for (int i = 0; i < 4; i++) {
      if (cimagf(z[i]) < 0)
        printf("%11.7f - %11.7fi", crealf(z[i]), fabs(cimagf(z[i])));
      else 
        printf("%11.7f + %11.7fi", crealf(z[i]), fabs(cimagf(z[i])));

      if (cimagf(z[i]+4) < 0)
        printf("  %11.7f - %11.7fi\n", crealf(z[i + 4]), fabs(cimagf(z[i + 4])));
      else
        printf("  %11.7f + %11.7fi\n", crealf(z[i + 4]), fabs(cimagf(z[i + 4])));
  }

  analytic_free();
  return 0;
}
