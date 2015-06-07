//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/mk_ad.hpp>
#include <nt2/include/functions/ad_io.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/colvect.hpp>

#include <nt2/ad/arithmetic.hpp>
#include <nt2/ad/operator.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/table.hpp>


NT2_TEST_CASE_TPL ( mk_ad,  (double))
{
  {
    nt2::ad::valder<T> a(T(3));
    auto b = nt2::ad::mk_ad(T(3));
    NT2_TEST_EQUAL(a.der(), b.der());
    NT2_TEST_EQUAL(a.val(), b.val());
  }
  {
    nt2::ad::valder<T> a(T(3), T(2));
    auto b = nt2::ad::mk_ad(T(3), T(2));
    NT2_TEST_EQUAL(a.der(), b.der());
    NT2_TEST_EQUAL(a.val(), b.val());
  }
  {
    typedef nt2::table<T> tT;
    tT u = nt2::linspace(T(1), T(5), 5);
    nt2::ad::valder<tT> a(nt2::linspace(T(1), T(5), 5));
    auto b = nt2::ad::mk_ad(nt2::linspace(T(1), T(5), 5));
    NT2_TEST_EQUAL(a.der(), b.der());
    NT2_TEST_EQUAL(a.val(), b.val());
  }
  { //PB
    typedef nt2::table<T> tT;
    tT x =  nt2::colvect(nt2::linspace(T(1), T(5), 5));
    tT d =  nt2::colvect(nt2::cons<T>(0, 0, 0, 1, 0));
    nt2::ad::valder<tT> a(x, d);
   auto b = nt2::ad::mk_ad(x, d);
    NT2_TEST_EQUAL(a.der(), b.der());
    NT2_TEST_EQUAL(a.val(), b.val());
  }
  {
    typedef nt2::table<T> tT;
    auto x =  nt2::colvect(nt2::linspace(T(1), T(5), 5));
    auto d =  nt2::colvect(nt2::cons<T>(0, 0, 0, 1, 0));
    nt2::ad::valder<tT> a(x, d);
    auto b = nt2::ad::mk_ad(x, std::size_t(4));
    NT2_TEST_EQUAL(a.der(), b.der());
    NT2_TEST_EQUAL(a.val(), b.val());
  }
}


