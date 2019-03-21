import serial
import time
ser = serial.Serial('COM12', baudrate = 9600, timeout = 1)
x = 0

file = open("received2.txt","w+")
if ser.isOpen():
    ser.close()
ser.open()
while x<40:
	#ser.write(b'HelloPythonCOMport\n')
	msg = ser.readline()
	msg2 = msg
	if len(msg)>2: 
		if len(msg)<5:
			msg += ser.readline()
		print(str(msg))
		print(len(msg))
		msg2 = msg[4:len(msg)]
		msg3 = msg2.decode()
		file.write(msg3)	
	
	time.sleep(.1)
	x+=1
	if x == 39:
		condition = input("Continue? y/n")
		if 'y' == condition:
			x = 0

file.close()
ser.close()
print("End")