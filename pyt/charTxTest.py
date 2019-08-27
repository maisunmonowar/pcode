import serial
import time
ser = serial.Serial('COM5', baudrate = 9600, timeout = 5, xonxoff=True)

if ser.isOpen():
    #do nothing
    print("Serial is open")
else:
    try:
            ser.open()
    except Exception as e:
            print("error opening Serial Port: " + str(e))
            exit()

if ser.isOpen():
    for x in range(5):
        ser.write(0x06)
    ser.write("you can stop\n\r")
else:
    print("Serial is not open")
ser.close()
print("End")