msg = b'can\n'
print(msg)
msg2 = msg.decode()
filename = "rec.txt"
mode = "w+"
file = open(filename, mode)
file.write(msg2)
file.write("hello")
file.write("World")
file.write("\n")
file.write("Konnichiwa")
file.close()