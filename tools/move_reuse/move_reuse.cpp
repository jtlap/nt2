#include <filesystem/filesystem.hpp>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <iostream>

namespace fs = filesystem;

bool equal_streams(std::istream& s1, std::istream& s2)
{
    typedef std::istreambuf_iterator<char, std::char_traits<char> > iterator;
    iterator begin1(s1.rdbuf());
    iterator begin2(s2.rdbuf());
    iterator end;
    
    for(; begin1 != end && begin2 != end; ++begin1, ++begin2)
        if(*begin1 != *begin2)
            return false;
            
    return begin1 == end && begin2 == end;
}

void move_file(std::string const& old, std::string const& new_)
{
    {
        std::ifstream fp1(new_.c_str());
        if(!fp1)
            throw std::runtime_error( "couldn't open file '" + new_ + "' for reading" );
    
        std::ifstream fp2(old.c_str());
        if(fp2 && equal_streams(fp1, fp2))
            return;
    }

    fs::create_directories(fs::parent_path(old));
    fs::rename(new_.c_str(), old.c_str());
}

int delete_files(std::string const& old, std::string const& new_)
{
    if(fs::is_symlink(old.c_str()))
    {
      fs::remove(old.c_str());
      return 0;
    }

    int count = 0;
    for ( fs::directory_iterator current_dir(old.c_str()); *current_dir; ++current_dir )
    {
        std::string const entry_name( *current_dir            );
        std::string const      entry( old + '/' + entry_name  );
        std::string const  new_entry( new_ + '/' + entry_name );

        if(fs::extension(entry_name) == ".hpp")
        {
            if(fs::exists(new_entry.c_str()))
                count++;
            else
                fs::remove(entry.c_str());
        }
            
        if(fs::is_directory(entry))
            count += delete_files(entry, new_entry);
    }

    if(!count)
        fs::remove(old.c_str());

    return count;
}

void move_files(std::string const& old, std::string const& new_)
{
    for ( fs::directory_iterator current_dir(new_.c_str()); *current_dir; ++current_dir )
    {
        std::string const entry_name( *current_dir            );
        std::string const      entry( old + '/' + entry_name  );
        std::string const  new_entry( new_ + '/' + entry_name );
        
        if(fs::extension(entry_name) == ".hpp")
            move_file(entry, new_entry);
            
        if(fs::is_directory(new_entry))
            move_files(entry, new_entry);
    }
}

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        std::cout << "usage: " << argv[0] << " <new> <old>" << std::endl;
        return EXIT_FAILURE;
    }

    if(fs::exists(argv[2]))
        delete_files(argv[2], argv[1]);

    if(fs::exists(argv[1]))
    {
        move_files(argv[2], argv[1]);
        fs::remove_all(argv[1]);
    }
}
