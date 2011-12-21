//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 operator toolbox - modulo/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of operator components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
/// 
#include <nt2/toolbox/operator/include/functions/modulo.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/meta/as_signed.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/meta/floating.hpp>
#include <boost/type_traits/common_type.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/toolbox/constant/constant.hpp>


NT2_TEST_CASE_TPL ( modulo_signed_int__2_0,  NT2_INTEGRAL_SIGNED_TYPES)
{
  
  using nt2::modulo;
  using nt2::tag::modulo_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<modulo_(T,T)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef r_t wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(modulo(nt2::Mone<T>(),nt2::Two<T>()), nt2::Mone<r_t>());
  NT2_TEST_EQUAL(modulo(nt2::One<T>(), nt2::One<T>()), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(modulo(nt2::One<T>(),nt2::Two<T>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(modulo(nt2::Zero<T>(),nt2::Two<T>()), nt2::Zero<r_t>());
} // end of test for signed_int_

NT2_TEST_CASE_TPL ( modulo_unsigned_int__2_0,  NT2_UNSIGNED_TYPES)
{
  
  using nt2::modulo;
  using nt2::tag::modulo_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<modulo_(T,T)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef r_t wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(modulo(nt2::Four<T>(),nt2::Two<T>()), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(modulo(nt2::One<T>(), nt2::One<T>()), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(modulo(nt2::One<T>(),nt2::Two<T>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(modulo(nt2::Zero<T>(),nt2::Two<T>()), nt2::Zero<r_t>());
} // end of test for unsigned_int_
