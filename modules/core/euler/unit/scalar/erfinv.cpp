//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 euler toolbox - erfinv/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of euler components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 22/02/2011
///
#include <nt2/toolbox/euler/include/functions/erfinv.hpp>
#include <nt2/include/functions/ulpdist.hpp>
extern "C" {long double cephes_erfinvl(long double);}

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


NT2_TEST_CASE_TPL ( erfinv_real__1_0, NT2_REAL_TYPES)
{

  using nt2::erfinv;
  using nt2::tag::erfinv_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<erfinv_(T)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename boost::dispatch::meta::as_floating<T>::type wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;

  // specific values tests
  NT2_TEST_ULP_EQUAL(erfinv(nt2::One<r_t>()      ),  nt2::Inf<T>()   , 10);
  NT2_TEST_ULP_EQUAL(erfinv(nt2::Zero<r_t>()     ),  nt2::Mzero<T>() , 10);
  NT2_TEST_ULP_EQUAL(erfinv(nt2::Nan<r_t>()      ),  nt2::Nan<T>()   , 10);
  NT2_TEST_ULP_EQUAL(erfinv(T(0.52049987781304653768274665389196) ),  nt2::Half<T>()  , 10);
  NT2_TEST_ULP_EQUAL(erfinv(T(0.842700792949714869341220635082610) ),  nt2::One<T>()   , 10);
  NT2_TEST_ULP_EQUAL(erfinv(T(0.99532226501895273416206925636725) ),  nt2::Two<T>()   , 10);
  NT2_TEST_ULP_EQUAL(erfinv(nt2::Zero<r_t>()     ),  nt2::Zero<T>()  , 10);
} // end of test for floating_
