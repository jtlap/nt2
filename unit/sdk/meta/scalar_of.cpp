/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::meta::scalar_of.cpp"

#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that scalar_of on scalar is idempotent
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(scalar_of_scalar)
{
  using nt2::meta::scalar_of;
  using boost::is_same;
  using namespace nt2;

  NT2_TEST( (is_same<scalar_of<double>::type  , double  >::value) );
  NT2_TEST( (is_same<scalar_of<float>::type   , float   >::value) );
  NT2_TEST( (is_same<scalar_of<uint64_t>::type, uint64_t>::value) );
  NT2_TEST( (is_same<scalar_of<uint32_t>::type, uint32_t>::value) );
  NT2_TEST( (is_same<scalar_of<uint16_t>::type, uint16_t>::value) );
  NT2_TEST( (is_same<scalar_of<uint8_t>::type , uint8_t >::value) );
  NT2_TEST( (is_same<scalar_of<int64_t>::type , int64_t >::value) );
  NT2_TEST( (is_same<scalar_of<int32_t>::type , int32_t >::value) );
  NT2_TEST( (is_same<scalar_of<int16_t>::type , int16_t >::value) );
  NT2_TEST( (is_same<scalar_of<int8_t>::type  , int8_t  >::value) );
}

////////////////////////////////////////////////////////////////////////////////
// Test that scalar_of on simd::native<T,X> returns T
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(scalar_of_native_simd)
{
  using nt2::meta::scalar_of;
  using boost::is_same;
  using namespace nt2;

  #if defined(NT2_HAS_SSE2_SUPPORT)

  #elif defined(NT2_HAS_AVX_SUPPORT)

  #elif defined(NT2_HAS_VMX_SUPPORT)

  #endif
}
