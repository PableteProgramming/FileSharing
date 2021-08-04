#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>

void SocketSend(int,std::string);
std::string SocketRead(int);