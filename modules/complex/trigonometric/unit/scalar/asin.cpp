//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 complex.exponential toolbox - asin/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of exponential components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 08/12/2010
/// 
#include <nt2/include/functions/asin.hpp>
#include <nt2/include/functions/ulpdist.hpp>
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
#include <boost/math/complex/asin.hpp>


NT2_TEST_CASE_TPL ( asin_real__1_0,  (double))//NT2_REAL_TYPES)
{
  
  using nt2::asin;
  using nt2::tag::asin_;
  typedef std::complex<T> cT; 
  typedef typename nt2::meta::call<asin_(cT)>::type r_t;
  typedef typename nt2:: meta::as_complex<T>::type wished_r_t;


  // return type conformity test 
  //  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;
 

  // specific values tests
  NT2_TEST_ULP_EQUAL(nt2::asin(cT(nt2::Zero<T>(),  nt2::Zero<T>())), cT(nt2::Zero<T>(), nt2::Zero<T>()), 1);
  NT2_TEST_ULP_EQUAL(nt2::asin(cT(nt2::Nan  <T>(), nt2::Zero<T>())), cT(nt2::Nan <T>(), nt2::Nan<T>()), 1);

  NT2_TEST_ULP_EQUAL(nt2::asin(cT(nt2::Nan  <T>(), nt2::One<T>())),  cT(nt2::Nan <T>(), nt2::Nan<T>()), 1);
  NT2_TEST_ULP_EQUAL(nt2::asin(cT(nt2::Nan  <T>(), nt2::Inf<T>())),  cT(nt2::Nan <T>(), nt2::Inf<T>()), 1);
  NT2_TEST_ULP_EQUAL(nt2::asin(cT(nt2::Nan  <T>(), nt2::Nan<T>())),  cT(nt2::Nan <T>(), nt2::Nan<T>()), 1);
  NT2_TEST_ULP_EQUAL(nt2::asin(cT(nt2::Zero <T>(), nt2::Nan <T>())), cT(nt2::Zero<T>(), nt2::Nan<T>()), 1);
  NT2_TEST_ULP_EQUAL(nt2::asin(cT(nt2::One  <T>(), nt2::Nan <T>())), cT(nt2::Nan<T>(),  nt2::Nan<T>()), 1);
  NT2_TEST_ULP_EQUAL(nt2::asin(cT(nt2::Inf  <T>(), nt2::Nan<T>())),  cT(nt2::Nan <T>(), nt2::Inf<T>()), 1);
  NT2_TEST_ULP_EQUAL(nt2::asin(cT(nt2::One  <T>(), nt2::Inf <T>())), cT(nt2::Zero<T>(), nt2::Inf<T>()), 1);
  NT2_TEST_ULP_EQUAL(nt2::asin(cT(nt2::Inf  <T>(), nt2::One <T>())), cT(nt2::Pio_2<T>(), nt2::Inf <T>()), 1);
  NT2_TEST_ULP_EQUAL(nt2::asin(cT(nt2::Inf  <T>(), nt2::Inf<T>())),  cT(nt2::Pi<T>()/nt2::Four<T>(), nt2::Inf <T>()), 1);

  NT2_TEST_ULP_EQUAL(nt2::asin(cT(nt2::Nan  <T>(), -nt2::One<T>())),  cT(nt2::Nan <T>(), -nt2::Nan<T>()), 1);
  NT2_TEST_ULP_EQUAL(nt2::asin(cT(nt2::Nan  <T>(), -nt2::Inf<T>())),  cT(nt2::Nan <T>(), -nt2::Inf<T>()), 1);
  NT2_TEST_ULP_EQUAL(nt2::asin(cT(nt2::Nan  <T>(), -nt2::Nan<T>())),  cT(nt2::Nan <T>(), -nt2::Nan<T>()), 1);
  NT2_TEST_ULP_EQUAL(nt2::asin(cT(nt2::Zero <T>(), -nt2::Nan <T>())), cT(nt2::Zero<T>(), -nt2::Nan<T>()), 1);
  NT2_TEST_ULP_EQUAL(nt2::asin(cT(nt2::One  <T>(), -nt2::Nan <T>())), cT(nt2::Nan<T>(),  -nt2::Nan<T>()), 1);
  NT2_TEST_ULP_EQUAL(nt2::asin(cT(nt2::Inf  <T>(), -nt2::Nan<T>())),  cT(nt2::Nan <T>(),  nt2::Inf<T>()), 1);
  NT2_TEST_ULP_EQUAL(nt2::asin(cT(nt2::One  <T>(), -nt2::Inf <T>())), cT(nt2::Zero<T>(), -nt2::Inf<T>()), 1);
  NT2_TEST_ULP_EQUAL(nt2::asin(cT(nt2::Inf  <T>(), -nt2::One <T>())), cT(nt2::Pio_2<T>(), -nt2::Inf <T>()), 1);
  NT2_TEST_ULP_EQUAL(nt2::asin(cT(nt2::Inf  <T>(), -nt2::Inf<T>())),  cT(nt2::Pi<T>()/nt2::Four<T>(), -nt2::Inf <T>()), 1);

  NT2_TEST_ULP_EQUAL(nt2::asin(cT(nt2::One  <T>(), nt2::One <T>())),  cT(0.666239432492515, 1.061275061905036), 2);
  NT2_TEST_ULP_EQUAL(nt2::asin(cT(nt2::One  <T>(), nt2::Mone <T>())),  cT(0.666239432492515, -1.061275061905036), 2);  
  NT2_TEST_ULP_EQUAL(nt2::asin(cT(nt2::Mone  <T>(), nt2::One <T>())),  cT(-0.666239432492515, 1.061275061905036), 2);
  NT2_TEST_ULP_EQUAL(nt2::asin(cT(nt2::Mone  <T>(), nt2::Mone <T>())), cT(-0.666239432492515, -1.061275061905036), 2);  

  NT2_TEST_ULP_EQUAL(nt2::asin(cT(1, 1)),  boost::math::asin(cT(1, 1)), 1);
  NT2_TEST_ULP_EQUAL(nt2::asin(cT(1, 10)),  boost::math::asin(cT(1, 10)), 1);
  NT2_TEST_ULP_EQUAL(nt2::asin(cT(10, 10)),  boost::math::asin(cT(10, 10)), 1);
  NT2_TEST_ULP_EQUAL(nt2::asin(cT(10, 1)),  boost::math::asin(cT(10, 1)), 1);
 } // end of test for floating_
