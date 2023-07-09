#pragma once
#include <WinSock2.h>


class MyClass {
private:
    sockaddr_in socketAddress;

public:
    MyClass();  // Constructor
    // Add more member functions as needed

    void test();
};