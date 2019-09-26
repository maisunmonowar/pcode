#import the necessary items 
import serial
import Adafruit_BBIO.GPIO as GPIO
import time

#define pins
LED="P9_12"
GPIO.setup(LED, GPIO.OUT)
GPIO.output(LED, GPIO.HIGH) #to enter APP mode

#initialize serial parameter
ser = serial.Serial()
ser.port= "/dev/ttyO4"
ser.baudrate = 9600
ser.bytesize = serial.EIGHTBITS
ser.parity = serial.PARITY_NONE
ser.stopbits = serial.STOPBITS_ONE
ser.timeout = 1
ser.writeTimeout = 1
ser.xonxoff= True
ser.rtscts = False
ser.dsrdtr = False

try:
        ser.open()
except Exception as e:
        print("error open Serial Port: " +str(e))
        GPIO.cleanup()
        exit()

#do the work
if ser.isOpen():
        print("Serial is Open")
<<<<<<< HEAD
	for x in range(50000):
		msg = ser.readline()
		msg_str = msg.decode()
		print(msg)
		if msg.find(b'\x06') != -1:
			print("06 Received")
=======
	for x in range(10):
		if ser.inWaiting() > 0:
			msg = ser.readline()
			#msg_str = msg.decode()
			print(msg)
		else:
			time.sleep(1)
		#if msg.find(b'\x06') != -1:
		#	print("06 Received")
>>>>>>> uartTrigger
else:
        print("Serial is not open")

#clean up
ser.close()
GPIO.cleanup()
print("end")
