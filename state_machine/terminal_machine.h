#include "terminal_state.h"
#include "message.h"

#ifndef _TERMINAL_MACHINE_H_
#define _TERMINAL_MACHINE_H_ "terminal_machine.h"

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

        void setRole(bool);
        bool getRole();

        void setPeer(uint16_t);
        uint16_t getPeer();

        void setHopCount(uint16_t);
        utin16_t getHopCount();

        void setMaxRecords(uint16_t);
        uint16_t getMaxRecords();

        void setChannel(uint16_t);
        utin16_t getChannel();

        void run();

    private:
        bool isFirst;
        uint16_t peerId;
        uint16_t hopCount;
        uint16_t maximumRecords;
        uint16_t channel;
        TerminalState *pCurrentState;
        TerminalState *listeningBeacons;
        TerminalState *sendingBeacons;
        TerminalState *receiveParameters;
        TerminalState *sendParameters;
        TerminalState *saveRecords;
        TerminalState *sendRecords;
};

#endif