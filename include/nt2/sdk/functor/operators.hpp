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
#include <nt2/sdk/functor/category.hpp>
#include <nt2/sdk/functor/details/tags.hpp>
//#include <nt2/sdk/functor/details/comma.hpp> //*
#include <nt2/sdk/functor/details/shifts.hpp>
#include <nt2/sdk/functor/details/boolean.hpp>
#include <nt2/sdk/functor/details/bitwise.hpp>
//#include <nt2/sdk/functor/details/if_else.hpp>//*
#include <nt2/sdk/functor/details/complement.hpp>
//#include <nt2/sdk/functor/details/terminal.hpp>//*
#include <nt2/sdk/functor/details/arithmetic.hpp>
#include <nt2/sdk/functor/preprocessor/function.hpp>

namespace nt2
{
  //////////////////////////////////////////////////////////////////////////////
  // Unary function wrappers
  //////////////////////////////////////////////////////////////////////////////
  NT2_FUNCTION_IMPLEMENTATION(functors::unary_plus_ , unary_plus  , 1 )
  NT2_FUNCTION_IMPLEMENTATION(functors::unary_plus_ , identity    , 1 )
  NT2_FUNCTION_IMPLEMENTATION(functors::unary_plus_ , id          , 1 )
  NT2_FUNCTION_IMPLEMENTATION(functors::complement_ , complement  , 1 )
  NT2_FUNCTION_IMPLEMENTATION(functors::complement_ , bitwise_not , 1 )
  NT2_FUNCTION_IMPLEMENTATION(functors::complement_ , b_not       , 1 )
  NT2_FUNCTION_IMPLEMENTATION(functors::logical_not_, logical_not , 1 )
  NT2_FUNCTION_IMPLEMENTATION(functors::logical_not_, l_not       , 1 )
  NT2_FUNCTION_IMPLEMENTATION(functors::neg_        , neg         , 1 )

  //////////////////////////////////////////////////////////////////////////////
  // Binary function wrappers
  //////////////////////////////////////////////////////////////////////////////
  NT2_FUNCTION_IMPLEMENTATION(functors::plus_             , plus            , 2 )
  NT2_FUNCTION_IMPLEMENTATION(functors::plus_             , add             , 2 )
  NT2_FUNCTION_IMPLEMENTATION(functors::minus_            , minus           , 2 )
  NT2_FUNCTION_IMPLEMENTATION(functors::minus_            , sub             , 2 )
  NT2_FUNCTION_IMPLEMENTATION(functors::multiplies_       , multiplies      , 2 )
  NT2_FUNCTION_IMPLEMENTATION(functors::multiplies_       , mul             , 2 )
  NT2_FUNCTION_IMPLEMENTATION(functors::divides_          , divides         , 2 )
  NT2_FUNCTION_IMPLEMENTATION(functors::divides_          , rdiv            , 2 )
  NT2_FUNCTION_IMPLEMENTATION(functors::divides_          , div             , 2 )
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
}

#endif
