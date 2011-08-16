//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//============================================================================== 

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <boost/utility.hpp>

#include <iostream>
#include <fstream>
#include <cctype>

namespace fs = boost::filesystem;
namespace po = boost::program_options;
using std::vector;
using std::string;
using std::pair;

// Compiler options
po::options_description cmdline_options("Allowed options");

po::parsed_options compiler_options(int argc, char* argv[])
{    
    po::options_description generic("Generic options");
    generic.add_options()
        ("version,v",  "print version string")
        ("help,h",     "produce help message")
    ;
    
    po::options_description config("Configuration");
    config.add_options()
        ("include-path,I", po::value< vector<string> >()->composing()->default_value(vector<string>(), ""), 
                           "include path")
        ("ignore",         po::value< vector<string> >()->composing()->default_value(vector<string>(), ""), 
                           "directory names to ignore when looking for files")
        ("binary-path",    po::value<string>(), "binary path")
        ("directory",      po::value< vector<string> >()->composing()->default_value(vector<string>(), ""), 
                           "directory where files are or where they should be put")
        ("all",            po::value< vector<string> >()->composing()->default_value(vector<string>(), ""),
                           "reduce all files in previous directory to a single one")
    ;
    
    cmdline_options.add(generic).add(config);
    
    po::positional_options_description p;
    p.add("binary-path",  1);
    p.add("directory",   -1);

    return po::command_line_parser(argc, argv).
               options(cmdline_options).positional(p).run();
}

template<class T, class Allocator>
std::ostream& operator<<(std::ostream& os, const std::vector<T, Allocator>& v)
{
    for(std::size_t i=0; i!=v.size(); ++i)
        os << v[i] << ", ";
    return os;
}

struct depth_compare
{
    bool operator()(const fs::path& a0, const fs::path& a1) const
    {
        std::size_t a0_size = std::distance(a0.begin(), a0.end());
        std::size_t a1_size = std::distance(a1.begin(), a1.end());
        
        if(a0_size == a1_size)
            return a0 < a1;
        
        return a0_size < a1_size;
    }
};

typedef std::set<string, depth_compare> FileSet;

typedef std::map<fs::path, FileSet> Files;
Files find_files(const std::vector<string>& paths, const std::vector<string>& ignore, const fs::path& source_dir)
{
    Files files;
    
    fs::recursive_directory_iterator end;
    for(std::vector<string>::const_iterator it = paths.begin(); it != paths.end(); ++it)
    {
        fs::path root(*it);
        fs::path dir = root / source_dir;
        
        if(fs::exists(dir))
        {
            for(fs::recursive_directory_iterator it2(dir); it2 != end; ++it2)
            {
                if(it2->path().extension() == ".hpp")
                {
                    string s = it2->path().string().substr(it->size()+1);
                    std::replace(s.begin(), s.end(), '\\', '/');
                    files[it2->path().filename()].insert(s);
                }
                
                if(std::find(ignore.begin(), ignore.end(), it2->path().filename()) != ignore.end())
                    it2.no_push();
            }
        }
    }
    
    return files;
}

void generate_file(const fs::path& binary_path, const fs::path& output_dir, const fs::path& file_name, const FileSet& includes)
{
    string file_dir = (output_dir / file_name).string();
    fs::path file_path = binary_path / file_dir;
    
    // generate include guard name
    for(string::iterator it = file_dir.begin(); it != file_dir.end(); ++it)
    {
        if(*it == '/' || *it == '\\' || *it == '.')
            *it = '_';
        else
            *it = std::toupper(*it);
    }
    
    fs::create_directories(file_path.parent_path());
    
    std::ofstream fp(file_path.c_str());
    if(!fp)
        throw std::runtime_error("couldn't open file '" + file_path.string() + "' for writing");
    
    fp << "#ifndef " << file_dir << "_INCLUDED\n";
    fp << "#define " << file_dir << "_INCLUDED\n\n";
    for(FileSet::const_iterator it = includes.begin(); it != includes.end(); ++it)
        fp << "#include <" << *it << ">\n";
        
    fp << "\n#endif\n";
}

int main(int argc, char* argv[])
{
    try
    {
        po::parsed_options options = compiler_options(argc, argv);
        po::variables_map vm;
        
        store(options, vm);
        notify(vm);
    
        if(vm.count("help"))
        {
            std::cout << "Usage: gather_includes [options] binary-path directory [directory | --all file]...\n";
            std::cout << cmdline_options << std::endl;
            return 0;
        }

        if (vm.count("version"))
        {
            std::cout << "NT2 specialization gatherer, version 1.0" << std::endl;
            return 0;
        }
        
        if(vm.count("binary-path") == 0 || vm.count("directory") == 0)
        {
            std::cerr << "Error: not enough arguments provided." << std::endl;
            return 1;
        }
        
        vector<string> paths = vm["include-path"].as< vector<string> >();
        const vector<string>& ignore = vm["ignore"].as< vector<string> >();
        const string& binary_path = vm["binary-path"].as<string>();
        paths.push_back(binary_path);
        
        Files files;
        for(vector<po::option>::const_iterator it = options.options.begin(); it != options.options.end(); ++it)
        {
            fs::path path = it->value.front();
            
            if(it->string_key == "directory")
            {
                // regular file rather than directory
                if(path.extension() != "")
                {
                    files[path.filename()].insert(path.string());
                    continue;
                }
                
                for(Files::const_iterator it2 = files.begin(); it2 != files.end(); ++it2)
                   generate_file(binary_path, path, it2->first, it2->second);
                
                files = find_files(paths, ignore, path);
            }
            else if(it->string_key == "all")
            {
                // flatten all found files
                FileSet includes;
                for(Files::const_iterator it2 = files.begin(); it2 != files.end(); ++it2)
                    includes.insert(it2->second.begin(), it2->second.end());
                    
                generate_file(binary_path, path.parent_path().string(), path.filename(), includes);
            }
        }
        
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << "." << std::endl;
        return 1;
    }
    catch(...)
    {
        std::cerr << "Uncaught exception, aborted." << std::endl;
        throw;
        return 1;
    }
    return 0;
}
