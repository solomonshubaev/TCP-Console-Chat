#pragma once
#ifndef CLIENT_CONNECTION
#define CLIENT_CONNECTION
#include <thread>
#include <string>
#include <WinSock2.h>
#define BUFFER_SIZE 2048

class ServerManager; // forward declaration

class ClientConnection
{

private:
	ServerManager* serverManager; // should be singleton

	std::thread readThread;
	//std::thread writeThread;
	std::string nickName;
	SOCKET clientSocket;
	char buffer[BUFFER_SIZE] = { 0 }; // important to reset!

	void resetBuffer();

	void printMessage();

	void readThreadMethod();

	void writeThreadMethod();


public:
	// think of adding startThread and stopThread

	ClientConnection(std::string nickName, SOCKET clientSocket, ServerManager* serverManager);

	void start();

	void update(std::string messageToSend);

	std::string getNickName() { return this->nickName; };

};
#endif // CLIENT_CONNECTION

