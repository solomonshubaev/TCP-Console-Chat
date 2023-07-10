#include "Client.h"
#include "PrintUtils.h"
#include <Ws2tcpip.h>
#include <iostream>
#include <thread>


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

		this->readThread = std::thread(&Client::readThreadMethod, this);
		this->writeThread = std::thread(&Client::writeThreadMethod, this);
		this->readThread.join();
		this->writeThread.join();
	}
	catch (const std::exception& ex)
	{
		PrintUtils::printError(ex.what());
	}
}

void Client::readThreadMethod()
{
	try
	{
		int receivedBytes;
		while (true)
		{
			receivedBytes = recv(this->socketToServer, this->buffer, sizeof(this->buffer) - 1, 0);
			if (receivedBytes < 0)
			{
				throw std::exception("Error while reading bytes from socket stream");

			}
			else if (receivedBytes == 0)
			{
				std::cout << "Received 0 bytes from socket stream, leaving the chat." << std::endl;
				break; // temporary
				// need close connection and remove from managed thread (connections)
			}
			std::cout << this->buffer << std::endl;
			memset(&this->buffer, 0, sizeof(this->buffer));
		}
	}
	catch (const std::exception& ex)
	{
		PrintUtils::printError(ex.what());
		// handle exit
	}
}

void Client::writeThreadMethod()
{
	try
	{
		std::string message;
		while (true)
		{
			getline(std::cin, message);
			send(this->socketToServer, message.c_str(), message.length(), 0);
		}
	}
	catch (const std::exception& ex)
	{
		PrintUtils::printError(ex.what());
		// if needed handle exit
	}
}
