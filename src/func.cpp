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

void SocketSend(int sock,std::string message){
    std::vector<std::string> splitted= SplitMessage(message,1022);
    for(int i=0; i<splitted.size()-1;i++){
        //std::cout<<"N"<<splitted[i]<<std::endl;
        send(sock , std::string("N"+splitted[i]).c_str() , strlen(std::string("N"+splitted[i]).c_str()) , 0 );
        char temp[1]={0};
        read(sock,temp,1);
    }
    //std::cout<<"Y"<<splitted[splitted.size()-1]<<std::endl;
	send(sock , std::string("Y"+splitted[splitted.size()-1]).c_str() , strlen(std::string("Y"+splitted[splitted.size()-1]).c_str()) , 0 );
    char temp[1]={0};
    read(sock,temp,1);
}

std::string SocketRead(int sock){
    bool recv=true;
    std::string r="";
    while(recv){
        char buffer[1024]={0};
	    read(sock , buffer, 1024);
        if(buffer[0]=='Y'){
            recv=false;
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