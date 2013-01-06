//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.reduction toolbox - is_simd_logical/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.reduction components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 24/02/2011
///
#include <boost/simd/toolbox/reduction/include/functions/is_simd_logical.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>


NT2_TEST_CASE_TPL ( is_simd_logical_real__1_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::is_simd_logical;
  using boost::simd::tag::is_simd_logical_;
  using boost::simd::load;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<is_simd_logical_(vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef boost::simd::logical<T> vsr_t;

  // specific values tests
  NT2_TEST_EQUAL(is_simd_logical(-boost::simd::Nan<vT>()), vsr_t(false));
  NT2_TEST_EQUAL(is_simd_logical(boost::simd::Inf<vT>()), vsr_t(false));
  NT2_TEST_EQUAL(is_simd_logical(boost::simd::Minf<vT>()), vsr_t(false));
  NT2_TEST_EQUAL(is_simd_logical(boost::simd::Mone<vT>()), vsr_t(false));
  NT2_TEST_EQUAL(is_simd_logical(boost::simd::Nan<vT>()), vsr_t(true));
  NT2_TEST_EQUAL(is_simd_logical(boost::simd::One<vT>()), vsr_t(false));
  NT2_TEST_EQUAL(is_simd_logical(boost::simd::Zero<vT>()), vsr_t(true));
} // end of test for floating_
