
#include "terminal_machine.h"
#include "terminal_state.h"

TerminalMachine TerminalState::getTerminalMachine(){
    return *pTerminalMachine;
}
void TerminalState::setTerminalMachine(TerminalMachine *terminalMachine){
    pTerminalMachine = terminalMachine;
}