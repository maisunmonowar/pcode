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
UART4 = serial.Serial()
UART4.port= "/dev/ttyO4"
UART4.baudrate = 9600
UART4.bytesize = serial.EIGHTBITS
UART4.parity = serial.PARITY_NONE
UART4.stopbits = serial.STOPBITS_ONE
UART4.timeout = 1
UART4.xonxoff= True
UART4.rtscts = False
UART4.dsrdtr = False
UART4.writeTimeout = 1

uart1 = serial.Serial()
uart1.port = "/dev/ttyO1"
uart1
#prepare files
nameOfFile = "appv2.hex"
modeOfFile = "r"

with open(nameOfFile, modeOfFile) as file:
    lineList = file.readlines()
print("list loading done.\n\r")
print("Number of lines: ")
print(len(lineList))

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
	print(ser.readline())
	print(ser.readline())
	print(ser.readline())
	print(ser.readline())
	GPIO.output(LED, GPIO.HIGH)

	for x in range(len(lineList)-2):
    		print(lineList[x])
    		ser.write(lineList[x])
    		time.sleep(.1)
		feedback = ser.readline()
		print("Feed, ")
    		print(feedback)
    		#print("\n")
		while (feedback.find(b'\x06') == -1):
                	#means there was no feedback
	                #try again
			print("trying again")
			ser.write("refresh\x0D")#im thinking serial line may be noisy. need to clear things???
			ser.write(lineList[x])
			time.sleep(.1)
			feedback = ser.readline()
			print("Feed, ")
			print(feedback)
	endTime = time.time()
	#GPIO.output(LED, GPIO.HIGH)
else:
	print("Serial is not open")

#analyze feedback
for y in range(60):
	feedback = ser.readline()
	print(feedback)
	if (feedback.find(b'\x06') != -1):
		print("06 Received")

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
print("end")
