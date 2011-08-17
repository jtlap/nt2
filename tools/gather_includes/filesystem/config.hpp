#ifndef FILESYSTEM_CONFIG_HPP
#define FILESYSTEM_CONFIG_HPP

#include <boost/system/api_config.hpp>

#ifdef BOOST_WINDOWS_API
    #pragma warning( disable : 4996 ) // The POSIX name for this item is deprecated.
    #define _POSIX_
    #include "direct.h"
    #define PATH_MAX 512 //...zzz...for some reason it does not get picked up from limits.h
    #define NOMINMAX
    #include "windows.h"
#else // POSIX
    #include "dirent.h"
    #include "sys/types.h"
#endif // OS API

#endif
