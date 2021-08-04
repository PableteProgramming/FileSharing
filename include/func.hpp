#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <vector>
#include <iostream>

void SocketSend(int,std::string);
std::string SocketRead(int);
std::vector<std::string> SplitMessage(std::string,int);
std::string GetFrom(std::string,int);