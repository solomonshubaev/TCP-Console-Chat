#include "PrintUtils.h"
#include <iostream>
#include <winsock.h>

void PrintUtils::printError(const char* errorMessage, bool printLastErrorMessage)
{
	if (printLastErrorMessage)
	{
		std::cerr << errorMessage << ". Error message: " << WSAGetLastError() << std::endl;
	}
	else
	{
		std::cerr << errorMessage << std::endl;
	}
}