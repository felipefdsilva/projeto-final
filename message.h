  
/*
* Deals with protocol message types
* Felipe Ferreira
* Fev/2020
*/
// ! este código está desatualizado - não  roda!

#include "field.h"

#ifndef MESSAGE_H
#define MESSAGE_H "message.h"

using namespace std;

class Message{
    public:
        Message(unsigned);
    private:
        Field *pFields;
        unsigned fieldCount;
        unsigned *fieldSizes;
};
Message processMessage(char *, unsigned);

#endif