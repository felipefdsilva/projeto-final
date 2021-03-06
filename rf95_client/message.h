  
/*
* Deals with protocol message types
* Felipe Ferreira
* Fev/2020
*/
#include "field.h"

#ifndef MESSAGE_H
#define MESSAGE_H "message.h"

#define BYTE 8
#define BATTERY_SIZE 4
#define MSG_TYPE_SIZE 3
#define DEVICE_ID_SIZE 12
#define GROUP_FLAG_SIZE 1
#define COORDINATE_SIZE 16
#define CHANNEL_SIZE 2
#define HOP_COUNT_SIZE 4
#define MAX_RECORDS_SIZE 10
#define RECORD_TIME_SIZE 16
#define LOCATION_TIME_SIZE 16
#define HELP_FLAG_SIZE 4
#define PADDING_1_SIZE 1
#define PADDING_2_SIZE 12

using namespace std;

class Message{
    public:
        Message(unsigned);
        ~Message();
        void generateMessage();
        void readMessage();
        uint8_t *getMessage();
        void setMessage(uint8_t *message);
        unsigned getMessageSize();
        Field *getFields();
        unsigned getFieldCount();
        void printMessage();
        void printFieldValues();
    private:
        Field *pFields;
        unsigned pFieldCount;
        uint16_t *pMessage;
        uint8_t *pByteMessage;
        unsigned pMessageSize; //in BYTE_SIZE*2
};

#endif