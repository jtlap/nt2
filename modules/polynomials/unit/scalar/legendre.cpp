//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 polynomials toolbox - legendre/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of polynomials components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 06/03/2011
/// modified by jt the 06/03/2011
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/toolbox/polynomials/include/legendre.hpp>
// specific includes for arity 2 tests
#include <nt2/toolbox/boost_math/include/legendre_p.hpp>

NT2_TEST_CASE_TPL ( legendre_real__2,  NT2_REAL_TYPES)
{
  
  using nt2::legendre;
  using nt2::tag::legendre_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<legendre_(iT,T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename std::tr1::result_of<nt2::meta::floating(T)>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;


  // specific values tests
  NT2_TEST_ULP_EQUAL(legendre(1,nt2::Half<T>()), nt2::Half<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(legendre(1,nt2::Inf<T>()), nt2::Nan<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(legendre(1,nt2::Minf<T>()), nt2::Nan<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(legendre(1,nt2::Nan<T>()), nt2::Nan<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(legendre(1,nt2::One<T>()), nt2::One<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(legendre(1,nt2::Zero<T>()), nt2::Zero<r_t>(), 0.5);
  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,iT, NR, iT(0), T(10));
    NT2_CREATE_BUF(tab_a1,T, NR, iT(-1), T(1));
    double ulp0 = 0.0, ulpd = 0.0;
    iT a0;
    T a1;
    for (int j =0; j < NR; ++j )
      {
        std::cout << "for params "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << ", a1 = "<< u_t(a1 = tab_a1[j])
                  << std::endl;
        NT2_TEST_ULP_EQUAL( nt2::legendre(a0,a1),nt2::boost_math::legendre_p(a0,a1),0.5);
        ulp0=nt2::max(ulpd,ulp0);
     }
     std::cout << "max ulp found is: " << ulp0 << std::endl;
   }
} // end of test for real_

NT2_TEST_CASE_TPL ( legendre_unsigned_int__2,  NT2_UNSIGNED_TYPES)
{
  
  using nt2::legendre;
  using nt2::tag::legendre_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<legendre_(iT,T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename std::tr1::result_of<nt2::meta::floating(T)>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;


  // specific values tests
  NT2_TEST_ULP_EQUAL(legendre(1,nt2::One<T>()), nt2::One<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(legendre(1,nt2::Zero<T>()), nt2::Zero<r_t>(), 0.5);
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( legendre_signed_int__2,  NT2_INTEGRAL_SIGNED_TYPES)
{
  
  using nt2::legendre;
  using nt2::tag::legendre_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<legendre_(iT,T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename std::tr1::result_of<nt2::meta::floating(T)>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;


  // specific values tests
  NT2_TEST_ULP_EQUAL(legendre(1,nt2::One<T>()), nt2::One<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(legendre(1,nt2::Zero<T>()), nt2::Zero<r_t>(), 0.5);
} // end of test for signed_int_
