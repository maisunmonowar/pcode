#include <SPI.h>
#include <LoRa.h>

unsigned long counter = 0;
String msg = "HeLoRa World!111111222222222234444444445";
String inputString = "";         // a String to hold incoming data
bool stringComplete = true;  // whether the string is complete
char i;

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

}

void loop() {
  if (Serial.available() > 0)
  {
    i = 4;
    while (Serial.available()) {
      // get the new byte:
      char inChar = (char)Serial.read();

      if (inChar == '\n') {
        stringComplete = true;
      }
      else
      {
        msg[i] = inChar;
      }
      i++;
    }
  }
  if (stringComplete)
  {
    //Packet counter
    msg [3] = (char)(counter % 128);
    Serial.print(msg[3],HEX);
    msg [2] = (char)((counter >> 7) % 128);
    Serial.print("  ");
    Serial.println(msg[2],HEX);
    msg [1] = (char)((counter >> 14) % 128);
    msg [0] = (char)((counter >> 21) % 128);

    // send packet
    Serial.print("Sending packet: ");
    Serial.print(counter);
    Serial.print("  ::");
    Serial.println(msg);

    LoRa.beginPacket();
    LoRa.print(msg);
    //LoRa.print(counter);
    LoRa.endPacket();

    counter++;
    stringComplete = false;
    msg = "                                        ";
  }
}
