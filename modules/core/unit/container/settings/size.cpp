/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::settings size is an option"

#include <boost/type_traits/is_same.hpp>
#include <nt2/core/settings/settings.hpp>
#include <nt2/core/settings/size.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Pass some of_size_ as an option and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( single_of_size_ )
{
  using nt2::_2D;
  using nt2::of_size_;
  using boost::is_same;
  using nt2::meta::option;

  NT2_TEST( ( is_same < _2D
                      , option< _2D, nt2::tag::size_ >::type 
                      >::value
            ) 
          );

  NT2_TEST( ( is_same < of_size_<3,4>
                      , option< of_size_<3,4>, nt2::tag::size_ >::type 
                      >::value
            ) 
          );
}

////////////////////////////////////////////////////////////////////////////////
// Pass some of_size_ as default and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( single_of_size_default )
{
  using nt2::_2D;
  using nt2::of_size_;
  using boost::is_same;
  using nt2::meta::option;

  NT2_TEST( ( is_same < _2D
                      , option< void, nt2::tag::size_, _2D >::type 
                      >::value
            ) 
          );

  NT2_TEST( ( is_same < of_size_<3,4>
                      , option< void, nt2::tag::size_,of_size_<3,4> >::type 
                      >::value
            ) 
          );
}

////////////////////////////////////////////////////////////////////////////////
// Pass some of_size_ as a setting and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( setting_of_size_ )
{
  using nt2::_2D;
  using nt2::of_size_;
  using nt2::settings;
  using boost::is_same;
  using nt2::meta::option;

  NT2_TEST( ( is_same < _2D
                      , option< settings(of_size_<3,4>,_2D)
                              , nt2::tag::size_ 
                              >::type 
                      >::value
            ) 
          );

  NT2_TEST( ( is_same < of_size_<3,4>
                      , option< settings(_2D, of_size_<3,4>)
                              , nt2::tag::size_ 
                              >::type 
                      >::value
            ) 
          );
}

////////////////////////////////////////////////////////////////////////////////
// Pass some of_size_ as a default setting and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( setting_of_size_default )
{
  using nt2::_2D;
  using nt2::of_size_;
  using nt2::settings;
  using boost::is_same;
  using nt2::meta::option;

  NT2_TEST( ( is_same < _2D
                      , option< settings(long,int)
                              , nt2::tag::size_ 
                              , _2D
                              >::type 
                      >::value
            ) 
          );

  NT2_TEST( ( is_same < of_size_<3,4>
                      , option< settings(int, double)
                              , nt2::tag::size_ 
                              , of_size_<3,4>
                              >::type 
                      >::value
            ) 
          );
}
