#ifndef HTTP_H
#define HTTP_H "http.h"

#define PORT 8080
#define LOCAL_IP_ADR "127.0.0.1"


class LocalChannel{
    public:
        LocalChannel(bool);
        void receiveMessage(uint8_t *, size_t);
        void sendMessage(uint8_t *, size_t);

    protected:
        void createSocket();
        void setSocketOptions();
        struct sockaddr_in bindAddress();
        void awaitsConnectionRequest();
        void acceptConnection(struct sockaddr_in);
        void setUpServer();
        void connectToServer();

    private:
        int serverSocket;
        int peerSocket;
        bool pServer;
};

#endif