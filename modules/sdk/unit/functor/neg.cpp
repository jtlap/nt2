/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::neg"

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/functor/operators.hpp>
#include <boost/type_traits/is_same.hpp>

#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/module.hpp>

#ifdef BOOST_MSVC
  #pragma warning(disable: 4146) // unary minus applied to unsigned
#endif

////////////////////////////////////////////////////////////////////////////////
// Test behavior for complement
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL ( signed_neg, NT2_SIGNED_TYPES )
{
  using boost::is_same;
  using nt2::tag::unary_minus_;

  NT2_TEST( (boost::is_same < typename nt2::meta::call<unary_minus_(T)>::type
                            , BOOST_TYPEOF_TPL(-T())
                            >::value
            )
          );

  NT2_TEST_EQUAL( nt2::neg(T(0))    , T(0)     );
  NT2_TEST_EQUAL( nt2::neg(T(-42))  , T(42)    );
  NT2_TEST_EQUAL( nt2::neg(T(1337)) , T(-1337) );
}

NT2_TEST_CASE_TPL ( unsigned_neg, NT2_UNSIGNED_TYPES )
{
  using boost::is_same;
  using nt2::tag::unary_minus_;

  NT2_TEST( (boost::is_same < typename nt2::meta::call<unary_minus_(T)>::type
                            , BOOST_TYPEOF_TPL(-T())
                            >::value
            )
          );

  NT2_TEST_EQUAL( nt2::neg(T(0))  , 0   );
  NT2_TEST_EQUAL( nt2::neg(T(42)) , -42 );
}

