import os

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
for x in range(len(lineList)):
    print(lineList[x])
    outputFile.write(lineList[x])
file.close()
outputFile.close()
