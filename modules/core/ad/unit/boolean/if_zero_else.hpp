//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/ad.hpp>
#include <nt2/include/functions/ad_io.hpp>

#include <nt2/ad/boolean.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/table.hpp>


template <class L, class T1, class T2>
auto test(const L & l, const T1 & x) -> decltype(if_zero_else(l, x))
{
  return if_zero_else(l, x);
}

using nt2::ad::valder;

NT2_TEST_CASE_TPL ( if_zero_else,  NT2_REAL_TYPES)
{
  {
    T l = nt2::Nan<T>();
    valder<T> vx(2, 1);
    valder<T> r1 = test(l, vx);
    NT2_TEST_EQUAL(r1.der(), vx.der());
  }
  {
    bool l = nt2::One<T>();
    valder<T> vx(2, 1);
    valder<T> r1 = test(l, vx);
    NT2_TEST_EQUAL(r1.der(), Zero<T>());
  }

}



