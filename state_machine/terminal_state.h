#ifndef _TERMINAL_STATE_H_
#define _TERMINAL_STATE_H_ "terminal_state.h"

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