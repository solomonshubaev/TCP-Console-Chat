#include "ClientConnection.h"
#include <thread>
#include <iostream>
#include "PrintUtils.h"
#include "ServerManager.h"



ClientConnection::ClientConnection(std::string nickName, SOCKET clientSocket, ServerManager* serverManager)
{
	this->serverManager = serverManager;
	this->nickName = nickName;
	this->clientSocket = clientSocket;
	this->resetBuffer();
}

void ClientConnection::start()
{
	this->readThread = std::thread(&ClientConnection::readThreadMethod, this);
	//this->writeThread = std::thread(&ClientConnection::writeThreadMethod, this);
	this->readThread.join();
	//this->writeThread.join();
}


void ClientConnection::resetBuffer()
{
	memset(&this->buffer, 0, sizeof(this->buffer));
}

void ClientConnection::printMessage()
{
	std::cout << this->nickName << ": " << this->buffer << std::endl;
}


void ClientConnection::update(std::string messageToSend)
{
	send(this->clientSocket, messageToSend.c_str(), messageToSend.length(), 0);
}

void ClientConnection::readThreadMethod()
{
	try
	{
		int receivedBytes;
		while (true)
		{
			receivedBytes = recv(this->clientSocket, this->buffer, sizeof(this->buffer) - 1, 0);
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
			this->printMessage();
			this->serverManager->notify(this->nickName, this->buffer);
			this->resetBuffer();
		}
	}
	catch (const std::exception& ex)
	{
		PrintUtils::printError(ex.what());
	}
}

void ClientConnection::writeThreadMethod()
{
	// I dont need it as the write will happen via update, but it can be faster if we do it via multithreading
	// use data structure like queue to handle thread and update from subject
}