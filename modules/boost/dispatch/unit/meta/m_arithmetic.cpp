/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "boost::dispatch::meta::arithmetic"

#include <boost/dispatch/meta/result_of.hpp>
#include <boost/simd/sdk/config/types.hpp>
#include <boost/dispatch/meta/arithmetic.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test any with 1 types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( unary_arithmetic )
{
  using boost::dispatch::meta::arithmetic;
  using boost::dispatch::meta::result_of;
  using boost::is_same;

  NT2_TEST( (is_same<double, result_of<arithmetic(double)>::type >::value ) );
  NT2_TEST( (is_same<float, result_of<arithmetic(float )>::type >::value ) );
  NT2_TEST( (is_same<boost::simd::uint64_t, result_of<arithmetic(boost::simd::uint64_t )>::type >::value ) );
  NT2_TEST( (is_same<boost::simd::uint32_t, result_of<arithmetic(boost::simd::uint32_t )>::type >::value ) );
  NT2_TEST( (is_same<boost::simd::uint16_t, result_of<arithmetic(boost::simd::uint16_t )>::type >::value ) );
  NT2_TEST( (is_same<boost::simd::uint8_t, result_of<arithmetic(boost::simd::uint8_t )>::type >::value ) );
  NT2_TEST( (is_same<boost::simd::int64_t, result_of<arithmetic(boost::simd::int64_t )>::type >::value ) );
  NT2_TEST( (is_same<boost::simd::int32_t, result_of<arithmetic(boost::simd::int32_t )>::type >::value ) );
  NT2_TEST( (is_same<boost::simd::int16_t, result_of<arithmetic(boost::simd::int16_t )>::type >::value ) );
  NT2_TEST( (is_same<boost::simd::int8_t, result_of<arithmetic(boost::simd::int8_t )>::type >::value ) );
}

////////////////////////////////////////////////////////////////////////////////
// Test any with 2 types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( binary_arithmetic )
{
  using boost::dispatch::meta::arithmetic;
  using boost::dispatch::meta::result_of;
  using boost::is_same;

  NT2_TEST( (is_same<double, result_of<arithmetic(double,double)>::type >::value ) );
  NT2_TEST( (is_same<double, result_of<arithmetic(double,float )>::type >::value ) );
  NT2_TEST( (is_same<double, result_of<arithmetic(double,boost::simd::uint64_t )>::type >::value ) );
  NT2_TEST( (is_same<double, result_of<arithmetic(double,boost::simd::uint32_t )>::type >::value ) );
  NT2_TEST( (is_same<double, result_of<arithmetic(double,boost::simd::uint16_t )>::type >::value ) );
  NT2_TEST( (is_same<double, result_of<arithmetic(double,boost::simd::uint8_t )>::type >::value ) );
  NT2_TEST( (is_same<double, result_of<arithmetic(double,boost::simd::int64_t )>::type >::value ) );
  NT2_TEST( (is_same<double, result_of<arithmetic(double,boost::simd::int32_t )>::type >::value ) );
  NT2_TEST( (is_same<double, result_of<arithmetic(double,boost::simd::int16_t )>::type >::value ) );
  NT2_TEST( (is_same<double, result_of<arithmetic(double,boost::simd::int8_t )>::type >::value ) );

  NT2_TEST( (is_same<double, result_of<arithmetic(float,double)>::type >::value ) );
  NT2_TEST( (is_same<float , result_of<arithmetic(float,float )>::type >::value ) );
  NT2_TEST( (is_same<float , result_of<arithmetic(float,boost::simd::uint64_t )>::type >::value ) );
  NT2_TEST( (is_same<float , result_of<arithmetic(float,boost::simd::uint32_t )>::type >::value ) );
  NT2_TEST( (is_same<float , result_of<arithmetic(float,boost::simd::uint16_t )>::type >::value ) );
  NT2_TEST( (is_same<float , result_of<arithmetic(float,boost::simd::uint8_t )>::type >::value ) );
  NT2_TEST( (is_same<float , result_of<arithmetic(float,boost::simd::int64_t )>::type >::value ) );
  NT2_TEST( (is_same<float , result_of<arithmetic(float,boost::simd::int32_t )>::type >::value ) );
  NT2_TEST( (is_same<float , result_of<arithmetic(float,boost::simd::int16_t )>::type >::value ) );
  NT2_TEST( (is_same<float , result_of<arithmetic(float,boost::simd::int8_t )>::type >::value ) );

  NT2_TEST( (is_same<double, result_of<arithmetic(double,double)>::type >::value ) );
  NT2_TEST( (is_same<double, result_of<arithmetic(float,double )>::type >::value ) );
  NT2_TEST( (is_same<double, result_of<arithmetic(boost::simd::uint64_t,double )>::type >::value ) );
  NT2_TEST( (is_same<double, result_of<arithmetic(boost::simd::uint32_t,double )>::type >::value ) );
  NT2_TEST( (is_same<double, result_of<arithmetic(boost::simd::uint16_t,double )>::type >::value ) );
  NT2_TEST( (is_same<double, result_of<arithmetic(boost::simd::uint8_t ,double )>::type >::value ) );
  NT2_TEST( (is_same<double, result_of<arithmetic(boost::simd::int64_t ,double )>::type >::value ) );
  NT2_TEST( (is_same<double, result_of<arithmetic(boost::simd::int32_t ,double )>::type >::value ) );
  NT2_TEST( (is_same<double, result_of<arithmetic(boost::simd::int16_t ,double )>::type >::value ) );
  NT2_TEST( (is_same<double, result_of<arithmetic(boost::simd::int8_t  ,double )>::type >::value ) );

  NT2_TEST( (is_same<double, result_of<arithmetic(double,float)>::type >::value ) );
  NT2_TEST( (is_same<float , result_of<arithmetic(float ,float)>::type >::value ) );
  NT2_TEST( (is_same<float , result_of<arithmetic(boost::simd::uint64_t,float )>::type >::value ) );
  NT2_TEST( (is_same<float , result_of<arithmetic(boost::simd::uint32_t,float )>::type >::value ) );
  NT2_TEST( (is_same<float , result_of<arithmetic(boost::simd::uint16_t,float )>::type >::value ) );
  NT2_TEST( (is_same<float , result_of<arithmetic(boost::simd::uint8_t ,float )>::type >::value ) );
  NT2_TEST( (is_same<float , result_of<arithmetic(boost::simd::int64_t ,float )>::type >::value ) );
  NT2_TEST( (is_same<float , result_of<arithmetic(boost::simd::int32_t ,float )>::type >::value ) );
  NT2_TEST( (is_same<float , result_of<arithmetic(boost::simd::int16_t ,float )>::type >::value ) );
  NT2_TEST( (is_same<float , result_of<arithmetic(boost::simd::int8_t  ,float )>::type >::value ) );
}
