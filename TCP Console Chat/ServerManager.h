#pragma once
#ifndef SERVER_MANAGER
#define SERVER_MANAGER

#include <WinSock2.h>
#include <string>
#include <vector>
#include "ClientConnection.h"

class ServerManager
{
private:
	std::vector<ClientConnection*> clientConnections;
	int maxClients;
	int port;
	SOCKET serverSocket;
	sockaddr_in socketAddress;
	WSADATA wsaData;


	std::string getSocketIpAddress(sockaddr_storage socketAddress);

public:
	ServerManager();

	~ServerManager();

	void init();

	void start(); // Start sever

	void attach(ClientConnection* observer);

	void detach(ClientConnection* observer);

	void notify(std::string nickName, std::string message);
};
#endif // SERVER_MANAGER