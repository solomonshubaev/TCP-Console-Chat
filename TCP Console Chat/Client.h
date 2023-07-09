#pragma once
#ifndef CLIENT
#define CLIENT
#include <string>
#include <WinSock2.h>
#define BUFFER_SIZE 2048

class Client
{
private:
	std::string nickName;
	std::string serverIP;
	char buffer[BUFFER_SIZE] = { 0 };
	SOCKET socketToServer;
	sockaddr_in serverAddress;
	WSADATA wsaData;
	int serverPort;

public: 
	Client(const std::string nickName, int serverPort, std::string serverIP);

	~Client();

	void init();

	void connectToServer();
};

#endif // CLIENT