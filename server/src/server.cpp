#include <server.hpp>

int main(int argc, char const *argv[])
{
    bool running=false;
#ifdef __linux__
	int server_info;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);

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
#else
	#define WIN32_LEAN_AND_MEAN
	#pragma comment (lib, "Ws2_32.lib")

	WSADATA wsaData;
	int iResult;

	SOCKET server_info = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	struct addrinfo* result = NULL;
	struct addrinfo hints;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, std::to_string(PORT).c_str(), &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// Create a SOCKET for connecting to server
	server_info = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (server_info == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	// Setup the TCP listening socket
	iResult = bind(server_info, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(server_info);
		WSACleanup();
		return 1;
	}

	freeaddrinfo(result);

	iResult = listen(server_info, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(server_info);
		WSACleanup();
		return 1;
	}
#endif
    running=true;

#ifdef __linux__
	int ClientSocket= accept(server_info, (struct sockaddr *)&address,(socklen_t*)&addrlen);
	if (ClientSocket < 0)
	{
		std::cout<<"accept"<<std::endl;
		exit(EXIT_FAILURE);
	}
#else
	ClientSocket = accept(server_info, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET) {
		printf("accept failed with error: %d\n", WSAGetLastError());
		closesocket(server_info);
		WSACleanup();
		return 1;
	}
#endif

    while(running){
        std::string message= SocketRead(ClientSocket);
        std::string toSend= "message from client: "+message;
	    SocketSend(ClientSocket,toSend);
    }

	return 0;
}
