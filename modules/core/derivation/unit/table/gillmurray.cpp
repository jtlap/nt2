//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/derivation/include/functions/gillmurray.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/functions/cat.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/pow.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/invpi.hpp>
#include <nt2/include/constants/sqrteps.hpp>
#include <nt2/include/constants/derivinc2.hpp>
#include <nt2/table.hpp>



NT2_TEST_CASE_TPL ( gillmurray, NT2_REAL_TYPES)
{
  using nt2::gillmurray;
  using nt2::tag::gillmurray_;

  nt2::table<T> x =  nt2::reshape(nt2::linspace(T(1), T(4), 4), 4, 1); //12), 3, 4);
  auto f =  [](nt2::table<T> xx)
    {
      return xx(1, nt2::_)*(xx(1, nt2::_)+sqr(xx(2, nt2::_)))+sqr(xx(3, nt2::_))*xx(3, nt2::_);
    };
  auto dd2f =  [](nt2::table<T> xx)
    {
      return nt2::cons<T>(nt2::of_size(4, 4),
                          2,             2*xx(2),       0,   0,
                          2*xx(2),       2*xx(1),       0,   0,
                          0,             0,       6*xx(3),   0,
                          0,             0,             0,   0 );
   };

//   nt2::table<T> r =   nt2::cat(3,
//                                nt2::cat(3,
//                                         nt2::cat(3,
//                                                  dd2f(x(nt2::_, 1)),
//                                                  dd2f(x(nt2::_, 2))
//                                                  ),
//                                         dd2f(x(nt2::_, 3))
//                                        ),
//                                dd2f(x(nt2::_, 4))
//                               );
  T ulp =  nt2::pow(nt2::Eps<T>(), T(-2.0/3.0));
  nt2::table<T> r = dd2f(x);
  nt2::table<T> d2fdxdy =  gillmurray(f, x);
  NT2_DISPLAY(d2fdxdy);
  NT2_DISPLAY(r);
  NT2_TEST_ULP_EQUAL(d2fdxdy, r, ulp);
  d2fdxdy =  gillmurray(f, x,  nt2::Derivincgm<T>());
  NT2_TEST_ULP_EQUAL(d2fdxdy, r, ulp);
  NT2_DISPLAY(d2fdxdy);
  d2fdxdy =  gillmurray(f, x, nt2::Derivincgm<T>(), nt2::pow2den_);
  NT2_TEST_ULP_EQUAL(d2fdxdy, r, ulp);
  NT2_DISPLAY(d2fdxdy);
  d2fdxdy =  gillmurray(f, x, nt2::pow2den_);
  NT2_TEST_ULP_EQUAL(d2fdxdy, r, ulp);
  NT2_DISPLAY(d2fdxdy);
 }





