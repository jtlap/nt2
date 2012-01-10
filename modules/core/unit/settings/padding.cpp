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

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

////////////////////////////////////////////////////////////////////////////////
// Pass some padding_ as an option and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
nt2::settings no_padd(nt2::no_padding_);

NT2_TEST_CASE( no_padding )
{
  using nt2::no_padding_;
  using nt2::lead_padding_strategy_;
  using nt2::global_padding_strategy_;
  using nt2::meta::option;
  using boost::mpl::_;
  using boost::mpl::int_;
  using nt2::settings;

  NT2_TEST_EXPR_TYPE( no_padding_()
                    , (option< _, nt2::tag::lead_padding_>)
                    , (lead_padding_strategy_<1>)
                    );

  NT2_TEST_EXPR_TYPE( no_padding_()
                    , (option< _, nt2::tag::global_padding_>)
                    , (global_padding_strategy_<1>)
                    );

  NT2_TEST_EXPR_TYPE( no_padd
                    , (option< _, nt2::tag::lead_padding_>)
                    , (lead_padding_strategy_<1>)
                    );

  NT2_TEST_EXPR_TYPE( no_padd
                    , (option< _, nt2::tag::global_padding_>)
                    , (global_padding_strategy_<1>)
                    );
}

nt2::global_padding_  global_32(nt2::with_<32>);
nt2::settings         global_set( nt2::global_padding_(nt2::with_<64>) );

NT2_TEST_CASE( lead_padding )
{
  using nt2::global_padding_;
  using nt2::global_padding_strategy_;
  using nt2::meta::option;
  using nt2::settings;
  using boost::mpl::_;
  using boost::mpl::int_;

  NT2_TEST_EXPR_TYPE( global_32
                      ,(option< _, nt2::tag::global_padding_>)
                      ,(global_padding_strategy_<32>)
                     );

  NT2_TEST_EXPR_TYPE( global_set
                      ,(option<_, nt2::tag::global_padding_>)
                      ,(global_padding_strategy_<64>)
                     );
}

nt2::lead_padding_  lead_32(nt2::with_<32>);
nt2::settings       lead_set( nt2::lead_padding_(nt2::with_<64>) );

NT2_TEST_CASE( global_padding )
{
  using nt2::lead_padding_;
  using nt2::lead_padding_strategy_;
  using nt2::meta::option;
  using nt2::settings;
  using boost::mpl::_;
  using boost::mpl::int_;

  NT2_TEST_EXPR_TYPE( lead_32
                      ,(option< _, nt2::tag::lead_padding_>)
                      ,(lead_padding_strategy_<32>)
                     );

  NT2_TEST_EXPR_TYPE( lead_set
                      ,(option<_, nt2::tag::lead_padding_>)
                      ,(lead_padding_strategy_<64>)
                     );
}
