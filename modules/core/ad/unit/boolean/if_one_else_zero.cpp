//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/ad.hpp>
#include <nt2/include/functions/ad_io.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>

#include <nt2/ad/boolean.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/table.hpp>


template <class L>
auto test(const L & l) -> decltype(if_one_else_zero(l))
{
  return if_one_else_zero(l);
}

using nt2::ad::valder;

NT2_TEST_CASE_TPL ( if_one_else_zero,  NT2_REAL_TYPES)
{

  {
    valder<T> l = valder<T>(T(0));
    valder<T> r1 = test(l);
    NT2_TEST_EQUAL(r1.der(), T(0));
  }
  {
    valder<T> l = valder<T>(T(1));
    valder<T> r1 = test(l);
    NT2_TEST_EQUAL(r1.der(), T(0));
  }
}



