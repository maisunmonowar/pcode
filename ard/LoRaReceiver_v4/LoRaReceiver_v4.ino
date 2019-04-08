#include <SPI.h>
#include <LoRa.h>

String msg, feedback;
unsigned long counter;
void setup() {
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

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    //Serial.print("Received packet '");
    // read packet
    while (LoRa.available()) {
      msg += (char)LoRa.read();
    }
    //Packet Number
    counter = (unsigned long)msg[0];
    counter = counter << 7;

    counter += (unsigned long)msg[1];
    counter = counter << 7;

    counter += (unsigned long)msg[2];
    counter = counter << 7;

    counter += (unsigned long)msg[3];

    //--do string operation
    //Serial.print("counter: ");
    //Serial.print(counter);
    //Serial.print("    ::");
    Serial.println(msg);

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
  }
}
