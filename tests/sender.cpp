#include <iostream>
#include <string>

#include "../messages/message.h"
#include "../messages/field.h"
#include "http.h"

#define OK	0

using namespace std;

int main (int argc, char **argv){
	cout << "Sending Message" << endl;
	// uint16_t values[] = {TOTEN_BEACON, 0, 1, 41000, 38349};
	uint16_t values[] = {TERMINAL_BEACON, 0, 150, 41920, 40349};
	// uint16_t values[] = {TX_RX, 0, 248, 29000, 10, 12, 3};
	// uint16_t values[] = {TX_RX, 0, 249, 29222, 12, 5, 3};
	// uint16_t values[] = {RECORD, 1, 4095, 43200, 42345, 25908, 10123, 3, 0};
	// uint16_t values[] = {GROUP_LEADER, 1, 3333, 15};
	// uint16_t values[] = {HELP, 1, 4095, 43233, 42346, 25908, 10123, 3, 0};
	// uint16_t values[] = {RESCUE, 1, 4095, 42346, 25908, 3, 0};

	Message message(values);

	cout << "Message as Bytes: ";
	message.printMessage();
	cout << "Message as Fields: ";
	message.printFieldValues();

	sendMessageLocally(message.getMessageAsBytesArray(), message.getMessageSize()*2);

	return OK;
}