#include <ls.hpp>

std::string ls(std::string args){
    std::string dir=".";
    std::string r="";
    if(args!=""){
        std::vector<std::string> argsv= Split(args, ' ');
        if(argsv.size()>1){
            return "too many parameters passed";
        }
        dir= argsv[0];
    }
    if(!fs::exists(dir) || !fs::is_directory(dir)){
        return "Path is not a directory or it does not exist!";
    }
    for (const auto & entry : fs::directory_iterator(dir)){
        std::string path= entry.path().string();
        std::string rpath="";
        bool end=false;
        for(int i=0; i<path.size();i++){
            if(!end && path[i]!='.' && path[i]!='/' && path[i]!='\\'){
                end=true;
                //we get all the points before it
                int j=i;
                while(true){
                    j--;
                    if(path[j]=='.'){
                        rpath+= ".";
                    }
                    else{
                        break;
                    }
                }
            }
            if(end){
                rpath+= path[i];
            }
        }
        r+=rpath;
        r+="\n";
    }
    return r;
}