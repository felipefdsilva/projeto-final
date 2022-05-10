#include <iostream>

#include "../messages/message.h"
#include "../messages/field.h"
#include "http.h"

#define OK	0

using namespace std;

int main (int argc, char **argv){
    uint8_t message[MESSAGE_MAX_SIZE_BYTES];
	LocalChannel channel(true);

	cout << "Receiving Terminal Beacon" << endl;
    channel.receiveMessage(message, MESSAGE_MAX_SIZE_BYTES);

	if (!message[0]) {
		cout << "No message was received. Timed out" << endl;
		cout << "You should start sending beacons!" << endl;
		exit(1);
	}
	Message messageObj(message);

	cout << "Message as Bytes: ";
	messageObj.printMessage();
	cout << "Message as Fields: ";
	messageObj.printFieldValues();

	cout << "Now, let's request TX" << endl;
	uint16_t values[] = {TX_RX, 0, 248, 29000, 10, 12, 3};
	messageObj.build(values);

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