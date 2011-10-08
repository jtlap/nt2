//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 core - of_size test"

//==============================================================================
// Test behavior of nt2::of_size
//==============================================================================
#include <nt2/sdk/parameters.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/core/functions/of_size.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

NT2_TEST_CASE ( of_size_0d )
{
  using nt2::of_size;

  NT2_TEST( of_size().empty() );
  NT2_TEST_EQUAL( of_size().size()  , 0);
  NT2_TEST_EQUAL( of_size().size(1) , 1);
  NT2_TEST_EQUAL( of_size().size(2) , 1);
  NT2_TEST_EQUAL( of_size().lower(0), 1);
  NT2_TEST_EQUAL( of_size().upper(0), 1);
  NT2_TEST_EQUAL( of_size()(1)      , 1);
}

NT2_TEST_CASE( of_size )
{
  using nt2::of_size;

  #define M1(z,n,t) BOOST_PP_INC(n)
  #define M0(z,n,t)                                               \
  NT2_TEST( !of_size(BOOST_PP_ENUM(n,M1,~)).empty() );            \
  NT2_TEST_EQUAL( of_size(BOOST_PP_ENUM(n,M1,~)).size()  , n );   \
  NT2_TEST_EQUAL( of_size(BOOST_PP_ENUM(n,M1,~)).size(1) , 1 );   \
  NT2_TEST_EQUAL( of_size(BOOST_PP_ENUM(n,M1,~)).size(2) , n );   \
  NT2_TEST_EQUAL( of_size(BOOST_PP_ENUM(n,M1,~)).lower(1), 1 );   \
  NT2_TEST_EQUAL( of_size(BOOST_PP_ENUM(n,M1,~)).lower(2), 1 );   \
  NT2_TEST_EQUAL( of_size(BOOST_PP_ENUM(n,M1,~)).upper(1), 1 );   \
  NT2_TEST_EQUAL( of_size(BOOST_PP_ENUM(n,M1,~)).upper(2), n );   \
  for(std::size_t i= 1; i<= n;++i)                                \
    NT2_TEST_EQUAL( of_size(BOOST_PP_ENUM(n,M1,~))(i), i );       \
  for(std::size_t i= 3; i<= n;++i)                                \
  {                                                               \
    NT2_TEST_EQUAL( of_size(BOOST_PP_ENUM(n,M1,~)).size(i) , 1 ); \
    NT2_TEST_EQUAL( of_size(BOOST_PP_ENUM(n,M1,~)).lower(i), 1 ); \
    NT2_TEST_EQUAL( of_size(BOOST_PP_ENUM(n,M1,~)).upper(i), 1 ); \
  }                                                               \
  /**/

  BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(NT2_MAX_DIMENSIONS),M0,~)

  #undef M0
  #undef M1
}
