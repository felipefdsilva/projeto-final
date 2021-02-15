#include "context.h"
#include "concrete_states.h"

TerminalMachine::TerminalMachine(){
    listeningBeacons = new ListeningBeaconsState(this);
    sendingBeacons = new SendingBeaconsState(this);
    acceptTransmission = new AcceptTransmissionState(this);
    requestTransmission = new RequestTransmissionState(this);
    sendData = new SendDataState(this);
    waitTransmissionRequest = new WaitTransmissionState(this);
    savingData = new SavingDataState(this);

    setStateToListeningBeacons();
    run();
}

TerminalMachine::~TerminalMachine(){
    delete listeningBeacons;
    delete sendingBeacons;
    delete acceptTransmission;
    delete requestTransmission;
    delete sendData;
    delete waitTransmissionRequest;
    delete savingData;
}
void TerminalMachine::setStateToListeningBeacons(){
    pCurrentState = listeningBeacons;
}

void TerminalMachine::setStateToSendingBeacons(){
    pCurrentState = sendingBeacons;
}

void TerminalMachine::setStateToAcceptTransmission(){
    pCurrentState = acceptTransmission;
}

void TerminalMachine::setStateToRequestTransmission(){
    pCurrentState = requestTransmission;
}

void TerminalMachine::setStateToSendData(){
    pCurrentState = sendData;
}

void TerminalMachine::setStateToWaitTransmissionRequest(){
    pCurrentState = waitTransmissionRequest;
}

void TerminalMachine::setStateToSavingData(){
    pCurrentState = savingData;
}

TerminalState *TerminalMachine::getCurrentState(){
    return pCurrentState;
}

void TerminalMachine::run(){
    pCurrentState->run();
}