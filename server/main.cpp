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

void RecvAndSend(SOCKET client_socket,SOCKET client_arr[],int numofclients)
{
	    std::mutex mut;
	
		char RecvBuffer[256];
		mut.lock();
		while (true)
		{
			//recv
			if (recv(client_socket, RecvBuffer, strlen(RecvBuffer) + 1, 0) == SOCKET_ERROR)
			{
				
			}
			else
			{
				//send
				for (int i = 0;i < numofclients;i++)
				{
					//if(client_arr[i]!=client_socket)
						send(client_arr[i], RecvBuffer, strlen(RecvBuffer) + 1, 0);
				}
			}
		}
		mut.unlock();
}

	int main()
	{
		WSADATA Winsockdata;
		SOCKET server_socket;
		struct sockaddr_in server_address;

		SOCKET client_arr[5];
		struct sockaddr_in client_addresses[5];
		std::thread client_threads[5];
		int numOfClients=0;

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
		int result;
		u_long mode;
		
		while (true)
		{
			if (numOfClients!=0)
			{
				mode = 1;
				result = ioctlsocket(server_socket, FIONBIO, &mode);//sets the socket as non blocking
			}
			
			//accept
			int iclient_addr = sizeof(client_addresses[numOfClients]);
			client_arr[numOfClients] = accept(server_socket, (SOCKADDR*)&client_addresses[numOfClients], &iclient_addr);
			mode = 1;
			result = ioctlsocket(server_socket, FIONBIO, &mode);//sets the socket as non blocking
			if (client_arr[numOfClients] == EWOULDBLOCK)
			{
				client_arr[numOfClients] == NULL;	
			}
			else
			{
				numOfClients++;
				client_threads[numOfClients-1] = thread(RecvAndSend, client_arr[numOfClients-1], client_arr, numOfClients);
			}
			
			for (int i = 0;i < numOfClients;i++)
			{
				client_threads[i].join();
			}
			
		}

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


		return 0;
	}
	
