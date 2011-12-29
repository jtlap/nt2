//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.arithmetic toolbox - eps/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 30/11/2010
/// 
#include <boost/simd/include/functions/eps.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/simd/include/constants/i.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>


NT2_TEST_CASE_TPL ( eps_real__1_0,  BOOST_SIMD_REAL_TYPES)
{
  
  using boost::simd::eps;
  using boost::simd::tag::eps_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<eps_(T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef typename std::complex<T> cT;
  typedef T wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0; 

  // std::cout << nt2::type_id(boost::simd::I<T>()) << std::endl; 
  // specific values tests
  NT2_TEST_EQUAL(eps(cT(1)), boost::simd::eps(T(1)));
   NT2_TEST_EQUAL(eps(cT(boost::simd::Inf<T>())), boost::simd::Nan<T>());
   NT2_TEST_EQUAL(eps(cT(boost::simd::Minf<T>())), boost::simd::Nan<T>());
   NT2_TEST_EQUAL(eps(cT(boost::simd::Mone<T>())), boost::simd::Eps<T>());
   NT2_TEST_EQUAL(eps(cT(boost::simd::Nan<T>())), boost::simd::Nan<T>());
   NT2_TEST_EQUAL(eps(cT(boost::simd::One<T>())), boost::simd::Eps<T>());
   NT2_TEST_EQUAL(eps(cT(boost::simd::Zero<T>())), boost::simd::eps(boost::simd::Zero<T>()));
   std::complex < T > a(0, 1);
   NT2_TEST_EQUAL(eps(a), boost::simd::eps(boost::simd::One<T>()));
   std::complex < T > b(3, 4);
   NT2_TEST_EQUAL(eps(b), boost::simd::eps(boost::simd::Five<T>()));
} // end of test for floating_

