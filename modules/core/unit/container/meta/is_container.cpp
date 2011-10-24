/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::meta::is_container"

#include <nt2/core/container/meta/is_container.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Check is_container random non-container types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( value_is_not_container )
{
  using nt2::meta::is_container;
  
  NT2_TEST( !is_container<float       >::value );
  NT2_TEST( !is_container<float&      >::value );
  NT2_TEST( !is_container<float const >::value );
  NT2_TEST( !is_container<float const&>::value );
}

////////////////////////////////////////////////////////////////////////////////
// Check is_container container type
////////////////////////////////////////////////////////////////////////////////
struct some_container {};

namespace nt2 { namespace meta
{
  template<> struct is_container< ::some_container > : boost::mpl::true_ {};
} }

NT2_TEST_CASE( container_is_container )
{
  using nt2::meta::is_container;
  
  NT2_TEST( is_container<some_container       >::value );
  NT2_TEST( is_container<some_container&      >::value );
  NT2_TEST( is_container<some_container const >::value );
  NT2_TEST( is_container<some_container const&>::value );
}
