#ifndef _INTERFACE_H_
#define _INTERFACE_H_ "state_interface.h"

class TerminalState{
    public:
        ~TerminalState();
        TerminalMachine getTerminalMachine();
        void setTerminalMachine(TerminalMachine *);
        virtual void run() = 0;
    
    private:
        TerminalMachine *pTerminalMachine;
};

#endif