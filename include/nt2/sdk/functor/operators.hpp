/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_FUNCTOR_OPERATORS_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_OPERATORS_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Generate boilerplate function for mapping natural operators
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/functor/functor.hpp>
#include <nt2/sdk/functor/details/tags.hpp>
#include <nt2/sdk/functor/details/comma.hpp>
#include <nt2/sdk/functor/details/shifts.hpp>
#include <nt2/sdk/functor/details/boolean.hpp>
#include <nt2/sdk/functor/details/bitwise.hpp>
#include <nt2/sdk/functor/details/complement.hpp>
#include <nt2/sdk/functor/details/terminal.hpp>
#include <nt2/sdk/functor/details/arithmetic.hpp>
#include <nt2/sdk/functor/preprocessor/function.hpp>

namespace nt2
{
  //////////////////////////////////////////////////////////////////////////////
  // Unary function wrappers
  //////////////////////////////////////////////////////////////////////////////
  NT2_FUNCTION_IMPLEMENTATION(tag::unary_plus_ , unary_plus  , 1 )
  NT2_FUNCTION_IMPLEMENTATION(tag::unary_plus_ , identity    , 1 )
  NT2_FUNCTION_IMPLEMENTATION(tag::unary_plus_ , id          , 1 )
  NT2_FUNCTION_IMPLEMENTATION(tag::complement_ , complement  , 1 )
  NT2_FUNCTION_IMPLEMENTATION(tag::complement_ , bitwise_not , 1 )
  NT2_FUNCTION_IMPLEMENTATION(tag::complement_ , b_not       , 1 )
  NT2_FUNCTION_IMPLEMENTATION(tag::logical_not_, logical_not , 1 )
  NT2_FUNCTION_IMPLEMENTATION(tag::logical_not_, l_not       , 1 )
  NT2_FUNCTION_IMPLEMENTATION(tag::unary_minus_, unary_minus , 1 )
  NT2_FUNCTION_IMPLEMENTATION(tag::unary_minus_, neg         , 1 )

  //////////////////////////////////////////////////////////////////////////////
  // Binary function wrappers
  //////////////////////////////////////////////////////////////////////////////
  NT2_FUNCTION_IMPLEMENTATION(tag::plus_             , plus            , 2 )
  NT2_FUNCTION_IMPLEMENTATION(tag::plus_             , add             , 2 )
  NT2_FUNCTION_IMPLEMENTATION(tag::minus_            , minus           , 2 )
  NT2_FUNCTION_IMPLEMENTATION(tag::minus_            , sub             , 2 )
  NT2_FUNCTION_IMPLEMENTATION(tag::multiplies_       , multiplies      , 2 )
  NT2_FUNCTION_IMPLEMENTATION(tag::multiplies_       , mul             , 2 )
  NT2_FUNCTION_IMPLEMENTATION(tag::divides_          , divides         , 2 )
  NT2_FUNCTION_IMPLEMENTATION(tag::divides_          , rdiv            , 2 )
  NT2_FUNCTION_IMPLEMENTATION(tag::divides_          , div             , 2 )
  NT2_FUNCTION_IMPLEMENTATION(tag::modulo_           , modulo          , 2 )
  NT2_FUNCTION_IMPLEMENTATION(tag::bitwise_xor_      , bitwise_xor     , 2 )
  NT2_FUNCTION_IMPLEMENTATION(tag::bitwise_xor_      , b_xor           , 2 )
  NT2_FUNCTION_IMPLEMENTATION(tag::bitwise_or_       , bitwise_or      , 2 )
  NT2_FUNCTION_IMPLEMENTATION(tag::bitwise_or_       , b_or            , 2 )
  NT2_FUNCTION_IMPLEMENTATION(tag::bitwise_and_      , bitwise_and     , 2 )
  NT2_FUNCTION_IMPLEMENTATION(tag::bitwise_and_      , b_and           , 2 )
  NT2_FUNCTION_IMPLEMENTATION(tag::is_equal_         , is_equal        , 2 )
  NT2_FUNCTION_IMPLEMENTATION(tag::is_equal_         , eq              , 2 )
  NT2_FUNCTION_IMPLEMENTATION(tag::is_not_equal_     , is_not_equal    , 2 )
  NT2_FUNCTION_IMPLEMENTATION(tag::is_not_equal_     , neq             , 2 )
  NT2_FUNCTION_IMPLEMENTATION(tag::is_less_          , is_less         , 2 )
  NT2_FUNCTION_IMPLEMENTATION(tag::is_less_          , lt              , 2 )
  NT2_FUNCTION_IMPLEMENTATION(tag::is_greater_       , is_greater      , 2 )
  NT2_FUNCTION_IMPLEMENTATION(tag::is_greater_       , gt              , 2 )
  NT2_FUNCTION_IMPLEMENTATION(tag::is_less_equal_    , is_less_equal   , 2 )
  NT2_FUNCTION_IMPLEMENTATION(tag::is_less_equal_    , le              , 2 )
  NT2_FUNCTION_IMPLEMENTATION(tag::is_greater_equal_ , is_greater_equal, 2 )
  NT2_FUNCTION_IMPLEMENTATION(tag::is_greater_equal_ , ge              , 2 )
  NT2_FUNCTION_IMPLEMENTATION(tag::logical_or_       , logical_or      , 2 )
  NT2_FUNCTION_IMPLEMENTATION(tag::logical_or_       , l_or            , 2 )
  NT2_FUNCTION_IMPLEMENTATION(tag::logical_and_      , logical_and     , 2 )
  NT2_FUNCTION_IMPLEMENTATION(tag::logical_and_      , l_and           , 2 )
  NT2_FUNCTION_IMPLEMENTATION(tag::shift_right_      , shift_right     , 2 )
  NT2_FUNCTION_IMPLEMENTATION(tag::shift_right_      , shr             , 2 )
  NT2_FUNCTION_IMPLEMENTATION(tag::shift_left_       , shift_left      , 2 )
  NT2_FUNCTION_IMPLEMENTATION(tag::shift_left_       , shl             , 2 )
  NT2_FUNCTION_IMPLEMENTATION(tag::comma_            , comma           , 2 )
  NT2_FUNCTION_IMPLEMENTATION(tag::comma_            , then            , 2 )

  //////////////////////////////////////////////////////////////////////////////
  // Ternary function wrappers
  //////////////////////////////////////////////////////////////////////////////
  NT2_FUNCTION_IMPLEMENTATION(tag::if_else_          , if_else         , 3 )
  NT2_FUNCTION_IMPLEMENTATION(tag::if_else_          , where           , 3 )
}

#endif
