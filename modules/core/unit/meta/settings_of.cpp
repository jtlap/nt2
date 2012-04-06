//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::meta::settings_of"

#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/meta/settings_of.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

//#include <nt2/core/settings/storage_order.hpp>
//#include <nt2/core/settings/alignment.hpp>

////////////////////////////////////////////////////////////////////////////////
// Check settings_of random non-container types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( value_settings_type )
{
  using nt2::_0D;
  using nt2::settings;
  using boost::is_same;
  using nt2::matlab_index_;
  using nt2::matlab_order_;
  using nt2::unaligned_;
  using nt2::meta::settings_of;

  NT2_TEST(( is_same< settings(matlab_index_, _0D, matlab_order_, unaligned_)
                    , settings_of<float>::type 
                    >::value 
          ));

  NT2_TEST(( is_same< settings(matlab_index_, _0D, matlab_order_, unaligned_)
                    , settings_of<float&>::type 
                    >::value 
          ));

  NT2_TEST(( is_same< settings(matlab_index_, _0D, matlab_order_, unaligned_)
                    , settings_of<float const>::type 
                    >::value 
          ));

  NT2_TEST(( is_same< settings(matlab_index_, _0D, matlab_order_, unaligned_)
                    , settings_of<float const&>::type 
                    >::value 
          ));
}

////////////////////////////////////////////////////////////////////////////////
// Check settings_of container type
////////////////////////////////////////////////////////////////////////////////
struct some_container
{
  typedef nt2::settings settings_type( nt2::C_index_, nt2::of_size_<1,3,3,7> );
};

NT2_TEST_CASE( container_settings_type )
{
  using nt2::settings;
  using nt2::C_index_;
  using nt2::of_size_;  
  using boost::is_same;
  using nt2::meta::settings_of;

  NT2_TEST(( is_same< settings(C_index_, of_size_<1,3,3,7>)
                    , settings_of<some_container>::type 
                    >::value 
          ));

  NT2_TEST(( is_same< settings(C_index_, of_size_<1,3,3,7>)
                    , settings_of<some_container&>::type 
                    >::value 
          ));

  NT2_TEST(( is_same< settings(C_index_, of_size_<1,3,3,7>)
                    , settings_of<some_container const>::type 
                    >::value 
          ));

  NT2_TEST(( is_same< settings(C_index_, of_size_<1,3,3,7>)
                    , settings_of<some_container const&>::type 
                    >::value 
          ));
}
