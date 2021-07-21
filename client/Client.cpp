#include "Client.hpp"
#pragma warning(disable:4996) 
using namespace std;

Client::Client()
{
	//WSAstartup
	if (WSAStartup(MAKEWORD(2, 2), &Winsockdata) != 0)
	{
		printf("WSAstartup failed \n");
	}
	else
	{
		printf("WSAstartup successfull \n");
	}

	cout << "enter name: \n";
	cin.getline(client_name, 1024);
	strcat(client_name, ": ");

	//creating the socket
	client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (client_socket == INVALID_SOCKET)
	{
		printf("client socket creation failed \n");
	}
	else
	{
		printf("client socket creation successfull \n");
	}

	//define the address
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); // connects to any IP address used by the computer

	//connect
	if (connect(client_socket, (SOCKADDR*)&server_address, sizeof(server_address)) == SOCKET_ERROR)
	{
		printf("connecting failed \n");
	}
	else
	{
		printf("connecting successfull \n");
	}
}

void Client::Send()
{
	char Message[1024];
	char SendBuffer[1024];
	while (true)
	{
		cout << "enter text: \n";
		cin.getline(Message, 1024);
		if (strcmp(Message, "break") == 0)
			exit(0);
		strcpy(SendBuffer, client_name);
		strcat(SendBuffer, Message);
		send(client_socket, SendBuffer, strlen(SendBuffer) + 1, 0);
	}
}

void Client::recieve()
{
	char RecvBuffer[1024];
	while (true)
	{
		recv(client_socket, RecvBuffer, strlen(RecvBuffer) + 1, 0);
		printf("%s \n", RecvBuffer);
	}
}

void Client::openChat()
{
	while (true)
	{
		std::thread sending_thread = thread(&Client::Send,this);
		std::thread recieving_thread = thread(&Client::recieve,this);
		sending_thread.join();
		recieving_thread.join();
	}
}

void Client::closeClient()
{
	//close
	if (closesocket(client_socket) == SOCKET_ERROR)
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
