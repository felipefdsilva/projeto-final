#include "context.h"

TerminalState::TerminalState(TerminalMachine &terminalMachine){
    this->setTerminalMachine(terminalMachine);
}

void TerminalState::setTerminalMachine(TerminalMachine &terminalMachine){
    pTerminalMachine = terminalMachine;
}

TerminalMachine TerminalState::getTerminalMachine(){
    return pTerminalMachine;
}

TerminalMachine::TerminalMachine(){
    this->listeningBeacons = new ListeningBeacons(*this);
    //Fazer todos os outros estados concretos
    this->changeState(this->listeningBeacons);
    this->run();
}

char * TerminalMachine::listen(){
    return "AMANHÃ VAI!!!!!";
}

void TerminalMachine::run(){
    pCurrentState.run();
}

ListeningBeacons::ListeningBeacons(TerminalMachine &terminalMachine):TerminalState(terminalMachine){
    this->setTerminalMachine(terminalMachine);
}

void ListeningBeacons::run(){
    unsigned period = 100;
    unsigned t = 0;
    char *hasMessage;
    
    while (t < period){
        hasMessage = getTerminalMachine().listen();
        t++;

        if (hasMessage){
            getTerminalMachine().changeState(new RequestTransmission(getTerminalMachine()));
            getTerminalMachine().run();
            return;
        }
    }
    getTerminalMachine().changeState(new SendingBeacons(getTerminalMachine()));
    getTerminalMachine().run();
    return;
}