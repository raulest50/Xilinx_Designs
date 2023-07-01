%%%
% Matlab Ethernet ArtyA7 FPGA FFT acceleration test


%cli = tcpclient('192.168.1.10', 7, "Timeout", 500);
%configureTerminator(cli,"LF");

%configureCallback(cli,"terminator", @(varargin)cback_tcp(cli));

%N = 8192;
%load('inputs.mat');
%Dh = complex_vector_org(ex_Dh);

%data = single(zeros(1, 2*N));

%writeline(cli, '$d');
%resp = readline(cli);
%disp(resp)

%for i=1:64
%    write(cli, A, 'single');
%end

%data(1:8192) = read(cli, 8192, 'single');
%writeline(cli, '$d');
%data(8193:end) = read(cli, 8192, 'single');


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