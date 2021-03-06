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

void ListeningBeaconsState::run(argv){
    Message beaconMessage(TERMINAL_BEACON);
    //TODO: Implementar periodo em intervalo de tempo
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

void SendingBeaconsState::speak(uint8_t message){
    rf95.send(message, sizeof(message));
    rf95.waitPacketSent();
    Serial.println("Beacon sent!");
}

char *SendingBeaconsState::listen(){
    // Now wait for a reply
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);

    if (rf95.waitAvailableTimeout(3000)){ 
        // Should be a reply message for us now   
        if (rf95.recv(buf, &len)){
            Serial.print("got reply: ");
            Serial.println((char*)buf);
            return (char *)buf  
        }
        Serial.println("recv failed");
        return NULL;
    }
    Serial.println("No reply, is rf95_server running?");
    return NULL;
}

void SendingBeaconsState::run(){
    Message beaconMessage(TERMINAL_BEACON);
    Message txrxMessage(TX_RX);

    uint16_t values[beaconMessage.getFieldCount()] = {
        TERMINAL_BEACON, //message type
        1, //group
        2, //device id
        42345, //latitude
        25908, //longitude
    };

	for (unsigned i = 0; i < beaconMessage.getFieldCount(); i++){
		beaconMessage.getFields()[i].setValue(values[i]);
	}
    //TODO: Implementar periodo em intervalo de tempo
    unsigned period = 100;
    unsigned t = 0;

    while (t < period){
        speak(beaconMessage.getMessage());

        receivedMessage = listen();

        if (receivedMessage){
            //É preciso ler o tipo da mensagem, nos primeiros 16 bits, para poder construir um objeto Message
			uint16_t messageChunk = (((uint16_t) receivedMessage[0]) << 8) | receivedMessage[1];
			uint16_t messageType = Field(MSG_TYPE_SIZE).extract(&messageChunk);

            if (messageType == TX_RX){
                txrxMessage.setMessage(receivedMessage);
                txrxMessage.readMessage();

                char *group = (char *) txrxMessage().getFields()[1].getValue();
                char *terminal_id = (char *) txrxMessage().getFields()[2].getValue();
                char *record_time = (char *) txrxMessage().getFields()[3].getValue();
                char *max_records = (char *) txrxMessage().getFields()[4].getValue();
                char *hop_count = (char *) txrxMessage().getFields()[5].getValue();
                char *channel = (char *) txrxMessage().getFields()[6].getValue();

                char *argv = {group, terminal_id, record_time, max_records, hop_count, channel}

                getTerminalMachine().setStateToAcceptTransmission();
                getTerminalMachine().run(argv);
                return;
            }
        }
        t++;
    }
    //TODO: COMO VOLTAR PARA O INICIO?
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

