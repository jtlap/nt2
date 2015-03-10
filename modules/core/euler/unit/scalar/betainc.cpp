//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/euler/include/functions/betainc.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/five.hpp>

NT2_TEST_CASE_TPL ( betainc_real, NT2_REAL_TYPES)
{
  using nt2::betainc;
  using nt2::tag::betainc_;
  typedef typename nt2::meta::call<betainc_(T,T,T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(betainc( nt2::Nan<T>() , nt2::Nan<T>(), nt2::Nan<T>()  ), nt2::Nan<r_t>(), 0);
#endif
  NT2_TEST_ULP_EQUAL(betainc( nt2::Half<T>(), nt2::One<T>(), nt2::One<T>()  ), nt2::Half<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(betainc( T(0.2)        , nt2::Half<T>(), nt2::Five<T>()), T(8.55072394595920e-01), 10);
}



NT2_TEST_CASE_TPL ( betainc_2, NT2_REAL_TYPES)
{
  using nt2::betainc;
  using nt2::tag::betainc_;
  typedef typename nt2::meta::call<betainc_(T,T,T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  T x[] = {1.00000000000000,
           0.87500000000000,
           0.68750000000000,
           0.50000000000000,
           0.34375000000000,
           0.22656250000000,
           0.14453125000000,
           0.08984375000000,
           0.05468750000000,
           0.03271484375000,
           0.01928710937500};
  for(int i =  0;  i < 11; ++i)
    NT2_TEST_ULP_EQUAL(betainc(T(.5), T(i), T(3)), x[i], 20);

}



