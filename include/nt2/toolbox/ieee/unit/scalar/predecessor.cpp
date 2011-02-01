//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 ieee toolbox - predecessor/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of ieee components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// modified by jt the 04/12/2010
/// modified by jt the 12/12/2010
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/toolbox/ieee/include/predecessor.hpp>
// specific includes for arity 1 tests
#include <nt2/include/functions/prev.hpp>
#include <nt2/sdk/constant/eps_related.hpp>
// specific includes for arity 2 tests
#include <nt2/include/functions/next.hpp>
#include <nt2/sdk/constant/eps_related.hpp>

NT2_TEST_CASE_TPL ( predecessor_real__1,  NT2_REAL_TYPES)
{
  using nt2::predecessor;
  using nt2::tag::predecessor_;
  typedef typename nt2::meta::call<predecessor_(T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;

  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 


  // specific values tests
  NT2_TEST_ULP_EQUAL(  predecessor(nt2::Inf<T>()), nt2::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(  predecessor(nt2::Minf<T>()), nt2::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(  predecessor(nt2::Mone<T>()), nt2::Mone<r_t>()-nt2::Eps<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(  predecessor(nt2::Nan<T>()), nt2::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(  predecessor(nt2::One<T>()), nt2::One<r_t>()-nt2::Eps<r_t>()/2, 0);
  NT2_TEST_ULP_EQUAL(  predecessor(nt2::Zero<T>()), -nt2::Mindenormal<T>(), 0);
} // end of test for real_

NT2_TEST_CASE_TPL ( predecessor_unsigned_int__1,  NT2_UNSIGNED_TYPES)
{
  using nt2::predecessor;
  using nt2::tag::predecessor_;
  typedef typename nt2::meta::call<predecessor_(T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;

  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 


  // specific values tests
  NT2_TEST_ULP_EQUAL(  predecessor(nt2::One<T>()), nt2::Zero<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(  predecessor(nt2::Zero<T>()), nt2::Valmax<r_t>(), 0);
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( predecessor_signed_int__1,  NT2_INTEGRAL_SIGNED_TYPES)
{
  using nt2::predecessor;
  using nt2::tag::predecessor_;
  typedef typename nt2::meta::call<predecessor_(T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;

  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 


  // specific values tests
  NT2_TEST_ULP_EQUAL(  predecessor(nt2::Mone<T>()), -nt2::Two<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(  predecessor(nt2::One<T>()), nt2::Zero<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(  predecessor(nt2::Zero<T>()), nt2::Mone<r_t>(), 0);
} // end of test for signed_int_

NT2_TEST_CASE_TPL ( predecessor_real__2,  NT2_REAL_TYPES)
{
  using nt2::predecessor;
  using nt2::tag::predecessor_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<predecessor_(T,iT)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;

  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 

} // end of test for real_

NT2_TEST_CASE_TPL ( predecessor_unsigned_int__2,  NT2_UNSIGNED_TYPES)
{
  using nt2::predecessor;
  using nt2::tag::predecessor_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<predecessor_(T,iT)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;

  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 

} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( predecessor_signed_int__2,  NT2_INTEGRAL_SIGNED_TYPES)
{
  using nt2::predecessor;
  using nt2::tag::predecessor_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<predecessor_(T,iT)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;

  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 

} // end of test for signed_int_