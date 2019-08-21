#include <SPI.h>
#include <LoRa.h>

int counter = 0;

void setup() {
  LoRa.setPins(8,12,3);
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

}

void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);
  String msg = "HeLoRa World!";
  msg [3] = 'L';
  msg [5] = ' ';
  msg [4] = 'o';
  // send packet
  LoRa.beginPacket();
  LoRa.print(msg);
  //LoRa.print(counter);
  LoRa.endPacket();
  msg ="";
  counter++;

  delay(1000);
}
