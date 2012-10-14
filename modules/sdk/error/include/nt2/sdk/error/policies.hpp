//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_ERROR_POLICIES_HPP_INCLUDED
#define NT2_SDK_ERROR_POLICIES_HPP_INCLUDED

#include <boost/math/policies/policy.hpp> 

namespace nt2
{
  using namespace boost::math::policies;

  typedef policy< domain_error<errno_on_error>
                , pole_error<errno_on_error>
                , overflow_error<errno_on_error>
                , evaluation_error<errno_on_error>
                > nt2_policy;
}

#endif 