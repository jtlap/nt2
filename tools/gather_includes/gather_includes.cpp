//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//============================================================================== 

#include <filesystem/filesystem.hpp>

#include <boost/assert.hpp>
#include <boost/foreach.hpp>
#include <boost/range/algorithm/count.hpp>
#include <boost/range/algorithm/replace.hpp>
#include <boost/range/size.hpp>
#include <boost/utility.hpp>

#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>

namespace fs = filesystem;

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
                        ( a0_position == a0_current_element_end ) &&
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

void find_files_recursive_worker( Files & files, std::string const & path, std::set<std::string> const & ignore, int max )
{
    if(max == 0)
        return;

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
        else if( ignore.find(entry_name) == ignore.end() )
        {
            fs::current_path_saver const cps;
            
            int ec;
            fs::current_path( entry_name, ec );
            if ( !ec )
                find_files_recursive_worker( files, path, ignore, max-1 );
        }
    }
}


void find_files
(
    Files                          & files,
    std::vector<std::string> const & paths,
    std::set<std::string>    const & ignore,
    std::string              const & source_dir,
    int                              max
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
        
        find_files_recursive_worker( files, absolute_path, ignore, max );
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
        if(argc < 3)
        {
            std::cout << "Usage: gather_includes [options] binary-path directory [directory | --all file]..." << std::endl;
            return 1;
        }

        std::vector<std::string> paths;
        std::set<std::string>    ignore;
        std::string              binary_path;
        int                      write = 0;
        int                      max = -1;
        
        Files files;
        for(int i = 1; i != argc; ++i)
        {
            // directory names to ignore
            if(!std::strcmp(argv[i], "--ignore") && i != argc-1)
            {
                ignore.insert(argv[i+1]);
                ++i;
                continue;
            }
            
            // include directories, two argument syntax
            if(!std::strcmp(argv[i], "-I") && i != argc-1)
            {
                paths.push_back(argv[i+1]);
                ++i;
                continue;
            }
            
            if(!std::strcmp(argv[i], "--max") && i != argc-1)
            {
                max = strtol(argv[i+1], NULL, 10);
                ++i;
                continue;
            }
            
            // include directories, one argument syntax
            if(!std::strncmp(argv[i], "-I", 2))
            {
                paths.push_back(argv[i] + 2);
                continue;
            }
            
            if(!std::strcmp(argv[i], "--out"))
            {
                write = 2;
                continue;
            }
            
            // first argument is binary path
            if( binary_path.empty() )
            {
                binary_path = argv[i];
                paths.push_back(binary_path);
                continue;
            }
            
            // other arguments are directory or file names
            std::string const & path( argv[i] );
            
            // regular file end with an extension
            bool regular_file = !fs::extension( path ).empty();
            
            if(write == 2)
            {
                write = 1;
              
                // flatten all found files
                if(regular_file)
                {
                    FileSet includes;
                    for(Files::const_iterator it2 = files.begin(); it2 != files.end(); ++it2)
                        includes.insert(it2->second.begin(), it2->second.end());

                    generate_file( binary_path, fs::parent_path( path ), fs::filename( path ), includes );
                }
                
                // generate one file per entry
                else
                {
                    for(Files::const_iterator it2 = files.begin(); it2 != files.end(); ++it2)
                        generate_file(binary_path, path, it2->first, it2->second);
                }
                
                continue;
            }
            
            if(write == 1)
            {
                write = 0;
                files.clear();
            }
  
            if(regular_file)
                files[ fs::filename( path ) ].insert( path );
            else
                find_files( files, paths, ignore, path, max );
            
            max = -1;
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
