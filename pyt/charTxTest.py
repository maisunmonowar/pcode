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
    o = "hello serial port\n\r"
    o_out = o.encode()
    ser.write(o_out)
    for x in range(10):
       ser.write(b'\x06')
    ser.write(o_out)
    youcan = "you can stop\n\r"
    ser.write(youcan.encode())
else:
    print("Serial is not open")
ser.close()
print("End")