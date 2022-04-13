#include <iostream>
#include <string>

#include "../messages/message.h"
#include "../messages/field.h"
#include "http.h"

#define OK	0

using namespace std;

int main (int argc, char **argv){
	Message message(RESCUE);
	// uint16_t values[] = {0, 0, 1, 41000, 38349}; // TotemBeacon;
	// uint16_t values[] = {2, 0, 150, 41920, 40349}; // TerminalBeacon;
	// uint16_t values[] = {3, 0, 248, 29000, 10, 12, 3}; // AskTx;
	// uint16_t values[] = {3, 0, 249, 29222, 12, 5, 3}; // AccceptTx;
	// uint16_t values[] = {4, 1, 4095, 43200, 42345, 25908, 10123, 3, 0}; // Record;
	// uint16_t values[] = {5, 1, 3333, 15}; // GroupLeaderElection;
	// uint16_t values[] = {6, 1, 4095, 43233, 42346, 25908, 10123, 3, 0}; // HelpCall;
	uint16_t values[] = {7, 1, 4095, 42346, 25908, 3, 0}; // RescueNotification;

	for (unsigned i = 0; i < message.getFieldCount(); i++){
		message.getFields()[i].setValue(values[i]);
	}
	message.printFieldValues();

	//Transmission
	message.convertFieldsArrayInBytes();
	message.printMessage();
	sendMessageLocally(message.getMessageAsBytes(), message.getMessageSize()*2);

	return OK;
}