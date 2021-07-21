#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <winsock2.h>
#pragma warning(disable:4996) 
#include <iostream>
#include <thread>
#include <string>
using namespace std;

class Client
{
private:
	WSADATA Winsockdata;
	SOCKET client_socket;
	struct sockaddr_in server_address;
	char client_name[1024];

public:
	Client();
	void openChat();
	void Send();
	void recieve();
	void closeClient();
	
};
