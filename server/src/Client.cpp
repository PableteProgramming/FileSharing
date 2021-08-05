#include <Client.hpp>

#ifdef __linux__
Client::Client(int _sock){
#else
Client::Client(SOCKET _sock){
#endif
    sock= _sock;
    exit=false;
}

#ifdef __linux__
int Client::getSock(){
#else
SOCKET Client::getSock(){
#endif
    return sock;
}

void Client::StartThread(bool* running){
    Thread= new std::thread(ClientRead,running,sock,&exit);
}

bool Client::GetExit(){
    return exit;
}

void Client::JoinThread(){
    Thread->join();
}

#ifdef __linux__
void ClientRead(bool* running,int sock,bool* exit){
#else
void ClientRead(bool* running,SOCKET sock,bool* exit){
#endif
    while((*running)){
        std::string message= SocketRead(sock);
        std::string toSend= "message from client: "+message;
	    SocketSend(sock,toSend);
        if(message=="exit"){
            break;
        }
    }
    (*exit)=true;
}