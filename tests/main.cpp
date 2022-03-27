#include <iostream>
//#include <iomanip>
//#include <string>
//#include <ctime>

//#include "coordinate.h"
#include "../messages/message.h"
#include "../messages/field.h"

#define OK	0

using namespace std;

int main (int argc, char **argv){
	Message message(RECORD);
	cout << "message size is: " << message.getFieldCount() << endl;

	uint16_t values[] = {4, 1, 4095, 43200, 42345, 25908, 10123, 3, 0};

	for (unsigned i = 0; i < message.getFieldCount(); i++){
		message.getFields()[i].setValue(values[i]);
	}
	cout << "Field values: ";
	message.printFieldValues();

	//Transmission
	message.convertFieldsArrayInBytes();
	cout << "Message to send: ";
	message.printMessage();

	//Reception
	cout << "\nReceiving Message" << endl;

	//É preciso ler o tipo da mensagem, nos primeiros 16 bits, para poder construir um objeto Message
	uint16_t messageChunk = (((uint16_t) message.getMessageAsBytes()[0]) << 8) | message.getMessageAsBytes()[1];
	uint16_t type = Field(MSG_TYPE_SIZE).extract(&messageChunk);

	Message receivedMessage(type);
	receivedMessage.saveMessageAsBytes(message.getMessageAsBytes());

	cout << "Received Message: ";
	receivedMessage.printMessage();

	receivedMessage.convertMessageBytesInFields(); //converte para Fields
	cout << "Message Fields: ";
	receivedMessage.printFieldValues();

	return OK;
}