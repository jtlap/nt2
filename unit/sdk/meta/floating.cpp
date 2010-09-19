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

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test any with 1 types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL	(	unary_floating_int
									, (nt2::int64_t)(nt2::int32_t)(nt2::int16_t)(nt2::int8_t)
										(nt2::uint64_t)(nt2::uint32_t)(nt2::uint16_t)(nt2::uint8_t)
									)
{
	using nt2::meta::floating;
	using std::tr1::result_of;
	using boost::is_same;

	NT2_TEST( (is_same<NT2_DEFAULT_REAL_TYPE, typename result_of<floating(T)>::type >::value ) );
}

////////////////////////////////////////////////////////////////////////////////
// Test any with 2 types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( binary_floating )
{
	using nt2::meta::floating;
	using std::tr1::result_of;
	using boost::is_same;

	NT2_TEST( (is_same<double, result_of<floating(double,double)>::type >::value ) );
	NT2_TEST( (is_same<double, result_of<floating(double,float )>::type >::value ) );
	NT2_TEST( (is_same<double, result_of<floating(double,nt2::uint64_t )>::type >::value ) );
	NT2_TEST( (is_same<double, result_of<floating(double,nt2::uint32_t )>::type >::value ) );
	NT2_TEST( (is_same<double, result_of<floating(double,nt2::uint16_t )>::type >::value ) );
	NT2_TEST( (is_same<double, result_of<floating(double,nt2::uint8_t )>::type >::value ) );
	NT2_TEST( (is_same<double, result_of<floating(double,nt2::int64_t )>::type >::value ) );
	NT2_TEST( (is_same<double, result_of<floating(double,nt2::int32_t )>::type >::value ) );
	NT2_TEST( (is_same<double, result_of<floating(double,nt2::int16_t )>::type >::value ) );
	NT2_TEST( (is_same<double, result_of<floating(double,nt2::int8_t )>::type >::value ) );

	NT2_TEST( (is_same<double, result_of<floating(float,double)>::type >::value ) );
	NT2_TEST( (is_same<float , result_of<floating(float,float )>::type >::value ) );
	NT2_TEST( (is_same<float , result_of<floating(float,nt2::uint64_t )>::type >::value ) );
	NT2_TEST( (is_same<float , result_of<floating(float,nt2::uint32_t )>::type >::value ) );
	NT2_TEST( (is_same<float , result_of<floating(float,nt2::uint16_t )>::type >::value ) );
	NT2_TEST( (is_same<float , result_of<floating(float,nt2::uint8_t )>::type >::value ) );
	NT2_TEST( (is_same<float , result_of<floating(float,nt2::int64_t )>::type >::value ) );
	NT2_TEST( (is_same<float , result_of<floating(float,nt2::int32_t )>::type >::value ) );
	NT2_TEST( (is_same<float , result_of<floating(float,nt2::int16_t )>::type >::value ) );
	NT2_TEST( (is_same<float , result_of<floating(float,nt2::int8_t )>::type >::value ) );

	NT2_TEST( (is_same<double, result_of<floating(double,double)>::type >::value ) );
	NT2_TEST( (is_same<double, result_of<floating(float,double )>::type >::value ) );
	NT2_TEST( (is_same<double, result_of<floating(nt2::uint64_t,double )>::type >::value ) );
	NT2_TEST( (is_same<double, result_of<floating(nt2::uint32_t,double )>::type >::value ) );
	NT2_TEST( (is_same<double, result_of<floating(nt2::uint16_t,double )>::type >::value ) );
	NT2_TEST( (is_same<double, result_of<floating(nt2::uint8_t ,double )>::type >::value ) );
	NT2_TEST( (is_same<double, result_of<floating(nt2::int64_t ,double )>::type >::value ) );
	NT2_TEST( (is_same<double, result_of<floating(nt2::int32_t ,double )>::type >::value ) );
	NT2_TEST( (is_same<double, result_of<floating(nt2::int16_t ,double )>::type >::value ) );
	NT2_TEST( (is_same<double, result_of<floating(nt2::int8_t  ,double )>::type >::value ) );

	NT2_TEST( (is_same<double, result_of<floating(double,float)>::type >::value ) );
	NT2_TEST( (is_same<float , result_of<floating(float ,float)>::type >::value ) );
	NT2_TEST( (is_same<float , result_of<floating(nt2::uint64_t,float )>::type >::value ) );
	NT2_TEST( (is_same<float , result_of<floating(nt2::uint32_t,float )>::type >::value ) );
	NT2_TEST( (is_same<float , result_of<floating(nt2::uint16_t,float )>::type >::value ) );
	NT2_TEST( (is_same<float , result_of<floating(nt2::uint8_t ,float )>::type >::value ) );
	NT2_TEST( (is_same<float , result_of<floating(nt2::int64_t ,float )>::type >::value ) );
	NT2_TEST( (is_same<float , result_of<floating(nt2::int32_t ,float )>::type >::value ) );
	NT2_TEST( (is_same<float , result_of<floating(nt2::int16_t ,float )>::type >::value ) );
	NT2_TEST( (is_same<float , result_of<floating(nt2::int8_t  ,float )>::type >::value ) );
}
