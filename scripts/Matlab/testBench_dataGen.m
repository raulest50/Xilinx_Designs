
% script para generar un .dat file que utilizara e test bench de 
% vitis hls para probar el acelerador.

%xn = zeros(8192,1);
%xn(4000:4030) = 10;

load('patron.mat');
Ain = Ain';
% input pulse
save('Ain.dat', 'Ain', '-ascii');
