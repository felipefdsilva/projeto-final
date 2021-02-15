#include "concrete_states.h"
#include "context.h"

ListeningBeaconsState::ListeningBeaconsState(TerminalMachine *terminalMachine){
    this->setTerminalMachine(terminalMachine);
}

char *ListeningBeaconsState::listen(){
    //TODO: integrar com o código do arduino
    return "new message";
}

void ListeningBeaconsState::run(){
    unsigned period = 100;
    unsigned t = 0;
    char *hasMessage;
    
    while (t < period){
        hasMessage = listen();
        t++;

        if (hasMessage){
            getTerminalMachine().setStateToRequestTransmission();
            getTerminalMachine().run();
            return;
        }
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

void RequestTransmissionState::run(){
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

