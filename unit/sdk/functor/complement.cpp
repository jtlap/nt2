/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::unary_plus"

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/functor/operators.hpp>
#include <boost/type_traits/is_same.hpp>

#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test behavior for complement
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL ( complement, NT2_INTEGRAL_TYPES )
{
  using boost::is_same;
  using nt2::tag::complement_;

  NT2_TEST( (boost::is_same < typename nt2::meta::call<complement_(T)>::type
                            , T
                            >::value
            )
          );

  T value  = 0;
  NT2_TEST_EQUAL( nt2::complement(value) , T(~value) );
  NT2_TEST_EQUAL( nt2::bitwise_not(value), T(~value) );
  NT2_TEST_EQUAL( nt2::b_not(value), T(~value) );
}

NT2_TEST_CASE ( complement_float )
{
  using boost::is_same;
  using nt2::tag::complement_;

  NT2_TEST( (boost::is_same < nt2::meta::call<complement_(float)>::type
                            , float
                            >::value
            )
          );

  NT2_TEST_EQUAL( nt2::complement(1.f) , -3.9999998f );
  NT2_TEST_EQUAL( nt2::bitwise_not(1.f), -3.9999998f );
  NT2_TEST_EQUAL( nt2::b_not(1.f)      , -3.9999998f );
}

NT2_TEST_CASE ( complement_double )
{
  using boost::is_same;
  using nt2::tag::complement_;

  NT2_TEST( (boost::is_same < nt2::meta::call<complement_(double)>::type
                            , double
                            >::value
            )
          );

  NT2_TEST_EQUAL( nt2::complement(1.) , -3.9999999999999996 );
  NT2_TEST_EQUAL( nt2::bitwise_not(1.), -3.9999999999999996 );
  NT2_TEST_EQUAL( nt2::b_not(1.)      , -3.9999999999999996 );
}



