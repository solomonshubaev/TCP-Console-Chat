#include "Client.h"
#include "PrintUtils.h"
#include <Ws2tcpip.h>
#include <iostream>


Client::Client(const std::string nickName, int serverPort, std::string serverIP)
{
	this->serverPort = serverPort;
	this->nickName = nickName;
	this->socketToServer = INVALID_SOCKET;
	this->serverIP = serverIP;
	memset(&this->serverAddress, 0, sizeof(this->serverAddress));
}

Client::~Client()
{
	closesocket(this->socketToServer);
	WSACleanup();
}

void Client::init()
{
	try
	{
		if (WSAStartup(MAKEWORD(2, 2), &this->wsaData) != 0) {
			throw std::exception("WSAStartup failed");
		}

		if ((this->socketToServer = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		{
			throw std::exception("Failed to create socket");
		}

		this->serverAddress.sin_family = AF_INET;
		this->serverAddress.sin_port = htons(this->serverPort);

		if (inet_pton(AF_INET, this->serverIP.c_str(), &this->serverAddress.sin_addr) <= 0)
		{
			throw std::exception("Failed to convert ip address to binary");
		}
	}
	catch (const std::exception& ex)
	{
		PrintUtils::printError(ex.what());
	}
}

void Client::connectToServer()
{
	try
	{
		if (connect(this->socketToServer, (struct sockaddr*)&this->serverAddress, sizeof(this->serverAddress)) < 0)
		{
			throw std::exception("Failed to connect to server");
		}

		//TEST ONLY
		const char* testString = "Hello From CLIENT";
		std::cout << "Message: " << testString << ". Length: " << strlen(testString) << std::endl;
		send(this->socketToServer, testString, strlen(testString), 0);
		printf("Sent a message to the server\n");
	}
	catch (const std::exception& ex)
	{
		PrintUtils::printError(ex.what());
	}
}
