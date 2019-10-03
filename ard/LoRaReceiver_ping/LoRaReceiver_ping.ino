//use with LoRaSender_pint
//if something received via LoRa, just give the feedback

#include <SPI.h>
#include <LoRa.h>

String msg, feedback, beagleMsg;
unsigned long counter;
boolean msgReceived, lineWritten, stringComplete;


void setup() 
{
  Serial.begin(9600);
  while (!Serial);
  Serial.println("LoRa Receiver");

  
  LoRa.setPins(8, 12, 3);
  //LoRa.setPins(4,7,2);
  if (!LoRa.begin(433E6))
  {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.setSpreadingFactor(8);
  LoRa.setSignalBandwidth(62.5E3);
  LoRa.enableCrc();
  //LoRa.setCodingRate4(8);
  //LoRa.setPreambleLength(6);

  msgReceived = false;
  lineWritten = false;
  stringComplete = false;
}


void loop()
{
  listenRadio();
}

void send_feedback()
 
  {
    //--send feedback to GS
    feedback = msg[0] + msg[1] + msg[2] + msg[3];

    LoRa.beginPacket();
    LoRa.print(feedback);
    LoRa.endPacket();
    Serial.println("Feedback::" + feedback);
    LoRa.receive();

    //clear string
    msg = "";
    // print RSSI of packet
    //Serial.print("' with RSSI ");
    //Serial.println(LoRa.packetRssi());
    lineWritten = false;
  }

void  listenRadio()
{
    // try to parse packet
  int packetSize = LoRa.parsePacket();

  if (packetSize)
  {
    
    msg = ""; //must clear buffer for the new packet
    // received a packet
    msgReceived = true;
    //Serial.print("Received packet ");
    // read packet
    while (LoRa.available())
    {
      msg += (char)LoRa.read();
    }
    Serial.print("Received: ");
    Serial.print("Received packet '");
    send_feedback();
  }
}
