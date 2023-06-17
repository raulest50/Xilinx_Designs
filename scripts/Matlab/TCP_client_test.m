% se crea un cliente TCP/IP
cli = tcpclient('192.168.1.10', 7, "Timeout", 500);
configureTerminator(cli,"LF");

configureCallback(cli,"terminator", @(varargin)cback_tcp(cli));


writeline(cli, 'hola');


function [] = cback_tcp(cli)
    data = readline(cli);
    disp(data)
end