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
        while(True):
            msg = ser.readline()
            print(str(msg))
            if msg == 0x06:
                print("06 Received")
            if str(msg) == "you can stop\n\r"
                print("I can stop")
                break
else:
        print("Serial is not open")
ser.close()
print("end")