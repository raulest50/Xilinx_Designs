clear all;
clc;

devs = serialportlist();
blaze = serialport(devs(2), 9600, 'Parity','none', 'StopBits',1, 'DataBits',8);
configureTerminator(blaze,"LF");

configureCallback(blaze,"byte", 1, @(varargin)cback(blaze));

%write(blaze, 'a',"uint8");


function [] = cback(blaze)
    
    persistent buff;
    persistent ind;

    if(isempty(buff))
        buff = zeros(1, 200);
        ind=1;    
    end
    
    b = read(blaze,1,"uint8");
    if( b == 10) % si es el caracter de terminacion
        ind = 1;
        disp(char(buff));
        buff = zeros(1, 200);
    else % si no
        buff(ind) = b;
        ind = ind+1;
    end
end
