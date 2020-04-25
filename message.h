#ifndef _MESSAGE_H_
#define _MESSAGE_H_ "message.h"

class Field{
    public:
        Field();
        int getFieldSize();
        int getFieldValue();
        uint16_t insert(uint16_t, uint16_t, uint16_t);
        uint16_t extract(uint16_t, uint16_t, uint16_t);
    private:
        unsigned short size;
        unsigned short value;
};
class Message{
    public:
        Message();
        Field getField(string);
    private:
        uint16_t *message;
        unsigned short size;
};