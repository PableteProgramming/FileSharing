#include <func.hpp>

std::vector<std::string> SplitMessage(std::string message,int size){
    int curr=0;
    std::string currs="";
    std::vector<std::string> r;
    r.clear();
    for(int i=0; i<message.size();i++){
        currs+= message[i];
        curr++;
        if(curr>= size){
            curr=0;
            r.push_back(currs);
            currs="";
        }
    }
    r.push_back(currs);
    return r;
}

#ifdef __linux__
void SocketSend(int sock,std::string message){
#else
void SocketSend(SOCKET sock,std::string message){
#endif
    std::vector<std::string> splitted= SplitMessage(message,1022);
    for(int i=0; i<splitted.size()-1;i++){
        send(sock , std::string("N"+splitted[i]).c_str() , strlen(std::string("N"+splitted[i]).c_str()) , 0 );
        char temp[1]= {0};
#ifdef __linux__
        read(sock,temp,1);
#else    
        recv(sock, temp, sizeof(temp),0);
#endif
    }
    send(sock , std::string("Y"+splitted[splitted.size()-1]).c_str() , strlen(std::string("Y"+splitted[splitted.size()-1]).c_str()) , 0 );
    char temp[1]={0};
#ifdef __linux__
    read(sock,temp,1);
#else
    recv(sock,temp,sizeof(temp),0);
#endif
}

#ifdef __linux__
std::string SocketRead(int sock){
#else
std::string SocketRead(SOCKET sock){
#endif
    bool rec=true;
    std::string r="";
    while(rec){
        char buffer[1024]={0};
#ifdef __linux__
	    read(sock , buffer, 1024);
#else
	    recv(sock, buffer, sizeof(buffer),0);
#endif
        if(buffer[0]=='Y'){
            rec=false;
        }
        r+= GetFrom(std::string(buffer),1);
        send(sock,"Y",1,0);
    }
    return r;
}

std::string GetFrom(std::string s,int index){
    std::string r="";
    for(int i=index;i<s.size();i++){
        r+=s[i];
    }
    return r;
}