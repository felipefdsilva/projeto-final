/*
* Deals with protocol message types
* Felipe Ferreira
* Set/2020
*/
#include "message.h"
#include <iostream>

using namespace std;

uint16_t getMessageType(uint8_t *message){
	//É preciso ler o tipo da mensagem, nos primeiros 16 bits,
    // para poder construir um objeto da classe Message
	uint16_t messageChunk = (((uint16_t) message[0]) << 8) | message[1];
	return Field(MSG_TYPE_SIZE).extract(&messageChunk);
}

/*Construtor*/
Message::Message(unsigned type){
    //Totem Beacon
    if (type == TOTEN_BEACON){
        pFieldCount = 5;
        pMessageSize = 3;
        pFields = new Field[pFieldCount];
        pFields[0].setSize(MSG_TYPE_SIZE);
        pFields[1].setSize(PADDING_1_SIZE);
        pFields[2].setSize(DEVICE_ID_SIZE);
        pFields[3].setSize(COORDINATE_SIZE);
        pFields[4].setSize(COORDINATE_SIZE);
    }
    //Terminal Beacon
    else if (type == TERMINAL_BEACON){
        pFieldCount = 5;
        pMessageSize = 3;
        pFields = new Field[pFieldCount];
        pFields[0].setSize(MSG_TYPE_SIZE);
        pFields[1].setSize(GROUP_FLAG_SIZE);
        pFields[2].setSize(DEVICE_ID_SIZE);
        pFields[3].setSize(COORDINATE_SIZE);
        pFields[4].setSize(COORDINATE_SIZE);
    }
    //Solict./Aceite TX
    else if (type == TX_RX){
        pFieldCount = 7;
        pMessageSize = 3;
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
    else if (type == RECORD){
        pFieldCount = 9;
        pMessageSize = 6;
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
    else if (type == GROUP_LEADER){
        pFieldCount = 5;
        pMessageSize = 2;
        pFields = new Field[pFieldCount];
        pFields[0].setSize(MSG_TYPE_SIZE);
        pFields[1].setSize(GROUP_FLAG_SIZE);
        pFields[2].setSize(DEVICE_ID_SIZE);
        pFields[3].setSize(BATTERY_SIZE);
        pFields[4].setSize(PADDING_2_SIZE);
    }
    //Pedido de Socorro
    else if (type == HELP){
        pFieldCount = 9;
        pMessageSize = 6;
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
    else if (type == RESCUE){
        pFieldCount = 7;
        pMessageSize = 4;
        pFields = new Field[pFieldCount];
        pFields[0].setSize(MSG_TYPE_SIZE);
        pFields[1].setSize(PADDING_1_SIZE);
        pFields[2].setSize(DEVICE_ID_SIZE);
        pFields[3].setSize(COORDINATE_SIZE);
        pFields[4].setSize(COORDINATE_SIZE);
        pFields[5].setSize(HELP_FLAG_SIZE);
        pFields[6].setSize(PADDING_2_SIZE);
    }
    else {
        cout << "Message type is " << type << endl;
        throw invalid_argument("Not a valid message type");
    }
    pMessage = new uint16_t[pMessageSize];
    pByteMessage = new uint8_t[pMessageSize*2];
}
/*Destrutor*/
Message::~Message(){
    delete pFields;
    delete pMessage;
}
/*converte um array de Fields no array de bytes para envio via LoRa*/
void Message::convertFieldsArrayInBytes(){
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
void Message::convertMessageBytesInFields(){
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
uint8_t *Message::getMessageAsBytes(){
    for(unsigned i=0; i < pMessageSize; i++){
        pByteMessage[(i+1)*2-2] = (pMessage[i] & 0xff00) >> 8;
        pByteMessage[(i+1)*2-1] = pMessage[i] & 0x00ff;
    }
    return pByteMessage;
}
/*Copia a messagem recebida para o atributo privado*/
void Message::saveMessageAsBytes(uint8_t *message){
    for(unsigned i=0; i < pMessageSize; i++){
        pMessage[i] = (uint16_t) message[(i+1)*2-2];
        pMessage[i] <<= BYTE;
        pMessage[i] += message[(i+1)*2-1];
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
void Message::printMessage(){
    uint8_t *byteMessage = this->getMessageAsBytes();

    for (unsigned i = 0; i < this->getMessageSize()*2; i++){
		cout << byteMessage[i] << " ";
	}
	cout << endl;
}
void Message::printFieldValues(){
	for (unsigned i = 0; i < this->getFieldCount(); i++){
		cout << this->getFields()[i].getValue() << " ";
	}
	cout << endl;
}
