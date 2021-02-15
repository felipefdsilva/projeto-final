#ifndef _CONTEXT_H_
#define _CONTEXT_H_ "context.h"

class TerminalState{
    public:
        TerminalState(TerminalMachine &);
        ~TerminalState();
        void run();
        void setTerminalMachine(TerminalMachine &);
        TerminalMachine getTerminalMachine();
        //void listen();
        //void speak();
    
    private:
        TerminalMachine pTerminalMachine;
};

class TerminalMachine{
    public:
        void changeState(TerminalState &);
        char *listen();
        void run();
        TerminalState sleep;
        TerminalState listeningBeacons;
        TerminalState sendingBeacons;
        TerminalState acceptTransmission;
        TerminalState requestTransmission;
        TerminalState sendData;
        TerminalState waitTransmissionRequest;
        TerminalState savingData;
    
    private:
        TerminalState pCurrentState;
};
class ListeningBeacons: public TerminalState{
    public:
        ListeningBeacons(TerminalMachine &);
        void run();
    
};
#endif