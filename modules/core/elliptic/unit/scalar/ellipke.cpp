//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 elliptic toolbox - ellipke/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of elliptic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 21/02/2011
///
#include <nt2/toolbox/elliptic/include/functions/ellipke.hpp>
#include <boost/fusion/tuple.hpp>
extern "C" {long double cephes_ellikl(long double,long double);}
#include <nt2/toolbox/trigonometric/constants.hpp>

#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/meta/as_signed.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/type_traits/common_type.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/toolbox/constant/constant.hpp>




NT2_TEST_CASE_TPL ( ellipke_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::ellipke;
  using nt2::tag::ellipke_;
  typedef typename boost::dispatch::meta::as_floating<T>::type etype;
  typedef boost::fusion::tuple<etype,etype> rtype;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<ellipke_(T)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
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
    NT2_TEST_ULP_EQUAL( boost::fusion::get<0>(res), nt2::Inf<r_t0>(), 0.5);
    NT2_TEST_ULP_EQUAL( boost::fusion::get<1>(res), nt2::One<r_t1>(), 0.5);
  }
  {
    r_t res = ellipke(nt2::Zero<T>());
    NT2_TEST_ULP_EQUAL( boost::fusion::get<0>(res), nt2::Pio_2<r_t0>(), 0.5);
    NT2_TEST_ULP_EQUAL( boost::fusion::get<1>(res), nt2::Pio_2<r_t1>(), 0.5);
  }

  // specific values tests
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,0>::type>::type r_t0;
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,1>::type>::type r_t1;
  {
    r_t res = ellipke(nt2::One<T>());
    NT2_TEST_ULP_EQUAL( boost::fusion::get<0>(res), nt2::Inf<r_t0>(), 0.5);
    NT2_TEST_ULP_EQUAL( boost::fusion::get<1>(res), nt2::One<r_t1>(), 0.5);
  }
  {
    r_t res = ellipke(nt2::Zero<T>());
    NT2_TEST_ULP_EQUAL( boost::fusion::get<0>(res), nt2::Pio_2<r_t0>(), 0.5);
    NT2_TEST_ULP_EQUAL( boost::fusion::get<1>(res), nt2::Pio_2<r_t1>(), 0.5);
  }
} // end of test for floating_

NT2_TEST_CASE_TPL ( ellipke_real__2_1,  NT2_REAL_TYPES)
{

  using nt2::ellipke;
  using nt2::tag::ellipke_;
  typedef T scalar;
  typedef typename boost::dispatch::meta::as_floating<T>::type etype;
  typedef boost::fusion::tuple<etype,etype> rtype;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<ellipke_(T,scalar)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
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
    r_t res = ellipke(nt2::One<T>(),nt2::Eps<scalar>());
    NT2_TEST_ULP_EQUAL( boost::fusion::get<0>(res), nt2::Inf<r_t0>(), 0.5);
    NT2_TEST_ULP_EQUAL( boost::fusion::get<1>(res), nt2::One<r_t1>(), 0.5);
  }
  {
    r_t res = ellipke(nt2::Zero<T>(),nt2::Eps<scalar>());
    NT2_TEST_ULP_EQUAL( boost::fusion::get<0>(res), nt2::Pio_2<r_t0>(), 0.5);
    NT2_TEST_ULP_EQUAL( boost::fusion::get<1>(res), nt2::Pio_2<r_t1>(), 0.5);
  }

  // specific values tests
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,0>::type>::type r_t0;
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,1>::type>::type r_t1;
  {
    r_t res = ellipke(nt2::One<T>(),nt2::Eps<scalar>());
    NT2_TEST_ULP_EQUAL( boost::fusion::get<0>(res), nt2::Inf<r_t0>(), 0.5);
    NT2_TEST_ULP_EQUAL( boost::fusion::get<1>(res), nt2::One<r_t1>(), 0.5);
  }
  {
    r_t res = ellipke(nt2::Zero<T>(),nt2::Eps<scalar>());
    NT2_TEST_ULP_EQUAL( boost::fusion::get<0>(res), nt2::Pio_2<r_t0>(), 0.5);
    NT2_TEST_ULP_EQUAL( boost::fusion::get<1>(res), nt2::Pio_2<r_t1>(), 0.5);
  }
} // end of test for floating_
