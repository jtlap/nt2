//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/arithmetic/include/functions/correct_fma.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/constants/eps.hpp>
#include <boost/simd/include/functions/simd/oneplus.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

NT2_TEST_CASE_TPL ( correct_fma_real,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::correct_fma;
  using boost::simd::tag::correct_fma_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<correct_fma_(vT,vT,vT)>::type r_t;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(correct_fma(boost::simd::Inf<vT>(), boost::simd::Inf<vT>(), boost::simd::Inf<vT>()), boost::simd::Inf<vT>());
  NT2_TEST_EQUAL(correct_fma(boost::simd::Minf<vT>(), boost::simd::Minf<vT>(), boost::simd::Minf<vT>()), boost::simd::Nan<vT>());
  NT2_TEST_EQUAL(correct_fma(boost::simd::Nan<vT>(), boost::simd::Nan<vT>(), boost::simd::Nan<vT>()), boost::simd::Nan<vT>());
#endif
  NT2_TEST_EQUAL(correct_fma(boost::simd::Mone<vT>(), boost::simd::Mone<vT>(), boost::simd::Mone<vT>()), boost::simd::Zero<vT>());
  NT2_TEST_EQUAL(correct_fma(boost::simd::One<vT>(), boost::simd::One<vT>(), boost::simd::One<vT>()), boost::simd::Two<vT>());
  NT2_TEST_EQUAL(correct_fma(boost::simd::One<vT>()+boost::simd::Eps<vT>(), boost::simd::One<vT>()-boost::simd::Eps<vT>(),boost::simd::Mone<vT>()), -boost::simd::Eps<vT>()*boost::simd::Eps<vT>());
  NT2_TEST_EQUAL(correct_fma(boost::simd::Zero<vT>(), boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), boost::simd::Zero<vT>());
#ifndef  BOOST_SIMD_DONT_CARE_CORRECT_FMA_OVERFLOW
  NT2_TEST_EQUAL(correct_fma(boost::simd::Valmax<vT>(), boost::simd::Two<vT>(), -boost::simd::Valmax<vT>()), boost::simd::Valmax<vT>());
#endif
} // end of test for floating_


NT2_TEST_CASE_TPL ( correct_fma_si,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::correct_fma;
  using boost::simd::tag::correct_fma_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<correct_fma_(vT,vT,vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(correct_fma(boost::simd::Mone<vT>(), boost::simd::Mone<vT>(), boost::simd::Mone<vT>()), boost::simd::Zero<vT>());
  NT2_TEST_EQUAL(correct_fma(boost::simd::One<vT>(), boost::simd::One<vT>(), boost::simd::One<vT>()), boost::simd::Two<vT>());
  NT2_TEST_EQUAL(correct_fma(boost::simd::Zero<vT>(), boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), boost::simd::Zero<vT>());
  NT2_TEST_EQUAL(correct_fma(boost::simd::Valmax<vT>(), boost::simd::Two<vT>(),  boost::simd::oneplus(boost::simd::Valmin<T>())), boost::simd::Valmax<vT>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( correct_fma_ui,  BOOST_SIMD_SIMD_UNSIGNED_TYPES)
{
  using boost::simd::correct_fma;
  using boost::simd::tag::correct_fma_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<correct_fma_(vT,vT,vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(correct_fma(boost::simd::One<vT>(), boost::simd::One<vT>(), boost::simd::One<vT>()), boost::simd::Two<vT>());
  NT2_TEST_EQUAL(correct_fma(boost::simd::Zero<vT>(), boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), boost::simd::Zero<vT>());
} // end of test for floating_
