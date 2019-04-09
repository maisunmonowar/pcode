import serial
import time
ser = serial.Serial('COM12', baudrate = 9600, timeout = 1)
x = 0
oldPacketCode = b'xx'

if ser.isOpen():
    ser.close()
ser.open()
while x<40:
	#ser.write(b'HelloPythonCOMport\n')
	msg = ser.readline()
	msg2 = msg
	if len(msg)>2:
		print("len>2") 
		if len(msg)<5:
			print("len<5") 
			msg += ser.readline()
		print(str(msg))
		print(len(msg))
		msg2 = msg[4:len(msg)]
		msg3 = msg2.decode()
		newPacketCode = msg[0:4]
		if newPacketCode != oldPacketCode:

			if msg3[0:15] == 'gsToBIRDcommand':
				print("Command Received")
				if msg3[15:24] == 'endOfFile':	
					print("end of file command")
					file.close()
					#count execution time
					endTime = time.time()
					break
				if msg3[15:25] == 'nameOfFile':	
					print("name of file command")
					nameOfFile = msg3[25:len(msg3)-2]
					print(nameOfFile)
					#count execution time
					startTime = time.time()
				if msg3[15:25] == 'modeOfFile':	
					print("mode of file command")
					modeOfFile = msg3[25:len(msg3)-2]
					print(modeOfFile)
					file = open(nameOfFile,modeOfFile)
				x = 0
				#so the loop will act as a timeout check	
			if msg3[0:4] == 'data':
				file.write(msg3[4:len(msg3)-1])	
				x = 0
				#so the loop will act as a timeout check
			oldPacketCode = newPacketCode	
		else:
			#same packet
			print("same packet")
	#tell ardunio >> ok
	ser.write(b'ok\n')

	time.sleep(.1)
	x+=1
	if x == 39:
		condition = input("Continue? y/n")
		if 'y' == condition:
			x = 0


ser.close()
print ("Process took")
print(endTime - startTime)
print("End")