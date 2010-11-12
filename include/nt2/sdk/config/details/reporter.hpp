/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONFIG_DETAILS_REPORTER_HPP_INCLUDED
#define NT2_SDK_CONFIG_DETAILS_REPORTER_HPP_INCLUDED

#include <cstdio>
#include <boost/preprocessor/cat.hpp>
#include <nt2/sdk/config/details/boost.hpp>

namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // status reporter structure
  // Statically generated linked link of function pointers
  //////////////////////////////////////////////////////////////////////////////
  struct reporter
  {
    // Status function have a void() type
    typedef void (*ptr_fun_t)();

    // Store current status function
    ptr_fun_t      call;

    // Next reporter
    mutable reporter const* next;

    // Called by the reporter registration to build the chain of reporting
    reporter* link(reporter const* n) const
    {
      if(next != 0 )  return next->link(n);
      else            next = n;
      return 0;
    }

    // Display all its registered status
    void operator()() const
    {
      reporter const* curr = this;
      while(curr != 0) { curr->call(); curr = curr->next; }
    }
  };

  //////////////////////////////////////////////////////////////////////////////
  // Status header reporter - Head for the reporter list
  //////////////////////////////////////////////////////////////////////////////
  inline void status_headers()
  {
    puts("/****************************************************************\\");
    puts( "|                   NT2 v3.0 - Ophelia release                   |");
    puts("\\****************************************************************/");
    puts(" Last compilation        : " __DATE__ " @ " __TIME__ "\n");
  }
} }

////////////////////////////////////////////////////////////////////////////////
// status reporter global instance
// When called, display the current list fo all status reporter
// Documentation: http://nt2.lri.fr/sdk/config/function.html
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace config
{
  details::reporter const status = {details::status_headers,0};
} }

////////////////////////////////////////////////////////////////////////////////
// Status reporter registration macro
////////////////////////////////////////////////////////////////////////////////
#define NT2_REGISTER_STATUS(FUNC)                                     \
nt2::details::reporter const                                          \
BOOST_PP_CAT(FUNC,_reporter) = { FUNC                                 \
                               , nt2::config::status                  \
                                .link(&BOOST_PP_CAT(FUNC,_reporter))  \
                              }                                       \
/**/

#endif
