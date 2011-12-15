/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::settings allocator_ is an option"

#include <boost/type_traits/is_same.hpp>
#include <nt2/core/settings/settings.hpp>
#include <nt2/core/settings/allocator.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

////////////////////////////////////////////////////////////////////////////////
// Pass some allocator_ as an option and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( single_allocator )
{
   using std::allocator;
   using boost::is_same;
   using nt2::allocator_;
   using nt2::meta::option;

  NT2_TEST( (is_same< allocator<float>
                    , option< allocator_< allocator<float> >
                            , nt2::tag::allocator_
                            >::type::type
                    >::value) 
          );

}

////////////////////////////////////////////////////////////////////////////////
// Pass some allocator_ as option with a default
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( single_allocator_default )
{
  using std::allocator;
  using boost::is_same;
  using nt2::allocator_;
  using nt2::meta::option;

  NT2_TEST( (is_same< allocator<int>
                    , option< void
                            , nt2::tag::allocator_
                            , allocator_< allocator<int> >
                            >::type::type
                    >::value) 
          );
}

////////////////////////////////////////////////////////////////////////////////
// Pass some allocator_ as settings
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( single_allocator_settings )
{
  using std::allocator;
  using boost::is_same;
  using nt2::allocator_;
  using nt2::settings;
  using nt2::meta::option;

  NT2_TEST( (is_same< allocator<int>
                    , option< settings( allocator_< allocator<float> >
                                      , allocator_< allocator<int> >
                                      )                      
                            , nt2::tag::allocator_
                            >::type::type 
                    >::value) 
          );
}

////////////////////////////////////////////////////////////////////////////////
// Pass some allocator_ as settings with a default
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( single_allocator_settings_default )
{
  using std::allocator;
  using boost::is_same;
  using nt2::allocator_;
  using nt2::settings;
  using nt2::meta::option;

  NT2_TEST( (is_same< allocator<int>
                    , option< settings( double, long )                      
                            , nt2::tag::allocator_
                            , allocator_< allocator<int> >
                            >::type::type 
                    >::value) 
          );
}
