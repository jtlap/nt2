//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 elliptic toolbox - ellipke/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of elliptic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 21/02/2011
/// modified by jt the 23/03/2011
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/toolbox/elliptic/include/ellipke.hpp>
#include <boost/fusion/tuple.hpp>
// specific includes for arity 1 tests
extern "C" {long double cephes_ellikl(long double,long double);}
#include <nt2/toolbox/trigonometric/include/constants.hpp>
#include <boost/fusion/tuple.hpp>
// specific includes for arity 2 tests
extern "C" {long double cephes_ellikl(long double,long double);}
#include <nt2/toolbox/trigonometric/include/constants.hpp>

NT2_TEST_CASE_TPL ( ellipke_real__1_0,  NT2_REAL_TYPES)
{
  
  using nt2::ellipke;
  using nt2::tag::ellipke_;
  typedef typename boost::result_of<nt2::meta::floating(T)>::type etype;
  typedef boost::fusion::tuple<etype,etype> rtype;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<ellipke_(T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef rtype wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,0>::type>::type r_t0;
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,1>::type>::type r_t1;
  {
    r_t res = ellipke(nt2::One<T>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res), nt2::Inf<r_t0>(), 0);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res), nt2::Zero<r_t1>(), 0);
  }
  {
    r_t res = ellipke(nt2::Zero<T>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res), nt2::Pio_2<r_t0>(), 0);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res), nt2::Pio_2<r_t1>(), 0);
  }
} // end of test for real_

NT2_TEST_CASE_TPL ( ellipke_real__2_1,  NT2_REAL_TYPES)
{
  
  using nt2::ellipke;
  using nt2::tag::ellipke_;
  typedef typename boost::result_of<nt2::meta::floating(T)>::type etype;
  typedef boost::fusion::tuple<etype,etype> rtype;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<ellipke_(T,T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef rtype wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,0>::type>::type r_t0;
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,1>::type>::type r_t1;
  {
    r_t res = ellipke(nt2::One<T>(),0);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res), nt2::Inf<r_t0>(), 0);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res), nt2::Zero<r_t1>(), 0);
  }
  {
    r_t res = ellipke(nt2::Zero<T>(),0);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res), nt2::Pio_2<r_t0>(), 0);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res), nt2::Pio_2<r_t1>(), 0);
  }
} // end of test for real_
