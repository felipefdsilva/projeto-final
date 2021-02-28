#include "state_interface.h"

#ifndef _CONTEXT_H_
#define _CONTEXT_H_ "context.h"

class TerminalMachine{
    public:
        TerminalMachine();
        ~TerminalMachine();
        void setStateToListeningBeacons();
        void setStateToSendingBeacons();
        void setStateToAcceptTransmission();
        void setStateToRequestTransmission();
        void setStateToSendData();
        void setStateToWaitTransmissionRequest();
        void setStateToSavingData();
        TerminalState *getCurrentState();
        void run(char **);

    private:
        TerminalState *pCurrentState;
        TerminalState *listeningBeacons;
        TerminalState *sendingBeacons;
        TerminalState *acceptTransmission;
        TerminalState *requestTransmission;
        TerminalState *sendData;
        TerminalState *waitTransmissionRequest;
        TerminalState *savingData;
};

#endif