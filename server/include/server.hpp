#include <iostream>
#include <string.h>
//#include <func.hpp>
#include <vector>
#include <Client.hpp>
#ifdef __linux__
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
const std::string OS= "L";
#else
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <WS2tcpip.h>
const std::string OS= "W";
#endif

const int PORT=8080;

void ExitClients(bool*);