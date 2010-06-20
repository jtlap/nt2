/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_ERRORS_CONFIG_HPP_INCLUDED
#define NT2_SDK_ERRORS_CONFIG_HPP_INCLUDED

#include <nt2/sdk/errors/failure.hpp>
#include <nt2/sdk/errors/error.hpp>
#include <nt2/sdk/errors/warning.hpp>

namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // Status header reporter - Head for the reporter list
  //////////////////////////////////////////////////////////////////////////////
  static void errors()
  {
    puts(" Warnings                : " NT2_WARNINGS_CONFIG_STRING );
    puts(" Errors                  : " NT2_ERRORS_CONFIG_STRING   );
    puts(" Failures                : " NT2_FAILURES_CONFIG_STRING );
  }

  NT2_REGISTER_STATUS(errors);
} }
#endif
