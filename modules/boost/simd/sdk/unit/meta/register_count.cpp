//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/meta/register_count.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/pack.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL(register_count_integer, BOOST_SIMD_INTEGRAL_TYPES)
{
  using boost::simd::meta::register_count;

  NT2_TEST_EQUAL  ( register_count<T>::value     , BOOST_SIMD_GPR_COUNT);
}

NT2_TEST_CASE_TPL(register_count_real, BOOST_SIMD_REAL_TYPES)
{
  using boost::simd::meta::register_count;

  NT2_TEST_EQUAL  ( register_count<T>::value     , BOOST_SIMD_VR_COUNT);
}

NT2_TEST_CASE_TPL(register_count_simd, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::meta::register_count;
  using boost::simd::native;
  using boost::simd::pack;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                nT;
  typedef pack<T>                        pT;

  NT2_TEST_EQUAL  ( register_count<nT>::value , BOOST_SIMD_VR_COUNT);
  NT2_TEST_EQUAL  ( register_count<pT>::value , BOOST_SIMD_VR_COUNT);
}
