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
	
	#time.sleep(1)

	feedback = ser.readline()
	while len(feedback) <= 2:
		feedback = ser.readline()
	feedback2 = feedback[0:22] #This is still a byte obj
	feedback3 = feedback2.decode() #Feedback3 is now a string
	print(feedback3)
	while feedback3 != 'Procceed with the next':
		feedback = ser.readline()
		feedback2 = feedback[0:22] #This is still a byte obj
		feedback3 = feedback2.decode() #Feedback3 is now a string
		print(feedback3)
	x+=1

file.close()
ser.close()