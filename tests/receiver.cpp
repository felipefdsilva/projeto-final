#include <iostream>

#include "../messages/message.h"
#include "../messages/field.h"
#include "http.h"

#define OK	0

using namespace std;

int main (int argc, char **argv){
	cout << "Receiving Message" << endl;

    uint8_t message[MESSAGE_MAX_SIZE];

	LocalChannel channel(true);
    channel.receiveMessage(message, MESSAGE_MAX_SIZE);
	Message rcvdMessage(message);

	cout << "Message as Bytes: ";
	rcvdMessage.printMessage();
	cout << "Message as Fields: ";
	rcvdMessage.printFieldValues();

	cout << "Now, let's send a hello" << endl;

	channel.sendMessage((uint8_t *) "hello", 5);

	return OK;
}