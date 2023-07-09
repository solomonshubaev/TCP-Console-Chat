#include "MyClass.h"

MyClass::MyClass() {
    // Initialize the sockaddr_in attribute
    // For example, set it to all zeros
    memset(&this->socketAddress, 0, sizeof(this->socketAddress));
    // Additional initialization if needed
}

void MyClass::test()
{
    this->socketAddress;
}
