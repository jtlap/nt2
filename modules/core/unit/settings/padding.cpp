//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::settings padding_ is an option"

#include <nt2/core/settings/settings.hpp>
#include <nt2/core/settings/padding.hpp>
#include <nt2/sdk/memory/cache_padding.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

////////////////////////////////////////////////////////////////////////////////
// Pass some padding_ as an option and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
nt2::settings no_pad(nt2::no_padding_);

NT2_TEST_CASE( no_padding_strategy )
{
  using boost::mpl::_;
  using nt2::padding_;
  using nt2::settings;
  using nt2::no_padding_;
  using nt2::meta::option;

  NT2_TEST_EXPR_TYPE( no_padding_()
                    , (option< _, nt2::tag::padding_>)
                    , (nt2::padding_<nt2::memory::no_padding>)
                    );

  NT2_TEST_EXPR_TYPE( no_pad
                    , (option< _, nt2::tag::padding_>)
                    , (nt2::padding_<nt2::memory::no_padding>)
                    );
}

nt2::settings none( nt2::padding_<nt2::memory::no_padding> );
nt2::settings cache( nt2::padding_<nt2::memory::cache_padding> );

NT2_TEST_CASE( padding_strategy )
{
  using boost::mpl::_;
  using nt2::padding_;
  using nt2::no_padding_;
  using nt2::settings;
  using nt2::meta::option;

  NT2_TEST_EXPR_TYPE ( nt2::padding_<nt2::memory::no_padding>()
                     , (option< _, nt2::tag::padding_>)
                     , (nt2::padding_<nt2::memory::no_padding>)
                     );

  NT2_TEST_EXPR_TYPE ( none
                     , (option< _, nt2::tag::padding_>)
                     , (nt2::padding_<nt2::memory::no_padding>)
                     );

  NT2_TEST_EXPR_TYPE( nt2::padding_<nt2::memory::cache_padding>()
                      ,(option<_, nt2::tag::padding_>)
                      ,(nt2::padding_<nt2::memory::cache_padding>)
                     );

  NT2_TEST_EXPR_TYPE( cache
                      ,(option<_, nt2::tag::padding_>)
                      ,(nt2::padding_<nt2::memory::cache_padding>)
                     );
}
