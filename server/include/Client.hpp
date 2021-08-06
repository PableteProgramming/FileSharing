#include <thread>
#include <func.hpp>
#include <Shell.hpp>

class Client{
private:
    Shell* shell;
    bool exit;
    std::thread* Thread;
#ifdef __linux__
    int sock;
public:
    Client(int);
    int getSock();
#else
    SOCKET sock;
public:
    Client(SOCKET);
    SOCKET getSock();
#endif
    void StartThread(bool*);
    bool GetExit();
    void JoinThread();
};

#ifdef __linux__
void ClientRead(bool*,int,bool*);
#else
void ClientRead(bool*,SOCKET,bool*);
#endif