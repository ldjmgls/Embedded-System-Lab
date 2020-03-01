import serial
import time

# send the message to K66F
serdev = '/dev/ttyACM0'
s = serial.Serial(serdev,baudrate=115200)
print("Sending message ...")
print("It may take several seconds ...")
s.write(bytes("106061224", 'UTF-8'))
time.sleep(1)
s.close()
print("Message sended")