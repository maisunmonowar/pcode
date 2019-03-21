import serial
import time
ser = serial.Serial('COM8', baudrate = 9600, timeout = 1)
x = 0
msg = 'this is a message.'
msg += '\n'
if ser.isOpen():
    ser.close()
ser.open()
while x<2:
	#ser.write(b'HelloPythonCOMport\n')
	ser.write(msg.encode())
	time.sleep(1)
	x+=1

file = open("test.txt","r")

x = 0
while x < 20:
	msg = file.readline()
	msg += '\n'
	ser.write(msg.encode())
	time.sleep(1)

file.close()
ser.close()