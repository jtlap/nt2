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
#include <nt2/core/settings/padding_option.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

////////////////////////////////////////////////////////////////////////////////
// Pass some padding_ as an option and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( single_allocator )
{
   using boost::is_same;
   using nt2::padding_;
   using nt2::none_;
   using nt2::with_;
   using nt2::global_;
   using nt2::lead_;
   using nt2::no_padding_;
   using nt2::global_padding_;
   using nt2::lead_padding_;
   using nt2::meta::option;

  NT2_TEST( (is_same< no_padding_ 
             , option< padding_(none_)
                       , nt2::tag::padding_
                       >::type
             >::value) 
          );

  NT2_TEST( (is_same< global_padding_ 
             , option< padding_(global_)
                       , nt2::tag::padding_
                       >::type
             >::value) 
          );

  NT2_TEST( (is_same< global_padding_ 
             , option< padding_(global_, with_<32>)
                       , nt2::tag::padding_
                       >::type
             >::value) 
          );

  NT2_TEST( (is_same< lead_padding_ 
             , option< padding_(lead_)
                       , nt2::tag::padding_
                       >::type
             >::value) 
          );

  NT2_TEST( (is_same< lead_padding_ 
             , option< padding_(lead_, with_<32>)
                       , nt2::tag::padding_
                       >::type
             >::value) 
          );
}

////////////////////////////////////////////////////////////////////////////////
// Pass some padding_ as option with a default
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( single_padding_default )
{
   using boost::is_same;
   using nt2::padding_;
   using nt2::none_;
   using nt2::with_;
   using nt2::global_;
   using nt2::lead_;
   using nt2::no_padding_;
   using nt2::global_padding_;
   using nt2::lead_padding_;
   using nt2::meta::option;

  NT2_TEST( (is_same< no_padding_ 
             , option< void
                       , nt2::tag::padding_
                       , padding_(none_)
                       >::type
             >::value) 
          );

  NT2_TEST( (is_same< global_padding_ 
             , option< void
                       , nt2::tag::padding_
                       , padding_(global_)
                       >::type
             >::value) 
          );

  NT2_TEST( (is_same< global_padding_ 
             , option< void
                       , nt2::tag::padding_
             , padding_(global_, with_<16>)
                       >::type
             >::value) 
          );

  NT2_TEST( (is_same< lead_padding_ 
             , option< void
                       , nt2::tag::padding_
                       , padding_(lead_)
                       >::type
             >::value) 
          );

  NT2_TEST( (is_same< lead_padding_ 
             , option< void
                       , nt2::tag::padding_
             , padding_(lead_, with_<16>)
                       >::type
             >::value) 
          );
}

////////////////////////////////////////////////////////////////////////////////
// Pass some padding_ as settings
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( single_padding_settings )
{
   using boost::is_same;
   using nt2::padding_;
   using nt2::none_;
   using nt2::with_;
   using nt2::global_;
   using nt2::lead_;
   using nt2::no_padding_;
   using nt2::global_padding_;
   using nt2::lead_padding_;
   using nt2::meta::option;
   using nt2::settings;

  NT2_TEST( (is_same< no_padding_ 
             , option< settings (padding_(global_),
                                 padding_(none_)
                                 )
                       , nt2::tag::padding_
                       >::type
             >::value) 
          );

  NT2_TEST( (is_same< global_padding_ 
             , option< settings (padding_(none_),
                                 padding_(global_)
                                 )
                       , nt2::tag::padding_
                       >::type
             >::value) 
          );

  NT2_TEST( (is_same< global_padding_ 
             , option< settings (padding_(none_),
                                 padding_(global_, with_<5>)
                                 )
                       , nt2::tag::padding_
                       >::type
             >::value) 
          );

  NT2_TEST( (is_same< lead_padding_ 
             , option< settings (padding_(none_),
                                 padding_(lead_)
                                 )
                       , nt2::tag::padding_
                       >::type
             >::value) 
          );

  NT2_TEST( (is_same< lead_padding_ 
             , option< settings (padding_(none_),
                                 padding_(lead_, with_<5>)
                                 )
                       , nt2::tag::padding_
                       >::type
             >::value) 
          );

}

////////////////////////////////////////////////////////////////////////////////
// Pass some padding_ as settings with a default
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( single_padding_settings_default )
{

   using boost::is_same;
   using nt2::padding_;
   using nt2::none_;
   using nt2::with_;
   using nt2::global_;
   using nt2::lead_;
   using nt2::no_padding_;
   using nt2::global_padding_;
   using nt2::lead_padding_;
   using nt2::meta::option;
   using nt2::settings;

  NT2_TEST( (is_same< no_padding_ 
             , option< settings (double, long )
                       , nt2::tag::padding_
                       , padding_(none_)
                       >::type
             >::value) 
          );

  NT2_TEST( (is_same< global_padding_ 
             , option< settings (double, long )
                       , nt2::tag::padding_
                       , padding_(global_)
                       >::type
             >::value) 
          );

NT2_TEST( (is_same< global_padding_ 
             , option< settings (double, long )
                       , nt2::tag::padding_
           , padding_(global_,with_<5>)
                       >::type
             >::value) 
          );

  NT2_TEST( (is_same< lead_padding_ 
             , option< settings (double, long )
                       , nt2::tag::padding_
             , padding_(lead_, with_<6>)
                       >::type
             >::value) 
          );
  NT2_TEST( (is_same< lead_padding_ 
             , option< settings (double, long )
                       , nt2::tag::padding_
                       , padding_(lead_)
                       >::type
             >::value) 
          );
}
