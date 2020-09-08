/*
* Deals with protocol message types
* Felipe Ferreira
* Set/2020
*/
#include "message.h"
//#include <iostream>

using namespace std;

/*Construtor*/
Message::Message(unsigned type){
    //Totem Beacon
    if (type == 1){
        pFieldCount = 5;
        pMessageSize = 3;
        pMessage = new uint16_t[pMessageSize];
        pFields = new Field[pFieldCount];
        pFields[0].setSize(MSG_TYPE_SIZE);
        pFields[1].setSize(PADDING_1_SIZE);
        pFields[2].setSize(DEVICE_ID_SIZE);
        pFields[3].setSize(COORDINATE_SIZE);
        pFields[4].setSize(COORDINATE_SIZE);
    }
    //Terminal Beacon
    else if (type == 2){
        pFieldCount = 5;
        pMessageSize = 3;
        pMessage = new uint16_t[pMessageSize];
        pFields = new Field[pFieldCount];
        pFields[0].setSize(MSG_TYPE_SIZE);
        pFields[1].setSize(GROUP_FLAG_SIZE);
        pFields[2].setSize(DEVICE_ID_SIZE);
        pFields[3].setSize(COORDINATE_SIZE);
        pFields[4].setSize(COORDINATE_SIZE);
    }
    //Solict./Aceite TX
    else if (type == 3){
        pFieldCount = 7;
        pMessageSize = 3;
        pMessage = new uint16_t[pMessageSize];
        pFields = new Field[pFieldCount];
        pFields[0].setSize(MSG_TYPE_SIZE);
        pFields[1].setSize(GROUP_FLAG_SIZE);
        pFields[2].setSize(DEVICE_ID_SIZE);
        pFields[3].setSize(RECORD_TIME_SIZE);
        pFields[4].setSize(MAX_RECORDS_SIZE);
        pFields[5].setSize(HOP_COUNT_SIZE);
        pFields[6].setSize(CHANNEL_SIZE);
    }
    //Registro
    else if (type == 4){
        pFieldCount = 9;
        pMessageSize = 6;
        pMessage = new uint16_t[pMessageSize];
        pFields = new Field[pFieldCount];
        pFields[0].setSize(MSG_TYPE_SIZE);
        pFields[1].setSize(GROUP_FLAG_SIZE);
        pFields[2].setSize(DEVICE_ID_SIZE);
        pFields[3].setSize(RECORD_TIME_SIZE);
        pFields[4].setSize(COORDINATE_SIZE);
        pFields[5].setSize(COORDINATE_SIZE);
        pFields[6].setSize(LOCATION_TIME_SIZE);
        pFields[7].setSize(HOP_COUNT_SIZE);
        pFields[8].setSize(PADDING_2_SIZE);
    }
    //Eleição de Lider de Grupo
    else if (type == 5){
        pFieldCount = 5;
        pMessageSize = 2;
        pMessage = new uint16_t[pMessageSize];
        pFields = new Field[pFieldCount];
        pFields[0].setSize(MSG_TYPE_SIZE);
        pFields[1].setSize(GROUP_FLAG_SIZE);
        pFields[2].setSize(DEVICE_ID_SIZE);
        pFields[3].setSize(BATTERY_SIZE);
        pFields[4].setSize(PADDING_2_SIZE);
    }
    //Pedido de Socorro
    else if (type == 6){
        pFieldCount = 9;
        pMessageSize = 6;
        pMessage = new uint16_t[pMessageSize];
        pFields = new Field[pFieldCount];
        pFields[0].setSize(MSG_TYPE_SIZE);
        pFields[1].setSize(PADDING_1_SIZE);
        pFields[2].setSize(DEVICE_ID_SIZE);
        pFields[3].setSize(RECORD_TIME_SIZE);
        pFields[4].setSize(COORDINATE_SIZE);
        pFields[5].setSize(COORDINATE_SIZE);
        pFields[6].setSize(LOCATION_TIME_SIZE);
        pFields[7].setSize(HELP_FLAG_SIZE);
        pFields[8].setSize(PADDING_2_SIZE);
    }
    //Notificação de Resgate
    else {
        pFieldCount = 7;
        pMessageSize = 4;
        pMessage = new uint16_t[pMessageSize];
        pFields = new Field[pFieldCount];
        pFields[0].setSize(MSG_TYPE_SIZE);
        pFields[1].setSize(PADDING_1_SIZE);
        pFields[2].setSize(DEVICE_ID_SIZE);
        pFields[3].setSize(COORDINATE_SIZE);
        pFields[4].setSize(COORDINATE_SIZE);
        pFields[5].setSize(HELP_FLAG_SIZE);
        pFields[6].setSize(PADDING_2_SIZE);
    }
}
/*Destrutor*/
Message::~Message(){
    delete pFields;
    delete pMessage;
}
/*converte um array de Fields no array de bytes para envio via LoRa*/
void Message::generateMessage(){
	unsigned sumOfFieldSizes = 0;
	unsigned j = 0;

	for (unsigned i = 0; i < pMessageSize; i++){
		while (sumOfFieldSizes < BYTE*2){
			sumOfFieldSizes += pFields[j].getSize();
			pFields[j].insert(&pMessage[i]);
			j++;
		}
		sumOfFieldSizes = 0;
	}
}
/*converte um array de bytes em array de Fields*/
void Message::readMessage(){
    unsigned sumOfFieldSizes=0;
    unsigned j = 0;

    for (unsigned i = 0; i < pMessageSize; i++){
        while(sumOfFieldSizes < BYTE*2){
            sumOfFieldSizes += pFields[j].getSize();
            pFields[j].extract(&pMessage[i]);
            j++;
        }
        sumOfFieldSizes = 0;
    }
}
/*Retorna a mensagem em array de bytes*/
uint16_t *Message::getMessage(){
    return pMessage;
}
/*Copia a messagem recebida para o atributo privado*/
void Message::setMessage(uint16_t *message){
    for(unsigned i=0; i < pMessageSize; i++){
        pMessage[i] = message[i];
    }
}
/*Retorna o tamanho da mensagem*/
unsigned Message::getMessageSize(){
    return pMessageSize;
}
Field *Message::getFields(){
    return pFields;
}
unsigned Message::getFieldCount(){
    return pFieldCount;
}
/*
void Message::printMessage(){
    for (unsigned i = 0; i < this->getMessageSize(); i++){
		cout << this->getMessage()[i] << " ";
	}
	cout << endl;
}
void Message::printFieldValues(){
	for (unsigned i = 0; i < this->getFieldCount(); i++){
		cout << this->getFields()[i].getValue() << " ";
	}
	cout << endl;
}
*/