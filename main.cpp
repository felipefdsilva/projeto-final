#include <iostream>
#include <iomanip>
#include <string>
#include "field.h"
#include "coordinate.h"
#include <ctime>
//para o relógio do arduino//
//#include <RTC.h> 

#define OK	0

#define UTC -3

#define GROUP_FLAG 1
#define DEVICE_ID 4095

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



using namespace std;

/*para sincronizar o relógio do arduio: talvez precise de modificações
void updateClock(uint8_t hours, uint8_t minutes, uint8_t seconds){
	setTime(hours, minutes, seconds)
}*/

uint16_t time_in_seconds(){
	//ARDUINO:
	//return getHour() * 3600 + getMinutes() * 60 + getSeconds()
	//PC:
	time_t rawtime;
	struct tm *ptm;

	time(&rawtime);
	ptm = gmtime(&rawtime);
	return (ptm->tm_hour+UTC)%24 * 3600 + ptm->tm_min * 60 +  ptm->tm_sec;
}

void generateMessage(uint16_t *message, unsigned messageSize, Field *fields){
	unsigned sumOfSizes = 0;
	unsigned j = 0;

	for (unsigned i = 0; i < messageSize; i++){
		while (sumOfSizes < 16){
			sumOfSizes += fields[j].getSize();
			fields[j].insert(message+i);
			j++;
		}
		sumOfSizes = 0;
	}
}
void extractFields(Field *fields, uint16_t *message, unsigned messageSize){
	unsigned type = Field(MSG_TYPE_SIZE).extract(&message[messageSize-1]);
	fields[0].setValue(type);

	//Beacon do Totem
	if (type == 1){	
		Field(1).extract(&message[messageSize-1]); //padding
		fields[1].setValue(Field(DEVICE_ID_SIZE).extract(&message[messageSize-1]));
		fields[2].setValue(Field(COORDINATE_SIZE).extract(&message[messageSize-2]));
		fields[3].setValue(Field(COORDINATE_SIZE).extract(&message[messageSize-3]));
	}
	 //Beacon do Terminal 
	else if (type == 2){
		fields[1].setValue(Field(GROUP_FLAG_SIZE).extract(&message[messageSize-1]));
		fields[2].setValue(Field(DEVICE_ID_SIZE).extract(&message[messageSize-1]));
		fields[3].setValue(Field(COORDINATE_SIZE).extract(&message[messageSize-2]));
		fields[4].setValue(Field(COORDINATE_SIZE).extract(&message[messageSize-3]));
	}
	//Solicitação/Aceite de Transmissão
	else if (type == 3){
		fields[1].setValue(Field(GROUP_FLAG_SIZE).extract(&message[messageSize-1]));
		fields[2].setValue(Field(DEVICE_ID_SIZE).extract(&message[messageSize-1]));
		fields[3].setValue(Field(RECORD_TIME_SIZE).extract(&message[messageSize-2]));
		fields[4].setValue(Field(MAX_RECORDS_SIZE).extract(&message[messageSize-3]));
		fields[5].setValue(Field(HOP_COUNT_SIZE).extract(&message[messageSize-3]));
		fields[6].setValue(Field(CHANNEL_SIZE).extract(&message[messageSize-3]));
	}
	//Registro
	else if (type == 4){
		fields[1].setValue(Field(GROUP_FLAG_SIZE).extract(&message[messageSize-1]));
		fields[2].setValue(Field(DEVICE_ID_SIZE).extract(&message[messageSize-1]));
		fields[3].setValue(Field(RECORD_TIME_SIZE).extract(&message[messageSize-2]));
		fields[4].setValue(Field(COORDINATE_SIZE).extract(&message[messageSize-3]));
		fields[5].setValue(Field(COORDINATE_SIZE).extract(&message[messageSize-4]));
		fields[6].setValue(Field(LOCATION_TIME_SIZE).extract(&message[messageSize-5]));
		fields[7].setValue(Field(HOP_COUNT_SIZE).extract(&message[messageSize-6]));
		Field(12).extract(&message[messageSize-1]); //padding
	}
	//Eleição de Líder de Grupo
	else if (type == 5){
		fields[1].setValue(Field(GROUP_FLAG_SIZE).extract(&message[messageSize-1]));
		fields[2].setValue(Field(DEVICE_ID_SIZE).extract(&message[messageSize-1]));
		fields[3].setValue(Field(BATTERY_SIZE).extract(&message[messageSize-2]));
		Field(12).extract(&message[messageSize-1]); //padding
	}
	//Pedido de Socorro
	else if (type == 6){
		fields[1].setValue(Field(GROUP_FLAG_SIZE).extract(&message[messageSize-1]));
		fields[2].setValue(Field(DEVICE_ID_SIZE).extract(&message[messageSize-1]));
		fields[3].setValue(Field(RECORD_TIME_SIZE).extract(&message[messageSize-2]));
		fields[4].setValue(Field(COORDINATE_SIZE).extract(&message[messageSize-3]));
		fields[5].setValue(Field(COORDINATE_SIZE).extract(&message[messageSize-4]));
		fields[6].setValue(Field(LOCATION_TIME_SIZE).extract(&message[messageSize-5]));
		fields[7].setValue(Field(HELP_FLAG_SIZE).extract(&message[messageSize-6]));
		Field(12).extract(&message[messageSize-1]); //padding
	}
	//Notificação de Resgate 
	else {
		fields[1].setValue(Field(GROUP_FLAG_SIZE).extract(&message[messageSize-1]));
		fields[2].setValue(Field(DEVICE_ID_SIZE).extract(&message[messageSize-1]));
		fields[3].setValue(Field(COORDINATE_SIZE).extract(&message[messageSize-2]));
		fields[4].setValue(Field(COORDINATE_SIZE).extract(&message[messageSize-3]));
		fields[5].setValue(Field(HELP_FLAG_SIZE).extract(&message[messageSize-4]));
		Field(12).extract(&message[messageSize-1]); //padding
	}
}

