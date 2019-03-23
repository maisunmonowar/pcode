import serial
import time
ser = serial.Serial('COM12', baudrate = 9600, timeout = 1)
x = 0


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
		if msg3[0:15] == 'gsToBIRDcommand':
			print("Command Received")
			if msg3[15:24] == 'endOfFile':	
				print("end of file command")
				file.close()
			if msg3[15:25] == 'nameOfFile':	
				print("name of file command")
				nameOfFile = msg3[25:len(msg3)-2]
				print(nameOfFile)
			if msg3[15:25] == 'modeOfFile':	
				print("mode of file command")
				modeOfFile = msg3[25:len(msg3)-2]
				print(modeOfFile)
				file = open(nameOfFile,modeOfFile)
		if msg3[0:4] == 'data':
			file.write(msg3[4:len(msg3)-1])	
	
	time.sleep(.1)
	x+=1
	if x == 39:
		condition = input("Continue? y/n")
		if 'y' == condition:
			x = 0


ser.close()
print("End")