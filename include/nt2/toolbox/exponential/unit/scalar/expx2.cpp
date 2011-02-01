//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 exponential toolbox - expx2/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of exponential components in scalar mode
//////////////////////////////////////////////////////////////////////////////
///  created by jt the 08/12/2010
/// modified by jt the 14/12/2010
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/toolbox/exponential/include/expx2.hpp>
// specific includes for arity 1 tests
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/sqrt.hpp>

NT2_TEST_CASE_TPL ( expx2_real__1,  NT2_REAL_TYPES)
{
  using nt2::expx2;
  using nt2::tag::expx2_;
  typedef typename nt2::meta::call<expx2_(T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename boost::result_of<nt2::meta::floating(T)>::type wished_r_t;

  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 


  // specific values tests
  NT2_TEST_ULP_EQUAL(  expx2(nt2::Inf<T>()), nt2::Inf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(  expx2(nt2::Minf<T>()), nt2::Inf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(  expx2(nt2::Mone<T>()), nt2::Exp_1<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(  expx2(nt2::Nan<T>()), nt2::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(  expx2(nt2::One<T>()), nt2::Exp_1<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(  expx2(nt2::Zero<T>()), nt2::One<r_t>(), 0);
  // random verifications
  static const uint32_t NR = 100;
  {
    NT2_CREATE_BUFFER(a0,T, 100, T(0), T(5));
    for (int j =0; j < NR; ++j )
      {
        std::cout << "for param "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << std::endl;
        NT2_TEST_ULP_EQUAL( nt2::log(nt2::expx2(nt2::sqrt(a0))),a0,7);
     }
   }
} // end of test for real_

NT2_TEST_CASE_TPL ( expx2_unsigned_int__1,  NT2_UNSIGNED_TYPES)
{
  using nt2::expx2;
  using nt2::tag::expx2_;
  typedef typename nt2::meta::call<expx2_(T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename boost::result_of<nt2::meta::floating(T)>::type wished_r_t;

  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 


  // specific values tests
  NT2_TEST_ULP_EQUAL(  expx2(nt2::One<T>()), nt2::Exp_1<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(  expx2(nt2::Zero<T>()), nt2::One<r_t>(), 0);
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( expx2_signed_int__1,  NT2_INTEGRAL_SIGNED_TYPES)
{
  using nt2::expx2;
  using nt2::tag::expx2_;
  typedef typename nt2::meta::call<expx2_(T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename boost::result_of<nt2::meta::floating(T)>::type wished_r_t;

  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 


  // specific values tests
  NT2_TEST_ULP_EQUAL(  expx2(nt2::Mone<T>()), nt2::Exp_1<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(  expx2(nt2::One<T>()), nt2::Exp_1<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(  expx2(nt2::Zero<T>()), nt2::One<r_t>(), 0);
} // end of test for signed_int_