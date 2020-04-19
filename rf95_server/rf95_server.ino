// rf95_server.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messageing server
// with the RH_RF95 class. RH_RF95 class does not provide for addressing or
// reliability, so you should only use RH_RF95  if you do not need the higher
// level messaging abilities.
// It is designed to work with the other example rf95_client
// Tested with Anarduino MiniWirelessLoRa, Rocket Scream Mini Ultra Pro with
// the RFM95W, Adafruit Feather M0 with RFM95

#include <SPI.h>
#include <RH_RF95.h>

#define MSG_TYPE_SIZE 3
#define DEVICE_ID_SIZE 12
#define COORDINATES_SIZE 32
#define GROUP_FLAG_SIZE 1
#define BYTE_SIZE 8

#define LAT_MIN  42900000
#define LNG_MIN 22380000

// Singleton instance of the radio driver
RH_RF95 rf95;
//RH_RF95 rf95(5, 2); // Rocket Scream Mini Ultra Pro with the RFM95W
//RH_RF95 rf95(8, 3); // Adafruit Feather M0 with RFM95 

// Need this on Arduino Zero with SerialUSB port (eg RocketScream Mini Ultra Pro)
//#define Serial SerialUSB

int extractField(uint8_t message_byte, unsigned position, unsigned fieldSize){ 
    return ((message_byte >> (position - 1)) & ((1 << fieldSize) - 1)); 
}
long decompress_coordinate(uint8_t coord1, uint8_t coord2, long offset){
  uint16_t coord;
  coord = coord1;
  coord <<= 8;
  coord += coord2;

  return ((coord + offset)*-1);
}

int led = 8;

void setup() 
{
  // Rocket Scream Mini Ultra Pro with the RFM95W only:
  // Ensure serial flash is not interfering with radio communication on SPI bus
//  pinMode(4, OUTPUT);
//  digitalWrite(4, HIGH);

  pinMode(led, OUTPUT);     
  Serial.begin(9600);
  while (!Serial) ; // Wait for serial port to be available
  if (!rf95.init())
    Serial.println("init failed");  
  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on

  // The default transmitter power is 13dBm, using PA_BOOST.
  // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then 
  // you can set transmitter powers from 5 to 23 dBm:
//  driver.setTxPower(23, false);
  // If you are using Modtronix inAir4 or inAir9,or any other module which uses the
  // transmitter RFO pins and not the PA_BOOST pins
  // then you can configure the power transmitter power for -1 to 14 dBm and with useRFO true. 
  // Failure to do that will result in extremely low transmit powers.
//  driver.setTxPower(14, true);
}

void loop()
{
  unsigned messageType;
  unsigned deviceID;
  double lat, lng;

  if (rf95.available())
  {
    // Should be a message for us now   
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    uint8_t groupFlag;
    
    if (rf95.recv(buf, &len))
    {
      digitalWrite(led, HIGH);
//      RH_RF95::printBuffer("request: ", buf, len);
      Serial.print("got request: ");
      Serial.println((char*)buf);


      messageType = extractField(buf[0], 1+GROUP_FLAG_SIZE+DEVICE_ID_SIZE-BYTE_SIZE, MSG_TYPE_SIZE);
      groupFlag = extractField(buf[0], 1+DEVICE_ID_SIZE-BYTE_SIZE, GROUP_FLAG_SIZE);
      deviceID = (extractField(buf[0], 1, DEVICE_ID_SIZE-BYTE_SIZE)<<8) + (unsigned)buf[1];
      lat = decompress_coordinate(buf[2], buf[3], LAT_MIN);
      lng = decompress_coordinate(buf[4], buf[5], LNG_MIN);

      Serial.print("Message Type: ");
      Serial.println(messageType);
      Serial.print("Group Flag: ");
      Serial.println(groupFlag);
      Serial.print("Device ID: ");
      Serial.println(deviceID);
      Serial.print("Latitude: ");
      Serial.println(lat);
      Serial.print("Longitude: ");
      Serial.println(lng);
      
      // Send a reply
      uint8_t data[] = "And hello back to you";
      rf95.send(data, sizeof(data));
      rf95.waitPacketSent();
      Serial.println("Sent a reply");
       digitalWrite(led, LOW);
    }
    else
    {
      Serial.println("recv failed");
    }
  }
  /*else 
  {
    Serial.println("rf95 not avaiable");
    
  }*/
}
