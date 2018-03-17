% x = [1.0; 2.0; 3.0; 4.0; 10.0; 21.0; 32.0; 43.0];
x = [1.0, 2.0, 3.0, 4.0; 10.0, 21.0, 32.0, 43.0]';
x
z = hilbert(x)
% z = analytic_signal(x);
fprintf('Analytic signal:');
z
h = imag(z);
fprintf('Hilbert transform:');
h
e = abs(z);
fprintf('envelope signal:');
e
