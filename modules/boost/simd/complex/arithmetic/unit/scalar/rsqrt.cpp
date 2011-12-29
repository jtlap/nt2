//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.arithmetic toolbox - rsqrt/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 30/11/2010
/// 
#include <boost/simd/toolbox/arithmetic/include/functions/rsqrt.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/simd/include/constants/i.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>


NT2_TEST_CASE_TPL ( rsqrt_real__1_0,  BOOST_SIMD_REAL_TYPES)
{
  
  using boost::simd::rsqrt;
  using boost::simd::tag::rsqrt_;
  typedef typename std::complex<T> cT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<rsqrt_(cT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef cT wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
 ulpd=0.0; 

  // std::cout << nt2::type_id(boost::simd::I<T>()) << std::endl; 
  // specific values tests
   NT2_TEST_EQUAL(rsqrt(cT(1)), T(1));
   NT2_TEST_EQUAL(rsqrt(cT(boost::simd::Inf<T>())), cT(boost::simd::Zero<T>()));
   NT2_TEST_EQUAL(rsqrt(cT(boost::simd::Minf<T>())), cT(0, boost::simd::Zero<T>()));
   NT2_TEST_EQUAL(rsqrt(cT(boost::simd::Mone<T>())), cT(0, boost::simd::Mone<T>()));
   NT2_TEST_EQUAL(rsqrt(cT(boost::simd::Nan<T>())), cT(boost::simd::Nan<T>()));
   NT2_TEST_EQUAL(rsqrt(cT(boost::simd::One<T>())), cT(boost::simd::One<T>()));
   NT2_TEST_EQUAL(rsqrt(cT(boost::simd::Zero<T>())), cT(boost::simd::Zero<T>()));
   std::complex < T > a(1, 0);
   NT2_TEST_EQUAL(rsqrt(a), boost::simd::One<T>());
   std::complex < T > b(0, i);
   NT2_TEST_EQUAL(rsqrt(b), cT(boost::simd::Sqrt_2o_2<T>(),boost::simd::Sqrt_2o_2<T>()));
} // end of test for floating_

