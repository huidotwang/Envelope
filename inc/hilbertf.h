#include <complex.h>
#include <fftw3.h>
#include <omp.h>
#include <string.h>

void analytic_init(int nt_, /* number of samples of the signal */
                   int n2_  /* number of times to compute analytic signal */
                   );

fftwf_complex* analytic_execute(float* x);

void analytic_free(void);

void hilbert(float* y, float* x, int nt, int n2);

void envelope(float* y, float* x, int nt, int n2);
