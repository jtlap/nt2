#ifndef FILESYSTEM_PATH_HPP
#define FILESYSTEM_PATH_HPP

#include <boost/assert.hpp>
#include <string>

namespace filesystem
{
    inline std::string parent_path( std::string const & path )
    {
        BOOST_ASSERT( path.find_last_of( "/\\" ) != std::string::npos );
        return path.substr( 0, path.find_last_of( "/\\" ) );
    }
    
    
    inline std::string filename( std::string const & path )
    {
        BOOST_ASSERT( path.find_last_of( "/\\" ) != std::string::npos );
        return path.substr( path.find_last_of( "/\\" ) + 1 );
    }
    
    inline std::string extension( std::string const & path )
    {
        std::string::size_type const dot_position( path.find_last_of( '.' ) );
        return ( dot_position != std::string::npos ) ? path.substr( dot_position ) : std::string();
    }
    
    inline bool is_absolute( std::string const & path )
    {
    #ifdef BOOST_WINDOWS_API
        return path.size() > 1 && path[1] == ':';
    #else // POSIX
        return !path.empty() && path[0] == '/';
    #endif
    }
}

#endif
