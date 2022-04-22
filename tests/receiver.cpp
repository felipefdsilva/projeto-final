#include <iostream>

#include "../messages/message.h"
#include "../messages/field.h"
#include "http.h"

#define OK	0

using namespace std;

int main (int argc, char **argv){
	cout << "Receiving Terminal Beacon" << endl;

    uint8_t message[MESSAGE_MAX_SIZE];

	LocalChannel channel(true);
    channel.receiveMessage(message, MESSAGE_MAX_SIZE);
	Message rcvdMessage(message);

	cout << "Message as Bytes: ";
	rcvdMessage.printMessage();
	cout << "Message as Fields: ";
	rcvdMessage.printFieldValues();

	cout << "Now, let's request TX" << endl;
	uint16_t values[] = {TX_RX, 0, 248, 29000, 10, 12, 3};
	Message toSendMessage(values);

	cout << "Message as Bytes: ";
	toSendMessage.printMessage();
	cout << "Message as Fields: ";
	toSendMessage.printFieldValues();

	channel.sendMessage(
		toSendMessage.getMessageAsBytesArray(),
		toSendMessage.getMessageSize()*2
	);

	return OK;
}