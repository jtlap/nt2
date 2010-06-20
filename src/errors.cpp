#include <nt2/sdk/sys/timestamp.hpp>
#include <nt2/sdk/errors/details/message.hpp>

namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // Build a warning string from warning/assertion info
  //////////////////////////////////////////////////////////////////////////////
  sys::string message ( const char* header, const char* msg
                      , const char* fn, const char* file, int line  )
  {
    return sys::string( "[%s] %s in file %s:%d, function %s: %s"
                      , sys::timestamp().c_str(), header
                      , file, line, fn, msg
                      );
  }
} }
