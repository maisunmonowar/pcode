#import os
#myCmd = "certutil -hashfile appv4.hex md5"# >> appv4hash.txt"
#lineList = os.system(myCmd)
#print(lineList)

import subprocess

filename = input("Which file? eg. appv4.hex...\n\r")
out = subprocess.Popen(['md5sum', filename], stdout = subprocess.PIPE, stderr = subprocess.STDOUT)
stdout, stderr = out.communicate()

print(stdout)
print(stderr)

if out.stderr is None:
	md5Checksum = stdout[:32]
	print(md5Checksum)
	outputFileName = filename[:-4] + "Hash" + ".txt"
	outputFile = open(outputFileName, "w+")
	outputFile.write("MD5")
	outputFile.write("\x0D")
	outputFile.write(filename)
	outputFile.write("\x0D")
	outputFile.write(md5Checksum)
	outputFile.close()
else:
	print("oopps")
