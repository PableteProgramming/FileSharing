#include <Client.hpp>

#ifdef __linux__
Client::Client(int _sock){
#else
Client::Client(SOCKET _sock){
#endif
    shell= new Shell();
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
        if(message=="exit"){
	        SocketSend(sock,"exit");
            break;
        }
        std::vector<std::string> splitted= Split(message,' ');
        std::string command= splitted[0];
        bool found=false;
        std::string toSend="";
        splitted.erase(splitted.begin()+0);
        for(int i=0; i<commands.size();i++){
            if(commands[i].first==command){
                std::string args= Join(splitted,' ');
                found=true;
                toSend= commands[i].second(args);
                break;
            }
        }
        if(!found){
            toSend= "command "+ command + " not found !";
        }
	    SocketSend(sock,toSend);
    }
    (*exit)=true;
}