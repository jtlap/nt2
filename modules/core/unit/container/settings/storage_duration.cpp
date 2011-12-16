/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::settings storage_duration is an option"

#include <nt2/core/settings/settings.hpp>
#include <nt2/core/settings/storage_duration.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

////////////////////////////////////////////////////////////////////////////////
// Pass some storage_duration_ as an option and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( storage_duration_ )
{
  using nt2::dynamic_;
  using nt2::automatic_;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE( dynamic_()
                      ,(option< _, nt2::tag::storage_duration_>)
                      ,(dynamic_)
                      );

  NT2_TEST_EXPR_TYPE( automatic_()
                      ,(option< _, nt2::tag::storage_duration_>)
                      ,(automatic_)
                      );
}

////////////////////////////////////////////////////////////////////////////////
// Pass some storage_duration_ as default and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( storage_duration_default )
{
  using nt2::dynamic_;
  using nt2::automatic_;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE( dynamic_()
                      ,(option< void, nt2::tag::storage_duration_,_>)
                      ,(dynamic_)
                      );

  NT2_TEST_EXPR_TYPE( automatic_()
                      ,(option< void, nt2::tag::storage_duration_,_>)
                      ,(automatic_)
                      );
}

////////////////////////////////////////////////////////////////////////////////
// Pass some storage_duration_ as a setting and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
nt2::settings dyn   (nt2::automatic_, nt2::dynamic_);
nt2::settings autom (nt2::dynamic_  , nt2::automatic_);
NT2_TEST_CASE( setting_storage_duration_ )
{
  using nt2::dynamic_;
  using nt2::automatic_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;


  NT2_TEST_EXPR_TYPE( dyn
                      ,(option<_ , nt2::tag::storage_duration_>)
                      ,(dynamic_)
                      );

  NT2_TEST_EXPR_TYPE( autom
                      ,(option<_ , nt2::tag::storage_duration_>)
                      ,(automatic_)
                      );
}

////////////////////////////////////////////////////////////////////////////////
// Pass some storage_duration_ as a default setting and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( setting_storage_duration_default )
{
  using nt2::dynamic_;
  using nt2::automatic_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE( dynamic_()
                      ,(option< settings(long, int), nt2::tag::storage_duration_,_>)
                      ,(dynamic_)
                      );

  NT2_TEST_EXPR_TYPE( automatic_()
                      ,(option< settings(long, int), nt2::tag::storage_duration_,_>)
                      ,(automatic_)
                      );
}
