//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/ieee/include/functions/saturate.hpp>
#include <boost/simd/sdk/simd/logical.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/meta/downgrade.hpp>
#include <boost/simd/include/functions/splat.hpp>

#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/mone.hpp>

NT2_TEST_CASE_TPL ( saturate,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::saturate;
  using boost::simd::tag::saturate_;
  using boost::simd::Valmax;
  using boost::simd::Valmin;
  using boost::simd::Inf;
  using boost::simd::Minf;
  using boost::simd::Nan;
  using boost::simd::splat;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION                            ext_t;
  typedef typename boost::dispatch::meta::as_integer<T>::type        iT;
  typedef native<T,ext_t>                                            vT;
  typedef typename boost::dispatch::meta::as_integer<vT>::type      viT;
  // specific values tests
  NT2_TEST_ULP_EQUAL(splat<vT>(1),           saturate<viT>(splat<vT>(1ull        )), 0);
  NT2_TEST_ULP_EQUAL(splat<vT>(Valmax<iT>()),saturate<viT>(splat<vT>(T(Valmax<iT>())*2)), 0);
  NT2_TEST_ULP_EQUAL(splat<vT>(Valmin<iT>()),saturate<viT>(splat<vT>(T(Valmin<iT>())*2)), 0);
  NT2_TEST_ULP_EQUAL(splat<vT>(Valmin<iT>()),saturate<viT>(splat<vT>(Minf<T>())), 0);
  NT2_TEST_ULP_EQUAL(splat<vT>(Valmax<iT>()),saturate<viT>(splat<vT>(Inf<T>())), 0);
  NT2_TEST_ULP_EQUAL(Nan<vT>(),saturate<viT>(splat<vT>(Nan<T>())), 0);

}


NT2_TEST_CASE_TPL ( saturateu,  BOOST_SIMD_SIMD_INTEGRAL_TYPES)
{
  using boost::simd::saturate;
  using boost::simd::tag::saturate_;
  using boost::simd::Valmax;
  using boost::simd::Valmin;
  using boost::simd::splat;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION                            ext_t;
  typedef native<T,ext_t>                                            vT;
  typedef typename boost::dispatch::meta::downgrade<T>::type         dT;

  // specific values tests
  NT2_TEST_ULP_EQUAL(splat<vT>(Valmax <dT>()),           saturate<dT>(Valmax<vT>()), 0);
  NT2_TEST_ULP_EQUAL(splat<vT>(Valmin <dT>()),           saturate<dT>(Valmin<vT>()), 0);
}




