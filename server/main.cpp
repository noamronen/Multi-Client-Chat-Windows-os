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
	SOCKET server_socket;
	int iCloseSocket;

	//define the addresses
	struct sockaddr_in client_address;
	struct sockaddr_in server_address;
	int iClient_address = sizeof(client_address);

	//for bind function
	int iBind;

	//for listen function
	int iListen;

	//for the accept function
	SOCKET client_socket;

	//for the send function
	int iSend;
	char server_response[256] = "you reached the server";
	int iServer_response = strlen(server_response) + 1;

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
	

	//define the address
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); // connects to any IP address used by the computer

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
	iBind = bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));
	if (iBind == SOCKET_ERROR)
	{
		printf("binding failed \n");
	}
	else
	{
		printf("binding successfull \n");
	}
	

	//listen
	iListen = listen(server_socket, 2);
	if (iListen == SOCKET_ERROR)
	{
		printf("listening failed \n");
	}
	else
	{
		printf("listening successfull \n");
	}
	

	//accept
	client_socket = accept(server_socket, (SOCKADDR*)&client_address, &iClient_address);
	if (client_socket == INVALID_SOCKET)
	{
		printf("accepting failed \n");
	}
	else
	{
		printf("accepting successfull \n");
	}
	

	//send
	iSend = send(client_socket, server_response, iServer_response, 0);
	if (iSend == SOCKET_ERROR)
	{
		printf("sending failed \n");
	}
	else
	{
		printf("sending successfull \n");
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
	iCloseSocket = closesocket(server_socket);
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


