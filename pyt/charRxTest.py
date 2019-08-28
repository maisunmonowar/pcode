import serial

ser = serial.Serial()
ser.port= "/dev/ttyO4"
ser.baudrate = 9600
ser.bytesize = serial.EIGHTBITS
ser.parity = serial.PARITY_NONE
ser.stopbits = serial.STOPBITS_ONE
ser.timeout = 5
ser.xonxoff= True
ser.rtscts = False
ser.dsrdtr = False

ser.writeTimeout = 5

try:
        ser.open()
except Exception as e:
        print("error open Serial Port: " +str(e))
        exit()


if ser.isOpen():
        print("Serial is Open")
	loopLogic = True
        while(loopLogic):
		msg = ser.readline()
		msg_str = msg.decode()
		print(msg)
		if msg.find(b'\x06') != -1:
			print("06 Received")
		if (msg.find(b'you can stop') != -1):
			print("I can stop")
			loopLogic = False
else:
        print("Serial is not open")
ser.close()
print("end")
