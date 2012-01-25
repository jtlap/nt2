//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 complex.arithmetic toolbox - abs/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 30/11/2010
/// 
#include <nt2/toolbox/arithmetic/include/functions/abs.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/constants/i.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <nt2/toolbox/constant/constant.hpp>
#include <nt2/sdk/complex/dry.hpp>

NT2_TEST_CASE_TPL ( abs_real__1_0,  BOOST_SIMD_REAL_TYPES)
{
  
  using nt2::abs;
  using nt2::tag::abs_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<abs_(T)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef typename std::complex<T> cT;
  typedef typename nt2::meta::as_imaginary<T>::type ciT;
  typedef typename nt2::meta::as_dry<T>::type dT;
  typedef T wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
 ulpd=0.0; 

  // std::cout << nt2::type_id(nt2::I<T>()) << std::endl; 
  // specific values tests
   NT2_TEST_EQUAL(nt2::abs(cT(1)), T(1));
   NT2_TEST_EQUAL(nt2::abs(cT(nt2::Inf<T>())), nt2::Inf<T>());
   NT2_TEST_EQUAL(nt2::abs(cT(nt2::Minf<T>())), nt2::Inf<T>());
   NT2_TEST_EQUAL(nt2::abs(cT(nt2::Mone<T>())), nt2::One<T>());
   NT2_TEST_EQUAL(nt2::abs(cT(nt2::Nan<T>())), nt2::Nan<T>());
   NT2_TEST_EQUAL(nt2::abs(cT(nt2::One<T>())), nt2::One<T>());
   NT2_TEST_EQUAL(nt2::abs(cT(nt2::Valmax<T>())), nt2::Valmax<T>());
   NT2_TEST_EQUAL(nt2::abs(cT(nt2::Valmin<T>())), nt2::Valmax<T>());
   NT2_TEST_EQUAL(nt2::abs(cT(nt2::Zero<T>())), nt2::Zero<T>());
   std::complex < T > a(1, 0);
   NT2_TEST_EQUAL(nt2::abs(a), nt2::One<T>());
   std::complex < T > b(3, 4);
   NT2_TEST_EQUAL(nt2::abs(b), nt2::Five<T>());
} // end of test for floating_

