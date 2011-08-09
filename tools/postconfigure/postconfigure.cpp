#include <boost/filesystem.hpp>
#include <iostream>
#include <string>
#include <cstdlib>

namespace fs = boost::filesystem;
using std::string;

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        std::cerr << "missing argument: path to NT2 installation" << std::endl;
        return 1;
    }

    fs::path root(argv[1]);

    fs::directory_iterator end;
    for(fs::directory_iterator it(root / "modules"); it != end; ++it)
    {
        if(it->path().extension() != ".manifest")
            continue;

        std::ifstream fp(it->path().string().c_str());
        string line;

        if(!fp)
            std::cerr << "error: " << it->path().filename() << " could not be opened" << std::endl;

        while(std::getline(fp, line, '\n'))
        {
            size_t pos = line.find(' ');
            if(pos == (size_t)-1 || pos == line.size())
            {
                std::cerr << "error: invalid syntax in " << it->path().filename() << std::endl;
                continue;
            }

            string tool_name = line.substr(0, pos);
            string args = (root / "include").string() + line.substr(pos);

            fs::path tool_path = root / "tools" / tool_name / tool_name;
            string command = tool_path.string() + " " + args;
            std::cout << "command " << command << std::endl;
            if(std::system(command.c_str()) < 0)
                std::cerr << "error: command in " << it->path().filename() << " could not be executed" << std::endl;
        }
    }
}