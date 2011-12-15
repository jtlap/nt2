/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::settings storage_scheme is an option"

#include <boost/type_traits/is_same.hpp>
#include <nt2/core/settings/settings.hpp>
#include <nt2/core/settings/storage_scheme.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Pass some storage_scheme_ as an option and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( single_storage_scheme_ )
{
  using nt2::conventional_;
  using nt2::packed_;
  using boost::is_same;
  using nt2::meta::option;


  NT2_TEST( ( is_same < conventional_
              , option< conventional_, nt2::tag::storage_scheme_ >::type 
                      >::value
            ) 
          );

  NT2_TEST( ( is_same < packed_
              , option< packed_, nt2::tag::storage_scheme_ >::type 
                      >::value
            ) 
          );

}

////////////////////////////////////////////////////////////////////////////////
// Pass some storage_scheme_ as default and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( single_storage_scheme_default )
{
  using nt2::conventional_;
  using nt2::packed_;
  using boost::is_same;
  using nt2::meta::option;

  NT2_TEST( ( is_same < conventional_
              , option< void, nt2::tag::storage_scheme_, conventional_ >::type 
            >::value
            ) 
          );

  NT2_TEST( ( is_same < packed_
              , option< void, nt2::tag::storage_scheme_, packed_ >::type 
            >::value
            ) 
          );
}

////////////////////////////////////////////////////////////////////////////////
// Pass some storage_scheme_ as a setting and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( setting_storage_scheme_ )
{
  using nt2::conventional_;
  using nt2::packed_;
  using nt2::settings;
  using boost::is_same;
  using nt2::meta::option;

  NT2_TEST( ( is_same < conventional_
              , option< settings(packed_,
                                 conventional_)
              , nt2::tag::storage_scheme_ 
              >::type 
              >::value
            ) 
          );

  NT2_TEST( ( is_same < packed_
              , option< settings(conventional_,
                                 packed_
                                 )
              , nt2::tag::storage_scheme_ 
              >::type 
              >::value
            ) 
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
  using boost::is_same;
  using nt2::meta::option;

  NT2_TEST( ( is_same < conventional_
                      , option< settings(long,int)
                              , nt2::tag::storage_scheme_ 
                              , conventional_
                              >::type 
                      >::value
            ) 
          );

  NT2_TEST( ( is_same < packed_
                      , option< settings(long,int)
                              , nt2::tag::storage_scheme_ 
                              , packed_
                              >::type 
                      >::value
            ) 
          );
}
