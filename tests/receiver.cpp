#include <iostream>

#include "../messages/message.h"
#include "../messages/field.h"
#include "http.h"

#define OK	0

using namespace std;

int main (int argc, char **argv){
	cout << "Receiving Message" << endl;

    uint8_t msg[6*2*BYTE];
    receiveMessageLocally(msg);

	Message receivedMessage(msg);

	cout << "Message as Bytes: ";
	receivedMessage.printMessage();
	cout << "Message as Fields: ";
	receivedMessage.printFieldValues();

	return OK;
}