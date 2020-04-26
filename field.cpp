#include "field.h"
#include <iostream>

Field::Field(char type){
    pType = type;

    switch(type){
        case 'a': // Lider de grupo
            size = 1;
            break;
        case 'b': // Canal 
            size = 2;
            break;
        case 'c': // type 
            size = 3;
            break;
        case 'd': // Bateria
            size = 4;
            break;
        case 'e': // Help Flag
            size = 4;
            break;
        case 'f': // Hop Count
            size = 4;
            break;
        case 'g': // Máximo de registros
            size = 10;
            break;
        case 'h': // ID
            size = 12;
            break;
        case 'i': // Record Time
            size = 16;
            break;
        case 'j': // Location Time
            size = 16;
            break;
        case 'k': // Latitude
            size = 16;
            break;
        case 'l': // Longitude
            size = 16;
            break;
    }
}
uint16_t Field::getFieldSize(){
    return size;
}
uint16_t Field::getFieldValue(){
    return value;
}
uint16_t Field::insert(uint16_t messageChunk){
  messageChunk <<= this->size;
  messageChunk += this->value;
  return messageChunk;
}
uint16_t Field::extract(uint16_t messageChunk, uint16_t position){
    return ((messageChunk >> (position - 1)) & ((1 << this->size) - 1)); 
}