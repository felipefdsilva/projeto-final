#include <iostream>
//#include <iomanip>
//#include <string>
//#include <ctime>

//#include "coordinate.h"
#include "message.h"
#include "field.h"

#define OK	0

using namespace std;

int main (int argc, char **argv){
	Message message(4);
	uint16_t values[message.getFieldCount()] = {4, 1, 4095, 43200, 42345, 25908, 10123, 3, 0};

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
	uint16_t messageChunk = (((uint16_t) message.getMessage()[0]) << 8) | message.getMessage()[1];
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