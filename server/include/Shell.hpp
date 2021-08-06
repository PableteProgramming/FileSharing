#include <string>
#include <vector>
#include <ls.hpp>

class Shell{
private:
    std::string dir;
public:
    Shell();
    Shell(std::string);
};

//////////////////////////////////
//          CMD COMMANDS        //
//////////////////////////////////

typedef std::string (*funcPtr)(std::string);

std::string ls(std::string);

const std::vector<std::pair<std::string, funcPtr>> commands = {
	std::make_pair("ls",&ls)
};