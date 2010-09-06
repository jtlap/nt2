/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_NATIVE_COMPARISONS_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_NATIVE_COMPARISONS_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Setup SIMD extension specific boolean operations
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/simd/category.hpp>

namespace nt2 { namespace simd
{
  struct is_equal_          {};
  struct is_not_equal_      {};
  struct is_less_           {};
  struct is_greater_        {};
  struct is_less_equal_     {};
  struct is_greater_equal_  {};

  NT2_FUNCTION_IMPLEMENTATION( is_equal_        , operator==, 2 )
  NT2_FUNCTION_IMPLEMENTATION( is_not_equal_    , operator!=, 2 )
  NT2_FUNCTION_IMPLEMENTATION( is_less_         , operator< , 2 )
  NT2_FUNCTION_IMPLEMENTATION( is_greater_      , operator> , 2 )
  NT2_FUNCTION_IMPLEMENTATION( is_less_equal_   , operator<=, 2 )
  NT2_FUNCTION_IMPLEMENTATION( is_greater_equal_, operator>=, 2 )
} }

#include <nt2/sdk/simd/details/impl/comparisons.hpp>

#endif
