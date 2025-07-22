#include "server/server.hpp"

int main()
{
	c_server server(420);
	server.start();
	return 0;
}