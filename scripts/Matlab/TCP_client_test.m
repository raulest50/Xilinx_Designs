% se crea un cliente TCP/IP
cli = tcpclient('192.168.1.10', 7, "Timeout", 500);
writeline(cli, 'hola');
data = readline(cli);