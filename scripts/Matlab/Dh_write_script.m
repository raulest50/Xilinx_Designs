

Dh = readmatrix('Dh_csv.txt');

Dhc = Dh(1:2:end) + 1j*Dh(2:2:end);

fid = fopen('Dh_cpp2.txt','w');

%fprintf(fid, '{');

lenDh = length(Dhc);

for n=1:lenDh
    fprintf(fid, '{');
    fprintf( fid, num2str( real(Dhc(n)) ) );
    fprintf(fid, ',');
    fprintf( fid, num2str( imag(Dhc(n)) ) );
    fprintf(fid, '}');
    fprintf(fid, ',');
end

%fprintf(fid, '}');

fclose(fid);