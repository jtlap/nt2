/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define BOOST_SIMD_UNIT_MODULE "boost::simd::meta::make_real"

#include <boost/mpl/placeholders.hpp>
#include <boost/simd/sdk/config/types.hpp>
#include <boost/simd/sdk/meta/make_real.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/simd/sdk/unit/module.hpp>
#include <boost/simd/sdk/unit/tests/basic.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test make_real output
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(make_real)
{
  using boost::simd::meta::make_real;
  using boost::is_same;
  using namespace boost;

  BOOST_SIMD_TEST( (is_same<float  , make_real<4>::type >::value)  );
  BOOST_SIMD_TEST( (is_same<double , make_real<8>::type >::value)  );
}

////////////////////////////////////////////////////////////////////////////////
// Test make_real transformed output
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(make_real_transform)
{
  using boost::simd::meta::make_real;
  using boost::add_pointer;
  using boost::is_same;
  using boost::mpl::_;
  using namespace boost;

  BOOST_SIMD_TEST( (is_same<float*  , make_real<4, add_pointer<_> >::type >::value)  );
  BOOST_SIMD_TEST( (is_same<double* , make_real<8, add_pointer<_> >::type >::value)  );
}
