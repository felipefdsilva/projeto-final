#include "field.h"
#include <iostream>

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