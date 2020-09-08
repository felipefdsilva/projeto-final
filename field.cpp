#include "field.h"
#include <iostream>

using namespace std;

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
    unsigned positon = TWO_BYTES - this->getSize(); //to get k MSB bits, extract from 16 to position
    unsigned k_MSBs = ~((1 << positon)-1); //Example: 001 << 2 is 100. Then, 100 - 001 is 011. The complement is then 100.
	
    pValue = *messageChunk & k_MSBs;
    pValue >>= positon; //return value to begining of byte
	*messageChunk <<= this->getSize();
	return pValue;
}