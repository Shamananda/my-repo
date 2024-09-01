//client.hpp

#ifndef CLIENT_H
#define CLIENT_H


#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdint.h>
#include<bits/stdc++.h>


using namespace std;

class Client{
	private:
		int8_t iClientSock;
		sockaddr_in serverAddr;
		int16_t iClientPort;

	public:
		Client();
		Client(int16_t iPort);
		~Client();

		int8_t iInitClientSocket(int8_t iDomain, int8_t iType, int8_t iProtocol);
		int8_t iSendData();
		int8_t iReceiveData();	
		int8_t iCloseConnection();
};

#endif
