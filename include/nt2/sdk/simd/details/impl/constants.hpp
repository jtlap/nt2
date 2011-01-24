/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_CONSTANTS_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_CONSTANTS_HPP_INCLUDED

#include <nt2/sdk/simd/preprocessor/include.hpp>

////////////////////////////////////////////////////////////////////////////////
// True and False forward to ~0 and 0 respectively
////////////////////////////////////////////////////////////////////////////////
#include NT2_SIMD_INCLUDE(true.hpp)
#include NT2_SIMD_INCLUDE(false.hpp)

////////////////////////////////////////////////////////////////////////////////
// In AltiVec some constants are computed faster by doing computation than using
// from memory values
////////////////////////////////////////////////////////////////////////////////
#if defined(NT2_SIMD_VMX_FAMILY)
#include NT2_SIMD_INCLUDE(zero.hpp)
#endif

#endif
