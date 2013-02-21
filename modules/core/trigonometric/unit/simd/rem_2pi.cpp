//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/toolbox/trigonometric/include/functions/rem_2pi.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/constants/twopi.hpp>
#include <nt2/include/constants/zero.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>

NT2_TEST_CASE_TPL ( rem_2pi_real__1_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::rem_2pi;
  using nt2::tag::rem_2pi_;
  using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                vT;

  // specific values tests
  {
    vT res = rem_2pi(nt2::Zero<vT>());
    NT2_TEST_ULP_EQUAL( res, nt2::Zero<vT>(), 1.5);
    res = rem_2pi(nt2::Pi<vT>());
    NT2_TEST_ULP_EQUAL( res, nt2::Pi<vT>(), 1.5);
    res = rem_2pi(nt2::Twopi<vT>());
    NT2_TEST_ULP_EQUAL( res, nt2::Zero<vT>(), 1.5);
    res = rem_2pi(nt2::Pio_2<vT>());
    NT2_TEST_ULP_EQUAL( res, nt2::Pio_2<vT>(), 1.5);
  }
} // end of test for floating_

NT2_TEST_CASE_TPL ( rem_2pi_targeted,  NT2_SIMD_REAL_TYPES)
{

  using nt2::rem_2pi;
  using nt2::tag::rem_2pi_;
  using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                vT;

  vT x = nt2::Twopi<vT>(), xr;
  xr = rem_2pi(x, nt2::meta::as_<nt2::big_>());
  NT2_TEST_ULP_EQUAL( xr, nt2::Zero<vT>(), 1.5);


  xr = rem_2pi(x, nt2::meta::as_<nt2::medium_>());
  NT2_TEST_ULP_EQUAL( xr, nt2::Zero<vT>(), 1.5);


  xr = rem_2pi(x, nt2::meta::as_<nt2::small_>());
  NT2_TEST_ULP_EQUAL( xr, nt2::Zero<vT>(), 1.5);


  xr = rem_2pi(x, nt2::meta::as_<nt2::very_small_>());
  NT2_TEST_ULP_EQUAL( xr, nt2::Zero<vT>(), 1.5);

}
