//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 trigonometric toolbox - rem_2pi/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of trigonometric components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 11/02/2011
///
#include <nt2/toolbox/trigonometric/include/functions/rem_2pi.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/isulpequal.hpp>
#include <boost/fusion/tuple.hpp>
#include <nt2/toolbox/trigonometric/constants.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/twopi.hpp>
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


NT2_TEST_CASE_TPL ( rem_2pi_targeted, NT2_REAL_TYPES)
{

  using nt2::rem_2pi;
  using nt2::tag::rem_2pi_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<rem_2pi_(T)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename nt2::meta::call<rem_2pi_(T)>::type wished_r_t;

  nt2::uint32_t n;
  T x = nt2::Pi<T>(), xr, xc;
  rem_2pi(x, xr, xc, nt2::meta::as_<nt2::big_>());
    NT2_TEST_ULP_EQUAL(xr, nt2::Pi<T>(), 0.5);
//   NT2_TEST(nt2::isulpequal(xr, nt2::Pi<T>(), 0.5)||nt2::isulpequal(xr, -nt2::Pi<T>(), 0.5));
  rem_2pi(x, xr, xc, nt2::meta::as_<nt2::medium_>());
    NT2_TEST_ULP_EQUAL(xr, nt2::Pi<T>(), 0.5);
//   NT2_TEST(nt2::isulpequal(xr, nt2::Pi<T>(), 0.5)||nt2::isulpequal(xr, -nt2::Pi<T>(), 0.5));
  rem_2pi(x, xr, xc, nt2::meta::as_<nt2::small_>());
    NT2_TEST_ULP_EQUAL(xr, nt2::Pi<T>(), 0.5);
//   NT2_TEST(nt2::isulpequal(xr, nt2::Pi<T>(), 0.5)||nt2::isulpequal(xr, -nt2::Pi<T>(), 0.5));
  rem_2pi(x, xr, xc, nt2::meta::as_<nt2::very_small_>());
    NT2_TEST_ULP_EQUAL(xr, nt2::Pi<T>(), 0.5);
//   NT2_TEST(nt2::isulpequal(xr, nt2::Pi<T>(), 0.5)||nt2::isulpequal(xr, -nt2::Pi<T>(), 0.5));
  std::cout << " ==================== " << std::endl;
  x =  5*nt2::Pi<T>()/4;
  T r = -3*nt2::Pi<T>()/4;
  rem_2pi(x, xr, xc, nt2::meta::as_<nt2::big_>());
  NT2_TEST_ULP_EQUAL(xr, r, 0.5);
  rem_2pi(x, xr, xc, nt2::meta::as_<nt2::medium_>());
  NT2_TEST_ULP_EQUAL(xr,r, 0.5);
  rem_2pi(x, xr, xc, nt2::meta::as_<nt2::small_>());
  NT2_TEST_ULP_EQUAL(xr,r, 0.5);
  rem_2pi(x, xr, xc, nt2::meta::as_<nt2::very_small_>());
  NT2_TEST_ULP_EQUAL(xr,r, 0.5);
  std::cout << " ==================== " << std::endl;
  x =  nt2::Pi<T>()/4;
  r = nt2::Pi<T>()/4;
  rem_2pi(x, xr, xc, nt2::meta::as_<nt2::big_>());
  NT2_TEST_ULP_EQUAL(xr, r, 0.5);
  rem_2pi(x, xr, xc, nt2::meta::as_<nt2::medium_>());
  NT2_TEST_ULP_EQUAL(xr,r, 0.5);
  rem_2pi(x, xr, xc, nt2::meta::as_<nt2::small_>());
  NT2_TEST_ULP_EQUAL(xr,r, 0.5);
  rem_2pi(x, xr, xc, nt2::meta::as_<nt2::very_small_>());
  NT2_TEST_ULP_EQUAL(xr,r, 0.5);
  std::cout << " ==================== " << std::endl;
  x =  nt2::Pi<T>()*10.25;
  r = nt2::Pi<T>()*0.25;
  rem_2pi(x, xr, xc, nt2::meta::as_<nt2::big_>());
  NT2_TEST_ULP_EQUAL(xr, r, 20);
  rem_2pi(x, xr, xc, nt2::meta::as_<nt2::medium_>());
  NT2_TEST_ULP_EQUAL(xr,r, 20);
  rem_2pi(x, xr, xc, nt2::meta::as_<nt2::small_>());
  NT2_TEST_ULP_EQUAL(xr,r, 20);

}
