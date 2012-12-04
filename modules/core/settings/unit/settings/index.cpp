//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::settings index_ is an option"

#include <boost/mpl/at.hpp>
#include <boost/mpl/size.hpp>
#include <nt2/core/settings/settings.hpp>
#include <nt2/core/settings/index.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Pass some index_ as an option and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( single_index )
{
  using nt2::index_;
  using nt2::meta::option;

  typedef option<nt2::index_<3,2,4>, nt2::tag::index_>::type::type index_option;
  NT2_TEST_EQUAL( boost::mpl::size<index_option>::value, NT2_MAX_DIMENSIONS );
  NT2_TEST_EQUAL( (boost::mpl::at_c<index_option,0>::type::value), 3 );
  NT2_TEST_EQUAL( (boost::mpl::at_c<index_option,1>::type::value), 2 );
  NT2_TEST_EQUAL( (boost::mpl::at_c<index_option,2>::type::value), 4 );
}

////////////////////////////////////////////////////////////////////////////////
// Pass some allocator_ as option with a default
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( single_index_default )
{
  using nt2::index_;
  using nt2::meta::option;

  typedef index_<3,2,5,4> default_;

  typedef option< void, nt2::tag::index_, default_>::type::type index_option;
  NT2_TEST_EQUAL( boost::mpl::size<index_option>::value, NT2_MAX_DIMENSIONS );
  NT2_TEST_EQUAL( (boost::mpl::at_c<index_option,0>::type::value), 3 );
  NT2_TEST_EQUAL( (boost::mpl::at_c<index_option,1>::type::value), 2 );
  NT2_TEST_EQUAL( (boost::mpl::at_c<index_option,2>::type::value), 5 );
  NT2_TEST_EQUAL( (boost::mpl::at_c<index_option,3>::type::value), 4 );
}


////////////////////////////////////////////////////////////////////////////////
// Pass some id_ as settings
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( single_index_settings )
{
  using nt2::index_;
  using nt2::C_index_;
  using nt2::settings;
  using nt2::meta::option;

  typedef option< settings(C_index_), nt2::tag::index_>::type::type index_option;

  NT2_TEST_EQUAL( boost::mpl::size<index_option>::value, NT2_MAX_DIMENSIONS );
  NT2_TEST_EQUAL( (boost::mpl::at_c<index_option,0>::type::value), 0 );
  NT2_TEST_EQUAL( (boost::mpl::at_c<index_option,1>::type::value), 0 );
  NT2_TEST_EQUAL( (boost::mpl::at_c<index_option,2>::type::value), 0 );
  NT2_TEST_EQUAL( (boost::mpl::at_c<index_option,3>::type::value), 0 );
}

////////////////////////////////////////////////////////////////////////////////
// Pass some id_ as settings with a default
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( single_id_settings_default )
{
  using nt2::index_;
  using nt2::settings;
  using nt2::meta::option;

  typedef settings default_(index_<3,2,5,4>);

  typedef option< settings(long,short)
                , nt2::tag::index_
                , default_>::type::type   index_option;

  NT2_TEST_EQUAL( boost::mpl::size<index_option>::value, NT2_MAX_DIMENSIONS );
  NT2_TEST_EQUAL( (boost::mpl::at_c<index_option,0>::type::value), 3 );
  NT2_TEST_EQUAL( (boost::mpl::at_c<index_option,1>::type::value), 2 );
  NT2_TEST_EQUAL( (boost::mpl::at_c<index_option,2>::type::value), 5 );
  NT2_TEST_EQUAL( (boost::mpl::at_c<index_option,3>::type::value), 4 );
}
