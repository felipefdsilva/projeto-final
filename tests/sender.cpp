#include <iostream>
#include <string>

#include "../messages/message.h"
#include "../messages/field.h"
#include "http.h"

#define OK	0

using namespace std;

int main (int argc, char **argv){
	cout << "Sending Terminal Beacon" << endl;
	// uint16_t values[] = {TOTEN_BEACON, 0, 1, 41000, 38349};
	uint16_t values[] = {TERMINAL_BEACON, 0, 150, 41920, 40349};
	// uint16_t values[] = {TX_RX, 0, 248, 29000, 10, 12, 3};
	// uint16_t values[] = {TX_RX, 0, 249, 29222, 12, 5, 3};
	// uint16_t values[] = {RECORD, 1, 4095, 43200, 42345, 25908, 10123, 3, 0};
	// uint16_t values[] = {GROUP_LEADER, 1, 3333, 15};
	// uint16_t values[] = {HELP, 1, 4095, 43233, 42346, 25908, 10123, 3, 0};
	// uint16_t values[] = {RESCUE, 1, 4095, 42346, 25908, 3, 0};

	Message messageObj(values);

	cout << "Message as Bytes: ";
	messageObj.printMessage();
	cout << "Message as Fields: ";
	messageObj.printFieldValues();

	LocalChannel channel(false);
	channel.sendMessage(
		messageObj.getMessageAsBytesArray(),
		messageObj.getMessageSize()*2
	);

	cout << "Receiving  TX Request" << endl;
	uint8_t msg[MESSAGE_MAX_SIZE];
	channel.receiveMessage(msg, MESSAGE_MAX_SIZE);

	messageObj.reset(msg);

	cout << "Message as Bytes: ";
	messageObj.printMessage();
	cout << "Message as Fields: ";
	messageObj.printFieldValues();

	return OK;
}