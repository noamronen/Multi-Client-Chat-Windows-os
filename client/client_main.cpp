#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <winsock2.h>
#pragma warning(disable:4996) 
#include <iostream>
#include <thread>
#include <string>
#include "Client.hpp"
using namespace std;

int main()
{
	Client client = Client();
	client.openChat();
	client.closeClient();
	return 0;
}
