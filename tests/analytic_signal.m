function [z] = analytic_signal(x)
  is_row_vector = isrow(x);
  if (is_row_vector)
    x = x';
  end
  N = length(x);
  X = fft(x, N);
  z = ifft([X(1); 2*X(2:N/2); X(N/2+1); zeros(N/2-1,1)], N);
  if (is_row_vector)
    z = z';
  end
end
