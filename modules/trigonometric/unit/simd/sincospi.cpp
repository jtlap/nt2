//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 trigonometric toolbox - sincospi/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of trigonometric components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 11/02/2011
/// modified by jt the 18/04/2011
#include <nt2/sdk/memory/is_aligned.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>
#include <nt2/sdk/memory/load.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/toolbox/trigonometric/include/sincospi.hpp>
#include <boost/fusion/tuple.hpp>

NT2_TEST_CASE_TPL ( sincospi_real__1_0,  NT2_REAL_TYPES)
{
  using nt2::sincospi;
  using nt2::tag::sincospi_;
  using nt2::load; 
  using nt2::simd::native;
  using nt2::meta::cardinal_of;
  typedef typename boost::result_of<nt2::meta::floating(T)>::type ftype;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<sincospi_(vT)>::type r_t;
  typedef typename nt2::meta::call<sincospi_(T)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,0>::type>::type r_t0;
  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,1>::type>::type r_t1;
  {
    r_t res = sincospi(-nt2::Quarter<vT>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res)[0], -nt2::Sqrt_2o_2<r_t0>()[0], 0.75);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res)[0], nt2::Sqrt_2o_2<r_t0>()[0], 0.75);
  }
  {
    r_t res = sincospi(nt2::Half<vT>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res)[0], nt2::One<r_t0>()[0], 0.75);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res)[0], nt2::Zero<r_t0>()[0], 0.75);
  }
  {
    r_t res = sincospi(nt2::Inf<vT>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res)[0], nt2::Nan<r_t0>()[0], 0.75);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res)[0], nt2::Nan<r_t0>()[0], 0.75);
  }
  {
    r_t res = sincospi(nt2::Mhalf<vT>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res)[0], nt2::Mone<r_t0>()[0], 0.75);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res)[0], nt2::Zero<r_t1>()[0], 0.75);
  }
  {
    r_t res = sincospi(nt2::Minf<vT>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res)[0], nt2::Nan<r_t0>()[0], 0.75);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res)[0], nt2::Nan<r_t0>()[0], 0.75);
  }
  {
    r_t res = sincospi(nt2::Mone<vT>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res)[0], nt2::Zero<r_t0>()[0], 0.75);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res)[0], nt2::Mone<r_t1>()[0], 0.75);
  }
  {
    r_t res = sincospi(nt2::Nan<vT>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res)[0], nt2::Nan<r_t0>()[0], 0.75);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res)[0], nt2::Nan<r_t0>()[0], 0.75);
  }
  {
    r_t res = sincospi(nt2::One<vT>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res)[0], nt2::Zero<r_t0>()[0], 0.75);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res)[0], nt2::Mone<r_t1>()[0], 0.75);
  }
  {
    r_t res = sincospi(nt2::Quarter<vT>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res)[0], nt2::Sqrt_2o_2<r_t0>()[0], 0.75);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res)[0], nt2::Sqrt_2o_2<r_t0>()[0], 0.75);
  }
  {
    r_t res = sincospi(nt2::Zero<vT>());
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(res)[0], nt2::Zero<r_t0>()[0], 0.75);
    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(res)[0], nt2::One<r_t0>()[0], 0.75);
  }
} // end of test for real_
