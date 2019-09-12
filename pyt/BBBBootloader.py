#import every thing necessary
import serial
import time
import os
import Adafruit_BBIO.GPIO as GPIO

#define pins
LED="P9_12"
GPIO.setup(LED, GPIO.OUT)
GPIO.output(LED, GPIO.LOW) #to enter bootloader mode
print("bootloader mode selected")
feedback = "nothing"

#open Serial
ser = serial.Serial()
ser.port= "/dev/ttyO4"
ser.baudrate = 9600
ser.bytesize = serial.EIGHTBITS
ser.parity = serial.PARITY_NONE
ser.stopbits = serial.STOPBITS_ONE
ser.timeout = 1
ser.xonxoff= False
ser.rtscts = False
ser.dsrdtr = False
ser.writeTimeout = 1

#prepare files
nameOfFile = "appv2.hex"
modeOfFile = "r"

with open(nameOfFile, modeOfFile) as file:
    lineList = file.readlines()
print("list loading done.\n\r")
print("Number of lines: ")
print(len(lineList))
fail = 0

try:
        ser.open()
except Exception as e:
        print("error open Serial Port: " +str(e))
        GPIO.output(LED, GPIO.HIGH) #Normally needs to be high
        file.close()
	GPIO.cleanup()
        exit()

#do the work
if ser.isOpen():
	#count start time
	startTime = time.time()
	print("\n\rSerial is Open\n\r")
	#make sure the MCU is in bootloader mode:
	while feedback.find(b'ownload') == -1:
		feedback = ser.readline()
		print("Feed, ")
		print(feedback)
		print("\n")
	#flushing everything out of buffer
	while ser.inWaiting() > 0:
		print(ser.readline())
	GPIO.output(LED, GPIO.HIGH)

	for x in range(len(lineList)-2):
    		print(lineList[x])
    		ser.write(lineList[x])
		feedback = ser.read(3)
		#print("Feed, ")
    		#print(feedback)
    		#print("\n")
		while (feedback.find(b'\x11') == -1):
                	#means there was no feedback
	                #try again
			print("trying again")
			fail += 1
			#ser.write("refresh\x0D")#im thinking serial line may be noisy. need to clear things???
			ser.write(lineList[x])
			#time.sleep(.1)
			#i = 0
			#while ser.inWaiting() < 3 and i < 3000:
				#wait
		#		i += 1
		#	if ser.inWaiting() == 3:
			feedback = ser.read(3)
		#	else:
		#		feedback = ser.readline()
			#print("Feed, ")
			#print(feedback)
	endTime = time.time()
	#GPIO.output(LED, GPIO.HIGH)
else:
	print("Serial is not open")

#analyze feedback
print("\n\r Sending done")
for y in range(10):
	if ser.inWaiting() > 0:
		feedback = ser.readline()
		print(feedback)
	else:
		time.sleep(1)	

#cleanup
GPIO.output(LED, GPIO.HIGH) #Normally needs to be high
ser.close()
file.close()
GPIO.cleanup()
#count execution time
#endTime = time.time()
print("process took, ")
print(endTime - startTime)
print(" seconds\n\r")
print("fail count " + str(fail))
print("end")
