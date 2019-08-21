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
msg = ''
with open("test.txt", "r") as file:
	for line in file 
		msg = line
		msg += '\n'
		ser.write(msg.encode())
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
	
if !file.closed:
	file.close()
ser.close()