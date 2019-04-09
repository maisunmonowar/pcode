#include <SPI.h>
#include <LoRa.h>

String msg, feedback, beagleMsg;
unsigned long counter;
boolean msgReceived, waitingRadio, waitingUart, beagleUnderstood, stringComplete, feedbackSent;
void setup() {

  msgReceived = false;
  waitingRadio = true;
  waitingUart = false;
  beagleUnderstood = false;
  stringComplete = false;
  feedbackSent = false;

  Serial.begin(9600);
  LoRa.setPins(8, 12, 3);

  //LoRa.setPins(4,7,2);
  while (!Serial);

  Serial.println("LoRa Receiver");

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.setSpreadingFactor(8);
  LoRa.setSignalBandwidth(62.5E3);
  LoRa.enableCrc();
  //LoRa.setCodingRate4(8);
  //LoRa.setPreambleLength(6);
}

void loop()
{
  if (waitingRadio)
  {
    listenLora();
  }

  if (msgReceived)
  {
    tellBeagle();
  }

  if (waitingUart)
  {
    listenBeagle();
  }

  if (stringComplete)
  {
    if (beagleUnderstood)
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

void listenBeagle()
{
  counter = 3;
  while (Serial.available() == 0 && counter > 2)
  {
    counter++;
  }
  if (Serial.available() > 0)
  {
    beagleMsg = ""; //force overwrite buffer

    while (Serial.available()) {
      // get the new byte:
      char inChar = (char)Serial.read();

      if (inChar == '\n') {
        stringComplete = true;
        waitingUart = false;
        beagleUnderstood = beagleMsg == "ok";
      }
      else
      {
        beagleMsg += inChar;
      }
    }
  }
  else
  {
    delay(120);
  }
}

void tellBeagle()
{
  Serial.println(msg);
  waitingUart = true;
  beagleUnderstood = false;
}


void listenLora()
{
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize)
  {
    // received a packet
    msg = "";
    //Serial.print("Received packet '");
    // read packet
    while (LoRa.available())
    {
      msg += (char)LoRa.read();
    }
    msgReceived = true;
    feedbackSent = false;
  }
}

void sendFeedback()
{
  //--send feedback to GS
  feedback = msg[0] + msg[1] + msg[2] + msg[3];

  LoRa.beginPacket();
  LoRa.print(feedback);
  LoRa.endPacket();
  //Serial.println("Feedback::" + feedback);
  LoRa.receive();
  feedbackSent = true;
  waitingRadio = true;
  waitingUart = false;
  stringComplete = false;
  msgReceived = false;
}
