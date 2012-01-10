//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::meta::container_traits"

#include <vector>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/meta/container_traits.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Check reference_
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( reference )
{
  using nt2::meta::reference_;
  using boost::is_same;
  using std::vector;

  NT2_TEST(( is_same < float&, reference_<float>::type >::value ));
  NT2_TEST(( is_same < float&, reference_< vector<float> >::type >::value ));
}

////////////////////////////////////////////////////////////////////////////////
// Check const_reference_
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( const_reference )
{
  using nt2::meta::const_reference_;
  using boost::is_same;
  using std::vector;

  NT2_TEST(( is_same < float const&, const_reference_<float>::type >::value ));
  NT2_TEST(( is_same < float const&, const_reference_< vector<float> >::type >::value ));
}

////////////////////////////////////////////////////////////////////////////////
// Check value_type_
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( value_type )
{
  using nt2::meta::value_type_;
  using boost::is_same;
  using std::vector;

  NT2_TEST(( is_same < float, value_type_<float>::type >::value ));
  NT2_TEST(( is_same < float, value_type_< vector<float> >::type >::value ));
}
