/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_PREPROCESSOR_VMX_HPP_INCLUDED
#define NT2_SDK_SIMD_PREPROCESSOR_VMX_HPP_INCLUDED

#if defined(NT2_SIMD_ALTIVEC)
  #define NT2_SIMD_INCLUDE_BASE() nt2/sdk/simd/details/impl/vmx/altivec/
  #define NT2_SIMD_RELATIVE_INCLUDE_BASE(B,F) BOOST_PP_STRINGIZE(B()simd/vmx/altivec/F) 
#endif

#endif
