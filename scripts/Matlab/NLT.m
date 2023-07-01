function y=NLT(u)

%%% u = A
%%%%%%%Non linear term%%%%%%%%%%

global gama;
global f_R;
global dtau;
global Tshock;
global omega;

conR_A2=fftshift(ifft(f_R.*fft(fftshift(abs(u)).^2))); %% se resuelve la integral


y=-i*gama*u.*conR_A2-gama*Tshock*fftshift(ifft(i*omega.*fft(fftshift(u.*conR_A2))));

end


