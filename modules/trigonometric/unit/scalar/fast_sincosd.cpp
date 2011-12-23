//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 trigonometric toolbox - fast_sincosd/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of trigonometric components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 11/02/2011
/// 
#include <nt2/toolbox/trigonometric/include/functions/fast_sincosd.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <boost/fusion/tuple.hpp>
#include <nt2/toolbox/trigonometric/constants.hpp>
#include <nt2/include/functions/sind.hpp>
#include <nt2/include/functions/cosd.hpp>

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


NT2_TEST_CASE_TPL ( fast_sincosd_real__1_0,  NT2_REAL_TYPES)
{
  
  using nt2::fast_sincosd;
  using nt2::tag::fast_sincosd_;
  typedef typename boost::dispatch::meta::as_floating<T>::type ftype;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<fast_sincosd_(T)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
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
    r_t res = fast_sincosd(nt2::Zero<T>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res), nt2::Zero<r_t0>(), 0.75);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res), nt2::One<r_t0>(), 0.75);
  }
  {
    r_t res = fast_sincosd(nt2::_45<T>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res), nt2::Sqrt_2o_2<r_t0>(), 0.75);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res), nt2::Sqrt_2o_2<r_t0>(), 0.75);
  }

  // specific values tests
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,0>::type>::type r_t0;
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,1>::type>::type r_t1;
  {
    r_t res = fast_sincosd(nt2::Zero<T>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res), nt2::Zero<r_t0>(), 0.75);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res), nt2::One<r_t0>(), 0.75);
  }
  {
    r_t res = fast_sincosd(nt2::_45<T>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res), nt2::Sqrt_2o_2<r_t0>(), 0.75);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res), nt2::Sqrt_2o_2<r_t0>(), 0.75);
  }
} // end of test for floating_

NT2_TEST_CASE_TPL ( fast_sincosd_unsigned_int__1_0,  NT2_UNSIGNED_TYPES)
{
  
  using nt2::fast_sincosd;
  using nt2::tag::fast_sincosd_;
  typedef typename boost::dispatch::meta::as_floating<T>::type ftype;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<fast_sincosd_(T)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
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
    r_t res = fast_sincosd(nt2::Zero<T>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res), nt2::Zero<r_t0>(), 0.75);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res), nt2::One<r_t0>(), 0.75);
  }
  {
    r_t res = fast_sincosd(nt2::_45<T>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res), nt2::Sqrt_2o_2<r_t0>(), 0.75);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res), nt2::Sqrt_2o_2<r_t0>(), 0.75);
  }

  // specific values tests
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,0>::type>::type r_t0;
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,1>::type>::type r_t1;
  {
    r_t res = fast_sincosd(nt2::Zero<T>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res), nt2::Zero<r_t0>(), 0.75);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res), nt2::One<r_t0>(), 0.75);
  }
  {
    r_t res = fast_sincosd(nt2::_45<T>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res), nt2::Sqrt_2o_2<r_t0>(), 0.75);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res), nt2::Sqrt_2o_2<r_t0>(), 0.75);
  }

  // specific values tests
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,0>::type>::type r_t0;
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,1>::type>::type r_t1;
  {
    r_t res = fast_sincosd(nt2::Zero<T>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res), nt2::Zero<r_t0>(), 0.75);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res), nt2::One<r_t0>(), 0.75);
  }
  {
    r_t res = fast_sincosd(nt2::_45<T>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res), nt2::Sqrt_2o_2<r_t0>(), 0.75);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res), nt2::Sqrt_2o_2<r_t0>(), 0.75);
  }

  // specific values tests
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,0>::type>::type r_t0;
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,1>::type>::type r_t1;
  {
    r_t res = fast_sincosd(nt2::Zero<T>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res), nt2::Zero<r_t0>(), 0.75);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res), nt2::One<r_t0>(), 0.75);
  }
  {
    r_t res = fast_sincosd(nt2::_45<T>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res), nt2::Sqrt_2o_2<r_t0>(), 0.75);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res), nt2::Sqrt_2o_2<r_t0>(), 0.75);
  }
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( fast_sincosd_signed_int__1_0,  NT2_INTEGRAL_SIGNED_TYPES)
{
  
  using nt2::fast_sincosd;
  using nt2::tag::fast_sincosd_;
  typedef typename boost::dispatch::meta::as_floating<T>::type ftype;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<fast_sincosd_(T)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
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
    r_t res = fast_sincosd(nt2::Zero<T>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res), nt2::Zero<r_t0>(), 0.75);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res), nt2::One<r_t0>(), 0.75);
  }
  {
    r_t res = fast_sincosd(nt2::_45<T>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res), nt2::Sqrt_2o_2<r_t0>(), 0.75);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res), nt2::Sqrt_2o_2<r_t0>(), 0.75);
  }

  // specific values tests
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,0>::type>::type r_t0;
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,1>::type>::type r_t1;
  {
    r_t res = fast_sincosd(nt2::Zero<T>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res), nt2::Zero<r_t0>(), 0.75);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res), nt2::One<r_t0>(), 0.75);
  }
  {
    r_t res = fast_sincosd(nt2::_45<T>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res), nt2::Sqrt_2o_2<r_t0>(), 0.75);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res), nt2::Sqrt_2o_2<r_t0>(), 0.75);
  }

  // specific values tests
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,0>::type>::type r_t0;
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,1>::type>::type r_t1;
  {
    r_t res = fast_sincosd(nt2::Zero<T>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res), nt2::Zero<r_t0>(), 0.75);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res), nt2::One<r_t0>(), 0.75);
  }
  {
    r_t res = fast_sincosd(nt2::_45<T>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res), nt2::Sqrt_2o_2<r_t0>(), 0.75);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res), nt2::Sqrt_2o_2<r_t0>(), 0.75);
  }

  // specific values tests
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,0>::type>::type r_t0;
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,1>::type>::type r_t1;
  {
    r_t res = fast_sincosd(nt2::Zero<T>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res), nt2::Zero<r_t0>(), 0.75);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res), nt2::One<r_t0>(), 0.75);
  }
  {
    r_t res = fast_sincosd(nt2::_45<T>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res), nt2::Sqrt_2o_2<r_t0>(), 0.75);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res), nt2::Sqrt_2o_2<r_t0>(), 0.75);
  }
} // end of test for signed_int_
