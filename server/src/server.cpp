//server.cpp

#include "server.hpp"

Server::Server(){}

Server::Server(int16_t port):iServerPort(port){}

Server::~Server(){}

int8_t Server::iCreateSocket(int8_t iDomain = AF_INET, int8_t iType = SOCK_STREAM, int8_t iProtocol =0){
	iServerSocket = socket(iDomain, iType, iProtocol);
	int opt = 1;

	if(iServerSocket == -1){
		cerr<<"Failed Socket Creation";
		return -1;
	}

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(iServerPort);

	//set the server socket to reuse again
	if(setsockopt(iServerSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
		cerr<<"setsockopt";
		return -1;
	}

	//bind the server socket
	if(bind(iServerSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr))<0){
		cerr<<"Binding error";
		close(iServerSocket);
		return -1;
	}
	return 0;

}

int8_t Server::iListenSocket(){
	if(listen(iServerSocket, 50) <0){
		cerr<<"Listening failed";
		return -1;
	}
	return 0;
}

int8_t Server::iAcceptConnection(){
	iClientSocket = accept(iServerSocket, nullptr, nullptr);

	if(iClientSocket < 0){
		cerr<<"Acceptance failed";
		return -1;
	}
	cout<<"Sever has Accepted the client connection"<<endl;
	return 0;

}

int8_t Server::iSendData(){
	char buffer[1024] = "Hello from the server";
	int8_t retVal = send(iClientSocket, buffer, sizeof(buffer),0);
	cout<<"Sent: "<<buffer<<endl;
	return retVal;
}

int8_t Server::iReceiveData(){
	char buffer[1024] = {0};
	int8_t readVal = read(iClientSocket, buffer, sizeof(buffer));
	cout<<"Read: "<<buffer<<endl;
	return readVal;
}

int8_t Server::iCloseConnection(){
	close(iClientSocket);
	return close(iServerSocket);
}

int main(){
	Server objServer(11115);

	if(objServer.iCreateSocket() == 0){
		cout<<"Server Socket created"<<endl;
		if(objServer.iListenSocket() ==0){
			cout<<"Server is Listening"<<endl;
			if(objServer.iAcceptConnection() == 0){
				cout<<"Seerver Accepted"<<endl;
				if(objServer.iSendData() >0){
					cout<<"data sent"<<endl;
				}
			}
		}
	}else{
		cout<<"Failed Socket Creation"<<endl;
	}
	if(objServer.iCloseConnection() == 0){
		cout<<"Successfully close server socket"<<endl;
	}else{
		cout<<"Failed closing server socket"<<endl;
	}
	return 0;
}
