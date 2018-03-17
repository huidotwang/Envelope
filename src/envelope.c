/* compute envelope of discrete time real signal */
#include "envelope.h"

void
envelope(float* y, float* x, int nt, int n2)
/*
 * @param x: input signal with length nt*n2
 * @param nt: length of the signal
 * @param n2: counts of signals
 * @return y: envelope of the input signal
 */
{
  analytic_init(nt, n2);
  fftwf_complex* z = analytic_execute(x);
  for (int i = n2 * nt - 1; i >= 0; i--)
    y[i] = sqrtf(crealf(z[i]) * crealf(z[i]) + cimagf(z[i]) * cimagf(z[i]));
  analytic_free();
  return;
}
