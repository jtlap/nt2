#ifndef FILESYSTEM_OPERATIONS_HPP
#define FILESYSTEM_OPERATIONS_HPP

#include <boost/system/api_config.hpp>
#include <boost/assert.hpp>
#include <string>
#include <stdexcept>
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
        // Assume we are working with absolute paths and strip the "root" element.
        #ifdef BOOST_WINDOWS_API
            BOOST_ASSERT( file_path[ 1 ] == ':' );
            std::string::const_iterator current_element( file_path.begin() + 3 );
        #else // POSIX
            BOOST_ASSERT( file_path[ 0 ] == '/' );
            std::string::const_iterator current_element( file_path.begin() + 1 );
        #endif // OS API
        std::string::const_iterator const path_end( file_path.begin() + file_path.find_last_of( '/' ) );
        BOOST_ASSERT( path_end        < file_path.end() );
        BOOST_ASSERT( current_element < path_end        );
    
        for ( ; ; )
        {
            std::string::const_iterator const current_element_end( std::find( current_element, path_end, '/' ) );
            char directory[ PATH_MAX ];
            BOOST_ASSERT( current_element_end - current_element < sizeof( directory ) );
            *std::copy( current_element, current_element_end, directory ) = '\0';
            if ( ( ::mkdir( directory FILESYSTEM_MKDIR_SUFFIX ) == -1 ) && ( errno != EEXIST ) )
                throw std::runtime_error( std::string( "Error creating a directory " ) + directory );
    
            if ( current_element_end == path_end )
                break;
    
            current_element = current_element_end + 1;
        }
    }

    inline std::string current_path()
    {
        char cwd[ PATH_MAX + 1 ];
        if( ::getcwd( cwd, sizeof cwd ) == 0 )
            throw std::runtime_error("Error reading current path");
            
        return cwd;
    }

    inline void current_path(const char* directory)
    {
        if( ::chdir( directory ) != 0 )
            throw std::runtime_error( std::string("Error setting ") + directory + " as current path" );
    }
    
    inline void current_path(std::string const & directory)
    {
        return current_path( directory.c_str() );
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif
