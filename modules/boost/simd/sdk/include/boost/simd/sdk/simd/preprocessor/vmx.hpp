/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_PREPROCESSOR_VMX_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PREPROCESSOR_VMX_HPP_INCLUDED

#if defined(BOOST_SIMD_ALTIVEC)
  #define BOOST_SIMD_RELATIVE_INCLUDE_BASE(B,F) BOOST_PP_STRINGIZE(B()simd/vmx/altivec/F) 
#endif

#endif
