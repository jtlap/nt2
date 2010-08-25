/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::functors::find_type"

#include <nt2/sdk/config/types.hpp>
#include <nt2/sdk/functor/hierarchy.hpp>
#include <nt2/sdk/functor/meta/find_type.hpp>
#include <boost/type_traits/is_same.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that T is found among T
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(find_type_trivial)
{
  using nt2::functors::empty_;
  using nt2::meta::find_type;
  using nt2::meta::belong_to;
  using boost::is_same;

  NT2_TEST( (is_same<find_type<float, float>::type, float>::value) );
}

////////////////////////////////////////////////////////////////////////////////
// Test that T is found among a list of types containing T
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(find_type_trivial_list)
{
  using nt2::functors::empty_;
  using nt2::meta::find_type;
  using nt2::meta::belong_to;
  using boost::is_same;

  NT2_TEST( (is_same<find_type<float,double,float,nt2::int32_t>::type, float>::value) );
}

////////////////////////////////////////////////////////////////////////////////
// Test that T is found among a hierarchy
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(find_type_hierarchy)
{
  using nt2::functors::real_;
  using nt2::meta::find_type;
  using nt2::meta::belong_to;
  using boost::is_same;

  NT2_TEST( (is_same<find_type<float,real_>::type, real_>::value) );
}

////////////////////////////////////////////////////////////////////////////////
// Test that T is found among a hierarchy list
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(find_type_hierarchies)
{
  using nt2::functors::int_;
  using nt2::functors::real_;
  using nt2::functors::unsigned_;
  using nt2::meta::find_type;
  using nt2::meta::belong_to;
  using boost::is_same;

  NT2_TEST( (is_same<find_type<float,int_,unsigned_,real_>::type, real_>::value) );
}

////////////////////////////////////////////////////////////////////////////////
// Test that T is found among the first matching hierarchy in the list
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(find_type_hierarchy_order)
{
  using nt2::functors::int_;
  using nt2::functors::real_;
  using nt2::functors::unsigned_;
  using nt2::meta::find_type;
  using nt2::meta::belong_to;
  using boost::is_same;

  NT2_TEST( (is_same<find_type<float,float,unsigned_,real_>::type, float>::value) );
}
