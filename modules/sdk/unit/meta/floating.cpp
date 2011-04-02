/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::meta::floating"

#include <boost/tr1/functional.hpp>
#include <nt2/sdk/config/types.hpp>
#include <nt2/sdk/meta/floating.hpp>
#include <boost/type_traits/is_same.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test any with 1 types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL (  unary_floating_t32
                  , (nt2::int32_t)(nt2::int16_t)(nt2::int8_t)(float)
                    (nt2::uint32_t)(nt2::uint16_t)(nt2::uint8_t)(bool)
                  )
{
  using nt2::meta::floating;
  using std::tr1::result_of;
  using boost::is_same;

  NT2_TEST( (is_same<float, typename result_of<floating(T)>::type >::value ) );
}

NT2_TEST_CASE_TPL (  unary_floating_t64
                  , (nt2::int64_t)(nt2::uint64_t)(double)
                  )
{
  using nt2::meta::floating;
  using std::tr1::result_of;
  using boost::is_same;

  NT2_TEST( (is_same<double, typename result_of<floating(T)>::type >::value ) );
}

////////////////////////////////////////////////////////////////////////////////
// Test any with 2 types, one being 64 bits
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL ( binary_floating_t64
                  , (nt2::int64_t)(nt2::uint64_t)(double)
                  )
{
  using nt2::meta::floating;
  using std::tr1::result_of;
  using boost::is_same;

  NT2_TEST( (is_same<double, typename result_of<floating(T,double)>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(T,float )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(T,nt2::uint64_t )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(T,nt2::uint32_t )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(T,nt2::uint16_t )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(T,nt2::uint8_t )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(T,nt2::int64_t )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(T,nt2::int32_t )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(T,nt2::int16_t )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(T,nt2::int8_t )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(T,bool )>::type >::value ) );

  NT2_TEST( (is_same<double, typename result_of<floating(double,T)>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(float,T )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(nt2::uint64_t,T )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(nt2::uint32_t,T )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(nt2::uint16_t,T )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(nt2::uint8_t,T )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(nt2::int64_t,T )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(nt2::int32_t,T )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(nt2::int16_t,T )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(nt2::int8_t,T )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(bool,T )>::type >::value ) );
}

////////////////////////////////////////////////////////////////////////////////
// Test any with 2 types, one being 32 or less  bits
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL ( binary_floating_t32
                  , (nt2::int32_t)(nt2::int16_t)(nt2::int8_t)(float)
                    (nt2::uint32_t)(nt2::uint16_t)(nt2::uint8_t)(bool)
                  )
{
  using nt2::meta::floating;
  using std::tr1::result_of;
  using boost::is_same;

  NT2_TEST( (is_same<double, typename result_of<floating(T,double)>::type >::value ) );
  NT2_TEST( (is_same<float , typename result_of<floating(T,float )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(T,nt2::uint64_t )>::type >::value ) );
  NT2_TEST( (is_same<float , typename result_of<floating(T,nt2::uint32_t )>::type >::value ) );
  NT2_TEST( (is_same<float , typename result_of<floating(T,nt2::uint16_t )>::type >::value ) );
  NT2_TEST( (is_same<float , typename result_of<floating(T,nt2::uint8_t )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(T,nt2::int64_t )>::type >::value ) );
  NT2_TEST( (is_same<float , typename result_of<floating(T,nt2::int32_t )>::type >::value ) );
  NT2_TEST( (is_same<float , typename result_of<floating(T,nt2::int16_t )>::type >::value ) );
  NT2_TEST( (is_same<float , typename result_of<floating(T,nt2::int8_t )>::type >::value ) );
  NT2_TEST( (is_same<float , typename result_of<floating(T,bool )>::type >::value ) );

  NT2_TEST( (is_same<double, typename result_of<floating(double,T)>::type >::value ) );
  NT2_TEST( (is_same<float, typename result_of<floating(float,T )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(nt2::uint64_t,T )>::type >::value ) );
  NT2_TEST( (is_same<float, typename result_of<floating(nt2::uint32_t,T )>::type >::value ) );
  NT2_TEST( (is_same<float, typename result_of<floating(nt2::uint16_t,T )>::type >::value ) );
  NT2_TEST( (is_same<float, typename result_of<floating(nt2::uint8_t,T )>::type >::value ) );
  NT2_TEST( (is_same<double, typename result_of<floating(nt2::int64_t,T )>::type >::value ) );
  NT2_TEST( (is_same<float, typename result_of<floating(nt2::int32_t,T )>::type >::value ) );
  NT2_TEST( (is_same<float, typename result_of<floating(nt2::int16_t,T )>::type >::value ) );
  NT2_TEST( (is_same<float, typename result_of<floating(nt2::int8_t,T )>::type >::value ) );
  NT2_TEST( (is_same<float, typename result_of<floating(bool,T )>::type >::value ) );
}
