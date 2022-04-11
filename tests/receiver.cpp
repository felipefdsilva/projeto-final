#include <iostream>

#include "../messages/message.h"
#include "../messages/field.h"
#include "http.h"

#define OK	0

using namespace std;

int main (int argc, char **argv){
	//Reception
	cout << "\nReceiving Message" << endl;

    uint8_t msg[6*2*BYTE];
    receiveMessageLocally(msg);
	Message receivedMessage(getMessageType(msg));
	receivedMessage.saveMessageAsBytes(msg);

	cout << "Received Message: ";
	receivedMessage.printMessage();

	receivedMessage.convertMessageBytesInFields(); //converte para Fields
	cout << "Message Fields: ";
	receivedMessage.printFieldValues();

	return OK;
}