// rf95_client.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messageing client
// with the RH_RF95 class. RH_RF95 class does not provide for addressing or
// reliability, so you should only use RH_RF95 if you do not need the higher
// level messaging abilities.
// It is designed to work with the other example rf95_server
// Tested with Anarduino MiniWirelessLoRa, Rocket Scream Mini Ultra Pro with
// the RFM95W, Adafruit Feather M0 with RFM95

#include <SPI.h>
#include <RH_RF95.h>
#include <time.h>
#include <string.h>
#include <RTCZero.h>

#define DEVICE_ID 4095
#define MESSAGE_SIZE 48
#define GROUP_FLAG 0

#define MSG_TYPE_SIZE 3
#define DEVICE_ID_SIZE 12
#define COORDINATES_SIZE 32
#define GROUP_FLAG_SIZE 1
#define BYTE_SIZE 8

#define DELTA_MAX_LAT 17001
#define DELTA_MAX_LNG 23001
#define LAT_MIN  42900000
#define LNG_MIN 22380000

class Field{
    public:
        Field();
        Field(uint8_t, uint16_t = 0);
        void setSize(uint8_t);
        void setValue(uint16_t);
        uint16_t getSize();
        uint16_t getValue();
        void insert(uint16_t *);
        uint16_t extract(uint16_t *);
    private:
        uint8_t pSize;
        uint16_t pValue;
};

Field::Field(){}

Field::Field(uint8_t size, uint16_t value){
    pSize = size;
    pValue = value;
}
void Field::setSize(uint8_t size){
    pSize = size;
}
void Field::setValue(uint16_t value){
    pValue = value;
}
uint16_t Field::getSize(){
    return pSize;
}
uint16_t Field::getValue(){
    return pValue;
}
void Field::insert(uint16_t *messageChunk){
  *messageChunk <<= this->pSize;
  *messageChunk += this->pValue;
}
uint16_t Field::extract(uint16_t *messageChunk){
  pValue = *messageChunk & ((1 << this->pSize)-1);
  *messageChunk >>= this->pSize;
  return pValue;
}

// Singleton instance of the radio driver
RH_RF95 rf95;
//RH_RF95 rf95(5, 2); // Rocket Scream Mini Ultra Pro with the RFM95W
//RH_RF95 rf95(8, 3); // Adafruit Feather M0 with RFM95 

// Need this on Arduino Zero with SerialUSB port (eg RocketScream Mini Ultra Pro)
//#define Serial SerialUSB

void generateLocation (long location[]){
  location[0] = (LAT_MIN+DELTA_MAX_LAT)*-1;
  location[1] = (LNG_MIN+DELTA_MAX_LNG)*-1;
}
void compressCoordinate(long coordinates[], unsigned short compressedCoord[]){
  compressedCoord[0] = (coordinates[0]*(-1) - LAT_MIN);
  compressedCoord[1] = (coordinates[1]*(-1) - LNG_MIN);
}
void appendBits(uint8_t *messageByte, int appendix, unsigned appendixSize){
  *messageByte <<= appendixSize;
  *messageByte += appendix;
}
void updateClock(uint8_t hours, uint8_t minutes, uint8_t seconds){
  setTime(hours, minutes, seconds);
}
uint16_t timeInSeconds(){
  return getHour() * 3600 + getMinutes() * 60 + getSeconds();
}
void generateMessage(uint16_t *message, unsigned messageSize, Field *fields){
  unsigned sumOfSizes = 0;
  unsigned j = 0;

  for (unsigned i = 0; i < messageSize; i++){
    while (sumOfSizes < 16){
      sumOfSizes += fields[j].getSize();
      fields[j].insert(message+i);
      j++;
    }
    sumOfSizes = 0;
  }
}

void setup() 
{
  // Rocket Scream Mini Ultra Pro with the RFM95W only:
  // Ensure serial flash is not interfering with radio communication on SPI bus
//  pinMode(4, OUTPUT);
//  digitalWrite(4, HIGH);

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

/*
Tipos de Mensagem:
  1- Beacon do Totem
  2- Beacon do Terminal
  3- Solicitação/Aceite de Transmissão
  4- Registro
  5- Eleição de Líder de Grupo
  6- Pedido de Socorro
  7- Notificação de Resgate
*/

void loop()
{
  uint8_t message[MESSAGE_SIZE/8];
  long location[2];
  generateLocation(location);
  unsigned short compressedCoord[2];
  char messageType = '5';

  Serial.print("Location ");
  Serial.print(location[0]);
  Serial.print("; ");
  Serial.println(location[1]);

  compressCoordinate(location, compressedCoord);

  Serial.print("Crompressed Location ");
  Serial.print(compressedCoord[0]);
  Serial.print("; ");
  Serial.println(compressedCoord[1]);

  append_bits(&message[5], (int) (compressedCoord[1] & 0xFF), BYTE_SIZE);
  append_bits(&message[4], (int) ((compressedCoord[1] >> 8) & 0xFF), BYTE_SIZE);
  append_bits(&message[3], (int) (compressedCoord[0] & 0xFF), BYTE_SIZE);
  append_bits(&message[2], (int) ((compressedCoord[0] >> 8) & 0xFF), BYTE_SIZE);
  append_bits(&message[1], (int) (DEVICE_ID & 0xFF), BYTE_SIZE);
  append_bits(&message[0], messageType, MSG_TYPE_SIZE);
  append_bits(&message[0], GROUP_FLAG, GROUP_FLAG_SIZE);
  append_bits(&message[0], (int) ((DEVICE_ID >> BYTE_SIZE) & 0x0F), DEVICE_ID_SIZE-BYTE_SIZE);

  //Transmission
  Serial.print("Message to send: ");
  Serial.println((char*)message);
  Serial.println("Sending Beacon");
  // Send a message to rf95_server
  Serial.println(sizeof(message));
  rf95.send(message, sizeof(message));
  rf95.waitPacketSent();
  Serial.println("Packet sent!");
  // Now wait for a reply
  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);

  if (rf95.waitAvailableTimeout(3000))
  { 
    // Should be a reply message for us now   
    if (rf95.recv(buf, &len))
   {
      Serial.print("got reply: ");
      Serial.println((char*)buf);
//      Serial.print("RSSI: ");
//      Serial.println(rf95.lastRssi(), DEC);    
    }
    else
    {
      Serial.println("recv failed");
    }
  }
  else
  {
    Serial.println("No reply, is rf95_server running?");
  }
  delay(400);
}