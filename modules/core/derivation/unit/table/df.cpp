//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/derivation/include/functions/df.hpp>

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
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/globalsum.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/invpi.hpp>
#include <nt2/include/constants/sqrteps.hpp>
#include <nt2/table.hpp>



NT2_TEST_CASE_TPL ( df, NT2_REAL_TYPES)
{
  using nt2::df;
  using nt2::tag::df_;

  nt2::table<T> x =  nt2::reshape(nt2::linspace(T(3), T(14), 12), 3, 4);
  auto f =  [](nt2::table<T> xx)
    {
      return nt2::cat(1
                     , xx(1, nt2::_)*xx(1, nt2::_)+xx(2, nt2::_)
                     , xx(2, nt2::_)*xx(2, nt2::_)*xx(3, nt2::_)
                     );
    };
  typedef typename nt2::meta::as_complex<T>::type cT;
  auto cf =  [](nt2::table<cT> xx)
    {
      return nt2::cat(1
                     , xx(1, nt2::_)*xx(1, nt2::_)+xx(2, nt2::_)
                     , xx(2, nt2::_)*xx(2, nt2::_)*xx(3, nt2::_)
                     );
    };

  auto ddf =  [](nt2::table<T> xx)
    {
      return nt2::cons<T>(nt2::of_size(2, 3),
                          2*xx(1),              0,
                          1        , 2*xx(2)*xx(3),
                          0        , xx(2)*xx(2) );
   };

  nt2::table<T> r =   nt2::cat(3,
                               nt2::cat(3,
                                        nt2::cat(3,
                                                 ddf(x(nt2::_, 1)),
                                                 ddf(x(nt2::_, 2))
                                                ),
                                        ddf(x(nt2::_, 3))
                                       ),
                               ddf(x(nt2::_, 4))
                              );
  nt2::table<T> dfdx =  df(f, x, nt2::tag::forward_());
  NT2_TEST_ULP_EQUAL(dfdx, r, nt2::rec(nt2::Sqrteps<T>()));
  dfdx =  df(f, x, nt2::tag::centered_(), nt2::pow2den_);
  NT2_TEST_ULP_EQUAL(dfdx, r, nt2::rec(nt2::Sqrteps<T>()));
  dfdx =  df(cf, x, nt2::tag::vand_());
  NT2_TEST_ULP_EQUAL(dfdx, r, nt2::rec(nt2::Sqrteps<T>()));
 }



