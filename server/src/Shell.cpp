#include <Shell.hpp>

Shell::Shell(){
#ifdef __linux__
    dir="/";
#else
    dir="C:/";
#endif
}

Shell::Shell(std::string _dir){
    dir=_dir;
}