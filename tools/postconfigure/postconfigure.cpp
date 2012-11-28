#include <filesystem/filesystem.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

namespace fs = filesystem;
using std::string;

int main(int argc, char* argv[])
{
    try
    {
        std::string root;
        if(argc >= 2)
            root = argv[1];
        else
        {
            root = argv[0];
            if(!fs::is_absolute(root))
                root = fs::current_path() + '/' + root;
            root = fs::parent_path(fs::parent_path(fs::parent_path(root)));
        }

        for(fs::directory_iterator it((root + "/modules").c_str()); *it; ++it)
        {
            string path = root + "/modules/" + *it;
            if(fs::extension(path) != ".manifest")
                continue;

            std::ifstream fp(path.c_str());
            string line;

            if(!fp)
                std::cerr << "error: " << *it << " could not be opened" << std::endl;

            while(std::getline(fp, line, '\n'))
            {
                size_t pos = line.find(' ');
                if(pos == (size_t)-1 || pos == line.size())
                {
                    std::cerr << "error: invalid syntax in " << *it << std::endl;
                    continue;
                }

                string tool_name = line.substr(0, pos);
                string args = '"' + root + "/include\"" + line.substr(pos);

                string tool_path = root + "/tools/"  + tool_name + '/' + tool_name;
                string command = '"' + tool_path + "\" " + args;
#ifdef WIN32
                command = '"' + command + '"'; // yes, the Windows shell is nonsense
#endif
                if(std::system(command.c_str()) < 0)
                    std::cerr << "error: command in " << *it << " could not be executed" << std::endl;
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "error: " << e.what() << std::endl;
        return 1;
    }
    catch(...)
    {
        std::cerr << "error: uncaught exception" << std::endl;
        return 1;
    }
}
