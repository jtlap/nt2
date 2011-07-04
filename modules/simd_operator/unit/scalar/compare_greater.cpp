//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 operator toolbox - compare_greater/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of operator components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
/// 
#include <nt2/toolbox/operator/include/compare_greater.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/all.hpp>

#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/include/constants/infinites.hpp>


NT2_TEST_CASE_TPL ( compare_greater_real__2_0,  NT2_REAL_TYPES)
{
  
  using nt2::compare_greater;
  using nt2::tag::compare_greater_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<compare_greater_(T,T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef bool wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(compare_greater(nt2::Inf<T>(), nt2::Inf<T>()), false);
  NT2_TEST_EQUAL(compare_greater(nt2::Minf<T>(), nt2::Minf<T>()), false);
  NT2_TEST_EQUAL(compare_greater(nt2::Nan<T>(), nt2::Nan<T>()), false);
  NT2_TEST_EQUAL(compare_greater(nt2::One<T>(),nt2::Two<T>()), false);
  NT2_TEST_EQUAL(compare_greater(nt2::Zero<T>(), nt2::Zero<T>()), false);
} // end of test for real_

NT2_TEST_CASE_TPL ( compare_greater_integer__2_0,  NT2_INTEGRAL_TYPES)
{
  
  using nt2::compare_greater;
  using nt2::tag::compare_greater_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<compare_greater_(T,T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef bool wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(compare_greater(nt2::One<T>(), nt2::One<T>()), false);
  NT2_TEST_EQUAL(compare_greater(nt2::One<T>(),nt2::Zero<T>()), false);
  NT2_TEST_EQUAL(compare_greater(nt2::Zero<T>(), nt2::Zero<T>()), false);
} // end of test for integer_
