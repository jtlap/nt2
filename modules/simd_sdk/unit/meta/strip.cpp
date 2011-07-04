/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::meta::strip"

#include <nt2/sdk/meta/strip.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that strip is correct
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(strip)
{
  using boost::is_same;
  using nt2::meta::strip;

  NT2_TEST( (is_same<double , strip<double>::type >::value)       );
  NT2_TEST( (is_same<double , strip<double&>::type >::value)      );
  NT2_TEST( (is_same<double , strip<double const>::type >::value) );
  NT2_TEST( (is_same<double , strip<double const&>::type >::value));
}
