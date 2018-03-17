/* compute discrete-time analytic signal in frequency domain */
/*
 * References:
 * [1] Marple, S. L. "Computing the Discrete-Time Analytic Signal via FFT." IEEE
 * Transactions on Signal Processing. Vol. 47, 1999, pp. 2600-2603.
 *
 */
#include "analytic.h"

static int nt, nw, n2buf;
static fftwf_plan forward_plan, inverse_plan;
fftwf_complex* z;

void
analytic_init(int nt_, /* number of samples of the signal */
              int n2_  /* number of times to compute analytic signal */
              )
/* assume enough memory for holding the whole array */
{
  nt = nt_;
  n2buf = n2_;
  nw = nt;
  z = (fftwf_complex*)fftwf_malloc(sizeof(fftwf_complex) * nt * n2buf);
  memset(z, 0, sizeof(fftwf_complex) * nt * n2buf);

// in-place complex-to-complex forw/back plans
#ifdef SF_HAS_FFTW_OMP
  fftwf_plan_with_nthreads(omp_get_max_threads());
#endif
  forward_plan = fftwf_plan_many_dft(1, &nt, n2buf, (fftwf_complex*)z, NULL, 1,
                                     nt, (fftwf_complex*)z, NULL, 1, nw,
                                     FFTW_FORWARD, FFTW_ESTIMATE);
#ifdef SF_HAS_FFTW_OMP
  fftwf_plan_with_nthreads(omp_get_max_threads());
#endif
  inverse_plan = fftwf_plan_many_dft(1, &nt, n2buf, (fftwf_complex*)z, NULL, 1,
                                     nw, (fftwf_complex*)z, NULL, 1, nt,
                                     FFTW_BACKWARD, FFTW_ESTIMATE);
}

fftwf_complex*
analytic_execute(float* x)
{
  for (int i = n2buf * nt - 1; i >= 0; i--)
    z[i] = x[i];

  // step 1: forward DTFT (do not zero-padding)
  fftwf_execute(forward_plan);

  // step 2: n-point one-sided discrete-time "analytic" signal
  for (int i2 = 0; i2 < n2buf; i2++) {
    /* Z[0] = X[0]; Z[n/2] = X[n/2]; */
    for (int i1 = nw / 2 - 1; i1 > 0; i1--) {
      z[i2 * nw + i1] *= 2.0;
    }
    for (int i1 = nw / 2 + 1; i1 < nw; i1++) {
      z[i2 * nw + i1] = 0.0;
    }
  }

  // step 3: inverse DTFT
  fftwf_execute(inverse_plan);

  // normalization
  for (int i = n2buf * nt - 1; i >= 0; i--)
    z[i] /= nt;
  return z;
}

void
analytic_free(void)
{
  fftwf_destroy_plan(forward_plan);
  fftwf_destroy_plan(inverse_plan);
  fftwf_free(z);
}
