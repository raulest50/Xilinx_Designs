%%%
% Matlab Ethernet ArtyA7 FPGA FFT acceleration test


cli = tcpclient('192.168.1.10', 7, "Timeout", 500);
configureTerminator(cli,"LF");

% configureCallback(cli,"terminator", @(varargin)cback_tcp(cli));

N = 8192;
%A = 0:1:N;
A = zeros(1, N);
A(N/2: N/2 + 10) = 10;
B = fft(A);
An = complex_vector_org(B);

data = single(zeros(1, 2*N));

writeline(cli, '$d');
resp = readline(cli);

for i=1:64
    write(cli, An(256*(i-1)+1 : i*256), 'single');
end

data(1:8192) = read(cli, 8192, 'single');
writeline(cli, '$d');
data(8193:end) = read(cli, 8192, 'single');

y = data(1:2:end) + 1i*data(2:2:end);
plot(abs(y/8192));



% organiza un vector con numeros complejos en la forma mas conveniente
% para enviarselo a la arty y al ip de fft de vivado. Ejemplo:
% real(0), imag(0), real(1), imag(1), real(2), imag(2) etc
% es decir que un vector de complejos en matlab, siempre queda 
% del doble de tamaño, si es 128 entonces 256 (128 reales 128 complejos)
function [Y] = complex_vector_org(A)
    A = single(A);
    Af = [real(A) ; imag(A)];
    Y = Af(:);
end


% function [] = cback_tcp(cli)
%     data = readline(cli);
%     disp(data)
% end