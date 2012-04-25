//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 euler toolbox - erfc/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of euler components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 22/02/2011
/// 
#include <nt2/toolbox/euler/include/functions/erfc.hpp>
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
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/three.hpp>
#include <nt2/include/constants/four.hpp>
#include <nt2/include/constants/eight.hpp>


NT2_TEST_CASE_TPL ( erfc_real__1_0,  NT2_REAL_TYPES)
{
//   T a = nt2::Eight<T>()*(nt2::Pi<T>()-nt2::Three<T>())/(nt2::Three<T>()*nt2::Pi<T>()*(nt2::Four<T>()-nt2::Pi<T>()));
//      std::cout << std::setprecision(20) << a << std::endl;
//      std::cout << nt2::Four<T>()/nt2::Pi<T>()<< std::endl;
  
  using nt2::erfc;
  using nt2::tag::erfc_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<erfc_(T)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename boost::dispatch::meta::as_floating<T>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_ULP_EQUAL(erfc(nt2::Inf<T>()), nt2::Zero<r_t>(), 200);
  NT2_TEST_ULP_EQUAL(erfc(nt2::Mzero<T>()), nt2::One<r_t>(), 200);
  NT2_TEST_ULP_EQUAL(erfc(nt2::Nan<T>()), nt2::Nan<r_t>(), 200);
  NT2_TEST_ULP_EQUAL(erfc(nt2::Half<T>()), T( 1-0.520499877813047), 200);
  NT2_TEST_ULP_EQUAL(erfc(nt2::One<T>()), T(1-0.842700792949715), 200);
  NT2_TEST_ULP_EQUAL(erfc(nt2::Two<T>()), T(1-0.995322265018953), 200);
  NT2_TEST_ULP_EQUAL(erfc(nt2::Zero<T>()), nt2::One<r_t>(), 200);
} // end of test for floating_
