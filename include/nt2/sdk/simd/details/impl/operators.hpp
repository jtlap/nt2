/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_OPERATORS_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_OPERATORS_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Extension specific additional helpers
////////////////////////////////////////////////////////////////////////////////
#if defined( NT2_SIMD_XOP)
//  #include <nt2/sdk/simd/native/details/impl/sse/xop/macros.hpp>
#elif defined( NT2_SIMD_AVX)
//  #include <nt2/sdk/simd/native/details/impl/sse/avx/macros.hpp>
#elif (defined( NT2_SIMD_SSE4_2) || defined( NT2_SIMD_SSE4_1))
#elif defined( NT2_SIMD_SSSE3)
#elif defined( NT2_SIMD_SSE3)
#elif defined( NT2_SIMD_SSE2)
#endif

////////////////////////////////////////////////////////////////////////////////
// Include all specific implementation of operators
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/simd/details/common.hpp>
#include <nt2/sdk/simd/preprocessor/include.hpp>

#include NT2_SIMD_INCLUDE(complement.hpp)
#include NT2_SIMD_INCLUDE(neg.hpp)
#include NT2_SIMD_INCLUDE(bitwise_and.hpp)
#include NT2_SIMD_INCLUDE(bitwise_or.hpp)
#include NT2_SIMD_INCLUDE(bitwise_xor.hpp)
#include NT2_SIMD_INCLUDE(divides.hpp)
#include NT2_SIMD_INCLUDE(is_equal_to.hpp)
#include NT2_SIMD_INCLUDE(is_greater.hpp)
#include NT2_SIMD_INCLUDE(is_greater_equal.hpp)
#include NT2_SIMD_INCLUDE(is_less.hpp)
#include NT2_SIMD_INCLUDE(is_less_equal.hpp)
#include NT2_SIMD_INCLUDE(is_not_equal_to.hpp)
#include NT2_SIMD_INCLUDE(logical_and.hpp)
#include NT2_SIMD_INCLUDE(logical_or.hpp)
#include NT2_SIMD_INCLUDE(logical_not.hpp)
#include NT2_SIMD_INCLUDE(minus.hpp)
#include NT2_SIMD_INCLUDE(modulo.hpp)
#include NT2_SIMD_INCLUDE(multiplies.hpp)
#include NT2_SIMD_INCLUDE(plus.hpp)
#include NT2_SIMD_INCLUDE(shift_left.hpp)
#include NT2_SIMD_INCLUDE(shift_right.hpp)

#endif
