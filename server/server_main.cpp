
#include "server.hpp"

#pragma comment (lib, "ws2_32.lib") //including the library to the LINKER settings.

using namespace std;
int main()
{
	server serv = server();
	serv.openChat();
	serv.closeServer();

	return 0;
}
