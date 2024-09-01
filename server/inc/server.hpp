//server.hpp

#ifndef SERVER_H
#define SERVER_H

#include<iostream>
#include<bits/stdc++.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdint.h>
#include<memory>

using namespace std;

class Server{
	private:
		int8_t iServerSocket, iClientSocket;
		sockaddr_in serverAddr, clientAddr;
		int16_t iServerPort;
	public:
		Server();
		Server(int16_t iPort);
		~Server();

		int8_t iCreateSocket(int8_t iDomain, int8_t iType, int8_t iProtocol);
		int8_t iListenSocket();
		int8_t iAcceptConnection();

		int8_t iSendData();
		int8_t iReceiveData();

		int8_t iCloseConnection();
};

#endif
