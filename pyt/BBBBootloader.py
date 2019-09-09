#import every thing necessary
import serial
import time
import os
import Adafruit_BBIO.GPIO as GPIO

#define pins
LED="P9_12"
GPIO.setup(LED, GPIO.OUT)
GPIO.output(LED, GPIO.LOW) #to enter bootloader mode
time.sleep(2) #to give MCU to enter into boothloader mode

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
	print("\n\rSerial is Open\n\r")
	ser.readline()
	ser.readline()#to clear the buffer
	#there has to be a better way to do it
	for x in range(len(lineList)):
    		print(lineList[x])
    		ser.write(lineList[x])
    		print("Feed, ")
<<<<<<< HEAD
		feedbackMsg = ser.readline()
		print(len(feedbackMsg))
		print(" ")
    		print(feedbackMsg)
    		print("\n")
		stupid = [ord(g) for g in feedbackMsg]
		print(stupid)
		print("\n")
=======
            time.delay(0.01)
            feedback = ser.readline()
    		print(feedback)
    		print("\n")
            while (feedback.find(b'\x06') == -1):
                #means there was no feedback
                #try again
                print("trying again")
                ser.write(lineList[x])
                print("Feed, ")
                time.delay(0.01)
                feedback = ser.readline()
                print(feedback)
                print("\n")
>>>>>>> 7aaac375d6728cd69600c09e9b3f82c8868fc692
else:
	print("Serial is not open")

#analyze feedback
for y in range(5):
	feedback = ser.readline()
	if (feedback.find(b'\x06') != -1):
		print("Success feedback")

#cleanup
GPIO.output(LED, GPIO.HIGH) #Normally needs to be high
ser.close()
file.close()
GPIO.cleanup()
print("end")
