/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::functors::belong_to"

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/functor/operators.hpp>
#include <boost/type_traits/is_same.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test behavior for unary plus
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL ( unary_plus, (double)(nt2::uint64_t)(nt2::int64_t)
                          (float)(nt2::uint32_t)(nt2::int32_t)
                          (nt2::uint16_t)(nt2::int16_t)         
                          (nt2::uint8_t)(nt2::int8_t)
                  )
{
  using boost::is_same;
  using nt2::functors::unary_plus_;

  NT2_TEST( (boost::is_same < typename nt2::meta::call<unary_plus_(T)>::type
                            , typename std::tr1::result_of<nt2::meta::arithmetic(T)>::type
                            >::value
            )
          );

  T value  = 42;
  NT2_TEST_EQUAL( nt2::unary_plus(value), value );
  NT2_TEST_EQUAL( nt2::identity(value)  , value );
  NT2_TEST_EQUAL( nt2::id(value)        , value );
}

////////////////////////////////////////////////////////////////////////////////
// Test behavior for complement
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL ( complement, (nt2::uint64_t)(nt2::int64_t)
                                (nt2::uint32_t)(nt2::int32_t)
                                (nt2::uint16_t)(nt2::int16_t)         
                                (nt2::uint8_t)(nt2::int8_t)
                  )
{
  using boost::is_same;
  using nt2::functors::complement_;

  NT2_TEST( (boost::is_same < typename nt2::meta::call<complement_(T)>::type
                            , typename std::tr1::result_of<nt2::meta::arithmetic(T)>::type
                            >::value
            )
          );

  T value  = 42;
  NT2_TEST_EQUAL( nt2::complement(value) , ~value );
  NT2_TEST_EQUAL( nt2::bitwise_not(value), ~value );
}


/*
  NT2_FUNCTION_IMPLEMENTATION(functors::complement_ , b_not       , 1 )
  NT2_FUNCTION_IMPLEMENTATION(functors::logical_not_, logical_not , 1 )
  NT2_FUNCTION_IMPLEMENTATION(functors::logical_not_, l_not       , 1 )
  NT2_FUNCTION_IMPLEMENTATION(functors::neg_        , neg         , 1 )
*/

////////////////////////////////////////////////////////////////////////////////
// Test behavior for plus
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL ( plus, (double)(nt2::uint64_t)(nt2::int64_t)
                          (float)(nt2::uint32_t)(nt2::int32_t)
                          (nt2::uint16_t)(nt2::int16_t)         
                          (nt2::uint8_t)(nt2::int8_t)
                  )
{
  using boost::is_same;
  using nt2::functors::plus_;

  NT2_TEST( (boost::is_same < typename nt2::meta::call<plus_(T,T)>::type
                            , typename std::tr1::result_of<nt2::meta::arithmetic(T,T)>::type
                            >::value
            )
          );

  T value  = 42;
  NT2_TEST_EQUAL( nt2::plus(value ,value ), value+value );
  NT2_TEST_EQUAL( nt2::add(value ,value ) , value+value );
}

////////////////////////////////////////////////////////////////////////////////
// Test behavior for minus
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL ( minus,  (double)(nt2::uint64_t)(nt2::int64_t)
                            (float)(nt2::uint32_t)(nt2::int32_t)
                            (nt2::uint16_t)(nt2::int16_t)         
                            (nt2::uint8_t)(nt2::int8_t)
                  )
{
  using boost::is_same;
  using nt2::functors::minus_;

  NT2_TEST( (boost::is_same < typename nt2::meta::call<minus_(T,T)>::type
                            , typename std::tr1::result_of<nt2::meta::arithmetic(T,T)>::type
                            >::value
            )
          );

  T value  = 42;
  NT2_TEST_EQUAL( nt2::minus(value ,value ), value-value );
  NT2_TEST_EQUAL( nt2::sub(value ,value ), value-value );
}

////////////////////////////////////////////////////////////////////////////////
// Test behavior for multiplies
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL ( mul,  (double)(nt2::uint64_t)(nt2::int64_t)
                          (float)(nt2::uint32_t)(nt2::int32_t)
                          (nt2::uint16_t)(nt2::int16_t)         
                          (nt2::uint8_t)(nt2::int8_t)
                  )
{
  using boost::is_same;
  using nt2::functors::multiplies_;

  NT2_TEST( (boost::is_same < typename nt2::meta::call<multiplies_(T,T)>::type
                            , typename std::tr1::result_of<nt2::meta::arithmetic(T,T)>::type
                            >::value
            )
          );

  T value  = 4;
  NT2_TEST_EQUAL( nt2::mul(value ,value ), value*value );
  NT2_TEST_EQUAL( nt2::multiplies(value ,value ), value*value );
}


