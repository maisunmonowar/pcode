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
print("\n\r\n\rThey are:\n\r")
for x in range(len(lineList)):
    print(lineList[x])
    outputFile.write(lineList[x])
file.close()
outputFile.close()
'''















# count execution time
startTime = time.time()
# --Command satellite to open a file
time.sleep(1)
msg = ''
msg += 'gsToBIRDcommand'
msg += 'nameOfFile'
msg += nameOfFile
msg += '\n'
print(msg)
ser.write(msg.encode())
# --wait for ok signal to send next command
feedback = ser.readline()
while len(feedback) <= 2:
    feedback = ser.readline()
feedback2 = feedback[0:22]  # This is still a byte obj
feedback3 = feedback2.decode()  # Feedback3 is now a string
print(feedback3)
while feedback3 != 'Procceed with the next':
    feedback = ser.readline()
    feedback2 = feedback[0:22]  # This is still a byte obj
    feedback3 = feedback2.decode()  # Feedback3 is now a string
    print(feedback3)
# --now send mode command
time.sleep(2)
# absence of delay sometimes
# sends two line at same time
# need to investigate later
msg = ''
msg += 'gsToBIRDcommand'
msg += 'modeOfFile'
msg += 'w+'
msg += '\n'
print(msg)
ser.write(msg.encode())
# --wait for ok signal to send next command
feedback = ser.readline()
while len(feedback) <= 2:
    feedback = ser.readline()
feedback2 = feedback[0:22]  # This is still a byte obj
feedback3 = feedback2.decode()  # Feedback3 is now a string
print(feedback3)
while feedback3 != 'Procceed with the next':
    feedback = ser.readline()
    feedback2 = feedback[0:22]  # This is still a byte obj
    feedback3 = feedback2.decode()  # Feedback3 is now a string
    print(feedback3)
time.sleep(1)
# absence of delay sometimes
# sends two line at same time
# need to investigate later

# --Send the file
x = 0
while x < 5000:
    # I know limiting the line size to
    # 5000 is stupid
    # will fix later
    msg = 'data'
    msg += file.readline()
    msg += '\n'
    print(msg)
    ser.write(msg.encode())

    time.sleep(.1)
    # absence of delay sometimes
    # sends two line at same time
    # need to investigate later
    feedback = ser.readline()
    while len(feedback) <= 2:
        feedback = ser.readline()
    feedback2 = feedback[0:22]  # This is still a byte obj
    feedback3 = feedback2.decode()  # Feedback3 is now a string
    print(feedback3)
    while feedback3 != 'Procceed with the next':
        feedback = ser.readline()
        feedback2 = feedback[0:22]  # This is still a byte obj
        feedback3 = feedback2.decode()  # Feedback3 is now a string
        print(feedback3)
    ##--Detect End of File
    if msg[9:18] == 'endOfFile':
        break
    x += 1

# Tell satellite to close the file
time.sleep(1)
msg = ''
msg += 'gsToBIRDcommand'
msg += 'endOfFile'
msg += '\n'
print(msg)
ser.write(msg.encode())
# --GS work is done. Close and exit
file.close()
ser.close()
# count execution time
endTime = time.time()
print("Process took")
print(endTime - startTime)
'''
