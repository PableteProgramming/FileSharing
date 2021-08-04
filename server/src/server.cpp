#include <server.hpp>

int main(int argc, char const *argv[])
{
	int server_info;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};
	char *hello = "Hello from server";

	server_info = socket(AF_INET, SOCK_STREAM, 0);
	// Creating socket file descriptor

	if (server_info == 0)
	{
		std::cout<<"socket failed"<<std::endl;
		exit(EXIT_FAILURE);
	}
	
	// Forcefully attaching socket to the port 8080
    int result= setsockopt(server_info, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
	if (result)
	{
		std::cout<<"setsockopt"<<std::endl;
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );
	
	// Forcefully attaching socket to the port 8080
    result= bind(server_info, (struct sockaddr *)&address, sizeof(address));
	if (result<0)
	{
		std::cout<<"bind failed"<<std::endl;
		exit(EXIT_FAILURE);
	}

    result= listen(server_info, 3);
	if (result < 0)
	{
		std::cout<<"listen"<<std::endl;
		exit(EXIT_FAILURE);
	}

    int ClientSocket= accept(server_info, (struct sockaddr *)&address,(socklen_t*)&addrlen);
	if (ClientSocket < 0)
	{
		std::cout<<"accept"<<std::endl;
		exit(EXIT_FAILURE);
	}

	read(ClientSocket , buffer, 1024);
    std::cout<<buffer<<std::endl;
	send(ClientSocket , hello , strlen(hello) , 0 );
	return 0;
}
