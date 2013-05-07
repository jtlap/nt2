//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "boost::dispatch::meta::make_real"

#include <boost/mpl/placeholders.hpp>
#include <boost/simd/sdk/config/types.hpp>
#include <boost/dispatch/meta/make_floating.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test make_floating output
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(make_floating)
{
  using boost::dispatch::meta::make_floating;
  using boost::is_same;
  using namespace boost::simd;

  NT2_TEST( (is_same<float  , make_floating<4>::type >::value)  );
  NT2_TEST( (is_same<double , make_floating<8>::type >::value)  );
}

////////////////////////////////////////////////////////////////////////////////
// Test make_floating transformed output
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(make_real_transform)
{
  using boost::dispatch::meta::make_floating;
  using boost::add_pointer;
  using boost::is_same;
  using boost::mpl::_;
  using namespace boost::simd;

  NT2_TEST( (is_same<float*  , make_floating<4, add_pointer<_> >::type >::value)  );
  NT2_TEST( (is_same<double* , make_floating<8, add_pointer<_> >::type >::value)  );
}
