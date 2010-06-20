/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
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
