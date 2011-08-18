//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//============================================================================== 

#include <boost/program_options.hpp>
#include <filesystem/filesystem.hpp>

#include <boost/assert.hpp>
#include <boost/foreach.hpp>
#include <boost/range/algorithm/count.hpp>
#include <boost/range/algorithm/replace.hpp>
#include <boost/range/size.hpp>
#include <boost/utility.hpp>

#include <algorithm>
#include <cctype>
#include <climits>
#include <fstream>
#include <iostream>

namespace po = boost::program_options;
namespace fs = filesystem;
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
    bool operator()( std::string const & a0, std::string const & a1 ) const
    {
        std::size_t const a0_size( boost::count( a0, '/' ) );
        std::size_t const a1_size( boost::count( a1, '/' ) );
        
        if ( a0_size == a1_size )
        {
            std::string::const_iterator       a0_position( a0.begin() );
            std::string::const_iterator       a1_position( a1.begin() );
            std::string::const_iterator const a0_end     ( a0.end  () );
            std::string::const_iterator const a1_end     ( a1.end  () );

            for ( ; ; )
            {
                std::string::const_iterator const a0_current_element_end( std::find( a0_position, a0_end, '/' ) );
                std::string::const_iterator const a1_current_element_end( std::find( a1_position, a1_end, '/' ) );

                if ( std::lexicographical_compare( a0_position, a0_current_element_end, a1_position, a1_current_element_end ) ) return true ;
                if ( std::lexicographical_compare( a1_position, a1_current_element_end, a0_position, a0_current_element_end ) ) return false;

                if ( ( a0_current_element_end == a0_end ) || ( a1_current_element_end == a1_end ) )
                {
                    return
                        ( a0_position == a1_current_element_end ) &&
                        ( a1_position != a1_current_element_end );
                }

                a0_position = a0_current_element_end + 1;
                a1_position = a1_current_element_end + 1;
            }

            BOOST_ASSERT_MSG( false, "Should not be reached." );
        }
        
        return a0_size < a1_size;
    }
};

typedef std::set<std::string, depth_compare> FileSet;
typedef std::map<std::string, FileSet      > Files  ;

void find_files_recursive_worker( Files & files, std::string const & path, std::vector<string> const & ignore )
{
    BOOST_ASSERT( fs::current_path().size() > path.size() );
    std::string cwd_relative_path( fs::current_path().c_str() + path.size() + 1 );
    #ifdef _WIN32
        boost::replace( cwd_relative_path, '\\', '/' );
    #endif

    for ( fs::directory_iterator current_dir( "." ); *current_dir; ++current_dir )
    {
        std::string const entry_name( *current_dir );
        
        if(fs::extension(entry_name) == ".hpp")
        {
            files[ entry_name ].insert( cwd_relative_path + '/' + entry_name );
        }
        else if( std::find( ignore.begin(), ignore.end(), entry_name ) == ignore.end() )
        {
            fs::current_path_saver const cps;
            
            int ec;
            fs::current_path( entry_name, ec );
            if ( !ec )
                find_files_recursive_worker( files, path, ignore );
        }
    }
}


void find_files
(
    Files                     & files,
    std::vector<string> const & paths,
    std::vector<string> const & ignore,
    std::string         const & source_dir
)
{
    BOOST_FOREACH( std::string const & path, paths )
    {
        fs::current_path_saver const cps;
        int ec;
        
        fs::current_path(path, ec);
        if( ec )
            continue;
        std::string absolute_path = fs::current_path();
            
        fs::current_path(source_dir, ec);
        if( ec )
            continue;
        
        find_files_recursive_worker( files, absolute_path, ignore );
    }
}

void generate_file( std::string const & binary_path, std::string const & output_dir, std::string const & file_name, FileSet const & includes )
{
    std::string const file_dir    ( binary_path + '/' + output_dir );
    std::string const file_path   ( file_dir    + '/' + file_name  );
    std::string       file_header ( output_dir  + '/' + file_name  );

    // uppercase include guard name
    BOOST_FOREACH( char & character, file_header )
    {
        char const chr( character );
        if ( chr == '/' || chr == '\\' || chr == '.' )
            character = '_';
        else
            character = static_cast<char>( std::toupper( chr ) );
    }

    fs::create_directories( file_dir );
    
    std::ofstream fp( file_path.c_str() );
    if(!fp)
        throw std::runtime_error( "couldn't open file '" + file_path + "' for writing" );
    
    fp << "#ifndef " << file_header << "_INCLUDED\n";
    fp << "#define " << file_header << "_INCLUDED\n\n";
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

        vector<string>         paths       = vm["include-path"].as< vector<string> >();
        vector<string> const & ignore      = vm["ignore"      ].as< vector<string> >();
        string         const & binary_path = vm["binary-path" ].as<string>();
        paths.push_back(binary_path);
        
        Files files;
        for(vector<po::option>::const_iterator it = options.options.begin(); it != options.options.end(); ++it)
        {
            std::string const & path( it->value.front() );
            if(it->string_key == "directory")
            {
                // regular file rather than directory
                if ( !fs::extension( path ).empty() )
                {
                    files[ fs::filename( path ) ].insert( path );
                    continue;
                }
                
                for(Files::const_iterator it2 = files.begin(); it2 != files.end(); ++it2)
                   generate_file(binary_path, path, it2->first, it2->second);
                
                files.clear();
                find_files( files, paths, ignore, path );
            }
            else if(it->string_key == "all")
            {
                // flatten all found files
                FileSet includes;
                for(Files::const_iterator it2 = files.begin(); it2 != files.end(); ++it2)
                    includes.insert(it2->second.begin(), it2->second.end());

                generate_file( binary_path, fs::parent_path( path ), fs::filename( path ), includes );
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
