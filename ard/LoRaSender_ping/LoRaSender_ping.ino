//use it with LoRaReceiver_ping
//sender sends a fixed string
//when receiver receives, it sends a feedback
//Feedback is shown via serial

#include <SPI.h>
#include <LoRa.h>

unsigned long counter = 0;
unsigned long lastSendTime, receiveTime, feedbackTimeout;
char i;
String msg = "HeLoRa World!111111222222222234444444445";
String inputString = "";         // a String to hold incoming data
bool stringComplete = true;  // whether the string is complete
bool lastPacketSuccess;

void setup() {
  Serial.begin(9600);
  Serial.println("LoRa Sender");

  LoRa.setPins(8, 12, 3);
  if (!LoRa.begin(433E6)) 
  {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.setSpreadingFactor(8);
  LoRa.setSignalBandwidth(62.5E3);
  LoRa.enableCrc();
  // LoRa.setCodingRate4(8);
  // LoRa.setPreambleLength(6);
  
  feedbackTimeout = 5000; //set feedback timeout to 5 seconds
  lastSendTime = 0;
  receiveTime = 0;
}

void loop() 
{
  send_msg();
  receiveFeedback();
}


void receiveFeedback()
{
  int packetSize = LoRa.parsePacket();
  if (packetSize == 0)
  {
    
    return;          // if there's no packet, return
  }
  Serial.println("Receiving");
  String incoming = "";                 // payload of packet

  while (LoRa.available()) {            // can't use readString() in callback, so
    incoming += (char)LoRa.read();      // add bytes one by one
  }
  receiveTime = millis();
  Serial.println("Feedback::" + incoming);
  //Serial.print("Round trip:: ");
  //Serial.println((receiveTime - lastSendTime));
}

void send_msg()
{  
    Serial.println("Sending Msg");
    LoRa.beginPacket();
    LoRa.print(msg);
    //LoRa.print(counter);
    LoRa.endPacket();
    lastSendTime = millis();            // timestamp the message
    LoRa.receive();
}
