//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.predicates toolbox - is_finite/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.predicates components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 21/02/2011
///
#include <nt2/include/functions/is_finite.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/sdk/simd/logical.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/toolbox/constant/constant.hpp>
#include <nt2/include/functions/load.hpp>
#include <nt2/toolbox/constant/constant.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/dry.hpp>
#include <nt2/sdk/complex/imaginary.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_imaginary.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>


NT2_TEST_CASE_TPL ( is_finite_real__1_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using nt2::is_finite;
  using nt2::tag::is_finite_;
  using nt2::load;
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<is_finite_(vT)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef std::complex<T> cT;
  typedef nt2::imaginary<T> ciT;
  typedef native<std::complex<T>, ext_t> cvT;
  typedef native<nt2::imaginary<T>, ext_t > civT;
  typedef native<nt2::dry<T>, ext_t > divT;

  // specific values tests
  NT2_TEST_EQUAL(is_finite(nt2::Mzero<cvT>())[0], nt2::True<sr_t>());
  NT2_TEST_EQUAL(is_finite(nt2::Half<cvT>())[0], nt2::True<sr_t>());
  NT2_TEST_EQUAL(is_finite(nt2::Inf<cvT>())[0], nt2::False<sr_t>());
  NT2_TEST_EQUAL(is_finite(nt2::Minf<cvT>())[0], nt2::False<sr_t>());
  NT2_TEST_EQUAL(is_finite(nt2::Mone<cvT>())[0], nt2::True<sr_t>());
  NT2_TEST_EQUAL(is_finite(nt2::Nan<cvT>())[0], nt2::False<sr_t>());
  NT2_TEST_EQUAL(is_finite(nt2::One<cvT>())[0], nt2::True<sr_t>());
  NT2_TEST_EQUAL(is_finite(nt2::Quarter<cvT>())[0], nt2::True<sr_t>());
  NT2_TEST_EQUAL(is_finite(nt2::Two<cvT>())[0], nt2::True<sr_t>());
  NT2_TEST_EQUAL(is_finite(nt2::Zero<cvT>())[0], nt2::True<sr_t>());
} // end of test for floating_