int main (int argc, char **argv){
	messageSize = 48;
	uint16_t message[messageSize/16];
	//unsigned short compressedCoord[2];
	uint16_t messageType = 2;
	uint8_t fieldCount = 0;
	cout << "Time in seconds " << time_in_seconds() << endl;
	
	//string location = generateLocation();
	//cout << "Coordenada: " << location << endl;

	//Compressing Coordinates
	//compressCoordinate(location, compressedCoord);

	// TODO: improve this code
	fieldCount = 5;
	uint8_t sizes [fieldCount] = {16, 16, 12, 1, 3};
	uint16_t values[fieldCount] = {200, 250, DEVICE_ID, GROUP_FLAG, messageType};
	Field fields[fieldCount];

	for (unsigned i=0; i < fieldCount; i++){
		fields[i].setSize(sizes[i]);
		fields[i].setValue(values[i]);
	}
	// TODO: end
	generateMessage(message, messageSize/16, fields);

	//Transmission
	cout << "\nMessage to send: ";
	for (unsigned i=0; i<messageSize/16;i++){
		cout << message[i] << " ";
	}
	cout << endl;

	//Reception
	/*
	 * O que preciso saber para ler uma mensagem? 
	 * Numero de campos
	 * Tipo da mensagem - OK
	 * Tamanho da mensagem
	 */
	 // todo: Uma ideia é criar uma class Message
	 /*
	 * Construtor recebe o tipo da mensagem
	 * Constroi array de Fields com os tamanhos configurados
	 * Esse array é passado para extractFields
	 * extractFileds preenche os valores de acordo com message
	 */
	Field retrievedFields[fieldCount];
	extractFields(retrievedFields, message, messageSize/16);

	for (unsigned i=0; i < fieldCount; i++){
		cout << retrievedFields[i].getValue() << endl;
	}
	return OK;
}
/*
Tipos de Mensagem:
  1- Beacon do Totem
  2- Beacon do Terminal
  3- Solicitação/Aceite de Transmissão
  4- Registro
  5- Eleição de Líder de Grupo
  6- Pedido de Socorro
  7- Notificação de Resgate
*/