/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_NATIVE_OPERATORS_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_NATIVE_OPERATORS_HPP_INCLUDED

#include <nt2/sdk/simd/category.hpp>
#include <nt2/sdk/functor/operators.hpp>

namespace nt2 { namespace simd
{
  NT2_FUNCTION_IMPLEMENTATION( functors::complement_      , operator~   , 1 )
  NT2_FUNCTION_IMPLEMENTATION( functors::logical_not_     , operator!   , 1 )
  NT2_FUNCTION_IMPLEMENTATION( functors::neg_             , operator-   , 1 )
  NT2_FUNCTION_IMPLEMENTATION( functors::bitwise_and_     , operator&   , 2 )
  NT2_FUNCTION_IMPLEMENTATION( functors::bitwise_or_      , operator|   , 2 )
  NT2_FUNCTION_IMPLEMENTATION( functors::bitwise_xor_     , operator^   , 2 )
  NT2_FUNCTION_IMPLEMENTATION( functors::divides_         , operator/   , 2 )
  NT2_FUNCTION_IMPLEMENTATION( functors::logical_and_     , operator&&  , 2 )
  NT2_FUNCTION_IMPLEMENTATION( functors::logical_or_      , operator||  , 2 )
  NT2_FUNCTION_IMPLEMENTATION( functors::minus_           , operator-   , 2 )
  NT2_FUNCTION_IMPLEMENTATION( functors::multiplies_      , operator*   , 2 )
  NT2_FUNCTION_IMPLEMENTATION( functors::plus_            , operator+   , 2 )
  NT2_FUNCTION_IMPLEMENTATION( functors::modulo_          , operator%   , 2 )
  NT2_FUNCTION_IMPLEMENTATION( functors::shift_left_      , operator<<  , 2 )
  NT2_FUNCTION_IMPLEMENTATION( functors::shift_right_     , operator>>  , 2 )
  NT2_FUNCTION_IMPLEMENTATION( functors::if_else_         , if_else_    , 3 )
} }

#include <nt2/sdk/simd/details/impl/operators.hpp>

#endif
