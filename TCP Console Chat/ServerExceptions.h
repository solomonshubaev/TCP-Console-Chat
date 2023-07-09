#pragma once
#ifndef SERVER_EXCPETION
#define SERVER_EXCEPTION

#include <exception>

class GeneralServerException: public std::exception
{
public:
	GeneralServerException(char const* const message);
};


#endif // !SERVER_EXCPETION