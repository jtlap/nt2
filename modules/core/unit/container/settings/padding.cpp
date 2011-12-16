/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::settings padding_ is an option"

#include <boost/type_traits/is_same.hpp>
#include <nt2/core/settings/settings.hpp>
#include <nt2/core/settings/padding.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

////////////////////////////////////////////////////////////////////////////////
// Pass some padding_ as an option and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( no_padding )
{
   using nt2::none_;
   using nt2::no_padding_;
   using nt2::padding_;
   using nt2::lead_;
   using nt2::padding_strategy_;
   using nt2::meta::option;
   using boost::mpl::_;
   using boost::mpl::int_;
   using nt2::settings;

  NT2_TEST_EXPR_TYPE( no_padding_()
                     ,(option< _, nt2::tag::padding_>)
                     ,(padding_strategy_<none_, int_<-1> >)
                     );

  //Pass some padding_ as option with a default
  NT2_TEST_EXPR_TYPE( no_padding_()
                      ,(option< void, nt2::tag::padding_,_>)
                     ,(padding_strategy_<none_, int_<-1> >)
                     );

  //Pass some padding_ as settings
  nt2::settings no_padd(padding_(lead_),padding_(none_));

  NT2_TEST_EXPR_TYPE( no_padd
                      ,(option<_, nt2::tag::padding_>)
                     ,(padding_strategy_<none_, int_<-1> >)
                     );

  // Pass some padding_ as settings with a default
  NT2_TEST_EXPR_TYPE( no_padding_()
                      ,(option<settings(double,float), nt2::tag::padding_,_>)
                     ,(padding_strategy_<none_, int_<-1> >)
                     );


}


NT2_TEST_CASE( global_padding )
{
   using nt2::global_;
   using nt2::global_padding_;
   using nt2::padding_;
   using nt2::padding_strategy_;
   using nt2::meta::option;
   using nt2::settings;
   using boost::mpl::_;
   using boost::mpl::int_;

  NT2_TEST_EXPR_TYPE( global_padding_()
                     ,(option< _, nt2::tag::padding_>)
                     ,(padding_strategy_<global_, int_<-1> >)
                     );

  nt2::padding_ global_32(global_, nt2::with_<32>);
  nt2::padding_ global_32_permute(nt2::with_<32>, global_);

  NT2_TEST_EXPR_TYPE( global_32
                     ,(option< _, nt2::tag::padding_>)
                     ,(padding_strategy_<global_, int_<32> >)
                     );

  NT2_TEST_EXPR_TYPE( global_32_permute
                     ,(option< _, nt2::tag::padding_>)
                     ,(padding_strategy_<global_, int_<32> >)
                     );

  //Pass some padding_ as option with a default
  NT2_TEST_EXPR_TYPE( global_32
                      ,(option< void, nt2::tag::padding_,_>)
                     ,(padding_strategy_<global_, int_<32> >)
                     );

  NT2_TEST_EXPR_TYPE( global_32_permute
                      ,(option< void, nt2::tag::padding_,_>)
                     ,(padding_strategy_<global_, int_<32> >)
                     );

  //Pass some padding_ as settings
  nt2::settings global_padd_sett_32(padding_(none_)
                                    ,padding_(global_,nt2::with_<32>)
                                    );
  nt2::settings global_padd_sett_32_permute(padding_(none_)
                                           ,padding_(global_,nt2::with_<32>)
                                           );
  NT2_TEST_EXPR_TYPE( global_padd_sett_32
                      ,(option<_, nt2::tag::padding_>)
                     ,(padding_strategy_<global_, int_<32> >)
                     );
  NT2_TEST_EXPR_TYPE( global_padd_sett_32_permute
                      ,(option<_, nt2::tag::padding_>)
                     ,(padding_strategy_<global_, int_<32> >)
                     );

  // Pass some padding_ as settings with a default
  NT2_TEST_EXPR_TYPE( global_32
                      ,(option< settings(double, float), nt2::tag::padding_,_>)
                     ,(padding_strategy_<global_, int_<32> >)
                     );

  NT2_TEST_EXPR_TYPE( global_32_permute
                      ,(option< settings(double, float), nt2::tag::padding_,_>)
                     ,(padding_strategy_<global_, int_<32> >)
                     );

}


NT2_TEST_CASE( lead_padding )
{
   using nt2::padding_;
   using nt2::lead_padding_;
   using nt2::lead_;
   using nt2::none_;
   using nt2::padding_strategy_;
   using nt2::meta::option;
   using nt2::settings;
   using boost::mpl::_;
   using boost::mpl::int_;

  NT2_TEST_EXPR_TYPE( lead_padding_()
                     ,(option< _, nt2::tag::padding_>)
                     ,(padding_strategy_<lead_, int_<-1> >)
                     );

  nt2::padding_ lead_32(lead_, nt2::with_<32>);
  nt2::padding_ lead_32_permute(nt2::with_<32>, lead_);

  NT2_TEST_EXPR_TYPE( lead_32
                     ,(option< _, nt2::tag::padding_>)
                     ,(padding_strategy_<lead_, int_<32> >)
                     );

  NT2_TEST_EXPR_TYPE( lead_32_permute
                     ,(option< _, nt2::tag::padding_>)
                     ,(padding_strategy_<lead_, int_<32> >)
                     );

  //Pass some padding_ as option with a default
  NT2_TEST_EXPR_TYPE( lead_32
                      ,(option< void, nt2::tag::padding_,_>)
                     ,(padding_strategy_<lead_, int_<32> >)
                     );

  NT2_TEST_EXPR_TYPE( lead_32_permute
                      ,(option< void, nt2::tag::padding_,_>)
                     ,(padding_strategy_<lead_, int_<32> >)
                     );

  //Pass some padding_ as settings
  nt2::settings lead_padd_sett_32( padding_(none_)
                                  ,padding_(lead_,nt2::with_<32>)
                                   );
  nt2::settings lead_padd_sett_32_permute( padding_(none_)
                                          ,padding_(lead_,nt2::with_<32>)
                                           );
  NT2_TEST_EXPR_TYPE( lead_padd_sett_32
                      ,(option<_, nt2::tag::padding_>)
                     ,(padding_strategy_<lead_, int_<32> >)
                     );

  NT2_TEST_EXPR_TYPE( lead_padd_sett_32_permute
                      ,(option<_, nt2::tag::padding_>)
                     ,(padding_strategy_<lead_, int_<32> >)
                     );

  // Pass some padding_ as settings with a default
  NT2_TEST_EXPR_TYPE( lead_32
                      ,(option< settings(double, float), nt2::tag::padding_,_>)
                      ,(padding_strategy_<lead_, int_<32> >)
                     );

  NT2_TEST_EXPR_TYPE( lead_32_permute
                      ,(option< settings(double, float), nt2::tag::padding_,_>)
                      ,(padding_strategy_<lead_, int_<32> >)
                     );
}
