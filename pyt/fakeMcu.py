#import every thing necessary
import serial
import time
import os

#open 2 files
pcData = open("pcData.txt", "w+")
mcuData = open("mcuData.txt", "w+")
#open Serial
uart4 = serial.Serial()
uart4.port= "/dev/ttyO4"
uart4.baudrate = 9600
uart4.bytesize = serial.EIGHTBITS
uart4.parity = serial.PARITY_NONE
uart4.stopbits = serial.STOPBITS_ONE
uart4.timeout = 1
uart4.xonxoff= False
uart4.rtscts = False
uart4.dsrdtr = False
uart4.writeTimeout = 5

uart1 = serial.Serial()
uart1.port = "/dev/ttyO1"
uart1.baudrate = 9600
uart1.bytesize = serial.EIGHTBITS
uart1.parity = serial.PARITY_NONE
uart1.stopbits = serial.STOPBITS_ONE
uart1.timeout = 1
uart1.xonxoff= False
uart1.rtscts = False
uart1.dsrdtr = False
uart1.writeTimeout = 5

try:
        uart4.open()
except Exception as e:
        print("error open Serial Port: " +str(e))
        #GPIO.output(LED, GPIO.HIGH) #Normally needs to be high
        pcData.close()
	mcuData.close()
	#GPIO.cleanup()
        exit()

try:
        uart1.open()
except Exception as e:
        print("error open Serial Port: " +str(e))
        #GPIO.output(LED, GPIO.HIGH) #Normally needs to be high
        pcData.close()
	mcuData.close()
	#GPIO.cleanup()
        exit()

#do the work
if uart4.isOpen() and uart1.isOpen():
	print("Start")
	
	timeout = 0
	pc = 0
	#mcu = 0
	dataFromPc = ["begin"]
	dataFromMcu = ["begin"]
	startTime = time.time()
	while True:#timeout <30000:
		if uart1.inWaiting() > 0:
			msg = uart1.readline()
			uart1.write(b'\x13')
			mcuData.write(msg)
			uart1.write(b'\x06')
			uart1.write(b'\x11')
			#dataFromMcu.append(msg)
			#mcu += 1
			#timeout = 0
#			print(msg)
			#startTime = time.time()
		#if time.time()-startTime  > 30:
		#	break
		#timeout += 1
		#time.sleep(0.001)

#write to file
#mcuData.write("Begin\n\r")
#pcData.write("Begin\n\r")
#for x in range(len(dataFromMcu)):
#	mcuData.write(dataFromMcu[x])
#for y in range(len(dataFromPc)):
#	pcData.write(dataFromPc[x])

#cleanup
uart4.close()
uart1.close()
pcData.close()
mcuData.close()
#count execution time
#endTime = time.time()
print("end")
