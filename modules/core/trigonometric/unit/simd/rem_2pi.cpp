//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 trigonometric toolbox - rem_2pi/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of trigonometric components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 11/02/2011
///
#include <nt2/toolbox/trigonometric/include/functions/rem_2pi.hpp>
#include <nt2/toolbox/trigonometric/constants.hpp>
#include <nt2/toolbox/constant/constant.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>

NT2_TEST_CASE_TPL ( rem_2pi_real__1_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::rem_2pi;
  using nt2::tag::rem_2pi_;
  using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::call<rem_2pi_(vT)>::type r_t;
  typedef typename nt2::meta::call<rem_2pi_(T)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;

  // specific values tests
  typedef typename boost::fusion::result_of::value_at_c<r_t,0>::type r_t0;
  typedef typename boost::fusion::result_of::value_at_c<r_t,1>::type r_t1;
  {
    r_t res = rem_2pi(nt2::Zero<vT>());
    NT2_TEST_ULP_EQUAL( boost::fusion::get<0>(res)[0], nt2::Zero<r_t0>()[0], 0.5);
    NT2_TEST_ULP_EQUAL( boost::fusion::get<1>(res)[0], nt2::Zero<r_t1>()[0], 0.5);
  }
} // end of test for floating_

NT2_TEST_CASE_TPL ( rem_2pi_targeted,  NT2_SIMD_REAL_TYPES)
{

  using nt2::rem_2pi;
  using nt2::tag::rem_2pi_;
  using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;

  vT x = nt2::Zero<vT>(), xr, xc;
  rem_2pi(x, xr, xc, nt2::meta::as_<nt2::big_>());
  rem_2pi(x, xr, xc, nt2::meta::as_<nt2::medium_>());
  rem_2pi(x, xr, xc, nt2::meta::as_<nt2::small_>());
  rem_2pi(x, xr, xc, nt2::meta::as_<nt2::very_small_>());
}
