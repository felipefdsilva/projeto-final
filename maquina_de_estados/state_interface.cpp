
#include "state_interface.h"
#include "context.h"

TerminalMachine TerminalState::getTerminalMachine(){
    return *pTerminalMachine;
}
void TerminalState::setTerminalMachine(TerminalMachine *terminalMachine){
    pTerminalMachine = terminalMachine;
}