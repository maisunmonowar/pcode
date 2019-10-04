#import os
#myCmd = "certutil -hashfile appv4.hex md5"# >> appv4hash.txt"
#lineList = os.system(myCmd)
#print(lineList)

import subprocess

filename = input("Which file? eg. appv4.hex...\n\r")
out = subprocess.Popen(['certutil', '-hashfile', filename, 'md5'], stdout = subprocess.PIPE, stderr = subprocess.STDOUT)
stdout, stderr = out.communicate()

print(stdout)
print(stderr)

if stdout.find(b'successfully') != -1:
	firstPointer = stdout.find(b'hex')
	md5Checksum = stdout[firstPointer+6:firstPointer+6+32]
	print(md5Checksum)
	outputFileName = filename[:-4] + "Hash" + ".txt"
	outputFile = open(outputFileName, "w+")
	hashType = stdout[:4]
	outputFile.write(hashType.decode())
	outputFile.write("\x0D")
	outputFile.write(filename)
	outputFile.write("\x0D")
	outputFile.write(md5Checksum.decode())
	outputFile.close()
else:
	print("oopps")