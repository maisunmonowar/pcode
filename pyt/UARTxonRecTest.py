import serial
import time
ser = serial.Serial('COM5', baudrate = 9600, timeout = 5, xonxoff=True)

try:
		ser.open()
except Exception as e:
		print("error opening Serial Port: " + str(e))
		exit()

if: ser.isOpen():
	while(True):
		rBuffer = ser.readline()
		msg = rBuffer.decode()
		print(msg)
		if(msg[len(msg)-1:len(msg)] == "\""):
			break
else:
	print("Serial is not open")
ser.close()
print("End")
'''
x = 0
msg = 'this is a message.'
msg += '\n'
if ser.isOpen():
    ser.close()
ser.open()


nameOfFile = "testTransfer.cpp"
modeOfFile = "w+"

file = open(nameOfFile, "r")

#count execution time
startTime = time.time()
#--Command satellite to open a file
time.sleep(1)
msg = ''
msg += 'gsToBIRDcommand'
msg += 'nameOfFile'
msg += nameOfFile
msg += '\n'
print(msg)
ser.write(msg.encode())
#--wait for ok signal to send next command
feedback = ser.readline()
while len(feedback) <= 2:
	feedback = ser.readline()
feedback2 = feedback[0:22] #This is still a byte obj
feedback3 = feedback2.decode() #Feedback3 is now a string
print(feedback3)
while feedback3 != 'Procceed with the next':
	feedback = ser.readline()
	feedback2 = feedback[0:22] #This is still a byte obj
	feedback3 = feedback2.decode() #Feedback3 is now a string
	print(feedback3)
#--now send mode command
time.sleep(2)
#absence of delay sometimes 
#sends two line at same time
#need to investigate later
msg = ''
msg += 'gsToBIRDcommand'
msg += 'modeOfFile'
msg += 'w+'
msg += '\n'
print(msg)
ser.write(msg.encode())
#--wait for ok signal to send next command
feedback = ser.readline()
while len(feedback) <= 2:
	feedback = ser.readline()
feedback2 = feedback[0:22] #This is still a byte obj
feedback3 = feedback2.decode() #Feedback3 is now a string
print(feedback3)
while feedback3 != 'Procceed with the next':
	feedback = ser.readline()
	feedback2 = feedback[0:22] #This is still a byte obj
	feedback3 = feedback2.decode() #Feedback3 is now a string
	print(feedback3)
time.sleep(1)
#absence of delay sometimes 
#sends two line at same time
#need to investigate later

#--Send the file
x = 0
while x < 5000:
	#I know limiting the line size to 
	#5000 is stupid
	#will fix later
	msg = 'data'
	msg += file.readline()
	msg += '\n'
	print(msg)
	ser.write(msg.encode())
	
	time.sleep(.1)
	#absence of delay sometimes 
	#sends two line at same time
	#need to investigate later
	feedback = ser.readline()
	while len(feedback) <= 2:
		feedback = ser.readline()
	feedback2 = feedback[0:22] #This is still a byte obj
	feedback3 = feedback2.decode() #Feedback3 is now a string
	print(feedback3)
	while feedback3 != 'Procceed with the next':
		feedback = ser.readline()
		feedback2 = feedback[0:22] #This is still a byte obj
		feedback3 = feedback2.decode() #Feedback3 is now a string
		print(feedback3)
	##--Detect End of File
	if msg[9:18] == 'endOfFile':
		break	
	x+=1

#Tell satellite to close the file
time.sleep(1)
msg = ''
msg += 'gsToBIRDcommand'
msg += 'endOfFile'
msg += '\n'
print(msg)
ser.write(msg.encode())	
#--GS work is done. Close and exit
file.close()
ser.close()
#count execution time
endTime = time.time()
print ("Process took")
print(endTime - startTime)
 '''