/*
  Serial Call and Response
  Language: Wiring/Arduino

  This program sends an ASCII A (byte of value 65) on startup and repeats that
  until it gets some data in. Then it waits for a byte in the serial port, and
  sends three sensor values whenever it gets a byte in.

  The circuit:
  - potentiometers attached to analog inputs 0 and 1
  - pushbutton attached to digital I/O 2

  created 26 Sep 2005
  by Tom Igoe
  modified 24 Apr 2012
  by Tom Igoe and Scott Fitzgerald
  Thanks to Greg Shakar and Scott Fitzgerald for the improvements

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/SerialCallResponse
*/
void setup() 
{
   Serial2.begin(1200);
   pinMode(53, INPUT);   // digital sensor is on digital pin 2
}

void loop() 
{
  if(!digitalRead(53))
  {
    Serial.write(0xFE);
    Serial.write(0xFD);
  } 
}
