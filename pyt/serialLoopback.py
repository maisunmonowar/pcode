#import necessary library
import serial

#open serial
ser = serial.Serial()
ser.port = "/dev/ttyO1"
ser.baudrate = 9600
ser.bytesize = serial.EIGHTBITS
ser.parity = serial.PARITY_NONE
ser.stopbits = serial.STOPBITS_ONE
ser.timeout = 2
ser.xonxoff = True
ser.rtscts = False
ser.dsrdtr = False
ser.writeTimeout = 2

try:
	ser.open()
except Exception as e:
	print("error open Serial Port: "+ str(e))
	exit()

if ser.isOpen():
	#:0606800080310A2C00008D
	ser.write(b':060668\n')
	x = ser.readline()
	print(x)
	print(type(x))
	print(len(x))

	ser.write(":060668\n")
	y = ser.readline()
	print(y)
	print(type(y))
	print(len(y))

	ser.write(b'abc\x30\x06')
	z = ser.readline()
	print(z)
	print(type(z))
	print(len(z))
ser.close()
print("End")
