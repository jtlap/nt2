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


template <class L, class T1>
auto test(const L & l, const T1 & x) -> decltype(negifnot(l, x))
{
  return negifnot(l, x);
}

using nt2::ad::valder;

NT2_TEST_CASE_TPL ( negifnot,  NT2_REAL_TYPES)
{
  {
    bool l =  false;
    valder<T> vx(2, 1);
    valder<T> r1 = test(l, vx);
    NT2_TEST_EQUAL(r1.der(), -vx.der());
  }
  {
    bool l = true;
    valder<T> vx(2, 1);
    valder<T> r1 = test(l, vx);
    NT2_TEST_EQUAL(r1.der(), vx.der());
  }
  {
    T l = nt2::Zero<T>();
    valder<T> vx(2, 1);
    valder<T> r1 = test(l, vx);
    NT2_TEST_EQUAL(r1.der(), -vx.der());
  }
  {
    bool l = nt2::One<T>();
    valder<T> vx(2, 1);
    valder<T> r1 = test(l, vx);
    NT2_TEST_EQUAL(r1.der(), vx.der());
  }
  {
    valder<T> l = valder<T>(T(0));
    valder<T> vx(2, 1);
    valder<T> r1 = test(l, vx);
    NT2_TEST_EQUAL(r1.der(), -vx.der());
  }
  {
    valder<T> l = valder<T>(T(1));
    valder<T> vx(2, 1);
    valder<T> r1 = test(l, vx);
    NT2_TEST_EQUAL(r1.der(), vx.der());
  }
  {
    valder<T> l = valder<T>(T(0));
    T  x(2);
    valder<T> r1 = test(l, x);
    NT2_TEST_EQUAL(r1.der(), T(0));
  }
  {
    valder<T> l = valder<T>(T(1));
    T x(2);
    valder<T> r1 = test(l, x);
    NT2_TEST_EQUAL(r1.der(), T(0));
  }
}



