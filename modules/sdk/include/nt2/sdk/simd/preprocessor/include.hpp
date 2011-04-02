/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_PREPROCESSOR_INCLUDE_HPP_INCLUDED
#define NT2_SDK_SIMD_PREPROCESSOR_INCLUDE_HPP_INCLUDED

#include <nt2/sdk/simd/extensions.hpp>
#include <nt2/sdk/details/preprocessor.hpp>
#include <nt2/sdk/simd/preprocessor/sse.hpp>
#include <nt2/sdk/simd/preprocessor/vmx.hpp>

#define NT2_SIMD_INCLUDE(F)             NT2_PP_INCLUDE(NT2_SIMD_INCLUDE_BASE,F)
#define NT2_SIMD_RELATIVE_INCLUDE(B,F)  NT2_SIMD_RELATIVE_INCLUDE_BASE(B,F)

#endif

