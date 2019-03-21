#include <SPI.h>
#include <LoRa.h>

unsigned long counter = 0;
String msg = "HeLoRa World!111111222222222234444444445";
String inputString = "";         // a String to hold incoming data
bool stringComplete = true;  // whether the string is complete
bool lastPacketSuccess;
char i;
unsigned long lastSendTime, receiveTime, feedbackTimeout;

void setup() {
  LoRa.setPins(8, 12, 3);
  Serial.begin(9600);
  Serial.println("LoRa Sender");
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.setSpreadingFactor(9);
  LoRa.setSignalBandwidth(41.25E3);
  // LoRa.setCodingRate4(8);
  // LoRa.setPreambleLength(6);
  feedbackTimeout = 5000; //set feedback timeout to 5 seconds
  lastSendTime = 0;
  receiveTime = 0;
}

void loop() {
  if (Serial.available() > 0)
  {
    counter++;
    msg = ""; //force overwrite buffer
    msg = "ffff";
    while (Serial.available()) {
      // get the new byte:
      char inChar = (char)Serial.read();

      if (inChar == '\n') {
        stringComplete = true;
      }
      else
      {
        msg += inChar;
      }
    }
  }


  if (stringComplete)
  {
    //Packet counter
    msg [3] = (char)(counter % 128);
    //Serial.print(msg[3], HEX);
    msg [2] = (char)((counter >> 7) % 128);
    //Serial.print("  ");
    //Serial.println(msg[2], HEX);
    msg [1] = (char)((counter >> 14) % 128);
    msg [0] = (char)((counter >> 21) % 128);

    // send packet
    //Serial.print("Sending packet: ");
    //Serial.print(counter);
    //Serial.print("  ::");
    //Serial.println(msg);

    LoRa.beginPacket();
    LoRa.print(msg);
    //LoRa.print(counter);
    LoRa.endPacket();
    lastSendTime = millis();            // timestamp the message
    LoRa.receive();

    lastPacketSuccess = false;
    stringComplete = false;
    //msg = "                                        ";

  }


  receiveFeedback();

  //--what if no feed back is received for long time
  //--Send the last packet again
  if (  (millis() - lastSendTime) > feedbackTimeout  &&  !lastPacketSuccess  )
  {
    //Serial.print("Timeout:: ");
    //Serial.println(millis() - lastSendTime);
    stringComplete = true;
  }

}


void receiveFeedback()
{
  int packetSize = LoRa.parsePacket();
  if (packetSize == 0) return;          // if there's no packet, return

  String incoming = "";                 // payload of packet

  while (LoRa.available()) {            // can't use readString() in callback, so
    incoming += (char)LoRa.read();      // add bytes one by one
  }
  receiveTime = millis();
  Serial.println("Feedback::" + incoming);
  //Serial.print("Round trip:: ");
  //Serial.println((receiveTime - lastSendTime));

  //reSend
  String sentStr;
  sentStr = msg[0] + msg[1] + msg[2] + msg[3];
  if ( sentStr != incoming) //did the feedback differnet from sent??
  {
    LoRa.beginPacket();
    LoRa.print(msg);
    //LoRa.print(counter);
    LoRa.endPacket();
    lastSendTime = millis();            // timestamp the message
    LoRa.receive();
  }
  else
  {
    lastPacketSuccess = true;
    Serial.println("Procceed with the next packet");
  }
}
