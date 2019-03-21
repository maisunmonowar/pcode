#include <SPI.h>
#include <LoRa.h>

String msg;
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
  LoRa.setSpreadingFactor(9);
  LoRa.setSignalBandwidth(41.25E3);
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
    counter = msg[0];
    counter = counter << 8;

    counter += msg[1];
    counter = counter << 8;

    counter += msg[2];
    counter = counter << 8;

    counter += msg[3];
    //do string operation
    Serial.print("counter: ");
    Serial.print(counter);
    Serial.print("    ::");
    Serial.println(msg);
    //clear string
    msg = "";
    // print RSSI of packet
    //Serial.print("' with RSSI ");
    //Serial.println(LoRa.packetRssi());
  }
}
