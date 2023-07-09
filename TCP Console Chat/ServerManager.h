#pragma once
#ifndef SERVER_MANAGER
#define SERVER_MANAGER

#include <WinSock2.h>
#include <string>

#define BUFFER_SIZE 2048
class ServerManager
{
private:
	int maxClients;
	int port;
	char buffer[BUFFER_SIZE] = { 0 }; // important to reset!
	SOCKET serverSocket;
	sockaddr_in socketAddress;
	WSADATA wsaData;

	void resetBuffer();

	std::string getSocketIpAddress(sockaddr_storage socketAddress);

public:
	ServerManager();

	~ServerManager();

	void init();

	void start(); // Start sever
};
#endif // SERVER_MANAGER