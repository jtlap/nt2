/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::functors::category"

#include <nt2/sdk/config/types.hpp>
#include <nt2/sdk/functor/category.hpp>
#include <nt2/sdk/meta/category_of.hpp>
#include <boost/type_traits/is_same.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that fundamental types are in tag::scalar(tag::arithmetic) category
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(fundamental_category)
{
  using nt2::tag::scalar_;
  using nt2::tag::arithmetic_;
  using nt2::meta::category_of;
  using boost::is_same;

  NT2_TEST( (is_same<category_of<bool>::type::tag     , scalar_(arithmetic_)>::value) );
  NT2_TEST( (is_same<category_of<double>::type::tag   , scalar_(arithmetic_)>::value) );
  NT2_TEST( (is_same<category_of<float>::type::tag    , scalar_(arithmetic_)>::value) );
  NT2_TEST( (is_same<category_of<nt2::uint8_t>::type::tag  , scalar_(arithmetic_)>::value) );
  NT2_TEST( (is_same<category_of<nt2::uint16_t>::type::tag , scalar_(arithmetic_)>::value) );
  NT2_TEST( (is_same<category_of<nt2::uint32_t>::type::tag , scalar_(arithmetic_)>::value) );
  NT2_TEST( (is_same<category_of<nt2::uint64_t>::type::tag , scalar_(arithmetic_)>::value) );
  NT2_TEST( (is_same<category_of<nt2::int8_t>::type::tag   , scalar_(arithmetic_)>::value) );
  NT2_TEST( (is_same<category_of<nt2::int16_t>::type::tag  , scalar_(arithmetic_)>::value) );
  NT2_TEST( (is_same<category_of<nt2::int32_t>::type::tag  , scalar_(arithmetic_)>::value) );
  NT2_TEST( (is_same<category_of<nt2::int64_t>::type::tag  , scalar_(arithmetic_)>::value) );
}
