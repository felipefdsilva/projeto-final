#include "state_interface.h"

#ifndef _CONCRETE_STATES_H_
#define _CONCRETE_STATES_H_ "concrete_states.h"

class ListeningBeaconsState: public TerminalState{
    public:
        ListeningBeaconsState(TerminalMachine *);
        char *listen();
        void run(char **);
};

class SendingBeaconsState: public TerminalState{
    public:
        SendingBeaconsState(TerminalMachine *);
        void run(char **);
        void speak();
        char *listen();
};

class AcceptTransmissionState: public TerminalState{
    public:
        AcceptTransmissionState(TerminalMachine *);
        void run(char **);
};

class RequestTransmissionState: public TerminalState{
    public:
        RequestTransmissionState(TerminalMachine *);
        void run(char **);
};

class SendDataState: public TerminalState{
    public:
        SendDataState(TerminalMachine *);
        void run(char **);
};

class WaitTransmissionState: public TerminalState{
    public:
        WaitTransmissionState(TerminalMachine *);
        void run(char **);
};

class SavingDataState: public TerminalState{
    public:
        SavingDataState(TerminalMachine *);
        void run(char **);
};

#endif