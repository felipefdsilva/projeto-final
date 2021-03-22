#include "context.h"
#include "concrete_states.h"

TerminalMachine::TerminalMachine(){
    listeningBeacons = new ListeningBeaconsState(this);
    sendingBeacons = new SendingBeaconsState(this);
    receiveParameters = new ReceiveParametersState(this);
    sendParameters = new SendParametersState(this);
    saveRecords = new SaveRecordsState(this);
    sendRecords = new SendRecordsState(this);

    setStateToListeningBeacons();
    char *argv = {};
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

void TerminalMachine::setStateToReceiveParameters(){
    pCurrentState = receiveParameters;
}

void TerminalMachine::setStateToSendParameters(){
    pCurrentState = sendParameters;
}

void TerminalMachine::setStateToSaveRecords(){
    pCurrentState = saveRecords;
}

void TerminalMachine::setStateToSendRecords(){
    pCurrentState = sendRecords;
}

TerminalState *TerminalMachine::getCurrentState(){
    return pCurrentState;
}

void TerminalMachine::run(){
    pCurrentState->run(argv);
}

void TerminalMachine::setMessage(Message *messageObject){
    pMessage = messageObject;
}

Message *TerminalMachine::getMessage(){
    return pMessage;
}