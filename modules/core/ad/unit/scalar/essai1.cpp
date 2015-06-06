//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/sqr.hpp>

#include <nt2/sdk/unit/module.hpp>

NT2_TEST_CASE_TPL ( essai,  NT2_REAL_TYPES)
{
  T a =  nt2::sqr(T(3));
}




