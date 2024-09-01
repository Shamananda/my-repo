#include "client.hpp"

Client::Client(){}

Client::Client(int16_t iPort):iClientPort(iPort){}

Client::~Client(){}


int8_t Client::iInitClientSocket(int8_t iDomain=AF_INET, int8_t iType=SOCK_STREAM, int8_t iProtocol=0){
	iClientSock = socket(iDomain, iType, iProtocol);

	if(iClientSock == -1){
		cerr<<"Failed Socket creation";
		return -1;
	}

	serverAddr.sin_family = iDomain;
	serverAddr.sin_port = htons(iClientPort);
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	
	int8_t iClientFd = connect(iClientSock, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(iClientFd<0){
		cerr<<"Failed socket connectio";
		return -1;
	}
	return 0;
}

int8_t Client::iSendData(){
	char buffer[1024] = "Hello world from client";
	int8_t retVal = send(iClientSock, buffer, sizeof(buffer), 0);
	cout<<"Sent: "<<buffer<<endl;
	return retVal;	
}

int8_t Client::iReceiveData(){
	char buffer[1024] = {0};
	int8_t valRead = read(iClientSock, buffer, sizeof(buffer));
	cout<<"Read: "<<buffer<<endl;
	return valRead;
}

int8_t Client::iCloseConnection(){
	return close(iClientSock); //return 0 if success else -1
}

int main(){
	Client objClient(11115);
	if(objClient.iInitClientSocket() == 0){
		cout<<"Socket Connection Established"<<endl;
		if(objClient.iReceiveData() == 0){
			cout<<"Receive Successfully"<<endl;
			if(objClient.iSendData() == 0){
				cout<<"Sent Successfully"<<endl;
			}
		}
	}else{
		cout<<"Failed connection Established"<<endl;
	}
	if(objClient.iCloseConnection() == 0){
		cout<<"Close socket Successfully"<<endl;
	}else{
		cout<<"Error Close Connection"<<endl;
	}
	
	return 0;
}
