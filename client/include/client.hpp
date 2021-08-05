#ifdef __linux__
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#else
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#endif
#include <string.h>
#include <iostream>
#include <func.hpp>

const int PORT= 8080;