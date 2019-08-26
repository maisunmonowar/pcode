import serial
import time
import os

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

nameOfFile = "test.hex"
modeOfFile = "w+"
script_dir = os.path.dirname(__file__)  # <-- absolute dir the script is in
rel_path = "../ard/" + nameOfFile
abs_file_path = os.path.join(script_dir, rel_path)
outputFile = open("outputFile.hex", "w+")
with open(abs_file_path, "r") as file:
    lineList = file.readlines()
print("list loading done.\n\r")
print("Number of lines: ")
print(len(lineList))
print("\n\r\n\rThey are:\n\r")


try:
        ser.open()
except Exception as e:
        print("error open Serial Port: " +str(e))
        exit()


if ser.isOpen():
        print("Serial is Open")
        ser.write("Hello Serial Port")
        for x in range(len(lineList)):
    		print(lineList[x])
    		ser.write(lineList[x])
    		outputFile.write(lineList[x])
else:
        print("Serial is not open")
ser.close()
file.close()
outputFile.close()
print("end")