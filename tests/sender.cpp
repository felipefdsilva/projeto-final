#include <iostream>

#include "../messages/message.h"
#include "../messages/field.h"
#include "http.h"

#define OK	0

using namespace std;

int main (int argc, char **argv){
	Message message(RECORD);

	uint16_t values[] = {4, 1, 4095, 43200, 42345, 25908, 10123, 3, 0};

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