////////////////////////////////////////////////////////////////////////////////
// Test behavior for divides
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL ( div,  (double)(nt2::uint64_t)(nt2::int64_t)
                          (float)(nt2::uint32_t)(nt2::int32_t)
                          (nt2::uint16_t)(nt2::int16_t)         
                          (nt2::uint8_t)(nt2::int8_t)
                  )
{
  using boost::is_same;
  using nt2::functors::divides_;

  NT2_TEST( (boost::is_same < typename nt2::meta::call<divides_(T,T)>::type
                            , typename std::tr1::result_of<nt2::meta::arithmetic(T,T)>::type
                            >::value
            )
          );

  T value  = 4;
  NT2_TEST_EQUAL( nt2::div(value ,value ), value/value );
  NT2_TEST_EQUAL( nt2::rdiv(value ,value ), value/value );
  NT2_TEST_EQUAL( nt2::divides(value ,value ), value/value );
}


/*
  NT2_FUNCTION_IMPLEMENTATION(functors::modulo_           , modulo          , 2 )
  NT2_FUNCTION_IMPLEMENTATION(functors::bitwise_xor_      , bitwise_xor     , 2 )
  NT2_FUNCTION_IMPLEMENTATION(functors::bitwise_xor_      , b_xor           , 2 )
  NT2_FUNCTION_IMPLEMENTATION(functors::bitwise_or_       , bitwise_or      , 2 )
  NT2_FUNCTION_IMPLEMENTATION(functors::bitwise_or_       , b_or            , 2 )
  NT2_FUNCTION_IMPLEMENTATION(functors::bitwise_and_      , bitwise_and     , 2 )
  NT2_FUNCTION_IMPLEMENTATION(functors::bitwise_and_      , b_and           , 2 )
  NT2_FUNCTION_IMPLEMENTATION(functors::is_equal_         , is_equal        , 2 )
  NT2_FUNCTION_IMPLEMENTATION(functors::is_equal_         , eq              , 2 )
  NT2_FUNCTION_IMPLEMENTATION(functors::is_not_equal_     , is_not_equal    , 2 )
  NT2_FUNCTION_IMPLEMENTATION(functors::is_not_equal_     , neq             , 2 )
  NT2_FUNCTION_IMPLEMENTATION(functors::is_less_          , is_less         , 2 )
  NT2_FUNCTION_IMPLEMENTATION(functors::is_less_          , lt              , 2 )
  NT2_FUNCTION_IMPLEMENTATION(functors::is_greater_       , is_greater      , 2 )
  NT2_FUNCTION_IMPLEMENTATION(functors::is_greater_       , gt              , 2 )
  NT2_FUNCTION_IMPLEMENTATION(functors::is_less_equal_    , is_less_equal   , 2 )
  NT2_FUNCTION_IMPLEMENTATION(functors::is_less_equal_    , le              , 2 )
  NT2_FUNCTION_IMPLEMENTATION(functors::is_greater_equal_ , is_greater_equal, 2 )
  NT2_FUNCTION_IMPLEMENTATION(functors::is_greater_equal_ , ge              , 2 )
  NT2_FUNCTION_IMPLEMENTATION(functors::logical_or_       , logical_or      , 2 )
  NT2_FUNCTION_IMPLEMENTATION(functors::logical_or_       , l_or            , 2 )
  NT2_FUNCTION_IMPLEMENTATION(functors::logical_and_      , logical_and     , 2 )
  NT2_FUNCTION_IMPLEMENTATION(functors::logical_and_      , l_and           , 2 )
  NT2_FUNCTION_IMPLEMENTATION(functors::shift_right_      , shift_right     , 2 )
  NT2_FUNCTION_IMPLEMENTATION(functors::shift_right_      , shr             , 2 )
  NT2_FUNCTION_IMPLEMENTATION(functors::shift_left_       , shift_left      , 2 )
  NT2_FUNCTION_IMPLEMENTATION(functors::shift_left_       , shl             , 2 )

  NT2_FUNCTION_IMPLEMENTATION(functors::if_else_  , if_else , 3 )
  NT2_FUNCTION_IMPLEMENTATION(functors::if_else_  , where   , 3 )
*/
