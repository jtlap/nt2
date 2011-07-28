//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define BOOST_SIMD_UNIT_MODULE "nt2 reduction toolbox - sum/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of reduction components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 24/02/2011
/// 
#include <boost/simd/toolbox/reduction/include/sum.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/sdk/unit/tests.hpp>
#include <boost/simd/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <boost/simd/include/constants/real.hpp>
#include <boost/simd/include/constants/infinites.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <boost/simd/include/functions/load.hpp>


BOOST_SIMD_TEST_CASE_TPL ( sum_real__1_0,  BOOST_SIMD_REAL_TYPES)
{
  using boost::simd::sum;
  using boost::simd::tag::sum_;
  using boost::simd::load; 
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef typename boost::dispatch::meta::scalar_of<T>::type sT;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<sum_(vT)>::type r_t;
  typedef typename boost::dispatch::meta::call<sum_(T)>::type sr_t;
  typedef typename boost::dispatch::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  BOOST_SIMD_TEST_ULP_EQUAL(sum(boost::simd::Inf<vT>()), boost::simd::Inf<sr_t>(), 0);
  BOOST_SIMD_TEST_ULP_EQUAL(sum(boost::simd::Minf<vT>()), boost::simd::Minf<sr_t>(), 0);
  BOOST_SIMD_TEST_ULP_EQUAL(sum(boost::simd::Mone<vT>()), -int(cardinal_of<n_t>()), 0);
  BOOST_SIMD_TEST_ULP_EQUAL(sum(boost::simd::Nan<vT>()), boost::simd::Nan<sr_t>(), 0);
  BOOST_SIMD_TEST_ULP_EQUAL(sum(boost::simd::One<vT>()), int(cardinal_of<n_t>()), 0);
  BOOST_SIMD_TEST_ULP_EQUAL(sum(boost::simd::Zero<vT>()), boost::simd::Zero<sr_t>(), 0);
} // end of test for real_
