

load('debug.mat');

Aout = ifft(fft(Ain).*Dh);

fileID = fopen('./debug_out.dat');
tex = textscan(fileID, '%s');
fclose(fileID);
tex = replace(tex{1}, '(', '');
tex = split(tex{1}, ')');
len = length(tex)-1;
Adbg = zeros(len,1);
for n=1:len
    aux = split(tex{n}, ',');
    Adbg(n) = str2double(aux{1}) + 1j*str2double(aux{2});
end

clear tex aux;