#import Adafruit_BBIO.UART as UART
import serial
import time
#UART.setup("UART4")

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

ser.writeTimeout = 2

try:
	ser.open()
except Exception as e:
	print("error open Serial Port: " +str(e))
	exit()


if ser.isOpen():
	print("Serial is Open")
	ser.write("Hello Serial Port")
else:
	print("Serial is not open")
ser.close()
#UART.cleanup()
