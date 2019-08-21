#include <SPI.h>
#include <LoRa.h>

String msg, feedback, beagleMsg;
unsigned long counter;
boolean msgReceived, lineWritten, stringComplete, beagleUnderstood, feedbackSent, waitingNewRadio, uartWaiting;


void setup()
{
  msgReceived = false;
  lineWritten = false;
  stringComplete = false;
  feedbackSent = false;
  waitingNewRadio = true;

  Serial.begin(9600);
  LoRa.setPins(8, 12, 3);

  while (!Serial);
  Serial.println("LoRa Receiver");

  if (!LoRa.begin(433E6))
  {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  LoRa.setSpreadingFactor(8);
  LoRa.setSignalBandwidth(62.5E3);
  LoRa.enableCrc();
}


void loop()
{
  if (waitingNewRadio)
  {
    listenLora();
  }

  if (msgReceived)
  {
    waitingNewRadio = false;

//    //Packet Number calculation
//    counter = (unsigned long)msg[0];
//    counter = counter << 7;
//
//    counter += (unsigned long)msg[1];
//    counter = counter << 7;
//
//    counter += (unsigned long)msg[2];
//    counter = counter << 7;
//
//    counter += (unsigned long)msg[3];

    tellBeagle();
    
  }
    if (uartWaiting)
    {
      listenBeagle();
    if (beagleUnderstood )
    {
      sendFeedback();
      beagleUnderstood = false;
    }
    else
    {
      tellBeagle();
    }
    }
}



void tellBeagle()
{
  beagleUnderstood = false;
  uartWaiting = true;
  Serial.println(msg);
  delay(300);
}

void listenBeagle()
{
  Serial.println("listen beagle");
  if (Serial.available() > 0)
  {
    beagleMsg = ""; //force overwrite buffer

    while (Serial.available())
    {
      // get the new byte:
      char inChar = (char)Serial.read();

      if (inChar == '\n' || inChar == '\r' )
      {
        stringComplete = true;
        uartWaiting = false;
        Serial.print("beagle::  ");
        Serial.println(beagleMsg);
        beagleUnderstood = beagleMsg == msg;
      }
      else
      {
        beagleMsg += inChar;
      }
    }
  }
  else 
  {
    delay(50);
  }
}

void sendFeedback()
{
  //--send feedback to GS
  Serial.println("send feedback");
  feedback = msg[0] + msg[1] + msg[2] + msg[3];

  LoRa.beginPacket();
  LoRa.print(feedback);
  LoRa.endPacket();
  LoRa.receive();

  //clear string
  msg = "";
  feedbackSent = true;
  waitingNewRadio = true;
  msgReceived = false;
  uartWaiting = false;
}

void listenLora()
{
  Serial.println("listen lora");
  // try to parse packet
  int packetSize = LoRa.parsePacket();

  if (packetSize)
  {
    msg = ""; //must clear buffer for the new packet
    // received a packet
    msgReceived = true;
    feedbackSent = false;
    waitingNewRadio = false;
    // read packet
    while (LoRa.available())
    {
      msg += (char)LoRa.read();
    }
  }
}
