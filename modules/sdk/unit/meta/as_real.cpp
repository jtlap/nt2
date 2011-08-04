/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::meta::as_real"

#include <nt2/sdk/config/types.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <boost/type_traits/is_same.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that as_real is correct w/r to original sign
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(as_real)
{
  using nt2::meta::as_real;
  using boost::is_same;

  NT2_TEST( (is_same<as_real<double       >::type,double  >::value ));
  NT2_TEST( (is_same<as_real<float        >::type,float   >::value ));
  NT2_TEST( (is_same<as_real<nt2::int64_t >::type,double  >::value ));
  NT2_TEST( (is_same<as_real<nt2::int32_t >::type,float   >::value ));
  NT2_TEST( (is_same<as_real<nt2::uint64_t>::type,double  >::value ));
  NT2_TEST( (is_same<as_real<nt2::uint32_t>::type,float   >::value ));
}
