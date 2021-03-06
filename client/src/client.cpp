#include <client.hpp>

int main(int argc, char const *argv[])
{
	if(argc<=1){
		std::cout<<"Please input the ip to connect"<<std::endl;
		return 1;
	}
	std::string ip= std::string(argv[1]);
    bool running=false;
#ifdef __linux__
	int sock = 0;
	struct sockaddr_in serv_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
	{
		std::cout<<std::endl<<"Socket creation error"<<std::endl;
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	
	// Convert IPv4 and IPv6 addresses from text to binary form
    int result= inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr);
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
#else
	#pragma comment (lib, "Ws2_32.lib")
	#pragma comment (lib, "Mswsock.lib")
	#pragma comment (lib, "AdvApi32.lib")
	WSADATA wsaData;
	SOCKET sock = INVALID_SOCKET;
	struct addrinfo* result = NULL;
	struct addrinfo* ptr = NULL;
	struct addrinfo hints;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("Error when init WSAStartup!\n");
		exit(1);
	}
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	iResult = getaddrinfo(ip.c_str(), std::to_string(PORT).c_str(), &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (sock == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			return 1;
		}

		// Connect to server.
		iResult = connect(sock, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(sock);
			sock = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (sock == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
		return 1;
	}
#endif

	std::string os= SocketRead(sock);
	SocketSend(sock,"K");
    running=true;
    while(running){
        std::string message;
        std::cout<<"send > ";
        std::getline(std::cin,message);
		if(message!=""){
			bool clear=false;
			if(os=="W"){
				if(message=="cls"){
					clear=true;
				}
			}
			else if(os=="L"){
				if(message=="clear"){
					clear=true;
				}
			}
			if(!clear){
				SocketSend(sock,message);
				std::string r= SocketRead(sock);
				if(message=="exit"){
					return 0;
				}
				std::cout<<r<<std::endl;
			}
			else{
				clearScreen();
			}
		}
    }
	return 0;
}

void clearScreen(){
#ifdef __linux__
	system("clear");
#else
	system("cls");
#endif
}