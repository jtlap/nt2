//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 polynomials toolbox - tchebeval/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of polynomials components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 06/03/2011
/// 
#include <nt2/toolbox/polynomials/include/functions/tchebeval.hpp>
#include <nt2/include/functions/ulpdist.hpp>
//#include <nt2/toolbox/cephes/include/functions/tchebeval.hpp>

#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/include/constants/infinites.hpp>

//COMMENTED
NT2_TEST_CASE_TPL ( tchebeval_real__2_0,  NT2_REAL_TYPES)
{
  
//   using nt2::tchebeval;
//   using nt2::tag::tchebeval_;
//   typedef typename nt2::meta::as_integer<T>::type iT;
//   typedef typename nt2::meta::call<tchebeval_(T,T)>::type r_t;
//   typedef typename nt2::meta::upgrade<T>::type u_t;
//   typedef typename boost::dispatch::meta::as_floating<T>::type wished_r_t;


//   // return type conformity test 
//   NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
//   std::cout << std::endl; 

//   // specific values tests
//   NT2_TEST_ULP_EQUAL(tchebeval(nt2::Inf<T>(), nt2::Inf<T>()), nt2::Inf<r_t>(), 0.5);
//   NT2_TEST_ULP_EQUAL(tchebeval(nt2::Minf<T>(), nt2::Minf<T>()), nt2::Zero<r_t>(), 0.5);
//   NT2_TEST_ULP_EQUAL(tchebeval(nt2::Nan<T>(), nt2::Nan<T>()), nt2::Nan<r_t>(), 0.5);
//   NT2_TEST_ULP_EQUAL(tchebeval(nt2::Zero<T>(), nt2::Zero<T>()), nt2::Zero<r_t>(), 0.5);
// } // end of test for floating_

// NT2_TEST_CASE_TPL ( tchebeval_unsigned_int__2_0,  NT2_UNSIGNED_TYPES)
// {
  
//   using nt2::tchebeval;
//   using nt2::tag::tchebeval_;
//   typedef typename nt2::meta::as_integer<T>::type iT;
//   typedef typename nt2::meta::call<tchebeval_(T,T)>::type r_t;
//   typedef typename nt2::meta::upgrade<T>::type u_t;
//   typedef typename boost::dispatch::meta::as_floating<T>::type wished_r_t;


//   // return type conformity test 
//   NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
//   std::cout << std::endl; 

//   // specific values tests
//   NT2_TEST_ULP_EQUAL(tchebeval(nt2::Zero<T>(), nt2::Zero<T>()), nt2::Zero<r_t>(), 0.5);
// } // end of test for unsigned_int_

// NT2_TEST_CASE_TPL ( tchebeval_signed_int__2_0,  NT2_INTEGRAL_SIGNED_TYPES)
// {
  
//   using nt2::tchebeval;
//   using nt2::tag::tchebeval_;
//   typedef typename nt2::meta::as_integer<T>::type iT;
//   typedef typename nt2::meta::call<tchebeval_(T,T)>::type r_t;
//   typedef typename nt2::meta::upgrade<T>::type u_t;
//   typedef typename boost::dispatch::meta::as_floating<T>::type wished_r_t;


//   // return type conformity test 
//   NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
//   std::cout << std::endl; 


//   // specific values tests
//  NT2_TEST_ULP_EQUAL(tchebeval(nt2::Zero<T>(), nt2::Zero<T>()), nt2::Zero<r_t>(), 0.5);
} // end of test for signed_int_
