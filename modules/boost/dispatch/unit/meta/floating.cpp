/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "boost::dispatch::meta::floating"

#include <boost/dispatch/meta/result_of.hpp>
#include <boost/simd/sdk/config/types.hpp>
#include <boost/dispatch/meta/floating.hpp>
#include <boost/type_traits/is_same.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test any with 1 types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL (  unary_floating_t32
                  , (boost::simd::int32_t)(boost::simd::int16_t)(boost::simd::int8_t)(float)
                    (boost::simd::uint32_t)(boost::simd::uint16_t)(boost::simd::uint8_t)(bool)
                  )
{
  using boost::dispatch::meta::floating;
  using boost::dispatch::meta::result_of;
  using boost::is_same;

  NT2_TEST( (is_same<float, typename result_of<floating(T)>::type >::value ) );
}

NT2_TEST_CASE_TPL (  unary_floating_t64
                  , (boost::simd::int64_t)(boost::simd::uint64_t)(double)
                  )
{
  using boost::dispatch::meta::floating;
  using boost::dispatch::meta::result_of;
  using boost::is_same;

  NT2_TEST( (is_same<double, typename result_of<floating(T)>::type >::value ) );
}

////////////////////////////////////////////////////////////////////////////////
// Test any with 2 types, one being 64 bits
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL ( binary_floating_t64
                  , (boost::simd::int64_t)(boost::simd::uint64_t)(double)
                  )
{
  using boost::dispatch::meta::floating;
  using boost::dispatch::meta::result_of;
  using boost::is_same;

  NT2_TEST( (is_same<double, typename result_of<floating(T,double)>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(T,float )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(T,boost::simd::uint64_t )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(T,boost::simd::uint32_t )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(T,boost::simd::uint16_t )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(T,boost::simd::uint8_t )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(T,boost::simd::int64_t )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(T,boost::simd::int32_t )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(T,boost::simd::int16_t )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(T,boost::simd::int8_t )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(T,bool )>::type >::value ) );

  NT2_TEST( (is_same<double, typename result_of<floating(double,T)>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(float,T )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(boost::simd::uint64_t,T )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(boost::simd::uint32_t,T )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(boost::simd::uint16_t,T )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(boost::simd::uint8_t,T )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(boost::simd::int64_t,T )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(boost::simd::int32_t,T )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(boost::simd::int16_t,T )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(boost::simd::int8_t,T )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(bool,T )>::type >::value ) );
}

////////////////////////////////////////////////////////////////////////////////
// Test any with 2 types, one being 32 or less  bits
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL ( binary_floating_t32
                  , (boost::simd::int32_t)(boost::simd::int16_t)(boost::simd::int8_t)(float)
                    (boost::simd::uint32_t)(boost::simd::uint16_t)(boost::simd::uint8_t)(bool)
                  )
{
  using boost::dispatch::meta::floating;
  using boost::dispatch::meta::result_of;
  using boost::is_same;

  NT2_TEST( (is_same<double, typename result_of<floating(T,double)>::type >::value ) );
  NT2_TEST( (is_same<float , typename result_of<floating(T,float )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(T,boost::simd::uint64_t )>::type >::value ) );
  NT2_TEST( (is_same<float , typename result_of<floating(T,boost::simd::uint32_t )>::type >::value ) );
  NT2_TEST( (is_same<float , typename result_of<floating(T,boost::simd::uint16_t )>::type >::value ) );
  NT2_TEST( (is_same<float , typename result_of<floating(T,boost::simd::uint8_t )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(T,boost::simd::int64_t )>::type >::value ) );
  NT2_TEST( (is_same<float , typename result_of<floating(T,boost::simd::int32_t )>::type >::value ) );
  NT2_TEST( (is_same<float , typename result_of<floating(T,boost::simd::int16_t )>::type >::value ) );
  NT2_TEST( (is_same<float , typename result_of<floating(T,boost::simd::int8_t )>::type >::value ) );
  NT2_TEST( (is_same<float , typename result_of<floating(T,bool )>::type >::value ) );

  NT2_TEST( (is_same<double, typename result_of<floating(double,T)>::type >::value ) );
  NT2_TEST( (is_same<float, typename result_of<floating(float,T )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(boost::simd::uint64_t,T )>::type >::value ) );
  NT2_TEST( (is_same<float, typename result_of<floating(boost::simd::uint32_t,T )>::type >::value ) );
  NT2_TEST( (is_same<float, typename result_of<floating(boost::simd::uint16_t,T )>::type >::value ) );
  NT2_TEST( (is_same<float, typename result_of<floating(boost::simd::uint8_t,T )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(boost::simd::int64_t,T )>::type >::value ) );
  NT2_TEST( (is_same<float, typename result_of<floating(boost::simd::int32_t,T )>::type >::value ) );
  NT2_TEST( (is_same<float, typename result_of<floating(boost::simd::int16_t,T )>::type >::value ) );
  NT2_TEST( (is_same<float, typename result_of<floating(boost::simd::int8_t,T )>::type >::value ) );
  NT2_TEST( (is_same<float, typename result_of<floating(bool,T )>::type >::value ) );
}
