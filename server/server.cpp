
#include "server.hpp"
using namespace std;

#pragma warning(disable:4996)



server::server()
{
	//WSAstartup
	if (WSAStartup(MAKEWORD(2, 2), &Winsockdata) != 0)
		printf("WSAstartup failed");
	else
		printf("WSAstartup successful");

	//define the address
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

	//creating the socket
	server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (server_socket == INVALID_SOCKET)
	{
		printf("server socket creation failed \n");
	}
	else
	{
		printf("server socket creation successfull \n");
	}

	//bind
	if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == SOCKET_ERROR)
	{
		printf("binding failed \n");
	}
	else
	{
		printf("binding successfull \n");
	}

	//listen
	if (listen(server_socket, 5) == SOCKET_ERROR)
		printf("listening failed \n");
	else
		printf("listening successfull \n");
		
}


void server::recieve(SOCKET client_socket)
{
	char RecvBuffer[256];
	ZeroMemory(RecvBuffer, 256);
	while (true)
	{
		
		if (recv(client_socket, RecvBuffer, 256, 0) != SOCKET_ERROR)
		{
			
			broadcast(client_socket, RecvBuffer);

		}
		
			
	}
}

void server::broadcast(SOCKET client_socket, char buffer[256])
{
	for (auto i : clients_vec)
	{
		send(i, buffer, strlen(buffer)+1, 0);
	}
}



void server::openChat()
{
	int result;
	u_long mode;
	mode = 0;
	result = ioctlsocket(server_socket, FIONBIO, &mode);//sets the socket as  blocking
	struct sockaddr_in client_addr;
	int iclient_addr = sizeof(client_addr);
	while (true)
	{
		SOCKET new_client;
		new_client = accept(server_socket, (SOCKADDR*)&client_addr, &iclient_addr);
		//accept
		if (new_client != INVALID_SOCKET)
		{
			clients_vec.push_back(new_client);
			client_threads.push_back(thread(&server::recieve, this, clients_vec.back()));
		}
		/*
		for (int i = 0;i < numOfClients;i++)
		{
			client_threads[i].join();
		}
		*/

	}
}

void server::closeServer()
{
	//close
	if (closesocket(server_socket) == SOCKET_ERROR)
	{
		printf("closing failed \n");
	}
	else
	{
		printf("closing successfull \n");
	}

	//WSAcleanup
	if (WSACleanup() == SOCKET_ERROR)
	{
		printf("cleenup failed \n");
	}
	else
	{
		printf("cleanup successfull \n");
	}
}

