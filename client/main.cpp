#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <winsock2.h>
#include <iostream>
int main()
{
	//local variable
	WSADATA Winsockdata;
	int iWsaStartup;
	int iWsaCleanup;

	//for creating the socket
	SOCKET client_socket;
	int iCloseSocket;

	//define address
	struct sockaddr_in server_address;

	//for Recv function
	int iRecv;
	char RecvBuffer[256];
	int iRecvBuffer = strlen(RecvBuffer) + 1;


	
	//WSAstartup
	iWsaStartup = WSAStartup(MAKEWORD(2, 2), &Winsockdata);
	if (iWsaStartup != 0)
	{
		printf("WSAstartup failed \n");
	}
	else
	{
		printf("WSAstartup successfull \n");
	}
	

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
	

	//recv
	iRecv = recv(client_socket, RecvBuffer, iRecvBuffer, 0);
	if (iRecv == SOCKET_ERROR)
	{
		printf("recieving failed \n");
	}
	else
	{
		printf("recieving successfull \n");
	}
	

	//close
	iCloseSocket = closesocket(client_socket);
	if (iCloseSocket == SOCKET_ERROR)
	{
		printf("closing failed \n");
	}
	else
	{
		printf("closing successfull \n");
	}
	
	
	//WSAcleanup
	iWsaCleanup = WSACleanup();
	if (iWsaCleanup == SOCKET_ERROR)
	{
		printf("cleenup failed \n");
	}
	else
	{
		printf("cleanup successfull \n");
	}
	



	return 0;
}








































	
