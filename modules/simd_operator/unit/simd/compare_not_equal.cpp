//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define BOOST_SIMD_UNIT_MODULE "nt2 operator toolbox - compare_not_equal/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of operator components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
/// 
#include <boost/simd/toolbox/operator/include/compare_not_equal.hpp>
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


BOOST_SIMD_TEST_CASE_TPL ( compare_not_equal_real__2_0,  BOOST_SIMD_REAL_TYPES)
{
  using boost::simd::compare_not_equal;
  using boost::simd::tag::compare_not_equal_;
  using boost::simd::load; 
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::simd::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::simd::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::simd::meta::call<compare_not_equal_(vT,vT)>::type r_t;
  typedef typename boost::simd::meta::call<compare_not_equal_(T,T)>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  BOOST_SIMD_TEST_EQUAL(compare_not_equal(boost::simd::Inf<vT>(), boost::simd::Inf<vT>()), false);
  BOOST_SIMD_TEST_EQUAL(compare_not_equal(boost::simd::Minf<vT>(), boost::simd::Minf<vT>()), false);
  BOOST_SIMD_TEST_EQUAL(compare_not_equal(boost::simd::Nan<vT>(), boost::simd::Nan<vT>()), true);
  BOOST_SIMD_TEST_EQUAL(compare_not_equal(boost::simd::One<vT>(),boost::simd::Zero<vT>()), true);
  BOOST_SIMD_TEST_EQUAL(compare_not_equal(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), false);
} // end of test for real_
