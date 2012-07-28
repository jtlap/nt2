#ifndef FILESYSTEM_OPERATIONS_HPP
#define FILESYSTEM_OPERATIONS_HPP

#include <boost/system/api_config.hpp>
#include <boost/throw_exception.hpp>
#include <boost/assert.hpp>
#include <filesystem/directory_iterator.hpp>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <limits.h>
#include <stdio.h>

#ifdef BOOST_WINDOWS_API
    #include <direct.h>
    #define PATH_MAX 512 //...zzz...for some reason it does not get picked up from limits.h
    #define FILESYSTEM_MKDIR_SUFFIX
    #include <errno.h>
#else // POSIX
    #include <sys/stat.h>
    #include <unistd.h>
    #define FILESYSTEM_MKDIR_SUFFIX , 0777
    #include <errno.h>
#endif


#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4996) // The POSIX name for this item is deprecated.
#endif

namespace filesystem
{
    inline bool exists( const char* file_path )
    {
    #ifdef BOOST_WINDOWS_API
        return GetFileAttributes(file_path) != INVALID_FILE_ATTRIBUTES;
    #else
        struct stat s;
        return stat(file_path, &s) == 0;
    #endif
    }

    inline void create_directories( std::string const & file_path )
    {
        static const char separator[] = "/\\";

        if(file_path.empty())
            return;

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

    inline bool is_directory( std::string const & file_path )
    {
        int ec;

        std::string path = current_path();
        current_path(file_path, ec);
        current_path(path);

        return ec == 0;
    }

    inline bool remove( const char* file_path, int& ec )
    {
        // TODO: implement error reporting
        ec = 0;

#ifdef BOOST_WINDOWS_API
        if(is_directory(file_path))
            return ::RemoveDirectory(file_path) ? true : false;
        else
            return ::DeleteFileA(file_path) ? true : false;
#else

        return ::remove(file_path) == 0;
#endif
    }

namespace details
{
    inline int remove_all_rec( int& ec )
    {
        int count = 0;
        for ( directory_iterator current_dir( "." ); *current_dir; ++current_dir )
        {
            if(!is_directory(*current_dir))
            {
                count += remove(*current_dir, ec);
                continue;
            }

            {
                current_path_saver const cps;
                current_path(*current_dir);
                count += remove_all_rec(ec);
            }

            count += remove(*current_dir, ec);
        }
        return count;
    }
}

    inline int remove_all( const char* file_path, int& ec )
    {
        if(!is_directory(file_path))
            return remove(file_path, ec);

        int count;
        {
            current_path_saver const cps;
            current_path(file_path);
            count = details::remove_all_rec(ec);
        }

        return count + remove(file_path, ec);
    }

    inline bool remove( const char* file_path )
    {
        int ec;
        bool result = remove(file_path, ec);

        if( ec )
            BOOST_THROW_EXCEPTION( std::runtime_error( std::string("Error removing ") + file_path ) );

        return result;
    }

    inline int remove_all( const char* file_path )
    {
        int ec;
        int result = remove_all(file_path, ec);

        if( ec )
            BOOST_THROW_EXCEPTION( std::runtime_error( std::string("Error removing recursively ") + file_path ) );

        return result;
    }

    inline void rename(const char* from, const char* to, int& ec)
    {
    #ifdef BOOST_WINDOWS_API
        if(exists(to))
            remove(to, ec);
    #endif
        ec = ::rename(from, to) ? errno : 0;
    }

    inline void rename(const char* from, const char* to)
    {
        int ec;
        rename(from, to, ec);

        if( ec )
            BOOST_THROW_EXCEPTION( std::runtime_error( std::string("Error renaming ") + from + " to " + to) );
    }

    inline std::string absolute(const char* s)
    {
        current_path_saver const cps;
        current_path(s);
        return current_path();
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif
