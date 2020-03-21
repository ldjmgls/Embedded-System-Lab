import matplotlib.pyplot as plt
import numpy as np
import serial
import time

Fs = 100.0;  # sampling rate
Ts = 1.0/Fs; # sampling interval
t1 = np.arange(0,1,Ts) # time vector; create Fs samples between 0 and 1.0 sec.
y1 = np.arange(0,1,Ts) # signal vector; create Fs samples
y2 = np.arange(0,1,Ts) # signal vector; create Fs samples

n = len(y1) # length of the signal
k = np.arange(n)
T = n/Fs
frq = k/T # a vector of frequencies; two sides frequency range
frq = frq[range(int(n/2))] # one side frequency range

serdev = '/dev/ttyACM0'
s = serial.Serial(serdev)
for x in range(0, int(Fs)):
    line1=s.readline() # Read an echo string from K66F terminated with '\n'
    line2=s.readline()
    # print line
    y1[x] = float(line1)
    y2[x] = float(line2)

Y = np.fft.fft(y1)/n*2 # fft computing and normalization
Y = Y[range(int(n/2))] # remove the conjugate frequency parts

fig, ax = plt.subplots(2, 1)
ax[0].plot(t1,y1,t1,y2) # plot two lines(digital & analog) on same pic
ax[0].set_xlabel('Time')
ax[0].set_ylabel('Amplitude')
ax[1].plot(frq,abs(Y),'r') # plotting the spectrum
ax[1].set_xlabel('Freq (Hz)')
ax[1].set_ylabel('|Y(freq)|')
plt.show()
s.close()