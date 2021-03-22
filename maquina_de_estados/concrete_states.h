#include "state_interface.h"

#ifndef _CONCRETE_STATES_H_
#define _CONCRETE_STATES_H_ "concrete_states.h"

class ListeningBeaconsState: public TerminalState{
    public:
        ListeningBeaconsState(TerminalMachine *);
        char *listen();
        void run();
};

class SendingBeaconsState: public TerminalState{
    public:
        SendingBeaconsState(TerminalMachine *);
        void run();
        void speak();
        char *listen();
};

class ReceiveParametersState: public TerminalState{
    public:
        ReceiveParametersState(TerminalMachine *);
        void run();
};

class SendParametersState: public TerminalState{
    public:
        SendParametersState(TerminalMachine *);
        void run();
};

class SaveRecordsState: public TerminalState{
    public:
        SaveRecordsState(TerminalMachine *);
        void run();
};

class SendRecordsState: public TerminalState{
    public:
        SendRecordsState(TerminalMachine *);
        void run();
};

#endif