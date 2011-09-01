#ifndef FILESYSTEM_OPERATIONS_HPP
#define FILESYSTEM_OPERATIONS_HPP

#include <boost/system/api_config.hpp>
#include <boost/throw_exception.hpp>
#include <boost/assert.hpp>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <limits.h>

#ifdef BOOST_WINDOWS_API
    #include <direct.h>
    #define PATH_MAX 512 //...zzz...for some reason it does not get picked up from limits.h
    #define FILESYSTEM_MKDIR_SUFFIX
#else // POSIX
    #include <sys/stat.h>
    #include <unistd.h>
    #include <errno.h>
    #define FILESYSTEM_MKDIR_SUFFIX , 0777
#endif

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4996) // The POSIX name for this item is deprecated.
#endif

namespace filesystem
{
    inline void create_directories( std::string const & file_path )
    {
        static const char separator[] = "/\\";
    
        char directory[ PATH_MAX ];
        if( file_path.size() >= PATH_MAX )
            BOOST_THROW_EXCEPTION( std::runtime_error ( "Path " + file_path + " is too long" ) );
        *std::copy(file_path.begin(), file_path.end(), directory) = '\0';
        
        std::string::size_type end_pos = file_path.find_first_of(separator);
        if ( end_pos == 0 ) // POSIX-style root
            end_pos = file_path.find_first_of(separator, 1);
        
        for ( ; ; )
        {
            if( end_pos == std::string::npos )
                end_pos = file_path.size();
            
            char old_char = directory[end_pos];
            directory[end_pos] = '\0';
            
            if ( ( ::mkdir( directory FILESYSTEM_MKDIR_SUFFIX ) == -1 ) && ( errno != EEXIST ) )
                BOOST_THROW_EXCEPTION( std::runtime_error( std::string( "Error creating directory " ) + directory ) );
                
            directory[end_pos] = old_char;
            if( !old_char )
                break;
    
            end_pos = file_path.find_first_of(separator, end_pos+1);
        }
    }

    inline std::string current_path()
    {
        char cwd[ PATH_MAX + 1 ];
        if( ::getcwd( cwd, sizeof cwd ) == 0 )
            BOOST_THROW_EXCEPTION( std::runtime_error("Error reading current path") );
            
        return cwd;
    }
    
    inline void current_path(const char* directory, int & ec )
    {
        ec = ::chdir( directory );
    }

    inline void current_path(const char* directory)
    {
        int ec;
        current_path( directory, ec );
        if( ec )
            BOOST_THROW_EXCEPTION( std::runtime_error( std::string("Error setting ") + directory + " as current path (current path was " + current_path() + ")" ) );
    }
    
    inline void current_path(std::string const & directory, int & ec)
    {
        return current_path( directory.c_str(), ec );
    }
    
    inline void current_path(std::string const & directory)
    {
        return current_path( directory.c_str() );
    }
    
    struct current_path_saver
    {
        current_path_saver() : cwd_(current_path())
        {
        }

        ~current_path_saver()
        {
            current_path(cwd_);
        }

        char const * c_str() const
        {
            return cwd_.c_str();
        }
    
    private:
        std::string cwd_;
    };
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif
