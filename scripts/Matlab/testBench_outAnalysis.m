

fileID = fopen('./out2.dat');
tex = textscan(fileID, '%s');
fclose(fileID);
%whos tex

tex = replace(tex{1}, '(', '');
tex = split(tex{1}, ')');

len = length(tex)-1;

xk = zeros(len,1);

for n=1:len
    aux = split(tex{n}, ',');
    xk(n) = str2double(aux{1}) + 1j*str2double(aux{2});
end

hold on;

plot(abs(fftshift(xk)), 'ro');