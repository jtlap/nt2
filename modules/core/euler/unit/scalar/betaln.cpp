//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/euler/include/functions/betaln.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/inf.hpp>

NT2_TEST_CASE_TPL ( betaln_real,  NT2_REAL_TYPES)
{
  using nt2::betaln;
  using nt2::tag::betaln_;
  typedef typename nt2::meta::call<betaln_(T,T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(betaln(nt2::Nan<T>(), nt2::Nan<T>()), nt2::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(betaln(nt2::Inf<T>(), nt2::Inf<T>()), nt2::Nan<r_t>(), 0);
#endif

  T r[5] = {T(-1.609437912434100),  T(-2.995732273553991),  T(-3.401197381662155),  T(-2.995732273553991),  T(  -1.609437912434100)};

  for(int i = 1; i <= 5 ; ++i)
  {
    NT2_TEST_ULP_EQUAL(betaln(T(i), T(6-i)), r[i-1], 0.5);
  }

}
