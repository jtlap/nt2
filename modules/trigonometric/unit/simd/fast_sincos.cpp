//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 trigonometric toolbox - fast_sincos/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of trigonometric components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 11/02/2011
///
#include <nt2/toolbox/trigonometric/include/functions/fast_sincos.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <boost/fusion/tuple.hpp>
#include <nt2/toolbox/trigonometric/constants.hpp>
extern "C" {extern long double cephes_sinl(long double);}
extern "C" {extern long double cephes_cosl(long double);}

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
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/load.hpp>


NT2_TEST_CASE_TPL ( fast_sincos_real__1_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::fast_sincos;
  using nt2::tag::fast_sincos_;
  using nt2::load;
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef typename boost::dispatch::meta::as_floating<T>::type ftype;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<fast_sincos_(vT)>::type r_t;
  typedef typename nt2::meta::call<fast_sincos_(T)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;

  // specific values tests
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,0>::type>::type r_t0;
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,1>::type>::type r_t1;
  {
    r_t res = fast_sincos(nt2::Zero<vT>());
    NT2_TEST_ULP_EQUAL( boost::fusion::get<0>(res)[0], nt2::Zero<r_t0>()[0], 0.75);
    NT2_TEST_ULP_EQUAL( boost::fusion::get<1>(res)[0], nt2::One<r_t0>()[0], 0.75);
  }

  // specific values tests
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,0>::type>::type r_t0;
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,1>::type>::type r_t1;
  {
    r_t res = fast_sincos(nt2::Zero<vT>());
    NT2_TEST_ULP_EQUAL( boost::fusion::get<0>(res)[0], nt2::Zero<r_t0>()[0], 0.75);
    NT2_TEST_ULP_EQUAL( boost::fusion::get<1>(res)[0], nt2::One<r_t0>()[0], 0.75);
  }
} // end of test for floating_
