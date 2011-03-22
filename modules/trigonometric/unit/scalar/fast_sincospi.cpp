//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 trigonometric toolbox - fast_sincospi/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of trigonometric components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 11/02/2011
/// modified by jt the 23/03/2011
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/toolbox/trigonometric/include/fast_sincospi.hpp>
#include <boost/fusion/tuple.hpp>
// specific includes for arity 1 tests
#include <nt2/toolbox/trigonometric/include/constants.hpp>
#include <nt2/include/functions/sin.hpp>
#include <nt2/include/functions/cos.hpp>

NT2_TEST_CASE_TPL ( fast_sincospi_real__1_0,  NT2_REAL_TYPES)
{
  
  using nt2::fast_sincospi;
  using nt2::tag::fast_sincospi_;
  typedef typename boost::result_of<nt2::meta::floating(T)>::type ftype;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<fast_sincospi_(T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef boost::fusion::tuple<ftype,ftype> wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,0>::type>::type r_t0;
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,1>::type>::type r_t1;
  {
    r_t res = fast_sincospi(-nt2::Quarter<T>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res), -nt2::Sqrt_2o_2<r_t0>(), 0.75);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res), nt2::Sqrt_2o_2<r_t0>(), 0.75);
  }
  {
    r_t res = fast_sincospi(nt2::Half<T>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res), nt2::Nan<r_t0>(), 0.75);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res), nt2::Nan<r_t0>(), 0.75);
  }
  {
    r_t res = fast_sincospi(nt2::Inf<T>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res), nt2::Nan<r_t0>(), 0.75);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res), nt2::Nan<r_t0>(), 0.75);
  }
  {
    r_t res = fast_sincospi(nt2::Mhalf<T>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res), nt2::Nan<r_t0>(), 0.75);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res), nt2::Nan<r_t1>(), 0.75);
  }
  {
    r_t res = fast_sincospi(nt2::Minf<T>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res), nt2::Nan<r_t0>(), 0.75);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res), nt2::Nan<r_t0>(), 0.75);
  }
  {
    r_t res = fast_sincospi(nt2::Nan<T>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res), nt2::Nan<r_t0>(), 0.75);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res), nt2::Nan<r_t0>(), 0.75);
  }
  {
    r_t res = fast_sincospi(nt2::Quarter<T>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res), nt2::Sqrt_2o_2<r_t0>(), 0.75);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res), nt2::Sqrt_2o_2<r_t0>(), 0.75);
  }
  {
    r_t res = fast_sincospi(nt2::Zero<T>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res), nt2::Zero<r_t0>(), 0.75);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res), nt2::One<r_t0>(), 0.75);
  }
  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    typedef typename boost::result_of<nt2::meta::floating(T)>::type ftype;
    NT2_CREATE_BUF(tab_a0,T, NR, T(0.25), T(0.25));
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    T a0;
    for (uint32_t j =0; j < NR; ++j )
      {
        std::cout << "for param "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << std::endl;
        r_t r = nt2::fast_sincospi(a0);
        typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,0>::type>::type r_t0;
        typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,1>::type>::type r_t1;
        r_t0 r0 = boost::fusion::get<0>(r);
        r_t1 r1 = boost::fusion::get<1>(r);
        NT2_TEST_TUPLE_ULP_EQUAL( r0, nt2::sin(nt2::Pi<T>()*a0), 0.5);
        NT2_TEST_TUPLE_ULP_EQUAL( r1, nt2::cos(nt2::Pi<T>()*a0), 0.5);
     }
     std::cout << "max ulp found is: " << ulp0 << std::endl;
   }
} // end of test for real_

NT2_TEST_CASE_TPL ( fast_sincospi_unsigned_int__1_0,  NT2_UNSIGNED_TYPES)
{
  
  using nt2::fast_sincospi;
  using nt2::tag::fast_sincospi_;
  typedef typename boost::result_of<nt2::meta::floating(T)>::type ftype;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<fast_sincospi_(T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef boost::fusion::tuple<ftype,ftype> wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,0>::type>::type r_t0;
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,1>::type>::type r_t1;
  {
    r_t res = fast_sincospi(nt2::Zero<T>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res), nt2::Zero<r_t0>(), 0.75);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res), nt2::One<r_t0>(), 0.75);
  }
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( fast_sincospi_signed_int__1_0,  NT2_INTEGRAL_SIGNED_TYPES)
{
  
  using nt2::fast_sincospi;
  using nt2::tag::fast_sincospi_;
  typedef typename boost::result_of<nt2::meta::floating(T)>::type ftype;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<fast_sincospi_(T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef boost::fusion::tuple<ftype,ftype> wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,0>::type>::type r_t0;
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,1>::type>::type r_t1;
  {
    r_t res = fast_sincospi(nt2::Zero<T>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res), nt2::Zero<r_t0>(), 0.75);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res), nt2::One<r_t0>(), 0.75);
  }
} // end of test for signed_int_
