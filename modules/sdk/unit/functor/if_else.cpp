/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::if_else"

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/functor/operators.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/module.hpp>


////////////////////////////////////////////////////////////////////////////////
// Test behavior for comma
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL ( if_else, NT2_TYPES )
{
  using boost::is_same;
  using nt2::tag::if_else_;

  NT2_TEST( (boost::is_same < typename nt2::meta::call<if_else_(bool,T,T)>::type
                            , BOOST_TYPEOF(bool() ? T() : T())
                            >::value
            )
          );

  NT2_TEST_EQUAL( nt2::if_else(true,T(42),T(17)), T(42) );
  NT2_TEST_EQUAL( nt2::if_else(false,T(42),T(17)), T(17) );
  NT2_TEST_EQUAL( nt2::where(true,T(42),T(17)), T(42) );
  NT2_TEST_EQUAL( nt2::where(false,T(42),T(17)), T(17) );
}

