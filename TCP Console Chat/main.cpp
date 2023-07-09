#include "ServerManager.h"
#include "Client.h"
#include <windows.h>
#include <iostream>
#include <thread>

#define MIN_CHOICE '1'
#define MAX_CHOICE '3'

using namespace std;

void runServerThread();
void runClientThread();

int main()
{
    char inputChoice;
    do {
        cout << "Choose An Option From The Menu:" << endl;
        cout << "1. Start TCP Server - Create A Server" << endl;
        cout << "2. Start TCP Client - Connect To Server" << endl;
        cout << "3. Quit Application" << endl;
        cin >> inputChoice;
    } while (inputChoice < MIN_CHOICE || inputChoice > MAX_CHOICE);
    cout << endl;

    if (inputChoice == '1')
    {
        cout << "Starting TCP server..." << endl;
        cout << endl;
        thread serverThread(runServerThread);
        serverThread.join();
    }
    else if (inputChoice == '2')
    {
        cout << "Starting TCP client..." << endl;
        cout << endl;
        thread clientThread(runClientThread);
        clientThread.join();
    }
    else if (inputChoice == '3')
    {
        cout << "Bye Bye...";
        Sleep(1000);
        exit(EXIT_SUCCESS);
    }
    else
    {
        cout << "Something went wrong!!!" << endl;
    }
    return 0;
}

void runServerThread()
{
    cout << "Running server thread" << endl;
    ServerManager* serverManager = new ServerManager();
    serverManager->init();
    serverManager->start();
    delete serverManager;
}

void runClientThread()
{
    cout << "Running client thread" << endl;
    Client* client = new Client("Solo", 5400, "192.168.1.227");
    client->init();
    client->connectToServer();
    delete client;
}
