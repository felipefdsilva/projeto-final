#include "state_interface.h"
#include "message.h"

#ifndef _CONTEXT_H_
#define _CONTEXT_H_ "context.h"

class TerminalMachine{
    public:
        TerminalMachine();
        ~TerminalMachine();

        void setStateToListeningBeacons();
        void setStateToSendingBeacons();
        //Handshake
        void setStateToReceiveParameters();
        void setStateToSendParameters();
        //Records exchange
        void setStateToSendRecords();
        void setStateToSaveRecords();

        TerminalState *getCurrentState();
        void setMessage(Message *);
        Message *getMessage();
        void run();

    protected:
        bool isFirst;
        uint16_t peerId;
        uint16_t hopCount;
        uint16_t maximumRecords;
        uint16_t channel;

    private:
        TerminalState *pCurrentState;
        TerminalState *listeningBeacons;
        TerminalState *sendingBeacons;
        TerminalState *receiveParameters;
        TerminalState *sendParameters;
        TerminalState *saveRecords;
        TerminalState *sendRecords;
};

#endif