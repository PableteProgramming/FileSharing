#include <client.hpp>

int main(int argc, char const *argv[])
{
	int sock = 0;
	struct sockaddr_in serv_addr;
	char *hello = "Hello from client";
	char buffer[1024] = {0};

    sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
	{
		std::cout<<std::endl<<"Socket creation error"<<std::endl;
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	
	// Convert IPv4 and IPv6 addresses from text to binary form
    int result= inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
	if(result <=0)
	{
		std::cout<<std::endl<<"Invalid address/ Address not supported"<<std::endl;
		return -1;
	}

    result= connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if (result < 0)
	{
		std::cout<<std::endl<<"Connection Failed"<<std::endl;
		return -1;
	}

	send(sock , hello , strlen(hello) , 0 );
    read( sock , buffer, 1024);
	std::cout<<buffer<<std::endl;
	return 0;
}
