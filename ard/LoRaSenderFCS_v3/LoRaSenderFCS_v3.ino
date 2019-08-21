#define NRZI3_DATA_SIZE 250
#include <SPI.h>

unsigned long counter = 0;
String msg = "hello";
bool stringComplete = true;  // whether the string is complete
char i;


void setup() {
  msg.reserve(200);
  Serial.begin(9600);
  Serial.println("LoRa Sender");
}

void loop() {
  if (Serial.available() > 0)
  {
    msg = ""; //force overwrite buffer
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

    // send packet
    Serial.print("Sending");

    Serial.print("  :: ");
    Serial.println(msg);

    //try to make CRC
    Serial.print("msg length ");
    Serial.println( msg.length());
    unsigned char dataIndex = (unsigned char) msg.length();
    msg = mk_CRC(msg, dataIndex);
    Serial.print("with CRC");
    Serial.print("  ::");
    Serial.println(msg);
    Serial.print("new length ");
    Serial.println(msg.length());
    //--can we double check?
    String receivedString = mk_CRC(msg.substring(0, msg.length() - 2), (unsigned char)(msg.length() - 2));
    Serial.println(receivedString);
    if (receivedString == msg)
    {
      Serial.println("match");
    }
    else
    {
      Serial.println("nope");
    }
    stringComplete = false;
  }
}



String mk_CRC(String data, unsigned char data_number)
{
  unsigned int crcReg = 0xffff;   //set initial value of CRC
  unsigned int calc = 0x8408;      //X16+X12+X5+X0   multiplier corresponding to the CRC generating polynomial
  unsigned char w;            //stores the temporary data of CRC
  long i;                     //counts 8 bit data
  long k;                     //counts data bytes
  String cal_data;
  cal_data.reserve(NRZI3_DATA_SIZE);
  for (k = 0; k < data_number; k++)
  {
    cal_data[k] = data[k];   //data_copy

    //calculates CRC for one byte and outputs the result
    //loops eight times
    for (i = 0; i < 8; i++)
    {
      //takes exclusive OR of crcReg and data, and set the LS bit to w
      w = (crcReg ^ cal_data[k]) & 0x0001;

      //shift crcReg one bit to right and store the result to crcReg
      crcReg = crcReg >> 1;

      //if w is 1, take exclusive OR of crcReg and 0x8408 and store the result to crcReg
      if (w == 1)
      {
        crcReg = crcReg ^ calc;
      }

      //data is shifted right one bit
      cal_data[k] = cal_data[k] >> 1;
    }
  }

  //output reversal is on
  crcReg = crcReg ^ 0xffff;
  //cout << crcReg; //this is crc data (in binary). maisun. 160414. print out is in dec.

  //store in  the CRC check byte and the packet data


  //printf("\nCRC %Lu", crcReg);
  Serial.print("crc ");
  Serial.print(crcReg, HEX);
  data += (char)crcReg;
  data += (char)(crcReg >> 8); //exactly same as horyu4.

  //add 2 bytes of CRC check byte to the data number
  //data_number[0] = data_number[0] + 2;
  //  Serial.print(data[data_number - 1], HEX);
  //  Serial.print(data[data_number], HEX);
  //  Serial.print(data[data_number + 1], HEX);
  //  Serial.print(data[data_number + 2], HEX);
  return data;
}
