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
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/math/special_functions/asinh.hpp>


#include <nt2/include/functions/rec.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/sqrteps.hpp>
#include <nt2/include/constants/oneosqrteps.hpp>
#include <nt2/include/constants/two.hpp>

NT2_TEST_CASE_TPL ( asinh,  NT2_SIMD_REAL_TYPES)
{
  using nt2::asinh;
  using nt2::tag::asinh_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename nt2::meta::call<asinh_(vT)>::type r_t;
  typedef vT wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);


  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(asinh(nt2::Inf<vT>()), nt2::Inf<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(asinh(nt2::Minf<vT>()), nt2::Minf<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(asinh(nt2::Nan<vT>()), nt2::Nan<r_t>(), 0.5);
#endif
 NT2_TEST_ULP_EQUAL(asinh(nt2::Zero<vT>()), nt2::Zero<r_t>(), 0.5);
 NT2_TEST_ULP_EQUAL(asinh(nt2::Valmax<vT>()), nt2::splat<vT>(boost::math::asinh(nt2::Valmax<T>())), 0.5);
 NT2_TEST_ULP_EQUAL(asinh(nt2::rec(nt2::Sqrteps<vT>())*nt2::Two<vT>()),  nt2::splat<vT>(boost::math::asinh(nt2::rec(nt2::Sqrteps<T>())*2)), 0.5);
 NT2_TEST_ULP_EQUAL(asinh(nt2::Eps<vT>()), nt2::Eps<vT>(), 0.5);

 for(T i=T(0.1); i <= T(1.1); i+= T(0.5))
 {
   vT ii =  nt2::splat<vT>(i);
   vT ri =  nt2::splat<vT>(nt2::rec(i));
   NT2_TEST_ULP_EQUAL(asinh(ii), nt2::splat<vT>(boost::math::asinh(i)), 0.5);
   NT2_TEST_ULP_EQUAL(asinh(ri), nt2::splat<vT>(boost::math::asinh(nt2::rec(i))), 0.5);
 }

}
