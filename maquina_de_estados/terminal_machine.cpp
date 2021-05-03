#include "concrete_states.h"
#include "context.h"

TerminalMachine::TerminalMachine(){
    receiveParameters = new ReceiveParametersState(this);
    listeningBeacons = new ListeningBeaconsState(this);
    sendingBeacons = new SendingBeaconsState(this);
    sendParameters = new SendParametersState(this);
    saveRecords = new SaveRecordsState(this);
    sendRecords = new SendRecordsState(this);

    setStateToListeningBeacons();
}

TerminalMachine::~TerminalMachine(){
    delete receiveParameters;
    delete listeningBeacons;
    delete sendingBeacons;
    delete sendParameters;
    delete saveRecords;
    delete sendRecords;
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

void TerminalMachine::setRole(bool role){
    isFirst = role;
}
bool TerminalMachine::getRole(){
    return isFist;
}
void TerminalMachine::setPeer(uint16_t _peerId){
    peerId = _peerId;
}
uint16_t TerminalMachine::getPeer(){
    return peerId;
}
void TerminalMachine::setHopCount(uint16_t _hopCount){
    hopCount = _hopCount;
}
utin16_t TerminalMachine::getHopCount(){
    return hopCount
}
void TerminalMachine::setMaxRecords(uint16_t _maxRecords){
    maximunRecords = _maxRecords;
}
uint16_t TerminalMachine::getMaxRecords(){
    return maximumRecords;
}
void TerminalMachine::setChannel(uint16_t _channel){
    channel = _channel;
}
utin16_t TerminalMachine::getChannel(){
    return channel;
}

void TerminalMachine::run(){
    pCurrentState->run();
}