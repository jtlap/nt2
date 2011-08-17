#ifndef FILESYSTEM_PATH_HPP
#define FILESYSTEM_PATH_HPP

#include <boost/system/api_config.hpp>
#include <boost/assert.hpp>
#include <string>

#ifdef BOOST_WINDOWS_API
    #include <stdlib.h>
#else // POSIX
    #include <libgen.h>
    #include <string.h>
#endif

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4996) // The POSIX name for this item is deprecated.
#endif

namespace filesystem
{
    inline std::string parent_path( std::string const & path )
    {
        return path.substr( 0, path.find_last_of( '/' ) );
    }
    
    
    inline std::string filename( std::string const & path )
    {
        #ifdef BOOST_WINDOWS_API
            char base_file_name[ _MAX_FNAME ];
            char extension     [ _MAX_FNAME ];
            ::_splitpath( path.c_str(), NULL, NULL, base_file_name, extension );
            return std::string( base_file_name ) + '.' + extension;
        #else // POSIX
            return ::basename( ::strdup( path.c_str() ) );
        #endif // OS API
    }
    
    
    inline std::string extension( std::string const & path )
    {
        #ifdef BOOST_WINDOWS_API
            char extension[ _MAX_FNAME ];
            ::_splitpath( path.c_str(), NULL, NULL, NULL, extension );
            BOOST_ASSERT( extension[ 0 ] == '.' );
            return extension + 1;
        #else // POSIX
            std::string::size_type const dot_position( path.find_last_of( '.' ) );
            return ( dot_position != std::string::npos ) ? path.substr( dot_position ) : std::string();
        #endif // OS API
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif
