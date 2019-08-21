#include <SPI.h>
#include <LoRa.h>

String msg, feedback, beagleMsg;
unsigned long counter;
boolean msgReceived, lineWritten, stringComplete;


void setup() {
  msgReceived = false;
  lineWritten = false;
  stringComplete = false;

  Serial.begin(9600);
  LoRa.setPins(8, 12, 3);
  //LoRa.setPins(4,7,2);

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
  //LoRa.setCodingRate4(8);
  //LoRa.setPreambleLength(6);
}


void loop()
{
  // try to parse packet
  int packetSize = LoRa.parsePacket();

  if (packetSize)
  {
    msg = ""; //must clear buffer for the new packet
    // received a packet
    msgReceived = true;
    //Serial.print("Received packet '");
    // read packet
    while (LoRa.available())
    {
      msg += (char)LoRa.read();
    }
  }
  //--do string operation
  //Serial.print("counter: ");
  //Serial.print(counter);
  //Serial.print("    ::");

  if (msgReceived)
  {
    //Packet Number
    counter = (unsigned long)msg[0];
    counter = counter << 7;

    counter += (unsigned long)msg[1];
    counter = counter << 7;

    counter += (unsigned long)msg[2];
    counter = counter << 7;

    counter += (unsigned long)msg[3];

    Serial.println(msg);
    msgReceived = false;
  }

  if (Serial.available() > 0)
  {
    beagleMsg = ""; //force overwrite buffer

    while (Serial.available())
    {
      // get the new byte:
      char inChar = (char)Serial.read();

      if (inChar == '\n')
      {
        stringComplete = true;
      }
      else
      {
        beagleMsg += inChar;
      }
    }
    if ( beagleMsg == msg && stringComplete)
    {
      lineWritten = true;
      stringComplete = false;
    }
    else
    {
      //beagle somehow didn't get the last message
      //resend beagle
      Serial.println(msg);
    }
  }

  if (lineWritten)
  {
    //--send feedback to GS
    feedback = msg[0] + msg[1] + msg[2] + msg[3];

    LoRa.beginPacket();
    LoRa.print(feedback);
    LoRa.endPacket();
    //Serial.println("Feedback::" + feedback);
    LoRa.receive();

    //clear string
    msg = "";
    // print RSSI of packet
    //Serial.print("' with RSSI ");
    //Serial.println(LoRa.packetRssi());
    lineWritten = false;
  }
}
