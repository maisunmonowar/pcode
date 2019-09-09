#import every thing necessary
import serial
import time
import os

feedback = ""

#open Serial
ser = serial.Serial()
ser.port= "/dev/ttyO4"
ser.baudrate = 9600
ser.bytesize = serial.EIGHTBITS
ser.parity = serial.PARITY_NONE
ser.stopbits = serial.STOPBITS_ONE
ser.timeout = 1
ser.xonxoff= True
ser.rtscts = False
ser.dsrdtr = False
ser.writeTimeout = 1

#prepare files
nameOfFile = "siow.txt"
modeOfFile = "w+"

file = open(nameOfFile, modeOfFile)

try:
        ser.open()
except Exception as e:
        print("error open Serial Port: " +str(e))
        file.close()
        exit()

#do the work
if ser.isOpen():
	#count start time
	startTime = time.time()
	print("\n\rSerial is Open\n\r")
	
	for x in range(300):
    		feedback = ser.readline()
		print("Feed, ")
    		print(feedback)
		
    		if len(feedback) > 2:
			file.write(feedback)
			ser.write(b'\x06')
	endTime = time.time()
else:
	print("Serial is not open")

#analyze feedback
for y in range(60):
	feedback = ser.readline()
	print(feedback)
	if (feedback.find(b'\x06') != -1):
		print("06 Received")

#cleanup
ser.close()
file.close()
#count execution time
#endTime = time.time()
print("process took, ")
print(endTime - startTime)
print(" seconds\n\r")
print("end")
