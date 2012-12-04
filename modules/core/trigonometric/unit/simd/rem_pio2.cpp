//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 trigonometric toolbox - rem_pio2/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of trigonometric components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 11/02/2011
///
#include <nt2/toolbox/trigonometric/include/functions/rem_pio2.hpp>
#include <nt2/toolbox/trigonometric/constants.hpp>
#include <nt2/toolbox/constant/constant.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/meta/as_integer.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>

NT2_TEST_CASE_TPL ( rem_pio2_real__1_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::rem_pio2;
  using nt2::tag::rem_pio2_;
  using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::call<rem_pio2_(vT)>::type r_t;
  typedef typename nt2::meta::call<rem_pio2_(T)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;

  // specific values tests
  typedef typename boost::fusion::result_of::value_at_c<r_t,0>::type r_t0;
  typedef typename boost::fusion::result_of::value_at_c<r_t,1>::type r_t1;
  typedef typename boost::fusion::result_of::value_at_c<r_t,2>::type r_t2;
  {
    r_t res = rem_pio2(nt2::Zero<vT>());
    NT2_TEST_ULP_EQUAL( boost::fusion::get<0>(res)[0], nt2::Zero<r_t0>()[0], 0.5);
    NT2_TEST_ULP_EQUAL( boost::fusion::get<1>(res)[0], nt2::Zero<r_t1>()[0], 0.5);
    NT2_TEST_ULP_EQUAL( boost::fusion::get<2>(res)[0], nt2::Zero<r_t2>()[0], 0.5);
  }
} // end of test for floating_

NT2_TEST_CASE_TPL ( rem_pio2_targeted,  NT2_SIMD_REAL_TYPES)
{

  using nt2::rem_pio2;
  using nt2::tag::rem_pio2_;
  using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<vT>::type ivT;

  ivT n;
  vT x = nt2::Pio_2<vT>(), xr, xc;
  n = rem_pio2(x, xr, xc, nt2::meta::as_<nt2::big_>());
  NT2_TEST_ULP_EQUAL( xr[0], nt2::Zero<vT>()[0], 0.5);
  NT2_TEST_ULP_EQUAL( xc[0], nt2::Zero<vT>()[0], 0.5);

  n = rem_pio2(x, xr, xc, nt2::meta::as_<nt2::medium_>());
  NT2_TEST_ULP_EQUAL( xr[0], nt2::Zero<vT>()[0], 0.5);
  NT2_TEST_ULP_EQUAL( xc[0], nt2::Zero<vT>()[0], 0.5);

  n = rem_pio2(x, xr, xc, nt2::meta::as_<nt2::small_>());
  NT2_TEST_ULP_EQUAL( xr[0], nt2::Zero<vT>()[0], 0.5);
  NT2_TEST_ULP_EQUAL( xc[0], nt2::Zero<vT>()[0], 0.5);

  n = rem_pio2(x, xr, xc, nt2::meta::as_<nt2::very_small_>());
  NT2_TEST_ULP_EQUAL( xr[0], nt2::Zero<vT>()[0], 0.5);
  NT2_TEST_ULP_EQUAL( xc[0], nt2::Zero<vT>()[0], 0.5);
}
