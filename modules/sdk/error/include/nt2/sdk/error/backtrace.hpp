//==============================================================================
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_ERROR_BACKTRACE_HPP_INCLUDED
#define NT2_SDK_ERROR_BACKTRACE_HPP_INCLUDED

#include <boost/dispatch/attributes.hpp>
#ifdef __linux__
#include <execinfo.h>
#include <ostream>
#include <iomanip>
#endif

namespace nt2
{
  BOOST_FORCEINLINE void backtrace(std::ostream& os)
  {
    #ifdef __linux__
    void *bt[1024];
    int bt_size = ::backtrace(bt, 1024);
    for(int i=0; i!=bt_size; ++i)
      os << bt[i] << "\n";
    os << std::flush;
    #endif
  }
}

#endif
