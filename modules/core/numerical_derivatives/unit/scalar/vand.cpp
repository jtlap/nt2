//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/numerical_derivatives/include/functions/vand.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/invpi.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/table.hpp>



NT2_TEST_CASE_TPL ( vand, NT2_REAL_TYPES)
{
  using nt2::vand;
  using nt2::tag::vand_;
  typedef typename nt2::meta::as_complex<T>::type cT;
  auto f =  [](cT t){return t*t;};
  T x =  T(nt2::Pi<T>());
  T r = T(2)*nt2::Pi<T>();
  T dfdx =  vand(f, x);
  NT2_TEST_ULP_EQUAL(dfdx, r, 0.5);


  x = nt2::Invpi<T>();
  r = 2*x;
  dfdx =  vand(f, x);
  NT2_TEST_ULP_EQUAL(dfdx, r,  0.5);
 }

