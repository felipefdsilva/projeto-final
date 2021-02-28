#include <RH_RF95.h>
#include <SPI.h>
#include "concrete_states.h"
#include "context.h"
#include "message.h"

RH_RF95 rf95;

ListeningBeaconsState::ListeningBeaconsState(TerminalMachine *terminalMachine){
    this->setTerminalMachine(terminalMachine);
}

char *ListeningBeaconsState::listen(){
	if (rf95.available()){
		// Should be a message for us now   
		uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
		uint8_t len = sizeof(buf);

		if (rf95.recv(buf, &len)){
			digitalWrite(led, HIGH);

			Serial.print("got request: ");
			Serial.println((char*)buf);

            return (char *)buf
        }
    return NULL;
}

void ListeningBeaconsState::run(){
    Message beaconMessage(TERMINAL_BEACON);
    unsigned period = 100;
    unsigned t = 0;
    
    while (t < period){
        message = listen();

        if (message){
            //É preciso ler o tipo da mensagem, nos primeiros 16 bits, para poder construir um objeto Message
			uint16_t messageChunk = (((uint16_t) message[0]) << 8) | message[1];
			uint16_t messageType = Field(MSG_TYPE_SIZE).extract(&messageChunk);

            if (messageType == TERMINAL_BEACON){
                beaconMessage.setMessage(message);
                beaconMessage.readMessage();

                uint16_t terminal_id = beaconMessage().getFields()[2].getValue();

                getTerminalMachine().setStateToRequestTransmission();
                getTerminalMachine().run({(char *)terminal_id});
                return;
            }
        }
        t++;
    }
    getTerminalMachine().setStateToSendingBeacons();
    getTerminalMachine().run();
    return;
}

SendingBeaconsState::SendingBeaconsState(TerminalMachine *terminalMachine){
    this->setTerminalMachine(terminalMachine);
}

void SendingBeaconsState::run(){
    //TODO: Implement this
    speak();
}

AcceptTransmissionState::AcceptTransmissionState(TerminalMachine *terminalMachine){
    this->setTerminalMachine(terminalMachine);
}

void AcceptTransmissionState::run(){
//TODO: Implement this
}

RequestTransmissionState::RequestTransmissionState(TerminalMachine *terminalMachine){
    this->setTerminalMachine(terminalMachine);
}

void RequestTransmissionState::run(char **argv){
    terminal_id = (uint16_t) argv[0];
    //TODO: Implement this
}

SendDataState::SendDataState(TerminalMachine *terminalMachine){
    this->setTerminalMachine(terminalMachine);
}

void SendDataState::run(){
//TODO: Implement this
}

WaitTransmissionState::WaitTransmissionState(TerminalMachine *terminalMachine){
    this->setTerminalMachine(terminalMachine);
}

void WaitTransmissionState::run(){
//TODO: Implement this
}

SavingDataState::SavingDataState(TerminalMachine *terminalMachine){
    this->setTerminalMachine(terminalMachine);
}

void SavingDataState::run(){
 //TODO: Implement this
}

