/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::settings storage_scheme is an option"

#include <nt2/core/settings/settings.hpp>
#include <nt2/core/settings/storage_scheme.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

////////////////////////////////////////////////////////////////////////////////
// Pass some storage_scheme_ as an option and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( storage_scheme_ )
{
  using nt2::conventional_;
  using nt2::packed_;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE( conventional_()
                      ,(option< _, nt2::tag::storage_scheme_>)
                      ,(conventional_)
                      );

  NT2_TEST_EXPR_TYPE( packed_()
                      ,(option< _, nt2::tag::storage_scheme_>)
                      ,(packed_)
                      );
}

////////////////////////////////////////////////////////////////////////////////
// Pass some storage_scheme_ as default and check everything go out properly
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( storage_scheme_default )
{
  using nt2::conventional_;
  using nt2::packed_;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE( conventional_()
                      ,(option< void, nt2::tag::storage_scheme_,_>)
                      ,(conventional_)
                      );

  NT2_TEST_EXPR_TYPE( packed_()
                      ,(option< void, nt2::tag::storage_scheme_,_>)
                      ,(packed_)
                      );
}

////////////////////////////////////////////////////////////////////////////////
// Pass some storage_scheme_ as a setting and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
nt2::settings conv (nt2::packed_      , nt2::conventional_)
{
  return nt2::settings();
}

nt2::settings pack (nt2::conventional_, nt2::packed_ )
{
  return nt2::settings();
}

NT2_TEST_CASE( setting_storage_scheme_ )
{
  using nt2::conventional_;
  using nt2::packed_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;


  NT2_TEST_EXPR_TYPE( conv
                      ,(option<_ , nt2::tag::storage_scheme_>)
                      ,(conventional_)
                      );

  NT2_TEST_EXPR_TYPE( pack
                      ,(option<_ , nt2::tag::storage_scheme_>)
                      ,(packed_)
                      );
}

////////////////////////////////////////////////////////////////////////////////
// Pass some storage_scheme_ as a default setting and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( setting_storage_scheme_default )
{
  using nt2::conventional_;
  using nt2::packed_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE( conventional_()
                      ,(option< settings(long,int), nt2::tag::storage_scheme_,_>)
                      ,(conventional_)
                      );

  NT2_TEST_EXPR_TYPE( packed_()
                      ,(option< settings(long,int), nt2::tag::storage_scheme_,_>)
                      ,(packed_)
                      );
}
