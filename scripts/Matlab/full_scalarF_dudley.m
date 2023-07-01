%%%%%%%%% Rodrigo Acuna- University of Wisconsin - Milwaukee
%%%%%%%%%Solving: NLSE in Fiber Optics by using Split-step-Method and
%%%%%%%%%Four Order Runge-Kutta. Dudley paper

clear all 
global nt;
global dtau;
global f_R;
global gama;
global A0;
global Tshock;
global omega


c=3*10.^8;% m/s
l0=835*10^-9;%m - Wavelenth 
f0=c/l0*10^-12;%in Hz
w0=(2*pi*c/l0);%rad/s
k0=(2*pi/l0);%in m-1
gama=0.11;%W-1*m-1, n2=2.6*10^-20, Aeffx=0.84*10^12 m^2. gamax = (n2*w0)/(c*Aeffx), slow axes
T0=0.0284;%in ps. T-FWHM=1.665T0 for Gaussian pulse, T-FWHM=1.763T0 for Gaussian pulse
z=0.15;%Distance in m
fR=0.18;%%Raman response Coefficient
Tshock=(1/w0)*1.0e12;%%%0.56*10^-3;%%%ps
P0=10000;%Initial Power, in W
nt = 2^13;  % FFT points and window size
step_num = 1500;%10^3; % Number of z steps 
distance = z;
t_mult=150;% How large should the time window be as a multiple of the FWHM?

%%%%Be careful betax(m)=beta(m-1) order. eg betax(1)=betax0,
beta(2)=-11.830*10^-3;%ps^2/m, beta1x
beta(3)=8.1038*10^-5;%ps^3/m;
beta(4)=-9.5205*10^-8;%ps^4/m;
beta(5)=2.0737*10^-10;%ps^5/m
beta(6)=-5.3943*10^-13;%%ps^6/m
beta(7)=1.3486*10^-15;%%ps^7/m
beta(8)=-2.5495*10^-18;%%ps^8/m
beta(9)=3.0524*10^-21;%%ps^9/m
beta(10)=-1.7140*10^-24;%%ps^10/m

%%%%Dispersion Lengths

%LD=T0^2/abs(beta(2))
%Ltod=T0^3/abs(beta(3))

%%%%%Parameter for the pulse
mshape = 0;%shape of incide pulse, mshape = 1, Gaussian
chirp0 = 0; % input pulse chirp
m=mshape;
c0=chirp0;

if mshape==0
    t0_FWHM = 2*log(1+sqrt(2))*T0;
else
    t0_FWHM = 2*sqrt(log(2))*T0;
end

%---set simulation parameters
t_range = .5*t_mult*t0_FWHM; 
tau = linspace(-t_range, t_range, nt+1); % temporal grid
tau = tau(1:end-1);
dtau = tau(2)-tau(1); 
fs = 1/dtau;% Sampling frequency
deltaz = distance/step_num;
domega = 2*pi/nt*fs;
omega = [-2*pi*fs + (((nt/2):(nt-1))*domega), (0:(nt/2-1))*domega];% frequency grid
f = omega/2/pi;

% Shift the frequency domain to match MATLAB's shifted domain
omega = fftshift(omega);
omega0 = 2*pi*c/l0;
 

%---Input Field profile, initial pulse
if mshape==0
    A= sqrt(P0)*sech(tau/T0).*exp(-0.5i*chirp0*(tau/T0).^2);% polarized light along -x
    
else % super-Gaussian or Gaussian (mshape =1)
    A =sqrt(P0)*exp(-0.5*(1+1i*chirp0).*(tau/T0).^(2*mshape));
    
end

A0=A;
%---Plot input pulses shape and spectrum
figure; 
%subplot(3,1,1);
%plot(tau, ((abs(A)).^2)/P0,'-r')
%axis([-.4 .4 0 inf]);
%xlabel('Frequency (THz)');
%ylabel('Normalized Power');
%title('Spectrum Input Pulse');
%hold on;
%plot(f,(dtau^2*abs(fftshift(fft(A0))).^2)/P0,'-r'); %Plotting the initial pulse
%axis([-50 50 0 inf])
%hold on
%xlabel('Normalized Frequency');
%ylabel('Spectral Power, dB');

%%%%%%%%Dispersion effects
dispbeta=0;

for v=2:10
    dispbeta=dispbeta+(beta(v)/(factorial(v)))*omega.^(v);%sum of dispersion terms, for m>=2 plus dbeta1
    
end
dispersion_half = exp(-i*dispbeta.*deltaz/2); % Half Dispersion term, in frequency domain

%%%%%%%% R(t)-Raman-Fourier domain%%%%%%%%%%%%
for kk=1:nt
    hR1(kk)=hR(tau(kk));
end

f_R=((1-fR)+dtau*fR*fft(fftshift(hR1)));%%%Raman - Frequency Domain


% scheme: 1/2D -> N -> 1/2D; first half step nonlinear
%exA = A;
%ex_Dh = dispersion_half;
tic
Ain = A;
for n=1:step_num %Total of number step 
    
    %%%%%%First half dispersion
    A = ifft(fft(A).*dispersion_half);%converting to w domain
    
    %%%%%% Non-linear step using Runga-Kutta, 4th order 
    k1 = NLT(A);
    A_half2 = A + k1*deltaz/2;
    k2 = NLT(A_half2);
    A_half3 = A + k2*deltaz/2;
    k3 = NLT(A_half3);
    A_full = A + k3*deltaz;
    k4 = NLT(A_full);
    A = A + deltaz/6*(k1 + 2*k2 + 2*k3 + k4);
    
    %%%%%%Second half dispersion
    A = ifft(fft(A).*dispersion_half);%converting to w-domain
    %A_shot(:,n)=A;
    %P_t(:,n)=((abs(A)).^2)/P0;%% Time domain
    %P_w(:,n)=((dtau^2/(P0))*abs(fftshift(fft(A))).^2);%%%Frequency domain, no dB, in column each veactor
          
end
toc
Afin = A;

%dlmwrite('pw.txt', P_w, 'delimiter', '\t');%%%row(lambda) column(acoustic wavelength)
%dlmwrite('pt.txt', P_t, 'delimiter', '\t');
%qw=dlmread('pw.txt');%%%%reading the power file
l_lambda=c*10^-3./(f0+f);

%%%%Output - Pulse last step
Pt=((abs(A)).^2)/P0;%% Time domain
subplot(2,1,1)%%%Wavelength-Plot
xlabel('Wavelength (nm)');
ylabel('Power(dB)');
title('Output - Spectrum');
hold on;
%plot(l_lambda,10*log10((dtau^2/(P0))*abs(fftshift(fft(A))).^2),'-b'); %Plotting the final pulse in dB
plot(l_lambda,10*log10((dtau^2/(P0))*abs(fftshift(fft(A))).^2),'-b');
axis([300 1500 -100 10])


subplot(2,1,2)%%%%%Time Plot
xlabel('Time (ps)');
ylabel('Normalized Power');
title('Output - Shape');
hold on;
plot(tau, Pt, '-b')
%axis([-1 1 0 inf])
