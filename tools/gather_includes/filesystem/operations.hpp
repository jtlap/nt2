#ifndef FILESYSTEM_OPERATIONS_HPP
#define FILESYSTEM_OPERATIONS_HPP

#include <boost/system/api_config.hpp>
#include <boost/throw_exception.hpp>
#include <boost/assert.hpp>
#include <boost/scoped_array.hpp>
#include <filesystem/directory_iterator.hpp>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <limits.h>
#include <stdio.h>

#ifdef BOOST_WINDOWS_API
    #include <direct.h>
    #ifndef PATH_MAX
        #define PATH_MAX 512 //...zzz...for some reason it does not get picked up from limits.h
    #endif
    #define FILESYSTEM_MKDIR_SUFFIX
    #include <errno.h>
#else // POSIX
    #include <sys/stat.h>
    #include <unistd.h>
    #define FILESYSTEM_MKDIR_SUFFIX , 0777
    #include <errno.h>
#endif

#ifdef BOOST_WINDOWS_API
    //  REPARSE_DATA_BUFFER related definitions are found in ntifs.h, which is part of the
    //  Windows Device Driver Kit. Since that's inconvenient, the definitions are provided
    //  here. See http://msdn.microsoft.com/en-us/library/ms791514.aspx

    #if !defined(REPARSE_DATA_BUFFER_HEADER_SIZE)  // mingw winnt.h does provide the defs

    typedef struct _REPARSE_DATA_BUFFER {
      ULONG  ReparseTag;
      USHORT  ReparseDataLength;
      USHORT  Reserved;
      union {
        struct {
          USHORT  SubstituteNameOffset;
          USHORT  SubstituteNameLength;
          USHORT  PrintNameOffset;
          USHORT  PrintNameLength;
          ULONG  Flags;
          WCHAR  PathBuffer[1];
      /*  Example of distinction between substitute and print names:
            mklink /d ldrive c:\
            SubstituteName: c:\\??\
            PrintName: c:\
      */
         } SymbolicLinkReparseBuffer;
        struct {
          USHORT  SubstituteNameOffset;
          USHORT  SubstituteNameLength;
          USHORT  PrintNameOffset;
          USHORT  PrintNameLength;
          WCHAR  PathBuffer[1];
          } MountPointReparseBuffer;
        struct {
          UCHAR  DataBuffer[1];
        } GenericReparseBuffer;
      };
    } REPARSE_DATA_BUFFER, *PREPARSE_DATA_BUFFER;

    #define REPARSE_DATA_BUFFER_HEADER_SIZE \
      FIELD_OFFSET(REPARSE_DATA_BUFFER, GenericReparseBuffer)

    #endif

    #ifndef MAXIMUM_REPARSE_DATA_BUFFER_SIZE
        #define MAXIMUM_REPARSE_DATA_BUFFER_SIZE  ( 16 * 1024 )
    #endif

    #ifndef FSCTL_GET_REPARSE_POINT
        #define FSCTL_GET_REPARSE_POINT 0x900a8
    #endif

    #ifndef IO_REPARSE_TAG_SYMLINK
        #define IO_REPARSE_TAG_SYMLINK (0xA000000CL)
    #endif

#endif

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4996) // The POSIX name for this item is deprecated.
#endif

namespace filesystem
{
#ifdef BOOST_WINDOWS_API
    namespace detail
    {
        inline bool is_reparse_point_a_symlink(const char* p)
        {
            HANDLE h = CreateFileA(p, FILE_READ_EA,
                FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING,
                FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT, NULL);
            if (h == INVALID_HANDLE_VALUE)
                return false;

            boost::scoped_array<char> buf(new char [MAXIMUM_REPARSE_DATA_BUFFER_SIZE]);

            // Query the reparse data
            DWORD dwRetLen;
            BOOL result = DeviceIoControl(h, FSCTL_GET_REPARSE_POINT, NULL, 0, buf.get(),
                MAXIMUM_REPARSE_DATA_BUFFER_SIZE, &dwRetLen, NULL);
            CloseHandle(h);

            if(!result)
                return false;

            return reinterpret_cast<const REPARSE_DATA_BUFFER*>(buf.get())
                ->ReparseTag == IO_REPARSE_TAG_SYMLINK;
        }
    }
#endif

    inline bool exists( const char* file_path )
    {
    #ifdef BOOST_WINDOWS_API
        return GetFileAttributes(file_path) != INVALID_FILE_ATTRIBUTES;
    #else
        struct stat s;
        return stat(file_path, &s) == 0;
    #endif
    }

    inline bool is_symlink( const char* file_path )
    {
    #ifdef BOOST_WINDOWS_API
        DWORD attr = GetFileAttributes(file_path);
        if(attr == INVALID_FILE_ATTRIBUTES)
            return false;

        if(attr & FILE_ATTRIBUTE_REPARSE_POINT)
            return detail::is_reparse_point_a_symlink(file_path);
        return false;
    #else
        struct stat s;
        if(lstat(file_path, &s))
            return false;

        return S_ISLNK(s.st_mode) == 1;
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
            if(is_symlink(*current_dir) || !is_directory(*current_dir))
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
        if(is_symlink(file_path) || !is_directory(file_path))
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
