#include <SPI.h>


String msg, feedback, beagleMsg;
unsigned long counter;
boolean msgReceived, lineWritten, stringComplete, beagleUnderstood, feedbackSent;


void setup() {
  msgReceived = false;
  lineWritten = false;
  stringComplete = false;
  counter = 0;
  msg = "First Message";
  Serial.begin(9600);

  while (!Serial);
  Serial.println("LoRa Receiver");

}


void loop()
{
  delay(5000);//because I'm dumb & and this is a test loop
  //wait for msg
  
  //parse msg
  //tell beagle the msg
  tellBeagle();

  //receive feedback from beagle
  listenBeagle();

  //if beagle understood, send feedback (since this is test program, also change message)
  if (beagleUnderstood)
  {
    Serial.println("Beagle Understood");
    sendFeedback();
    changeMessage();
    beagleUnderstood = false;
  }
  //if beagle didn't understood, tell beagle again
  else
  {
    tellBeagle();
  }
}


void tellBeagle()
{
  Serial.println(msg);
}

void listenBeagle()
{
  if (Serial.available() > 0)
  {
    beagleMsg = ""; //force overwrite buffer

    while (Serial.available())
    {
      // get the new byte:
      Serial.println("serial available");
      char inChar = (char)Serial.read();

      if (inChar == '\n' || inChar == '\r' )
      {
        stringComplete = true;
        Serial.print("BEAGLE:: ");
        Serial.println(beagleMsg);
        beagleUnderstood = beagleMsg == msg;
      }
      else
      {
        beagleMsg += inChar;
      }
    }
  }
}

void changeMessage()
{
        Serial.println("change");
  counter ++;
  msg = counter + "the new message";
      Serial.println(msg);
}
void sendFeedback()
{
  Serial.println("FEEDBACK");
  feedbackSent = true;
}
