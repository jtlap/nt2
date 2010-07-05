/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::meta::category_of"

#include <nt2/sdk/meta/category_of.hpp>
#include <boost/type_traits/is_same.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test category of unregistered types
////////////////////////////////////////////////////////////////////////////////
struct bar {};

NT2_TEST_CASE(unknown_types)
{
  using nt2::meta::category_of;
  using nt2::tag::unknown;
  NT2_TEST( (boost::is_same< category_of<bar>::type, unknown >::value) );
}

////////////////////////////////////////////////////////////////////////////////
// Test category of type with category_tag
////////////////////////////////////////////////////////////////////////////////
struct foo { struct  foo_tag {}; typedef foo_tag nt2_category_tag; };

NT2_TEST_CASE(tagged_types)
{
  using nt2::meta::category_of;
  NT2_TEST( (boost::is_same< category_of<foo>::type, foo::foo_tag >::value) );
}


////////////////////////////////////////////////////////////////////////////////
// Test category of type with overlaoded category_of
////////////////////////////////////////////////////////////////////////////////
struct man { struct man_tag {}; };

namespace nt2 { namespace meta
{
  template<> struct category_of<man> { typedef man::man_tag type; };
} }

NT2_TEST_CASE(overloading_types)
{
  using nt2::meta::category_of;
  NT2_TEST( (boost::is_same< category_of<man>::type, man::man_tag >::value) );
}
