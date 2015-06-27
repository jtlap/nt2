//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/numerical_derivatives/include/functions/vand2.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/exp.hpp>


NT2_TEST_CASE_TPL ( vand, NT2_REAL_TYPES)
{
  using nt2::vand2;
  using nt2::tag::vand2_;
  typedef typename nt2::meta::as_complex<T>::type cT;
  auto f =  [](cT t){return nt2::exp(t);};
  T x = T(0);
  T r = T(1);
  T d2fdx2 =  vand2(f, x);
  NT2_TEST_ULP_EQUAL(d2fdx2, r, 0.5);
}

