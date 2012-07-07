//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.bitwise toolbox - ctz/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.bitwise components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
/// 
#include <boost/simd/toolbox/bitwise/include/functions/ctz.hpp>
#include <boost/simd/include/functions/ffs.hpp>
#include <boost/simd/include/functions/clz.hpp>
#include <boost/simd/include/functions/ilog2.hpp>
#include <boost/simd/include/functions/reversebits.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>
#include <boost/dispatch/details/ignore_unused.hpp>


NT2_TEST_CASE_TPL ( ctz_real__1_0,  BOOST_SIMD_REAL_TYPES)
{
  
  using boost::simd::ctz;
  using boost::simd::tag::ctz_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<ctz_(T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef typename boost::dispatch::meta::as_integer<T, unsigned>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 

  // specific values tests
  NT2_TEST_EQUAL(ctz(boost::simd::Inf<T>()), boost::simd::Nbmantissabits<T>());
  NT2_TEST_EQUAL(ctz(boost::simd::Minf<T>()), boost::simd::Nbmantissabits<T>());
  NT2_TEST_EQUAL(ctz(boost::simd::Nan<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(ctz(boost::simd::Signmask<T>()), sizeof(T)*8-1);
  NT2_TEST_EQUAL(ctz(boost::simd::Zero<T>()), sizeof(T)*8);
} // end of test for real_

NT2_TEST_CASE_TPL ( ctz_signed_int__1_0,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{
  
  using boost::simd::ctz;
  using boost::simd::tag::ctz_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<ctz_(T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef typename boost::dispatch::meta::as_integer<T, unsigned>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 

  // specific values tests
  NT2_TEST_EQUAL(ctz(boost::simd::One<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(ctz(boost::simd::Signmask<T>()), sizeof(T)*8-1);
  NT2_TEST_EQUAL(ctz(boost::simd::Zero<T>()), sizeof(T)*8);
} // end of test for signed_int_

 NT2_TEST_CASE_TPL ( ctz_unsigned_int__1_0,  BOOST_SIMD_UNSIGNED_TYPES)
 {
  
  using boost::simd::ctz;
  using boost::simd::tag::ctz_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<ctz_(T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef typename boost::dispatch::meta::as_integer<T, unsigned>::type wished_r_t;
  
  
  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  
  // specific values tests
  //   std::cout << int(ctz(boost::simd::One<T>())) << std::endl; 
  NT2_TEST_EQUAL(ctz(boost::simd::One<T>()), boost::simd::Zero<r_t>());
  //   std::cout << int(ctz(boost::simd::Zero<T>())) << std::endl; 
  NT2_TEST_EQUAL(ctz(boost::simd::Zero<T>()), sizeof(T)*8);
  
  T j = 1; 
  for(T i=2; i< boost::simd::Valmax<T>()/2; i*= 2)
    {
      NT2_TEST_EQUAL(ctz(i), j);
      NT2_TEST_EQUAL(ctz(i+1), 0);
      
      //       std::cout << i << "   "
      //                 << int(boost::simd::ctz(T(i))) << "           "
      //                 << boost::simd::ffs(T(i)) << "           "
      //                 << boost::simd::clz(T(i)) << "           "
      //                 << boost::simd::ffs(boost::simd::reversebits(T(i))) << "           "
      //                 << boost::simd::ilog2(T(i)) << "           "
      //                 << sizeof(T)*8-boost::simd::ffs(boost::simd::reversebits(T(i))) << std::endl; 
      ++j; 
    }
 } // end of test for unsigned_int_
