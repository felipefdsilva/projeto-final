#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>

#include "coordinate.h"
#include "message.h"
#include "field.h"

#define OK	0

#define UTC -3

#define GROUP_FLAG 1
#define DEVICE_ID 4095

using namespace std;

/*para sincronizar o relógio do arduio: talvez precise de modificações
void updateClock(uint8_t hours, uint8_t minutes, uint8_t seconds){
	setTime(hours, minutes, seconds)
}

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
*/
int main (int argc, char **argv){
	uint16_t messageType = 4;

	Message message(messageType);
	uint16_t values[message.getFieldCount()] = {messageType, GROUP_FLAG, DEVICE_ID, 43200, 42345, 25908, 10123, 3, 0};

	for (unsigned i = 0; i < message.getFieldCount(); i++){
		message.getFields()[i].setValue(values[i]);
	}	
	cout << "Field values: ";
	message.printFieldValues();
	
	//Transmission
	message.generateMessage();
	cout << "Message to send: ";
	message.printMessage();

	//Reception
	cout << "\nReceiving Message" << endl;

	//É preciso ler o tipo da mensagem, nos primeiros 16 bits, para poder construir um objeto Message
	uint16_t messageChunk = message.getMessage()[0];
	uint16_t type = Field(MSG_TYPE_SIZE).extract(&messageChunk);

	Message receivedMessage(type);
	receivedMessage.setMessage(message.getMessage());

	cout << "Received Message: ";
	receivedMessage.printMessage();

	receivedMessage.readMessage(); //converte para Fields
	cout << "Message Fields: ";
	receivedMessage.printFieldValues();
	
	return OK;
}