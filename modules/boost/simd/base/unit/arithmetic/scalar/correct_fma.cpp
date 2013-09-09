//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/arithmetic/include/functions/correct_fma.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/constants/eps.hpp>
#include <boost/simd/include/constants/three.hpp>
#include <boost/simd/include/functions/oneplus.hpp>
#include <boost/simd/sdk/config.hpp>

NT2_TEST_CASE_TPL ( correct_fma_real,  BOOST_SIMD_REAL_TYPES)
{

  using boost::simd::correct_fma;
  using boost::simd::tag::correct_fma_;
  typedef typename boost::dispatch::meta::call<correct_fma_(T,T,T)>::type r_t;
  typedef typename boost::common_type<T,T,T>::type wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(correct_fma(boost::simd::Inf<T>(), boost::simd::Inf<T>(), boost::simd::Inf<T>()), boost::simd::Inf<T>());
  NT2_TEST_EQUAL(correct_fma(boost::simd::Minf<T>(), boost::simd::Minf<T>(), boost::simd::Minf<T>()), boost::simd::Nan<T>());
  NT2_TEST_EQUAL(correct_fma(boost::simd::Nan<T>(), boost::simd::Nan<T>(), boost::simd::Nan<T>()), boost::simd::Nan<T>());
#endif
  NT2_TEST_EQUAL(correct_fma(boost::simd::Mone<T>(), boost::simd::Mone<T>(), boost::simd::Mone<T>()), boost::simd::Zero<T>());
  NT2_TEST_EQUAL(correct_fma(boost::simd::One<T>(), boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::Two<T>());
  NT2_TEST_EQUAL(correct_fma(boost::simd::One<T>()+boost::simd::Eps<T>(), boost::simd::One<T>()-boost::simd::Eps<T>(),boost::simd::Mone<T>()), -boost::simd::Eps<T>()*boost::simd::Eps<T>());
  NT2_TEST_EQUAL(correct_fma(boost::simd::Zero<T>(), boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Zero<T>());
#ifndef  BOOST_SIMD_DONT_CARE_CORRECT_FMA_OVERFLOW
  NT2_TEST_EQUAL(correct_fma(boost::simd::Valmax<T>(), boost::simd::Two<T>(), -boost::simd::Valmax<T>()), boost::simd::Valmax<T>());
#endif
} // end of test for floating_

NT2_TEST_CASE_TPL ( correct_fma_signed_int,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using boost::simd::correct_fma;
  using boost::simd::tag::correct_fma_;
  typedef typename boost::dispatch::meta::call<correct_fma_(T,T,T)>::type r_t;
  typedef typename boost::common_type<T,T,T>::type wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(correct_fma(boost::simd::Mone<T>(), boost::simd::Mone<T>(), boost::simd::Mone<T>()), boost::simd::Zero<T>());
  NT2_TEST_EQUAL(correct_fma(boost::simd::One<T>(), boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::Two<T>());
  NT2_TEST_EQUAL(correct_fma(boost::simd::Zero<T>(), boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Zero<T>());
  NT2_TEST_EQUAL(correct_fma(boost::simd::Valmax<T>(), boost::simd::Two<T>(), boost::simd::oneplus(boost::simd::Valmin<T>())), boost::simd::Valmax<T>());
} // end of test for signed_int_

NT2_TEST_CASE_TPL ( correct_fma_unsigned_int,  BOOST_SIMD_UNSIGNED_TYPES)
{

  using boost::simd::correct_fma;
  using boost::simd::tag::correct_fma_;
  typedef typename boost::dispatch::meta::call<correct_fma_(T,T,T)>::type r_t;
  typedef typename boost::common_type<T,T,T>::type wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);


  // specific values tests
  NT2_TEST_EQUAL(correct_fma(boost::simd::One<T>(), boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::Two<T>());
  NT2_TEST_EQUAL(correct_fma(boost::simd::Zero<T>(), boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Zero<T>());
} // end of test for unsigned_int_
