#include <func.hpp>

void SocketSend(int sock,std::string message){
	send(sock , message.c_str() , strlen(message.c_str()) , 0 );
}

std::string SocketRead(int sock){
    char buffer[1024]={0};
	read(sock , buffer, 1024);
    return std::string(buffer);
}