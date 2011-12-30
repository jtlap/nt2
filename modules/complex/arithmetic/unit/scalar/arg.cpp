//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 complex.operator toolbox - arg/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.operator components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
/// 
#include <nt2/toolbox/arithmetic/include/functions/arg.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <nt2/toolbox/constant/constant.hpp>

NT2_TEST_CASE_TPL ( arg_real__2_0,  BOOST_SIMD_REAL_TYPES)
{
  
  using boost::simd::arg;
  using boost::simd::tag::arg_;
  typedef std::complex<T> cT; 
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<arg_(cT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef boost::simd::imaginary<T> ciT; 
  typedef T wished_r_t;

  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(arg(cT(boost::simd::Inf<T>())), boost::simd::Zero<T>());
  NT2_TEST_EQUAL(arg(cT(boost::simd::Minf<T>())),boost::simd::Pi<T>());
  NT2_TEST_EQUAL(arg(cT(boost::simd::Nan<T>())), boost::simd::Nan<T>());   
  NT2_TEST_EQUAL(arg(cT(boost::simd::One<T>())), boost::simd::Zero<T>()); 
  NT2_TEST_EQUAL(arg(cT(boost::simd::Zero<T>())),boost::simd::Zero<T>()); 
  NT2_TEST_EQUAL(arg(cT(0, 1)), boost::simd::Pio_2<T>());
  NT2_TEST_EQUAL(arg(cT(1, 0)), boost::simd::Zero<T>());
  NT2_TEST_EQUAL(arg(cT(2, 2)), boost::simd::Pio_2<T>()/2);
  NT2_TEST_EQUAL(arg(cT(2,-2)),-boost::simd::Pio_2<T>()/2);
  NT2_TEST_EQUAL(arg(ciT(1)), boost::simd::Pio_2<T>());
} // end of test for floating_
