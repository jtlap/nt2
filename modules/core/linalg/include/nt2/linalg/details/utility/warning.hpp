//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_UTILITY_WARNING_HPP_INCLUDED
#define NT2_LINALG_DETAILS_UTILITY_WARNING_HPP_INCLUDED

#include <nt2/sdk/error/warning.hpp>
#include <boost/dispatch/meta/ignore_unused.hpp>

namespace nt2
{
  /**
    @brief Low level LAPACK warning
  **/

  BOOST_FORCEINLINE void lapack_warn(const nt2_la_int & info)
  {
    boost::dispatch::ignore_unused(info);
    NT2_WARNING(info == 0, "Warning lapack info is not zero");
  }

}

#endif
