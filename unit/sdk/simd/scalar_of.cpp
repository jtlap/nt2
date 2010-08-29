/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::meta::scalar_of SIMD"

#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/simd/native.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that scalar_of on scalar is idempotent
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(scalar_of_scalar)
{
  using nt2::simd::native;
  using nt2::meta::scalar_of;
  using boost::is_same;
  using namespace nt2;

  typedef NT2_SIMD_DEFAULT_EXTENSION ext_t;

  #if defined(NT2_SIMD_SSE_FAMILY)
  NT2_TEST( (is_same<scalar_of<native<double  ,ext_t> >::type, double  >::value) );
  NT2_TEST( (is_same<scalar_of<native<uint64_t,ext_t> >::type, uint64_t>::value) );
  NT2_TEST( (is_same<scalar_of<native<int64_t ,ext_t> >::type , int64_t >::value) );
  #endif

  NT2_TEST( (is_same<scalar_of<native<float   ,ext_t> >::type, float   >::value) );
  NT2_TEST( (is_same<scalar_of<native<uint32_t,ext_t> >::type, uint32_t>::value) );
  NT2_TEST( (is_same<scalar_of<native<uint16_t,ext_t> >::type, uint16_t>::value) );
  NT2_TEST( (is_same<scalar_of<native<uint8_t ,ext_t> >::type , uint8_t >::value) );
  NT2_TEST( (is_same<scalar_of<native<int32_t ,ext_t> >::type , int32_t >::value) );
  NT2_TEST( (is_same<scalar_of<native<int16_t ,ext_t> >::type , int16_t >::value) );
  NT2_TEST( (is_same<scalar_of<native<int8_t ,ext_t> >::type  , int8_t  >::value) );

}
