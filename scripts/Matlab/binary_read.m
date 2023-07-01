% vitis can export from debug session binary data
% from specified addres. the exported file extension is bin
% this can allow data visialization outide vits

% in this script this bin data is read, a 16384 floats

fileID = fopen('A.bin', 'r');
A2 = fread(fileID, 'single');

A2 = line2cvec(A2)/97.33;

plot(fftshift(abs(A2)), 'go')
hold on;
At = ifft(fft(A).*Dh);
plot( abs(At), 'ro')



function [Y] = cvec2line(A)
    A = single(A);
    Af = [real(A) ; imag(A)];
    Y = Af(:);
end

function [Y] = line2cvec(A)
    Y = A(1:2:end) + 1j*A(2:2:end);
end