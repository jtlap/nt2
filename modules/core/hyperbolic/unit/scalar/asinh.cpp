//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/hyperbolic/include/functions/asinh.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/functions/rec.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/sqrteps.hpp>
#include <nt2/include/constants/oneosqrteps.hpp>
#include <boost/math/special_functions/asinh.hpp>

NT2_TEST_CASE_TPL ( asinh,  NT2_REAL_TYPES)
{
  using nt2::asinh;
  using nt2::tag::asinh_;
  typedef typename nt2::meta::call<asinh_(T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(asinh(nt2::Inf<T>()), nt2::Inf<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(asinh(nt2::Minf<T>()), nt2::Minf<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(asinh(nt2::Nan<T>()), nt2::Nan<r_t>(), 0.5);
#endif
  NT2_TEST_ULP_EQUAL(asinh(nt2::Zero<T>()), nt2::Zero<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(asinh(nt2::Valmax<T>()), boost::math::asinh(nt2::Valmax<T>()), 0.5);
  NT2_TEST_ULP_EQUAL(asinh(nt2::rec(nt2::Sqrteps<T>())*2),  boost::math::asinh(nt2::rec(nt2::Sqrteps<T>())*2), 0.5);
  NT2_TEST_ULP_EQUAL(asinh(nt2::Eps<T>()), nt2::Eps<T>(), 0.5);
 for(T i=T(0.1); i <= T(1.1); i+= T(0.5))
 {
   T ri =  nt2::rec(i);
   NT2_TEST_ULP_EQUAL(asinh(i), boost::math::asinh(i), 0.5);
   NT2_TEST_ULP_EQUAL(asinh(ri), boost::math::asinh(ri), 0.5);
 }
}





