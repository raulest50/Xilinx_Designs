%%%
% Matlab Ethernet ArtyA7 FPGA FFT acceleration test


cli = tcpclient('192.168.1.10', 7, "Timeout", 500);
configureTerminator(cli,"LF");

configureCallback(cli,"terminator", @(varargin)cback_tcp(cli));


writeline(cli, '$d');
data = readline(cli);

if

function [] = cback_tcp(cli)
    data = readline(cli);
    disp(data)
end