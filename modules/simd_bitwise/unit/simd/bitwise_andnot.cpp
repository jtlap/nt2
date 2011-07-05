//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define BOOST_SIMD_UNIT_MODULE "nt2 bitwise toolbox - bitwise_andnot/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of bitwise components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
/// 
#include <boost/simd/toolbox/bitwise/include/bitwise_andnot.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/simd/sdk/functor/meta/call.hpp>
#include <boost/simd/sdk/unit/tests.hpp>
#include <boost/simd/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <boost/simd/include/constants/real.hpp>
#include <boost/simd/include/constants/infinites.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <boost/simd/include/functions/load.hpp>


BOOST_SIMD_TEST_CASE_TPL ( bitwise_andnot_real__2_0,  BOOST_SIMD_REAL_TYPES)
{
  using boost::simd::bitwise_andnot;
  using boost::simd::tag::bitwise_andnot_;
  using boost::simd::load; 
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::simd::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::simd::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::simd::meta::call<bitwise_andnot_(vT,vT)>::type r_t;
  typedef typename boost::simd::meta::call<bitwise_andnot_(T,T)>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  BOOST_SIMD_TEST_EQUAL(bitwise_andnot(boost::simd::Inf<vT>(), boost::simd::Inf<vT>())[0], boost::simd::Zero<sr_t>());
  BOOST_SIMD_TEST_EQUAL(bitwise_andnot(boost::simd::Minf<vT>(), boost::simd::Minf<vT>())[0], boost::simd::Zero<sr_t>());
  BOOST_SIMD_TEST_EQUAL(bitwise_andnot(boost::simd::Nan<vT>(), boost::simd::Nan<vT>())[0], boost::simd::Zero<sr_t>());
  BOOST_SIMD_TEST_EQUAL(bitwise_andnot(boost::simd::One<vT>(),boost::simd::Zero<vT>())[0], boost::simd::One<sr_t>());
  BOOST_SIMD_TEST_EQUAL(bitwise_andnot(boost::simd::Zero<vT>(), boost::simd::Zero<vT>())[0], boost::simd::Zero<sr_t>());
} // end of test for real_
