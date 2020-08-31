#ifndef _FIELD_H_
#define _FIELD_H_ "field.h"

#include <stdint.h>

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

#endif