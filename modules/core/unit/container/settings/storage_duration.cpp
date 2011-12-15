/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::settings storage_duration is an option"

#include <boost/type_traits/is_same.hpp>
#include <nt2/core/settings/settings.hpp>
#include <nt2/core/settings/storage_duration.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Pass some storage_duration_ as an option and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( single_storage_duration_ )
{
  using nt2::dynamic_;
  using nt2::automatic_;
  using boost::is_same;
  using nt2::meta::option;

  NT2_TEST( ( is_same < dynamic_
              , option< dynamic_, nt2::tag::storage_duration_ >::type 
                      >::value
            ) 
          );

  NT2_TEST( ( is_same < automatic_
              , option< automatic_, nt2::tag::storage_duration_ >::type 
                      >::value
            ) 
          );

}

////////////////////////////////////////////////////////////////////////////////
// Pass some storage_duration_ as default and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( single_storage_duration_default )
{
  using nt2::dynamic_;
  using nt2::automatic_;
  using boost::is_same;
  using nt2::meta::option;

  NT2_TEST( ( is_same < dynamic_
              , option< void, nt2::tag::storage_duration_, dynamic_ >::type 
                      >::value
            ) 
          );

  NT2_TEST( ( is_same < automatic_
              , option< void, nt2::tag::storage_duration_, automatic_ >::type 
              >::value
            ) 
          );

}

////////////////////////////////////////////////////////////////////////////////
// Pass some storage_duration_ as a setting and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( setting_storage_duration_ )
{
  using nt2::dynamic_;
  using nt2::automatic_;
  using nt2::settings;
  using boost::is_same;
  using nt2::meta::option;

  NT2_TEST( ( is_same < dynamic_
              , option< settings(automatic_, 
                                 dynamic_)
                              , nt2::tag::storage_duration_ 
                              >::type 
                      >::value
            ) 
          );


  NT2_TEST( ( is_same < automatic_
              , option< settings(dynamic_, 
                                 automatic_)
                              , nt2::tag::storage_duration_ 
                              >::type 
                      >::value
            ) 
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
  using boost::is_same;
  using nt2::meta::option;

  NT2_TEST( ( is_same < dynamic_
              , option< settings(long,int)
                        , nt2::tag::storage_duration_ 
                        , dynamic_
                        >::type 
              >::value
            ) 
          );

  NT2_TEST( ( is_same < automatic_
              , option< settings(long,int)
                        , nt2::tag::storage_duration_ 
                        , automatic_
                        >::type 
            >::value
            ) 
          );
}
