#include <client.hpp>

int main(int argc, char const *argv[])
{
	int sock = 0;
	struct sockaddr_in serv_addr;
    bool running=false;

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

    running=true;
    while(running){
        std::string message;
        std::cout<<"send > ";
        std::getline(std::cin,message);
        SocketSend(sock,message);
        std::string r= SocketRead(sock);
        std::cout<<r<<std::endl;
    }
	return 0;
}
