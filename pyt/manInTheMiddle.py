#import every thing necessary
import serial
import time
import os

#open Serial
uart4 = serial.Serial()
uart4.port= "/dev/ttyO4"
uart4.baudrate = 9600
uart4.bytesize = serial.EIGHTBITS
uart4.parity = serial.PARITY_NONE
uart4.stopbits = serial.STOPBITS_ONE
uart4.timeout = 1
uart4.xonxoff= True
uart4.rtscts = False
uart4.dsrdtr = False
uart4.writeTimeout = 1

uart1 = serial.Serial()
uart1.port = "/dev/ttyO1"
uart1.baudrate = 9600
uart1.bytesize = serial.EIGHTBITS
uart1.parity = serial.PARITY_NONE
uart1.stopbits = serial.STOPBITS_ONE
uart1.timeout = 1
uart1.xonxoff= True
uart1.rtscts = False
uart1.dsrdtr = False
uart1.writeTimeout = 1

try:
        uart4.open()
except Exception as e:
        print("error open Serial Port: " +str(e))
        GPIO.output(LED, GPIO.HIGH) #Normally needs to be high
        file.close()
	GPIO.cleanup()
        exit()

try:
        uart1.open()
except Exception as e:
        print("error open Serial Port: " +str(e))
        GPIO.output(LED, GPIO.HIGH) #Normally needs to be high
        file.close()
	GPIO.cleanup()
        exit()

#do the work
if uart4.isOpen() and uart1.isOpen():
	uart4.write(b'a')
	print("in waiting, " + str(uart1.in_waiting()))
	print(uart1.readline())

	uart4.write(b'b\x0D\x0A')
	print("in waiting, " + str(uart1.in_waiting()))
	print(uart1.readline())

	uart4.write("c")
	print("in waiting, " + str(uart1.in_waiting()))
	print(uart1.readline())


#cleanup
uart4.close()
uart1.close()
file.close()
GPIO.cleanup()
#count execution time
#endTime = time.time()
print("end")
