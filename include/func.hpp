#include <string>
#include <string.h>
#include <vector>
#include <iostream>

#ifdef __linux__
#include <unistd.h>
#include <sys/socket.h>
#else
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#endif

#ifdef __linux__
void SocketSend(int,std::string);
std::string SocketRead(int);
#else
void SocketSend(SOCKET,std::string);
std::string SocketRead(SOCKET);
#endif
std::vector<std::string> SplitMessage(std::string,int);
std::string GetFrom(std::string,int);
std::vector<std::string> Split(std::string,char);
std::string Join(std::vector<std::string>,char);