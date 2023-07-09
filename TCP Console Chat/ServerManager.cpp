#include "ServerManager.h"
#include "ServerExceptions.h"
#include "PrintUtils.h"
#include <Ws2tcpip.h>
#include <iostream>
#define MAX_CLIENTS 5
#define PORT 5400
#define ENABLE 1

ServerManager::ServerManager()
{
	std::cout << "Initializing ServerManager..." << std::endl;
	this->maxClients = MAX_CLIENTS;
	this->port = PORT;
	this->serverSocket = INVALID_SOCKET;
	memset(&this->socketAddress, 0, sizeof(this->socketAddress));
}


ServerManager::~ServerManager()
{
	closesocket(this->serverSocket);
	WSACleanup();
}

void ServerManager::resetBuffer()
{
	memset(&this->buffer, 0, sizeof(this->buffer));
}

std::string ServerManager::getSocketIpAddress(sockaddr_storage socketAddress)
{
	char ipAddressString[INET_ADDRSTRLEN];
	const sockaddr_in* incomingConnectionAddress = reinterpret_cast<const sockaddr_in*>(&socketAddress);
	const char* result = inet_ntop(AF_INET, &(incomingConnectionAddress->sin_addr), ipAddressString, INET_ADDRSTRLEN);
	if (result != nullptr)
	{
		return std::string(result);
	}

	return "";
}

void ServerManager::init()
{
	const int enableReuseAddr = ENABLE;

	try
	{
		if (WSAStartup(MAKEWORD(2, 2), &this->wsaData) != 0) {
			throw GeneralServerException("WSAStartup failed");
		}

		if ((this->serverSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		{
			throw GeneralServerException("Failed to create socket");
		}

		if (setsockopt(this->serverSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&enableReuseAddr, sizeof(enableReuseAddr)) < 0)
		{
			throw GeneralServerException("Failed to set socket");
		}
		this->socketAddress.sin_family = AF_INET;
		this->socketAddress.sin_addr.s_addr = INADDR_ANY;
		this->socketAddress.sin_port = htons(this->port);

		if (bind(this->serverSocket, (const sockaddr*)&this->socketAddress, sizeof(this->socketAddress)) < 0)
		{
			throw GeneralServerException("Failed to bind");
		}

		std::cout << "Server was initialized successfully, Server bound to port: " << this->port << " successfully." << std::endl << std::endl;
	}
	catch (const GeneralServerException& generalServerException)
	{
		PrintUtils::printError(generalServerException.what());
	}
	catch (const std::exception& ex)
	{
		PrintUtils::printError(ex.what());
	}

}

void ServerManager::start()
{
	const int enableReuseAddr = ENABLE;
	if (this->serverSocket == INVALID_SOCKET)
		throw GeneralServerException("Server socket is invalid");
	
	try
	{
		sockaddr_storage incomingConnectionAddressStorage;
		memset(&incomingConnectionAddressStorage, 0, sizeof(incomingConnectionAddressStorage));
		int addressSize;
		SOCKET incomingSocket;
		while (true)
		{
			// Do it in another thread and another method of course
			if (listen(this->serverSocket, 10) > -1)
			{
				// Declare all the variables outside of while loop!!!
				
				addressSize = sizeof(incomingConnectionAddressStorage);
				incomingSocket = accept(this->serverSocket, (sockaddr*)&incomingConnectionAddressStorage, &addressSize);
				if (incomingSocket < 0)
				{
					PrintUtils::printError("Error while accepting socket");
				}
				else // Socket != -1
				{
					if (incomingConnectionAddressStorage.ss_family == AF_INET)
					{
						std::cout << "Accepting socket connection from IP address: " << this->getSocketIpAddress(incomingConnectionAddressStorage) << std::endl;
						
						// TEST ONLY
						int valread = recv(incomingSocket, this->buffer, sizeof(this->buffer) - 1, 0);
						if (valread < 0)
						{
							PrintUtils::printError("Error while reading");
						}
						std::cout << "Bytes received: " << valread << std::endl;
						printf("%s\n", this->buffer);
						this->resetBuffer();
						printf("After reset: %s\n", this->buffer);
					}
					else
					{
						PrintUtils::printError("Error while accepting socket");
					}
					
				}
				
			}
			else
			{
				PrintUtils::printError("Error in listen");
			}

		}
	}
	catch (const GeneralServerException& generalServerException)
	{
		PrintUtils::printError(generalServerException.what());
	}
	catch (const std::exception& ex)
	{
		PrintUtils::printError(ex.what());
	}
}
