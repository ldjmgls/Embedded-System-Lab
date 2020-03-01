import numpy as np
import serial
import time

# generate the waveform table
waveformLength = 128
t = np.linspace(0, 2*np.pi, waveformLength)
waveformTable = (np.sin(t) + 1.0) / 2.0

# output formatter
formatter = lambda x: "%.3f" % x

# send the waveform table to K66F
serdev = '/dev/ttyACM0'
s = serial.Serial(serdev)
print("Sending waveform ...")
print("It may take several seconds ...")
for data in waveformTable:
  s.write(bytes(formatter(data), 'UTF-8'))
  time.sleep(0.1)
s.close()
print("Waveform sended")