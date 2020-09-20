n=512;                                               %number of points
Fs=1200;                                              %sampling fequency
fo=100;f1=3*fo;                                      %frequencies in Hz
 
t=(0:(n-1))/Fs;                                      %time vector
 
y=sin(2*pi*fo*t)+ 0.8*cos(2*pi*f1*t)+0.1*randn(1,n); %time domain signal with noise
p=fft(y);                                            %frequency domain 											transformation
 
F=(0:(n/2)-1)*Fs/512;
 
 
figure(1); clf
subplot(212); plot(F,abs(p(1:256)),'b.-'); xlabel('Frequency (Hz)'); ylabel('Magnitude'); %ploting graphs
subplot(211); plot(F,angle(p(1:256)),'m.-'); xlabel('Frequency (Hz)'); ylabel('Phase');   %ploting graphs
