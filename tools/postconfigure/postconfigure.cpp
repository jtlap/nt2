#include <boost/filesystem.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

namespace fs = boost::filesystem;
using std::string;

int main(int argc, char* argv[])
{
    try
    {
        fs::path root;
        if(argc >= 2)
            root = argv[1];
        else
        {
            root = argv[0];
            if(!root.is_absolute())
                root = fs::initial_path() / root;
            root.remove_filename().remove_filename().remove_filename();
        }
    
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
                string args = '"' + (root / "include").string() + '"' + line.substr(pos);
    
                fs::path tool_path = root / "tools" / tool_name / tool_name;
                string command = '"' + tool_path.string() + "\" " + args;
#ifdef WIN32
                command = '"' + command + '"'; // yes, the Windows shell is nonsense
#endif
                if(std::system(command.c_str()) < 0)
                    std::cerr << "error: command in " << it->path().filename() << " could not be executed" << std::endl;
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
