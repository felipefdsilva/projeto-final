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
	Message messageObj(message);

	cout << "Message as Bytes: ";
	messageObj.printMessage();
	cout << "Message as Fields: ";
	messageObj.printFieldValues();

	cout << "Now, let's request TX" << endl;
	uint16_t values[] = {TX_RX, 0, 248, 29000, 10, 12, 3};
	messageObj.reset(values);

	cout << "Message as Bytes: ";
	messageObj.printMessage();
	cout << "Message as Fields: ";
	messageObj.printFieldValues();

	channel.sendMessage(
		messageObj.getMessageAsBytesArray(),
		messageObj.getMessageSize()*2
	);

	return OK;
}