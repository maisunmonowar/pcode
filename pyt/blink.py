import Adafruit_BBIO.GPIO as GPIO
import time

LED="P9_12"
GPIO.setup(LED, GPIO.OUT)

for x in range(5):
	GPIO.output(LED, GPIO.HIGH)
	print("High")
	time.sleep(1)
	GPIO.output(LED, GPIO.LOW)
	print("Low")
	time.sleep(1)
GPIO.cleanup()	
print("End")