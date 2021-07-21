#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <winsock2.h>
#include <iostream>
#include <thread>
#include<WS2tcpip.h>
#include<vector>
#include <fcntl.h>
#include <mutex>
using namespace std;

#pragma warning(disable:4996)

class server
{
private:
	WSADATA Winsockdata;
	SOCKET server_socket;
	std::vector<SOCKET> clients_vec;
	//SOCKET clients_arr[5];
	std::vector<std::thread>client_threads;
	//std::thread client_threads[5];
	struct sockaddr_in server_address;
	int numOfClients = 0;
public:
	server();
	void broadcast(SOCKET client_socket, char buffer[1024]);
	void recieve(SOCKET client_socket);
	void openChat();
	void closeServer();
};
