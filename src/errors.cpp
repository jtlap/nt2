/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/

#include <boost/format.hpp>
#include <nt2/sdk/sys/timestamp.hpp>
#include <nt2/sdk/errors/details/message.hpp>

namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // Build a warning string from warning/assertion info
  //////////////////////////////////////////////////////////////////////////////
  std::string message ( const char* header, const char* msg
                      , const char* fn, const char* file, int line  )
  {
    std::string that;
    that  = boost::str(   boost::format("[%1%] %2% in file %3%:%4%, function %5%: %6%\n")
                        % sys::timestamp() % header % file % line % fn % msg
                      );
    return that;
  }
} }
