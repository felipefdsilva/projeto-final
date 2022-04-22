// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#include "http.h"


LocalChannel::LocalChannel(bool server){
	createSocket();

	if (server) {
		setUpServer();
	}
	else {
		connectToServer();
	}
	pServer = server;
}

void LocalChannel::setUpServer(){
	printf("Setting up server\n");

	setSocketOptions();
	struct sockaddr_in socketAddress = bindAddress();
	awaitsConnectionRequest();
	acceptConnection(socketAddress);
}

void LocalChannel::connectToServer(){
	printf("Connecting to Server\n");
	struct sockaddr_in address;

	address.sin_family = AF_INET;
	address.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, LOCAL_IP_ADR, &(address.sin_addr))<=0){
		printf("Invalid address/ Address not supported\n");
		exit(EXIT_FAILURE);
	}

	if (connect(serverSocket, (struct sockaddr *)&address, sizeof(address)) < 0){
		printf("Connection Failed\n");
		exit(EXIT_FAILURE);
	}
}

void LocalChannel::createSocket(){
	printf("Creating Socket\n");

	serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	if(serverSocket < 0){
		printf("Socket creation error\n");
		exit(EXIT_FAILURE);
	}
}

void LocalChannel::setSocketOptions(){
	printf("Configuring socket\n");

	int opt = 1;
	// Configures socket to reuse address and port
	if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))){
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
}

struct sockaddr_in LocalChannel::bindAddress(){
	printf("Binding socket address\n");

	struct sockaddr_in serverAddress;

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(PORT);

	// Forcefully binding the socket to local ip pAddress
	unsigned bindStatus = bind(
		serverSocket,
		(struct sockaddr *)&serverAddress,
		sizeof(serverAddress)
	);
	if (bindStatus < 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	return serverAddress;
}

void LocalChannel::awaitsConnectionRequest(){
	printf("Awaiting connection request\n");

    if (listen(serverSocket, 3) < 0){
        perror("listen");
        exit(EXIT_FAILURE);
    }
}

void LocalChannel::acceptConnection(struct sockaddr_in socketAdress){
	printf("Accepting request\n");

	unsigned addressLength = sizeof(socketAdress);

	peerSocket = accept(
		serverSocket,
		(struct sockaddr *) &socketAdress,
		(socklen_t*) &addressLength
	);

	if (peerSocket<0){
        perror("accept");
        exit(EXIT_FAILURE);
    }
}

void LocalChannel::receiveMessage(uint8_t *message, size_t msgMaxSize){
	printf("Receiving message\n");

	if(pServer){
    	read(peerSocket, message, msgMaxSize);
	}
	else {
		read(serverSocket, message, msgMaxSize);
	}
}

void LocalChannel::sendMessage(uint8_t *message, size_t messageSize){
	printf("Sending message\n");

	if(pServer){
		send(peerSocket, message, messageSize, 0);
	}
	else {
		send(serverSocket, message, messageSize, 0);
	}

	printf("Message sent.\n");
}