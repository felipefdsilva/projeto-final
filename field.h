#ifndef _FIELD_H_
#define _FIELD_H_ "field.h"

class Field{
    public:
        Field(char);
        uint16_t getFieldSize();
        uint16_t getFieldValue();
        uint16_t insert(uint16_t);
        uint16_t extract(uint16_t, uint16_t);
    private:
        char pType;
        uint16_t size;
        uint16_t value;
};

#endif