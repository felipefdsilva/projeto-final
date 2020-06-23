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
#define MESSAGE_SIZE 32
#define MSG_TYPE_SIZE 3
#define DEVICE_ID_SIZE 12
#define GROUP_FLAG_SIZE 1

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

void generateMessage(uint16_t *message, unsigned messageSize, Field *fields, unsigned fieldCount){
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

int main (int argc, char **argv){
	uint16_t message[MESSAGE_SIZE/16];
	//unsigned short compressedCoord[2];
	uint16_t messageType = 5;
	uint8_t fieldCount = 0;
	cout << time_in_seconds() << endl;
	exit(1);
	
	//string location = generateLocation();
	//cout << "Coordenada: " << location << endl;

	//Compressing Coordinates
	//compressCoordinate(location, compressedCoord);

	// TODO: improve this code
	uint8_t sizes []= {3, 1, 12, 4, 12};
	uint16_t values[] = {messageType, GROUP_FLAG, DEVICE_ID, 15, 0};
	fieldCount = 5;
	Field fields[fieldCount];

	for (unsigned i=0; i < fieldCount; i++){
		fields[i].setSize(sizes[i]);
		fields[i].setValue(values[i]);
	}
	// TODO: end
	generateMessage(message, MESSAGE_SIZE/16, fields, fieldCount);

	//Transmission
	cout << "\nMessage to send: ";
	for (unsigned i=0; i<MESSAGE_SIZE/16;i++){
		cout << message[i] << " ";
	}
	cout << endl;

	//Reception
	cout << "Retrieved Device ID: " << Field(DEVICE_ID_SIZE).extract(&message[0]) << endl;
	cout << "Retrieved Group Flag: " << Field(GROUP_FLAG_SIZE).extract(&message[0]) << endl;
	cout << "Retrieved Message Type: " << Field(MSG_TYPE_SIZE).extract(&message[0]) << endl;
	cout << "Retrieved Padding: " << Field(12).extract(&message[1]) << endl;
	cout << "Retrieved Battery: " << Field(BATTERY_SIZE).extract(&message[1]) << endl;
	//cout << "Retrieved Latitude: " << decompressCoordinate(message[1], LAT_MIN) << endl;
	//cout << "Retrieved Longitude: " << decompressCoordinate(message[2], LNG_MIN) << endl;
	
	return OK;
}