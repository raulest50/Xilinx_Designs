

xnf = exp(-single(-128:128).^2);
xkf = fft(xnf);

plot(fftshift(abs(xkf)));
hold on

signess = 1; % con signo
w_len = 16; % word length
f_len = 3; % fraction length
xnp = fi(xnf, 1, 16, 5);
xkp = fft(single(xnp));
%figure;
plot(fftshift(abs(xkp)));

