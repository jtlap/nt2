/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::settings id_ is an option"

#include <boost/type_traits/is_same.hpp>
#include <nt2/core/settings/settings.hpp>
#include <nt2/core/settings/id.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Pass some allocator_ as an option and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( single_id )
{
  using nt2::id_;
  using boost::is_same;
  using boost::mpl::string;
  using nt2::meta::option;

  NT2_TEST( ( is_same < string<'ping'>
                      , option< id_<'ping'>, nt2::tag::id_ >::type::type 
                      >::value
            ) 
          );
}

////////////////////////////////////////////////////////////////////////////////
// Pass some allocator_ as option with a default
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( single_id_default )
{
  using nt2::id_;
  using boost::is_same;
  using boost::mpl::string;
  using nt2::meta::option;

  NT2_TEST( ( is_same < string<'ping'>
                      , option< void, nt2::tag::id_, id_<'ping'> >::type::type 
                      >::value
            ) 
          );
}

////////////////////////////////////////////////////////////////////////////////
// Pass some id_ as settings
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( single_id_settings )
{
  using nt2::id_;
  using boost::is_same;
  using boost::mpl::string;
  using nt2::settings;
  using nt2::meta::option;

  NT2_TEST( ( is_same < string<'ping'>
                      , option< settings( id_<'pong'>, id_<'ping'> )
                              , nt2::tag::id_
                              >::type::type
                      >::value
            ) 
          );
}

//////////////////////////////////////////////////////////////////////////////////
//// Pass some id_ as settings with a default
//////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( id_settings )
{
  using nt2::id_;
  using boost::is_same;
  using boost::mpl::string;
  using nt2::settings;
  using nt2::meta::option;

  NT2_TEST( ( is_same < string<'ping'>
                      , option< settings( long, void* )
                              , nt2::tag::id_
                              , id_<'ping'>
                              >::type::type 
                      >::value
            ) 
          );
}
