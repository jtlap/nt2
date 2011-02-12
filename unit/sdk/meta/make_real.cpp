/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::meta::make_real"

#include <boost/mpl/placeholders.hpp>
#include <nt2/sdk/config/types.hpp>
#include <nt2/sdk/meta/make_real.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test make_real output
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(make_real)
{
  using nt2::meta::make_real;
  using boost::is_same;
  using namespace nt2;

  NT2_TEST( (is_same<float  , make_real<4>::type >::value)  );
  NT2_TEST( (is_same<double , make_real<8>::type >::value)  );
}

////////////////////////////////////////////////////////////////////////////////
// Test make_real transformed output
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(make_real_transform)
{
  using nt2::meta::make_real;
  using boost::add_pointer;
  using boost::is_same;
  using boost::mpl::_;
  using namespace nt2;

  NT2_TEST( (is_same<float*  , make_real<4, add_pointer<_> >::type >::value)  );
  NT2_TEST( (is_same<double* , make_real<8, add_pointer<_> >::type >::value)  );
}
