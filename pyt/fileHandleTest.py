# import serial
import time
import os

# ser = serial.Serial('COM8', baudrate=9600, timeout=1)
# x = 0
msg = 'this is a message\n.'

# if ser.isOpen():
#    ser.close()
# ser.open()

# nameOfFile = "testTransfer.cpp"
nameOfFile = "test.txt"
modeOfFile = "w+"

script_dir = os.path.dirname(__file__)  # <-- absolute dir the script is in
rel_path = "../ard/" + nameOfFile
abs_file_path = os.path.join(script_dir, rel_path)
# file = open(abs_file_path, "r")
outputFile = open("outputFile.txt", "w+")
with open(abs_file_path, "r") as file:
    lineList = file.readlines()

print("list loading done.\n\r")
print("Number of lines: ")
print(len(lineList))
print(type(lineList))
print(type(lineList[1]))
print("\n\r\n\rThey are:\n\r")
for x in range(len(lineList)):
    print(lineList[x])
    outputFile.write(lineList[x])
file.close()
outputFile.close()
print("End")
