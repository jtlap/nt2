/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::settings id_ is an option"

#include <nt2/core/settings/settings.hpp>
#include <nt2/core/settings/id.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

////////////////////////////////////////////////////////////////////////////////
// Pass some allocator_ as an option and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( single_id )
{
  using nt2::id_;
  using boost::mpl::string;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE( (id_<'ping'>())
                      ,(option< _, nt2::tag::id_>)
                      ,(id_<'ping'>)
                      );
}

////////////////////////////////////////////////////////////////////////////////
// Pass some allocator_ as option with a default
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( single_id_default )
{
  using nt2::id_;
  using boost::mpl::string;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE( (id_<'ping'>())
                      ,(option< void, nt2::tag::id_,_>)
                      ,(id_<'ping'>)
                      );
}

////////////////////////////////////////////////////////////////////////////////
// Pass some id_ as settings
////////////////////////////////////////////////////////////////////////////////
nt2::settings identity  (nt2::id_<'pong'>, nt2::id_<'ping'>);
NT2_TEST_CASE( single_id_settings )
{
  using nt2::id_;
  using boost::mpl::string;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE( identity
                      ,(option<_ , nt2::tag::id_>)
                      ,(id_<'ping'>)
                      );
}

//////////////////////////////////////////////////////////////////////////////////
//// Pass some id_ as settings with a default
//////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( id_settings )
{
  using nt2::id_;
  using boost::mpl::string;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE( (id_<'ping'>())
                      ,(option< settings(long, void*), nt2::tag::id_,_>)
                      ,(id_<'ping'>)
                      );
}
